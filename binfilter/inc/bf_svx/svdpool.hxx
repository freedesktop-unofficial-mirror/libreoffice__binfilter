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

#ifndef _SVDPOOL_HXX
#define _SVDPOOL_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svx/xpool.hxx>

#include <bf_svx/svddef.hxx>
namespace binfilter {

class XLineAttrSetItem;
class XFillAttrSetItem;
class XTextAttrSetItem;
class SdrShadowSetItem;
class SdrOutlinerSetItem;
class SdrMiscSetItem;

////////////////////////////////////////////////////////////////////////////////////////////////////

class SdrItemPool: public XOutdevItemPool {
private:
    void Ctor(SfxItemPool* pMaster, USHORT nAttrStart, USHORT nAttrEnd);
public:
    // Kontstruktion des Pools als MasterPool
    SdrItemPool(USHORT nAttrStart=SDRATTR_START, USHORT nAttrEnd=SDRATTR_END,
        bool bLoadRefCounts = TRUE);

    // Damit meine SetItems mit dem MasterPool konstruiert werden koennen.
    // Der SdrItemPool wird dabei automatisch als Secondary an den
    // uebergebenen MasterPool bzw. an's Ende einer bestehenden Pool-Kette
    // angehaengt.
    SdrItemPool(SfxItemPool* pMaster, USHORT nAttrStart=SDRATTR_START, USHORT nAttrEnd=SDRATTR_END,
        bool bLoadRefCounts = TRUE);

    SdrItemPool(const SdrItemPool& rPool);
    virtual ~SdrItemPool();
    virtual SfxItemPool* Clone() const;

    // liefert nur einen String, wenn die DLL mit DBG_UTIL uebersetzt ist
};

////////////////////////////////////////////////////////////////////////////////////////////////////

}//end of namespace binfilter
#endif // _SVDPOOL_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
