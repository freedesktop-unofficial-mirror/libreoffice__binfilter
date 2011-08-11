/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#include <com/sun/star/beans/PropertyAttribute.hpp>
#include <com/sun/star/task/XStatusIndicatorSupplier.hpp>
#include <com/sun/star/document/XImporter.hpp>
#include <com/sun/star/document/XFilter.hpp>
#include <com/sun/star/document/XExporter.hpp>

#include <bf_sfx2/docfile.hxx>
#include <bf_svtools/sfxecode.hxx>

#include "SchXMLWrapper.hxx"

#include <unotools/streamwrap.hxx>
#include <bf_svx/xmlgrhlp.hxx>
#include <tools/debug.hxx>

#include <comphelper/genericpropertyset.hxx>

#include <bf_svtools/saveopt.hxx>

#include <com/sun/star/xml/sax/XParser.hpp>
#include <com/sun/star/io/XActiveDataSource.hpp>
#include <com/sun/star/xml/sax/SAXParseException.hpp>
#include <com/sun/star/packages/zip/ZipIOException.hpp>

#include <legacysmgr/legacy_binfilters_smgr.hxx>
namespace binfilter {

#define XML_STRING(i, x) sal_Char const i[sizeof(x)] = x
#define MAP_LEN(x) x, sizeof(x) - 1

XML_STRING( sXML_metaStreamName,        "meta.xml");
XML_STRING( sXML_styleStreamName,       "styles.xml" );
XML_STRING( sXML_contentStreamName,     "content.xml" );
XML_STRING( sXML_oldContentStreamName,  "Content.xml" );

XML_STRING( sXML_export_chart_meta_service,         "com.sun.star.comp.Chart.XMLMetaExporter" );
XML_STRING( sXML_export_chart_styles_service,       "com.sun.star.comp.Chart.XMLStylesExporter" );
XML_STRING( sXML_export_chart_content_service,      "com.sun.star.comp.Chart.XMLContentExporter" );
XML_STRING( sXML_export_chart_old_content_service,  "com.sun.star.office.sax.exporter.Chart" );

XML_STRING( sXML_import_chart_meta_service,         "com.sun.star.comp.Chart.XMLMetaImporter" );
XML_STRING( sXML_import_chart_styles_service,       "com.sun.star.comp.Chart.XMLStylesImporter" );
XML_STRING( sXML_import_chart_content_service,      "com.sun.star.comp.Chart.XMLContentImporter" );
XML_STRING( sXML_import_chart_old_content_service,  "com.sun.star.office.sax.importer.Chart" );

using namespace ::com::sun::star;
using namespace ::rtl;
using namespace comphelper;

/*N*/ SchXMLWrapper::SchXMLWrapper( uno::Reference< frame::XModel >& xModel,
/*N*/                             SvStorage& rStorage,
/*N*/                             sal_Bool bShowProgress ) :
/*N*/       mxModel( xModel ),
/*N*/       mrStorage( rStorage ),
/*N*/       mbShowProgress( bShowProgress )
/*N*/ {}

// -----------------------------------------------------------------------------

/*N*/ sal_Bool SchXMLWrapper::ExportStream(
/*N*/   const ::rtl::OUString& rsStreamName,
/*N*/   const ::rtl::OUString& rsServiceName,
/*N*/   uno::Reference< io::XActiveDataSource >& xDataSource,
/*N*/   uno::Reference< lang::XMultiServiceFactory>& xServiceFactory,
/*N*/   uno::Sequence< uno::Any >& aArgs )
/*N*/ {
/*N*/   sal_Bool bRet = sal_False;
/*N*/
/*N*/   try
/*N*/   {
/*N*/       // create output stream
/*N*/       SvStorageStreamRef rOutputStream( mrStorage.OpenStream(
/*N*/           String( rsStreamName ), STREAM_WRITE | STREAM_SHARE_DENYWRITE | STREAM_TRUNC ));
/*N*/
/*N*/       ::rtl::OUString sMIMEType( RTL_CONSTASCII_USTRINGPARAM( "text/xml" ) );
/*N*/       uno::Any aAny;
/*N*/       aAny <<= sMIMEType;
/*N*/       rOutputStream->SetProperty( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "MediaType" )), aAny );
/*N*/
/*N*/         // "Encrypted" means "Encryptable". Has to be set for all but the meta stream (which doesn't exist in charts)
/*N*/         aAny <<= (sal_Bool)(sal_True);
/*N*/         rOutputStream->SetProperty( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "Encrypted" )), aAny );
/*N*/
/*N*/       rOutputStream->SetBufferSize( 0x4000 );    // 16*1024
/*N*/
/*N*/       if( xDataSource.is())
/*N*/           xDataSource->setOutputStream( new ::utl::OOutputStreamWrapper( *rOutputStream ));
/*N*/
/*N*/       uno::Reference< document::XFilter > xFilter(
/*N*/           xServiceFactory->createInstanceWithArguments( rsServiceName, aArgs ),
/*N*/           uno::UNO_QUERY );
/*N*/
/*N*/       if( xFilter.is())
/*N*/       {
/*N*/           uno::Reference< document::XExporter > xExporter( xFilter, uno::UNO_QUERY );
/*N*/           if( xExporter.is())
/*N*/           {
/*N*/               uno::Reference< lang::XComponent > xModelComponent( mxModel, uno::UNO_QUERY );
/*N*/               xExporter->setSourceDocument( xModelComponent );
/*N*/           }
/*N*/
/*N*/           // empty Descriptior (formerly FileName was given)
/*N*/           uno::Sequence< beans::PropertyValue > aEmptyDescriptor( 0 );
/*N*/           bRet = xFilter->filter( aEmptyDescriptor );
/*N*/
/*N*/           if( bRet && rOutputStream.Is())
/*N*/               rOutputStream->Commit();
/*N*/       }
/*N*/   }
/*N*/   catch( uno::Exception aEx )
/*N*/   {
/*N*/ #if OSL_DEBUG_LEVEL > 1
/*N*/       // convert ::rtl::OUString => tools String => ByteString
/*?*/       String aStr( aEx.Message );
/*?*/       ByteString aBStr( aStr, RTL_TEXTENCODING_ASCII_US );
/*?*/       ByteString aBStrStreamName = ByteString( String( rsStreamName ), RTL_TEXTENCODING_ASCII_US );
/*?*/       OSL_TRACE( "Exception caught during Export of \"%s\" stream(): %s",
/*?*/                   aBStrStreamName.GetBuffer(),
/*?*/                   aBStr.GetBuffer());
/*N*/ #endif
/*N*/   }
/*N*/
/*N*/   return bRet;
/*N*/ }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
