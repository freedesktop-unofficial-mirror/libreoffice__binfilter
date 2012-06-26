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

#include <bf_sfx2/docfac.hxx>


#include "sdmod.hxx"

#include <osl/mutex.hxx>
#include <vcl/svapp.hxx>
namespace binfilter {

using namespace ::com::sun::star;

// com.sun.star.comp.Draw.DrawingDocument

::rtl::OUString SAL_CALL SdDrawingDocument_getImplementationName() throw( uno::RuntimeException )
{
    return ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.comp.Draw.DrawingDocument" ) );
}

uno::Sequence< ::rtl::OUString > SAL_CALL SdDrawingDocument_getSupportedServiceNames() throw( uno::RuntimeException )
{
    // useable for component registration only!
    uno::Sequence< ::rtl::OUString > aSeq( 1 );
    aSeq[0] = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.drawing.DrawingDocument"));

    return aSeq;
}

uno::Reference< uno::XInterface > SAL_CALL SdDrawingDocument_createInstance(
                const uno::Reference< lang::XMultiServiceFactory > & /*rSMgr*/ )
{
    SolarMutexGuard aGuard;

    // to create the service the SW_MOD should be already initialized
    DBG_ASSERT( SD_MOD(), "No StarDraw module!" );

    if ( SD_MOD() )
    {
        ::rtl::OUString aFactoryURL( RTL_CONSTASCII_USTRINGPARAM ( "private:factory/sdraw" ) );
        const SfxObjectFactory* pFactory = SfxObjectFactory::GetFactory( aFactoryURL );
        if ( pFactory )
        {
            SfxObjectShell* pShell = pFactory->CreateObject();
            if( pShell )
                return uno::Reference< uno::XInterface >( pShell->GetModel() );
        }
    }

    return uno::Reference< uno::XInterface >();
}

// com.sun.star.comp.Draw.PresentationDocument

::rtl::OUString SAL_CALL SdPresentationDocument_getImplementationName() throw( uno::RuntimeException )
{
    return ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.comp.Draw.PresentationDocument" ) );
}

uno::Sequence< ::rtl::OUString > SAL_CALL SdPresentationDocument_getSupportedServiceNames() throw( uno::RuntimeException )
{
    // useable for component registration only!
    uno::Sequence< ::rtl::OUString > aSeq( 1 );
    aSeq[0] = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.presentation.PresentationDocument"));

    return aSeq;
}

uno::Reference< uno::XInterface > SAL_CALL SdPresentationDocument_createInstance(
                const uno::Reference< lang::XMultiServiceFactory > & /*rSMgr*/ )
{
    SolarMutexGuard aGuard;

    // to create the service the SW_MOD should be already initialized
    DBG_ASSERT( SD_MOD(), "No StarDraw module!" );

    if ( SD_MOD() )
    {
        ::rtl::OUString aFactoryURL( RTL_CONSTASCII_USTRINGPARAM ( "private:factory/simpress" ) );
        const SfxObjectFactory* pFactory = SfxObjectFactory::GetFactory( aFactoryURL );
        if ( pFactory )
        {
            SfxObjectShell* pShell = pFactory->CreateObject();
            if( pShell )
                return uno::Reference< uno::XInterface >( pShell->GetModel() );
        }
    }

    return uno::Reference< uno::XInterface >();
}


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
