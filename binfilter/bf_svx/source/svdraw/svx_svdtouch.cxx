/*************************************************************************
 *
 *  $RCSfile: svx_svdtouch.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 16:32:28 $
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

// auto strip #include "svdtouch.hxx"
// auto strip #include "xoutx.hxx"

#ifndef _BIGINT_HXX //autogen
#include <tools/bigint.hxx>
#endif
#ifndef _TL_POLY_HXX
#include <tools/poly.hxx>
#endif
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ class ImpPolyHitCalc {
/*N*/ public:
/*N*/   long x1,x2,y1,y2; // Koordinaten des Rect, muessen sortiert sein!
/*N*/   FASTBOOL bEdge;       // ein Punkt lag genau auf einer Kante
/*N*/   FASTBOOL bIntersect;  // mind. 2 Punkte auf verschiedenen Seiten einer Kante
/*N*/   FASTBOOL bPntInRect;  // mind. 1 Punkt war vollstaendig im Rect
/*N*/   USHORT   nOCnt;       // wenn Counter ungerade, dann getroffen
/*N*/   USHORT   nUCnt;       // wenn Counter ungerade, dann getroffen
/*N*/   USHORT   nLCnt;       // wenn Counter ungerade, dann getroffen
/*N*/   USHORT   nRCnt;       // wenn Counter ungerade, dann getroffen
/*N*/   FASTBOOL bLine;       // TRUE=PolyLine, kein Polygon
/*N*/ public:
/*N*/   ImpPolyHitCalc(const Rectangle& aR, FASTBOOL bIsLine=FALSE)
/*N*/   {
/*N*/       bLine=bIsLine;
/*N*/       bEdge=FALSE;
/*N*/       bIntersect=FALSE;
/*N*/       bPntInRect=FALSE;
/*N*/       x1=aR.Left();
/*N*/       x2=aR.Right();
/*N*/       y1=aR.Top();
/*N*/       y2=aR.Bottom();
/*N*/       nOCnt=0;
/*N*/       nUCnt=0;
/*N*/       nLCnt=0;
/*N*/       nRCnt=0;
/*N*/   }
/*N*/   FASTBOOL IsDecided() { return bEdge || bIntersect || bPntInRect; }
/*N*/   void CheckPntInRect(const Point& rP)
/*N*/   {
/*N*/       if (!bPntInRect) {
/*N*/           bPntInRect=rP.X()>=x1 && rP.X()<=x2 && rP.Y()>=y1 && rP.Y()<=y2;
/*N*/       }
/*N*/   }
/*N*/   FASTBOOL IsHit() { return (!bLine && (nOCnt & 1)==1) || IsDecided(); }
/*N*/ };

/*N*/ #define CAREFUL_MULDIV(Res,Val,Mul,Div) {      \
/*N*/     if (Abs(Val)>0xB504 || Abs(Mul)>0xB504) {  \
/*N*/         BigInt aBigTemp(Val);                  \
/*N*/         aBigTemp*=Mul;                         \
/*N*/         aBigTemp/=Div;                         \
/*N*/         Res=long(aBigTemp);                    \
/*N*/     } else {                                   \
/*N*/         Res=Val*Mul/Div;                       \
/*N*/     }                                          \
/*N*/ }

