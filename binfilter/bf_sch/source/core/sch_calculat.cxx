/*************************************************************************
 *
 *  $RCSfile: sch_calculat.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 12:42:32 $
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

// header for Point, Rectangle
// auto strip #ifndef _SV_GEN_HXX
// auto strip #include <tools/gen.hxx>
// auto strip #endif
// header for Polygon
// auto strip #ifndef _TL_POLY_HXX
// auto strip #include <tools/poly.hxx>
// auto strip #endif
// header for DBG_ASSERT
// auto strip #ifndef _TOOLS_DEBUG_HXX
// auto strip #include <tools/debug.hxx>
// auto strip #endif
// header for XPolygon, XPolyPolygon
#ifndef _XPOLY_HXX
#include <bf_svx/xpoly.hxx>
#endif
// header for Line
#ifndef _SV_LINE_HXX
#include <tools/line.hxx>
#endif
// auto strip #ifndef INCLUDED_RTL_MATH_HXX
// auto strip #include <rtl/math.hxx>
// auto strip #endif
// for performance measurement
#ifndef _RTL_LOGFILE_HXX_
#include <rtl/logfile.hxx>
#endif

// Note: Enable the following to skip points in the resulting spline
// poly-polygon, if they have equal x-values rather than identical points.
// Unitl now, I think there are situations where the output might differ, if you
// do so, so it's not enabled by default.

// #define SPLINE_OPTIMIZE_POINTS

#include "calculat.hxx"

#include <algorithm>
#include <functional>
namespace binfilter {

using namespace ::std;

//STRIP001 void SchCalculationHelper::IntersectPolyPolygonWithRectangle(
//STRIP001     const XPolyPolygon & rPolyPolygon,
//STRIP001     const Rectangle& rRectangle,
//STRIP001     XPolyPolygon& rOutResult )
//STRIP001 {
//STRIP001  RTL_LOGFILE_CONTEXT_AUTHOR( context, "sch", "bm93744", "SchCalculationHelper::IntersectPolyPolygonWithRectangle");
//STRIP001
//STRIP001     const USHORT nCount = rPolyPolygon.Count();
//STRIP001     rOutResult.Clear();
//STRIP001     XPolyPolygon aSubResult;
//STRIP001
//STRIP001     for( USHORT i = 0; i < nCount; ++i )
//STRIP001     {
//STRIP001         aSubResult.Clear();
//STRIP001         IntersectPolygonWithRectangle( rPolyPolygon.GetObject( i ),
//STRIP001                                        rRectangle,
//STRIP001                                        aSubResult );
//STRIP001
//STRIP001         rOutResult.Insert( aSubResult, XPOLYPOLY_APPEND );
//STRIP001     }
//STRIP001     OSL_TRACE( "IntersectPolyPolygonWithRectangle: result has %d polygons", rOutResult.Count() );
//STRIP001 }

/*N*/ void SchCalculationHelper::IntersectPolygonWithRectangle( const XPolygon& rPolygon, const Rectangle& rRectangle, XPolyPolygon& aResult )
/*N*/ {
/*N*/   RTL_LOGFILE_CONTEXT_AUTHOR( context, "sch", "bm93744", "SchCalculationHelper::IntersectPolygonWithRectangle");
/*N*/
/*N*/   aResult.Clear();
/*N*/
/*N*/   if( rRectangle.IsInside( rPolygon.GetBoundRect() ) )
/*N*/   {
/*N*/       aResult.Insert( rPolygon );
/*N*/         OSL_TRACE( "IntersectPolygonWithRectangle: result has %d polygons", aResult.Count() );
/*N*/       return;
/*N*/   }
/*N*/
/*N*/     Point aFrom;
/*N*/     Point aTo;
/*N*/   USHORT nCount = rPolygon.GetPointCount();
/*N*/
/*N*/     // set last point to a position outside the rectangle, such that the first
/*N*/     // time clip2d returns true, the comparison to last will always yield false
/*N*/     Point aLast (rRectangle.TopLeft());
/*N*/     aLast.Move (-1, -1);
/*N*/     XPolygon aCurrentPoly;
/*N*/     USHORT nIdx = 0;
/*N*/
/*N*/   for (USHORT i=1; i<nCount; i++)
/*N*/   {
/*N*/       aFrom = rPolygon[i-1];
/*N*/       aTo = rPolygon[i];
/*N*/       if (clip2d (aFrom, aTo, rRectangle))
/*N*/       {
/*N*/             // compose an XPolygon of as many consecutive points as possible
/*N*/             if (aFrom == aLast)
/*N*/             {
/*N*/                 if (aTo != aFrom)
/*N*/                     aCurrentPoly.Insert (nIdx++, aTo, XPOLY_NORMAL);
/*N*/             }
/*N*/             else
/*N*/             {
/*N*/                 // create an XPolygon and put it into the XPolyPolygon
/*N*/                 if (aCurrentPoly.GetPointCount() > 0)
/*N*/                     aResult.Insert (aCurrentPoly, XPOLYPOLY_APPEND);
/*N*/
/*N*/                 // start new sequence
/*N*/               aCurrentPoly.SetPointCount (0);
/*N*/                 aCurrentPoly.Insert (0, aFrom, XPOLY_NORMAL);
/*N*/                 nIdx = 1;
/*N*/                 if (aTo != aFrom)
/*N*/                     aCurrentPoly.Insert (nIdx++, aTo, XPOLY_NORMAL);
/*N*/             }
/*N*/
/*N*/             aLast = aTo;
/*N*/         }
/*N*/     }
/*N*/     if (aCurrentPoly.GetPointCount() > 0)
/*N*/         aResult.Insert (aCurrentPoly, XPOLYPOLY_APPEND);
/*N*/
/*N*/     OSL_TRACE( "IntersectPolygonWithRectangle: result has %d polygons", aResult.Count() );
/*N*/ }

