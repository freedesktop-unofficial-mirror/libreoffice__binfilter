/*************************************************************************
 *
 *  $RCSfile: svx_view3d.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:43:26 $
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

#define ITEMID_COLOR 0

#ifndef _SV_WRKWIN_HXX
#include <vcl/wrkwin.hxx>
#endif

#ifndef INCLUDED_SVTOOLS_OPTIONS3D_HXX
#include <svtools/options3d.hxx>
#endif

#ifndef _SVDOGRP_HXX
#include "svdogrp.hxx"
#endif

#ifndef _SVDOPATH_HXX
#include "svdopath.hxx"
#endif

#ifndef _SHL_HXX
#include <tools/shl.hxx>
#endif

#ifndef _SVDITER_HXX
#include "svditer.hxx"
#endif

#ifndef _SVDPOOL_HXX
#include "svdpool.hxx"
#endif

#ifndef _SVDORECT_HXX
#include "svdorect.hxx"
#endif

#ifndef _SVDMODEL_HXX
#include "svdmodel.hxx"
#endif

#ifndef _SVDPAGV_HXX
#include "svdpagv.hxx"
#endif

#ifndef _XOUTX_HXX
#include "xoutx.hxx"
#endif

#ifndef _SVX_SVXIDS_HRC
#include <svxids.hrc>
#endif

#ifndef _SVX_COLRITEM_HXX
#include "colritem.hxx"
#endif

#ifndef _XTABLE_HXX
#include "xtable.hxx"
#endif

#ifndef _SVDVIEW_HXX
#include "svdview.hxx"
#endif

#ifndef _SVX_DIALOGS_HRC
#include "dialogs.hrc"
#endif

#ifndef _SVX_DIALMGR_HXX
#include "dialmgr.hxx"
#endif

#ifndef _E3D_GLOBL3D_HXX
#include "globl3d.hxx"
#endif

#ifndef _E3D_OBJ3D_HXX
#include "obj3d.hxx"
#endif

#ifndef _E3D_LATHE3D_HXX
#include "lathe3d.hxx"
#endif

#ifndef _E3D_SPHERE3D_HXX
#include "sphere3d.hxx"
#endif

#ifndef _E3D_EXTRUD3D_HXX
#include "extrud3d.hxx"
#endif

#ifndef _E3D_CUBE3D_HXX
#include "cube3d.hxx"
#endif

#ifndef _E3D_POLYOB3D_HXX
#include "polyob3d.hxx"
#endif

#ifndef _E3D_DLIGHT3D_HXX
#include "dlight3d.hxx"
#endif

#ifndef _E3D_POLYSC3D_HXX
#include "polysc3d.hxx"
#endif

#ifndef _E3D_DRAGMT3D_HXX
#include "dragmt3d.hxx"
#endif

#ifndef _E3D_VIEW3D_HXX
#include "view3d.hxx"
#endif

#ifndef _SVDUNDO_HXX
#include "svdundo.hxx"
#endif

#ifndef _SVX_XFLCLIT_HXX
#include "xflclit.hxx"
#endif

#ifndef _SVX_XLNCLIT_HXX
#include "xlnclit.hxx"
#endif

#ifndef _SVDOGRAF_HXX
#include <svdograf.hxx>
#endif

#ifndef _SVX_XBTMPIT_HXX
#include <xbtmpit.hxx>
#endif

#ifndef _SVX_XFLBMTIT_HXX
#include <xflbmtit.hxx>
#endif

#include "xlnwtit.hxx"
namespace binfilter {

#define ITEMVALUE(ItemSet,Id,Cast)  ((const Cast&)(ItemSet).Get(Id)).GetValue()

/*N*/ TYPEINIT1(E3dView, SdrView);

long Scalar (Point aPoint1,
             Point aPoint2);

Point ScaleVector (Point  aPoint,
                   double nScale);

double NormVector (Point aPoint);

BOOL LineCutting (Point aP1,
                  Point aP2,
                  Point aP3,
                  Point aP4);

long Point2Line (Point aP1,
                 Point aP2,
                 Point aP3);

long DistPoint2Line (Point u,
                     Point v1,
                     Point v);

/*************************************************************************
|*
|* Konstruktor 1
|*
\************************************************************************/

/*N*/ E3dView::E3dView(SdrModel* pModel, OutputDevice* pOut) :
/*N*/     SdrView(pModel, pOut)
/*N*/ {
/*N*/   InitView ();
/*N*/ }

/*************************************************************************
|*
|* Konstruktor 2
|*
\************************************************************************/

/*?*/ E3dView::E3dView(SdrModel* pModel, ExtOutputDevice* pExtOut) :
/*?*/     SdrView(pModel, pExtOut)
/*?*/ {
/*?*/   InitView ();
/*?*/ }

/*************************************************************************
|*
|* Konstruktor 3
|*
\************************************************************************/

/*?*/ E3dView::E3dView(SdrModel* pModel) :
/*?*/     SdrView(pModel)
/*?*/ {
/*?*/   InitView ();
/*?*/ }

/*************************************************************************
|*
|* DrawMarkedObj ueberladen, da eventuell nur einzelne 3D-Objekte
|* gezeichnet werden sollen
|*
\************************************************************************/

//STRIP001 void E3dView::DrawMarkedObj(OutputDevice& rOut, const Point& rOfs) const
//STRIP001 {
//STRIP001  // Existieren 3D-Objekte, deren Szenen nicht selektiert sind?
//STRIP001  BOOL bSpecialHandling = FALSE;
//STRIP001  E3dScene *pScene = NULL;
//STRIP001
//STRIP001  long nCnt = aMark.GetMarkCount();
//STRIP001  for(long nObjs = 0;nObjs < nCnt;nObjs++)
//STRIP001  {
//STRIP001      SdrObject *pObj = aMark.GetMark(nObjs)->GetObj();
//STRIP001      if(pObj && pObj->ISA(E3dCompoundObject))
//STRIP001      {
//STRIP001          // zugehoerige Szene
//STRIP001          pScene = ((E3dCompoundObject*)pObj)->GetScene();
//STRIP001          if(pScene && !IsObjMarked(pScene))
//STRIP001              bSpecialHandling = TRUE;
//STRIP001      }
//STRIP001      // Alle SelectionFlags zuruecksetzen
//STRIP001      if(pObj && pObj->ISA(E3dObject))
//STRIP001      {
//STRIP001          pScene = ((E3dObject*)pObj)->GetScene();
//STRIP001          if(pScene)
//STRIP001              pScene->SetSelected(FALSE);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if(bSpecialHandling)
//STRIP001  {
//STRIP001      // SelectionFlag bei allen zu 3D Objekten gehoerigen
//STRIP001      // Szenen und deren Objekten auf nicht selektiert setzen
//STRIP001      long nObjs;
//STRIP001      for(nObjs = 0;nObjs < nCnt;nObjs++)
//STRIP001      {
//STRIP001          SdrObject *pObj = aMark.GetMark(nObjs)->GetObj();
//STRIP001          if(pObj && pObj->ISA(E3dCompoundObject))
//STRIP001          {
//STRIP001              // zugehoerige Szene
//STRIP001              pScene = ((E3dCompoundObject*)pObj)->GetScene();
//STRIP001              if(pScene)
//STRIP001                  pScene->SetSelected(FALSE);
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // bei allen direkt selektierten Objekten auf selektiert setzen
//STRIP001      SdrMark* pM = NULL;
//STRIP001
//STRIP001      for(nObjs = 0;nObjs < nCnt;nObjs++)
//STRIP001      {
//STRIP001          SdrObject *pObj = aMark.GetMark(nObjs)->GetObj();
//STRIP001          if(pObj && pObj->ISA(E3dObject))
//STRIP001          {
//STRIP001              // Objekt markieren
//STRIP001              E3dObject* p3DObj = (E3dObject*)pObj;
//STRIP001              p3DObj->SetSelected(TRUE);
//STRIP001              pScene = p3DObj->GetScene();
//STRIP001              pM = aMark.GetMark(nObjs);
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if(pScene)
//STRIP001      {
//STRIP001          // code from parent
//STRIP001          ((E3dView*)this)->aMark.ForceSort();
//STRIP001          pXOut->SetOutDev(&rOut);
//STRIP001          SdrPaintInfoRec aInfoRec;
//STRIP001          aInfoRec.nPaintMode|=SDRPAINTMODE_ANILIKEPRN;
//STRIP001
//STRIP001          Point aOfs(-rOfs.X(), -rOfs.Y());
//STRIP001          aOfs += pM->GetPageView()->GetOffset();
//STRIP001
//STRIP001          if(aOfs != pXOut->GetOffset())
//STRIP001              pXOut->SetOffset(aOfs);
//STRIP001
//STRIP001          pScene->SetDrawOnlySelected(TRUE);
//STRIP001          pScene->Paint(*pXOut,aInfoRec);
//STRIP001          pScene->SetDrawOnlySelected(FALSE);
//STRIP001
//STRIP001          pXOut->SetOffset(Point(0,0));
//STRIP001      }
//STRIP001
//STRIP001      // SelectionFlag zuruecksetzen
//STRIP001      for(nObjs = 0;nObjs < nCnt;nObjs++)
//STRIP001      {
//STRIP001          SdrObject *pObj = aMark.GetMark(nObjs)->GetObj();
//STRIP001          if(pObj && pObj->ISA(E3dCompoundObject))
//STRIP001          {
//STRIP001              // zugehoerige Szene
//STRIP001              pScene = ((E3dCompoundObject*)pObj)->GetScene();
//STRIP001              if(pScene)
//STRIP001                  pScene->SetSelected(FALSE);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // call parent
//STRIP001      SdrExchangeView::DrawMarkedObj(rOut, rOfs);
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Model holen ueberladen, da bei einzelnen 3D Objekten noch eine Szene
|* untergeschoben werden muss
|*
\************************************************************************/

