--场景函数
MapScene = class("MapScene")

All_Scenes[SCENE_TYPE_MAP] = MapScene.new();

--一些现实的优先级
ZORDER_MONSTER = 0;
ZORDER_TOWER = 0;
ZORDER_OUTSIDE_BLOCK = 1;
ZORDER_INSIDE_BLOCK = 2;
ZORDER_TOWER_RANGE = 3;
ZORDER_TMP_TOWER = 4;
ZORDER_TOWER_CTRL_SELL = 5;
ZORDER_TOWER_CTRL_LEVEL_UP = 5;

function MapScene:init(scene, params)
	  if (LoadingScene.instance:set_load_process(5) == false) then
	      cclog("MapScene init require");
	      
        require ("scripts.logic.SkillActivateObject")
        require ("scripts.logic.SkillPerform")
        require ("scripts.logic.Skill")
        require ("scripts.logic.EffectActivateObject")
        require ("scripts.logic.Effect")
        require ("scripts.logic.MapLogic")
        require ("scripts.logic.Monster")
        require ("scripts.logic.Tower")
        require ("scripts.logic.Arrow")
        
        return;
    end
    
    local index = params["index"];
    local datamgr = DataMgr:sharedMgr();
    local mapmgr = GMapMgr:GetInstance();
    
    if (LoadingScene.instance:set_load_process(10) == false) then
        cclog("MapScene:init");
    		CalcCostMS("");
    		
    		self.scene = scene;
    		self.uilayer = UILayer:create();
        self.uilayer:scheduleUpdate();
        
        local uilayer_rootwidget = tolua.cast(self.uilayer:getRootWidget(), "UIWidget");
        self.uilayer_container = uilayer_rootwidget:getContainerNode();
        
        self.in_set = false;
        	
        return;
    end
    
    if (LoadingScene.instance:set_load_process(30) == false) then
        --创建游戏逻辑管理
        self.maplogic = MapLogic:create(self, index);
            
        return;
    end
    
    if (LoadingScene.instance:set_load_process(35) == false) then
        --初始化动作播放器
        self.actionRunner = aeditor.ActionTemplateTable:create(GET_PATH(g_resource_path["aeditor"],"template.xml"), self.scene);
        
        --注册一个定时函数
        self.scheduler = self.uilayer:getScheduler():scheduleScriptFunc(self.Heartbeat,self.maplogic.tick_time,false)
        
        --加载地图的背景文件
        local tmp = STRING_WITH_INT("maps/map",index);
        local path = GET_PATH(tmp,".json");
    
    		self.root_widget = CreateWidgetFromJsonFile(GET_PATH(g_resource_path["scenes"], path));
    		self.root_widget:setName("map_root");
    		local map_image_widget = UIHelper:instance():seekWidgetByName(self.root_widget, "map_background");
        map_image_widget:setPosition(ccp(GET_POS_CENTOR().x+50,GET_POS_CENTOR().y));
    		self.uilayer:addWidget(self.root_widget);
    		    
    		return;
    end
		
		if (LoadingScene.instance:set_load_process(60) == false) then
		    --加载控制界面
    		self.control_widget = CreateWidgetFromJsonFile(GET_PATH(g_resource_path["scenes"], "maps/towercontrol/towercontrol.json"));
    		self.control_widget:setName("control_root");
    		self.control_widget:setWidgetZOrder(999);
    		self.control_image_widget = UIHelper:instance():seekWidgetByName(self.control_widget, "background");
    		self.control_image_widget:setPosition(GET_POS_CENTOR());
    		self.uilayer:addWidget(self.control_widget);
    		
    		self.pImageInfo = UIHelper:instance():seekWidgetByName(self.control_widget, "info");
    		self.pText = tolua.cast(UIHelper:instance():seekWidgetByName(self.control_widget, "text"), "UITextArea");
    		self.pImageControl = UIHelper:instance():seekWidgetByName(self.control_widget, "towercontrol");
    		self.pSellPriceText = tolua.cast(UIHelper:instance():seekWidgetByName(self.control_widget, "sell_price"), "UITextArea");
    		self.pLevelUpPriceText = tolua.cast(UIHelper:instance():seekWidgetByName(self.control_widget, "levelup_price"), "UITextArea");
    		self.pFinal = UIHelper:instance():seekWidgetByName(self.control_widget, "final");
    		self.pSuccess = UIHelper:instance():seekWidgetByName(self.control_widget, "success");
    		self.pFail = UIHelper:instance():seekWidgetByName(self.control_widget, "fail");
    		self.pFinalInfo1 = tolua.cast(UIHelper:instance():seekWidgetByName(self.control_widget, "info1"), "UITextArea");
    		self.pFinalInfo2 = tolua.cast(UIHelper:instance():seekWidgetByName(self.control_widget, "info2"), "UITextArea");
    		    
    		return;
		end
		
		if (LoadingScene.instance:set_load_process(65) == false) then
		    --设置控制界面按钮绑定
    		self.pBtnSet = UIHelper:instance():seekWidgetByName(self.control_widget, "set");
    		GFuncMgr:GetInstance():AddFunc(tolua.cast(self.pBtnSet, "CCObject"), tolua.cast(self.uilayer, "CCObject"), EVENT_UIWIDGET_RELEASE, "MapScene:OnBtnSet");
    		
    		self.pBtnMenu = UIHelper:instance():seekWidgetByName(self.control_widget, "menu");
    		GFuncMgr:GetInstance():AddFunc(tolua.cast(self.pBtnMenu, "CCObject"), tolua.cast(self.uilayer, "CCObject"), EVENT_UIWIDGET_RELEASE, "MapScene:OnBtnMenu");
    		self.on_btn_menu = false;
    		
    		self.pBtnContinue = UIHelper:instance():seekWidgetByName(self.control_widget, "continue");
    		GFuncMgr:GetInstance():AddFunc(tolua.cast(self.pBtnContinue, "CCObject"), tolua.cast(self.uilayer, "CCObject"), EVENT_UIWIDGET_RELEASE, "MapScene:OnBtnContinue");
    		
    		self.pBtnFinalMenu = UIHelper:instance():seekWidgetByName(self.control_widget, "final_menu");
    		GFuncMgr:GetInstance():AddFunc(tolua.cast(self.pBtnFinalMenu, "CCObject"), tolua.cast(self.uilayer, "CCObject"), EVENT_UIWIDGET_RELEASE, "MapScene:OnBtnFinalMenu");
    		self.on_btn_final_menu = false;
    		
    		self.pBtnFinalChoose = UIHelper:instance():seekWidgetByName(self.control_widget, "final_choose");
    		GFuncMgr:GetInstance():AddFunc(tolua.cast(self.pBtnFinalChoose, "CCObject"), tolua.cast(self.uilayer, "CCObject"), EVENT_UIWIDGET_RELEASE, "MapScene:OnBtnFinalChoose");
    		self.on_btn_final_choose = false;
    		
    		self.play_speed = 1;
    		self.pBtnPlay = UIHelper:instance():seekWidgetByName(self.control_widget, "play");
    		GFuncMgr:GetInstance():AddFunc(tolua.cast(self.pBtnPlay, "CCObject"), tolua.cast(self.uilayer, "CCObject"), EVENT_UIWIDGET_RELEASE, "MapScene:OnBtnPlay");
    		
    		self.pBtnSpeed = UIHelper:instance():seekWidgetByName(self.control_widget, "speed");
    		GFuncMgr:GetInstance():AddFunc(tolua.cast(self.pBtnSpeed, "CCObject"), tolua.cast(self.uilayer, "CCObject"), EVENT_UIWIDGET_RELEASE, "MapScene:OnBtnSpeed");
    		
    		GFuncMgr:GetInstance():AddFunc(tolua.cast(self.control_image_widget, "CCObject"), tolua.cast(self.uilayer, "CCObject"), EVENT_UIWIDGET_PUSH_DOWN, "MapScene:OnBtnControlPush");
    		GFuncMgr:GetInstance():AddFunc(tolua.cast(self.control_image_widget, "CCObject"), tolua.cast(self.uilayer, "CCObject"), EVENT_UIWIDGET_RELEASE, "MapScene:OnBtnControlRelease");
    		GFuncMgr:GetInstance():AddFunc(tolua.cast(self.control_image_widget, "CCObject"), tolua.cast(self.uilayer, "CCObject"), EVENT_UIWIDGET_MOVE, "MapScene:OnBtnControlMove");
    		    
    		return;
		end
		
		if (LoadingScene.instance:set_load_process(70) == false) then
		    --加载箭塔地形块
    		self.show_block = false;
    		
    		self.outside_sprite = {};
    		self.block_outside_batch = CCSpriteBatchNode:create(GET_PATH(g_resource_path["scenes"], "maps/others/outside.png"));
    		self.uilayer_container:addChild(self.block_outside_batch);
    		SET_NODE_ZORDER(self.block_outside_batch, ZORDER_OUTSIDE_BLOCK);
    		
    		self.inside_sprite = CCSprite:create(GET_PATH(g_resource_path["scenes"], "maps/others/inside.png"));
    		self.uilayer_container:addChild(self.inside_sprite);
    		SET_NODE_ZORDER(self.inside_sprite, ZORDER_INSIDE_BLOCK);
    		self.inside_sprite:setVisible(false);
    		self.inside_sprite:setScale(2);
    		self.inside_sprite:setPosition(GET_POS_CENTOR().x,GET_POS_CENTOR().y);
    		
    		for i=0,self.maplogic.rows-1,1 do
    		    self.outside_sprite[i] = {};
    		    for j=0,self.maplogic.cols-1,1 do
    		        local grid = mapmgr:GetMapGrid(i,j);
    		        if (grid == 3) then
    		            local block_outside_sprite = CCSprite:createWithTexture(self.block_outside_batch:getTexture());
        		        block_outside_sprite:setPosition(self.maplogic:ColIndexToX(j),self.maplogic:RowIndexToY(i));
        		        self.block_outside_batch:addChild(block_outside_sprite);
        		        self.outside_sprite[i][j] = block_outside_sprite;
        		        self.outside_sprite[i][j]:setVisible(false);
        		        self.outside_sprite[i][j]:setScale(2);
    		        end
    		    end
    		end
    		
    		return;
		end
		
		if (LoadingScene.instance:set_load_process(85) == false) then
		    --绑定塔的控件
    		self.tower_control = {};
    		self.tower_lock = {};
    		self.tower_control_count = 6;
    		for i=1,self.tower_control_count,1 do
            self.tower_control[i] = UIHelper:instance():seekWidgetByName(self.control_widget, STRING_WITH_INT("tower",i));
            self.tower_lock[i] = UIHelper:instance():seekWidgetByName(self.control_widget, STRING_WITH_INT("towerlock",i));
            if i == 1 or (datamgr:GetInt(STRING_WITH_INT("MapScene_tower",i),true) == 1) then
                self.tower_lock[i]:setVisible(false);
            end
    		end
    		
    		return;
		end
		
		if (LoadingScene.instance:set_load_process(90) == false) then
		    --加载圆环
    		self.tower_range = CCSprite:create(GET_PATH(g_resource_path["scenes"], "maps/others/round.png"));
    		self.uilayer_container:addChild(self.tower_range);
    		self.tower_range:setVisible(false);
    		SET_NODE_ZORDER(self.tower_range, ZORDER_TOWER_RANGE);
    		
    		return;
		end
		
		if (LoadingScene.instance:set_load_process(95) == false) then
		    --加载箭塔升级界面
        self.tower_control_sell = CCSprite:create(GET_PATH(g_resource_path["scenes"], "maps/others/sell.png"));
    		self.tower_control_sell:setVisible(false);
    		SET_NODE_ZORDER(self.tower_control_sell, ZORDER_TOWER_CTRL_SELL);
    		self.uilayer_container:addChild(self.tower_control_sell);
    		
    		self.tower_control_levelup = CCSprite:create(GET_PATH(g_resource_path["scenes"], "maps/others/levelup.png"));
    		self.tower_control_levelup:setVisible(false);
    		SET_NODE_ZORDER(self.tower_control_levelup, ZORDER_TOWER_CTRL_LEVEL_UP);
    		self.uilayer_container:addChild(self.tower_control_levelup);
    		    
    		--把layer添加到scene中去进行显示
		    scene:addChild(self.uilayer);
    		    
		    return;
		end
		
		if (LoadingScene.instance:set_load_process(100) == false) then
		    return;
		end
		
		CalcCostMS("MapScene:init");
