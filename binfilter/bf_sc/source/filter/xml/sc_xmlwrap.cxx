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

#ifdef _MSC_VER
#pragma hdrstop
#endif

// INCLUDE ---------------------------------------------------------------

#include <bf_sfx2/docfile.hxx>
#include <bf_sfx2/objsh.hxx>
#include <unotools/streamwrap.hxx>
#include <bf_svx/xmlgrhlp.hxx>
#include <bf_svtools/sfxecode.hxx>
#include <bf_sfx2/appuno.hxx>
#include <bf_svtools/itemset.hxx>
#include <bf_sfx2/sfxsids.hrc>

#include <com/sun/star/xml/sax/XParser.hpp>
#include <com/sun/star/io/XActiveDataSource.hpp>
#include <com/sun/star/io/XActiveDataControl.hpp>
#include <com/sun/star/task/XStatusIndicatorFactory.hpp>
#include <com/sun/star/beans/PropertyAttribute.hpp>
#include <comphelper/extract.hxx>
#include <comphelper/genericpropertyset.hxx>
#include <com/sun/star/lang/DisposedException.hpp>
#include <com/sun/star/packages/zip/ZipIOException.hpp>

#include <bf_svx/xmleohlp.hxx>
#include <rtl/logfile.hxx>
#include <bf_svtools/saveopt.hxx>

