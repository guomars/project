#pragma once

#include <cocos2d.h>

USING_NS_CC;

extern void setLayer(CCLayer* layer);

class LAnimationView2 : public CCLayer {
public:
	CCPoint m_tBeginPos;
	CCMenuItem* menuItemReturn;
	std::vector<std::string> m_files;
	bool isPariticle;

	virtual bool init();

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);

	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);

	void checkOn();

	void onBtnSelectFile(CCObject* sender);

	void onBtnReturn(CCObject* sender);

	static LAnimationView2* create(bool isPariticle) {
		LAnimationView2* ret = new LAnimationView2();
		ret->autorelease();
		ret->isPariticle = isPariticle;
		ret->init();
		return ret;
	}
};