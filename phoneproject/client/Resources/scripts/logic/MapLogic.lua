--地图逻辑管理
MapLogic = class("MapLogic");

function MapLogic:create(mapscene, map_index)
    cclog("MapLogic:create");
    maplogic = MapLogic.new();
    maplogic.mapscene = mapscene;
    maplogic.map_index = map_index;
    
    maplogic:init();
    
    return maplogic;
end

function MapLogic:init()
    cclog("MapLogic:init");
    CalcCostMS("");
    
    math.randomseed(os.time());
    
    --每个心跳的时间间隔(秒)
    maplogic.tick_time = 0.05;
    
    local mapmgr = GMapMgr:GetInstance();
    
    --先从csv里读取地图的通过信息
    local mapconfig_table = GetTable("mapconfig");
    
    local map_csv_file = mapconfig_table:GetRecByColName(self.map_index, "csvfile");
    local map_table = GetTable(map_csv_file);
    self.rows = map_table:Rows();
    self.cols = map_table:Columns()-1;  --第一列是索引，不是地形
    mapmgr:SetMaxSize(self.rows,self.cols);
		cclog("rows="..self.rows.." cols="..self.cols);
		for i=0,self.rows-1,1 do
				local index = map_table:GetRecFromIndex(i,map_table:GetColIndex("index"));
				if (index ~= nil) then
						for j=0,self.cols-1,1 do
							local col_name = STRING_WITH_INT("col",j+1);
							local grid = map_table:GetRecByColName(index,col_name);
							mapmgr:SetMapGrid(i,j,grid);
							--cclog("i="..i.." j="..j.." grid="..grid);
						end
				end
		end
		
		--再从csv里读取地图的开始点和结束点
		self.row_size = mapconfig_table:GetRecByColName(self.map_index, "row_size");
    self.col_size = mapconfig_table:GetRecByColName(self.map_index, "col_size");
		self.refresh_pos_num = mapconfig_table:GetRecByColName(self.map_index, "refresh_pos_num");
		self.refresh_pos = {};
		self.start = {};
		for i=1,self.refresh_pos_num,1 do
		    self.refresh_pos[i] = {};
		    self.refresh_pos[i]["begin_row"] = mapconfig_table:GetRecByColName(self.map_index, STRING_WITH_INT("begin_row",i));
		    self.refresh_pos[i]["begin_col"] = mapconfig_table:GetRecByColName(self.map_index, STRING_WITH_INT("begin_col",i));
		    self.refresh_pos[i]["end_row"] = mapconfig_table:GetRecByColName(self.map_index, STRING_WITH_INT("end_row",i));
		    self.refresh_pos[i]["end_col"] = mapconfig_table:GetRecByColName(self.map_index, STRING_WITH_INT("end_col",i));
    		
    		cclog("i="..i.." begin_row="..self.refresh_pos[i]["begin_row"].." begin_col="..self.refresh_pos[i]["begin_col"].." end_row="..self.refresh_pos[i]["end_row"].." end_col="..self.refresh_pos[i]["end_col"]);
    		
    		--用A*算法计算寻路
    		local start = mapmgr:AStarStart(self.refresh_pos[i]["begin_col"],self.refresh_pos[i]["begin_row"],self.refresh_pos[i]["end_col"],self.refresh_pos[i]["end_row"]);
    		
    		--把路径保存起来
    		self.start[i] = {};
    		local pNow = start;
    		local j = 1;
    		while pNow~= nil do
    				cclog("pNow x="..pNow:GetX().." y="..pNow:GetY());
    				self.start[i][j] = {};
    				self.start[i][j]["col"] = pNow:GetX();
    				self.start[i][j]["row"] = pNow:GetY();
    				
    				j = j + 1;
    				pNow = pNow:GetNext();
    		end
    		
    		start:Release();
		end
		
		--初始银币
		self.money = tonumber(mapconfig_table:GetRecByColName(self.map_index, "init_money"));
		
		--初始化怪物列表的数组和创建计数
		self.monster_index = 0;
		self.monster_count = 0;
		self.monster_escaped = 0;
		self.max_monster_num = 20;
		self.monster_gen_tick = 0;
		self.monsters = {};
		
		--初始化箭塔的talbe
		self.towers = {};
		
		--状态(0未开始 1-998 第*波 999结束)
		self.state = 0;
		self.end_tick = 0;
		
		--显示箭塔升级界面的箭塔
		self.in_control_tower = nil;
		
		--关于第几波的一些数据
		self.wave_end = true;
		self.wave_end_tick = 0;
		self.wave_type = 0;
		self.wave_count = 0;
		self.wave_monster_num = 0;
		self.wave_line = nil;
		self.total_wave = tonumber(mapconfig_table:GetRecByColName(self.map_index, "total_wave"));
		
		CalcCostMS("MapLogic:init");
