/*************************************************************************
 *
 *  $RCSfile: svdomeas.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:42 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef _SVDOMEAS_HXX
#define _SVDOMEAS_HXX

#ifndef _SVDOTEXT_HXX
#include <bf_svx/svdotext.hxx>
#endif

//************************************************************
//   Vorausdeklarationen
//************************************************************

class SdrMeasureSetItem;
class SdrOutliner;
struct ImpMeasureRec;
struct ImpMeasurePoly;

//************************************************************
//   Hilfsklasse SdrMeasureObjGeoData
//************************************************************

class SdrMeasureObjGeoData : public SdrTextObjGeoData
{
public:
    Point                       aPt1;
    Point                       aPt2;

public:
    SdrMeasureObjGeoData();
    virtual ~SdrMeasureObjGeoData();
};

//************************************************************
//   SdrMeasureObj
//************************************************************

class SdrMeasureObj : public SdrTextObj
{
    friend class                SdrMeasureField;

protected:
    Point                       aPt1;
    Point                       aPt2;
    FASTBOOL                    bTextDirty;

protected:
    virtual void SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType);
    virtual void ForceDefaultAttr();
    void ImpTakeAttr(ImpMeasureRec& rRec) const;
    void ImpCalcGeometrics(const ImpMeasureRec& rRec, ImpMeasurePoly& rPol) const;
    void ImpCalcXPoly(const ImpMeasurePoly& rPol, XPolyPolygon& rXPP) const;
//STRIP001  void ImpEvalDrag(ImpMeasureRec& rRec, const SdrDragStat& rDrag) const;
    void SetTextDirty() { bTextDirty=TRUE; SetTextSizeDirty(); if (!bBoundRectDirty) { bBoundRectDirty=TRUE; SetRectsDirty(TRUE); } }
    void UndirtyText() const;

//STRIP001  virtual SdrObjGeoData* NewGeoData() const;
//STRIP001  virtual void SaveGeoData(SdrObjGeoData& rGeo) const;
//STRIP001  virtual void RestGeoData(const SdrObjGeoData& rGeo);

public:
    TYPEINFO();
    SdrMeasureObj();
    SdrMeasureObj(const Point& rPt1, const Point& rPt2);
    virtual ~SdrMeasureObj();

//STRIP001  virtual void TakeObjInfo(SdrObjTransformInfoRec& rInfo) const;
    virtual UINT16 GetObjIdentifier() const;
//STRIP001  virtual FASTBOOL Paint(ExtOutputDevice& rOut, const SdrPaintInfoRec& rInfoRec) const;
    virtual void TakeUnrotatedSnapRect(Rectangle& rRect) const;
//STRIP001  virtual SdrObject* CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const;
//STRIP001  virtual void operator=(const SdrObject& rObj);

//STRIP001  virtual void TakeObjNameSingul(String& rName) const;
//STRIP001  virtual void TakeObjNamePlural(String& rName) const;

//STRIP001  virtual void TakeXorPoly(XPolyPolygon& rPoly, FASTBOOL bDetail) const;
//STRIP001  virtual void TakeContour(XPolyPolygon& rXPoly, SdrContourType eType) const;

//STRIP001  virtual USHORT GetHdlCount() const;
//STRIP001  virtual SdrHdl* GetHdl(USHORT nHdlNum) const;
//STRIP001  virtual void AddToHdlList(SdrHdlList& rHdlList) const;
//STRIP001  virtual FASTBOOL HasSpecialDrag() const;
//STRIP001  virtual FASTBOOL BegDrag(SdrDragStat& rDrag) const;
//STRIP001  virtual FASTBOOL MovDrag(SdrDragStat& rDrag) const;
//STRIP001  virtual FASTBOOL EndDrag(SdrDragStat& rDrag);
//STRIP001  virtual void BrkDrag(SdrDragStat& rDrag) const;

//STRIP001  virtual String GetDragComment(const SdrDragStat& rDrag, FASTBOOL bUndoDragComment, FASTBOOL bCreateComment) const;
//STRIP001  virtual void TakeDragPoly(const SdrDragStat& rDrag, XPolyPolygon& rXPP) const;

//STRIP001  virtual FASTBOOL BegCreate(SdrDragStat& rStat);
//STRIP001  virtual FASTBOOL MovCreate(SdrDragStat& rStat);
//STRIP001  virtual FASTBOOL EndCreate(SdrDragStat& rStat, SdrCreateCmd eCmd);
//STRIP001  virtual FASTBOOL BckCreate(SdrDragStat& rStat);
//STRIP001  virtual void BrkCreate(SdrDragStat& rStat);
//STRIP001  virtual void TakeCreatePoly(const SdrDragStat& rDrag, XPolyPolygon& rXPP) const;
//STRIP001  virtual Pointer GetCreatePointer() const;

    virtual void NbcMove(const Size& rSiz);
    virtual void NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact);
//STRIP001  virtual void NbcRotate(const Point& rRef, long nWink, double sn, double cs);
//STRIP001  virtual void NbcMirror(const Point& rRef1, const Point& rRef2);
//STRIP001  virtual void NbcShear(const Point& rRef, long nWink, double tn, FASTBOOL bVShear);
//STRIP001  virtual const Rectangle& GetLogicRect() const;
//STRIP001  virtual void NbcSetLogicRect(const Rectangle& rRect);
    virtual long GetRotateAngle() const;
    virtual void RecalcBoundRect();
    virtual void RecalcSnapRect();

//STRIP001  virtual USHORT GetSnapPointCount() const;
//STRIP001  virtual Point GetSnapPoint(USHORT i) const;

//STRIP001  virtual FASTBOOL IsPolyObj() const;
//STRIP001  virtual USHORT GetPointCount() const;
    virtual const Point& GetPoint(USHORT i) const;
    virtual void NbcSetPoint(const Point& rPnt, USHORT i);

//STRIP001  virtual SdrObject* DoConvertToPolyObj(BOOL bBezier) const;
//STRIP001     virtual ::std::auto_ptr< SdrLineGeometry > CreateLinePoly( OutputDevice&     rOut,
//STRIP001                                                                BOOL          bForceOnePixel,
//STRIP001                                                                BOOL          bForceTwoPixel,
//STRIP001                                                                BOOL          bIsLineDraft    ) const;

    virtual FASTBOOL BegTextEdit(SdrOutliner& rOutl);
    virtual void EndTextEdit(SdrOutliner& rOutl);
    virtual const Size& GetTextSize() const;
    virtual void TakeTextRect( SdrOutliner& rOutliner, Rectangle& rTextRect, FASTBOOL bNoEditText=FALSE,
        Rectangle* pAnchorRect=NULL, BOOL bLineWidth=TRUE ) const;
    virtual void TakeTextAnchorRect(Rectangle& rAnchorRect) const;
//STRIP001  virtual void TakeTextEditArea(Size* pPaperMin, Size* pPaperMax, Rectangle* pViewInit, Rectangle* pViewMin) const;
//STRIP001  virtual SdrObject* CheckTextEditHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const;
//STRIP001  virtual USHORT GetOutlinerViewAnchorMode() const;
    virtual void NbcSetOutlinerParaObject(OutlinerParaObject* pTextObject);
    virtual OutlinerParaObject* GetOutlinerParaObject() const;

    virtual FASTBOOL CalcFieldValue(const SvxFieldItem& rField, USHORT nPara, USHORT nPos,
        FASTBOOL bEdit, Color*& rpTxtColor, Color*& rpFldColor, String& rRet) const;

    virtual void NbcSetStyleSheet(SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr);

    // ItemSet access
    virtual SfxItemSet* CreateNewItemSet(SfxItemPool& rPool);

    // private support routines for ItemSet access. NULL pointer means clear item.
    virtual void ItemSetChanged(const SfxItemSet& rSet);

    // pre- and postprocessing for objects for saving
    virtual void PreSave();
    virtual void PostSave();

    virtual void WriteData(SvStream& rOut) const;
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
//     ณ        Masszahl       ณ 2mm
//     ร<--------------------->ด---
//     ณ                       ณ 8mm
//     ณ                       ณ
//    Pt1ออออออออออออป        Pt2-- <----Bezugskante (von Pt1 nach Pt2)
//     บ             บ         ณ___ <- Ueberstand der Masshilfslinie(n)
//     บ             ศอออออออออป
//     บ Zu bemassendes Objekt บ
//     ศอออออออออออออออออออออออผ
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

#endif //_SVDOMEAS_HXX

