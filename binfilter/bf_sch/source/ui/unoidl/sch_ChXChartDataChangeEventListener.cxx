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

#include <vcl/svapp.hxx>
#include <osl/mutex.hxx>

#include "ChXChartDataChangeEventListener.hxx"
#include "ChXChartDocument.hxx"
namespace binfilter {

#ifndef SCH_ASCII_TO_OU
#define SCH_ASCII_TO_OU( s )  ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( s ) )
#endif

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star;
using ::rtl::OUString;

ChXChartDataChangeEventListener::ChXChartDataChangeEventListener()
{
    mpXDoc = NULL;
}

void ChXChartDataChangeEventListener::SetOwner( ChXChartDocument* pXDoc ) throw()
{
    SolarMutexGuard aGuard;

    mpXDoc = pXDoc;
}

void ChXChartDataChangeEventListener::Reset() throw()
{
    SolarMutexGuard aGuard;
    mpXDoc = NULL;
}

// XChartDataChangeEventListener
void SAL_CALL ChXChartDataChangeEventListener::chartDataChanged( const chart::ChartDataChangeEvent& aEvent )
    throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;
    if( mpXDoc )
        mpXDoc->RefreshData( aEvent );
}

// XEventListener
void SAL_CALL ChXChartDataChangeEventListener::disposing( const lang::EventObject& /*Source*/ ) throw( uno::RuntimeException )
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
    SolarMutexGuard aGuard;

    uno::Sequence< OUString > aServSeq( 0 );
    return aServSeq;
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
