/*************************************************************************
 *
 *  $RCSfile: svx_svdocirc.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:20 $
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

#ifndef _SFXSTYLE_HXX //autogen
#include <svtools/style.hxx>
#endif

#ifndef _BIGINT_HXX //autogen
#include <tools/bigint.hxx>
#endif

#ifndef _SVX_XLNWTIT_HXX //autogen
#include <xlnwtit.hxx>
#endif

#ifndef _SVX_XLNEDWIT_HXX //autogen
#include <xlnedwit.hxx>
#endif

#ifndef _SVX_XLNSTWIT_HXX //autogen
#include <xlnstwit.hxx>
#endif

#ifndef _SVX_XLNSTIT_HXX //autogen
#include <xlnstit.hxx>
#endif

#ifndef _SVX_XLNEDIT_HXX //autogen
#include <xlnedit.hxx>
#endif

#include "svdocirc.hxx"
#include <math.h>
#include "xpool.hxx"
#include "svdtouch.hxx"
#include "svdxout.hxx"
#include "svdattr.hxx"
#include "svdpool.hxx"
#include "svdattrx.hxx"
#include "svdtrans.hxx"
#include "svdio.hxx"
#include "svdetc.hxx"
#include "svddrag.hxx"
#include "svdmodel.hxx"
#include "svdpage.hxx"
#include "svdopath.hxx" // fuer die Objektkonvertierung
#include "svdview.hxx"  // Zum Draggen (Ortho)
#include "svdglob.hxx"   // StringCache
#include "svdstr.hrc"    // Objektname

#ifndef _EEITEM_HXX
#include "eeitem.hxx"
#endif

#ifndef _SVX_SVDOIMP_HXX
#include "svdoimp.hxx"
#endif

/*N*/ void SetWinkPnt(const Rectangle& rR, long nWink, Point& rPnt)
/*N*/ {
/*N*/   Point aCenter(rR.Center());
/*N*/   long nWdt=rR.Right()-rR.Left();
/*N*/   long nHgt=rR.Bottom()-rR.Top();
/*N*/   long nMaxRad=((nWdt>nHgt ? nWdt : nHgt)+1) /2;
/*N*/   double a;
/*N*/   a=nWink*nPi180;
/*N*/   rPnt=Point(Round(cos(a)*nMaxRad),-Round(sin(a)*nMaxRad));
/*N*/   if (nWdt==0) rPnt.X()=0;
/*N*/   if (nHgt==0) rPnt.Y()=0;
/*N*/   if (nWdt!=nHgt) {
/*N*/       if (nWdt>nHgt) {
/*N*/           if (nWdt!=0) {
/*N*/               // eventuelle Ueberlaeufe bei sehr grossen Objekten abfangen (Bug 23384)
/*N*/               if (Abs(nHgt)>32767 || Abs(rPnt.Y())>32767) {
/*N*/                   rPnt.Y()=BigMulDiv(rPnt.Y(),nHgt,nWdt);
/*N*/               } else {
/*N*/                   rPnt.Y()=rPnt.Y()*nHgt/nWdt;
/*N*/               }
/*N*/           }
/*N*/       } else {
/*N*/           if (nHgt!=0) {
/*N*/               // eventuelle Ueberlaeufe bei sehr grossen Objekten abfangen (Bug 23384)
/*N*/               if (Abs(nWdt)>32767 || Abs(rPnt.X())>32767) {
/*N*/                   rPnt.X()=BigMulDiv(rPnt.X(),nWdt,nHgt);
/*N*/               } else {
/*N*/                   rPnt.X()=rPnt.X()*nWdt/nHgt;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   rPnt+=aCenter;
/*N*/ }

/*N*/ TYPEINIT1(SdrCircObj,SdrRectObj);

/*N*/ SdrCircObj::SdrCircObj(SdrObjKind eNewKind)
/*N*/ {
/*N*/   nStartWink=0;
/*N*/   nEndWink=36000;
/*N*/   eKind=eNewKind;
/*N*/   bClosedObj=eNewKind!=OBJ_CARC;
/*N*/ }

/*N*/ SdrCircObj::SdrCircObj(SdrObjKind eNewKind, const Rectangle& rRect):
/*N*/   SdrRectObj(rRect)
/*N*/ {
/*N*/   nStartWink=0;
/*N*/   nEndWink=36000;
/*N*/   eKind=eNewKind;
/*N*/   bClosedObj=eNewKind!=OBJ_CARC;
/*N*/ }

/*N*/ SdrCircObj::SdrCircObj(SdrObjKind eNewKind, const Rectangle& rRect, long nNewStartWink, long nNewEndWink):
/*N*/   SdrRectObj(rRect)
/*N*/ {
/*N*/   long nWinkDif=nNewEndWink-nNewStartWink;
/*N*/   nStartWink=NormAngle360(nNewStartWink);
/*N*/   nEndWink=NormAngle360(nNewEndWink);
/*N*/   if (nWinkDif==36000) nEndWink+=nWinkDif; // Vollkreis
/*N*/   eKind=eNewKind;
/*N*/   bClosedObj=eNewKind!=OBJ_CARC;
/*N*/ }
/*N*/
/*N*/ SdrCircObj::~SdrCircObj()
/*N*/ {
/*N*/ }

//STRIP001 void SdrCircObj::TakeObjInfo(SdrObjTransformInfoRec& rInfo) const
//STRIP001 {
//STRIP001  FASTBOOL bCanConv=!HasText() || ImpCanConvTextToCurve();
//STRIP001  rInfo.bEdgeRadiusAllowed    = FALSE;
//STRIP001  rInfo.bCanConvToPath=bCanConv;
//STRIP001  rInfo.bCanConvToPoly=bCanConv;
//STRIP001  rInfo.bCanConvToContour = !IsFontwork() && (rInfo.bCanConvToPoly || LineGeometryUsageIsNecessary());
//STRIP001 }

/*N*/ UINT16 SdrCircObj::GetObjIdentifier() const
/*N*/ {
/*N*/   return UINT16(eKind);
/*N*/ }

/*N*/ FASTBOOL SdrCircObj::PaintNeedsXPoly() const
/*N*/ {
/*N*/   // XPoly ist notwendig fuer alle gedrehten Ellipsenobjekte,
/*N*/   // fuer alle Kreis- und Ellipsenabschnitte
/*N*/   // und wenn nicht WIN dann (erstmal) auch fuer Kreis-/Ellipsenausschnitte
/*N*/   // und Kreis-/Ellipsenboegen (wg. Genauigkeit)
/*N*/   FASTBOOL bNeed=aGeo.nDrehWink!=0 || aGeo.nShearWink!=0 || eKind==OBJ_CCUT;
/*N*/ #ifndef WIN
/*N*/   // Wenn nicht Win, dann fuer alle ausser Vollkreis (erstmal!!!)
/*N*/   if (eKind!=OBJ_CIRC) bNeed=TRUE;
/*N*/ #endif
/*N*/
/*N*/   const SfxItemSet& rSet = GetItemSet();
/*N*/   if(!bNeed)
/*N*/   {
/*N*/       // XPoly ist notwendig fuer alles was nicht LineSolid oder LineNone ist
/*N*/       XLineStyle eLine = ((XLineStyleItem&)(rSet.Get(XATTR_LINESTYLE))).GetValue();
/*N*/       bNeed = eLine != XLINE_NONE && eLine != XLINE_SOLID;
/*N*/
/*N*/       // XPoly ist notwendig fuer dicke Linien
/*N*/       if(!bNeed && eLine != XLINE_NONE)
/*N*/           bNeed = ((XLineWidthItem&)(rSet.Get(XATTR_LINEWIDTH))).GetValue() != 0;
/*N*/
/*N*/       // XPoly ist notwendig fuer Kreisboegen mit Linienenden
/*N*/       if(!bNeed && eKind == OBJ_CARC)
/*N*/       {
/*N*/           // Linienanfang ist da, wenn StartPolygon und StartWidth!=0
/*?*/           bNeed=((XLineStartItem&)(rSet.Get(XATTR_LINESTART))).GetValue().GetPointCount() != 0 &&
/*?*/                 ((XLineStartWidthItem&)(rSet.Get(XATTR_LINESTARTWIDTH))).GetValue() != 0;
/*?*/
/*?*/           if(!bNeed)
/*?*/           {
/*?*/               // Linienende ist da, wenn EndPolygon und EndWidth!=0
/*?*/               bNeed = ((XLineEndItem&)(rSet.Get(XATTR_LINEEND))).GetValue().GetPointCount() != 0 &&
/*?*/                       ((XLineEndWidthItem&)(rSet.Get(XATTR_LINEENDWIDTH))).GetValue() != 0;
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // XPoly ist notwendig, wenn Fill !=None und !=Solid
/*N*/   if(!bNeed && eKind != OBJ_CARC)
/*N*/   {
/*N*/       XFillStyle eFill=((XFillStyleItem&)(rSet.Get(XATTR_FILLSTYLE))).GetValue();
/*N*/       bNeed = eFill != XFILL_NONE && eFill != XFILL_SOLID;
/*N*/   }
/*N*/
/*N*/   if(!bNeed && eKind != OBJ_CIRC && nStartWink == nEndWink)
/*N*/       bNeed=TRUE; // Weil sonst Vollkreis gemalt wird
/*N*/
/*N*/   return bNeed;
/*N*/ }

/*N*/ XPolygon SdrCircObj::ImpCalcXPoly(const Rectangle& rRect1, long nStart, long nEnd, FASTBOOL bContour) const
/*N*/ {
/*N*/   bContour=TRUE; // am 14.1.97 wg. Umstellung TakeContour ueber Mtf und Paint. Joe.
/*N*/   long rx=rRect1.GetWidth()/2;  // Da GetWidth()/GetHeight() jeweils 1
/*N*/   long ry=rRect1.GetHeight()/2; // draufaddieren wird korrekt gerundet.
/*N*/   long a=0,e=3600;
/*N*/   if (eKind!=OBJ_CIRC) {
/*N*/       a=nStart/10;
/*N*/       e=nEnd/10;
/*N*/       if (bContour) {
/*N*/           // Drehrichtung umkehren, damit Richtungssinn genauso wie Rechteck
/*N*/           rx=-rx;
/*N*/           a=1800-a; if (a<0) a+=3600;
/*N*/           e=1800-e; if (e<0) e+=3600;
/*N*/           long nTmp=a;
/*N*/           a=e;
/*N*/           e=nTmp;
/*N*/       }
/*N*/   } else {
/*N*/       if (bContour) {
/*N*/           long nTmp=rx;
/*N*/           rx=ry;
/*N*/           ry=nTmp;
/*N*/           // und auch noch die Drehrichtung aendern
/*N*/           ry=-ry;
/*N*/       }
/*N*/   }
/*N*/   ((SdrCircObj*)this)->bXPolyIsLine=eKind==OBJ_CARC;
/*N*/   FASTBOOL bClose=eKind==OBJ_CIRC /*|| eKind==OBJ_SECT*/;
/*N*/   XPolygon aXPoly(rRect1.Center(),rx,ry,USHORT(a),USHORT(e),bClose);
/*N*/   if (eKind!=OBJ_CIRC && nStart==nEnd) {
/*?*/       if (eKind==OBJ_SECT) {
/*?*/           Point aMerk(aXPoly[0]);
/*?*/           aXPoly=XPolygon(2);
/*?*/           aXPoly[0]=rRect1.Center();
/*?*/           aXPoly[1]=aMerk;
/*?*/       } else {
/*?*/           aXPoly=XPolygon();
/*?*/       }
/*N*/   }
/*N*/   if (eKind==OBJ_SECT) { // Der Sektor soll Start/Ende im Zentrum haben
/*N*/       // Polygon um einen Punkt rotieren (Punkte im Array verschieben)
/*N*/       unsigned nPointAnz=aXPoly.GetPointCount();
/*N*/       aXPoly.Insert(0,rRect1.Center(),XPOLY_NORMAL);
/*N*/       aXPoly[aXPoly.GetPointCount()]=rRect1.Center();
/*N*/   }
/*N*/   // Der Kreis soll Anfang und Ende im unteren Scheitelpunkt haben!
/*N*/   if (bContour && eKind==OBJ_CIRC) RotateXPoly(aXPoly,rRect1.Center(),-1.0,0.0);
/*N*/   // Die Winkelangaben beziehen sich immer auf die linke obere Ecke von !aRect!
/*N*/   if (aGeo.nShearWink!=0) ShearXPoly(aXPoly,aRect.TopLeft(),aGeo.nTan);
/*N*/   if (aGeo.nDrehWink!=0) RotateXPoly(aXPoly,aRect.TopLeft(),aGeo.nSin,aGeo.nCos);
/*N*/   return aXPoly;
/*N*/ }

/*N*/ void SdrCircObj::RecalcXPoly()
/*N*/ {
/*N*/   pXPoly=new XPolygon(ImpCalcXPoly(aRect,nStartWink,nEndWink));
/*N*/ }

/*N*/ void SdrCircObj::RecalcBoundRect()
/*N*/ {
/*N*/   SetWinkPnt(aRect,nStartWink,aPnt1);
/*N*/   SetWinkPnt(aRect,nEndWink,aPnt2);
/*N*/   bBoundRectDirty=FALSE;
/*N*/   aOutRect=GetSnapRect();
/*N*/   long nLineWdt=ImpGetLineWdt();
/*N*/   nLineWdt++; nLineWdt/=2;
/*N*/   if (nLineWdt!=0) {
/*N*/       long nWink=nEndWink-nStartWink;
/*N*/       if (nWink<0) nWink+=36000;
/*N*/       if (eKind==OBJ_SECT && nWink<18000) nLineWdt*=2; // doppelt, wegen evtl. spitzen Ecken
/*N*/       if (eKind==OBJ_CCUT && nWink<18000) nLineWdt*=2; // doppelt, wegen evtl. spitzen Ecken
/*N*/   }
/*N*/   if (eKind==OBJ_CARC) { // ggf. Linienenden beruecksichtigen
/*N*/       long nLEndWdt=ImpGetLineEndAdd();
/*N*/       if (nLEndWdt>nLineWdt) nLineWdt=nLEndWdt;
/*N*/   }
/*N*/   if (nLineWdt!=0) {
/*N*/       aOutRect.Left  ()-=nLineWdt;
/*N*/       aOutRect.Top   ()-=nLineWdt;
/*N*/       aOutRect.Right ()+=nLineWdt;
/*N*/       aOutRect.Bottom()+=nLineWdt;
/*N*/   }
/*N*/   ImpAddShadowToBoundRect();
/*N*/   ImpAddTextToBoundRect();
/*N*/ }

/*N*/ FASTBOOL SdrCircObj::Paint(ExtOutputDevice& rXOut, const SdrPaintInfoRec& rInfoRec) const
/*N*/ {
/*N*/   // Hidden objects on masterpages, draw nothing
/*N*/   if((rInfoRec.nPaintMode & SDRPAINTMODE_MASTERPAGE) && bNotVisibleAsMaster)
/*N*/       return TRUE;
/*N*/
/*N*/   BOOL bHideContour(IsHideContour());
/*N*/   BOOL bIsLineDraft(0 != (rInfoRec.nPaintMode & SDRPAINTMODE_DRAFTLINE));
/*N*/   BOOL bIsFillDraft(0 != (rInfoRec.nPaintMode & SDRPAINTMODE_DRAFTFILL));
/*N*/
/*N*/   // prepare ItemSet of this object
/*N*/   const SfxItemSet& rSet = GetItemSet();
/*N*/
/*N*/   // perepare ItemSet to avoid old XOut line drawing
/*N*/   SfxItemSet aEmptySet(*rSet.GetPool());
/*N*/   aEmptySet.Put(XLineStyleItem(XLINE_NONE));
/*N*/   aEmptySet.Put(XFillStyleItem(XFILL_NONE));
/*N*/
/*N*/     // #103692# prepare ItemSet for shadow fill attributes
/*N*/     SfxItemSet aShadowSet(rSet);
/*N*/
/*N*/   // prepare line geometry
/*N*/   ::std::auto_ptr< SdrLineGeometry > pLineGeometry( ImpPrepareLineGeometry(rXOut, rSet, bIsLineDraft) );
/*N*/
/*N*/   // Shadows
/*N*/   if(!bHideContour && ImpSetShadowAttributes(rSet, aShadowSet))
/*N*/   {
/*?*/         if( eKind==OBJ_CARC || bIsFillDraft )
/*?*/             rXOut.SetFillAttr(aEmptySet);
/*?*/         else
/*?*/             rXOut.SetFillAttr(aShadowSet);
/*?*/
/*?*/       UINT32 nXDist=((SdrShadowXDistItem&)(rSet.Get(SDRATTR_SHADOWXDIST))).GetValue();
/*?*/       UINT32 nYDist=((SdrShadowYDistItem&)(rSet.Get(SDRATTR_SHADOWYDIST))).GetValue();
/*?*/
/*?*/       // avoid shadow line drawing in XOut
/*?*/       rXOut.SetLineAttr(aEmptySet);
/*?*/
/*?*/         if (PaintNeedsXPoly())
/*?*/         {
/*?*/             if( !bXPolyIsLine )
/*?*/             {
/*?*/                 XPolygon aX(GetXPoly()); // In dieser Reihenfolge, damit bXPolyIsLine gueltig ist.
/*?*/                 aX.Move(nXDist,nYDist);
/*?*/
/*?*/                 // #100127# Output original geometry for metafiles
/*?*/                 ImpGraphicFill aFill( *this, rXOut, aShadowSet, true );
/*?*/
/*?*/                 rXOut.DrawXPolygon(aX);
/*?*/             }
/*?*/         } else {
/*?*/             // #100127# Output original geometry for metafiles
/*?*/             ImpGraphicFill aFill( *this, rXOut, aShadowSet, true );
/*?*/
/*?*/             Rectangle aR(aRect);
/*?*/             aR.Move(nXDist,nYDist);
/*?*/             if (eKind==OBJ_CIRC) {
/*?*/                 rXOut.DrawEllipse(aR);
/*?*/             } else {
/*?*/                 GetBoundRect(); // fuer aPnt1,aPnt2
/*?*/                 Point aTmpPt1(aPnt1);
/*?*/                 Point aTmpPt2(aPnt2);
/*?*/                 aTmpPt1.X()+=nXDist;
/*?*/                 aTmpPt1.Y()+=nYDist;
/*?*/                 aTmpPt2.X()+=nXDist;
/*?*/                 aTmpPt2.Y()+=nYDist;
/*?*/                 switch (eKind) {
/*?*/                     case OBJ_SECT: rXOut.DrawPie(aR,aTmpPt1,aTmpPt2); break;
/*?*/                     case OBJ_CARC: rXOut.DrawArc(aR,aTmpPt1,aTmpPt2); break;
/*?*/                     case OBJ_CCUT: DBG_ERROR("SdrCircObj::Paint(): ein Kreisabschnitt muss immer mit XPoly gepaintet werden"); break;
/*?*/                 }
/*?*/             }
/*?*/         }
/*?*/
/*?*/       // new shadow line drawing
/*?*/       if( pLineGeometry.get() )
/*?*/       {DBG_ASSERT(0, "STRIP"); //STRIP001
/*?*/           // draw the line geometry
//STRIP001 /*?*/            ImpDrawShadowLineGeometry(rXOut, rSet, *pLineGeometry);
/*?*/       }
/*N*/   }

    // Before here the LineAttr were set: if(pLineAttr) rXOut.SetLineAttr(*pLineAttr);
/*N*/   rXOut.SetLineAttr(aEmptySet);
/*N*/
/*N*/     rXOut.SetFillAttr( bIsFillDraft ? aEmptySet : rSet );
/*N*/
/*N*/   if (!bHideContour) {
/*N*/       if (PaintNeedsXPoly())
/*N*/         {
/*?*/           if( !bXPolyIsLine )
/*?*/             {
/*?*/                 const XPolygon& rXP=GetXPoly(); // In dieser Reihenfolge, damit bXPolyIsLine gueltig ist.
/*?*/
/*?*/                 // #100127# Output original geometry for metafiles
/*?*/                 ImpGraphicFill aFill( *this, rXOut, bIsFillDraft ? aEmptySet : rSet );
/*?*/
/*?*/               rXOut.DrawXPolygon(rXP);
/*N*/           }
/*N*/       } else {
/*N*/             // #100127# Output original geometry for metafiles
/*N*/             ImpGraphicFill aFill( *this, rXOut, bIsFillDraft ? aEmptySet : rSet );
/*N*/
/*N*/           if (eKind==OBJ_CIRC) {
/*N*/               rXOut.DrawEllipse(aRect);
/*N*/           } else {
/*?*/               GetBoundRect(); // fuer aPnt1,aPnt2
/*?*/               switch (eKind) {
/*?*/                   case OBJ_SECT: rXOut.DrawPie(aRect,aPnt1,aPnt2); break;
/*?*/                   case OBJ_CARC: rXOut.DrawArc(aRect,aPnt1,aPnt2); break;
/*?*/                   case OBJ_CCUT: DBG_ERROR("SdrCircObj::Paint(): ein Kreisabschnitt muss immer mit XPoly gepaintet werden"); break;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }

    // Own line drawing
/*N*/   if(!bHideContour && pLineGeometry.get() )
/*N*/   {
/*N*/       // draw the line geometry
/*N*/       ImpDrawColorLineGeometry(rXOut, rSet, *pLineGeometry);
/*N*/   }
/*N*/
/*N*/   FASTBOOL bOk=TRUE;
/*N*/   if (HasText()) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        bOk=SdrTextObj::Paint(rXOut,rInfoRec);
/*N*/   }
/*N*/   if (bOk && (rInfoRec.nPaintMode & SDRPAINTMODE_GLUEPOINTS) !=0) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        bOk=PaintGluePoints(rXOut,rInfoRec);
/*N*/   }
/*N*/
/*N*/   return bOk;
/*N*/ }

//STRIP001 SdrObject* SdrCircObj::CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const
//STRIP001 {
//STRIP001  if (pVisiLayer!=NULL && !pVisiLayer->IsSet(nLayerId)) return NULL;
//STRIP001  Point aPt(rPnt);
//STRIP001  Point aZero;
//STRIP001  aPt.X()-=aRect.Left();
//STRIP001  aPt.Y()-=aRect.Top();
//STRIP001
//STRIP001  INT32 nMyTol=nTol;
//STRIP001  FASTBOOL bFilled=eKind!=OBJ_CARC && (bTextFrame || HasFill());
//STRIP001
//STRIP001  INT32 nWdt=ImpGetLineWdt()/2; // Halbe Strichstaerke
//STRIP001  long nBoundWdt=aRect.GetWidth()-1;
//STRIP001  long nBoundHgt=aRect.GetHeight()-1;
//STRIP001  if (eKind==OBJ_SECT) {
//STRIP001      long nTmpWink=NormAngle360(nEndWink-nStartWink);
//STRIP001      if (nTmpWink<9000) {
//STRIP001          nBoundWdt=0;
//STRIP001          nBoundHgt=0;
//STRIP001      } else if (nTmpWink<27000) {
//STRIP001          nBoundWdt/=2;
//STRIP001          nBoundHgt/=2;
//STRIP001      }
//STRIP001  }
//STRIP001  if (bFilled && nBoundWdt>short(nTol) && nBoundHgt>short(nTol) && Abs(aGeo.nShearWink)<=4500) nMyTol=0; // Keine Toleranz noetig hier
//STRIP001  if (nWdt>nMyTol) nMyTol=nWdt; // Bei dicker Umrandung keine Toleranz noetig
//STRIP001
//STRIP001  // Den uebergebenen Punkt auf den gedrehten, geshearten Kreis transformieren
//STRIP001  // Unrotate:
//STRIP001  if (aGeo.nDrehWink!=0) RotatePoint(aPt,aZero,-aGeo.nSin,aGeo.nCos); // -sin fuer Umkehrung
//STRIP001  // Unshear:
//STRIP001  if (aGeo.nShearWink!=0) ShearPoint(aPt,aZero,-aGeo.nTan); // -tan fuer Umkehrung
//STRIP001
//STRIP001  long nXRad=aRect.GetWidth()/2;  if (nXRad<1) nXRad=1;
//STRIP001  long nYRad=aRect.GetHeight()/2; if (nYRad<1) nYRad=1;
//STRIP001
//STRIP001  // Die wirklichen Radien fuer spaeter merken
//STRIP001  long nXRadReal=nXRad;
//STRIP001  long nYRadReal=nYRad;
//STRIP001  aPt.X()-=nXRad;
//STRIP001  aPt.Y()-=nYRad;
//STRIP001  Point aPtNoStretch(aPt);
//STRIP001
//STRIP001  if (nXRad>nYRad) {
//STRIP001      aPt.Y()=BigMulDiv(aPt.Y(),nXRad,nYRad);
//STRIP001      // Da die Strichstaerke bei Ellipsen ueberall gleich ist:
//STRIP001      if (Abs(aPt.X())<Abs(aPt.Y())) {
//STRIP001          nMyTol=BigMulDiv(nMyTol,nXRad,nYRad);
//STRIP001      }
//STRIP001      nYRad=nXRad;
//STRIP001  }
//STRIP001  if (nYRad>nXRad) {
//STRIP001      aPt.X()=BigMulDiv(aPt.X(),nYRad,nXRad);
//STRIP001      // Da die Strichstaerke bei Ellipsen ueberall gleich ist:
//STRIP001      if (Abs(aPt.Y())<Abs(aPt.X())) {
//STRIP001          nMyTol=BigMulDiv(nMyTol,nYRad,nXRad);
//STRIP001      }
//STRIP001      nXRad=nYRad;
//STRIP001  }
//STRIP001
//STRIP001  // Die BigInts haben bei *= leider ein Vorzeichenproblem (a*=a;)
//STRIP001  // (SV250A), deshalb hier soviele Instanzen. (JOE)
//STRIP001  long nAussen=nXRad+nMyTol;
//STRIP001  BigInt nBigTmpA(nAussen);
//STRIP001  BigInt nAusRadQ(nBigTmpA*nBigTmpA);
//STRIP001  long nInnen=nXRad-nMyTol; if (nInnen<=0) nInnen=0;
//STRIP001  BigInt nBigTmpI(nInnen);
//STRIP001  // wird sonst nicht benoetigt, ggf. BugMul sparen:
//STRIP001  BigInt nInnRadQ((!bFilled && nInnen!=0) ? nBigTmpI*nBigTmpI : nBigTmpI);
//STRIP001
//STRIP001  // Radius von aPt berechnen
//STRIP001  BigInt nBigTmpX(aPt.X());
//STRIP001  BigInt nBigTmpY(aPt.Y());
//STRIP001  BigInt nPntRadQ(nBigTmpX*nBigTmpX+nBigTmpY*nBigTmpY);
//STRIP001
//STRIP001  FASTBOOL bRet=FALSE;
//STRIP001  if (nPntRadQ<=nAusRadQ) { // sonst ausserhalb
//STRIP001      if (nInnen==0) bRet=TRUE;
//STRIP001      else if (eKind==OBJ_CIRC) { // Vollkreis
//STRIP001          if (bFilled) bRet=TRUE;
//STRIP001          else if (nPntRadQ>=nInnRadQ) bRet=TRUE;
//STRIP001      } else { // Teilkreise
//STRIP001          long nWink=NormAngle360(GetAngle(aPt));
//STRIP001          long a=nStartWink;
//STRIP001          long e=nEndWink;
//STRIP001          if (e<a) e+=36000;
//STRIP001          if (nWink<a) nWink+=36000;
//STRIP001          if (nWink>=a && nWink<=e) {
//STRIP001              if (bFilled) bRet=TRUE;
//STRIP001              else if (nPntRadQ>=nInnRadQ) bRet=TRUE;
//STRIP001          }
//STRIP001          if (!bRet) {
//STRIP001              Rectangle aR(aPtNoStretch.X()-nMyTol,aPtNoStretch.Y()-nMyTol,
//STRIP001                           aPtNoStretch.X()+nMyTol,aPtNoStretch.Y()+nMyTol);
//STRIP001              Point aP1(aPnt1);
//STRIP001              aP1.X()-=aRect.Left()+nXRadReal;
//STRIP001              aP1.Y()-=aRect.Top()+nYRadReal;
//STRIP001              Point aP2(aPnt2);
//STRIP001              aP2.X()-=aRect.Left()+nXRadReal;
//STRIP001              aP2.Y()-=aRect.Top()+nYRadReal;
//STRIP001              if (eKind==OBJ_SECT) { // Kreissektor: nur noch die beiden Strecken testen
//STRIP001                  bRet=IsRectTouchesLine(aZero,aP1,aR) || IsRectTouchesLine(aZero,aP2,aR);
//STRIP001              }
//STRIP001              if (eKind==OBJ_CCUT) { // Kreisabschnitt noch die Sehne und die MaeuseEcke (Dreieck) testen
//STRIP001                  if (IsRectTouchesLine(aP1,aP2,aR)) bRet=TRUE; // die Sehne
//STRIP001                  else if (bFilled) { // und nun die Maeusescke
//STRIP001                      Polygon aPoly(XOutCreatePolygon(GetXPoly(),NULL));
//STRIP001                      bRet=IsPointInsidePoly(aPoly,rPnt);
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if (!bRet && HasText()) bRet=SdrTextObj::CheckHit(rPnt,nTol,pVisiLayer)!=NULL;
//STRIP001  return bRet ? (SdrObject*)this : NULL;
//STRIP001 }

//STRIP001 void SdrCircObj::TakeObjNameSingul(XubString& rName) const
//STRIP001 {
//STRIP001  USHORT nID=STR_ObjNameSingulCIRC;
//STRIP001  if (aRect.GetWidth()==aRect.GetHeight() && aGeo.nShearWink==0) {
//STRIP001      switch (eKind) {
//STRIP001          case OBJ_CIRC: nID=STR_ObjNameSingulCIRC; break;
//STRIP001          case OBJ_SECT: nID=STR_ObjNameSingulSECT; break;
//STRIP001          case OBJ_CARC: nID=STR_ObjNameSingulCARC; break;
//STRIP001          case OBJ_CCUT: nID=STR_ObjNameSingulCCUT; break;
//STRIP001      }
//STRIP001  } else {
//STRIP001      switch (eKind) {
//STRIP001          case OBJ_CIRC: nID=STR_ObjNameSingulCIRCE; break;
//STRIP001          case OBJ_SECT: nID=STR_ObjNameSingulSECTE; break;
//STRIP001          case OBJ_CARC: nID=STR_ObjNameSingulCARCE; break;
//STRIP001          case OBJ_CCUT: nID=STR_ObjNameSingulCCUTE; break;
//STRIP001      }
//STRIP001  }
//STRIP001  rName=ImpGetResStr(nID);
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

//STRIP001 void SdrCircObj::TakeObjNamePlural(XubString& rName) const
//STRIP001 {
//STRIP001  USHORT nID=STR_ObjNamePluralCIRC;
//STRIP001  if (aRect.GetWidth()==aRect.GetHeight() && aGeo.nShearWink==0) {
//STRIP001      switch (eKind) {
//STRIP001          case OBJ_CIRC: nID=STR_ObjNamePluralCIRC; break;
//STRIP001          case OBJ_SECT: nID=STR_ObjNamePluralSECT; break;
//STRIP001          case OBJ_CARC: nID=STR_ObjNamePluralCARC; break;
//STRIP001          case OBJ_CCUT: nID=STR_ObjNamePluralCCUT; break;
//STRIP001      }
//STRIP001  } else {
//STRIP001      switch (eKind) {
//STRIP001          case OBJ_CIRC: nID=STR_ObjNamePluralCIRCE; break;
//STRIP001          case OBJ_SECT: nID=STR_ObjNamePluralSECTE; break;
//STRIP001          case OBJ_CARC: nID=STR_ObjNamePluralCARCE; break;
//STRIP001          case OBJ_CCUT: nID=STR_ObjNamePluralCCUTE; break;
//STRIP001      }
//STRIP001  }
//STRIP001  rName=ImpGetResStr(nID);
//STRIP001 }

/*N*/ void SdrCircObj::operator=(const SdrObject& rObj)
/*N*/ {
/*N*/   SdrRectObj::operator=(rObj);
/*N*/
/*N*/   nStartWink = ((SdrCircObj&)rObj).nStartWink;
/*N*/   nEndWink = ((SdrCircObj&)rObj).nEndWink;
/*N*/   aPnt1 = ((SdrCircObj&)rObj).aPnt1;
/*N*/   aPnt2 = ((SdrCircObj&)rObj).aPnt2;
/*N*/ }

/*N*/ void SdrCircObj::TakeXorPoly(XPolyPolygon& rPoly, FASTBOOL bDetail) const
/*N*/ {
/*N*/   XPolygon aP(ImpCalcXPoly(aRect,nStartWink,nEndWink));
/*N*/   if (!bXPolyIsLine) { // Polygon schliessen
/*N*/       USHORT n=aP.GetPointCount();
/*N*/       Point aPnt(aP[0]);
/*N*/       aP[n]=aPnt;
/*N*/   }
/*N*/   rPoly=XPolyPolygon(aP);
/*N*/ }

/*N*/ void SdrCircObj::TakeContour(XPolyPolygon& rPoly) const
/*N*/ {
/*N*/   // am 14.1.97 wg. Umstellung TakeContour ueber Mtf und Paint. Joe.
/*N*/   SdrRectObj::TakeContour(rPoly);
/*N*/ }

//STRIP001 void SdrCircObj::TakeContour(XPolyPolygon& rXPoly, SdrContourType eType) const
//STRIP001 {
//STRIP001 }

//STRIP001 class ImpCircUser
//STRIP001 {
//STRIP001 public:
//STRIP001  Rectangle                   aR;
//STRIP001  Point                       aCenter;
//STRIP001  Point                       aRadius;
//STRIP001  Point                       aP1;
//STRIP001  Point                       aP2;
//STRIP001  long                        nMaxRad;
//STRIP001  long                        nHgt;
//STRIP001  long                        nWdt;
//STRIP001  long                        nStart;
//STRIP001  long                        nEnd;
//STRIP001  FASTBOOL                    bRight; // noch nicht implementiert
//STRIP001
//STRIP001 public:
//STRIP001  ImpCircUser()
//STRIP001  :   nMaxRad(0),
//STRIP001      nHgt(0),
//STRIP001      nWdt(0),
//STRIP001      nStart(0),
//STRIP001      nEnd(0),
//STRIP001      bRight(FALSE)
//STRIP001  {}
//STRIP001  void SetCreateParams(SdrDragStat& rStat);
//STRIP001 };

//STRIP001 USHORT SdrCircObj::GetHdlCount() const
//STRIP001 {
//STRIP001  if (eKind!=OBJ_CIRC) {
//STRIP001      return 10;
//STRIP001  } else {
//STRIP001      return 8;
//STRIP001  }
//STRIP001 }

//STRIP001 SdrHdl* SdrCircObj::GetHdl(USHORT nHdlNum) const
//STRIP001 {
//STRIP001  if (eKind==OBJ_CIRC) nHdlNum+=2; // Keine Winkelhandles fuer den Vollkreis
//STRIP001  SdrHdl* pH=NULL;
//STRIP001  Point aPnt;
//STRIP001  SdrHdlKind eKind=HDL_MOVE;
//STRIP001  USHORT nPNum=0;
//STRIP001  switch (nHdlNum) {
//STRIP001      case 0: aPnt=aPnt1; eKind=HDL_CIRC; nPNum=1; break; // StartWink
//STRIP001      case 1: aPnt=aPnt2; eKind=HDL_CIRC; nPNum=2; break; // EndWink
//STRIP001      case 2: aPnt=aRect.TopLeft();      eKind=HDL_UPLFT; break; // Oben links
//STRIP001      case 3: aPnt=aRect.TopCenter();    eKind=HDL_UPPER; break; // Oben
//STRIP001      case 4: aPnt=aRect.TopRight();     eKind=HDL_UPRGT; break; // Oben rechts
//STRIP001      case 5: aPnt=aRect.LeftCenter();   eKind=HDL_LEFT ; break; // Links
//STRIP001      case 6: aPnt=aRect.RightCenter();  eKind=HDL_RIGHT; break; // Rechts
//STRIP001      case 7: aPnt=aRect.BottomLeft();   eKind=HDL_LWLFT; break; // Unten links
//STRIP001      case 8: aPnt=aRect.BottomCenter(); eKind=HDL_LOWER; break; // Unten
//STRIP001      case 9: aPnt=aRect.BottomRight();  eKind=HDL_LWRGT; break; // Unten rechts
//STRIP001  }
//STRIP001  if (aGeo.nShearWink!=0) ShearPoint(aPnt,aRect.TopLeft(),aGeo.nTan);
//STRIP001  if (aGeo.nDrehWink!=0) RotatePoint(aPnt,aRect.TopLeft(),aGeo.nSin,aGeo.nCos);
//STRIP001  if (eKind!=HDL_MOVE) {
//STRIP001      pH=new SdrHdl(aPnt,eKind);
//STRIP001      pH->SetPointNum(nPNum);
//STRIP001      pH->SetObj((SdrObject*)this);
//STRIP001      pH->SetDrehWink(aGeo.nDrehWink);
//STRIP001  }
//STRIP001  return pH;
//STRIP001 }

//STRIP001 FASTBOOL SdrCircObj::HasSpecialDrag() const
//STRIP001 {
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 FASTBOOL SdrCircObj::BegDrag(SdrDragStat& rDrag) const
//STRIP001 {
//STRIP001  FASTBOOL bWink=rDrag.GetHdl()!=NULL && rDrag.GetHdl()->GetKind()==HDL_CIRC;
//STRIP001  FASTBOOL bOk=bWink;
//STRIP001  if (bWink) {
//STRIP001      long* pWink=new long;
//STRIP001      *pWink=0;
//STRIP001      rDrag.SetUser(pWink);
//STRIP001      if (rDrag.GetHdl()->GetPointNum()==1 || rDrag.GetHdl()->GetPointNum()==2) {
//STRIP001          rDrag.SetNoSnap(TRUE);
//STRIP001      }
//STRIP001  } else {
//STRIP001      bOk=SdrTextObj::BegDrag(rDrag);
//STRIP001  }
//STRIP001  return bOk;
//STRIP001 }

//STRIP001 FASTBOOL SdrCircObj::MovDrag(SdrDragStat& rDrag) const
//STRIP001 {
//STRIP001  FASTBOOL bWink=rDrag.GetHdl()!=NULL && rDrag.GetHdl()->GetKind()==HDL_CIRC;
//STRIP001  if (bWink) {
//STRIP001      Point aPt(rDrag.GetNow());
//STRIP001      // Unrotate:
//STRIP001      if (aGeo.nDrehWink!=0) RotatePoint(aPt,aRect.TopLeft(),-aGeo.nSin,aGeo.nCos); // -sin fuer Umkehrung
//STRIP001      // Unshear:
//STRIP001      if (aGeo.nShearWink!=0) ShearPoint(aPt,aRect.TopLeft(),-aGeo.nTan); // -tan fuer Umkehrung
//STRIP001      aPt-=aRect.Center();
//STRIP001      long nWdt=aRect.Right()-aRect.Left();
//STRIP001      long nHgt=aRect.Bottom()-aRect.Top();
//STRIP001      if (nWdt>=nHgt) {
//STRIP001          aPt.Y()=BigMulDiv(aPt.Y(),nWdt,nHgt);
//STRIP001      } else {
//STRIP001          aPt.X()=BigMulDiv(aPt.X(),nHgt,nWdt);
//STRIP001      }
//STRIP001      long nWink=NormAngle360(GetAngle(aPt));
//STRIP001      if (rDrag.GetView()!=NULL && rDrag.GetView()->IsAngleSnapEnabled()) {
//STRIP001          long nSA=rDrag.GetView()->GetSnapAngle();
//STRIP001          if (nSA!=0) { // Winkelfang
//STRIP001              nWink+=nSA/2;
//STRIP001              nWink/=nSA;
//STRIP001              nWink*=nSA;
//STRIP001              nWink=NormAngle360(nWink);
//STRIP001          }
//STRIP001      }
//STRIP001      long* pWink=(long*)(rDrag.GetUser());
//STRIP001      if (*pWink!=nWink) {
//STRIP001          *pWink=nWink;
//STRIP001          return TRUE;
//STRIP001      } else {
//STRIP001          return FALSE;
//STRIP001      }
//STRIP001  } else {
//STRIP001      return SdrTextObj::MovDrag(rDrag);
//STRIP001  }
//STRIP001 }

//STRIP001 FASTBOOL SdrCircObj::EndDrag(SdrDragStat& rDrag)
//STRIP001 {
//STRIP001  FASTBOOL bWink=rDrag.GetHdl()!=NULL && rDrag.GetHdl()->GetKind()==HDL_CIRC;
//STRIP001  if (bWink) {
//STRIP001      Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001      SendRepaintBroadcast();
//STRIP001      long nWink=*((long*)(rDrag.GetUser()));
//STRIP001      if (rDrag.GetHdl()->GetPointNum()==1) nStartWink=nWink;
//STRIP001      if (rDrag.GetHdl()->GetPointNum()==2) nEndWink=nWink;
//STRIP001      SetRectsDirty();
//STRIP001      SetXPolyDirty();
//STRIP001      ImpSetCircInfoToAttr();
//STRIP001      SetChanged();
//STRIP001      SendRepaintBroadcast();
//STRIP001      SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001      return TRUE;
//STRIP001  } else {
//STRIP001      return SdrTextObj::EndDrag(rDrag);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrCircObj::BrkDrag(SdrDragStat& rDrag) const
//STRIP001 {
//STRIP001  SdrTextObj::BrkDrag(rDrag);
//STRIP001 }

//STRIP001 XubString SdrCircObj::GetDragComment(const SdrDragStat& rDrag, FASTBOOL bUndoDragComment, FASTBOOL bCreateComment) const
//STRIP001 {
//STRIP001  if(bCreateComment)
//STRIP001  {
//STRIP001      XubString aStr;
//STRIP001      ImpTakeDescriptionStr(STR_ViewCreateObj, aStr);
//STRIP001      UINT32 nPntAnz(rDrag.GetPointAnz());
//STRIP001
//STRIP001      if(eKind != OBJ_CIRC && nPntAnz > 2)
//STRIP001      {
//STRIP001          ImpCircUser* pU = (ImpCircUser*)rDrag.GetUser();
//STRIP001          INT32 nWink;
//STRIP001
//STRIP001          aStr.AppendAscii(" (");
//STRIP001
//STRIP001          if(nPntAnz == 3)
//STRIP001              nWink = pU->nStart;
//STRIP001          else
//STRIP001              nWink = pU->nEnd;
//STRIP001
//STRIP001          aStr += GetWinkStr(nWink,FALSE);
//STRIP001          aStr += sal_Unicode(')');
//STRIP001      }
//STRIP001      return aStr;
//STRIP001  }
//STRIP001
//STRIP001  BOOL bWink(rDrag.GetHdl() && rDrag.GetHdl()->GetKind() == HDL_CIRC);
//STRIP001
//STRIP001  if(bWink)
//STRIP001  {
//STRIP001      XubString aStr;
//STRIP001      INT32 nWink(*((long*)(rDrag.GetUser())));
//STRIP001
//STRIP001      ImpTakeDescriptionStr(STR_DragCircAngle, aStr);
//STRIP001      aStr.AppendAscii(" (");
//STRIP001      aStr += GetWinkStr(nWink,FALSE);
//STRIP001      aStr += sal_Unicode(')');
//STRIP001
//STRIP001      return aStr;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      return SdrTextObj::GetDragComment(rDrag, bUndoDragComment, FALSE);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrCircObj::TakeDragPoly(const SdrDragStat& rDrag, XPolyPolygon& rXPP) const
//STRIP001 {
//STRIP001  rXPP.Clear();
//STRIP001  FASTBOOL bWink=rDrag.GetHdl()!=NULL && rDrag.GetHdl()->GetKind()==HDL_CIRC;
//STRIP001  long a=nStartWink;
//STRIP001  long e=nEndWink;
//STRIP001  if (bWink) {
//STRIP001      long nWink=*((long*)(rDrag.GetUser()));
//STRIP001      if (rDrag.GetHdl()->GetPointNum()==1) a=nWink;
//STRIP001      else e=nWink;
//STRIP001  }
//STRIP001  Rectangle aTmpRect(bWink ? aRect : ImpDragCalcRect(rDrag));
//STRIP001  XPolygon aXP(ImpCalcXPoly(aTmpRect,a,e));
//STRIP001  if (!bXPolyIsLine) { // Polygon schliessen
//STRIP001      USHORT n=aXP.GetPointCount();
//STRIP001      Point aPnt(aXP[0]);
//STRIP001      aXP[n]=aPnt;
//STRIP001  }
//STRIP001  rXPP.Insert(aXP);
//STRIP001 }

//STRIP001 void ImpCircUser::SetCreateParams(SdrDragStat& rStat)
//STRIP001 {
//STRIP001  rStat.TakeCreateRect(aR);
//STRIP001  aR.Justify();
//STRIP001  aCenter=aR.Center();
//STRIP001  nWdt=aR.Right()-aR.Left();
//STRIP001  nHgt=aR.Bottom()-aR.Top();
//STRIP001  nMaxRad=((nWdt>nHgt ? nWdt : nHgt)+1) /2;
//STRIP001  nStart=0;
//STRIP001  nEnd=36000;
//STRIP001  if (rStat.GetPointAnz()>2) {
//STRIP001      Point aP(rStat.GetPoint(2)-aCenter);
//STRIP001      if (nWdt==0) aP.X()=0;
//STRIP001      if (nHgt==0) aP.Y()=0;
//STRIP001      if (nWdt>=nHgt) {
//STRIP001          if (nHgt!=0) aP.Y()=aP.Y()*nWdt/nHgt;
//STRIP001      } else {
//STRIP001          if (nWdt!=0) aP.X()=aP.X()*nHgt/nWdt;
//STRIP001      }
//STRIP001      nStart=NormAngle360(GetAngle(aP));
//STRIP001      if (rStat.GetView()!=NULL && rStat.GetView()->IsAngleSnapEnabled()) {
//STRIP001          long nSA=rStat.GetView()->GetSnapAngle();
//STRIP001          if (nSA!=0) { // Winkelfang
//STRIP001              nStart+=nSA/2;
//STRIP001              nStart/=nSA;
//STRIP001              nStart*=nSA;
//STRIP001              nStart=NormAngle360(nStart);
//STRIP001          }
//STRIP001      }
//STRIP001      SetWinkPnt(aR,nStart,aP1);
//STRIP001      nEnd=nStart;
//STRIP001      aP2=aP1;
//STRIP001  } else aP1=aCenter;
//STRIP001  if (rStat.GetPointAnz()>3) {
//STRIP001      Point aP(rStat.GetPoint(3)-aCenter);
//STRIP001      if (nWdt>=nHgt) {
//STRIP001          aP.Y()=BigMulDiv(aP.Y(),nWdt,nHgt);
//STRIP001      } else {
//STRIP001          aP.X()=BigMulDiv(aP.X(),nHgt,nWdt);
//STRIP001      }
//STRIP001      nEnd=NormAngle360(GetAngle(aP));
//STRIP001      if (rStat.GetView()!=NULL && rStat.GetView()->IsAngleSnapEnabled()) {
//STRIP001          long nSA=rStat.GetView()->GetSnapAngle();
//STRIP001          if (nSA!=0) { // Winkelfang
//STRIP001              nEnd+=nSA/2;
//STRIP001              nEnd/=nSA;
//STRIP001              nEnd*=nSA;
//STRIP001              nEnd=NormAngle360(nEnd);
//STRIP001          }
//STRIP001      }
//STRIP001      SetWinkPnt(aR,nEnd,aP2);
//STRIP001  } else aP2=aCenter;
//STRIP001 }

//STRIP001 void SdrCircObj::ImpSetCreateParams(SdrDragStat& rStat) const
//STRIP001 {
//STRIP001  ImpCircUser* pU=(ImpCircUser*)rStat.GetUser();
//STRIP001  if (pU==NULL) {
//STRIP001      pU=new ImpCircUser;
//STRIP001      rStat.SetUser(pU);
//STRIP001  }
//STRIP001  pU->SetCreateParams(rStat);
//STRIP001 }

//STRIP001 FASTBOOL SdrCircObj::BegCreate(SdrDragStat& rStat)
//STRIP001 {
//STRIP001  rStat.SetOrtho4Possible();
//STRIP001  ImpSetCreateParams(rStat);
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 FASTBOOL SdrCircObj::MovCreate(SdrDragStat& rStat)
//STRIP001 {
//STRIP001  ImpSetCreateParams(rStat);
//STRIP001  ImpCircUser* pU=(ImpCircUser*)rStat.GetUser();
//STRIP001  rStat.SetActionRect(pU->aR);
//STRIP001  aRect=pU->aR; // fuer ObjName
//STRIP001  ImpJustifyRect(aRect);
//STRIP001  nStartWink=pU->nStart;
//STRIP001  nEndWink=pU->nEnd;
//STRIP001  bBoundRectDirty=TRUE;
//STRIP001  bSnapRectDirty=TRUE;
//STRIP001  SetXPolyDirty();
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 FASTBOOL SdrCircObj::EndCreate(SdrDragStat& rStat, SdrCreateCmd eCmd)
//STRIP001 {
//STRIP001  ImpSetCreateParams(rStat);
//STRIP001  ImpCircUser* pU=(ImpCircUser*)rStat.GetUser();
//STRIP001  FASTBOOL bRet=FALSE;
//STRIP001  if (eCmd==SDRCREATE_FORCEEND && rStat.GetPointAnz()<4) eKind=OBJ_CIRC;
//STRIP001  if (eKind==OBJ_CIRC) {
//STRIP001      bRet=rStat.GetPointAnz()>=2;
//STRIP001      if (bRet) {
//STRIP001          aRect=pU->aR;
//STRIP001          ImpJustifyRect(aRect);
//STRIP001      }
//STRIP001  } else {
//STRIP001      rStat.SetNoSnap(rStat.GetPointAnz()>=2);
//STRIP001      rStat.SetOrtho4Possible(rStat.GetPointAnz()<2);
//STRIP001      bRet=rStat.GetPointAnz()>=4;
//STRIP001      if (bRet) {
//STRIP001          aRect=pU->aR;
//STRIP001          ImpJustifyRect(aRect);
//STRIP001          nStartWink=pU->nStart;
//STRIP001          nEndWink=pU->nEnd;
//STRIP001      }
//STRIP001  }
//STRIP001  bClosedObj=eKind!=OBJ_CARC;
//STRIP001  SetRectsDirty();
//STRIP001  SetXPolyDirty();
//STRIP001  ImpSetCircInfoToAttr();
//STRIP001  if (bRet) {
//STRIP001      delete pU;
//STRIP001      rStat.SetUser(NULL);
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 void SdrCircObj::BrkCreate(SdrDragStat& rStat)
//STRIP001 {
//STRIP001  ImpCircUser* pU=(ImpCircUser*)rStat.GetUser();
//STRIP001  delete pU;
//STRIP001  rStat.SetUser(NULL);
//STRIP001 }

//STRIP001 FASTBOOL SdrCircObj::BckCreate(SdrDragStat& rStat)
//STRIP001 {
//STRIP001  rStat.SetNoSnap(rStat.GetPointAnz()>=3);
//STRIP001  rStat.SetOrtho4Possible(rStat.GetPointAnz()<3);
//STRIP001  return eKind!=OBJ_CIRC;
//STRIP001 }

//STRIP001 void SdrCircObj::TakeCreatePoly(const SdrDragStat& rDrag, XPolyPolygon& rXPP) const
//STRIP001 {
//STRIP001  rXPP.Clear();
//STRIP001  ImpCircUser* pU=(ImpCircUser*)rDrag.GetUser();
//STRIP001  if (eKind==OBJ_CIRC || rDrag.GetPointAnz()<4) {
//STRIP001      rXPP.Insert(XPolygon(pU->aCenter,pU->aR.GetWidth()/2,pU->aR.GetHeight()/2));
//STRIP001      if (rDrag.GetPointAnz()==3) {
//STRIP001          XPolygon aXP(2);
//STRIP001          aXP[0]=pU->aCenter;
//STRIP001          aXP[1]=pU->aP1;
//STRIP001          rXPP.Insert(aXP);
//STRIP001      }
//STRIP001  } else {
//STRIP001      XPolygon aXP(ImpCalcXPoly(pU->aR,pU->nStart,pU->nEnd));
//STRIP001      if (!bXPolyIsLine) { // Polygon schliessen
//STRIP001          USHORT n=aXP.GetPointCount();
//STRIP001          Point aPnt(aXP[0]);
//STRIP001          aXP[n]=aPnt;
//STRIP001      }
//STRIP001      rXPP.Insert(aXP);
//STRIP001  }
//STRIP001 }

//STRIP001 Pointer SdrCircObj::GetCreatePointer() const
//STRIP001 {
//STRIP001  switch (eKind) {
//STRIP001      case OBJ_CIRC: return Pointer(POINTER_DRAW_ELLIPSE);
//STRIP001      case OBJ_SECT: return Pointer(POINTER_DRAW_PIE);
//STRIP001      case OBJ_CARC: return Pointer(POINTER_DRAW_ARC);
//STRIP001      case OBJ_CCUT: return Pointer(POINTER_DRAW_CIRCLECUT);
//STRIP001  } // switch
//STRIP001  return Pointer(POINTER_CROSS);
//STRIP001 }

/*N*/ void SdrCircObj::NbcMove(const Size& aSiz)
/*N*/ {
/*N*/   MoveRect(aRect,aSiz);
/*N*/   MoveRect(aOutRect,aSiz);
/*N*/   MoveRect(maSnapRect,aSiz);
/*N*/   MovePoint(aPnt1,aSiz);
/*N*/   MovePoint(aPnt2,aSiz);
/*N*/   SetXPolyDirty();
/*N*/   SetRectsDirty(TRUE);
/*N*/ }

/*N*/ void SdrCircObj::NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact)
/*N*/ {
/*N*/   long nWink0=aGeo.nDrehWink;
/*N*/   FASTBOOL bNoShearRota=(aGeo.nDrehWink==0 && aGeo.nShearWink==0);
/*N*/   SdrTextObj::NbcResize(rRef,xFact,yFact);
/*N*/   bNoShearRota|=(aGeo.nDrehWink==0 && aGeo.nShearWink==0);
/*N*/   if (eKind!=OBJ_CIRC) {
/*N*/       FASTBOOL bXMirr=(xFact.GetNumerator()<0) != (xFact.GetDenominator()<0);
/*N*/       FASTBOOL bYMirr=(yFact.GetNumerator()<0) != (yFact.GetDenominator()<0);
/*N*/       if (bXMirr || bYMirr) {
/*N*/           // bei bXMirr!=bYMirr muessten eigentlich noch die beiden
/*N*/           // Linienende vertauscht werden. Das ist jedoch mal wieder
/*N*/           // schlecht (wg. zwangslaeufiger harter Formatierung).
/*N*/           // Alternativ koennte ein bMirrored-Flag eingefuehrt werden
/*N*/           // (Vielleicht ja mal grundsaetzlich, auch fuer gepiegelten Text, ...).
/*N*/           long nS0=nStartWink;
/*N*/           long nE0=nEndWink;
/*N*/           if (bNoShearRota) {
/*N*/               // Das RectObj spiegelt bei VMirror bereits durch durch 180deg Drehung.
/*N*/               if (! (bXMirr && bYMirr)) {
/*N*/                   long nTmp=nS0;
/*N*/                   nS0=18000-nE0;
/*N*/                   nE0=18000-nTmp;
/*N*/               }
/*N*/           } else { // Spiegeln fuer verzerrte Ellipsen
/*N*/               if (bXMirr!=bYMirr) {
/*N*/                   nS0+=nWink0;
/*N*/                   nE0+=nWink0;
/*N*/                   if (bXMirr) {
/*N*/                       long nTmp=nS0;
/*N*/                       nS0=18000-nE0;
/*N*/                       nE0=18000-nTmp;
/*N*/                   }
/*N*/                   if (bYMirr) {
/*N*/                       long nTmp=nS0;
/*N*/                       nS0=-nE0;
/*N*/                       nE0=-nTmp;
/*N*/                   }
/*N*/                   nS0-=aGeo.nDrehWink;
/*N*/                   nE0-=aGeo.nDrehWink;
/*N*/               }
/*N*/           }
/*N*/           long nWinkDif=nE0-nS0;
/*N*/           nStartWink=NormAngle360(nS0);
/*N*/           nEndWink  =NormAngle360(nE0);
/*N*/           if (nWinkDif==36000) nEndWink+=nWinkDif; // Vollkreis
/*N*/       }
/*N*/   }
/*N*/   SetXPolyDirty();
/*N*/   ImpSetCircInfoToAttr();
/*N*/ }

/*N*/ void SdrCircObj::NbcShear(const Point& rRef, long nWink, double tn, FASTBOOL bVShear)
/*N*/ {
/*N*/   SdrTextObj::NbcShear(rRef,nWink,tn,bVShear);
/*N*/   SetXPolyDirty();
/*N*/   ImpSetCircInfoToAttr();
/*N*/ }

//STRIP001 void SdrCircObj::NbcMirror(const Point& rRef1, const Point& rRef2)
//STRIP001 {
//STRIP001  long nWink0=aGeo.nDrehWink;
//STRIP001  FASTBOOL bFreeMirr=eKind!=OBJ_CIRC;
//STRIP001  Point aTmpPt1;
//STRIP001  Point aTmpPt2;
//STRIP001  if (bFreeMirr) { // bei freier Spiegelachse einige Vorbereitungen Treffen
//STRIP001      Point aCenter(aRect.Center());
//STRIP001      long nWdt=aRect.GetWidth()-1;
//STRIP001      long nHgt=aRect.GetHeight()-1;
//STRIP001      long nMaxRad=((nWdt>nHgt ? nWdt : nHgt)+1) /2;
//STRIP001      double a;
//STRIP001      // Startpunkt
//STRIP001      a=nStartWink*nPi180;
//STRIP001      aTmpPt1=Point(Round(cos(a)*nMaxRad),-Round(sin(a)*nMaxRad));
//STRIP001      if (nWdt==0) aTmpPt1.X()=0;
//STRIP001      if (nHgt==0) aTmpPt1.Y()=0;
//STRIP001      aTmpPt1+=aCenter;
//STRIP001      // Endpunkt
//STRIP001      a=nEndWink*nPi180;
//STRIP001      aTmpPt2=Point(Round(cos(a)*nMaxRad),-Round(sin(a)*nMaxRad));
//STRIP001      if (nWdt==0) aTmpPt2.X()=0;
//STRIP001      if (nHgt==0) aTmpPt2.Y()=0;
//STRIP001      aTmpPt2+=aCenter;
//STRIP001      if (aGeo.nDrehWink!=0) {
//STRIP001          RotatePoint(aTmpPt1,aRect.TopLeft(),aGeo.nSin,aGeo.nCos);
//STRIP001          RotatePoint(aTmpPt2,aRect.TopLeft(),aGeo.nSin,aGeo.nCos);
//STRIP001      }
//STRIP001      if (aGeo.nShearWink!=0) {
//STRIP001          ShearPoint(aTmpPt1,aRect.TopLeft(),aGeo.nTan);
//STRIP001          ShearPoint(aTmpPt2,aRect.TopLeft(),aGeo.nTan);
//STRIP001      }
//STRIP001  }
//STRIP001  SdrTextObj::NbcMirror(rRef1,rRef2);
//STRIP001  if (eKind!=OBJ_CIRC) { // Anpassung von Start- und Endwinkel
//STRIP001      MirrorPoint(aTmpPt1,rRef1,rRef2);
//STRIP001      MirrorPoint(aTmpPt2,rRef1,rRef2);
//STRIP001      // Unrotate:
//STRIP001      if (aGeo.nDrehWink!=0) {
//STRIP001          RotatePoint(aTmpPt1,aRect.TopLeft(),-aGeo.nSin,aGeo.nCos); // -sin fuer Umkehrung
//STRIP001          RotatePoint(aTmpPt2,aRect.TopLeft(),-aGeo.nSin,aGeo.nCos); // -sin fuer Umkehrung
//STRIP001      }
//STRIP001      // Unshear:
//STRIP001      if (aGeo.nShearWink!=0) {
//STRIP001          ShearPoint(aTmpPt1,aRect.TopLeft(),-aGeo.nTan); // -tan fuer Umkehrung
//STRIP001          ShearPoint(aTmpPt2,aRect.TopLeft(),-aGeo.nTan); // -tan fuer Umkehrung
//STRIP001      }
//STRIP001      Point aCenter(aRect.Center());
//STRIP001      aTmpPt1-=aCenter;
//STRIP001      aTmpPt2-=aCenter;
//STRIP001      // Weil gespiegelt sind die Winkel nun auch noch vertauscht
//STRIP001      nStartWink=GetAngle(aTmpPt2);
//STRIP001      nEndWink  =GetAngle(aTmpPt1);
//STRIP001      long nWinkDif=nEndWink-nStartWink;
//STRIP001      nStartWink=NormAngle360(nStartWink);
//STRIP001      nEndWink  =NormAngle360(nEndWink);
//STRIP001      if (nWinkDif==36000) nEndWink+=nWinkDif; // Vollkreis
//STRIP001  }
//STRIP001  SetXPolyDirty();
//STRIP001  ImpSetCircInfoToAttr();
//STRIP001 }

//STRIP001 SdrObjGeoData* SdrCircObj::NewGeoData() const
//STRIP001 {
//STRIP001  return new SdrCircObjGeoData;
//STRIP001 }

//STRIP001 void SdrCircObj::SaveGeoData(SdrObjGeoData& rGeo) const
//STRIP001 {
//STRIP001  SdrRectObj::SaveGeoData(rGeo);
//STRIP001  SdrCircObjGeoData& rCGeo=(SdrCircObjGeoData&)rGeo;
//STRIP001  rCGeo.nStartWink=nStartWink;
//STRIP001  rCGeo.nEndWink  =nEndWink;
//STRIP001 }

//STRIP001 void SdrCircObj::RestGeoData(const SdrObjGeoData& rGeo)
//STRIP001 {
//STRIP001  SdrRectObj::RestGeoData(rGeo);
//STRIP001  SdrCircObjGeoData& rCGeo=(SdrCircObjGeoData&)rGeo;
//STRIP001  nStartWink=rCGeo.nStartWink;
//STRIP001  nEndWink  =rCGeo.nEndWink;
//STRIP001  SetXPolyDirty();
//STRIP001  ImpSetCircInfoToAttr();
//STRIP001 }

/*N*/ void Union(Rectangle& rR, const Point& rP)
/*N*/ {
/*N*/   if (rP.X()<rR.Left  ()) rR.Left  ()=rP.X();
/*N*/   if (rP.X()>rR.Right ()) rR.Right ()=rP.X();
/*N*/   if (rP.Y()<rR.Top   ()) rR.Top   ()=rP.Y();
/*N*/   if (rP.Y()>rR.Bottom()) rR.Bottom()=rP.Y();
/*N*/ }

/*N*/ void SdrCircObj::TakeUnrotatedSnapRect(Rectangle& rRect) const
/*N*/ {
/*N*/   rRect=aRect;
/*N*/   if (eKind!=OBJ_CIRC) {
/*N*/       SetWinkPnt(rRect,nStartWink,((SdrCircObj*)(this))->aPnt1);
/*N*/       SetWinkPnt(rRect,nEndWink  ,((SdrCircObj*)(this))->aPnt2);
/*N*/       long a=nStartWink;
/*N*/       long e=nEndWink;
/*N*/       rRect.Left  ()=aRect.Right();
/*N*/       rRect.Right ()=aRect.Left();
/*N*/       rRect.Top   ()=aRect.Bottom();
/*N*/       rRect.Bottom()=aRect.Top();
/*N*/       Union(rRect,aPnt1);
/*N*/       Union(rRect,aPnt2);
/*N*/       if ((a<=18000 && e>=18000) || (a>e && (a<=18000 || e>=18000))) {
/*N*/           Union(rRect,aRect.LeftCenter());
/*N*/       }
/*N*/       if ((a<=27000 && e>=27000) || (a>e && (a<=27000 || e>=27000))) {
/*N*/           Union(rRect,aRect.BottomCenter());
/*N*/       }
/*N*/       if (a>e) {
/*N*/           Union(rRect,aRect.RightCenter());
/*N*/       }
/*N*/       if ((a<=9000 && e>=9000) || (a>e && (a<=9000 || e>=9000))) {
/*N*/           Union(rRect,aRect.TopCenter());
/*N*/       }
/*N*/       if (eKind==OBJ_SECT) {
/*N*/           Union(rRect,aRect.Center());
/*N*/       }
/*N*/       if (aGeo.nDrehWink!=0) {
/*?*/           Point aDst(rRect.TopLeft());
/*?*/           aDst-=aRect.TopLeft();
/*?*/           Point aDst0(aDst);
/*?*/           RotatePoint(aDst,Point(),aGeo.nSin,aGeo.nCos);
/*?*/           aDst-=aDst0;
/*?*/           rRect.Move(aDst.X(),aDst.Y());
/*N*/       }
/*N*/   }
/*N*/   if (aGeo.nShearWink!=0) {
/*N*/       long nDst=Round((rRect.Bottom()-rRect.Top())*aGeo.nTan);
/*N*/       if (aGeo.nShearWink>0) {
/*?*/           Point aRef(rRect.TopLeft());
/*?*/           rRect.Left()-=nDst;
/*?*/           Point aTmpPt(rRect.TopLeft());
/*?*/           RotatePoint(aTmpPt,aRef,aGeo.nSin,aGeo.nCos);
/*?*/           aTmpPt-=rRect.TopLeft();
/*?*/           rRect.Move(aTmpPt.X(),aTmpPt.Y());
/*?*/       } else {
/*?*/           rRect.Right()-=nDst;
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void SdrCircObj::RecalcSnapRect()
/*N*/ {
/*N*/   if (PaintNeedsXPoly()) {
/*N*/       maSnapRect=GetXPoly().GetBoundRect();
/*N*/   } else {
/*N*/       TakeUnrotatedSnapRect(maSnapRect);
/*N*/   }
/*N*/ }

/*N*/ void SdrCircObj::NbcSetSnapRect(const Rectangle& rRect)
/*N*/ {
/*N*/   if (aGeo.nDrehWink!=0 || aGeo.nShearWink!=0 || eKind!=OBJ_CIRC) {
/*?*/       Rectangle aSR0(GetSnapRect());
/*?*/       long nWdt0=aSR0.Right()-aSR0.Left();
/*?*/       long nHgt0=aSR0.Bottom()-aSR0.Top();
/*?*/       long nWdt1=rRect.Right()-rRect.Left();
/*?*/       long nHgt1=rRect.Bottom()-rRect.Top();
/*?*/       NbcResize(maSnapRect.TopLeft(),Fraction(nWdt1,nWdt0),Fraction(nHgt1,nHgt0));
/*?*/       NbcMove(Size(rRect.Left()-aSR0.Left(),rRect.Top()-aSR0.Top()));
/*N*/   } else {
/*N*/       aRect=rRect;
/*N*/       ImpJustifyRect(aRect);
/*N*/   }
/*N*/   SetRectsDirty();
/*N*/   SetXPolyDirty();
/*N*/   ImpSetCircInfoToAttr();
/*N*/ }

//STRIP001 USHORT SdrCircObj::GetSnapPointCount() const
//STRIP001 {
//STRIP001  if (eKind==OBJ_CIRC) {
//STRIP001      return 1;
//STRIP001  } else {
//STRIP001      return 3;
//STRIP001  }
//STRIP001 }

//STRIP001 Point SdrCircObj::GetSnapPoint(USHORT i) const
//STRIP001 {
//STRIP001  switch (i) {
//STRIP001      case 1 : return aPnt1;
//STRIP001      case 2 : return aPnt2;
//STRIP001      default: return aRect.Center();
//STRIP001  }
//STRIP001 }

/*N*/ void __EXPORT SdrCircObj::SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType)
/*N*/ {
/*N*/   SetXPolyDirty();
/*N*/   SdrRectObj::SFX_NOTIFY(rBC,rBCType,rHint,rHintType);
/*N*/   ImpSetAttrToCircInfo();
/*N*/ }

/*N*/ void SdrCircObj::ForceDefaultAttr()
/*N*/ {
/*N*/   SdrCircKind eKindA = SDRCIRC_FULL;
/*N*/
/*N*/   if(eKind == OBJ_SECT)
/*N*/       eKindA = SDRCIRC_SECT;
/*N*/   else if(eKind == OBJ_CARC)
/*N*/       eKindA = SDRCIRC_ARC;
/*N*/   else if(eKind == OBJ_CCUT)
/*N*/       eKindA = SDRCIRC_CUT;
/*N*/
/*N*/   if(eKindA != SDRCIRC_FULL)
/*N*/   {
/*N*/       ImpForceItemSet();
/*N*/       mpObjectItemSet->Put(SdrCircKindItem(eKindA));
/*N*/
/*N*/       if(nStartWink)
/*N*/           mpObjectItemSet->Put(SdrCircStartAngleItem(nStartWink));
/*N*/
/*N*/       if(nEndWink != 36000)
/*N*/           mpObjectItemSet->Put(SdrCircEndAngleItem(nEndWink));
/*N*/   }
/*N*/
/*N*/   // call parent, after SetItem(SdrCircKindItem())
/*N*/   // because ForceDefaultAttr() will call
/*N*/   // ImpSetAttrToCircInfo() which needs a correct
/*N*/   // SdrCircKindItem
/*N*/   SdrRectObj::ForceDefaultAttr();
/*N*/
/*N*/ }

/*N*/ void SdrCircObj::NbcSetStyleSheet(SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr)
/*N*/ {
/*N*/   SetXPolyDirty();
/*N*/   SdrRectObj::NbcSetStyleSheet(pNewStyleSheet,bDontRemoveHardAttr);
/*N*/   ImpSetAttrToCircInfo();
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// ItemSet access

/*N*/ SfxItemSet* SdrCircObj::CreateNewItemSet(SfxItemPool& rPool)
/*N*/ {
/*N*/   // include ALL items, 2D and 3D
/*N*/   return new SfxItemSet(rPool,
/*N*/       // ranges from SdrAttrObj
/*N*/       SDRATTR_START, SDRATTRSET_SHADOW,
/*N*/       SDRATTRSET_OUTLINER, SDRATTRSET_MISC,
/*N*/       SDRATTR_TEXTDIRECTION, SDRATTR_TEXTDIRECTION,
/*N*/
/*N*/       // circle attributes
/*N*/       SDRATTR_CIRC_FIRST, SDRATTRSET_CIRC,
/*N*/
/*N*/       // outliner and end
/*N*/       EE_ITEMS_START, EE_ITEMS_END,
/*N*/       0, 0);
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// private support routines for ItemSet access
/*N*/ void SdrCircObj::ItemSetChanged(const SfxItemSet& rSet)
/*N*/ {
/*N*/   // local changes
/*N*/   SetXPolyDirty();
/*N*/
/*N*/   // call parent
/*N*/   SdrRectObj::ItemSetChanged(rSet);
/*N*/
/*N*/   // local changes
/*N*/   ImpSetAttrToCircInfo();
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrCircObj::ImpSetAttrToCircInfo()
/*N*/ {
/*N*/   const SfxItemSet& rSet = GetItemSet();
/*N*/   SdrCircKind eNewKindA = ((SdrCircKindItem&)rSet.Get(SDRATTR_CIRCKIND)).GetValue();
/*N*/   SdrObjKind eNewKind = eKind;
/*N*/
/*N*/   if(eNewKindA == SDRCIRC_FULL)
/*N*/       eNewKind = OBJ_CIRC;
/*N*/   else if(eNewKindA == SDRCIRC_SECT)
/*N*/       eNewKind = OBJ_SECT;
/*N*/   else if(eNewKindA == SDRCIRC_ARC)
/*N*/       eNewKind = OBJ_CARC;
/*N*/   else if(eNewKindA == SDRCIRC_CUT)
/*N*/       eNewKind = OBJ_CCUT;
/*N*/
/*N*/   sal_Int32 nNewStart = ((SdrCircStartAngleItem&)rSet.Get(SDRATTR_CIRCSTARTANGLE)).GetValue();
/*N*/   sal_Int32 nNewEnd = ((SdrCircEndAngleItem&)rSet.Get(SDRATTR_CIRCENDANGLE)).GetValue();
/*N*/
/*N*/   BOOL bKindChg = eKind != eNewKind;
/*N*/   BOOL bWinkChg = nNewStart != nStartWink || nNewEnd != nEndWink;
/*N*/
/*N*/   if(bKindChg || bWinkChg)
/*N*/   {
/*N*/       eKind = eNewKind;
/*N*/       nStartWink = nNewStart;
/*N*/       nEndWink = nNewEnd;
/*N*/
/*N*/       if(bKindChg || (eKind != OBJ_CIRC && bWinkChg))
/*N*/       {
/*N*/           SetXPolyDirty();
/*N*/           SetRectsDirty();
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void SdrCircObj::ImpSetCircInfoToAttr()
/*N*/ {
/*N*/   SdrCircKind eNewKindA = SDRCIRC_FULL;
/*N*/   const SfxItemSet& rSet = GetItemSet();
/*N*/
/*N*/   if(eKind == OBJ_SECT)
/*N*/       eNewKindA = SDRCIRC_SECT;
/*N*/   else if(eKind == OBJ_CARC)
/*N*/       eNewKindA = SDRCIRC_ARC;
/*N*/   else if(eKind == OBJ_CCUT)
/*N*/       eNewKindA = SDRCIRC_CUT;
/*N*/
/*N*/   SdrCircKind eOldKindA = ((SdrCircKindItem&)rSet.Get(SDRATTR_CIRCKIND)).GetValue();
/*N*/   sal_Int32 nOldStartWink = ((SdrCircStartAngleItem&)rSet.Get(SDRATTR_CIRCSTARTANGLE)).GetValue();
/*N*/   sal_Int32 nOldEndWink = ((SdrCircEndAngleItem&)rSet.Get(SDRATTR_CIRCENDANGLE)).GetValue();
/*N*/
/*N*/   if(eNewKindA != eOldKindA || nStartWink != nOldStartWink || nEndWink != nOldEndWink)
/*N*/   {
/*N*/       // #81921# since SetItem() implicitly calls ImpSetAttrToCircInfo()
/*N*/       // setting the item directly is necessary here.
/*?*/       ImpForceItemSet();
/*?*/
/*?*/       if(eNewKindA != eOldKindA)
/*?*/           mpObjectItemSet->Put(SdrCircKindItem(eNewKindA));
/*?*/
/*?*/       if(nStartWink != nOldStartWink)
/*?*/           mpObjectItemSet->Put(SdrCircStartAngleItem(nStartWink));
/*?*/
/*?*/       if(nEndWink != nOldEndWink)
/*?*/           mpObjectItemSet->Put(SdrCircEndAngleItem(nEndWink));
/*?*/
/*?*/       SetXPolyDirty();
/*?*/       ImpSetAttrToCircInfo();
/*N*/   }
/*N*/ }

/*N*/ SdrObject* SdrCircObj::DoConvertToPolyObj(BOOL bBezier) const
/*N*/ {
/*N*/   XPolygon aXP(ImpCalcXPoly(aRect,nStartWink,nEndWink));
/*N*/   SdrObjKind ePathKind=OBJ_PATHFILL;
/*N*/   FASTBOOL bFill=TRUE;
/*N*/   if (eKind==OBJ_CARC) bFill=FALSE;
/*N*/   SdrObject* pRet=ImpConvertMakeObj(XPolyPolygon(aXP),bFill,bBezier);
/*N*/   pRet=ImpConvertAddText(pRet,bBezier);
/*N*/   return pRet;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// pre- and postprocessing for objects for saving

/*N*/ void SdrCircObj::PreSave()
/*N*/ {
/*N*/   // call parent
/*N*/   SdrRectObj::PreSave();
/*N*/
/*N*/   // prepare SetItems for storage
/*N*/   const SfxItemSet& rSet = GetUnmergedItemSet();
/*N*/   const SfxItemSet* pParent = GetStyleSheet() ? &GetStyleSheet()->GetItemSet() : 0L;
/*N*/   SdrCircSetItem aCircAttr(rSet.GetPool());
/*N*/   aCircAttr.GetItemSet().Put(rSet);
/*N*/   aCircAttr.GetItemSet().SetParent(pParent);
/*N*/   mpObjectItemSet->Put(aCircAttr);
/*N*/ }

/*N*/ void SdrCircObj::PostSave()
/*N*/ {
/*N*/   // call parent
/*N*/   SdrRectObj::PostSave();
/*N*/
/*N*/   // remove SetItems from local itemset
/*N*/   mpObjectItemSet->ClearItem(SDRATTRSET_CIRC);
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrCircObj::WriteData(SvStream& rOut) const
/*N*/ {
/*N*/   SdrRectObj::WriteData(rOut);
/*N*/   SdrDownCompat aCompat(rOut,STREAM_WRITE); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("SdrCircObj");
/*N*/ #endif
/*N*/
/*N*/   if(eKind != OBJ_CIRC)
/*N*/   {
/*N*/       rOut << nStartWink;
/*N*/       rOut << nEndWink;
/*N*/   }
/*N*/
/*N*/   SfxItemPool* pPool=GetItemPool();
/*N*/   if(pPool)
/*N*/   {
/*N*/       const SfxItemSet& rSet = GetUnmergedItemSet();
/*N*/
/*N*/       pPool->StoreSurrogate(rOut, &rSet.Get(SDRATTRSET_CIRC));
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       rOut << UINT16(SFX_ITEMS_NULL);
/*N*/   }
/*N*/ }

/*N*/ void SdrCircObj::ReadData(const SdrObjIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   if(rIn.GetError())
/*N*/       return;
/*N*/
/*N*/   // #91764# remember eKind, it will be deleted during SdrRectObj::ReadData(...)
/*N*/   // but needs to be known to decide to jump over angles or not. Deletion happens
/*N*/   // cause of fix #89025# wich is necessary, too.
/*N*/   SdrObjKind eRememberedKind = eKind;
/*N*/
/*N*/   SdrRectObj::ReadData(rHead,rIn);
/*N*/   SdrDownCompat aCompat(rIn,STREAM_READ); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("SdrCircObj");
/*N*/ #endif
/*N*/
/*N*/   // #92309# at once restore the remembered eKind here.
/*N*/   eKind = eRememberedKind;
/*N*/
/*N*/   // #91764# use remembered eKind here
/*N*/   if(eRememberedKind != OBJ_CIRC)
/*N*/   {
/*N*/       rIn >> nStartWink;
/*N*/       rIn >> nEndWink;
/*N*/   }
/*N*/
/*N*/   if(aCompat.GetBytesLeft() > 0)
/*N*/   {
/*N*/       SfxItemPool* pPool = GetItemPool();
/*N*/
/*N*/       if(pPool)
/*N*/       {
/*N*/           sal_uInt16 nSetID = SDRATTRSET_CIRC;
/*N*/           const SdrCircSetItem* pCircAttr = (const SdrCircSetItem*)pPool->LoadSurrogate(rIn, nSetID, 0);
/*N*/           if(pCircAttr)
/*N*/               SetItemSet(pCircAttr->GetItemSet());
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           sal_uInt16 nSuroDum;
/*N*/           rIn >> nSuroDum;
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       // create pCircAttr for old Objects to let ImpSetCircInfoToAttr() do it's work
/*N*/       SdrCircKind eKindA(SDRCIRC_FULL);
/*N*/
/*N*/       if(eKind == OBJ_SECT)
/*N*/           eKindA = SDRCIRC_SECT;
/*N*/       else if(eKind == OBJ_CARC)
/*N*/           eKindA = SDRCIRC_ARC;
/*N*/       else if(eKind == OBJ_CCUT)
/*N*/           eKindA = SDRCIRC_CUT;
/*N*/
/*N*/       if(eKindA != SDRCIRC_FULL)
/*N*/       {
/*N*/           mpObjectItemSet->Put(SdrCircKindItem(eKindA));
/*N*/
/*N*/           if(nStartWink)
/*N*/               mpObjectItemSet->Put(SdrCircStartAngleItem(nStartWink));
/*N*/
/*N*/           if(nEndWink != 36000)
/*N*/               mpObjectItemSet->Put(SdrCircEndAngleItem(nEndWink));
/*N*/       }
/*N*/   }
/*N*/ }

