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
#ifndef SMDLL_HXX
#define SMDLL_HXX

#include <bf_svtools/bf_solar.h>

#define SMDLL   1

#include <bf_starmath/smdll0.hxx>
#include <tools/resid.hxx>
#include <bf_sfx2/sfxdefs.hxx>
namespace binfilter {

class SmData;
class SfxMedium;
class SfxFilter;

class SmDLL
{
    static BOOL bInitialized;
public:
    SmDLL();
    ~SmDLL();

    static void Init();
    static void LibInit();
    static void Exit();
    static void LibExit();

    static ULONG DetectFilter( SfxMedium& rMedium, const SfxFilter **ppFilter,
                               SfxFilterFlags nMust, SfxFilterFlags nDont );
};

#ifdef SMDLL
class SmResId : public ResId
{
public:
    SmResId(USHORT nId) :
        ResId(nId, *SM_MOD()->GetResMgr())
    {
    }
};
#endif

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