//STRIP001 SdrModel* E3dView::GetMarkedObjModel() const
//STRIP001 {
//STRIP001  // Existieren 3D-Objekte, deren Szenen nicht selektiert sind?
//STRIP001  BOOL bSpecialHandling = FALSE;
//STRIP001  E3dScene *pScene = NULL;
//STRIP001
//STRIP001  long nCnt = aMark.GetMarkCount();
//STRIP001  for(long nObjs = 0;nObjs < nCnt;nObjs++)
//STRIP001  {
//STRIP001      SdrObject *pObj = aMark.GetMark(nObjs)->GetObj();
//STRIP001      if(pObj && pObj->ISA(E3dCompoundObject))
//STRIP001      {
//STRIP001          // zugehoerige Szene
//STRIP001          pScene = ((E3dCompoundObject*)pObj)->GetScene();
//STRIP001          if(pScene && !IsObjMarked(pScene))
//STRIP001              bSpecialHandling = TRUE;
//STRIP001      }
//STRIP001      // Alle SelectionFlags zuruecksetzen
//STRIP001      if(pObj && pObj->ISA(E3dObject))
//STRIP001      {
//STRIP001          pScene = ((E3dObject*)pObj)->GetScene();
//STRIP001          if(pScene)
//STRIP001              pScene->SetSelected(FALSE);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  SdrModel* pNewModel = 0L;
//STRIP001  if(bSpecialHandling)
//STRIP001  {
//STRIP001      // SelectionFlag bei allen zu 3D Objekten gehoerigen
//STRIP001      // Szenen und deren Objekten auf nicht selektiert setzen
//STRIP001      long nObjs;
//STRIP001      for(nObjs = 0;nObjs < nCnt;nObjs++)
//STRIP001      {
//STRIP001          SdrObject *pObj = aMark.GetMark(nObjs)->GetObj();
//STRIP001          if(pObj && pObj->ISA(E3dCompoundObject))
//STRIP001          {
//STRIP001              // zugehoerige Szene
//STRIP001              pScene = ((E3dCompoundObject*)pObj)->GetScene();
//STRIP001              if(pScene)
//STRIP001                  pScene->SetSelected(FALSE);
//STRIP001          }
//STRIP001      }
//STRIP001      // bei allen direkt selektierten Objekten auf selektiert setzen
//STRIP001      for(nObjs = 0;nObjs < nCnt;nObjs++)
//STRIP001      {
//STRIP001          SdrObject *pObj = aMark.GetMark(nObjs)->GetObj();
//STRIP001          if(pObj && pObj->ISA(E3dObject))
//STRIP001          {
//STRIP001              // Objekt markieren
//STRIP001              E3dObject* p3DObj = (E3dObject*)pObj;
//STRIP001              p3DObj->SetSelected(TRUE);
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // Neue MarkList generieren, die die betroffenen
//STRIP001      // Szenen als markierte Objekte enthaelt
//STRIP001         SdrMarkList aOldML(aMark); // alte Marklist merken
//STRIP001         SdrMarkList aNewML; // neue leere Marklist
//STRIP001      ((E3dView*)this)->aMark = aNewML;
//STRIP001
//STRIP001      for(nObjs = 0;nObjs < nCnt;nObjs++)
//STRIP001      {
//STRIP001          SdrObject *pObj = aOldML.GetMark(nObjs)->GetObj();
//STRIP001          if(pObj)
//STRIP001          {
//STRIP001              if(pObj->ISA(E3dCompoundObject))
//STRIP001              {
//STRIP001                  // zugehoerige Szene holen
//STRIP001                  pScene = ((E3dCompoundObject*)pObj)->GetScene();
//STRIP001                  if(pScene)
//STRIP001                      pObj = pScene;
//STRIP001              }
//STRIP001
//STRIP001              // Keine Objekte doppelt markieren
//STRIP001              // (dies koennten nur Szenen sein)
//STRIP001              if(!IsObjMarked(pObj))
//STRIP001              {
//STRIP001                  USHORT nAnz=GetPageViewCount();
//STRIP001                  for (USHORT nv=0; nv<nAnz; nv++) {
//STRIP001                      SdrPageView* pPV=GetPageViewPvNum(nv);
//STRIP001                      ((E3dView*)this)->MarkObj(pObj,pPV,FALSE,TRUE);
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // call parent
//STRIP001      pNewModel = SdrView::GetMarkedObjModel();
//STRIP001
//STRIP001      // Alle Szenen im kopierten Model in Ihren Ausdehnungen Korrigieren
//STRIP001      // und IsSelected zuruecksetzen
//STRIP001      if(pNewModel)
//STRIP001      {
//STRIP001          for(UINT16 nPg=0; nPg < pNewModel->GetPageCount(); nPg++)
//STRIP001          {
//STRIP001              const SdrPage* pSrcPg=pNewModel->GetPage(nPg);
//STRIP001              UINT32 nObAnz=pSrcPg->GetObjCount();
//STRIP001
//STRIP001              // Unterobjekte von Szenen einfuegen
//STRIP001              for(UINT32 nOb=0; nOb<nObAnz; nOb++)
//STRIP001              {
//STRIP001                  const SdrObject* pSrcOb=pSrcPg->GetObj(nOb);
//STRIP001                  if(pSrcOb->ISA(E3dScene))
//STRIP001                  {
//STRIP001                      pScene = (E3dScene*)pSrcOb;
//STRIP001                      pScene->CorrectSceneDimensions();
//STRIP001                      pScene->SetSelected(FALSE);
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // Alte Liste wieder setzen
//STRIP001      ((E3dView*)this)->aMark = aOldML;
//STRIP001
//STRIP001      // SelectionFlag zuruecksetzen
//STRIP001      for(nObjs = 0;nObjs < nCnt;nObjs++)
//STRIP001      {
//STRIP001          SdrObject *pObj = aMark.GetMark(nObjs)->GetObj();
//STRIP001          if(pObj && pObj->ISA(E3dCompoundObject))
//STRIP001          {
//STRIP001              // zugehoerige Szene
//STRIP001              pScene = ((E3dCompoundObject*)pObj)->GetScene();
//STRIP001              if(pScene)
//STRIP001                  pScene->SetSelected(FALSE);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // call parent
//STRIP001      pNewModel = SdrView::GetMarkedObjModel();
//STRIP001  }
//STRIP001
//STRIP001  // model zurueckgeben
//STRIP001  return pNewModel;
//STRIP001 }

/*************************************************************************
|*
|* Bei Paste muss - falls in eine Scene eingefuegt wird - die
|* Objekte der Szene eingefuegt werden, die Szene selbst aber nicht
|*
\************************************************************************/

//STRIP001 BOOL E3dView::Paste(const SdrModel& rMod, const Point& rPos, SdrObjList* pLst, UINT32 nOptions)
//STRIP001 {
//STRIP001  BOOL bRetval = FALSE;
//STRIP001
//STRIP001  // Liste holen
//STRIP001     Point aPos(rPos);
//STRIP001  SdrObjList* pDstList = pLst;
//STRIP001     ImpGetPasteObjList(aPos, pDstList);
//STRIP001
//STRIP001  if(!pDstList)
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // Owner der Liste holen
//STRIP001  SdrObject* pOwner = pDstList->GetOwnerObj();
//STRIP001  if(pOwner && pOwner->ISA(E3dScene))
//STRIP001  {
//STRIP001      E3dScene* pDstScene = (E3dScene*)pOwner;
//STRIP001      BOOL bDstInserted(FALSE);
//STRIP001      BegUndo(SVX_RESSTR(RID_SVX_3D_UNDO_EXCHANGE_PASTE));
//STRIP001
//STRIP001      // Alle Objekte aus E3dScenes kopieren und direkt einfuegen
//STRIP001      for(sal_uInt16 nPg(0); nPg < rMod.GetPageCount(); nPg++)
//STRIP001      {
//STRIP001          const SdrPage* pSrcPg=rMod.GetPage(nPg);
//STRIP001          sal_uInt32 nObAnz(pSrcPg->GetObjCount());
//STRIP001
//STRIP001          // calculate offset for paste
//STRIP001          Rectangle aR = pSrcPg->GetAllObjBoundRect();
//STRIP001          Point aDist(aPos - aR.Center());
//STRIP001
//STRIP001          // Unterobjekte von Szenen einfuegen
//STRIP001          for(sal_uInt32 nOb(0); nOb < nObAnz; nOb++)
//STRIP001          {
//STRIP001              const SdrObject* pSrcOb = pSrcPg->GetObj(nOb);
//STRIP001              if(pSrcOb->ISA(E3dScene))
//STRIP001              {
//STRIP001                  E3dScene* pSrcScene = (E3dScene*)pSrcOb;
//STRIP001                  bDstInserted = ImpCloneAll3DObjectsToDestScene(pSrcScene, pDstScene, aDist);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      EndUndo();
//STRIP001
//STRIP001      // DestScene anpassen
//STRIP001      if(bDstInserted)
//STRIP001      {
//STRIP001          pDstScene->SetRectsDirty();
//STRIP001          pDstScene->CorrectSceneDimensions();
//STRIP001          bRetval = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // call parent
//STRIP001      bRetval = SdrView::Paste(rMod, rPos, pLst, nOptions);
//STRIP001  }
//STRIP001
//STRIP001  // und Rueckgabewert liefern
//STRIP001  return bRetval;
//STRIP001 }

// #83403# Service routine used from local Clone() and from SdrCreateView::EndCreateObj(...)
//STRIP001 BOOL E3dView::ImpCloneAll3DObjectsToDestScene(E3dScene* pSrcScene, E3dScene* pDstScene, Point aOffset)
//STRIP001 {
//STRIP001  BOOL bRetval(FALSE);
//STRIP001
//STRIP001  if(pSrcScene && pDstScene)
//STRIP001  {
//STRIP001      B3dCamera& rCameraSetDst = pDstScene->GetCameraSet();
//STRIP001      B3dCamera& rCameraSetSrc = pSrcScene->GetCameraSet();
//STRIP001
//STRIP001      for(sal_uInt32 i(0); i < pSrcScene->GetSubList()->GetObjCount(); i++)
//STRIP001      {
//STRIP001          SdrObject* pObj = pSrcScene->GetSubList()->GetObj(i);
//STRIP001          if(pObj && pObj->ISA(E3dCompoundObject))
//STRIP001          {
//STRIP001              // Kopieren
//STRIP001              E3dObject* pNew = (E3dObject*)pObj->Clone(pDstScene->GetPage(), pDstScene->GetModel());
//STRIP001              if(pNew)
//STRIP001              {
//STRIP001                  // Neues Objekt in Szene einfuegen
//STRIP001                  pNew->NbcSetLayer(pObj->GetLayer());
//STRIP001                  pNew->NbcSetStyleSheet(pObj->GetStyleSheet(), TRUE);
//STRIP001                  pDstScene->Insert3DObj(pNew);
//STRIP001                  bRetval = TRUE;
//STRIP001
//STRIP001                  // Transformation ObjectToEye Src
//STRIP001                  Matrix4D aMatSrc;
//STRIP001                  aMatSrc = ((E3dCompoundObject*)pObj)->GetFullTransform();
//STRIP001                  aMatSrc *= rCameraSetSrc.GetOrientation();
//STRIP001
//STRIP001                  // Tanslation und scale von source
//STRIP001                  B3dVolume aDevVolSrc = rCameraSetSrc.GetDeviceVolume();
//STRIP001
//STRIP001                  // auf Augkoordinaten umstellen
//STRIP001                  double fTemp = aDevVolSrc.MinVec().Z();
//STRIP001                  aDevVolSrc.MinVec().Z() = -aDevVolSrc.MaxVec().Z();
//STRIP001                  aDevVolSrc.MaxVec().Z() = -fTemp;
//STRIP001
//STRIP001                  Vector3D aProjScaleSrc(
//STRIP001                      2.0 / aDevVolSrc.GetWidth(),
//STRIP001                      2.0 / aDevVolSrc.GetHeight(),
//STRIP001                      2.0 / aDevVolSrc.GetDepth());
//STRIP001                  Vector3D aProjTransSrc(
//STRIP001                      -1.0 * ((aDevVolSrc.MaxVec().X() + aDevVolSrc.MinVec().X()) / aDevVolSrc.GetWidth()),
//STRIP001                      -1.0 * ((aDevVolSrc.MaxVec().Y() + aDevVolSrc.MinVec().Y()) / aDevVolSrc.GetHeight()),
//STRIP001                      -1.0 * ((aDevVolSrc.MaxVec().Z() + aDevVolSrc.MinVec().Z()) / aDevVolSrc.GetDepth()));
//STRIP001                  Vector3D aViewScaleSrc(rCameraSetSrc.GetScale());
//STRIP001                  aViewScaleSrc.Z() = 1.0;
//STRIP001
//STRIP001                  // Tanslation und scale von dest
//STRIP001                  B3dVolume aDevVolDst = rCameraSetDst.GetDeviceVolume();
//STRIP001
//STRIP001                  // auf Augkoordinaten umstellen
//STRIP001                  fTemp = aDevVolDst.MinVec().Z();
//STRIP001                  aDevVolDst.MinVec().Z() = -aDevVolDst.MaxVec().Z();
//STRIP001                  aDevVolDst.MaxVec().Z() = -fTemp;
//STRIP001
//STRIP001                  Vector3D aProjScaleDst(
//STRIP001                      2.0 / aDevVolDst.GetWidth(),
//STRIP001                      2.0 / aDevVolDst.GetHeight(),
//STRIP001                      2.0 / aDevVolDst.GetDepth());
//STRIP001                  Vector3D aProjTransDst(
//STRIP001                      -1.0 * ((aDevVolDst.MaxVec().X() + aDevVolDst.MinVec().X()) / aDevVolDst.GetWidth()),
//STRIP001                      -1.0 * ((aDevVolDst.MaxVec().Y() + aDevVolDst.MinVec().Y()) / aDevVolDst.GetHeight()),
//STRIP001                      -1.0 * ((aDevVolDst.MaxVec().Z() + aDevVolDst.MinVec().Z()) / aDevVolDst.GetDepth()));
//STRIP001                  Vector3D aViewScaleDst(rCameraSetDst.GetScale());
//STRIP001                  aViewScaleDst.Z() = 1.0;
//STRIP001
//STRIP001                  // Groesse des Objektes in Augkoordinaten Src
//STRIP001                  Volume3D aObjVolSrc;
//STRIP001                  aObjVolSrc.Union(((E3dCompoundObject*)pObj)->GetBoundVolume().GetTransformVolume(aMatSrc));
//STRIP001
//STRIP001                  // Vorlaeufige Groesse in Augkoordinaten Dst
//STRIP001                  Matrix4D aMatZwi = aMatSrc;
//STRIP001                  aMatZwi.Scale(aProjScaleSrc);
//STRIP001                  aMatZwi.Translate(aProjTransSrc);
//STRIP001                  aMatZwi.Scale(aViewScaleSrc);
//STRIP001
//STRIP001                  Matrix4D aMatDst;
//STRIP001                  aMatDst.Scale(aProjScaleDst);
//STRIP001                  aMatDst.Translate(aProjTransDst);
//STRIP001                  aMatDst.Scale(aViewScaleDst);
//STRIP001                  aMatDst.Invert();
//STRIP001
//STRIP001                  aMatZwi *= aMatDst;
//STRIP001
//STRIP001                  Volume3D aObjVolDst;
//STRIP001                  aObjVolDst.Union(((E3dCompoundObject*)pObj)->GetBoundVolume().GetTransformVolume(aMatZwi));
//STRIP001
//STRIP001                  // Beide verhaeltnistiefen berechnen und mitteln
//STRIP001                  double fDepthOne = (aObjVolSrc.GetDepth() * aObjVolDst.GetWidth()) / aObjVolSrc.GetWidth();
//STRIP001                  double fDepthTwo = (aObjVolSrc.GetDepth() * aObjVolDst.GetHeight()) / aObjVolSrc.GetHeight();
//STRIP001                  double fWantedDepth = (fDepthOne + fDepthTwo) / 2.0;
//STRIP001
//STRIP001                  // Faktor zum Tiefe anpassen bilden
//STRIP001                  double fFactor = fWantedDepth / aObjVolDst.GetDepth();
//STRIP001                  Vector3D aDepthScale(1.0, 1.0, fFactor);
//STRIP001
//STRIP001                  // Endgueltige Transformation bilden
//STRIP001                  aMatSrc.Scale(aProjScaleSrc);
//STRIP001                  aMatSrc.Translate(aProjTransSrc);
//STRIP001                  aMatSrc.Scale(aViewScaleSrc);
//STRIP001                  aMatSrc.Scale(aDepthScale);
//STRIP001
//STRIP001                  aMatDst = pDstScene->GetFullTransform();
//STRIP001                  aMatDst *= rCameraSetDst.GetOrientation();
//STRIP001                  aMatDst.Scale(aProjScaleDst);
//STRIP001                  aMatDst.Translate(aProjTransDst);
//STRIP001                  aMatDst.Scale(aViewScaleDst);
//STRIP001                  aMatDst.Invert();
//STRIP001
//STRIP001                  aMatSrc *= aMatDst;
//STRIP001
//STRIP001                  // Neue Objekttransformation setzen
//STRIP001                  pNew->SetTransform(aMatSrc);
//STRIP001
//STRIP001                  // force new camera and SnapRect on scene, geometry may have really
//STRIP001                  // changed
//STRIP001                  pDstScene->CorrectSceneDimensions();
//STRIP001
//STRIP001                  // #83403# translate in view coor
//STRIP001                  {
//STRIP001                      // screen position of center of old object
//STRIP001                      Matrix4D aSrcFullTrans = ((E3dCompoundObject*)pObj)->GetFullTransform();
//STRIP001                      rCameraSetSrc.SetObjectTrans(aSrcFullTrans);
//STRIP001                      Vector3D aSrcCenter = ((E3dCompoundObject*)pObj)->GetCenter();
//STRIP001                      aSrcCenter = rCameraSetSrc.ObjectToViewCoor(aSrcCenter);
//STRIP001                      if(aOffset.X() != 0 || aOffset.Y() != 0)
//STRIP001                          aSrcCenter += Vector3D((double)aOffset.X(), (double)aOffset.Y(), 0.0);
//STRIP001
//STRIP001                      // to have a valid Z-Coor in dst system, calc current center of dst object
//STRIP001                      Matrix4D aDstFullTrans = pNew->GetFullTransform();
//STRIP001                      rCameraSetDst.SetObjectTrans(aDstFullTrans);
//STRIP001                      Vector3D aDstCenter = pNew->GetCenter();
//STRIP001                      aDstCenter = rCameraSetDst.ObjectToEyeCoor(aDstCenter);
//STRIP001
//STRIP001                      // convert aSrcCenter to a eye position of dst scene
//STRIP001                      Vector3D aNewDstCenter = rCameraSetDst.ViewToEyeCoor(aSrcCenter);
//STRIP001                      aNewDstCenter.Z() = aDstCenter.Z();
//STRIP001
//STRIP001                      // transform back to object coor
//STRIP001                      aNewDstCenter = rCameraSetDst.EyeToObjectCoor(aNewDstCenter);
//STRIP001
//STRIP001                      // get transform vector
//STRIP001                      Vector3D aTransformCorrection = aNewDstCenter - pNew->GetCenter();
//STRIP001                      Matrix4D aTransCorrMat;
//STRIP001                      aTransCorrMat.Translate(aTransformCorrection);
//STRIP001
//STRIP001                      // treanslate new object, add translate in front of obj transform
//STRIP001                      pNew->SetTransform(aTransCorrMat * pNew->GetTransform());
//STRIP001
//STRIP001                      // force new camera and SnapRect on scene, geometry may have really
//STRIP001                      // changed
//STRIP001                      pDstScene->CorrectSceneDimensions();
//STRIP001
//STRIP001                      //Rectangle aOldPosSize = pObj->GetSnapRect();
//STRIP001                      //if(aOffset.X() != 0 || aOffset.Y() != 0)
//STRIP001                      //  aOldPosSize.Move(aOffset.X(), aOffset.Y());
//STRIP001                      //Rectangle aNewPosSize = pNew->GetSnapRect();
//STRIP001                  }
//STRIP001
//STRIP001                  // Undo anlegen
//STRIP001                  AddUndo(new SdrUndoNewObj(*pNew));
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return bRetval;
//STRIP001 }