//STRIP001 BOOL SchCalculationHelper::ClipLineAtRectangle( Line& aLine, const Rectangle& rRectangle )
//STRIP001 {
//STRIP001  Point   aPoint0 = aLine.GetStart ();
//STRIP001  Point   aPoint1 = aLine.GetEnd ();
//STRIP001  BOOL    bVisible = clip2d (aPoint0, aPoint1, rRectangle);
//STRIP001  if (bVisible)
//STRIP001  {
//STRIP001      aLine.SetStart (aPoint0);
//STRIP001      aLine.SetEnd (aPoint1);
//STRIP001  }
//STRIP001  return bVisible;
//STRIP001 }




/*N*/ BOOL  SchCalculationHelper::clip2d    (Point & rPoint0,
/*N*/                                       Point & rPoint1,
/*N*/                                       const Rectangle & rRectangle)
/*N*/ {
/*N*/   //  Direction vector of the line.
/*N*/   Point   aD = rPoint1 - rPoint0;
/*N*/
/*N*/   if (aD.X()==0 && aD.Y()==0 && rRectangle.IsInside (rPoint0))
/*N*/   {
/*N*/       //  Degenerate case of a zero length line.
/*N*/       return TRUE;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       //  Values of the line parameter where the line enters resp. leaves the rectangle.
/*N*/       double  fTE = 0,
/*N*/               fTL = 1;
/*N*/
/*N*/       //  Test wether at least a part lies in the four half-planes with respect to
/*N*/       //  the rectangles four edges.
/*N*/       if (CLIPt (aD.X(), rRectangle.Left() - rPoint0.X(), fTE, fTL))
/*N*/           if (CLIPt (-aD.X(), rPoint0.X() - rRectangle.Right(), fTE, fTL))
/*N*/               if (CLIPt (aD.Y(), rRectangle.Top() - rPoint0.Y(), fTE, fTL))
/*N*/                   if (CLIPt (-aD.Y(), rPoint0.Y() - rRectangle.Bottom(), fTE, fTL))
/*N*/                   {
/*N*/                       //  At least a part is visible.
/*N*/                       if (fTL < 1)
/*N*/                       {
/*N*/                           //  ::com::pute the new end point.
/*N*/                           rPoint1.X() = (long)(rPoint0.X() + fTL * aD.X() + 0.5);
/*N*/                           rPoint1.Y() = (long)(rPoint0.Y() + fTL * aD.Y() + 0.5);
/*N*/                       }
/*N*/                       if (fTE > 0)
/*N*/                       {
/*N*/                           //  ::com::pute the new starting point.
/*N*/                           rPoint0.X() = (long)(rPoint0.X() + fTE * aD.X() + 0.5);
/*N*/                           rPoint0.Y() = (long)(rPoint0.Y() + fTE * aD.Y() + 0.5);
/*N*/                       }
/*N*/                       return TRUE;
/*N*/                   }
/*N*/
/*N*/       //  Line is not visible.
/*N*/       return FALSE;
/*N*/   }
/*N*/ }




