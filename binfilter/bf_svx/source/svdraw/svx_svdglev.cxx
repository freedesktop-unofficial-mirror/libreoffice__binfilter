/*************************************************************************
 *
 *  $RCSfile: svx_svdglev.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 16:22:14 $
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

#include "svdglev.hxx"
#include <math.h>

// auto strip #include "svdundo.hxx"
#include "svdstr.hrc"   // Namen aus der Resource
// auto strip #include "svdglob.hxx"  // StringCache
// auto strip #include "svdpagv.hxx"
// auto strip #include "svdglue.hxx"
// auto strip #include "svdtrans.hxx"
// auto strip #include "svdobj.hxx"
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrGlueEditView::ImpClearVars()
/*N*/ {
/*N*/ }

/*N*/ SdrGlueEditView::SdrGlueEditView(SdrModel* pModel1, OutputDevice* pOut):
/*N*/   SdrPolyEditView(pModel1,pOut)
/*N*/ {
/*N*/   ImpClearVars();
/*N*/ }

/*?*/ SdrGlueEditView::SdrGlueEditView(SdrModel* pModel1, ExtOutputDevice* pXOut):
/*?*/   SdrPolyEditView(pModel1,pXOut)
/*?*/ {
/*?*/   ImpClearVars();
/*?*/ }