end

function MapLogic:Heartbeat()
    --CalcCostMS("");
    --刷新一下文字信息
		self:RefreshText();
		--CalcCostMS("MapLogic:Heartbeat text");
		
		--延迟一会结束
    if (self:IsEnd()) then
        self.end_tick = self.end_tick + 1;
        if (self.end_tick == toint(2/self.tick_time)) then
            self:OnMapEnd();
        end
        return;
    end
    --CalcCostMS("MapLogic:Heartbeat end_tick");
    
    --对所有的箭塔进行心跳函数
		for i=0,self.rows-1,1 do
		    if (self.towers[i] ~= nil) then
		        for j=0,self.cols-1,1 do
		            if (self.towers[i][j] ~= nil) then
    		            self.towers[i][j]:Heartbeat();
    		        end
		        end
		    end
		end
		--CalcCostMS("MapLogic:Heartbeat towers");
    
    --对所有的怪物进行心跳函数
		for key, mon in pairs(self.monsters) do
		    if mon ~= nil then
		        mon:Heartbeat();
		    end
		end
		--CalcCostMS("MapLogic:Heartbeat monsters");

    if (self.wave_end == true) then
        local mapconfig_table = GetTable("mapconfig");
        local begin_time = mapconfig_table:GetRecByColName(self.map_index, STRING_WITH_INT("begin_time",self.state+1));
        
        self.wave_end_tick = self.wave_end_tick + 1;
        if (self.wave_end_tick >= begin_time/self.tick_time) then
            self.state = self.state + 1;
            self.monster_index = 0;
            self.wave_end_tick = 0;
            self.wave_end = false;
            self.wave_type = tonumber(mapconfig_table:GetRecByColName(self.map_index, STRING_WITH_INT("refresh_type",self.state)));
            self.wave_monster_num = tonumber(mapconfig_table:GetRecByColName(self.map_index, STRING_WITH_INT("refresh_num",self.state)));
            self.wave_line = string.split(mapconfig_table:GetRecByColName(self.map_index, STRING_WITH_INT("refresh_pos",self.state)),";");
        end
    else
        --看看是否需要创建新的怪物
        self.monster_gen_tick = self.monster_gen_tick + 1;
        if self.monster_gen_tick >= 1/self.tick_time and self.wave_count < self.wave_monster_num then
            self.monster_gen_tick = 0;
            self.wave_count = self.wave_count + 1;
            for k , v in pairs(self.wave_line) do
                if v ~= nil then
                    self:CreateMonster(self.wave_type,tonumber(v));
                end
            end
        end
    end
    --CalcCostMS("MapLogic:Heartbeat monster_gen_tick");
end

function MapLogic:IsEnd()
    if (self.state == 999) then
        return true;
    end
    
    return false;
end

function MapLogic:SetEnd(succeed)
    self.succeed = succeed;
    self.state = 999;
    
    self.mapscene:HideBlock();
    self.mapscene:RemoveTmpTower();
    self.mapscene.tower_range:setVisible(false);
    self.mapscene:RemoveTowerControl();
    
    self.mapscene.inside_sprite:setVisible(false);
    for i=0,self.rows-1,1 do
		    for j=0,self.cols-1,1 do
		        if (self.mapscene.outside_sprite[i][j] ~= nil) then
    		        self.mapscene.outside_sprite[i][j]:setVisible(false);
    		    end
		    end
		end
