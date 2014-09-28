 /*
 * FILE: EC_SendC2SCmds.cpp
 *
 * DESCRIPTION: Functions used to C2S net commands
 *
 * CREATED BY: duyuxin, 2004/11/15
 *
 * HISTORY:
 *
 * Copyright (c) 2003 Archosaur Studio, All Rights Reserved.
 */

#include "EC_SendC2sCmds.h"
#include "EC_IvtrTypes.h"
#include "AChar.h"
#include "NetworkMgr.h"

///////////////////////////////////////////////////////////////////////////
//	
//	Define and Macro
//	
///////////////////////////////////////////////////////////////////////////

//	Macros used to implement 16.16 fix point calculation
#define	INTTOFIX16(x)		(((int)(x)) << 16)
#define FIX16TOINT(x)		(((x) + 0x00008000) >> 16)
#define FIX16TOINTCEIL(x)	(((x) + 0x0000ffff) >> 16)
#define FIX16TOINTFLOOR(x)	((x) >> 16)
#define FLOATTOFIX16(x)		((int)((x) * 65536.0f + 0.5f))
#define FIX16TOFLOAT(x)		((x) / 65536.0f)

#define FLOATTOFIX8(x)		((short)((x) * 256.0f + 0.5f))
#define FIX8TOFLOAT(x)		((x) / 256.0f)

#define FIX16MUL(M1, M2)	(int)(((__int64)(M1) * (M2) + 0x00008000) >> 16)
#define FIX16DIV(D1, D2)	(int)(((__int64)(D1) << 16) / (D2))

//	Check whether a position value is valid
#define INVALIDPOS			9000000.0f
#define POSISVALID(x)		((x) < INVALIDPOS-1.0f && (x) > -INVALIDPOS+1.0f)

//	Fixed length game command structure
#define FIXLEN_GAMECMD(cmd_id, content_type) \
	using namespace C2S; \
	struct \
	{ \
		cmd_header hd; \
		char content[sizeof (content_type)]; \
	} cmd; \
	cmd.hd.cmd = cmd_id; \
    content_type* pCmd = (content_type*)(&cmd.content); \
	int iSize = sizeof (cmd_header) + sizeof (content_type);

//	Fixed length NPC service command structure
#define FIXLEN_NPCSEV(sev_id, content_type) \
	using namespace C2S; \
	struct \
	{ \
		cmd_header hd; \
		cmd_sevnpc_serve sev; \
		char content[sizeof (content_type)]; \
	} cmd; \
	cmd.hd.cmd = SEVNPC_SERVE; \
	cmd.sev.service_type = sev_id; \
	cmd.sev.len = sizeof (content_type); \
    content_type* pContent = (content_type*)(&cmd.content); \
	int iSize = sizeof (cmd_header) + sizeof (cmd_sevnpc_serve) + sizeof (content_type);

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


///////////////////////////////////////////////////////////////////////////
//	
//	Local functions
//	
///////////////////////////////////////////////////////////////////////////

//	Send a nake command (commands that have id but havn't data)
static inline void _SendNakeCommand(int iCmd)
{
	using namespace C2S;

	int iSize = sizeof (cmd_header);
	unsigned char* pBuf = new unsigned char [iSize];
	if (!pBuf)
		return;
	
	((cmd_header*)pBuf)->cmd = iCmd;
	NetworkMgr::sharedMgr()->sendGameData(pBuf, iSize);

	delete [] pBuf;
}

void c2s_SendCmdGameDataSend(int cmd_header_type,void*pData,int size)
{
	using namespace C2S;

	int iSize = sizeof (cmd_header) + size;
	unsigned char* pBuf = new unsigned char [iSize];
	if (!pBuf)
		return;
	
	((cmd_header*)pBuf)->cmd = (unsigned short)cmd_header_type;

	char* p = (char*)(pBuf + sizeof (cmd_header));

	memcpy(p,pData,size);

	NetworkMgr::sharedMgr()->sendGameData(pBuf, iSize);

	delete [] pBuf;
}

void c2s_SendDebugCmd(int iCmd, int iNumParams, ...)
{
	using namespace C2S;

	int iSize = sizeof (cmd_header) + iNumParams * sizeof (int);
	unsigned char* pBuf = new unsigned char [iSize];
	if (!pBuf)
		return;
	
	((cmd_header*)pBuf)->cmd = iCmd;

	if (iNumParams)
	{
		va_list vaList;
		va_start(vaList, iNumParams);

		int* pData = (int*)(pBuf + sizeof (cmd_header));
		for (int i=0; i < iNumParams; i++)
			*pData++ = va_arg(vaList, int);

		va_end(vaList);
	}

	NetworkMgr::sharedMgr()->sendGameData(pBuf, iSize);

	delete [] pBuf;
}