end

--以下是控件的一些触摸回调
function MapScene:OnBtnSet()
    cclog("MapScene:OnBtnSet");
    
    if (BaseScene.instance.maplogic:IsEnd()) then return end;
    
    BaseScene.instance.pBtnMenu:setVisible(true);
    BaseScene.instance.pBtnContinue:setVisible(true);
    
    local director = CCDirector:sharedDirector();
    director:pause();
    
    BaseScene.instance.in_set = true;
end

function MapScene:OnBtnMenu()
    cclog("MapScene:OnBtnMenu");
    
    if (BaseScene.instance.on_btn_menu == nil or BaseScene.instance.on_btn_menu == true) then return end;
		BaseScene.instance.on_btn_menu = true;
    
    BaseScene.instance.uilayer:getScheduler():unscheduleScriptEntry(BaseScene.instance.scheduler);
    local director = CCDirector:sharedDirector();
    director:resume();

    params = {};
    local next_scene = BaseScene:create(SCENE_TYPE_MENU,params);
		CCDirector:sharedDirector():replaceScene(next_scene);
end

function MapScene:OnBtnContinue()
    cclog("MapScene:OnBtnContinue");
    
    BaseScene.instance.pBtnMenu:setVisible(false);
    BaseScene.instance.pBtnContinue:setVisible(false);
    
    local director = CCDirector:sharedDirector();
    director:resume();
    
    BaseScene.instance.in_set = false;