/*N*/ void ImpCheckIt(ImpPolyHitCalc& rH, long lx1, long ly1, long lx2, long ly2,
/*N*/            long rx1, long ry1, long rx2, long ry2, USHORT& nOCnt, USHORT& nUCnt)
/*N*/ {
/*N*/   if ((ly1>ly2) || ((ly1==ly2) && (lx1>lx2))) {
/*N*/       long nTmp; // die 2 Punkte nach Y sortieren
/*N*/       nTmp=lx1;
/*N*/       lx1=lx2;
/*N*/       lx2=nTmp;
/*N*/       nTmp=ly1;
/*N*/       ly1=ly2;
/*N*/       ly2=nTmp;
/*N*/   }
/*N*/   FASTBOOL b1=FALSE,b2=FALSE,b3=FALSE,b4=FALSE; // je 1 Flag fuer jeden der 4 Punkte LO,RO,LU,RU
/*N*/   FASTBOOL bx1,bx2;
/*N*/   FASTBOOL by1=ly1<=ry1 && ly2>ry1;
/*N*/   FASTBOOL by2=ly1<=ry2 && ly2>ry2;
/*N*/   long dx,dy,a;
/*N*/   if (by1 || by2) {
/*N*/       dx=lx2-lx1;
/*N*/       dy=ly2-ly1;
/*N*/   }
/*N*/   if (by1) { // Nur wer die Scanline schneidet
/*N*/       bx1=lx1<rx1;                    // x1,y1
/*N*/       bx2=lx2<rx1;
/*N*/       FASTBOOL bA=FALSE; // Optimierung: ggf eine Division sparen
/*N*/       if (bx1 && bx2) b1=TRUE;
/*N*/       else if (bx1 || bx2) {
/*N*/           long yTemp=ry1-ly1;
/*N*/           CAREFUL_MULDIV(a,dx,yTemp,dy); // a=dx*yTemp/dy;
/*N*/           a+=lx1;
/*N*/           bA=TRUE;
/*N*/           rH.bEdge=(a==rx1);
/*N*/           if (a<rx1) b1=TRUE;
/*N*/       }                                     // x2,y1
/*N*/       bx1=lx1<rx2;
/*N*/       bx2=lx2<rx2;
/*N*/       if (bx1 && bx2) b2=TRUE;
/*N*/       else if (bx1 || bx2) {
/*N*/           if (!bA) {
/*?*/               long yTemp=ry1-ly1;
/*?*/               CAREFUL_MULDIV(a,dx,yTemp,dy);
/*?*/               a+=lx1;
/*N*/           }
/*N*/           rH.bEdge=(a==rx2);
/*N*/           if (a<rx2) b2=TRUE;
/*N*/       }
/*N*/   }
/*N*/   if (by2) { // Nur wer die Scanline schneidet
/*N*/       bx1=lx1<rx1;                    // x1,y2
/*N*/       bx2=lx2<rx1;
/*N*/       FASTBOOL bA=FALSE; // Optimierung: ggf eine Division sparen
/*N*/       if (bx1 && bx2) b3=TRUE;
/*N*/       else if (bx1 || bx2) {
/*N*/           long yTemp=ry2-ly1;
/*N*/           CAREFUL_MULDIV(a,dx,yTemp,dy);
/*N*/           a+=lx1;
/*N*/           bA=TRUE;
/*N*/           rH.bEdge=(a==rx1);
/*N*/           if (a<rx1) b3=TRUE;
/*N*/       }
/*N*/       bx1=lx1<rx2;                    // x2,y2
/*N*/       bx2=lx2<rx2;
/*N*/       if (bx1 && bx2) b4=TRUE;
/*N*/       else if (bx1 || bx2) {
/*N*/           if (!bA) {
/*N*/               long yTemp=ry2-ly1;
/*N*/               CAREFUL_MULDIV(a,dx,yTemp,dy);
/*N*/               a+=lx1;
/*N*/           }
/*N*/           rH.bEdge=(a==rx2);
/*N*/           if (a<rx2) b4=TRUE;
/*N*/       }
/*N*/   }
/*N*/   if (by1 || by2) { // nun die Ergebnisse auswerten
/*N*/       if (by1 && by2) { // Linie durch beide Scanlines
/*N*/           if (b1 && b2 && b3 && b4) { nOCnt++; nUCnt++; } // Rect komplett rechts neben der Linie
/*N*/           else if (b1 || b2 || b3 || b4) rH.bIntersect=TRUE; // Nur zum Teil->Schnittpunkt
/*N*/       } else { // ansonsten Ober- und Unterkante des Rects getrennt betrachten
/*N*/           if (by1) { // Linie durch Oberkante
/*N*/               if (b1 && b2) nOCnt++; // Oberkante komplett rechts neben der Linie
/*N*/               else if (b1 || b2) rH.bIntersect=TRUE; // Nur zum Teil->Schnittpunkt
/*N*/           }
/*N*/           if (by2) { // Linie durch Unterkante
/*N*/               if (b3 && b4) nUCnt++; // Unterkante komplett rechts neben der Linie
/*N*/               else if (b3 || b4) rH.bIntersect=TRUE; // Nur zum Teil->Schnittpunkt
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void CheckPolyHit(const Polygon& rPoly, ImpPolyHitCalc& rH)
/*N*/ {
/*N*/   USHORT nAnz=rPoly.GetSize();
/*N*/   if (nAnz==0) return;
/*N*/   if (nAnz==1) { rH.CheckPntInRect(rPoly[0]); return; }
/*N*/   Point aPt0=rPoly[USHORT(nAnz-1)];
/*N*/   rH.CheckPntInRect(aPt0);
/*N*/   USHORT i=0;
/*N*/   if (rH.bLine) {
/*N*/       aPt0=rPoly[0];
/*N*/       i++;
/*N*/   }
/*N*/   for (; i<nAnz && !rH.IsDecided(); i++) {
/*N*/       Point aP1(aPt0);
/*N*/       Point aP2(rPoly[i]);
/*N*/       rH.CheckPntInRect(aP2);
/*N*/       if (!rH.IsDecided()) {
/*N*/           ImpCheckIt(rH,aP1.X(),aP1.Y(),aP2.X(),aP2.Y(),rH.x1,rH.y1,rH.x2,rH.y2,rH.nOCnt,rH.nUCnt);
/*N*/           ImpCheckIt(rH,aP1.Y(),aP1.X(),aP2.Y(),aP2.X(),rH.y1,rH.x1,rH.y2,rH.x2,rH.nLCnt,rH.nRCnt);
/*N*/       }
/*N*/       aPt0=rPoly[i];
/*N*/   }
/*N*/   if (!rH.bLine) { // Sicherheitshalber nochmal checken
/*N*/       if ((rH.nOCnt&1)!=(rH.nUCnt&1)) rH.bIntersect=TRUE; // da wird wohl eine durchgegangen sein
/*N*/       if ((rH.nLCnt&1)!=(rH.nRCnt&1)) rH.bIntersect=TRUE; // da wird wohl eine durchgegangen sein
/*N*/       if ((rH.nOCnt&1)!=(rH.nLCnt&1)) rH.bIntersect=TRUE; // da wird wohl eine durchgegangen sein
/*N*/   }
/*N*/ }

//STRIP001 FASTBOOL IsRectTouchesPoly(const Polygon& rPoly, const Rectangle& rHit)
//STRIP001 {
//STRIP001  ImpPolyHitCalc aHit(rHit);
//STRIP001  CheckPolyHit(rPoly,aHit);
//STRIP001  return aHit.IsHit();
//STRIP001 }

/*N*/ FASTBOOL IsRectTouchesPoly(const PolyPolygon& rPoly, const Rectangle& rHit)
/*N*/ {
/*N*/   ImpPolyHitCalc aHit(rHit);
/*N*/   USHORT nAnz=rPoly.Count();
/*N*/   for (USHORT i=0; i<nAnz && !aHit.IsDecided(); i++) {
/*N*/       CheckPolyHit(rPoly.GetObject(i),aHit);
/*N*/   }
/*N*/   return aHit.IsHit();
/*N*/ }

//STRIP001 FASTBOOL IsRectTouchesPoly(const XPolygon& rPoly, const Rectangle& rHit, OutputDevice* pOut)
//STRIP001 {
//STRIP001  return IsRectTouchesPoly(XOutCreatePolygon(rPoly,pOut),rHit);
//STRIP001 }

//STRIP001 FASTBOOL IsRectTouchesPoly(const XPolyPolygon& rPoly, const Rectangle& rHit, OutputDevice* pOut)
//STRIP001 {
//STRIP001  ImpPolyHitCalc aHit(rHit);
//STRIP001  USHORT nAnz=rPoly.Count();
//STRIP001  for (USHORT i=0; i<nAnz && !aHit.IsDecided(); i++) {
//STRIP001      CheckPolyHit(XOutCreatePolygon(rPoly[i],pOut),aHit);
//STRIP001  }
//STRIP001  return aHit.IsHit();
//STRIP001 }

//STRIP001 FASTBOOL IsRectTouchesLine(const Point& rPt1, const Point& rPt2, const Rectangle& rHit)
//STRIP001 {
//STRIP001  Polygon aPol(2);
//STRIP001  aPol[0]=rPt1;
//STRIP001  aPol[1]=rPt2;
//STRIP001  ImpPolyHitCalc aHit(rHit,TRUE);
//STRIP001  CheckPolyHit(aPol,aHit);
//STRIP001  return aHit.IsHit();
//STRIP001 }

/*N*/ FASTBOOL IsRectTouchesLine(const Polygon& rLine, const Rectangle& rHit)
/*N*/ {
/*N*/   ImpPolyHitCalc aHit(rHit,TRUE);
/*N*/   CheckPolyHit(rLine,aHit);
/*N*/   return aHit.IsHit();
/*N*/ }

//STRIP001 FASTBOOL IsRectTouchesLine(const PolyPolygon& rLine, const Rectangle& rHit)
//STRIP001 {
//STRIP001  ImpPolyHitCalc aHit(rHit,TRUE);
//STRIP001  USHORT nAnz=rLine.Count();
//STRIP001  for (USHORT nNum=0; nNum<nAnz && !aHit.IsHit(); nNum++) {
//STRIP001      CheckPolyHit(rLine[nNum],aHit);
//STRIP001  }
//STRIP001  return aHit.IsHit();
//STRIP001 }

//STRIP001 FASTBOOL IsRectTouchesLine(const XPolygon& rLine, const Rectangle& rHit, OutputDevice* pOut)
//STRIP001 {
//STRIP001  return IsRectTouchesLine(XOutCreatePolygon(rLine,pOut),rHit);
//STRIP001 }

//STRIP001 FASTBOOL IsRectTouchesLine(const XPolyPolygon& rLine, const Rectangle& rHit, OutputDevice* pOut)
//STRIP001 {
//STRIP001  ImpPolyHitCalc aHit(rHit,TRUE);
//STRIP001  USHORT nAnz=rLine.Count();
//STRIP001  for (USHORT nNum=0; nNum<nAnz && !aHit.IsHit(); nNum++) {
//STRIP001      CheckPolyHit(XOutCreatePolygon(rLine[nNum],pOut),aHit);
//STRIP001  }
//STRIP001  return aHit.IsHit();
//STRIP001 }

/*N*/ BYTE CheckPointTouchesPoly(const Polygon& rPoly, const Point& rHit) // 0=Ausserhalb, 1=Innerhalb, 2=Beruehrung
/*N*/ {
/*N*/   USHORT nAnz=rPoly.GetSize();
/*N*/   if (nAnz<2) return FALSE;
/*N*/   FASTBOOL bEdge=FALSE;
/*N*/   USHORT nCnt=0;
/*N*/   Point aPt0=rPoly[USHORT(nAnz-1)];
/*N*/   for (USHORT i=0; i<nAnz && !bEdge; i++) {
/*N*/       Point aP1(rPoly[i]);
/*N*/       Point aP2(aPt0);
/*N*/       if ((aP1.Y()>aP2.Y()) || ((aP1.Y()==aP2.Y()) && (aP1.X()>aP2.X()))) { Point aTmp(aP1); aP1=aP2; aP2=aTmp; }
/*N*/       bEdge=((aP1.X()==aP2.X()) && (rHit.X()==aP1.X()) && (rHit.Y()>=aP1.Y()) && (rHit.Y()<=aP2.Y())) ||
/*N*/             ((aP1.Y()==aP2.Y()) && (rHit.Y()==aP1.Y()) && (rHit.X()>=aP1.X()) && (rHit.X()<=aP2.X())) ||
/*N*/             (rHit.X()==aP1.X()) && (rHit.Y()==aP1.Y());
/*N*/       if (!bEdge && aP1.Y()<=rHit.Y() && aP2.Y()>rHit.Y()) { // Nur wer die Scanline schneidet
/*N*/           FASTBOOL bx1=aP1.X()<rHit.X();
/*N*/           FASTBOOL bx2=aP2.X()<rHit.X();
/*N*/           if (bx1 && bx2) nCnt++;
/*N*/           else if (bx1 || bx2) {
/*N*/               long dx=aP2.X()-aP1.X();
/*N*/               long dy=aP2.Y()-aP1.Y();
/*N*/               long yTemp=rHit.Y()-aP1.Y();
/*N*/               long xTemp;
/*N*/               if (Abs(dx)>0xB504 || Abs(yTemp)>0xB504) { // gegen Integerueberlaeufe
/*?*/                   BigInt aBigTemp(dx);
/*?*/                   aBigTemp*=yTemp;
/*?*/                   aBigTemp/=dy;
/*?*/                   xTemp=long(aBigTemp);
/*N*/               } else {
/*N*/                   xTemp=dx*yTemp /dy;
/*N*/               }
/*N*/               xTemp+=aP1.X();
/*N*/               bEdge=(xTemp==rHit.X());
/*N*/               if (xTemp<rHit.X()) nCnt++;
/*N*/           }
/*N*/       }
/*N*/       aPt0=rPoly[i];
/*N*/   }
/*N*/   if (bEdge) return 2;
/*N*/   return (nCnt & 1)==1;
/*N*/ }

/*N*/ FASTBOOL IsPointInsidePoly(const Polygon& rPoly, const Point& rHit)
/*N*/ {
/*N*/   return CheckPointTouchesPoly(rPoly,rHit)!=0;
/*N*/ }

//STRIP001 FASTBOOL IsPointInsidePoly(const PolyPolygon& rPoly, const Point& rHit)
//STRIP001 {
//STRIP001  FASTBOOL bInside=FALSE;
//STRIP001  FASTBOOL bEdge=FALSE;
//STRIP001  USHORT nAnz=rPoly.Count();
//STRIP001  for (USHORT i=0; i<nAnz && !bEdge; i++) {
//STRIP001      BYTE n=CheckPointTouchesPoly(rPoly.GetObject(i),rHit);
//STRIP001      bEdge=n==2;
//STRIP001      if (n==1) bInside=!bInside;
//STRIP001  }
//STRIP001  return bInside || bEdge;
//STRIP001 }

//STRIP001 FASTBOOL IsPointInsidePoly(const XPolygon& rPoly, const Point& rHit, OutputDevice* pOut)
//STRIP001 {
//STRIP001  return IsPointInsidePoly(XOutCreatePolygon(rPoly,pOut),rHit);
//STRIP001 }

//STRIP001 FASTBOOL IsPointInsidePoly(const XPolyPolygon& rPoly, const Point& rHit, OutputDevice* pOut)
//STRIP001 {
//STRIP001  FASTBOOL bInside=FALSE;
//STRIP001  FASTBOOL bEdge=FALSE;
//STRIP001  USHORT nAnz=rPoly.Count();
//STRIP001  for (USHORT i=0; i<nAnz && !bEdge; i++) {
//STRIP001      BYTE n=CheckPointTouchesPoly(XOutCreatePolygon(rPoly[i],pOut),rHit);
//STRIP001      bEdge=n==2;
//STRIP001      if (n==1) bInside=!bInside;
//STRIP001  }
//STRIP001  return bInside || bEdge;
//STRIP001
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////


}
