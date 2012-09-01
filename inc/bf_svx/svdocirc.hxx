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

#ifndef _SVDOCIRC_HXX
#define _SVDOCIRC_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svx/svdorect.hxx>
namespace binfilter {

//************************************************************
//   Vorausdeklarationen
//************************************************************

class SdrCircSetItem;

//************************************************************
//   Hilfsklasse SdrCircObjGeoData
//************************************************************

class SdrCircObjGeoData : public SdrRectObjGeoData
{
public:
    long                        nStartWink;
    long                        nEndWink;
};

//************************************************************
//   SdrCircObj
//************************************************************

class SdrCircObj : public SdrRectObj
{
protected:
    SdrObjKind                  eKind;
    long                        nStartWink;
    long                        nEndWink;
    Point                       aPnt1;
    Point                       aPnt2;

private:
    XPolygon ImpCalcXPoly(const Rectangle& rRect1, long nStart, long nEnd, bool bContour=FALSE) const;
    void ImpSetAttrToCircInfo(); // Werte vom Pool kopieren
    void ImpSetCircInfoToAttr(); // Werte in den Pool kopieren

    // Liefert TRUE, wenn das Painten ein XPolygon erfordert.
    bool PaintNeedsXPoly() const;
    virtual void RecalcXPoly();

protected:
    virtual void SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType);
    virtual void ForceDefaultAttr();

public:
    TYPEINFO();
    SdrCircObj(SdrObjKind eNewKind); // Circ, CArc, Sect oder CCut
    SdrCircObj(SdrObjKind eNewKind, const Rectangle& rRect);

    // 0=0.00Deg=3h 9000=90.00Deg=12h 18000=180.00Deg=9h 27000=270.00Deg=6h
    // Der Verlauf des Kreises von StartWink nach EndWink ist immer entgegen
    // dem Uhrzeigersinn.
    // Wenn nNewStartWink==nNewEndWink hat der Kreisbogen einen Verlaufswinkel
    // von 0 Grad. Bei nNewStartWink+36000==nNewEndWink ist der Verlaufswinkel
    // 360.00 Grad.
    SdrCircObj(SdrObjKind eNewKind, const Rectangle& rRect, long nNewStartWink, long nNewEndWink);
    virtual ~SdrCircObj();

    virtual UINT16 GetObjIdentifier() const;
    virtual void RecalcBoundRect();
    virtual void TakeUnrotatedSnapRect(Rectangle& rRect) const;
    virtual bool Paint(ExtOutputDevice& rOut, const SdrPaintInfoRec& rInfoRec) const;


    virtual void operator=(const SdrObject& rObj);
    virtual void RecalcSnapRect();
    virtual void NbcSetSnapRect(const Rectangle& rRect);
    virtual void TakeXorPoly(XPolyPolygon& rXPoly, bool bDetail) const;
    using SdrObject::TakeContour;
    virtual void TakeContour(XPolyPolygon& rXPoly) const;




    virtual void NbcMove(const Size& aSiz);
    virtual void NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact);
    virtual void NbcShear (const Point& rRef, double tn, bool bVShear);
    virtual SdrObject* DoConvertToPolyObj(BOOL bBezier) const;

public:
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

    long GetStartWink() const { return nStartWink; }
    long GetEndWink() const { return nEndWink; }
    virtual void NbcSetStyleSheet(SfxStyleSheet* pNewStyleSheet, bool bDontRemoveHardAttr);

    // ItemSet access
    virtual SfxItemSet* CreateNewItemSet(SfxItemPool& rPool);

    // private support routines for ItemSet access. NULL pointer means clear item.
    virtual void ItemSetChanged(const SfxItemSet& rSet);
};

}//end of namespace binfilter
#endif //_SVDOCIRC_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