end

function MapScene:OnBtnFinalMenu()
    cclog("MapScene:OnBtnFinalMenu");
    
    if (BaseScene.instance.on_btn_final_menu == nil or BaseScene.instance.on_btn_final_menu == true) then return end;
		BaseScene.instance.on_btn_final_menu = true;
		
		BaseScene.instance.uilayer:getScheduler():unscheduleScriptEntry(BaseScene.instance.scheduler);
		
		params = {};
    local next_scene = BaseScene:create(SCENE_TYPE_MENU,params);
		CCDirector:sharedDirector():replaceScene(next_scene);
end

function MapScene:OnBtnFinalChoose()
    cclog("MapScene:OnBtnFinalChoose");
    
    if (BaseScene.instance.on_btn_final_choose == nil or BaseScene.instance.on_btn_final_choose == true) then return end;
		BaseScene.instance.on_btn_final_choose = true;
		
		BaseScene.instance.uilayer:getScheduler():unscheduleScriptEntry(BaseScene.instance.scheduler);
		
		params = {};
    local next_scene = BaseScene:create(SCENE_TYPE_CHOOSE_MAP,params);
		CCDirector:sharedDirector():replaceScene(next_scene);
end

function MapScene:OnBtnSpeed()
    cclog("MapScene:OnBtnSpeed");
    
    BaseScene.instance.play_speed = BaseScene.instance.play_speed + 1;
    CCDirector:sharedDirector():getScheduler():setTimeScale(BaseScene.instance.play_speed);
    
    cclog("play_speed="..BaseScene.instance.play_speed);
