#include "ActionStubs.h"
#include "AEAction.h"
//#include "FightConf.h"
#include <set>
#include "cocos2d.h"
#include "GridSprite.h"
#include "CCShake.h"
#include "CocoGUILIB/System/CocosGUI.h"

static char s_szBuff[256];

// win32下弹出对话框
static void MessageHint(bool cond, const std::string& msg, const std::string& hint)
{
#ifdef WIN32
	if (!cond) {
		sprintf(s_szBuff, "%s, hint=\"%s\"", msg.c_str(), hint.c_str());
		int ret = ::MessageBoxA(GetActiveWindow(), s_szBuff, "error", MB_ABORTRETRYIGNORE);
		if(ret != IDIGNORE)
			assert(cond && "void MessageHint(bool cond,const std::string& msg)");
	}
#endif
}

// UIWidget initPos, 存到这里，不释放了，没多少内存
std::map<std::string, CCPoint> g_uiNameToOriginalPos;
std::map<std::string, ccFontDefinition> g_fontStroke;
bool g_ae_isSoundOn = true;

// 性能分析
static cc_timeval s_last_time_for_effect;
static float CalcCostMS(char* str = "") {
	assert(str != NULL);
	cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now, NULL);
	float deltaMS = CCTime::timersubCocos2d(&s_last_time_for_effect, &now);
	s_last_time_for_effect = now;
	if (strlen(str) > 0) {
		CCLog("[CostMS] %s ---- %f second", str, deltaMS / 1000.0);
	}
	return deltaMS;
}

namespace aeditor {
	class AEParamAmmend;
	class AEParamInner {
		friend class AEParamAmmend;

	public:
		float init_delay;										// 内部使用
		UIWidget* uiJasonRoot;									// 内部使用，不要随便设置
		GridEffectSprite* gridEffectSprite;						// 内部使用，不要随便设置
		bool isSubAE;											// 内部使用，不要随便设置
		CCPoint alignSpritePos;									// 内部使用，不要随便设置
		std::map<std::string, CCPoint> dynamicNode2TargetPos;	// 动态精灵追踪的目标位置

		AEParamInner() : uiJasonRoot(0), gridEffectSprite(0), isSubAE(false), init_delay(0.0f) {

		}
	};

	//FightConf* s_fightConf = 0;

	/*void loadFightConf(const std::string& fileName) {
		unsigned long size;
		unsigned char* pData = CCFileUtils::sharedFileUtils()->getFileData(fileName.c_str(), "rb", &size);
		MessageHint(pData != NULL, "not found fightConf", fileName);
		tinyxml2::XMLDocument doc;
		char* szBuff = new char[size + 1];
		szBuff[size] = 0;
		memcpy(szBuff, pData, size);
		delete[] pData;
		doc.ParseDeep(szBuff, 0 );

		s_fightConf = new FightConf(doc.RootElement());

		delete[] szBuff;
	}

	FightConf* getFightConf() {
		CCAssert(s_fightConf, "not load fightConfFile");
		return s_fightConf;
	}*/

	AEParamAmmend::AEParamAmmend() : duration(0), condition(0), pParamInner(0), performer(NULL), isPerformerAttacker(true)
	{
		pParamInner = new AEParamInner;
	}

	AEParamAmmend::~AEParamAmmend()
	{
		CC_SAFE_DELETE(pParamInner);
	}

};

ccFontDefinition getFontDefinition(const std::string& fontXmlPath) {
	std::map<std::string, ccFontDefinition>::iterator it = g_fontStroke.find(fontXmlPath);
	if (it != g_fontStroke.end()) {
		return it->second;
	} else {
		unsigned long size;
		unsigned char* pData = CCFileUtils::sharedFileUtils()->getFileData(fontXmlPath.c_str(), "rb", &size);
		CCAssert(pData != NULL, fontXmlPath.c_str());
		tinyxml2::XMLDocument doc;
		char* szBuff = new char[size + 1];
		szBuff[size] = 0;
		memcpy(szBuff, pData, size);
		delete[] pData;

		doc.ParseDeep(szBuff, 0 );

		float testDelaySecond = 0;
		tinyxml2::XMLElement* eFont = doc.RootElement();
		ccFontDefinition fontDef;
		fontDef.m_fontName = eFont->Attribute("name");
		fontDef.m_fontSize = eFont->IntAttribute("size");
		if (eFont->Attribute("fillColor") != NULL && strlen(eFont->Attribute("fillColor")) > 0) {
			const char* fillColorStr = eFont->Attribute("fillColor");
			int r,g,b = 255;
			sscanf(fillColorStr, "(%d,%d,%d)", &r, &g, &b);
			fontDef.m_fontFillColor = ccc3(r, g, b);
		}

		tinyxml2::XMLElement* eShadow = eFont->FirstChildElement("shadow");
		if (eShadow != NULL && eShadow->Attribute("enable") != NULL && strcmp(eShadow->Attribute("enable"), "true") == 0) { // 开启阴影
			fontDef.m_shadow.m_shadowEnabled = true;
			if (eShadow->Attribute("offset") != NULL && strlen(eShadow->Attribute("offset")) > 0) {
				const char* offsetStr = eShadow->Attribute("offset");
				float x,y = 0;
				sscanf(offsetStr, "(%f,%f)", &x, &y);
				fontDef.m_shadow.m_shadowOffset = ccp(x, y);
			}
			if (eShadow->Attribute("blur") != NULL && strlen(eShadow->Attribute("blur")) > 0) {
				fontDef.m_shadow.m_shadowBlur = eShadow->FloatAttribute("blur");
			}
			if (eShadow->Attribute("opacity") != NULL && strlen(eShadow->Attribute("opacity")) > 0) {
				fontDef.m_shadow.m_shadowOpacity = eShadow->FloatAttribute("opacity");
			}
		}
		tinyxml2::XMLElement* eStroke = eFont->FirstChildElement("stroke");
		if (eStroke != NULL && eStroke->Attribute("enable") != NULL && strcmp(eStroke->Attribute("enable"), "true") == 0) { // 开启描边
			fontDef.m_stroke.m_strokeEnabled = true;
			if (eStroke->Attribute("color") != NULL && strlen(eStroke->Attribute("color")) > 0) {
				int r,g,b = 0;
				sscanf(eStroke->Attribute("color"), "(%d,%d,%d)", &r, &g, &b);
				fontDef.m_stroke.m_strokeColor = ccc3(r, g, b);
			}
			if (eStroke->Attribute("size") != NULL && strlen(eStroke->Attribute("size")) > 0) {
				fontDef.m_stroke.m_strokeSize = eStroke->FloatAttribute("size");
			}
		}

		delete[] szBuff;

		g_fontStroke[fontXmlPath] = fontDef;
		return fontDef;
	}
}

namespace aeditor {
	static int transGLBlendFactor(const char* src, int blendFactor) {
		if (src == NULL || strlen(src) == 0) return blendFactor;

		if (strcmp(src, "GL_ZERO") == 0) blendFactor = GL_ZERO;
		else if (strcmp(src, "GL_ONE") == 0) blendFactor = GL_ONE;
		else if (strcmp(src, "GL_SRC_COLOR") == 0) blendFactor = GL_SRC_COLOR;
		else if (strcmp(src, "GL_ONE_MINUS_SRC_COLOR") == 0) blendFactor = GL_ONE_MINUS_SRC_COLOR;
		else if (strcmp(src, "GL_SRC_ALPHA") == 0) blendFactor = GL_SRC_ALPHA;
		else if (strcmp(src, "GL_ONE_MINUS_SRC_ALPHA") == 0) blendFactor = GL_ONE_MINUS_SRC_ALPHA;
		else if (strcmp(src, "GL_DST_ALPHA") == 0) blendFactor = GL_DST_ALPHA;
		else if (strcmp(src, "GL_ONE_MINUS_DST_ALPHA") == 0) blendFactor = GL_ONE_MINUS_DST_ALPHA;
		else if (strcmp(src, "GL_DST_COLOR") == 0) blendFactor = GL_DST_COLOR;
		else if (strcmp(src, "GL_ONE_MINUS_DST_COLOR") == 0) blendFactor = GL_ONE_MINUS_DST_COLOR;
		else if (strcmp(src, "GL_SRC_ALPHA_SATURATE") == 0) blendFactor = GL_SRC_ALPHA_SATURATE;

		return blendFactor;
	}

	class AEButtonHandler : public CCNode {
	private:
		ActionTemplateTable* att;		// weak ptr
		CCNode* container;				// weak ptr
		int closeHandle;
		std::string newAEFileName;

	public:
		AEButtonHandler(): att(NULL), closeHandle(0), container(NULL) {}

	public:
		static AEButtonHandler* create(ActionTemplateTable* _att, CCNode* _container, int _closeHandle, const std::string& _newAEFileName)
		{ 
			AEButtonHandler* ret = new AEButtonHandler;
			ret->att = _att; 
			ret->container = _container;
			ret->closeHandle = _closeHandle;
			ret->newAEFileName = _newAEFileName;

			ret->autorelease();
			return ret;
		}

		void handle(CCObject* n) {
			CC_UNUSED_PARAM(n);
			CCCallFunc* onActionDone = NULL;
			if (closeHandle != 0) {
				att->RemoveByHandle(closeHandle, onActionDone);
			}
			if (newAEFileName.length() != 0) {
				att->RunAeAction(container, newAEFileName, NULL, onActionDone);
			} else {
				if(onActionDone)
					onActionDone->execute();
			}
		}
	};

	class RenderTargetRotateSprite : public CCSprite {
#define __RTRS_SCALE_RATE 1.0f

		CCNode* m_original;
		float m_rotated;
		float m_rotate_speed;
		CCPoint m_rtSize;
		CCPoint m_center;
		CCPoint m_region;
		CCRenderTexture* m_rt;

		RenderTargetRotateSprite(): m_rotated(0), m_rotate_speed(0), m_original(NULL), m_rt(NULL) {}

	public:

		static RenderTargetRotateSprite* create(CCNode* originalSprite, float rotate_speed) {
			return create(originalSprite, rotate_speed, originalSprite->getContentSize(), 
				ccp(originalSprite->getContentSize().width / 2, originalSprite->getContentSize().height / 2), originalSprite->getContentSize());
		}

		static RenderTargetRotateSprite* create(CCNode* originalSprite, float rotate_speed, const CCPoint& rtSize, const CCPoint& center, const CCPoint& region) {
			RenderTargetRotateSprite* ret = new RenderTargetRotateSprite();
			if (ret == NULL) return NULL;

			ret->init(originalSprite, rotate_speed, rtSize, center, region);
			ret->autorelease();
			return ret;
		}

		virtual ~RenderTargetRotateSprite() {
			CC_SAFE_RELEASE(m_original);
			CC_SAFE_RELEASE(m_rt);
		}

		void init(CCNode* original, float rotate_speed, const CCPoint& rtSize, const CCPoint& center, const CCPoint& region) {
			CCSprite::init();

			this->m_rt = CCRenderTexture::create(rtSize.x * __RTRS_SCALE_RATE, rtSize.y * __RTRS_SCALE_RATE);
			this->m_original = original;
			this->m_rotate_speed = rotate_speed;
			this->m_rtSize = rtSize;
			this->m_center = center;
			this->m_region = region;

			this->m_original->retain();
			this->m_rt->retain();

			this->m_original->setAnchorPoint(ccp(0.5f, 0.5f));
			this->m_original->setScaleX(rtSize.x / region.x);
			this->m_original->setScaleY(rtSize.y / region.y);
			this->m_rt->getSprite()->setPosition(ccp(
				(rtSize.x / 2) * __RTRS_SCALE_RATE,
				(rtSize.y / 2) * __RTRS_SCALE_RATE));
			this->addChild(m_original);

			this->scheduleUpdate();
		}

