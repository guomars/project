#pragma once

#include <string>
#include <cstring>
#include <cstdio>
#include <sstream>
#include <map>
#include <cstdio>
#include "support/tinyxml2/tinyxml2.h"
#include "cocos2d.h"
#include "CocoGUILIB/BaseClasses/UIWidget.h"
#include "GridSprite.h"
#include "GridEffect.h"

using namespace cocos2d;
USING_NS_CC_EXT;

namespace aeditor {
	//class FightConf;

	//extern void loadFightConf(const std::string& fileName);
	//extern FightConf* getFightConf();

	enum {
		EActionList_NULL = 0,
		EActionList_ONE = 1,
		EActionList_MULTI = 2,
	};

	class AEParamInner;

	class AEParamAmmend : public CCObject
	{
	public:
		std::map<int, std::string> strs;						// 修正的字符串, index from 1
		std::map<int, cocos2d::CCPoint> positions;				// 修正的坐标, index from 1
		std::map<std::string, CCNode*> sprites;					// 修正的精灵
		std::map<std::string, std::string> uiNameReplaced;		// 修正的精灵
		std::map<std::string, std::string> resReplaced;			// 修正的精灵资源
		float duration;											// 非零修正
		int condition;											// 条件
		std::string alignSpriteName;							// 子AE的时候，用于对齐的精灵

		AEParamInner* pParamInner;
		CCNode* performer;
		bool isPerformerAttacker;
		std::vector<CCNode*> targets;
	public:
		AEParamAmmend();

		~AEParamAmmend();

		static AEParamAmmend * create()
		{
			AEParamAmmend * pobj = new AEParamAmmend();
			if (pobj)
			{
				pobj->autorelease();
			}
			return pobj;
		}
		void AddPos(int index, CCPoint & pos)
		{
			positions[index] = pos;
		}
		void AddSprite(std::string str, CCNode* node)
		{
			if (!str.empty() && node)
				sprites[str] = node;
		}
	};

	class ActionParam {
		friend class ActionTemplate;
	public:
		ActionParam() : var_f(0), var_i(0) {};
	private:
		std::string name;
		std::string type;
		std::string note;

		// dynamic
		std::string var_str;
		std::list<std::string> var_strs;
		int var_i;
		float var_f;
		CCPoint var_point;
		ccBezierConfig var_Bezier;

		ActionParam(tinyxml2::XMLElement* e) : var_f(0), var_i(0) {
			this->name = e->Attribute("name");
			this->type = e->Attribute("type");
			this->note = e->Attribute("note");
		}

	public:
		static cocos2d::CCPoint GetPointParam(const char* var, tinyxml2::XMLElement* eConfig, AEParamAmmend* ammend) {
			assert(var != NULL);
			cocos2d::CCPoint ret;
			if (strlen(var) == 2) {
				if (strcmp(var, "P1") == 0) {
					if (ammend->positions.find(1) != ammend->positions.end()) {
						ret = ammend->positions[1];
					} else {
						sscanf(eConfig->Attribute("point1"), "(%f,%f)", &(ret.x), &(ret.y));
					}
				} else if (strcmp(var, "P2") == 0) {
					if (ammend->positions.find(2) != ammend->positions.end()) {
						ret = ammend->positions[2];
					} else {
						sscanf(eConfig->Attribute("point2"), "(%f,%f)", &(ret.x), &(ret.y));
					}
				} else if (strcmp(var, "P3") == 0) {
					if (ammend->positions.find(3) != ammend->positions.end()) {
						ret = ammend->positions[3];
					} else {
						sscanf(eConfig->Attribute("point3"), "(%f,%f)", &(ret.x), &(ret.y));
					}
				} else if (strcmp(var, "P4") == 0) {
					if (ammend->positions.find(4) != ammend->positions.end()) {
						ret = ammend->positions[4];
					} else {
						sscanf(eConfig->Attribute("point4"), "(%f,%f)", &(ret.x), &(ret.y));
					}
				} else if (strcmp(var, "P5") == 0) {
					if (ammend->positions.find(5) != ammend->positions.end()) {
						ret = ammend->positions[5];
					} else {
						sscanf(eConfig->Attribute("point5"), "(%f,%f)", &(ret.x), &(ret.y));
					}
				}
			} else {
				sscanf(var, "(%f,%f)", &(ret.x), &(ret.y));
			}
			return ret;
		}

