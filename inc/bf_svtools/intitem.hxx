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

#ifndef _SFXINTITEM_HXX
#define _SFXINTITEM_HXX

#include <bf_svtools/bf_solar.h>


#include <bf_svtools/cintitem.hxx>

namespace binfilter
{

//============================================================================
class  SfxByteItem: public CntByteItem
{
public:
    TYPEINFO();

    SfxByteItem(USHORT which = 0, BYTE nValue = 0):
        CntByteItem(which, nValue) {}

    virtual SfxPoolItem * Create(SvStream & rStream, USHORT) const;

    virtual SfxPoolItem * Clone(SfxItemPool * = 0) const;
};

//============================================================================
DBG_NAMEEX_VISIBILITY(SfxInt16Item, )

class  SfxInt16Item: public SfxPoolItem
{
    INT16 m_nValue;

public:
    TYPEINFO();

    SfxInt16Item(USHORT which = 0, INT16 nTheValue = 0):
        SfxPoolItem(which), m_nValue(nTheValue)
    { DBG_CTOR(SfxInt16Item, 0); }

    SfxInt16Item(USHORT nWhich, SvStream & rStream);

    SfxInt16Item(const SfxInt16Item & rItem):
        SfxPoolItem(rItem), m_nValue(rItem.m_nValue)
    { DBG_CTOR(SfxInt16Item, 0); }

    virtual ~SfxInt16Item();

    virtual int operator ==(const SfxPoolItem & rItem) const;

    using SfxPoolItem::Compare;
    virtual int Compare(const SfxPoolItem & rWith) const;

    virtual SfxItemPresentation GetPresentation(SfxItemPresentation,
                                                SfxMapUnit, SfxMapUnit,
                                                XubString & rText,
                                                const ::IntlWrapper * = 0)
        const;

    virtual bool QueryValue( ::com::sun::star::uno::Any& rVal,
                             BYTE nMemberId = 0 ) const;

    virtual bool PutValue( const ::com::sun::star::uno::Any& rVal,
                           BYTE nMemberId = 0 );

    virtual SfxPoolItem * Create(SvStream & rStream, USHORT) const;

    virtual SvStream & Store(SvStream & rStream, USHORT) const { return rStream; }

    virtual SfxPoolItem * Clone(SfxItemPool * = 0) const;

    virtual INT16 GetMin() const;

    virtual INT16 GetMax() const;

    virtual SfxFieldUnit GetUnit() const;

    INT16 GetValue() const { return m_nValue; }

    inline void SetValue(INT16 nTheValue);
};

inline void SfxInt16Item::SetValue(INT16 nTheValue)
{
    DBG_ASSERT(GetRefCount() == 0, "SfxInt16Item::SetValue(); Pooled item");
    m_nValue = nTheValue;
}

//============================================================================
class  SfxUInt16Item: public CntUInt16Item
{
public:
    TYPEINFO();

    SfxUInt16Item(USHORT which = 0, UINT16 nValue = 0):
        CntUInt16Item(which, nValue) {}

    SfxUInt16Item(USHORT which, SvStream & rStream):
        CntUInt16Item(which, rStream) {}

    virtual SfxPoolItem * Create(SvStream & rStream, USHORT) const;

    virtual SfxPoolItem * Clone(SfxItemPool * = 0) const;
};

//============================================================================
class  SfxInt32Item: public CntInt32Item
{
public:
    TYPEINFO();

    SfxInt32Item(USHORT which = 0, INT32 nValue = 0):
        CntInt32Item(which, nValue) {}

    SfxInt32Item(USHORT which, SvStream & rStream):
        CntInt32Item(which, rStream) {}

    virtual SfxPoolItem * Create(SvStream & rStream, USHORT) const;

    virtual SfxPoolItem * Clone(SfxItemPool * = 0) const;

};

//============================================================================
class  SfxUInt32Item: public CntUInt32Item
{
public:
    TYPEINFO();

    SfxUInt32Item(USHORT which = 0, UINT32 nValue = 0):
        CntUInt32Item(which, nValue) {}

    SfxUInt32Item(USHORT which, SvStream & rStream):
        CntUInt32Item(which, rStream) {}

    virtual SfxPoolItem * Create(SvStream & rStream, USHORT) const;

    virtual SfxPoolItem * Clone(SfxItemPool * = 0) const;
};

}

#endif // _SFXINTITEM_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
