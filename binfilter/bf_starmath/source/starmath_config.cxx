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

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <bf_svtools/itemset.hxx>
#include <bf_sfx2/sfxsids.hrc>
#include <bf_svtools/eitem.hxx>
#include <bf_svtools/itempool.hxx>
#include <bf_svtools/intitem.hxx>


#include "config.hxx"
#include "starmath.hrc"
namespace binfilter {

/////////////////////////////////////////////////////////////////

/*N*/ SmConfig::SmConfig()
/*N*/ {
/*N*/ }


/*N*/ SmConfig::~SmConfig()
/*N*/ {
/*N*/ }




/*N*/ void SmConfig::ConfigToItemSet(SfxItemSet &rSet) const
/*N*/ {
/*N*/   const SfxItemPool *pPool = rSet.GetPool();
/*N*/
/*N*/   rSet.Put(SfxUInt16Item(pPool->GetWhich(SID_PRINTSIZE),
/*N*/                            (UINT16) GetPrintSize()));
/*N*/   rSet.Put(SfxUInt16Item(pPool->GetWhich(SID_PRINTZOOM),
/*N*/                            (UINT16) GetPrintZoomFactor()));
/*N*/
/*N*/     rSet.Put(SfxBoolItem(pPool->GetWhich(SID_PRINTTITLE), IsPrintTitle()));
/*N*/     rSet.Put(SfxBoolItem(pPool->GetWhich(SID_PRINTTEXT),  IsPrintFormulaText()));
/*N*/     rSet.Put(SfxBoolItem(pPool->GetWhich(SID_PRINTFRAME), IsPrintFrame()));
/*N*/     rSet.Put(SfxBoolItem(pPool->GetWhich(SID_AUTOREDRAW), IsAutoRedraw()));
/*N*/     rSet.Put(SfxBoolItem(pPool->GetWhich(SID_NO_RIGHT_SPACES), IsIgnoreSpacesRight()));
/*N*/ }


/////////////////////////////////////////////////////////////////


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
