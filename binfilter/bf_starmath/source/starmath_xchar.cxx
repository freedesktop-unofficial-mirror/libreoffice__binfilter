/*************************************************************************
 *
 *  $RCSfile: starmath_xchar.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: vg $ $Date: 2005-02-16 17:41:40 $
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

#ifndef _STREAM_HXX
#include <tools/stream.hxx>
#endif
#ifndef _XOUTX_HXX //autogen
#include <bf_svx/xoutx.hxx>
#endif

#include "xchar.hxx"
#include "types.hxx"

#include "smdll.hxx"
#include "starmath.hrc"
namespace binfilter {



//STRIP001 PolyPolygon  SmGetPolyPolygon(const XPolyPolygon &rPoly, OutputDevice *pDev)
//STRIP001  // convert XPolyPolygon in PolyPolygon
//STRIP001 {
//STRIP001  PolyPolygon aResult(rPoly.Count());
//STRIP001
//STRIP001  USHORT  n = rPoly.Count();
//STRIP001  for (USHORT i = 0;  i < n;  i++)
//STRIP001  {   // nRough = 1 is maximal resolution
//STRIP001      Polygon  aTmp (XOutCreatePolygon(rPoly[i], pDev, 1));
//STRIP001      aResult.Insert(aTmp, i);
//STRIP001  }
//STRIP001
//STRIP001  return aResult;
//STRIP001 }


//STRIP001 XPolyPolygon & SmLogicToPixel(XPolyPolygon &rXPPoly, const OutputDevice &rDev)
//STRIP001  // convert points of 'rXPPoly' from logic coordinates to pixel coordinates
//STRIP001  // according to 'rDev'.
//STRIP001 {
//STRIP001  USHORT  n = rXPPoly.Count();
//STRIP001  for (USHORT i = 0;  i < n;  i++)
//STRIP001  {   XPolygon  &rXPoly = rXPPoly[i];
//STRIP001
//STRIP001      USHORT  m = rXPoly.GetPointCount();
//STRIP001      for (USHORT j = 0;  j < m;  j++)
//STRIP001      {   Point &rPoint = rXPoly[j];
//STRIP001
//STRIP001          rPoint = rDev.LogicToPixel(rPoint);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return rXPPoly;
//STRIP001 }


//STRIP001 XPolyPolygon & SmPixelToLogic(XPolyPolygon &rXPPoly, const OutputDevice &rDev)
//STRIP001  // convert points of 'rXPPoly' from pixel coordinates to logic coordinates
//STRIP001  // according to 'rDev'.
//STRIP001 {
//STRIP001  for (USHORT i = rXPPoly.Count() - 1;  i >= 0;  i--)
//STRIP001  {   XPolygon  &rXPoly = rXPPoly[i];
//STRIP001
//STRIP001      for (USHORT j = rXPoly.GetPointCount() - 1;  j >= 0;  j--)
//STRIP001      {   Point &rPoint = rXPoly[j];
//STRIP001
//STRIP001          rPoint = rDev.PixelToLogic(rPoint);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return rXPPoly;
//STRIP001 }


////////////////////////////////////////


//STRIP001 static BOOL SmWillBeVisible(const Point &rStart, const Point &rEnd)
//STRIP001  // returns TRUE iff 'SmDrawPolygon' has to draw a line
//STRIP001 {
//STRIP001  return      rStart.Y() >  rEnd.Y()
//STRIP001          ||  rStart.Y() == rEnd.Y()  &&  rStart.X() < rEnd.X();
//STRIP001 }



//STRIP001 void SmDrawPolyPolygon(OutputDevice &rDev, const PolyPolygon &rPPoly)
//STRIP001  // workaround for the "polygon vanishes partly or in whole bug" that
//STRIP001  // occurs when the linecolor is not set.
//STRIP001  // It should become superfluous in the near future when the bug is fixed.
//STRIP001 {
//STRIP001  Point  aFrom,
//STRIP001         aPF, aPT;
//STRIP001  int    nIdx;
//STRIP001
//STRIP001  USHORT  nPolys = rPPoly.Count();
//STRIP001  for (USHORT i = 0;  i < nPolys;  i++)
//STRIP001  {   const Polygon &rPoly = rPPoly[i];
//STRIP001
//STRIP001      USHORT  nPoints = rPoly.GetSize();
//STRIP001      if (nPoints >= 2)
//STRIP001          aFrom = rPoly[0];
//STRIP001      for (USHORT j = 1;  j < nPoints;  j++)
//STRIP001      {   const Point &rTo = rPoly[j];
//STRIP001
//STRIP001          aPF = aFrom;
//STRIP001          aPT = rTo;
//STRIP001
//STRIP001          BOOL bDraw = TRUE;
//STRIP001
//STRIP001          if (aFrom.Y() > rTo.Y())
//STRIP001          {   if (aFrom.X() == rTo.X())
//STRIP001              {   // draw startpoint only if previous line is to be drawn
//STRIP001                  nIdx = j - 2;
//STRIP001                  if (nIdx < 0)
//STRIP001                      nIdx += nPoints;
//STRIP001
//STRIP001                  if (   !SmWillBeVisible(rPoly[nIdx], aFrom)
//STRIP001                      &&  aPF.Y() > aPT.Y())
//STRIP001                          aPF.Y()--;
//STRIP001              }
//STRIP001          }
//STRIP001          else if (aFrom.Y() == rTo.Y()  &&  aFrom.X() < rTo.X())
//STRIP001          {   // draw endpoint only if next line is to be drawn
//STRIP001                  nIdx = j + 1;
//STRIP001                  if (nIdx == nPoints)
//STRIP001                      nIdx = 0;
//STRIP001
//STRIP001                  if (   !SmWillBeVisible(rTo, rPoly[nIdx])
//STRIP001                      &&  aPT.X() > aPF.X())
//STRIP001                          aPT.X()--;
//STRIP001          }
//STRIP001          else
//STRIP001              bDraw = FALSE;
//STRIP001
//STRIP001          if (bDraw)
//STRIP001              rDev.DrawLine(aPF, aPT);
//STRIP001
//STRIP001          aFrom = rTo;
//STRIP001      }
//STRIP001  }
//STRIP001 }


////////////////////////////////////////


/*?*/ class SmPolygonLoader : public Resource
/*?*/ {
/*?*/ public:
/*?*/   SmPolygonLoader(const SmResId &rId, SmPolygon &rSmPolygon);
/*?*/ };


