/*************************************************************************
 *
 *  $RCSfile: svdocapt.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:28:52 $
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

#ifndef _SVDCAPT_HXX
#define _SVDCAPT_HXX

#ifndef _SVDORECT_HXX
#include <bf_svx/svdorect.hxx>
#endif
namespace binfilter {

//************************************************************
//   Vorausdeklarationen
//************************************************************

class SdrCaptionSetItem;
class ImpCaptParams;

#define SDRSETITEM_CAPTION_ATTR     SDRSETITEM_ATTR_COUNT

//************************************************************
//   Hilfsklasse SdrCaptObjGeoData
//************************************************************

class SdrCaptObjGeoData : public SdrRectObjGeoData
{
public:
    Polygon                     aTailPoly;
};

//************************************************************
//   SdrCaptionObj
//************************************************************

class SdrCaptionObj : public SdrRectObj
{
    friend class                SdrTextObj; // fuer ImpRecalcTail() bei AutoGrow

protected:
    Polygon                     aTailPoly;  // das ganze Polygon des Schwanzes
    sal_Bool                    mbSpecialTextBoxShadow; // for calc special shadow, default FALSE

private:
    void ImpGetCaptParams(ImpCaptParams& rPara) const;
//STRIP001  void ImpCalcTail1(const ImpCaptParams& rPara, Polygon& rPoly, Rectangle& rRect) const;
//STRIP001  void ImpCalcTail2(const ImpCaptParams& rPara, Polygon& rPoly, Rectangle& rRect) const;
    void ImpCalcTail3(const ImpCaptParams& rPara, Polygon& rPoly, Rectangle& rRect) const;
//STRIP001  void ImpCalcTail4(const ImpCaptParams& rPara, Polygon& rPoly, Rectangle& rRect) const;
    void ImpCalcTail (const ImpCaptParams& rPara, Polygon& rPoly, Rectangle& rRect) const;
    void ImpRecalcTail();

public:
    TYPEINFO();
    SdrCaptionObj();
    SdrCaptionObj(const Rectangle& rRect);
    SdrCaptionObj(const Rectangle& rRect, const Point& rTail);
    virtual ~SdrCaptionObj();

//STRIP001  virtual void TakeObjInfo(SdrObjTransformInfoRec& rInfo) const;
    virtual UINT16 GetObjIdentifier() const;
    virtual void RecalcBoundRect();
//STRIP001  virtual SdrObject* CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const;
//STRIP001  virtual void operator=(const SdrObject& rObj);

    // for calc: special shadow only for text box
    void SetSpecialTextBoxShadow() { mbSpecialTextBoxShadow = TRUE; }
//STRIP001  virtual FASTBOOL Paint(ExtOutputDevice& rOut, const SdrPaintInfoRec& rInfoRec) const;

//STRIP001  virtual void TakeObjNameSingul(String& rName) const;
//STRIP001  virtual void TakeObjNamePlural(String& rName) const;

//STRIP001  virtual void TakeXorPoly(XPolyPolygon& rXPoly, FASTBOOL bDetail) const;
//STRIP001  virtual void TakeContour(XPolyPolygon& rPoly, SdrContourType eType) const;
    virtual void SetModel(SdrModel* pNewModel);
//STRIP001  virtual void SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType);

    // ItemSet access
    virtual SfxItemSet* CreateNewItemSet(SfxItemPool& rPool);

    // private support routines for ItemSet access. NULL pointer means clear item.
    virtual void ItemSetChanged(const SfxItemSet& rSet);

    // pre- and postprocessing for objects for saving
    virtual void PreSave();
    virtual void PostSave();

    virtual void NbcSetStyleSheet(SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr);

//STRIP001  virtual USHORT GetHdlCount() const;
//STRIP001  virtual SdrHdl* GetHdl(USHORT nHdlNum) const;
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

//STRIP001  virtual void NbcSetRelativePos(const Point& rPnt);
//STRIP001  virtual Point GetRelativePos() const;
    virtual void NbcSetAnchorPos(const Point& rPnt);
    virtual const Point& GetAnchorPos() const;

    virtual void RecalcSnapRect();
    virtual const Rectangle& GetSnapRect() const;
    virtual void NbcSetSnapRect(const Rectangle& rRect);
//STRIP001  virtual const Rectangle& GetLogicRect() const;
//STRIP001  virtual void NbcSetLogicRect(const Rectangle& rRect);

//STRIP001  virtual USHORT GetSnapPointCount() const;
//STRIP001  virtual Point GetSnapPoint(USHORT i) const;

protected:
//STRIP001  virtual SdrObjGeoData* NewGeoData() const;
//STRIP001  virtual void SaveGeoData(SdrObjGeoData& rGeo) const;
//STRIP001  virtual void RestGeoData(const SdrObjGeoData& rGeo);

public:
//STRIP001  virtual SdrObject* DoConvertToPolyObj(BOOL bBezier) const;

    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

    const Point& GetTailPos() const;
    void SetTailPos(const Point& rPos);
    void NbcSetTailPos(const Point& rPos);
};

////////////////////////////////////////////////////////////////////////////////////////////////////

}//end of namespace binfilter
#endif //_SVDOCAPT_HXX

