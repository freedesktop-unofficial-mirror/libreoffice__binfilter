/*************************************************************************
 *
 *  $RCSfile: svx_svdtrans.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hjs $ $Date: 2004-06-28 12:34:33 $
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

#include "svdtrans.hxx"
#include <math.h>
#include "xpoly.hxx"

#ifndef _VIRDEV_HXX //autogen
#include <vcl/virdev.hxx>
#endif

#ifndef _BIGINT_HXX //autogen
#include <tools/bigint.hxx>
#endif

#ifndef _TOOLS_DEBUG_HXX //autogen
#include <tools/debug.hxx>
#endif

#ifndef INCLUDED_SVTOOLS_SYSLOCALE_HXX
#include <svtools/syslocale.hxx>
#endif
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void MoveXPoly(XPolygon& rPoly, const Size& S)
/*N*/ {
/*N*/   rPoly.Move(S.Width(),S.Height());
/*N*/ }

/*N*/ void MoveXPoly(XPolyPolygon& rPoly, const Size& S)
/*N*/ {
/*N*/   rPoly.Move(S.Width(),S.Height());
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void ResizeRect(Rectangle& rRect, const Point& rRef, const Fraction& rxFact, const Fraction& ryFact, FASTBOOL bNoJustify)
/*N*/ {
/*N*/   Fraction xFact(rxFact);
/*N*/   Fraction yFact(ryFact);
/*N*/   long nHgt=rRect.Bottom()-rRect.Top();
/*N*/
/*N*/   {
/*N*/       if (xFact.GetDenominator()==0) {
/*?*/           long nWdt=rRect.Right()-rRect.Left();
/*?*/           if (xFact.GetNumerator()>=0) { // DivZero abfangen
/*?*/               xFact=Fraction(xFact.GetNumerator(),1);
/*?*/               if (nWdt==0) rRect.Right()++;
/*?*/           } else {
/*?*/               xFact=Fraction(xFact.GetNumerator(),-1);
/*?*/               if (nWdt==0) rRect.Left()--;
/*N*/           }
/*N*/       }
/*N*/       rRect.Left()  =rRef.X()+Round(((double)(rRect.Left()  -rRef.X())*xFact.GetNumerator())/xFact.GetDenominator());
/*N*/       rRect.Right() =rRef.X()+Round(((double)(rRect.Right() -rRef.X())*xFact.GetNumerator())/xFact.GetDenominator());
/*N*/   }
/*N*/   {
/*N*/       if (yFact.GetDenominator()==0) {
/*?*/           long nHgt=rRect.Bottom()-rRect.Top();
/*?*/           if (yFact.GetNumerator()>=0) { // DivZero abfangen
/*?*/               yFact=Fraction(yFact.GetNumerator(),1);
/*?*/               if (nHgt==0) rRect.Bottom()++;
/*?*/           } else {
/*?*/               yFact=Fraction(yFact.GetNumerator(),-1);
/*?*/               if (nHgt==0) rRect.Top()--;
/*?*/           }
/*?*/
/*?*/           yFact=Fraction(yFact.GetNumerator(),1); // DivZero abfangen
/*N*/       }
/*N*/       rRect.Top()   =rRef.Y()+Round(((double)(rRect.Top()   -rRef.Y())*yFact.GetNumerator())/yFact.GetDenominator());
/*N*/       rRect.Bottom()=rRef.Y()+Round(((double)(rRect.Bottom()-rRef.Y())*yFact.GetNumerator())/yFact.GetDenominator());
/*N*/   }
/*N*/   if (!bNoJustify) rRect.Justify();
/*N*/ }


/*?*/ void ResizePoly(Polygon& rPoly, const Point& rRef, const Fraction& xFact, const Fraction& yFact)
/*?*/ {
/*?*/   USHORT nAnz=rPoly.GetSize();
/*?*/   for (USHORT i=0; i<nAnz; i++) {
/*?*/       ResizePoint(rPoly[i],rRef,xFact,yFact);
/*?*/   }
/*?*/ }

/*N*/ void ResizeXPoly(XPolygon& rPoly, const Point& rRef, const Fraction& xFact, const Fraction& yFact)
/*N*/ {
/*N*/   USHORT nAnz=rPoly.GetPointCount();
/*N*/   for (USHORT i=0; i<nAnz; i++) {
/*N*/       ResizePoint(rPoly[i],rRef,xFact,yFact);
/*N*/   }
/*N*/ }

/*?*/ void ResizePoly(PolyPolygon& rPoly, const Point& rRef, const Fraction& xFact, const Fraction& yFact)
/*?*/ {
/*?*/   USHORT nAnz=rPoly.Count();
/*?*/   for (USHORT i=0; i<nAnz; i++) {
/*?*/       ResizePoly(rPoly[i],rRef,xFact,yFact);
/*?*/   }
/*?*/ }

/*N*/ void ResizeXPoly(XPolyPolygon& rPoly, const Point& rRef, const Fraction& xFact, const Fraction& yFact)
/*N*/ {
/*N*/   USHORT nAnz=rPoly.Count();
/*N*/   for (USHORT i=0; i<nAnz; i++) {
/*N*/       ResizeXPoly(rPoly[i],rRef,xFact,yFact);
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void RotatePoly(Polygon& rPoly, const Point& rRef, double sn, double cs)
/*N*/ {
/*N*/   USHORT nAnz=rPoly.GetSize();
/*N*/   for (USHORT i=0; i<nAnz; i++) {
/*N*/       RotatePoint(rPoly[i],rRef,sn,cs);
/*N*/   }
/*N*/ }

/*N*/ void RotateXPoly(XPolygon& rPoly, const Point& rRef, double sn, double cs)
/*N*/ {
/*N*/   USHORT nAnz=rPoly.GetPointCount();
/*N*/   for (USHORT i=0; i<nAnz; i++) {
/*N*/       RotatePoint(rPoly[i],rRef,sn,cs);
/*N*/   }
/*N*/ }

/*?*/ void RotatePoly(PolyPolygon& rPoly, const Point& rRef, double sn, double cs)
/*?*/ {
/*?*/   USHORT nAnz=rPoly.Count();
/*?*/   for (USHORT i=0; i<nAnz; i++) {
/*?*/       RotatePoly(rPoly[i],rRef,sn,cs);
/*?*/   }
/*?*/ }

/*N*/ void RotateXPoly(XPolyPolygon& rPoly, const Point& rRef, double sn, double cs)
/*N*/ {
/*N*/   USHORT nAnz=rPoly.Count();
/*N*/   for (USHORT i=0; i<nAnz; i++) {
/*N*/       RotateXPoly(rPoly[i],rRef,sn,cs);
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void MirrorRect(Rectangle& rRect, const Point& rRef1, const Point& rRef2, FASTBOOL bNoJustify)
//STRIP001 {
//STRIP001  // !!! fehlende Implementation !!!
//STRIP001  if (!bNoJustify) rRect.Justify();
//STRIP001 }

//STRIP001 void MirrorPoint(Point& rPnt, const Point& rRef1, const Point& rRef2)
//STRIP001 {
//STRIP001  long mx=rRef2.X()-rRef1.X();
//STRIP001  long my=rRef2.Y()-rRef1.Y();
//STRIP001  if (mx==0) { // Achse senkrecht
//STRIP001      long dx=rRef1.X()-rPnt.X();
//STRIP001      rPnt.X()+=2*dx;
//STRIP001  } else if (my==0) { // Achse waagerecht
//STRIP001      long dy=rRef1.Y()-rPnt.Y();
//STRIP001      rPnt.Y()+=2*dy;
//STRIP001  } else if (mx==my) { // Achse diagonal '\'
//STRIP001      long dx1=rPnt.X()-rRef1.X();
//STRIP001      long dy1=rPnt.Y()-rRef1.Y();
//STRIP001      rPnt.X()=rRef1.X()+dy1;
//STRIP001      rPnt.Y()=rRef1.Y()+dx1;
//STRIP001  } else if (mx==-my) { // Achse diagonal '/'
//STRIP001      long dx1=rPnt.X()-rRef1.X();
//STRIP001      long dy1=rPnt.Y()-rRef1.Y();
//STRIP001      rPnt.X()=rRef1.X()-dy1;
//STRIP001      rPnt.Y()=rRef1.Y()-dx1;
//STRIP001  } else { // beliebige Achse
//STRIP001      // mal optimieren !!!
//STRIP001      // Lot auf der Spiegelachse faellen oder so
//STRIP001      long nRefWink=GetAngle(rRef2-rRef1);
//STRIP001      rPnt-=rRef1;
//STRIP001      long nPntWink=GetAngle(rPnt);
//STRIP001      long nWink=2*(nRefWink-nPntWink);
//STRIP001      double a=nWink*nPi180;
//STRIP001      double nSin=sin(a);
//STRIP001      double nCos=cos(a);
//STRIP001      RotatePoint(rPnt,Point(),nSin,nCos);
//STRIP001      rPnt+=rRef1;
//STRIP001  }
//STRIP001 }

//STRIP001 void MirrorPoly(Polygon& rPoly, const Point& rRef1, const Point& rRef2)
//STRIP001 {
//STRIP001  USHORT nAnz=rPoly.GetSize();
//STRIP001  for (USHORT i=0; i<nAnz; i++) {
//STRIP001      MirrorPoint(rPoly[i],rRef1,rRef2);
//STRIP001  }
//STRIP001 }

//STRIP001 void MirrorXPoly(XPolygon& rPoly, const Point& rRef1, const Point& rRef2)
//STRIP001 {
//STRIP001  USHORT nAnz=rPoly.GetPointCount();
//STRIP001  for (USHORT i=0; i<nAnz; i++) {
//STRIP001      MirrorPoint(rPoly[i],rRef1,rRef2);
//STRIP001  }
//STRIP001 }

//STRIP001 void MirrorPoly(PolyPolygon& rPoly, const Point& rRef1, const Point& rRef2)
//STRIP001 {
//STRIP001  USHORT nAnz=rPoly.Count();
//STRIP001  for (USHORT i=0; i<nAnz; i++) {
//STRIP001      MirrorPoly(rPoly[i],rRef1,rRef2);
//STRIP001  }
//STRIP001 }

//STRIP001 void MirrorXPoly(XPolyPolygon& rPoly, const Point& rRef1, const Point& rRef2)
//STRIP001 {
//STRIP001  USHORT nAnz=rPoly.Count();
//STRIP001  for (USHORT i=0; i<nAnz; i++) {
//STRIP001      MirrorXPoly(rPoly[i],rRef1,rRef2);
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void ShearPoly(Polygon& rPoly, const Point& rRef, double tn, FASTBOOL bVShear)
/*N*/ {
/*N*/   USHORT nAnz=rPoly.GetSize();
/*N*/   for (USHORT i=0; i<nAnz; i++) {
/*N*/       ShearPoint(rPoly[i],rRef,tn,bVShear);
/*N*/   }
/*N*/ }

/*N*/ void ShearXPoly(XPolygon& rPoly, const Point& rRef, double tn, FASTBOOL bVShear)
/*N*/ {
/*N*/   USHORT nAnz=rPoly.GetPointCount();
/*N*/   for (USHORT i=0; i<nAnz; i++) {
/*N*/       ShearPoint(rPoly[i],rRef,tn,bVShear);
/*N*/   }
/*N*/ }

/*?*/ void ShearPoly(PolyPolygon& rPoly, const Point& rRef, double tn, FASTBOOL bVShear)
/*?*/ {
/*?*/   USHORT nAnz=rPoly.Count();
/*?*/   for (USHORT i=0; i<nAnz; i++) {
/*?*/       ShearPoly(rPoly[i],rRef,tn,bVShear);
/*?*/   }
/*?*/ }

/*N*/ void ShearXPoly(XPolyPolygon& rPoly, const Point& rRef, double tn, FASTBOOL bVShear)
/*N*/ {
/*N*/   USHORT nAnz=rPoly.Count();
/*N*/   for (USHORT i=0; i<nAnz; i++) {
/*N*/       ShearXPoly(rPoly[i],rRef,tn,bVShear);
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//   @@@@  @@@@@   @@@@   @@@@  @@  @@
//  @@  @@ @@  @@ @@  @@ @@  @@ @@  @@
//  @@     @@  @@ @@  @@ @@  @@ @@ @@
//  @@     @@@@@  @@  @@ @@  @@ @@@@
//  @@     @@  @@ @@  @@ @@  @@ @@ @@
//  @@  @@ @@  @@ @@  @@ @@  @@ @@  @@
//   @@@@  @@  @@  @@@@   @@@@  @@  @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 double CrookRotateXPoint(Point& rPnt, Point* pC1, Point* pC2, const Point& rCenter,
//STRIP001                       const Point& rRad, double& rSin, double& rCos, FASTBOOL bVert)
//STRIP001 {
//STRIP001  FASTBOOL bC1=pC1!=NULL;
//STRIP001  FASTBOOL bC2=pC2!=NULL;
//STRIP001  long x0=rPnt.X();
//STRIP001  long y0=rPnt.Y();
//STRIP001  long cx=rCenter.X();
//STRIP001  long cy=rCenter.Y();
//STRIP001  double nWink=GetCrookAngle(rPnt,rCenter,rRad,bVert);
//STRIP001  double sn=sin(nWink);
//STRIP001  double cs=cos(nWink);
//STRIP001  RotatePoint(rPnt,rCenter,sn,cs);
//STRIP001  if (bC1) {
//STRIP001      if (bVert) {
//STRIP001          // Richtung Zentrum verschieben, als Ausgangsposition fuer Rotate
//STRIP001          pC1->Y()-=y0;
//STRIP001          // Resize, entsprechend der Entfernung vom Zentrum
//STRIP001          pC1->Y()=Round(((double)pC1->Y()) /rRad.X()*(cx-pC1->X()));
//STRIP001          pC1->Y()+=cy;
//STRIP001      } else {
//STRIP001          // Richtung Zentrum verschieben, als Ausgangsposition fuer Rotate
//STRIP001          pC1->X()-=x0;
//STRIP001          // Resize, entsprechend der Entfernung vom Zentrum
//STRIP001          long nPntRad=cy-pC1->Y();
//STRIP001          double nFact=(double)nPntRad/(double)rRad.Y();
//STRIP001          pC1->X()=Round((double)pC1->X()*nFact);
//STRIP001          pC1->X()+=cx;
//STRIP001      }
//STRIP001      RotatePoint(*pC1,rCenter,sn,cs);
//STRIP001  }
//STRIP001  if (bC2) {
//STRIP001      if (bVert) {
//STRIP001          // Richtung Zentrum verschieben, als Ausgangsposition fuer Rotate
//STRIP001          pC2->Y()-=y0;
//STRIP001          // Resize, entsprechend der Entfernung vom Zentrum
//STRIP001          pC2->Y()=Round(((double)pC2->Y()) /rRad.X()*(rCenter.X()-pC2->X()));
//STRIP001          pC2->Y()+=cy;
//STRIP001      } else {
//STRIP001          // Richtung Zentrum verschieben, als Ausgangsposition fuer Rotate
//STRIP001          pC2->X()-=x0;
//STRIP001          // Resize, entsprechend der Entfernung vom Zentrum
//STRIP001          long nPntRad=rCenter.Y()-pC2->Y();
//STRIP001          double nFact=(double)nPntRad/(double)rRad.Y();
//STRIP001          pC2->X()=Round((double)pC2->X()*nFact);
//STRIP001          pC2->X()+=cx;
//STRIP001      }
//STRIP001      RotatePoint(*pC2,rCenter,sn,cs);
//STRIP001  }
//STRIP001  rSin=sn;
//STRIP001  rCos=cs;
//STRIP001  return nWink;
//STRIP001 }

//STRIP001 double CrookSlantXPoint(Point& rPnt, Point* pC1, Point* pC2, const Point& rCenter,
//STRIP001                      const Point& rRad, double& rSin, double& rCos, FASTBOOL bVert)
//STRIP001 {
//STRIP001  FASTBOOL bC1=pC1!=NULL;
//STRIP001  FASTBOOL bC2=pC2!=NULL;
//STRIP001  long x0=rPnt.X();
//STRIP001  long y0=rPnt.Y();
//STRIP001  long dx1=0,dy1=0;
//STRIP001  long dxC1=0,dyC1=0;
//STRIP001  long dxC2=0,dyC2=0;
//STRIP001  if (bVert) {
//STRIP001      long nStart=rCenter.X()-rRad.X();
//STRIP001      dx1=rPnt.X()-nStart;
//STRIP001      rPnt.X()=nStart;
//STRIP001      if (bC1) {
//STRIP001          dxC1=pC1->X()-nStart;
//STRIP001          pC1->X()=nStart;
//STRIP001      }
//STRIP001      if (bC2) {
//STRIP001          dxC2=pC2->X()-nStart;
//STRIP001          pC2->X()=nStart;
//STRIP001      }
//STRIP001  } else {
//STRIP001      long nStart=rCenter.Y()-rRad.Y();
//STRIP001      dy1=rPnt.Y()-nStart;
//STRIP001      rPnt.Y()=nStart;
//STRIP001      if (bC1) {
//STRIP001          dyC1=pC1->Y()-nStart;
//STRIP001          pC1->Y()=nStart;
//STRIP001      }
//STRIP001      if (bC2) {
//STRIP001          dyC2=pC2->Y()-nStart;
//STRIP001          pC2->Y()=nStart;
//STRIP001      }
//STRIP001  }
//STRIP001  double nWink=GetCrookAngle(rPnt,rCenter,rRad,bVert);
//STRIP001  double sn=sin(nWink);
//STRIP001  double cs=cos(nWink);
//STRIP001  RotatePoint(rPnt,rCenter,sn,cs);
//STRIP001  if (bC1) { if (bVert) pC1->Y()-=y0-rCenter.Y(); else pC1->X()-=x0-rCenter.X(); RotatePoint(*pC1,rCenter,sn,cs); }
//STRIP001  if (bC2) { if (bVert) pC2->Y()-=y0-rCenter.Y(); else pC2->X()-=x0-rCenter.X(); RotatePoint(*pC2,rCenter,sn,cs); }
//STRIP001  if (bVert) {
//STRIP001      rPnt.X()+=dx1;
//STRIP001      if (bC1) pC1->X()+=dxC1;
//STRIP001      if (bC2) pC2->X()+=dxC2;
//STRIP001  } else {
//STRIP001      rPnt.Y()+=dy1;
//STRIP001      if (bC1) pC1->Y()+=dyC1;
//STRIP001      if (bC2) pC2->Y()+=dyC2;
//STRIP001  }
//STRIP001  rSin=sn;
//STRIP001  rCos=cs;
//STRIP001  return nWink;
//STRIP001 }

//STRIP001 double CrookStretchXPoint(Point& rPnt, Point* pC1, Point* pC2, const Point& rCenter,
//STRIP001                        const Point& rRad, double& rSin, double& rCos, FASTBOOL bVert,
//STRIP001                        const Rectangle rRefRect)
//STRIP001 {
//STRIP001  FASTBOOL bC1=pC1!=NULL;
//STRIP001  FASTBOOL bC2=pC2!=NULL;
//STRIP001  long x0=rPnt.X();
//STRIP001  long y0=rPnt.Y();
//STRIP001  CrookSlantXPoint(rPnt,pC1,pC2,rCenter,rRad,rSin,rCos,bVert);
//STRIP001  if (bVert) {
//STRIP001  } else {
//STRIP001      long nBase=rCenter.Y()-rRad.Y();
//STRIP001      long nTop=rRefRect.Top();
//STRIP001      long nBtm=rRefRect.Bottom();
//STRIP001      long nHgt=nBtm-nTop;
//STRIP001      long dy=rPnt.Y()-y0;
//STRIP001      FASTBOOL bOben=rRad.Y()<0;
//STRIP001      double a=((double)(y0-nTop))/nHgt;
//STRIP001      a*=dy;
//STRIP001      rPnt.Y()=y0+Round(a);
//STRIP001  } return 0.0;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void CrookRotatePoly(XPolygon& rPoly, const Point& rCenter, const Point& rRad, FASTBOOL bVert)
//STRIP001 {
//STRIP001  double nSin,nCos;
//STRIP001  USHORT nPointAnz=rPoly.GetPointCount();
//STRIP001  USHORT i=0;
//STRIP001  while (i<nPointAnz) {
//STRIP001      Point* pPnt=&rPoly[i];
//STRIP001      Point* pC1=NULL;
//STRIP001      Point* pC2=NULL;
//STRIP001      if (i+1<nPointAnz && rPoly.IsControl(i)) { // Kontrollpunkt links
//STRIP001          pC1=pPnt;
//STRIP001          i++;
//STRIP001          pPnt=&rPoly[i];
//STRIP001      }
//STRIP001      i++;
//STRIP001      if (i<nPointAnz && rPoly.IsControl(i)) { // Kontrollpunkt rechts
//STRIP001          pC2=&rPoly[i];
//STRIP001          i++;
//STRIP001      }
//STRIP001      CrookRotateXPoint(*pPnt,pC1,pC2,rCenter,rRad,nSin,nCos,bVert);
//STRIP001  }
//STRIP001 }

//STRIP001 void CrookSlantPoly(XPolygon& rPoly, const Point& rCenter, const Point& rRad, FASTBOOL bVert)
//STRIP001 {
//STRIP001  double nSin,nCos;
//STRIP001  USHORT nPointAnz=rPoly.GetPointCount();
//STRIP001  USHORT i=0;
//STRIP001  while (i<nPointAnz) {
//STRIP001      Point* pPnt=&rPoly[i];
//STRIP001      Point* pC1=NULL;
//STRIP001      Point* pC2=NULL;
//STRIP001      if (i+1<nPointAnz && rPoly.IsControl(i)) { // Kontrollpunkt links
//STRIP001          pC1=pPnt;
//STRIP001          i++;
//STRIP001          pPnt=&rPoly[i];
//STRIP001      }
//STRIP001      i++;
//STRIP001      if (i<nPointAnz && rPoly.IsControl(i)) { // Kontrollpunkt rechts
//STRIP001          pC2=&rPoly[i];
//STRIP001          i++;
//STRIP001      }
//STRIP001      CrookSlantXPoint(*pPnt,pC1,pC2,rCenter,rRad,nSin,nCos,bVert);
//STRIP001  }
//STRIP001 }

//STRIP001 void CrookStretchPoly(XPolygon& rPoly, const Point& rCenter, const Point& rRad, FASTBOOL bVert, const Rectangle rRefRect)
//STRIP001 {
//STRIP001  double nSin,nCos;
//STRIP001  USHORT nPointAnz=rPoly.GetPointCount();
//STRIP001  USHORT i=0;
//STRIP001  while (i<nPointAnz) {
//STRIP001      Point* pPnt=&rPoly[i];
//STRIP001      Point* pC1=NULL;
//STRIP001      Point* pC2=NULL;
//STRIP001      if (i+1<nPointAnz && rPoly.IsControl(i)) { // Kontrollpunkt links
//STRIP001          pC1=pPnt;
//STRIP001          i++;
//STRIP001          pPnt=&rPoly[i];
//STRIP001      }
//STRIP001      i++;
//STRIP001      if (i<nPointAnz && rPoly.IsControl(i)) { // Kontrollpunkt rechts
//STRIP001          pC2=&rPoly[i];
//STRIP001          i++;
//STRIP001      }
//STRIP001      CrookStretchXPoint(*pPnt,pC1,pC2,rCenter,rRad,nSin,nCos,bVert,rRefRect);
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void CrookRotatePoly(XPolyPolygon& rPoly, const Point& rCenter, const Point& rRad, FASTBOOL bVert)
//STRIP001 {
//STRIP001  USHORT nPolyAnz=rPoly.Count();
//STRIP001  for (USHORT nPolyNum=0; nPolyNum<nPolyAnz; nPolyNum++) {
//STRIP001      CrookRotatePoly(rPoly[nPolyNum],rCenter,rRad,bVert);
//STRIP001  }
//STRIP001 }

//STRIP001 void CrookSlantPoly(XPolyPolygon& rPoly, const Point& rCenter, const Point& rRad, FASTBOOL bVert)
//STRIP001 {
//STRIP001  USHORT nPolyAnz=rPoly.Count();
//STRIP001  for (USHORT nPolyNum=0; nPolyNum<nPolyAnz; nPolyNum++) {
//STRIP001      CrookSlantPoly(rPoly[nPolyNum],rCenter,rRad,bVert);
//STRIP001  }
//STRIP001 }

//STRIP001 void CrookStretchPoly(XPolyPolygon& rPoly, const Point& rCenter, const Point& rRad, FASTBOOL bVert, const Rectangle rRefRect)
//STRIP001 {
//STRIP001  USHORT nPolyAnz=rPoly.Count();
//STRIP001  for (USHORT nPolyNum=0; nPolyNum<nPolyAnz; nPolyNum++) {
//STRIP001      CrookStretchPoly(rPoly[nPolyNum],rCenter,rRad,bVert,rRefRect);
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ long GetAngle(const Point& rPnt)
/*N*/ {
/*N*/   long a=0;
/*N*/   if (rPnt.Y()==0) {
/*N*/       if (rPnt.X()<0) a=-18000;
/*N*/   } else if (rPnt.X()==0) {
/*N*/       if (rPnt.Y()>0) a=-9000;
/*N*/       else a=9000;
/*N*/   } else {
/*N*/       a=Round((atan2((double)-rPnt.Y(),(double)rPnt.X())/nPi180));
/*N*/   }
/*N*/   return a;
/*N*/ }

/*N*/ long NormAngle180(long a)
/*N*/ {
/*N*/   while (a<18000) a+=36000;
/*N*/   while (a>=18000) a-=36000;
/*N*/   return a;
/*N*/ }

/*N*/ long NormAngle360(long a)
/*N*/ {
/*N*/   while (a<0) a+=36000;
/*N*/   while (a>=36000) a-=36000;
/*N*/   return a;
/*N*/ }

/*?*/ USHORT GetAngleSector(long nWink)
/*?*/ {
/*?*/   while (nWink<0) nWink+=36000;
/*?*/   while (nWink>=36000) nWink-=36000;
/*?*/   if (nWink< 9000) return 0;
/*?*/   if (nWink<18000) return 1;
/*?*/   if (nWink<27000) return 2;
/*?*/   return 3;
/*?*/ }

/*N*/ long GetLen(const Point& rPnt)
/*N*/ {
/*N*/   long x=Abs(rPnt.X());
/*N*/   long y=Abs(rPnt.Y());
/*N*/   if (x+y<0x8000) { // weil 7FFF * 7FFF * 2 = 7FFE0002
/*N*/       x*=x;
/*N*/       y*=y;
/*N*/       x+=y;
/*N*/       x=Round(sqrt((double)x));
/*N*/       return x;
/*N*/   } else {
/*?*/       double nx=x;
/*?*/       double ny=y;
/*?*/       nx*=nx;
/*?*/       ny*=ny;
/*?*/       nx+=ny;
/*?*/       nx=sqrt(nx);
/*?*/       if (nx>0x7FFFFFFF) {
/*?*/           return 0x7FFFFFFF; // Ueberlauf, mehr is nich!
/*?*/       } else {
/*?*/           return Round(nx);
/*?*/       }
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void GeoStat::RecalcSinCos()
/*N*/ {
/*N*/   if (nDrehWink==0) {
/*N*/       nSin=0.0;
/*N*/       nCos=1.0;
/*N*/   } else {
/*N*/       double a=nDrehWink*nPi180;
/*N*/       nSin=sin(a);
/*N*/       nCos=cos(a);
/*N*/   }
/*N*/ }
/*N*/
/*N*/ void GeoStat::RecalcTan()
/*N*/ {
/*N*/   if (nShearWink==0) {
/*N*/       nTan=0.0;
/*N*/   } else {
/*N*/       double a=nShearWink*nPi180;
/*N*/       nTan=tan(a);
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ Polygon Rect2Poly(const Rectangle& rRect, const GeoStat& rGeo)
/*N*/ {
/*N*/   Polygon aPol(5);
/*N*/   aPol[0]=rRect.TopLeft();
/*N*/   aPol[1]=rRect.TopRight();
/*N*/   aPol[2]=rRect.BottomRight();
/*N*/   aPol[3]=rRect.BottomLeft();
/*N*/   aPol[4]=rRect.TopLeft();
/*N*/   if (rGeo.nShearWink!=0) ShearPoly(aPol,rRect.TopLeft(),rGeo.nTan);
/*N*/   if (rGeo.nDrehWink!=0) RotatePoly(aPol,rRect.TopLeft(),rGeo.nSin,rGeo.nCos);
/*N*/   return aPol;
/*N*/ }

/*N*/ void Poly2Rect(const Polygon& rPol, Rectangle& rRect, GeoStat& rGeo)
/*N*/ {
/*N*/   rGeo.nDrehWink=GetAngle(rPol[1]-rPol[0]);
/*N*/   rGeo.nDrehWink=NormAngle360(rGeo.nDrehWink);
/*N*/   // Drehung ist damit im Kasten
/*N*/   rGeo.RecalcSinCos();
/*N*/
/*N*/   Point aPt1(rPol[1]-rPol[0]);
/*N*/   if (rGeo.nDrehWink!=0) RotatePoint(aPt1,Point(0,0),-rGeo.nSin,rGeo.nCos); // -Sin fuer Rueckdrehung
/*N*/   long nWdt=aPt1.X();
/*N*/
/*N*/   Point aPt0(rPol[0]);
/*N*/   Point aPt3(rPol[3]-rPol[0]);
/*N*/   if (rGeo.nDrehWink!=0) RotatePoint(aPt3,Point(0,0),-rGeo.nSin,rGeo.nCos); // -Sin fuer Rueckdrehung
/*N*/   long nHgt=aPt3.Y();
/*N*/   long nShW=GetAngle(aPt3);
/*N*/   nShW-=27000; // ShearWink wird zur Senkrechten gemessen
/*N*/   nShW=-nShW;  // Negieren, denn '+' ist Rechtskursivierung
/*N*/
/*N*/   FASTBOOL bMirr=aPt3.Y()<0;
/*N*/   if (bMirr) { // "Punktetausch" bei Spiegelung
/*N*/       nHgt=-nHgt;
/*N*/       nShW+=18000;
/*N*/       aPt0=rPol[3];
/*N*/   }
/*N*/   nShW=NormAngle180(nShW);
/*N*/   if (nShW<-9000 || nShW>9000) {
/*N*/       nShW=NormAngle180(nShW+18000);
/*N*/   }
/*N*/   if (nShW<-SDRMAXSHEAR) nShW=-SDRMAXSHEAR; // ShearWinkel begrenzen auf +/- 89.00 deg
/*N*/   if (nShW>SDRMAXSHEAR)  nShW=SDRMAXSHEAR;
/*N*/   rGeo.nShearWink=nShW;
/*N*/   rGeo.RecalcTan();
/*N*/   Point aRU(aPt0);
/*N*/   aRU.X()+=nWdt;
/*N*/   aRU.Y()+=nHgt;
/*N*/   rRect=Rectangle(aPt0,aRU);
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*?*/ void OrthoDistance8(const Point& rPt0, Point& rPt, FASTBOOL bBigOrtho)
/*?*/ {
/*?*/   long dx=rPt.X()-rPt0.X();
/*?*/   long dy=rPt.Y()-rPt0.Y();
/*?*/   long dxa=Abs(dx);
/*?*/   long dya=Abs(dy);
/*?*/   if (dx==0 || dy==0 || dxa==dya) return;
/*?*/   if (dxa>=dya*2) { rPt.Y()=rPt0.Y(); return; }
/*?*/   if (dya>=dxa*2) { rPt.X()=rPt0.X(); return; }
/*?*/   if ((dxa<dya) != bBigOrtho) {
/*?*/       rPt.Y()=rPt0.Y()+(dxa* (dy>=0 ? 1 : -1) );
/*?*/   } else {
/*?*/       rPt.X()=rPt0.X()+(dya* (dx>=0 ? 1 : -1) );
/*?*/   }
/*?*/ }

/*?*/ void OrthoDistance4(const Point& rPt0, Point& rPt, FASTBOOL bBigOrtho)
/*?*/ {
/*?*/   long dx=rPt.X()-rPt0.X();
/*?*/   long dy=rPt.Y()-rPt0.Y();
/*?*/   long dxa=Abs(dx);
/*?*/   long dya=Abs(dy);
/*?*/   if ((dxa<dya) != bBigOrtho) {
/*?*/       rPt.Y()=rPt0.Y()+(dxa* (dy>=0 ? 1 : -1) );
/*?*/   } else {
/*?*/       rPt.X()=rPt0.X()+(dya* (dx>=0 ? 1 : -1) );
/*?*/   }
/*?*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ long BigMulDiv(long nVal, long nMul, long nDiv)
/*N*/ {
/*N*/   BigInt aVal(nVal);
/*N*/   aVal*=nMul;
/*N*/   if (aVal.IsNeg()!=(nDiv<0)) {
/*N*/       aVal-=nDiv/2; // fuer korrektes Runden
/*N*/   } else {
/*N*/       aVal+=nDiv/2; // fuer korrektes Runden
/*N*/   }
/*N*/   if(nDiv)
/*N*/   {
/*N*/       aVal/=nDiv;
/*N*/       return long(aVal);
/*N*/   }
/*N*/   return 0x7fffffff;
/*N*/ }

/*NBFF*/ void Kuerzen(Fraction& rF, unsigned nDigits)
/*NBFF*/ {
/*NBFF*/    INT32 nMul=rF.GetNumerator();
/*NBFF*/    INT32 nDiv=rF.GetDenominator();
/*NBFF*/    FASTBOOL bNeg=FALSE;
/*NBFF*/    if (nMul<0) { nMul=-nMul; bNeg=!bNeg; }
/*NBFF*/    if (nDiv<0) { nDiv=-nDiv; bNeg=!bNeg; }
/*NBFF*/    if (nMul==0 || nDiv==0) return;
/*NBFF*/    UINT32 a;
/*NBFF*/    a=UINT32(nMul); unsigned nMulZ=0; // Fuehrende Nullen zaehlen
/*NBFF*/    while (a<0x00800000) { nMulZ+=8; a<<=8; }
/*NBFF*/    while (a<0x80000000) { nMulZ++; a<<=1; }
/*NBFF*/    a=UINT32(nDiv); unsigned nDivZ=0; // Fuehrende Nullen zaehlen
/*NBFF*/    while (a<0x00800000) { nDivZ+=8; a<<=8; }
/*NBFF*/    while (a<0x80000000) { nDivZ++; a<<=1; }
/*NBFF*/    // Anzahl der verwendeten Digits bestimmen
/*NBFF*/    int nMulDigits=32-nMulZ;
/*NBFF*/    int nDivDigits=32-nDivZ;
/*NBFF*/    // Nun bestimmen, wieviele Stellen hinten weg koennen
/*NBFF*/    int nMulWeg=nMulDigits-nDigits; if (nMulWeg<0) nMulWeg=0;
/*NBFF*/    int nDivWeg=nDivDigits-nDigits; if (nDivWeg<0) nDivWeg=0;
/*NBFF*/    int nWeg=Min(nMulWeg,nDivWeg);
/*NBFF*/    nMul>>=nWeg;
/*NBFF*/    nDiv>>=nWeg;
/*NBFF*/    if (nMul==0 || nDiv==0) {
/*NBFF*/        DBG_WARNING("Oups, beim kuerzen einer Fraction hat sich Joe verrechnet.");
/*NBFF*/        return;
/*NBFF*/    }
/*NBFF*/    if (bNeg) nMul=-nMul;
/*NBFF*/    rF=Fraction(nMul,nDiv);
/*NBFF*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// Wieviele eU-Einheiten passen in einen mm bzw. Inch?
// Oder wie gross ist ein eU in mm bzw. Inch, und davon der Kehrwert

//STRIP001 FrPair GetInchOrMM(MapUnit eU)
//STRIP001 {
//STRIP001  switch (eU) {
//STRIP001      case MAP_1000TH_INCH: return FrPair(1000,1);
//STRIP001      case MAP_100TH_INCH : return FrPair( 100,1);
//STRIP001      case MAP_10TH_INCH  : return FrPair(  10,1);
//STRIP001      case MAP_INCH       : return FrPair(   1,1);
//STRIP001      case MAP_POINT      : return FrPair(  72,1);
//STRIP001      case MAP_TWIP       : return FrPair(1440,1);
//STRIP001      case MAP_100TH_MM   : return FrPair( 100,1);
//STRIP001      case MAP_10TH_MM    : return FrPair(  10,1);
//STRIP001      case MAP_MM         : return FrPair(   1,1);
//STRIP001      case MAP_CM         : return FrPair(   1,10);
//STRIP001      case MAP_PIXEL      : {
//STRIP001          VirtualDevice aVD;
//STRIP001          aVD.SetMapMode(MapMode(MAP_100TH_MM));
//STRIP001          Point aP(aVD.PixelToLogic(Point(64,64))); // 64 Pixel fuer bessere Genauigkeit
//STRIP001          return FrPair(6400,aP.X(),6400,aP.Y());
//STRIP001      }
//STRIP001      case MAP_APPFONT: case MAP_SYSFONT: {
//STRIP001          VirtualDevice aVD;
//STRIP001          aVD.SetMapMode(MapMode(eU));
//STRIP001          Point aP(aVD.LogicToPixel(Point(32,32))); // 32 Einheiten fuer bessere Genauigkeit
//STRIP001          aVD.SetMapMode(MapMode(MAP_100TH_MM));
//STRIP001          aP=aVD.PixelToLogic(aP);
//STRIP001          return FrPair(3200,aP.X(),3200,aP.Y());
//STRIP001      }
//STRIP001  }
//STRIP001  return Fraction(1,1);
//STRIP001 }

//STRIP001 FrPair GetInchOrMM(FieldUnit eU)
//STRIP001 {
//STRIP001  switch (eU) {
//STRIP001      case FUNIT_INCH       : return FrPair(   1,1);
//STRIP001      case FUNIT_POINT      : return FrPair(  72,1);
//STRIP001      case FUNIT_TWIP       : return FrPair(1440,1);
//STRIP001      case FUNIT_100TH_MM   : return FrPair( 100,1);
//STRIP001      case FUNIT_MM         : return FrPair(   1,1);
//STRIP001      case FUNIT_CM         : return FrPair(   1,10);
//STRIP001      case FUNIT_M          : return FrPair(   1,1000);
//STRIP001      case FUNIT_KM         : return FrPair(   1,1000000);
//STRIP001      case FUNIT_PICA       : return FrPair(   6,1);
//STRIP001      case FUNIT_FOOT       : return FrPair(   1,12);
//STRIP001      case FUNIT_MILE       : return FrPair(   1,63360);
//STRIP001  }
//STRIP001  return Fraction(1,1);
//STRIP001 }

// Den Faktor berechnen, der anzuwenden ist um n Einheiten von eS nach
// eD umzurechnen. Z.B. GetMapFactor(UNIT_MM,UNIT_100TH_MM) => 100.

//STRIP001 FrPair GetMapFactor(MapUnit eS, MapUnit eD)
//STRIP001 {
//STRIP001  if (eS==eD) return FrPair(1,1,1,1);
//STRIP001  FrPair aS(GetInchOrMM(eS));
//STRIP001  FrPair aD(GetInchOrMM(eD));
//STRIP001  FASTBOOL bSInch=IsInch(eS);
//STRIP001  FASTBOOL bDInch=IsInch(eD);
//STRIP001  FrPair aRet(aD.X()/aS.X(),aD.Y()/aS.Y());
//STRIP001  if (bSInch && !bDInch) { aRet.X()*=Fraction(127,5); aRet.Y()*=Fraction(127,5); }
//STRIP001  if (!bSInch && bDInch) { aRet.X()*=Fraction(5,127); aRet.Y()*=Fraction(5,127); }
//STRIP001  return aRet;
//STRIP001 };

//STRIP001 FrPair GetMapFactor(MapUnit eS, FieldUnit eD)
//STRIP001 {
//STRIP001  FrPair aS(GetInchOrMM(eS));
//STRIP001  FrPair aD(GetInchOrMM(eD));
//STRIP001  FASTBOOL bSInch=IsInch(eS);
//STRIP001  FASTBOOL bDInch=IsInch(eD);
//STRIP001  FrPair aRet(aD.X()/aS.X(),aD.Y()/aS.Y());
//STRIP001  if (bSInch && !bDInch) { aRet.X()*=Fraction(127,5); aRet.Y()*=Fraction(127,5); }
//STRIP001  if (!bSInch && bDInch) { aRet.X()*=Fraction(5,127); aRet.Y()*=Fraction(5,127); }
//STRIP001  return aRet;
//STRIP001 };

//STRIP001 FrPair GetMapFactor(FieldUnit eS, MapUnit eD)
//STRIP001 {
//STRIP001  FrPair aS(GetInchOrMM(eS));
//STRIP001  FrPair aD(GetInchOrMM(eD));
//STRIP001  FASTBOOL bSInch=IsInch(eS);
//STRIP001  FASTBOOL bDInch=IsInch(eD);
//STRIP001  FrPair aRet(aD.X()/aS.X(),aD.Y()/aS.Y());
//STRIP001  if (bSInch && !bDInch) { aRet.X()*=Fraction(127,5); aRet.Y()*=Fraction(127,5); }
//STRIP001  if (!bSInch && bDInch) { aRet.X()*=Fraction(5,127); aRet.Y()*=Fraction(5,127); }
//STRIP001  return aRet;
//STRIP001 };

/*?*/ FrPair GetMapFactor(FieldUnit eS, FieldUnit eD)
/*?*/ {
/*?*/   if (eS==eD) return FrPair(1,1,1,1);
/*?*/ {DBG_BF_ASSERT(0, "STRIP");}return FrPair(1,1,1,1);//STRIP001 //STRIP001 /*?*/    FrPair aS(GetInchOrMM(eS));
//STRIP001 /*?*/    FrPair aD(GetInchOrMM(eD));
//STRIP001 /*?*/    FASTBOOL bSInch=IsInch(eS);
//STRIP001 /*?*/    FASTBOOL bDInch=IsInch(eD);
//STRIP001 /*?*/    FrPair aRet(aD.X()/aS.X(),aD.Y()/aS.Y());
//STRIP001 /*?*/    if (bSInch && !bDInch) { aRet.X()*=Fraction(127,5); aRet.Y()*=Fraction(127,5); }
//STRIP001 /*?*/    if (!bSInch && bDInch) { aRet.X()*=Fraction(5,127); aRet.Y()*=Fraction(5,127); }
//STRIP001 /*?*/    return aRet;
/*?*/ };

////////////////////////////////////////////////////////////////////////////////////////////////////

    // 1 mile    =  8 furlong = 63.360" = 1.609.344,0mm
    // 1 furlong = 10 chains  =  7.920" =   201.168,0mm
    // 1 chain   =  4 poles   =    792" =    20.116,8mm
    // 1 pole    =  5 1/2 yd  =    198" =     5.029,2mm
    // 1 yd      =  3 ft      =     36" =       914,4mm
    // 1 ft      = 12 "       =      1" =       304,8mm

//STRIP001 void GetMeterOrInch(MapUnit eMU, short& rnKomma, long& rnMul, long& rnDiv, FASTBOOL& rbMetr, FASTBOOL& rbInch)
//STRIP001 {
//STRIP001  rnMul=1; rnDiv=1;
//STRIP001  short nKomma=0;
//STRIP001  FASTBOOL bMetr=FALSE,bInch=FALSE;
//STRIP001  switch (eMU) {
//STRIP001      // Metrisch
//STRIP001      case MAP_100TH_MM   : bMetr=TRUE; nKomma=5; break;
//STRIP001      case MAP_10TH_MM    : bMetr=TRUE; nKomma=4; break;
//STRIP001      case MAP_MM         : bMetr=TRUE; nKomma=3; break;
//STRIP001      case MAP_CM         : bMetr=TRUE; nKomma=2; break;
//STRIP001      // Inch
//STRIP001      case MAP_1000TH_INCH: bInch=TRUE; nKomma=3; break;
//STRIP001      case MAP_100TH_INCH : bInch=TRUE; nKomma=2; break;
//STRIP001      case MAP_10TH_INCH  : bInch=TRUE; nKomma=1; break;
//STRIP001      case MAP_INCH       : bInch=TRUE; nKomma=0; break;
//STRIP001      case MAP_POINT      : bInch=TRUE; rnDiv=72;  break;          // 1Pt   = 1/72"
//STRIP001      case MAP_TWIP       : bInch=TRUE; rnDiv=144; nKomma=1; break; // 1Twip = 1/1440"
//STRIP001      // Sonstiges
//STRIP001      case MAP_PIXEL      : break;
//STRIP001      case MAP_SYSFONT    : break;
//STRIP001      case MAP_APPFONT    : break;
//STRIP001      case MAP_RELATIVE   : break;
//STRIP001  } // switch
//STRIP001  rnKomma=nKomma;
//STRIP001  rbMetr=bMetr;
//STRIP001  rbInch=bInch;
//STRIP001 }

//STRIP001 void GetMeterOrInch(FieldUnit eFU, short& rnKomma, long& rnMul, long& rnDiv, FASTBOOL& rbMetr, FASTBOOL& rbInch)
//STRIP001 {
//STRIP001  rnMul=1; rnDiv=1;
//STRIP001  short nKomma=0;
//STRIP001  FASTBOOL bMetr=FALSE,bInch=FALSE;
//STRIP001  switch (eFU) {
//STRIP001      case FUNIT_NONE     : break;
//STRIP001      // Metrisch
//STRIP001      case FUNIT_100TH_MM : bMetr=TRUE; nKomma=5; break;
//STRIP001      case FUNIT_MM       : bMetr=TRUE; nKomma=3; break;
//STRIP001      case FUNIT_CM       : bMetr=TRUE; nKomma=2; break;
//STRIP001      case FUNIT_M        : bMetr=TRUE; nKomma=0; break;
//STRIP001      case FUNIT_KM       : bMetr=TRUE; nKomma=-3; break;
//STRIP001      // Inch
//STRIP001      case FUNIT_TWIP     : bInch=TRUE; rnDiv=144; nKomma=1; break;  // 1Twip = 1/1440"
//STRIP001      case FUNIT_POINT    : bInch=TRUE; rnDiv=72; break;   // 1Pt   = 1/72"
//STRIP001      case FUNIT_PICA     : bInch=TRUE; rnDiv=6; break;    // 1Pica = 1/6"  ?
//STRIP001      case FUNIT_INCH     : bInch=TRUE; break;             // 1"    = 1"
//STRIP001      case FUNIT_FOOT     : bInch=TRUE; rnMul=12; break;   // 1Ft   = 12"
//STRIP001      case FUNIT_MILE     : bInch=TRUE; rnMul=6336; nKomma=-1; break; // 1mile = 63360"
//STRIP001      // sonstiges
//STRIP001      case FUNIT_CUSTOM   : break;
//STRIP001      case FUNIT_PERCENT  : nKomma=2; break;
//STRIP001  } // switch
//STRIP001  rnKomma=nKomma;
//STRIP001  rbMetr=bMetr;
//STRIP001  rbInch=bInch;
//STRIP001 }

//STRIP001 void SdrFormatter::Undirty()
//STRIP001 {
//STRIP001  if (aScale.GetNumerator()==0 || aScale.GetDenominator()==0) aScale=Fraction(1,1);
//STRIP001  FASTBOOL bSrcMetr,bSrcInch,bDstMetr,bDstInch;
//STRIP001  long nMul1,nDiv1,nMul2,nDiv2;
//STRIP001  short nKomma1,nKomma2;
//STRIP001  // Zunaechst normalisieren auf m bzw. "
//STRIP001  if (!bSrcFU) {
//STRIP001      GetMeterOrInch(eSrcMU,nKomma1,nMul1,nDiv1,bSrcMetr,bSrcInch);
//STRIP001  } else {
//STRIP001      GetMeterOrInch(eSrcFU,nKomma1,nMul1,nDiv1,bSrcMetr,bSrcInch);
//STRIP001  }
//STRIP001  if (!bDstFU) {
//STRIP001      GetMeterOrInch(eDstMU,nKomma2,nMul2,nDiv2,bDstMetr,bDstInch);
//STRIP001  } else {
//STRIP001      GetMeterOrInch(eDstFU,nKomma2,nMul2,nDiv2,bDstMetr,bDstInch);
//STRIP001  }
//STRIP001  nMul1*=nDiv2;
//STRIP001  nDiv1*=nMul2;
//STRIP001  nKomma1-=nKomma2;
//STRIP001
//STRIP001  if (bSrcInch && bDstMetr) {
//STRIP001      nKomma1+=4;
//STRIP001      nMul1*=254;
//STRIP001  }
//STRIP001  if (bSrcMetr && bDstInch) {
//STRIP001      nKomma1-=4;
//STRIP001      nDiv1*=254;
//STRIP001  }
//STRIP001
//STRIP001  // Temporaere Fraction zum Kuerzen
//STRIP001  Fraction aTempFract(nMul1,nDiv1);
//STRIP001  nMul1=aTempFract.GetNumerator();
//STRIP001  nDiv1=aTempFract.GetDenominator();
//STRIP001
//STRIP001  nMul_=nMul1;
//STRIP001  nDiv_=nDiv1;
//STRIP001  nKomma_=nKomma1;
//STRIP001  bDirty=FALSE;
//STRIP001 }


//STRIP001 void SdrFormatter::TakeStr(long nVal, XubString& rStr) const
//STRIP001 {
//STRIP001  sal_Unicode aNullCode('0');
//STRIP001
//STRIP001  if(!nVal)
//STRIP001  {
//STRIP001      rStr = UniString();
//STRIP001      rStr += aNullCode;
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  // Hier fallen trotzdem evtl. Nachkommastellen weg, wg. MulDiv statt Real
//STRIP001  BOOL bNeg(nVal < 0);
//STRIP001     SvtSysLocale aSysLoc;
//STRIP001     const LocaleDataWrapper& rLoc = aSysLoc.GetLocaleData();
//STRIP001
//STRIP001  ForceUndirty();
//STRIP001
//STRIP001  xub_StrLen nK(nKomma_);
//STRIP001  XubString aStr;
//STRIP001
//STRIP001  if(bNeg)
//STRIP001      nVal = -nVal;
//STRIP001
//STRIP001  while(nK <= -3)
//STRIP001  {
//STRIP001      nVal *= 1000;
//STRIP001      nK += 3;
//STRIP001  }
//STRIP001
//STRIP001  while(nK <= -1)
//STRIP001  {
//STRIP001      nVal *= 10;
//STRIP001      nK++;
//STRIP001  }
//STRIP001
//STRIP001  if(nMul_ != nDiv_)
//STRIP001      nVal = BigMulDiv(nVal, nMul_, nDiv_);
//STRIP001
//STRIP001  aStr = UniString::CreateFromInt32(nVal);
//STRIP001
//STRIP001  if(nK > 0 && aStr.Len() <= nK )
//STRIP001  {
//STRIP001      // Komma erforderlich
//STRIP001      xub_StrLen nAnz(nK - aStr.Len());
//STRIP001
//STRIP001         if(nAnz >= 0 && rLoc.isNumLeadingZero())
//STRIP001          nAnz++;
//STRIP001
//STRIP001      for(xub_StrLen  i=0; i<nAnz; i++)
//STRIP001          aStr.Insert(aNullCode, 0);
//STRIP001
//STRIP001      // zuviele Nachkommastellen abhacken
//STRIP001         xub_StrLen nNumDigits(rLoc.getNumDigits());
//STRIP001      xub_StrLen nWeg(nK - nNumDigits);
//STRIP001
//STRIP001      if(nWeg > 0)
//STRIP001      {
//STRIP001          // hier muesste eigentlich noch gerundet werden!
//STRIP001          aStr.Erase(aStr.Len() - nWeg);
//STRIP001          nK = nNumDigits;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Vorkommastellen fuer spaeter merken
//STRIP001  xub_StrLen nVorKomma(aStr.Len() - nK);
//STRIP001
//STRIP001  if(nK > 0)
//STRIP001  {
//STRIP001      // KommaChar einfuegen
//STRIP001      // erstmal trailing Zeros abhacken
//STRIP001      while(nK > 0 && aStr.GetChar(aStr.Len() - 1) == aNullCode)
//STRIP001      {
//STRIP001          aStr.Erase(aStr.Len() - 1);
//STRIP001          nK--;
//STRIP001      }
//STRIP001
//STRIP001      if(nK > 0)
//STRIP001      {
//STRIP001          // na, noch Nachkommastellen da?
//STRIP001             sal_Unicode cDec(rLoc.getNumDecimalSep().GetChar(0));
//STRIP001          aStr.Insert(cDec, nVorKomma);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // ggf. Trennpunkte bei jedem Tausender einfuegen
//STRIP001     if( nVorKomma > 3 )
//STRIP001  {
//STRIP001         String aThoSep( rLoc.getNumThousandSep() );
//STRIP001         if ( aThoSep.Len() > 0 )
//STRIP001         {
//STRIP001             sal_Unicode cTho( aThoSep.GetChar(0) );
//STRIP001             sal_Int32 i(nVorKomma - 3);
//STRIP001
//STRIP001             while(i > 0)
//STRIP001             {
//STRIP001                 rStr.Insert(cTho, (xub_StrLen)i);
//STRIP001                 i -= 3;
//STRIP001             }
//STRIP001         }
//STRIP001  }
//STRIP001
//STRIP001  if(!aStr.Len())
//STRIP001      aStr += aNullCode;
//STRIP001
//STRIP001  if(bNeg && (aStr.Len() > 1 || aStr.GetChar(0) != aNullCode))
//STRIP001  {
//STRIP001      rStr.Insert(sal_Unicode('-'), 0);
//STRIP001  }
//STRIP001
//STRIP001  rStr = aStr;
//STRIP001 }

//STRIP001 void SdrFormatter::TakeUnitStr(MapUnit eUnit, XubString& rStr)
//STRIP001 {
//STRIP001  switch(eUnit)
//STRIP001  {
//STRIP001      // Metrisch
//STRIP001      case MAP_100TH_MM   :
//STRIP001      {
//STRIP001          sal_Char aText[] = "/100mm";
//STRIP001          rStr = UniString(aText, sizeof(aText-1));
//STRIP001          break;
//STRIP001      }
//STRIP001      case MAP_10TH_MM    :
//STRIP001      {
//STRIP001          sal_Char aText[] = "/10mm";
//STRIP001          rStr = UniString(aText, sizeof(aText-1));
//STRIP001          break;
//STRIP001      }
//STRIP001      case MAP_MM         :
//STRIP001      {
//STRIP001          sal_Char aText[] = "mm";
//STRIP001          rStr = UniString(aText, sizeof(aText-1));
//STRIP001          break;
//STRIP001      }
//STRIP001      case MAP_CM         :
//STRIP001      {
//STRIP001          sal_Char aText[] = "cm";
//STRIP001          rStr = UniString(aText, sizeof(aText-1));
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      // Inch
//STRIP001      case MAP_1000TH_INCH:
//STRIP001      {
//STRIP001          sal_Char aText[] = "/1000\"";
//STRIP001          rStr = UniString(aText, sizeof(aText-1));
//STRIP001          break;
//STRIP001      }
//STRIP001      case MAP_100TH_INCH :
//STRIP001      {
//STRIP001          sal_Char aText[] = "/100\"";
//STRIP001          rStr = UniString(aText, sizeof(aText-1));
//STRIP001          break;
//STRIP001      }
//STRIP001      case MAP_10TH_INCH  :
//STRIP001      {
//STRIP001          sal_Char aText[] = "/10\"";
//STRIP001          rStr = UniString(aText, sizeof(aText-1));
//STRIP001          break;
//STRIP001      }
//STRIP001      case MAP_INCH       :
//STRIP001      {
//STRIP001          rStr = UniString();
//STRIP001          rStr += sal_Unicode('"');
//STRIP001          break;
//STRIP001      }
//STRIP001      case MAP_POINT      :
//STRIP001      {
//STRIP001          sal_Char aText[] = "pt";
//STRIP001          rStr = UniString(aText, sizeof(aText-1));
//STRIP001          break;
//STRIP001      }
//STRIP001      case MAP_TWIP       :
//STRIP001      {
//STRIP001          sal_Char aText[] = "twip";
//STRIP001          rStr = UniString(aText, sizeof(aText-1));
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      // Sonstiges
//STRIP001      case MAP_PIXEL      :
//STRIP001      {
//STRIP001          sal_Char aText[] = "pixel";
//STRIP001          rStr = UniString(aText, sizeof(aText-1));
//STRIP001          break;
//STRIP001      }
//STRIP001      case MAP_SYSFONT    :
//STRIP001      {
//STRIP001          sal_Char aText[] = "sysfont";
//STRIP001          rStr = UniString(aText, sizeof(aText-1));
//STRIP001          break;
//STRIP001      }
//STRIP001      case MAP_APPFONT    :
//STRIP001      {
//STRIP001          sal_Char aText[] = "appfont";
//STRIP001          rStr = UniString(aText, sizeof(aText-1));
//STRIP001          break;
//STRIP001      }
//STRIP001      case MAP_RELATIVE   :
//STRIP001      {
//STRIP001          rStr = UniString();
//STRIP001          rStr += sal_Unicode('%');
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrFormatter::TakeUnitStr(FieldUnit eUnit, XubString& rStr)
//STRIP001 {
//STRIP001  switch(eUnit)
//STRIP001  {
//STRIP001      default             :
//STRIP001      case FUNIT_NONE     :
//STRIP001      case FUNIT_CUSTOM   :
//STRIP001      {
//STRIP001          rStr = UniString();
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      // Metrisch
//STRIP001      case FUNIT_100TH_MM:
//STRIP001      {
//STRIP001          sal_Char aText[] = "/100mm";
//STRIP001          rStr = UniString(aText, sizeof(aText-1));
//STRIP001          break;
//STRIP001      }
//STRIP001      case FUNIT_MM     :
//STRIP001      {
//STRIP001          sal_Char aText[] = "mm";
//STRIP001          rStr = UniString(aText, sizeof(aText-1));
//STRIP001          break;
//STRIP001      }
//STRIP001      case FUNIT_CM     :
//STRIP001      {
//STRIP001          sal_Char aText[] = "cm";
//STRIP001          rStr = UniString(aText, sizeof(aText-1));
//STRIP001          break;
//STRIP001      }
//STRIP001      case FUNIT_M      :
//STRIP001      {
//STRIP001          rStr = UniString();
//STRIP001          rStr += sal_Unicode('m');
//STRIP001          break;
//STRIP001      }
//STRIP001      case FUNIT_KM     :
//STRIP001      {
//STRIP001          sal_Char aText[] = "km";
//STRIP001          rStr = UniString(aText, sizeof(aText-1));
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      // Inch
//STRIP001      case FUNIT_TWIP   :
//STRIP001      {
//STRIP001          sal_Char aText[] = "twip";
//STRIP001          rStr = UniString(aText, sizeof(aText-1));
//STRIP001          break;
//STRIP001      }
//STRIP001      case FUNIT_POINT  :
//STRIP001      {
//STRIP001          sal_Char aText[] = "pt";
//STRIP001          rStr = UniString(aText, sizeof(aText-1));
//STRIP001          break;
//STRIP001      }
//STRIP001      case FUNIT_PICA   :
//STRIP001      {
//STRIP001          sal_Char aText[] = "pica";
//STRIP001          rStr = UniString(aText, sizeof(aText-1));
//STRIP001          break;
//STRIP001      }
//STRIP001      case FUNIT_INCH   :
//STRIP001      {
//STRIP001          rStr = UniString();
//STRIP001          rStr += sal_Unicode('"');
//STRIP001          break;
//STRIP001      }
//STRIP001      case FUNIT_FOOT   :
//STRIP001      {
//STRIP001          sal_Char aText[] = "ft";
//STRIP001          rStr = UniString(aText, sizeof(aText-1));
//STRIP001          break;
//STRIP001      }
//STRIP001      case FUNIT_MILE   :
//STRIP001      {
//STRIP001          sal_Char aText[] = "mile(s)";
//STRIP001          rStr = UniString(aText, sizeof(aText-1));
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      // sonstiges
//STRIP001      case FUNIT_PERCENT:
//STRIP001      {
//STRIP001          rStr = UniString();
//STRIP001          rStr += sal_Unicode('%');
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////


}
