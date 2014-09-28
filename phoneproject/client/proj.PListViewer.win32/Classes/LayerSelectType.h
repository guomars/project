#pragma once

#include <cocos2d.h>
#include <string>

USING_NS_CC;

// 用来选择是序列帧动画，还是粒子动画
class LayerSelectType : public CCLayer {
public:
	virtual bool init();

	static CCScene* scene();

	void onBtnAnimationView(CCObject* pSender);

	void onBtnParticleView(CCObject* pSender);

	CREATE_FUNC(LayerSelectType);
};