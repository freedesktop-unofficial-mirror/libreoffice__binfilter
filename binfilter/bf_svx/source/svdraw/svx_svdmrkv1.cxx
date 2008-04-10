/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: svx_svdmrkv1.cxx,v $
 * $Revision: 1.8 $
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#include "svdmrkv.hxx"
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
/*N*/   }
/*N*/   if (pM!=NULL) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001  // Den zuletzt geaenderten MarkEntry ggf. noch aufraeumen
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


////////////////////////////////////////////////////////////////////////////////////////////////////
// UndirtyMrkPnt() ist fuer PolyPoints und GluePoints!
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrMarkView::UndirtyMrkPnt() const
/*N*/ {
/*N*/   BOOL bChg=FALSE;
/*N*/   ULONG nMarkAnz=aMark.GetMarkCount();
/*N*/   for (ULONG nMarkNum=0; nMarkNum<nMarkAnz; nMarkNum++) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   }
/*N*/   if (bChg) ((SdrMarkView*)this)->bMarkedPointsRectsDirty=TRUE;
/*N*/   ((SdrMarkView*)this)->bMrkPntDirty=FALSE;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////



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


/*N*/ BOOL SdrMarkView::MarkGluePoints(const Rectangle* pRect, BOOL bUnmark)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
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
/*N*/       }
/*N*/       bNext=FALSE; // HitNextGluePoint nur beim ersten Obj
/*N*/       if (bBack) nMarkNum++;
/*N*/   }
/*N*/   return FALSE;
/*N*/ }








}
