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

#ifndef _EHDL_HXX
#define _EHDL_HXX

#include <bf_svtools/bf_solar.h>

#ifndef __RSC

#include <bf_tools/string.hxx>

#include <tools/errinf.hxx>

class Window;
class ResMgr;

namespace binfilter
{

class  SfxErrorContext : private ErrorContext
{
public:
    SfxErrorContext(
            USHORT nCtxIdP, const String &aArg1, Window *pWin=0,
            USHORT nResIdP=USHRT_MAX, ResMgr *pMgrP=0);
    virtual BOOL GetString(ULONG nErrId, ::String &rStr);

private:
    USHORT nCtxId;
    USHORT nResId;
    ResMgr *pMgr;
    String aArg1;
};

class  SfxErrorHandler : private ErrorHandler
{
public:
    SfxErrorHandler(USHORT nId, ULONG lStart, ULONG lEnd, ResMgr *pMgr=0);
    ~SfxErrorHandler();

protected:
    virtual BOOL     GetErrorString(ULONG lErrId, ::String &, USHORT&) const;
    virtual BOOL     GetMessageString(ULONG lErrId, ::String &, USHORT&) const;

private:

    ULONG            lStart;
    ULONG            lEnd;
    USHORT           nId;
    ResMgr          *pMgr;
    ResMgr          *pFreeMgr;

    BOOL             GetClassString(ULONG lErrId, String &) const;
    virtual BOOL     CreateString(
                         const ErrorInfo *, ::String &, USHORT &) const;
};


}

#endif

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
