/*************************************************************************
 *
 *  $RCSfile: svx_svdpntv.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 16:31:06 $
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

#ifndef _COM_SUN_STAR_AWT_XWINDOW_HPP_
#include <com/sun/star/awt/XWindow.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_POSSIZE_HPP_
#include <com/sun/star/awt/PosSize.hpp>
#endif
// auto strip #ifndef _COM_SUN_STAR_AWT_XCONTROL_HPP_
// auto strip #include <com/sun/star/awt/XControl.hpp>
// auto strip #endif

// auto strip #include "svdpntv.hxx"
// auto strip #include "editdata.hxx"
// auto strip #include "svdmrkv.hxx"
// auto strip #include "svdxout.hxx"
#include "svdpagv.hxx"
#include "svdpage.hxx"
// auto strip #include "svdmodel.hxx"
#include "svdvmark.hxx"
#include "svdio.hxx"
// auto strip #include "svdundo.hxx"
#include "svdview.hxx"
// auto strip #include "svdglue.hxx"
// auto strip #include "svdobj.hxx"
#include "svdograf.hxx"
// auto strip #include "svdattrx.hxx"
// auto strip #include "svdibrow.hxx"
// auto strip #include "svditer.hxx"
#include "svdouno.hxx"

// auto strip #ifndef _SVX_XLNCLIT_HXX
// auto strip #include "xlnclit.hxx"
// auto strip #endif
// auto strip #ifndef _SVX_XFLCLIT_HXX
// auto strip #include "xflclit.hxx"
// auto strip #endif

// auto strip #ifndef _EEITEM_HXX //autogen
// auto strip #include <eeitem.hxx>
// auto strip #endif

#ifndef _SFX_WHITER_HXX //autogen
#include <svtools/whiter.hxx>
#endif

// auto strip #ifndef _SV_MSGBOX_HXX //autogen
// auto strip #include <vcl/msgbox.hxx>
// auto strip #endif

// auto strip #ifndef _SFXITEMITER_HXX //autogen
// auto strip #include <svtools/itemiter.hxx>
// auto strip #endif

#ifndef _SFXSTYLE_HXX //autogen
#include <svtools/style.hxx>
#endif

// auto strip #ifndef _B2D_MBMP_HXX
// auto strip #include <goodies/b2dmbmp.hxx>
// auto strip #endif

// auto strip #ifndef _B2D_MTRI_HXX
// auto strip #include <goodies/b2dmtri.hxx>
// auto strip #endif

// auto strip #ifndef _GRFMGR_HXX
// auto strip #include <goodies/grfmgr.hxx>
// auto strip #endif

#ifndef _XOUTX_HXX
#include "xoutx.hxx"
#endif

namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void RollingRect::DrawHor(OutputDevice& rOut, long x1, long x2, long y, BOOL bMov) const
//STRIP001 {
//STRIP001  USHORT nLen2=nLen*2;
//STRIP001  BOOL bBck=x1>x2;
//STRIP001  long nOfs=nIdx;
//STRIP001  if (bBck) {
//STRIP001      long nTmp;
//STRIP001      nTmp=x1-x2+1+nLen2+nLen;
//STRIP001      nTmp%=nLen2;
//STRIP001      nOfs=nLen2-nOfs+nTmp;
//STRIP001      nTmp=x1; x1=x2; x2=nTmp;
//STRIP001  }
//STRIP001  while (nOfs>0) nOfs-=nLen2;
//STRIP001  long a1,a2,a;
//STRIP001  a=x1+nOfs;
//STRIP001  while (a<=x2+1) {
//STRIP001      a1=a;
//STRIP001      a2=a+(nLen-1);
//STRIP001      if (bMov) {
//STRIP001          if (!bBck) a2++; else a1--;
//STRIP001          if (a1>=x1 && a1<=x2) ((Window&)rOut).Invert(Rectangle(a1,y,a1,y));
//STRIP001          if (a2>=x1 && a2<=x2) ((Window&)rOut).Invert(Rectangle(a2,y,a2,y));
//STRIP001      } else {
//STRIP001          if (a1<x1) a1=x1;
//STRIP001          if (a2>x2) a2=x2;
//STRIP001          if (a1<=a2) ((Window&)rOut).Invert(Rectangle(a1,y,a2,y));
//STRIP001      }
//STRIP001      a+=nLen2;
//STRIP001  }
//STRIP001 }

//STRIP001 void RollingRect::DrawVer(OutputDevice& rOut, long x, long y1, long y2, BOOL bMov) const
//STRIP001 {
//STRIP001  USHORT nLen2=nLen*2;
//STRIP001  BOOL bBck=y1>y2;
//STRIP001  long nOfs=nIdx;
//STRIP001  if (bBck) {
//STRIP001      long nTmp;
//STRIP001      nTmp=y1-y2+1+nLen2+nLen;
//STRIP001      nTmp%=nLen2;
//STRIP001      nOfs=nLen2-nOfs+nTmp;
//STRIP001      nTmp=y1; y1=y2; y2=nTmp;
//STRIP001  }
//STRIP001  while (nOfs>0) nOfs-=nLen2;
//STRIP001  long a1,a2,a;
//STRIP001  a=y1+nOfs;
//STRIP001  while (a<=y2+1) {
//STRIP001      a1=a;
//STRIP001      a2=a+nLen-1;
//STRIP001      if (bMov) {
//STRIP001          if (!bBck) a2++; else a1--;
//STRIP001          if (a1>=y1 && a1<=y2) ((Window&)rOut).Invert(Rectangle(x,a1,x,a1));
//STRIP001          if (a2>=y1 && a2<=y2) ((Window&)rOut).Invert(Rectangle(x,a2,x,a2));
//STRIP001      } else {
//STRIP001          if (a1<y1) a1=y1;
//STRIP001          if (a2>y2) a2=y2;
//STRIP001          if (a1<=a2) ((Window&)rOut).Invert(Rectangle(x,a1,x,a2));
//STRIP001      }
//STRIP001      a+=nLen2;
//STRIP001  }
//STRIP001 }

//STRIP001 void RollingRect::DrawRect(OutputDevice& rOut, BOOL bMov) const
//STRIP001 {
//STRIP001  BOOL bMap0=rOut.IsMapModeEnabled();
//STRIP001  Point aPt1(rOut.LogicToPixel(aP1));
//STRIP001  Point aPt2(rOut.LogicToPixel(aP2));
//STRIP001  rOut.EnableMapMode(FALSE);
//STRIP001  Size aS(rOut.GetOutputSizePixel());
//STRIP001  long dx=Abs(aPt2.X()-aPt1.X());
//STRIP001  long dy=Abs(aPt2.Y()-aPt1.Y());
//STRIP001  if (IsStripes()) {
//STRIP001      DrawHor(rOut,aPt1.X(),0,aPt1.Y(),bMov);
//STRIP001      DrawHor(rOut,aPt2.X(),aS.Width(),aPt1.Y(),bMov);
//STRIP001      if (dy!=0) {
//STRIP001          DrawHor(rOut,aPt1.X(),0,aPt2.Y(),bMov);
//STRIP001          DrawHor(rOut,aPt2.X(),aS.Width(),aPt2.Y(),bMov);
//STRIP001      }
//STRIP001      DrawVer(rOut,aPt1.X(),aPt1.Y(),0,bMov);
//STRIP001      DrawVer(rOut,aPt1.X(),aPt2.Y(),aS.Height(),bMov);
//STRIP001      if (dx!=0) {
//STRIP001          DrawVer(rOut,aPt2.X(),aPt1.Y(),0,bMov);
//STRIP001          DrawVer(rOut,aPt2.X(),aPt2.Y(),aS.Height(),bMov);
//STRIP001      }
//STRIP001  } else if (IsCrossHair()) {
//STRIP001      DrawHor(rOut,aPt1.X(),0,aPt1.Y(),bMov);
//STRIP001      DrawHor(rOut,aPt1.X(),aS.Width(),aPt1.Y(),bMov);
//STRIP001      DrawVer(rOut,aPt1.X(),aPt1.Y(),0,bMov);
//STRIP001      DrawVer(rOut,aPt1.X(),aPt1.Y(),aS.Height(),bMov);
//STRIP001  } else {
//STRIP001      if (dx!=0) {
//STRIP001          DrawHor(rOut,aPt1.X(),aPt2.X(),aPt1.Y(),bMov);
//STRIP001          if (dy>0) DrawHor(rOut,aPt2.X(),aPt1.X(),aPt2.Y(),bMov);
//STRIP001      }
//STRIP001      if (dy!=0 || (dy==1 && dx>1)) {
//STRIP001          DrawVer(rOut,aPt1.X(),aPt1.Y(),aPt2.Y(),bMov);
//STRIP001          if (dx>0) DrawVer(rOut,aPt2.X(),aPt2.Y(),aPt1.Y(),bMov);
//STRIP001      }
//STRIP001  }
//STRIP001  rOut.EnableMapMode(bMap0);
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ FrameAnimator::FrameAnimator(SdrView& rNewView):
/*N*/   rView(rNewView)
/*N*/ {
/*N*/   aTim.SetTimeoutHdl(LINK(this,FrameAnimator,Hdl));
/*N*/   aTim.SetTimeout(50);
/*N*/   pOut=NULL;
/*N*/ }

//STRIP001 void FrameAnimator::Start() const
//STRIP001 {
//STRIP001  if (!Application::IsRemoteServer())
//STRIP001  {
//STRIP001        // Die Animation ist in der Remote-Version zu langsam.
//STRIP001        // Daher nur in der Nicht-Remote-Version Animation starten
//STRIP001        ((FrameAnimator*)this)->aTim.Start();
//STRIP001  }
//STRIP001 }

//STRIP001 void FrameAnimator::Stop() const
//STRIP001 {
//STRIP001  ((FrameAnimator*)this)->aTim.Stop();
//STRIP001 }

/*N*/ IMPL_LINK(FrameAnimator,Hdl,AutoTimer*,pTim)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if (rView.aDragStat.IsShown()) {
//STRIP001      USHORT i=0;
//STRIP001      do {
//STRIP001          OutputDevice* pO=rView.pDragWin;
//STRIP001          if (pO==NULL) {
//STRIP001              pO=rView.GetWin(i);
//STRIP001              i++;
//STRIP001          }
//STRIP001          if (pO!=NULL) {
//STRIP001              RollIt(*pO,FALSE);
//STRIP001          }
//STRIP001      } while (pOut==NULL && i<rView.GetWinCount());
//STRIP001      IncRollIdx();
//STRIP001  }
/*N*/   return 0;
/*N*/ }

//STRIP001 void FrameAnimator::Invert(OutputDevice* pNewOut) const
//STRIP001 {
//STRIP001  USHORT i=0;
//STRIP001  ((FrameAnimator*)this)->pOut=pNewOut;
//STRIP001  do {
//STRIP001      OutputDevice* pO=pNewOut;
//STRIP001      if (pO==NULL) {
//STRIP001          pO=rView.GetWin(i);
//STRIP001          i++;
//STRIP001      }
//STRIP001      if (pO!=NULL) {
//STRIP001          RollingRect::Invert(*pO);
//STRIP001      }
//STRIP001  } while (pOut==NULL && i<rView.GetWinCount());
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////
//#define   TEST_IAO

