/*************************************************************************
 *
 *  $RCSfile: svx_svdedtv.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:18 $
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

#include <vcl/metaact.hxx>
#include "svdedtv.hxx"
#include "svdxout.hxx"
#include "svdundo.hxx"
#include "svdograf.hxx"  // fuer Possibilities
#include "svdopath.hxx"
#include "svdoole2.hxx"
#include "svdopage.hxx"
#include "svdoedge.hxx"
#include "svdlayer.hxx"
#include "svdpagv.hxx"
#include "svdpage.hxx"
#include "svdpoev.hxx"  // fuer die PolyPossiblities
#include "svdstr.hrc"   // Namen aus der Resource
#include "svdglob.hxx"  // StringCache

// #i13033#
#ifndef _CLONELIST_HXX_
#include <clonelist.hxx>
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@@@@ @@@@@  @@ @@@@@@  @@ @@ @@ @@@@@ @@   @@
//  @@    @@  @@ @@   @@    @@ @@ @@ @@    @@   @@
//  @@    @@  @@ @@   @@    @@ @@ @@ @@    @@ @ @@
//  @@@@  @@  @@ @@   @@    @@@@@ @@ @@@@  @@@@@@@
//  @@    @@  @@ @@   @@     @@@  @@ @@    @@@@@@@
//  @@    @@  @@ @@   @@     @@@  @@ @@    @@@ @@@
//  @@@@@ @@@@@  @@   @@      @   @@ @@@@@ @@   @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrEditView::ImpResetPossibilityFlags()
/*N*/ {
/*N*/   bReadOnly               =FALSE;
/*N*/
/*N*/   bGroupPossible          =FALSE;
/*N*/   bUnGroupPossible        =FALSE;
/*N*/   bGrpEnterPossible       =FALSE;
/*N*/   bDeletePossible         =FALSE;
/*N*/   bToTopPossible          =FALSE;
/*N*/   bToBtmPossible          =FALSE;
/*N*/   bReverseOrderPossible   =FALSE;
/*N*/
/*N*/   bImportMtfPossible      =FALSE;
/*N*/   bCombinePossible        =FALSE;
/*N*/   bDismantlePossible      =FALSE;
/*N*/   bCombineNoPolyPolyPossible =FALSE;
/*N*/   bDismantleMakeLinesPossible=FALSE;
/*N*/   bOrthoDesiredOnMarked   =FALSE;
/*N*/
/*N*/   bMoreThanOneNotMovable  =FALSE;
/*N*/   bOneOrMoreMovable       =FALSE;
/*N*/   bMoreThanOneNoMovRot    =FALSE;
/*N*/   bContortionPossible     =FALSE;
/*N*/   bAllPolys               =FALSE;
/*N*/   bOneOrMorePolys         =FALSE;
/*N*/   bMoveAllowed            =FALSE;
/*N*/   bResizeFreeAllowed      =FALSE;
/*N*/   bResizePropAllowed      =FALSE;
/*N*/   bRotateFreeAllowed      =FALSE;
/*N*/   bRotate90Allowed        =FALSE;
/*N*/   bMirrorFreeAllowed      =FALSE;
/*N*/   bMirror45Allowed        =FALSE;
/*N*/   bMirror90Allowed        =FALSE;
/*N*/   bTransparenceAllowed    =FALSE;
/*N*/   bGradientAllowed        =FALSE;
/*N*/   bShearAllowed           =FALSE;
/*N*/   bEdgeRadiusAllowed      =FALSE;
/*N*/   bCanConvToPath          =FALSE;
/*N*/   bCanConvToPoly          =FALSE;
/*N*/   bCanConvToContour       =FALSE;
/*N*/   bCanConvToPathLineToArea=FALSE;
/*N*/   bCanConvToPolyLineToArea=FALSE;
/*N*/   bMoveProtect            =FALSE;
/*N*/   bResizeProtect          =FALSE;
/*N*/ }

/*N*/ void SdrEditView::ImpClearVars()
/*N*/ {
/*N*/   ImpResetPossibilityFlags();
/*N*/   bPossibilitiesDirty=TRUE;   // << war von Purify angemeckert
/*N*/   bCombineError=FALSE;
/*N*/   bBundleVirtObj=FALSE;
/*N*/ }

/*N*/ SdrEditView::SdrEditView(SdrModel* pModel1, OutputDevice* pOut):
/*N*/   SdrMarkView(pModel1,pOut)
/*N*/ {
/*N*/   ImpClearVars();
/*N*/ }

/*?*/ SdrEditView::SdrEditView(SdrModel* pModel1, ExtOutputDevice* pXOut):
/*?*/   SdrMarkView(pModel1,pXOut)
/*?*/ {
/*?*/   ImpClearVars();
/*?*/ }

