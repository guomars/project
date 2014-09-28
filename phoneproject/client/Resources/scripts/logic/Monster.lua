--怪物
Monster = class("Monster",EffectActivatedObejct);

function Monster:create(index, type, line)
    cclog("Monster:create index="..index.." type="..type.." line="..line);
    
    --先获得怪物配置表
    local monsterconfig_table = GetTable("monsterconfig");
    
    --初始化怪物属性
    local max_hp = tonumber(monsterconfig_table:GetRecByColName(type, "hp"));
    local armor = tonumber(monsterconfig_table:GetRecByColName(type, "armor"));
    local begin_row = BaseScene.instance.maplogic.refresh_pos[line]["begin_row"];
		local begin_col = BaseScene.instance.maplogic.refresh_pos[line]["begin_col"];
		local begin_x = BaseScene.instance.maplogic:ColIndexToX(begin_col);
		local begin_y = BaseScene.instance.maplogic:RowIndexToY(begin_row);
    local sprite = CCSprite:create();
		local param = aeditor.AEParamAmmend:create();
		local pos = GET_POS_CENTOR();
		local ae_file = monsterconfig_table:GetRecByColName(type, "animation");
		param:AddPos(1, ccp(BaseScene.instance.maplogic:ColIndexToX(begin_col), BaseScene.instance.maplogic:RowIndexToY(begin_row)));
		param:AddSprite("monster",sprite);
		
		--创建怪物并赋值
		monster_params = {};
		monster = Monster.new(monster_params);
		monster.line = line;
		monster.type = type;
		monster.step = 1;
		monster.move_time = 0.05;
		monster.move_tick_count = 0;
		monster.x = BaseScene.instance.maplogic:ColIndexToX(begin_col);
		monster.y = BaseScene.instance.maplogic:RowIndexToY(begin_row);
		monster.handler = BaseScene.instance.actionRunner:RunAeActionWithParam(BaseScene.instance.uilayer_container, GET_PATH(g_resource_path["aeditor"],ae_file),param,nil,nil);
		monster.sprite = sprite;
		SET_NODE_ZORDER(monster.sprite, ZORDER_MONSTER);
		monster.speed = monsterconfig_table:GetRecByColName(type, "speed");  --这里填的是每秒前进的像素
		monster.play_speed = 1;
		monster.effects = {};
		monster.have_skills = string.split(monsterconfig_table:GetRecByColName(type, "skills"),";");
		
		cclog("monster skills size="..table.nums(monster.have_skills));
    
    params = {};
    for k,skill_id in pairs(monster.have_skills) do
        if skill_id ~= nil and tonumber(skill_id) ~= 0 then
            Skill:create(monster,skill_id,params);
        end
    end
		
		monster:SetMaxHP(max_hp);
		monster:SetArmor(armor);
		
		--调用地图的回调函数对怪物进行添加
		BaseScene.instance.maplogic:OnCreateMonster(monster, index);
end

function Monster:remove(escaped)
    --删除掉精灵就行了
    BaseScene.instance.actionRunner:RemoveByHandle(self.handler);
    
    --把身上所有特效先都删了
    self:RemoveAllEffects();
    
    --调用地图的回调函数进行计数统计
    BaseScene.instance.maplogic:OnRemoveMonster(self,escaped);
end

function Monster:Heartbeat()
	
	  Monster.super.Heartbeat(self);
	
    self.move_tick_count = self.move_tick_count + 1;
    if (self.move_tick_count >= self.move_time/BaseScene.instance.maplogic.tick_time) then
        self.move_tick_count = 0;
        self:Move();
    end
    
    local speed_action = tolua.cast(self.sprite:getActionByTag(999999), "CCSpeed");
    if (speed_action ~= nil) then
		    speed_action:setSpeed(self.play_speed);
		end
end

function Monster:GetPos()
	  return ccp(self.sprite:getPositionX(),self.sprite:getPositionY());
end

function Monster:ChangeSpeed(change_speed)
    cclog("Monster:ChangeSpeed speed="..self.speed.." change_speed="..change_speed);
    
    self.speed = self.speed * change_speed;
    self.play_speed = self.play_speed * change_speed;
    
    cclog("Monster:ChangeSpeed speed="..self.speed);
    
    local speed_action = tolua.cast(self.sprite:getActionByTag(999999), "CCSpeed");
    if (speed_action ~= nil) then
		    speed_action:setSpeed(self.play_speed);
		end
end

function Monster:Jump(grid_num)
    cclog("Monster:Jump grid_num="..grid_num);
end

function Monster:Move()
    local next_row = BaseScene.instance.maplogic:GetStepRow(self.line, self.step+1);
		local next_col = BaseScene.instance.maplogic:GetStepCol(self.line, self.step+1);
		--cclog("Move next_row="..next_row.." next_col="..next_col);
		if (next_row == nil or next_col == nil) then
				self:remove(true);
				return;
		end
		
		local next_x = BaseScene.instance.maplogic:ColIndexToX(next_col);
		local next_y =  BaseScene.instance.maplogic:RowIndexToY(next_row);
		
		local pos1 = ccp(next_x-self.x, next_y-self.y);
		local pos2 = ccp(0,1);
		local angle_radian = GET_CCP_ANGLE(pos1,pos2);
		local angle_degree = RADIANS_TO_DEGREES(angle_radian);
		
		if (self.x ~= next_x) then
				if (self.x < next_x) then
						self.x = self.x + self.speed*self.move_time*math.abs(math.sin(angle_radian));
						if (self.x > next_x) then
								self.x = next_x;
						end
				else
				    self.x = self.x - self.speed*self.move_time*math.abs(math.sin(angle_radian));
				    if (self.x < next_x) then
				        self.x = next_x;
				    end
				end
		end
		if (self.y ~= next_y) then
		    if (self.y < next_y) then
						self.y = self.y + self.speed*self.move_time*math.abs(math.cos(angle_radian));
						if (self.y > next_y) then
								self.y = next_y;
						end
				else
				    self.y = self.y - self.speed*self.move_time*math.abs(math.cos(angle_radian));
				    if (self.y < next_y) then
				        self.y = next_y;
				    end
				end
    end
		if (self.x == next_x and self.y == next_y) then
		    self.step = self.step + 1;
		    self:Move();    --这里再调用一次是为了防止下次才走会出现卡顿
		    return;
		end
		
		self.sprite:setPosition(self.x, self.y);
end

function Monster:Die()
    cclog("Monster:Die");
    self:remove(false);
end

function Monster:CheckTarget()
	  --TODO 需要把附加箭塔加进目标么
end