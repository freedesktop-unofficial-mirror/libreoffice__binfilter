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
#ifndef _SFX_PROGRESS_HXX
#define _SFX_PROGRESS_HXX

#include <bf_svtools/bf_solar.h>

#include <tools/link.hxx>
namespace binfilter {
class String;
class SfxObjectShell;
class SfxStatusBarManager;
class INetHint;
struct SfxProgress_Impl;
struct PlugInLoadStatus;
struct SvProgressArg;

//=======================================================================

class SfxProgress
{
    SfxProgress_Impl*       pImp;
    ULONG                   nVal;
    BOOL                    bSuspended;

public:
                            SfxProgress( SfxObjectShell* pObjSh,
                                         const String& rText,
                                         ULONG nRange, BOOL bAllDocs = FALSE,
                                         BOOL bWait = TRUE );
    virtual                 ~SfxProgress();

    virtual BOOL            SetState( ULONG nVal, ULONG nNewRange = 0 );
    ULONG                   GetState() const { return nVal; }

    void                    Resume();
    void                    Suspend();
    BOOL                    IsSuspended() const { return bSuspended; }

    void                    Stop();


    static SfxProgress*     GetActiveProgress( SfxObjectShell *pDocSh = 0 );

#if _SOLAR__PRIVATE
    DECL_STATIC_LINK( SfxProgress, SetStateHdl, PlugInLoadStatus* );
#endif
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
