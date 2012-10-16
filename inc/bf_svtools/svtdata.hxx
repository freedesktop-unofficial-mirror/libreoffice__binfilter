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

#ifndef _SVTOOLS_SVTDATA_HXX
#define _SVTOOLS_SVTDATA_HXX

#include <bf_svtools/bf_solar.h>
#include <com/sun/star/lang/Locale.hpp>
#include <tools/resid.hxx>

class ResMgr;

namespace binfilter
{

class SfxItemDesruptorList_Impl;
class SfxItemPool;

//============================================================================
class ImpSvtData
{
public:
    const SfxItemPool * pStoringPool;
    SfxItemDesruptorList_Impl * pItemDesruptList;

    ResMgr *        pResMgr;
private:
    ImpSvtData():
        pStoringPool(0), pItemDesruptList(0), pResMgr(0)
    {}

    ~ImpSvtData();

public:
    ResMgr * GetResMgr(const ::com::sun::star::lang::Locale aLocale);
    ResMgr * GetResMgr(); // VCL dependant, only available in SVT, not in SVL!

    static ImpSvtData & GetSvtData();
};

class SvtResId: public ResId
{
public:
    SvtResId(USHORT nId, const ::com::sun::star::lang::Locale aLocale):
        ResId(nId, *ImpSvtData::GetSvtData().GetResMgr(aLocale)) {}

    SvtResId(USHORT nId): ResId(nId, *ImpSvtData::GetSvtData().GetResMgr()) {}
     // VCL dependant, only available in SVT, not in SVL!
};

#define SvpResId SvtResId

}

#endif //  _SVTOOLS_SVTDATA_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
