/*************************************************************************
 *
 *  $RCSfile: svx_xline.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 16:52:07 $
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

#pragma hdrstop

#include <stdlib.h>
#include <math.h>
#include <tools/bigint.hxx>
// auto strip #include <tools/poly.hxx>
// auto strip #include <vcl/svapp.hxx>
#include <vcl/virdev.hxx>
#include <vcl/metaact.hxx>
// auto strip #include <vcl/gdimtf.hxx>
// auto strip #include <vcl/gradient.hxx>
// auto strip #include "xpoly.hxx"
#include "xoutx.hxx"

#ifndef INCLUDED_SVTOOLS_COLORCFG_HXX
#include <svtools/colorcfg.hxx>
#endif
namespace binfilter {

#define GLOBALOVERFLOW

/*************************************************************************
|*
|* eine der Haelften einer Bezierkurve berechnen
|*
\************************************************************************/

/*N*/ void SplitBezier(const XPolygon& rBez, XPolygon& rSplit, BOOL bFirstPart)
/*N*/ {
/*N*/   if ( bFirstPart )
/*N*/   {
/*N*/       rSplit[0] = rBez[0];
/*N*/       rSplit[1] = (rBez[0] + rBez[1]) / 2;
/*N*/       rSplit[2] = (rBez[0] + rBez[1] * 2 + rBez[2]) / 4;
/*N*/       rSplit[3] = (rBez[0] + rBez[1] * 3 + rBez[2] * 3 + rBez[3]) / 8;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       rSplit[1] = (rBez[3] + rBez[2] * 2 + rBez[1]) / 4;
/*N*/       rSplit[2] = (rBez[3] + rBez[2]) / 2;
/*N*/       rSplit[3] = rBez[3];
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* pruefen, ob die uebergebene Bezierkurve eine gerade Linie ist
|*
\************************************************************************/

/*N*/ BOOL IsBezierStraight(const XPolygon& rBez)
/*N*/ {
/*N*/   // Point-on-Line-Test nach Graphics Gems I, S. 49f.
/*N*/   long X0 = rBez[0].X(), Y0 = rBez[0].Y();
/*N*/   long X1 = rBez[1].X(), Y1 = rBez[1].Y();
/*N*/   long X2 = rBez[2].X(), Y2 = rBez[2].Y();
/*N*/   long X3 = rBez[3].X(), Y3 = rBez[3].Y();
/*N*/   BigInt DX(X3 - X0);
/*N*/   BigInt DY(Y3 - Y0);
/*N*/   BigInt nAbsDX(DX), nAbsDY(DY);
/*N*/   nAbsDX.Abs();
/*N*/   nAbsDY.Abs();
/*N*/   BigInt nMax(nAbsDX > nAbsDY ? nAbsDX : nAbsDY);
/*N*/   BigInt nCompare;
/*N*/
/*N*/   // Kontrollpunkte auf der (unendlichen) Linie durch P3 und P0?
/*N*/   nCompare = DY * BigInt(X1-X0) - DX * BigInt(Y1-Y0);
/*N*/   nCompare.Abs();
/*N*/   if ( nCompare >= nMax )
/*N*/       return FALSE;
/*N*/
/*N*/   nCompare = DY * BigInt(X2-X0) - DX * BigInt(Y2-Y0);
/*N*/   nCompare.Abs();
/*N*/   if ( nCompare >= nMax )
/*N*/       return FALSE;
/*N*/
/*N*/   //                                                  ____
/*N*/   // wenn ja, dann pruefen, ob ausserhalb der Strecke P3P0
/*N*/   if ( (X3 < X0 && X0 < X1) || (Y3 < Y0 && Y0 < Y1) ) return FALSE;
/*N*/   if ( (X1 < X0 && X0 < X3) || (Y1 < Y0 && Y0 < Y3) ) return FALSE;
/*N*/   if ( (X0 < X3 && X3 < X1) || (Y0 < Y3 && Y3 < Y1) ) return FALSE;
/*N*/   if ( (X1 < X3 && X3 < X0) || (Y1 < Y3 && Y3 < Y3) ) return FALSE;
/*N*/
/*N*/   if ( (X3 < X0 && X0 < X2) || (Y3 < Y0 && Y0 < Y2) ) return FALSE;
/*N*/   if ( (X2 < X0 && X0 < X3) || (Y2 < Y0 && Y0 < Y3) ) return FALSE;
/*N*/   if ( (X0 < X3 && X3 < X2) || (Y0 < Y3 && Y3 < Y2) ) return FALSE;
/*N*/   if ( (X2 < X3 && X3 < X0) || (Y2 < Y3 && Y3 < Y3) ) return FALSE;
/*N*/
/*N*/   return TRUE;
/*N*/ }

/*************************************************************************
|*
|* Bezierkurve durch Iteration bestimmen
|*
\************************************************************************/

/*N*/ void XOutIterateBezier(const XPolygon& rBez, Rectangle& rRect, USHORT nMaxDepth)
/*N*/ {
/*N*/   // Das Folgende Statement ist Optimierung
/*N*/   if (rRect.IsInside(rBez[0]) && rRect.IsInside(rBez[1]) &&
/*N*/       rRect.IsInside(rBez[2]) && rRect.IsInside(rBez[3])) return;
/*N*/
/*N*/   if ( nMaxDepth == 0 || IsBezierStraight(rBez) )
/*N*/   {
/*N*/       long nX = rBez[3].X(),
/*N*/            nY = rBez[3].Y();
/*N*/       rRect.Left()    = Min(nX, rRect.Left());
/*N*/       rRect.Right()   = Max(nX, rRect.Right());
/*N*/       rRect.Top()     = Min(nY, rRect.Top());
/*N*/       rRect.Bottom()  = Max(nY, rRect.Bottom());
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       XPolygon aSplitBez(4);
/*N*/
/*N*/       nMaxDepth--;
/*N*/       SplitBezier(rBez, aSplitBez, TRUE);
/*N*/       XOutIterateBezier(aSplitBez, rRect, nMaxDepth);
/*N*/       aSplitBez[0] = aSplitBez[3];
/*N*/       SplitBezier(rBez, aSplitBez, FALSE);
/*N*/       XOutIterateBezier(aSplitBez, rRect, nMaxDepth);
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|*    XOutputDevice::XOutCalcXPolyExtent()
|*
|*    Beschreibung
|*    Ersterstellung    14.08.95 ESO
|*    Letzte Aenderung  15.08.95 ESO
|*
*************************************************************************/

/*N*/ Rectangle XOutCalcXPolyExtent(const XPolygon& rXPoly, OutputDevice* pOut)
/*N*/ {
/*N*/   if ( rXPoly.GetPointCount() == 0 )
/*?*/       return Rectangle();
/*N*/
/*N*/   USHORT i;
/*N*/   USHORT nPntMax=rXPoly.GetPointCount()-1;
/*N*/
/*N*/   FASTBOOL bHasBezier=FALSE;
/*N*/   Rectangle aRect(rXPoly[0],rXPoly[0]);
/*N*/   // zunaechst das Rect der Stuetzstellen (ohne Kontrollpunkte) bestimmen
/*N*/   Point aPt;
/*N*/   for (i=nPntMax; i>0; i--) {
/*N*/       if (!rXPoly.IsControl(i)) {
/*N*/           aPt=rXPoly[i]; // lokal kopieren fuer bessere Performance
/*N*/           if (aPt.X()<aRect.Left  ()) aRect.Left  ()=aPt.X();
/*N*/           if (aPt.X()>aRect.Right ()) aRect.Right ()=aPt.X();
/*N*/           if (aPt.Y()<aRect.Top   ()) aRect.Top   ()=aPt.Y();
/*N*/           if (aPt.Y()>aRect.Bottom()) aRect.Bottom()=aPt.Y();
/*N*/       } else bHasBezier=TRUE;
/*N*/   }
/*N*/   if (!bHasBezier) return aRect;
/*N*/
/*N*/   if (pOut!=NULL)
/*?*/       aRect = pOut->LogicToPixel(aRect);
/*N*/   i=0;
/*N*/   while ( i < nPntMax )
/*N*/   {
/*N*/       if ( i <= nPntMax - 3 && rXPoly.GetFlags(i+1) == XPOLY_CONTROL )
/*N*/       {
/*N*/           XPolygon aBez(4);
/*N*/
/*N*/           if ( pOut )
/*N*/           {
/*?*/               aBez[0] = pOut->LogicToPixel(rXPoly[i]);
/*?*/               aBez[1] = pOut->LogicToPixel(rXPoly[i+1]);
/*?*/               aBez[2] = pOut->LogicToPixel(rXPoly[i+2]);
/*?*/               aBez[3] = pOut->LogicToPixel(rXPoly[i+3]);
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               aBez[0] = rXPoly[i];
/*N*/               aBez[1] = rXPoly[i+1];
/*N*/               aBez[2] = rXPoly[i+2];
/*N*/               aBez[3] = rXPoly[i+3];
/*N*/           }
/*N*/           XOutIterateBezier(aBez, aRect, 8);
/*N*/           i += 3;
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           Point aPnt(rXPoly[++i]);
/*N*/           if ( pOut )
/*?*/               aPnt = pOut->LogicToPixel(aPnt);
/*N*/
/*N*/           aRect.Left()    = Min(aPnt.X(), aRect.Left());
/*N*/           aRect.Right()   = Max(aPnt.X(), aRect.Right());
/*N*/           aRect.Top()     = Min(aPnt.Y(), aRect.Top());
/*N*/           aRect.Bottom()  = Max(aPnt.Y(), aRect.Bottom());
/*N*/       }
/*N*/   }
/*N*/   if ( pOut )
/*?*/       aRect = pOut->PixelToLogic(aRect);
/*N*/   return aRect;
/*N*/ }

/*************************************************************************
|*
|*    XOutputDevice::CalcBezierStepCount()
|*
|*    Beschreibung
|*    Ersterstellung    08.11.94
|*    Letzte Aenderung  14.12.94 ESO
|*
*************************************************************************/

/*N*/ long XOutCalcBezierStepCount( const XPolygon& rXPoly, USHORT nIndex,
/*N*/                             OutputDevice* pOut, USHORT nRough )
/*N*/ {
/*N*/   long nSteps;
/*N*/
/*N*/   if( pOut || nRough )
/*N*/   {
/*N*/       const Point& aPt = rXPoly[ nIndex++ ];
/*N*/       const Point& aPt1 = rXPoly[ nIndex++ ];
/*N*/       const Point& aPt2 = rXPoly[ nIndex++ ];
/*N*/       const Point& aPt3 = rXPoly[ nIndex ];
/*N*/       long nDx1 = Abs( aPt1.X() - aPt.X() ) * 2;
/*N*/       long nDy1 = Abs( aPt1.Y() - aPt.Y() ) * 2;
/*N*/       long nDx2 = Abs( aPt3.X() - aPt2.X() ) * 2;
/*N*/       long nDy2 = Abs( aPt3.Y() - aPt2.Y() ) * 2;
/*N*/       long nDxHndl = Abs( aPt2.X() - aPt1.X() );
/*N*/       long nDyHndl = Abs( aPt2.Y() - aPt1.Y() );
/*N*/
/*N*/       long nDelta = Max(Max(nDx1, nDy1), Max(nDx2, nDy2));
/*N*/       nDelta = Max(nDelta, Max(nDxHndl, nDyHndl));
/*N*/       if( pOut )
/*N*/           nDelta = pOut->LogicToPixel(Size(nDelta, 0)).Width();
/*N*/       if( nRough )
/*N*/           nSteps = nDelta / nRough + 4;
/*N*/       else
/*N*/           nSteps = nDelta / 25 + 4;
/*N*/   }
/*N*/   else nSteps = 10;
/*N*/
/*N*/   return nSteps;
/*N*/ }


/*************************************************************************
|*
|*    XOutputDevice::CalcBezier()
|*
|*    Beschreibung
|*    Ersterstellung    08.11.94
|*    Letzte Aenderung  14.12.94 ESO
|*
*************************************************************************/

/*N*/ void XOutCalcBezier( const XPolygon& rXPoly, USHORT nBezIndex, Polygon& rPoly,
/*N*/                    USHORT nPolyIndex, long nSteps )
/*N*/ {
/*N*/   if ( nPolyIndex > XPOLY_MAXPOINTS )
/*N*/   {
/*N*/       return;
/*N*/   }
/*N*/
/*N*/   double nX;
/*N*/   double nY;
/*N*/   double nX0, nX1, nX2, nX3;
/*N*/   double nY0, nY1, nY2, nY3;
/*N*/
/*N*/   long nDiff = nSteps - 1;
/*N*/   long nDiv = nSteps * nSteps * nSteps;
/*N*/   rPoly[nPolyIndex++] = rXPoly[nBezIndex];
/*N*/
/*N*/   nX0 = rXPoly[nBezIndex  ].X();
/*N*/   nY0 = rXPoly[nBezIndex++].Y();
/*N*/   nX1 = rXPoly[nBezIndex  ].X() * 3;
/*N*/   nY1 = rXPoly[nBezIndex++].Y() * 3;
/*N*/   nX2 = rXPoly[nBezIndex  ].X() * 3;
/*N*/   nY2 = rXPoly[nBezIndex++].Y() * 3;
/*N*/   nX3 = rXPoly[nBezIndex  ].X();
/*N*/   nY3 = rXPoly[nBezIndex  ].Y();
/*N*/
/*N*/   for (long nStep = 1; nStep < nSteps; nStep++, nDiff--, nPolyIndex++)
/*N*/   {
/*N*/       long nAcc = nDiff * nDiff * nDiff;
/*N*/
/*N*/       nX = nX0 * nAcc;
/*N*/       nY = nY0 * nAcc;
/*N*/       nAcc = nAcc / nDiff * nStep;
/*N*/       nX += nX1 * nAcc;
/*N*/       nY += nY1 * nAcc;
/*N*/       nAcc = nAcc / nDiff * nStep;
/*N*/       nX += nX2 * nAcc;
/*N*/       nY += nY2 * nAcc;
/*N*/       nAcc = nAcc / nDiff * nStep;
/*N*/       nX += nX3 * nAcc;
/*N*/       nY += nY3 * nAcc;
/*N*/
/*N*/       rPoly[nPolyIndex].X() = (long) (nX / nDiv);
/*N*/       rPoly[nPolyIndex].Y() = (long) (nY / nDiv);
/*N*/   }
/*N*/   rPoly[nPolyIndex] = rXPoly[nBezIndex];
/*N*/ }

/*************************************************************************
|*
|*    XOutputDevice::CreatePolygon()
|*
|*    Beschreibung
|*    Ersterstellung    09.11.94
|*    Letzte Aenderung  14.12.94
|*
*************************************************************************/

/*N*/ Polygon XOutCreatePolygon( const XPolygon& rXPoly, OutputDevice* pOut,
/*N*/                          USHORT nRough )
/*N*/ {
/*N*/   if ( rXPoly.GetPointCount() == 0 )
/*N*/       return Polygon(0);
/*N*/
/*N*/   USHORT i = 0;
/*N*/   ULONG  nPolySize = 1;
/*N*/   USHORT nPntMax = rXPoly.GetPointCount()-1;
/*N*/
/*N*/   while (i<nPntMax) {
/*N*/       if (i+3<=nPntMax && rXPoly.IsControl(i+1)) {
/*N*/ #ifdef DGB_UTIL
/*N*/           // am 14.2.1997 von Joe
/*N*/           if (!rXPoly.IsControl(i+2)) {
/*N*/               ByteString aMsg("XOutCreatePolygon(): Fehlender Kontrollpunkt an Position ");
/*N*/               aMsg += i+2;
/*N*/               aMsg += ". Stattdessen ist dort eine normale Stuetzstelle.";
/*N*/               DGB_ERROR(aMsg.GetBuffer());
/*N*/           }
/*N*/           if (rXPoly.IsControl(i+3)) {
/*N*/               ByteString aMsg("XOutCreatePolygon(): Fehlende Stuetzstelle an Position ");
/*N*/               aMsg += i+3;
/*N*/               aMsg += ". Stattdessen ist dort ein Kontrollpunkt.";
/*N*/               DGB_ERROR(aMsg.GetBuffer());
/*N*/           }
/*N*/ #endif
/*N*/           nPolySize+=(USHORT)XOutCalcBezierStepCount(rXPoly,i,pOut,nRough);
/*N*/           i+=3;
/*N*/       } else {
/*N*/           nPolySize++;
/*N*/           i++;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if ( nPolySize > XPOLY_MAXPOINTS )
/*N*/       nPolySize = XPOLY_MAXPOINTS;
/*N*/
/*N*/   Polygon aPoly( (USHORT) nPolySize );
/*N*/   USHORT  nPolyPos = 0, nPolyPosMax = nPolySize - 1;
/*N*/
/*N*/     aPoly[ 0 ] = rXPoly[ i = 0 ];
/*N*/
/*N*/   while( i < nPntMax && nPolyPos < nPolySize )
/*N*/   {
/*N*/       if( i + 3 <= nPntMax && rXPoly.GetFlags( i + 1 ) == XPOLY_CONTROL )
/*N*/       {
/*N*/           USHORT nSteps = (USHORT) XOutCalcBezierStepCount( rXPoly, i, pOut, nRough );
/*N*/
/*N*/             if( nPolyPos + nSteps >= (USHORT) nPolySize )
/*N*/               nSteps = (USHORT)( nPolySize - nPolyPos - 1 );
/*N*/
/*N*/             XOutCalcBezier( rXPoly, i, aPoly, nPolyPos, nSteps );
/*N*/           nPolyPos += (USHORT) nSteps;
/*N*/           i += 3;
/*N*/       }
/*N*/       else if( nPolyPos < nPolyPosMax )
/*N*/           aPoly[ ++nPolyPos ] = rXPoly[ ++i ];
/*N*/   }
/*N*/
/*N*/   return aPoly;
/*N*/ }

/*N*/ Polygon XOutCreatePolygonBezier( const XPolygon& rXPoly, OutputDevice* pOut )
/*N*/ {
/*N*/   sal_uInt16 i, nPtCount = rXPoly.GetPointCount();
/*N*/   Polygon aPoly( nPtCount );
/*N*/   for ( i = 0; i < nPtCount; i++ )
/*N*/   {
/*N*/       aPoly[ i ] = rXPoly[ i ];
/*N*/         aPoly.SetFlags( i, (PolyFlags)( rXPoly.GetFlags( i ) ) );
/*N*/   }
/*N*/   return aPoly;
/*N*/ }

//STRIP001 PolyPolygon XOutCreatePolyPolygonBezier( const XPolyPolygon& rXPolyPoly, OutputDevice* pOut )
//STRIP001 {
//STRIP001  PolyPolygon aPolyPoly;
//STRIP001
//STRIP001  USHORT  nCount = rXPolyPoly.Count(), i;
//STRIP001
//STRIP001  for( i = 0; i < nCount; i++ )
//STRIP001  {
//STRIP001      if( rXPolyPoly[i].GetPointCount() > 0 )
//STRIP001          aPolyPoly.Insert(XOutCreatePolygonBezier(rXPolyPoly[i], pOut));
//STRIP001  }
//STRIP001
//STRIP001  return aPolyPoly;
//STRIP001 }

/*************************************************************************
|*
|*    Parameterklassse fuer dicke Linien mit Linienmuster
|*
\************************************************************************/

/*N*/ class XLineParam
/*N*/ {
/*N*/  public:
/*N*/   long    nPatSeg;
/*N*/   long    nPatRemain;
/*N*/   BOOL    bHasJoin, bUseJoin3;
/*N*/   Point   aJoin1, aJoin2, aJoin3;
/*N*/   double  fLength;
/*N*/   long    nLineDx, nLineDy;
/*N*/   long    nDxW, nDyW;
/*N*/
/*N*/   XLineParam() {}
/*N*/
/*N*/   void Init(const Point& rP1, const Point& rP2, long nWidth);
/*N*/ };

/*N*/ void XLineParam::Init(const Point& rP1, const Point& rP2, long nWidth)
/*N*/ {
/*N*/   double fWidth, fRound;
/*N*/
/*N*/   nPatSeg = -1;
/*N*/   nPatRemain = 0;
/*N*/   bHasJoin = FALSE;
/*N*/   bUseJoin3 = FALSE;
/*N*/   nLineDx = rP2.X() - rP1.X();
/*N*/   nLineDy = rP2.Y() - rP1.Y();
/*N*/   fLength = sqrt((double) nLineDx * nLineDx + (double) nLineDy * nLineDy);
/*N*/   if ( fLength > 0 )
/*N*/       fWidth = nWidth / fLength;
/*N*/   if ( nLineDy >= 0 ) fRound =  0.5;
/*N*/   else                fRound = -0.5;
/*N*/   nDxW =   (long) (fWidth * nLineDy + fRound);
/*N*/   if ( nLineDx >= 0 ) fRound =  0.5;
/*N*/   else                fRound = -0.5;
/*N*/   nDyW = - (long) (fWidth * nLineDx + fRound);
/*N*/
/*N*/   aJoin1.X() = rP2.X() + nDxW / 2;
/*N*/   aJoin1.Y() = rP2.Y() + nDyW / 2;
/*N*/   aJoin2 = aJoin1;
/*N*/   aJoin2.X() -= nDxW;
/*N*/   aJoin2.Y() -= nDyW;
/*N*/   aJoin3 = aJoin1;
/*N*/ }

/*************************************************************************
|*
|*    XOutputDevice::CalcFatLineJoin()
|*
|*    Beschreibung      Uebergang zwischen zwei Linien eines Polygons
|*                      berechnen
|*    Ersterstellung    02.12.94
|*    Letzte Aenderung  09.01.95
|*
\************************************************************************/

//STRIP001 void XOutputDevice::CalcFatLineJoin(const Point& rEnd, const Point& rNext,
//STRIP001                                  XLineParam& rParam)
//STRIP001 {
//STRIP001  long nNextDx = rNext.X() - rEnd.X();
//STRIP001  long nNextDy = rNext.Y() - rEnd.Y();
//STRIP001
//STRIP001  if ( nNextDx || nNextDy )
//STRIP001  {
//STRIP001      double fRound;
//STRIP001      long nJoinDx, nJoinDy;
//STRIP001      BOOL bFlatJoin = FALSE;
//STRIP001      BOOL bResetJoin = FALSE;
//STRIP001
//STRIP001      double fNextLen = sqrt((double) nNextDx * nNextDx +
//STRIP001                             (double) nNextDy * nNextDy);
//STRIP001
//STRIP001      // Berechnung des Anschlussuebergangs durch Auswertung
//STRIP001      // der Seitenverhaeltnisse in den Uebergangsdreiecken
//STRIP001      long nPrevDxW = rParam.nDxW;
//STRIP001      long nPrevDyW = rParam.nDyW;
//STRIP001
//STRIP001      double fWidth = (double) nLineWidth / fNextLen;
//STRIP001      if ( nNextDy >= 0 ) fRound =  0.5;
//STRIP001      else                fRound = -0.5;
//STRIP001      long nNextDxW =   (long) (fWidth * nNextDy + fRound);
//STRIP001      if ( nNextDx >= 0 ) fRound =  0.5;
//STRIP001      else                fRound = -0.5;
//STRIP001      long nNextDyW = - (long) (fWidth * nNextDx + fRound);
//STRIP001      long nDxA = nNextDxW - nPrevDxW;
//STRIP001      long nDyA = nNextDyW - nPrevDyW;
//STRIP001      long nDxU = nPrevDxW + nNextDxW;
//STRIP001      long nDyU = nPrevDyW + nNextDyW;
//STRIP001      double fJoin = nDxA * nDxA + nDyA * nDyA;
//STRIP001      double fULen = nDxU * nDxU + nDyU * nDyU;
//STRIP001
//STRIP001      if ( fULen > 0 )    fJoin = sqrt(fJoin / fULen) / 2;
//STRIP001      else                fJoin = 0;
//STRIP001
//STRIP001      if ( fJoin > 0.7 )
//STRIP001      {
//STRIP001          double fJoinLen = fJoin * nLineWidth;
//STRIP001          double fLen = rParam.fLength < fNextLen ? rParam.fLength : fNextLen;
//STRIP001
//STRIP001          if ( fJoinLen > fLen )
//STRIP001          {
//STRIP001              fJoin = 0;
//STRIP001              if ( fLen == rParam.fLength )
//STRIP001                  bResetJoin = TRUE;
//STRIP001          }
//STRIP001          bFlatJoin = TRUE;
//STRIP001      }
//STRIP001
//STRIP001      if ( nPrevDyW >= 0 )    fRound =  0.5;
//STRIP001      else                    fRound = -0.5;
//STRIP001      nJoinDx = -(long) (fJoin * nPrevDyW + fRound);
//STRIP001
//STRIP001      if ( nPrevDxW >= 0 )    fRound =  0.5;
//STRIP001      else                    fRound = -0.5;
//STRIP001      nJoinDy = (long) (fJoin * nPrevDxW + fRound);
//STRIP001
//STRIP001      // mit Vektorprodukt feststellen, ob Anschlusslinie links oder rechts
//STRIP001      // von der ersten Linie verlaeuft; < 0 -> links
//STRIP001      BOOL bLeftTurn =( (rParam.nLineDx * nNextDy -
//STRIP001                         rParam.nLineDy * nNextDx) < 0 );
//STRIP001
//STRIP001      if ( bLeftTurn )
//STRIP001      {
//STRIP001          nJoinDx = - nJoinDx;
//STRIP001          nJoinDy = - nJoinDy;
//STRIP001      }
//STRIP001      rParam.bUseJoin3 = FALSE;
//STRIP001
//STRIP001      if ( bFlatJoin )
//STRIP001      {
//STRIP001          if ( bLeftTurn )
//STRIP001          {
//STRIP001              rParam.aJoin3 = rParam.aJoin1;
//STRIP001              rParam.aJoin1 = rParam.aJoin2;
//STRIP001              if ( bResetJoin )
//STRIP001                  rParam.aJoin3 = rParam.aJoin2;
//STRIP001              else
//STRIP001              {
//STRIP001                  rParam.aJoin3.X() += nJoinDx;
//STRIP001                  rParam.aJoin3.Y() += nJoinDy;
//STRIP001              }
//STRIP001              rParam.aJoin2.X() = rEnd.X() - nNextDxW / 2;
//STRIP001              rParam.aJoin2.Y() = rEnd.Y() - nNextDyW / 2;
//STRIP001              rParam.bUseJoin3 = TRUE;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              if ( bResetJoin )
//STRIP001                  rParam.aJoin2 = rParam.aJoin1;
//STRIP001              else
//STRIP001              {
//STRIP001                  rParam.aJoin2.X() -= nJoinDx;
//STRIP001                  rParam.aJoin2.Y() -= nJoinDy;
//STRIP001              }
//STRIP001              rParam.aJoin3.X() = rEnd.X() + nNextDxW / 2;
//STRIP001              rParam.aJoin3.Y() = rEnd.Y() + nNextDyW / 2;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          rParam.aJoin1.X() += nJoinDx;
//STRIP001          rParam.aJoin1.Y() += nJoinDy;
//STRIP001          rParam.aJoin2.X() -= nJoinDx;
//STRIP001          rParam.aJoin2.Y() -= nJoinDy;
//STRIP001          rParam.aJoin3 = rParam.aJoin1;
//STRIP001      }
//STRIP001      rParam.bHasJoin = TRUE;
//STRIP001
//STRIP001      rParam.fLength = fNextLen;
//STRIP001      rParam.nLineDx = nNextDx;
//STRIP001      rParam.nLineDy = nNextDy;
//STRIP001      rParam.nDxW = nNextDxW;
//STRIP001      rParam.nDyW = nNextDyW;
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*    XOutputDevice::DrawStartEndPoly()
|*
|*    Linienanfang- bzw. -endpolygon zeichnen
|*    Ersterstellung    17.01.95 ESO
|*    Letzte Aenderung  18.01.95 ESO
|*
\************************************************************************/

//STRIP001 void XOutputDevice::DrawStartEndPoly(const Point& rPos,
//STRIP001                                   const XPolygon& rXPoly,
//STRIP001                                   const XLineParam& rParam)
//STRIP001 {
//STRIP001  XPolygon    aXPoly(rXPoly);
//STRIP001  Polygon     aPoly;
//STRIP001
//STRIP001
//STRIP001  if ( rParam.fLength )
//STRIP001      aXPoly.Rotate(Point(0,0), (double) rParam.nLineDx / rParam.fLength,
//STRIP001                                (double) rParam.nLineDy / rParam.fLength);
//STRIP001  aXPoly.Translate(rPos);
//STRIP001  aPoly = XOutCreatePolygon(aXPoly, pOut);
//STRIP001  pOut->DrawPolygon(aPoly);
//STRIP001 }

/*************************************************************************
|*
|*    XOutputDevice::DrawLineStartEnd()
|*
|*    Linienanfang bzw. -ende eines Polygons zeichnen
|*    Ersterstellung    18.01.95 ESO
|*    Letzte Aenderung  20.01.95 ESO
|*
\************************************************************************/

//STRIP001 void XOutputDevice::DrawLineStartEnd(const Polygon& rPoly)
//STRIP001 {
//STRIP001  Point   aDiff;
//STRIP001  USHORT  nPntMax = rPoly.GetSize() - 1;
//STRIP001  USHORT  i = 0;
//STRIP001
//STRIP001  if ( bLineStart || bLineEnd )
//STRIP001  {   // Linien mit Laenge 0 nicht beruecksichtigen
//STRIP001      while ( i < nPntMax )
//STRIP001      {
//STRIP001          aDiff = rPoly[i+1] - rPoly[i];
//STRIP001          if ( aDiff.X() || aDiff.Y() )
//STRIP001              break;
//STRIP001          i++;
//STRIP001      }
//STRIP001      while ( nPntMax > i )
//STRIP001      {
//STRIP001          aDiff = rPoly[nPntMax] - rPoly[0];
//STRIP001          if ( aDiff.X() || aDiff.Y() )
//STRIP001              break;
//STRIP001          nPntMax--;
//STRIP001      }
//STRIP001      if ( i < nPntMax )
//STRIP001      {
//STRIP001          XLineParam  aLineParam;
//STRIP001          const Color aLineColor( pOut->GetLineColor() );
//STRIP001          const Color aFillColor( pOut->GetFillColor() );
//STRIP001
//STRIP001          pOut->SetLineColor();
//STRIP001          pOut->SetFillColor( aLineColor );
//STRIP001
//STRIP001          if( bLineStart )
//STRIP001          {
//STRIP001              aLineParam.Init(rPoly[i], rPoly[i+1], 1);
//STRIP001              DrawStartEndPoly(rPoly[i], aLineStartPoly, aLineParam);
//STRIP001          }
//STRIP001          if ( bLineEnd )
//STRIP001          {
//STRIP001              aLineParam.Init(rPoly[nPntMax], rPoly[nPntMax-1], 1);
//STRIP001              DrawStartEndPoly(rPoly[nPntMax], aLineEndPoly, aLineParam);
//STRIP001          }
//STRIP001
//STRIP001          pOut->SetFillColor( aFillColor );
//STRIP001          pOut->SetLineColor( aLineColor );
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*    XOutputDevice::DrawFatLine()
|*
|*    Beschreibung      Dicke Linie mit oder ohne Linienstile zeichnen
|*    Ersterstellung    28.11.94
|*    Letzte Aenderung  09.10.95
|*
\************************************************************************/

//STRIP001 void XOutputDevice::DrawFatLine(const Point& rStart, const Point& rEnd,
//STRIP001                          const Point* pNext, XLineParam& rParam)
//STRIP001 {
//STRIP001  Polygon aPoly(5);
//STRIP001  BOOL    bLineComplete = FALSE;
//STRIP001
//STRIP001  long nLineDx = rParam.nLineDx;
//STRIP001  long nLineDy = rParam.nLineDy;
//STRIP001  double fLength = rParam.fLength;
//STRIP001
//STRIP001  long nDxW = rParam.nDxW;
//STRIP001  long nDyW = rParam.nDyW;
//STRIP001
//STRIP001  double  fDx = 0, fDy = 0;
//STRIP001  long    nDx, nDy;
//STRIP001  long    nSeg = rParam.nPatSeg;
//STRIP001  long    nPattern;
//STRIP001
//STRIP001  // Linienmuster vorhanden?
//STRIP001  if ( !pLinePattern )
//STRIP001  {
//STRIP001      nPattern = -1;
//STRIP001      nSeg = 0;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // Angefangenes Segment zu Ende zeichnen?
//STRIP001      if ( rParam.nPatRemain )
//STRIP001          nPattern = rParam.nPatRemain;
//STRIP001      else    // sonst naechstes Segment
//STRIP001      {
//STRIP001          nSeg++;
//STRIP001          if ( pLinePattern[nSeg] == 0 )  nSeg = 0;
//STRIP001          nPattern = pLinePattern[nSeg];
//STRIP001      }
//STRIP001  }
//STRIP001  aPoly[0].X() = rStart.X() + nDxW / 2;
//STRIP001  aPoly[0].Y() = rStart.Y() + nDyW / 2;
//STRIP001  aPoly[1].X() = aPoly[0].X() - nDxW;
//STRIP001  aPoly[1].Y() = aPoly[0].Y() - nDyW;
//STRIP001  aPoly[2] = aPoly[1];
//STRIP001  aPoly[3] = aPoly[0];
//STRIP001  aPoly[4] = aPoly[0];
//STRIP001  // An vorheriges Segment anschliessen?
//STRIP001  if ( rParam.bHasJoin )
//STRIP001  {
//STRIP001      aPoly[0] = rParam.aJoin1;
//STRIP001      aPoly[1] = rParam.aJoin2;
//STRIP001      aPoly[4] = rParam.aJoin3;
//STRIP001  }
//STRIP001  // Punkte zum Testen auf erreichen des Linienendes
//STRIP001  Point SegStart = rStart;
//STRIP001  Point SegEnd   = rStart;
//STRIP001
//STRIP001  // Anschlusspunkte zunaechst im rechten Winkel an das Linienende
//STRIP001  rParam.aJoin1.X() = rEnd.X() + nDxW / 2;
//STRIP001  rParam.aJoin1.Y() = rEnd.Y() + nDyW / 2;
//STRIP001  rParam.aJoin2 = rParam.aJoin1;
//STRIP001  rParam.aJoin2.X() -= nDxW;
//STRIP001  rParam.aJoin2.Y() -= nDyW;
//STRIP001  rParam.bHasJoin = FALSE;
//STRIP001  rParam.bUseJoin3 = FALSE;
//STRIP001
//STRIP001  // Anschlusslinie vorhanden?
//STRIP001  if ( pNext )
//STRIP001      CalcFatLineJoin(rEnd, *pNext, rParam);
//STRIP001
//STRIP001  while ( !bLineComplete )
//STRIP001  {
//STRIP001      double fSegLength;
//STRIP001      // nPattern < 0: durchgehende Linie
//STRIP001      if ( nPattern < 0 ) fSegLength = 1.0;
//STRIP001      else                fSegLength = (double) nPattern / fLength;
//STRIP001      fDx += fSegLength * nLineDx;
//STRIP001      fDy += fSegLength * nLineDy;
//STRIP001      nDx = (long) fDx;
//STRIP001      nDy = (long) fDy;
//STRIP001      fDx -= nDx;     // Rundungsfehler ausgleichen
//STRIP001      fDy -= nDy;
//STRIP001      aPoly[2].X() += nDx;
//STRIP001      aPoly[2].Y() += nDy;
//STRIP001      aPoly[3].X() += nDx;
//STRIP001      aPoly[3].Y() += nDy;
//STRIP001      SegEnd.X() += nDx;
//STRIP001      SegEnd.Y() += nDy;
//STRIP001
//STRIP001      // wenn das rEnde ueberschritten wurde, hat das Vorzeichen
//STRIP001      // der Abstaende vom rEndpunkt gewechselt; durch Xor-Verknuepfung
//STRIP001      // wird dieser Wechsel festgestellt
//STRIP001      long nEndDiffX = (SegEnd.X() - rEnd.X());
//STRIP001      long nEndDiffY = (SegEnd.Y() - rEnd.Y());
//STRIP001
//STRIP001      if ( (nEndDiffX ^ (SegStart.X() - rEnd.X())) < 0 ||
//STRIP001           (nEndDiffY ^ (SegStart.Y() - rEnd.Y())) < 0 ||
//STRIP001           (!nEndDiffX && !nEndDiffY) )
//STRIP001      {
//STRIP001          if ( nDx || nDy )
//STRIP001          {
//STRIP001              if ( Abs(nDx) >= Abs(nDy) )
//STRIP001              {
//STRIP001                  long nDiffX = SegEnd.X() - rEnd.X();
//STRIP001                  rParam.nPatRemain = nPattern * nDiffX / nDx;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  long nDiffY = SegEnd.Y() - rEnd.Y();
//STRIP001                  rParam.nPatRemain = nPattern * nDiffY / nDy;
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001              rParam.nPatRemain = 0;
//STRIP001
//STRIP001          rParam.nPatSeg = nSeg;
//STRIP001          if ( rParam.bUseJoin3 )
//STRIP001          {
//STRIP001              aPoly[2] = rParam.aJoin1;
//STRIP001              aPoly[3] = rParam.aJoin3;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              aPoly[2] = rParam.aJoin2;
//STRIP001              aPoly[3] = rParam.aJoin1;
//STRIP001          }
//STRIP001          bLineComplete = TRUE;
//STRIP001      }
//STRIP001      if ( !(nSeg & 0x1) )
//STRIP001          pOut->DrawPolygon(aPoly);
//STRIP001
//STRIP001      aPoly[0] = aPoly[3];
//STRIP001      aPoly[1] = aPoly[2];
//STRIP001      aPoly[4] = aPoly[0];
//STRIP001      SegStart = SegEnd;
//STRIP001
//STRIP001      if ( pLinePattern )
//STRIP001      {
//STRIP001          nSeg++;
//STRIP001          if ( pLinePattern[nSeg] == 0 )
//STRIP001              nSeg = 0;
//STRIP001          nPattern = pLinePattern[nSeg];
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*    XOutputDevice::DrawPatternLine()
|*
|*    Beschreibung      Haarlinie mit Linienstil zeichnen
|*    Ersterstellung    13.08.95 ESO
|*    Letzte Aenderung  14.08.95 ESO
|*
\************************************************************************/

//STRIP001 void XOutputDevice::DrawPatternLine(const Point& rStart, const Point& rEnd,
//STRIP001                                  XLineParam& rParam)
//STRIP001 {
//STRIP001  Point   aP1, aP2;
//STRIP001  BOOL    bLineComplete = FALSE;
//STRIP001
//STRIP001  long    nLineDx = rParam.nLineDx;
//STRIP001  long    nLineDy = rParam.nLineDy;
//STRIP001  double  fLength = rParam.fLength;
//STRIP001
//STRIP001  long    nDxW = rParam.nDxW;
//STRIP001  long    nDyW = rParam.nDyW;
//STRIP001
//STRIP001  double  fDx = 0, fDy = 0;
//STRIP001  long    nDx, nDy;
//STRIP001  long    nSeg = rParam.nPatSeg;
//STRIP001  long    nPattern;
//STRIP001
//STRIP001  // Linienmuster vorhanden?
//STRIP001  if ( !pLinePattern )
//STRIP001  {
//STRIP001      nPattern = -1;
//STRIP001      nSeg = 0;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // Angefangenes Segment zu Ende zeichnen?
//STRIP001      if ( rParam.nPatRemain )
//STRIP001          nPattern = rParam.nPatRemain;
//STRIP001      else    // sonst naechstes Segment
//STRIP001      {
//STRIP001          nSeg++;
//STRIP001          if ( pLinePattern[nSeg] == 0 )  nSeg = 0;
//STRIP001          nPattern = pLinePattern[nSeg];
//STRIP001      }
//STRIP001  }
//STRIP001  // Punkte fuer DrawLine initialisieren
//STRIP001  aP1 = rStart;
//STRIP001  aP2 = aP1;
//STRIP001
//STRIP001  // Punkte zum Testen auf erreichen des Linienendes
//STRIP001  Point SegStart = rStart;
//STRIP001  Point SegEnd   = rStart;
//STRIP001
//STRIP001  while ( !bLineComplete )
//STRIP001  {
//STRIP001      double fSegLength;
//STRIP001      // nPattern < 0: durchgehende Linie
//STRIP001      if ( nPattern < 0 ) fSegLength = 1.0;
//STRIP001      else                fSegLength = (double) nPattern / fLength;
//STRIP001      fDx += fSegLength * nLineDx;
//STRIP001      fDy += fSegLength * nLineDy;
//STRIP001      nDx = (long) fDx;
//STRIP001      nDy = (long) fDy;
//STRIP001      fDx -= nDx;     // Rundungsfehler ausgleichen
//STRIP001      fDy -= nDy;
//STRIP001      aP2.X() += nDx;
//STRIP001      aP2.Y() += nDy;
//STRIP001      SegEnd.X() += nDx;
//STRIP001      SegEnd.Y() += nDy;
//STRIP001
//STRIP001      // wenn das Ende ueberschritten wurde, hat das Vorzeichen
//STRIP001      // der Abstaende vom Endpunkt gewechselt; durch Xor-Verknuepfung
//STRIP001      // wird dieser Wechsel festgestellt
//STRIP001      long nEndDiffX = (SegEnd.X() - rEnd.X());
//STRIP001      long nEndDiffY = (SegEnd.Y() - rEnd.Y());
//STRIP001
//STRIP001      if ( (nEndDiffX ^ (SegStart.X() - rEnd.X())) < 0 ||
//STRIP001           (nEndDiffY ^ (SegStart.Y() - rEnd.Y())) < 0 ||
//STRIP001           (!nEndDiffX && !nEndDiffY) )
//STRIP001      {
//STRIP001          if ( nDx || nDy )
//STRIP001          {
//STRIP001              if ( Abs(nDx) >= Abs(nDy) )
//STRIP001              {
//STRIP001                  long nDiffX = SegEnd.X() - rEnd.X();
//STRIP001                  rParam.nPatRemain = nPattern * nDiffX / nDx;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  long nDiffY = SegEnd.Y() - rEnd.Y();
//STRIP001                  rParam.nPatRemain = nPattern * nDiffY / nDy;
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001              rParam.nPatRemain = 0;
//STRIP001
//STRIP001          rParam.nPatSeg = nSeg;
//STRIP001          aP2 = rEnd;
//STRIP001          bLineComplete = TRUE;
//STRIP001      }
//STRIP001      if ( !(nSeg & 0x1) )
//STRIP001      {
//STRIP001          pOut->DrawLine(aP1, aP2);
//STRIP001      }
//STRIP001
//STRIP001      aP1 = aP2;
//STRIP001      SegStart = SegEnd;
//STRIP001
//STRIP001      if ( pLinePattern )
//STRIP001      {
//STRIP001          nSeg++;
//STRIP001          if ( pLinePattern[nSeg] == 0 )
//STRIP001              nSeg = 0;
//STRIP001          nPattern = pLinePattern[nSeg];
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*    XOutputDevice::DrawLinePolygon()
|*
|*    Beschreibung      Polygon-Linie (ggf. mit Linienmuster) zeichnen
|*    Ersterstellung    28.11.94
|*    Letzte Aenderung  09.10.95 ESO
|*
\************************************************************************/

/*N*/ void XOutputDevice::DrawLinePolygon( const Polygon& rPoly, BOOL bClosePoly )
/*N*/ {
/*N*/   if( nLineTransparence )
/*N*/   {
/*?*/       GDIMetaFile     aMtf;
/*?*/       VirtualDevice   aVDev;
/*?*/       OutputDevice*   pOldOut = pOut;
/*?*/       MapMode         aMap( pOldOut->GetMapMode() );
/*?*/       const BYTE      cTrans = nLineTransparence * 255 / 100;
/*?*/       const Color     aTrans( cTrans, cTrans, cTrans );
/*?*/       Gradient        aTransGradient( GRADIENT_LINEAR, aTrans, aTrans );
/*?*/
/*?*/       pOut = &aVDev;
/*?*/       aVDev.EnableOutput( FALSE );
/*?*/       aVDev.SetMapMode( pOldOut->GetMapMode() );
/*?*/       aMtf.Record( &aVDev );
/*?*/       aVDev.SetLineColor( pOldOut->GetLineColor() );
/*?*/       aVDev.SetFillColor( pOldOut->GetFillColor() );
/*?*/       aVDev.SetFont( pOldOut->GetFont() );
/*?*/       aVDev.SetDrawMode( pOldOut->GetDrawMode() );
/*?*/       aVDev.SetRefPoint( pOldOut->GetRefPoint() );
/*?*/       ImpDrawLinePolygon( rPoly, bClosePoly );
/*?*/       aMtf.Stop();
/*?*/       pOut = pOldOut;
/*?*/
/*?*/       Rectangle aBound;
/*?*/
/*?*/       for( MetaAction* pAct = aMtf.FirstAction(); pAct; pAct = aMtf.NextAction() )
/*?*/       {
/*?*/           if( pAct->GetType() == META_POLYGON_ACTION )
/*?*/               aBound.Union( ( (MetaPolygonAction*) pAct )->GetPolygon().GetBoundRect() );
/*?*/           else if( pAct->GetType() == META_POLYLINE_ACTION )
/*?*/               aBound.Union( ( (MetaPolyLineAction*) pAct )->GetPolygon().GetBoundRect() );
/*?*/           else if( pAct->GetType() == META_LINE_ACTION )
/*?*/           {
/*?*/               const Point aStart( ( (MetaLineAction*) pAct )->GetStartPoint() );
/*?*/               const Point aEnd( ( (MetaLineAction*) pAct )->GetEndPoint() );
/*?*/               aBound.Union( Rectangle( aStart, aEnd ) );
/*?*/           }
/*?*/       }
/*?*/
/*?*/       if( aMtf.GetActionCount() )
/*?*/       {
/*?*/           Size        aSizeLog( aBound.GetSize() );
/*?*/           const Size  aMinSizeLog( pOut->PixelToLogic( Size( 1, 1 ) ) );
/*?*/           const Size  aSizePix( pOut->LogicToPixel( aSizeLog ) );
/*?*/
/*?*/           // watch for minimum width
/*?*/           if( !aSizePix.Width() )
/*?*/               aSizeLog.Width() = aMinSizeLog.Width();
/*?*/
/*?*/           // watch for minimum width
/*?*/           if( !aSizePix.Height() )
/*?*/               aSizeLog.Height() = aMinSizeLog.Height();
/*?*/
/*?*/           aMap.SetOrigin( aBound.TopLeft() );
/*?*/           aMtf.SetPrefMapMode( aMap );
/*?*/           aMtf.SetPrefSize( aBound.GetSize() );
/*?*/           aTransGradient.SetSteps(3);
/*?*/           pOut->DrawTransparent( aMtf, aBound.TopLeft(), aSizeLog, aTransGradient );
/*?*/       }
/*N*/   }
/*N*/   else
/*N*/       ImpDrawLinePolygon( rPoly, bClosePoly );
/*N*/ }

// -----------------------------------------------------------------------------

/*N*/ void XOutputDevice::ImpDrawLinePolygon(const Polygon& rPoly, BOOL bClosePoly)
/*N*/ {
/*N*/   Polygon         aPoly( rPoly );
/*N*/   const Point*    pNextPoint;
/*N*/   Point           aLineStartPos, aLineEndPos;
/*N*/   XLineParam      aLParam, aStartParam, aEndParam;
/*N*/   USHORT          nPntMax = aPoly.GetSize() - 1;
/*N*/
/*N*/   if( nPntMax >= 1 )
/*N*/   {
/*N*/       if( bHair || ( ( XLINE_SOLID == eLineStyle ) && ( nLineWidth ==  0 ) ) )
/*N*/       {{DBG_BF_ASSERT(0, "STRIP"); }//STRIP001
//STRIP001 /*?*/            // #107240#
//STRIP001 /*?*/            // Since this method is also used for XOR drawing it's not allowed
//STRIP001 /*?*/            // to optimize to line drawing here. DrawLine() does not draw the
//STRIP001 /*?*/            // last point, thus a cycle with XOR drawing with DrawPolyLine() and then
//STRIP001 /*?*/            // deleting the last part with DrawLine() results in one point not being deleted.
//STRIP001 /*?*/            // if( 1 == nPntMax )
//STRIP001 /*?*/            //  pOut->DrawLine( rPoly[ 0 ], rPoly[ 1 ] );
//STRIP001 /*?*/            // else
//STRIP001 /*?*/            pOut->DrawPolyLine( rPoly );
//STRIP001 /*?*/
//STRIP001 /*?*/            DrawLineStartEnd( rPoly );
/*N*/       }
/*N*/       else if( XLINE_NONE != eLineStyle )
/*N*/       {
/*?*/           Color       aOldLineColor;
/*?*/           Color       aOldFillColor;
/*?*/           Point       aDiff;
/*?*/           const ULONG nOldDrawMode = pOut->GetDrawMode();
/*?*/           USHORT      i = 0;
/*?*/
/*?*/           if( !nLineWidth )
/*?*/           {
/*?*/               aOldLineColor = pOut->GetLineColor();
/*?*/               pOut->SetLineColor( aLineColor );
/*?*/           }
/*?*/
/*?*/           aOldFillColor = pOut->GetFillColor();
/*?*/
/*?*/           if( nOldDrawMode & DRAWMODE_WHITEFILL )
/*?*/           {
/*?*/               ULONG nNewDrawMode = nOldDrawMode;
/*?*/
/*?*/               nNewDrawMode &= ~DRAWMODE_WHITEFILL;
/*?*/               nNewDrawMode |= DRAWMODE_BLACKFILL;
/*?*/               pOut->SetDrawMode( nNewDrawMode );
/*?*/           }
/*?*/
/*?*/             if( nOldDrawMode & DRAWMODE_BLACKLINE )
/*?*/             {
/*?*/                 const Color aBlack( COL_BLACK );
/*?*/
/*?*/                 pOut->SetDrawMode( pOut->GetDrawMode() & (~DRAWMODE_SETTINGSFILL) );
/*?*/                 pOut->SetFillColor( aBlack );
/*?*/             }
/*?*/             else if( nOldDrawMode & DRAWMODE_SETTINGSLINE )
/*?*/             {
/*?*/                 pOut->SetDrawMode( pOut->GetDrawMode() & (~DRAWMODE_SETTINGSFILL) );
/*?*/               svtools::ColorConfig aColorConfig;
/*?*/               Color aColor( aColorConfig.GetColorValue( svtools::FONTCOLOR ).nColor );
/*?*/                 pOut->SetFillColor( aColor );
/*?*/             }
/*?*/             else
/*?*/                 pOut->SetFillColor( aLineColor );
/*?*/
/*?*/           // bei einfachen Linien darf das Polygon nicht geschlossen sein (#24000)
/*?*/           if ( aPoly[ nPntMax ] == aPoly[ 0 ] )
/*?*/           {
/*?*/               if ( nPntMax > 2 )
/*?*/               {
/*?*/                   nPntMax--;
/*?*/                   bClosePoly = TRUE;
/*?*/               }
/*?*/               else if ( 2 == nPntMax )
/*?*/                   bClosePoly = FALSE;
/*?*/           }
/*?*/
/*?*/           // Linien mit Laenge 0 nicht beruecksichtigen
/*?*/           while ( i < nPntMax )
/*?*/           {
/*?*/               aDiff = aPoly[i+1] - aPoly[0];
/*?*/
/*?*/               if ( bLineStart && !bClosePoly )
/*?*/               {
/*?*/                   long nSqLen = aDiff.X() * aDiff.X() + aDiff.Y() * aDiff.Y();
/*?*/                   if ( nSqLen > nLineStartSqLen || i == nPntMax-1 )
/*?*/                   {
/*?*/                       aLineStartPos = aPoly[0];
/*?*/                       aStartParam.Init(aPoly[0], aPoly[i+1], 1);
/*?*/                       double fLen = sqrt((double)nLineStartSqLen);
/*?*/                       if ( aStartParam.fLength )
/*?*/                           fLen /= aStartParam.fLength;
/*?*/                       aPoly[i].X() = aPoly[0].X() + (long) (fLen * aStartParam.nLineDx);
/*?*/                       aPoly[i].Y() = aPoly[0].Y() + (long) (fLen * aStartParam.nLineDy);
/*?*/                       break;
/*?*/                   }
/*?*/               }
/*?*/               else if ( aDiff.X() || aDiff.Y() )
/*?*/                   break;
/*?*/               i++;
/*?*/           }
/*?*/           USHORT  nLastPnt = nPntMax;
/*?*/
/*?*/           while ( nPntMax > i )
/*?*/           {
/*?*/               aDiff = aPoly[nPntMax-1] - aPoly[nLastPnt];
/*?*/               if ( bLineEnd && !bClosePoly )
/*?*/               {
/*?*/                   long nSqLen = aDiff.X() * aDiff.X() + aDiff.Y() * aDiff.Y();
/*?*/                   if ( nSqLen > nLineEndSqLen || nPntMax == i+1 )
/*?*/                   {
/*?*/                       aLineEndPos = aPoly[nLastPnt];
/*?*/                       aEndParam.Init(aPoly[nLastPnt], aPoly[nPntMax-1], 1);
/*?*/                       double fLen = sqrt((double)nLineEndSqLen);
/*?*/                       if ( aEndParam.fLength )
/*?*/                           fLen /= aEndParam.fLength;
/*?*/                       aPoly[nPntMax].X() = aPoly[nLastPnt].X() + (long) (fLen * aEndParam.nLineDx);
/*?*/                       aPoly[nPntMax].Y() = aPoly[nLastPnt].Y() + (long) (fLen * aEndParam.nLineDy);
/*?*/                       break;
/*?*/                   }
/*?*/               }
/*?*/               else if ( aDiff.X() || aDiff.Y() )
/*?*/                   break;
/*?*/               nPntMax--;
/*?*/           }
/*?*/
/*?*/           if ( bClosePoly )
/*?*/           {
/*?*/               aDiff = aPoly[nPntMax] - aPoly[i];
/*?*/               if ( !aDiff.X() && !aDiff.Y() )
/*?*/                   nPntMax--;
/*?*/               aLParam.Init(aPoly[nPntMax], aPoly[i], nLineWidth);
/*?*/               if ( nLineWidth > 0 )
/*?*/                   {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 CalcFatLineJoin(aPoly[i], aPoly[i+1], aLParam);
/*?*/           }
/*?*/           else
/*?*/               aLParam.Init(aPoly[i], aPoly[i+1], nLineWidth);
/*?*/
/*?*/           while ( i < nPntMax )
/*?*/           {
/*?*/               USHORT nPos = i + 1;
/*?*/               while ( nPos < nPntMax )
/*?*/               {
/*?*/                   aDiff = aPoly[nPos+1] - aPoly[nPos];
/*?*/                   if ( aDiff.X() || aDiff.Y() )
/*?*/                       break;
/*?*/                   nPos++;
/*?*/               }
/*?*/               if ( nPos+1 <= nPntMax )    pNextPoint = &aPoly[nPos+1];
/*?*/               else if ( bClosePoly )      pNextPoint = &aPoly[0];
/*?*/               else                        pNextPoint = NULL;
/*?*/
/*?*/               if ( nLineWidth > 0 )
/*?*/                   {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 DrawFatLine(aPoly[i], aPoly[i+1], pNextPoint, aLParam);
/*?*/               else
/*?*/               {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/                    aLParam.nLineDx = aPoly[i+1].X() - aPoly[i].X();
//STRIP001 /*?*/                    aLParam.nLineDy = aPoly[i+1].Y() - aPoly[i].Y();
//STRIP001 /*?*/                    aLParam.fLength = sqrt((double) aLParam.nLineDx * aLParam.nLineDx +
//STRIP001 /*?*/                                           (double) aLParam.nLineDy * aLParam.nLineDy);
//STRIP001 /*?*/                    DrawPatternLine(aPoly[i], aPoly[i+1], aLParam);
/*?*/               }
/*?*/               i = nPos;
/*?*/           }
/*?*/           if ( bClosePoly )
/*?*/           {
/*?*/               if ( nLineWidth > 0 )
/*?*/               {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001     DrawFatLine(aPoly[i], aPoly[0], &aPoly[1], aLParam);
/*?*/               else
/*?*/               {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/                    aLParam.nLineDx = aPoly[0].X() - aPoly[i].X();
//STRIP001 /*?*/                    aLParam.nLineDy = aPoly[0].Y() - aPoly[i].Y();
//STRIP001 /*?*/                    aLParam.fLength = sqrt((double) aLParam.nLineDx * aLParam.nLineDx +
//STRIP001 /*?*/                                           (double) aLParam.nLineDy * aLParam.nLineDy);
//STRIP001 /*?*/                    DrawPatternLine(aPoly[i], aPoly[0], aLParam);
/*?*/               }
/*?*/           }
/*?*/           else
/*?*/           {
/*?*/               if ( bLineStart )
/*?*/                   {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 DrawStartEndPoly(aLineStartPos, aLineStartPoly, aStartParam);
/*?*/               if ( bLineEnd )
/*?*/                   {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 DrawStartEndPoly(aLineEndPos, aLineEndPoly, aEndParam);
/*?*/           }
/*?*/
/*?*/           if( nLineWidth == 0 )
/*?*/               pOut->SetLineColor( aOldLineColor );
/*?*/
/*?*/           pOut->SetFillColor( aOldFillColor );
/*?*/           pOut->SetDrawMode( nOldDrawMode );
/*N*/       }
/*N*/   }
/*N*/ }


}