		virtual void visit()
		{
			// quick return if not visible. children won't be drawn.
			if (!m_bVisible)
			{
				return;
			}

			kmGLPushMatrix();

			if (m_pGrid && m_pGrid->isActive())
			{
				m_pGrid->beforeDraw();
			}

			this->transform();

			// not draw children
			{
				setTexture(m_rt->getSprite()->getTexture());
				CCRect rect = CCRectMake(0, 0, m_rtSize.x * __RTRS_SCALE_RATE, m_rtSize.y * __RTRS_SCALE_RATE);
				setTextureRect(rect);

				m_rt->getSprite()->getTexture()->setAntiAliasTexParameters();
				m_rt->getSprite()->transform();
				this->draw();
			}

			if (m_pGrid && m_pGrid->isActive())
			{
				m_pGrid->afterDraw(this);
			}

			kmGLPopMatrix();
		}

		virtual void update(float dt) {
			m_original->update(dt);

			this->m_rotated += (m_rotate_speed * dt);
			if (this->m_rotated < 0) {
				this->m_rotated += 360;
			}

			this->m_original->setRotation(m_rotated);

			m_rt->beginWithClear(0, 0, 0, 0);
			m_original->setPosition(ccp(
				(m_original->getContentSize().width / 2 + m_region.x / 2 - m_center.x) * m_rtSize.x / m_region.x * __RTRS_SCALE_RATE,
				(m_original->getContentSize().height / 2 + m_region.x / 2 - m_center.y) * m_rtSize.y / m_region.y * __RTRS_SCALE_RATE
				));
			m_original->visit();
			m_rt->end();
		}
	};

	ActionSpriteHolder::~ActionSpriteHolder() {
		CC_SAFE_RELEASE(this->container);
		for (std::list<int>::iterator it = rtChildHandles.begin(); it != rtChildHandles.end(); ++it) {
			att->RemoveByHandle(*it);
		}
		for (std::set<CCNode*>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
			(*it)->removeFromParentAndCleanup(true);
			(*it)->release();
		}
		for (std::list<std::pair<CCNode*, CCAction*> >::iterator it = actions.begin(); it != actions.end(); ++it) {
			CC_SAFE_RELEASE(it->first);
			CC_SAFE_RELEASE(it->second);
		}
		CC_SAFE_RELEASE(onActionDone);
	}

	bool ActionSpriteHolder::Update(float delta) {
		if (!isStartAnimation) {
			isStartAnimation = true;
			for (std::list<std::pair<CCNode*, CCAction*> >::iterator it = actions.begin(); it != actions.end(); ++it) {
				it->first->runAction(it->second);
				CC_SAFE_RELEASE(it->first);
				CC_SAFE_RELEASE(it->second);
			}
			actions.clear();
			leftSecond -= 0.02f;
			return false;
		}

		if (leftSecond < 0) { // remove in next frame
			return true;
		}

		leftSecond -= delta * speed;

		if (leftSecond < 0) {
			if (!isForceRemove) {
				if (nextAE.size() != 0) {
					att->RunAeAction(container, nextAE, onActionDone);
				} else if (onActionDone != NULL) {
					onActionDone->execute();
				}
			}
		}

		char szTmp[256];

		if (pShowCurSecond != NULL) {
			snprintf(szTmp, sizeof(szTmp), "Cur Second =  %.1f", leftSecond);
			pShowCurSecond->setString(szTmp);
		}
		return false;
	}

	ActionTemplate ActionTemplate::create(const char* spriteName, tinyxml2::XMLElement* eAction, ActionTemplateTable& table, tinyxml2::XMLElement* eConfig, AEParamAmmend* ammend) {
		if (strcmp(eAction->Attribute("name"), name.c_str()) != 0) {
			std::string s;
			s += eAction->Attribute("name");
			s += "!=";
			s += name;
			CCAssert(0, s.c_str());
		}

		ActionTemplate ret = *this;
		for (std::map<std::string, ActionParam>::iterator it = ret.params.begin(); it != ret.params.end(); ++it) {
			if (eAction->Attribute(it->first.c_str()) != NULL) {
				it->second.SetVar(eAction->Attribute(it->first.c_str()), eConfig, ammend);
			}
		}
		if (eActionList >= 1) {
			for (tinyxml2::XMLElement* element = eAction->FirstChildElement("action"); element != NULL; element = element->NextSiblingElement("action")) {
				CCAction* subAction = table.CreateAction(spriteName, element, eConfig, ammend);
				if (subAction != NULL) {
					ret.actionList.push_back(subAction);
				}
			}
		}

		if (eActionList > 1) {
			CCAssert(ret.actionList.size() >= 1, name.c_str());
		} else if (eActionList == 1) {
			CCAssert(ret.actionList.size() == 1, name.c_str());
		} else {
			CCAssert(ret.actionList.size() == 0, name.c_str());
		}
		return ret;
	}

	ActionTemplateTable ActionTemplateTable::instance;

