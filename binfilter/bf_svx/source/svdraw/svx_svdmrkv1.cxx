/*************************************************************************
 *
 *  $RCSfile: svx_svdmrkv1.cxx,v $
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
#include "svdpagv.hxx"
#include "svdpage.hxx"
#include "svddrgm1.hxx"
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@@@@  @@  @@ @@  @@ @@  @@ @@@@@@ @@   @@  @@@@  @@@@@  @@  @@ @@ @@@@@ @@@@@  @@  @@ @@  @@  @@@@
//  @@  @@ @@  @@ @@@ @@ @@  @@   @@   @@@ @@@ @@  @@ @@  @@ @@  @@ @@ @@    @@  @@ @@  @@ @@@ @@ @@  @@
//  @@  @@ @@  @@ @@@@@@ @@ @@    @@   @@@@@@@ @@  @@ @@  @@ @@ @@  @@ @@    @@  @@ @@  @@ @@@@@@ @@
//  @@@@@  @@  @@ @@@@@@ @@@@     @@   @@@@@@@ @@@@@@ @@@@@  @@@@   @@ @@@@  @@@@@  @@  @@ @@@@@@ @@ @@@
//  @@     @@  @@ @@ @@@ @@ @@    @@   @@ @ @@ @@  @@ @@  @@ @@ @@  @@ @@    @@  @@ @@  @@ @@ @@@ @@  @@
//  @@     @@  @@ @@  @@ @@  @@   @@   @@   @@ @@  @@ @@  @@ @@  @@ @@ @@    @@  @@ @@  @@ @@  @@ @@  @@
//  @@      @@@@  @@  @@ @@  @@   @@   @@   @@ @@  @@ @@  @@ @@  @@ @@ @@@@@ @@  @@  @@@@  @@  @@  @@@@@
//
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ BOOL SdrMarkView::HasMarkablePoints() const
/*N*/ {
/*N*/   ForceUndirtyMrkPnt();
/*N*/   BOOL bRet=FALSE;
/*N*/   if (!ImpIsFrameHandles()) {
/*?*/       ULONG nMarkAnz=aMark.GetMarkCount();
/*?*/       if (nMarkAnz<=nFrameHandlesLimit) {
/*?*/           for (ULONG nMarkNum=0; nMarkNum<nMarkAnz && !bRet; nMarkNum++) {
/*?*/               const SdrMark* pM=aMark.GetMark(nMarkNum);
/*?*/               const SdrObject* pObj=pM->GetObj();
/*?*/               bRet=pObj->IsPolyObj();
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }

//STRIP001 ULONG SdrMarkView::GetMarkablePointCount() const
//STRIP001 {
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  ULONG nAnz=0;
//STRIP001  if (!ImpIsFrameHandles()) {
//STRIP001      ULONG nMarkAnz=aMark.GetMarkCount();
//STRIP001      if (nMarkAnz<=nFrameHandlesLimit) {
//STRIP001          for (ULONG nMarkNum=0; nMarkNum<nMarkAnz; nMarkNum++) {
//STRIP001              const SdrMark* pM=aMark.GetMark(nMarkNum);
//STRIP001              const SdrObject* pObj=pM->GetObj();
//STRIP001              if (pObj->IsPolyObj()) {
//STRIP001                  nAnz+=pObj->GetPointCount();
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return nAnz;
//STRIP001 }

/*N*/ BOOL SdrMarkView::HasMarkedPoints() const
/*N*/ {
/*N*/   ForceUndirtyMrkPnt();
/*N*/   BOOL bRet=FALSE;
/*N*/   if (!ImpIsFrameHandles()) {
/*N*/       ULONG nMarkAnz=aMark.GetMarkCount();
/*N*/       if (nMarkAnz<=nFrameHandlesLimit) {
/*N*/           for (ULONG nMarkNum=0; nMarkNum<nMarkAnz && !bRet; nMarkNum++) {
/*?*/               const SdrMark* pM=aMark.GetMark(nMarkNum);
/*?*/               const SdrUShortCont* pPts=pM->GetMarkedPoints();
/*?*/               bRet=pPts!=NULL && pPts->GetCount()!=0;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }

//STRIP001 ULONG SdrMarkView::GetMarkedPointCount() const
//STRIP001 {
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  ULONG nAnz=0;
//STRIP001  if (!ImpIsFrameHandles()) {
//STRIP001      ULONG nMarkAnz=aMark.GetMarkCount();
//STRIP001      if (nMarkAnz<=nFrameHandlesLimit) {
//STRIP001          for (ULONG nMarkNum=0; nMarkNum<nMarkAnz; nMarkNum++) {
//STRIP001              const SdrMark* pM=aMark.GetMark(nMarkNum);
//STRIP001              const SdrUShortCont* pPts=pM->GetMarkedPoints();
//STRIP001              if (pPts!=NULL) nAnz+=pPts->GetCount();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return nAnz;
//STRIP001 }

//STRIP001 BOOL SdrMarkView::IsPointMarkable(const SdrHdl& rHdl) const
//STRIP001 {
//STRIP001  return !ImpIsFrameHandles() && &rHdl!=NULL && !rHdl.IsPlusHdl() && rHdl.GetKind()!=HDL_GLUE && rHdl.GetObj()!=NULL && rHdl.GetObj()->IsPolyObj();
//STRIP001 }

//STRIP001 BOOL SdrMarkView::ImpMarkPoint(SdrHdl* pHdl, SdrMark* pMark, BOOL bUnmark)
//STRIP001 {
//STRIP001  if (pHdl==NULL || pHdl->IsPlusHdl() || pHdl->GetKind()==HDL_GLUE) return FALSE;
//STRIP001  if (pHdl->IsSelected() != bUnmark) return FALSE;
//STRIP001  SdrObject* pObj=pHdl->GetObj();
//STRIP001  if (pObj==NULL || !pObj->IsPolyObj()) return FALSE;
//STRIP001  if (pMark==NULL) {
//STRIP001      ULONG nMarkNum=aMark.FindObject(pObj);
//STRIP001      if (nMarkNum==CONTAINER_ENTRY_NOTFOUND) return FALSE;
//STRIP001      pMark=aMark.GetMark(nMarkNum);
//STRIP001  }
//STRIP001  USHORT nHdlNum=pHdl->GetObjHdlNum();
//STRIP001  SdrUShortCont* pPts=pMark->ForceMarkedPoints();
//STRIP001  if (!bUnmark) {
//STRIP001      pPts->Insert(nHdlNum);
//STRIP001  } else {
//STRIP001      ULONG nBla=pPts->GetPos(nHdlNum);
//STRIP001      if (nBla!=CONTAINER_ENTRY_NOTFOUND) {
//STRIP001          pPts->Remove(nBla);
//STRIP001      } else return FALSE; // Fehlerfall!
//STRIP001  }
//STRIP001  BOOL bVis=IsMarkHdlShown();
//STRIP001  USHORT nWinAnz=GetWinCount();
//STRIP001 //    if (bVis) for (nw=0; nw<nWinAnz; nw++) pHdl->Draw(*GetWin(nw));
//STRIP001  pHdl->SetSelected(!bUnmark);
//STRIP001 //    if (bVis) for (nw=0; nw<nWinAnz; nw++) pHdl->Draw(*GetWin(nw));
//STRIP001  if (!bPlusHdlAlways) {
//STRIP001      BOOL bSolid=IsSolidMarkHdl();
//STRIP001      if (!bUnmark) {
//STRIP001          USHORT nAnz=pObj->GetPlusHdlCount(*pHdl);
//STRIP001          if (nAnz!=0 && bSolid && bVis) HideMarkHdl(NULL);
//STRIP001          for (USHORT i=0; i<nAnz; i++) {
//STRIP001              SdrHdl* pPlusHdl=pObj->GetPlusHdl(*pHdl,i);
//STRIP001              if (pPlusHdl!=NULL) {
//STRIP001                  pPlusHdl->SetObj(pObj);
//STRIP001                  pPlusHdl->SetPageView(pMark->GetPageView());
//STRIP001                  pPlusHdl->SetPlusHdl(TRUE);
//STRIP001                  aHdl.AddHdl(pPlusHdl);
//STRIP001 //                    if (bVis && !bSolid) for (nw=0; nw<nWinAnz; nw++) pPlusHdl->Draw(*GetWin(nw));
//STRIP001              }
//STRIP001          }
//STRIP001          if (nAnz!=0 && bSolid && bVis) ShowMarkHdl(NULL);
//STRIP001      } else {
//STRIP001          ULONG nAnz=aHdl.GetHdlCount();
//STRIP001          for (ULONG i=nAnz; i>0;) {
//STRIP001              i--;
//STRIP001              SdrHdl* pPlusHdl=aHdl.GetHdl(i);
//STRIP001              BOOL bFlag=FALSE;
//STRIP001              if (pPlusHdl->IsPlusHdl() && pPlusHdl->GetSourceHdlNum()==nHdlNum) {
//STRIP001                  if (bVis) {
//STRIP001                      if (bSolid) {
//STRIP001                          bFlag=TRUE;
//STRIP001                          HideMarkHdl(NULL); // SolidMarkHdl und Bezier ist noch nicht fertig!
//STRIP001                      }
//STRIP001 //                       else {
//STRIP001 //                            for (nw=0; nw<nWinAnz; nw++) pPlusHdl->Draw(*GetWin(nw));
//STRIP001 //                        }
//STRIP001                  }
//STRIP001                  aHdl.RemoveHdl(i);
//STRIP001                  delete pPlusHdl;
//STRIP001              }
//STRIP001              if (bFlag) ShowMarkHdl(NULL);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // refresh IAOs
//STRIP001 //   RefreshAllIAOManagers();
//STRIP001
//STRIP001  // #97016# II: Sort handles. This was missing in ImpMarkPoint all the time.
//STRIP001  aHdl.Sort();
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL SdrMarkView::MarkPoint(SdrHdl& rHdl, BOOL bUnmark)
//STRIP001 {
//STRIP001  if (&rHdl==NULL) return FALSE;
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  BOOL bRet=FALSE;
//STRIP001  const SdrObject* pObj=rHdl.GetObj();
//STRIP001  if (IsPointMarkable(rHdl) && rHdl.IsSelected()==bUnmark) {
//STRIP001      ULONG nMarkNum=aMark.FindObject(pObj);
//STRIP001      if (nMarkNum!=CONTAINER_ENTRY_NOTFOUND) {
//STRIP001          SdrMark* pM=aMark.GetMark(nMarkNum);
//STRIP001          SdrUShortCont* pPts=pM->ForceMarkedPoints();
//STRIP001          pPts->ForceSort();
//STRIP001          if (ImpMarkPoint(&rHdl,pM,bUnmark)) {
//STRIP001              pPts->ForceSort();
//STRIP001              MarkListHasChanged();
//STRIP001              bRet=TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // #90239# refresh IAOs
//STRIP001  // added this call again to make visible (un)marking of point(s)
//STRIP001  if(bRet)
//STRIP001      RefreshAllIAOManagers();
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

/*N*/ BOOL SdrMarkView::MarkPoints(const Rectangle* pRect, BOOL bUnmark)
/*N*/ {
/*N*/   ForceUndirtyMrkPnt();
/*N*/   BOOL bChgd=FALSE;
/*N*/   aMark.ForceSort();
/*N*/   const SdrObject* pObj0=NULL;
/*N*/   const SdrPageView* pPV0=NULL;
/*N*/   SdrMark* pM=NULL;
/*N*/   aHdl.Sort();
/*N*/   BOOL bHideHdl=IsMarkHdlShown() && IsSolidMarkHdl() && !bPlusHdlAlways;
/*N*/   ULONG nHdlAnz=aHdl.GetHdlCount();
/*N*/   for (ULONG nHdlNum=nHdlAnz; nHdlNum>0;) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        nHdlNum--;
//STRIP001 /*?*/        SdrHdl* pHdl=aHdl.GetHdl(nHdlNum);
//STRIP001 /*?*/        if (IsPointMarkable(*pHdl) && pHdl->IsSelected()==bUnmark) {
//STRIP001 /*?*/            const SdrObject* pObj=pHdl->GetObj();
//STRIP001 /*?*/            const SdrPageView* pPV=pHdl->GetPageView();
//STRIP001 /*?*/            if (pObj!=pObj0 || pPV!=pPV0 || pM==NULL) { // Dieser Abschnitt dient zur Optimierung,
//STRIP001 /*?*/                if (pM!=NULL) {
//STRIP001 /*?*/                    SdrUShortCont* pPts=pM->GetMarkedPoints();
//STRIP001 /*?*/                    if (pPts!=NULL) pPts->ForceSort();
//STRIP001 /*?*/                }
//STRIP001 /*?*/                ULONG nMarkNum=aMark.FindObject(pObj);  // damit ImpMarkPoint() nicht staendig das
//STRIP001 /*?*/                if (nMarkNum!=CONTAINER_ENTRY_NOTFOUND) { // Objekt in der MarkList suchen muss.
//STRIP001 /*?*/                    pM=aMark.GetMark(nMarkNum);
//STRIP001 /*?*/                    pObj0=pObj;
//STRIP001 /*?*/                    pPV0=pPV;
//STRIP001 /*?*/                    SdrUShortCont* pPts=pM->ForceMarkedPoints();
//STRIP001 /*?*/                    pPts->ForceSort();
//STRIP001 /*?*/                } else {
//STRIP001 /*?*/ #ifdef DBG_UTIL
//STRIP001 /*?*/                    if (pObj->IsInserted()) {
//STRIP001 /*?*/                        DBG_ERROR("SdrMarkView::MarkPoints(const Rectangle* pRect): Markiertes Objekt nicht gefunden");
//STRIP001 /*?*/                    }
//STRIP001 /*?*/ #endif
//STRIP001 /*?*/                    pM=NULL;
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/            Point aPos(pHdl->GetPos());
//STRIP001 /*?*/            aPos+=pPV->GetOffset();
//STRIP001 /*?*/            if (pM!=NULL && (pRect==NULL || pRect->IsInside(aPos))) {
//STRIP001 /*?*/                if (bHideHdl && IsMarkHdlShown() && pHdl->GetObj()!=NULL) {
//STRIP001 /*?*/                    USHORT nAnz=pHdl->GetObj()->GetPlusHdlCount(*pHdl);
//STRIP001 /*?*/                    if (nAnz!=0) HideMarkHdl(NULL); // #36987#
//STRIP001 /*?*/                }
//STRIP001 /*?*/                if (ImpMarkPoint(pHdl,pM,bUnmark)) bChgd=TRUE;
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
/*N*/   }
/*N*/   if (pM!=NULL) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001  // Den zuletzt geaenderten MarkEntry ggf. noch aufraeumen
//STRIP001 /*?*/        SdrUShortCont* pPts=pM->GetMarkedPoints();
//STRIP001 /*?*/        if (pPts!=NULL) pPts->ForceSort();
/*N*/   }
/*N*/   if (bHideHdl) ShowMarkHdl(NULL); // #36987#
/*N*/   if (bChgd) {
/*?*/       MarkListHasChanged();
/*N*/   }

    // #90239# refresh IAOs
    // added this call again to make visible (un)marking of point(s)
//STRIP012/*N*/     if(bChgd)
//STRIP012/*?*/         RefreshAllIAOManagers();
/*N*/
/*N*/   return bChgd;
/*N*/ }

//STRIP001 BOOL SdrMarkView::MarkNextPoint(BOOL bPrev)
//STRIP001 {
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  BOOL bChgd=FALSE;
//STRIP001  aMark.ForceSort();
//STRIP001  // ...
//STRIP001  if (bChgd) {
//STRIP001      MarkListHasChanged();
//STRIP001  }
//STRIP001  return bChgd;
//STRIP001 }

//STRIP001 BOOL SdrMarkView::MarkNextPoint(const Point& rPnt, BOOL bPrev)
//STRIP001 {
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  BOOL bChgd=FALSE;
//STRIP001  aMark.ForceSort();
//STRIP001  // ...
//STRIP001  if (bChgd) {
//STRIP001      MarkListHasChanged();
//STRIP001  }
//STRIP001  return bChgd;
//STRIP001 }

//STRIP001 const Rectangle& SdrMarkView::GetMarkedPointsRect() const
//STRIP001 {
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  if (bMarkedPointsRectsDirty) ImpSetPointsRects();
//STRIP001  return aMarkedPointsRect;
//STRIP001 }

/*N*/ void SdrMarkView::SetPlusHandlesAlwaysVisible(BOOL bOn)
/*N*/ { // HandlePaint optimieren !!!!!!!
/*N*/   ForceUndirtyMrkPnt();
/*N*/   if (bOn!=bPlusHdlAlways) {
/*?*/       BOOL bVis=IsMarkHdlShown();
/*?*/       if (bVis) HideMarkHdl(NULL);
/*?*/       bPlusHdlAlways=bOn;
/*?*/       SetMarkHandles();
/*?*/       if (bVis) ShowMarkHdl(NULL);
/*?*/       MarkListHasChanged();
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// ImpSetPointsRects() ist fuer PolyPoints und GluePoints!
////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrMarkView::ImpSetPointsRects() const
//STRIP001 {
//STRIP001  Rectangle aPnts;
//STRIP001  Rectangle aGlue;
//STRIP001  ULONG nHdlAnz=aHdl.GetHdlCount();
//STRIP001  for (ULONG nHdlNum=0; nHdlNum<nHdlAnz; nHdlNum++) {
//STRIP001      const SdrHdl* pHdl=aHdl.GetHdl(nHdlNum);
//STRIP001      SdrHdlKind eKind=pHdl->GetKind();
//STRIP001      if ((eKind==HDL_POLY && pHdl->IsSelected()) || eKind==HDL_GLUE) {
//STRIP001          Point aPt(pHdl->GetPos());
//STRIP001          const SdrPageView* pPV=pHdl->GetPageView();
//STRIP001          if (pPV!=NULL) aPt+=pPV->GetOffset();
//STRIP001          Rectangle& rR=eKind==HDL_GLUE ? aGlue : aPnts;
//STRIP001          if (rR.IsEmpty()) {
//STRIP001              rR=Rectangle(aPt,aPt);
//STRIP001          } else {
//STRIP001              if (aPt.X()<rR.Left  ()) rR.Left  ()=aPt.X();
//STRIP001              if (aPt.X()>rR.Right ()) rR.Right ()=aPt.X();
//STRIP001              if (aPt.Y()<rR.Top   ()) rR.Top   ()=aPt.Y();
//STRIP001              if (aPt.Y()>rR.Bottom()) rR.Bottom()=aPt.Y();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  ((SdrMarkView*)this)->aMarkedPointsRect=aPnts;
//STRIP001  ((SdrMarkView*)this)->aMarkedGluePointsRect=aGlue;
//STRIP001  ((SdrMarkView*)this)->bMarkedPointsRectsDirty=FALSE;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////
// UndirtyMrkPnt() ist fuer PolyPoints und GluePoints!
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrMarkView::UndirtyMrkPnt() const
/*N*/ {
/*N*/   BOOL bChg=FALSE;
/*N*/   ULONG nMarkAnz=aMark.GetMarkCount();
/*N*/   for (ULONG nMarkNum=0; nMarkNum<nMarkAnz; nMarkNum++) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        SdrMark* pM=aMark.GetMark(nMarkNum);
//STRIP001 /*?*/        const SdrObject* pObj=pM->GetObj();
//STRIP001 /*?*/        // PolyPoints
//STRIP001 /*?*/        SdrUShortCont* pPts=pM->GetMarkedPoints();
//STRIP001 /*?*/        if (pPts!=NULL) {
//STRIP001 /*?*/            if (pObj->IsPolyObj()) {
//STRIP001 /*?*/                // Ungueltig markierte Punkte entfernen, also alle
//STRIP001 /*?*/                // Eintraege die groesser sind als die Punktanzahl des Objekts
//STRIP001 /*?*/                USHORT nMax=pObj->GetPointCount();
//STRIP001 /*?*/                USHORT nPtNum=0xFFFF;
//STRIP001 /*?*/                pPts->ForceSort();
//STRIP001 /*?*/                for (ULONG nIndex=pPts->GetCount(); nIndex>0 && nPtNum>=nMax;) {
//STRIP001 /*?*/                    nIndex--;
//STRIP001 /*?*/                    nPtNum=pPts->GetObject(nIndex);
//STRIP001 /*?*/                    if (nPtNum>=nMax) {
//STRIP001 /*?*/                        pPts->Remove(nIndex);
//STRIP001 /*?*/                        bChg=TRUE;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/            } else {
//STRIP001 /*?*/                DBG_ERROR("SdrMarkView::UndirtyMrkPnt(): Markierte Punkte an einem Objekt, dass kein PolyObj ist!");
//STRIP001 /*?*/                if (pPts!=NULL && pPts->GetCount()!=0) {
//STRIP001 /*?*/                    pPts->Clear();
//STRIP001 /*?*/                    bChg=TRUE;
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
//STRIP001 /*?*/        // GluePoints
//STRIP001 /*?*/        pPts=pM->GetMarkedGluePoints();
//STRIP001 /*?*/        const SdrGluePointList* pGPL=pObj->GetGluePointList();
//STRIP001 /*?*/        if (pPts!=NULL) {
//STRIP001 /*?*/            if (pGPL!=NULL) {
//STRIP001 /*?*/                // Ungueltig markierte Klebepunkte entfernen, also alle
//STRIP001 /*?*/                // Eintraege (Id's) die nicht in der GluePointList des
//STRIP001 /*?*/                // Objekts enthalten sind
//STRIP001 /*?*/                pPts->ForceSort();
//STRIP001 /*?*/                for (ULONG nIndex=pPts->GetCount(); nIndex>0;) {
//STRIP001 /*?*/                    nIndex--;
//STRIP001 /*?*/                    USHORT nId=pPts->GetObject(nIndex);
//STRIP001 /*?*/                    if (pGPL->FindGluePoint(nId)==SDRGLUEPOINT_NOTFOUND) {
//STRIP001 /*?*/                        pPts->Remove(nIndex);
//STRIP001 /*?*/                        bChg=TRUE;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/            } else {
//STRIP001 /*?*/                if (pPts!=NULL && pPts->GetCount()!=0) {
//STRIP001 /*?*/                    pPts->Clear(); // Objekt hat keine Klebepunkte (mehr)
//STRIP001 /*?*/                    bChg=TRUE;
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
/*N*/   }
/*N*/   if (bChg) ((SdrMarkView*)this)->bMarkedPointsRectsDirty=TRUE;
/*N*/   ((SdrMarkView*)this)->bMrkPntDirty=FALSE;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 BOOL SdrMarkView::HasMarkableGluePoints() const
//STRIP001 {
//STRIP001  BOOL bRet=FALSE;
//STRIP001  if (IsGluePointEditMode()) {
//STRIP001      ForceUndirtyMrkPnt();
//STRIP001      ULONG nMarkAnz=aMark.GetMarkCount();
//STRIP001      for (ULONG nMarkNum=0; nMarkNum<nMarkAnz && !bRet; nMarkNum++) {
//STRIP001          const SdrMark* pM=aMark.GetMark(nMarkNum);
//STRIP001          const SdrObject* pObj=pM->GetObj();
//STRIP001          const SdrGluePointList* pGPL=pObj->GetGluePointList();
//STRIP001          bRet=pGPL!=NULL && pGPL->GetCount()!=0;
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 ULONG SdrMarkView::GetMarkableGluePointCount() const
//STRIP001 {
//STRIP001  ULONG nAnz=0;
//STRIP001  if (IsGluePointEditMode()) {
//STRIP001      ForceUndirtyMrkPnt();
//STRIP001      ULONG nMarkAnz=aMark.GetMarkCount();
//STRIP001      for (ULONG nMarkNum=0; nMarkNum<nMarkAnz; nMarkNum++) {
//STRIP001          const SdrMark* pM=aMark.GetMark(nMarkNum);
//STRIP001          const SdrObject* pObj=pM->GetObj();
//STRIP001          const SdrGluePointList* pGPL=pObj->GetGluePointList();
//STRIP001          if (pGPL!=NULL) {
//STRIP001              nAnz+=pGPL->GetCount();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return nAnz;
//STRIP001 }

/*N*/ BOOL SdrMarkView::HasMarkedGluePoints() const
/*N*/ {
/*N*/   ForceUndirtyMrkPnt();
/*N*/   BOOL bRet=FALSE;
/*N*/   ULONG nMarkAnz=aMark.GetMarkCount();
/*N*/   for (ULONG nMarkNum=0; nMarkNum<nMarkAnz && !bRet; nMarkNum++) {
/*?*/       const SdrMark* pM=aMark.GetMark(nMarkNum);
/*?*/       const SdrUShortCont* pPts=pM->GetMarkedGluePoints();
/*?*/       bRet=pPts!=NULL && pPts->GetCount()!=0;
/*N*/   }
/*N*/   return bRet;
/*N*/ }

//STRIP001 ULONG SdrMarkView::GetMarkedGluePointCount() const
//STRIP001 {
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  ULONG nAnz=0;
//STRIP001  ULONG nMarkAnz=aMark.GetMarkCount();
//STRIP001  for (ULONG nMarkNum=0; nMarkNum<nMarkAnz; nMarkNum++) {
//STRIP001      const SdrMark* pM=aMark.GetMark(nMarkNum);
//STRIP001      const SdrUShortCont* pPts=pM->GetMarkedGluePoints();
//STRIP001      if (pPts!=NULL) nAnz+=pPts->GetCount();
//STRIP001  }
//STRIP001  return nAnz;
//STRIP001 }

/*N*/ BOOL SdrMarkView::MarkGluePoints(const Rectangle* pRect, BOOL bUnmark)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  if (!IsGluePointEditMode() && !bUnmark) return FALSE;
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  BOOL bChgd=FALSE;
//STRIP001  aMark.ForceSort();
//STRIP001  ULONG nMarkAnz=aMark.GetMarkCount();
//STRIP001  for (ULONG nMarkNum=0; nMarkNum<nMarkAnz; nMarkNum++) {
//STRIP001      SdrMark* pM=aMark.GetMark(nMarkNum);
//STRIP001      const SdrObject* pObj=pM->GetObj();
//STRIP001      const SdrPageView* pPV=pM->GetPageView();
//STRIP001      const SdrGluePointList* pGPL=pObj->GetGluePointList();
//STRIP001      SdrUShortCont* pPts=pM->GetMarkedGluePoints();
//STRIP001      if (bUnmark && pRect==NULL) { // UnmarkAll
//STRIP001          if (pPts!=NULL && pPts->GetCount()!=0) {
//STRIP001              pPts->Clear();
//STRIP001              bChgd=TRUE;
//STRIP001          }
//STRIP001      } else {
//STRIP001          if (pGPL!=NULL && (pPts!=NULL || !bUnmark)) {
//STRIP001              USHORT nGPAnz=pGPL->GetCount();
//STRIP001              for (USHORT nGPNum=0; nGPNum<nGPAnz; nGPNum++) {
//STRIP001                  const SdrGluePoint& rGP=(*pGPL)[nGPNum];
//STRIP001                  Point aPos(rGP.GetAbsolutePos(*pObj));
//STRIP001                  aPos+=pPV->GetOffset();
//STRIP001                  if (pRect==NULL || pRect->IsInside(aPos)) {
//STRIP001                      if (pPts==NULL) pPts=pM->ForceMarkedGluePoints();
//STRIP001                      else pPts->ForceSort();
//STRIP001                      ULONG nPos=pPts->GetPos(rGP.GetId());
//STRIP001                      if (!bUnmark && nPos==CONTAINER_ENTRY_NOTFOUND) {
//STRIP001                          bChgd=TRUE;
//STRIP001                          pPts->Insert(rGP.GetId());
//STRIP001                      }
//STRIP001                      if (bUnmark && nPos!=CONTAINER_ENTRY_NOTFOUND) {
//STRIP001                          bChgd=TRUE;
//STRIP001                          pPts->Remove(nPos);
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if (bChgd) {
//STRIP001      AdjustMarkHdl();
//STRIP001      MarkListHasChanged();
//STRIP001  }
//STRIP001  return bChgd;
/*N*/ }

/*N*/ BOOL SdrMarkView::PickGluePoint(const Point& rPnt, SdrObject*& rpObj, USHORT& rnId, SdrPageView*& rpPV, ULONG nOptions) const
/*N*/ {
/*N*/   SdrObject* pObj0=rpObj;
/*N*/   SdrPageView* pPV0=rpPV;
/*N*/   USHORT nId0=rnId;
/*N*/   rpObj=NULL; rpPV=NULL; rnId=0;
/*N*/   if (!IsGluePointEditMode()) return FALSE;
/*N*/   BOOL bBack=(nOptions & SDRSEARCH_BACKWARD) !=0;
/*N*/   BOOL bNext=(nOptions & SDRSEARCH_NEXT) !=0;
/*N*/   const OutputDevice* pOut=(const OutputDevice*)pActualOutDev;
/*N*/   if (pOut==NULL) const OutputDevice* pOut=GetWin(0);
/*N*/   if (pOut==NULL) return FALSE;
/*N*/   ((SdrMarkView*)this)->aMark.ForceSort();
/*N*/   ULONG nMarkAnz=aMark.GetMarkCount();
/*N*/   ULONG nMarkNum=bBack ? 0 : nMarkAnz;
/*N*/   if (bNext) {
/*N*/       nMarkNum=((SdrMarkView*)this)->aMark.FindObject(pObj0);
/*N*/       if (nMarkNum==CONTAINER_ENTRY_NOTFOUND) return FALSE;
/*N*/       if (!bBack) nMarkNum++;
/*N*/   }
/*N*/   while (bBack ? nMarkNum<nMarkAnz : nMarkNum>0) {
/*N*/       if (!bBack) nMarkNum--;
/*N*/       const SdrMark* pM=aMark.GetMark(nMarkNum);
/*N*/       SdrObject* pObj=pM->GetObj();
/*N*/       SdrPageView* pPV=pM->GetPageView();
/*N*/       const SdrGluePointList* pGPL=pObj->GetGluePointList();
/*N*/       if (pGPL!=NULL) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            Point aPnt(rPnt);
//STRIP001 /*?*/            aPnt-=pPV->GetOffset();
//STRIP001 /*?*/            USHORT nNum=pGPL->HitTest(aPnt,*pOut,pObj,bBack,bNext,nId0);
//STRIP001 /*?*/            if (nNum!=SDRGLUEPOINT_NOTFOUND) {
//STRIP001 /*?*/                rpObj=pObj;
//STRIP001 /*?*/                rnId=(*pGPL)[nNum].GetId();
//STRIP001 /*?*/                rpPV=pPV;
//STRIP001 /*?*/                return TRUE;
//STRIP001 /*?*/            }
/*N*/       }
/*N*/       bNext=FALSE; // HitNextGluePoint nur beim ersten Obj
/*N*/       if (bBack) nMarkNum++;
/*N*/   }
/*N*/   return FALSE;
/*N*/ }

//STRIP001 BOOL SdrMarkView::MarkGluePoint(const SdrObject* pObj, USHORT nId, const SdrPageView* pPV, BOOL bUnmark)
//STRIP001 {
//STRIP001  if (!IsGluePointEditMode()) return FALSE;
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  BOOL bChgd=FALSE;
//STRIP001  if (pObj!=NULL) {
//STRIP001      ULONG nMarkPos=aMark.FindObject(pObj);
//STRIP001      if (nMarkPos!=CONTAINER_ENTRY_NOTFOUND) {
//STRIP001          SdrMark* pM=aMark.GetMark(nMarkPos);
//STRIP001          SdrUShortCont* pPts=bUnmark ? pM->GetMarkedGluePoints() : pM->ForceMarkedGluePoints();
//STRIP001          if (pPts!=NULL) {
//STRIP001              ULONG nPointPos=pPts->GetPos(nId);
//STRIP001              if (!bUnmark && nPointPos==CONTAINER_ENTRY_NOTFOUND) {
//STRIP001                  bChgd=TRUE;
//STRIP001                  pPts->Insert(nId);
//STRIP001              }
//STRIP001              if (bUnmark && nPointPos!=CONTAINER_ENTRY_NOTFOUND) {
//STRIP001                  bChgd=TRUE;
//STRIP001                  pPts->Remove(nPointPos);
//STRIP001              }
//STRIP001          }
//STRIP001      } else {
//STRIP001          // Objekt implizit markieren ...
//STRIP001          // ... fehlende Implementation
//STRIP001      }
//STRIP001  }
//STRIP001  if (bChgd) {
//STRIP001      AdjustMarkHdl();
//STRIP001      MarkListHasChanged();
//STRIP001  }
//STRIP001  return bChgd;
//STRIP001 }

//STRIP001 BOOL SdrMarkView::IsGluePointMarked(const SdrObject* pObj, USHORT nId) const
//STRIP001 {
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  BOOL bRet=FALSE;
//STRIP001  ULONG nPos=((SdrMarkView*)this)->aMark.FindObject(pObj); // casting auf NonConst
//STRIP001  if (nPos!=CONTAINER_ENTRY_NOTFOUND) {
//STRIP001      const SdrMark* pM=aMark.GetMark(nPos);
//STRIP001      const SdrUShortCont* pPts=pM->GetMarkedGluePoints();
//STRIP001      if (pPts!=NULL) {
//STRIP001          bRet=pPts->Exist(nId);
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SdrMarkView::UnmarkGluePoint(const SdrHdl& rHdl)
//STRIP001 {
//STRIP001  if (&rHdl!=NULL && rHdl.GetKind()==HDL_GLUE && rHdl.GetObj()!=NULL) {
//STRIP001      return MarkGluePoint(rHdl.GetObj(),rHdl.GetObjHdlNum(),rHdl.GetPageView(),TRUE);
//STRIP001  } else return FALSE;
//STRIP001 }

//STRIP001 SdrHdl* SdrMarkView::GetGluePointHdl(const SdrObject* pObj, USHORT nId) const
//STRIP001 {
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  ULONG nHdlAnz=aHdl.GetHdlCount();
//STRIP001  for (ULONG nHdlNum=0; nHdlNum<nHdlAnz; nHdlNum++) {
//STRIP001      SdrHdl* pHdl=aHdl.GetHdl(nHdlNum);
//STRIP001      if (pHdl->GetObj()==pObj &&
//STRIP001          pHdl->GetKind()==HDL_GLUE &&
//STRIP001          pHdl->GetObjHdlNum()==nId ) return pHdl;
//STRIP001  }
//STRIP001  return NULL;
//STRIP001 }

//STRIP001 BOOL SdrMarkView::MarkNextGluePoint(BOOL bPrev)
//STRIP001 {
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  BOOL bChgd=FALSE;
//STRIP001  aMark.ForceSort();
//STRIP001  // ...
//STRIP001  if (bChgd) {
//STRIP001      MarkListHasChanged();
//STRIP001  }
//STRIP001  return bChgd;
//STRIP001 }

//STRIP001 BOOL SdrMarkView::MarkNextGluePoint(const Point& rPnt, BOOL bPrev)
//STRIP001 {
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  BOOL bChgd=FALSE;
//STRIP001  aMark.ForceSort();
//STRIP001  // ...
//STRIP001  if (bChgd) {
//STRIP001      MarkListHasChanged();
//STRIP001  }
//STRIP001  return bChgd;
//STRIP001 }

//STRIP001 const Rectangle& SdrMarkView::GetMarkedGluePointsRect() const
//STRIP001 {
//STRIP001  ForceUndirtyMrkPnt();
//STRIP001  if (bMarkedPointsRectsDirty) ImpSetPointsRects();
//STRIP001  return aMarkedGluePointsRect;
//STRIP001 }

}
