/*************************************************************************
 *
 *  $RCSfile: svx_svdsnpv.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:46:29 $
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

#include "svdsnpv.hxx"
#include <math.h>

#include "svdetc.hxx"
#include "svdio.hxx"
#include "svdobj.hxx"
#include "svdpagv.hxx"
#include "svdpage.hxx"
#include "svditer.hxx"
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@@@  @@  @@  @@@@  @@@@@   @@ @@ @@ @@@@@ @@   @@
// @@  @@ @@@ @@ @@  @@ @@  @@  @@ @@ @@ @@    @@   @@
// @@     @@@@@@ @@  @@ @@  @@  @@ @@ @@ @@    @@ @ @@
//  @@@@  @@@@@@ @@@@@@ @@@@@   @@@@@ @@ @@@@  @@@@@@@
//     @@ @@ @@@ @@  @@ @@       @@@  @@ @@    @@@@@@@
// @@  @@ @@  @@ @@  @@ @@       @@@  @@ @@    @@@ @@@
//  @@@@  @@  @@ @@  @@ @@        @   @@ @@@@@ @@   @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrSnapView::ClearVars()
/*N*/ {
/*N*/   nMagnSizPix=4;
/*N*/   bSnapEnab=TRUE;
/*N*/   bGridSnap=TRUE;
/*N*/   bSnapTo1Pix=TRUE;
/*N*/   bBordSnap=TRUE;
/*N*/   bHlplSnap=TRUE;
/*N*/   bOFrmSnap=TRUE;
/*N*/   bOPntSnap=FALSE;
/*N*/   bOConSnap=TRUE;
/*N*/   bMoveMFrmSnap=TRUE;
/*N*/   bMoveOFrmSnap=TRUE;
/*N*/   bMoveOPntSnap=TRUE;
/*N*/   bMoveOConSnap=TRUE;
/*N*/   bMoveSnapOnlyTopLeft=FALSE;
/*N*/   bSetPageOrg=FALSE;
/*N*/   bOrtho=FALSE;
/*N*/   bBigOrtho=TRUE;
/*N*/   nSnapAngle=1500;
/*N*/   bAngleSnapEnab=FALSE;
/*N*/   bMoveOnlyDragging=FALSE;
/*N*/   bSlantButShear=FALSE;
/*N*/   bCrookNoContortion=FALSE;
/*N*/   eCrookMode=SDRCROOK_ROTATE;
/*N*/   bHlplFixed=FALSE;
/*N*/   pDragHelpLinePV=NULL;
/*N*/   nDragHelpLineNum=0;
/*N*/   bDragHelpLine=FALSE;
/*N*/   bEliminatePolyPoints=FALSE;
/*N*/   nEliminatePolyPointLimitAngle=0;
/*N*/ }

/*N*/ SdrSnapView::SdrSnapView(SdrModel* pModel1, OutputDevice* pOut):
/*N*/   SdrPaintView(pModel1,pOut)
/*N*/ {
/*N*/   ClearVars();
/*N*/ }

/*?*/ SdrSnapView::SdrSnapView(SdrModel* pModel1, ExtOutputDevice* pXOut):
/*?*/   SdrPaintView(pModel1,pXOut)
/*?*/ {
/*?*/   ClearVars();
/*?*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ BOOL SdrSnapView::IsAction() const
/*N*/ {
/*N*/   return IsSetPageOrg() || IsDragHelpLine() || SdrPaintView::IsAction();
/*N*/ }

//STRIP001 void SdrSnapView::MovAction(const Point& rPnt)
//STRIP001 {
//STRIP001  aLastMausPosNoSnap=rPnt;
//STRIP001  SdrPaintView::MovAction(rPnt);
//STRIP001  if (IsSetPageOrg()) {
//STRIP001      MovSetPageOrg(rPnt);
//STRIP001  }
//STRIP001  if (IsDragHelpLine()) {
//STRIP001      MovDragHelpLine(rPnt);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrSnapView::EndAction()
//STRIP001 {
//STRIP001  if (IsSetPageOrg()) {
//STRIP001      EndSetPageOrg();
//STRIP001  }
//STRIP001  if (IsDragHelpLine()) {
//STRIP001      EndDragHelpLine();
//STRIP001  }
//STRIP001  SdrPaintView::EndAction();
//STRIP001 }

//STRIP001 void SdrSnapView::BckAction()
//STRIP001 {
//STRIP001  BrkSetPageOrg();
//STRIP001  BrkDragHelpLine();
//STRIP001  SdrPaintView::BckAction();
//STRIP001 }

/*N*/ void SdrSnapView::BrkAction()
/*N*/ {
/*N*/   BrkSetPageOrg();
/*N*/   BrkDragHelpLine();
/*N*/   SdrPaintView::BrkAction();
/*N*/ }

//STRIP001 void SdrSnapView::TakeActionRect(Rectangle& rRect) const
//STRIP001 {
//STRIP001  if (IsSetPageOrg() || IsDragHelpLine()) {
//STRIP001      rRect=Rectangle(aDragStat.GetNow(),aDragStat.GetNow());
//STRIP001  } else {
//STRIP001      SdrPaintView::TakeActionRect(rRect);
//STRIP001  }
//STRIP001 }

/*N*/ void SdrSnapView::ToggleShownXor(OutputDevice* pOut, const Region* pRegion) const
/*N*/ {
/*N*/   SdrPaintView::ToggleShownXor(pOut,pRegion);
/*N*/   if (IsSetPageOrg()) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        DrawSetPageOrg(pOut);
/*N*/   }
/*N*/   if (IsDragHelpLine()) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        DrawDragHelpLine(pOut);
/*N*/   }
/*N*/ }

