/*************************************************************************
 *
 *  $RCSfile: svx_svddrgv.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:22 $
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

#include "svddrgv.hxx"
#include "xattr.hxx"
#include "xpoly.hxx"
#include "svdxout.hxx"
#include "svdetc.hxx"
#include "svdtrans.hxx"
#include "svdundo.hxx"
#include "svdocapt.hxx"
#include "svdio.hxx"
#include "svdpagv.hxx"
#include "svdopath.hxx" // wg. Sonderbehandlung in SetDragPolys()
#include "svdoedge.hxx" // wg. Sonderbehandlung in IsInsGluePossible()
#include "svdstr.hrc"   // Namen aus der Resource
#include "svdglob.hxx"  // StringCache
#include "svddrgm1.hxx"
#include "obj3d.hxx"

#define XOR_DRAG_PEN   PEN_DOT

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@@@@  @@@@@   @@@@   @@@@   @@ @@ @@ @@@@@ @@   @@
//  @@  @@ @@  @@ @@  @@ @@  @@  @@ @@ @@ @@    @@   @@
//  @@  @@ @@  @@ @@  @@ @@      @@ @@ @@ @@    @@ @ @@
//  @@  @@ @@@@@  @@@@@@ @@ @@@  @@@@@ @@ @@@@  @@@@@@@
//  @@  @@ @@  @@ @@  @@ @@  @@   @@@  @@ @@    @@@@@@@
//  @@  @@ @@  @@ @@  @@ @@  @@   @@@  @@ @@    @@@ @@@
//  @@@@@  @@  @@ @@  @@  @@@@@    @   @@ @@@@@ @@   @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrDragView::ImpClearVars()
/*N*/ {
/*N*/   bFramDrag=FALSE;
/*N*/   eDragMode=SDRDRAG_MOVE;
/*N*/   bDragLimit=FALSE;
/*N*/   bMarkedHitMovesAlways=FALSE;
/*N*/   eDragHdl=HDL_MOVE;
/*N*/   pDragHdl=NULL;
/*N*/   bDragHdl=FALSE;
/*N*/   bDragSpecial=FALSE;
/*N*/   pDragBla=NULL;
/*N*/   bDragStripes=FALSE;
/*N*/   bNoDragHdl=TRUE;
/*N*/   bMirrRefDragObj=TRUE;
/*N*/   bSolidDragging=FALSE;
/*N*/   bSolidDrgNow=FALSE;
/*N*/   bSolidDrgChk=FALSE;
/*N*/   bDragWithCopy=FALSE;
/*N*/   pInsPointUndo=NULL;
/*N*/   bInsAfter=FALSE;
/*N*/   bInsGluePoint=FALSE;
/*N*/   bInsObjPointMode=FALSE;
/*N*/   bInsGluePointMode=FALSE;
/*N*/   nDragXorPolyLimit=100;
/*N*/   nDragXorPointLimit=500;
/*N*/   bNoDragXorPolys=FALSE;
/*N*/   bAutoVertexCon=TRUE;
/*N*/   bAutoCornerCon=FALSE;
/*N*/   bRubberEdgeDragging=TRUE;
/*N*/   nRubberEdgeDraggingLimit=100;
/*N*/   bDetailedEdgeDragging=TRUE;
/*N*/   nDetailedEdgeDraggingLimit=10;
/*N*/   bResizeAtCenter=FALSE;
/*N*/   bCrookAtCenter=FALSE;
/*N*/   bMouseHideWhileDraggingPoints=FALSE;
/*N*/ }

/*N*/ void SdrDragView::ImpMakeDragAttr()
/*N*/ {
/*N*/   ImpDelDragAttr();
/*N*/ }

/*N*/ SdrDragView::SdrDragView(SdrModel* pModel1, OutputDevice* pOut):
/*N*/   SdrExchangeView(pModel1,pOut)
/*N*/ {
/*N*/   ImpClearVars();
/*N*/   ImpMakeDragAttr();
/*N*/ }

/*?*/ SdrDragView::SdrDragView(SdrModel* pModel1, ExtOutputDevice* pXOut):
/*?*/   SdrExchangeView(pModel1,pXOut)
/*?*/ {
/*?*/   ImpClearVars();
/*?*/   ImpMakeDragAttr();
/*?*/ }

/*N*/ SdrDragView::~SdrDragView()
/*N*/ {
/*N*/   ImpDelDragAttr();
/*N*/ }

/*N*/ void SdrDragView::ImpDelDragAttr()
/*N*/ {
/*N*/ }

/*N*/ BOOL SdrDragView::IsAction() const
/*N*/ {
/*N*/   return SdrExchangeView::IsAction() || pDragBla!=NULL;
/*N*/ }

//STRIP001 void SdrDragView::MovAction(const Point& rPnt)
//STRIP001 {
//STRIP001  SdrExchangeView::MovAction(rPnt);
//STRIP001  if (pDragBla!=NULL) {
//STRIP001      MovDragObj(rPnt);
//STRIP001      RefreshAllIAOManagers();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrDragView::EndAction()
//STRIP001 {
//STRIP001  if (pDragBla!=NULL)
//STRIP001  {
//STRIP001      EndDragObj(FALSE);
//STRIP001      RefreshAllIAOManagers();
//STRIP001  }
//STRIP001  SdrExchangeView::EndAction();
//STRIP001 }

//STRIP001 void SdrDragView::BckAction()
//STRIP001 {
//STRIP001  SdrExchangeView::BckAction();
//STRIP001  BrkDragObj();
//STRIP001  RefreshAllIAOManagers();
//STRIP001 }

/*N*/ void SdrDragView::BrkAction()
/*N*/ {
/*N*/   SdrExchangeView::BrkAction();
/*N*/   BrkDragObj();
/*N*/   RefreshAllIAOManagers();
/*N*/ }

