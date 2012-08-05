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

#include <unotools/intlwrapper.hxx>

#include <tools/stream.hxx>
#include <tools/debug.hxx>
#include <tools/datetime.hxx>

#include <bf_svtools/frqitem.hxx>

namespace binfilter
{

DBG_NAME( SfxFrequencyItem )

TYPEINIT1( SfxFrequencyItem, SfxPoolItem );

#define MAX_GOTO 32000

// -----------------------------------------------------------------------

SfxFrequencyItem::SfxFrequencyItem( USHORT which, FrequencyMode eMode, FrequencyTimeMode eTMode,
                                    USHORT nDI1, USHORT nDI2, USHORT nDI3, USHORT nTI1,
                                    const Time& rT1, const Time& rT2 ) :
    SfxPoolItem     ( which ),
    eFrqMode        ( eMode ),
    eFrqTimeMode    ( eTMode ),
    nDInterval1     ( nDI1 ),
    nDInterval2     ( nDI2 ),
    nDInterval3     ( nDI3 ),
    nTInterval1     ( nTI1 ),
    aTime1          ( rT1 ),
    aTime2          ( rT2 ),
    bMissingDate    ( FALSE ),
    aMissingDate    ( DateTime::EMPTY )
{
    DBG_CTOR( SfxFrequencyItem, 0 );
}

// -----------------------------------------------------------------------

SfxFrequencyItem::SfxFrequencyItem( const SfxFrequencyItem& rItem ) :
    SfxPoolItem     ( rItem ),
    eFrqMode        ( rItem.eFrqMode ),
    eFrqTimeMode    ( rItem.eFrqTimeMode ),
    nDInterval1     ( rItem.nDInterval1 ),
    nDInterval2     ( rItem.nDInterval2 ),
    nDInterval3     ( rItem.nDInterval3 ),
    nTInterval1     ( rItem.nTInterval1 ),
    aTime1          ( rItem.aTime1 ),
    aTime2          ( rItem.aTime2 ),
    bMissingDate    ( rItem.bMissingDate ),
    aMissingDate    ( rItem.aMissingDate )
{
    DBG_CTOR( SfxFrequencyItem, 0 );
}

// -----------------------------------------------------------------------

int SfxFrequencyItem::operator==( const SfxPoolItem& rItem ) const
{
    DBG_CHKTHIS( SfxFrequencyItem, 0 );
    DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal type" );

    return  ((SfxFrequencyItem&)rItem ).eFrqMode == eFrqMode &&
            ((SfxFrequencyItem&)rItem ).eFrqTimeMode == eFrqTimeMode &&
            ((SfxFrequencyItem&)rItem ).nDInterval1 == nDInterval1 &&
            ((SfxFrequencyItem&)rItem ).nDInterval2 == nDInterval2 &&
            ((SfxFrequencyItem&)rItem ).nDInterval3 == nDInterval3 &&
            ((SfxFrequencyItem&)rItem ).nTInterval1 == nTInterval1 &&
            ((SfxFrequencyItem&)rItem ).aTime1 == aTime1 &&
            ((SfxFrequencyItem&)rItem ).aTime2 == aTime2;
}

// -----------------------------------------------------------------------

int SfxFrequencyItem::Compare( const SfxPoolItem&
#ifdef DBG_UTIL
rItem
#endif
) const
{
    DBG_CHKTHIS( SfxFrequencyItem, 0 );
    DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal type" );

    return 1;
}

// -----------------------------------------------------------------------

SfxPoolItem* SfxFrequencyItem::Create( SvStream& rStream, USHORT ) const
{
    DBG_CHKTHIS(SfxFrequencyItem, 0);

    USHORT          _eFrqMode;
    USHORT          _eFrqTimeMode;
    USHORT          _nDInterval1;
    USHORT          _nDInterval2;
    USHORT          _nDInterval3;
    USHORT          _nTInterval1;
    long            _nTime1;
    long            _nTime2;

    rStream >> _eFrqMode;
    rStream >> _eFrqTimeMode;
    rStream >> _nDInterval1;
    rStream >> _nDInterval2;
    rStream >> _nDInterval3;
    rStream >> _nTInterval1;
    rStream >> _nTime1;
    rStream >> _nTime2;

    return new SfxFrequencyItem( Which(), (FrequencyMode)_eFrqMode,
        (FrequencyTimeMode) _eFrqTimeMode, _nDInterval1, _nDInterval2, _nDInterval3,
        _nTInterval1, Time(_nTime1), Time(_nTime2) );
}

SfxPoolItem* SfxFrequencyItem::Clone( SfxItemPool* ) const
{
    DBG_CHKTHIS( SfxFrequencyItem, 0 );
    return new SfxFrequencyItem( *this );
}

// -----------------------------------------------------------------------

SfxItemPresentation SfxFrequencyItem::GetPresentation
(
    SfxItemPresentation     /*ePresentation*/,
    SfxMapUnit              /*eCoreMetric*/,
    SfxMapUnit              /*ePresentationMetric*/,
    XubString&              rText,
    const ::IntlWrapper *
)   const
{
    DBG_CHKTHIS(SfxFrequencyItem, 0);
    rText.AssignAscii(RTL_CONSTASCII_STRINGPARAM("SNIY"));
    return SFX_ITEM_PRESENTATION_NAMELESS;
}

// -----------------------------------------------------------------------

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