end

function MapScene:OnBtnPlay()
    cclog("MapScene:OnBtnPlay");
    
    BaseScene.instance.play_speed = 1;
    CCDirector:sharedDirector():getScheduler():setTimeScale(1);
end

function MapScene:OnBtnControlPush(obj)
    --cclog("MapScene:OnBtnControlPush");
    
    if (BaseScene.instance.maplogic:IsEnd()) then return end;
    if (BaseScene.instance.in_set == true) then return end;
    
    local pos = BaseScene.instance.control_image_widget:getTouchStartPos();
    cclog("x="..pos.x.." y="..pos.y);
    for i=1,BaseScene.instance.tower_control_count,1 do
        if (BaseScene.instance.tower_control[i]:pointAtSelfBody(pos) == true) then
            cclog("TowerControlActivate");
            BaseScene.instance:TowerControlActivate(i, pos.x, pos.y+100);
        end
    end
    
    BaseScene.instance.maplogic:OnBtnControlPush(pos);
end

function MapScene:OnBtnControlRelease(obj)
    --cclog("MapScene:OnBtnControlRelease");
    
    if (BaseScene.instance.maplogic:IsEnd()) then return end;
    if (BaseScene.instance.in_set == true) then return end;
    
    local pos = BaseScene.instance.control_image_widget:getTouchEndPos();
    
    if (BaseScene.instance.sel_tower_type ~= 0) then
        BaseScene.instance:HideBlock();
	      BaseScene.instance:RemoveTmpTower();
	    
	      local row = BaseScene.instance.maplogic:YToRowIndex(pos.y+100);
	      local col = BaseScene.instance.maplogic:XToColIndex(pos.x);
	    
	      if (BaseScene.instance.maplogic:CheckCanBuildTower(row,col) == true) then
	          BaseScene.instance.maplogic:CreateTower(row, col, BaseScene.instance.sel_tower_type);
	      end
	    
	      BaseScene.instance.sel_tower_type = 0;
    end
    
    BaseScene.instance.maplogic:OnBtnControlRelease(pos);
