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
#ifndef _NOTXTFRM_HXX
#define _NOTXTFRM_HXX

#include <bf_svtools/bf_solar.h>

#include <cntfrm.hxx>
class OutputDevice;
class Bitmap;
namespace binfilter {

class SwNoTxtNode;

class SwBorderAttrs;

struct SwCrsrMoveState;

class SwNoTxtFrm: public SwCntntFrm
{
    friend void _FrmFinit();    //erase pErrorBmp and pReplaceBmp
    static Bitmap *pErrorBmp, *pReplaceBmp;

    short    nWeight;                   // "Wichtigkeit" der Grafik

    const Size& GetSize() const;

    void InitCtor();

    void Format ( const SwBorderAttrs *pAttrs = 0 );
    void PaintCntnt  ( OutputDevice*, const SwRect&, const SwRect& ) const;
    void PaintPicture( OutputDevice*, const SwRect& ) const;
protected:
    virtual void MakeAll();
public:
    SwNoTxtFrm( SwNoTxtNode * const );
    ~SwNoTxtFrm();

    virtual void Modify( SfxPoolItem*, SfxPoolItem* );
    virtual void Paint(const SwRect& ) const {} // DBG_BF_ASSERT
    virtual BOOL GetCharRect( SwRect &, const SwPosition&, SwCrsrMoveState* = 0) const { return TRUE; } // DBG_BF_ASSERT
    BOOL GetCrsrOfst(SwPosition*, Point&, const SwCrsrMoveState* = 0) const { return TRUE; } // DBG_BF_ASSERT

    const Size &GetGrfSize() const  { return GetSize(); }
    void GetGrfArea( SwRect &rRect, SwRect * = 0, BOOL bMirror = TRUE ) const;

    void StopAnimation( OutputDevice* = 0 ) const;

    // Routinen fuer den Grafik-Cache
    USHORT GetWeight() { return nWeight; }

    static const Bitmap& GetBitmap( BOOL bError );
};


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
