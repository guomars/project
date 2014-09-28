#ifndef __EFFECT_H__
#define __EFFECT_H__

#include "cocos2d.h"
#include <vector>
#include <map>
USING_NS_CC;
using namespace std;

namespace aeditor {
	// particle settings
	typedef struct _MPParticle
	{
		string strName;
		string strFile;
		int nLayer;
		float fDelay;
		float fOffsetx;
		float fOffsety;
		float fScale;
		float fRotate;
		int nAbsCoord;

		_MPParticle()
			: strName(""), strFile(""), nLayer(1), fDelay(0.0f), fOffsetx(0.0f), fOffsety(0.0f), fScale(1.0f), fRotate(0.0f), nAbsCoord(0)
		{}
	}MPParticle;

	// animations
	typedef struct _MPAnimation
	{
		string strName;
		string strFile;
		int nLayer;
		float fDelay;

		int nFrameCnt;
		string strFrameName;

		float fPlayTime;
		float fOffsetx;
		float fOffsety;

		int nAbsCoord;

		float fScale;
		float fRotate;

		float fFadeInTime;
		float fFadeOutTime;

		bool bNeedFlip;	// if true,  animation should flip when attacker is above the target

		_MPAnimation()
			: strName(""), strFile(""), nLayer(1), fDelay(0.0f), nFrameCnt(0), strFrameName(""), fPlayTime(1.0f), fOffsetx(0.0f), fOffsety(0.0f),
			nAbsCoord(0), fScale(1.0f), fRotate(0.0f), fFadeInTime(0.0f), fFadeOutTime(0.0f), bNeedFlip(true)
		{}
	}MPAnimation;

	// special effects
	typedef struct _MPSpecialEffect
	{
		string strName;
		int nLayer;

		int nType;

		float fDelay;
		float fTime;

		float fOffsetx;
		float fOffsety;

		int nAbsCoord;

		float fRange;
		CCPoint vPlayPos;	// not loaded from xml
	}MPSpecialEffect;

	class MPEffectParam {
	public:
		float scaleForAnimation;
		float gameSpeed;
		bool isFlipY;

		MPEffectParam() : scaleForAnimation(1.3f / 2.0f), gameSpeed(1.0f), isFlipY(false) {}
	};

	// Effect
	class MPEffect : public CCObject
	{
	public:
		MPEffect(const std::string& path);

		~MPEffect();

		static void runEffectOnNode(CCNode* node, const std::string& path, MPEffectParam& param);

	protected:
		string m_strEffectName;

		vector<MPParticle*> m_vecParticles;
		vector<MPAnimation*> m_vecAnimations;
		vector<MPSpecialEffect*> m_vecSpecialEffects;	
		string m_strSound;
	};
}

#endif