	CCAction* ActionTemplateTable::CreateAction(const char* spriteName, tinyxml2::XMLElement* eAction, tinyxml2::XMLElement* eConfig, AEParamAmmend* ammend) {
		std::string actionName = eAction->Attribute("name");
		if (stubTable.find(actionName) == stubTable.end()) {
			return NULL;
		}

		ActionTemplate aa = stubTable[actionName].create(spriteName, eAction, *this, eConfig, ammend);
		CCAction* ret = NULL;
		// 0. Condition
		if (actionName == "AE_Condition") {
			bool isMeet = false;
			int paramCond = aa.GetInt("conditionParam");
			std::string strCond = aa.GetStr("conditionType");
			if (strCond == "EQUAL" && paramCond == ammend->condition) {
				isMeet = true;
			} else if (strCond == "GREAT_EQUAL" && paramCond >= ammend->condition) {
				isMeet = true;
			} else if (strCond == "GREAT" && paramCond > ammend->condition) {
				isMeet = true;
			} else if (strCond == "LESS_EQUAL" && paramCond <= ammend->condition) {
				isMeet = true;
			} else if (strCond == "LESS" && paramCond < ammend->condition) {
				isMeet = true;
			}

			if (isMeet && aa.actionList.size() > 0) {
				return *aa.actionList.begin();
			} else { // no effect
				ret = AE_Scale::create(1.0f);
			}
		}

		// Shader
		else if (actionName == "AE_ChangeShader") {
			std::string shaderName = aa.GetStr("shaderName");
			ret = AE_ChangeShader::create(shaderName.c_str());
		}
		else if (actionName == "AE_FadeShaderParams1f") {
			std::string shaderName = aa.GetStr("shaderName");
			char szBuff[64];
			ShaderParams1ffMap params;
			for (int i = 1; i <= 3; ++i) {
				sprintf(szBuff, "paramName%d", i);
				std::string paramName = szBuff;
				if (aa.GetStr(paramName) == "") continue;

				sprintf(szBuff, "paramStartValue%d", i);
				std::string paramStartValue = szBuff;
				sprintf(szBuff, "paramEndValue%d", i);
				std::string paramEndValue = szBuff;
				ShaderParams1f xxx;
				xxx.from = aa.GetFloat(paramStartValue);
				xxx.to = aa.GetFloat(paramEndValue);

				params[aa.GetStr(paramName)] = xxx;
			}
			ret = AE_FadeShaderParams1f::create(shaderName.c_str(), params, aa.GetFloat("duration"));
		}

		// 1. Sequence And CCSpawn
		else if (actionName == "CCSequence") {
			CCArray array;
			for (std::vector<CCAction*>::iterator it = aa.actionList.begin(); it != aa.actionList.end(); ++it) {
				array.addObject(*it);
			}
			ret = CCSequence::create(&array);
		} else if (actionName == "CCSpawn") {
			CCArray array;
			for (std::vector<CCAction*>::iterator it = aa.actionList.begin(); it != aa.actionList.end(); ++it) {
				array.addObject(*it);
			}
			ret = CCSpawn::create(&array);
		}
		// 2. CCActionInstant[Ignored: CCRemoveSelf]
		else if (actionName == "CCShow") {
			ret = CCShow::create();
		} else if (actionName == "CCHide") {
			ret = CCHide::create();
		} else if (actionName == "CCToggleVisibility") {
			ret = CCToggleVisibility::create();
		} else if (actionName == "CCFlipX") {
			ret = CCFlipX::create(aa.GetInt("x") > 0);
		} else if (actionName == "CCFlipY") {
			ret = CCFlipY::create(aa.GetInt("y") > 0);
		} else if (actionName == "CCPlace") {
			ret = CCPlace::create(aa.GetCCPoint("position"));
		} else if (actionName == "CCRemoveSelf") {
			ret = CCRemoveSelf::create(true);
		} else if (actionName == "AE_SetData") {
			ret = AE_SetData::create(aa.GetStr("key"),aa.GetStr("value"));
		} else if (actionName == "AE_ZOrder") {
			ret = AE_ZOrder::create(aa.GetInt("zOrder"));
		} else if (actionName == "AE_PlayWav") {
			ret = AE_PlayWav::create(aa.GetStr("wavFile"));
		} else if (actionName == "AE_Scale") {
			ret = AE_Scale::create(aa.GetFloat("scale"));
		} else if (actionName == "AE_FaceToPos") {
			ret = AE_FaceToPos::create(aa.GetCCPoint("faceToPos"), aa.GetFloat("initDegree"), aa.GetFloat("duration"));
		} else if (actionName == "AE_FightGoToTarget") {
			if (ammend->pParamInner->dynamicNode2TargetPos.find(spriteName) != ammend->pParamInner->dynamicNode2TargetPos.end()) {
				CCPoint delta = aa.GetCCPoint("position");
				CCPoint pos = ammend->pParamInner->dynamicNode2TargetPos[spriteName];
				pos.x += delta.x;
				pos.y += delta.y;
				ret = CCMoveTo::create(aa.GetFloat("duration"), pos);
			} else { // 忽略错误
				ret = CCDelayTime::create(aa.GetFloat("duration"));
			}
		} else if (actionName == "AE_Particle_Plist") {
			if (aa.GetStr("plist") != "") {
				ret = AE_Particle_Plist::create(aa.GetStr("plist"), (aa.HasParam("scale") ? aa.GetFloat("scale") : 1), aa.GetCCPoint("pos"), aa.GetInt("zOrder"), aa.GetInt("tag"),kCCPositionTypeFree, 0.0f);
			} else {
				ret = CCDelayTime::create(0);
			}
		} else if (actionName == "AE_Particle_Sys") {
			if (aa.GetStr("res") != "" && aa.GetStr("sysname") != "") {
				ret = AE_Particle_Sys::create(aa.GetStr("sysname"), aa.GetStr("res"), aa.GetInt("number"), (aa.HasParam("scale") ? aa.GetFloat("scale") : 1), aa.GetCCPoint("pos"), aa.GetInt("zOrder"), aa.GetInt("tag"));
			} else {
				ret = CCDelayTime::create(0);
			}
		} else if (actionName == "AE_Add_Label") {
			ret = AE_Add_Label::create(aa.GetCCPoint("pos"), aa.GetStr("label"), aa.GetStr("fontDefFile"), aa.GetStr("font"), aa.GetFloat("fontSize"), ccc3(aa.GetInt("r"), aa.GetInt("g"), aa.GetInt("b")), aa.GetFloat("duration"), 
				transGLBlendFactor(aa.GetStr("srcBlendFactor").c_str(), GL_ONE), transGLBlendFactor(aa.GetStr("dstBlendFactor").c_str(), GL_ONE_MINUS_SRC_ALPHA),
				aa.GetInt("tag"));
		} else if (actionName == "AE_Remove_Child") {
			ret = AE_Remove_Child::create(aa.GetInt("tag"));
		} else if (actionName == "AE_ChildAnimation") {
			ret = AE_ChildAnimation::create(aa.GetStrs("fileNames"), aa.GetStr("prefix"), aa.GetInt("prefixNum"), aa.GetStr("plist"),
						aa.GetFloat("delayPerUnit"), aa.GetInt("loops"), (aa.HasParam("scale") ? aa.GetFloat("scale") : 1), aa.GetCCPoint("pos"), 
						transGLBlendFactor(aa.GetStr("srcBlendFactor").c_str(), GL_ONE), transGLBlendFactor(aa.GetStr("dstBlendFactor").c_str(), GL_ONE_MINUS_SRC_ALPHA),
						aa.GetInt("zOrder"), aa.GetInt("tag"));
		}
		
		// 3. CCActionInterval
		// 3.1 basic
		else if (actionName == "CCMoveTo") {
			ret = CCMoveTo::create(aa.GetFloat("duration"), aa.GetCCPoint("position"));
		} else if (actionName == "CCMoveBy") {
			ret = CCMoveBy::create(aa.GetFloat("duration"), aa.GetCCPoint("deltaPosition"));
		} else if (actionName == "CCJumpTo") {
			ret = CCJumpTo::create(aa.GetFloat("duration"), aa.GetCCPoint("position"), aa.GetFloat("height"), aa.GetInt("jumps"));
		} else if (actionName == "CCJumpBy") {
			ret = CCJumpBy::create(aa.GetFloat("duration"), aa.GetCCPoint("position"), aa.GetFloat("height"), aa.GetInt("jumps"));
		} else if (actionName == "CCBlink") {
			ret = CCBlink::create(aa.GetFloat("duration"), aa.GetInt("blinks"));
		} else if (actionName == "CCRepeat") {
			ret = CCRepeat::create((CCActionInterval*)aa.actionList[0], aa.GetInt("times"));
		} else if (actionName == "CCRepeatForEver") {
			// bug: CCRepeatForEver not effect in CCSequence, use CCRepeat replaced
			ret = CCRepeat::create((CCActionInterval*)aa.actionList[0], 0x7FFFFFFF);
			//ret = CCRepeatForever::create((CCActionInterval*)aa.actionList[0]);
		} else if (actionName == "CCRotateBy") {
			ret = CCRotateBy::create(aa.GetFloat("duration"), aa.GetFloat("deltaAngel"));
		} else if (actionName == "CCRotateTo") {
			ret = CCRotateTo::create(aa.GetFloat("duration"), aa.GetFloat("deltaAngel"));
		} else if (actionName == "CCSkewTo") {
			ret = CCSkewTo::create(aa.GetFloat("t"), aa.GetFloat("sx"), aa.GetFloat("sy"));
		} else if (actionName == "CCSkewBy") {
			ret = CCSkewBy::create(aa.GetFloat("t"), aa.GetFloat("sx"), aa.GetFloat("sy"));
		} else if (actionName == "CCBezierBy") {
			ret = CCBezierBy::create(aa.GetFloat("t"), aa.GetBezier("bezier"));
		} else if (actionName == "CCBezierTo") {
			ret = CCBezierTo::create(aa.GetFloat("t"), aa.GetBezier("bezier"));
		} else if (actionName == "CCScaleBy") {
			ret = CCScaleBy::create(aa.GetFloat("duration"), aa.GetFloat("s"));
		} else if (actionName == "CCScaleTo") {
			ret = CCScaleTo::create(aa.GetFloat("duration"), aa.GetFloat("s"));
		} else if (actionName == "CCFadeIn") {
			ret = CCFadeIn::create(aa.GetFloat("d"));
		} else if (actionName == "CCFadeOut") {
			ret = CCFadeOut::create(aa.GetFloat("d"));
		} else if (actionName == "GE_TurnOver") {
			if (ammend->pParamInner->gridEffectSprite != NULL) {
				ret = GE_TurnOver::create(ammend->pParamInner->gridEffectSprite, aa.GetFloat("degree"), aa.GetFloat("duration"));
			} else {
				ret = CCDelayTime::create(aa.GetFloat("duration"));
			}
		} else if (actionName == "GE_Shake") {
			if (ammend->pParamInner->gridEffectSprite != NULL) {
				ret = GE_Shake::create(ammend->pParamInner->gridEffectSprite, aa.GetFloat("range"), aa.GetFloat("duration"));
			} else {
				ret = CCDelayTime::create(aa.GetFloat("duration"));
			}
		} else if (actionName == "GE_EdgeScale") {
			if (ammend->pParamInner->gridEffectSprite != NULL) {
				ret = GE_EdgeScale::create(ammend->pParamInner->gridEffectSprite, aa.GetFloat("duration"), aa.GetFloat("up"), aa.GetFloat("down"), aa.GetFloat("left"), aa.GetFloat("right"));
			} else {
				ret = CCDelayTime::create(aa.GetFloat("duration"));
			}
		} else if (actionName == "GE_Stop") {
			if (ammend->pParamInner->gridEffectSprite != NULL) {
				ret = GE_Stop::create();
			} else {
				ret = CCDelayTime::create(0.001f);
			}
		} else if (actionName == "AE_RunAEAction") {
			ret = extractAction(aa.GetStr("aeFile"), aa.GetStr("spriteName"));
		} else if (actionName == "AE_AddSubAE") {
			std::map<std::string, std::string> resReplaced;
			char szBuff[64];
			for (int i = 1; i <= 5; ++i) {
				sprintf(szBuff, "sprite%d", i);
				std::string str1 = aa.GetStr(szBuff);
				if (str1.size() > 0) {
					sprintf(szBuff, "resReplaced%d", i);
					std::string str2 = aa.GetStr(szBuff);
					resReplaced[str1] = str2;
				}
			}
			ret = AE_AddSubAE::create(this, aa.GetStr("aeFile"), aa.GetStr("alignSprite"), aa.GetCCPoint("pos"), aa.GetFloat("scale"), resReplaced, aa.GetInt("zOrder"), aa.GetInt("tag"));
		} else if (actionName == "AE_AddMpEffect") {
			ret = AE_AddMpEffect::create(aa.GetStr("mpFile"), aa.GetCCPoint("pos"), aa.GetFloat("extraAnimationScale"), aa.GetFloat("scale"), aa.GetInt("zOrder"), aa.GetInt("tag"));
		} else if (actionName == "AE_UiMoveFromDelta") {
			ret = AE_UiMoveFromDelta::create(spriteName, aa.GetFloat("duration"));
		} else if (actionName == "AE_UiMoveToWidget") {
			assert(ammend->pParamInner->uiJasonRoot != NULL);
			float duration = aa.GetFloat("duration");
			std::string moveToWidgetName = aa.GetStr("moveToWidgetName");
			if (ammend->uiNameReplaced.find(moveToWidgetName) != ammend->uiNameReplaced.end()) {
				moveToWidgetName = ammend->uiNameReplaced[moveToWidgetName];
			}
			CCPoint offset = aa.GetCCPoint("offset");

			UIWidget* moveFrom = CCUIHELPER->seekWidgetByName(ammend->pParamInner->uiJasonRoot, spriteName);
			UIWidget* movedTo = CCUIHELPER->seekWidgetByName(ammend->pParamInner->uiJasonRoot, moveToWidgetName.c_str());
			if (moveFrom == NULL || movedTo == NULL) {
				ret = CCDelayTime::create(duration);
			} else {
				CCPoint moveDelta = offset + movedTo->getContainerNode()->convertToWorldSpaceAR(CCPointZero) - moveFrom->getContainerNode()->convertToWorldSpaceAR(CCPointZero);
				ret = CCMoveBy::create(duration, moveDelta);
			}

		} else if (actionName == "AE_FadeIn_WithAllChild") {
			ret = AE_FadeIn_WithAllChild::create(aa.GetFloat("d"));
		} else if (actionName == "AE_FadeOut_WithAllChild") {
			ret = AE_FadeOut_WithAllChild::create(aa.GetFloat("d"));
		} else if (actionName == "CCFadeTo") {
			ret = CCFadeTo::create(aa.GetFloat("duration"), aa.GetInt("opacity"));
		} else if (actionName == "CCTintTo") {
			ret = CCTintTo::create(aa.GetFloat("duration"), aa.GetInt("r"), aa.GetInt("g"), aa.GetInt("b"));
		} else if (actionName == "CCTintBy") {
			ret = CCTintBy::create(aa.GetFloat("duration"), aa.GetInt("r"), aa.GetInt("g"), aa.GetInt("b"));
		} else if (actionName == "CCDelayTime") {
			ret = CCDelayTime::create(aa.GetFloat("d"));
		} else if (actionName == "CCReverseTime") {
			ret = CCReverseTime::create((CCActionInterval*)aa.actionList[0]);
		} else if (actionName == "CCShake") {
			ret = CCShake::create(aa.GetFloat("duration"), aa.GetCCPoint("amplitude"), aa.GetInt("isDampening") > 0, aa.GetInt("shakeNum"));
		} 
		// 3.2 animate
		else if (actionName == "CCAnimate") {
			char szBuff[100];
			CCAnimation* animation = NULL;
			if (aa.HasParam("plist") && aa.GetStr("plist") != "") {
				CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(aa.GetStr("plist").c_str());
				CCArray* animFrames = CCArray::create();
				std::list<std::string> strs = aa.GetStrs("fileNames");
				for (std::list<std::string>::iterator it = strs.begin(); it != strs.end(); ++it) {
					CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(it->c_str());
					animFrames->addObject(frame);
				}
				if (aa.HasParam("prefix") && aa.GetStr("prefix") != "" && aa.GetInt("prefixNum") > 0) {
					for (int i = 1; i <= aa.GetInt("prefixNum"); ++i) {
						sprintf(szBuff, "%s%02d.png", aa.GetStr("prefix").c_str(), i);
						CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szBuff);
						animFrames->addObject(frame);
					}
				}
				animation = CCAnimation::createWithSpriteFrames(animFrames, 0);
			} else {
				animation = CCAnimation::create();
				std::list<std::string> strs = aa.GetStrs("fileNames");
				for (std::list<std::string>::iterator it = strs.begin(); it != strs.end(); ++it) {
					animation->addSpriteFrameWithFileName(it->c_str());
				}
				if (aa.HasParam("prefix") && aa.GetStr("prefix") != "" && aa.GetInt("prefixNum") > 0) {
					for (int i = 1; i <= aa.GetInt("prefixNum"); ++i) {
						sprintf(szBuff, "%s%02d.png", aa.GetStr("prefix").c_str(), i);
						animation->addSpriteFrameWithFileName(szBuff);
					}
				}
			}

			animation->setDelayPerUnit(aa.GetFloat("delayPerUnit"));
			animation->setLoops(aa.GetInt("loops") <= 0 ? 0 : aa.GetInt("loops"));

			if (animation != NULL) {
				ret = CCAnimate::create(animation);
			}
		}

