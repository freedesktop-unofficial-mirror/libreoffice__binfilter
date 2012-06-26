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
#include <stdio.h>

#include <osl/thread.h>


#include <legacysmgr/legacy_binfilters_smgr.hxx>

#include <bf_migratefilter.hxx>

#include <bf_sfx2/objuno.hxx>

namespace binfilter {

using namespace ::rtl;
using namespace ::cppu;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::registry;

extern "C"
{

SAL_DLLPUBLIC_EXPORT void* SAL_CALL component_getFactory(const sal_Char* pImplName, void* pServiceManager, void* pRegistryKey)
{
    void* pRet = 0;

    OUString implName = OUString::createFromAscii(pImplName);

    if(pServiceManager && implName.equals(bf_MigrateFilter_getImplementationName()))
    {
        Reference< XSingleServiceFactory > xFactory(createSingleFactory(
            reinterpret_cast< XMultiServiceFactory * >(pServiceManager),
            OUString::createFromAscii(pImplName),
            bf_MigrateFilter_createInstance, bf_MigrateFilter_getSupportedServiceNames()));

        if(xFactory.is())
        {
            xFactory->acquire();
            pRet = xFactory.get();
        }

        // init LegacyServiceFactory
        legacysmgr_component_getFactory(
            pImplName,
            reinterpret_cast< XMultiServiceFactory *>(pServiceManager),
            reinterpret_cast<XRegistryKey*> (pRegistryKey) );
    }
    else if(pServiceManager && implName.equals(SfxStandaloneDocumentInfoObject::impl_getStaticImplementationName()))
    {
        Reference< XSingleServiceFactory > xFactory(createSingleFactory(
            reinterpret_cast< XMultiServiceFactory * >(pServiceManager),
            OUString::createFromAscii(pImplName),
            bf_BinaryDocInfo_createInstance, binfilter::SfxStandaloneDocumentInfoObject::impl_getStaticSupportedServiceNames()));

        if(xFactory.is())
        {
            xFactory->acquire();
            pRet = xFactory.get();
        }

        // init LegacyServiceFactory
        legacysmgr_component_getFactory(
            pImplName,
            reinterpret_cast< XMultiServiceFactory *>(pServiceManager),
            reinterpret_cast<XRegistryKey*> (pRegistryKey) );
    }

    return pRet;
}
}

// eof
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