/*N*/ SmPolygonLoader::SmPolygonLoader(const SmResId& rId, SmPolygon &rSmPolygon)
/*N*/ : Resource (rId)
/*N*/ {
/*N*/   USHORT  nBytesLeft;     // upper size limit to a single resource is 64 kB!
/*N*/
/*N*/   // set cursor to begin of resource
/*N*/   //GetClassRes();    // it's done automatically!
/*N*/
/*N*/   // get number of bytes from actual position to end of resource
/*N*/   nBytesLeft = GetRemainSizeRes();
/*N*/
/*N*/   char *pStr = (char *) GetClassRes();
/*N*/   SvMemoryStream  aStrm(pStr, nBytesLeft, STREAM_READ);
/*N*/
/*N*/   aStrm >> rSmPolygon.cChar
/*N*/         >> rSmPolygon.aFontSize
/*N*/         >> rSmPolygon.aOrigPos
/*N*/         >> rSmPolygon.aOrigSize
/*N*/         >> rSmPolygon.aPoly;
/*N*/
/*N*/   //! Warning: don't know why, but it has to be done!
/*N*/   IncrementRes(nBytesLeft);
/*N*/ }


////////////////////////////////////////
// SmPolygon
//

/*N*/ SmPolygon::SmPolygon()
/*N*/ {
/*N*/   cChar = sal_Char('\x00'),
/*N*/   fScaleX = fScaleY =
/*N*/   fDelayedFactorX = fDelayedFactorY = 1.0;
/*N*/   bDelayedScale = bDelayedBoundRect = FALSE;
/*N*/ }


