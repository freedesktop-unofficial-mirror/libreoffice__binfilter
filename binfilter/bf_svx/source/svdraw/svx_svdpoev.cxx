/*************************************************************************
 *
 *  $RCSfile: svx_svdpoev.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:46:28 $
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

#include "svdpoev.hxx"
#include <math.h>
#include "svdpagv.hxx"
#include "svdpage.hxx"
#include "svdopath.hxx"
#include "svdundo.hxx"
#include "svdstr.hrc"   // Namen aus der Resource
#include "svdglob.hxx"  // StringCache
#include "svdtrans.hxx"
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrPolyEditView::ImpResetPolyPossibilityFlags()
/*N*/ {
/*N*/   eMarkedPointsSmooth=SDRPATHSMOOTH_DONTCARE;
/*N*/   eMarkedSegmentsKind=SDRPATHSEGMENT_DONTCARE;
/*N*/   bSetMarkedPointsSmoothPossible=FALSE;
/*N*/   bSetMarkedSegmentsKindPossible=FALSE;
/*N*/ }

/*N*/ void SdrPolyEditView::ImpClearVars()
/*N*/ {
/*N*/   ImpResetPolyPossibilityFlags();
/*N*/ }

/*N*/ SdrPolyEditView::SdrPolyEditView(SdrModel* pModel1, OutputDevice* pOut):
/*N*/   SdrEditView(pModel1,pOut)
/*N*/ {
/*N*/   ImpClearVars();
/*N*/ }

/*?*/ SdrPolyEditView::SdrPolyEditView(SdrModel* pModel1, ExtOutputDevice* pXOut):
/*?*/   SdrEditView(pModel1,pXOut)
/*?*/ {
/*?*/   ImpClearVars();
/*?*/ }

/*N*/ SdrPolyEditView::~SdrPolyEditView()
/*N*/ {
/*N*/ }

