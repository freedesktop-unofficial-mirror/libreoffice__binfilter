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
#ifndef _SW_HF_EAT_SPACINGITEM_HXX
#define _SW_HF_EAT_SPACINGITEM_HXX

#include <bf_svtools/bf_solar.h>


#include <bf_svtools/eitem.hxx>
#include <format.hxx>
class IntlWrapper;
namespace binfilter {



class SwHeaderAndFooterEatSpacingItem : public SfxBoolItem
{
public:
    SwHeaderAndFooterEatSpacingItem( USHORT nId = RES_HEADER_FOOTER_EAT_SPACING,
                                     BOOL bPrt = FALSE ) : SfxBoolItem( nId, bPrt ) {}

    // "pure virtual Methoden" vom SfxPoolItem
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT) const;
    virtual SvStream&       Store(SvStream &rStream, USHORT) const { return rStream; }
    virtual SfxItemPresentation GetPresentation(
                SfxItemPresentation     /* ePres */,
                SfxMapUnit              /* eCoreMetric */,
                SfxMapUnit              /* ePresMetric */,
                String&                 /* rText */,
                const ::IntlWrapper*    /* pIntl */ = 0
            ) const
            {   return SFX_ITEM_PRESENTATION_NONE; }

    virtual USHORT           GetVersion( USHORT nFFVer ) const;
};

inline const SwHeaderAndFooterEatSpacingItem &SwAttrSet::GetHeaderAndFooterEatSpacing(BOOL bInP) const
    { return (const SwHeaderAndFooterEatSpacingItem&)Get( RES_HEADER_FOOTER_EAT_SPACING,bInP); }

inline const SwHeaderAndFooterEatSpacingItem &SwFmt::GetHeaderAndFooterEatSpacing(BOOL bInP) const
    { return aSet.GetHeaderAndFooterEatSpacing(bInP); }

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
