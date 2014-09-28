#ifndef __CONFIGS_H__
#define __CONFIGS_H__

#include "cocos2d.h"
#include <vector>
USING_NS_CC;
using namespace std;

class MPEffect;

#define DESIGN_RESOLUTION_320X480    0
#define DESIGN_RESOLUTION_768X1024   1
#define DESIGN_RESOLUTION_1536X2048  2
#define DESIGN_RESOLUTION_480X320    3
#define DESIGN_RESOLUTION_1024X768   4
#define DESIGN_RESOLUTION_2048X1536  5

/* If you want to switch design resolution, change next line */
#define TARGET_DESIGN_RESOLUTION_SIZE  DESIGN_RESOLUTION_1024X768

#if (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_320X480)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(320, 480);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_768X1024)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(768, 1024);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_1536X2048)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(1536, 2048);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_480X320)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(480, 320);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_1024X768)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(1024, 768);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_2048X1536)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(2048, 1536);
#else
#error unknown target design resolution!
#endif

enum 
{
	DEVICE_IPAD = 0,
	DEVICE_IPHONE4,
	DEVICE_IPHONE5,

	NUM_DEVICE,
};

extern CCSize g_winSize;
extern CCPoint g_vPosCenter;
extern bool g_bShowDebugInfo;
extern bool g_bTestMode;
extern char g_szFilePath[256];
extern char* g_szDefaultFontName;

#define CURRENT_VERSION 1

#define POLYGON_LENGTH 5
#define PI	3.14159265f

//=============================== Sound 
#define LOAD_SOUND CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect

//=============================== utilities
#define SaveStringToXML CCUserDefault::sharedUserDefault()->setStringForKey  
#define SaveIntegerToXML CCUserDefault::sharedUserDefault()->setIntegerForKey  
#define SaveBooleanToXML CCUserDefault::sharedUserDefault()->setBoolForKey  
#define LoadStringFromXML CCUserDefault::sharedUserDefault()->getStringForKey  
#define LoadIntegerFromXML CCUserDefault::sharedUserDefault()->getIntegerForKey  
#define LoadBooleanFromXML CCUserDefault::sharedUserDefault()->getBoolForKey

//=============================== Global Data
void initGlobalData();

//以下是lua也能调用的函数
void PLAY_SOUND(const char* szFile);
void PLAY_MUSIC(const char* szFile);
const char* GET_PATH(const char* strPath, const char* strFileName);
const char* GET_PATH2(const char* strPath, const char* strFileName);
const char* STRING_WITH_INT(const char * str, int t);
const char* STRING_WITH_INT2(const char * str, int t);

const CCSize & GET_WIN_SIZE();

const CCPoint & GET_POS_CENTOR();

const float GET_CCOBJECT_DISTANCE(CCNode * obj1, CCNode * obj2);

const float GET_CCP_DISTANCE(const CCPoint * p1, const CCPoint * p2);

const float GET_CCP_ANGLE(const CCPoint * p1, const CCPoint * p2);

const float RADIANS_TO_DEGREES(float radius);

const float DEGREES_TO_RADIANS(float degrees);

void SET_NODE_ZORDER(CCNode * node, int zorder);

bool POINT_INT_NODE(CCNode* node, const CCPoint &pt);

void SET_SPRITE_TEXTURE(CCSprite* node, const char *fileName);

#endif  // __CONFIGS_H__