/*N*/ SdrEditView::~SdrEditView()
/*N*/ {
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 SdrLayer* SdrEditView::InsertNewLayer(const XubString& rName, USHORT nPos)
//STRIP001 {
//STRIP001  SdrLayerAdmin& rLA=pMod->GetLayerAdmin();
//STRIP001  USHORT nMax=rLA.GetLayerCount();
//STRIP001  if (nPos>nMax) nPos=nMax;
//STRIP001  SdrLayer* pNewLayer=rLA.NewLayer(rName,nPos);
//STRIP001  AddUndo(new SdrUndoNewLayer(nPos,rLA,*pMod));
//STRIP001  pMod->SetChanged();
//STRIP001  return pNewLayer;
//STRIP001 }

#include "svdogrp.hxx"
#include "scene3d.hxx"

//STRIP001 BOOL SdrEditView::ImpDelLayerCheck(SdrObjList* pOL, SdrLayerID nDelID) const
//STRIP001 {
//STRIP001  sal_Bool bDelAll(sal_True);
//STRIP001  sal_uInt32 nObjAnz(pOL->GetObjCount());
//STRIP001
//STRIP001  for(sal_uInt32 nObjNum(nObjAnz); nObjNum > 0 && bDelAll;)
//STRIP001  {
//STRIP001      nObjNum--;
//STRIP001      SdrObject* pObj = pOL->GetObj(nObjNum);
//STRIP001      SdrObjList* pSubOL = pObj->GetSubList();
//STRIP001
//STRIP001      // #104809# Test explicitely for group objects and 3d scenes
//STRIP001      if(pSubOL && (pObj->ISA(SdrObjGroup) || pObj->ISA(E3dScene)))
//STRIP001      {
//STRIP001          if(!ImpDelLayerCheck(pSubOL, nDelID))
//STRIP001          {
//STRIP001              // Rekursion
//STRIP001              bDelAll = sal_False;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if(pObj->GetLayer() != nDelID)
//STRIP001          {
//STRIP001              bDelAll = sal_False;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return bDelAll;
//STRIP001 }

//STRIP001 void SdrEditView::ImpDelLayerDelObjs(SdrObjList* pOL, SdrLayerID nDelID)
//STRIP001 {
//STRIP001  sal_uInt32 nObjAnz(pOL->GetObjCount());
//STRIP001  // make sure OrdNums are correct
//STRIP001  pOL->GetObj(0)->GetOrdNum();
//STRIP001
//STRIP001  for(sal_uInt32 nObjNum(nObjAnz); nObjNum > 0;)
//STRIP001  {
//STRIP001      nObjNum--;
//STRIP001      SdrObject* pObj = pOL->GetObj(nObjNum);
//STRIP001      SdrObjList* pSubOL = pObj->GetSubList();
//STRIP001
//STRIP001      // #104809# Test explicitely for group objects and 3d scenes
//STRIP001      if(pSubOL && (pObj->ISA(SdrObjGroup) || pObj->ISA(E3dScene)))
//STRIP001      {
//STRIP001          if(ImpDelLayerCheck(pSubOL, nDelID))
//STRIP001          {
//STRIP001              AddUndo(new SdrUndoDelObj(*pObj, TRUE));
//STRIP001              pOL->RemoveObject(nObjNum);
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              ImpDelLayerDelObjs(pSubOL, nDelID);
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if(pObj->GetLayer() == nDelID)
//STRIP001          {
//STRIP001              AddUndo(new SdrUndoDelObj(*pObj, TRUE));
//STRIP001              pOL->RemoveObject(nObjNum);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*N*/ void SdrEditView::DeleteLayer(const XubString& rName)
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  SdrLayerAdmin& rLA = pMod->GetLayerAdmin();
//STRIP001  SdrLayer* pLayer = rLA.GetLayer(rName, TRUE);
//STRIP001  sal_uInt16 nLayerNum(rLA.GetLayerPos(pLayer));
//STRIP001
//STRIP001  if(SDRLAYER_NOTFOUND != nLayerNum)
//STRIP001  {
//STRIP001      SdrLayerID nDelID = pLayer->GetID();
//STRIP001      BegUndo(ImpGetResStr(STR_UndoDelLayer));
//STRIP001      sal_Bool bMaPg(sal_True);
//STRIP001
//STRIP001      for(sal_uInt16 nPageKind(0); nPageKind < 2; nPageKind++)
//STRIP001      {
//STRIP001          // MasterPages and DrawPages
//STRIP001          sal_uInt16 nPgAnz(bMaPg ? pMod->GetMasterPageCount() : pMod->GetPageCount());
//STRIP001
//STRIP001          for(sal_uInt16 nPgNum(0); nPgNum < nPgAnz; nPgNum++)
//STRIP001          {
//STRIP001              // over all pages
//STRIP001              SdrPage* pPage = (bMaPg) ? pMod->GetMasterPage(nPgNum) : pMod->GetPage(nPgNum);
//STRIP001              sal_uInt32 nObjAnz(pPage->GetObjCount());
//STRIP001
//STRIP001              // make sure OrdNums are correct
//STRIP001              if(nObjAnz)
//STRIP001                  pPage->GetObj(0)->GetOrdNum();
//STRIP001
//STRIP001              for(sal_uInt32 nObjNum(nObjAnz); nObjNum > 0;)
//STRIP001              {
//STRIP001                  nObjNum--;
//STRIP001                  SdrObject* pObj = pPage->GetObj(nObjNum);
//STRIP001                  SdrObjList* pSubOL = pObj->GetSubList();
//STRIP001
//STRIP001                  // #104809# Test explicitely for group objects and 3d scenes
//STRIP001                  if(pSubOL && (pObj->ISA(SdrObjGroup) || pObj->ISA(E3dScene)))
//STRIP001                  {
//STRIP001                      if(ImpDelLayerCheck(pSubOL, nDelID))
//STRIP001                      {
//STRIP001                          AddUndo(new SdrUndoDelObj(*pObj, TRUE));
//STRIP001                          pPage->RemoveObject(nObjNum);
//STRIP001                      }
//STRIP001                      else
//STRIP001                      {
//STRIP001                          ImpDelLayerDelObjs(pSubOL, nDelID);
//STRIP001                      }
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      if(pObj->GetLayer() == nDelID)
//STRIP001                      {
//STRIP001                          AddUndo(new SdrUndoDelObj(*pObj, TRUE));
//STRIP001                          pPage->RemoveObject(nObjNum);
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          bMaPg = sal_False;
//STRIP001      }
//STRIP001
//STRIP001      AddUndo(new SdrUndoDelLayer(nLayerNum, rLA, *pMod));
//STRIP001      rLA.RemoveLayer(nLayerNum);
//STRIP001      EndUndo();
//STRIP001      pMod->SetChanged();
//STRIP001  }
/*N*/ }

