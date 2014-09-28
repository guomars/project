#include "Configs.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

CCSize g_winSize;
CCPoint g_vPosCenter;
bool g_bShowDebugInfo = false;
char g_szFilePath[256] = {0};
char g_szFilePath2[256] = {0};
char g_szStringWithInt[256] = {0};
char g_szStringWithInt2[256] = {0};
char* g_szDefaultFontName = "黑体";
bool g_bTestMode = false;	// 测试单机模式
bool g_bSoundOn = true;

void initGlobalData()
{
	g_winSize = CCDirector::sharedDirector()->getWinSize();
	g_vPosCenter = ccp(g_winSize.width/2, g_winSize.height/2);

	g_bTestMode = true;
}

void PLAY_SOUND(const char* szFile)
{
	if (g_bSoundOn)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(szFile);
}

void PLAY_MUSIC(const char* szFile)
{
	if (g_bSoundOn)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(szFile, true);
}

const CCSize & GET_WIN_SIZE()
{
	return g_winSize;
}

const CCPoint & GET_POS_CENTOR()
{
	return g_vPosCenter;
}

const char* GET_PATH(const char* strPath, const char* strFileName)
{
	strcpy(g_szFilePath, strPath);
	strcat(g_szFilePath, strFileName);

	return g_szFilePath;
}

const char* GET_PATH2(const char* strPath, const char* strFileName)
{
	strcpy(g_szFilePath2, strPath);
	strcat(g_szFilePath2, strFileName);

	return g_szFilePath2;
}

const char* STRING_WITH_INT(const char * str, int t)
{
	sprintf(g_szStringWithInt,"%s%d",str,t);
	return g_szStringWithInt;
}

const char* STRING_WITH_INT2(const char * str, int t)
{
	sprintf(g_szStringWithInt2,"%s%d",str,t);
	return g_szStringWithInt2;
}

const float GET_CCOBJECT_DISTANCE(CCNode * obj1, CCNode * obj2)
{
	if (!obj1 || !obj2)
		return -1;
	const CCPoint & p1 = obj1->getPosition();
	const CCPoint & p2 = obj2->getPosition();
	return p1.getDistance(p2);
}

const float GET_CCP_DISTANCE(const CCPoint * p1, const CCPoint * p2)
{
	if (!p1 || !p2)
		return 0;

	return p1->getDistance(*p2);
}

const float GET_CCP_ANGLE(const CCPoint * p1, const CCPoint * p2)
{
	if (!p1 || !p2)
		return 0;

	return p1->getAngle(*p2);
}

const float RADIANS_TO_DEGREES(float radius)
{
	return CC_RADIANS_TO_DEGREES(radius);
}

const float DEGREES_TO_RADIANS(float degrees)
{
	return CC_DEGREES_TO_RADIANS(degrees);
}

void SET_NODE_ZORDER(CCNode * node, int zorder)
{
	if (!node) return;

	node->setZOrder(zorder);
}

bool POINT_INT_NODE(CCNode* node, const CCPoint &pt)
{
	if (!node)
		return false;

	CCPoint nsp = node->convertToNodeSpace(pt);
    CCRect bb = node->boundingBox();
    if (nsp.x >= 0.0f && nsp.x <= bb.size.width && nsp.y >= 0.0f && nsp.y <= bb.size.height)
    {
        return true;
    }
    return false;
}

void SET_SPRITE_TEXTURE(CCSprite* sprite, const char *fileName)
{
	if (!sprite) return;

	sprite->initWithFile(fileName);
    sprite->setColor(sprite->getColor());
    sprite->setOpacity(sprite->getOpacity());
}