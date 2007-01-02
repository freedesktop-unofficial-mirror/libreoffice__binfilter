/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_svdvmark.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 17:33:58 $
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

#include "svdvmark.hxx"
#include "svdobj.hxx"
#include "svdpntv.hxx"

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

/*N*/ void SdrViewUserMarker::SetLineWidth(USHORT nWdt)
/*N*/ {
/*N*/   FASTBOOL bVis=bVisible;
/*N*/   if (bVis) Hide();
/*N*/   nLineWdt=nWdt;
/*N*/   if (bVis) Show();
/*N*/ }

/*N*/ void SdrViewUserMarker::Show()
/*N*/ {DBG_BF_ASSERT(0, "STRIP");
/*N*/ }

/*N*/ void SdrViewUserMarker::Hide()
/*N*/ {DBG_BF_ASSERT(0, "STRIP");
/*N*/ }


}
