/*
 * FILE: EC_IvtrTypes.h
 *
 * DESCRIPTION: 
 *
 * CREATED BY: Duyuxin, 2004/11/19
 *
 * HISTORY: 
 *
 * Copyright (c) 2004 Archosaur Studio, All Rights Reserved.
 */

#pragma once

///////////////////////////////////////////////////////////////////////////
//	
//	Define and Macro
//	
///////////////////////////////////////////////////////////////////////////

#ifndef NUM_MAGICCLASS
#define NUM_MAGICCLASS		5
#endif	//	NUM_MAGICCLASS

//	Equipment endurance scale
#define ENDURANCE_SCALE		100
//	Player item price scale
#define PLAYER_PRICE_SCALE	1.0f
//	Weapon endurance reduce speed
#define WEAPON_RUIN_SPEED	-2
//	Armor endurance reduce speed
#define ARMOR_RUIN_SPEED	-25

//	Inventory type
enum
{
	IVTRTYPE_PACK = 0,		//	Normal pack
	IVTRTYPE_EQUIPPACK,		//	Equipment
	IVTRTYPE_TASKPACK,		//	Task pack
	IVTRTYPE_TRASHBOX,		//	Trash box
	IVTRTYPE_TRASHBOX2,		//	Trash box - material box
	IVTRTYPE_TRASHBOX3,		//	Trash box - fashion box
	IVTRTYPE_ACCOUNT_BOX,	//  User account box
};

//	Index of item in equipment inventory
enum
{
	EQUIPIVTR_WEAPON = 0,
	EQUIPIVTR_HEAD,
	EQUIPIVTR_NECK,
	EQUIPIVTR_SHOULDER,
	EQUIPIVTR_BODY,
	EQUIPIVTR_WAIST,
	EQUIPIVTR_LEG,
	EQUIPIVTR_FOOT,
	EQUIPIVTR_WRIST,
	EQUIPIVTR_FINGER1,
	EQUIPIVTR_FINGER2,
	EQUIPIVTR_PROJECTILE,
	EQUIPIVTR_FLYSWORD,
	EQUIPIVTR_FASHION_BODY,
	EQUIPIVTR_FASHION_LEG,
	EQUIPIVTR_FASHION_FOOT,
	EQUIPIVTR_FASHION_WRIST,
	EQUIPIVTR_RUNE,
	EQUIPIVTR_BIBLE,
	EQUIPIVTR_SPEAKER,
	EQUIPIVTR_AUTOHP,
	EQUIPIVTR_AUTOMP,
	EQUIPIVTR_POCKET,
	EQUIPIVTR_GOBLIN,
	EQUIPIVTR_CERTIFICATE,
	EQUIPIVTR_FASHION_HEAD,
	EQUIPIVTR_FORCE_TOKEN,
	EQUIPIVTR_DYNSKILLEQUIP1,
	EQUIPIVTR_DYNSKILLEQUIP2,
	EQUIPIVTR_FASHION_WEAPON,
	SIZE_EQUIPIVTR,
};

//	Inventory size
enum
{
	IVTRSIZE_EQUIPPACK	= SIZE_EQUIPIVTR,	//	Equipment
	IVTRSIZE_TASKPACK	= 20,	//	Task pack
	IVTRSIZE_DEALPACK	= 24,	//	Deal pack
	IVTRSIZE_NPCPACK	= 32,	//	NPC pack
	IVTRSIZE_TRASHBOX	= 16,	//	Trash box
	IVTRSIZE_BUYPACK	= 12,	//	Buy pack
	IVTRSIZE_SELLPACK	= 12,	//	Sell pack
	IVTRSIZE_BOOTHSPACK	= 12,	//	Default booth pack for selling
	IVTRSIZE_BOOTHBPACK = 12,	//	Default booth pack for buying
	IVTRSIZE_BOOTHSPACK_MAX	= 20,	//	Max booth pack for selling (player may use certificate...)
	IVTRSIZE_BOOTHBPACK_MAX = 20,	//	Max booth pack for buying
	
	NUM_NPCIVTR			= 8,	//	NPC inventory number
};