/*N*/ BOOL  SchCalculationHelper::CLIPt (double fDenom,
/*N*/                                   double fNum,
/*N*/                                   double & fTE,
/*N*/                                   double & fTL)
/*N*/ {
/*N*/   double  fT;
/*N*/
/*N*/   if (fDenom > 0)             //  Intersection enters: PE
/*N*/   {
/*N*/       fT = fNum / fDenom;     //  Parametric value at the intersection.
/*N*/       if (fT > fTL)           //  fTE and fTL crossover
/*N*/           return FALSE;       //    therefore reject the line.
/*N*/       else if (fT > fTE)      //  A new fTE has been found.
/*N*/           fTE = fT;
/*N*/   }
/*N*/   else if (fDenom < 0)        //  Intersection leaves: PL
/*N*/   {
/*N*/       fT = fNum / fDenom;     //  Parametric Value at the intersection.
/*N*/       if (fT < fTE)           //  fTE and fTL crossover
/*N*/           return FALSE;       //    therefore reject the line.
/*N*/       else if (fT < fTL)      //  A new fTL has been found.
/*N*/           fTL = fT;
/*N*/   }
/*N*/   else if (fNum > 0)
/*N*/       return FALSE;           //  Line lies on the outside of the edge.
/*N*/
/*N*/   return TRUE;
/*N*/ }


// --------------------------------------------------------------------------------

// Calculation of Splines

