/*************************************************************************
 *
 *  $RCSfile: svx_svdglue.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:19 $
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

#ifndef _TOOLS_DEBUG_HXX //autogen
#include <tools/debug.hxx>
#endif

#include "svdglue.hxx"
#include "svdobj.hxx"
#include "svdio.hxx"
#include "svdtrans.hxx"

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrGluePoint::SetReallyAbsolute(FASTBOOL bOn, const SdrObject& rObj)
//STRIP001 {
//STRIP001  if (bReallyAbsolute!=bOn) {
//STRIP001     if (bOn) {
//STRIP001         aPos=GetAbsolutePos(rObj);
//STRIP001         bReallyAbsolute=bOn;
//STRIP001     } else {
//STRIP001         bReallyAbsolute=bOn;
//STRIP001         Point aPt(aPos);
//STRIP001         SetAbsolutePos(aPt,rObj);
//STRIP001     }
//STRIP001  } else {
//STRIP001      DBG_ASSERT(bOn,"SdrGluePoint::SetReallyAbsolute(FALSE) mehrfach gerufen");
//STRIP001      DBG_ASSERT(!bOn,"SdrGluePoint::SetReallyAbsolute(TRUE) mehrfach gerufen");
//STRIP001  }
//STRIP001 }

/*N*/ Point SdrGluePoint::GetAbsolutePos(const SdrObject& rObj) const
/*N*/ {
/*N*/   if (bReallyAbsolute) return aPos;
/*N*/   Rectangle aSnap(rObj.GetSnapRect());
/*N*/   Rectangle aBound(rObj.GetSnapRect());
/*N*/   Point aPt(aPos);
/*N*/
/*N*/   Point aOfs(aSnap.Center());
/*N*/   switch (GetHorzAlign()) {
/*?*/       case SDRHORZALIGN_LEFT  : aOfs.X()=aSnap.Left(); break;
/*?*/       case SDRHORZALIGN_RIGHT : aOfs.X()=aSnap.Right(); break;
/*N*/   }
/*N*/   switch (GetVertAlign()) {
/*?*/       case SDRVERTALIGN_TOP   : aOfs.Y()=aSnap.Top(); break;
/*?*/       case SDRVERTALIGN_BOTTOM: aOfs.Y()=aSnap.Bottom(); break;
/*N*/   }
/*N*/   if (!bNoPercent) {
/*?*/       long nXMul=aSnap.Right()-aSnap.Left();
/*?*/       long nYMul=aSnap.Bottom()-aSnap.Top();
/*?*/       long nXDiv=10000;
/*?*/       long nYDiv=10000;
/*?*/       if (nXMul!=nXDiv) {
/*?*/           aPt.X()*=nXMul;
/*?*/           aPt.X()/=nXDiv;
/*?*/       }
/*?*/       if (nYMul!=nYDiv) {
/*?*/           aPt.Y()*=nYMul;
/*?*/           aPt.Y()/=nYDiv;
/*?*/       }
/*N*/   }
/*N*/   aPt+=aOfs;
/*N*/   // Und nun auf's BoundRect des Objekts begrenzen
/*N*/   if (aPt.X()<aBound.Left  ()) aPt.X()=aBound.Left  ();
/*N*/   if (aPt.X()>aBound.Right ()) aPt.X()=aBound.Right ();
/*N*/   if (aPt.Y()<aBound.Top   ()) aPt.Y()=aBound.Top   ();
/*N*/   if (aPt.Y()>aBound.Bottom()) aPt.Y()=aBound.Bottom();
/*N*/   return aPt;
/*N*/ }

