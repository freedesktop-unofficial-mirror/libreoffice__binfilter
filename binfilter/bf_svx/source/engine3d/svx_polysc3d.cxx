/*************************************************************************
 *
 *  $RCSfile: svx_polysc3d.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:43:25 $
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

#ifndef INCLUDED_SVTOOLS_OPTIONS3D_HXX
#include <svtools/options3d.hxx>
#endif

#ifndef _SVX_FILLITEM_HXX
#include "xfillit.hxx"
#endif

#ifndef _SVDOPATH_HXX //autogen
#include "svdopath.hxx"
#endif

#ifndef _SVDOGRP_HXX //autogen
#include "svdogrp.hxx"
#endif

#ifndef _SVDITER_HXX //autogen
#include "svditer.hxx"
#endif

#ifndef _SVDETC_HXX //autogen
#include "svdetc.hxx"
#endif

#ifndef _VIRDEV_HXX //autogen
#include <vcl/virdev.hxx>
#endif

#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif

#ifndef _XOUTX_HXX
#include "xoutx.hxx"
#endif

#ifndef _SVDPAGE_HXX
#include "svdpage.hxx"
#endif

#ifndef _SVDPOOL_HXX
#include "svdpool.hxx"
#endif

#ifndef _SFXSTYLE_HXX
#include <svtools/style.hxx>
#endif

#ifndef _E3D_GLOBL3D_HXX
#include "globl3d.hxx"
#endif

#ifndef _E3D_POLYSC3D_HXX
#include "polysc3d.hxx"
#endif

#ifndef _E3D_PLIGHT3D_HXX
#include "plight3d.hxx"
#endif

#ifndef _E3D_DLIGHT3D_HXX
#include "dlight3d.hxx"
#endif

#ifndef _B3D_BASE3D_HXX
#include <goodies/base3d.hxx>
#endif

#ifndef _B3D_B3DTEX_HXX
#include <goodies/b3dtex.hxx>
#endif

#ifndef _SVX_XLNCLIT_HXX
#include "xlnclit.hxx"
#endif

#ifndef _SFXMETRICITEM_HXX
#include <svtools/metitem.hxx>
#endif

#ifndef _XTABLE_HXX
#include "xtable.hxx"
#endif

#ifndef _SVX_XLNWTIT_HXX
#include "xlnwtit.hxx"
#endif
namespace binfilter {

#define ITEMVALUE(ItemSet,Id,Cast)  ((const Cast&)(ItemSet).Get(Id)).GetValue()

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*N*/ TYPEINIT1(E3dPolyScene, E3dScene);

/*N*/ E3dPolyScene::E3dPolyScene()
/*N*/ : E3dScene()
/*N*/ {
/*N*/ }

/*?*/ E3dPolyScene::E3dPolyScene(E3dDefaultAttributes& rDefault)
/*?*/ : E3dScene(rDefault)
/*?*/ {
/*?*/ }

/*************************************************************************
|*
|* Identifier zurueckgeben
|*
\************************************************************************/

/*N*/ UINT16 E3dPolyScene::GetObjIdentifier() const
/*N*/ {
/*N*/   return E3D_POLYSCENE_ID;
/*N*/ }

/*************************************************************************
|*
|* Die Kontur fuer TextToContour
|*
\************************************************************************/

//STRIP001 void E3dPolyScene::TakeContour(XPolyPolygon& rPoly) const
//STRIP001 {
//STRIP001  ((E3dPolyScene*)this)->TakeContour3D(rPoly);
//STRIP001 }

/*************************************************************************
|*
|* Objekt als Kontur in das Polygon einfuegen
|*
\************************************************************************/

//STRIP001 void E3dPolyScene::TakeContour3D(XPolyPolygon& rPoly)
//STRIP001 {
//STRIP001  // TransformationSet vorbereiten
//STRIP001  InitTransformationSet();
//STRIP001
//STRIP001  // Holen
//STRIP001  E3dScene::TakeContour3D(rPoly);
//STRIP001 }

/*************************************************************************
|*
|* Paint
|*
\************************************************************************/