end

function MapScene:OnBtnControlMove(obj,x,y)
    --cclog("MapScene:OnBtnControlMove x="..x.." y="..y);
    
    if (BaseScene.instance.maplogic:IsEnd()) then return end;
    if (BaseScene.instance.in_set == true) then return end;
    
    local pos = ccp(x,y);
    if (BaseScene.instance.control_image_widget:pointAtSelfBody(pos) == false) then
        BaseScene.instance:OnBtnControlRelease(obj)
        return;
    end
    
    BaseScene.instance:RefreshControlSprite(x,y+100);
    
    BaseScene.instance.maplogic:OnBtnControlMove(x,y);
end

--以下是地图场景的一些功能函数
function MapScene:TowerControlActivate(tower_type, x, y)
    cclog("MapScene:TowerControlActivate");
    
    if (self.maplogic:IsEnd()) then return end;
    if (self.in_set == true) then return end;
    
    --判断tower_type这个箭塔是否已经激活
    if (self.maplogic:CheckTowerActivated(tower_type) == false) then return end;
    
    self.sel_tower_type = tower_type;
    self:ShowBlock();
    
    self:AddTmpTower(tower_type,x,y);
end

function MapScene:AddTmpTower(type,x,y)
    if (self.tmp_tower ~= nil) then
        self:RemoveTmpTower();
    end
    
    local tmp = STRING_WITH_INT("t",type);
    local pngfile = GET_PATH(tmp,"_1.png");
    self.tmp_tower = CCSprite:create(GET_PATH(g_resource_path["towers"], pngfile));
    SET_NODE_ZORDER(self.tmp_tower, ZORDER_TMP_TOWER);
    self.tmp_tower:setPosition(x,y);
    self.tmp_tower:setScale(1.5);
    self.uilayer:addChild(self.tmp_tower);
end

function MapScene:RemoveTmpTower()
    if (self.tmp_tower == nil) then
        return;
    end
    
    self.uilayer:removeChild(self.tmp_tower,true);
    self.tmp_tower = nil;
end

function MapScene:AddTowerControl(tower,sell_price,levelup_price)
    cclog("MapScene:AddTowerControl row="..tower.row.." col="..tower.col);
    
    local x = self.maplogic:ColIndexToX(tower.col);
    local y = self.maplogic:RowIndexToY(tower.row);
    
    --local towerconfig_table = GetTable("towerconfig");
    --local sight_range = tonumber(towerconfig_table:GetRecByColName(tower.type, STRING_WITH_INT("sight_range",tower.level)));
    local range = 200;
    local offset = range/2;
    if (offset > 100) then
        offset = 100;
    end
    
    self.tower_range:setScale(2*range/200);
    self.tower_range:setPosition(x,y);
    self.tower_range:setVisible(true);
    
    self.pLevelUpPriceText:setText(levelup_price);
    
    if (tower:CheckLevelUp() == true) then
        self.tower_control_levelup:setPosition(x+offset,y);
        self.tower_control_levelup:setVisible(true);
        
        self.pLevelUpPriceText:setPosition(ccp(x+offset,y+80));
        self.pLevelUpPriceText:setVisible(true);
    end
    
    self.tower_control_sell:setPosition(x-offset,y);
    self.tower_control_sell:setVisible(true);
    
    self.pSellPriceText:setPosition(ccp(x-offset,y+80));
    self.pSellPriceText:setText(sell_price);
    self.pSellPriceText:setVisible(true);
