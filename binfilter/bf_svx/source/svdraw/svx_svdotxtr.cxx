/*************************************************************************
 *
 *  $RCSfile: svx_svdotxtr.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:46:25 $
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

#include "svdotext.hxx"
#include "xoutx.hxx"     // fuer XOutCreatePolygon
#include "svditext.hxx"
#include "svdtrans.hxx"
#include "svdogrp.hxx"
#include "svdopath.hxx"
#include "svdoutl.hxx"
#include "svdtxhdl.hxx"  // DrawTextToPath fuer Convert
#include "svdpage.hxx"   // fuer Convert
#include "svdmodel.hxx"  // fuer Convert

#ifndef _OUTLINER_HXX //autogen
#include "outliner.hxx"
#endif
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@@@@@ @@@@@ @@   @@ @@@@@@  @@@@  @@@@@  @@@@@@
//    @@   @@    @@@ @@@   @@   @@  @@ @@  @@     @@
//    @@   @@     @@@@@    @@   @@  @@ @@  @@     @@
//    @@   @@@@    @@@     @@   @@  @@ @@@@@      @@
//    @@   @@     @@@@@    @@   @@  @@ @@  @@     @@
//    @@   @@    @@@ @@@   @@   @@  @@ @@  @@ @@  @@
//    @@   @@@@@ @@   @@   @@    @@@@  @@@@@   @@@@
//
//  Transformationen
//
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrTextObj::NbcSetSnapRect(const Rectangle& rRect)
/*N*/ {
/*N*/   if (aGeo.nDrehWink!=0 || aGeo.nShearWink!=0) {
/*?*/       Rectangle aSR0(GetSnapRect());
/*?*/       long nWdt0=aSR0.Right()-aSR0.Left();
/*?*/       long nHgt0=aSR0.Bottom()-aSR0.Top();
/*?*/       long nWdt1=rRect.Right()-rRect.Left();
/*?*/       long nHgt1=rRect.Bottom()-rRect.Top();
/*?*/       SdrTextObj::NbcResize(maSnapRect.TopLeft(),Fraction(nWdt1,nWdt0),Fraction(nHgt1,nHgt0));
/*?*/       SdrTextObj::NbcMove(Size(rRect.Left()-aSR0.Left(),rRect.Top()-aSR0.Top()));
/*N*/   } else {
/*N*/       long nHDist=GetTextLeftDistance()+GetTextRightDistance();
/*N*/       long nVDist=GetTextUpperDistance()+GetTextLowerDistance();
/*N*/       long nTWdt0=aRect.GetWidth ()-1-nHDist; if (nTWdt0<0) nTWdt0=0;
/*N*/       long nTHgt0=aRect.GetHeight()-1-nVDist; if (nTHgt0<0) nTHgt0=0;
/*N*/       long nTWdt1=rRect.GetWidth ()-1-nHDist; if (nTWdt1<0) nTWdt1=0;
/*N*/       long nTHgt1=rRect.GetHeight()-1-nVDist; if (nTHgt1<0) nTHgt1=0;
/*N*/       aRect=rRect;
/*N*/       ImpJustifyRect(aRect);
/*N*/       if (bTextFrame && (pModel==NULL || !pModel->IsPasteResize())) { // #51139#
/*N*/           if (nTWdt0!=nTWdt1 && IsAutoGrowWidth() ) NbcSetMinTextFrameWidth(nTWdt1);
/*N*/           if (nTHgt0!=nTHgt1 && IsAutoGrowHeight()) NbcSetMinTextFrameHeight(nTHgt1);
/*N*/           if (GetFitToSize()==SDRTEXTFIT_RESIZEATTR) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/                NbcResizeTextAttributes(Fraction(nTWdt1,nTWdt0),Fraction(nTHgt1,nTHgt0));
/*N*/           }
/*N*/           NbcAdjustTextFrameWidthAndHeight();
/*N*/       }
/*N*/       ImpCheckShear();
/*N*/       SetRectsDirty();
/*N*/   }
/*N*/ }

