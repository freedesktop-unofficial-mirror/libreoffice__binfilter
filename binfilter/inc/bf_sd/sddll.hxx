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

#ifndef _SDDLL_HXX
#define _SDDLL_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_so3/pseudo.hxx>

#include <bf_sfx2/module.hxx>
#include <bf_sfx2/sfxdefs.hxx>
class SvFactory;
class SotFactory;
namespace binfilter {

class SfxMedium;
class SfxFilter;

/*************************************************************************
|*
|* This class is a wrapper for a Load-On-Demand-DLL. One instance
|* per SfxApplication will be created for the runtime of
|* SfxApplication-subclass::Main().
|*
|* Remember: Do export this class! It is used by the application.
|*
\************************************************************************/

class SdDLL
{
public:
                    // Ctor/Dtor must be linked to the application
                    SdDLL();
                    ~SdDLL();

                    // static-init/exit-code must be linked to the application
    static void     LibInit();  // called from SfxApplication-subclass::Init()
    static void     LibExit();  // called from SfxApplication-subclass::Exit()

                    // DLL-init/exit-code must be linked to the DLL only
    static void     Init();     // called directly after loading the DLL
    static void     Exit();     // called directly befor unloading the DLL

    static ULONG    DetectFilter(SfxMedium& rMedium, const SfxFilter** pFilter,
                                 SfxFilterFlags nMust, SfxFilterFlags nDont);
};

/*************************************************************************
|*
|* This tricky class keeps pointers to the SvFactories while
|* the DLL isn`t loaded. A pointer to the one instance is available
|* through SD_MOD() (shared-lib-app-data).
|*
\************************************************************************/

class SdModuleDummy : public SfxModule
{
public:
    TYPEINFO();

                // SvFactory name convention:
                // 'p' + SfxObjectShell-subclass + 'Factory'
    SotFactory* pSdDrawDocShellFactory;
    SotFactory* pSdGraphicDocShellFactory;

               SdModuleDummy(ResMgr* pResMgrIn, BOOL bDummyIn,
                             SotFactory* pDrawObjFact, SotFactory* pGraphicObjFact)
               : SfxModule(pResMgrIn, bDummyIn,
                            // Der erste Factory-Pointer muss gueltig sein!
                           (SfxObjectFactory*) (pDrawObjFact ? pDrawObjFact    : pGraphicObjFact),
                           (SfxObjectFactory*) (pDrawObjFact ? pGraphicObjFact : pDrawObjFact),
                           0L),
                 pSdDrawDocShellFactory( pDrawObjFact ),
                 pSdGraphicDocShellFactory( pGraphicObjFact )
               {}

    virtual SfxModule*  Load();
};

#ifndef _SD_DLL                      // Das define muss im Draw gesetzt werden
#define SD_MOD() ( *(SdModuleDummy**) GetAppData(BF_SHL_DRAW) )
#endif

} //namespace binfilter
#endif                               // _SDDLL_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
