/*************************************************************************
 *
 *  $RCSfile: svx_svdorect.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 16:27:52 $
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

// auto strip #include "svdorect.hxx"
#include <math.h>
#include <stdlib.h>
#include "xpool.hxx"
// auto strip #include "xpoly.hxx"
// auto strip #include "svdxout.hxx"
// auto strip #include "svdattr.hxx"
#include "svdpool.hxx"
#include "svdtouch.hxx"
// auto strip #include "svdtrans.hxx"
#include "svdio.hxx"
// auto strip #include "svdetc.hxx"
// auto strip #include "svddrag.hxx"
// auto strip #include "svdmodel.hxx"
#include "svdpage.hxx"
#include "svdocapt.hxx" // fuer Import von SdrFileVersion 2
// auto strip #include "svdpagv.hxx" // fuer
#include "svdview.hxx" // das
// auto strip #include "svdundo.hxx" // Macro-Beispiel
// auto strip #include "svdopath.hxx"
// auto strip #include "svdglob.hxx"  // Stringcache
#include "svdstr.hrc"   // Objektname

#ifndef _SVX_XFLCLIT_HXX //autogen
#include <xflclit.hxx>
#endif

#ifndef _SVX_XLNCLIT_HXX //autogen
#include <xlnclit.hxx>
#endif

#ifndef _SVX_XLNWTIT_HXX //autogen
#include <xlnwtit.hxx>
#endif

#ifndef _SVX_RECTENUM_HXX
#include "rectenum.hxx"
#endif

#ifndef _SVX_SVDOIMP_HXX
#include "svdoimp.hxx"
#endif

#ifndef _XOUTX_HXX
#include "xoutx.hxx"
#endif

namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ TYPEINIT1(SdrRectObj,SdrTextObj);

/*N*/ SdrRectObj::SdrRectObj():
/*N*/   pXPoly(NULL),
/*N*/   bXPolyIsLine(FALSE)
/*N*/ {
/*N*/   bClosedObj=TRUE;
/*N*/ }

/*N*/ SdrRectObj::SdrRectObj(const Rectangle& rRect):
/*N*/   SdrTextObj(rRect),
/*N*/   pXPoly(NULL),
/*N*/   bXPolyIsLine(FALSE)
/*N*/ {
/*N*/   bClosedObj=TRUE;
/*N*/ }

/*N*/ SdrRectObj::SdrRectObj(SdrObjKind eNewTextKind):
/*N*/   SdrTextObj(eNewTextKind),
/*N*/   pXPoly(NULL),
/*N*/   bXPolyIsLine(FALSE)
/*N*/ {
/*N*/   DBG_ASSERT(eTextKind==OBJ_TEXT || eTextKind==OBJ_TEXTEXT ||
/*N*/              eTextKind==OBJ_OUTLINETEXT || eTextKind==OBJ_TITLETEXT,
/*N*/              "SdrRectObj::SdrRectObj(SdrObjKind) ist nur fuer Textrahmen gedacht");
/*N*/   bClosedObj=TRUE;
/*N*/ }

/*N*/ SdrRectObj::SdrRectObj(SdrObjKind eNewTextKind, const Rectangle& rRect):
/*N*/   SdrTextObj(eNewTextKind,rRect),
/*N*/   pXPoly(NULL),
/*N*/   bXPolyIsLine(FALSE)
/*N*/ {
/*N*/   DBG_ASSERT(eTextKind==OBJ_TEXT || eTextKind==OBJ_TEXTEXT ||
/*N*/              eTextKind==OBJ_OUTLINETEXT || eTextKind==OBJ_TITLETEXT,
/*N*/              "SdrRectObj::SdrRectObj(SdrObjKind,...) ist nur fuer Textrahmen gedacht");
/*N*/   bClosedObj=TRUE;
/*N*/ }

/*?*/ SdrRectObj::SdrRectObj(SdrObjKind eNewTextKind, const Rectangle& rNewRect, SvStream& rInput, USHORT eFormat):
/*?*/   SdrTextObj(eNewTextKind,rNewRect,rInput,eFormat),
/*?*/   pXPoly(NULL),
/*?*/   bXPolyIsLine(FALSE)
/*?*/ {
/*?*/   DBG_ASSERT(eTextKind==OBJ_TEXT || eTextKind==OBJ_TEXTEXT ||
/*?*/              eTextKind==OBJ_OUTLINETEXT || eTextKind==OBJ_TITLETEXT,
/*?*/              "SdrRectObj::SdrRectObj(SdrObjKind,...) ist nur fuer Textrahmen gedacht");
/*?*/   bClosedObj=TRUE;
/*?*/ }

/*N*/ SdrRectObj::~SdrRectObj()
/*N*/ {
/*N*/   if (pXPoly!=NULL) delete pXPoly;
/*N*/ }

/*N*/ void SdrRectObj::SetXPolyDirty()
/*N*/ {
/*N*/   if (pXPoly!=NULL) {
/*N*/       delete pXPoly;
/*N*/       pXPoly=NULL;
/*N*/   }
/*N*/ }

/*N*/ FASTBOOL SdrRectObj::PaintNeedsXPoly(long nEckRad) const
/*N*/ {
/*N*/   FASTBOOL bNeed=aGeo.nDrehWink!=0 || aGeo.nShearWink!=0 || nEckRad!=0;
/*N*/   return bNeed;
/*N*/ }

