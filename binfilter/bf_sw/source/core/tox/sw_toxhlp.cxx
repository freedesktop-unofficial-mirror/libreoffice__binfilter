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

#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <comphelper/processfactory.hxx>
#include <com/sun/star/i18n/XExtendedIndexEntrySupplier.hpp>
#include <rtl/strbuf.hxx>
#include <bf_tools/string.hxx>
#include <tools/debug.hxx>

#include <toxwrap.hxx>
#include <legacysmgr/legacy_binfilters_smgr.hxx>
namespace binfilter {

 IndexEntrySupplierWrapper::IndexEntrySupplierWrapper()
 {
     ::com::sun::star::uno::Reference<
             ::com::sun::star::lang::XMultiServiceFactory > rxMSF =
                                     ::legacy_binfilters::getLegacyProcessServiceFactory();

    try {
        ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > xI =
            rxMSF->createInstance( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.i18n.IndexEntrySupplier" )) );
        if( xI.is() )
        {
            ::com::sun::star::uno::Any x = xI->queryInterface( ::getCppuType(
                     (const ::com::sun::star::uno::Reference< ::com::sun::star::i18n::XExtendedIndexEntrySupplier>*)0) );
            x >>= xIES;
        }
    }
    catch ( const ::com::sun::star::uno::Exception& e )
    {
 #ifdef DBG_UTIL
        rtl::OStringBuffer aMsg("IndexEntrySupplierWrapper: Exception caught\n");
        aMsg.append(rtl::OUStringToOString(e.Message, RTL_TEXTENCODING_UTF8));
        DBG_ERRORFILE(aMsg.getStr());
 #endif
    }
 }

 IndexEntrySupplierWrapper::~IndexEntrySupplierWrapper()
 {
 }

 ::com::sun::star::uno::Sequence< ::rtl::OUString >
 IndexEntrySupplierWrapper::GetAlgorithmList( const ::com::sun::star::lang::Locale& rLcl ) const
 {
     ::com::sun::star::uno::Sequence< ::rtl::OUString > sRet;

    try {
         sRet = xIES->getAlgorithmList( rLcl );
    }
    catch ( const ::com::sun::star::uno::Exception& e )
    {
 #ifdef DBG_UTIL
        rtl::OStringBuffer aMsg("getAlgorithmList: Exception caught\n");
        aMsg.append(rtl::OUStringToOString(e.Message, RTL_TEXTENCODING_UTF8));
        DBG_ERRORFILE(aMsg.getStr());
 #endif
    }
    return sRet;
 }

 sal_Bool IndexEntrySupplierWrapper::LoadAlgorithm(
         const ::com::sun::star::lang::Locale& rLcl,
         const String& sSortAlgorithm, long nOptions ) const
 {
     sal_Bool bRet = sal_False;
    try {
         bRet = xIES->loadAlgorithm( rLcl, sSortAlgorithm, nOptions );
    }
    catch (const ::com::sun::star::uno::Exception& e)
    {
 #ifdef DBG_UTIL
        rtl::OStringBuffer aMsg("loadAlgorithm: Exception caught\n");
        aMsg.append(rtl::OUStringToOString(e.Message, RTL_TEXTENCODING_UTF8));
        DBG_ERRORFILE(aMsg.getStr());
 #endif
    }
     return bRet;
 }

 sal_Int16 IndexEntrySupplierWrapper::CompareIndexEntry(
             const String& rTxt1, const String& rTxtReading1,
             const ::com::sun::star::lang::Locale& rLocale1,
             const String& rTxt2, const String& rTxtReading2,
             const ::com::sun::star::lang::Locale& rLocale2 ) const
 {
     sal_Int16 nRet = 0;
    try {
         nRet = xIES->compareIndexEntry( rTxt1, rTxtReading1, rLocale1,
                                         rTxt2, rTxtReading2, rLocale2 );
    }
    catch (const ::com::sun::star::uno::Exception& e)
    {
 #ifdef DBG_UTIL
        rtl::OStringBuffer aMsg( "compareIndexEntry: Exception caught\n" );
        aMsg.append(rtl::OUStringToOString(e.Message, RTL_TEXTENCODING_UTF8));
        DBG_ERRORFILE(aMsg.getStr());
 #endif
    }
     return nRet;
 }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
