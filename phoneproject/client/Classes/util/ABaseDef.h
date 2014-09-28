/*
 * FILE: ABaseDef.h
 *
 * DESCRIPTION: Base definition
 *
 * CREATED BY: duyuxin, 2003/6/6
 *
 * HISTORY:
 *
 * Copyright (c) 2001 Archosaur Studio, All Rights Reserved.
 */

#ifndef _ABASEDEF_H_
#define _ABASEDEF_H_

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////
//
//	Define and Macro
//
///////////////////////////////////////////////////////////////////////////

#ifndef ASSERT
#include <assert.h>
#define ASSERT	assert
#endif	//	ASSERT

#define TRUE				1
#define FALSE				0

#ifdef UNICODE
	typedef wchar_t			ACHAR;
	#define _AL(str)		L##str
#else
	typedef char			ACHAR;
	#define _AL(str)		str
#endif

#endif	//	_ABASEDEF_H_