/*N*/ void SdrPolyEditView::ImpCheckPolyPossibilities()
/*N*/ {
/*N*/   ImpResetPolyPossibilityFlags();
/*N*/   ULONG nMarkAnz=aMark.GetMarkCount();
/*N*/   if (nMarkAnz>0 && !ImpIsFrameHandles()) {
/*?*/       BOOL bReadOnly=FALSE;
/*?*/       BOOL b1stSmooth=TRUE;
/*?*/       BOOL b1stSegm=TRUE;
/*?*/       BOOL bCurve=FALSE;
/*?*/       BOOL bSmoothFuz=FALSE;
/*?*/       BOOL bSegmFuz=FALSE;
/*?*/       XPolyFlags eSmooth=XPOLY_NORMAL;
/*?*/
/*?*/       for (ULONG nMarkNum=0; nMarkNum<nMarkAnz; nMarkNum++) {
/*?*/           SdrMark* pM=aMark.GetMark(nMarkNum);
/*?*/           SdrObject* pObj=pM->GetObj();
/*?*/           SdrUShortCont* pPts=pM->GetMarkedPoints();
/*?*/           SdrPathObj* pPath=PTR_CAST(SdrPathObj,pObj);
/*?*/           if (pPath!=NULL && pPts!=NULL) {
/*?*/               ULONG nMarkedPntAnz=pPts->GetCount();
/*?*/               if (nMarkedPntAnz!=0) {
/*?*/                   BOOL bClosed=pPath->IsClosed();
/*?*/                   bSetMarkedPointsSmoothPossible=TRUE;
/*?*/                   if (bClosed) bSetMarkedSegmentsKindPossible=TRUE;
/*?*/                   const XPolyPolygon& rXPP=pPath->GetPathPoly();
/*?*/                   for (USHORT nMarkedPntNum=0; nMarkedPntNum<(USHORT)nMarkedPntAnz; nMarkedPntNum++) {
/*?*/                       USHORT nNum=pPts->GetObject(nMarkedPntNum);
/*?*/                       USHORT nPolyNum=0,nPntNum=0;
/*?*/                       if (pPath->FindPolyPnt(nNum,nPolyNum,nPntNum,FALSE)) {
/*?*/                           const XPolygon& rXP=rXPP[nPolyNum];
/*?*/                           BOOL bCanSegment=bClosed || nPntNum<rXP.GetPointCount()-1;
/*?*/
/*?*/                           if (!bSetMarkedSegmentsKindPossible && bCanSegment) {
/*?*/                               bSetMarkedSegmentsKindPossible=TRUE;
/*?*/                           }
/*?*/                           if (!bSmoothFuz) {
/*?*/                               if (b1stSmooth) {
/*?*/                                   b1stSmooth=FALSE;
/*?*/                                   eSmooth=rXP.GetFlags(nPntNum);
/*?*/                               } else {
/*?*/                                   bSmoothFuz=eSmooth!=rXP.GetFlags(nPntNum);
/*?*/                               }
/*?*/                           }
/*?*/                           if (!bSegmFuz) {
/*?*/                               if (bCanSegment) {
/*?*/                                   BOOL bCrv=rXP.IsControl(nPntNum+1);
/*?*/                                   if (b1stSegm) {
/*?*/                                       b1stSegm=FALSE;
/*?*/                                       bCurve=bCrv;
/*?*/                                   } else {
/*?*/                                       bSegmFuz=bCrv!=bCurve;
/*?*/                                   }
/*?*/                               }
/*?*/                           }
/*?*/                       }
/*?*/                   }
/*?*/                   if (!b1stSmooth && !bSmoothFuz) {
/*?*/                       if (eSmooth==XPOLY_NORMAL) eMarkedPointsSmooth=SDRPATHSMOOTH_ANGULAR;
/*?*/                       if (eSmooth==XPOLY_SMOOTH) eMarkedPointsSmooth=SDRPATHSMOOTH_ASYMMETRIC;
/*?*/                       if (eSmooth==XPOLY_SYMMTR) eMarkedPointsSmooth=SDRPATHSMOOTH_SYMMETRIC;
/*?*/                   }
/*?*/                   if (!b1stSegm && !bSegmFuz) {
/*?*/                       eMarkedSegmentsKind= bCurve ? SDRPATHSEGMENT_CURVE : SDRPATHSEGMENT_LINE;
/*?*/                   }
/*?*/               }
/*?*/           }
/*?*/       }
/*?*/       if (bReadOnly) {
/*?*/           bSetMarkedPointsSmoothPossible=FALSE;
/*?*/           bSetMarkedSegmentsKindPossible=FALSE;
/*?*/       }
/*N*/   }
/*N*/ }

