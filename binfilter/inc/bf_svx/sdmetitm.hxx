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
#ifndef _SDMETITM_HXX
#define _SDMETITM_HXX

#include <bf_svtools/intitem.hxx>
namespace binfilter {

//------------------------------------------------------------
// class SdrAngleItem
// Fuer alle Metriken. GetPresentation liefert dann bei
// Value=2500 z.B. ein "25mm".
//------------------------------------------------------------
class SdrMetricItem: public SfxInt32Item {
public:
    TYPEINFO();
    SdrMetricItem(): SfxInt32Item() {}
    SdrMetricItem(USHORT nId, INT32 nVal=0):  SfxInt32Item(nId,nVal) {}
    SdrMetricItem(USHORT nId, SvStream& rIn): SfxInt32Item(nId,rIn) {}
    virtual SfxPoolItem* Clone(SfxItemPool* pPool=NULL) const;
    virtual SfxPoolItem* Create(SvStream& rIn, USHORT nVer) const;


#ifdef SDR_ISPOOLABLE
    virtual int IsPoolable() const;
#endif
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
