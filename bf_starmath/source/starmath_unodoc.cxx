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

#include <bf_tools/string.hxx>
#include <bf_sfx2/docfac.hxx>

#include <com/sun/star/lang/XMultiServiceFactory.hpp>

#include "smmod.hxx"

#include <osl/mutex.hxx>
#include <vcl/svapp.hxx>
namespace binfilter {

using namespace ::com::sun::star;

::rtl::OUString SAL_CALL SmDocument_getImplementationName() throw()
{
    return ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.comp.Math.FormulaDocument" ) );
}

uno::Sequence< ::rtl::OUString > SAL_CALL SmDocument_getSupportedServiceNames() throw()
{
    uno::Sequence< ::rtl::OUString > aSeq( 1 );
    aSeq[0] = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.formula.FormulaProperties" ));
    return aSeq;
}

uno::Reference< uno::XInterface > SAL_CALL SmDocument_createInstance(
                const uno::Reference< lang::XMultiServiceFactory > & /*rSMgr*/ ) throw( uno::Exception )
{
    SolarMutexGuard aGuard;

    // to create the service the SW_MOD should be already initialized
    DBG_ASSERT( SM_MOD(), "No StarMath module!" );

    if ( SM_MOD() )
    {
        ::rtl::OUString aFactoryURL( RTL_CONSTASCII_USTRINGPARAM ( "private:factory/smath" ) );
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
