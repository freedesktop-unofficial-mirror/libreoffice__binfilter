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
#ifndef SW_TGRDITEM_HXX
#define SW_TGRDITEM_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svtools/poolitem.hxx>
#include <hintids.hxx>
#include <format.hxx>

class IntlWrapper;

namespace binfilter {

enum SwTextGrid { GRID_NONE, GRID_LINES_ONLY, GRID_LINES_CHARS };

class SwTextGridItem : public SfxPoolItem
{
    Color aColor;
    sal_uInt16 nLines;
    sal_uInt16 nBaseHeight, nRubyHeight;
    SwTextGrid eGridType;
    BOOL bRubyTextBelow;
    BOOL bPrintGrid;
    BOOL bDisplayGrid;

public:
    SwTextGridItem();
    virtual ~SwTextGridItem();

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool* pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT nVer) const;
    virtual SvStream&       Store(SvStream &rStream, USHORT) const { return rStream; }
    virtual USHORT          GetVersion( USHORT nFFVer ) const;
    virtual bool            QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual bool            PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

    SwTextGridItem&  operator=( const SwTextGridItem& );

    const Color& GetColor() const { return aColor; }
    void SetColor( const Color& rCol )  { aColor = rCol; }

    sal_uInt16 GetLines() const { return nLines; }
    void SetLines( sal_uInt16 nNew ) { nLines = nNew; }

    sal_uInt16 GetBaseHeight() const { return nBaseHeight; }
    void SetBaseHeight( sal_uInt16 nNew ) { nBaseHeight = nNew; }

    sal_uInt16 GetRubyHeight() const { return nRubyHeight; }
    void SetRubyHeight( sal_uInt16 nNew ) { nRubyHeight = nNew; }

    SwTextGrid GetGridType() const { return eGridType; }
    void SetGridType( SwTextGrid eNew ) { eGridType = eNew; }

    BOOL IsRubyTextBelow() const { return bRubyTextBelow; }
    BOOL GetRubyTextBelow() const { return bRubyTextBelow; }
    void SetRubyTextBelow( BOOL bNew ) { bRubyTextBelow = bNew; }

    BOOL IsPrintGrid() const { return bPrintGrid; }
    BOOL GetPrintGrid() const { return bPrintGrid; }
    void SetPrintGrid( BOOL bNew ) { bPrintGrid = bNew; }

    BOOL IsDisplayGrid() const { return bDisplayGrid; }
    BOOL GetDisplayGrid() const { return bDisplayGrid; }
    void SetDisplayGrid( BOOL bNew ) { bDisplayGrid = bNew; }
};

inline const SwTextGridItem &SwAttrSet::GetTextGrid(BOOL bInP) const
    {   return (const SwTextGridItem&)Get( RES_TEXTGRID, bInP ); }
inline const SwTextGridItem &SwFmt::GetTextGrid(BOOL bInP) const
    {   return (const SwTextGridItem&)aSet.Get( RES_TEXTGRID, bInP ); }

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