/*N*/ FASTBOOL E3dPolyScene::Paint(ExtOutputDevice& rOut,
/*N*/   const SdrPaintInfoRec& rInfoRec) const
/*N*/ {DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  FASTBOOL bOk=TRUE;
//STRIP001  if(GetSubList() && GetSubList()->GetObjCount())
//STRIP001  {
//STRIP001      bOk = ((E3dPolyScene*)this)->LocalPaint3D(rOut, rInfoRec);
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // Leere Szene, zeichne genau wie leere Gruppe
//STRIP001      if (!rInfoRec.bPrinter && rInfoRec.aPaintLayer.IsSet(nLayerId)) {
//STRIP001          OutputDevice* pOutDev=rOut.GetOutDev();
//STRIP001          pOutDev->SetLineColor(Color(COL_LIGHTGRAY));
//STRIP001          pOutDev->SetFillColor();
//STRIP001          pOutDev->DrawRect(aOutRect);
//STRIP001      }
//STRIP001  }
//STRIP001  if (bOk && (rInfoRec.nPaintMode & SDRPAINTMODE_GLUEPOINTS) !=0) {
//STRIP001      bOk=PaintGluePoints(rOut,rInfoRec);
//STRIP001  }
//STRIP001  return bOk;
/*N*/ }

//STRIP001 BOOL E3dPolyScene::LocalPaint3D(ExtOutputDevice& rOut,
//STRIP001  const SdrPaintInfoRec& rInfoRec)
//STRIP001 {
//STRIP001  Time aStartTime;
//STRIP001  Rectangle aBound(GetSnapRect());
//STRIP001  OutputDevice* pOut = rOut.GetOutDev();
//STRIP001
//STRIP001  sal_uInt16 nShadeMode = GetShadeMode();
//STRIP001  Base3D *pBase3D = Base3D::Create(pOut, nShadeMode > 2);
//STRIP001
//STRIP001  DBG_ASSERT(pBase3D, "Habe keinen Base3D Kontext bekommen!!");
//STRIP001  pBase3D->SetDisplayQuality(GetDisplayQuality());
//STRIP001
//STRIP001  if(nShadeMode == 0)
//STRIP001      pBase3D->SetShadeModel(Base3DFlat);
//STRIP001  else if(nShadeMode == 1)
//STRIP001      pBase3D->SetShadeModel(Base3DPhong);
//STRIP001  else
//STRIP001      pBase3D->SetShadeModel(Base3DSmooth);
//STRIP001
//STRIP001  Rectangle aVisible(Point(0,0), pOut->GetOutputSizePixel());
//STRIP001  aVisible = pOut->PixelToLogic(aVisible);
//STRIP001
//STRIP001  // #101867# If rendering to metafile
//STRIP001  if(pOut && pOut->GetConnectMetaFile() && !pOut->IsOutputEnabled())
//STRIP001  {
//STRIP001      aVisible = aBound;
//STRIP001  }
//STRIP001
//STRIP001  // Feststellen, ob transparente Teile enthalten sind
//STRIP001  pBase3D->SetTransparentPartsContainedHint(AreThereTransparentParts());
//STRIP001
//STRIP001  // eventuell ScissorRegion setzen
//STRIP001  pBase3D->ActivateScissorRegion(FALSE);
//STRIP001  if(aBound != aVisible)
//STRIP001  {
//STRIP001      Rectangle aClipBound = aBound.GetIntersection(aVisible);
//STRIP001      if(aClipBound != aBound)
//STRIP001      {
//STRIP001          pBase3D->SetScissorRegion(aClipBound);
//STRIP001
//STRIP001 #ifdef DBG_UTIL      // draw aClipBound for testing
//STRIP001          static BOOL bDoDrawClipBoundForTesting(FALSE);
//STRIP001          if(bDoDrawClipBoundForTesting)
//STRIP001          {
//STRIP001              OutputDevice* pOut = rOut.GetOutDev();
//STRIP001
//STRIP001              // red
//STRIP001              pOut->SetLineColor(Color(COL_RED));
//STRIP001              pOut->SetFillColor();
//STRIP001              pOut->DrawRect(aClipBound);
//STRIP001
//STRIP001              Rectangle aClipBoundPixel = pOut->LogicToPixel(aClipBound);
//STRIP001              BOOL bWasEnabled = pOut->IsMapModeEnabled();
//STRIP001              pOut->EnableMapMode(FALSE);
//STRIP001
//STRIP001              // GREEN
//STRIP001              pOut->SetLineColor(Color(COL_GREEN));
//STRIP001              pOut->SetFillColor();
//STRIP001              pOut->DrawRect(aClipBoundPixel);
//STRIP001
//STRIP001              pOut->EnableMapMode(bWasEnabled);
//STRIP001          }
//STRIP001 #endif
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // GeometricSet reset und mit pBase3D assoziieren
//STRIP001  B3dCamera& rSet = GetCameraSet();
//STRIP001  pBase3D->SetTransformationSet(&rSet);
//STRIP001
//STRIP001  // Dithering
//STRIP001  pBase3D->SetDither(GetDither() && SvtOptions3D().IsDithering());
//STRIP001
//STRIP001  // Licht setzen, vor Object->World setzen, um Lichter im
//STRIP001  // WKS zu positionieren
//STRIP001  pBase3D->SetLightGroup(&(GetLightGroup()));
//STRIP001
//STRIP001  // Transformation initialisieren
//STRIP001  InitTransformationSet();
//STRIP001
//STRIP001  // Viewport-Grenzen eintragen
//STRIP001  rSet.SetViewportRectangle(aBound, aVisible);
//STRIP001
//STRIP001  // Matritzen aktualisieren (OpenGL)
//STRIP001  pBase3D->SetTransformationSet(&rSet);
//STRIP001
//STRIP001  if(!pBase3D->GetDisplayQuality())
//STRIP001  {
//STRIP001      // Extrem verminderte Darstellungsqualitaet, zeichne als
//STRIP001      // WireFrame, voellig OHNE renderer
//STRIP001      DrawWireframe(pBase3D, rOut);
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // Schatten zeichnen
//STRIP001      if(pBase3D->GetDisplayQuality() > 128)
//STRIP001      {
//STRIP001          B3dVolume aVol = rSet.GetDeviceVolume();
//STRIP001          Volume3D aVolume(aVol.MinVec(), aVol.MaxVec());
//STRIP001          DrawAllShadows(pBase3D, rOut, aBound, aVolume, rInfoRec);
//STRIP001      }
//STRIP001
//STRIP001      // Szene mit clipping zeichnen
//STRIP001      DrawPolySceneClip(rOut, this, pBase3D, rInfoRec);
//STRIP001  }
//STRIP001
//STRIP001  // Labels darueber zeichnen. Da es auch Wertebeschriftungen
//STRIP001  // im Chart gibt, ist es besser, die Labels hinterher zu zeichnen.
//STRIP001  // Leider kann es auch dabei zu Zeichenfehlern kommen. Die
//STRIP001  // LabelObjekte muessen irgendwann mal auf echte 3D-Objekte
//STRIP001  // umgestellt werden.
//STRIP001  SdrObjList* pSubList = GetSubList();
//STRIP001  if(pSubList)
//STRIP001  {
//STRIP001      SdrObjListIter a3DIterator(*pSubList, IM_DEEPWITHGROUPS);
//STRIP001      while ( a3DIterator.IsMore() )
//STRIP001      {
//STRIP001          E3dObject* pObj = (E3dObject*) a3DIterator.Next();
//STRIP001          DBG_ASSERT(pObj->ISA(E3dObject), "In Szenen sind nur 3D-Objekte erlaubt!");
//STRIP001
//STRIP001          if(pObj->ISA(E3dLabelObj))
//STRIP001          {
//STRIP001              E3dLabelObj* pLabelObject = (E3dLabelObj*)pObj;
//STRIP001              SdrObject* pLabel = (SdrObject*)pLabelObject->Get2DLabelObj();
//STRIP001              const Vector3D aPos = rSet.WorldToViewCoor(pLabelObject->GetTransPosition());
//STRIP001              Point a2DPos((long)(aPos.X() + 0.5), (long)(aPos.Y() + 0.5));
//STRIP001              pLabel->NbcSetAnchorPos(a2DPos);
//STRIP001              pLabel->Paint(rOut, rInfoRec);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Zeichenzeit bestimmen
//STRIP001  aPaintTime = Time().GetTime() - aStartTime.GetTime();
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }

