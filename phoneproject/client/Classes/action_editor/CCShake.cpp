#include "CCShake.h"

#include "sprite_nodes/CCSprite.h"
#include "base_nodes/CCNode.h"
#include "support/CCPointExtension.h"
#include "CCStdC.h"
//#include "CCActionInstant.h"
#include "cocoa/CCZone.h"
#include <stdarg.h>


NS_CC_BEGIN
//
// Shake
//
CCShake* CCShake::create(float duration, CCPoint ptAmplitude, bool  bDampening, int nShakeNum)
{
	CCShake *pShake = new CCShake();
	pShake->initWithDuration(duration, ptAmplitude, bDampening, nShakeNum);
	pShake->autorelease();

	return pShake;
}

bool CCShake::initWithDuration(float duration,  CCPoint ptAmplitude, bool  bDampening, int nShakeNum)
{
	if (CCActionInterval::initWithDuration(duration))
	{		
		startAmplitude	= ptAmplitude;
		dampening	= bDampening;

		// calculate shake intervals based on the number of shakes
		if(nShakeNum == 0)
			shakeInterval = 0;
		else
			shakeInterval = 1.f/nShakeNum;

		return true;
	}

	return false;
}

CCObject* CCShake::copyWithZone(CCZone *pZone)
{
	CCZone* pNewZone = NULL;
	CCShake* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		//in case of being called at sub class
		pCopy = (CCShake*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new CCShake();
		pZone = pNewZone = new CCZone(pCopy);
	}

	CCActionInterval::copyWithZone(pZone);

	pCopy->initWithDuration(m_fDuration, startAmplitude, dampening, shakeInterval );

	CC_SAFE_DELETE(pNewZone);
	return pCopy;
}

void CCShake::startWithTarget(CCNode *pTarget)
{
	CCActionInterval::startWithTarget(pTarget);
	amplitude	= startAmplitude;
	last		= CCPointZero;
	nextShake	= 0;
}

void CCShake::update(float time)
{
	// waits until enough time has passed for the next shake
	if(shakeInterval == 0)
	{
		// shake every frame!
	} 
	else if(time < nextShake)
		return; // haven't reached the next shake point yet
	else
		nextShake += shakeInterval; // proceed with shake this time and increment for next shake goal

	// calculate the dampening effect, if being used
	if(dampening)
	{
		float dFactor = (1-time);
		amplitude.x = dFactor * startAmplitude.x;
		amplitude.y = dFactor * startAmplitude.y;
	}

	CCPoint new1 = ccp((CCRANDOM_0_1()*amplitude.x*2) - amplitude.x,(CCRANDOM_0_1()*amplitude.y*2) - amplitude.y);

	// simultaneously un-move the last shake and move the next shake
	m_pTarget->setPosition(ccpAdd(ccpSub(m_pTarget->getPosition(), last),new1));

	// store the current shake value so it can be un-done
	last = new1;
}

NS_CC_END