/*************************************************************************
|*
|* 3D-Konvertierung moeglich?
|*
\************************************************************************/

/*N*/ BOOL E3dView::IsConvertTo3DObjPossible() const
/*N*/ {
/*N*/   BOOL bAny3D(FALSE);
/*N*/   BOOL bGroupSelected(FALSE);
/*N*/   BOOL bRetval(TRUE);
/*N*/
/*N*/   for(sal_uInt32 a=0;!bAny3D && a<aMark.GetMarkCount();a++)
/*N*/   {
/*?*/       SdrObject *pObj = aMark.GetMark(a)->GetObj();
/*?*/       if(pObj)
/*?*/       {
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 ImpIsConvertTo3DPossible(pObj, bAny3D, bGroupSelected);
/*?*/       }
/*N*/   }
/*N*/
/*N*/   bRetval = !bAny3D
/*N*/       && (
/*N*/          IsConvertToPolyObjPossible(FALSE)
/*N*/       || IsConvertToPathObjPossible(FALSE)
/*N*/       || IsImportMtfPossible());
/*N*/   return bRetval;
/*N*/ }

//STRIP001 void E3dView::ImpIsConvertTo3DPossible(SdrObject* pObj, BOOL& rAny3D,
//STRIP001  BOOL& rGroupSelected) const
//STRIP001 {
//STRIP001  if(pObj)
//STRIP001  {
//STRIP001      if(pObj->ISA(E3dObject))
//STRIP001      {
//STRIP001          rAny3D = TRUE;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if(pObj->IsGroupObject())
//STRIP001          {
//STRIP001              SdrObjListIter aIter(*pObj, IM_DEEPNOGROUPS);
//STRIP001              while(aIter.IsMore())
//STRIP001              {
//STRIP001                  SdrObject* pNewObj = aIter.Next();
//STRIP001                  ImpIsConvertTo3DPossible(pNewObj, rAny3D, rGroupSelected);
//STRIP001              }
//STRIP001              rGroupSelected = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* 3D-Konvertierung zu Extrude ausfuehren
|*
\************************************************************************/

#ifndef _EEITEM_HXX
#include "eeitem.hxx"
#endif

//STRIP001 void E3dView::ImpChangeSomeAttributesFor3DConversion(SdrObject* pObj)
//STRIP001 {
//STRIP001  if(pObj->ISA(SdrTextObj))
//STRIP001  {
//STRIP001      const SfxItemSet& rSet = pObj->GetItemSet();
//STRIP001      const SvxColorItem& rTextColorItem = (const SvxColorItem&)rSet.Get(EE_CHAR_COLOR);
//STRIP001      if(rTextColorItem.GetValue() == RGB_Color(COL_BLACK))
//STRIP001      {
//STRIP001          // Bei schwarzen Textobjekten wird die Farbe auf grau gesetzt
//STRIP001          if(pObj->GetPage())
//STRIP001          {
//STRIP001              // #84864# if black is only default attribute from
//STRIP001              // pattern set it hard so that it is used in undo.
//STRIP001              pObj->SetItem(SvxColorItem(RGB_Color(COL_BLACK), EE_CHAR_COLOR));
//STRIP001
//STRIP001              // add undo now
//STRIP001              AddUndo(new SdrUndoAttrObj(*pObj, FALSE, FALSE));
//STRIP001          }
//STRIP001          pObj->SetItem(SvxColorItem(RGB_Color(COL_GRAY), EE_CHAR_COLOR));
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void E3dView::ImpChangeSomeAttributesFor3DConversion2(SdrObject* pObj)
//STRIP001 {
//STRIP001  if(pObj->ISA(SdrPathObj))
//STRIP001  {
//STRIP001      const SfxItemSet& rSet = pObj->GetItemSet();
//STRIP001      sal_Int32 nLineWidth = ((const XLineWidthItem&)(rSet.Get(XATTR_LINEWIDTH))).GetValue();
//STRIP001      XLineStyle eLineStyle = (XLineStyle)((const XLineStyleItem&)rSet.Get(XATTR_LINESTYLE)).GetValue();
//STRIP001      XFillStyle eFillStyle = ITEMVALUE(rSet, XATTR_FILLSTYLE, XFillStyleItem);
//STRIP001
//STRIP001      if(((SdrPathObj*)pObj)->IsClosed()
//STRIP001          && eLineStyle == XLINE_SOLID
//STRIP001          && !nLineWidth
//STRIP001          && eFillStyle != XFILL_NONE)
//STRIP001      {
//STRIP001          if(pObj->GetPage())
//STRIP001              AddUndo(new SdrUndoAttrObj(*pObj, FALSE, FALSE));
//STRIP001          pObj->SetItem(XLineStyleItem(XLINE_NONE));
//STRIP001          pObj->SetItem(XLineWidthItem(0L));
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void E3dView::ImpCreateSingle3DObjectFlat(E3dScene* pScene, SdrObject* pObj, BOOL bExtrude, double fDepth, Matrix4D& rLatheMat)
//STRIP001 {
//STRIP001  // Einzelnes PathObject, dieses umwanden
//STRIP001  SdrPathObj* pPath = PTR_CAST(SdrPathObj, pObj);
//STRIP001
//STRIP001  if(pPath)
//STRIP001  {
//STRIP001      E3dDefaultAttributes aDefault = Get3DDefaultAttributes();
//STRIP001      if(bExtrude)
//STRIP001          aDefault.SetDefaultExtrudeCharacterMode(TRUE);
//STRIP001      else
//STRIP001          aDefault.SetDefaultLatheCharacterMode(TRUE);
//STRIP001
//STRIP001      // ItemSet des Ursprungsobjektes holen
//STRIP001      SfxItemSet aSet(pObj->GetItemSet());
//STRIP001
//STRIP001      XFillStyle eFillStyle = ITEMVALUE(aSet, XATTR_FILLSTYLE, XFillStyleItem);
//STRIP001
//STRIP001      // Linienstil ausschalten
//STRIP001      aSet.Put(XLineStyleItem(XLINE_NONE));
//STRIP001
//STRIP001      // Feststellen, ob ein FILL_Attribut gesetzt ist.
//STRIP001      if(!pPath->IsClosed() || eFillStyle == XFILL_NONE)
//STRIP001      {
//STRIP001          // Das SdrPathObj ist nicht gefuellt, lasse die
//STRIP001          // vordere und hintere Flaeche weg. Ausserdem ist
//STRIP001          // eine beidseitige Darstellung notwendig.
//STRIP001          aDefault.SetDefaultExtrudeCloseFront(FALSE);
//STRIP001          aDefault.SetDefaultExtrudeCloseBack(FALSE);
//STRIP001
//STRIP001          aSet.Put(Svx3DDoubleSidedItem(TRUE));
//STRIP001
//STRIP001          // Fuellattribut setzen
//STRIP001          aSet.Put(XFillStyleItem(XFILL_SOLID));
//STRIP001
//STRIP001          // Fuellfarbe muss auf Linienfarbe, da das Objekt vorher
//STRIP001          // nur eine Linie war
//STRIP001          Color aColorLine = ((const XLineColorItem&)(aSet.Get(XATTR_LINECOLOR))).GetValue();
//STRIP001          aSet.Put(XFillColorItem(String(), aColorLine));
//STRIP001      }
//STRIP001
//STRIP001      // Neues Extrude-Objekt erzeugen
//STRIP001      E3dObject* p3DObj = NULL;
//STRIP001      if(bExtrude)
//STRIP001      {
//STRIP001          p3DObj = new E3dExtrudeObj(aDefault, pPath->GetPathPoly(), fDepth);
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          PolyPolygon3D aPolyPoly3D(pPath->GetPathPoly(), aDefault.GetDefaultLatheScale());
//STRIP001          aPolyPoly3D.Transform(rLatheMat);
//STRIP001          p3DObj = new E3dLatheObj(aDefault, aPolyPoly3D);
//STRIP001      }
//STRIP001
//STRIP001      // Attribute setzen
//STRIP001      if(p3DObj)
//STRIP001      {
//STRIP001          p3DObj->NbcSetLayer(pObj->GetLayer());
//STRIP001
//STRIP001          p3DObj->SetItemSet(aSet);
//STRIP001
//STRIP001          p3DObj->NbcSetStyleSheet(pObj->GetStyleSheet(), TRUE);
//STRIP001
//STRIP001          // Neues 3D-Objekt einfuegen
//STRIP001          pScene->Insert3DObj(p3DObj);
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void E3dView::ImpCreate3DObject(E3dScene* pScene, SdrObject* pObj, BOOL bExtrude, double fDepth, Matrix4D& rLatheMat)
//STRIP001 {
//STRIP001  if(pObj)
//STRIP001  {
//STRIP001      // change text color attribute for not so dark colors
//STRIP001      if(pObj->IsGroupObject())
//STRIP001      {
//STRIP001          SdrObjListIter aIter(*pObj, IM_DEEPWITHGROUPS);
//STRIP001          while(aIter.IsMore())
//STRIP001          {
//STRIP001              SdrObject* pGroupMember = aIter.Next();
//STRIP001              ImpChangeSomeAttributesFor3DConversion(pGroupMember);
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001          ImpChangeSomeAttributesFor3DConversion(pObj);
//STRIP001
//STRIP001      // convert completely to path objects
//STRIP001      SdrObject* pNewObj1 = pObj->ConvertToPolyObj(FALSE, FALSE);
//STRIP001
//STRIP001      if(pNewObj1)
//STRIP001      {
//STRIP001          // change text color attribute for not so dark colors
//STRIP001          if(pNewObj1->IsGroupObject())
//STRIP001          {
//STRIP001              SdrObjListIter aIter(*pNewObj1, IM_DEEPWITHGROUPS);
//STRIP001              while(aIter.IsMore())
//STRIP001              {
//STRIP001                  SdrObject* pGroupMember = aIter.Next();
//STRIP001                  ImpChangeSomeAttributesFor3DConversion2(pGroupMember);
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001              ImpChangeSomeAttributesFor3DConversion2(pNewObj1);
//STRIP001
//STRIP001          // convert completely to path objects
//STRIP001          SdrObject* pNewObj2 = pObj->ConvertToContourObj(pNewObj1, TRUE);
//STRIP001
//STRIP001          if(pNewObj2)
//STRIP001          {
//STRIP001              // add all to flat scene
//STRIP001              if(pNewObj2->IsGroupObject())
//STRIP001              {
//STRIP001                  SdrObjListIter aIter(*pNewObj2, IM_DEEPWITHGROUPS);
//STRIP001                  while(aIter.IsMore())
//STRIP001                  {
//STRIP001                      SdrObject* pGroupMember = aIter.Next();
//STRIP001                      ImpCreateSingle3DObjectFlat(pScene, pGroupMember, bExtrude, fDepth, rLatheMat);
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001                  ImpCreateSingle3DObjectFlat(pScene, pNewObj2, bExtrude, fDepth, rLatheMat);
//STRIP001
//STRIP001              // delete zwi object
//STRIP001              if(pNewObj2 != pObj && pNewObj2 != pNewObj1 && pNewObj2)
//STRIP001                  delete pNewObj2;
//STRIP001          }
//STRIP001
//STRIP001          // delete zwi object
//STRIP001          if(pNewObj1 != pObj && pNewObj1)
//STRIP001              delete pNewObj1;
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* 3D-Konvertierung zu Extrude steuern
|*
\************************************************************************/