/*N*/ XPolygon SdrRectObj::ImpCalcXPoly(const Rectangle& rRect1, long nRad1, FASTBOOL bContour) const
/*N*/ {
/*N*/   bContour=TRUE; // am 14.1.97 wg. Umstellung TakeContour ueber Mtf und Paint. Joe.
/*N*/   XPolygon aXPoly(rRect1,nRad1,nRad1);
/*N*/   if (bContour) {
/*N*/       unsigned nPointAnz=aXPoly.GetPointCount();
/*N*/       XPolygon aNeuPoly(nPointAnz+1);
/*N*/       unsigned nShift=nPointAnz-2;
/*N*/       if (nRad1!=0) nShift=nPointAnz-5;
/*N*/       unsigned j=nShift;
/*N*/       for (unsigned i=1; i<nPointAnz; i++) {
/*N*/           aNeuPoly[i]=aXPoly[j];
/*N*/           aNeuPoly.SetFlags(i,aXPoly.GetFlags(j));
/*N*/           j++;
/*N*/           if (j>=nPointAnz) j=1;
/*N*/       }
/*N*/       aNeuPoly[0]=rRect1.BottomCenter();
/*N*/       aNeuPoly[nPointAnz]=aNeuPoly[0];
/*N*/       aXPoly=aNeuPoly;
/*N*/   }
/*N*/   // Die Winkelangaben beziehen sich immer auf die linke obere Ecke von !aRect!
/*N*/   if (aGeo.nShearWink!=0) ShearXPoly(aXPoly,aRect.TopLeft(),aGeo.nTan);
/*N*/   if (aGeo.nDrehWink!=0) RotateXPoly(aXPoly,aRect.TopLeft(),aGeo.nSin,aGeo.nCos);
/*N*/   return aXPoly;
/*N*/ }

/*N*/ void SdrRectObj::RecalcXPoly()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  pXPoly=new XPolygon(ImpCalcXPoly(aRect,GetEckenradius()));
/*N*/ }

/*N*/ const XPolygon& SdrRectObj::GetXPoly() const
/*N*/ {
/*N*/   if (pXPoly==NULL) ((SdrRectObj*)this)->RecalcXPoly();
/*N*/   return *pXPoly;
/*N*/ }

//STRIP001 void SdrRectObj::TakeObjInfo(SdrObjTransformInfoRec& rInfo) const
//STRIP001 {
//STRIP001  FASTBOOL bNoTextFrame=!IsTextFrame();
//STRIP001  rInfo.bResizeFreeAllowed=bNoTextFrame || aGeo.nDrehWink%9000==0;
//STRIP001  rInfo.bResizePropAllowed=TRUE;
//STRIP001  rInfo.bRotateFreeAllowed=TRUE;
//STRIP001  rInfo.bRotate90Allowed  =TRUE;
//STRIP001  rInfo.bMirrorFreeAllowed=bNoTextFrame;
//STRIP001  rInfo.bMirror45Allowed  =bNoTextFrame;
//STRIP001  rInfo.bMirror90Allowed  =bNoTextFrame;
//STRIP001
//STRIP001  // allow transparence
//STRIP001  rInfo.bTransparenceAllowed = TRUE;
//STRIP001
//STRIP001  // gradient depends on fillstyle
//STRIP001  XFillStyle eFillStyle = ((XFillStyleItem&)(GetItem(XATTR_FILLSTYLE))).GetValue();
//STRIP001  rInfo.bGradientAllowed = (eFillStyle == XFILL_GRADIENT);
//STRIP001
//STRIP001  rInfo.bShearAllowed     =bNoTextFrame;
//STRIP001  rInfo.bEdgeRadiusAllowed=TRUE;
//STRIP001
//STRIP001  FASTBOOL bCanConv=!HasText() || ImpCanConvTextToCurve();
//STRIP001  if (bCanConv && !bNoTextFrame && !HasText()) {
//STRIP001      bCanConv=HasFill() || HasLine();
//STRIP001  }
//STRIP001  rInfo.bCanConvToPath    =bCanConv;
//STRIP001  rInfo.bCanConvToPoly    =bCanConv;
//STRIP001  rInfo.bCanConvToContour = (rInfo.bCanConvToPoly || LineGeometryUsageIsNecessary());
//STRIP001 }

/*N*/ UINT16 SdrRectObj::GetObjIdentifier() const
/*N*/ {
/*N*/   if (IsTextFrame()) return UINT16(eTextKind);
/*N*/   else return UINT16(OBJ_RECT);
/*N*/ }

/*N*/ void SdrRectObj::RecalcBoundRect()
/*N*/ {
/*N*/   aOutRect=GetSnapRect();
/*N*/   long nLineWdt=ImpGetLineWdt();
/*N*/   nLineWdt++; nLineWdt/=2;
/*N*/   if (nLineWdt!=0) {
/*N*/       long a=nLineWdt;
/*N*/       if ((aGeo.nDrehWink!=0 || aGeo.nShearWink!=0) && GetEckenradius()==0) {
/*N*/           a*=2; // doppelt, wegen evtl. spitzen Ecken
/*N*/       }
/*N*/       aOutRect.Left  ()-=a;
/*N*/       aOutRect.Top   ()-=a;
/*N*/       aOutRect.Right ()+=a;
/*N*/       aOutRect.Bottom()+=a;
/*N*/   }
/*N*/   ImpAddShadowToBoundRect();
/*N*/   ImpAddTextToBoundRect();
/*N*/ }