/*************************************************************************
|*
|* Geometrie zeichnen mit clipping Beruecksichtigung
|*
\************************************************************************/

//STRIP001 void E3dPolyScene::DrawPolySceneClip(ExtOutputDevice& rOut,
//STRIP001  const E3dObject* p3DObj, Base3D* pBase3D, const SdrPaintInfoRec& rInfoRec)
//STRIP001 {
//STRIP001  // spezielles Clipping fuer OpenGL, um keine floating windows ueberzumalen
//STRIP001  OutputDevice* pOut = rOut.GetOutDev();
//STRIP001
//STRIP001  if(pBase3D->GetBase3DType() == BASE3D_TYPE_OPENGL
//STRIP001      && pOut->GetOutDevType() == OUTDEV_WINDOW
//STRIP001      && pBase3D->GetTransformationSet())
//STRIP001  {
//STRIP001      Window* pWin = (Window*)pOut;
//STRIP001      RegionHandle aRegionHandle;
//STRIP001      Rectangle aClipRect;
//STRIP001      Rectangle aSystemClipRect;
//STRIP001      BOOL bClippingWasActive(FALSE);
//STRIP001      Region aClipRegion;
//STRIP001
//STRIP001 #ifdef DBG_UTIL      // ClipRegions zum testen zeichnen
//STRIP001      static BOOL bDoDrawRegionsToMakeThemVisible = FALSE;
//STRIP001      if(bDoDrawRegionsToMakeThemVisible)
//STRIP001      {
//STRIP001          // Rot
//STRIP001          aClipRegion = pWin->GetWindowClipRegionPixel();
//STRIP001
//STRIP001          // Trick von TH, um das Umrechnen auf logische Koordinaten zu vermeiden
//STRIP001          BOOL bMapModeWasSet = pWin->IsMapModeEnabled();
//STRIP001          pWin->EnableMapMode(FALSE);
//STRIP001
//STRIP001          aClipRegion.Intersect(pWin->GetActiveClipRegion());
//STRIP001          pWin->EnableMapMode(bMapModeWasSet);
//STRIP001
//STRIP001          aRegionHandle = aClipRegion.BeginEnumRects();
//STRIP001
//STRIP001          while(aClipRegion.GetEnumRects(aRegionHandle, aClipRect))
//STRIP001          {
//STRIP001              pOut->SetLineColor(Color(COL_RED));
//STRIP001              pOut->SetFillColor();
//STRIP001              pOut->DrawRect(aClipRect);
//STRIP001          }
//STRIP001          aClipRegion.EndEnumRects(aRegionHandle);
//STRIP001      }
//STRIP001 #endif
//STRIP001
//STRIP001      // Eventuell bereits gesetzte ClipRegion sichern und zur Verwendung
//STRIP001      // vorbereiten
//STRIP001      if(pBase3D->IsScissorRegionActive())
//STRIP001      {
//STRIP001          aSystemClipRect = pBase3D->GetScissorRegionPixel();
//STRIP001          bClippingWasActive = TRUE;
//STRIP001      }
//STRIP001
//STRIP001      // ClipRegion holen und Durchlauf vorbereiten
//STRIP001      aClipRegion = pWin->GetWindowClipRegionPixel();
//STRIP001
//STRIP001      // Trick von TH, um das Umrechnen auf logische Koordinaten zu vermeiden
//STRIP001      BOOL bMapModeWasSet = pWin->IsMapModeEnabled();
//STRIP001      pWin->EnableMapMode(FALSE);
//STRIP001
//STRIP001      aClipRegion.Intersect(pWin->GetActiveClipRegion());
//STRIP001      pWin->EnableMapMode(bMapModeWasSet);
//STRIP001
//STRIP001      aRegionHandle = aClipRegion.BeginEnumRects();
//STRIP001      Rectangle aBase3DRect = pWin->LogicToPixel(
//STRIP001          pBase3D->GetTransformationSet()->GetLogicalViewportBounds());
//STRIP001
//STRIP001      // Lauf ueber die ClipRegions
//STRIP001      while(aClipRegion.GetEnumRects(aRegionHandle, aClipRect))
//STRIP001      {
//STRIP001          if(aClipRect.IsOver(aBase3DRect))
//STRIP001          {
//STRIP001              // ClipRegion setzen
//STRIP001              if(bClippingWasActive)
//STRIP001              {
//STRIP001                  pBase3D->SetScissorRegionPixel(aClipRect.GetIntersection(aSystemClipRect), TRUE);
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  pBase3D->SetScissorRegionPixel(aClipRect, TRUE);
//STRIP001              }
//STRIP001
//STRIP001              // Beginn szene
//STRIP001              pBase3D->StartScene();
//STRIP001
//STRIP001              // Ausgabe aller 3D Objekte
//STRIP001              Paint3D(rOut, pBase3D, rInfoRec, 0);
//STRIP001
//STRIP001              // Ende der Szene
//STRIP001              UINT32 nWasDrawMode = rOut.GetOutDev()->GetDrawMode();
//STRIP001              rOut.GetOutDev()->SetDrawMode(rInfoRec.nOriginalDrawMode);
//STRIP001              pBase3D->EndScene();
//STRIP001              rOut.GetOutDev()->SetDrawMode(nWasDrawMode);
//STRIP001          }
//STRIP001      }
//STRIP001      aClipRegion.EndEnumRects(aRegionHandle);
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // Ohne clipping ausgeben
//STRIP001      // Beginn szene
//STRIP001      pBase3D->StartScene();
//STRIP001
//STRIP001      // Ausgabe aller 3D Objekte
//STRIP001      ((E3dPolyScene *)this)->Paint3D(rOut, pBase3D, rInfoRec, 0);
//STRIP001
//STRIP001      // Ende der Szene
//STRIP001      UINT32 nWasDrawMode = rOut.GetOutDev()->GetDrawMode();
//STRIP001      rOut.GetOutDev()->SetDrawMode(rInfoRec.nOriginalDrawMode);
//STRIP001      pBase3D->EndScene();
//STRIP001      rOut.GetOutDev()->SetDrawMode(nWasDrawMode);
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Zeichenroutine fuer 3D
|*
\************************************************************************/

