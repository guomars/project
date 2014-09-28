#include "AEAction.h"
#include "ActionStubs.h"
#include "cocoa/CCZone.h"
#include "particle_nodes/CCParticleSystemQuad.h"
#include "particle_nodes/CCParticleExamples.h"
#include "base_nodes/CCNode.h"
#include "cocos2d.h"
#include "GridSprite.h"
#include "GridEffect.h"
#include "SimpleAudioEngine.h"
#include "MPEffect.h"

#ifndef ACTION_EDITOR
#include "DataMgr.h"
#endif

extern std::map<std::string, CCPoint> g_uiNameToOriginalPos;
extern cocos2d::ccFontDefinition getFontDefinition(const std::string& fontXmlPath);

NS_CC_BEGIN

//
// AE_SetData
//
AE_SetData* AE_SetData::create(std::string k, std::string v)
{
	AE_SetData *pRet = new AE_SetData();

	if (pRet) {
		pRet->autorelease();
		pRet->init(k,v);
	}
	return pRet;
}

void AE_SetData::update(float time) {
	CC_UNUSED_PARAM(time);
	CCLog("AE_SetData tag=%d key=%s value=%s",m_pTarget->getTag(),key.c_str(),value.c_str());
#ifndef ACTION_EDITOR
	char tmp[512];
	sprintf(tmp,"%s%d",key.c_str(),m_pTarget->getTag());
	DataMgr::sharedMgr()->SetString(tmp,value.c_str());
#endif
}

