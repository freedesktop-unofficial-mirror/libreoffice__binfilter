/*************************************************************************
 *
 *  $RCSfile: svx_polyob3d.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 15:41:28 $
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

#include <stdio.h>

#include "svdstr.hrc"
// auto strip #include "svdglob.hxx"

#ifndef _INC_FLOAT
#include <float.h>
#endif

#ifndef _SVDOPATH_HXX //autogen
#include "svdopath.hxx"
#endif

// auto strip #ifndef _SVDITER_HXX //autogen
// auto strip #include "svditer.hxx"
// auto strip #endif

// auto strip #ifndef _SVDPAGE_HXX
// auto strip #include "svdpage.hxx"
// auto strip #endif

// auto strip #ifndef _XATTR_HXX
// auto strip #include "xattr.hxx"
// auto strip #endif

// auto strip #ifndef _SVDHDL_HXX
// auto strip #include "svdhdl.hxx"
// auto strip #endif

#ifndef _SVDIO_HXX
#include "svdio.hxx"
#endif

// auto strip #ifndef _B3D_BASE3D_HXX
// auto strip #include <goodies/base3d.hxx>
// auto strip #endif

// FG: wegen der DEBUG-Ausgabe in Dateien (temporaer)
#ifndef _INC_STDIO
#include <stdio.h>
#endif

#ifndef _E3D_GLOBL3D_HXX
#include "globl3d.hxx"
#endif

#ifndef _E3D_POLYOB3D_HXX
#include "polyob3d.hxx"
#endif

#ifndef _E3D_POLYSC3D_HXX
#include "polysc3d.hxx"
#endif
namespace binfilter {

/*N*/ TYPEINIT1(E3dPolyObj, E3dObject);

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ E3dPolyObj::E3dPolyObj(const PolyPolygon3D& rPolyPoly3D, FASTBOOL bDblSided,
/*N*/   FASTBOOL bLight) :
/*N*/   bDoubleSided(bDblSided),
/*N*/   bBackSideVisible(FALSE),
/*N*/   bLighted(bLight),
/*N*/   bOwnAttrs (FALSE),
/*N*/   bOwnStyle (FALSE),
/*N*/   nObjectnumber (-1)  // FG: 0 waere eine gueltige Objektnummer, naemlich die erste!
/*N*/ {
/*N*/   SetPolyPolygon3D(rPolyPoly3D);
/*N*/ }

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*?*/ E3dPolyObj::E3dPolyObj(const PolyPolygon3D& rPolyPoly3D,
/*?*/   const PolyPolygon3D& rPolyNormals3D, FASTBOOL bDblSided,
/*?*/   FASTBOOL bLight) :
/*?*/   bDoubleSided(bDblSided),
/*?*/   bBackSideVisible(FALSE),
/*?*/   bLighted(bLight),
/*?*/   bOwnAttrs (FALSE),
/*?*/   bOwnStyle (FALSE),
/*?*/   nObjectnumber (-1)  // FG: 0 waere eine gueltige Objektnummer, naemlich die erste!
/*?*/ {
/*?*/   SetPolyPolygon3D(rPolyPoly3D);
/*?*/   SetPolyNormals3D(rPolyNormals3D);
/*?*/ }

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ E3dPolyObj::E3dPolyObj(const PolyPolygon3D& rPolyPoly3D,
/*N*/   const PolyPolygon3D& rPolyNormals3D,
/*N*/   const PolyPolygon3D& rPolyTexture3D,
/*N*/   FASTBOOL bDblSided,
/*N*/   FASTBOOL bLight) :
/*N*/   bDoubleSided(bDblSided),
/*N*/   bBackSideVisible(FALSE),
/*N*/   bLighted(bLight),
/*N*/   bOwnAttrs (FALSE),
/*N*/   bOwnStyle (FALSE),
/*N*/   nObjectnumber (-1)  // FG: 0 waere eine gueltige Objektnummer, naemlich die erste!
/*N*/ {
/*N*/   SetPolyPolygon3D(rPolyPoly3D);
/*N*/   SetPolyNormals3D(rPolyNormals3D);
/*N*/   SetPolyTexture3D(rPolyTexture3D);
/*N*/ }