/*N*/ SdrGlueEditView::~SdrGlueEditView()
/*N*/ {
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrGlueEditView::ImpDoMarkedGluePoints(PGlueDoFunc pDoFunc, BOOL bConst, const void* p1, const void* p2, const void* p3, const void* p4, const void* p5)
//STRIP001 {
//STRIP001  ULONG nMarkAnz=aMark.GetMarkCount();
//STRIP001  for (ULONG nm=0; nm<nMarkAnz; nm++) {
//STRIP001      SdrMark* pM=aMark.GetMark(nm);
//STRIP001      SdrObject* pObj=pM->GetObj();
//STRIP001      const SdrUShortCont* pPts=pM->GetMarkedGluePoints();
//STRIP001      ULONG nPtAnz=pPts==NULL ? 0 : pPts->GetCount();
//STRIP001      if (nPtAnz!=0) {
//STRIP001          SdrGluePointList* pGPL=NULL;
//STRIP001          if (bConst) {
//STRIP001              const SdrGluePointList* pConstGPL=pObj->GetGluePointList();
//STRIP001              pGPL=(SdrGluePointList*)pConstGPL;
//STRIP001          } else {
//STRIP001              pGPL=pObj->ForceGluePointList();
//STRIP001          }
//STRIP001          if (pGPL!=NULL) {
//STRIP001              if (!bConst) AddUndo(new SdrUndoGeoObj(*pObj));
//STRIP001              for (ULONG nPtNum=0; nPtNum<nPtAnz; nPtNum++) {
//STRIP001                  USHORT nPtId=pPts->GetObject(nPtNum);
//STRIP001                  USHORT nGlueIdx=pGPL->FindGluePoint(nPtId);
//STRIP001                  if (nGlueIdx!=SDRGLUEPOINT_NOTFOUND) {
//STRIP001                      SdrGluePoint& rGP=(*pGPL)[nGlueIdx];
//STRIP001                      (*pDoFunc)(rGP,pObj,p1,p2,p3,p4,p5);
//STRIP001                  }
//STRIP001              }
//STRIP001              if (!bConst) pObj->SendRepaintBroadcast();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if (!bConst && nMarkAnz!=0) pMod->SetChanged();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 static void ImpGetEscDir(SdrGluePoint& rGP, const SdrObject* pObj, const void* pbFirst, const void* pnThisEsc, const void* pnRet, const void*, const void*)
//STRIP001 {
//STRIP001  USHORT& nRet=*(USHORT*)pnRet;
//STRIP001  BOOL& bFirst=*(BOOL*)pbFirst;
//STRIP001  if (nRet!=FUZZY) {
//STRIP001      USHORT nEsc=rGP.GetEscDir();
//STRIP001      BOOL bOn=(nEsc & *(USHORT*)pnThisEsc)!=0;
//STRIP001      if (bFirst) { nRet=bOn; bFirst=FALSE; }
//STRIP001      else if (nRet!=bOn) nRet=FUZZY;
//STRIP001  }
//STRIP001 }

//STRIP001 TRISTATE SdrGlueEditView::IsMarkedGluePointsEscDir(USHORT nThisEsc) const
//STRIP001 {
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  BOOL bFirst=TRUE;
//STRIP001  USHORT nRet=FALSE;
//STRIP001  ((SdrGlueEditView*)this)->ImpDoMarkedGluePoints(ImpGetEscDir,TRUE,&bFirst,&nThisEsc,&nRet);
//STRIP001  return (TRISTATE)nRet;
//STRIP001 }

//STRIP001 static void ImpSetEscDir(SdrGluePoint& rGP, const SdrObject* pObj, const void* pnThisEsc, const void* pbOn, const void*, const void*, const void*)
//STRIP001 {
//STRIP001  USHORT nEsc=rGP.GetEscDir();
//STRIP001  if (*(BOOL*)pbOn) nEsc|=*(USHORT*)pnThisEsc;
//STRIP001  else nEsc&=~*(USHORT*)pnThisEsc;
//STRIP001  rGP.SetEscDir(nEsc);
//STRIP001 }

//STRIP001 void SdrGlueEditView::SetMarkedGluePointsEscDir(USHORT nThisEsc, BOOL bOn)
//STRIP001 {
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  BegUndo(ImpGetResStr(STR_EditSetGlueEscDir),aMark.GetGluePointMarkDescription());
//STRIP001  ImpDoMarkedGluePoints(ImpSetEscDir,FALSE,&nThisEsc,&bOn);
//STRIP001  EndUndo();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 static void ImpGetPercent(SdrGluePoint& rGP, const SdrObject* pObj, const void* pbFirst, const void* pnRet, const void*, const void*, const void*)
//STRIP001 {
//STRIP001  USHORT& nRet=*(USHORT*)pnRet;
//STRIP001  BOOL& bFirst=*(BOOL*)pbFirst;
//STRIP001  if (nRet!=FUZZY) {
//STRIP001      BOOL bOn=rGP.IsPercent();
//STRIP001      if (bFirst) { nRet=bOn; bFirst=FALSE; }
//STRIP001      else if (nRet!=bOn) nRet=FUZZY;
//STRIP001  }
//STRIP001 }

//STRIP001 TRISTATE SdrGlueEditView::IsMarkedGluePointsPercent() const
//STRIP001 {
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  BOOL bFirst=TRUE;
//STRIP001  USHORT nRet=TRUE;
//STRIP001  ((SdrGlueEditView*)this)->ImpDoMarkedGluePoints(ImpGetPercent,TRUE,&bFirst,&nRet);
//STRIP001  return (TRISTATE)nRet;
//STRIP001 }

//STRIP001 static void ImpSetPercent(SdrGluePoint& rGP, const SdrObject* pObj, const void* pbOn, const void*, const void*, const void*, const void*)
//STRIP001 {
//STRIP001  Point aPos(rGP.GetAbsolutePos(*pObj));
//STRIP001  rGP.SetPercent(*(BOOL*)pbOn);
//STRIP001  rGP.SetAbsolutePos(aPos,*pObj);
//STRIP001 }

//STRIP001 void SdrGlueEditView::SetMarkedGluePointsPercent(BOOL bOn)
//STRIP001 {
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  BegUndo(ImpGetResStr(STR_EditSetGluePercent),aMark.GetGluePointMarkDescription());
//STRIP001  ImpDoMarkedGluePoints(ImpSetPercent,FALSE,&bOn);
//STRIP001  EndUndo();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 static void ImpGetAlign(SdrGluePoint& rGP, const SdrObject* pObj, const void* pbFirst, const void* pbDontCare, const void* pbVert, const void* pnRet, const void*)
//STRIP001 {
//STRIP001  USHORT& nRet=*(USHORT*)pnRet;
//STRIP001  BOOL& bFirst=*(BOOL*)pbFirst;
//STRIP001  BOOL& bDontCare=*(BOOL*)pbDontCare;
//STRIP001  BOOL bVert=*(BOOL*)pbVert;
//STRIP001  if (!bDontCare) {
//STRIP001      USHORT nAlg=0;
//STRIP001      if (bVert) {
//STRIP001          nAlg=rGP.GetVertAlign();
//STRIP001      } else {
//STRIP001          nAlg=rGP.GetHorzAlign();
//STRIP001      }
//STRIP001      if (bFirst) { nRet=nAlg; bFirst=FALSE; }
//STRIP001      else if (nRet!=nAlg) {
//STRIP001          if (bVert) {
//STRIP001              nRet=SDRVERTALIGN_DONTCARE;
//STRIP001          } else {
//STRIP001              nRet=SDRHORZALIGN_DONTCARE;
//STRIP001          }
//STRIP001          bDontCare=TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 USHORT SdrGlueEditView::GetMarkedGluePointsAlign(BOOL bVert) const
//STRIP001 {
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  BOOL bFirst=TRUE;
//STRIP001  BOOL bDontCare=FALSE;
//STRIP001  USHORT nRet=0;
//STRIP001  ((SdrGlueEditView*)this)->ImpDoMarkedGluePoints(ImpGetAlign,TRUE,&bFirst,&bDontCare,&bVert,&nRet);
//STRIP001  return nRet;
//STRIP001 }

//STRIP001 static void ImpSetAlign(SdrGluePoint& rGP, const SdrObject* pObj, const void* pbVert, const void* pnAlign, const void*, const void*, const void*)
//STRIP001 {
//STRIP001  Point aPos(rGP.GetAbsolutePos(*pObj));
//STRIP001  if (*(BOOL*)pbVert) { // bVert?
//STRIP001      rGP.SetVertAlign(*(USHORT*)pnAlign);
//STRIP001  } else {
//STRIP001      rGP.SetHorzAlign(*(USHORT*)pnAlign);
//STRIP001  }
//STRIP001  rGP.SetAbsolutePos(aPos,*pObj);
//STRIP001 }

//STRIP001 void SdrGlueEditView::SetMarkedGluePointsAlign(BOOL bVert, USHORT nAlign)
//STRIP001 {
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  BegUndo(ImpGetResStr(STR_EditSetGlueAlign),aMark.GetGluePointMarkDescription());
//STRIP001  ImpDoMarkedGluePoints(ImpSetAlign,FALSE,&bVert,&nAlign);
//STRIP001  EndUndo();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 BOOL SdrGlueEditView::IsDeleteMarkedGluePointsPossible() const
//STRIP001 {
//STRIP001  return HasMarkedGluePoints();
//STRIP001 }

//STRIP001 void SdrGlueEditView::DeleteMarkedGluePoints()
//STRIP001 {
//STRIP001  BrkAction();
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  BegUndo(ImpGetResStr(STR_EditDelete),aMark.GetGluePointMarkDescription(),SDRREPFUNC_OBJ_DELETE);
//STRIP001  ULONG nMarkAnz=aMark.GetMarkCount();
//STRIP001  for (ULONG nm=0; nm<nMarkAnz; nm++) {
//STRIP001      SdrMark* pM=aMark.GetMark(nm);
//STRIP001      SdrObject* pObj=pM->GetObj();
//STRIP001      const SdrUShortCont* pPts=pM->GetMarkedGluePoints();
//STRIP001      ULONG nPtAnz=pPts==NULL ? 0 : pPts->GetCount();
//STRIP001      if (nPtAnz!=0) {
//STRIP001          SdrGluePointList* pGPL=pObj->ForceGluePointList();
//STRIP001          if (pGPL!=NULL) {
//STRIP001              AddUndo(new SdrUndoGeoObj(*pObj));
//STRIP001              for (ULONG nPtNum=0; nPtNum<nPtAnz; nPtNum++) {
//STRIP001                  USHORT nPtId=pPts->GetObject(nPtNum);
//STRIP001                  USHORT nGlueIdx=pGPL->FindGluePoint(nPtId);
//STRIP001                  if (nGlueIdx!=SDRGLUEPOINT_NOTFOUND) {
//STRIP001                      pGPL->Delete(nGlueIdx);
//STRIP001                  }
//STRIP001              }
//STRIP001              pObj->SendRepaintBroadcast();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  EndUndo();
//STRIP001  UnmarkAllGluePoints();
//STRIP001  if (nMarkAnz!=0) pMod->SetChanged();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrGlueEditView::ImpCopyMarkedGluePoints()
//STRIP001 {
//STRIP001  BegUndo();
//STRIP001  ULONG nMarkAnz=aMark.GetMarkCount();
//STRIP001  for (ULONG nm=0; nm<nMarkAnz; nm++) {
//STRIP001      SdrMark* pM=aMark.GetMark(nm);
//STRIP001      SdrObject* pObj=pM->GetObj();
//STRIP001      SdrUShortCont* pPts=pM->GetMarkedGluePoints();
//STRIP001      SdrGluePointList* pGPL=pObj->ForceGluePointList();
//STRIP001      ULONG nPtAnz=pPts==NULL ? 0 : pPts->GetCount();
//STRIP001      if (nPtAnz!=0 && pGPL!=NULL) {
//STRIP001          AddUndo(new SdrUndoGeoObj(*pObj));
//STRIP001          for (ULONG nPtNum=0; nPtNum<nPtAnz; nPtNum++) {
//STRIP001              USHORT nPtId=pPts->GetObject(nPtNum);
//STRIP001              USHORT nGlueIdx=pGPL->FindGluePoint(nPtId);
//STRIP001              if (nGlueIdx!=SDRGLUEPOINT_NOTFOUND) {
//STRIP001                  SdrGluePoint aNewGP((*pGPL)[nGlueIdx]);  // GluePoint klonen
//STRIP001                  USHORT nNewIdx=pGPL->Insert(aNewGP);     // und einfuegen
//STRIP001                  USHORT nNewId=(*pGPL)[nNewIdx].GetId();  // Id des neuen GluePoints ermitteln
//STRIP001                  pPts->Replace(nNewId,nPtNum);            // und diesen markieren (anstelle des alten)
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  EndUndo();
//STRIP001  if (nMarkAnz!=0) pMod->SetChanged();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrGlueEditView::ImpTransformMarkedGluePoints(PGlueTrFunc pTrFunc, const void* p1, const void* p2, const void* p3, const void* p4, const void* p5)
//STRIP001 {
//STRIP001  ULONG nMarkAnz=aMark.GetMarkCount();
//STRIP001  for (ULONG nm=0; nm<nMarkAnz; nm++) {
//STRIP001      SdrMark* pM=aMark.GetMark(nm);
//STRIP001      SdrObject* pObj=pM->GetObj();
//STRIP001      const SdrUShortCont* pPts=pM->GetMarkedGluePoints();
//STRIP001      Point aPvOfs(pM->GetPageView()->GetOffset());
//STRIP001      ULONG nPtAnz=pPts==NULL ? 0 : pPts->GetCount();
//STRIP001      if (nPtAnz!=0) {
//STRIP001          SdrGluePointList* pGPL=pObj->ForceGluePointList();
//STRIP001          if (pGPL!=NULL) {
//STRIP001              AddUndo(new SdrUndoGeoObj(*pObj));
//STRIP001              for (ULONG nPtNum=0; nPtNum<nPtAnz; nPtNum++) {
//STRIP001                  USHORT nPtId=pPts->GetObject(nPtNum);
//STRIP001                  USHORT nGlueIdx=pGPL->FindGluePoint(nPtId);
//STRIP001                  if (nGlueIdx!=SDRGLUEPOINT_NOTFOUND) {
//STRIP001                      SdrGluePoint& rGP=(*pGPL)[nGlueIdx];
//STRIP001                      Point aPos(rGP.GetAbsolutePos(*pObj));
//STRIP001                      aPos+=aPvOfs;
//STRIP001                      (*pTrFunc)(aPos,p1,p2,p3,p4,p5);
//STRIP001                      aPos-=aPvOfs;
//STRIP001                      rGP.SetAbsolutePos(aPos,*pObj);
//STRIP001                  }
//STRIP001              }
//STRIP001              pObj->SendRepaintBroadcast();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if (nMarkAnz!=0) pMod->SetChanged();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 static void ImpMove(Point& rPt, const void* p1, const void* p2, const void* p3, const void* p4, const void* p5)
//STRIP001 {
//STRIP001  rPt.X()+=((const Size*)p1)->Width();
//STRIP001  rPt.Y()+=((const Size*)p1)->Height();
//STRIP001 }

//STRIP001 void SdrGlueEditView::MoveMarkedGluePoints(const Size& rSiz, BOOL bCopy)
//STRIP001 {
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  XubString aStr(ImpGetResStr(STR_EditMove));
//STRIP001  if (bCopy) aStr+=ImpGetResStr(STR_EditWithCopy);
//STRIP001  BegUndo(aStr,aMark.GetGluePointMarkDescription(),SDRREPFUNC_OBJ_MOVE);
//STRIP001  if (bCopy) ImpCopyMarkedGluePoints();
//STRIP001  ImpTransformMarkedGluePoints(ImpMove,&rSiz);
//STRIP001  EndUndo();
//STRIP001  AdjustMarkHdl();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 static void ImpResize(Point& rPt, const void* p1, const void* p2, const void* p3, const void* p4, const void* p5)
//STRIP001 {
//STRIP001  ResizePoint(rPt,*(const Point*)p1,*(const Fraction*)p2,*(const Fraction*)p3);
//STRIP001 }

//STRIP001 void SdrGlueEditView::ResizeMarkedGluePoints(const Point& rRef, const Fraction& xFact, const Fraction& yFact, BOOL bCopy)
//STRIP001 {
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  XubString aStr(ImpGetResStr(STR_EditResize));
//STRIP001  if (bCopy) aStr+=ImpGetResStr(STR_EditWithCopy);
//STRIP001  BegUndo(aStr,aMark.GetGluePointMarkDescription(),SDRREPFUNC_OBJ_RESIZE);
//STRIP001  if (bCopy) ImpCopyMarkedGluePoints();
//STRIP001  ImpTransformMarkedGluePoints(ImpResize,&rRef,&xFact,&yFact);
//STRIP001  EndUndo();
//STRIP001  AdjustMarkHdl();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 static void ImpRotate(Point& rPt, const void* p1, const void* p2, const void* p3, const void* p4, const void* p5)
//STRIP001 {
//STRIP001  RotatePoint(rPt,*(const Point*)p1,*(const double*)p3,*(const double*)p4);
//STRIP001 }

//STRIP001 void SdrGlueEditView::RotateMarkedGluePoints(const Point& rRef, long nWink, BOOL bCopy)
//STRIP001 {
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  XubString aStr(ImpGetResStr(STR_EditRotate));
//STRIP001  if (bCopy) aStr+=ImpGetResStr(STR_EditWithCopy);
//STRIP001  BegUndo(aStr,aMark.GetGluePointMarkDescription(),SDRREPFUNC_OBJ_ROTATE);
//STRIP001  if (bCopy) ImpCopyMarkedGluePoints();
//STRIP001  double nSin=sin(nWink*nPi180);
//STRIP001  double nCos=cos(nWink*nPi180);
//STRIP001  ImpTransformMarkedGluePoints(ImpRotate,&rRef,&nWink,&nSin,&nCos);
//STRIP001  EndUndo();
//STRIP001  AdjustMarkHdl();
//STRIP001 }

}
