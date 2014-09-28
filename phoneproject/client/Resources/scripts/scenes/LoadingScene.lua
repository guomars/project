LoadingScene = class("LoadingScene");

function LoadingScene:create(type,params)
    scene = CCScene:create();
    LoadingScene.instance = LoadingScene.new();
		LoadingScene.instance:init(scene,params);
		LoadingScene.instance.type = type;
		LoadingScene.instance.params = params;
    
    return scene;
end

function LoadingScene:init(scene,params)
		cclog("LoadingScene:init");
		
		self.uilayer = UILayer:create();
    self.uilayer:scheduleUpdate();
    
    self.process = 0;
    
    self.scheduler = self.uilayer:getScheduler():scheduleScriptFunc(self.do_load,0.05,false)
    
    local widget = CreateWidgetFromJsonFile(GET_PATH(g_resource_path["scenes"], "loading/loading.json"));
		widget:setName("loading");
		local loading_image_widget = UIHelper:instance():seekWidgetByName(widget, "background");
    loading_image_widget:setPosition(GET_POS_CENTOR());
		self.uilayer:addWidget(widget);
		
		self.loading_bar = tolua.cast(UIHelper:instance():seekWidgetByName(widget, "loading_in"), "UIImageView");
		local rect = CCRectMake(0,0,0,36);
    self.loading_bar:setTextureRect(rect);
    self.loading_bar_original_pos = ccp(self.loading_bar:getPosition().x,self.loading_bar:getPosition().y);
    
    scene:addChild(self.uilayer);
end

function LoadingScene:do_load()
    --cclog("LoadingScene:do_load");
    local tmp_scene = LoadingScene.instance.scene;
    if (LoadingScene.instance.process == 0) then
        --cclog("LoadingScene BaseScene create");
        LoadingScene.instance.scene = BaseScene:create(LoadingScene.instance.type,LoadingScene.instance.params);
    elseif (LoadingScene.instance.process >= 100) then
        --cclog("LoadingScene BaseScene end");
        LoadingScene.instance.uilayer:getScheduler():unscheduleScriptEntry(LoadingScene.instance.scheduler);
        CCDirector:sharedDirector():replaceScene(LoadingScene.instance.scene);
        LoadingScene.instance.scene:release();
    else
        --cclog("LoadingScene BaseScene loading_init");
        BaseScene:loading_init(LoadingScene.instance.scene,LoadingScene.instance.params);
    end
    
    if (tmp_scene == nil and LoadingScene.instance.scene ~= nil) then
        --cclog("LoadingScene retain");
        LoadingScene.instance.scene:retain();
    end
end

function LoadingScene:set_load_process(process)
    if (process <= self.process) then
        return true;
    end
    
    cclog("LoadingScene process = "..process);
    
    self.process = process;
    
    local rect = CCRectMake(0,0,process/100*500,36);
    local pos = ccp(self.loading_bar_original_pos.x-250+process/100*250,self.loading_bar_original_pos.y);
    self.loading_bar:setTextureRect(rect);
    self.loading_bar:setPosition(pos);
		
		return false;
end