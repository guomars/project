MenuScene = class("MenuScene",BaseScene);

All_Scenes[SCENE_TYPE_MENU] = MenuScene.new();

function MenuScene:init(scene,params)
		cclog("MenuScene:init");
		self.uilayer = UILayer:create();
    self.uilayer:scheduleUpdate();
    
    self.scheduler = self.uilayer:getScheduler():scheduleScriptFunc(self.heartbeat,0.1,false);
    
    self.root_widget = CreateWidgetFromJsonFile(GET_PATH(g_resource_path["scenes"], "menu/menu.json"));
		self.root_widget:setName("menu_root");
		local menu_image_widget = UIHelper:instance():seekWidgetByName(self.root_widget, "menu_image");
    menu_image_widget:setPosition(GET_POS_CENTOR());
		self.uilayer:addWidget(self.root_widget);
		
		local pBtnBegin = UIHelper:instance():seekWidgetByName(self.root_widget, "begingame");
    local pBtnHelp= UIHelper:instance():seekWidgetByName(self.root_widget, "help");
    local pBtnExit= UIHelper:instance():seekWidgetByName(self.root_widget, "exit");
    local pTextNet = UIHelper:instance():seekWidgetByName(self.root_widget, "NetworkType");
    
    local pTextNetArea = tolua.cast(pTextNet, "UITextArea");
    local nwmgr = NetworkMgr:sharedMgr();
    local networktype = nwmgr:GetNetworkType();
    pTextNetArea:setText("Net:None");
    cclog("network="..networktype);
    if (0 == networktype) then
    		pTextNetArea:setText("Net:None");
    elseif (1 == networktype) then
    		pTextNetArea:setText("Net:WIFI");
    elseif (2 == networktype) then
    		pTextNetArea:setText("Net:2G");
    elseif (3 == networktype) then
    		pTextNetArea:setText("Net:3G");
    else
    		pTextNetArea:setText("Net:Unknowon");
    end
    
    GFuncMgr:GetInstance():AddFunc(tolua.cast(pBtnBegin, "CCObject"), tolua.cast(self.uilayer, "CCObject"), EVENT_UIWIDGET_RELEASE, "MenuScene:OnBtnBegin");
    GFuncMgr:GetInstance():AddFunc(tolua.cast(pBtnHelp, "CCObject"), tolua.cast(self.uilayer, "CCObject"), EVENT_UIWIDGET_RELEASE, "MenuScene:OnBtnHelp");
    GFuncMgr:GetInstance():AddFunc(tolua.cast(pBtnExit, "CCObject"), tolua.cast(self.uilayer, "CCObject"), EVENT_UIWIDGET_RELEASE, "MenuScene:OnBtnExit");
    
    self.on_btn_begin = false;
    self.on_btn_help = false;
    
    local assetsupdatemgr = AssetsUpdateManager:GetInstance();
    self.update_finish = false;
    self.update_param = update_param:create(assetsupdatemgr:GetCachePath(), assetsupdatemgr:GetTmpPath(), "http://111.193.197.219:9000/Package/", "md5.file", 10, 1);
    self.update_param:retain();
    
    scene:addChild(self.uilayer);
end

function MenuScene:heartbeat()

		if (BaseScene.instance.update_finish == true) then return end

		local pBtnBegin = UIHelper:instance():seekWidgetByName(BaseScene.instance.root_widget, "begingame");
    local pBtnHelp= UIHelper:instance():seekWidgetByName(BaseScene.instance.root_widget, "help");
    local pBtnExit= UIHelper:instance():seekWidgetByName(BaseScene.instance.root_widget, "exit");
    local pUpdate = UIHelper:instance():seekWidgetByName(BaseScene.instance.root_widget, "Update");
    local pTextUpdateArea = tolua.cast(pUpdate, "UITextArea");
    
		local assetsupdatemgr = AssetsUpdateManager:GetInstance();
		if (BaseScene.instance.need_update) then
				pTextUpdateArea:setText("Downloading Now");
				if (assetsupdatemgr:CheckUpdate(BaseScene.instance.update_param)) then
						if (BaseScene.instance.update_param:getRet()) then
								cclog("MenuScene:Update succed.");
						else
								cclog("MenuScene:Update failed.");
						end
						BaseScene.instance.update_finish = true;
						pBtnBegin:setVisible(true);
						pBtnHelp:setVisible(true);
						pBtnExit:setVisible(true);
						pTextUpdateArea:setVisible(false);
				end
		else
				pBtnBegin:setVisible(true);
				pBtnHelp:setVisible(true);
				pBtnExit:setVisible(true);
				pTextUpdateArea:setVisible(false);
		end
end

function MenuScene:OnBtnBegin(uid)
		cclog("MenuScene:OnBtnBegin");
		
		if (BaseScene.instance.on_btn_begin == nil or BaseScene.instance.on_btn_begin == true) then return end;
		BaseScene.instance.on_btn_begin = true;
		
		BaseScene.instance.update_param:release();
		BaseScene.instance.uilayer:getScheduler():unscheduleScriptEntry(BaseScene.instance.scheduler);
		params = {};
		local next_scene = BaseScene:create(SCENE_TYPE_CHOOSE_MAP,params);
		CCDirector:sharedDirector():replaceScene(next_scene);
end

function MenuScene:OnBtnHelp(uid)
		cclog("MenuScene:OnBtnHelp");
		
		if (BaseScene.instance.on_btn_help == nil or BaseScene.instance.on_btn_help == true) then return end;
		BaseScene.instance.on_btn_help = true;
		
		BaseScene.instance.update_param:release();
		BaseScene.instance.uilayer:getScheduler():unscheduleScriptEntry(BaseScene.instance.scheduler);
		local next_scene = GameScene:create();
		CCDirector:sharedDirector():replaceScene(next_scene);
end

function MenuScene:OnBtnExit(uid)
		cclog("MenuScene:OnBtnExit");
end