//STRIP001 void SdrEditView::MoveLayer(const XubString& rName, USHORT nNewPos)
//STRIP001 {
//STRIP001  SdrLayerAdmin& rLA=pMod->GetLayerAdmin();
//STRIP001  SdrLayer* pLayer=rLA.GetLayer(rName,TRUE);
//STRIP001  USHORT nLayerNum=rLA.GetLayerPos(pLayer);
//STRIP001  if (nLayerNum!=SDRLAYER_NOTFOUND) {
//STRIP001      AddUndo(new SdrUndoMoveLayer(nLayerNum,rLA,*pMod,nNewPos));
//STRIP001      rLA.MoveLayer(nLayerNum,nNewPos);
//STRIP001      pMod->SetChanged();
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrEditView::EndUndo()
//STRIP001 {
//STRIP001  // #i13033#
//STRIP001  // Comparison changed to 1L since EndUndo() is called later now
//STRIP001  // and EndUndo WILL change count to count-1
//STRIP001  if(1L == pMod->GetUndoBracketLevel())
//STRIP001  {
//STRIP001      ImpBroadcastEdgesOfMarkedNodes();
//STRIP001  }
//STRIP001
//STRIP001  // #i13033#
//STRIP001  // moved to bottom to still have access to UNDOs inside of
//STRIP001  // ImpBroadcastEdgesOfMarkedNodes()
//STRIP001  pMod->EndUndo();
//STRIP001 }

//STRIP001 void SdrEditView::ImpBroadcastEdgesOfMarkedNodes()
//STRIP001 {
//STRIP001  ForceEdgesOfMarkedNodes();
//STRIP001
//STRIP001  // #i13033#
//STRIP001  // New mechanism to search for necessary disconnections for
//STRIP001  // changed connectors inside the transitive hull of all at
//STRIP001  // the beginning of UNDO selected objects
//STRIP001  for(sal_uInt32 a(0L); a < maAllMarkedObjects.Count(); a++)
//STRIP001  {
//STRIP001      SdrEdgeObj* pEdge = PTR_CAST(SdrEdgeObj, (SdrObject*)maAllMarkedObjects.GetObject(a));
//STRIP001
//STRIP001      if(pEdge)
//STRIP001      {
//STRIP001          SdrObject* pObj1 = pEdge->GetConnectedNode(sal_False);
//STRIP001          SdrObject* pObj2 = pEdge->GetConnectedNode(sal_True);
//STRIP001
//STRIP001          if(pObj1
//STRIP001              && LIST_ENTRY_NOTFOUND == maAllMarkedObjects.GetPos(pObj1)
//STRIP001              && !pEdge->CheckNodeConnection(sal_False))
//STRIP001          {
//STRIP001              AddUndo(new SdrUndoGeoObj(*pEdge));
//STRIP001              pEdge->DisconnectFromNode(sal_False);
//STRIP001          }
//STRIP001
//STRIP001          if(pObj2
//STRIP001              && LIST_ENTRY_NOTFOUND == maAllMarkedObjects.GetPos(pObj2)
//STRIP001              && !pEdge->CheckNodeConnection(sal_True))
//STRIP001          {
//STRIP001              AddUndo(new SdrUndoGeoObj(*pEdge));
//STRIP001              pEdge->DisconnectFromNode(sal_True);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  ULONG nMarkedEdgeAnz=aMarkedEdgesOfMarkedNodes.GetMarkCount();
//STRIP001  USHORT i;
//STRIP001
//STRIP001  for (i=0; i<nMarkedEdgeAnz; i++) {
//STRIP001      SdrMark* pEM=aMarkedEdgesOfMarkedNodes.GetMark(i);
//STRIP001      SdrObject* pEdgeTmp=pEM->GetObj();
//STRIP001      SdrEdgeObj* pEdge=PTR_CAST(SdrEdgeObj,pEdgeTmp);
//STRIP001      if (pEdge!=NULL) {
//STRIP001          pEdge->SetEdgeTrackDirty();
//STRIP001      }
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  ####   ###   ####  #### # ####  # #    # ##### # #####  ####
//  #   # #   # #     #     # #   # # #    #   #   # #     #
//  ####  #   #  ###   ###  # ####  # #    #   #   # ####   ###
//  #     #   #     #     # # #   # # #    #   #   # #         #
//  #      ###  ####  ####  # ####  # #### #   #   # ##### ####
//
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrEditView::MarkListHasChanged()
/*N*/ {
/*N*/   SdrMarkView::MarkListHasChanged();
/*N*/   bPossibilitiesDirty=TRUE;
/*N*/ }

/*N*/ void SdrEditView::ModelHasChanged()
/*N*/ {
/*N*/   SdrMarkView::ModelHasChanged();
/*N*/   bPossibilitiesDirty=TRUE;
/*N*/ }

//STRIP001 BOOL SdrEditView::IsResizeAllowed(BOOL bProp) const
//STRIP001 {
//STRIP001  ForcePossibilities();
//STRIP001  if (bResizeProtect) return FALSE;
//STRIP001  if (bProp) return bResizePropAllowed;
//STRIP001  return bResizeFreeAllowed;
//STRIP001 }

