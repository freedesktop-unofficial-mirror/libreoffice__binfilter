/*************************************************************************
 *
 *  $RCSfile: sw_swrect.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:48:17 $
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


#pragma hdrstop

#ifndef PRODUCT
#ifndef _STREAM_HXX //autogen
#include <tools/stream.hxx>
#endif
#endif
#include <stdlib.h>
#include "swrect.hxx"


/*************************************************************************
|*
|*  SwRect::SwRect()
|*
|*  Ersterstellung      MA 02. Feb. 93
|*  Letzte Aenderung    MA 05. Sep. 93
|*
|*************************************************************************/
#ifndef _DEBUG_HXX //autogen
#include <tools/debug.hxx>
#endif
namespace binfilter {
/*N*/ SwRect::SwRect( const Rectangle &rRect ) :
/*N*/   nX( rRect.Left() ),
/*N*/   nY( rRect.Top() )
/*N*/ {
/*N*/   nWidth  = rRect.Right() == RECT_EMPTY ? 0 :
/*N*/                           rRect.Right()  - rRect.Left() +1;
/*N*/   nHeight = rRect.Bottom() == RECT_EMPTY ? 0 :
/*N*/                           rRect.Bottom() - rRect.Top() + 1;
/*N*/ }

/*************************************************************************
|*
|*  SwRect::Center()
|*
|*  Ersterstellung      MA 27. Jan. 93
|*  Letzte Aenderung    MA 27. Jan. 93
|*
|*************************************************************************/
/*N*/ Point SwRect::Center() const
/*N*/ {
/*N*/   return Point( Left() + Width()  / 2,
/*N*/                 Top()  + Height() / 2 );

/*  Wer ruft schon ein Center auf ein "falsches" Rechteck?
    const long nRight = Right();
    const long nBottom= Bottom();
    return Point( min( Left(), nRight ) + long(abs( (nRight - Left())/2) ),
                  min( Top(),  nBottom) + long(abs( (nBottom - Top())/2)));
*/
/*N*/ }

/*************************************************************************
|*
|*  SwRect::Union()
|*
|*  Ersterstellung      MA 27. Jan. 93
|*  Letzte Aenderung    MA 27. Jan. 93
|*
|*************************************************************************/



/*N*/ SwRect& SwRect::Union( const SwRect& rRect )
/*N*/ {
/*N*/   if ( Top() > rRect.Top() )
/*N*/       Top( rRect.Top() );
/*N*/   if ( Left() > rRect.Left() )
/*N*/       Left( rRect.Left() );
/*N*/   register long n = rRect.Right();
/*N*/   if ( Right() < n )
/*N*/       Right( n );
/*N*/   n = rRect.Bottom();
/*N*/   if ( Bottom() < n )
/*N*/       Bottom( n );
/*N*/   return *this;
/*N*/ }
/*************************************************************************
|*
|*  SwRect::Intersection(), _Intersection()
|*
|*  Ersterstellung      MA 27. Jan. 93
|*  Letzte Aenderung    MA 05. Sep. 93
|*
|*************************************************************************/



/*N*/ SwRect& SwRect::Intersection( const SwRect& rRect )
/*N*/ {
/*N*/   //Hat das Teil ueberhaupt Gemeinsamkeiten mit mir?
/*N*/   if ( IsOver( rRect ) )
/*N*/   {
/*N*/       //Bestimmung der kleineren  rechten sowie unteren und
/*N*/       //           der groesseren linken  sowie oberen Kante.
/*N*/       if ( Left() < rRect.Left() )
/*N*/           Left( rRect.Left() );
/*N*/       if ( Top() < rRect.Top() )
/*?*/           Top( rRect.Top() );
/*N*/       register long n = rRect.Right();
/*N*/       if ( Right() > n )
/*N*/           Right( n );
/*N*/       n = rRect.Bottom();
/*N*/       if ( Bottom() > n )
/*?*/           Bottom( n );
/*N*/   }
/*N*/   else
/*N*/       //Def.: Bei einer leeren Intersection wird nur die SSize genullt.
/*N*/       nHeight = nWidth = 0;
/*N*/
/*N*/   return *this;
/*N*/ }



/*N*/ SwRect& SwRect::_Intersection( const SwRect& rRect )
/*N*/ {
/*N*/   //Bestimmung der kleineren  rechten sowie unteren und
/*N*/   //           der groesseren linken  sowie oberen Kante.
/*N*/   if ( Left() < rRect.Left() )
/*N*/       Left( rRect.Left() );
/*N*/   if ( Top() < rRect.Top() )
/*N*/       Top( rRect.Top() );
/*N*/   register long n = rRect.Right();
/*N*/   if ( Right() > n )
/*N*/       Right( n );
/*N*/   n = rRect.Bottom();
/*N*/   if ( Bottom() > n )
/*N*/       Bottom( n );
/*N*/
/*N*/   return *this;
/*N*/ }
/*************************************************************************
|*
|*  SwRect::IsInside()
|*
|*  Ersterstellung      MA 27. Jan. 93
|*  Letzte Aenderung    MA 27. Jan. 93
|*
|*************************************************************************/



/*N*/ BOOL SwRect::IsInside( const SwRect& rRect ) const
/*N*/ {
/*N*/   const long nRight  = Right();
/*N*/   const long nBottom = Bottom();
/*N*/   const long nrRight = rRect.Right();
/*N*/   const long nrBottom= rRect.Bottom();
/*N*/   return (Left() <= rRect.Left()) && (rRect.Left()<= nRight)  &&
/*N*/          (Left() <= nrRight)      && (nrRight     <= nRight)  &&
/*N*/          (Top()  <= rRect.Top())  && (rRect.Top() <= nBottom) &&
/*N*/          (Top()  <= nrBottom)     && (nrBottom    <= nBottom);
/*N*/ }



/*N*/ BOOL SwRect::IsInside( const Point& rPoint ) const
/*N*/ {
/*N*/   return    (Left()  <= rPoint.X())
/*N*/          && (Top()   <= rPoint.Y())
/*N*/          && (Right() >= rPoint.X())
/*N*/          && (Bottom()>= rPoint.Y());
/*N*/ }
/* -----------------------------11.04.00 15:46--------------------------------
    mouse moving of table borders
 ---------------------------------------------------------------------------*/
//STRIP001 BOOL SwRect::IsNear( const Point& rPoint, long nTolerance ) const
//STRIP001 {
//STRIP001  return    IsInside(rPoint) ||
//STRIP001      (((Left() - nTolerance)  <= rPoint.X())
//STRIP001         && ((Top()  - nTolerance)  <= rPoint.Y())
//STRIP001         && ((Right() + nTolerance) >= rPoint.X())
//STRIP001         && ((Bottom()  + nTolerance)>= rPoint.Y()));
//STRIP001 }

/*************************************************************************
|*
|*  SwRect::IsOver()
|*
|*  Ersterstellung      MA 25. Feb. 94
|*  Letzte Aenderung    MA 27. Jun. 96
|*
|*************************************************************************/



/*N*/ BOOL SwRect::IsOver( const SwRect& rRect ) const
/*N*/ {
/*N*/   return    (Top()   <= rRect.Bottom())
/*N*/          && (Left()  <= rRect.Right())
/*N*/          && (Right() >= rRect.Left())
/*N*/          && (Bottom()>= rRect.Top()) ? TRUE : FALSE;
/*N*/ }

/*************************************************************************
|*
|*  SwRect::Justify()
|*
|*  Ersterstellung      MA 10. Oct. 94
|*  Letzte Aenderung    MA 23. Oct. 96
|*
|*************************************************************************/



/*N*/ void SwRect::Justify()
/*N*/ {
/*N*/   if ( nHeight < 0 )
/*N*/   {
/*N*/       nY = nY + nHeight + 1;
/*N*/       nHeight = -nHeight;
/*N*/   }
/*N*/   if ( nWidth < 0 )
/*N*/   {
/*N*/       nX = nX + nWidth + 1;
/*N*/       nWidth = -nWidth;
/*N*/   }
/*N*/ }


#ifdef VERTICAL_LAYOUT

// Similiar to the inline methods, but we need the function pointers

/*N*/ void SwRect::_Width( const long nNew ) { nWidth = nNew; }
/*N*/ void SwRect::_Height( const long nNew ) { nHeight = nNew; }
/*N*/ void SwRect::_Left( const long nLeft ){ nWidth += nX - nLeft; nX = nLeft; }
/*N*/ void SwRect::_Right( const long nRight ){ nWidth = nRight - nX; }
/*N*/ void SwRect::_Top( const long nTop ){ nHeight += nY - nTop; nY = nTop; }
/*N*/ void SwRect::_Bottom( const long nBottom ){ nHeight = nBottom - nY; }
/*N*/
/*N*/ long SwRect::_Width() const{ return nWidth; }
/*N*/ long SwRect::_Height() const{ return nHeight; }
/*N*/ long SwRect::_Left() const{ return nX; }
/*N*/ long SwRect::_Right() const{ return nX + nWidth; }
/*N*/ long SwRect::_Top() const{ return nY; }
/*N*/ long SwRect::_Bottom() const{ return nY + nHeight; }

/*N*/ void SwRect::AddWidth( const long nAdd ) { nWidth += nAdd; }
/*N*/ void SwRect::AddHeight( const long nAdd ) { nHeight += nAdd; }
/*N*/ void SwRect::SubLeft( const long nSub ){ nWidth += nSub; nX -= nSub; }
/*N*/ void SwRect::AddRight( const long nAdd ){ nWidth += nAdd; }
/*N*/ void SwRect::SubTop( const long nSub ){ nHeight += nSub; nY -= nSub; }
/*N*/ void SwRect::AddBottom( const long nAdd ){ nHeight += nAdd; }
/*N*/ void SwRect::SetPosX( const long nNew ){ nX = nNew; }
/*N*/ void SwRect::SetPosY( const long nNew ){ nY = nNew; }
//STRIP001 const Point SwRect::_Pos()  const { return Pos(); }
/*N*/ const Size  SwRect::_Size() const { return SSize(); }
//STRIP001 const Point SwRect::SwappedPos()  const { return Point( nY, nX ); }
/*N*/ const Size  SwRect::SwappedSize() const { return Size( nHeight, nWidth ); }
/*N*/ const Point SwRect::TopLeft() const { return Pos(); }
/*N*/ const Point SwRect::TopRight() const { return Point( nX + nWidth, nY ); }
/*N*/ const Point SwRect::BottomLeft() const { return Point( nX, nY + nHeight ); }
/*N*/ const Point SwRect::BottomRight() const
/*N*/     { return Point( nX + nWidth, nY + nHeight ); }
/*N*/ long SwRect::GetLeftDistance( long nLimit ) const { return nX - nLimit; }
/*N*/ long SwRect::GetBottomDistance( long nLim ) const { return nLim - nY - nHeight;}
/*N*/ long SwRect::GetTopDistance( long nLimit ) const { return nY - nLimit; }
/*N*/ long SwRect::GetRightDistance( long nLim ) const { return nLim - nX - nWidth; }
/*N*/ BOOL SwRect::OverStepLeft( long nLimit ) const
/*N*/     { return nLimit > nX && nX + nWidth > nLimit; }
/*N*/ BOOL SwRect::OverStepBottom( long nLimit ) const
/*N*/     { return nLimit > nY && nY + nHeight > nLimit; }
/*N*/ BOOL SwRect::OverStepTop( long nLimit ) const
/*N*/     { return nLimit > nY && nY + nHeight > nLimit; }
/*N*/ BOOL SwRect::OverStepRight( long nLimit ) const
/*N*/     { return nLimit > nX && nX + nWidth > nLimit; }
/*N*/ void SwRect::SetLeftAndWidth( long nLeft, long nNew )
/*N*/     { nX = nLeft; nWidth = nNew; }
/*N*/ void SwRect::SetTopAndHeight( long nTop, long nNew )
/*N*/     { nY = nTop; nHeight = nNew; }
/*N*/ void SwRect::SetRightAndWidth( long nRight, long nNew )
/*N*/     { nX = nRight - nNew; nWidth = nNew; }
/*N*/ void SwRect::SetBottomAndHeight( long nBottom, long nNew )
/*N*/     { nY = nBottom - nNew; nHeight = nNew; }
/*N*/ void SwRect::SetUpperLeftCorner(  const Point& rNew )
/*N*/     { nX = rNew.nA; nY = rNew.nB; }
/*N*/ void SwRect::SetUpperRightCorner(  const Point& rNew )
/*N*/     { nX = rNew.nA - nWidth; nY = rNew.nB; }
/*N*/ void SwRect::SetLowerLeftCorner(  const Point& rNew )
/*N*/     { nX = rNew.nA; nY = rNew.nB - nHeight; }
//STRIP001 void SwRect::SetLowerRightCorner(  const Point& rNew )
//STRIP001     { nX = rNew.nA - nWidth; nY = rNew.nB - nHeight; }
#endif

#ifndef PRODUCT
/*************************************************************************
 *                  operator<<( ostream&, SwRect&)
 *************************************************************************/



/*N*/ SvStream &operator<<( SvStream &rStream, const SwRect &rRect )
/*N*/ {
/*N*/           DBG_ASSERT(0, "STRIP"); //STRIP001 //STRIP001   rStream << '[' << rRect.Top()   << '/' << rRect.Left()
//STRIP001          << ',' << rRect.Width() << 'x' << rRect.Height() << "] ";
/*N*/   return rStream;
/*N*/ }
#endif


}
