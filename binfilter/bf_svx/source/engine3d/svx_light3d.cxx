/*************************************************************************
 *
 *  $RCSfile: svx_light3d.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:21:47 $
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

#ifndef _SVDIO_HXX
#include "svdio.hxx"
#endif

#ifndef _E3D_GLOBL3D_HXX
#include "globl3d.hxx"
#endif

#ifndef _E3D_LIGHT3D_HXX
#include "light3d.hxx"
#endif

#ifndef _SVDPAGE_HXX
#include "svdpage.hxx"
#endif

/*N*/ TYPEINIT1(E3dLight, E3dPointObj);

/*************************************************************************
|*
|* E3dLight-Konstruktor
|*
\************************************************************************/

/*N*/ E3dLight::E3dLight(const Vector3D& rPos, const Color& rColor,
/*N*/                   double fLightIntensity) :
/*N*/   E3dPointObj(rPos),
/*N*/   fIntensity(fLightIntensity),
/*N*/   bOn(TRUE),
/*N*/   bVisible(FALSE)
/*N*/ {
/*N*/   SetColor(rColor);
/*N*/   aLocalBoundVol = Volume3D();
/*N*/   bBoundVolValid = FALSE;
/*N*/ }

/*************************************************************************
|*
|* E3dLight-Konstruktor 2
|*
\************************************************************************/

/*N*/ E3dLight::E3dLight() :
/*N*/   E3dPointObj(Vector3D()),
/*N*/
/*N*/   aColor(255, 255, 255),
/*N*/
/*N*/   fRed(1.0),
/*N*/   fGreen(1.0),
/*N*/   fBlue(1.0),
/*N*/   fIntensity(1.0),
/*N*/   bOn(TRUE),
/*N*/   bVisible(FALSE)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* protected, daher kein Einfuegen von Objekten von aussen moeglich
|*
\************************************************************************/

/*N*/ void E3dLight::Insert3DObj(E3dObject* p3DObj)
/*N*/ {
/*N*/ //    E3dPointObj::Insert3DObj(p3DObj);
/*N*/   GetSubList()->InsertObject(p3DObj);
/*N*/ }

/*************************************************************************
|*
|* Identifier zurueckgeben
|*
\************************************************************************/

/*N*/ UINT16 E3dLight::GetObjIdentifier() const
/*N*/ {
/*N*/   return E3D_LIGHT_ID;
/*N*/ }

/*************************************************************************
|*
|* Lichtstaerke an uebergeben Punkt bestimmen und die akkumulierte
|* Punktfarbe berechnen; Return = TRUE bedeutet, dass die maximale
|* Farbintensitaet aller Farbanteile erreicht ist.
|*
\************************************************************************/

/*N*/ FASTBOOL E3dLight::ImpCalcLighting(Color& rNewColor, const Color& rPntColor,
/*N*/                                   double fR, double fG, double fB) const
/*N*/ {
/*N*/   ULONG   nR(rNewColor.GetRed()),
/*N*/           nG(rNewColor.GetGreen()),
/*N*/           nB(rNewColor.GetBlue());
/*N*/   ULONG   nPntR(rPntColor.GetRed()),
/*N*/           nPntG(rPntColor.GetGreen()),
/*N*/           nPntB(rPntColor.GetBlue());
/*N*/
/*N*/   if ( bOn )
/*N*/   {
/*N*/       nR += (ULONG) (fR * nPntR);
/*N*/       nG += (ULONG) (fG * nPntG);
/*N*/       nB += (ULONG) (fB * nPntB);
/*N*/
/*N*/       nR = Min(nR, nPntR);
/*N*/       nG = Min(nG, nPntG);
/*N*/       nB = Min(nB, nPntB);
/*N*/
/*N*/       rNewColor.SetRed((USHORT) nR);
/*N*/       rNewColor.SetGreen((USHORT) nG);
/*N*/       rNewColor.SetBlue((USHORT) nB);
/*N*/   }
/*N*/   return ( nR == nPntR && nG == nPntG && nB == nPntB );
/*N*/ }

/*************************************************************************
|*
|* Lichtstaerke an uebergeben Punkt bestimmen und die akkumulierte
|* Punktfarbe berechnen
|*
\************************************************************************/

/*N*/ FASTBOOL E3dLight::CalcLighting(Color& rNewColor,
/*N*/                               const Vector3D& rPnt,
/*N*/                               const Vector3D& rPntNormal,
/*N*/                               const Color& rPntColor)
/*N*/ {
/*N*/   return ImpCalcLighting(rNewColor, rPntColor, fRed, fGreen, fBlue);
/*N*/ }

/*************************************************************************
|*
|* neue Position setzen und Aenderung an Parents (Szene) melden
|*
\************************************************************************/

/*N*/ void E3dLight::SetPosition(const Vector3D& rNewPos)
/*N*/ {
/*N*/   E3dPointObj::SetPosition(rNewPos);
/*N*/   CreateLightObj();
/*N*/ }

/*************************************************************************
|*
|* neue Intensitaet setzen und Aenderung an Parents (Szene) melden
|*
\************************************************************************/