		else if (actionName == "CCSpeed") {
			ret = CCSpeed::create((CCActionInterval*)aa.actionList[0], aa.GetFloat("speed"));
			if (ret)
			{
				ret->setTag(999999); //专门给调节速度使用的tag
			}
		}
		else if (actionName == "CCOrbitCamera") {
			ret = CCOrbitCamera::create(aa.GetFloat("t"), aa.GetFloat("radius"), aa.GetFloat("deltaRadius"), 
				aa.GetFloat("angleZ"), aa.GetFloat("deltaAngleZ"), aa.GetFloat("angleX"), aa.GetFloat("deltaAngleX"));
		}
		// 3.3 ease
		else if (actionName == "CCEaseIn") {
			ret = CCEaseIn::create((CCActionInterval*)aa.actionList[0], aa.GetFloat("rate"));
		} else if (actionName == "CCEaseOut") {
			ret = CCEaseOut::create((CCActionInterval*)aa.actionList[0], aa.GetFloat("rate"));
		} else if (actionName == "CCEaseInOut") {
			ret = CCEaseInOut::create((CCActionInterval*)aa.actionList[0], aa.GetFloat("rate"));
		} else if (actionName == "CCEaseExponentialIn") {
			ret = CCEaseExponentialIn::create((CCActionInterval*)aa.actionList[0]);
		} else if (actionName == "CCEaseExponentialOut") {
			ret = CCEaseExponentialOut::create((CCActionInterval*)aa.actionList[0]);
		} else if (actionName == "CCEaseExponentialInOut") {
			ret = CCEaseExponentialInOut::create((CCActionInterval*)aa.actionList[0]);
		} else if (actionName == "CCEaseSineIn") {
			ret = CCEaseSineIn::create((CCActionInterval*)aa.actionList[0]);
		} else if (actionName == "CCEaseSineOut") {
			ret = CCEaseSineOut::create((CCActionInterval*)aa.actionList[0]);
		} else if (actionName == "CCEaseSineInOut") {
			ret = CCEaseSineInOut::create((CCActionInterval*)aa.actionList[0]);
		} else if (actionName == "CCEaseElasticIn") {
			ret = CCEaseElasticIn::create((CCActionInterval*)aa.actionList[0], aa.GetFloat("period"));
		} else if (actionName == "CCEaseElasticOut") {
			ret = CCEaseElasticOut::create((CCActionInterval*)aa.actionList[0], aa.GetFloat("period"));
		} else if (actionName == "CCEaseElasticInOut") {
			ret = CCEaseElasticInOut::create((CCActionInterval*)aa.actionList[0], aa.GetFloat("period"));
		} else if (actionName == "CCEaseBounceIn") {
			ret = CCEaseBounceIn::create((CCActionInterval*)aa.actionList[0]);
		} else if (actionName == "CCEaseBounceOut") {
			ret = CCEaseBounceOut::create((CCActionInterval*)aa.actionList[0]);
		} else if (actionName == "CCEaseBounceInOut") {
			ret = CCEaseBounceInOut::create((CCActionInterval*)aa.actionList[0]);
		} else if (actionName == "CCEaseBackIn") {
			ret = CCEaseBackIn::create((CCActionInterval*)aa.actionList[0]);
		} else if (actionName == "CCEaseBackOut") {
			ret = CCEaseBackOut::create((CCActionInterval*)aa.actionList[0]);
		} else if (actionName == "CCEaseBackInOut") {
			ret = CCEaseBackInOut::create((CCActionInterval*)aa.actionList[0]);

		// 4 grid
		// StopGrid
		} else if (actionName == "CCStopGrid") {
			ret = CCStopGrid::create();
		// Amplitude
		} else if (actionName == "CCDeccelAmplitude") {
			ret = CCDeccelAmplitude::create((CCAction*)aa.actionList[0], aa.GetFloat("duration"));
		} else if (actionName == "CCAccelAmplitude") {
			ret = CCAccelAmplitude::create((CCAction*)aa.actionList[0], aa.GetFloat("duration"));
		} else if (actionName == "CCAccelDeccelAmplitude") {
			ret = CCAccelDeccelAmplitude::create((CCAction*)aa.actionList[0], aa.GetFloat("duration"));
		}
		// TiledGrid3D
		else if (actionName == "CCShakyTiles3D") {
			CCSize cc_size;
			CCPoint cc_point = aa.GetCCPoint("gridSize");
			cc_size.width = cc_point.x;
			cc_size.height = cc_point.y;
			ret = CCShakyTiles3D::create(aa.GetFloat("duration"), cc_size, aa.GetInt("range"), aa.GetInt("shakeZ") > 0);
		} else if (actionName == "CCShatteredTiles3D") { // not effected
			CCSize cc_size;
			CCPoint cc_point = aa.GetCCPoint("gridSize");
			cc_size.width = cc_point.x;
			cc_size.height = cc_point.y;
			ret = CCShatteredTiles3D::create(aa.GetFloat("duration"), cc_size, aa.GetInt("range"), aa.GetInt("shakeZ") > 0);
		} else if (actionName == "CCShuffleTiles") {
			CCSize cc_size;
			CCPoint cc_point = aa.GetCCPoint("gridSize");
			cc_size.width = cc_point.x;
			cc_size.height = cc_point.y;
			ret = CCShuffleTiles::create(aa.GetFloat("duration"), cc_size, aa.GetInt("speed"));
		} else if (actionName == "CCFadeOutTRTiles") {
			CCSize cc_size;
			CCPoint cc_point = aa.GetCCPoint("gridSize");
			cc_size.width = cc_point.x;
			cc_size.height = cc_point.y;
			ret = CCFadeOutTRTiles::create(aa.GetFloat("duration"), cc_size);
		} else if (actionName == "CCFadeOutBLTiles") {
			CCSize cc_size;
			CCPoint cc_point = aa.GetCCPoint("gridSize");
			cc_size.width = cc_point.x;
			cc_size.height = cc_point.y;
			ret = CCFadeOutBLTiles::create(aa.GetFloat("duration"), cc_size);
		} else if (actionName == "CCFadeOutUpTiles") {
			CCSize cc_size;
			CCPoint cc_point = aa.GetCCPoint("gridSize");
			cc_size.width = cc_point.x;
			cc_size.height = cc_point.y;
			ret = CCFadeOutUpTiles::create(aa.GetFloat("duration"), cc_size);
		} else if (actionName == "CCFadeOutDownTiles") {
			CCSize cc_size;
			CCPoint cc_point = aa.GetCCPoint("gridSize");
			cc_size.width = cc_point.x;
			cc_size.height = cc_point.y;
			ret = CCFadeOutDownTiles::create(aa.GetFloat("duration"), cc_size);
		} else if (actionName == "CCTurnOffTiles") {
			CCSize cc_size;
			CCPoint cc_point = aa.GetCCPoint("gridSize");
			cc_size.width = cc_point.x;
			cc_size.height = cc_point.y;
			ret = CCTurnOffTiles::create(aa.GetFloat("duration"), cc_size, aa.GetInt("seed"));
		} else if (actionName == "CCWavesTiles3D") {
			CCSize cc_size;
			CCPoint cc_point = aa.GetCCPoint("gridSize");
			cc_size.width = cc_point.x;
			cc_size.height = cc_point.y;
			ret = CCWavesTiles3D::create(aa.GetFloat("duration"), cc_size, aa.GetInt("waves"), aa.GetFloat("amplitude"));
		} else if (actionName == "CCJumpTiles3D") {
			CCSize cc_size;
			CCPoint cc_point = aa.GetCCPoint("gridSize");
			cc_size.width = cc_point.x;
			cc_size.height = cc_point.y;
			ret = CCJumpTiles3D::create(aa.GetFloat("duration"), cc_size, aa.GetInt("numberOfJumps"), aa.GetFloat("amplitude"));
		} else if (actionName == "CCSplitRows") {
			ret = CCSplitRows::create(aa.GetFloat("duration"), aa.GetInt("rows"));
		} else if (actionName == "CCSplitCols") {
			ret = CCSplitCols::create(aa.GetFloat("duration"), aa.GetInt("cols"));
		} else if (actionName == "CCPageTurn3D") {
			CCSize cc_size;
			CCPoint cc_point = aa.GetCCPoint("gridSize");
			cc_size.width = cc_point.x;
			cc_size.height = cc_point.y;
			ret = CCPageTurn3D::create(aa.GetFloat("duration"), cc_size);
		} else if (actionName == "CCWaves3D") {
			CCSize cc_size;
			CCPoint cc_point = aa.GetCCPoint("gridSize");
			cc_size.width = cc_point.x;
			cc_size.height = cc_point.y;
			ret = CCWaves3D::create(aa.GetFloat("duration"), cc_size, aa.GetInt("waves"), aa.GetFloat("amplitude"));
		} else if (actionName == "CCWaves") {
			CCSize cc_size;
			CCPoint cc_point = aa.GetCCPoint("gridSize");
			cc_size.width = cc_point.x;
			cc_size.height = cc_point.y;
			ret = CCWaves::create(aa.GetFloat("duration"), cc_size, aa.GetInt("waves"), aa.GetFloat("amplitude"),
				aa.GetInt("horizontal") > 0, aa.GetInt("vertical") > 0);
		} else if (actionName == "CCFlipX3D") {
			ret = CCFlipX3D::create(aa.GetFloat("duration"));
		} else if (actionName == "CCFlipY3D") {
			ret = CCFlipY3D::create(aa.GetFloat("duration"));
		} else if (actionName == "CCLens3D") { // TODO: check not effected
			CCPoint cc_point1 = aa.GetCCPoint("gridSize");
			CCSize cc_size1(cc_point1.x, cc_point1.y);
			CCPoint cc_point2 = aa.GetCCPoint("position");
			ret = CCLens3D::create(aa.GetFloat("duration"), cc_size1, cc_point2, aa.GetFloat("radius"));
		} else if (actionName == "CCRipple3D") {
			CCPoint cc_point1 = aa.GetCCPoint("gridSize");
			CCSize cc_size1(cc_point1.x, cc_point1.y);
			CCPoint cc_point2 = aa.GetCCPoint("position");
			ret = CCRipple3D::create(aa.GetFloat("duration"), cc_size1, cc_point2, aa.GetFloat("radius"),
				aa.GetInt("waves"), aa.GetFloat("amplitude"));
		} else if (actionName == "CCLiquid") {
			CCPoint cc_point1 = aa.GetCCPoint("gridSize");
			CCSize cc_size1(cc_point1.x, cc_point1.y);
			ret = CCLiquid::create(aa.GetFloat("duration"), cc_size1, aa.GetInt("waves"), aa.GetFloat("amplitude"));
		} else if (actionName == "CCTwirl") {
			CCPoint cc_point1 = aa.GetCCPoint("gridSize");
			CCSize cc_size1(cc_point1.x, cc_point1.y);
			ret = CCTwirl::create(aa.GetFloat("duration"), cc_size1, aa.GetCCPoint("position"), aa.GetInt("twirls"), aa.GetFloat("amplitude"));
		}

