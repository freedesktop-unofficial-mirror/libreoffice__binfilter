/*************************************************************************
 *
 *  $RCSfile: svx_viewpt3d.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:43:27 $
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

#ifndef _VIEWPT3D_HXX
#include "viewpt3d.hxx"
#endif

#ifndef _VOLUME3D_HXX
#include "volume3d.hxx"
#endif

#ifndef _SVDIO_HXX
#include "svdio.hxx"
#endif
namespace binfilter {

/*************************************************************************
|*
|* Konstruktor
|*
\************************************************************************/

/*N*/ Viewport3D::Viewport3D() :
/*N*/   aVRP(0, 0, 5),
/*N*/   aVPN(0, 0, 1),
/*N*/   aVUV(0, 1, 1),
/*N*/   aPRP(0, 0, 2),
/*N*/   fVPD(-3),
/*N*/   aViewPoint (0, 0, 5000),
/*N*/   fNearClipDist (0.0),
/*N*/   fFarClipDist (0.0),
/*N*/   fWRatio (1.0),
/*N*/   fHRatio (1.0),
/*N*/   eProjection(PR_PERSPECTIVE),
/*N*/   eAspectMapping(AS_NO_MAPPING),
/*N*/   bTfValid(0),
/*N*/   // DeviceRect-Groesse < 0 -> ungueltig
/*N*/   aDeviceRect(Point(0,0), Size(-1,-1))
/*N*/ {
/*N*/   aViewWin.X = -1; aViewWin.Y = -1;
/*N*/   aViewWin.W =  2; aViewWin.H = 2;
/*N*/ }

/*************************************************************************
|*
|* View-Transformationsmatrix berechnen
|*
\************************************************************************/

