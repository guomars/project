#ifndef __G_FUNC_MGR_H__
#define __G_FUNC_MGR_H__

#include "cocos2d.h"
#include "CCLuaEngine.h"

using namespace cocos2d;

enum
{
	EVENT_BEGIN,

	EVENT_UIWIDGET_PUSH_DOWN,
	EVENT_UIWIDGET_MOVE,
	EVENT_UIWIDGET_RELEASE,

	EVENT_END,
};

//typedef void (*func)(cocos2d::CCObject * obj);
typedef std::map<unsigned short , std::string> SubUidFuncMapType;
typedef std::map<unsigned int, SubUidFuncMapType> UidFuncMapType;
extern UidFuncMapType uid_func_map;

class GFuncMgr
{
	GFuncMgr() {}
public:
	static GFuncMgr * GetInstance()
	{
		static GFuncMgr gfuncmgr;
		return &gfuncmgr;
	}
	bool AddFunc(CCObject * obj, CCObject * parent, unsigned short event_type, std::string func_name);
	void uiwidget_pushdown_func(CCObject * obj);
	void uiwidget_move_func(CCObject * obj);
	void uiwidget_release_func(CCObject * obj);
};

#endif