/*N*/ void SdrRectObj::TakeUnrotatedSnapRect(Rectangle& rRect) const
/*N*/ {
/*N*/   rRect=aRect;
/*N*/   if (aGeo.nShearWink!=0) {
/*N*/       long nDst=Round((aRect.Bottom()-aRect.Top())*aGeo.nTan);
/*N*/       if (aGeo.nShearWink>0) {
/*?*/           Point aRef(rRect.TopLeft());
/*?*/           rRect.Left()-=nDst;
/*?*/           Point aTmpPt(rRect.TopLeft());
/*?*/           RotatePoint(aTmpPt,aRef,aGeo.nSin,aGeo.nCos);
/*?*/           aTmpPt-=rRect.TopLeft();
/*?*/           rRect.Move(aTmpPt.X(),aTmpPt.Y());
/*N*/       } else {
/*N*/           rRect.Right()-=nDst;
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ FASTBOOL SdrRectObj::Paint(ExtOutputDevice& rXOut, const SdrPaintInfoRec& rInfoRec) const
/*N*/ {
/*N*/   // Hidden objects on masterpages, draw nothing
/*N*/   if((rInfoRec.nPaintMode & SDRPAINTMODE_MASTERPAGE) && bNotVisibleAsMaster)
/*N*/       return TRUE;
/*N*/
/*N*/   // Im Graustufenmodus/Kontrastmodus soll die Hintergrundseite NICHT angezeigt werden
/*N*/   ULONG nMode = rXOut.GetOutDev()->GetDrawMode();
/*N*/   FASTBOOL bGrayscaleMode = ( nMode == (DRAWMODE_GRAYLINE | DRAWMODE_GRAYFILL | DRAWMODE_BLACKTEXT | DRAWMODE_GRAYBITMAP | DRAWMODE_GRAYGRADIENT ) );
/*N*/   FASTBOOL bSettingsMode = ( nMode == (DRAWMODE_SETTINGSLINE | DRAWMODE_SETTINGSFILL | DRAWMODE_SETTINGSTEXT | DRAWMODE_SETTINGSGRADIENT ) );
/*N*/
/*N*/     if( ( bGrayscaleMode || bSettingsMode ) && pPage && pPage->IsMasterPage() )
/*N*/   {
/*?*/       Size aPageSize = pPage->GetSize();
/*?*/       long aRectWidth = aRect.GetSize().Width() - 1;
/*?*/       long aRectHeight = aRect.GetSize().Height() - 1;
/*?*/
/*?*/       // Objekt so gross wie Seite ? -> Hintergrund
/*?*/       if( aRectWidth == aPageSize.Width() &&
/*?*/           aRectHeight == aPageSize.Height()  )
/*?*/       {
/*?*/           return TRUE;
/*?*/       }
/*?*/       // oder so gross wie Seite abzueglich der Raender
/*?*/       if( aRectWidth == aPageSize.Width() -
/*?*/               pPage->GetLftBorder() - pPage->GetRgtBorder() &&
/*?*/           aRectHeight == aPageSize.Height() -
/*?*/               pPage->GetUppBorder() - pPage->GetLwrBorder() )
/*?*/       {
/*?*/           return TRUE;
/*?*/       }
/*?*/
/*N*/   }

/*N*/   if (bTextFrame && aGeo.nShearWink!=0) {
/*?*/       DBG_WARNING("Shearwinkel vom TextFrame innerhalb von SdrRectObj::Paint() auf 0 gesetzt");
/*?*/       ((SdrRectObj*)this)->ImpCheckShear();
/*?*/       ((SdrRectObj*)this)->SetRectsDirty();
/*N*/   }
/*N*/   FASTBOOL bOk=TRUE;
/*N*/   BOOL bHideContour(IsHideContour());
/*N*/   sal_Int32 nEckRad(GetEckenradius());
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
/*?*/         if( bIsFillDraft )
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
/*?*/         {
/*?*/             // #100127# Output original geometry for metafiles
/*?*/             ImpGraphicFill aFill( *this, rXOut, aShadowSet, true );
/*?*/
/*?*/             if (PaintNeedsXPoly(nEckRad)) {
/*?*/                 XPolygon aX(GetXPoly());
/*?*/                 aX.Move(nXDist,nYDist);
/*?*/                 rXOut.DrawXPolygon(aX);
/*?*/             } else {
/*?*/                 Rectangle aR(aRect);
/*?*/                 aR.Move(nXDist,nYDist);
/*?*/                 rXOut.DrawRect(aR,USHORT(2*nEckRad),USHORT(2*nEckRad));
/*?*/             }
/*?*/         }
/*?*/
/*?*/       // new shadow line drawing
/*?*/       if( pLineGeometry.get() )
/*?*/       {
/*?*/           // draw the line geometry
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ImpDrawShadowLineGeometry(rXOut, rSet, *pLineGeometry);
/*?*/       }
/*N*/   }

    // Before here the LineAttr were set: if(pLineAttr) rXOut.SetLineAttr(*pLineAttr);
/*N*/   rXOut.SetLineAttr(aEmptySet);
/*N*/
/*N*/     rXOut.SetFillAttr( bIsFillDraft ? aEmptySet : rSet );
/*N*/
/*N*/   if (!bHideContour) {
/*N*/         // #100127# Output original geometry for metafiles
/*N*/         ImpGraphicFill aFill( *this, rXOut, bIsFillDraft ? aEmptySet : rSet );
/*N*/
/*N*/       if (PaintNeedsXPoly(nEckRad)) {
/*?*/           rXOut.DrawXPolygon(GetXPoly());
/*N*/       } else {
/*N*/           DBG_ASSERT(nEckRad==0,"SdrRectObj::Paint(): XOut.DrawRect() unterstuetz kein Eckenradius!");
/*N*/           rXOut.DrawRect(aRect/*,USHORT(2*nEckRad),USHORT(2*nEckRad)*/);
/*N*/       }
/*N*/   }
/*N*/
/*N*/   DBG_ASSERT(aRect.GetWidth()>1 && aRect.GetHeight()>1,"SdrRectObj::Paint(): Rect hat Nullgroesse (oder negativ)!");
/*N*/
/*N*/   // Own line drawing
/*N*/   if( !bHideContour && pLineGeometry.get() )
/*N*/   {
/*N*/       // draw the line geometry
/*N*/       ImpDrawColorLineGeometry(rXOut, rSet, *pLineGeometry);
/*N*/   }
/*N*/
/*N*/   if (HasText()) {
/*?*/       bOk=SdrTextObj::Paint(rXOut,rInfoRec);
/*N*/   }
/*N*/   if (bOk && (rInfoRec.nPaintMode & SDRPAINTMODE_GLUEPOINTS) !=0) {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 bOk=PaintGluePoints(rXOut,rInfoRec);
/*N*/   }
/*N*/
/*N*/   return bOk;
/*N*/ }

/*N*/ SdrObject* SdrRectObj::ImpCheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer, FASTBOOL bForceFilled, FASTBOOL bForceTol) const
/*N*/ {
/*N*/   if (pVisiLayer!=NULL && !pVisiLayer->IsSet(nLayerId)) return NULL;
/*N*/   INT32 nMyTol=nTol;
/*N*/   FASTBOOL bFilled=bForceFilled || HasFill();
/*N*/   FASTBOOL bPickThrough=pModel!=NULL && pModel->IsPickThroughTransparentTextFrames();
/*N*/   if (bTextFrame && !bPickThrough) bFilled=TRUE;
/*N*/   FASTBOOL bLine=HasLine();
/*N*/
/*N*/   INT32 nWdt=bLine ? ImpGetLineWdt()/2 :0; // Halbe Strichstaerke
/*N*/   long nBoundWdt=aRect.GetWidth()-1;
/*N*/   long nBoundHgt=aRect.GetHeight()-1;
/*N*/   if (bFilled && nBoundWdt>short(nTol) && nBoundHgt>short(nTol) && Abs(aGeo.nShearWink)<=4500) {
/*N*/       if (!bForceTol && !bTextFrame ) nMyTol=0; // Keine Toleranz noetig hier
/*N*/   }
/*N*/   if (nWdt>nMyTol && (!bTextFrame || pEdtOutl==NULL)) nMyTol=nWdt; // Bei dicker Umrandung keine Toleranz noetig, ausser wenn bei TextEdit
/*N*/   Rectangle aR(aRect);
/*N*/   if (nMyTol!=0 && bFilled) {
/*N*/       aR.Left  ()-=nMyTol;
/*N*/       aR.Top   ()-=nMyTol;
/*N*/       aR.Right ()+=nMyTol;
/*N*/       aR.Bottom()+=nMyTol;
/*N*/   }
/*N*/
/*N*/   if (bFilled || bLine || bTextFrame) { // Bei TextFrame so tun, alsob Linie da
/*N*/       unsigned nCnt=0;
/*N*/       INT32 nXShad=0,nYShad=0;
/*N*/       long nEckRad=/*bTextFrame ? 0 :*/ GetEckenradius();
/*N*/       do { // 1 Durchlauf, bei Schatten 2 Durchlaeufe.
/*N*/           if (nCnt!=0) aR.Move(nXShad,nYShad);
/*N*/           if (aGeo.nDrehWink!=0 || aGeo.nShearWink!=0 || nEckRad!=0 || !bFilled) {
/*N*/               Polygon aPol(aR);
/*N*/               if (nEckRad!=0) {
/*N*/                   INT32 nRad=nEckRad;
/*N*/                   if (bFilled) nRad+=nMyTol; // um korrekt zu sein ...
/*N*/                   XPolygon aXPoly(ImpCalcXPoly(aR,nRad));
/*N*/                   aPol=XOutCreatePolygon(aXPoly,NULL);
/*N*/               } else {
/*N*/                   if (aGeo.nShearWink!=0) ShearPoly(aPol,aRect.TopLeft(),aGeo.nTan);
/*N*/                   if (aGeo.nDrehWink!=0) RotatePoly(aPol,aRect.TopLeft(),aGeo.nSin,aGeo.nCos);
/*N*/               }
/*N*/               if (bFilled) {
/*N*/                   if (IsPointInsidePoly(aPol,rPnt)) return (SdrObject*)this;
/*N*/               } else {
/*N*/                   Rectangle aTouchRect(rPnt.X()-nMyTol,rPnt.Y()-nMyTol,rPnt.X()+nMyTol,rPnt.Y()+nMyTol);
/*N*/                   if (IsRectTouchesLine(aPol,aTouchRect)) return (SdrObject*)this;
/*N*/               }
/*N*/           } else {
/*N*/               if (aR.IsInside(rPnt)) return (SdrObject*)this;
/*N*/           }
/*N*/       } while (nCnt++==0 && ImpGetShadowDist(nXShad,nYShad));
/*N*/   }
/*N*/   FASTBOOL bCheckText=TRUE;
/*N*/   if (bCheckText && HasText() && (!bTextFrame || bPickThrough)) {
/*N*/       return SdrTextObj::CheckHit(rPnt,nTol,pVisiLayer);
/*N*/   }
/*N*/   return NULL;
/*N*/ }

/*N*/ SdrObject* SdrRectObj::CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const
/*N*/ {
/*N*/   return ImpCheckHit(rPnt,nTol,pVisiLayer,FALSE/*,bTextFrame*/);
/*N*/ }

//STRIP001 void SdrRectObj::TakeObjNameSingul(XubString& rName) const
//STRIP001 {
//STRIP001  if (IsTextFrame())
//STRIP001  {
//STRIP001      SdrTextObj::TakeObjNameSingul(rName);
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      USHORT nResId=STR_ObjNameSingulRECT;
//STRIP001      if (aGeo.nShearWink!=0) {
//STRIP001          nResId+=4;  // Parallelogramm oder Raute
//STRIP001          // Raute ist nicht, weil Shear die vertikalen Kanten verlaengert!
//STRIP001          // Wenn Zeit ist, werde ich das mal berechnen.
//STRIP001      } else {
//STRIP001          if (aRect.GetWidth()==aRect.GetHeight()) nResId+=2; // Quadrat
//STRIP001      }
//STRIP001      if (GetEckenradius()!=0) nResId+=8; // abgerundet
//STRIP001      rName=ImpGetResStr(nResId);
//STRIP001
//STRIP001      String aName( GetName() );
//STRIP001      if(aName.Len())
//STRIP001      {
//STRIP001          rName += sal_Unicode(' ');
//STRIP001          rName += sal_Unicode('\'');
//STRIP001          rName += aName;
//STRIP001          rName += sal_Unicode('\'');
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrRectObj::TakeObjNamePlural(XubString& rName) const
//STRIP001 {
//STRIP001  if (IsTextFrame()) SdrTextObj::TakeObjNamePlural(rName);
//STRIP001  else {
//STRIP001      USHORT nResId=STR_ObjNamePluralRECT;
//STRIP001      if (aGeo.nShearWink!=0) {
//STRIP001          nResId+=4;  // Parallelogramm oder Raute
//STRIP001      } else {
//STRIP001          if (aRect.GetWidth()==aRect.GetHeight()) nResId+=2; // Quadrat
//STRIP001      }
//STRIP001      if (GetEckenradius()!=0) nResId+=8; // abgerundet
//STRIP001      rName=ImpGetResStr(nResId);
//STRIP001  }
//STRIP001 }

/*N*/ void SdrRectObj::operator=(const SdrObject& rObj)
/*N*/ {
/*N*/   SdrTextObj::operator=(rObj);
/*N*/ }

/*N*/ void SdrRectObj::TakeXorPoly(XPolyPolygon& rPoly, FASTBOOL bDetail) const
/*N*/ {
/*N*/   rPoly=XPolyPolygon(ImpCalcXPoly(aRect,GetEckenradius()));
/*N*/ }

/*N*/ void SdrRectObj::TakeContour(XPolyPolygon& rPoly) const
/*N*/ {
/*N*/   SdrTextObj::TakeContour(rPoly);
/*N*/ }

//STRIP001 void SdrRectObj::TakeContour(XPolyPolygon& rXPoly, SdrContourType eType) const
//STRIP001 {
//STRIP001 }

/*N*/ void SdrRectObj::RecalcSnapRect()
/*N*/ {
/*N*/   long nEckRad=GetEckenradius();
/*N*/   if ((aGeo.nDrehWink!=0 || aGeo.nShearWink!=0) && nEckRad!=0) {
/*?*/       maSnapRect=GetXPoly().GetBoundRect();
/*N*/   } else {
/*N*/       SdrTextObj::RecalcSnapRect();
/*N*/   }
/*N*/ }

/*N*/ void SdrRectObj::NbcSetSnapRect(const Rectangle& rRect)
/*N*/ {
/*N*/   SdrTextObj::NbcSetSnapRect(rRect);
/*N*/   SetXPolyDirty();
/*N*/ }

/*N*/ void SdrRectObj::NbcSetLogicRect(const Rectangle& rRect)
/*N*/ {
/*N*/   SdrTextObj::NbcSetLogicRect(rRect);
/*N*/   SetXPolyDirty();
/*N*/ }

//STRIP001 USHORT SdrRectObj::GetHdlCount() const
//STRIP001 {
//STRIP001  return 9;
//STRIP001 }

//STRIP001 SdrHdl* SdrRectObj::GetHdl(USHORT nHdlNum) const
//STRIP001 {
//STRIP001  SdrHdl* pH=NULL;
//STRIP001  Point aPnt;
//STRIP001  SdrHdlKind eKind=HDL_MOVE;
//STRIP001  switch (nHdlNum) {
//STRIP001      case 0: {
//STRIP001          long a=GetEckenradius();
//STRIP001          long b=Max(aRect.GetWidth(),aRect.GetHeight())/2; // Wird aufgerundet, da GetWidth() eins draufaddiert
//STRIP001          if (a>b) a=b;
//STRIP001          if (a<0) a=0;
//STRIP001          aPnt=aRect.TopLeft();
//STRIP001          aPnt.X()+=a;
//STRIP001          eKind=HDL_CIRC;
//STRIP001      } break; // Eckenradius
//STRIP001      case 1: aPnt=aRect.TopLeft();      eKind=HDL_UPLFT; break; // Oben links
//STRIP001      case 2: aPnt=aRect.TopCenter();    eKind=HDL_UPPER; break; // Oben
//STRIP001      case 3: aPnt=aRect.TopRight();     eKind=HDL_UPRGT; break; // Oben rechts
//STRIP001      case 4: aPnt=aRect.LeftCenter();   eKind=HDL_LEFT ; break; // Links
//STRIP001      case 5: aPnt=aRect.RightCenter();  eKind=HDL_RIGHT; break; // Rechts
//STRIP001      case 6: aPnt=aRect.BottomLeft();   eKind=HDL_LWLFT; break; // Unten links
//STRIP001      case 7: aPnt=aRect.BottomCenter(); eKind=HDL_LOWER; break; // Unten
//STRIP001      case 8: aPnt=aRect.BottomRight();  eKind=HDL_LWRGT; break; // Unten rechts
//STRIP001  }
//STRIP001  if (aGeo.nShearWink!=0) ShearPoint(aPnt,aRect.TopLeft(),aGeo.nTan);
//STRIP001  if (aGeo.nDrehWink!=0) RotatePoint(aPnt,aRect.TopLeft(),aGeo.nSin,aGeo.nCos);
//STRIP001  if (eKind!=HDL_MOVE) {
//STRIP001      pH=new SdrHdl(aPnt,eKind);
//STRIP001      pH->SetObj((SdrObject*)this);
//STRIP001      pH->SetDrehWink(aGeo.nDrehWink);
//STRIP001  }
//STRIP001  return pH;
//STRIP001 }

//STRIP001 FASTBOOL SdrRectObj::HasSpecialDrag() const
//STRIP001 {
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 FASTBOOL SdrRectObj::BegDrag(SdrDragStat& rDrag) const
//STRIP001 {
//STRIP001  FASTBOOL bRad=rDrag.GetHdl()!=NULL && rDrag.GetHdl()->GetKind()==HDL_CIRC;
//STRIP001  if (bRad) {
//STRIP001      rDrag.SetEndDragChangesAttributes(TRUE);
//STRIP001      return TRUE;
//STRIP001  } else {
//STRIP001      return SdrTextObj::BegDrag(rDrag);
//STRIP001  }
//STRIP001 }

//STRIP001 FASTBOOL SdrRectObj::MovDrag(SdrDragStat& rDrag) const
//STRIP001 {
//STRIP001  FASTBOOL bRad=rDrag.GetHdl()!=NULL && rDrag.GetHdl()->GetKind()==HDL_CIRC;
//STRIP001  if (bRad) {
//STRIP001      return TRUE;
//STRIP001  } else {
//STRIP001      return SdrTextObj::MovDrag(rDrag);
//STRIP001  }
//STRIP001 }

//STRIP001 FASTBOOL SdrRectObj::EndDrag(SdrDragStat& rDrag)
//STRIP001 {
//STRIP001  FASTBOOL bRad=rDrag.GetHdl()!=NULL && rDrag.GetHdl()->GetKind()==HDL_CIRC;
//STRIP001  if (bRad) {
//STRIP001      Rectangle aBoundRect0; if (pUserCall!=NULL) aBoundRect0=GetBoundRect();
//STRIP001      SendRepaintBroadcast();
//STRIP001      Point aPt(rDrag.GetNow());
//STRIP001      if (aGeo.nDrehWink!=0) RotatePoint(aPt,aRect.TopLeft(),-aGeo.nSin,aGeo.nCos); // -sin fuer Umkehrung
//STRIP001      // Shear nicht noetig, da Pt auf einer Linie mit dem RefPt (LiOb Ecke des Rect)
//STRIP001      long nRad=aPt.X()-aRect.Left();
//STRIP001      if (nRad<0) nRad=0;
//STRIP001      long nAltRad=GetEckenradius();
//STRIP001      if (nRad!=nAltRad) NbcSetEckenradius(nRad);
//STRIP001      SetChanged();
//STRIP001      SetRectsDirty();
//STRIP001      SetXPolyDirty();
//STRIP001      SendRepaintBroadcast();
//STRIP001      SendUserCall(SDRUSERCALL_RESIZE,aBoundRect0);
//STRIP001      return TRUE;
//STRIP001  } else {
//STRIP001      return SdrTextObj::EndDrag(rDrag);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrRectObj::BrkDrag(SdrDragStat& rDrag) const
//STRIP001 {
//STRIP001  FASTBOOL bRad=rDrag.GetHdl()!=NULL && rDrag.GetHdl()->GetKind()==HDL_CIRC;
//STRIP001  if (bRad) {
//STRIP001  } else {
//STRIP001      SdrTextObj::BrkDrag(rDrag);
//STRIP001  }
//STRIP001 }

//STRIP001 XubString SdrRectObj::GetDragComment(const SdrDragStat& rDrag, FASTBOOL bUndoDragComment, FASTBOOL bCreateComment) const
//STRIP001 {
//STRIP001  if(bCreateComment)
//STRIP001      return String();
//STRIP001
//STRIP001  BOOL bRad(rDrag.GetHdl() && rDrag.GetHdl()->GetKind() == HDL_CIRC);
//STRIP001
//STRIP001  if(bRad)
//STRIP001  {
//STRIP001      Point aPt(rDrag.GetNow());
//STRIP001
//STRIP001      // -sin fuer Umkehrung
//STRIP001      if(aGeo.nDrehWink)
//STRIP001          RotatePoint(aPt, aRect.TopLeft(), -aGeo.nSin, aGeo.nCos);
//STRIP001
//STRIP001      INT32 nRad(aPt.X() - aRect.Left());
//STRIP001
//STRIP001      if(nRad < 0)
//STRIP001          nRad = 0;
//STRIP001
//STRIP001      XubString aStr;
//STRIP001
//STRIP001      ImpTakeDescriptionStr(STR_DragRectEckRad, aStr);
//STRIP001      aStr.AppendAscii(" (");
//STRIP001      aStr += GetMetrStr(nRad);
//STRIP001      aStr += sal_Unicode(')');
//STRIP001
//STRIP001      return aStr;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      return SdrTextObj::GetDragComment(rDrag, bUndoDragComment, FALSE);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrRectObj::TakeDragPoly(const SdrDragStat& rDrag, XPolyPolygon& rXPP) const
//STRIP001 {
//STRIP001  rXPP.Clear();
//STRIP001  FASTBOOL bRad=rDrag.GetHdl()!=NULL && rDrag.GetHdl()->GetKind()==HDL_CIRC;
//STRIP001  FASTBOOL bRectSiz=!bRad;
//STRIP001  if (bRad) {
//STRIP001      Point aPt(rDrag.GetNow());
//STRIP001      if (aGeo.nDrehWink!=0) RotatePoint(aPt,aRect.TopLeft(),-aGeo.nSin,aGeo.nCos); // -sin fuer Umkehrung
//STRIP001      // Shear nicht noetig, da Pt auf einer Linie mit dem RefPt (LiOb Ecke des Rect)
//STRIP001      long nRad=aPt.X()-aRect.Left();
//STRIP001      if (nRad<0) nRad=0;
//STRIP001      rXPP.Insert(ImpCalcXPoly(aRect,nRad));
//STRIP001  } else {
//STRIP001      rXPP.Insert(ImpCalcXPoly(ImpDragCalcRect(rDrag),GetEckenradius()));
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrRectObj::TakeCreatePoly(const SdrDragStat& rDrag, XPolyPolygon& rXPP) const
//STRIP001 {
//STRIP001  Rectangle aRect1;
//STRIP001  rDrag.TakeCreateRect(aRect1);
//STRIP001  aRect1.Justify();
//STRIP001  rXPP=XPolyPolygon(ImpCalcXPoly(aRect1,GetEckenradius()));
//STRIP001 }

/*N*/ Pointer SdrRectObj::GetCreatePointer() const
/*N*/ {
/*N*/   if (IsTextFrame()) return Pointer(POINTER_DRAW_TEXT);
/*N*/   return Pointer(POINTER_DRAW_RECT);
/*N*/ }

/*N*/ void SdrRectObj::NbcMove(const Size& rSiz)
/*N*/ {
/*N*/   SdrTextObj::NbcMove(rSiz);
/*N*/   SetXPolyDirty();
/*N*/ }

/*N*/ void SdrRectObj::NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact)
/*N*/ {
/*N*/   SdrTextObj::NbcResize(rRef,xFact,yFact);
/*N*/   SetXPolyDirty();
/*N*/ }

