/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: AccessibleStringWrap.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 21:06:08 $
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

#ifndef _ACCESSIBLESTRINGWRAP_HXX
#define _ACCESSIBLESTRINGWRAP_HXX

#ifndef _SAL_TYPES_H_
#include <sal/types.h>
#endif

#ifndef _STRING_HXX
#include <tools/string.hxx>
#endif
class OutputDevice;
class Rectangle;
class Point;
namespace binfilter {


class SvxFont;

//------------------------------------------------------------------------
//
// AccessibleStringWrap declaration
//
//------------------------------------------------------------------------

class AccessibleStringWrap
{
public:

    AccessibleStringWrap( OutputDevice& rDev, SvxFont& rFont, const String& rText ){DBG_BF_ASSERT(0, "STRIP");}//STRIP001 AccessibleStringWrap( OutputDevice& rDev, SvxFont& rFont, const String& rText );

    sal_Bool GetCharacterBounds( sal_Int32 nIndex, Rectangle& rRect ){DBG_BF_ASSERT(0, "STRIP"); return false;}//STRIP001 sal_Bool GetCharacterBounds( sal_Int32 nIndex, Rectangle& rRect );
    sal_Int32 GetIndexAtPoint( const Point& rPoint ){DBG_BF_ASSERT(0, "STRIP"); return 0;}//STRIP001 sal_Int32 GetIndexAtPoint( const Point& rPoint );

private:

};

}//end of namespace binfilter
#endif /* _ACCESSIBLESTRINGWRAP_HXX */
