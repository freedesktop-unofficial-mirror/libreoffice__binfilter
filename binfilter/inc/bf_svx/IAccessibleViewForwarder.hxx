/*************************************************************************
 *
 *  $RCSfile: IAccessibleViewForwarder.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:27:24 $
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

#ifndef _SVX_ACCESSIBILITY_IACCESSIBLE_VIEW_FORWARDER_HXX
#define _SVX_ACCESSIBILITY_IACCESSIBLE_VIEW_FORWARDER_HXX

#ifndef _SAL_TYPES_H_
#include <sal/types.h>
#endif

#ifndef _SV_GEN_HXX
#include <tools/gen.hxx>
#endif
namespace binfilter {

namespace accessibility {

/** <p>This interface provides the means to transform between internal
    coordinates in 100th of mm and screen coordinates without giving direct
    access to the underlying view.  Each view forwarder represents a
    specific real or virtual window.  A call to
    <method>GetVisibleArea</method> returns the visible rectangle that
    corresponds to this window.</p>

    <p>This interface is similar to the <type>SvxViewForwarder</type> but
    differs in two important points: Firstly the <member>GetVisArea</member>
    method returns a rectangle in internal coordinates and secondly the
    transformation methods do not require explicit mapmodes.  These have to
    be provided implicitely by the classes that implement this
    interface.  A third, less important, difference are the additional
    transfomation methods for sizes.  The reasons for their existince are
    convenience and improved performance.</p>

    @attention
        Note, that modifications of the underlying view that lead to
        different transformations between internal and screen coordinates or
        change the validity of the forwarder have to be signaled seperately.
*/
class IAccessibleViewForwarder
{
public:
    virtual ~IAccessibleViewForwarder (void){};

    /** This method informs you about the state of the forwarder.  Do not
        use it when the returned value is <false/>.

        @return
            Return <true/> if the view forwarder is valid and <false/> else.
     */
    virtual sal_Bool IsValid (void) const = 0;

    /** Returns the area of the underlying document that is visible in the
    * corresponding window.

        @return
            The rectangle of the visible part of the document. The values
            are, contrary to the base class, in internal coordinates of
            100th of mm.
     */
    virtual Rectangle GetVisibleArea() const = 0;

    /** Transform the specified point from internal coordinates in 100th of
        mm to an absolute screen position.

        @param rPoint
            Point in internal coordinates (100th of mm).

        @return
            The same point but in screen coordinates relative to the upper
            left corner of the (current) screen.
     */
    virtual Point LogicToPixel (const Point& rPoint) const = 0;

    /** Transform the specified size from internal coordinates in 100th of
        mm to a screen oriented pixel size.

        @param rSize
            Size in internal coordinates (100th of mm).

        @return
            The same size but in screen coordinates.
     */
    virtual Size LogicToPixel (const Size& rSize) const = 0;

    /** Transform the specified point from absolute screen coordinates to
        internal coordinates (100th of mm).

        @param rPoint
            Point in screen coordinates relative to the upper left corner of
            the (current) screen.

        @return
            The same point but in internal coordinates (100th of mm).
     */
    virtual Point PixelToLogic (const Point& rPoint) const = 0;

    /** Transform the specified size from screen coordinates to internal
        coordinates (100th of mm).

        @param rSize
            Size in screen coordinates.

        @return
            The same size but in internal coordinates (100th of mm).
     */
    virtual Size PixelToLogic (const Size& rSize) const = 0;
};

} // end of namespace accessibility

}//end of namespace binfilter
#endif