CCObject* AE_SetData::copyWithZone(CCZone *pZone) {
	CCZone *pNewZone = NULL;
	AE_SetData *pRet = NULL;

	if (pZone && pZone->m_pCopyObject) {
		pRet = (AE_SetData*) (pZone->m_pCopyObject);
	} else {
		pRet = new AE_SetData();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(pZone);
	
	init(key,value);

	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

bool AE_SetData::init( std::string k, std::string v )
{
	key.swap(k);
	value.swap(v);
	return true;
}

//
// AE_ZOrder
//
AE_ZOrder* AE_ZOrder::create(int zOrder) 
{
	AE_ZOrder *pRet = new AE_ZOrder();

	if (pRet) {
		pRet->autorelease();
		pRet->init(zOrder);
	}
	return pRet;
}

void AE_ZOrder::update(float time) {
	CC_UNUSED_PARAM(time);
	m_pTarget->setZOrder(m_zOrder);
}

CCObject* AE_ZOrder::copyWithZone(CCZone *pZone) {
	CCZone *pNewZone = NULL;
	AE_ZOrder *pRet = NULL;

	if (pZone && pZone->m_pCopyObject) {
		pRet = (AE_ZOrder*) (pZone->m_pCopyObject);
	} else {
		pRet = new AE_ZOrder();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(pZone);
	
	init(m_zOrder);

	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

bool AE_ZOrder::init( int zOrder )
{
	m_zOrder = zOrder;
	return true;
}


//
// AE_PlayWav
//
AE_PlayWav* AE_PlayWav::create(std::string wavFile) 
{
	AE_PlayWav *pRet = new AE_PlayWav();

	if (pRet) {
		pRet->autorelease();
		pRet->init(wavFile);
	}
	return pRet;
}

void AE_PlayWav::update(float time) {
	CC_UNUSED_PARAM(time);

	if (g_ae_isSoundOn) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(wavFile.c_str());
	}
}

CCObject* AE_PlayWav::copyWithZone( CCZone *pZone )
{
	CCZone *pNewZone = NULL;
	AE_PlayWav *pRet = NULL;

	if (pZone && pZone->m_pCopyObject) {
		pRet = (AE_PlayWav*) (pZone->m_pCopyObject);
	} else {
		pRet = new AE_PlayWav();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(pZone);

	init(wavFile);

	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

bool AE_PlayWav::init( std::string wavFile )
{
	this->wavFile = wavFile;
	if (this->wavFile.find("\\") == std::string::npos && this->wavFile.find("/") == std::string::npos) {
		// 写死了，旧MP格式无指定目录
		this->wavFile = "sound/" + this->wavFile;
	}
	return true;
}



//
// GE_Stop
//
GE_Stop* GE_Stop::create() 
{
	GE_Stop *pRet = new GE_Stop();

	if (pRet) {
		pRet->autorelease();
	}
	return pRet;
}

void GE_Stop::update(float time) {
	CC_UNUSED_PARAM(time);
	GridEffectSprite* ges = dynamic_cast<GridEffectSprite*>(m_pTarget);
	if (ges != 0) {
		ges->setGridEffect(GridEffect::create(ges, 1, 0));
	}
}

CCObject* GE_Stop::copyWithZone( CCZone *pZone )
{
	CCZone *pNewZone = NULL;
	GE_Stop *pRet = NULL;

	if (pZone && pZone->m_pCopyObject) {
		pRet = (GE_Stop*) (pZone->m_pCopyObject);
	} else {
		pRet = new GE_Stop();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(pZone);

	CC_SAFE_DELETE(pNewZone);
	return pRet;
}


//
// AE_ChildTagRun
//
AE_ChildTagRun* AE_ChildTagRun::create(int childTag, CCAction* childAction) 
{
	AE_ChildTagRun* pRet = new AE_ChildTagRun();
	if (pRet) {
		pRet->autorelease();
		pRet->init(childTag, childAction);
	}
	return pRet;
}

void AE_ChildTagRun::update(float time) {
	CC_UNUSED_PARAM(time);

	CCNode* pChild = m_pTarget->getChildByTag(m_childTag);
	if (pChild != NULL) {
		CCAction* action = (CCAction*)m_childAction->copy();
		pChild->runAction(action);
	}
}

CCObject* AE_ChildTagRun::copyWithZone( CCZone *pZone )
{
	CCZone *pNewZone = NULL;
	AE_ChildTagRun *pRet = NULL;

	if (pZone && pZone->m_pCopyObject) {
		pRet = (AE_ChildTagRun*) (pZone->m_pCopyObject);
	} else {
		pRet = new AE_ChildTagRun();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(pZone);

	init(m_childTag, m_childAction);

	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

bool AE_ChildTagRun::init( int childTag, CCAction* childAction )
{
	this->m_childTag = childTag;
	this->m_childAction = childAction;
	this->m_childAction->retain();
	return true;
}



//
// AE_Scale
//
AE_Scale* AE_Scale::create(float scale) 
{
	AE_Scale *pRet = new AE_Scale();

	if (pRet) {
		pRet->autorelease();
	}
	pRet->init(scale);

	return pRet;
}

void AE_Scale::update(float time) {
	CC_UNUSED_PARAM(time);
	m_pTarget->setScale(m_scale);
}

CCObject* AE_Scale::copyWithZone(CCZone *pZone) {
	CCZone *pNewZone = NULL;
	AE_Scale *pRet = NULL;

	if (pZone && pZone->m_pCopyObject) {
		pRet = (AE_Scale*) (pZone->m_pCopyObject);
	} else {
		pRet = new AE_Scale();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(pZone);
	pRet->init(m_scale);
	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

bool AE_Scale::init( float scale )
{
	this->m_scale = scale;
	return true;
}


//
// AE_Particle_Plist
//
AE_Particle_Plist* AE_Particle_Plist::create(std::string plist, float scale, CCPoint pos, int zOrder, int tag, tCCPositionType posType, float rotate) 
{
	AE_Particle_Plist *pRet = new AE_Particle_Plist();

	if (pRet) {
		pRet->autorelease();
		pRet->init(plist, scale, pos, zOrder, tag, posType, rotate);
	}

	return pRet;
}

void AE_Particle_Plist::update(float time) {
	CC_UNUSED_PARAM(time);
	// add particle list

	CCParticleSystemQuad* pParticle = CCParticleSystemQuad::create(m_plist.c_str());
	if (pParticle != NULL) {
		pParticle->setPosition(m_pos.x, m_pos.y);
		m_pTarget->addChild(pParticle);
		pParticle->setTag(m_tag);
		pParticle->setZOrder(m_zOrder);
		pParticle->setScale(m_scale);
		pParticle->setRotation(m_rotate);
		pParticle->setPositionType(m_posType);
	}
}

CCObject* AE_Particle_Plist::copyWithZone(CCZone *pZone) {
	CCZone *pNewZone = NULL;
	AE_Particle_Plist *pRet = NULL;

	if (pZone && pZone->m_pCopyObject) {
		pRet = (AE_Particle_Plist*) (pZone->m_pCopyObject);
	} else {
		pRet = new AE_Particle_Plist();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(pZone);
	
	pRet->init(m_plist, m_scale, m_pos, m_zOrder, m_tag, m_posType, m_rotate);
	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

bool AE_Particle_Plist::init( std::string plist, float scale, CCPoint pos, int zOrder, int tag, tCCPositionType posType, float rotate)
{
	this->m_plist = plist;
	this->m_scale = scale;
	this->m_pos = pos;
	this->m_zOrder = zOrder;
	this->m_tag = tag;
	this->m_posType = posType;
	this->m_rotate = rotate;
	return true;
}


//
// AE_Particle_Sys
//
AE_Particle_Sys* AE_Particle_Sys::create(std::string name, std::string res, unsigned int number, float scale, CCPoint pos, int zOrder, int tag) 
{
	AE_Particle_Sys *pRet = new AE_Particle_Sys();

	if (pRet) {
		pRet->autorelease();
		pRet->init(name, res, number, scale, pos, zOrder, tag);
	}

	return pRet;
}

void AE_Particle_Sys::update(float time) {
	CC_UNUSED_PARAM(time);

	CCParticleSystemQuad* pParticle = NULL;
	if (m_name == "CCParticleFire") {
		pParticle = CCParticleFire::createWithTotalParticles(m_number);
	} else if (m_name == "CCParticleSun") {
		pParticle = CCParticleSun::createWithTotalParticles(m_number);
	} else if (m_name == "CCParticleFireworks") {
		pParticle = CCParticleFireworks::createWithTotalParticles(m_number);
	} else if (m_name == "CCParticleGalaxy") {
		pParticle = CCParticleGalaxy::createWithTotalParticles(m_number);
	} else if (m_name == "CCParticleFlower") {
		pParticle = CCParticleFlower::createWithTotalParticles(m_number);
	} else if (m_name == "CCParticleMeteor") {
		pParticle = CCParticleMeteor::createWithTotalParticles(m_number);
	} else if (m_name == "CCParticleSpiral") {
		pParticle = CCParticleSpiral::createWithTotalParticles(m_number);
	} else if (m_name == "CCParticleExplosion") {
		pParticle = CCParticleExplosion::createWithTotalParticles(m_number);
	} else if (m_name == "CCParticleSmoke") {
		pParticle = CCParticleSmoke::createWithTotalParticles(m_number);
	} else if (m_name == "CCParticleSnow") {
		pParticle = CCParticleSnow::createWithTotalParticles(m_number);
	} else if (m_name == "CCParticleRain") {
		pParticle = CCParticleRain::createWithTotalParticles(m_number);
	}

	if (pParticle != NULL) {
		pParticle->setTexture(CCTextureCache::sharedTextureCache()->addImage(m_res.c_str()));
		pParticle->setPosition(m_pos.x, m_pos.y);
		pParticle->setTag(m_tag);
		pParticle->setScale(m_scale);
		pParticle->setZOrder(m_zOrder);

		m_pTarget->addChild(pParticle);
	}
}

CCObject* AE_Particle_Sys::copyWithZone( CCZone *pZone )
{
	CCZone *pNewZone = NULL;
	AE_Particle_Sys *pRet = NULL;

	if (pZone && pZone->m_pCopyObject) {
		pRet = (AE_Particle_Sys*) (pZone->m_pCopyObject);
	} else {
		pRet = new AE_Particle_Sys();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(pZone);

	pRet->init(m_name, m_res, m_number, m_scale, m_pos, m_zOrder, m_tag);

	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

bool AE_Particle_Sys::init( std::string name, std::string res,unsigned int number, float scale, CCPoint pos, int zOrder, int tag )
{
	this->m_name = name;
	this->m_res = res;
	this->m_number = number;
	this->m_scale = scale;
	this->m_pos = pos;
	this->m_zOrder = zOrder;
	this->m_tag = tag;
	return true;
}

//
// AE_ChildAnimation
//
AE_ChildAnimation* AE_ChildAnimation::create(const std::list<std::string>& fileNames, const std::string& prefix, int prefixNum, std::string plist,
											 float delayPerUnit, int loops, float scale, CCPoint pos, int srcBlendFunc, int dstBlendFunc, int zOrder, int tag)
{
	AE_ChildAnimation *pRet = new AE_ChildAnimation();

	if (pRet) {
		pRet->autorelease();
		pRet->init(fileNames, prefix, prefixNum, plist, delayPerUnit, loops, scale, pos, srcBlendFunc, dstBlendFunc, zOrder, tag);
	}

	return pRet;
}

void AE_ChildAnimation::update(float time) {
	CC_UNUSED_PARAM(time);
	// add particle list

	CCSprite* sprite = CCSprite::create();
	{ // add animation
		char szBuff[100];
		CCAnimation* animation = NULL;
		if (m_plist.size() > 0) {
			CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(m_plist.c_str());
			CCArray* animFrames = CCArray::create();
			for (std::list<std::string>::iterator it = m_fileNames.begin(); it != m_fileNames.end(); ++it) {
				CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(it->c_str());
				animFrames->addObject(frame);
			}

			if (m_prefixNum == 0) { // let us guess
				std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(m_plist.c_str());
				CCDictionary *dict = CCDictionary::createWithContentsOfFileThreadSafe(fullPath.c_str());
				if (dict != 0) {
					dict = (CCDictionary*)dict->objectForKey("frames");
					if (dict != 0 && dict->count() > 0) {
						CCDictElement* pElement = NULL;
						CCDICT_FOREACH(dict, pElement) {
							std::string spriteFrameName = pElement->getStrKey();
							int guessPrefixNameCount = spriteFrameName.size() - 6;
							if (guessPrefixNameCount > 0) { // 6 = "01.png"
								m_prefix = spriteFrameName.substr(0, guessPrefixNameCount);
							}
							break;
						}
						
						if (m_prefix.size() > 0) {
							for (int i = 1; i < 99; ++i) {
								sprintf(szBuff, "%s%02d.png", m_prefix.c_str(), i);
								CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szBuff);
								if (frame == 0) break;

								animFrames->addObject(frame);
							}
						}
					}
				}
				dict->release();
			} else if (m_prefix.size() > 0 && m_prefixNum > 0) {
				for (int i = 1; i <= m_prefixNum; ++i) {
					sprintf(szBuff, "%s%02d.png", m_prefix.c_str(), i);
					CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szBuff);
					sprintf(szBuff, "%s%02d.png not exist in %s", m_prefix.c_str(), i, m_plist.c_str());
					CCAssert(frame != 0, szBuff);
					animFrames->addObject(frame);
				}
			}
			animation = CCAnimation::createWithSpriteFrames(animFrames, 0);
		} else {
			animation = CCAnimation::create();
			for (std::list<std::string>::iterator it = m_fileNames.begin(); it != m_fileNames.end(); ++it) {
				animation->addSpriteFrameWithFileName(it->c_str());
			}
			if (m_prefix.size() > 0 && m_prefixNum > 0) {
				for (int i = 1; i <= m_prefixNum; ++i) {
					sprintf(szBuff, "%s%02d.png", m_prefix.c_str(), i);
					animation->addSpriteFrameWithFileName(szBuff);
				}
			}
		}

		animation->setDelayPerUnit(m_delayPerUnit);
		animation->setLoops(m_loops <= 0 ? 1 : m_loops);

		if (animation != NULL) {
			if (m_loops <= 0) {
				sprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
			} else {
				sprite->runAction(CCAnimate::create(animation));
			}
		}
	}
	sprite->setPosition(ccp(m_pos.x, m_pos.y));
	sprite->setTag(m_tag);
	sprite->setZOrder(m_zOrder);
	sprite->setScale(m_scale);
	ccBlendFunc blendFunc = { static_cast<GLenum>(m_srcBlendFunc), static_cast<GLenum>(m_dstBlendFunc) };
	sprite->setBlendFunc(blendFunc);
	m_pTarget->addChild(sprite);
}

CCObject* AE_ChildAnimation::copyWithZone( CCZone *pZone )
{
	CCZone *pNewZone = NULL;
	AE_ChildAnimation *pRet = NULL;

	if (pZone && pZone->m_pCopyObject) {
		pRet = (AE_ChildAnimation*) (pZone->m_pCopyObject);
	} else {
		pRet = new AE_ChildAnimation();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(pZone);

	pRet->init(m_fileNames, m_prefix, m_prefixNum, m_plist, m_delayPerUnit, m_loops, m_scale, m_pos, m_srcBlendFunc, m_dstBlendFunc, m_zOrder, m_tag);

	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

bool AE_ChildAnimation::init( const std::list<std::string>& fileNames, const std::string& prefix, int prefixNum, std::string plist, float delayPerUnit, int loops, float scale, CCPoint pos, int srcBlendFunc, int dstBlendFunc, int zOrder, int tag )
{
	this->m_fileNames = fileNames;
	this->m_prefix = prefix;
	this->m_prefixNum = prefixNum;
	this->m_plist = plist;
	this->m_delayPerUnit = delayPerUnit;
	this->m_loops = loops;
	this->m_scale = scale;
	this->m_pos = pos;
	this->m_srcBlendFunc = srcBlendFunc;
	this->m_dstBlendFunc = dstBlendFunc;
	this->m_zOrder = zOrder;
	this->m_tag = tag;
	return true;
}



//
// AE_ShowLabelInDuration
//
class AE_ShowLabelInDuration : public CCActionInterval {
	unsigned short* unicode;
	int length;
	int curShow;

public:
	AE_ShowLabelInDuration() : unicode(NULL), length(0), curShow(0) {}

	static AE_ShowLabelInDuration* create( float d, const std::string& label)
	{
		AE_ShowLabelInDuration* pAction = new AE_ShowLabelInDuration();

		pAction->initWithDuration(d);
		pAction->unicode = cc_utf8_to_utf16(label.c_str(), -1, &pAction->length);
		pAction->autorelease();

		return pAction;
	}

	CCObject* copyWithZone(CCZone *pZone)
	{
		CCZone* pNewZone = NULL;
		AE_ShowLabelInDuration* pCopy = NULL;
		if(pZone && pZone->m_pCopyObject) 
		{
			//in case of being called at sub class
			pCopy = (AE_ShowLabelInDuration*)(pZone->m_pCopyObject);
		}
		else
		{
			pCopy = new AE_ShowLabelInDuration();
			pZone = pNewZone = new CCZone(pCopy);
		}

		CCActionInterval::copyWithZone(pZone);

		pCopy->unicode = new unsigned short[this->length];
		memcpy(pCopy->unicode, this->unicode, this->length * sizeof(unsigned short));
		pCopy->length = length;
		pCopy->curShow = curShow;

		CC_SAFE_DELETE(pNewZone);
		return pCopy;
	}

	void update(float time)
	{
		int needShow = length * time;
		if (needShow <= curShow) return;

		const char* str = cc_utf16_to_utf8(unicode, needShow, NULL, NULL);
		((CCLabelTTF*)(m_pTarget))->setString(str);
		delete str;
	}

	virtual ~AE_ShowLabelInDuration() {
		delete[] unicode;
	}
};

//
// AE_Add_Label
//
AE_Add_Label* AE_Add_Label::create(CCPoint pos, const std::string& label, const std::string& fontDefFile, const std::string& font, float fontSize, ccColor3B color, float duration, int srcBlendFactor, int dstBlendFactor, int tag) 
{
	AE_Add_Label *pRet = new AE_Add_Label();

	if (pRet) {
		pRet->autorelease();
		pRet->init(pos, label, fontDefFile, font, fontSize, color, duration, srcBlendFactor, dstBlendFactor, tag);
	}

	return pRet;
}

void AE_Add_Label::update(float time) {
	CC_UNUSED_PARAM(time);

	CCLabelTTF* ret = CCLabelTTF::create(m_duration > 0 ? "" : m_label.c_str(), m_font.c_str(), m_fontSize);

	if (ret != NULL) {
		if (m_fontDefFile.size() > 0) {
			ccFontDefinition ccFD = getFontDefinition(m_fontDefFile);
			ccFD.m_fontFillColor = m_fontColor;
		} else {
			ret->setColor(m_fontColor);
		}
		ret->setTag(m_tag);
		ret->setPosition(m_pos);
		ret->setAnchorPoint(ccp(0, 0));
		ccBlendFunc blendFunc = { static_cast<GLenum>(m_srcBlendFactor), static_cast<GLenum>(m_dstBlendFactor) };
		ret->setBlendFunc(blendFunc);
		m_pTarget->addChild(ret);

		if (m_duration != 0) {
			AE_ShowLabelInDuration* pAction = AE_ShowLabelInDuration::create(m_duration, m_label);
			ret->runAction(pAction);
		}
	}
}

CCObject* AE_Add_Label::copyWithZone(CCZone *pZone) {
	CCZone *pNewZone = NULL;
	AE_Add_Label *pRet = NULL;

	if (pZone && pZone->m_pCopyObject) {
		pRet = (AE_Add_Label*) (pZone->m_pCopyObject);
	} else {
		pRet = new AE_Add_Label();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(pZone);

	pRet->init(m_pos, m_label, m_fontDefFile, m_font, m_fontSize, m_fontColor, m_duration, m_srcBlendFactor, m_dstBlendFactor, m_tag);

	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

bool AE_Add_Label::init( CCPoint pos, const std::string& label, const std::string& fontDefFile, const std::string& font, float fontSize, ccColor3B fontColor, float duration, int srcBlendFactor, int dstBlendFactor, int tag )
{
	this->m_pos = pos;
	this->m_label = label;
	this->m_fontDefFile = fontDefFile;
	this->m_font = font;
	this->m_fontSize = fontSize;
	this->m_fontColor = fontColor;
	this->m_duration = duration;
	this->m_srcBlendFactor = srcBlendFactor;
	this->m_dstBlendFactor = dstBlendFactor;
	this->m_tag = tag;
	return true;
}


//
// AE_Remove_Child
//
AE_Remove_Child* AE_Remove_Child::create(int tag) 
{
	AE_Remove_Child *pRet = new AE_Remove_Child();

	if (pRet) {
		pRet->autorelease();
		pRet->init(tag);
	}

	return pRet;
}

void AE_Remove_Child::update(float time) {
	CC_UNUSED_PARAM(time);
	// add particle list

	m_pTarget->removeChildByTag(m_tag, true);
}

CCObject* AE_Remove_Child::copyWithZone(CCZone *pZone) {
	CCZone *pNewZone = NULL;
	AE_Remove_Child *pRet = NULL;

	if (pZone && pZone->m_pCopyObject) {
		pRet = (AE_Remove_Child*) (pZone->m_pCopyObject);
	} else {
		pRet = new AE_Remove_Child();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(pZone);
	pRet->init(m_tag);
	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

bool AE_Remove_Child::init( int tag )
{
	this->m_tag = tag;
	return true;
}


// -----------------------------  Grid3D  ----------------------------------

// implementation of AE_New_Flip

AE_New_Flip3D* AE_New_Flip3D::create(float duration, float delta, bool isFlipX)
{
	AE_New_Flip3D *pAction = new AE_New_Flip3D();

	if (pAction)
	{
		if (pAction->initWithDuration(duration))
		{
			pAction->autorelease();
		}
		else
		{
			CC_SAFE_RELEASE_NULL(pAction);
		}
	}

	pAction->m_delta = delta;
	pAction->m_isFilpX = isFlipX;
	return pAction;
}

bool AE_New_Flip3D::initWithDuration(float duration)
{
	return CCGrid3DAction::initWithDuration(duration, CCSizeMake(1, 1));
}

bool AE_New_Flip3D::initWithSize(const CCSize& gridSize, float duration)
{
	if (gridSize.width != 1 || gridSize.height != 1)
	{
		// Grid size must be (1,1)
		CCAssert(0, "Grid size must be (1,1)");

		return false;
	}

	return CCGrid3DAction::initWithDuration(duration, gridSize);
}

CCObject* AE_New_Flip3D::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	AE_New_Flip3D* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (AE_New_Flip3D*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new AE_New_Flip3D();
		pZone = pNewZone = new CCZone(pCopy);
	}

	CCGrid3DAction::copyWithZone(pZone);

	pCopy->initWithSize(m_sGridSize, m_fDuration);
	pCopy->m_delta = this->m_delta;
	pCopy->m_isFilpX = this->m_isFilpX;

	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

void AE_New_Flip3D::update(float time)
{
	float angle = (float)M_PI * time; // 180 degrees
	float mz = sinf(angle);
	angle = angle / 2.0f; // x calculates degrees from 0 to 90
	float mx = cosf(angle);

	ccVertex3F v0, v1, v, diff;

	v0 = originalVertex(ccp(1, 1));
	v1 = originalVertex(ccp(0, 0));

	float    x0 = v0.x;
	float    x1 = v1.x;
	float x;
	CCPoint    a, b, c, d;

	if ( x0 > x1 )
	{
		// Normal Grid
		a = ccp(0,0);
		b = ccp(0,1);
		c = ccp(1,0);
		d = ccp(1,1);
		x = x0;
	}
	else
	{
		// Reversed Grid
		c = ccp(0,0);
		d = ccp(0,1);
		a = ccp(1,0);
		b = ccp(1,1);
		x = x1;
	}

	diff.x = ( x - x * mx );
	diff.z = fabsf( floorf( (x * mz) / 4.0f ) );

	// bottom-left
	v = originalVertex(a);
	v.x = diff.x;
	v.z += diff.z;
	setVertex(a, v);

	// upper-left
	v = originalVertex(b);
	v.x = diff.x;
	v.z += diff.z;
	setVertex(b, v);

	// bottom-right
	v = originalVertex(c);
	v.x -= diff.x;
	v.z -= diff.z;
	setVertex(c, v);

	// upper-right
	v = originalVertex(d);
	v.x -= diff.x;
	v.z -= diff.z;
	setVertex(d, v);
}

CCActionInterval* AE_UiMoveFromDelta::create(const char* spriteName, float d) 
{
	if (spriteName == NULL) return CCDelayTime::create(d);
	std::map<std::string, CCPoint>::iterator it = g_uiNameToOriginalPos.find(std::string(spriteName));
	if (it != g_uiNameToOriginalPos.end()) {
		return CCMoveTo::create(d, it->second);
	} else {
		return CCDelayTime::create(d);
	}
}

//
// FadeIn
//

AE_FadeIn_WithAllChild* AE_FadeIn_WithAllChild::create(float d)
{
	AE_FadeIn_WithAllChild* pAction = new AE_FadeIn_WithAllChild();

	pAction->initWithDuration(d);
	pAction->autorelease();

	return pAction;
}

CCObject* AE_FadeIn_WithAllChild::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	AE_FadeIn_WithAllChild* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject)
	{
		//in case of being called at sub class
		pCopy = (AE_FadeIn_WithAllChild*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new AE_FadeIn_WithAllChild();
		pZone = pNewZone = new CCZone(pCopy);
	}

	CCActionInterval::copyWithZone(pZone);
	pCopy->initWithDuration(this->getDuration());

	CC_SAFE_DELETE(pNewZone);

	return pCopy;
}

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

static void FadeWithAllChild(CCNode*ccNode, int opacity, bool isFadeIn)
{
	if(ccNode == NULL)
		return;

	CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(ccNode);
	if (pRGBAProtocol != NULL) {
		pRGBAProtocol->setOpacity(isFadeIn ? max(pRGBAProtocol->getOpacity(), opacity) : min(opacity, pRGBAProtocol->getOpacity()));
	}
	CCObject* ccChild;
	CCARRAY_FOREACH(ccNode->getChildren(), ccChild) {
		FadeWithAllChild((CCNode*)ccChild, opacity, isFadeIn);
	}
}

void AE_FadeIn_WithAllChild::update(float time)
{
	GLubyte opacity = (GLubyte)(255 * time);
	FadeWithAllChild(m_pTarget, opacity, true);
}

CCActionInterval* AE_FadeIn_WithAllChild::reverse(void)
{
	return AE_FadeOut_WithAllChild::create(m_fDuration);
}


//
// FadeOut
//

AE_FadeOut_WithAllChild* AE_FadeOut_WithAllChild::create(float d)
{
	AE_FadeOut_WithAllChild* pAction = new AE_FadeOut_WithAllChild();

	pAction->initWithDuration(d);
	pAction->autorelease();

	return pAction;
}

CCObject* AE_FadeOut_WithAllChild::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	AE_FadeOut_WithAllChild* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (AE_FadeOut_WithAllChild*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new AE_FadeOut_WithAllChild();
		pZone = pNewZone = new CCZone(pCopy);
	}

	CCActionInterval::copyWithZone(pZone);
	pCopy->initWithDuration(this->getDuration());
	CC_SAFE_DELETE(pNewZone);

	return pCopy;
}

void AE_FadeOut_WithAllChild::update(float time)
{
	GLubyte opacity = GLubyte(255 * (1 - time));
	FadeWithAllChild(m_pTarget, opacity, false);
}

CCActionInterval* AE_FadeOut_WithAllChild::reverse(void)
{
	return AE_FadeIn_WithAllChild::create(m_fDuration);
}

void AE_FaceToPos::adjustFaceTo()
{
	if (m_pTarget == NULL) return;

	CCPoint delta = m_faceToPos - m_pTarget->getPosition();
	if (delta.equals(CCPointZero)) return;

	float deltaDegree = delta.getAngle() * 180.0f / 3.14f;
	float degree = -deltaDegree + this->m_initDegree;
	//if (delta.y < 0) degree += 180.0f;
	m_pTarget->setRotation(degree);
}

AE_FaceToPos* AE_FaceToPos::create(const CCPoint& faceToPos, float initDegree, float duration)
{
	AE_FaceToPos *pRet = new AE_FaceToPos();
	if (pRet && pRet->init(faceToPos, initDegree, duration))
	{
		pRet->autorelease();
		pRet->adjustFaceTo();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void AE_FaceToPos::update(float dt) 
{
	adjustFaceTo();
}

CCObject* AE_FaceToPos::copyWithZone( CCZone *pZone )
{
	CCZone *pNewZone = NULL;
	AE_FaceToPos *pRet = NULL;

	if (pZone && pZone->m_pCopyObject) {
		pRet = (AE_FaceToPos*) (pZone->m_pCopyObject);
	} else {
		pRet = new AE_FaceToPos();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInterval::copyWithZone(pZone);

	pRet->init(m_faceToPos, m_initDegree, getDuration());

	CC_SAFE_DELETE(pNewZone);
	return pRet;
}



AE_AddSubAE * AE_AddSubAE::create(aeditor::ActionTemplateTable* table, const std::string& aeFile, const std::string& alignSprite, CCPoint pos, float scale, std::map<std::string, std::string>& resReplaced, int zOrder, int tag )
{
	AE_AddSubAE *pRet = new AE_AddSubAE();

	if (pRet) {
		pRet->autorelease();
	}

	pRet->init(table, aeFile, alignSprite, pos, scale, resReplaced, zOrder, tag);

	return pRet;
}

void AE_AddSubAE::update( float time )
{
	CC_UNUSED_PARAM(time);

	CCNode* node = m_table->addAEToNode(m_aeFile, m_alignSprite, m_scale, m_resReplaced);
	node->setPosition(m_pos);
	node->setZOrder(m_zOrder);
	node->setTag(m_tag);

	m_pTarget->addChild(node);
}

CCObject* AE_AddSubAE::copyWithZone( CCZone *pZone )
{
	CCZone *pNewZone = NULL;
	AE_AddSubAE *pRet = NULL;

	if (pZone && pZone->m_pCopyObject) {
		pRet = (AE_AddSubAE*) (pZone->m_pCopyObject);
	} else {
		pRet = new AE_AddSubAE();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(pZone);

	pRet->init(m_table, m_aeFile, m_alignSprite, m_pos, m_scale, m_resReplaced, m_zOrder, m_tag);

	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

bool AE_AddSubAE::init( aeditor::ActionTemplateTable* table, const std::string& aeFile, const std::string& alignSprite, CCPoint pos, float scale, std::map<std::string, std::string>& resReplaced, int zOrder, int tag )
{
	this->m_table = table;
	this->m_aeFile = aeFile;
	this->m_alignSprite = alignSprite;
	this->m_pos = pos;
	this->m_scale = scale;
	this->m_resReplaced = resReplaced;
	this->m_zOrder = zOrder;
	this->m_tag = tag;
	return true;
}

void AE_AddMpEffect::update( float time )
{
	CC_UNUSED_PARAM(time);

	aeditor::MPEffectParam param;
	//param.gameSpeed = 1.0f; ???
	//isFlipY ???
	param.scaleForAnimation = m_extraAnimationScale;
	CCNode* node = CCNode::create();
	node->setPosition(m_pos);
	node->setScale(m_scale);
	node->setZOrder(m_zOrder);
	node->setTag(m_tag);
	aeditor::MPEffect::runEffectOnNode(node, m_mpFile, param);

	m_pTarget->addChild(node);
}

CCObject* AE_AddMpEffect::copyWithZone( CCZone *pZone )
{
	CCZone *pNewZone = NULL;
	AE_AddMpEffect *pRet = NULL;

	if (pZone && pZone->m_pCopyObject) {
		pRet = (AE_AddMpEffect*) (pZone->m_pCopyObject);
	} else {
		pRet = new AE_AddMpEffect();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(pZone);

	pRet->init(m_mpFile, m_pos, m_extraAnimationScale, m_scale, m_zOrder, m_tag);

	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

AE_AddMpEffect * AE_AddMpEffect::create( const std::string& mpFile, CCPoint pos, float extraAnimationScale, float scale, int zOrder, int tag )
{
	AE_AddMpEffect *pRet = new AE_AddMpEffect();

	if (pRet) {
		pRet->autorelease();
	}

	pRet->init(mpFile, pos, extraAnimationScale, scale, zOrder, tag);

	return pRet;
}

bool AE_AddMpEffect::init( const std::string& mpFile, CCPoint pos, float extraAnimationScale, float scale, int zOrder, int tag )
{
	this->m_mpFile = mpFile;
	this->m_pos = pos;
	this->m_extraAnimationScale = extraAnimationScale;
	this->m_scale = scale;
	this->m_zOrder = zOrder;
	this->m_tag = tag;
	return true;
}


// shaders
static std::string s_ccprite_default_shader = kCCShader_PositionTextureColor;
static std::string s_blur_shader = "ShaderBlur";
static std::string s_grey_shader = "ShaderGrey";
static std::string s_mosaic_shader = "ShaderMosaic";
static std::string s_compose_shader = "ShaderCompose";
static std::string s_bloom_shader = "ShaderBloom";
static std::string s_water_shader = "ShaderWater";
static std::string s_radialblur_shader = "ShaderRadialBlur";

static std::string s_blur_param = "ShaderParam_Blur"; // float
static std::string s_mosaic_param = "ShaderParam_Mosaic"; // float
static std::string s_grey_param = "ShaderParam_Grey"; // float [0, 1]
static std::string s_compose_brightness = "ShaderParam_Compose_brightness"; // float [-1, 1]
static std::string s_compose_contrast = "ShaderParam_Compose_contrast"; // float [-1, 1]
static std::string s_compose_saturation = "ShaderParam_Compose_saturation"; // float [-1, 1]
static std::string s_bloom_offset = "ShaderParam_Bloom_offset"; // float
static std::string s_bloom_scale = "ShaderParam_Bloom_scale"; // float
static std::string s_radialblur_dist = "ShaderParam_RadialBlur_dist"; // float
static std::string s_radialblur_strength = "ShaderParam_RadialBlur_strength"; // float

//
// AE_ChangeShader
//
AE_ChangeShader * AE_ChangeShader::create(CCGLProgram *shader)
{
	AE_ChangeShader *pRet = new AE_ChangeShader();

	if (pRet) {
		pRet->autorelease();
		pRet->init(shader);
	}
	return pRet;
}
AE_ChangeShader* AE_ChangeShader::create(const char *name) 
{
	AE_ChangeShader *pRet = new AE_ChangeShader();

	if (pRet) {
		pRet->autorelease();
		pRet->init(name);
	}
	return pRet;
}

void AE_ChangeShader::update(float time) {
	CC_UNUSED_PARAM(time);
	m_pTarget->setShaderProgram(m_Shader);
}

CCObject* AE_ChangeShader::copyWithZone(CCZone *pZone) {
	CCZone *pNewZone = NULL;
	AE_ChangeShader *pRet = NULL;

	if (pZone && pZone->m_pCopyObject) {
		pRet = (AE_ChangeShader*) (pZone->m_pCopyObject);
	} else {
		pRet = new AE_ChangeShader();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(pZone);
	
	init(m_Shader);

	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

bool AE_ChangeShader::init( CCGLProgram *shader )
{
    CC_SAFE_RETAIN(shader);
    CC_SAFE_RELEASE(m_Shader);
	m_Shader = shader;
	return true;
}
bool AE_ChangeShader::init( const char *name )
{
	CCGLProgram *shader = CCShaderCache::sharedShaderCache()->programForKey(name);
	if (shader)
	{
		init(shader);
	}
	else if (name == s_blur_shader)
	{
		CCGLProgram* shader = new CCGLProgram();
		// TODO check exists
		GLchar * fragSource = (GLchar*) CCString::createWithContentsOfFile(
							CCFileUtils::sharedFileUtils()->fullPathForFilename("shaders/example_Blur.fsh").c_str())->getCString();	
		shader->initWithVertexShaderByteArray(ccPositionTextureColor_vert, fragSource);
    
		CHECK_GL_ERROR_DEBUG();
		shader->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
		shader->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
		shader->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    
		CHECK_GL_ERROR_DEBUG();
    
		shader->link();
    
		CHECK_GL_ERROR_DEBUG();
    
		shader->updateUniforms();
    
		CHECK_GL_ERROR_DEBUG();

		init(shader);

		CCShaderCache::sharedShaderCache()->addProgram(shader, name);

		shader->release();
	}
	else if (name == s_grey_shader)
	{
		CCGLProgram* shader = new CCGLProgram();
		// TODO check exists
		GLchar * fragSource = (GLchar*) CCString::createWithContentsOfFile(
							CCFileUtils::sharedFileUtils()->fullPathForFilename("shaders/example_Grey.fsh").c_str())->getCString();	
		shader->initWithVertexShaderByteArray(ccPositionTextureColor_vert, fragSource);
    
		CHECK_GL_ERROR_DEBUG();
		shader->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
		shader->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
		shader->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    
		CHECK_GL_ERROR_DEBUG();
    
		shader->link();
    
		CHECK_GL_ERROR_DEBUG();
    
		shader->updateUniforms();
    
		CHECK_GL_ERROR_DEBUG();

		init(shader);

		CCShaderCache::sharedShaderCache()->addProgram(shader, name);

		shader->release();
	}
	else if (name == s_mosaic_shader)
	{
		CCGLProgram* shader = new CCGLProgram();
		// TODO check exists
		GLchar * fragSource = (GLchar*) CCString::createWithContentsOfFile(
							CCFileUtils::sharedFileUtils()->fullPathForFilename("shaders/example_Mosaic.fsh").c_str())->getCString();	
		shader->initWithVertexShaderByteArray(ccPositionTextureColor_vert, fragSource);
    
		CHECK_GL_ERROR_DEBUG();
		shader->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
		shader->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
		shader->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    
		CHECK_GL_ERROR_DEBUG();
    
		shader->link();
    
		CHECK_GL_ERROR_DEBUG();
    
		shader->updateUniforms();
    
		CHECK_GL_ERROR_DEBUG();

		init(shader);

		CCShaderCache::sharedShaderCache()->addProgram(shader, name);

		shader->release();
	}
	else if (name == s_compose_shader)
	{
		CCGLProgram* shader = new CCGLProgram();
		// TODO check exists
		GLchar * fragSource = (GLchar*) CCString::createWithContentsOfFile(
							CCFileUtils::sharedFileUtils()->fullPathForFilename("shaders/example_Compose.fsh").c_str())->getCString();	
		shader->initWithVertexShaderByteArray(ccPositionTextureColor_vert, fragSource);
    
		CHECK_GL_ERROR_DEBUG();
		shader->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
		shader->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
		shader->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    
		CHECK_GL_ERROR_DEBUG();
    
		shader->link();
    
		CHECK_GL_ERROR_DEBUG();
    
		shader->updateUniforms();
    
		CHECK_GL_ERROR_DEBUG();

		init(shader);

		CCShaderCache::sharedShaderCache()->addProgram(shader, name);

		shader->release();
	}
	else if (name == s_bloom_shader)
	{
		CCGLProgram* shader = new CCGLProgram();
		// TODO check exists
		GLchar * fragSource = (GLchar*) CCString::createWithContentsOfFile(
							CCFileUtils::sharedFileUtils()->fullPathForFilename("shaders/example_Bloom.fsh").c_str())->getCString();	
		shader->initWithVertexShaderByteArray(ccPositionTextureColor_vert, fragSource);
    
		CHECK_GL_ERROR_DEBUG();
		shader->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
		shader->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
		shader->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    
		CHECK_GL_ERROR_DEBUG();
    
		shader->link();
    
		CHECK_GL_ERROR_DEBUG();
    
		shader->updateUniforms();
    
		CHECK_GL_ERROR_DEBUG();

		init(shader);

		CCShaderCache::sharedShaderCache()->addProgram(shader, name);

		shader->release();
	}
	else if (name == s_water_shader)
	{
		CCGLProgram* shader = new CCGLProgram();
		// TODO check exists
		GLchar * fragSource = (GLchar*) CCString::createWithContentsOfFile(
							CCFileUtils::sharedFileUtils()->fullPathForFilename("shaders/example_Water.fsh").c_str())->getCString();	
		shader->initWithVertexShaderByteArray(ccPositionTextureColor_vert, fragSource);
    
		CHECK_GL_ERROR_DEBUG();
		shader->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
		shader->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
		shader->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    
		CHECK_GL_ERROR_DEBUG();
    
		shader->link();
    
		CHECK_GL_ERROR_DEBUG();
    
		shader->updateUniforms();
    
		CHECK_GL_ERROR_DEBUG();

		init(shader);

		CCShaderCache::sharedShaderCache()->addProgram(shader, name);

		shader->release();
	}
	else if (name == s_radialblur_shader)
	{
		CCGLProgram* shader = new CCGLProgram();
		// TODO check exists
		GLchar * fragSource = (GLchar*) CCString::createWithContentsOfFile(
							CCFileUtils::sharedFileUtils()->fullPathForFilename("shaders/example_RadialBlur.fsh").c_str())->getCString();	
		shader->initWithVertexShaderByteArray(ccPositionTextureColor_vert, fragSource);
    
		CHECK_GL_ERROR_DEBUG();
		shader->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
		shader->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
		shader->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    
		CHECK_GL_ERROR_DEBUG();
    
		shader->link();
    
		CHECK_GL_ERROR_DEBUG();
    
		shader->updateUniforms();
    
		CHECK_GL_ERROR_DEBUG();

		init(shader);

		CCShaderCache::sharedShaderCache()->addProgram(shader, name);

		shader->release();
	}
	return true;
}

//
// AE_FadeShaderParams1f
//
AE_FadeShaderParams1f* AE_FadeShaderParams1f::create(const char *name, const ShaderParams1ffMap& params, float duration) 
{
	AE_FadeShaderParams1f *pRet = new AE_FadeShaderParams1f();

	if (pRet) {
		pRet->autorelease();
		pRet->init(name, params, duration);
	}
	return pRet;
}

void AE_FadeShaderParams1f::update(float time) {
	if (m_strName == s_blur_shader)
	{
		CCTextureProtocol* sprite = dynamic_cast<CCTextureProtocol*>(m_pTarget);
		if (sprite == NULL) return;

		if (m_mapParams.find(s_blur_param) == m_mapParams.end()) return;

		CCSize s = sprite->getTexture()->getContentSizeInPixels();
		ShaderParams1f param = m_mapParams[s_blur_param];
		float f = param.from + (param.to - param.from) * time;
		CCSize blur_ = ccp(1/s.width, 1/s.height);
		blur_ = ccpMult(blur_,f);
		GLint location = glGetUniformLocation( m_pTarget->getShaderProgram()->getProgram(), "blurSize");
		m_pTarget->setUniformLocationWith2f(location, blur_.width, blur_.height);
	}
	else if (m_strName == s_mosaic_shader)
	{
		CCTextureProtocol* sprite = dynamic_cast<CCTextureProtocol*>(m_pTarget);
		if (sprite == NULL) return;

		if (m_mapParams.find(s_mosaic_param) == m_mapParams.end()) return;

		ShaderParams1f param = m_mapParams[s_mosaic_param];
		float size = param.from + (param.to - param.from) * time;
		GLint location = glGetUniformLocation( m_pTarget->getShaderProgram()->getProgram(), "mosaicSize");
		m_pTarget->setUniformLocationWith1f(location, size);
	}
	else if (m_strName == s_grey_shader)
	{
		CCTextureProtocol* sprite = dynamic_cast<CCTextureProtocol*>(m_pTarget);
		if (sprite == NULL) return;

		if (m_mapParams.find(s_grey_param) == m_mapParams.end()) return;

		ShaderParams1f param = m_mapParams[s_grey_param];
		float grey = param.from + (param.to - param.from) * time;
		GLint location = glGetUniformLocation( m_pTarget->getShaderProgram()->getProgram(), "grey");
		m_pTarget->setUniformLocationWith1f(location, grey);
	}
	else if (m_strName == s_compose_shader)
	{
		CCTextureProtocol* sprite = dynamic_cast<CCTextureProtocol*>(m_pTarget);
		if (sprite == NULL) return;

		if (m_mapParams.find(s_compose_brightness) != m_mapParams.end())
		{
			ShaderParams1f brightness = m_mapParams[s_compose_brightness];
			float b = brightness.from + (brightness.to - brightness.from) * time;
			GLint location_b = glGetUniformLocation( m_pTarget->getShaderProgram()->getProgram(), "brightness");
			m_pTarget->setUniformLocationWith1f(location_b, b);
		}
		if (m_mapParams.find(s_compose_contrast) != m_mapParams.end())
		{
			ShaderParams1f contrast = m_mapParams[s_compose_contrast];
			float c = contrast.from + (contrast.to - contrast.from) * time;
			GLint location_c = glGetUniformLocation( m_pTarget->getShaderProgram()->getProgram(), "contrast");
			m_pTarget->setUniformLocationWith1f(location_c, c);

		}
		if (m_mapParams.find(s_compose_saturation) != m_mapParams.end())
		{
			ShaderParams1f saturation = m_mapParams[s_compose_saturation];
			float s = saturation.from + (saturation.to - saturation.from) * time;
			GLint location_s = glGetUniformLocation( m_pTarget->getShaderProgram()->getProgram(), "saturation");
			m_pTarget->setUniformLocationWith1f(location_s, s);
		}
	}
	else if (m_strName == s_bloom_shader)
	{
		CCTextureProtocol* sprite = dynamic_cast<CCTextureProtocol*>(m_pTarget);
		if (sprite == NULL) return;

		if (m_mapParams.find(s_bloom_offset) != m_mapParams.end())
		{
			ShaderParams1f offset = m_mapParams[s_bloom_offset];
			float f = offset.from + (offset.to - offset.from) * time;
			GLint location = glGetUniformLocation( m_pTarget->getShaderProgram()->getProgram(), "offset");
			m_pTarget->setUniformLocationWith1f(location, f);
		}
		if (m_mapParams.find(s_bloom_scale) != m_mapParams.end())
		{
			ShaderParams1f scale = m_mapParams[s_bloom_scale];
			float f = scale.from + (scale.to - scale.from) * time;
			GLint location = glGetUniformLocation( m_pTarget->getShaderProgram()->getProgram(), "scale");
			m_pTarget->setUniformLocationWith1f(location, f);
		}
	}
	else if (m_strName == s_water_shader)
	{
		CCTextureProtocol* sprite = dynamic_cast<CCTextureProtocol*>(m_pTarget);
		if (sprite == NULL) return;

		ShaderParams1f water = m_mapParams["time"];
		float f = water.from + (water.to - water.from) * time;
		GLint location = glGetUniformLocation( m_pTarget->getShaderProgram()->getProgram(), "time");
		m_pTarget->setUniformLocationWith1f(location, f);
	}
	else if (m_strName == s_radialblur_shader)
	{
		CCTextureProtocol* sprite = dynamic_cast<CCTextureProtocol*>(m_pTarget);
		if (sprite == NULL) return;

		if (m_mapParams.find(s_radialblur_dist) != m_mapParams.end())
		{
			ShaderParams1f dist = m_mapParams[s_radialblur_dist];
			float f = dist.from + (dist.to - dist.from) * time;
			GLint location = glGetUniformLocation( m_pTarget->getShaderProgram()->getProgram(), "dist");
			m_pTarget->setUniformLocationWith1f(location, f);
		}
		if (m_mapParams.find(s_radialblur_strength) != m_mapParams.end())
		{
			ShaderParams1f strength = m_mapParams[s_radialblur_strength];
			float f = strength.from + (strength.to - strength.from) * time;
			GLint location = glGetUniformLocation( m_pTarget->getShaderProgram()->getProgram(), "strength");
			m_pTarget->setUniformLocationWith1f(location, f);
		}
	}
}

CCObject* AE_FadeShaderParams1f::copyWithZone(CCZone *pZone) {
	CCZone *pNewZone = NULL;
	AE_FadeShaderParams1f *pRet = NULL;

	if (pZone && pZone->m_pCopyObject) {
		pRet = (AE_FadeShaderParams1f*) (pZone->m_pCopyObject);
	} else {
		pRet = new AE_FadeShaderParams1f();
		pZone = pNewZone = new CCZone(pRet);
	}

	CCActionInterval::copyWithZone(pZone);

	pRet->init(m_strName.c_str(), m_mapParams, getDuration());

	CC_SAFE_DELETE(pNewZone);
	return pRet;
}

void AE_FadeShaderParams1f::startWithTarget(CCNode *pTarget) 
{
	CCActionInterval::startWithTarget(pTarget);
}

bool AE_FadeShaderParams1f::init(const char *name, const ShaderParams1ffMap& params, float duration)
{
	m_strName = name;
	m_mapParams = params;
	this->initWithDuration(duration);
	return true;
}

NS_CC_END