/*************************************************************************
 *
 *  $RCSfile: calculat.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:25:23 $
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

// header for BOOL
#ifndef _SOLAR_H
#include <tools/solar.h>
#endif

#include <vector>
#include <utility>
class Point;
class Rectangle;
namespace binfilter {

class Line;
class XPolygon;
class XPolyPolygon;

/** @descr  This class clips single lines and polygons at a given rectangle.
        All of it's methods are static, therefore no object has to be created.

        It uses the Liang-Biarsky parametric line-clipping algorithm as described in:
            Computer Graphics: principles and practice, 2nd ed.,
            James D. Foley et al.,
            Section 3.12.4 on page 117.
*/
class SchCalculationHelper
{
public:
    /** like Rectangle::IsInside, but the result is FALSE, if
        the Point is on the Border of the Rectangle
     */
//  static BOOL IsPointInsideRectangle( const Point& rPoint, const Rectangle& rRect );

    /** @descr  The line is clipped at the rectangle.  If the line lies completely or partly
             inside the clipping area then TRUE is returned and the line is modified accordingly.
             If the line lies completely outside the clipping area then FALSE is returned and the
             line remains unmodified.
             The line may be degenerate in that both of it's end points have the same
             coordinates.
        @param  aLine   The line to be clipped.  It is modified to a part that lies completely
            inside the clipping area if such a part exists.
        @param  rRectangle  The clipping area.
        @return TRUE is returned if the line lies completely or partly inside the clipping area.
     */
//STRIP001  static BOOL ClipLineAtRectangle( Line& aLine, const Rectangle& rRectangle );

    /** @descr  The intersection between an open polygon and a rectangle is
            calculated and the resulting lines are placed into the poly-polygon aResult.
        @param  rPolygon    The polygon is required to be open, ie. it's start and end point
            have different coordinates and that it is continuous, ie. has no holes.
        @param  rRectangle  The clipping area.
        @param  aResult The resulting lines that are the parts of the given polygon lying inside
            the clipping area are stored into aResult whose prior content is deleted first.
     */
    static void IntersectPolygonWithRectangle( const XPolygon& rPolygon, const Rectangle& rRectangle,
                                               XPolyPolygon& aResult );

    /** @descr Calculates the intersection between a set of open polygons and a
               rectangle.  This function iterates over all polygons contained in
               rPolyPolygon and calls IntersectPolygonWithRectangle() for it.
               The resulting XPolyPolygons are then put together into aResult.
        @param rPolyPolygon  A set of polygons that must be open.
        @param rRectangle    The clipping region
        @param rOutResult    The resulting lines representing rPolyPolygon clipped
                             at rRectangle.
     */
//STRIP001     static void IntersectPolyPolygonWithRectangle( const XPolyPolygon & rPolyPolygon,
//STRIP001                                                    const Rectangle & rRectangle,
//STRIP001                                                    XPolyPolygon & rOutResult );

    /** @descr calculates natural cubic splines for the given set of points.

        @param rPoints is a vector of tuples containing x and y coordinate of
               points that are to be interpolated.
        @param nGranularity The number of interpolation points between two
               x-values given in rPoints

        @param rOutResult A polygon (split up into more, if the number of points
               is too high as to fit into a single XPolygon) that contains all
               line segments between the interpolated points.  It should contain
               (rPoints.size() * nGranularity) points.

        @param nDPIX resolution in x-direction to reduce the number of points.
               A value of 0 (default) means do not take into account.

        @param nDPIY resolution in y-direction to reduce the number of points.
               A value of 0 (default) means do not take into account.
     */
//STRIP001     static void CalculateCubicSplines( const ::std::vector< ::std::pair< double, double > > & rPoints,
//STRIP001                                        sal_Int32 nGranularity,
//STRIP001                                        XPolyPolygon & rOutResult,
//STRIP001                                        long nDPIX = 0, long nDPIY = 0 );

private:
    /** @descr  The line given by it's two endpoints rP0 and rP1 is clipped at the rectangle
            rRectangle.  If there is at least a part of it visible then TRUE is returned and
            the endpoints of that part are stored in rP0 and rP1.  The points rP0 and rP1
            may have the same coordinates.
        @param  rP0 Start point of the line to clip.  Modified to contain a start point inside
            the clipping area if possible.
        @param  rP1 End point of the line to clip.  Modified to contain an end point inside
            the clipping area if possible.
        @param  rRectangle Clipping area.
        @return If the line lies completely or partly inside the clipping area then TRUE
            is returned.  If the line lies completely outside then FALSE is returned and rP0 and
            rP1 are left unmodified.
    */
    static  BOOL    clip2d  (Point & rP0, Point & rP1, const Rectangle& rRectangle);

    /** @descr  This is a supporting function for clip2d.  It computes a new parametric
            value for an entering (dTE) or leaving (dTL) intersection point with one
            of the edges bounding the clipping area.
            For explanation of the parameters please refer to the literature reference
            given above.
    */
    static  BOOL    CLIPt   (double fDenom, double fNum, double & fTE, double & fTL);
};

} //namespace binfilter