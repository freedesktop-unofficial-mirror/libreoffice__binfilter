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

#ifndef SVX_UNOMOD_HXX
#define SVX_UNOMOD_HXX

#include <com/sun/star/document/EventObject.hpp>

#include <com/sun/star/lang/XMultiServiceFactory.hpp>
namespace binfilter {

class SdrHint;
class SdrModel;

class SvxUnoDrawMSFactory : public ::com::sun::star::lang::XMultiServiceFactory
{
public:
    SvxUnoDrawMSFactory() throw() {};

    virtual ~SvxUnoDrawMSFactory() {}

    virtual ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SAL_CALL createInstance( const ::rtl::OUString& aServiceSpecifier ) throw(::com::sun::star::uno::Exception, ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SAL_CALL createInstanceWithArguments( const ::rtl::OUString& ServiceSpecifier, const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any >& Arguments ) throw(::com::sun::star::uno::Exception, ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getAvailableServiceNames(  ) throw(::com::sun::star::uno::RuntimeException);

    static ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SAL_CALL createTextField( const ::rtl::OUString& aServiceSpecifier ) throw(::com::sun::star::uno::Exception, ::com::sun::star::uno::RuntimeException);
    // internal
    ::com::sun::star::uno::Sequence< ::rtl::OUString >
        concatServiceNames( ::com::sun::star::uno::Sequence< ::rtl::OUString >& rServices1,
                            ::com::sun::star::uno::Sequence< ::rtl::OUString >& rServices2 ) throw();

    /** fills the given EventObject from the given SdrHint.
        @returns
            true    if the SdrHint could be translated to an EventObject<br>
            false   if not
    */
    static sal_Bool createEvent( const SdrModel* pDoc, const SdrHint* pSdrHint, ::com::sun::star::document::EventObject& aEvent );
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