/*N*/ void SdrRectObj::NbcRotate(const Point& rRef, long nWink, double sn, double cs)
/*N*/ {
/*N*/   SdrTextObj::NbcRotate(rRef,nWink,sn,cs);
/*N*/   SetXPolyDirty();
/*N*/ }

/*N*/ void SdrRectObj::NbcShear(const Point& rRef, long nWink, double tn, FASTBOOL bVShear)
/*N*/ {
/*N*/   SdrTextObj::NbcShear(rRef,nWink,tn,bVShear);
/*N*/   SetXPolyDirty();
/*N*/ }

//STRIP001 void SdrRectObj::NbcMirror(const Point& rRef1, const Point& rRef2)
//STRIP001 {
//STRIP001  SdrTextObj::NbcMirror(rRef1,rRef2);
//STRIP001  SetXPolyDirty();
//STRIP001 }

//STRIP001 FASTBOOL SdrRectObj::DoMacro(const SdrObjMacroHitRec& rRec)
//STRIP001 {
//STRIP001  return SdrTextObj::DoMacro(rRec);
//STRIP001 }

//STRIP001 XubString SdrRectObj::GetMacroPopupComment(const SdrObjMacroHitRec& rRec) const
//STRIP001 {
//STRIP001  return SdrTextObj::GetMacroPopupComment(rRec);
//STRIP001 }

