/*************************************************************************
 *
 *  $RCSfile: svx_cube3d.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:28 $
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

#include "svdstr.hrc"
#include "svdglob.hxx"

#ifndef _E3D_CUBE3D_HXX
#include "cube3d.hxx"
#endif

#ifndef _E3D_GLOBL3D_HXX
#include "globl3d.hxx"
#endif

#ifndef _POLY3D_HXX
#include "poly3d.hxx"
#endif

#ifndef _SVX_VECTOR3D_HXX
#include <goodies/vector3d.hxx>
#endif

#ifndef _E3D_E3DIOCMPT_HXX
#include "e3dcmpt.hxx"
#endif
namespace binfilter {

/*N*/ TYPEINIT1(E3dCubeObj, E3dCompoundObject);

/*************************************************************************
|*
|* Konstruktor:                                                 |
|* 3D-Quader erzeugen; aPos: Zentrum oder links, unten, hinten  |__
|*                           (abhaengig von bPosIsCenter)      /
|*
\************************************************************************/

/*N*/ E3dCubeObj::E3dCubeObj(E3dDefaultAttributes& rDefault, Vector3D aPos, const Vector3D& r3DSize)
/*N*/ : E3dCompoundObject(rDefault)
/*N*/ {
/*N*/   // Defaults setzen
/*N*/   SetDefaultAttributes(rDefault);
/*N*/
/*N*/   // uebergebene drueberbuegeln
/*N*/   aCubePos = aPos;
/*N*/   aCubeSize = r3DSize;
/*N*/
/*N*/   // Geometrie erzeugen
/*N*/   CreateGeometry();
/*N*/ }

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

/*N*/ SdrObject *E3dCubeObj::DoConvertToPolyObj(BOOL bBezier) const
/*N*/ {
/*N*/   return NULL;
/*N*/ }

/*************************************************************************
|*
|* Give out simple line geometry
|*
\************************************************************************/

//STRIP001 void E3dCubeObj::GetLineGeometry(PolyPolygon3D& rLinePolyPolygon) const
//STRIP001 {
//STRIP001  // add geometry describing polygons to rLinePolyPolygon
//STRIP001  Polygon3D aNewUpper(5);
//STRIP001  aNewUpper[0] = Vector3D(aCubePos.X(), aCubePos.Y(), aCubePos.Z() + aCubeSize.Z());
//STRIP001  aNewUpper[1] = Vector3D(aCubePos.X(), aCubePos.Y() + aCubeSize.Y(), aCubePos.Z() + aCubeSize.Z());
//STRIP001  aNewUpper[2] = Vector3D(aCubePos.X() + aCubeSize.X(), aCubePos.Y() + aCubeSize.Y(), aCubePos.Z() + aCubeSize.Z());
//STRIP001  aNewUpper[3] = Vector3D(aCubePos.X() + aCubeSize.X(), aCubePos.Y(), aCubePos.Z() + aCubeSize.Z());
//STRIP001  aNewUpper[4] = aNewUpper[0];
//STRIP001  rLinePolyPolygon.Insert(aNewUpper);
//STRIP001
//STRIP001  Polygon3D aNewLower(5);
//STRIP001  aNewLower[0] = Vector3D(aCubePos.X(), aCubePos.Y(), aCubePos.Z());
//STRIP001  aNewLower[1] = Vector3D(aCubePos.X(), aCubePos.Y() + aCubeSize.Y(), aCubePos.Z());
//STRIP001  aNewLower[2] = Vector3D(aCubePos.X() + aCubeSize.X(), aCubePos.Y() + aCubeSize.Y(), aCubePos.Z());
//STRIP001  aNewLower[3] = Vector3D(aCubePos.X() + aCubeSize.X(), aCubePos.Y(), aCubePos.Z());
//STRIP001  aNewLower[4] = aNewLower[0];
//STRIP001  rLinePolyPolygon.Insert(aNewLower);
//STRIP001
//STRIP001  Polygon3D aNewVertical(2);
//STRIP001  aNewVertical[0] = Vector3D(aCubePos.X(), aCubePos.Y(), aCubePos.Z());
//STRIP001  aNewVertical[1] = Vector3D(aCubePos.X(), aCubePos.Y(), aCubePos.Z() + aCubeSize.Z());
//STRIP001  rLinePolyPolygon.Insert(aNewVertical);
//STRIP001
//STRIP001  aNewVertical[0] = Vector3D(aCubePos.X(), aCubePos.Y() + aCubeSize.Y(), aCubePos.Z());
//STRIP001  aNewVertical[1] = Vector3D(aCubePos.X(), aCubePos.Y() + aCubeSize.Y(), aCubePos.Z() + aCubeSize.Z());
//STRIP001  rLinePolyPolygon.Insert(aNewVertical);
//STRIP001
//STRIP001  aNewVertical[0] = Vector3D(aCubePos.X() + aCubeSize.X(), aCubePos.Y() + aCubeSize.Y(), aCubePos.Z());
//STRIP001  aNewVertical[1] = Vector3D(aCubePos.X() + aCubeSize.X(), aCubePos.Y() + aCubeSize.Y(), aCubePos.Z() + aCubeSize.Z());
//STRIP001  rLinePolyPolygon.Insert(aNewVertical);
//STRIP001
//STRIP001  aNewVertical[0] = Vector3D(aCubePos.X() + aCubeSize.X(), aCubePos.Y(), aCubePos.Z());
//STRIP001  aNewVertical[1] = Vector3D(aCubePos.X() + aCubeSize.X(), aCubePos.Y(), aCubePos.Z() + aCubeSize.Z());
//STRIP001  rLinePolyPolygon.Insert(aNewVertical);
//STRIP001
//STRIP001  // don't call parent
//STRIP001  // E3dCompoundObject::GetLineGeometry(rLinePolyPolygon);
//STRIP001 }

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
|* Objektdaten in Stream speichern
|*
\************************************************************************/

