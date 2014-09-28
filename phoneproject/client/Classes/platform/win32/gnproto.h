#ifndef __PROTOCOL_H
#define __PROTOCOL_H
#pragma warning (disable:4355)

#include <map>
#include <set>
#include <list>
#include <queue>
#include <algorithm>
#include <functional>
#include <iterator>

#include "gnpassiveio.h"
#include "gnactiveio.h"
#include "gnmarshal.h"
//#include "gnthread.h"
#include "gntimer.h"
#define ZLIB_WINAPI
#include "zlib.h"


namespace GNET
{

#define PROTOCOL_BINDER		0

class Protocol : public Marshal
{

	friend class ProtocolBinder;
	friend class CompressBinder;
public:
	class Exception { };
	typedef unsigned int Type;
protected:
	Type type;
	Protocol() { }
private:
	typedef std::map<Type, const Protocol*> Map;
	static Map& GetMap();
	void Encode(Marshal::OctetsStream &os) const
	{
		os << CompactUINT(type) << (Marshal::OctetsStream() << *this);
	}

protected:
	virtual ~Protocol() { }
	Protocol(Type t) : type(t)
	{
		if (!GetStub(type)) GetMap().insert(std::make_pair(type, this));
	}
	Protocol(const Protocol &rhs) : type(rhs.type){ }
public:
	static const Protocol *GetStub(Type type)
	{
		Map::const_iterator it = GetMap().find(type);
		return it == GetMap().end() ? NULL : (*it).second;
	}
	static Protocol *Create(Type type)
	{
		const Protocol *stub = GetStub(type);
		return stub ? stub->Clone() : NULL;
	}
	class Manager
	{
		friend class Protocol;  
	public:
		class Session : public NetSession
		{
			friend class Protocol;
			friend class Manager;
			friend class ProtocolBinder;
			friend class CompressBinder;

			struct Stream : public Marshal::OctetsStream
			{
				Session *session;
				mutable bool check_policy;
				mutable bool proto_ignore;
				Stream(Session *s) : session(s), check_policy(true), proto_ignore(false) { }
			};
		public:
			class State
			{
				typedef std::set<Type> Set;
				Set set;
				int timeout;
			public:
				State (Type *first, size_t len, int t = 0) : set(first, first+len), timeout(t) { }
				State (Type *first, Type *last, int t = 0) : set(first, last), timeout(t) { }
				bool TypePolicy(Type type) const { return set.find(type) != set.end(); }
				bool TimePolicy(int t) const { return timeout <= 0 || t < timeout; }
				size_t SetSize() const { return set.size(); }
			};

			typedef unsigned int ID;

			ID GetSid() { return sid; }

		private:
			typedef std::map<ID, Session *> Map;
			static ID session_id;
			ID sid;
			Stream isc;
			Stream is;
			std::queue<Marshal::OctetsStream> osc;
			std::deque<Marshal::OctetsStream> os;
			Manager *manager;
			const State *state;
			Timer timer;
			bool ignore;