//STRIP001 void SdrGluePoint::SetAbsolutePos(const Point& rNewPos, const SdrObject& rObj)
//STRIP001 {
//STRIP001  if (bReallyAbsolute) {
//STRIP001      aPos=rNewPos;
//STRIP001      return;
//STRIP001  }
//STRIP001  Rectangle aSnap(rObj.GetSnapRect());
//STRIP001  Point aPt(rNewPos);
//STRIP001
//STRIP001  Point aOfs(aSnap.Center());
//STRIP001  switch (GetHorzAlign()) {
//STRIP001      case SDRHORZALIGN_LEFT  : aOfs.X()=aSnap.Left(); break;
//STRIP001      case SDRHORZALIGN_RIGHT : aOfs.X()=aSnap.Right(); break;
//STRIP001  }
//STRIP001  switch (GetVertAlign()) {
//STRIP001      case SDRVERTALIGN_TOP   : aOfs.Y()=aSnap.Top(); break;
//STRIP001      case SDRVERTALIGN_BOTTOM: aOfs.Y()=aSnap.Bottom(); break;
//STRIP001  }
//STRIP001  aPt-=aOfs;
//STRIP001  if (!bNoPercent) {
//STRIP001      long nXMul=aSnap.Right()-aSnap.Left();
//STRIP001      long nYMul=aSnap.Bottom()-aSnap.Top();
//STRIP001      if (nXMul==0) nXMul=1;
//STRIP001      if (nYMul==0) nYMul=1;
//STRIP001      long nXDiv=10000;
//STRIP001      long nYDiv=10000;
//STRIP001      if (nXMul!=nXDiv) {
//STRIP001          aPt.X()*=nXDiv;
//STRIP001          aPt.X()/=nXMul;
//STRIP001      }
//STRIP001      if (nYMul!=nYDiv) {
//STRIP001          aPt.Y()*=nYDiv;
//STRIP001          aPt.Y()/=nYMul;
//STRIP001      }
//STRIP001  }
//STRIP001  aPos=aPt;
//STRIP001 }

//STRIP001 long SdrGluePoint::GetAlignAngle() const
//STRIP001 {
//STRIP001  switch (nAlign) {
//STRIP001      case SDRHORZALIGN_CENTER|SDRVERTALIGN_CENTER: return 0; // Invalid!
//STRIP001      case SDRHORZALIGN_RIGHT |SDRVERTALIGN_CENTER: return 0;
//STRIP001      case SDRHORZALIGN_RIGHT |SDRVERTALIGN_TOP   : return 4500;
//STRIP001      case SDRHORZALIGN_CENTER|SDRVERTALIGN_TOP   : return 9000;
//STRIP001      case SDRHORZALIGN_LEFT  |SDRVERTALIGN_TOP   : return 13500;
//STRIP001      case SDRHORZALIGN_LEFT  |SDRVERTALIGN_CENTER: return 18000;
//STRIP001      case SDRHORZALIGN_LEFT  |SDRVERTALIGN_BOTTOM: return 22500;
//STRIP001      case SDRHORZALIGN_CENTER|SDRVERTALIGN_BOTTOM: return 27000;
//STRIP001      case SDRHORZALIGN_RIGHT |SDRVERTALIGN_BOTTOM: return 31500;
//STRIP001  } // switch
//STRIP001  return 0;
//STRIP001 }

//STRIP001 void SdrGluePoint::SetAlignAngle(long nWink)
//STRIP001 {
//STRIP001  nWink=NormAngle360(nWink);
//STRIP001  if (nWink>=33750 || nWink<2250) nAlign=SDRHORZALIGN_RIGHT |SDRVERTALIGN_CENTER;
//STRIP001  else if (nWink< 6750) nAlign=SDRHORZALIGN_RIGHT |SDRVERTALIGN_TOP   ;
//STRIP001  else if (nWink<11250) nAlign=SDRHORZALIGN_CENTER|SDRVERTALIGN_TOP   ;
//STRIP001  else if (nWink<15750) nAlign=SDRHORZALIGN_LEFT  |SDRVERTALIGN_TOP   ;
//STRIP001  else if (nWink<20250) nAlign=SDRHORZALIGN_LEFT  |SDRVERTALIGN_CENTER;
//STRIP001  else if (nWink<24750) nAlign=SDRHORZALIGN_LEFT  |SDRVERTALIGN_BOTTOM;
//STRIP001  else if (nWink<29250) nAlign=SDRHORZALIGN_CENTER|SDRVERTALIGN_BOTTOM;
//STRIP001  else if (nWink<33750) nAlign=SDRHORZALIGN_RIGHT |SDRVERTALIGN_BOTTOM;
//STRIP001 }

