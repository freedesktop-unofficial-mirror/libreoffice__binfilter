/*************************************************************************
 *
 *  $RCSfile: svdorect.hxx,v $
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

#ifndef _SVDORECT_HXX
#define _SVDORECT_HXX

#ifndef _SVDOTEXT_HXX
#include <bf_svx/svdotext.hxx>
#endif

//************************************************************
//   Vorausdeklarationen
//************************************************************

class XPolygon;

//************************************************************
//   Hilfsklasse SdrRectObjGeoData
//************************************************************

class SdrRectObjGeoData : public SdrTextObjGeoData
{
public:
    long                        nEckRad; // Eckenradius -> Undo soll dann auch mal ueber Items ...
};

//************************************************************
//   SdrRectObj
//
// Rechteck-Objekte (Rechteck,Kreis,...)
//
//************************************************************

class SdrRectObj : public SdrTextObj
{
    friend class                SdrTextObj; // wg SetXPolyDirty bei GrowAdjust

protected:
    XPolygon*                   pXPoly;
    FASTBOOL                    bXPolyIsLine;  // TRUE: pXPoly muss als PolyLine angesehen werden.

protected:
    // Liefert TRUE, wenn das Painten ein XPolygon erfordert.
    FASTBOOL PaintNeedsXPoly(long nEckRad) const;

protected:
    XPolygon ImpCalcXPoly(const Rectangle& rRect1, long nRad1, FASTBOOL bContour=FALSE) const;
    SdrObject* ImpCheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer, FASTBOOL bForceFilled, FASTBOOL bForceTol=FALSE) const;

    //void PaintIt(ExtOutputDevice& rOut, _BOOL bDown) const;
    void SetXPolyDirty();

    // RecalcXPoly sollte ueberladen werden. Dabei muss dann eine XPolygon
    // Instanz generiert (new) und an pXPoly zugewiesen werden.
    virtual void RecalcXPoly();
    const XPolygon& GetXPoly() const;
    virtual SdrObjGeoData* NewGeoData() const;
    virtual void           SaveGeoData(SdrObjGeoData& rGeo) const;
    virtual void           RestGeoData(const SdrObjGeoData& rGeo);

public:
    TYPEINFO();
    // Der Eckenradius-Parameter fliegt irgendwann raus. Der Eckenradius
    // ist dann (spaeter) ueber SfxItems einzustellen (SetAttributes()).
    // Konstruktion eines Rechteck-Zeichenobjekts

    SdrRectObj();
    SdrRectObj(const Rectangle& rRect);

    // Konstruktion eines Textrahmens
    SdrRectObj(SdrObjKind eNewTextKind);
    SdrRectObj(SdrObjKind eNewTextKind, const Rectangle& rRect);
    // der USHORT eFormat nimmt Werte des enum EETextFormat entgegen
    SdrRectObj(SdrObjKind eNewTextKind, const Rectangle& rNewRect, SvStream& rInput, USHORT eFormat);
    virtual ~SdrRectObj();

//STRIP001  virtual void TakeObjInfo(SdrObjTransformInfoRec& rInfo) const;
    virtual UINT16 GetObjIdentifier() const;
    virtual void RecalcBoundRect();
    virtual void TakeUnrotatedSnapRect(Rectangle& rRect) const;
    virtual FASTBOOL Paint(ExtOutputDevice& rOut, const SdrPaintInfoRec& rInfoRec) const;
    virtual SdrObject* CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const;

//STRIP001  virtual void TakeObjNameSingul(String& rName) const;
//STRIP001  virtual void TakeObjNamePlural(String& rName) const;

    virtual void operator=(const SdrObject& rObj);
    virtual void RecalcSnapRect();
    virtual void NbcSetSnapRect(const Rectangle& rRect);
    virtual void NbcSetLogicRect(const Rectangle& rRect);
    virtual void TakeXorPoly(XPolyPolygon& rPoly, FASTBOOL bDetail) const;
    virtual void TakeContour(XPolyPolygon& rPoly) const;
//STRIP001  virtual void TakeContour(XPolyPolygon& rXPoly, SdrContourType eType) const;

//STRIP001  virtual USHORT GetHdlCount() const;
//STRIP001  virtual SdrHdl* GetHdl(USHORT nHdlNum) const;
//STRIP001  virtual FASTBOOL HasSpecialDrag() const;
//STRIP001  virtual FASTBOOL BegDrag(SdrDragStat& rDrag) const;
//STRIP001  virtual FASTBOOL MovDrag(SdrDragStat& rDrag) const;
//STRIP001  virtual FASTBOOL EndDrag(SdrDragStat& rDrag);
//STRIP001  virtual void BrkDrag(SdrDragStat& rDrag) const;

//STRIP001  virtual String GetDragComment(const SdrDragStat& rDrag, FASTBOOL bUndoDragComment, FASTBOOL bCreateComment) const;

//STRIP001  virtual void TakeDragPoly(const SdrDragStat& rDrag, XPolyPolygon& rXPP) const;
//STRIP001  virtual void TakeCreatePoly(const SdrDragStat& rDrag, XPolyPolygon& rXPP) const;
    virtual Pointer GetCreatePointer() const;

    virtual void NbcMove(const Size& rSiz);
    virtual void NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact);
    virtual void NbcRotate(const Point& rRef, long nWink, double sn, double cs);
//STRIP001  virtual void NbcMirror(const Point& rRef1, const Point& rRef2);
    virtual void NbcShear(const Point& rRef, long nWink, double tn, FASTBOOL bVShear);

//STRIP001  virtual FASTBOOL DoMacro(const SdrObjMacroHitRec& rRec);
//STRIP001  virtual XubString GetMacroPopupComment(const SdrObjMacroHitRec& rRec) const;

    virtual SdrGluePoint GetVertexGluePoint(USHORT nNum) const;
//STRIP001  virtual SdrGluePoint GetCornerGluePoint(USHORT nNum) const;

//STRIP001  virtual SdrObject* DoConvertToPolyObj(BOOL bBezier) const;

    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

    virtual void SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType);

    // private support routines for ItemSet access. NULL pointer means clear item.
    virtual void ItemSetChanged(const SfxItemSet& rSet);

    virtual void NbcSetStyleSheet(SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr);
};

#endif //_SVDORECT_HXX

