/*************************************************************************
 *
 *  $RCSfile: svx_svdhlpln.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 16:23:04 $
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

#include "svdhlpln.hxx"
#include "svdio.hxx"

// auto strip #ifndef _COLOR_HXX //autogen
// auto strip #include <tools/color.hxx>
// auto strip #endif

// auto strip #ifndef _OUTDEV_HXX //autogen
// auto strip #include <vcl/outdev.hxx>
// auto strip #endif

#ifndef _SV_WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif

// auto strip #ifndef _TL_POLY_HXX
// auto strip #include <tools/poly.hxx>
// auto strip #endif
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 Pointer SdrHelpLine::GetPointer() const
//STRIP001 {
//STRIP001  switch (eKind) {
//STRIP001      case SDRHELPLINE_VERTICAL  : return Pointer(POINTER_ESIZE); break;
//STRIP001      case SDRHELPLINE_HORIZONTAL: return Pointer(POINTER_SSIZE); break;
//STRIP001      default                    : return Pointer(POINTER_MOVE);  break;
//STRIP001  } // switch
//STRIP001 }

//STRIP001 void SdrHelpLine::Draw(OutputDevice& rOut, const Point& rOfs) const
//STRIP001 {
//STRIP001  Point aPnt(rOut.LogicToPixel(aPos+rOfs));
//STRIP001  long x=aPnt.X();
//STRIP001  long y=aPnt.Y();
//STRIP001  long nMin=0;
//STRIP001  long nMax=2048;
//STRIP001  FASTBOOL bMap0=rOut.IsMapModeEnabled();
//STRIP001  rOut.EnableMapMode(FALSE);
//STRIP001  switch (eKind) {
//STRIP001      case SDRHELPLINE_VERTICAL  :
//STRIP001      {
//STRIP001          if (rOut.GetOutDevType() == OUTDEV_WINDOW)
//STRIP001          {
//STRIP001              Point aLine[2];
//STRIP001              aLine[0].X() = x; aLine[0].Y() = nMin;
//STRIP001              aLine[1].X() = x; aLine[1].Y() = nMax;
//STRIP001              ((Window&) rOut).InvertTracking(Polygon(2, aLine), SHOWTRACK_WINDOW);
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              rOut.DrawLine(Point(x,nMin),Point(x,nMax));
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001      case SDRHELPLINE_HORIZONTAL:
//STRIP001      {
//STRIP001          if (rOut.GetOutDevType() == OUTDEV_WINDOW)
//STRIP001          {
//STRIP001              Point aLine[2];
//STRIP001              aLine[0].X() = nMin; aLine[0].Y() = y;
//STRIP001              aLine[1].X() = nMax; aLine[1].Y() = y;
//STRIP001              ((Window&) rOut).InvertTracking(Polygon(2, aLine), SHOWTRACK_WINDOW);
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              rOut.DrawLine(Point(nMin,y),Point(nMax,y));
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001      case SDRHELPLINE_POINT     :
//STRIP001      {
//STRIP001          int r=SDRHELPLINE_POINT_PIXELSIZE;
//STRIP001
//STRIP001          if (rOut.GetOutDevType() == OUTDEV_WINDOW)
//STRIP001          {
//STRIP001              Point aHLine[2];
//STRIP001              aHLine[0].X() = x-r; aHLine[0].Y() = y;
//STRIP001              aHLine[1].X() = x+r; aHLine[1].Y() = y;
//STRIP001              ((Window&) rOut).InvertTracking(Polygon(2, aHLine), SHOWTRACK_WINDOW);
//STRIP001
//STRIP001              Point aVLine[2];
//STRIP001              aVLine[0].X() = x; aVLine[0].Y() = y-r;
//STRIP001              aVLine[1].X() = x; aVLine[1].Y() = y+r;
//STRIP001              ((Window&) rOut).InvertTracking(Polygon(2, aVLine), SHOWTRACK_WINDOW);
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              rOut.DrawLine(Point(x-r,y),Point(x+r,y));
//STRIP001              rOut.DrawLine(Point(x,y-r),Point(x,y+r));
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  } // switch
//STRIP001  rOut.EnableMapMode(bMap0);
//STRIP001 }

/*N*/ FASTBOOL SdrHelpLine::IsHit(const Point& rPnt, USHORT nTolLog, const OutputDevice& rOut) const
/*N*/ {
/*N*/   Size a1Pix(rOut.PixelToLogic(Size(1,1)));
/*N*/   FASTBOOL bXHit=rPnt.X()>=aPos.X()-nTolLog && rPnt.X()<=aPos.X()+nTolLog+a1Pix.Width();
/*N*/   FASTBOOL bYHit=rPnt.Y()>=aPos.Y()-nTolLog && rPnt.Y()<=aPos.Y()+nTolLog+a1Pix.Height();
/*N*/   switch (eKind) {
/*N*/       case SDRHELPLINE_VERTICAL  : return bXHit; break;
/*N*/       case SDRHELPLINE_HORIZONTAL: return bYHit; break;
/*N*/       case SDRHELPLINE_POINT: {
/*?*/           if (bXHit || bYHit) {
/*?*/               Size aRad(rOut.PixelToLogic(Size(SDRHELPLINE_POINT_PIXELSIZE,SDRHELPLINE_POINT_PIXELSIZE)));
/*?*/               return rPnt.X()>=aPos.X()-aRad.Width() && rPnt.X()<=aPos.X()+aRad.Width()+a1Pix.Width() &&
/*?*/                      rPnt.Y()>=aPos.Y()-aRad.Height() && rPnt.Y()<=aPos.Y()+aRad.Height()+a1Pix.Height();
/*N*/           }
/*N*/       } break;
/*N*/   } // switch
/*N*/   return FALSE;
/*N*/ }

