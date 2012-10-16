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

#ifndef _SVTOOLS_CENUMITM_HXX
#define _SVTOOLS_CENUMITM_HXX

#include <bf_svtools/bf_solar.h>

#include <tools/debug.hxx>

#include <bf_svtools/poolitem.hxx>

namespace binfilter {

//============================================================================
DBG_NAMEEX(SfxEnumItemInterface)

class  SfxEnumItemInterface: public SfxPoolItem
{
protected:
    SfxEnumItemInterface(USHORT which): SfxPoolItem(which) {}

    SfxEnumItemInterface(const SfxEnumItemInterface & rItem):
        SfxPoolItem(rItem) {}

public:
    TYPEINFO();

    virtual int operator ==(const SfxPoolItem & rItem) const;

    virtual SfxItemPresentation GetPresentation(SfxItemPresentation,
                                                SfxMapUnit, SfxMapUnit,
                                                XubString & rText,
                                                const ::IntlWrapper * = 0)
        const;

    virtual bool QueryValue(::com::sun::star::uno::Any & rVal, BYTE = 0) const;

    virtual bool PutValue(const ::com::sun::star::uno::Any & rVal, BYTE = 0);

    virtual USHORT GetValueCount() const = 0;

    virtual XubString GetValueTextByPos(USHORT nPos) const;

    virtual USHORT GetValueByPos(USHORT nPos) const;

    /// Return the position of some value within this enumeration.
    ///
    /// @descr  This method is implemented using GetValueCount() and
    /// GetValueByPos().  Derived classes may replace this with a more
    /// efficient implementation.
    ///
    /// @param nValue  Some value.
    ///
    /// @return  The position of nValue within this enumeration, or USHRT_MAX
    /// if not included.
    virtual USHORT GetPosByValue(USHORT nValue) const;

    virtual BOOL IsEnabled(USHORT nValue) const;

    virtual USHORT GetEnumValue() const = 0;

    virtual void SetEnumValue(USHORT nValue) = 0;

    virtual int HasBoolValue() const;

    virtual BOOL GetBoolValue() const;

    virtual void SetBoolValue(BOOL bValue);
};

//============================================================================
DBG_NAMEEX(CntEnumItem)

class  CntEnumItem: public SfxEnumItemInterface
{
    USHORT m_nValue;

protected:
    CntEnumItem(USHORT which = 0, USHORT nTheValue = 0):
        SfxEnumItemInterface(which), m_nValue(nTheValue) {}

    CntEnumItem(USHORT which, SvStream & rStream);

    CntEnumItem(const CntEnumItem & rItem):
        SfxEnumItemInterface(rItem), m_nValue(rItem.m_nValue) {}

public:
    TYPEINFO();

    virtual SvStream & Store(SvStream & rStream, USHORT) const { return rStream; }

    virtual USHORT GetEnumValue() const;

    virtual void SetEnumValue(USHORT nTheValue);

    USHORT GetValue() const { return m_nValue; }

    inline void SetValue(USHORT nTheValue);
};

inline void CntEnumItem::SetValue(USHORT nTheValue)
{
    DBG_ASSERT(GetRefCount() == 0, "CntEnumItem::SetValue(): Pooled item");
    m_nValue = nTheValue;
}

//============================================================================
DBG_NAMEEX(CntBoolItem)

class  CntBoolItem: public SfxPoolItem
{
    BOOL m_bValue;

public:
    TYPEINFO();

    CntBoolItem(USHORT which = 0, BOOL bTheValue = FALSE):
        SfxPoolItem(which), m_bValue(bTheValue) {}

    CntBoolItem(USHORT nWhich, SvStream & rStream);

    CntBoolItem(const CntBoolItem & rItem):
        SfxPoolItem(rItem), m_bValue(rItem.m_bValue) {}

    virtual int operator ==(const SfxPoolItem & rItem) const;

    using SfxPoolItem::Compare;
    virtual int Compare(const SfxPoolItem & rWith) const;

    virtual SfxItemPresentation GetPresentation(SfxItemPresentation,
                                                SfxMapUnit, SfxMapUnit,
                                                UniString & rText,
                                                const ::IntlWrapper * = 0)
        const;

    virtual bool QueryValue(::com::sun::star::uno::Any& rVal, BYTE = 0) const;

    virtual bool PutValue(const ::com::sun::star::uno::Any& rVal, BYTE = 0);

    virtual SfxPoolItem * Create(SvStream & rStream, USHORT) const;

    virtual SvStream & Store(SvStream & rStream, USHORT) const { return rStream; }

    virtual SfxPoolItem * Clone(SfxItemPool * = 0) const;

    virtual USHORT GetValueCount() const;

    virtual UniString GetValueTextByVal(BOOL bTheValue) const;

    BOOL GetValue() const { return m_bValue; }

    void SetValue(BOOL bTheValue) { m_bValue = bTheValue; }
};

}

#endif // _SVTOOLS_CENUMITM_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
