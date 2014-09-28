#pragma once

#include <string>
#include <map>
#include "support/tinyxml2/tinyxml2.h"

namespace aeditor {
	class FightAction {
	public:
		std::string aeFileName;
		std::string actionSpriteName;

		FightAction() {}

		FightAction(const std::string _aeFileName, const std::string _actionSpriteName) 
			: aeFileName(_aeFileName), actionSpriteName(_actionSpriteName) {}
	};

	enum EFightActionType {
		EFAT_Perform,		// 施放
		EFAT_Hit,			// 被击
		EFAT_Avoid,			// 躲闪
		EFAT_Frenzy,		// 被暴击
		EFAT_Move,			// 移动一格
		EFAT_TransferCol,	// 换列
	};

	class FightConf {
	public:
		float sprite_width;
		float sprite_height;
		float x_dist;
		float y_dist;

		std::map<EFightActionType, FightAction> defaultActions;

		FightConf(tinyxml2::XMLElement* eRoot) : sprite_width(150), sprite_height(150), x_dist(150), y_dist(112) 
		{
			tinyxml2::XMLElement* eSprite = eRoot->FirstChildElement("sprite");
			sprite_width = eSprite->FloatAttribute("width");
			sprite_height = eSprite->FloatAttribute("height");
			x_dist = eSprite->FloatAttribute("x_dist");
			y_dist = eSprite->FloatAttribute("y_dist");

			for (tinyxml2::XMLElement* eDefaultAction = eRoot->FirstChildElement("default_action"); eDefaultAction != NULL; eDefaultAction = eDefaultAction->NextSiblingElement("default_action")) 
			{
				std::string strDefaultActionName = eDefaultAction->Attribute("name");
				if (strDefaultActionName == "perform") {
					defaultActions[EFAT_Perform] = FightAction(eDefaultAction->Attribute("file"), eDefaultAction->Attribute("sprite"));
				} else if (strDefaultActionName == "hit") {
					defaultActions[EFAT_Hit] = FightAction(eDefaultAction->Attribute("file"), eDefaultAction->Attribute("sprite"));
				} else if (strDefaultActionName == "avoid") {
					defaultActions[EFAT_Avoid] = FightAction(eDefaultAction->Attribute("file"), eDefaultAction->Attribute("sprite"));
				} else if (strDefaultActionName == "frenzy") {
					defaultActions[EFAT_Frenzy] = FightAction(eDefaultAction->Attribute("file"), eDefaultAction->Attribute("sprite"));
				} else if (strDefaultActionName == "move") {
					defaultActions[EFAT_Move] = FightAction(eDefaultAction->Attribute("file"), eDefaultAction->Attribute("sprite"));
				} else if (strDefaultActionName == "transfer") {
					defaultActions[EFAT_TransferCol] = FightAction(eDefaultAction->Attribute("file"), eDefaultAction->Attribute("sprite"));
				} else {
					// 忽略未知动作
				}
			}
		}
	};

	extern FightConf* getFightConf();
};