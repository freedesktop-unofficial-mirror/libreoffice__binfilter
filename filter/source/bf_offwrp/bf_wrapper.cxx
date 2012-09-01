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

#include <bf_wrapper.hxx>

#include <bf_offmgr/app.hxx>
#include <bf_sw/swdll.hxx>
#include <bf_sc/scdll.hxx>
#include <bf_sd/sddll.hxx>
#include <bf_sch/schdll.hxx>
#include <bf_starmath/smdll.hxx>
#include <bf_svx/svdetc.hxx>
#include <bf_svx/itemdata.hxx>
#include <framework/imageproducer.hxx>

#include <bf_svtools/moduleoptions.hxx>

// #i30187#
#include <osl/mutex.hxx>

namespace binfilter {

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::registry;

static SwDLL*               pSwDLL = 0L;
static SdDLL*               pSdDLL = 0L;
static ScDLL*               pScDLL = 0L;
static SchDLL*              pSchDLL = 0L;
static SmDLL*               pSmDLL = 0L;
static bf_OfficeWrapper*    pOfficeWrapper = 0L;

/* XServiceInfo */
UNOOUSTRING SAL_CALL bf_OfficeWrapper::getImplementationName() throw( UNORUNTIMEEXCEPTION )
{
    return impl_getStaticImplementationName();
}

/* XServiceInfo */
sal_Bool SAL_CALL bf_OfficeWrapper::supportsService( const UNOOUSTRING& sServiceName ) throw( UNORUNTIMEEXCEPTION )
{
    UNOSEQUENCE< UNOOUSTRING >  seqServiceNames =   getSupportedServiceNames();
    const UNOOUSTRING*          pArray          =   seqServiceNames.getConstArray();
    for ( sal_Int32 nCounter=0; nCounter<seqServiceNames.getLength(); nCounter++ )
    {
        if ( pArray[nCounter] == sServiceName )
        {
            return sal_True ;
        }
    }
    return sal_False ;
}

/* XServiceInfo */
UNOSEQUENCE< UNOOUSTRING > SAL_CALL bf_OfficeWrapper::getSupportedServiceNames() throw( UNORUNTIMEEXCEPTION )
{
    return impl_getStaticSupportedServiceNames();
}

/* Helper for XServiceInfo */
UNOSEQUENCE< UNOOUSTRING > bf_OfficeWrapper::impl_getStaticSupportedServiceNames()
{
    UNOMUTEXGUARD aGuard( UNOMUTEX::getGlobalMutex() );
    UNOSEQUENCE< UNOOUSTRING > seqServiceNames( 1 );
    seqServiceNames.getArray() [0] = UNOOUSTRING::createFromAscii( "com.sun.star.office.OfficeWrapper" );
    return seqServiceNames ;
}

/* Helper for XServiceInfo */
UNOOUSTRING bf_OfficeWrapper::impl_getStaticImplementationName()
{
    return UNOOUSTRING::createFromAscii( "com.sun.star.comp.desktop.OfficeWrapper" );
}

Reference< XInterface >  SAL_CALL bf_OfficeWrapper_CreateInstance( const Reference< XMultiServiceFactory >  & rSMgr )
{
    static osl::Mutex aMutex;

    if ( 0L == pOfficeWrapper)
    {
        osl::MutexGuard guard( aMutex );

        if ( 0L == pOfficeWrapper )
        {
            // #i30187#
            SolarMutexGuard aGuard;

            return (XComponent*) ( new bf_OfficeWrapper( rSMgr ) );
        }
    }

    return (XComponent*)0;
}

bf_OfficeWrapper::bf_OfficeWrapper( const Reference < XMultiServiceFactory >& )
    : pApp( new OfficeApplication )
    , aListeners( aMutex )
{
    SvtModuleOptions aMOpt;

    {
        pSwDLL  = new SwDLL;
        SwDLL::LibInit();
    }

    if ( aMOpt.IsModuleInstalled( SvtModuleOptions::E_SDRAW ) || aMOpt.IsModuleInstalled( SvtModuleOptions::E_SIMPRESS ) )
    {
        pSdDLL  = new SdDLL;
        SdDLL::LibInit();
    }

    if ( aMOpt.IsModuleInstalled( SvtModuleOptions::E_SCALC ) )
    {
        pScDLL  = new ScDLL;
        ScDLL::LibInit();
    }

    if ( aMOpt.IsModuleInstalled( SvtModuleOptions::E_SCHART ) )
    {
        pSchDLL = new SchDLL;
        SchDLL::LibInit();
    }

    if ( aMOpt.IsModuleInstalled( SvtModuleOptions::E_SMATH ) )
    {
        pSmDLL = new SmDLL;
        SmDLL::LibInit();
    }
}

void SAL_CALL bf_OfficeWrapper::initialize( const Sequence< Any >& ) throw( Exception )
{
}

bf_OfficeWrapper::~bf_OfficeWrapper()
{
    {
        // all ConfigItems must be destroyed before destroying the SfxApp
        SvtModuleOptions aMOpt;

        if ( aMOpt.IsModuleInstalled( SvtModuleOptions::E_SCHART ) )
        {
            SchDLL::LibExit();
            DELETEZ( pSchDLL );
        }

        if ( aMOpt.IsModuleInstalled( SvtModuleOptions::E_SMATH ) )
        {
            SmDLL::LibExit();
            DELETEZ( pSmDLL );
        }

        {
            SwDLL::LibExit();
            DELETEZ( pSwDLL );
        }

        if ( aMOpt.IsModuleInstalled( SvtModuleOptions::E_SDRAW ) || aMOpt.IsModuleInstalled( SvtModuleOptions::E_SIMPRESS ) )
        {
            SdDLL::LibExit();
            DELETEZ( pSdDLL );
        }

        if ( aMOpt.IsModuleInstalled( SvtModuleOptions::E_SCALC ) )
        {
            ScDLL::PreExit();           // der Teil vom Exit der noch Svx etc. braucht
            ScDLL::LibExit();
            DELETEZ( pScDLL );
        }
    }

    delete pApp;
    delete &GetSdrGlobalData(); // ??????????

    (*(SdrGlobalData**)GetAppData(BF_SHL_SVD))=0;
    (*(SvxGlobalItemData**)GetAppData(BF_SHL_ITEM))=0;
}

void SAL_CALL bf_OfficeWrapper::dispose() throw ( RuntimeException )
{
    EventObject aObject;
    aObject.Source = (XComponent*)this;
    aListeners.disposeAndClear( aObject );
}

void SAL_CALL bf_OfficeWrapper::addEventListener( const Reference< XEventListener > & aListener) throw ( RuntimeException )
{
    aListeners.addInterface( aListener );
}

void SAL_CALL bf_OfficeWrapper::removeEventListener( const Reference< XEventListener > & aListener ) throw ( RuntimeException )
{
    aListeners.removeInterface( aListener );
}

extern "C"
{

SAL_DLLPUBLIC_EXPORT void* SAL_CALL component_getFactory(
    const sal_Char* pImplementationName,
    void* pServiceManager,
    void* /*pRegistryKey*/)
{
    // Set default return value for this operation - if it failed.
    void* pReturn = NULL;

    if ( pImplementationName && pServiceManager )
    {
        // Define variables which are used in following macros.
        Reference< XSingleServiceFactory > xFactory;
        Reference< XMultiServiceFactory > xServiceManager( reinterpret_cast< XMultiServiceFactory* >( pServiceManager ) );

        if ( bf_OfficeWrapper::impl_getStaticImplementationName().compareToAscii( pImplementationName ) == COMPARE_EQUAL )
        {
            xFactory = Reference< XSingleServiceFactory >(
                cppu::createOneInstanceFactory( xServiceManager, bf_OfficeWrapper::impl_getStaticImplementationName(),
                bf_OfficeWrapper_CreateInstance, bf_OfficeWrapper::impl_getStaticSupportedServiceNames() ) );
        }

        // Factory is valid - service was found.
        if ( xFactory.is() )
        {
            xFactory->acquire();
            pReturn = xFactory.get();
        }
    }

    // Return with result of this operation.
    return pReturn;
}

} // extern "C"

// eof
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