/*N*/ SmPolygon::SmPolygon(sal_Unicode cCharP)
/*N*/ {
/*N*/   cChar = cCharP;
/*N*/   fScaleX = fScaleY =
/*N*/   fDelayedFactorX = fDelayedFactorY = 1.0;
/*N*/   bDelayedScale = bDelayedBoundRect = FALSE;
/*N*/
/*N*/   if (cChar == sal_Char('\0'))
/*N*/       return;
/*N*/
/*N*/   // get appropriate resource id
/*N*/   int  nResId = 0;
/*N*/     switch (cChar)
/*N*/   {
/*N*/       case MS_LINE :          nResId = RID_XPP_LINE;          break;
/*N*/       case MS_DLINE :         nResId = RID_XPP_DLINE;         break;
/*N*/       case MS_SQRT :          nResId = RID_XPP_SQRT;          break;
/*N*/       case MS_SQRT2 :         nResId = RID_XPP_SQRT2;         break;
/*N*/       case MS_HAT :           nResId = RID_XPP_HAT;           break;
/*N*/       case MS_TILDE :         nResId = RID_XPP_TILDE;         break;
/*N*/       case MS_BAR :           nResId = RID_XPP_BAR;           break;
/*N*/       case MS_VEC :           nResId = RID_XPP_VEC;           break;
/*N*/       case MS_LBRACE :        nResId = RID_XPP_LBRACE;        break;
/*N*/       case MS_RBRACE :        nResId = RID_XPP_RBRACE;        break;
/*N*/       case MS_LPARENT :       nResId = RID_XPP_LPARENT;       break;
/*N*/       case MS_RPARENT :       nResId = RID_XPP_RPARENT;       break;
/*N*/       case MS_LANGLE :        nResId = RID_XPP_LANGLE;        break;
/*N*/       case MS_RANGLE :        nResId = RID_XPP_RANGLE;        break;
/*N*/       case MS_LBRACKET :      nResId = RID_XPP_LBRACKET;      break;
/*N*/       case MS_RBRACKET :      nResId = RID_XPP_RBRACKET;      break;
/*N*/       case MS_LDBRACKET :     nResId = RID_XPP_LDBRACKET;     break;
/*N*/       case MS_RDBRACKET :     nResId = RID_XPP_RDBRACKET;     break;
/*N*/       case MS_LCEIL :         nResId = RID_XPP_LCEIL;         break;
/*N*/       case MS_RCEIL :         nResId = RID_XPP_RCEIL;         break;
/*N*/       case MS_LFLOOR :        nResId = RID_XPP_LFLOOR;        break;
/*N*/       case MS_RFLOOR :        nResId = RID_XPP_RFLOOR;        break;
/*N*/       case MS_OVERBRACE :     nResId = RID_XPP_OVERBRACE;     break;
/*N*/       case MS_UNDERBRACE :    nResId = RID_XPP_UNDERBRACE;    break;
/*N*/
/*N*/       default :
/*N*/           DBG_ASSERT(0, "Sm: char hat kein Polygon");
/*N*/   }
/*N*/
/*N*/   if (nResId)
/*N*/   {
/*N*/       // SmPolygon (XPolyPolygon, ...) aus der Resource laden
/*N*/       SmResId aSmResId(nResId);
/*N*/       SmPolygonLoader(aSmResId, *this);
/*N*/
/*N*/       // die verbleibenden member Variablen setzen
/*N*/       aBoundRect = aPoly.GetBoundRect();
/*N*/       aPos       = GetOrigPos();
/*N*/
/*N*/       // jetzt nach (0, 0) verschieben verbessert die Chancen, dass in Scale()
/*N*/       // (welches ia oefter aufgerufen wird) nicht das MoveTo ausgefuehrt
/*N*/       // werden muss
/*N*/       MoveTo(Point());
/*N*/   }
/*N*/ }


/*N*/ void SmPolygon::Scale()
/*N*/ {
/*N*/   DBG_ASSERT(bDelayedScale, "Sm: es gibt nichts zu skalieren");
/*N*/
/*N*/   Point aOrigin,
/*N*/         aDelta;
/*N*/
/*N*/   if (aPos != aOrigin)
/*N*/   {
/*?*/       aDelta = aOrigin - aPos;
/*?*/       aPoly.Move(aDelta.X(), aDelta.Y());
/*N*/   }
/*N*/
/*N*/   aPoly.Scale(fDelayedFactorX, fDelayedFactorY);
/*N*/   fScaleX *= fDelayedFactorX;
/*N*/   fScaleY *= fDelayedFactorY;
/*N*/
/*N*/   bDelayedScale = FALSE;
/*N*/   fDelayedFactorX = fDelayedFactorY = 1.0;
/*N*/
/*N*/   // Anm.: aBoundRect stimmt hier immer noch nicht!
/*N*/   // Das passiert erst wenn es benoetigt wird.
/*N*/
/*N*/   // ggf Ausgangsposition wiederherstellen
/*N*/   if (aPos != aOrigin)
/*?*/       aPoly.Move(-aDelta.X(), -aDelta.Y());
/*?*/
/*N*/ }