//	Equip mask
enum
{
	EQUIP_MASK_WEAPON       	= 0x00000001,
	EQUIP_MASK_HEAD         	= 0x00000002,
	EQUIP_MASK_NECK         	= 0x00000004,
	EQUIP_MASK_SHOULDER     	= 0x00000008,
	EQUIP_MASK_BODY         	= 0x00000010,
	EQUIP_MASK_WAIST        	= 0x00000020,
	EQUIP_MASK_LEG          	= 0x00000040,
	EQUIP_MASK_FOOT         	= 0x00000080,
	EQUIP_MASK_WRIST        	= 0x00000100,
	EQUIP_MASK_FINGER1      	= 0x00000200,
	EQUIP_MASK_FINGER2      	= 0x00000400,
	EQUIP_MASK_PROJECTILE   	= 0x00000800,
	EQUIP_MASK_FLYSWORD			= 0x00001000,
	EQUIP_MASK_FASHION_BODY		= 0x00002000,
	EQUIP_MASK_FASHION_LEG		= 0x00004000,
	EQUIP_MASK_FASHION_FOOT		= 0x00008000,
	EQUIP_MASK_FASHION_WRIST	= 0x00010000,
	EQUIP_MASK_RUNE				= 0x00020000,
	EQUIP_MASK_BIBLE			= 0x00040000,
	EQUIP_MASK_SPEAKER			= 0x00080000,
	EQUIP_MASK_AUTOHP			= 0x00100000,
	EQUIP_MASK_AUTOMP			= 0x00200000,
	EQUIP_MASK_POCKET			= 0x00400000,
	EQUIP_MASK_GOBLIN			= 0x00800000,
	EQUIP_MASK_CERTIFICATE		= 0x01000000,
	EQUIP_MASK_FASHION_HEAD		= 0x02000000,
	EQUIP_MASK_FORCE_TICKET		= 0x04000000,
	EQUIP_MASK_DYNSKILLEQUIP1	=	0x08000000,
	EQUIP_MASK_DYNSKILLEQUIP2	=	0x10000000,
	EQUIP_MASK_FASHION_WEAPON	=	0x20000000,
	EQUIP_MASK_ALL				= 0x0fffffff,
};

//	Weapon type
enum
{
    WEAPONTYPE_MELEE = 0,
    WEAPONTYPE_RANGE = 1,
};

//	Shortcut
enum
{
	NUM_HOSTSCSETS1 = 5,	// expanded from 3 to 5 (2009.05.27)
	NUM_HOSTSCSETS2 = 3,
	SIZE_HOSTSCSET1 = 9,	// expanded from 6 to 9 (2009.05.27)
	SIZE_HOSTSCSET2 = 8,

	SIZE_FASHIONSCSET = 240,
};

//	Pet food type
enum
{
	PET_FOOD_GRASS = 0,
	PET_FOOD_MEAT,
	PET_FOOD_VEGETABLE,
	PET_FOOD_FRUIT,
	PET_FOOD_WATER,
	MAX_PET_FOOD,
};

///////////////////////////////////////////////////////////////////////////
//	
//	Types and Global variables
//	
///////////////////////////////////////////////////////////////////////////

#pragma pack(1)

struct IVTR_ESSENCE_WEAPON
{
    short	weapon_type;
	short	weapon_dealy;
	int		weapon_class;
	int		weapon_level;
    int		require_projectile; 	//	需要弹药的类型
    int		damage_low;         	//	物理攻击最小加值
    int 	damage_high;        	//	物理攻击最大加值
    int 	magic_damage_low;		//	魔法攻击
    int 	magic_damage_high;		//	魔法攻击
//  int 	attack;					//	命中率
    int 	attack_speed;
    float	attack_range;
    float	attack_short_range;
};

struct IVTR_ESSENCE_ARROW
{
	unsigned int	dwBowMask;
	int		iDamage;
	int		iDamageScale;			//	Percent
	int		iWeaponReqLow;
	int		iWeaponReqHigh;
};

struct IVTR_ESSENCE_DECORATION
{
	int		damage;
	int		magic_damage;
	int		defense;
	int		armor;
	int		resistance[NUM_MAGICCLASS];
};

