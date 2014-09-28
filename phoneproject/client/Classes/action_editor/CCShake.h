#ifndef __CCSHAKE_ACTION_H__
#define __CCSHAKE_ACTION_H__

#include "cocos2d.h"

NS_CC_BEGIN

class  CCShake : public CCActionInterval
{
public:
	/** initializes the action */
	bool initWithDuration(float duration,  CCPoint ptAmplitude, bool  bDampening, int nShakeNum);

	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual void startWithTarget(CCNode *pTarget);
	virtual void update(float time);

public:
	/** creates the action */
	static CCShake* create(float duration, CCPoint ptAmplitude, bool  bDampening, int nShakeNum);
protected:
	float shakeInterval;
	float nextShake;
	bool dampening;
	CCPoint startAmplitude;
	CCPoint amplitude;
	CCPoint last;
};

NS_CC_END

#endif // __CCSHAKE_ACTION_H__