/*************************************************************************
 *
 *  $RCSfile: sch_ChartLine.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 13:23:31 $
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
#include "ChartLine.hxx"

#include "mapprov.hxx"
// auto strip #include "defines.hxx"

// header for class OGuard
#ifndef _VOS_MUTEX_HXX_
#include <vos/mutex.hxx>
#endif
// header for class Application
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif
#ifndef _RTL_UUID_H_
#include <rtl/uuid.h>
#endif
// auto strip #ifndef _CPPUHELPER_QUERYINTERFACE_HXX_
// auto strip #include <cppuhelper/queryinterface.hxx>
// auto strip #endif
namespace binfilter {

using namespace ::com::sun::star;

ChartLine::ChartLine( ChartModel* pModel, sal_Int32 nObjectId, sal_Int32 nIndex ) :
        ChXChartObject( CHMAP_LINE, pModel, nObjectId, nIndex )
{
}

ChartLine::~ChartLine()
{}

// XServiceInfo
::rtl::OUString SAL_CALL ChartLine::getImplementationName()
    throw( uno::RuntimeException )
{
    return ::rtl::OUString::createFromAscii( "ChartLine" );
}

uno::Sequence< ::rtl::OUString > SAL_CALL ChartLine::getSupportedServiceNames()
    throw( uno::RuntimeException )
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    uno::Sequence< ::rtl::OUString > aSeq( 3 );
    aSeq[ 0 ] = ::rtl::OUString::createFromAscii( "com.sun.star.chart.ChartLine" );
    aSeq[ 1 ] = ::rtl::OUString::createFromAscii( "com.sun.star.drawing.LineProperties" );
    aSeq[ 2 ] = ::rtl::OUString::createFromAscii( "com.sun.star.xml.UserDefinedAttributeSupplier" );

    return aSeq;
}

// XTypeProvider
uno::Sequence< sal_Int8 > SAL_CALL ChartLine::getImplementationId()
    throw( uno::RuntimeException )
{
    static uno::Sequence< sal_Int8 > aId;
    if( aId.getLength() == 0 )
    {
        aId.realloc( 16 );
        rtl_createUuid( (sal_uInt8 *)aId.getArray(), 0, sal_True );
    }
    return aId;
}

// XShapeDescriptor
::rtl::OUString SAL_CALL ChartLine::getShapeType()
    throw( uno::RuntimeException )
{
    return ::rtl::OUString::createFromAscii( "com.sun.star.chart.ChartLine" );
}

// XUnoTunnel
sal_Int64 SAL_CALL ChartLine::getSomething( const uno::Sequence< sal_Int8 >& aIdentifier )
    throw( uno::RuntimeException )
{
    if( aIdentifier.getLength() == 16 && 0 == rtl_compareMemory( getUnoTunnelId().getConstArray(),
                                                                 aIdentifier.getConstArray(), 16 ) )
    {
        return (sal_Int64)this;
    }
    return ChXChartObject::getSomething( aIdentifier );
}

// helpers for XUnoTunnel
const uno::Sequence< sal_Int8 > & ChartLine::getUnoTunnelId() throw()
{
    static uno::Sequence< sal_Int8 > * pSeq = 0;
    if( !pSeq )
    {
        osl::Guard< osl::Mutex > aGuard( osl::Mutex::getGlobalMutex() );
        if( !pSeq )
        {
            static uno::Sequence< sal_Int8 > aSeq( 16 );
            rtl_createUuid( (sal_uInt8*)aSeq.getArray(), 0, sal_True );
            pSeq = &aSeq;
        }
    }
    return *pSeq;
}

ChartLine* ChartLine::getImplementation( uno::Reference< uno::XInterface > xData ) throw()
{
    uno::Reference< lang::XUnoTunnel > xUT( xData, uno::UNO_QUERY );
    if( xUT.is() )
        return (ChartLine*)xUT->getSomething( ChartLine::getUnoTunnelId() );
    else
        return NULL;
}
}
