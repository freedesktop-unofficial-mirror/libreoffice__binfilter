/*************************************************************************
 *
 *  $RCSfile: svx_svdovirt.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:41 $
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

#include "svdovirt.hxx"
#include "xpool.hxx"
#include "svdxout.hxx"
#include "svdtrans.hxx"
#include "svdio.hxx"
#include "svdetc.hxx"
#include "svdhdl.hxx"
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ TYPEINIT1(SdrVirtObj,SdrObject);

/*N*/ SdrVirtObj::SdrVirtObj(SdrObject& rNewObj):
/*N*/   rRefObj(rNewObj)
/*N*/ {
/*N*/   bVirtObj=TRUE; // Ja, ich bin ein virtuelles Objekt
/*N*/   rRefObj.AddReference(*this);
/*N*/   bClosedObj=rRefObj.IsClosedObj();
/*N*/ }

/*?*/ SdrVirtObj::SdrVirtObj(SdrObject& rNewObj, const Point& rAnchorPos):
/*?*/   rRefObj(rNewObj)
/*?*/ {
/*?*/   aAnchor=rAnchorPos;
/*?*/   bVirtObj=TRUE; // Ja, ich bin ein virtuelles Objekt
/*?*/   rRefObj.AddReference(*this);
/*?*/   bClosedObj=rRefObj.IsClosedObj();
/*?*/ }

/*N*/ SdrVirtObj::~SdrVirtObj()
/*N*/ {
/*N*/   rRefObj.DelReference(*this);
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ const SdrObject& SdrVirtObj::GetReferencedObj() const
/*N*/ {
/*N*/   return rRefObj;
/*N*/ }

/*N*/ SdrObject& SdrVirtObj::ReferencedObj()
/*N*/ {
/*N*/   return rRefObj;
/*N*/ }

/*N*/ void __EXPORT SdrVirtObj::SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType)
/*N*/ {
/*N*/   bClosedObj=rRefObj.IsClosedObj();
/*N*/   SetRectsDirty(); // hier noch Optimieren.
/*N*/   SendRepaintBroadcast();
/*N*/ }

//STRIP001 void SdrVirtObj::NbcSetAnchorPos(const Point& rAnchorPos)
//STRIP001 {
//STRIP001  aAnchor=rAnchorPos;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrVirtObj::SetModel(SdrModel* pNewModel)
/*N*/ {
/*N*/   SdrObject::SetModel(pNewModel);
/*N*/   rRefObj.SetModel(pNewModel);
/*N*/ }

//STRIP001 void SdrVirtObj::TakeObjInfo(SdrObjTransformInfoRec& rInfo) const
//STRIP001 {
//STRIP001  rRefObj.TakeObjInfo(rInfo);
//STRIP001 }

/*N*/ UINT32 SdrVirtObj::GetObjInventor() const
/*N*/ {
/*N*/   return rRefObj.GetObjInventor();
/*N*/ }

/*N*/ UINT16 SdrVirtObj::GetObjIdentifier() const
/*N*/ {
/*N*/   return rRefObj.GetObjIdentifier();
/*N*/ }

/*N*/ SdrObjList* SdrVirtObj::GetSubList() const
/*N*/ {
/*N*/   return rRefObj.GetSubList();
/*N*/ }

//STRIP001 const Rectangle& SdrVirtObj::GetBoundRect() const
//STRIP001 {
//STRIP001  ((SdrVirtObj*)this)->aOutRect=rRefObj.GetBoundRect(); // Hier noch optimieren
//STRIP001  ((SdrVirtObj*)this)->aOutRect+=aAnchor;
//STRIP001  return aOutRect;
//STRIP001 }

//STRIP001 void SdrVirtObj::RecalcBoundRect()
//STRIP001 {
//STRIP001  aOutRect=rRefObj.GetBoundRect();
//STRIP001  aOutRect+=aAnchor;
//STRIP001 }

/*N*/ void SdrVirtObj::SetChanged()
/*N*/ {
/*N*/   SdrObject::SetChanged();
/*N*/ }

//STRIP001 FASTBOOL SdrVirtObj::Paint(ExtOutputDevice& rOut, const SdrPaintInfoRec& rInfoRec) const
//STRIP001 {
//STRIP001  Point aOfs(rOut.GetOffset());
//STRIP001  rOut.SetOffset(aOfs+aAnchor);
//STRIP001  FASTBOOL bRet=rRefObj.Paint(rOut,rInfoRec);
//STRIP001  rOut.SetOffset(aOfs);
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 SdrObject* SdrVirtObj::CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const
//STRIP001 {
//STRIP001  Point aPnt(rPnt-aAnchor);
//STRIP001  FASTBOOL bRet=rRefObj.CheckHit(aPnt,nTol,pVisiLayer)!=NULL;
//STRIP001  return bRet ? (SdrObject*)this : NULL;
//STRIP001 }

