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
#ifndef _SFX_MACROCONF_HXX
#define _SFX_MACROCONF_HXX

#include <tools/errcode.hxx>
#define _SVSTDARR_USHORTS
#include <bf_svtools/svstdarr.hxx>      // SvUShorts
#include <bf_sfx2/evntconf.hxx>
class SvStream;
namespace binfilter {

class SvxMacro;
class BasicManager;
class SbMethod;
class SbxValue;
class SbxObject;
class SbxArray;
class SfxMacroInfo;
class SfxSlot;
class SfxMacroInfoItem;
class SfxObjectShell;
struct SfxMacroConfig_Impl;

typedef SfxMacroInfo* SfxMacroInfoPtr;
#if _SOLAR__PRIVATE
SV_DECL_PTRARR(SfxMacroInfoArr_Impl, SfxMacroInfoPtr, 5, 5)
#else
class SfxMacroInfoArr_Impl;
#endif

class SfxMacroInfo
{
friend class SfxMacroConfig;
friend class SfxEventConfiguration;
friend SvStream& operator >> (SvStream& rStream, SfxMacroInfo& rInfo);
friend SvStream& operator << (SvStream& rStream, const SfxMacroInfo& rInfo);

    SfxObjectShell*         pDocShell;          // nur noch wg. Kompatib. drin
    String*                 pHelpText;
    sal_uInt16              nRefCnt;
    sal_Bool                bAppBasic;
    String                  aLibName;
    String                  aModuleName;
    String                  aMethodName;
    sal_uInt16              nSlotId;
    SfxSlot*                pSlot;

public:
    SfxMacroInfo(SfxObjectShell *pDoc=NULL);
    ~SfxMacroInfo();

    int Store (SvStream&);

    sal_Bool            IsAppMacro() const
                        { return bAppBasic; }
    const String&       GetModuleName() const
                        { return aModuleName; }
    const String&       GetLibName() const
                        { return aLibName; }
    const String&       GetMethodName() const
                        { return aMethodName; }
    sal_uInt16              GetSlotId() const
                        { return nSlotId; }
    SfxSlot*            GetSlot() const
                        { return pSlot; }
};

class SfxMacroConfig
{
friend class SfxEventConfiguration;

    static SfxMacroConfig*  pMacroConfig;

    SfxMacroConfig_Impl*    pImp;
    SvUShorts               aIdArray;

public:
                            ~SfxMacroConfig();

    static SbMethod*        GetMethod_Impl( const String&, BasicManager* );

#if _SOLAR__PRIVATE
    static void             Release_Impl();
#endif
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
