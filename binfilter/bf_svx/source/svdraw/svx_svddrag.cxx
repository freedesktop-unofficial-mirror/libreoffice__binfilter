/*************************************************************************
 *
 *  $RCSfile: svx_svddrag.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:46:08 $
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
#include "svdview.hxx"

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

//STRIP001 void SdrDragStat::Reset(const Point& rPnt)
//STRIP001 {
//STRIP001  Reset();
//STRIP001  Start()=rPnt;
//STRIP001  aPos0=rPnt;
//STRIP001  aRealPos0=rPnt;
//STRIP001  RealNow()=rPnt;
//STRIP001 }

//STRIP001 void SdrDragStat::NextMove(const Point& rPnt)
//STRIP001 {
//STRIP001  aRealPos0=GetRealNow();
//STRIP001  aPos0=GetNow();
//STRIP001  RealNow()=rPnt;
//STRIP001  Point aBla=KorregPos(GetRealNow(),GetPrev());
//STRIP001  Now()=aBla;
//STRIP001 }

//STRIP001 void SdrDragStat::NextPoint(FASTBOOL bSaveReal)
//STRIP001 {
//STRIP001  Point aPnt(GetNow());
//STRIP001  if (bSaveReal) aPnt=aRealNow;
//STRIP001  aPnts.Insert(new Point(KorregPos(GetRealNow(),aPnt)),CONTAINER_APPEND);
//STRIP001  Prev()=aPnt;
//STRIP001 }

//STRIP001 void SdrDragStat::PrevPoint()
//STRIP001 {
//STRIP001  if (aPnts.Count()>=2) { // einer muss immer da bleiben
//STRIP001      Point* pPnt=(Point*)(aPnts.GetObject(aPnts.Count()-2));
//STRIP001      aPnts.Remove(aPnts.Count()-2);
//STRIP001      delete pPnt;
//STRIP001      Now()=KorregPos(GetRealNow(),GetPrev());
//STRIP001  }
//STRIP001 }

//STRIP001 Point SdrDragStat::KorregPos(const Point& rNow, const Point& rPrev) const
//STRIP001 {
//STRIP001  Point aRet(rNow);
//STRIP001  return aRet;
//STRIP001 }

//STRIP001 FASTBOOL SdrDragStat::CheckMinMoved(const Point& rPnt)
//STRIP001 {
//STRIP001  if (!bMinMoved) {
//STRIP001      long dx=rPnt.X()-GetPrev().X(); if (dx<0) dx=-dx;
//STRIP001      long dy=rPnt.Y()-GetPrev().Y(); if (dy<0) dy=-dy;
//STRIP001      if (dx>=long(nMinMov) || dy>=long(nMinMov))
//STRIP001          bMinMoved=TRUE;
//STRIP001  }
//STRIP001  return bMinMoved;
//STRIP001 }

//STRIP001 Fraction SdrDragStat::GetXFact() const
//STRIP001 {
//STRIP001  long nMul=GetNow().X()-aRef1.X();
//STRIP001  long nDiv=GetPrev().X()-aRef1.X();
//STRIP001  if (nDiv==0) nDiv=1;
//STRIP001  if (bHorFixed) { nMul=1; nDiv=1; }
//STRIP001  return Fraction(nMul,nDiv);
//STRIP001 }

//STRIP001 Fraction SdrDragStat::GetYFact() const
//STRIP001 {
//STRIP001  long nMul=GetNow().Y()-aRef1.Y();
//STRIP001  long nDiv=GetPrev().Y()-aRef1.Y();
//STRIP001  if (nDiv==0) nDiv=1;
//STRIP001  if (bVerFixed) { nMul=1; nDiv=1; }
//STRIP001  return Fraction(nMul,nDiv);
//STRIP001 }

//STRIP001 void SdrDragStat::TakeCreateRect(Rectangle& rRect) const
//STRIP001 {
//STRIP001  rRect=Rectangle(GetStart(),GetNow());
//STRIP001  if (GetPointAnz()>=2) {
//STRIP001      Point aBtmRgt(GetPoint(1));
//STRIP001      rRect.Right()=aBtmRgt.X();
//STRIP001      rRect.Bottom()=aBtmRgt.Y();
//STRIP001  }
//STRIP001  if (pView!=NULL && pView->IsCreate1stPointAsCenter()) {
//STRIP001      rRect.Top()+=rRect.Top()-rRect.Bottom();
//STRIP001      rRect.Left()+=rRect.Left()-rRect.Right();
//STRIP001  }
//STRIP001 }

}
