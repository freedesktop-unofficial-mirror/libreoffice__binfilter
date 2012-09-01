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

#ifndef SW_SWDLL_HXX
#define SW_SWDLL_HXX

#include <bf_svtools/bf_solar.h>

class ResMgr;
class SvFactory;
class SotFactory;
class StatusBar;

class SfxMedium;
class SfxFilter;

#include <bf_sfx2/sfxdefs.hxx>
#include <bf_sfx2/module.hxx>

#include <bf_so3/pseudo.hxx>

namespace binfilter {

class SwDLL

/*  [Description]

    This class is a wrapper for a Load-On-Demand-DLL. One instance
    per SfxApplication will be created for the runtime of
    SfxApplication-subclass::Main().

    Remember: Do export this class! It is used by the application.
*/

{

    static void RegisterFactories();

public:
                    // Ctor/Dtor must be linked to the application
                    SwDLL();
                    ~SwDLL();

                    // static-init/exit-code must be linked to the application
    static void     LibInit();  // called from SfxApplication-subclass::Init()
    static void     LibExit();  // called from SfxApplication-subclass::Exit()

                    // DLL-init/exit-code must be linked to the DLL only
    static void     Init();     // called directly after loading the DLL
    static void     Exit();     // called directly befor unloading the DLL

    static ULONG    DetectFilter( SfxMedium& rMedium, const SfxFilter** ppFilter,
                                    SfxFilterFlags nMust, SfxFilterFlags nDont );
    static ULONG    GlobDetectFilter( SfxMedium& rMedium, const SfxFilter** ppFilter,
                                    SfxFilterFlags nMust, SfxFilterFlags nDont );

    static sal_Bool RegisterFrameLoaders( void* pServiceManager, void* pRegistryKey );
    static void*    CreateFrameLoader( const sal_Char* pImplementationName, void* pServiceManager, void *pRegistryKey );
};

//-------------------------------------------------------------------------

class SwModuleDummy : public SfxModule

/*  [Description]

    This tricky class keeps pointers to the SvFactories while
    the DLL isn`t loaded. A pointer to the one instance is available
    through SXX_MOD() (shared-lib-app-data).
*/

{
public:
    virtual ~SwModuleDummy();
    TYPEINFO();
                    // SvFactory name convention:
                    // 'p' + SfxObjectShell-subclass + 'Factory'
    SotFactory*     pSwDocShellFactory;
    SotFactory*     pSwWebDocShellFactory;
    SotFactory*     pSwGlobalDocShellFactory;

                    SwModuleDummy( ResMgr *pResMgrIn, BOOL bDummyIn,
                                    SotFactory* pWebFact,
                                    SotFactory* pFact,
                                    SotFactory* pGlobalFact )
                    :   SfxModule(pResMgrIn, bDummyIn,
                                (SfxObjectFactory*)pFact,
                                (SfxObjectFactory*)pWebFact,
                                (SfxObjectFactory*)pGlobalFact, 0L),
                        pSwDocShellFactory( pFact ),
                        pSwWebDocShellFactory( pWebFact ),
                        pSwGlobalDocShellFactory( pGlobalFact )
                    {}

    virtual SfxModule* Load();
};

//-------------------------------------------------------------------------

#define SW_DLL() ( *(SwModuleDummy**) GetAppData(BF_SHL_WRITER) )

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
