/*************************************************************************
 *
 *  $RCSfile: svx_svdopath.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:40 $
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

#include <tools/bigint.hxx>
#include "svdopath.hxx"
#include <math.h>
#include "xpool.hxx"
#include "xpoly.hxx"
#include "xoutx.hxx"
#include "svdxout.hxx"
#include "svdattr.hxx"
#include "svdtouch.hxx"
#include "svdtrans.hxx"
#include "svdio.hxx"
#include "svdetc.hxx"
#include "svddrag.hxx"
#include "svdmodel.hxx"
#include "svdpage.hxx"
#include "svdhdl.hxx"
//#include "svdosmrt.hxx"
#include "svdview.hxx"  // fuer MovCreate bei Freihandlinien
#include "svdglob.hxx"  // Stringcache
#include "svdstr.hrc"   // Objektname

#ifdef _MSC_VER
#pragma optimize ("",off)
#endif

#include "xlnwtit.hxx"
#include "xlnclit.hxx"
#include "xflclit.hxx"
#include "svdogrp.hxx"

#ifndef _SVX_XLNTRIT_HXX
#include "xlntrit.hxx"
#endif

#ifndef _SV_SALBTYPE_HXX
#include <vcl/salbtype.hxx>     // FRound
#endif

#ifndef _SVX_SVDOIMP_HXX
#include "svdoimp.hxx"
#endif
namespace binfilter {

// #104018# replace macros above with type-safe methods
inline sal_Int32 ImplTwipsToMM(sal_Int32 nVal) { return ((nVal * 127 + 36) / 72); }
inline sal_Int32 ImplMMToTwips(sal_Int32 nVal) { return ((nVal * 72 + 63) / 127); }
inline double ImplTwipsToMM(double fVal) { return (fVal * (127.0 / 72.0)); }
inline double ImplMMToTwips(double fVal) { return (fVal * (72.0 / 127.0)); }

/*************************************************************************/

#define SVDOPATH_INITSIZE   20
#define SVDOPATH_RESIZE     20

/*************************************************************************/

/*N*/ SdrPathObjGeoData::SdrPathObjGeoData()
/*N*/ {
/*N*/ }

/*N*/ SdrPathObjGeoData::~SdrPathObjGeoData()
/*N*/ {
/*N*/ }

/*N*/ TYPEINIT1(SdrPathObj,SdrTextObj);

/*N*/ SdrPathObj::SdrPathObj(SdrObjKind eNewKind)
/*N*/ {
/*N*/   eKind=eNewKind;
/*N*/   bClosedObj=IsClosed();
/*N*/   bCreating=FALSE;
/*N*/ }

/*N*/ SdrPathObj::SdrPathObj(SdrObjKind eNewKind, const XPolyPolygon& rPathPoly)
/*N*/ {
/*N*/   eKind=eNewKind;
/*N*/   bClosedObj=IsClosed();
/*N*/
/*N*/   // #104640# Set local XPolyPolygon with open/close correction
/*N*/   NbcSetPathPoly(rPathPoly);
/*N*/
/*N*/   bCreating=FALSE;
/*N*/   ImpForceKind();
/*N*/ }

/*?*/ SdrPathObj::SdrPathObj(const Point& rPt1, const Point& rPt2)
/*?*/ {
/*?*/   eKind=OBJ_LINE;
/*?*/   XPolygon aXP(2);
/*?*/   aXP[0]=rPt1;
/*?*/   aXP[1]=rPt2;
/*?*/   aPathPolygon.Insert(aXP);
/*?*/   bClosedObj=FALSE;
/*?*/   bCreating=FALSE;
/*?*/   ImpForceLineWink();
/*?*/ }

/*N*/ SdrPathObj::~SdrPathObj()
/*N*/ {
/*N*/ }

/*N*/ FASTBOOL SdrPathObj::FindPolyPnt(USHORT nAbsPnt, USHORT& rPolyNum,
/*N*/                            USHORT& rPointNum, FASTBOOL bAllPoints) const
/*N*/ {
/*N*/   USHORT nPolyCnt=aPathPolygon.Count();
/*N*/   USHORT nPoly=0;
/*N*/   FASTBOOL bClosed=IsClosed();
/*N*/   nAbsPnt+=1;
/*N*/
/*N*/   while (nPoly<nPolyCnt) {
/*N*/       const XPolygon& rXPoly = aPathPolygon[nPoly];
/*N*/       USHORT nPnt=0;
/*N*/       USHORT nCnt=0;
/*N*/       USHORT nPntCnt=rXPoly.GetPointCount();
/*N*/       // geschlossen? Dann Endpunkt=Startpunkt
/*N*/       if (bClosed && nPntCnt>1) nPntCnt--;
/*N*/
/*N*/       while (nPnt<nPntCnt) {
/*N*/           if (bAllPoints || rXPoly.GetFlags(nPnt)!=XPOLY_CONTROL) nCnt++;
/*N*/           if (nCnt==nAbsPnt) {
/*N*/               rPolyNum=nPoly;
/*N*/               rPointNum=nPnt;
/*N*/               return TRUE;
/*N*/           }
/*N*/           nPnt++;
/*N*/       }
/*?*/       nAbsPnt-=nCnt;
/*?*/       nPoly++;
/*?*/   }
/*?*/   return FALSE;
/*N*/ }

/*N*/ void SdrPathObj::ImpForceLineWink()
/*N*/ {
/*N*/   if (aPathPolygon.Count()==1 && aPathPolygon[0].GetPointCount()==2 && eKind==OBJ_LINE) {
/*N*/       Point aDelt(aPathPolygon[0][1]);
/*N*/       aDelt-=aPathPolygon[0][0];
/*N*/       aGeo.nDrehWink=GetAngle(aDelt);
/*N*/       aGeo.nShearWink=0;
/*N*/       aGeo.RecalcSinCos();
/*N*/       aGeo.RecalcTan();
/*N*/
/*N*/       // #101412# for SdrTextObj, keep aRect up to date
/*N*/       aRect = Rectangle(aPathPolygon[0][0], aPathPolygon[0][1]);
/*N*/       aRect.Justify();
/*N*/   }
/*N*/ }

