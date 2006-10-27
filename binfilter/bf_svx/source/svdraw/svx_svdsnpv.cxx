/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_svdsnpv.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 21:46:14 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#include "svdsnpv.hxx"
#include <math.h>

#include "svdio.hxx"
#include "svdpagv.hxx"
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@@@  @@  @@  @@@@  @@@@@   @@ @@ @@ @@@@@ @@   @@
// @@  @@ @@@ @@ @@  @@ @@  @@  @@ @@ @@ @@    @@   @@
// @@     @@@@@@ @@  @@ @@  @@  @@ @@ @@ @@    @@ @ @@
//  @@@@  @@@@@@ @@@@@@ @@@@@   @@@@@ @@ @@@@  @@@@@@@
//     @@ @@ @@@ @@  @@ @@       @@@  @@ @@    @@@@@@@
// @@  @@ @@  @@ @@  @@ @@       @@@  @@ @@    @@@ @@@
//  @@@@  @@  @@ @@  @@ @@        @   @@ @@@@@ @@   @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrSnapView::ClearVars()
/*N*/ {
/*N*/   nMagnSizPix=4;
/*N*/   bSnapEnab=TRUE;
/*N*/   bGridSnap=TRUE;
/*N*/   bSnapTo1Pix=TRUE;
/*N*/   bBordSnap=TRUE;
/*N*/   bHlplSnap=TRUE;
/*N*/   bOFrmSnap=TRUE;
/*N*/   bOPntSnap=FALSE;
/*N*/   bOConSnap=TRUE;
/*N*/   bMoveMFrmSnap=TRUE;
/*N*/   bMoveOFrmSnap=TRUE;
/*N*/   bMoveOPntSnap=TRUE;
/*N*/   bMoveOConSnap=TRUE;
/*N*/   bMoveSnapOnlyTopLeft=FALSE;
/*N*/   bSetPageOrg=FALSE;
/*N*/   bOrtho=FALSE;
/*N*/   bBigOrtho=TRUE;
/*N*/   nSnapAngle=1500;
/*N*/   bAngleSnapEnab=FALSE;
/*N*/   bMoveOnlyDragging=FALSE;
/*N*/   bSlantButShear=FALSE;
/*N*/   bCrookNoContortion=FALSE;
/*N*/   eCrookMode=SDRCROOK_ROTATE;
/*N*/   bHlplFixed=FALSE;
/*N*/   pDragHelpLinePV=NULL;
/*N*/   nDragHelpLineNum=0;
/*N*/   bDragHelpLine=FALSE;
/*N*/   bEliminatePolyPoints=FALSE;
/*N*/   nEliminatePolyPointLimitAngle=0;
/*N*/ }

/*N*/ SdrSnapView::SdrSnapView(SdrModel* pModel1, OutputDevice* pOut):
/*N*/   SdrPaintView(pModel1,pOut)
/*N*/ {
/*N*/   ClearVars();
/*N*/ }

/*?*/ SdrSnapView::SdrSnapView(SdrModel* pModel1, ExtOutputDevice* pXOut):
/*?*/   SdrPaintView(pModel1,pXOut)
/*?*/ {
/*?*/   ClearVars();
/*?*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ BOOL SdrSnapView::IsAction() const
/*N*/ {
/*N*/   return IsSetPageOrg() || IsDragHelpLine() || SdrPaintView::IsAction();
/*N*/ }




/*N*/ void SdrSnapView::BrkAction()
/*N*/ {
/*N*/   BrkSetPageOrg();
/*N*/   BrkDragHelpLine();
/*N*/   SdrPaintView::BrkAction();
/*N*/ }


/*N*/ void SdrSnapView::ToggleShownXor(OutputDevice* pOut, const Region* pRegion) const
/*N*/ {
/*N*/   SdrPaintView::ToggleShownXor(pOut,pRegion);
/*N*/   if (IsSetPageOrg()) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   }
/*N*/   if (IsDragHelpLine()) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   }
/*N*/ }

