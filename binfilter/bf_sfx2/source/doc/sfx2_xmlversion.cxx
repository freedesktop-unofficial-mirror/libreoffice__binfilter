/*************************************************************************
 *
 *  $RCSfile: sfx2_xmlversion.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 14:53:50 $
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
 *  Contributor(s): Martin Gallwey (gallwey@sun.com)
 *
 *
 ************************************************************************/

#ifndef  _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif

#ifndef _UTL_STREAM_WRAPPER_HXX_
#include <unotools/streamwrap.hxx>
#endif

#ifndef _SFX_XMLVERSION_HXX
#include <xmlversion.hxx>
#endif

#ifndef  _XMLOFF_XMLMETAE_HXX
#include <bf_xmloff/xmlmetae.hxx>
#endif

#ifndef  _XMLOFF_XMLKYWD_HXX
#include <bf_xmloff/xmlkywd.hxx>
#endif

#ifndef  _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif

#ifndef  _COM_SUN_STAR_IO_XACTIVEDATASOURCE_HPP_
#include <com/sun/star/io/XActiveDataSource.hpp>
#endif
#ifndef  _COM_SUN_STAR_IO_XOUTPUTSTREAM_HPP_
#include <com/sun/star/io/XOutputStream.hpp>
#endif

#ifndef  _COM_SUN_STAR_UTIL_DATETIME_HPP_
#include <com/sun/star/util/DateTime.hpp>
#endif

#ifndef  _COM_SUN_STAR_XML_SAX_INPUTSOURCE_HPP_
#include <com/sun/star/xml/sax/InputSource.hpp>
#endif
#ifndef  _COM_SUN_STAR_XML_SAX_XPARSER_HPP_
#include <com/sun/star/xml/sax/XParser.hpp>
#endif

#ifndef _SFXDOCFILE_HXX
#include <docfile.hxx>
#endif

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif

#ifndef _XMLOFF_NMSPMAP_HXX
#include <bf_xmloff/nmspmap.hxx>
#endif

#ifndef _XMLOFF_XMLNMSPE_HXX
#include <bf_xmloff/xmlnmspe.hxx>
#endif

