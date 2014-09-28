#ifndef __CLIENT_MANAGER_H__
#define __CLIENT_MANAGER_H__

#ifdef WIN32
#include "gnproto.h"
#else
#include "protocol.h"
#endif

#include <list>

namespace GNET{

class ProtocolEnum
{
public:
	Protocol * protocol;
	Octets * unknownprotocol;
	Protocol::Type type;
	
	ProtocolEnum(): protocol(NULL), unknownprotocol(NULL) {}
	~ProtocolEnum()
	{
		if (protocol)
			protocol->Destroy();
		if (unknownprotocol)
			delete unknownprotocol;
	}
};

class ClientManager : public Protocol::Manager
{
	int net_type;
	Session::ID sid;
	size_t      accumulate_limit;
    
#ifndef WIN32
    struct timeval connect_time;
#endif

	typedef std::list<ProtocolEnum *> ProtocolsType;
	ProtocolsType protocols;

	const Session::State *GetInitState() const;
    bool OnCheckAccumulate(size_t size) const { return accumulate_limit == 0 || size < accumulate_limit; }
    void OnAddSession(Session::ID sid);
    void OnDelSession(Session::ID sid);
    void OnAbortSession(Session::ID sid);
    void OnCheckAddress(SockAddr &) const;
	ClientManager():net_type(0),sid(0),accumulate_limit(65535){}
public:
	void SetNetType(int ntype) {net_type = ntype;}
    static ClientManager *GetInstance() 
	{
		static ClientManager instance;
		return &instance; 
	}
    std::string Identification() const { return "ClientManager"; }
    void SetAccumulate(size_t size) { accumulate_limit = size; }
	Session::ID getSid() { return sid; }

	bool Send(const Protocol *protocol, bool urg=false);
	bool Send(const Protocol &protocol, bool urg=false);
	bool Send(const Marshal::OctetsStream &os, bool urg=false);
	void ChangeState(Session::State *state);

    bool CheckUnknownProtocol(Session::ID id, Protocol::Type type, unsigned int size);

    void DispatchUnknownProtocol(Session::ID id, Protocol::Type type, const Marshal::OctetsStream & data);

	void DispatchProtocol(Session::ID sid, Protocol * protocol);

	inline ProtocolEnum * GetProtocolEnum()
	{
		if (protocols.empty())
			return NULL;
		ProtocolEnum * pe = protocols.front();
		protocols.pop_front();
		return pe;
	}

	static void LogProtocol(const Protocol *p);
    
    void SetConnectTime();
    void PrintDelayTime();


};

};

#endif