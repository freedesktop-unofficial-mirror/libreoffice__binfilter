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
#ifndef _SVX_SHADITEM_HXX
#define _SVX_SHADITEM_HXX

#include <tools/color.hxx>
#include <bf_svtools/eitem.hxx>
#include <bf_svx/svxenum.hxx>
#include <bf_svx/svxids.hrc>

namespace rtl
{
    class OUString;
}
namespace binfilter {

// class SvxShadowItem ---------------------------------------------------

/*  [Beschreibung]

    Dieses Item beschreibt ein Schattenattribut (Farbe, Breite, Lage).
*/

#define SHADOW_TOP      ((USHORT)0)
#define SHADOW_BOTTOM   ((USHORT)1)
#define SHADOW_LEFT     ((USHORT)2)
#define SHADOW_RIGHT    ((USHORT)3)

class SvxShadowItem : public SfxEnumItemInterface
{
    Color               aShadowColor;
    USHORT              nWidth;
    SvxShadowLocation   eLocation;
public:
    TYPEINFO();

    SvxShadowItem( const USHORT nId = ITEMID_SHADOW,
                 const Color *pColor = 0, const USHORT nWidth = 100 /*5pt*/,
                 const SvxShadowLocation eLoc = SVX_SHADOW_NONE );

    inline SvxShadowItem& operator=( const SvxShadowItem& rFmtShadow );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int              operator==( const SfxPoolItem& ) const;
    virtual bool             QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual bool             PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );


    virtual SfxPoolItem*     Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*     Create(SvStream &, USHORT) const;
    virtual SvStream&        Store(SvStream &rStream, USHORT) const { return rStream; }

    const Color& GetColor() const { return aShadowColor;}
    void SetColor( const Color &rNew ) { aShadowColor = rNew; }

    USHORT GetWidth() const { return nWidth; }
    SvxShadowLocation GetLocation() const { return eLocation; }

    void SetWidth( USHORT nNew ) { nWidth = nNew; }
    void SetLocation( SvxShadowLocation eNew ) { eLocation = eNew; }

        //Breite des Schattens auf der jeweiligen Seite berechnen.
    USHORT CalcShadowSpace( USHORT nShadow ) const;

    virtual USHORT          GetValueCount() const   { return 0; }
    virtual USHORT          GetEnumValue() const    { return 0; }
    virtual void            SetEnumValue( USHORT /* nNewVal */ )  {}
};

inline SvxShadowItem &SvxShadowItem::operator=( const SvxShadowItem& rFmtShadow )
{
    aShadowColor = rFmtShadow.aShadowColor;
    nWidth = rFmtShadow.GetWidth();
    eLocation = rFmtShadow.GetLocation();
    return *this;
}

}//end of namespace binfilter
#endif // #ifndef _SVX_SHADITEM_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
