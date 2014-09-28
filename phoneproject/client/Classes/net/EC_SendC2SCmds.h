/*
 * FILE: EC_SendC2SCmds.h
 *
 * DESCRIPTION: 
 *
 * CREATED BY: Duyuxin, 2005/1/22
 *
 * HISTORY: 
 *
 * Copyright (c) 2004 Archosaur Studio, All Rights Reserved.
 */

#pragma once

#include "A3DVector.h"
#include "EC_RoleTypes.h"
#include "EC_GPDataType.h"
///////////////////////////////////////////////////////////////////////////
//	
//	Define and Macro
//	
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
//	
//	Types and Global variables
//	
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
//	
//	Declare of Global functions
//	
///////////////////////////////////////////////////////////////////////////

void c2s_SendCmdGameDataSend(int cmd_header_type,void*pData,int size);

void c2s_SendDebugCmd(int iCmd, int iNumParams, ...);