#include "document.hxx"
#include "xmlwrap.hxx"
#include "xmlimprt.hxx"
#include "xmlexprt.hxx"
#include "globstr.hrc"
#include "scerrors.hxx"
#include "XMLExportSharedData.hxx"
#include <legacysmgr/legacy_binfilters_smgr.hxx>
#ifndef SEQTYPE
namespace binfilter {
 #if defined(__SUNPRO_CC) && (__SUNPRO_CC == 0x500)
  #define SEQTYPE(x) (new ::com::sun::star::uno::Type( x ))
 #else
  #define SEQTYPE(x) &(x)
 #endif
#endif

#define MAP_LEN(x) x, sizeof(x) - 1

using namespace ::com::sun::star;

using rtl::OUString;

// -----------------------------------------------------------------------

ScXMLImportWrapper::ScXMLImportWrapper(ScDocument& rD, SfxMedium* pM, SvStorage* pS) :
    rDoc(rD),
    pMedium(pM),
    pStorage(pS)
{
    DBG_ASSERT( pMedium || pStorage, "ScXMLImportWrapper: Medium or Storage must be set" );
}

uno::Reference <task::XStatusIndicator> ScXMLImportWrapper::GetStatusIndicator(
    uno::Reference < frame::XModel> & rModel)
{
    uno::Reference<task::XStatusIndicator> xStatusIndicator;
    if (rModel.is())
    {
        uno::Reference<frame::XController> xController( rModel->getCurrentController());
        if( xController.is())
        {
            uno::Reference<frame::XFrame> xFrame( xController->getFrame());
            if( xFrame.is())
            {
                uno::Reference<task::XStatusIndicatorFactory> xFactory( xFrame, uno::UNO_QUERY );
                if( xFactory.is())
                {
                    try
                    {
                        xStatusIndicator = xFactory->createStatusIndicator();
                    }
                    catch( lang::DisposedException e )
                    {
                        OSL_FAIL("Exception while trying to get a Status Indicator");
                    }
                }
            }
        }
    }
    return xStatusIndicator;
}

uno::Reference <task::XStatusIndicator> ScXMLImportWrapper::GetStatusIndicator()
{
    uno::Reference<task::XStatusIndicator> xStatusIndicator;
    if (pMedium)
    {
        SfxItemSet* pSet = pMedium->GetItemSet();
        if (pSet)
        {
            const SfxUnoAnyItem* pItem = static_cast<const SfxUnoAnyItem*>(pSet->GetItem(SID_PROGRESS_STATUSBAR_CONTROL));
            if (pItem)
            {
                uno::Any aAny(pItem->GetValue());
                aAny >>= xStatusIndicator;
            }
        }
    }
    return xStatusIndicator;
}

sal_uInt32 ScXMLImportWrapper::ImportFromComponent(uno::Reference<lang::XMultiServiceFactory>& xServiceFactory,
    uno::Reference<frame::XModel>& xModel, uno::Reference<uno::XInterface>& xXMLParser,
    xml::sax::InputSource& aParserInput,
    const ::rtl::OUString& sComponentName, const ::rtl::OUString& sDocName,
    const ::rtl::OUString& sOldDocName, uno::Sequence<uno::Any>& aArgs,
    sal_Bool bMustBeSuccessfull)
{
    SvStorageStreamRef xDocStream;
    if ( !pStorage && pMedium )
        pStorage = pMedium->GetStorage();

    // Get data source ...

    uno::Reference< uno::XInterface > xPipe;
    uno::Reference< io::XActiveDataSource > xSource;

    sal_Bool bEncrypted = sal_False;
    if( pStorage )
    {
        if (pStorage->IsStream(sDocName))
            xDocStream = pStorage->OpenStream( sDocName,
                                  STREAM_READ | STREAM_NOCREATE );
        else if (sOldDocName.getLength() && pStorage->IsStream(sOldDocName))
            xDocStream = pStorage->OpenStream( sOldDocName,
                                  STREAM_READ | STREAM_NOCREATE );
        else
            return sal_False;
        xDocStream->SetBufferSize( 16*1024 );
        aParserInput.aInputStream = xDocStream->GetXInputStream();

        uno::Any aAny;
        bEncrypted = xDocStream->GetProperty(
                            OUString( RTL_CONSTASCII_USTRINGPARAM("Encrypted") ), aAny ) &&
                        aAny.getValueType() == ::getBooleanCppuType() &&
                        *(sal_Bool *)aAny.getValue();
    }
    else
        return SCERR_IMPORT_UNKNOWN;

    sal_uInt32 nReturn(0);
    uno::Reference<xml::sax::XDocumentHandler> xDocHandler(
        xServiceFactory->createInstanceWithArguments(
            sComponentName, aArgs ),
        uno::UNO_QUERY );
    DBG_ASSERT( xDocHandler.is(), "can't get Calc importer" );
    uno::Reference<document::XImporter> xImporter( xDocHandler, uno::UNO_QUERY );
    uno::Reference<lang::XComponent> xComponent( xModel, uno::UNO_QUERY );
    if (xImporter.is())
        xImporter->setTargetDocument( xComponent );

    // connect parser and filter
    uno::Reference<xml::sax::XParser> xParser( xXMLParser, uno::UNO_QUERY );
    xParser->setDocumentHandler( xDocHandler );

    // parse
    if( xSource.is() )
    {
        uno::Reference<io::XActiveDataControl> xSourceControl( xSource, uno::UNO_QUERY );
        if( xSourceControl.is() )
            xSourceControl->start();
    }

    try
    {
        xParser->parseStream( aParserInput );
    }
    catch( xml::sax::SAXParseException& r )
    {
        if( bEncrypted )
            nReturn = ERRCODE_SFX_WRONGPASSWORD;
        else
        {

#ifdef DBG_UTIL
            ByteString aError( "SAX parse exception catched while importing:\n" );
            aError += ByteString( String( r.Message), RTL_TEXTENCODING_ASCII_US );
            OSL_FAIL( aError.GetBuffer() );
#endif

            String sErr( String::CreateFromInt32( r.LineNumber ));
            sErr += ',';
            sErr += String::CreateFromInt32( r.ColumnNumber );

            if( sDocName.getLength() )
            {
                nReturn = *new TwoStringErrorInfo(
                                (bMustBeSuccessfull ? SCERR_IMPORT_FILE_ROWCOL
                                                        : SCWARN_IMPORT_FILE_ROWCOL),
                                sDocName, sErr,
                                ERRCODE_BUTTON_OK | ERRCODE_MSG_ERROR );
            }
            else
            {
                DBG_ASSERT( bMustBeSuccessfull, "Warnings are not supported" );
                nReturn = *new StringErrorInfo( SCERR_IMPORT_FORMAT_ROWCOL, sErr,
                                 ERRCODE_BUTTON_OK | ERRCODE_MSG_ERROR );
            }
        }
    }
    catch( xml::sax::SAXException& r )
    {
        if( bEncrypted )
            nReturn = ERRCODE_SFX_WRONGPASSWORD;
        else
        {

#ifdef DBG_UTIL
            ByteString aError( "SAX exception catched while importing:\n" );
            aError += ByteString( String( r.Message), RTL_TEXTENCODING_ASCII_US );
            OSL_FAIL( aError.GetBuffer() );
#endif
            nReturn = SCERR_IMPORT_FORMAT;
        }
    }
    catch( packages::zip::ZipIOException& r )
    {
#ifdef DBG_UTIL
        ByteString aError( "Zip exception catched while importing:\n" );
        aError += ByteString( String( r.Message), RTL_TEXTENCODING_ASCII_US );
        OSL_FAIL( aError.GetBuffer() );
#endif
        nReturn = ERRCODE_IO_BROKENPACKAGE;
    }
    catch( io::IOException& r )
    {
#ifdef DBG_UTIL
        ByteString aError( "IO exception catched while importing:\n" );
        aError += ByteString( String( r.Message), RTL_TEXTENCODING_ASCII_US );
        OSL_FAIL( aError.GetBuffer() );
#endif
        nReturn = SCERR_IMPORT_OPEN;
    }
    catch( uno::Exception& r )
    {
#ifdef DBG_UTIL
        ByteString aError( "uno exception catched while importing:\n" );
        aError += ByteString( String( r.Message), RTL_TEXTENCODING_ASCII_US );
        OSL_FAIL( aError.GetBuffer() );
#endif
        nReturn = SCERR_IMPORT_UNKNOWN;
    }

    if ( xDocHandler.is() )
    {
        ScXMLImport* pImport = static_cast<ScXMLImport*>(SvXMLImport::getImplementation(xDocHandler));

        if (pImport && pImport->HasRangeOverflow() && !nReturn)
            nReturn = pImport->GetRangeOverflowType();
    }

    // free the component
    xParser->setDocumentHandler( NULL );

    // success!
    return nReturn;
}

sal_Bool ScXMLImportWrapper::ExportToComponent(uno::Reference<lang::XMultiServiceFactory>& xServiceFactory,
    uno::Reference<frame::XModel>& xModel, uno::Reference<uno::XInterface>& xWriter,
    uno::Sequence<beans::PropertyValue>& aDescriptor, const ::rtl::OUString& sName,
    const ::rtl::OUString& sMediaType, const ::rtl::OUString& sComponentName,
    const sal_Bool bPlainText, uno::Sequence<uno::Any>& aArgs, ScMySharedData*& pSharedData)
{
    sal_Bool bRet(sal_False);
    uno::Reference<io::XOutputStream> xOut;
    SvStorageStreamRef xStream;

    if( pStorage )
    {
        // #96807#; trunc stream before use, because it could be an existing stream
        // and the new content could be shorter than the old content. In this case
        // would not all be over written by the new content and the xml file
        // would not be valid.
        xStream = pStorage->OpenStream( sName,
                                STREAM_WRITE | STREAM_SHARE_DENYWRITE | STREAM_TRUNC );
        uno::Any aAny; aAny <<= sMediaType;
        xStream->SetProperty(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("MediaType")), aAny);
        if (bPlainText)
        {
            aAny = ::cppu::bool2any(sal_False);
            xStream->SetProperty(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Compressed")), aAny);
        }
        else
        {
            aAny = ::cppu::bool2any(sal_True);
            xStream->SetProperty(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Encrypted")), aAny);
        }
        xStream->SetBufferSize( 16*1024 );
        xOut = new ::utl::OOutputStreamWrapper( *xStream );
    }
    // #99667#; no longer necessary
/*  else if ( pMedium )
    {
        xOut = pMedium->GetDataSink();
    }*/

    uno::Reference<io::XActiveDataSource> xSrc( xWriter, uno::UNO_QUERY );
    xSrc->setOutputStream( xOut );


    uno::Reference<document::XFilter> xFilter(
        xServiceFactory->createInstanceWithArguments( sComponentName , aArgs ),
            uno::UNO_QUERY );
    DBG_ASSERT( xFilter.is(), "can't get exporter" );
    uno::Reference<document::XExporter> xExporter( xFilter, uno::UNO_QUERY );
    uno::Reference<lang::XComponent> xComponent( xModel, uno::UNO_QUERY );
    if (xExporter.is())
        xExporter->setSourceDocument( xComponent );

    if ( xFilter.is() )
    {
        ScXMLExport* pExport = static_cast<ScXMLExport*>(SvXMLExport::getImplementation(xFilter));
        pExport->SetSharedData(pSharedData);
        bRet = xFilter->filter( aDescriptor );
        pSharedData = pExport->GetSharedData();

        if (xStream.Is())
            xStream->Commit();
    }
    return bRet;
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