/*N*/ void Viewport3D::MakeTransform(void)
/*N*/ {
/*N*/   if ( !bTfValid )
/*N*/   {
/*N*/       double fV, fXupVp, fYupVp;
/*N*/       aViewPoint = aVRP + aVPN * aPRP.Z();
/*N*/
/*N*/       // auf Einheitsmatrix zuruecksetzen
/*N*/       aViewTf.Identity();
/*N*/
/*N*/       // in den Ursprung verschieben
/*N*/       aViewTf.Translate(-aVRP);
/*N*/
/*N*/       // fV = Laenge der Projektion von aVPN auf die yz-Ebene:
/*N*/       fV = aVPN.GetYZLength();
/*N*/
/*N*/       if ( fV != 0 )
/*N*/           aViewTf.RotateX(aVPN.Y() / fV, aVPN.Z() / fV);
/*N*/
/*N*/       aViewTf.RotateY(- aVPN.X(), fV);
/*N*/       // X- und Y-Koordinaten des View Up Vektors in das (vorlaeufige)
/*N*/       // View-Koordinatensytem umrechnen
/*N*/       fXupVp = aViewTf[0][0] * aVUV[0] + aViewTf[0][1] * aVUV[1] + aViewTf[0][2] * aVUV[2];
/*N*/       fYupVp = aViewTf[1][0] * aVUV[0] + aViewTf[1][1] * aVUV[1] + aViewTf[1][2] * aVUV[2];
/*N*/       fV = sqrt(fXupVp * fXupVp + fYupVp * fYupVp);
/*N*/       if ( fV != 0 )
/*N*/           aViewTf.RotateZ(fXupVp / fV, fYupVp / fV);
/*N*/
/*N*/       aViewTf = Matrix4D(aViewTf);
/*N*/       bTfValid = TRUE;
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* ViewWindow (in View-Koordinaten) setzen
|*
\************************************************************************/

/*N*/ void Viewport3D::SetViewWindow(double fX, double fY, double fW, double fH)
/*N*/ {
/*N*/   aViewWin.X = fX;
/*N*/   aViewWin.Y = fY;
/*N*/   if ( fW > 0 )   aViewWin.W = fW;
/*N*/   else            aViewWin.W = 1.0;
/*N*/   if ( fH > 0 )   aViewWin.H = fH;
/*N*/   else            aViewWin.H = 1.0;
/*N*/
/*N*/   fWRatio = aDeviceRect.GetWidth() / aViewWin.W;
/*N*/   fHRatio = aDeviceRect.GetHeight() / aViewWin.H;
/*N*/ }

/*************************************************************************
|*
|* ViewWindow zurueckgeben
|*
\************************************************************************/

//STRIP001 void Viewport3D::GetViewWindow(double& rX, double& rY,
//STRIP001                             double& rW, double& rH) const
//STRIP001 {
//STRIP001  rX = aViewWin.X;
//STRIP001  rY = aViewWin.Y;
//STRIP001  rW = aViewWin.W;
//STRIP001  rH = aViewWin.H;
//STRIP001 }

/*************************************************************************
|*
|* View-Window genau um das mit rTransform transformierte Volumen legen
|*
\************************************************************************/

/*N*/ void Viewport3D::FitViewToVolume(const Volume3D& rVolume, Matrix4D aTransform)
/*N*/ {
/*N*/   Vector3D aTfVec;
/*N*/   Volume3D aFitVol;
/*N*/
/*N*/   aTransform *= GetViewTransform();
/*N*/   Vol3DPointIterator aIter(rVolume, &aTransform);
/*N*/
/*N*/   while ( aIter.Next(aTfVec) )
/*N*/   {
/*N*/       DoProjection(aTfVec);
/*N*/       aFitVol.Union(aTfVec);
/*N*/   }
/*N*/   SetViewWindow(aFitVol.MinVec().X(), aFitVol.MinVec().Y(),
/*N*/                 aFitVol.GetWidth(), aFitVol.GetHeight());
/*N*/ }

/*************************************************************************
|*
|* DeviceWindow des Ausgabegeraetes setzen
|*
\************************************************************************/

/*N*/ void Viewport3D::SetDeviceWindow(const Rectangle& rRect)
/*N*/ {
/*N*/   long nNewW = rRect.GetWidth();
/*N*/   long nNewH = rRect.GetHeight();
/*N*/   long nOldW = aDeviceRect.GetWidth();
/*N*/   long nOldH = aDeviceRect.GetHeight();
/*N*/
/*N*/   switch ( eAspectMapping )
/*N*/   {
/*N*/       double  fRatio, fTmp;
/*N*/
/*N*/       // Mapping, ohne die reale Groesse der Objekte im Device-Window
/*N*/       // zu aendern
/*N*/       case AS_HOLD_SIZE:
/*N*/           // Wenn Device ungueltig (w, h = -1), zunaechst
/*N*/           // View mit AsHoldX anpassen
/*N*/           if ( nOldW > 0 && nOldH > 0 )
/*N*/           {
/*N*/               fRatio = (double) nNewW / nOldW;
/*N*/               aViewWin.X *= fRatio;
/*N*/               aViewWin.W *= fRatio;
/*N*/               fRatio = (double) nNewH / nOldH;
/*N*/               aViewWin.Y *= fRatio;
/*N*/               aViewWin.H *= fRatio;
/*N*/               break;
/*N*/           }
/*N*/       case AS_HOLD_X:
/*N*/           // View-Hoehe an -Breite anpassen
/*N*/           fRatio = (double) nNewH / nNewW;
/*N*/           fTmp = aViewWin.H;
/*N*/           aViewWin.H = aViewWin.W * fRatio;
/*N*/           aViewWin.Y = aViewWin.Y * aViewWin.H / fTmp;
/*N*/           break;
/*N*/
/*N*/       case AS_HOLD_Y:
/*N*/           // View-Breite an -Hoehe anpassen
/*N*/           fRatio = (double) nNewW / nNewH;
/*N*/           fTmp = aViewWin.W;
/*N*/           aViewWin.W = aViewWin.H * fRatio;
/*N*/           aViewWin.X = aViewWin.X * aViewWin.W / fTmp;
/*N*/           break;
/*N*/   }
/*N*/   fWRatio = nNewW / aViewWin.W;
/*N*/   fHRatio = nNewH / aViewWin.H;
/*N*/
/*N*/   aDeviceRect = rRect;
/*N*/ }

/*************************************************************************
|*
|* Beobachterposition (PRP) in Weltkoordinaten zurueckgeben
|*
\************************************************************************/

/*N*/ const Vector3D& Viewport3D::GetViewPoint()
/*N*/ {
/*N*/   MakeTransform();
/*N*/
/*N*/   return aViewPoint;
/*N*/ }

/*************************************************************************
|*
|* Transformationsmatrix zurueckgeben
|*
\************************************************************************/

/*N*/ const Matrix4D& Viewport3D::GetViewTransform()
/*N*/ {
/*N*/   MakeTransform();
/*N*/
/*N*/   return aViewTf;
/*N*/ }

/*************************************************************************
|*
|* uebergebenen Punkt transformieren
|*
\************************************************************************/

//STRIP001 Vector3D& Viewport3D::Transform(Vector3D& rVec)
//STRIP001 {
//STRIP001  MakeTransform();
//STRIP001
//STRIP001  rVec *= aViewTf;
//STRIP001
//STRIP001  return rVec;
//STRIP001 }

/*************************************************************************
|*
|* neuen Punkt transformiert zurueckgeben
|*
\************************************************************************/

//STRIP001 Vector3D Viewport3D::Transformed(const Vector3D& rVec)
//STRIP001 {
//STRIP001  Vector3D aNewVec = rVec;
//STRIP001  Transform(aNewVec);
//STRIP001
//STRIP001  return aNewVec;
//STRIP001 }

/*************************************************************************
|*
|* 3D-Punkt auf Viewplane projizieren
|*
\************************************************************************/

/*N*/ Vector3D& Viewport3D::DoProjection(Vector3D& rVec) const
/*N*/ {
/*N*/   if ( eProjection == PR_PERSPECTIVE )
/*N*/   {
/*N*/       double fPrDist = fVPD - aPRP.Z();
/*N*/
/*N*/       if ( aPRP.Z() == rVec.Z() )
/*?*/           rVec.X() = rVec.Y() = 0;
/*N*/       else
/*N*/       {
            // Das ist die Version fuer beliebigen PRP, wird aber
            // aus Performancegruenden nicht verwendet
/*          double fZDiv = rVec.Z() / fPrDist;
            double fZSub = 1 - fZDiv;
            rVec.X() = (rVec.X() - aPRP.X() * fZDiv) / fZSub;
            rVec.Y() = (rVec.Y() - aPRP.Y() * fZDiv) / fZSub;
*/
/*N*/           fPrDist /= rVec.Z() - aPRP.Z();
/*N*/           rVec.X() *= fPrDist;
/*N*/           rVec.Y() *= fPrDist;
/*N*/       }
/*N*/   }
/*N*/   return rVec;
/*N*/ }

/*************************************************************************
|*
|* 3D-Punkt auf Geraetekoordinaten mappen
|*
\************************************************************************/

/*N*/ Vector3D Viewport3D::MapToDevice(const Vector3D& rVec) const
/*N*/ {
/*N*/   Vector3D aRetval;
/*N*/
/*N*/   // Y-Koordinate subtrahieren, da die Device-Y-Achse von oben
/*N*/   // nach unten verlaeuft
/*N*/   aRetval.X() = (double)aDeviceRect.Left() + ((rVec.X() - aViewWin.X) * fWRatio);
/*N*/   aRetval.Y() = (double)aDeviceRect.Bottom() - ((rVec.Y() - aViewWin.Y) * fHRatio);
/*N*/   aRetval.Z() = rVec.Z();
/*N*/
/*N*/   return aRetval;
/*N*/ }

/*************************************************************************
|*
|* 3D-Punkt auf Viewplane projizieren und auf Geraetekoordinaten mappen
|*
\************************************************************************/

//STRIP001 Vector3D Viewport3D::ProjectAndMap(Vector3D aVec) const
//STRIP001 {
//STRIP001  DoProjection(aVec);
//STRIP001  return MapToDevice(aVec);
//STRIP001 }

/*************************************************************************
|*
|* Device-Werte fuer Breite und Hoehe des Vektors in View-Werte
|* wandeln, abhaengig von der Projektion
|*
\************************************************************************/

//STRIP001 Vector3D Viewport3D::MapSizeToView(const Vector3D& rVec)
//STRIP001 {
//STRIP001  Vector3D aVec(rVec);
//STRIP001  // zuerst von Device in View umrechnen
//STRIP001  aVec.X() /= fWRatio;
//STRIP001  aVec.Y() /= fHRatio;
//STRIP001
//STRIP001  // dann die Perspektivtransformation umkehren
//STRIP001 /*   if ( eProjection == PR_PERSPECTIVE )
//STRIP001  {
//STRIP001      double fPrDist = fVPD - aPRP.Z();
//STRIP001
//STRIP001      if ( aPRP.Z() != aVec.Z() )
//STRIP001      {
//STRIP001          fPrDist /= aVec.Z() - aPRP.Z();
//STRIP001          aVec.X() /= fPrDist;
//STRIP001          aVec.Y() /= fPrDist;
//STRIP001      }
//STRIP001  }
//STRIP001 */   return aVec;
//STRIP001 }

/*************************************************************************
|*
|* View Reference Point setzen
|*
\************************************************************************/

/*N*/ void Viewport3D::SetVRP(const Vector3D& rNewVRP)
/*N*/ {
/*N*/   aVRP = rNewVRP;
/*N*/   bTfValid = FALSE;
/*N*/ }

/*************************************************************************
|*
|* View Plane Normal setzen
|*
\************************************************************************/

/*N*/ void Viewport3D::SetVPN(const Vector3D& rNewVPN)
/*N*/ {
/*N*/   aVPN = rNewVPN;
/*N*/   aVPN.Normalize();
/*N*/   bTfValid = FALSE;
/*N*/ }

/*************************************************************************
|*
|* View Up Vector setzen
|*
\************************************************************************/

/*N*/ void Viewport3D::SetVUV(const Vector3D& rNewVUV)
/*N*/ {
/*N*/   aVUV = rNewVUV;
/*N*/   bTfValid = FALSE;
/*N*/ }

/*************************************************************************
|*
|* Center Of Projection setzen
|*
\************************************************************************/

/*N*/ void Viewport3D::SetPRP(const Vector3D& rNewPRP)
/*N*/ {
/*N*/   aPRP = rNewPRP;
/*N*/   aPRP.X() = 0;
/*N*/   aPRP.Y() = 0;
/*N*/   bTfValid = FALSE;
/*N*/ }

/*************************************************************************
|*
|* View Plane Distance setzen
|*
\************************************************************************/

/*N*/ void Viewport3D::SetVPD(double fNewVPD)
/*N*/ {
/*N*/   fVPD = fNewVPD;
/*N*/   bTfValid = FALSE;
/*N*/ }

/*************************************************************************
|*
|* Abstand der vorderen Clippingebene setzen
|*
\************************************************************************/

//STRIP001 void Viewport3D::SetNearClipDist(double fNewNCD)
//STRIP001 {
//STRIP001  fNearClipDist = fNewNCD;
//STRIP001  bTfValid = FALSE;
//STRIP001 }

/*************************************************************************
|*
|* Abstand der hinteren Clippingebene setzen
|*
\************************************************************************/

//STRIP001 void Viewport3D::SetFarClipDist(double fNewFCD)
//STRIP001 {
//STRIP001  fFarClipDist = fNewFCD;
//STRIP001  bTfValid = FALSE;
//STRIP001 }

/*************************************************************************
|*
|* Stream-Out-Operator fuer Viewport3D (Version 3.1)
|*
\************************************************************************/

/*N*/ void Viewport3D::WriteData31(SvStream& rOut) const
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   rOut << aVRP;
/*N*/   rOut << aVPN;
/*N*/   rOut << aVUV;
/*N*/   rOut << aPRP;
/*N*/   rOut << fVPD;
/*N*/   rOut << fNearClipDist;
/*N*/   rOut << fFarClipDist;
/*N*/   rOut << UINT16(eProjection);
/*N*/   rOut << UINT16(eAspectMapping);
/*N*/   rOut << aDeviceRect;
/*N*/   rOut << aViewWin.X;
/*N*/   rOut << aViewWin.Y;
/*N*/   rOut << aViewWin.W;
/*N*/   rOut << aViewWin.H;
/*N*/ #endif
/*N*/ }

/*************************************************************************
|*
|* Stream-Out-Operator fuer Viewport3D ab File-Revision 13
|* implementiert zum Hauptupdate 355 am 4.2.97 FG (freigegeben ab 356)
|*
\************************************************************************/

/*N*/ void Viewport3D::WriteData(SvStream& rOut) const
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   if (rOut.GetVersion() < 3560)
/*N*/   {
/*N*/       Viewport3D::WriteData31(rOut);
/*N*/       return;
/*N*/   }
/*N*/   SdrDownCompat aCompat(rOut, STREAM_WRITE);
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("Viewport3D");
/*N*/ #endif
/*N*/
/*N*/   rOut << aVRP;
/*N*/   rOut << aVPN;
/*N*/   rOut << aVUV;
/*N*/   rOut << aPRP;
/*N*/   rOut << fVPD;
/*N*/   rOut << fNearClipDist;
/*N*/   rOut << fFarClipDist;
/*N*/   rOut << UINT16(eProjection);
/*N*/   rOut << UINT16(eAspectMapping);
/*N*/   rOut << aDeviceRect;
/*N*/   rOut << aViewWin.X;
/*N*/   rOut << aViewWin.Y;
/*N*/   rOut << aViewWin.W;
/*N*/   rOut << aViewWin.H;
/*N*/ #endif
/*N*/ }