			NetSession *Clone () const	{ return new Session(*this); }
			std::string Identification() const { return manager->Identification(); }
			void Close() 
			{ 
				_snprintf(errormsg, ERRSIZE, "Active close\n");
				NetSession::Close();
			}
			void OnCheckAddress(SockAddr &sa) const { manager->OnCheckAddress(sa); }
			void OnOpen()  { timer.Reset(); manager->AddSession(sid, this); }
			void OnClose() { manager->DelSession(sid, this); }
			void OnAbort() { manager->AbortSession(sid, this); }
			void Decompress()
			{
				try
				{
					size_t sz_org;
					OctetsStream data_c,data_o;
					isc>>Marshal::Begin >> CompactUINT(sz_org)>> data_c >> Marshal::Commit;
					size_t dstLen=sz_org;
					data_o.reserve(dstLen);
					if (Z_OK == uncompress((Bytef*)data_o.begin(),(uLongf*)&dstLen,(const Bytef*)data_c.begin(),data_c.size()))
					{
						data_o.resize(dstLen);
						is.insert(is.end(),data_o.begin(),data_o.size());
					}
				}
				catch (...)
				{
					isc>>Marshal::Rollback;
				}
			}
			void OnRecv()
			{
				timer.Reset();
				Octets &input = Input();
				if (manager->blCompress)
				{
					isc.insert(isc.end(), input.begin(), input.end());
					Decompress();
				}
				else
				{
					is.insert(is.end(), input.begin(), input.end());
				}
				input.clear();
				Protocol *p = NULL;
				
				try
				{
					for ( p ; (p = Protocol::Decode(is)) ; manager->DispatchProtocol(sid, p));
				}
				catch (Protocol::Exception&)
				{
					NetSession::Close();
				}
			}
			bool Compress()
			{       
				if (!os.size()) return false;
				Marshal::OctetsStream ss; //source stream
				Marshal::OctetsStream cs; //compressed stream
				Marshal::OctetsStream tmp;
				//printf("Compress:: Enter compress procedure....\n");
				for (;os.size();)
				{       
					//if (os.front().size() + obuffer.size() > obuffer.capacity()) break;//压缩后尺寸大于原尺寸如何判断
					ss.insert(ss.end(),os.front().begin(),os.front().size());
					os.pop_front();
				}   
				tmp.reserve(compressBound((uLong)ss.size()));
				uLong dstLen=tmp.capacity();
				if (Z_OK==compress((Bytef*)tmp.begin(),&dstLen,(Bytef*)ss.begin(),ss.size()))
				{
					tmp.resize(dstLen);
					cs<<CompactUINT((size_t)ss.size());
					cs<<tmp;
					osc.push(cs);
					//printf("Compress:: compress successfully. origin size %d, compress size %d\n",ss.size(),cs.size());
					return true;
				}
				else
				{   
					//printf("Compress:: compress failed.\n");
					return false;
				}       
			}
			void OnSend()
			{
				if (state->TimePolicy(timer.Elapse()))
				{
					if (manager->blCompress)
					{
						Compress();
						if (osc.size())
						{
							for (;osc.size() && Output(osc.front()); osc.pop());
							timer.Reset();
						}
					}
					else
					{
						if (os.size()&&Output(os.front()))
						{
							os.pop_front();
							//for (;os.size() && Output(os.front()); os.pop_front());
							timer.Reset();
						}
					}

				}
				else
				{
					_snprintf(errormsg, 128, "Local timeout\n");
					NetSession::Close();
				}
			}
			bool NoMoreData() const { return os.empty(); }
			bool Send(const Protocol *protocol, bool urg)
			{
				//Thread::Mutex::Scoped l(locker);
				Marshal::OctetsStream ps;
				protocol->Encode(ps);
				if(urg)
					os.push_front(ps);
				else
					os.push_back(ps);
				PollIO::WakeUp();
				return true;
			}
			bool Send(int tag,const Marshal::OctetsStream&ps, bool urg)
			{
				//Thread::Mutex::Scoped l(locker);
				if(urg)
					os.push_front(ps);
				else
					os.push_back(ps);
				PollIO::WakeUp();
				return true;
			}

			bool StatePolicy(Type type) const { return state->TypePolicy(type); }
			size_t AcceptSize() const { return state->SetSize(); }
			void ChangeState(const State *newstate)
			{
				//Thread::Mutex::Scoped l(locker);
				timer.Reset();
				state = newstate;
			}
			void SetIgnore(bool val) { ignore = val;}
			bool Ignore() const { return ignore; }
			Session(Manager *n) : sid(session_id++), isc(this),is(this), manager(n), state(n->GetInitState()),ignore(false){ } 
			Session(const Session &rhs) : NetSession(rhs),isc(this),is(this), sid(session_id++), manager(rhs.manager), 
										  state(rhs.state), ignore(false)
			{}
			virtual void Destroy() 
			{ 
				while(!osc.empty())
					osc.pop();
				while(!os.empty())
					os.pop_front();
				delete this; 
			}
		};
	private:
		Session::Map map;
		//Thread::RWLock locker_map;
		void AddSession(Session::ID sid, Session *session)
		{
			{
			//Thread::RWLock::WRScoped l(locker_map);
			map.insert(std::make_pair(sid, session));
			}
			OnAddSession(sid);
		}
		void DelSession(Session::ID sid, Session *)
		{
			OnDelSession(sid);
			{
			//Thread::RWLock::WRScoped l(locker_map);
			map.erase(sid);
			}
		}
		void AbortSession(Session::ID sid, Session *)
		{
			OnAbortSession(sid);
		}
		Session *GetSession(Session::ID sid)
		{
			Session::Map::iterator it = map.find(sid);
			return it == map.end() ? NULL : (*it).second;
		}
	public:
		bool blCompress;
		Manager() { 
			blCompress=false;
		}
		virtual ~Manager() { }
		bool SetISecurity(Session::ID id, Security::Type type, const Octets &key)
		{
			//Thread::RWLock::RDScoped l(locker_map);
			Session *session = GetSession(id);
			if (session) session->SetISecurity(type, key);
			return session != NULL;
		}
		bool SetOSecurity(Session::ID id, Security::Type type, const Octets &key)
		{
			//Thread::RWLock::RDScoped l(locker_map);
			Session *session = GetSession(id);
			if (session) session->SetOSecurity(type, key);
			return session != NULL;
		}
		bool Send(Session::ID id, const Protocol *protocol, bool urg=false)
		{
			bool rc = false;
			//Thread::RWLock::RDScoped l(locker_map);
			Session *session = GetSession(id);
			if (session) rc = session->Send(protocol, urg);
			return rc;
		}
		bool Send(Session::ID id, const Protocol &protocol, bool urg=false) { return Send(id,&protocol,urg); }
		bool Send(Session::ID id, const Marshal::OctetsStream &os, bool urg=false)
		{
			bool rc = false;
			//Thread::RWLock::RDScoped l(locker_map);
			Session *session = GetSession(id);
			if (session) rc = session->Send(0,os, urg);
			return rc;
		}
		bool Close(Session::ID id)
		{
			//Thread::RWLock::RDScoped l(locker_map);
			Session *session = GetSession(id);
			if (session) session->Close();
			return session != NULL;
		}

