WelcomeScene = class("WelcomeScene",BaseScene);

All_Scenes[SCENE_TYPE_WELCOME] = WelcomeScene.new();

function WelcomeScene:init(scene,params)
		cclog("WelcomeScene:init");
		local uilayer = UILayer:create();
    uilayer:scheduleUpdate();
    
    local widget = CreateWidgetFromJsonFile(GET_PATH(g_resource_path["scenes"], "welcome/welcome.json"));
		widget:setName("welcome");
		local welcome_image_widget = UIHelper:instance():seekWidgetByName(widget, "welcome_image");
    welcome_image_widget:setPosition(GET_POS_CENTOR());
		uilayer:addWidget(widget);
		
		local actionRunner = aeditor.ActionTemplateTable:create(GET_PATH(g_resource_path["aeditor"],"template.xml"), scene);
		actionRunner:RunUIAction(GET_PATH(g_resource_path["aeditor"],"welcome.ue"), widget);
    
    scene:addChild(uilayer);
    
    Global:CreateTimer(self, 1, 1, 1, 0);
end

function WelcomeScene:OnTimer(id, period, count, arg)
    params = {};
		local next_scene = BaseScene:create(SCENE_TYPE_MENU,params);
		CCDirector:sharedDirector():replaceScene(next_scene);
end