/*N*/ void SdrSnapView::SnapMove()
/*N*/ {
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 Point SdrSnapView::GetSnapPos(const Point& rPnt, const SdrPageView* pPV) const
//STRIP001 {
//STRIP001  Point aPt(rPnt);
//STRIP001  SnapPos(aPt,pPV);
//STRIP001  return aPt;
//STRIP001 }

#define NOT_SNAPPED 0x7FFFFFFF
//STRIP001 USHORT SdrSnapView::SnapPos(Point& rPnt, const SdrPageView* pPV) const
//STRIP001 {
//STRIP001  if (!bSnapEnab) return SDRSNAP_NOTSNAPPED;
//STRIP001  BOOL bPVOfs=FALSE;
//STRIP001  long x=rPnt.X();
//STRIP001  long y=rPnt.Y();
//STRIP001  long xOffs=0;
//STRIP001  long yOffs=0;
//STRIP001  if (pPV==NULL) {
//STRIP001      bPVOfs=TRUE;
//STRIP001      pPV=GetPageView(rPnt);
//STRIP001      if (pPV==NULL) return SDRSNAP_NOTSNAPPED;
//STRIP001  }
//STRIP001  bPVOfs=TRUE;
//STRIP001  // !!!!!!hier stattdessen mal die GridFrames verwenden!!!!!!!!
//STRIP001  // SdrPage::GetOffset() kann dann entsorgt werden.
//STRIP001
//STRIP001  // #i3694#
//STRIP001  // The Page::GetOffset() method is not needed anymore, it even leads to errors.
//STRIP001  // I will completely remove it, only Writer implements it (with a constant
//STRIP001  // of (DOCUMENTBORDER, DOCUMENTBORDER ).
//STRIP001  // Point aWriterPageOffset(pPV->GetPage()->GetOffset());
//STRIP001  xOffs=pPV->GetOffset().X(); // +aWriterPageOffset.X();
//STRIP001  yOffs=pPV->GetOffset().Y(); // +aWriterPageOffset.Y();
//STRIP001  x-=xOffs;
//STRIP001  y-=yOffs;
//STRIP001
//STRIP001  long dx=NOT_SNAPPED;
//STRIP001  long dy=NOT_SNAPPED;
//STRIP001  long dx1,dy1;
//STRIP001  long mx=aMagnSiz.Width();
//STRIP001  long my=aMagnSiz.Height();
//STRIP001  if (bHlplVisible && bHlplSnap && !bDragHelpLine) {
//STRIP001      const SdrHelpLineList& rHLL=pPV->GetHelpLines();
//STRIP001      USHORT nAnz=rHLL.GetCount();
//STRIP001      for (USHORT i=nAnz; i>0;) {
//STRIP001          i--;
//STRIP001          const SdrHelpLine& rHL=rHLL[i];
//STRIP001          const Point& rPos=rHL.GetPos();
//STRIP001          switch (rHL.GetKind()) {
//STRIP001              case SDRHELPLINE_VERTICAL: {
//STRIP001                  long a=x-rPos.X();
//STRIP001                  if (Abs(a)<=mx) { dx1=-a; if (Abs(dx1)<Abs(dx)) dx=dx1; }
//STRIP001              } break;
//STRIP001              case SDRHELPLINE_HORIZONTAL: {
//STRIP001                  long b=y-rPos.Y();
//STRIP001                  if (Abs(b)<=my) { dy1=-b; if (Abs(dy1)<Abs(dy)) dy=dy1; }
//STRIP001              } break;
//STRIP001              case SDRHELPLINE_POINT: {
//STRIP001                  long a=x-rPos.X();
//STRIP001                  long b=y-rPos.Y();
//STRIP001                  if (Abs(a)<=mx && Abs(b)<=my) {
//STRIP001                      dx1=-a; dy1=-b;
//STRIP001                      if (Abs(dx1)<Abs(dx) && Abs(dy1)<Abs(dy)) { dx=dx1; dy=dy1; }
//STRIP001                  }
//STRIP001              } break;
//STRIP001          } // switch
//STRIP001      }
//STRIP001  }
//STRIP001  if (bBordVisible && bBordSnap) {
//STRIP001      SdrPage* pPage=pPV->GetPage();
//STRIP001      long xs=pPage->GetWdt();
//STRIP001      long ys=pPage->GetHgt();
//STRIP001      long lft=pPage->GetLftBorder();
//STRIP001      long rgt=pPage->GetRgtBorder();
//STRIP001      long upp=pPage->GetUppBorder();
//STRIP001      long lwr=pPage->GetLwrBorder();
//STRIP001      long a;
//STRIP001      a=x- lft    ; if (Abs(a)<=mx) { dx1=-a; if (Abs(dx1)<Abs(dx)) dx=dx1; } // linker Rand
//STRIP001      a=x-(xs-rgt); if (Abs(a)<=mx) { dx1=-a; if (Abs(dx1)<Abs(dx)) dx=dx1; } // rechter Rand
//STRIP001      a=x         ; if (Abs(a)<=mx) { dx1=-a; if (Abs(dx1)<Abs(dx)) dx=dx1; } // linke Papierkante
//STRIP001      a=x- xs     ; if (Abs(a)<=mx) { dx1=-a; if (Abs(dx1)<Abs(dx)) dx=dx1; } // rechte Papierkante
//STRIP001      a=y- upp    ; if (Abs(a)<=my) { dy1=-a; if (Abs(dy1)<Abs(dy)) dy=dy1; } // linker Rand
//STRIP001      a=y-(ys-lwr); if (Abs(a)<=my) { dy1=-a; if (Abs(dy1)<Abs(dy)) dy=dy1; } // rechter Rand
//STRIP001      a=y         ; if (Abs(a)<=my) { dy1=-a; if (Abs(dy1)<Abs(dy)) dy=dy1; } // linke Papierkante
//STRIP001      a=y- ys     ; if (Abs(a)<=my) { dy1=-a; if (Abs(dy1)<Abs(dy)) dy=dy1; } // rechte Papierkante
//STRIP001  }
//STRIP001  if (bOFrmSnap || bOPntSnap /*|| (bConnVisible && bOConSnap)*/) {
//STRIP001      ULONG nMaxPointSnapCount=200;
//STRIP001      ULONG nMaxFrameSnapCount=200;
//STRIP001
//STRIP001      // #97981# go back to IM_DEEPNOGROUPS runthrough for snap to object comparisons
//STRIP001      // SdrObjListIter aIter(*pPV->GetPage(),IM_FLAT/*IM_DEEPNOGROUPS*/,TRUE);
//STRIP001      SdrObjListIter aIter(*pPV->GetPage(),/*IM_FLAT*/IM_DEEPNOGROUPS,TRUE);
//STRIP001
//STRIP001      while (aIter.IsMore() && (nMaxPointSnapCount>0 || nMaxFrameSnapCount>0)) {
//STRIP001          SdrObject* pO=aIter.Next();
//STRIP001          Rectangle aRect(pO->GetBoundRect());
//STRIP001          aRect.Left  ()-=mx;
//STRIP001          aRect.Right ()+=mx;
//STRIP001          aRect.Top   ()-=my;
//STRIP001          aRect.Bottom()+=my;
//STRIP001          if (aRect.IsInside(rPnt)) {
//STRIP001              if (bOPntSnap && nMaxPointSnapCount>0) {
//STRIP001                  USHORT nAnz=pO->GetSnapPointCount();
//STRIP001                  for (USHORT i=0; i<nAnz && nMaxPointSnapCount>0; i++) {
//STRIP001                      Point aP(pO->GetSnapPoint(i));
//STRIP001                      dx1=x-aP.X();
//STRIP001                      dy1=y-aP.Y();
//STRIP001                      if (Abs(dx1)<=mx && Abs(dy1)<=my && Abs(dx1)<Abs(dx) && Abs(dy1)<Abs(dy)) {
//STRIP001                          dx=-dx1;
//STRIP001                          dy=-dy1;
//STRIP001                      }
//STRIP001                      nMaxPointSnapCount--;
//STRIP001                  }
//STRIP001              }
//STRIP001              if (bOFrmSnap && nMaxFrameSnapCount>0) {
//STRIP001                  Rectangle aLog(pO->GetSnapRect());
//STRIP001                  Rectangle aR1(aLog);
//STRIP001                  aR1.Left  ()-=mx;
//STRIP001                  aR1.Right ()+=mx;
//STRIP001                  aR1.Top   ()-=my;
//STRIP001                  aR1.Bottom()+=my;
//STRIP001                  if (aR1.IsInside(rPnt)) {
//STRIP001                      if (Abs(x-aLog.Left  ())<=mx) { dx1=-(x-aLog.Left  ()); if (Abs(dx1)<Abs(dx)) dx=dx1; }
//STRIP001                      if (Abs(x-aLog.Right ())<=mx) { dx1=-(x-aLog.Right ()); if (Abs(dx1)<Abs(dx)) dx=dx1; }
//STRIP001                      if (Abs(y-aLog.Top   ())<=my) { dy1=-(y-aLog.Top   ()); if (Abs(dy1)<Abs(dy)) dy=dy1; }
//STRIP001                      if (Abs(y-aLog.Bottom())<=my) { dy1=-(y-aLog.Bottom()); if (Abs(dy1)<Abs(dy)) dy=dy1; }
//STRIP001                  }
//STRIP001                  nMaxFrameSnapCount--;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if(bGridSnap)
//STRIP001  {
//STRIP001      double fSnapWidth = aSnapWdtX;
//STRIP001      if(dx == NOT_SNAPPED && fSnapWidth != 0.0)
//STRIP001      {
//STRIP001          double fx = (double)x;
//STRIP001
//STRIP001          // round statt trunc
//STRIP001          if(fx - (double)pPV->GetPageOrigin().X() >= 0.0)
//STRIP001              fx += fSnapWidth / 2.0;
//STRIP001          else
//STRIP001              fx -= fSnapWidth / 2.0;
//STRIP001
//STRIP001          x = (long)((fx - (double)pPV->GetPageOrigin().X()) / fSnapWidth);
//STRIP001          x = (long)((double)x * fSnapWidth + (double)pPV->GetPageOrigin().X());
//STRIP001          dx = 0;
//STRIP001      }
//STRIP001      fSnapWidth = aSnapWdtY;
//STRIP001      if(dy == NOT_SNAPPED && fSnapWidth)
//STRIP001      {
//STRIP001          double fy = (double)y;
//STRIP001
//STRIP001          // round statt trunc
//STRIP001          if(fy - (double)pPV->GetPageOrigin().Y() >= 0.0)
//STRIP001              fy += fSnapWidth / 2.0;
//STRIP001          else
//STRIP001              fy -= fSnapWidth / 2.0;
//STRIP001
//STRIP001          y = (long)((fy - (double)pPV->GetPageOrigin().Y()) / fSnapWidth);
//STRIP001          y = (long)((double)y * fSnapWidth + (double)pPV->GetPageOrigin().Y());
//STRIP001          dy = 0;
//STRIP001      }
//STRIP001  }
//STRIP001  BOOL bRet=SDRSNAP_NOTSNAPPED;
//STRIP001  if (dx==NOT_SNAPPED) dx=0; else bRet|=SDRSNAP_XSNAPPED;
//STRIP001  if (dy==NOT_SNAPPED) dy=0; else bRet|=SDRSNAP_YSNAPPED;
//STRIP001  if (bPVOfs) {
//STRIP001      x+=xOffs;
//STRIP001      y+=yOffs;
//STRIP001  }
//STRIP001  rPnt.X()=x+dx;
//STRIP001  rPnt.Y()=y+dy;
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 void SdrSnapView::CheckSnap(const Point& rPt, const SdrPageView* pPV,
//STRIP001  long& nBestXSnap, long& nBestYSnap,
//STRIP001  BOOL& bXSnapped, BOOL& bYSnapped) const
//STRIP001 {
//STRIP001  Point aPt(rPt);
//STRIP001  USHORT nRet=SnapPos(aPt,pPV);
//STRIP001  aPt-=rPt;
//STRIP001  if ((nRet & SDRSNAP_XSNAPPED) !=0) {
//STRIP001      if (bXSnapped) {
//STRIP001          if (Abs(aPt.X())<Abs(nBestXSnap)) {
//STRIP001              nBestXSnap=aPt.X();
//STRIP001          }
//STRIP001      } else {
//STRIP001          nBestXSnap=aPt.X();
//STRIP001          bXSnapped=TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  if ((nRet & SDRSNAP_YSNAPPED) !=0) {
//STRIP001      if (bYSnapped) {
//STRIP001          if (Abs(aPt.Y())<Abs(nBestYSnap)) {
//STRIP001              nBestYSnap=aPt.Y();
//STRIP001          }
//STRIP001      } else {
//STRIP001          nBestYSnap=aPt.Y();
//STRIP001          bYSnapped=TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 USHORT SdrSnapView::SnapRect(const Rectangle& rRect, const SdrPageView* pPV, long& rDX, long& rDY) const
//STRIP001 {
//STRIP001  long nBestXSnap=0;
//STRIP001  long nBestYSnap=0;
//STRIP001  BOOL bXSnapped=FALSE;
//STRIP001  BOOL bYSnapped=FALSE;
//STRIP001  CheckSnap(rRect.TopLeft()    ,pPV,nBestXSnap,nBestYSnap,bXSnapped,bYSnapped);
//STRIP001  if (!bMoveSnapOnlyTopLeft) {
//STRIP001      CheckSnap(rRect.TopRight()   ,pPV,nBestXSnap,nBestYSnap,bXSnapped,bYSnapped);
//STRIP001      CheckSnap(rRect.BottomLeft() ,pPV,nBestXSnap,nBestYSnap,bXSnapped,bYSnapped);
//STRIP001      CheckSnap(rRect.BottomRight(),pPV,nBestXSnap,nBestYSnap,bXSnapped,bYSnapped);
//STRIP001  }
//STRIP001  rDX=nBestXSnap;
//STRIP001  rDY=nBestYSnap;
//STRIP001  USHORT nRet=0;
//STRIP001  if (bXSnapped) nRet+=SDRSNAP_XSNAPPED;
//STRIP001  if (bYSnapped) nRet+=SDRSNAP_YSNAPPED;
//STRIP001  return nRet;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 BOOL SdrSnapView::BegSetPageOrg(const Point& rPnt, OutputDevice* pOut, short nMinMov)
//STRIP001 {
//STRIP001  BrkAction();
//STRIP001  aAni.Reset();
//STRIP001  aAni.SetCrossHair(TRUE);
//STRIP001  aDragStat.Reset(GetSnapPos(rPnt,NULL));
//STRIP001  aDragStat.SetMinMove(ImpGetMinMovLogic(nMinMov,pOut));
//STRIP001  if (nMinMov==0) aDragStat.SetMinMoved();
//STRIP001  pDragWin=pOut;
//STRIP001  bSetPageOrg=TRUE;
//STRIP001  if (aDragStat.IsMinMoved()) ShowSetPageOrg(pOut);
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 void SdrSnapView::MovSetPageOrg(const Point& rPnt)
//STRIP001 {
//STRIP001  if (bSetPageOrg) {
//STRIP001      if (aDragStat.IsMinMoved()) HideSetPageOrg(pDragWin);
//STRIP001      aDragStat.NextMove(GetSnapPos(rPnt,NULL));
//STRIP001      if (aDragStat.CheckMinMoved(rPnt)) ShowSetPageOrg(pDragWin);
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL SdrSnapView::EndSetPageOrg()
//STRIP001 {
//STRIP001  BOOL bRet=FALSE;
//STRIP001  if (bSetPageOrg) {
//STRIP001      HideSetPageOrg(pDragWin);
//STRIP001      bSetPageOrg=FALSE;
//STRIP001      Point aPnt=aDragStat.GetNow();
//STRIP001      SdrPageView* pPV=HitPage(aPnt);
//STRIP001
//STRIP001         // According to bug #99937# the page origin shall allways be set,
//STRIP001         // even when it lies outside the actual page area.  Therefore, the
//STRIP001         // first page is used as a fallback when no other is found.
//STRIP001      if (pPV == NULL)
//STRIP001             pPV = GetPageViewPvNum (0);
//STRIP001
//STRIP001      if (pPV!=NULL) {
//STRIP001          aPnt-=pPV->GetOffset();
//STRIP001          pPV->SetPageOrigin(aPnt);
//STRIP001          bRet=TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*N*/ void SdrSnapView::BrkSetPageOrg()
/*N*/ {
/*N*/   if (bSetPageOrg) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        HideSetPageOrg(pDragWin);
//STRIP001 /*?*/        bSetPageOrg=FALSE;
/*N*/   }
/*N*/ }

//STRIP001 void SdrSnapView::ShowSetPageOrg(OutputDevice* pOut)
//STRIP001 {
//STRIP001  if (bSetPageOrg && !aDragStat.IsShown()) {
//STRIP001      DrawSetPageOrg(pOut);
//STRIP001      aDragStat.SetShown(TRUE);
//STRIP001      aAni.Start();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrSnapView::HideSetPageOrg(OutputDevice* pOut)
//STRIP001 {
//STRIP001  if (bSetPageOrg && aDragStat.IsShown()) {
//STRIP001      aAni.Stop();
//STRIP001      DrawSetPageOrg(pOut);
//STRIP001      aDragStat.SetShown(FALSE);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrSnapView::DrawSetPageOrg(OutputDevice* pOut) const
//STRIP001 {
//STRIP001  if (bSetPageOrg) {
//STRIP001      aAni.SetP1(aDragStat.GetNow());
//STRIP001      aAni.Invert(pOut);
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ BOOL SdrSnapView::PickHelpLine(const Point& rPnt, short nTol, const OutputDevice& rOut, USHORT& rnHelpLineNum, SdrPageView*& rpPV) const
/*N*/ {
/*N*/   rpPV=NULL;
/*N*/   nTol=ImpGetHitTolLogic(nTol,&rOut);
/*N*/   for (USHORT nv=GetPageViewCount(); nv>0;) {
/*N*/       nv--;
/*N*/       SdrPageView* pPV=GetPageViewPvNum(nv);
/*N*/       Point aPnt(rPnt);
/*N*/       aPnt-=pPV->GetOffset();
/*N*/       USHORT nIndex=pPV->GetHelpLines().HitTest(aPnt,USHORT(nTol),rOut);
/*N*/       if (nIndex!=SDRHELPLINE_NOTFOUND) {
/*?*/           rpPV=pPV;
/*?*/           rnHelpLineNum=nIndex;
/*?*/           return TRUE;
/*N*/       }
/*N*/   }
/*N*/   return FALSE;
/*N*/ }

//STRIP001 BOOL SdrSnapView::BegDragHelpLine(USHORT nHelpLineNum, SdrPageView* pPV, OutputDevice* pOut, short nMinMov)
//STRIP001 {
//STRIP001  BOOL bRet=FALSE;
//STRIP001  if (bHlplFixed) return FALSE;
//STRIP001  BrkAction();
//STRIP001  if (pPV!=NULL && nHelpLineNum<pPV->GetHelpLines().GetCount()) {
//STRIP001      pDragHelpLinePV=pPV;
//STRIP001      nDragHelpLineNum=nHelpLineNum;
//STRIP001      aDragHelpLine=pPV->GetHelpLines()[nHelpLineNum];
//STRIP001      Point aPnt(aDragHelpLine.GetPos());
//STRIP001      aPnt+=pPV->GetOffset();
//STRIP001      aDragHelpLine.SetPos(aPnt);
//STRIP001      pDragWin=pOut;
//STRIP001      aDragStat.Reset(GetSnapPos(aPnt,pPV));
//STRIP001      aDragStat.SetMinMove(ImpGetMinMovLogic(nMinMov,pOut));
//STRIP001      if (nMinMov==0) aDragStat.SetMinMoved();
//STRIP001      bDragHelpLine=TRUE;
//STRIP001      if (aDragStat.IsMinMoved()) ShowDragHelpLine(pOut);
//STRIP001      bRet=TRUE;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SdrSnapView::BegDragHelpLine(const Point& rPnt, SdrHelpLineKind eNewKind, OutputDevice* pOut, short nMinMov)
//STRIP001 {
//STRIP001  BOOL bRet=FALSE;
//STRIP001  BrkAction();
//STRIP001  if (GetPageViewCount()>0) {
//STRIP001      pDragHelpLinePV=NULL;
//STRIP001      nDragHelpLineNum=0xFFFF;
//STRIP001      aDragStat.Reset(GetSnapPos(rPnt,NULL));
//STRIP001      aDragStat.SetMinMove(ImpGetMinMovLogic(nMinMov,pOut));
//STRIP001      if (nMinMov==0) aDragStat.SetMinMoved();
//STRIP001      aDragHelpLine.SetPos(aDragStat.GetNow());
//STRIP001      aDragHelpLine.SetKind(eNewKind);
//STRIP001      pDragWin=pOut;
//STRIP001      bDragHelpLine=TRUE;
//STRIP001      if (aDragStat.IsMinMoved()) ShowDragHelpLine(pOut);
//STRIP001      bRet=TRUE;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 void SdrSnapView::SetDraggedHelpLineKind(SdrHelpLineKind eNewKind)
//STRIP001 {
//STRIP001  if (bDragHelpLine) {
//STRIP001      BOOL bVis=aDragStat.IsShown();
//STRIP001      HideDragHelpLine(pDragWin);
//STRIP001      aDragHelpLine.SetKind(eNewKind);
//STRIP001      aDragStat.SetMinMoved();
//STRIP001      ShowDragHelpLine(pDragWin);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrSnapView::MovDragHelpLine(const Point& rPnt)
//STRIP001 {
//STRIP001  if (bDragHelpLine && aDragStat.CheckMinMoved(rPnt)) {
//STRIP001      Point aPnt(GetSnapPos(rPnt,NULL));
//STRIP001      if (aPnt!=aDragStat.GetNow()) {
//STRIP001          if (aDragStat.IsMinMoved()) HideDragHelpLine(pDragWin);
//STRIP001          aDragStat.NextMove(aPnt);
//STRIP001          aDragHelpLine.SetPos(aDragStat.GetNow());
//STRIP001          if (aDragStat.CheckMinMoved(rPnt)) ShowDragHelpLine(pDragWin);
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL SdrSnapView::EndDragHelpLine()
//STRIP001 {
//STRIP001  BOOL bRet=FALSE;
//STRIP001  if (bDragHelpLine) {
//STRIP001      if (aDragStat.IsMinMoved()) {
//STRIP001          HideDragHelpLine(pDragWin);
//STRIP001          if (pDragHelpLinePV!=NULL) {
//STRIP001              Point aPnt(aDragStat.GetNow());
//STRIP001              aPnt-=pDragHelpLinePV->GetOffset(); // an die PageView anpassen
//STRIP001              aDragHelpLine.SetPos(aPnt);
//STRIP001              pDragHelpLinePV->SetHelpLine(nDragHelpLineNum,aDragHelpLine);
//STRIP001              bRet=TRUE;
//STRIP001          } else { // ansonsten neue Hilfslinie
//STRIP001              Point aPnt(aDragStat.GetNow());
//STRIP001              SdrPageView* pPV=GetPageView(aPnt);
//STRIP001              if (pPV!=NULL) {
//STRIP001                  aPnt-=pPV->GetOffset(); // an die PageView anpassen
//STRIP001                  aDragHelpLine.SetPos(aPnt);
//STRIP001                  pDragHelpLinePV=pPV;
//STRIP001                  nDragHelpLineNum=pPV->GetHelpLines().GetCount();
//STRIP001                  pPV->InsertHelpLine(aDragHelpLine);
//STRIP001                  bRet=TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001          bDragHelpLine=FALSE;
//STRIP001      } else {
//STRIP001          BrkDragHelpLine();
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*N*/ void SdrSnapView::BrkDragHelpLine()
/*N*/ {
/*N*/   if (bDragHelpLine) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        HideDragHelpLine(pDragWin);
//STRIP001 /*?*/        bDragHelpLine=FALSE;
//STRIP001 /*?*/        pDragHelpLinePV=NULL;
/*N*/   }
/*N*/ }

