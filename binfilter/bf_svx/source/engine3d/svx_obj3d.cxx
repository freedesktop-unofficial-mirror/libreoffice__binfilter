/*************************************************************************
 *
 *  $RCSfile: svx_obj3d.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 15:40:17 $
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

#define ITEMID_COLOR            SID_ATTR_3D_LIGHTCOLOR

#include "svdstr.hrc"
// auto strip #include "svdglob.hxx"

#ifndef _SVDVIEW_HXX
#include "svdview.hxx"
#endif

// auto strip #ifndef _SVDATTR_HXX
// auto strip #include "svdattr.hxx"
// auto strip #endif

// auto strip #ifndef _SVDPAGE_HXX
// auto strip #include "svdpage.hxx"
// auto strip #endif

// auto strip #ifndef _SVDIO_HXX
// auto strip #include "svdio.hxx"
// auto strip #endif

// auto strip #ifndef _SVDMODEL_HXX
// auto strip #include "svdmodel.hxx"
// auto strip #endif

// auto strip #ifndef _SVDITER_HXX
// auto strip #include "svditer.hxx"
// auto strip #endif

#ifndef _E3D_GLOBL3D_HXX
#include "globl3d.hxx"
#endif

// auto strip #ifndef _CAMERA3D_HXX
// auto strip #include "camera3d.hxx"
// auto strip #endif

// auto strip #ifndef _E3D_VOLMRK3D_HXX
// auto strip #include "volmrk3d.hxx"
// auto strip #endif

#ifndef _E3D_POLYOB3D_HXX
#include "polyob3d.hxx"
#endif

// auto strip #ifndef _E3D_SCENE3D_HXX
// auto strip #include "scene3d.hxx"
// auto strip #endif

#ifndef _E3D_POLYSC3D_HXX
#include "polysc3d.hxx"
#endif

// auto strip #ifndef _E3D_CUBE3D_HXX
// auto strip #include "cube3d.hxx"
// auto strip #endif

// auto strip #ifndef _E3D_LATHE3D_HXX
// auto strip #include "lathe3d.hxx"
// auto strip #endif

// auto strip #ifndef _E3D_SPHERE3D_HXX
// auto strip #include "sphere3d.hxx"
// auto strip #endif

// auto strip #ifndef _E3D_EXTRUD3D_HXX
// auto strip #include "extrud3d.hxx"
// auto strip #endif

// auto strip #ifndef _E3D_OBJ3D_HXX
// auto strip #include "obj3d.hxx"
// auto strip #endif

#ifndef _XOUTX_HXX
#include "xoutx.hxx"
#endif

// auto strip #ifndef _XTABLE_HXX
// auto strip #include "xtable.hxx"
// auto strip #endif

// auto strip #ifndef _SVX_XFLCLIT_HXX
// auto strip #include "xflclit.hxx"
// auto strip #endif

// auto strip #ifndef _SVAPP_HXX
// auto strip #include <vcl/svapp.hxx>
// auto strip #endif

// auto strip #ifndef _SETTINGS_HXX
// auto strip #include <vcl/settings.hxx>
// auto strip #endif

// auto strip #ifndef _B3D_BASE3D_HXX
// auto strip #include <goodies/base3d.hxx>
// auto strip #endif

// auto strip #ifndef _B3D_B3DTEX_HXX
// auto strip #include <goodies/b3dtex.hxx>
// auto strip #endif

// auto strip #ifndef _SVX_XLNCLIT_HXX
// auto strip #include "xlnclit.hxx"
// auto strip #endif

// auto strip #ifndef _SFXMETRICITEM_HXX
// auto strip #include <svtools/metitem.hxx>
// auto strip #endif

// auto strip #ifndef _XTABLE_HXX
// auto strip #include "xtable.hxx"
// auto strip #endif

// auto strip #ifndef _SVX_FILLITEM_HXX
// auto strip #include "xfillit.hxx"
// auto strip #endif

#ifndef _SVX_XLNWTIT_HXX
#include "xlnwtit.hxx"
#endif

// auto strip #ifndef _SV_VIRDEV_HXX
// auto strip #include <vcl/virdev.hxx>
// auto strip #endif

#ifndef _SVDIO_HXX
#include "svdio.hxx"
#endif

// auto strip #ifndef _TL_POLY_HXX
// auto strip #include <tools/poly.hxx>
// auto strip #endif

// auto strip #ifndef _B3D_B3DTRANS_HXX
// auto strip #include "b3dtrans.hxx"
// auto strip #endif

#ifndef _SVX_SVXIDS_HRC
#include "svxids.hrc"
#endif

// auto strip #ifndef _SVX_COLRITEM_HXX
// auto strip #include "colritem.hxx"
// auto strip #endif

// auto strip #ifndef _SVXE3DITEM_HXX
// auto strip #include "e3ditem.hxx"
// auto strip #endif

// auto strip #ifndef _SVX_XLNTRIT_HXX
// auto strip #include "xlntrit.hxx"
// auto strip #endif

// auto strip #ifndef _SVX_XFLTRIT_HXX
// auto strip #include "xfltrit.hxx"
// auto strip #endif

// auto strip #ifndef _SVDPAGV_HXX
// auto strip #include "svdpagv.hxx"
// auto strip #endif

// auto strip #ifndef _SV_GRADIENT_HXX
// auto strip #include <vcl/gradient.hxx>
// auto strip #endif

// auto strip #ifndef _SV_METAACT_HXX
// auto strip #include <vcl/metaact.hxx>
// auto strip #endif

// auto strip #ifndef _SVX3DITEMS_HXX
// auto strip #include "svx3ditems.hxx"
// auto strip #endif

// auto strip #ifndef _SFX_WHITER_HXX
// auto strip #include <svtools/whiter.hxx>
// auto strip #endif

// auto strip #ifndef INCLUDED_SVTOOLS_COLORCFG_HXX
// auto strip #include <svtools/colorcfg.hxx>
// auto strip #endif

#ifndef _EEITEM_HXX
#include "eeitem.hxx"
#endif

// auto strip #ifndef _SVX_XGRSCIT_HXX
// auto strip #include "xgrscit.hxx"
// auto strip #endif

// auto strip #ifndef _SVX_SVDOIMP_HXX
// auto strip #include "svdoimp.hxx"
// auto strip #endif
namespace binfilter {

#define ITEMVALUE(ItemSet,Id,Cast)  ((const Cast&)(ItemSet).Get(Id)).GetValue()

/*************************************************************************
|*
|* Liste fuer 3D-Objekte
|*
\************************************************************************/

/*N*/ TYPEINIT1(E3dObjList, SdrObjList);

/*N*/ E3dObjList::E3dObjList(SdrModel* pNewModel, SdrPage* pNewPage, E3dObjList* pNewUpList)
/*N*/ : SdrObjList(pNewModel, pNewPage, pNewUpList)
/*N*/ {
/*N*/ }

/*?*/ E3dObjList::E3dObjList(const E3dObjList& rSrcList)
/*?*/ : SdrObjList(rSrcList)
/*?*/ {
/*?*/ }

/*N*/ E3dObjList::~E3dObjList()
/*N*/ {
/*N*/ }

/*N*/ void E3dObjList::NbcInsertObject(SdrObject* pObj, ULONG nPos, const SdrInsertReason* pReason)
/*N*/ {
/*N*/   // Owner holen
/*N*/   DBG_ASSERT(GetOwnerObj()->ISA(E3dObject), "AW: Einfuegen 3DObject in Parent != 3DObject");
/*N*/
/*N*/   // Ist es ueberhaupt ein 3D-Objekt?
/*N*/   if(pObj && pObj->ISA(E3dObject))
/*N*/   {
/*N*/       // Normales 3D Objekt, einfuegen mittels
/*N*/       // call parent
/*N*/       SdrObjList::NbcInsertObject(pObj, nPos, pReason);
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       // Kein 3D Objekt, fuege in Seite statt in Szene ein...
/*?*/       GetOwnerObj()->GetPage()->InsertObject(pObj, nPos);
/*N*/   }
/*N*/ }

//STRIP001 SdrObject* E3dObjList::NbcRemoveObject(ULONG nObjNum)
//STRIP001 {
//STRIP001  // Owner holen
//STRIP001  DBG_ASSERT(GetOwnerObj()->ISA(E3dObject), "AW: Entfernen 3DObject aus Parent != 3DObject");
//STRIP001  E3dObject* pOwner = (E3dObject*)GetOwnerObj();
//STRIP001
//STRIP001  // call parent
//STRIP001  SdrObject* pRetval = SdrObjList::NbcRemoveObject(nObjNum);
//STRIP001
//STRIP001  // FitSnapRectToBoundVol vorbereiten
//STRIP001  if(GetOwnerObj() && GetOwnerObj()->ISA(E3dScene))
//STRIP001      ((E3dScene*)GetOwnerObj())->CorrectSceneDimensions();
//STRIP001
//STRIP001  return pRetval;
//STRIP001 }

/*N*/ SdrObject* E3dObjList::RemoveObject(ULONG nObjNum)
/*N*/ {
/*N*/   // Owner holen
/*N*/   DBG_ASSERT(GetOwnerObj()->ISA(E3dObject), "AW: Entfernen 3DObject aus Parent != 3DObject");
/*N*/   E3dObject* pOwner = (E3dObject*)GetOwnerObj();
/*N*/
/*N*/   // call parent
/*N*/   SdrObject* pRetval = SdrObjList::RemoveObject(nObjNum);
/*N*/
/*N*/   // FitSnapRectToBoundVol vorbereiten
/*N*/   if(GetOwnerObj() && GetOwnerObj()->ISA(E3dScene))
/*N*/       ((E3dScene*)GetOwnerObj())->CorrectSceneDimensions();
/*N*/
/*N*/   return pRetval;
/*N*/ }

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ TYPEINIT1(E3dObject, SdrAttrObj);

/*N*/ E3dObject::E3dObject() :
/*N*/   nLogicalGroup(0),
/*N*/   nObjTreeLevel(0),
/*N*/   eDragDetail(E3DDETAIL_ONEBOX),
/*N*/   nPartOfParent(0),
/*N*/   bTfHasChanged(TRUE),
/*N*/   bBoundVolValid(TRUE),
/*N*/   bIsSelected(FALSE)
/*N*/ {
/*N*/   bIs3DObj = TRUE;
/*N*/   pSub = new E3dObjList(NULL, NULL);
/*N*/   pSub->SetOwnerObj(this);
/*N*/   pSub->SetListKind(SDROBJLIST_GROUPOBJ);
/*N*/   bClosedObj = TRUE;
/*N*/ }

/*************************************************************************
|*
|* Destruktor
|*
\************************************************************************/

/*N*/ E3dObject::~E3dObject()
/*N*/ {
/*N*/   delete pSub;
/*N*/   pSub = NULL;
/*N*/ }

/*************************************************************************
|*
|* Selektions-Flag setzen
|*
\************************************************************************/

//STRIP001 void E3dObject::SetSelected(BOOL bNew)
//STRIP001 {
//STRIP001  // selbst setzen
//STRIP001  bIsSelected = bNew;
//STRIP001
//STRIP001  // bei SubObjekten setzen
//STRIP001  for ( ULONG i = 0; i < pSub->GetObjCount(); i++ )
//STRIP001  {
//STRIP001      if(pSub->GetObj(i) && pSub->GetObj(i)->ISA(E3dObject))
//STRIP001          ((E3dObject*)pSub->GetObj(i))->SetSelected(bNew);
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Aufbrechen, default-Implementierungen
|*
\************************************************************************/

//STRIP001 BOOL E3dObject::IsBreakObjPossible()
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }

/*N*/ SdrAttrObj* E3dObject::GetBreakObj()
/*N*/ {
/*N*/   return 0L;
/*N*/ }

/*************************************************************************
|*
|* SetRectsDirty muss ueber die lokale SdrSubList gehen
|*
\************************************************************************/

/*N*/ void E3dObject::SetRectsDirty(FASTBOOL bNotMyself)
/*N*/ {
/*N*/   // call parent
/*N*/   SdrAttrObj::SetRectsDirty(bNotMyself);
/*N*/
/*N*/   // Eigene SubListe AUCH behandeln
/*N*/   if(pSub && pSub->GetObjCount())
/*N*/   {
/*N*/       for (ULONG i = 0; i < pSub->GetObjCount(); i++)
/*N*/       {
/*N*/           SdrObject* pObj = pSub->GetObj(i);
/*N*/           DBG_ASSERT(pObj->ISA(E3dObject), "AW: In E3dObject sind nur 3D-Objekte erlaubt!");
/*N*/           ((E3dObject*)pObj)->SetRectsDirty(bNotMyself);
/*N*/       }
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Inventor zurueckgeben
|*
\************************************************************************/

/*N*/ UINT32 E3dObject::GetObjInventor() const
/*N*/ {
/*N*/   return E3dInventor;
/*N*/ }

/*************************************************************************
|*
|* Identifier zurueckgeben
|*
\************************************************************************/

/*N*/ UINT16 E3dObject::GetObjIdentifier() const
/*N*/ {
/*N*/   return E3D_OBJECT_ID;
/*N*/ }

/*************************************************************************
|*
|* Faehigkeiten des Objektes feststellen
|*
\************************************************************************/

//STRIP001 void E3dObject::TakeObjInfo(SdrObjTransformInfoRec& rInfo) const
//STRIP001 {
//STRIP001  rInfo.bResizeFreeAllowed    = TRUE;
//STRIP001  rInfo.bResizePropAllowed    = TRUE;
//STRIP001  rInfo.bRotateFreeAllowed    = TRUE;
//STRIP001  rInfo.bRotate90Allowed      = TRUE;
//STRIP001  rInfo.bMirrorFreeAllowed    = FALSE;
//STRIP001  rInfo.bMirror45Allowed      = FALSE;
//STRIP001  rInfo.bMirror90Allowed      = FALSE;
//STRIP001  rInfo.bShearAllowed         = FALSE;
//STRIP001  rInfo.bEdgeRadiusAllowed    = FALSE;
//STRIP001  rInfo.bCanConvToPath        = FALSE;
//STRIP001
//STRIP001  // no transparence for 3d objects
//STRIP001  rInfo.bTransparenceAllowed = FALSE;
//STRIP001
//STRIP001  // gradient depends on fillstyle
//STRIP001  // BM *** check if SetItem is NULL ***
//STRIP001  XFillStyle eFillStyle = ((XFillStyleItem&)(GetItem(XATTR_FILLSTYLE))).GetValue();
//STRIP001  rInfo.bGradientAllowed = (eFillStyle == XFILL_GRADIENT);
//STRIP001
//STRIP001  // Umwandeln von 3D-Koerpern in Gruppe von Polygonen:
//STRIP001  //
//STRIP001  // Erst mal nicht moeglich, da die Erzeugung einer Gruppe von
//STRIP001  // 2D-Polygonen notwendig waere, die tiefensortiert werden muessten,
//STRIP001  // also bei Durchdringugnen auch gegeneinander geschnitten werden
//STRIP001  // muessten. Auch die Texturkoorinaten waeren ein ungeloestes
//STRIP001  // Problem.
//STRIP001  rInfo.bCanConvToPoly = FALSE;
//STRIP001  rInfo.bCanConvToContour = FALSE;
//STRIP001
//STRIP001  rInfo.bCanConvToPathLineToArea = FALSE;
//STRIP001  rInfo.bCanConvToPolyLineToArea = FALSE;
//STRIP001 }

/*************************************************************************
|*
|* Layer abfragen
|*
\************************************************************************/

/*N*/ SdrLayerID E3dObject::GetLayer() const
/*N*/ {
/*N*/   FASTBOOL bFirst = TRUE;
/*N*/   E3dObjList* pOL = pSub;
/*N*/   ULONG       nObjCnt = pOL->GetObjCount();
/*N*/   SdrLayerID  nLayer = SdrLayerID(nLayerID);
/*N*/
/*N*/   for ( ULONG i = 0; i < nObjCnt; i++ )
/*N*/   {
/*N*/       SdrLayerID nObjLayer;
/*N*/       if(pOL->GetObj(i)->ISA(E3dPolyObj))
/*N*/           nObjLayer = SdrLayerID(nLayerID);
/*N*/       else
/*N*/           nObjLayer = pOL->GetObj(i)->GetLayer();
/*N*/
/*N*/       if (bFirst)
/*N*/       {
/*N*/           nLayer = nObjLayer;
/*N*/           bFirst = FALSE;
/*N*/       }
/*N*/       else if ( nObjLayer != nLayer )
/*N*/           return 0;
/*N*/   }
/*N*/   return nLayer;
/*N*/ }

/*************************************************************************
|*
|* Layer setzen
|*
\************************************************************************/

/*N*/ void E3dObject::NbcSetLayer(SdrLayerID nLayer)
/*N*/ {
/*N*/   SdrAttrObj::NbcSetLayer(nLayer);
/*N*/
/*N*/   E3dObjList* pOL = pSub;
/*N*/   ULONG nObjCnt = pOL->GetObjCount();
/*N*/   ULONG i;
/*N*/   for ( i = 0; i < nObjCnt; i++ )
/*N*/       pOL->GetObj(i)->NbcSetLayer(nLayer);
/*N*/ }

/*************************************************************************
|*
|* ObjList auch an SubList setzen
|*
\************************************************************************/

/*N*/ void E3dObject::SetObjList(SdrObjList* pNewObjList)
/*N*/ {
/*N*/   SdrObject::SetObjList(pNewObjList);
/*N*/   pSub->SetUpList(pNewObjList);
/*N*/ }

/*************************************************************************
|*
|* Layer setzen
|*
\************************************************************************/

/*N*/ void E3dObject::SetPage(SdrPage* pNewPage)
/*N*/ {
/*N*/   SdrAttrObj::SetPage(pNewPage);
/*N*/   pSub->SetPage(pNewPage);
/*N*/ }

/*************************************************************************
|*
|* Layer setzen
|*
\************************************************************************/

/*N*/ void E3dObject::SetModel(SdrModel* pNewModel)
/*N*/ {
/*N*/   SdrAttrObj::SetModel(pNewModel);
/*N*/   pSub->SetModel(pNewModel);
/*N*/ }

/*************************************************************************
|*
|* resize object, used from old 2d interfaces, e.g. in Move/Scale dialog
|* (F4)
|*
\************************************************************************/
/*N*/ void E3dObject::NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact)
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   // SdrAttrObj::NbcResize(rRef, xFact, yFact);
/*N*/
/*N*/   // Bewegung in X,Y im Augkoordinatensystem
/*N*/   E3dScene* pScene = GetScene();
/*N*/
/*N*/   if(pScene)
/*N*/   {
/*N*/       // pos ermitteln
/*N*/       B3dTransformationSet& rTransSet = pScene->GetCameraSet();
/*N*/       Vector3D aScaleCenter((double)rRef.X(), (double)rRef.Y(), 32768.0);
/*N*/       aScaleCenter = rTransSet.ViewToEyeCoor(aScaleCenter);
/*N*/
/*N*/       // scale-faktoren holen
/*N*/       double fScaleX = xFact;
/*N*/       double fScaleY = yFact;
/*N*/
/*N*/       // build transform
/*N*/       Matrix4D mFullTransform(GetFullTransform());
/*N*/       Matrix4D mTrans(mFullTransform);
/*N*/
/*N*/       mTrans *= rTransSet.GetOrientation();
/*N*/       mTrans.Translate(-aScaleCenter);
/*N*/       mTrans.Scale(fScaleX, fScaleY, 1.0);
/*N*/       mTrans.Translate(aScaleCenter);
/*N*/       mTrans *= rTransSet.GetInvOrientation();
/*N*/       mFullTransform.Invert();
/*N*/       mTrans *= mFullTransform;
/*N*/
/*N*/       // anwenden
/*N*/       Matrix4D mObjTrans(GetTransform());
/*N*/       mObjTrans *= mTrans;
/*N*/       SetTransform(mObjTrans);
/*N*/
/*N*/       // force new camera and SnapRect on scene, geometry may have really
/*N*/       // changed
/*N*/       pScene->CorrectSceneDimensions();
/*N*/   }
/*N*/ #endif
/*N*/ }

/*************************************************************************
|*
|* Objekt verschieben in 2D, wird bei Cursortasten benoetigt
|*
\************************************************************************/
//STRIP001 void E3dObject::NbcMove(const Size& rSize)
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  // Bewegung in X,Y im Augkoordinatensystem
//STRIP001  E3dScene* pScene = GetScene();
//STRIP001
//STRIP001  if(pScene)
//STRIP001  {
//STRIP001      // Abmessungen der Szene in 3D und 2D als Vergleich
//STRIP001      Rectangle aRect = pScene->GetSnapRect();
//STRIP001
//STRIP001      // Transformation Weltkoordinaten bis eine VOR Objektkoordinaten holen
//STRIP001      Matrix4D mInvDispTransform;
//STRIP001      if(GetParentObj())
//STRIP001      {
//STRIP001          mInvDispTransform = GetParentObj()->GetFullTransform();
//STRIP001          mInvDispTransform.Invert();
//STRIP001      }
//STRIP001
//STRIP001      // BoundVolume von Weltkoordinaten in Eye-Koordinaten
//STRIP001      B3dTransformationSet& rTransSet = pScene->GetCameraSet();
//STRIP001      const Volume3D& rVol = pScene->GetBoundVolume();
//STRIP001      Volume3D aEyeVol = rVol.GetTransformVolume(rTransSet.GetOrientation());
//STRIP001
//STRIP001      // relativen Bewegungsvektor in Augkoordinaten bilden
//STRIP001      Vector3D aMove(
//STRIP001          (double)rSize.Width() * aEyeVol.GetWidth() / (double)aRect.GetWidth(),
//STRIP001          (double)-rSize.Height() * aEyeVol.GetHeight() / (double)aRect.GetHeight(),
//STRIP001          0.0);
//STRIP001
//STRIP001      // Bewegungsvektor in lokale Koordinaten des Parents des Objektes
//STRIP001      Vector3D aPos;
//STRIP001      aMove = rTransSet.EyeToWorldCoor(aMove);
//STRIP001      aMove *= mInvDispTransform;
//STRIP001      aPos = rTransSet.EyeToWorldCoor(aPos);
//STRIP001      aPos *= mInvDispTransform;
//STRIP001      aMove = aMove - aPos;
//STRIP001
//STRIP001      // Transformieren
//STRIP001      Translate(aMove);
//STRIP001
//STRIP001      // force new camera and SnapRect on scene, geometry may have really
//STRIP001      // changed
//STRIP001      pScene->CorrectSceneDimensions();
//STRIP001  }
//STRIP001 #endif
//STRIP001 }

/*************************************************************************
|*
|* liefere die Sublist, aber nur dann, wenn darin Objekte enthalten sind !
|*
\************************************************************************/

/*N*/ SdrObjList* E3dObject::GetSubList() const
/*N*/ {
/*N*/   return pSub;
/*N*/ }

/*************************************************************************
|*
|* Anzahl der Handles zurueckgeben
|*
\************************************************************************/

//STRIP001 USHORT E3dObject::GetHdlCount() const
//STRIP001 {
//STRIP001  // 8 Eckpunkte + 1 E3dVolumeMarker (= Wireframe-Darstellung)
//STRIP001  return 9;
//STRIP001 }

/*************************************************************************
|*
|* Handle-Liste fuellen
|*
\************************************************************************/

//STRIP001 void E3dObject::AddToHdlList(SdrHdlList& rHdlList) const
//STRIP001 {
//STRIP001  XPolyPolygon     aXPP(12);
//STRIP001  XPolygon         aLine(2);
//STRIP001  E3dVolumeMarker* pVolMarker;
//STRIP001  USHORT           nPolyCnt;
//STRIP001
//STRIP001  ((E3dObject*) this)->ImpCreateWireframePoly(aXPP, E3DDETAIL_ONEBOX);
//STRIP001  nPolyCnt = aXPP.Count();
//STRIP001
//STRIP001  for ( USHORT i = 0; i < nPolyCnt; i += 3 )
//STRIP001  {
//STRIP001      rHdlList.AddHdl(new SdrHdl(aXPP[i][0], HDL_BWGT));
//STRIP001      rHdlList.AddHdl(new SdrHdl(aXPP[i][1], HDL_BWGT));
//STRIP001  }
//STRIP001
//STRIP001  if ( nPolyCnt > 0 )
//STRIP001  {
//STRIP001      pVolMarker = new E3dVolumeMarker(aXPP);
//STRIP001      rHdlList.AddHdl(pVolMarker);
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
\************************************************************************/

//STRIP001 FASTBOOL E3dObject::HasSpecialDrag() const
//STRIP001 {
//STRIP001  return TRUE;
//STRIP001 }

/*************************************************************************
|*
|* Paint; wird z.Z. nicht benutzt, da das Paint ueber die
|* (2D-)Displayliste der Szene laeuft
|*
\************************************************************************/

//STRIP001 void E3dObject::Paint3D(ExtOutputDevice& rOut, Base3D* pBase3D,
//STRIP001  const SdrPaintInfoRec& rInfoRec, UINT16 nDrawFlags)
//STRIP001 {
//STRIP001  if(pSub && pSub->GetObjCount())
//STRIP001  {
//STRIP001      BOOL bWasNotActive = rInfoRec.bNotActive;
//STRIP001      BOOL bIsEnteredGroup(FALSE);
//STRIP001
//STRIP001      if((rInfoRec.pPV && GetSubList() && rInfoRec.pPV->GetObjList() == GetSubList())
//STRIP001          || ((rInfoRec.nPaintMode & SDRPAINTMODE_MASTERPAGE) != 0))
//STRIP001      {
//STRIP001          bIsEnteredGroup = TRUE;
//STRIP001      }
//STRIP001
//STRIP001      if(bIsEnteredGroup && bWasNotActive)
//STRIP001      {
//STRIP001          // auf aktive Elemente schalten
//STRIP001          ((SdrPaintInfoRec&)rInfoRec).bNotActive = FALSE;
//STRIP001      }
//STRIP001
//STRIP001      for (ULONG i = 0; i < pSub->GetObjCount(); i++)
//STRIP001      {
//STRIP001          SdrObject* pObj = pSub->GetObj(i);
//STRIP001          DBG_ASSERT(pObj->ISA(E3dObject), "AW: In E3dObject sind nur 3D-Objekte erlaubt!");
//STRIP001          ((E3dObject*)pObj)->Paint3D(rOut, pBase3D, rInfoRec, nDrawFlags);
//STRIP001      }
//STRIP001
//STRIP001      if(bIsEnteredGroup && bWasNotActive)
//STRIP001      {
//STRIP001          // Zurueck auf Ursprung, Zustand wieder verlassen
//STRIP001          ((SdrPaintInfoRec&)rInfoRec).bNotActive = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Objekt als Kontur in das Polygon einfuegen
|*
\************************************************************************/

//STRIP001 void E3dObject::TakeContour3D(XPolyPolygon& rPoly)
//STRIP001 {
//STRIP001  if(pSub && pSub->GetObjCount())
//STRIP001  {
//STRIP001      for (ULONG i = 0; i < pSub->GetObjCount(); i++)
//STRIP001      {
//STRIP001          SdrObject* pObj = pSub->GetObj(i);
//STRIP001          DBG_ASSERT(pObj->ISA(E3dObject), "AW: In E3dObject sind nur 3D-Objekte erlaubt!");
//STRIP001          ((E3dObject*)pObj)->TakeContour3D(rPoly);
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Schatten fuer 3D-Objekte zeichnen
|*
\************************************************************************/

//STRIP001 void E3dObject::DrawShadows(Base3D *pBase3D,
//STRIP001  ExtOutputDevice& rXOut,
//STRIP001  const Rectangle& rBound, const Volume3D& rVolume,
//STRIP001  const SdrPaintInfoRec& rInfoRec)
//STRIP001 {
//STRIP001  if(pSub && pSub->GetObjCount())
//STRIP001  {
//STRIP001      for (ULONG i = 0; i < pSub->GetObjCount(); i++)
//STRIP001      {
//STRIP001          SdrObject* pObj = pSub->GetObj(i);
//STRIP001          DBG_ASSERT(pObj->ISA(E3dObject), "AW: In E3dObject sind nur 3D-Objekte erlaubt!");
//STRIP001          ((E3dObject*)pObj)->DrawShadows(pBase3D, rXOut, rBound, rVolume, rInfoRec);
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* SnapRect berechnen
|*
\************************************************************************/