/*************************************************************************
|*
|* Stream-In-Operator fuer Viewport3D fuer die Version 3.1
|*
\************************************************************************/

/*N*/ void Viewport3D::ReadData31(SvStream& rIn)
/*N*/ {
/*N*/   UINT16  nTmp16;
/*N*/
/*N*/   rIn >> aVRP;
/*N*/   rIn >> aVPN;
/*N*/   rIn >> aVUV;
/*N*/   rIn >> aPRP;
/*N*/   rIn >> fVPD;
/*N*/   rIn >> fNearClipDist;
/*N*/   rIn >> fFarClipDist;
/*N*/   rIn >> nTmp16; eProjection = ProjectionType(nTmp16);
/*N*/   rIn >> nTmp16; eAspectMapping = AspectMapType(nTmp16);
/*N*/   rIn >> aDeviceRect;
/*N*/   rIn >> aViewWin.X;
/*N*/   rIn >> aViewWin.Y;
/*N*/   rIn >> aViewWin.W;
/*N*/   rIn >> aViewWin.H;
/*N*/
/*N*/   // es gibt einige Docs mit zweifelhaften werten, daher wird die Dist auf 0 gesetzt
/*N*/   if ((fNearClipDist <= 1e-100) || (fNearClipDist >= 1e100)) fNearClipDist = 0.0;
/*N*/   if ((fFarClipDist <= 1e-100) || (fFarClipDist >= 1e100)) fFarClipDist = 0.0;
/*N*/
/*N*/   fWRatio = aDeviceRect.GetWidth() / aViewWin.W;
/*N*/   fHRatio = aDeviceRect.GetHeight() / aViewWin.H;
/*N*/
/*N*/   bTfValid = FALSE;
/*N*/ }