//STRIP001 BOOL SdrEditView::IsRotateAllowed(BOOL b90Deg) const
//STRIP001 {
//STRIP001  ForcePossibilities();
//STRIP001  if (bMoveProtect) return FALSE;
//STRIP001  if (b90Deg) return bRotate90Allowed;
//STRIP001  return bRotateFreeAllowed;
//STRIP001 }

/*N*/ BOOL SdrEditView::IsMirrorAllowed(BOOL b45Deg, BOOL b90Deg) const
/*N*/ {
/*N*/   ForcePossibilities();
/*N*/   if (bMoveProtect) return FALSE;
/*N*/   if (b90Deg) return bMirror90Allowed;
/*N*/   if (b45Deg) return bMirror45Allowed;
/*N*/   return bMirrorFreeAllowed && !bMoveProtect;
/*N*/ }

/*N*/ BOOL SdrEditView::IsTransparenceAllowed() const
/*N*/ {
/*N*/   ForcePossibilities();
/*N*/   return bTransparenceAllowed;
/*N*/ }
/*N*/
/*N*/ BOOL SdrEditView::IsGradientAllowed() const
/*N*/ {
/*N*/   ForcePossibilities();
/*N*/   return bGradientAllowed;
/*N*/ }

//STRIP001 BOOL SdrEditView::IsShearAllowed() const
//STRIP001 {
//STRIP001  ForcePossibilities();
//STRIP001  if (bResizeProtect) return FALSE;
//STRIP001  return bShearAllowed;
//STRIP001 }

//STRIP001 BOOL SdrEditView::IsEdgeRadiusAllowed() const
//STRIP001 {
//STRIP001  ForcePossibilities();
//STRIP001  return bEdgeRadiusAllowed;
//STRIP001 }

/*N*/ BOOL SdrEditView::IsCrookAllowed(BOOL bNoContortion) const
/*N*/ {
/*N*/   // CrookMode fehlt hier (weil kein Rotate bei Shear ...)
/*N*/   ForcePossibilities();
/*N*/   if (bNoContortion) {
/*?*/       if (!bRotateFreeAllowed) return FALSE; // Crook is nich
/*?*/       return !bMoveProtect && bMoveAllowed;
/*N*/   } else {
/*N*/       return !bResizeProtect && bContortionPossible;
/*N*/   }
/*N*/ }

//STRIP001 BOOL SdrEditView::IsDistortAllowed(BOOL bNoContortion) const
//STRIP001 {
//STRIP001  ForcePossibilities();
//STRIP001  if (bNoContortion) {
//STRIP001      return FALSE;
//STRIP001  } else {
//STRIP001      return !bResizeProtect && bContortionPossible;
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL SdrEditView::IsCombinePossible(BOOL bNoPolyPoly) const
//STRIP001 {
//STRIP001  ForcePossibilities();
//STRIP001  if (bNoPolyPoly) return bCombineNoPolyPolyPossible;
//STRIP001  else return bCombinePossible;
//STRIP001 }

//STRIP001 BOOL SdrEditView::IsDismantlePossible(BOOL bMakeLines) const
//STRIP001 {
//STRIP001  ForcePossibilities();
//STRIP001  if (bMakeLines) return bDismantleMakeLinesPossible;
//STRIP001  else return bDismantlePossible;
//STRIP001 }