		static std::string GetStringParam(const char* var, tinyxml2::XMLElement* eConfig, AEParamAmmend* ammend) {
			assert(var != NULL);
			std::string ret;
			if (strlen(var) == 2) {
				if (strcmp(var, "S1") == 0) {
					ret = ammend->strs.find(1) == ammend->strs.end() ? eConfig->Attribute("str1") : ammend->strs[1];
				} else if (strcmp(var, "S2") == 0) {
					ret = ammend->strs.find(2) == ammend->strs.end() ? eConfig->Attribute("str2") : ammend->strs[1];
				} else if (strcmp(var, "S3") == 0) {
					ret = ammend->strs.find(3) == ammend->strs.end() ? eConfig->Attribute("str3") : ammend->strs[2];
				} else if (strcmp(var, "S4") == 0) {
					ret = ammend->strs.find(4) == ammend->strs.end() ? eConfig->Attribute("str4") : ammend->strs[3];
				} else if (strcmp(var, "S5") == 0) {
					ret = ammend->strs.find(5) == ammend->strs.end() ? eConfig->Attribute("str5") : ammend->strs[4];
				}
			} else {
				ret = var;
			}
			return ret;
		}

	private:
		void SetVar(const char* var, tinyxml2::XMLElement* eConfig, AEParamAmmend* ammend) {
			if (type == "float") {
				sscanf(var, "%f", &var_f);
			} else if (type == "CCPoint") {
				var_point = GetPointParam(var, eConfig, ammend);
			} else if (type == "int") {
				sscanf(var, "%d", &var_i);
			} else if (type == "Bezier") {
				sscanf(var, "((%f,%f),(%f,%f),(%f,%f))", &(var_Bezier.endPosition.x), &(var_Bezier.endPosition.y), 
					&(var_Bezier.controlPoint_1.x), &(var_Bezier.controlPoint_1.y), 
					&(var_Bezier.controlPoint_2.x), &(var_Bezier.controlPoint_2.y));
			} else if (type == "str") {
				var_str = GetStringParam(var, eConfig, ammend);
			} else if (type == "strs") {
				std::string tmp = var;
				for (size_t i = 0, start = 0; i < tmp.size(); ++i) {
					if (tmp[i] == ',') {
						if (i != start) {
							var_strs.push_back(GetStringParam(tmp.substr(start, i - start).c_str(), eConfig, ammend));
						}
						start = i + 1;
					} else if (i == tmp.size() - 1) {
						if (i >= start) {
							var_strs.push_back(GetStringParam(tmp.substr(start, i + 1 - start).c_str(), eConfig, ammend));
						}
					}
				}
			} else {
				CCAssert(0, type.c_str());
			}
		}

		std::string toString() {
			std::stringstream ss;
			ss << "param_" << this->name << "=" << this->type;
			return ss.str();
		}
	};

	class ActionTemplateTable;
	class ActionTemplate {
	public:
		ActionTemplate() : eActionList(0) {};
	private:
		friend class ActionTemplateTable;

		std::string name;
		std::string type;
		std::string note;
		int eActionList;

		std::map<std::string, ActionParam> params;

		// dynamic
		std::vector<CCAction*> actionList;			// weak ptr

		std::string toString() {
			std::stringstream ss;
			ss << "[Action name=" << name << ", type=" << type << ", eActionList=" << eActionList;
			for (std::map<std::string, ActionParam>::iterator it = params.begin(); it != params.end(); ++it) {
				ss << ", " << it->second.toString();
			}
 			return ss.str();
		}

