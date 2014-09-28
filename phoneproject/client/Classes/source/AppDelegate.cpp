#include "AppDelegate.h"

#include <vector>
#include <string>

#include "Configs.h"
#include "EventMgr.h"
#include "AssetsUpdateMgr.h"
//#include "MapMgr.h"
#include "CocosGUIUtils.h"
#include "gutil.h"

#include "script_support/CCScriptSupport.h"
#include "CCLuaEngine.h"

#include <fcntl.h>
#pragma warning (disable: 4996)

//================================
/*
* 网络底层相关头文件和命名空间
*/
#ifdef WIN32
#include "gnconf.h"
#include <winbase.h>
//#include "ClientManager.h"
#include "gnpollio.h"
#include <winbase.h>
#include "gnsecure.h"
#else
#include "conf.h"
#include "ClientManager.h"
#include "pollio.h"
#include "threadusage.h"
#include "security.h"
#endif

USING_NS_CC;
using namespace std;
using namespace GNET;

#define TICK_DELAY 20
//#define CCLOG_FILE_OUTPUT

//////////////////////////////////////////////
// 
class CCObjectTick : public CCObject
{
public:
	//=============================================
	/*
	 * 主线程tick函数
	*/
	void tickCallback(float dt)
	{
		PollIO::Poll(0);
		EventMgr::sharedMgr()->tick(dt);

		if (++m_tick_count >= 1000/TICK_DELAY)
		{
			m_tick_count = 0;
			DoLuaString("Global:Tick",dt);
		}
	}
	//=============================================
	virtual bool init()
	{
		m_tick_count = 0;
		return true;
	}
	CREATE_FUNC(CCObjectTick);
private:
	unsigned short m_tick_count;
};

static CCObjectTick* s_pObjectTick = NULL;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	
	std::string writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();

#ifdef CCLOG_FILE_OUTPUT
	std::string output_path = writablePath + "output.log";
	int fd = open(output_path.c_str(), O_CREAT|O_RDWR|O_TRUNC,0600);
	if (-1 == fd)
		exit(-1);
	close(1);
	dup2(fd,1);
	close(fd);

	std::string err_path = writablePath + "error.log";
	fd = open(err_path.c_str(), O_CREAT|O_RDWR|O_TRUNC,0600);
	if (-1 == fd)
		exit(-1);
	close(2);
	dup2(fd,2);
	close(fd);
#endif

    // initialize director
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

	pDirector->setOpenGLView(pEGLView);

	pDirector->setProjection(kCCDirectorProjection2D);

    // Set the design resolution
    //pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);

	CCSize frameSize = pEGLView->getFrameSize();

	float f = ((float)frameSize.width) / frameSize.height;
	// Set the design resolution

	if(f <= 768.f / 1024 + 0.01f)
	{
		pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionExactFit);
	}
	else
	{
		pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionExactFit);
	}
    
    vector<string> searchPath;

    // In this demo, we select resource according to the frame's height.
    // If the resource size is different from design resolution size, you need to set contentScaleFactor.
    // We use the ratio of resource's height to the height of design resolution,
    // this can make sure that the resource's height could fit for the height of design resolution.

    // if the frame's height is larger than the height of medium resource size, select large resource.
	/*if (frameSize.height > mediumResource.size.height)
	{
        searchPath.push_back(largeResource.directory);

        pDirector->setContentScaleFactor(MIN(largeResource.size.height/designResolutionSize.height, largeResource.size.width/designResolutionSize.width));
	}
    // if the frame's height is larger than the height of small resource size, select medium resource.
    else if (frameSize.height > smallResource.size.height)
    {
        searchPath.push_back(mediumResource.directory);
        
        pDirector->setContentScaleFactor(MIN(mediumResource.size.height/designResolutionSize.height, mediumResource.size.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium resource size, select small resource.
	else
    {
        searchPath.push_back(smallResource.directory);

        pDirector->setContentScaleFactor(MIN(smallResource.size.height/designResolutionSize.height, smallResource.size.width/designResolutionSize.width));
    }*/

	if (frameSize.height == 1136 && frameSize.width == 640) // iphone5
	{
		searchPath.push_back("..//Documents//iphone5");
		searchPath.push_back("iphone5");
		searchPath.push_back("..//Documents//iphone4");
		searchPath.push_back("iphone4");
	}
	else 	if (frameSize.height == 960 && frameSize.width == 640) // iphone4
	{
		searchPath.push_back("..//Documents//iphone4");
		searchPath.push_back("iphone4");
	}
	else if ((frameSize.height == 2048 && frameSize.width == 1536) || 
		(frameSize.height == 1024 && frameSize.width == 768))
	{
		searchPath.push_back("..//Documents//ipad");
		searchPath.push_back("ipad");
	}

	searchPath.push_back("..//Documents//common");
	searchPath.push_back("common");
    
    // set searching path
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);
	pDirector->setContentScaleFactor(1.0f);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

	initGlobalData();

	//tick
	s_pObjectTick = CCObjectTick::create();
	s_pObjectTick->retain();
	//pScene->schedule(schedule_selector(AppDelegate::tickCallback), 0.01f);
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(CCObjectTick::tickCallback), s_pObjectTick, 1.f / TICK_DELAY, false);
	//==========================================================================================

	/*AssetsUpdateManager::update_param up;
	up.resource_path = "../ResourcesUpdate/";
	up.download_path = "../download/";
	up.md5_file = "md5.file";
	up.src = "http://114.245.90.20:9000/Package/";
	up.ret = false;
	up.timeout = 30;
	up.trytime = 2;
	while(true)
	{
		if (AssetsUpdateManager::GetInstance().CheckUpdate(&up))
			break;
		Sleep(1);
	}*/

	//aStar* pStart = GMapMgr::GetInstance()->AStarStart(0,0,1,10);

	// register lua engine
    CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
    CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);

    std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename("scripts/main.lua");
    pEngine->executeScriptFile(path.c_str());

    // create a scene. it's an autorelease object
	//CCScene *pScene = CCScene::create();
	//CCScene *pScene = HelloWorld::scene();

	/*UIWidget* m_Widget = CreateWidgetFromJsonFile(GET_PATH(PATH_UI, "baoshibase.json"));
	m_Widget->setName("login");
	UILayer* m_pUILayer = UILayer::create();
	m_pUILayer->addWidget(m_Widget);
	m_Widget->setPosition(ccp(g_winSize.width/2, g_winSize.height/2));

	pScene->addChild(m_pUILayer);

    // run
    pDirector->runWithScene(pScene);*/

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