//STRIP001 namespace
//STRIP001 {
//STRIP001
//STRIP001 class lcl_SplineCalculation
//STRIP001 {
//STRIP001 public:
//STRIP001     typedef pair< double, double >   tPointType;
//STRIP001     typedef vector< tPointType >     tPointVecType;
//STRIP001
//STRIP001     /** @descr creates an object that calculates cublic splines on construction
//STRIP001
//STRIP001         @param rPoints  the points for which splines shall be calculated
//STRIP001         @param fY1FirstDerivation the resulting spline should have the first
//STRIP001                derivation equal to this value at the x-value of the first point
//STRIP001                of rPoints.  If fY1FirstDerivation is set to infinity, a natural
//STRIP001                spline is calculated.
//STRIP001         @param fYnFirstDerivation the resulting spline should have the first
//STRIP001                derivation equal to this value at the x-value of the last point
//STRIP001                of rPoints
//STRIP001      */
//STRIP001     lcl_SplineCalculation( const tPointVecType & rPoints,
//STRIP001                            double fY1FirstDerivation,
//STRIP001                            double fYnFirstDerivation );
//STRIP001
//STRIP001     /** @descr this function corresponds to the function splint in [1].
//STRIP001
//STRIP001         [1] Numerical Recipies in C, 2nd edition
//STRIP001             William H. Press, et al.,
//STRIP001             Section 3.3, page 116
//STRIP001     */
//STRIP001     double GetInterpolatedValue( double x );
//STRIP001
//STRIP001 private:
//STRIP001     /// a copy of the points given in the CTOR
//STRIP001     tPointVecType            m_aPoints;
//STRIP001
//STRIP001     /// the result of the Calculate() method
//STRIP001     vector< double >         m_aSecDerivY;
//STRIP001
//STRIP001     double m_fYp1;
//STRIP001     double m_fYpN;
//STRIP001
//STRIP001     // these values are cached for performance reasons
//STRIP001     tPointVecType::size_type m_nKLow;
//STRIP001     tPointVecType::size_type m_nKHigh;
//STRIP001     double m_fLastInterpolatedValue;
//STRIP001
//STRIP001     /** @descr this function corresponds to the function spline in [1].
//STRIP001
//STRIP001         [1] Numerical Recipies in C, 2nd edition
//STRIP001             William H. Press, et al.,
//STRIP001             Section 3.3, page 115
//STRIP001     */
//STRIP001     void Calculate();
//STRIP001 };
//STRIP001
//STRIP001 template< typename T, typename U >
//STRIP001     struct lcl_LessFirstOfPair : binary_function< pair< T, U >, pair< T, U >, bool >
//STRIP001 {
//STRIP001     inline bool operator() ( const pair< T, U > & rOne, const pair< T, U > & rOther )
//STRIP001     {
//STRIP001         return ( rOne.first < rOther.first );
//STRIP001     }
//STRIP001 };
//STRIP001
//STRIP001 template< typename T >
//STRIP001     struct lcl_EqualsFirstDoubleOfPair : binary_function< pair< double, T >, pair< double, T >, bool >
//STRIP001 {
//STRIP001     inline bool operator() ( const pair< double, T > & rOne, const pair< double, T > & rOther )
//STRIP001     {
//STRIP001         return ( ::rtl::math::approxEqual( rOne.first, rOther.first ) );
//STRIP001     }
//STRIP001 };
//STRIP001
//STRIP001 // assume Point given in 100th of a mm
//STRIP001 struct lcl_EqualsPointWithDPI : binary_function< Point, Point, bool >
//STRIP001 {
//STRIP001     lcl_EqualsPointWithDPI( long nDPIX, long nDPIY ) :
//STRIP001             m_fFactX( static_cast< double >( nDPIX ) / 2540.0 ),
//STRIP001             m_fFactY( static_cast< double >( nDPIY ) / 2540.0 )
//STRIP001     {}
//STRIP001
//STRIP001     inline bool operator() ( const Point & p1, const Point & p2 )
//STRIP001     {
//STRIP001         bool bXEqual = false;
//STRIP001         bool bYEqual = false;
//STRIP001         if( m_fFactX > 0 )
//STRIP001         {
//STRIP001             bXEqual =
//STRIP001                 ( static_cast< long >( static_cast< double >( p1.getX()) * m_fFactX ) ==
//STRIP001                   static_cast< long >( static_cast< double >( p2.getX()) * m_fFactX ) );
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             bXEqual = ( p1.getX() == p2.getX() );
//STRIP001         }
//STRIP001
//STRIP001         if( bXEqual )
//STRIP001         {
//STRIP001             if( m_fFactY > 0 )
//STRIP001             {
//STRIP001                 bYEqual =
//STRIP001                     ( static_cast< long >( static_cast< double >( p1.getY()) * m_fFactY ) ==
//STRIP001                       static_cast< long >( static_cast< double >( p2.getY()) * m_fFactY ) );
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 bYEqual = ( p1.getY() == p2.getY() );
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         return bXEqual && bYEqual;
//STRIP001     }
//STRIP001
//STRIP001 private:
//STRIP001     double m_fFactX;
//STRIP001     double m_fFactY;
//STRIP001 };
//STRIP001
//STRIP001 lcl_SplineCalculation::lcl_SplineCalculation(
//STRIP001     const tPointVecType & rPoints,
//STRIP001     double fY1FirstDerivation,
//STRIP001     double fYnFirstDerivation )
//STRIP001         : m_aPoints( rPoints ),
//STRIP001           m_fYp1( fY1FirstDerivation ),
//STRIP001           m_fYpN( fYnFirstDerivation ),
//STRIP001           m_nKLow( 0 ),
//STRIP001           m_nKHigh( rPoints.size() - 1 )
//STRIP001 {
//STRIP001     ::rtl::math::setInf( &m_fLastInterpolatedValue, sal_False );
//STRIP001
//STRIP001     sort( m_aPoints.begin(), m_aPoints.end(),
//STRIP001           lcl_LessFirstOfPair< double, double >() );
//STRIP001
//STRIP001     // #108301# remove points that have equal x-values
//STRIP001     m_aPoints.erase( unique( m_aPoints.begin(), m_aPoints.end(),
//STRIP001                              lcl_EqualsFirstDoubleOfPair< double >() ),
//STRIP001                      m_aPoints.end() );
//STRIP001
//STRIP001     Calculate();
//STRIP001 }
//STRIP001
//STRIP001 void lcl_SplineCalculation::Calculate()
//STRIP001 {
//STRIP001     // n is the last valid index to m_aPoints
//STRIP001     const tPointVecType::size_type n = m_aPoints.size() - 1;
//STRIP001     vector< double > u( n );
//STRIP001     m_aSecDerivY.resize( n + 1, 0.0 );
//STRIP001
//STRIP001     if( ::rtl::math::isInf( m_fYp1 ) )
//STRIP001     {
//STRIP001         // natural spline
//STRIP001         m_aSecDerivY[ 0 ] = 0.0;
//STRIP001         u[ 0 ] = 0.0;
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         m_aSecDerivY[ 0 ] = -0.5;
//STRIP001         double xDiff = ( m_aPoints[ 1 ].first - m_aPoints[ 0 ].first );
//STRIP001         u[ 0 ] = ( 3.0 / xDiff ) *
//STRIP001             ((( m_aPoints[ 1 ].second - m_aPoints[ 0 ].second ) / xDiff ) - m_fYp1 );
//STRIP001     }
//STRIP001
//STRIP001     for( tPointVecType::size_type i = 1; i < n; ++i )
//STRIP001     {
//STRIP001         pair< double, double >
//STRIP001             p_i = m_aPoints[ i ],
//STRIP001             p_im1 = m_aPoints[ i - 1 ],
//STRIP001             p_ip1 = m_aPoints[ i + 1 ];
//STRIP001
//STRIP001         double sig = ( p_i.first - p_im1.first ) /
//STRIP001             ( p_ip1.first - p_im1.first );
//STRIP001         double p = sig * m_aSecDerivY[ i - 1 ] + 2.0;
//STRIP001
//STRIP001         m_aSecDerivY[ i ] = ( sig - 1.0 ) / p;
//STRIP001         u[ i ] =
//STRIP001             ( ( p_ip1.second - p_i.second ) /
//STRIP001               ( p_ip1.first - p_i.first ) ) -
//STRIP001             ( ( p_i.second - p_im1.second ) /
//STRIP001               ( p_i.first - p_im1.first ) );
//STRIP001         u[ i ] =
//STRIP001             ( 6.0 * u[ i ] / ( p_ip1.first - p_im1.first )
//STRIP001               - sig * u[ i - 1 ] ) / p;
//STRIP001     }
//STRIP001
//STRIP001     // initialize to values for natural splines (used for m_fYpN equal to
//STRIP001     // infinity)
//STRIP001     double qn = 0.0;
//STRIP001     double un = 0.0;
//STRIP001
//STRIP001     if( ! ::rtl::math::isInf( m_fYpN ) )
//STRIP001     {
//STRIP001         qn = 0.5;
//STRIP001         double xDiff = ( m_aPoints[ n ].first - m_aPoints[ n - 1 ].first );
//STRIP001         un = ( 3.0 / xDiff ) *
//STRIP001             ( m_fYpN - ( m_aPoints[ n ].second - m_aPoints[ n - 1 ].second ) / xDiff );
//STRIP001     }
//STRIP001
//STRIP001     m_aSecDerivY[ n ] = ( un - qn * u[ n - 1 ] ) * ( qn * m_aSecDerivY[ n - 1 ] + 1.0 );
//STRIP001
//STRIP001     // note: the algorithm in [1] iterates from n-1 to 0, but as size_type
//STRIP001     // may be (usuall is) an unsigned type, we can not write k >= 0, as this
//STRIP001     // is always true.
//STRIP001     for( tPointVecType::size_type k = n; k > 0; --k )
//STRIP001     {
//STRIP001         ( m_aSecDerivY[ k - 1 ] *= m_aSecDerivY[ k ] ) += u[ k - 1 ];
//STRIP001     }
//STRIP001 }
//STRIP001
//STRIP001 double lcl_SplineCalculation::GetInterpolatedValue( double x )
//STRIP001 {
//STRIP001     DBG_ASSERT( ( m_aPoints[ 0 ].first <= x ) &&
//STRIP001                 ( x <= m_aPoints[ m_aPoints.size() - 1 ].first ),
//STRIP001                 "Trying to extrapolate" );
//STRIP001
//STRIP001     const tPointVecType::size_type n = m_aPoints.size() - 1;
//STRIP001     if( x < m_fLastInterpolatedValue )
//STRIP001     {
//STRIP001         m_nKLow = 0;
//STRIP001         m_nKHigh = n;
//STRIP001
//STRIP001         // calculate m_nKLow and m_nKHigh
//STRIP001         // first initialization is done in CTOR
//STRIP001         while( m_nKHigh - m_nKLow > 1 )
//STRIP001         {
//STRIP001             tPointVecType::size_type k = ( m_nKHigh + m_nKLow ) / 2;
//STRIP001             if( m_aPoints[ k ].first > x )
//STRIP001                 m_nKHigh = k;
//STRIP001             else
//STRIP001                 m_nKLow = k;
//STRIP001         }
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         while( ( m_aPoints[ m_nKHigh ].first < x ) &&
//STRIP001                ( m_nKHigh <= n ) )
//STRIP001         {
//STRIP001             ++m_nKHigh;
//STRIP001             ++m_nKLow;
//STRIP001         }
//STRIP001         DBG_ASSERT( m_nKHigh <= n, "Out of Bounds" );
//STRIP001     }
//STRIP001     m_fLastInterpolatedValue = x;
//STRIP001
//STRIP001     double h = m_aPoints[ m_nKHigh ].first - m_aPoints[ m_nKLow ].first;
//STRIP001     DBG_ASSERT( h != 0, "Bad input to GetInterpolatedValue()" );
//STRIP001
//STRIP001     double a = ( m_aPoints[ m_nKHigh ].first - x ) / h;
//STRIP001     double b = ( x - m_aPoints[ m_nKLow ].first  ) / h;
//STRIP001
//STRIP001     return ( a * m_aPoints[ m_nKLow ].second +
//STRIP001              b * m_aPoints[ m_nKHigh ].second +
//STRIP001              (( a*a*a - a ) * m_aSecDerivY[ m_nKLow ] +
//STRIP001               ( b*b*b - b ) * m_aSecDerivY[ m_nKHigh ] ) *
//STRIP001              ( h*h ) / 6.0 );
//STRIP001 }
//STRIP001
//STRIP001 typedef lcl_SplineCalculation::tPointVecType::size_type lcl_tSizeType;
//STRIP001
//STRIP001 // this is the maximum number of points that will be inserted into an XPolygon
//STRIP001 const lcl_tSizeType nPolygonSizeThreshold = 0xff00;
//STRIP001
//STRIP001 } //  anonymous namespace

// ----------------------------------------

//STRIP001 void SchCalculationHelper::CalculateCubicSplines(
//STRIP001     const vector< pair< double, double > > & rPoints,
//STRIP001     sal_Int32 nGranularity,
//STRIP001     XPolyPolygon & rOutResult,
//STRIP001     long nDPIX /* = 0 */, long nDPIY /* = 0 */ )
//STRIP001 {
//STRIP001  RTL_LOGFILE_CONTEXT_AUTHOR( context, "sch", "bm93744", "SchCalculationHelper::CalculateCubicSplines");
//STRIP001
//STRIP001     DBG_ASSERT( nGranularity != 0, "Zero-Granularity is invalid" );
//STRIP001     rOutResult.Clear();
//STRIP001
//STRIP001     // calculate second derivates
//STRIP001     double fInfty;
//STRIP001     ::rtl::math::setInf( &fInfty, sal_False );
//STRIP001     lcl_SplineCalculation aSpline( rPoints, fInfty, fInfty );
//STRIP001
//STRIP001     // fill result polygon with calculated values
//STRIP001     lcl_tSizeType nLastIndex = rPoints.size() - 1;
//STRIP001
//STRIP001     // calculate all necessary points on spline curve
//STRIP001     vector< Point > aCalculatedPoints;
//STRIP001     aCalculatedPoints.reserve( nLastIndex * nGranularity + 1 );
//STRIP001 #ifdef SPLINE_OPTIMIZE_POINTS
//STRIP001     long nLastX = -1;
//STRIP001 #else
//STRIP001     Point aLast( -1, -1 );
//STRIP001 #endif
//STRIP001
//STRIP001     for( lcl_tSizeType i = 0; i < nLastIndex; ++i )
//STRIP001     {
//STRIP001         double fBaseX = rPoints[ i ].first;
//STRIP001         double fInc = ( rPoints[ i + 1 ].first - fBaseX ) /
//STRIP001             static_cast< double >( nGranularity );
//STRIP001
//STRIP001         for( sal_Int32 j = 0; j < nGranularity; ++j )
//STRIP001         {
//STRIP001             double x = fBaseX + ( fInc * static_cast< double >( j ) );
//STRIP001             Point aPoint( static_cast< long >( x ),
//STRIP001                           static_cast< long >( aSpline.GetInterpolatedValue( x )));
//STRIP001 #ifdef SPLINE_OPTIMIZE_POINTS
//STRIP001             if( aPoint.getX() != nLastX )
//STRIP001             {
//STRIP001                 aCalculatedPoints.push_back( aPoint );
//STRIP001                 nLastX = aPoint.getX();
//STRIP001             }
//STRIP001 #else
//STRIP001             if( aPoint != aLast )
//STRIP001             {
//STRIP001                 aCalculatedPoints.push_back( aPoint );
//STRIP001                 aLast = aPoint;
//STRIP001             }
//STRIP001 #endif
//STRIP001         }
//STRIP001     }
//STRIP001     // calculate last point
//STRIP001     Point aPoint( static_cast< long >( rPoints[ nLastIndex ].first ),
//STRIP001                   static_cast< long >( aSpline.GetInterpolatedValue( rPoints[ nLastIndex ].first )));
//STRIP001 #ifdef SPLINE_OPTIMIZE_POINTS
//STRIP001     if( aPoint.getX() != nLastX )
//STRIP001         aCalculatedPoints.push_back( aPoint );
//STRIP001 #else
//STRIP001     if( aPoint != aLast )
//STRIP001         aCalculatedPoints.push_back( aPoint );
//STRIP001 #endif
//STRIP001
//STRIP001     OSL_TRACE( "Used points: %u of %u (skipped %u)",
//STRIP001                aCalculatedPoints.size(),
//STRIP001                nLastIndex * nGranularity + 1,
//STRIP001                nLastIndex * nGranularity + 1 - aCalculatedPoints.size() );
//STRIP001
//STRIP001     if( nDPIX > 0 || nDPIY > 0 )
//STRIP001     {
//STRIP001         size_t nOldSize = aCalculatedPoints.size();
//STRIP001         OSL_TRACE( "Reducing with %u x %u DPI", nDPIX, nDPIY );
//STRIP001         aCalculatedPoints.erase(
//STRIP001             unique( aCalculatedPoints.begin(), aCalculatedPoints.end(),
//STRIP001                     lcl_EqualsPointWithDPI( nDPIX, nDPIY ) ),
//STRIP001             aCalculatedPoints.end() );
//STRIP001         OSL_TRACE( "Used points: %u (removed: %u)",
//STRIP001                    aCalculatedPoints.size(),
//STRIP001                    nOldSize - aCalculatedPoints.size());
//STRIP001     }
//STRIP001
//STRIP001     // put calculated points into XPolygons that are put into an XPolyPolygon
//STRIP001
//STRIP001     // note: the threshold should be strictly smaller than the maximum capacity
//STRIP001     // of an XPolygon
//STRIP001     XPolygon aCurrentPolygon( static_cast< USHORT >(
//STRIP001                                   min< lcl_tSizeType >( aCalculatedPoints.size(),
//STRIP001                                                         nPolygonSizeThreshold )));
//STRIP001     aCurrentPolygon[ 0 ] = aCalculatedPoints[ 0 ];
//STRIP001     USHORT nIndexInPolygon = 1;
//STRIP001     for( vector< Point >::const_iterator aIt = aCalculatedPoints.begin();
//STRIP001          aIt != aCalculatedPoints.end(); ++aIt )
//STRIP001     {
//STRIP001         aCurrentPolygon[ nIndexInPolygon ] = (*aIt);
//STRIP001         if( ( ++nIndexInPolygon % nPolygonSizeThreshold ) == 0 )
//STRIP001         {
//STRIP001             rOutResult.Insert( aCurrentPolygon, XPOLYPOLY_APPEND );
//STRIP001             aCurrentPolygon[ 0 ] = (*aIt);
//STRIP001             nIndexInPolygon = 1;
//STRIP001         }
//STRIP001     }
//STRIP001     if( nIndexInPolygon > 1 )
//STRIP001     {
//STRIP001         aCurrentPolygon.SetSize( nIndexInPolygon );
//STRIP001         rOutResult.Insert( aCurrentPolygon, XPOLYPOLY_APPEND );
//STRIP001     }
//STRIP001
//STRIP001     OSL_TRACE( "CalculateCubicSplines: result has %d polygons", rOutResult.Count() );
//STRIP001 }
}
