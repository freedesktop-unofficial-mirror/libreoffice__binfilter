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

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <SwXFilterOptions.hxx>

#include <shellio.hxx>
#include <swdll.hxx>
#include <unoprnms.hxx>

#include <osl/mutex.hxx>
#include <vcl/svapp.hxx>
#include <tools/shl.hxx>
#include <vcl/msgbox.hxx>

#include <com/sun/star/lang/XUnoTunnel.hpp>
#include <com/sun/star/ui/dialogs/ExecutableDialogResults.hpp>
#include <unotools/ucbstreamhelper.hxx>
#include <unotxdoc.hxx>
#include <com/sun/star/io/XInputStream.hpp>
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::ui::dialogs;
using namespace ::com::sun::star::document;
using namespace ::com::sun::star::lang;

#define SWFILTEROPTIONSOBJ_SERVICE      RTL_CONSTASCII_USTRINGPARAM("com.sun.star.ui.dialogs.FilterOptionsDialog")
#define SWFILTEROPTIONSOBJ_IMPLNAME     RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.Writer.FilterOptionsDialog")
#define FILTER_OPTIONS_NAME             RTL_CONSTASCII_USTRINGPARAM("FilterOptions")

SwXFilterOptions::SwXFilterOptions() :
    bExport( sal_False )
{
}

SwXFilterOptions::~SwXFilterOptions()
{
}

::rtl::OUString  SwXFilterOptions::getImplementationName_Static()
{
    return ::rtl::OUString(SWFILTEROPTIONSOBJ_IMPLNAME);
}

uno::Sequence< ::rtl::OUString> SwXFilterOptions::getSupportedServiceNames_Static()
{
    ::rtl::OUString sService(SWFILTEROPTIONSOBJ_SERVICE);
    return uno::Sequence< ::rtl::OUString> (&sService, 1);
}

uno::Sequence< beans::PropertyValue > SwXFilterOptions::getPropertyValues() throw (uno::RuntimeException)
{
    uno::Sequence<beans::PropertyValue> aRet(1);
    beans::PropertyValue* pArray = aRet.getArray();

    pArray[0].Name = ::rtl::OUString( FILTER_OPTIONS_NAME );
    pArray[0].Value <<= sFilterOptions;

    return aRet;
}

void   SwXFilterOptions::setPropertyValues( const uno::Sequence<beans::PropertyValue >& aProps )
    throw (beans::UnknownPropertyException, beans::PropertyVetoException,
       IllegalArgumentException, WrappedTargetException, uno::RuntimeException)
{
    const beans::PropertyValue* pPropArray = aProps.getConstArray();
    long nPropCount = aProps.getLength();
    for (long i = 0; i < nPropCount; i++)
    {
        const beans::PropertyValue& rProp = pPropArray[i];
        ::rtl::OUString aPropName = rProp.Name;

        if ( aPropName.equalsAscii( SW_PROP_NAME_STR(UNO_NAME_FILTER_NAME) ) )
            rProp.Value >>= sFilterName;
        else if ( aPropName == ::rtl::OUString(FILTER_OPTIONS_NAME) )
            rProp.Value >>= sFilterOptions;
        else if ( aPropName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( "InputStream" ) ) )
            rProp.Value >>= xInputStream;
    }
}

void   SwXFilterOptions::setTitle( const ::rtl::OUString& /*aTitle*/ )
    throw (uno::RuntimeException)
{
}

sal_Int16 SwXFilterOptions::execute() throw (uno::RuntimeException)
{
    sal_Int16 nRet = ui::dialogs::ExecutableDialogResults::CANCEL;

    SvStream* pInStream = NULL;
    if ( xInputStream.is() )
        pInStream = ::utl::UcbStreamHelper::CreateStream( xInputStream );

    uno::Reference< XUnoTunnel > xTunnel(xModel, uno::UNO_QUERY);
    SwDocShell* pDocShell = 0;
    if(xTunnel.is())
    {
        SwXTextDocument* pXDoc = (SwXTextDocument*)xTunnel->getSomething(SwXTextDocument::getUnoTunnelId());
        pDocShell = pXDoc ? pXDoc->GetDocShell() : 0;
    }
    if(pDocShell)
    {
    }

    if( pInStream )
        delete pInStream;

    return nRet;
}

void   SwXFilterOptions::setTargetDocument( const uno::Reference< XComponent >& xDoc )
    throw (IllegalArgumentException, uno::RuntimeException)
{
    bExport = sal_False;
    xModel = xDoc;
}

void   SwXFilterOptions::setSourceDocument( const uno::Reference<XComponent >& xDoc )
        throw (IllegalArgumentException,uno::RuntimeException)
{
    bExport = sal_True;
    xModel = xDoc;
}

::rtl::OUString SwXFilterOptions::getImplementationName() throw(uno::RuntimeException)
{
    return ::rtl::OUString(SWFILTEROPTIONSOBJ_IMPLNAME);
}

sal_Bool SwXFilterOptions::supportsService( const ::rtl::OUString& rServiceName )
    throw(uno::RuntimeException)
{
    return rServiceName == ::rtl::OUString(SWFILTEROPTIONSOBJ_SERVICE);
}

uno::Sequence< ::rtl::OUString > SwXFilterOptions::getSupportedServiceNames()
                throw(uno::RuntimeException)
{
    return SwXFilterOptions::getSupportedServiceNames_Static();
}


uno::Reference<uno::XInterface> SAL_CALL SwXFilterOptions_createInstance(
                        const uno::Reference<lang::XMultiServiceFactory>& )
{
    SolarMutexGuard aGuard;
    SW_DLL()->Load();       // load module

    return (::cppu::OWeakObject*) new SwXFilterOptions;
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