struct IVTR_ESSENCE_ARMOR
{
	int		defense;
	int		armor;
	int		mp_enhance;
	int		hp_enhance;
	int		resistance[NUM_MAGICCLASS];
};

struct IVTR_ESSENCE_FASHION
{
	int require_level;
	unsigned short color;
	unsigned short gender;
};

struct IVTR_ESSENCE_FLYSWORD
{
	int		cur_time;
	int		max_time;
	short	require_level;
    short	level;
	int		profession;
	size_t	time_per_element;
	float	speed_increase;
	float	speed_increase2;		//	高速飞行速度
};

struct IVTR_ESSENCE_WING
{
	int		require_level;
	size_t	mp_launch;
	size_t	mp_per_second;
	float	speed_increase;
};

struct IVTR_ESSENCE_AUTOHP
{
	int		hp_left;
	float	trigger;
};

struct IVTR_ESSENCE_AUTOMP
{
	int		mp_left;
	float	trigger;
};

struct IVTR_ESSENCE_PETEGG
{
	int		req_level;          //	需求玩家级别
	int		req_class;          //	需求玩家职业
	int		honor_point;        //	好感度
	int		pet_tid;            //	宠物的模板ID
	int		pet_vis_tid;        //	宠物的可见ID（如果为0，则表示无特殊可见ID）
	int		pet_egg_tid;        //	宠物蛋的ID
	int		pet_class;          //	宠物类型 战宠，骑宠，观赏宠
	short	level;				//	宠物级别
	unsigned short	color;			//	宠物颜色，最高位为1表示有效，目前仅对骑宠有效
	int		exp;                //	宠物当前经验
	int		skill_point;        //	剩余技能点
	unsigned short name_len;	//	名字长度 
	unsigned short skill_count;	//	技能数量		
	wchar_t	name[8];			//	名字内容
	//	这里跟随技能表
	/*
	struct
	{	
		int skill
		int level;

	} skills[]
	 */
};

struct IVTR_ESSENCE_DESTROYING
{
	int tid;
};

struct IVTR_ESSENCE_GOBLIN
{
	struct _GOBLIN_DATA
	{
		unsigned int exp;			//	当前经验值
		short	level;				//	当前等级
		
		short	total_attribute;	//	升级产生的属性点总数，不包括装备增加的及各属性初始值
		short	strength;			//	力量, 由加属性点而产生的属性值，不包括装备增加的及各属性初始值
		short	agility;			//	敏捷
		short	vitality;			//	体质
		short	energy;				//	灵力

		short	total_genius;		//	升级产生的天赋点总数，不包括装备增加的
		short	genius[5];			//	金木水火土0-4 //由加天赋点而产生的天赋值，不包括装备增加的
		
		short	refine_level;		//	精炼等级
		int		stamina; 			//	耐力
		int		status_value;		//	0: 安全状态，>0：转化状态，-1:可交易状态 
	};

	_GOBLIN_DATA	data;

	int equip_cnt;					//	装备数量
//	unsigned int equipid[];			//	装备id
	int skill_cnt;					//	已学会的技能数 
/*	struct
	{	
		unsigned short skill
		short level;

	} skills[]; */
};

struct IVTR_ESSENCE_WEDDING_BOOKCARD 
{
	int	year;
	int	month;
	int	day;
};

struct IVTR_ESSENCE_WEDDING_INVITECARD 
{
	int	start_time;	//	婚礼开始时间
	int	end_time;	//	婚礼结束时间
	int	groom;		//	新郎角色 ID
	int	bride;		//	新娘角色 ID
	int	scene;		//	场景索引，用来索引名称和具体位置
	int	invitee;	//	被邀请者 ID
};

struct IVTR_ESSENCE_FORCE_TOKEN
{
	int require_force;	// 物品使用所需势力限制
	int repu_total;		// 存储的额外增加威望总额
	int repu_inc_ratio; // 每次获得威望时额外增加的威望系数，1~100对应0%~100%
};

#pragma pack()

///////////////////////////////////////////////////////////////////////////
//	
//	Declare of Global functions
//	
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
//	
//	Inline functions
//	
///////////////////////////////////////////////////////////////////////////



