/*************************************************************************
 *
 *  $RCSfile: svx_svdmrkv.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:39 $
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

#include "svdmrkv.hxx"
#include "svdetc.hxx"
#include "svdoedge.hxx"
#include "svdglob.hxx"
#include "svditext.hxx"
#include "svdview.hxx"
#include "svdpagv.hxx"
#include "svdpage.hxx"
#include "svddrgm1.hxx"
#include "svdio.hxx"
#include "svdibrow.hxx"
#include "svdoole2.hxx"
#include "xgrad.hxx"
#include "xflgrit.hxx"

#include "gradtrns.hxx"
#include "xflftrit.hxx"

#include "dialmgr.hxx"
#include "svdstr.hrc"
#include "svdundo.hxx"

// #105722#
#ifndef _SVDOPATH_HXX
#include "svdopath.hxx"
#endif

// #i13033#
#ifndef _E3D_SCENE3D_HXX
#include "scene3d.hxx"
#endif

// OD 30.06.2003 #108784#
#ifndef _SVDOVIRT_HXX
#include <svdovirt.hxx>
#endif
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@   @@  @@@@  @@@@@  @@  @@  @@ @@ @@ @@@@@ @@   @@
//  @@@ @@@ @@  @@ @@  @@ @@  @@  @@ @@ @@ @@    @@   @@
//  @@@@@@@ @@  @@ @@  @@ @@ @@   @@ @@ @@ @@    @@ @ @@
//  @@@@@@@ @@@@@@ @@@@@  @@@@    @@@@@ @@ @@@@  @@@@@@@
//  @@ @ @@ @@  @@ @@  @@ @@ @@    @@@  @@ @@    @@@@@@@
//  @@   @@ @@  @@ @@  @@ @@  @@   @@@  @@ @@    @@@ @@@
//  @@   @@ @@  @@ @@  @@ @@  @@    @   @@ @@@@@ @@   @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrMarkView::ImpClearVars()
/*N*/ {
/*N*/   eDragMode=SDRDRAG_MOVE;
/*N*/   bHdlShown=FALSE;
/*N*/   bRefHdlShownOnly=FALSE;
/*N*/   eEditMode=SDREDITMODE_EDIT;
/*N*/   eEditMode0=SDREDITMODE_EDIT;
/*N*/   bDesignMode=FALSE;
/*N*/   bMarking=FALSE;
/*N*/   bMarkingPoints=FALSE;
/*N*/   bMarkingGluePoints=FALSE;
/*N*/   bUnmarking=FALSE;
/*N*/   pMarkedObj=NULL;
/*N*/   pMarkedPV=NULL;
/*N*/   bForceFrameHandles=FALSE;
/*N*/   bPlusHdlAlways=FALSE;
/*N*/   nFrameHandlesLimit=50;
/*N*/   nSpecialCnt=0;
/*N*/   bInsPolyPoint=FALSE;
/*N*/   nInsPointNum=0;
/*N*/   bEdgesOfMarkedNodesDirty=FALSE;
/*N*/   bMarkedObjRectDirty=FALSE;
/*N*/   bMarkedPointsRectsDirty=FALSE;
/*N*/   bHdlHidden=FALSE;
/*N*/   bMrkPntDirty=FALSE;
/*N*/   bMarkHdlWhenTextEdit=FALSE;
/*N*/ //    bSolidHdlBackgroundInvalid=FALSE;
/*N*/   bMarkableObjCountDirty=FALSE; // noch nicht implementiert
/*N*/   nMarkableObjCount=0;          // noch nicht implementiert
/*N*/ }

/*N*/ SdrMarkView::SdrMarkView(SdrModel* pModel1, OutputDevice* pOut):
/*N*/   SdrSnapView(pModel1,pOut),
/*N*/   aHdl(this)
/*N*/ {
/*N*/   ImpClearVars();
/*N*/   StartListening(*pModel1);
/*N*/ }

/*?*/ SdrMarkView::SdrMarkView(SdrModel* pModel1, ExtOutputDevice* pXOut):
/*?*/   SdrSnapView(pModel1,pXOut),
/*?*/   aHdl(this)
/*?*/ {
/*?*/   ImpClearVars();
/*?*/   StartListening(*pModel1);
/*?*/ }

/*N*/ void __EXPORT SdrMarkView::SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType)
/*N*/ {
/*N*/   SdrHint* pSdrHint=PTR_CAST(SdrHint,&rHint);
/*N*/   if (pSdrHint!=NULL) {
/*N*/       SdrHintKind eKind=pSdrHint->GetKind();
/*N*/       if (eKind==HINT_OBJLISTCLEARED) {
/*N*/           USHORT nAnz=GetPageViewCount();
/*N*/           BOOL bMLChgd=FALSE;
/*N*/           for (USHORT nv=0; nv<nAnz; nv++) {
/*N*/               SdrPageView* pPV=GetPageViewPvNum(nv);
/*N*/               if (pPV->GetObjList()==pSdrHint->GetObjList()) {
/*?*/                   aMark.DeletePageView(*pPV);
/*?*/                   bMLChgd=TRUE;
/*N*/               }
/*N*/           }
/*N*/           if (bMLChgd) MarkListHasChanged();
/*N*/       }
/*N*/       if (eKind==HINT_OBJCHG || eKind==HINT_OBJINSERTED || eKind==HINT_OBJREMOVED)
/*N*/       {
/*N*/           if(bHdlShown
/*N*/               // #75438# do not hide handles if no repaint will be triggered
/*N*/               // since the repaint will show handles again later
/*N*/               && pSdrHint->IsNeedRepaint())
/*N*/           {
/*N*/               HideMarkHdl(NULL);
/*N*/           }
/*N*/
/*N*/           bMarkedObjRectDirty=TRUE;
/*N*/           bMarkedPointsRectsDirty=TRUE;
/*N*/       }
/*N*/   }
/*N*/   SdrSnapView::SFX_NOTIFY(rBC,rBCType,rHint,rHintType);
/*N*/ }

/*N*/ void SdrMarkView::ModelHasChanged()
/*N*/ {
/*N*/   SdrPaintView::ModelHasChanged();
/*N*/   aMark.SetNameDirty();
/*N*/   bMarkedObjRectDirty=TRUE;
/*N*/   bMarkedPointsRectsDirty=TRUE;
/*N*/   // Es sind beispielsweise Obj markiert und aMark ist Sorted.
/*N*/   // In einer anderen View 2 wird die ObjOrder veraendert
/*N*/   // (z.B. MovToTop()). Dann ist Neusortieren der MarkList erforderlich.
/*N*/   aMark.SetUnsorted();
/*N*/   aMark.ForceSort();
/*N*/   bMrkPntDirty=TRUE;
/*N*/   UndirtyMrkPnt();
/*N*/   SdrView* pV=(SdrView*)this;
/*N*/   if (pV!=NULL && !pV->IsDragObj() && !pV->IsInsObjPoint()) { // an dieser Stelle habe ich ein ziemliches Problem !!!
/*N*/       AdjustMarkHdl();
//        if (!IsSolidMarkHdl()) {
//            if (!bHdlShown) {
//                // Ein wenig unsauber ...
//                if ((bMarkHdlWhenTextEdit || !pV->IsTextEdit()) &&  // evtl. keine Handles bei TextEdit
//                    !(pV->IsDragHdlHide() && pV->IsDragObj() && // Ggf. keine Handles beim Draggen
//                      aDragStat.IsMinMoved() && !IS_TYPE(SdrDragMovHdl,pV->GetDragMethod()))) {
//                    ShowMarkHdl(NULL);
//                }
//            }
//        }
    }
/*N*/ }

//STRIP001 void SdrMarkView::AfterInitRedraw(USHORT nWinNum)
//STRIP001 {
//STRIP001 //    if (IsShownXorVisibleWinNum(nWinNum)) { // Durch Invalidate zerstoerte Handles wiederherstellen
//STRIP001 //        OutputDevice* pOut=GetWin(nWinNum);
//STRIP001 //        if (pOut!=NULL && pOut->GetOutDevType()==OUTDEV_WINDOW) {
//STRIP001 //            if (bHdlShown && IsSolidMarkHdl()) {
//STRIP001 //               if( aWinList[nWinNum].pVDev == NULL )
//STRIP001 //                   aWinList[nWinNum].pVDev = new VirtualDevice;
//STRIP001 //
//STRIP001 //                aHdl.SaveBackground(*pOut,*aWinList[nWinNum].pVDev);
//STRIP001 //            }
//STRIP001 //        }
//STRIP001 //    }
//STRIP001 }

//STRIP001 void SdrMarkView::ImpAfterPaint()
//STRIP001 {
//STRIP001 //    if (IsSolidMarkHdl()) {
//STRIP001      SdrView* pV=(SdrView*)this;
//STRIP001      if (pV!=NULL && !pV->IsDragObj() && !pV->IsInsObjPoint()) { // an dieser Stelle habe ich ein ziemliches Problem !!!
//STRIP001          if (!bHdlShown ) {
//STRIP001              // Ein wenig unsauber ...
//STRIP001              if ((bMarkHdlWhenTextEdit || !pV->IsTextEdit()) &&  // evtl. keine Handles bei TextEdit
//STRIP001                  !(pV->IsDragHdlHide() && pV->IsDragObj() && // Ggf. keine Handles beim Draggen
//STRIP001                    aDragStat.IsMinMoved() && !IS_TYPE(SdrDragMovHdl,pV->GetDragMethod()))) {
//STRIP001                  ShowMarkHdl(NULL);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001 //    }
//STRIP001 //   // refresh with Paint-functionality
//STRIP001 //   RefreshAllIAOManagers();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ BOOL SdrMarkView::IsAction() const
/*N*/ {
/*N*/   return SdrSnapView::IsAction() || bMarking || bMarkingPoints || bMarkingGluePoints;
/*N*/ }

//STRIP001 void SdrMarkView::MovAction(const Point& rPnt)
//STRIP001 {
//STRIP001  SdrSnapView::MovAction(rPnt);
//STRIP001  if (bMarking) {
//STRIP001      MovMarkObj(rPnt);
//STRIP001  }
//STRIP001  if (bMarkingPoints) {
//STRIP001      MovMarkPoints(rPnt);
//STRIP001  }
//STRIP001  if (bMarkingGluePoints) {
//STRIP001      MovMarkGluePoints(rPnt);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrMarkView::EndAction()
//STRIP001 {
//STRIP001  if (bMarking) EndMarkObj();
//STRIP001  if (bMarkingPoints) EndMarkPoints();
//STRIP001  if (bMarkingGluePoints) EndMarkGluePoints();
//STRIP001  SdrSnapView::EndAction();
//STRIP001 }

//STRIP001 void SdrMarkView::BckAction()
//STRIP001 {
//STRIP001  SdrSnapView::BckAction();
//STRIP001  BrkMarkObj();
//STRIP001  BrkMarkPoints();
//STRIP001  BrkMarkGluePoints();
//STRIP001 }

/*N*/ void SdrMarkView::BrkAction()
/*N*/ {
/*N*/   SdrSnapView::BrkAction();
/*N*/   BrkMarkObj();
/*N*/   BrkMarkPoints();
/*N*/   BrkMarkGluePoints();
/*N*/ }

//STRIP001 void SdrMarkView::TakeActionRect(Rectangle& rRect) const
//STRIP001 {
//STRIP001  if (bMarking || bMarkingPoints || bMarkingGluePoints) {
//STRIP001      rRect=Rectangle(aDragStat.GetStart(),aDragStat.GetNow());
//STRIP001  } else {
//STRIP001      SdrSnapView::TakeActionRect(rRect);
//STRIP001  }
//STRIP001 }

