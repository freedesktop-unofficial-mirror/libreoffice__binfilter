/*************************************************************************
 *
 *  $RCSfile: sch_globfunc.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:39:53 $
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
#pragma optimize("e",off)


#pragma hdrstop
#define ITEMID_FONTLIST         0
#define ITEMID_POSTURE          0
#define ITEMID_WEIGHT           0
#define ITEMID_UNDERLINE        0
#define ITEMID_CROSSEDOUT       0
#define ITEMID_SHADOWED         0
#define ITEMID_AUTOKERN         0
#define ITEMID_WORDLINEMODE     0
#define ITEMID_CONTOUR          0
#define ITEMID_PROPSIZE         0
#define ITEMID_CHARSETCOLOR     0
#define ITEMID_KERNING          0
#define ITEMID_CASEMAP          0
#define ITEMID_ESCAPEMENT       0
#define ITEMID_LANGUAGE         0
#define ITEMID_NOLINEBREAK      0
#define ITEMID_NOHYPHENHERE     0
#define ITEMID_BLINK            0

#define ITEMID_FONT        EE_CHAR_FONTINFO
#define ITEMID_COLOR       EE_CHAR_COLOR
#define ITEMID_FONTHEIGHT  EE_CHAR_FONTHEIGHT
#define ITEMID_FONTWIDTH   EE_CHAR_FONTWIDTH

#include <svtools/whiter.hxx>

#include <bf_svx/eeitem.hxx>

#ifndef _SCHATTR_HXX
#include "schattr.hxx"
#endif
#ifndef _SVDPAGE_HXX //autogen
#include <bf_svx/svdpage.hxx>
#endif
#ifndef _SVX_CHRTITEM_HXX //autogen
#define ITEMID_DOUBLE           0
#define ITEMID_CHARTTEXTORDER   SCHATTR_TEXT_ORDER
#define ITEMID_CHARTTEXTORIENT  SCHATTR_TEXT_ORIENT
#define ITEMID_CHARTDATADESCR   SCHATTR_DATADESCR_DESCR
#include <bf_svx/chrtitem.hxx>
#endif


#include <bf_svx/fhgtitem.hxx>
#include <bf_svx/fwdtitem.hxx>

#ifndef _SVDOPATH_HXX //autogen
#include <bf_svx/svdopath.hxx>
#endif
#ifndef _SVDOCIRC_HXX //autogen
#include <bf_svx/svdocirc.hxx>
#endif
#ifndef _SVDORECT_HXX //autogen
#include <bf_svx/svdorect.hxx>
#endif


#ifndef _SVX_SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif

#ifndef _XLNCLIT_HXX
#include <bf_svx/xlnclit.hxx>
#endif
#ifndef _XFLCLIT_HXX
#include <bf_svx/xflclit.hxx>
#endif
#ifndef _SVX_DLGUTIL_HXX
#include <bf_svx/dlgutil.hxx>
#endif

#ifndef _CHTMODEL_HXX
#include <chtmodel.hxx>
#include <globfunc.hxx>
#endif

#ifndef _E3D_POLYGON3D_HXX
#include <bf_svx/polygn3d.hxx>
#endif

#ifndef _E3D_CUBE3D_HXX
#include <bf_svx/cube3d.hxx>
#endif

#ifndef _E3D_DLIGHT3D_HXX
#include <bf_svx/dlight3d.hxx>
#endif

#include "math.h"
#include "float.h"
#include <axisid.hxx>

#include "pairs.hxx"
#ifndef _SVX_COLRITEM_HXX //autogen
#include <bf_svx/colritem.hxx>
#endif

#include "chdescr.hxx"
#ifndef _SVX_FWDTITEM_HXX //autogen
#include <bf_svx/fwdtitem.hxx>
#endif
#ifndef _SVX_FONTITEM_HXX //autogen
#include <bf_svx/fontitem.hxx>
#endif
#ifndef _SVX_WGHTITEM_HXX //autogen
#include <bf_svx/wghtitem.hxx>
#endif
#ifndef _SVX_UDLNITEM_HXX //autogen
#include <bf_svx/udlnitem.hxx>
#endif
#ifndef _SVX_CRSDITEM_HXX //autogen
#include <bf_svx/crsditem.hxx>
#endif
#ifndef _SVX_POSTITEM_HXX //autogen
#include <bf_svx/postitem.hxx>
#endif
#ifndef _SVX_ITEM_HXX //autogen
#include <bf_svx/cntritem.hxx>
#endif
#ifndef _SVX_SHDDITEM_HXX //autogen
#include <bf_svx/shdditem.hxx>
#endif
#ifndef _SVX_ESCPITEM_HXX //autogen
#include <bf_svx/escpitem.hxx>
#endif
#ifndef _SVX_AKRNITEM_HXX //autogen
#include <bf_svx/akrnitem.hxx>
#endif
#ifndef _SVX_KERNITEM_HXX //autogen
#include <bf_svx/kernitem.hxx>
#endif
#ifndef _SVX_WRLMITEM_HXX //autogen
#include <bf_svx/wrlmitem.hxx>
#endif

#include <algorithm>
#include <functional>

/*************************************************************************
|*
|* Objekt attributieren
|*
\************************************************************************/
namespace binfilter {
/*N*/ SdrObject *SetObjectAttr (SdrObject  *pObj,
/*N*/                         UINT16     nID,
/*N*/                         BOOL       bProtect,
/*N*/                         BOOL       bResize,
/*N*/                         SfxItemSet *pAttr)
/*N*/ {
/*N*/   pObj->InsertUserData (new SchObjectId (nID));
/*N*/   pObj->SetMoveProtect (bProtect);
/*N*/   pObj->SetResizeProtect (bResize);
/*N*/   if (pAttr)
/*N*/ //-/      pObj->NbcSetAttributes (*pAttr, FALSE);//#63904# Nbc neu
/*N*/       pObj->SetItemSet(*pAttr);
/*N*/
/*N*/   return pObj;
/*N*/ }

/*************************************************************************
|*
|* Objektgruppe erzeugen
|*
\************************************************************************/

/*N*/ SdrObjList *CreateGroup (SdrObjList &rObjList,
/*N*/                        UINT16     nID,
/*N*/                        ULONG      nIndex)
/*N*/ {
/*N*/   SdrObjGroup *pGroup = (SdrObjGroup *) SetObjectAttr (new SchObjGroup, nID, TRUE, TRUE, 0);
/*N*/
/*N*/   rObjList.NbcInsertObject((SdrObject *) pGroup, nIndex);
/*N*/   return pGroup->GetSubList();
/*N*/ }

/*************************************************************************
|*
|* Objektgruppe erzeugen
|*
\************************************************************************/

/*N*/ SchObjGroup *CreateSimpleGroup (UINT16 nID,
/*N*/                               BOOL   bProtect,
/*N*/                               BOOL   bResize)
/*N*/ {
/*N*/   return (SchObjGroup *) SetObjectAttr (new SchObjGroup, nID, bProtect, bResize, 0);
/*N*/ }


/*************************************************************************
|*
|* Berechne kub. Spline
|*
\************************************************************************/

/*N*/ void CubicSpline (XPolygon &pKnownPoints,
/*N*/                 int      n,
/*N*/                 int      splineSize,
/*N*/                 XPolygon &pSplines)
/*N*/ {
/*N*/   double *h      = new double [n + 1];
/*N*/   double *m      = new double [n + 1];
/*N*/   double *q      = new double [n + 1];
/*N*/   double *u      = new double [n + 1];
/*N*/
/*N*/   for (int k = 1;
/*N*/            k <= n;
/*N*/            k ++)
/*N*/       h [k] = pKnownPoints [k].X () - pKnownPoints [k - 1].X ();
/*N*/
/*N*/   double p;
/*N*/   double lambda = 0.0;
/*N*/   double d      = 0.0;
/*N*/   double mue;
/*N*/
/*N*/   q [0] = -lambda / 2.0;
/*N*/   u [0] = d / 2.0;
/*N*/
/*N*/   int j;
/*N*/   for (j = 1;
/*N*/            j <= n;
/*N*/            j ++)
/*N*/   {
/*N*/       mue        = (j < n)
/*N*/                        ? h[j] / (h [j] + h [j + 1])
/*N*/                        : 0.0;
/*N*/       p          = mue * q [j - 1] + 2.0;
/*N*/       lambda     = 1.0 - mue;
/*N*/       q [j]      = -lambda / p;
/*N*/       d          = (j < n)
/*N*/                        ? 6.0 * ((pKnownPoints [j + 1].Y () - pKnownPoints [j].Y ()) / h [j + 1] -
/*N*/                                 (pKnownPoints [j].Y () - pKnownPoints [j - 1].Y ()) / h [j]) / (h [j] + h [j + 1])
/*N*/                        : 0.0;
/*N*/       u [j]      = (d - mue * u [j - 1]) / p;
/*N*/   }
/*N*/
/*N*/   m [n] = u [n];
/*N*/
/*N*/   for (j = n - 1;
/*N*/        j >= 0;
/*N*/        j --)
/*N*/       m [j] = q [j] * m [j + 1] + u [j];
/*N*/
/*N*/   for (j = 0;
/*N*/        j < n;
/*N*/        j ++)
/*N*/   {
/*N*/       double xStep = (pKnownPoints [j + 1].X () - pKnownPoints [j].X ()) / splineSize;
/*N*/       double x     = pKnownPoints [j].X ();
/*N*/
/*N*/       double alpha = pKnownPoints [j].Y ();
/*N*/       double gamma = m [j] / 2;
/*N*/       double beta  = (pKnownPoints [j + 1].Y () - pKnownPoints [j].Y ()) / h [j + 1] -
/*N*/                      ((2 * m [j] + m [j + 1]) * h [j + 1]) / 6;
/*N*/       double delta = (m [j + 1] - m [j]) / (6 * h [j + 1]);
/*N*/
/*N*/       for (int i = 0;
/*N*/                i < splineSize;
/*N*/                i ++)
/*N*/       {
/*N*/           double xdiff = (x - pKnownPoints [j].X ());
/*N*/           int    index = j * splineSize + i;
/*N*/
/*N*/           pSplines [(short) index].Y () = long(alpha + xdiff * (beta + xdiff * (gamma + xdiff * delta)));
/*N*/           pSplines [(short) index].X () = long(x);
/*N*/           x                            += xStep;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   pSplines [n * splineSize].Y () = pKnownPoints [n].Y ();
/*N*/   pSplines [n * splineSize].X () = pKnownPoints [n].X ();
/*N*/
/*N*/   delete[] h;
/*N*/   delete[] m;
/*N*/   delete[] q;
/*N*/   delete[] u;
/*N*/ }

/*************************************************************************
|*
|* Bestimme Knotenvektor fuer B-Spline
|*
\************************************************************************/

/*N*/ void TVector (int    n,
/*N*/             int    k,
/*N*/             double *t)
/*N*/ {
/*N*/   for (int i = 0;
/*N*/            i <= n + k;
/*N*/            i ++)
/*N*/   {
/*N*/       if (i < k) t [i] = 0;
/*N*/       else if (i <= n) t [i] = i - k + 1;
/*N*/            else t [i] = n - k + 2;
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Berechne linken Knotenvektor
|*
\************************************************************************/

/*N*/ double TLeft (double x,
/*N*/             int    i,
/*N*/             int    k,
/*N*/             double *t)
/*N*/ {
/*N*/   double deltaT = t [i + k - 1] - t [i];
/*N*/
/*N*/   return (deltaT == 0.0)
/*N*/              ? 0.0
/*N*/              : (x - t [i]) / deltaT;
/*N*/ }

/*************************************************************************
|*
|* Berechne rechten Knotenvektor
|*
\************************************************************************/

/*N*/ double TRight (double x,
/*N*/              int    i,
/*N*/              int    k,
/*N*/              double *t)
/*N*/ {
/*N*/   double deltaT = t [i + k] - t [i + 1];
/*N*/
/*N*/   return (deltaT == 0.0)
/*N*/              ? 0.0
/*N*/              : (t [i + k] - x) / deltaT;
/*N*/ }

/*************************************************************************
|*
|* Berechne Gewichtungsvektor
|*
\************************************************************************/

/*N*/ void BVector (double x,
/*N*/             int    n,
/*N*/             int    k,
/*N*/             double *b,
/*N*/             double *t)
/*N*/ {
/*N*/   for (int i = 0;
/*N*/            i <= n + k;
/*N*/            i ++)
/*N*/       b [i] = 0;
/*N*/
/*N*/   int i0 = (int) floor (x) + k - 1;
/*N*/   b [i0] = 1;
/*N*/
/*N*/   for (int j = 2;
/*N*/            j <= k;
/*N*/            j ++)
/*N*/       for (int i = 0;
/*N*/                i <= i0;
/*N*/                i ++)
/*N*/           b [i] = TLeft (x, i, j, t) * b [i] + TRight (x, i, j, t) * b [i + 1];
/*N*/ }

/*************************************************************************
|*
|* Berechne einzelnen Punkt
|*
\************************************************************************/

/*N*/ void BSPoint (int      n,
/*N*/             Point    &p1,
/*N*/             Point    &p2,
/*N*/             XPolygon &pKnownPoints,
/*N*/             double   *b)
/*N*/ {
/*N*/   for (int i = 0;
/*N*/            i <= n;
/*N*/            i ++)
/*N*/   {
/*N*/       p1.Y () = long(p1.Y () + b [i] * pKnownPoints [i].Y ());
/*N*/       p2.Y () = long(p2.Y () + b [n - i] * pKnownPoints [i].Y ());
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Berechne B-Spline
|*
\************************************************************************/

/*N*/ void approxMesh (int      splineSize,
/*N*/                XPolygon &pSplines,
/*N*/                XPolygon &pKnownPoints,
/*N*/                int      n,
/*N*/                int      k)
/*N*/ {
/*N*/   int    pCount   = splineSize * n;
/*N*/   double *b       = new double [n + k + 1];
/*N*/   double *t       = new double [n + k + 2];
/*N*/   double xStep    = ((double) n - (double) k + 2.0) / (double) pCount;
/*N*/   double dStep = ((double) pKnownPoints [n].X () - (double) pKnownPoints [0].X ()) / (double) pCount;
/*N*/   double dXUp     = pKnownPoints [0].X ();
/*N*/   double dXDown   = pKnownPoints [n].X ();
/*N*/   double x        = 0.0;
/*N*/   int    nEnd     = pCount / 2 + 1;
/*N*/
/*N*/   TVector (n, k, t);
/*N*/
/*N*/   for (int j = 0;
/*N*/            j <= nEnd;
/*N*/            j ++)
/*N*/   {
/*N*/       Point aPoint1;
/*N*/       Point aPoint2;
/*N*/
/*N*/       BVector (x, n, k, b, t);
/*N*/       BSPoint (n, aPoint1, aPoint2, pKnownPoints, b);
/*N*/
/*N*/       pSplines [j].X ()          = (int)(floor(dXUp)+0.5);
/*N*/       pSplines [j].Y ()          = aPoint1.Y ();
/*N*/       pSplines [pCount - j].X () = (int)(floor(dXDown)+0.5);
/*N*/       pSplines [pCount - j].Y () = aPoint2.Y ();
/*N*/
/*N*/       x      += xStep;
/*N*/       dXUp   += dStep;
/*N*/       dXDown -= dStep;
/*N*/   }
/*N*/
/*N*/   delete[] t;
/*N*/   delete[] b;
/*N*/ }

/*************************************************************************
|*
|* Passe untere Grenze an den Wertebereich an
|*
\************************************************************************/

/*N*/ double SizeBounds (double dMinValue,
/*N*/                  double dMaxValue,
/*N*/                  BOOL   bIsMax)
/*N*/ {
/*N*/   if( (dMinValue == DBL_MIN) ||
/*N*/       (dMaxValue == DBL_MIN) ||
/*N*/       (dMinValue == dMaxValue) ||
/*N*/       (dMinValue == 0.0) )
/*?*/       return 0.0;
/*N*/
/*N*/   return bIsMax? dMaxValue : dMinValue;
/*N*/
/*N*/   // BM: I removed some very strange code here. It
/*N*/   // calculated a kind of log10 but the charts didn't
/*N*/   // really use the value calculated.
/*N*/ }

/*************************************************************************
|*
|* Erhoehe einen Wert mit Log.
|*
\************************************************************************/

/*N*/ void IncValue(double &rValue,
/*N*/             double fInc,
/*N*/             BOOL   bLogarithm)
/*N*/ {
/*N*/   if (bLogarithm)
/*?*/       rValue *= fInc;
/*N*/   else
/*N*/       rValue += fInc;
/*N*/ }

/*************************************************************************
|*
|* Vermindere einen Wert mit Log.
|*
\************************************************************************/

/*N*/ void DecValue(double &rValue,
/*N*/             double fInc,
/*N*/             BOOL   bLogarithm)
/*N*/ {
/*N*/   if (bLogarithm) rValue /= fInc;
/*N*/   else rValue -= fInc;
/*N*/ }

/*************************************************************************
|*
|* Faktor fuer Koordinaten-Multiplikation berechnen
|*
\************************************************************************/

//STRIP001 double CalcFact(double fValue,
//STRIP001              BOOL   bLogarithm,
//STRIP001              double fMinValue,
//STRIP001              double fMaxValue)
//STRIP001 {
//STRIP001  if (fValue == DBL_MIN)
//STRIP001  {
//STRIP001      return DBL_MIN;
//STRIP001  }
//STRIP001  else if (fMinValue == fMaxValue)
//STRIP001  {
//STRIP001      return 0.0;
//STRIP001  }
//STRIP001  else if (bLogarithm)
//STRIP001  {
//STRIP001      double fVal = (fValue > 0.0) ? log10(fValue) : log10(fMinValue);
//STRIP001
//STRIP001      DBG_ASSERT( fMinValue <= 0, "Chart: CalcFact: Argument for logarithm is not positive" );
//STRIP001      DBG_ASSERT( fMaxValue <= 0, "Chart: CalcFact: Argument for logarithm is not positive" );
//STRIP001      return (fVal - log10(fMinValue)) / (log10(fMaxValue) - log10(fMinValue));
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      return (fValue - fMinValue) / (fMaxValue - fMinValue);
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Konvertiert in echte RGB-Farben.
|*
\************************************************************************/

/*N*/ Color RGBColor(ColorData nColorName)
/*N*/ {
/*N*/   Color aColor(nColorName);
/*N*/
/*N*/   return Color(aColor.GetRed(), aColor.GetGreen(), aColor.GetBlue());
/*N*/ }

/*************************************************************************
|*
|* "Stapelt" den angegebenen String.
|*
\************************************************************************/

/*N*/ String StackString( const String& aString )
/*N*/ {
/*N*/   String aStackStr;
/*N*/   xub_StrLen nLen = aString.Len();
/*N*/
/*N*/   if( nLen )
/*N*/   {
/*N*/       // '\n' is interpreted as newline by the outliner
/*N*/       aStackStr.Fill( nLen * 2 - 1, (sal_Unicode)('\n') );
/*N*/
/*N*/       for( xub_StrLen posSrc=0, posDest=0;
/*N*/            posSrc < nLen;
/*N*/            posSrc++, posDest += 2 )
/*N*/           aStackStr.SetChar( posDest, aString.GetChar( posSrc ));
/*N*/   }
/*N*/
/*N*/   return aStackStr;
/*N*/ }

/*************************************************************************
|*
|* "Entstapelt" den angegebenen String.
|*
\************************************************************************/

//STRIP001 String UnstackString( const String& aString )
//STRIP001 {
//STRIP001  // prerequisite: aString was stacked by StackString
//STRIP001  // => every second letter is a '\n' (except the very end)
//STRIP001
//STRIP001  String aUnstackStr;
//STRIP001  xub_StrLen nLen = aString.Len();
//STRIP001
//STRIP001  if( nLen )
//STRIP001  {
//STRIP001      aUnstackStr.Fill( nLen / 2 + 1 );
//STRIP001
//STRIP001      for( xub_StrLen posSrc=0, posDest=0;
//STRIP001           posSrc < nLen;
//STRIP001           posSrc += 2, posDest++ )
//STRIP001          aUnstackStr.SetChar( posDest, aString.GetChar( posSrc ));
//STRIP001  }
//STRIP001
//STRIP001  return aUnstackStr;
//STRIP001 }

/*************************************************************************
|*
|* Aendert die Helligkeit der Fuellfarbe des Ziel-ItemSets;
|* Liefert die alte Fuellfarbe zurueck.
|*
\************************************************************************/

//STRIP001 Color SetBrightness(const SfxItemSet &rSourceAttr,
//STRIP001                  SfxItemSet       &rDestAttr,
//STRIP001                  double           fLightFactor)
//STRIP001 {
//STRIP001  Color aOldColor(((const XFillColorItem&)rSourceAttr.Get(XATTR_FILLCOLOR)).GetValue());
//STRIP001  Color aColor (aOldColor);
//STRIP001
//STRIP001  aColor.SetRed((UINT8)(fLightFactor * aColor.GetRed()));
//STRIP001  aColor.SetGreen((UINT8)(fLightFactor * aColor.GetGreen()));
//STRIP001  aColor.SetBlue((UINT8)(fLightFactor * aColor.GetBlue()));
//STRIP001  rDestAttr.Put(XFillColorItem(String(), aColor));
//STRIP001
//STRIP001  return aOldColor;
//STRIP001 }

/*************************************************************************
|*
|* Position des ungedrehten Rechtecks entsprechend der Ausrichtung anpassen
|*
\************************************************************************/

/*N*/ void AdjustRect(Rectangle          &rRect,
/*N*/               ChartAdjust        eAdjust)
/*N*/ {
/*N*/   Point aPos = rRect.TopLeft();
/*N*/   Size aSize = rRect.GetSize();
/*N*/
/*N*/   switch (eAdjust)
/*N*/   {
/*N*/       case CHADJUST_TOP_LEFT:
/*N*/
/*N*/           break;
/*N*/
/*N*/       case CHADJUST_TOP_CENTER:
/*N*/
/*N*/           aPos.X() -= aSize.Width() / 2;
/*N*/           break;
/*N*/
/*N*/       case CHADJUST_TOP_RIGHT:
/*N*/
/*N*/           aPos.X() -= aSize.Width();
/*N*/           break;
/*N*/
/*N*/       case CHADJUST_CENTER_LEFT:
/*N*/
/*N*/           aPos.Y() -= aSize.Height() / 2;
/*N*/           break;
/*N*/
/*N*/       case CHADJUST_CENTER_CENTER:
/*N*/
/*?*/           aPos.X() -= aSize.Width() / 2;
/*?*/           aPos.Y() -= aSize.Height() / 2;
/*?*/           break;
/*N*/
/*N*/       case CHADJUST_CENTER_RIGHT:
/*N*/
/*N*/           aPos.X() -= aSize.Width();
/*N*/           aPos.Y() -= aSize.Height() / 2;
/*N*/           break;
/*N*/
/*N*/       case CHADJUST_BOTTOM_LEFT:
/*N*/
/*?*/           aPos.Y() -= aSize.Height();
/*?*/           break;
/*N*/
/*N*/       case CHADJUST_BOTTOM_CENTER:
/*N*/
/*N*/           aPos.X() -= aSize.Width() / 2;
/*N*/           aPos.Y() -= aSize.Height();
/*N*/           break;
/*N*/
/*N*/       case CHADJUST_BOTTOM_RIGHT:
/*?*/           aPos.X() -= aSize.Width();
/*?*/           aPos.Y() -= aSize.Height();
/*N*/
/*N*/   }
/*N*/
/*N*/   rRect.SetPos(aPos);
/*N*/ }

/*************************************************************************
|*
|* Position des gedrehten Rechtecks entsprechend der Ausrichtung anpassen
|*
\************************************************************************/

/*N*/ Size AdjustRotatedRect(const Rectangle       &rOldRect,
/*N*/                      ChartAdjust        eAdjust,
/*N*/                      const Rectangle          &rNewRect)
/*N*/ {
/*N*/
/*N*/   Size aMovement;
/*N*/   Point aOld;
/*N*/   Point aNew;
/*N*/   Point aDifference;
/*N*/
/*N*/   switch (eAdjust)
/*N*/   {
/*?*/       case CHADJUST_TOP_LEFT:
/*?*/
/*?*/           aOld = rOldRect.TopLeft();
/*?*/           aNew = rNewRect.TopLeft();
/*?*/           break;
/*?*/
/*?*/       case CHADJUST_TOP_CENTER:
/*?*/
/*?*/           aOld = rOldRect.TopCenter();
/*?*/           aNew = rNewRect.TopCenter();
/*?*/           break;
/*?*/
/*?*/       case CHADJUST_TOP_RIGHT:
/*?*/
/*?*/           aOld = rOldRect.TopRight();
/*?*/           aNew = rNewRect.TopRight();
/*?*/           break;
/*?*/
/*?*/       case CHADJUST_CENTER_LEFT:
/*?*/
/*N*/           aOld = rOldRect.LeftCenter();
/*N*/           aNew = rNewRect.LeftCenter();
/*N*/           break;
/*?*/
/*?*/       case CHADJUST_CENTER_CENTER:
/*?*/
/*?*/           aOld = rOldRect.Center();
/*?*/           aNew = rNewRect.Center();
/*?*/           break;
/*?*/
/*?*/       case CHADJUST_CENTER_RIGHT:
/*?*/
/*?*/           aOld = rOldRect.RightCenter();
/*?*/           aNew = rNewRect.RightCenter();
/*?*/           break;
/*?*/
/*?*/       case CHADJUST_BOTTOM_LEFT:
/*?*/
/*?*/           aOld = rOldRect.BottomLeft();
/*?*/           aNew = rNewRect.BottomLeft();
/*?*/           break;
/*?*/
/*?*/       case CHADJUST_BOTTOM_CENTER:
/*?*/
/*?*/           aOld = rOldRect.BottomCenter();
/*?*/           aNew = rNewRect.BottomCenter();
/*?*/           break;
/*?*/
/*?*/       case CHADJUST_BOTTOM_RIGHT:
/*?*/
/*?*/           aOld = rOldRect.BottomRight();
/*?*/           aNew = rNewRect.BottomRight();
/*?*/           break;
/*N*/   }
/*N*/
/*N*/   aDifference = ( aOld - aNew);
/*N*/   aMovement =  Size(aDifference.X(),aDifference.Y());
/*N*/
/*N*/   return aMovement;
/*N*/ }
//Umrechnung Textgröße in Größe des BoundRects rotierter Texte
/*N*/ Size GetRotatedTextSize(const Size& rSize,const long nDegrees)
/*N*/ {
/*N*/   if(nDegrees)
/*N*/   {
/*?*/       double fDeg,fSin,fCos;
/*?*/       fDeg=CDEG2RAD(nDegrees);
/*?*/       fSin=fabs(sin(fDeg));
/*?*/       fCos=fabs(cos(fDeg));
/*?*/       Size aRetSize(
/*?*/       (long)( (double)rSize.Width()*fCos + (double)rSize.Height()*fSin ),
/*?*/       (long)( (double)rSize.Width()*fSin + (double)rSize.Height()*fCos )
/*?*/           );
/*?*/       return aRetSize;
/*N*/   }
/*N*/   Size aRetSize(rSize);
/*N*/   return aRetSize;
/*N*/ }
/*************************************************************************
|*
|* die Rotation des Textes in Grad zurueckgeben, falls kein DEGREE-item
|* vorhanden, (z.B. 4.0-Chart) so wird das Item ergaenzt
|*
\************************************************************************/
/*N*/ long GetTextRotation(SfxItemSet &rAttr) //Wrapper, falls eOrient noch nicht ermittelt
/*N*/ {
/*N*/   SvxChartTextOrient eOrient
/*N*/       = ((const SvxChartTextOrientItem&)rAttr.Get(SCHATTR_TEXT_ORIENT)).GetValue();
/*N*/   return GetTextRotation(rAttr,eOrient);
/*N*/ }

/*N*/ long GetTextRotation(SfxItemSet &rAttr,SvxChartTextOrient eOrient)
/*N*/ {
/*N*/
/*N*/   const SfxPoolItem* pPoolItem = NULL;
/*N*/   long nDegrees = 0;
/*N*/
/*N*/     // the attribute is set: use it
/*N*/   if( rAttr.GetItemState( SCHATTR_TEXT_DEGREES, TRUE, &pPoolItem ) == SFX_ITEM_SET )
/*N*/   {
/*?*/         nDegrees = ((const SfxInt32Item*)pPoolItem)->GetValue();
/*?*/         return nDegrees;
/*N*/   }
/*N*/
/*N*/     // otherwise use orientation to set default rotation
/*N*/   switch( eOrient )
/*N*/   {
/*N*/       case CHTXTORIENT_BOTTOMTOP:
/*N*/             nDegrees = 9000;    // 90 deg
/*N*/           break;
/*N*/
/*N*/       case CHTXTORIENT_TOPBOTTOM:
/*?*/             nDegrees = 27000;   // 270 deg
/*?*/           break;
/*N*/
/*N*/       case CHTXTORIENT_STANDARD:
/*N*/       case CHTXTORIENT_STACKED:
/*N*/           break;
/*N*/   }
/*N*/
/*N*/   return nDegrees;
/*N*/ }


/*************************************************************************
|*
|* Ausrichtung entsprechend der Orientierung anpassen
|*
\************************************************************************/

/*N*/ void SetAdjust(ChartAdjust        &rAdjust,
/*N*/              SvxChartTextOrient eOrient)
/*N*/ {
/*N*/   switch (eOrient)
/*N*/   {
/*N*/       case CHTXTORIENT_BOTTOMTOP:
/*N*/           switch (rAdjust)
/*N*/           {
/*N*/               case CHADJUST_TOP_LEFT:
/*N*/                   rAdjust = CHADJUST_TOP_RIGHT;
/*N*/                   break;
/*N*/
/*N*/               case CHADJUST_TOP_CENTER:
/*N*/                   rAdjust = CHADJUST_CENTER_RIGHT;
/*N*/                   break;
/*N*/
/*N*/               case CHADJUST_TOP_RIGHT:
/*N*/                   rAdjust = CHADJUST_BOTTOM_RIGHT;
/*N*/
/*N*/                   break;
/*N*/
/*N*/               case CHADJUST_CENTER_LEFT:
/*N*/                   rAdjust = CHADJUST_TOP_CENTER;
/*N*/                   break;
/*N*/
/*N*/               case CHADJUST_CENTER_RIGHT:
/*N*/                   rAdjust = CHADJUST_BOTTOM_CENTER;
/*N*/                   break;
/*N*/
/*N*/               case CHADJUST_BOTTOM_LEFT:
/*N*/                   rAdjust = CHADJUST_TOP_LEFT;
/*N*/                   break;
/*N*/
/*N*/               case CHADJUST_BOTTOM_CENTER:
/*N*/                   rAdjust = CHADJUST_CENTER_LEFT;
/*N*/                   break;
/*N*/
/*N*/               case CHADJUST_BOTTOM_RIGHT:
/*N*/                   rAdjust = CHADJUST_BOTTOM_LEFT;
/*N*/                   break;
/*N*/           }
/*N*/           break;
/*N*/
/*N*/       case CHTXTORIENT_TOPBOTTOM:
/*N*/           switch (rAdjust)
/*N*/           {
/*N*/               case CHADJUST_TOP_LEFT:
/*N*/                   rAdjust = CHADJUST_BOTTOM_LEFT;
/*N*/                   break;
/*N*/
/*N*/               case CHADJUST_TOP_CENTER:
/*N*/                   rAdjust = CHADJUST_CENTER_LEFT;
/*N*/                   break;
/*N*/
/*N*/               case CHADJUST_TOP_RIGHT:
/*N*/                   rAdjust = CHADJUST_TOP_LEFT;
/*N*/                   break;
/*N*/
/*N*/               case CHADJUST_CENTER_LEFT:
/*N*/                   rAdjust = CHADJUST_BOTTOM_CENTER;
/*N*/                   break;
/*N*/
/*N*/               case CHADJUST_CENTER_RIGHT:
/*N*/                   rAdjust = CHADJUST_TOP_CENTER;
/*N*/                   break;
/*N*/
/*N*/               case CHADJUST_BOTTOM_LEFT:
/*N*/                   rAdjust = CHADJUST_BOTTOM_RIGHT;
/*N*/                   break;
/*N*/
/*N*/               case CHADJUST_BOTTOM_CENTER:
/*N*/                   rAdjust = CHADJUST_CENTER_RIGHT;
/*N*/                   break;
/*N*/
/*N*/               case CHADJUST_BOTTOM_RIGHT:
/*N*/                   rAdjust = CHADJUST_TOP_RIGHT;
/*N*/                   break;
/*N*/           }
/*N*/           break;
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Textobjekt positionieren
|*
\************************************************************************/
/*N*/ void SetTextPos(SdrTextObj  &rTextObj,
/*N*/               const Point &rPos,SfxItemSet* pAttr)
/*N*/ {
/*N*/   SchObjectAdjust    *pObjAdjust = GetObjectAdjust(rTextObj);
/*N*/   ChartAdjust         eAdjust    = pObjAdjust->GetAdjust();
/*N*/   double              fVal;
/*N*/   SvxChartTextOrient  eOrient    = pObjAdjust->GetOrient();
/*N*/
/*N*/   switch (eOrient)
/*N*/   {
/*N*/       case CHTXTORIENT_BOTTOMTOP:
/*N*/       case CHTXTORIENT_TOPBOTTOM:
/*N*/       {
/*N*/           long nAng = 36000 - rTextObj.GetRotateAngle();
/*N*/           fVal = nAng * nPi180;
/*N*/           rTextObj.NbcRotate(rPos, nAng, sin(fVal), cos(fVal));
/*N*/           break;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   Rectangle aRect = rTextObj.GetLogicRect();
/*N*/   aRect.SetPos(rPos);
/*N*/   AdjustRect(aRect, eAdjust);
/*N*/   rTextObj.NbcSetLogicRect(aRect);
/*N*/
/*N*/   switch (eOrient)
/*N*/   {
/*N*/       case CHTXTORIENT_BOTTOMTOP:
/*N*/       case CHTXTORIENT_TOPBOTTOM:
/*N*/       {
/*N*/           long nDegrees = GetTextRotation(*pAttr,eOrient);
/*N*/           Rectangle aOldBoundRect=rTextObj.GetBoundRect();
/*N*/           fVal = nDegrees * nPi180;
/*N*/           rTextObj.NbcRotate(rPos, nDegrees, sin(fVal), cos(fVal));
/*N*/           Rectangle aNewBoundRect=rTextObj.GetBoundRect();
/*N*/           rTextObj.NbcMove( AdjustRotatedRect(aOldBoundRect, eAdjust, aNewBoundRect));
/*N*/           break;
/*N*/       }
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Textobjekt-Groesse entsprechend der Ausrichtung anpassen
|*
\************************************************************************/

/*N*/ void AdjustTextSize(SdrTextObj &rTextObj,
/*N*/                   const Size &rTextSize)
/*N*/ {
/*N*/   Rectangle aRect = rTextObj.GetLogicRect();
/*N*/
/*N*/   if (aRect.GetSize() != rTextSize)
/*N*/   {
/*N*/       SchObjectAdjust    *pObjAdjust = GetObjectAdjust(rTextObj);
/*N*/       ChartAdjust        eAdjust     = pObjAdjust->GetAdjust();
/*N*/       SvxChartTextOrient eOrient     = pObjAdjust->GetOrient();
/*N*/
/*N*/       SetAdjust(eAdjust, eOrient);
/*N*/
/*N*/       Point aOldPos = aRect.TopLeft();
/*N*/
/*N*/       switch (eAdjust)
/*N*/       {
/*N*/           case CHADJUST_TOP_CENTER:
/*N*/               aRect.Left() = aRect.Left() + aRect.GetWidth() / 2 - rTextSize.Width() / 2;
/*N*/               aRect.Right() = aRect.Left() + rTextSize.Width();
/*N*/               aRect.Bottom() = aRect.Top() + rTextSize.Height();
/*N*/               break;
/*N*/
/*N*/           case CHADJUST_TOP_RIGHT:
/*N*/               aRect.Left() = aRect.Right() - rTextSize.Width();
/*N*/               aRect.Bottom() = aRect.Top() + rTextSize.Height();
/*N*/               break;
/*N*/
/*N*/           case CHADJUST_CENTER_LEFT:
/*N*/               aRect.Right() = aRect.Left() + rTextSize.Width();
/*N*/               aRect.Top() = aRect.Top() + aRect.GetHeight() / 2 - rTextSize.Height() / 2;
/*N*/               aRect.Bottom() = aRect.Top() + rTextSize.Height();
/*N*/               break;
/*N*/
/*N*/           case CHADJUST_CENTER_CENTER:
/*N*/               aRect.Left() = aRect.Left() + aRect.GetWidth() / 2 - rTextSize.Width() / 2;
/*N*/               aRect.Right() = aRect.Left() + rTextSize.Width();
/*N*/               aRect.Top() = aRect.Top() + aRect.GetHeight() / 2 - rTextSize.Height() / 2;
/*N*/               aRect.Bottom() = aRect.Top() + rTextSize.Height();
/*N*/               break;
/*N*/
/*N*/           case CHADJUST_CENTER_RIGHT:
/*N*/               aRect.Left() = aRect.Right() - rTextSize.Width();
/*N*/               aRect.Top() = aRect.Top() + aRect.GetHeight() / 2 - rTextSize.Height() / 2;
/*N*/               aRect.Bottom() = aRect.Top() + rTextSize.Height();
/*N*/               break;
/*N*/
/*N*/           case CHADJUST_BOTTOM_LEFT:
/*N*/               aRect.Right() = aRect.Left() + rTextSize.Width();
/*N*/               aRect.Top() = aRect.Bottom() - rTextSize.Height();
/*N*/               break;
/*N*/
/*N*/           case CHADJUST_BOTTOM_CENTER:
/*N*/               aRect.Left() = aRect.Left() + aRect.GetWidth() / 2 - rTextSize.Width() / 2;
/*N*/               aRect.Right() = aRect.Left() + rTextSize.Width();
/*N*/               aRect.Top() = aRect.Bottom() - rTextSize.Height();
/*N*/               break;
/*N*/
/*N*/           case CHADJUST_BOTTOM_RIGHT:
/*N*/               aRect.Left() = aRect.Right() - rTextSize.Width();
/*N*/               aRect.Top() = aRect.Bottom() - rTextSize.Height();
/*N*/               break;
/*N*/
/*N*/           default:
/*N*/               aRect.Right() = aRect.Left() + rTextSize.Width();
/*N*/               aRect.Bottom() = aRect.Top() + rTextSize.Height();
/*N*/               break;
/*N*/       }
/*N*/
/*N*/       Point aNewPos = aRect.TopLeft();
/*N*/
/*N*/       if (aNewPos != aOldPos)
/*N*/       {
/*N*/           long nArc = rTextObj.GetRotateAngle();
/*N*/
/*N*/           if (nArc)
/*N*/           {
/*N*/               double fVal = nArc * nPi180;
/*N*/               RotatePoint(aNewPos, aOldPos, sin(fVal), cos(fVal));
/*N*/               aRect.SetPos(aNewPos);
/*N*/           }
/*N*/       }
/*N*/
/*N*/       rTextObj.SetLogicRect(aRect);
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Ausgabegroesse ermitteln
|*
\************************************************************************/

/*N*/ Size GetOutputSize(SdrTextObj& rTextObj)
/*N*/ {
/*N*/   return (rTextObj.GetBoundRect().GetSize());
/*N*/ }

/*************************************************************************
|*
|* Haenge die Beschriftungen an die Segmente
|*
\************************************************************************/

/*N*/ void SegmentDescr (DataDescription &rDescr,
/*N*/                  const Rectangle &rRect,
/*N*/                  long            nStartAng,
/*N*/                  long            nEndAng,
/*N*/                  long            nHeight,
/*N*/                  double          a,
/*N*/                  double          b)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  long nAngleDiff;
//STRIP001  long nAngleHook;
//STRIP001
//STRIP001  // bestimme die Winkelhalbierenden des Segments
//STRIP001  if (nStartAng > nEndAng)
//STRIP001  {
//STRIP001      nAngleDiff = (nEndAng + 36000 - nStartAng) / 2;
//STRIP001      nAngleHook = (nStartAng + nAngleDiff) % 36000;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      nAngleDiff = (nEndAng - nStartAng) / 2;
//STRIP001      nAngleHook = nStartAng + nAngleDiff;
//STRIP001  }
//STRIP001
//STRIP001  // und dementsprechend die Textausrichtung
//STRIP001  if (nAngleHook < 2250) rDescr.eAdjust = CHADJUST_CENTER_LEFT;
//STRIP001  else if (nAngleHook < 6750) rDescr.eAdjust = CHADJUST_BOTTOM_LEFT;
//STRIP001       else if (nAngleHook < 11250) rDescr.eAdjust = CHADJUST_BOTTOM_CENTER;
//STRIP001            else if (nAngleHook < 15750) rDescr.eAdjust = CHADJUST_BOTTOM_RIGHT;
//STRIP001                 else if (nAngleHook < 20250) rDescr.eAdjust = CHADJUST_CENTER_RIGHT;
//STRIP001                      else if (nAngleHook < 24750) rDescr.eAdjust = CHADJUST_TOP_RIGHT;
//STRIP001                           else if (nAngleHook < 29250) rDescr.eAdjust = CHADJUST_TOP_CENTER;
//STRIP001                                else if (nAngleHook < 33750) rDescr.eAdjust = CHADJUST_TOP_LEFT;
//STRIP001                                     else rDescr.eAdjust = CHADJUST_CENTER_LEFT;
//STRIP001
//STRIP001  // die Seiten werden etwas verlaengert, um einen Offset Text<-->Segment zu erhalten
//STRIP001  double fAng = F_PI * (double) nAngleHook / 18000;
//STRIP001  rDescr.aTextPos2D       = rRect.Center();
//STRIP001  rDescr.aTextPos2D.X() += long((a * 10 / 9) * cos (fAng));
//STRIP001  rDescr.aTextPos2D.Y() -= long((b * 10 / 9) * sin (fAng));
//STRIP001
//STRIP001  // Winkel im Bereich der Bodenplatte -> Texte etwas tiefer setzen
//STRIP001  if ((nAngleHook > 18000) && (nAngleHook < 36000)) rDescr.aTextPos2D.Y() += nHeight;
//STRIP001
//STRIP001  // TVM: vorlaeufiger Bug-Fix, pText kann bei 3DPieChart Null sein
//STRIP001  DBG_ASSERT(rDescr.pLabelObj,"Beschriftungstext ist nicht vorhanden");
//STRIP001  if(rDescr.pLabelObj)
//STRIP001  {
//STRIP001      Rectangle aObjRect = rDescr.pLabelObj->GetLogicRect();
//STRIP001
//STRIP001      aObjRect.SetPos(rDescr.aTextPos2D);
//STRIP001      AdjustRect(aObjRect, rDescr.eAdjust);
//STRIP001      rDescr.pLabelObj->SetLogicRect(aObjRect);
//STRIP001  }
/*N*/ }


/** Draw a donut segment's description centered into that segment.
    Please see the header for a detailed documentation.
*/
/*N*/ void SegmentDescr (DataDescription &rDescr,
/*N*/                  const Rectangle &rRect,
/*N*/                  long            nStartAng,
/*N*/                  long            nEndAng,
/*N*/                  double          fRadius)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  //  Calculate the radial line on which the desctiption will be positioned.
//STRIP001  long nAngleHook;
//STRIP001  if (nStartAng > nEndAng)
//STRIP001      nAngleHook = (nStartAng + (nEndAng + 36000 - nStartAng) / 2) % 36000;
//STRIP001  else
//STRIP001      nAngleHook = nStartAng + (nEndAng - nStartAng) / 2;
//STRIP001
//STRIP001  //  Place description at the given radius.
//STRIP001  double fAng = F_PI * (double) nAngleHook / 18000;
//STRIP001  rDescr.aTextPos2D = rRect.Center();
//STRIP001  rDescr.aTextPos2D.X() += long(fRadius * cos (fAng));
//STRIP001  rDescr.aTextPos2D.Y() -= long(fRadius * sin (fAng));
//STRIP001
//STRIP001  //  Description will be centerd around it's reference point.
//STRIP001  rDescr.eAdjust = CHADJUST_CENTER_CENTER;
//STRIP001
//STRIP001  //  Create description.
//STRIP001  DBG_ASSERT(rDescr.pLabelObj,"Beschriftungstext ist nicht vorhanden");
//STRIP001  if(rDescr.pLabelObj)
//STRIP001  {
//STRIP001      Rectangle aObjRect = rDescr.pLabelObj->GetLogicRect();
//STRIP001
//STRIP001      aObjRect.SetPos(rDescr.aTextPos2D);
//STRIP001      AdjustRect(aObjRect, rDescr.eAdjust);
//STRIP001      rDescr.pLabelObj->SetLogicRect(aObjRect);
//STRIP001  }
/*N*/ }
/*************************************************************************
|*
|* zeichne Fehlerbalken
|*
\************************************************************************/

//STRIP001 void ShowErrorLineY( BOOL              bIsVertical,
//STRIP001                   double            fErrorUp,
//STRIP001                   double            fErrorDown,
//STRIP001                   SfxItemSet        &rAttr,
//STRIP001                   const  Point&     rPos,
//STRIP001                   SvxChartIndicate  eMyIndicate,
//STRIP001                   SdrObjList        *pList,
//STRIP001                      ChartModel *      pModel )
//STRIP001 {
//STRIP001  long              nPosX,nPosY;
//STRIP001
//STRIP001  XPolygon   aErrorPolygon (2);
//STRIP001  XPolygon   aTopPolygon (2);
//STRIP001  XPolygon   aBottomPolygon (2);
//STRIP001 //   SfxItemSet aSolidAttr (rAttr);
//STRIP001
//STRIP001 //   aSolidAttr.ClearItem (XATTR_LINESTYLE);
//STRIP001 //   aSolidAttr.Put(XLineStyleItem (XLINE_SOLID));
//STRIP001
//STRIP001  if(bIsVertical) //Bei Gelegenheit sollte hier mal aufgeräumt werden....
//STRIP001  {
//STRIP001      nPosX = rPos.Y();
//STRIP001      nPosY = rPos.X();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      nPosX = rPos.X();
//STRIP001      nPosY = rPos.Y();
//STRIP001  }
//STRIP001
//STRIP001  switch (eMyIndicate)
//STRIP001  {
//STRIP001      case CHINDICATE_BOTH :
//STRIP001             {
//STRIP001                 if (bIsVertical)
//STRIP001                 {
//STRIP001                     aErrorPolygon [0].Y()  =
//STRIP001                         aErrorPolygon [1].Y()  = nPosX;
//STRIP001                     aErrorPolygon [0].X()  =
//STRIP001                         aTopPolygon [0].X()    =
//STRIP001                         aTopPolygon [1].X()    = (long) fErrorUp;
//STRIP001                     aErrorPolygon [1].X()  =
//STRIP001                         aBottomPolygon [0].X() =
//STRIP001                         aBottomPolygon [1].X() = (long) fErrorDown;
//STRIP001                     aTopPolygon [0].Y()    =
//STRIP001                         aBottomPolygon [0].Y() = nPosX - 100;
//STRIP001                     aTopPolygon [1].Y()    =
//STRIP001                         aBottomPolygon [1].Y() = nPosX + 100;
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     aErrorPolygon [0].X()  =
//STRIP001                         aErrorPolygon [1].X()  = nPosX;
//STRIP001                     aErrorPolygon [0].Y()  =
//STRIP001                         aTopPolygon [0].Y()    =
//STRIP001                         aTopPolygon [1].Y()    = (long) fErrorUp;
//STRIP001                     aErrorPolygon [1].Y()  =
//STRIP001                         aBottomPolygon [0].Y() =
//STRIP001                         aBottomPolygon [1].Y() = (long) fErrorDown;
//STRIP001                     aTopPolygon [0].X()    =
//STRIP001                         aBottomPolygon [0].X() = nPosX - 100;
//STRIP001                     aTopPolygon [1].X()    =
//STRIP001                         aBottomPolygon [1].X() = nPosX + 100;
//STRIP001                 }
//STRIP001
//STRIP001                 ::std::vector< XPolygon > aPolygons;
//STRIP001                 aPolygons.push_back( aErrorPolygon );
//STRIP001                 aPolygons.push_back( aTopPolygon );
//STRIP001                 aPolygons.push_back( aBottomPolygon );
//STRIP001                 pList->NbcInsertObject( CreateErrorGroup( pModel, aPolygons, rAttr ) );
//STRIP001             }
//STRIP001          break;
//STRIP001
//STRIP001      case CHINDICATE_UP :
//STRIP001             {
//STRIP001                 if (bIsVertical)
//STRIP001                 {
//STRIP001                     aErrorPolygon [0].Y()  =
//STRIP001                         aErrorPolygon [1].Y()  = nPosX;
//STRIP001                     aErrorPolygon [0].X()  =
//STRIP001                         aTopPolygon [0].X()    =
//STRIP001                         aTopPolygon [1].X()    = (long) fErrorUp;
//STRIP001                     aErrorPolygon [1].X()  = nPosY;
//STRIP001                     aTopPolygon [0].Y()    = nPosX - 100;
//STRIP001                     aTopPolygon [1].Y()    = nPosX + 100;
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     aErrorPolygon [0].X()  =
//STRIP001                         aErrorPolygon [1].X()  = nPosX;
//STRIP001                     aErrorPolygon [0].Y()  =
//STRIP001                         aTopPolygon [0].Y()    =
//STRIP001                         aTopPolygon [1].Y()    = (long) fErrorUp;
//STRIP001                     aErrorPolygon [1].Y()  = nPosY;
//STRIP001                     aTopPolygon [0].X()    = nPosX - 100;
//STRIP001                     aTopPolygon [1].X()    = nPosX + 100;
//STRIP001                 }
//STRIP001
//STRIP001                 ::std::vector< XPolygon > aPolygons;
//STRIP001                 aPolygons.push_back( aErrorPolygon );
//STRIP001                 aPolygons.push_back( aTopPolygon );
//STRIP001                 pList->NbcInsertObject( CreateErrorGroup( pModel, aPolygons, rAttr ) );
//STRIP001             }
//STRIP001          break;
//STRIP001
//STRIP001      case CHINDICATE_DOWN :
//STRIP001             {
//STRIP001                 if (bIsVertical)
//STRIP001                 {
//STRIP001                     aErrorPolygon [0].Y()  =
//STRIP001                         aErrorPolygon [1].Y()  = nPosX;
//STRIP001                     aErrorPolygon [0].X()  =
//STRIP001                         aBottomPolygon [0].X() =
//STRIP001                         aBottomPolygon [1].X() = (long) fErrorDown;
//STRIP001                     aErrorPolygon [1].X()  = nPosY;
//STRIP001                     aBottomPolygon [0].Y() = nPosX - 100;
//STRIP001                     aBottomPolygon [1].Y() = nPosX + 100;
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     aErrorPolygon [0].X()  =
//STRIP001                         aErrorPolygon [1].X()  = nPosX;
//STRIP001                     aErrorPolygon [0].Y()  =
//STRIP001                         aBottomPolygon [0].Y() =
//STRIP001                         aBottomPolygon [1].Y() = (long) fErrorDown;
//STRIP001                     aErrorPolygon [1].Y()  = nPosY;
//STRIP001                     aBottomPolygon [0].X() = nPosX - 100;
//STRIP001                     aBottomPolygon [1].X() = nPosX + 100;
//STRIP001                 }
//STRIP001
//STRIP001                 ::std::vector< XPolygon > aPolygons;
//STRIP001                 aPolygons.push_back( aErrorPolygon );
//STRIP001                 aPolygons.push_back( aBottomPolygon );
//STRIP001                 pList->NbcInsertObject( CreateErrorGroup( pModel, aPolygons, rAttr ) );
//STRIP001             }
//STRIP001          break;
//STRIP001
//STRIP001      case CHINDICATE_NONE :
//STRIP001      default :
//STRIP001          ;
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* bestimme lineare regression
|*
\************************************************************************/

//STRIP001 void InsertPolygon (SdrObjList *pList,
//STRIP001                  XPolygon   &rPolygon,
//STRIP001                  SfxItemSet &rAttr)
//STRIP001 {
//STRIP001  SdrObject *pObj = new SdrPathObj (OBJ_PLIN, rPolygon);
//STRIP001
//STRIP001  if (pObj)
//STRIP001  {
//STRIP001      pObj->InsertUserData (new SchObjectId (CHOBJID_DIAGRAM_ERROR));
//STRIP001 //-/     pObj->NbcSetAttributes (rAttr, FALSE);
//STRIP001      pObj->SetItemSet(rAttr);
//STRIP001      pList->NbcInsertObject (pObj);
//STRIP001  }
//STRIP001 }

// --------------------

//STRIP001 namespace
//STRIP001 {
//STRIP001
//STRIP001 class lcl_InsertPolygonInList : public ::std::unary_function< void, XPolygon >
//STRIP001 {
//STRIP001 public:
//STRIP001     lcl_InsertPolygonInList( SdrObjList * pObjListForInsertion,
//STRIP001                              const SfxItemSet & rItems ) :
//STRIP001             m_pObjList( pObjListForInsertion ),
//STRIP001             m_rItems( rItems )
//STRIP001     {}
//STRIP001
//STRIP001     inline void operator() ( const XPolygon & rPoly )
//STRIP001     {
//STRIP001         SdrObject * pObj = new SdrPathObj( OBJ_PLIN, rPoly );
//STRIP001         pObj->SetItemSet( m_rItems );
//STRIP001         m_pObjList->NbcInsertObject( pObj );
//STRIP001     }
//STRIP001
//STRIP001 private:
//STRIP001     SdrObjList *        m_pObjList;
//STRIP001     const SfxItemSet &  m_rItems;
//STRIP001 };
//STRIP001
//STRIP001 }
//STRIP001
//STRIP001 // --------------------
//STRIP001
//STRIP001 SdrObject * CreateErrorGroup(
//STRIP001     ChartModel * pModel,
//STRIP001     const ::std::vector< XPolygon > & rPolygons,
//STRIP001     const SfxItemSet & rItems )
//STRIP001 {
//STRIP001     SdrObject * pResult = new SchObjGroup( pModel );
//STRIP001
//STRIP001     pResult->InsertUserData( new SchObjectId( CHOBJID_DIAGRAM_ERROR ));
//STRIP001     SdrObjList * pObjList = pResult->GetSubList();
//STRIP001     ::std::for_each( rPolygons.begin(), rPolygons.end(),
//STRIP001                      lcl_InsertPolygonInList( pObjList, rItems ) );
//STRIP001
//STRIP001     return pResult;
//STRIP001 }

/*************************************************************************
/*************************************************************************
|*
|* Erstelle Polygone fuer die Scheiben in den Pie-Charts
|*
\************************************************************************/

//STRIP001 SdrObject *Create2DPolyObj (SfxItemSet &rAttr,
//STRIP001                          Point      aLeftBottom,
//STRIP001                          Point      aLeftTop,
//STRIP001                          Point      aRightTop,
//STRIP001                          Point      aRightBottom)
//STRIP001 {
//STRIP001  XPolygon   aSide (5);
//STRIP001
//STRIP001  aSide [0] =
//STRIP001  aSide [4] = aLeftBottom;
//STRIP001  aSide [1] = aLeftTop;
//STRIP001  aSide [2] = aRightTop;
//STRIP001  aSide [3] = aRightBottom;
//STRIP001
//STRIP001  rAttr.Put(XLineStyleItem(XLINE_NONE));
//STRIP001
//STRIP001  return SetObjectAttr (new SdrPathObj(OBJ_POLY, XPolyPolygon(aSide)), 0, TRUE, TRUE, &rAttr);
//STRIP001 }

/*************************************************************************
|*
|* Erstelle Sublist fuer Elemente eines 3D-PieCharts
|*
\************************************************************************/

//STRIP001 SdrObjList *CreateGroupList (SdrObjList *pList,
//STRIP001                           long       nID)
//STRIP001 {
//STRIP001  SchObjGroup *pGroup     = CreateSimpleGroup (USHORT(nID), TRUE, TRUE);
//STRIP001  SdrObjList  *pGroupList = pGroup->GetSubList();
//STRIP001
//STRIP001  pGroup->InsertUserData(new SchDataRow(0));
//STRIP001  pList->NbcInsertObject (pGroup);
//STRIP001
//STRIP001  return pGroupList;
//STRIP001 }

/*************************************************************************
|*
|* Erstelle eine Gruppe und die Sublist fuer ein Chart
|*
\************************************************************************/

/*N*/ void CreateChartGroup( SchObjGroup* &pGroup,
/*N*/                      SdrObjList*  &pList )
/*N*/ {
/*N*/   pGroup = new SchObjGroup;
/*N*/   pList  = pGroup->GetSubList();
/*N*/   pGroup->InsertUserData( new SchObjectId( CHOBJID_DIAGRAM ));
/*N*/ }



/*************************************************************************
|*
|* Beseitige alle Statistikattrs
|*
\************************************************************************/

//STRIP001 void CopySetsFrom40To31(const SfxItemSet &rSourceSet,SfxItemSet &rDestSet)
//STRIP001 {
//STRIP001  SfxWhichIter aIter (rSourceSet);
//STRIP001  USHORT       nWhich = aIter.FirstWhich();
//STRIP001
//STRIP001  while (nWhich)
//STRIP001  {
//STRIP001      if (((nWhich < SCHATTR_STAT_START) || (nWhich > SCHATTR_STAT_END)) &&
//STRIP001          ((nWhich < EE_ITEMS_START) || (nWhich > EE_ITEMS_END)))
//STRIP001      {
//STRIP001          rDestSet.InvalidateItem (nWhich);
//STRIP001          rDestSet.Put (rSourceSet.Get (nWhich));
//STRIP001      }
//STRIP001
//STRIP001      nWhich = aIter.NextWhich();
//STRIP001  }
//STRIP001 }

/*N*/ const long nOffX = SCHATTR_AXIS_AUTO_MIN - SCHATTR_X_AXIS_AUTO_MIN;
/*N*/ const long nOffY = SCHATTR_AXIS_AUTO_MIN - SCHATTR_Y_AXIS_AUTO_MIN;
/*N*/ const long nOffZ = SCHATTR_AXIS_AUTO_MIN - SCHATTR_Z_AXIS_AUTO_MIN;

//neue in alte Achsenattr konvertieren
/*N*/ void AxisAttrNew2Old(SfxItemSet &rDestSet,long nId,BOOL bClear)
/*N*/ {
/*N*/   USHORT nOff;
/*N*/   double f;
/*N*/   BOOL b;
/*N*/   SfxItemSet aSet(rDestSet); //Kopie
/*N*/
/*N*/   switch(nId)
/*N*/   {
/*N*/       case CHOBJID_DIAGRAM_X_AXIS:
/*N*/           nOff=nOffX;
/*N*/           rDestSet.Put(SvxChartTextOrderItem(CHTXTORDER_SIDEBYSIDE));
/*N*/           rDestSet.Put(SfxBoolItem(SCHATTR_X_AXIS_AUTO_MIN, TRUE));
/*N*/           rDestSet.Put(SvxDoubleItem(0.0, SCHATTR_X_AXIS_MIN));
/*N*/           rDestSet.Put(SfxBoolItem(SCHATTR_X_AXIS_AUTO_MAX, TRUE));
/*N*/           rDestSet.Put(SvxDoubleItem(0.0, SCHATTR_X_AXIS_MAX));
/*N*/           rDestSet.Put(SfxBoolItem(SCHATTR_X_AXIS_AUTO_STEP_MAIN, TRUE));
/*N*/           rDestSet.Put(SvxDoubleItem(0.0, SCHATTR_X_AXIS_STEP_MAIN));
/*N*/           rDestSet.Put(SfxBoolItem(SCHATTR_X_AXIS_AUTO_STEP_HELP, TRUE));
/*N*/           rDestSet.Put(SvxDoubleItem(0.0, SCHATTR_X_AXIS_STEP_HELP));
/*N*/           rDestSet.Put(SfxBoolItem(SCHATTR_X_AXIS_LOGARITHM, FALSE));
/*N*/           rDestSet.Put(SfxBoolItem(SCHATTR_X_AXIS_AUTO_ORIGIN, TRUE));
/*N*/           rDestSet.Put(SvxDoubleItem(0.0, SCHATTR_X_AXIS_ORIGIN));
/*N*/           break;
/*N*/       case CHOBJID_DIAGRAM_Y_AXIS:
/*N*/           nOff=nOffY;
/*N*/           rDestSet.Put(SvxChartTextOrderItem(CHTXTORDER_SIDEBYSIDE));
/*N*/           rDestSet.Put(SfxBoolItem(SCHATTR_Y_AXIS_AUTO_MIN, TRUE));
/*N*/           rDestSet.Put(SvxDoubleItem(0.0, SCHATTR_Y_AXIS_MIN));
/*N*/           rDestSet.Put(SfxBoolItem(SCHATTR_Y_AXIS_AUTO_MAX, TRUE));
/*N*/           rDestSet.Put(SvxDoubleItem(0.0, SCHATTR_Y_AXIS_MAX));
/*N*/           rDestSet.Put(SfxBoolItem(SCHATTR_Y_AXIS_AUTO_STEP_MAIN, TRUE));
/*N*/           rDestSet.Put(SvxDoubleItem(0.0, SCHATTR_Y_AXIS_STEP_MAIN));
/*N*/           rDestSet.Put(SfxBoolItem(SCHATTR_Y_AXIS_AUTO_STEP_HELP, TRUE));
/*N*/           rDestSet.Put(SvxDoubleItem(0.0, SCHATTR_Y_AXIS_STEP_HELP));
/*N*/           rDestSet.Put(SfxBoolItem(SCHATTR_Y_AXIS_LOGARITHM, FALSE));
/*N*/           rDestSet.Put(SfxBoolItem(SCHATTR_Y_AXIS_AUTO_ORIGIN, FALSE));
/*N*/           rDestSet.Put(SvxDoubleItem(0.0, SCHATTR_Y_AXIS_ORIGIN));
/*N*/           break;
/*N*/       case CHOBJID_DIAGRAM_Z_AXIS:
/*N*/           nOff=nOffZ;
/*N*/           rDestSet.Put(SvxChartTextOrderItem(CHTXTORDER_SIDEBYSIDE));
/*N*/           rDestSet.Put(SfxBoolItem(SCHATTR_Z_AXIS_AUTO_MIN, TRUE));
/*N*/           rDestSet.Put(SvxDoubleItem(0.0, SCHATTR_Z_AXIS_MIN));
/*N*/           rDestSet.Put(SfxBoolItem(SCHATTR_Z_AXIS_AUTO_MAX, TRUE));
/*N*/           rDestSet.Put(SvxDoubleItem(0.0, SCHATTR_Z_AXIS_MAX));
/*N*/           rDestSet.Put(SfxBoolItem(SCHATTR_Z_AXIS_AUTO_STEP_MAIN, TRUE));
/*N*/           rDestSet.Put(SvxDoubleItem(0.0, SCHATTR_Z_AXIS_STEP_MAIN));
/*N*/           rDestSet.Put(SfxBoolItem(SCHATTR_Z_AXIS_AUTO_STEP_HELP, TRUE));
/*N*/           rDestSet.Put(SvxDoubleItem(0.0, SCHATTR_Z_AXIS_STEP_HELP));
/*N*/           rDestSet.Put(SfxBoolItem(SCHATTR_Z_AXIS_LOGARITHM, FALSE));
/*N*/           rDestSet.Put(SfxBoolItem(SCHATTR_Z_AXIS_AUTO_ORIGIN, TRUE));
/*N*/           rDestSet.Put(SvxDoubleItem(0.0, SCHATTR_Z_AXIS_ORIGIN));
/*N*/           break;
/*N*/   }
/*N*/
/*N*/   SfxWhichIter aIter(aSet);
/*N*/   USHORT       nWhich = aIter.FirstWhich();
/*N*/
/*N*/   while(nWhich)
/*N*/   {
/*N*/       switch(nWhich)
/*N*/       {
/*N*/           case SCHATTR_AXIS_AUTO_MIN:
/*N*/           case SCHATTR_AXIS_AUTO_MAX:
/*N*/           case SCHATTR_AXIS_AUTO_STEP_MAIN:
/*N*/           case SCHATTR_AXIS_AUTO_STEP_HELP:
/*N*/           case SCHATTR_AXIS_LOGARITHM:
/*N*/           case SCHATTR_AXIS_AUTO_ORIGIN:
/*N*/
/*N*/               b=((const SfxBoolItem&)rDestSet.Get(nWhich)).GetValue();
/*N*/               rDestSet.Put(SfxBoolItem(nWhich-nOff,b));
/*N*/               if(bClear)
/*N*/                   rDestSet.ClearItem(nWhich);
/*N*/               break;
/*N*/
/*N*/           case SCHATTR_AXIS_MIN:
/*N*/           case SCHATTR_AXIS_MAX:
/*N*/           case SCHATTR_AXIS_STEP_MAIN:
/*N*/           case SCHATTR_AXIS_STEP_HELP:
/*N*/           case SCHATTR_AXIS_ORIGIN:
/*N*/
/*N*/               f=((const SvxDoubleItem&)rDestSet.Get(nWhich)).GetValue();
/*N*/               rDestSet.Put(SvxDoubleItem(f,nWhich-nOff));
/*N*/               if(bClear)
/*N*/                   rDestSet.ClearItem(nWhich);
/*N*/               break;
/*N*/
/*N*/       }
/*N*/       nWhich = aIter.NextWhich();
/*N*/   }
/*N*/ }
//alte in neue Achsenattr konvertieren
/*N*/ void AxisAttrOld2New(SfxItemSet &rDestSet,BOOL bClear,long nId)
/*N*/ {
/*N*/
/*N*/   double f;
/*N*/   BOOL b;
/*N*/   SfxItemSet aSet(rDestSet); //Kopie
/*N*/
/*N*/   SfxWhichIter aIter (aSet);
/*N*/   USHORT nWhich = aIter.FirstWhich ();
/*N*/
/*N*/   while (nWhich)
/*N*/   {
/*N*/       switch(nWhich)
/*N*/       {
/*N*/           case SCHATTR_X_AXIS_AUTO_MIN:
/*N*/           case SCHATTR_X_AXIS_AUTO_MAX:
/*N*/           case SCHATTR_X_AXIS_AUTO_STEP_MAIN:
/*N*/           case SCHATTR_X_AXIS_AUTO_STEP_HELP:
/*N*/           case SCHATTR_X_AXIS_LOGARITHM:
/*N*/           case SCHATTR_X_AXIS_AUTO_ORIGIN:
/*N*/
/*N*/               if(nId==CHOBJID_DIAGRAM_X_AXIS)
/*N*/               {
/*N*/                   b=((const SfxBoolItem&)rDestSet.Get(nWhich)).GetValue();
/*N*/                   rDestSet.Put(SfxBoolItem(nWhich+USHORT(nOffX),b));
/*N*/                   if(bClear)
/*N*/                       rDestSet.ClearItem(nWhich);
/*N*/               }
/*N*/               break;
/*N*/
/*N*/           case SCHATTR_X_AXIS_MIN:
/*N*/           case SCHATTR_X_AXIS_MAX:
/*N*/           case SCHATTR_X_AXIS_STEP_MAIN:
/*N*/           case SCHATTR_X_AXIS_STEP_HELP:
/*N*/           case SCHATTR_X_AXIS_ORIGIN:
/*N*/
/*N*/               if(nId==CHOBJID_DIAGRAM_X_AXIS)
/*N*/               {
/*N*/                   f=((const SvxDoubleItem&)rDestSet.Get(nWhich)).GetValue();
/*N*/                   rDestSet.Put(SvxDoubleItem(f,nWhich+USHORT(nOffX)));
/*N*/                   if(bClear)
/*N*/                       rDestSet.ClearItem(nWhich);
/*N*/               }
/*N*/               break;
/*N*/
/*N*/           case SCHATTR_Y_AXIS_AUTO_MIN:
/*N*/           case SCHATTR_Y_AXIS_AUTO_MAX:
/*N*/           case SCHATTR_Y_AXIS_AUTO_STEP_MAIN:
/*N*/           case SCHATTR_Y_AXIS_AUTO_STEP_HELP:
/*N*/           case SCHATTR_Y_AXIS_LOGARITHM:
/*N*/           case SCHATTR_Y_AXIS_AUTO_ORIGIN:
/*N*/
/*N*/               if(nId==CHOBJID_DIAGRAM_Y_AXIS)
/*N*/               {
/*N*/                   b=((const SfxBoolItem&)rDestSet.Get(nWhich)).GetValue();
/*N*/                   rDestSet.Put(SfxBoolItem(nWhich+USHORT(nOffY),b));
/*N*/                   if(bClear)
/*N*/                       rDestSet.ClearItem(nWhich);
/*N*/               }
/*N*/               break;
/*N*/
/*N*/           case SCHATTR_Y_AXIS_MIN:
/*N*/           case SCHATTR_Y_AXIS_MAX:
/*N*/           case SCHATTR_Y_AXIS_STEP_MAIN:
/*N*/           case SCHATTR_Y_AXIS_STEP_HELP:
/*N*/           case SCHATTR_Y_AXIS_ORIGIN:
/*N*/
/*N*/               if(nId==CHOBJID_DIAGRAM_Y_AXIS)
/*N*/               {
/*N*/                   f=((const SvxDoubleItem&)rDestSet.Get(nWhich)).GetValue();
/*N*/                   rDestSet.Put(SvxDoubleItem(f,nWhich+USHORT(nOffY)));
/*N*/                   if(bClear)
/*N*/                       rDestSet.ClearItem(nWhich);
/*N*/               }
/*N*/               break;
/*N*/
/*N*/           case SCHATTR_Z_AXIS_AUTO_MIN:
/*N*/           case SCHATTR_Z_AXIS_AUTO_MAX:
/*N*/           case SCHATTR_Z_AXIS_AUTO_STEP_MAIN:
/*N*/           case SCHATTR_Z_AXIS_AUTO_STEP_HELP:
/*N*/           case SCHATTR_Z_AXIS_LOGARITHM:
/*N*/           case SCHATTR_Z_AXIS_AUTO_ORIGIN:
/*N*/
/*N*/               if(nId==CHOBJID_DIAGRAM_Z_AXIS)
/*N*/               {
/*N*/                   b=((const SfxBoolItem&)rDestSet.Get(nWhich)).GetValue();
/*N*/                   rDestSet.Put(SfxBoolItem(nWhich+USHORT(nOffZ),b));
/*N*/                   if(bClear)
/*N*/                       rDestSet.ClearItem(nWhich);
/*N*/               }
/*N*/               break;
/*N*/
/*N*/           case SCHATTR_Z_AXIS_MIN:
/*N*/           case SCHATTR_Z_AXIS_MAX:
/*N*/           case SCHATTR_Z_AXIS_STEP_MAIN:
/*N*/           case SCHATTR_Z_AXIS_STEP_HELP:
/*N*/           case SCHATTR_Z_AXIS_ORIGIN:
/*N*/
/*N*/               if(nId==CHOBJID_DIAGRAM_Z_AXIS)
/*N*/               {
/*N*/                   f=((const SvxDoubleItem&)rDestSet.Get(nWhich)).GetValue();
/*N*/                   rDestSet.Put(SvxDoubleItem(f,nWhich+USHORT(nOffZ)));
/*N*/                   if(bClear)
/*N*/                       rDestSet.ClearItem(nWhich);
/*N*/               }
/*N*/               break;
/*N*/       }
/*N*/       nWhich = aIter.NextWhich();
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Pruefe zwei ItemSets und vernichte paarweise verschiedene Items
|*
\************************************************************************/

//STRIP001 void CompareSets (const SfxItemSet &rSourceSet, SfxItemSet  &rDestSet)
//STRIP001 {
//STRIP001  SfxWhichIter      aIter (rSourceSet);
//STRIP001  USHORT            nWhich     = aIter.FirstWhich ();
//STRIP001  const SfxPoolItem *pPoolItem = NULL;
//STRIP001
//STRIP001  while (nWhich)
//STRIP001  {
//STRIP001      if ((rSourceSet.GetItemState(nWhich, TRUE, &pPoolItem) == SFX_ITEM_SET) &&
//STRIP001          (rDestSet.GetItemState(nWhich, TRUE, &pPoolItem) == SFX_ITEM_SET))
//STRIP001          if (rSourceSet.Get(nWhich) != rDestSet.Get(nWhich))
//STRIP001              rDestSet.InvalidateItem(nWhich);
//STRIP001
//STRIP001      nWhich = aIter.NextWhich ();
//STRIP001  }
//STRIP001 }
//STRIP001 void ClearDblItems(const SfxItemSet &rSourceSet, SfxItemSet  &rDestSet)
//STRIP001 {
//STRIP001  SfxWhichIter      aIter (rSourceSet);
//STRIP001  USHORT            nWhich     = aIter.FirstWhich ();
//STRIP001  const SfxPoolItem *pPoolItem = NULL;
//STRIP001
//STRIP001  while (nWhich)
//STRIP001  {
//STRIP001      if ((rSourceSet.GetItemState(nWhich, TRUE, &pPoolItem) == SFX_ITEM_SET) &&
//STRIP001          (rDestSet.GetItemState(nWhich, TRUE, &pPoolItem) == SFX_ITEM_SET))
//STRIP001          if (rSourceSet.Get(nWhich) != rDestSet.Get(nWhich))
//STRIP001              rDestSet.ClearItem(nWhich);
//STRIP001
//STRIP001      nWhich = aIter.NextWhich ();
//STRIP001  }
//STRIP001 }

/*N*/ void IntersectSets( const SfxItemSet &  rSource, SfxItemSet &  rDest )
/*N*/ {
/*N*/     SfxWhichIter aIter( rSource );
/*N*/     SfxItemState aSrcState;
/*N*/
/*N*/     for( USHORT nWhich = aIter.FirstWhich(); nWhich != 0; nWhich = aIter.NextWhich() )
/*N*/     {
/*N*/         aSrcState = rSource.GetItemState( nWhich );
/*N*/
/*N*/         if( // one item is (may be) set but the other one isn't
/*N*/             ( aSrcState != rDest.GetItemState( nWhich ) )
/*N*/             ||
/*N*/             // both items are set, but their content differs
/*N*/             // (if aSrcState is set it follows that also aDestState is set)
/*N*/             ( ( aSrcState == SFX_ITEM_SET )
/*N*/                 &&
/*N*/               ( rSource.Get( nWhich ) != rDest.Get( nWhich ) ) ) )
/*N*/         {
/*N*/             rDest.InvalidateItem( nWhich );
/*N*/         }
/*N*/     }
/*N*/ }

/*************************************************************************
|*
|* Setze je nach Ausrichtungsinformation den Punkt um den ausgerichtet wird
|*
|* Das wird hauptsaechlich von chtmode4 aufgerufen um zu wissen welche
|* Position des Textes man sich merken muss, um dne wird dann mit moeglicherweise
|* veraenderter Schriftgroesse ausgegeben.
|*
\************************************************************************/

/*N*/ Point SetPointOfRectangle (const Rectangle& rRect, ChartAdjust eAdjust)
/*N*/ {
/*N*/   switch (eAdjust)
/*N*/   {
/*?*/       case CHADJUST_TOP_LEFT:
/*?*/            return (rRect.TopLeft());
/*?*/       case CHADJUST_TOP_RIGHT:
/*?*/            return (rRect.TopRight());
/*N*/       case CHADJUST_TOP_CENTER:
/*N*/            return (rRect.TopCenter());
/*N*/       case CHADJUST_CENTER_LEFT:
/*N*/            return (rRect.LeftCenter());
/*?*/       case CHADJUST_CENTER_RIGHT:
/*?*/            return (rRect.RightCenter());
/*?*/       case CHADJUST_CENTER_CENTER:
/*?*/            return (rRect.Center());
/*?*/       case CHADJUST_BOTTOM_LEFT:
/*?*/            return (rRect.BottomLeft());
/*?*/       case CHADJUST_BOTTOM_CENTER:
/*N*/            return (rRect.BottomCenter());
/*?*/       case CHADJUST_BOTTOM_RIGHT:
/*?*/            return (rRect.BottomRight());
/*?*/       default:
/*?*/            ;
/*?*/   }
/*?*/   Point aPoint(-1,-1);
/*?*/   return aPoint;  // Das ist das Default für die Plazierungsinformation von Chart-Texten
/*N*/ }

//!!! Es werden NICHT ALLE Attr ausgewertet, nur Größen-relevante!
/*N*/ void ItemsToFont(const SfxItemSet& rSet,Font& rFont)
/*N*/ {
/*N*/   const SfxPoolItem* pItem = NULL;
/*N*/   if( rSet.GetItemState( EE_CHAR_FONTINFO, TRUE, &pItem ))
/*N*/   {
/*N*/       SvxFontItem* pFontItem = (SvxFontItem*)pItem;
/*N*/
/*N*/       rFont.SetStyleName(pFontItem->GetStyleName() );
/*N*/       rFont.SetName(     pFontItem->GetFamilyName());
/*N*/       rFont.SetCharSet(  pFontItem->GetCharSet());
/*N*/       rFont.SetFamily(   pFontItem->GetFamily());
/*N*/       rFont.SetPitch(    pFontItem->GetPitch());
/*N*/   }
/*N*/
/*N*/ //    rFont.SetColor( ((const SvxColorItem&)rSet.Get( EE_CHAR_COLOR )).GetValue() );
/*N*/ //    rFont.SetName( ((const SvxFontItem&)rSet.Get( EE_CHAR_FONTINFO )).GetFamilyName() );
/*N*/ //    rFont.SetFamily( ((const SvxFontItem&)rSet.Get( EE_CHAR_FONTINFO )).GetFamily() );
/*N*/ //    rFont.SetPitch( ((const SvxFontItem&)rSet.Get( EE_CHAR_FONTINFO )).GetPitch() );
/*N*/ //    rFont.SetCharSet( ((const SvxFontItem&)rSet.Get( EE_CHAR_FONTINFO )).GetCharSet() );
/*N*/
/*N*/   //  Scale the font's horizontal size like the vertical size.  Assume that the original size is
/*N*/   //  7pt.  The scaling is done here because the item EE_CHAR_FONTWIDTH holds a horizontal scaling
/*N*/   //  factor.  The horizontal size can therefore not be stored there.  But as the font is scaled
/*N*/   //  uniformly, the horizontal size depends uniquely on the vertical size.
/*N*/   long nFontHeight = static_cast<const SvxFontHeightItem&>(rSet.Get(EE_CHAR_FONTHEIGHT)).GetHeight();
/*N*/   const double fSevenPoint = (1000/*scale*/ * 2.54/*cm per inch*/ / 72/*point per inch*/ * 7 /*pt*/);
/*N*/   long nFontWidth = 0;    // #89001# use default font width
/*N*/   rFont.SetSize (Size (nFontWidth, nFontHeight));
/*N*/   //  Old line.
/*N*/   //  rFont.SetSize( Size( ((const SvxFontWidthItem&)rSet.Get( EE_CHAR_FONTWIDTH )).GetWidth(),
/*N*/   //   ((const SvxFontHeightItem&)rSet.Get( EE_CHAR_FONTHEIGHT )).GetHeight() ) );
/*N*/
/*N*/   rFont.SetWeight( ((const SvxWeightItem&)rSet.Get( EE_CHAR_WEIGHT )).GetWeight() );
/*N*/   rFont.SetUnderline( ((const SvxUnderlineItem&)rSet.Get( EE_CHAR_UNDERLINE )).GetUnderline() );
/*N*/   rFont.SetStrikeout( ((const SvxCrossedOutItem&)rSet.Get( EE_CHAR_STRIKEOUT )).GetStrikeout() );
/*N*/   rFont.SetItalic( ((const SvxPostureItem&)rSet.Get( EE_CHAR_ITALIC )).GetPosture() );
/*N*/   rFont.SetOutline( ((const SvxContourItem&)rSet.Get( EE_CHAR_OUTLINE )).GetValue() );
/*N*/   rFont.SetShadow( ((const SvxShadowedItem&)rSet.Get( EE_CHAR_SHADOW )).GetValue() );
/*N*/   //rFont.SetEscapement( ((const SvxEscapementItem&)rSet.Get( EE_CHAR_ESCAPEMENT)).GetEsc() );
/*N*/   //rFont.SetPropr( ((const SvxEscapementItem&)rSet.Get( EE_CHAR_ESCAPEMENT)).GetProp() );
/*N*/   rFont.SetKerning( ((const SvxAutoKernItem&)rSet.Get( EE_CHAR_PAIRKERNING )).GetValue() );
/*N*/   //rFont.SetFixKerning( ((const SvxKerningItem&)rSet.Get( EE_CHAR_KERNING )).GetValue() );
/*N*/   rFont.SetWordLineMode( ((const SvxWordLineModeItem&)rSet.Get( EE_CHAR_WLM )).GetValue() );
/*N*/ //    rFont.SetOrientation( (short)(rDesc.Orientation*10) );
/*N*/ }

//STRIP001 void GlobalGenerate3DAttrDefaultItem( INT16 nWID, SfxItemSet& rSet )
//STRIP001 {
//STRIP001  E3dDefaultAttributes a3DDefaultAttr;
//STRIP001 //-/ SfxItemSet aSet( *rSet.GetPool(), SID_ATTR_3D_START, SID_ATTR_3D_END );
//STRIP001  SfxItemSet aSet( *rSet.GetPool(), SDRATTR_3D_FIRST, SDRATTR_3D_LAST);
//STRIP001 //-/ a3DDefaultAttr.TakeDefaultValues( aSet );
//STRIP001  const SfxPoolItem* pItem = 0;
//STRIP001  SfxPoolItem *pNewItem = 0;
//STRIP001  SfxItemState eState = aSet.GetItemState( nWID, TRUE, &pItem );
//STRIP001  if( eState >= SFX_ITEM_DEFAULT && pItem )
//STRIP001  {
//STRIP001      pNewItem = pItem->Clone();
//STRIP001      rSet.Put( *pNewItem, nWID );
//STRIP001      delete pNewItem;
//STRIP001  }
//STRIP001 }

} //namespace binfilter
#ifdef DBG_UTIL

// ==================== DEBUG SfxItemSets ====================

#ifndef _SFXITEMPOOL_HXX
#include <svtools/itempool.hxx>
#endif
#ifndef _SFXITEMITER_HXX
#include <svtools/itemiter.hxx>
#endif

#include <cstdio>       // for snprintf
#include <cstring>      // for strncat
namespace binfilter {//STRIP009
/*N*/ void Dbg_DebugItems( SfxItemSet& rSet, ChartModel* pModel, long num )
/*N*/ {
/*N*/   SfxItemPool *pItemPool=&( pModel->GetItemPool() );
/*N*/
/*N*/   char pBuf[ 512 ] = "";
/*N*/   char pSmallBuf[ 128 ] = "";
/*N*/
/*N*/   const USHORT* pRanges = rSet.GetRanges();
/*N*/   for( long n = 0; pRanges[ n ] && n<32; n++ )
/*N*/   {
/*N*/       snprintf( pSmallBuf, sizeof(pSmallBuf), "[%ld; %ld] ", pRanges[ n ], pRanges[ ++n ] );
/*N*/       strncat( pBuf, pSmallBuf, sizeof(pBuf) - strlen(pBuf) - 1 );
/*N*/   }
/*N*/
/*N*/   DBG_TRACE1( "SCH:ItemDBG - Ranges: %s", pBuf );
/*N*/
/*N*/   pBuf[ 0 ] = '\0';
/*N*/
/*N*/   long nInv = 0, nCnt = 0, nCnv = 0, nCns = 0;
/*N*/   SfxItemIter aIterator( rSet );
/*N*/
/*N*/   const SfxPoolItem* pItem;
/*N*/   USHORT nWhich, nNewWhich;
/*N*/
/*N*/   pItem = aIterator.FirstItem();
/*N*/   while( pItem )
/*N*/   {
/*N*/       if( ! IsInvalidItem( pItem ) )
/*N*/       {
/*N*/           nWhich= pItem->Which();
/*N*/
/*N*/           nCnt++;
/*N*/           if( nWhich < SCHATTR_END )
/*N*/               nCns++;
/*N*/           if( nCnt < 100 )
/*N*/           {
/*N*/               snprintf( pSmallBuf, sizeof(pSmallBuf), "%ld, ", nWhich );
/*N*/               strncat( pBuf, pSmallBuf, sizeof(pBuf) - strlen(pBuf) - 1 );
/*N*/           }
/*N*/
/*N*/           nNewWhich = pItemPool->GetWhich( nWhich );
/*N*/           if( nWhich != nNewWhich )
/*?*/               nCnv++;
/*N*/       }
/*N*/       else
/*?*/           nInv++;
/*N*/
/*N*/       pItem = aIterator.NextItem();
/*N*/   }
/*N*/
/*N*/   DBG_TRACE1( "SCH:ItemDBG - List: %s", pBuf );
/*N*/
/*N*/   long nColor = -1;
/*N*/   long nMat = -1;
/*N*/   const SfxPoolItem *pPoolItem;
/*N*/
/*N*/   if( SFX_ITEM_SET == rSet.GetItemState(XATTR_FILLCOLOR,TRUE,&pPoolItem ) )
/*N*/   {
/*N*/       Color aColor( ( ( const XFillColorItem* ) pPoolItem )->GetValue() );
/*N*/       nColor=aColor.GetRGBColor();
/*N*/   }
/*N*/ //-/  if( SFX_ITEM_SET == rSet.GetItemState( SID_ATTR_3D_MAT_COLOR, TRUE, &pPoolItem ) )
/*N*/   if( SFX_ITEM_SET == rSet.GetItemState( SDRATTR_3DOBJ_MAT_COLOR, TRUE, &pPoolItem ) )
/*N*/   {
/*N*/       Color aNew(  ((const SvxColorItem*) pPoolItem )->GetValue()   );
/*N*/       nMat=aNew.GetRGBColor();
/*N*/   }
/*N*/
/*N*/
/*N*/   long r=COLORDATA_RED(nColor),g=COLORDATA_GREEN(nColor),b=COLORDATA_BLUE(nColor);
/*N*/
/*N*/   DBG_TRACE4( "SCH:ItemDBG - Info: this=%lx, #=%ld, WID-able=%ld, invalid=%ld", (long)pModel, nCnt, nCnv, nInv );
/*N*/   DBG_TRACE5( "... Chart=%ld, RGB=(%d, %d, %d), Mat=%ld", nCns, r, g, b, nMat );
/*N*/ }
} //namespace binfilter
#endif