/*N*/ void E3dCubeObj::WriteData(SvStream& rOut) const
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   long nVersion = rOut.GetVersion(); // Build_Nr * 10 z.B. 3810
/*N*/   if(nVersion < 3800)
/*N*/   {
/*N*/       // Alte Geometrie erzeugen, um die E3dPolyObj's zu haben
/*?*/       ((E3dCompoundObject*)this)->ReCreateGeometry(TRUE);
/*N*/   }
/*N*/
/*N*/   // call parent, schreibt die SubList (alte Geometrie) raus
/*N*/   E3dCompoundObject::WriteData(rOut);
/*N*/
/*N*/   E3dIOCompat aCompat(rOut, STREAM_WRITE, 1);
/*N*/   rOut << aCubePos;
/*N*/   rOut << aCubeSize;
/*N*/   rOut << BOOL(bPosIsCenter);
/*N*/   rOut << nSideFlags;
/*N*/
/*N*/   if(nVersion < 3800)
/*N*/   {
/*N*/       // Geometrie neu erzeugen, um E3dPolyObj's wieder loszuwerden
/*?*/       ((E3dCompoundObject*)this)->ReCreateGeometry();
/*N*/   }
/*N*/ #endif
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

//STRIP001 void E3dCubeObj::operator=(const SdrObject& rObj)
//STRIP001 {
//STRIP001  // erstmal alle Childs kopieren
//STRIP001  E3dCompoundObject::operator=(rObj);
//STRIP001
//STRIP001  // weitere Parameter kopieren
//STRIP001  const E3dCubeObj& r3DObj = (const E3dCubeObj&)rObj;
//STRIP001
//STRIP001  aCubePos = r3DObj.aCubePos;
//STRIP001  aCubeSize = r3DObj.aCubeSize;
//STRIP001  bPosIsCenter = r3DObj.bPosIsCenter;
//STRIP001  nSideFlags = r3DObj.nSideFlags;
//STRIP001 }

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

/*N*/ void E3dCubeObj::SetPosIsCenter(BOOL bNew)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if(bPosIsCenter != bNew)
//STRIP001  {
//STRIP001      bPosIsCenter = bNew;
//STRIP001      bGeometryValid = FALSE;
//STRIP001  }
/*N*/ }

//STRIP001 void E3dCubeObj::SetSideFlags(UINT16 nNew)
//STRIP001 {
//STRIP001  if(nSideFlags != nNew)
//STRIP001  {
//STRIP001      nSideFlags = nNew;
//STRIP001      bGeometryValid = FALSE;
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Get the name of the object (singular)
|*
\************************************************************************/

//STRIP001 void E3dCubeObj::TakeObjNameSingul(XubString& rName) const
//STRIP001 {
//STRIP001  rName=ImpGetResStr(STR_ObjNameSingulCube3d);
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

//STRIP001 void E3dCubeObj::TakeObjNamePlural(XubString& rName) const
//STRIP001 {
//STRIP001  rName=ImpGetResStr(STR_ObjNamePluralCube3d);
//STRIP001 }


}