		ActionTemplate(tinyxml2::XMLElement* e) : eActionList(0) {
			this->name = e->Attribute("name");
			this->type = e->Attribute("type");
			this->note = e->Attribute("note");
			if (e->Attribute("actionList") != NULL) {
				eActionList = e->IntAttribute("actionList");
			} else {
				eActionList = EActionList_NULL;
			}

			for (tinyxml2::XMLElement* element = e->FirstChildElement("param"); element != NULL; element = element->NextSiblingElement("param")) {
				ActionParam param(element);
				params.insert(std::make_pair(param.name, param));
			}
		}

		bool HasParam(const std::string& param) {
			return params.find(param) != params.end();
		}

		ActionParam* GetActionParam(const std::string& param) {
			if (params.find(param) == params.end()) {
				std::string s;
				s += name;
				s += " not contain param name=";
				s + param;
				CCAssert(0, s.c_str());
			}

			return &params[param];
		}

		std::string GetStr(const std::string& param) {
			ActionParam* ap = GetActionParam(param);
			return ap->var_str;
		}

		float GetInt(const std::string& param) {
			ActionParam* ap = GetActionParam(param);
			return ap->var_i;
		}

		float GetFloat(const std::string& param) {
			ActionParam* ap = GetActionParam(param);
			return ap->var_f;
		}

		CCPoint GetCCPoint(const std::string& param) {
			ActionParam* ap = GetActionParam(param);
			return ap->var_point;
		}

		ccBezierConfig GetBezier(const std::string& param) {
			ActionParam* ap = GetActionParam(param);
			return ap->var_Bezier;
		}

		std::list<std::string> GetStrs(const std::string& param) {
			ActionParam* ap = GetActionParam(param);
			return ap->var_strs;
		}

		ActionTemplate create(const char* spriteName, tinyxml2::XMLElement* eAction, ActionTemplateTable& table, tinyxml2::XMLElement* eConfig, AEParamAmmend* ammend);
	};

	class ActionTemplateTable;

	class ActionSpriteHolder {
		friend class ActionTemplateTable;

	private:
		bool isForceRemove;
		bool isStartAnimation;
		float leftSecond;
		float speed;
		CCLabelTTF* pShowCurSecond;
		CCNode* container;				// weak ptr
		std::string nextAE;
		std::set<CCNode*> nodes;
		CCCallFunc* onActionDone;
		ActionTemplateTable* att;		// weak ptr
		std::list<std::pair<CCNode*, CCAction*> > actions;
		std::list<int> rtChildHandles;

	public:
		ActionSpriteHolder() : pShowCurSecond(NULL), onActionDone(NULL), speed(1), leftSecond(0), container(NULL), att(NULL), isForceRemove(false), isStartAnimation(false) {}

		~ActionSpriteHolder();

		CCCallFunc* GetOnActionDone() {
			return onActionDone;
		}

		void SetForceRemove() {
			this->leftSecond = 0;
			this->isForceRemove = true;
		}

		void SetAtt(ActionTemplateTable* att) {
			this->att = att;
		}

		void SetNextAE(const std::string& nextAE) {
			this->nextAE = nextAE;
		}

		void SetContainer(CCNode* container) {
			assert(this->container == NULL && container != NULL);

			this->container = container;
			this->container->retain();
		}

		CCNode* GetContainer() const {
			return this->container;
		}
		void SetOnActionDone(CCCallFunc* onActionDone) {
			onActionDone->retain();
			this->onActionDone = onActionDone;
		}

		void SetLeftSecond(float _leftSecond) {
			this->leftSecond = _leftSecond;
		}

		void SetSpeed(float _speed) {
			this->speed = _speed;
		}

		void AddNode(CCNode* node) {
			if (nodes.find(node) != nodes.end()) return;

			node->retain();
			nodes.insert(node);
		}

		void AddShowCurSecondTTF(CCLabelTTF* _pShowCurSecond) {
			AddNode(_pShowCurSecond);
			pShowCurSecond = _pShowCurSecond;
		}

		// return true for need delete
		bool Update(float delta);
	};

