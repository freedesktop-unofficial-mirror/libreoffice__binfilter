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


#include <bf_sfx2/sfxuno.hxx>

#include "schdll.hxx"
namespace binfilter {

using namespace ::com::sun::star;

//StarChart document
extern uno::Sequence< ::rtl::OUString > SAL_CALL SchDocument_getSupportedServiceNames() throw();
extern ::rtl::OUString SAL_CALL SchDocument_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SchDocument_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

extern "C" {

SAL_DLLPUBLIC_EXPORT void* SAL_CALL component_getFactory(   const   sal_Char*   pImplementationName ,
                                                void*       pServiceManager     ,
                                                void*       /*pRegistryKey*/    )
{
    void* pReturn = NULL ;

    if  ( ( pImplementationName !=  NULL ) && ( pServiceManager     !=  NULL ) )
    {
        uno::Reference< lang::XSingleServiceFactory > xFactory;
        uno::Reference< lang::XMultiServiceFactory > xServiceManager(
                    reinterpret_cast< lang::XMultiServiceFactory* >( pServiceManager ) );

        if( SchDocument_getImplementationName().equalsAsciiL(
            pImplementationName, strlen(pImplementationName)) )
        {
            xFactory = ::cppu::createSingleFactory( xServiceManager,
            SchDocument_getImplementationName(),
            SchDocument_createInstance,
            SchDocument_getSupportedServiceNames() );
        }


        if ( xFactory.is() )
        {
            xFactory->acquire();
            pReturn = xFactory.get();
        }
    }

    return pReturn ;
}
} // extern "C"



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
