/*************************************************************************
 *
 *  $RCSfile: svdocirc.hxx,v $
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

#ifndef _SVDOCIRC_HXX
#define _SVDOCIRC_HXX

#ifndef _SVDORECT_HXX
#include <bf_svx/svdorect.hxx>
#endif

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
    XPolygon ImpCalcXPoly(const Rectangle& rRect1, long nStart, long nEnd, FASTBOOL bContour=FALSE) const;
//STRIP001  void ImpSetCreateParams(SdrDragStat& rStat) const;
    void ImpSetAttrToCircInfo(); // Werte vom Pool kopieren
    void ImpSetCircInfoToAttr(); // Werte in den Pool kopieren

    // Liefert TRUE, wenn das Painten ein XPolygon erfordert.
    FASTBOOL PaintNeedsXPoly() const;
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

//STRIP001  virtual void TakeObjInfo(SdrObjTransformInfoRec& rInfo) const;
    virtual UINT16 GetObjIdentifier() const;
    virtual void RecalcBoundRect();
    virtual void TakeUnrotatedSnapRect(Rectangle& rRect) const;
    virtual FASTBOOL Paint(ExtOutputDevice& rOut, const SdrPaintInfoRec& rInfoRec) const;
//STRIP001  virtual SdrObject* CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const;

//STRIP001  virtual void TakeObjNameSingul(String& rName) const;
//STRIP001  virtual void TakeObjNamePlural(String& rName) const;

    virtual void operator=(const SdrObject& rObj);
    virtual void RecalcSnapRect();
    virtual void NbcSetSnapRect(const Rectangle& rRect);
    virtual void TakeXorPoly(XPolyPolygon& rXPoly, FASTBOOL bDetail) const;
    virtual void TakeContour(XPolyPolygon& rXPoly) const;
//STRIP001  virtual void TakeContour(XPolyPolygon& rXPoly, SdrContourType eType) const;

//STRIP001  virtual USHORT GetSnapPointCount() const;
//STRIP001  virtual Point GetSnapPoint(USHORT i) const;

//STRIP001  virtual USHORT GetHdlCount() const;
//STRIP001  virtual SdrHdl* GetHdl(USHORT nHdlNum) const;
//STRIP001  virtual FASTBOOL HasSpecialDrag() const;
//STRIP001  virtual FASTBOOL BegDrag(SdrDragStat& rDrag) const;
//STRIP001  virtual FASTBOOL MovDrag(SdrDragStat& rDrag) const;
//STRIP001  virtual FASTBOOL EndDrag(SdrDragStat& rDrag);
//STRIP001  virtual void BrkDrag(SdrDragStat& rDrag)  const;

//STRIP001  virtual String GetDragComment(const SdrDragStat& rDrag, FASTBOOL bUndoDragComment, FASTBOOL bCreateComment) const;

//STRIP001  virtual void TakeDragPoly(const SdrDragStat& rDrag, XPolyPolygon& rXPP) const;
//STRIP001  virtual FASTBOOL BegCreate(SdrDragStat& rStat);
//STRIP001  virtual FASTBOOL MovCreate(SdrDragStat& rStat);
//STRIP001  virtual FASTBOOL EndCreate(SdrDragStat& rStat, SdrCreateCmd eCmd);
//STRIP001  virtual FASTBOOL BckCreate(SdrDragStat& rStat);
//STRIP001  virtual void BrkCreate(SdrDragStat& rStat);
//STRIP001  virtual void TakeCreatePoly(const SdrDragStat& rDrag, XPolyPolygon& rXPP) const;
//STRIP001  virtual Pointer GetCreatePointer() const;
    virtual void NbcMove(const Size& aSiz);
    virtual void NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact);
//STRIP001  virtual void NbcMirror(const Point& rRef1, const Point& rRef2);
    virtual void NbcShear (const Point& rRef, long nWink, double tn, FASTBOOL bVShear);
    virtual SdrObject* DoConvertToPolyObj(BOOL bBezier) const;

protected:
//STRIP001  virtual SdrObjGeoData* NewGeoData() const;
//STRIP001  virtual void SaveGeoData(SdrObjGeoData& rGeo) const;
//STRIP001  virtual void RestGeoData(const SdrObjGeoData& rGeo);
public:
    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

    long GetStartWink() const { return nStartWink; }
    long GetEndWink() const { return nEndWink; }
    virtual void NbcSetStyleSheet(SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr);

    // ItemSet access
    virtual SfxItemSet* CreateNewItemSet(SfxItemPool& rPool);

    // private support routines for ItemSet access. NULL pointer means clear item.
    virtual void ItemSetChanged(const SfxItemSet& rSet);

    // pre- and postprocessing for objects for saving
    virtual void PreSave();
    virtual void PostSave();
};

#endif //_SVDOCIRC_HXX