/*N*/ const Rectangle& SdrTextObj::GetLogicRect() const
/*N*/ {
/*N*/   return aRect;
/*N*/ }

/*N*/ void SdrTextObj::NbcSetLogicRect(const Rectangle& rRect)
/*N*/ {
/*N*/   long nHDist=GetTextLeftDistance()+GetTextRightDistance();
/*N*/   long nVDist=GetTextUpperDistance()+GetTextLowerDistance();
/*N*/   long nTWdt0=aRect.GetWidth ()-1-nHDist; if (nTWdt0<0) nTWdt0=0;
/*N*/   long nTHgt0=aRect.GetHeight()-1-nVDist; if (nTHgt0<0) nTHgt0=0;
/*N*/   long nTWdt1=rRect.GetWidth ()-1-nHDist; if (nTWdt1<0) nTWdt1=0;
/*N*/   long nTHgt1=rRect.GetHeight()-1-nVDist; if (nTHgt1<0) nTHgt1=0;
/*N*/   aRect=rRect;
/*N*/   ImpJustifyRect(aRect);
/*N*/   if (bTextFrame) {
/*N*/       if (nTWdt0!=nTWdt1 && IsAutoGrowWidth() ) NbcSetMinTextFrameWidth(nTWdt1);
/*N*/       if (nTHgt0!=nTHgt1 && IsAutoGrowHeight()) NbcSetMinTextFrameHeight(nTHgt1);
/*N*/       if (GetFitToSize()==SDRTEXTFIT_RESIZEATTR) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            NbcResizeTextAttributes(Fraction(nTWdt1,nTWdt0),Fraction(nTHgt1,nTHgt0));
/*N*/       }
/*N*/       NbcAdjustTextFrameWidthAndHeight();
/*N*/   }
/*N*/   SetRectsDirty();
/*N*/ }

/*N*/ long SdrTextObj::GetRotateAngle() const
/*N*/ {
/*N*/   return aGeo.nDrehWink;
/*N*/ }

/*N*/ long SdrTextObj::GetShearAngle(FASTBOOL bVertical) const
/*N*/ {
/*N*/   return (aGeo.nDrehWink==0 || aGeo.nDrehWink==18000) ? aGeo.nShearWink : 0;
/*N*/ }

/*N*/ void SdrTextObj::NbcMove(const Size& rSiz)
/*N*/ {
/*N*/   MoveRect(aRect,rSiz);
/*N*/   MoveRect(aOutRect,rSiz);
/*N*/   MoveRect(maSnapRect,rSiz);
/*N*/   SetRectsDirty(TRUE);
/*N*/ }

