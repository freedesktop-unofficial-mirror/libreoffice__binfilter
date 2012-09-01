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
#ifndef _XMLOFF_PROPERTYSETINFOHASH_HXX
#define _XMLOFF_PROPERTYSETINFOHASH_HXX

#include "sal/config.h"

#include <cstddef>

#include "com/sun/star/beans/XPropertySetInfo.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/XInterface.hpp"
#include "osl/diagnose.h"
#include "sal/types.h"

namespace binfilter {

struct PropertySetInfoHash
{
    inline std::size_t operator()( const com::sun::star::uno::Reference< com::sun::star::beans::XPropertySetInfo >& r ) const;
    inline bool operator()( const com::sun::star::uno::Reference< com::sun::star::beans::XPropertySetInfo >& r1,
                                const com::sun::star::uno::Reference< com::sun::star::beans::XPropertySetInfo >& r2 ) const;
};

inline std::size_t PropertySetInfoHash::operator()(
        const com::sun::star::uno::Reference< com::sun::star::beans::XPropertySetInfo >& r ) const
{
    OSL_ASSERT(r.is());
    return static_cast< std::size_t >(
        reinterpret_cast< sal_uIntPtr >(
            com::sun::star::uno::Reference< com::sun::star::uno::XInterface >(
                r) // UNO_QUERY_THROW not available due to EXCEPTIONS_OFF
            .get()));
}

inline bool PropertySetInfoHash::operator()(
        const com::sun::star::uno::Reference< com::sun::star::beans::XPropertySetInfo >& r1,
        const com::sun::star::uno::Reference< com::sun::star::beans::XPropertySetInfo >& r2 ) const
{
    return r1 == r2;
}
}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
