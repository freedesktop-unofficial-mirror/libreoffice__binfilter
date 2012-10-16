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

#ifndef _TRANSUNO_HXX
#define _TRANSUNO_HXX

#ifndef _RTL_USTRING_
#include <rtl/ustring.h>
#endif

#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/uno/Sequence.hxx>
#include <com/sun/star/uno/XInterface.hpp>
#include <com/sun/star/beans/Property.hpp>
#include <com/sun/star/beans/PropertyValue.hpp>
#include <com/sun/star/ucb/PropertyValueInfo.hpp>
#include <com/sun/star/ucb/XContent.hpp>
#include <com/sun/star/ucb/XCommandProcessor.hpp>
#include <com/sun/star/sdbc/XRow.hpp>

using com::sun::star::beans::PropertyValue;
using com::sun::star::beans::Property;
using com::sun::star::ucb::XContent;
using com::sun::star::ucb::XCommandProcessor;

namespace binfilter {

/*========================================================================
 *
 * SvBindingTransport_Impl interface.
 *
 *======================================================================*/
class SvBindingTransport_Impl
{
public:
    /** getProcessServiceFactory.
     */
    static com::sun::star::uno::Reference<com::sun::star::uno::XInterface>
    getProcessServiceFactory (void);

    /** createContent.
     */
    static com::sun::star::uno::Reference<XContent>
    createContent (
        const rtl::OUString &rUrl);

    /** getProperties.
     */
    static com::sun::star::uno::Any
    getProperties (
        const com::sun::star::uno::Reference<XCommandProcessor> &rxProc,
        const com::sun::star::uno::Sequence<Property>           &rxProp);

    /** setProperties.
     */
    static void setProperties (
        const com::sun::star::uno::Reference<XCommandProcessor> &rxProc,
        const com::sun::star::uno::Sequence<PropertyValue>           &rxProp);
};

/*========================================================================
 *
 * The End.
 *
 *======================================================================*/

}

#endif /* !_TRANSUNO_HXX */

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