end

function MapLogic:RowIndexToY(index)
		return tonumber(768 - (toint(index)+0.5)*self.col_size);
end

function MapLogic:ColIndexToX(index)
		return tonumber(100+(toint(index)+0.5)*self.row_size);
end

function MapLogic:YToRowIndex(y)
    return tonumber(toint((768-y-0.5*self.col_size)/self.col_size));
end

function MapLogic:XToColIndex(x)
    return tonumber(toint((x-100-0.5*self.row_size)/self.row_size));
end

function MapLogic:CheckCanBuildTower(row, col)
    if (self.mapscene.outside_sprite[row][col] ~= nil) then
        if (self.towers[row] == nil or self.towers[row][col] == nil) then
            return true;
        else
            return false;
        end
    end
    
    return false;
end

function MapLogic:CheckTowerActivated(tower_type)
    local datamgr = DataMgr:sharedMgr();
    if (tower_type ~= 1 and datamgr:GetInt(STRING_WITH_INT("MapScene_tower",tower_type),true) ~= 1) then
        return false;
    end
    
    local towerconfig_table = GetTable("towerconfig");
    local money_cost = tonumber(towerconfig_table:GetRecByColName(tower_type, "build_cost"));
    if (self.money < money_cost) then
        return false;
    end
    
    return true;
end

function MapLogic:GetStepRow(line,step)
    if (self.start[line] == nil) then return nil end
    if (self.start[line][step] == nil) then return nil end
    
    return self.start[line][step]["row"];
end

function MapLogic:GetStepCol(line,step)
    if (self.start[line] == nil) then return nil end
    if (self.start[line][step] == nil) then return nil end
    
    return self.start[line][step]["col"];
end

function MapLogic:RefreshText()
    local tmpstr = STRING_WITH_INT("money:",self.money);
    local tmpstr2 = STRING_WITH_INT2(" escapted:",self.monster_escaped);
    self.mapscene.pText:setText(GET_PATH(tmpstr,tmpstr2));
end

function MapLogic:CreateMonster(type, line)
    self.monster_index = self.monster_index + 1;
    Monster:create(self.monster_index, type, line);
end

function MapLogic:CreateTower(row, col, type)
    Tower:create(row, col, type);
end

--以下是地图逻辑的一些回调函数
function MapLogic:OnCreateMonster(monster, index)
    monster.index = index;
    self.monsters[index] = monster;
    
    self.monster_count = self.monster_count + 1;
    
    cclog("OnCreateMonster count="..self.monster_count.." escaped="..self.monster_escaped);
end

function MapLogic:OnCreateTower(tower, row, col)
    if (self.towers[row] == nil) then
        self.towers[row] = {};
    end
    
    self.towers[row][col] = tower;
    
    local towerconfig_table = GetTable("towerconfig");
    local money_cost = tonumber(towerconfig_table:GetRecByColName(tower.type, "build_cost"));
    
    self.money = self.money - money_cost;
    if (self.money < 0) then
        self.moeny = 0;
    end
end

function MapLogic:OnRemoveMonster(monster, escaped)
    if escaped == true then
        self.monster_escaped = self.monster_escaped + 1;
    else
        local monsterconfig_table = GetTable("monsterconfig");
        local prize = tonumber(monsterconfig_table:GetRecByColName(monster.type, "prize"));
        self.money = self.money + prize;
        
        self.mapscene:RefreshTowerControl(self.in_control_tower);
    end
    
    self.monster_count = self.monster_count - 1;
    self.monsters[monster.index] = nil;
    
    cclog("OnRemoveMonster count="..self.monster_count.." escaped="..self.monster_escaped);
    
    if self.monster_escaped >= 20 then
        self:SetEnd(false);
    elseif (self.monster_count <= 0) then
        if (self.state >= self.total_wave) then
            self:SetEnd(true);
        else
            self.wave_end = true;
            self.wave_end_tick = 0;
            self.wave_count = 0;
            self.monster_gen_tick = 0;
        end
    end