		virtual const char* GetLastError()
		{
			return errormsg;
		}

		bool ChangeState(Session::ID id, Session::State *state)
		{
			//Thread::RWLock::RDScoped l(locker_map);
			Session *session = GetSession(id);
			if (session) session->ChangeState(state);
			return session != NULL;
		}
		virtual void OnAddSession(Session::ID) = 0;
		virtual void OnDelSession(Session::ID) = 0;
		virtual void OnAbortSession(Session::ID) {}
		virtual void OnRecvProtocol(Session::ID, Protocol*) {}

		virtual const Session::State *GetInitState() const = 0;
		virtual int  PriorPolicy(Type type) const
		{
			return Protocol::GetStub(type)->PriorPolicy();
		}
		virtual bool InputPolicy(Type type, size_t size) const
		{
			return Protocol::GetStub(type)->SizePolicy(size);
		}
		virtual std::string Identification() const = 0;
		virtual void OnCheckAddress(SockAddr &) const { }
		bool SetIgnore(Session::ID id, bool val)
		{
			//Thread::RWLock::RDScoped l(locker_map);
			Session *session = GetSession(id);
			if (session) session->SetIgnore(val);
			return session != NULL;
		}
		virtual bool CheckUnknownProtocol(Session::ID id, Protocol::Type type, unsigned int size) {return false;}
		virtual void DispatchUnknownProtocol(Session::ID id, Protocol::Type type, const OctetsStream & data) {}
		virtual void DispatchProtocol(Session::ID sid, Protocol * p)
		{
			// if overwrite this function, you should delete protocol by your self
			OnDispatchProtocol(sid, p);
			p->Destroy();
		}
		virtual void OnDispatchProtocol(Session::ID sid, Protocol * p) {}

		friend class Session; 
	};
private:
	
	/*class Task : public Thread::Runnable
	{
		Manager *manager;
		Manager::Session::ID sid;
		Protocol *protocol;
		bool immediately;
	public:
		~Task () { }
		Task(Manager *m, Manager::Session::ID id, Protocol *p) : 
			manager(m), sid(id), protocol(p), immediately(false) { }
		void Run()
		{
			try
			{
				protocol->Notify(manager, sid);
			}
			catch (Protocol::Exception &)
			{
				manager->Close(sid);
			}
			delete this;
		}

		static void Dispatch(Manager *manager, Manager::Session::ID sid, Protocol *protocol)
		{
			Task *task = new Task(manager, sid, protocol);
			Thread::Pool::AddTask(task);
			PollIO::WakeUp();
		}
	};*/
	static void CheckPolicy(Type type, unsigned int size, const Manager::Session::Stream &is)
	{
		if (Protocol::GetStub(type))
		{
			// origin check
			if (!is.session->StatePolicy(type))
			{
				if (!is.session->Ignore()) 
				{
					fprintf(stderr, "Protocol state policy error.sid=%d,type=%d,size=%d",
						is.session->GetSid(),type,size);
					throw Protocol::Exception();
				}
				else
				{
					is.proto_ignore = true;
				}
			}
			if (!is.session->manager->InputPolicy(type, size))
			{
				fprintf(stderr, "Protocol size policy error.sid=%d,type=%d,size=%d",
					is.session->GetSid(),type,size);
				throw Protocol::Exception();
			}
		}
		else
		{
			// unkown check
			if (!is.session->manager->CheckUnknownProtocol(is.session->GetSid(), type, size))
			{
				fprintf(stderr, "Protocol Unknown . sid=%d,type=%d,size=%d,acceptsize=%d",
					is.session->GetSid(),type,size,is.session->AcceptSize());
				throw Protocol::Exception();
			}
		}
		is.check_policy = false;
	}
	static Protocol *Decode(const Manager::Session::Stream &is)
	{
		if (is.eos())
			return NULL;
		Protocol *protocol = NULL;
		Protocol::Type type = 0;
		unsigned int size = 0;
		try
		{
			bool loop = true;
			while(loop)
			{
				if (is.eos()) return NULL;

				if (is.check_policy)
				{
					is >> Marshal::Begin >> CompactUINT(type) >> CompactUINT(size) >> Marshal::Rollback;
					CheckPolicy(type, size, is);
				}

				Manager::Session::Stream data(is.session);
				data.reserve(size);
				is >> Marshal::Begin >> CompactUINT(type) >> data >> Marshal::Commit;

				if (!is.proto_ignore)
				{
					if ((protocol = Protocol::Create(type))) 
					{
						data >> *protocol;
						loop = false;
					}
					else
					{
						is.session->manager->DispatchUnknownProtocol(is.session->GetSid(), type, data);
					}
				}
				else
					printf("proto_ignore type=%d\n",type);
				is.check_policy = true;
				is.proto_ignore = false;
			}
		}
		catch (Marshal::Exception &)
		{
			if (protocol)
			{
				fprintf(stderr, "Protocol(type=%d,size=%d) Decode Error.", type, size);
				protocol->Destroy();
				throw Protocol::Exception();
			}
			is >> Marshal::Rollback;
		}
		return protocol;
	}
public:
	virtual void Process(Manager *mgr, Manager::Session::ID sid){}
	virtual void Notify(Manager *mgr, Manager::Session::ID sid)
	{
		mgr->OnRecvProtocol(sid, this);
	}