//STRIP001 void SdrSnapView::ShowDragHelpLine(OutputDevice* pOut)
//STRIP001 {
//STRIP001  if (bDragHelpLine && !aDragStat.IsShown()) {
//STRIP001      DrawDragHelpLine(pOut);
//STRIP001      aDragStat.SetShown(TRUE);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrSnapView::HideDragHelpLine(OutputDevice* pOut)
//STRIP001 {
//STRIP001  if (bDragHelpLine && aDragStat.IsShown()) {
//STRIP001      DrawDragHelpLine(pOut);
//STRIP001      aDragStat.SetShown(FALSE);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrSnapView::DrawDragHelpLine(OutputDevice* pOut) const
//STRIP001 {
//STRIP001  if (bDragHelpLine)
//STRIP001  {
//STRIP001      USHORT i=0;
//STRIP001      do
//STRIP001      {
//STRIP001          OutputDevice* pO=pOut;
//STRIP001          if (pO==NULL)
//STRIP001          {
//STRIP001              pO=GetWin(i);
//STRIP001              i++;
//STRIP001          }
//STRIP001          if (pO!=NULL)
//STRIP001          {
//STRIP001              bool bDontDraw = false;
//STRIP001
//STRIP001              // see if there is already a help line on same position
//STRIP001              Point aPnt(aDragStat.GetNow());
//STRIP001              SdrPageView* pPV=GetPageView(aPnt);
//STRIP001              if (pPV!=NULL)
//STRIP001              {
//STRIP001                  const SdrHelpLineList& rList = pPV->GetHelpLines();
//STRIP001                  sal_uInt16 nAnz = rList.GetCount(),i;
//STRIP001
//STRIP001                  for(i=0; i<nAnz; i++)
//STRIP001                  {
//STRIP001                      const SdrHelpLine rHelpLine = rList[i];
//STRIP001
//STRIP001                      // check if we already drawn a help line like this one
//STRIP001                      if( aDragHelpLine.IsVisibleEqual( rHelpLine, *pO) )
//STRIP001                          bDontDraw = true;
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              if( !bDontDraw )
//STRIP001              {
//STRIP001                  RasterOp eRop0=pO->GetRasterOp();
//STRIP001                  pO->SetRasterOp(ROP_INVERT);
//STRIP001                  Color aColor0( pO->GetLineColor() );
//STRIP001                  Color aBlackColor( COL_BLACK );
//STRIP001                  pO->SetLineColor( aBlackColor );
//STRIP001                  aDragHelpLine.Draw(*pO,Point());
//STRIP001                  pO->SetRasterOp(eRop0);
//STRIP001                  pO->SetLineColor( aColor0 );
//STRIP001              }
//STRIP001          }
//STRIP001      } while (pOut==NULL && i<GetWinCount());
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrSnapView::WriteRecords(SvStream& rOut) const
/*N*/ {
/*N*/   SdrPaintView::WriteRecords(rOut);
/*N*/   {
/*N*/       SdrNamedSubRecord aSubRecord(rOut,STREAM_WRITE,SdrInventor,SDRIORECNAME_VIEWSNAP);
/*N*/       rOut<<aMagnSiz;
/*N*/       rOut<<aSnapSiz;
/*N*/
/*N*/       rOut << (BOOL)bSnapEnab;
/*N*/       rOut << (BOOL)bGridSnap;
/*N*/       rOut << (BOOL)bBordSnap;
/*N*/       rOut << (BOOL)bHlplSnap;
/*N*/       rOut << (BOOL)bOFrmSnap;
/*N*/       rOut << (BOOL)bOPntSnap;
/*N*/       rOut << (BOOL)bOConSnap;
/*N*/       rOut << (BOOL)bMoveMFrmSnap;
/*N*/       rOut << (BOOL)bMoveOFrmSnap;
/*N*/       rOut << (BOOL)bMoveOPntSnap;
/*N*/       rOut << (BOOL)bMoveOConSnap;
/*N*/       rOut << (BOOL)bHlplFixed;
/*N*/
/*N*/       rOut<<nMagnSizPix;
/*N*/
/*N*/       rOut << (BOOL)bSnapTo1Pix;
/*N*/       rOut << (BOOL)bMoveSnapOnlyTopLeft;
/*N*/
/*N*/       rOut<<aSnapWdtX;
/*N*/       rOut<<aSnapWdtY;
/*N*/   } {
/*N*/       SdrNamedSubRecord aSubRecord(rOut,STREAM_WRITE,SdrInventor,SDRIORECNAME_VIEWORTHO);
/*N*/
/*N*/       rOut << (BOOL)bOrtho;
/*N*/       rOut << (BOOL)bBigOrtho;
/*N*/
/*N*/       rOut<<nSnapAngle;
/*N*/
/*N*/       rOut << (BOOL)bAngleSnapEnab;
/*N*/       rOut << (BOOL)bMoveOnlyDragging;
/*N*/       rOut << (BOOL)bSlantButShear;
/*N*/       rOut << (BOOL)bCrookNoContortion;
/*N*/
/*N*/       rOut<<USHORT(eCrookMode);
/*N*/   }
/*N*/ }

