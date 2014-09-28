#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#endif

#include <iostream>

#include "ClientManager.h"
#include "State.hxx"
#include "callid.hxx"
//#include "gamedatasend.hpp"
#include "cocos2d.h"
#include "gutil.h"
//#include "GWebManager.h"

namespace GNET{

const Protocol::Manager::Session::State *ClientManager::GetInitState() const
{
	return &state_GLoginClient;
}
void ClientManager::OnAddSession(Session::ID sid)
{
	std::cout << "ClientManager::OnAddSession sid= "<< sid << std::endl;
	this->sid = sid;

	Conf *conf = Conf::GetInstance();
	Conf::section_type section = Identification(); 
	bool bIgnore = atoi(conf->find(section, "ignore_state").c_str()) > 0;
	SetIgnore(sid, bIgnore);
    PrintDelayTime();

	DoLuaString("LNetworkMgr:onConnect");
}
void ClientManager::OnDelSession(Session::ID sid)
{
	DoLuaString("LNetworkMgr:onDisConnect");
	std::cout << "ClientManager::OnDelSession sid= "<< sid << std::endl;
	this->sid = 0;
}
void ClientManager::OnAbortSession(Session::ID sid)
{
	DoLuaString("LNetworkMgr:onDisConnect");
	std::cout << "ClientManager::OnAbortSession sid= "<< sid << std::endl;
	this->sid = 0;
}
void ClientManager::OnCheckAddress(SockAddr &) const
{
}

void ClientManager::LogProtocol(const Protocol *p)
{
	USING_NS_CC;
	if (p){
		/*if (p->GetType() != PROTOCOL_GAMEDATASEND){
			CCLog("send protocol(%d)", p->GetType());
		}else{
			const GamedataSend *pGamedata = dynamic_cast<const GamedataSend *>(p);
			unsigned short cmd = *(unsigned short *)(pGamedata->data.begin());
			CCLog("send gamedata(%d)", cmd);
		}*/
	}
}

bool ClientManager::Send(const Marshal::OctetsStream &os, bool urg)
{
	return Protocol::Manager::Send(sid, os, urg);
}

bool ClientManager::Send(const Protocol *protocol, bool urg)
{
	LogProtocol(protocol);
	return Protocol::Manager::Send(sid, protocol, urg);
}
bool ClientManager::Send(const Protocol &protocol, bool urg) 
{
	LogProtocol(&protocol);
	return Protocol::Manager::Send(sid, protocol, urg);
}

void ClientManager::ChangeState(Session::State *state)
{
	Protocol::Manager::ChangeState(getSid(), state);
}

bool ClientManager::CheckUnknownProtocol(Session::ID id, Protocol::Type type, unsigned int size)
{
    if (type == 0 || type > 65535)
        return false;
    else if (size == 0 || size > 131072)
        return false;
    return true;
}
    
void ClientManager::DispatchUnknownProtocol(Session::ID id, Protocol::Type type, const Marshal::OctetsStream & data)
{
    printf("DispatchUnknownProtocol type=%d datasize=%ld\n", type, data.size());
	ProtocolEnum * pe = new ProtocolEnum;
	pe->type = type;
	pe->unknownprotocol = new Octets(data);

	protocols.push_back(pe);
}

void ClientManager::DispatchProtocol(Session::ID sid, Protocol * protocol)
{
	ProtocolEnum * pe = new ProtocolEnum;
	pe->type = protocol->GetType();
	pe->protocol = protocol;

	protocols.push_back(pe);
}
    
void ClientManager::SetConnectTime()
{
#ifndef WIN32
    gettimeofday(&connect_time, NULL);
#endif
}
    
void ClientManager::PrintDelayTime()
{
#ifndef WIN32
    struct timeval now_time;
    gettimeofday(&now_time, NULL);
    float delay = (float)(now_time.tv_sec - connect_time.tv_sec) + (now_time.tv_usec - connect_time.tv_usec)/1000000.f;
    CCLog("net delay=%f\n", delay);
#endif
}

};