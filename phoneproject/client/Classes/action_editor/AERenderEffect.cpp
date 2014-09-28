#include "AERenderEffect.h"

using namespace cocos2d;

namespace aeditor 
{
	void RenderEffectSprite::addEffect( RenderEffect* effect )
	{
		effect->retain();

		int n = effects.size();
		if (n == 0) {
			rt1 = CCRenderTexture::create(input->getContentSize().width, input->getContentSize().height);
			rt1->retain();
		} else if (n == 1) {
			rt2 = CCRenderTexture::create(input->getContentSize().width, input->getContentSize().height);
			rt2->retain();
		}

		effects.push_back(effect);
		effect->setOutput(n % 2 == 0 ? rt1 : rt2);
	}

	void RenderEffectSprite::doEffect()
	{
		for (size_t i = 0; i < effects.size(); ++i) {
			if (i == 0) {
				effects[i]->doEffect(input);
			} else {
				effects[i]->doEffect(effects[i - 1]->m_rt->getSprite());
			}
		}
	}

	void RenderEffectSprite::visit()
	{
		doEffect();

		if (effects.size() > 0) {
			setTexture(effects[effects.size() - 1]->m_rt->getSprite()->getTexture());
			setTextureRect(effects[effects.size() - 1]->m_rt->getSprite()->getTextureRect());
		}

		// quick return if not visible. children won't be drawn.
		if (!m_bVisible)
		{
			return;
		}
		kmGLPushMatrix();

		if (m_pGrid && m_pGrid->isActive())
		{
			m_pGrid->beforeDraw();
		}

		// just draw input
		this->transform();
		this->draw();

		if (m_pGrid && m_pGrid->isActive())
		{
			m_pGrid->afterDraw(this);
		}

		kmGLPopMatrix();
	}

}