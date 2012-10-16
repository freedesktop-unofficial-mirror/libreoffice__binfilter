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
#ifndef _FMTFSIZE_HXX
#define _FMTFSIZE_HXX

#include <bf_svtools/bf_solar.h>

#include <tools/gen.hxx>
#include <swtypes.hxx>
#include <format.hxx>

class IntlWrapper;

namespace binfilter {

//Die Framesize ---------------------------------

enum SwFrmSize
{
    ATT_VAR_SIZE,       //Frm ist in der Var-Richtung variabel
    ATT_FIX_SIZE,       //Frm ist in der Var-Richtung unbeweglich
    ATT_MIN_SIZE        //Der Wert in der Var-Richtung beschreibt eine
                        //Minimalgroesse, die nicht unter- wohl aber
                        //ueberschritten werden kann.
};

class SwFmtFrmSize: public SfxPoolItem
{
    Size      aSize;
    SwFrmSize eFrmSize;
    BYTE      nWidthPercent;    //Fuer Tabellen kann die Breite in Prozent
    BYTE      nHeightPercent;   //angegeben sein.
                                //Fuer Rahmen koennen Hoehe und/oder Breite
                                //in Prozent angegeben sein. Wenn nur eine
                                //der Angaben in Prozent angeben ist, kann
                                //durch den ausgezeichneten Wert 0xFF in der
                                //anderen Prozentangabe bestimmt werden, das
                                //sich diese Richtung proportional zur anderen
                                //verhaelt. Basis fuer die Umrechnung sind fuer
                                //diesen Fall die Angaben in der Size.
                                //Die Prozentwerte beziehen sich immer auf die
                                //Umgebung in der das Objekt steht (PrtArea)
                                //Auf die Bildschirmbreite abzueglich Raender
                                //in der BrowseView wenn die Umgebung die Seite
                                //ist.
public:
    SwFmtFrmSize( SwFrmSize eSize = ATT_VAR_SIZE,
                  SwTwips nWidth = 0, SwTwips nHeight = 0 );
    SwFmtFrmSize& operator=( const SwFmtFrmSize& rCpy );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxPoolItem*    Create(SvStream &, USHORT nVer) const;
    virtual SvStream&       Store(SvStream &rStream, USHORT) const { return rStream; }
    virtual bool            QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual bool            PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );
    virtual USHORT          GetVersion( USHORT nFFVer ) const;

    SwFrmSize GetSizeType() const { return eFrmSize; }
    void SetSizeType( SwFrmSize eSize ) { eFrmSize = eSize; }

    const Size& GetSize() const { return aSize; }
          void  SetSize( const Size &rNew ) { aSize = rNew; }

    SwTwips GetHeight() const { return aSize.Height(); }
    SwTwips GetWidth()  const { return aSize.Width();  }
    void    SetHeight( const SwTwips nNew ) { aSize.Height() = nNew; }
    void    SetWidth ( const SwTwips nNew ) { aSize.Width()  = nNew; }

    BYTE    GetHeightPercent() const{ return nHeightPercent; }
    BYTE    GetWidthPercent() const { return nWidthPercent;  }
    void    SetHeightPercent( BYTE n ) { nHeightPercent = n; }
    void    SetWidthPercent ( BYTE n ) { nWidthPercent  = n; }

    Size    GetSizeConvertedFromSw31( const SvxLRSpaceItem *pLRSpace,
                                      const SvxULSpaceItem *pULSpace ) const;
};

inline const SwFmtFrmSize &SwAttrSet::GetFrmSize(BOOL bInP) const
    { return (const SwFmtFrmSize&)Get( RES_FRM_SIZE,bInP); }

inline const SwFmtFrmSize &SwFmt::GetFrmSize(BOOL bInP) const
    { return aSet.GetFrmSize(bInP); }

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