//STRIP001 SdrObject* SdrVirtObj::Clone() const
//STRIP001 {
//STRIP001  SdrObject* pObj=new SdrVirtObj(((SdrVirtObj*)this)->rRefObj); // Nur eine weitere Referenz
//STRIP001  return pObj;
//STRIP001 }

//STRIP001 void SdrVirtObj::operator=(const SdrObject& rObj)
//STRIP001 {   // ???anderes Objekt referenzieren???
//STRIP001  SdrObject::operator=(rObj);
//STRIP001  aAnchor=((SdrVirtObj&)rObj).aAnchor;
//STRIP001 }

//STRIP001 void SdrVirtObj::TakeObjNameSingul(XubString& rName) const
//STRIP001 {
//STRIP001  rRefObj.TakeObjNameSingul(rName);
//STRIP001  rName.Insert(sal_Unicode('['), 0);
//STRIP001  rName += sal_Unicode(']');
//STRIP001
//STRIP001  String aName( GetName() );
//STRIP001  if(aName.Len())
//STRIP001  {
//STRIP001      rName += sal_Unicode(' ');
//STRIP001      rName += sal_Unicode('\'');
//STRIP001      rName += aName;
//STRIP001      rName += sal_Unicode('\'');
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrVirtObj::TakeObjNamePlural(XubString& rName) const
//STRIP001 {
//STRIP001  rRefObj.TakeObjNamePlural(rName);
//STRIP001  rName.Insert(sal_Unicode('['), 0);
//STRIP001  rName += sal_Unicode(']');
//STRIP001 }

//STRIP001 void operator +=(PolyPolygon& rPoly, const Point& rOfs)
//STRIP001 {
//STRIP001  if (rOfs.X()!=0 || rOfs.Y()!=0) {
//STRIP001      USHORT i,j;
//STRIP001      for (j=0; j<rPoly.Count(); j++) {
//STRIP001          Polygon aP1(rPoly.GetObject(j));
//STRIP001          for (i=0; i<aP1.GetSize(); i++) {
//STRIP001               aP1[i]+=rOfs;
//STRIP001          }
//STRIP001          rPoly.Replace(aP1,j);
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrVirtObj::TakeXorPoly(XPolyPolygon& rPoly, FASTBOOL bDetail) const
//STRIP001 {
//STRIP001  rRefObj.TakeXorPoly(rPoly,bDetail);
//STRIP001  rPoly.Move(aAnchor.X(),aAnchor.Y());
//STRIP001 }

//STRIP001 void SdrVirtObj::TakeContour(XPolyPolygon& rXPoly, SdrContourType eType) const
//STRIP001 {
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 USHORT SdrVirtObj::GetHdlCount() const
//STRIP001 {
//STRIP001  return rRefObj.GetHdlCount();
//STRIP001 }

//STRIP001 SdrHdl* SdrVirtObj::GetHdl(USHORT nHdlNum) const
//STRIP001 {
//STRIP001  SdrHdl* pHdl=rRefObj.GetHdl(nHdlNum);
//STRIP001  Point aP(pHdl->GetPos()+aAnchor);
//STRIP001  pHdl->SetPos(aP);
//STRIP001  return pHdl;
//STRIP001 }

//STRIP001 USHORT SdrVirtObj::GetPlusHdlCount(const SdrHdl& rHdl) const
//STRIP001 {
//STRIP001  return rRefObj.GetPlusHdlCount(rHdl);
//STRIP001 }

//STRIP001 SdrHdl* SdrVirtObj::GetPlusHdl(const SdrHdl& rHdl, USHORT nPlNum) const
//STRIP001 {
//STRIP001  SdrHdl* pHdl=rRefObj.GetPlusHdl(rHdl,nPlNum);
//STRIP001  pHdl->SetPos(pHdl->GetPos()+aAnchor);
//STRIP001  return pHdl;
//STRIP001 }

//STRIP001 void SdrVirtObj::AddToHdlList(SdrHdlList& rHdlList) const
//STRIP001 {
//STRIP001  SdrObject::AddToHdlList(rHdlList);
//STRIP001 }

