#include "MPEffect.h"
#include "support/tinyxml2/tinyxml2.h"
#include "AEAction.h"

aeditor::MPEffect::MPEffect(const std::string& path)
{
	unsigned long size;
	unsigned char* pData = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &size);
	std::string strData((char*)pData, size);
	delete[] pData;

	tinyxml2::XMLDocument doc;
	doc.ParseDeep((char*)strData.c_str(), 0);
	if (doc.Error()) {
		char szBuff[256];
		sprintf(szBuff, "Read MPEffect Tempalte File Failed !!!! file = %s", path.c_str());
		CCAssert(!doc.Error(), szBuff);
	}
	

	tinyxml2::XMLElement * pRoot = doc.RootElement();
	if (!pRoot )
	{
		CCLOG("MPEffect::LoadFromFile, can't load file: %s!", path.c_str());
		return;
	}

	m_strEffectName = pRoot->Attribute("name");

	{
		tinyxml2::XMLElement* __eParticles = pRoot->FirstChildElement("particles");
		if(__eParticles)
		{
			for (tinyxml2::XMLElement* eParticle = __eParticles->FirstChildElement("particle"); eParticle != NULL; 
				eParticle = eParticle->NextSiblingElement("particle"))
			{
				MPParticle* particle = new MPParticle;

				particle->strName = eParticle->Attribute("name");
				particle->strFile = eParticle->Attribute("file");
				if(particle->strFile.length() > 0 && particle->strFile.find("/") == std::string::npos && particle->strFile.find("\\") == std::string::npos) 
				{ // 不包含斜杠，反斜杠
					particle->strFile = "effect/particle/" + particle->strFile;
				}

				particle->nLayer = eParticle->IntAttribute("layer");
				particle->fDelay = eParticle->FloatAttribute("delay");
				particle->fOffsetx = eParticle->FloatAttribute("offsetx");
				particle->fOffsety = eParticle->FloatAttribute("offsety");
				particle->fScale = eParticle->FloatAttribute("scale");
				particle->fRotate = eParticle->FloatAttribute("rotate");
				particle->nAbsCoord = eParticle->IntAttribute("abscoord");
				m_vecParticles.push_back(particle);
			}
		}
	}

	// animations
	{
		tinyxml2::XMLElement* __eAnimations = pRoot->FirstChildElement("animations");
		if(__eAnimations)
		{
			for (tinyxml2::XMLElement* eAnimation = __eAnimations->FirstChildElement("animation"); eAnimation != NULL; 
				eAnimation = eAnimation->NextSiblingElement("animation"))
			{
				MPAnimation* animation = new MPAnimation;

				animation->strName = eAnimation->Attribute("name");
				animation->strFile = eAnimation->Attribute("file");
				if(animation->strFile.length() > 0 && animation->strFile.find("/") == std::string::npos && animation->strFile.find("\\") == std::string::npos) 
				{ // 不包含斜杠，反斜杠
					animation->strFile = "effect/animation/" + animation->strFile;
				}

				animation->nLayer = eAnimation->IntAttribute("layer");
				animation->fDelay = eAnimation->FloatAttribute("delay");
				animation->nFrameCnt = eAnimation->IntAttribute("frames");
				animation->strFrameName = eAnimation->Attribute("framename");
				animation->fPlayTime = eAnimation->FloatAttribute("playtime");
				animation->fOffsetx = eAnimation->FloatAttribute("offsetx");
				animation->fOffsety = eAnimation->FloatAttribute("offsety");
				animation->nAbsCoord = eAnimation->FloatAttribute("abscoord");
				animation->fScale = eAnimation->FloatAttribute("scale");
				animation->fRotate = eAnimation->FloatAttribute("rotate");
				if (eAnimation->Attribute("needflip") != 0 && strlen(eAnimation->Attribute("needflip")) > 0) {
					animation->bNeedFlip = eAnimation->IntAttribute("needflip") > 0;
				}
				if (eAnimation->Attribute("fadeintime") != 0 && strlen(eAnimation->Attribute("fadeintime")) > 0) {
					animation->fFadeInTime = eAnimation->FloatAttribute("fadeintime");
				}
				if (eAnimation->Attribute("fadeouttime") != 0 && strlen(eAnimation->Attribute("fadeouttime")) > 0) {
					animation->fFadeOutTime = eAnimation->FloatAttribute("fadeouttime");
				}
				m_vecAnimations.push_back(animation);
			}
		}
	}

	// specialeffects
	{
		tinyxml2::XMLElement* __eSpecialEffects = pRoot->FirstChildElement("specialeffects");
		if(__eSpecialEffects)
		{
			for (tinyxml2::XMLElement* eSpecialEffect = __eSpecialEffects->FirstChildElement("specialeffect"); eSpecialEffect != NULL; 
				eSpecialEffect = __eSpecialEffects->NextSiblingElement("specialeffect"))
			{
				MPSpecialEffect* specialeffect = new MPSpecialEffect;

				specialeffect->strName = eSpecialEffect->Attribute("name");
				specialeffect->nType = eSpecialEffect->IntAttribute("type");
				specialeffect->fDelay = eSpecialEffect->FloatAttribute("delay");
				specialeffect->fTime = eSpecialEffect->FloatAttribute("time");
				specialeffect->fOffsetx = eSpecialEffect->FloatAttribute("offsetx");
				specialeffect->fOffsety = eSpecialEffect->FloatAttribute("offsety");
				specialeffect->nAbsCoord = eSpecialEffect->IntAttribute("abscoord");
				specialeffect->fRange = eSpecialEffect->FloatAttribute("range");

				m_vecSpecialEffects.push_back(specialeffect);
			}
		}
	}

	// sound
	{
		tinyxml2::XMLElement* eSound = pRoot->FirstChildElement("sound");
		if (eSound) {
			m_strSound = eSound->Attribute("file");
		}
	}
}

