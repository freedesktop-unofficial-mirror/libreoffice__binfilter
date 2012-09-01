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

#ifndef _SVTOOLS_TTPROPS_HXX
#define _SVTOOLS_TTPROPS_HXX

#include <bf_svtools/bf_solar.h>


#include <tools/rtti.hxx>
#include <vcl/apptypes.hxx>

#include <bf_svtools/svtdata.hxx>

class Bitmap;

namespace binfilter
{

class SfxPoolItem;

// Defines zur Steuerung der Ausf�hrung von Slots
#define EXECUTE_NO                  0
#define EXECUTE_POSSIBLE            1
#define EXECUTE_YES                 2
#define EXECUTEMODE_ASYNCHRON       1
#define EXECUTEMODE_DIALOGASYNCHRON 2

#define SFX_USE_BINDINGS        0x8000

// Property Requests(PR)
#define TT_PR_ONCE      0x100

#define TT_PR_SLOTS     ( 0x001 | TT_PR_ONCE )
#define TT_PR_DISPATCHER (0x002 )
#define TT_PR_IMG       ( 0x004 )

#define TT_PR_ERR_NODISPATCHER  01
#define TT_PR_ERR_NOEXECUTE     02

/// To detect inconsistencies
#define TT_PROPERTIES_VERSION   1

class  TTProperties : public ApplicationProperty
{
    USHORT nDonePRs;                    // Verwaltung f�r die Properties, die nur einmal gerufen werden mussen.
    BOOL RequestProperty( USHORT nRequest );

    BOOL HasSlots(){ return nPropertyVersion == TT_PROPERTIES_VERSION; }

public:
    TYPEINFO();

    TTProperties()
            : nDonePRs( 0 )
            , mppArgs( NULL )
            , mpBmp( NULL )
            , nPropertyVersion( 0 )
                    {}

    BOOL GetSlots();

    /// ExecuteFunction
    USHORT mnSID;
    SfxPoolItem** mppArgs;
    USHORT mnMode;
    USHORT ExecuteFunction( USHORT nSID, SfxPoolItem** ppArgs = NULL, USHORT nMode = 0 );

    /// Img
    Bitmap *mpBmp;
    BOOL Img( Bitmap *pBmp );

    static SvtResId GetSvtResId( USHORT nId );

    ULONG nSidOpenUrl;
    ULONG nSidFileName;
    ULONG nSidNewDocDirect;
    ULONG nSidCopy;
    ULONG nSidPaste;
    ULONG nSidSourceView;
    ULONG nSidSelectAll;
    ULONG nSidReferer;

    USHORT nActualPR;
    USHORT nPropertyVersion;        // Wird bei jedem call gesetzt.
};

}

#endif // _SVTOOLS_TTPROPS_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