	class ActionTemplateTable : public CCNode {
		friend class ActionTemplate;
	private:
		std::map<std::string, ActionTemplate> stubTable;
		bool isDebug;
		bool isCreateDebugBackground;
		bool isUpdateScheduled;
		int seed;
		std::map<int, ActionSpriteHolder*> holders;
		std::map<std::string,int> tagMap; //sprite的tag与名字查找表，在整个ae内唯一
		float playSpeed;

	public:
		void setIsCreateDebugBackground(bool isCreateDebugBackground) { this->isCreateDebugBackground = isCreateDebugBackground; };

	public:
		static ActionTemplateTable instance;

		std::string ToString() {
			std::stringstream ss;
			for (std::map<std::string, ActionTemplate>::iterator it = stubTable.begin(); it != stubTable.end(); ++it) {
				ss << it->second.toString() << std::endl;
			}
			return ss.str();
		}

		~ActionTemplateTable() {
			for (std::map<int, ActionSpriteHolder*>::iterator it = holders.begin(); it != holders.end(); ++it) {
				delete it->second;
			}
		}

	private:
		ActionTemplateTable() : isDebug(false), isCreateDebugBackground(true), seed(0), isUpdateScheduled(false), playSpeed(1) {}

		int NextSeed() {
			++seed;
			if (seed < 0) {
				seed = 1;
			}
			return seed;
		}

	public:
		CCAction* CreateAction(const char* spriteName, tinyxml2::XMLElement* eAction, tinyxml2::XMLElement* eConfig, AEParamAmmend* ammend);

		CCSpawn* extractAction(const std::string& fileName, std::string spriteName) {
			AEParamAmmend ammend;
			return extractAction(fileName, spriteName, ammend, true);
		}

		// 获取指定aeFile中的，指定精灵上的动作
		CCSpawn* extractAction(const std::string& fileName, std::string spriteName, AEParamAmmend& ammend, bool isUseCache = false);

		CCNode* addAEToNode(const std::string& fileName, float delay = 0.0f) {
			std::map<std::string, std::string> resReplace;
			CCNode* ret = addAEToNode(fileName, "", 1.0f, resReplace, delay);
			CCNode* xxx = CCNode::create();
			ret->setPosition(-384, -512);	// 设计分辨率
			xxx->addChild(ret);
			return xxx;
		}

		// 指定aeFile挂到Node上
		CCNode* addAEToNode(const std::string& fileName, std::string alignSpriteName, float scale, const std::map<std::string, std::string>& resReplace, float delay = 0.0f);

	public:
		//const char* templateXmlFile = "./Editor/template.xml";
		//tinyxml2::XMLDocument doc;
		//doc.LoadFile(templateXmlFile);
		//aeditor::ActionTemplateTable::instance.Init(doc.RootElement(), scene, true);
		static ActionTemplateTable* create(const std::string& fileName, CCScene* pScene, bool _isDebug = false) {
			ActionTemplateTable* ret = new ActionTemplateTable();
			ret->Init(fileName, pScene, _isDebug);
			ret->autorelease();
			return ret;
		}

		void SetPlaySpeed(int playSpeed) {
			this->playSpeed = playSpeed;
		}

		int GetPlaySpeed() {
			return this->playSpeed;
		}

		void Init(const std::string& fileName, CCScene* pScene, bool _isDebug = false) {
			unsigned long size;
			unsigned char* pData = CCFileUtils::sharedFileUtils()->getFileData(fileName.c_str(), "rb", &size);
			tinyxml2::XMLDocument doc;
			char* szBuff = new char[size + 1];
			szBuff[size] = 0;
			memcpy(szBuff, pData, size);
			delete[] pData;

			doc.ParseDeep(szBuff, 0 );
			CCAssert(!doc.Error(), "Read AE Tempalte File Failed !!!!");

			Init(doc.RootElement(), pScene, _isDebug);
		}