//STRIP001 long SdrGluePoint::EscDirToAngle(USHORT nEsc) const
//STRIP001 {
//STRIP001  switch (nEsc) {
//STRIP001      case SDRESC_RIGHT : return 0;
//STRIP001      case SDRESC_TOP   : return 9000;
//STRIP001      case SDRESC_LEFT  : return 18000;
//STRIP001      case SDRESC_BOTTOM: return 27000;
//STRIP001  } // switch
//STRIP001  return 0;
//STRIP001 }

//STRIP001 USHORT SdrGluePoint::EscAngleToDir(long nWink) const
//STRIP001 {
//STRIP001  nWink=NormAngle360(nWink);
//STRIP001  if (nWink>=31500 || nWink<4500) return SDRESC_RIGHT;
//STRIP001  if (nWink<13500) return SDRESC_TOP;
//STRIP001  if (nWink<22500) return SDRESC_LEFT;
//STRIP001  if (nWink<31500) return SDRESC_BOTTOM;
//STRIP001  return 0;
//STRIP001 }

//STRIP001 void SdrGluePoint::Rotate(const Point& rRef, long nWink, double sn, double cs, const SdrObject* pObj)
//STRIP001 {
//STRIP001  Point aPt(pObj!=NULL ? GetAbsolutePos(*pObj) : GetPos());
//STRIP001  RotatePoint(aPt,rRef,sn,cs);
//STRIP001  // Bezugskante drehen
//STRIP001  if(nAlign != (SDRHORZALIGN_CENTER|SDRVERTALIGN_CENTER))
//STRIP001  {
//STRIP001      SetAlignAngle(GetAlignAngle()+nWink);
//STRIP001  }
//STRIP001  // Austrittsrichtungen drehen
//STRIP001  USHORT nEscDir0=nEscDir;
//STRIP001  USHORT nEscDir1=0;
//STRIP001  if ((nEscDir0&SDRESC_LEFT  )!=0) nEscDir1|=EscAngleToDir(EscDirToAngle(SDRESC_LEFT  )+nWink);
//STRIP001  if ((nEscDir0&SDRESC_TOP   )!=0) nEscDir1|=EscAngleToDir(EscDirToAngle(SDRESC_TOP   )+nWink);
//STRIP001  if ((nEscDir0&SDRESC_RIGHT )!=0) nEscDir1|=EscAngleToDir(EscDirToAngle(SDRESC_RIGHT )+nWink);
//STRIP001  if ((nEscDir0&SDRESC_BOTTOM)!=0) nEscDir1|=EscAngleToDir(EscDirToAngle(SDRESC_BOTTOM)+nWink);
//STRIP001  nEscDir=nEscDir1;
//STRIP001  if (pObj!=NULL) SetAbsolutePos(aPt,*pObj); else SetPos(aPt);
//STRIP001 }

//STRIP001 void SdrGluePoint::Mirror(const Point& rRef1, const Point& rRef2, const SdrObject* pObj)
//STRIP001 {
//STRIP001  Point aPt(rRef2); aPt-=rRef1;
//STRIP001  long nWink=GetAngle(aPt);
//STRIP001  Mirror(rRef1,rRef2,nWink,pObj);
//STRIP001 }