		if (ret != NULL && eAction->Attribute("targetTag") != NULL && strlen(eAction->Attribute("targetTag")) != 0) {
			int targetTag = eAction->IntAttribute("targetTag");
			if (targetTag != 0 && ret != NULL) {
				ret = AE_ChildTagRun::create(targetTag, ret);
			}
		}
		
		return ret;
	}

	void split(std::string& str, std::vector<std::string>& ret, tinyxml2::XMLElement* eConfig, AEParamAmmend& ammend) {
		for (size_t i = 0, start = 0; i < str.size(); ++i) {
			if (str[i] == ',') {
				if (i != start) {
					ret.push_back(ActionParam::GetStringParam(str.substr(start, i - start).c_str(), eConfig, &ammend));
				}
				start = i + 1;
			} else if (i == str.size() - 1) {
				if (i >= start) {
					ret.push_back(ActionParam::GetStringParam(str.substr(start, i + 1 - start).c_str(), eConfig, &ammend));
				}
			}
		}
	}

	class XmlCacheEntry {
	public:
		char* szBuff;
		tinyxml2::XMLDocument* pDoc;

		XmlCacheEntry(const std::string& fileName) : szBuff(0), pDoc(0) {
			unsigned long size;
			unsigned char* pData = CCFileUtils::sharedFileUtils()->getFileData(fileName.c_str(), "rb", &size);
			if (pData == NULL) {
				CCLOG("Error in RunUIAction, %s not found !", fileName.c_str());
				return;
			}

			szBuff = new char[size + 1];
			szBuff[size] = 0;
			memcpy(szBuff, pData, size);
			delete[] pData;

			pDoc = new tinyxml2::XMLDocument();
			pDoc->ParseDeep(szBuff, 0 );
		}

		~XmlCacheEntry() {
			if (pDoc) delete pDoc;
			if (szBuff) delete[] szBuff;
		}
	};

	class SkillAction {
	private:
		std::vector<CCNode*> toRmvNodes;
		CCCallFunc* onActionDone;

	public:
		SkillAction(CCCallFunc* _onActionDone) {
			this->onActionDone = _onActionDone;
		}

		void addNode(CCNode* node) {
			toRmvNodes.push_back(node);
			node->retain();
		}

		~SkillAction() {
			for (std::vector<CCNode*>::iterator it = toRmvNodes.begin(); it != toRmvNodes.end(); ++it) {
				CC_SAFE_RELEASE(*it);
			}
			toRmvNodes.clear();
		}
	};

	static std::map<std::string, XmlCacheEntry*> s_xmlCache;
	static std::map<std::string, CCAction*> s_actionCache;		// aeFileName + spriteName  -->  action
	static int s_seed = 0;

	CCSpawn* ActionTemplateTable::extractAction(const std::string& fileName, std::string spriteName, AEParamAmmend& ammend, bool isUseCache) {
		std::string index = fileName + "-" + spriteName;
		if (s_actionCache.find(index) == s_actionCache.end()) {
			CCArray* actions = CCArray::create();
			unsigned long size;
			unsigned char* pData = CCFileUtils::sharedFileUtils()->getFileData(fileName.c_str(), "rb", &size);
			if (pData != NULL) {
				tinyxml2::XMLDocument doc;
				std::string str((char*)pData, size);
				delete[] pData;
				doc.ParseDeep((char*)str.c_str(), 0 );

				tinyxml2::XMLElement* eRoot = doc.RootElement();
				tinyxml2::XMLElement* eConfig = eRoot->FirstChildElement("config");
				for (tinyxml2::XMLElement* eSprite = eRoot->FirstChildElement("sprite"); eSprite != NULL; eSprite = eSprite->NextSiblingElement("sprite")) 
				{
					if (spriteName != eSprite->Attribute("name")) continue;

					for (tinyxml2::XMLElement* eAction = eSprite->FirstChildElement("action"); eAction != NULL; eAction = eAction->NextSiblingElement("action")) {
						CCAction* pAction = CreateAction(eSprite->Attribute("name"), eAction, eConfig, &ammend);
						if (pAction != NULL) {
							actions->addObject(pAction);
						}
					}
				}

			}

			if (actions->count() == 0) {
				actions->addObject(CCDelayTime::create(0.0f));
			}
			CCSpawn* spawn = CCSpawn::create(actions);
			if (!isUseCache) {
				return spawn;
			}
			spawn->retain();
			s_actionCache[index] = spawn;
		}

		return (CCSpawn*)(s_actionCache[index]->copy());
	}

	XmlCacheEntry* getXmlCacheEntry(std::string xmlFileName) {
		XmlCacheEntry* pEntry = NULL;
#ifdef WIN32
		pEntry = new XmlCacheEntry(xmlFileName);
#else
		if (s_xmlCache.find(xmlFileName) != s_xmlCache.end()) {
			pEntry = s_xmlCache[xmlFileName];
		} else {
			pEntry = new XmlCacheEntry(xmlFileName);
			if (pEntry->pDoc == NULL) { // Parse Error
				delete pEntry;
				return NULL;
			}
			s_xmlCache[xmlFileName] = pEntry;
		}
#endif
		return pEntry;
	}

	CCNode* ActionTemplateTable::addAEToNode(const std::string& fileName, std::string alignSpriteName, float scale, const std::map<std::string, std::string>& resReplace, float delay) {
		CCNode* container = CCNode::create();

		AEParamAmmend ammend;
		ammend.pParamInner->isSubAE = true;
		ammend.pParamInner->init_delay = delay;
		ammend.resReplaced = resReplace;
		ammend.alignSpriteName = alignSpriteName;

		XmlCacheEntry* xmlCacheEntry = getXmlCacheEntry(fileName);
		if (xmlCacheEntry != 0) {
			RunAeAction(container, ammend, xmlCacheEntry->pDoc->RootElement());
		}
		
		container->setPosition(ccp(-ammend.pParamInner->alignSpritePos.x, -ammend.pParamInner->alignSpritePos.y));

		CCNode* ret = CCNode::create();
		ret->addChild(container);
		ret->setScale(scale);

		// 下一帧显示
		ret->setVisible(false);
		ret->runAction(CCShow::create());
		return ret;
	}

	enum EOffsetType
	{
		Performer_Position,     // 相对于施放者
		Performer_Upper,
		Performer_Middle,
		Performer_Bottom,

		Target_Position,        // 相对于目标       
		Target_Upper,
		Target_Middle,
		Target_Bottom,

		Screen_Position,           // 相对于屏幕
	};

	static EOffsetType transferOffsetType(std::string str) {
		if (str == "Performer_Position") {
			return Performer_Position;
		} else if (str == "Performer_Upper") {
			return Performer_Upper;
		} else if (str == "Performer_Middle") {
			return Performer_Middle;
		} else if (str == "Performer_Bottom") {
			return Performer_Bottom;
		} else if (str == "Target_Position") {
			return Target_Position;
		} else if (str == "Target_Upper") {
			return Target_Upper;
		} else if (str == "Target_Middle") {
			return Target_Middle;
		} else if (str == "Target_Bottom") {
			return Target_Bottom;
		} else if (str == "Screen_Position") {
			return Screen_Position;
		} else {
			CCLog("Unkowned offsetType: %s", str.c_str());
			return Screen_Position;
		}
	}

	int nextSeed() { return ++s_seed; }

	static CCPoint calculateGridXY(CCPoint& gridXY, bool isChangePart) {
		CCPoint ret;
		ret.x = 384 + ((!isChangePart ? gridXY.x : 4 - gridXY.x) - 2) /** getFightConf()->x_dist*/;
		ret.y = 512 + ((!isChangePart ? gridXY.y : 8 - gridXY.y) - 4) /** getFightConf()->y_dist*/;
		return ret;
	}

	void ActionTemplateTable::ClearXmlFileCache() {
		for (std::map<std::string, XmlCacheEntry*>::iterator it = s_xmlCache.begin(); it != s_xmlCache.end(); ++it) {
			delete it->second;
		}
		s_xmlCache.clear();
	}

	static CCNode* RunDynamicNode(tinyxml2::XMLElement* eSprite, ActionTemplateTable& actionTemplateTable, 
		tinyxml2::XMLElement* eConfig, AEParamAmmend& ammend, float totalSecond, CCNode* performer, CCNode* target) 
	{
		EOffsetType eOffsetType = transferOffsetType(eSprite->Attribute("dynamic_offsetType"));
		CCPoint offset = ActionParam::GetPointParam(eSprite->Attribute("dynamic_offset"), eConfig, &ammend);
		bool isOrientAdjust = false;
		float delaySecond = 0.0f;
		if (!ammend.isPerformerAttacker && eSprite->Attribute("dynamic_isOrientAdjust") != NULL && strlen(eSprite->Attribute("dynamic_isOrientAdjust")) != 0) {
			isOrientAdjust = eSprite->IntAttribute("dynamic_isOrientAdjust") > 0;
		}
		if (eSprite->Attribute("dynamic_delaySecond") != NULL && strlen(eSprite->Attribute("dynamic_delaySecond")) != 0) {
			delaySecond = eSprite->FloatAttribute("dynamic_delaySecond");
		}

		CCSprite* dynamicNode = NULL;
		if (eSprite->Attribute("res") != NULL && strlen(eSprite->Attribute("res")) != 0)
			dynamicNode = CCSprite::create(eSprite->Attribute("res"));
		else {
			dynamicNode = CCSprite::create();
		}
		if (eSprite->Attribute("dynamic_use_new_grid") != NULL && strlen(eSprite->Attribute("dynamic_use_new_grid")) != 0 && eSprite->IntAttribute("dynamic_use_new_grid") > 0) {
			dynamicNode = GridEffectSprite::create(dynamicNode);
		}
		if (eSprite->Attribute("scale") != NULL && strlen(eSprite->Attribute("scale")) != 0) {
			dynamicNode->setScale(eSprite->FloatAttribute("scale"));
		}
		if (eSprite->Attribute("zOrder") != NULL && strlen(eSprite->Attribute("zOrder")) != 0) {
			dynamicNode->setZOrder(eSprite->IntAttribute("zOrder"));
		}
		if (eSprite->Attribute("dynamic_anchor") != NULL && strlen(eSprite->Attribute("dynamic_anchor")) != 0) {
			dynamicNode->setAnchorPoint(ActionParam::GetPointParam(eSprite->Attribute("dynamic_anchor"), eConfig, &ammend));
		}
		dynamicNode->setVisible(false);	// show in actions
		if (target != NULL) {
			ammend.pParamInner->dynamicNode2TargetPos[eSprite->Attribute("name")] = target->getPosition();
		}
		
		CCPoint pos = offset;
		if (isOrientAdjust) {
			pos.y = -pos.y;
		}
		if (performer != NULL) {
			switch (eOffsetType) {
			case Performer_Position: pos.x += performer->getPositionX(); pos.y += performer->getPositionY(); break;
			case Performer_Upper: pos.x += performer->getPositionX(); pos.y += isOrientAdjust ? 0 : 1024; break;
			case Performer_Middle: pos.x += performer->getPositionX(); pos.y += 512; break;
			case Performer_Bottom: pos.x += performer->getPositionX(); pos.y += isOrientAdjust ? 1024 : 0; break;
			}
		}
		if (target != NULL) {
			switch (eOffsetType) {
			case Target_Position: pos.x += target->getPositionX(); pos.y += target->getPositionY(); break;
			case Target_Upper: pos.x += target->getPositionX(); pos.y += isOrientAdjust ? 0 : 1024; break;
			case Target_Middle: pos.x += target->getPositionX(); pos.y += 512; break;
			case Target_Bottom: pos.x += target->getPositionX(); pos.y += isOrientAdjust ? 1024 : 0; break;
			}
		}

		if (eOffsetType == Screen_Position && isOrientAdjust) {
			pos.y = 1024 - pos.y;
			pos.x = 768 - pos.x;
		}

		if (eSprite->Attribute("dynamic_col_delta") != NULL && strlen(eSprite->Attribute("dynamic_col_delta")) != 0) {
			int dynamic_col_delta = eSprite->IntAttribute("dynamic_col_delta");
			//pos.x += getFightConf()->x_dist * isOrientAdjust ? -dynamic_col_delta : dynamic_col_delta;
		}

		dynamicNode->setPosition(pos);
		if (eSprite->Attribute("extraDeviceScale") != NULL && strlen(eSprite->Attribute("extraDeviceScale")) > 0) {
			CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
			if (frameSize.width != 768) { // iphone 额外缩放
				dynamicNode->setScale(dynamicNode->getScale() * eSprite->FloatAttribute("extraDeviceScale"));
			}
		}

		if (isOrientAdjust && !ammend.isPerformerAttacker) {
			dynamicNode->setRotation(dynamicNode->getRotation() + 180.0f);
		}

		for (tinyxml2::XMLElement* eAction = eSprite->FirstChildElement("action"); eAction != NULL; eAction = eAction->NextSiblingElement("action")) {
			CCAction* pAction = actionTemplateTable.CreateAction(eSprite->Attribute("name"), eAction, eConfig, &ammend);

			dynamicNode->setVisible(false);
			dynamicNode->runAction(CCSequence::create(CCDelayTime::create(delaySecond), CCShow::create(), pAction, NULL));
			dynamicNode->runAction(CCSequence::create(CCDelayTime::create(totalSecond), CCRemoveSelf::create(), NULL));
		}

		return dynamicNode;
	}

	float ActionTemplateTable::RunSkillAction(const std::string& fileName, CCLayer* battleLayer, CCCallFunc* onActionDone) {
		AEParamAmmend ammend;
		return RunSkillAction(fileName, battleLayer, ammend, onActionDone);
	}

	float ActionTemplateTable::RunSkillAction(const std::string& fileName, CCLayer* battleLayer, AEParamAmmend& ammend, CCCallFunc* onActionDone) {
		bool isGen = ammend.performer == NULL;
		XmlCacheEntry* pEntry = NULL;
		if (s_xmlCache.find(fileName) != s_xmlCache.end()) {
			pEntry = s_xmlCache[fileName];
		} else {
			pEntry = new XmlCacheEntry(fileName);
			if (pEntry->pDoc == NULL) { // Parse Error
				delete pEntry;
				return 0;
			}
			s_xmlCache[fileName] = pEntry;
		}

		tinyxml2::XMLElement* eConfig = pEntry->pDoc->RootElement()->FirstChildElement("config");
		float totalSecond = 2.0f;
		if (eConfig != NULL) {
			if (isDebug && isCreateDebugBackground) {
				if (eConfig->Attribute("testBackGround") != NULL && strlen(eConfig->Attribute("testBackGround")) != 0) {
					std::string strTestBackGround = std::string(eConfig->Attribute("testBackGround"));
					if (strTestBackGround.find(".ae") == std::string::npos) { // not ae
						CCNode* testBackGroundSprite = CCSprite::create(eConfig->Attribute("testBackGround"));
						if (testBackGroundSprite != NULL) {
							testBackGroundSprite->setScaleX(CCEGLView::sharedOpenGLView()->getFrameSize().width / testBackGroundSprite->getContentSize().width);
							testBackGroundSprite->setScaleY(CCEGLView::sharedOpenGLView()->getFrameSize().height / testBackGroundSprite->getContentSize().height);
							testBackGroundSprite->setPosition(ccp(CCEGLView::sharedOpenGLView()->getFrameSize().width / 2, 
								CCEGLView::sharedOpenGLView()->getFrameSize().height / 2));
							battleLayer->addChild(testBackGroundSprite);
							testBackGroundSprite->setVisible(false);
							testBackGroundSprite->runAction(CCShow::create());
						}
					} else { // ae
						std::map<std::string, std::string> xxx;
						CCNode* node = this->addAEToNode(strTestBackGround.c_str(), "", 1.0f, xxx);
						battleLayer->addChild(node);
					}
				}
				if (eConfig->Attribute("testChangePart") != NULL && strlen(eConfig->Attribute("testChangePart")) != 0) {
					ammend.isPerformerAttacker = eConfig->IntAttribute("testChangePart") == 0;
				}
			}

			if (eConfig->Attribute("totalSecond") != NULL && strlen(eConfig->Attribute("totalSecond")) != 0) {
				totalSecond = eConfig->FloatAttribute("totalSecond");
				if (onActionDone != NULL) { // onActionDone
					battleLayer->runAction(CCSequence::create(CCDelayTime::create(totalSecond), onActionDone, NULL));
				}
			}

			// first time: Performer and Targets
			for (tinyxml2::XMLElement* eSprite = pEntry->pDoc->RootElement()->FirstChildElement("sprite"); eSprite != NULL; eSprite = eSprite->NextSiblingElement("sprite")) 
			{
				if (strcmp(eSprite->Attribute("spriteType"), "Performer") == 0) {
					if (ammend.performer == NULL) {
						if (eSprite->Attribute("res") != NULL && strlen(eSprite->Attribute("res")) != 0) {
							ammend.performer = CCSprite::create(eSprite->Attribute("res"));
						} else {
							ammend.performer = CCSprite::create();
						}
						// 注释掉GridEffectSprite先
						//ammend.performer = GridEffectSprite::create((CCSprite*)ammend.performer);

						if (eSprite->Attribute("scale") != NULL && strlen(eSprite->Attribute("scale")) != 0) {
							ammend.performer->setScale(eSprite->FloatAttribute("scale"));
						}
                        CCPoint point = ActionParam::GetPointParam(eSprite->Attribute("performer_posGrid"), eConfig, &ammend);
						ammend.performer->setPosition(calculateGridXY(point, !ammend.isPerformerAttacker));
						if (eSprite->Attribute("zOrder") != NULL && strlen(eSprite->Attribute("zOrder")) != 0) {
							ammend.performer->setZOrder(eSprite->IntAttribute("zOrder"));
						}
						battleLayer->addChild(ammend.performer);
					}

					if (eSprite->Attribute("extraDeviceScale") != NULL && strlen(eSprite->Attribute("extraDeviceScale")) > 0) {
						CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
						if (frameSize.width != 768) { // iphone 额外缩放
							ammend.performer->setScale(ammend.performer->getScale() * eSprite->FloatAttribute("extraDeviceScale"));
						}
					}

					int todo_performer_skillNameAction;
					// __performer.skillNameSecond = eSprite->FloatAttribute("performer_skillNameSecond");

					for (tinyxml2::XMLElement* eAction = eSprite->FirstChildElement("action"); eAction != NULL; eAction = eAction->NextSiblingElement("action")) {
						CCAction* pAction = CreateAction(eSprite->Attribute("name"), eAction, eConfig, &ammend);

						ammend.performer->runAction(pAction);
					}

					if (isGen) {
						ammend.performer->runAction(CCSequence::create(CCDelayTime::create(totalSecond), CCRemoveSelf::create(), NULL));
					}
				} else if (strcmp(eSprite->Attribute("spriteType"), "Target") == 0) {
					if (isGen) {
						std::vector<CCPoint> gridPoses;
						char szBuff[64];
						for (int i = 1; i <= 5; ++i) {
							sprintf(szBuff, "target_posGrid%d", i);
							if (eSprite->Attribute(szBuff) != NULL && strlen(eSprite->Attribute(szBuff)) != 0) {
								CCPoint gridPos = ActionParam::GetPointParam(eSprite->Attribute(szBuff), eConfig, &ammend);
								if (gridPos.x < 0 && gridPos.y < 0) continue;

								gridPoses.push_back(gridPos);
							}
						}
						for (std::vector<CCPoint>::iterator it = gridPoses.begin(); it != gridPoses.end(); ++it) {
							CCSprite* target = NULL;
							if (eSprite->Attribute("res") != NULL && strlen(eSprite->Attribute("res")) != 0) {
								target = CCSprite::create(eSprite->Attribute("res"));
							} else {
								target = CCSprite::create();
							}
							// 注释掉GridEffectSprite先
							//target = GridEffectSprite::create((CCSprite*)target);

							if (eSprite->Attribute("scale") != NULL && strlen(eSprite->Attribute("scale")) != 0) {
								target->setScale(eSprite->FloatAttribute("scale"));
							}
							if (eSprite->Attribute("zOrder") != NULL && strlen(eSprite->Attribute("zOrder")) != 0) {
								target->setZOrder(eSprite->IntAttribute("zOrder"));
							}
							target->setPosition(calculateGridXY(*it, !ammend.isPerformerAttacker));
							ammend.targets.push_back(target);
							battleLayer->addChild(target);
							target->runAction(CCSequence::create(CCDelayTime::create(totalSecond), CCRemoveSelf::create(), NULL));

							if (eSprite->Attribute("extraDeviceScale") != NULL && strlen(eSprite->Attribute("extraDeviceScale")) > 0) {
								CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
								if (frameSize.width != 768) { // iphone 额外缩放
									target->setScale(target->getScale() * eSprite->FloatAttribute("extraDeviceScale"));
								}
							}
						}
					}

					// TODO ...
					int todo_target_hitSecond;
					for (tinyxml2::XMLElement* eAction = eSprite->FirstChildElement("action"); eAction != NULL; eAction = eAction->NextSiblingElement("action")) {
						CCAction* pAction = CreateAction(eSprite->Attribute("name"), eAction, eConfig, &ammend);

						for (std::vector<CCNode*>::iterator it = ammend.targets.begin(); it != ammend.targets.end(); ++it) {
							CCNode* pNode = *it;
							pNode->runAction(pAction);
						}
					}
				} else if (strcmp(eSprite->Attribute("spriteType"), "Dynamic") == 0) {
					bool isPerTarget = false;
					if (eSprite->Attribute("dynamic_isPerTarget") != NULL && strlen(eSprite->Attribute("dynamic_isPerTarget")) != 0) {
						isPerTarget = eSprite->IntAttribute("dynamic_isPerTarget") > 0;
					}

					if (isPerTarget) {
						for (std::vector<CCNode*>::iterator it = ammend.targets.begin(); it != ammend.targets.end(); ++it) {
							CCNode* dynamicNode = RunDynamicNode(eSprite, *this, eConfig, ammend, totalSecond, ammend.performer, *it); 
							if (dynamicNode != NULL) {
								battleLayer->addChild(dynamicNode);
							}
						}
					} else {
						CCNode* dynamicNode = RunDynamicNode(eSprite, *this, eConfig, ammend, totalSecond, ammend.performer, NULL); 
						if (dynamicNode != NULL) {
							battleLayer->addChild(dynamicNode);
						}
					}
				}
			}
		}

		return totalSecond;
	}

	void ActionTemplateTable::RunUIAction(const std::string& fileName, UIWidget* uiWidget) {
		AEParamAmmend ammend;
		RunUIAction(fileName, uiWidget, ammend);
	}

	void ActionTemplateTable::RunUIAction(const std::string& fileName, UIWidget* uiWidget, AEParamAmmend& ammend) {
		// TODO cache
		unsigned long size;
		unsigned char* pData = CCFileUtils::sharedFileUtils()->getFileData(fileName.c_str(), "rb", &size);
		if (pData == NULL) {
			CCLOG("Error in RunUIAction, %s not found !", fileName.c_str());
			return;
		}

		ammend.pParamInner->uiJasonRoot = uiWidget;

		tinyxml2::XMLDocument doc;
		char* szBuff = new char[size + 1];
		szBuff[size] = 0;
		memcpy(szBuff, pData, size);
		delete[] pData;

		doc.ParseDeep(szBuff, 0 );

		float testDelaySecond = 0;
		tinyxml2::XMLElement* eConfig = doc.RootElement()->FirstChildElement("config");
		if (eConfig != NULL) {
			if (isDebug) {
				// 非debug,外面设置
				CCSize winSize = CCDirector::sharedDirector()->getWinSize();
				uiWidget->setPosition(ccp(winSize.width / 2, winSize.height / 2));

				if (eConfig->Attribute("testBackGround") != NULL && strlen(eConfig->Attribute("testBackGround")) != 0) {
					CCNode* testBackGroundSprite = CCSprite::create(eConfig->Attribute("testBackGround"));
					if (testBackGroundSprite != NULL) {
						testBackGroundSprite->setScaleX(CCEGLView::sharedOpenGLView()->getFrameSize().width / testBackGroundSprite->getContentSize().width);
						testBackGroundSprite->setScaleY(CCEGLView::sharedOpenGLView()->getFrameSize().height / testBackGroundSprite->getContentSize().height);
						testBackGroundSprite->setPosition(ccp(CCEGLView::sharedOpenGLView()->getFrameSize().width / 2, 
							CCEGLView::sharedOpenGLView()->getFrameSize().height / 2));
						if (uiWidget->getValidNode() != NULL) {
							uiWidget->getValidNode()->getParent()->addChild(testBackGroundSprite);
						}
						testBackGroundSprite->setVisible(false);
						testBackGroundSprite->runAction(CCShow::create());
					}
				}
				if (eConfig->Attribute("testDelaySecond") != NULL && strlen(eConfig->Attribute("testDelaySecond")) != 0) {
					testDelaySecond = eConfig->FloatAttribute("testDelaySecond");
				}
			}
			if (eConfig->Attribute("condition") != NULL && strlen(eConfig->Attribute("condition")) != 0) {
				ammend.condition = eConfig->IntAttribute("condition");
			}
		}

		for (tinyxml2::XMLElement* eSprite = doc.RootElement()->FirstChildElement("sprite"); eSprite != NULL; eSprite = eSprite->NextSiblingElement("sprite")) 
		{
			std::vector<std::string> uiWidgetNames;
			std::string spriteNameStr(eSprite->Attribute("name"));
			split(spriteNameStr, uiWidgetNames, eConfig, ammend);
			for (std::vector<std::string>::iterator it = uiWidgetNames.begin(); it != uiWidgetNames.end(); ++it) {
				if (ammend.uiNameReplaced.find(*it) != ammend.uiNameReplaced.end()) {
					*it = ammend.uiNameReplaced[*it];
				}
			}

			for (std::vector<std::string>::iterator it = uiWidgetNames.begin(); it != uiWidgetNames.end(); ++it) {
				UIWidget* subWidget = (CCUIHELPER->seekWidgetByName(uiWidget, it->c_str()));
				if (subWidget == NULL) continue;

				if (eSprite->Attribute("initOffset") != NULL && strlen(eSprite->Attribute("initOffset")) != 0) {
					CCPoint initOffset = ActionParam::GetPointParam(eSprite->Attribute("initOffset"), eConfig, &ammend);
					if (g_uiNameToOriginalPos.find(std::string(subWidget->getName())) == g_uiNameToOriginalPos.end()) {
						CCPoint originalPosition = subWidget->getPosition();
						g_uiNameToOriginalPos[std::string(subWidget->getName())] = originalPosition;
					}
					CCPoint originalPosition = g_uiNameToOriginalPos[std::string(subWidget->getName())];

					if (subWidget->getPosition().x == originalPosition.x && subWidget->getPosition().y == originalPosition.y) {
						subWidget->setPosition(ccpAdd(originalPosition, initOffset));
					}
				}
				if (eSprite->Attribute("visible") != NULL) {
					if (strcmp(eSprite->Attribute("visible"), "true") == 0) {
						subWidget->setVisible(true);
					} else if (strcmp(eSprite->Attribute("visible"), "false") == 0) {
						subWidget->setVisible(false);
					} else if (eSprite->IntAttribute("visible") == 0) {
						subWidget->setVisible(false);
					} else if (eSprite->IntAttribute("visible") == 1) {
						subWidget->setVisible(true);
					}
				}

				for (tinyxml2::XMLElement* eAction = eSprite->FirstChildElement("action"); eAction != NULL; eAction = eAction->NextSiblingElement("action")) {
					CCAction* pAction = CreateAction(it->c_str(), eAction, eConfig, &ammend);

					if (pAction != NULL) {
						if (isDebug && testDelaySecond > 0) {
							// 延迟执行此动作
							pAction = CCSequence::create(CCDelayTime::create(testDelaySecond), pAction, NULL);
						}
					}

					if (subWidget->getContainerNode() != NULL) {
						subWidget->getContainerNode()->runAction(pAction);
					}
				}
			}
		}
	}
	
	// replace sprite
	// @return: handle 0表示失败
	int ActionTemplateTable::RunAeAction(CCNode* container, AEParamAmmend& ammend, const std::string& fileName, CCCallFunc* onActionBefore, CCCallFunc* onActionDone) {
		CalcCostMS("");
		unsigned long size;
		unsigned char* pData = CCFileUtils::sharedFileUtils()->getFileData(fileName.c_str(), "rb", &size);
		tinyxml2::XMLDocument doc;
		char* szFileStrBuff = new char[size + 1];
		szFileStrBuff[size] = 0;
		memcpy(szFileStrBuff, pData, size);
		delete[] pData;

		sprintf(s_szBuff, "[AE] ReadFileData of %s", fileName.c_str());
		CalcCostMS(s_szBuff);

		doc.ParseDeep(szFileStrBuff, 0 );
		sprintf(s_szBuff, "[AE] XmlParseDeep of %s", fileName.c_str());
		CalcCostMS(s_szBuff);

		int ret = 0;
		if (doc.Error()) {
			ret = 0;
		} else {
			ret = RunAeAction(container, ammend, doc.RootElement(), onActionBefore, onActionDone);
		}
		sprintf(s_szBuff, "[AE] RunAction of %s", fileName.c_str());
		CalcCostMS(s_szBuff);

		return ret;
	}

	int ActionTemplateTable::RunAeAction(CCNode* container, std::map<std::string, CCNode*> sprites, tinyxml2::XMLElement* eAction, CCCallFunc* onActionBefore, CCCallFunc* onActionDone) {
		AEParamAmmend ammend;
		ammend.sprites = sprites;
		return RunAeAction(container, ammend, eAction, onActionBefore, onActionDone);
	}

	int ActionTemplateTable::RunAeAction(CCNode* container, std::map<std::string, CCNode*> sprites, const std::string& fileName, CCCallFunc* onActionBefore, CCCallFunc* onActionDone) {
		AEParamAmmend ammend;
		ammend.sprites = sprites;
		return RunAeAction(container, ammend, fileName, onActionBefore, onActionDone);
	}

	// @return: handle 0表示失败
	int ActionTemplateTable::RunAeAction(CCNode* container, const std::string& fileName, CCCallFunc* onActionBefore, CCCallFunc* onActionDone) {
		AEParamAmmend ammend;
		return RunAeAction(container, ammend, fileName, onActionBefore, onActionDone);
	}


	int ActionTemplateTable::RunAeAction(CCNode* container, AEParamAmmend& ammend, tinyxml2::XMLElement* eRoot, CCCallFunc* onActionBefore, CCCallFunc* onActionDone) {
		ActionSpriteHolder* pHolder = new ActionSpriteHolder;
		if (onActionDone) {
			pHolder->SetOnActionDone(onActionDone);
			pHolder->SetSpeed(playSpeed);
		}
		pHolder->SetAtt(this);
		pHolder->SetContainer(container);
		int sid = 0;
		static int sprite_tag_id = 0;
		float configSpeed = 1;
		while (holders.find(sid = NextSeed()) != holders.end()) {}
		
		float totalSecond = 2;
		float testDelaySecond = 0;
		tinyxml2::XMLElement* eConfig = eRoot->FirstChildElement("config");
		if (eConfig != NULL) {
			if (eConfig->Attribute("totalSecond") != NULL) {
				totalSecond = eConfig->FloatAttribute("totalSecond");
			}
			if (ammend.duration > 0) { // 替换 totalSecond
				totalSecond = ammend.duration;
			}
			if (eConfig->Attribute("testDelaySecond") != NULL) {
				testDelaySecond = eConfig->FloatAttribute("testDelaySecond");
				totalSecond += testDelaySecond;
			}
			if (!ammend.pParamInner->isSubAE && eConfig->Attribute("nextAE") != NULL) {
				pHolder->SetNextAE(std::string(eConfig->Attribute("nextAE")));
			}
			pHolder->SetLeftSecond(totalSecond);
			if (eConfig->Attribute("playSpeed") != NULL && strlen(eConfig->Attribute("playSpeed")) != 0) {
				configSpeed = eConfig->FloatAttribute("playSpeed");
				pHolder->SetSpeed(playSpeed * configSpeed);
			}
			if (isDebug && !ammend.pParamInner->isSubAE) {
				if (eConfig->Attribute("testBackGround") != NULL && strlen(eConfig->Attribute("testBackGround")) != 0) {
					CCNode* testBackGroundSprite = CCSprite::create(eConfig->Attribute("testBackGround"));
					if (testBackGroundSprite != NULL) {
						testBackGroundSprite->setScaleX(CCEGLView::sharedOpenGLView()->getFrameSize().width / testBackGroundSprite->getContentSize().width);
						testBackGroundSprite->setScaleY(CCEGLView::sharedOpenGLView()->getFrameSize().height / testBackGroundSprite->getContentSize().height);
						testBackGroundSprite->setPosition(ccp(CCEGLView::sharedOpenGLView()->getFrameSize().width / 2, 
							CCEGLView::sharedOpenGLView()->getFrameSize().height / 2));
						pHolder->AddNode(testBackGroundSprite);
						container->addChild(testBackGroundSprite);
						testBackGroundSprite->setVisible(false);
						testBackGroundSprite->runAction(CCShow::create());
					}
				}

				{
					char szTmp[256];
					{
						snprintf(szTmp, sizeof(szTmp), "TotalSecond = %.1f", totalSecond);
						CCLabelTTF* pShowTotalSecond = CCLabelTTF::create(szTmp, "Arial", 44);
						pShowTotalSecond->setColor(ccc3(255, 0, 0));
						pShowTotalSecond->setAnchorPoint(ccp(0, 0.5));
						pShowTotalSecond->setPosition(ccp(60, CCEGLView::sharedOpenGLView()->getFrameSize().height - 125));
						container->addChild(pShowTotalSecond);
						pHolder->AddNode(pShowTotalSecond);
						pShowTotalSecond->setVisible(false);
						pShowTotalSecond->runAction(CCShow::create());
					}
					{
						snprintf(szTmp, sizeof(szTmp), "Cur Second =  0.0");
						CCLabelTTF* pShowCurSecond = CCLabelTTF::create(szTmp, "Arial", 44);
						pShowCurSecond->setPosition(ccp(60, CCEGLView::sharedOpenGLView()->getFrameSize().height - 75));
						pShowCurSecond->setColor(ccc3(255, 0, 0));
						pShowCurSecond->setAnchorPoint(ccp(0, 0.5));
						container->addChild(pShowCurSecond);
						pHolder->AddShowCurSecondTTF(pShowCurSecond);
						pShowCurSecond->setVisible(false);
						pShowCurSecond->runAction(CCShow::create());
					}
					{
						snprintf(szTmp, sizeof(szTmp), "Play Speed =  %.1f", playSpeed);
						CCLabelTTF* pShowSpeed = CCLabelTTF::create(szTmp, "Arial", 44);
						pShowSpeed->setPosition(ccp(60, CCEGLView::sharedOpenGLView()->getFrameSize().height - 25));
						pShowSpeed->setColor(ccc3(255, 0, 0));
						pShowSpeed->setAnchorPoint(ccp(0, 0.5));
						container->addChild(pShowSpeed);
						pHolder->AddShowCurSecondTTF(pShowSpeed);
						pShowSpeed->setVisible(false);
						pShowSpeed->runAction(CCShow::create());
					}
				}
			}
		}

		for (tinyxml2::XMLElement* eSprite = eRoot->FirstChildElement("sprite"); eSprite != NULL; eSprite = eSprite->NextSiblingElement("sprite")) 
		{
			bool isNewCreatedSprite = false;
			CCNode* sprite = NULL;
			if (eSprite->Attribute("name") != NULL && ammend.sprites.find(eSprite->Attribute("name")) != ammend.sprites.end()) {
				sprite = ammend.sprites[eSprite->Attribute("name")];
				if (eSprite->Attribute("rotate") != NULL && eSprite->FloatAttribute("rotate") != 0) {
					sprite = RenderTargetRotateSprite::create((CCSprite*)sprite, eSprite->FloatAttribute("rotate"));
				}
			} else {
				if (eSprite->Attribute("res") != NULL && strlen(eSprite->Attribute("res")) != 0) {
					bool isCloseButton = eSprite->Attribute("isCloseButton") != NULL && strlen(eSprite->Attribute("isCloseButton")) != 0 && eSprite->IntAttribute("isCloseButton");
					std::string openNewAEFileName;
					if (!ammend.pParamInner->isSubAE && eSprite->Attribute("openNewAEButton") != NULL && strlen(eSprite->Attribute("openNewAEButton")) != 0) {
						openNewAEFileName = eSprite->Attribute("openNewAEButton");
					}
					if (isCloseButton || openNewAEFileName.size() > 0) 
					{
						AEButtonHandler* handler = AEButtonHandler::create(this, container, (isCloseButton ? sid : 0), openNewAEFileName);
						CCMenuItemImage* menuItem = CCMenuItemImage::create(eSprite->Attribute("res"), NULL, handler, menu_selector(AEButtonHandler::handle));
						menuItem->addChild(handler);

						sprite = CCMenu::create(menuItem, NULL);
					} else {
						std::string spriteName = eSprite->Attribute("name");
						if (ammend.resReplaced.find(spriteName) != ammend.resReplaced.end()) {
							sprite = CCSprite::create(ammend.resReplaced[spriteName].c_str());
						} else {
							sprite = CCSprite::create(eSprite->Attribute("res"));
						}
					}
				} else {
					sprite = CCSprite::create();
				}
				if (eSprite->Attribute("ry") != NULL && strlen(eSprite->Attribute("ry")) != 0) {
					CCSprite* p = dynamic_cast<CCSprite*>(sprite);
					if (p != NULL) {
						std::string ryFileName = eSprite->Attribute("ry");
						sprite = GS_RegionShake::create(p, 40, ryFileName);
						if (sprite != NULL) {
							((GS_RegionShake*)sprite)->trigger();
						}
					} else {
						CCLog("Error: ry file, must not be isCloseButton");
					}
				}

				float rotate = 0;
				if (eSprite->Attribute("rotate") != NULL && eSprite->FloatAttribute("rotate") != 0) {
					rotate = eSprite->FloatAttribute("rotate");
				}
				if (eSprite->Attribute("aeRenderTarget") != NULL && strlen(eSprite->Attribute("aeRenderTarget")) != 0
					&& eSprite->Attribute("aeRenderTargetSize") != NULL && strlen(eSprite->Attribute("aeRenderTargetSize")) != 0) 
				{
					CCPoint size = ActionParam::GetPointParam(eSprite->Attribute("aeRenderTargetSize"), eConfig, &ammend);
					CCPoint center = ccp(384, 512);
					if (eSprite->Attribute("aeRenderTargetCenter") != NULL && strlen(eSprite->Attribute("aeRenderTargetCenter")) != 0) {
						center = ActionParam::GetPointParam(eSprite->Attribute("aeRenderTargetCenter"), eConfig, &ammend);
					}
					CCPoint region = ccp(0, 0);
					if (eSprite->Attribute("aeRenderTargetRegion") != NULL && strlen(eSprite->Attribute("aeRenderTargetRegion")) != 0) {
						region = ActionParam::GetPointParam(eSprite->Attribute("aeRenderTargetRegion"), eConfig, &ammend);
					}
					CCSprite* container = CCSprite::create();
					container->setContentSize(CCSize(768, 1024));
					std::string fileName = eSprite->Attribute("aeRenderTarget");
					int handle = RunAeAction(container, fileName);
					pHolder->rtChildHandles.push_back(handle);
					sprite = RenderTargetRotateSprite::create(container, rotate, size, center, region);
				} else if (rotate != 0) {
					sprite = RenderTargetRotateSprite::create((CCSprite*)sprite, eSprite->FloatAttribute("rotate"));
				}

				if (sprite == NULL) {
					continue;
				}
				
				if (eSprite->Attribute("label") != NULL && strlen(eSprite->Attribute("label")) > 0) {
					CCLabelTTF* pTTF = CCLabelTTF::create(ActionParam::GetStringParam(eSprite->Attribute("label"), eConfig, &ammend).c_str(), 
						eSprite->Attribute("font"), eSprite->IntAttribute("fontSize"));
					if (pTTF != NULL) {
						if (eSprite->Attribute("fontColor") != NULL && strlen(eSprite->Attribute("fontColor")) > 0) {
							int r,g,b = 255;
							sscanf(eSprite->Attribute("fontColor"), "(%d,%d,%d)", &r, &g, &b);
							pTTF->setColor(ccc3(r, g, b));
						} else {
							pTTF->setColor(ccc3(255, 255, 255));
						}
						sprite->addChild(pTTF);
					}
				}

				isNewCreatedSprite = true;
			}

			if (dynamic_cast<CCSprite*>(sprite) != NULL && eSprite->Attribute("isGridEffect") != NULL && eSprite->IntAttribute("isGridEffect") > 0) {
				sprite = GridEffectSprite::create((CCSprite*)sprite);
				ammend.pParamInner->gridEffectSprite = (GridEffectSprite*)sprite;
			}

			CCBlendProtocol* pBlendProtocol = dynamic_cast<CCBlendProtocol*>(sprite);
			if (pBlendProtocol != NULL) {
				if (eSprite->Attribute("srcBlendFactor") != NULL || eSprite->Attribute("dstBlendFactor") != NULL) {
					ccBlendFunc blendFunc = { static_cast<GLenum>(transGLBlendFactor(eSprite->Attribute("srcBlendFactor"), GL_ONE)), static_cast<GLenum>(transGLBlendFactor(eSprite->Attribute("dstBlendFactor"), GL_ONE_MINUS_SRC_ALPHA)) };
					pBlendProtocol->setBlendFunc(blendFunc);
				}
			}

			if (eSprite->Attribute("isHide") != NULL && strlen(eSprite->Attribute("isHide")) != 0) {
				if (eSprite->IntAttribute("isHide") != 0) {
					sprite->setVisible(false);
				}
			}
			if (isNewCreatedSprite) {
				sprite->setZOrder(eSprite->IntAttribute("zOrder"));
			}
			if (eSprite->Attribute("pos") != NULL) {
				sprite->setPosition(ActionParam::GetPointParam(eSprite->Attribute("pos"), eConfig, &ammend));
			}
			if (isNewCreatedSprite && eSprite->Attribute("scale") != NULL) {
				sprite->setScale(eSprite->FloatAttribute("scale"));
			}
			if (isNewCreatedSprite && eSprite->Attribute("anchorPos") != NULL) {
				sprite->setAnchorPoint(ActionParam::GetPointParam(eSprite->Attribute("anchorPos"), eConfig, &ammend));
			}
			if (sprite->getParent() == NULL) {
				sprite->setTag(++sprite_tag_id);
				container->addChild(sprite);
				tagMap[eSprite->Attribute("name")] = sprite_tag_id;
			}
			if (eSprite->Attribute("extraDeviceScale") != NULL && strlen(eSprite->Attribute("extraDeviceScale")) > 0) {
				CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
				if (frameSize.width != 768) { // iphone 额外缩放
					sprite->setScale(sprite->getScale() * eSprite->FloatAttribute("extraDeviceScale"));
				}
			}
			pHolder->AddNode(sprite);
			if (ammend.alignSpriteName != "" && eSprite->Attribute("name") == ammend.alignSpriteName) {
				ammend.pParamInner->alignSpritePos = sprite->getPosition();
			}

			for (tinyxml2::XMLElement* eAction = eSprite->FirstChildElement("action"); eAction != NULL; eAction = eAction->NextSiblingElement("action")) {
				CCAction* pAction = CreateAction(eSprite->Attribute("name"), eAction, eConfig, &ammend);

				if (pAction != NULL) {
					if (isDebug && testDelaySecond > 0) {
						// 延迟执行此动作
						pAction = CCSequence::create(CCDelayTime::create(testDelaySecond), pAction, NULL);
					}
					if (ammend.pParamInner->init_delay > 0) { // init_delay
						pAction = CCSequence::create(CCDelayTime::create(ammend.pParamInner->init_delay), pAction, NULL);
					}

					if (playSpeed != 1 || configSpeed != 1) {
						CCActionInterval* pInterval = dynamic_cast<CCActionInterval*>(pAction);
						if (pInterval != NULL) {
							pAction = CCSpeed::create(pInterval, playSpeed * configSpeed);
						}
					}

					sprite->retain();
					pAction->retain();
					pHolder->actions.push_back(std::make_pair(sprite, pAction));
				}
			}
		}

		if (onActionBefore != NULL) {
			onActionBefore->execute();
		}

		holders[sid] = pHolder;
		return sid;
	}
}