//STRIP001 void E3dView::ConvertMarkedObjTo3D(BOOL bExtrude, Vector3D aPnt1, Vector3D aPnt2)
//STRIP001 {
//STRIP001  if(HasMarkedObj())
//STRIP001  {
//STRIP001      // Undo anlegen
//STRIP001         if(bExtrude)
//STRIP001          BegUndo(SVX_RESSTR(RID_SVX_3D_UNDO_EXTRUDE));
//STRIP001      else
//STRIP001          BegUndo(SVX_RESSTR(RID_SVX_3D_UNDO_LATHE));
//STRIP001
//STRIP001      // Neue Szene fuer zu erzeugende 3D-Objekte anlegen
//STRIP001         E3dScene* pScene = new E3dPolyScene(Get3DDefaultAttributes());
//STRIP001
//STRIP001      // Rechteck bestimmen und evtl. korrigieren
//STRIP001      Rectangle aRect = GetAllMarkedRect();
//STRIP001      if(aRect.GetWidth() <= 1)
//STRIP001          aRect.SetSize(Size(500, aRect.GetHeight()));
//STRIP001      if(aRect.GetHeight() <= 1)
//STRIP001          aRect.SetSize(Size(aRect.GetWidth(), 500));
//STRIP001
//STRIP001      // Tiefe relativ zur Groesse der Selektion bestimmen
//STRIP001      double fDepth = 0.0;
//STRIP001      double fRot3D = 0.0;
//STRIP001      Matrix4D aLatheMat;
//STRIP001
//STRIP001      if(bExtrude)
//STRIP001      {
//STRIP001          double fW = (double)aRect.GetWidth();
//STRIP001          double fH = (double)aRect.GetHeight();
//STRIP001          fDepth = sqrt(fW*fW + fH*fH) / 6.0;
//STRIP001      }
//STRIP001      if(!bExtrude)
//STRIP001      {
//STRIP001          // Transformation fuer Polygone Rotationskoerper erstellen
//STRIP001          if(aPnt1 != aPnt2)
//STRIP001          {
//STRIP001              // Rotation um Kontrollpunkt1 mit eigestelltem Winkel
//STRIP001              // fuer 3D Koordinaten
//STRIP001              Vector3D aDiff = aPnt1 - aPnt2;
//STRIP001              fRot3D = atan2(aDiff.Y(), aDiff.X()) - F_PI2;
//STRIP001
//STRIP001              if(fabs(fRot3D) < SMALL_DVALUE)
//STRIP001                  fRot3D = 0.0;
//STRIP001
//STRIP001              if(fRot3D != 0.0)
//STRIP001              {
//STRIP001                  aLatheMat.Translate(-aPnt2);
//STRIP001                  aLatheMat.RotateZ(-fRot3D);
//STRIP001                  aLatheMat.Translate(aPnt2);
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          if(aPnt2.X() != 0.0)
//STRIP001          {
//STRIP001              // Translation auf Y=0 - Achse
//STRIP001              aLatheMat.TranslateX(-aPnt2.X());
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              aLatheMat.Translate((double)-aRect.Left());
//STRIP001          }
//STRIP001
//STRIP001          // Inverse Matrix bilden, um die Zielausdehnung zu bestimmen
//STRIP001          Matrix4D aInvLatheMat = aLatheMat;
//STRIP001          aInvLatheMat.Invert();
//STRIP001
//STRIP001          // SnapRect Ausdehnung mittels Spiegelung an der Rotationsachse
//STRIP001          // erweitern
//STRIP001          for(UINT32 a=0;a<aMark.GetMarkCount();a++)
//STRIP001          {
//STRIP001              SdrMark* pMark = aMark.GetMark(a);
//STRIP001              SdrObject* pObj = pMark->GetObj();
//STRIP001              Rectangle aTurnRect = pObj->GetSnapRect();
//STRIP001              Vector3D aRot;
//STRIP001              Point aRotPnt;
//STRIP001
//STRIP001              aRot = Vector3D(aTurnRect.Left(), -aTurnRect.Top(), 0.0);
//STRIP001              aRot *= aLatheMat;
//STRIP001              aRot.X() = -aRot.X();
//STRIP001              aRot *= aInvLatheMat;
//STRIP001              aRotPnt = Point((long)(aRot.X() + 0.5), (long)(-aRot.Y() - 0.5));
//STRIP001              aRect.Union(Rectangle(aRotPnt, aRotPnt));
//STRIP001
//STRIP001              aRot = Vector3D(aTurnRect.Left(), -aTurnRect.Bottom(), 0.0);
//STRIP001              aRot *= aLatheMat;
//STRIP001              aRot.X() = -aRot.X();
//STRIP001              aRot *= aInvLatheMat;
//STRIP001              aRotPnt = Point((long)(aRot.X() + 0.5), (long)(-aRot.Y() - 0.5));
//STRIP001              aRect.Union(Rectangle(aRotPnt, aRotPnt));
//STRIP001
//STRIP001              aRot = Vector3D(aTurnRect.Right(), -aTurnRect.Top(), 0.0);
//STRIP001              aRot *= aLatheMat;
//STRIP001              aRot.X() = -aRot.X();
//STRIP001              aRot *= aInvLatheMat;
//STRIP001              aRotPnt = Point((long)(aRot.X() + 0.5), (long)(-aRot.Y() - 0.5));
//STRIP001              aRect.Union(Rectangle(aRotPnt, aRotPnt));
//STRIP001
//STRIP001              aRot = Vector3D(aTurnRect.Right(), -aTurnRect.Bottom(), 0.0);
//STRIP001              aRot *= aLatheMat;
//STRIP001              aRot.X() = -aRot.X();
//STRIP001              aRot *= aInvLatheMat;
//STRIP001              aRotPnt = Point((long)(aRot.X() + 0.5), (long)(-aRot.Y() - 0.5));
//STRIP001              aRect.Union(Rectangle(aRotPnt, aRotPnt));
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // Ueber die Selektion gehen und in 3D wandeln, komplett mit
//STRIP001      // Umwandeln in SdrPathObject, auch Schriften
//STRIP001      for(UINT32 a=0;a<aMark.GetMarkCount();a++)
//STRIP001      {
//STRIP001          SdrMark* pMark = aMark.GetMark(a);
//STRIP001          SdrObject* pObj = pMark->GetObj();
//STRIP001
//STRIP001          ImpCreate3DObject(pScene, pObj, bExtrude, fDepth, aLatheMat);
//STRIP001      }
//STRIP001
//STRIP001      if(pScene->GetSubList() && pScene->GetSubList()->GetObjCount() != 0)
//STRIP001      {
//STRIP001          // Alle angelegten Objekte Tiefenarrangieren
//STRIP001          if(bExtrude)
//STRIP001              DoDepthArrange(pScene, fDepth);
//STRIP001
//STRIP001          // 3D-Objekte auf die Mitte des Gesamtrechtecks zentrieren
//STRIP001          Vector3D aCenter = pScene->GetCenter();
//STRIP001          Matrix4D aMatrix;
//STRIP001
//STRIP001             aMatrix.Translate(-aCenter);
//STRIP001          pScene->SetTransform(pScene->GetTransform() * aMatrix);
//STRIP001
//STRIP001          // Szene initialisieren
//STRIP001          pScene->NbcSetSnapRect(aRect);
//STRIP001          Volume3D aBoundVol = pScene->GetBoundVolume();
//STRIP001          InitScene(pScene, (double)aRect.GetWidth(),
//STRIP001              (double)aRect.GetHeight(), aBoundVol.GetDepth());
//STRIP001
//STRIP001          // Transformationen initialisieren, damit bei RecalcSnapRect()
//STRIP001          // richtig gerechnet wird
//STRIP001          pScene->InitTransformationSet();
//STRIP001
//STRIP001          // Szene anstelle des ersten selektierten Objektes einfuegen
//STRIP001          // und alle alten Objekte weghauen
//STRIP001          SdrObject* pRepObj = aMark.GetMark(0)->GetObj();
//STRIP001          SdrPageView* pPV = aMark.GetMark(0)->GetPageView();
//STRIP001          MarkObj(pRepObj, pPV, TRUE);
//STRIP001          ReplaceObject(pRepObj, *pPV, pScene, FALSE);
//STRIP001          DeleteMarked();
//STRIP001          MarkObj(pScene, pPV);
//STRIP001
//STRIP001          // Rotationskoerper um Rotationsachse drehen
//STRIP001          if(!bExtrude && fRot3D != 0.0)
//STRIP001          {
//STRIP001              pScene->RotateZ(fRot3D);
//STRIP001          }
//STRIP001
//STRIP001          // Default-Rotation setzen
//STRIP001             double XRotateDefault = 20;
//STRIP001             pScene->RotateX(DEG2RAD(XRotateDefault));
//STRIP001             pScene->SetSortingMode(E3D_SORT_FAST_SORTING|E3D_SORT_IN_PARENTS|E3D_SORT_TEST_LENGTH);
//STRIP001
//STRIP001          // SnapRects der Objekte ungueltig
//STRIP001          pScene->CorrectSceneDimensions();
//STRIP001          pScene->SetSnapRect(aRect);
//STRIP001      }
//STRIP001      else
//STRIP001         {
//STRIP001          // Es wurden keine 3D Objekte erzeugt, schmeiss alles weg
//STRIP001          delete pScene;
//STRIP001         }
//STRIP001
//STRIP001      // Undo abschliessen
//STRIP001         EndUndo();
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Alle enthaltenen Extrude-Objekte Tiefenarrangieren
|*
\************************************************************************/