//STRIP001 FASTBOOL SdrVirtObj::HasSpecialDrag() const
//STRIP001 {
//STRIP001  return rRefObj.HasSpecialDrag();
//STRIP001 }

//STRIP001 FASTBOOL SdrVirtObj::BegDrag(SdrDragStat& rDrag) const
//STRIP001 {
//STRIP001  return rRefObj.BegDrag(rDrag);
//STRIP001 }

//STRIP001 FASTBOOL SdrVirtObj::MovDrag(SdrDragStat& rDrag) const
//STRIP001 {
//STRIP001  return rRefObj.MovDrag(rDrag);
//STRIP001 }

//STRIP001 FASTBOOL SdrVirtObj::EndDrag(SdrDragStat& rDrag)
//STRIP001 {
//STRIP001  return rRefObj.EndDrag(rDrag);
//STRIP001 }

//STRIP001 void SdrVirtObj::BrkDrag(SdrDragStat& rDrag) const
//STRIP001 {
//STRIP001  rRefObj.BrkDrag(rDrag);
//STRIP001 }

//STRIP001 void SdrVirtObj::TakeDragPoly(const SdrDragStat& rDrag, XPolyPolygon& rXPP) const
//STRIP001 {
//STRIP001  rRefObj.TakeDragPoly(rDrag,rXPP);
//STRIP001  // Offset handlen !!!!!! fehlt noch !!!!!!!
//STRIP001 }

//STRIP001 XubString SdrVirtObj::GetDragComment(const SdrDragStat& rDrag, FASTBOOL bUndoDragComment, FASTBOOL bCreateComment) const
//STRIP001 {
//STRIP001  return rRefObj.GetDragComment(rDrag,bUndoDragComment,bCreateComment);
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 FASTBOOL SdrVirtObj::BegCreate(SdrDragStat& rStat)
//STRIP001 {
//STRIP001  return rRefObj.BegCreate(rStat);
//STRIP001 }

//STRIP001 FASTBOOL SdrVirtObj::MovCreate(SdrDragStat& rStat)
//STRIP001 {
//STRIP001  return rRefObj.MovCreate(rStat);
//STRIP001 }

//STRIP001 FASTBOOL SdrVirtObj::EndCreate(SdrDragStat& rStat, SdrCreateCmd eCmd)
//STRIP001 {
//STRIP001  return rRefObj.EndCreate(rStat,eCmd);
//STRIP001 }

//STRIP001 FASTBOOL SdrVirtObj::BckCreate(SdrDragStat& rStat)
//STRIP001 {
//STRIP001  return rRefObj.BckCreate(rStat);
//STRIP001 }

//STRIP001 void SdrVirtObj::BrkCreate(SdrDragStat& rStat)
//STRIP001 {
//STRIP001  rRefObj.BrkCreate(rStat);
//STRIP001 }

//STRIP001 void SdrVirtObj::TakeCreatePoly(const SdrDragStat& rDrag, XPolyPolygon& rXPP) const
//STRIP001 {
//STRIP001  rRefObj.TakeCreatePoly(rDrag,rXPP);
//STRIP001  // Offset handlen !!!!!! fehlt noch !!!!!!!
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrVirtObj::NbcMove(const Size& rSiz)
//STRIP001 {
//STRIP001  MovePoint(aAnchor,rSiz);
//STRIP001  SetRectsDirty();
//STRIP001 }

/*N*/ void SdrVirtObj::NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact)
/*N*/ {
/*N*/   rRefObj.NbcResize(rRef-aAnchor,xFact,yFact);
/*N*/   SetRectsDirty();
/*N*/ }

//STRIP001 void SdrVirtObj::NbcRotate(const Point& rRef, long nWink, double sn, double cs)
//STRIP001 {
//STRIP001  rRefObj.NbcRotate(rRef-aAnchor,nWink,sn,cs);
//STRIP001  SetRectsDirty();
//STRIP001 }

//STRIP001 void SdrVirtObj::NbcMirror(const Point& rRef1, const Point& rRef2)
//STRIP001 {
//STRIP001  rRefObj.NbcMirror(rRef1-aAnchor,rRef2-aAnchor);
//STRIP001  SetRectsDirty();
//STRIP001 }