		void Init(tinyxml2::XMLElement* e, CCScene* pScene, bool _isDebug = false) {
			assert(pScene != NULL);

			stubTable.clear();
			ClearAllHolders();
			this->removeFromParentAndCleanup(false);

			this->isDebug = _isDebug;
			for (tinyxml2::XMLElement* element = e->FirstChildElement("action"); element != NULL; element = element->NextSiblingElement("action")) {
				ActionTemplate actionTemplate(element);
				stubTable.insert(std::make_pair(actionTemplate.name, actionTemplate));
			}

			this->setVisible(false);
			pScene->addChild(this);
			if (!isUpdateScheduled) {
				this->scheduleUpdate();
				this->isUpdateScheduled = true;
			}
		}
	public:
		void ClearAllHolders() {
			for (std::map<int, ActionSpriteHolder*>::iterator it = holders.begin(); it != holders.end();) {
				delete it->second;
			}
			holders.clear();
		}
		
		virtual void update(float delta) {
			std::map<int, ActionSpriteHolder*> mapSwap;
			for (std::map<int, ActionSpriteHolder*>::iterator it = holders.begin(); it != holders.end();++it) {
				if (it->second->Update(delta)) {
					delete it->second;
					//it = holders.erase(it);
				} else {
					mapSwap.insert(std::make_pair(it->first, it->second));
					//++it;
				}
			}

			holders.swap(mapSwap);
		}

		// 通过句柄删掉
		bool RemoveByHandle(int handle) {
			CCCallFunc* onActionDone = NULL;
			return RemoveByHandle(handle, onActionDone);
		}

		bool RemoveByHandle(int handle, CCCallFunc*& onActionDone) {
			if (holders.find(handle) == holders.end()) return false;

			ActionSpriteHolder* pHolder = holders[handle];
			onActionDone = pHolder->GetOnActionDone();
			pHolder->SetForceRemove();
			return true;
		}

		// replace sprite
		// @return: handle 0表示失败
		int RunAeAction(CCNode* container, AEParamAmmend& ammend, tinyxml2::XMLElement* eAction, CCCallFunc* onActionBefore = NULL, CCCallFunc* onActionDone = NULL);

		// replace sprite
		// @return: handle 0表示失败
		int RunAeAction(CCNode* container, AEParamAmmend& ammend, const std::string& fileName, CCCallFunc* onActionBefore = NULL, CCCallFunc* onActionDone = NULL);

		int RunAeAction(CCNode* container, std::map<std::string, CCNode*> sprites, tinyxml2::XMLElement* eAction, CCCallFunc* onActionBefore = NULL, CCCallFunc* onActionDone = NULL);

		int RunAeAction(CCNode* container, std::map<std::string, CCNode*> sprites, const std::string& fileName, CCCallFunc* onActionBefore = NULL, CCCallFunc* onActionDone = NULL);

		// @return: handle 0表示失败
		int RunAeAction(CCNode* container, const std::string& fileName, CCCallFunc* onActionBefore = NULL, CCCallFunc* onActionDone = NULL);

		void RunUIAction(const std::string& fileName, UIWidget* uiWidget);

		// 运行UI Action, *.ue  ammend设置参数
		void RunUIAction(const std::string& fileName, UIWidget* uiWidget, AEParamAmmend& ammend);

		// ae, se, ue 等xml文件是否进入缓存
		void ClearXmlFileCache();

		// 返回技能时间
		float RunSkillAction(const std::string& fileName, CCLayer* battleLayer, CCCallFunc* onActionDone = NULL);

		// 运行Skill Action, *.se  ammend设置参数
		float RunSkillAction(const std::string& fileName, CCLayer* battleLayer, AEParamAmmend& ammend, CCCallFunc* onActionDone = NULL);

		//给lua用的接口
		int RunAeActionWithParam(CCNode* container, const std::string& fileName, AEParamAmmend* ammend, CCCallFunc* onActionBefore = NULL, CCCallFunc* onActionDone = NULL)
		{
			return RunAeAction(container,*ammend,fileName,onActionBefore,onActionDone);
		}
		CCSprite* GetSpriteByName(CCNode* container, const std::string& spriteName)
		{
			std::map<std::string,int>::const_iterator it = tagMap.find(spriteName);
			if(it != tagMap.end())
			{
				return dynamic_cast<CCSprite*>(container->getChildByTag(it->second));
			}
			else
				return NULL;
		}
	};
}