/*N*/ BOOL SdrSnapView::ReadRecord(const SdrIOHeader& rViewHead,
/*N*/   const SdrNamedSubRecord& rSubHead,
/*N*/   SvStream& rIn)
/*N*/ {
/*N*/   BOOL bRet=FALSE;
/*N*/   if (rSubHead.GetInventor()==SdrInventor)
/*N*/   {
/*N*/       bRet=TRUE;
/*N*/       BOOL bZwi;
/*N*/
/*N*/       switch (rSubHead.GetIdentifier())
/*N*/       {
/*N*/           case SDRIORECNAME_VIEWSNAP:
/*N*/           {
/*N*/               rIn>>aMagnSiz;
/*N*/               rIn>>aSnapSiz;
/*N*/
/*N*/               rIn >> bZwi; bSnapEnab = bZwi;
/*N*/               rIn >> bZwi; bGridSnap = bZwi;
/*N*/               rIn >> bZwi; bBordSnap = bZwi;
/*N*/               rIn >> bZwi; bHlplSnap = bZwi;
/*N*/               rIn >> bZwi; bOFrmSnap = bZwi;
/*N*/               rIn >> bZwi; bOPntSnap = bZwi;
/*N*/               rIn >> bZwi; bOConSnap = bZwi;
/*N*/               rIn >> bZwi; bMoveMFrmSnap = bZwi;
/*N*/               rIn >> bZwi; bMoveOFrmSnap = bZwi;
/*N*/               rIn >> bZwi; bMoveOPntSnap = bZwi;
/*N*/               rIn >> bZwi; bMoveOConSnap = bZwi;
/*N*/
/*N*/               if (rSubHead.GetBytesLeft()>0)
/*N*/               {
/*N*/                   rIn >> bZwi; bHlplFixed = bZwi; // kam erst spaeter dazu
/*N*/               }
/*N*/               if (rSubHead.GetBytesLeft()>0)
/*N*/               {
/*N*/                   // kam erst spaeter dazu
/*N*/                   rIn>>nMagnSizPix;
/*N*/                   rIn >> bZwi; bSnapTo1Pix = bZwi;
/*N*/               }
/*N*/               if (rSubHead.GetBytesLeft()>0)
/*N*/               {
/*N*/                   // kam erst spaeter dazu
/*N*/                   rIn >> bZwi; bMoveSnapOnlyTopLeft = bZwi;
/*N*/               }
/*N*/               if (rSubHead.GetBytesLeft()>0)
/*N*/               {
/*N*/                   // kam erst spaeter dazu
/*N*/                   rIn>>aSnapWdtX;
/*N*/                   rIn>>aSnapWdtY;
/*N*/               }
/*N*/           } break;
/*N*/           case SDRIORECNAME_VIEWORTHO:
/*N*/           {
/*N*/               rIn >> bZwi; bOrtho = bZwi;
/*N*/               rIn >> bZwi; bBigOrtho = bZwi;
/*N*/
/*N*/               rIn>>nSnapAngle;
/*N*/
/*N*/               if (rSubHead.GetBytesLeft()>0)
/*N*/               {
/*N*/                   // kam erst spaeter dazu
/*N*/                   rIn >> bZwi; bAngleSnapEnab = bZwi;
/*N*/                   rIn >> bZwi; bMoveOnlyDragging = bZwi;
/*N*/                   rIn >> bZwi; bSlantButShear = bZwi;
/*N*/                   rIn >> bZwi; bCrookNoContortion = bZwi;
/*N*/               }
/*N*/               if (rSubHead.GetBytesLeft()>0)
/*N*/               {
/*N*/                   // kam erst spaeter dazu
/*N*/                   USHORT nCrookMode;
/*N*/                   rIn>>nCrookMode;
/*N*/                   eCrookMode=SdrCrookMode(nCrookMode);
/*N*/               }
/*N*/           } break;
/*N*/           default: bRet=FALSE;
/*N*/       }
/*N*/   }
/*N*/   if (!bRet) bRet=SdrPaintView::ReadRecord(rViewHead,rSubHead,rIn);
/*N*/   return bRet;
/*N*/ }

}
