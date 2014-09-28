#include "AppDelegate.h"
#include "LayerSelectType.h"
#include "LAnimationView.h"
#include <vector>
#include <string>

std::string g_plistFileName;

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

	CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
	std::vector<std::string> searchPath;
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
	CCScene *pScene = LayerSelectType::scene();
	// run
	pDirector->runWithScene(pScene);
	if (g_plistFileName.size() > 0) {
		setLayer(LParticleShow::create(g_plistFileName));
	}

    return true;
}

extern LRESULT my_win_proc(UINT message, WPARAM wParam, LPARAM lParam, BOOL* pProcessed) {
	if (message == 5000) {
		SetWindowPos(CCEGLView::sharedOpenGLView()->getHWnd(), 0, wParam, lParam, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		*pProcessed = 1;
	} else if (message == 5001) {
		setLayer(LParticleShow::create(g_plistFileName));
		*pProcessed = 1;
	}

	return 0;
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
