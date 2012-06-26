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
#ifndef _SVX_UDLNITEM_HXX
#define _SVX_UDLNITEM_HXX

#include <bf_svtools/bf_solar.h>

// include ---------------------------------------------------------------

#include <bf_svtools/eitem.hxx>
#include <bf_svx/svxids.hrc>
#include <vcl/vclenum.hxx>
#include <tools/color.hxx>

namespace rtl
{
    class OUString;
}
namespace binfilter {
class SvXMLUnitConverter;

// class SvxUnderlineItem ------------------------------------------------

/*  [Beschreibung]

    Dieses Item beschreibt, ob und wie unterstrichen ist.
*/

class SvxUnderlineItem : public SfxEnumItem
{
    Color mColor;
public:
    TYPEINFO();

    SvxUnderlineItem( const FontUnderline eSt = UNDERLINE_NONE,
                      const USHORT nId = ITEMID_UNDERLINE );

    // "pure virtual Methoden" vom SfxPoolItem

    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT) const;
    virtual SvStream&       Store(SvStream &rStream, USHORT) const { return rStream; }
    virtual USHORT          GetValueCount() const;

    virtual bool         QueryValue( ::com::sun::star::uno::Any& rVal,
                                        BYTE nMemberId = 0 ) const;
    virtual bool         PutValue( const ::com::sun::star::uno::Any& rVal,
                                        BYTE nMemberId = 0 );

    // MS VC4.0 kommt durcheinander
    void                    SetValue( USHORT nNewVal )
                                {SfxEnumItem::SetValue(nNewVal); }
    virtual int             HasBoolValue() const { return sal_True; } // DBG_BF_ASSERT
    virtual BOOL            GetBoolValue() const;

    virtual int              operator==( const SfxPoolItem& ) const;

    inline SvxUnderlineItem& operator=(const SvxUnderlineItem& rUnderline)
        {
            SetValue( rUnderline.GetValue() );
            SetColor( rUnderline.GetColor() );
            return *this;
        }

    // enum cast
    FontUnderline           GetUnderline() const
                                { return (FontUnderline)GetValue(); }
    void                    SetUnderline ( FontUnderline eNew )
                                { SetValue((USHORT) eNew); }

    const Color&            GetColor() const                { return mColor; }
    void                    SetColor( const Color& rCol )   { mColor = rCol; }
};

}//end of namespace binfilter
#endif // #ifndef _SVX_UDLNITEM_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