/*N*/ SdrViewWinRec::SdrViewWinRec(OutputDevice* pW)
/*N*/ : pWin(pW),
/*N*/ //    pVDev(NULL),
//STRIP012/*N*/     pIAOManager(NULL),
/*N*/   bXorVisible(FALSE)
/*N*/ {
/*N*/   // is it a window?
/*N*/   if(pW && pW->GetOutDevType() == OUTDEV_WINDOW)
/*N*/   {
/*N*/       // create B2dIAOManager for this window
//STRIP012/*N*/         pIAOManager = new B2dIAOManager((Window*)pW);
//STRIP012#ifdef TEST_IAO
//STRIP012/*?*/         if(pIAOManager)
//STRIP012/*?*/         {
//STRIP012/*?*/             // create some demo shapes
//STRIP012/*?*/             B2dIAOLine* pLine;
//STRIP012/*?*/             B2dIAOMarker* pMarker;
//STRIP012/*?*/             B2dIAOBitmapObj* pBitmap;
//STRIP012/*?*/             B2dIAOTriangle* pTriangle;
//STRIP012/*?*/
//STRIP012/*?*/             static BOOL bCreateLines = FALSE;
//STRIP012/*?*/             static BOOL bCreateMarkers = FALSE;
//STRIP012/*?*/             static BOOL bCreateField = FALSE;
//STRIP012/*?*/             static BOOL bCreateSingleMarker = FALSE;
//STRIP012/*?*/             static BOOL bCreateBitmap = FALSE;
//STRIP012/*?*/             static BOOL bCreateBitmapField = FALSE;
//STRIP012/*?*/             static BOOL bCreateTriangle = FALSE;
//STRIP012/*?*/
//STRIP012/*?*/             if(bCreateLines)
//STRIP012/*?*/             {
//STRIP012/*?*/                 pLine = new B2dIAOLine(pIAOManager, Point(5000, 5200), Point(5000, 7000));
//STRIP012/*?*/                 pLine->SetBaseColor(Color(COL_CYAN));
//STRIP012/*?*/                 pLine = new B2dIAOLineStriped(pIAOManager, Point(5100, 5200), Point(5100, 7000));
//STRIP012/*?*/                 pLine->SetBaseColor(Color(COL_BLUE));
//STRIP012/*?*/                 B2dIAOLineTwoColor* p2Line = new B2dIAOLineTwoColor(pIAOManager, Point(5200, 5200), Point(5200, 7000));
//STRIP012/*?*/                 p2Line->SetBaseColor(Color(COL_YELLOW));
//STRIP012/*?*/                 p2Line->Set2ndColor(Color(COL_BLACK));
//STRIP012/*?*/                 B2dIAOLineTwoColorAnim* p3Line = new B2dIAOLineTwoColorAnim(pIAOManager, Point(5300, 5200), Point(5300, 7000));
//STRIP012/*?*/                 p3Line->SetBaseColor(Color(COL_YELLOW));
//STRIP012/*?*/                 p3Line->Set2ndColor(Color(COL_BLACK));
//STRIP012/*?*/             }
//STRIP012/*?*/
//STRIP012/*?*/             if(bCreateMarkers)
//STRIP012/*?*/             {
//STRIP012/*?*/                 pMarker = new B2dIAOMarker(pIAOManager, Point(5000, 5000), B2D_IAO_MARKER_POINT);
//STRIP012/*?*/                 pMarker->SetBaseColor(Color(COL_LIGHTRED));
//STRIP012/*?*/                 pMarker = new B2dIAOMarker(pIAOManager, Point(5100, 5000), B2D_IAO_MARKER_PLUS);
//STRIP012/*?*/                 pMarker->SetBaseColor(Color(COL_LIGHTGREEN));
//STRIP012/*?*/                 pMarker = new B2dIAOMarker(pIAOManager, Point(5200, 5000), B2D_IAO_MARKER_CROSS);
//STRIP012/*?*/                 pMarker->SetBaseColor(Color(COL_LIGHTBLUE));
//STRIP012/*?*/
//STRIP012/*?*/                 pMarker = new B2dIAOMarker(pIAOManager, Point(5000, 5100), B2D_IAO_MARKER_RECT_5X5);
//STRIP012/*?*/                 pMarker->SetBaseColor(Color(COL_LIGHTGREEN));
//STRIP012/*?*/                 pMarker->Set2ndColor(Color(COL_BLACK));
//STRIP012/*?*/                 pMarker = new B2dIAOMarker(pIAOManager, Point(5100, 5100), B2D_IAO_MARKER_RECT_7X7);
//STRIP012/*?*/                 pMarker->SetBaseColor(Color(COL_LIGHTGREEN));
//STRIP012/*?*/                 pMarker->Set2ndColor(Color(COL_BLACK));
//STRIP012/*?*/                 pMarker = new B2dIAOMarker(pIAOManager, Point(5200, 5100), B2D_IAO_MARKER_RECT_9X9);
//STRIP012/*?*/                 pMarker->SetBaseColor(Color(COL_LIGHTGREEN));
//STRIP012/*?*/                 pMarker->Set2ndColor(Color(COL_BLACK));
//STRIP012/*?*/             }
//STRIP012/*?*/
//STRIP012/*?*/             if(bCreateField || bCreateBitmapField)
//STRIP012/*?*/             {
//STRIP012/*?*/                 static UINT16 nNumX = 10;
//STRIP012/*?*/                 static UINT16 nNumY = 10;
//STRIP012/*?*/                 static UINT16 nStart = 2000;
//STRIP012/*?*/                 static UINT16 nEnd = 16000;
//STRIP012/*?*/
//STRIP012/*?*/                 for(UINT16 a=nStart;a<nEnd;a+=(nEnd-nStart)/nNumX)
//STRIP012/*?*/                 {
//STRIP012/*?*/                     for(UINT16 b=nStart;b<nEnd;b+=(nEnd-nStart)/nNumY)
//STRIP012/*?*/                     {
//STRIP012/*?*/                         if(bCreateField)
//STRIP012/*?*/                         {
//STRIP012/*?*/                             pMarker = new B2dIAOMarker(pIAOManager, Point(a, b), B2D_IAO_MARKER_RECT_7X7);
//STRIP012/*?*/                             pMarker->SetBaseColor(Color(
//STRIP012/*?*/                                 (((a-nStart)*256L)/(nEnd-nStart)),
//STRIP012/*?*/                                 (((b-nStart)*256L)/(nEnd-nStart)),
//STRIP012/*?*/                                 0x80));
//STRIP012/*?*/                             pMarker->Set2ndColor(Color(COL_BLACK));
//STRIP012/*?*/                         }
//STRIP012/*?*/                         if(bCreateBitmapField)
//STRIP012/*?*/                         {
//STRIP012/*?*/                             Bitmap aBitmap(Size(10, 10), 8);
//STRIP012/*?*/                             pBitmap = new B2dIAOBitmapObj(pIAOManager, Point(a, b), aBitmap);
//STRIP012/*?*/                         }
//STRIP012/*?*/                     }
//STRIP012/*?*/                 }
//STRIP012/*?*/             }
//STRIP012/*?*/             if(bCreateSingleMarker)
//STRIP012/*?*/             {
//STRIP012/*?*/                 pMarker = new B2dIAOMarker(pIAOManager, Point(5000, 5000), B2D_IAO_MARKER_RECT_7X7);
//STRIP012/*?*/                 pMarker->SetBaseColor(Color(COL_LIGHTGREEN));
//STRIP012/*?*/                 pMarker->Set2ndColor(Color(COL_BLACK));
//STRIP012/*?*/             }
//STRIP012/*?*/             if(bCreateBitmap)
//STRIP012/*?*/             {
//STRIP012/*?*/                 Bitmap aBitmap(Size(10, 10), 8);
//STRIP012/*?*/                 pBitmap = new B2dIAOBitmapObj(pIAOManager, Point(6000, 6000), aBitmap);
//STRIP012/*?*/             }
//STRIP012/*?*/             if(bCreateTriangle)
//STRIP012/*?*/             {
//STRIP012/*?*/                 pTriangle = new B2dIAOTriangle(pIAOManager, Point(5000, 5000), Point(7000, 5000), Point(6000, 7000), Color(COL_YELLOW));
//STRIP012/*?*/                 pLine = new B2dIAOLine(pIAOManager, pTriangle->GetBasePosition(), pTriangle->Get2ndPosition());
//STRIP012/*?*/                 pLine = new B2dIAOLine(pIAOManager, pTriangle->Get2ndPosition(), pTriangle->Get3rdPosition());
//STRIP012/*?*/                 pLine = new B2dIAOLine(pIAOManager, pTriangle->Get3rdPosition(), pTriangle->GetBasePosition());
//STRIP012/*?*/
//STRIP012/*?*/                 pTriangle = new B2dIAOBitmapTriangle(pIAOManager, Point(8000, 5000), Point(10000, 5000), Point(9000, 7000), Color(COL_RED));
//STRIP012/*?*/                 pLine = new B2dIAOLine(pIAOManager, pTriangle->GetBasePosition(), pTriangle->Get2ndPosition());
//STRIP012/*?*/                 pLine = new B2dIAOLine(pIAOManager, pTriangle->Get2ndPosition(), pTriangle->Get3rdPosition());
//STRIP012/*?*/                 pLine = new B2dIAOLine(pIAOManager, pTriangle->Get3rdPosition(), pTriangle->GetBasePosition());
//STRIP012/*?*/             }
//STRIP012/*?*/         }
//STRIP012#endif
/*N*/   }
/*N*/ }