/*N*/ void E3dLight::SetIntensity(double fNew)
/*N*/ {
/*N*/   if ( fIntensity != fNew )
/*N*/   {
/*N*/       fIntensity = fNew;
/*N*/       StructureChanged(this);
/*N*/       SetColor(aColor);
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* neue Farbe setzen und Aenderung an Parents (Szene) melden
|*
\************************************************************************/

/*N*/ void E3dLight::SetColor(const Color& rNewColor)
/*N*/ {
/*N*/   if ( aColor != rNewColor )
/*N*/   {
/*N*/       aColor = rNewColor;
/*N*/       StructureChanged(this);
/*N*/   }
/*N*/
/*N*/   fRed    = fIntensity * aColor.GetRed()   / 255;
/*N*/   fGreen  = fIntensity * aColor.GetGreen() / 255;
/*N*/   fBlue   = fIntensity * aColor.GetBlue()  / 255;
/*N*/ }

/*************************************************************************
|*
|* Lichtquelle ein-/ausschalten und Aenderung an Parents (Szene) melden
|*
\************************************************************************/

//STRIP001 void E3dLight::SetOn(FASTBOOL bNewOn)
//STRIP001 {
//STRIP001  if ( bOn != bNewOn )
//STRIP001  {
//STRIP001      bOn = bNewOn;
//STRIP001      StructureChanged(this);
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Darstellung des Lichtobjekts in der Szene ein-/ausschalten
|*
\************************************************************************/

//STRIP001 void E3dLight::SetLightObjVisible(FASTBOOL bNewVisible)
//STRIP001 {
//STRIP001  if ( bVisible != bNewVisible )
//STRIP001  {
//STRIP001      bVisible = bNewVisible;
//STRIP001      CreateLightObj();
//STRIP001
//STRIP001      if ( bVisible )
//STRIP001          aLocalBoundVol = Volume3D(aPosition, Vector3D(), FALSE);
//STRIP001      else
//STRIP001          aLocalBoundVol = Volume3D();
//STRIP001
//STRIP001      bBoundVolValid = FALSE;
//STRIP001      StructureChanged(this);
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Darstellung des Lichtobjekts in der Szene ein-/ausschalten
|*
\************************************************************************/

/*N*/ void E3dLight::CreateLightObj()
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* sichern
|*
\************************************************************************/

/*N*/ void E3dLight::WriteData(SvStream& rOut) const
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   E3dPointObj::WriteData(rOut);
/*N*/
/*N*/ #ifdef E3D_STREAMING
/*N*/
/*N*/   SdrDownCompat aCompat(rOut, STREAM_WRITE);
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("E3dLight");
/*N*/ #endif
/*N*/
/*N*/   rOut << aColor;
/*N*/   rOut << fIntensity;
/*N*/   rOut << fRed;
/*N*/   rOut << fGreen;
/*N*/   rOut << fBlue;
/*N*/   rOut << BOOL(bOn);
/*N*/   rOut << BOOL(bVisible);
/*N*/ #endif
/*N*/ #endif    // #ifndef SVX_LIGHT
/*N*/ }

/*************************************************************************
|*
|* laden
|*
\************************************************************************/

/*N*/ void E3dLight::ReadData(const SdrObjIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   if (ImpCheckSubRecords (rHead, rIn))
/*N*/   {
/*N*/       E3dPointObj::ReadData(rHead, rIn);
/*N*/
/*N*/       SdrDownCompat aCompat(rIn, STREAM_READ);
/*N*/ #ifdef DBG_UTIL
/*N*/       aCompat.SetID("E3dLight");
/*N*/ #endif
/*N*/
/*N*/       BOOL bTmp;
/*N*/
/*N*/       rIn >> aColor;
/*N*/       rIn >> fIntensity;
/*N*/       rIn >> fRed;
/*N*/       rIn >> fGreen;
/*N*/       rIn >> fBlue;
/*N*/       rIn >> bTmp; bOn = bTmp;
/*N*/       rIn >> bTmp; bVisible = bTmp;
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Zuweisungsoperator
|*
\************************************************************************/

//STRIP001 void E3dLight::operator=(const SdrObject& rObj)
//STRIP001 {
//STRIP001  E3dPointObj::operator=(rObj);
//STRIP001
//STRIP001  const E3dLight& r3DObj = (const E3dLight&) rObj;
//STRIP001
//STRIP001  aColor      = r3DObj.aColor;
//STRIP001  fIntensity  = r3DObj.fIntensity;
//STRIP001  fRed        = r3DObj.fRed;
//STRIP001  fGreen      = r3DObj.fGreen;
//STRIP001  fBlue       = r3DObj.fBlue;
//STRIP001  bOn         = r3DObj.bOn;
//STRIP001  bVisible    = r3DObj.bVisible;
//STRIP001 }

/*************************************************************************
|*
|* Attribute setzen
|*
\************************************************************************/

//STRIP001 void E3dLight::NbcSetStyleSheet(SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr)
//STRIP001 {
//STRIP001 }

/*************************************************************************
|*
|* Attribute setzen
|*
\************************************************************************/

/*N*/ void E3dLight::SetStyleSheet(SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Attribute abfragen
|*
\************************************************************************/

/*N*/ SfxStyleSheet*E3dLight::GetStyleSheet() const
/*N*/ {
/*N*/   return 0;
/*N*/ }


