/*************************************************************************
 *
 *  $RCSfile: sch_ChXChartDataChangeEventListener.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:34:04 $
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

// header for class Application
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif
// header for class OGuard
#ifndef _VOS_MUTEX_HXX_
#include <vos/mutex.hxx>
#endif

#include "ChXChartDataChangeEventListener.hxx"
#include "ChXChartDocument.hxx"
namespace binfilter {

#ifndef SCH_ASCII_TO_OU
#define SCH_ASCII_TO_OU( s )  ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( s ) )
#endif

// using namespace osl;
using namespace rtl;
using namespace vos;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star;

ChXChartDataChangeEventListener::ChXChartDataChangeEventListener()
{
    mpXDoc = NULL;
}

void ChXChartDataChangeEventListener::SetOwner( ChXChartDocument* pXDoc ) throw()
{
    OGuard aGuard( Application::GetSolarMutex() );

    mpXDoc = pXDoc;
}

void ChXChartDataChangeEventListener::Reset() throw()
{
    OGuard aGuard( Application::GetSolarMutex() );
    mpXDoc = NULL;
}

// XChartDataChangeEventListener
void SAL_CALL ChXChartDataChangeEventListener::chartDataChanged( const chart::ChartDataChangeEvent& aEvent )
    throw( uno::RuntimeException )
{
    OGuard aGuard( Application::GetSolarMutex() );
    if( mpXDoc )
        mpXDoc->RefreshData( aEvent );
}

// XEventListener
void SAL_CALL ChXChartDataChangeEventListener::disposing( const lang::EventObject& Source ) throw( uno::RuntimeException )
{
    Reset();
}

// XServiceInfo
::rtl::OUString SAL_CALL ChXChartDataChangeEventListener::getImplementationName() throw( uno::RuntimeException )
{
    return SCH_ASCII_TO_OU( "ChXChartDataChangeEventListener" );
}

sal_Bool SAL_CALL ChXChartDataChangeEventListener::supportsService( const OUString& ServiceName )
    throw( uno::RuntimeException )
{
    uno::Sequence< OUString > aSNL = getSupportedServiceNames();
    const OUString * pArray = aSNL.getConstArray();
    for( INT32 i = 0; i < aSNL.getLength(); i++ )
        if( pArray[i] == ServiceName )
            return TRUE;
    return FALSE;
}

uno::Sequence< ::rtl::OUString > SAL_CALL ChXChartDataChangeEventListener::getSupportedServiceNames()
    throw( uno::RuntimeException )
{
    OGuard aGuard( Application::GetSolarMutex() );

    uno::Sequence< OUString > aServSeq( 0 );
    return aServSeq;
}

}
