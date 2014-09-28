--箭塔
Tower = class("Tower",EffectActivatedObejct);

function Tower:create(row, col, type)
    cclog("Tower:create row="..row.." col="..col.." type="..type);
    
    --先获得箭塔配置表
    local towerconfig_table = GetTable("towerconfig");
    
    --初始化图片路径
    local pngfile = towerconfig_table:GetRecByColName(type, "picture1");
    
    --创建箭塔对象
    tower_params = {};
    tower = Tower.new(tower_params);
    tower.type = type;
    tower.level = 1;
    tower.row = row;
    tower.col = col;
    tower.sight_range = tonumber(towerconfig_table:GetRecByColName(type, "sight_range1"));
    tower.have_skills = string.split(towerconfig_table:GetRecByColName(type, "skills1"),";");
    tower.sprite = CCSprite:create(GET_PATH(g_resource_path["towers"], pngfile));
    tower.sprite:setScale(1.5);
    tower.sprite:setPosition(BaseScene.instance.maplogic:ColIndexToX(col), BaseScene.instance.maplogic:RowIndexToY(row));
    BaseScene.instance.uilayer_container:addChild(tower.sprite);
    SET_NODE_ZORDER(tower.sprite, ZORDER_TOWER);
    
    cclog("skills size="..table.nums(tower.have_skills));
    
    params = {};
    for k,skill_id in pairs(tower.have_skills) do
        if skill_id ~= nil and tonumber(skill_id) ~= 0 then
            Skill:create(tower,skill_id,params);
        end
    end
    
    BaseScene.instance.maplogic:OnCreateTower(tower, row, col);
end

function Tower:remove()
    Tower.super.remove(self);
    
    --删除掉精灵就行了
    BaseScene.instance.uilayer_container:removeChild(self.sprite,true);
    
    BaseScene.instance.maplogic:OnRemoveTower(self,self.type,self.row,self.col);
end

function Tower:pointAtSelfBody(pos)
    return POINT_INT_NODE(self.sprite,pos);
end

function Tower:GetPos()
    return ccp(self.sprite:getPositionX(),self.sprite:getPositionY());
end

function Tower:CheckTarget()
    --CalcCostMS2(1,"");
    for key, mon in pairs(BaseScene.instance.maplogic.monsters) do
        if mon ~= nil then
    		    local pos1 = mon:GetPos();
    		    local pos2 = self:GetPos();
    		    local dis = GET_CCP_DISTANCE(pos1,pos2);
    		    if (dis < self.sight_range and table.hasValue(self.targets,key) == false) then
    		        self.targets[#self.targets+1] = key;
    		    end
    		end
    end
    
    if (table.nums(self.targets) ~= 0) then
        local remove_map = {};
        local i = 0;
        for key, target_key in pairs(self.targets) do
            --cclog("check key="..key.." target="..target_key);
            i = i + 1;
            local mon = BaseScene.instance.maplogic.monsters[target_key];
            if (mon == nil) then
                remove_map[#remove_map+1] = i;
            else
		            local pos1 = mon:GetPos();
		            local pos2 = self:GetPos();
		            local dis = GET_CCP_DISTANCE(pos1,pos2);
                --cclog("target="..target_key.." dis="..dis.." range="..self.attack_range);
                if (dis > self.sight_range) then
                    remove_map[#remove_map+1] = i;
                end
            end
        end
        
        if (table.nums(remove_map) ~= 0) then
            for k, v in pairs(remove_map) do
                table.remove(self.targets,v);
                --cclog("remove key="..v.." size="..table.nums(self.targets));
            end
        end
    end
    --CalcCostMS2(1,"Tower:CheckTarget");
end

function Tower:CheckLevelUp()
    local towerconfig_table = GetTable("towerconfig");
    local cost = tonumber(towerconfig_table:GetRecByColName(self.type, STRING_WITH_INT("lvup_cost",self.level)));
    if (cost <= 0 or cost > BaseScene.instance.maplogic.money) then
        return false;
    end
    
    --TODO 需要再判断一下该等级是否已经激活
    
    return true;
end

function Tower:LevelUp()
    if (self:CheckLevelUp() == false) then return end
    
    local tolevel = self.level + 1;
    local towerconfig_table = GetTable("towerconfig");
    local pngfile = towerconfig_table:GetRecByColName(self.type, STRING_WITH_INT("picture",tolevel));
    local cost = tonumber(towerconfig_table:GetRecByColName(self.type, STRING_WITH_INT("lvup_cost",self.level)));
    
    self.level = tolevel;
    self.sight_range = tonumber(towerconfig_table:GetRecByColName(self.type, STRING_WITH_INT("sight_range",tolevel)));
    SET_SPRITE_TEXTURE(self.sprite,GET_PATH(g_resource_path["towers"], pngfile));
    
    for k,skill_id in pairs(self.have_skills) do
        if skill_id ~= nil then
            self:RemoveSkill(skill_id);
        end
    end
    
    self.have_skills = string.split(towerconfig_table:GetRecByColName(self.type, STRING_WITH_INT("skills",tolevel)),";");
    params = {};
    for k,skill_id in pairs(self.have_skills) do
        if skill_id ~= nil then
            Skill:create(self,skill_id,params);
        end
    end
    
    BaseScene.instance.maplogic:OnTowerLevelUp(self, cost);
end

function Tower:Sell()
    local towerconfig_table = GetTable("towerconfig");
    local sell_price = tonumber(towerconfig_table:GetRecByColName(self.type, STRING_WITH_INT("sell_price",self.level)));
    
    BaseScene.instance.maplogic:OnTowerSell(self, sell_price);
    
    self:remove();
end

function Tower:OnBtnControlPush()
    cclog("Tower:OnBtnControlPush");
    
    local towerconfig_table = GetTable("towerconfig");
    local sell_price = towerconfig_table:GetRecByColName(self.type, STRING_WITH_INT("sell_price",self.level));
    local levelup_price = towerconfig_table:GetRecByColName(self.type, STRING_WITH_INT("lvup_cost",self.level));
    
    BaseScene.instance:AddTowerControl(self,sell_price,levelup_price);
end

function Tower:OnBtnControlRelease()
    cclog("Tower:OnBtnControlRelease");
    
    BaseScene.instance:RemoveTowerControl();
end