//STRIP001 void E3dPolyScene::Paint3D(ExtOutputDevice& rOut, Base3D* pBase3D,
//STRIP001  const SdrPaintInfoRec& rInfoRec, UINT16 nDrawFlags)
//STRIP001 {
//STRIP001  if(GetScene() != this)
//STRIP001  {
//STRIP001      // Szene in einer Szene, durchreichen
//STRIP001      E3dObject::Paint3D(rOut, pBase3D, rInfoRec, nDrawFlags);
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // Dies ist die Root-Szene
//STRIP001      if(pBase3D->GetTransparentPartsContainedHint())
//STRIP001      {
//STRIP001          // Nicht-Transparente Flaechen
//STRIP001          E3dObject::Paint3D(rOut, pBase3D, rInfoRec, E3D_DRAWFLAG_FILLED);
//STRIP001
//STRIP001          // Nicht-Transparente Linien
//STRIP001          E3dObject::Paint3D(rOut, pBase3D, rInfoRec, E3D_DRAWFLAG_OUTLINE);
//STRIP001
//STRIP001          // Transparente Flaechen
//STRIP001          E3dObject::Paint3D(rOut, pBase3D, rInfoRec, E3D_DRAWFLAG_FILLED|E3D_DRAWFLAG_TRANSPARENT);
//STRIP001
//STRIP001          // Transparente Linien
//STRIP001          E3dObject::Paint3D(rOut, pBase3D, rInfoRec, E3D_DRAWFLAG_OUTLINE|E3D_DRAWFLAG_TRANSPARENT);
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // call parent
//STRIP001          E3dObject::Paint3D(rOut, pBase3D, rInfoRec, E3D_DRAWFLAG_FILLED|E3D_DRAWFLAG_OUTLINE);
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Schatten aller Objekte zeichnen
|*
\************************************************************************/

