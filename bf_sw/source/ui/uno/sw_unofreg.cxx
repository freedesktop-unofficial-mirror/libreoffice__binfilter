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

#include <string.h>

#include <com/sun/star/registry/XRegistryKey.hpp>

#include <osl/diagnose.h>

#include <cppuhelper/factory.hxx>
#include <uno/lbnames.h>
#include <SwXFilterOptions.hxx>
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::lang;

using ::rtl::OUString;

// writer documents
extern uno::Sequence< OUString > SAL_CALL SwTextDocument_getSupportedServiceNames() throw();
extern OUString SAL_CALL SwTextDocument_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwTextDocument_createInstance( const uno::Reference< XMultiServiceFactory > &rSMgr ) throw( uno::Exception );
extern uno::Sequence< OUString > SAL_CALL SwWebDocument_getSupportedServiceNames() throw();
extern OUString SAL_CALL SwWebDocument_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwWebDocument_createInstance( const uno::Reference< XMultiServiceFactory > &rSMgr ) throw( uno::Exception );
extern uno::Sequence< OUString > SAL_CALL SwGlobalDocument_getSupportedServiceNames() throw();
extern OUString SAL_CALL SwGlobalDocument_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwGlobalDocument_createInstance( const uno::Reference< XMultiServiceFactory > &rSMgr ) throw( uno::Exception );

// xml import
extern uno::Sequence< OUString > SAL_CALL SwXMLImport_getSupportedServiceNames() throw();
extern OUString SAL_CALL SwXMLImport_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwXMLImport_createInstance(const uno::Reference< XMultiServiceFactory > & rSMgr)  throw( uno::Exception );
extern uno::Sequence< OUString > SAL_CALL SwXMLImportStyles_getSupportedServiceNames() throw();
extern OUString SAL_CALL SwXMLImportStyles_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwXMLImportStyles_createInstance(const uno::Reference< XMultiServiceFactory > & rSMgr)    throw( uno::Exception );
extern uno::Sequence< OUString > SAL_CALL SwXMLImportContent_getSupportedServiceNames() throw();
extern OUString SAL_CALL SwXMLImportContent_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwXMLImportContent_createInstance(const uno::Reference< XMultiServiceFactory > & rSMgr)   throw( uno::Exception );

extern uno::Sequence< OUString > SAL_CALL     SwXMLImportMeta_getSupportedServiceNames() throw();
extern OUString SAL_CALL     SwXMLImportMeta_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwXMLImportMeta_createInstance(const uno::Reference< XMultiServiceFactory > & rSMgr)  throw( uno::Exception );

extern uno::Sequence< OUString > SAL_CALL SwXMLImportSettings_getSupportedServiceNames() throw();
extern OUString SAL_CALL SwXMLImportSettings_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwXMLImportSettings_createInstance(const uno::Reference< XMultiServiceFactory > & rSMgr)  throw( uno::Exception );

// xml export
extern uno::Sequence< OUString > SAL_CALL SwXMLExport_getSupportedServiceNames() throw();
extern OUString SAL_CALL SwXMLExport_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwXMLExport_createInstance(const uno::Reference< XMultiServiceFactory > & rSMgr)  throw( uno::Exception );
extern uno::Sequence< OUString > SAL_CALL SwXMLExportContent_getSupportedServiceNames() throw();
extern OUString SAL_CALL SwXMLExportContent_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwXMLExportContent_createInstance(const uno::Reference< XMultiServiceFactory > & rSMgr)   throw( uno::Exception );
extern uno::Sequence< OUString > SAL_CALL SwXMLExportStyles_getSupportedServiceNames() throw();
extern OUString SAL_CALL SwXMLExportStyles_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwXMLExportStyles_createInstance(const uno::Reference< XMultiServiceFactory > & rSMgr)    throw( uno::Exception );
extern uno::Sequence< OUString > SAL_CALL SwXMLExportMeta_getSupportedServiceNames() throw();
extern OUString SAL_CALL SwXMLExportMeta_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwXMLExportMeta_createInstance(const uno::Reference< XMultiServiceFactory > & rSMgr)  throw( uno::Exception );
extern uno::Sequence< OUString > SAL_CALL SwXMLExportSettings_getSupportedServiceNames() throw();
extern OUString SAL_CALL SwXMLExportSettings_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwXMLExportSettings_createInstance(const uno::Reference< XMultiServiceFactory > & rSMgr)  throw( uno::Exception );

extern uno::Sequence< OUString > SAL_CALL SwXModule_getSupportedServiceNames() throw();
extern OUString SAL_CALL SwXModule_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SwXModule_createInstance(const uno::Reference< XMultiServiceFactory > & rSMgr) throw( uno::Exception );

