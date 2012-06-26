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

#ifndef _SVIPCDEF_H
#define _SVIPCDEF_H

namespace binfilter
{

#ifdef __cplusplus
extern "C" {
#endif

#if defined (WNT) || defined (WIN)
#define CDECL __cdecl
#else
#define CDECL
#endif

#if defined WIN
#define _EXTLIBCALL_ _pascal
#else
#define _EXTLIBCALL_ CDECL
#endif

typedef void (CDECL *IPCCallbackFunc)(void*);

extern void _EXTLIBCALL_ IPCFreeMemory(void*);
extern short _EXTLIBCALL_ IPCGetStatus(void*);
extern short _EXTLIBCALL_ IPCInit(void);
extern void  _EXTLIBCALL_ IPCDeInit(void);
extern void*  _EXTLIBCALL_ IPCConnectServer(const char*, IPCCallbackFunc);
extern void  _EXTLIBCALL_ IPCDisconnectServer(void *);
#ifdef WIN
extern long CDECL IPCCALLFUNCTION(void *,unsigned long,void *,
                                               short,const char *, char, ...);
#else
extern long CDECL IPCCallFunction(void *,unsigned long,void *,
                                               short,const char *, char, ...);
#endif
#ifdef __cplusplus
}
#endif

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