/*N*/ void SmPolygon::ScaleBy(double fFactorX, double fFactorY)
/*N*/ {
/*N*/   if (fFactorX != 1.0  ||  fFactorY != 1.0)
/*N*/   {
/*N*/       fDelayedFactorX *= fFactorX;
/*N*/       fDelayedFactorY *= fFactorY;
/*N*/
/*N*/       bDelayedScale = TRUE;
/*N*/       bDelayedBoundRect = TRUE;
/*N*/   }
/*N*/ }


/*N*/ void SmPolygon::AdaptToX(const OutputDevice &rDev, ULONG nWidth)
/*N*/ {
/*N*/   DBG_ASSERT(aOrigSize.Width() != 0, "Sm: Polygon hat keine Breite");
/*N*/   if (aOrigSize.Width() != 0)
/*N*/   {
/*N*/       double  fFactor = 1.0 / GetScaleX() * nWidth / aOrigSize.Width();
/*N*/       ScaleBy(fFactor, 1.0);
/*N*/   }
/*N*/ }


/*N*/ void SmPolygon::AdaptToY(const OutputDevice &rDev, ULONG nHeight)
/*N*/ {
/*N*/   DBG_ASSERT(aOrigSize.Height() != 0, "Sm: Polygon hat keine Hoehe");
/*N*/   if (aOrigSize.Height() != 0)
/*N*/   {
/*N*/       double  fFactor = 1.0 / GetScaleY() * nHeight / aOrigSize.Height();
/*N*/       ScaleBy(1.0, fFactor);
/*N*/   }
/*N*/ }


/*N*/ void SmPolygon::Move(const Point &rPoint)
/*N*/ {
/*N*/   long  nX = rPoint.X(),
/*N*/         nY = rPoint.Y();
/*N*/
/*N*/   aPoly     .Move(nX, nY);
/*N*/   aBoundRect.Move(nX, nY);
/*N*/   aPos      .Move(nX, nY);
/*N*/ }


//STRIP001 const XPolyPolygon & SmPolygon::GetXPolyPolygon() const
//STRIP001 {
//STRIP001  if (bDelayedScale)
//STRIP001      ((SmPolygon *) this)->Scale();
//STRIP001  return aPoly;
//STRIP001 }


/*N*/ const Rectangle & SmPolygon::GetBoundRect(const OutputDevice &rDev) const
/*N*/ {
/*N*/   SmPolygon *pNCthis = ((SmPolygon *) this);
/*N*/
/*N*/   if (bDelayedScale)
/*N*/       pNCthis->Scale();
/*N*/   if (bDelayedBoundRect)
/*N*/   {
/*N*/       pNCthis->aBoundRect = aPoly.GetBoundRect((OutputDevice *) &rDev);
/*N*/       pNCthis->bDelayedBoundRect = FALSE;
/*N*/   }
/*N*/   return aBoundRect;
/*N*/ }


//STRIP001 void SmPolygon::Draw(OutputDevice &rDev, const Point &rPoint) const
//STRIP001 {
//STRIP001  if (bDelayedScale)
//STRIP001      ((SmPolygon *) this)->Scale();
//STRIP001
//STRIP001  // align output position with pixel position
//STRIP001  Point aPos (rDev.PixelToLogic(rDev.LogicToPixel(rPoint)));
//STRIP001
//STRIP001  PolyPolygon  aDrawPoly (SmGetPolyPolygon(aPoly, &rDev));
//STRIP001
//STRIP001  Point  aDelta (aPos - aDrawPoly.GetBoundRect().TopLeft());
//STRIP001  aDrawPoly.Move(aDelta.X(), aDelta.Y());
//STRIP001
//STRIP001  rDev.DrawPolyPolygon(aDrawPoly);
//STRIP001
//STRIP001  if (rDev.GetOutDevType() != OUTDEV_PRINTER)
//STRIP001  {   // workaround to avoid vanishing of the polygon
//STRIP001      Color aOldCol = rDev.GetLineColor();
//STRIP001      rDev.SetLineColor(rDev.GetFont().GetColor());
//STRIP001      SmDrawPolyPolygon(rDev, aDrawPoly);
//STRIP001      rDev.SetLineColor(aOldCol);
//STRIP001  }
//STRIP001 }


}