//STRIP001 Rectangle SdrHelpLine::GetBoundRect(const OutputDevice& rOut) const
//STRIP001 {
//STRIP001  Rectangle aRet(aPos,aPos);
//STRIP001  Point aOfs(rOut.GetMapMode().GetOrigin());
//STRIP001  Size aSiz(rOut.GetOutputSize());
//STRIP001  switch (eKind) {
//STRIP001      case SDRHELPLINE_VERTICAL  : aRet.Top()=-aOfs.Y(); aRet.Bottom()=-aOfs.Y()+aSiz.Height(); break;
//STRIP001      case SDRHELPLINE_HORIZONTAL: aRet.Left()=-aOfs.X(); aRet.Right()=-aOfs.X()+aSiz.Width();  break;
//STRIP001      case SDRHELPLINE_POINT     : {
//STRIP001          Size aRad(rOut.PixelToLogic(Size(SDRHELPLINE_POINT_PIXELSIZE,SDRHELPLINE_POINT_PIXELSIZE)));
//STRIP001          aRet.Left()  -=aRad.Width();
//STRIP001          aRet.Right() +=aRad.Width();
//STRIP001          aRet.Top()   -=aRad.Height();
//STRIP001          aRet.Bottom()+=aRad.Height();
//STRIP001      } break;
//STRIP001  } // switch
//STRIP001  return aRet;
//STRIP001 }

//STRIP001 bool SdrHelpLine::IsVisibleEqual( const SdrHelpLine& rHelpLine, const OutputDevice& rOut ) const
//STRIP001 {
//STRIP001  if( eKind == rHelpLine.eKind)
//STRIP001  {
//STRIP001      Point aPt1(rOut.LogicToPixel(aPos)), aPt2(rOut.LogicToPixel(rHelpLine.aPos));
//STRIP001      switch( eKind )
//STRIP001      {
//STRIP001          case SDRHELPLINE_POINT:
//STRIP001              return aPt1 == aPt2;
//STRIP001          case SDRHELPLINE_VERTICAL:
//STRIP001              return aPt1.X() == aPt2.X();
//STRIP001          case SDRHELPLINE_HORIZONTAL:
//STRIP001              return aPt1.Y() == aPt2.Y();
//STRIP001      }
//STRIP001  }
//STRIP001  return false;
//STRIP001 }

/*?*/ SvStream& operator<<(SvStream& rOut, const SdrHelpLine& rHL)
/*?*/ {
/*?*/   SdrIOHeader aHead(rOut,STREAM_WRITE,SdrIOHlpLID);
/*?*/   rOut<<UINT16(rHL.eKind);
/*?*/   rOut<<rHL.aPos;
/*?*/   return rOut;
/*?*/ }

/*N*/ SvStream& operator>>(SvStream& rIn, SdrHelpLine& rHL)
/*N*/ {
/*N*/   SdrIOHeader aHead(rIn,STREAM_READ);
/*N*/   UINT16 nDum;
/*N*/   rIn>>nDum;
/*N*/   rHL.eKind=(SdrHelpLineKind)nDum;
/*N*/   rIn>>rHL.aPos;
/*N*/   return rIn;
/*N*/ }

