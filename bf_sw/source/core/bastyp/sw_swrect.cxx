/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <stdlib.h>
#include "swrect.hxx"


/*************************************************************************
|*
|*  SwRect::SwRect()
|*
|*************************************************************************/
#include <tools/debug.hxx>
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
|*  SwRect::Union()
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
/* ---------------------------------------------------------------------------
    mouse moving of table borders
 ---------------------------------------------------------------------------*/

/*************************************************************************
|*
|*  SwRect::IsOver()
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
/*N*/ const Size  SwRect::_Size() const { return SSize(); }
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
#endif

#ifdef DBG_UTIL
/*************************************************************************
 *                  operator<<( ostream&, SwRect&)
 *************************************************************************/



/*N*/ SvStream &operator<<( SvStream &rStream, const SwRect & )
/*N*/ {
/*N*/   return rStream;
/*N*/ }
#endif


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
