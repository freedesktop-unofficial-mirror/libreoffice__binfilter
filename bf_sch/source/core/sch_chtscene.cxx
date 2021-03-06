/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#ifdef _MSC_VER
#pragma hdrstop
#endif



#include "axisid.hxx"
#include "chtscene.hxx"
namespace binfilter {

#ifdef _MSC_VER
#pragma optimize ("",off)
#endif


/*N*/ TYPEINIT1(ChartScene, E3dPolyScene);

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ ChartScene::ChartScene(ChartModel* pDocument) :
/*N*/   E3dPolyScene(),
/*N*/   pDoc(pDocument),
/*N*/   bAskForLogicRect(TRUE)
/*N*/ {
/*N*/   nSortingMode = E3D_SORT_LOOKUP_FIELD | E3D_SORT_NON_POLYOBJ | E3D_SORT_TEST_LENGTH;
/*N*/     Initialize();
/*N*/     SetModel( pDocument );
/*N*/ }

/*************************************************************************
|*
|* Destruktor
|*
\************************************************************************/

/*N*/ ChartScene::~ChartScene ()
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Einpassen der Projektion aller Szenenobjekte in das
|* umschliessende Rechteck
|*
\************************************************************************/

/*N*/ Volume3D ChartScene::FitInSnapRect()
/*N*/ {
/*N*/   // untransformiertes BoundVolume holen und parent rufen
/*N*/   Volume3D aNewVol = E3dScene::FitInSnapRect();
/*N*/
/*N*/   // Groesse etwas anpassen, umPlatz am Rand des Charts fu schaffen
/*N*/   aNewVol.MinVec () = Vector3D (
/*N*/       aNewVol.MinVec ().X () * 1.2,
/*N*/       aNewVol.MinVec ().Y () * 1.2,
/*N*/       aNewVol.MinVec ().Z ());
/*N*/   aNewVol.MaxVec () = Vector3D (
/*N*/       aNewVol.MaxVec ().X () * 1.2,
/*N*/       aNewVol.MaxVec ().Y () * 1.2,
/*N*/       aNewVol.MaxVec ().Z ());
/*N*/
/*N*/   SetRectsDirty(FALSE);
/*N*/   return aNewVol;
/*N*/ }

/*************************************************************************
|*
|* Erstelle die 3D-Achsenbeschriftung  //war mal in globfunc.cxx
|*
\************************************************************************/

/*N*/ void ChartScene::InsertAllTitleText (DescrList         &rList,
/*N*/                                    E3dObject * /*pGroup*/,
/*N*/                                    long              nAxisId)
/*N*/ {
/*N*/   Rectangle aOldRect;
/*N*/
        for ( size_t i = 0, n = rList.size(); i < n; ++i )
        {
            E3dLabelObj *pLabel = rList[ i ];
/*N*/       Insert3DObj(pLabel);
/*N*/       pLabel->InsertUserData (new SchAxisId (nAxisId));
/*N*/   }
/*N*/ }
/*N*/ Rectangle ChartScene::Get3DDescrRect(E3dLabelObj *p3DObj,B3dCamera& rCamSet )
/*N*/ {
/*N*/   const SdrObject* pObj = p3DObj->Get2DLabelObj();
/*N*/   // View- Abmessungen des Labels holen
/*N*/   Rectangle  aRect = pObj->GetLogicRect();
/*N*/
/*N*/   // Position des Objektes in Weltkoordinaten ermitteln
/*N*/   Vector3D aObjPos = p3DObj->GetFullTransform() * p3DObj->GetPosition();
/*N*/   aObjPos = rCamSet.WorldToViewCoor(aObjPos);
/*N*/   Point aPoint((long)(aObjPos.X() + 0.5), (long)(aObjPos.Y() + 0.5));
/*N*/
/*N*/   // Relative Position des Labels in View-Koordinaten
/*N*/   Point aRelPosOne = pObj->GetRelativePos();
/*N*/   aRelPosOne += aPoint;
/*N*/
/*N*/   aRect.SetPos(aRelPosOne);
/*N*/   return aRect;
/*N*/ }

/*N*/ void ChartScene::ReduceDescrList(DescrList & aList)
/*N*/ {
/*N*/
/*N*/   Rectangle aIntersect(0,0,0,0);
/*N*/   Rectangle aPrevRect(0,0,0,0);
/*N*/   Rectangle aNextRect(0,0,0,0);
/*N*/
/*N*/   //Transformation berechnen, die sp?er im Paint ausgef?rt wird,
/*N*/   //(Derzeit sind die Labelobject-Positionen unbekannt)
/*N*/   Rectangle aBound(GetSnapRect());
/*N*/   Volume3D aVolume = FitInSnapRect();
/*N*/   B3dCamera& rSet = GetCameraSet();
/*N*/   rSet.SetDeviceRectangle(aVolume.MinVec().X(), aVolume.MaxVec().X(),
/*N*/   aVolume.MinVec().Y(), aVolume.MaxVec().Y(), FALSE);
/*N*/   rSet.SetFrontClippingPlane(aVolume.MinVec().Z());
/*N*/   rSet.SetBackClippingPlane(aVolume.MaxVec().Z());
/*N*/   rSet.SetViewportRectangle(aBound);
/*N*/
        size_t i = 0;
/*N*/   E3dLabelObj *p3DObj = aList.empty() ? NULL : aList[ 0 ];
/*N*/   E3dLabelObj *pOld3DObj=p3DObj;
/*N*/   BOOL bGetCurrent=FALSE;
/*N*/
/*N*/   if(p3DObj)
/*N*/   {
/*N*/       const SdrTextObj* pObj = (const SdrTextObj*)p3DObj->Get2DLabelObj();
/*N*/
/*N*/       //Es reicht, die Rotation des ersten Elements zu ermitteln,
/*N*/       //alle in der Liste sind gleicherma?n gedreht
/*N*/       //GetRotateAngle() gibt 100tel, gebraucht werden 10tel Grad.
/*N*/       long nAngle = pObj->GetRotateAngle()/10;
/*N*/
/*N*/       aPrevRect=Get3DDescrRect(p3DObj,rSet);
/*N*/       if(nAngle!=0)
/*N*/       {
/*?*/           //Um TopLeft drehen, so wie es sp?er gezeichnet wird
/*?*/           XPolygon aPoly(aPrevRect);
/*?*/           aPoly.Rotate(aPrevRect.TopLeft(),(USHORT)nAngle);
/*?*/           //und um den Koordinaten-Ursprung herum zur?kdrehen
/*?*/           //um wieder Rectangles zu erhalten (f? Intersect)
/*?*/           aPoly.Rotate(Point(0,0),(USHORT)(3600 - nAngle));
/*?*/           aPrevRect=aPoly.GetBoundRect();
/*N*/       }
/*N*/
/*N*/       while(p3DObj)
/*N*/       {
/*N*/           //n?hstes Objekt holen, abh?gig davon, ob das zuletzt behandelte
/*N*/           //entfernt wurde oder nicht (bGetCurrent)
/*N*/           if(bGetCurrent)
/*N*/           {
/*?*/               p3DObj = aList[ i ];
/*N*/           }
/*N*/           else
/*N*/           {
                    ++i;
                    p3DObj = ( i < aList.size() ) ? aList[ i ] : NULL;
/*N*/           }
/*N*/           bGetCurrent=FALSE;
/*N*/
/*N*/           //Da insbesondere bei Remove() des letzten Objects sowohl Next()
/*N*/           //als auch GetCurObject() den alten Pointer zur?kgeben,
/*N*/           //wird getestet, ob tats?hlich verschiedene Objekte vorliegen
/*N*/           DBG_ASSERT(p3DObj!=pOld3DObj,"Chart: pointers equal in Scene:reduce...");
/*N*/           if(p3DObj && p3DObj!=pOld3DObj)
/*N*/           {
/*N*/               pOld3DObj=p3DObj;
/*N*/
/*N*/               aNextRect=Get3DDescrRect(p3DObj,rSet);
/*N*/
/*N*/               if(nAngle!=0)
/*N*/               {
/*?*/                   //Um TopLeft drehen (wie oben):
/*?*/                   XPolygon aPoly(aNextRect);
/*?*/                   aPoly.Rotate(aNextRect.TopLeft(),(USHORT)nAngle);
/*?*/                   //und um den Ursprung herum zur?kdrehen
/*?*/                   aPoly.Rotate(Point(0,0),(USHORT)(3600 - nAngle));
/*?*/                   aNextRect=aPoly.GetBoundRect();
/*N*/               }
/*N*/
/*N*/               aIntersect=aNextRect.GetIntersection(aPrevRect);
/*N*/               if( !  (aIntersect.IsEmpty())
/*N*/                   && (   (aIntersect.GetHeight()>aNextRect.GetHeight()/100)
/*N*/                        ||(aIntersect.GetWidth() >aNextRect.GetHeight()/100)//2% Deckung maximal bezogen auf die Fonth?e
/*N*/                       )
/*N*/                 )
/*N*/               {
/*N*/                   E3dObject* pParent=p3DObj->GetParentObj();
/*N*/                   if(pParent)
/*N*/                   {
/*N*/                       //aus der Page streichen
/*N*/                       pParent->Remove3DObj(p3DObj);
/*N*/                   }
/*N*/                   else
/*N*/                   {
/*?*/                       OSL_TRACE("Chart:: Object has no parent (Scene)");
/*N*/                   }
/*N*/               }
/*N*/               else
/*N*/               {
/*N*/                   aPrevRect=aNextRect;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/ }

/*N*/ void ChartScene::Initialize()
/*N*/ {
/*N*/   // #66930# BM  activate second light source and deactivate first one
/*N*/     // reason: the first light source is in contrast to the other seven
/*N*/     //         lightsources specular by default
/*N*/
/*N*/     // Note: Use items at the scene instead of methods at the subobjects
/*N*/     //       otherwise settings get overwritten later
/*N*/
/*N*/     // copy lightsource 1 (Base3DLight0) to lightsource 2
/*N*/     // color
/*N*/   SetItem( Svx3DLightcolor2Item( GetLightGroup().GetIntensity( Base3DMaterialDiffuse, Base3DLight0 )));
/*N*/     // direction
/*N*/   SetItem( Svx3DLightDirection2Item( GetLightGroup().GetDirection( Base3DLight0 )));
/*N*/
/*N*/     // enable light source 2
/*N*/     SetItem( Svx3DLightOnOff2Item( TRUE ));
/*N*/     // disable light source 1
/*N*/     SetItem( Svx3DLightOnOff1Item( FALSE ));
/*N*/ }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
