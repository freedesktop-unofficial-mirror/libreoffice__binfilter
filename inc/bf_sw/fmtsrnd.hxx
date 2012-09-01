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
#ifndef _FMTSRND_HXX
#define _FMTSRND_HXX

#include <bf_svtools/bf_solar.h>

#include <format.hxx>
#include <bf_svtools/eitem.hxx>
class IntlWrapper;
namespace binfilter {



//SwFmtSurround, wie soll sich der ---------------
//  Dokumentinhalt unter dem Rahmen verhalten ---

enum SwSurround {
    SURROUND_BEGIN,
    SURROUND_NONE = SURROUND_BEGIN,
    SURROUND_THROUGHT,
    SURROUND_PARALLEL,
    SURROUND_IDEAL,
    SURROUND_LEFT,
    SURROUND_RIGHT,
    SURROUND_END
};

class SwFmtSurround: public SfxEnumItem
{
    BOOL    bAnchorOnly :1;
    BOOL    bContour    :1;
    BOOL    bOutside    :1;
public:
    SwFmtSurround( SwSurround eNew = SURROUND_PARALLEL );
    SwFmtSurround( const SwFmtSurround & );
    inline SwFmtSurround &operator=( const SwFmtSurround &rCpy );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT nVer) const;
    virtual SvStream&       Store(SvStream &rStream, USHORT) const { return rStream; }
    virtual USHORT          GetValueCount() const{DBG_BF_ASSERT(0, "STRIP"); return 0;}
    virtual USHORT          GetVersion( USHORT nFFVer ) const;
    virtual bool            QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual bool            PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );


    SwSurround GetSurround()const { return SwSurround( GetValue() ); }
    BOOL    IsAnchorOnly()  const { return bAnchorOnly; }
    BOOL    IsContour()     const { return bContour; }
    BOOL    IsOutside()     const { return bOutside; }
    void    SetSurround  ( SwSurround eNew ){ SfxEnumItem::SetValue( USHORT( eNew ) ); }
    void    SetAnchorOnly( BOOL bNew )      { bAnchorOnly = bNew; }
    void    SetContour( BOOL bNew )         { bContour = bNew; }
    void    SetOutside( BOOL bNew )         { bOutside = bNew; }
};

inline SwFmtSurround &SwFmtSurround::operator=( const SwFmtSurround &rCpy )
{
    bAnchorOnly = rCpy.IsAnchorOnly();
    bContour = rCpy.IsContour();
    bOutside = rCpy.IsOutside();
    SfxEnumItem::SetValue( rCpy.GetValue() );
    return *this;
}

inline const SwFmtSurround &SwAttrSet::GetSurround(BOOL bInP) const
    { return (const SwFmtSurround&)Get( RES_SURROUND,bInP); }

inline const SwFmtSurround &SwFmt::GetSurround(BOOL bInP) const
    { return aSet.GetSurround(bInP); }

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