//STRIP001 void SdrPolyEditView::SetMarkedPointsSmooth(SdrPathSmoothKind eKind)
//STRIP001 {
//STRIP001  XPolyFlags eFlags;
//STRIP001  if (eKind==SDRPATHSMOOTH_ANGULAR) eFlags=XPOLY_NORMAL;
//STRIP001  else if (eKind==SDRPATHSMOOTH_ASYMMETRIC) eFlags=XPOLY_SMOOTH;
//STRIP001  else if (eKind==SDRPATHSMOOTH_SYMMETRIC) eFlags=XPOLY_SYMMTR;
//STRIP001  else return;
//STRIP001  if (HasMarkedPoints()) {
//STRIP001      aMark.ForceSort();
//STRIP001      BegUndo(ImpGetResStr(STR_EditSetPointsSmooth),aMark.GetPointMarkDescription()/*,SDRREPFUNC_OBJ_*/);
//STRIP001      ULONG nMarkAnz=aMark.GetMarkCount();
//STRIP001      for (ULONG nMarkNum=nMarkAnz; nMarkNum>0;) {
//STRIP001          nMarkNum--;
//STRIP001          SdrMark* pM=aMark.GetMark(nMarkNum);
//STRIP001          SdrUShortCont* pPts=pM->GetMarkedPoints();
//STRIP001          SdrObject* pObj=pM->GetObj();
//STRIP001          SdrPathObj* pPath=PTR_CAST(SdrPathObj,pObj);
//STRIP001          if (pPts!=NULL && pPath!=NULL) {
//STRIP001              pPts->ForceSort();
//STRIP001              AddUndo(new SdrUndoGeoObj(*pPath));
//STRIP001              Rectangle aBoundRect0; if (pPath->pUserCall!=NULL) aBoundRect0=pPath->GetBoundRect();
//STRIP001              pPath->SendRepaintBroadcast();
//STRIP001              for (ULONG nNum=pPts->GetCount(); nNum>0;) {
//STRIP001                  nNum--;
//STRIP001                  USHORT nPtNum=pPts->GetObject(nNum);
//STRIP001                  USHORT nPolyNum,nPntNum;
//STRIP001                  if (pPath->FindPolyPnt(nPtNum,nPolyNum,nPntNum,FALSE)) {
//STRIP001                      pPath->ImpSetSmoothFlag(nPolyNum,nPntNum,eFlags);
//STRIP001                  }
//STRIP001              }
//STRIP001              // die folgenden 5 Statements sowie das obige SendRepaintBroadcast,
//STRIP001              // da ich das wesentlich schnellere ImpSetSmoothFlag verwende.
//STRIP001              pPath->ImpForceKind(); // ebenso impl. an der SdrPolyEditView
//STRIP001              pPath->SetRectsDirty();
//STRIP001              pPath->SetChanged();
//STRIP001              pPath->SendRepaintBroadcast();
//STRIP001              pPath->SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001          }
//STRIP001      }
//STRIP001      EndUndo();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrPolyEditView::SetMarkedSegmentsKind(SdrPathSegmentKind eKind)
//STRIP001 {
//STRIP001  SdrPathType eType;
//STRIP001  if (eKind==SDRPATHSEGMENT_LINE) eType=SDRPATH_LINE;
//STRIP001  else if (eKind==SDRPATHSEGMENT_CURVE) eType=SDRPATH_CURVE;
//STRIP001  else if (eKind==SDRPATHSEGMENT_TOGGLE) eType=SDRPATH_NONE;
//STRIP001  else return;
//STRIP001  if (HasMarkedPoints()) {
//STRIP001      aMark.ForceSort();
//STRIP001      BegUndo(ImpGetResStr(STR_EditSetSegmentsKind),aMark.GetPointMarkDescription()/*,SDRREPFUNC_OBJ_*/);
//STRIP001      ULONG nMarkAnz=aMark.GetMarkCount();
//STRIP001      for (ULONG nMarkNum=nMarkAnz; nMarkNum>0;) {
//STRIP001          nMarkNum--;
//STRIP001          SdrMark* pM=aMark.GetMark(nMarkNum);
//STRIP001          SdrUShortCont* pPts=pM->GetMarkedPoints();
//STRIP001          SdrObject* pObj=pM->GetObj();
//STRIP001          SdrPathObj* pPath=PTR_CAST(SdrPathObj,pObj);
//STRIP001          if (pPts!=NULL && pPath!=NULL) {
//STRIP001              pPts->ForceSort();
//STRIP001              AddUndo(new SdrUndoGeoObj(*pPath));
//STRIP001              Rectangle aBoundRect0; if (pPath->pUserCall!=NULL) aBoundRect0=pPath->GetBoundRect();
//STRIP001              pPath->SendRepaintBroadcast();
//STRIP001              for (ULONG nNum=pPts->GetCount(); nNum>0;) {   // hier muss ich mir noch den 1. und letzten Punkt
//STRIP001                  nNum--;                         // eines jeden Polygons merken (fehlende Impl.) !!!
//STRIP001                  USHORT nPtNum=pPts->GetObject(nNum);
//STRIP001                  USHORT nPolyNum,nPntNum;
//STRIP001                  if (pPath->FindPolyPnt(nPtNum,nPolyNum,nPntNum,FALSE)) {
//STRIP001                      pPath->ImpConvertSegment(nPolyNum,nPntNum,eType,FALSE);
//STRIP001                  }
//STRIP001              }
//STRIP001              // die folgenden 5 Statements sowie das obige SendRepaintBroadcast,
//STRIP001              // da ich das wesentlich schnellere ImpSetSmoothFlag verwende.
//STRIP001              pPath->ImpForceKind(); // ebenso impl. an der SdrPolyEditView
//STRIP001              pPath->SetRectsDirty();
//STRIP001              pPath->SetChanged();
//STRIP001              pPath->SendRepaintBroadcast();
//STRIP001              pPath->SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001          }
//STRIP001      }
//STRIP001      EndUndo();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrPolyEditView::DeleteMarkedPoints()
//STRIP001 {
//STRIP001  if (HasMarkedPoints()) {
//STRIP001      BrkAction();
//STRIP001      aMark.ForceSort();
//STRIP001      ULONG nMarkAnz=aMark.GetMarkCount();
//STRIP001      // Description
//STRIP001      BegUndo(ImpGetResStr(STR_EditDelete),aMark.GetPointMarkDescription(),SDRREPFUNC_OBJ_DELETE);
//STRIP001      // und nun das eigentliche loeschen
//STRIP001      ULONG nObjDelCount=0;
//STRIP001      for (ULONG nMarkNum=nMarkAnz; nMarkNum>0;) {
//STRIP001          nMarkNum--;
//STRIP001          SdrMark* pM=aMark.GetMark(nMarkNum);
//STRIP001          SdrUShortCont* pPts=pM->GetMarkedPoints();
//STRIP001          SdrObject* pObj=pM->GetObj();
//STRIP001          BOOL bDel=FALSE;
//STRIP001          if (pPts!=NULL) {
//STRIP001              pPts->ForceSort();
//STRIP001              ULONG nMarkPtsAnz=pPts->GetCount();
//STRIP001              if (nMarkPtsAnz!=0) {
//STRIP001                  AddUndo(new SdrUndoGeoObj(*pObj));
//STRIP001
//STRIP001                  if(nMarkPtsAnz > 5)
//STRIP001                  {
//STRIP001                      Rectangle aBoundRect0(pObj->GetBoundRect());
//STRIP001                      pObj->SendRepaintBroadcast();
//STRIP001                      for (ULONG i=nMarkPtsAnz; i>0 && !bDel;)
//STRIP001                      {
//STRIP001                          i--;
//STRIP001                          bDel=!pObj->NbcDelPoint(pPts->GetObject(i));
//STRIP001                      }
//STRIP001                      if(!bDel)
//STRIP001                      {
//STRIP001                          pObj->SetChanged();
//STRIP001                          pObj->SendRepaintBroadcast();
//STRIP001                          pObj->SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001                      }
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      for (ULONG i=nMarkPtsAnz; i>0 && !bDel;)
//STRIP001                      {
//STRIP001                          i--;
//STRIP001                          bDel=!pObj->DelPoint(pPts->GetObject(i));
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          if (bDel) {
//STRIP001              AddUndo(new SdrUndoDelObj(*pObj));
//STRIP001              pM->GetPageView()->GetObjList()->RemoveObject(pObj->GetOrdNum());
//STRIP001              nObjDelCount++;
//STRIP001          }
//STRIP001      }
//STRIP001      EndUndo();
//STRIP001      UnmarkAllPoints();
//STRIP001      MarkListHasChanged();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrPolyEditView::RipUpAtMarkedPoints()
//STRIP001 {
//STRIP001  if (HasMarkedPoints()) {
//STRIP001      aMark.ForceSort();
//STRIP001      ULONG nMarkAnz=aMark.GetMarkCount();
//STRIP001      BegUndo(ImpGetResStr(STR_EditRipUp),aMark.GetPointMarkDescription()/*,SDRREPFUNC_OBJ_MOVE*/);
//STRIP001      for (ULONG nMarkNum=nMarkAnz; nMarkNum>0;) {
//STRIP001          nMarkNum--;
//STRIP001          SdrMark* pM=aMark.GetMark(nMarkNum);
//STRIP001          SdrUShortCont* pPts=pM->GetMarkedPoints();
//STRIP001          SdrObject* pObj=pM->GetObj();
//STRIP001          if (pPts!=NULL) {
//STRIP001              pPts->ForceSort();
//STRIP001              AddUndo(new SdrUndoGeoObj(*pObj));
//STRIP001              BOOL bKorregFlag=FALSE;
//STRIP001              BOOL bInsAny=FALSE;
//STRIP001              ULONG nMarkPtsAnz=pPts->GetCount();
//STRIP001              USHORT nMax=pObj->GetHdlCount();
//STRIP001              for (ULONG i=nMarkPtsAnz; i>0;) {
//STRIP001                  i--;
//STRIP001                  USHORT nNewPt0Idx=0;
//STRIP001                  SdrObject* pNeuObj=pObj->RipPoint(pPts->GetObject(i),nNewPt0Idx);
//STRIP001                  if (pNeuObj!=NULL) {
//STRIP001                      bInsAny=TRUE;
//STRIP001                      SdrInsertReason aReason(SDRREASON_VIEWCALL,pObj);
//STRIP001                      pM->GetPageView()->GetObjList()->InsertObject(pNeuObj,pObj->GetOrdNum()+1,&aReason);
//STRIP001                      AddUndo(new SdrUndoNewObj(*pNeuObj));
//STRIP001                      MarkObj(pNeuObj,pM->GetPageView(),FALSE,TRUE);
//STRIP001                  }
//STRIP001                  if (nNewPt0Idx!=0) { // Korrektur notwendig?
//STRIP001                      DBG_ASSERT(bKorregFlag==FALSE,"Mehrfache Indexkorrektur bei SdrPolyEditView::RipUp()");
//STRIP001                      if (!bKorregFlag) {
//STRIP001                          bKorregFlag=TRUE;
//STRIP001                          for (ULONG nBla=0; nBla<nMarkPtsAnz; nBla++) {
//STRIP001                              USHORT nPntNum=pPts->GetObject(nBla);
//STRIP001                              nPntNum+=nNewPt0Idx;
//STRIP001                              if (nPntNum>=nMax) nPntNum-=nMax;
//STRIP001                              pPts->Replace(nPntNum,nBla);
//STRIP001                          }
//STRIP001                          i=nMarkPtsAnz; // ... und nochmal von vorn
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      UnmarkAllPoints();
//STRIP001      EndUndo();
//STRIP001      MarkListHasChanged();
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL SdrPolyEditView::IsRipUpAtMarkedPointsPossible() const
//STRIP001 {
//STRIP001  BOOL bRet=FALSE;
//STRIP001  ULONG nMarkAnz=aMark.GetMarkCount();
//STRIP001  for (ULONG nMarkNum=0; nMarkNum<nMarkAnz && !bRet; nMarkNum++) {
//STRIP001      SdrMark* pM=aMark.GetMark(nMarkNum);
//STRIP001      SdrObject* pObj=pM->GetObj();
//STRIP001      SdrUShortCont* pPts=pM->GetMarkedPoints();
//STRIP001      ULONG nMarkPntAnz=pPts!=NULL ? pPts->GetCount() : 0;
//STRIP001      if (pPts!=NULL && nMarkPntAnz!=0 && pObj!=NULL && pObj->ISA(SdrPathObj)) {
//STRIP001          const XPolyPolygon& rXPP=((SdrPathObj*)pObj)->GetPathPoly();
//STRIP001          if (rXPP.Count()==1) { // es muss genau 1 Polygon drin sein!
//STRIP001              const XPolygon& rXP=rXPP[0];
//STRIP001              USHORT nPntAnz=rXP.GetPointCount();
//STRIP001              if (nPntAnz>=3) {
//STRIP001                  bRet=pObj->IsClosedObj();
//STRIP001                  if (!bRet) {
//STRIP001                      for (ULONG nMarkPntNum=0; nMarkPntNum<nMarkPntAnz && !bRet; nMarkPntNum++) {
//STRIP001                          USHORT nMarkPt=pPts->GetObject(nMarkPntNum);
//STRIP001                          bRet=nMarkPt>0 && nMarkPt<nPntAnz-1;
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SdrPolyEditView::IsOpenCloseMarkedObjectsPossible() const
//STRIP001 {
//STRIP001  BOOL bRet=FALSE;
//STRIP001  ULONG nMarkAnz=aMark.GetMarkCount();
//STRIP001  for (ULONG nm=0; nm<nMarkAnz && !bRet; nm++) {
//STRIP001      SdrMark* pM=aMark.GetMark(nm);
//STRIP001      SdrObject* pO=pM->GetObj();
//STRIP001      if (pO->ISA(SdrPathObj)) {
//STRIP001          const XPolyPolygon& rXPP=((SdrPathObj*)pO)->GetPathPoly();
//STRIP001          USHORT nPolyAnz=rXPP.Count();
//STRIP001          for (USHORT nPolyNum=0; nPolyNum<nPolyAnz && !bRet; nPolyNum++) {
//STRIP001              const XPolygon& rXP=rXPP[nPolyNum];
//STRIP001              USHORT nPntAnz=rXP.GetPointCount();
//STRIP001              bRet=nPntAnz>=3;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001          return FALSE;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 SdrObjClosedKind SdrPolyEditView::GetMarkedObjectsClosedState() const
//STRIP001 {
//STRIP001  BOOL bOpen=FALSE;
//STRIP001  BOOL bClosed=FALSE;
//STRIP001  ULONG nMarkAnz=aMark.GetMarkCount();
//STRIP001  for (ULONG nm=0; nm<nMarkAnz && (!bOpen || !bClosed); nm++) {
//STRIP001      SdrMark* pM=aMark.GetMark(nm);
//STRIP001      SdrObject* pO=pM->GetObj();
//STRIP001      if (pO->ISA(SdrPathObj)) {
//STRIP001          const XPolyPolygon& rXPP=((SdrPathObj*)pO)->GetPathPoly();
//STRIP001          if (rXPP.Count()==1) { // es muss genau 1 Polygon drin sein!
//STRIP001              const XPolygon& rXP=rXPP[0];
//STRIP001              USHORT nPntAnz=rXP.GetPointCount();
//STRIP001              if (nPntAnz>=3) {
//STRIP001                  if (pO->IsClosedObj()) bClosed=TRUE; else bOpen=TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if (bOpen && bClosed) return SDROBJCLOSED_DONTCARE;
//STRIP001  if (bOpen) return SDROBJCLOSED_OPEN;
//STRIP001  return SDROBJCLOSED_CLOSED;
//STRIP001 }

//STRIP001 void SdrPolyEditView::ShutMarkedObjects()
//STRIP001 {
//STRIP001  CloseMarkedObjects();
//STRIP001 }

//STRIP001 void SdrPolyEditView::CloseMarkedObjects(BOOL bToggle, BOOL bOpen, long nOpenDistance)
//STRIP001 {
//STRIP001  if (HasMarkedObj()) {
//STRIP001      BegUndo(ImpGetResStr(STR_EditShut),aMark.GetPointMarkDescription());
//STRIP001      BOOL bChg=FALSE;
//STRIP001      ULONG nMarkAnz=aMark.GetMarkCount();
//STRIP001      for (ULONG nm=0; nm<nMarkAnz; nm++) {
//STRIP001          SdrMark* pM=aMark.GetMark(nm);
//STRIP001          SdrObject* pO=pM->GetObj();
//STRIP001          BOOL bClosed=pO->IsClosedObj();
//STRIP001          if (pO->IsPolyObj() && (bClosed==bOpen) || bToggle) {
//STRIP001              AddUndo(new SdrUndoGeoObj(*pO));
//STRIP001              if (pO->ISA(SdrPathObj)) {
//STRIP001                  ((SdrPathObj*)pO)->ToggleClosed(nOpenDistance);
//STRIP001              } else {
//STRIP001                  if (!bOpen) pO->Shut();
//STRIP001              }
//STRIP001              bChg=TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001      EndUndo();
//STRIP001      if (bChg) {
//STRIP001          UnmarkAllPoints();
//STRIP001          MarkListHasChanged();
//STRIP001      }
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrPolyEditView::ImpCopyMarkedPoints()
//STRIP001 {
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrPolyEditView::ImpTransformMarkedPoints(PPolyTrFunc pTrFunc, const void* p1, const void* p2, const void* p3, const void* p4, const void* p5)
//STRIP001 {
//STRIP001  ULONG nMarkAnz=aMark.GetMarkCount();
//STRIP001  for (ULONG nm=0; nm<nMarkAnz; nm++) {
//STRIP001      SdrMark* pM=aMark.GetMark(nm);
//STRIP001      SdrObject* pObj=pM->GetObj();
//STRIP001      const SdrUShortCont* pPts=pM->GetMarkedPoints();
//STRIP001      Point aPvOfs(pM->GetPageView()->GetOffset());
//STRIP001      ULONG nPtAnz=pPts==NULL ? 0 : pPts->GetCount();
//STRIP001      SdrPathObj* pPath=PTR_CAST(SdrPathObj,pObj);
//STRIP001      if (nPtAnz!=0 && pPath!=NULL) {
//STRIP001          AddUndo(new SdrUndoGeoObj(*pObj));
//STRIP001          XPolyPolygon aXPP(pPath->GetPathPoly());
//STRIP001          BOOL bClosed=pPath->IsClosed();
//STRIP001          for (ULONG nPtNum=0; nPtNum<nPtAnz; nPtNum++) {
//STRIP001              USHORT nPt=pPts->GetObject(nPtNum);
//STRIP001              USHORT nPolyNum,nPointNum;
//STRIP001              if (pPath->TakePolyIdxForHdlNum(nPt,nPolyNum,nPointNum)) {
//STRIP001                  XPolygon& rXP=aXPP[nPolyNum];
//STRIP001                  USHORT nPointAnz=rXP.GetPointCount();
//STRIP001                  Point& rPos=rXP[nPointNum];
//STRIP001                  Point* pC1=NULL;
//STRIP001                  Point* pC2=NULL;
//STRIP001                  if (nPointNum>0 && rXP.IsControl(nPointNum-1)) {
//STRIP001                      pC1=&rXP[nPointNum-1];
//STRIP001                  }
//STRIP001                  if (nPointNum<nPointAnz-1 && rXP.IsControl(nPointNum+1)) {
//STRIP001                      pC2=&rXP[nPointNum+1];
//STRIP001                  }
//STRIP001                  if (bClosed && nPointNum==0 && nPointAnz>=2 && rXP.IsControl(nPointAnz-2)) {
//STRIP001                      pC1=&rXP[nPointAnz-2];
//STRIP001                  }
//STRIP001                  rPos+=aPvOfs;
//STRIP001                  if (pC1!=NULL) *pC1+=aPvOfs;
//STRIP001                  if (pC2!=NULL) *pC2+=aPvOfs;
//STRIP001                  (*pTrFunc)(rPos,pC1,pC2,p1,p2,p3,p4,p5);
//STRIP001                  rPos-=aPvOfs;
//STRIP001                  if (pC1!=NULL) *pC1-=aPvOfs;
//STRIP001                  if (pC2!=NULL) *pC2-=aPvOfs;
//STRIP001                  if (bClosed && nPointNum==0) rXP[nPointAnz-1]=rXP[0];
//STRIP001              }
//STRIP001          }
//STRIP001          pPath->SetPathPoly(aXPP);
//STRIP001      }
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 static void ImpMove(Point& rPt, Point* pC1, Point* pC2, const void* p1, const void* p2, const void* p3, const void* p4, const void* p5)
//STRIP001 {
//STRIP001  MovePoint(rPt,*(const Size*)p1);
//STRIP001  if (pC1!=NULL) MovePoint(*pC1,*(const Size*)p1);
//STRIP001  if (pC2!=NULL) MovePoint(*pC2,*(const Size*)p1);
//STRIP001 }

//STRIP001 void SdrPolyEditView::MoveMarkedPoints(const Size& rSiz, BOOL bCopy)
//STRIP001 {
//STRIP001  bCopy=FALSE; // noch nicht implementiert
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  XubString aStr(ImpGetResStr(STR_EditMove));
//STRIP001  if (bCopy) aStr+=ImpGetResStr(STR_EditWithCopy);
//STRIP001  BegUndo(aStr,aMark.GetPointMarkDescription(),SDRREPFUNC_OBJ_MOVE);
//STRIP001  if (bCopy) ImpCopyMarkedPoints();
//STRIP001  ImpTransformMarkedPoints(ImpMove,&rSiz);
//STRIP001  EndUndo();
//STRIP001  AdjustMarkHdl();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 static void ImpResize(Point& rPt, Point* pC1, Point* pC2, const void* p1, const void* p2, const void* p3, const void* p4, const void* p5)
//STRIP001 {
//STRIP001  ResizePoint(rPt,*(const Point*)p1,*(const Fraction*)p2,*(const Fraction*)p3);
//STRIP001  if (pC1!=NULL) ResizePoint(*pC1,*(const Point*)p1,*(const Fraction*)p2,*(const Fraction*)p3);
//STRIP001  if (pC2!=NULL) ResizePoint(*pC2,*(const Point*)p1,*(const Fraction*)p2,*(const Fraction*)p3);
//STRIP001 }

//STRIP001 void SdrPolyEditView::ResizeMarkedPoints(const Point& rRef, const Fraction& xFact, const Fraction& yFact, BOOL bCopy)
//STRIP001 {
//STRIP001  bCopy=FALSE; // noch nicht implementiert
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  XubString aStr(ImpGetResStr(STR_EditResize));
//STRIP001  if (bCopy) aStr+=ImpGetResStr(STR_EditWithCopy);
//STRIP001  BegUndo(aStr,aMark.GetPointMarkDescription(),SDRREPFUNC_OBJ_RESIZE);
//STRIP001  if (bCopy) ImpCopyMarkedPoints();
//STRIP001  ImpTransformMarkedPoints(ImpResize,&rRef,&xFact,&yFact);
//STRIP001  EndUndo();
//STRIP001  AdjustMarkHdl();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 static void ImpRotate(Point& rPt, Point* pC1, Point* pC2, const void* p1, const void* p2, const void* p3, const void* p4, const void* p5)
//STRIP001 {
//STRIP001  RotatePoint(rPt,*(const Point*)p1,*(const double*)p3,*(const double*)p4);
//STRIP001  if (pC1!=NULL) RotatePoint(*pC1,*(const Point*)p1,*(const double*)p3,*(const double*)p4);
//STRIP001  if (pC2!=NULL) RotatePoint(*pC2,*(const Point*)p1,*(const double*)p3,*(const double*)p4);
//STRIP001 }

//STRIP001 void SdrPolyEditView::RotateMarkedPoints(const Point& rRef, long nWink, BOOL bCopy)
//STRIP001 {
//STRIP001  bCopy=FALSE; // noch nicht implementiert
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  XubString aStr(ImpGetResStr(STR_EditResize));
//STRIP001  if (bCopy) aStr+=ImpGetResStr(STR_EditWithCopy);
//STRIP001  BegUndo(aStr,aMark.GetPointMarkDescription(),SDRREPFUNC_OBJ_ROTATE);
//STRIP001  if (bCopy) ImpCopyMarkedPoints();
//STRIP001  double nSin=sin(nWink*nPi180);
//STRIP001  double nCos=cos(nWink*nPi180);
//STRIP001  ImpTransformMarkedPoints(ImpRotate,&rRef,&nWink,&nSin,&nCos);
//STRIP001  EndUndo();
//STRIP001  AdjustMarkHdl();
//STRIP001 }

}