aeditor::MPEffect::~MPEffect()
{
	for(vector<MPParticle*>::iterator iter = m_vecParticles.begin(); iter !=m_vecParticles.end();++iter)
	{
		delete *iter;
	}

	for(vector<MPAnimation*>::iterator iter = m_vecAnimations.begin(); iter !=m_vecAnimations.end();++iter)
	{
		delete *iter;
	}

	for(vector<MPSpecialEffect*>::iterator iter = m_vecSpecialEffects.begin(); iter !=m_vecSpecialEffects.end();++iter) {
		delete *iter;
	}
}

std::map<std::string, aeditor::MPEffect*> s_cache;


void aeditor::MPEffect::runEffectOnNode(CCNode* node, const std::string& path, MPEffectParam& param)
{
	char szBuff[128];
	aeditor::MPEffect* effectToRun;
	std::map<std::string, aeditor::MPEffect*>::iterator it = s_cache.find(path);
	if (it != s_cache.end()) {
		effectToRun = it->second;
	} else {
		s_cache[path] = effectToRun = new MPEffect(path);
	}

	if (effectToRun == 0) return;

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	// 添加执行序列帧
	for (vector<MPAnimation*>::iterator it = effectToRun->m_vecAnimations.begin(); it != effectToRun->m_vecAnimations.end(); ++it) {
		MPAnimation* pMPAnimation = *it;

		if (pMPAnimation->strFile.size() == 0) {
			sprintf(szBuff, "Mp file: %s, animation file: %s not found, can ignore.", path.c_str(), pMPAnimation->strFile.c_str());
			continue;
			//CCAssert(szBuff && false, szBuff);
		}

		CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
		frameCache->addSpriteFramesWithFile(pMPAnimation->strFile.c_str());
	
		int nFrameCnt = pMPAnimation->nFrameCnt;
		if(nFrameCnt <=0)
			continue;

		CCArray* animFrames = CCArray::createWithCapacity(pMPAnimation->nFrameCnt);
		char str[100] = {0};
		CCSpriteFrame* pFirstFrame = NULL;
		for(int i = 1; i <= nFrameCnt; i++)
		{
			sprintf(str, "%s%02d.png",pMPAnimation->strFrameName.c_str(), i);
			CCSpriteFrame *frame = frameCache->spriteFrameByName(str);
			animFrames->addObject(frame);
	
			if(i==1)
				pFirstFrame = frame;
		}
	
		// create an sprite without texture
		CCSprite *pAnmSprite = CCSprite::create();
		pAnmSprite->setDisplayFrame(pFirstFrame);
	
		bool bNeedFlip = false;
		if(param.isFlipY && pMPAnimation->bNeedFlip)
			bNeedFlip = true;
	
		pAnmSprite->setFlipY(bNeedFlip);
		pAnmSprite->setScale(pMPAnimation->fScale * param.scaleForAnimation);
		pAnmSprite->setRotation(pMPAnimation->fRotate);
		pAnmSprite->setAnchorPoint(ccp(0.5f, 0.5f));
		// 废弃：绝对坐标 pMPAnimation->nAbsCoord == 1
		pAnmSprite->setPosition(ccp(pMPAnimation->fOffsetx, bNeedFlip ? -pMPAnimation->fOffsety : pMPAnimation->fOffsety));
		pAnmSprite->setZOrder(pMPAnimation->nLayer);
	
		CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, (pMPAnimation->fPlayTime/nFrameCnt) / param.gameSpeed);
		CCAnimate *animN = CCAnimate::create(animation);
	
		CCDelayTime* pDelay = CCDelayTime::create(pMPAnimation->fDelay / param.gameSpeed);
		CCActionInterval* pFadeIn = CCFadeIn::create(pMPAnimation->fFadeInTime / param.gameSpeed);
		CCActionInterval* pFadeOut = CCFadeOut::create(pMPAnimation->fFadeOutTime / param.gameSpeed);
	
		CCActionInterval* pSeq = CCSequence::create(pFadeIn, animN, pFadeOut, CCRemoveSelf::create(true),  NULL);
		pAnmSprite->runAction(pSeq);
		node->addChild(pAnmSprite);
	}

	// 添加执行粒子
	for(vector<MPParticle*>::iterator it = effectToRun->m_vecParticles.begin(), ie = effectToRun->m_vecParticles.end(); it!=ie; ++it )
	{
		MPParticle* pMPParticle = *it;
		if(pMPParticle->strFile.length() == 0) continue;

		CCParticleSystemQuad* pParticleSystem = CCParticleSystemQuad::create(pMPParticle->strFile.c_str());
		if(!pParticleSystem) continue;

		// 废弃绝对坐标
		AE_Particle_Plist* ae_Particle_Plist = AE_Particle_Plist::create(pMPParticle->strFile, pMPParticle->fScale, 
			ccp(pMPParticle->fOffsetx, pMPParticle->fOffsety), pMPParticle->nLayer, 0, kCCPositionTypeFree, pMPParticle->fRotate);
	
		CCFiniteTimeAction* action = CCSequence::create(
			CCDelayTime::create(pMPParticle->fDelay),
			ae_Particle_Plist,
			NULL);
		node->runAction(action);
	}

	// 特殊效果 （屏幕震动 和 水波，用的地方不多，先注释掉）

	// 声音
	if(effectToRun->m_strSound.size() > 0) {
		AE_PlayWav* pPlayWav = AE_PlayWav::create(effectToRun->m_strSound);
		node->runAction(pPlayWav);
	}
	return;
}
