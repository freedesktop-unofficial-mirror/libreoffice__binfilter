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

#ifndef _CONTTRANS_HXX
#define _CONTTRANS_HXX

// interfaces and structs
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/lang/XSingleServiceFactory.hpp>
#include <com/sun/star/registry/XRegistryKey.hpp>
#include <com/sun/star/ucb/XContentTransmitter.hpp>

// helper classes and functions
#include <cppuhelper/implbase2.hxx>
#include <uno/dispatcher.h>
#include <uno/mapping.hxx>
#include <cppuhelper/factory.hxx>


#include <rtl/ustrbuf.hxx>
#include <bf_svtools/lstner.hxx>
namespace binfilter {

//=========================================================================

#define CT_SERVICE_NAME L"com.sun.star.ucb.ContentTransmitter"
#define FLAG_SET_READONLY   0x01
#define FLAG_NOTIFY_ANCHOR  0x02

//=========================================================================

class ContentTransmitter : public SfxListener,
                           public cppu::WeakImplHelper2<
                                ::com::sun::star::ucb::XContentTransmitter,
                                ::com::sun::star::lang::XServiceInfo >
{
    ::com::sun::star::uno::Reference < ::com::sun::star::lang::XMultiServiceFactory > m_xFact;
    ::rtl::OUString m_aSource;
    ::rtl::OUString m_aDest;
    long            m_nFlags;

public:

    ContentTransmitter( const ::com::sun::star::uno::Reference < ::com::sun::star::lang::XMultiServiceFactory >& rFact )
        : m_xFact( rFact )
    {}

    // SfxListener
    virtual void
    Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

    // XContentTransmitter
    virtual void SAL_CALL
    transmit( const ::rtl::OUString& Source,
              const ::rtl::OUString& Destination,
              long                 Flags )
        throw( ::com::sun::star::uno::RuntimeException );

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL
    getImplementationName()
        throw( ::com::sun::star::uno::RuntimeException );

    virtual sal_Bool SAL_CALL
    supportsService( const ::rtl::OUString& ServiceName )
        throw( ::com::sun::star::uno::RuntimeException );

    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL
    getSupportedServiceNames()
        throw( ::com::sun::star::uno::RuntimeException );

    // static Helper functions
    static ::com::sun::star::uno::Sequence< ::rtl::OUString >
    getSupportedServiceNames_Static();

    static ::rtl::OUString
    getImplementationName_Static() { return CT_SERVICE_NAME; }

    ::com::sun::star::uno::Reference< ::com::sun::star::lang::XSingleServiceFactory >
    createServiceFactory( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& rxServiceMgr );
};


}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