/*N*/ SdrGluePoint SdrRectObj::GetVertexGluePoint(USHORT nPosNum) const
/*N*/ {
/*N*/   INT32 nWdt = ((XLineWidthItem&)(GetItem(XATTR_LINEWIDTH))).GetValue();
/*N*/   nWdt++;
/*N*/   nWdt /= 2;
/*N*/
/*N*/   Point aPt;
/*N*/   switch (nPosNum) {
/*N*/       case 0: aPt=aRect.TopCenter();    aPt.Y()-=nWdt; break;
/*N*/       case 1: aPt=aRect.RightCenter();  aPt.X()+=nWdt; break;
/*N*/       case 2: aPt=aRect.BottomCenter(); aPt.Y()+=nWdt; break;
/*N*/       case 3: aPt=aRect.LeftCenter();   aPt.X()-=nWdt; break;
/*N*/   }
/*N*/   if (aGeo.nShearWink!=0) ShearPoint(aPt,aRect.TopLeft(),aGeo.nTan);
/*N*/   if (aGeo.nDrehWink!=0) RotatePoint(aPt,aRect.TopLeft(),aGeo.nSin,aGeo.nCos);
/*N*/   aPt-=GetSnapRect().Center();
/*N*/   SdrGluePoint aGP(aPt);
/*N*/   aGP.SetPercent(FALSE);
/*N*/   return aGP;
/*N*/ }

