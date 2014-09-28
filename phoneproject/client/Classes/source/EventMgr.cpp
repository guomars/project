#include "EventMgr.h"
#include "callid.hxx"
#include "DataMgr.h"
#include "NetworkMgr.h"
#include "ClientManager.h"
#include "gutil.h"

USING_NS_CC;

void EventMgr::tick(float dt)
{
	EventMgr::sharedMgr()->DealMsg();
}

void EventMgr::DealMsg()
{
	ProtocolEnum * pe = NULL;
	while(pe = ClientManager::GetInstance()->GetProtocolEnum())
	{
		if (pe->protocol)	//已知协议
		{
			OnDealMsg(pe->protocol);
		}
		else if (pe->unknownprotocol)	//未知协议
		{
			GNET::Marshal::OctetsStream os(*(pe->unknownprotocol));
			NetworkMgr::sharedMgr()->SetDealUnknownProtocol(os);
			DoLuaString("LNetworkMgr:onUnknownProtocol",(int)pe->type);
		}

		delete pe;
	}
}

void EventMgr::OnDealMsg(Protocol * p)
{
	if(!NetworkMgr::sharedMgr()->receiveProtocol(p))
	{
		if(p->GetType() != 0)
			CCLog("Protocol(%d) ignored.",p->GetType());
	}/*else if (p->GetType() != PROTOCOL_GAMEDATASEND){
		CCLog("Protocol(%d) processed.", p->GetType());
	}*/
}