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

#ifndef _SVDOMEAS_HXX
#define _SVDOMEAS_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svx/svdotext.hxx>
namespace binfilter {

//************************************************************
//   Vorausdeklarationen
//************************************************************

class SdrMeasureSetItem;
class SdrOutliner;
struct ImpMeasureRec;
struct ImpMeasurePoly;

//************************************************************
//   SdrMeasureObj
//************************************************************

class SdrMeasureObj : public SdrTextObj
{
    friend class                SdrMeasureField;

protected:
    Point                       aPt1;
    Point                       aPt2;
    bool                    bTextDirty;

protected:
    virtual void SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType);
    virtual void ForceDefaultAttr();
    void ImpTakeAttr(ImpMeasureRec& rRec) const;
    void ImpCalcGeometrics(const ImpMeasureRec& rRec, ImpMeasurePoly& rPol) const;
    void ImpCalcXPoly(const ImpMeasurePoly& rPol, XPolyPolygon& rXPP) const;
    void SetTextDirty() { bTextDirty=TRUE; SetTextSizeDirty(); if (!bBoundRectDirty) { bBoundRectDirty=TRUE; SetRectsDirty(TRUE); } }
    void UndirtyText() const;


public:
    TYPEINFO();
    SdrMeasureObj();
    SdrMeasureObj(const Point& rPt1, const Point& rPt2);
    virtual ~SdrMeasureObj();
    using SdrTextObj::operator=;

    virtual UINT16 GetObjIdentifier() const;
    virtual void TakeUnrotatedSnapRect(Rectangle& rRect) const;

    virtual void NbcMove(const Size& rSiz);
    virtual void NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact);
    virtual long GetRotateAngle() const;
    virtual void RecalcBoundRect();
    virtual void RecalcSnapRect();


    virtual const Point& GetPoint(USHORT i) const;
    virtual void NbcSetPoint(const Point& rPnt, USHORT i);


    virtual bool BegTextEdit(SdrOutliner&) { return false; } // DBG_BF_ASSERT
    virtual void EndTextEdit(SdrOutliner& rOutl);
    virtual const Size& GetTextSize() const;
    virtual void TakeTextRect( SdrOutliner& rOutliner, Rectangle& rTextRect,
        Rectangle* pAnchorRect ) const;
    virtual void TakeTextAnchorRect(Rectangle& rAnchorRect) const;
    virtual void NbcSetOutlinerParaObject(OutlinerParaObject* pTextObject);
    virtual OutlinerParaObject* GetOutlinerParaObject() const;

    virtual bool CalcFieldValue(const SvxFieldItem& rField, USHORT nPara, USHORT nPos,
        bool bEdit, Color*& rpTxtColor, Color*& rpFldColor, String& rRet) const;

    virtual void NbcSetStyleSheet(SfxStyleSheet* pNewStyleSheet, bool bDontRemoveHardAttr);

    // ItemSet access
    virtual SfxItemSet* CreateNewItemSet(SfxItemPool& rPool);

    // private support routines for ItemSet access. NULL pointer means clear item.
    virtual void ItemSetChanged(const SfxItemSet& rSet);

    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);
};

/////////////////////////////////////////////////////////////////////////////////////////////////
//
// Creating:
// ~~~~~~~~~
// Dragging von Bezugspunkt 1 zu Bezugspunkt 2 -> Bezugskante
//
// Die Defaults:
// ~~~~~~~~~~~~~
// Masslinie und Masshilfslinien: Haarlinien solid schwarz
// Pfeile:     2mm x 4mm
// Textgroesse
//                              ___
//     ?       Masszahl       ?2mm
//     ?--------------------->?--
//     ?                      ?8mm
//     ?                      ?
//    Pt1?????????????       Pt2-- <----Bezugskante (von Pt1 nach Pt2)
//     ?            ?        ?___ <- Ueberstand der Masshilfslinie(n)
//     ?            ???????????
//     ?Zu bemassendes Objekt ?
//     ?????????????????????????
//
// Attribute:
// ~~~~~~~~~~
// 1. Wo steht der Text: mitte, rechts oder links (def=automatik)
// 2. Text oberhalb der Linie oder unterhalb oder Linie unterbrochen durch Text (def=automatik)
// 3. Den Abstand der Masslinie zur Bezugskante (=zum bemassten Objekt).
//    Default=8mm
// 4. Masslinie unterhalb der Bezugskante (default=nein)
// 5. Die Ueberlaenge(n) der Masshilfslinien ueber die Bezugskante (2x, default=0)
// 6. Den Ueberhang der Masshilfslinien ueber die Masslinie (default=2mm)
// 7. Den Abstand der Masshilfslinien zur Bezugskante
//
// Dragging:                    Handle          Shift
// ~~~~~~~~~
// -  Die Bezugspunkte        SolidQuadHdl   nur die Laenge
// 1.+2. Anpacken des Textes
// 3.+4. Hdl am Pfeil (2x)    SolidQuadHdl   nur den Bool
// 5.    Hdl am Endpunkt      CircHdl        beide Laengen?
// 6.+7. Kein Dragging
//
// Offen:
// ~~~~~~
// - Radien (gleich als Typ verankern
//
// Special:
// ~~~~~~~~
// Connecting an max. 2 Objekte
// -> Bei Copy, etc. den entspr. Code der Verbinder verwenden?!?
// wird wohl recht kompliziert werden ...
//
/////////////////////////////////////////////////////////////////////////////////////////////////

}//end of namespace binfilter
#endif //_SVDOMEAS_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
