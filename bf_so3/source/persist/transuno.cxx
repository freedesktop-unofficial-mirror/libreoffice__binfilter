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

#ifndef _RTL_WSTRING
#include <rtl/ustring.h>
#endif

#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/uno/Sequence.hxx>
#include <com/sun/star/uno/XInterface.hpp>

#include <com/sun/star/beans/PropertyValue.hpp>

#include <com/sun/star/ucb/UniversalContentBroker.hpp>
#include <com/sun/star/ucb/XContent.hpp>
#include <com/sun/star/ucb/XUniversalContentBroker.hpp>

#include <comphelper/processfactory.hxx>

#include <transuno.hxx>

/*========================================================================
 *
 * SvBindingTransport_Impl internals.
 *
 *======================================================================*/
using namespace com::sun::star::ucb;
using namespace com::sun::star::uno;
using namespace com::sun::star::sdbc;

namespace binfilter {

typedef com::sun::star::lang::XMultiServiceFactory factory_type;

/*========================================================================
 *
 * SvBindingTransport_Impl implementation.
 *
 *======================================================================*/
/*
 * getProcessServiceFactory.
 */
com::sun::star::uno::Reference<com::sun::star::uno::XInterface>
SvBindingTransport_Impl::getProcessServiceFactory (void)
{
    return com::sun::star::uno::Reference<com::sun::star::uno::XInterface>(
        comphelper::getProcessServiceFactory(), com::sun::star::uno::UNO_QUERY_THROW);
}

/*
 * createContent.
 */
com::sun::star::uno::Reference<XContent>
SvBindingTransport_Impl::createContent (const rtl::OUString &rUrl)
{
    com::sun::star::uno::Reference<XUniversalContentBroker>
        xBroker (UniversalContentBroker::create(comphelper::getProcessComponentContext()));
    return xBroker->queryContent (xBroker->createContentIdentifier (rUrl));
}

/*
 * getProperties.
 */
Any SvBindingTransport_Impl::getProperties ( const Reference<XCommandProcessor> &rxProcessor, const Sequence<Property> &rProperties)
{
    Any aResult;
    if (rxProcessor.is() && rProperties.getLength())
    {
        try
        {
            com::sun::star::uno::Reference<XCommandEnvironment> xEnvironment;
            Command aCommand;
            aCommand.Name     = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "getPropertyValues" ));
            aCommand.Handle   = -1; /* unknown */
            aCommand.Argument <<= rProperties;
            aResult = rxProcessor->execute( aCommand, 0, xEnvironment );
        }
        catch (com::sun::star::uno::Exception &)
        {
        }
    }

    return aResult;
}

/*
 * setProperties.
 */
void SvBindingTransport_Impl::setProperties ( const Reference<XCommandProcessor> &rxProcessor, const Sequence<PropertyValue> &rProperties)
{
    if (rxProcessor.is() && rProperties.getLength())
    {
        try
        {
            Reference<XCommandEnvironment> xEnvironment;
            Command aCommand;
            aCommand.Name     = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "setPropertyValues" ));
            aCommand.Handle   = -1; /* unknown */
            aCommand.Argument <<= rProperties;
            rxProcessor->execute( aCommand, 0, xEnvironment );
        }
        catch (com::sun::star::uno::Exception &)
        {
        }
    }
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
