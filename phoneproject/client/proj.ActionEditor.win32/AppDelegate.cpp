#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(1024, 768);

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    pDirector->setOpenGLView(pEGLView);
	pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionExactFit);
	pDirector->setContentScaleFactor(1.0f);

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 45);

	CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
	vector<string> searchPath;
	if (frameSize.height == 1136 && frameSize.width == 640) // iphone5
	{
		searchPath.push_back("..//Documents//iphone5");
		searchPath.push_back("iphone5");
		searchPath.push_back("..//Documents//iphone4");
		searchPath.push_back("iphone4");
	}
	else if (frameSize.height == 960 && frameSize.width == 640) // iphone4
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

    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

    // run
    pDirector->runWithScene(pScene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
