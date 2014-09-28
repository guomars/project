--保存了所有技能的实例
All_Skills = {};

--技能载体的基类
SkillActivatedObejct = class("SkillActivatedObejct");

function SkillActivatedObejct:ctor(params)
    cclog("SkillActivatedObejct:ctor");
    
    self.check_target_tick_count = 0;
    self.targets = {};
    self.skills = {};
    self.skill_performs = {};
    self.hp = 100;
    self.max_hp = 100;
    self.armor = 0;
end

function SkillActivatedObejct:remove()
    cclog("SkillActivatedObejct:remove");
    
    self:RemoveAllPerforms();
end

function SkillActivatedObejct:RemoveAllPerforms()
    cclog("SkillActivatedObejct:RemoveAllPerforms size="..#self.skill_performs);
    
    local num = #self.skill_performs;
    for i=1,num,1 do
        self.skill_performs[1]:remove();   --每次删除完了都往前移动，所以一直是删除第一个就行
    end
end

function SkillActivatedObejct:RemoveSkill(skill_id)
    cclog("SkillActivatedObejct:RemoveSkill id="..skill_id);
    for key, skill in pairs(self.skills) do
        if (skill ~= nil and skill.tid == skill_id) then
            skill:remove();
            break;
        end
    end
end

function SkillActivatedObejct:SetArmor(armor)
    if (armor <= 0) then return end;
    
    self.armor = armor;
end

function SkillActivatedObejct:AddArmor(value)
    if (value <= 0) then return end;
    
    self.armor = self.armor + value;
end

function SkillActivatedObejct:ReduceArmor(value)
    if (value <= 0) then return end;
    
    self.armor = self.armor - value;
end

function SkillActivatedObejct:OnAttack(attack)
    local value = attack - self.armor;
    if (value <= 0) then
        value = 1;
    end
    
    return self:Hurt(value);
end

function SkillActivatedObejct:SetMaxHP(value)
    if (value <= 0) then return end;
    
    self.max_hp = value;
    if (self.hp > self.max_hp) then
        self.hp = self.max_hp;
    end
end

function SkillActivatedObejct:AddHP(value)
    if (value <= 0) then return end;
    
    self.hp = self.hp + value;
    if (self.hp > self.max_hp) then
        self.hp = self.max_hp;
    end
end

function SkillActivatedObejct:Hurt(value)
    if (value <= 0) then return false end;
    
    self.hp = self.hp - value;
    if (self.hp <= 0) then
        self.hp = 0;
        self:Die();
        return true;
    end
    return false;
end

function SkillActivatedObejct:Die()
    cclog("SkillActivatedObejct:Die");
end

function SkillActivatedObejct:OnAddSkill(skill)
    cclog("SkillActivatedObejct:OnAddSkill index="..skill.index);
    
    self.skills[#self.skills+1] = skill;
    skill:OnAddSkill();
end

function SkillActivatedObejct:OnRemoveSkill(skill)
    cclog("SkillActivatedObejct:OnRemoveSkill index="..skill.index);
    
    local remove_map = {};
    local i = 0;
    for key, s in pairs(self.skills) do
        i = i + 1;
        if (skill == s) then
            remove_map[#remove_map+1] = i;
            break;
        end
    end
    
    if (table.nums(remove_map) ~= 0) then
        for k, v in pairs(remove_map) do
            table.remove(self.skills,v);
        end
    end
end

function SkillActivatedObejct:OnAddSkillPerform(skill_perform)
    cclog("SkillActivatedObejct:OnAddSkillPerform index="..skill_perform.index);
    
    self.skill_performs[#self.skill_performs+1] = skill_perform;
end

function SkillActivatedObejct:OnRemoveSkillPerform(skill_perform)
    cclog("SkillActivatedObejct:OnRemoveSkillPerform index="..skill_perform.index);
    
	  local remove_map = {};
    local i = 0;
    for key, perform in pairs(self.skill_performs) do
        i = i + 1;
        if (perform == skill_perform) then
            remove_map[#remove_map+1] = i;
            break;
        end
    end
    
    if (table.nums(remove_map) ~= 0) then
        for k, v in pairs(remove_map) do
            table.remove(self.skill_performs,v);
            cclog("SkillActivatedObejct:OnRemoveSkillPerform remove key="..v.." size="..table.nums(self.skill_performs));
        end
    end
end

function SkillActivatedObejct:OnCastSkill(target,skill)
    cclog("SkillActivatedObejct:OnCastSkill");
end

function SkillActivatedObejct:GetPos()
    return nil;
end

function SkillActivatedObejct:Jump(grid_num)
end

function SkillActivatedObejct:CheckTarget()
	 cclog("SkillActivatedObejct:CheckTarget");
end

function SkillActivatedObejct:CreateEffect(target, type, params)
    cclog("SkillActivatedObejct:CreateEffect");
end

function SkillActivatedObejct:Heartbeat()
    --CalcCostMS2(2,"");
	  self.check_target_tick_count = self.check_target_tick_count + 1;
	  if (self.check_target_tick_count >= 0.2/BaseScene.instance.maplogic.tick_time) then
        self.check_target_tick_count = 0;
        self:CheckTarget();
    end
    --CalcCostMS2(2,"SkillActivatedObejct:Heartbeat CheckTarget");
    
    for key, skill in pairs(self.skills) do
        if (skill ~= nil) then
            skill:Heartbeat();
        end
    end
    --CalcCostMS2(2,"SkillActivatedObejct:Heartbeat skills");
    
    for key, skill_perform in pairs(self.skill_performs) do
        if (skill_perform ~= nil) then
            skill_perform:Heartbeat();
        end
    end
    --CalcCostMS2(2,"SkillActivatedObejct:Heartbeat skill_performs");
end