#include "LAnimationView.h"
#include "LayerSelectType.h"

static CCPoint s_tCurPos = CCPointZero;
static std::string s_animationDir = "effect/animation";
static std::string s_particleDir = "effect/particle";

static bool IsDirectory(const char *pDir)  
{  
	char szCurPath[500];  
	ZeroMemory(szCurPath, 500);  
	sprintf_s(szCurPath, 500, "%s//*", pDir);  
	WIN32_FIND_DATAA FindFileData;        
	ZeroMemory(&FindFileData, sizeof(WIN32_FIND_DATAA));  
  
	HANDLE hFile = FindFirstFileA(szCurPath, &FindFileData); /**< find first file by given path. */  
  
	if( hFile == INVALID_HANDLE_VALUE )   
	{  
		FindClose(hFile);  
		return FALSE; /** 如果不能找到第一个文件，那么没有目录 */  
	}else  
	{     
		FindClose(hFile);  
		return TRUE;  
	}  
      
}

bool LAnimationView::init() {
	char szBuff[1024];

	{
		std::wstring wstrReturn = std::wstring(L"返回");
		char* strReturn = cc_utf16_to_utf8((const unsigned short *)wstrReturn.c_str(), wstrReturn.size(), NULL, NULL);
		CCLabelTTF* label = CCLabelTTF::create(strReturn, "SimHei", 32);
		menuItemReturn = CCMenuItemLabel::create(label, this, menu_selector(LAnimationView::onBtnReturn));
		CCMenu* menu = CCMenu::create(menuItemReturn, NULL);
		menu->setPosition(950, 40);
		this->addChild(menu);
	}

	menuItems = CCArray::create();
	menuItems->retain();

	std::vector<std::string> files;
	// 遍历文件
	char szCurPath[MAX_PATH];       //用于定义搜索格式  
	_snprintf(szCurPath, MAX_PATH, "./common/%s//*.*", isPariticle ? s_particleDir.c_str() : s_animationDir.c_str()); //匹配格式为*.*,即该目录下的所有文件  
	WIN32_FIND_DATAA FindFileData;        
	ZeroMemory(&FindFileData, sizeof(WIN32_FIND_DATAA));  
	HANDLE hFile = FindFirstFileA(szCurPath, &FindFileData);  
	BOOL IsFinded = TRUE;  
	while(IsFinded)  
	{   
		if( strcmp(FindFileData.cFileName, ".") && strcmp(FindFileData.cFileName, "..") ) //如果不是"." ".."目录  
		{  
			std::string strFileName = FindFileData.cFileName;  
			std::string strTemp;  
			strTemp = strFileName;  
			if( IsDirectory(strFileName.c_str()) ) //如果是目录，则递归地调用  
			{     
				// 忽略子目录
			}  
			else  
			{  
				if (strFileName.find(".plist") != std::string::npos) {
					files.push_back(strFileName);
				}
			}  
		}
		IsFinded = FindNextFileA(hFile, &FindFileData); //递归搜索其他的文件 
	}  
	FindClose(hFile);  

	int i = 0;
	for (std::vector<std::string>::iterator it = files.begin(); it != files.end(); ++it) {
		sprintf(szBuff, "%02d. %s", (i+1), it->c_str());
		CCLabelTTF* label = CCLabelTTF::create(szBuff, "SimHei", 32);
		CCMenuItemLabel* menuItem = CCMenuItemLabel::create(label, this, menu_selector(LAnimationView::onBtnSelectFile));
		menuItem->setPosition(ccp(0, 1024 + (i++) * (-40) - 20));
		menuItem->setAnchorPoint(ccp(0, 1));
		menuItems->addObject(menuItem);
	}

	m_menu = CCMenu::createWithArray(menuItems);
	m_menu->setContentSize(CCSize(200, i * 40));
	m_menu->setPosition(CCPointZero);
	this->addChild(m_menu);

	setTouchEnabled(true);
	return true;
}

void LAnimationView::onBtnSelectFile( CCObject* sender )
{
	CCObject* child;
	CCARRAY_FOREACH(menuItems, child)
	{
		bool isSelect = sender == child;
		CCMenuItemLabel* cur = (CCMenuItemLabel*)child;
		cur->setColor(isSelect ? ccc3(255, 0, 0) : ccc3(255, 255, 255));

		if (isSelect) { // 播放
			if (m_play != NULL) {
				this->removeChild(m_play);
				m_play = NULL;
			}

			if (isPariticle) {
				std::string tmp = ((CCLabelTTF*)cur->getLabel())->getString();
				int pos = tmp.find(" ");
				std::string path = s_particleDir;
				path += "/";
				path += tmp.substr(pos + 1);
				m_play = CCParticleSystemQuad::create(path.c_str());
				if (m_play != NULL) {
					m_play->setPosition(512, 512);
					this->addChild(m_play);
				}
			} else {
				std::string prefix;

				char szBuff[128];
				std::string tmp = ((CCLabelTTF*)cur->getLabel())->getString();
				int pos = tmp.find(" ");
				std::string path = s_animationDir;
				path += "/";
				path += tmp.substr(pos + 1);
				CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(path.c_str());
				CCArray* animFrames = CCArray::create();
				// let us guess
				std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(path.c_str());
				CCDictionary *dict = CCDictionary::createWithContentsOfFileThreadSafe(fullPath.c_str());
				if (dict != 0) {
					dict = (CCDictionary*)dict->objectForKey("frames");
					if (dict != 0 && dict->count() > 0) {
						CCDictElement* pElement = NULL;
						CCDICT_FOREACH(dict, pElement) {
							std::string spriteFrameName = pElement->getStrKey();
							int guessPrefixNameCount = spriteFrameName.size() - 6;
							if (guessPrefixNameCount > 0) { // 6 = "01.png"
								prefix = spriteFrameName.substr(0, guessPrefixNameCount);
							}
							break;
						}

						if (prefix.size() > 0) {
							for (int i = 1; i < 99; ++i) {
								sprintf(szBuff, "%s%02d.png", prefix.c_str(), i);
								CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szBuff);
								if (frame == 0) break;

								animFrames->addObject(frame);
							}
						}
					}
				}
				dict->release();
				CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0);
				animation->setDelayPerUnit(0.1); // todo confirm
				animation->setLoops(999999);

				m_play = CCSprite::create();
				if (m_play != NULL) {
					m_play->setPosition(512, 512);
					m_play->runAction(CCAnimate::create(animation));
					this->addChild(m_play);
				}
			}
		}
	}
}

void LAnimationView::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	m_tBeginPos = touch->getLocation();    
}

void LAnimationView::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	CCPoint touchLocation = touch->getLocation();    
	float nMoveY = touchLocation.y - m_tBeginPos.y;

	CCPoint curPos  = m_menu->getPosition();
	CCPoint nextPos = ccp(curPos.x, curPos.y + nMoveY);

	if (nextPos.y < 0.0f)
	{
		m_menu->setPosition(CCPointZero);
		return;
	}

	if (nextPos.y > ((menuItems->count() + 1)* 40 - 1024))
	{
		m_menu->setPosition(ccp(0, ((menuItems->count() + 1) * 40 - 1024)));
		return;
	}

	m_menu->setPosition(nextPos);
	m_tBeginPos = touchLocation;
	s_tCurPos   = nextPos;
}

void LAnimationView::onBtnReturn( CCObject* sender )
{
	setLayer(LayerSelectType::create());
}

void LParticleShow::ccTouchEnded( CCSet *pTouches, CCEvent *pEvent )
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	m_particleSystemQuad->setPosition(touch->getLocationInView());
}