//STRIP001 void SdrGluePoint::Mirror(const Point& rRef1, const Point& rRef2, long nWink, const SdrObject* pObj)
//STRIP001 {
//STRIP001  Point aPt(pObj!=NULL ? GetAbsolutePos(*pObj) : GetPos());
//STRIP001  MirrorPoint(aPt,rRef1,rRef2);
//STRIP001  // Bezugskante spiegeln
//STRIP001  if(nAlign != (SDRHORZALIGN_CENTER|SDRVERTALIGN_CENTER))
//STRIP001  {
//STRIP001      long nAW=GetAlignAngle();
//STRIP001      nAW+=2*(nWink-nAW);
//STRIP001      SetAlignAngle(nAW);
//STRIP001  }
//STRIP001  // Austrittsrichtungen spiegeln
//STRIP001  USHORT nEscDir0=nEscDir;
//STRIP001  USHORT nEscDir1=0;
//STRIP001  if ((nEscDir0&SDRESC_LEFT)!=0) {
//STRIP001      long nEW=EscDirToAngle(SDRESC_LEFT);
//STRIP001      nEW+=2*(nWink-nEW);
//STRIP001      nEscDir1|=EscAngleToDir(nEW);
//STRIP001  }
//STRIP001  if ((nEscDir0&SDRESC_TOP)!=0) {
//STRIP001      long nEW=EscDirToAngle(SDRESC_TOP);
//STRIP001      nEW+=2*(nWink-nEW);
//STRIP001      nEscDir1|=EscAngleToDir(nEW);
//STRIP001  }
//STRIP001  if ((nEscDir0&SDRESC_RIGHT)!=0) {
//STRIP001      long nEW=EscDirToAngle(SDRESC_RIGHT);
//STRIP001      nEW+=2*(nWink-nEW);
//STRIP001      nEscDir1|=EscAngleToDir(nEW);
//STRIP001  }
//STRIP001  if ((nEscDir0&SDRESC_BOTTOM)!=0) {
//STRIP001      long nEW=EscDirToAngle(SDRESC_BOTTOM);
//STRIP001      nEW+=2*(nWink-nEW);
//STRIP001      nEscDir1|=EscAngleToDir(nEW);
//STRIP001  }
//STRIP001  nEscDir=nEscDir1;
//STRIP001  if (pObj!=NULL) SetAbsolutePos(aPt,*pObj); else SetPos(aPt);
//STRIP001 }

//STRIP001 void SdrGluePoint::Shear(const Point& rRef, long nWink, double tn, FASTBOOL bVShear, const SdrObject* pObj)
//STRIP001 {
//STRIP001  Point aPt(pObj!=NULL ? GetAbsolutePos(*pObj) : GetPos());
//STRIP001  ShearPoint(aPt,rRef,tn,bVShear);
//STRIP001  if (pObj!=NULL) SetAbsolutePos(aPt,*pObj); else SetPos(aPt);
//STRIP001 }

//STRIP001 void SdrGluePoint::Draw(OutputDevice& rOut, const SdrObject* pObj) const
//STRIP001 {
//STRIP001  Color aBackPenColor(COL_WHITE);
//STRIP001  Color aForePenColor(COL_LIGHTBLUE);
//STRIP001
//STRIP001  FASTBOOL bMapMerk=rOut.IsMapModeEnabled();
//STRIP001  Point aPt(pObj!=NULL ? GetAbsolutePos(*pObj) : GetPos());
//STRIP001  aPt=rOut.LogicToPixel(aPt);
//STRIP001  rOut.EnableMapMode(FALSE);
//STRIP001  long x=aPt.X(),y=aPt.Y(); // Groesse erstmal fest auf 7 Pixel
//STRIP001
//STRIP001  rOut.SetLineColor( aBackPenColor );
//STRIP001  rOut.DrawLine(Point(x-2,y-3),Point(x+3,y+2));
//STRIP001  rOut.DrawLine(Point(x-3,y-2),Point(x+2,y+3));
//STRIP001  rOut.DrawLine(Point(x-3,y+2),Point(x+2,y-3));
//STRIP001  rOut.DrawLine(Point(x-2,y+3),Point(x+3,y-2));
//STRIP001
//STRIP001  if (bNoPercent)
//STRIP001  {
//STRIP001      switch (GetHorzAlign())
//STRIP001      {
//STRIP001          case SDRHORZALIGN_LEFT  : rOut.DrawLine(Point(x-3,y-1),Point(x-3,y+1)); break;
//STRIP001          case SDRHORZALIGN_RIGHT : rOut.DrawLine(Point(x+3,y-1),Point(x+3,y+1)); break;
//STRIP001      }
//STRIP001
//STRIP001      switch (GetVertAlign())
//STRIP001      {
//STRIP001          case SDRVERTALIGN_TOP   : rOut.DrawLine(Point(x-1,y-3),Point(x+1,y-3)); break;
//STRIP001          case SDRVERTALIGN_BOTTOM: rOut.DrawLine(Point(x-1,y+3),Point(x+1,y+3)); break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  rOut.SetLineColor( aForePenColor );
//STRIP001  rOut.DrawLine(Point(x-2,y-2),Point(x+2,y+2));
//STRIP001  rOut.DrawLine(Point(x-2,y+2),Point(x+2,y-2));
//STRIP001  rOut.EnableMapMode(bMapMerk);
//STRIP001 }

