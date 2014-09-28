--Skill的表现(释放后的特效移动效果)
SkillPerform = class("SkillPerform");
SkillPerform.index = 0;

function SkillPerform:create(master,target,tid,params)
	  SkillPerform.index = SkillPerform.index + 1;
	  
    skill_perform = SkillPerform.new(SkillPerform.index,master,target,tid,params);
    
    master:OnAddSkillPerform(skill_perform);
    
    return skill_perform;
end

function SkillPerform:ctor(index,master,target,tid,params)
    self.index = index;
    self.tid = tid;
    self.master = master;
    self.target = target.index;	--target可能消失，索引保存索引
    
    self.move_time = 0.05;	--每0.05秒前进一下
    self.move_tick_count = 0;
    self.life_tick_count = 0;
    self.hit = false;
    self.isremove = false;
    
    local skillperformconfig_table = GetTable("skillperformconfig");

    self.rotate_with_monster = tonumber(skillperformconfig_table:GetRecByColName(self.tid, "rotate_with_monster"));
    self.move_with_monster = tonumber(skillperformconfig_table:GetRecByColName(self.tid, "move_with_monster"));
    self.life = tonumber(skillperformconfig_table:GetRecByColName(self.tid, "life"));
    self.speed = tonumber(skillperformconfig_table:GetRecByColName(self.tid, "speed"));
    self.attack = tonumber(skillperformconfig_table:GetRecByColName(self.tid, "attack"));
    self.effect = tonumber(skillperformconfig_table:GetRecByColName(self.tid, "effect"));
    
    self.x = master:GetPos().x;
    self.y = master:GetPos().y;
    self.tx = target:GetPos().x;
    self.ty = target:GetPos().y;
    
    local particle = skillperformconfig_table:GetRecByColName(self.tid, "particle");
    if (particle ~= nil and particle ~= "") then
        self.particle = CCParticleSystemQuad:create(GET_PATH(g_resource_path["effect"], GET_PATH2("particle/",particle)));
        self.particle:setScale(0.8);   --TODO
        self.particle:setPosition(self.x,self.y);
        BaseScene.instance.uilayer:addChild(self.particle);
    end
    
    local animation = skillperformconfig_table:GetRecByColName(self.tid, "animation");
    if (animation ~= nil and animation ~= "") then
        local sprite = CCSprite:create();
        sprite:setScale(0.5);   --TODO
        local param = aeditor.AEParamAmmend:create();
        local pos = GET_POS_CENTOR();
        param:AddPos(1, self:GetPos());
        param:AddSprite("arrow",sprite);
        
        self.sprite = sprite;
        self.handler = BaseScene.instance.actionRunner:RunAeActionWithParam(BaseScene.instance.uilayer, GET_PATH(g_resource_path["aeditor"],animation),param,nil,nil);
    end
    
end

function SkillPerform:remove()
    if (self.isremove == true) then return end
    self.isremove = true;
    
    if (self.particle ~= nil) then
        BaseScene.instance.uilayer:removeChild(self.particle,true);
    end
    if (self.handler ~= nil) then
        BaseScene.instance.actionRunner:RemoveByHandle(self.handler);
    end

    self.master:OnRemoveSkillPerform(self);
end

function SkillPerform:Heartbeat()
    self.move_tick_count = self.move_tick_count + 1;
    if (self.move_tick_count >= self.move_time/BaseScene.instance.maplogic.tick_time) then
        self.move_tick_count = 0;
        self:Move();
    end
end

function SkillPerform:Hit(target)
    cclog("SkillPerform:Hit");
    
    local die = target:OnAttack(self.attack);
    
    if (die == false) then
        if (self.effect ~= nil and self.effect ~= 0) then
            params = {};
            Effect:create(target,self.effect,params);
        end
    end
    
    return die;
end

function SkillPerform:GetPos()
    return ccp(self.x,self.y);
end

function SkillPerform:Move()
    local target = BaseScene.instance.maplogic.monsters[self.target];
    if (target ~= nil and self.move_with_monster == 1) then
        self.tx = target:GetPos().x;
        self.ty = target:GetPos().y;
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
		
		--cclog("SkillPerform:Move x="..self.x.." y="..self.y.." tx="..self.tx.." ty="..self.ty);
		
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
		    
		    self.life_tick_count = self.life_tick_count + 1;
        if (self.life_tick_count > self.life/BaseScene.instance.maplogic.tick_time) then
            --cclog("life count remove");
            self:remove();
        end
		end
end