/*N*/ void SdrPathObj::ImpForceKind()
/*N*/ {
/*N*/   if (eKind==OBJ_PATHPLIN) eKind=OBJ_PLIN;
/*N*/   if (eKind==OBJ_PATHPOLY) eKind=OBJ_POLY;
/*N*/
/*N*/   USHORT nPolyAnz=aPathPolygon.Count();
/*N*/   USHORT nPoly1PointAnz=nPolyAnz==0 ? 0 : aPathPolygon[0].GetPointCount();
/*N*/   FASTBOOL bHasCtrl=FALSE;
/*N*/   FASTBOOL bHasLine=FALSE; // gemischt wird jedoch z.Zt. nicht in eKind festgehalten
/*N*/   for (USHORT nPolyNum=0; nPolyNum<nPolyAnz && (!bHasCtrl || !bHasLine); nPolyNum++) {
/*N*/       const XPolygon& rPoly=aPathPolygon[nPolyNum];
/*N*/       USHORT nPointAnz=rPoly.GetPointCount();
/*N*/       for (USHORT nPointNum=0; nPointNum<nPointAnz && (!bHasCtrl || !bHasLine); nPointNum++) {
/*N*/           if (rPoly.IsControl(nPointNum)) bHasCtrl=TRUE;
/*N*/           if (nPointNum+1<nPointAnz && !rPoly.IsControl(nPointNum) && !rPoly.IsControl(nPointNum+1)) bHasLine=TRUE;
/*N*/       }
/*N*/   }
/*N*/   if (!bHasCtrl) {
/*N*/       switch (eKind) {
/*N*/           case OBJ_PATHLINE: eKind=OBJ_PLIN; break;
/*N*/           case OBJ_FREELINE: eKind=OBJ_PLIN; break;
/*N*/           case OBJ_PATHFILL: eKind=OBJ_POLY; break;
/*N*/           case OBJ_FREEFILL: eKind=OBJ_POLY; break;
/*N*/       }
/*N*/   } else {
/*N*/       switch (eKind) {
/*N*/           case OBJ_LINE: eKind=OBJ_PATHLINE; break;
/*N*/           case OBJ_PLIN: eKind=OBJ_PATHLINE; break;
/*N*/           case OBJ_POLY: eKind=OBJ_PATHFILL; break;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (eKind==OBJ_LINE && (nPolyAnz!=1 || nPoly1PointAnz!=2)) eKind=OBJ_PLIN;
/*N*/   if (eKind==OBJ_PLIN && (nPolyAnz==1 && nPoly1PointAnz==2)) eKind=OBJ_LINE;
/*N*/
/*N*/   bClosedObj=IsClosed();
/*N*/
/*N*/   if (eKind==OBJ_LINE)
/*N*/   {
/*N*/       ImpForceLineWink();
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       // #i10659#, similar to #101412# but for polys with more than 2 points.
/*N*/       //
/*N*/       // Here i again need to fix something, because when Path-Polys are Copy-Pasted
/*N*/       // between Apps with different measurements (e.g. 100TH_MM and TWIPS) there is
/*N*/       // a scaling loop started from SdrExchangeView::Paste. This is principally nothing
/*N*/       // wrong, but aRect is wrong here and not even updated by RecalcSnapRect(). If
/*N*/       // this is the case, some size needs to be set here in aRect to avoid that the cyclus
/*N*/       // through Rect2Poly - Poly2Rect does something badly wrong since that cycle is
/*N*/       // BASED on aRect. That cycle is triggered in SdrTextObj::NbcResize() which is called
/*N*/       // from the local Resize() implementation.
/*N*/       //
/*N*/       // Basic problem is that the member aRect in SdrTextObj basically is a unrotated
/*N*/       // text rectangle for the text object itself and methods at SdrTextObj do handle it
/*N*/       // in that way. Many draw objects derived from SdrTextObj 'abuse' aRect as SnapRect
/*N*/       // which is basically wrong. To make the SdrText methods which deal with aRect directly
/*N*/       // work it is necessary to always keep aRect updated. This e.g. not done after a Clone()
/*N*/       // command for SdrPathObj. Since adding this update mechanism with #101412# to
/*N*/       // ImpForceLineWink() for lines was very successful, i add it to where ImpForceLineWink()
/*N*/       // was called, once here below and once on a 2nd place below.
/*N*/
/*N*/       // #i10659# for SdrTextObj, keep aRect up to date
/*N*/       aRect=aPathPolygon.GetBoundRect(); // fuer SdrTextObj
/*N*/   }
/*N*/ }

//STRIP001 void SdrPathObj::ImpSetClosed(FASTBOOL bClose)
//STRIP001 {
//STRIP001  if (bClose) {
//STRIP001      switch (eKind) {
//STRIP001          case OBJ_LINE    : eKind=OBJ_POLY;     break;
//STRIP001          case OBJ_PLIN    : eKind=OBJ_POLY;     break;
//STRIP001          case OBJ_PATHLINE: eKind=OBJ_PATHFILL; break;
//STRIP001          case OBJ_FREELINE: eKind=OBJ_FREEFILL; break;
//STRIP001          case OBJ_SPLNLINE: eKind=OBJ_SPLNFILL; break;
//STRIP001      }
//STRIP001      // Nun das Poly noch schliessen
//STRIP001      USHORT nPolyAnz=aPathPolygon.Count();
//STRIP001      for (USHORT nPolyNum=0; nPolyNum<nPolyAnz; nPolyNum++) {
//STRIP001           XPolygon& rXP=aPathPolygon[nPolyNum];
//STRIP001           USHORT nPntMax=rXP.GetPointCount();
//STRIP001           if (nPntMax!=0) {
//STRIP001               nPntMax--;
//STRIP001               if (rXP[0]!=rXP[nPntMax]) {
//STRIP001                   rXP[nPntMax+1]=Point(rXP[0]);
//STRIP001               }
//STRIP001           }
//STRIP001      }
//STRIP001      bClosedObj=TRUE;
//STRIP001  } else {
//STRIP001      switch (eKind) {
//STRIP001          case OBJ_POLY    : eKind=OBJ_PLIN;     break;
//STRIP001          case OBJ_PATHFILL: eKind=OBJ_PATHLINE; break;
//STRIP001          case OBJ_FREEFILL: eKind=OBJ_FREELINE; break;
//STRIP001          case OBJ_SPLNFILL: eKind=OBJ_SPLNLINE; break;
//STRIP001      }
//STRIP001      bClosedObj=FALSE;
//STRIP001  }
//STRIP001  ImpForceKind();
//STRIP001 }

//STRIP001 void SdrPathObj::TakeObjInfo(SdrObjTransformInfoRec& rInfo) const
//STRIP001 {
//STRIP001  rInfo.bNoContortion=FALSE;
//STRIP001
//STRIP001  FASTBOOL bCanConv = !HasText() || ImpCanConvTextToCurve();
//STRIP001  FASTBOOL bIsPath = IsBezier() || IsSpline();
//STRIP001
//STRIP001  rInfo.bEdgeRadiusAllowed    = FALSE;
//STRIP001  rInfo.bCanConvToPath = bCanConv && !bIsPath;
//STRIP001  rInfo.bCanConvToPoly = bCanConv && bIsPath;
//STRIP001  rInfo.bCanConvToContour = !IsFontwork() && (rInfo.bCanConvToPoly || LineGeometryUsageIsNecessary());
//STRIP001 }

/*N*/ UINT16 SdrPathObj::GetObjIdentifier() const
/*N*/ {
/*N*/   return USHORT(eKind);
/*N*/ }

/*N*/ void SdrPathObj::RecalcBoundRect()
/*N*/ {
/*N*/   aOutRect=GetSnapRect();
/*N*/   long nLineWdt=ImpGetLineWdt();
/*N*/   if (!IsClosed()) { // ggf. Linienenden beruecksichtigen
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

/*N*/ FASTBOOL SdrPathObj::Paint(ExtOutputDevice& rXOut, const SdrPaintInfoRec& rInfoRec) const
/*N*/ {
/*N*/   // Hidden objects on masterpages, draw nothing
/*N*/   if((rInfoRec.nPaintMode & SDRPAINTMODE_MASTERPAGE) && bNotVisibleAsMaster)
/*N*/       return TRUE;
/*N*/
/*N*/   BOOL bHideContour(IsHideContour());
/*N*/   BOOL bIsFillDraft(0 != (rInfoRec.nPaintMode & SDRPAINTMODE_DRAFTFILL));
/*N*/   BOOL bIsLineDraft(0 != (rInfoRec.nPaintMode & SDRPAINTMODE_DRAFTLINE));
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
/*N*/   if (!bHideContour && ImpSetShadowAttributes(rSet, aShadowSet))
/*N*/   {
/*?*/         if( !IsClosed() || bIsFillDraft )
/*?*/             rXOut.SetFillAttr(aEmptySet);
/*?*/         else
/*?*/             rXOut.SetFillAttr(aShadowSet);
/*?*/
/*?*/       UINT32 nXDist=((SdrShadowXDistItem&)(rSet.Get(SDRATTR_SHADOWXDIST))).GetValue();
/*?*/       UINT32 nYDist=((SdrShadowYDistItem&)(rSet.Get(SDRATTR_SHADOWYDIST))).GetValue();
/*?*/       XPolyPolygon aTmpXPoly(aPathPolygon);
/*?*/       aTmpXPoly.Move(nXDist,nYDist);
/*?*/
/*?*/       // avoid shadow line drawing in XOut
/*?*/       rXOut.SetLineAttr(aEmptySet);
/*?*/
/*?*/         if (!IsClosed()) {
/*?*/             USHORT nPolyAnz=aTmpXPoly.Count();
/*?*/             for (USHORT nPolyNum=0; nPolyNum<nPolyAnz; nPolyNum++) {
/*?*/                 rXOut.DrawXPolyLine(aTmpXPoly.GetObject(nPolyNum));
/*?*/             }
/*?*/         } else {
/*?*/             // #100127# Output original geometry for metafiles
/*?*/             ImpGraphicFill aFill( *this, rXOut, aShadowSet, true );
/*?*/
/*?*/             rXOut.DrawXPolyPolygon(aTmpXPoly);
/*?*/         }
/*?*/
/*?*/       // new shadow line drawing
/*?*/       if( pLineGeometry.get() )
/*?*/       {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/           // draw the line geometry
//STRIP001 /*?*/            ImpDrawShadowLineGeometry(rXOut, rSet, *pLineGeometry);
/*?*/       }
/*N*/   }

    // Before here the LineAttr were set: if(pLineAttr) rXOut.SetLineAttr(*pLineAttr);
    // avoid line drawing in XOut
/*N*/   rXOut.SetLineAttr(aEmptySet);
/*N*/
/*N*/     rXOut.SetFillAttr( bIsFillDraft || !IsClosed() ? aEmptySet : rSet );
/*N*/
/*N*/   if( !bHideContour )
/*N*/     {
/*N*/         if( IsClosed() )
/*N*/         {
/*N*/             // #100127# Output original geometry for metafiles
/*?*/             ImpGraphicFill aFill( *this, rXOut, bIsFillDraft || !IsClosed() ? aEmptySet : rSet );
/*?*/
/*?*/             rXOut.DrawXPolyPolygon(aPathPolygon);
/*N*/         }
/*N*/
/*N*/         // Own line drawing
/*N*/         if( pLineGeometry.get() )
/*N*/         {
/*N*/             // draw the line geometry
/*N*/             ImpDrawColorLineGeometry(rXOut, rSet, *pLineGeometry);
/*N*/         }
/*N*/     }
/*N*/
/*N*/   FASTBOOL bOk=TRUE;
/*N*/   if (HasText()) {
/*?*/       bOk=SdrTextObj::Paint(rXOut,rInfoRec);
/*N*/   }
/*N*/   if (bOk && (rInfoRec.nPaintMode & SDRPAINTMODE_GLUEPOINTS) !=0) {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 bOk=PaintGluePoints(rXOut,rInfoRec);
/*N*/   }
/*N*/
/*N*/   return bOk;
/*N*/ }

/*N*/ SdrObject* SdrPathObj::CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const
/*N*/ {
/*N*/   if (pVisiLayer!=NULL && !pVisiLayer->IsSet(nLayerId)) return NULL;
/*N*/   INT32 nMyTol=nTol;
/*N*/   FASTBOOL bFilled=IsClosed() && (bTextFrame || HasFill());
/*N*/
/*N*/   INT32 nWdt=ImpGetLineWdt()/2; // Halbe Strichstaerke
/*N*/   if (nWdt>nMyTol) nMyTol=nWdt; // Bei dicker Linie keine Toleranz noetig
/*N*/   Rectangle aR(rPnt,rPnt);
/*N*/   aR.Left()  -=nMyTol;
/*N*/   aR.Right() +=nMyTol;
/*N*/   aR.Top()   -=nMyTol;
/*N*/   aR.Bottom()+=nMyTol;
/*N*/
/*N*/   FASTBOOL bHit=FALSE;
/*N*/   unsigned nPolyAnz=aPathPolygon.Count();
/*N*/   if (bFilled) {
/*N*/       PolyPolygon aPP;
/*N*/       for (unsigned nPolyNum=0; nPolyNum<nPolyAnz; nPolyNum++) {
/*N*/           aPP.Insert(XOutCreatePolygon(aPathPolygon[nPolyNum],NULL));
/*N*/       }
/*N*/       bHit=IsRectTouchesPoly(aPP,aR);
/*N*/   } else {
/*N*/       for (unsigned nPolyNum=0; nPolyNum<nPolyAnz && !bHit; nPolyNum++) {
/*N*/           Polygon aPoly(XOutCreatePolygon(aPathPolygon[nPolyNum],NULL));
/*N*/           bHit=IsRectTouchesLine(aPoly,aR);
/*N*/       }
/*N*/   }
/*N*/   if (!bHit && !IsTextFrame() && HasText()) {
/*N*/       bHit=SdrTextObj::CheckHit(rPnt,nTol,pVisiLayer)!=NULL;
/*N*/   }
/*N*/   return bHit ? (SdrObject*)this : NULL;
/*N*/ }

/*N*/ void SdrPathObj::operator=(const SdrObject& rObj)
/*N*/ {
/*N*/   SdrTextObj::operator=(rObj);
/*N*/   SdrPathObj& rPath=(SdrPathObj&)rObj;
/*N*/   aPathPolygon=rPath.aPathPolygon;
/*N*/ }

//STRIP001 void SdrPathObj::TakeObjNameSingul(XubString& rName) const
//STRIP001 {
//STRIP001  if (eKind==OBJ_LINE) {
//STRIP001      USHORT nId=STR_ObjNameSingulLINE;
//STRIP001      if (aPathPolygon.Count()==1 && aPathPolygon[0].GetPointCount()==2) {
//STRIP001          Point aP1(aPathPolygon[0][0]);
//STRIP001          Point aP2(aPathPolygon[0][1]);
//STRIP001          if (aP1!=aP2) {
//STRIP001              if (aP1.Y()==aP2.Y()) {
//STRIP001                  nId=STR_ObjNameSingulLINE_Hori;
//STRIP001              } else if (aP1.X()==aP2.X()) {
//STRIP001                  nId=STR_ObjNameSingulLINE_Vert;
//STRIP001              } else {
//STRIP001                  long dx=aP1.X()-aP2.X(); dx=Abs(dx);
//STRIP001                  long dy=aP1.Y()-aP2.Y(); dy=Abs(dy);
//STRIP001                  if (dx==dy) {
//STRIP001                      nId=STR_ObjNameSingulLINE_Diag;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      rName=ImpGetResStr(nId);
//STRIP001  } else if (eKind==OBJ_PLIN || eKind==OBJ_POLY) {
//STRIP001      FASTBOOL bClosed=eKind==OBJ_POLY;
//STRIP001      USHORT nId=0;
//STRIP001      if (bCreating) { // z.Zt. Create
//STRIP001          if (bClosed) {
//STRIP001              nId=STR_ObjNameSingulPOLY;
//STRIP001          } else {
//STRIP001              nId=STR_ObjNameSingulPLIN;
//STRIP001          }
//STRIP001          rName=ImpGetResStr(nId);
//STRIP001      } else {                // sonst Punkteanzahl bestimmen
//STRIP001          ULONG nPntAnz=0;
//STRIP001          USHORT nPolyAnz=aPathPolygon.Count();
//STRIP001          for (USHORT nPoly=0; nPoly<nPolyAnz; nPoly++) {
//STRIP001              USHORT n=aPathPolygon[nPoly].GetPointCount();
//STRIP001              if (n>1 && bClosed) n--;
//STRIP001              nPntAnz+=n;
//STRIP001          }
//STRIP001          if (bClosed) {
//STRIP001              nId=STR_ObjNameSingulPOLY_PntAnz;
//STRIP001          } else {
//STRIP001              nId=STR_ObjNameSingulPLIN_PntAnz;
//STRIP001          }
//STRIP001
//STRIP001          rName = ImpGetResStr(nId);
//STRIP001          UINT16 nPos = rName.SearchAscii("%N");
//STRIP001
//STRIP001          if(nPos != STRING_NOTFOUND)
//STRIP001          {
//STRIP001              rName.Erase(nPos, 2);
//STRIP001              rName.Insert(UniString::CreateFromInt32(nPntAnz), nPos);
//STRIP001          }
//STRIP001      }
//STRIP001  } else {
//STRIP001      switch (eKind) {
//STRIP001          case OBJ_PATHLINE: rName=ImpGetResStr(STR_ObjNameSingulPATHLINE); break;
//STRIP001          case OBJ_FREELINE: rName=ImpGetResStr(STR_ObjNameSingulFREELINE); break;
//STRIP001          case OBJ_SPLNLINE: rName=ImpGetResStr(STR_ObjNameSingulNATSPLN); break;
//STRIP001          case OBJ_PATHFILL: rName=ImpGetResStr(STR_ObjNameSingulPATHFILL); break;
//STRIP001          case OBJ_FREEFILL: rName=ImpGetResStr(STR_ObjNameSingulFREEFILL); break;
//STRIP001          case OBJ_SPLNFILL: rName=ImpGetResStr(STR_ObjNameSingulPERSPLN); break;
//STRIP001      }
//STRIP001  }
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

//STRIP001 void SdrPathObj::TakeObjNamePlural(XubString& rName) const
//STRIP001 {
//STRIP001  switch (eKind) {
//STRIP001      case OBJ_LINE    : rName=ImpGetResStr(STR_ObjNamePluralLINE    ); break;
//STRIP001      case OBJ_PLIN    : rName=ImpGetResStr(STR_ObjNamePluralPLIN    ); break;
//STRIP001      case OBJ_POLY    : rName=ImpGetResStr(STR_ObjNamePluralPOLY    ); break;
//STRIP001      case OBJ_PATHLINE: rName=ImpGetResStr(STR_ObjNamePluralPATHLINE); break;
//STRIP001      case OBJ_FREELINE: rName=ImpGetResStr(STR_ObjNamePluralFREELINE); break;
//STRIP001      case OBJ_SPLNLINE: rName=ImpGetResStr(STR_ObjNamePluralNATSPLN); break;
//STRIP001      case OBJ_PATHFILL: rName=ImpGetResStr(STR_ObjNamePluralPATHFILL); break;
//STRIP001      case OBJ_FREEFILL: rName=ImpGetResStr(STR_ObjNamePluralFREEFILL); break;
//STRIP001      case OBJ_SPLNFILL: rName=ImpGetResStr(STR_ObjNamePluralPERSPLN); break;
//STRIP001  }
//STRIP001 }

/*N*/ void SdrPathObj::TakeXorPoly(XPolyPolygon& rXPolyPoly, FASTBOOL bDetail) const
/*N*/ {
/*N*/   rXPolyPoly=aPathPolygon;
/*N*/ }

/*N*/ void SdrPathObj::TakeContour(XPolyPolygon& rPoly) const
/*N*/ {
/*N*/   // am 14.1.97 wg. Umstellung TakeContour ueber Mtf und Paint. Joe.
/*N*/   SdrTextObj::TakeContour(rPoly);
/*N*/ }

//STRIP001 void SdrPathObj::TakeContour(XPolyPolygon& rXPoly, SdrContourType eType) const
//STRIP001 {
//STRIP001 }

//STRIP001 USHORT SdrPathObj::GetHdlCount() const
//STRIP001 {
//STRIP001  USHORT i,j;
//STRIP001  USHORT nCnt=0;
//STRIP001  USHORT nPolyCnt=aPathPolygon.Count();
//STRIP001  FASTBOOL bClosed=IsClosed();
//STRIP001
//STRIP001  for (i=0; i<nPolyCnt; i++) {
//STRIP001      const XPolygon& rXPoly=aPathPolygon[i];
//STRIP001      USHORT nPntCnt=rXPoly.GetPointCount();
//STRIP001      // Polygon geschlossen? Dann Endpunkt = Startpunkt
//STRIP001      if (bClosed && nPntCnt>1) nPntCnt--;
//STRIP001
//STRIP001      for (j=0; j<nPntCnt; j++)
//STRIP001          if (rXPoly.GetFlags(j)!=XPOLY_CONTROL) nCnt++;
//STRIP001  }
//STRIP001  return nCnt;
//STRIP001 }

//STRIP001 SdrHdl* SdrPathObj::GetHdl(USHORT nHdlNum) const
//STRIP001 {
//STRIP001  SdrHdl* pHdl=NULL;
//STRIP001  USHORT  nPoly,nPnt;
//STRIP001
//STRIP001  if (FindPolyPnt(nHdlNum,nPoly,nPnt,FALSE)) {
//STRIP001      pHdl=new SdrHdl(aPathPolygon[nPoly][nPnt],HDL_POLY);
//STRIP001      pHdl->SetPolyNum(nPoly);
//STRIP001      pHdl->SetPointNum(nPnt);
//STRIP001      pHdl->SetSourceHdlNum(nHdlNum);
//STRIP001      pHdl->Set1PixMore(nPnt==0);
//STRIP001  }
//STRIP001  return pHdl;
//STRIP001 }

//STRIP001 void SdrPathObj::AddToHdlList(SdrHdlList& rHdlList) const
//STRIP001 {
//STRIP001  USHORT nCnt=GetHdlCount();
//STRIP001  USHORT nPolyCnt=aPathPolygon.Count();
//STRIP001  FASTBOOL bClosed=IsClosed();
//STRIP001  USHORT nIdx=0;
//STRIP001
//STRIP001  for (USHORT i=0; i<nPolyCnt; i++) {
//STRIP001      const XPolygon& rXPoly=aPathPolygon.GetObject(i);
//STRIP001      USHORT nPntCnt=rXPoly.GetPointCount();
//STRIP001      if (bClosed && nPntCnt>1) nPntCnt--;
//STRIP001
//STRIP001      for (USHORT j=0; j<nPntCnt; j++) {
//STRIP001          if (rXPoly.GetFlags(j)!=XPOLY_CONTROL) {
//STRIP001              const Point& rPnt=rXPoly[j];
//STRIP001              SdrHdl* pHdl=new SdrHdl(rPnt,HDL_POLY);
//STRIP001              pHdl->SetPolyNum(i);
//STRIP001              pHdl->SetPointNum(j);
//STRIP001              pHdl->Set1PixMore(j==0);
//STRIP001              pHdl->SetSourceHdlNum(nIdx);
//STRIP001              nIdx++;
//STRIP001              rHdlList.AddHdl(pHdl);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 USHORT SdrPathObj::GetPlusHdlCount(const SdrHdl& rHdl) const
//STRIP001 {
//STRIP001  USHORT nCnt=0;
//STRIP001  USHORT nPnt=rHdl.GetPointNum();
//STRIP001  USHORT nPolyNum=rHdl.GetPolyNum();
//STRIP001  if (nPolyNum<aPathPolygon.Count()) {
//STRIP001      const XPolygon& rXPoly=aPathPolygon[nPolyNum];
//STRIP001      USHORT nPntMax=rXPoly.GetPointCount();
//STRIP001      if (nPntMax>0) {
//STRIP001          nPntMax--;
//STRIP001          if (nPnt<=nPntMax) {
//STRIP001              if (rXPoly.GetFlags(nPnt)!=XPOLY_CONTROL) {
//STRIP001                  if (nPnt==0 && IsClosed()) nPnt=nPntMax;
//STRIP001                  if (nPnt>0 && rXPoly.GetFlags(nPnt-1)==XPOLY_CONTROL) nCnt++;
//STRIP001                  if (nPnt==nPntMax && IsClosed()) nPnt=0;
//STRIP001                  if (nPnt<nPntMax && rXPoly.GetFlags(nPnt+1)==XPOLY_CONTROL) nCnt++;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return nCnt;
//STRIP001 }

//STRIP001 SdrHdl* SdrPathObj::GetPlusHdl(const SdrHdl& rHdl, USHORT nPlusNum) const
//STRIP001 {
//STRIP001  SdrHdl* pHdl=NULL;
//STRIP001  USHORT nPnt=rHdl.GetPointNum();
//STRIP001  USHORT nPolyNum=rHdl.GetPolyNum();
//STRIP001  if (nPolyNum<aPathPolygon.Count()) {
//STRIP001      const XPolygon& rXPoly=aPathPolygon[nPolyNum];
//STRIP001      USHORT nPntMax=rXPoly.GetPointCount();
//STRIP001      if (nPntMax>0) {
//STRIP001          nPntMax--;
//STRIP001          if (nPnt<=nPntMax) {
//STRIP001              pHdl=new SdrHdlBezWgt(&rHdl);
//STRIP001              pHdl->SetPolyNum(rHdl.GetPolyNum());
//STRIP001
//STRIP001              if (nPnt==0 && IsClosed()) nPnt=nPntMax;
//STRIP001              if (nPnt>0 && rXPoly.GetFlags(nPnt-1)==XPOLY_CONTROL && nPlusNum==0) {
//STRIP001                  pHdl->SetPos(rXPoly[nPnt-1]);
//STRIP001                  pHdl->SetPointNum(nPnt-1);
//STRIP001              } else {
//STRIP001                  if (nPnt==nPntMax && IsClosed()) nPnt=0;
//STRIP001                  if (nPnt<rXPoly.GetPointCount()-1 && rXPoly.GetFlags(nPnt+1)==XPOLY_CONTROL) {
//STRIP001                      pHdl->SetPos(rXPoly[nPnt+1]);
//STRIP001                      pHdl->SetPointNum(nPnt+1);
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              pHdl->SetSourceHdlNum(rHdl.GetSourceHdlNum());
//STRIP001              pHdl->SetPlusHdl(TRUE);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return pHdl;
//STRIP001 }

//STRIP001 FASTBOOL SdrPathObj::HasSpecialDrag() const
//STRIP001 {
//STRIP001  return TRUE;
//STRIP001 }

/*?*/ inline USHORT GetPrevPnt(USHORT nPnt, USHORT nPntMax, FASTBOOL bClosed)
/*?*/ {
/*?*/   if (nPnt>0) {
/*?*/       nPnt--;
/*?*/   } else {
/*?*/       nPnt=nPntMax;
/*?*/       if (bClosed) nPnt--;
/*?*/   }
/*?*/   return nPnt;
/*?*/ }

/*?*/ inline USHORT GetNextPnt(USHORT nPnt, USHORT nPntMax, FASTBOOL bClosed)
/*?*/ {
/*?*/   nPnt++;
/*?*/   if (nPnt>nPntMax || (bClosed && nPnt>=nPntMax)) nPnt=0;
/*?*/   return nPnt;
/*?*/ }

//STRIP001 class ImpSdrPathDragData
//STRIP001 {
//STRIP001 public:
//STRIP001  XPolygon                    aXP;            // Ausschnitt aud dem Originalpolygon
//STRIP001  FASTBOOL                    bValid;         // FALSE = zu wenig Punkte
//STRIP001  FASTBOOL                    bClosed;        // geschlossenes Objekt?
//STRIP001  USHORT                      nPoly;          // Nummer des Polygons im PolyPolygon
//STRIP001  USHORT                      nPnt;           // Punktnummer innerhalb des obigen Polygons
//STRIP001  USHORT                      nPntAnz;        // Punktanzahl des Polygons
//STRIP001  USHORT                      nPntMax;        // Maximaler Index
//STRIP001  FASTBOOL                    bBegPnt;        // Gedraggter Punkt ist der Anfangspunkt einer Polyline
//STRIP001  FASTBOOL                    bEndPnt;        // Gedraggter Punkt ist der Endpunkt einer Polyline
//STRIP001  USHORT                      nPrevPnt;       // Index des vorherigen Punkts
//STRIP001  USHORT                      nNextPnt;       // Index des naechsten Punkts
//STRIP001  FASTBOOL                    bPrevIsBegPnt;  // Vorheriger Punkt ist Anfangspunkt einer Polyline
//STRIP001  FASTBOOL                    bNextIsEndPnt;  // Folgepunkt ist Endpunkt einer Polyline
//STRIP001  USHORT                      nPrevPrevPnt;   // Index des vorvorherigen Punkts
//STRIP001  USHORT                      nNextNextPnt;   // Index des uebernaechsten Punkts
//STRIP001  FASTBOOL                    bControl;       // Punkt ist ein Kontrollpunkt
//STRIP001  FASTBOOL                    bIsPrevControl; // Punkt ist Kontrollpunkt vor einem Stuetzpunkt
//STRIP001  FASTBOOL                    bIsNextControl; // Punkt ist Kontrollpunkt hinter einem Stuetzpunkt
//STRIP001  FASTBOOL                    bPrevIsControl; // Falls nPnt ein StPnt: Davor ist ein Kontrollpunkt
//STRIP001  FASTBOOL                    bNextIsControl; // Falls nPnt ein StPnt: Dahinter ist ein Kontrollpunkt
//STRIP001  USHORT                      nPrevPrevPnt0;
//STRIP001  USHORT                      nPrevPnt0;
//STRIP001  USHORT                      nPnt0;
//STRIP001  USHORT                      nNextPnt0;
//STRIP001  USHORT                      nNextNextPnt0;
//STRIP001  FASTBOOL                    bEliminate;     // Punkt loeschen? (wird von MovDrag gesetzt)
//STRIP001
//STRIP001  // ##
//STRIP001  BOOL                        mbMultiPointDrag;
//STRIP001  const XPolyPolygon&         mrOrig;
//STRIP001  XPolyPolygon                maMove;
//STRIP001  Container                   maHandles;
//STRIP001
//STRIP001 public:
//STRIP001  ImpSdrPathDragData(const SdrPathObj& rPO, const SdrHdl& rHdl, BOOL bMuPoDr, const SdrDragStat& rDrag);
//STRIP001  void ResetPoly(const SdrPathObj& rPO);
//STRIP001  BOOL IsMultiPointDrag() const { return mbMultiPointDrag; }
//STRIP001 };

//STRIP001 ImpSdrPathDragData::ImpSdrPathDragData(const SdrPathObj& rPO, const SdrHdl& rHdl, BOOL bMuPoDr, const SdrDragStat& rDrag)
//STRIP001 :    aXP(5),
//STRIP001  mbMultiPointDrag(bMuPoDr),
//STRIP001  mrOrig(rPO.GetPathPoly()),
//STRIP001  maHandles(0)
//STRIP001 {
//STRIP001  if(mbMultiPointDrag)
//STRIP001  {
//STRIP001      const SdrMarkView& rMarkView = *rDrag.GetView();
//STRIP001      const SdrHdlList& rHdlList = rMarkView.GetHdlList();
//STRIP001      const sal_uInt32 nHdlCount = rHdlList.GetHdlCount();
//STRIP001
//STRIP001      for(sal_uInt32 a(0); a < nHdlCount; a++)
//STRIP001      {
//STRIP001          SdrHdl* pTestHdl = rHdlList.GetHdl(a);
//STRIP001
//STRIP001          if(pTestHdl
//STRIP001              && pTestHdl->IsSelected()
//STRIP001              && pTestHdl->GetObj() == (SdrObject*)&rPO)
//STRIP001          {
//STRIP001              maHandles.Insert(pTestHdl, CONTAINER_APPEND);
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      maMove = mrOrig;
//STRIP001      bValid = TRUE;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      bValid=FALSE;
//STRIP001      bClosed=rPO.IsClosed();          // geschlossenes Objekt?
//STRIP001      nPoly=rHdl.GetPolyNum();            // Nummer des Polygons im PolyPolygon
//STRIP001      nPnt=rHdl.GetPointNum();            // Punktnummer innerhalb des obigen Polygons
//STRIP001      const XPolygon& rXP=rPO.aPathPolygon[nPoly];     // Referenz auf das Polygon
//STRIP001      nPntAnz=rXP.GetPointCount();        // Punktanzahl des Polygons
//STRIP001      if (nPntAnz==0 || (bClosed && nPntAnz==1)) return; // min. 1Pt bei Line, min. 2 bei Polygon
//STRIP001      nPntMax=nPntAnz-1;                  // Maximaler Index
//STRIP001      bBegPnt=!bClosed && nPnt==0;        // Gedraggter Punkt ist der Anfangspunkt einer Polyline
//STRIP001      bEndPnt=!bClosed && nPnt==nPntMax;  // Gedraggter Punkt ist der Endpunkt einer Polyline
//STRIP001      if (bClosed && nPntAnz<=3) {        // Falls Polygon auch nur eine Linie ist
//STRIP001          bBegPnt=(nPntAnz<3) || nPnt==0;
//STRIP001          bEndPnt=(nPntAnz<3) || nPnt==nPntMax-1;
//STRIP001      }
//STRIP001      nPrevPnt=nPnt;                      // Index des vorherigen Punkts
//STRIP001      nNextPnt=nPnt;                      // Index des naechsten Punkts
//STRIP001      if (!bBegPnt) nPrevPnt=GetPrevPnt(nPnt,nPntMax,bClosed);
//STRIP001      if (!bEndPnt) nNextPnt=GetNextPnt(nPnt,nPntMax,bClosed);
//STRIP001      bPrevIsBegPnt=bBegPnt || (!bClosed && nPrevPnt==0);
//STRIP001      bNextIsEndPnt=bEndPnt || (!bClosed && nNextPnt==nPntMax);
//STRIP001      nPrevPrevPnt=nPnt;                  // Index des vorvorherigen Punkts
//STRIP001      nNextNextPnt=nPnt;                  // Index des uebernaechsten Punkts
//STRIP001      if (!bPrevIsBegPnt) nPrevPrevPnt=GetPrevPnt(nPrevPnt,nPntMax,bClosed);
//STRIP001      if (!bNextIsEndPnt) nNextNextPnt=GetNextPnt(nNextPnt,nPntMax,bClosed);
//STRIP001      bControl=rHdl.IsPlusHdl();          // Punkt ist ein Kontrollpunkt
//STRIP001      bIsPrevControl=FALSE;               // Punkt ist Kontrollpunkt vor einem Stuetzpunkt
//STRIP001      bIsNextControl=FALSE;               // Punkt ist Kontrollpunkt hinter einem Stuetzpunkt
//STRIP001      bPrevIsControl=FALSE;               // Falls nPnt ein StPnt: Davor ist ein Kontrollpunkt
//STRIP001      bNextIsControl=FALSE;               // Falls nPnt ein StPnt: Dahinter ist ein Kontrollpunkt
//STRIP001      if (bControl) {
//STRIP001          bIsPrevControl=rXP.IsControl(nPrevPnt);
//STRIP001          bIsNextControl=!bIsPrevControl;
//STRIP001      } else {
//STRIP001          bPrevIsControl=!bBegPnt && !bPrevIsBegPnt && rXP.GetFlags(nPrevPnt)==XPOLY_CONTROL;
//STRIP001          bNextIsControl=!bEndPnt && !bNextIsEndPnt && rXP.GetFlags(nNextPnt)==XPOLY_CONTROL;
//STRIP001      }
//STRIP001      nPrevPrevPnt0=nPrevPrevPnt;
//STRIP001      nPrevPnt0    =nPrevPnt;
//STRIP001      nPnt0        =nPnt;
//STRIP001      nNextPnt0    =nNextPnt;
//STRIP001      nNextNextPnt0=nNextNextPnt;
//STRIP001      nPrevPrevPnt=0;
//STRIP001      nPrevPnt=1;
//STRIP001      nPnt=2;
//STRIP001      nNextPnt=3;
//STRIP001      nNextNextPnt=4;
//STRIP001      bEliminate=FALSE;
//STRIP001      ResetPoly(rPO);
//STRIP001      bValid=TRUE;
//STRIP001  }
//STRIP001 }

//STRIP001 void ImpSdrPathDragData::ResetPoly(const SdrPathObj& rPO)
//STRIP001 {
//STRIP001  const XPolygon& rXP=rPO.aPathPolygon[nPoly];     // Referenz auf das Polygon
//STRIP001  aXP[0]=rXP[nPrevPrevPnt0];  aXP.SetFlags(0,rXP.GetFlags(nPrevPrevPnt0));
//STRIP001  aXP[1]=rXP[nPrevPnt0];      aXP.SetFlags(1,rXP.GetFlags(nPrevPnt0));
//STRIP001  aXP[2]=rXP[nPnt0];          aXP.SetFlags(2,rXP.GetFlags(nPnt0));
//STRIP001  aXP[3]=rXP[nNextPnt0];      aXP.SetFlags(3,rXP.GetFlags(nNextPnt0));
//STRIP001  aXP[4]=rXP[nNextNextPnt0];  aXP.SetFlags(4,rXP.GetFlags(nNextNextPnt0));
//STRIP001 }

//STRIP001 class ImpPathCreateUser
//STRIP001 {
//STRIP001 public:
//STRIP001  Point                   aBezControl0;
//STRIP001  Point                   aBezStart;
//STRIP001  Point                   aBezCtrl1;
//STRIP001  Point                   aBezCtrl2;
//STRIP001  Point                   aBezEnd;
//STRIP001  Point                   aCircStart;
//STRIP001  Point                   aCircEnd;
//STRIP001  Point                   aCircCenter;
//STRIP001  Point                   aLineStart;
//STRIP001  Point                   aLineEnd;
//STRIP001  Point                   aRectP1;
//STRIP001  Point                   aRectP2;
//STRIP001  Point                   aRectP3;
//STRIP001  long                    nCircRadius;
//STRIP001  long                    nCircStWink;
//STRIP001  long                    nCircRelWink;
//STRIP001  FASTBOOL                bBezier;
//STRIP001  FASTBOOL                bBezHasCtrl0;
//STRIP001  FASTBOOL                bCurve;
//STRIP001  FASTBOOL                bCircle;
//STRIP001  FASTBOOL                bAngleSnap;
//STRIP001  FASTBOOL                bLine;
//STRIP001  FASTBOOL                bLine90;
//STRIP001  FASTBOOL                bRect;
//STRIP001  FASTBOOL                bMixedCreate;
//STRIP001  USHORT                  nBezierStartPoint;
//STRIP001  SdrObjKind              eStartKind;
//STRIP001  SdrObjKind              eAktKind;
//STRIP001
//STRIP001 public:
//STRIP001  ImpPathCreateUser(): nCircRadius(0),nCircStWink(0),nCircRelWink(0),
//STRIP001      bBezier(FALSE),bBezHasCtrl0(FALSE),bCurve(FALSE),bCircle(FALSE),bAngleSnap(FALSE),bLine(FALSE),bLine90(FALSE),bRect(FALSE),
//STRIP001      bMixedCreate(FALSE),nBezierStartPoint(0),eStartKind(OBJ_NONE),eAktKind(OBJ_NONE) { }
//STRIP001
//STRIP001  void ResetFormFlags() { bBezier=FALSE; bCurve=FALSE; bCircle=FALSE; bLine=FALSE; bRect=FALSE; }
//STRIP001  FASTBOOL IsFormFlag() const { return bBezier || bCurve || bCircle || bLine || bRect; }
//STRIP001  XPolygon GetFormPoly() const;
//STRIP001  FASTBOOL CalcBezier(const Point& rP1, const Point& rP2, const Point& rDir, FASTBOOL bMouseDown, SdrView* pView);
//STRIP001  XPolygon GetBezierPoly() const;
//STRIP001  FASTBOOL CalcCurve(const Point& rP1, const Point& rP2, const Point& rDir, SdrView* pView) { return FALSE; }
//STRIP001  XPolygon GetCurvePoly() const { return XPolygon(); }
//STRIP001  FASTBOOL CalcCircle(const Point& rP1, const Point& rP2, const Point& rDir, SdrView* pView);
//STRIP001  XPolygon GetCirclePoly() const;
//STRIP001  FASTBOOL CalcLine(const Point& rP1, const Point& rP2, const Point& rDir, SdrView* pView);
//STRIP001  Point    CalcLine(const Point& rCsr, long nDirX, long nDirY, SdrView* pView) const;
//STRIP001  XPolygon GetLinePoly() const;
//STRIP001  FASTBOOL CalcRect(const Point& rP1, const Point& rP2, const Point& rDir, SdrView* pView);
//STRIP001  XPolygon GetRectPoly() const;
//STRIP001 };

//STRIP001 XPolygon ImpPathCreateUser::GetFormPoly() const
//STRIP001 {
//STRIP001  if (bBezier) return GetBezierPoly();
//STRIP001  if (bCurve)  return GetCurvePoly();
//STRIP001  if (bCircle) return GetCirclePoly();
//STRIP001  if (bLine)   return GetLinePoly();
//STRIP001  if (bRect)   return GetRectPoly();
//STRIP001  return XPolygon();
//STRIP001 }

//STRIP001 FASTBOOL ImpPathCreateUser::CalcBezier(const Point& rP1, const Point& rP2, const Point& rDir, FASTBOOL bMouseDown, SdrView* pView)
//STRIP001 {
//STRIP001  FASTBOOL bRet=TRUE;
//STRIP001  aBezStart=rP1;
//STRIP001  aBezCtrl1=rP1+rDir;
//STRIP001  aBezCtrl2=rP2;
//STRIP001  if (!bMouseDown) aBezEnd=rP2;
//STRIP001  bBezier=bRet;
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 XPolygon ImpPathCreateUser::GetBezierPoly() const
//STRIP001 {
//STRIP001  XPolygon aXP(4);
//STRIP001  aXP[0]=aBezStart; aXP.SetFlags(0,XPOLY_SMOOTH);
//STRIP001  aXP[1]=aBezCtrl1; aXP.SetFlags(1,XPOLY_CONTROL);
//STRIP001  aXP[2]=aBezCtrl2; aXP.SetFlags(2,XPOLY_CONTROL);
//STRIP001  aXP[3]=aBezEnd;
//STRIP001  return aXP;
//STRIP001 }

//STRIP001 FASTBOOL ImpPathCreateUser::CalcCircle(const Point& rP1, const Point& rP2, const Point& rDir, SdrView* pView)
//STRIP001 {
//STRIP001  long nTangAngle=GetAngle(rDir);
//STRIP001  aCircStart=rP1;
//STRIP001  aCircEnd=rP2;
//STRIP001  aCircCenter=rP1;
//STRIP001  long dx=rP2.X()-rP1.X();
//STRIP001  long dy=rP2.Y()-rP1.Y();
//STRIP001  long dAngle=GetAngle(Point(dx,dy))-nTangAngle;
//STRIP001  dAngle=NormAngle360(dAngle);
//STRIP001  long nTmpAngle=NormAngle360(9000-dAngle);
//STRIP001  FASTBOOL bRet=nTmpAngle!=9000 && nTmpAngle!=27000;
//STRIP001  long nRad=0;
//STRIP001  if (bRet) {
//STRIP001      double cs=cos(nTmpAngle*nPi180);
//STRIP001      double nR=(double)GetLen(Point(dx,dy))/cs/2;
//STRIP001      nRad=Abs(Round(nR));
//STRIP001  }
//STRIP001  if (dAngle<18000) {
//STRIP001      nCircStWink=NormAngle360(nTangAngle-9000);
//STRIP001      nCircRelWink=NormAngle360(2*dAngle);
//STRIP001      aCircCenter.X()+=Round(nRad*cos((nTangAngle+9000)*nPi180));
//STRIP001      aCircCenter.Y()-=Round(nRad*sin((nTangAngle+9000)*nPi180));
//STRIP001  } else {
//STRIP001      nCircStWink=NormAngle360(nTangAngle+9000);
//STRIP001      nCircRelWink=-NormAngle360(36000-2*dAngle);
//STRIP001      aCircCenter.X()+=Round(nRad*cos((nTangAngle-9000)*nPi180));
//STRIP001      aCircCenter.Y()-=Round(nRad*sin((nTangAngle-9000)*nPi180));
//STRIP001  }
//STRIP001  bAngleSnap=pView!=NULL && pView->IsAngleSnapEnabled();
//STRIP001  if (bAngleSnap) {
//STRIP001      long nSA=pView->GetSnapAngle();
//STRIP001      if (nSA!=0) { // Winkelfang
//STRIP001          FASTBOOL bNeg=nCircRelWink<0;
//STRIP001          if (bNeg) nCircRelWink=-nCircRelWink;
//STRIP001          nCircRelWink+=nSA/2;
//STRIP001          nCircRelWink/=nSA;
//STRIP001          nCircRelWink*=nSA;
//STRIP001          nCircRelWink=NormAngle360(nCircRelWink);
//STRIP001          if (bNeg) nCircRelWink=-nCircRelWink;
//STRIP001      }
//STRIP001  }
//STRIP001  nCircRadius=nRad;
//STRIP001  if (nRad==0 || Abs(nCircRelWink)<5) bRet=FALSE;
//STRIP001  bCircle=bRet;
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 XPolygon ImpPathCreateUser::GetCirclePoly() const
//STRIP001 {
//STRIP001  if (nCircRelWink>=0) {
//STRIP001      XPolygon aXP(aCircCenter,nCircRadius,nCircRadius,
//STRIP001                   USHORT((nCircStWink+5)/10),USHORT((nCircStWink+nCircRelWink+5)/10),FALSE);
//STRIP001      aXP[0]=aCircStart; aXP.SetFlags(0,XPOLY_SMOOTH);
//STRIP001      if (!bAngleSnap) aXP[aXP.GetPointCount()-1]=aCircEnd;
//STRIP001      return aXP;
//STRIP001  } else {
//STRIP001      XPolygon aXP(aCircCenter,nCircRadius,nCircRadius,
//STRIP001                   USHORT(NormAngle360(nCircStWink+nCircRelWink+5)/10),USHORT((nCircStWink+5)/10),FALSE);
//STRIP001      USHORT nAnz=aXP.GetPointCount();
//STRIP001      for (USHORT nNum=nAnz/2; nNum>0;) {
//STRIP001          nNum--; // XPoly Punktreihenfolge umkehren
//STRIP001          USHORT n2=nAnz-nNum-1;
//STRIP001          Point aPt(aXP[nNum]);
//STRIP001          aXP[nNum]=aXP[n2];
//STRIP001          aXP[n2]=aPt;
//STRIP001      }
//STRIP001      aXP[0]=aCircStart; aXP.SetFlags(0,XPOLY_SMOOTH);
//STRIP001      if (!bAngleSnap) aXP[aXP.GetPointCount()-1]=aCircEnd;
//STRIP001      return aXP;
//STRIP001  }
//STRIP001 }

//STRIP001 Point ImpPathCreateUser::CalcLine(const Point& aCsr, long nDirX, long nDirY, SdrView* pView) const
//STRIP001 {
//STRIP001  long x=aCsr.X(),x1=x,x2=x;
//STRIP001  long y=aCsr.Y(),y1=y,y2=y;
//STRIP001  FASTBOOL bHLin=nDirY==0;
//STRIP001  FASTBOOL bVLin=nDirX==0;
//STRIP001  if (bHLin) y=0;
//STRIP001  else if (bVLin) x=0;
//STRIP001  else {
//STRIP001      x1=BigMulDiv(y,nDirX,nDirY);
//STRIP001      y2=BigMulDiv(x,nDirY,nDirX);
//STRIP001      long l1=Abs(x1)+Abs(y1);
//STRIP001      long l2=Abs(x2)+Abs(y2);
//STRIP001      if (l1<=l2 !=(pView!=NULL && pView->IsBigOrtho())) {
//STRIP001          x=x1; y=y1;
//STRIP001      } else {
//STRIP001          x=x2; y=y2;
//STRIP001      }
//STRIP001  }
//STRIP001  return Point(x,y);
//STRIP001 }

//STRIP001 FASTBOOL ImpPathCreateUser::CalcLine(const Point& rP1, const Point& rP2, const Point& rDir, SdrView* pView)
//STRIP001 {
//STRIP001  aLineStart=rP1;
//STRIP001  aLineEnd=rP2;
//STRIP001  bLine90=FALSE;
//STRIP001  if (rP1==rP2 || (rDir.X()==0 && rDir.Y()==0)) { bLine=FALSE; return FALSE; }
//STRIP001  Point aTmpPt(rP2-rP1);
//STRIP001  long nDirX=rDir.X();
//STRIP001  long nDirY=rDir.Y();
//STRIP001  Point aP1(CalcLine(aTmpPt, nDirX, nDirY,pView)); aP1-=aTmpPt; long nQ1=Abs(aP1.X())+Abs(aP1.Y());
//STRIP001  Point aP2(CalcLine(aTmpPt, nDirY,-nDirX,pView)); aP2-=aTmpPt; long nQ2=Abs(aP2.X())+Abs(aP2.Y());
//STRIP001  if (pView!=NULL && pView->IsOrtho()) nQ1=0; // Ortho schaltet rechtwinklig aus
//STRIP001  bLine90=nQ1>2*nQ2;
//STRIP001  if (!bLine90) { // glatter Uebergang
//STRIP001      aLineEnd+=aP1;
//STRIP001  } else {          // rechtwinkliger Uebergang
//STRIP001      aLineEnd+=aP2;
//STRIP001  }
//STRIP001  bLine=TRUE;
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 XPolygon ImpPathCreateUser::GetLinePoly() const
//STRIP001 {
//STRIP001  XPolygon aXP(2);
//STRIP001  aXP[0]=aLineStart; if (!bLine90) aXP.SetFlags(0,XPOLY_SMOOTH);
//STRIP001  aXP[1]=aLineEnd;
//STRIP001  return aXP;
//STRIP001 }

//STRIP001 FASTBOOL ImpPathCreateUser::CalcRect(const Point& rP1, const Point& rP2, const Point& rDir, SdrView* pView)
//STRIP001 {
//STRIP001  aRectP1=rP1;
//STRIP001  aRectP2=rP1;
//STRIP001  aRectP3=rP2;
//STRIP001  if (rP1==rP2 || (rDir.X()==0 && rDir.Y()==0)) { bRect=FALSE; return FALSE; }
//STRIP001  Point aTmpPt(rP2-rP1);
//STRIP001  long nDirX=rDir.X();
//STRIP001  long nDirY=rDir.Y();
//STRIP001  long x=aTmpPt.X();
//STRIP001  long y=aTmpPt.Y();
//STRIP001  FASTBOOL bHLin=nDirY==0;
//STRIP001  FASTBOOL bVLin=nDirX==0;
//STRIP001  if (bHLin) y=0;
//STRIP001  else if (bVLin) x=0;
//STRIP001  else {
//STRIP001      y=BigMulDiv(x,nDirY,nDirX);
//STRIP001      long nHypLen=aTmpPt.Y()-y;
//STRIP001      long nTangAngle=-GetAngle(rDir);
//STRIP001      // sin=g/h, g=h*sin
//STRIP001      double a=nTangAngle*nPi180;
//STRIP001      double sn=sin(a);
//STRIP001      double cs=cos(a);
//STRIP001      double nGKathLen=nHypLen*sn;
//STRIP001      y+=Round(nGKathLen*sn);
//STRIP001      x+=Round(nGKathLen*cs);
//STRIP001  }
//STRIP001  aRectP2.X()+=x;
//STRIP001  aRectP2.Y()+=y;
//STRIP001  if (pView!=NULL && pView->IsOrtho()) {
//STRIP001      long dx1=aRectP2.X()-aRectP1.X(); long dx1a=Abs(dx1);
//STRIP001      long dy1=aRectP2.Y()-aRectP1.Y(); long dy1a=Abs(dy1);
//STRIP001      long dx2=aRectP3.X()-aRectP2.X(); long dx2a=Abs(dx2);
//STRIP001      long dy2=aRectP3.Y()-aRectP2.Y(); long dy2a=Abs(dy2);
//STRIP001      FASTBOOL b1MoreThan2=dx1a+dy1a>dx2a+dy2a;
//STRIP001      if (b1MoreThan2 != pView->IsBigOrtho()) {
//STRIP001          long xtemp=dy2a-dx1a; if (dx1<0) xtemp=-xtemp;
//STRIP001          long ytemp=dx2a-dy1a; if (dy1<0) ytemp=-ytemp;
//STRIP001          aRectP2.X()+=xtemp;
//STRIP001          aRectP2.Y()+=ytemp;
//STRIP001          aRectP3.X()+=xtemp;
//STRIP001          aRectP3.Y()+=ytemp;
//STRIP001      } else {
//STRIP001          long xtemp=dy1a-dx2a; if (dx2<0) xtemp=-xtemp;
//STRIP001          long ytemp=dx1a-dy2a; if (dy2<0) ytemp=-ytemp;
//STRIP001          aRectP3.X()+=xtemp;
//STRIP001          aRectP3.Y()+=ytemp;
//STRIP001      }
//STRIP001  }
//STRIP001  bRect=TRUE;
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 XPolygon ImpPathCreateUser::GetRectPoly() const
//STRIP001 {
//STRIP001  XPolygon aXP(3);
//STRIP001  aXP[0]=aRectP1; aXP.SetFlags(0,XPOLY_SMOOTH);
//STRIP001  aXP[1]=aRectP2;
//STRIP001  if (aRectP3!=aRectP2) aXP[2]=aRectP3;
//STRIP001  return aXP;
//STRIP001 }

//STRIP001 FASTBOOL SdrPathObj::BegDrag(SdrDragStat& rDrag) const
//STRIP001 {
//STRIP001  const SdrHdl* pHdl=rDrag.GetHdl();
//STRIP001  if(!pHdl)
//STRIP001      return FALSE;
//STRIP001
//STRIP001  BOOL bMultiPointDrag(TRUE);
//STRIP001
//STRIP001  if(aPathPolygon[pHdl->GetPolyNum()].IsControl(pHdl->GetPointNum()))
//STRIP001      bMultiPointDrag = FALSE;
//STRIP001
//STRIP001  if(bMultiPointDrag)
//STRIP001  {
//STRIP001      const SdrMarkView& rMarkView = *rDrag.GetView();
//STRIP001      const SdrHdlList& rHdlList = rMarkView.GetHdlList();
//STRIP001      const sal_uInt32 nHdlCount = rHdlList.GetHdlCount();
//STRIP001      sal_uInt32 nSelectedPoints(0);
//STRIP001
//STRIP001      for(sal_uInt32 a(0); a < nHdlCount; a++)
//STRIP001      {
//STRIP001          SdrHdl* pTestHdl = rHdlList.GetHdl(a);
//STRIP001
//STRIP001          if(pTestHdl
//STRIP001              && pTestHdl->IsSelected()
//STRIP001              && pTestHdl->GetObj() == (SdrObject*)this)
//STRIP001          {
//STRIP001              nSelectedPoints++;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if(nSelectedPoints <= 1)
//STRIP001          bMultiPointDrag = FALSE;
//STRIP001  }
//STRIP001
//STRIP001  ImpSdrPathDragData* pID=new ImpSdrPathDragData(*this,*pHdl,bMultiPointDrag,rDrag);
//STRIP001  if (!pID->bValid) {
//STRIP001      DBG_ERROR("SdrPathObj::BegDrag(): ImpSdrPathDragData ist ungueltig");
//STRIP001      delete pID;
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  rDrag.SetUser(pID);
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 FASTBOOL SdrPathObj::MovDrag(SdrDragStat& rDrag) const
//STRIP001 {
//STRIP001  ImpSdrPathDragData* pID=(ImpSdrPathDragData*)rDrag.GetUser();
//STRIP001  if (pID==NULL || !pID->bValid) {
//STRIP001      DBG_ERROR("SdrPathObj::MovDrag(): ImpSdrPathDragData ist ungueltig");
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  if(pID->IsMultiPointDrag())
//STRIP001  {
//STRIP001      Point aDelta(rDrag.GetNow() - rDrag.GetStart());
//STRIP001
//STRIP001      if(aDelta.X() || aDelta.Y())
//STRIP001      {
//STRIP001          for(sal_uInt32 a(0); a < pID->maHandles.Count(); a++)
//STRIP001          {
//STRIP001              SdrHdl* pHandle = (SdrHdl*)pID->maHandles.GetObject(a);
//STRIP001              const sal_uInt16 nPolyIndex(pHandle->GetPolyNum());
//STRIP001              const sal_uInt16 nPointIndex(pHandle->GetPointNum());
//STRIP001              const XPolygon& rOrig = pID->mrOrig[nPolyIndex];
//STRIP001              XPolygon& rMove = pID->maMove[nPolyIndex];
//STRIP001              const sal_uInt16 nPointCount(rOrig.GetPointCount());
//STRIP001              BOOL bClosed(rOrig[0] == rOrig[nPointCount-1]);
//STRIP001
//STRIP001              // move point itself
//STRIP001              rMove[nPointIndex] = rOrig[nPointIndex] + aDelta;
//STRIP001
//STRIP001              // when point is first and poly closed, move close point, too.
//STRIP001              if(nPointCount > 0 && !nPointIndex && bClosed)
//STRIP001              {
//STRIP001                  rMove[nPointCount - 1] = rOrig[nPointCount - 1] + aDelta;
//STRIP001
//STRIP001                  // when moving the last point it may be necessary to move the
//STRIP001                  // control point in front of this one, too.
//STRIP001                  if(nPointCount > 1 && rOrig.IsControl(nPointCount - 2))
//STRIP001                      rMove[nPointCount - 2] = rOrig[nPointCount - 2] + aDelta;
//STRIP001              }
//STRIP001
//STRIP001              // is a control point before this?
//STRIP001              if(nPointIndex > 0 && rOrig.IsControl(nPointIndex - 1))
//STRIP001              {
//STRIP001                  // Yes, move it, too
//STRIP001                  rMove[nPointIndex - 1] = rOrig[nPointIndex - 1] + aDelta;
//STRIP001              }
//STRIP001
//STRIP001              // is a control point after this?
//STRIP001              if(nPointIndex + 1 < nPointCount && rOrig.IsControl(nPointIndex + 1))
//STRIP001              {
//STRIP001                  // Yes, move it, too
//STRIP001                  rMove[nPointIndex + 1] = rOrig[nPointIndex + 1] + aDelta;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pID->ResetPoly(*this);
//STRIP001
//STRIP001      // Div. Daten lokal Kopieren fuer weniger Code und schnelleren Zugriff
//STRIP001      FASTBOOL bClosed       =pID->bClosed       ; // geschlossenes Objekt?
//STRIP001      USHORT   nPnt          =pID->nPnt          ; // Punktnummer innerhalb des obigen Polygons
//STRIP001      FASTBOOL bBegPnt       =pID->bBegPnt       ; // Gedraggter Punkt ist der Anfangspunkt einer Polyline
//STRIP001      FASTBOOL bEndPnt       =pID->bEndPnt       ; // Gedraggter Punkt ist der Endpunkt einer Polyline
//STRIP001      USHORT   nPrevPnt      =pID->nPrevPnt      ; // Index des vorherigen Punkts
//STRIP001      USHORT   nNextPnt      =pID->nNextPnt      ; // Index des naechsten Punkts
//STRIP001      FASTBOOL bPrevIsBegPnt =pID->bPrevIsBegPnt ; // Vorheriger Punkt ist Anfangspunkt einer Polyline
//STRIP001      FASTBOOL bNextIsEndPnt =pID->bNextIsEndPnt ; // Folgepunkt ist Endpunkt einer Polyline
//STRIP001      USHORT   nPrevPrevPnt  =pID->nPrevPrevPnt  ; // Index des vorvorherigen Punkts
//STRIP001      USHORT   nNextNextPnt  =pID->nNextNextPnt  ; // Index des uebernaechsten Punkts
//STRIP001      FASTBOOL bControl      =pID->bControl      ; // Punkt ist ein Kontrollpunkt
//STRIP001      FASTBOOL bIsPrevControl=pID->bIsPrevControl; // Punkt ist Kontrollpunkt vor einem Stuetzpunkt
//STRIP001      FASTBOOL bIsNextControl=pID->bIsNextControl; // Punkt ist Kontrollpunkt hinter einem Stuetzpunkt
//STRIP001      FASTBOOL bPrevIsControl=pID->bPrevIsControl; // Falls nPnt ein StPnt: Davor ist ein Kontrollpunkt
//STRIP001      FASTBOOL bNextIsControl=pID->bNextIsControl; // Falls nPnt ein StPnt: Dahinter ist ein Kontrollpunkt
//STRIP001
//STRIP001      // Ortho bei Linien/Polygonen = Winkel beibehalten
//STRIP001      if (!bControl && rDrag.GetView()!=NULL && rDrag.GetView()->IsOrtho()) {
//STRIP001          FASTBOOL bBigOrtho=rDrag.GetView()->IsBigOrtho();
//STRIP001          Point  aPos(rDrag.GetNow());      // die aktuelle Position
//STRIP001          Point  aPnt(pID->aXP[nPnt]);      // der gedraggte Punkt
//STRIP001          USHORT nPnt1=0xFFFF,nPnt2=0xFFFF; // seine Nachbarpunkte
//STRIP001          Point  aNeuPos1,aNeuPos2;         // die neuen Alternativen fuer aPos
//STRIP001          FASTBOOL bPnt1=FALSE,bPnt2=FALSE; // die neuen Alternativen gueltig?
//STRIP001          if (!bClosed && pID->nPntAnz>=2) { // Mind. 2 Pt bei Linien
//STRIP001              if (!bBegPnt) nPnt1=nPrevPnt;
//STRIP001              if (!bEndPnt) nPnt2=nNextPnt;
//STRIP001          }
//STRIP001          if (bClosed && pID->nPntAnz>=3) { // Mind. 3 Pt bei Polygon
//STRIP001              nPnt1=nPrevPnt;
//STRIP001              nPnt2=nNextPnt;
//STRIP001          }
//STRIP001          if (nPnt1!=0xFFFF && !bPrevIsControl) {
//STRIP001              Point aPnt1=pID->aXP[nPnt1];
//STRIP001              long ndx0=aPnt.X()-aPnt1.X();
//STRIP001              long ndy0=aPnt.Y()-aPnt1.Y();
//STRIP001              FASTBOOL bHLin=ndy0==0;
//STRIP001              FASTBOOL bVLin=ndx0==0;
//STRIP001              if (!bHLin || !bVLin) {
//STRIP001                  long ndx=aPos.X()-aPnt1.X();
//STRIP001                  long ndy=aPos.Y()-aPnt1.Y();
//STRIP001                  bPnt1=TRUE;
//STRIP001                  double nXFact=0; if (!bVLin) nXFact=(double)ndx/(double)ndx0;
//STRIP001                  double nYFact=0; if (!bHLin) nYFact=(double)ndy/(double)ndy0;
//STRIP001                  FASTBOOL bHor=bHLin || (!bVLin && (nXFact>nYFact) ==bBigOrtho);
//STRIP001                  FASTBOOL bVer=bVLin || (!bHLin && (nXFact<=nYFact)==bBigOrtho);
//STRIP001                  if (bHor) ndy=long(ndy0*nXFact);
//STRIP001                  if (bVer) ndx=long(ndx0*nYFact);
//STRIP001                  aNeuPos1=aPnt1;
//STRIP001                  aNeuPos1.X()+=ndx;
//STRIP001                  aNeuPos1.Y()+=ndy;
//STRIP001              }
//STRIP001          }
//STRIP001          if (nPnt2!=0xFFFF && !bNextIsControl) {
//STRIP001              Point aPnt2=pID->aXP[nPnt2];
//STRIP001              long ndx0=aPnt.X()-aPnt2.X();
//STRIP001              long ndy0=aPnt.Y()-aPnt2.Y();
//STRIP001              FASTBOOL bHLin=ndy0==0;
//STRIP001              FASTBOOL bVLin=ndx0==0;
//STRIP001              if (!bHLin || !bVLin) {
//STRIP001                  long ndx=aPos.X()-aPnt2.X();
//STRIP001                  long ndy=aPos.Y()-aPnt2.Y();
//STRIP001                  bPnt2=TRUE;
//STRIP001                  double nXFact=0; if (!bVLin) nXFact=(double)ndx/(double)ndx0;
//STRIP001                  double nYFact=0; if (!bHLin) nYFact=(double)ndy/(double)ndy0;
//STRIP001                  FASTBOOL bHor=bHLin || (!bVLin && (nXFact>nYFact) ==bBigOrtho);
//STRIP001                  FASTBOOL bVer=bVLin || (!bHLin && (nXFact<=nYFact)==bBigOrtho);
//STRIP001                  if (bHor) ndy=long(ndy0*nXFact);
//STRIP001                  if (bVer) ndx=long(ndx0*nYFact);
//STRIP001                  aNeuPos2=aPnt2;
//STRIP001                  aNeuPos2.X()+=ndx;
//STRIP001                  aNeuPos2.Y()+=ndy;
//STRIP001              }
//STRIP001          }
//STRIP001          if (bPnt1 && bPnt2) { // beide Alternativen vorhanden (Konkurenz)
//STRIP001              BigInt nX1(aNeuPos1.X()-aPos.X()); nX1*=nX1;
//STRIP001              BigInt nY1(aNeuPos1.Y()-aPos.Y()); nY1*=nY1;
//STRIP001              BigInt nX2(aNeuPos2.X()-aPos.X()); nX2*=nX2;
//STRIP001              BigInt nY2(aNeuPos2.Y()-aPos.Y()); nY2*=nY2;
//STRIP001              nX1+=nY1; // Korrekturabstand zum Quadrat
//STRIP001              nX2+=nY2; // Korrekturabstand zum Quadrat
//STRIP001              // Die Alternative mit dem geringeren Korrekturbedarf gewinnt
//STRIP001              if (nX1<nX2) bPnt2=FALSE; else bPnt1=FALSE;
//STRIP001          }
//STRIP001          if (bPnt1) rDrag.Now()=aNeuPos1;
//STRIP001          if (bPnt2) rDrag.Now()=aNeuPos2;
//STRIP001      }
//STRIP001      rDrag.SetActionRect(Rectangle(rDrag.GetNow(),rDrag.GetNow()));
//STRIP001
//STRIP001      // IBM Special: Punkte eliminieren, wenn die beiden angrenzenden
//STRIP001      //              Linien eh' fast 180 deg sind.
//STRIP001      if (!bControl && rDrag.GetView()!=NULL && rDrag.GetView()->IsEliminatePolyPoints() &&
//STRIP001          !bBegPnt && !bEndPnt && !bPrevIsControl && !bNextIsControl)
//STRIP001      {
//STRIP001          Point aPt(pID->aXP[nNextPnt]);
//STRIP001          aPt-=rDrag.GetNow();
//STRIP001          long nWink1=GetAngle(aPt);
//STRIP001          aPt=rDrag.GetNow();
//STRIP001          aPt-=pID->aXP[nPrevPnt];
//STRIP001          long nWink2=GetAngle(aPt);
//STRIP001          long nDiff=nWink1-nWink2;
//STRIP001          nDiff=Abs(nDiff);
//STRIP001          pID->bEliminate=nDiff<=rDrag.GetView()->GetEliminatePolyPointLimitAngle();
//STRIP001          if (pID->bEliminate) { // Position anpassen, damit Smooth an den Enden stimmt
//STRIP001              aPt=pID->aXP[nNextPnt];
//STRIP001              aPt+=pID->aXP[nPrevPnt];
//STRIP001              aPt/=2;
//STRIP001              rDrag.Now()=aPt;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // Um diese Entfernung wurde insgesamt gedraggd
//STRIP001      Point aDiff(rDrag.GetNow()); aDiff-=pID->aXP[nPnt];
//STRIP001
//STRIP001      // Insgesamt sind 8 Faelle moeglich:
//STRIP001      //    X      1. Weder rechts noch links Ctrl.
//STRIP001      // o--X--o   2. Rechts und links Ctrl, gedraggd wird St.
//STRIP001      // o--X      3. Nur links Ctrl, gedraggd wird St.
//STRIP001      //    X--o   4. Nur rechts Ctrl, gedraggd wird St.
//STRIP001      // x--O--o   5. Rechts und links Ctrl, gedraggd wird links.
//STRIP001      // x--O      6. Nur links Ctrl, gedraggd wird links.
//STRIP001      // o--O--x   7. Rechts und links Ctrl, gedraggd wird rechts.
//STRIP001      //    O--x   8. Nur rechts Ctrl, gedraggd wird rechts.
//STRIP001      // Zusaetzlich ist zu beachten, dass das Veraendern einer Linie (keine Kurve)
//STRIP001      // eine evtl. Kurve am anderen Ende der Linie bewirkt, falls dort Smooth
//STRIP001      // gesetzt ist (Kontrollpunktausrichtung an Gerade).
//STRIP001
//STRIP001      pID->aXP[nPnt]+=aDiff; // <<<<<<<<<<
//STRIP001
//STRIP001      // Nun symmetrische PlusHandles etc. checken
//STRIP001      if (bControl) { // Faelle 5,6,7,8
//STRIP001          USHORT   nSt=nPnt;   // der zugehoerige Stuetzpunkt
//STRIP001          USHORT   nFix=nPnt;  // der gegenueberliegende Kontrollpunkt
//STRIP001          if (bIsNextControl) { // Wenn der naechste ein Kontrollpunkt ist, muss der vorh. der Stuetzpunkt sein
//STRIP001              nSt=nPrevPnt;
//STRIP001              nFix=nPrevPrevPnt;
//STRIP001          } else {
//STRIP001              nSt=nNextPnt;
//STRIP001              nFix=nNextNextPnt;
//STRIP001          }
//STRIP001          if (pID->aXP.IsSmooth(nSt)) {
//STRIP001              pID->aXP.CalcSmoothJoin(nSt,nPnt,nFix); // <<<<<<<<<<
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if (!bControl) { // Faelle 1,2,3,4 wobei bei 1 nix passiert und bei 3+4 unten noch mehr folgt
//STRIP001          // die beiden Kontrollpunkte mit verschieben
//STRIP001          if (bPrevIsControl) pID->aXP[nPrevPnt]+=aDiff; // <<<<<<<<<<
//STRIP001          if (bNextIsControl) pID->aXP[nNextPnt]+=aDiff; // <<<<<<<<<<
//STRIP001          // Kontrollpunkt ggf. an Gerade ausrichten
//STRIP001          if (pID->aXP.IsSmooth(nPnt)) {
//STRIP001              if (bPrevIsControl && !bNextIsControl && !bEndPnt) { // Fall 3
//STRIP001                  pID->aXP.CalcSmoothJoin(nPnt,nNextPnt,nPrevPnt); // <<<<<<<<<<
//STRIP001              }
//STRIP001              if (bNextIsControl && !bPrevIsControl && !bBegPnt) { // Fall 4
//STRIP001                  pID->aXP.CalcSmoothJoin(nPnt,nPrevPnt,nNextPnt); // <<<<<<<<<<
//STRIP001              }
//STRIP001          }
//STRIP001          // Und nun noch die anderen Enden der Strecken ueberpruefen (nPnt+-1).
//STRIP001          // Ist dort eine Kurve (IsControl(nPnt+-2)) mit SmoothJoin (nPnt+-1),
//STRIP001          // so muss der entsprechende Kontrollpunkt (nPnt+-2) angepasst werden.
//STRIP001          if (!bBegPnt && !bPrevIsControl && !bPrevIsBegPnt && pID->aXP.IsSmooth(nPrevPnt)) {
//STRIP001              if (pID->aXP.IsControl(nPrevPrevPnt)) {
//STRIP001                  pID->aXP.CalcSmoothJoin(nPrevPnt,nPnt,nPrevPrevPnt); // <<<<<<<<<<
//STRIP001              }
//STRIP001          }
//STRIP001          if (!bEndPnt && !bNextIsControl && !bNextIsEndPnt && pID->aXP.IsSmooth(nNextPnt)) {
//STRIP001              if (pID->aXP.IsControl(nNextNextPnt)) {
//STRIP001                  pID->aXP.CalcSmoothJoin(nNextPnt,nPnt,nNextNextPnt); // <<<<<<<<<<
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 FASTBOOL SdrPathObj::EndDrag(SdrDragStat& rDrag)
//STRIP001 {
//STRIP001  Point aLinePt1;
//STRIP001  Point aLinePt2;
//STRIP001  FASTBOOL bLineGlueMirror=eKind==OBJ_LINE;
//STRIP001  if (bLineGlueMirror) { // #40549#
//STRIP001      XPolygon& rXP=aPathPolygon[0];
//STRIP001      aLinePt1=rXP[0];
//STRIP001      aLinePt2=rXP[1];
//STRIP001  }
//STRIP001  ImpSdrPathDragData* pID=(ImpSdrPathDragData*)rDrag.GetUser();
//STRIP001
//STRIP001  if(pID->IsMultiPointDrag())
//STRIP001  {
//STRIP001      SetPathPoly(pID->maMove);
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      const SdrHdl* pHdl=rDrag.GetHdl();
//STRIP001      if (pID==NULL || !pID->bValid) {
//STRIP001          DBG_ERROR("SdrPathObj::EndDrag(): ImpSdrPathDragData ist ungueltig");
//STRIP001          return FALSE;
//STRIP001      }
//STRIP001      Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001      SendRepaintBroadcast();
//STRIP001      // Referenz auf das Polygon
//STRIP001      XPolygon& rXP=aPathPolygon[pHdl->GetPolyNum()];
//STRIP001
//STRIP001      // Die 5 Punkte die sich evtl. geaendert haben
//STRIP001      if (!pID->bPrevIsBegPnt) rXP[pID->nPrevPrevPnt0]=pID->aXP[pID->nPrevPrevPnt];
//STRIP001      if (!pID->bNextIsEndPnt) rXP[pID->nNextNextPnt0]=pID->aXP[pID->nNextNextPnt];
//STRIP001      if (!pID->bBegPnt)       rXP[pID->nPrevPnt0]    =pID->aXP[pID->nPrevPnt];
//STRIP001      if (!pID->bEndPnt)       rXP[pID->nNextPnt0]    =pID->aXP[pID->nNextPnt];
//STRIP001                               rXP[pID->nPnt0]        =pID->aXP[pID->nPnt];
//STRIP001
//STRIP001      // Letzter Punkt muss beim Geschlossenen immer gleich dem Ersten sein
//STRIP001      if (pID->bClosed) rXP[rXP.GetPointCount()-1]=rXP[0];
//STRIP001      if (pID->bEliminate) {
//STRIP001          NbcDelPoint(rDrag.GetHdl()->GetSourceHdlNum());
//STRIP001      }
//STRIP001      ImpForceKind(); // Wg. impliziter Punktloeschung evtl. von PolyLine nach Line
//STRIP001      // Winkel anpassen fuer Text an einfacher Linie
//STRIP001      SetRectsDirty();
//STRIP001      if (bLineGlueMirror) { // #40549#
//STRIP001          XPolygon& rXP=aPathPolygon[0];
//STRIP001          Point aLinePt1_(rXP[0]);
//STRIP001          Point aLinePt2_(rXP[1]);
//STRIP001          FASTBOOL bXMirr=(aLinePt1_.X()>aLinePt2_.X())!=(aLinePt1.X()>aLinePt2.X());
//STRIP001          FASTBOOL bYMirr=(aLinePt1_.Y()>aLinePt2_.Y())!=(aLinePt1.Y()>aLinePt2.Y());
//STRIP001          if (bXMirr || bYMirr) {
//STRIP001              Point aRef1(GetSnapRect().Center());
//STRIP001              if (bXMirr) {
//STRIP001                  Point aRef2(aRef1);
//STRIP001                  aRef2.Y()++;
//STRIP001                  NbcMirrorGluePoints(aRef1,aRef2);
//STRIP001              }
//STRIP001              if (bYMirr) {
//STRIP001                  Point aRef2(aRef1);
//STRIP001                  aRef2.X()++;
//STRIP001                  NbcMirrorGluePoints(aRef1,aRef2);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      SetChanged();
//STRIP001      SendRepaintBroadcast();
//STRIP001      SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001  }
//STRIP001
//STRIP001  delete pID;
//STRIP001  rDrag.SetUser(NULL);
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 void SdrPathObj::BrkDrag(SdrDragStat& rDrag) const
//STRIP001 {
//STRIP001  ImpSdrPathDragData* pID=(ImpSdrPathDragData*)rDrag.GetUser();
//STRIP001  if (pID!=NULL) {
//STRIP001      delete pID;
//STRIP001      rDrag.SetUser(NULL);
//STRIP001  }
//STRIP001 }

//STRIP001 XubString SdrPathObj::GetDragComment(const SdrDragStat& rDrag, FASTBOOL bUndoDragComment, FASTBOOL bCreateComment) const
//STRIP001 {
//STRIP001  ImpSdrPathDragData* pID = (ImpSdrPathDragData*)rDrag.GetUser();
//STRIP001
//STRIP001  if(!pID || !pID->bValid)
//STRIP001      return String();
//STRIP001
//STRIP001  // Hier auch mal pID verwenden !!!
//STRIP001  XubString aStr;
//STRIP001
//STRIP001  if(!bCreateComment)
//STRIP001  {
//STRIP001      const SdrHdl* pHdl = rDrag.GetHdl();
//STRIP001
//STRIP001      if(bUndoDragComment || !pModel || !pHdl)
//STRIP001      {
//STRIP001          ImpTakeDescriptionStr(STR_DragPathObj, aStr);
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if(!pID->IsMultiPointDrag() && pID->bEliminate)
//STRIP001          {
//STRIP001              // Punkt von ...
//STRIP001              ImpTakeDescriptionStr(STR_ViewMarkedPoint, aStr);
//STRIP001
//STRIP001              // %O loeschen
//STRIP001              XubString aStr2(ImpGetResStr(STR_EditDelete));
//STRIP001
//STRIP001              // UNICODE: Punkt von ... loeschen
//STRIP001              aStr2.SearchAndReplaceAscii("%O", aStr);
//STRIP001
//STRIP001              return aStr2;
//STRIP001          }
//STRIP001
//STRIP001          // dx=0.00 dy=0.00                // Beide Seiten Bezier
//STRIP001          // dx=0.00 dy=0.00  l=0.00 0.00ø  // Anfang oder Ende oder eine Seite Bezier bzw. Hebel
//STRIP001          // dx=0.00 dy=0.00  l=0.00 0.00ø / l=0.00 0.00ø   // Mittendrin
//STRIP001          XubString aMetr;
//STRIP001          Point aBeg(rDrag.GetStart());
//STRIP001          Point aNow(rDrag.GetNow());
//STRIP001
//STRIP001          aStr = String();
//STRIP001          aStr.AppendAscii("dx=");
//STRIP001          pModel->TakeMetricStr(aNow.X() - aBeg.X(), aMetr, TRUE);
//STRIP001          aStr += aMetr;
//STRIP001
//STRIP001          aStr.AppendAscii(" dy=");
//STRIP001          pModel->TakeMetricStr(aNow.Y() - aBeg.Y(), aMetr, TRUE);
//STRIP001          aStr += aMetr;
//STRIP001
//STRIP001          if(!pID->IsMultiPointDrag())
//STRIP001          {
//STRIP001              UINT16 nPntNum(pHdl->GetPointNum());
//STRIP001              const XPolygon& rXPoly = aPathPolygon[rDrag.GetHdl()->GetPolyNum()];
//STRIP001              UINT16 nPntAnz(rXPoly.GetPointCount());
//STRIP001              BOOL bClose(IsClosed());
//STRIP001
//STRIP001              if(bClose)
//STRIP001                  nPntAnz--;
//STRIP001
//STRIP001              if(pHdl->IsPlusHdl())
//STRIP001              {
//STRIP001                  // Hebel
//STRIP001                  UINT16 nRef(nPntNum);
//STRIP001
//STRIP001                  if(rXPoly.IsControl(nPntNum + 1))
//STRIP001                      nRef--;
//STRIP001                  else
//STRIP001                      nRef++;
//STRIP001
//STRIP001                  aNow -= rXPoly[nRef];
//STRIP001
//STRIP001                  INT32 nLen(GetLen(aNow));
//STRIP001                  aStr.AppendAscii("  l=");
//STRIP001                  pModel->TakeMetricStr(nLen, aMetr, TRUE);
//STRIP001                  aStr += aMetr;
//STRIP001
//STRIP001                  INT32 nWink(GetAngle(aNow));
//STRIP001                  aStr += sal_Unicode(' ');
//STRIP001                  pModel->TakeWinkStr(nWink, aMetr);
//STRIP001                  aStr += aMetr;
//STRIP001              }
//STRIP001              else if(nPntAnz > 1)
//STRIP001              {
//STRIP001                  UINT16 nPntMax(nPntAnz - 1);
//STRIP001                  Point aPt1,aPt2;
//STRIP001                  BOOL bClose(IsClosed());
//STRIP001                  BOOL bPt1(nPntNum > 0);
//STRIP001                  BOOL bPt2(nPntNum < nPntMax);
//STRIP001
//STRIP001                  if(bClose && nPntAnz > 2)
//STRIP001                  {
//STRIP001                      bPt1 = TRUE;
//STRIP001                      bPt2 = TRUE;
//STRIP001                  }
//STRIP001
//STRIP001                  UINT16 nPt1,nPt2;
//STRIP001
//STRIP001                  if(nPntNum > 0)
//STRIP001                      nPt1 = nPntNum - 1;
//STRIP001                  else
//STRIP001                      nPt1 = nPntMax;
//STRIP001
//STRIP001                  if(nPntNum < nPntMax)
//STRIP001                      nPt2 = nPntNum + 1;
//STRIP001                  else
//STRIP001                      nPt2 = 0;
//STRIP001
//STRIP001                  if(bPt1 && rXPoly.IsControl(nPt1))
//STRIP001                      bPt1 = FALSE; // Keine Anzeige
//STRIP001
//STRIP001                  if(bPt2 && rXPoly.IsControl(nPt2))
//STRIP001                      bPt2 = FALSE; // von Bezierdaten
//STRIP001
//STRIP001                  if(bPt1)
//STRIP001                  {
//STRIP001                      Point aPt(aNow);
//STRIP001                      aPt -= rXPoly[nPt1];
//STRIP001
//STRIP001                      INT32 nLen(GetLen(aPt));
//STRIP001                      aStr.AppendAscii("  l=");
//STRIP001                      pModel->TakeMetricStr(nLen, aMetr, TRUE);
//STRIP001                      aStr += aMetr;
//STRIP001
//STRIP001                      INT32 nWink(GetAngle(aPt));
//STRIP001                      aStr += sal_Unicode(' ');
//STRIP001                      pModel->TakeWinkStr(nWink, aMetr);
//STRIP001                      aStr += aMetr;
//STRIP001                  }
//STRIP001
//STRIP001                  if(bPt2)
//STRIP001                  {
//STRIP001                      if(bPt1)
//STRIP001                          aStr.AppendAscii(" / ");
//STRIP001                      else
//STRIP001                          aStr.AppendAscii("  ");
//STRIP001
//STRIP001                      Point aPt(aNow);
//STRIP001                      aPt -= rXPoly[nPt2];
//STRIP001
//STRIP001                      INT32 nLen(GetLen(aPt));
//STRIP001                      aStr.AppendAscii("l=");
//STRIP001                      pModel->TakeMetricStr(nLen, aMetr, TRUE);
//STRIP001                      aStr += aMetr;
//STRIP001
//STRIP001                      INT32 nWink(GetAngle(aPt));
//STRIP001                      aStr += sal_Unicode(' ');
//STRIP001                      pModel->TakeWinkStr(nWink, aMetr);
//STRIP001                      aStr += aMetr;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else if(pModel && !pID->IsMultiPointDrag())
//STRIP001  {
//STRIP001      // Ansonsten CreateComment
//STRIP001      ImpPathCreateUser* pU = (ImpPathCreateUser*)rDrag.GetUser();
//STRIP001      SdrObjKind eKindMerk = eKind;
//STRIP001
//STRIP001      // fuer Description bei Mixed das Aktuelle...
//STRIP001      ((SdrPathObj*)this)->eKind = pU->eAktKind;
//STRIP001      ImpTakeDescriptionStr(STR_ViewCreateObj, aStr);
//STRIP001      ((SdrPathObj*)this)->eKind = eKindMerk;
//STRIP001
//STRIP001      Point aPrev(rDrag.GetPrev());
//STRIP001      Point aNow(rDrag.GetNow());
//STRIP001
//STRIP001      if(pU->bLine)
//STRIP001          aNow = pU->aLineEnd;
//STRIP001
//STRIP001      aNow -= aPrev;
//STRIP001      aStr.AppendAscii(" (");
//STRIP001
//STRIP001      XubString aMetr;
//STRIP001
//STRIP001      if(pU->bCircle)
//STRIP001      {
//STRIP001          pModel->TakeWinkStr(Abs(pU->nCircRelWink), aMetr);
//STRIP001          aStr += aMetr;
//STRIP001          aStr.AppendAscii(" r=");
//STRIP001          pModel->TakeMetricStr(pU->nCircRadius, aMetr, TRUE);
//STRIP001          aStr += aMetr;
//STRIP001      }
//STRIP001
//STRIP001      aStr.AppendAscii("dx=");
//STRIP001      pModel->TakeMetricStr(aNow.X(), aMetr, TRUE);
//STRIP001      aStr += aMetr;
//STRIP001
//STRIP001      aStr.AppendAscii(" dy=");
//STRIP001      pModel->TakeMetricStr(aNow.Y(), aMetr, TRUE);
//STRIP001      aStr += aMetr;
//STRIP001
//STRIP001      if(!IsFreeHand())
//STRIP001      {
//STRIP001          INT32 nLen(GetLen(aNow));
//STRIP001          aStr.AppendAscii("  l=");
//STRIP001          pModel->TakeMetricStr(nLen, aMetr, TRUE);
//STRIP001          aStr += aMetr;
//STRIP001
//STRIP001          INT32 nWink(GetAngle(aNow));
//STRIP001          aStr += sal_Unicode(' ');
//STRIP001          pModel->TakeWinkStr(nWink, aMetr);
//STRIP001          aStr += aMetr;
//STRIP001      }
//STRIP001
//STRIP001      aStr += sal_Unicode(')');
//STRIP001  }
//STRIP001
//STRIP001  return aStr;
//STRIP001 }

//STRIP001 void lcl_CopyBezier(const XPolygon& rSrc, USHORT nSPos, XPolygon& rDst, USHORT nDPos)
//STRIP001 {
//STRIP001  rDst[nDPos++] = rSrc[nSPos++];
//STRIP001  rDst.SetFlags(nDPos, XPOLY_CONTROL);
//STRIP001  rDst[nDPos++] = rSrc[nSPos++];
//STRIP001  rDst.SetFlags(nDPos, XPOLY_CONTROL);
//STRIP001  rDst[nDPos++] = rSrc[nSPos++];
//STRIP001  rDst[nDPos] = rSrc[nSPos];
//STRIP001 }

//STRIP001 void SdrPathObj::TakeDragPoly(const SdrDragStat& rDrag, XPolyPolygon& rXPP) const
//STRIP001 {
//STRIP001  rXPP.Clear();
//STRIP001  ImpSdrPathDragData* pID=(ImpSdrPathDragData*)rDrag.GetUser();
//STRIP001
//STRIP001  if(pID->IsMultiPointDrag())
//STRIP001  {
//STRIP001      rXPP.Insert(pID->maMove);
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      const XPolygon& rXP=aPathPolygon[rDrag.GetHdl()->GetPolyNum()];
//STRIP001      if (rXP.GetPointCount()<=2 /*|| rXPoly.GetFlags(1)==XPOLY_CONTROL && rXPoly.GetPointCount()<=4*/) {
//STRIP001          XPolygon aXPoly(rXP);
//STRIP001          aXPoly[rDrag.GetHdl()->GetPointNum()]=rDrag.GetNow();
//STRIP001          rXPP.Insert(aXPoly);
//STRIP001          return;
//STRIP001      }
//STRIP001      // Div. Daten lokal Kopieren fuer weniger Code und schnelleren Zugriff
//STRIP001      FASTBOOL bClosed       =pID->bClosed       ; // geschlossenes Objekt?
//STRIP001      USHORT   nPntAnz       =pID->nPntAnz       ; // Punktanzahl
//STRIP001      USHORT   nPnt          =pID->nPnt          ; // Punktnummer innerhalb des Polygons
//STRIP001      FASTBOOL bBegPnt       =pID->bBegPnt       ; // Gedraggter Punkt ist der Anfangspunkt einer Polyline
//STRIP001      FASTBOOL bEndPnt       =pID->bEndPnt       ; // Gedraggter Punkt ist der Endpunkt einer Polyline
//STRIP001      USHORT   nPrevPnt      =pID->nPrevPnt      ; // Index des vorherigen Punkts
//STRIP001      USHORT   nNextPnt      =pID->nNextPnt      ; // Index des naechsten Punkts
//STRIP001      FASTBOOL bPrevIsBegPnt =pID->bPrevIsBegPnt ; // Vorheriger Punkt ist Anfangspunkt einer Polyline
//STRIP001      FASTBOOL bNextIsEndPnt =pID->bNextIsEndPnt ; // Folgepunkt ist Endpunkt einer Polyline
//STRIP001      USHORT   nPrevPrevPnt  =pID->nPrevPrevPnt  ; // Index des vorvorherigen Punkts
//STRIP001      USHORT   nNextNextPnt  =pID->nNextNextPnt  ; // Index des uebernaechsten Punkts
//STRIP001      FASTBOOL bControl      =pID->bControl      ; // Punkt ist ein Kontrollpunkt
//STRIP001      FASTBOOL bIsPrevControl=pID->bIsPrevControl; // Punkt ist Kontrollpunkt vor einem Stuetzpunkt
//STRIP001      FASTBOOL bIsNextControl=pID->bIsNextControl; // Punkt ist Kontrollpunkt hinter einem Stuetzpunkt
//STRIP001      FASTBOOL bPrevIsControl=pID->bPrevIsControl; // Falls nPnt ein StPnt: Davor ist ein Kontrollpunkt
//STRIP001      FASTBOOL bNextIsControl=pID->bNextIsControl; // Falls nPnt ein StPnt: Dahinter ist ein Kontrollpunkt
//STRIP001      XPolygon aXPoly(pID->aXP);
//STRIP001      XPolygon aLine1(2);
//STRIP001      XPolygon aLine2(2);
//STRIP001      XPolygon aLine3(2);
//STRIP001      XPolygon aLine4(2);
//STRIP001      if (bControl) {
//STRIP001          aLine1[1]=pID->aXP[nPnt];
//STRIP001          if (bIsNextControl) { // bin ich Kontrollpunkt hinter der Stuetzstelle?
//STRIP001              aLine1[0]=pID->aXP[nPrevPnt];
//STRIP001              aLine2[0]=pID->aXP[nNextNextPnt];
//STRIP001              aLine2[1]=pID->aXP[nNextPnt];
//STRIP001              if (pID->aXP.IsSmooth(nPrevPnt) && !bPrevIsBegPnt && pID->aXP.IsControl(nPrevPrevPnt)) {
//STRIP001                  aXPoly.Insert(0,rXP[pID->nPrevPrevPnt0-1],XPOLY_CONTROL);
//STRIP001                  aXPoly.Insert(0,rXP[pID->nPrevPrevPnt0-2],XPOLY_NORMAL);
//STRIP001                  // Hebellienien fuer das gegenueberliegende Kurvensegment
//STRIP001                  aLine3[0]=pID->aXP[nPrevPnt];
//STRIP001                  aLine3[1]=pID->aXP[nPrevPrevPnt];
//STRIP001                  aLine4[0]=rXP[pID->nPrevPrevPnt0-2];
//STRIP001                  aLine4[1]=rXP[pID->nPrevPrevPnt0-1];
//STRIP001              } else {
//STRIP001                  aXPoly.Remove(0,1);
//STRIP001              }
//STRIP001          } else { // ansonsten bin ich Kontrollpunkt vor der Stuetzstelle
//STRIP001              aLine1[0]=pID->aXP[nNextPnt];
//STRIP001              aLine2[0]=pID->aXP[nPrevPrevPnt];
//STRIP001              aLine2[1]=pID->aXP[nPrevPnt];
//STRIP001              if (pID->aXP.IsSmooth(nNextPnt) && !bNextIsEndPnt && pID->aXP.IsControl(nNextNextPnt)) {
//STRIP001                  aXPoly.Insert(XPOLY_APPEND,rXP[pID->nNextNextPnt0+1],XPOLY_CONTROL);
//STRIP001                  aXPoly.Insert(XPOLY_APPEND,rXP[pID->nNextNextPnt0+2],XPOLY_NORMAL);
//STRIP001                  // Hebellinien fuer das gegenueberliegende Kurvensegment
//STRIP001                  aLine3[0]=pID->aXP[nNextPnt];
//STRIP001                  aLine3[1]=pID->aXP[nNextNextPnt];
//STRIP001                  aLine4[0]=rXP[pID->nNextNextPnt0+2];
//STRIP001                  aLine4[1]=rXP[pID->nNextNextPnt0+1];
//STRIP001              } else {
//STRIP001                  aXPoly.Remove(aXPoly.GetPointCount()-1,1);
//STRIP001              }
//STRIP001          }
//STRIP001      } else { // ansonsten kein Kontrollpunkt
//STRIP001          if (pID->bEliminate) {
//STRIP001              aXPoly.Remove(2,1);
//STRIP001          }
//STRIP001          if (bPrevIsControl) aXPoly.Insert(0,rXP[pID->nPrevPrevPnt0-1],XPOLY_NORMAL);
//STRIP001          else if (!bBegPnt && !bPrevIsBegPnt && pID->aXP.IsControl(nPrevPrevPnt)) {
//STRIP001              aXPoly.Insert(0,rXP[pID->nPrevPrevPnt0-1],XPOLY_CONTROL);
//STRIP001              aXPoly.Insert(0,rXP[pID->nPrevPrevPnt0-2],XPOLY_NORMAL);
//STRIP001          } else {
//STRIP001              aXPoly.Remove(0,1);
//STRIP001              if (bBegPnt) aXPoly.Remove(0,1);
//STRIP001          }
//STRIP001          if (bNextIsControl) aXPoly.Insert(XPOLY_APPEND,rXP[pID->nNextNextPnt0+1],XPOLY_NORMAL);
//STRIP001          else if (!bEndPnt && !bNextIsEndPnt && pID->aXP.IsControl(nNextNextPnt)) {
//STRIP001              aXPoly.Insert(XPOLY_APPEND,rXP[pID->nNextNextPnt0+1],XPOLY_CONTROL);
//STRIP001              aXPoly.Insert(XPOLY_APPEND,rXP[pID->nNextNextPnt0+2],XPOLY_NORMAL);
//STRIP001          } else {
//STRIP001              aXPoly.Remove(aXPoly.GetPointCount()-1,1);
//STRIP001              if (bEndPnt) aXPoly.Remove(aXPoly.GetPointCount()-1,1);
//STRIP001          }
//STRIP001          if (bClosed) { // "Birnenproblem": 2 Linien, 1 Kurve, alles Smooth, Punkt zw. beiden Linien wird gedraggt
//STRIP001              if (aXPoly.GetPointCount()>nPntAnz && aXPoly.IsControl(1)) {
//STRIP001                  USHORT a=aXPoly.GetPointCount();
//STRIP001                  aXPoly[a-2]=aXPoly[2]; aXPoly.SetFlags(a-2,aXPoly.GetFlags(2));
//STRIP001                  aXPoly[a-1]=aXPoly[3]; aXPoly.SetFlags(a-1,aXPoly.GetFlags(3));
//STRIP001                  aXPoly.Remove(0,3);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      rXPP.Insert(aXPoly);
//STRIP001      if (aLine1.GetPointCount()>1) rXPP.Insert(aLine1);
//STRIP001      if (aLine2.GetPointCount()>1) rXPP.Insert(aLine2);
//STRIP001      if (aLine3.GetPointCount()>1) rXPP.Insert(aLine3);
//STRIP001      if (aLine4.GetPointCount()>1) rXPP.Insert(aLine4);
//STRIP001  }
//STRIP001 }

//STRIP001 FASTBOOL SdrPathObj::BegCreate(SdrDragStat& rStat)
//STRIP001 {
//STRIP001  FASTBOOL bFreeHand=IsFreeHand();
//STRIP001  rStat.SetNoSnap(bFreeHand);
//STRIP001  rStat.SetOrtho8Possible();
//STRIP001  aPathPolygon.Clear();
//STRIP001  bCreating=TRUE;
//STRIP001  FASTBOOL bMakeStartPoint=TRUE;
//STRIP001  SdrView* pView=rStat.GetView();
//STRIP001  if (pView!=NULL && pView->IsUseIncompatiblePathCreateInterface() &&
//STRIP001      (eKind==OBJ_POLY || eKind==OBJ_PLIN || eKind==OBJ_PATHLINE || eKind==OBJ_PATHFILL)) {
//STRIP001      bMakeStartPoint=FALSE;
//STRIP001  }
//STRIP001  aPathPolygon.Insert(XPolygon());
//STRIP001  aPathPolygon[0][0]=rStat.GetStart();
//STRIP001  if (bMakeStartPoint) {
//STRIP001      aPathPolygon[0][1]=rStat.GetNow();
//STRIP001  }
//STRIP001  ImpPathCreateUser* pU=new ImpPathCreateUser;
//STRIP001  pU->eStartKind=eKind;
//STRIP001  pU->eAktKind=eKind;
//STRIP001  rStat.SetUser(pU);
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 FASTBOOL SdrPathObj::MovCreate(SdrDragStat& rStat)
//STRIP001 {
//STRIP001  ImpPathCreateUser* pU=(ImpPathCreateUser*)rStat.GetUser();
//STRIP001  SdrView* pView=rStat.GetView();
//STRIP001  XPolygon& rXPoly=aPathPolygon[aPathPolygon.Count()-1];
//STRIP001  if (pView!=NULL && pView->IsCreateMode()) {
//STRIP001      // ggf. auf anderes CreateTool umschalten
//STRIP001      UINT16 nIdent;
//STRIP001      UINT32 nInvent;
//STRIP001      pView->TakeCurrentObj(nIdent,nInvent);
//STRIP001      if (nInvent==SdrInventor && pU->eAktKind!=(SdrObjKind)nIdent) {
//STRIP001          SdrObjKind eNewKind=(SdrObjKind)nIdent;
//STRIP001          switch (eNewKind) {
//STRIP001              case OBJ_CARC: case OBJ_CIRC: case OBJ_CCUT: case OBJ_SECT: eNewKind=OBJ_CARC;
//STRIP001              case OBJ_RECT:
//STRIP001              case OBJ_LINE: case OBJ_PLIN: case OBJ_POLY:
//STRIP001              case OBJ_PATHLINE: case OBJ_PATHFILL:
//STRIP001              case OBJ_FREELINE: case OBJ_FREEFILL:
//STRIP001              case OBJ_SPLNLINE: case OBJ_SPLNFILL: {
//STRIP001                  pU->eAktKind=eNewKind;
//STRIP001                  pU->bMixedCreate=TRUE;
//STRIP001                  pU->nBezierStartPoint=rXPoly.GetPointCount();
//STRIP001                  if (pU->nBezierStartPoint>0) pU->nBezierStartPoint--;
//STRIP001              } break;
//STRIP001          } // switch
//STRIP001      }
//STRIP001  }
//STRIP001  USHORT nActPoint=rXPoly.GetPointCount();
//STRIP001  if (aPathPolygon.Count()>1 && rStat.IsMouseDown() && nActPoint<2) {
//STRIP001      rXPoly[0]=rStat.GetPos0();
//STRIP001      rXPoly[1]=rStat.GetNow();
//STRIP001      nActPoint=2;
//STRIP001  }
//STRIP001  if (nActPoint==0) {
//STRIP001      rXPoly[0]=rStat.GetPos0();
//STRIP001  } else nActPoint--;
//STRIP001  FASTBOOL bFreeHand=IsFreeHand(pU->eAktKind);
//STRIP001  rStat.SetNoSnap(bFreeHand /*|| (pU->bMixed && pU->eAktKind==OBJ_LINE)*/);
//STRIP001  rStat.SetOrtho8Possible(pU->eAktKind!=OBJ_CARC && pU->eAktKind!=OBJ_RECT && (!pU->bMixedCreate || pU->eAktKind!=OBJ_LINE));
//STRIP001  Point aActMerk(rXPoly[nActPoint]);
//STRIP001  rXPoly[nActPoint]=rStat.Now();
//STRIP001  if (!pU->bMixedCreate && pU->eStartKind==OBJ_LINE && rXPoly.GetPointCount()>=1) {
//STRIP001      Point aPt(rStat.Start());
//STRIP001      if (pView!=NULL && pView->IsCreate1stPointAsCenter()) {
//STRIP001          aPt+=aPt;
//STRIP001          aPt-=rStat.Now();
//STRIP001      }
//STRIP001      rXPoly[0]=aPt;
//STRIP001  }
//STRIP001  OutputDevice* pOut=pView==NULL ? NULL : pView->GetWin(0);
//STRIP001  if (bFreeHand) {
//STRIP001      if (pU->nBezierStartPoint>nActPoint) pU->nBezierStartPoint=nActPoint;
//STRIP001      if (rStat.IsMouseDown() && nActPoint>0) {
//STRIP001          // keine aufeinanderfolgenden Punkte an zu Nahe gelegenen Positionen zulassen
//STRIP001          long nMinDist=1;
//STRIP001          if (pView!=NULL) nMinDist=pView->GetFreeHandMinDistPix();
//STRIP001          if (pOut!=NULL) nMinDist=pOut->PixelToLogic(Size(nMinDist,0)).Width();
//STRIP001          if (nMinDist<1) nMinDist=1;
//STRIP001
//STRIP001          Point aPt0(rXPoly[nActPoint-1]);
//STRIP001          Point aPt1(rStat.Now());
//STRIP001          long dx=aPt0.X()-aPt1.X(); if (dx<0) dx=-dx;
//STRIP001          long dy=aPt0.Y()-aPt1.Y(); if (dy<0) dy=-dy;
//STRIP001          if (dx<nMinDist && dy<nMinDist) return FALSE;
//STRIP001
//STRIP001          // folgendes ist aus EndCreate kopiert (nur kleine Modifikationen)
//STRIP001          // und sollte dann mal in eine Methode zusammengefasst werden:
//STRIP001
//STRIP001          if (nActPoint-pU->nBezierStartPoint>=3 && ((nActPoint-pU->nBezierStartPoint)%3)==0) {
//STRIP001              rXPoly.PointsToBezier(nActPoint-3);
//STRIP001              rXPoly.SetFlags(nActPoint-1,XPOLY_CONTROL);
//STRIP001              rXPoly.SetFlags(nActPoint-2,XPOLY_CONTROL);
//STRIP001
//STRIP001              if (nActPoint>=6 && rXPoly.IsControl(nActPoint-4)) {
//STRIP001                  rXPoly.CalcTangent(nActPoint-3,nActPoint-4,nActPoint-2);
//STRIP001                  rXPoly.SetFlags(nActPoint-3,XPOLY_SMOOTH);
//STRIP001              }
//STRIP001          }
//STRIP001          rXPoly[nActPoint+1]=rStat.Now();
//STRIP001          rStat.NextPoint();
//STRIP001      } else {
//STRIP001          pU->nBezierStartPoint=nActPoint;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  pU->ResetFormFlags();
//STRIP001  if (IsBezier(pU->eAktKind)) {
//STRIP001      if (nActPoint>=2) {
//STRIP001          pU->CalcBezier(rXPoly[nActPoint-1],rXPoly[nActPoint],rXPoly[nActPoint-1]-rXPoly[nActPoint-2],rStat.IsMouseDown(),pView);
//STRIP001      } else if (pU->bBezHasCtrl0) {
//STRIP001          pU->CalcBezier(rXPoly[nActPoint-1],rXPoly[nActPoint],pU->aBezControl0-rXPoly[nActPoint-1],rStat.IsMouseDown(),pView);
//STRIP001      }
//STRIP001  }
//STRIP001  if (pU->eAktKind==OBJ_CARC && nActPoint>=2) {
//STRIP001      pU->CalcCircle(rXPoly[nActPoint-1],rXPoly[nActPoint],rXPoly[nActPoint-1]-rXPoly[nActPoint-2],pView);
//STRIP001  }
//STRIP001  if (pU->eAktKind==OBJ_LINE && nActPoint>=2) {
//STRIP001      pU->CalcLine(rXPoly[nActPoint-1],rXPoly[nActPoint],rXPoly[nActPoint-1]-rXPoly[nActPoint-2],pView);
//STRIP001  }
//STRIP001  if (pU->eAktKind==OBJ_RECT && nActPoint>=2) {
//STRIP001      pU->CalcRect(rXPoly[nActPoint-1],rXPoly[nActPoint],rXPoly[nActPoint-1]-rXPoly[nActPoint-2],pView);
//STRIP001  }
//STRIP001
//STRIP001  bBoundRectDirty=TRUE;
//STRIP001  bSnapRectDirty=TRUE;
//STRIP001  ImpForceKind();
//STRIP001  if (pU->eStartKind!=OBJ_LINE) { aGeo.nDrehWink=0; aGeo.RecalcSinCos(); }
//STRIP001  //ImpForceLineWink();
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 FASTBOOL SdrPathObj::EndCreate(SdrDragStat& rStat, SdrCreateCmd eCmd)
//STRIP001 {
//STRIP001  ImpPathCreateUser* pU=(ImpPathCreateUser*)rStat.GetUser();
//STRIP001  FASTBOOL bRet=FALSE;
//STRIP001  SdrView* pView=rStat.GetView();
//STRIP001  FASTBOOL bIncomp=pView!=NULL && pView->IsUseIncompatiblePathCreateInterface();
//STRIP001  XPolygon& rXPoly=aPathPolygon[aPathPolygon.Count()-1];
//STRIP001  USHORT nActPoint=rXPoly.GetPointCount()-1;
//STRIP001  Point aAktMerk(rXPoly[nActPoint]);
//STRIP001  rXPoly[nActPoint]=rStat.Now();
//STRIP001  if (!pU->bMixedCreate && pU->eStartKind==OBJ_LINE) {
//STRIP001      if (rStat.GetPointAnz()>=2) eCmd=SDRCREATE_FORCEEND;
//STRIP001      bRet=eCmd==SDRCREATE_FORCEEND;
//STRIP001      if (bRet) {
//STRIP001          bCreating=FALSE;
//STRIP001          delete pU;
//STRIP001          rStat.SetUser(NULL);
//STRIP001      }
//STRIP001      ImpForceKind();
//STRIP001      return bRet;
//STRIP001  }
//STRIP001
//STRIP001  OutputDevice* pOut=pView==NULL ? NULL : pView->GetWin(0);
//STRIP001  long nCloseDist=0;
//STRIP001  FASTBOOL bCloseOnEnd=FALSE;
//STRIP001  if (pView!=NULL && pOut!=NULL && pView->IsAutoClosePolys() && !bIncomp) {
//STRIP001      nCloseDist=pView->GetAutoCloseDistPix();
//STRIP001      nCloseDist=pOut->PixelToLogic(Size(nCloseDist,0)).Width();
//STRIP001      if (nCloseDist<1) nCloseDist=1;
//STRIP001      Point aPt0(rStat.GetStart());
//STRIP001      Point aPt1(rStat.GetNow());
//STRIP001      long dx=aPt0.X()-aPt1.X(); if (dx<0) dx=-dx;
//STRIP001      long dy=aPt0.Y()-aPt1.Y(); if (dy<0) dy=-dy;
//STRIP001      bCloseOnEnd=dx<=nCloseDist && dy<=nCloseDist;
//STRIP001  }
//STRIP001
//STRIP001  if (!pU->bMixedCreate && IsFreeHand(pU->eStartKind)) {
//STRIP001      if (rStat.GetPointAnz()>=2) eCmd=SDRCREATE_FORCEEND;
//STRIP001      if (eCmd==SDRCREATE_FORCEEND && (bCloseOnEnd || IsClosed())) {
//STRIP001          ImpSetClosed(TRUE);
//STRIP001      }
//STRIP001      bRet=eCmd==SDRCREATE_FORCEEND;
//STRIP001      if (bRet) {
//STRIP001          bCreating=FALSE;
//STRIP001          delete pU;
//STRIP001          rStat.SetUser(NULL);
//STRIP001      }
//STRIP001      ImpForceKind();
//STRIP001      aGeo.nDrehWink=0; aGeo.RecalcSinCos();
//STRIP001      return bRet;
//STRIP001  }
//STRIP001  if (eCmd==SDRCREATE_NEXTPOINT || eCmd==SDRCREATE_NEXTOBJECT) {
//STRIP001      // keine aufeinanderfolgenden Punkte an identischer Position zulassen
//STRIP001      if (nActPoint==0 || rStat.Now()!=rXPoly[nActPoint-1]) {
//STRIP001          if (bIncomp) {
//STRIP001              if (pU->nBezierStartPoint>nActPoint) pU->nBezierStartPoint=nActPoint;
//STRIP001              if (IsBezier(pU->eAktKind) && nActPoint-pU->nBezierStartPoint>=3 && ((nActPoint-pU->nBezierStartPoint)%3)==0) {
//STRIP001                  rXPoly.PointsToBezier(nActPoint-3);
//STRIP001                  rXPoly.SetFlags(nActPoint-1,XPOLY_CONTROL);
//STRIP001                  rXPoly.SetFlags(nActPoint-2,XPOLY_CONTROL);
//STRIP001
//STRIP001                  if (nActPoint>=6 && rXPoly.IsControl(nActPoint-4)) {
//STRIP001                      rXPoly.CalcTangent(nActPoint-3,nActPoint-4,nActPoint-2);
//STRIP001                      rXPoly.SetFlags(nActPoint-3,XPOLY_SMOOTH);
//STRIP001                  }
//STRIP001              }
//STRIP001          } else {
//STRIP001              if (nActPoint==1 && IsBezier(pU->eAktKind) && !pU->bBezHasCtrl0) {
//STRIP001                  pU->aBezControl0=rStat.GetNow();;
//STRIP001                  pU->bBezHasCtrl0=TRUE;
//STRIP001                  nActPoint--;
//STRIP001              }
//STRIP001              if (pU->IsFormFlag()) {
//STRIP001                  USHORT nPtAnz0=rXPoly.GetPointCount();
//STRIP001                  rXPoly.Remove(nActPoint-1,2); // die letzten beiden Punkte entfernen und durch die Form ersetzen
//STRIP001                  rXPoly.Insert(XPOLY_APPEND,pU->GetFormPoly());
//STRIP001                  USHORT nPtAnz1=rXPoly.GetPointCount();
//STRIP001                  for (USHORT i=nPtAnz0+1; i<nPtAnz1-1; i++) { // Damit BckAction richtig funktioniert
//STRIP001                      if (!rXPoly.IsControl(i)) rStat.NextPoint();
//STRIP001                  }
//STRIP001                  nActPoint=rXPoly.GetPointCount()-1;
//STRIP001              }
//STRIP001          }
//STRIP001          nActPoint++;
//STRIP001          rXPoly[nActPoint]=rStat.GetNow();
//STRIP001      }
//STRIP001      if (eCmd==SDRCREATE_NEXTOBJECT) {
//STRIP001          if (rXPoly.GetPointCount()>=2) {
//STRIP001              pU->bBezHasCtrl0=FALSE;
//STRIP001              // nur einzelnes Polygon kann offen sein, deshalb schliessen
//STRIP001              rXPoly[nActPoint]=rXPoly[0];
//STRIP001              ImpSetClosed(TRUE);
//STRIP001              XPolygon aXP;
//STRIP001              aXP[0]=rStat.GetNow();
//STRIP001              aPathPolygon.Insert(aXP);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  USHORT nPolyAnz=aPathPolygon.Count();
//STRIP001  if (nPolyAnz!=0) {
//STRIP001      // den letzten Punkt ggf. wieder loeschen
//STRIP001      if (eCmd==SDRCREATE_FORCEEND) {
//STRIP001          XPolygon& rXP=aPathPolygon[nPolyAnz-1];
//STRIP001          USHORT nPtAnz=rXP.GetPointCount();
//STRIP001          if (nPtAnz>=2) {
//STRIP001              if (!rXP.IsControl(nPtAnz-2)) {
//STRIP001                  if (rXP[nPtAnz-1]==rXP[nPtAnz-2]) {
//STRIP001                      rXP.Remove(nPtAnz-1,1);
//STRIP001                  }
//STRIP001              } else {
//STRIP001                  if (rXP[nPtAnz-3]==rXP[nPtAnz-2]) {
//STRIP001                      rXP.Remove(nPtAnz-3,3);
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      for (USHORT nPolyNum=nPolyAnz; nPolyNum>0;) {
//STRIP001          nPolyNum--;
//STRIP001          XPolygon& rXP=aPathPolygon[nPolyNum];
//STRIP001          USHORT nPtAnz=rXP.GetPointCount();
//STRIP001          // Polygone mit zu wenig Punkten werden geloescht
//STRIP001          if (nPolyNum<nPolyAnz-1 || eCmd==SDRCREATE_FORCEEND) {
//STRIP001              if (nPtAnz<2) aPathPolygon.Remove(nPolyNum);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  pU->ResetFormFlags();
//STRIP001  bRet=eCmd==SDRCREATE_FORCEEND;
//STRIP001  if (bRet) {
//STRIP001      bCreating=FALSE;
//STRIP001      delete pU;
//STRIP001      rStat.SetUser(NULL);
//STRIP001      aRect=aPathPolygon.GetBoundRect(); // fuer SdrTextObj
//STRIP001      if (bCloseOnEnd || IsClosed()) ImpSetClosed(TRUE);
//STRIP001      ImpForceKind();
//STRIP001      SetRectsDirty();
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 FASTBOOL SdrPathObj::BckCreate(SdrDragStat& rStat)
//STRIP001 {
//STRIP001  ImpPathCreateUser* pU=(ImpPathCreateUser*)rStat.GetUser();
//STRIP001  if (aPathPolygon.Count()>0) {
//STRIP001      XPolygon& rXPoly=aPathPolygon[aPathPolygon.Count()-1];
//STRIP001      USHORT nActPoint=rXPoly.GetPointCount();
//STRIP001      if (nActPoint>0) {
//STRIP001          nActPoint--;
//STRIP001          // Das letzte Stueck einer Bezierkurve wird erstmal zu 'ner Linie
//STRIP001          rXPoly.Remove(nActPoint,1);
//STRIP001          if (nActPoint>=3 && rXPoly.IsControl(nActPoint-1)) {
//STRIP001              // Beziersegment am Ende sollte zwar nicht vorkommen, aber falls doch ...
//STRIP001              rXPoly.Remove(nActPoint-1,1);
//STRIP001              if (rXPoly.IsControl(nActPoint-2)) rXPoly.Remove(nActPoint-2,1);
//STRIP001          }
//STRIP001      }
//STRIP001      nActPoint=rXPoly.GetPointCount();
//STRIP001      if (nActPoint>=4) { // Kein Beziersegment am Ende
//STRIP001          nActPoint--;
//STRIP001          if (rXPoly.IsControl(nActPoint-1)) {
//STRIP001              rXPoly.Remove(nActPoint-1,1);
//STRIP001              if (rXPoly.IsControl(nActPoint-2)) rXPoly.Remove(nActPoint-2,1);
//STRIP001          }
//STRIP001      }
//STRIP001      if (rXPoly.GetPointCount()<2) {
//STRIP001          aPathPolygon.Remove(aPathPolygon.Count()-1);
//STRIP001      }
//STRIP001      if (aPathPolygon.Count()>0) {
//STRIP001          XPolygon& rXPoly=aPathPolygon[aPathPolygon.Count()-1];
//STRIP001          USHORT nActPoint=rXPoly.GetPointCount();
//STRIP001          if (nActPoint>0) {
//STRIP001              nActPoint--;
//STRIP001              rXPoly[nActPoint]=rStat.Now();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  pU->ResetFormFlags();
//STRIP001  return aPathPolygon.Count()!=0;
//STRIP001 }

//STRIP001 void SdrPathObj::BrkCreate(SdrDragStat& rStat)
//STRIP001 {
//STRIP001  ImpPathCreateUser* pU=(ImpPathCreateUser*)rStat.GetUser();
//STRIP001  aPathPolygon.Clear();
//STRIP001  bCreating=FALSE;
//STRIP001  delete pU;
//STRIP001  rStat.SetUser(NULL);
//STRIP001 }

//STRIP001 void SdrPathObj::TakeCreatePoly(const SdrDragStat& rDrag, XPolyPolygon& rXPP) const
//STRIP001 {
//STRIP001  rXPP=aPathPolygon;
//STRIP001  SdrView* pView=rDrag.GetView();
//STRIP001  if (pView!=NULL && pView->IsUseIncompatiblePathCreateInterface()) return;
//STRIP001
//STRIP001  ImpPathCreateUser* pU=(ImpPathCreateUser*)rDrag.GetUser();
//STRIP001  XPolygon& rXP=rXPP[rXPP.Count()-1];
//STRIP001  USHORT nPtAnz=rXP.GetPointCount();
//STRIP001  if (pU->IsFormFlag()) { // Letztes Polylinesegment entfernen und durch Form ersetzen
//STRIP001      rXP.Remove(nPtAnz-2,2);
//STRIP001      nPtAnz=rXP.GetPointCount();
//STRIP001      rXP.Insert(nPtAnz,pU->GetFormPoly());
//STRIP001  }
//STRIP001  if (pU->bBezier && rDrag.IsMouseDown()) { // Dragging des Hebels
//STRIP001      // Den Hebel etwas gestrichelt darstellen:
//STRIP001      // erst -- -- -- -- -- -- -- und das letzte 1/4 frei
//STRIP001      // -> 1/25 Raster
//STRIP001      XPolygon aXP(2);
//STRIP001      Point aP1(pU->aBezCtrl2);
//STRIP001      Point aP2(pU->aBezEnd);
//STRIP001      long dx=aP2.X()-aP1.X();
//STRIP001      long dy=aP2.Y()-aP1.Y();
//STRIP001      for (long i=0; i<7; i++) {
//STRIP001          aXP[0].X()=aP1.X()+(i*3)*dx/25;
//STRIP001          aXP[0].Y()=aP1.Y()+(i*3)*dy/25;
//STRIP001          aXP[1].X()=aP1.X()+(2+i*3)*dx/25;
//STRIP001          aXP[1].Y()=aP1.Y()+(2+i*3)*dy/25;
//STRIP001          rXPP.Insert(aXP);
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 Pointer SdrPathObj::GetCreatePointer() const
//STRIP001 {
//STRIP001  switch (eKind) {
//STRIP001      case OBJ_LINE    : return Pointer(POINTER_DRAW_LINE);
//STRIP001      case OBJ_POLY    : return Pointer(POINTER_DRAW_POLYGON);
//STRIP001      case OBJ_PLIN    : return Pointer(POINTER_DRAW_POLYGON);
//STRIP001      case OBJ_PATHLINE: return Pointer(POINTER_DRAW_BEZIER);
//STRIP001      case OBJ_PATHFILL: return Pointer(POINTER_DRAW_BEZIER);
//STRIP001      case OBJ_FREELINE: return Pointer(POINTER_DRAW_FREEHAND);
//STRIP001      case OBJ_FREEFILL: return Pointer(POINTER_DRAW_FREEHAND);
//STRIP001      case OBJ_SPLNLINE: return Pointer(POINTER_DRAW_FREEHAND);
//STRIP001      case OBJ_SPLNFILL: return Pointer(POINTER_DRAW_FREEHAND);
//STRIP001      case OBJ_PATHPOLY: return Pointer(POINTER_DRAW_POLYGON);
//STRIP001      case OBJ_PATHPLIN: return Pointer(POINTER_DRAW_POLYGON);
//STRIP001  } // switch
//STRIP001  return Pointer(POINTER_CROSS);
//STRIP001 }

/*N*/ void SdrPathObj::NbcMove(const Size& rSiz)
/*N*/ {
/*N*/   SdrTextObj::NbcMove(rSiz);
/*N*/   MoveXPoly(aPathPolygon,rSiz);
/*N*/ }

/*N*/ void SdrPathObj::NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact)
/*N*/ {
/*N*/   SdrTextObj::NbcResize(rRef,xFact,yFact);
/*N*/   ResizeXPoly(aPathPolygon,rRef,xFact,yFact);
/*N*/ }

/*N*/ void SdrPathObj::NbcRotate(const Point& rRef, long nWink, double sn, double cs)
/*N*/ {
/*N*/   SdrTextObj::NbcRotate(rRef,nWink,sn,cs);
/*N*/   RotateXPoly(aPathPolygon,rRef,sn,cs);
/*N*/ }

/*N*/ void SdrPathObj::NbcShear(const Point& rRefPnt, long nAngle, double fTan, FASTBOOL bVShear)
/*N*/ {
/*N*/   SdrTextObj::NbcShear(rRefPnt,nAngle,fTan,bVShear);
/*N*/   ShearXPoly(aPathPolygon,rRefPnt,fTan,bVShear);
/*N*/ }

//STRIP001 void SdrPathObj::NbcMirror(const Point& rRefPnt1, const Point& rRefPnt2)
//STRIP001 {
//STRIP001  SdrTextObj::NbcMirror(rRefPnt1,rRefPnt2);
//STRIP001  MirrorXPoly(aPathPolygon,rRefPnt1,rRefPnt2);
//STRIP001
//STRIP001  // #97538# Do Joe's special handling for lines when mirroring, too
//STRIP001  ImpForceKind();
//STRIP001 }

/*N*/ void SdrPathObj::TakeUnrotatedSnapRect(Rectangle& rRect) const
/*N*/ {
/*N*/   if (aGeo.nDrehWink==0) {
/*N*/       rRect=GetSnapRect();
/*N*/   } else {
/*N*/       XPolyPolygon aXPP(aPathPolygon);
/*N*/       RotateXPoly(aXPP,Point(),-aGeo.nSin,aGeo.nCos);
/*N*/       rRect=aXPP.GetBoundRect();
/*N*/       Point aTmp(rRect.TopLeft());
/*N*/       RotatePoint(aTmp,Point(),aGeo.nSin,aGeo.nCos);
/*N*/       aTmp-=rRect.TopLeft();
/*N*/       rRect.Move(aTmp.X(),aTmp.Y());
/*N*/   }
/*N*/ }

/*N*/ void SdrPathObj::RecalcSnapRect()
/*N*/ {
/*N*/   maSnapRect=aPathPolygon.GetBoundRect();
/*N*/ }

/*N*/ void SdrPathObj::NbcSetSnapRect(const Rectangle& rRect)
/*N*/ {
/*N*/   Rectangle aOld(GetSnapRect());
/*N*/
/*N*/   // #95736# Take RECT_EMPTY into account when calculating scale factors
/*N*/   long nMulX = (RECT_EMPTY == rRect.Right()) ? 0 : rRect.Right()  - rRect.Left();
/*N*/
/*N*/   long nDivX = aOld.Right()   - aOld.Left();
/*N*/
/*N*/   // #95736# Take RECT_EMPTY into account when calculating scale factors
/*N*/   long nMulY = (RECT_EMPTY == rRect.Bottom()) ? 0 : rRect.Bottom() - rRect.Top();
/*N*/
/*N*/   long nDivY = aOld.Bottom()  - aOld.Top();
/*N*/   if ( nDivX == 0 ) { nMulX = 1; nDivX = 1; }
/*N*/   if ( nDivY == 0 ) { nMulY = 1; nDivY = 1; }
/*N*/   Fraction aX(nMulX,nDivX);
/*N*/   Fraction aY(nMulY,nDivY);
/*N*/   NbcResize(aOld.TopLeft(), aX, aY);
/*N*/   NbcMove(Size(rRect.Left() - aOld.Left(), rRect.Top() - aOld.Top()));
/*N*/ }

//STRIP001 USHORT SdrPathObj::GetSnapPointCount() const
//STRIP001 {
//STRIP001  return GetHdlCount();
//STRIP001 }

//STRIP001 Point SdrPathObj::GetSnapPoint(USHORT nSnapPnt) const
//STRIP001 {
//STRIP001  USHORT nPoly,nPnt;
//STRIP001  if (!FindPolyPnt(nSnapPnt,nPoly,nPnt,FALSE)) {
//STRIP001      DBG_ASSERT(FALSE,"SdrPathObj::GetSnapPoint: Punkt nSnapPnt nicht vorhanden!");
//STRIP001  }
//STRIP001  return Point( aPathPolygon[nPoly][nPnt] );
//STRIP001 }

/*N*/ FASTBOOL SdrPathObj::IsPolyObj() const
/*N*/ {
/*N*/   return TRUE;
/*N*/ }

/*N*/ USHORT SdrPathObj::GetPointCount() const
/*N*/ {
/*N*/   USHORT nPolyCnt = aPathPolygon.Count();
/*N*/   USHORT nPntCnt = 0;
/*N*/
/*N*/   for (USHORT i = 0; i < nPolyCnt; i++)
/*N*/       nPntCnt += aPathPolygon[i].GetPointCount();
/*N*/
/*N*/   return nPntCnt;
/*N*/ }

/*N*/ const Point& SdrPathObj::GetPoint(USHORT nHdlNum) const
/*N*/ {
/*N*/   USHORT nPoly,nPnt;
/*N*/   FindPolyPnt(nHdlNum,nPoly,nPnt,FALSE);
/*N*/   return aPathPolygon[nPoly][nPnt];
/*N*/ }

/*N*/ void SdrPathObj::NbcSetPoint(const Point& rPnt, USHORT nHdlNum)
/*N*/ {
/*N*/   USHORT nPoly,nPnt;
/*N*/
/*N*/   if (FindPolyPnt(nHdlNum,nPoly,nPnt,FALSE)) {
/*N*/       XPolygon& rXP=aPathPolygon[nPoly];
/*N*/       rXP[nPnt]=rPnt;
/*N*/       if (IsClosed() && nPnt==0) rXP[rXP.GetPointCount()-1]=rXP[0];
/*N*/
/*N*/       if (eKind==OBJ_LINE)
/*N*/       {
/*N*/           ImpForceLineWink();
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           // #i10659# for SdrTextObj, keep aRect up to date
/*N*/           aRect=aPathPolygon.GetBoundRect(); // fuer SdrTextObj
/*N*/       }
/*N*/
/*N*/       SetRectsDirty();
/*N*/   }
/*N*/ }

/*************************************************************************/
// Abstand des Punktes Pt zur Strecke AB. Hat der Punkt Pt keine Senkrechte
// zur Strecke AB, so ist der Abstand zum naechstliegenden Punkt verwendet;
// dazu wird nocheinmal der einfache Abstand parallel zu AB draufaddiert
// (als Winkelersatz) (=> groesserer Abstand=unguenstigerer Winkel).

//STRIP001 BigInt GetLineQDist(Point aPt, Point aA, Point aB)
//STRIP001 {
//STRIP001  aPt-=aA; // Nullpunkt zum Linienanfang verschieben
//STRIP001  aB-=aA;
//STRIP001  aA=Point(0,0);
//STRIP001  // Nun auf eine waagerechte Strecke transformieren
//STRIP001  // Ergebnis:  aA Ã-------´ aB
//STRIP001  long nWink=GetAngle(aB);
//STRIP001  double nSin=sin(nWink*nPi180);
//STRIP001  double nCos=cos(nWink*nPi180);
//STRIP001  RotatePoint(aPt,aA,-nSin,nCos);
//STRIP001  RotatePoint(aB,aA,-nSin,nCos);
//STRIP001  //
//STRIP001  if (aPt.X()>=aA.X() && aPt.X()<=aB.X()) { // Hat Pt eine Senkrechte auf AB?
//STRIP001      BigInt nRet=aPt.Y();
//STRIP001      return nRet*nRet;
//STRIP001  }
//STRIP001  if (aPt.X()<aA.X()) { // Pt liegt links der Strecke
//STRIP001      BigInt nDX=aA.X()-aPt.X();
//STRIP001      BigInt nDY=aA.Y()-aPt.Y();
//STRIP001      return nDX*nDX+nDY*nDY+nDX; // Den horizontalen Abstand nochmal als Winkelersatz dazu
//STRIP001  }
//STRIP001  // Pt liegt rechts der Strecke
//STRIP001  BigInt nDX=aPt.X()-aB.X();
//STRIP001  BigInt nDY=aPt.Y()-aB.Y();
//STRIP001  return nDX*nDX+nDY*nDY+nDX; // Den horizontalen Abstand nochmal als Winkelersatz dazu
//STRIP001 }

//STRIP001 BigInt GetQDist(const Point& rP1, const Point& rP2)
//STRIP001 {
//STRIP001  BigInt nDX(rP2.X()-rP1.X());
//STRIP001  BigInt nDY(rP2.Y()-rP1.Y());
//STRIP001  return nDX*nDX+nDY*nDY;
//STRIP001 }

//STRIP001 USHORT SdrPathObj::NbcInsPoint(const Point& rPos, FASTBOOL bNewObj, FASTBOOL bHideHim,
//STRIP001  FASTBOOL& rInsNextAfter)
//STRIP001 {
//STRIP001  USHORT nNewHdl;
//STRIP001
//STRIP001  if (bNewObj) {
//STRIP001      rInsNextAfter=TRUE;
//STRIP001      nNewHdl=NbcInsPoint(0,rPos,FALSE,bNewObj,bHideHim);
//STRIP001  } else {
//STRIP001      VirtualDevice   aVDev;
//STRIP001      Polygon         aPoly, aStart(2), aEnd(2);
//STRIP001      Point           aBestPnt[2];
//STRIP001      BigInt          nBestDst(0x7FFFFFFF);
//STRIP001      USHORT          nBestPoly = 0;
//STRIP001      USHORT          nBestPnt = 0xFFFF;
//STRIP001      USHORT          nPolyCnt = aPathPolygon.Count();
//STRIP001      USHORT          nPoly;
//STRIP001      USHORT          nPnt;
//STRIP001      USHORT          nPntMax;
//STRIP001      FASTBOOL        bAppend = FALSE;
//STRIP001      FASTBOOL        bTestEnd = FALSE;
//STRIP001
//STRIP001      MapMode aMap = aVDev.GetMapMode();
//STRIP001      aMap.SetMapUnit(pModel->GetScaleUnit());
//STRIP001      aMap.SetScaleX(pModel->GetScaleFraction());
//STRIP001      aMap.SetScaleY(pModel->GetScaleFraction());
//STRIP001      aVDev.SetMapMode(aMap);
//STRIP001
//STRIP001      for (nPoly = 0; nPoly < nPolyCnt; nPoly++)
//STRIP001      {
//STRIP001          XPolygon aXPolyPart(4);
//STRIP001          XPolygon& rXPoly = aPathPolygon[nPoly];
//STRIP001          nPnt=0;
//STRIP001
//STRIP001          nPntMax=rXPoly.GetPointCount();
//STRIP001          if (nPntMax>0) {
//STRIP001              nPntMax--;
//STRIP001
//STRIP001              while (nPnt<nPntMax) {
//STRIP001                  USHORT nNextPartPos;
//STRIP001
//STRIP001                  if (rXPoly.IsControl(nPnt+1)) {
//STRIP001                      lcl_CopyBezier(rXPoly,nPnt,aXPolyPart,0);
//STRIP001                      aPoly=XOutCreatePolygon(aXPolyPart,&aVDev);
//STRIP001                      nNextPartPos=3;
//STRIP001                  } else {
//STRIP001                      aPoly = Polygon(2);
//STRIP001                      aPoly[0] = rXPoly[nPnt];
//STRIP001                      aPoly[1] = rXPoly[nPnt+1];
//STRIP001                      nNextPartPos = 1;
//STRIP001                  }
//STRIP001                  USHORT nPartMax=aPoly.GetSize()-1;
//STRIP001
//STRIP001                  for (USHORT i=0; i<nPartMax; i++) {
//STRIP001                      BigInt nDist(GetLineQDist(rPos, aPoly[i], aPoly[i+1]));
//STRIP001
//STRIP001                      if (nDist<nBestDst) {
//STRIP001                          nBestDst =nDist;
//STRIP001                          nBestPoly=nPoly;
//STRIP001                          nBestPnt =nPnt;
//STRIP001                          aBestPnt[0]=rXPoly[nPnt];
//STRIP001                          aBestPnt[1]=rXPoly[nPnt+1];
//STRIP001                          if (nPnt+nNextPartPos>=nPntMax)
//STRIP001                              bTestEnd=TRUE;
//STRIP001                      }
//STRIP001                  }
//STRIP001                  // Start und Endlinien sichern fuer nachfolgenden Test
//STRIP001                  if (nPnt==0) {
//STRIP001                      aStart[0]=aPoly[0];
//STRIP001                      aStart[1]=aPoly[1];
//STRIP001                  }
//STRIP001                  nPnt+=nNextPartPos;
//STRIP001
//STRIP001                  if (nPnt>=nPartMax) {
//STRIP001                      aEnd[1]=aPoly[nPartMax-1];
//STRIP001                      aEnd[0]=aPoly[nPartMax];
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      // und nun noch fuer Linienanfang und -ende
//STRIP001      if ( !IsClosed() )
//STRIP001      {
//STRIP001          if ( nBestPnt == 0 )
//STRIP001          {
//STRIP001              aStart[1] = aStart[1] - aStart[0];
//STRIP001              aStart[0] = rPos - aStart[0];
//STRIP001              // Skalarprodukt fuer Winkelbestimmung
//STRIP001              long nDotProd = aStart[0].X() * aStart[1].X() +
//STRIP001                              aStart[0].Y() * aStart[1].Y();
//STRIP001              // Cosinus des Winkels <= 0? neue Linie am Anfang
//STRIP001              if ( nDotProd <= 0 )
//STRIP001              {
//STRIP001                  nBestPnt = 0;
//STRIP001                  bAppend = TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001          if ( bTestEnd )
//STRIP001          {
//STRIP001              aEnd[1] = aEnd[1] - aEnd[0];
//STRIP001              aEnd[0] = rPos - aEnd[0];
//STRIP001              // Skalarprodukt fuer Winkelbestimmung
//STRIP001              long nDotProd = aEnd[0].X() * aEnd[1].X() +
//STRIP001                              aEnd[0].Y() * aEnd[1].Y();
//STRIP001              // Cosinus des Winkels <= 0? neue Linie am Ende
//STRIP001              if (nDotProd<=0 && (!bAppend || GetQDist(rPos,aEnd[1])<GetQDist(rPos,aStart[0]))) {
//STRIP001                  nBestPnt=nPntMax;
//STRIP001                  bAppend=TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      USHORT nIdx = 0;
//STRIP001      nPnt = 1;
//STRIP001
//STRIP001      // Handle-Nummer aus Punktindex berechnen
//STRIP001      for (nPoly = 0; nPoly <= nBestPoly; nPoly++)
//STRIP001      {
//STRIP001          /*const*/ XPolygon& rXPoly = aPathPolygon[nPoly];
//STRIP001          long nMax = rXPoly.GetPointCount() - 1;
//STRIP001
//STRIP001          if ( nPoly == nBestPoly )   nMax = nBestPnt;
//STRIP001          else if ( IsClosed() )   nMax -= 1;
//STRIP001
//STRIP001          while ( (long) nPnt <= nMax )
//STRIP001              if ( ! rXPoly.IsControl(nPnt++) )
//STRIP001                  nIdx += 1;
//STRIP001          nPnt = 0;
//STRIP001      }
//STRIP001      // berechnen, wo die naechsten Punkte eingefuegt werden sollen
//STRIP001      if (bAppend) {
//STRIP001          rInsNextAfter=(nBestPnt==nPntMax);
//STRIP001      } else {
//STRIP001          rInsNextAfter=GetQDist(rPos,aBestPnt[0]) < GetQDist(rPos,aBestPnt[1]);
//STRIP001      }
//STRIP001      nNewHdl=NbcInsPoint(nIdx,rPos,(!bAppend || nBestPnt==nPntMax),bNewObj,bHideHim);
//STRIP001  }
//STRIP001  ImpForceKind();
//STRIP001  return nNewHdl;
//STRIP001 }

//STRIP001 USHORT SdrPathObj::NbcInsPoint(USHORT nHdl, const Point& rPos, FASTBOOL bInsAfter,
//STRIP001  FASTBOOL bNewObj, FASTBOOL bHideHim)
//STRIP001 {
//STRIP001  USHORT nHdlCnt=GetHdlCount();
//STRIP001  USHORT nNewHdl;
//STRIP001  Point aPnt(rPos);
//STRIP001
//STRIP001  if (bNewObj) {
//STRIP001      XPolygon aNewPoly(SVDOPATH_INITSIZE,SVDOPATH_RESIZE);
//STRIP001      aNewPoly[0]=aPnt;
//STRIP001      aNewPoly[1]=aPnt;
//STRIP001      aNewPoly[2]=aPnt;
//STRIP001      aPathPolygon.Insert(aNewPoly);
//STRIP001      if (!IsClosed() && aPathPolygon.Count()>1) {
//STRIP001           ImpSetClosed(TRUE);
//STRIP001      }
//STRIP001      SetRectsDirty();
//STRIP001      nNewHdl=nHdlCnt;
//STRIP001  } else {
//STRIP001      if (nHdl>nHdlCnt) {
//STRIP001          nHdl=nHdlCnt;
//STRIP001      }
//STRIP001
//STRIP001      USHORT nPoly, nPnt;
//STRIP001      if (!FindPolyPnt(nHdl,nPoly,nPnt,FALSE)) {
//STRIP001          DBG_ASSERT(FALSE,"SdrPathObj::NbcInsPoint() ungueltiger Index.");
//STRIP001          return 0xFFFF;
//STRIP001      }
//STRIP001      // Einfuegen des Punktes in das Polygon...
//STRIP001      XPolygon& rXPoly=aPathPolygon[nPoly];
//STRIP001      if (bHideHim && rXPoly.GetPointCount()!=0) {
//STRIP001          aPnt=rXPoly[nPnt];
//STRIP001      }
//STRIP001      USHORT nPntCnt=rXPoly.GetPointCount();
//STRIP001      nNewHdl=nHdl;
//STRIP001      // ggf. dahinter einfuegen
//STRIP001      if (bInsAfter) {
//STRIP001          nPnt++;
//STRIP001          if (nPnt<nPntCnt && rXPoly.IsControl(nPnt))
//STRIP001              nPnt+=2;
//STRIP001          nNewHdl++;
//STRIP001      }
//STRIP001      if (nPnt>0 && rXPoly.IsControl(nPnt-1)) {
//STRIP001          Point aDiff;
//STRIP001          USHORT nInsPos=nPnt-1;
//STRIP001
//STRIP001          aDiff=(rXPoly[nPnt]-rPos) /3;
//STRIP001          rXPoly.Insert(nInsPos,rPos+aDiff,XPOLY_CONTROL);
//STRIP001          rXPoly.Insert(nInsPos,rPos,XPOLY_SMOOTH);
//STRIP001          aDiff=(rXPoly[nPnt-3]-rPos) /3;
//STRIP001          rXPoly.Insert(nInsPos,rPos+aDiff,XPOLY_CONTROL);
//STRIP001
//STRIP001          rXPoly.CalcTangent(nInsPos+1,nInsPos,nInsPos+2);
//STRIP001      } else {
//STRIP001          rXPoly.Insert(nPnt,aPnt,XPOLY_NORMAL);
//STRIP001      }
//STRIP001  }
//STRIP001  ImpForceKind();
//STRIP001  return nNewHdl;
//STRIP001 }

//STRIP001 FASTBOOL SdrPathObj::NbcDelPoint(USHORT nHdlNum)
//STRIP001 {
//STRIP001  USHORT nPoly,nPnt;
//STRIP001
//STRIP001  if (FindPolyPnt(nHdlNum,nPoly,nPnt,FALSE)) {
//STRIP001      XPolygon& rXPoly=aPathPolygon[nPoly];
//STRIP001      FASTBOOL bClosed=IsClosed();
//STRIP001
//STRIP001      if (rXPoly.GetPointCount()>1) {
//STRIP001          USHORT nPntMax=USHORT(rXPoly.GetPointCount()-1);
//STRIP001          FASTBOOL bFrst=nPnt==0;
//STRIP001          FASTBOOL bLast=nPnt==nPntMax;
//STRIP001          FASTBOOL bPrevIsBez=!bFrst && rXPoly.IsControl(USHORT(nPnt-1));
//STRIP001          FASTBOOL bNextIsBez=!bLast && rXPoly.IsControl(nPnt+1);
//STRIP001          if (bClosed && bFrst) bPrevIsBez=rXPoly.IsControl(USHORT(nPntMax-1));
//STRIP001          if (bClosed && bLast) bNextIsBez=rXPoly.IsControl(1);
//STRIP001          USHORT nDelOfs=nPnt;
//STRIP001          USHORT nDelAnz=0;
//STRIP001
//STRIP001          if (bPrevIsBez && bNextIsBez) { // Bezierpunkt mittendrin
//STRIP001              if (bFrst || bLast) { // Bezierflaeche 1. Punkt
//STRIP001                 nDelAnz=3;
//STRIP001                 rXPoly[nPntMax-1]=rXPoly[2];
//STRIP001              } else { // Bezierflaeche oder -linie mittendrin
//STRIP001                  nDelOfs--;
//STRIP001                  nDelAnz=3;
//STRIP001              }
//STRIP001          } else if (!bPrevIsBez && !bNextIsBez) { // Polygonpunkt oder Polylinepunkt (inkl. Anfangs-/Endpunkt)
//STRIP001              nDelAnz=1;
//STRIP001          } else if (!bClosed && bFrst && bNextIsBez) {
//STRIP001              nDelAnz=3;  // Bezierpunkt am Anfang der Bezierlinie
//STRIP001          } else if (bClosed && bLast && bPrevIsBez) {
//STRIP001              nDelOfs-=2; // Bezierpunkt am Ende der Bezierlinie
//STRIP001              nDelAnz=3;
//STRIP001          } else if (bPrevIsBez && !bNextIsBez) {
//STRIP001              if (bFrst) {
//STRIP001                  nDelAnz=1;  // Uebergang Kurve nach Linie
//STRIP001                  rXPoly.Remove(USHORT(nPntMax-2),2);
//STRIP001              } else {
//STRIP001                  nDelAnz=3;  // Uebergang Kurve nach Linie
//STRIP001                  nDelOfs-=2;
//STRIP001              }
//STRIP001          } else if (!bPrevIsBez && bNextIsBez) {
//STRIP001              nDelAnz=3;  // Uebergang Kurve nach Linie
//STRIP001          }
//STRIP001          if (nDelAnz!=0) rXPoly.Remove(nDelOfs,nDelAnz);
//STRIP001          if (bClosed) { // letzten Punkt auf den Ersten setzen
//STRIP001              USHORT nPntMax=rXPoly.GetPointCount();
//STRIP001              if (nPntMax>0) {
//STRIP001                  nPntMax--;
//STRIP001                  rXPoly[nPntMax]=rXPoly[0];
//STRIP001                  rXPoly.SetFlags(nPntMax,rXPoly.GetFlags(0));
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      if ((bClosed && rXPoly.GetPointCount()<3) || rXPoly.GetPointCount()<2) {
//STRIP001          aPathPolygon.Remove(nPoly);
//STRIP001      }
//STRIP001      SetRectsDirty();
//STRIP001  }
//STRIP001  ImpForceKind();
//STRIP001  return (aPathPolygon.Count()>0);
//STRIP001 }

//STRIP001 SdrObject* SdrPathObj::NbcRipPoint(USHORT nHdlNum, USHORT& rNewPt0Index)
//STRIP001 {
//STRIP001  SdrPathObj* pNewObj=NULL;
//STRIP001  USHORT      nPoly,nPnt;
//STRIP001
//STRIP001  if (FindPolyPnt(nHdlNum,nPoly,nPnt,FALSE)) {
//STRIP001      if (nPoly>0) return NULL;
//STRIP001
//STRIP001      const XPolygon& rXPoly=aPathPolygon.GetObject(nPoly);
//STRIP001      USHORT nPntAnz=rXPoly.GetPointCount();
//STRIP001      if (nPntAnz<=1) return NULL;
//STRIP001      USHORT nPntMax=USHORT(nPntAnz-1);
//STRIP001
//STRIP001      if (IsClosed() && nPntAnz>=1) {
//STRIP001          XPolygon aNeuP(rXPoly);
//STRIP001          USHORT nSrcCnt=nPnt;
//STRIP001          USHORT nIdxCnt=0;
//STRIP001          for (USHORT i=0; i<nPntMax; i++) {
//STRIP001              if (nSrcCnt==0) rNewPt0Index=nIdxCnt; // Mitteilung an den Aufrufer: PtArray ist verschoben
//STRIP001              aNeuP[i]=rXPoly[nSrcCnt];
//STRIP001              aNeuP.SetFlags(i,rXPoly.GetFlags(nSrcCnt));
//STRIP001              nSrcCnt++;
//STRIP001              if (nSrcCnt>=nPntMax) nSrcCnt=0;
//STRIP001              if (!rXPoly.IsControl(i)) nIdxCnt++;
//STRIP001          }
//STRIP001          aNeuP[nPntMax]=aNeuP[0];
//STRIP001          aNeuP.SetFlags(nPntMax,aNeuP.GetFlags(0));
//STRIP001          aPathPolygon.Replace(aNeuP,nPoly);
//STRIP001          ImpSetClosed(FALSE);
//STRIP001      } else if (nPntMax>=2 && nPnt>0 && nPnt<nPntMax) {
//STRIP001          // Aus offener PolyLine zwei PolyLines erzeugen
//STRIP001          pNewObj=(SdrPathObj*)Clone();
//STRIP001          aPathPolygon[0].Remove(nPnt+1,nPntMax-nPnt);
//STRIP001          SetRectsDirty();
//STRIP001          (pNewObj->aPathPolygon)[0].Remove(0,nPnt);
//STRIP001          pNewObj->SetRectsDirty();
//STRIP001      }
//STRIP001  }
//STRIP001  ImpForceKind();
//STRIP001  return pNewObj;
//STRIP001 }

//STRIP001 void SdrPathObj::NbcShut()
//STRIP001 {
//STRIP001 }

//STRIP001 SdrObject* SdrPathObj::DoConvertToPolyObj(BOOL bBezier) const
//STRIP001 {
//STRIP001  SdrObject* pRet = ImpConvertMakeObj(aPathPolygon, IsClosed(), bBezier);
//STRIP001  SdrPathObj* pPath = PTR_CAST(SdrPathObj, pRet);
//STRIP001  if(pPath)
//STRIP001      pPath->ConvertAllSegments(bBezier ? SDRPATH_CURVE : SDRPATH_LINE);
//STRIP001  pRet = ImpConvertAddText(pRet, bBezier);
//STRIP001  return pRet;
//STRIP001 }

/*N*/ SdrObjGeoData* SdrPathObj::NewGeoData() const
/*N*/ {
/*N*/   return new SdrPathObjGeoData;
/*N*/ }

/*N*/ void SdrPathObj::SaveGeoData(SdrObjGeoData& rGeo) const
/*N*/ {
/*N*/   SdrTextObj::SaveGeoData(rGeo);
/*N*/   SdrPathObjGeoData& rPGeo = (SdrPathObjGeoData&) rGeo;
/*N*/   rPGeo.aPathPolygon=aPathPolygon;
/*N*/   rPGeo.eKind=eKind;
/*N*/ }

//STRIP001 void SdrPathObj::RestGeoData(const SdrObjGeoData& rGeo)
//STRIP001 {
//STRIP001  SdrTextObj::RestGeoData(rGeo);
//STRIP001  SdrPathObjGeoData& rPGeo=(SdrPathObjGeoData&)rGeo;
//STRIP001  aPathPolygon=rPGeo.aPathPolygon;
//STRIP001  eKind=rPGeo.eKind;
//STRIP001  ImpForceKind(); // damit u.a. bClosed gesetzt wird
//STRIP001 }

/*N*/ void SdrPathObj::WriteData(SvStream& rOut) const
/*N*/ {
/*N*/   SdrTextObj::WriteData(rOut);
/*N*/   SdrDownCompat aCompat(rOut,STREAM_WRITE); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("SdrPathObj");
/*N*/ #endif
/*N*/   {
/*N*/       SdrDownCompat aPathCompat(rOut,STREAM_WRITE); // ab V11 eingepackt
/*N*/ #ifdef DBG_UTIL
/*N*/       aPathCompat.SetID("SdrPathObj(PathPolygon)");
/*N*/ #endif
/*N*/       rOut<<aPathPolygon;
/*N*/   }
/*N*/ }

/*N*/ void SdrPathObj::ReadData(const SdrObjIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   if (rIn.GetError()!=0) return;
/*N*/   SdrTextObj::ReadData(rHead,rIn);
/*N*/   SdrDownCompat aCompat(rIn,STREAM_READ); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("SdrPathObj");
/*N*/ #endif
/*N*/   aPathPolygon.Clear();
/*N*/   if (rHead.GetVersion()<=6 && (rHead.nIdentifier==OBJ_LINE || rHead.nIdentifier==OBJ_POLY || rHead.nIdentifier==OBJ_PLIN)) {
/*?*/       // SdrPolyObj importieren
/*?*/       switch (eKind) {
/*?*/           case OBJ_LINE: {
/*?*/               Polygon aP(2);
/*?*/               rIn>>aP[0];
/*?*/               rIn>>aP[1];
/*?*/               aPathPolygon=XPolyPolygon(PolyPolygon(aP));
/*?*/           } break;
/*?*/           case OBJ_PLIN: {
/*?*/               Polygon aP;
/*?*/               rIn>>aP;
/*?*/               aPathPolygon=XPolyPolygon(PolyPolygon(aP));
/*?*/           } break;
/*?*/           default: {
/*?*/               PolyPolygon aPoly;
/*?*/               rIn>>aPoly;
/*?*/               aPathPolygon=XPolyPolygon(aPoly);
/*?*/               // und nun die Polygone ggf. durch einfuegen eines weiteren Punktes schliessen
/*?*/               USHORT nPolyAnz=aPathPolygon.Count();
/*?*/               for (USHORT nPolyNum=0; nPolyNum<nPolyAnz; nPolyNum++) {
/*?*/                   const XPolygon& rPoly=aPathPolygon[nPolyNum];
/*?*/                   USHORT nPointAnz=rPoly.GetPointCount();
/*?*/                   aPathPolygon[nPolyNum].GetPointCount();
/*?*/                   if (nPointAnz>=2 && rPoly[0]!=rPoly[USHORT(nPointAnz-1)]) {
/*?*/                       Point aPt(rPoly[0]);
/*?*/                       aPathPolygon[nPolyNum][nPointAnz]=aPt;
/*?*/                   }
/*?*/               }
/*?*/           }
/*?*/       }
/*N*/   } else {
/*N*/       if (rHead.GetVersion()>=11) { // ab V11 ist das eingepackt
/*N*/           SdrDownCompat aPathCompat(rIn,STREAM_READ);
/*N*/ #ifdef DBG_UTIL
/*N*/           aPathCompat.SetID("SdrPathObj(PathPolygon)");
/*N*/ #endif
/*N*/           rIn>>aPathPolygon;
/*N*/       } else {
/*N*/           rIn>>aPathPolygon;
/*N*/       }
/*N*/   }
/*N*/   ImpForceKind(); // ggf. den richtigen Identifier herstellen.
/*N*/ }

/*N*/ void SdrPathObj::NbcSetPathPoly(const XPolyPolygon& rPathPoly)
/*N*/ {
/*N*/   aPathPolygon=rPathPoly;
/*N*/   ImpForceKind();
/*N*/   if (IsClosed()) {
/*N*/       USHORT nPolyAnz=aPathPolygon.Count();
/*N*/       for (USHORT nPolyNum=nPolyAnz; nPolyNum>0;) {
/*N*/           nPolyNum--;
/*N*/           const XPolygon& rConstXP=aPathPolygon[nPolyNum];
/*N*/           USHORT nPointAnz=rConstXP.GetPointCount();
/*N*/           if (nPointAnz!=0) {
/*N*/               Point aStartPt(rConstXP[0]);
/*N*/               if (rConstXP[nPointAnz-1]!=aStartPt) {
/*N*/                   // Polygon schliessen (wird dabei um einen Punkt erweitert)
/*N*/                   aPathPolygon[nPolyNum][nPointAnz]=aStartPt;
/*N*/               }
/*N*/           } else {
/*?*/               DBG_BF_ASSERT(0, "STRIP"); //STRIP001 aPathPolygon.Remove(nPolyNum); // leere Polygone raus
/*N*/           }
/*N*/
/*N*/       }
/*N*/   }
/*N*/   SetRectsDirty();
/*N*/ }

/*N*/ void SdrPathObj::SetPathPoly(const XPolyPolygon& rPathPoly)
/*N*/ {
/*N*/   Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
/*N*/   SendRepaintBroadcast();
/*N*/   NbcSetPathPoly(rPathPoly);
/*N*/   SetChanged();
/*N*/   SendRepaintBroadcast();
/*N*/   SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
/*N*/ }

//STRIP001 void SdrPathObj::ToggleClosed(long nOpenDistance)
//STRIP001 {
//STRIP001  Rectangle aBoundRect0;
//STRIP001
//STRIP001  if(pUserCall != NULL)
//STRIP001      aBoundRect0 = GetBoundRect();
//STRIP001
//STRIP001  FASTBOOL bClosed = IsClosed();
//STRIP001  FASTBOOL bBCFlag = FALSE;
//STRIP001
//STRIP001  USHORT nPolyAnz = aPathPolygon.Count();
//STRIP001  for(USHORT nPolyNum = 0; nPolyNum < nPolyAnz; nPolyNum++)
//STRIP001  {
//STRIP001      XPolygon& rXPoly = aPathPolygon[nPolyNum];
//STRIP001      USHORT nPntAnz = rXPoly.GetPointCount();
//STRIP001
//STRIP001      if(nPntAnz >= 3)
//STRIP001      {
//STRIP001          USHORT nPntMax = nPntAnz-1;
//STRIP001          if(!bBCFlag)
//STRIP001          {
//STRIP001              SendRepaintBroadcast();
//STRIP001              bBCFlag = TRUE;
//STRIP001          }
//STRIP001          if(bClosed)
//STRIP001          {
//STRIP001              // Oeffnen
//STRIP001              double fDist = rXPoly.CalcDistance(nPntMax, nPntMax-1);
//STRIP001
//STRIP001              if(fDist == 0)
//STRIP001                  fDist = 1;
//STRIP001
//STRIP001              double fRatio = (double)nOpenDistance / fDist;
//STRIP001              Point aDiff = rXPoly[nPntMax-1] - rXPoly[nPntMax];
//STRIP001              aDiff.X() = (long) (fRatio * aDiff.X());
//STRIP001              aDiff.Y() = (long) (fRatio * aDiff.Y());
//STRIP001              rXPoly[nPntMax] += aDiff;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              // Schliessen
//STRIP001              INT32 nDist0 = (INT32)(rXPoly.CalcDistance(nPntMax, 0) + 0.5);
//STRIP001
//STRIP001              if(nDist0 > nOpenDistance)
//STRIP001              {
//STRIP001                  // Punkt hinzufuegen zum schliessen
//STRIP001                  nPntMax += 1;
//STRIP001              }
//STRIP001
//STRIP001              rXPoly[nPntMax] = rXPoly[0];
//STRIP001              ImpSetClosed(TRUE);
//STRIP001              rXPoly.SetFlags(nPntMax, rXPoly.GetFlags(0));
//STRIP001              if (rXPoly.IsSmooth(0))
//STRIP001                  rXPoly.CalcSmoothJoin(0, 1, nPntMax-1);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if(bBCFlag)
//STRIP001  {
//STRIP001      ImpSetClosed(!bClosed); // neuen ObjKind setzen
//STRIP001      ImpForceKind(); // wg. Line->Poly->PolyLine statt Line->Poly->Line
//STRIP001      SetRectsDirty();
//STRIP001      SetChanged();
//STRIP001      SendRepaintBroadcast();
//STRIP001      SendUserCall(SDRUSERCALL_RESIZE, aBoundRect0);
//STRIP001  }
//STRIP001 }

//STRIP001 XPolyFlags SdrPathObj::GetSmoothFlag(const SdrHdl* pHdl) const
//STRIP001 {
//STRIP001  XPolyFlags eRet=XPOLY_NORMAL;
//STRIP001  if (pHdl!=NULL) {
//STRIP001      USHORT nPnt=pHdl->GetPointNum();
//STRIP001      const XPolygon& rXPoly=aPathPolygon[pHdl->GetPolyNum()];
//STRIP001      eRet=rXPoly.GetFlags(nPnt);
//STRIP001  }
//STRIP001  return eRet;
//STRIP001 }

//STRIP001 void SdrPathObj::ImpSetSmoothFlag(USHORT nPolyNum, USHORT nPointNum, XPolyFlags eFlag)
//STRIP001 {
//STRIP001  if (eFlag==XPOLY_NORMAL || eFlag==XPOLY_SMOOTH || eFlag==XPOLY_SYMMTR) {
//STRIP001      FASTBOOL bClosed=IsClosed();
//STRIP001      USHORT nPnt=nPointNum;
//STRIP001      XPolygon& rXPoly=aPathPolygon[nPolyNum];
//STRIP001      USHORT nPntMax=rXPoly.GetPointCount();
//STRIP001      if (nPntMax==0) return;
//STRIP001      nPntMax--;
//STRIP001      rXPoly.SetFlags(nPnt,eFlag);
//STRIP001      if (bClosed && nPnt==0) rXPoly.SetFlags(nPntMax,eFlag);
//STRIP001
//STRIP001      if (eFlag!=XPOLY_NORMAL) {
//STRIP001          USHORT nPrev=nPnt;
//STRIP001          USHORT nNext=nPnt+1;
//STRIP001
//STRIP001          if (nPrev==0 && bClosed) nPrev=nPntMax;
//STRIP001          if (nNext>nPntMax && bClosed) nNext=1;
//STRIP001
//STRIP001          if (nPrev>0 && nNext<=nPntMax) {
//STRIP001              nPrev--;
//STRIP001              FASTBOOL bPrevIsBez=rXPoly.IsControl(nPrev);
//STRIP001              FASTBOOL bNextIsBez=rXPoly.IsControl(nNext);
//STRIP001
//STRIP001              if (bPrevIsBez || bNextIsBez) {
//STRIP001                  if (bPrevIsBez && bNextIsBez) {
//STRIP001                      rXPoly.CalcTangent(nPnt,nPrev,nNext);
//STRIP001                  } else {
//STRIP001                      rXPoly.CalcSmoothJoin(nPnt,nPrev,nNext);
//STRIP001                  }
//STRIP001                  if (bClosed) {
//STRIP001                      if (nPnt==0) rXPoly.SetFlags(nPntMax,eFlag);
//STRIP001                      else if (nPnt==nPntMax) rXPoly.SetFlags(0,eFlag);
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrPathObj::NbcSetSmoothFlag(const SdrHdl* pHdl, XPolyFlags eFlag)
//STRIP001 {
//STRIP001  if (pHdl!=NULL) {
//STRIP001      ImpSetSmoothFlag(pHdl->GetPolyNum(),pHdl->GetPointNum(),eFlag);
//STRIP001      ImpForceKind();
//STRIP001      SetRectsDirty();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrPathObj::SetSmoothFlag(const SdrHdl* pHdl, XPolyFlags eFlag)
//STRIP001 {
//STRIP001  Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001  SendRepaintBroadcast();
//STRIP001  NbcSetSmoothFlag(pHdl,eFlag);
//STRIP001  SetChanged();
//STRIP001  SendRepaintBroadcast();
//STRIP001  SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001 }

//STRIP001 SdrPathType SdrPathObj::CanConvertSegment(const SdrHdl* pHdl) const
//STRIP001 {
//STRIP001  SdrPathType ePathType=SDRPATH_NONE;
//STRIP001  if (pHdl!=NULL) {
//STRIP001      const XPolygon& rXPoly=aPathPolygon[pHdl->GetPolyNum()];
//STRIP001      USHORT nPnt=pHdl->GetPointNum();
//STRIP001      USHORT nPntMax=rXPoly.GetPointCount();
//STRIP001      if (nPntMax>0) {
//STRIP001          nPntMax--;
//STRIP001          if (nPnt<nPntMax) {
//STRIP001              if (rXPoly.IsControl(nPnt+1)) {
//STRIP001                  ePathType=SDRPATH_LINE;
//STRIP001              } else {
//STRIP001                  ePathType=SDRPATH_CURVE;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return ePathType;
//STRIP001 }

//STRIP001 SdrPathType SdrPathObj::GetSegmentType(const SdrHdl* pHdl) const
//STRIP001 {
//STRIP001  SdrPathType ePathType=SDRPATH_NONE;
//STRIP001  if (pHdl!=NULL) {
//STRIP001      const XPolygon& rXPoly=aPathPolygon[pHdl->GetPolyNum()];
//STRIP001      USHORT nPnt=pHdl->GetPointNum();
//STRIP001      USHORT nPntMax=rXPoly.GetPointCount();
//STRIP001      if (nPntMax>0) {
//STRIP001          nPntMax--;
//STRIP001          if (nPnt<nPntMax) {
//STRIP001              if (rXPoly.IsControl(nPnt+1)) {
//STRIP001                  ePathType=SDRPATH_CURVE;
//STRIP001              } else {
//STRIP001                  ePathType=SDRPATH_LINE;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return ePathType;
//STRIP001 }

//STRIP001 void SdrPathObj::ConvertSegment(const SdrHdl* pHdl)
//STRIP001 {
//STRIP001  if (pHdl==NULL) return;
//STRIP001  XPolygon& rXPoly = aPathPolygon[pHdl->GetPolyNum()];
//STRIP001  USHORT nP1=pHdl->GetPointNum();
//STRIP001  USHORT nPntMax=rXPoly.GetPointCount();
//STRIP001  if (nPntMax==0) return;
//STRIP001  Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001  nPntMax--;
//STRIP001  if (nP1<nPntMax) {
//STRIP001      USHORT nP2=nP1+1;
//STRIP001
//STRIP001      SendRepaintBroadcast();
//STRIP001
//STRIP001      if (rXPoly.IsControl(nP2)) {
//STRIP001          rXPoly.Remove(nP2, 2);
//STRIP001          nPntMax -= 2;
//STRIP001      } else {
//STRIP001          Point aDiff = (rXPoly[nP2] - rXPoly[nP1]) / 3;
//STRIP001          rXPoly.Insert(nP2, rXPoly[nP1] + aDiff, XPOLY_CONTROL);
//STRIP001          aDiff *= 2;
//STRIP001          rXPoly.Insert(nP2+1, rXPoly[nP1] + aDiff, XPOLY_CONTROL);
//STRIP001          nP2 = nP1 + 3;
//STRIP001          nPntMax += 2;
//STRIP001      }
//STRIP001
//STRIP001      if (rXPoly.IsSmooth(nP1)) {
//STRIP001          USHORT nPrev = nP1;
//STRIP001          if (nP1>0)           nPrev--;
//STRIP001          else if (IsClosed()) nPrev=nPntMax-1;
//STRIP001          if (nPrev!=nP1 && (rXPoly.IsControl(nPrev) || rXPoly.IsControl(nP1+1))) {
//STRIP001              if (rXPoly.IsControl(nPrev) && rXPoly.IsControl(nP1+1)) {
//STRIP001                  rXPoly.CalcTangent(nP1,nPrev,nP1+1);
//STRIP001              } else {
//STRIP001                  rXPoly.CalcSmoothJoin(nP1,nPrev,nP1+1);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      if (rXPoly.IsSmooth(nP2)) {
//STRIP001          USHORT nNext=nP2;
//STRIP001          if (nP2<nPntMax) nNext++;
//STRIP001          else if (IsClosed()) nNext=1;
//STRIP001          if (nNext!=nP2 && (rXPoly.IsControl(nP2-1) || rXPoly.IsControl(nNext))) {
//STRIP001              if (rXPoly.IsControl(nP2-1) && rXPoly.IsControl(nNext)) {
//STRIP001                  rXPoly.CalcTangent(nP2,nP2-1,nNext);
//STRIP001              } else {
//STRIP001                  rXPoly.CalcSmoothJoin(nP2,nP2-1,nNext);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      ImpForceKind();
//STRIP001      SetRectsDirty();
//STRIP001      SetChanged();
//STRIP001      SendRepaintBroadcast();
//STRIP001      SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrPathObj::ImpConvertSegment(USHORT nPolyNum, USHORT nPointNum, SdrPathType ePathType, FASTBOOL bIgnoreSmooth)
//STRIP001 {
//STRIP001  XPolygon& rXPoly=aPathPolygon[nPolyNum];
//STRIP001  USHORT nP1=nPointNum;
//STRIP001  USHORT nPntMax=rXPoly.GetPointCount();
//STRIP001  if (nPntMax==0) return;
//STRIP001  nPntMax--;
//STRIP001  if (nP1<nPntMax) {
//STRIP001      USHORT nP2=nP1+1;
//STRIP001      FASTBOOL bIsCurve=rXPoly.IsControl(nP2);
//STRIP001      if (ePathType!=SDRPATH_NONE) {
//STRIP001          if ((bIsCurve && ePathType==SDRPATH_CURVE) ||
//STRIP001              (!bIsCurve && ePathType==SDRPATH_LINE)) return; // Wandlung nicht erforderlich
//STRIP001      }
//STRIP001      if (bIsCurve) {
//STRIP001          rXPoly.Remove(nP2,2);
//STRIP001          nPntMax-=2;
//STRIP001      } else {
//STRIP001          Point aDiff=(rXPoly[nP2]-rXPoly[nP1])/3;
//STRIP001          rXPoly.Insert(nP2,rXPoly[nP1]+aDiff,XPOLY_CONTROL);
//STRIP001          aDiff*=2;
//STRIP001          rXPoly.Insert(nP2+1,rXPoly[nP1]+aDiff,XPOLY_CONTROL);
//STRIP001          nP2=nP1+3;
//STRIP001          nPntMax+=2;
//STRIP001      }
//STRIP001      if (!bIgnoreSmooth) {
//STRIP001          if (rXPoly.IsSmooth(nP1)) {
//STRIP001              USHORT nPrev=nP1;
//STRIP001              if (nP1>0) nPrev--;
//STRIP001              else if (IsClosed()) nPrev=nPntMax-1;
//STRIP001              if (nPrev!=nP1 && (rXPoly.IsControl(nPrev) || rXPoly.IsControl(nP1+1))) {
//STRIP001                  if (rXPoly.IsControl(nPrev) && rXPoly.IsControl(nP1+1)) {
//STRIP001                      rXPoly.CalcTangent(nP1, nPrev, nP1+1);
//STRIP001                  } else {
//STRIP001                      rXPoly.CalcSmoothJoin(nP1,nPrev,nP1+1);
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          if (rXPoly.IsSmooth(nP2)) {
//STRIP001              USHORT nNext=nP2;
//STRIP001              if (nP2<nPntMax) nNext++;
//STRIP001              else if (IsClosed()) nNext=1;
//STRIP001              if (nNext!=nP2 && (rXPoly.IsControl(nP2-1) || rXPoly.IsControl(nNext))) {
//STRIP001                  if (rXPoly.IsControl(nP2-1) && rXPoly.IsControl(nNext)) {
//STRIP001                      rXPoly.CalcTangent(nP2,nP2-1,nNext);
//STRIP001                  } else {
//STRIP001                      rXPoly.CalcSmoothJoin(nP2,nP2-1,nNext);
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrPathObj::NbcConvertSegment(const SdrHdl* pHdl, SdrPathType ePathType, FASTBOOL bIgnoreSmooth)
//STRIP001 {
//STRIP001  if (pHdl!=NULL) {
//STRIP001      ImpConvertSegment(pHdl->GetPolyNum(),pHdl->GetPointNum(),ePathType,bIgnoreSmooth);
//STRIP001      ImpForceKind(); // ebenso impl. an der SdrPolyEditView
//STRIP001      SetRectsDirty();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrPathObj::ConvertSegment(const SdrHdl* pHdl, SdrPathType ePathType, FASTBOOL bIgnoreSmooth)
//STRIP001 {
//STRIP001  Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001  SendRepaintBroadcast();
//STRIP001  NbcConvertSegment(pHdl,ePathType,bIgnoreSmooth);
//STRIP001  SetChanged();
//STRIP001  SendRepaintBroadcast();
//STRIP001  SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001 }

//STRIP001 void SdrPathObj::ConvertAllSegments(SdrPathType ePathType)
//STRIP001 {
//STRIP001  Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001  FASTBOOL bBroadcastFlg=FALSE;
//STRIP001  FASTBOOL bClosed=IsClosed();
//STRIP001  // von hinten anfangen, da evtl. Punkte geloescht oder eingefuegt werden
//STRIP001  USHORT nPoly=aPathPolygon.Count();
//STRIP001  while (nPoly>0) {
//STRIP001      nPoly--;
//STRIP001      XPolygon& rXPoly=aPathPolygon[nPoly];
//STRIP001      USHORT nPnt=rXPoly.GetPointCount()-1;
//STRIP001      FASTBOOL bSmoothFlg=FALSE;
//STRIP001
//STRIP001      while (nPnt>0) {
//STRIP001          if (rXPoly.IsControl(nPnt-1)) {
//STRIP001              if (nPnt<3) {
//STRIP001                  nPnt=0; // enddeckt durch #35912#. Nun Sicherheitsabfrage
//STRIP001                  DBG_ERROR("SdrPathObj::ConvertAllSegments(): Ungueltige Kontrollpunktanordnung endeckt!");
//STRIP001              } else {
//STRIP001                  nPnt-=3;
//STRIP001              }
//STRIP001              if (ePathType==SDRPATH_LINE || ePathType==SDRPATH_NONE) {
//STRIP001                  if (!bBroadcastFlg) { SendRepaintBroadcast(); bBroadcastFlg=TRUE; }
//STRIP001                  bSmoothFlg=TRUE;
//STRIP001                  ImpConvertSegment(nPoly,nPnt,ePathType,TRUE);
//STRIP001              }
//STRIP001          } else {
//STRIP001              nPnt--;
//STRIP001              if (ePathType==SDRPATH_CURVE || ePathType==SDRPATH_NONE) {
//STRIP001                  if (!bBroadcastFlg) { SendRepaintBroadcast(); bBroadcastFlg=TRUE; }
//STRIP001                  bSmoothFlg=TRUE;
//STRIP001                  ImpConvertSegment(nPoly,nPnt,ePathType,TRUE);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      if (bSmoothFlg) { // und nun die Kontrollpunkte nach Smoothbedingung korregieren
//STRIP001          nPnt=rXPoly.GetPointCount();
//STRIP001          FASTBOOL bLast=TRUE;
//STRIP001          FASTBOOL bLastIsCurve=FALSE;
//STRIP001          while (nPnt>0) {
//STRIP001              FASTBOOL bCurve=rXPoly.IsControl(nPnt-1);
//STRIP001              if (bCurve) {
//STRIP001                  if (nPnt<3) {
//STRIP001                      nPnt=0; // enddeckt durch #35912#. Nun Sicherheitsabfrage
//STRIP001                      DBG_ERROR("SdrPathObj::ConvertAllSegments(): Ungueltige Kontrollpunktanordnung endeckt!");
//STRIP001                  } else {
//STRIP001                      nPnt-=3;
//STRIP001                  }
//STRIP001              } else nPnt--;
//STRIP001              if (bLast) {
//STRIP001                  bLast=FALSE; // den Letzten Punkt ignorieren, denn da hat Smooth eh keinen Einfluss
//STRIP001                  bLastIsCurve=bCurve;
//STRIP001              } else {
//STRIP001                  if (rXPoly.IsSmooth(nPnt) &&
//STRIP001                      (bCurve ||                                   // dahinter eine Kurve
//STRIP001                       (nPnt>0 && rXPoly.IsControl(nPnt-1)) ||     // oder davor eine Kurve
//STRIP001                        (bClosed && nPnt==0 && bLastIsCurve)))
//STRIP001                  {
//STRIP001                      XPolyFlags eSmooth=rXPoly.GetFlags(nPnt);
//STRIP001                      rXPoly.SetFlags(nPnt,XPOLY_NORMAL); // damit ImpSetSmoothFlag() was tut
//STRIP001                      ImpSetSmoothFlag(nPoly,nPnt,eSmooth);
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if (bBroadcastFlg) {
//STRIP001      ImpForceKind();
//STRIP001      SetRectsDirty();
//STRIP001      SetChanged();
//STRIP001      SendRepaintBroadcast();
//STRIP001      SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// transformation interface for StarOfficeAPI. This implements support for
// homogen 3x3 matrices containing the transformation of the SdrObject. At the
// moment it contains a shearX, rotation and translation, but for setting all linear
// transforms like Scale, ShearX, ShearY, Rotate and Translate are supported.
//
////////////////////////////////////////////////////////////////////////////////////////////////////
// gets base transformation and rectangle of object. If it's an SdrPathObj it fills the PolyPolygon
// with the base geometry and returns TRUE. Otherwise it returns FALSE.
/*N*/ BOOL SdrPathObj::TRGetBaseGeometry(Matrix3D& rMat, XPolyPolygon& rPolyPolygon) const
/*N*/ {
/*N*/   double fRotate;
/*N*/   double fShear;
/*N*/   Rectangle aRectangle;
/*N*/
/*N*/   if(eKind==OBJ_LINE)
/*N*/   {
/*N*/       // #85920# special handling for single line mode (2 points)
/*N*/       XPolygon aLine(2);
/*N*/       aLine[0] = GetPoint(0);
/*N*/       aLine[1] = GetPoint(1);
/*N*/       rPolyPolygon.Clear();
/*N*/       rPolyPolygon.Insert(aLine);
/*N*/       aRectangle = rPolyPolygon.GetBoundRect();
/*N*/
/*N*/       // fill in values
/*N*/       fRotate = fShear = 0.0;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       // get turn and shear
/*N*/       fRotate = (aGeo.nDrehWink / 100.0) * F_PI180;
/*N*/       fShear = (aGeo.nShearWink / 100.0) * F_PI180;
/*N*/
/*N*/       // get path, remove rotate and shear
/*N*/       rPolyPolygon = GetPathPoly();
/*N*/       if(aGeo.nDrehWink)
/*N*/           RotateXPoly(rPolyPolygon, Point(), -aGeo.nSin, aGeo.nCos);
/*N*/
/*N*/       aRectangle = rPolyPolygon.GetBoundRect();
/*N*/       Point aTmp(aRectangle.TopLeft());
/*N*/
/*N*/       if(aGeo.nShearWink)
/*N*/       {
/*N*/           ShearXPoly(rPolyPolygon, aTmp, -aGeo.nTan, FALSE);
/*N*/           aRectangle = rPolyPolygon.GetBoundRect();
/*N*/           aTmp = aRectangle.TopLeft();
/*N*/       }
/*N*/
/*N*/       RotatePoint(aTmp, Point(), aGeo.nSin, aGeo.nCos);
/*N*/       aTmp -= aRectangle.TopLeft();
/*N*/
/*N*/       // polygon to base position
/*N*/       rPolyPolygon.Move(aTmp.X(), aTmp.Y());
/*N*/
/*N*/       // get bound rect for values
/*N*/       aRectangle = rPolyPolygon.GetBoundRect();
/*N*/   }
/*N*/
/*N*/   // fill in values
/*N*/   Vector2D aScale((double)aRectangle.GetWidth(), (double)aRectangle.GetHeight());
/*N*/   Vector2D aTranslate((double)aRectangle.Left(), (double)aRectangle.Top());
/*N*/
/*N*/   // polygon to (0,0)
/*N*/   rPolyPolygon.Move(-aRectangle.Left(), -aRectangle.Top());
/*N*/
/*N*/   // position maybe relative to anchorpos, convert
/*N*/   if( pModel->IsWriter() )
/*N*/   {
/*N*/       if(GetAnchorPos().X() != 0 || GetAnchorPos().Y() != 0)
/*N*/           aTranslate -= Vector2D(GetAnchorPos().X(), GetAnchorPos().Y());
/*N*/   }
/*N*/
/*N*/   // force MapUnit to 100th mm
/*N*/   SfxMapUnit eMapUnit = pModel->GetItemPool().GetMetric(0);
/*N*/   if(eMapUnit != SFX_MAPUNIT_100TH_MM)
/*N*/   {
/*N*/       switch(eMapUnit)
/*N*/       {
/*N*/           case SFX_MAPUNIT_TWIP :
/*N*/           {
/*N*/               // position
/*N*/               // #104018#
/*N*/               aTranslate.X() = ImplTwipsToMM(aTranslate.X());
/*N*/               aTranslate.Y() = ImplTwipsToMM(aTranslate.Y());
/*N*/
/*N*/               // size
/*N*/               // #104018#
/*N*/               aScale.X() = ImplTwipsToMM(aScale.X());
/*N*/               aScale.Y() = ImplTwipsToMM(aScale.Y());
/*N*/
/*N*/               // polygon
/*N*/               for(sal_uInt16 a(0); a < rPolyPolygon.Count(); a++)
/*N*/               {
/*N*/                   XPolygon& rPoly = rPolyPolygon[a];
/*N*/                   for(sal_uInt16 b(0); b < rPoly.GetPointCount(); b++)
/*N*/                   {
/*N*/                       rPoly[b].X() = ImplTwipsToMM(rPoly[b].X());
/*N*/                       rPoly[b].Y() = ImplTwipsToMM(rPoly[b].Y());
/*N*/                   }
/*N*/               }
/*N*/
/*N*/               break;
/*N*/           }
/*N*/           default:
/*N*/           {
/*N*/               DBG_ERROR("TRGetBaseGeometry: Missing unit translation to 100th mm!");
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // build matrix
/*N*/   rMat.Identity();
/*N*/   if(aScale.X() != 1.0 || aScale.Y() != 1.0)
/*N*/       rMat.Scale(aScale.X(), aScale.Y());
/*N*/   if(fShear != 0.0)
/*N*/       rMat.ShearX(tan(fShear));
/*N*/   if(fRotate != 0.0)
/*N*/       rMat.Rotate(fRotate);
/*N*/   if(aTranslate.X() != 0.0 || aTranslate.Y() != 0.0)
/*N*/       rMat.Translate(aTranslate.X(), aTranslate.Y());
/*N*/
/*N*/   return TRUE;
/*N*/ }

// sets the base geometry of the object using infos contained in the homogen 3x3 matrix.
// If it's an SdrPathObj it will use the provided geometry information. The Polygon has
// to use (0,0) as upper left and will be scaled to the given size in the matrix.
/*N*/ void SdrPathObj::TRSetBaseGeometry(const Matrix3D& rMat, const XPolyPolygon& rPolyPolygon)
/*N*/ {
/*N*/   // break up matrix
/*N*/   Vector2D aScale, aTranslate;
/*N*/   double fShear, fRotate;
/*N*/   rMat.DecomposeAndCorrect(aScale, fShear, fRotate, aTranslate);
/*N*/
/*N*/   // copy poly
/*N*/   XPolyPolygon aNewPolyPolygon(rPolyPolygon);
/*N*/
/*N*/   // reset object shear and rotations
/*N*/   aGeo.nDrehWink = 0;
/*N*/   aGeo.RecalcSinCos();
/*N*/   aGeo.nShearWink = 0;
/*N*/   aGeo.RecalcTan();
/*N*/
/*N*/   // force metric to pool metric
/*N*/   SfxMapUnit eMapUnit = pModel->GetItemPool().GetMetric(0);
/*N*/   if(eMapUnit != SFX_MAPUNIT_100TH_MM)
/*N*/   {
/*N*/       switch(eMapUnit)
/*N*/       {
/*N*/           case SFX_MAPUNIT_TWIP :
/*N*/           {
/*N*/               // position
/*N*/               // #104018#
/*N*/               aTranslate.X() = ImplMMToTwips(aTranslate.X());
/*N*/               aTranslate.Y() = ImplMMToTwips(aTranslate.Y());
/*N*/
/*N*/               // size
/*N*/               // #104018#
/*N*/               aScale.X() = ImplMMToTwips(aScale.X());
/*N*/               aScale.Y() = ImplMMToTwips(aScale.Y());
/*N*/
/*N*/               // polygon
/*N*/               for(sal_uInt16 a(0); a < aNewPolyPolygon.Count(); a++)
/*N*/               {
/*N*/                   XPolygon& rPoly = aNewPolyPolygon[a];
/*N*/                   for(sal_uInt16 b(0); b < rPoly.GetPointCount(); b++)
/*N*/                   {
/*N*/                       rPoly[b].X() = ImplMMToTwips(rPoly[b].X());
/*N*/                       rPoly[b].Y() = ImplMMToTwips(rPoly[b].Y());
/*N*/                   }
/*N*/               }
/*N*/
/*N*/               break;
/*N*/           }
/*N*/           default:
/*N*/           {
/*N*/               DBG_ERROR("TRSetBaseGeometry: Missing unit translation to PoolMetric!");
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if( pModel->IsWriter() )
/*N*/   {
/*N*/       // if anchor is used, make position relative to it
/*N*/       if(GetAnchorPos().X() != 0 || GetAnchorPos().Y() != 0)
/*N*/           aTranslate -= Vector2D(GetAnchorPos().X(), GetAnchorPos().Y());
/*N*/   }
/*N*/
/*N*/   // set PathPoly and get type
/*N*/   SetPathPoly(aNewPolyPolygon);
/*N*/
/*N*/   if(eKind==OBJ_LINE)
/*N*/   {
/*N*/       // #85920# special handling for single line mode (2 points)
/*N*/       Point aPoint1 = aNewPolyPolygon[0][0];
/*N*/       Point aPoint2 = aNewPolyPolygon[0][1];
/*N*/
/*N*/       // shear?
/*N*/       if(fShear != 0.0)
/*N*/       {
/*?*/           GeoStat aGeoStat;
/*?*/           aGeoStat.nShearWink = FRound((atan(fShear) / F_PI180) * 100.0);
/*?*/           aGeoStat.RecalcTan();
/*?*/           ShearPoint(aPoint1, Point(), aGeoStat.nTan, FALSE);
/*?*/           ShearPoint(aPoint2, Point(), aGeoStat.nTan, FALSE);
/*N*/       }
/*N*/
/*N*/       // rotation?
/*N*/       if(fRotate != 0.0)
/*N*/       {
/*?*/           GeoStat aGeoStat;
/*?*/           aGeoStat.nDrehWink = FRound((fRotate / F_PI180) * 100.0);
/*?*/           aGeoStat.RecalcSinCos();
/*?*/           RotatePoint(aPoint1, Point(), aGeoStat.nSin, aGeoStat.nCos);
/*?*/           RotatePoint(aPoint2, Point(), aGeoStat.nSin, aGeoStat.nCos);
/*N*/       }
/*N*/
/*N*/       // translate?
/*N*/       if(aTranslate.X() != 0.0 || aTranslate.Y() != 0.0)
/*N*/       {
/*N*/           Point aOffset((sal_Int32)FRound(aTranslate.X()), (sal_Int32)FRound(aTranslate.Y()));
/*N*/           aPoint1 += aOffset;
/*N*/           aPoint2 += aOffset;
/*N*/       }
/*N*/
/*N*/       // put points back to poly
/*N*/       aNewPolyPolygon[0][0] = aPoint1;
/*N*/       aNewPolyPolygon[0][1] = aPoint2;
/*N*/
/*N*/       // set PathPoly again; this sets all of JOEs old needed stati and values
/*N*/       SetPathPoly(aNewPolyPolygon);
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       // shear?
/*N*/       if(fShear != 0.0)
/*N*/       {
/*N*/           GeoStat aGeoStat;
/*N*/           aGeoStat.nShearWink = FRound((atan(fShear) / F_PI180) * 100.0);
/*N*/           aGeoStat.RecalcTan();
/*N*/           Shear(Point(), aGeoStat.nShearWink, aGeoStat.nTan, FALSE);
/*N*/       }
/*N*/
/*N*/       // rotation?
/*N*/       if(fRotate != 0.0)
/*N*/       {
/*N*/           GeoStat aGeoStat;
/*N*/           aGeoStat.nDrehWink = FRound((fRotate / F_PI180) * 100.0);
/*N*/           aGeoStat.RecalcSinCos();
/*N*/           Rotate(Point(), aGeoStat.nDrehWink, aGeoStat.nSin, aGeoStat.nCos);
/*N*/       }
/*N*/
/*N*/       // translate?
/*N*/       if(aTranslate.X() != 0.0 || aTranslate.Y() != 0.0)
/*N*/       {
/*N*/           Move(Size(
/*N*/               (sal_Int32)FRound(aTranslate.X()),
/*N*/               (sal_Int32)FRound(aTranslate.Y())));
/*N*/       }
/*N*/   }
/*N*/ }

// EOF
}
