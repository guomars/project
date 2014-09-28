#include "GFuncMgr.h"
#include "DataMgr.h"
#include "UIWidget.h"

using namespace cocos2d;

UidFuncMapType uid_func_map;

bool GFuncMgr::AddFunc(CCObject * obj, CCObject * parent, unsigned short event_type, std::string func_name)
{
	if (!obj || event_type <= EVENT_BEGIN || event_type >= EVENT_END || func_name.empty() || func_name.size() > 80)
		return false;

	cocos2d::extension::UIWidget * pobj = dynamic_cast<cocos2d::extension::UIWidget *>(obj);
	if (!pobj)
		return false;

	switch (event_type)
	{
	case EVENT_UIWIDGET_PUSH_DOWN:
		{
			pobj->setTouchEnable(true);
			pobj->addPushDownEvent(parent, coco_releaseselector(GFuncMgr::uiwidget_pushdown_func));
		}
		break;
	case EVENT_UIWIDGET_MOVE:
		{
			pobj->setTouchEnable(true);
			pobj->addMoveEvent(parent, coco_releaseselector(GFuncMgr::uiwidget_move_func));
		}
		break;
	case EVENT_UIWIDGET_RELEASE:
		{
			pobj->setTouchEnable(true);
			pobj->addReleaseEvent(parent, coco_releaseselector(GFuncMgr::uiwidget_release_func));
		}
		break;
	default:
		return false;
	}

	if (uid_func_map.find(obj->m_uID) == uid_func_map.end())
	{
		SubUidFuncMapType sub_uid_func_map;
		sub_uid_func_map[event_type] = func_name;
		uid_func_map[obj->m_uID] = sub_uid_func_map;
	}
	else
	{
		if (uid_func_map[obj->m_uID].find(event_type) != uid_func_map[obj->m_uID].end())
			return false;

		uid_func_map[obj->m_uID][event_type] = func_name;
	}
	return true;
}

void GFuncMgr::uiwidget_pushdown_func(CCObject * obj)
{
	if (uid_func_map.find(obj->m_uID) == uid_func_map.end())
	{
		CCLog("GFuncMgr::uiwidget_pushdown_func cant find uid=%d",obj->m_uID);
		return;
	}
	if (uid_func_map[obj->m_uID].find(EVENT_UIWIDGET_PUSH_DOWN) == uid_func_map[obj->m_uID].end())
	{
		CCLog("GFuncMgr::uiwidget_pushdown_func cant find event. uid=%d,menuclick=%s",obj->m_uID,uid_func_map[obj->m_uID][EVENT_UIWIDGET_PUSH_DOWN].c_str());
		return;
	}
	//CCLog("GFuncMgr::uiwidget_pushdown_func muid=%d,menuclick=%s",obj->m_uID,uid_func_map[obj->m_uID][EVENT_UIWIDGET_PUSH_DOWN].c_str());

	char tmp[100];
	memset(tmp,0,100);
	sprintf(tmp,"%s(%d)",uid_func_map[obj->m_uID][EVENT_UIWIDGET_PUSH_DOWN].c_str(),obj->m_uID);
	CCLuaEngine* pEngine1 = CCLuaEngine::defaultEngine();

	pEngine1->executeString(tmp);
}

void GFuncMgr::uiwidget_move_func(CCObject * obj)
{
	if (uid_func_map.find(obj->m_uID) == uid_func_map.end())
	{
		CCLog("GFuncMgr::uiwidget_move_func cant find uid=%d",obj->m_uID);
		return;
	}
	if (uid_func_map[obj->m_uID].find(EVENT_UIWIDGET_MOVE) == uid_func_map[obj->m_uID].end())
	{
		CCLog("GFuncMgr::uiwidget_move_func cant find event. uid=%d,menuclick=%s",obj->m_uID,uid_func_map[obj->m_uID][EVENT_UIWIDGET_MOVE].c_str());
		return;
	}
	//CCLog("GFuncMgr::uiwidget_move_func muid=%d,menuclick=%s",obj->m_uID,uid_func_map[obj->m_uID][EVENT_UIWIDGET_MOVE].c_str());

	cocos2d::extension::UIWidget * pobj = dynamic_cast<cocos2d::extension::UIWidget *>(obj);
	if (!pobj)
	{
		CCLog("GFuncMgr::uiwidget_move_func wrong object.");
		return;
	}

	CCPoint movePoint = pobj->getTouchMovePos();

	char tmp[100];
	memset(tmp,0,100);
	sprintf(tmp,"%s(%d,%f,%f)",uid_func_map[obj->m_uID][EVENT_UIWIDGET_MOVE].c_str(),obj->m_uID,movePoint.x, movePoint.y);
	CCLuaEngine* pEngine1 = CCLuaEngine::defaultEngine();

	pEngine1->executeString(tmp);
}

void GFuncMgr::uiwidget_release_func(CCObject * obj)
{
	if (uid_func_map.find(obj->m_uID) == uid_func_map.end())
	{
		CCLog("GFuncMgr::uiwidget_release_func cant find uid=%d",obj->m_uID);
		return;
	}
	if (uid_func_map[obj->m_uID].find(EVENT_UIWIDGET_RELEASE) == uid_func_map[obj->m_uID].end())
	{
		CCLog("GFuncMgr::uiwidget_release_func cant find event. uid=%d,menuclick=%s",obj->m_uID,uid_func_map[obj->m_uID][EVENT_UIWIDGET_RELEASE].c_str());
		return;
	}
	//CCLog("GFuncMgr::uiwidget_release_func muid=%d,menuclick=%s",obj->m_uID,uid_func_map[obj->m_uID][EVENT_UIWIDGET_RELEASE].c_str());

	char tmp[100];
	memset(tmp,0,100);
	sprintf(tmp,"%s(%d)",uid_func_map[obj->m_uID][EVENT_UIWIDGET_RELEASE].c_str(),obj->m_uID);
	CCLuaEngine* pEngine1 = CCLuaEngine::defaultEngine();

	pEngine1->executeString(tmp);
}