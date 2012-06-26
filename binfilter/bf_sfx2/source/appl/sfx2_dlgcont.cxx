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

#include "dlgcont.hxx"


#include <xmlscript/xmldlg_imexp.hxx>


#include <bf_sfx2/sfxuno.hxx>

namespace binfilter {

using namespace ::com::sun::star::container;
using namespace ::com::sun::star::io;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::ucb;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::script;
using namespace ::com::sun::star::xml::sax;
using namespace ::com::sun::star;
using namespace cppu;
using namespace osl;
using ::rtl::OUString;


//============================================================================
// Implementation class SfxDialogLibraryContainer

/*N*/ sal_Bool SfxDialogLibraryContainer::init
/*N*/     ( const ::rtl::OUString& aInitialisationParam, SotStorage* pStor )
/*N*/ {
/*N*/     return SfxLibraryContainer_Impl::init(
/*N*/           aInitialisationParam,
/*N*/           OUString ( RTL_CONSTASCII_USTRINGPARAM("dialog") ),
/*N*/         OUString ( RTL_CONSTASCII_USTRINGPARAM("dialogs") ),
/*N*/         OUString ( RTL_CONSTASCII_USTRINGPARAM("xdl") ),
/*N*/         OUString ( RTL_CONSTASCII_USTRINGPARAM("Dialogs") ),
/*N*/           pStor );
/*N*/ }

// Ctor for service
// Ctor for service
SfxDialogLibraryContainer::SfxDialogLibraryContainer( void )
{
    // all initialisation has to be done
    // by calling XInitialization::initialize
}

/*N*/ SfxDialogLibraryContainer::SfxDialogLibraryContainer( SotStorage* pStor )
/*N*/ {
/*N*/     OUString aInitialisationParam;
/*N*/     init( aInitialisationParam, pStor );
/*N*/ }

// Methods to get library instances of the correct type
/*N*/ SfxLibrary_Impl* SfxDialogLibraryContainer::implCreateLibrary( void )
/*N*/ {
/*N*/   SfxLibrary_Impl* pRet = (SfxLibrary_Impl*) new SfxDialogLibrary( mxMSF, mxSFI );
/*N*/   return pRet;
/*N*/ }

/*N*/ SfxLibrary_Impl* SfxDialogLibraryContainer::implCreateLibraryLink
/*N*/   ( const OUString& aLibInfoFileURL, const OUString& StorageURL, sal_Bool ReadOnly )
/*N*/ {
/*N*/   SfxLibrary_Impl* pRet =
/*N*/       (SfxLibrary_Impl*) new SfxDialogLibrary
/*N*/             ( mxMSF, mxSFI, aLibInfoFileURL, StorageURL, ReadOnly );
/*N*/   return pRet;
/*N*/ }

/*N*/ Any SAL_CALL SfxDialogLibraryContainer::createEmptyLibraryElement( void )
/*N*/ {
/*N*/   Reference< XInputStreamProvider > xISP;
/*N*/   Any aRetAny;
/*N*/   aRetAny <<= xISP;
/*N*/   return aRetAny;
/*N*/ }

/*?*/ sal_Bool SAL_CALL SfxDialogLibraryContainer::isLibraryElementValid( Any aElement )
/*?*/ {
        Reference< XInputStreamProvider > xISP;
        aElement >>= xISP;
        sal_Bool bRet = xISP.is();
        return bRet;

/*?*/ }

/*?*/ void SAL_CALL SfxDialogLibraryContainer::writeLibraryElement
/*?*/ (
/*?*/   Any aElement,
/*?*/   const OUString& /*aElementName*/,
/*?*/   Reference< XOutputStream > xOutput
/*?*/ )
/*?*/   throw(Exception)
/*?*/ {
        Reference< XInputStreamProvider > xISP;
        aElement >>= xISP;
        if( !xISP.is() )
            return;

        Reference< XInputStream > xInput( xISP->createInputStream() );
        Sequence< sal_Int8 > bytes;
        sal_Int32 nRead = xInput->readBytes( bytes, xInput->available() );
        for (;;)
        {
            if( nRead )
                xOutput->writeBytes( bytes );

            nRead = xInput->readBytes( bytes, 1024 );
            if (! nRead)
                break;
        }
        xInput->closeInput();
/*?*/ }


Any SAL_CALL SfxDialogLibraryContainer::importLibraryElement
(
    const OUString& /*aFile*/,
    SotStorageStreamRef /*xElementStream*/
)
{
    DBG_BF_ASSERT(0, "STRIP");  // VIRTUAL
    Any aAny;
    return aAny;
}


//============================================================================
// Methods XInitialization
/*?*/ void SAL_CALL SfxDialogLibraryContainer::initialize( const Sequence< Any >& aArguments )
/*?*/     throw (::com::sun::star::uno::Exception,
/*?*/            ::com::sun::star::uno::RuntimeException)
/*?*/ {
        sal_Int32 nArgCount = aArguments.getLength();
        OSL_ENSURE( nArgCount, "SfxDialogLibraryContainer::initialize() called with no arguments\n" );

        OUString aInitialisationParam;
        if( nArgCount )
        {
            const Any* pArgs = aArguments.getConstArray();
            pArgs[0] >>= aInitialisationParam;
            OSL_ENSURE( aInitialisationParam.getLength(),
                "SfxDialogLibraryContainer::initialize() called with empty url\n" );
        }

        init( aInitialisationParam );
/*?*/ }


//============================================================================
// Service
/*N*/ SFX_IMPL_SINGLEFACTORY( SfxDialogLibraryContainer )

Sequence< OUString > SfxDialogLibraryContainer::impl_getStaticSupportedServiceNames()
{
    static Sequence< OUString > seqServiceNames( 1 );
    static sal_Bool bNeedsInit = sal_True;

    MutexGuard aGuard( Mutex::getGlobalMutex() );
    if( bNeedsInit )
    {
        OUString* pSeq = seqServiceNames.getArray();
        pSeq[0] = OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.script.DialogLibraryContainer" ));
        bNeedsInit = sal_False;
    }
    return seqServiceNames;
}

OUString SfxDialogLibraryContainer::impl_getStaticImplementationName()
{
    static OUString aImplName;
    static sal_Bool bNeedsInit = sal_True;

    MutexGuard aGuard( Mutex::getGlobalMutex() );
    if( bNeedsInit )
    {
        aImplName = OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.comp.sfx2.DialogLibraryContainer" ));
        bNeedsInit = sal_False;
    }
    return aImplName;
}

Reference< XInterface > SAL_CALL SfxDialogLibraryContainer::impl_createInstance
    ( const Reference< XMultiServiceFactory >& /*xServiceManager*/ )
        throw( Exception )
{
    Reference< XInterface > xRet =
        static_cast< XInterface* >( static_cast< OWeakObject* >(new SfxDialogLibraryContainer()) );
    return xRet;
}

//============================================================================
// Implementation class SfxDialogLibrary

// Ctor
/*N*/ SfxDialogLibrary::SfxDialogLibrary( Reference< XMultiServiceFactory > xMSF,
/*N*/                                     Reference< XSimpleFileAccess > xSFI )
/*N*/   : SfxLibrary_Impl( getCppuType( (const Reference< XInputStreamProvider > *)0 ), xMSF, xSFI )
/*N*/ {
/*N*/ }

/*N*/ SfxDialogLibrary::SfxDialogLibrary( Reference< XMultiServiceFactory > xMSF,
/*N*/                                     Reference< XSimpleFileAccess > xSFI,
/*N*/                                     const OUString& aLibInfoFileURL,
/*N*/                                     const OUString& aStorageURL,
/*N*/                                     sal_Bool ReadOnly )
/*N*/   : SfxLibrary_Impl( getCppuType( (const Reference< XInputStreamProvider > *)0 ),
/*N*/                        xMSF, xSFI, aLibInfoFileURL, aStorageURL, ReadOnly)
/*N*/ {
/*N*/ }

//============================================================================

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
