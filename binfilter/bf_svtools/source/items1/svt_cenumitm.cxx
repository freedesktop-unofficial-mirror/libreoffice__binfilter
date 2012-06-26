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

#include <bf_svtools/cenumitm.hxx>

#include <whassert.hxx>

#include <comphelper/extract.hxx>

namespace binfilter
{

//============================================================================
//
//  class SfxEnumItemInterface
//
//============================================================================

//============================================================================
TYPEINIT1(SfxEnumItemInterface, SfxPoolItem)

//============================================================================
// virtual
int SfxEnumItemInterface::operator ==(const SfxPoolItem & rItem) const
{
    SFX_ASSERT(SfxPoolItem::operator ==(rItem), Which(), "unequal type");
    return GetEnumValue()
               == static_cast< const SfxEnumItemInterface * >(&rItem)->
                      GetEnumValue();
}

//============================================================================
// virtual
SfxItemPresentation
SfxEnumItemInterface::GetPresentation(SfxItemPresentation, SfxMapUnit,
                                      SfxMapUnit, XubString & rText,
                                      const ::IntlWrapper *) const
{
    rText = XubString::CreateFromInt32(GetEnumValue());
    return SFX_ITEM_PRESENTATION_NAMELESS;
}

//============================================================================
// virtual
bool SfxEnumItemInterface::QueryValue(::com::sun::star::uno::Any& rVal, BYTE)
    const
{
    rVal <<= sal_Int32(GetEnumValue());
    return true;
}

//============================================================================
// virtual
bool SfxEnumItemInterface::PutValue(const ::com::sun::star::uno::Any& rVal,
                                    BYTE)
{
    sal_Int32 nTheValue = 0;

    if ( ::cppu::enum2int( nTheValue, rVal ) )
    {
        SetEnumValue(USHORT(nTheValue));
        return true;
    }
    OSL_FAIL("SfxEnumItemInterface::PutValue(): Wrong type");
    return false;
}

//============================================================================
XubString SfxEnumItemInterface::GetValueTextByPos(USHORT) const
{
    DBG_WARNING("SfxEnumItemInterface::GetValueTextByPos(): Pure virtual");
    return XubString();
}

//============================================================================
// virtual
USHORT SfxEnumItemInterface::GetValueByPos(USHORT nPos) const
{
    return nPos;
}

//============================================================================
// virtual
USHORT SfxEnumItemInterface::GetPosByValue(USHORT nValue) const
{
    USHORT nCount = GetValueCount();
    for (USHORT i = 0; i < nCount; ++i)
        if (GetValueByPos(i) == nValue)
            return i;
    return USHRT_MAX;
}

BOOL SfxEnumItemInterface::IsEnabled(USHORT) const
{
    return TRUE;
}

//============================================================================
// virtual
int SfxEnumItemInterface::HasBoolValue() const
{
    return false;
}

//============================================================================
// virtual
BOOL SfxEnumItemInterface::GetBoolValue() const
{
    return false;
}

//============================================================================
// virtual
void SfxEnumItemInterface::SetBoolValue(BOOL)
{}

//============================================================================
//
//  class CntEnumItem
//
//============================================================================

//============================================================================
CntEnumItem::CntEnumItem(USHORT which, SvStream & rStream):
    SfxEnumItemInterface(which)
{
    m_nValue = 0;
    rStream >> m_nValue;
}

//============================================================================
TYPEINIT1(CntEnumItem, SfxEnumItemInterface)

//============================================================================
// virtual
USHORT CntEnumItem::GetEnumValue() const
{
    return GetValue();
}

//============================================================================
// virtual
void CntEnumItem::SetEnumValue(USHORT nTheValue)
{
    SetValue(nTheValue);
}

//============================================================================
//
//  class CntBoolItem
//
//============================================================================

//============================================================================
TYPEINIT1_AUTOFACTORY(CntBoolItem, SfxPoolItem)

//============================================================================
CntBoolItem::CntBoolItem(USHORT which, SvStream & rStream):
    SfxPoolItem(which)
{
    m_bValue = false;
    rStream >> m_bValue;
}

//============================================================================
// virtual
int CntBoolItem::operator ==(const SfxPoolItem & rItem) const
{
    DBG_ASSERT(rItem.ISA(CntBoolItem),
               "CntBoolItem::operator ==(): Bad type");
    return m_bValue == static_cast< CntBoolItem const * >(&rItem)->m_bValue;
}

//============================================================================
// virtual
int CntBoolItem::Compare(const SfxPoolItem & rWith) const
{
    DBG_ASSERT(rWith.ISA(CntBoolItem), "CntBoolItem::Compare(): Bad type");
    return m_bValue == static_cast< CntBoolItem const * >(&rWith)->m_bValue ?
               0 : m_bValue ? -1 : 1;
}

//============================================================================
// virtual
SfxItemPresentation CntBoolItem::GetPresentation(SfxItemPresentation,
                                                 SfxMapUnit, SfxMapUnit,
                                                 UniString & rText,
                                                 const ::IntlWrapper *) const
{
    rText = GetValueTextByVal(m_bValue);
    return SFX_ITEM_PRESENTATION_NAMELESS;
}

//============================================================================
// virtual
bool CntBoolItem::QueryValue(com::sun::star::uno::Any& rVal, BYTE) const
{
    rVal <<= sal_Bool(m_bValue);
    return true;
}

//============================================================================
// virtual
bool CntBoolItem::PutValue(const com::sun::star::uno::Any& rVal, BYTE)
{
    sal_Bool bTheValue = sal_Bool();
    if (rVal >>= bTheValue)
    {
        m_bValue = bTheValue;
        return true;
    }
    OSL_FAIL("CntBoolItem::PutValue(): Wrong type");
    return false;
}

//============================================================================
// virtual
SfxPoolItem * CntBoolItem::Create(SvStream & rStream, USHORT) const
{
    return new CntBoolItem(Which(), rStream);
}

//============================================================================
// virtual
SfxPoolItem * CntBoolItem::Clone(SfxItemPool *) const
{
    return new CntBoolItem(*this);
}

//============================================================================
// virtual
USHORT CntBoolItem::GetValueCount() const
{
    return 2;
}

//============================================================================
// virtual
UniString CntBoolItem::GetValueTextByVal(BOOL bTheValue) const
{
    return
        bTheValue ?
            UniString::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("TRUE")) :
            UniString::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("FALSE"));
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