//STRIP001 SdrGluePoint SdrRectObj::GetCornerGluePoint(USHORT nPosNum) const
//STRIP001 {
//STRIP001  INT32 nWdt = ((XLineWidthItem&)(GetItem(XATTR_LINEWIDTH))).GetValue();
//STRIP001  nWdt++;
//STRIP001  nWdt /= 2;
//STRIP001
//STRIP001  Point aPt;
//STRIP001  switch (nPosNum) {
//STRIP001      case 0: aPt=aRect.TopLeft();     aPt.X()-=nWdt; aPt.Y()-=nWdt; break;
//STRIP001      case 1: aPt=aRect.TopRight();    aPt.X()+=nWdt; aPt.Y()-=nWdt; break;
//STRIP001      case 2: aPt=aRect.BottomRight(); aPt.X()+=nWdt; aPt.Y()+=nWdt; break;
//STRIP001      case 3: aPt=aRect.BottomLeft();  aPt.X()-=nWdt; aPt.Y()+=nWdt; break;
//STRIP001  }
//STRIP001  if (aGeo.nShearWink!=0) ShearPoint(aPt,aRect.TopLeft(),aGeo.nTan);
//STRIP001  if (aGeo.nDrehWink!=0) RotatePoint(aPt,aRect.TopLeft(),aGeo.nSin,aGeo.nCos);
//STRIP001  aPt-=GetSnapRect().Center();
//STRIP001  SdrGluePoint aGP(aPt);
//STRIP001  aGP.SetPercent(FALSE);
//STRIP001  return aGP;
//STRIP001 }