//STRIP001 void SdrGluePoint::Invalidate(Window& rWin, const SdrObject* pObj) const
//STRIP001 {
//STRIP001  FASTBOOL bMapMerk=rWin.IsMapModeEnabled();
//STRIP001  Point aPt(pObj!=NULL ? GetAbsolutePos(*pObj) : GetPos());
//STRIP001  aPt=rWin.LogicToPixel(aPt);
//STRIP001  rWin.EnableMapMode(FALSE);
//STRIP001  long x=aPt.X(),y=aPt.Y(); // Groesse erstmal fest auf 7 Pixel
//STRIP001  rWin.Invalidate(Rectangle(Point(x-3,y-3),Point(x+3,y+3)));
//STRIP001  rWin.EnableMapMode(bMapMerk);
//STRIP001 }

//STRIP001 FASTBOOL SdrGluePoint::IsHit(const Point& rPnt, const OutputDevice& rOut, const SdrObject* pObj) const
//STRIP001 {
//STRIP001  Point aPt(pObj!=NULL ? GetAbsolutePos(*pObj) : GetPos());
//STRIP001  Size aSiz=rOut.PixelToLogic(Size(3,3));
//STRIP001  Rectangle aRect(aPt.X()-aSiz.Width(),aPt.Y()-aSiz.Height(),aPt.X()+aSiz.Width(),aPt.Y()+aSiz.Height());
//STRIP001  return aRect.IsInside(rPnt);
//STRIP001 }

/*?*/ SvStream& operator<<(SvStream& rOut, const SdrGluePoint& rGP)
/*?*/ {
/*?*/   if (rOut.GetError()!=0) return rOut;
/*?*/   SdrDownCompat aCompat(rOut,STREAM_WRITE); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*?*/ #ifdef DBG_UTIL
/*?*/   aCompat.SetID("SdrGluePoint");
/*?*/ #endif
/*?*/   rOut<<rGP.aPos;
/*?*/   rOut<<rGP.nEscDir;
/*?*/   rOut<<rGP.nId;
/*?*/   rOut<<rGP.nAlign;
/*?*/   BOOL bTmp=rGP.bNoPercent; // ueber bTmp, weil sonst (beim casting) im Falle
/*?*/   rOut<<bTmp;               // TRUE nicht 01 sondern FF geschrieben wird.
/*?*/   return rOut;
/*?*/ }

