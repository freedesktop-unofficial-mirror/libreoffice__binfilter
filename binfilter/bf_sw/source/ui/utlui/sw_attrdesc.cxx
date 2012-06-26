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

#include <fchrfmt.hxx>
#include <horiornt.hxx>
#include <fmtclds.hxx>
#include <hfspacingitem.hxx>
#include <paratr.hxx>
#include <pagedesc.hxx>
#include <attrdesc.hrc>

namespace binfilter {

TYPEINIT2(SwFmtCharFmt,SfxPoolItem,SwClient);

/*N*/ void SwPageDesc::GetPresentation(
/*N*/       SfxItemPresentation /*ePres*/,
/*N*/       SfxMapUnit /*eCoreMetric*/,
/*N*/       SfxMapUnit /*ePresMetric*/,
/*N*/       String &rText ) const
/*N*/ {
/*N*/   rText = GetName();
/*N*/ }


/*************************************************************************
|*    class     SwParaConnectBorderItem
*************************************************************************/

/*N*/ SfxItemPresentation SwParaConnectBorderItem::GetPresentation
/*N*/ (
/*N*/     SfxItemPresentation ePres,
/*N*/     SfxMapUnit          eCoreUnit,
/*N*/     SfxMapUnit          ePresUnit,
/*N*/     XubString&          rText,
/*N*/     const ::IntlWrapper*        pIntl
/*N*/ )   const
/*N*/ {
/*N*/     // no UI support available
/*N*/     return SfxBoolItem::GetPresentation( ePres, eCoreUnit, ePresUnit, rText, pIntl );
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