/*N*/ void SdrEditView::CheckPossibilities()
/*N*/ {
/*N*/   if (bSomeObjChgdFlag) bPossibilitiesDirty=TRUE;
/*N*/
/*N*/   if(bSomeObjChgdFlag)
/*N*/   {
/*N*/       // This call IS necessary to correct the MarkList, in which
/*N*/       // no longer to the model belonging objects still can reside.
/*N*/       // These ones nned to be removed.
/*N*/       CheckMarked();
/*N*/   }
/*N*/
/*N*/   if (bPossibilitiesDirty) {
/*N*/       ImpResetPossibilityFlags();
/*N*/       aMark.ForceSort();
/*N*/       ULONG nMarkAnz=aMark.GetMarkCount();
/*N*/       if (nMarkAnz!=0) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            bReverseOrderPossible=nMarkAnz>=2;
//STRIP001 /*?*/
//STRIP001 /*?*/            ULONG nMovableCount=0;
//STRIP001 /*?*/            bGroupPossible=nMarkAnz>=2;
//STRIP001 /*?*/            bCombinePossible=nMarkAnz>=2;
//STRIP001 /*?*/            if (nMarkAnz==1) {
//STRIP001 /*?*/                // bCombinePossible gruendlicher checken
//STRIP001 /*?*/                // fehlt noch ...
//STRIP001 /*?*/                const SdrObject* pObj=aMark.GetMark(0)->GetObj();
//STRIP001 /*?*/                const SdrPathObj* pPath=PTR_CAST(SdrPathObj,pObj);
//STRIP001 /*?*/                BOOL bGroup=pObj->GetSubList()!=NULL;
//STRIP001 /*?*/                BOOL bHasText=pObj->GetOutlinerParaObject()!=NULL;
//STRIP001 /*?*/                if (bGroup || bHasText) {
//STRIP001 /*?*/                    bCombinePossible=TRUE;
//STRIP001 /*?*/                } else {
//STRIP001 /*?*/                    // folgendes Statemant macht IMHO keinen Sinn (Bugfix am 27-11-1995 Combine und Fontwork):
//STRIP001 /*?*/                    //bCombinePossible=pPath->GetPathPoly().Count()>1;
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/            bCombineNoPolyPolyPossible=bCombinePossible;
//STRIP001 /*?*/            bDeletePossible=TRUE;
//STRIP001 /*?*/            // Zu den Transformationen erstmal ja sagen
//STRIP001 /*?*/            bMoveAllowed      =TRUE;
//STRIP001 /*?*/            bResizeFreeAllowed=TRUE;
//STRIP001 /*?*/            bResizePropAllowed=TRUE;
//STRIP001 /*?*/            bRotateFreeAllowed=TRUE;
//STRIP001 /*?*/            bRotate90Allowed  =TRUE;
//STRIP001 /*?*/            bMirrorFreeAllowed=TRUE;
//STRIP001 /*?*/            bMirror45Allowed  =TRUE;
//STRIP001 /*?*/            bMirror90Allowed  =TRUE;
//STRIP001 /*?*/            bShearAllowed     =TRUE;
//STRIP001 /*?*/            bEdgeRadiusAllowed=FALSE;
//STRIP001 /*?*/            bContortionPossible=TRUE;
//STRIP001 /*?*/            bCanConvToContour = TRUE;
//STRIP001 /*?*/
//STRIP001 /*?*/            // these ones are only allowed when single object is selected
//STRIP001 /*?*/            bTransparenceAllowed = (nMarkAnz == 1);
//STRIP001 /*?*/            bGradientAllowed = (nMarkAnz == 1);
//STRIP001 /*?*/            if(bGradientAllowed)
//STRIP001 /*?*/            {
//STRIP001 /*?*/                // gradient depends on fillstyle
//STRIP001 /*?*/                const SdrMark* pM = aMark.GetMark(0);
//STRIP001 /*?*/                const SdrObject* pObj = pM->GetObj();
//STRIP001 /*?*/
//STRIP001 /*?*/
//STRIP001 /*?*/                XFillStyle eFillStyle = ((XFillStyleItem&)(pObj->GetItem(XATTR_FILLSTYLE))).GetValue();
//STRIP001 /*?*/
//STRIP001 /*?*/                if(eFillStyle != XFILL_GRADIENT)
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    bGradientAllowed = FALSE;
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            BOOL bNoMovRotFound=FALSE;
//STRIP001 /*?*/            const SdrPageView* pPV0=NULL;
//STRIP001
//STRIP001 /*?*/            for (ULONG nm=0; nm<nMarkAnz; nm++) {
//STRIP001 /*?*/                const SdrMark* pM=aMark.GetMark(nm);
//STRIP001 /*?*/                const SdrObject* pObj=pM->GetObj();
//STRIP001 /*?*/                const SdrPageView* pPV=pM->GetPageView();
//STRIP001 /*?*/                if (pPV!=pPV0) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 //STRIP001 /*?*/                     if (pPV->IsReadOnly()) bReadOnly=TRUE;
//STRIP001 //STRIP001 /*?*/                     pPV0=pPV;
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/                SdrObjTransformInfoRec aInfo;
//STRIP001 /*?*/                pObj->TakeObjInfo(aInfo);
//STRIP001 /*?*/                BOOL bMovPrt=pObj->IsMoveProtect();
//STRIP001 /*?*/                BOOL bSizPrt=pObj->IsResizeProtect();
//STRIP001 /*?*/                if (!bMovPrt && aInfo.bMoveAllowed) nMovableCount++; // Menge der MovableObjs zaehlen
//STRIP001 /*?*/                if (bMovPrt) bMoveProtect=TRUE;
//STRIP001 /*?*/                if (bSizPrt) bResizeProtect=TRUE;
//STRIP001 /*?*/
//STRIP001 /*?*/                // not allowed when not allowed at one object
//STRIP001 /*?*/                if(!aInfo.bTransparenceAllowed)
//STRIP001 /*?*/                    bTransparenceAllowed = FALSE;
//STRIP001 /*?*/
//STRIP001 /*?*/                // Wenn einer was nicht kann, duerfen's alle nicht
//STRIP001 /*?*/                if (!aInfo.bMoveAllowed      ) bMoveAllowed      =FALSE;
//STRIP001 /*?*/                if (!aInfo.bResizeFreeAllowed) bResizeFreeAllowed=FALSE;
//STRIP001 /*?*/                if (!aInfo.bResizePropAllowed) bResizePropAllowed=FALSE;
//STRIP001 /*?*/                if (!aInfo.bRotateFreeAllowed) bRotateFreeAllowed=FALSE;
//STRIP001 /*?*/                if (!aInfo.bRotate90Allowed  ) bRotate90Allowed  =FALSE;
//STRIP001 /*?*/                if (!aInfo.bMirrorFreeAllowed) bMirrorFreeAllowed=FALSE;
//STRIP001 /*?*/                if (!aInfo.bMirror45Allowed  ) bMirror45Allowed  =FALSE;
//STRIP001 /*?*/                if (!aInfo.bMirror90Allowed  ) bMirror90Allowed  =FALSE;
//STRIP001 /*?*/                if (!aInfo.bShearAllowed     ) bShearAllowed     =FALSE;
//STRIP001 /*?*/                if (aInfo.bEdgeRadiusAllowed) bEdgeRadiusAllowed=TRUE;
//STRIP001 /*?*/                if (aInfo.bNoContortion      ) bContortionPossible=FALSE;
//STRIP001 /*?*/                // Fuer Crook mit Contortion: Alle Objekte muessen
//STRIP001 /*?*/                // Movable und Rotatable sein, ausser maximal 1
//STRIP001 /*?*/                if (!bMoreThanOneNoMovRot) {
//STRIP001 /*?*/                    if (!aInfo.bMoveAllowed || !aInfo.bResizeFreeAllowed) {
//STRIP001 /*?*/                        bMoreThanOneNoMovRot=bNoMovRotFound;
//STRIP001 /*?*/                        bNoMovRotFound=TRUE;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/                // when one member cannot be converted, no conversion is possible
//STRIP001 /*?*/                if(!aInfo.bCanConvToContour)
//STRIP001 /*?*/                    bCanConvToContour = FALSE;
//STRIP001 /*?*/
//STRIP001 /*?*/                // Ungroup
//STRIP001 /*?*/                if (!bUnGroupPossible) bUnGroupPossible=pObj->GetSubList()!=NULL;
//STRIP001 /*?*/                // ConvertToCurve: Wenn mind. einer konvertiert werden kann ist das ok.
//STRIP001 /*?*/                if (aInfo.bCanConvToPath          ) bCanConvToPath          =TRUE;
//STRIP001 /*?*/                if (aInfo.bCanConvToPoly          ) bCanConvToPoly          =TRUE;
//STRIP001 /*?*/                if (aInfo.bCanConvToPathLineToArea) bCanConvToPathLineToArea=TRUE;
//STRIP001 /*?*/                if (aInfo.bCanConvToPolyLineToArea) bCanConvToPolyLineToArea=TRUE;
//STRIP001 /*?*/                // Combine/Dismantle
//STRIP001 /*?*/                if (bCombinePossible) {
//STRIP001 /*?*/                    bCombinePossible=ImpCanConvertForCombine(pObj);
//STRIP001 /*?*/                    bCombineNoPolyPolyPossible=bCombinePossible;
//STRIP001 /*?*/                }
//STRIP001 /*?*/                if (!bDismantlePossible) bDismantlePossible=ImpCanDismantle(pObj,FALSE);
//STRIP001 /*?*/                if (!bDismantleMakeLinesPossible) bDismantleMakeLinesPossible=ImpCanDismantle(pObj,TRUE);
//STRIP001 /*?*/                // OrthoDesiredOnMarked checken
//STRIP001 /*?*/                if (!bOrthoDesiredOnMarked && !aInfo.bNoOrthoDesired) bOrthoDesiredOnMarked=TRUE;
//STRIP001 /*?*/                // ImportMtf checken
//STRIP001 /*?*/
//STRIP001 /*?*/                 if (!bImportMtfPossible) {
//STRIP001 /*?*/                     BOOL bGraf=HAS_BASE(SdrGrafObj,pObj);
//STRIP001 /*?*/                     BOOL bOle2=HAS_BASE(SdrOle2Obj,pObj);
//STRIP001 /*?*/
//STRIP001 /*?*/                    if( bGraf && ((SdrGrafObj*)pObj)->HasGDIMetaFile() && !((SdrGrafObj*)pObj)->IsEPS() )
//STRIP001 /*?*/                        bImportMtfPossible = TRUE;
//STRIP001 /*?*/
//STRIP001 /*?*/                    if (bOle2)
//STRIP001 /*?*/                        bImportMtfPossible=((SdrOle2Obj*)pObj)->HasGDIMetaFile();
//STRIP001 /*?*/                 }
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            bMoreThanOneNotMovable=nMovableCount<nMarkAnz-1;
//STRIP001 /*?*/            bOneOrMoreMovable=nMovableCount!=0;
//STRIP001 /*?*/            bGrpEnterPossible=bUnGroupPossible;
/*N*/       }
/*N*/       ImpCheckToTopBtmPossible();
/*N*/       ((SdrPolyEditView*)this)->ImpCheckPolyPossibilities();
/*N*/       bPossibilitiesDirty=FALSE;
/*N*/
/*N*/       if (bReadOnly) {
/*?*/           BOOL bMerker1=bGrpEnterPossible;
/*?*/           ImpResetPossibilityFlags();
/*?*/           bReadOnly=TRUE;
/*?*/           bGrpEnterPossible=bMerker1;
/*N*/       }
/*N*/       if (bMoveAllowed) {
/*?*/           // Verschieben von angeklebten Verbindern unterbinden
/*?*/           // Derzeit nur fuer Einfachselektion implementiert.
/*?*/           if (nMarkAnz==1) {
/*?*/               SdrObject* pObj=aMark.GetMark(0)->GetObj();
/*?*/               SdrEdgeObj* pEdge=PTR_CAST(SdrEdgeObj,pObj);
/*?*/               if (pEdge!=NULL) {
/*?*/                   SdrObject* pNode1=pEdge->GetConnectedNode(TRUE);
/*?*/                   SdrObject* pNode2=pEdge->GetConnectedNode(FALSE);
/*?*/                   if (pNode1!=NULL || pNode2!=NULL) bMoveAllowed=FALSE;
/*?*/               }
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrEditView::ForceMarkedObjToAnotherPage()
//STRIP001 {
//STRIP001  BOOL bFlg=FALSE;
//STRIP001  for (ULONG nm=0; nm<aMark.GetMarkCount(); nm++) {
//STRIP001      SdrMark* pM=aMark.GetMark(nm);
//STRIP001      SdrObject* pObj=pM->GetObj();
//STRIP001      Rectangle aObjRect(pObj->GetBoundRect());
//STRIP001      aObjRect+=pM->GetPageView()->GetOffset(); // auf View-Koordinaten
//STRIP001      Rectangle aPgRect(pM->GetPageView()->GetPageRect());
//STRIP001      if (!aObjRect.IsOver(aPgRect)) {
//STRIP001          BOOL bFnd=FALSE;
//STRIP001          SdrPageView* pPV;
//STRIP001          for (USHORT nv=GetPageViewCount(); nv>0 && !bFnd;) {
//STRIP001              nv--;
//STRIP001              pPV=GetPageViewPvNum(nv);
//STRIP001              bFnd=aObjRect.IsOver(pPV->GetPageRect());
//STRIP001          }
//STRIP001          if (bFnd) {
//STRIP001              pM->GetPageView()->GetObjList()->RemoveObject(pObj->GetOrdNum());
//STRIP001              Point aDelta(pM->GetPageView()->GetOffset()-pPV->GetOffset());
//STRIP001              pObj->Move(Size(aDelta.X(),aDelta.Y()));
//STRIP001              SdrInsertReason aReason(SDRREASON_VIEWCALL);
//STRIP001              pPV->GetObjList()->InsertObject(pObj,CONTAINER_APPEND,&aReason);
//STRIP001              pM->SetPageView(pPV);
//STRIP001              InvalidateAllWin(aObjRect);
//STRIP001              bFlg=TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if (bFlg) {
//STRIP001      MarkListHasChanged();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrEditView::DeleteMarked(SdrMarkList& rMark)
//STRIP001 {
//STRIP001  if (rMark.GetMarkCount()!=0) {
//STRIP001      rMark.ForceSort();
//STRIP001      BegUndo();
//STRIP001      ULONG nMarkAnz=rMark.GetMarkCount();
//STRIP001      ULONG nm;
//STRIP001      for (nm=nMarkAnz; nm>0;) {
//STRIP001          nm--;
//STRIP001          SdrMark* pM=rMark.GetMark(nm);
//STRIP001          AddUndo(new SdrUndoDelObj(*pM->GetObj()));
//STRIP001      }
//STRIP001      // Sicherstellen, dass die OrderNums stimmen:
//STRIP001      rMark.GetMark(0)->GetObj()->GetOrdNum();
//STRIP001      for (nm=nMarkAnz; nm>0;) {
//STRIP001          nm--;
//STRIP001          SdrMark* pM=rMark.GetMark(nm);
//STRIP001          SdrObject*   pObj=pM->GetObj();
//STRIP001          SdrPageView* pPV =pM->GetPageView();
//STRIP001          SdrObjList*  pOL =pObj->GetObjList(); //#52680#
//STRIP001          UINT32 nOrdNum=pObj->GetOrdNumDirect();
//STRIP001          SdrObject* pChkObj=pOL->RemoveObject(nOrdNum);
//STRIP001          DBG_ASSERT(pChkObj==pObj,"DeleteMarked(MarkList): pChkObj!=pObj beim RemoveObject()");
//STRIP001      }
//STRIP001      EndUndo();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrEditView::DeleteMarkedObj()
//STRIP001 {
//STRIP001  if (aMark.GetMarkCount()!=0) {
//STRIP001      nSpecialCnt=0;
//STRIP001      BrkAction();
//STRIP001      HideMarkHdl(NULL);
//STRIP001      BegUndo(ImpGetResStr(STR_EditDelete),aMark.GetMarkDescription(),SDRREPFUNC_OBJ_DELETE);
//STRIP001      DeleteMarked(aMark);
//STRIP001      aMark.Clear();
//STRIP001      aHdl.Clear();
//STRIP001      EndUndo();
//STRIP001      MarkListHasChanged();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrEditView::CopyMarkedObj()
//STRIP001 {
//STRIP001  aMark.ForceSort();
//STRIP001  ForceEdgesOfMarkedNodes();
//STRIP001
//STRIP001  SdrMarkList aSourceObjectsForCopy(aMark);
//STRIP001  // Folgende Schleife Anstatt MarkList::Merge(), damit
//STRIP001  // ich jeweils mein Flag an die MarkEntries setzen kann.
//STRIP001  ULONG nEdgeAnz=aEdgesOfMarkedNodes.GetMarkCount();
//STRIP001  for (ULONG nEdgeNum=0; nEdgeNum<nEdgeAnz; nEdgeNum++) {
//STRIP001      SdrMark aM(*aEdgesOfMarkedNodes.GetMark(nEdgeNum));
//STRIP001      aM.SetUser(1);
//STRIP001      aSourceObjectsForCopy.InsertEntry(aM);
//STRIP001  }
//STRIP001  aSourceObjectsForCopy.ForceSort();
//STRIP001
//STRIP001  // #i13033#
//STRIP001  // New mechanism to re-create the connections of cloned connectors
//STRIP001  CloneList aCloneList;
//STRIP001
//STRIP001  aMark.Clear();
//STRIP001  ULONG nCloneErrCnt=0;
//STRIP001  ULONG nMarkAnz=aSourceObjectsForCopy.GetMarkCount();
//STRIP001  ULONG nm;
//STRIP001  for (nm=0; nm<nMarkAnz; nm++) {
//STRIP001      SdrMark* pM=aSourceObjectsForCopy.GetMark(nm);
//STRIP001      SdrObject* pO=pM->GetObj()->Clone();
//STRIP001      if (pO!=NULL) {
//STRIP001          SdrInsertReason aReason(SDRREASON_VIEWCALL);
//STRIP001          pM->GetPageView()->GetObjList()->InsertObject(pO,CONTAINER_APPEND,&aReason);
//STRIP001          AddUndo(new SdrUndoCopyObj(*pO));
//STRIP001          SdrMark aME(*pM);
//STRIP001          aME.SetObj(pO);
//STRIP001
//STRIP001          // aCopiedObjects.InsertEntry(aME);
//STRIP001          aCloneList.AddPair(pM->GetObj(), pO);
//STRIP001
//STRIP001          if (pM->GetUser()==0) { // Sonst war's nur eine mitzukierende Edge
//STRIP001              aMark.InsertEntry(aME);
//STRIP001          }
//STRIP001      } else {
//STRIP001          nCloneErrCnt++;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // #i13033#
//STRIP001  // New mechanism to re-create the connections of cloned connectors
//STRIP001  aCloneList.CopyConnections();
//STRIP001
//STRIP001  if(0L != nCloneErrCnt)
//STRIP001  {
//STRIP001 #ifdef DBG_UTIL
//STRIP001      ByteString aStr("SdrEditView::CopyMarkedObj(): Fehler beim Clonen ");
//STRIP001
//STRIP001      if(nCloneErrCnt == 1)
//STRIP001      {
//STRIP001          aStr += "eines Zeichenobjekts.";
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          aStr += "von ";
//STRIP001          aStr += ByteString::CreateFromInt32( nCloneErrCnt );
//STRIP001          aStr += " Zeichenobjekten.";
//STRIP001      }
//STRIP001
//STRIP001      aStr += " Objektverbindungen werden nicht mitkopiert.";
//STRIP001      DBG_ERROR(aStr.GetBuffer());
//STRIP001 #endif
//STRIP001  }
//STRIP001  MarkListHasChanged();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 BOOL SdrEditView::InsertObject(SdrObject* pObj, SdrPageView& rPV, ULONG nOptions)
//STRIP001 {
//STRIP001  if ((nOptions & SDRINSERT_SETDEFLAYER)!=0) {
//STRIP001      SdrLayerID nLayer=rPV.GetPage()->GetLayerAdmin().GetLayerID(aAktLayer,TRUE);
//STRIP001      if (nLayer==SDRLAYER_NOTFOUND) nLayer=0;
//STRIP001      if (rPV.GetLockedLayers().IsSet(nLayer) || !rPV.GetVisibleLayers().IsSet(nLayer)) {
//STRIP001          delete pObj; // Layer gesperrt oder nicht sichtbar
//STRIP001          return FALSE;
//STRIP001      }
//STRIP001      pObj->NbcSetLayer(nLayer);
//STRIP001  }
//STRIP001  if ((nOptions & SDRINSERT_SETDEFATTR)!=0) {
//STRIP001      if (pDefaultStyleSheet!=NULL) pObj->NbcSetStyleSheet(pDefaultStyleSheet,FALSE);
//STRIP001      pObj->SetItemSet(aDefaultAttr);
//STRIP001  }
//STRIP001  if (!pObj->IsInserted()) {
//STRIP001      SdrInsertReason aReason(SDRREASON_VIEWCALL);
//STRIP001      if ((nOptions & SDRINSERT_NOBROADCAST)!=0) {
//STRIP001          rPV.GetObjList()->NbcInsertObject(pObj,CONTAINER_APPEND,&aReason);
//STRIP001      } else {
//STRIP001          rPV.GetObjList()->InsertObject(pObj,CONTAINER_APPEND,&aReason);
//STRIP001      }
//STRIP001  }
//STRIP001  AddUndo(new SdrUndoNewObj(*pObj));
//STRIP001  if ((nOptions & SDRINSERT_DONTMARK)==0) {
//STRIP001      if ((nOptions & SDRINSERT_ADDMARK)==0) UnmarkAllObj();
//STRIP001      MarkObj(pObj,&rPV);
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 void SdrEditView::ReplaceObject(SdrObject* pOldObj, SdrPageView& rPV, SdrObject* pNewObj, BOOL bMark)
//STRIP001 {
//STRIP001  SdrObjList* pOL=pOldObj->GetObjList();
//STRIP001  AddUndo(new SdrUndoReplaceObj(*pOldObj,*pNewObj));
//STRIP001  pOL->ReplaceObject(pNewObj,pOldObj->GetOrdNum());
//STRIP001  if (bMark) MarkObj(pNewObj,&rPV);
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef WIN
//STRIP001 void SdrEditView::BegUndo()             // Undo-Klammerung auf
//STRIP001 {
//STRIP001  pMod->BegUndo();
//STRIP001 }

//STRIP001 void SdrEditView::BegUndo(const String& rComment) // Undo-Klammerung auf
//STRIP001 {
//STRIP001  pMod->BegUndo(rComment);
//STRIP001 }

//STRIP001 void SdrEditView::BegUndo(const String& rComment, const String& rObjDescr,
//STRIP001      SdrRepeatFunc eFunc) // Undo-Klammerung auf
//STRIP001 {
//STRIP001  pMod->BegUndo(rComment,rObjDescr,eFunc);
//STRIP001 }

//STRIP001 void SdrEditView::BegUndo(SdrUndoGroup* pUndoGrp) // Undo-Klammerung auf
//STRIP001 {
//STRIP001  pMod->BegUndo(pUndoGrp);
//STRIP001 }

//STRIP001 void SdrEditView::AddUndo(SdrUndoAction* pUndo)   // Action hinzufuegen
//STRIP001 {
//STRIP001  pMod->AddUndo(pUndo);
//STRIP001 }
    // nur nach dem 1. BegUndo oder vor dem letzten EndUndo:
//STRIP001 void SdrEditView::SetUndoComment(const String& rComment)
//STRIP001 {
//STRIP001  pMod->SetUndoComment(rComment);
//STRIP001 }

//STRIP001 void SdrEditView::SetUndoComment(const String& rComment,
//STRIP001                              const String& rObjDescr)
//STRIP001 {
//STRIP001  pMod->SetUndoComment(rComment,rObjDescr);
//STRIP001 }
#endif