/*N*/ void SdrSnapView::SnapMove()
/*N*/ {
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////


#define NOT_SNAPPED 0x7FFFFFFF



////////////////////////////////////////////////////////////////////////////////////////////////////




/*N*/ void SdrSnapView::BrkSetPageOrg()
/*N*/ {
/*N*/   if (bSetPageOrg) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   }
/*N*/ }




////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ BOOL SdrSnapView::PickHelpLine(const Point& rPnt, short nTol, const OutputDevice& rOut, USHORT& rnHelpLineNum, SdrPageView*& rpPV) const
/*N*/ {
/*N*/   rpPV=NULL;
/*N*/   nTol=ImpGetHitTolLogic(nTol,&rOut);
/*N*/   for (USHORT nv=GetPageViewCount(); nv>0;) {
/*N*/       nv--;
/*N*/       SdrPageView* pPV=GetPageViewPvNum(nv);
/*N*/       Point aPnt(rPnt);
/*N*/       aPnt-=pPV->GetOffset();
/*N*/       USHORT nIndex=pPV->GetHelpLines().HitTest(aPnt,USHORT(nTol),rOut);
/*N*/       if (nIndex!=SDRHELPLINE_NOTFOUND) {
/*?*/           rpPV=pPV;
/*?*/           rnHelpLineNum=nIndex;
/*?*/           return TRUE;
/*N*/       }
/*N*/   }
/*N*/   return FALSE;
/*N*/ }






/*N*/ void SdrSnapView::BrkDragHelpLine()
/*N*/ {
/*N*/   if (bDragHelpLine) {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   }
/*N*/ }




////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrSnapView::WriteRecords(SvStream& rOut) const
/*N*/ {
/*N*/   SdrPaintView::WriteRecords(rOut);
/*N*/   {
/*N*/       SdrNamedSubRecord aSubRecord(rOut,STREAM_WRITE,SdrInventor,SDRIORECNAME_VIEWSNAP);
/*N*/       rOut<<aMagnSiz;
/*N*/       rOut<<aSnapSiz;
/*N*/
/*N*/       rOut << (BOOL)bSnapEnab;
/*N*/       rOut << (BOOL)bGridSnap;
/*N*/       rOut << (BOOL)bBordSnap;
/*N*/       rOut << (BOOL)bHlplSnap;
/*N*/       rOut << (BOOL)bOFrmSnap;
/*N*/       rOut << (BOOL)bOPntSnap;
/*N*/       rOut << (BOOL)bOConSnap;
/*N*/       rOut << (BOOL)bMoveMFrmSnap;
/*N*/       rOut << (BOOL)bMoveOFrmSnap;
/*N*/       rOut << (BOOL)bMoveOPntSnap;
/*N*/       rOut << (BOOL)bMoveOConSnap;
/*N*/       rOut << (BOOL)bHlplFixed;
/*N*/
/*N*/       rOut<<nMagnSizPix;
/*N*/
/*N*/       rOut << (BOOL)bSnapTo1Pix;
/*N*/       rOut << (BOOL)bMoveSnapOnlyTopLeft;
/*N*/
/*N*/       rOut<<aSnapWdtX;
/*N*/       rOut<<aSnapWdtY;
/*N*/   } {
/*N*/       SdrNamedSubRecord aSubRecord(rOut,STREAM_WRITE,SdrInventor,SDRIORECNAME_VIEWORTHO);
/*N*/
/*N*/       rOut << (BOOL)bOrtho;
/*N*/       rOut << (BOOL)bBigOrtho;
/*N*/
/*N*/       rOut<<nSnapAngle;
/*N*/
/*N*/       rOut << (BOOL)bAngleSnapEnab;
/*N*/       rOut << (BOOL)bMoveOnlyDragging;
/*N*/       rOut << (BOOL)bSlantButShear;
/*N*/       rOut << (BOOL)bCrookNoContortion;
/*N*/
/*N*/       rOut<<USHORT(eCrookMode);
/*N*/   }
/*N*/ }