//
#ifdef __cplusplus
extern "C"
{
#endif

SAL_DLLPUBLIC_EXPORT void * SAL_CALL component_getFactory( const sal_Char * pImplName,
                                      void * pServiceManager,
                                      void * /*pRegistryKey*/ )
{
    void * pRet = 0;
    if( pServiceManager )
    {
        uno::Reference< XMultiServiceFactory > xMSF(
            reinterpret_cast< XMultiServiceFactory * >( pServiceManager ) );

        uno::Reference< XSingleServiceFactory > xFactory;

        const sal_Int32 nImplNameLen = strlen( pImplName );
        if( SwXMLImport_getImplementationName().equalsAsciiL( pImplName,
                                                              nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwXMLImport_getImplementationName(),
                SwXMLImport_createInstance,
                SwXMLImport_getSupportedServiceNames() );
        }
        else if( SwXMLImportStyles_getImplementationName().equalsAsciiL(
                                                    pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwXMLImportStyles_getImplementationName(),
                SwXMLImportStyles_createInstance,
                SwXMLImportStyles_getSupportedServiceNames() );
        }
        else if( SwXMLImportContent_getImplementationName().equalsAsciiL(
                                                    pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwXMLImportContent_getImplementationName(),
                SwXMLImportContent_createInstance,
                SwXMLImportContent_getSupportedServiceNames() );
        }
        else if( SwXMLImportMeta_getImplementationName().equalsAsciiL(
                                                    pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwXMLImportMeta_getImplementationName(),
                SwXMLImportMeta_createInstance,
                SwXMLImportMeta_getSupportedServiceNames() );
        }
        else if( SwXMLExport_getImplementationName().equalsAsciiL( pImplName,
                                                            nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwXMLExport_getImplementationName(),
                SwXMLExport_createInstance,
                SwXMLExport_getSupportedServiceNames() );
        }
        else if( SwXMLExportStyles_getImplementationName().equalsAsciiL(
                                                    pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwXMLExportStyles_getImplementationName(),
                SwXMLExportStyles_createInstance,
                SwXMLExportStyles_getSupportedServiceNames() );
        }
        else if( SwXMLExportContent_getImplementationName().equalsAsciiL(
                                                    pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwXMLExportContent_getImplementationName(),
                SwXMLExportContent_createInstance,
                SwXMLExportContent_getSupportedServiceNames() );
        }
        else if( SwXMLExportMeta_getImplementationName().equalsAsciiL(
                                                    pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwXMLExportMeta_getImplementationName(),
                SwXMLExportMeta_createInstance,
                SwXMLExportMeta_getSupportedServiceNames() );
        }
        else if( SwXMLExportSettings_getImplementationName().equalsAsciiL(
                                                    pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwXMLExportSettings_getImplementationName(),
                SwXMLExportSettings_createInstance,
                SwXMLExportSettings_getSupportedServiceNames() );
        }
        else if( SwXMLImportSettings_getImplementationName().equalsAsciiL(
                                                    pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwXMLImportSettings_getImplementationName(),
                SwXMLImportSettings_createInstance,
                SwXMLImportSettings_getSupportedServiceNames() );
        }
        else if( SwXModule_getImplementationName().equalsAsciiL(
                                                    pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwXModule_getImplementationName(),
                SwXModule_createInstance,
                SwXModule_getSupportedServiceNames() );
        }
        else if( SwXFilterOptions::getImplementationName_Static().equalsAsciiL(
                                                    pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwXFilterOptions::getImplementationName_Static(),
                SwXFilterOptions_createInstance,
                SwXFilterOptions::getSupportedServiceNames_Static() );
        }
        else if( SwTextDocument_getImplementationName().equalsAsciiL(
                                                    pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwTextDocument_getImplementationName(),
                SwTextDocument_createInstance,
                SwTextDocument_getSupportedServiceNames() );
        }
        else if( SwWebDocument_getImplementationName().equalsAsciiL(
                                                    pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwWebDocument_getImplementationName(),
                SwWebDocument_createInstance,
                SwWebDocument_getSupportedServiceNames() );
        }
        else if( SwGlobalDocument_getImplementationName().equalsAsciiL(
                                                    pImplName, nImplNameLen ) )
        {
            xFactory = ::cppu::createSingleFactory( xMSF,
                SwGlobalDocument_getImplementationName(),
                SwGlobalDocument_createInstance,
                SwGlobalDocument_getSupportedServiceNames() );
        }

        if( xFactory.is())
        {
            xFactory->acquire();
            pRet = xFactory.get();
        }
    }
    return pRet;
}

#ifdef __cplusplus
}
#endif
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
