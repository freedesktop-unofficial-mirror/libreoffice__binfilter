/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_svdmrkv.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 17:31:56 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#include "svdview.hxx"
#include "svdpagv.hxx"
#include "svdio.hxx"
#include "svdoole2.hxx"


#include "svdstr.hrc"

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



////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ BOOL SdrMarkView::IsAction() const
/*N*/ {
/*N*/   return SdrSnapView::IsAction() || bMarking || bMarkingPoints || bMarkingGluePoints;
/*N*/ }




/*N*/ void SdrMarkView::BrkAction()
/*N*/ {
/*N*/   SdrSnapView::BrkAction();
/*N*/   BrkMarkObj();
/*N*/   BrkMarkPoints();
/*N*/   BrkMarkGluePoints();
/*N*/ }


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


////////////////////////////////////////////////////////////////////////////////////////////////////





/*N*/ void SdrMarkView::BrkMarkObj()
/*N*/ {
/*N*/   if (bMarking) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////





/*N*/ void SdrMarkView::BrkMarkPoints()
/*N*/ {
/*N*/   if (bMarkingPoints) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////





/*N*/ void SdrMarkView::BrkMarkGluePoints()
/*N*/ {
/*N*/   if (bMarkingGluePoints) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////



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
/*N*/ }

/*N*/ BOOL SdrMarkView::ImpIsFrameHandles() const
/*N*/ {
/*N*/   ULONG nMarkAnz=aMark.GetMarkCount();
/*N*/   BOOL bFrmHdl=nMarkAnz>nFrameHandlesLimit || bForceFrameHandles;
/*N*/   BOOL bStdDrag=eDragMode==SDRDRAG_MOVE;
/*N*/   if (nMarkAnz==1 && bStdDrag && bFrmHdl) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
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
/*N*/       }
/*N*/   } else {
/*N*/       for (ULONG nMarkNum=0; nMarkNum<nMarkAnz; nMarkNum++) {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 const SdrMark* pM=aMark.GetMark(nMarkNum);
/*N*/       } // for nMarkNum
/*N*/   } // if bFrmHdl else
/*N*/   // GluePoint-Handles
/*N*/   for (ULONG nMarkNum=0; nMarkNum<nMarkAnz; nMarkNum++) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
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
/*N*/   }
/*N*/ }

/*N*/ void SdrMarkView::AddCustomHdl()
/*N*/ {
/*N*/   // add custom handles (used by other apps, e.g. AnchorPos)
/*N*/ }

/*N*/ void SdrMarkView::SetDragMode(SdrDragMode eMode)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
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
/*?*/
/*?*/           break;
/*?*/       }
/*?*/       case SDRDRAG_MIRROR:
/*?*/       {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/
/*?*/           break;
/*?*/       }
/*?*/       case SDRDRAG_TRANSPARENCE:
/*?*/       {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/           break;
/*?*/       }
/*?*/       case SDRDRAG_GRADIENT:
/*?*/       {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/           break;
/*N*/       }
/*N*/   }
/*N*/ }




/*N*/ void SdrMarkView::CheckMarked()
/*N*/ {
/*N*/   for (ULONG nm=aMark.GetMarkCount(); nm>0;) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
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





/*N*/ void SdrMarkView::MarkObj(SdrObject* pObj, SdrPageView* pPV, BOOL bUnmark, BOOL bImpNoSetMarkHdl)
/*N*/ {
/*N*/   if (pObj!=NULL && pPV!=NULL && IsObjMarkable(pObj, pPV)) {
/*N*/       BrkAction();
/*N*/       if (!bUnmark) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/       } else {
/*N*/           ULONG nPos=aMark.FindObject(pObj);
/*N*/           if (nPos!=CONTAINER_ENTRY_NOTFOUND) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
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
/*N*/       }
/*N*/       if (pObj!=NULL && (nOptions & SDRSEARCH_TESTMACRO) !=0) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/       }
/*N*/       if (pObj!=NULL && (nOptions & SDRSEARCH_WITHTEXT) !=0 && pObj->GetOutlinerParaObject()==NULL) pObj=NULL;
/*N*/       if (pObj!=NULL && (nOptions & SDRSEARCH_TESTTEXTAREA) !=0) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/       }
/*N*/       if (pObj!=NULL) {
/*N*/           rpObj=pObj;
/*N*/           rpPV=pPV;
/*N*/           if (pnPassNum!=NULL) *pnPassNum|=SDRSEARCHPASS_DIRECT;
/*N*/       }
/*N*/   }
/*N*/   return rpObj!=NULL;
/*N*/ }



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



////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////

// #i13033#
// Helper method for building the transitive hull of all selected
// objects


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
