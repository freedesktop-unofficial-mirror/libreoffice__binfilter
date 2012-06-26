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

#ifndef _SVTOOLS_SVTUNO_HXX
#define _SVTOOLS_SVTUNO_HXX

namespace binfilter
{

// Macro to define const unicode a'la "..."
// It's better then "OUString::createFromAscii(...)" !!!
#define DEFINE_CONST_UNICODE(CONSTASCII)        UniString(RTL_CONSTASCII_USTRINGPARAM(CONSTASCII))
#define DEFINE_CONST_OUSTRING(CONSTASCII)       OUString(RTL_CONSTASCII_USTRINGPARAM(CONSTASCII))

// defines ---------------------------------------------------------------
#define UNOANY                          ::com::sun::star::uno::Any
#define UNOEXCEPTION                    ::com::sun::star::uno::Exception
#define UNOMUTEX                        ::osl::Mutex
#define UNOMUTEXGUARD                   ::osl::MutexGuard
#define UNOOIMPLEMENTATIONID            ::cppu::OImplementationId
#define UNOOTYPECOLLECTION              ::cppu::OTypeCollection
#define UNOOUSTRING                     ::rtl::OUString
#define UNOPROPERTYVALUE                ::com::sun::star::beans::PropertyValue
#define UNOSTRINGPAIR                   ::com::sun::star::beans::StringPair
#define UNOREFERENCE                    ::com::sun::star::uno::Reference
#define UNORUNTIMEEXCEPTION             ::com::sun::star::uno::RuntimeException
#define UNOINVALIDREGISTRYEXCEPTION     ::com::sun::star::registry::InvalidRegistryException
#define UNOSEQUENCE                     ::com::sun::star::uno::Sequence
#define UNOTYPE                         ::com::sun::star::uno::Type
#define UNOURL                          ::com::sun::star::util::URL
#define UNOXINTERFACE                   ::com::sun::star::uno::XInterface
#define UNOXMULTISERVICEFACTORY         ::com::sun::star::lang::XMultiServiceFactory
#define UNOXSINGLESERVICEFACTORY        ::com::sun::star::lang::XSingleServiceFactory
#define UNOXTYPEPROVIDER                ::com::sun::star::lang::XTypeProvider
#define UNOILLEGALARGUMENTEXCEPTION     ::com::sun::star::lang::IllegalArgumentException

// -----------------------------------------------------------------------

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
