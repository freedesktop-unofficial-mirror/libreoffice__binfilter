/*************************************************************************
 *
 *  $RCSfile: svx_svdvmark.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:42 $
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

#include "svdvmark.hxx"
#include "xpoly.hxx"
#include "svdxout.hxx"
#include "svdobj.hxx"
#include "svdpagv.hxx"
#include "svdpntv.hxx"

#ifndef _TL_POLY_HXX
#include <tools/poly.hxx>
#endif
//#ifndef NOOLDSV //autogen
//#include <vcl/system.hxx>
//#endif
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrViewUserMarker::SdrViewUserMarker(SdrPaintView* pView_)
/*N*/ : pView(pView_),
/*N*/   pForcedOutDev(NULL),
/*N*/   pPoint(NULL),
/*N*/   pRect(NULL),
/*N*/   pPoly(NULL),
/*N*/   pPolyPoly(NULL),
/*N*/   pXPoly(NULL),
/*N*/   pXPolyPoly(NULL),
/*N*/   eAlign(SDRMARKER_ALIGNCENTER),
/*N*/   nPixelDistance(0),
/*N*/   nLineWdt(0),
/*N*/   nCrossSize(0),
/*N*/   bLineWdtLog(FALSE),
/*N*/   bCrossSizeLog(FALSE),
/*N*/   bSolidArea(FALSE),
/*N*/   bDashed(FALSE),
/*N*/   bCrossHair(FALSE),
/*N*/   bStripes(FALSE),
/*N*/   bEllipse(FALSE),
/*N*/   bPolyLine(FALSE),
/*N*/   bAnimate(FALSE),
/*N*/   bVisible(FALSE),
/*N*/   nAnimateDelay(0),
/*N*/   nAnimateSpeed(0),
/*N*/   nAnimateAnz(0),
/*N*/   bAnimateBwd(FALSE),
/*N*/   bAnimateToggle(FALSE),
/*N*/   nAnimateDelayCountDown(0),
/*N*/   nAnimateSpeedCountDown(0),
/*N*/   nAnimateNum(0),
/*N*/   bHasPointer(FALSE),
/*N*/   bMouseMovable(FALSE)
/*N*/ {
/*N*/   if (pView!=NULL) pView->ImpInsertUserMarker(this);
/*N*/   bAnimateToggle=TRUE;
/*N*/ }
/*N*/
/*N*/ SdrViewUserMarker::~SdrViewUserMarker()
/*N*/ {
/*N*/   if (bVisible) {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 Hide();
/*N*/   if (pView!=NULL) pView->ImpRemoveUserMarker(this);
/*N*/   ImpDelGeometrics();
/*N*/ }
/*N*/
/*N*/ void SdrViewUserMarker::ImpDelGeometrics()
/*N*/ {
/*N*/   if (pPoint    !=NULL) { delete pPoint    ; pPoint    =NULL; }
/*N*/   if (pRect     !=NULL) { delete pRect     ; pRect     =NULL; }
/*N*/   if (pPoly     !=NULL) { delete pPoly     ; pPoly     =NULL; }
/*N*/   if (pPolyPoly !=NULL) { delete pPolyPoly ; pPolyPoly =NULL; }
/*N*/   if (pXPoly    !=NULL) { delete pXPoly    ; pXPoly    =NULL; }
/*N*/   if (pXPolyPoly!=NULL) { delete pXPolyPoly; pXPolyPoly=NULL; }
/*N*/ }

//STRIP001 void SdrViewUserMarker::SetView(SdrPaintView* pView_)
//STRIP001 {
//STRIP001  if (pView_==pView) return;
//STRIP001  FASTBOOL bVis=bVisible;
//STRIP001  if (bVis) Hide();
//STRIP001  pView=pView_;
//STRIP001  if (bVis) Show();
//STRIP001 }

/*N*/ void SdrViewUserMarker::SetPoint(const Point& rPoint)
/*N*/ {
/*N*/   if (pPoint!=NULL && rPoint==*pPoint) return;
/*N*/   FASTBOOL bVis=bVisible;
/*N*/   if (bVis) Hide();
/*N*/   if (pPoint==NULL) {
/*N*/       ImpDelGeometrics();
/*N*/       pPoint=new Point(rPoint);
/*N*/   } else {
/*N*/       *pPoint=rPoint;
/*N*/   }
/*N*/   if (bVis) Show();
/*N*/ }

//STRIP001 void SdrViewUserMarker::SetRectangle(const Rectangle& rRect)
//STRIP001 {
//STRIP001  if (pRect!=NULL && rRect==*pRect) return;
//STRIP001  FASTBOOL bVis=bVisible;
//STRIP001  if (bVis) Hide();
//STRIP001  if (pRect==NULL) {
//STRIP001      ImpDelGeometrics();
//STRIP001      pRect=new Rectangle(rRect);
//STRIP001  } else {
//STRIP001      *pRect=rRect;
//STRIP001  }
//STRIP001  if (bVis) Show();
//STRIP001 }
//STRIP001
//STRIP001 void SdrViewUserMarker::SetRectangle(const SdrObject* pObj, const SdrPageView* pPV)
//STRIP001 {
//STRIP001  if (pObj!=NULL) {
//STRIP001      Rectangle aR(pObj->GetBoundRect());
//STRIP001      if (pPV!=NULL) {
//STRIP001          aR.Move(pPV->GetOffset().X(),pPV->GetOffset().Y());
//STRIP001      }
//STRIP001      SetRectangle(aR);
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001 void SdrViewUserMarker::SetPolygon(const Polygon& rPoly)
//STRIP001 {
//STRIP001  if (pPoly!=NULL && rPoly==*pPoly) return;
//STRIP001  FASTBOOL bVis=bVisible;
//STRIP001  if (bVis) Hide();
//STRIP001  if (pPoly==NULL) {
//STRIP001      ImpDelGeometrics();
//STRIP001      pPoly=new Polygon(rPoly);
//STRIP001  } else {
//STRIP001      *pPoly=rPoly;
//STRIP001  }
//STRIP001  if (bVis) Show();
//STRIP001 }
//STRIP001
//STRIP001 void SdrViewUserMarker::SetPolyPolygon(const PolyPolygon& rPolyPoly)
//STRIP001 {
//STRIP001  if (pPolyPoly!=NULL && rPolyPoly==*pPolyPoly) return;
//STRIP001  FASTBOOL bVis=bVisible;
//STRIP001  if (bVis) Hide();
//STRIP001  if (pPolyPoly==NULL) {
//STRIP001      ImpDelGeometrics();
//STRIP001      pPolyPoly=new PolyPolygon(rPolyPoly);
//STRIP001  } else {
//STRIP001      *pPolyPoly=rPolyPoly;
//STRIP001  }
//STRIP001  if (bVis) Show();
//STRIP001 }
//STRIP001
//STRIP001 void SdrViewUserMarker::SetXPolygon(const XPolygon& rXPoly)
//STRIP001 {
//STRIP001  if (pXPoly!=NULL && rXPoly==*pXPoly) return;
//STRIP001  FASTBOOL bVis=bVisible;
//STRIP001  if (bVis) Hide();
//STRIP001  if (pXPoly==NULL) {
//STRIP001      ImpDelGeometrics();
//STRIP001      pXPoly=new XPolygon(rXPoly);
//STRIP001  } else {
//STRIP001      *pXPoly=rXPoly;
//STRIP001  }
//STRIP001  if (bVis) Show();
//STRIP001 }
//STRIP001
//STRIP001 void SdrViewUserMarker::SetXPolyPolygon(const XPolyPolygon& rXPolyPoly)
//STRIP001 {
//STRIP001  if (pXPolyPoly!=NULL && rXPolyPoly==*pXPolyPoly) return;
//STRIP001  FASTBOOL bVis=bVisible;
//STRIP001  if (bVis) Hide();
//STRIP001  if (pXPolyPoly==NULL) {
//STRIP001      ImpDelGeometrics();
//STRIP001      pXPolyPoly=new XPolyPolygon(rXPolyPoly);
//STRIP001  } else {
//STRIP001      *pXPolyPoly=rXPolyPoly;
//STRIP001  }
//STRIP001  if (bVis) Show();
//STRIP001 }
//STRIP001
//STRIP001 void SdrViewUserMarker::SetXPolyPolygon(const SdrObject* pObj, const SdrPageView* pPV)
//STRIP001 {
//STRIP001  if (pObj!=NULL) {
//STRIP001      XPolyPolygon aXPP;
//STRIP001      pObj->TakeXorPoly(aXPP,TRUE);
//STRIP001      if (pPV!=NULL) {
//STRIP001          aXPP.Move(pPV->GetOffset().X(),pPV->GetOffset().Y());
//STRIP001      }
//STRIP001      FASTBOOL bChg=!bSolidArea && !bPolyLine;
//STRIP001      FASTBOOL bVis=bVisible;
//STRIP001      if (bVis && bChg) Hide();
//STRIP001      SetXPolyPolygon(aXPP);
//STRIP001      if (bChg) bPolyLine=TRUE;
//STRIP001      if (bVis && bChg) Show();
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001 void SdrViewUserMarker::SetCrossHair(FASTBOOL bOn)
//STRIP001 {
//STRIP001  FASTBOOL bVis=bVisible;
//STRIP001  if (bVis) Hide();
//STRIP001  bCrossHair=bOn;
//STRIP001  if (bVis) Show();
//STRIP001 }
//STRIP001
//STRIP001 void SdrViewUserMarker::SetStripes(FASTBOOL bOn)
//STRIP001 {
//STRIP001  FASTBOOL bVis=bVisible;
//STRIP001  if (bVis) Hide();
//STRIP001  bStripes=bOn;
//STRIP001  if (bOn) { bSolidArea=FALSE; bEllipse=FALSE; }
//STRIP001  if (bVis) Show();
//STRIP001 }
//STRIP001
//STRIP001 void SdrViewUserMarker::SetEllipse(FASTBOOL bOn)
//STRIP001 {
//STRIP001  FASTBOOL bVis=bVisible;
//STRIP001  if (bVis) Hide();
//STRIP001  bEllipse=bOn;
//STRIP001  if (bVis) Show();
//STRIP001 }
//STRIP001
//STRIP001 void SdrViewUserMarker::SetPolyLine(FASTBOOL bOn)
//STRIP001 {
//STRIP001  FASTBOOL bVis=bVisible;
//STRIP001  if (bVis) Hide();
//STRIP001  bPolyLine=bOn;
//STRIP001  if (bOn) { bSolidArea=FALSE; }
//STRIP001  if (bVis) Show();
//STRIP001 }
//STRIP001
//STRIP001 void SdrViewUserMarker::SetSolidArea(FASTBOOL bOn)
//STRIP001 {
//STRIP001  FASTBOOL bVis=bVisible;
//STRIP001  if (bVis) Hide();
//STRIP001  bSolidArea=bOn;
//STRIP001  if (bOn) { bStripes=FALSE; bPolyLine=FALSE; }
//STRIP001  if (bVis) Show();
//STRIP001 }
//STRIP001
//STRIP001 void SdrViewUserMarker::SetDashed(FASTBOOL bOn)
//STRIP001 {
//STRIP001  FASTBOOL bVis=bVisible;
//STRIP001  if (bVis) Hide();
//STRIP001  bDashed=bOn;
//STRIP001  if (bVis) Show();
//STRIP001 }
//STRIP001
//STRIP001 void SdrViewUserMarker::SetAnimate(FASTBOOL bOn)
//STRIP001 {
//STRIP001  FASTBOOL bFlag=IsAnimate();
//STRIP001  FASTBOOL bVis=bVisible;
//STRIP001  if (bVis) Hide();
//STRIP001  bAnimate=bOn;
//STRIP001  if (bVis) Show();
//STRIP001  if (bFlag!=IsAnimate() && pView!=NULL) pView->ImpCheckMarkerAnimator();
//STRIP001 }
//STRIP001
//STRIP001 void SdrViewUserMarker::SetPixelDistance(USHORT nDistance)
//STRIP001 {
//STRIP001  FASTBOOL bVis=bVisible;
//STRIP001  if (bVis) Hide();
//STRIP001  nPixelDistance=nDistance;
//STRIP001  if (bVis) Show();
//STRIP001 }
//STRIP001
/*N*/ void SdrViewUserMarker::SetLineWidth(USHORT nWdt)
/*N*/ {
/*N*/   FASTBOOL bVis=bVisible;
/*N*/   if (bVis) Hide();
/*N*/   nLineWdt=nWdt;
/*N*/   if (bVis) Show();
/*N*/ }
//STRIP001
//STRIP001 void SdrViewUserMarker::SetLineWidthIsLogic(FASTBOOL bOn)
//STRIP001 {
//STRIP001  FASTBOOL bVis=bVisible;
//STRIP001  if (bVis) Hide();
//STRIP001  bLineWdtLog=bOn;
//STRIP001  if (bVis) Show();
//STRIP001 }
//STRIP001
//STRIP001 void SdrViewUserMarker::SetCrossHairSize(USHORT nSize)
//STRIP001 {
//STRIP001  FASTBOOL bVis=bVisible;
//STRIP001  if (bVis) Hide();
//STRIP001  nCrossSize=nSize;
//STRIP001  if (bVis) Show();
//STRIP001 }
//STRIP001
//STRIP001 void SdrViewUserMarker::SetCrossSizeIsLogic(FASTBOOL bOn)
//STRIP001 {
//STRIP001  FASTBOOL bVis=bVisible;
//STRIP001  if (bVis) Hide();
//STRIP001  bCrossSizeLog=bOn;
//STRIP001  if (bVis) Show();
//STRIP001 }
//STRIP001
//STRIP001 void SdrViewUserMarker::Move(long nXMove, long nYMove)
//STRIP001 {
//STRIP001  if (nXMove==0 && nYMove==0) return;
//STRIP001  FASTBOOL bVis=bVisible;
//STRIP001  if (bVis) Hide();
//STRIP001  if (pPoint    !=NULL) { pPoint    ->Move(nXMove,nYMove); }
//STRIP001  if (pRect     !=NULL) { pRect     ->Move(nXMove,nYMove); }
//STRIP001  if (pPoly     !=NULL) { pPoly     ->Move(nXMove,nYMove); }
//STRIP001  if (pPolyPoly !=NULL) { pPolyPoly ->Move(nXMove,nYMove); }
//STRIP001  if (pXPoly    !=NULL) { pXPoly    ->Move(nXMove,nYMove); }
//STRIP001  if (pXPolyPoly!=NULL) { pXPolyPoly->Move(nXMove,nYMove); }
//STRIP001  if (bVis) Show();
//STRIP001 }

/*N*/ void SdrViewUserMarker::Show()
/*N*/ {DBG_BF_ASSERT(0, "STRIP");
//STRIP001  if (!bVisible) {
//STRIP001      nAnimateDelayCountDown=nAnimateDelay;
//STRIP001      if (nAnimateDelay!=0) {
//STRIP001          if (bAnimateToggle) bAnimateBwd=FALSE;
//STRIP001          nAnimateNum=0;
//STRIP001      }
//STRIP001      nAnimateSpeedCountDown=nAnimateSpeed;
//STRIP001      ImpDraw(FALSE,FALSE);
//STRIP001      bVisible=TRUE;
//STRIP001  }
/*N*/ }

/*N*/ void SdrViewUserMarker::Hide()
/*N*/ {DBG_BF_ASSERT(0, "STRIP");
//STRIP001  if (bVisible) {
//STRIP001      ImpDraw(TRUE,FALSE);
//STRIP001      bVisible=FALSE;
//STRIP001  }
/*N*/ }

//STRIP001 void SdrViewUserMarker::ImpDraw(FASTBOOL bHiding, FASTBOOL bNoSaveDC)
//STRIP001 {
//STRIP001  if (pView==NULL) return;
//STRIP001  if (pForcedOutDev!=NULL) {
//STRIP001      Draw(pForcedOutDev,bHiding,bNoSaveDC);
//STRIP001  } else {
//STRIP001      USHORT nAnz=pView->GetWinCount();
//STRIP001      for (USHORT nNum=0; nNum<nAnz; nNum++) {
//STRIP001          SdrViewWinRec& rWinRec = pView->GetWinRec(nNum);
//STRIP001          OutputDevice* pO=pView->GetWin(nNum);
//STRIP001          if (pO->GetOutDevType()==OUTDEV_WINDOW) {
//STRIP001              Draw(pO,bHiding,bNoSaveDC);
//STRIP001              if(!bHiding)
//STRIP001                  rWinRec.bXorVisible = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001 void SdrViewUserMarker::Draw(OutputDevice* pOut1, FASTBOOL bHiding, FASTBOOL bNoSaveDC)
//STRIP001 {
//STRIP001  if (pOut1==NULL)
//STRIP001      return;
//STRIP001
//STRIP001  RasterOp eRop0=pOut1->GetRasterOp();
//STRIP001  FASTBOOL bMap0=pOut1->IsMapModeEnabled();
//STRIP001  pOut1->SetRasterOp(ROP_INVERT);
//STRIP001
//STRIP001  FASTBOOL bFill=IsSolidArea();
//STRIP001
//STRIP001  Color aLineColorMerk( pOut1->GetLineColor() );
//STRIP001  Color aFillColorMerk( pOut1->GetFillColor() );
//STRIP001
//STRIP001  Color aLineColor( bFill ? COL_TRANSPARENT : COL_BLACK );
//STRIP001  Color aFillColor( bFill ? COL_BLACK : COL_TRANSPARENT );
//STRIP001
//STRIP001  USHORT nLWdt=nLineWdt;
//STRIP001
//STRIP001  if (nLWdt==0)
//STRIP001      nLWdt=1;
//STRIP001  if (bAnimate && !bDashed)
//STRIP001      nLWdt+=nAnimateNum;
//STRIP001
//STRIP001  // Point und Rect werden in Pixel ausgegeben
//STRIP001  Point aPoint;
//STRIP001  Rectangle aRect;
//STRIP001  if (pPoint!=NULL)
//STRIP001      aPoint=pOut1->LogicToPixel(*pPoint);
//STRIP001  if (pRect!=NULL)
//STRIP001      aRect =pOut1->LogicToPixel(*pRect);
//STRIP001
//STRIP001  long nLWdt1=0,nLWdt2=0;
//STRIP001  if (pPoint!=NULL || pRect!=NULL)
//STRIP001  {
//STRIP001      nLWdt1=nLWdt;
//STRIP001      if (bLineWdtLog) nLWdt1=pOut1->PixelToLogic(Size(nLWdt1,0)).Width();
//STRIP001      nLWdt2=nLWdt1;
//STRIP001      if (nLWdt1>0) {
//STRIP001          nLWdt1=(nLWdt1-1)/2;
//STRIP001          nLWdt2/=2;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  Size aCrSiz(nCrossSize,nCrossSize);
//STRIP001  long nOutMaxX=0,nOutMaxY=0;
//STRIP001
//STRIP001  if ((pPoint!=NULL && bCrossHair) || (pRect!=NULL && bStripes))
//STRIP001  {
//STRIP001      if (nCrossSize!=0)
//STRIP001      {
//STRIP001          if (bCrossSizeLog)
//STRIP001              aCrSiz=pOut1->LogicToPixel(aCrSiz);
//STRIP001      }
//STRIP001      else
//STRIP001      { // Stripes/CrossHair ueber den vollen Bildschirm
//STRIP001          Size aSiz(pOut1->GetOutputSizePixel());
//STRIP001          nOutMaxX=aSiz.Width();
//STRIP001          nOutMaxY=aSiz.Height();
//STRIP001      }
//STRIP001      aCrSiz.Width()/=2;
//STRIP001      aCrSiz.Height()/=2;
//STRIP001      if (aCrSiz.Width()<=0)
//STRIP001          aCrSiz.Width()=1;
//STRIP001      if (aCrSiz.Height()<=0)
//STRIP001          aCrSiz.Height()=1;
//STRIP001  }
//STRIP001  if (pPoint!=NULL)
//STRIP001  {
//STRIP001      pOut1->EnableMapMode(FALSE);
//STRIP001      pOut1->SetLineColor( aLineColor );
//STRIP001      if (bCrossHair)
//STRIP001      {
//STRIP001          long xl=nCrossSize==0 ? 0        : aPoint.X()-aCrSiz.Width();
//STRIP001          long xr=nCrossSize==0 ? nOutMaxX : aPoint.X()+aCrSiz.Width();
//STRIP001          long yo=nCrossSize==0 ? 0        : aPoint.Y()-aCrSiz.Height();
//STRIP001          long yu=nCrossSize==0 ? nOutMaxY : aPoint.Y()+aCrSiz.Height();
//STRIP001          pOut1->DrawLine(Point(aPoint.X(),yo),Point(aPoint.X(),yu));
//STRIP001          pOut1->DrawLine(Point(xl,aPoint.Y()),Point(xr,aPoint.Y()));
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          Rectangle aRect(aPoint,aPoint);
//STRIP001          long nDist1=nLWdt1+nPixelDistance; // Strichstaerke und
//STRIP001          long nDist2=nLWdt2+nPixelDistance; // Pixelabstand noch dazu
//STRIP001          aRect.Left()-=nDist1;
//STRIP001          aRect.Top()-=nDist1;
//STRIP001          aRect.Right()+=nDist2;
//STRIP001          aRect.Bottom()+=nDist2;
//STRIP001
//STRIP001          pOut1->SetFillColor( aFillColor );
//STRIP001
//STRIP001          if (bEllipse)
//STRIP001              pOut1->DrawEllipse(aRect);
//STRIP001          else
//STRIP001              pOut1->DrawRect(aRect);
//STRIP001      }
//STRIP001  }
//STRIP001  if (pRect!=NULL)
//STRIP001  {
//STRIP001      pOut1->EnableMapMode(FALSE);
//STRIP001      pOut1->SetLineColor( aLineColor );
//STRIP001      long nDist1=nLWdt1+nPixelDistance; // Strichstaerke und
//STRIP001      long nDist2=nLWdt2+nPixelDistance; // Pixelabstand noch dazu
//STRIP001      aRect.Left()-=nDist1;
//STRIP001      aRect.Top()-=nDist1;
//STRIP001      aRect.Right()+=nDist2;
//STRIP001      aRect.Bottom()+=nDist2;
//STRIP001
//STRIP001      if (bStripes)
//STRIP001      {
//STRIP001          long xl=aCrSiz.Width ()==0 ? 0        : aRect.Left  ()-aCrSiz.Width();
//STRIP001          long xr=aCrSiz.Width ()==0 ? nOutMaxX : aRect.Right ()+aCrSiz.Width();
//STRIP001          long yo=aCrSiz.Height()==0 ? 0        : aRect.Top   ()-aCrSiz.Height();
//STRIP001          long yu=aCrSiz.Height()==0 ? nOutMaxY : aRect.Bottom()+aCrSiz.Height();
//STRIP001
//STRIP001          pOut1->DrawLine(Point(xl,aRect.Top   ()),aRect.TopLeft   ());
//STRIP001          pOut1->DrawLine(Point(xl,aRect.Bottom()),aRect.BottomLeft());
//STRIP001          pOut1->DrawLine(aRect.TopRight   (),Point(xr,aRect.Top())   );
//STRIP001          pOut1->DrawLine(aRect.BottomRight(),Point(xr,aRect.Bottom()));
//STRIP001          pOut1->DrawLine(Point(aRect.Left (),yo),aRect.TopLeft ());
//STRIP001          pOut1->DrawLine(Point(aRect.Right(),yo),aRect.TopRight());
//STRIP001          pOut1->DrawLine(aRect.TopLeft (),Point(aRect.Left (),yu));
//STRIP001          pOut1->DrawLine(aRect.TopRight(),Point(aRect.Right(),yu));
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pOut1->SetFillColor( aFillColor );
//STRIP001
//STRIP001          if (bEllipse)
//STRIP001              pOut1->DrawEllipse(aRect);
//STRIP001          else
//STRIP001          {
//STRIP001              if (pOut1->GetOutDevType() == OUTDEV_WINDOW)
//STRIP001              {
//STRIP001                  ((Window*) pOut1)->InvertTracking(aRect, SHOWTRACK_OBJECT | SHOWTRACK_WINDOW);
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  pOut1->DrawRect(aRect);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if (pPoly!=NULL)
//STRIP001  {
//STRIP001      pOut1->SetLineColor( aLineColor );
//STRIP001
//STRIP001      if (bPolyLine)
//STRIP001          pOut1->DrawPolyLine(*pPoly);
//STRIP001      else
//STRIP001      {
//STRIP001          pOut1->SetFillColor( aFillColor );
//STRIP001
//STRIP001          if (pOut1->GetOutDevType() == OUTDEV_WINDOW)
//STRIP001          {
//STRIP001              ((Window*) pOut1)->InvertTracking(*pPoly, SHOWTRACK_WINDOW);
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              pOut1->DrawPolygon(*pPoly);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if (pPolyPoly!=NULL)
//STRIP001  {
//STRIP001      pOut1->SetLineColor( aLineColor);
//STRIP001
//STRIP001      if (bPolyLine)
//STRIP001      {
//STRIP001          USHORT nAnz=pPolyPoly->Count();
//STRIP001          for (USHORT nNum=0; nNum<nAnz; nNum++)
//STRIP001              pOut1->DrawPolyLine((*pPolyPoly)[nNum]);
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pOut1->SetFillColor( aFillColor );
//STRIP001          pOut1->DrawPolyPolygon(*pPolyPoly);
//STRIP001      }
//STRIP001  }
//STRIP001  if ((pXPoly!=NULL || pXPolyPoly!=NULL) && pView!=NULL)
//STRIP001  {
//STRIP001      ExtOutputDevice* pXOut=pView->pXOut;
//STRIP001      pXOut->SetOutDev(pOut1);
//STRIP001
//STRIP001      pXOut->OverrideLineColor( aLineColor);
//STRIP001
//STRIP001      if (pXPoly!=NULL)
//STRIP001      {
//STRIP001          if (bPolyLine)
//STRIP001              pXOut->DrawXPolyLine(*pXPoly);
//STRIP001          else
//STRIP001          {
//STRIP001              pXOut->OverrideFillColor( aFillColor );
//STRIP001
//STRIP001              if (pOut1->GetOutDevType() == OUTDEV_WINDOW)
//STRIP001              {
//STRIP001                  const Polygon aPolygon( XOutCreatePolygon(*pXPoly, pOut1) );
//STRIP001                  ((Window*) pOut1)->InvertTracking(aPolygon, SHOWTRACK_WINDOW);
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  pXOut->DrawXPolygon(*pXPoly);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      if (pXPolyPoly!=NULL)
//STRIP001      {
//STRIP001          if (bPolyLine)
//STRIP001          {
//STRIP001              USHORT nAnz=pXPolyPoly->Count();
//STRIP001              for (USHORT nNum=0; nNum<nAnz; nNum++)
//STRIP001              {
//STRIP001                  if (pOut1->GetOutDevType() == OUTDEV_WINDOW)
//STRIP001                  {
//STRIP001                      const Polygon aPolygon( XOutCreatePolygon((*pXPolyPoly)[nNum], pOut1) );
//STRIP001                      ((Window*) pOut1)->InvertTracking(aPolygon, SHOWTRACK_WINDOW);
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      pXOut->DrawXPolyLine((*pXPolyPoly)[nNum]);
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              pXOut->OverrideFillColor( aFillColor );
//STRIP001              pXOut->DrawXPolyPolygon(*pXPolyPoly);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if (!bNoSaveDC)
//STRIP001  {
//STRIP001      pOut1->SetLineColor( aLineColorMerk );
//STRIP001
//STRIP001      if ( aFillColorMerk != pOut1->GetFillColor() )
//STRIP001          pOut1->SetFillColor( aFillColorMerk );
//STRIP001  }
//STRIP001  pOut1->SetRasterOp(eRop0);
//STRIP001  pOut1->EnableMapMode(bMap0);
//STRIP001 }
//STRIP001
//STRIP001 FASTBOOL SdrViewUserMarker::IncAnimateCounters()
//STRIP001 {
//STRIP001  if (nAnimateDelayCountDown>0) {
//STRIP001      nAnimateDelayCountDown--;
//STRIP001  } else {
//STRIP001      if (nAnimateSpeedCountDown>0) {
//STRIP001          nAnimateSpeedCountDown--;
//STRIP001      } else {
//STRIP001          nAnimateSpeedCountDown=nAnimateSpeed; // SpeedCounter zurueksetzen
//STRIP001          if (nAnimateNum==0 && bAnimateBwd) {
//STRIP001              if (bAnimateToggle) {
//STRIP001                  bAnimateBwd=FALSE;
//STRIP001                  nAnimateNum++;
//STRIP001              } else {
//STRIP001                  nAnimateNum=nAnimateAnz-1;
//STRIP001              }
//STRIP001          } else if (nAnimateNum>=nAnimateAnz-1 && !bAnimateBwd) {
//STRIP001              if (bAnimateToggle) {
//STRIP001                  bAnimateBwd=TRUE;
//STRIP001                  nAnimateNum--;
//STRIP001              } else {
//STRIP001                  nAnimateNum=0;
//STRIP001              }
//STRIP001          } else if (bAnimateBwd) {
//STRIP001              nAnimateNum--;
//STRIP001          } else {
//STRIP001              nAnimateNum++;
//STRIP001          }
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }
//STRIP001
//STRIP001 void SdrViewUserMarker::DoAnimateOneStep()
//STRIP001 {
//STRIP001  USHORT nMerk1=nAnimateNum;
//STRIP001  if (bVisible && IncAnimateCounters()) {
//STRIP001      USHORT nMerk2=nAnimateNum;
//STRIP001      nAnimateNum=nMerk1;
//STRIP001      ImpDraw(TRUE,FALSE);
//STRIP001      nAnimateNum=nMerk2;
//STRIP001      ImpDraw(FALSE,FALSE);
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001 FASTBOOL SdrViewUserMarker::IsHit(const Point& rPnt, short nTol) const
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }
//STRIP001
//STRIP001 Pointer SdrViewUserMarker::GetPointer() const
//STRIP001 {
//STRIP001  return Pointer(POINTER_ARROW);
//STRIP001 }

}
