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

#include <com/sun/star/uno/Any.hxx>

#include <tools/stream.hxx>

#include <tools/bigint.hxx>

#include <bf_svtools/bintitem.hxx>

// STATIC DATA
namespace binfilter
{

DBG_NAME(SfxBigIntItem)

// RTTI
TYPEINIT1_AUTOFACTORY(SfxBigIntItem, SfxPoolItem);

// SfxBigIntItem

//============================================================================
SfxBigIntItem::SfxBigIntItem()
    : SfxPoolItem(0),
        aVal(0)
{
    DBG_CTOR(SfxBigIntItem, 0);
}

//============================================================================
SfxBigIntItem::SfxBigIntItem(USHORT which, SvStream &rStream)
    : SfxPoolItem(which)
{
    DBG_CTOR(SfxBigIntItem, 0);
    UniString sTmp = rStream.ReadUniOrByteString(rStream.GetStreamCharSet());
    BigInt aTmp(sTmp);
    aVal = aTmp;
}

//============================================================================
SfxBigIntItem::SfxBigIntItem(const SfxBigIntItem& rItem)
    : SfxPoolItem(rItem),
        aVal(rItem.aVal)
{
    DBG_CTOR(SfxBigIntItem, 0);
}

//============================================================================
SfxItemPresentation SfxBigIntItem::GetPresentation(
    SfxItemPresentation /*ePresentation*/,
    SfxMapUnit          /*eCoreMetric*/,
    SfxMapUnit          /*ePresentationMetric*/,
    XubString&           rText,
    const ::IntlWrapper * ) const
{
    DBG_CHKTHIS(SfxBigIntItem, 0);
    rText = aVal.GetString();
    return SFX_ITEM_PRESENTATION_NAMELESS;
}

//============================================================================
int SfxBigIntItem::operator==(const SfxPoolItem& rItem) const
{
    DBG_CHKTHIS(SfxBigIntItem, 0);
    DBG_ASSERT(SfxPoolItem::operator==(rItem), "unequal type");
    return ((SfxBigIntItem&)rItem).aVal == aVal;
}

//============================================================================
int SfxBigIntItem::Compare(const SfxPoolItem& rItem) const
{
    DBG_CHKTHIS(SfxBigIntItem, 0);
    DBG_ASSERT(SfxPoolItem::operator==(rItem), "unequal type");

    if (((const SfxBigIntItem&)rItem ).aVal < aVal )
        return -1;
    else if (((const SfxBigIntItem&)rItem ).aVal == aVal)
        return 0;
    else
        return 1;
}

//============================================================================
SfxPoolItem* SfxBigIntItem::Clone(SfxItemPool *) const
{
    DBG_CHKTHIS(SfxBigIntItem, 0);
    return new SfxBigIntItem(*this);
}

//============================================================================
SfxPoolItem* SfxBigIntItem::Create(SvStream &rStream, USHORT) const
{
    DBG_CHKTHIS(SfxBigIntItem, 0);
    return new SfxBigIntItem(Which(), rStream);
}

//============================================================================
SfxFieldUnit SfxBigIntItem::GetUnit() const
{
    DBG_CHKTHIS(SfxBigIntItem, 0);
    return SFX_FUNIT_NONE;
}

//============================================================================
// virtual
bool SfxBigIntItem::PutValue( const com::sun::star::uno::Any& rVal, BYTE )
{
    double aValue = 0.0;
    if ( rVal >>= aValue )
    {
        SetValue( aValue );
        return true;
    }

    OSL_FAIL( "SfxBigIntItem::PutValue - Wrong type!" );
    return false;
}

//============================================================================
// virtual
bool SfxBigIntItem::QueryValue( ::com::sun::star::uno::Any& rVal,   BYTE ) const
{
    double aValue = GetValue();
    rVal <<= aValue;
    return true;
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
