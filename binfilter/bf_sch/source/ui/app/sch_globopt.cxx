/*************************************************************************
 *
 *  $RCSfile: sch_globopt.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:32:50 $
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
 *  Copyright: 2002 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/
#include "globopt.hxx"

#include <stdio.h>

#ifndef INCLUDED_SVTOOLS_SYSLOCALE_HXX
#include <svtools/syslocale.hxx>
#endif
#ifndef _UTL_CONFIGITEM_HXX_
#include <unotools/configitem.hxx>
#endif
namespace binfilter {

// ================================================================================

/*N*/ namespace
/*N*/ {
/*N*/
/*N*/ bool IsMetric()
/*N*/ {
/*N*/     SvtSysLocale aSysLocale;
/*N*/     const LocaleDataWrapper* pLocWrapper = aSysLocale.GetLocaleDataPtr();
/*N*/     MeasurementSystem eSys = pLocWrapper->getMeasurementSystemEnum();
/*N*/
/*N*/     return ( eSys == MEASURE_METRIC );
/*N*/ }

// ----------------------------------------

/*N*/ class CalcConfigItem : public ::utl::ConfigItem
/*N*/ {
/*N*/ public:
/*N*/     CalcConfigItem() :
/*N*/             ConfigItem( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "Office.Calc/Layout" )))
/*N*/     {}
/*N*/
/*N*/     FieldUnit GetMeasureUnit();
/*N*/ };

/*N*/ FieldUnit CalcConfigItem::GetMeasureUnit()
/*N*/ {
/*N*/     FieldUnit eResult( FUNIT_CM );
/*N*/
/*N*/     ::com::sun::star::uno::Sequence< ::rtl::OUString > aNames( 1 );
/*N*/     if( IsMetric() )
/*N*/         aNames[ 0 ] = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "Other/MeasureUnit/Metric" ));
/*N*/     else
/*N*/         aNames[ 0 ] = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "Other/MeasureUnit/NonMetric" ));
/*N*/
/*N*/     ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any > aResult(
/*N*/         GetProperties( aNames ));
/*N*/
/*N*/     if( aResult[ 0 ].hasValue() )
/*N*/     {
/*N*/         sal_Int32 nValue;
/*N*/         aResult[ 0 ] >>= nValue;
/*N*/         eResult = static_cast< FieldUnit >( nValue );
/*N*/     }
/*N*/
/*N*/     return eResult;
/*N*/ }


}  // anonymous namespace

// ================================================================================

namespace sch
{

namespace util
{

/*N*/ FieldUnit GetMeasureUnit()
/*N*/ {
/*N*/     static CalcConfigItem aCfgItem;
/*N*/     FieldUnit aUnit( aCfgItem.GetMeasureUnit() );
/*N*/
/*N*/     return aCfgItem.GetMeasureUnit();
/*N*/ }

}  // namespace util
}  // namespace sch
}