/*************************************************************************
|*
|* Linien-Konstruktor
|*
\************************************************************************/

/*?*/ E3dPolyObj::E3dPolyObj(const Vector3D& rP1, const Vector3D& rP2) :
/*?*/   aPolyPoly3D(1),
/*?*/   bDoubleSided(TRUE),
/*?*/   bBackSideVisible(FALSE),
/*?*/   bLighted(FALSE),
/*?*/   bOwnAttrs (FALSE),
/*?*/   bOwnStyle (FALSE),
/*?*/   nObjectnumber (-1)    // FG: 0 waere eine gueltige Objektnummer, naemlich die erste!
/*?*/ {
/*?*/   Polygon3D aPoly3D(2);
/*?*/   aPoly3D[0] = rP1;
/*?*/   aPoly3D[1] = rP2;
/*?*/   aPolyPoly3D.Insert(aPoly3D);
/*?*/   aLocalBoundVol.Union(rP1);
/*?*/   aLocalBoundVol.Union(rP2);
/*?*/   RecalcBoundVolume();
/*?*/ }

/*************************************************************************
|*
|* Leer-Konstruktor
|*
\************************************************************************/

/*N*/ E3dPolyObj::E3dPolyObj() :
/*N*/   bDoubleSided(FALSE),
/*N*/   bBackSideVisible(FALSE),
/*N*/   bLighted(FALSE),
/*N*/   bOwnAttrs (FALSE),
/*N*/   bOwnStyle (FALSE),
/*N*/   nObjectnumber (-1)    // FG: 0 waere eine gueltige Objektnummer, naemlich die erste!
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Destruktor
|*
\************************************************************************/

/*N*/ E3dPolyObj::~E3dPolyObj()
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Identifier zurueckgeben
|*
\************************************************************************/

/*N*/ UINT16 E3dPolyObj::GetObjIdentifier() const
/*N*/ {
/*N*/   return E3D_POLYOBJ_ID;
/*N*/ }

/*************************************************************************
|*
|* Polygon setzen
|*
\************************************************************************/

/*N*/ void E3dPolyObj::SetPolyPolygon3D(const PolyPolygon3D& rNewPolyPoly3D)
/*N*/ {
/*N*/   if ( aPolyPoly3D != rNewPolyPoly3D )
/*N*/   {
/*N*/       // Neues PolyPolygon; kopieren
/*N*/       aPolyPoly3D = rNewPolyPoly3D;
/*N*/
/*N*/       // Normale berechnen und BoundVol fuellen
/*N*/       aLocalBoundVol = Volume3D();
/*N*/       aNormal = aPolyPoly3D.GetNormal();
/*N*/
/*N*/       // Teilpolygone einbeziehen
/*N*/       for ( USHORT nPoly = 0; nPoly < aPolyPoly3D.Count(); nPoly++ )
/*N*/           for ( USHORT i = 0; i < aPolyPoly3D[nPoly].GetPointCount(); i++ )
/*N*/               aLocalBoundVol.Union(aPolyPoly3D[nPoly][i]);
/*N*/
/*N*/       bBoundVolValid = FALSE;
/*N*/       StructureChanged(this);
/*N*/   }
/*N*/ }

/*N*/ void E3dPolyObj::SetPolyNormals3D(const PolyPolygon3D& rNewPolyNormals3D)
/*N*/ {
/*N*/   if ( aPolyNormals3D != rNewPolyNormals3D )
/*N*/   {
/*N*/       // Neue Normalen; kopieren
/*N*/       aPolyNormals3D = rNewPolyNormals3D;
/*N*/   }
/*N*/ }