/*N*/ void E3dObject::RecalcSnapRect()
/*N*/ {
/*N*/   maSnapRect = Rectangle();
/*N*/   if(pSub && pSub->GetObjCount())
/*N*/   {
/*N*/       for (ULONG i = 0; i < pSub->GetObjCount(); i++)
/*N*/       {
/*N*/           SdrObject* pObj = pSub->GetObj(i);
/*N*/           DBG_ASSERT(pObj->ISA(E3dObject), "AW: In E3dObject sind nur 3D-Objekte erlaubt!");
/*N*/           Rectangle aSubRect = ((E3dObject*)pObj)->GetSnapRect();
/*N*/           maSnapRect.Union(aSubRect);
/*N*/       }
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* BoundRect berechnen
|*
\************************************************************************/

/*N*/ void E3dObject::RecalcBoundRect()
/*N*/ {
/*N*/   // BoundRect aus SnapRect berechnen
/*N*/   aOutRect = GetSnapRect();
/*N*/
/*N*/   if(pSub && pSub->GetObjCount())
/*N*/   {
/*N*/       for (ULONG i = 0; i < pSub->GetObjCount(); i++)
/*N*/       {
/*N*/           SdrObject* pObj = pSub->GetObj(i);
/*N*/           DBG_ASSERT(pObj->ISA(E3dObject), "AW: In E3dObject sind nur 3D-Objekte erlaubt!");
/*N*/           Rectangle aSubRect = ((E3dObject*)pObj)->GetBoundRect();
/*N*/           aOutRect.Union(aSubRect);
/*N*/       }
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Einfuegen eines 3D-Objekts an den Parent weitermelden, damit dieser
|* ggf. eine Sonderbehandlung fuer spezielle Objekte durchfuehren kann
|* (z.B. Light/Label in E3dScene)
|*
\************************************************************************/

/*N*/ void E3dObject::NewObjectInserted(const E3dObject* p3DObj)
/*N*/ {
/*N*/   if(GetParentObj())
/*N*/       GetParentObj()->NewObjectInserted(p3DObj);
/*N*/ }

/*************************************************************************
|*
|* Parent ueber Aenderung der Struktur (z.B. durch Transformation)
|* informieren; dabei wird das Objekt, in welchem die Aenderung
|* aufgetreten ist, uebergeben
|*
\************************************************************************/

/*N*/ void E3dObject::StructureChanged(const E3dObject* p3DObj)
/*N*/ {
/*N*/   if ( GetParentObj() )
/*N*/   {
/*N*/       // Wenn sich im Child das BoundVolume geaendert hat, muessen
/*N*/       // auch die der Parents angepasst werden
/*N*/       if ( !p3DObj->bBoundVolValid )
/*N*/           GetParentObj()->bBoundVolValid = FALSE;
/*N*/
/*N*/       GetParentObj()->StructureChanged(p3DObj);
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* 3D-Objekt einfuegen
|*
\************************************************************************/

/*N*/ void E3dObject::Insert3DObj(E3dObject* p3DObj)
/*N*/ {
/*N*/   DBG_ASSERT(p3DObj, "Insert3DObj mit NULL-Zeiger!");
/*N*/   p3DObj->SetObjTreeLevel(nObjTreeLevel + 1);
/*N*/   SdrPage* pPg = pPage;
/*N*/   pSub->InsertObject(p3DObj);
/*N*/   pPage = pPg;
/*N*/   bBoundVolValid = FALSE;
/*N*/   NewObjectInserted(p3DObj);
/*N*/   StructureChanged(this);
/*N*/ }

/*N*/ void E3dObject::Remove3DObj(E3dObject* p3DObj)
/*N*/ {
/*N*/   DBG_ASSERT(p3DObj, "Remove3DObj mit NULL-Zeiger!");
/*N*/
/*N*/   if(p3DObj->GetParentObj() == this)
/*N*/   {
/*N*/       SdrPage* pPg = pPage;
/*N*/       pSub->RemoveObject(p3DObj->GetOrdNum());
/*N*/       pPage = pPg;
/*N*/
/*N*/       bBoundVolValid = FALSE;
/*N*/       StructureChanged(this);
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Parent holen
|*
\************************************************************************/

/*N*/ E3dObject* E3dObject::GetParentObj() const
/*N*/ {
/*N*/   E3dObject* pRetval = NULL;
/*N*/
/*N*/   if(GetObjList()
/*N*/       && GetObjList()->GetOwnerObj()
/*N*/       && GetObjList()->GetOwnerObj()->ISA(E3dObject))
/*N*/       pRetval = ((E3dObject*)GetObjList()->GetOwnerObj());
/*N*/   return pRetval;
/*N*/ }

/*************************************************************************
|*
|* Uebergeordnetes Szenenobjekt bestimmen
|*
\************************************************************************/

/*N*/ E3dScene* E3dObject::GetScene() const
/*N*/ {
/*N*/   if(GetParentObj())
/*N*/       return GetParentObj()->GetScene();
/*N*/   return NULL;
/*N*/ }

/*************************************************************************
|*
|* umschliessendes Volumen inklusive aller Kindobjekte berechnen
|*
\************************************************************************/

/*N*/ void E3dObject::RecalcBoundVolume()
/*N*/ {
/*N*/   E3dObjList* pOL = pSub;
/*N*/   ULONG nObjCnt = pOL->GetObjCount();
/*N*/
/*N*/   if(nObjCnt)
/*N*/   {
/*N*/       aBoundVol = Volume3D();
/*N*/
/*N*/       for (ULONG i = 0; i < nObjCnt; i++)
/*N*/       {
/*N*/           SdrObject* pObj = pOL->GetObj(i);
/*N*/
/*N*/           DBG_ASSERT(pObj->ISA(E3dObject), "In E3dObject sind nur 3D-Objekte erlaubt!");
/*N*/           // Bei den Kindobjekten auch die lokalen Transformationen
/*N*/           // beruecksichtigen
/*N*/           E3dObject* p3DObj = (E3dObject*) pObj;
/*N*/           const Volume3D& rVol = p3DObj->GetBoundVolume();
/*N*/           const Matrix4D& rTf  = p3DObj->GetTransform();
/*N*/           aBoundVol.Union(rVol.GetTransformVolume(rTf));
/*N*/       }
/*N*/
/*N*/       aLocalBoundVol = aBoundVol;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       aBoundVol = aLocalBoundVol;
/*N*/   }
/*N*/
/*N*/   bBoundVolValid = TRUE;
/*N*/ }

/*************************************************************************
|*
|* umschliessendes Volumen zurueckgeben und ggf. neu berechnen
|*
\************************************************************************/

/*N*/ const Volume3D& E3dObject::GetBoundVolume()
/*N*/ {
/*N*/   if ( !bBoundVolValid )
/*N*/       RecalcBoundVolume();
/*N*/
/*N*/   if(!aBoundVol.IsValid())
/*N*/       aBoundVol = Volume3D(Vector3D(), Vector3D());
/*N*/
/*N*/   return aBoundVol;
/*N*/ }

/*************************************************************************
|*
|* Mittelpunkt liefern
|*
\************************************************************************/

/*N*/ Vector3D E3dObject::GetCenter()
/*N*/ {
/*N*/   Volume3D aVolume = GetBoundVolume();
/*N*/   return (aVolume.MaxVec() + aVolume.MinVec()) / 2.0;
/*N*/ }

/*************************************************************************
|*
|* Aederung des BoundVolumes an alle Kindobjekte weitergeben
|*
\************************************************************************/

/*N*/ void E3dObject::SetBoundVolInvalid()
/*N*/ {
/*N*/   bBoundVolValid = FALSE;
/*N*/
/*N*/   E3dObjList* pOL = pSub;
/*N*/   ULONG nObjCnt = pOL->GetObjCount();
/*N*/
/*N*/   for (ULONG i = 0; i < nObjCnt; i++)
/*N*/   {
/*N*/       SdrObject* pObj = pOL->GetObj(i);
/*N*/       DBG_ASSERT(pObj->ISA(E3dObject), "In E3dObject sind nur 3D-Objekte erlaubt!");
/*N*/
/*N*/       ((E3dObject*) pObj)->SetBoundVolInvalid();
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Aederung der Transformation an alle Kindobjekte weitergeben
|*
\************************************************************************/

/*N*/ void E3dObject::SetTransformChanged()
/*N*/ {
/*N*/   bTfHasChanged = TRUE;
/*N*/   bBoundVolValid = FALSE;
/*N*/
/*N*/   E3dObjList* pOL = pSub;
/*N*/   ULONG nObjCnt = pOL->GetObjCount();
/*N*/
/*N*/   for (ULONG i = 0; i < nObjCnt; i++)
/*N*/   {
/*N*/       SdrObject* pObj = pOL->GetObj(i);
/*N*/       DBG_ASSERT(pObj->ISA(E3dObject), "In E3dObject sind nur 3D-Objekte erlaubt!");
/*N*/
/*N*/       ((E3dObject*) pObj)->SetTransformChanged();
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* hierarchische Transformation ueber alle Parents bestimmen und mit
|* der uebergebenen Matrix verketten
|*
\************************************************************************/

//STRIP001 void E3dObject::GetFullTransform(Matrix4D& rMatrix) const
//STRIP001 {
//STRIP001  if ( bTfHasChanged )
//STRIP001  {
//STRIP001      rMatrix *= aTfMatrix;
//STRIP001      if ( GetParentObj() )
//STRIP001          GetParentObj()->GetFullTransform(rMatrix);
//STRIP001  }
//STRIP001  else
//STRIP001      rMatrix *= aFullTfMatrix;
//STRIP001 }

/*************************************************************************
|*
|* hierarchische Transformation ueber alle Parents bestimmen, in
|* aFullTfMatrix ablegen und diese zurueckgeben
|*
\************************************************************************/

/*N*/ const Matrix4D& E3dObject::GetFullTransform()
/*N*/ {
/*N*/   if ( bTfHasChanged )
/*N*/   {
/*N*/       aFullTfMatrix = aTfMatrix;
/*N*/
/*N*/       if ( GetParentObj() )
/*N*/           aFullTfMatrix *= GetParentObj()->GetFullTransform();
/*N*/
/*N*/       bTfHasChanged = FALSE;
/*N*/   }
/*N*/
/*N*/   return aFullTfMatrix;
/*N*/ }

/*************************************************************************
|*
|* Transformationsmatrix abfragen
|*
\************************************************************************/

/*N*/ const Matrix4D& E3dObject::GetTransform() const
/*N*/ {
/*N*/   return aTfMatrix;
/*N*/ }

/*************************************************************************
|*
|* Transformationsmatrix setzen
|*
\************************************************************************/

/*N*/ void E3dObject::NbcSetTransform(const Matrix4D& rMatrix)
/*N*/ {
/*N*/   aTfMatrix = rMatrix;
/*N*/   SetTransformChanged();
/*N*/   StructureChanged(this);
/*N*/ }

/*************************************************************************
|*
|* Transformationsmatrix auf Einheitsmatrix zuruecksetzen
|*
\************************************************************************/

/*N*/ void E3dObject::NbcResetTransform()
/*N*/ {
/*N*/   aTfMatrix.Identity();
/*N*/   SetTransformChanged();
/*N*/   StructureChanged(this);
/*N*/ }

/*************************************************************************
|*
|* Transformationsmatrix setzen mit Repaint-Broadcast
|*
\************************************************************************/

/*N*/ void E3dObject::SetTransform(const Matrix4D& rMatrix)
/*N*/ {
/*N*/   SendRepaintBroadcast();
/*N*/   NbcSetTransform(rMatrix);
/*N*/   SetChanged();
/*N*/   SendRepaintBroadcast();
/*N*/   if (pUserCall != NULL) pUserCall->Changed(*this, SDRUSERCALL_RESIZE, Rectangle());
/*N*/ }

/*************************************************************************
|*
|* Transformationsmatrix zuruecksetzen mit Repaint-Broadcast
|*
\************************************************************************/

//STRIP001 void E3dObject::ResetTransform()
//STRIP001 {
//STRIP001  SendRepaintBroadcast();
//STRIP001  NbcResetTransform();
//STRIP001  SetChanged();
//STRIP001  SendRepaintBroadcast();
//STRIP001  if (pUserCall != NULL) pUserCall->Changed(*this, SDRUSERCALL_RESIZE, Rectangle());
//STRIP001 }

/*************************************************************************
|*
|* Translation
|*
\************************************************************************/

//STRIP001 void E3dObject::NbcTranslate(const Vector3D& rTrans)
//STRIP001 {
//STRIP001  aTfMatrix.Translate(rTrans);
//STRIP001  SetTransformChanged();
//STRIP001  StructureChanged(this);
//STRIP001 }
/*************************************************************************
|*
|* Translation mit Repaint-Broadcast
|*
\************************************************************************/

//STRIP001 void E3dObject::Translate(const Vector3D& rTrans)
//STRIP001 {
//STRIP001  SendRepaintBroadcast();
//STRIP001  NbcTranslate(rTrans);
//STRIP001  SetChanged();
//STRIP001  SendRepaintBroadcast();
//STRIP001  if (pUserCall != NULL) pUserCall->Changed(*this, SDRUSERCALL_RESIZE, Rectangle());
//STRIP001 }

/*************************************************************************
|*
|* Skalierungen
|*
\************************************************************************/

//STRIP001 void E3dObject::NbcScaleX(double fSx)
//STRIP001 {
//STRIP001  aTfMatrix.ScaleX(fSx);
//STRIP001  SetTransformChanged();
//STRIP001  StructureChanged(this);
//STRIP001 }

/************************************************************************/

//STRIP001 void E3dObject::NbcScaleY(double fSy)
//STRIP001 {
//STRIP001  aTfMatrix.ScaleY(fSy);
//STRIP001  SetTransformChanged();
//STRIP001  StructureChanged(this);
//STRIP001 }

/************************************************************************/

//STRIP001 void E3dObject::NbcScaleZ(double fSz)
//STRIP001 {
//STRIP001  aTfMatrix.ScaleZ(fSz);
//STRIP001  SetTransformChanged();
//STRIP001  StructureChanged(this);
//STRIP001 }

/************************************************************************/

//STRIP001 void E3dObject::NbcScale(double fSx, double fSy, double fSz)
//STRIP001 {
//STRIP001  aTfMatrix.Scale(fSx, fSy, fSz);
//STRIP001  SetTransformChanged();
//STRIP001  StructureChanged(this);
//STRIP001 }

/*************************************************************************
|*
|* gleichmaessige Skalierung
|*
\************************************************************************/

//STRIP001 void E3dObject::NbcScale(double fS)
//STRIP001 {
//STRIP001  aTfMatrix.Scale(fS, fS, fS);
//STRIP001  SetTransformChanged();
//STRIP001  StructureChanged(this);
//STRIP001 }

/*************************************************************************
|*
|* Skalierungen mit mit Repaint-Broadcast
|*
\************************************************************************/

//STRIP001 void E3dObject::ScaleX(double fSx)
//STRIP001 {
//STRIP001  SendRepaintBroadcast();
//STRIP001  NbcScaleX(fSx);
//STRIP001  SetChanged();
//STRIP001  SendRepaintBroadcast();
//STRIP001  if (pUserCall != NULL) pUserCall->Changed(*this, SDRUSERCALL_RESIZE, Rectangle());
//STRIP001 }

/************************************************************************/

//STRIP001 void E3dObject::ScaleY(double fSy)
//STRIP001 {
//STRIP001  SendRepaintBroadcast();
//STRIP001  NbcScaleY(fSy);
//STRIP001  SetChanged();
//STRIP001  SendRepaintBroadcast();
//STRIP001  if (pUserCall != NULL) pUserCall->Changed(*this, SDRUSERCALL_RESIZE, Rectangle());
//STRIP001 }

/************************************************************************/

//STRIP001 void E3dObject::ScaleZ(double fSz)
//STRIP001 {
//STRIP001  SendRepaintBroadcast();
//STRIP001  NbcScaleZ(fSz);
//STRIP001  SetChanged();
//STRIP001  SendRepaintBroadcast();
//STRIP001  if (pUserCall != NULL) pUserCall->Changed(*this, SDRUSERCALL_RESIZE, Rectangle());
//STRIP001 }

/************************************************************************/

//STRIP001 void E3dObject::Scale(double fSx, double fSy, double fSz)
//STRIP001 {
//STRIP001  SendRepaintBroadcast();
//STRIP001  NbcScale(fSx, fSy, fSz);
//STRIP001  SetChanged();
//STRIP001  SendRepaintBroadcast();
//STRIP001  if (pUserCall != NULL) pUserCall->Changed(*this, SDRUSERCALL_RESIZE, Rectangle());
//STRIP001 }

/************************************************************************/

//STRIP001 void E3dObject::Scale(double fS)
//STRIP001 {
//STRIP001  SendRepaintBroadcast();
//STRIP001  NbcScale(fS);
//STRIP001  SetChanged();
//STRIP001  SendRepaintBroadcast();
//STRIP001  if (pUserCall != NULL) pUserCall->Changed(*this, SDRUSERCALL_RESIZE, Rectangle());
//STRIP001 }

/*************************************************************************
|*
|* Rotationen mit Winkel in Radiant
|*
\************************************************************************/

//STRIP001 void E3dObject::NbcRotateX(double fAng)
//STRIP001 {
//STRIP001  aTfMatrix.RotateX(fAng);
//STRIP001  SetTransformChanged();
//STRIP001  StructureChanged(this);
//STRIP001 }

/************************************************************************/

//STRIP001 void E3dObject::NbcRotateY(double fAng)
//STRIP001 {
//STRIP001  aTfMatrix.RotateY(fAng);
//STRIP001  SetTransformChanged();
//STRIP001  StructureChanged(this);
//STRIP001 }

/************************************************************************/

//STRIP001 void E3dObject::NbcRotateZ(double fAng)
//STRIP001 {
//STRIP001  aTfMatrix.RotateZ(fAng);
//STRIP001  SetTransformChanged();
//STRIP001  StructureChanged(this);
//STRIP001 }

/*************************************************************************
|*
|* Rotationen mit Repaint-Broadcast
|*
\************************************************************************/

//STRIP001 void E3dObject::RotateX(double fAng)
//STRIP001 {
//STRIP001  SendRepaintBroadcast();
//STRIP001  NbcRotateX(fAng);
//STRIP001  SetChanged();
//STRIP001  SendRepaintBroadcast();
//STRIP001  if (pUserCall != NULL) pUserCall->Changed(*this, SDRUSERCALL_RESIZE, Rectangle());
//STRIP001 }

/************************************************************************/

//STRIP001 void E3dObject::RotateY(double fAng)
//STRIP001 {
//STRIP001  SendRepaintBroadcast();
//STRIP001  NbcRotateY(fAng);
//STRIP001  SetChanged();
//STRIP001  SendRepaintBroadcast();
//STRIP001  if (pUserCall != NULL) pUserCall->Changed(*this, SDRUSERCALL_RESIZE, Rectangle());
//STRIP001 }

/************************************************************************/

//STRIP001 void E3dObject::RotateZ(double fAng)
//STRIP001 {
//STRIP001  SendRepaintBroadcast();
//STRIP001  NbcRotateZ(fAng);
//STRIP001  SetChanged();
//STRIP001  SendRepaintBroadcast();
//STRIP001  if (pUserCall != NULL) pUserCall->Changed(*this, SDRUSERCALL_RESIZE, Rectangle());
//STRIP001 }

/*************************************************************************
|*
|* Objektbaum-Ebene des Objekts und aller Children setzen
|*
\************************************************************************/

/*N*/ void E3dObject::SetObjTreeLevel(USHORT nNewLevel)
/*N*/ {
/*N*/   nObjTreeLevel = nNewLevel;
/*N*/   nNewLevel++;
/*N*/
/*N*/   E3dObjList* pOL = pSub;
/*N*/   ULONG nObjCnt = pOL->GetObjCount();
/*N*/
/*N*/   for (ULONG i = 0; i < nObjCnt; i++)
/*N*/   {
/*N*/       SdrObject* pObj = pOL->GetObj(i);
/*N*/       DBG_ASSERT(pObj->ISA(E3dObject), "In E3dObject sind nur 3D-Objekte erlaubt!");
/*N*/
/*N*/       ((E3dObject*) pObj)->SetObjTreeLevel(nNewLevel);
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* logische Gruppe setzen
|*
\************************************************************************/

//STRIP001 void E3dObject::SetLogicalGroup(USHORT nGroup)
//STRIP001 {
//STRIP001  nLogicalGroup = nGroup;
//STRIP001 }

/*************************************************************************
|*
|* Linien fuer die Wireframe-Darstellung des Objekts dem uebergebenen
|* Polygon3D hinzufuegen. Als default wird das BoundVolume verwendet.
|*
\************************************************************************/

//STRIP001 void E3dObject::CreateWireframe(Polygon3D& rWirePoly, const Matrix4D* pTf,
//STRIP001  E3dDragDetail eDetail)
//STRIP001 {
//STRIP001  if ( eDetail == E3DDETAIL_DEFAULT )
//STRIP001      eDetail = eDragDetail;
//STRIP001
//STRIP001  if ( eDetail == E3DDETAIL_ALLBOXES || eDetail == E3DDETAIL_ALLLINES )
//STRIP001  {
//STRIP001      E3dObjList* pOL = pSub;
//STRIP001      ULONG nObjCnt = pOL->GetObjCount();
//STRIP001
//STRIP001      for (ULONG i = 0; i < nObjCnt; i++)
//STRIP001      {
//STRIP001          E3dObject* pObj = (E3dObject*)pOL->GetObj(i);
//STRIP001          DBG_ASSERT(pObj->ISA(E3dObject), "In E3dObject sind nur 3D-Objekte erlaubt!");
//STRIP001
//STRIP001          Matrix4D aLocalTf(pObj->GetTransform());
//STRIP001          if(pTf)
//STRIP001              aLocalTf *= *pTf;
//STRIP001          pObj->CreateWireframe(rWirePoly, &aLocalTf, eDetail);
//STRIP001      }
//STRIP001
//STRIP001      if(eDetail == E3DDETAIL_ALLBOXES && nObjCnt != 1)
//STRIP001          GetBoundVolume().CreateWireframe(rWirePoly, pTf);
//STRIP001  }
//STRIP001  else
//STRIP001      GetBoundVolume().CreateWireframe(rWirePoly, pTf);
//STRIP001 }

/*************************************************************************
|*
|* Get the name of the object (singular)
|*
\************************************************************************/

//STRIP001 void E3dObject::TakeObjNameSingul(XubString& rName) const
//STRIP001 {
//STRIP001  rName=ImpGetResStr(STR_ObjNameSingulObj3d);
//STRIP001
//STRIP001  String aName( GetName() );
//STRIP001  if(aName.Len())
//STRIP001  {
//STRIP001      rName += sal_Unicode(' ');
//STRIP001      rName += sal_Unicode('\'');
//STRIP001      rName += aName;
//STRIP001      rName += sal_Unicode('\'');
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Get the name of the object (plural)
|*
\************************************************************************/

//STRIP001 void E3dObject::TakeObjNamePlural(XubString& rName) const
//STRIP001 {
//STRIP001  rName=ImpGetResStr(STR_ObjNamePluralObj3d);
//STRIP001 }

/*************************************************************************
|*
|* Wireframe-XPolyPolygon erzeugen
|*
\************************************************************************/

//STRIP001 void E3dObject::ImpCreateWireframePoly(XPolyPolygon& rXPP,
//STRIP001  E3dDragDetail eDetail)
//STRIP001 {
//STRIP001  // Neue Methode
//STRIP001  E3dScene* pScene = GetScene();
//STRIP001  Polygon3D aPoly3D(24, 240);
//STRIP001  XPolygon aLine(2);
//STRIP001  USHORT nPntCnt;
//STRIP001
//STRIP001  // WireFrame herstellen
//STRIP001  CreateWireframe(aPoly3D, NULL, eDetail);
//STRIP001  nPntCnt = aPoly3D.GetPointCount();
//STRIP001
//STRIP001  if(pScene)
//STRIP001  {
//STRIP001      // Maximas holen in DeviceKoordinaten
//STRIP001      Volume3D aVolume = pScene->FitInSnapRect();
//STRIP001
//STRIP001      // Maximas fuer Abbildung verwenden
//STRIP001      pScene->GetCameraSet().SetDeviceVolume(aVolume, FALSE);
//STRIP001      Matrix4D mTransform = GetFullTransform();
//STRIP001      pScene->GetCameraSet().SetObjectTrans(mTransform);
//STRIP001
//STRIP001      if ( nPntCnt > 1 )
//STRIP001      {
//STRIP001          Vector3D aVec;
//STRIP001          for ( USHORT i = 0; i < nPntCnt; i += 2 )
//STRIP001          {
//STRIP001              aVec = pScene->GetCameraSet().ObjectToViewCoor(aPoly3D[i]);
//STRIP001              aLine[0] = Point((long)(aVec.X() + 0.5), (long)(aVec.Y() + 0.5));
//STRIP001
//STRIP001              aVec = pScene->GetCameraSet().ObjectToViewCoor(aPoly3D[i+1]);
//STRIP001              aLine[1] = Point((long)(aVec.X() + 0.5), (long)(aVec.Y() + 0.5));
//STRIP001
//STRIP001              rXPP.Insert(aLine);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Drag-Polygon zurueckgeben
|*
\************************************************************************/

//STRIP001 void E3dObject::TakeXorPoly(XPolyPolygon& rXPP, FASTBOOL bDetail) const
//STRIP001 {
//STRIP001  rXPP.Clear();
//STRIP001  // Const mal wieder weg, da evtl. das BoundVolume neu generiert wird
//STRIP001  static E3dDragDetail eDetail = E3DDETAIL_DEFAULT;
//STRIP001  ((E3dObject*) this)->ImpCreateWireframePoly(rXPP, eDetail);
//STRIP001 }

/*************************************************************************
|*
|* Zuweisungsoperator
|*
\************************************************************************/

//STRIP001 void E3dObject::operator=(const SdrObject& rObj)
//STRIP001 {
//STRIP001  // erstmal alle Childs kopieren
//STRIP001  SdrAttrObj::operator=(rObj);
//STRIP001
//STRIP001  const E3dObject& r3DObj = (const E3dObject&) rObj;
//STRIP001  if (r3DObj.GetSubList())
//STRIP001  {
//STRIP001      // feststellen, ob alle SubObjekte selektiert oder
//STRIP001      // deselektiert sind
//STRIP001      BOOL bAllSelected = TRUE;
//STRIP001      BOOL bNoneSelected = TRUE;
//STRIP001      UINT32 nObjCnt = r3DObj.GetSubList()->GetObjCount();
//STRIP001
//STRIP001      ULONG i;
//STRIP001      for (i = 0; i < nObjCnt; i++)
//STRIP001      {
//STRIP001          SdrObject* pObj = r3DObj.GetSubList()->GetObj(i);
//STRIP001          if(pObj && pObj->ISA(E3dObject))
//STRIP001          {
//STRIP001              E3dObject* p3DObj = (E3dObject*)pObj;
//STRIP001              if(p3DObj->GetSelected())
//STRIP001                  bNoneSelected = FALSE;
//STRIP001              else
//STRIP001                  bAllSelected = FALSE;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if(bAllSelected || bNoneSelected)
//STRIP001      {
//STRIP001          // Normales verhalten
//STRIP001          pSub->CopyObjects(*r3DObj.GetSubList());
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // Spezielle SubListe aufstellen, kopieren
//STRIP001          SdrObjList aOwnSubList(*r3DObj.GetSubList());
//STRIP001
//STRIP001          // Alle nicht selektierten Objekte rausschmeissen
//STRIP001          for(i = 0;i < aOwnSubList.GetObjCount();i++)
//STRIP001          {
//STRIP001              SdrObject* pObj = aOwnSubList.GetObj(i);
//STRIP001              if(pObj && pObj->ISA(E3dObject))
//STRIP001              {
//STRIP001                  E3dObject* p3DObj = (E3dObject*)pObj;
//STRIP001                  if(!p3DObj->GetSelected())
//STRIP001                  {
//STRIP001                      aOwnSubList.NbcRemoveObject(pObj->GetOrdNum());
//STRIP001                      i--;
//STRIP001                      delete pObj;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          // jetzt diese Liste kopieren
//STRIP001          pSub->CopyObjects(aOwnSubList);
//STRIP001
//STRIP001          // Hier noch ein FitSnapRect einleiten
//STRIP001          if(ISA(E3dScene))
//STRIP001              ((E3dScene&)r3DObj).FitSnapRectToBoundVol();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // BoundVol kann uebernommen werden, da die Childs auch kopiert werden
//STRIP001  bBoundVolValid  = r3DObj.bBoundVolValid;
//STRIP001  aBoundVol       = r3DObj.aBoundVol;
//STRIP001  aLocalBoundVol  = r3DObj.aLocalBoundVol;
//STRIP001
//STRIP001  aTfMatrix       = r3DObj.aTfMatrix;
//STRIP001  nLogicalGroup   = r3DObj.nLogicalGroup;
//STRIP001  nObjTreeLevel   = r3DObj.nObjTreeLevel;
//STRIP001  nPartOfParent   = r3DObj.nPartOfParent;
//STRIP001  eDragDetail     = r3DObj.eDragDetail;
//STRIP001
//STRIP001  // Da sich der Parent geaendert haben kann, Gesamttransformation beim
//STRIP001  // naechsten Mal auf jeden Fall neu bestimmen
//STRIP001  SetTransformChanged();
//STRIP001
//STRIP001  // Selektionsstatus kopieren
//STRIP001  bIsSelected = r3DObj.bIsSelected;
//STRIP001 }

//////////////////////////////////////////////////////////////////////////////
// ItemSet access

/*N*/ const SfxItemSet& E3dObject::GetItemSet() const
/*N*/ {
/*N*/   // include Items of scene this object belongs to
/*N*/   E3dScene* pScene = GetScene();
/*N*/   if(pScene && pScene != this)
/*N*/   {
/*N*/       SfxItemSet& rSet = (SfxItemSet&)SdrAttrObj::GetItemSet();
/*N*/       SfxItemSet aSet(*rSet.GetPool(), SDRATTR_3DSCENE_FIRST, SDRATTR_3DSCENE_LAST);
/*N*/       aSet.Put(pScene->E3dObject::GetItemSet());
/*N*/       rSet.Put(aSet);
/*N*/   }
/*N*/
/*N*/   return SdrAttrObj::GetItemSet();
/*N*/ }

/*N*/ SfxItemSet* E3dObject::CreateNewItemSet(SfxItemPool& rPool)
/*N*/ {
/*N*/   // include ALL items, 2D and 3D
/*N*/   return new SfxItemSet(rPool,
/*N*/       // ranges from SdrAttrObj
/*N*/       SDRATTR_START, SDRATTRSET_SHADOW,
/*N*/       SDRATTRSET_OUTLINER, SDRATTRSET_MISC,
/*N*/
/*N*/       // ranges for 3D (object and scene)
/*N*/       SDRATTR_3D_FIRST, SDRATTR_3D_LAST,
/*N*/
/*N*/       // outliner and end
/*N*/       EE_ITEMS_START, EE_ITEMS_END,
/*N*/       0, 0);
/*N*/ }

// private support routines for ItemSet access. NULL pointer means clear item.
/*N*/ void E3dObject::ItemChange(const sal_uInt16 nWhich, const SfxPoolItem* pNewItem)
/*N*/ {
/*N*/   // propagate item changes to scene
/*N*/   if(!nWhich || (nWhich >= SDRATTR_3DSCENE_FIRST && nWhich <= SDRATTR_3DSCENE_LAST))
/*N*/   {
/*N*/       E3dScene* pScene = GetScene();
/*N*/       if(pScene && pScene != this)
/*N*/           pScene->E3dObject::ItemChange(nWhich, pNewItem);
/*N*/   }
/*N*/
/*N*/   // call parent
/*N*/   SdrAttrObj::ItemChange(nWhich, pNewItem);
/*N*/ }

// #107770# Like propagating ItemChange to the scene if scene items are changed,
// do the same with the PostItemChange calls.
/*N*/ void E3dObject::PostItemChange(const sal_uInt16 nWhich)
/*N*/ {
/*N*/   // propagate item changes to scene
/*N*/   if(!nWhich || (nWhich >= SDRATTR_3DSCENE_FIRST && nWhich <= SDRATTR_3DSCENE_LAST))
/*N*/   {
/*N*/       E3dScene* pScene = GetScene();
/*N*/       if(pScene && pScene != this)
/*N*/           pScene->PostItemChange(nWhich);
/*N*/   }
/*N*/
/*N*/   // call parent
/*N*/   SdrAttrObj::PostItemChange(nWhich);
/*N*/ }

/*N*/ void E3dObject::ItemSetChanged( const SfxItemSet& rSet )
/*N*/ {
/*N*/   // call parent
/*N*/   SdrAttrObj::ItemSetChanged( rSet );
/*N*/
/*N*/   // local changes
/*N*/   StructureChanged(this);
/*N*/ }

/*************************************************************************
|*
|* StyleSheet setzen
|*
\************************************************************************/

/*N*/ void E3dObject::NbcSetStyleSheet(SfxStyleSheet* pNewStyleSheet,
/*N*/   FASTBOOL bDontRemoveHardAttr)
/*N*/ {
/*N*/   // call parent
/*N*/   SdrAttrObj::NbcSetStyleSheet(pNewStyleSheet, bDontRemoveHardAttr);
/*N*/
/*N*/   E3dObjList* pOL = pSub;
/*N*/   ULONG nObjCnt = pOL->GetObjCount();
/*N*/   for ( ULONG i = 0; i < nObjCnt; i++ )
/*?*/       pOL->GetObj(i)->NbcSetStyleSheet(pNewStyleSheet, bDontRemoveHardAttr);
/*N*/ }

/*************************************************************************
|*
|* Nur die Member des E3dObjekts in den Stream speichern
|* Dies wird direkt auch von E3dSphere gerufen um zu verhindern dass die
|* Subliste weggeschrieben wird. (FG)
|*
\************************************************************************/

/*N*/ #ifndef SVX_LIGHT
/*N*/ void E3dObject::WriteOnlyOwnMembers(SvStream& rOut) const
/*N*/ {
/*N*/   // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/   SdrDownCompat aCompat(rOut, STREAM_WRITE);
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("E3dObjectOwnMembers");
/*N*/ #endif
/*N*/
/*N*/   rOut << aLocalBoundVol;
/*N*/
/*N*/   Old_Matrix3D aMat3D;
/*N*/   aMat3D = aTfMatrix;
/*N*/   rOut << aMat3D;
/*N*/
/*N*/   rOut << nLogicalGroup;
/*N*/   rOut << nObjTreeLevel;
/*N*/   rOut << nPartOfParent;
/*N*/   rOut << UINT16(eDragDetail);
/*N*/ }
/*N*/ #endif

/*************************************************************************
|*
|* Objektdaten in Stream speichern
|*
\************************************************************************/

/*N*/ void E3dObject::WriteData(SvStream& rOut) const
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   long position = rOut.Tell();
/*N*/   SdrAttrObj::WriteData(rOut);
/*N*/   position = rOut.Tell();
/*N*/
/*N*/   // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/   SdrDownCompat aCompat(rOut, STREAM_WRITE);
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("E3dObject");
/*N*/ #endif
/*N*/
/*N*/   position = rOut.Tell();
/*N*/   pSub->Save(rOut);
/*N*/   position = rOut.Tell();
/*N*/
/*N*/   if (rOut.GetVersion() < 3560)
/*N*/   {
/*N*/       rOut << aLocalBoundVol;
/*N*/
/*N*/       Old_Matrix3D aMat3D;
/*N*/       aMat3D = aTfMatrix;
/*N*/       rOut << aMat3D;
/*N*/
/*N*/       rOut << nLogicalGroup;
/*N*/       rOut << nObjTreeLevel;
/*N*/       rOut << nPartOfParent;
/*N*/       rOut << UINT16(eDragDetail);
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       WriteOnlyOwnMembers(rOut);
/*N*/   }
/*N*/   position = rOut.Tell();
/*N*/ #endif
/*N*/ }

/*************************************************************************
|*
|* Objektdaten aus Stream laden
|*
\************************************************************************/

/*N*/ void E3dObject::ReadData(const SdrObjIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   long position = rIn.Tell();
/*N*/   if (ImpCheckSubRecords (rHead, rIn))
/*N*/   {
/*N*/       position = rIn.Tell();
/*N*/       SdrAttrObj::ReadData(rHead, rIn);
/*N*/       position = rIn.Tell();
/*N*/       // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/       SdrDownCompat aCompat(rIn, STREAM_READ);
/*N*/ #ifdef DBG_UTIL
/*N*/       aCompat.SetID("E3dObject");
/*N*/ #endif
/*N*/       pSub->Load(rIn, *pPage);
/*N*/
/*N*/       position = rIn.Tell();
/*N*/       if ((rIn.GetVersion() < 3560) || (rHead.GetVersion() <= 12))
/*N*/       {
/*N*/           UINT16  nTmp16;
/*N*/
/*N*/           rIn >> aLocalBoundVol;
/*N*/
/*N*/           Old_Matrix3D aMat3D;
/*N*/           rIn >> aMat3D;
/*N*/           aTfMatrix = Matrix4D(aMat3D);
/*N*/
/*N*/           rIn >> nLogicalGroup;
/*N*/           rIn >> nObjTreeLevel;
/*N*/           rIn >> nPartOfParent;
/*N*/           rIn >> nTmp16; eDragDetail = E3dDragDetail(nTmp16);
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           ReadOnlyOwnMembers(rHead, rIn);
/*N*/       }
/*N*/       position = rIn.Tell();
/*N*/
/*N*/       // Wie ein veraendertes Objekt behandeln
/*N*/       SetTransformChanged();
/*N*/       StructureChanged(this);
/*N*/
/*N*/       // BoundVolume muss neu berechnet werden
/*N*/       bBoundVolValid = FALSE;
/*N*/
/*N*/       // SnapRect auch
/*N*/       bSnapRectDirty = TRUE;
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Nur die Daten des E3dObject aus Stream laden (nicht der Sublisten und
|* der Basisklassen). Wird von E3dSphere auch genutzt. (FileFormat-Optimierung)
|*
\************************************************************************/

/*N*/ void E3dObject::ReadOnlyOwnMembers(const SdrObjIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/   SdrDownCompat aCompat(rIn, STREAM_READ);
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("E3dObjectOwnMembers");
/*N*/ #endif
/*N*/   UINT16  nTmp16;
/*N*/
/*N*/   rIn >> aLocalBoundVol;
/*N*/
/*N*/   Old_Matrix3D aMat3D;
/*N*/   rIn >> aMat3D;
/*N*/   aTfMatrix = Matrix4D(aMat3D);
/*N*/
/*N*/   rIn >> nLogicalGroup;
/*N*/   rIn >> nObjTreeLevel;
/*N*/   rIn >> nPartOfParent;
/*N*/   rIn >> nTmp16; eDragDetail = E3dDragDetail(nTmp16);
/*N*/
/*N*/   bBoundVolValid = FALSE;
/*N*/ }


/*************************************************************************
|*
|* nach dem Laden...
|*
\************************************************************************/

/*N*/ void E3dObject::AfterRead()
/*N*/ {
/*N*/   SdrAttrObj::AfterRead();
/*N*/   if (pSub)
/*N*/       pSub->AfterRead();
/*N*/ }

/*************************************************************************
|*
|* erstelle neues GeoData-Objekt
|*
\************************************************************************/

/*N*/ SdrObjGeoData *E3dObject::NewGeoData() const
/*N*/ {
/*N*/   // Theoretisch duerfen auch nur Szenen ihre GeoDatas erstellen und verwalten !!
/*N*/   // AW: Dies stimmt nicht mehr, diese Stelle ist mit der neuen Engine OK!
/*N*/   return new E3DObjGeoData;
/*N*/ }

/*************************************************************************
|*
|* uebergebe aktuelle werte an das GeoData-Objekt
|*
\************************************************************************/

/*N*/ void E3dObject::SaveGeoData(SdrObjGeoData& rGeo) const
/*N*/ {
/*N*/   SdrAttrObj::SaveGeoData (rGeo);
/*N*/
/*N*/   ((E3DObjGeoData &) rGeo).aLocalBoundVol  = aLocalBoundVol;
/*N*/   ((E3DObjGeoData &) rGeo).aTfMatrix       = aTfMatrix;
/*N*/ }

/*************************************************************************
|*
|* uebernehme werte aus dem GeoData-Objekt
|*
\************************************************************************/

/*N*/ void E3dObject::RestGeoData(const SdrObjGeoData& rGeo)
/*N*/ {
/*N*/   aLocalBoundVol = ((E3DObjGeoData &) rGeo).aLocalBoundVol;
/*N*/   NbcSetTransform (((E3DObjGeoData &) rGeo).aTfMatrix);
/*N*/
/*N*/   SdrAttrObj::RestGeoData (rGeo);
/*N*/   GetScene()->FitSnapRectToBoundVol();
/*N*/ }

/*************************************************************************
|*
|* Pruefe, ob die SubRecords ok sind und mit der Factory gelesen werden
|* koennen.
|*
\************************************************************************/

/*N*/ BOOL E3dObject::ImpCheckSubRecords (const SdrObjIOHeader& rHead,
/*N*/                                   SvStream&             rIn)
/*N*/ {
/*N*/   BOOL bDoRead = FALSE;
/*N*/
/*N*/   if ( rIn.GetError() == SVSTREAM_OK )
/*N*/   {
/*N*/       if (rHead.GetVersion () <= 12)
/*N*/       {
/*N*/           ULONG nPos0 = rIn.Tell();
/*N*/           // Einen SubRecord ueberspringen (SdrObject)
/*N*/           { SdrDownCompat aCompat(rIn,STREAM_READ); }
/*N*/           // Nocheinen SubRecord ueberspringen (SdrAttrObj)
/*N*/           { SdrDownCompat aCompat(rIn,STREAM_READ); }
/*N*/           // Und nun muesste meiner kommen
/*N*/           bDoRead = rHead.GetBytesLeft() != 0;
/*N*/           rIn.Seek (nPos0); // FilePos wieder restaurieren
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           bDoRead = TRUE;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return bDoRead;
/*N*/ }

/*************************************************************************
|*
|* Keine DefaultAttr, zu langsam
|*
\************************************************************************/

/*N*/ void E3dObject::ForceDefaultAttr()
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Falls doch noch DefaultAttrs benoetigt werden
|*
\************************************************************************/

/*N*/ void E3dObject::ForceDefaultAttrAgain()
/*N*/ {
/*N*/   SdrAttrObj::ForceDefaultAttr();
/*N*/ }

/*************************************************************************
|*
|* Rotation eines 3d-Koerpers
|*
\************************************************************************/
// 2D-rotation eines 3D-Koerpers, normalerweise macht das die Szene selbst
// Ist aber eine korrekte Implementierung, denn alles was passiert ist eine
// Rotation um die Achse die senkrecht auf dem Bildschirm steht und zwar
// unabhaengig davon, wie die Szene bisher gedreht worden ist.

//STRIP001 void E3dObject::NbcRotate(const Point& rRef, long nWink, double sn, double cs)
//STRIP001 {
//STRIP001      // Also derzeit sind die Klebepunkte relativ zum aOutRect der Szene definiert. Vor dem Drehen
//STRIP001      // werden die Klebepunkte relativ zur Seite definiert. Sie nehmen an der Drehung der Szene noch nicht Teil
//STRIP001      // dafuer gibt es den
//STRIP001  SetGlueReallyAbsolute(TRUE);
//STRIP001
//STRIP001  // SendRepaintBroadcast();
//STRIP001  double fWinkelInRad = nWink/100 * F_PI180;
//STRIP001  NbcRotateZ(fWinkelInRad);
//STRIP001  SetRectsDirty();    // Veranlasst eine Neuberechnung aller BoundRects
//STRIP001  NbcRotateGluePoints(rRef,nWink,sn,cs);  // Rotiert die Klebepunkte (die haben noch Koordinaten relativ
//STRIP001                                          // zum Urpsung des Blattes
//STRIP001  SetGlueReallyAbsolute(FALSE);  // ab jetzt sind sie wieder relativ zum BoundRect (also dem aOutRect definiert)
//STRIP001 }

/*************************************************************************/

/*N*/ TYPEINIT1(E3dCompoundObject, E3dObject);

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ E3dCompoundObject::E3dCompoundObject() : E3dObject()
/*N*/ {
/*N*/   // Defaults setzen
/*N*/   E3dDefaultAttributes aDefault;
/*N*/   SetDefaultAttributes(aDefault);
/*N*/
/*N*/   bBytesLeft = FALSE;
/*N*/   bCreateE3dPolyObj = FALSE;
/*N*/   bGeometryValid = FALSE;
/*N*/ }

/*N*/ E3dCompoundObject::E3dCompoundObject(E3dDefaultAttributes& rDefault) : E3dObject()
/*N*/ {
/*N*/   // Defaults setzen
/*N*/   SetDefaultAttributes(rDefault);
/*N*/
/*N*/   bBytesLeft = FALSE;
/*N*/   bCreateE3dPolyObj = FALSE;
/*N*/   bGeometryValid = FALSE;
/*N*/ }

/*N*/ void E3dCompoundObject::SetDefaultAttributes(E3dDefaultAttributes& rDefault)
/*N*/ {
/*N*/   // Defaults setzen
/*N*/   aMaterialAmbientColor = rDefault.GetDefaultAmbientColor();
/*N*/
/*N*/   aBackMaterial = rDefault.GetDefaultBackMaterial();
/*N*/   bCreateNormals = rDefault.GetDefaultCreateNormals();
/*N*/   bCreateTexture = rDefault.GetDefaultCreateTexture();
/*N*/   bUseDifferentBackMaterial = rDefault.GetDefaultUseDifferentBackMaterial();
/*N*/ }

/*************************************************************************
|*
|* Destruktor
|*
\************************************************************************/

/*N*/ E3dCompoundObject::~E3dCompoundObject ()
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Start der Geometrieerzeugung ankuendigen
|*
\************************************************************************/

/*N*/ void E3dCompoundObject::StartCreateGeometry()
/*N*/ {
/*N*/   // Geometriestart mitteilen
/*N*/   aDisplayGeometry.StartDescription();
/*N*/
/*N*/   // Lokales Volumen reset
/*N*/   aLocalBoundVol = Volume3D();
/*N*/
/*N*/   // Geometrie ist ab jetzt gueltig, um ein rekursives weiteres
/*N*/   // Erzeugen zu verhindern
/*N*/   bGeometryValid = TRUE;
/*N*/ }

/*************************************************************************
|*
|* Identifier zurueckgeben
|*
\************************************************************************/

/*N*/ UINT16 E3dCompoundObject::GetObjIdentifier() const
/*N*/ {
/*N*/   return E3D_COMPOUNDOBJ_ID;
/*N*/ }

/*************************************************************************
|*
|* Compounds brauchen Defaults
|*
\************************************************************************/

/*N*/ void E3dCompoundObject::ForceDefaultAttr()
/*N*/ {
/*N*/   SdrAttrObj::ForceDefaultAttr();
/*N*/ }

/*************************************************************************
|*
|* SnapRect berechnen
|*
\************************************************************************/

/*N*/ void E3dCompoundObject::RecalcSnapRect()
/*N*/ {
/*N*/   E3dScene* pScene = GetScene();
/*N*/   if(pScene)
/*N*/   {
/*N*/       // Objekttransformation uebernehmen
/*N*/       const Volume3D& rBoundVol = GetBoundVolume();
/*N*/       maSnapRect = Rectangle();
/*N*/
/*N*/       if(rBoundVol.IsValid())
/*N*/       {
/*N*/           const Matrix4D& rTrans = GetFullTransform();
/*N*/           Vol3DPointIterator aIter(rBoundVol, &rTrans);
/*N*/           Vector3D aTfVec;
/*N*/           while ( aIter.Next(aTfVec) )
/*N*/           {
/*N*/               aTfVec = pScene->GetCameraSet().WorldToViewCoor(aTfVec);
/*N*/               Point aPoint((long)(aTfVec.X() + 0.5), (long)(aTfVec.Y() + 0.5));
/*N*/               maSnapRect.Union(Rectangle(aPoint, aPoint));
/*N*/           }
/*N*/       }
/*N*/       bSnapRectDirty = FALSE;
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* BoundRect berechnen und evtl. Schatten einbeziehen
|* Dazu muss ein eventueller Schatten des einzelnen 3D-Objektes
|* beruecksichtigt werden
|*
\************************************************************************/

/*N*/ void E3dCompoundObject::RecalcBoundRect()
/*N*/ {
/*N*/   // BoundRect aus SnapRect berechnen
/*N*/   aOutRect = GetSnapRect();
/*N*/
/*N*/   E3dScene* pScene = GetScene();
/*N*/   if(pScene)
/*N*/   {
/*N*/       // Schatten beruecksichtigen
/*N*/       if(DoDrawShadow())
/*N*/       {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            // ObjectTrans setzen
//STRIP001 /*?*/            Matrix4D mTransform = GetFullTransform();
//STRIP001 /*?*/            pScene->GetCameraSet().SetObjectTrans(mTransform);
//STRIP001 /*?*/
//STRIP001 /*?*/            // Schattenpolygon holen
//STRIP001 /*?*/            PolyPolygon3D aShadowPoly3D;
//STRIP001 /*?*/            ImpGetShadowPolygon(aShadowPoly3D);
//STRIP001 /*?*/
//STRIP001 /*?*/            // invert Y coor cause of GetPolyPolygon() later
//STRIP001 /*?*/            Matrix4D aTransMat;
//STRIP001 /*?*/            aTransMat.Scale(1.0, -1.0, 1.0);
//STRIP001 /*?*/            aShadowPoly3D.Transform(aTransMat);
//STRIP001 /*?*/
//STRIP001 /*?*/            PolyPolygon aShadowPoly(aShadowPoly3D.GetPolyPolygon());
//STRIP001 /*?*/
//STRIP001 /*?*/            // Hinzufuegen
//STRIP001 /*?*/            aOutRect.Union(aShadowPoly.GetBoundRect());
/*N*/       }

        // Linienbreite beruecksichtigen
/*N*/       INT32 nLineWidth = ((const XLineWidthItem&)(GetItem(XATTR_LINEWIDTH))).GetValue();
/*N*/       if(nLineWidth)
/*N*/       {
/*?*/           Rectangle aShadowRect = aOutRect;
/*?*/           aShadowRect.Left() -= nLineWidth;
/*?*/           aShadowRect.Right() += nLineWidth;
/*?*/           aShadowRect.Top() -= nLineWidth;
/*?*/           aShadowRect.Bottom() += nLineWidth;
/*?*/           aOutRect.Union(aShadowRect);
/*N*/       }
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* BoundVolume holen. Falls die Geometrie ungueltig ist, diese neu
|* erzeugen und das BoundVol neu berechnen
|*
\************************************************************************/

/*N*/ const Volume3D& E3dCompoundObject::GetBoundVolume()
/*N*/ {
/*N*/   // Geometrie aktuell?
/*N*/   if(!bGeometryValid)
/*N*/   {
/*N*/       // Neu erzeugen und eine Neubestimmung des BoundVol erzwingen
/*N*/       ReCreateGeometry();
/*N*/       bBoundVolValid = FALSE;
/*N*/   }
/*N*/
/*N*/   // call parent
/*N*/   return E3dObject::GetBoundVolume();
/*N*/ }

/*************************************************************************
|*
|* Rausschreiben der Datenmember eines E3dCompounds
|*
\************************************************************************/

/*N*/ void E3dCompoundObject::WriteData(SvStream& rOut) const
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/ #ifdef E3D_STREAMING
/*N*/
/*N*/   if (!aLocalBoundVol.IsValid() && aBoundVol.IsValid())
/*N*/   {
/*N*/       // Das aLocalBoundVol wird gespeichert.
/*N*/       // Ist dieses ungueltig, so wird das aBoundVol genommen
/*N*/       // (sollten beim E3dCompoundObject sowieso gleich sein)
/*N*/       ((E3dCompoundObject*) this)->aLocalBoundVol = aBoundVol;
/*N*/   }
/*N*/
/*N*/   E3dObject::WriteData(rOut);
/*N*/   if (rOut.GetVersion() < 3560)
/*N*/   {
/*N*/       // In diesem Fall passiert nichts, da vor der Version 4.0
/*N*/       // also im Falle der Revision 3.1
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       SdrDownCompat aCompat(rOut, STREAM_WRITE);
/*N*/ #ifdef DBG_UTIL
/*N*/       aCompat.SetID("E3dCompoundObject");
/*N*/ #endif
/*N*/       rOut << BOOL(GetDoubleSided());
/*N*/ #endif
/*N*/
/*N*/       // neue Parameter zur Geometrieerzeugung
/*N*/       rOut << BOOL(bCreateNormals);
/*N*/       rOut << BOOL(bCreateTexture);
/*N*/
/*N*/       sal_uInt16 nVal = GetNormalsKind();
/*N*/       rOut << BOOL(nVal > 0);
/*N*/       rOut << BOOL(nVal > 1);
/*N*/
/*N*/       nVal = GetTextureProjectionX();
/*N*/       rOut << BOOL(nVal > 0);
/*N*/       rOut << BOOL(nVal > 1);
/*N*/
/*N*/       nVal = GetTextureProjectionY();
/*N*/       rOut << BOOL(nVal > 0);
/*N*/       rOut << BOOL(nVal > 1);
/*N*/
/*N*/       rOut << BOOL(GetShadow3D());
/*N*/
/*N*/       // neu al 384:
/*N*/       rOut << GetMaterialAmbientColor();
/*N*/       rOut << GetMaterialColor();
/*N*/       rOut << GetMaterialSpecular();
/*N*/       rOut << GetMaterialEmission();
/*N*/       rOut << GetMaterialSpecularIntensity();
/*N*/
/*N*/       aBackMaterial.WriteData(rOut);
/*N*/
/*N*/       rOut << (UINT16)GetTextureKind();
/*N*/
/*N*/       rOut << (UINT16)GetTextureMode();
/*N*/
/*N*/       rOut << BOOL(GetNormalsInvert());
/*N*/
/*N*/       // neu ab 534: (hat noch gefehlt)
/*N*/       rOut << BOOL(GetTextureFilter());
/*N*/   }
/*N*/ #endif
/*N*/ }

/*************************************************************************
|*
|* Einlesen der Datenmember eines E3dCompounds
|*
\************************************************************************/

/*N*/ void E3dCompoundObject::ReadData(const SdrObjIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   if ( rIn.GetError() != SVSTREAM_OK )
/*N*/       return;
/*N*/
/*N*/   E3dObject::ReadData(rHead, rIn);
/*N*/
/*N*/     // Vor der Filerevision 13 wurde das Objekt nie geschrieben.
/*N*/     // auch kein Kompatibilitaetsrecord.
/*N*/   if ((rHead.GetVersion() < 13) || (rIn.GetVersion() < 3560))
/*N*/   {
/*N*/       return;
/*N*/   }
/*N*/
/*N*/   SdrDownCompat aCompat(rIn, STREAM_READ);
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("E3dCompoundObject");
/*N*/ #endif
/*N*/
/*N*/   bBytesLeft = FALSE;
/*N*/   if (aCompat.GetBytesLeft () >= sizeof (BOOL))
/*N*/   {
/*N*/       BOOL bTmp, bTmp2;
/*N*/       sal_uInt16 nTmp;
/*N*/
/*N*/       rIn >> bTmp;
/*N*/       mpObjectItemSet->Put(Svx3DDoubleSidedItem(bTmp));
/*N*/
/*N*/       // neue Parameter zur Geometrieerzeugung
/*N*/       if (aCompat.GetBytesLeft () >= sizeof (BOOL))
/*N*/       {
/*N*/           rIn >> bTmp;
/*N*/           bCreateNormals = bTmp;
/*N*/
/*N*/           rIn >> bTmp;
/*N*/           bCreateTexture = bTmp;
/*N*/
/*N*/           rIn >> bTmp;
/*N*/           rIn >> bTmp2;
/*N*/           if(bTmp == FALSE && bTmp2 == FALSE)
/*N*/               nTmp = 0;
/*N*/           else if(bTmp == TRUE && bTmp2 == FALSE)
/*N*/               nTmp = 1;
/*N*/           else
/*N*/               nTmp = 2;
/*N*/           mpObjectItemSet->Put(Svx3DNormalsKindItem(nTmp));
/*N*/
/*N*/           rIn >> bTmp;
/*N*/           rIn >> bTmp2;
/*N*/           if(bTmp == FALSE && bTmp2 == FALSE)
/*N*/               nTmp = 0;
/*N*/           else if(bTmp == TRUE && bTmp2 == FALSE)
/*N*/               nTmp = 1;
/*N*/           else
/*N*/               nTmp = 2;
/*N*/           mpObjectItemSet->Put(Svx3DTextureProjectionXItem(nTmp));
/*N*/
/*N*/           rIn >> bTmp;
/*N*/           rIn >> bTmp2;
/*N*/           if(bTmp == FALSE && bTmp2 == FALSE)
/*N*/               nTmp = 0;
/*N*/           else if(bTmp == TRUE && bTmp2 == FALSE)
/*N*/               nTmp = 1;
/*N*/           else
/*N*/               nTmp = 2;
/*N*/           mpObjectItemSet->Put(Svx3DTextureProjectionYItem(nTmp));
/*N*/
/*N*/           rIn >> bTmp;
/*N*/           mpObjectItemSet->Put(Svx3DShadow3DItem(bTmp));
/*N*/
/*N*/           // Setze ein Flag fuer den Aufrufer, dass neues Format
/*N*/           // zu lesen ist
/*N*/           bBytesLeft = TRUE;
/*N*/       }
/*N*/
/*N*/       // neu al 384:
/*N*/       if (aCompat.GetBytesLeft () >= sizeof (B3dMaterial))
/*N*/       {
/*N*/           UINT16 nTmp;
/*N*/
/*N*/           Color aCol;
/*N*/
/*N*/           rIn >> aCol;
/*N*/           SetMaterialAmbientColor(aCol);
/*N*/
/*N*/           rIn >> aCol;
/*N*/           // do NOT use, this is the old 3D-Color(!)
/*N*/           // SetItem(XFillColorItem(String(), aCol));
/*N*/
/*N*/           rIn >> aCol;
/*N*/           mpObjectItemSet->Put(Svx3DMaterialSpecularItem(aCol));
/*N*/
/*N*/           rIn >> aCol;
/*N*/           mpObjectItemSet->Put(Svx3DMaterialEmissionItem(aCol));
/*N*/
/*N*/           rIn >> nTmp;
/*N*/           mpObjectItemSet->Put(Svx3DMaterialSpecularIntensityItem(nTmp));
/*N*/
/*N*/           aBackMaterial.ReadData(rIn);
/*N*/
/*N*/           rIn >> nTmp;
/*N*/           mpObjectItemSet->Put(Svx3DTextureKindItem(nTmp));
/*N*/
/*N*/           rIn >> nTmp;
/*N*/           mpObjectItemSet->Put(Svx3DTextureModeItem(nTmp));
/*N*/
/*N*/           rIn >> bTmp;
/*N*/           mpObjectItemSet->Put(Svx3DNormalsInvertItem(bTmp));
/*N*/       }
/*N*/
/*N*/       // neu ab 534: (hat noch gefehlt)
/*N*/       if (aCompat.GetBytesLeft () >= sizeof (BOOL))
/*N*/       {
/*N*/           rIn >> bTmp;
/*N*/           mpObjectItemSet->Put(Svx3DTextureFilterItem(bTmp));
/*N*/       }
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Bitmaps fuer 3D-Darstellung von Gradients und Hatches holen
|*
\************************************************************************/

//STRIP001 AlphaMask E3dCompoundObject::GetAlphaMask(const SfxItemSet& rSet, const Size& rSizePixel)
//STRIP001 {
//STRIP001  const XFillFloatTransparenceItem& rFloatTrans = ((const XFillFloatTransparenceItem&)(rSet.Get(XATTR_FILLFLOATTRANSPARENCE)));
//STRIP001  VirtualDevice *pVD = new VirtualDevice();
//STRIP001  pVD->SetOutputSizePixel( rSizePixel );
//STRIP001  XOutputDevice *pXOut = new XOutputDevice( pVD );
//STRIP001  SfxItemSet aFillSet(*rSet.GetPool());
//STRIP001
//STRIP001  XGradient aNewGradient(rFloatTrans.GetValue());
//STRIP001
//STRIP001  Color aStartCol(aNewGradient.GetStartColor());
//STRIP001  if(aNewGradient.GetStartIntens() != 100)
//STRIP001  {
//STRIP001      double fFact = (double)aNewGradient.GetStartIntens() / 100.0;
//STRIP001      aStartCol = (B3dColor)aStartCol * fFact;
//STRIP001  }
//STRIP001  aNewGradient.SetStartColor(aStartCol);
//STRIP001  aNewGradient.SetStartIntens(100);
//STRIP001
//STRIP001  Color aEndCol(aNewGradient.GetEndColor());
//STRIP001  if(aNewGradient.GetEndIntens() != 100)
//STRIP001  {
//STRIP001      double fFact = (double)aNewGradient.GetEndIntens() / 100.0;
//STRIP001      aEndCol = (B3dColor)aEndCol * fFact;
//STRIP001  }
//STRIP001  aNewGradient.SetEndColor(aEndCol);
//STRIP001  aNewGradient.SetEndIntens(100);
//STRIP001
//STRIP001  aFillSet.Put( XFillStyleItem( XFILL_GRADIENT ) );
//STRIP001  aFillSet.Put( XFillGradientItem( String(), aNewGradient ) );
//STRIP001  aFillSet.Put( XGradientStepCountItem( aNewGradient.GetSteps() ) );
//STRIP001  pXOut->SetFillAttr( aFillSet );
//STRIP001
//STRIP001  aFillSet.Put( XLineStyleItem( XLINE_NONE ) );
//STRIP001  pXOut->SetLineAttr( aFillSet );
//STRIP001
//STRIP001  pXOut->DrawRect( Rectangle( Point(), rSizePixel ) );
//STRIP001  Bitmap aGradientBitmap = pVD->GetBitmap( Point(), rSizePixel );
//STRIP001
//STRIP001  if( pVD )
//STRIP001      delete pVD;
//STRIP001  if( pXOut )
//STRIP001      delete pXOut;
//STRIP001
//STRIP001  return AlphaMask(aGradientBitmap);
//STRIP001 }

//STRIP001 Bitmap E3dCompoundObject::GetGradientBitmap(const SfxItemSet& rSet)
//STRIP001 {
//STRIP001  VirtualDevice *pVD = new VirtualDevice();
//STRIP001  Size aVDSize(256, 256);
//STRIP001  pVD->SetOutputSizePixel( aVDSize );
//STRIP001  XOutputDevice *pXOut = new XOutputDevice( pVD );
//STRIP001  SfxItemSet aFillSet(*rSet.GetPool());
//STRIP001
//STRIP001  aFillSet.Put( XFillStyleItem( XFILL_GRADIENT ) );
//STRIP001  aFillSet.Put( rSet.Get(XATTR_FILLGRADIENT) );
//STRIP001  aFillSet.Put( rSet.Get(XATTR_GRADIENTSTEPCOUNT) );
//STRIP001  pXOut->SetFillAttr( aFillSet );
//STRIP001
//STRIP001  aFillSet.Put( XLineStyleItem( XLINE_NONE ) );
//STRIP001  pXOut->SetLineAttr( aFillSet );
//STRIP001
//STRIP001  pXOut->DrawRect( Rectangle( Point(), aVDSize ) );
//STRIP001  Bitmap aGradientBitmap = pVD->GetBitmap( Point(), aVDSize );
//STRIP001
//STRIP001  if( pVD )
//STRIP001      delete pVD;
//STRIP001  if( pXOut )
//STRIP001      delete pXOut;
//STRIP001
//STRIP001  return aGradientBitmap;
//STRIP001 }

//STRIP001 Bitmap E3dCompoundObject::GetHatchBitmap(const SfxItemSet& rSet)
//STRIP001 {
//STRIP001  VirtualDevice *pVD = new VirtualDevice();
//STRIP001  const XFillHatchItem* pFillHatchItem = (XFillHatchItem*)&rSet.Get(XATTR_FILLHATCH);
//STRIP001  const XHatch& rHatch = pFillHatchItem->GetValue();
//STRIP001  long nDistance = rHatch.GetDistance(); // in 100stel mm
//STRIP001  double fAngle = double(rHatch.GetAngle()) * (F_PI180 / 10.0);
//STRIP001
//STRIP001  double fMinX(0.0);
//STRIP001  double fMaxX(0.0);
//STRIP001  double fMinY(0.0);
//STRIP001  double fMaxY(0.0);
//STRIP001
//STRIP001  // nDistance in X-Richtung
//STRIP001  double fX = cos(fAngle) * double(nDistance);
//STRIP001  double fY = sin(fAngle) * double(nDistance);
//STRIP001
//STRIP001  if(fX < fMinX)
//STRIP001      fMinX = fX;
//STRIP001  if(fX > fMaxX)
//STRIP001      fMaxX = fX;
//STRIP001
//STRIP001  if(fY < fMinY)
//STRIP001      fMinY = fY;
//STRIP001  if(fY > fMaxY)
//STRIP001      fMaxY = fY;
//STRIP001
//STRIP001  // nDistance in Y-Richtung
//STRIP001  fX = cos(fAngle + F_PI2) * double(nDistance);
//STRIP001  fY = sin(fAngle + F_PI2) * double(nDistance);
//STRIP001
//STRIP001  if(fX < fMinX)
//STRIP001      fMinX = fX;
//STRIP001  if(fX > fMaxX)
//STRIP001      fMaxX = fX;
//STRIP001
//STRIP001  if(fY < fMinY)
//STRIP001      fMinY = fY;
//STRIP001  if(fY > fMaxY)
//STRIP001      fMaxY = fY;
//STRIP001
//STRIP001  // nDistance in -X-Richtung
//STRIP001  fX = cos(fAngle + F_PI) * double(nDistance);
//STRIP001  fY = sin(fAngle + F_PI) * double(nDistance);
//STRIP001
//STRIP001  if(fX < fMinX)
//STRIP001      fMinX = fX;
//STRIP001  if(fX > fMaxX)
//STRIP001      fMaxX = fX;
//STRIP001
//STRIP001  if(fY < fMinY)
//STRIP001      fMinY = fY;
//STRIP001  if(fY > fMaxY)
//STRIP001      fMaxY = fY;
//STRIP001
//STRIP001  // nDistance in -Y-Richtung
//STRIP001  fX = cos(fAngle + (F_PI + F_PI2)) * double(nDistance);
//STRIP001  fY = sin(fAngle + (F_PI + F_PI2)) * double(nDistance);
//STRIP001
//STRIP001  if(fX < fMinX)
//STRIP001      fMinX = fX;
//STRIP001  if(fX > fMaxX)
//STRIP001      fMaxX = fX;
//STRIP001
//STRIP001  if(fY < fMinY)
//STRIP001      fMinY = fY;
//STRIP001  if(fY > fMaxY)
//STRIP001      fMaxY = fY;
//STRIP001
//STRIP001  long nDistanceX = long(fMaxX - fMinX);
//STRIP001  long nDistanceY = long(fMaxY - fMinY);
//STRIP001
//STRIP001  // Bei Schraffuren in eine der 4 Himmelsrichtungen Ausdehnung halbieren
//STRIP001  if(rHatch.GetAngle() % 900 == 0)
//STRIP001  {
//STRIP001      nDistanceX /= 2;
//STRIP001      nDistanceY /= 2;
//STRIP001  }
//STRIP001
//STRIP001  Size aVDSize(64, 64);
//STRIP001  pVD->SetOutputSizePixel( aVDSize );
//STRIP001  MapMode aMapMode(MAP_100TH_MM);
//STRIP001  pVD->SetMapMode(aMapMode);
//STRIP001
//STRIP001  XOutputDevice *pXOut = new XOutputDevice( pVD );
//STRIP001  SfxItemSet aFillSet(*rSet.GetPool());
//STRIP001
//STRIP001  aFillSet.Put( XFillStyleItem( XFILL_SOLID ) );
//STRIP001  aFillSet.Put( XFillColorItem( String(), RGB_Color( COL_WHITE ) ) );
//STRIP001  aFillSet.Put( XLineStyleItem( XLINE_NONE ) );
//STRIP001  pXOut->SetLineAttr( aFillSet );
//STRIP001  pXOut->SetFillAttr( aFillSet );
//STRIP001  pXOut->DrawRect( Rectangle( Point(), pVD->PixelToLogic(aVDSize) ) );
//STRIP001
//STRIP001  aFillSet.Put( XFillStyleItem( XFILL_HATCH ) );
//STRIP001  aFillSet.Put( rSet.Get(XATTR_FILLHATCH) );
//STRIP001  pXOut->SetFillAttr( aFillSet );
//STRIP001
//STRIP001  Size aLogicalSize = pVD->PixelToLogic(aVDSize);
//STRIP001
//STRIP001  // #109483#
//STRIP001  // If nDistance was 0 (the init value from the API), nDistanceX/Y
//STRIP001  // may be zero, too, which is not a valid value for a fraction. The
//STRIP001  // best value then is 1 since this simply takes the logical size as
//STRIP001  // scaling. A distance of 0 in a hatch makes no sense anyways.
//STRIP001  if(!nDistanceX)
//STRIP001  {
//STRIP001      nDistanceX = 1;
//STRIP001  }
//STRIP001
//STRIP001  if(!nDistanceY)
//STRIP001  {
//STRIP001      nDistanceY = 1;
//STRIP001  }
//STRIP001
//STRIP001  Fraction aFractionX(aLogicalSize.Width(), nDistanceX);
//STRIP001  Fraction aFractionY(aLogicalSize.Height(), nDistanceY);
//STRIP001  aMapMode.SetScaleX(aFractionX);
//STRIP001  aMapMode.SetScaleY(aFractionY);
//STRIP001  pVD->SetMapMode(aMapMode);
//STRIP001  pXOut->DrawRect( Rectangle( Point(), pVD->PixelToLogic(aVDSize) ) );
//STRIP001
//STRIP001  Bitmap aHatchBitmap = pVD->GetBitmap( Point(), pVD->PixelToLogic(aVDSize) );
//STRIP001
//STRIP001  if( pVD )
//STRIP001      delete pVD;
//STRIP001  if( pXOut )
//STRIP001      delete pXOut;
//STRIP001
//STRIP001  return aHatchBitmap;
//STRIP001 }

/*************************************************************************
|*
|* Give out simple line geometry
|*
\************************************************************************/

//STRIP001 void E3dCompoundObject::GetLineGeometry(PolyPolygon3D& rLinePolyPolygon) const
//STRIP001 {
//STRIP001  // use basic implementation here. Maybe optimized later.
//STRIP001  rLinePolyPolygon.Clear();
//STRIP001  B3dEntityBucket& rEntityBucket = ((E3dCompoundObject*)this)->GetDisplayGeometry().GetEntityBucket();
//STRIP001  GeometryIndexValueBucket& rIndexBucket = ((E3dCompoundObject*)this)->GetDisplayGeometry().GetIndexBucket();
//STRIP001  sal_uInt32 nPolyCounter(0);
//STRIP001  sal_uInt32 nEntityCounter(0);
//STRIP001
//STRIP001  while(nPolyCounter < rIndexBucket.Count())
//STRIP001  {
//STRIP001      // next primitive
//STRIP001      sal_uInt32 nUpperBound(rIndexBucket[nPolyCounter++].GetIndex());
//STRIP001      Vector3D aLastPoint;
//STRIP001
//STRIP001      BOOL bLastLineVisible = rEntityBucket[nUpperBound - 1].IsEdgeVisible();
//STRIP001      if(bLastLineVisible)
//STRIP001          aLastPoint = rEntityBucket[nUpperBound - 1].Point().GetVector3D();
//STRIP001
//STRIP001      while(nEntityCounter < nUpperBound)
//STRIP001      {
//STRIP001          Vector3D aNewPoint = rEntityBucket[nEntityCounter].Point().GetVector3D();
//STRIP001
//STRIP001          if(bLastLineVisible)
//STRIP001          {
//STRIP001              if(aLastPoint != aNewPoint)
//STRIP001              {
//STRIP001                  // fill polygon
//STRIP001                  Polygon3D aNewPoly(2);
//STRIP001                  aNewPoly[0] = aLastPoint;
//STRIP001                  aNewPoly[1] = aNewPoint;
//STRIP001
//STRIP001                  // create line geometry for polygon in eye coor to
//STRIP001                  // have it always orthogonal to camera plane
//STRIP001                  rLinePolyPolygon.Insert(aNewPoly);
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          bLastLineVisible = rEntityBucket[nEntityCounter++].IsEdgeVisible();
//STRIP001          aLastPoint = aNewPoint;
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Geometrieerzeugung
|*
\************************************************************************/

/*N*/ void E3dCompoundObject::DestroyGeometry()
/*N*/ {
/*N*/   // Alle Objekte in der Sub-Liste zerstoeren. Dies sind die
/*N*/   // zur Visualisierung des Objektes verwendeten Hilfsobjekte
/*N*/   pSub->Clear();
/*N*/   delete pSub;
/*N*/   pSub = new E3dObjList(NULL, NULL);
/*N*/   pSub->SetOwnerObj(this);
/*N*/   pSub->SetListKind(SDROBJLIST_GROUPOBJ);
/*N*/
/*N*/   // Neue Geometrie zerstoeren
/*N*/   aDisplayGeometry.Erase();
/*N*/
/*N*/   // BoundVols resetten
/*N*/   aLocalBoundVol  = Volume3D();
/*N*/   bBoundVolValid = FALSE;
/*N*/   StructureChanged(this);
/*N*/
/*N*/   // Geometrie ist ungueltig
/*N*/   bGeometryValid = FALSE;
/*N*/ }

/*N*/ void E3dCompoundObject::CreateGeometry()
/*N*/ {
/*N*/   // Geometrie ist gueltig, um rekursion zu verhindern
/*N*/   bGeometryValid = TRUE;
/*N*/
/*N*/   // Eventuell entstandene Geometrie noch korrigieren
/*N*/   // und Default -Normalen oder -Texturkoordinaten erzeugen
/*N*/   if(bCreateNormals)
/*N*/   {
/*N*/       if(GetNormalsKind() > 1)
/*?*/           GetDisplayGeometry().CreateDefaultNormalsSphere();
/*N*/       if(GetNormalsInvert())
/*?*/           GetDisplayGeometry().InvertNormals();
/*N*/   }
/*N*/
/*N*/   if(bCreateTexture)
/*N*/   {
/*N*/       GetDisplayGeometry().CreateDefaultTexture(
/*N*/           ((GetTextureProjectionX() > 0) ? B3D_CREATE_DEFAULT_X : FALSE)
/*N*/           |((GetTextureProjectionY() > 0) ? B3D_CREATE_DEFAULT_Y : FALSE),
/*N*/           GetTextureProjectionX() > 1);
/*N*/   }
/*N*/
/*N*/   // Am Ende der Geometrieerzeugung das model an den erzeugten
/*N*/   // PolyObj's setzen, d.h. beim ueberladen dieser Funktion
/*N*/   // den parent am Ende rufen.
/*N*/   if(bCreateE3dPolyObj)
/*N*/       SetModel(pModel);
/*N*/
/*N*/   // Das Ende der Geometrieerzeugung anzeigen
/*N*/   aDisplayGeometry.EndDescription();
/*N*/ }

/*N*/ void E3dCompoundObject::ReCreateGeometry(BOOL bCreateOldGeometry)
/*N*/ {
/*N*/   // Geometrie zerstoeren
/*N*/   DestroyGeometry();
/*N*/
/*N*/   // Flag fuer Geometrieerzeugung setzen
/*N*/   bCreateE3dPolyObj = bCreateOldGeometry;
/*N*/
/*N*/   // ... und neu erzeugen
/*N*/   CreateGeometry();
/*N*/ }

/*************************************************************************
|*
|* Geometrieerzeugung
|*
\************************************************************************/

/*N*/ void E3dCompoundObject::AddGeometry(const PolyPolygon3D& rPolyPolygon3D,
/*N*/   BOOL bHintIsComplex, BOOL bOutline)
/*N*/ {
/*N*/   if(rPolyPolygon3D.Count())
/*N*/   {
/*N*/       // eventuell alte Geometrie erzeugen (z.B. zum speichern)
/*N*/       if(bCreateE3dPolyObj)
/*N*/       {
/*N*/           E3dPolyObj* pObj = new E3dPolyObj(
/*N*/               rPolyPolygon3D, GetDoubleSided(), TRUE);
/*N*/           pObj->SetPartOfParent();
/*N*/           Insert3DObj(pObj);
/*N*/       }
/*N*/
/*N*/       // neue Geometrie erzeugen
/*N*/       for(USHORT a = 0; a < rPolyPolygon3D.Count(); a++ )
/*N*/       {
/*N*/           const Polygon3D& rPoly3D = rPolyPolygon3D[a];
/*N*/           aDisplayGeometry.StartObject(bHintIsComplex, bOutline);
/*N*/           for(USHORT b = 0; b < rPoly3D.GetPointCount(); b++ )
/*N*/               aDisplayGeometry.AddEdge(rPoly3D[b]);
/*N*/       }
/*N*/       aDisplayGeometry.EndObject();
/*N*/
/*N*/       // LocalBoundVolume pflegen
/*N*/       aLocalBoundVol.Union(rPolyPolygon3D.GetPolySize());
/*N*/
/*N*/       // Eigenes BoundVol nicht mehr gueltig
/*N*/       SetBoundVolInvalid();
/*N*/       SetRectsDirty();
/*N*/   }
/*N*/ }

/*?*/ void E3dCompoundObject::AddGeometry(
/*?*/   const PolyPolygon3D& rPolyPolygon3D,
/*?*/   const PolyPolygon3D& rPolyNormal3D,
/*?*/   BOOL bHintIsComplex, BOOL bOutline)
/*?*/ {
/*?*/   if(rPolyPolygon3D.Count())
/*?*/   {
/*?*/       // eventuell alte Geometrie erzeugen (z.B. zum speichern)
/*?*/       if(bCreateE3dPolyObj)
/*?*/       {
/*?*/           E3dPolyObj* pObj = new E3dPolyObj(
/*?*/               rPolyPolygon3D, rPolyNormal3D, GetDoubleSided(), TRUE);
/*?*/           pObj->SetPartOfParent();
/*?*/           Insert3DObj(pObj);
/*?*/       }
/*?*/
/*?*/       // neue Geometrie erzeugen
/*?*/       for(USHORT a = 0; a < rPolyPolygon3D.Count(); a++ )
/*?*/       {
/*?*/           const Polygon3D& rPoly3D = rPolyPolygon3D[a];
/*?*/           const Polygon3D& rNormal3D = rPolyNormal3D[a];
/*?*/           aDisplayGeometry.StartObject(bHintIsComplex, bOutline);
/*?*/           for(USHORT b = 0; b < rPoly3D.GetPointCount(); b++ )
/*?*/               aDisplayGeometry.AddEdge(rPoly3D[b], rNormal3D[b]);
/*?*/       }
/*?*/       aDisplayGeometry.EndObject();
/*?*/
/*?*/       // LocalBoundVolume pflegen
/*?*/       aLocalBoundVol.Union(rPolyPolygon3D.GetPolySize());
/*?*/
/*?*/       // Eigenes BoundVol nicht mehr gueltig
/*?*/       SetBoundVolInvalid();
/*?*/       SetRectsDirty();
/*?*/   }
/*?*/ }

/*N*/ void E3dCompoundObject::AddGeometry(
/*N*/   const PolyPolygon3D& rPolyPolygon3D,
/*N*/   const PolyPolygon3D& rPolyNormal3D,
/*N*/   const PolyPolygon3D& rPolyTexture3D,
/*N*/   BOOL bHintIsComplex, BOOL bOutline)
/*N*/ {
/*N*/   if(rPolyPolygon3D.Count())
/*N*/   {
/*N*/       // eventuell alte Geometrie erzeugen (z.B. zum speichern)
/*N*/       if(bCreateE3dPolyObj)
/*N*/       {
/*N*/           E3dPolyObj* pObj = new E3dPolyObj(
/*N*/               rPolyPolygon3D, rPolyNormal3D,
/*N*/               rPolyTexture3D, GetDoubleSided(), TRUE);
/*N*/           pObj->SetPartOfParent();
/*N*/           Insert3DObj(pObj);
/*N*/       }
/*N*/
/*N*/       // neue Geometrie erzeugen
/*N*/       for(USHORT a = 0; a < rPolyPolygon3D.Count(); a++ )
/*N*/       {
/*N*/           const Polygon3D& rPoly3D = rPolyPolygon3D[a];
/*N*/           const Polygon3D& rNormal3D = rPolyNormal3D[a];
/*N*/           const Polygon3D& rTexture3D = rPolyTexture3D[a];
/*N*/           aDisplayGeometry.StartObject(bHintIsComplex, bOutline);
/*N*/           for(USHORT b = 0; b < rPoly3D.GetPointCount(); b++ )
/*N*/               aDisplayGeometry.AddEdge(rPoly3D[b], rNormal3D[b], rTexture3D[b]);
/*N*/       }
/*N*/       aDisplayGeometry.EndObject();
/*N*/
/*N*/       // LocalBoundVolume pflegen
/*N*/       aLocalBoundVol.Union(rPolyPolygon3D.GetPolySize());
/*N*/
/*N*/       // Eigenes BoundVol nicht mehr gueltig
/*N*/       SetBoundVolInvalid();
/*N*/       SetRectsDirty();
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Hilfsfunktionen zur Geometrieerzeugung
|*
\************************************************************************/

/*N*/ void E3dCompoundObject::RotatePoly(
/*N*/   PolyPolygon3D& rPolyPolyRotate,
/*N*/   Matrix4D& rRotMat)
/*N*/ {
/*N*/   USHORT nPolyCnt = rPolyPolyRotate.Count();
/*N*/
/*N*/   for(UINT16 a=0;a<nPolyCnt;a++)
/*N*/   {
/*N*/       Polygon3D& rPolyRotate = rPolyPolyRotate[a];
/*N*/       USHORT nPntCnt = rPolyRotate.GetPointCount();
/*N*/
/*N*/       for(UINT16 b=0;b<nPntCnt;b++)
/*N*/           rPolyRotate[b] *= rRotMat;
/*N*/   }
/*N*/ }

/*N*/ void E3dCompoundObject::GrowPoly(
/*N*/   PolyPolygon3D& rPolyPolyGrow,
/*N*/   PolyPolygon3D& rPolyPolyNormals,
/*N*/   double fFactor)
/*N*/ {
/*N*/   USHORT nPolyCnt = rPolyPolyGrow.Count();
/*N*/
/*N*/   for(UINT16 a=0;a<nPolyCnt;a++)
/*N*/   {
/*N*/       Polygon3D& rPolyGrow = rPolyPolyGrow[a];
/*N*/       const Polygon3D& rPolyNormals = rPolyPolyNormals[a];
/*N*/       USHORT nPntCnt = rPolyGrow.GetPointCount();
/*N*/
/*N*/       for(UINT16 b=0;b<nPntCnt;b++)
/*N*/           rPolyGrow[b] += rPolyNormals[b] * fFactor;
/*N*/   }
/*N*/ }

//STRIP001 void E3dCompoundObject::AddNormals(
//STRIP001  PolyPolygon3D& rPolyPolyDest,
//STRIP001  const PolyPolygon3D& rPolyPolySource)
//STRIP001 {
//STRIP001  USHORT nPolyCnt = rPolyPolyDest.Count();
//STRIP001
//STRIP001  for(UINT16 a=0;a<nPolyCnt;a++)
//STRIP001  {
//STRIP001      Polygon3D& rPolyDest = rPolyPolyDest[a];
//STRIP001      const Polygon3D& rPolySource = rPolyPolySource[a];
//STRIP001      USHORT nPntCnt = rPolyDest.GetPointCount();
//STRIP001
//STRIP001      for(UINT16 b=0;b<nPntCnt;b++)
//STRIP001      {
//STRIP001          rPolyDest[b] += rPolySource[b];
//STRIP001          rPolyDest[b].Normalize();
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*N*/ void E3dCompoundObject::ScalePoly(
/*N*/   PolyPolygon3D& rPolyPolyScale,
/*N*/   double fFactor)
/*N*/ {
/*N*/   USHORT nPolyCnt = rPolyPolyScale.Count();
/*N*/   Vector3D aMiddle = rPolyPolyScale.GetMiddle();
/*N*/
/*N*/   for(UINT16 a=0;a<nPolyCnt;a++)
/*N*/   {
/*N*/       Polygon3D& rPolyScale = rPolyPolyScale[a];
/*N*/       USHORT nPntCnt = rPolyScale.GetPointCount();
/*N*/
/*N*/       for(UINT16 b=0;b<nPntCnt;b++)
/*N*/           rPolyScale[b] = ((rPolyScale[b] - aMiddle) * fFactor) + aMiddle;
/*N*/   }
/*N*/ }

/*N*/ void E3dCompoundObject::CreateFront(
/*N*/   const PolyPolygon3D& rPolyPoly3D,
/*N*/   const PolyPolygon3D& rFrontNormals,
/*N*/   BOOL bCreateNormals,
/*N*/   BOOL bCreateTexture)
/*N*/ {
/*N*/   // Vorderseite
/*N*/   if(bCreateNormals)
/*N*/   {
/*N*/       if(bCreateTexture)
/*N*/       {
/*N*/           // Polygon fuer die Textur erzeugen
/*N*/           PolyPolygon3D aPolyTexture = rPolyPoly3D;
/*N*/           Volume3D aSize = aPolyTexture.GetPolySize();
/*N*/           Matrix4D aTrans;
/*N*/
/*N*/           aTrans.Identity();
/*N*/           aTrans.Translate(-aSize.MinVec());
/*N*/           aPolyTexture.Transform(aTrans);
/*N*/
/*N*/           double fFactorX(1.0), fFactorY(1.0), fFactorZ(1.0);
/*N*/
/*N*/           if(aSize.GetWidth() != 0.0)
/*N*/               fFactorX = 1.0 / aSize.GetWidth();
/*N*/
/*N*/           if(aSize.GetHeight() != 0.0)
/*N*/               fFactorY = 1.0 / aSize.GetHeight();
/*N*/
/*N*/           if(aSize.GetDepth() != 0.0)
/*N*/               fFactorZ = 1.0 / aSize.GetDepth();
/*N*/
/*N*/           aTrans.Identity();
/*N*/           aTrans.Scale(fFactorX, -fFactorY, fFactorZ);
/*N*/           aTrans.Translate(Vector3D(0.0, 1.0, 0.0));
/*N*/           aPolyTexture.Transform(aTrans);
/*N*/
/*N*/           AddGeometry(rPolyPoly3D, rFrontNormals, aPolyTexture, TRUE);
/*N*/       }
/*N*/       else
/*N*/           AddGeometry(rPolyPoly3D, rFrontNormals, TRUE);
/*N*/   }
/*N*/   else
/*N*/       AddGeometry(rPolyPoly3D, TRUE);
/*N*/ }

/*N*/ void E3dCompoundObject::AddFrontNormals(
/*N*/   const PolyPolygon3D& rPolyPoly3D,
/*N*/   PolyPolygon3D& rNormalsFront,
/*N*/   Vector3D &rOffset)
/*N*/ {
/*N*/   Vector3D aFrontNormal = -rOffset;
/*N*/   aFrontNormal.Normalize();
/*N*/   USHORT nPolyCnt = rPolyPoly3D.Count();
/*N*/
/*N*/   for(UINT16 a=0;a<nPolyCnt;a++)
/*N*/   {
/*N*/       const Polygon3D& rPoly3D = rPolyPoly3D[a];
/*N*/       Polygon3D& rNormalPoly = rNormalsFront[a];
/*N*/       USHORT nPntCnt = rPoly3D.GetPointCount();
/*N*/
/*N*/       for(UINT16 b=0;b<nPntCnt;b++)
/*N*/       {
/*N*/           rNormalPoly[b] += aFrontNormal;
/*N*/           rNormalPoly[b].Normalize();
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void E3dCompoundObject::CreateBack(
/*N*/   const PolyPolygon3D& rPolyPoly3D,
/*N*/   const PolyPolygon3D& rBackNormals,
/*N*/   BOOL bCreateNormals,
/*N*/   BOOL bCreateTexture)
/*N*/ {
/*N*/   // PolyPolygon umdrehen
/*N*/   PolyPolygon3D aLocalPoly = rPolyPoly3D;
/*N*/   aLocalPoly.FlipDirections();
/*N*/
/*N*/   // Rueckseite
/*N*/   if(bCreateNormals)
/*N*/   {
/*N*/       PolyPolygon3D aLocalNormals = rBackNormals;
/*N*/       aLocalNormals.FlipDirections();
/*N*/       if(bCreateTexture)
/*N*/       {
/*N*/           // Polygon fuer die Textur erzeugen
/*N*/           PolyPolygon3D aPolyTexture(aLocalPoly);
/*N*/           Volume3D aSize = aPolyTexture.GetPolySize();
/*N*/           Matrix4D aTrans;
/*N*/
/*N*/           aTrans.Identity();
/*N*/           aTrans.Translate(-aSize.MinVec());
/*N*/           aPolyTexture.Transform(aTrans);
/*N*/
/*N*/           double fFactorX(1.0), fFactorY(1.0), fFactorZ(1.0);
/*N*/
/*N*/           if(aSize.GetWidth() != 0.0)
/*N*/               fFactorX = 1.0 / aSize.GetWidth();
/*N*/
/*N*/           if(aSize.GetHeight() != 0.0)
/*N*/               fFactorY = 1.0 / aSize.GetHeight();
/*N*/
/*N*/           if(aSize.GetDepth() != 0.0)
/*N*/               fFactorZ = 1.0 / aSize.GetDepth();
/*N*/
/*N*/           aTrans.Identity();
/*N*/           aTrans.Scale(fFactorX, -fFactorY, fFactorZ);
/*N*/           aTrans.Translate(Vector3D(0.0, 1.0, 0.0));
/*N*/           aPolyTexture.Transform(aTrans);
/*N*/
/*N*/           AddGeometry(aLocalPoly, aLocalNormals, aPolyTexture, TRUE);
/*N*/       }
/*N*/       else
/*N*/           AddGeometry(aLocalPoly, aLocalNormals, TRUE);
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       AddGeometry(aLocalPoly, TRUE);
/*N*/   }
/*N*/ }

/*N*/ void E3dCompoundObject::AddBackNormals(
/*N*/   const PolyPolygon3D& rPolyPoly3D,
/*N*/   PolyPolygon3D& rNormalsBack,
/*N*/   Vector3D& rOffset)
/*N*/ {
/*N*/   Vector3D aBackNormal = rOffset;
/*N*/   aBackNormal.Normalize();
/*N*/   USHORT nPolyCnt = rPolyPoly3D.Count();
/*N*/
/*N*/   for(UINT16 a=0;a<nPolyCnt;a++)
/*N*/   {
/*N*/       const Polygon3D& rPoly3D = rPolyPoly3D[a];
/*N*/       Polygon3D& rNormalPoly = rNormalsBack[a];
/*N*/       USHORT nPntCnt = rPoly3D.GetPointCount();
/*N*/
/*N*/       for(UINT16 b=0;b<nPntCnt;b++)
/*N*/       {
/*N*/           rNormalPoly[b] += aBackNormal;
/*N*/           rNormalPoly[b].Normalize();
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void E3dCompoundObject::CreateInBetween(
/*N*/   const PolyPolygon3D& rPolyPolyFront,
/*N*/   const PolyPolygon3D& rPolyPolyBack,
/*N*/   const PolyPolygon3D& rFrontNormals,
/*N*/   const PolyPolygon3D& rBackNormals,
/*N*/   BOOL bCreateNormals,
/*N*/   double fSurroundFactor,
/*N*/   double fTextureStart,
/*N*/   double fTextureDepth,
/*N*/   BOOL bRotateTexture90)
/*N*/ {
/*N*/   USHORT nPolyCnt = rPolyPolyFront.Count();
/*N*/   BOOL bCreateTexture = (fTextureDepth == 0.0) ? FALSE : TRUE;
/*N*/   double fPolyLength, fPolyPos;
/*N*/   USHORT nLastIndex;
/*N*/
/*N*/   // Verbindungsstuecke
/*N*/   if(bCreateNormals)
/*N*/   {
/*N*/       for(UINT16 a=0;a<nPolyCnt;a++)
/*N*/       {
/*N*/           const Polygon3D& rPoly3DFront = rPolyPolyFront[a];
/*N*/           const Polygon3D& rPoly3DBack = rPolyPolyBack[a];
/*N*/
/*N*/           const Polygon3D& rPolyNormalsFront = rFrontNormals[a];
/*N*/           const Polygon3D& rPolyNormalsBack = rBackNormals[a];
/*N*/
/*N*/           Polygon3D   aRect3D(4);
/*N*/           Polygon3D   aNormal3D(4);
/*N*/           Polygon3D   aTexture3D(4);
/*N*/           USHORT nPntCnt = rPoly3DFront.GetPointCount();
/*N*/           USHORT nPrefillIndex = rPoly3DFront.IsClosed() ? nPntCnt - 1 : 0;
/*N*/
/*N*/           aRect3D[3] = rPoly3DFront[nPrefillIndex];
/*N*/           aRect3D[2] = rPoly3DBack[nPrefillIndex];
/*N*/           aNormal3D[3] = rPolyNormalsFront[nPrefillIndex];
/*N*/           aNormal3D[2] = rPolyNormalsBack[nPrefillIndex];
/*N*/
/*N*/           if(bCreateTexture)
/*N*/           {
/*N*/               fPolyLength = rPoly3DFront.GetLength();
/*N*/               fPolyPos = 0.0;
/*N*/               nLastIndex = rPoly3DFront.IsClosed() ? nPntCnt - 1 : 0;
/*N*/
/*N*/               if(bRotateTexture90)
/*N*/               {
/*N*/                   // X,Y vertauschen
/*N*/                   aTexture3D[3].X() = fTextureStart;
/*N*/                   aTexture3D[3].Y() = (1.0 - fPolyPos) * fSurroundFactor;
/*N*/
/*N*/                   aTexture3D[2].X() = fTextureStart + fTextureDepth;
/*N*/                   aTexture3D[2].Y() = (1.0 - fPolyPos) * fSurroundFactor;
/*N*/               }
/*N*/               else
/*N*/               {
/*N*/                   aTexture3D[3].X() = fPolyPos * fSurroundFactor;
/*N*/                   aTexture3D[3].Y() = fTextureStart;
/*N*/
/*N*/                   aTexture3D[2].X() = fPolyPos * fSurroundFactor;
/*N*/                   aTexture3D[2].Y() = fTextureStart + fTextureDepth;
/*N*/               }
/*N*/           }
/*N*/
/*N*/           for (USHORT i = rPoly3DFront.IsClosed() ? 0 : 1; i < nPntCnt; i++)
/*N*/           {
/*N*/               aRect3D[0] = aRect3D[3];
/*N*/               aRect3D[1] = aRect3D[2];
/*N*/
/*N*/               aRect3D[3] = rPoly3DFront[i];
/*N*/               aRect3D[2] = rPoly3DBack[i];
/*N*/
/*N*/               aNormal3D[0] = aNormal3D[3];
/*N*/               aNormal3D[1] = aNormal3D[2];
/*N*/
/*N*/               aNormal3D[3] = rPolyNormalsFront[i];
/*N*/               aNormal3D[2] = rPolyNormalsBack[i];
/*N*/
/*N*/               if(bCreateTexture)
/*N*/               {
/*N*/                   // Texturkoordinaten ermitteln
/*N*/                   Vector3D aPart = rPoly3DFront[i] - rPoly3DFront[nLastIndex];
/*N*/                   fPolyPos += aPart.GetLength() / fPolyLength;
/*N*/                   nLastIndex = i;
/*N*/
/*N*/                   // Der Abschnitt am Polygon entspricht dem Teil
/*N*/                   // von fPolyPos bis fPolyPos+fPartLength
/*N*/
/*N*/                   aTexture3D[0] = aTexture3D[3];
/*N*/                   aTexture3D[1] = aTexture3D[2];
/*N*/
/*N*/                   if(bRotateTexture90)
/*N*/                   {
/*N*/                       // X,Y vertauschen
/*N*/                       aTexture3D[3].X() = fTextureStart;
/*N*/                       aTexture3D[3].Y() = (1.0 - fPolyPos) * fSurroundFactor;
/*N*/
/*N*/                       aTexture3D[2].X() = fTextureStart + fTextureDepth;
/*N*/                       aTexture3D[2].Y() = (1.0 - fPolyPos) * fSurroundFactor;
/*N*/                   }
/*N*/                   else
/*N*/                   {
/*N*/                       aTexture3D[3].X() = fPolyPos * fSurroundFactor;
/*N*/                       aTexture3D[3].Y() = fTextureStart;
/*N*/
/*N*/                       aTexture3D[2].X() = fPolyPos * fSurroundFactor;
/*N*/                       aTexture3D[2].Y() = fTextureStart + fTextureDepth;
/*N*/                   }
/*N*/
/*N*/                   AddGeometry(aRect3D, aNormal3D, aTexture3D, FALSE);
/*N*/               }
/*N*/               else
/*N*/                   AddGeometry(aRect3D, aNormal3D, FALSE);
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       for(UINT16 a=0;a<nPolyCnt;a++)
/*N*/       {
/*N*/           const Polygon3D& rPoly3DFront = rPolyPolyFront[a];
/*N*/           const Polygon3D& rPoly3DBack = rPolyPolyBack[a];
/*N*/           Polygon3D   aRect3D(4);
/*N*/           USHORT nPntCnt = rPoly3DFront.GetPointCount();
/*N*/           USHORT nPrefillIndex = rPoly3DFront.IsClosed() ? nPntCnt - 1 : 0;
/*N*/
/*N*/           aRect3D[3] = rPoly3DFront[nPrefillIndex];
/*N*/           aRect3D[2] = rPoly3DBack[nPrefillIndex];
/*N*/
/*N*/           for (USHORT i = rPoly3DFront.IsClosed() ? 0 : 1; i < nPntCnt; i++)
/*N*/           {
/*N*/               aRect3D[0] = aRect3D[3];
/*N*/               aRect3D[1] = aRect3D[2];
/*N*/
/*N*/               aRect3D[3] = rPoly3DFront[i];
/*N*/               aRect3D[2] = rPoly3DBack[i];
/*N*/
/*N*/               AddGeometry(aRect3D, FALSE);
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void E3dCompoundObject::AddInBetweenNormals(
/*N*/   const PolyPolygon3D& rPolyPolyFront,
/*N*/   const PolyPolygon3D& rPolyPolyBack,
/*N*/   PolyPolygon3D& rNormals,
/*N*/   BOOL bSmoothed)
/*N*/ {
/*N*/   USHORT nPolyCnt = rPolyPolyFront.Count();
/*N*/
/*N*/   // Verbindungsstuecke
/*N*/   for(UINT16 a=0;a<nPolyCnt;a++)
/*N*/   {
/*N*/       const Polygon3D& rPoly3DFront = rPolyPolyFront[a];
/*N*/       const Polygon3D& rPoly3DBack = rPolyPolyBack[a];
/*N*/       Polygon3D& rNormalPoly = rNormals[a];
/*N*/       USHORT nPntCnt = rPoly3DFront.GetPointCount();
/*N*/
/*N*/       if(rPoly3DBack.IsClosed())
/*N*/       {
/*N*/           Vector3D aNormal = (rPoly3DBack[nPntCnt - 1] - rPoly3DFront[nPntCnt - 1])
/*N*/                     |(rPoly3DFront[0] - rPoly3DFront[nPntCnt - 1]);
/*N*/           aNormal.Normalize();
/*N*/           for (USHORT i = 0; i < nPntCnt; i++)
/*N*/           {
/*N*/               Vector3D aNextNormal = (rPoly3DBack[i] - rPoly3DFront[i])
/*N*/                   |(rPoly3DFront[(i+1 == nPntCnt) ? 0 : i+1] - rPoly3DFront[i]);
/*N*/               aNextNormal.Normalize();
/*N*/               if(bSmoothed)
/*N*/               {
/*N*/                   Vector3D aMidNormal = aNormal + aNextNormal;
/*N*/                   aMidNormal.Normalize();
/*N*/                   rNormalPoly[i] += aMidNormal;
/*N*/               }
/*N*/               else
/*N*/                   rNormalPoly[i] += aNormal;
/*N*/               rNormalPoly[i].Normalize();
/*N*/               aNormal = aNextNormal;
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           Vector3D aNormal;
/*N*/           if(rPoly3DBack[0] == rPoly3DFront[0])
/*N*/           {
/*N*/               aNormal = (rPoly3DBack[1] - rPoly3DFront[1])
/*N*/                     |(rPoly3DFront[1] - rPoly3DFront[0]);
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               aNormal = (rPoly3DBack[0] - rPoly3DFront[0])
/*N*/                     |(rPoly3DFront[1] - rPoly3DFront[0]);
/*N*/           }
/*N*/           aNormal.Normalize();
/*N*/           rNormalPoly[0] += aNormal; rNormalPoly[0].Normalize();
/*N*/           for (USHORT i = 1; i < nPntCnt; i++)
/*N*/           {
/*N*/               Vector3D aNextNormal;
/*N*/               if(i+1 == nPntCnt)
/*N*/               {
/*N*/                   aNextNormal = aNormal;
/*N*/               }
/*N*/               else
/*N*/               {
/*N*/                   aNextNormal = (rPoly3DBack[i] - rPoly3DFront[i])
/*N*/                       |(rPoly3DFront[i+1] - rPoly3DFront[i]);
/*N*/               }
/*N*/               aNextNormal.Normalize();
/*N*/               if(bSmoothed)
/*N*/               {
/*N*/                   Vector3D aMidNormal = aNormal + aNextNormal;
/*N*/                   aMidNormal.Normalize();
/*N*/                   rNormalPoly[i] += aMidNormal;
/*N*/               }
/*N*/               else
/*N*/                   rNormalPoly[i] += aNormal;
/*N*/               rNormalPoly[i].Normalize();
/*N*/               aNormal = aNextNormal;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Copy-Operator
|*
\************************************************************************/

//STRIP001 void E3dCompoundObject::operator=(const SdrObject& rObj)
//STRIP001 {
//STRIP001  // erstmal alle Childs kopieren
//STRIP001  E3dObject::operator=(rObj);
//STRIP001
//STRIP001  // weitere Parameter kopieren
//STRIP001  const E3dCompoundObject& r3DObj = (const E3dCompoundObject&) rObj;
//STRIP001
//STRIP001  aDisplayGeometry = r3DObj.aDisplayGeometry;
//STRIP001  bCreateNormals = r3DObj.bCreateNormals;
//STRIP001  bCreateTexture = r3DObj.bCreateTexture;
//STRIP001  bGeometryValid = r3DObj.bGeometryValid;
//STRIP001  bBytesLeft = r3DObj.bBytesLeft;
//STRIP001  bCreateE3dPolyObj = r3DObj.bCreateE3dPolyObj;
//STRIP001
//STRIP001  // neu ab 383:
//STRIP001  aMaterialAmbientColor = r3DObj.aMaterialAmbientColor;
//STRIP001
//STRIP001  aBackMaterial = r3DObj.aBackMaterial;
//STRIP001  bUseDifferentBackMaterial = r3DObj.bUseDifferentBackMaterial;
//STRIP001 }

/*************************************************************************
|*
|* Ausgabeparameter an 3D-Kontext setzen
|*
\************************************************************************/

//STRIP001 void E3dCompoundObject::ImpSet3DParForFill(ExtOutputDevice& rOut, Base3D* pBase3D,
//STRIP001  BOOL& bDrawObject, UINT16 nDrawFlags, BOOL bGhosted, BOOL bIsFillDraft)
//STRIP001 {
//STRIP001  if(bIsFillDraft)
//STRIP001  {
//STRIP001      bDrawObject = FALSE;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      const SfxItemSet& rSet = GetItemSet();
//STRIP001      const XFillStyle eFillStyle = ((const XFillStyleItem&)(rSet.Get(XATTR_FILLSTYLE))).GetValue();
//STRIP001
//STRIP001      if(eFillStyle == XFILL_NONE)
//STRIP001      {
//STRIP001          bDrawObject = FALSE;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          sal_uInt16 nFillTrans = ((const XFillTransparenceItem&)(rSet.Get(XATTR_FILLTRANSPARENCE))).GetValue();
//STRIP001          const XFillFloatTransparenceItem& rFloatTrans = ((const XFillFloatTransparenceItem&)(rSet.Get(XATTR_FILLFLOATTRANSPARENCE)));
//STRIP001          BOOL bFillTransparence = (nFillTrans != 0);
//STRIP001          BOOL bFloatTransparence = rFloatTrans.IsEnabled();
//STRIP001          BOOL bAnyTransparence = (bFillTransparence || bFloatTransparence);
//STRIP001          BOOL bDrawTransparence = ((nDrawFlags & E3D_DRAWFLAG_TRANSPARENT) != 0);
//STRIP001
//STRIP001          // force no fill transparence when float transparence
//STRIP001          if(bFloatTransparence)
//STRIP001          {
//STRIP001              bFillTransparence = FALSE;
//STRIP001              nFillTrans = 0;
//STRIP001          }
//STRIP001
//STRIP001          if(bAnyTransparence != bDrawTransparence)
//STRIP001          {
//STRIP001              bDrawObject = FALSE;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              // get base color
//STRIP001              Color aColorSolid = ((const XFillColorItem&) (rSet.Get(XATTR_FILLCOLOR))).GetValue();
//STRIP001              if(bGhosted)
//STRIP001              {
//STRIP001                  aColorSolid = Color(
//STRIP001                      (aColorSolid.GetRed() >> 1) + 0x80,
//STRIP001                      (aColorSolid.GetGreen() >> 1) + 0x80,
//STRIP001                      (aColorSolid.GetBlue() >> 1) + 0x80);
//STRIP001              }
//STRIP001
//STRIP001              // prepare custom colors for linear transparency and black/white mode
//STRIP001              Color aColorSolidWithTransparency(aColorSolid);
//STRIP001              aColorSolidWithTransparency.SetTransparency((UINT8)(nFillTrans * 255 / 100));
//STRIP001              Color aColorWhite(COL_WHITE);
//STRIP001              Color aColorWhiteWithTransparency(COL_WHITE);
//STRIP001              aColorWhiteWithTransparency.SetTransparency((UINT8)(nFillTrans * 255 / 100));
//STRIP001
//STRIP001              // set base materials (if no drawmode is set)
//STRIP001              pBase3D->SetMaterial(aColorWhite, Base3DMaterialAmbient);
//STRIP001              pBase3D->SetMaterial(aColorWhiteWithTransparency, Base3DMaterialDiffuse);
//STRIP001              pBase3D->SetMaterial(GetMaterialSpecular(), Base3DMaterialSpecular);
//STRIP001              pBase3D->SetMaterial(GetMaterialEmission(), Base3DMaterialEmission);
//STRIP001              pBase3D->SetShininess(GetMaterialSpecularIntensity());
//STRIP001              if(GetUseDifferentBackMaterial())
//STRIP001              {
//STRIP001                  pBase3D->SetMaterial(aColorWhite, Base3DMaterialAmbient, Base3DMaterialBack);
//STRIP001                  pBase3D->SetMaterial(aColorWhiteWithTransparency, Base3DMaterialDiffuse, Base3DMaterialBack);
//STRIP001                  pBase3D->SetMaterial(aBackMaterial.GetMaterial(Base3DMaterialSpecular), Base3DMaterialSpecular, Base3DMaterialBack);
//STRIP001                  pBase3D->SetMaterial(aBackMaterial.GetMaterial(Base3DMaterialEmission), Base3DMaterialEmission, Base3DMaterialBack);
//STRIP001                  pBase3D->SetShininess(aBackMaterial.GetShininess(), Base3DMaterialBack);
//STRIP001              }
//STRIP001
//STRIP001              // prepare some more later used texture parameters
//STRIP001              B3dTexture* pTexture = NULL;
//STRIP001              Base3DTextureWrap eWrapX(Base3DTextureRepeat);
//STRIP001              Base3DTextureWrap eWrapY(Base3DTextureRepeat);
//STRIP001              Matrix4D mTexture;
//STRIP001
//STRIP001              // now test the different draw modes and cases
//STRIP001              if((pBase3D->GetOutputDevice()->GetDrawMode() & DRAWMODE_WHITEFILL) != 0)
//STRIP001              {
//STRIP001                  // set material to black and white mode
//STRIP001                  pBase3D->SetMaterial(aColorWhite, Base3DMaterialAmbient);
//STRIP001                  pBase3D->SetMaterial(aColorWhiteWithTransparency, Base3DMaterialDiffuse);
//STRIP001                  if(GetUseDifferentBackMaterial())
//STRIP001                  {
//STRIP001                      pBase3D->SetMaterial(aColorWhite, Base3DMaterialAmbient, Base3DMaterialBack);
//STRIP001                      pBase3D->SetMaterial(aColorWhiteWithTransparency, Base3DMaterialDiffuse, Base3DMaterialBack);
//STRIP001                  }
//STRIP001
//STRIP001                  // Color stays white, just set render mode
//STRIP001                  pBase3D->SetRenderMode(Base3DRenderFill);
//STRIP001              }
//STRIP001              else if((pBase3D->GetOutputDevice()->GetDrawMode() & DRAWMODE_SETTINGSFILL) != 0)
//STRIP001              {
//STRIP001                  Color aColorFill(Application::GetSettings().GetStyleSettings().GetWindowColor());
//STRIP001                  Color aColorFillWithTransparency(aColorFill);
//STRIP001                  aColorFillWithTransparency.SetTransparency((UINT8)(nFillTrans * 255 / 100));
//STRIP001
//STRIP001                  // set material to black and white mode
//STRIP001                  pBase3D->SetMaterial(aColorFill, Base3DMaterialAmbient);
//STRIP001                  pBase3D->SetMaterial(aColorFillWithTransparency, Base3DMaterialDiffuse);
//STRIP001                  if(GetUseDifferentBackMaterial())
//STRIP001                  {
//STRIP001                      pBase3D->SetMaterial(aColorFill, Base3DMaterialAmbient, Base3DMaterialBack);
//STRIP001                      pBase3D->SetMaterial(aColorFillWithTransparency, Base3DMaterialDiffuse, Base3DMaterialBack);
//STRIP001                  }
//STRIP001
//STRIP001                  // Color stays solid, just set render mode
//STRIP001                  pBase3D->SetRenderMode(Base3DRenderFill);
//STRIP001              }
//STRIP001              else if(eFillStyle == XFILL_BITMAP)
//STRIP001              {
//STRIP001                  // bitmap fill, use bitmap texture from 2D defines
//STRIP001                  BitmapEx aBmpEx;
//STRIP001
//STRIP001                  if(SFX_ITEM_SET == rSet.GetItemState(XATTR_FILLBITMAP, TRUE))
//STRIP001                  {
//STRIP001                      // EIndeutige Bitmap, benutze diese
//STRIP001                      aBmpEx = BitmapEx((((const XFillBitmapItem&) (rSet.Get(XATTR_FILLBITMAP))).GetValue()).GetBitmap());
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      // Keine eindeutige Bitmap. benutze default
//STRIP001                      //
//STRIP001                      // DIES IST EINE NOTLOESUNG, BIS MAN IRGENDWO AN DIE
//STRIP001                      // DEAULT-BITMAP RANKOMMT (IST VON KA IN VORBEREITUNG)
//STRIP001                      //
//STRIP001                      aBmpEx = BitmapEx(Bitmap(Size(4,4), 8));
//STRIP001                  }
//STRIP001
//STRIP001                  // Texturattribute bilden
//STRIP001                  TextureAttributesBitmap aTexAttr(
//STRIP001                      bGhosted,
//STRIP001                      (void*)&rSet.Get(XATTR_FILLFLOATTRANSPARENCE),
//STRIP001                      aBmpEx.GetBitmap());
//STRIP001                  pTexture = pBase3D->ObtainTexture(aTexAttr);
//STRIP001                  if(!pTexture)
//STRIP001                  {
//STRIP001                      if(bGhosted)
//STRIP001                          aBmpEx.Adjust( 50 );
//STRIP001
//STRIP001                      if(bFloatTransparence)
//STRIP001                          // add alpha channel to bitmap
//STRIP001                          aBmpEx = BitmapEx(aBmpEx.GetBitmap(), GetAlphaMask(rSet, aBmpEx.GetSizePixel()));
//STRIP001
//STRIP001                      pTexture = pBase3D->ObtainTexture(aTexAttr, aBmpEx);
//STRIP001                  }
//STRIP001
//STRIP001                  sal_uInt16 nOffX = ((const SfxUInt16Item&) (rSet.Get(XATTR_FILLBMP_TILEOFFSETX))).GetValue();
//STRIP001                  sal_uInt16 nOffY = ((const SfxUInt16Item&) (rSet.Get(XATTR_FILLBMP_TILEOFFSETY))).GetValue();
//STRIP001                  sal_uInt16 nOffPosX = ((const SfxUInt16Item&) (rSet.Get(XATTR_FILLBMP_POSOFFSETX))).GetValue();
//STRIP001                  sal_uInt16 nOffPosY = ((const SfxUInt16Item&) (rSet.Get(XATTR_FILLBMP_POSOFFSETY))).GetValue();
//STRIP001                  RECT_POINT eRectPoint = (RECT_POINT)((const SfxEnumItem&) (rSet.Get(XATTR_FILLBMP_POS))).GetValue();
//STRIP001                  BOOL bTile = ((const SfxBoolItem&) (rSet.Get(XATTR_FILLBMP_TILE))).GetValue();
//STRIP001                  BOOL bStretch = ((const SfxBoolItem&) (rSet.Get(XATTR_FILLBMP_STRETCH))).GetValue();
//STRIP001                  BOOL bLogSize = ((const SfxBoolItem&) (rSet.Get(XATTR_FILLBMP_SIZELOG))).GetValue();
//STRIP001                  Size aSize(
//STRIP001                      labs(((const SfxMetricItem&)(rSet.Get(XATTR_FILLBMP_SIZEX))).GetValue()),
//STRIP001                      labs(((const SfxMetricItem&)(rSet.Get(XATTR_FILLBMP_SIZEY))).GetValue()));
//STRIP001                  Vector3D aScaleVector(1.0, 1.0, 1.0);
//STRIP001                  Vector3D aTranslateVector(0.0, 0.0, 0.0);
//STRIP001
//STRIP001                  // Groesse beachten, logische Groesse einer Kachel bestimmen
//STRIP001                  // erst mal in 1/100 mm
//STRIP001                  Size aLogicalSize = aBmpEx.GetPrefSize();
//STRIP001                  const Volume3D& rVol = GetBoundVolume();
//STRIP001                  if(aLogicalSize.Width() == 0 || aLogicalSize.Height() == 0)
//STRIP001                  {
//STRIP001                      // Keine logische Groesse, nimm Pixelgroesse
//STRIP001                      // und wandle diese um
//STRIP001                      aLogicalSize = Application::GetDefaultDevice()->PixelToLogic(aBmpEx.GetSizePixel(), MAP_100TH_MM);
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      if ( aBmpEx.GetPrefMapMode() == MAP_PIXEL )
//STRIP001                          aLogicalSize = Application::GetDefaultDevice()->PixelToLogic( aLogicalSize, MAP_100TH_MM );
//STRIP001                      else
//STRIP001                          aLogicalSize = OutputDevice::LogicToLogic( aLogicalSize, aBmpEx.GetPrefMapMode(), MAP_100TH_MM );
//STRIP001                  }
//STRIP001
//STRIP001                  if(bLogSize)
//STRIP001                  {
//STRIP001                      // logische Groesse
//STRIP001                      if(aSize.Width() == 0 && aSize.Height() == 0)
//STRIP001                      {
//STRIP001                          // Originalgroesse benutzen, Original flagy
//STRIP001
//STRIP001                          // Um ein vernuenftiges Mapping bei defaults auch
//STRIP001                          // fuer 3D-Objekte zu erreichen, nimm die logische
//STRIP001                          // groesse einfach als groesser an
//STRIP001                          aLogicalSize.Width() /= 5; //10;
//STRIP001                          aLogicalSize.Height() /= 5; //10;
//STRIP001                      }
//STRIP001                      else
//STRIP001                      {
//STRIP001                          // Groesse in 100TH_MM in aSize, keine Flags
//STRIP001                          aLogicalSize = aSize;
//STRIP001
//STRIP001                          // Um ein vernuenftiges Mapping bei defaults auch
//STRIP001                          // fuer 3D-Objekte zu erreichen, nimm die logische
//STRIP001                          // groesse einfach als groesser an
//STRIP001                          aLogicalSize.Width() /= 5; //10;
//STRIP001                          aLogicalSize.Height() /= 5; //10;
//STRIP001                      }
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      // relative Groesse
//STRIP001                      // 0..100 Prozent in aSize, relativ flag
//STRIP001                      aLogicalSize = Size(
//STRIP001                          (long)((rVol.GetWidth() * (double)aSize.Width() / 100.0) + 0.5),
//STRIP001                          (long)((rVol.GetHeight() * (double)aSize.Height() / 100.0) + 0.5));
//STRIP001                  }
//STRIP001
//STRIP001                  // Skalieren
//STRIP001                  aScaleVector.X() = rVol.GetWidth() / (double)aLogicalSize.Width();
//STRIP001                  aScaleVector.Y() = rVol.GetHeight() / (double)aLogicalSize.Height();
//STRIP001
//STRIP001                  if(bTile)
//STRIP001                  {
//STRIP001                      // Aneinandergefuegt drauflegen
//STRIP001                      double fLeftBound, fTopBound;
//STRIP001
//STRIP001                      // Vertikal
//STRIP001                      if(eRectPoint == RP_LT || eRectPoint == RP_LM || eRectPoint == RP_LB)
//STRIP001                      {
//STRIP001                          // Links aligned starten
//STRIP001                          fLeftBound = 0.0;
//STRIP001                      }
//STRIP001                      else if(eRectPoint == RP_MT || eRectPoint == RP_MM || eRectPoint == RP_MB)
//STRIP001                      {
//STRIP001                          // Mittig
//STRIP001                          fLeftBound = (rVol.GetWidth() / 2.0)
//STRIP001                              - ((double)aLogicalSize.Width() / 2.0);
//STRIP001                      }
//STRIP001                      else
//STRIP001                      {
//STRIP001                          // Rechts aligned starten
//STRIP001                          fLeftBound = rVol.GetWidth()
//STRIP001                              - (double)aLogicalSize.Width();
//STRIP001                      }
//STRIP001
//STRIP001                      // Horizontal
//STRIP001                      if(eRectPoint == RP_LT || eRectPoint == RP_MT || eRectPoint == RP_RT)
//STRIP001                      {
//STRIP001                          // Top aligned starten
//STRIP001                          fTopBound = 0.0;
//STRIP001                      }
//STRIP001                      else if(eRectPoint == RP_LM || eRectPoint == RP_MM || eRectPoint == RP_RM)
//STRIP001                      {
//STRIP001                          // Mittig
//STRIP001                          fTopBound = (rVol.GetHeight() / 2.0)
//STRIP001                              - ((double)aLogicalSize.Height() / 2.0);
//STRIP001                      }
//STRIP001                      else
//STRIP001                      {
//STRIP001                          // Bottom aligned starten
//STRIP001                          fTopBound = rVol.GetHeight()
//STRIP001                              - (double)aLogicalSize.Height();
//STRIP001                      }
//STRIP001
//STRIP001                      // Verschieben
//STRIP001                      aTranslateVector.X() = fLeftBound;
//STRIP001                      aTranslateVector.Y() = fTopBound;
//STRIP001
//STRIP001                      // Offset beachten
//STRIP001                      if(nOffPosX || nOffPosY)
//STRIP001                      {
//STRIP001                          aTranslateVector.X() += (double)aLogicalSize.Width() * ((double)nOffPosX / 100.0);
//STRIP001                          aTranslateVector.Y() += (double)aLogicalSize.Height() * ((double)nOffPosY / 100.0);
//STRIP001                      }
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      if(bStretch)
//STRIP001                      {
//STRIP001                          // 1x drauflegen, alles wie gehabt
//STRIP001                          // fertig
//STRIP001                          aScaleVector.X() = 1.0;
//STRIP001                          aScaleVector.Y() = 1.0;
//STRIP001                      }
//STRIP001                      else
//STRIP001                      {
//STRIP001                          // nur einmal benutzen
//STRIP001                          eWrapX = Base3DTextureSingle;
//STRIP001                          eWrapY = Base3DTextureSingle;
//STRIP001
//STRIP001                          // Groesse beachten, zentriert anlegen
//STRIP001                          double fLeftBound = (rVol.GetWidth() / 2.0) - ((double)aLogicalSize.Width() / 2.0);
//STRIP001                          double fTopBound = (rVol.GetHeight() / 2.0) - ((double)aLogicalSize.Height() / 2.0);
//STRIP001
//STRIP001                          // Verschieben
//STRIP001                          aTranslateVector.X() = fLeftBound;
//STRIP001                          aTranslateVector.Y() = fTopBound;
//STRIP001                      }
//STRIP001                  }
//STRIP001
//STRIP001                  // TranslateVector anpassen
//STRIP001                  if(aTranslateVector.X())
//STRIP001                      aTranslateVector.X() /= -rVol.GetWidth();
//STRIP001                  if(aTranslateVector.Y())
//STRIP001                      aTranslateVector.Y() /= -rVol.GetHeight();
//STRIP001
//STRIP001                  // Texturtransformation setzen
//STRIP001                  mTexture.Translate(aTranslateVector);
//STRIP001                  mTexture.Scale(aScaleVector);
//STRIP001              }
//STRIP001              else if(eFillStyle == XFILL_GRADIENT)
//STRIP001              {
//STRIP001                  // gradient fill. Create texture and set.
//STRIP001                  TextureAttributesGradient aTexAttr(
//STRIP001                      bGhosted,
//STRIP001                      (void*)&rSet.Get(XATTR_FILLFLOATTRANSPARENCE),
//STRIP001                      (void*)&rSet.Get(XATTR_FILLGRADIENT),
//STRIP001                      (void*)&rSet.Get(XATTR_GRADIENTSTEPCOUNT));
//STRIP001
//STRIP001                  pTexture = pBase3D->ObtainTexture(aTexAttr);
//STRIP001                  if(!pTexture)
//STRIP001                  {
//STRIP001                      BitmapEx aBmpEx = BitmapEx(GetGradientBitmap(rSet));
//STRIP001
//STRIP001                      if(bFloatTransparence)
//STRIP001                          // add alpha channel to bitmap
//STRIP001                          aBmpEx = BitmapEx(aBmpEx.GetBitmap(), GetAlphaMask(rSet, aBmpEx.GetSizePixel()));
//STRIP001
//STRIP001                      if(bGhosted)
//STRIP001                          aBmpEx.Adjust( 50 );
//STRIP001                      pTexture = pBase3D->ObtainTexture(aTexAttr, aBmpEx);
//STRIP001                  }
//STRIP001              }
//STRIP001              else if(eFillStyle == XFILL_HATCH)
//STRIP001              {
//STRIP001                  // hatch fill. Create texture and set.
//STRIP001                  TextureAttributesHatch aTexAttr(
//STRIP001                      bGhosted,
//STRIP001                      (void*)&rSet.Get(XATTR_FILLFLOATTRANSPARENCE),
//STRIP001                      (void*)&rSet.Get(XATTR_FILLHATCH));
//STRIP001
//STRIP001                  pTexture = pBase3D->ObtainTexture(aTexAttr);
//STRIP001                  if(!pTexture)
//STRIP001                  {
//STRIP001                      BitmapEx aBmpEx = GetHatchBitmap(rSet);
//STRIP001
//STRIP001                      if(bFloatTransparence)
//STRIP001                          // add alpha channel to bitmap
//STRIP001                          aBmpEx = BitmapEx(aBmpEx.GetBitmap(), GetAlphaMask(rSet, aBmpEx.GetSizePixel()));
//STRIP001
//STRIP001                      if(bGhosted)
//STRIP001                          aBmpEx.Adjust( 50 );
//STRIP001                      pTexture = pBase3D->ObtainTexture(aTexAttr, aBmpEx);
//STRIP001                  }
//STRIP001
//STRIP001                  // set different texture transformation
//STRIP001                  mTexture.Scale(Vector3D(20.0, 20.0, 20.0));
//STRIP001              }
//STRIP001              else if(eFillStyle == XFILL_SOLID)
//STRIP001              {
//STRIP001                  if(bFloatTransparence)
//STRIP001                  {
//STRIP001                      // Texturattribute bilden
//STRIP001                      TextureAttributesColor aTexAttr(
//STRIP001                          bGhosted,
//STRIP001                          (void*)&rSet.Get(XATTR_FILLFLOATTRANSPARENCE),
//STRIP001                          aColorSolid);
//STRIP001
//STRIP001                      pTexture = pBase3D->ObtainTexture(aTexAttr);
//STRIP001                      if(!pTexture)
//STRIP001                      {
//STRIP001                          // build single colored bitmap with draw color and add transparence bitmap
//STRIP001                          Size aSizeBitmap(128, 128);
//STRIP001                          Bitmap aForeground(aSizeBitmap, 24);
//STRIP001                          aForeground.Erase(aColorSolid);
//STRIP001
//STRIP001                          if(bGhosted)
//STRIP001                              aForeground.Adjust( 50 );
//STRIP001
//STRIP001                          // add alpha channel to bitmap
//STRIP001                          BitmapEx aBmpEx(aForeground, GetAlphaMask(rSet, aSizeBitmap));
//STRIP001
//STRIP001                          pTexture = pBase3D->ObtainTexture(aTexAttr, aBmpEx);
//STRIP001                      }
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      // set material to base color
//STRIP001                      pBase3D->SetMaterial(aColorSolid, Base3DMaterialAmbient);
//STRIP001                      pBase3D->SetMaterial(aColorSolidWithTransparency, Base3DMaterialDiffuse);
//STRIP001                      if(GetUseDifferentBackMaterial())
//STRIP001                      {
//STRIP001                          pBase3D->SetMaterial(aBackMaterial.GetMaterial(Base3DMaterialAmbient), Base3DMaterialAmbient, Base3DMaterialBack);
//STRIP001                          pBase3D->SetMaterial(aBackMaterial.GetMaterial(Base3DMaterialDiffuse), Base3DMaterialDiffuse, Base3DMaterialBack);
//STRIP001                      }
//STRIP001
//STRIP001                      // and at last, the render mode.
//STRIP001                      pBase3D->SetRenderMode(Base3DRenderFill);
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  DBG_ERROR("unknown drawing mode (!)");
//STRIP001              }
//STRIP001
//STRIP001              // use texture?
//STRIP001              if(pTexture)
//STRIP001              {
//STRIP001                  // set values for texture modes
//STRIP001                  pTexture->SetTextureKind(GetTextureKind());
//STRIP001                  pTexture->SetTextureMode(GetTextureMode());
//STRIP001                  pTexture->SetTextureFilter(GetTextureFilter() ? Base3DTextureLinear : Base3DTextureNearest);
//STRIP001                  pTexture->SetTextureWrapS(eWrapX);
//STRIP001                  pTexture->SetTextureWrapT(eWrapY);
//STRIP001                  pTexture->SetBlendColor(aColorSolid);
//STRIP001                  pTexture->SetTextureColor(aColorSolid);
//STRIP001
//STRIP001                  // activate texture
//STRIP001                  pBase3D->SetActiveTexture(pTexture);
//STRIP001                  pBase3D->SetRenderMode(Base3DRenderFill);
//STRIP001
//STRIP001                  // set texture transformation
//STRIP001                  GetScene()->GetCameraSet().SetTexture(mTexture);
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  // switch it off.texture usage
//STRIP001                  pBase3D->SetActiveTexture();
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void E3dCompoundObject::ImpSet3DParForLine(ExtOutputDevice& rOut, Base3D* pBase3D,
//STRIP001  BOOL& bDrawOutline, UINT16 nDrawFlags, BOOL bGhosted, BOOL bIsLineDraft)
//STRIP001 {
//STRIP001  // do drawflags allow line drawing at all?
//STRIP001  const SfxItemSet& rSet = GetItemSet();
//STRIP001  sal_uInt16 nLineTransparence = ((const XLineTransparenceItem&)(rSet.Get(XATTR_LINETRANSPARENCE))).GetValue();
//STRIP001  BOOL bLineTransparence = (nLineTransparence != 0);
//STRIP001  BOOL bDrawTransparence = ((nDrawFlags & E3D_DRAWFLAG_TRANSPARENT) != 0);
//STRIP001
//STRIP001  if(bLineTransparence != bDrawTransparence)
//STRIP001  {
//STRIP001      bDrawOutline = FALSE;
//STRIP001  }
//STRIP001
//STRIP001  // if no linestyle, draw no outline
//STRIP001  XLineStyle aLineStyle(XLINE_NONE);
//STRIP001  if(bDrawOutline)
//STRIP001  {
//STRIP001      aLineStyle = ((const XLineStyleItem&)(rSet.Get(XATTR_LINESTYLE))).GetValue();
//STRIP001      bDrawOutline = (aLineStyle != XLINE_NONE);
//STRIP001  }
//STRIP001
//STRIP001  // special mode for black/white drawing or high contrast mode
//STRIP001  // Linecolor is set to black before (Base3d::SetColor())
//STRIP001  if((!bDrawOutline) && ((pBase3D->GetOutputDevice()->GetDrawMode() & (DRAWMODE_WHITEFILL|DRAWMODE_SETTINGSLINE)) != 0))
//STRIP001  {
//STRIP001      bDrawOutline = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  // does the outdev use linestyle?
//STRIP001  if(bDrawOutline && !rOut.GetIgnoreLineStyle())
//STRIP001  {
//STRIP001      Color aColorLine = ((const XLineColorItem&)(rSet.Get(XATTR_LINECOLOR))).GetValue();
//STRIP001      sal_Int32 nLineWidth = ((const XLineWidthItem&)(rSet.Get(XATTR_LINEWIDTH))).GetValue();
//STRIP001
//STRIP001         if(pBase3D->GetOutputDevice()->GetDrawMode() & DRAWMODE_SETTINGSLINE)
//STRIP001         {
//STRIP001          svtools::ColorConfig aColorConfig;
//STRIP001             aColorLine = Color( aColorConfig.GetColorValue( svtools::FONTCOLOR ).nColor );
//STRIP001         }
//STRIP001
//STRIP001      if(nLineWidth && !bIsLineDraft)
//STRIP001      {
//STRIP001          Point aPnt(nLineWidth, 0);
//STRIP001          aPnt = pBase3D->GetOutputDevice()->LogicToPixel(aPnt) - pBase3D->GetOutputDevice()->LogicToPixel(Point());
//STRIP001          if(aPnt.X() <= 0)
//STRIP001              aPnt.X() = 1;
//STRIP001          pBase3D->SetLineWidth((double)aPnt.X());
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pBase3D->SetLineWidth(1.0);
//STRIP001      }
//STRIP001
//STRIP001      // Material setzen
//STRIP001      pBase3D->SetColor(aColorLine);
//STRIP001  }
//STRIP001 }

//STRIP001 void E3dCompoundObject::SetBase3DParams(ExtOutputDevice& rOut, Base3D* pBase3D,
//STRIP001  BOOL& bDrawObject, BOOL& bDrawOutline, UINT16 nDrawFlags, BOOL bGhosted,
//STRIP001  BOOL bIsLineDraft, BOOL bIsFillDraft)
//STRIP001 {
//STRIP001  bDrawObject = ((nDrawFlags & E3D_DRAWFLAG_FILLED) != 0);
//STRIP001  if(bDrawObject)
//STRIP001      ImpSet3DParForFill(rOut, pBase3D, bDrawObject, nDrawFlags, bGhosted, bIsFillDraft);
//STRIP001
//STRIP001  bDrawOutline = ((nDrawFlags & E3D_DRAWFLAG_OUTLINE) != 0);
//STRIP001  if(bDrawOutline)
//STRIP001      ImpSet3DParForLine(rOut, pBase3D, bDrawOutline, nDrawFlags, bGhosted, bIsLineDraft);
//STRIP001
//STRIP001  // Set ObjectTrans if line or fill is still set (maybe retet by upper calls)
//STRIP001  if(bDrawObject || bDrawOutline)
//STRIP001  {
//STRIP001      Matrix4D mTransform = GetFullTransform();
//STRIP001      GetScene()->GetCameraSet().SetObjectTrans(mTransform);
//STRIP001      pBase3D->SetTransformationSet(&(GetScene()->GetCameraSet()));
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Hittest fuer 3D-Objekte, wird an Geometrie weitergegeben
|*
\************************************************************************/

/*N*/ SdrObject* E3dCompoundObject::CheckHit(const Point& rPnt, USHORT nTol,
/*N*/   const SetOfByte* pVisiLayer) const
/*N*/ {
/*N*/   E3dPolyScene* pScene = (E3dPolyScene*)GetScene();
/*N*/   if(pScene)
/*N*/   {
/*N*/       // HitLine holen in ObjektKoordinaten
/*N*/       // ObjectTrans setzen
/*N*/       Matrix4D mTransform = ((E3dCompoundObject*)this)->GetFullTransform();
/*N*/       pScene->GetCameraSet().SetObjectTrans(mTransform);
/*N*/
/*N*/       // HitPoint Front und Back erzeugen und umrechnen
/*N*/       Vector3D aFront(rPnt.X(), rPnt.Y(), 0.0);
/*N*/       Vector3D aBack(rPnt.X(), rPnt.Y(), ZBUFFER_DEPTH_RANGE);
/*N*/       aFront = pScene->GetCameraSet().ViewToObjectCoor(aFront);
/*N*/       aBack = pScene->GetCameraSet().ViewToObjectCoor(aBack);
/*N*/
/*N*/       const Volume3D& rBoundVol = ((E3dCompoundObject*)this)->GetBoundVolume();
/*N*/       if(rBoundVol.IsValid())
/*N*/       {
/*N*/           double fXMax = aFront.X();
/*N*/           double fXMin = aBack.X();
/*N*/
/*N*/           if(fXMax < fXMin)
/*N*/           {
/*N*/               fXMax = aBack.X();
/*N*/               fXMin = aFront.X();
/*N*/           }
/*N*/
/*N*/           if(rBoundVol.MinVec().X() <= fXMax && rBoundVol.MaxVec().X() >= fXMin)
/*N*/           {
/*N*/               double fYMax = aFront.Y();
/*N*/               double fYMin = aBack.Y();
/*N*/
/*N*/               if(fYMax < fYMin)
/*N*/               {
/*N*/                   fYMax = aBack.Y();
/*N*/                   fYMin = aFront.Y();
/*N*/               }
/*N*/
/*N*/               if(rBoundVol.MinVec().Y() <= fYMax && rBoundVol.MaxVec().Y() >= fYMin)
/*N*/               {
/*N*/                   double fZMax = aFront.Z();
/*N*/                   double fZMin = aBack.Z();
/*N*/
/*N*/                   if(fZMax < fZMin)
/*N*/                   {
/*N*/                       fZMax = aBack.Z();
/*N*/                       fZMin = aFront.Z();
/*N*/                   }
/*N*/
/*N*/                   if(rBoundVol.MinVec().Z() <= fZMax && rBoundVol.MaxVec().Z() >= fZMin)
/*N*/                   {
/*N*/                       // Geometrie herstellen
/*N*/                       if(!bGeometryValid)
/*?*/                           ((E3dCompoundObject*)this)->ReCreateGeometry();
/*N*/
/*N*/                       // 3D Volumes schneiden sich, teste in der Geometrie
/*N*/                       // auf Basis der Projektion weiter
/*N*/                       if(((E3dCompoundObject*)this)->aDisplayGeometry.CheckHit(aFront, aBack, nTol) != -1L)
/*?*/                           return ((E3dCompoundObject*)this);
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return NULL;
/*N*/ }

/*************************************************************************
|*
|* Geometrie des Objektes auf angegebenen Punkt zentrieren
|*
\************************************************************************/

//STRIP001 void E3dCompoundObject::CenterObject(const Vector3D& rCenter)
//STRIP001 {
//STRIP001  // Geometrie herstellen
//STRIP001  if(!bGeometryValid)
//STRIP001      ReCreateGeometry();
//STRIP001
//STRIP001  Vector3D aOldCenter = aDisplayGeometry.GetCenter();
//STRIP001  Vector3D aMoveVector = rCenter - aOldCenter;
//STRIP001  Matrix4D aTransMat;
//STRIP001
//STRIP001  aTransMat.Translate(aMoveVector);
//STRIP001  SetTransform(GetTransform() * aTransMat);
//STRIP001 }

/*************************************************************************
|*
|* Schattenattribute holen
|*
\************************************************************************/

//STRIP001 Color E3dCompoundObject::GetShadowColor()
//STRIP001 {
//STRIP001  return ((SdrShadowColorItem&)(GetItem(SDRATTR_SHADOWCOLOR))).GetValue();
//STRIP001 }

//STRIP001 BOOL E3dCompoundObject::DrawShadowAsOutline()
//STRIP001 {
//STRIP001  const SfxItemSet& rSet = GetItemSet();
//STRIP001  XFillStyle eFillStyle = ((XFillStyleItem&)(rSet.Get(XATTR_FILLSTYLE))).GetValue();
//STRIP001  XLineStyle eLineStyle = ((XLineStyleItem&)(rSet.Get(XATTR_LINESTYLE))).GetValue();
//STRIP001  BOOL bFillAttrIsNone = eFillStyle == XFILL_NONE;
//STRIP001  BOOL bLineAttrIsNone = eLineStyle == XLINE_NONE;
//STRIP001  return (bFillAttrIsNone && !bLineAttrIsNone);
//STRIP001 }

//STRIP001 INT32 E3dCompoundObject::GetShadowXDistance()
//STRIP001 {
//STRIP001  return (long)((SdrShadowXDistItem&)(GetItem(SDRATTR_SHADOWXDIST))).GetValue();
//STRIP001 }

//STRIP001 INT32 E3dCompoundObject::GetShadowYDistance()
//STRIP001 {
//STRIP001  return (long)((SdrShadowYDistItem&)(GetItem(SDRATTR_SHADOWYDIST))).GetValue();
//STRIP001 }

//STRIP001 UINT16 E3dCompoundObject::GetShadowTransparence()
//STRIP001 {
//STRIP001  return (UINT16)((SdrShadowTransparenceItem&)(GetItem(SDRATTR_SHADOWTRANSPARENCE))).GetValue();
//STRIP001 }

/*N*/ BOOL E3dCompoundObject::DoDrawShadow()
/*N*/ {
/*N*/   const SfxItemSet& rSet = GetItemSet();
/*N*/   BOOL bRetval(FALSE);
/*N*/   BOOL bShadOn = ((SdrShadowItem&)(rSet.Get(SDRATTR_SHADOW))).GetValue();
/*N*/
/*N*/   if(bShadOn)
/*N*/   {
/*?*/       bRetval = TRUE;
/*?*/
/*?*/       if(((XFillStyleItem&)(rSet.Get(XATTR_FILLSTYLE))).GetValue() == XFILL_NONE)
/*?*/       {
/*?*/           if(((XLineStyleItem&)(rSet.Get(XATTR_LINESTYLE))).GetValue() == XLINE_NONE)
/*?*/           {
/*?*/               bRetval = FALSE;
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/   return bRetval;
/*N*/ }

/*************************************************************************
|*
|* Objekt als WireFrame zeichnen
|*
\************************************************************************/

//STRIP001 void E3dCompoundObject::DrawObjectWireframe(ExtOutputDevice& rXOut)
//STRIP001 {
//STRIP001  UINT32 nPolyCounter = 0;
//STRIP001  UINT32 nEntityCounter = 0;
//STRIP001  UINT32 nUpperBound;
//STRIP001  Point aFirstPoint, aLastPoint, aNewPoint;
//STRIP001  B3dEntityBucket& rEntityBucket = GetDisplayGeometry().GetEntityBucket();
//STRIP001  GeometryIndexValueBucket& rIndexBucket = GetDisplayGeometry().GetIndexBucket();
//STRIP001  B3dTransformationSet& rTransSet = GetScene()->GetCameraSet();
//STRIP001  BOOL bDrawLine, bLastDrawLine;
//STRIP001  Vector3D aPoint;
//STRIP001
//STRIP001  while(nPolyCounter < rIndexBucket.Count())
//STRIP001  {
//STRIP001      // Naechstes Primitiv
//STRIP001      nUpperBound = rIndexBucket[nPolyCounter++].GetIndex();
//STRIP001      bDrawLine = bLastDrawLine = rEntityBucket[nEntityCounter].IsEdgeVisible();
//STRIP001      aPoint = rTransSet.ObjectToViewCoor(rEntityBucket[nEntityCounter++].Point().GetVector3D());
//STRIP001      aFirstPoint.X() = (long)(aPoint.X() + 0.5);
//STRIP001      aFirstPoint.Y() = (long)(aPoint.Y() + 0.5);
//STRIP001      aLastPoint = aFirstPoint;
//STRIP001
//STRIP001      // Polygon fuellen
//STRIP001      while(nEntityCounter < nUpperBound)
//STRIP001      {
//STRIP001          // Punkt holen und auf Weltkoordinaten umrechnen
//STRIP001          bDrawLine = rEntityBucket[nEntityCounter].IsEdgeVisible();
//STRIP001          aPoint = rTransSet.ObjectToViewCoor(rEntityBucket[nEntityCounter++].Point().GetVector3D());
//STRIP001          aNewPoint.X() = (long)(aPoint.X() + 0.5);
//STRIP001          aNewPoint.Y() = (long)(aPoint.Y() + 0.5);
//STRIP001          if(bLastDrawLine)
//STRIP001              rXOut.GetOutDev()->DrawLine(aLastPoint, aNewPoint);
//STRIP001          aLastPoint = aNewPoint;
//STRIP001          bLastDrawLine = bDrawLine;
//STRIP001      }
//STRIP001
//STRIP001      // Polygon scliessen
//STRIP001      if(bLastDrawLine)
//STRIP001          rXOut.GetOutDev()->DrawLine(aLastPoint, aFirstPoint);
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Create vertical polygons for line polygon
|*
\************************************************************************/

// #78972#
/*N*/ void E3dCompoundObject::ImpCompleteLinePolygon(PolyPolygon3D& rLinePolyPoly,
/*N*/   sal_uInt16 nPolysPerRun, BOOL bClosed)
/*N*/ {
/*N*/   if(rLinePolyPoly.Count() && nPolysPerRun)
/*N*/   {
/*N*/       // get number of layers
/*N*/       sal_uInt16 nLayers(rLinePolyPoly.Count() / nPolysPerRun);
/*N*/       sal_uInt16 a, b, c;
/*N*/
/*N*/       // add vertical Polygons if at least two horizontal ones exist
/*N*/       if(nLayers > 1)
/*N*/       {
/*N*/           for(a = 0; a < nPolysPerRun; a++)
/*N*/           {
/*N*/               const sal_uInt16 nPntCnt = rLinePolyPoly[a].GetPointCount();
/*N*/
/*N*/               for(b = 0; b < nPntCnt; b++)
/*N*/               {
/*N*/                   Polygon3D aNewVerPoly(bClosed ? nLayers + 1 : nLayers);
/*N*/
/*N*/                   for(c = 0; c < nLayers; c++)
/*N*/                       aNewVerPoly[c] = rLinePolyPoly[(c * nPolysPerRun) + a][b];
/*N*/
/*N*/                   // evtl. set first point again to close polygon
/*N*/                   if(bClosed)
/*N*/                       aNewVerPoly[aNewVerPoly.GetPointCount()] = aNewVerPoly[0];
/*N*/
/*N*/                   // insert
/*N*/                   rLinePolyPoly.Insert(aNewVerPoly);
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/
/*N*/       // open closed polygons
/*N*/       for(a = 0; a < rLinePolyPoly.Count(); a++)
/*N*/       {
/*N*/           if(rLinePolyPoly[a].IsClosed())
/*N*/           {
/*N*/               rLinePolyPoly[a][rLinePolyPoly[a].GetPointCount()] = rLinePolyPoly[a][0];
/*N*/               rLinePolyPoly[a].SetClosed(FALSE);
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }
/*N*/
/*************************************************************************
|*
|* Ein Segment fuer Extrude oder Lathe erzeugen
|*
\************************************************************************/

/*N*/ void E3dCompoundObject::ImpCreateSegment(
/*N*/   const PolyPolygon3D& rFront,        // vorderes Polygon
/*N*/   const PolyPolygon3D& rBack,         // hinteres Polygon
/*N*/   const PolyPolygon3D* pPrev,         // smooth uebergang zu Vorgaenger
/*N*/   const PolyPolygon3D* pNext,         // smooth uebergang zu Nachfolger
/*N*/   BOOL bCreateFront,                  // vorderen Deckel erzeugen
/*N*/   BOOL bCreateBack,                   // hinteren Deckel erzeugen
/*N*/   double fPercentDiag,                // Anteil des Deckels an der Tiefe
/*N*/   BOOL bSmoothLeft,                   // Glaetten der umlaufenden Normalen links
/*N*/   BOOL bSmoothRight,                  // Glaetten der umlaufenden Normalen rechts
/*N*/   BOOL bSmoothFrontBack,              // Glaetten der Abschlussflaechen
/*N*/   double fSurroundFactor,             // Wertebereich der Texturkoordinaten im Umlauf
/*N*/   double fTextureStart,               // TexCoor ueber Extrude-Tiefe
/*N*/   double fTextureDepth,               // TexCoor ueber Extrude-Tiefe
/*N*/   BOOL bCreateTexture,
/*N*/   BOOL bCreateNormals,
/*N*/   BOOL bCharacterExtrude,             // FALSE=exakt, TRUE=ohne Ueberschneidungen
/*N*/   BOOL bRotateTexture90,              // Textur der Seitenflaechen um 90 Grad kippen
/*N*/   PolyPolygon3D* pLineGeometry        // For creation of line geometry
/*N*/   )
/*N*/ {
/*N*/   PolyPolygon3D aNormalsLeft, aNormalsRight;
/*N*/   AddInBetweenNormals(rFront, rBack, aNormalsLeft, bSmoothLeft);
/*N*/   AddInBetweenNormals(rFront, rBack, aNormalsRight, bSmoothRight);
/*N*/   Vector3D aOffset = rBack.GetMiddle() - rFront.GetMiddle();
/*N*/
/*N*/   // Ausnahmen: Nicht geschlossen
/*N*/   if(!rFront.IsClosed())
/*N*/   {
/*N*/       bCreateFront = FALSE;
/*N*/   }
/*N*/   if(!rBack.IsClosed())
/*N*/   {
/*N*/       bCreateBack = FALSE;
/*N*/   }
/*N*/
/*N*/   // Ausnahmen: Einfache Linie
/*N*/   if(rFront[0].GetPointCount() < 3 || (!bCreateFront && !bCreateBack))
/*N*/   {
/*N*/       fPercentDiag = 0.0;
/*N*/   }
/*N*/
/*N*/   if(fPercentDiag == 0.0)
/*N*/   {
/*N*/       // Ohne Schraegen, Vorderseite
/*N*/       if(bCreateFront)
/*N*/       {
/*N*/           PolyPolygon3D aNormalsFront;
/*N*/           AddFrontNormals(rFront, aNormalsFront, aOffset);
/*N*/
/*N*/           if(!bSmoothFrontBack)
/*N*/               CreateFront(rFront, aNormalsFront, bCreateNormals, bCreateTexture);
/*N*/           if(bSmoothLeft)
/*N*/               AddFrontNormals(rFront, aNormalsLeft, aOffset);
/*N*/           if(bSmoothFrontBack)
/*?*/               CreateFront(rFront, aNormalsLeft, bCreateNormals, bCreateTexture);
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           if(pPrev)
/*N*/               AddInBetweenNormals(*pPrev, rFront, aNormalsLeft, bSmoothLeft);
/*N*/       }
/*N*/
/*N*/       // Ohne Schraegen, Rueckseite
/*N*/       if(bCreateBack)
/*N*/       {
/*N*/           PolyPolygon3D aNormalsBack;
/*N*/           AddBackNormals(rBack, aNormalsBack, aOffset);
/*N*/
/*N*/           if(!bSmoothFrontBack)
/*N*/               CreateBack(rBack, aNormalsBack, bCreateNormals, bCreateTexture);
/*N*/           if(bSmoothRight)
/*N*/               AddBackNormals(rBack, aNormalsRight, aOffset);
/*N*/           if(bSmoothFrontBack)
/*?*/               CreateBack(rBack, aNormalsRight, bCreateNormals, bCreateTexture);
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           if(pNext)
/*N*/               AddInBetweenNormals(rBack, *pNext, aNormalsRight, bSmoothRight);
/*N*/       }
/*N*/
/*N*/       // eigentliches Zwischenstueck
/*N*/       CreateInBetween(rFront, rBack,
/*N*/           aNormalsLeft, aNormalsRight,
/*N*/           bCreateNormals,
/*N*/           fSurroundFactor,
/*N*/           fTextureStart,
/*N*/           fTextureDepth,
/*N*/           bRotateTexture90);
/*N*/
/*N*/       // #78972#
/*N*/       if(pLineGeometry)
/*N*/       {
/*N*/           pLineGeometry->Insert(rFront);
/*N*/           if(bCreateBack)
/*N*/               pLineGeometry->Insert(rBack);
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       // Mit Scraegen, Vorderseite
/*N*/       PolyPolygon3D aLocalFront = rFront;
/*N*/       PolyPolygon3D aLocalBack = rBack;
/*N*/       double fExtrudeDepth, fDiagLen;
/*N*/       double fTexMidStart = fTextureStart;
/*N*/       double fTexMidDepth = fTextureDepth;
/*N*/
/*N*/       if(bCreateFront || bCreateBack)
/*N*/       {
/*N*/           fExtrudeDepth = aOffset.GetLength();
/*N*/           fDiagLen = fPercentDiag * fExtrudeDepth;
/*N*/       }
/*N*/
/*N*/       PolyPolygon3D aOuterFront;
/*N*/       PolyPolygon3D aOuterBack;
/*N*/
/*N*/       if(bCreateFront)
/*N*/       {
/*N*/           PolyPolygon3D aNormalsOuterFront;
/*N*/           AddFrontNormals(aLocalFront, aNormalsOuterFront, aOffset);
/*N*/
/*N*/           if(bCharacterExtrude)
/*N*/           {
/*N*/               // Polygon kopieren
/*N*/               aOuterFront = aLocalFront;
/*N*/
/*N*/               // notwendige Normalen erzeugen
/*N*/               PolyPolygon3D aGrowDirection;
/*N*/               AddInBetweenNormals(aLocalFront, aLocalBack, aGrowDirection, bSmoothLeft);
/*N*/
/*N*/               // Groesse inneres Polygon merken
/*N*/               Volume3D aOldSize(aLocalFront.GetPolySize());
/*N*/
/*N*/               // Inneres Polygon vergroessern
/*N*/               GrowPoly(aLocalFront, aGrowDirection, fDiagLen);
/*N*/
/*N*/               // Inneres Polygon nach innen verschieben
/*N*/               //GrowPoly(aLocalFront, aNormalsOuterFront, -fDiagLen);
/*N*/
/*N*/               // Neue Groesse inneres Polygon feststellen
/*N*/               Volume3D aNewSize(aLocalFront.GetPolySize());
/*N*/
/*N*/               // Skalierung feststellen (nur X,Y)
/*N*/               Vector3D aScaleVec(
/*N*/                   (aNewSize.GetWidth() != 0.0) ? aOldSize.GetWidth() / aNewSize.GetWidth() : 1.0,
/*N*/                   (aNewSize.GetHeight() != 0.0) ? aOldSize.GetHeight() / aNewSize.GetHeight() : 1.0,
/*N*/                   (aNewSize.GetDepth() != 0.0) ? aOldSize.GetDepth() / aNewSize.GetDepth() : 1.0);
/*N*/
/*N*/               // Transformation bilden
/*N*/               Matrix4D aTransMat;
/*N*/               aTransMat.Scale(aScaleVec);
/*N*/
/*N*/               // aeusseres und inneres Polygon skalieren
/*N*/               aLocalFront.Transform(aTransMat);
/*N*/               aOuterFront.Transform(aTransMat);
/*N*/
/*N*/               // Neue Groesse aktualisieren
/*N*/               aNewSize = aLocalFront.GetPolySize();
/*N*/
/*N*/               // Translation feststellen
/*N*/               Vector3D aTransVec(
/*N*/                   aOldSize.MinVec().X() - aNewSize.MinVec().X(),
/*N*/                   aOldSize.MinVec().Y() - aNewSize.MinVec().Y(),
/*N*/                   aOldSize.MinVec().Z() - aNewSize.MinVec().Z());
/*N*/
/*N*/               // Transformation bilden
/*N*/               aTransMat.Identity();
/*N*/               aTransMat.Translate(aTransVec);
/*N*/
/*N*/               // aeusseres und inneres Polygon skalieren
/*N*/               aLocalFront.Transform(aTransMat);
/*N*/               aOuterFront.Transform(aTransMat);
/*N*/
/*N*/               // move aLocalFront again, scale and translate has moved it back
/*N*/               GrowPoly(aLocalFront, aNormalsOuterFront, -fDiagLen);
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               // Polygon kopieren
/*N*/               aOuterFront = aLocalFront;
/*N*/
/*N*/               // notwendige Normalen erzeugen
/*N*/               PolyPolygon3D aGrowDirection;
/*N*/               AddInBetweenNormals(aLocalFront, aLocalBack, aGrowDirection, bSmoothLeft);
/*N*/
/*N*/               // Aeusseres Polygon verkleinern
/*N*/               GrowPoly(aOuterFront, aGrowDirection, -fDiagLen);
/*N*/               aOuterFront.CorrectGrownPoly(aLocalFront);
/*N*/
/*N*/               // Inneres Polygon nach innen verschieben
/*N*/               GrowPoly(aLocalFront, aNormalsOuterFront, -fDiagLen);
/*N*/           }
/*N*/
/*N*/           // eventuell noch glaetten
/*N*/           if(bSmoothLeft)
/*N*/           {
/*N*/               if(bSmoothFrontBack)
/*?*/                   AddInBetweenNormals(aOuterFront, aLocalFront, aNormalsOuterFront, bSmoothLeft);
/*N*/               AddInBetweenNormals(aOuterFront, aLocalFront, aNormalsLeft, bSmoothLeft);
/*N*/           }
/*N*/
/*N*/           // vordere Zwischenstuecke erzeugen
/*N*/           CreateInBetween(aOuterFront, aLocalFront,
/*N*/               aNormalsOuterFront, aNormalsLeft,
/*N*/               bCreateNormals,
/*N*/               fSurroundFactor,
/*N*/               fTextureStart,
/*N*/               fTextureDepth * fPercentDiag,
/*N*/               bRotateTexture90);
/*N*/
/*N*/           // Vorderseite erzeugen
/*N*/           CreateFront(aOuterFront, aNormalsOuterFront, bCreateNormals, bCreateTexture);
/*N*/
/*N*/           // Weitere Texturwerte setzen
/*N*/           fTexMidStart += fTextureDepth * fPercentDiag;
/*N*/           fTexMidDepth -= fTextureDepth * fPercentDiag;
/*N*/       }
/*N*/       else
/*N*/       {
/*?*/           if(pPrev)
/*?*/               AddInBetweenNormals(*pPrev, rFront, aNormalsLeft, bSmoothLeft);
/*N*/       }
/*N*/
/*N*/       // Mit Scraegen, Rueckseite
/*N*/       if(bCreateBack)
/*N*/       {
/*N*/           PolyPolygon3D aNormalsOuterBack;
/*N*/           AddBackNormals(aLocalBack, aNormalsOuterBack, aOffset);
/*N*/
/*N*/           if(bCharacterExtrude)
/*N*/           {
/*N*/               // Polygon kopieren
/*N*/               aOuterBack = aLocalBack;
/*N*/
/*N*/               // notwendige Normalen erzeugen
/*N*/               PolyPolygon3D aGrowDirection;
/*N*/               AddInBetweenNormals(aLocalFront, aLocalBack, aGrowDirection, bSmoothRight);
/*N*/
/*N*/               // Groesse inneres Polygon merken
/*N*/               Volume3D aOldSize(aLocalBack.GetPolySize());
/*N*/
/*N*/               // Inneres Polygon vergroessern
/*N*/               GrowPoly(aLocalBack, aGrowDirection, fDiagLen);
/*N*/
/*N*/               // Inneres Polygon nach innen verschieben
/*N*/               //GrowPoly(aLocalBack, aNormalsOuterBack, -fDiagLen);
/*N*/
/*N*/               // Neue Groesse inneres Polygon feststellen
/*N*/               Volume3D aNewSize(aLocalBack.GetPolySize());
/*N*/
/*N*/               // Skalierung feststellen (nur X,Y)
/*N*/               Vector3D aScaleVec(
/*N*/                   (aNewSize.GetWidth() != 0.0) ? aOldSize.GetWidth() / aNewSize.GetWidth() : 1.0,
/*N*/                   (aNewSize.GetHeight() != 0.0) ? aOldSize.GetHeight() / aNewSize.GetHeight() : 1.0,
/*N*/                   (aNewSize.GetDepth() != 0.0) ? aOldSize.GetDepth() / aNewSize.GetDepth() : 1.0);
/*N*/
/*N*/               // Transformation bilden
/*N*/               Matrix4D aTransMat;
/*N*/               aTransMat.Scale(aScaleVec);
/*N*/
/*N*/               // aeusseres und inneres Polygon skalieren
/*N*/               aLocalBack.Transform(aTransMat);
/*N*/               aOuterBack.Transform(aTransMat);
/*N*/
/*N*/               // Neue Groesse aktualisieren
/*N*/               aNewSize = aLocalBack.GetPolySize();
/*N*/
/*N*/               // Translation feststellen
/*N*/               Vector3D aTransVec(
/*N*/                   aOldSize.MinVec().X() - aNewSize.MinVec().X(),
/*N*/                   aOldSize.MinVec().Y() - aNewSize.MinVec().Y(),
/*N*/                   aOldSize.MinVec().Z() - aNewSize.MinVec().Z());
/*N*/
/*N*/               // Transformation bilden
/*N*/               aTransMat.Identity();
/*N*/               aTransMat.Translate(aTransVec);
/*N*/
/*N*/               // aeusseres und inneres Polygon skalieren
/*N*/               aLocalBack.Transform(aTransMat);
/*N*/               aOuterBack.Transform(aTransMat);
/*N*/
/*N*/               // move aLocalBack again, scale and translate has moved it back
/*N*/               GrowPoly(aLocalBack, aNormalsOuterBack, -fDiagLen);
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               // Polygon kopieren
/*N*/               aOuterBack = aLocalBack;
/*N*/
/*N*/               // notwendige Normalen erzeugen
/*N*/               PolyPolygon3D aGrowDirection;
/*N*/               AddInBetweenNormals(aLocalFront, aLocalBack, aGrowDirection, bSmoothRight);
/*N*/
/*N*/               // Aeusseres Polygon verkleinern
/*N*/               GrowPoly(aOuterBack, aGrowDirection, -fDiagLen);
/*N*/               aOuterBack.CorrectGrownPoly(aLocalBack);
/*N*/
/*N*/               // Inneres Polygon nach innen verschieben
/*N*/               GrowPoly(aLocalBack, aNormalsOuterBack, -fDiagLen);
/*N*/           }
/*N*/
/*N*/           // eventuell noch glaetten
/*N*/           if(bSmoothRight)
/*N*/           {
/*N*/               if(bSmoothFrontBack)
/*?*/                   AddInBetweenNormals(aLocalBack, aOuterBack, aNormalsOuterBack, bSmoothRight);
/*N*/               AddInBetweenNormals(aLocalBack, aOuterBack, aNormalsRight, bSmoothRight);
/*N*/           }
/*N*/
/*N*/           // vordere Zwischenstuecke erzeugen
/*N*/           // hintere Zwischenstuecke erzeugen
/*N*/           CreateInBetween(aLocalBack, aOuterBack,
/*N*/               aNormalsRight, aNormalsOuterBack,
/*N*/               bCreateNormals,
/*N*/               fSurroundFactor,
/*N*/               fTextureStart + (fTextureDepth * (1.0 - fPercentDiag)),
/*N*/               fTextureDepth * fPercentDiag,
/*N*/               bRotateTexture90);
/*N*/
/*N*/           // Rueckseite erzeugen
/*N*/           CreateBack(aOuterBack, aNormalsOuterBack, bCreateNormals, bCreateTexture);
/*N*/
/*N*/           // Weitere Texturwerte setzen
/*N*/           fTexMidDepth -= fTextureDepth * fPercentDiag;
/*N*/       }
/*N*/       else
/*N*/       {
/*?*/           if(pNext)
/*?*/               AddInBetweenNormals(rBack, *pNext, aNormalsRight, bSmoothRight);
/*?*/       }
/*N*/
/*N*/       // eigentliches Zwischenstueck
/*N*/       CreateInBetween(aLocalFront, aLocalBack,
/*N*/           aNormalsLeft, aNormalsRight,
/*N*/           bCreateNormals,
/*N*/           fSurroundFactor,
/*N*/           fTexMidStart,
/*N*/           fTexMidDepth,
/*N*/           bRotateTexture90);
/*N*/
/*N*/       // #78972#
/*N*/       if(pLineGeometry)
/*N*/       {
/*N*/           if(bCreateFront)
/*N*/               pLineGeometry->Insert(aOuterFront);
/*N*/           pLineGeometry->Insert(aLocalFront);
/*N*/           if(bCreateBack)
/*N*/           {
/*N*/               pLineGeometry->Insert(aLocalBack);
/*N*/               pLineGeometry->Insert(aOuterBack);
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Parameter Geometrieerzeugung setzen
|*
\************************************************************************/

//STRIP001 void E3dCompoundObject::SetCreateNormals(BOOL bNew)
//STRIP001 {
//STRIP001  if(bCreateNormals != bNew)
//STRIP001  {
//STRIP001      bCreateNormals = bNew;
//STRIP001      bGeometryValid = FALSE;
//STRIP001  }
//STRIP001 }

//STRIP001 void E3dCompoundObject::SetCreateTexture(BOOL bNew)
//STRIP001 {
//STRIP001  if(bCreateTexture != bNew)
//STRIP001  {
//STRIP001      bCreateTexture = bNew;
//STRIP001      bGeometryValid = FALSE;
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* DisplayGeometry rausruecken
|*
\************************************************************************/

/*N*/ B3dGeometry& E3dCompoundObject::GetDisplayGeometry()
/*N*/ {
/*N*/   // Geometrie herstellen
/*N*/   if(!bGeometryValid)
/*?*/       ReCreateGeometry();
/*N*/
/*N*/   return aDisplayGeometry;
/*N*/ }

/*************************************************************************
|*
|* Material des Objektes
|*
\************************************************************************/

/*N*/ void E3dCompoundObject::SetMaterialAmbientColor(const Color& rColor)
/*N*/ {
/*N*/   if(aMaterialAmbientColor != rColor)
/*N*/   {
/*?*/       aMaterialAmbientColor = rColor;
/*N*/   }
/*N*/ }

//STRIP001 void E3dCompoundObject::SetBackMaterial(const B3dMaterial& rNew)
//STRIP001 {
//STRIP001  if(aBackMaterial != rNew)
//STRIP001  {
//STRIP001      aBackMaterial = rNew;
//STRIP001  }
//STRIP001 }

//STRIP001 void E3dCompoundObject::SetUseDifferentBackMaterial(BOOL bNew)
//STRIP001 {
//STRIP001  if(bUseDifferentBackMaterial != bNew)
//STRIP001  {
//STRIP001      bUseDifferentBackMaterial = bNew;
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* 3D Ausgabe
|*
\************************************************************************/

//STRIP001 void E3dCompoundObject::Paint3D(ExtOutputDevice& rOut, Base3D* pBase3D,
//STRIP001  const SdrPaintInfoRec& rInfoRec, UINT16 nDrawFlags)
//STRIP001 {
//STRIP001  // call parent, draw all subobjects
//STRIP001  E3dObject::Paint3D(rOut, pBase3D, rInfoRec, nDrawFlags);
//STRIP001
//STRIP001  // Feststellen, ob das Objekt dargestellt werden muss, was die Layer angeht
//STRIP001  BOOL bPrinter = (pBase3D->GetOutputDevice()->GetOutDevType()==OUTDEV_PRINTER);
//STRIP001  const SetOfByte* pVisiLayer=&rInfoRec.aPaintLayer;
//STRIP001  E3dScene* pScene = GetScene();
//STRIP001  BOOL bOnlySelectedCriteria = (pScene && (!pScene->DoDrawOnlySelected() || GetSelected()));
//STRIP001
//STRIP001  if((!bPrinter || IsPrintable()) && pVisiLayer->IsSet(GetLayer()) && bOnlySelectedCriteria)
//STRIP001  {
//STRIP001      // Ausgabeparameter setzen
//STRIP001      BOOL bDrawOutline;
//STRIP001      BOOL bDrawObject;
//STRIP001      BOOL bIsLineDraft((rInfoRec.nPaintMode & SDRPAINTMODE_DRAFTLINE) != 0);
//STRIP001      BOOL bIsFillDraft((rInfoRec.nPaintMode & SDRPAINTMODE_DRAFTFILL) != 0);
//STRIP001      SetBase3DParams(rOut, pBase3D, bDrawObject, bDrawOutline, nDrawFlags,
//STRIP001          (rInfoRec.pPV && rInfoRec.pPV->GetView().DoVisualizeEnteredGroup()) ? rInfoRec.bNotActive : FALSE,
//STRIP001          bIsLineDraft, bIsFillDraft);
//STRIP001
//STRIP001      // Culling?
//STRIP001      pBase3D->SetCullMode(GetDoubleSided() ? Base3DCullNone : Base3DCullBack);
//STRIP001
//STRIP001      // Objekt flat darstellen?
//STRIP001      BOOL bForceFlat = ((GetNormalsKind() > 0) && !(GetNormalsKind() > 1));
//STRIP001      pBase3D->SetForceFlat(bForceFlat);
//STRIP001
//STRIP001      // Geometrie ausgeben
//STRIP001      if(bDrawObject)
//STRIP001      {
//STRIP001          // #92030# for E3dPolygonObj, take flag at created DisplayGeometry into account
//STRIP001          // which may not allow this object to be drawn filled
//STRIP001          if(!GetDisplayGeometry().IsOutline())
//STRIP001          {
//STRIP001              pBase3D->DrawPolygonGeometry(GetDisplayGeometry());
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // Outline ausgeben
//STRIP001      if(bDrawOutline && pBase3D->GetLightGroup())
//STRIP001      {
//STRIP001          BOOL bLightingWasEnabled = pBase3D->GetLightGroup()->IsLightingEnabled();
//STRIP001          pBase3D->GetLightGroup()->EnableLighting(FALSE);
//STRIP001          pBase3D->SetLightGroup(pBase3D->GetLightGroup());
//STRIP001
//STRIP001          // #79585#
//STRIP001          pBase3D->SetActiveTexture();
//STRIP001
//STRIP001          // #78972#
//STRIP001          // detect if lines need to be drawn specifically
//STRIP001          const SfxItemSet& rSet = GetItemSet();
//STRIP001          sal_Int32 nLineWidth = ((const XLineWidthItem&)(rSet.Get(XATTR_LINEWIDTH))).GetValue();
//STRIP001          XLineStyle aLineStyle = ((const XLineStyleItem&)(rSet.Get(XATTR_LINESTYLE))).GetValue();
//STRIP001          BOOL bDrawLineSolidHair = (aLineStyle == XLINE_SOLID && nLineWidth == 0);
//STRIP001
//STRIP001          // get line geometry
//STRIP001          PolyPolygon3D aLinePolyPolygon;
//STRIP001          GetLineGeometry(aLinePolyPolygon);
//STRIP001
//STRIP001          if(bDrawLineSolidHair)
//STRIP001          {
//STRIP001              // simply draw the object geometry as line (as done before)
//STRIP001              // pBase3D->DrawPolygonGeometry(GetDisplayGeometry(), TRUE);
//STRIP001              if(aLinePolyPolygon.Count())
//STRIP001              {
//STRIP001                  // draw the line geometry as 3d lines
//STRIP001                  pBase3D->SetRenderMode(Base3DRenderLine);
//STRIP001                  pBase3D->SetPolygonOffset(Base3DPolygonOffsetLine, TRUE);
//STRIP001
//STRIP001                  for(sal_uInt32 a(0); a < aLinePolyPolygon.Count(); a++)
//STRIP001                  {
//STRIP001                      // start new primitive
//STRIP001                      const Polygon3D& rPolygon = aLinePolyPolygon[(sal_uInt16)a];
//STRIP001                      pBase3D->StartPrimitive(Base3DLineStrip);
//STRIP001
//STRIP001                      for(sal_uInt32 b(0); b < rPolygon.GetPointCount(); b++)
//STRIP001                      {
//STRIP001                          Vector3D aVec = rPolygon[sal_uInt16(b)];
//STRIP001                          pBase3D->AddVertex(aVec);
//STRIP001                      }
//STRIP001
//STRIP001                      // draw primitive
//STRIP001                      pBase3D->EndPrimitive();
//STRIP001                  }
//STRIP001
//STRIP001                  pBase3D->SetPolygonOffset(Base3DPolygonOffsetLine, FALSE);
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              // convert object geometry to line geometry and draw as polygons
//STRIP001              // in 3D space
//STRIP001              PolyPolygon3D aPolyPoly3D;
//STRIP001              PolyPolygon3D aLinePoly3D;
//STRIP001
//STRIP001              // get ImpLineStyleParameterPack
//STRIP001              ImpLineStyleParameterPack aLineAttr(rSet, FALSE, rOut.GetOutDev());
//STRIP001              aLineAttr.ForceNoArrowsLeft(TRUE);
//STRIP001              aLineAttr.ForceNoArrowsRight(TRUE);
//STRIP001              ImpLineGeometryCreator aLineCreator(aLineAttr, aPolyPoly3D, aLinePoly3D, FALSE);
//STRIP001
//STRIP001              // get camera set
//STRIP001              B3dTransformationSet* pTransSet = pBase3D->GetTransformationSet();
//STRIP001
//STRIP001              // get transform object geometry in eye coor
//STRIP001              Matrix4D aMatObjectToEye = pTransSet->GetObjectTrans();
//STRIP001              aMatObjectToEye *= pTransSet->GetOrientation();
//STRIP001
//STRIP001              for(sal_uInt16 nInd(0); nInd < aLinePolyPolygon.Count(); nInd++)
//STRIP001              {
//STRIP001                  // create line geometry for polygon in eye coor to
//STRIP001                  // have it always orthogonal to camera plane
//STRIP001                  Polygon3D aLinePoly = aLinePolyPolygon.GetObject(nInd);
//STRIP001                  aLinePoly.Transform(aMatObjectToEye);
//STRIP001                  aLineCreator.AddPolygon3D(aLinePoly);
//STRIP001              }
//STRIP001
//STRIP001              // put together
//STRIP001              aLinePoly3D.Insert(aPolyPoly3D);
//STRIP001
//STRIP001              if(aLinePoly3D.Count())
//STRIP001              {
//STRIP001                  pBase3D->SetCullMode(Base3DCullNone);
//STRIP001                  for(sal_uInt32 a(0); a < aLinePoly3D.Count(); a++)
//STRIP001                  {
//STRIP001                      // start new primitive
//STRIP001                      const Polygon3D& rPolygon = aLinePoly3D[(sal_uInt16)a];
//STRIP001
//STRIP001                      if(rPolygon.IsClosed())
//STRIP001                      {
//STRIP001                          pBase3D->SetRenderMode(Base3DRenderFill);
//STRIP001                          pBase3D->StartPrimitive(Base3DPolygon);
//STRIP001                      }
//STRIP001                      else
//STRIP001                      {
//STRIP001                          pBase3D->SetRenderMode(Base3DRenderLine);
//STRIP001                          pBase3D->SetPolygonOffset(Base3DPolygonOffsetLine, TRUE);
//STRIP001                          pBase3D->StartPrimitive(Base3DLineStrip);
//STRIP001                      }
//STRIP001
//STRIP001                      for(sal_uInt32 b(0); b < rPolygon.GetPointCount(); b++)
//STRIP001                      {
//STRIP001                          Vector3D aVec = rPolygon[sal_uInt16(b)];
//STRIP001                          aVec = pTransSet->EyeToObjectCoor(aVec);
//STRIP001                          pBase3D->AddVertex(aVec);
//STRIP001                      }
//STRIP001
//STRIP001                      // draw primitive
//STRIP001                      pBase3D->EndPrimitive();
//STRIP001
//STRIP001                      if(!rPolygon.IsClosed())
//STRIP001                      {
//STRIP001                          pBase3D->SetPolygonOffset(Base3DPolygonOffsetLine, FALSE);
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          pBase3D->GetLightGroup()->EnableLighting(bLightingWasEnabled);
//STRIP001          pBase3D->SetLightGroup(pBase3D->GetLightGroup());
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001 #ifdef DBG_UTIL      // SnapRect und BoundRect zum testen zeichnen
//STRIP001  static BOOL bDoDrawSnapBoundToMakeThemVisible = FALSE;
//STRIP001  if(bDoDrawSnapBoundToMakeThemVisible)
//STRIP001  {
//STRIP001      OutputDevice* pOut = rOut.GetOutDev();
//STRIP001
//STRIP001      // SnapRect in Rot
//STRIP001      Rectangle aTempRect = GetSnapRect();
//STRIP001      pOut->SetLineColor(Color(COL_RED));
//STRIP001      pOut->SetFillColor();
//STRIP001      pOut->DrawRect(aTempRect);
//STRIP001
//STRIP001      // BoundRect in Gruen
//STRIP001      aTempRect = GetBoundRect();
//STRIP001      pOut->SetLineColor(Color(COL_GREEN));
//STRIP001      pOut->SetFillColor();
//STRIP001      pOut->DrawRect(aTempRect);
//STRIP001  }
//STRIP001 #endif
//STRIP001 }

/*************************************************************************
|*
|* Objekt als Kontur in das Polygon einfuegen
|*
\************************************************************************/

//STRIP001 void E3dCompoundObject::TakeContour3D(XPolyPolygon& rPoly)
//STRIP001 {
//STRIP001  // call parent
//STRIP001  E3dObject::TakeContour3D(rPoly);
//STRIP001
//STRIP001  // Kontur dieses Objektes liefern
//STRIP001  UINT32 nPolyCounter = 0;
//STRIP001  UINT32 nEntityCounter = 0;
//STRIP001  UINT32 nUpperBound;
//STRIP001  B3dEntityBucket& rEntityBucket = GetDisplayGeometry().GetEntityBucket();
//STRIP001  GeometryIndexValueBucket& rIndexBucket = GetDisplayGeometry().GetIndexBucket();
//STRIP001  B3dTransformationSet& rTransSet = GetScene()->GetCameraSet();
//STRIP001  Vector3D aPoint;
//STRIP001  Point aNewPoint;
//STRIP001
//STRIP001  // ObjectTrans setzen
//STRIP001  Matrix4D mTransform = GetFullTransform();
//STRIP001  rTransSet.SetObjectTrans(mTransform);
//STRIP001
//STRIP001  while(nPolyCounter < rIndexBucket.Count())
//STRIP001  {
//STRIP001      // Naechstes Primitiv
//STRIP001      nUpperBound = rIndexBucket[nPolyCounter++].GetIndex();
//STRIP001      XPolygon aNewPart(UINT16(nUpperBound - nEntityCounter));
//STRIP001      UINT16 nIndex = 0;
//STRIP001
//STRIP001      while(nEntityCounter < nUpperBound)
//STRIP001      {
//STRIP001          aPoint = rTransSet.ObjectToViewCoor(rEntityBucket[nEntityCounter++].Point().GetVector3D());
//STRIP001          aNewPart[nIndex  ].X() = (long)(aPoint.X() + 0.5);
//STRIP001          aNewPart[nIndex++].Y() = (long)(aPoint.Y() + 0.5);
//STRIP001      }
//STRIP001
//STRIP001      // Teilprimitiv einfuegen
//STRIP001      rPoly.Insert(aNewPart);
//STRIP001  }
//STRIP001
//STRIP001  // add shadow now too (#61279#)
//STRIP001  PolyPolygon3D aShadowPolyPoly;
//STRIP001  ImpGetShadowPolygon(aShadowPolyPoly);
//STRIP001
//STRIP001  // invert Y coor cause of GetPolygon() later
//STRIP001  Matrix4D aTransMat;
//STRIP001  aTransMat.Scale(1.0, -1.0, 1.0);
//STRIP001  aShadowPolyPoly.Transform(aTransMat);
//STRIP001
//STRIP001  for(UINT16 a = 0; a < aShadowPolyPoly.Count(); a++)
//STRIP001  {
//STRIP001      XPolygon aNewPart(aShadowPolyPoly[a].GetPolygon());
//STRIP001      rPoly.Insert(aNewPart);
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Schatten fuer 3D-Objekte zeichnen
|*
\************************************************************************/

//STRIP001 void E3dCompoundObject::DrawShadows(Base3D *pBase3D, ExtOutputDevice& rXOut,
//STRIP001  const Rectangle& rBound, const Volume3D& rVolume,
//STRIP001  const SdrPaintInfoRec& rInfoRec)
//STRIP001 {
//STRIP001  // call parent
//STRIP001  E3dObject::DrawShadows(pBase3D, rXOut, rBound, rVolume, rInfoRec);
//STRIP001
//STRIP001  // Schatten fuer dieses Objekt zeichnen
//STRIP001  // Feststellen, ob das Objekt dargestellt werden muss, was die Layer angeht
//STRIP001  BOOL bPrinter = (pBase3D->GetOutputDevice()->GetOutDevType()==OUTDEV_PRINTER);
//STRIP001  const SetOfByte* pVisiLayer=&rInfoRec.aPaintLayer;
//STRIP001  if(DoDrawShadow()
//STRIP001      && (!bPrinter || IsPrintable())
//STRIP001      && pVisiLayer->IsSet(GetLayer()))
//STRIP001  {
//STRIP001      // ObjectTrans setzen
//STRIP001      Matrix4D mTransform = GetFullTransform();
//STRIP001      GetScene()->GetCameraSet().SetObjectTrans(mTransform);
//STRIP001
//STRIP001      // Schattenpolygon holen
//STRIP001      PolyPolygon3D aShadowPoly;
//STRIP001      ImpGetShadowPolygon(aShadowPoly);
//STRIP001
//STRIP001      // invert Y coor cause of GetPolyPolygon() in ImpDrawShadowPolygon() later
//STRIP001      Matrix4D aTransMat;
//STRIP001      aTransMat.Scale(1.0, -1.0, 1.0);
//STRIP001      aShadowPoly.Transform(aTransMat);
//STRIP001
//STRIP001      // ...und Zeichnen
//STRIP001      ImpDrawShadowPolygon(aShadowPoly, rXOut);
//STRIP001  }
//STRIP001 }

//STRIP001 void E3dCompoundObject::ImpGetShadowPolygon(PolyPolygon3D& rPoly)
//STRIP001 {
//STRIP001  // #79585#
//STRIP001  sal_Int32 nXDist(GetShadowXDistance());
//STRIP001  sal_Int32 nYDist(GetShadowYDistance());
//STRIP001  BOOL bDrawAsOutline(DrawShadowAsOutline());
//STRIP001  PolyPolygon3D aLinePolyPolygon;
//STRIP001  B3dTransformationSet& rTransSet = GetScene()->GetCameraSet();
//STRIP001  const SfxItemSet& rSet = GetItemSet();
//STRIP001  XLineStyle aLineStyle = ((const XLineStyleItem&)(rSet.Get(XATTR_LINESTYLE))).GetValue();
//STRIP001  sal_Int32 nLineWidth = ((const XLineWidthItem&)(rSet.Get(XATTR_LINEWIDTH))).GetValue();
//STRIP001
//STRIP001  if(!bDrawAsOutline)
//STRIP001  {
//STRIP001      // add basic polygon geometry, generate from 3D bucket
//STRIP001      B3dEntityBucket& rEntityBucket = ((E3dCompoundObject*)this)->GetDisplayGeometry().GetEntityBucket();
//STRIP001      GeometryIndexValueBucket& rIndexBucket = ((E3dCompoundObject*)this)->GetDisplayGeometry().GetIndexBucket();
//STRIP001      sal_uInt32 nPolyCounter(0);
//STRIP001      sal_uInt32 nEntityCounter(0);
//STRIP001
//STRIP001      while(nPolyCounter < rIndexBucket.Count())
//STRIP001      {
//STRIP001          // next primitive
//STRIP001          sal_uInt32 nUpperBound(rIndexBucket[nPolyCounter++].GetIndex());
//STRIP001          Polygon3D aNewPolygon((sal_uInt16)(nUpperBound - nEntityCounter));
//STRIP001          sal_uInt16 nIndex(0);
//STRIP001
//STRIP001          while(nEntityCounter < nUpperBound)
//STRIP001              aNewPolygon[nIndex++] = rEntityBucket[nEntityCounter++].Point().GetVector3D();
//STRIP001
//STRIP001          aNewPolygon.SetClosed(TRUE);
//STRIP001          aLinePolyPolygon.Insert(aNewPolygon);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if(bDrawAsOutline || (nLineWidth != 0))
//STRIP001  {
//STRIP001      // add 3D line drawing geometry
//STRIP001      PolyPolygon3D aBasicLinePolyPoly;
//STRIP001      GetLineGeometry(aBasicLinePolyPoly);
//STRIP001
//STRIP001      // #78972# detect if lines need to be drawn with pattern
//STRIP001      if(aLineStyle == XLINE_DASH || (aLineStyle == XLINE_SOLID && nLineWidth != 0))
//STRIP001      {
//STRIP001          PolyPolygon3D aPolyPoly3D;
//STRIP001          PolyPolygon3D aLinePoly3D;
//STRIP001
//STRIP001          // get ImpLineStyleParameterPack, bForceHair==FALSE to create polygons
//STRIP001          ImpLineStyleParameterPack aLineAttr(rSet, FALSE, NULL);
//STRIP001          aLineAttr.ForceNoArrowsLeft(TRUE);
//STRIP001          aLineAttr.ForceNoArrowsRight(TRUE);
//STRIP001          ImpLineGeometryCreator aLineCreator(aLineAttr, aPolyPoly3D, aLinePoly3D, FALSE);
//STRIP001
//STRIP001          // get camera set and transform to eye coor
//STRIP001          Matrix4D aMatObjectToEye = rTransSet.GetObjectTrans();
//STRIP001          aMatObjectToEye *= rTransSet.GetOrientation();
//STRIP001
//STRIP001          for(sal_uInt16 nInd(0); nInd < aBasicLinePolyPoly.Count(); nInd++)
//STRIP001          {
//STRIP001              Polygon3D aLinePoly = aBasicLinePolyPoly.GetObject(nInd);
//STRIP001              aLinePoly.Transform(aMatObjectToEye);
//STRIP001              aLineCreator.AddPolygon3D(aLinePoly);
//STRIP001          }
//STRIP001
//STRIP001          // prepare transform back to object coor
//STRIP001          if(aLinePoly3D.Count() || aPolyPoly3D.Count())
//STRIP001              aMatObjectToEye.Invert();
//STRIP001
//STRIP001          if(aLinePoly3D.Count())
//STRIP001          {
//STRIP001              // transform and add all generated line polygons
//STRIP001              aLinePoly3D.Transform(aMatObjectToEye);
//STRIP001              aLinePolyPolygon.Insert(aLinePoly3D);
//STRIP001          }
//STRIP001
//STRIP001          if(aPolyPoly3D.Count())
//STRIP001          {
//STRIP001              // transform and add all generated polygons
//STRIP001              aPolyPoly3D.Transform(aMatObjectToEye);
//STRIP001              aLinePolyPolygon.Insert(aPolyPoly3D);
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // simply add basic line geometry
//STRIP001          aLinePolyPolygon.Insert(aBasicLinePolyPoly);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if(aLinePolyPolygon.Count())
//STRIP001  {
//STRIP001      if(GetShadow3D())
//STRIP001      {
//STRIP001          // 3D Schatten. Nimm Lichtquelle und Ebene. Projiziere
//STRIP001          // die Punkte und jage sie durch die 3D Darstellung.
//STRIP001          Vector3D aLampPositionOrDirection;
//STRIP001          BOOL bDirectionalSource(TRUE);
//STRIP001          Vector3D aGroundPosition;
//STRIP001          Vector3D aGroundDirection;
//STRIP001          B3dLightGroup& rLightGroup = GetScene()->GetLightGroup();
//STRIP001
//STRIP001          // Lampe waehlen
//STRIP001          Base3DLightNumber aLightNumber = Base3DLight0;
//STRIP001          BOOL bLightNumberValid(FALSE);
//STRIP001
//STRIP001          while(!bLightNumberValid && aLightNumber <= Base3DLight7)
//STRIP001          {
//STRIP001              if(rLightGroup.IsEnabled(aLightNumber))
//STRIP001                  bLightNumberValid = TRUE;
//STRIP001              else
//STRIP001                  aLightNumber = (Base3DLightNumber)((UINT16)aLightNumber + 1);
//STRIP001          }
//STRIP001
//STRIP001          if(bLightNumberValid)
//STRIP001          {
//STRIP001              // Position oder Vektor aus der Lampe extrahieren
//STRIP001              if(rLightGroup.IsDirectionalSource(aLightNumber))
//STRIP001              {
//STRIP001                  // Nur Richtung vorhanden
//STRIP001                  aLampPositionOrDirection = -rLightGroup.GetDirection(aLightNumber);
//STRIP001                  aLampPositionOrDirection.Normalize();
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  // Nur Position vorhanden
//STRIP001                  aLampPositionOrDirection = rLightGroup.GetPosition(aLightNumber);
//STRIP001                  bDirectionalSource = FALSE;
//STRIP001              }
//STRIP001
//STRIP001              // Ebene holen, Richtung in Augkoordinaten
//STRIP001              aGroundDirection = -GetScene()->GetShadowPlaneDirection();
//STRIP001              aGroundDirection.Normalize();
//STRIP001
//STRIP001              // Ist die Lampe auch vor der Ebene?
//STRIP001              Vector3D aLightNormal = aLampPositionOrDirection;
//STRIP001              if(!bDirectionalSource)
//STRIP001              {
//STRIP001                  // Nur Position vorhanden, berechne einen Lichtvektor
//STRIP001                  aLightNormal = aLinePolyPolygon[0][0] - aLampPositionOrDirection;
//STRIP001                  aLightNormal.Normalize();
//STRIP001              }
//STRIP001
//STRIP001              double fLightAndNormal = aLightNormal.Scalar(aGroundDirection);
//STRIP001              B3dVolume aVolume = rTransSet.GetDeviceVolume();
//STRIP001
//STRIP001              // auf Augkoordinaten umstellen
//STRIP001              double fTemp = aVolume.MinVec().Z();
//STRIP001              aVolume.MinVec().Z() = -aVolume.MaxVec().Z();
//STRIP001              aVolume.MaxVec().Z() = -fTemp;
//STRIP001
//STRIP001              if(fLightAndNormal > 0.0)
//STRIP001              {
//STRIP001                  // Position der Ebene in Augkoordinaten setzen
//STRIP001                  aGroundPosition.X() = (aGroundDirection.X() < 0.0) ? aVolume.MinVec().X() : aVolume.MaxVec().X();
//STRIP001                  aGroundPosition.Y() = (aGroundDirection.Y() < 0.0) ? aVolume.MinVec().Y() : aVolume.MaxVec().Y();
//STRIP001                  aGroundPosition.Z() = aVolume.MinVec().Z() - ((aVolume.MaxVec().Z() - aVolume.MinVec().Z()) / 8.0);
//STRIP001
//STRIP001                  // Skalar der Ebenengleichung holen
//STRIP001                  double fGroundScalar = -aGroundPosition.Scalar(aGroundDirection);
//STRIP001
//STRIP001                  // ObjectTrans setzen
//STRIP001                  BOOL bPolygonVisible(TRUE);
//STRIP001                  Matrix4D mTransform = GetFullTransform();
//STRIP001                  rTransSet.SetObjectTrans(mTransform);
//STRIP001
//STRIP001                  for(sal_uInt16 a(0); a < aLinePolyPolygon.Count(); a++)
//STRIP001                  {
//STRIP001                      Polygon3D& rLinePoly = aLinePolyPolygon[a];
//STRIP001                      Polygon3D aPoly(rLinePoly.GetPointCount());
//STRIP001                      sal_uInt16 nPolyPos(0);
//STRIP001
//STRIP001                      for(sal_uInt16 b(0); b < rLinePoly.GetPointCount(); b++)
//STRIP001                      {
//STRIP001                          // Naechsten Punkt holen
//STRIP001                          Vector3D aPoint = rLinePoly[b];
//STRIP001
//STRIP001                          // Auf Augkoordinaten umrechnen
//STRIP001                          aPoint = rTransSet.ObjectToEyeCoor(aPoint);
//STRIP001
//STRIP001                          // Richtung bestimmen
//STRIP001                          Vector3D aDirection = aLampPositionOrDirection;
//STRIP001                          if(!bDirectionalSource)
//STRIP001                          {
//STRIP001                              aDirection = aPoint - aLampPositionOrDirection;
//STRIP001                              aDirection.Normalize();
//STRIP001                          }
//STRIP001
//STRIP001                          // Schnittpunkt berechnen (N.D)
//STRIP001                          double fDiv = aGroundDirection.Scalar(aDirection);
//STRIP001                          if(fabs(fDiv) < SMALL_DVALUE)
//STRIP001                          {
//STRIP001                              bPolygonVisible = FALSE;
//STRIP001                          }
//STRIP001                          else
//STRIP001                          {
//STRIP001                              fDiv = -((fGroundScalar + aGroundDirection.Scalar(aPoint)) / fDiv);
//STRIP001                              aPoint += aDirection * fDiv;
//STRIP001                          }
//STRIP001
//STRIP001                          // Punkt normal transformieren
//STRIP001                          if(bPolygonVisible)
//STRIP001                          {
//STRIP001                              // Auf ViewKoordinaten
//STRIP001                              Vector3D aShadowPoint = rTransSet.EyeToViewCoor(aPoint);
//STRIP001                              aPoly[nPolyPos++] = Vector3D(
//STRIP001                                  aShadowPoint.X() + (double)nXDist,
//STRIP001                                  aShadowPoint.Y() + (double)nYDist,
//STRIP001                                  0.0);
//STRIP001                          }
//STRIP001                      }
//STRIP001
//STRIP001                      // Teilpolygon einfuegen
//STRIP001                      if(nPolyPos)
//STRIP001                      {
//STRIP001                          aPoly.SetClosed(rLinePoly.IsClosed());
//STRIP001                          rPoly.Insert(aPoly);
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // ObjectTrans setzen
//STRIP001          Matrix4D mTransform = GetFullTransform();
//STRIP001          rTransSet.SetObjectTrans(mTransform);
//STRIP001
//STRIP001          for(sal_uInt16 a(0); a < aLinePolyPolygon.Count(); a++)
//STRIP001          {
//STRIP001              Polygon3D& rLinePoly = aLinePolyPolygon[a];
//STRIP001              Polygon3D aPoly(rLinePoly.GetPointCount());
//STRIP001              sal_uInt16 nPolyPos(0);
//STRIP001
//STRIP001              // Polygon fuellen
//STRIP001              for(sal_uInt16 b(0); b < rLinePoly.GetPointCount(); b++)
//STRIP001              {
//STRIP001                  // Naechsten Punkt holen
//STRIP001                  Vector3D aPoint = rLinePoly[b];
//STRIP001                  aPoint = rTransSet.ObjectToViewCoor(aPoint);
//STRIP001                  aPoly[nPolyPos++] = Vector3D(
//STRIP001                      aPoint.X() + (double)nXDist,
//STRIP001                      aPoint.Y() + (double)nYDist,
//STRIP001                      0.0);
//STRIP001              }
//STRIP001
//STRIP001              // open/close
//STRIP001              aPoly.SetClosed(rLinePoly.IsClosed());
//STRIP001
//STRIP001              // Teilpolygon einfuegen
//STRIP001              rPoly.Insert(aPoly);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void E3dCompoundObject::ImpDrawShadowPolygon(PolyPolygon3D& rPoly, ExtOutputDevice& rXOut)
//STRIP001 {
//STRIP001  Color aCol = GetShadowColor();
//STRIP001  OutputDevice *pDevice = rXOut.GetOutDev();
//STRIP001  BOOL bDrawAsOutline(DrawShadowAsOutline());
//STRIP001  UINT16 nTransparence = GetShadowTransparence();
//STRIP001
//STRIP001  if(nTransparence)
//STRIP001  {
//STRIP001      if(nTransparence != 100)
//STRIP001      {
//STRIP001          // transparence, draw to metafile and then transparent to
//STRIP001          // outdev
//STRIP001          UINT8 nScaledTrans((UINT8)((nTransparence * 255)/100));
//STRIP001          Color aTransColor(nScaledTrans, nScaledTrans, nScaledTrans);
//STRIP001          Gradient aGradient(GRADIENT_LINEAR, aTransColor, aTransColor);
//STRIP001          GDIMetaFile aMetaFile;
//STRIP001          VirtualDevice aVDev;
//STRIP001          MapMode aMap(rXOut.GetOutDev()->GetMapMode());
//STRIP001
//STRIP001          // StepCount to someting small
//STRIP001          aGradient.SetSteps(3);
//STRIP001
//STRIP001          // create BoundRectangle
//STRIP001          PolyPolygon aPolyPolygon(rPoly.GetPolyPolygon());
//STRIP001          Rectangle aBound(aPolyPolygon.GetBoundRect());
//STRIP001
//STRIP001          // prepare VDev and MetaFile
//STRIP001          aVDev.EnableOutput(FALSE);
//STRIP001          aVDev.SetMapMode(rXOut.GetOutDev()->GetMapMode());
//STRIP001          aMetaFile.Record(&aVDev);
//STRIP001
//STRIP001          aVDev.SetFont(rXOut.GetOutDev()->GetFont());
//STRIP001          aVDev.SetDrawMode(rXOut.GetOutDev()->GetDrawMode());
//STRIP001          aVDev.SetRefPoint(rXOut.GetOutDev()->GetRefPoint());
//STRIP001
//STRIP001          // create output
//STRIP001          for(UINT16 a(0); a < aPolyPolygon.Count(); a++)
//STRIP001          {
//STRIP001              if(rPoly[a].IsClosed())
//STRIP001              {
//STRIP001                  aVDev.SetLineColor();
//STRIP001                  aVDev.SetFillColor(aCol);
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  aVDev.SetLineColor(aCol);
//STRIP001                  aVDev.SetFillColor();
//STRIP001              }
//STRIP001
//STRIP001              aMetaFile.AddAction(new MetaPolygonAction(aPolyPolygon[a]));
//STRIP001          }
//STRIP001
//STRIP001          // draw metafile
//STRIP001          aMetaFile.Stop();
//STRIP001          aMetaFile.WindStart();
//STRIP001          aMap.SetOrigin(aBound.TopLeft());
//STRIP001          aMetaFile.SetPrefMapMode(aMap);
//STRIP001          aMetaFile.SetPrefSize(aBound.GetSize());
//STRIP001          rXOut.GetOutDev()->DrawTransparent(aMetaFile, aBound.TopLeft(), aBound.GetSize(), aGradient);
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001          // no transparence, draw all single polys directly
//STRIP001      for(UINT16 a(0); a < rPoly.Count(); a++)
//STRIP001      {
//STRIP001          if(rPoly[a].IsClosed())
//STRIP001          {
//STRIP001              pDevice->SetLineColor();
//STRIP001              pDevice->SetFillColor(aCol);
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              pDevice->SetLineColor(aCol);
//STRIP001              pDevice->SetFillColor();
//STRIP001          }
//STRIP001
//STRIP001          pDevice->DrawPolygon(rPoly[a].GetPolygon());
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* convert given PolyPolygon3D to screen coor
|*
\************************************************************************/

//STRIP001 XPolyPolygon E3dCompoundObject::TransformToScreenCoor(const PolyPolygon3D &rExtrudePoly)
//STRIP001 {
//STRIP001  XPolyPolygon aNewPolyPolygon;
//STRIP001  B3dTransformationSet& rTransSet = GetScene()->GetCameraSet();
//STRIP001
//STRIP001  // set ObjectTrans
//STRIP001  Matrix4D mTransform = GetFullTransform();
//STRIP001  rTransSet.SetObjectTrans(mTransform);
//STRIP001
//STRIP001  // transform base polygon to screen coor
//STRIP001  for(UINT16 a=0;a<rExtrudePoly.Count();a++)
//STRIP001  {
//STRIP001      const Polygon3D &rExtPoly = rExtrudePoly[a];
//STRIP001      BOOL bClosed = rExtPoly.IsClosed();
//STRIP001      XPolygon aNewPoly(rExtPoly.GetPointCount() + (bClosed ? 1 : 0));
//STRIP001
//STRIP001      UINT16 b;
//STRIP001      for(b=0;b<rExtPoly.GetPointCount();b++)
//STRIP001      {
//STRIP001          Vector3D aPoint = rTransSet.ObjectToViewCoor(rExtPoly[b]);
//STRIP001          aNewPoly[b].X() = (long)(aPoint.X() + 0.5);
//STRIP001          aNewPoly[b].Y() = (long)(aPoint.Y() + 0.5);
//STRIP001      }
//STRIP001
//STRIP001      if(bClosed)
//STRIP001          aNewPoly[b] = aNewPoly[0];
//STRIP001
//STRIP001      aNewPolyPolygon.Insert(aNewPoly);
//STRIP001  }
//STRIP001
//STRIP001  return aNewPolyPolygon;
//STRIP001 }

/*************************************************************************
|*
|* Attribute setzen
|*
\************************************************************************/

// private support routines for ItemSet access. NULL pointer means clear item.
/*N*/ void E3dCompoundObject::PostItemChange(const sal_uInt16 nWhich)
/*N*/ {
/*N*/   // call parent
/*N*/   E3dObject::PostItemChange(nWhich);
/*N*/
/*N*/   // handle value change
/*N*/   switch(nWhich)
/*N*/   {
/*N*/       case SDRATTR_3DOBJ_DOUBLE_SIDED:
/*N*/       {
/*N*/           bGeometryValid = FALSE;
/*N*/           break;
/*N*/       }
/*N*/       case SDRATTR_3DOBJ_NORMALS_KIND:
/*N*/       {
/*N*/           bGeometryValid = FALSE;
/*N*/           break;
/*N*/       }
/*N*/       case SDRATTR_3DOBJ_NORMALS_INVERT:
/*N*/       {
/*N*/           bGeometryValid = FALSE;
/*N*/           break;
/*N*/       }
/*N*/       case SDRATTR_3DOBJ_TEXTURE_PROJ_X:
/*N*/       {
/*N*/           bGeometryValid = FALSE;
/*N*/           break;
/*N*/       }
/*N*/       case SDRATTR_3DOBJ_TEXTURE_PROJ_Y:
/*N*/       {
/*N*/           bGeometryValid = FALSE;
/*N*/           break;
/*N*/       }
/*N*/   }
/*N*/ }

// EOF
}