/*N*/ SdrViewWinRec::~SdrViewWinRec()
/*N*/ {
/*N*/ //    if (pVDev!=NULL)
/*N*/ //        delete pVDev;
/*N*/
/*N*/   // cleanup IAOManager for this window
//STRIP012/*N*/     if(pIAOManager)
//STRIP012/*N*/         delete pIAOManager;
//STRIP012/*N*/     pIAOManager = NULL;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrViewWinList::Clear()
/*N*/ {
/*N*/   USHORT nAnz=GetCount();
/*N*/   for (USHORT i=0; i<nAnz; i++) {
/*N*/       delete GetObject(i);
/*N*/   }
/*N*/   aList.Clear();
/*N*/ }

/*N*/ USHORT SdrViewWinList::Find(OutputDevice* pW) const
/*N*/ {
/*N*/   USHORT nAnz=GetCount();
/*N*/   USHORT nRet=SDRVIEWWIN_NOTFOUND;
/*N*/   for (USHORT nNum=0; nNum<nAnz && nRet==SDRVIEWWIN_NOTFOUND; nNum++) {
/*N*/       if (GetObject(nNum)->pWin==pW) nRet=nNum;
/*N*/   }
/*N*/   return nRet;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ TYPEINIT1( SvxViewHint, SfxSimpleHint );
/*N*/
/*N*/ SvxViewHint::SvxViewHint( ULONG _nId ) :
/*N*/     SfxSimpleHint( _nId )
/*N*/ {
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@@@@   @@@@  @@ @@  @@ @@@@@@  @@ @@ @@ @@@@@ @@   @@
//  @@  @@ @@  @@ @@ @@@ @@   @@    @@ @@ @@ @@    @@   @@
//  @@  @@ @@  @@ @@ @@@@@@   @@    @@ @@ @@ @@    @@ @ @@
//  @@@@@  @@@@@@ @@ @@@@@@   @@    @@@@@ @@ @@@@  @@@@@@@
//  @@     @@  @@ @@ @@ @@@   @@     @@@  @@ @@    @@@@@@@
//  @@     @@  @@ @@ @@  @@   @@     @@@  @@ @@    @@@ @@@
//  @@     @@  @@ @@ @@  @@   @@      @   @@ @@@@@ @@   @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ TYPEINIT2(SdrPaintView,SfxListener,SfxRepeatTarget);

/*N*/ DBG_NAME(SdrPaintView)

/*N*/ void SdrPaintView::ImpClearVars()
/*N*/ {
/*N*/   pXOut=NULL;
/*N*/   bForeignXOut=FALSE;
/*N*/   pItemBrowser=NULL;
/*N*/   bLayerSortedRedraw=FALSE;
/*N*/   bPageVisible=TRUE;
/*N*/   bPageBorderVisible=TRUE;
/*N*/   bBordVisible=TRUE;
/*N*/   bGridVisible=TRUE;
/*N*/   bGridFront  =FALSE;
/*N*/   bHlplVisible=TRUE;
/*N*/   bHlplFront  =TRUE;
/*N*/   bGlueVisible=FALSE;
/*N*/   bGlueVisible2=FALSE;
/*N*/   bGlueVisible3=FALSE;
/*N*/   bGlueVisible4=FALSE;
/*N*/   bSwapAsynchron=FALSE;
/*N*/   bPrintPreview=FALSE;
/*N*/   bLineDraft=FALSE;
/*N*/   bFillDraft=FALSE;
/*N*/   bGrafDraft=FALSE;
/*N*/   bHideGrafDraft=FALSE;
/*N*/   bTextDraft=FALSE;
/*N*/   bLineDraftPrn=FALSE;
/*N*/   bFillDraftPrn=FALSE;
/*N*/   bGrafDraftPrn=FALSE;
/*N*/   bTextDraftPrn=FALSE;
/*N*/
/*N*/   bObjectPaintIgnoresClipping=FALSE;
/*N*/
/*N*/   eAnimationMode = SDR_ANIMATION_ANIMATE;
/*N*/     bAnimationPause = FALSE;
/*N*/
/*N*/   nHitTolPix=2;
/*N*/   nMinMovPix=3;
/*N*/   nHitTolLog=0;
/*N*/   nMinMovLog=0;
/*N*/   pActualOutDev=NULL;
/*N*/
/*N*/   bSaveHiddenPages=FALSE;
/*N*/   bPageTwice=FALSE;
/*N*/   pDragWin=NULL;
/*N*/   bRestoreColors=TRUE;
/*N*/   pDisabledAttr=NULL;
/*N*/   pDefaultStyleSheet=NULL;
/*N*/   bEncircle=FALSE;
/*N*/   bSomeObjChgdFlag=FALSE;
/*N*/
/*N*/   bMasterBmp=FALSE;
/*N*/   pMasterBmp=NULL;
/*N*/   nMasterCacheMode = SDR_MASTERPAGECACHE_DEFAULT;
/*N*/
/*N*/     nGraphicManagerDrawMode = GRFMGR_DRAW_STANDARD;
/*N*/
/*N*/   aComeBackTimer.SetTimeout(1);
/*N*/   aComeBackTimer.SetTimeoutHdl(LINK(this,SdrPaintView,ImpComeBackHdl));
/*N*/   aAfterPaintTimer.SetTimeout(1);
/*N*/   aAfterPaintTimer.SetTimeoutHdl(LINK(this,SdrPaintView,ImpAfterPaintHdl));
/*N*/   aUserMarkerAnimator.SetTimeout(50);
/*N*/   aUserMarkerAnimator.SetTimeoutHdl(LINK(this,SdrPaintView,ImpUserMarkerAnimatorHdl));
/*N*/
/*N*/   String aNam;    // System::GetUserName() just return an empty string
/*N*/
/*N*/   if (pMod)
/*N*/       SetDefaultStyleSheet(pMod->GetDefaultStyleSheet(), TRUE);
/*N*/
/*N*/   aNam.ToUpperAscii();
/*N*/
/*N*/   maGridColor = Color( COL_BLACK );
/*N*/ }


/*N*/ SdrPaintView::SdrPaintView(SdrModel* pModel1, OutputDevice* pOut):
/*N*/   aPagV(1024,16,16),
/*N*/   aPagHide(1024,16,16),
/*N*/   aAni(*(SdrView*)this),
/*N*/   aDefaultAttr(pModel1->GetItemPool()),
/*N*/   aUserMarkers(1024,16,16)
/*N*/ {
/*N*/   DBG_CTOR(SdrPaintView,NULL);
/*N*/   pMod=pModel1;
/*N*/   ImpClearVars();
/*N*/   if (pOut!=NULL) AddWin(pOut);
/*N*/   pXOut=new ExtOutputDevice(pOut);
/*N*/
/*N*/   // Flag zur Visualisierung von Gruppen
/*N*/   bVisualizeEnteredGroup = TRUE;
/*N*/
/*N*/   StartListening( maColorConfig );
/*N*/   onChangeColorConfig();
/*N*/ }

/*?*/ SdrPaintView::SdrPaintView(SdrModel* pModel1, ExtOutputDevice* pExtOut):
/*?*/   aPagV(1024,16,16),
/*?*/   aPagHide(1024,16,16),
/*?*/   aAni(*(SdrView*)this),
/*?*/   aDefaultAttr(pModel1->GetItemPool()),
/*?*/   aUserMarkers(1024,16,16)
/*?*/ {
/*?*/   DBG_CTOR(SdrPaintView,NULL);
/*?*/   pMod=pModel1;
/*?*/   ImpClearVars();
/*?*/   pMod=pModel1;
/*?*/   if (pExtOut!=NULL) {
/*?*/       bForeignXOut=TRUE;
/*?*/       pXOut=pExtOut;
/*?*/       OutputDevice* pO=pXOut->GetOutDev();
/*?*/       if (pO!=NULL) AddWin(pO);
/*?*/   } else {
/*?*/       pXOut=new ExtOutputDevice(NULL);
/*?*/   }
/*?*/
/*?*/   // Flag zur Visualisierung von Gruppen
/*?*/   bVisualizeEnteredGroup = TRUE;
/*?*/
/*?*/   StartListening( maColorConfig );
/*?*/   onChangeColorConfig();
/*?*/ }

/*N*/ SdrPaintView::~SdrPaintView()
/*N*/ {
/*N*/   DBG_DTOR(SdrPaintView,NULL);
/*N*/   aAfterPaintTimer.Stop();
/*N*/
/*N*/   EndListening( maColorConfig );
/*N*/
/*N*/   ClearAll();
/*N*/   if (!bForeignXOut && pXOut!=NULL) {
/*N*/       delete pXOut;
/*N*/   }
/*N*/   if (pDisabledAttr!=NULL) {
/*?*/       delete pDisabledAttr;
/*N*/   }
/*N*/   if (pMasterBmp!=NULL) {
/*?*/       delete pMasterBmp;
/*N*/   }
/*N*/ #ifndef SVX_LIGHT
/*N*/   if (pItemBrowser!=NULL) {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001   delete pItemBrowser;
/*N*/   }
/*N*/ #endif
/*N*/   USHORT nAnz=ImpGetUserMarkerCount();
/*N*/   for (USHORT nNum=0; nNum<nAnz; nNum++) {
/*?*/       SdrViewUserMarker* pUM=ImpGetUserMarker(nNum);
/*?*/       pUM->pView=NULL; // Weil's mich gleich nichtmehr gibt.
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void __EXPORT SdrPaintView::SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType)
/*N*/ {
/*N*/   BOOL bObjChg=!bSomeObjChgdFlag; // TRUE= auswerten fuer ComeBack-Timer
/*N*/   BOOL bMaster=pMasterBmp!=NULL;  // TRUE= auswerten fuer MasterPagePaintCache
/*N*/   if (bObjChg || bMaster) {
/*N*/       SdrHint* pSdrHint=PTR_CAST(SdrHint,&rHint);
/*N*/       if (pSdrHint!=NULL) {
/*N*/           SdrHintKind eKind=pSdrHint->GetKind();
/*N*/           if (eKind==HINT_OBJCHG || eKind==HINT_OBJINSERTED || eKind==HINT_OBJREMOVED) {
/*N*/               if (bObjChg) {
/*N*/                   bSomeObjChgdFlag=TRUE;
/*N*/                   aComeBackTimer.Start();
/*N*/               }
/*N*/               if (bMaster) {
/*?*/                   const SdrPage* pPg=pSdrHint->GetPage();
/*?*/                   if (pPg!=NULL && pPg->IsMasterPage() && pPg->GetPageNum()==pMasterBmp->GetMasterPageNum()) {
/*?*/                       ReleaseMasterPagePaintCache();
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/           if (eKind==HINT_PAGEORDERCHG) {
/*N*/               const SdrPage* pPg=pSdrHint->GetPage();
/*N*/               if (!pPg->IsInserted()) { // aha, Seite geloescht: also hiden
/*N*/                   USHORT nAnz=GetPageViewCount();
/*N*/                   USHORT nv;
/*N*/                   for (nv=nAnz; nv>0;) {
/*?*/                       nv--;
/*?*/                       SdrPageView* pPV=GetPageViewPvNum(nv);
/*?*/                       if (pPV->GetPage()==pPg) {
/*?*/                           HidePagePvNum(nv);
/*N*/                       }
/*N*/                   }
/*N*/               }
/*N*/               if (bMaster) ReleaseMasterPagePaintCache();
/*N*/           }
/*N*/           if (eKind==HINT_PAGECHG) {
/*N*/               if (bMaster) ReleaseMasterPagePaintCache();
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if( rHint.ISA( SfxSimpleHint ) && ( (SfxSimpleHint&) rHint ).GetId() == SFX_HINT_COLORS_CHANGED )
/*N*/   {
/*?*/       onChangeColorConfig();
/*?*/       InvalidateAllWin();
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ IMPL_LINK_INLINE_START(SdrPaintView,ImpComeBackHdl,Timer*,pTimer)
/*N*/ {
/*N*/   if (bSomeObjChgdFlag) {
/*N*/       bSomeObjChgdFlag=FALSE;
/*N*/       ModelHasChanged();
/*N*/   }
/*N*/   return 0;
/*N*/ }

/*N*/ IMPL_LINK_INLINE_END(SdrPaintView,ImpComeBackHdl,Timer*,pTimer)

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 struct ImpAsyncStruct
//STRIP001 {
//STRIP001  const SdrObject*    mpObj;
//STRIP001  const OutputDevice* mpOut;
//STRIP001  const Rectangle     maRectPix;
//STRIP001
//STRIP001                      ImpAsyncStruct( const SdrObject* pObj, const OutputDevice* pOut ) :
//STRIP001                          mpObj( pObj ), mpOut( pOut ), maRectPix( pOut->LogicToPixel( pObj->GetBoundRect() ) ) {}
//STRIP001 };

//STRIP001 void SdrPaintView::ImpAddAsyncObj( const SdrObject* pObj, const OutputDevice* pOut )
//STRIP001 {
//STRIP001  aAsyncPaintList.Insert( new ImpAsyncStruct( pObj, pOut ), LIST_APPEND );
//STRIP001 }

/*?*/ void SdrPaintView::ImpAsyncPaintDone( const SdrObject* pObj )
/*?*/ {{DBG_BF_ASSERT(0, "STRIP");}//STRIP001
//STRIP001     // #110290# Remove the given object from the
//STRIP001     // maSwappedInGraphicsStack list, as the object
//STRIP001     // itself caters for swapout again.
//STRIP001     maSwappedInGraphicsStack.remove( (SdrGrafObj*)pObj );
/*?*/ }

/*N*/ IMPL_LINK(SdrPaintView,ImpAfterPaintHdl,Timer*,pTimer)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  while( aAsyncPaintList.Count() )
//STRIP001  {
//STRIP001      Rectangle           aInvRect;
//STRIP001      const OutputDevice* pOut = NULL;
//STRIP001
//STRIP001      for( void* p = aAsyncPaintList.First(); p;  )
//STRIP001      {
//STRIP001          ImpAsyncStruct* pAsync = (ImpAsyncStruct*) p;
//STRIP001          BOOL            bMatch = TRUE;
//STRIP001
//STRIP001          if( pAsync->mpObj && pAsync->mpObj->ISA( SdrGrafObj) )
//STRIP001             {
//STRIP001                 // #110290# Store swapped-in graphic, such that we can later
//STRIP001                 // force-swap it out, when this view is cleared.
//STRIP001                 maSwappedInGraphicsStack.push_front( (SdrGrafObj*) pAsync->mpObj );
//STRIP001
//STRIP001              ( (SdrGrafObj*) pAsync->mpObj )->ForceSwapIn();
//STRIP001             }
//STRIP001
//STRIP001          if( !pOut )
//STRIP001              pOut = pAsync->mpOut;
//STRIP001          else if( pOut != pAsync->mpOut )
//STRIP001              bMatch = FALSE;
//STRIP001
//STRIP001          if( bMatch )
//STRIP001          {
//STRIP001              aInvRect.Union( pAsync->maRectPix );
//STRIP001              delete (ImpAsyncStruct*) aAsyncPaintList.Remove();
//STRIP001              p = aAsyncPaintList.GetCurObject();
//STRIP001          }
//STRIP001          else
//STRIP001              p = aAsyncPaintList.Next();
//STRIP001      }
//STRIP001
//STRIP001      if( OUTDEV_WINDOW == pOut->GetOutDevType() )
//STRIP001          ( (Window*) pOut )->Invalidate( pOut->PixelToLogic( aInvRect ) );
//STRIP001  }
//STRIP001
//STRIP001  ((SdrMarkView*)this)->ImpAfterPaint();
//STRIP001
/*N*/   return 0;
/*N*/ }

/*N*/ void SdrPaintView::FlushComeBackTimer() const
/*N*/ {
/*N*/   if (bSomeObjChgdFlag) {
/*N*/       // casting auf nonconst
/*N*/       ((SdrPaintView*)this)->ImpComeBackHdl(&((SdrPaintView*)this)->aComeBackTimer);
/*N*/       ((SdrPaintView*)this)->aComeBackTimer.Stop();
/*N*/   }
/*N*/ }

/*N*/ void SdrPaintView::ModelHasChanged()
/*N*/ {
/*N*/   // Auch alle PageViews benachrichtigen
/*N*/   USHORT nv;
/*N*/   USHORT nAnz;
/*N*/   nAnz=GetPageViewCount();
/*N*/   for (nv=nAnz; nv>0;) {
/*N*/       nv--;
/*N*/       SdrPageView* pPV=GetPageViewPvNum(nv);
/*N*/       if (!pPV->GetPage()->IsInserted()) {
/*?*/           HidePage(pPV);
/*N*/       }
/*N*/   }
/*N*/   nAnz=GetPageViewCount();
/*N*/   for (nv=0; nv<nAnz; nv++) {
/*N*/       SdrPageView* pPV=GetPageViewPvNum(nv);
/*N*/       pPV->ModelHasChanged();
/*N*/   }
/*N*/   nAnz=GetPageHideCount();
/*N*/   for (nv=0; nv<nAnz; nv++) {
/*?*/       SdrPageView* pPV=GetPageHidePvNum(nv);
/*?*/       pPV->ModelHasChanged();
/*N*/   }
/*N*/ #ifndef SVX_LIGHT
/*N*/   if (pItemBrowser!=NULL) {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 pItemBrowser->SetDirty();
/*N*/ #endif
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ IMPL_LINK_INLINE_START(SdrPaintView,ImpUserMarkerAnimatorHdl,AutoTimer*,pTimer)
/*N*/ {
/*N*/   USHORT nAnz=ImpGetUserMarkerCount();
/*N*/   for (USHORT nNum=0; nNum<nAnz; nNum++) {
/*N*/       SdrViewUserMarker* pUM=ImpGetUserMarker(nNum);
/*N*/       if (pUM->IsAnimate() && pUM->IsVisible()) {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 pUM->DoAnimateOneStep();
/*N*/   }
/*N*/   return 0;
/*N*/ }

/*N*/ IMPL_LINK_INLINE_END(SdrPaintView,ImpUserMarkerAnimatorHdl,AutoTimer*,pTimer)

/*N*/ void SdrPaintView::ImpInsertUserMarker(SdrViewUserMarker* pMarker)
/*N*/ {
/*N*/   aUserMarkers.Insert(pMarker);
/*N*/   ImpCheckMarkerAnimator();
/*N*/ }
/*N*/
/*N*/ void SdrPaintView::ImpRemoveUserMarker(SdrViewUserMarker* pMarker)
/*N*/ {
/*N*/   aUserMarkers.Remove(pMarker);
/*N*/   ImpCheckMarkerAnimator();
/*N*/ }
/*N*/
/*N*/ void SdrPaintView::ImpCheckMarkerAnimator()
/*N*/ {
/*N*/   BOOL bNeed=FALSE;
/*N*/   USHORT nAnz=ImpGetUserMarkerCount();
/*N*/   for (USHORT nNum=0; nNum<nAnz && !bNeed; nNum++) {
/*N*/       SdrViewUserMarker* pUM=ImpGetUserMarker(nNum);
/*N*/       bNeed=pUM->IsAnimate();
/*N*/   }
/*N*/   if (bNeed) aUserMarkerAnimator.Start();
/*N*/   else aUserMarkerAnimator.Stop();
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ BOOL SdrPaintView::IsAction() const
/*N*/ {
/*N*/   return IsEncirclement();
/*N*/ }

//STRIP001 void SdrPaintView::MovAction(const Point& rPnt)
//STRIP001 {
//STRIP001  if (IsEncirclement()) {
//STRIP001      MovEncirclement(rPnt);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrPaintView::EndAction()
//STRIP001 {
//STRIP001  if (IsEncirclement()) EndEncirclement();
//STRIP001 }

//STRIP001 void SdrPaintView::BckAction()
//STRIP001 {
//STRIP001  BrkEncirclement();
//STRIP001 }

/*N*/ void SdrPaintView::BrkAction()
/*N*/ {
/*N*/   BrkEncirclement();
/*N*/ }

//STRIP001 void SdrPaintView::TakeActionRect(Rectangle& rRect) const
//STRIP001 {
//STRIP001  if (IsEncirclement()) {
//STRIP001      rRect=Rectangle(aDragStat.GetStart(),aDragStat.GetNow());
//STRIP001  }
//STRIP001 }

/*N*/ void SdrPaintView::ToggleShownXor(OutputDevice* pOut, const Region* pRegion) const
/*N*/ {
/*N*/   if (IsEncirclement() && aDragStat.IsShown()) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        DrawEncirclement(pOut);
/*N*/   }
/*N*/   USHORT nAnz=ImpGetUserMarkerCount();
/*N*/   for (USHORT nNum=0; nNum<nAnz; nNum++) {
/*N*/       SdrViewUserMarker* pUM=ImpGetUserMarker(nNum);
/*N*/       if (pUM->IsVisible()) {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 pUM->Draw(pOut,FALSE,!bRestoreColors); // den 3. Parameter hier noch richtig setzen !!!!!
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 USHORT SdrPaintView::ImpGetMinMovLogic(short nMinMov, const OutputDevice* pOut) const
//STRIP001 {
//STRIP001  if (nMinMov>=0) return USHORT(nMinMov);
//STRIP001  if (pOut==NULL) pOut=GetWin(0);
//STRIP001  if (pOut!=NULL) {
//STRIP001      return short(-pOut->PixelToLogic(Size(nMinMov,0)).Width());
//STRIP001  } else {
//STRIP001      return 0;
//STRIP001  }
//STRIP001 }

/*N*/ USHORT SdrPaintView::ImpGetHitTolLogic(short nHitTol, const OutputDevice* pOut) const
/*N*/ {
/*N*/   if (nHitTol>=0) return USHORT(nHitTol);
/*?*/   if (pOut==NULL) pOut=GetWin(0);
/*?*/   if (pOut!=NULL) {
/*?*/       return short(-pOut->PixelToLogic(Size(nHitTol,0)).Width());
/*?*/   } else {
/*?*/       return 0;
/*?*/   }
/*N*/ }

/*N*/ void SdrPaintView::TheresNewMapMode()
/*N*/ {
/*N*/   if (pActualOutDev!=NULL) {
/*N*/       nHitTolLog=(USHORT)((OutputDevice*)pActualOutDev)->PixelToLogic(Size(nHitTolPix,0)).Width();
/*N*/       nMinMovLog=(USHORT)((OutputDevice*)pActualOutDev)->PixelToLogic(Size(nMinMovPix,0)).Width();
/*N*/   }
/*N*/ }

/*N*/ void SdrPaintView::SetActualWin(const OutputDevice* pWin)
/*N*/ {
/*N*/   pActualOutDev=pWin;
/*N*/   TheresNewMapMode();
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrPaintView::BegEncirclement(const Point& rPnt, OutputDevice* pOut, short nMinMov)
//STRIP001 {
//STRIP001  BrkAction();
//STRIP001  aDragStat.Reset(rPnt);
//STRIP001  aDragStat.SetMinMove(ImpGetMinMovLogic(nMinMov,pOut));
//STRIP001  if (nMinMov==0) aDragStat.SetMinMoved();
//STRIP001  aAni.Reset();
//STRIP001  aDragStat.NextPoint();
//STRIP001  pDragWin=pOut;
//STRIP001  bEncircle=TRUE;
//STRIP001  if (aDragStat.IsMinMoved()) ShowEncirclement(pOut);
//STRIP001 }

//STRIP001 void SdrPaintView::MovEncirclement(const Point& rPnt)
//STRIP001 {
//STRIP001  if (IsEncirclement()) {
//STRIP001      if (aDragStat.IsMinMoved()) HideEncirclement(pDragWin);
//STRIP001      aDragStat.NextMove(rPnt);
//STRIP001      if (aDragStat.CheckMinMoved(rPnt)) ShowEncirclement(pDragWin);
//STRIP001  }
//STRIP001 }

//STRIP001 Rectangle SdrPaintView::EndEncirclement(BOOL bNoJustify)
//STRIP001 {
//STRIP001  if (IsEncirclement() && aDragStat.IsMinMoved()) {
//STRIP001      HideEncirclement(pDragWin);
//STRIP001      bEncircle=FALSE;
//STRIP001      Rectangle aRect(aDragStat.GetStart(),aDragStat.GetNow());
//STRIP001      if (!bNoJustify) aRect.Justify();
//STRIP001      return aRect;
//STRIP001  }
//STRIP001  bEncircle=FALSE;
//STRIP001  return Rectangle();
//STRIP001 }

/*N*/ void SdrPaintView::BrkEncirclement()
/*N*/ {
/*N*/   if (IsEncirclement()) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        HideEncirclement(pDragWin);
//STRIP001 /*?*/        bEncircle=FALSE;
/*N*/   }
/*N*/ }

//STRIP001 void SdrPaintView::ShowEncirclement(OutputDevice* pOut)
//STRIP001 {
//STRIP001  if (IsEncirclement() && !aDragStat.IsShown()) {
//STRIP001      DrawEncirclement(pOut);
//STRIP001      aDragStat.SetShown(TRUE);
//STRIP001      aAni.Start();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrPaintView::HideEncirclement(OutputDevice* pOut)
//STRIP001 {
//STRIP001  if (IsEncirclement() && aDragStat.IsShown()) {
//STRIP001      aAni.Stop();
//STRIP001      DrawEncirclement(pOut);
//STRIP001      aDragStat.SetShown(FALSE);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrPaintView::DrawEncirclement(OutputDevice* pOut) const
//STRIP001 {
//STRIP001  if (IsEncirclement()) {
//STRIP001      aAni.SetP1(aDragStat.GetStart());
//STRIP001      aAni.SetP2(aDragStat.GetNow());
//STRIP001      aAni.Invert(pOut);
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrPaintView::ShowShownXor(OutputDevice* pOut, BOOL bShow)
/*N*/ {
/*N*/   USHORT nAnz=GetWinCount();
/*N*/   USHORT nw=0;
/*N*/   BOOL bWeiter=TRUE;
/*N*/   do {
/*N*/       if (pOut!=NULL) {
/*N*/           nw=aWinList.Find(pOut);
/*N*/           bWeiter=FALSE;
/*N*/       }
/*N*/       if (nw<nAnz && nw!=SDRVIEWWIN_NOTFOUND) {
/*N*/           BOOL bOn=IsShownXorVisibleWinNum(nw);
/*N*/           if (bOn!=bShow) {
/*N*/               ToggleShownXor(GetWin(nw),NULL);
/*N*/               SetShownXorVisible(nw,bShow);
/*N*/           }
/*N*/       } else bWeiter=FALSE;
/*N*/   } while (bWeiter);
/*N*/ }

/*N*/ BOOL SdrPaintView::IsShownXorVisible(OutputDevice* pOut) const
/*N*/ {
/*N*/   USHORT nPos=aWinList.Find(pOut);
/*N*/   if (nPos!=SDRVIEWWIN_NOTFOUND) {
/*N*/       return IsShownXorVisibleWinNum(nPos);
/*N*/   } else {
/*N*/       return FALSE;
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrPaintView::ClearPageViews()
/*N*/ {
/*N*/   BrkAction();
/*N*/   for (USHORT nv=0; nv<GetPageViewCount(); nv++) {
/*N*/       SdrPageView* pPV=GetPageViewPvNum(nv);
/*N*/       InvalidateAllWin(pPV->GetPageRect());
/*N*/       delete pPV;
/*N*/   }
/*N*/   aPagV.Clear();
/*N*/ }

/*N*/ void SdrPaintView::ClearHideViews()
/*N*/ {
/*N*/   for (USHORT nh=0; nh<GetPageHideCount(); nh++) {
/*?*/       SdrPageView* pPV=GetPageHidePvNum(nh);
/*?*/       delete pPV;
/*N*/   }
/*N*/   aPagHide.Clear();
/*N*/ }

/*N*/ void SdrPaintView::Clear()
/*N*/ {
/*N*/   ClearPageViews();
/*N*/   ClearHideViews();
/*N*/ }

/*N*/ void SdrPaintView::ClearAll()
/*N*/ {
/*N*/   for( void* p = aAsyncPaintList.First(); p; p = aAsyncPaintList.Next() )
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 delete (ImpAsyncStruct*) p;
/*N*/
/*N*/   aAsyncPaintList.Clear();
/*N*/   ClearPageViews();
/*N*/   ClearHideViews();
/*N*/     ImpForceSwapOut();
/*N*/ }

/*N*/ SdrPageView* SdrPaintView::ShowPage(SdrPage* pPage, const Point& rOffs)
/*N*/ {
/*N*/   SdrPageView* pPV=NULL;
/*N*/   if (pPage!=NULL) {
/*N*/       SdrPageView* pTmpPV=NULL;
/*N*/       if (!bPageTwice) pTmpPV=GetPageView(pPage); // Evtl. jede Seite nur einmal!
/*N*/       if (pTmpPV==NULL) {
/*N*/           USHORT nPos=GetHiddenPV(pPage);   // War die schon mal da?
/*N*/           if (nPos<GetPageHideCount()) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/                pPV=GetPageHidePvNum(nPos);
//STRIP001 /*?*/                aPagHide.Remove(nPos);
//STRIP001 /*?*/                pPV->SetOffset(rOffs);
/*N*/           } else {
/*N*/               pPV=new SdrPageView(pPage,rOffs,*((SdrView*)this));
/*N*/           }
/*N*/           if (pPV!=NULL) {
/*N*/               aPagV.Insert(pPV,CONTAINER_APPEND);
/*N*/               pPV->Show();
/*N*/
/*N*/                 // #110290# Swap out graphics when switching pages
/*N*/                 ImpForceSwapOut();
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return pPV;
/*N*/ }

/*N*/ SdrPageView* SdrPaintView::ShowPagePgNum(USHORT nPgNum, const Point& rOffs)
/*N*/ {
/*N*/   return ShowPage(pMod->GetPage(nPgNum),rOffs);
/*N*/ }

//STRIP001 SdrPageView* SdrPaintView::ShowMasterPagePgNum(USHORT nPgNum, const Point& rOffs)
//STRIP001 {
//STRIP001  return ShowPage(pMod->GetMasterPage(nPgNum),rOffs);
//STRIP001 }

/*N*/ void SdrPaintView::HidePage(SdrPageView* pPV)
/*N*/ {
/*N*/   if (pPV!=NULL) {
/*N*/       ULONG nPos=aPagV.GetPos(pPV);
/*N*/       if (nPos!=CONTAINER_ENTRY_NOTFOUND) {
/*N*/           aPagV.Remove(nPos);
/*N*/           pPV->Hide();
/*N*/           if (bSaveHiddenPages) {
/*?*/               aPagHide.Insert(pPV,CONTAINER_APPEND);
/*N*/           } else {
/*N*/               delete pPV;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

//STRIP001 void SdrPaintView::HidePagePgNum(USHORT nPgNum)
//STRIP001 {
//STRIP001  HidePage(pMod->GetPage(nPgNum));
//STRIP001 }

/*N*/ void SdrPaintView::HideAllPages()
/*N*/ {
/*N*/   while (GetPageViewCount()>0) HidePagePvNum(0);
/*N*/ }

//STRIP001 void SdrPaintView::SetPagePos(SdrPageView* pPV, const Point& rOffs)
//STRIP001 {
//STRIP001  if (pPV!=NULL) {
//STRIP001      pPV->SetOffset(rOffs);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrPaintView::SetPagePosPgNum(USHORT nPgNum, const Point& rOffs)
//STRIP001 {
//STRIP001  SetPagePos(pMod->GetPage(nPgNum),rOffs);
//STRIP001 }

/*N*/ SdrPageView* SdrPaintView::GetPageView(const SdrPage* pPage) const
/*N*/ {
/*N*/   if (pPage==NULL) return NULL;
/*N*/   BOOL bWeiter=TRUE;
/*N*/   SdrPageView* pPV=NULL;
/*N*/   for (USHORT i=0; i<GetPageViewCount() && bWeiter; i++) {
/*?*/       pPV=GetPageViewPvNum(i);
/*?*/       bWeiter=(pPV->GetPage()!=pPage);
/*N*/   }
/*N*/   if (bWeiter) return NULL;
/*N*/   else return pPV;
/*N*/ }

//STRIP001 SdrPageView* SdrPaintView::GetPageViewPgNum(USHORT nPgNum) const
//STRIP001 {
//STRIP001  return GetPageView(pMod->GetPage(nPgNum));
//STRIP001 }

//STRIP001 SdrPageView* SdrPaintView::GetPageView(const Point& rPnt) const
//STRIP001 {
//STRIP001  SdrPageView* pHit=NULL;
//STRIP001  SdrPageView* pBest=GetPageViewPvNum(0);
//STRIP001  ULONG        nBest=0xFFFFFFFF;
//STRIP001
//STRIP001  for (USHORT i=GetPageViewCount(); i>0 && pHit==NULL;) {
//STRIP001      i--;
//STRIP001      SdrPageView* pPV=GetPageViewPvNum(i);
//STRIP001      Rectangle aRect(pPV->GetPageRect());
//STRIP001      if (aRect.IsInside(rPnt)) {
//STRIP001          pHit=pPV;
//STRIP001          pBest=pHit;
//STRIP001      } else {
//STRIP001          ULONG dx=0,dy=0;
//STRIP001          if (rPnt.X()<aRect.Left  ()) dx=ULONG(aRect.Left  ()-rPnt.X());
//STRIP001          if (rPnt.Y()<aRect.Top   ()) dy=ULONG(aRect.Top   ()-rPnt.Y());
//STRIP001          if (rPnt.X()>aRect.Right ()) dx=ULONG(rPnt.X()-aRect.Left  ());
//STRIP001          if (rPnt.Y()>aRect.Bottom()) dy=ULONG(rPnt.Y()-aRect.Bottom());
//STRIP001          ULONG nDist=dx+dy;
//STRIP001          if (nDist<nBest) {
//STRIP001              nBest=nDist;
//STRIP001              pBest=pPV;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return pBest;
//STRIP001 }

//STRIP001 USHORT SdrPaintView::GetPageViewNum(const SdrPageView* pPV) const
//STRIP001 {
//STRIP001  if (pPV==NULL) return 0xFFFF;
//STRIP001  ULONG nNum=aPagV.GetPos(pPV);
//STRIP001  if (nNum==CONTAINER_ENTRY_NOTFOUND) nNum=0xFFFF;
//STRIP001  return USHORT(nNum);
//STRIP001 }

//STRIP001 SdrPageView* SdrPaintView::HitPage(const Point& rPnt) const
//STRIP001 {
//STRIP001  SdrPageView* pHit=NULL;
//STRIP001  for (USHORT i=GetPageViewCount(); i>0 && pHit==NULL;) {
//STRIP001      i--;
//STRIP001      SdrPageView* pPV=GetPageViewPvNum(i);
//STRIP001      if (pPV->GetPageRect().IsInside(rPnt)) pHit=pPV;
//STRIP001  }
//STRIP001  return pHit;
//STRIP001 }

/*N*/ USHORT SdrPaintView::GetHiddenPV(const SdrPage* pPage) const
/*N*/ {
/*N*/   BOOL bWeiter=TRUE;
/*N*/   USHORT i;
/*N*/   for (i=0; i<GetPageHideCount() && bWeiter;) {
/*?*/       SdrPageView* pPV=GetPageHidePvNum(i);
/*?*/       bWeiter=(pPV->GetPage()!=pPage);
/*?*/       if (bWeiter) i++;
/*N*/   }
/*N*/   return i;
/*N*/ }

//STRIP001 USHORT SdrPaintView::GetPageHideNum(const SdrPageView* pPV) const
//STRIP001 {
//STRIP001  if (pPV==NULL) return 0xFFFF;
//STRIP001  ULONG nNum=aPagHide.GetPos(pPV);
//STRIP001  if (nNum==CONTAINER_ENTRY_NOTFOUND) nNum=0xFFFF;
//STRIP001  return USHORT(nNum);
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrPaintView::AddWin(OutputDevice* pWin1)
/*N*/ {
/*N*/   SdrViewWinRec* pWinRec=new SdrViewWinRec(pWin1);
/*N*/   pWinRec->bXorVisible=TRUE; // Normalerweise ist Xor nicht unterdrueckt
/*N*/   aWinList.Insert(pWinRec);
/*N*/   for (USHORT i=0; i<GetPageViewCount(); i++) {
/*?*/       GetPageViewPvNum(i)->AddWin(pWin1);
/*N*/   }
/*N*/ #ifndef SVX_LIGHT
/*N*/   if (pItemBrowser!=NULL) {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 pItemBrowser->ForceParent();
/*N*/ #endif
/*N*/ }

/*N*/ void SdrPaintView::DelWin(OutputDevice* pWin1)
/*N*/ {
/*N*/   USHORT nPos=aWinList.Find(pWin1);
/*N*/   if (nPos!=SDRVIEWWIN_NOTFOUND) {
/*N*/       for (USHORT i=0; i<GetPageViewCount(); i++) {
/*N*/           GetPageViewPvNum(i)->DelWin(pWin1);
/*N*/       }
/*N*/       aWinList.Delete(nPos);
/*N*/   }
/*N*/ #ifndef SVX_LIGHT
/*N*/   if (pItemBrowser!=NULL) {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 pItemBrowser->ForceParent();
/*N*/ #endif
/*N*/ }

/*N*/ Rectangle SdrPaintView::GetVisibleArea( USHORT nNum )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return Rectangle();//STRIP001
//STRIP001     OutputDevice* pWin = GetWin(nNum);
//STRIP001
//STRIP001     if( pWin )
//STRIP001     {
//STRIP001         // get visible area
//STRIP001         Size aVisSizePixel( pWin->GetOutputSizePixel() );
//STRIP001         return Rectangle( pWin->PixelToLogic(Rectangle(Point(0,0), aVisSizePixel)) );
//STRIP001     }
//STRIP001
//STRIP001     return Rectangle();
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 TRISTATE SdrPaintView::IsLayerSetVisible(const XubString& rName) const
//STRIP001 {
//STRIP001  TRISTATE nRet=FALSE;
//STRIP001  USHORT i=0;
//STRIP001  BOOL b1st=TRUE;
//STRIP001  while (i<GetPageViewCount() && nRet!=FUZZY) {
//STRIP001      SdrPageView* pPV=GetPageViewPvNum(i);
//STRIP001      BOOL bOn=pPV->IsLayerSetVisible(rName);
//STRIP001      if (b1st) {
//STRIP001          nRet=bOn;
//STRIP001          b1st=FALSE;
//STRIP001      } else {
//STRIP001          if (nRet!=bOn) nRet=FUZZY;
//STRIP001      }
//STRIP001      i++;
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

//STRIP001 void SdrPaintView::ShowLayerSet(const XubString& rName, BOOL bShow)
//STRIP001 {
//STRIP001  USHORT i;
//STRIP001  for (i=0; i<GetPageViewCount(); i++) {
//STRIP001      SdrPageView* pPV=GetPageViewPvNum(i);
//STRIP001      pPV->ShowLayerSet(rName,bShow);
//STRIP001  }
//STRIP001  InvalidateAllWin();
//STRIP001 }

//STRIP001 void SdrPaintView::SetLayerVisible(const XubString& rName, BOOL bShow)
//STRIP001 {
//STRIP001  USHORT i;
//STRIP001  for (i=0; i<GetPageViewCount(); i++) {
//STRIP001      SdrPageView* pPV=GetPageViewPvNum(i);
//STRIP001      pPV->SetLayerVisible(rName,bShow);
//STRIP001  }
//STRIP001  InvalidateAllWin();
//STRIP001 }

//STRIP001 TRISTATE SdrPaintView::IsLayerVisible(const XubString& rName) const
//STRIP001 {
//STRIP001  TRISTATE nRet=FALSE;
//STRIP001  USHORT i=0;
//STRIP001  BOOL b1st=TRUE;
//STRIP001  while (i<GetPageViewCount() && nRet!=FUZZY) {
//STRIP001      SdrPageView* pPV=GetPageViewPvNum(i);
//STRIP001      BOOL bOn=pPV->IsLayerVisible(rName);
//STRIP001      if (b1st) {
//STRIP001          nRet=bOn;
//STRIP001          b1st=FALSE;
//STRIP001      } else {
//STRIP001          if (nRet!=bOn) nRet=FUZZY;
//STRIP001      }
//STRIP001      i++;
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

//STRIP001 void SdrPaintView::SetAllLayersVisible(BOOL bShow)
//STRIP001 {
//STRIP001  USHORT i;
//STRIP001  for (i=0; i<GetPageViewCount(); i++) {
//STRIP001      SdrPageView* pPV=GetPageViewPvNum(i);
//STRIP001      pPV->SetAllLayersVisible(bShow);
//STRIP001  }
//STRIP001  InvalidateAllWin();
//STRIP001 }

/*N*/ void SdrPaintView::SetLayerLocked(const XubString& rName, BOOL bLock)
/*N*/ {
/*N*/   USHORT i;
/*N*/   for (i=0; i<GetPageViewCount(); i++) {
/*N*/       SdrPageView* pPV=GetPageViewPvNum(i);
/*N*/       pPV->SetLayerLocked(rName,bLock);
/*N*/   }
/*N*/ }

//STRIP001 TRISTATE SdrPaintView::IsLayerLocked(const XubString& rName) const
//STRIP001 {
//STRIP001  TRISTATE nRet=FALSE;
//STRIP001  USHORT i=0;
//STRIP001  BOOL b1st=TRUE;
//STRIP001  while (i<GetPageViewCount() && nRet!=FUZZY) {
//STRIP001      SdrPageView* pPV=GetPageViewPvNum(i);
//STRIP001      BOOL bLock=pPV->IsLayerLocked(rName);
//STRIP001      if (b1st) {
//STRIP001          nRet=bLock;
//STRIP001          b1st=FALSE;
//STRIP001      } else {
//STRIP001          if (nRet!=bLock) nRet=FUZZY;
//STRIP001      }
//STRIP001      i++;
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

//STRIP001 void SdrPaintView::SetAllLayersLocked(BOOL bLock)
//STRIP001 {
//STRIP001  USHORT i;
//STRIP001  for (i=0; i<GetPageViewCount(); i++) {
//STRIP001      SdrPageView* pPV=GetPageViewPvNum(i);
//STRIP001      pPV->SetAllLayersLocked(bLock);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrPaintView::SetLayerPrintable(const XubString& rName, BOOL bPrn)
//STRIP001 {
//STRIP001  USHORT i;
//STRIP001  for (i=0; i<GetPageViewCount(); i++) {
//STRIP001      SdrPageView* pPV=GetPageViewPvNum(i);
//STRIP001      pPV->SetLayerPrintable(rName,bPrn);
//STRIP001  }
//STRIP001 }

//STRIP001 TRISTATE SdrPaintView::IsLayerPrintable(const XubString& rName) const
//STRIP001 {
//STRIP001  TRISTATE nRet=FALSE;
//STRIP001  USHORT i=0;
//STRIP001  BOOL b1st=TRUE;
//STRIP001  while (i<GetPageViewCount() && nRet!=FUZZY) {
//STRIP001      SdrPageView* pPV=GetPageViewPvNum(i);
//STRIP001      BOOL bPrn=pPV->IsLayerPrintable(rName);
//STRIP001      if (b1st) {
//STRIP001          nRet=bPrn;
//STRIP001          b1st=FALSE;
//STRIP001      } else {
//STRIP001          if (nRet!=bPrn) nRet=FUZZY;
//STRIP001      }
//STRIP001      i++;
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

//STRIP001 void SdrPaintView::SetAllLayersPrintable(BOOL bPrn)
//STRIP001 {
//STRIP001  for (USHORT nv=0; nv<GetPageViewCount(); nv++) {
//STRIP001      SdrPageView* pPV=GetPageViewPvNum(nv);
//STRIP001      pPV->SetAllLayersPrintable(bPrn);
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrPaintView::InitRedraw(OutputDevice* pOut, const Region& rReg, USHORT nPaintMode)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  for (USHORT i=0; i<GetPageViewCount(); i++) {
//STRIP001      SdrPageView* pPV=GetPageViewPvNum(i);
//STRIP001      pPV->InitRedraw(pOut,rReg,nPaintMode,NULL);
//STRIP001  }
//STRIP001  USHORT nWinNum=aWinList.Find(pOut);
//STRIP001  if (nWinNum!=SDRVIEWWIN_NOTFOUND) {
//STRIP001      ((SdrMarkView*)this)->AfterInitRedraw(nWinNum);
//STRIP001      if (IsShownXorVisibleWinNum(nWinNum)) { // Durch Invalidate zerstoerte Handles wiederherstellen
//STRIP001          OutputDevice* pOut=GetWin(nWinNum);
//STRIP001          if (pOut!=NULL && pOut->GetOutDevType()!=OUTDEV_PRINTER) {
//STRIP001              ToggleShownXor(pOut,&rReg);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  RestartAfterPaintTimer();
/*N*/ }

//STRIP001 B2dIAOManager* SdrPaintView::GetIAOManager(OutputDevice* pOut)
//STRIP001 {
//STRIP001  UINT16 nWinIndex = aWinList.Find(pOut);
//STRIP001  if(nWinIndex != SDRVIEWWIN_NOTFOUND)
//STRIP001  {
//STRIP001      if(aWinList[nWinIndex].pIAOManager)
//STRIP001      {
//STRIP001          return aWinList[nWinIndex].pIAOManager;
//STRIP001      }
//STRIP001  }
//STRIP001  return NULL;
//STRIP001 }

//STRIP001 B2dIAOManager* SdrPaintView::GetFirstIAOManager()
//STRIP001 {
//STRIP001  if(aWinList.GetCount())
//STRIP001  {
//STRIP001      if(aWinList[0].pIAOManager)
//STRIP001      {
//STRIP001          return aWinList[0].pIAOManager;
//STRIP001      }
//STRIP001  }
//STRIP001  return NULL;
//STRIP001 }

//STRIP012/*N*/ void SdrPaintView::RefreshAllIAOManagers()
//STRIP012/*N*/ {
//STRIP012/*N*/     for(UINT16 a=0;a<aWinList.GetCount();a++)
//STRIP012/*N*/     {
//STRIP012/*N*/         if(aWinList[a].pIAOManager)
//STRIP012/*N*/         {
//STRIP012/*N*/             aWinList[a].pIAOManager->UpdateDisplay();
//STRIP012/*N*/         }
//STRIP012/*N*/     }
//STRIP012/*N*/ }

//STRIP012#ifdef TEST_IAO
//STRIP012static UINT16 nStepWidthForMove = 100;
//STRIP012static UINT32 nDirectObjectNum = 0L;
//STRIP012static UINT32 nInsertXPos = 4000;
//STRIP012static UINT32 nInsertYPos = 4000;
//STRIP012static UINT32 nInsertIncrement = 100;
//STRIP012#endif

//STRIP001 BOOL SdrPaintView::KeyInput(const KeyEvent& rKEvt, Window* pWin)
//STRIP001 {
//STRIP001 #ifdef TEST_IAO
//STRIP001  B2dIAOManager* pIAOManager = NULL;
//STRIP001  if(aWinList.GetCount() && aWinList[0].pIAOManager)
//STRIP001      pIAOManager = aWinList[0].pIAOManager;
//STRIP001
//STRIP001  if(pIAOManager)
//STRIP001  {
//STRIP001      switch(rKEvt.GetCharCode())
//STRIP001      {
//STRIP001          case '1' :  // On/Off
//STRIP001          {
//STRIP001              pIAOManager->SetVisible(!pIAOManager->IsVisible());
//STRIP001              break;
//STRIP001          }
//STRIP001          case 'a':
//STRIP001          case 's':
//STRIP001          case 'w':
//STRIP001          case 'y':   // move all
//STRIP001          {
//STRIP001              Vector2D aMove;
//STRIP001
//STRIP001              if(rKEvt.GetCharCode() == 'a') aMove.X() -= (double)nStepWidthForMove;
//STRIP001              if(rKEvt.GetCharCode() == 's') aMove.X() += (double)nStepWidthForMove;
//STRIP001              if(rKEvt.GetCharCode() == 'w') aMove.Y() -= (double)nStepWidthForMove;
//STRIP001              if(rKEvt.GetCharCode() == 'y') aMove.Y() += (double)nStepWidthForMove;
//STRIP001
//STRIP001              Matrix3D aTrans;
//STRIP001              aTrans.Translate(aMove);
//STRIP001              pIAOManager->Transform(aTrans);
//STRIP001              break;
//STRIP001          }
//STRIP001          case '3':
//STRIP001          {
//STRIP001              nDirectObjectNum++;
//STRIP001              if(nDirectObjectNum >= pIAOManager->GetIAOCount())
//STRIP001                  nDirectObjectNum = 0L;
//STRIP001              break;
//STRIP001          }
//STRIP001          case '2':
//STRIP001          {
//STRIP001              if(nDirectObjectNum)
//STRIP001                  nDirectObjectNum--;
//STRIP001              else
//STRIP001                  nDirectObjectNum = pIAOManager->GetIAOCount()-1;
//STRIP001              break;
//STRIP001          }
//STRIP001          case '4':
//STRIP001          {
//STRIP001              B2dIAObject* pAct = pIAOManager->GetIAObject(nDirectObjectNum);
//STRIP001              if(pAct)
//STRIP001              {
//STRIP001                  delete pAct;
//STRIP001              }
//STRIP001              break;
//STRIP001          }
//STRIP001          case '5':
//STRIP001          {
//STRIP001              B2dIAOMarker* pMarker = new B2dIAOMarker(pIAOManager, Point(nInsertXPos, nInsertYPos), B2D_IAO_MARKER_RECT_7X7);
//STRIP001              nInsertXPos += nInsertIncrement;
//STRIP001              nInsertYPos += nInsertIncrement;
//STRIP001              pMarker->SetBaseColor(Color(COL_YELLOW));
//STRIP001              pMarker->Set2ndColor(Color(COL_BLACK));
//STRIP001              break;
//STRIP001          }
//STRIP001          case 'd':
//STRIP001          case 'f':
//STRIP001          case 'r':
//STRIP001          case 'c':   // move
//STRIP001          {
//STRIP001              Vector2D aMove;
//STRIP001
//STRIP001              if(rKEvt.GetCharCode() == 'd') aMove.X() -= (double)nStepWidthForMove;
//STRIP001              if(rKEvt.GetCharCode() == 'f') aMove.X() += (double)nStepWidthForMove;
//STRIP001              if(rKEvt.GetCharCode() == 'r') aMove.Y() -= (double)nStepWidthForMove;
//STRIP001              if(rKEvt.GetCharCode() == 'c') aMove.Y() += (double)nStepWidthForMove;
//STRIP001
//STRIP001              Matrix3D aTrans;
//STRIP001              aTrans.Translate(aMove);
//STRIP001
//STRIP001              B2dIAObject* pAct = pIAOManager->GetIAObject(nDirectObjectNum);
//STRIP001              if(pAct)
//STRIP001                  pAct->Transform(aTrans);
//STRIP001              break;
//STRIP001          }
//STRIP001          case 't':
//STRIP001          case 'z':
//STRIP001          case 'u':
//STRIP001          case 'i':   // rotate all
//STRIP001          {
//STRIP001              B2dIAObject* pCenterObj = pIAOManager->GetIAObject(nDirectObjectNum);
//STRIP001              if(pCenterObj)
//STRIP001              {
//STRIP001                  Vector2D aCenter(pCenterObj->GetBasePosition());
//STRIP001                  Matrix3D aTrans;
//STRIP001
//STRIP001                  aTrans.Translate(-aCenter);
//STRIP001                  if(rKEvt.GetCharCode() == 't') aTrans.Rotate(  1.0 * (F_PI / 180.0));
//STRIP001                  if(rKEvt.GetCharCode() == 'z') aTrans.Rotate( 10.0 * (F_PI / 180.0));
//STRIP001                  if(rKEvt.GetCharCode() == 'u') aTrans.Rotate(-10.0 * (F_PI / 180.0));
//STRIP001                  if(rKEvt.GetCharCode() == 'i') aTrans.Rotate( -1.0 * (F_PI / 180.0));
//STRIP001                  aTrans.Translate(aCenter);
//STRIP001
//STRIP001                  pIAOManager->Transform(aTrans);
//STRIP001              }
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // update display if necessary
//STRIP001      pIAOManager->UpdateDisplay();
//STRIP001  }
//STRIP001 #endif
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 void SdrPaintView::InitRedraw(USHORT nWinNum, const Region& rReg, USHORT nPaintMode)
//STRIP001 {
//STRIP001  for (USHORT i=0; i<GetPageViewCount(); i++) {
//STRIP001      SdrPageView* pPV=GetPageViewPvNum(i);
//STRIP001      pPV->InitRedraw(nWinNum,rReg,nPaintMode,NULL);
//STRIP001  }
//STRIP001  ((SdrMarkView*)this)->AfterInitRedraw(nWinNum);
//STRIP001  if (IsShownXorVisibleWinNum(nWinNum)) { // Durch Invalidate zerstoerte Handles wiederherstellen
//STRIP001      OutputDevice* pOut=GetWin(nWinNum);
//STRIP001      if (pOut!=NULL && pOut->GetOutDevType()!=OUTDEV_PRINTER) {
//STRIP001          ToggleShownXor(pOut,&rReg);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  RestartAfterPaintTimer();
//STRIP001 }

/*N*/ void SdrPaintView::PostPaint()
/*N*/ {
/*N*/   // refresh with Paint-functionality
//STRIP012/*N*/     RefreshAllIAOManagers();
/*N*/ }

/*N*/ void SdrPaintView::RestartAfterPaintTimer()
/*N*/ {
/*N*/   // start timer for ImpAfterPaint()
/*N*/   aAfterPaintTimer.Start();
/*N*/ }

//STRIP001 BOOL SdrPaintView::IsRedrawReady() const
//STRIP001 {
//STRIP001  BOOL bOk=TRUE;
//STRIP001  for (USHORT i=0; i<GetPageViewCount() && bOk; i++) {
//STRIP001      SdrPageView* pPV=GetPageViewPvNum(i);
//STRIP001      bOk=pPV->IsReady();
//STRIP001  }
//STRIP001  return bOk;
//STRIP001 }

//STRIP001 BOOL SdrPaintView::RedrawOne(USHORT nBrkEvent)
//STRIP001 {
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL SdrPaintView::RedrawUntilInput(USHORT nBrkEvent)
//STRIP001 {
//STRIP001  return TRUE;
//STRIP001 }

/*N*/ void SdrPaintView::GlueInvalidate() const
/*N*/ {DBG_BF_ASSERT(0, "STRIP");
//STRIP001  USHORT nPvAnz=GetPageViewCount();
//STRIP001  USHORT nWinAnz=GetWinCount();
//STRIP001  for (USHORT nWinNum=0; nWinNum<nWinAnz; nWinNum++) {
//STRIP001      OutputDevice* pOut=GetWin(nWinNum);
//STRIP001      if (pOut->GetOutDevType()==OUTDEV_WINDOW) {
//STRIP001          pXOut->SetOutDev(pOut);
//STRIP001          for (USHORT nPvNum=0; nPvNum<nPvAnz; nPvNum++) {
//STRIP001              const SdrPageView* pPV=GetPageViewPvNum(nPvNum);
//STRIP001              const SdrObjList* pOL=pPV->GetObjList();
//STRIP001              pXOut->SetOffset(pPV->GetOffset());
//STRIP001              ULONG nObjAnz=pOL->GetObjCount();
//STRIP001              for (ULONG nObjNum=0; nObjNum<nObjAnz; nObjNum++) {
//STRIP001                  const SdrObject* pObj=pOL->GetObj(nObjNum);
//STRIP001                  const SdrGluePointList* pGPL=pObj->GetGluePointList();
//STRIP001                  if (pGPL!=NULL && pGPL->GetCount()!=0) {
//STRIP001                      pGPL->Invalidate(*(Window*)pOut,pObj);
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      pXOut->SetOffset(Point(0,0));
//STRIP001  }
/*N*/ }

/*N*/ void SdrPaintView::InvalidateAllWin()
/*N*/ {
/*N*/   for (USHORT i=0; i<GetWinCount(); i++) {
/*N*/       OutputDevice* pOut=GetWin(i);
/*N*/       if (pOut->GetOutDevType()==OUTDEV_WINDOW) {
/*N*/           InvalidateOneWin(*(Window*)pOut);
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void SdrPaintView::InvalidateAllWin(const Rectangle& rRect, BOOL bPlus1Pix)
/*N*/ {
/*N*/   USHORT nWinAnz=GetWinCount();
/*N*/   for (USHORT i=0; i<nWinAnz; i++) {
/*N*/       OutputDevice* pOut=GetWin(i);
/*N*/       if (pOut->GetOutDevType()==OUTDEV_WINDOW) {
/*N*/           Rectangle aRect(rRect);
/*N*/           if (bPlus1Pix) {
/*N*/               Size aPixSiz(1,1);
/*N*/               Size aSiz(pOut->PixelToLogic(aPixSiz));
/*N*/               aRect.Left  ()-=aSiz.Width();
/*N*/               aRect.Top   ()-=aSiz.Height();
/*N*/               aRect.Right ()+=aSiz.Width();
/*N*/               aRect.Bottom()+=aSiz.Height();
/*N*/           }
/*N*/           Point aOrg(pOut->GetMapMode().GetOrigin());
/*N*/           aOrg.X()=-aOrg.X(); aOrg.Y()=-aOrg.Y();
/*N*/           Rectangle aOutRect(aOrg,pOut->GetOutputSize());
/*N*/           if (aRect.IsOver(aOutRect)) {
/*N*/               InvalidateOneWin(*(Window*)pOut,aRect);
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void SdrPaintView::InvalidateOneWin(Window& rWin)
/*N*/ {
/*N*/   rWin.Invalidate();
/*N*/ }

/*N*/ void SdrPaintView::InvalidateOneWin(Window& rWin, const Rectangle& rRect)
/*N*/ {
/*N*/   rWin.Invalidate(rRect);
/*N*/ }

//STRIP001 void SdrPaintView::LeaveOneGroup()
//STRIP001 {
//STRIP001  for (USHORT nv=0; nv<GetPageViewCount(); nv++) {
//STRIP001      SdrPageView* pPV=GetPageViewPvNum(nv);
//STRIP001      pPV->LeaveOneGroup();
//STRIP001  }
//STRIP001 }

/*N*/ void SdrPaintView::LeaveAllGroup()
/*N*/ {
/*N*/   for (USHORT nv=0; nv<GetPageViewCount(); nv++) {
/*N*/       SdrPageView* pPV=GetPageViewPvNum(nv);
/*N*/       pPV->LeaveAllGroup();
/*N*/   }
/*N*/ }

/*N*/ BOOL SdrPaintView::IsGroupEntered() const
/*N*/ {
/*N*/   BOOL bRet=FALSE;
/*N*/   USHORT nPVAnz=GetPageViewCount();
/*N*/   for (USHORT nv=0; nv<nPVAnz && !bRet; nv++) {
/*N*/       SdrPageView* pPV=GetPageViewPvNum(nv);
/*N*/       if (pPV->GetEnteredLevel()!=0) bRet=TRUE;
/*N*/   }
/*N*/   return bRet;
/*N*/ }

/*N*/ void SdrPaintView::SetMasterPagePaintCaching( BOOL bOn, ULONG nCacheMode )
/*N*/ {
/*N*/   bMasterBmp = bOn;
/*N*/
/*N*/   if( bOn )
/*N*/   {
/*N*/       if( SDR_MASTERPAGECACHE_DEFAULT == nCacheMode || SDR_MASTERPAGECACHE_NONE == nCacheMode )
/*N*/           nMasterCacheMode = SDR_MASTERPAGECACHE_FULL;
/*N*/       else
/*N*/           nMasterCacheMode = nCacheMode;
/*N*/
/*N*/       ReleaseMasterPagePaintCache();
/*N*/   }
/*N*/   else
/*N*/       nMasterCacheMode = SDR_MASTERPAGECACHE_NONE;
/*N*/ }

// z.B. rufen, wenn Obj der MPg geaendert
/*N*/ void SdrPaintView::ReleaseMasterPagePaintCache()
/*N*/ {
/*N*/   if (pMasterBmp!=NULL) {
/*?*/       delete pMasterBmp;
/*?*/       pMasterBmp=NULL;
/*N*/   }
/*N*/ }

//STRIP001 void SdrPaintView::SetNotPersistDefaultAttr(const SfxItemSet& rAttr, BOOL bReplaceAll)
//STRIP001 {
//STRIP001  // bReplaceAll hat hier keinerlei Wirkung
//STRIP001  BOOL bMeasure=ISA(SdrView) && ((SdrView*)this)->IsMeasureTool();
//STRIP001  const SfxPoolItem *pPoolItem=NULL;
//STRIP001  if (rAttr.GetItemState(SDRATTR_LAYERID,TRUE,&pPoolItem)==SFX_ITEM_SET) {
//STRIP001      SdrLayerID nLayerId=((const SdrLayerIdItem*)pPoolItem)->GetValue();
//STRIP001      const SdrLayer* pLayer=pMod->GetLayerAdmin().GetLayerPerID(nLayerId);
//STRIP001      if (pLayer!=NULL) {
//STRIP001          if (bMeasure) aMeasureLayer=pLayer->GetName();
//STRIP001          else aAktLayer=pLayer->GetName();
//STRIP001      }
//STRIP001  }
//STRIP001  if (rAttr.GetItemState(SDRATTR_LAYERNAME,TRUE,&pPoolItem)==SFX_ITEM_SET) {
//STRIP001      if (bMeasure) aMeasureLayer=((const SdrLayerNameItem*)pPoolItem)->GetValue();
//STRIP001      else aAktLayer=((const SdrLayerNameItem*)pPoolItem)->GetValue();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrPaintView::MergeNotPersistDefaultAttr(SfxItemSet& rAttr, BOOL bOnlyHardAttr) const
//STRIP001 {
//STRIP001  // bOnlyHardAttr hat hier keinerlei Wirkung
//STRIP001  BOOL bMeasure=ISA(SdrView) && ((SdrView*)this)->IsMeasureTool();
//STRIP001  const XubString& aNam=bMeasure?aMeasureLayer:aAktLayer;
//STRIP001  rAttr.Put(SdrLayerNameItem(aNam));
//STRIP001  SdrLayerID nLayer=pMod->GetLayerAdmin().GetLayerID(aNam,TRUE);
//STRIP001  if (nLayer!=SDRLAYER_NOTFOUND) {
//STRIP001      rAttr.Put(SdrLayerIdItem(nLayer));
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrPaintView::SetDefaultAttr(const SfxItemSet& rAttr, BOOL bReplaceAll)
//STRIP001 {
//STRIP001 #ifdef DBG_UTIL
//STRIP001  {
//STRIP001      BOOL bHasEEFeatureItems=FALSE;
//STRIP001      SfxItemIter aIter(rAttr);
//STRIP001      const SfxPoolItem* pItem=aIter.FirstItem();
//STRIP001      while (!bHasEEFeatureItems && pItem!=NULL) {
//STRIP001          if (!IsInvalidItem(pItem)) {
//STRIP001              USHORT nW=pItem->Which();
//STRIP001              if (nW>=EE_FEATURE_START && nW<=EE_FEATURE_END) bHasEEFeatureItems=TRUE;
//STRIP001          }
//STRIP001          pItem=aIter.NextItem();
//STRIP001      }
//STRIP001
//STRIP001      if(bHasEEFeatureItems)
//STRIP001      {
//STRIP001          String aMessage;
//STRIP001          aMessage.AppendAscii("SdrPaintView::SetDefaultAttr(): Das setzen von EE_FEATURE-Items an der SdrView macht keinen Sinn! Es fuehrt nur zu Overhead und nicht mehr lesbaren Dokumenten.");
//STRIP001          InfoBox(NULL, aMessage).Execute();
//STRIP001      }
//STRIP001  }
//STRIP001 #endif
//STRIP001  if (bReplaceAll) aDefaultAttr.Set(rAttr);
//STRIP001  else aDefaultAttr.Put(rAttr,FALSE); // FALSE= InvalidItems nicht als Default, sondern als "Loecher" betrachten
//STRIP001  SetNotPersistDefaultAttr(rAttr,bReplaceAll);
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  if (pItemBrowser!=NULL) pItemBrowser->SetDirty();
//STRIP001 #endif
//STRIP001 }

/*N*/ void SdrPaintView::SetDefaultStyleSheet(SfxStyleSheet* pStyleSheet, BOOL bDontRemoveHardAttr)
/*N*/ {
/*N*/   pDefaultStyleSheet=pStyleSheet;
/*N*/   if (pStyleSheet!=NULL && !bDontRemoveHardAttr) {
/*?*/       SfxWhichIter aIter(pStyleSheet->GetItemSet());
/*?*/       USHORT nWhich=aIter.FirstWhich();
/*?*/       while (nWhich!=0) {
/*?*/           if (pStyleSheet->GetItemSet().GetItemState(nWhich,TRUE)==SFX_ITEM_SET) {
/*?*/               aDefaultAttr.ClearItem(nWhich);
/*?*/           }
/*?*/           nWhich=aIter.NextWhich();
/*?*/       }
/*N*/   }
#ifndef SVX_LIGHT
/*N*/   if (pItemBrowser!=NULL) {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 pItemBrowser->SetDirty();
#endif
/*N*/ }

/* new interface src537 */
//STRIP001 BOOL SdrPaintView::GetAttributes(SfxItemSet& rTargetSet, BOOL bOnlyHardAttr) const
//STRIP001 {
//STRIP001  if(bOnlyHardAttr || !pDefaultStyleSheet)
//STRIP001  {
//STRIP001      rTargetSet.Put(aDefaultAttr, FALSE);
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // sonst DefStyleSheet dazumergen
//STRIP001      rTargetSet.Put(pDefaultStyleSheet->GetItemSet(), FALSE);
//STRIP001      rTargetSet.Put(aDefaultAttr, FALSE);
//STRIP001  }
//STRIP001  MergeNotPersistDefaultAttr(rTargetSet, bOnlyHardAttr);
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL SdrPaintView::SetAttributes(const SfxItemSet& rSet, BOOL bReplaceAll)
//STRIP001 {
//STRIP001  SetDefaultAttr(rSet,bReplaceAll);
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 SfxStyleSheet* SdrPaintView::GetStyleSheet(BOOL& rOk) const
//STRIP001 {
//STRIP001  rOk=TRUE;
//STRIP001  return GetDefaultStyleSheet();
//STRIP001 }

/*N*/ BOOL SdrPaintView::SetStyleSheet(SfxStyleSheet* pStyleSheet, BOOL bDontRemoveHardAttr)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  SetDefaultStyleSheet(pStyleSheet,bDontRemoveHardAttr);
//STRIP001  return TRUE;
/*N*/ }

//STRIP001 void SdrPaintView::SetDisabledAttr(const SfxItemSet* pNewDisabledAttr)
//STRIP001 {
//STRIP001  if (pDisabledAttr!=NULL || pNewDisabledAttr!=NULL) {
//STRIP001      if (pDisabledAttr!=NULL) delete pDisabledAttr;
//STRIP001      pDisabledAttr=NULL;
//STRIP001      if (pNewDisabledAttr!=NULL) {
//STRIP001          pDisabledAttr=new SfxItemSet(*pNewDisabledAttr);
//STRIP001      }
//STRIP001      for (USHORT nv=0; nv<GetPageViewCount(); nv++) {
//STRIP001          SdrPageView* pPV=GetPageViewPvNum(nv);
//STRIP001          if (pPV->GetEnteredLevel()!=0) {
//STRIP001              InvalidateAllWin(pPV->GetPageRect());
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrPaintView::ShowItemBrowser(BOOL bShow)
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  if (bShow) {
//STRIP001      if (pItemBrowser==NULL) {
//STRIP001          pItemBrowser=new SdrItemBrowser(*(SdrView*)this);
//STRIP001          pItemBrowser->SetFloatingMode(TRUE);
//STRIP001      }
//STRIP001      pItemBrowser->Show();
//STRIP001      pItemBrowser->GrabFocus();
//STRIP001  } else {
//STRIP001      if (pItemBrowser!=NULL) {
//STRIP001          pItemBrowser->Hide();
//STRIP001          delete pItemBrowser;
//STRIP001          pItemBrowser=NULL;
//STRIP001      }
//STRIP001  }
//STRIP001 #endif
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrPaintView::WriteRecords(SvStream& rOut) const
/*N*/ {
/*N*/   {
/*N*/       SdrNamedSubRecord aSubRecord(rOut,STREAM_WRITE,SdrInventor,SDRIORECNAME_VIEWPAGEVIEWS);
/*N*/       USHORT nv;
/*N*/       for (nv=0; nv<GetPageViewCount(); nv++) {
/*N*/           SdrPageView* pPV=GetPageViewPvNum(nv);
/*N*/           if (pPV->GetPage()->IsInserted()) {
/*?*/               rOut<<*pPV;
/*N*/           }
/*N*/       }
/*N*/       for (nv=0; nv<GetPageHideCount(); nv++) {
/*?*/           SdrPageView* pPV=GetPageHidePvNum(nv);
/*?*/           if (pPV->GetPage()->IsInserted()) {
/*?*/               rOut<<*pPV;
/*N*/           }
/*N*/       }
/*N*/   } {
/*N*/       SdrNamedSubRecord aSubRecord(rOut,STREAM_WRITE,SdrInventor,SDRIORECNAME_VIEWVISIELEM);
/*N*/       rOut<<BOOL(bLayerSortedRedraw);
/*N*/       rOut<<BOOL(bPageVisible);
/*N*/       rOut<<BOOL(bBordVisible);
/*N*/       rOut<<BOOL(bGridVisible);
/*N*/       rOut<<BOOL(bGridFront);
/*N*/       rOut<<BOOL(bHlplVisible);
/*N*/       rOut<<BOOL(bHlplFront);
/*N*/       rOut<<BOOL(bGlueVisible);
/*N*/       rOut<<aGridBig;
/*N*/       rOut<<aGridFin;
/*N*/       rOut<<aGridWdtX;
/*N*/       rOut<<aGridWdtY;
/*N*/       rOut<<aGridSubdiv;
/*N*/   } {
/*N*/       SdrNamedSubRecord aSubRecord(rOut,STREAM_WRITE,SdrInventor,SDRIORECNAME_VIEWAKTLAYER);
/*N*/
/*N*/       // UNICODE: rOut << aAktLayer;
/*N*/       rOut.WriteByteString(aAktLayer);
/*N*/
/*N*/       // UNICODE: rOut << aMeasureLayer;
/*N*/       rOut.WriteByteString(aMeasureLayer);
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ BOOL SdrPaintView::ReadRecord(const SdrIOHeader& rViewHead,
/*N*/   const SdrNamedSubRecord& rSubHead,
/*N*/   SvStream& rIn)
/*N*/ {
/*N*/   BOOL bRet=FALSE;
/*N*/   if (rSubHead.GetInventor()==SdrInventor) {
/*N*/       bRet=TRUE;
/*N*/       switch (rSubHead.GetIdentifier()) {
/*N*/           case SDRIORECNAME_VIEWPAGEVIEWS: {
/*N*/               while (rSubHead.GetBytesLeft()>0 && rIn.GetError()==0 && !rIn.IsEof()) {
/*N*/                   SdrPageView* pPV=new SdrPageView(NULL,Point(),*(SdrView*)this);
/*N*/                   rIn>>*pPV;
/*N*/                   if (pPV->GetPage()!=NULL) {
/*N*/                       if (pPV->IsVisible()) {
/*N*/                           aPagV.Insert(pPV,CONTAINER_APPEND);
/*N*/                       } else aPagHide.Insert(pPV,CONTAINER_APPEND);
/*N*/                   } else {
/*N*/                       DBG_ERROR("SdrPaintView::ReadRecord(): Seite der PageView nicht gefunden");
/*N*/                       delete pPV;
/*N*/                   }
/*N*/               }
/*N*/           } break;
/*N*/
/*N*/           case SDRIORECNAME_VIEWVISIELEM:
/*N*/           {
/*N*/               BOOL bTemp;
/*N*/
/*N*/               rIn>>bTemp; bLayerSortedRedraw=bTemp;
/*N*/               rIn>>bTemp; bPageVisible      =bTemp;
/*N*/               rIn>>bTemp; bBordVisible      =bTemp;
/*N*/               rIn>>bTemp; bGridVisible      =bTemp;
/*N*/               rIn>>bTemp; bGridFront        =bTemp;
/*N*/               rIn>>bTemp; bHlplVisible      =bTemp;
/*N*/               rIn>>bTemp; bHlplFront        =bTemp;
/*N*/               rIn>>bTemp; bGlueVisible      =bTemp;
/*N*/               rIn>>aGridBig;
/*N*/               rIn>>aGridFin;
/*N*/
/*N*/               if(rSubHead.GetBytesLeft() > 0)
/*N*/               {
/*N*/                   rIn >> aGridWdtX;
/*N*/                   rIn >> aGridWdtY;
/*N*/                   rIn >> aGridSubdiv;
/*N*/               }
/*N*/               break;
/*N*/           }
/*N*/           case SDRIORECNAME_VIEWAKTLAYER:
/*N*/           {
/*N*/               // UNICODE: rIn >> aAktLayer;
/*N*/               rIn.ReadByteString(aAktLayer);
/*N*/
/*N*/               if(rSubHead.GetBytesLeft() > 0)
/*N*/               {
/*N*/                   // UNICODE: rIn >> aMeasureLayer;
/*N*/                   rIn.ReadByteString(aMeasureLayer);
/*N*/               }
/*N*/               break;
/*N*/           }
/*N*/
/*N*/           default:
/*N*/               bRet = FALSE;
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }

//STRIP001 void SdrPaintView::MakeVisible(const Rectangle& rRect, Window& rWin)
//STRIP001 {
//STRIP001  MapMode aMap(rWin.GetMapMode());
//STRIP001  Size aActualSize(rWin.GetOutputSize());
//STRIP001
//STRIP001  if( aActualSize.Height() > 0 && aActualSize.Width() > 0 )
//STRIP001  {
//STRIP001      Size aNewSize(rRect.GetSize());
//STRIP001      BOOL bNewScale=FALSE;
//STRIP001      BOOL bNeedMoreX=aNewSize.Width()>aActualSize.Width();
//STRIP001      BOOL bNeedMoreY=aNewSize.Height()>aActualSize.Height();
//STRIP001      if (bNeedMoreX || bNeedMoreY)
//STRIP001      {
//STRIP001          bNewScale=TRUE;
//STRIP001          // Neuen MapMode (Size+Org) setzen und dabei alles invalidieren
//STRIP001          Fraction aXFact(aNewSize.Width(),aActualSize.Width());
//STRIP001          Fraction aYFact(aNewSize.Height(),aActualSize.Height());
//STRIP001          if (aYFact>aXFact) aXFact=aYFact;
//STRIP001          aXFact*=aMap.GetScaleX();
//STRIP001          aXFact.ReduceInaccurate(10); // Um Ueberlaeufe und BigInt-Mapping zu vermeiden
//STRIP001          aMap.SetScaleX(aXFact);
//STRIP001          aMap.SetScaleY(aYFact);
//STRIP001          rWin.SetMapMode(aMap);
//STRIP001          aActualSize=rWin.GetOutputSize();
//STRIP001      }
//STRIP001      Point aOrg(aMap.GetOrigin());
//STRIP001      long dx=0,dy=0;
//STRIP001      long l=-aOrg.X();
//STRIP001      long r=-aOrg.X()+aActualSize.Width()-1;
//STRIP001      long o=-aOrg.Y();
//STRIP001      long u=-aOrg.Y()+aActualSize.Height()-1;
//STRIP001      if (l>rRect.Left()) dx=rRect.Left()-l;
//STRIP001      else if (r<rRect.Right()) dx=rRect.Right()-r;
//STRIP001      if (o>rRect.Top()) dy=rRect.Top()-o;
//STRIP001      else if (u<rRect.Bottom()) dy=rRect.Bottom()-u;
//STRIP001      aMap.SetOrigin(Point(aOrg.X()-dx,aOrg.Y()-dy));
//STRIP001      if (!bNewScale) {
//STRIP001          if (dx!=0 || dy!=0) {
//STRIP001              BOOL bXor=IsShownXorVisible(&rWin);
//STRIP001              if (bXor) HideShownXor(&rWin);
//STRIP001              rWin.Scroll(-dx,-dy);
//STRIP001              rWin.SetMapMode(aMap);
//STRIP001              rWin.Update();
//STRIP001              if (bXor) ShowShownXor(&rWin);
//STRIP001          }
//STRIP001      } else {
//STRIP001          rWin.SetMapMode(aMap);
//STRIP001          InvalidateOneWin(rWin);
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrPaintView::DoConnect(SdrOle2Obj* pOleObj)
//STRIP001 {
//STRIP001 }

/*N*/ void SdrPaintView::VisAreaChanged(const OutputDevice* pOut)
/*N*/ {
/*N*/   USHORT nCount = GetPageViewCount();
/*N*/
/*N*/   for (USHORT i = 0; i < nCount; i++)
/*N*/   {
/*N*/       SdrPageView* pPV = GetPageViewPvNum(i);
/*N*/
/*N*/       if (pOut)
/*N*/       {
/*N*/           // Nur dieses eine OutDev
/*N*/           USHORT nPos = pPV->GetWinList().Find((OutputDevice*) pOut);
/*N*/
/*N*/           if (nPos != SDRPAGEVIEWWIN_NOTFOUND)
/*N*/           {
/*N*/               VisAreaChanged(pPV->GetWinList()[nPos]);
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           // Alle OutDevs
/*N*/           USHORT nWinAnz = pPV->GetWinList().GetCount();
/*N*/
/*N*/           for (USHORT nWinNum = 0; nWinNum < nWinAnz; nWinNum++)
/*N*/           {
/*N*/               VisAreaChanged(pPV->GetWinList()[nWinNum]);
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void SdrPaintView::VisAreaChanged(const SdrPageViewWinRec& rPVWR)
/*N*/ {
/*N*/     // notify SfxListener
/*N*/     Broadcast( SvxViewHint(SVX_HINT_VIEWCHANGED) );
/*N*/
/*N*/     // notify UNO objects
/*N*/   if (rPVWR.GetControlContainerRef().is())
/*N*/   {
/*N*/       const SdrUnoControlList& rCList = rPVWR.GetControlList();
/*N*/
/*N*/       for (ULONG i = 0; i < rCList.GetCount(); i++)
/*N*/       {
/*N*/           const SdrUnoControlRec& rControlRec = rCList[ (sal_uInt16) i];
/*N*/           uno::Reference< awt::XControl > xUnoControl = rControlRec.GetControl();
/*N*/
/*N*/           if (xUnoControl.is())
/*N*/           {
/*N*/               uno::Reference< awt::XWindow > xVclComponent( xUnoControl, uno::UNO_QUERY );
/*N*/
/*N*/               if (xVclComponent.is() && rControlRec.GetUnoObj())
/*N*/               {
/*N*/                   Rectangle aRect = rControlRec.GetUnoObj()->GetLogicRect();
/*N*/                   OutputDevice* pOut = rPVWR.GetOutputDevice();
/*N*/                   Point aPixPos(pOut->LogicToPixel(aRect.TopLeft()));
/*N*/                   Size aPixSize(pOut->LogicToPixel(aRect.GetSize()));
/*N*/
/*N*/                   xVclComponent->setPosSize(aPixPos.X(), aPixPos.Y(),
/*N*/                       aPixSize.Width(), aPixSize.Height(), awt::PosSize::POSSIZE);
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }


//STRIP001 const svtools::ColorConfig& SdrPaintView::getColorConfig() const
//STRIP001 {
//STRIP001  return maColorConfig;
//STRIP001 }

/*N*/ void SdrPaintView::onChangeColorConfig()
/*N*/ {
/*N*/     SetGridColor( Color( maColorConfig.GetColorValue( svtools::DRAWGRID ).nColor ) );
/*N*/ }

/*N*/ void SdrPaintView::SetGridColor( Color aColor )
/*N*/ {
/*N*/   maGridColor = aColor;
/*N*/ }

//STRIP001 Color SdrPaintView::GetGridColor() const
//STRIP001 {
//STRIP001  return maGridColor;
//STRIP001 }

// #103834# Set background color for svx at SdrPageViews
//STRIP001 void SdrPaintView::SetApplicationBackgroundColor(Color aBackgroundColor)
//STRIP001 {
//STRIP001  for(sal_uInt16 a(0); a < GetPageViewCount(); a++)
//STRIP001  {
//STRIP001      SdrPageView* pPageView = GetPageViewPvNum(a);
//STRIP001      pPageView->SetApplicationBackgroundColor(aBackgroundColor);
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001 // #103911# Set document color for svx at SdrPageViews
//STRIP001 void SdrPaintView::SetApplicationDocumentColor(Color aDocumentColor)
//STRIP001 {
//STRIP001  for(sal_uInt16 a(0); a < GetPageViewCount(); a++)
//STRIP001  {
//STRIP001      SdrPageView* pPageView = GetPageViewPvNum(a);
//STRIP001      pPageView->SetApplicationDocumentColor(aDocumentColor);
//STRIP001  }
//STRIP001 }
//STRIP001
//STRIP001 // declaration extracted from svdedxv.cxx
//STRIP001 #define SPOTCOUNT    5
//STRIP001
//STRIP001 Color SdrPaintView::CalcBackgroundColor( const Rectangle& rArea,
//STRIP001                                          const SetOfByte& rVisibleLayers,
//STRIP001                                          const SdrPage&   rCurrPage ) const
//STRIP001 {
//STRIP001     // code extracted from SdrObjEditView::ImpGetTextEditBackgroundColor
//STRIP001     svtools::ColorConfig aColorConfig;
//STRIP001     Color aBackground(aColorConfig.GetColorValue(svtools::DOCCOLOR).nColor);
//STRIP001
//STRIP001  // #98988# test if we are in High contrast mode; if yes, take
//STRIP001  // application background color
//STRIP001     // #10049# wrong, always use svtools::DOCCOLOR as default and use document settings if
//STRIP001  //         not hc mode
//STRIP001  const StyleSettings& rStyleSettings = Application::GetSettings().GetStyleSettings();
//STRIP001
//STRIP001  if(!rStyleSettings.GetHighContrastMode())
//STRIP001  {
//STRIP001         // Ok, dann eben die Page durchsuchen!
//STRIP001         Point aSpotPos[SPOTCOUNT];
//STRIP001         Color aSpotColor[SPOTCOUNT];
//STRIP001         ULONG nHeight( rArea.GetSize().Height() );
//STRIP001         ULONG nWidth( rArea.GetSize().Width() );
//STRIP001         ULONG nWidth14  = nWidth / 4;
//STRIP001         ULONG nHeight14 = nHeight / 4;
//STRIP001         ULONG nWidth34  = ( 3 * nWidth ) / 4;
//STRIP001         ULONG nHeight34 = ( 3 * nHeight ) / 4;
//STRIP001
//STRIP001         USHORT i;
//STRIP001         for ( i = 0; i < SPOTCOUNT; i++ )
//STRIP001         {
//STRIP001             // Es wird anhand von fuenf Spots die Farbe untersucht
//STRIP001             switch ( i )
//STRIP001             {
//STRIP001                 case 0 :
//STRIP001                 {
//STRIP001                     // Center-Spot
//STRIP001                     aSpotPos[i] = rArea.Center();
//STRIP001                 }
//STRIP001                 break;
//STRIP001
//STRIP001                 case 1 :
//STRIP001                 {
//STRIP001                     // TopLeft-Spot
//STRIP001                     aSpotPos[i] = rArea.TopLeft();
//STRIP001                     aSpotPos[i].X() += nWidth14;
//STRIP001                     aSpotPos[i].Y() += nHeight14;
//STRIP001                 }
//STRIP001                 break;
//STRIP001
//STRIP001                 case 2 :
//STRIP001                 {
//STRIP001                     // TopRight-Spot
//STRIP001                     aSpotPos[i] = rArea.TopLeft();
//STRIP001                     aSpotPos[i].X() += nWidth34;
//STRIP001                     aSpotPos[i].Y() += nHeight14;
//STRIP001                 }
//STRIP001                 break;
//STRIP001
//STRIP001                 case 3 :
//STRIP001                 {
//STRIP001                     // BottomLeft-Spot
//STRIP001                     aSpotPos[i] = rArea.TopLeft();
//STRIP001                     aSpotPos[i].X() += nWidth14;
//STRIP001                     aSpotPos[i].Y() += nHeight34;
//STRIP001                 }
//STRIP001                 break;
//STRIP001
//STRIP001                 case 4 :
//STRIP001                 {
//STRIP001                     // BottomRight-Spot
//STRIP001                     aSpotPos[i] = rArea.TopLeft();
//STRIP001                     aSpotPos[i].X() += nWidth34;
//STRIP001                     aSpotPos[i].Y() += nHeight34;
//STRIP001                 }
//STRIP001                 break;
//STRIP001
//STRIP001             }
//STRIP001
//STRIP001             aSpotColor[i] = Color( COL_WHITE );
//STRIP001             rCurrPage.GetFillColor(aSpotPos[i], rVisibleLayers, bLayerSortedRedraw, aSpotColor[i]);
//STRIP001         }
//STRIP001
//STRIP001         USHORT aMatch[SPOTCOUNT];
//STRIP001
//STRIP001         for ( i = 0; i < SPOTCOUNT; i++ )
//STRIP001         {
//STRIP001             // Wurden gleiche Spot-Farben gefuden?
//STRIP001             aMatch[i] = 0;
//STRIP001
//STRIP001             for ( USHORT j = 0; j < SPOTCOUNT; j++ )
//STRIP001             {
//STRIP001                 if( j != i )
//STRIP001                 {
//STRIP001                     if( aSpotColor[i] == aSpotColor[j] )
//STRIP001                     {
//STRIP001                         aMatch[i]++;
//STRIP001                     }
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         // Das hoechste Gewicht hat der Spot in der Mitte
//STRIP001         aBackground = aSpotColor[0];
//STRIP001
//STRIP001         for ( USHORT nMatchCount = SPOTCOUNT - 1; nMatchCount > 1; nMatchCount-- )
//STRIP001         {
//STRIP001             // Welche Spot-Farbe wurde am haeufigsten gefunden?
//STRIP001             for ( USHORT i = 0; i < SPOTCOUNT; i++ )
//STRIP001             {
//STRIP001                 if( aMatch[i] == nMatchCount )
//STRIP001                 {
//STRIP001                     aBackground = aSpotColor[i];
//STRIP001                     nMatchCount = 1;   // Abbruch auch der aeusseren for-Schleife
//STRIP001                     break;
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001  }
//STRIP001
//STRIP001     return aBackground;
//STRIP001 }

/*N*/ void SdrPaintView::ImpForceSwapOut()
/*N*/ {
/*N*/     // #110290# Force swap out all graphics on this page. There might be
/*N*/   // some left, since every graphic that has not received a Draw yet,
/*N*/     // but is swapped in, has its swapout handler disabled.
/*N*/     while( !maSwappedInGraphicsStack.empty() )
/*N*/     {
/*N*/         maSwappedInGraphicsStack.front()->ForceSwapOut();
/*N*/         maSwappedInGraphicsStack.pop_front();
/*N*/     }
/*N*/ }

// eof
}