end

function MapLogic:OnRemoveTower(tower,type,row,col)
    self.towers[row][col] = nil;
end

function MapLogic:OnMapEnd()
    cclog("OnMapEnd");
    
    self.mapscene.pImageInfo:setVisible(false);
    --self.mapscene.pImageControl:setVisible(false);
    self.mapscene.pBtnMenu:setVisible(false);
    self.mapscene.pBtnContinue:setVisible(false);
    --self.mapscene.pBtnSet:setVisible(false);
    self.mapscene.pFinal:setVisible(true);
    
    if (self.succeed == true) then
        self.mapscene.pSuccess:setVisible(true);
        
        local datamgr = DataMgr:sharedMgr();
        
        local next_map_index = self.map_index+1;
        
        local technology = datamgr:GetInt("technology",true);
        local goldcoin = datamgr:GetInt("goldcoin",true);
        
        local next_map_activated = datamgr:GetInt(STRING_WITH_INT("activated_map",next_map_index),true);
        
        --TODO 需要计算一下每关发多少奖励
        
        if (next_map_activated == 0) then
            datamgr:SetInt(STRING_WITH_INT("activated_map",next_map_index),1,true);
            datamgr:SetInt("technology",technology+10,true);
        end
        datamgr:SetInt("goldcoin",goldcoin+100,true);
        
		    datamgr:SaveToFile();
        
        if (next_map_activated == 0) then
            local tmpstr = STRING_WITH_INT("get technology:",10);
            self.mapscene.pFinalInfo1:setText(tmpstr);
            self.mapscene.pFinalInfo1:setVisible(true);
        end
        
        local tmpstr2 = STRING_WITH_INT2("get goldcoin:",100);
        self.mapscene.pFinalInfo2:setText(tmpstr2);
        self.mapscene.pFinalInfo2:setVisible(true);
    else
        self.mapscene.pFail:setVisible(true);
        
        self.mapscene.pFinalInfo1:setVisible(false);
        self.mapscene.pFinalInfo2:setVisible(false);
    end
		
		for i=0,self.rows-1,1 do
		    if (self.towers[i] ~= nil) then
		        for j=0,self.cols-1,1 do
		            if (self.towers[i][j] ~= nil) then
    		            self.towers[i][j]:remove(false);
    		        end
		        end
		    end
		end
		
		for key, mon in pairs(self.monsters) do
		    if mon ~= nil then
		        mon:remove();
		    end
		end
end

function MapLogic:OnTowerLevelUp(tower, cost)
    cclog("MapLogic:OnTowerLevelUp money="..self.money.." cost="..cost);
    
    self.money = self.money - cost;
    if (self.money < 0) then
        self.money = 0;
    end
end

function MapLogic:OnTowerSell(tower, price)
    cclog("MapLogic:OnTowerSell money="..self.money.." price="..price);
    
    self.money = self.money + price;
end

--界面触摸的回调
function MapLogic:OnBtnControlPush(pos)
    for i=0,self.rows-1,1 do
		    if (self.towers[i] ~= nil) then
		        for j=0,self.cols-1,1 do
		            if (self.towers[i][j] ~= nil) then
    		            if self.towers[i][j]:pointAtSelfBody(pos) == true then
    		                self.towers[i][j]:OnBtnControlPush();
    		                self.in_control_tower = self.towers[i][j];
    		            end
    		        end
		        end
		    end
		end
end

function MapLogic:OnBtnControlRelease(pos)
    if (self.in_control_tower ~= nil) then
        if (self.mapscene.tower_control_levelup:isVisible() and POINT_INT_NODE(self.mapscene.tower_control_levelup,pos) == true) then
            self.in_control_tower:LevelUp();
        elseif (self.mapscene.tower_control_sell:isVisible() and POINT_INT_NODE(self.mapscene.tower_control_sell,pos) == true) then
            self.in_control_tower:Sell();
        end
        self.in_control_tower:OnBtnControlRelease();
        self.in_control_tower = nil;
    end
end

function MapLogic:OnBtnControlMove(obj,x,y)
end