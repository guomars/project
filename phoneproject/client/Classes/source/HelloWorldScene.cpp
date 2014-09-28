#include "HelloWorldScene.h"
#include "ActionStubs.h"
#include "GridSprite.h"
#include "CocoGUILIB/System/CocosGUI.h"
#include "Configs.h"
#include "CocosGUIUtils.h"
using namespace cocos2d;

extern char* g_SimulateFileName;
static CCNode* s_animationNode;

static CCScene* l_Scene = NULL;

CCScene* HelloWorld::scene()
{
   CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);
		l_Scene = scene;
		HelloWorld *layer = HelloWorld::create();
		CC_BREAK_IF(! layer);
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
        CC_BREAK_IF(! CCLayerColor::initWithColor(ccc4(0,0,0,255)));
		m_pUILayer = UILayer::create();
		m_pUILayer->scheduleUpdate();
		this->addChild(m_pUILayer);

		//m_actionRunner = aeditor::ActionTemplateTable::create("aeditor/template.xml", l_Scene);

		m_Widget = CreateWidgetFromJsonFile(GET_PATH(PATH_UI, "baoshibase.json"));
		m_Widget->setName("login");
		m_pUILayer->addWidget(m_Widget);
		m_Widget->setPosition(ccp(g_winSize.width/2, g_winSize.height/2));

        bRet = true;
    } while (0);

    return bRet;
}
