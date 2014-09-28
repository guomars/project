/*
 * FILE: EC_GPDataType.h
 *
 * DESCRIPTION: Game protocol data type
 *
 * CREATED BY: CuiMing, Duyuxin, 2004/9/9
 *
 * HISTORY: 
 *
 * Copyright (c) 2004 Archosaur Studio, All Rights Reserved.
 */

#pragma once

#include "EC_RoleTypes.h"
#include <vector>

///////////////////////////////////////////////////////////////////////////
//	
//	Define and Macro
//	
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
//	
//	Reference to External variables and functions
//	
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
//	
//	Local Types and Variables and Global variables
//	
///////////////////////////////////////////////////////////////////////////

#pragma pack(1)

namespace S2C
{
	typedef unsigned char byte;

	//	提取压缩数据辅助模板类
	template <typename T>
	bool Extract(T &ret, const byte *&pDataBuf, unsigned int &dwDataSize)
	{
		//	提取单个数据类型
		if (dwDataSize >= sizeof(T))
		{
			ret = *(const T*)pDataBuf;
			pDataBuf += sizeof(T);
			dwDataSize -= sizeof(T);
			return true;
		}
		return false;
	}

	template <typename T>
	bool Extract(T *pRet, int count, const byte *&pDataBuf, unsigned int &dwDataSize)
	{
		//	提取数组
		if (count >=0)
		{
			unsigned int s = sizeof(T)*count;
			if (dwDataSize >= s)
			{
				::memcpy(pRet, pDataBuf, s);
				pDataBuf += s;
				dwDataSize -= s;
				return true;
			}
		}
		return false;
	}

	//	Data type ---------------------------
	struct info_player_1
	{
		int cid;
		A3DVECTOR3 pos;
		unsigned short crc_e;
		unsigned short crc_c;
		unsigned char dir;		//256的定点数表示度数
		unsigned char level2;
		int state;
		int state2;

		bool CheckValid(size_t buf_size, size_t& sz) const
		{
			if (buf_size < sizeof(*this))
				return false;

			return buf_size >= sz;
		}
	};

	struct info_player_2		//name ,customize data 不常改变
	{
		unsigned char size;
		char data[1];
	};

	struct info_player_3		//viewdata of equipments and special effect
	{
		unsigned char size;
		char  data[1];
	};

	struct info_player_4		//detail
	{
		unsigned short size;
		char	data[1];
	};

	//	Commands ----------------------------

	enum	//	Command ID
	{
		PROTOCOL_COMMAND = -1,	//	Reserved for protocol
		
		PLAYER_INFO_1 = 0,
		PLAYER_INFO_2,
		PLAYER_INFO_3,
		PLAYER_INFO_4,
	};

	struct cmd_header
	{
        unsigned short cmd;
	};

	//	object 离开可见区域
	struct cmd_leave_slice
	{
		int id;
	};

	//	player更新位置
	struct cmd_notify_hostpos
	{
		A3DVECTOR3 vPos;
		int tag;
	};

	struct cmd_change_curr_title_re
	{
		int roleid;
		unsigned short titleid;
	};
	struct cmd_modify_title_notify
	{
		unsigned short id;
		int expiretime;
		char flag;
	};
	struct cmd_refresh_signin
	{
		char	type; // 同步原因 0初始1数据不同步2签到3补签4领奖
		int		monthcalendar;// 当前月签到日历
		int		curryearstate; // 当前年月份签到状态
		int		lastyearstate; // 去年月份签到状态
		int		updatetime;  // 签到数据最后一次变更时间  
		int		localtime;   // 当前服务器时间
	};
}

namespace C2S
{
	typedef unsigned char byte;

	//	Data type ---------------------------

	//	Commands ----------------------------
	enum
	{
		PLAYER_MOVE,		//	0
		LOGOUT,
	};

	struct cmd_header
	{
        unsigned short cmd;
	};

	struct cmd_player_move
	{
		A3DVECTOR3 vCurPos;
		A3DVECTOR3 vNextPos;
		unsigned short use_time;
		short sSpeed;				//	Move speed 8.8 fix-point
		unsigned char move_mode;	//	Walk run swim fly .... walk_back run_back
		unsigned short stamp;		//	move command stamp
	};

	struct cmd_stop_move
	{
		A3DVECTOR3 vCurPos;
		short sSpeed;				//	Moving speed in 8.8 fix-point
		unsigned char dir;			//	对象的方向
		unsigned char move_mode;	//	Walk run swim fly .... walk_back run_back
		unsigned short stamp;		//	move command stamp
		unsigned short use_time;
	};

	struct cmd_player_logout
	{
		int iOutType;
	};
}

#pragma pack()

