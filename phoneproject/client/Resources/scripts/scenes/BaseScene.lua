--所有Scene的类型
SCENE_TYPE_WELCOME = 1;
SCENE_TYPE_MENU = 2;
SCENE_TYPE_CHOOSE_MAP = 3;
SCENE_TYPE_MAP = 4;
SCENE_TYPE_MOLE = 5;

--保存了所有的scene
All_Scenes = {};

--这个是所有scene的基类
BaseScene = class("BaseScene");

function BaseScene:create(type,params)
    scene = nil;
    
    if (All_Scenes[type] ~= nil) then
        BaseScene.instance = clone(All_Scenes[type]);
        scene_obj = CCScene:create();
		    BaseScene.instance:init(scene_obj,params);
		    scene = scene_obj;
    end
    
    return scene;
end

function BaseScene:loading_init(scene_obj,params)
    BaseScene.instance:init(scene_obj,params);
end

function BaseScene:init(scene,params)
		cclog("BaseScene:init");
end