namespace binfilter {

using namespace ::com::sun::star::xml::sax;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star;
using namespace ::rtl;

// ------------------------------------------------------------------------

sal_Char __FAR_DATA XMLN_VERSIONSLIST[] = "VersionList.xml";

// ------------------------------------------------------------------------
// #110680#
/*?*/ SfxXMLVersListExport_Impl::SfxXMLVersListExport_Impl(
/*?*/   const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xServiceFactory,
/*?*/   const SfxVersionTableDtor *pVersions,
/*?*/     const OUString &rFileName,
/*?*/     Reference< XDocumentHandler > &rHandler )
/*?*/ : mpVersions( pVersions ),
/*?*/     SvXMLExport( xServiceFactory, rFileName, rHandler )
/*?*/ {
/*?*/
/*?*/     _GetNamespaceMap().AddAtIndex( XML_NAMESPACE_DC_IDX, sXML_np_dc,
/*?*/                                    sXML_n_dc, XML_NAMESPACE_DC );
/*?*/     _GetNamespaceMap().AddAtIndex( XML_NAMESPACE_FRAMEWORK_IDX, sXML_np_versions_list,
/*?*/                                    sXML_n_versions_list, XML_NAMESPACE_FRAMEWORK );
/*?*/ }

// ------------------------------------------------------------------------
/*?*/ sal_uInt32 SfxXMLVersListExport_Impl::exportDoc( enum ::binfilter::xmloff::token::XMLTokenEnum eClass )
/*?*/ {
/*?*/     GetDocHandler()->startDocument();
/*?*/
/*?*/     sal_uInt16 nPos = _GetNamespaceMap().GetIndexByKey( XML_NAMESPACE_DC );
/*?*/
/*?*/     AddAttribute( XML_NAMESPACE_NONE, _GetNamespaceMap().GetAttrNameByIndex( nPos ),
/*?*/                              _GetNamespaceMap().GetNameByIndex ( nPos ) );
/*?*/
/*?*/     nPos = _GetNamespaceMap().GetIndexByKey( XML_NAMESPACE_FRAMEWORK );
/*?*/     AddAttribute( XML_NAMESPACE_NONE, _GetNamespaceMap().GetAttrNameByIndex( nPos ),
/*?*/                              _GetNamespaceMap().GetNameByIndex ( nPos ) );
/*?*/
/*?*/     {
/*?*/         // the following object will write all collected attributes in its dtor
/*?*/         SvXMLElementExport aRoot( *this, XML_NAMESPACE_FRAMEWORK, sXML_version_list, sal_True, sal_True );
/*?*/
/*?*/         sal_uInt32 n=0;
/*?*/         SfxVersionInfo* pInfo = mpVersions->GetObject(n++);
/*?*/         while( pInfo )
/*?*/         {
/*?*/             AddAttribute( XML_NAMESPACE_FRAMEWORK,
/*?*/                           sXML_title,
/*?*/                           OUString( pInfo->aName ) );
/*?*/             AddAttribute( XML_NAMESPACE_FRAMEWORK,
/*?*/                           sXML_comment,
/*?*/                           OUString( pInfo->aComment ) );
/*?*/             AddAttribute( XML_NAMESPACE_FRAMEWORK,
/*?*/                           sXML_creator,
/*?*/                           OUString( pInfo->aCreateStamp.GetName() ) );
/*?*/
/*?*/             DateTime aDT = pInfo->aCreateStamp.GetTime();
/*?*/             ::com::sun::star::util::DateTime aDate( aDT.Get100Sec(),
/*?*/                                                     aDT.GetSec(),
/*?*/                                                     aDT.GetMin(),
/*?*/                                                     aDT.GetHour(),
/*?*/                                                     aDT.GetDay(),
/*?*/                                                     aDT.GetMonth(),
/*?*/                                                     aDT.GetYear() );
/*?*/
/*?*/             OUString aDateStr = SfxXMLMetaExport::GetISODateTimeString( aDate );
/*?*/
/*?*/             AddAttribute( XML_NAMESPACE_DC, sXML_date_time, aDateStr );
/*?*/
/*?*/             pInfo = mpVersions->GetObject(n++);
/*?*/
/*?*/             // the following object will write all collected attributes in its dtor
/*?*/             SvXMLElementExport aEntry( *this, XML_NAMESPACE_FRAMEWORK, sXML_version_entry, sal_True, sal_True );
/*?*/
/*?*/         }
/*?*/     }
/*?*/     GetDocHandler()->endDocument();
/*?*/     return 0;
/*?*/ }

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------

// #110680#
/*?*/ SfxXMLVersListImport_Impl::SfxXMLVersListImport_Impl(
/*?*/   const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xServiceFactory,
/*?*/   SfxVersionTableDtor *pVersions )
/*?*/ : SvXMLImport(xServiceFactory),
/*?*/   mpVersions( pVersions )
/*?*/ {
/*?*/     GetNamespaceMap().AddAtIndex( XML_NAMESPACE_FRAMEWORK_IDX, sXML_np_versions_list,
/*?*/                                   sXML_n_versions_list, XML_NAMESPACE_FRAMEWORK );
/*?*/ }

// ------------------------------------------------------------------------
/*?*/ SfxXMLVersListImport_Impl::~SfxXMLVersListImport_Impl( void ) throw()
/*?*/ {}

// ------------------------------------------------------------------------
/*?*/ SvXMLImportContext *SfxXMLVersListImport_Impl::CreateContext(
/*?*/         sal_uInt16 nPrefix,
/*?*/         const OUString& rLocalName,
/*?*/         const Reference< XAttributeList > & xAttrList )
/*?*/ {
/*?*/     SvXMLImportContext *pContext = 0;
/*?*/
/*?*/     if ( XML_NAMESPACE_FRAMEWORK == nPrefix &&
/*?*/         rLocalName.compareToAscii( sXML_version_list ) == 0 )
/*?*/     {
/*?*/         pContext = new SfxXMLVersListContext_Impl( *this, nPrefix, rLocalName, xAttrList );
/*?*/     }
/*?*/     else
/*?*/     {
/*?*/         pContext = SvXMLImport::CreateContext( nPrefix, rLocalName, xAttrList );
/*?*/     }
/*?*/
/*?*/     return pContext;
/*?*/ }
/*?*/

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------

/*?*/ SfxXMLVersListContext_Impl::SfxXMLVersListContext_Impl( SfxXMLVersListImport_Impl& rImport,
/*?*/                                         sal_uInt16 nPrefix,
/*?*/                                         const OUString& rLocalName,
/*?*/                                         const Reference< XAttributeList > & xAttrList )
/*?*/     : rLocalRef( rImport )
/*?*/     , SvXMLImportContext( rImport, nPrefix, rLocalName )
/*?*/ {
/*?*/ }

// ------------------------------------------------------------------------
/*?*/ SfxXMLVersListContext_Impl::~SfxXMLVersListContext_Impl( void )
/*?*/ {}

// ------------------------------------------------------------------------
/*?*/ SvXMLImportContext *SfxXMLVersListContext_Impl::CreateChildContext( sal_uInt16 nPrefix,
/*?*/                                         const OUString& rLocalName,
/*?*/                                         const Reference< XAttributeList > & xAttrList )
/*?*/ {
/*?*/     SvXMLImportContext *pContext = 0;
/*?*/
/*?*/     if ( nPrefix == XML_NAMESPACE_FRAMEWORK &&
/*?*/          rLocalName.compareToAscii( sXML_version_entry ) == 0)
/*?*/     {
/*?*/         pContext = new SfxXMLVersionContext_Impl( rLocalRef, nPrefix, rLocalName, xAttrList );
/*?*/     }
/*?*/     else
/*?*/     {
/*?*/         pContext = new SvXMLImportContext( rLocalRef, nPrefix, rLocalName );
/*?*/     }
/*?*/
/*?*/     return pContext;
/*?*/ }

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------

/*?*/ SfxXMLVersionContext_Impl::SfxXMLVersionContext_Impl( SfxXMLVersListImport_Impl& rImport,
/*?*/                                         sal_uInt16 nPref,
/*?*/                                         const OUString& rLocalName,
/*?*/                                         const Reference< XAttributeList > & xAttrList )
/*?*/     : rLocalRef( rImport )
/*?*/     , SvXMLImportContext( rImport, nPref, rLocalName )
/*?*/ {
/*?*/     sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
/*?*/
/*?*/     if ( !nAttrCount )
/*?*/         return;
/*?*/
/*?*/     SfxVersionInfo *pInfo = new SfxVersionInfo;
/*?*/
/*?*/     for ( sal_Int16 i=0; i < nAttrCount; i++ )
/*?*/     {
/*?*/         OUString        aLocalName;
/*?*/         const OUString& rAttrName   = xAttrList->getNameByIndex( i );
/*?*/         sal_uInt16      nPrefix     = rImport.GetNamespaceMap().GetKeyByAttrName( rAttrName, &aLocalName );
/*?*/
/*?*/         if ( XML_NAMESPACE_FRAMEWORK == nPrefix )
/*?*/         {
/*?*/             if ( aLocalName.compareToAscii( sXML_title ) == 0 )
/*?*/             {
/*?*/                 const OUString& rAttrValue = xAttrList->getValueByIndex( i );
/*?*/                 pInfo->aName = rAttrValue;
/*?*/             }
/*?*/             else if ( aLocalName.compareToAscii( sXML_comment ) == 0 )
/*?*/             {
/*?*/                 const OUString& rAttrValue = xAttrList->getValueByIndex( i );
/*?*/                 pInfo->aComment = rAttrValue;
/*?*/             }
/*?*/             else if ( aLocalName.compareToAscii( sXML_creator ) == 0 )
/*?*/             {
/*?*/                 const OUString& rAttrValue = xAttrList->getValueByIndex( i );
/*?*/                 pInfo->aCreateStamp.SetName( rAttrValue );
/*?*/             }
/*?*/         }
/*?*/         else if ( ( XML_NAMESPACE_DC == nPrefix ) &&
/*?*/                   ( aLocalName.compareToAscii( sXML_date_time ) == 0 ) )
/*?*/         {
/*?*/             const OUString& rAttrValue = xAttrList->getValueByIndex( i );
/*?*/             DateTime aTime;
/*?*/             if ( ParseISODateTimeString( rAttrValue, aTime ) )
/*?*/                 pInfo->aCreateStamp.SetTime( aTime );
/*?*/         }
/*?*/     }
/*?*/
/*?*/     SfxVersionTableDtor* pVersion = rLocalRef.GetList();
/*?*/     pVersion->Insert( pInfo, LIST_APPEND );
/*?*/ }


// ------------------------------------------------------------------------
/*?*/ SfxXMLVersionContext_Impl::~SfxXMLVersionContext_Impl( void )
/*?*/ {}

// ------------------------------------------------------------------------
// static
/*?*/ sal_Bool SfxXMLVersionContext_Impl::ParseISODateTimeString(
/*?*/                                 const ::rtl::OUString& rString,
/*?*/                                 DateTime& rDateTime )
/*?*/ {
/*?*/     sal_Bool bSuccess = sal_True;
/*?*/
/*?*/     OUString aDateStr, aTimeStr;
/*?*/     sal_Int32 nPos = rString.indexOf( (sal_Unicode) 'T' );
/*?*/     if ( nPos >= 0 )
/*?*/     {
/*?*/         aDateStr = rString.copy( 0, nPos );
/*?*/         aTimeStr = rString.copy( nPos + 1 );
/*?*/     }
/*?*/     else
/*?*/         aDateStr = rString;         // no separator: only date part
/*?*/
/*?*/     sal_Int32 nYear  = 0;
/*?*/     sal_Int32 nMonth = 1;
/*?*/     sal_Int32 nDay   = 1;
/*?*/     sal_Int32 nHour  = 0;
/*?*/     sal_Int32 nMin   = 0;
/*?*/     sal_Int32 nSec   = 0;
/*?*/
/*?*/     const sal_Unicode* pStr = aDateStr.getStr();
/*?*/     sal_Int32 nDateTokens = 1;
/*?*/     while ( *pStr )
/*?*/     {
/*?*/         if ( *pStr == '-' )
/*?*/             nDateTokens++;
/*?*/         pStr++;
/*?*/     }
/*?*/     if ( nDateTokens > 3 || aDateStr.getLength() == 0 )
/*?*/         bSuccess = sal_False;
/*?*/     else
/*?*/     {
/*?*/         sal_Int32 n = 0;
/*?*/         nYear = aDateStr.getToken( 0, '-', n ).toInt32();
/*?*/         if ( nYear > 9999 )
/*?*/             bSuccess = sal_False;
/*?*/         else if ( nDateTokens >= 2 )
/*?*/         {
/*?*/             nMonth = aDateStr.getToken( 0, '-', n ).toInt32();
/*?*/             if ( nMonth > 12 )
/*?*/                 bSuccess = sal_False;
/*?*/             else if ( nDateTokens >= 3 )
/*?*/             {
/*?*/                 nDay = aDateStr.getToken( 0, '-', n ).toInt32();
/*?*/                 if ( nDay > 31 )
/*?*/                     bSuccess = sal_False;
/*?*/             }
/*?*/         }
/*?*/     }
/*?*/
/*?*/     if ( bSuccess && aTimeStr.getLength() > 0 )         // time is optional
/*?*/     {
/*?*/         pStr = aTimeStr.getStr();
/*?*/         sal_Int32 nTimeTokens = 1;
/*?*/         while ( *pStr )
/*?*/         {
/*?*/             if ( *pStr == ':' )
/*?*/                 nTimeTokens++;
/*?*/             pStr++;
/*?*/         }
/*?*/         if ( nTimeTokens > 3 )
/*?*/             bSuccess = sal_False;
/*?*/         else
/*?*/         {
/*?*/             sal_Int32 n = 0;
/*?*/             nHour = aTimeStr.getToken( 0, ':', n ).toInt32();
/*?*/             if ( nHour > 23 )
/*?*/                 bSuccess = sal_False;
/*?*/             else if ( nTimeTokens >= 2 )
/*?*/             {
/*?*/                 nMin = aTimeStr.getToken( 0, ':', n ).toInt32();
/*?*/                 if ( nMin > 59 )
/*?*/                     bSuccess = sal_False;
/*?*/                 else if ( nTimeTokens >= 3 )
/*?*/                 {
/*?*/                     nSec = aTimeStr.getToken( 0, ':', n ).toInt32();
/*?*/                     if ( nSec > 59 )
/*?*/                         bSuccess = sal_False;
/*?*/                 }
/*?*/             }
/*?*/         }
/*?*/     }
/*?*/
/*?*/     if ( bSuccess )
/*?*/         rDateTime = DateTime( Date( (USHORT)nDay, (USHORT)nMonth, (USHORT)nYear ),
/*?*/                               Time( nHour, nMin, nSec ) );
/*?*/
/*?*/     return bSuccess;
/*?*/ }


// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
/*?*/ void SfxXMLVersList_Impl::WriteInfo( SvStorageRef xRoot, const SfxVersionTableDtor *pList )
/*?*/ {
/*?*/     // no storage, no version list!
/*?*/     if ( xRoot.Is() )
/*?*/     {
/*?*/         // get the services needed for writing the xml data
/*?*/         Reference< lang::XMultiServiceFactory > xServiceFactory =
/*?*/                 ::legacy_binfilters::getLegacyProcessServiceFactory();
/*?*/         DBG_ASSERT( xServiceFactory.is(), "XMLReader::Read: got no service manager" );
/*?*/
/*?*/         Reference< XInterface > xWriter (xServiceFactory->createInstance(
/*?*/                 OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.xml.sax.Writer"))));
/*?*/         DBG_ASSERT( xWriter.is(), "com.sun.star.xml.sax.Writer service missing" );
/*?*/
/*?*/         // check wether there's already a sub storage with the version info
/*?*/         // and delete it
/*?*/         OUString sVerName( RTL_CONSTASCII_USTRINGPARAM( XMLN_VERSIONSLIST ) );
/*?*/
/*?*/         // is this really needed, we set the size to zero before doing
/*?*/         // anything with this stream?
/*      if ( xRoot->IsContained( sVerName ) )
        {
            xRoot->Remove( sVerName );
            xRoot->Commit();
        }
*/
        // open (create) the sub storage with the version info
/*?*/         SvStorageStreamRef xVerStream = xRoot->OpenStream( sVerName, STREAM_WRITE | STREAM_TRUNC );
/*?*/
/*?*/         // SetSize should not be neccessary because OpenStream( WRITE|TRUNC ) should already
/*?*/         // have set the size to zero
/*?*/ //      xVerStream->SetSize ( 0L );
/*?*/         xVerStream->SetBufferSize( 16*1024 );
/*?*/
/*?*/         Reference< io::XOutputStream > xOut = new ::utl::OOutputStreamWrapper( *xVerStream );
/*?*/         Reference< io::XActiveDataSource > xSrc( xWriter, uno::UNO_QUERY );
/*?*/         xSrc->setOutputStream(xOut);
/*?*/
/*?*/         Reference< XDocumentHandler > xHandler( xWriter, uno::UNO_QUERY );
/*?*/
/*?*/       // #110680#
/*?*/         // SfxXMLVersListExport_Impl aExp( pList, sVerName, xHandler );
/*?*/         SfxXMLVersListExport_Impl aExp( xServiceFactory, pList, sVerName, xHandler );
/*?*/
/*?*/         aExp.exportDoc( ::binfilter::xmloff::token::XML_VERSION );
/*?*/
/*?*/         xVerStream->Commit();
/*?*/         xVerStream.Clear();
/*?*/ //      xRoot->Commit();
/*?*/     }
/*?*/ }

// ------------------------------------------------------------------------
/*N*/ sal_Bool SfxXMLVersList_Impl::ReadInfo( SvStorageRef xRoot, SfxVersionTableDtor *pList )
/*N*/ {
/*N*/     sal_Bool bRet = sal_False;
/*N*/
/*N*/     const OUString sDocName( RTL_CONSTASCII_USTRINGPARAM( XMLN_VERSIONSLIST ) );
/*N*/
/*N*/     if ( xRoot->IsContained ( sDocName ) )
/*N*/     {
/*?*/         Reference< lang::XMultiServiceFactory > xServiceFactory =
/*?*/                 ::legacy_binfilters::getLegacyProcessServiceFactory();
/*?*/         DBG_ASSERT( xServiceFactory.is(), "XMLReader::Read: got no service manager" );
/*?*/
/*?*/         InputSource aParserInput;
/*?*/         aParserInput.sSystemId = xRoot->GetName();
/*?*/
/*?*/         SvStorageStreamRef xDocStream = xRoot->OpenStream( sDocName, STREAM_READ | STREAM_SHARE_DENYWRITE | STREAM_NOCREATE );
/*?*/         xDocStream->Seek( 0L );
/*?*/         xDocStream->SetBufferSize( 16*1024 );
/*?*/         aParserInput.aInputStream = new ::utl::OInputStreamWrapper( *xDocStream );
/*?*/
/*?*/         // get parser
/*?*/         Reference< XInterface > xXMLParser = xServiceFactory->createInstance(
/*?*/             OUString::createFromAscii("com.sun.star.xml.sax.Parser") );
/*?*/         DBG_ASSERT( xXMLParser.is(),
/*?*/             "XMLReader::Read: com.sun.star.xml.sax.Parser service missing" );
/*?*/
/*?*/         // get filter
/*?*/       // #110680#
/*?*/         // Reference< XDocumentHandler > xFilter = new SfxXMLVersListImport_Impl( pList );
/*?*/         Reference< XDocumentHandler > xFilter = new SfxXMLVersListImport_Impl( xServiceFactory, pList );
/*?*/
/*?*/         // connect parser and filter
/*?*/         Reference< XParser > xParser( xXMLParser, UNO_QUERY );
/*?*/         xParser->setDocumentHandler( xFilter );
/*?*/
/*?*/         // parse
/*?*/         try
/*?*/         {
/*?*/             xParser->parseStream( aParserInput );
/*?*/             bRet = sal_True;
/*?*/         }
/*?*/         catch( SAXParseException&  ) {}
/*?*/         catch( SAXException&  )      {}
/*?*/         catch( io::IOException& )    {}
/*?*/     }
/*N*/
/*N*/     return bRet;
/*N*/ }

}