/*N*/ void E3dPolyObj::SetPolyTexture3D(const PolyPolygon3D& rNewPolyTexture3D)
/*N*/ {
/*N*/   if ( aPolyTexture3D != rNewPolyTexture3D )
/*N*/   {
/*N*/       // Neue Texturkoordinaten; kopieren
/*N*/       aPolyTexture3D = rNewPolyTexture3D;
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Get the name of the object (singular)
|*
\************************************************************************/

//STRIP001 void E3dPolyObj::TakeObjNameSingul(XubString& rName) const
//STRIP001 {
//STRIP001  rName=ImpGetResStr(STR_ObjNameSingulPoly3d);
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

//STRIP001 void E3dPolyObj::TakeObjNamePlural(XubString& rName) const
//STRIP001 {
//STRIP001  rName=ImpGetResStr(STR_ObjNamePluralPoly3d);
//STRIP001 }

/*************************************************************************
|*
|* Get BoundRect of Object
|*
\************************************************************************/

/*N*/ const Rectangle& E3dPolyObj::GetBoundRect() const
/*N*/ {
/*N*/   return E3dObject::GetBoundRect();
/*N*/ }

/*************************************************************************
|*
|* sichern
|*
\************************************************************************/

/*N*/ void E3dPolyObj::WriteData31(SvStream& rOut) const
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   E3dObject::WriteData(rOut);
/*N*/
/*N*/   SdrDownCompat aCompat(rOut, STREAM_WRITE);
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("E3dPolyObj");
/*N*/ #endif
/*N*/
/*N*/   rOut << aPolyPoly3D;
/*N*/   rOut << aNormal;
/*N*/   rOut << BOOL(bDoubleSided);
/*N*/   rOut << BOOL(bBackSideVisible);
/*N*/   rOut << BOOL(bLighted);
/*N*/
/*N*/   rOut << (UINT32) bOwnAttrs;
/*N*/   rOut << (UINT32) bOwnStyle;
/*N*/ #endif
/*N*/ }

/*************************************************************************
|*
|* sichern: zur 356 wurde das Fileformat freigegeben 11.2.1997 FG
|*
/*************************************************************************/

/*N*/ void E3dPolyObj::WriteData(SvStream& rOut) const
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   if (rOut.GetVersion() < 3560) // FG: Zu dieser Version erfolgte die Umstellung
/*N*/   {
/*N*/       WriteData31(rOut);
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       SdrDownCompat aCompat(rOut, STREAM_WRITE);
/*N*/ #ifdef DBG_UTIL
/*N*/       aCompat.SetID("E3dPolyObj");
/*N*/ #endif
/*N*/       {
/*N*/           SdrDownCompat aCompat (rOut, STREAM_WRITE);
/*N*/ #ifdef DBG_UTIL
/*N*/           aCompat.SetID("PolyPolygon3D");
/*N*/ #endif
/*N*/           rOut << aPolyPoly3D;
/*N*/       }
/*N*/       {
/*N*/           SdrDownCompat aCompat (rOut, STREAM_WRITE);
/*N*/ #ifdef DBG_UTIL
/*N*/           aCompat.SetID("PolyPolygon3D");
/*N*/ #endif
/*N*/           rOut << aNormal;
/*N*/       }
/*N*/       rOut << BOOL(bDoubleSided);
/*N*/       rOut << BOOL(bBackSideVisible);
/*N*/       rOut << BOOL(bLighted);
/*N*/
/*N*/       rOut << (UINT32) bOwnAttrs;
/*N*/       rOut << (UINT32) bOwnStyle;
/*N*/       rOut << (UINT32) nObjectnumber;
/*N*/           // Falls das Objekt eigene Attribute hat, wird es rausgeschrieben
/*N*/
/*N*/       if (OwnAttrs() || OwnStyle())
/*N*/       {
/*N*/           E3dObject::WriteData(rOut);
/*N*/       }
/*N*/
/*N*/       // Neue PolyPolygone schreiben fuer Normalen und Textur
/*N*/       if(aPolyNormals3D.Count())
/*N*/       {
/*N*/ #ifdef DBG_UTIL
/*N*/           aCompat.SetID("PolyPolygon3D Normals");
/*N*/ #endif
/*N*/           rOut << aPolyNormals3D;
/*N*/       }
/*N*/       if(aPolyTexture3D.Count())
/*N*/       {
/*N*/ #ifdef DBG_UTIL
/*N*/           aCompat.SetID("PolyPolygon3D Texturkoordinaten");
/*N*/ #endif
/*N*/           rOut << aPolyTexture3D;
/*N*/       }
/*N*/   }
/*N*/ #endif    // #ifndef SVX_LIGHT
/*N*/ }

