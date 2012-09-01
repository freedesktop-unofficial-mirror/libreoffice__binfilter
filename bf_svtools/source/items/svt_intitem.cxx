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

#include <bf_svtools/intitem.hxx>

#include <com/sun/star/uno/Any.hxx>

#include <tools/bigint.hxx>
#include <tools/stream.hxx>

#include <bf_svtools/metitem.hxx>

namespace binfilter
{

CntByteItem::~CntByteItem()
{
    DBG_DTOR(CntByteItem, 0);
}

CntUInt16Item::~CntUInt16Item()
{
    DBG_DTOR(CntUInt16Item, 0);
}

CntInt32Item::~CntInt32Item()
{
    DBG_DTOR(CntInt32Item, 0);
}

CntUInt32Item::~CntUInt32Item() { DBG_DTOR(CntUInt32Item, 0); }

SfxPoolItem * SfxByteItem::Clone(SfxItemPool *) const
{ return new SfxByteItem(*this); }

SfxInt16Item::~SfxInt16Item() { DBG_DTOR(SfxInt16Item, 0); }

SfxPoolItem * SfxUInt16Item::Create(SvStream & rStream, USHORT) const
{ return new SfxUInt16Item(Which(), rStream); }

SfxPoolItem * SfxUInt16Item::Clone(SfxItemPool *) const
{ return new SfxUInt16Item(*this); }

SfxPoolItem * SfxInt32Item::Create(SvStream & rStream, USHORT) const
{ return new SfxInt32Item(Which(), rStream); }

SfxPoolItem * SfxInt32Item::Clone(SfxItemPool * ) const
{ return new SfxInt32Item(*this); }

SfxPoolItem * SfxUInt32Item::Create(SvStream & rStream, USHORT) const
{ return new SfxUInt32Item(Which(), rStream); }

SfxPoolItem * SfxUInt32Item::Clone(SfxItemPool * ) const
{ return new SfxUInt32Item(*this); }

//============================================================================
//
//  class SfxByteItem
//
//============================================================================

TYPEINIT1_AUTOFACTORY(SfxByteItem, CntByteItem);

//============================================================================
// virtual
SfxPoolItem * SfxByteItem::Create(SvStream & rStream, USHORT) const
{
    short nValue = 0;
    rStream >> nValue;
    return new SfxByteItem(Which(), BYTE(nValue));
}

//============================================================================
//
//  class SfxInt16Item
//
//============================================================================

DBG_NAME(SfxInt16Item);

//============================================================================
TYPEINIT1_AUTOFACTORY(SfxInt16Item, SfxPoolItem);

//============================================================================
SfxInt16Item::SfxInt16Item(USHORT which, SvStream & rStream):
    SfxPoolItem(which)
{
    DBG_CTOR(SfxInt16Item, 0);
    short nTheValue = 0;
    rStream >> nTheValue;
    m_nValue = nTheValue;
}

//============================================================================
// virtual
int SfxInt16Item::operator ==(const SfxPoolItem & rItem) const
{
    DBG_CHKTHIS(SfxInt16Item, 0);
    DBG_ASSERT(SfxPoolItem::operator ==(rItem), "unequal type");
    return m_nValue == (static_cast< const SfxInt16Item * >(&rItem))->
                        m_nValue;
}

//============================================================================
// virtual
int SfxInt16Item::Compare(const SfxPoolItem & rWith) const
{
    DBG_CHKTHIS(SfxInt16Item, 0);
    DBG_ASSERT(SfxPoolItem::operator ==(rWith), "unequal type");
    return (static_cast< const SfxInt16Item * >(&rWith))->m_nValue
             < m_nValue ?
            -1 :
           (static_cast< const SfxInt16Item * >(&rWith))->m_nValue
             == m_nValue ?
            0 : 1;
}

//============================================================================
// virtual
SfxItemPresentation SfxInt16Item::GetPresentation(SfxItemPresentation,
                                                  SfxMapUnit, SfxMapUnit,
                                                  XubString & rText,
                                                  const ::IntlWrapper *) const
{
    DBG_CHKTHIS(SfxInt16Item, 0);
    rText = UniString::CreateFromInt32(m_nValue);
    return SFX_ITEM_PRESENTATION_NAMELESS;
}


//============================================================================
// virtual
bool SfxInt16Item::QueryValue(::com::sun::star::uno::Any& rVal, BYTE) const
{
    sal_Int16 nValue = m_nValue;
    rVal <<= nValue;
    return true;
}

//============================================================================
// virtual
bool SfxInt16Item::PutValue(const com::sun::star::uno::Any& rVal, BYTE )
{
    sal_Int16 nValue = sal_Int16();
    if (rVal >>= nValue)
    {
        m_nValue = nValue;
        return true;
    }

    OSL_FAIL( "SfxInt16Item::PutValue - Wrong type!" );
    return false;
}

//============================================================================
// virtual
SfxPoolItem * SfxInt16Item::Create(SvStream & rStream, USHORT) const
{
    DBG_CHKTHIS(SfxInt16Item, 0);
    return new SfxInt16Item(Which(), rStream);
}

//============================================================================
SfxPoolItem * SfxInt16Item::Clone(SfxItemPool *) const
{
    DBG_CHKTHIS(SfxInt16Item, 0);
    return new SfxInt16Item(*this);
}

//============================================================================
INT16 SfxInt16Item::GetMin() const
{
    DBG_CHKTHIS(SfxInt16Item, 0);
    return -32768;
}

//============================================================================
INT16 SfxInt16Item::GetMax() const
{
    DBG_CHKTHIS(SfxInt16Item, 0);
    return 32767;
}

//============================================================================
SfxFieldUnit SfxInt16Item::GetUnit() const
{
    DBG_CHKTHIS(SfxInt16Item, 0);
    return SFX_FUNIT_NONE;
}

//============================================================================
//
//  class SfxUInt16Item
//
//============================================================================

TYPEINIT1_AUTOFACTORY(SfxUInt16Item, CntUInt16Item);


//============================================================================
//
//  class SfxInt32Item
//
//============================================================================

TYPEINIT1_AUTOFACTORY(SfxInt32Item, CntInt32Item);


//============================================================================
//
//  class SfxUInt32Item
//
//============================================================================

TYPEINIT1_AUTOFACTORY(SfxUInt32Item, CntUInt32Item);


//============================================================================
//
//  class SfxMetricItem
//
//============================================================================

DBG_NAME(SfxMetricItem);

//============================================================================
TYPEINIT1_AUTOFACTORY(SfxMetricItem, SfxInt32Item);

//============================================================================
SfxMetricItem::SfxMetricItem(USHORT which, UINT32 nValue):
    SfxInt32Item(which, nValue)
{
    DBG_CTOR(SfxMetricItem, 0);
}

//============================================================================
SfxMetricItem::SfxMetricItem(USHORT which, SvStream & rStream):
    SfxInt32Item(which, rStream)
{
    DBG_CTOR(SfxMetricItem, 0);
}

//============================================================================
SfxMetricItem::SfxMetricItem(const SfxMetricItem & rItem):
    SfxInt32Item(rItem)
{
    DBG_CTOR(SfxMetricItem, 0);
}

//============================================================================
// virtual
int SfxMetricItem::ScaleMetrics(long nMult, long nDiv)
{
    BigInt aTheValue(GetValue());
    aTheValue *= nMult;
    aTheValue += nDiv / 2;
    aTheValue /= nDiv;
    SetValue(aTheValue);
    return 1;
}

//============================================================================
// virtual
int SfxMetricItem::HasMetrics() const
{
    return 1;
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
