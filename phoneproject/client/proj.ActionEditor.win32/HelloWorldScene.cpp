#include "HelloWorldScene.h"
#include "ActionStubs.h"
#include "GridSprite.h"
#include "CocoGUILIB/System/CocosGUI.h"
using namespace cocos2d;

extern char* g_SimulateFileName;
static CCNode* s_animationNode;

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

		// load aeditor, template data, every time createScene, so we can update template changed immediately.
		const char* templateXmlFile = "./Editor/template.xml";
		tinyxml2::XMLDocument doc;
		doc.LoadFile(templateXmlFile);
		aeditor::ActionTemplateTable::instance.Init(doc.RootElement(), scene, true);

		CCLOG("%s", aeditor::ActionTemplateTable::instance.ToString().c_str());

        // 'layer' is an autorelease object
		HelloWorld* layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

UILayer* s_pUILayer;

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		s_animationNode = CCNode::create();
		this->addChild(s_animationNode, 6);
		this->setPosition(ccp((winSize.width / 2 - 512), (winSize.height / 2 - 384)));

		s_pUILayer = UILayer::create();
		s_pUILayer->scheduleUpdate();
		this->addChild(s_pUILayer, 100);
		{
			//aeditor::loadFightConf("fight/fight_conf.xml");
			std::string fileName = g_SimulateFileName;
			if (fileName.find(".ry") != std::string::npos) {
				unsigned long size;
				unsigned char* pData = cocos2d::CCFileUtils::sharedFileUtils()->getFileData(fileName.c_str(), "rb", &size);
				tinyxml2::XMLDocument doc;
				char* szBuff = new char[size + 1];
				szBuff[size] = 0;
				memcpy(szBuff, pData, size);
				delete[] pData;

				doc.ParseDeep(szBuff, 0 );
				CCAssert(!doc.Error(), "Read RegionShake Tempalte File Failed !!!!");
				CCSprite* sprite = NULL;
				if (doc.RootElement()->Attribute("testBackGround") != NULL && strlen(doc.RootElement()->Attribute("testBackGround")) != 0) {
					sprite = CCSprite::create(doc.RootElement()->Attribute("testBackGround"));
				}

				if (sprite == NULL) {
					sprite = new CCSprite();
				}
				GridSprite::setDebug();
				GS_RegionShake* xxx = GS_RegionShake::create(sprite, 40, doc.RootElement());
				xxx->setPosition(ccp(sprite->getContentSize().width / 2, sprite->getContentSize().height / 2));
				xxx->trigger();
				this->addChild(xxx);
			} else if (fileName.find(".ue") != std::string::npos) {
				unsigned long size;
				unsigned char* pData = CCFileUtils::sharedFileUtils()->getFileData(fileName.c_str(), "rb", &size);
				tinyxml2::XMLDocument doc;
				char* szBuff = new char[size + 1];
				szBuff[size] = 0;
				memcpy(szBuff, pData, size);
				delete[] pData;

				doc.ParseDeep(szBuff, 0 );
				tinyxml2::XMLElement* eConfig = doc.RootElement()->FirstChildElement("config");

				UIWidget* uiWidget = CCUIHELPER->createWidgetFromJsonFile(eConfig->Attribute("jasonFile"));

				s_pUILayer->addWidget(uiWidget);
				aeditor::ActionTemplateTable::instance.RunUIAction(fileName, uiWidget);
			} else if (fileName.find(".ae") != std::string::npos) {
				aeditor::ActionTemplateTable::instance.RunAeAction(s_animationNode, fileName);
			} else if (fileName.find(".se") != std::string::npos) {
				onNextSkillSimulate(this);
			} else {
				assert(0);
			}
		}

        bRet = true;
    } while (0);

    return bRet;
}

static int s_skill_simulate_count = 0;

void HelloWorld::onNextSkillSimulate(CCNode* pSender)
{
	if (++ s_skill_simulate_count > 1) {
		aeditor::ActionTemplateTable::instance.setIsCreateDebugBackground(false);
	}
	std::string fileName = g_SimulateFileName;
	aeditor::AEParamAmmend ammend;
	float totalSecond = aeditor::ActionTemplateTable::instance.RunSkillAction(fileName, this, ammend);
	this->runAction(CCSequence::create(CCDelayTime::create(totalSecond), CCCallFuncN::create(this, callfuncN_selector(HelloWorld::onNextSkillSimulate)), NULL));
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

