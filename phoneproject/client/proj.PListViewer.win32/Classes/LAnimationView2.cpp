#include "LAnimationView2.h"
#include "LayerSelectType.h"

static CCPoint s_tCurPos = CCPointZero;
static std::string s_animationDir = "effect/animation";
static std::string s_particleDir = "effect/particle";

class XXSprite : public CCSprite
{
	std::string m_fileName;
	bool m_isParticle;
	CCNode* m_child;
	int m_i;
	int m_total;

public:
	XXSprite() : m_isParticle(false), m_child(NULL), m_i(0), m_total(0) {}

	static XXSprite* create(CCLayer* layer, std::string fileName, bool isParticle, int i, int total) {
		XXSprite* ret = new XXSprite();
		ret->init(layer, fileName, isParticle, i, total);
		ret->autorelease();
		return ret;
	}

	virtual bool init(CCLayer* layer, std::string fileName, bool isParticle, int i, int total) {
		CCSprite::init();

		char szBuff[256];
		setContentSize(CCSizeMake(1024.0f / 3, 1024.0f / 3));
		setPosition(ccp(i % 3  * getContentSize().width + getContentSize().width / 2, 
			(2 - i / 3) * getContentSize().height + getContentSize().height / 2));
		sprintf(szBuff, "(%d)%s", (i+1), fileName.c_str());
		CCLabelTTF* label = CCLabelTTF::create(szBuff, "simhei", 26);
		label->setPosition(ccp(getContentSize().width / 2, 30));
		addChild(label);

		m_fileName = fileName;
		m_isParticle = isParticle;
		m_i = i;
		m_total = total;
		layer->addChild(this);

		return true;
	}

	void onParticleEnd() {
		if (m_child != NULL) {
			CCParticleSystemQuad* pQuad = (CCParticleSystemQuad*)m_child;
			if (!pQuad->isActive() && pQuad->getParticleCount() == 0) {
				pQuad->resetSystem();
				this->runAction(CCSequence::create(CCDelayTime::create(1), 
					CCCallFunc::create(this, callfunc_selector(XXSprite::onParticleEnd)), NULL));
			}
		}
	}

	void setOn(bool isOn) {
		char szBuff[256];
		if (!isOn) {
			if (m_child != NULL) {
				removeChild(m_child, true);
				m_child = NULL;
			}
		} else {
			if (m_child == NULL) {
				if (m_isParticle) {
					std::string path = s_particleDir;
					path += "/";
					path += m_fileName;
					CCParticleSystemQuad* pQuad = CCParticleSystemQuad::create(path.c_str());
					pQuad->setPosition(ccp(getContentSize().width / 2, getContentSize().height / 2));
					addChild(pQuad);
					m_child = pQuad;
					if (pQuad->getDuration() > 0) {
						this->runAction(CCSequence::create(CCDelayTime::create(1), 
							CCCallFunc::create(this, callfunc_selector(XXSprite::onParticleEnd)), NULL));
					}
				} else {
					std::string prefix;
					std::string path = s_animationDir;
					path += "/";
					path += m_fileName;
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
					animation->setDelayPerUnit(0.05); // todo confirm
					animation->setLoops(999999);

					CCSprite* pAnimSprite = CCSprite::create();
					pAnimSprite->runAction(CCAnimate::create(animation));
					pAnimSprite->setPosition(ccp(getContentSize().width / 2, getContentSize().height / 2));
					addChild(pAnimSprite);
					m_child = pAnimSprite;
				}
			}
		}
	}
};

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

bool LAnimationView2::init() {
	char szBuff[1024];

	{
		std::wstring wstrReturn = std::wstring(L"返回");
		char* strReturn = cc_utf16_to_utf8((const unsigned short *)wstrReturn.c_str(), wstrReturn.size(), NULL, NULL);
		CCLabelTTF* label = CCLabelTTF::create(strReturn, "SimHei", 32);
		menuItemReturn = CCMenuItemLabel::create(label, this, menu_selector(LAnimationView2::onBtnReturn));
		CCMenu* menu = CCMenu::create(menuItemReturn, NULL);
		menu->setPosition(950, 40);
		this->addChild(menu);
	}

	m_files.clear();
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
					m_files.push_back(strFileName);
				}
			}  
		}
		IsFinded = FindNextFileA(hFile, &FindFileData); //递归搜索其他的文件 
	}  
	FindClose(hFile);  

	int i = 0;
	for (std::vector<std::string>::iterator it = m_files.begin(); it != m_files.end(); ++it) {
		XXSprite* xx = XXSprite::create(this, *it, isPariticle, i++, m_files.size());
	}
	checkOn();

	setTouchEnabled(true);
	return true;
}

void LAnimationView2::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	m_tBeginPos = touch->getLocation();    
}

void LAnimationView2::checkOn() {
	CCObject* curObject;
	CCARRAY_FOREACH(this->getChildren(), curObject) {
		XXSprite* xx = dynamic_cast<XXSprite*>(curObject);
		if (xx == NULL) continue;

		//if (nextPos.y < 0.0f)
		//{
		//	this->setPosition(CCPointZero);
		//	return;
		//}
		//if (nextPos.y > (m_files.size() / 3 - 2) * 1024.0f / 3) {
		//	this->setPosition(ccp(0, (m_files.size() / 3 - 2) * 1024.0f / 3));
		//	return;
		//}
		xx->setOn(xx->getPosition().y + this->getPosition().y > 0
			&& xx->getPosition().y + this->getPosition().y < 1024);
	}
}

void LAnimationView2::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	CCPoint touchLocation = touch->getLocation();    
	float nMoveY = touchLocation.y - m_tBeginPos.y;

	CCPoint curPos  = this->getPosition();
	CCPoint nextPos = ccp(curPos.x, curPos.y + nMoveY);

	if (nextPos.y < 0.0f)
	{
		this->setPosition(CCPointZero);
		return;
	}
	if (nextPos.y > (m_files.size() / 3 - 2) * 1024.0f / 3) {
		this->setPosition(ccp(0, (m_files.size() / 3 - 2) * 1024.0f / 3));
		return;
	}

	this->setPosition(nextPos);
	m_tBeginPos = touchLocation;
	s_tCurPos   = nextPos;

	menuItemReturn->setPosition(menuItemReturn->getPosition().x, menuItemReturn->getPosition().y + curPos.y - getPosition().y);

	checkOn();
}

void LAnimationView2::onBtnReturn( CCObject* sender )
{
	setLayer(LayerSelectType::create());
}