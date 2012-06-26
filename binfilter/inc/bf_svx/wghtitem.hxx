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
#ifndef _SVX_WGHTITEM_HXX
#define _SVX_WGHTITEM_HXX

#include <bf_svtools/bf_solar.h>

// include ---------------------------------------------------------------

#include <vcl/vclenum.hxx>
#include <bf_svtools/eitem.hxx>
#include <bf_svx/svxids.hrc>

namespace rtl
{
    class OUString;
}
namespace binfilter {
class SvXMLUnitConverter;

// class SvxWeightItem ---------------------------------------------------

/* [Beschreibung]

    Dieses Item beschreibt die Font-Staerke.
*/

class SvxWeightItem : public SfxEnumItem
{
public:
    TYPEINFO();

    SvxWeightItem(  const FontWeight eWght = WEIGHT_NORMAL,
                    const USHORT nId = ITEMID_WEIGHT );

    // "pure virtual Methoden" vom SfxPoolItem + SfxEnumItem

    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT) const;
    virtual SvStream&       Store(SvStream &rStream, USHORT) const { return rStream; }
    virtual USHORT          GetValueCount() const { return 0; } // DBG_BF_ASSERT

    virtual bool            QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual bool            PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

    virtual int             HasBoolValue() const { return sal_True; }  // DBG_BF_ASSERT
    virtual BOOL            GetBoolValue() const;

    inline SvxWeightItem& operator=(const SvxWeightItem& rWeight) {
            SetValue( rWeight.GetValue() );
            return *this;
        }

    // enum cast
    FontWeight              GetWeight() const
                                { return (FontWeight)GetValue(); }
    void                    SetWeight( FontWeight eNew )
                                { SetValue( (USHORT)eNew ); }
};

}//end of namespace binfilter
#endif // #ifndef _SVX_WGHTITEM_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