end

function MapScene:RefreshTowerControl(tower)
    if (tower ~= nil) then
        local can_level_up = tower:CheckLevelUp();
        if (self.tower_control_levelup:isVisible() ~= can_level_up) then
            local x = self.maplogic:ColIndexToX(tower.col);
            local y = self.maplogic:RowIndexToY(tower.row);
            local range = 200;
            local offset = range/2;
            if (offset > 100) then
                offset = 100;
            end
            
            self.tower_control_levelup:setPosition(x+offset,y);
            self.tower_control_levelup:setVisible(can_level_up);
            
            self.pLevelUpPriceText:setPosition(ccp(x+offset,y+80));
            self.pLevelUpPriceText:setVisible(can_level_up);
        end
    end
end

function MapScene:RemoveTowerControl()
    cclog("MapScene:RemoveTowerControl");
    
    self.tower_range:setVisible(false);
    self.tower_control_levelup:setVisible(false);
    self.tower_control_sell:setVisible(false);
    self.pLevelUpPriceText:setVisible(false);
    self.pSellPriceText:setVisible(false);
end

function MapScene:ShowBlock()
    if self.show_block == true then
        return;
    end
    
    self.show_block = true;
    for i=0,self.maplogic.rows-1,1 do
		    for j=0,self.maplogic.cols-1,1 do
		        if (self.outside_sprite[i][j] ~= nil) then
		            if (self.maplogic.towers[i] == nil or self.maplogic.towers[i][j] == nil) then
    		            self.outside_sprite[i][j]:setVisible(true);
    		        else
    		            self.outside_sprite[i][j]:setVisible(false);
    		        end
    		    end
		    end
		end
end

function MapScene:HideBlock()
    if self.show_block == false then
        return;
    end
    
    self.show_block = false;
    self.inside_sprite:setVisible(false);
    self.tower_range:setVisible(false);
    for i=0,self.maplogic.rows-1,1 do
		    for j=0,self.maplogic.cols-1,1 do
		        if (self.outside_sprite[i][j] ~= nil) then
    		        self.outside_sprite[i][j]:setVisible(false);
    		    end
		    end
		end
end

function MapScene:RefreshControlSprite(x,y)
    --cclog("MapScene:RefreshControlSprite x="..x.." y="..y);
    
    if (self.maplogic:IsEnd()) then return end;
    
    if self.show_block == false then
        return;
    end
    
    self.tmp_tower:setPosition(x,y);
    
    local row = self.maplogic:YToRowIndex(y);
    local col = self.maplogic:XToColIndex(x);
    
    self.inside_sprite:setPosition(self.maplogic:ColIndexToX(col),self.maplogic:RowIndexToY(row));
    self.tower_range:setPosition(self.maplogic:ColIndexToX(col),self.maplogic:RowIndexToY(row));
    self.inside_sprite:setVisible(self.maplogic:CheckCanBuildTower(row, col));
    
    local towerconfig_table = GetTable("towerconfig");
    local sight_range = towerconfig_table:GetRecByColName(self.sel_tower_type, "sight_range1");
    self.tower_range:setScale(2*sight_range/200);
    self.tower_range:setVisible(self.maplogic:CheckCanBuildTower(row, col));
end

function MapScene:Heartbeat()
    --CalcCostMS2(0,"");
    BaseScene.instance.maplogic:Heartbeat();
    --CalcCostMS2(0,"MapScene:Heartbeat");
end