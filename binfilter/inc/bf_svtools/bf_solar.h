/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#ifndef _BF_SOLAR_H
#define _BF_SOLAR_H

#include <tools/solar.h>

/*** common solar defines ***********************************/

#ifndef TRUE
#define TRUE        1
#endif
#ifndef FALSE
#define FALSE       0
#endif

/*** common solar types ********************************************/
/* NOTE: these types are deprecated, or soon will be.  They should */
/* not be used in new code, and should be replaced with their      */
/* corresponding types from sal/types.h in old code when possible. */
/*   Previous typedefs from before sal convergence are in comments */
/*   to the right of the new types.                                */

typedef sal_Bool        BOOL;   /* typedef unsigned char   BOOL; */
typedef sal_uInt8       BYTE;   /* typedef unsigned char   BYTE; */
typedef sal_uInt16      USHORT; /* typedef unsigned short  USHORT; */
typedef sal_uIntPtr     ULONG;  /* typedef unsigned long   ULONG; */
typedef int             FASTBOOL;

#if !defined(VCL_NEED_BASETSD) || defined(__MINGW32__)
#ifndef _SOLAR_NOUINT
typedef sal_Int16           INT16;  /* typedef short           INT16; */
typedef sal_uInt16          UINT16; /* typedef unsigned short  UINT16; */
#if defined(SAL_W32)
typedef sal_sChar           INT8;
#else
typedef sal_Char            INT8;   /* typedef char            INT8; */
#endif
typedef sal_uInt8           UINT8;  /* typedef unsigned char   UINT8; */
#endif /* _SOLAR_NOUINT */
#endif

#ifndef VCL_NEED_BASETSD
#ifndef _SOLAR_NOUINT
/* types with exact defined size (not just the minimum size) */
typedef sal_Int64           INT64;  /* typedef long            INT64;  previously "void" on Windows */
typedef sal_uInt64          UINT64; /* typedef unsigned long   UINT64; previously "void" on Windows */
typedef sal_Int32           INT32;  /* typedef int             INT32;  previously "long" on Windows */
typedef sal_uInt32          UINT32; /* typedef unsigned int    UINT32; previously "unsigned long" on Windows */
#endif /* _SOLAR_NOUINT */
#endif

#define SWAPSHORT OSL_SWAPWORD
#define SWAPLONG OSL_SWAPDWORD

#endif  /* _BF_SOLAR_H */

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
