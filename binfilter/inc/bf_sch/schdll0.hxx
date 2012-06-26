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

#ifndef _SCHDLL0_HXX
#define _SCHDLL0_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_so3/pseudo.hxx>

#include <bf_sfx2/module.hxx>
#include <tools/resmgr.hxx>

class SotFactory;
class SvFactory;
namespace binfilter {

/*************************************************************************
|*
|* This tricky class keeps pointers to the SvFactories while
|* the DLL isn`t loaded. A pointer to the one instance is available
|* through SD_MOD() (shared-lib-app-data).
|*
\************************************************************************/

class SchModuleDummy : public SfxModule
{
public:
    TYPEINFO();

                // SvFactory name convention:
                // 'p' + SfxObjectShell-subclass + 'Factory'
    SotFactory *pSchChartDocShellFactory;  // Namensaufbau zwingend!!

    SchModuleDummy(ResMgr    *pInResMgr,
                   BOOL      bInDummy,
                   SotFactory *pObjFact) :
        SfxModule(pInResMgr, bInDummy, (SfxObjectFactory*) pObjFact, NULL),
        pSchChartDocShellFactory(pObjFact)
    {
    }

    virtual SfxModule *Load ();

    static const SvGlobalName GetID(USHORT nFileFormat);
    static USHORT HasID (const SvGlobalName& rID);

};

#ifndef _SCH_DLL                      // Das define muss im Draw gesetzt werden
#define SCH_MOD() ( *(SchModuleDummy**) GetAppData(BF_SHL_SCH) )
#endif

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