//STRIP001 void SdrVirtObj::NbcShear(const Point& rRef, long nWink, double tn, FASTBOOL bVShear)
//STRIP001 {
//STRIP001  rRefObj.NbcShear(rRef-aAnchor,nWink,tn,bVShear);
//STRIP001  SetRectsDirty();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrVirtObj::Move(const Size& rSiz)
//STRIP001 {
//STRIP001  if (rSiz.Width()!=0 || rSiz.Height()!=0) {
//STRIP001      Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001      SendRepaintBroadcast();
//STRIP001      NbcMove(rSiz);
//STRIP001      SetChanged();
//STRIP001      SendRepaintBroadcast();
//STRIP001      SendUserCall(SDRUSERCALL_MOVEONLY,aBoundRect0);
//STRIP001  }
//STRIP001 }

/*N*/ void SdrVirtObj::Resize(const Point& rRef, const Fraction& xFact, const Fraction& yFact)
/*N*/ {
/*N*/   if (xFact.GetNumerator()!=xFact.GetDenominator() || yFact.GetNumerator()!=yFact.GetDenominator()) {
/*N*/       Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
/*N*/       rRefObj.Resize(rRef-aAnchor,xFact,yFact);
/*N*/       SetRectsDirty();
/*N*/       SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
/*N*/   }
/*N*/ }

//STRIP001 void SdrVirtObj::Rotate(const Point& rRef, long nWink, double sn, double cs)
//STRIP001 {
//STRIP001  if (nWink!=0) {
//STRIP001      Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001      rRefObj.Rotate(rRef-aAnchor,nWink,sn,cs);
//STRIP001      SetRectsDirty();
//STRIP001      SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrVirtObj::Mirror(const Point& rRef1, const Point& rRef2)
//STRIP001 {
//STRIP001  Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001  rRefObj.Mirror(rRef1-aAnchor,rRef2-aAnchor);
//STRIP001  SetRectsDirty();
//STRIP001  SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001 }

//STRIP001 void SdrVirtObj::Shear(const Point& rRef, long nWink, double tn, FASTBOOL bVShear)
//STRIP001 {
//STRIP001  if (nWink!=0) {
//STRIP001      Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001      rRefObj.Shear(rRef-aAnchor,nWink,tn,bVShear);
//STRIP001      SetRectsDirty();
//STRIP001      SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrVirtObj::RecalcSnapRect()
/*N*/ {
/*N*/   aSnapRect=rRefObj.GetSnapRect();
/*N*/   aSnapRect+=aAnchor;
/*N*/ }

//STRIP001 const Rectangle& SdrVirtObj::GetSnapRect() const
//STRIP001 {
//STRIP001  ((SdrVirtObj*)this)->aSnapRect=rRefObj.GetSnapRect();
//STRIP001  ((SdrVirtObj*)this)->aSnapRect+=aAnchor;
//STRIP001  return aSnapRect;
//STRIP001 }

//STRIP001 void SdrVirtObj::SetSnapRect(const Rectangle& rRect)
//STRIP001 {
//STRIP001  {
//STRIP001      Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001      Rectangle aR(rRect);
//STRIP001      aR-=aAnchor;
//STRIP001      rRefObj.SetSnapRect(aR);
//STRIP001      SetRectsDirty();
//STRIP001      SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrVirtObj::NbcSetSnapRect(const Rectangle& rRect)
//STRIP001 {
//STRIP001  Rectangle aR(rRect);
//STRIP001  aR-=aAnchor;
//STRIP001  SetRectsDirty();
//STRIP001  rRefObj.NbcSetSnapRect(aR);
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 const Rectangle& SdrVirtObj::GetLogicRect() const
//STRIP001 {
//STRIP001  ((SdrVirtObj*)this)->aSnapRect=rRefObj.GetLogicRect();  // !!! Missbrauch von aSnapRect !!!
//STRIP001  ((SdrVirtObj*)this)->aSnapRect+=aAnchor;                // Wenns mal Aerger gibt, muss ein weiteres Rectangle Member her (oder Heap)
//STRIP001  return aSnapRect;
//STRIP001 }

//STRIP001 void SdrVirtObj::SetLogicRect(const Rectangle& rRect)
//STRIP001 {
//STRIP001  Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001  Rectangle aR(rRect);
//STRIP001  aR-=aAnchor;
//STRIP001  rRefObj.SetLogicRect(aR);
//STRIP001  SetRectsDirty();
//STRIP001  SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001 }

//STRIP001 void SdrVirtObj::NbcSetLogicRect(const Rectangle& rRect)
//STRIP001 {
//STRIP001  Rectangle aR(rRect);
//STRIP001  aR-=aAnchor;
//STRIP001  SetRectsDirty();
//STRIP001  rRefObj.NbcSetLogicRect(aR);
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ long SdrVirtObj::GetRotateAngle() const
/*N*/ {
/*N*/   return rRefObj.GetRotateAngle();
/*N*/ }

