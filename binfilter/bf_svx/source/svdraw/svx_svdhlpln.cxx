/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_svdhlpln.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 21:39:21 $
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

#include "svdhlpln.hxx"
#include "svdio.hxx"



#ifndef _SV_WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif

namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////



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