//STRIP001 struct E3dDepthNeighbour
//STRIP001 {
//STRIP001  E3dDepthNeighbour*  pNext;
//STRIP001  E3dExtrudeObj*      pObj;
//STRIP001
//STRIP001  E3dDepthNeighbour() { pNext = NULL; pObj = NULL; }
//STRIP001 };

//STRIP001 struct E3dDepthLayer
//STRIP001 {
//STRIP001  E3dDepthLayer*      pDown;
//STRIP001  E3dDepthNeighbour*  pNext;
//STRIP001
//STRIP001  E3dDepthLayer() { pDown = NULL; pNext = NULL; }
//STRIP001  ~E3dDepthLayer() { while(pNext) { E3dDepthNeighbour* pSucc = pNext->pNext; delete pNext; pNext = pSucc; }}
//STRIP001 };

//STRIP001 void E3dView::DoDepthArrange(E3dScene* pScene, double fDepth)
//STRIP001 {
//STRIP001  if(pScene && pScene->GetSubList() && pScene->GetSubList()->GetObjCount() > 1)
//STRIP001  {
//STRIP001      SdrObjList* pSubList = pScene->GetSubList();
//STRIP001      SdrObjListIter aIter(*pSubList, IM_FLAT);
//STRIP001      E3dDepthLayer* pBaseLayer = NULL;
//STRIP001      E3dDepthLayer* pLayer = NULL;
//STRIP001      INT32 nNumLayers = 0;
//STRIP001      SfxItemPool& rPool = pMod->GetItemPool();
//STRIP001
//STRIP001      while(aIter.IsMore())
//STRIP001      {
//STRIP001          E3dObject* pSubObj = (E3dObject*)aIter.Next();
//STRIP001
//STRIP001          if(pSubObj && pSubObj->ISA(E3dExtrudeObj))
//STRIP001          {
//STRIP001              E3dExtrudeObj* pExtrudeObj = (E3dExtrudeObj*)pSubObj;
//STRIP001              const PolyPolygon3D& rExtrudePoly = pExtrudeObj->GetExtrudePolygon();
//STRIP001
//STRIP001              const SfxItemSet& rLocalSet = pExtrudeObj->GetItemSet();
//STRIP001              XFillStyle eLocalFillStyle = ITEMVALUE(rLocalSet, XATTR_FILLSTYLE, XFillStyleItem);
//STRIP001              Color aLocalColor = ((const XFillColorItem&)(rLocalSet.Get(XATTR_FILLCOLOR))).GetValue();
//STRIP001
//STRIP001              // ExtrudeObj einordnen
//STRIP001              if(pLayer)
//STRIP001              {
//STRIP001                  // Gibt es eine Ueberschneidung mit einem Objekt dieses
//STRIP001                  // Layers?
//STRIP001                  BOOL bOverlap(FALSE);
//STRIP001                  E3dDepthNeighbour* pAct = pLayer->pNext;
//STRIP001
//STRIP001                  while(!bOverlap && pAct)
//STRIP001                  {
//STRIP001                      // ueberlappen sich pAct->pObj und pExtrudeObj ?
//STRIP001                      const PolyPolygon3D& rActPoly = pAct->pObj->GetExtrudePolygon();
//STRIP001                      bOverlap = rExtrudePoly.DoesOverlap(rActPoly, DEGREE_FLAG_X|DEGREE_FLAG_Y);
//STRIP001
//STRIP001                      if(bOverlap)
//STRIP001                      {
//STRIP001                          // second ciriteria: is another fillstyle or color used?
//STRIP001                          const SfxItemSet& rCompareSet = pAct->pObj->GetItemSet();
//STRIP001
//STRIP001                          XFillStyle eCompareFillStyle = ITEMVALUE(rCompareSet, XATTR_FILLSTYLE, XFillStyleItem);
//STRIP001
//STRIP001                          if(eLocalFillStyle == eCompareFillStyle)
//STRIP001                          {
//STRIP001                              if(eLocalFillStyle == XFILL_SOLID)
//STRIP001                              {
//STRIP001                                  Color aCompareColor = ((const XFillColorItem&)(rCompareSet.Get(XATTR_FILLCOLOR))).GetValue();
//STRIP001
//STRIP001                                  if(aCompareColor == aLocalColor)
//STRIP001                                  {
//STRIP001                                      bOverlap = FALSE;
//STRIP001                                  }
//STRIP001                              }
//STRIP001                              else if(eLocalFillStyle == XFILL_NONE)
//STRIP001                              {
//STRIP001                                  bOverlap = FALSE;
//STRIP001                              }
//STRIP001                          }
//STRIP001                      }
//STRIP001
//STRIP001                      pAct = pAct->pNext;
//STRIP001                  }
//STRIP001
//STRIP001                  if(bOverlap)
//STRIP001                  {
//STRIP001                      // ja, beginne einen neuen Layer
//STRIP001                      pLayer->pDown = new E3dDepthLayer;
//STRIP001                      pLayer = pLayer->pDown;
//STRIP001                      nNumLayers++;
//STRIP001                      pLayer->pNext = new E3dDepthNeighbour;
//STRIP001                      pLayer->pNext->pObj = pExtrudeObj;
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      // nein, Objekt kann in aktuellen Layer
//STRIP001                      E3dDepthNeighbour* pNewNext = new E3dDepthNeighbour;
//STRIP001                      pNewNext->pObj = pExtrudeObj;
//STRIP001                      pNewNext->pNext = pLayer->pNext;
//STRIP001                      pLayer->pNext = pNewNext;
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  // erster Layer ueberhaupt
//STRIP001                  pBaseLayer = new E3dDepthLayer;
//STRIP001                  pLayer = pBaseLayer;
//STRIP001                  nNumLayers++;
//STRIP001                  pLayer->pNext = new E3dDepthNeighbour;
//STRIP001                  pLayer->pNext->pObj = pExtrudeObj;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // Anzahl Layer steht fest
//STRIP001      if(nNumLayers > 1)
//STRIP001      {
//STRIP001          // Arrangement ist notwendig
//STRIP001          double fMinDepth = fDepth * 0.8;
//STRIP001          double fStep = (fDepth - fMinDepth) / (double)nNumLayers;
//STRIP001          pLayer = pBaseLayer;
//STRIP001
//STRIP001          while(pLayer)
//STRIP001          {
//STRIP001              // an pLayer entlangspazieren
//STRIP001              E3dDepthNeighbour* pAct = pLayer->pNext;
//STRIP001
//STRIP001              while(pAct)
//STRIP001              {
//STRIP001                  // Anpassen
//STRIP001                  pAct->pObj->SetItem(SfxUInt32Item(SDRATTR_3DOBJ_DEPTH, sal_uInt32(fMinDepth + 0.5)));
//STRIP001
//STRIP001                  // Naechster Eintrag
//STRIP001                  pAct = pAct->pNext;
//STRIP001              }
//STRIP001
//STRIP001              // naechster Layer
//STRIP001              pLayer = pLayer->pDown;
//STRIP001              fMinDepth += fStep;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // angelegte Strukturen aufraeumen
//STRIP001      while(pBaseLayer)
//STRIP001      {
//STRIP001          pLayer = pBaseLayer->pDown;
//STRIP001          delete pBaseLayer;
//STRIP001          pBaseLayer = pLayer;
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Drag beginnen, vorher ggf. Drag-Methode fuer 3D-Objekte erzeugen
|*
\************************************************************************/

