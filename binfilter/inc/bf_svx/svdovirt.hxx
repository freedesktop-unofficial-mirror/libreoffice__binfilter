/*************************************************************************
 *
 *  $RCSfile: svdovirt.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:50 $
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

#ifndef _SVDOVIRT_HXX
#define _SVDOVIRT_HXX

#ifndef _SVDOBJ_HXX
#include <bf_svx/svdobj.hxx>
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//   SdrVirtObj
//
// Achtung! Das virtuelle Objekt ist noch nicht bis in alle Feinheiten
// durchprogrammiert und getestet. Z.Zt. kommt es nur in abgeleiteter
// beim Writer zum Einsatz.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

class SdrVirtObj : public SdrObject
{
protected:
    SdrObject&                  rRefObj; // Referenziertes Zeichenobjekt
    Rectangle                   aSnapRect;
    Point                       aHack;   // f. GetPoint()

protected:
    virtual void SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType);

    virtual SdrObjGeoData* NewGeoData() const;
    virtual void SaveGeoData(SdrObjGeoData& rGeo) const;
    virtual void RestGeoData(const SdrObjGeoData& rGeo);

public:
    TYPEINFO();
    SdrVirtObj(SdrObject& rNewObj);
    SdrVirtObj(SdrObject& rNewObj, const Point& rAnchorPos);
    virtual ~SdrVirtObj();
    virtual SdrObject& ReferencedObj();
    virtual const SdrObject& GetReferencedObj() const;
//STRIP001  virtual void NbcSetAnchorPos(const Point& rAnchorPos);
    virtual void SetModel(SdrModel* pNewModel);

//STRIP001  virtual void TakeObjInfo(SdrObjTransformInfoRec& rInfo) const;
    virtual UINT32 GetObjInventor() const;
    virtual UINT16 GetObjIdentifier() const;
    virtual SdrObjList* GetSubList() const;

//STRIP001  virtual const Rectangle& GetBoundRect() const;
//STRIP001  virtual void RecalcBoundRect();
    virtual void SetChanged();
//STRIP001  virtual FASTBOOL Paint(ExtOutputDevice& rOut, const SdrPaintInfoRec& rInfoRec) const;
//STRIP001  virtual SdrObject* CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const;
//STRIP001  virtual SdrObject* Clone() const;
//STRIP001  virtual void operator=(const SdrObject& rObj);

//STRIP001  virtual void TakeObjNameSingul(String& rName) const;
//STRIP001  virtual void TakeObjNamePlural(String& rName) const;

//STRIP001  virtual void TakeXorPoly(XPolyPolygon& rPoly, FASTBOOL bDetail) const;
//STRIP001  virtual void TakeContour(XPolyPolygon& rXPoly, SdrContourType eType) const;

//STRIP001  virtual USHORT GetHdlCount() const;
//STRIP001  virtual SdrHdl* GetHdl(USHORT nHdlNum) const;
//STRIP001  virtual USHORT GetPlusHdlCount(const SdrHdl& rHdl) const;
//STRIP001  virtual SdrHdl* GetPlusHdl(const SdrHdl& rHdl, USHORT nPlNum) const;
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

//STRIP001  virtual void NbcMove(const Size& rSiz);
    virtual void NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact);
//STRIP001  virtual void NbcRotate(const Point& rRef, long nWink, double sn, double cs);
//STRIP001  virtual void NbcMirror(const Point& rRef1, const Point& rRef2);
//STRIP001  virtual void NbcShear(const Point& rRef, long nWink, double tn, FASTBOOL bVShear);

//STRIP001  virtual void Move(const Size& rSiz);
    virtual void Resize(const Point& rRef, const Fraction& xFact, const Fraction& yFact);
//STRIP001  virtual void Rotate(const Point& rRef, long nWink, double sn, double cs);
//STRIP001  virtual void Mirror(const Point& rRef1, const Point& rRef2);
//STRIP001  virtual void Shear(const Point& rRef, long nWink, double tn, FASTBOOL bVShear);

    virtual void RecalcSnapRect();
//STRIP001  virtual const Rectangle& GetSnapRect() const;
//STRIP001  virtual void SetSnapRect(const Rectangle& rRect);
//STRIP001  virtual void NbcSetSnapRect(const Rectangle& rRect);

//STRIP001  virtual const Rectangle& GetLogicRect() const;
//STRIP001  virtual void SetLogicRect(const Rectangle& rRect);
//STRIP001  virtual void NbcSetLogicRect(const Rectangle& rRect);

    virtual long GetRotateAngle() const;
    virtual long GetShearAngle(FASTBOOL bVertical=FALSE) const;

//STRIP001  virtual USHORT GetSnapPointCount() const;
//STRIP001  virtual Point GetSnapPoint(USHORT i) const;

//STRIP001  virtual FASTBOOL IsPolyObj() const;
//STRIP001  virtual USHORT GetPointCount() const;
//STRIP001  virtual const Point& GetPoint(USHORT i) const;
    virtual void NbcSetPoint(const Point& rPnt, USHORT i);

//STRIP001  virtual SdrObjGeoData* GetGeoData() const;
//STRIP001  virtual void SetGeoData(const SdrObjGeoData& rGeo);

    // ItemSet access
    virtual const SfxItemSet& GetItemSet() const;
    virtual SfxItemSet* CreateNewItemSet(SfxItemPool& rPool);
//STRIP001  virtual void SetItem(const SfxPoolItem& rItem);
//STRIP001  virtual void ClearItem(const sal_uInt16 nWhich = 0);
//STRIP001  virtual void SetItemSet(const SfxItemSet& rSet);
//STRIP001  virtual void BroadcastItemChange(const SdrBroadcastItemChange& rChange);

    // private support routines for ItemSet access. NULL pointer means clear item.
//STRIP001  virtual BOOL AllowItemChange(const sal_uInt16 nWhich, const SfxPoolItem* pNewItem = 0) const;
//STRIP001  virtual void ItemChange(const sal_uInt16 nWhich, const SfxPoolItem* pNewItem = 0);
//STRIP001  virtual void PostItemChange(const sal_uInt16 nWhich);
//STRIP001  virtual void ItemSetChanged(const SfxItemSet& rSet);

    // pre- and postprocessing for objects for saving
    virtual void PreSave();
    virtual void PostSave();

//STRIP001  virtual SfxStyleSheet* GetStyleSheet() const;
    virtual void NbcSetStyleSheet(SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr);
    virtual void SetStyleSheet(SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr);

//STRIP001  virtual void NbcReformatText();
//STRIP001  virtual void ReformatText();

//STRIP001  virtual FASTBOOL HasMacro() const;
//STRIP001  virtual SdrObject* CheckMacroHit (const SdrObjMacroHitRec& rRec) const;
//STRIP001  virtual Pointer GetMacroPointer (const SdrObjMacroHitRec& rRec) const;
//STRIP001  virtual void PaintMacro (ExtOutputDevice& rXOut, const Rectangle& rDirtyRect, const SdrObjMacroHitRec& rRec) const;
//STRIP001  virtual FASTBOOL DoMacro (const SdrObjMacroHitRec& rRec);
//STRIP001  virtual XubString GetMacroPopupComment(const SdrObjMacroHitRec& rRec) const;

    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);
    virtual void AfterRead();

    // OD 30.06.2003 #108784# - virtual <GetOffset()> returns Point(0,0)
    virtual const Point GetOffset() const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //_SVDOVIRT_HXX

