/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: globopt.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 22:55:51 $
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
#ifndef _SCH_GLOBOPT_HXX
#define _SCH_GLOBOPT_HXX

#ifndef _VCL_FLDUNIT_HXX
#include <vcl/fldunit.hxx>
#endif
namespace binfilter {

namespace sch
{

namespace util
{

/** @descr Retrieve the FieldUnit to be used for the UI.  This unit is retrieved
    from the registry settings of the Calc application.

    If this setting can not be found there is a fallback to cm which is the most
    common setting worldwide (or not?)

    @return the FieldUnit enum.  See <vcl/fldunit.hxx> for definition
 */
FieldUnit GetMeasureUnit();

}  // namespace util
}  // namespace sch


// _SCH_GLOBOPT_HXX
} //namespace binfilter
#endif