/*N*/ void SdrMarkView::ToggleShownXor(OutputDevice* pOut, const Region* pRegion) const
/*N*/ {
/*N*/   SdrSnapView::ToggleShownXor(pOut,pRegion);
/*N*/   if ((bMarking || bMarkingPoints || bMarkingGluePoints) && aDragStat.IsShown()) {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001   DrawMarkObjOrPoints(pOut);
/*N*/   }
//    if (bHdlShown) {
//        DrawMarkHdl(pOut,FALSE);
//    } else if (bRefHdlShownOnly) {
//        DrawMarkHdl(pOut,BOOL(2)); HACK(nur die Ref-Hdls painten)
//    }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrMarkView::ClearPageViews()
/*N*/ {
/*N*/   UnmarkAllObj();
/*N*/   SdrSnapView::ClearPageViews();
/*N*/ }

/*N*/ void SdrMarkView::HidePage(SdrPageView* pPV)
/*N*/ {
/*N*/   if(pPV)
/*N*/   {
/*N*/       // break all creation actions when hiding page (#75081#)
/*N*/       BrkAction();
/*N*/
/*N*/       BOOL bVis(IsMarkHdlShown());
/*N*/
/*N*/       if(bVis)
/*?*/           HideMarkHdl(NULL);
/*N*/
/*N*/       // Alle Markierungen dieser Seite verwerfen
/*N*/       BOOL bMrkChg(aMark.DeletePageView(*pPV));
/*N*/       SdrSnapView::HidePage(pPV);
/*N*/
/*N*/       if(bMrkChg)
/*N*/       {
/*?*/           MarkListHasChanged();
/*?*/           AdjustMarkHdl();
/*N*/       }
/*N*/
/*N*/       if(bVis)
/*N*/           ShowMarkHdl(NULL);
/*N*/   }
/*N*/ }

//STRIP001 void SdrMarkView::SetPagePos(SdrPageView* pPV, const Point& rOffs)
//STRIP001 {
//STRIP001  if (pPV!=NULL && rOffs!=pPV->GetOffset()) {
//STRIP001      BOOL bVis=IsMarkHdlShown();
//STRIP001      if (bVis) HideMarkHdl(NULL);
//STRIP001      SdrSnapView::SetPagePos(pPV,rOffs);
//STRIP001      bMarkedObjRectDirty=TRUE;
//STRIP001      bMarkedPointsRectsDirty=TRUE;
//STRIP001      AdjustMarkHdl();
//STRIP001      if (bVis) ShowMarkHdl(NULL);
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 BOOL SdrMarkView::BegMarkObj(const Point& rPnt, OutputDevice* pOut)
//STRIP001 {
//STRIP001  return BegMarkObj(rPnt,(BOOL)FALSE);
//STRIP001 }

//STRIP001 BOOL SdrMarkView::BegMarkObj(const Point& rPnt, BOOL bUnmark)
//STRIP001 {
//STRIP001  BrkAction();
//STRIP001  Point aPt(rPnt);
//STRIP001  aDragStat.Reset(aPt);
//STRIP001  aDragStat.NextPoint();
//STRIP001  aDragStat.SetMinMove(nMinMovLog);
//STRIP001  aAni.Reset();
//STRIP001  pDragWin=NULL;
//STRIP001  bMarking=TRUE;
//STRIP001  bUnmarking=bUnmark;
//STRIP001  nSpecialCnt=0;
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 void SdrMarkView::MovMarkObj(const Point& rPnt)
//STRIP001 {
//STRIP001  if (bMarking && aDragStat.CheckMinMoved(rPnt)) {
//STRIP001      Point aPt(rPnt);
//STRIP001      HideMarkObjOrPoints(pDragWin);
//STRIP001      aDragStat.NextMove(aPt);
//STRIP001      ShowMarkObjOrPoints(pDragWin);
//STRIP001      long dx=aDragStat.GetNow().X()-aDragStat.GetStart().X();
//STRIP001      long dy=aDragStat.GetNow().Y()-aDragStat.GetStart().Y();
//STRIP001      OutputDevice* pOut=pDragWin;
//STRIP001      if (pOut==NULL) pOut=GetWin(0);
//STRIP001      if (pOut!=NULL) {
//STRIP001          Size aSiz(pOut->LogicToPixel(Size(dx,dy)));
//STRIP001          dx=aSiz.Width();
//STRIP001          dy=aSiz.Height();
//STRIP001      }
//STRIP001      if (nSpecialCnt==0 && dx>=20 && dy>=20) nSpecialCnt++;
//STRIP001      if (nSpecialCnt>0 && nSpecialCnt!=0xFFFF) {
//STRIP001          BOOL bOdd=(nSpecialCnt & 1) ==1;
//STRIP001          if (bOdd && dx>=20 && dy<=2) nSpecialCnt++;
//STRIP001          if (!bOdd && dy>=20 && dx<=2) nSpecialCnt++;
//STRIP001      }
//STRIP001      if (nSpecialCnt>=3) nSpecialCnt=0xFFFF;
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL SdrMarkView::EndMarkObj()
//STRIP001 {
//STRIP001  if (!aDragStat.IsMinMoved()) BrkMarkObj();
//STRIP001  if (bMarking) {
//STRIP001      HideMarkObjOrPoints(pDragWin);
//STRIP001      bMarking=FALSE;
//STRIP001      Rectangle aRect(aDragStat.GetStart(),aDragStat.GetNow());
//STRIP001      aRect.Justify();
//STRIP001      MarkObj(aRect,bUnmarking);
//STRIP001      bUnmarking=FALSE;
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

/*N*/ void SdrMarkView::BrkMarkObj()
/*N*/ {
/*N*/   if (bMarking) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        HideMarkObjOrPoints(pDragWin);
//STRIP001 /*?*/        bMarking=FALSE;
//STRIP001 /*?*/        bUnmarking=FALSE;
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 BOOL SdrMarkView::BegMarkPoints(const Point& rPnt, OutputDevice* pOut)
//STRIP001 {
//STRIP001  return BegMarkPoints(rPnt,(BOOL)FALSE);
//STRIP001 }

//STRIP001 BOOL SdrMarkView::BegMarkPoints(const Point& rPnt, BOOL bUnmark)
//STRIP001 {
//STRIP001  if (HasMarkablePoints()) {
//STRIP001      BrkAction();
//STRIP001      Point aPt(rPnt);
//STRIP001      aDragStat.Reset(aPt);
//STRIP001      aDragStat.NextPoint();
//STRIP001      aDragStat.SetMinMove(nMinMovLog);
//STRIP001      aAni.Reset();
//STRIP001      pDragWin=NULL;
//STRIP001      bMarkingPoints=TRUE;
//STRIP001      bUnmarking=bUnmark;
//STRIP001      return TRUE;
//STRIP001  } else return FALSE;
//STRIP001 }

//STRIP001 void SdrMarkView::MovMarkPoints(const Point& rPnt)
//STRIP001 {
//STRIP001  if (bMarkingPoints && aDragStat.CheckMinMoved(rPnt)) {
//STRIP001      HideMarkObjOrPoints(pDragWin);
//STRIP001      aDragStat.NextMove(rPnt);
//STRIP001      ShowMarkObjOrPoints(pDragWin);
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL SdrMarkView::EndMarkPoints()
//STRIP001 {
//STRIP001  if (!HasMarkablePoints() || // Falls waerend des markierens ein Unmark oder so kam
//STRIP001      !aDragStat.IsMinMoved())
//STRIP001  {
//STRIP001      BrkMarkPoints();
//STRIP001  }
//STRIP001  if (bMarkingPoints) {
//STRIP001      HideMarkObjOrPoints(pDragWin);
//STRIP001      bMarkingPoints=FALSE;
//STRIP001      Rectangle aRect(aDragStat.GetStart(),aDragStat.GetNow());
//STRIP001      aRect.Justify();
//STRIP001      MarkPoints(aRect,bUnmarking);
//STRIP001      bUnmarking=FALSE;
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

/*N*/ void SdrMarkView::BrkMarkPoints()
/*N*/ {
/*N*/   if (bMarkingPoints) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        HideMarkObjOrPoints(pDragWin);
//STRIP001 /*?*/        bMarkingPoints=FALSE;
//STRIP001 /*?*/        bUnmarking=FALSE;
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 BOOL SdrMarkView::BegMarkGluePoints(const Point& rPnt, OutputDevice* pOut)
//STRIP001 {
//STRIP001  return BegMarkGluePoints(rPnt,(BOOL)FALSE);
//STRIP001 }

//STRIP001 BOOL SdrMarkView::BegMarkGluePoints(const Point& rPnt, BOOL bUnmark)
//STRIP001 {
//STRIP001  if (HasMarkableGluePoints()) {
//STRIP001      BrkAction();
//STRIP001      Point aPt(rPnt);
//STRIP001      aDragStat.Reset(aPt);
//STRIP001      aDragStat.NextPoint();
//STRIP001      aDragStat.SetMinMove(nMinMovLog);
//STRIP001      aAni.Reset();
//STRIP001      pDragWin=NULL;
//STRIP001      bMarkingGluePoints=TRUE;
//STRIP001      bUnmarking=bUnmark;
//STRIP001      return TRUE;
//STRIP001  } else return FALSE;
//STRIP001 }

//STRIP001 void SdrMarkView::MovMarkGluePoints(const Point& rPnt)
//STRIP001 {
//STRIP001  if (bMarkingGluePoints && aDragStat.CheckMinMoved(rPnt)) {
//STRIP001      HideMarkObjOrPoints(pDragWin);
//STRIP001      aDragStat.NextMove(rPnt);
//STRIP001      ShowMarkObjOrPoints(pDragWin);
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL SdrMarkView::EndMarkGluePoints()
//STRIP001 {
//STRIP001  if (!HasMarkableGluePoints() || // Falls waerend des markierens ein Unmark oder so kam
//STRIP001      !aDragStat.IsMinMoved())
//STRIP001  {
//STRIP001      BrkMarkGluePoints();
//STRIP001  }
//STRIP001  if (bMarkingGluePoints) {
//STRIP001      HideMarkObjOrPoints(pDragWin);
//STRIP001      bMarkingGluePoints=FALSE;
//STRIP001      Rectangle aRect(aDragStat.GetStart(),aDragStat.GetNow());
//STRIP001      aRect.Justify();
//STRIP001      MarkGluePoints(&aRect,bUnmarking);
//STRIP001      bUnmarking=FALSE;
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

/*N*/ void SdrMarkView::BrkMarkGluePoints()
/*N*/ {
/*N*/   if (bMarkingGluePoints) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        HideMarkObjOrPoints(pDragWin);
//STRIP001 /*?*/        bMarkingGluePoints=FALSE;
//STRIP001 /*?*/        bUnmarking=FALSE;
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrMarkView::DrawMarkObjOrPoints(OutputDevice* pOut) const
//STRIP001 {
//STRIP001  if (bMarking || bMarkingPoints || bMarkingGluePoints) {
//STRIP001      Point aPt1(aDragStat.GetStart());
//STRIP001      Point aPt2(aDragStat.GetNow());
//STRIP001      aAni.SetP1(aPt1);
//STRIP001      aAni.SetP2(aPt2);
//STRIP001      aAni.Invert(pOut);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrMarkView::ShowMarkObjOrPoints(OutputDevice* pOut)
//STRIP001 {
//STRIP001  if ((bMarking || bMarkingPoints || bMarkingGluePoints) && !aDragStat.IsShown()) {
//STRIP001      DrawMarkObjOrPoints(pOut);
//STRIP001      aDragStat.SetShown(TRUE);
//STRIP001      aAni.Start();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrMarkView::HideMarkObjOrPoints(OutputDevice* pOut)
//STRIP001 {
//STRIP001  if ((bMarking || bMarkingPoints || bMarkingGluePoints) && aDragStat.IsShown()) {
//STRIP001      aAni.Stop();
//STRIP001      DrawMarkObjOrPoints(pOut);
//STRIP001      aDragStat.SetShown(FALSE);
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 BOOL SdrMarkView::HasMarkableObj() const
//STRIP001 {
//STRIP001  ULONG nCount=0;
//STRIP001  ULONG nObjCnt=0;
//STRIP001  USHORT nPvCnt=GetPageViewCount();
//STRIP001  for (USHORT nPvNum=0; nPvNum<nPvCnt && nCount==0; nPvNum++) {
//STRIP001      SdrPageView* pPV=GetPageViewPvNum(nPvNum);
//STRIP001      SdrObjList* pOL=pPV->GetObjList();
//STRIP001      ULONG nObjAnz=pOL->GetObjCount();
//STRIP001      for (ULONG nObjNum=0; nObjNum<nObjAnz && nCount==0; nObjNum++) {
//STRIP001          SdrObject* pObj=pOL->GetObj(nObjNum);
//STRIP001          if (IsObjMarkable(pObj,pPV)) {
//STRIP001              nCount++;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return nCount!=0;
//STRIP001 }

//STRIP001 ULONG SdrMarkView::GetMarkableObjCount() const
//STRIP001 {
//STRIP001  ULONG nCount=0;
//STRIP001  ULONG nObjCnt=0;
//STRIP001  USHORT nPvCnt=GetPageViewCount();
//STRIP001  for (USHORT nPvNum=0; nPvNum<nPvCnt; nPvNum++) {
//STRIP001      SdrPageView* pPV=GetPageViewPvNum(nPvNum);
//STRIP001      SdrObjList* pOL=pPV->GetObjList();
//STRIP001      ULONG nObjAnz=pOL->GetObjCount();
//STRIP001      for (ULONG nObjNum=0; nObjNum<nObjAnz; nObjNum++) {
//STRIP001          SdrObject* pObj=pOL->GetObj(nObjNum);
//STRIP001          if (IsObjMarkable(pObj,pPV)) {
//STRIP001              nCount++;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return nCount;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//void SdrMarkView::DrawMarkHdl(OutputDevice* pOut, BOOL bNoRefHdl) const
//{
//    if (bHdlHidden) return;
////    if (IsSolidMarkHdl())
//      bNoRefHdl=FALSE; // geht leider erstmal nicht anders
//    BOOL bOnlyRefs=USHORT(bNoRefHdl)==2; HACK(nur die Ref-Hdls painten)
//    USHORT nWinAnz=GetWinCount();
//    USHORT nWinNum=0;
//    do {
//        OutputDevice* pO=pOut;
//        if (pO==NULL) {
//            pO=GetWin(nWinNum);
//            nWinNum++;
//        }
//        if (pO!=NULL) {
//            if (!bInsPolyPoint && !bNoRefHdl && !bOnlyRefs) {
//                aHdl.DrawAll(*pO);
//            } else {
//                ULONG nHdlAnz=aHdl.GetHdlCount();
//                for (ULONG nHdlNum=0; nHdlNum<nHdlAnz; nHdlNum++) {
//                    SdrHdl* pHdl=aHdl.GetHdl(nHdlNum);
//                    SdrHdlKind eKind=pHdl->GetKind();
//                    USHORT nPtNum=pHdl->GetObjHdlNum();
//                    const SdrObject* pObj=pHdl->GetObj();
//                    if ((!bInsPolyPoint || nPtNum!=nInsPointNum || pObj==NULL || pObj!=pMarkedObj) &&
//                        (!bNoRefHdl || (eKind!=HDL_REF1 && eKind!=HDL_REF2 && eKind!=HDL_MIRX))!=bOnlyRefs) {
//                        pHdl->Draw(*pO);
//                    }
//                }
//            }
//        }
//    } while (pOut==NULL && nWinNum<nWinAnz);
//}

/*N*/ void SdrMarkView::ImpShowMarkHdl(OutputDevice* pOut, const Region* pRegion, BOOL bNoRefHdl)
/*N*/ {
//    if (IsSolidMarkHdl())
/*N*/       bNoRefHdl=FALSE; // geht leider erstmal nicht anders
/*N*/   if (!bHdlShown) {
//        if (aHdl.IsSolidHdl()) {
//            USHORT nAnz=pOut==NULL ? aWinList.GetCount() : 1;
//            for (USHORT i=0; i<nAnz; i++) {
//                USHORT nWinNum=pOut==NULL ? i : aWinList.Find(pOut);
//                if (nWinNum!=SDRVIEWWIN_NOTFOUND) {
//                    if (aWinList[nWinNum].pVDev==NULL) {
//                        aWinList[nWinNum].pVDev=new VirtualDevice;
//                    }
//                    aHdl.SaveBackground(*aWinList[nWinNum].pWin,*aWinList[nWinNum].pVDev,pRegion);
//                    bSolidHdlBackgroundInvalid=FALSE;
//                }
//            }
//        }
//        DrawMarkHdl(pOut,bRefHdlShownOnly);
/*N*/       bRefHdlShownOnly=FALSE;
/*N*/       bHdlShown=TRUE;

        // refresh IAOs
//      RefreshAllIAOManagers();
/*N*/   }
/*N*/ }

/*N*/ void SdrMarkView::ShowMarkHdl(OutputDevice* pOut, BOOL bNoRefHdl)
/*N*/ {
//    if (IsSolidMarkHdl())
/*N*/       bNoRefHdl=FALSE; // geht leider erstmal nicht anders
/*N*/   ImpShowMarkHdl(pOut,NULL,bNoRefHdl);

    // refresh IAOs
//STRIP012/*N*/     RefreshAllIAOManagers();
/*N*/ }


/*N*/ void SdrMarkView::HideMarkHdl(OutputDevice* pOut, BOOL bNoRefHdl)
/*N*/ {
//    if (IsSolidMarkHdl())
/*N*/       bNoRefHdl=FALSE; // geht leider erstmal nicht anders
/*N*/   if (bHdlShown) {
/*N*/       if (!bHdlHidden) { // #37331#
            // Optimierung geht nicht, weil diverse Handles trotz SolidHdl doch noch XOR gapainted werden
//          DrawMarkHdl(pOut,bNoRefHdl);
//            if (aHdl.IsSolidHdl()) {
//                BOOL bInvalidate=IsMarkHdlBackgroundInvalid();
//                USHORT nAnz=pOut==NULL ? aWinList.GetCount() : 1;
//                for (USHORT i=0; i<nAnz; i++) {
//                    USHORT nWinNum=pOut==NULL ? i : aWinList.Find(pOut);
//                    if (nWinNum!=SDRVIEWWIN_NOTFOUND) {
//                        SdrViewWinRec& rWRec=GetWinRec(nWinNum);
//                        if (rWRec.pVDev!=NULL) {
//                            OutputDevice* pOut=rWRec.pWin;
//                            if (bInvalidate) { // fuer den Writer in einigen Faellen Invalidieren
//                                if (pOut->GetOutDevType()==OUTDEV_WINDOW) {
//                                    aHdl.Invalidate(*(Window*)pOut);
//                                }
//                            } else {
//                                if (bNoRefHdl) {
//                                    ULONG nHdlAnz=aHdl.GetHdlCount();
//                                    for (ULONG nHdlNum=0; nHdlNum<nHdlAnz; nHdlNum++) {
//                                        SdrHdl* pHdl=aHdl.GetHdl(nHdlNum);
//                                        SdrHdlKind eKind=pHdl->GetKind();
//                                        USHORT nPtNum=pHdl->GetObjHdlNum();
//                                        if (eKind!=HDL_REF1 && eKind!=HDL_REF2 && eKind!=HDL_MIRX) {
//                                            aHdl.RestoreBackground(*pOut,*rWRec.pVDev,(USHORT)nHdlNum);
//                                        }
//                                    }
//                                } else {
//                                    aHdl.RestoreBackground(*pOut,*rWRec.pVDev);
//                                }
//                            }
//                        }
//                    }
//                }
//            }
/*N*/       }
/*N*/       bRefHdlShownOnly=bNoRefHdl;
/*N*/       bHdlShown=FALSE;
/*N*/   }
//    bSolidHdlBackgroundInvalid=FALSE;

    // refresh IAOs
//  RefreshAllIAOManagers();
/*N*/ }

/*N*/ void SdrMarkView::SetMarkHdlHidden(BOOL bOn)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if(bOn != bHdlHidden)
//STRIP001  {
//STRIP001      // one hide in which the old flag value is still set
//STRIP001      HideMarkHdl(NULL);
//STRIP001
//STRIP001      // remember new value
//STRIP001      bHdlHidden = bOn;
//STRIP001
//STRIP001      // create all IAOHandles new (depends on IsMarkHdlHidden())
//STRIP001      AdjustMarkHdl(TRUE);
//STRIP001
//STRIP001      // show new state
//STRIP001      RefreshAllIAOManagers();
//STRIP001
//STRIP001 //       BOOL bHdlShownMerk=bHdlShown;
//STRIP001 //       bHdlHidden=FALSE;
//STRIP001 //       if (bOn) { // Modus anschalten, also Handles ggf aus.
//STRIP001 //           if (bHdlShown) HideMarkHdl(NULL);
//STRIP001 //       } else { // Ansonsten Modus ausschalten, also Handles ggf. einblenden
//STRIP001 //           if (bHdlShown) { bHdlShown=FALSE; ShowMarkHdl(NULL); }
//STRIP001 //       }
//STRIP001 //       bHdlShown=bHdlShownMerk;
//STRIP001 //       bHdlHidden=bOn;
//STRIP001  }
/*N*/ }

/*N*/ BOOL SdrMarkView::ImpIsFrameHandles() const
/*N*/ {
/*N*/   ULONG nMarkAnz=aMark.GetMarkCount();
/*N*/   BOOL bFrmHdl=nMarkAnz>nFrameHandlesLimit || bForceFrameHandles;
/*N*/   BOOL bStdDrag=eDragMode==SDRDRAG_MOVE;
/*N*/   if (nMarkAnz==1 && bStdDrag && bFrmHdl) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        const SdrObject* pObj=aMark.GetMark(0)->GetObj();
//STRIP001 /*?*/        if (pObj->GetObjInventor()==SdrInventor) {
//STRIP001 /*?*/            UINT16 nIdent=pObj->GetObjIdentifier();
//STRIP001 /*?*/            if (nIdent==OBJ_LINE || nIdent==OBJ_EDGE || nIdent==OBJ_CAPTION || nIdent==OBJ_MEASURE) {
//STRIP001 /*?*/                bFrmHdl=FALSE;
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
/*N*/   }
/*N*/   if (!bStdDrag && !bFrmHdl) {
/*?*/       // Grundsaetzlich erstmal alle anderen Dragmodi nur mit FrameHandles
/*?*/       bFrmHdl=TRUE;
/*?*/       if (eDragMode==SDRDRAG_ROTATE) {
/*?*/           // bei Rotate ObjOwn-Drag, wenn mind. 1 PolyObj
/*?*/           for (ULONG nMarkNum=0; nMarkNum<nMarkAnz && bFrmHdl; nMarkNum++) {
/*?*/               const SdrMark* pM=aMark.GetMark(nMarkNum);
/*?*/               const SdrObject* pObj=pM->GetObj();
/*?*/               bFrmHdl=!pObj->IsPolyObj();
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/   if (!bFrmHdl) {
/*N*/       // FrameHandles, wenn wenigstens 1 Obj kein SpecialDrag kann
/*N*/       for (ULONG nMarkNum=0; nMarkNum<nMarkAnz && !bFrmHdl; nMarkNum++) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            const SdrMark* pM=aMark.GetMark(nMarkNum);
//STRIP001 /*?*/            const SdrObject* pObj=pM->GetObj();
//STRIP001 /*?*/            bFrmHdl=!pObj->HasSpecialDrag();
/*N*/       }
/*N*/   }
/*N*/   return bFrmHdl;
/*N*/ }

/*N*/ void SdrMarkView::SetMarkHandles()
/*N*/ {
/*N*/   // #105722# remember old focus handle values to search for it again
/*N*/   const SdrHdl* pSaveOldFocusHdl = aHdl.GetFocusHdl();
/*N*/   sal_Bool bSaveOldFocus(sal_False);
/*N*/   sal_uInt16 nSavePolyNum, nSavePointNum;
/*N*/   SdrHdlKind eSaveKind;
/*N*/   SdrObject* pSaveObj;
/*N*/
/*N*/   if(pSaveOldFocusHdl
/*N*/       && pSaveOldFocusHdl->GetObj()
/*N*/       && pSaveOldFocusHdl->GetObj()->ISA(SdrPathObj)
/*N*/       && (pSaveOldFocusHdl->GetKind() == HDL_POLY || pSaveOldFocusHdl->GetKind() == HDL_BWGT))
/*N*/   {DBG_BF_ASSERT(0, "STRIP");
//STRIP001 /*?*/        bSaveOldFocus = sal_True;
//STRIP001 /*?*/        nSavePolyNum = pSaveOldFocusHdl->GetPolyNum();
//STRIP001 /*?*/        nSavePointNum = pSaveOldFocusHdl->GetPointNum();
//STRIP001 /*?*/        pSaveObj = pSaveOldFocusHdl->GetObj();
//STRIP001 /*?*/        eSaveKind = pSaveOldFocusHdl->GetKind();
/*N*/   }
/*N*/
/*N*/   aHdl.Clear();
/*N*/   aHdl.SetRotateShear(eDragMode==SDRDRAG_ROTATE);
/*N*/   aHdl.SetDistortShear(eDragMode==SDRDRAG_SHEAR);
/*N*/   pMarkedObj=NULL;
/*N*/   pMarkedPV=NULL;
/*N*/   ULONG nMarkAnz=aMark.GetMarkCount();
/*N*/   BOOL bStdDrag=eDragMode==SDRDRAG_MOVE;
/*N*/   if (nMarkAnz==1) {
/*?*/       pMarkedObj=aMark.GetMark(0)->GetObj();
/*N*/   }
/*N*/   BOOL bFrmHdl=ImpIsFrameHandles();
/*N*/   if (nMarkAnz>0) {
/*?*/       pMarkedPV=aMark.GetMark(0)->GetPageView();
/*?*/       for (ULONG nMarkNum=0; nMarkNum<nMarkAnz && (pMarkedPV!=NULL || !bFrmHdl); nMarkNum++) {
/*?*/           const SdrMark* pM=aMark.GetMark(nMarkNum);
/*?*/           if (pMarkedPV!=pM->GetPageView()) {
/*?*/               pMarkedPV=NULL;
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/   if (bFrmHdl) {
/*N*/       Rectangle aRect(GetMarkedObjRect());
/*N*/       if (!aRect.IsEmpty()) { // sonst nix gefunden
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 BOOL bWdt0=aRect.Left()==aRect.Right();
//STRIP001 /*?*/            BOOL bHgt0=aRect.Top()==aRect.Bottom();
//STRIP001 /*?*/            if (bWdt0 && bHgt0) {
//STRIP001 /*?*/                aHdl.AddHdl(new SdrHdl(aRect.TopLeft(),HDL_UPLFT));
//STRIP001 /*?*/            } else if (!bStdDrag && (bWdt0 || bHgt0)) {
//STRIP001 /*?*/                aHdl.AddHdl(new SdrHdl(aRect.TopLeft()    ,HDL_UPLFT));
//STRIP001 /*?*/                aHdl.AddHdl(new SdrHdl(aRect.BottomRight(),HDL_LWRGT));
//STRIP001 /*?*/            } else {
//STRIP001 /*?*/                if (!bWdt0 && !bHgt0) aHdl.AddHdl(new SdrHdl(aRect.TopLeft()     ,HDL_UPLFT));
//STRIP001 /*?*/                if (          !bHgt0) aHdl.AddHdl(new SdrHdl(aRect.TopCenter()   ,HDL_UPPER));
//STRIP001 /*?*/                if (!bWdt0 && !bHgt0) aHdl.AddHdl(new SdrHdl(aRect.TopRight()    ,HDL_UPRGT));
//STRIP001 /*?*/                if (!bWdt0          ) aHdl.AddHdl(new SdrHdl(aRect.LeftCenter()  ,HDL_LEFT ));
//STRIP001 /*?*/                if (!bWdt0          ) aHdl.AddHdl(new SdrHdl(aRect.RightCenter() ,HDL_RIGHT));
//STRIP001 /*?*/                if (!bWdt0 && !bHgt0) aHdl.AddHdl(new SdrHdl(aRect.BottomLeft()  ,HDL_LWLFT));
//STRIP001 /*?*/                if (          !bHgt0) aHdl.AddHdl(new SdrHdl(aRect.BottomCenter(),HDL_LOWER));
//STRIP001 /*?*/                if (!bWdt0 && !bHgt0) aHdl.AddHdl(new SdrHdl(aRect.BottomRight() ,HDL_LWRGT));
//STRIP001 /*?*/            }
/*N*/       }
/*N*/   } else {
/*N*/       for (ULONG nMarkNum=0; nMarkNum<nMarkAnz; nMarkNum++) {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 const SdrMark* pM=aMark.GetMark(nMarkNum);
//STRIP001 /*?*/            SdrObject* pObj=pM->GetObj();
//STRIP001 /*?*/            SdrPageView* pPV=pM->GetPageView();
//STRIP001 /*?*/            ULONG nSiz0=aHdl.GetHdlCount();
//STRIP001 /*?*/            pObj->AddToHdlList(aHdl);
//STRIP001 /*?*/            ULONG nSiz1=aHdl.GetHdlCount();
//STRIP001 /*?*/            BOOL bPoly=pObj->IsPolyObj();
//STRIP001 /*?*/            const SdrUShortCont* pMrkPnts=pM->GetMarkedPoints();
//STRIP001 /*?*/            for (ULONG i=nSiz0; i<nSiz1; i++) {
//STRIP001 /*?*/                SdrHdl* pHdl=aHdl.GetHdl(i);
//STRIP001 /*?*/                pHdl->SetObj(pObj);
//STRIP001 /*?*/                pHdl->SetPageView(pPV);
//STRIP001 /*?*/                pHdl->SetObjHdlNum(USHORT(i-nSiz0));
//STRIP001 /*?*/                if (bPoly) {
//STRIP001 /*?*/                    BOOL bSelected=pMrkPnts!=NULL && pMrkPnts->Exist(USHORT(i-nSiz0));
//STRIP001 /*?*/                    pHdl->SetSelected(bSelected);
//STRIP001 /*?*/                    BOOL bPlus=bPlusHdlAlways;
//STRIP001 /*?*/                    if (bPlusHdlAlways || bSelected) {
//STRIP001 /*?*/                        USHORT nPlusAnz=pObj->GetPlusHdlCount(*pHdl);
//STRIP001 /*?*/                        for (USHORT nPlusNum=0; nPlusNum<nPlusAnz; nPlusNum++) {
//STRIP001 /*?*/                            SdrHdl* pPlusHdl=pObj->GetPlusHdl(*pHdl,nPlusNum);
//STRIP001 /*?*/                            if (pPlusHdl!=NULL) {
//STRIP001 /*?*/                                pPlusHdl->SetObj(pObj);
//STRIP001 /*?*/                                pPlusHdl->SetPageView(pPV);
//STRIP001 /*?*/                                pPlusHdl->SetPlusHdl(TRUE);
//STRIP001 /*?*/                                aHdl.AddHdl(pPlusHdl);
//STRIP001 /*?*/                            }
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
/*N*/       } // for nMarkNum
/*N*/   } // if bFrmHdl else
/*N*/   // GluePoint-Handles
/*N*/   for (ULONG nMarkNum=0; nMarkNum<nMarkAnz; nMarkNum++) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        const SdrMark* pM=aMark.GetMark(nMarkNum);
//STRIP001 /*?*/        SdrObject* pObj=pM->GetObj();
//STRIP001 /*?*/        SdrPageView* pPV=pM->GetPageView();
//STRIP001 /*?*/        const SdrUShortCont* pMrkGlue=pM->GetMarkedGluePoints();
//STRIP001 /*?*/        if (pMrkGlue!=NULL) {
//STRIP001 /*?*/            const SdrGluePointList* pGPL=pObj->GetGluePointList();
//STRIP001 /*?*/            if (pGPL!=NULL) {
//STRIP001 /*?*/                USHORT nGlueAnz=pGPL->GetCount();
//STRIP001 /*?*/                USHORT nAnz=(USHORT)pMrkGlue->GetCount();
//STRIP001 /*?*/                for (USHORT nNum=0; nNum<nAnz; nNum++) {
//STRIP001 /*?*/                    USHORT nId=pMrkGlue->GetObject(nNum);
//STRIP001 /*?*/                    USHORT nNum=pGPL->FindGluePoint(nId);
//STRIP001 /*?*/                    if (nNum!=SDRGLUEPOINT_NOTFOUND) {
//STRIP001 /*?*/                        const SdrGluePoint& rGP=(*pGPL)[nNum];
//STRIP001 /*?*/                        Point aPos(rGP.GetAbsolutePos(*pObj));
//STRIP001 /*?*/                        SdrHdl* pGlueHdl=new SdrHdl(aPos,HDL_GLUE);
//STRIP001 /*?*/                        pGlueHdl->SetObj(pObj);
//STRIP001 /*?*/                        pGlueHdl->SetPageView(pPV);
//STRIP001 /*?*/                        pGlueHdl->SetObjHdlNum(nId);
//STRIP001 /*?*/                        aHdl.AddHdl(pGlueHdl);
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
/*N*/   }

    // Drehpunkt/Spiegelachse
/*N*/   AddDragModeHdl(eDragMode);
/*N*/
/*N*/   // add custom handles (used by other apps, e.g. AnchorPos)
/*N*/   AddCustomHdl();
/*N*/
/*N*/   // sort handles
/*N*/   aHdl.Sort();
/*N*/
/*N*/   // #105722# try to restore focus handle index from remembered values
/*N*/   if(bSaveOldFocus)
/*N*/   {DBG_BF_ASSERT(0, "STRIP");//STRIP001
//STRIP001 /*?*/        for(sal_uInt32 a(0); a < aHdl.GetHdlCount(); a++)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            SdrHdl* pCandidate = aHdl.GetHdl(a);
//STRIP001 /*?*/
//STRIP001 /*?*/            if(pCandidate->GetObj()
//STRIP001 /*?*/                && pCandidate->GetObj() == pSaveObj
//STRIP001 /*?*/                && pCandidate->GetKind() == eSaveKind
//STRIP001 /*?*/                && pCandidate->GetPolyNum() == nSavePolyNum
//STRIP001 /*?*/                && pCandidate->GetPointNum() == nSavePointNum)
//STRIP001 /*?*/            {
//STRIP001 /*?*/                aHdl.SetFocusHdl(pCandidate);
//STRIP001 /*?*/                break;
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
/*N*/   }
/*N*/ }

/*N*/ void SdrMarkView::AddCustomHdl()
/*N*/ {
/*N*/   // add custom handles (used by other apps, e.g. AnchorPos)
/*N*/ }

/*N*/ void SdrMarkView::SetDragMode(SdrDragMode eMode)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  SdrDragMode eMode0=eDragMode;
//STRIP001  eDragMode=eMode;
//STRIP001  if (eDragMode==SDRDRAG_RESIZE) eDragMode=SDRDRAG_MOVE;
//STRIP001  if (eDragMode!=eMode0) {
//STRIP001      BOOL bVis=IsMarkHdlShown();
//STRIP001      if (bVis) HideMarkHdl(NULL);
//STRIP001      ForceRefToMarked();
//STRIP001      SetMarkHandles();
//STRIP001      if (bVis) ShowMarkHdl(NULL);
//STRIP001      {
//STRIP001          if (HasMarkedObj()) MarkListHasChanged();
//STRIP001      }
//STRIP001  }
/*N*/ }

/*N*/ void SdrMarkView::AddDragModeHdl(SdrDragMode eMode)
/*N*/ {
/*N*/   switch(eMode)
/*N*/   {
/*?*/       case SDRDRAG_ROTATE:
/*?*/       {
/*?*/           // add rotation center
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001   SdrHdl* pHdl = new SdrHdl(aRef1, HDL_REF1);
/*?*/
//STRIP001 /*?*/            aHdl.AddHdl(pHdl);
/*?*/
/*?*/           break;
/*?*/       }
/*?*/       case SDRDRAG_MIRROR:
/*?*/       {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            // add mirror axis
//STRIP001 /*?*/            SdrHdl* pHdl3 = new SdrHdl(aRef2, HDL_REF2);
//STRIP001 /*?*/            SdrHdl* pHdl2 = new SdrHdl(aRef1, HDL_REF1);
//STRIP001 /*?*/            SdrHdl* pHdl1 = new SdrHdlLine(*pHdl2, *pHdl3, HDL_MIRX);
//STRIP001 /*?*/
//STRIP001 /*?*/            pHdl1->SetObjHdlNum(1); // fuer Sortierung
//STRIP001 /*?*/            pHdl2->SetObjHdlNum(2); // fuer Sortierung
//STRIP001 /*?*/            pHdl3->SetObjHdlNum(3); // fuer Sortierung
//STRIP001 /*?*/
//STRIP001 /*?*/            aHdl.AddHdl(pHdl1); // Linie als erstes, damit als letztes im HitTest
//STRIP001 /*?*/            aHdl.AddHdl(pHdl2);
//STRIP001 /*?*/            aHdl.AddHdl(pHdl3);
/*?*/
/*?*/           break;
/*?*/       }
/*?*/       case SDRDRAG_TRANSPARENCE:
/*?*/       {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            // add interactive transparence handle
//STRIP001 /*?*/            UINT32 nMarkAnz = aMark.GetMarkCount();
//STRIP001 /*?*/            if(nMarkAnz == 1)
//STRIP001 /*?*/            {
//STRIP001 /*?*/                SdrObject* pObj = aMark.GetMark(0)->GetObj();
//STRIP001 /*?*/                SdrModel* pModel = GetModel();
//STRIP001 /*?*/                const SfxItemSet& rSet = pObj->GetItemSet();
//STRIP001 /*?*/
//STRIP001 /*?*/                if(SFX_ITEM_SET != rSet.GetItemState(XATTR_FILLFLOATTRANSPARENCE, FALSE))
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    // add this item, it's not yet there
//STRIP001 /*?*/                    XFillFloatTransparenceItem aNewItem(
//STRIP001 /*?*/                        (const XFillFloatTransparenceItem&)rSet.Get(XATTR_FILLFLOATTRANSPARENCE));
//STRIP001 /*?*/                    XGradient aGrad = aNewItem.GetValue();
//STRIP001 /*?*/
//STRIP001 /*?*/                    aNewItem.SetEnabled(TRUE);
//STRIP001 /*?*/                    aGrad.SetStartIntens(100);
//STRIP001 /*?*/                    aGrad.SetEndIntens(100);
//STRIP001 /*?*/                    aNewItem.SetValue(aGrad);
//STRIP001 /*?*/
//STRIP001 /*?*/                    // add undo to allow user to take back this step
//STRIP001 /*?*/                    pModel->BegUndo(SVX_RESSTR(SIP_XA_FILLTRANSPARENCE));
//STRIP001 /*?*/                    pModel->AddUndo(new SdrUndoAttrObj(*pObj));
//STRIP001 /*?*/                    pModel->EndUndo();
//STRIP001 /*?*/
//STRIP001 /*?*/                    pObj->SetItemAndBroadcast(aNewItem);
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/                // set values and transform to vector set
//STRIP001 /*?*/                GradTransformer aGradTransformer;
//STRIP001 /*?*/                GradTransVector aGradTransVector;
//STRIP001 /*?*/                GradTransGradient aGradTransGradient;
//STRIP001 /*?*/
//STRIP001 /*?*/                aGradTransGradient.aGradient = ((XFillFloatTransparenceItem&)rSet.Get(XATTR_FILLFLOATTRANSPARENCE)).GetValue();
//STRIP001 /*?*/                aGradTransformer.GradToVec(aGradTransGradient, aGradTransVector, pObj);
//STRIP001 /*?*/
//STRIP001 /*?*/                // build handles
//STRIP001 /*?*/                SdrHdlColor* pColHdl1 = new SdrHdlColor(aGradTransVector.aPos1, aGradTransVector.aCol1, SDR_HANDLE_COLOR_SIZE_NORMAL, TRUE);
//STRIP001 /*?*/                SdrHdlColor* pColHdl2 = new SdrHdlColor(aGradTransVector.aPos2, aGradTransVector.aCol2, SDR_HANDLE_COLOR_SIZE_NORMAL, TRUE);
//STRIP001 /*?*/                SdrHdlGradient* pGradHdl = new SdrHdlGradient(aGradTransVector.aPos1, aGradTransVector.aPos2, FALSE);
//STRIP001 /*?*/                DBG_ASSERT(pColHdl1 && pColHdl2 && pGradHdl, "Got not all necessary handles!!");
//STRIP001 /*?*/
//STRIP001 /*?*/                // link them
//STRIP001 /*?*/                pGradHdl->SetColorHandles(pColHdl1, pColHdl2);
//STRIP001 /*?*/                pGradHdl->SetObj(pObj);
//STRIP001 /*?*/                pColHdl1->SetColorChangeHdl(LINK(pGradHdl, SdrHdlGradient, ColorChangeHdl));
//STRIP001 /*?*/                pColHdl2->SetColorChangeHdl(LINK(pGradHdl, SdrHdlGradient, ColorChangeHdl));
//STRIP001 /*?*/
//STRIP001 /*?*/                // insert them
//STRIP001 /*?*/                aHdl.AddHdl(pColHdl1);
//STRIP001 /*?*/                aHdl.AddHdl(pColHdl2);
//STRIP001 /*?*/                aHdl.AddHdl(pGradHdl);
//STRIP001 /*?*/            }
/*?*/           break;
/*?*/       }
/*?*/       case SDRDRAG_GRADIENT:
/*?*/       {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            // add interactive gradient handle
//STRIP001 /*?*/            UINT32 nMarkAnz = aMark.GetMarkCount();
//STRIP001 /*?*/            if(nMarkAnz == 1)
//STRIP001 /*?*/            {
//STRIP001 /*?*/                SdrObject* pObj = aMark.GetMark(0)->GetObj();
//STRIP001 /*?*/                const SfxItemSet& rSet = pObj->GetItemSet();
//STRIP001 /*?*/                XFillStyle eFillStyle = ((XFillStyleItem&)(rSet.Get(XATTR_FILLSTYLE))).GetValue();
//STRIP001 /*?*/
//STRIP001 /*?*/                if(eFillStyle == XFILL_GRADIENT)
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    // set values and transform to vector set
//STRIP001 /*?*/                    GradTransformer aGradTransformer;
//STRIP001 /*?*/                    GradTransVector aGradTransVector;
//STRIP001 /*?*/                    GradTransGradient aGradTransGradient;
//STRIP001 /*?*/                    Size aHdlSize(15, 15);
//STRIP001 /*?*/
//STRIP001 /*?*/                    aGradTransGradient.aGradient = ((XFillGradientItem&)rSet.Get(XATTR_FILLGRADIENT)).GetValue();
//STRIP001 /*?*/                    aGradTransformer.GradToVec(aGradTransGradient, aGradTransVector, pObj);
//STRIP001 /*?*/
//STRIP001 /*?*/                    // build handles
//STRIP001 /*?*/                    SdrHdlColor* pColHdl1 = new SdrHdlColor(aGradTransVector.aPos1, aGradTransVector.aCol1, aHdlSize, FALSE);
//STRIP001 /*?*/                    SdrHdlColor* pColHdl2 = new SdrHdlColor(aGradTransVector.aPos2, aGradTransVector.aCol2, aHdlSize, FALSE);
//STRIP001 /*?*/                    SdrHdlGradient* pGradHdl = new SdrHdlGradient(aGradTransVector.aPos1, aGradTransVector.aPos2, TRUE);
//STRIP001 /*?*/                    DBG_ASSERT(pColHdl1 && pColHdl2 && pGradHdl, "Got not all necessary handles!!");
//STRIP001 /*?*/
//STRIP001 /*?*/                    // link them
//STRIP001 /*?*/                    pGradHdl->SetColorHandles(pColHdl1, pColHdl2);
//STRIP001 /*?*/                    pGradHdl->SetObj(pObj);
//STRIP001 /*?*/                    pColHdl1->SetColorChangeHdl(LINK(pGradHdl, SdrHdlGradient, ColorChangeHdl));
//STRIP001 /*?*/                    pColHdl2->SetColorChangeHdl(LINK(pGradHdl, SdrHdlGradient, ColorChangeHdl));
//STRIP001 /*?*/
//STRIP001 /*?*/                    // insert them
//STRIP001 /*?*/                    aHdl.AddHdl(pColHdl1);
//STRIP001 /*?*/                    aHdl.AddHdl(pColHdl2);
//STRIP001 /*?*/                    aHdl.AddHdl(pGradHdl);
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
/*?*/           break;
/*N*/       }
/*N*/   }
/*N*/ }

//STRIP001 void SdrMarkView::ForceRefToMarked()
//STRIP001 {
//STRIP001  switch(eDragMode)
//STRIP001  {
//STRIP001      case SDRDRAG_ROTATE:
//STRIP001      {
//STRIP001          Rectangle aR(GetMarkedObjRect());
//STRIP001          aRef1 = aR.Center();
//STRIP001
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      case SDRDRAG_MIRROR:
//STRIP001      {
//STRIP001          // Erstmal die laenge der Spiegelachsenlinie berechnen
//STRIP001          long nOutMin=0;
//STRIP001          long nOutMax=0;
//STRIP001          long nMinLen=0;
//STRIP001          long nObjDst=0;
//STRIP001          long nOutHgt=0;
//STRIP001          OutputDevice* pOut=GetWin(0);
//STRIP001          if (pOut!=NULL) {
//STRIP001              // Mindestlaenge 50 Pixel
//STRIP001              nMinLen=pOut->PixelToLogic(Size(0,50)).Height();
//STRIP001              // 20 Pixel fuer RefPt-Abstand vom Obj
//STRIP001              nObjDst=pOut->PixelToLogic(Size(0,20)).Height();
//STRIP001              // MinY/MaxY
//STRIP001              // Abstand zum Rand = Mindestlaenge = 10 Pixel
//STRIP001              long nDst=pOut->PixelToLogic(Size(0,10)).Height();
//STRIP001              nOutMin=-pOut->GetMapMode().GetOrigin().Y();
//STRIP001              nOutMax=pOut->GetOutputSize().Height()-1+nOutMin;
//STRIP001              nOutMin+=nDst;
//STRIP001              nOutMax-=nDst;
//STRIP001              // Absolute Mindestlaenge jedoch 10 Pixel
//STRIP001              if (nOutMax-nOutMin<nDst) {
//STRIP001                  nOutMin+=nOutMax+1;
//STRIP001                  nOutMin/=2;
//STRIP001                  nOutMin-=(nDst+1)/2;
//STRIP001                  nOutMax=nOutMin+nDst;
//STRIP001              }
//STRIP001              nOutHgt=nOutMax-nOutMin;
//STRIP001              // Sonst Mindestlaenge = 1/4 OutHgt
//STRIP001              long nTemp=nOutHgt/4;
//STRIP001              if (nTemp>nMinLen) nMinLen=nTemp;
//STRIP001          }
//STRIP001
//STRIP001          Rectangle aR(GetMarkedObjBoundRect());
//STRIP001          Point aCenter(aR.Center());
//STRIP001          long nMarkHgt=aR.GetHeight()-1;
//STRIP001          long nHgt=nMarkHgt+nObjDst*2;       // 20 Pixel obej und unten ueberstehend
//STRIP001          if (nHgt<nMinLen) nHgt=nMinLen;     // Mindestlaenge 50 Pixel bzw. 1/4 OutHgt
//STRIP001
//STRIP001          long nY1=aCenter.Y()-(nHgt+1)/2;
//STRIP001          long nY2=nY1+nHgt;
//STRIP001
//STRIP001          if (pOut!=NULL && nMinLen>nOutHgt) nMinLen=nOutHgt; // evtl. noch etwas verkuerzen
//STRIP001
//STRIP001          if (pOut!=NULL) { // nun vollstaendig in den sichtbaren Bereich schieben
//STRIP001              if (nY1<nOutMin) {
//STRIP001                  nY1=nOutMin;
//STRIP001                  if (nY2<nY1+nMinLen) nY2=nY1+nMinLen;
//STRIP001              }
//STRIP001              if (nY2>nOutMax) {
//STRIP001                  nY2=nOutMax;
//STRIP001                  if (nY1>nY2-nMinLen) nY1=nY2-nMinLen;
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          aRef1.X()=aCenter.X();
//STRIP001          aRef1.Y()=nY1;
//STRIP001          aRef2.X()=aCenter.X();
//STRIP001          aRef2.Y()=nY2;
//STRIP001
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      case SDRDRAG_TRANSPARENCE:
//STRIP001      case SDRDRAG_GRADIENT:
//STRIP001      {
//STRIP001          Rectangle aRect(GetMarkedObjBoundRect());
//STRIP001          aRef1 = aRect.TopLeft();
//STRIP001          aRef2 = aRect.BottomRight();
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrMarkView::SetRef1(const Point& rPt)
//STRIP001 {
//STRIP001  if(eDragMode == SDRDRAG_ROTATE || eDragMode == SDRDRAG_MIRROR)
//STRIP001  {
//STRIP001      aRef1 = rPt;
//STRIP001      SdrHdl* pH = aHdl.GetHdl(HDL_REF1);
//STRIP001      if(pH)
//STRIP001          pH->SetPos(rPt);
//STRIP001      ShowMarkHdl(NULL);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrMarkView::SetRef2(const Point& rPt)
//STRIP001 {
//STRIP001  if(eDragMode == SDRDRAG_MIRROR)
//STRIP001  {
//STRIP001      aRef2 = rPt;
//STRIP001      SdrHdl* pH = aHdl.GetHdl(HDL_REF2);
//STRIP001      if(pH)
//STRIP001          pH->SetPos(rPt);
//STRIP001      ShowMarkHdl(NULL);
//STRIP001  }
//STRIP001 }

/*N*/ void SdrMarkView::CheckMarked()
/*N*/ {
/*N*/   for (ULONG nm=aMark.GetMarkCount(); nm>0;) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        nm--;
//STRIP001 /*?*/        SdrMark* pM=aMark.GetMark(nm);
//STRIP001 /*?*/        SdrObject* pObj=pM->GetObj();
//STRIP001 /*?*/        SdrPageView* pPV=pM->GetPageView();
//STRIP001 /*?*/        SdrLayerID nLay=pObj->GetLayer();
//STRIP001 /*?*/        BOOL bRaus=!pObj->IsInserted(); // Obj geloescht?
//STRIP001 /*?*/        if (!pObj->Is3DObj()) {
//STRIP001 /*?*/            bRaus=bRaus || pObj->GetPage()!=pPV->GetPage();   // Obj ploetzlich in anderer Page oder Group
//STRIP001 /*?*/        }
//STRIP001 /*?*/        bRaus=bRaus || pPV->GetLockedLayers().IsSet(nLay) ||  // Layer gesperrt?
//STRIP001 /*?*/                       !pPV->GetVisibleLayers().IsSet(nLay);  // Layer nicht sichtbar?
//STRIP001 /*?*/        if (!bRaus) {
//STRIP001 /*?*/            // Joe am 9.3.1997: Gruppierte Objekten koennen nun auch
//STRIP001 /*?*/            // markiert werden. Nach EnterGroup muessen aber die Objekte
//STRIP001 /*?*/            // der hoeheren Ebene deselektiert werden.
//STRIP001 /*?*/            const SdrObjList* pOOL=pObj->GetObjList();
//STRIP001 /*?*/            const SdrObjList* pVOL=pPV->GetObjList();
//STRIP001 /*?*/            while (pOOL!=NULL && pOOL!=pVOL) {
//STRIP001 /*?*/                pOOL=pOOL->GetUpList();
//STRIP001 /*?*/            }
//STRIP001 /*?*/            bRaus=pOOL!=pVOL;
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        if (bRaus) {
//STRIP001 /*?*/            aMark.DeleteMarkNum(nm);
//STRIP001 /*?*/        } else {
//STRIP001 /*?*/            if (!IsGluePointEditMode()) { // Markierte GluePoints nur im GlueEditMode
//STRIP001 /*?*/                SdrUShortCont* pPts=pM->GetMarkedGluePoints();
//STRIP001 /*?*/                if (pPts!=NULL && pPts->GetCount()!=0) {
//STRIP001 /*?*/                    pPts->Clear();
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
/*N*/   }

    // #67670# When this leads to a change, MarkListHasChanged()
    // had been called before. Calling MarkListHasChanged() again
    // could lead to problems in sfx, see BUG description.
    //  if(bChg)
    //      MarkListHasChanged();

    // #97995# at least reset the remembered BoundRect to prevent handle
    // generation if bForceFrameHandles is TRUE.
/*N*/   bMarkedObjRectDirty = TRUE;
/*N*/ }

// for SW and their rearranged painting; this method forces the
// actual IAO-Handles to throw away saved contents
/*N*/ void SdrMarkView::ForceInvalidateMarkHandles()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  // #86973#
//STRIP001  aHdl.Clear();
/*N*/ }

/*N*/ void SdrMarkView::SetMarkRects()
/*N*/ {
/*N*/   for (USHORT nv=0; nv<GetPageViewCount(); nv++) {
/*N*/       SdrPageView* pPV=GetPageViewPvNum(nv);
/*N*/       pPV->SetHasMarkedObj(aMark.TakeSnapRect(pPV,pPV->MarkSnap()));
/*N*/       aMark.TakeBoundRect(pPV,pPV->MarkBound());
/*N*/   }
/*N*/ }

/*N*/ void SdrMarkView::SetFrameHandles(BOOL bOn)
/*N*/ {
/*N*/   if (bOn!=bForceFrameHandles) {
/*N*/       BOOL bOld=ImpIsFrameHandles();
/*N*/       bForceFrameHandles=bOn;
/*N*/       BOOL bNew=ImpIsFrameHandles();
/*N*/       if (bNew!=bOld) {
/*N*/           AdjustMarkHdl(TRUE);
/*N*/           MarkListHasChanged();
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void SdrMarkView::SetEditMode(SdrViewEditMode eMode)
/*N*/ {
/*N*/   if (eMode!=eEditMode) {
/*N*/       BOOL bGlue0=eEditMode==SDREDITMODE_GLUEPOINTEDIT;
/*N*/       BOOL bEdge0=((SdrCreateView*)this)->IsEdgeTool();
/*N*/       eEditMode0=eEditMode;
/*N*/       eEditMode=eMode;
/*N*/       BOOL bGlue1=eEditMode==SDREDITMODE_GLUEPOINTEDIT;
/*N*/       BOOL bEdge1=((SdrCreateView*)this)->IsEdgeTool();
/*N*/       // etwas Aufwand um Flackern zu verhindern beim Umschalten
/*N*/       // zwischen GlueEdit und EdgeTool
/*N*/       if (bGlue1 && !bGlue0) ImpSetGlueVisible2(bGlue1);
/*N*/       if (bEdge1!=bEdge0) ImpSetGlueVisible3(bEdge1);
/*N*/       if (!bGlue1 && bGlue0) ImpSetGlueVisible2(bGlue1);
/*N*/       if (bGlue0 && !bGlue1) UnmarkAllGluePoints();
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ BOOL SdrMarkView::IsObjMarkable(SdrObject* pObj, SdrPageView* pPV) const
/*N*/ {
/*N*/   if (pObj)
/*N*/   {
/*N*/       if (pObj->IsMarkProtect() ||
/*N*/           (!bDesignMode && pObj->IsUnoObj()))
/*N*/       {
/*N*/           // Objekt nicht selektierbar oder
/*N*/           // SdrUnoObj nicht im DesignMode
/*N*/           return FALSE;
/*N*/       }
/*N*/   }
/*N*/   return pPV!=NULL ? pPV->IsObjMarkable(pObj) : TRUE;
/*N*/ }

//STRIP001 BOOL SdrMarkView::IsMarkedObjHit(const Point& rPnt, short nTol) const
//STRIP001 {
//STRIP001  BOOL bRet=FALSE;
//STRIP001  nTol=ImpGetHitTolLogic(nTol,NULL);
//STRIP001  Point aPt(rPnt);
//STRIP001  for (ULONG nm=0; nm<aMark.GetMarkCount() && !bRet; nm++) {
//STRIP001      SdrMark* pM=aMark.GetMark(nm);
//STRIP001      bRet=ImpIsObjHit(aPt,USHORT(nTol),pM->GetObj(),pM->GetPageView(),0);
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*N*/ SdrHdl* SdrMarkView::PickHandle(const Point& rPnt, const OutputDevice& rOut, ULONG nOptions, SdrHdl* pHdl0) const
/*N*/ {
/*N*/   if (&rOut==NULL) return FALSE;
/*N*/   if (bSomeObjChgdFlag) { // ggf. Handles neu berechnen lassen!
/*N*/       FlushComeBackTimer();
/*N*/   }
/*N*/   BOOL bBack=(nOptions & SDRSEARCH_BACKWARD) !=0;
/*N*/   BOOL bNext=(nOptions & SDRSEARCH_NEXT) !=0;
/*N*/   Point aPt(rPnt);
/*N*/   return aHdl.HitTest(aPt,rOut,bBack,bNext,pHdl0);
/*N*/ }

//STRIP001 BOOL SdrMarkView::MarkObj(const Point& rPnt, short nTol, BOOL bToggle, BOOL bDeep)
//STRIP001 {
//STRIP001  SdrObject* pObj;
//STRIP001  SdrPageView* pPV;
//STRIP001  nTol=ImpGetHitTolLogic(nTol,NULL);
//STRIP001  ULONG nOptions=SDRSEARCH_PICKMARKABLE;
//STRIP001  if (bDeep) nOptions=nOptions|SDRSEARCH_DEEP;
//STRIP001  BOOL bRet=PickObj(rPnt,(USHORT)nTol,pObj,pPV,nOptions);
//STRIP001  if (bRet) {
//STRIP001      BOOL bUnmark=bToggle && IsObjMarked(pObj);
//STRIP001      MarkObj(pObj,pPV,bUnmark);
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SdrMarkView::MarkNextObj(BOOL bPrev)
//STRIP001 {
//STRIP001  USHORT nPvAnz=GetPageViewCount();
//STRIP001  if (nPvAnz==0) return FALSE;
//STRIP001  USHORT nMaxPV=USHORT(nPvAnz-1);
//STRIP001  aMark.ForceSort();
//STRIP001  ULONG  nMarkAnz=aMark.GetMarkCount();
//STRIP001  ULONG  nChgMarkNum=0xFFFFFFFF; // Nummer des zu ersetzenden MarkEntries
//STRIP001  USHORT nSearchPvNum=bPrev ? 0 : nMaxPV;
//STRIP001  ULONG  nSearchObjNum=bPrev ? 0 : 0xFFFFFFFF;
//STRIP001  if (nMarkAnz!=0) {
//STRIP001      nChgMarkNum=bPrev ? 0 : ULONG(nMarkAnz-1);
//STRIP001      SdrMark* pM=aMark.GetMark(nChgMarkNum);
//STRIP001      nSearchObjNum=pM->GetObj()->GetOrdNum();
//STRIP001      nSearchPvNum=GetPageViewNum(pM->GetPageView());
//STRIP001  }
//STRIP001  SdrObject* pMarkObj=NULL;
//STRIP001  SdrPageView* pMarkPV=NULL;
//STRIP001  while (pMarkObj==NULL) {
//STRIP001      SdrPageView* pSearchPV=GetPageViewPvNum(nSearchPvNum);
//STRIP001      SdrObjList* pSearchObjList=pSearchPV->GetObjList();
//STRIP001      ULONG nObjAnz=pSearchObjList->GetObjCount();
//STRIP001      if (nObjAnz!=0) {
//STRIP001          if (nSearchObjNum>nObjAnz) nSearchObjNum=nObjAnz;
//STRIP001          while (pMarkObj==NULL && ((!bPrev && nSearchObjNum>0) || (bPrev && nSearchObjNum<nObjAnz))) {
//STRIP001              if (!bPrev) nSearchObjNum--;
//STRIP001              SdrObject* pSearchObj=pSearchObjList->GetObj(nSearchObjNum);
//STRIP001              if (IsObjMarkable(pSearchObj,pSearchPV)) {
//STRIP001                  if (aMark.FindObject(pSearchObj)==CONTAINER_ENTRY_NOTFOUND) {
//STRIP001                      pMarkObj=pSearchObj;
//STRIP001                      pMarkPV=pSearchPV;
//STRIP001                  }
//STRIP001              }
//STRIP001              if (bPrev) nSearchObjNum++;
//STRIP001          }
//STRIP001      }
//STRIP001      if (pMarkObj==NULL) {
//STRIP001          if (bPrev) {
//STRIP001              if (nSearchPvNum>=nMaxPV) return FALSE;
//STRIP001              nSearchPvNum++;
//STRIP001              nSearchObjNum=0;
//STRIP001          } else {
//STRIP001              if (nSearchPvNum==0) return FALSE;
//STRIP001              nSearchPvNum--;
//STRIP001              nSearchObjNum=0xFFFFFFFF;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if (nChgMarkNum!=0xFFFFFFFF) aMark.DeleteMark(nChgMarkNum);
//STRIP001  MarkObj(pMarkObj,pMarkPV); // ruft auch MarkListHasChanged(), AdjustMarkHdl()
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL SdrMarkView::MarkNextObj(const Point& rPnt, short nTol, BOOL bPrev)
//STRIP001 {
//STRIP001  aMark.ForceSort();
//STRIP001  nTol=ImpGetHitTolLogic(nTol,NULL);
//STRIP001  Point aPt(rPnt);
//STRIP001  SdrMark* pTopMarkHit=NULL;
//STRIP001  SdrMark* pBtmMarkHit=NULL;
//STRIP001  ULONG nTopMarkHit=0;
//STRIP001  ULONG nBtmMarkHit=0;
//STRIP001  // oberstes der markierten Objekte suchen, das von rPnt getroffen wird
//STRIP001  ULONG nMarkAnz=aMark.GetMarkCount();
//STRIP001  ULONG nm=0;
//STRIP001  for (nm=nMarkAnz; nm>0 && pTopMarkHit==NULL;) {
//STRIP001      nm--;
//STRIP001      SdrMark* pM=aMark.GetMark(nm);
//STRIP001      if (ImpIsObjHit(aPt,USHORT(nTol),pM->GetObj(),pM->GetPageView(),0)) {
//STRIP001          pTopMarkHit=pM;
//STRIP001          nTopMarkHit=nm;
//STRIP001      }
//STRIP001  }
//STRIP001  // Nichts gefunden, dann ganz normal ein Obj markieren.
//STRIP001  if (pTopMarkHit==NULL) return MarkObj(rPnt,USHORT(nTol),FALSE);
//STRIP001
//STRIP001  SdrObject* pTopObjHit=pTopMarkHit->GetObj();
//STRIP001  SdrObjList* pObjList=pTopObjHit->GetObjList();
//STRIP001  SdrPageView* pPV=pTopMarkHit->GetPageView();
//STRIP001  // unterstes der markierten Objekte suchen, das von rPnt getroffen wird
//STRIP001  // und auf der gleichen PageView liegt wie pTopMarkHit
//STRIP001  for (nm=0; nm<nMarkAnz && pBtmMarkHit==NULL; nm++) {
//STRIP001      SdrMark* pM=aMark.GetMark(nm);
//STRIP001      SdrPageView* pPV2=pM->GetPageView();
//STRIP001      if (pPV2==pPV && ImpIsObjHit(aPt,USHORT(nTol),pM->GetObj(),pPV2,0)) {
//STRIP001          pBtmMarkHit=pM;
//STRIP001          nBtmMarkHit=nm;
//STRIP001      }
//STRIP001  }
//STRIP001  if (pBtmMarkHit==NULL) { pBtmMarkHit=pTopMarkHit; nBtmMarkHit=nTopMarkHit; }
//STRIP001  SdrObject* pBtmObjHit=pBtmMarkHit->GetObj();
//STRIP001
//STRIP001  ULONG nObjAnz=pObjList->GetObjCount();
//STRIP001  ULONG nSearchBeg=bPrev ? pBtmObjHit->GetOrdNum()+1 : pTopObjHit->GetOrdNum();
//STRIP001  ULONG no=nSearchBeg;
//STRIP001  SdrObject* pFndObj=NULL;
//STRIP001  SdrObject* pAktObj=NULL;
//STRIP001  while (pFndObj==NULL && ((!bPrev && no>0) || (bPrev && no<nObjAnz))) {
//STRIP001      if (!bPrev) no--;
//STRIP001      SdrObject* pObj=pObjList->GetObj(no);
//STRIP001      if (ImpIsObjHit(aPt,USHORT(nTol),pObj,pPV,SDRSEARCH_TESTMARKABLE)) {
//STRIP001          if (aMark.FindObject(pObj)==CONTAINER_ENTRY_NOTFOUND) {
//STRIP001              pFndObj=pObj;
//STRIP001          } else {
//STRIP001              // hier wg. Performance ggf. noch no auf Top bzw. auf Btm stellen
//STRIP001          }
//STRIP001      }
//STRIP001      if (bPrev) no++;
//STRIP001  }
//STRIP001  if (pFndObj!=NULL) {
//STRIP001      aMark.DeleteMark(bPrev?nBtmMarkHit:nTopMarkHit);
//STRIP001      aMark.InsertEntry(SdrMark(pFndObj,pPV));
//STRIP001      MarkListHasChanged();
//STRIP001      AdjustMarkHdl(TRUE);
//STRIP001  }
//STRIP001  return pFndObj!=NULL;
//STRIP001 }

//STRIP001 BOOL SdrMarkView::MarkObj(const Rectangle& rRect, BOOL bUnmark)
//STRIP001 {
//STRIP001  BOOL bFnd=FALSE;
//STRIP001  Rectangle aR(rRect);
//STRIP001  SdrObject* pObj;
//STRIP001  SdrObjList* pObjList;
//STRIP001  BrkAction();
//STRIP001  for (USHORT nv=0; nv<GetPageViewCount(); nv++) {
//STRIP001      SdrPageView* pPV=GetPageViewPvNum(nv);
//STRIP001      pObjList=pPV->GetObjList();
//STRIP001      Rectangle aFrm1(aR);
//STRIP001      aFrm1-=pPV->GetOffset(); // Selektionsrahmen auf die PageView transformieren
//STRIP001      ULONG nObjAnz=pObjList->GetObjCount();
//STRIP001      for (ULONG nO=0; nO<nObjAnz; nO++) {
//STRIP001          pObj=pObjList->GetObj(nO);
//STRIP001          Rectangle aRect(pObj->GetBoundRect());
//STRIP001          if (aFrm1.IsInside(aRect)) {
//STRIP001              if (!bUnmark) {
//STRIP001                  if (IsObjMarkable(pObj,pPV)) {
//STRIP001                      aMark.InsertEntry(SdrMark(pObj,pPV));
//STRIP001                      bFnd=TRUE;
//STRIP001                  }
//STRIP001              } else {
//STRIP001                  ULONG nPos=aMark.FindObject(pObj);
//STRIP001                  if (nPos!=CONTAINER_ENTRY_NOTFOUND) {
//STRIP001                      aMark.DeleteMark(nPos);
//STRIP001                      bFnd=TRUE;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if (bFnd) {
//STRIP001      aMark.ForceSort();
//STRIP001      MarkListHasChanged();
//STRIP001      AdjustMarkHdl(TRUE);
//STRIP001      ShowMarkHdl(NULL);
//STRIP001  }
//STRIP001  return bFnd;
//STRIP001 }

/*N*/ void SdrMarkView::MarkObj(SdrObject* pObj, SdrPageView* pPV, BOOL bUnmark, BOOL bImpNoSetMarkHdl)
/*N*/ {
/*N*/   if (pObj!=NULL && pPV!=NULL && IsObjMarkable(pObj, pPV)) {
/*N*/       BrkAction();
/*N*/       if (!bUnmark) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            aMark.InsertEntry(SdrMark(pObj,pPV));
/*N*/       } else {
/*N*/           ULONG nPos=aMark.FindObject(pObj);
/*N*/           if (nPos!=CONTAINER_ENTRY_NOTFOUND) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/                aMark.DeleteMark(nPos);
/*N*/           }
/*N*/       }
/*N*/       if (!bImpNoSetMarkHdl) {
/*N*/           MarkListHasChanged();
/*N*/           AdjustMarkHdl(TRUE);
/*N*/ //            if (!IsSolidMarkHdl() || !bSomeObjChgdFlag) {
/*N*/           if (!bSomeObjChgdFlag) {
/*N*/               // ShowMarkHdl kommt sonst mit dem AfterPaintTimer
/*N*/               ShowMarkHdl(NULL);
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

//STRIP001 BOOL SdrMarkView::IsObjMarked(SdrObject* pObj) const
//STRIP001 {
//STRIP001  // nicht so ganz die feine Art: Da FindObject() nicht const ist
//STRIP001  // muss ich mich hier auf non-const casten.
//STRIP001  ULONG nPos=((SdrMarkView*)this)->aMark.FindObject(pObj);
//STRIP001  return nPos!=CONTAINER_ENTRY_NOTFOUND;
//STRIP001 }

/*N*/ USHORT SdrMarkView::GetMarkHdlSizePixel() const
/*N*/ {
/*N*/   return aHdl.GetHdlSize()*2+1;
/*N*/ }

/*N*/ void SdrMarkView::SetSolidMarkHdl(BOOL bOn)
/*N*/ {
/*N*/   if (bOn!=aHdl.IsFineHdl()) {
/*N*/       BOOL bMerk=IsMarkHdlShown();
/*N*/       if (bMerk) HideMarkHdl(NULL);
/*N*/       aHdl.SetFineHdl(bOn);
/*N*/       if (bMerk) ShowMarkHdl(NULL);
/*N*/   }
/*N*/ }

/*N*/ void SdrMarkView::SetMarkHdlSizePixel(USHORT nSiz)
/*N*/ {
/*N*/   if (nSiz<3) nSiz=3;
/*N*/   nSiz/=2;
/*N*/   if (nSiz!=aHdl.GetHdlSize()) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        BOOL bMerk=IsMarkHdlShown();
//STRIP001 /*?*/        if (bMerk) HideMarkHdl(NULL);
//STRIP001 /*?*/        aHdl.SetHdlSize(nSiz);
//STRIP001 /*?*/        if (bMerk) ShowMarkHdl(NULL);
/*N*/   }
/*N*/ }

/*N*/ #define SDRSEARCH_IMPISMASTER 0x80000000 /* MasterPage wird gerade durchsucht */
/*N*/ SdrObject* SdrMarkView::ImpCheckObjHit(const Point& rPnt, USHORT nTol, SdrObject* pObj, SdrPageView* pPV, ULONG nOptions, const SetOfByte* pMVisLay) const
/*N*/ {
/*N*/   if ((nOptions & SDRSEARCH_IMPISMASTER) !=0 && pObj->IsNotVisibleAsMaster()) {
/*N*/       return NULL;
/*N*/   }
/*N*/   BOOL bCheckIfMarkable=(nOptions & SDRSEARCH_TESTMARKABLE)!=0;
/*N*/   BOOL bBack=(nOptions & SDRSEARCH_BACKWARD)!=0;
/*N*/   BOOL bDeep=(nOptions & SDRSEARCH_DEEP)!=0;
/*N*/   BOOL bOLE=pObj->ISA(SdrOle2Obj);
/*N*/   SdrObject* pRet=NULL;
/*N*/   Point aPnt1(rPnt-pPV->GetOffset()); // rPnt auf PageView transformieren
/*N*/   Rectangle aRect(pObj->GetBoundRect());
/*N*/   USHORT nTol2=nTol;
/*N*/   // Doppelte Tolezanz fuer ein an dieser View im TextEdit befindliches Objekt
/*N*/   if (bOLE || pObj==((SdrObjEditView*)this)->GetTextEditObject()) nTol2*=2;
/*N*/   aRect.Left  ()-=nTol2; // Einmal Toleranz drauf fuer alle Objekte
/*N*/   aRect.Top   ()-=nTol2;
/*N*/   aRect.Right ()+=nTol2;
/*N*/   aRect.Bottom()+=nTol2;
/*N*/   if (aRect.IsInside(aPnt1)) {
/*N*/       if ((!bCheckIfMarkable || IsObjMarkable(pObj,pPV))) {
/*N*/           SdrObjList* pOL=pObj->GetSubList();
/*N*/           if (pOL!=NULL && pOL->GetObjCount()!=0) {
/*N*/               SdrObject* pTmpObj;
/*N*/                 // OD 30.06.2003 #108784# - adjustment hit point for virtual
/*N*/                 // objects.
/*N*/                 Point aPnt( rPnt );
/*N*/                 if ( pObj->ISA(SdrVirtObj) )
/*N*/                 {
/*N*/                     Point aOffset = static_cast<SdrVirtObj*>(pObj)->GetOffset();
/*N*/                     aPnt.Move( -aOffset.X(), -aOffset.Y() );
/*N*/                 }
/*N*/                 pRet=ImpCheckObjHit(aPnt,nTol,pOL,pPV,nOptions,pMVisLay,pTmpObj);
/*N*/           } else {
/*N*/               SdrLayerID nLay=pObj->GetLayer();
/*N*/               if (pPV->GetVisibleLayers().IsSet(nLay) &&
/*N*/                   (pMVisLay==NULL || pMVisLay->IsSet(nLay)))
/*N*/               {
/*N*/                   pRet=pObj->CheckHit(aPnt1,nTol2,&pPV->GetVisibleLayers());
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   if (!bDeep && pRet!=NULL) pRet=pObj;
/*N*/   return pRet;
/*N*/ }

/*N*/ SdrObject* SdrMarkView::ImpCheckObjHit(const Point& rPnt, USHORT nTol, SdrObjList* pOL, SdrPageView* pPV, ULONG nOptions, const SetOfByte* pMVisLay, SdrObject*& rpRootObj) const
/*N*/ {
/*N*/   BOOL bBack=(nOptions & SDRSEARCH_BACKWARD)!=0;
/*N*/   SdrObject* pRet=NULL;
/*N*/   rpRootObj=NULL;
/*N*/   if (pOL!=NULL) {
/*N*/       ULONG nObjAnz=pOL->GetObjCount();
/*N*/       ULONG nObjNum=bBack ? 0 : nObjAnz;
/*N*/       while (pRet==NULL && (bBack ? nObjNum<nObjAnz : nObjNum>0)) {
/*N*/           if (!bBack) nObjNum--;
/*N*/           SdrObject* pObj=pOL->GetObj(nObjNum);
/*N*/           pRet=ImpCheckObjHit(rPnt,nTol,pObj,pPV,nOptions,pMVisLay);
/*N*/           if (pRet!=NULL) rpRootObj=pObj;
/*N*/           if (bBack) nObjNum++;
/*N*/       }
/*N*/   }
/*N*/   return pRet;
/*N*/ }

/*N*/ BOOL SdrMarkView::PickObj(const Point& rPnt, short nTol, SdrObject*& rpObj, SdrPageView*& rpPV, ULONG nOptions) const
/*N*/ {
/*N*/   return PickObj(rPnt,nTol,rpObj,rpPV,nOptions,NULL,NULL,NULL);
/*N*/ }

/*N*/ BOOL SdrMarkView::PickObj(const Point& rPnt, short nTol, SdrObject*& rpObj, SdrPageView*& rpPV, ULONG nOptions, SdrObject** ppRootObj, ULONG* pnMarkNum, USHORT* pnPassNum) const
/*N*/ { // Fehlt noch Pass2,Pass3
/*N*/   ((SdrMarkView*)this)->aMark.ForceSort();
/*N*/   if (ppRootObj!=NULL) *ppRootObj=NULL;
/*N*/   if (pnMarkNum!=NULL) *pnMarkNum=CONTAINER_ENTRY_NOTFOUND;
/*N*/   if (pnPassNum!=NULL) *pnPassNum=0;
/*N*/   rpObj=NULL;
/*N*/   rpPV=NULL;
/*N*/   BOOL bWholePage=(nOptions & SDRSEARCH_WHOLEPAGE) !=0;
/*N*/   BOOL bMarked=(nOptions & SDRSEARCH_MARKED) !=0;
/*N*/   BOOL bMasters=!bMarked && (nOptions & SDRSEARCH_ALSOONMASTER) !=0;
/*N*/   BOOL bBack=(nOptions & SDRSEARCH_BACKWARD) !=0;
/*N*/   BOOL bNext=(nOptions & SDRSEARCH_NEXT) !=0; // n.i.
/*N*/   BOOL bBoundCheckOn2ndPass=(nOptions & SDRSEARCH_PASS2BOUND) !=0; // n.i.
/*N*/   BOOL bCheckNearestOn3rdPass=(nOptions & SDRSEARCH_PASS3NEAREST) !=0; // n.i.
/*N*/   if (nTol<0) nTol=ImpGetHitTolLogic(nTol,NULL);
/*N*/   Point aPt(rPnt);
/*N*/   SdrObject* pObj=NULL;
/*N*/   SdrObject* pHitObj=NULL;
/*N*/   SdrPageView* pPV=NULL;
/*N*/   if (!bBack && ((SdrObjEditView*)this)->IsTextEditFrameHit(rPnt)) {
/*?*/       pObj=((SdrObjEditView*)this)->GetTextEditObject();
/*?*/       pHitObj=pObj;
/*?*/       pPV=((SdrObjEditView*)this)->GetTextEditPageView();
/*N*/   }
/*N*/   if (bMarked) {
/*N*/       ULONG nMrkAnz=aMark.GetMarkCount();
/*N*/       ULONG nMrkNum=bBack ? 0 : nMrkAnz;
/*N*/       while (pHitObj==NULL && (bBack ? nMrkNum<nMrkAnz : nMrkNum>0)) {
/*?*/           if (!bBack) nMrkNum--;
/*?*/           SdrMark* pM=aMark.GetMark(nMrkNum);
/*?*/           pObj=pM->GetObj();
/*?*/           pPV=pM->GetPageView();
/*?*/           pHitObj=ImpCheckObjHit(aPt,nTol,pObj,pPV,nOptions,NULL);
/*?*/           if (bBack) nMrkNum++;
/*N*/       }
/*N*/   } else {
/*N*/       USHORT nPvAnz=GetPageViewCount();
/*N*/       USHORT nPvNum=bBack ? 0 : nPvAnz;
/*N*/       while (pHitObj==NULL && (bBack ? nPvNum<nPvAnz : nPvNum>0)) {
/*N*/           if (!bBack) nPvNum--;
/*N*/           pPV=GetPageViewPvNum(nPvNum);
/*N*/           SdrPage* pPage=pPV->GetPage();
/*N*/           USHORT nPgAnz=1; if (bMasters) nPgAnz+=pPage->GetMasterPageCount();
/*N*/           BOOL bExtraPassForWholePage=bWholePage && pPage!=pPV->GetObjList();
/*N*/           if (bExtraPassForWholePage) nPgAnz++; // Suche erst in AktObjList, dann auf der gesamten Page
/*N*/           USHORT nPgNum=bBack ? 0 : nPgAnz;
/*N*/           while (pHitObj==NULL && (bBack ? nPgNum<nPgAnz : nPgNum>0)) {
/*N*/               ULONG nTmpOptions=nOptions;
/*N*/               if (!bBack) nPgNum--;
/*N*/               const SetOfByte* pMVisLay=NULL;
/*N*/               SdrObjList* pObjList=NULL;
/*N*/               if (pnPassNum!=NULL) *pnPassNum&=~(SDRSEARCHPASS_MASTERPAGE|SDRSEARCHPASS_INACTIVELIST);
/*N*/               if (nPgNum>=nPgAnz-1 || (bExtraPassForWholePage && nPgNum>=nPgAnz-2)) {
/*N*/                   pObjList=pPV->GetObjList();
/*N*/                   if (bExtraPassForWholePage && nPgNum==nPgAnz-2) {
/*?*/                       pObjList=pPage;
/*?*/                       if (pnPassNum!=NULL) *pnPassNum|=SDRSEARCHPASS_INACTIVELIST;
/*N*/                   }
/*N*/               } else { // sonst MasterPage
/*N*/                   const SdrMasterPageDescriptor& rMPD=pPage->GetMasterPageDescriptor(nPgNum);
/*N*/                   USHORT nNum=rMPD.GetPageNum();
/*N*/                   pMVisLay=&rMPD.GetVisibleLayers();
/*N*/                   if (nNum<pMod->GetMasterPageCount()) { // sonst ungueltiger MasterPageDescriptor
/*N*/                       pObjList=pMod->GetMasterPage(nNum);
/*N*/                   }
/*N*/                   if (pnPassNum!=NULL) *pnPassNum|=SDRSEARCHPASS_MASTERPAGE;
/*N*/                   nTmpOptions=nTmpOptions | SDRSEARCH_IMPISMASTER;
/*N*/               }
/*N*/               pHitObj=ImpCheckObjHit(aPt,nTol,pObjList,pPV,nTmpOptions,pMVisLay,pObj);
/*N*/               if (bBack) nPgNum++;
/*N*/           }
/*N*/           if (bBack) nPvNum++;
/*N*/       }
/*N*/
/*N*/   }
/*N*/   if (pHitObj!=NULL) {
/*N*/       if (ppRootObj!=NULL) *ppRootObj=pObj;
/*N*/       if ((nOptions & SDRSEARCH_DEEP) !=0) pObj=pHitObj;
/*N*/       if ((nOptions & SDRSEARCH_TESTTEXTEDIT) !=0) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            if (!pObj->HasTextEdit() || pPV->GetLockedLayers().IsSet(pObj->GetLayer())) {
//STRIP001 /*?*/                pObj=NULL;
//STRIP001 /*?*/            }
/*N*/       }
/*N*/       if (pObj!=NULL && (nOptions & SDRSEARCH_TESTMACRO) !=0) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            Point aP(aPt); aP-=pPV->GetOffset();
//STRIP001 /*?*/            SdrObjMacroHitRec aHitRec;
//STRIP001 /*?*/            aHitRec.aPos=aPt;
//STRIP001 /*?*/            aHitRec.aDownPos=aPt;
//STRIP001 /*?*/            aHitRec.nTol=nTol;
//STRIP001 /*?*/            aHitRec.pVisiLayer=&pPV->GetVisibleLayers();
//STRIP001 /*?*/            aHitRec.pPageView=pPV;
//STRIP001 /*?*/            if (!pObj->HasMacro() || !pObj->IsMacroHit(aHitRec)) pObj=NULL;
/*N*/       }
/*N*/       if (pObj!=NULL && (nOptions & SDRSEARCH_WITHTEXT) !=0 && pObj->GetOutlinerParaObject()==NULL) pObj=NULL;
/*N*/       if (pObj!=NULL && (nOptions & SDRSEARCH_TESTTEXTAREA) !=0) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            Point aP(aPt); aP-=pPV->GetOffset();
//STRIP001 /*?*/            if (!pObj->IsTextEditHit(aPt,0/*nTol*/,NULL)) pObj=NULL;
/*N*/       }
/*N*/       if (pObj!=NULL) {
/*N*/           rpObj=pObj;
/*N*/           rpPV=pPV;
/*N*/           if (pnPassNum!=NULL) *pnPassNum|=SDRSEARCHPASS_DIRECT;
/*N*/       }
/*N*/   }
/*N*/   return rpObj!=NULL;
/*N*/ }

//STRIP001 BOOL SdrMarkView::PickMarkedObj(const Point& rPnt, SdrObject*& rpObj, SdrPageView*& rpPV, ULONG* pnMarkNum, ULONG nOptions) const
//STRIP001 {
//STRIP001  ((SdrMarkView*)this)->aMark.ForceSort();
//STRIP001  BOOL bBoundCheckOn2ndPass=(nOptions & SDRSEARCH_PASS2BOUND) !=0;
//STRIP001  BOOL bCheckNearestOn3rdPass=(nOptions & SDRSEARCH_PASS3NEAREST) !=0;
//STRIP001  rpObj=NULL;
//STRIP001  rpPV=NULL;
//STRIP001  if (pnMarkNum!=NULL) *pnMarkNum=CONTAINER_ENTRY_NOTFOUND;
//STRIP001  Point aPt(rPnt);
//STRIP001  USHORT nTol=(USHORT)nHitTolLog;
//STRIP001  BOOL bFnd=FALSE;
//STRIP001  ULONG nMarkAnz=aMark.GetMarkCount();
//STRIP001  ULONG nMarkNum;
//STRIP001  for (nMarkNum=nMarkAnz; nMarkNum>0 && !bFnd;) {
//STRIP001      nMarkNum--;
//STRIP001      SdrMark* pM=aMark.GetMark(nMarkNum);
//STRIP001      SdrPageView* pPV=pM->GetPageView();
//STRIP001      SdrObject* pObj=pM->GetObj();
//STRIP001      bFnd=ImpIsObjHit(aPt,nTol,pObj,pPV,SDRSEARCH_TESTMARKABLE);
//STRIP001      if (bFnd) {
//STRIP001          rpObj=pObj;
//STRIP001          rpPV=pPV;
//STRIP001          if (pnMarkNum!=NULL) *pnMarkNum=nMarkNum;
//STRIP001      }
//STRIP001  }
//STRIP001  if ((bBoundCheckOn2ndPass || bCheckNearestOn3rdPass) && !bFnd) {
//STRIP001      SdrObject* pBestObj=NULL;
//STRIP001      SdrPageView* pBestPV=NULL;
//STRIP001      ULONG nBestMarkNum=0;
//STRIP001      ULONG nBestDist=0xFFFFFFFF;
//STRIP001      for (nMarkNum=nMarkAnz; nMarkNum>0 && !bFnd;) {
//STRIP001          nMarkNum--;
//STRIP001          SdrMark* pM=aMark.GetMark(nMarkNum);
//STRIP001          SdrPageView* pPV=pM->GetPageView();
//STRIP001          SdrObject* pObj=pM->GetObj();
//STRIP001          Point aPt1(aPt);
//STRIP001          aPt1-=pPV->GetOffset();
//STRIP001          Rectangle aRect(pObj->GetBoundRect());
//STRIP001          aRect.Left  ()-=nTol;
//STRIP001          aRect.Top   ()-=nTol;
//STRIP001          aRect.Right ()+=nTol;
//STRIP001          aRect.Bottom()+=nTol;
//STRIP001          if (aRect.IsInside(aPt1)) {
//STRIP001              bFnd=TRUE;
//STRIP001              rpObj=pObj;
//STRIP001              rpPV=pPV;
//STRIP001              if (pnMarkNum!=NULL) *pnMarkNum=nMarkNum;
//STRIP001          } else if (bCheckNearestOn3rdPass) {
//STRIP001              ULONG nDist=0;
//STRIP001              if (aPt1.X()<aRect.Left())   nDist+=aRect.Left()-aPt1.X();
//STRIP001              if (aPt1.X()>aRect.Right())  nDist+=aPt1.X()-aRect.Right();
//STRIP001              if (aPt1.Y()<aRect.Top())    nDist+=aRect.Top()-aPt1.Y();
//STRIP001              if (aPt1.Y()>aRect.Bottom()) nDist+=aPt1.Y()-aRect.Bottom();
//STRIP001              if (nDist<nBestDist) {
//STRIP001                  pBestObj=pObj;
//STRIP001                  pBestPV=pPV;
//STRIP001                  nBestMarkNum=nMarkNum;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      if (bCheckNearestOn3rdPass && !bFnd) {
//STRIP001          rpObj=pBestObj;
//STRIP001          rpPV=pBestPV;
//STRIP001          if (pnMarkNum!=NULL) *pnMarkNum=nBestMarkNum;
//STRIP001          bFnd=pBestObj!=NULL;
//STRIP001      }
//STRIP001  }
//STRIP001  return bFnd;
//STRIP001 }

//STRIP001 SdrHitKind SdrMarkView::PickSomething(const Point& rPnt, short nTol) const
//STRIP001 {
//STRIP001  nTol=ImpGetHitTolLogic(nTol,NULL);
//STRIP001  SdrHitKind eRet=SDRHIT_NONE;
//STRIP001  Point aPt(rPnt);
//STRIP001  SdrObject* pObj=NULL;
//STRIP001  SdrPageView* pPV=NULL;
//STRIP001  if (eRet==SDRHIT_NONE && PickObj(rPnt,USHORT(nTol),pObj,pPV,SDRSEARCH_PICKMARKABLE)) {
//STRIP001      Rectangle aRct1(aPt-Point(nTol,nTol),aPt+Point(nTol,nTol)); // HitRect fuer Toleranz
//STRIP001      Rectangle aBR(pObj->GetBoundRect());
//STRIP001      if      (aRct1.IsInside(aBR.TopLeft()))      eRet=SDRHIT_BOUNDTL;
//STRIP001      else if (aRct1.IsInside(aBR.TopCenter()))    eRet=SDRHIT_BOUNDTC;
//STRIP001      else if (aRct1.IsInside(aBR.TopRight()))     eRet=SDRHIT_BOUNDTR;
//STRIP001      else if (aRct1.IsInside(aBR.LeftCenter()))   eRet=SDRHIT_BOUNDCL;
//STRIP001      else if (aRct1.IsInside(aBR.RightCenter()))  eRet=SDRHIT_BOUNDCR;
//STRIP001      else if (aRct1.IsInside(aBR.BottomLeft()))   eRet=SDRHIT_BOUNDBL;
//STRIP001      else if (aRct1.IsInside(aBR.BottomCenter())) eRet=SDRHIT_BOUNDBC;
//STRIP001      else if (aRct1.IsInside(aBR.BottomRight()))  eRet=SDRHIT_BOUNDBR;
//STRIP001      else eRet=SDRHIT_OBJECT;
//STRIP001  }
//STRIP001  return eRet;
//STRIP001 }

/*N*/ void SdrMarkView::UnmarkAllObj(SdrPageView* pPV)
/*N*/ {
/*N*/   if (aMark.GetMarkCount()!=0) {
/*?*/       BrkAction();
/*?*/       BOOL bVis=bHdlShown;
/*?*/       if (bVis) HideMarkHdl(NULL);
/*?*/       if (pPV!=NULL) {
/*?*/           aMark.DeletePageView(*pPV);
/*?*/       } else {
/*?*/           aMark.Clear();
/*?*/       }
/*?*/       pMarkedObj=NULL;
/*?*/       pMarkedPV=NULL;
/*?*/       MarkListHasChanged();
/*?*/       AdjustMarkHdl(TRUE);
/*?*/       if (bVis) ShowMarkHdl(NULL); // ggf. fuer die RefPoints
/*?*/   }
/*N*/ }

//STRIP001 void SdrMarkView::MarkAllObj(SdrPageView* pPV)
//STRIP001 {
//STRIP001  BOOL bMarkChg=FALSE;
//STRIP001  BrkAction();
//STRIP001  HideMarkHdl(NULL);
//STRIP001  if (pPV!=NULL) {
//STRIP001      bMarkChg=aMark.InsertPageView(*pPV);
//STRIP001  } else {
//STRIP001      for (USHORT nv=0; nv<GetPageViewCount(); nv++) {
//STRIP001          SdrPageView* pPV=GetPageViewPvNum(nv);
//STRIP001          if (aMark.InsertPageView(*pPV)) bMarkChg=TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  if (bMarkChg) MarkListHasChanged();
//STRIP001  if (aMark.GetMarkCount()!=0) {
//STRIP001      AdjustMarkHdl(TRUE);
//STRIP001      ShowMarkHdl(NULL);
//STRIP001  } else {
//STRIP001  }
//STRIP001 }

/*N*/ void SdrMarkView::AdjustMarkHdl(BOOL bRestraintPaint)
/*N*/ {
/*N*/   BOOL bVis=bHdlShown;
/*N*/   if (bVis) HideMarkHdl(NULL);
/*N*/   CheckMarked();
/*N*/   SetMarkRects();
/*N*/   SetMarkHandles();
/*N*/   if(bRestraintPaint && bVis)
/*N*/   {
/*?*/       ShowMarkHdl(NULL);
/*N*/
/*N*/       // refresh IAOs
//STRIP012/*N*/ //--/       RefreshAllIAOManagers();
/*N*/   }
/*N*/ }

//STRIP001 Rectangle SdrMarkView::GetMarkedObjBoundRect() const
//STRIP001 {
//STRIP001  Rectangle aRect;
//STRIP001  for (ULONG nm=0; nm<aMark.GetMarkCount(); nm++) {
//STRIP001      SdrMark* pM=aMark.GetMark(nm);
//STRIP001      SdrObject* pO=pM->GetObj();
//STRIP001      Rectangle aR1(pO->GetBoundRect());
//STRIP001      aR1+=pM->GetPageView()->GetOffset();
//STRIP001      if (aRect.IsEmpty()) aRect=aR1;
//STRIP001      else aRect.Union(aR1);
//STRIP001  }
//STRIP001  return aRect;
//STRIP001 }

/*N*/ const Rectangle& SdrMarkView::GetMarkedObjRect() const
/*N*/ {
/*N*/   if (bMarkedObjRectDirty) {
/*N*/       ((SdrMarkView*)this)->bMarkedObjRectDirty=FALSE;
/*N*/       Rectangle aRect;
/*N*/       for (ULONG nm=0; nm<aMark.GetMarkCount(); nm++) {
/*?*/           SdrMark* pM=aMark.GetMark(nm);
/*?*/           SdrObject* pO=pM->GetObj();
/*?*/           Rectangle aR1(pO->GetSnapRect());
/*?*/           aR1+=pM->GetPageView()->GetOffset();
/*?*/           if (aRect.IsEmpty()) aRect=aR1;
/*?*/           else aRect.Union(aR1);
/*N*/       }
/*N*/       ((SdrMarkView*)this)->aMarkedObjRect=aRect;
/*N*/   }
/*N*/   return aMarkedObjRect;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrMarkView::ImpTakeDescriptionStr(const SdrMarkList& rML, USHORT nStrCacheID, XubString& rStr, USHORT nVal, USHORT nOpt) const
//STRIP001 {
//STRIP001  rStr = ImpGetResStr(nStrCacheID);
//STRIP001  xub_StrLen nPos = rStr.SearchAscii("%O");
//STRIP001
//STRIP001  if(nPos != STRING_NOTFOUND)
//STRIP001  {
//STRIP001      rStr.Erase(nPos, 2);
//STRIP001
//STRIP001      if(nOpt == IMPSDR_POINTSDESCRIPTION)
//STRIP001      {
//STRIP001          rStr.Insert(rML.GetPointMarkDescription(), nPos);
//STRIP001      }
//STRIP001      else if(nOpt == IMPSDR_GLUEPOINTSDESCRIPTION)
//STRIP001      {
//STRIP001          rStr.Insert(rML.GetGluePointMarkDescription(), nPos);
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          rStr.Insert(rML.GetMarkDescription(), nPos);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  nPos = rStr.SearchAscii("%N");
//STRIP001
//STRIP001  if(nPos != STRING_NOTFOUND)
//STRIP001  {
//STRIP001      rStr.Erase(nPos, 2);
//STRIP001      rStr.Insert(UniString::CreateFromInt32(nVal), nPos);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrMarkView::ImpTakeDescriptionStr(USHORT nStrCacheID, XubString& rStr, USHORT nVal, USHORT nOpt) const
//STRIP001 {
//STRIP001  ImpTakeDescriptionStr(aMark,nStrCacheID,rStr,nVal,nOpt);
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 BOOL SdrMarkView::EnterMarkedGroup()
//STRIP001 {
//STRIP001  BOOL bRet=FALSE;
//STRIP001  // Es wird nur die erste gefundene Gruppe (also nur in einer PageView) geentert
//STRIP001  // Weil PageView::EnterGroup ein AdjustMarkHdl ruft.
//STRIP001  // Das muss ich per Flag mal unterbinden  vvvvvvvv
//STRIP001  for (USHORT nv=0;   nv<GetPageViewCount() && !bRet; nv++) {
//STRIP001      BOOL bEnter=FALSE;
//STRIP001      SdrPageView* pPV=GetPageViewPvNum(nv);
//STRIP001      for (ULONG nm=aMark.GetMarkCount(); nm>0 && !bEnter;) {
//STRIP001          nm--;
//STRIP001          SdrMark* pM=aMark.GetMark(nm);
//STRIP001          if (pM->GetPageView()==pPV) {
//STRIP001              SdrObject* pObj=pM->GetObj();
//STRIP001              if (pObj->IsGroupObject()) {
//STRIP001                  if (pPV->EnterGroup(pObj)) {
//STRIP001                      bRet=TRUE;
//STRIP001                      bEnter=TRUE;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

// #i13033#
// Helper method for building the transitive hull of all selected
// objects
//STRIP001 void SdrMarkView::ImplCollectCompleteSelection(SdrObject* pObj)
//STRIP001 {
//STRIP001  sal_Bool bIsGroup(pObj->IsGroupObject());
//STRIP001
//STRIP001  if(bIsGroup && pObj->ISA(E3dObject) && !pObj->ISA(E3dScene))
//STRIP001      bIsGroup = sal_False;
//STRIP001
//STRIP001  if(bIsGroup)
//STRIP001  {
//STRIP001      SdrObjList* pList = pObj->GetSubList();
//STRIP001
//STRIP001      for(sal_uInt32 a(0L); a < pList->GetObjCount(); a++)
//STRIP001      {
//STRIP001          SdrObject* pObj2 = pList->GetObj(a);
//STRIP001          ImplCollectCompleteSelection(pObj2);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // #109870#
//STRIP001  // always also add the group object or scene to the hull of
//STRIP001  // the selection since connectors CAN directly connect to
//STRIP001  // groups or scenes.
//STRIP001  maAllMarkedObjects.Insert(pObj, LIST_APPEND);
//STRIP001 }

//STRIP001 void SdrMarkView::ForceEdgesOfMarkedNodes()
//STRIP001 {
//STRIP001  if (bEdgesOfMarkedNodesDirty) {
//STRIP001      aEdgesOfMarkedNodes.Clear();
//STRIP001      aMarkedEdgesOfMarkedNodes.Clear();
//STRIP001
//STRIP001      // #i13033#
//STRIP001      // Build transitive hull of complete selection in maAllMarkedObjects
//STRIP001      maAllMarkedObjects.Clear();
//STRIP001
//STRIP001      for(sal_uInt32 a(0L); a < aMark.GetMarkCount(); a++)
//STRIP001      {
//STRIP001          SdrObject* pObj = aMark.GetMark(a)->GetObj();
//STRIP001          ImplCollectCompleteSelection(pObj);
//STRIP001      }
//STRIP001
//STRIP001      bEdgesOfMarkedNodesDirty=FALSE;
//STRIP001      aMark.ForceSort();
//STRIP001      ULONG nMarkAnz=aMark.GetMarkCount();
//STRIP001      for (ULONG nm=0; nm<nMarkAnz; nm++) {
//STRIP001          SdrObject* pNode=aMark.GetMark(nm)->GetObj();
//STRIP001          const SfxBroadcaster* pBC=pNode->GetBroadcaster();
//STRIP001          if (pNode->IsNode()) {
//STRIP001              if (pBC!=NULL) {
//STRIP001                  USHORT nLstAnz=pBC->GetListenerCount();
//STRIP001                  for (USHORT nl=0; nl<nLstAnz; nl++) {
//STRIP001                      SfxListener* pLst=pBC->GetListener(nl);
//STRIP001                      SdrEdgeObj* pEdge=PTR_CAST(SdrEdgeObj,pLst);
//STRIP001                      if (pEdge!=NULL && pEdge->IsInserted() && pEdge->GetPage()==pNode->GetPage()) {
//STRIP001                          SdrMark aM(pEdge,aMark.GetMark(nm)->GetPageView());
//STRIP001                          if (pEdge->GetConnectedNode(TRUE)==pNode) aM.SetCon1(TRUE);
//STRIP001                          if (pEdge->GetConnectedNode(FALSE)==pNode) aM.SetCon2(TRUE);
//STRIP001                          if (!IsObjMarked(pEdge)) { // nachsehen, ob er selbst markiert ist
//STRIP001                              aEdgesOfMarkedNodes.InsertEntry(aM);
//STRIP001                          } else {
//STRIP001                              aMarkedEdgesOfMarkedNodes.InsertEntry(aM);
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      aEdgesOfMarkedNodes.ForceSort();
//STRIP001      aMarkedEdgesOfMarkedNodes.ForceSort();
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrMarkView::MarkListHasChanged()
/*N*/ {
/*N*/   aMark.SetNameDirty();
/*N*/   bEdgesOfMarkedNodesDirty=TRUE;
/*N*/   aEdgesOfMarkedNodes.Clear();
/*N*/   aMarkedEdgesOfMarkedNodes.Clear();
/*N*/
/*N*/   // #i13033#
/*N*/   // Forget transitive hull of complete selection
/*N*/   maAllMarkedObjects.Clear();
/*N*/
/*N*/   bMarkedObjRectDirty=TRUE;
/*N*/   bMarkedPointsRectsDirty=TRUE;
/*N*/ #ifndef SVX_LIGHT
/*?*/   if (pItemBrowser!=NULL) DBG_BF_ASSERT(0, "STRIP"); //STRIP001 pItemBrowser->SetDirty();
/*N*/ #endif
/*N*/   BOOL bOneEdgeMarked=FALSE;
/*N*/   if (aMark.GetMarkCount()==1) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        const SdrObject* pObj=aMark.GetMark(0)->GetObj();
//STRIP001 /*?*/        if (pObj->GetObjInventor()==SdrInventor) {
//STRIP001 /*?*/            UINT16 nIdent=pObj->GetObjIdentifier();
//STRIP001 /*?*/            bOneEdgeMarked=nIdent==OBJ_EDGE;
//STRIP001 /*?*/        }
/*N*/   }
/*N*/   ImpSetGlueVisible4(bOneEdgeMarked);
/*N*/ }
/*N*/
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrMarkView::WriteRecords(SvStream& rOut) const
/*N*/ {
/*N*/   SdrSnapView::WriteRecords(rOut);
/*N*/   {
/*N*/       SdrNamedSubRecord aSubRecord(rOut,STREAM_WRITE,SdrInventor,SDRIORECNAME_VIEWDRAGMODE);
/*N*/       rOut<<BOOL(eEditMode==SDREDITMODE_EDIT); // wg. Kompatibilitaet
/*N*/       rOut<<USHORT(eDragMode);
/*N*/       rOut<<aRef1;
/*N*/       rOut<<aRef2;
/*N*/       rOut<<BOOL(bForceFrameHandles);
/*N*/       rOut<<BOOL(bPlusHdlAlways);
/*N*/       rOut<<BOOL(eEditMode==SDREDITMODE_GLUEPOINTEDIT); // wg. Kompatibilitaet
/*N*/       rOut<<USHORT(eEditMode);
/*N*/       rOut<<BOOL(bMarkHdlWhenTextEdit);
/*N*/   } {
/*N*/       SdrNamedSubRecord aSubRecord(rOut,STREAM_WRITE,SdrInventor,SDRIORECNAME_VIEWCROOKCENTER);
/*N*/       rOut<<aLastCrookCenter;
/*N*/   }
/*N*/ }

/*N*/ BOOL SdrMarkView::ReadRecord(const SdrIOHeader& rViewHead,
/*N*/   const SdrNamedSubRecord& rSubHead,
/*N*/   SvStream& rIn)
/*N*/ {
/*N*/   BOOL bRet=FALSE;
/*N*/   if (rSubHead.GetInventor()==SdrInventor) {
/*N*/       bRet=TRUE;
/*N*/       switch (rSubHead.GetIdentifier()) {
/*N*/           case SDRIORECNAME_VIEWDRAGMODE: {
/*N*/               eEditMode=SDREDITMODE_EDIT;
/*N*/               BOOL bTmpBool;
/*N*/               USHORT nTmpUShort;
/*N*/               rIn>>bTmpBool; if (!bTmpBool) eEditMode=SDREDITMODE_CREATE; // wg. Kompatibilitaet
/*N*/               USHORT nDragMode;
/*N*/               rIn>>nDragMode;
/*N*/               eDragMode=SdrDragMode(nDragMode);
/*N*/               rIn>>aRef1;
/*N*/               rIn>>aRef2;
/*N*/               rIn>>bTmpBool; bForceFrameHandles=bTmpBool;
/*N*/               rIn>>bTmpBool; bPlusHdlAlways=bTmpBool;
/*N*/               if (rSubHead.GetBytesLeft()!=0) {
/*N*/                   rIn>>bTmpBool;
/*N*/                   if (bTmpBool) eEditMode=SDREDITMODE_GLUEPOINTEDIT; // wg. Kompatibilitaet
/*N*/               }
/*N*/               if (rSubHead.GetBytesLeft()!=0) {
/*N*/                   rIn>>nTmpUShort;
/*N*/                   eEditMode=(SdrViewEditMode)nTmpUShort;
/*N*/               }
/*N*/               bGlueVisible2=eEditMode==SDREDITMODE_GLUEPOINTEDIT;
/*N*/               if (rSubHead.GetBytesLeft()!=0) {
/*N*/                   rIn>>bTmpBool;
/*N*/                   bMarkHdlWhenTextEdit=bTmpBool;
/*N*/               }
/*N*/           } break;
/*N*/           case SDRIORECNAME_VIEWCROOKCENTER: {
/*N*/               rIn>>aLastCrookCenter;
/*N*/           } break;
/*N*/           default: bRet=FALSE;
/*N*/       }
/*N*/   }
/*N*/   if (!bRet) bRet=SdrSnapView::ReadRecord(rViewHead,rSubHead,rIn);
/*N*/   return bRet;
/*N*/ }

//STRIP001 void SdrMarkView::SetMoveOutside(BOOL bOn)
//STRIP001 {
//STRIP001  aHdl.SetMoveOutside(bOn);
//STRIP001 }

//STRIP001 BOOL SdrMarkView::IsMoveOutside() const
//STRIP001 {
//STRIP001  return aHdl.IsMoveOutside();
//STRIP001 }

/*N*/ void SdrMarkView::SetDesignMode(BOOL bOn)
/*N*/ {
/*N*/   if (bDesignMode != bOn)
/*N*/   {
/*N*/       bDesignMode = bOn;
/*N*/       // Setzen des Modes fuer alle Controls
/*N*/       USHORT nAnz = GetPageViewCount();
/*N*/       for (USHORT nv = 0; nv<nAnz; nv++)
/*N*/       {
/*N*/           SdrPageView* pPV = GetPageViewPvNum(nv);
/*N*/           const SdrPageViewWinList& rWinList = pPV->GetWinList();
/*N*/           for (ULONG i = 0; i < rWinList.GetCount(); i++)
/*N*/           {
/*N*/               const SdrPageViewWinRec& rWR = rWinList[ (USHORT) i];
/*N*/               const SdrUnoControlList& rControlList = rWR.GetControlList();
/*N*/
/*N*/               for(UINT32 j = 0; j < rControlList.GetCount(); j++)
/*N*/               {
/*?*/                   ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControl > xControl = rControlList[ (USHORT) j].GetControl();
/*?*/                   DBG_ASSERT( xControl.is(), "SdrMarkView::SetDesignMode: no control at this position!" );
/*?*/                   if ( xControl.is() )
/*?*/                       xControl->setDesignMode(bOn);
/*?*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

// MarkHandles Objektaenderung:
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// - Bei Notify mit HINT_OBJCHG (oder so) werden die Handles erstmal versteckt
//   (wenn nicht schon wegen Dragging versteckt).
// - XorHdl: Bei ModelHasChanged() werden sie dann wieder angezeigt.
// - PaintEvents kommen nun durch.
//   - Die XorHandles werden z.T. wieder uebermalt.
//   - Xor:  Nach dem Painten werden die Handles im (vom PaintHandler gerufenen)
//           InitRedraw per ToggleShownXor bei gesetzter ClipRegion nochmal gemalt
//           und damit ist alles in Butter.
//   - ToggleShownXor macht bei SolidHdl nix weil bHdlShown=FALSE
//   - Der AfterPaintTimer wird gestartet.
// - SolidHdl: Im AfterPaintHandler wird ShowMarkHdl gerufen.
//   Da die Handles zu diesem Zeitpunkt nicht angezeigt sind wird:
//   - SaveBackground durchgefuehrt.
//   - DrawMarkHdl gerufen und bHdlShown gesetzt.
//
// MarkHandles bei sonstigem Invalidate:
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// In diesem Fall bekomme ich kein Notify und beim Aufruf des
// PaintHandlers->InitRedraw() sind auch die SolidHandles sichtbar.

}
