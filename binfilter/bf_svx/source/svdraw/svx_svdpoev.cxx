/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_svdpoev.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 21:45:43 $
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

#include "svdpoev.hxx"
#include <math.h>
#include "svdopath.hxx"
#include "svdstr.hrc"   // Namen aus der Resource
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrPolyEditView::ImpResetPolyPossibilityFlags()
/*N*/ {
/*N*/   eMarkedPointsSmooth=SDRPATHSMOOTH_DONTCARE;
/*N*/   eMarkedSegmentsKind=SDRPATHSEGMENT_DONTCARE;
/*N*/   bSetMarkedPointsSmoothPossible=FALSE;
/*N*/   bSetMarkedSegmentsKindPossible=FALSE;
/*N*/ }

/*N*/ void SdrPolyEditView::ImpClearVars()
/*N*/ {
/*N*/   ImpResetPolyPossibilityFlags();
/*N*/ }

/*N*/ SdrPolyEditView::SdrPolyEditView(SdrModel* pModel1, OutputDevice* pOut):
/*N*/   SdrEditView(pModel1,pOut)
/*N*/ {
/*N*/   ImpClearVars();
/*N*/ }

/*?*/ SdrPolyEditView::SdrPolyEditView(SdrModel* pModel1, ExtOutputDevice* pXOut):
/*?*/   SdrEditView(pModel1,pXOut)
/*?*/ {
/*?*/   ImpClearVars();
/*?*/ }

/*N*/ SdrPolyEditView::~SdrPolyEditView()
/*N*/ {
/*N*/ }

/*N*/ void SdrPolyEditView::ImpCheckPolyPossibilities()
/*N*/ {
/*N*/   ImpResetPolyPossibilityFlags();
/*N*/   ULONG nMarkAnz=aMark.GetMarkCount();
/*N*/   if (nMarkAnz>0 && !ImpIsFrameHandles()) {
/*?*/       BOOL bReadOnly=FALSE;
/*?*/       BOOL b1stSmooth=TRUE;
/*?*/       BOOL b1stSegm=TRUE;
/*?*/       BOOL bCurve=FALSE;
/*?*/       BOOL bSmoothFuz=FALSE;
/*?*/       BOOL bSegmFuz=FALSE;
/*?*/       XPolyFlags eSmooth=XPOLY_NORMAL;
/*?*/
/*?*/       for (ULONG nMarkNum=0; nMarkNum<nMarkAnz; nMarkNum++) {
/*?*/           SdrMark* pM=aMark.GetMark(nMarkNum);
/*?*/           SdrObject* pObj=pM->GetObj();
/*?*/           SdrUShortCont* pPts=pM->GetMarkedPoints();
/*?*/           SdrPathObj* pPath=PTR_CAST(SdrPathObj,pObj);
/*?*/           if (pPath!=NULL && pPts!=NULL) {
/*?*/               ULONG nMarkedPntAnz=pPts->GetCount();
/*?*/               if (nMarkedPntAnz!=0) {
/*?*/                   BOOL bClosed=pPath->IsClosed();
/*?*/                   bSetMarkedPointsSmoothPossible=TRUE;
/*?*/                   if (bClosed) bSetMarkedSegmentsKindPossible=TRUE;
/*?*/                   const XPolyPolygon& rXPP=pPath->GetPathPoly();
/*?*/                   for (USHORT nMarkedPntNum=0; nMarkedPntNum<(USHORT)nMarkedPntAnz; nMarkedPntNum++) {
/*?*/                       USHORT nNum=pPts->GetObject(nMarkedPntNum);
/*?*/                       USHORT nPolyNum=0,nPntNum=0;
/*?*/                       if (pPath->FindPolyPnt(nNum,nPolyNum,nPntNum,FALSE)) {
/*?*/                           const XPolygon& rXP=rXPP[nPolyNum];
/*?*/                           BOOL bCanSegment=bClosed || nPntNum<rXP.GetPointCount()-1;
/*?*/
/*?*/                           if (!bSetMarkedSegmentsKindPossible && bCanSegment) {
/*?*/                               bSetMarkedSegmentsKindPossible=TRUE;
/*?*/                           }
/*?*/                           if (!bSmoothFuz) {
/*?*/                               if (b1stSmooth) {
/*?*/                                   b1stSmooth=FALSE;
/*?*/                                   eSmooth=rXP.GetFlags(nPntNum);
/*?*/                               } else {
/*?*/                                   bSmoothFuz=eSmooth!=rXP.GetFlags(nPntNum);
/*?*/                               }
/*?*/                           }
/*?*/                           if (!bSegmFuz) {
/*?*/                               if (bCanSegment) {
/*?*/                                   BOOL bCrv=rXP.IsControl(nPntNum+1);
/*?*/                                   if (b1stSegm) {
/*?*/                                       b1stSegm=FALSE;
/*?*/                                       bCurve=bCrv;
/*?*/                                   } else {
/*?*/                                       bSegmFuz=bCrv!=bCurve;
/*?*/                                   }
/*?*/                               }
/*?*/                           }
/*?*/                       }
/*?*/                   }
/*?*/                   if (!b1stSmooth && !bSmoothFuz) {
/*?*/                       if (eSmooth==XPOLY_NORMAL) eMarkedPointsSmooth=SDRPATHSMOOTH_ANGULAR;
/*?*/                       if (eSmooth==XPOLY_SMOOTH) eMarkedPointsSmooth=SDRPATHSMOOTH_ASYMMETRIC;
/*?*/                       if (eSmooth==XPOLY_SYMMTR) eMarkedPointsSmooth=SDRPATHSMOOTH_SYMMETRIC;
/*?*/                   }
/*?*/                   if (!b1stSegm && !bSegmFuz) {
/*?*/                       eMarkedSegmentsKind= bCurve ? SDRPATHSEGMENT_CURVE : SDRPATHSEGMENT_LINE;
/*?*/                   }
/*?*/               }
/*?*/           }
/*?*/       }
/*?*/       if (bReadOnly) {
/*?*/           bSetMarkedPointsSmoothPossible=FALSE;
/*?*/           bSetMarkedSegmentsKindPossible=FALSE;
/*?*/       }
/*N*/   }
/*N*/ }










////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////



}