/*N*/ void SdrTextObj::NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact)
/*N*/ {
/*N*/   FASTBOOL bNoShearMerk=aGeo.nShearWink==0;
/*N*/   FASTBOOL bRota90Merk=bNoShearMerk && aGeo.nDrehWink % 9000 ==0;
/*N*/   long nHDist=GetTextLeftDistance()+GetTextRightDistance();
/*N*/   long nVDist=GetTextUpperDistance()+GetTextLowerDistance();
/*N*/   long nTWdt0=aRect.GetWidth ()-1-nHDist; if (nTWdt0<0) nTWdt0=0;
/*N*/   long nTHgt0=aRect.GetHeight()-1-nVDist; if (nTHgt0<0) nTHgt0=0;
/*N*/   FASTBOOL bXMirr=(xFact.GetNumerator()<0) != (xFact.GetDenominator()<0);
/*N*/   FASTBOOL bYMirr=(yFact.GetNumerator()<0) != (yFact.GetDenominator()<0);
/*N*/   if (bXMirr || bYMirr) {
/*N*/       Point aRef1(GetSnapRect().Center());
/*N*/       if (bXMirr) {
/*N*/           Point aRef2(aRef1);
/*N*/           aRef2.Y()++;
/*N*/           NbcMirrorGluePoints(aRef1,aRef2);
/*N*/       }
/*N*/       if (bYMirr) {
/*N*/           Point aRef2(aRef1);
/*N*/           aRef2.X()++;
/*N*/           NbcMirrorGluePoints(aRef1,aRef2);
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (aGeo.nDrehWink==0 && aGeo.nShearWink==0) {
/*N*/       ResizeRect(aRect,rRef,xFact,yFact);
/*N*/       if (bYMirr) {
/*N*/           aRect.Justify();
/*N*/           aRect.Move(aRect.Right()-aRect.Left(),aRect.Bottom()-aRect.Top());
/*N*/           aGeo.nDrehWink=18000;
/*N*/           aGeo.RecalcSinCos();
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       // #100663# aRect is NOT initialized for lines (polgon objects with two
/*N*/       // exceptionally handled points). Thus, after this call the text rotaion is
/*N*/       // gone. This error must be present since day one of this old drawing layer.
/*N*/       // It's astonishing that noone discovered it earlier.
/*N*/       // Polygon aPol(Rect2Poly(aRect,aGeo));
/*N*/       // Polygon aPol(Rect2Poly(GetSnapRect(), aGeo));
/*N*/
/*N*/       // #101412# go back to old method, side effects are impossible
/*N*/       // to calculate.
/*N*/       Polygon aPol(Rect2Poly(aRect,aGeo));
/*N*/
/*N*/       for(sal_uInt16 a(0); a < aPol.GetSize(); a++)
/*N*/       {
/*N*/            ResizePoint(aPol[a], rRef, xFact, yFact);
/*N*/       }
/*N*/
/*N*/       if(bXMirr != bYMirr)
/*N*/       {
/*N*/           // Polygon wenden und etwas schieben
/*N*/           Polygon aPol0(aPol);
/*N*/
/*N*/           aPol[0] = aPol0[1];
/*N*/           aPol[1] = aPol0[0];
/*N*/           aPol[2] = aPol0[3];
/*N*/           aPol[3] = aPol0[2];
/*N*/           aPol[4] = aPol0[1];
/*N*/       }
/*N*/
/*N*/       Poly2Rect(aPol, aRect, aGeo);
/*N*/   }
/*N*/
/*N*/   if (bRota90Merk) {
/*N*/       FASTBOOL bRota90=aGeo.nDrehWink % 9000 ==0;
/*N*/       if (!bRota90) { // Scheinbar Rundungsfehler: Korregieren
/*N*/           long a=NormAngle360(aGeo.nDrehWink);
/*N*/           if (a<4500) a=0;
/*N*/           else if (a<13500) a=9000;
/*N*/           else if (a<22500) a=18000;
/*N*/           else if (a<31500) a=27000;
/*N*/           else a=0;
/*N*/           aGeo.nDrehWink=a;
/*N*/           aGeo.RecalcSinCos();
/*N*/       }
/*N*/       if (bNoShearMerk!=(aGeo.nShearWink==0)) { // Shear ggf. korregieren wg. Rundungsfehler
/*N*/           aGeo.nShearWink=0;
/*N*/           aGeo.RecalcTan();
/*N*/       }
/*N*/   }
/*N*/
/*N*/   ImpJustifyRect(aRect);
/*N*/   long nTWdt1=aRect.GetWidth ()-1-nHDist; if (nTWdt1<0) nTWdt1=0;
/*N*/   long nTHgt1=aRect.GetHeight()-1-nVDist; if (nTHgt1<0) nTHgt1=0;
/*N*/   if (bTextFrame && (pModel==NULL || !pModel->IsPasteResize())) { // #51139#
/*N*/       if (nTWdt0!=nTWdt1 && IsAutoGrowWidth() ) NbcSetMinTextFrameWidth(nTWdt1);
/*N*/       if (nTHgt0!=nTHgt1 && IsAutoGrowHeight()) NbcSetMinTextFrameHeight(nTHgt1);
/*N*/       if (GetFitToSize()==SDRTEXTFIT_RESIZEATTR) {
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 NbcResizeTextAttributes(Fraction(nTWdt1,nTWdt0),Fraction(nTHgt1,nTHgt0));
/*N*/       }
/*?*/       NbcAdjustTextFrameWidthAndHeight();
/*N*/   }
/*N*/   ImpCheckShear();
/*N*/   SetRectsDirty();
/*N*/ }

/*N*/ void SdrTextObj::NbcRotate(const Point& rRef, long nWink, double sn, double cs)
/*N*/ {
/*N*/   SetGlueReallyAbsolute(TRUE);
/*N*/   long dx=aRect.Right()-aRect.Left();
/*N*/   long dy=aRect.Bottom()-aRect.Top();
/*N*/   Point aP(aRect.TopLeft());
/*N*/   RotatePoint(aP,rRef,sn,cs);
/*N*/   aRect.Left()=aP.X();
/*N*/   aRect.Top()=aP.Y();
/*N*/   aRect.Right()=aRect.Left()+dx;
/*N*/   aRect.Bottom()=aRect.Top()+dy;
/*N*/   if (aGeo.nDrehWink==0) {
/*N*/       aGeo.nDrehWink=NormAngle360(nWink);
/*N*/       aGeo.nSin=sn;
/*N*/       aGeo.nCos=cs;
/*N*/   } else {
/*N*/       aGeo.nDrehWink=NormAngle360(aGeo.nDrehWink+nWink);
/*N*/       aGeo.RecalcSinCos();
/*N*/   }
/*N*/   SetRectsDirty();
/*N*/   NbcRotateGluePoints(rRef,nWink,sn,cs);
/*N*/   SetGlueReallyAbsolute(FALSE);
/*N*/ }

/*N*/ void SdrTextObj::NbcShear(const Point& rRef, long nWink, double tn, FASTBOOL bVShear)
/*N*/ {
/*N*/   SetGlueReallyAbsolute(TRUE);
/*N*/
/*N*/   // #75889# when this is a SdrPathObj aRect maybe not initialized
/*N*/   Polygon aPol(Rect2Poly(aRect.IsEmpty() ? GetSnapRect() : aRect, aGeo));
/*N*/
/*N*/   USHORT nPointCount=aPol.GetSize();
/*N*/   for (USHORT i=0; i<nPointCount; i++) {
/*N*/        ShearPoint(aPol[i],rRef,tn,bVShear);
/*N*/   }
/*N*/   Poly2Rect(aPol,aRect,aGeo);
/*N*/   ImpJustifyRect(aRect);
/*N*/   if (bTextFrame) {
/*?*/       NbcAdjustTextFrameWidthAndHeight();
/*N*/   }
/*N*/   ImpCheckShear();
/*N*/   SetRectsDirty();
/*N*/   NbcShearGluePoints(rRef,nWink,tn,bVShear);
/*N*/   SetGlueReallyAbsolute(FALSE);
/*N*/ }

//STRIP001 void SdrTextObj::NbcMirror(const Point& rRef1, const Point& rRef2)
//STRIP001 {
//STRIP001  SetGlueReallyAbsolute(TRUE);
//STRIP001  FASTBOOL bNoShearMerk=aGeo.nShearWink==0;
//STRIP001  FASTBOOL bRota90Merk=FALSE;
//STRIP001  if (bNoShearMerk &&
//STRIP001      (rRef1.X()==rRef2.X() || rRef1.Y()==rRef2.Y() ||
//STRIP001       Abs(rRef1.X()-rRef2.X())==Abs(rRef1.Y()-rRef2.Y()))) {
//STRIP001      bRota90Merk=aGeo.nDrehWink % 9000 ==0;
//STRIP001  }
//STRIP001  Polygon aPol(Rect2Poly(aRect,aGeo));
//STRIP001  USHORT i;
//STRIP001  USHORT nPntAnz=aPol.GetSize();
//STRIP001  for (i=0; i<nPntAnz; i++) {
//STRIP001       MirrorPoint(aPol[i],rRef1,rRef2);
//STRIP001  }
//STRIP001  // Polygon wenden und etwas schieben
//STRIP001  Polygon aPol0(aPol);
//STRIP001  aPol[0]=aPol0[1];
//STRIP001  aPol[1]=aPol0[0];
//STRIP001  aPol[2]=aPol0[3];
//STRIP001  aPol[3]=aPol0[2];
//STRIP001  aPol[4]=aPol0[1];
//STRIP001  Poly2Rect(aPol,aRect,aGeo);
//STRIP001
//STRIP001  if (bRota90Merk) {
//STRIP001      FASTBOOL bRota90=aGeo.nDrehWink % 9000 ==0;
//STRIP001      if (bRota90Merk && !bRota90) { // Scheinbar Rundungsfehler: Korregieren
//STRIP001          long a=NormAngle360(aGeo.nDrehWink);
//STRIP001          if (a<4500) a=0;
//STRIP001          else if (a<13500) a=9000;
//STRIP001          else if (a<22500) a=18000;
//STRIP001          else if (a<31500) a=27000;
//STRIP001          else a=0;
//STRIP001          aGeo.nDrehWink=a;
//STRIP001          aGeo.RecalcSinCos();
//STRIP001      }
//STRIP001  }
//STRIP001  if (bNoShearMerk!=(aGeo.nShearWink==0)) { // Shear ggf. korregieren wg. Rundungsfehler
//STRIP001      aGeo.nShearWink=0;
//STRIP001      aGeo.RecalcTan();
//STRIP001  }
//STRIP001
//STRIP001  ImpJustifyRect(aRect);
//STRIP001  if (bTextFrame) {
//STRIP001      NbcAdjustTextFrameWidthAndHeight();
//STRIP001  }
//STRIP001  ImpCheckShear();
//STRIP001  SetRectsDirty();
//STRIP001  NbcMirrorGluePoints(rRef1,rRef2);
//STRIP001  SetGlueReallyAbsolute(FALSE);
//STRIP001 }

//STRIP001 SdrObject* SdrTextObj::ImpConvertObj(FASTBOOL bToPoly) const
//STRIP001 {
//STRIP001  if (!ImpCanConvTextToCurve()) return NULL;
//STRIP001  SdrObjGroup* pGroup=new SdrObjGroup();
//STRIP001  SdrOutliner& rOutl=ImpGetDrawOutliner();
//STRIP001  rOutl.SetUpdateMode(TRUE);
//STRIP001  ImpTextPortionHandler aConverter(rOutl,*this);
//STRIP001
//STRIP001  aConverter.ConvertToPathObj(*pGroup,bToPoly);
//STRIP001
//STRIP001  // Nachsehen, ob ueberhaupt was drin ist:
//STRIP001  SdrObjList* pOL=pGroup->GetSubList();
//STRIP001
//STRIP001  if (pOL->GetObjCount()==0) {
//STRIP001      delete pGroup;
//STRIP001      return NULL;
//STRIP001  }
//STRIP001  // Ein einzelnes Objekt muss nicht gruppiert werden:
//STRIP001  if (pOL->GetObjCount()==1) {
//STRIP001      SdrObject* pObj=pOL->RemoveObject(0);
//STRIP001      delete pGroup;
//STRIP001      return pObj;
//STRIP001  }
//STRIP001  // Ansonsten die Gruppe zurueckgeben
//STRIP001  return pGroup;
//STRIP001 }

//STRIP001 SdrObject* SdrTextObj::DoConvertToPolyObj(BOOL bBezier) const
//STRIP001 {
//STRIP001  return ImpConvertObj(!bBezier);
//STRIP001 }

/*N*/ void SdrTextObj::ImpConvertSetAttrAndLayer(SdrObject* pObj, FASTBOOL bNoSetAttr) const
/*N*/ {
/*N*/   if (pObj!=NULL) {
/*N*/       pObj->ImpSetAnchorPos(aAnchor);
/*N*/       pObj->NbcSetLayer(SdrLayerID(nLayerId));
/*N*/       if (pModel!=NULL) {
/*N*/           pObj->SetModel(pModel);
/*N*/           if (!bNoSetAttr) {
/*N*/               SdrBroadcastItemChange aItemChange(*pObj);
/*N*/               pObj->ClearItem();
/*N*/               pObj->SetItemSet(GetItemSet());
/*N*/               pObj->BroadcastItemChange(aItemChange);
/*N*/
/*N*/               pObj->NbcSetStyleSheet(GetStyleSheet(),TRUE);
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ SdrObject* SdrTextObj::ImpConvertMakeObj(const XPolyPolygon& rXPP, FASTBOOL bClosed, FASTBOOL bBezier, FASTBOOL bNoSetAttr) const
/*N*/ {
/*N*/   SdrObjKind ePathKind=bClosed?OBJ_PATHFILL:OBJ_PATHLINE;
/*N*/   XPolyPolygon aXPP(rXPP);
/*N*/   if (bClosed) {
/*N*/       // Alle XPolygone des XPolyPolygons schliessen, sonst kommt das PathObj durcheinander!
/*N*/       for (USHORT i=0; i<aXPP.Count(); i++) {
/*N*/           const XPolygon& rXP=aXPP[i];
/*N*/           USHORT nAnz=rXP.GetPointCount();
/*N*/           if (nAnz>0) {
/*N*/               USHORT nMax=USHORT(nAnz-1);
/*N*/               Point aPnt(rXP[0]);
/*N*/               if (aPnt!=rXP[nMax]) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/                    aXPP[i].SetPointCount(nAnz+1);
//STRIP001 /*?*/                    aXPP[i][nAnz]=aPnt;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   if (!bBezier && pModel!=NULL) {
/*N*/       // Polygon aus Bezierkurve interpolieren
/*N*/       VirtualDevice   aVDev;
/*N*/       XPolyPolygon    aXPolyPoly;
/*N*/
/*N*/       MapMode aMap = aVDev.GetMapMode();
/*N*/       aMap.SetMapUnit(pModel->GetScaleUnit());
/*N*/       aMap.SetScaleX(pModel->GetScaleFraction());
/*N*/       aMap.SetScaleY(pModel->GetScaleFraction());
/*N*/       aVDev.SetMapMode(aMap);
/*N*/
/*N*/       for (USHORT i=0; i<aXPP.Count(); i++)
/*N*/           aXPolyPoly.Insert(XOutCreatePolygon(aXPP[i],&aVDev));
/*N*/       aXPP=aXPolyPoly;
/*N*/       ePathKind=bClosed?OBJ_POLY:OBJ_PLIN;
/*N*/   }
/*N*/   SdrPathObj* pPathObj=new SdrPathObj(ePathKind,aXPP);
/*N*/   if (bBezier) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        pPathObj->ConvertAllSegments(SDRPATH_CURVE);
/*N*/   }
/*N*/   ImpConvertSetAttrAndLayer(pPathObj,bNoSetAttr);
/*N*/   return pPathObj;
/*N*/ }

/*N*/ SdrObject* SdrTextObj::ImpConvertAddText(SdrObject* pObj, FASTBOOL bBezier) const
/*N*/ {
/*N*/   if (!ImpCanConvTextToCurve()) return pObj;
/*?*/   DBG_ASSERT(0, "STRIP"); return pObj;//STRIP001 SdrObject* pText=ImpConvertObj(!bBezier);
//STRIP001 /*?*/    if (pText==NULL) return pObj;
//STRIP001 /*?*/    if (pObj==NULL) return pText;
//STRIP001 /*?*/    if (pText->IsGroupObject()) {
//STRIP001 /*?*/        SdrObjList* pOL=pText->GetSubList();
//STRIP001 /*?*/        pOL->InsertObject(pObj,0);
//STRIP001 /*?*/        return pText;
//STRIP001 /*?*/    } else {
//STRIP001 /*?*/        SdrObjGroup* pGrp=new SdrObjGroup;
//STRIP001 /*?*/        SdrObjList* pOL=pGrp->GetSubList();
//STRIP001 /*?*/        pOL->InsertObject(pObj);
//STRIP001 /*?*/        pOL->InsertObject(pText);
//STRIP001 /*?*/        return pGrp;
//STRIP001 /*N*/    }
/*N*/ }

}
