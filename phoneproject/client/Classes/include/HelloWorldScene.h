#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "CocoGUILIB/BaseClasses/UIWidget.h"
#include "CocoGUILIB/UIWidgets/UINodeContainer.h"
#include "CocoGUILIB/System/UILayer.h"
#include "CocoGUILIB/System/UIHelper.h"
#include "GUI/CCEditBox/CCEditBox.h"
#include "ActionStubs.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;

class HelloWorld : public cocos2d::CCLayerColor
{
	UILayer* m_pUILayer;
	aeditor::ActionTemplateTable* m_actionRunner;
	UIWidget* m_Widget;
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif  // __HELLOWORLD_SCENE_H__