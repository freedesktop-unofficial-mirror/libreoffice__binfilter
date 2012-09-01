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

#ifndef _BF_WRAPPER_HXX
#define _BF_WRAPPER_HXX

#include <com/sun/star/lang/XServiceInfo.hpp>

#include <com/sun/star/uno/Exception.hpp>

#include <com/sun/star/uno/Reference.h>

#include <com/sun/star/lang/XComponent.hpp>

#include <com/sun/star/lang/XEventListener.hpp>

#include <com/sun/star/lang/XInitialization.hpp>

#include <cppuhelper/implbase3.hxx>

#include <cppuhelper/interfacecontainer.h>

#include <com/sun/star/lang/XSingleServiceFactory.hpp>
#include <osl/mutex.hxx>
#include <bf_sfx2/sfxuno.hxx>


#ifdef _MSC_VER
#pragma hdrstop
#endif
namespace binfilter {
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;

class OfficeApplication;

class bf_OfficeWrapper : public ::cppu::WeakImplHelper3< XInitialization, XComponent, XServiceInfo >
{
    OfficeApplication*                                  pApp;
    ::osl::Mutex                                        aMutex;
    ::cppu::OInterfaceContainerHelper                   aListeners;

public:
    bf_OfficeWrapper( const Reference < XMultiServiceFactory >& xFactory );
    virtual ~bf_OfficeWrapper();

    /* XServiceInfo */
    virtual UNOOUSTRING SAL_CALL getImplementationName() throw( UNORUNTIMEEXCEPTION );
    virtual sal_Bool SAL_CALL supportsService( const UNOOUSTRING& sServiceName ) throw( UNORUNTIMEEXCEPTION );
    virtual UNOSEQUENCE< UNOOUSTRING > SAL_CALL getSupportedServiceNames() throw( UNORUNTIMEEXCEPTION );

    /* Helper for XServiceInfo */
    static UNOSEQUENCE< UNOOUSTRING > impl_getStaticSupportedServiceNames();
    static UNOOUSTRING impl_getStaticImplementationName();

    /* Helper for registry */
    static UNOREFERENCE< UNOXSINGLESERVICEFACTORY > impl_createFactory( const UNOREFERENCE< UNOXMULTISERVICEFACTORY >& xServiceManager );

    static Reference< XSingleServiceFactory > GetWrapperFactory( Reference< XMultiServiceFactory > & xSMgr );
    static ::rtl::OUString  GetImplementationName_static();

    // XComponent
    virtual void SAL_CALL dispose() throw ( RuntimeException );
    virtual void SAL_CALL addEventListener( const Reference< XEventListener > & aListener) throw ( RuntimeException );
    virtual void SAL_CALL removeEventListener(const Reference< XEventListener > & aListener) throw ( RuntimeException );

    // XInitialization
    virtual void SAL_CALL initialize( const Sequence< Any >& aArguments ) throw( Exception );
};

}//end of namespace binfilter
#endif // _BF_WRAPPER_HXX

// eof

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