//STRIP001 void E3dPolyScene::DrawAllShadows(Base3D* pBase3D, ExtOutputDevice& rXOut,
//STRIP001  const Rectangle& rBound, const Volume3D& rVolume,
//STRIP001  const SdrPaintInfoRec& rInfoRec)
//STRIP001 {
//STRIP001  // TransformationSet vorbereiten
//STRIP001  InitTransformationSet();
//STRIP001
//STRIP001  // Schatten Zeichnen
//STRIP001  E3dScene::DrawShadows(pBase3D, rXOut, rBound, rVolume, rInfoRec);
//STRIP001 }

/*************************************************************************
|*
|* Verminderte Darstellungsqualitaet, zeichne als WireFrame OHNE renderer
|*
\************************************************************************/

//STRIP001 void E3dPolyScene::DrawWireframe(Base3D* pBase3D, ExtOutputDevice& rXOut)
//STRIP001 {
//STRIP001  // Farben setzen
//STRIP001  rXOut.GetOutDev()->SetLineColor(Color(COL_BLACK));
//STRIP001  rXOut.GetOutDev()->SetFillColor();
//STRIP001
//STRIP001  // Unterobjekte darstellen
//STRIP001  SdrObjList* pSubList = GetSubList();
//STRIP001  if(pSubList)
//STRIP001  {
//STRIP001      SdrObjListIter a3DIterator(*pSubList, IM_DEEPWITHGROUPS);
//STRIP001      while ( a3DIterator.IsMore() )
//STRIP001      {
//STRIP001          E3dObject* pObj = (E3dObject*) a3DIterator.Next();
//STRIP001          DBG_ASSERT(pObj->ISA(E3dObject), "In Szenen sind nur 3D-Objekte erlaubt!");
//STRIP001          if(pObj->ISA(E3dCompoundObject))
//STRIP001          {
//STRIP001              E3dCompoundObject* pCompObj = (E3dCompoundObject*)pObj;
//STRIP001
//STRIP001              // ObjectTrans setzen
//STRIP001              Matrix4D mTransform = pCompObj->GetFullTransform();
//STRIP001              GetCameraSet().SetObjectTrans(mTransform);
//STRIP001              pBase3D->SetTransformationSet(&(GetScene()->GetCameraSet()));
//STRIP001
//STRIP001              // WireFrame eines einzelnen Objektes
//STRIP001              pCompObj->DrawObjectWireframe(rXOut);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }


}
