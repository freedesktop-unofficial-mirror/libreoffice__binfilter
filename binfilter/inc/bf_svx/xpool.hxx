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

#ifndef _XPOOL_HXX
#define _XPOOL_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svtools/itempool.hxx>
#include <bf_svx/xdef.hxx>
namespace binfilter {

/*************************************************************************
|*
|* Klassendeklaration
|*
\************************************************************************/

class XOutdevItemPool: public SfxItemPool
{
protected:
    SfxPoolItem**   ppPoolDefaults;
    SfxItemInfo*    pItemInfos;
/*    USHORT*         pVersion1Map;
    USHORT*         pVersion2Map;
    USHORT*         pVersion3Map;
    USHORT*         pVersion4Map;*/
    USHORT          nStart, nEnd;

private:
    void Ctor(SfxItemPool* pMaster, USHORT nAttrStart, USHORT nAttrEnd);

public:
    // Kontstruktion des Pools als MasterPool
    XOutdevItemPool(USHORT nAttrStart = XATTR_START,
                    USHORT nAttrEnd = XATTR_END,
                    bool bLoadRefCounts = TRUE);

    // Damit meine SetItems mit dem MasterPool konstruiert werden koennen.
    // Der SdrItemPool wird dabei automatisch als Secondary an den
    // uebergebenen MasterPool bzw. an's Ende einer bestehenden Pool-Kette
    // angehaengt.
    XOutdevItemPool(SfxItemPool* pMaster,
                    USHORT nAttrStart = XATTR_START,
                    USHORT nAttrEnd = XATTR_END,
                    bool bLoadRefCounts = TRUE);

    XOutdevItemPool(const XOutdevItemPool& rPool);

    virtual SfxItemPool* Clone() const;

    ~XOutdevItemPool();
};

}//end of namespace binfilter
#endif      // _XPOOL_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
