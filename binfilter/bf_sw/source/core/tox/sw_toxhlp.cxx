/*************************************************************************
 *
 *  $RCSfile: sw_toxhlp.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:51:38 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/


#pragma hdrstop

#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif
#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif
#ifndef _COM_SUN_STAR_I18N_XINDEXENTRYSUPPLIER_HPP_
#include <com/sun/star/i18n/XExtendedIndexEntrySupplier.hpp>
#endif
#ifndef _STRING_HXX
#include <tools/string.hxx>
#endif
#ifndef _DEBUG_HXX
#include <tools/debug.hxx>
#endif

#ifndef _TOXWRAP_HXX
#include <toxwrap.hxx>
#endif
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {

//STRIP001 IndexEntrySupplierWrapper::IndexEntrySupplierWrapper()
//STRIP001 {
//STRIP001     ::com::sun::star::uno::Reference<
//STRIP001             ::com::sun::star::lang::XMultiServiceFactory > rxMSF =
//STRIP001                                     ::legacy_binfilters::getLegacyProcessServiceFactory();
//STRIP001
//STRIP001  try {
//STRIP001      STAR_REFERENCE( uno::XInterface ) xI =
//STRIP001          rxMSF->createInstance( ::rtl::OUString::createFromAscii(
//STRIP001                                 "com.sun.star.i18n.IndexEntrySupplier" ) );
//STRIP001      if( xI.is() )
//STRIP001      {
//STRIP001          UNO_NMSPC::Any x = xI->queryInterface( ::getCppuType(
//STRIP001                     (const ::com::sun::star::uno::Reference< ::com::sun::star::i18n::XExtendedIndexEntrySupplier>*)0) );
//STRIP001          x >>= xIES;
//STRIP001      }
//STRIP001  }
//STRIP001  catch ( UNO_NMSPC::Exception& e )
//STRIP001  {
//STRIP001 #ifndef PRODUCT
//STRIP001      ByteString aMsg( "IndexEntrySupplierWrapper: Exception caught\n" );
//STRIP001      aMsg += ByteString( String( e.Message ), RTL_TEXTENCODING_UTF8 );
//STRIP001      DBG_ERRORFILE( aMsg.GetBuffer() );
//STRIP001 #endif
//STRIP001  }
//STRIP001 }

//STRIP001 IndexEntrySupplierWrapper::~IndexEntrySupplierWrapper()
//STRIP001 {
//STRIP001 }

//STRIP001 String IndexEntrySupplierWrapper::GetIndexKey( const String& rTxt,
//STRIP001                                                const String& rTxtReading,
//STRIP001                                                const STAR_NMSPC::lang::Locale& rLocale ) const
//STRIP001 {
//STRIP001  String sRet;
//STRIP001  try {
//STRIP001         sRet = xIES->getIndexKey( rTxt, rTxtReading, rLocale );
//STRIP001  }
//STRIP001  catch ( UNO_NMSPC::Exception& e )
//STRIP001  {
//STRIP001 #ifndef PRODUCT
//STRIP001         ByteString aMsg( "getIndexKey: Exception caught\n" );
//STRIP001      aMsg += ByteString( String( e.Message ), RTL_TEXTENCODING_UTF8 );
//STRIP001      DBG_ERRORFILE( aMsg.GetBuffer() );
//STRIP001 #endif
//STRIP001  }
//STRIP001  return sRet;
//STRIP001 }

//STRIP001 String IndexEntrySupplierWrapper::GetFollowingText( BOOL bMorePages ) const
//STRIP001 {
//STRIP001  String sRet;
//STRIP001  try {
//STRIP001      sRet = xIES->getIndexFollowPageWord( bMorePages, aLcl );
//STRIP001  }
//STRIP001  catch ( UNO_NMSPC::Exception& e )
//STRIP001  {
//STRIP001 #ifndef PRODUCT
//STRIP001         ByteString aMsg( "getIndexFollowPageWord: Exception caught\n" );
//STRIP001      aMsg += ByteString( String( e.Message ), RTL_TEXTENCODING_UTF8 );
//STRIP001      DBG_ERRORFILE( aMsg.GetBuffer() );
//STRIP001 #endif
//STRIP001  }
//STRIP001  return sRet;
//STRIP001 }

//STRIP001 STAR_NMSPC::uno::Sequence< ::rtl::OUString >
//STRIP001 IndexEntrySupplierWrapper::GetAlgorithmList( const STAR_NMSPC::lang::Locale& rLcl ) const
//STRIP001 {
//STRIP001     ::com::sun::star::uno::Sequence< ::rtl::OUString > sRet;
//STRIP001
//STRIP001  try {
//STRIP001         sRet = xIES->getAlgorithmList( rLcl );
//STRIP001  }
//STRIP001  catch ( UNO_NMSPC::Exception& e )
//STRIP001  {
//STRIP001 #ifndef PRODUCT
//STRIP001         ByteString aMsg( "getAlgorithmList: Exception caught\n" );
//STRIP001      aMsg += ByteString( String( e.Message ), RTL_TEXTENCODING_UTF8 );
//STRIP001      DBG_ERRORFILE( aMsg.GetBuffer() );
//STRIP001 #endif
//STRIP001  }
//STRIP001  return sRet;
//STRIP001 }

//STRIP001 STAR_NMSPC::uno::Sequence < ::com::sun::star::lang::Locale >
//STRIP001 IndexEntrySupplierWrapper::GetLocaleList() const
//STRIP001 {
//STRIP001     ::com::sun::star::uno::Sequence< ::com::sun::star::lang::Locale > sRet;
//STRIP001
//STRIP001     try {
//STRIP001         sRet = xIES->getLocaleList();
//STRIP001     }
//STRIP001     catch ( UNO_NMSPC::Exception& e )
//STRIP001     {
//STRIP001 #ifndef PRODUCT
//STRIP001         ByteString aMsg( "getLocaleList: Exception caught\n" );
//STRIP001         aMsg += ByteString( String( e.Message ), RTL_TEXTENCODING_UTF8 );
//STRIP001         DBG_ERRORFILE( aMsg.GetBuffer() );
//STRIP001 #endif
//STRIP001     }
//STRIP001     return sRet;
//STRIP001 }

//STRIP001 sal_Bool IndexEntrySupplierWrapper::LoadAlgorithm(
//STRIP001         const STAR_NMSPC::lang::Locale& rLcl,
//STRIP001         const String& sSortAlgorithm, long nOptions ) const
//STRIP001 {
//STRIP001     sal_Bool bRet = sal_False;
//STRIP001  try {
//STRIP001         bRet = xIES->loadAlgorithm( rLcl, sSortAlgorithm, nOptions );
//STRIP001  }
//STRIP001  catch ( UNO_NMSPC::Exception& e )
//STRIP001  {
//STRIP001 #ifndef PRODUCT
//STRIP001         ByteString aMsg( "loadAlgorithm: Exception caught\n" );
//STRIP001      aMsg += ByteString( String( e.Message ), RTL_TEXTENCODING_UTF8 );
//STRIP001      DBG_ERRORFILE( aMsg.GetBuffer() );
//STRIP001 #endif
//STRIP001  }
//STRIP001     return bRet;
//STRIP001 }

//STRIP001 sal_Int16 IndexEntrySupplierWrapper::CompareIndexEntry(
//STRIP001             const String& rTxt1, const String& rTxtReading1,
//STRIP001             const STAR_NMSPC::lang::Locale& rLocale1,
//STRIP001             const String& rTxt2, const String& rTxtReading2,
//STRIP001             const STAR_NMSPC::lang::Locale& rLocale2 ) const
//STRIP001 {
//STRIP001     sal_Int16 nRet = 0;
//STRIP001  try {
//STRIP001         nRet = xIES->compareIndexEntry( rTxt1, rTxtReading1, rLocale1,
//STRIP001                                         rTxt2, rTxtReading2, rLocale2 );
//STRIP001  }
//STRIP001  catch ( UNO_NMSPC::Exception& e )
//STRIP001  {
//STRIP001 #ifndef PRODUCT
//STRIP001         ByteString aMsg( "compareIndexEntry: Exception caught\n" );
//STRIP001      aMsg += ByteString( String( e.Message ), RTL_TEXTENCODING_UTF8 );
//STRIP001      DBG_ERRORFILE( aMsg.GetBuffer() );
//STRIP001 #endif
//STRIP001  }
//STRIP001     return nRet;
//STRIP001 }
}