/*?*/ SvStream& operator>>(SvStream& rIn, SdrGluePoint& rGP)
/*?*/ {
/*?*/   if (rIn.GetError()!=0) return rIn;
/*?*/   SdrDownCompat aCompat(rIn,STREAM_READ); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*?*/ #ifdef DBG_UTIL
/*?*/   aCompat.SetID("SdrGluePoint");
/*?*/ #endif
/*?*/   BOOL bTmpBool;
/*?*/   rIn>>rGP.aPos;
/*?*/   rIn>>rGP.nEscDir;
/*?*/   rIn>>rGP.nId;
/*?*/   rIn>>rGP.nAlign;
/*?*/   rIn>>bTmpBool; rGP.bNoPercent=(bTmpBool!=0);
/*?*/   return rIn;
/*?*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrGluePointList::Clear()
/*N*/ {
/*N*/   USHORT nAnz=GetCount();
/*N*/   for (USHORT i=0; i<nAnz; i++) {
/*N*/       delete GetObject(i);
/*N*/   }
/*N*/   aList.Clear();
/*N*/ }

//STRIP001 void SdrGluePointList::operator=(const SdrGluePointList& rSrcList)
//STRIP001 {
//STRIP001  if (GetCount()!=0) Clear();
//STRIP001  USHORT nAnz=rSrcList.GetCount();
//STRIP001  for (USHORT i=0; i<nAnz; i++) {
//STRIP001      Insert(rSrcList[i]);
//STRIP001  }
//STRIP001 }

// Die Id's der Klebepunkte in der Liste sind stets streng monoton steigend!
// Ggf. wird dem neuen Klebepunkt eine neue Id zugewiesen (wenn diese bereits
// vergeben ist). Die Id 0 ist reserviert.
/*N*/ USHORT SdrGluePointList::Insert(const SdrGluePoint& rGP)
/*N*/ {
/*N*/   SdrGluePoint* pGP=new SdrGluePoint(rGP);
/*N*/   USHORT nId=pGP->GetId();
/*N*/   USHORT nAnz=GetCount();
/*N*/   USHORT nInsPos=nAnz;
/*N*/   USHORT nLastId=nAnz!=0 ? GetObject(nAnz-1)->GetId() : 0;
/*N*/   DBG_ASSERT(nLastId>=nAnz,"SdrGluePointList::Insert(): nLastId<nAnz");
/*N*/   FASTBOOL bHole=nLastId>nAnz;
/*N*/   if (nId<=nLastId) {
/*N*/       if (!bHole || nId==0) {
/*N*/           nId=nLastId+1;
/*N*/       } else {
/*N*/           FASTBOOL bBrk=FALSE;
/*N*/           for (USHORT nNum=0; nNum<nAnz && !bBrk; nNum++) {
/*N*/               const SdrGluePoint* pGP=GetObject(nNum);
/*N*/               USHORT nTmpId=pGP->GetId();
/*N*/               if (nTmpId==nId) {
/*N*/                   nId=nLastId+1; // bereits vorhanden
/*N*/                   bBrk=TRUE;
/*N*/               }
/*N*/               if (nTmpId>nId) {
/*N*/                   nInsPos=nNum; // Hier einfuegen (einsortieren)
/*N*/                   bBrk=TRUE;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/       pGP->SetId(nId);
/*N*/   }
/*N*/   aList.Insert(pGP,nInsPos);
/*N*/   return nInsPos;
/*N*/ }

//STRIP001 void SdrGluePointList::DrawAll(OutputDevice& rOut, const SdrObject* pObj) const
//STRIP001 {
//STRIP001  USHORT nAnz=GetCount();
//STRIP001  if (nAnz!=0)
//STRIP001  {
//STRIP001      Color aBackPenColor(COL_WHITE);
//STRIP001      Color aForePenColor(COL_LIGHTBLUE);
//STRIP001
//STRIP001      FASTBOOL bMapMerk=rOut.IsMapModeEnabled();
//STRIP001      rOut.SetLineColor( aBackPenColor );
//STRIP001      USHORT nNum;
//STRIP001
//STRIP001      for (nNum=0; nNum<nAnz; nNum++)
//STRIP001      {
//STRIP001          const SdrGluePoint* pGP=GetObject(nNum);
//STRIP001          Point aPt(pObj!=NULL ? pGP->GetAbsolutePos(*pObj) : pGP->GetPos());
//STRIP001          aPt=rOut.LogicToPixel(aPt);
//STRIP001          rOut.EnableMapMode(FALSE);
//STRIP001          long x=aPt.X(),y=aPt.Y(); // Groesse erstmal fest auf 7 Pixel
//STRIP001          rOut.DrawLine(Point(x-2,y-3),Point(x+3,y+2));
//STRIP001          rOut.DrawLine(Point(x-3,y-2),Point(x+2,y+3));
//STRIP001          rOut.DrawLine(Point(x-3,y+2),Point(x+2,y-3));
//STRIP001          rOut.DrawLine(Point(x-2,y+3),Point(x+3,y-2));
//STRIP001
//STRIP001          if (!pGP->IsPercent())
//STRIP001          {
//STRIP001              switch (pGP->GetHorzAlign())
//STRIP001              {
//STRIP001                  case SDRHORZALIGN_LEFT  : rOut.DrawLine(Point(x-3,y-1),Point(x-3,y+1)); break;
//STRIP001                  case SDRHORZALIGN_RIGHT : rOut.DrawLine(Point(x+3,y-1),Point(x+3,y+1)); break;
//STRIP001              }
//STRIP001              switch (pGP->GetVertAlign())
//STRIP001              {
//STRIP001                  case SDRVERTALIGN_TOP   : rOut.DrawLine(Point(x-1,y-3),Point(x+1,y-3)); break;
//STRIP001                  case SDRVERTALIGN_BOTTOM: rOut.DrawLine(Point(x-1,y+3),Point(x+1,y+3)); break;
//STRIP001              }
//STRIP001          }
//STRIP001          rOut.EnableMapMode(bMapMerk);
//STRIP001      }
//STRIP001
//STRIP001      rOut.SetLineColor( aForePenColor );
//STRIP001
//STRIP001      for (nNum=0; nNum<nAnz; nNum++)
//STRIP001      {
//STRIP001          const SdrGluePoint* pGP=GetObject(nNum);
//STRIP001          Point aPt(pObj!=NULL ? pGP->GetAbsolutePos(*pObj) : pGP->GetPos());
//STRIP001          aPt=rOut.LogicToPixel(aPt);
//STRIP001          rOut.EnableMapMode(FALSE);
//STRIP001          long x=aPt.X(),y=aPt.Y(); // Groesse erstmal fest auf 7 Pixel
//STRIP001          rOut.DrawLine(Point(x-2,y-2),Point(x+2,y+2));
//STRIP001          rOut.DrawLine(Point(x-2,y+2),Point(x+2,y-2));
//STRIP001          rOut.EnableMapMode(bMapMerk);
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrGluePointList::Invalidate(Window& rWin, const SdrObject* pObj) const
//STRIP001 {
//STRIP001  USHORT nAnz=GetCount();
//STRIP001  for (USHORT nNum=0; nNum<nAnz; nNum++) {
//STRIP001      GetObject(nNum)->Invalidate(rWin,pObj);
//STRIP001  }
//STRIP001 }

/*N*/ USHORT SdrGluePointList::FindGluePoint(USHORT nId) const
/*N*/ {
/*N*/   // Hier noch einen optimaleren Suchalgorithmus implementieren.
/*N*/   // Die Liste sollte stets sortiert sein!!!!
/*N*/   USHORT nAnz=GetCount();
/*N*/   USHORT nRet=SDRGLUEPOINT_NOTFOUND;
/*N*/   for (USHORT nNum=0; nNum<nAnz && nRet==SDRGLUEPOINT_NOTFOUND; nNum++) {
/*N*/       const SdrGluePoint* pGP=GetObject(nNum);
/*N*/       if (pGP->GetId()==nId) nRet=nNum;
/*N*/   }
/*N*/   return nRet;
/*N*/ }

//STRIP001 USHORT SdrGluePointList::HitTest(const Point& rPnt, const OutputDevice& rOut, const SdrObject* pObj, FASTBOOL bBack, FASTBOOL bNext, USHORT nId0) const
//STRIP001 {
//STRIP001  USHORT nAnz=GetCount();
//STRIP001  USHORT nRet=SDRGLUEPOINT_NOTFOUND;
//STRIP001  USHORT nNum=bBack ? 0 : nAnz;
//STRIP001  while ((bBack ? nNum<nAnz : nNum>0) && nRet==SDRGLUEPOINT_NOTFOUND) {
//STRIP001      if (!bBack) nNum--;
//STRIP001      const SdrGluePoint* pGP=GetObject(nNum);
//STRIP001      if (bNext) {
//STRIP001          if (pGP->GetId()==nId0) bNext=FALSE;
//STRIP001      } else {
//STRIP001          if (pGP->IsHit(rPnt,rOut,pObj)) nRet=nNum;
//STRIP001      }
//STRIP001      if (bBack) nNum++;
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

//STRIP001 void SdrGluePointList::SetReallyAbsolute(FASTBOOL bOn, const SdrObject& rObj)
//STRIP001 {
//STRIP001  USHORT nAnz=GetCount();
//STRIP001  for (USHORT nNum=0; nNum<nAnz; nNum++) {
//STRIP001      GetObject(nNum)->SetReallyAbsolute(bOn,rObj);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrGluePointList::Rotate(const Point& rRef, long nWink, double sn, double cs, const SdrObject* pObj)
//STRIP001 {
//STRIP001  USHORT nAnz=GetCount();
//STRIP001  for (USHORT nNum=0; nNum<nAnz; nNum++) {
//STRIP001      GetObject(nNum)->Rotate(rRef,nWink,sn,cs,pObj);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrGluePointList::Mirror(const Point& rRef1, const Point& rRef2, const SdrObject* pObj)
//STRIP001 {
//STRIP001  Point aPt(rRef2); aPt-=rRef1;
//STRIP001  long nWink=GetAngle(aPt);
//STRIP001  Mirror(rRef1,rRef2,nWink,pObj);
//STRIP001 }

//STRIP001 void SdrGluePointList::Mirror(const Point& rRef1, const Point& rRef2, long nWink, const SdrObject* pObj)
//STRIP001 {
//STRIP001  USHORT nAnz=GetCount();
//STRIP001  for (USHORT nNum=0; nNum<nAnz; nNum++) {
//STRIP001      GetObject(nNum)->Mirror(rRef1,rRef2,nWink,pObj);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrGluePointList::Shear(const Point& rRef, long nWink, double tn, FASTBOOL bVShear, const SdrObject* pObj)
//STRIP001 {
//STRIP001  USHORT nAnz=GetCount();
//STRIP001  for (USHORT nNum=0; nNum<nAnz; nNum++) {
//STRIP001      GetObject(nNum)->Shear(rRef,nWink,tn,bVShear,pObj);
//STRIP001  }
//STRIP001 }

/*?*/ SvStream& operator<<(SvStream& rOut, const SdrGluePointList& rGPL)
/*?*/ {
/*?*/   if (rOut.GetError()!=0) return rOut;
/*?*/   SdrDownCompat aCompat(rOut,STREAM_WRITE); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*?*/ #ifdef DBG_UTIL
/*?*/   aCompat.SetID("SdrGluePointList");
/*?*/ #endif
/*?*/   UINT16 nAnz=rGPL.GetCount();
/*?*/   rOut<<(UINT16)nAnz;
/*?*/   for (USHORT nNum=0; nNum<nAnz; nNum++) {
/*?*/       rOut<<rGPL[nNum];
/*?*/   }
/*?*/   return rOut;
/*?*/ }

/*?*/ SvStream& operator>>(SvStream& rIn, SdrGluePointList& rGPL)
/*?*/ {
/*?*/   if (rIn.GetError()!=0) return rIn;
/*?*/   SdrDownCompat aCompat(rIn,STREAM_READ); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*?*/ #ifdef DBG_UTIL
/*?*/   aCompat.SetID("SdrGluePointList");
/*?*/ #endif
/*?*/   rGPL.Clear();
/*?*/   UINT16 nAnz=0;
/*?*/   rIn>>nAnz;
/*?*/   for (USHORT nNum=0; nNum<nAnz; nNum++) {
/*?*/       SdrGluePoint aGP;
/*?*/       rIn>>aGP;
/*?*/       rGPL.Insert(aGP);
/*?*/   }
/*?*/   return rIn;
/*?*/ }

