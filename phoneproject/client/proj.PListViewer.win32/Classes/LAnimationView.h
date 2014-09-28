#pragma once

#include <cocos2d.h>

USING_NS_CC;

extern void setLayer(CCLayer* layer);

class LParticleShow : public CCLayer {
private:
	std::string m_fileName;
	CCParticleSystemQuad* m_particleSystemQuad;

public:
	virtual void ccTouchEnded(CCSet *pTouches, CCEvent *pEvent);

	static LParticleShow* create(std::string fileName) {
		LParticleShow* ret = new LParticleShow();
		ret->m_fileName = fileName;
		ret->autorelease();
		ret->init();

		ret->m_particleSystemQuad = CCParticleSystemQuad::create(fileName.c_str());
		ret->m_particleSystemQuad->setPosition(384, 512);
		ret->addChild(ret->m_particleSystemQuad);
		return ret;
	}
};

class LAnimationView : public CCLayer {
public:
	CCArray* menuItems;
	CCPoint m_tBeginPos;
	CCMenu* m_menu;
	CCMenuItem* menuItemReturn;
	CCNode* m_play;
	bool isPariticle;

	virtual bool init();

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);

	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);

	void onBtnSelectFile(CCObject* sender);

	void onBtnReturn(CCObject* sender);

	static LAnimationView* create(bool isPariticle) {
		LAnimationView* ret = new LAnimationView();
		ret->autorelease();
		ret->isPariticle = isPariticle;
		ret->init();
		return ret;
	}

	virtual ~LAnimationView() {
		CC_SAFE_RELEASE(menuItems);
	}
};