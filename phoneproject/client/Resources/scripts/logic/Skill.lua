--这里是所有箭塔技能的索引
SKILL_ARROW = 1;

--这里是所有怪物技能的索引
SKILL_JUMP = 1001;

--Skill的基类，必须被派生使用
Skill = class("Skill");
Skill.index = 0;

function Skill:create(master, tid, params)
    cclog("Skill:create id="..tid);
    
    skill = nil;
    
    local skillconfig_table = GetTable("skillconfig");
    local type = tonumber(skillconfig_table:GetRecByColName(tid, "type"));
    
    if (All_Skills[type] ~= nil) then
        Skill.index = Skill.index + 1;
        
        skill = clone(All_Skills[type]);
        skill.master = master;
        skill.tid = tid;
        skill.index = Skill.index;
        
        skill:init(params);
        
        skill.master:OnAddSkill(skill);
    end
    
    return skill;
end

function Skill:init(params)
    cclog("Skill:init");
end

function Skill:remove()
    cclog("Skill:remove tid="..self.tid);
    self.master:OnRemoveSkill(self);
end

function Skill:Heartbeat()
end

function Skill:OnAddSkill()
end

function Skill:CheckCast()
end

function Skill:Cast(target)
    self.master:OnCastSkill(target,self);
end

--主动技能，必须被派生使用
ActiveSkill = class("ActiveSkill", Skill);

function ActiveSkill:init(params)
    cclog("ActiveSkill:init");
    
    ActiveSkill.super.init(self,params);
    
    local skillconfig_table = GetTable("skillconfig");
    
    self.cast_tick_count = 0;
    
    self.interval = params["interval"];
    if (self.interval == nil) then
        self.interval = tonumber(skillconfig_table:GetRecByColName(self.tid, "interval"));
    end
end

function ActiveSkill:Heartbeat()
    self.cast_tick_count = self.cast_tick_count + 1;
    if (self.cast_tick_count >= self.interval/BaseScene.instance.maplogic.tick_time) then
        self.cast_tick_count = 0;
        
        self:CheckCast();
    end
end

function ActiveSkill:Cast(target)
    ActiveSkill.super.Cast(self,target);
end

--被动技能，必须被派生使用
PassiveSkill = class("PassiveSkill", Skill);

function PassiveSkill:init(params)
    cclog("PassiveSkill:init");
    
    PassiveSkill.super.init(self,params);
end

function PassiveSkill:OnAddSkill()
    self:CheckCast();
end

function PassiveSkill:CheckCast()
    self:Cast(self);
end

function PassiveSkill:Cast(target)
    PassiveSkill.super.Cast(self,target);
end

--箭塔的放箭技能
ArrowSkill = class("ArrowSkill", ActiveSkill);

function ArrowSkill:init(params)
    ArrowSkill.super.init(self,params);
    
    local skillconfig_table = GetTable("skillconfig");
    
    self.range = params["range"];
    if (self.range == nil) then
        self.range = tonumber(skillconfig_table:GetRecByColName(self.tid, "range"));
    end
    
    self.count = params["count"];
    if (self.count == nil) then
        self.count = tonumber(skillconfig_table:GetRecByColName(self.tid, "count"));
    end
    
    self.perform = params["perform"];
    if (self.perform == nil) then
        self.perform = tonumber(skillconfig_table:GetRecByColName(self.tid, "perform"));
    end
end

function ArrowSkill:CheckCast()
    --cclog("ArrowSkill:CheckCast target size="..table.nums(self.master.targets));
    
    local num = 0;
    for k,v in pairs(self.master.targets) do
        if (num >= self.count) then
            return;
        end
        if (v ~= nil) then
            local target = BaseScene.instance.maplogic.monsters[v];
            if (target ~= nil) then
                local pos1 = target:GetPos();
		            local pos2 = self.master:GetPos();
		            local dis = GET_CCP_DISTANCE(pos1,pos2);
                if (dis <= self.range) then
                    num = num + 1;
                    self:Cast(target);
                end
            end
        end
    end
end

function ArrowSkill:Cast(target)
    ArrowSkill.super.Cast(self,target);
    
    params = {};
    SkillPerform:create(self.master,target,self.perform,params);
end

All_Skills[SKILL_ARROW] = ArrowSkill.new();

--怪物的瞬移技能
JumpSkill = class("JumpSkill", ActiveSkill);

function JumpSkill:init(params)
    JumpSkill.super.init(self,params);
    
    local skillconfig_table = GetTable("skillconfig");
    
    self.jump_probability = tonumber(skillconfig_table:GetRecByColName(self.tid, "jump_probability"));
end

function JumpSkill:CheckCast()
    local rand = math.getrandnum();
    
    if (rand <= self.jump_probability) then
        self:Cast(self.master);
    end
end

function JumpSkill:Cast(target)
    JumpSkill.super.Cast(self,target);
    
    local grid_num = 3; --TODO
    
    target:Jump(grid_num);
end

All_Skills[SKILL_JUMP] = JumpSkill.new();