/*************************************************************************
|*
|* laden
|*
\************************************************************************/

/*N*/ void E3dPolyObj::ReadData31(const SdrObjIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   if (ImpCheckSubRecords (rHead, rIn))
/*N*/   {
/*N*/       E3dObject::ReadData(rHead, rIn);
/*N*/       SdrDownCompat aCompat(rIn, STREAM_READ);
/*N*/ #ifdef DBG_UTIL
/*N*/       aCompat.SetID("E3dPolyObj");
/*N*/ #endif
/*N*/
/*N*/       BOOL   bTmp;
/*N*/       UINT32 nTmp;
/*N*/
/*N*/       // wieviele Bytes werden fuer das Polygon gelesen ?
/*N*/       long nFilePositionBefore = rIn.Tell ();
/*N*/       rIn >> aPolyPoly3D;
/*N*/       long nFilePositionAfter  = rIn.Tell ();
/*N*/
/*N*/       // wenn anschliessend noch mehr Member gestreamt werden, so muss (!!!!) die
/*N*/       // folgende Anzahl der Bytes angepasst werden, ansonsten geht das Lesen wieder
/*N*/       // daneben !
/*N*/       // Diese Werte werden weiter unten eingelesen.
/*N*/       long nBytesToRead        = sizeof (aNormal) + sizeof (bTmp) * 3 + sizeof (nTmp) * 2;
/*N*/
/*N*/       // wieviele Bytes wuerden denn nun gelesen werden ?
/*N*/       // es kommen noch 4 Bytes hinzu, die vom SdrDownCompat fuer die Laenge belegt werden
/*N*/       long nWouldRead          = nFilePositionAfter - nFilePositionBefore + nBytesToRead + 4;
/*N*/
/*N*/       // und um wieviele liegen wir daneben ?
/*N*/       long nBytesWrong         = nWouldRead - aCompat.GetSubRecordSize();
/*N*/
/*N*/       // hoffentlich alles ok, sonst korrigiere die Fileposition
/*N*/       if (nBytesWrong)
/*N*/       {
/*N*/           rIn.Seek (nFilePositionAfter - nBytesWrong);
/*N*/       }
/*N*/
/*N*/       // so, jetzt kann der Rest unbeschadet gelesen werden.
/*N*/       // aus den hier gelesenen Werten muss die Groesse nBytesToRead bestimmt werden.
/*N*/       rIn >> aNormal;
/*N*/       rIn >> bTmp; bDoubleSided = bTmp;
/*N*/       rIn >> bTmp; bBackSideVisible = bTmp;
/*N*/       rIn >> bTmp; bLighted = bTmp;
/*N*/
/*N*/       // Temporaer: Anzahl der Dreiecke aus der Triangulation
/*N*/       rIn >> nTmp; bOwnAttrs = (BOOL) nTmp;
/*N*/
/*N*/       if (aCompat.GetBytesLeft () == sizeof (UINT32)) rIn >> nTmp; bOwnStyle = (BOOL) nTmp;
/*N*/
/*N*/       SetPolyPolygon3D(aPolyPoly3D);
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* laden
|*
\************************************************************************/

/*N*/ void E3dPolyObj::ReadData(const SdrObjIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   if ( rIn.GetError() != SVSTREAM_OK )
/*N*/       return;
/*N*/
/*N*/   if ((rHead.GetVersion() < 13) || (rIn.GetVersion() < 3560))
/*N*/   {
/*N*/       ReadData31(rHead, rIn);
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       BOOL   bTmp;
/*N*/       UINT32 nTmp;
/*N*/
/*N*/       SdrDownCompat aCompat(rIn, STREAM_READ);
/*N*/ #ifdef DBG_UTIL
/*N*/       aCompat.SetID("E3dPolyObj");
/*N*/ #endif
/*N*/
/*N*/       {
/*N*/           SdrDownCompat aCompatPolyPolygon (rIn, STREAM_READ);
/*N*/ #ifdef DBG_UTIL
/*N*/           aCompatPolyPolygon.SetID("PolyPolygon3D");
/*N*/ #endif
/*N*/           rIn >> aPolyPoly3D;
/*N*/       }
/*N*/       {
/*N*/           SdrDownCompat aCompatPolyPolygon (rIn, STREAM_READ);
/*N*/ #ifdef DBG_UTIL
/*N*/           aCompatPolyPolygon.SetID("PolyPolygon3D");
/*N*/ #endif
/*N*/           rIn >> aNormal;
/*N*/       }
/*N*/
/*N*/       rIn >> bTmp; bDoubleSided = bTmp;
/*N*/       rIn >> bTmp; bBackSideVisible = bTmp;
/*N*/       rIn >> bTmp; bLighted = bTmp;
/*N*/
/*N*/       // Temporaer: Anzahl der Dreiecke aus der Triangulation
/*N*/       rIn >> nTmp; bOwnAttrs = (BOOL) nTmp;
/*N*/       rIn >> nTmp; bOwnStyle = (BOOL) nTmp;
/*N*/       rIn >> nObjectnumber;
/*N*/
/*N*/       // Nur falls das Objekt eigene Attribute oder einen eigenen
/*N*/       // Stil besitzt wird es gelesen.
/*N*/
/*N*/       if (OwnAttrs() || OwnStyle())
/*N*/       {
/*N*/         E3dObject::ReadData(rHead, rIn);
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/               // FG: Achtung fuer jedes 3d-Objekt muss eine Subliste existieren, auch wenn
/*N*/               //     sie keinen Eintrag hat, viele Programmstellen (GetBoundRect) fragen nicht
/*N*/               //     ab ob dieser Pointer NULL ist.
/*N*/           pSub = new E3dObjList(NULL, NULL);
/*N*/           pSub->SetOwnerObj(this);
/*N*/           pSub->SetListKind(SDROBJLIST_GROUPOBJ);
/*N*/       }
/*N*/
/*N*/       if(aCompat.GetBytesLeft())
/*N*/       {
/*N*/           // Normalen lesen
/*N*/           rIn >> aPolyNormals3D;
/*N*/           SetPolyNormals3D(aPolyNormals3D);
/*N*/       }
/*N*/
/*N*/       if(aCompat.GetBytesLeft())
/*N*/       {
/*N*/           // Texturen lesen
/*N*/           rIn >> aPolyTexture3D;
/*N*/           SetPolyTexture3D(aPolyTexture3D);
/*N*/       }
/*N*/
/*N*/       SetPolyPolygon3D(aPolyPoly3D);
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Wireframe erzeugen
|*
\************************************************************************/

//STRIP001 void E3dPolyObj::CreateWireframe(Polygon3D& rWirePoly, const Matrix4D* pTf,
//STRIP001  E3dDragDetail eDetail)
//STRIP001 {
//STRIP001  // Keine Aktion, da solche Objekte nur noch Hilfsobjekte beim
//STRIP001  // Laden/Speichern von 4.0 Format sind.
//STRIP001 }

/*************************************************************************
|*
|* Zuweisungsoperator
|*
\************************************************************************/

//STRIP001 void E3dPolyObj::operator=(const SdrObject& rObj)
//STRIP001 {
//STRIP001  E3dObject::operator=(rObj);
//STRIP001
//STRIP001  const E3dPolyObj& r3DObj = (const E3dPolyObj&) rObj;
//STRIP001
//STRIP001  aPolyPoly3D      = r3DObj.aPolyPoly3D;
//STRIP001  aPolyNormals3D   = r3DObj.aPolyNormals3D;
//STRIP001  aPolyTexture3D   = r3DObj.aPolyTexture3D;
//STRIP001  aNormal          = r3DObj.aNormal;
//STRIP001
//STRIP001  bDoubleSided     = r3DObj.bDoubleSided;
//STRIP001  bBackSideVisible = r3DObj.bBackSideVisible;
//STRIP001  bLighted         = r3DObj.bLighted;
//STRIP001  bOwnAttrs        = r3DObj.bOwnAttrs;
//STRIP001  bOwnStyle        = r3DObj.bOwnStyle;
//STRIP001
//STRIP001  nObjectnumber    = r3DObj.nObjectnumber;
//STRIP001 }

/*************************************************************************
|*
|* Wandle das Objekt in ein Polygon.
|* Es ist nur ein Displayobjekt vorhanden, welches ein (!) Polygon darstellt
|*
\************************************************************************/

//STRIP001 SdrObject *E3dPolyObj::DoConvertToPolyObj(BOOL bBezier) const
//STRIP001 {
//STRIP001  return NULL;
//STRIP001 }

/*************************************************************************
|*
|* erstelle neues GeoData-Objekt
|*
\************************************************************************/

/*N*/ SdrObjGeoData *E3dPolyObj::NewGeoData() const
/*N*/ {
/*N*/   DBG_ASSERT(GetParentObj(), "3D-Polygone ohne Parent ?");
/*N*/   DBG_ASSERT(GetParentObj()->ISA(E3dScene) || GetParentObj()->ISA(E3dObject), "Parent eines 3D-Polygons ungültig");
/*N*/
/*N*/   if (GetParentObj()->ISA (E3dObject))
/*N*/       return GetParentObj()->E3dObject::NewGeoData ();
/*N*/   else
/*N*/       return E3dObject::NewGeoData ();
/*N*/ }

/*************************************************************************
|*
|* uebergebe aktuelle werte an das GeoData-Objekt
|*
\************************************************************************/

/*?*/ void E3dPolyObj::SaveGeoData(SdrObjGeoData& rGeo) const
/*?*/ {
/*?*/   DBG_ASSERT(GetParentObj(), "3D-Polygone ohne Parent ?");
/*?*/   DBG_ASSERT(GetParentObj()->ISA(E3dScene) || GetParentObj()->ISA(E3dObject), "Parent eines 3D-Polygons ungültig");
/*?*/
/*?*/   if (GetParentObj()->ISA (E3dObject))
/*?*/       GetParentObj()->E3dObject::SaveGeoData (rGeo);
/*?*/   else
/*?*/       E3dObject::SaveGeoData (rGeo);
/*?*/ }

/*************************************************************************
|*
|* uebernehme werte aus dem GeoData-Objekt
|*
\************************************************************************/

/*?*/ void E3dPolyObj::RestGeoData(const SdrObjGeoData& rGeo)
/*?*/ {
/*?*/   DBG_ASSERT(GetParentObj(), "3D-Polygone ohne Parent ?");
/*?*/   DBG_ASSERT(GetParentObj()->ISA(E3dScene) || GetParentObj()->ISA(E3dObject), "Parent eines 3D-Polygons ungültig");
/*?*/
/*?*/   if (GetParentObj()->ISA (E3dObject))
/*?*/       GetParentObj()->E3dObject::RestGeoData (rGeo);
/*?*/   else
/*?*/       E3dObject::RestGeoData (rGeo);
/*?*/ }

/*************************************************************************
|*
|* Page neu setzen. Normalerweise geht die Page an das Oberobjekt, wenn
|* dieses Objekt von einer Factory erzeugt wurde, existiert noch kein
|* Parent, also wird die Page selbst gesetzt.
|*
\************************************************************************/

/*N*/ void E3dPolyObj::SetPage(SdrPage* pNewPage)
/*N*/ {
/*N*/   if (GetParentObj())
/*N*/   {
/*N*/       DBG_ASSERT(GetParentObj()->ISA(E3dScene) || GetParentObj()->ISA(E3dObject), "Parent eines 3D-Polygons ungültig");
/*N*/
/*N*/       if (GetParentObj()->ISA (E3dObject))
/*N*/           GetParentObj()->E3dObject::SetPage (pNewPage);
/*N*/       SdrAttrObj::SetPage(pNewPage);
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       pPage = pNewPage;
/*N*/       if (pPage)
/*N*/           pModel = pPage->GetModel ();
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Layer setzen
|*
\************************************************************************/

/*N*/ void E3dPolyObj::SetModel(SdrModel* pNewModel)
/*N*/ {
/*N*/   SdrAttrObj::SetModel(pNewModel);
/*N*/ }

/*************************************************************************
|*
|* Layer abfragen. Da alle Unterobjekte auf demselben Layer liegen
|* gibt es keinerlei Probleme
|*
\************************************************************************/

/*?*/ SdrLayerID E3dPolyObj::GetLayer() const
/*?*/ {
/*?*/   DBG_ASSERT(GetParentObj(), "3D-Polygone ohne Parent ?");
/*?*/   DBG_ASSERT(GetParentObj()->ISA(E3dScene) || GetParentObj()->ISA(E3dObject), "Parent eines 3D-Polygons ungültig");
/*?*/
/*?*/   if (GetParentObj()->ISA (E3dObject))
/*?*/       return GetParentObj()->E3dObject::GetLayer ();
/*?*/   else
/*?*/       return SdrLayerID(nLayerID);
/*?*/ }

/*************************************************************************
|*
|* Layer setzen
|*
\************************************************************************/

/*N*/ void E3dPolyObj::NbcSetLayer(SdrLayerID nLayer)
/*N*/ {
/*N*/   DBG_ASSERT(GetParentObj(), "3D-Polygone ohne Parent ?");
/*N*/   DBG_ASSERT(GetParentObj()->ISA(E3dScene) || GetParentObj()->ISA(E3dObject), "Parent eines 3D-Polygons ungültig");
/*N*/
/*N*/   if (GetParentObj()->ISA (E3dObject))
/*N*/       GetParentObj()->SdrAttrObj::NbcSetLayer (nLayer);
/*N*/   SdrAttrObj::NbcSetLayer(nLayer);
/*N*/ }

/*************************************************************************
|*
|* StyleSheet abfragen
|*
\************************************************************************/

/*N*/ SfxStyleSheet* E3dPolyObj::GetStyleSheet() const
/*N*/ {
/*N*/   DBG_ASSERT(GetParentObj(), "3D-Polygone ohne Parent ?");
/*N*/   DBG_ASSERT(GetParentObj()->ISA(E3dScene) || GetParentObj()->ISA(E3dObject), "Parent eines 3D-Polygons ungültig");
/*N*/
/*N*/   if (bOwnStyle)
/*N*/       return SdrAttrObj::GetStyleSheet();
/*N*/   else
/*N*/       return GetParentObj()->E3dObject::GetStyleSheet ();
/*N*/ }

/*************************************************************************
|*
|* StyleSheet setzen
|*
\************************************************************************/

//STRIP001 void E3dPolyObj::NbcSetStyleSheet(SfxStyleSheet *pNewStyleSheet,
//STRIP001                                FASTBOOL      bDontRemoveHardAttr)
//STRIP001 {
//STRIP001  DBG_ASSERT(GetParentObj(), "3D-Polygone ohne Parent ?");
//STRIP001  DBG_ASSERT(GetParentObj()->ISA(E3dScene) || GetParentObj()->ISA(E3dObject), "Parent eines 3D-Polygons ungültig");
//STRIP001
//STRIP001
//STRIP001  GetParentObj()->E3dObject::SendRepaintBroadcast ();
//STRIP001  ForceDefaultAttrAgain ();
//STRIP001  SdrAttrObj::NbcSetStyleSheet(pNewStyleSheet, bDontRemoveHardAttr);
//STRIP001  bOwnAttrs = TRUE;
//STRIP001  bOwnStyle = TRUE;
//STRIP001  StructureChanged(this);
//STRIP001  GetParentObj()->E3dObject::SendRepaintBroadcast ();
//STRIP001 }

/*************************************************************************
|*
|* Bestimme die Anzahl der Punkte
|*
\************************************************************************/

//STRIP001 USHORT E3dPolyObj::GetPointCount () const
//STRIP001 {
//STRIP001  USHORT nResult = 0;
//STRIP001
//STRIP001  for (long nPoly = 0;
//STRIP001            nPoly < aPolyPoly3D.Count();
//STRIP001            nPoly ++)
//STRIP001      nResult += (USHORT) (aPolyPoly3D[(USHORT)nPoly].GetPointCount());
//STRIP001
//STRIP001  return nResult;
//STRIP001 }


}
