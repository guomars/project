--箭矢
Arrow = class("Arrow");

function Arrow:create(index, target, pos, target_pos, type)
    
    --TODO CCParticleBatchNode
    
    --先获得箭矢配置表
    local arrowconfig_table = GetTable("arrowconfig");
    
    local particlefile = arrowconfig_table:GetRecByColName(type, "particle");
    local animationfile = arrowconfig_table:GetRecByColName(type, "animation");
    local pos1 = ccp(target_pos.x-pos.x, target_pos.y-pos.y);
		local pos2 = ccp(0,1);
    
    arrow = Arrow.new();
    arrow.index = index;
    arrow.target = target;
    arrow.hit = false;
    arrow.isremove = false;
    arrow.life_count = 0;
    arrow.move_time = 0.05;
    arrow.move_tick_count = 0;
    arrow.x = pos.x;
    arrow.y = pos.y;
    arrow.tx = target_pos.x;
    arrow.ty = target_pos.y;
    arrow.init_angle_radian = GET_CCP_ANGLE(pos1,pos2);
		arrow.init_angle_degree = RADIANS_TO_DEGREES(arrow.init_angle_radian);
    arrow.move_with_monster = tonumber(arrowconfig_table:GetRecByColName(type, "move_with_monster"));
    arrow.rotate_with_monster = tonumber(arrowconfig_table:GetRecByColName(type, "rotate_with_monster"));
    arrow.life = tonumber(arrowconfig_table:GetRecByColName(type, "life"));
    arrow.effect = tonumber(arrowconfig_table:GetRecByColName(type, "effect"));
    arrow.speed = tonumber(arrowconfig_table:GetRecByColName(type, "speed"));
    arrow.attack = tonumber(arrowconfig_table:GetRecByColName(type, "attack"));
    
    if (particlefile ~= "" and particlefile ~= nil) then
        cclog("particlefile = "..particlefile);
        arrow.particle = CCParticleSystemQuad:create(GET_PATH(g_resource_path["effect"], GET_PATH2("particle/",particlefile)));
		    arrow.particle:setScale(0.8);   --TODO
		    arrow.particle:setPosition(arrow.x,arrow.y);
		    MapScene.uilayer:addChild(arrow.particle);
		    if (arrow.rotate_with_monster == 1) then
		        arrow.particle:setRotation(arrow.init_angle_degree);
		    end
		end
		
		if (animationfile ~= "" and animationfile ~= nil) then
		    cclog("animationfile = "..animationfile);
		    local sprite = CCSprite:create();
		    sprite:setScale(0.5);   --TODO
		    local param = aeditor.AEParamAmmend:create();
		    local pos = GET_POS_CENTOR();
		    param:AddPos(1, arrow:GetPos());
		    param:AddSprite("arrow",sprite);
		    arrow.sprite = sprite;
		    arrow.handler = MapScene.actionRunner:RunAeActionWithParam(MapScene.uilayer, GET_PATH(g_resource_path["aeditor"],animationfile),param,nil,nil);
		    if (arrow.rotate_with_monster == 1) then
		        arrow.sprite:setRotation(arrow.init_angle_degree);
		    end
		end
		
		MapScene.maplogic:OnCreateArrow(arrow,index);
end

function Arrow:remove()
    --cclog("remove");
    if (self.isremove == true) then return end
    self.isremove = true;
    --删除掉精灵就行了
    if (self.particle ~= nil) then
        MapScene.uilayer:removeChild(self.particle,true);
    end
    if (self.handler ~= nil) then
        MapScene.actionRunner:RemoveByHandle(self.handler);
    end
    
    MapScene.maplogic:OnRemoveArrow(self);
end

function Arrow:Heartbeat()
    --cclog("Arrow:Heartbeat index="..self.index);
    self.move_tick_count = self.move_tick_count + 1;
    if (self.move_tick_count >= self.move_time/MapScene.maplogic.tick_time) then
        self.move_tick_count = 0;
        self:Move();
    end
end

function Arrow:Move()
    local target = MapScene.maplogic.monsters[self.target];
    if (target ~= nil and self.move_with_monster == 1) then
        self.tx = target.sprite:getPositionX();
        self.ty = target.sprite:getPositionY();
    end
    
    local pos1 = ccp(self.tx-self.x, self.ty-self.y);
		local pos2 = ccp(0,1);
		local angle_radian = GET_CCP_ANGLE(pos1,pos2);
		local angle_degree = RADIANS_TO_DEGREES(angle_radian);
    
    if (self.x ~= self.tx) then
				if (self.x < self.tx) then
				    self.x = self.x + self.speed*self.move_time*math.abs(math.sin(angle_radian));
				    --self.x = self.x + self.speed*self.move_time;
				    if (self.x > self.tx) then
				        self.x = self.tx;
				    end
				elseif self.x > self.tx then
				    self.x = self.x - self.speed*self.move_time*math.abs(math.sin(angle_radian));
				    --self.x = self.x - self.speed*self.move_time;
				    if (self.x < self.tx) then
				        self.x = self.tx;
				    end
				end
		end
		if (self.y ~= self.ty) then
        if (self.y < self.ty) then
            self.y = self.y + self.speed*self.move_time*math.abs(math.cos(angle_radian));
            --self.y = self.y + self.speed*self.move_time;
				    if (self.y > self.ty) then
				        self.y = self.ty;
				    end
				elseif self.y > self.ty then
				    self.y = self.y - self.speed*self.move_time*math.abs(math.cos(angle_radian));
				    --self.y = self.y - self.speed*self.move_time;
				    if (self.y < self.ty) then
				        self.y = self.ty;
				    end
				end
		end
		if (self.x == self.tx and self.y == self.ty and self.hit == false) then
		    self.hit = true;
		end
		
		if (self.particle ~= nil) then
		    self.particle:setPosition(self.x, self.y);
		    if (self.rotate_with_monster == 1 and self.hit == false) then
		        self.particle:setRotation(angle_degree);
		    end
		end
		
		if (self.sprite ~= nil) then
		    self.sprite:setPosition(self.x, self.y);
		    if (self.rotate_with_monster == 1 and self.hit == false) then
		        self.sprite:setRotation(angle_degree);
		    end
		end
		
		if (self.hit == true) then
		    --cclog("hit");
		    if (target ~= nil) then
		        if self:Hit(target) == true then
		            self:remove();
		        end
		    end
		    
		    self.life_count = self.life_count + 1;
        if (self.life_count > self.life/MapScene.maplogic.tick_time) then
            --cclog("life count remove");
            self:remove();
        end
		end
end

function Arrow:Hit(target)
    return target:Hurt(self.attack);
end

function Arrow:GetPos()
    return ccp(self.x,self.y);
end