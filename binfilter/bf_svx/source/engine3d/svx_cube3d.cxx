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

#include "svdstr.hrc"

#include "cube3d.hxx"

#include "globl3d.hxx"



#include "e3dcmpt.hxx"
namespace binfilter {

/*N*/ TYPEINIT1(E3dCubeObj, E3dCompoundObject);

/*N*/ E3dCubeObj::E3dCubeObj()
/*N*/ : E3dCompoundObject()
/*N*/ {
/*N*/   // Defaults setzen
/*N*/   E3dDefaultAttributes aDefault;
/*N*/   SetDefaultAttributes(aDefault);
/*N*/ }

/*N*/ void E3dCubeObj::SetDefaultAttributes(E3dDefaultAttributes& rDefault)
/*N*/ {
/*N*/   aCubePos = rDefault.GetDefaultCubePos();
/*N*/   aCubeSize = rDefault.GetDefaultCubeSize();
/*N*/   nSideFlags = rDefault.GetDefaultCubeSideFlags();
/*N*/   bPosIsCenter = rDefault.GetDefaultCubePosIsCenter();
/*N*/ }

/*************************************************************************
|*
|* Identifier zurueckgeben
|*
\************************************************************************/

/*N*/ UINT16 E3dCubeObj::GetObjIdentifier() const
/*N*/ {
/*N*/   return E3D_CUBEOBJ_ID;
/*N*/ }

/*************************************************************************
|*
|* Wandle das Objekt in ein Gruppenobjekt bestehend aus 6 Polygonen
|*
\************************************************************************/

/*N*/ SdrObject *E3dCubeObj::DoConvertToPolyObj(BOOL /*bBezier*/) const
/*N*/ {
/*N*/   return NULL;
/*N*/ }

/*************************************************************************
|*
|* Geometrieerzeugung
|*
\************************************************************************/

/*N*/ void E3dCubeObj::CreateGeometry()
/*N*/ {
/*N*/   Vector3D    aPos(aCubePos);
/*N*/   Polygon3D   aRect3D(4);
/*N*/   Polygon3D   aNormals3D(4);
/*N*/   Polygon3D   aTexture3D(4);
/*N*/   short       nV1, nV2;
/*N*/   UINT16      nSideBit = 0x0001;
/*N*/
/*N*/   // Start der Geometrieerzeugung ankuendigen
/*N*/   StartCreateGeometry();
/*N*/
/*N*/   if ( bPosIsCenter )
/*?*/       aCubePos -= aCubeSize / 2;
/*N*/
/*N*/   for (nV1 = 0; nV1 < 3; nV1++)
/*N*/   {
/*N*/       if ( nV1 == 0 ) nV2 = 2;
/*N*/       else            nV2 = nV1 - 1;
/*N*/
/*N*/       // Nur die Flaechen erzeugen, fuer die ein Bit
/*N*/       if ( nSideFlags & nSideBit )
/*N*/       {   // Flaechenpunkte entgegen dem Uhrzeigersinn generieren
/*N*/           aRect3D[0] = aPos; aPos[nV1] += aCubeSize[nV1];
/*N*/           aRect3D[1] = aPos; aPos[nV2] += aCubeSize[nV2];
/*N*/           aRect3D[2] = aPos; aPos[nV1] -= aCubeSize[nV1];
/*N*/           aRect3D[3] = aPos; aPos[nV2] -= aCubeSize[nV2];
/*N*/
/*N*/           if(GetCreateNormals())
/*N*/           {
/*N*/               aNormals3D = aRect3D;
/*N*/               aNormals3D[0].Normalize();
/*N*/               aNormals3D[1].Normalize();
/*N*/               aNormals3D[2].Normalize();
/*N*/               aNormals3D[3].Normalize();
/*N*/
/*N*/               if(GetCreateTexture())
/*N*/               {
/*N*/                   aTexture3D[1].X() = 0.0;
/*N*/                   aTexture3D[1].Y() = 0.0;
/*N*/
/*N*/                   aTexture3D[0].X() = 1.0;
/*N*/                   aTexture3D[0].Y() = 0.0;
/*N*/
/*N*/                   aTexture3D[2].X() = 0.0;
/*N*/                   aTexture3D[2].Y() = 1.0;
/*N*/
/*N*/                   aTexture3D[3].X() = 1.0;
/*N*/                   aTexture3D[3].Y() = 1.0;
/*N*/
/*N*/                   AddGeometry(aRect3D, aNormals3D, aTexture3D, FALSE);
/*N*/               }
/*N*/               else
/*?*/                   AddGeometry(aRect3D, aNormals3D, FALSE);
/*N*/           }
/*N*/           else
/*N*/           {
/*?*/               AddGeometry(aRect3D, FALSE);
/*N*/           }
/*N*/       }
/*N*/       nSideBit <<= 1;
/*N*/   }
/*N*/   aPos += aCubeSize;
/*N*/
/*N*/   for (nV1 = 2; nV1 >= 0; nV1--)
/*N*/   {
/*N*/       if ( nV1 == 2 ) nV2 = 0;
/*N*/       else            nV2 = nV1 + 1;
/*N*/
/*N*/       if ( nSideFlags & nSideBit )
/*N*/       {   // Flaechenpunkte entgegen dem Uhrzeigersinn generieren
/*N*/           aRect3D[0] = aPos; aPos[nV1] -= aCubeSize[nV1];
/*N*/           aRect3D[1] = aPos; aPos[nV2] -= aCubeSize[nV2];
/*N*/           aRect3D[2] = aPos; aPos[nV1] += aCubeSize[nV1];
/*N*/           aRect3D[3] = aPos; aPos[nV2] += aCubeSize[nV2];
/*N*/
/*N*/           if(GetCreateTexture())
/*N*/           {
/*N*/               aTexture3D[1].X() = 0.0;
/*N*/               aTexture3D[1].Y() = 0.0;
/*N*/
/*N*/               aTexture3D[0].X() = 1.0;
/*N*/               aTexture3D[0].Y() = 0.0;
/*N*/
/*N*/               aTexture3D[2].X() = 0.0;
/*N*/               aTexture3D[2].Y() = 1.0;
/*N*/
/*N*/               aTexture3D[3].X() = 1.0;
/*N*/               aTexture3D[3].Y() = 1.0;
/*N*/           }
/*N*/
/*N*/           if(GetCreateNormals())
/*N*/           {
/*N*/               aNormals3D = aRect3D;
/*N*/               aNormals3D[0].Normalize();
/*N*/               aNormals3D[1].Normalize();
/*N*/               aNormals3D[2].Normalize();
/*N*/               aNormals3D[3].Normalize();
/*N*/
/*N*/               if(GetCreateTexture())
/*N*/                   AddGeometry(aRect3D, aNormals3D, aTexture3D, FALSE);
/*N*/               else
/*?*/                   AddGeometry(aRect3D, aNormals3D, FALSE);
/*N*/           }
/*N*/           else
/*N*/           {
/*?*/               AddGeometry(aRect3D, FALSE);
/*N*/           }
/*N*/       }
/*N*/       nSideBit <<= 1;
/*N*/   }
/*N*/
/*N*/   // call parent
/*N*/   E3dCompoundObject::CreateGeometry();
/*N*/ }

/*************************************************************************
|*
|* Objektdaten aus Stream laden
|*
\************************************************************************/

/*N*/ void E3dCubeObj::ReadData(const SdrObjIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   // call parent
/*N*/   E3dCompoundObject::ReadData(rHead, rIn);
/*N*/
/*N*/   // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/   BOOL bAllDone(FALSE);
/*N*/   if(AreBytesLeft())
/*N*/   {
/*N*/       E3dIOCompat aIoCompat(rIn, STREAM_READ);
/*N*/       if(aIoCompat.GetVersion() >= 1)
/*N*/       {
/*N*/           BOOL bTmp;
/*N*/           rIn >> aCubePos;
/*N*/           rIn >> aCubeSize;
/*N*/           rIn >> bTmp; bPosIsCenter = bTmp;
/*N*/           rIn >> nSideFlags;
/*N*/           bAllDone = TRUE;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if(!bAllDone)
/*N*/   {
/*N*/       // Geometrie aus erzeugten PolyObj's rekonstruieren
/*N*/       const Volume3D& rVolume = GetLocalBoundVolume();
/*N*/       aCubeSize = rVolume.MaxVec() - rVolume.MinVec();
/*N*/       aCubePos = rVolume.MinVec();
/*N*/       bPosIsCenter = FALSE;
/*N*/       nSideFlags = CUBE_FULL;
/*N*/   }
/*N*/
/*N*/   // Geometrie neu erzeugen, mit oder ohne E3dPolyObj's
/*N*/   ReCreateGeometry();
/*N*/ }

/*************************************************************************
|*
|* Zuweisungsoperator
|*
\************************************************************************/


/*************************************************************************
|*
|* Lokale Parameter setzen mit Geometrieneuerzeugung
|*
\************************************************************************/

/*N*/ void E3dCubeObj::SetCubePos(const Vector3D& rNew)
/*N*/ {
/*N*/   if(aCubePos != rNew)
/*N*/   {
/*N*/       aCubePos = rNew;
/*N*/       bGeometryValid = FALSE;
/*N*/   }
/*N*/ }

/*N*/ void E3dCubeObj::SetCubeSize(const Vector3D& rNew)
/*N*/ {
/*N*/   if(aCubeSize != rNew)
/*N*/   {
/*N*/       aCubeSize = rNew;
/*N*/       bGeometryValid = FALSE;
/*N*/   }
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