/*N*/ long SdrVirtObj::GetShearAngle(FASTBOOL bVertical) const
/*N*/ {
/*N*/   return rRefObj.GetShearAngle(bVertical);
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 USHORT SdrVirtObj::GetSnapPointCount() const
//STRIP001 {
//STRIP001  return rRefObj.GetSnapPointCount();
//STRIP001 }

//STRIP001 Point SdrVirtObj::GetSnapPoint(USHORT i) const
//STRIP001 {
//STRIP001  Point aP(rRefObj.GetSnapPoint(i));
//STRIP001  aP+=aAnchor;
//STRIP001  return aP;
//STRIP001 }

//STRIP001 FASTBOOL SdrVirtObj::IsPolyObj() const
//STRIP001 {
//STRIP001  return rRefObj.IsPolyObj();
//STRIP001 }

//STRIP001 USHORT SdrVirtObj::GetPointCount() const
//STRIP001 {
//STRIP001  return rRefObj.GetPointCount();
//STRIP001 }

//STRIP001 const Point& SdrVirtObj::GetPoint(USHORT i) const
//STRIP001 {
//STRIP001  ((SdrVirtObj*)this)->aHack=rRefObj.GetPoint(i);
//STRIP001  ((SdrVirtObj*)this)->aHack+=aAnchor;
//STRIP001  return aHack;
//STRIP001 }

/*N*/ void SdrVirtObj::NbcSetPoint(const Point& rPnt, USHORT i)
/*N*/ {
/*N*/   Point aP(rPnt);
/*N*/   aP-=aAnchor;
/*N*/   rRefObj.SetPoint(aP,i);
/*N*/   SetRectsDirty();
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrObjGeoData* SdrVirtObj::NewGeoData() const
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001
//STRIP001  return rRefObj.NewGeoData();
/*N*/ }

/*N*/ void SdrVirtObj::SaveGeoData(SdrObjGeoData& rGeo) const
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  rRefObj.SaveGeoData(rGeo);
/*N*/ }

/*N*/ void SdrVirtObj::RestGeoData(const SdrObjGeoData& rGeo)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  rRefObj.RestGeoData(rGeo);
//STRIP001  SetRectsDirty();
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 SdrObjGeoData* SdrVirtObj::GetGeoData() const
//STRIP001 {
//STRIP001  return rRefObj.GetGeoData();
//STRIP001 }

//STRIP001 void SdrVirtObj::SetGeoData(const SdrObjGeoData& rGeo)
//STRIP001 {
//STRIP001  Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001  rRefObj.SetGeoData(rGeo);
//STRIP001  SetRectsDirty();
//STRIP001  SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////
// ItemSet access

/*N*/ const SfxItemSet& SdrVirtObj::GetItemSet() const
/*N*/ {
/*N*/   return rRefObj.GetItemSet();
/*N*/ }

/*N*/ SfxItemSet* SdrVirtObj::CreateNewItemSet(SfxItemPool& rPool)
/*N*/ {
/*N*/   return rRefObj.CreateNewItemSet(rPool);
/*N*/ }

//STRIP001 void SdrVirtObj::SetItem( const SfxPoolItem& rItem )
//STRIP001 {
//STRIP001  rRefObj.SetItem(rItem);
//STRIP001 }

//STRIP001 void SdrVirtObj::ClearItem( const sal_uInt16 nWhich )
//STRIP001 {
//STRIP001  rRefObj.ClearItem(nWhich);
//STRIP001 }

//STRIP001 void SdrVirtObj::SetItemSet( const SfxItemSet& rSet )
//STRIP001 {
//STRIP001  rRefObj.SetItemSet(rSet);
//STRIP001 }

//STRIP001 void SdrVirtObj::BroadcastItemChange(const SdrBroadcastItemChange& rChange)
//STRIP001 {
//STRIP001  rRefObj.BroadcastItemChange(rChange);
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////
// private support routines for ItemSet access
//STRIP001 BOOL SdrVirtObj::AllowItemChange(const sal_uInt16 nWhich, const SfxPoolItem* pNewItem) const
//STRIP001 {
//STRIP001  return rRefObj.AllowItemChange(nWhich, pNewItem);
//STRIP001 }

//STRIP001 void SdrVirtObj::ItemChange(const sal_uInt16 nWhich, const SfxPoolItem* pNewItem)
//STRIP001 {
//STRIP001  rRefObj.ItemChange(nWhich, pNewItem);
//STRIP001 }

