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

#ifndef INCLUDED_SVTOOLS_DOCPASSWDREQUEST_HXX
#define INCLUDED_SVTOOLS_DOCPASSWDREQUEST_HXX

#include <com/sun/star/task/DocumentPasswordRequest.hpp>
#include <com/sun/star/task/XInteractionRequest.hpp>

#include <rtl/ustring.hxx>

#include <cppuhelper/implbase1.hxx>

namespace binfilter {

class AbortContinuation;
class PasswordContinuation;

class  RequestDocumentPassword : public ::cppu::WeakImplHelper1< ::com::sun::star::task::XInteractionRequest >
{
    ::com::sun::star::uno::Any m_aRequest;

    ::com::sun::star::uno::Sequence<
                    ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionContinuation >
                > m_lContinuations;

    AbortContinuation*      m_pAbort;
    PasswordContinuation*   m_pPassword;

public:
    RequestDocumentPassword( ::com::sun::star::task::PasswordRequestMode nMode, ::rtl::OUString aName );

    sal_Bool isPassword();

    ::rtl::OUString getPassword();

    virtual ::com::sun::star::uno::Any SAL_CALL getRequest()
        throw( ::com::sun::star::uno::RuntimeException );

    virtual ::com::sun::star::uno::Sequence<
                ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionContinuation >
            > SAL_CALL getContinuations()
        throw( ::com::sun::star::uno::RuntimeException );
};

}

#endif /* INCLUDED_SVTOOLS_DOCPASSWDREQUEST_HXX */

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
