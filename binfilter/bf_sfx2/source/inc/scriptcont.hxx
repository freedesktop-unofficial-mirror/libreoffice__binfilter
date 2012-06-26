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



#ifndef _SFX_SCRIPTCONT_HXX
#define _SFX_SCRIPTCONT_HXX

#include <bf_basic/basmgr.hxx>
class BasicManager;
namespace binfilter {


//============================================================================


class SfxScriptLibraryContainer : public SfxLibraryContainer_Impl, public OldBasicPassword
{
    ::rtl::OUString maScriptLanguage;
    BasicManager* mpBasMgr;

    // Methods to distinguish between deffirent library types
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

    virtual SfxLibraryContainer_Impl* createInstanceImpl( void ){ return NULL; }


    // OldBasicPassword interface
    virtual void setLibraryPassword( const String& rLibraryName, const String& rPassword );
    virtual String getLibraryPassword( const String& rLibraryName );
    virtual void clearLibraryPassword( const String& rLibraryName );
    virtual sal_Bool hasLibraryPassword( const String& rLibraryName );

    sal_Bool init( const ::rtl::OUString& aInitialisationParam,
                   const ::rtl::OUString& aScriptLanguage,
                   BasicManager* pBasMgr=NULL, SotStorage* pStor=NULL );

public:
    SfxScriptLibraryContainer( void );
    SfxScriptLibraryContainer( const ::rtl::OUString& aScriptLanguage,
        BasicManager* pBasMgr, SotStorage* pStor=NULL );

    // TODO: Methods of new XLibraryStorage interface?
    virtual void SAL_CALL storeLibraries( sal_Bool bComplete );
    virtual void SAL_CALL storeLibrariesToStorage( SotStorageRef xStorage );

    // Methods XInitialization
    virtual void SAL_CALL initialize( const ::com::sun::star::uno::Sequence<
        ::com::sun::star::uno::Any >& aArguments )
            throw (::com::sun::star::uno::Exception,
                   ::com::sun::star::uno::RuntimeException);

    // Methods XLibraryContainerPassword
    virtual sal_Bool SAL_CALL isLibraryPasswordProtected( const ::rtl::OUString& Name )
        throw (::com::sun::star::container::NoSuchElementException,
               ::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL isLibraryPasswordVerified( const ::rtl::OUString& Name )
        throw (::com::sun::star::lang::IllegalArgumentException,
               ::com::sun::star::container::NoSuchElementException,
               ::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL verifyLibraryPassword( const ::rtl::OUString& Name, const ::rtl::OUString& Password )
        throw (::com::sun::star::lang::IllegalArgumentException,
               ::com::sun::star::container::NoSuchElementException,
               ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL changeLibraryPassword( const ::rtl::OUString& Name,
        const ::rtl::OUString& OldPassword, const ::rtl::OUString& NewPassword )
        throw (::com::sun::star::lang::IllegalArgumentException,
               ::com::sun::star::container::NoSuchElementException,
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

// class to represent application container service
class SfxApplicationScriptLibraryContainer
{
public:
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

class SfxScriptLibrary : public SfxLibrary_Impl
{
    friend class SfxScriptLibraryContainer;

    sal_Bool mbLoadedSource;
    sal_Bool mbLoadedBinary;

public:
    SfxScriptLibrary
    (
        ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xMSF,
        ::com::sun::star::uno::Reference< ::com::sun::star::ucb::XSimpleFileAccess > xSFI
    );

    SfxScriptLibrary
    (
        ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xMSF,
        ::com::sun::star::uno::Reference< ::com::sun::star::ucb::XSimpleFileAccess > xSFI,
        const ::rtl::OUString& aLibInfoFileURL, const ::rtl::OUString& aStorageURL, sal_Bool ReadOnly
    );
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