/*N*/ void SdrHelpLineList::Clear()
/*N*/ {
/*N*/   USHORT nAnz=GetCount();
/*N*/   for (USHORT i=0; i<nAnz; i++) {
/*N*/       delete GetObject(i);
/*N*/   }
/*N*/   aList.Clear();
/*N*/ }

/*N*/ void SdrHelpLineList::operator=(const SdrHelpLineList& rSrcList)
/*N*/ {
/*N*/   Clear();
/*N*/   USHORT nAnz=rSrcList.GetCount();
/*N*/   for (USHORT i=0; i<nAnz; i++) {
/*N*/       Insert(rSrcList[i]);
/*N*/   }
/*N*/ }

//STRIP001 FASTBOOL SdrHelpLineList::operator==(const SdrHelpLineList& rSrcList) const
//STRIP001 {
//STRIP001  FASTBOOL bEqual=FALSE;
//STRIP001  USHORT nAnz=GetCount();
//STRIP001  if (nAnz==rSrcList.GetCount()) {
//STRIP001      bEqual=TRUE;
//STRIP001      for (USHORT i=0; i<nAnz && bEqual; i++) {
//STRIP001          if (*GetObject(i)!=*rSrcList.GetObject(i)) {
//STRIP001              bEqual=FALSE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return bEqual;
//STRIP001 }

//STRIP001 void SdrHelpLineList::DrawAll(OutputDevice& rOut, const Point& rOfs) const
//STRIP001 {
//STRIP001  Color aOldLineColor( rOut.GetLineColor() );
//STRIP001
//STRIP001  rOut.SetLineColor( Color( COL_GREEN ) );
//STRIP001
//STRIP001  sal_uInt16 nAnz = GetCount();
//STRIP001  sal_uInt16 i,j;
//STRIP001  SdrHelpLine *pHL, *pHL2;
//STRIP001
//STRIP001  for(i=0; i<nAnz; i++)
//STRIP001  {
//STRIP001      pHL = GetObject(i);
//STRIP001
//STRIP001      // check if we already drawn a help line like this one
//STRIP001      if( pHL )
//STRIP001      {
//STRIP001          for(j=0;j<i;j++)
//STRIP001          {
//STRIP001              pHL2 = GetObject(j);
//STRIP001              if( pHL2 && pHL->IsVisibleEqual( *pHL2, rOut) )
//STRIP001              {
//STRIP001                  pHL = NULL;
//STRIP001                  break;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if( pHL )
//STRIP001          pHL->Draw(rOut,rOfs);
//STRIP001  }
//STRIP001
//STRIP001  rOut.SetLineColor( aOldLineColor );
//STRIP001 }

/*N*/ USHORT SdrHelpLineList::HitTest(const Point& rPnt, USHORT nTolLog, const OutputDevice& rOut) const
/*N*/ {
/*N*/   USHORT nAnz=GetCount();
/*N*/   for (USHORT i=nAnz; i>0;) {
/*N*/       i--;
/*N*/       if (GetObject(i)->IsHit(rPnt,nTolLog,rOut)) return i;
/*N*/   }
/*N*/   return SDRHELPLINE_NOTFOUND;
/*N*/ }

/*N*/ SvStream& operator<<(SvStream& rOut, const SdrHelpLineList& rHLL)
/*N*/ {
/*N*/   SdrIOHeader aHead(rOut,STREAM_WRITE,SdrIOHLstID);
/*N*/   USHORT nAnz=rHLL.GetCount();
/*N*/   rOut<<nAnz;
/*N*/   for (USHORT i=0; i<nAnz; i++) {
/*N*/       rOut<<rHLL[i];
/*N*/   }
/*N*/   return rOut;
/*N*/ }

/*N*/ SvStream& operator>>(SvStream& rIn, SdrHelpLineList& rHLL)
/*N*/ {
/*N*/   SdrIOHeader aHead(rIn,STREAM_READ);
/*N*/   rHLL.Clear();
/*N*/   USHORT nAnz;
/*N*/   rIn>>nAnz;
/*N*/   for (USHORT i=0; i<nAnz; i++) {
/*N*/       SdrHelpLine* pHL=new SdrHelpLine;
/*N*/       rIn>>*pHL;
/*N*/       rHLL.aList.Insert(pHL,CONTAINER_APPEND);
/*N*/   }
/*N*/   return rIn;
/*N*/ }

}
