--洞口配置
local DiffX = 15
local DiffY = 19.5
local HoleCfg = {
      HolePosX = {-80+DiffX, 20+DiffX, 120+DiffX},
      HolePosY = {90-DiffY, -DiffY, -90-DiffY},
      Scale = 2.0,
}
local function GetHoleX(i)
   return HoleCfg["HolePosX"][i]*HoleCfg["Scale"]
end
local function GetHoleY(i)
   return HoleCfg["HolePosY"][i]*HoleCfg["Scale"]
end

GameScene = {
	scene,
	uilayer,
	layer,
	meadow,
	alive_arr,
	alive_cnt,
	actionRunner,
	--mole
	mole_sprite,
	mole_action_handle,
}
GameScene.alive_arr = {
  {0,0,0},
  {0,0,0},
  {0,0,0},
 } 

local Mole = {
	alive = false,
	be_hit = false,
}

function Mole:OnBorn(node)
	Mole.alive = true
	Mole.be_hit = false
end

function Mole:OnDeath(node)
	Mole.alive = false
	cclog("ondeath")
	GameScene.mole_sprite = nil
	GameScene.alive_cnt = GameScene.alive_cnt - 1
end

function GameScene:create()
		GameScene:Init()
		return GameScene.scene
end

function GameScene:Init()
    GameScene.scene = CCScene:create()
    GameScene.uilayer = UILayer:create()
	GameScene.layer = CCLayer:create()
    GameScene.uilayer:getScheduler():scheduleScriptFunc(GameScene.heartbeat,0.1,false)
    
    GameScene.meadow = CreateWidgetFromJsonFile(GET_PATH(g_resource_path["scenes"], "greenground/greenground.json"))
    GameScene.meadow:setName("meadow")
    local greenground_image_widget = UIHelper:instance():seekWidgetByName(GameScene.meadow, "greenground_image");
    greenground_image_widget:setPosition(GET_POS_CENTOR());
		GameScene.uilayer:addWidget(GameScene.meadow)
	    
	GameScene.scene:addChild(GameScene.uilayer)
	GameScene.scene:addChild(GameScene.layer)
    GameScene.alive_cnt = 0
	
    GameScene.actionRunner = aeditor.ActionTemplateTable:create(GET_PATH(g_resource_path["aeditor"],"template.xml"), GameScene.scene);
	
	local function onTouch(eventType , x , y)
			
			if eventType == "began" then
					if (nil ~= GameScene.mole_sprite and Mole.alive == true) then
							local mole_bb = GameScene.mole_sprite:boundingBox()
							if mole_bb:containsPoint(CCPoint(x,y)) then
									Mole.be_hit = true
									cclog("Hit!")
							end
					end
	    		return true
	    elseif eventType == "moved"  then
	    	cclog("move: ("..x..","..y..")")
	    	return true 
	    elseif eventType == "ended" then
	    	cclog("cctouchend")
	    end
	    return false
	end
	GameScene.layer:setTouchEnabled( true )
	GameScene.layer:registerScriptTouchHandler( onTouch ) --可以注册多点触摸
	
	--读取csv表的示范
	local test_table = GetTable("ctest");
	--1.用key查找
	local data = test_table:GetRecByColName(2, "hp");	--ctest.csv里没有2这个key
	if (nil ~= data) then
		cclog(data);
	end
	local data = test_table:GetRecByColName(3, "hp");
	if (nil ~= data) then
		cclog(data);
	end
	--2.遍历
	local count = test_table:Rows();
	cclog(count);
	for i=0,count-1,1 do
			local index = test_table:GetRecFromIndex(i,test_table:GetColIndex("index"));
			if (index ~= nil) then
					local country = test_table:GetRecByColName(index,"country");
			end
	end
	
end

function GameScene:heartbeat()
		
		local begincallback = CCCallFuncN:create(Mole.OnBorn)
		local finishcallback = CCCallFuncN:create(Mole.OnDeath)
	
		if Mole.be_hit then
				Mole.alive = false;
				Mole.be_hit = false;
				if (nil == GameScene.mole_sprite) then return end
				
				local datamgr = DataMgr:sharedMgr();
				local tag = GameScene.mole_sprite:getTag();
				local touchkey = STRING_WITH_INT("mole_can_touch",tag);
				
				local value = datamgr:GetString(touchkey);
				if (nil == value) then return end
				
				if ("0" == value) then return end
				
				local nposx = GameScene.mole_sprite:getPositionX();
				local nposy = GameScene.mole_sprite:getPositionY();
				if (GameScene.actionRunner:RemoveByHandle(GameScene.mole_action_handle)) then
						local sprite = CCSprite:create();
						local param = aeditor.AEParamAmmend:create();
						param:AddPos(1, ccp(nposx, nposy));
						param:AddSprite("hit",sprite);
						GameScene.mole_action_handle = GameScene.actionRunner:RunAeActionWithParam(GameScene.uilayer, GET_PATH(g_resource_path["aeditor"],"mole_hit.ae"),param,nil,finishcallback);
						GameScene.mole_sprite = sprite;
						GameScene.mole_sprite:setScale(HoleCfg["Scale"]);
				end
		end

    if(GameScene.alive_cnt ~= 0) then return end
    GameScene.alive_cnt = GameScene.alive_cnt+1
    local x = math.random(1,3)
    local y = math.random(1,3)
	
    GameScene.alive_arr[x][y] = 1

		local sprite = CCSprite:create();
		local param = aeditor.AEParamAmmend:create();
		local pos = GET_POS_CENTOR();
		param:AddPos(1, ccp(pos.x+GetHoleX(x),pos.y+GetHoleY(y)));
		param:AddSprite("normal",sprite);
		GameScene.mole_action_handle = GameScene.actionRunner:RunAeActionWithParam(GameScene.uilayer, GET_PATH(g_resource_path["aeditor"],"mole_normal.ae"),param,begincallback,finishcallback);
		--GameScene.mole_sprite = GameScene.actionRunner:GetSpriteByName(GameScene.uilayer, "normal");	--多个同名精灵的话这么搞不好
		GameScene.mole_sprite = sprite;
		GameScene.mole_sprite:setScale(HoleCfg["Scale"]);
	
		local tag = GameScene.mole_sprite:getTag();
		local touch = STRING_WITH_INT("mole_can_touch",tag);
		cclog(touch);
end