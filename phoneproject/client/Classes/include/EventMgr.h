#ifndef __EVENT_MGR_H__
#define __EVNET_MGR_H__

#include "cocos2d.h"
#include <list>
#ifdef WIN32
#include "gnproto.h"
#else
#include "protocol.h"
#endif

using namespace GNET;

class EventMgr
{
	EventMgr() {}
public:
	static EventMgr * sharedMgr()
	{
		static EventMgr event_mgr;
		return &event_mgr;
	}

	void tick(float dt);

	void DealMsg();
	void OnDealMsg(Protocol * p);
};

#endif