//STRIP001 void SdrDragView::TakeActionRect(Rectangle& rRect) const
//STRIP001 {
//STRIP001  if (pDragBla!=NULL) {
//STRIP001      rRect=aDragStat.GetActionRect();
//STRIP001      if (rRect.IsEmpty()) {
//STRIP001          BOOL b1st=TRUE;
//STRIP001          for (USHORT nv=0; nv<GetPageViewCount(); nv++) {
//STRIP001              SdrPageView* pPV=GetPageViewPvNum(nv);
//STRIP001              if (pPV->HasMarkedObj()) {
//STRIP001                  Rectangle aR(pPV->DragPoly().GetBoundRect(GetWin(0)));
//STRIP001                  aR+=pPV->GetOffset();
//STRIP001                  if (b1st) {
//STRIP001                      b1st=FALSE;
//STRIP001                      rRect=aR;
//STRIP001                  } else {
//STRIP001                      rRect.Union(aR);
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      if (rRect.IsEmpty()) {
//STRIP001          rRect=Rectangle(aDragStat.GetNow(),aDragStat.GetNow());
//STRIP001      }
//STRIP001  } else {
//STRIP001      SdrExchangeView::TakeActionRect(rRect);
//STRIP001  }
//STRIP001 }

/*N*/ void SdrDragView::ToggleShownXor(OutputDevice* pOut, const Region* pRegion) const
/*N*/ {
/*N*/   SdrExchangeView::ToggleShownXor(pOut,pRegion);
    if (pDragBla!=NULL && aDragStat.IsShown() &&
    1 )//STRIP001 //STRIP001        (!IS_TYPE(SdrDragMovHdl,pDragBla)) { // das ist ein Hack !!!!!!!!!!
/*?*/       {DBG_ASSERT(0, "STRIP"); }//STRIP001 DrawDragObj(pOut,TRUE);
//STRIP001 /*?*/    }
/*N*/ }

//STRIP001 void SdrDragView::SetDragPolys(BOOL bReset, BOOL bSeparate)
//STRIP001 {
//STRIP001  USHORT nPvAnz=GetPageViewCount();
//STRIP001  ULONG nMarkAnz=aMark.GetMarkCount();
//STRIP001  if (!bReset && (IsDraggingPoints() || IsDraggingGluePoints())) {
//STRIP001      BOOL bGlue=IsDraggingGluePoints();
//STRIP001      for (USHORT nv=0; nv<nPvAnz; nv++) {
//STRIP001          SdrPageView* pPV=GetPageViewPvNum(nv);
//STRIP001          pPV->DragPoly0().Clear();
//STRIP001          if (pPV->HasMarkedObj()) {
//STRIP001              for (ULONG nm=0; nm<nMarkAnz; nm++) {
//STRIP001                  SdrMark* pM=aMark.GetMark(nm);
//STRIP001                  if (pM->GetPageView()==pPV) {
//STRIP001                      const SdrUShortCont* pPts=bGlue ? pM->GetMarkedGluePoints() : pM->GetMarkedPoints();
//STRIP001                      if (pPts!=NULL && pPts->GetCount()!=0) {
//STRIP001                          const SdrObject* pObj=pM->GetObj();
//STRIP001                          const SdrPathObj* pPath=bGlue ? NULL : PTR_CAST(SdrPathObj,pObj);
//STRIP001                          const XPolyPolygon* pPathXPP=pPath!=NULL ? &pPath->GetPathPoly() : NULL;
//STRIP001                          const SdrGluePointList* pGPL=bGlue ? pObj->GetGluePointList() : NULL;
//STRIP001                          ULONG nPtAnz=pPts->GetCount();
//STRIP001                          XPolygon aXP((USHORT)nPtAnz);
//STRIP001                          for (ULONG nPtNum=0; nPtNum<nPtAnz; nPtNum++) {
//STRIP001                              USHORT nObjPt=pPts->GetObject(nPtNum);
//STRIP001                              if (bGlue) {
//STRIP001                                  if (pGPL!=NULL) {
//STRIP001                                      USHORT nGlueNum=pGPL->FindGluePoint(nObjPt);
//STRIP001                                      if (nGlueNum!=SDRGLUEPOINT_NOTFOUND) {
//STRIP001                                          aXP[(USHORT)nPtNum]=(*pGPL)[nGlueNum].GetAbsolutePos(*pObj);
//STRIP001                                      }
//STRIP001                                  }
//STRIP001                              } else {
//STRIP001                                  if (pPath!=NULL && pPathXPP!=NULL) {
//STRIP001                                      USHORT nPolyNum,nPointNum;
//STRIP001                                      if (pPath->TakePolyIdxForHdlNum(nObjPt,nPolyNum,nPointNum)) {
//STRIP001                                          aXP[(USHORT)nPtNum]=(*pPathXPP)[nPolyNum][nPointNum];
//STRIP001                                      }
//STRIP001                                  }
//STRIP001                              }
//STRIP001                          }
//STRIP001                          pPV->DragPoly0().Insert(aXP);
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          pPV->DragPoly()=pPV->DragPoly0();
//STRIP001      }
//STRIP001      return;
//STRIP001  }
//STRIP001  Rectangle aRect;
//STRIP001  XPolygon aEmptyPoly(0); // Lerres XPoly fuer Separate
//STRIP001  ULONG nMaxObj=nDragXorPolyLimit;
//STRIP001  ULONG nMaxPnt=nDragXorPointLimit;
//STRIP001  BOOL bNoPoly = IsNoDragXorPolys() || aMark.GetMarkCount()>nMaxObj;
//STRIP001  BOOL bBrk=FALSE;
//STRIP001  ULONG nPolyCnt=0; // Max nDragXorPolyLimit Polys
//STRIP001  ULONG nPntCnt=0;  // Max 5*nDragXorPolyLimit Punkte
//STRIP001  if (!bNoPoly && !bReset) {
//STRIP001      for (USHORT nv=0; nv<nPvAnz && !bBrk; nv++) {
//STRIP001          SdrPageView* pPV=GetPageViewPvNum(nv);
//STRIP001          if (pPV->HasMarkedObj()) {
//STRIP001              pPV->DragPoly0().Clear();
//STRIP001              BOOL b1st=TRUE;
//STRIP001              XPolyPolygon aDazuXPP;
//STRIP001              for (ULONG nm=0; nm<nMarkAnz && !bBrk; nm++) {
//STRIP001                  SdrMark* pM=aMark.GetMark(nm);
//STRIP001                  if (pM->GetPageView()==pPV) {
//STRIP001                      pM->GetObj()->TakeXorPoly(aDazuXPP,FALSE);
//STRIP001                      USHORT nDazuPolyAnz=aDazuXPP.Count();
//STRIP001                      nPolyCnt+=nDazuPolyAnz;
//STRIP001                      for (USHORT i=0; i<nDazuPolyAnz; i++) nPntCnt+=aDazuXPP[i].GetPointCount();
//STRIP001                      if (nPolyCnt>nMaxObj || nPntCnt>nMaxPnt) {
//STRIP001                          bBrk=TRUE;
//STRIP001                          bNoPoly=TRUE;
//STRIP001                      }
//STRIP001                      if (!bBrk) {
//STRIP001                          for (USHORT i=0; i<nDazuPolyAnz; i++) {
//STRIP001                              // 2-Punkt-Polygone zu einfachen Linien machen,
//STRIP001                              // damit nicht Xor+Xor=Nix
//STRIP001                              const XPolygon& rP=aDazuXPP[i];
//STRIP001                              if (rP.GetPointCount()==3 && rP[0]==rP[2]) {
//STRIP001                                  aDazuXPP[i].Remove(2,1);
//STRIP001                              }
//STRIP001                          }
//STRIP001                          if (b1st) {
//STRIP001                              pPV->DragPoly0()=aDazuXPP;
//STRIP001                              b1st=FALSE;
//STRIP001                          } else {
//STRIP001                              if (bSeparate) {
//STRIP001                                  // erstmal ein leeres Polygon als Trennung zwischen den Objekten
//STRIP001                                  pPV->DragPoly0().Insert(aEmptyPoly);
//STRIP001                              }
//STRIP001                              pPV->DragPoly0().Insert(aDazuXPP);
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001              pPV->DragPoly()=pPV->DragPoly0();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if (bNoPoly || bReset) {
//STRIP001      for (USHORT nv=0; nv<nPvAnz; nv++) {
//STRIP001          SdrPageView* pPV=GetPageViewPvNum(nv);
//STRIP001          if (!bReset) {
//STRIP001              if (pPV->HasMarkedObj()) {
//STRIP001                  Rectangle aR(pPV->MarkSnap());
//STRIP001                  if (TRUE) {
//STRIP001                      BOOL bMorePoints=TRUE;
//STRIP001                      // Faktor fuer Kontrollpunkte der Bezierkurven:
//STRIP001                      // 8/3 * (sin(45g) - 0.5) * 2/Pi
//STRIP001                      double a=0.3515953911 /2; // /2, weil halbe Strecke
//STRIP001                      if (bMorePoints) a/=2;
//STRIP001                      long dx=(long)(aR.GetWidth()*a);
//STRIP001                      long dy=(long)(aR.GetHeight()*a);
//STRIP001                      XPolygon aXP(25);
//STRIP001                      aXP[ 0]=aR.TopLeft();
//STRIP001                      aXP[ 1]=aR.TopLeft();      aXP[ 1].X()+=dx; aXP.SetFlags( 1,XPOLY_CONTROL);
//STRIP001                      aXP[ 2]=aR.TopCenter();    aXP[ 2].X()-=dx; aXP.SetFlags( 2,XPOLY_CONTROL);
//STRIP001                      aXP[ 3]=aR.TopCenter();
//STRIP001                      aXP[ 4]=aR.TopCenter();    aXP[ 4].X()+=dx; aXP.SetFlags( 4,XPOLY_CONTROL);
//STRIP001                      aXP[ 5]=aR.TopRight();     aXP[ 5].X()-=dx; aXP.SetFlags( 5,XPOLY_CONTROL);
//STRIP001                      aXP[ 6]=aR.TopRight();
//STRIP001                      aXP[ 7]=aR.TopRight();     aXP[ 7].Y()+=dy; aXP.SetFlags( 7,XPOLY_CONTROL);
//STRIP001                      aXP[ 8]=aR.RightCenter();  aXP[ 8].Y()-=dy; aXP.SetFlags( 8,XPOLY_CONTROL);
//STRIP001                      aXP[ 9]=aR.RightCenter();
//STRIP001                      aXP[10]=aR.RightCenter();  aXP[10].Y()+=dy; aXP.SetFlags(10,XPOLY_CONTROL);
//STRIP001                      aXP[11]=aR.BottomRight();  aXP[11].Y()-=dy; aXP.SetFlags(11,XPOLY_CONTROL);
//STRIP001                      aXP[12]=aR.BottomRight();
//STRIP001                      aXP[13]=aR.BottomRight();  aXP[13].X()-=dx; aXP.SetFlags(13,XPOLY_CONTROL);
//STRIP001                      aXP[14]=aR.BottomCenter(); aXP[14].X()+=dx; aXP.SetFlags(14,XPOLY_CONTROL);
//STRIP001                      aXP[15]=aR.BottomCenter();
//STRIP001                      aXP[16]=aR.BottomCenter(); aXP[16].X()-=dx; aXP.SetFlags(16,XPOLY_CONTROL);
//STRIP001                      aXP[17]=aR.BottomLeft();   aXP[17].X()+=dx; aXP.SetFlags(17,XPOLY_CONTROL);
//STRIP001                      aXP[18]=aR.BottomLeft();
//STRIP001                      aXP[19]=aR.BottomLeft();   aXP[19].Y()-=dy; aXP.SetFlags(19,XPOLY_CONTROL);
//STRIP001                      aXP[20]=aR.LeftCenter();   aXP[20].Y()+=dy; aXP.SetFlags(20,XPOLY_CONTROL);
//STRIP001                      aXP[21]=aR.LeftCenter();
//STRIP001                      aXP[22]=aR.LeftCenter();   aXP[22].Y()-=dy; aXP.SetFlags(22,XPOLY_CONTROL);
//STRIP001                      aXP[23]=aR.TopLeft();      aXP[23].Y()+=dy; aXP.SetFlags(23,XPOLY_CONTROL);
//STRIP001                      aXP[24]=aR.TopLeft();
//STRIP001                      if (bMorePoints) {
//STRIP001                          dx=-dx; dy=-dy;
//STRIP001                          for (USHORT i=aXP.GetPointCount(); i>1;) {
//STRIP001                              i--;
//STRIP001                              Point aPnt(aXP[i]);
//STRIP001                              aPnt+=aXP[i-3];
//STRIP001                              aPnt.X()/=2;
//STRIP001                              aPnt.Y()/=2;
//STRIP001                              USHORT nc1=USHORT(i-1);
//STRIP001                              USHORT nc2=USHORT(i+1);
//STRIP001                              BOOL bHor=aXP[i].Y()==aXP[i-3].Y();
//STRIP001                              aXP.Insert(nc1,aPnt,XPOLY_CONTROL); if (bHor) aXP[nc1].X()-=dx; else aXP[nc1].Y()-=dy;
//STRIP001                              aXP.Insert(i  ,aPnt,XPOLY_NORMAL);
//STRIP001                              aXP.Insert(nc2,aPnt,XPOLY_CONTROL); if (bHor) aXP[nc2].X()+=dx; else aXP[nc2].Y()+=dy;
//STRIP001                              if (i==15) { dx=-dx; dy=-dy; }
//STRIP001                              i-=2;
//STRIP001                          }
//STRIP001                      }
//STRIP001                      pPV->DragPoly0()=XPolyPolygon(aXP);
//STRIP001                  } else {
//STRIP001                      XPolygon aXP(aR);
//STRIP001                      pPV->DragPoly0()=XPolyPolygon(aXP);
//STRIP001                  }
//STRIP001                  pPV->DragPoly()=pPV->DragPoly0();
//STRIP001              }
//STRIP001          } else {
//STRIP001              pPV->DragPoly().Clear();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL SdrDragView::TakeDragObjAnchorPos(Point& rPos, BOOL bTR ) const
//STRIP001 {
//STRIP001  Rectangle aR;
//STRIP001  TakeActionRect(aR);
//STRIP001  rPos = bTR ? aR.TopRight() : aR.TopLeft();
//STRIP001  if (aMark.GetMarkCount()==1 && IsDragObj() && // nur bei Einzelselektion
//STRIP001      !IsDraggingPoints() && !IsDraggingGluePoints() && // nicht beim Punkteschieben
//STRIP001      !pDragBla->ISA(SdrDragMovHdl)) // nicht beim Handlesschieben
//STRIP001  {
//STRIP001      SdrObject* pObj=aMark.GetMark(0)->GetObj();
//STRIP001      if (pObj->ISA(SdrCaptionObj)) {
//STRIP001          Point aPt(((SdrCaptionObj*)pObj)->GetTailPos());
//STRIP001          BOOL bTail=eDragHdl==HDL_POLY; // Schwanz wird gedraggt (nicht so ganz feine Abfrage hier)
//STRIP001          BOOL bMove=pDragBla->ISA(SdrDragMove);  // Move des gesamten Obj
//STRIP001          BOOL bOwn=pDragBla->ISA(SdrDragObjOwn); // Objektspeziefisch
//STRIP001          if (!bTail) { // bei bTail liefert TakeActionRect schon das richtige
//STRIP001              if (bOwn) { // bOwn kann sein MoveTextFrame, ResizeTextFrame aber eben nicht mehr DragTail
//STRIP001                  rPos=aPt;
//STRIP001              } else {
//STRIP001                  // hier nun dragging des gesamten Objekts (Move, Resize, ...)
//STRIP001                  pDragBla->MovPoint(aPt,aMark.GetMark(0)->GetPageView()->GetOffset());
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 BOOL SdrDragView::TakeDragLimit(SdrDragMode eMode, Rectangle& rRect) const
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 BOOL SdrDragView::BegDragObj(const Point& rPnt, OutputDevice* pOut, SdrHdl* pHdl, short nMinMov, SdrDragMethod* pForcedMeth)
//STRIP001 {
//STRIP001  BrkAction();
//STRIP001  BOOL bRet=FALSE;
//STRIP001  {
//STRIP001      SetDragWithCopy(FALSE);
//STRIP001      ForceEdgesOfMarkedNodes();
//STRIP001      aAni.Reset();
//STRIP001      pDragBla=NULL;
//STRIP001      bDragSpecial=FALSE;
//STRIP001      bDragLimit=FALSE;
//STRIP001      SdrDragMode eTmpMode=eDragMode;
//STRIP001      if (eTmpMode==SDRDRAG_MOVE && pHdl!=NULL && pHdl->GetKind()!=HDL_MOVE) {
//STRIP001          eTmpMode=SDRDRAG_RESIZE;
//STRIP001      }
//STRIP001      bDragLimit=TakeDragLimit(eTmpMode,aDragLimit);
//STRIP001      bFramDrag=ImpIsFrameHandles();
//STRIP001      if (!bFramDrag &&
//STRIP001          (pMarkedObj==NULL || !pMarkedObj->HasSpecialDrag()) &&
//STRIP001          (pHdl==NULL || pHdl->GetObj()==NULL)) {
//STRIP001          bFramDrag=TRUE;
//STRIP001      }
//STRIP001
//STRIP001      Point aPnt(rPnt);
//STRIP001      if(pHdl == NULL
//STRIP001          || pHdl->GetKind() == HDL_MIRX
//STRIP001          || pHdl->GetKind() == HDL_TRNS
//STRIP001          || pHdl->GetKind() == HDL_GRAD)
//STRIP001      {
//STRIP001          aDragStat.Reset(aPnt);
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          aDragStat.Reset(pHdl->GetPos());
//STRIP001      }
//STRIP001
//STRIP001      aDragStat.SetView((SdrView*)this);
//STRIP001      aDragStat.SetPageView(pMarkedPV);  // <<-- hier muss die DragPV rein!!!
//STRIP001      aDragStat.SetMinMove(ImpGetMinMovLogic(nMinMov,pOut));
//STRIP001      aDragStat.SetHdl(pHdl);
//STRIP001      aDragStat.NextPoint();
//STRIP001      pDragWin=pOut;
//STRIP001      pDragHdl=pHdl;
//STRIP001      eDragHdl= pHdl==NULL ? HDL_MOVE : pHdl->GetKind();
//STRIP001      bDragHdl=eDragHdl==HDL_REF1 || eDragHdl==HDL_REF2 || eDragHdl==HDL_MIRX;
//STRIP001
//STRIP001      // #103894# Expand test for HDL_ANCHOR_TR
//STRIP001      BOOL bNotDraggable = (HDL_ANCHOR == eDragHdl || HDL_ANCHOR_TR == eDragHdl);
//STRIP001
//STRIP001      if(bDragHdl)
//STRIP001      {
//STRIP001          pDragBla = new SdrDragMovHdl(*this);
//STRIP001      }
//STRIP001      else if(!bNotDraggable)
//STRIP001      {
//STRIP001          switch (eDragMode) {
//STRIP001              case SDRDRAG_ROTATE: case SDRDRAG_SHEAR: case SDRDRAG_DISTORT: {
//STRIP001                  switch (eDragHdl) {
//STRIP001                      case HDL_LEFT:  case HDL_RIGHT:
//STRIP001                      case HDL_UPPER: case HDL_LOWER: {
//STRIP001                          // Sind 3D-Objekte selektiert?
//STRIP001                          BOOL b3DObjSelected = FALSE;
//STRIP001                          for(UINT32 a=0;!b3DObjSelected && a<aMark.GetMarkCount();a++)
//STRIP001                          {
//STRIP001                              SdrObject* pObj = aMark.GetMark(a)->GetObj();
//STRIP001                              if(pObj && pObj->ISA(E3dObject))
//STRIP001                                  b3DObjSelected = TRUE;
//STRIP001                          }
//STRIP001                          // Falls ja, Shear auch bei !IsShearAllowed zulassen,
//STRIP001                          // da es sich bei 3D-Objekten um eingeschraenkte
//STRIP001                          // Rotationen handelt
//STRIP001                          if (!b3DObjSelected && !IsShearAllowed())
//STRIP001                              return FALSE;
//STRIP001                          pDragBla=new SdrDragShear(*this,eDragMode==SDRDRAG_ROTATE);
//STRIP001                      } break;
//STRIP001                      case HDL_UPLFT: case HDL_UPRGT:
//STRIP001                      case HDL_LWLFT: case HDL_LWRGT: {
//STRIP001                          if (eDragMode==SDRDRAG_SHEAR || eDragMode==SDRDRAG_DISTORT) {
//STRIP001                              if (!IsDistortAllowed(TRUE) && !IsDistortAllowed(FALSE)) return FALSE;
//STRIP001                              pDragBla=new SdrDragDistort(*this);
//STRIP001                          } else {
//STRIP001                              if (!IsRotateAllowed(TRUE)) return FALSE;
//STRIP001                              pDragBla=new SdrDragRotate(*this);
//STRIP001                          }
//STRIP001                      } break;
//STRIP001                      default: {
//STRIP001                          if (IsMarkedHitMovesAlways() && eDragHdl==HDL_MOVE) { // HDL_MOVE ist auch wenn Obj direkt getroffen
//STRIP001                              if (!IsMoveAllowed()) return FALSE;
//STRIP001                              pDragBla=new SdrDragMove(*this);
//STRIP001                          } else {
//STRIP001                              if (!IsRotateAllowed(TRUE)) return FALSE;
//STRIP001                              pDragBla=new SdrDragRotate(*this);
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001              } break;
//STRIP001              case SDRDRAG_MIRROR: {
//STRIP001                  if (eDragHdl==HDL_MOVE && IsMarkedHitMovesAlways()) {
//STRIP001                      if (!IsMoveAllowed()) return FALSE;
//STRIP001                      pDragBla=new SdrDragMove(*this);
//STRIP001                  } else {
//STRIP001                      if (!IsMirrorAllowed(TRUE,TRUE)) return FALSE;
//STRIP001                      pDragBla=new SdrDragMirror(*this);
//STRIP001                  }
//STRIP001              } break;
//STRIP001
//STRIP001              case SDRDRAG_TRANSPARENCE:
//STRIP001              {
//STRIP001                  if(eDragHdl == HDL_MOVE && IsMarkedHitMovesAlways())
//STRIP001                  {
//STRIP001                      if(!IsMoveAllowed())
//STRIP001                          return FALSE;
//STRIP001                      pDragBla = new SdrDragMove(*this);
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      if(!IsTransparenceAllowed())
//STRIP001                          return FALSE;
//STRIP001
//STRIP001                      pDragBla = new SdrDragGradient(*this, FALSE);
//STRIP001                  }
//STRIP001                  break;
//STRIP001              }
//STRIP001              case SDRDRAG_GRADIENT:
//STRIP001              {
//STRIP001                  if(eDragHdl == HDL_MOVE && IsMarkedHitMovesAlways())
//STRIP001                  {
//STRIP001                      if(!IsMoveAllowed())
//STRIP001                          return FALSE;
//STRIP001                      pDragBla = new SdrDragMove(*this);
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      if(!IsGradientAllowed())
//STRIP001                          return FALSE;
//STRIP001
//STRIP001                      pDragBla = new SdrDragGradient(*this);
//STRIP001                  }
//STRIP001                  break;
//STRIP001              }
//STRIP001
//STRIP001              case SDRDRAG_CROOK : {
//STRIP001                  if (eDragHdl==HDL_MOVE && IsMarkedHitMovesAlways()) {
//STRIP001                      if (!IsMoveAllowed()) return FALSE;
//STRIP001                      pDragBla=new SdrDragMove(*this);
//STRIP001                  } else {
//STRIP001                      if (!IsCrookAllowed(TRUE) && !IsCrookAllowed(FALSE)) return FALSE;
//STRIP001                      pDragBla=new SdrDragCrook(*this);
//STRIP001                  }
//STRIP001              } break;
//STRIP001
//STRIP001              default: { // SDRDRAG_MOVE
//STRIP001                  if (eDragHdl==HDL_GLUE) {
//STRIP001                      pDragBla=new SdrDragMove(*this);
//STRIP001                  } else {
//STRIP001                      if (bFramDrag==TRUE) {
//STRIP001                          if (eDragHdl==HDL_MOVE) {
//STRIP001                              if (!IsMoveAllowed()) return FALSE;
//STRIP001                              pDragBla=new SdrDragMove(*this);
//STRIP001                          } else {
//STRIP001                              if (!IsResizeAllowed(TRUE)) return FALSE;
//STRIP001                              pDragBla=new SdrDragResize(*this);
//STRIP001                          }
//STRIP001                      } else {
//STRIP001                          if (eDragHdl==HDL_MOVE && !IsMoveAllowed()) return FALSE;
//STRIP001                          {
//STRIP001                              bDragSpecial=TRUE;
//STRIP001                              pDragBla=new SdrDragObjOwn(*this);
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      if (pForcedMeth!=NULL) {
//STRIP001          delete pDragBla;
//STRIP001          pDragBla=pForcedMeth;
//STRIP001      }
//STRIP001      aDragStat.SetDragMethod(pDragBla);
//STRIP001      if (pDragBla!=NULL) {
//STRIP001          bRet=pDragBla->Beg();
//STRIP001          if (!bRet) {
//STRIP001              if (pHdl==NULL && IS_TYPE(SdrDragObjOwn,pDragBla)) {
//STRIP001                  // Aha, Obj kann nicht Move SpecialDrag, also MoveFrameDrag versuchen
//STRIP001                  delete pDragBla;
//STRIP001                  pDragBla=NULL;
//STRIP001                  bDragSpecial=FALSE;
//STRIP001                  if (!IsMoveAllowed()) return FALSE;
//STRIP001                  bFramDrag=TRUE;
//STRIP001                  pDragBla=new SdrDragMove(*this);
//STRIP001                  aDragStat.SetDragMethod(pDragBla);
//STRIP001                  bRet=pDragBla->Beg();
//STRIP001              }
//STRIP001          }
//STRIP001          if (!bRet) {
//STRIP001              delete pDragBla;
//STRIP001              pDragBla=NULL;
//STRIP001              aDragStat.SetDragMethod(pDragBla);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // refresh IAOs
//STRIP001 //--/    RefreshAllIAOManagers();
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

/*N*/ BOOL SdrDragView::IsInsObjPointPossible() const
/*N*/ {
/*N*/   return pMarkedObj!=NULL && pMarkedObj->IsPolyObj();
/*N*/ }

//STRIP001 BOOL SdrDragView::BegInsObjPoint(BOOL bIdxZwang, USHORT nIdx, const Point& rPnt, BOOL bNewObj, OutputDevice* pOut, short nMinMov)
//STRIP001 {
//STRIP001  BOOL bRet=FALSE;
//STRIP001  nMinMov=0;
//STRIP001  if (pMarkedObj!=NULL && pMarkedObj->IsPolyObj()) {
//STRIP001      BrkAction();
//STRIP001      pInsPointUndo=new SdrUndoGeoObj(*pMarkedObj);
//STRIP001      XubString aStr(ImpGetResStr(STR_DragInsertPoint));
//STRIP001      XubString aName; pMarkedObj->TakeObjNameSingul(aName);
//STRIP001
//STRIP001      xub_StrLen nPos(aStr.SearchAscii("%O"));
//STRIP001
//STRIP001      if(nPos != STRING_NOTFOUND)
//STRIP001      {
//STRIP001          aStr.Erase(nPos, 2);
//STRIP001          aStr.Insert(aName, nPos);
//STRIP001      }
//STRIP001
//STRIP001      aInsPointUndoStr=aStr;
//STRIP001      Point aPt(rPnt-pMarkedPV->GetOffset());
//STRIP001      if (bNewObj) aPt=GetSnapPos(aPt,pMarkedPV);
//STRIP001      BOOL bClosed0=pMarkedObj->IsClosedObj();
//STRIP001      if (bIdxZwang) {
//STRIP001          nInsPointNum=pMarkedObj->NbcInsPoint(nIdx,aPt,IsInsertAfter(),bNewObj,TRUE);
//STRIP001      } else {
//STRIP001          FASTBOOL bTmpInsAfter = IsInsertAfter();
//STRIP001          nInsPointNum=pMarkedObj->NbcInsPoint(aPt,bNewObj,TRUE,bTmpInsAfter);
//STRIP001      }
//STRIP001      if (bClosed0!=pMarkedObj->IsClosedObj()) { // Obj wurde implizit geschlossen
//STRIP001          pMarkedObj->SendRepaintBroadcast();
//STRIP001      }
//STRIP001      if (nInsPointNum!=0xFFFF) {
//STRIP001          BOOL bVis=IsMarkHdlShown();
//STRIP001          if (bVis) HideMarkHdl(NULL);
//STRIP001          bInsPolyPoint=TRUE;
//STRIP001          UnmarkAllPoints();
//STRIP001          AdjustMarkHdl();
//STRIP001          if (bVis) ShowMarkHdl(NULL);
//STRIP001          bRet=BegDragObj(rPnt,pOut,aHdl.GetHdl(nInsPointNum),0);
//STRIP001          if (bRet) {
//STRIP001              if (nMinMov==0) { // ggf. nicht auf MouseMove warten
//STRIP001                  aDragStat.SetMinMoved();
//STRIP001                  MovDragObj(rPnt);
//STRIP001              }
//STRIP001          }
//STRIP001      } else {
//STRIP001          delete pInsPointUndo;
//STRIP001          pInsPointUndo=NULL;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // refresh IAOs
//STRIP001 //--/    RefreshAllIAOManagers();
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SdrDragView::EndInsObjPoint(SdrCreateCmd eCmd)
//STRIP001 {
//STRIP001  if (IsInsObjPoint()) {
//STRIP001      USHORT nNextPnt=nInsPointNum;
//STRIP001      Point aPnt(aDragStat.GetNow());
//STRIP001      USHORT nMinMov=aDragStat.GetMinMove();
//STRIP001      BOOL bOk=EndDragObj(FALSE);
//STRIP001      if (bOk==TRUE && eCmd!=SDRCREATE_FORCEEND) {
//STRIP001          // Ret=True bedeutet: Action ist vorbei.
//STRIP001          bOk=!(BegInsObjPoint(TRUE,nNextPnt,aPnt,eCmd==SDRCREATE_NEXTOBJECT,pDragWin,nMinMov));
//STRIP001      }
//STRIP001
//STRIP001      // refresh IAOs
//STRIP001 //--/        RefreshAllIAOManagers();
//STRIP001
//STRIP001      return bOk;
//STRIP001  } else return FALSE;
//STRIP001 }

/*N*/ BOOL SdrDragView::IsInsGluePointPossible() const
/*N*/ {
/*N*/   BOOL bRet=FALSE;
/*N*/   if (IsInsGluePointMode() && HasMarkedObj()) {
/*N*/       if (aMark.GetMarkCount()==1) {
/*N*/           // FALSE liefern, wenn 1 Objekt und dieses ein Verbinder ist.
/*N*/           const SdrObject* pObj=aMark.GetMark(0)->GetObj();
/*N*/           if (!HAS_BASE(SdrEdgeObj,pObj)) {
/*N*/              bRet=TRUE;
/*N*/           }
/*N*/       } else {
/*N*/           bRet=TRUE;
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }

//STRIP001 BOOL SdrDragView::BegInsGluePoint(const Point& rPnt)
//STRIP001 {
//STRIP001  BOOL bRet=FALSE;
//STRIP001  SdrObject* pObj;
//STRIP001  SdrPageView* pPV;
//STRIP001  ULONG nMarkNum;
//STRIP001  if (PickMarkedObj(rPnt,pObj,pPV,&nMarkNum,SDRSEARCH_PASS2BOUND)) {
//STRIP001      BrkAction();
//STRIP001      UnmarkAllGluePoints();
//STRIP001      SdrMark* pM=aMark.GetMark(nMarkNum);
//STRIP001      pInsPointUndo=new SdrUndoGeoObj(*pObj);
//STRIP001      XubString aStr(ImpGetResStr(STR_DragInsertGluePoint));
//STRIP001      XubString aName; pObj->TakeObjNameSingul(aName);
//STRIP001
//STRIP001      aStr.SearchAndReplaceAscii("%O", aName);
//STRIP001
//STRIP001      aInsPointUndoStr=aStr;
//STRIP001      SdrGluePointList* pGPL=pObj->ForceGluePointList();
//STRIP001      if (pGPL!=NULL) {
//STRIP001          USHORT nGlueIdx=pGPL->Insert(SdrGluePoint());
//STRIP001          SdrGluePoint& rGP=(*pGPL)[nGlueIdx];
//STRIP001          USHORT nGlueId=rGP.GetId();
//STRIP001          rGP.SetAbsolutePos(rPnt-pPV->GetOffset(),*pObj);
//STRIP001
//STRIP001          SdrHdl* pHdl=NULL;
//STRIP001          if (MarkGluePoint(pObj,nGlueId,pPV)) {
//STRIP001              pHdl=GetGluePointHdl(pObj,nGlueId);
//STRIP001          }
//STRIP001          if (pHdl!=NULL && pHdl->GetKind()==HDL_GLUE && pHdl->GetObj()==pObj && pHdl->GetObjHdlNum()==nGlueId) {
//STRIP001              SetInsertGluePoint(TRUE);
//STRIP001              bRet=BegDragObj(rPnt,NULL,pHdl,0);
//STRIP001              if (bRet) {
//STRIP001                  aDragStat.SetMinMoved();
//STRIP001                  MovDragObj(rPnt);
//STRIP001              } else {
//STRIP001                  SetInsertGluePoint(FALSE);
//STRIP001                  delete pInsPointUndo;
//STRIP001                  pInsPointUndo=NULL;
//STRIP001              }
//STRIP001          } else {
//STRIP001              DBG_ERROR("BegInsGluePoint(): GluePoint-Handle nicht gefunden");
//STRIP001          }
//STRIP001      } else {
//STRIP001          // Keine Klebepunkte moeglich bei diesem Objekt (z.B. Edge)
//STRIP001          SetInsertGluePoint(FALSE);
//STRIP001          delete pInsPointUndo;
//STRIP001          pInsPointUndo=NULL;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // refresh IAOs
//STRIP001 //--/    RefreshAllIAOManagers();
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 void SdrDragView::MovDragObj(const Point& rPnt)
//STRIP001 {
//STRIP001  if (pDragBla!=NULL) {
//STRIP001      Point aPnt(rPnt);
//STRIP001      ImpLimitToWorkArea(aPnt);
//STRIP001      pDragBla->Mov(aPnt);
//STRIP001      if (IsDragHdlHide() && aDragStat.IsMinMoved() && !bDragHdl && IsMarkHdlShown()) {
//STRIP001          BOOL bLeaveRefs=IS_TYPE(SdrDragMirror,pDragBla) || IS_TYPE(SdrDragRotate,pDragBla);
//STRIP001          BOOL bFlag=IsSolidMarkHdl() && aDragStat.IsShown();
//STRIP001          if (bFlag) HideDragObj(pDragWin);
//STRIP001          HideMarkHdl(pDragWin,bLeaveRefs);
//STRIP001          if (bFlag) ShowDragObj(pDragWin);
//STRIP001      }
//STRIP001
//STRIP001      // refresh IAOs
//STRIP001 //--/        RefreshAllIAOManagers();
//STRIP001
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL SdrDragView::EndDragObj(BOOL bCopy)
//STRIP001 {
//STRIP001  BOOL bRet=FALSE;
//STRIP001  if (pDragBla!=NULL && aDragStat.IsMinMoved() && aDragStat.GetNow()!=aDragStat.GetPrev()) {
//STRIP001      ULONG nHdlAnzMerk=0;
//STRIP001      if (bEliminatePolyPoints) { // IBM Special
//STRIP001          nHdlAnzMerk=GetMarkablePointCount();
//STRIP001      }
//STRIP001      if (IsInsertGluePoint()) {
//STRIP001          BegUndo(aInsPointUndoStr);
//STRIP001          AddUndo(pInsPointUndo);
//STRIP001      }
//STRIP001      bRet=pDragBla->End(bCopy);
//STRIP001      if (IsInsertGluePoint()) EndUndo();
//STRIP001      delete pDragBla;
//STRIP001      if (bEliminatePolyPoints) { // IBM Special
//STRIP001          if (nHdlAnzMerk!=GetMarkablePointCount()) {
//STRIP001              UnmarkAllPoints();
//STRIP001          }
//STRIP001      }
//STRIP001      pDragBla=NULL;
//STRIP001      if (bInsPolyPoint) {
//STRIP001          BOOL bVis=IsMarkHdlShown();
//STRIP001          if (bVis) HideMarkHdl(NULL);
//STRIP001          SetMarkHandles();
//STRIP001          bInsPolyPoint=FALSE;
//STRIP001          if (bVis) ShowMarkHdl(NULL);
//STRIP001          BegUndo(aInsPointUndoStr);
//STRIP001          AddUndo(pInsPointUndo);
//STRIP001          EndUndo();
//STRIP001      }
//STRIP001      if (!bSomeObjChgdFlag) { // Aha, Obj hat nicht gebroadcastet (z.B. Writer FlyFrames)
//STRIP001          if (IsDragHdlHide() && !bDragHdl &&
//STRIP001              !IS_TYPE(SdrDragMirror,pDragBla) && !IS_TYPE(SdrDragRotate,pDragBla))
//STRIP001          {
//STRIP001              AdjustMarkHdl();
//STRIP001              ShowMarkHdl(pDragWin);
//STRIP001          }
//STRIP001      }
//STRIP001      eDragHdl=HDL_MOVE;
//STRIP001      pDragHdl=NULL;
//STRIP001      SetDragPolys(TRUE);
//STRIP001 //--/        RefreshAllIAOManagers();
//STRIP001  } else {
//STRIP001      BrkDragObj();
//STRIP001  }
//STRIP001  bInsPolyPoint=FALSE;
//STRIP001  SetInsertGluePoint(FALSE);
//STRIP001
//STRIP001  // refresh IAOs
//STRIP001 //--/    RefreshAllIAOManagers();
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

/*N*/ void SdrDragView::BrkDragObj()
/*N*/ {
/*N*/   if (pDragBla!=NULL) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        pDragBla->Brk();
//STRIP001 /*?*/        delete pDragBla;
//STRIP001 /*?*/        pDragBla=NULL;
//STRIP001 /*?*/        if (bInsPolyPoint) {
//STRIP001 /*?*/            BOOL bVis=IsMarkHdlShown();
//STRIP001 /*?*/            if (bVis) HideMarkHdl(NULL);
//STRIP001 /*?*/            pInsPointUndo->Undo(); // Den eingefuegten Punkt wieder raus
//STRIP001 /*?*/            delete pInsPointUndo;
//STRIP001 /*?*/            pInsPointUndo=NULL;
//STRIP001 /*?*/            SetMarkHandles();
//STRIP001 /*?*/            bInsPolyPoint=FALSE;
//STRIP001 /*?*/            if (bVis) ShowMarkHdl(NULL);
//STRIP001 /*?*/        }
//STRIP001 /*?*/        if (IsInsertGluePoint()) {
//STRIP001 /*?*/            pInsPointUndo->Undo(); // Den eingefuegten Klebepunkt wieder raus
//STRIP001 /*?*/            delete pInsPointUndo;
//STRIP001 /*?*/            pInsPointUndo=NULL;
//STRIP001 /*?*/            SetInsertGluePoint(FALSE);
//STRIP001 /*?*/        }
//STRIP001 /*?*/        if (IsDragHdlHide() && !bDragHdl &&
//STRIP001 /*?*/            !IS_TYPE(SdrDragMirror,pDragBla) && !IS_TYPE(SdrDragRotate,pDragBla))
//STRIP001 /*?*/        {
//STRIP001 /*?*/            ShowMarkHdl(pDragWin);
//STRIP001 /*?*/        }
//STRIP001 /*?*/        eDragHdl=HDL_MOVE;
//STRIP001 /*?*/        pDragHdl=NULL;
//STRIP001 /*?*/        SetDragPolys(TRUE);
//STRIP001 /*?*/
//STRIP001 /*?*/        // refresh IAOs
//STRIP001 /*?*/ //--/      RefreshAllIAOManagers();
//STRIP001 /*?*/
/*N*/   }
/*N*/ }

//STRIP001 void SdrDragView::DrawDragObj(OutputDevice* pOut, BOOL bFull) const
//STRIP001 {
//STRIP001  if (pDragBla!=NULL) {
//STRIP001      USHORT i=0;
//STRIP001      do {
//STRIP001          OutputDevice* pO=pOut;
//STRIP001          if (pO==NULL) {
//STRIP001              pO=GetWin(i);
//STRIP001              i++;
//STRIP001          }
//STRIP001          if (pO!=NULL) {
//STRIP001              ImpSdrHdcMerk aHDCMerk(*pO,SDRHDC_SAVEPENANDBRUSH,bRestoreColors);
//STRIP001              RasterOp eRop0=pO->GetRasterOp();
//STRIP001              pO->SetRasterOp(ROP_INVERT);
//STRIP001              pXOut->SetOutDev(pO);
//STRIP001              Color aBlackColor( COL_BLACK );
//STRIP001              Color aTranspColor( COL_TRANSPARENT );
//STRIP001              pXOut->OverrideLineColor( aBlackColor );
//STRIP001              pXOut->OverrideFillColor( aTranspColor );
//STRIP001              pDragBla->DrawXor(*pXOut,bFull);
//STRIP001              pXOut->SetOffset(Point(0,0));
//STRIP001              pO->SetRasterOp(eRop0);
//STRIP001              aHDCMerk.Restore(*pO);
//STRIP001          }
//STRIP001      } while (pOut==NULL && i<GetWinCount());
//STRIP001      if (aAni.IsStripes() && IsDragStripes()) {
//STRIP001          Rectangle aR;
//STRIP001          TakeActionRect(aR);
//STRIP001          aAni.SetP1(aR.TopLeft());
//STRIP001          aAni.SetP2(aR.BottomRight());
//STRIP001          aAni.Invert(pOut);
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL SdrDragView::IsMoveOnlyDragObj(BOOL bAskRTTI) const
//STRIP001 {
//STRIP001  BOOL bRet=FALSE;
//STRIP001  if (pDragBla!=NULL && !IsDraggingPoints() && !IsDraggingGluePoints()) {
//STRIP001      if (bAskRTTI) {
//STRIP001          bRet=IS_TYPE(SdrDragMove,pDragBla);
//STRIP001      } else {
//STRIP001          bRet=pDragBla->IsMoveOnly();
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 void SdrDragView::ImpDrawEdgeXor(ExtOutputDevice& rXOut, BOOL bFull) const
//STRIP001 {
//STRIP001  ULONG nEdgeAnz=aEdgesOfMarkedNodes.GetMarkCount();
//STRIP001  BOOL bNo=(!IsRubberEdgeDragging() && !IsDetailedEdgeDragging()) || nEdgeAnz==0 ||
//STRIP001               IsDraggingPoints() || IsDraggingGluePoints();
//STRIP001  if (!pDragBla->IsMoveOnly() &&
//STRIP001      !(IS_TYPE(SdrDragMove,pDragBla) || IS_TYPE(SdrDragResize,pDragBla) ||
//STRIP001        IS_TYPE(SdrDragRotate,pDragBla) || IS_TYPE(SdrDragMirror,pDragBla))) bNo=TRUE;
//STRIP001  if (!bNo) {
//STRIP001      BOOL bDetail=IsDetailedEdgeDragging() && pDragBla->IsMoveOnly() &&
//STRIP001                       nEdgeAnz<=nDetailedEdgeDraggingLimit;
//STRIP001      if (!bDetail && !(IsRubberEdgeDragging() ||
//STRIP001                        nEdgeAnz>nRubberEdgeDraggingLimit)) bNo=TRUE;
//STRIP001      if (!bNo) {
//STRIP001          for (USHORT i=0; i<nEdgeAnz; i++) {
//STRIP001              SdrMark* pEM=aEdgesOfMarkedNodes.GetMark(i);
//STRIP001              SdrObject* pEdge=pEM->GetObj();
//STRIP001              SdrPageView* pEPV=pEM->GetPageView();
//STRIP001              pXOut->SetOffset(pEPV->GetOffset());
//STRIP001              pEdge->NspToggleEdgeXor(aDragStat,rXOut,pEM->IsCon1(),pEM->IsCon2(),bDetail);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrDragView::ShowDragObj(OutputDevice* pOut)
//STRIP001 {
//STRIP001  if(pDragBla && !aDragStat.IsShown())
//STRIP001  {
//STRIP001      DrawDragObj(pOut, FALSE);
//STRIP001      aDragStat.SetShown(TRUE);
//STRIP001
//STRIP001      // #93700# set shown state at views
//STRIP001      if(pOut)
//STRIP001      {
//STRIP001          sal_uInt16 nw(aWinList.Find(pOut));
//STRIP001
//STRIP001          if(nw < GetWinCount() && SDRVIEWWIN_NOTFOUND != nw)
//STRIP001          {
//STRIP001              if(!IsShownXorVisibleWinNum(nw))
//STRIP001              {
//STRIP001                  SetShownXorVisible(nw, TRUE);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if(aAni.IsStripes() && IsDragStripes())
//STRIP001      {
//STRIP001          aAni.Start();
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrDragView::HideDragObj(OutputDevice* pOut)
//STRIP001 {
//STRIP001  if(pDragBla && aDragStat.IsShown())
//STRIP001  {
//STRIP001      if(aAni.IsStripes() && IsDragStripes())
//STRIP001          aAni.Stop();
//STRIP001
//STRIP001      DrawDragObj(pOut, FALSE);
//STRIP001      aDragStat.SetShown(FALSE);
//STRIP001
//STRIP001      // #93700# clear shown state at views
//STRIP001      if(pOut)
//STRIP001      {
//STRIP001          sal_uInt16 nw(aWinList.Find(pOut));
//STRIP001
//STRIP001          if(nw < GetWinCount() && SDRVIEWWIN_NOTFOUND != nw)
//STRIP001          {
//STRIP001              if(IsShownXorVisibleWinNum(nw))
//STRIP001              {
//STRIP001                  SetShownXorVisible(nw, FALSE);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrDragView::SetNoDragXorPolys(BOOL bOn)
/*N*/ {
/*N*/   if (IsNoDragXorPolys()!=bOn) {
/*N*/       BOOL bDragging=pDragBla!=NULL;
/*N*/       BOOL bShown=bDragging && aDragStat.IsShown();
/*N*/       if (bShown) {DBG_ASSERT(0, "STRIP");} //STRIP001 HideDragObj(pDragWin);
/*N*/       bNoDragXorPolys=bOn;
/*N*/       if (bDragging) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            SetDragPolys(FALSE,IS_TYPE(SdrDragCrook,pDragBla));
//STRIP001 /*?*/            pDragBla->MovAllPoints(); // die gedraggten Polys neu berechnen
/*N*/       }
/*N*/       if (bShown) {DBG_ASSERT(0, "STRIP"); }//STRIP001 ShowDragObj(pDragWin);
/*N*/   }
/*N*/ }

/*N*/ void SdrDragView::SetDragStripes(BOOL bOn)
/*N*/ {
/*N*/   if (pDragBla!=NULL && aDragStat.IsShown()) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        HideDragObj(pDragWin);
//STRIP001 /*?*/        bDragStripes=bOn;
//STRIP001 /*?*/        ShowDragObj(pDragWin);
/*N*/   } else {
/*N*/       bDragStripes=bOn;
/*N*/   }
/*N*/ }

//STRIP001 void SdrDragView::SetDragHdlHide(BOOL bOn)
//STRIP001 {
//STRIP001  bNoDragHdl=bOn;
//STRIP001  if (pDragBla!=NULL && !bDragHdl && !IS_TYPE(SdrDragMirror,pDragBla) && !IS_TYPE(SdrDragRotate,pDragBla))
//STRIP001  {
//STRIP001      if (bOn) HideMarkHdl(pDragWin);
//STRIP001      else ShowMarkHdl(pDragWin);
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL SdrDragView::IsOrthoDesired() const
//STRIP001 {
//STRIP001  if (pDragBla!=NULL && (IS_TYPE(SdrDragObjOwn,pDragBla) || IS_TYPE(SdrDragResize,pDragBla))) {
//STRIP001      return bOrthoDesiredOnMarked;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrDragView::SetRubberEdgeDragging(BOOL bOn)
//STRIP001 {
//STRIP001  if (bOn!=IsRubberEdgeDragging()) {
//STRIP001      ULONG nAnz=aEdgesOfMarkedNodes.GetMarkCount();
//STRIP001      BOOL bShowHide=nAnz!=0 && IsDragObj() &&
//STRIP001               (nRubberEdgeDraggingLimit>=nAnz);
//STRIP001      if (bShowHide) HideDragObj(NULL);
//STRIP001      bRubberEdgeDragging=bOn;
//STRIP001      if (bShowHide) ShowDragObj(NULL);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrDragView::SetRubberEdgeDraggingLimit(USHORT nEdgeObjAnz)
//STRIP001 {
//STRIP001  if (nEdgeObjAnz!=nRubberEdgeDraggingLimit) {
//STRIP001      ULONG nAnz=aEdgesOfMarkedNodes.GetMarkCount();
//STRIP001      BOOL bShowHide=IsRubberEdgeDragging() && nAnz!=0 && IsDragObj() &&
//STRIP001               (nEdgeObjAnz>=nAnz)!=(nRubberEdgeDraggingLimit>=nAnz);
//STRIP001      if (bShowHide) HideDragObj(NULL);
//STRIP001      nRubberEdgeDraggingLimit=nEdgeObjAnz;
//STRIP001      if (bShowHide) ShowDragObj(NULL);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrDragView::SetDetailedEdgeDragging(BOOL bOn)
//STRIP001 {
//STRIP001  if (bOn!=IsDetailedEdgeDragging()) {
//STRIP001      ULONG nAnz=aEdgesOfMarkedNodes.GetMarkCount();
//STRIP001      BOOL bShowHide=nAnz!=0 && IsDragObj() &&
//STRIP001               (nDetailedEdgeDraggingLimit>=nAnz);
//STRIP001      if (bShowHide) HideDragObj(NULL);
//STRIP001      bDetailedEdgeDragging=bOn;
//STRIP001      if (bShowHide) ShowDragObj(NULL);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrDragView::SetDetailedEdgeDraggingLimit(USHORT nEdgeObjAnz)
//STRIP001 {
//STRIP001  if (nEdgeObjAnz!=nDetailedEdgeDraggingLimit) {
//STRIP001      ULONG nAnz=aEdgesOfMarkedNodes.GetMarkCount();
//STRIP001      BOOL bShowHide=IsDetailedEdgeDragging() && nAnz!=0 && IsDragObj() &&
//STRIP001               (nEdgeObjAnz>=nAnz)!=(nDetailedEdgeDraggingLimit>=nAnz);
//STRIP001      if (bShowHide) HideDragObj(NULL);
//STRIP001      nDetailedEdgeDraggingLimit=nEdgeObjAnz;
//STRIP001      if (bShowHide) ShowDragObj(NULL);
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrDragView::WriteRecords(SvStream& rOut) const
/*N*/ {
/*N*/   SdrExchangeView::WriteRecords(rOut);
/*N*/   {
/*N*/       SdrNamedSubRecord aSubRecord(rOut,STREAM_WRITE,SdrInventor,SDRIORECNAME_VIEWDRAGSTRIPES);
/*N*/       rOut<<(BOOL)bDragStripes;
/*N*/   } {
/*N*/       SdrNamedSubRecord aSubRecord(rOut,STREAM_WRITE,SdrInventor,SDRIORECNAME_VIEWDRAGHIDEHDL);
/*N*/       rOut<<(BOOL)bNoDragHdl;
/*N*/   } {
/*N*/       SdrNamedSubRecord aSubRecord(rOut,STREAM_WRITE,SdrInventor,SDRIORECNAME_VIEWOBJHITMOVES);
/*N*/       rOut<<(BOOL)bMarkedHitMovesAlways;
/*N*/   } {
/*N*/       SdrNamedSubRecord aSubRecord(rOut,STREAM_WRITE,SdrInventor,SDRIORECNAME_VIEWMIRRDRAGOBJ);
/*N*/       rOut<<(BOOL)bMirrRefDragObj;
/*N*/   }
/*N*/ }

/*N*/ BOOL SdrDragView::ReadRecord(const SdrIOHeader& rViewHead,
/*N*/   const SdrNamedSubRecord& rSubHead,
/*N*/   SvStream& rIn)
/*N*/ {
/*N*/   BOOL bRet=FALSE;
/*N*/   if (rSubHead.GetInventor()==SdrInventor) {
/*N*/       bRet=TRUE;
/*N*/       switch (rSubHead.GetIdentifier()) {
/*N*/           case SDRIORECNAME_VIEWDRAGSTRIPES: {
/*N*/               BOOL bZwi; rIn >> bZwi; bDragStripes = bZwi;
/*N*/           } break;
/*N*/           case SDRIORECNAME_VIEWDRAGHIDEHDL: {
/*N*/               BOOL bZwi; rIn >> bZwi; bNoDragHdl = bZwi;
/*N*/           } break;
/*N*/           case SDRIORECNAME_VIEWOBJHITMOVES: {
/*N*/               BOOL bZwi; rIn >> bZwi; bMarkedHitMovesAlways = bZwi;
/*N*/           } break;
/*N*/           case SDRIORECNAME_VIEWMIRRDRAGOBJ: {
/*N*/               BOOL bZwi; rIn >> bZwi; bMirrRefDragObj = bZwi;
/*N*/           } break;
/*N*/           default: bRet=FALSE;
/*N*/       }
/*N*/   }
/*N*/   if (!bRet) bRet=SdrExchangeView::ReadRecord(rViewHead,rSubHead,rIn);
/*N*/   return bRet;
/*N*/ }