//STRIP001 SdrObject* SdrRectObj::DoConvertToPolyObj(BOOL bBezier) const
//STRIP001 {
//STRIP001  XPolygon aXP(ImpCalcXPoly(aRect,GetEckenradius()));
//STRIP001  { // #40608# Nur Uebergangsweise bis zum neuen TakeContour()
//STRIP001      aXP.Remove(0,1);
//STRIP001      aXP[aXP.GetPointCount()-1]=aXP[0];
//STRIP001  }
//STRIP001  SdrObject* pRet=NULL;
//STRIP001  if (!IsTextFrame() || HasFill() || HasLine()) {
//STRIP001      pRet=ImpConvertMakeObj(XPolyPolygon(aXP),TRUE,bBezier);
//STRIP001  }
//STRIP001  pRet=ImpConvertAddText(pRet,bBezier);
//STRIP001  return pRet;
//STRIP001 }

/*N*/ void SdrRectObj::SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType)
/*N*/ {
/*N*/   SdrTextObj::SFX_NOTIFY(rBC,rBCType,rHint,rHintType);
/*N*/   SetXPolyDirty(); // wg. Eckenradius
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// private support routines for ItemSet access
/*N*/ void SdrRectObj::ItemSetChanged(const SfxItemSet& rSet)
/*N*/ {
/*N*/   // call parent
/*N*/   SdrTextObj::ItemSetChanged(rSet);
/*N*/
/*N*/   // local changes
/*N*/   SetXPolyDirty();
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrRectObj::NbcSetStyleSheet(SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr)
/*N*/ {
/*N*/   SdrTextObj::NbcSetStyleSheet(pNewStyleSheet,bDontRemoveHardAttr);
/*N*/   SetXPolyDirty(); // wg. Eckenradius
/*N*/ }

/*N*/ SdrObjGeoData* SdrRectObj::NewGeoData() const
/*N*/ { // etwas umstaendlicher, damit's vielleicht unter Chicago durchgeht
/*N*/   SdrObjGeoData* pGeo=new SdrRectObjGeoData;
/*N*/   return pGeo;
/*N*/ }

/*N*/ void SdrRectObj::SaveGeoData(SdrObjGeoData& rGeo) const
/*N*/ {
/*N*/   SdrTextObj::SaveGeoData(rGeo);
/*N*/   SdrRectObjGeoData& rRGeo=(SdrRectObjGeoData&)rGeo;
/*N*/   rRGeo.nEckRad=GetEckenradius();
/*N*/ }

/*?*/ void SdrRectObj::RestGeoData(const SdrObjGeoData& rGeo)
/*?*/ { // RectsDirty wird von SdrObject gerufen
/*?*/   SdrTextObj::RestGeoData(rGeo);
/*?*/   SdrRectObjGeoData& rRGeo=(SdrRectObjGeoData&)rGeo;
/*?*/   long nAltRad=GetEckenradius();
/*?*/   if (rRGeo.nEckRad!=nAltRad) NbcSetEckenradius(rRGeo.nEckRad);
/*?*/   SetXPolyDirty();
/*?*/ }

/*N*/ void SdrRectObj::WriteData(SvStream& rOut) const
/*N*/ {
/*N*/   SdrTextObj::WriteData(rOut);
/*N*/   SdrDownCompat aCompat(rOut,STREAM_WRITE); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("SdrRectObj");
/*N*/ #endif
/*N*/ }

/*N*/ void SdrRectObj::ReadData(const SdrObjIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   if (rIn.GetError()!=0) return;
/*N*/   SdrTextObj::ReadData(rHead,rIn);
/*N*/   if (IsTextFrame() && rHead.GetVersion()<3 && !HAS_BASE(SdrCaptionObj,this)) {
/*N*/       // Bis einschl. Version 2 wurden Textrahmen mit SdrTextObj dargestellt, ausser CaptionObj
/*?*/       SfxItemPool* pPool=GetItemPool();
/*?*/       if (pPool!=NULL) {
/*?*/           // Umrandung und Hintergrund des importierten Textrahmens ausschalten
/*?*/           SfxItemSet aSet(*pPool);
/*?*/           aSet.Put(XFillColorItem(String(),Color(COL_WHITE))); // Falls einer auf Solid umschaltet
/*?*/           aSet.Put(XFillStyleItem(XFILL_NONE));
/*?*/           aSet.Put(XLineColorItem(String(),Color(COL_BLACK))); // Falls einer auf Solid umschaltet
/*?*/           aSet.Put(XLineStyleItem(XLINE_NONE));
/*?*/
/*?*/           SetItemSet(aSet);
/*N*/       }
/*N*/   } else {
/*N*/       SdrDownCompat aCompat(rIn,STREAM_READ); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/ #ifdef DBG_UTIL
/*N*/       aCompat.SetID("SdrRectObj");
/*N*/ #endif
/*N*/       if (rHead.GetVersion()<=5) {
/*N*/           long nEckRad;
/*?*/           rIn>>nEckRad;
/*?*/           long nAltRad=GetEckenradius();
/*?*/           if (nEckRad!=nAltRad) NbcSetEckenradius(nEckRad);
/*N*/       }
/*N*/   }
/*N*/   SetXPolyDirty();
/*N*/ }

}