/*************************************************************************
|*
|* ReadData-Methode fuer Viewport3D, gueltig fuer Filerevisionen ab 13
|* eingecheckt ab Revision 355 am 4.2.97 (FG) (freigegeben ab 356)
|*
\************************************************************************/

/*N*/ void Viewport3D::ReadData(const SdrObjIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   if ((rHead.GetVersion() < 13) || (rIn.GetVersion() < 3560))
/*N*/   {
/*N*/       Viewport3D::ReadData31 (rIn);
/*N*/       return;
/*N*/   }
/*N*/   SdrDownCompat aCompat(rIn, STREAM_READ);
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("Viewport3D");
/*N*/ #endif
/*N*/
/*N*/   UINT16  nTmp16;
/*N*/
/*N*/   rIn >> aVRP;
/*N*/   rIn >> aVPN;
/*N*/   rIn >> aVUV;
/*N*/   rIn >> aPRP;
/*N*/   rIn >> fVPD;
/*N*/   rIn >> fNearClipDist;
/*N*/   rIn >> fFarClipDist;
/*N*/   rIn >> nTmp16; eProjection = ProjectionType(nTmp16);
/*N*/   rIn >> nTmp16; eAspectMapping = AspectMapType(nTmp16);
/*N*/   rIn >> aDeviceRect;
/*N*/   rIn >> aViewWin.X;
/*N*/   rIn >> aViewWin.Y;
/*N*/   rIn >> aViewWin.W;
/*N*/   rIn >> aViewWin.H;
/*N*/
/*N*/   // es gibt einige Docs mit zweifelhaften werten, daher wird die Dist auf 0 gesetzt
/*N*/   if ((fNearClipDist <= 1e-100) || (fNearClipDist >= 1e100)) fNearClipDist = 0.0;
/*N*/   if ((fFarClipDist <= 1e-100) || (fFarClipDist >= 1e100)) fFarClipDist = 0.0;
/*N*/
/*N*/   fWRatio = aDeviceRect.GetWidth() / aViewWin.W;
/*N*/   fHRatio = aDeviceRect.GetHeight() / aViewWin.H;
/*N*/
/*N*/   bTfValid = FALSE;
/*N*/ }


// FG: eigentlich sollten die Stream-Funktionen in der 3D-Engine nicht verwendet werden
//     sondern WriteData und ReadData, da man insbesondere bei ReadData einen
//     zusaetzlichen Parameter hat der die File-Revision enthaelt.

/*************************************************************************
|*
|* Stream-Out-Operator fuer Viewport3D
|*
\************************************************************************/

/*N*/ #ifndef SVX_LIGHT
/*N*/ SvStream& operator<<(SvStream& rOStream, const Viewport3D& rViewpt)
/*N*/ {
/*N*/   rViewpt.WriteData31(rOStream);
/*N*/   return rOStream;
/*N*/ }
/*N*/ #endif

/*************************************************************************
|*
|* Stream-In-Operator fuer Viewport3D
|*
\************************************************************************/

/*N*/ SvStream& operator>>(SvStream& rIStream, Viewport3D& rViewpt)
/*N*/ {
/*N*/   rViewpt.ReadData31(rIStream);
/*N*/   return rIStream;
/*N*/ }


}
