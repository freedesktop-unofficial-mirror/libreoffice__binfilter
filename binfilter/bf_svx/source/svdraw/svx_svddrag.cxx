/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_svddrag.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 21:36:53 $
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

#ifndef _SVDDRAG_HXX //autogen
#include "svddrag.hxx"
#endif
namespace binfilter {

/*N*/ void SdrDragStat::Clear(FASTBOOL bLeaveOne)
/*N*/ {
/*N*/   void* pP=aPnts.First();
/*N*/   while (pP!=NULL) {
/*N*/       delete (Point*)pP;
/*N*/       pP=aPnts.Next();
/*N*/   }
/*N*/   if (pUser!=NULL) delete pUser;
/*N*/   pUser=NULL;
/*N*/   aPnts.Clear();
/*N*/   if (bLeaveOne) {
/*N*/       aPnts.Insert(new Point,CONTAINER_APPEND);
/*N*/   }
/*N*/ }

/*N*/ void SdrDragStat::Reset()
/*N*/ {
/*N*/   pView=NULL;
/*N*/   pPageView=NULL;
/*N*/   bShown=FALSE;
/*N*/   nMinMov=1;
/*N*/   bMinMoved=FALSE;
/*N*/   bHorFixed=FALSE;
/*N*/   bVerFixed=FALSE;
/*N*/   bWantNoSnap=FALSE;
/*N*/   pHdl=NULL;
/*N*/   bOrtho4=FALSE;
/*N*/   bOrtho8=FALSE;
/*N*/   pDragMethod=NULL;
/*N*/   bEndDragChangesAttributes=FALSE;
/*N*/   bEndDragChangesGeoAndAttributes=FALSE;
/*N*/   bMouseIsUp=FALSE;
/*N*/   Clear(TRUE);
/*N*/   aActionRect=Rectangle();
/*N*/ }










}