/*N*/ BOOL SdrSnapView::ReadRecord(const SdrIOHeader& rViewHead,
/*N*/   const SdrNamedSubRecord& rSubHead,
/*N*/   SvStream& rIn)
/*N*/ {
/*N*/   BOOL bRet=FALSE;
/*N*/   if (rSubHead.GetInventor()==SdrInventor)
/*N*/   {
/*N*/       bRet=TRUE;
/*N*/       BOOL bZwi;
/*N*/
/*N*/       switch (rSubHead.GetIdentifier())
/*N*/       {
/*N*/           case SDRIORECNAME_VIEWSNAP:
/*N*/           {
/*N*/               rIn>>aMagnSiz;
/*N*/               rIn>>aSnapSiz;
/*N*/
/*N*/               rIn >> bZwi; bSnapEnab = bZwi;
/*N*/               rIn >> bZwi; bGridSnap = bZwi;
/*N*/               rIn >> bZwi; bBordSnap = bZwi;
/*N*/               rIn >> bZwi; bHlplSnap = bZwi;
/*N*/               rIn >> bZwi; bOFrmSnap = bZwi;
/*N*/               rIn >> bZwi; bOPntSnap = bZwi;
/*N*/               rIn >> bZwi; bOConSnap = bZwi;
/*N*/               rIn >> bZwi; bMoveMFrmSnap = bZwi;
/*N*/               rIn >> bZwi; bMoveOFrmSnap = bZwi;
/*N*/               rIn >> bZwi; bMoveOPntSnap = bZwi;
/*N*/               rIn >> bZwi; bMoveOConSnap = bZwi;
/*N*/
/*N*/               if (rSubHead.GetBytesLeft()>0)
/*N*/               {
/*N*/                   rIn >> bZwi; bHlplFixed = bZwi; // kam erst spaeter dazu
/*N*/               }
/*N*/               if (rSubHead.GetBytesLeft()>0)
/*N*/               {
/*N*/                   // kam erst spaeter dazu
/*N*/                   rIn>>nMagnSizPix;
/*N*/                   rIn >> bZwi; bSnapTo1Pix = bZwi;
/*N*/               }
/*N*/               if (rSubHead.GetBytesLeft()>0)
/*N*/               {
/*N*/                   // kam erst spaeter dazu
/*N*/                   rIn >> bZwi; bMoveSnapOnlyTopLeft = bZwi;
/*N*/               }
/*N*/               if (rSubHead.GetBytesLeft()>0)
/*N*/               {
/*N*/                   // kam erst spaeter dazu
/*N*/                   rIn>>aSnapWdtX;
/*N*/                   rIn>>aSnapWdtY;
/*N*/               }
/*N*/           } break;
/*N*/           case SDRIORECNAME_VIEWORTHO:
/*N*/           {
/*N*/               rIn >> bZwi; bOrtho = bZwi;
/*N*/               rIn >> bZwi; bBigOrtho = bZwi;
/*N*/
/*N*/               rIn>>nSnapAngle;
/*N*/
/*N*/               if (rSubHead.GetBytesLeft()>0)
/*N*/               {
/*N*/                   // kam erst spaeter dazu
/*N*/                   rIn >> bZwi; bAngleSnapEnab = bZwi;
/*N*/                   rIn >> bZwi; bMoveOnlyDragging = bZwi;
/*N*/                   rIn >> bZwi; bSlantButShear = bZwi;
/*N*/                   rIn >> bZwi; bCrookNoContortion = bZwi;
/*N*/               }
/*N*/               if (rSubHead.GetBytesLeft()>0)
/*N*/               {
/*N*/                   // kam erst spaeter dazu
/*N*/                   USHORT nCrookMode;
/*N*/                   rIn>>nCrookMode;
/*N*/                   eCrookMode=SdrCrookMode(nCrookMode);
/*N*/               }
/*N*/           } break;
/*N*/           default: bRet=FALSE;
/*N*/       }
/*N*/   }
/*N*/   if (!bRet) bRet=SdrPaintView::ReadRecord(rViewHead,rSubHead,rIn);
/*N*/   return bRet;
/*N*/ }

}
