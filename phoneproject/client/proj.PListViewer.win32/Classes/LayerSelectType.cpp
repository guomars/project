#include "LayerSelectType.h"
#include "LAnimationView.h"
#include "LAnimationView2.h"

static CCLayer* s_curLayer = NULL;
static CCScene* s_curScene = NULL;

void setLayer(CCLayer* layer) {
	s_curScene->removeChild(s_curLayer);
	s_curScene->addChild(s_curLayer = layer);
}

void LayerSelectType::onBtnAnimationView(CCObject* pSender)
{
	setLayer(LAnimationView2::create(false));
}

void LayerSelectType::onBtnParticleView(CCObject* pSender)
{
	setLayer(LAnimationView2::create(true));
}

bool LayerSelectType::init() {
	CCArray* menuItems = CCArray::create();
	{
		std::wstring wstr = std::wstring(L"序列帧动画");
		char* str = cc_utf16_to_utf8((const unsigned short *)wstr.c_str(), wstr.size(), NULL, NULL);
		CCLabelTTF* label = CCLabelTTF::create(str, "SimHei", 64);
		CCMenuItem* menuItem = CCMenuItemLabel::create(label, this, menu_selector(LayerSelectType::onBtnAnimationView));
		menuItems->addObject(menuItem);
		menuItem->setPosition(ccp(-100, 100));
	}
	{
		std::wstring wstr = std::wstring(L"粒子动画");
		char* str = cc_utf16_to_utf8((const unsigned short *)wstr.c_str(), wstr.size(), NULL, NULL);
		CCLabelTTF* label = CCLabelTTF::create(str, "SimHei", 64);
		CCMenuItem* menuItem = CCMenuItemLabel::create(label, this, menu_selector(LayerSelectType::onBtnParticleView));
		menuItems->addObject(menuItem);
		menuItem->setPosition(ccp(-100, -100));
	}

	CCMenu* menu = CCMenu::createWithArray(menuItems);
	this->addChild(menu);
	return true;
}

CCScene* LayerSelectType::scene()
{
	CCScene *scene = CCScene::create();
	LayerSelectType* layer = LayerSelectType::create();
	//LAnimationView* layer = LAnimationView::create(true);
	scene->addChild(layer);

	s_curScene = scene;
	s_curLayer = layer;
	return scene;
}