	virtual Protocol *Clone() const = 0;
	virtual void Destroy() { delete this; }
	virtual int  PriorPolicy() const { return 0; }
	virtual bool SizePolicy(size_t) const { return true; }

	static Manager::Session::ID Server(Manager *manager) 
	{ 
		Manager::Session* s = new Manager::Session(manager);
		PassiveIO::Open(s); 
		return s->GetSid();
	}

	static Manager::Session::ID  Client(Manager *manager) 
	{ 
		Manager::Session* s = new Manager::Session(manager);
		ActiveIO::Open(s); 
		return s->GetSid();
	}
	static Manager::Session::ID  Client(Manager *manager, const char* host, unsigned short port) 
	{
		Manager::Session* s = new Manager::Session(manager);
		ActiveIO::Open(s, host, port); 
		return s->GetSid();
	}

	virtual Type GetType() const { return type; }


	friend class Manager;
	friend class Task;  
	friend class Manager::Session;   
};

class ProtocolBinder : public Protocol
{
	Protocol *Clone() const { return new ProtocolBinder(*this); }
	typedef std::vector<Protocol *> ProtocolVector;
	ProtocolVector pv;
	//mutable Thread::RWLock locker_vector;
public:
	~ProtocolBinder()
	{
		//Thread::RWLock::WRScoped l(locker_vector);
		std::for_each(pv.begin(), pv.end(), std::mem_fun(&Protocol::Destroy));
	}
	explicit ProtocolBinder(Type type) : Protocol(type) { }
	ProtocolBinder(const ProtocolBinder &rhs) : Protocol(rhs)
	{
		//Thread::RWLock::RDScoped l(rhs.locker_vector);
		std::transform(rhs.pv.begin(), rhs.pv.end(), std::back_inserter(pv), std::mem_fun(&Protocol::Clone));
	}
	OctetsStream& marshal(OctetsStream &os) const
	{
		//Thread::RWLock::RDScoped l(locker_vector);
		for(ProtocolVector::const_iterator it = pv.begin(); it != pv.end(); ++it) (*it)->Encode(os);
		return os;
	}
	const OctetsStream& unmarshal(const OctetsStream &os)
	{
		Manager::Session::Stream &is = (Manager::Session::Stream &)(os);
		//Thread::RWLock::WRScoped l(locker_vector);
		for (Protocol *p; (p = Protocol::Decode(is)); is.session->manager->DispatchProtocol(is.session->sid, p));
		/*
		for (ProtocolVector::const_iterator it = pv.begin(); it != pv.end(); ++it)
			Protocol::Task::Dispatch(is.session->manager, is.session->sid, *it);
		*/
		return os;
	}

	void Process(Manager *manager, Manager::Session::ID sid)
	{
	}
	void Notify(Manager *mgr, Manager::Session::ID sid)
	{
		{
			//Thread::RWLock::WRScoped l(locker_vector);
			for (ProtocolVector::const_iterator it=pv.begin(); it!=pv.end();++it)
			{
				try
				{
					mgr->OnRecvProtocol(sid,(*it));
				}
				catch (Protocol::Exception &) {
					mgr->Close(sid);
				}
			}
			pv.clear();
		}
		Destroy();
	}

	ProtocolBinder& bind(const Protocol *p)
	{
		//Thread::RWLock::WRScoped l(locker_vector);
		pv.push_back(p->Clone()); 
		return *this;
	}
	ProtocolBinder& bind(const Protocol &p)
	{
		//Thread::RWLock::WRScoped l(locker_vector);
		pv.push_back(p.Clone());
		return *this;
	}
};

};

#endif