//STRIP001 void SdrVirtObj::ItemSetChanged(const SfxItemSet& rSet)
//STRIP001 {
//STRIP001  rRefObj.ItemSetChanged(rSet);
//STRIP001 }

//STRIP001 void SdrVirtObj::PostItemChange(const sal_uInt16 nWhich)
//STRIP001 {
//STRIP001  rRefObj.PostItemChange(nWhich);
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////
// pre- and postprocessing for objects for saving

/*N*/ void SdrVirtObj::PreSave()
/*N*/ {
/*N*/ }

/*N*/ void SdrVirtObj::PostSave()
/*N*/ {
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 SfxStyleSheet* SdrVirtObj::GetStyleSheet() const
//STRIP001 {
//STRIP001  return rRefObj.GetStyleSheet();
//STRIP001 }

/*N*/ void SdrVirtObj::SetStyleSheet(SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  rRefObj.SetStyleSheet(pNewStyleSheet,bDontRemoveHardAttr);
/*N*/ }

/*N*/ void SdrVirtObj::NbcSetStyleSheet(SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr)
/*N*/ {
/*N*/   rRefObj.NbcSetStyleSheet(pNewStyleSheet,bDontRemoveHardAttr);
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrVirtObj::NbcReformatText()
//STRIP001 {
//STRIP001  rRefObj.NbcReformatText();
//STRIP001 }

//STRIP001 void SdrVirtObj::ReformatText()
//STRIP001 {
//STRIP001  rRefObj.ReformatText();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 FASTBOOL SdrVirtObj::HasMacro() const
//STRIP001 {
//STRIP001  return rRefObj.HasMacro();
//STRIP001 }

//STRIP001 SdrObject* SdrVirtObj::CheckMacroHit(const SdrObjMacroHitRec& rRec) const
//STRIP001 {
//STRIP001  return rRefObj.CheckMacroHit(rRec); // Todo: Positionsversatz
//STRIP001 }

//STRIP001 Pointer SdrVirtObj::GetMacroPointer(const SdrObjMacroHitRec& rRec) const
//STRIP001 {
//STRIP001  return rRefObj.GetMacroPointer(rRec); // Todo: Positionsversatz
//STRIP001 }

//STRIP001 void SdrVirtObj::PaintMacro(ExtOutputDevice& rXOut, const Rectangle& rDirtyRect, const SdrObjMacroHitRec& rRec) const
//STRIP001 {
//STRIP001  rRefObj.PaintMacro(rXOut,rDirtyRect,rRec); // Todo: Positionsversatz
//STRIP001 }

//STRIP001 FASTBOOL SdrVirtObj::DoMacro(const SdrObjMacroHitRec& rRec)
//STRIP001 {
//STRIP001  return rRefObj.DoMacro(rRec); // Todo: Positionsversatz
//STRIP001 }

//STRIP001 XubString SdrVirtObj::GetMacroPopupComment(const SdrObjMacroHitRec& rRec) const
//STRIP001 {
//STRIP001  return rRefObj.GetMacroPopupComment(rRec); // Todo: Positionsversatz
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*?*/ void SdrVirtObj::WriteData(SvStream& rOut) const
/*?*/ {
/*?*/   SdrDownCompat aCompat(rOut,STREAM_WRITE); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*?*/ #ifdef DBG_UTIL
/*?*/   aCompat.SetID("SdrVirtObj");
/*?*/ #endif
/*?*/   // fehlende Implementation
/*?*/   rOut<<aAnchor;
/*?*/ }

/*?*/ void SdrVirtObj::ReadData(const SdrObjIOHeader& rHead, SvStream& rIn)
/*?*/ {
/*?*/   if (rIn.GetError()!=0) return;
/*?*/   if (rHead.GetVersion()>=4) {
/*?*/       SdrDownCompat aCompat(rIn,STREAM_READ); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*?*/ #ifdef DBG_UTIL
/*?*/       aCompat.SetID("SdrVirtObj");
/*?*/ #endif
/*?*/       // fehlende Implementation
/*?*/       rIn>>aAnchor;
/*?*/   } else {
/*?*/       rIn>>aAnchor;
/*?*/   }
/*?*/ }

/*?*/ void SdrVirtObj::AfterRead()
/*?*/ {
/*?*/   // fehlende Implementation
/*?*/ }

/*?*/ const Point SdrVirtObj::GetOffset() const
/*?*/ {
/*?*/     return Point(0,0);
/*?*/ }
}
