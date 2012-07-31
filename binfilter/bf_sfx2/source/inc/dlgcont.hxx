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

#ifndef _SFX_DLGCONT_HXX
#define _SFX_DLGCONT_HXX

#include <namecont.hxx>
#include <tools/debug.hxx> //for strip
namespace binfilter {

//============================================================================

class SfxDialogLibraryContainer : public SfxLibraryContainer_Impl
{
    // Methods to distinguish between different library types
    virtual SfxLibrary_Impl* SAL_CALL implCreateLibrary( void );
    virtual SfxLibrary_Impl* SAL_CALL implCreateLibraryLink
        ( const ::rtl::OUString& aLibInfoFileURL,
          const ::rtl::OUString& StorageURL, sal_Bool ReadOnly );
    virtual ::com::sun::star::uno::Any SAL_CALL createEmptyLibraryElement( void );
    virtual sal_Bool SAL_CALL isLibraryElementValid( ::com::sun::star::uno::Any aElement );
    virtual void SAL_CALL writeLibraryElement
    (
        ::com::sun::star::uno::Any aElement,
        const ::rtl::OUString& aElementName,
        ::com::sun::star::uno::Reference< ::com::sun::star::io::XOutputStream > xOutput
    )
        throw(::com::sun::star::uno::Exception);
    virtual ::com::sun::star::uno::Any SAL_CALL importLibraryElement
        ( const ::rtl::OUString& aFile, SotStorageStreamRef xElementStream );

    virtual SfxLibraryContainer_Impl* createInstanceImpl( void ) {return NULL; }

    sal_Bool init( const ::rtl::OUString& aInitialisationParam,
                   SotStorage* pStor=NULL );

public:
    SfxDialogLibraryContainer( void );
    SfxDialogLibraryContainer( SotStorage* pStor );

    // Methods XInitialization
    virtual void SAL_CALL initialize( const ::com::sun::star::uno::Sequence<
        ::com::sun::star::uno::Any >& aArguments )
            throw (::com::sun::star::uno::Exception,
                   ::com::sun::star::uno::RuntimeException);

    // Service
    static ::com::sun::star::uno::Sequence< ::rtl::OUString > impl_getStaticSupportedServiceNames();
    static ::rtl::OUString impl_getStaticImplementationName();
    static ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SAL_CALL impl_createInstance
        ( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& xServiceManager )
            throw( ::com::sun::star::uno::Exception );
    static ::com::sun::star::uno::Reference< ::com::sun::star::lang::XSingleServiceFactory > impl_createFactory
        ( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& xServiceManager );

};

//============================================================================

class SfxDialogLibrary : public SfxLibrary_Impl
{
public:
    SfxDialogLibrary
    (
        ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xMSF,
        ::com::sun::star::uno::Reference< ::com::sun::star::ucb::XSimpleFileAccess > xSFI
    );

    SfxDialogLibrary
    (
        ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xMSF,
        ::com::sun::star::uno::Reference< ::com::sun::star::ucb::XSimpleFileAccess > xSFI,
        const ::rtl::OUString& aLibInfoFileURL, const ::rtl::OUString& aStorageURL, sal_Bool ReadOnly
    );
};

}//end of namespace binfilter
#endif


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
