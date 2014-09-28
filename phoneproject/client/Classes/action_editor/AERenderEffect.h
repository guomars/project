#pragma once

#include "cocos2d.h"
#include <vector>

namespace aeditor 
{
	class RenderEffectSprite;

	class RenderEffect : public cocos2d::CCObject {
		friend class RenderEffectSprite;

	protected:
		cocos2d::CCSprite* m_input;			// weak ptr

		cocos2d::CCRenderTexture* m_rt;		// weak ptr

	protected:
		RenderEffect() : m_rt(NULL), m_input(NULL) {}

		void setOutput(cocos2d::CCRenderTexture* rt) {
			m_rt = rt;
		}

		void doEffect(cocos2d::CCSprite* input) {
			CCAssert(m_rt != NULL, "m_rt == NULL, why ???");

			m_input = input;

			beforeDoEffect();
			
			realDoEffect();

			afterDoEffect();

			m_input = NULL;
		}

	public:
		virtual ~RenderEffect() {}

	protected:

		virtual void realDoEffect() {}

		virtual void beforeDoEffect() {}

		virtual void afterDoEffect() {}
	};

	class RenderEffectSprite : public cocos2d::CCSprite {
	private:
		cocos2d::CCSprite* input;
		cocos2d::CCRenderTexture* rt1;
		cocos2d::CCRenderTexture* rt2;
		std::vector<RenderEffect*> effects;

		void addEffect(RenderEffect* effect);

		void doEffect();

		virtual void visit();

	public:
		RenderEffectSprite() : input(NULL), rt1(NULL), rt2(NULL) {

		}

		static RenderEffectSprite* create(cocos2d::CCSprite* _input) {
			RenderEffectSprite* ret = new RenderEffectSprite();
			ret->autorelease();

			ret->input = _input;

			ret->addChild(_input);

			return ret;
		}

		virtual ~RenderEffectSprite() {
			for (std::vector<RenderEffect*>::iterator it = effects.begin(); it != effects.end(); ++it) {
				CC_SAFE_RELEASE(*it);
			}
			effects.clear();

			CC_SAFE_RELEASE(input);
			CC_SAFE_RELEASE(rt1);
			CC_SAFE_RELEASE(rt2);
		}
	};
}