//STRIP001 BOOL E3dView::BegDragObj(const Point& rPnt, OutputDevice* pOut,
//STRIP001  SdrHdl* pHdl, short nMinMov,
//STRIP001  SdrDragMethod* pForcedMeth)
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001     if (b3dCreationActive && aMark.GetMarkCount())
//STRIP001  {
//STRIP001      // bestimme alle selektierten Polygone und gebe die gespiegelte Hilfsfigur aus
//STRIP001         if (!pMirrorPolygon && !pMirroredPolygon)
//STRIP001      {
//STRIP001          CreateMirrorPolygons ();
//STRIP001          ShowMirrorPolygons (aRef1, aRef2);
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001     {
//STRIP001         BOOL bOwnActionNecessary;
//STRIP001         if (pHdl == NULL)
//STRIP001         {
//STRIP001            bOwnActionNecessary = TRUE;
//STRIP001         }
//STRIP001         else if (pHdl->IsVertexHdl() || pHdl->IsCornerHdl())
//STRIP001         {
//STRIP001            bOwnActionNecessary = TRUE;
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001            bOwnActionNecessary = FALSE;
//STRIP001         }
//STRIP001
//STRIP001         if(bOwnActionNecessary && aMark.GetMarkCount() >= 1)
//STRIP001         {
//STRIP001             E3dDragConstraint eConstraint = E3DDRAG_CONSTR_XYZ;
//STRIP001          BOOL bThereAreRootScenes = FALSE;
//STRIP001          BOOL bThereAre3DObjects = FALSE;
//STRIP001          long nCnt = aMark.GetMarkCount();
//STRIP001          for(long nObjs = 0;nObjs < nCnt;nObjs++)
//STRIP001          {
//STRIP001              SdrObject *pObj = aMark.GetMark(nObjs)->GetObj();
//STRIP001              if(pObj)
//STRIP001              {
//STRIP001                  if(pObj->ISA(E3dScene) && ((E3dScene*)pObj)->GetScene() == pObj)
//STRIP001                      bThereAreRootScenes = TRUE;
//STRIP001                  if(pObj->ISA(E3dObject))
//STRIP001                      bThereAre3DObjects = TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001          if( bThereAre3DObjects )
//STRIP001          {
//STRIP001                 eDragHdl = ( pHdl == NULL ? HDL_MOVE : pHdl->GetKind() );
//STRIP001                 switch ( eDragMode )
//STRIP001                 {
//STRIP001                     case SDRDRAG_ROTATE:
//STRIP001                     case SDRDRAG_SHEAR:
//STRIP001                     {
//STRIP001                         switch ( eDragHdl )
//STRIP001                         {
//STRIP001                             case HDL_LEFT:
//STRIP001                             case HDL_RIGHT:
//STRIP001                             {
//STRIP001                                 eConstraint = E3DDRAG_CONSTR_X;
//STRIP001                             }
//STRIP001                             break;
//STRIP001
//STRIP001                             case HDL_UPPER:
//STRIP001                             case HDL_LOWER:
//STRIP001                             {
//STRIP001                                 eConstraint = E3DDRAG_CONSTR_Y;
//STRIP001                             }
//STRIP001                             break;
//STRIP001
//STRIP001                             case HDL_UPLFT:
//STRIP001                             case HDL_UPRGT:
//STRIP001                             case HDL_LWLFT:
//STRIP001                             case HDL_LWRGT:
//STRIP001                             {
//STRIP001                                 eConstraint = E3DDRAG_CONSTR_Z;
//STRIP001                             }
//STRIP001                             break;
//STRIP001                         }
//STRIP001
//STRIP001                         // die nicht erlaubten Rotationen ausmaskieren
//STRIP001                         eConstraint = E3dDragConstraint(eConstraint& eDragConstraint);
//STRIP001                         pForcedMeth = new E3dDragRotate(*this, aMark, eDragDetail, eConstraint,
//STRIP001                                                      SvtOptions3D().IsShowFull() );
//STRIP001                     }
//STRIP001                     break;
//STRIP001
//STRIP001                     case SDRDRAG_MOVE:
//STRIP001                     {
//STRIP001                         if(!bThereAreRootScenes)
//STRIP001                      {
//STRIP001                          pForcedMeth = new E3dDragMove(*this, aMark, eDragDetail, eDragHdl, eConstraint,
//STRIP001                                                        SvtOptions3D().IsShowFull() );
//STRIP001                      }
//STRIP001                     }
//STRIP001                     break;
//STRIP001
//STRIP001                     // spaeter mal
//STRIP001                     case SDRDRAG_MIRROR:
//STRIP001                     case SDRDRAG_CROOK:
//STRIP001                     case SDRDRAG_DISTORT:
//STRIP001                     case SDRDRAG_TRANSPARENCE:
//STRIP001                     case SDRDRAG_GRADIENT:
//STRIP001                     default:
//STRIP001                     {
//STRIP001                      long nCnt = aMark.GetMarkCount();
//STRIP001                      for(long nObjs = 0;nObjs < nCnt;nObjs++)
//STRIP001                      {
//STRIP001                          SdrObject *pObj = aMark.GetMark(nObjs)->GetObj();
//STRIP001                          if(pObj && pObj->ISA(E3dObject))
//STRIP001                              ((E3dObject*) pObj)->SetDragDetail(eDragDetail);
//STRIP001                      }
//STRIP001                     }
//STRIP001                     break;
//STRIP001                 }
//STRIP001          }
//STRIP001         }
//STRIP001     }
//STRIP001     return SdrView::BegDragObj(rPnt, pOut, pHdl, nMinMov, pForcedMeth);
//STRIP001 #else
//STRIP001  return sal_False;
//STRIP001 #endif
//STRIP001 }

/*************************************************************************
|*
|* Pruefen, obj 3D-Szene markiert ist
|*
\************************************************************************/

//STRIP001 BOOL E3dView::HasMarkedScene()
//STRIP001 {
//STRIP001  return (GetMarkedScene() != NULL);
//STRIP001 }

/*************************************************************************
|*
|* Pruefen, obj 3D-Szene markiert ist
|*
\************************************************************************/

//STRIP001 E3dScene* E3dView::GetMarkedScene()
//STRIP001 {
//STRIP001  ULONG nCnt = aMark.GetMarkCount();
//STRIP001
//STRIP001  for ( ULONG i = 0; i < nCnt; i++ )
//STRIP001      if ( aMark.GetMark(i)->GetObj()->ISA(E3dScene) )
//STRIP001          return (E3dScene*) aMark.GetMark(i)->GetObj();
//STRIP001
//STRIP001  return NULL;
//STRIP001 }

/*************************************************************************
|*
|* aktuelles 3D-Zeichenobjekt setzen, dafuer Szene erzeugen
|*
\************************************************************************/

//STRIP001 void E3dView::SetCurrent3DObj(E3dObject* p3DObj)
//STRIP001 {
//STRIP001  DBG_ASSERT(p3DObj != NULL, "Nana, wer steckt denn hier 'nen NULL-Zeiger rein?");
//STRIP001  E3dScene* pScene = NULL;
//STRIP001
//STRIP001  // get transformed BoundVolume of the object
//STRIP001  Volume3D aVolume;
//STRIP001  const Volume3D& rObjVol = p3DObj->GetBoundVolume();
//STRIP001  const Matrix4D& rObjTrans = p3DObj->GetTransform();
//STRIP001  aVolume.Union(rObjVol.GetTransformVolume(rObjTrans));
//STRIP001
//STRIP001  double fW = aVolume.GetWidth();
//STRIP001  double fH = aVolume.GetHeight();
//STRIP001
//STRIP001  Rectangle aRect(0,0, (long) fW, (long) fH);
//STRIP001
//STRIP001  pScene = new E3dPolyScene(Get3DDefaultAttributes());
//STRIP001
//STRIP001  InitScene(pScene, fW, fH, aVolume.MaxVec().Z() + ((fW + fH) / 4.0));
//STRIP001
//STRIP001  pScene->Insert3DObj(p3DObj);
//STRIP001  pScene->NbcSetSnapRect(aRect);
//STRIP001  SetCurrentLibObj(pScene);
//STRIP001 }

/*************************************************************************
|*
|* neu erzeugte Szene initialisieren
|*
\************************************************************************/

//STRIP001 void E3dView::InitScene(E3dScene* pScene, double fW, double fH, double fCamZ)
//STRIP001 {
//STRIP001  Camera3D aCam(pScene->GetCamera());
//STRIP001
//STRIP001  aCam.SetAutoAdjustProjection(FALSE);
//STRIP001  aCam.SetViewWindow(- fW / 2, - fH / 2, fW, fH);
//STRIP001  Vector3D aLookAt;
//STRIP001
//STRIP001  double fDefaultCamPosZ = GetDefaultCamPosZ();
//STRIP001  Vector3D aCamPos(0.0, 0.0, fCamZ < fDefaultCamPosZ ? fDefaultCamPosZ : fCamZ);
//STRIP001
//STRIP001  aCam.SetPosAndLookAt(aCamPos, aLookAt);
//STRIP001  aCam.SetFocalLength(GetDefaultCamFocal());
//STRIP001  aCam.SetDefaults(Vector3D(0.0, 0.0, fDefaultCamPosZ), aLookAt, GetDefaultCamFocal());
//STRIP001  pScene->SetCamera(aCam);
//STRIP001 }

/*************************************************************************
|*
|* startsequenz fuer die erstellung eines 3D-Rotationskoerpers
|*
\************************************************************************/

//STRIP001 void E3dView::Start3DCreation ()
//STRIP001 {
//STRIP001  b3dCreationActive = TRUE;
//STRIP001
//STRIP001  if (aMark.GetMarkCount())
//STRIP001  {
//STRIP001      // irgendwelche Markierungen ermitteln und ausschalten
//STRIP001      BOOL bVis = IsMarkHdlShown();
//STRIP001
//STRIP001      if (bVis) HideMarkHdl(NULL);
//STRIP001
//STRIP001      // bestimme die koordinaten fuer JOEs Mirrorachse
//STRIP001      // entgegen der normalen Achse wird diese an die linke Seite des Objektes
//STRIP001      // positioniert
//STRIP001      long          nOutMin = 0;
//STRIP001      long          nOutMax = 0;
//STRIP001      long          nMinLen = 0;
//STRIP001      long          nObjDst = 0;
//STRIP001      long          nOutHgt = 0;
//STRIP001      OutputDevice* pOut    = GetWin(0);
//STRIP001
//STRIP001      // erstmal Darstellungsgrenzen bestimmen
//STRIP001      if (pOut != NULL)
//STRIP001      {
//STRIP001          nMinLen = pOut->PixelToLogic(Size(0,50)).Height();
//STRIP001          nObjDst = pOut->PixelToLogic(Size(0,20)).Height();
//STRIP001
//STRIP001          long nDst = pOut->PixelToLogic(Size(0,10)).Height();
//STRIP001
//STRIP001          nOutMin =  -pOut->GetMapMode().GetOrigin().Y();
//STRIP001          nOutMax =  pOut->GetOutputSize().Height() - 1 + nOutMin;
//STRIP001          nOutMin += nDst;
//STRIP001          nOutMax -= nDst;
//STRIP001
//STRIP001          if (nOutMax - nOutMin < nDst)
//STRIP001          {
//STRIP001              nOutMin += nOutMax + 1;
//STRIP001              nOutMin /= 2;
//STRIP001              nOutMin -= (nDst + 1) / 2;
//STRIP001              nOutMax  = nOutMin + nDst;
//STRIP001          }
//STRIP001
//STRIP001          nOutHgt = nOutMax - nOutMin;
//STRIP001
//STRIP001          long nTemp = nOutHgt / 4;
//STRIP001          if (nTemp > nMinLen) nMinLen = nTemp;
//STRIP001      }
//STRIP001
//STRIP001      // und dann die Markierungen oben und unten an das Objekt heften
//STRIP001      Rectangle aR;
//STRIP001      for(UINT32 nMark = 0; nMark < aMark.GetMarkCount(); nMark++)
//STRIP001      {
//STRIP001          XPolyPolygon aXPP;
//STRIP001          SdrObject* pMark = aMark.GetMark(nMark)->GetObj();
//STRIP001          pMark->TakeXorPoly(aXPP, FALSE);
//STRIP001          aR.Union(aXPP.GetBoundRect());
//STRIP001      }
//STRIP001      Point     aCenter(aR.Center());
//STRIP001      long      nMarkHgt = aR.GetHeight() - 1;
//STRIP001      long      nHgt     = nMarkHgt + nObjDst * 2;
//STRIP001
//STRIP001      if (nHgt < nMinLen) nHgt = nMinLen;
//STRIP001
//STRIP001      long nY1 = aCenter.Y() - (nHgt + 1) / 2;
//STRIP001      long nY2 = nY1 + nHgt;
//STRIP001
//STRIP001      if (pOut && (nMinLen > nOutHgt)) nMinLen = nOutHgt;
//STRIP001      if (pOut)
//STRIP001      {
//STRIP001          if (nY1 < nOutMin)
//STRIP001          {
//STRIP001              nY1 = nOutMin;
//STRIP001              if (nY2 < nY1 + nMinLen) nY2 = nY1 + nMinLen;
//STRIP001          }
//STRIP001          if (nY2 > nOutMax)
//STRIP001          {
//STRIP001              nY2 = nOutMax;
//STRIP001              if (nY1 > nY2 - nMinLen) nY1 = nY2 - nMinLen;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001         aRef1.X() = aR.Left();    // Initial Achse um 2/100mm nach links
//STRIP001      aRef1.Y() = nY1;
//STRIP001         aRef2.X() = aRef1.X();
//STRIP001      aRef2.Y() = nY2;
//STRIP001
//STRIP001      // Markierungen einschalten
//STRIP001      SetMarkHandles();
//STRIP001
//STRIP001      if (bVis) ShowMarkHdl(NULL);
//STRIP001      if (HasMarkedObj()) MarkListHasChanged();
//STRIP001
//STRIP001      // SpiegelPolygone SOFORT zeigen
//STRIP001      CreateMirrorPolygons ();
//STRIP001      const SdrHdlList &aHdlList = GetHdlList ();
//STRIP001      ShowMirrorPolygons (aHdlList.GetHdl (HDL_REF1)->GetPos (),
//STRIP001                          aHdlList.GetHdl (HDL_REF2)->GetPos ());
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* was passiert bei einer Mausbewegung, wenn das Objekt erstellt wird ?
|*
\************************************************************************/

//STRIP001 void E3dView::MovAction(const Point& rPnt)
//STRIP001 {
//STRIP001     if (b3dCreationActive)
//STRIP001  {
//STRIP001      SdrHdl* pHdl = GetDragHdl();
//STRIP001
//STRIP001      if (pHdl)
//STRIP001      {
//STRIP001          SdrHdlKind eHdlKind = pHdl->GetKind();
//STRIP001
//STRIP001          // reagiere nur bei einer spiegelachse
//STRIP001          if ((eHdlKind == HDL_REF1) ||
//STRIP001              (eHdlKind == HDL_REF2) ||
//STRIP001              (eHdlKind == HDL_MIRX))
//STRIP001          {
//STRIP001              const SdrHdlList &aHdlList = GetHdlList ();
//STRIP001
//STRIP001              // loesche das gespiegelte Polygon, spiegele das Original und zeichne es neu
//STRIP001                 b3dCreationActive = FALSE;  // Damit in DrawDragObj() gezeichnet wird
//STRIP001                 b3dCreationActive = TRUE;   // restaurieren (Trick)
//STRIP001                 ShowMirrored ();
//STRIP001                 SdrView::MovAction (rPnt);
//STRIP001              ShowMirrorPolygons (aHdlList.GetHdl (HDL_REF1)->GetPos (),
//STRIP001                                  aHdlList.GetHdl (HDL_REF2)->GetPos ());
//STRIP001             }
//STRIP001      }
//STRIP001         else
//STRIP001         {
//STRIP001             SdrView::MovAction (rPnt);
//STRIP001         }
//STRIP001  }
//STRIP001     else
//STRIP001     {
//STRIP001         SdrView::MovAction (rPnt);
//STRIP001     }
//STRIP001 }

/*************************************************************************
|*
|* Schluss. Objekt und evtl. Unterobjekte ueber ImpCreate3DLathe erstellen
|*          [FG] Mit dem Parameterwert TRUE (SDefault: FALSE) wird einfach ein
|*               Rotationskoerper erzeugt, ohne den Benutzer die Lage der
|*               Achse fetlegen zu lassen. Es reicht dieser Aufruf, falls
|*               ein Objekt selektiert ist. (keine Initialisierung noetig)
|*
\************************************************************************/

//STRIP001 void E3dView::End3DCreation(BOOL bUseDefaultValuesForMirrorAxes)
//STRIP001 {
//STRIP001  if(HasMarkedObj())
//STRIP001  {
//STRIP001      if(bUseDefaultValuesForMirrorAxes)
//STRIP001      {
//STRIP001          Rectangle aRect = GetAllMarkedRect();
//STRIP001          if(aRect.GetWidth() <= 1)
//STRIP001              aRect.SetSize(Size(500, aRect.GetHeight()));
//STRIP001          if(aRect.GetHeight() <= 1)
//STRIP001              aRect.SetSize(Size(aRect.GetWidth(), 500));
//STRIP001
//STRIP001          Vector3D aPnt1(aRect.Left(), -aRect.Top(), 0.0);
//STRIP001          Vector3D aPnt2(aRect.Left(), -aRect.Bottom(), 0.0);
//STRIP001
//STRIP001          ConvertMarkedObjTo3D(FALSE, aPnt1, aPnt2);
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // Hilfsfigur ausschalten
//STRIP001             ShowMirrored();
//STRIP001
//STRIP001          // irgendwo kassieren wir eine Rekursion, also unterbinden
//STRIP001          b3dCreationActive = FALSE;
//STRIP001
//STRIP001          // bestimme aus den Handlepositionen und den Versatz der Punkte
//STRIP001             const SdrHdlList &aHdlList = GetHdlList();
//STRIP001          Point aMirrorRef1 = aHdlList.GetHdl(HDL_REF1)->GetPos();
//STRIP001          Point aMirrorRef2 = aHdlList.GetHdl(HDL_REF2)->GetPos();
//STRIP001
//STRIP001          Vector3D aPnt1(aMirrorRef1.X(), -aMirrorRef1.Y(), 0.0);
//STRIP001          Vector3D aPnt2(aMirrorRef2.X(), -aMirrorRef2.Y(), 0.0);
//STRIP001
//STRIP001          ConvertMarkedObjTo3D(FALSE, aPnt1, aPnt2);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  ResetCreationActive();
//STRIP001 }

/*************************************************************************
|*
|* stelle das Mirrorobjekt dar
|*
\************************************************************************/

/*N*/ void E3dView::ShowMirrored ()
/*N*/ {
/*N*/   if (b3dCreationActive)
/*N*/   {
/*?*/       OutputDevice  *pOut = GetWin(0);
/*?*/       RasterOp      eRop0 = pOut->GetRasterOp();
/*?*/
/*?*/       Color aOldLineColor( pXOut->GetLineColor() );
/*?*/       Color aOldFillColor( pXOut->GetFillColor() );
/*?*/       Color aNewLineColor( COL_BLACK );
/*?*/       Color aNewFillColor( COL_TRANSPARENT );
/*?*/
/*?*/
/*?*/       // invertiere die Darstellung
/*?*/       pOut->SetRasterOp(ROP_INVERT);
/*?*/       pXOut->SetOutDev(pOut);
/*?*/       pXOut->OverrideLineColor( aNewLineColor );
/*?*/       pXOut->OverrideFillColor( aNewFillColor );
/*?*/
/*?*/       for (long nMark = 0;
/*?*/                 nMark < nPolyCnt;
/*?*/                 nMark ++)
/*?*/       {
/*?*/           const XPolyPolygon &rXPP    = pMirroredPolygon [nMark];
/*?*/           USHORT             nPolyAnz = rXPP.Count();
/*?*/
/*?*/             for (USHORT nPolyNum = 0;
/*?*/                        nPolyNum < nPolyAnz;
/*?*/                        nPolyNum ++)
/*?*/           {
/*?*/               const XPolygon &rXP = rXPP [nPolyNum];
/*?*/
/*?*/               pXOut->DrawXPolyLine(rXP);
/*?*/           }
/*?*/       }
/*?*/
/*?*/       pXOut->OverrideLineColor( aOldLineColor );
/*?*/       pXOut->OverrideFillColor( aOldFillColor );
/*?*/       pOut->SetRasterOp(eRop0);
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Destruktor
|*
\************************************************************************/

/*N*/ E3dView::~E3dView ()
/*N*/ {
/*N*/   /*#90353#*/delete [] pMirrorPolygon;
/*N*/   /*#90353#*/delete [] pMirroredPolygon;
/*N*/   /*#90353#*/delete [] pMarkedObjs;
/*N*/ }

/*************************************************************************
|*
|* Bestimme Anzahl der Polygone und kopiere in die Spiegelpolygone
|*
\************************************************************************/

//STRIP001 void E3dView::CreateMirrorPolygons ()
//STRIP001 {
//STRIP001  nPolyCnt         = aMark.GetMarkCount();
//STRIP001  pMirrorPolygon   = new XPolyPolygon [nPolyCnt];
//STRIP001  pMirroredPolygon = new XPolyPolygon [nPolyCnt];
//STRIP001  pMarkedObjs      = new SdrObject* [nPolyCnt];
//STRIP001  pMyPV            = aMark.GetMark(0)->GetPageView();
//STRIP001
//STRIP001  for (long nMark = nPolyCnt;
//STRIP001            nMark > 0;
//STRIP001      )
//STRIP001  {
//STRIP001      SdrMark   *pMark = aMark.GetMark(-- nMark);
//STRIP001      SdrObject *pObj  = pMark->GetObj();
//STRIP001
//STRIP001      pObj->TakeXorPoly (pMirrorPolygon [nMark], FALSE);
//STRIP001      pMarkedObjs [nMark] = pObj;
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* spiegele die originalpolygone und stelle sie als hilfsfigur dar
|*
\************************************************************************/

//STRIP001 void E3dView::ShowMirrorPolygons (Point aMirrorPoint1,
//STRIP001                                Point aMirrorPoint2)
//STRIP001 {
//STRIP001  for (long nMark = 0;
//STRIP001            nMark < nPolyCnt;
//STRIP001            nMark ++)
//STRIP001  {
//STRIP001      pMirroredPolygon [nMark] = pMirrorPolygon [nMark];
//STRIP001      MirrorXPoly(pMirroredPolygon [nMark], aMirrorPoint1, aMirrorPoint2);
//STRIP001  }
//STRIP001
//STRIP001  if (nPolyCnt) ShowMirrored ();
//STRIP001 }

/*************************************************************************
|*
|* beende das erzeugen und loesche die polygone
|*
\************************************************************************/

/*N*/ void E3dView::ResetCreationActive ()
/*N*/ {
/*N*/   /*#90353#*/delete [] pMirrorPolygon;
/*N*/   /*#90353#*/delete [] pMirroredPolygon;
/*N*/   /*#90353#*/delete [] pMarkedObjs;
/*N*/
/*N*/   pMarkedObjs       = 0;
/*N*/   pMirrorPolygon    =
/*N*/   pMirroredPolygon  = 0;
/*N*/   b3dCreationActive = FALSE;
/*N*/   nPolyCnt          = 0;
/*N*/ }

/*************************************************************************
|*
|* Skalarprodukt zweier Punktvektoren
|*
\************************************************************************/

//STRIP001 long Scalar (Point aPoint1,
//STRIP001           Point aPoint2)
//STRIP001 {
//STRIP001  return aPoint1.X () * aPoint2.X () + aPoint1.Y () * aPoint2.Y ();
//STRIP001 }

/*************************************************************************
|*
|* Skalarprodukt zweier Punktvektoren
|*
\************************************************************************/

//STRIP001 Point ScaleVector (Point  aPoint,
//STRIP001                 double nScale)
//STRIP001 {
//STRIP001  return Point ((long) ((double) aPoint.X () * nScale), (long) ((double) aPoint.Y () * nScale));
//STRIP001 }

/*************************************************************************
|*
|* Skalarprodukt zweier Punktvektoren
|*
\************************************************************************/

//STRIP001 double NormVector (Point aPoint)
//STRIP001 {
//STRIP001  return sqrt ((double) Scalar (aPoint, aPoint));
//STRIP001 }

/*************************************************************************
|*
|* Pruefe, ob sich zwei Geradensegemente schneiden
|* Dazu wird ueber einfache Determinanten bestimmt, wie die Endpunkte
|* zu der jeweils anderen Gerade liegen.
|*
\************************************************************************/

//STRIP001 BOOL LineCutting (Point aP1,
//STRIP001                Point aP2,
//STRIP001                Point aP3,
//STRIP001                Point aP4)
//STRIP001 {
//STRIP001  long nS1 = Point2Line (aP1, aP3, aP4);
//STRIP001  long nS2 = Point2Line (aP2, aP3, aP4);
//STRIP001  long nS3 = Point2Line (aP3, aP1, aP2);
//STRIP001  long nS4 = Point2Line (aP4, aP1, aP2);
//STRIP001
//STRIP001  // die werte koennen reichlich gross werden, also geht eine multiplikation daneben
//STRIP001     BOOL bCut (((nS1 < 0) && (nS2 > 0) || (nS1 > 0) && (nS2 < 0)) &&
//STRIP001               ((nS3 < 0) && (nS4 > 0) || (nS3 > 0) && (nS4 < 0)));
//STRIP001
//STRIP001     if (bCut)
//STRIP001     {
//STRIP001         BOOL bStop = bCut;
//STRIP001     }
//STRIP001
//STRIP001     return ((nS1 < 0) && (nS2 > 0) || (nS1 > 0) && (nS2 < 0)) &&
//STRIP001            ((nS3 < 0) && (nS4 > 0) || (nS3 > 0) && (nS4 < 0));
//STRIP001 }

/*************************************************************************
|*
|* Bestimme, ob sich ein Punkt aP1 rechts oder links eines Geradensegments,
|* definiert durch aP2 und aP3, befindet.
|* >0 : rechts, <0 : links, =0 : auf dem Geradensegment
|* Die Vektoren (Punkte) liegen in der homogenen Form vor, wobei die
|* Skalierung =1 gesetzt ist (schneller und einfacher).
|*
\************************************************************************/

//STRIP001 long Point2Line (Point aP1,
//STRIP001               Point aP2,
//STRIP001               Point aP3)
//STRIP001 {
//STRIP001  return (aP2.X () * aP3.Y () - aP2.Y () * aP3.X ()) -
//STRIP001         (aP1.X () * aP3.Y () - aP1.Y () * aP3.X ()) +
//STRIP001         (aP1.X () * aP2.Y () - aP1.Y () * aP2.X ());
//STRIP001 }

/*************************************************************************
|*
|* Bestimme den Abstand eines Punktes u zu einem Geradensegment,
|* definiert durch v1 und v.
|*
\************************************************************************/

//STRIP001 long DistPoint2Line (Point u,
//STRIP001                   Point v1,
//STRIP001                   Point v)
//STRIP001 {
//STRIP001  Point w = v1 - v;
//STRIP001
//STRIP001  return (long) NormVector (v - ScaleVector (w, (double) Scalar (v - u, w) / (double) Scalar (w, w)) - u);
//STRIP001 }

/*************************************************************************
|*
|* Klasse initialisieren
|*
\************************************************************************/

/*N*/ void E3dView::InitView ()
/*N*/ {
/*N*/   eDragConstraint          = E3DDRAG_CONSTR_XYZ;
/*N*/   eDragDetail              = E3DDETAIL_ONEBOX;
/*N*/   b3dCreationActive        = FALSE;
/*N*/   pMirrorPolygon           = 0;
/*N*/   pMirroredPolygon         = 0;
/*N*/   nPolyCnt                 = 0;
/*N*/   pMyPV                    = 0;
/*N*/   pMarkedObjs              = 0;
/*N*/   fDefaultScaleX           =
/*N*/   fDefaultScaleY           =
/*N*/   fDefaultScaleZ           = 1.0;
/*N*/   fDefaultRotateX          =
/*N*/   fDefaultRotateY          =
/*N*/   fDefaultRotateZ          = 0.0;
/*N*/   fDefaultExtrusionDeepth  = 1000; // old: 2000;
/*N*/   fDefaultLightIntensity   = 0.8; // old: 0.6;
/*N*/   fDefaultAmbientIntensity = 0.4;
/*N*/     nHDefaultSegments        = 12;
/*N*/     nVDefaultSegments        = 12;
/*N*/     aDefaultLightColor       = RGB_Color(COL_WHITE);
/*N*/     aDefaultAmbientColor     = RGB_Color(COL_BLACK);
/*N*/   aDefaultLightPos         = Vector3D (1, 1, 1); // old: Vector3D (0, 0, 1);
/*N*/   aDefaultLightPos.Normalize();
/*N*/     bDoubleSided             = FALSE;
/*N*/ }

/*************************************************************************
|*
|* Zeige eine Hilfsfigur
|*
\************************************************************************/

//STRIP001 void E3dView::ShowDragObj (OutputDevice *pOut)
//STRIP001 {
//STRIP001     SdrView::ShowDragObj (pOut);
//STRIP001 }

/*************************************************************************
|*
|* Verdecke eine Hilfsfigur
|*
\************************************************************************/

//STRIP001 void E3dView::HideDragObj (OutputDevice *pOut)
//STRIP001 {
//STRIP001     SdrView::HideDragObj (pOut);
//STRIP001 }

/*************************************************************************
|*
|* Zeige eine Hilfsfigur
|*
\************************************************************************/

//STRIP001 void E3dView::DrawDragObj (OutputDevice *pOut,
//STRIP001                            BOOL     bFull) const
//STRIP001 {
//STRIP001     if (!b3dCreationActive)
//STRIP001     {
//STRIP001         SdrView::DrawDragObj (pOut, bFull);
//STRIP001     }
//STRIP001 }

/*************************************************************************
|*
|* Koennen die selektierten Objekte aufgebrochen werden?
|*
\************************************************************************/

//STRIP001 BOOL E3dView::IsBreak3DObjPossible() const
//STRIP001 {
//STRIP001     ULONG nCount = aMark.GetMarkCount();
//STRIP001
//STRIP001     if (nCount > 0)
//STRIP001     {
//STRIP001         ULONG i = 0;
//STRIP001
//STRIP001         while (i < nCount)
//STRIP001         {
//STRIP001             SdrObject* pObj = aMark.GetMark(i)->GetObj();
//STRIP001
//STRIP001             if (pObj && pObj->ISA(E3dObject))
//STRIP001             {
//STRIP001                 if(!(((E3dObject*)pObj)->IsBreakObjPossible()))
//STRIP001                     return FALSE;
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 return FALSE;
//STRIP001             }
//STRIP001
//STRIP001             i++;
//STRIP001         }
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         return FALSE;
//STRIP001     }
//STRIP001
//STRIP001     return TRUE;
//STRIP001 }

/*************************************************************************
|*
|* Selektierte Lathe-Objekte aufbrechen
|*
\************************************************************************/

//STRIP001 void E3dView::Break3DObj()
//STRIP001 {
//STRIP001  if(IsBreak3DObjPossible())
//STRIP001  {
//STRIP001      // ALLE selektierten Objekte werden gewandelt
//STRIP001      UINT32 nCount = aMark.GetMarkCount();
//STRIP001
//STRIP001      BegUndo(String(SVX_RESSTR(RID_SVX_3D_UNDO_BREAK_LATHE)));
//STRIP001      for(UINT32 a=0;a<nCount;a++)
//STRIP001      {
//STRIP001          E3dObject* pObj = (E3dObject*)aMark.GetMark(a)->GetObj();
//STRIP001          BreakSingle3DObj(pObj);
//STRIP001      }
//STRIP001      DeleteMarked();
//STRIP001      EndUndo();
//STRIP001  }
//STRIP001 }

//STRIP001 void E3dView::BreakSingle3DObj(E3dObject* pObj)
//STRIP001 {
//STRIP001  if(pObj->ISA(E3dScene))
//STRIP001  {
//STRIP001      SdrObjList* pSubList = pObj->GetSubList();
//STRIP001      SdrObjListIter aIter(*pSubList, IM_FLAT);
//STRIP001
//STRIP001      while(aIter.IsMore())
//STRIP001      {
//STRIP001          E3dObject* pSubObj = (E3dObject*)aIter.Next();
//STRIP001          BreakSingle3DObj(pSubObj);
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SdrAttrObj* pNewObj = pObj->GetBreakObj();
//STRIP001      if(pNewObj)
//STRIP001      {
//STRIP001          InsertObject(pNewObj, *GetPageViewPvNum(0), SDRINSERT_DONTMARK);
//STRIP001          pNewObj->SendRepaintBroadcast();
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Szenen mischen
|*
\************************************************************************/
// Wird bisher noch nirgenswo (weder im Draw oder Chart) aufgerufen

//STRIP001 void E3dView::MergeScenes ()
//STRIP001 {
//STRIP001     ULONG nCount = aMark.GetMarkCount();
//STRIP001
//STRIP001     if (nCount > 0)
//STRIP001     {
//STRIP001         ULONG     nObj    = 0;
//STRIP001         SdrObject *pObj   = aMark.GetMark(nObj)->GetObj();
//STRIP001      E3dScene  *pScene = new E3dPolyScene(Get3DDefaultAttributes());
//STRIP001         Volume3D  aBoundVol;
//STRIP001         Rectangle aAllBoundRect (GetMarkedObjBoundRect ());
//STRIP001      Point     aCenter (aAllBoundRect.Center());
//STRIP001
//STRIP001         while (pObj)
//STRIP001         {
//STRIP001             if (pObj->ISA(E3dScene))
//STRIP001             {
//STRIP001                 /**********************************************************
//STRIP001                 * Es ist eine 3D-Scene oder 3D-PolyScene
//STRIP001                 **********************************************************/
//STRIP001                 SdrObjList* pSubList = ((E3dObject*) pObj)->GetSubList();
//STRIP001
//STRIP001                 SdrObjListIter aIter(*pSubList, IM_FLAT);
//STRIP001
//STRIP001                 while (aIter.IsMore())
//STRIP001                 {
//STRIP001                     /******************************************************
//STRIP001                     * LatheObjekte suchen
//STRIP001                     ******************************************************/
//STRIP001                     SdrObject* pSubObj = aIter.Next();
//STRIP001
//STRIP001                     if (!pSubObj->ISA(E3dLight))
//STRIP001                     {
//STRIP001                         E3dObject *pNewObj = 0;
//STRIP001
//STRIP001                         switch (pSubObj->GetObjIdentifier())
//STRIP001                         {
//STRIP001                          case E3D_OBJECT_ID:
//STRIP001                              pNewObj = new E3dObject;
//STRIP001                              *(E3dObject*)pNewObj = *(E3dObject*)pSubObj;
//STRIP001                              break;
//STRIP001
//STRIP001                          case E3D_POLYOBJ_ID :
//STRIP001                              pNewObj = new E3dPolyObj;
//STRIP001                              *(E3dPolyObj*)pNewObj= *(E3dPolyObj*)pSubObj;
//STRIP001                              break;
//STRIP001
//STRIP001                          case E3D_CUBEOBJ_ID :
//STRIP001                              pNewObj = new E3dCubeObj;
//STRIP001                              *(E3dCubeObj*)pNewObj = *(E3dCubeObj*)pSubObj;
//STRIP001                              break;
//STRIP001
//STRIP001                          case E3D_SPHEREOBJ_ID:
//STRIP001                              pNewObj = new E3dSphereObj;
//STRIP001                              *(E3dSphereObj*)pNewObj = *(E3dSphereObj*)pSubObj;
//STRIP001                              break;
//STRIP001
//STRIP001                          case E3D_POINTOBJ_ID:
//STRIP001                              pNewObj = new E3dPointObj;
//STRIP001                              *(E3dPointObj*)pNewObj = *(E3dPointObj*)pSubObj;
//STRIP001                              break;
//STRIP001
//STRIP001                          case E3D_EXTRUDEOBJ_ID:
//STRIP001                              pNewObj = new E3dExtrudeObj;
//STRIP001                              *(E3dExtrudeObj*)pNewObj = *(E3dExtrudeObj*)pSubObj;
//STRIP001                              break;
//STRIP001
//STRIP001                          case E3D_LATHEOBJ_ID:
//STRIP001                              pNewObj = new E3dLatheObj;
//STRIP001                              *(E3dLatheObj*)pNewObj = *(E3dLatheObj*)pSubObj;
//STRIP001                              break;
//STRIP001
//STRIP001                          case E3D_LABELOBJ_ID:
//STRIP001                              pNewObj = new E3dLabelObj;
//STRIP001                              *(E3dLabelObj*)pNewObj = *(E3dLabelObj*)pSubObj;
//STRIP001                              break;
//STRIP001
//STRIP001                             case E3D_COMPOUNDOBJ_ID:
//STRIP001                              pNewObj = new E3dCompoundObject;
//STRIP001                              *(E3dCompoundObject*)pNewObj = *(E3dCompoundObject*)pSubObj;
//STRIP001                              break;
//STRIP001                         }
//STRIP001
//STRIP001                         Rectangle aBoundRect = pSubObj->GetBoundRect ();
//STRIP001
//STRIP001                      Matrix4D aMatrix;
//STRIP001                      aMatrix.Translate(Vector3D(aBoundRect.Left () - aCenter.X (), aCenter.Y(), 0));
//STRIP001                      pNewObj->SetTransform(pNewObj->GetTransform() * aMatrix);
//STRIP001
//STRIP001                         if (pNewObj) aBoundVol.Union (pNewObj->GetBoundVolume());
//STRIP001                      pScene->Insert3DObj (pNewObj);
//STRIP001                     }
//STRIP001              }
//STRIP001             }
//STRIP001
//STRIP001             nObj++;
//STRIP001
//STRIP001             if (nObj < nCount)
//STRIP001             {
//STRIP001                 pObj = aMark.GetMark(nObj)->GetObj();
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 pObj = NULL;
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001      double fW = aAllBoundRect.GetWidth();
//STRIP001      double fH = aAllBoundRect.GetHeight();
//STRIP001      Rectangle aRect(0,0, (long) fW, (long) fH);
//STRIP001
//STRIP001      InitScene(pScene, fW, fH, aBoundVol.MaxVec().Z() +  + ((fW + fH) / 4.0));
//STRIP001
//STRIP001      pScene->FitSnapRectToBoundVol();
//STRIP001      pScene->NbcSetSnapRect(aRect);
//STRIP001
//STRIP001         Camera3D &aCamera  = (Camera3D&) pScene->GetCamera ();
//STRIP001         Vector3D aMinVec (aBoundVol.MinVec ());
//STRIP001         Vector3D aMaxVec (aBoundVol.MaxVec ());
//STRIP001         double fDeepth = fabs (aMaxVec.Z () - aMinVec.Z ());
//STRIP001
//STRIP001         aCamera.SetPRP (Vector3D (0, 0, 1000));
//STRIP001      double fDefaultCamPosZ = GetDefaultCamPosZ();
//STRIP001      aCamera.SetPosition (Vector3D(0.0, 0.0, fDefaultCamPosZ + fDeepth / 2));
//STRIP001      aCamera.SetFocalLength(GetDefaultCamFocal());
//STRIP001         pScene->SetCamera (aCamera);
//STRIP001
//STRIP001      // SnapRects der Objekte ungueltig
//STRIP001      pScene->SetRectsDirty();
//STRIP001
//STRIP001      // Transformationen initialisieren, damit bei RecalcSnapRect()
//STRIP001      // richtig gerechnet wird
//STRIP001      pScene->InitTransformationSet();
//STRIP001
//STRIP001      InsertObject (pScene, *(aMark.GetMark(0)->GetPageView()));
//STRIP001
//STRIP001      // SnapRects der Objekte ungueltig
//STRIP001      pScene->SetRectsDirty();
//STRIP001     }
//STRIP001 }

/*************************************************************************
|*
|* Possibilities, hauptsaechlich gruppieren/ungruppieren
|*
\************************************************************************/
/*N*/ void E3dView::CheckPossibilities()
/*N*/ {
/*N*/   // call parent
/*N*/   SdrView::CheckPossibilities();
/*N*/
/*N*/   // Weitere Flags bewerten
/*N*/   if(bGroupPossible || bUnGroupPossible || bGrpEnterPossible)
/*N*/   {
/*?*/       INT32 nMarkCnt = aMark.GetMarkCount();
/*?*/       BOOL bCoumpound = FALSE;
/*?*/       BOOL b3DObject = FALSE;
/*?*/       for(INT32 nObjs = 0L; (nObjs < nMarkCnt) && !bCoumpound; nObjs++)
/*?*/       {
/*?*/           SdrObject *pObj = aMark.GetMark(nObjs)->GetObj();
/*?*/           if(pObj && pObj->ISA(E3dCompoundObject))
/*?*/               bCoumpound = TRUE;
/*?*/           if(pObj && pObj->ISA(E3dObject))
/*?*/               b3DObject = TRUE;
/*?*/       }
/*?*/
/*?*/       // Bisher: Es sind ZWEI oder mehr beliebiger Objekte selektiert.
/*?*/       // Nachsehen, ob CompoundObjects beteiligt sind. Falls ja,
/*?*/       // das Gruppieren verbieten.
/*?*/       if(bGroupPossible && bCoumpound)
/*?*/           bGroupPossible = FALSE;
/*?*/
/*?*/       if(bUnGroupPossible && b3DObject)
/*?*/           bUnGroupPossible = FALSE;
/*?*/
/*?*/       if(bGrpEnterPossible && bCoumpound)
/*?*/           bGrpEnterPossible = FALSE;
/*N*/   }

//  bGroupPossible
//  bCombinePossible
//  bUnGroupPossible
//  bGrpEnterPossible
/*N*/ }



}
