ChooseMapScene = class("ChooseMapScene",BaseScene)

All_Scenes[SCENE_TYPE_CHOOSE_MAP] = ChooseMapScene.new();

function ChooseMapScene:init(scene,params)
    cclog("ChooseMapScene:init");
		self.uilayer = UILayer:create();
    self.uilayer:scheduleUpdate();
    
    self.root_widget = CreateWidgetFromJsonFile(GET_PATH(g_resource_path["scenes"], "choosemap/ChooseMap.json"));
		self.root_widget:setName("choosemap_root");
		local image_widget = UIHelper:instance():seekWidgetByName(self.root_widget, "background");
    image_widget:setPosition(GET_POS_CENTOR());
		self.uilayer:addWidget(self.root_widget);
		
		local datamgr = DataMgr:sharedMgr();
		
		local pBtnBack = UIHelper:instance():seekWidgetByName(self.root_widget, "back");
		GFuncMgr:GetInstance():AddFunc(tolua.cast(pBtnBack, "CCObject"), tolua.cast(self.uilayer, "CCObject"), EVENT_UIWIDGET_RELEASE, "ChooseMapScene:OnBtnBack");
		self.on_btn_back = false;
		
		self.on_btn_map = false;
		for i=1,6,1 do
		    local pBtnMap = UIHelper:instance():seekWidgetByName(self.root_widget, STRING_WITH_INT("map",i));
		    GFuncMgr:GetInstance():AddFunc(tolua.cast(pBtnMap, "CCObject"), tolua.cast(self.uilayer, "CCObject"), EVENT_UIWIDGET_RELEASE, STRING_WITH_INT("ChooseMapScene:OnBtnMap",i));
		    if i ~= 1 then
		        local activated = datamgr:GetInt(STRING_WITH_INT("activated_map",i),true);
		        cclog("activated_map i="..i.." activated="..activated);
		        if (activated ~= 1) then
		            DisableWidget(self.root_widget,STRING_WITH_INT("map",i));
		        end
		    end
		end
		
		--测试用，可以测试第2张地图能否点亮
		--datamgr:SetInt(STRING_WITH_INT("activated_map",2),1,true);
		--datamgr:SaveToFile();
		
		scene:addChild(self.uilayer);
end

function ChooseMapScene:OnBtnBack()
    cclog("ChooseMapScene:OnBtnBack");
    
    if (BaseScene.instance.on_btn_back == nil or BaseScene.instance.on_btn_back == true) then return end;
		BaseScene.instance.on_btn_back = true;
    
    local next_scene = BaseScene:create(SCENE_TYPE_MENU,params);
		CCDirector:sharedDirector():replaceScene(next_scene);
end

function ChooseMapScene:OnChooseMap(index)
    if (BaseScene.instance.on_btn_map == nil or BaseScene.instance.on_btn_map == true) then return end;
		BaseScene.instance.on_btn_map = true;

    params = {};
    params["index"] = index;
    local next_scene = LoadingScene:create(SCENE_TYPE_MAP,params);
		CCDirector:sharedDirector():replaceScene(next_scene);
end

function ChooseMapScene:OnBtnMap1()
    self:OnChooseMap(1);
end

function ChooseMapScene:OnBtnMap2()
    --目前还没开放
end

function ChooseMapScene:OnBtnMap3()
    --目前还没开放
end

function ChooseMapScene:OnBtnMap4()
    --目前还没开放
end

function ChooseMapScene:OnBtnMap5()
    --目前还没开放
end

function ChooseMapScene:OnBtnMap6()
    --目前还没开放
end