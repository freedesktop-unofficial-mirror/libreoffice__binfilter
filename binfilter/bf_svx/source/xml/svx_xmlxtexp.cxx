/*************************************************************************
 *
 *  $RCSfile: svx_xmlxtexp.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 16:50:12 $
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

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif

// auto strip #ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
// auto strip #include <com/sun/star/container/XNameContainer.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_XML_SAX_XDOCUMENTHANDLER_HPP_
// auto strip #include <com/sun/star/xml/sax/XDocumentHandler.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
// auto strip #include <com/sun/star/uno/Sequence.hxx>
// auto strip #endif
#ifndef _COM_SUN_STAR_DRAWING_POLYPOLYGONBEZIERCOORDS_HPP_
#include <com/sun/star/drawing/PolyPolygonBezierCoords.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_LINEDASH_HPP_
#include <com/sun/star/drawing/LineDash.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_GRADIENT_HPP_
#include <com/sun/star/awt/Gradient.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_HATCH_HPP_
#include <com/sun/star/drawing/Hatch.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XACTIVEDATASOURCE_HPP_
#include <com/sun/star/io/XActiveDataSource.hpp>
#endif

#ifndef _SFXDOCFILE_HXX
#include <bf_sfx2/docfile.hxx>
#endif
// auto strip #ifndef _SVSTOR_HXX
// auto strip #include <so3/svstor.hxx>
// auto strip #endif

// auto strip #ifndef _RTL_USTRBUF_HXX_
// auto strip #include <rtl/ustrbuf.hxx>
// auto strip #endif

#ifndef _XMLOFF_XMLUCONV_HXX
#include <bf_xmloff/xmluconv.hxx>
#endif

#ifndef _XMLOFF_XMLNMSPE_HXX
#include "bf_xmloff/xmlnmspe.hxx"
#endif

#ifndef _XMLOFF_NMSPMAP_HXX
#include "bf_xmloff/nmspmap.hxx"
#endif

#ifndef _XMLOFF_XMLKYWD_HXX
#include "bf_xmloff/xmlkywd.hxx"
#endif

// auto strip #ifndef _XMLOFF_XMLMETAE_HXX
// auto strip #include "bf_xmloff/xmlmetae.hxx"
// auto strip #endif

#ifndef _XMLOFF_DASHSTYLE_HXX
#include "bf_xmloff/DashStyle.hxx"
#endif

#ifndef _XMLOFF_GRADIENTSTYLE_HXX
#include "bf_xmloff/GradientStyle.hxx"
#endif

#ifndef _XMLOFF_HATCHSTYLE_HXX
#include "bf_xmloff/HatchStyle.hxx"
#endif

#ifndef _XMLOFF_IMAGESTYLE_HXX
#include "bf_xmloff/ImageStyle.hxx"
#endif

#ifndef _XMLOFF_MARKERSTYLE_HXX
#include "bf_xmloff/MarkerStyle.hxx"
#endif

#ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
#include <com/sun/star/container/XNameContainer.hpp>
#endif

// auto strip #ifndef _COMPHELPER_PROCESSFACTORY_HXX_
// auto strip #include <comphelper/processfactory.hxx>
// auto strip #endif

#ifndef _UTL_STREAM_WRAPPER_HXX_
#include <unotools/streamwrap.hxx>
#endif

#ifndef _XMLGRHLP_HXX
#include "xmlgrhlp.hxx"
#endif

#include "xmlxtexp.hxx"
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {
using namespace ::com::sun::star;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::document;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::awt;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::xml::sax;
using namespace ::rtl;
using namespace cppu;

/*N*/ class SvxXMLTableEntryExporter
/*N*/ {
/*N*/ public:
/*N*/   SvxXMLTableEntryExporter( SvXMLExport& rExport ) : mrExport( rExport ) {}
/*N*/   virtual ~SvxXMLTableEntryExporter();
/*N*/
/*N*/   virtual void exportEntry( const OUString& rStrName, const Any& rValue ) = 0;
/*N*/
/*N*/ protected:
/*N*/   SvXMLExport& mrExport;
/*N*/ };
/*N*/
/*N*/ class SvxXMLColorEntryExporter : public SvxXMLTableEntryExporter
/*N*/ {
/*N*/ public:
/*N*/   SvxXMLColorEntryExporter( SvXMLExport& rExport );
/*N*/   virtual ~SvxXMLColorEntryExporter();
/*N*/
/*N*/   virtual void exportEntry( const OUString& rStrName, const Any& rValue );
/*N*/ };
/*N*/
/*N*/ class SvxXMLLineEndEntryExporter : public SvxXMLTableEntryExporter
/*N*/ {
/*N*/ public:
/*N*/   SvxXMLLineEndEntryExporter( SvXMLExport& rExport );
/*N*/   SvxXMLLineEndEntryExporter();
/*N*/   virtual ~SvxXMLLineEndEntryExporter();
/*N*/
/*N*/   virtual void exportEntry( const OUString& rStrName, const Any& rValue );
/*N*/ private:
/*N*/   XMLMarkerStyleExport maMarkerStyle;
/*N*/ };
/*N*/
/*N*/ class SvxXMLDashEntryExporter : public SvxXMLTableEntryExporter
/*N*/ {
/*N*/ public:
/*N*/   SvxXMLDashEntryExporter( SvXMLExport& rExport );
/*N*/   virtual ~SvxXMLDashEntryExporter();
/*N*/
/*N*/   virtual void exportEntry( const OUString& rStrName, const Any& rValue );
/*N*/
/*N*/ private:
/*N*/   XMLDashStyleExport maDashStyle;
/*N*/ };
/*N*/
/*N*/ class SvxXMLHatchEntryExporter : public SvxXMLTableEntryExporter
/*N*/ {
/*N*/ public:
/*N*/   SvxXMLHatchEntryExporter( SvXMLExport& rExport );
/*N*/   virtual ~SvxXMLHatchEntryExporter();
/*N*/
/*N*/   virtual void exportEntry( const OUString& rStrName, const Any& rValue );
/*N*/ private:
/*N*/   XMLHatchStyleExport maHatchStyle;
/*N*/ };
/*N*/
/*N*/ class SvxXMLGradientEntryExporter : public SvxXMLTableEntryExporter
/*N*/ {
/*N*/ public:
/*N*/   SvxXMLGradientEntryExporter( SvXMLExport& rExport );
/*N*/   virtual ~SvxXMLGradientEntryExporter();
/*N*/
/*N*/   virtual void exportEntry( const OUString& rStrName, const Any& rValue );
/*N*/ private:
/*N*/   XMLGradientStyleExport maGradientStyle;
/*N*/ };
/*N*/
/*N*/ class SvxXMLBitmapEntryExporter : public SvxXMLTableEntryExporter
/*N*/ {
/*N*/ public:
/*N*/   SvxXMLBitmapEntryExporter( SvXMLExport& rExport );
/*N*/   virtual ~SvxXMLBitmapEntryExporter();
/*N*/
/*N*/   virtual void exportEntry( const OUString& rStrName, const Any& rValue );
/*N*/
/*N*/ private:
/*N*/   XMLImageStyle maImageStyle;
/*N*/ };
/*N*/
/*N*/ ///////////////////////////////////////////////////////////////////////
/*N*/
/*N*/ // #110680#
/*N*/ SvxXMLXTableExportComponent::SvxXMLXTableExportComponent(
/*N*/   const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xServiceFactory,
/*N*/   const OUString& rFileName,
/*N*/   const uno::Reference<xml::sax::XDocumentHandler> & rHandler,
/*N*/   const uno::Reference<container::XNameContainer >& xTable,
/*N*/   uno::Reference<document::XGraphicObjectResolver >& xGrfResolver )
/*N*/ : SvXMLExport( xServiceFactory, rFileName, rHandler, NULL, MAP_100TH_MM),
/*N*/   mxTable( xTable )
/*N*/ {
/*N*/   SetGraphicResolver( xGrfResolver );
/*N*/   setExportFlags( 0 );
/*N*/ }
/*N*/
/*N*/ SvxXMLXTableExportComponent::~SvxXMLXTableExportComponent()
/*N*/ {
/*N*/ }
/*N*/
/*N*/ sal_Bool SvxXMLXTableExportComponent::save( const OUString& rURL, const uno::Reference<container::XNameContainer >& xTable ) throw()
/*N*/ {
/*N*/   SvStorageRef aStorage;
/*N*/   SfxMedium* pMedium = NULL;
/*N*/   sal_Bool bRet = sal_False;
/*N*/
/*N*/   Reference< XGraphicObjectResolver > xGrfResolver;
/*N*/   SvXMLGraphicHelper* pGraphicHelper = 0;
/*N*/
/*N*/   try
/*N*/   {
/*N*/       do
/*N*/       {
/*N*/           SvStorage* pStorage = NULL;
/*N*/           uno::Reference<io::XOutputStream> xOut;
/*N*/
/*N*/           SvStorageStreamRef xStream;
/*N*/
/*N*/           sal_Bool bNeedStorage = xTable->getElementType() == ::getCppuType((const OUString*)0);
/*N*/
/*N*/           uno::Reference< lang::XMultiServiceFactory> xServiceFactory( ::legacy_binfilters::getLegacyProcessServiceFactory() );
/*N*/
/*N*/           if( !xServiceFactory.is() )
/*N*/           {
/*N*/               DBG_ERROR( "got no service manager" );
/*N*/               return FALSE;
/*N*/           }
/*N*/
/*N*/           uno::Reference< uno::XInterface > xWriter( xServiceFactory->createInstance( OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.xml.sax.Writer" ) ) ) );
/*N*/
/*N*/           if( !xWriter.is() )
/*N*/           {
/*N*/               DBG_ERROR( "com.sun.star.xml.sax.Writer service missing" );
/*N*/               return FALSE;
/*N*/           }
/*N*/
/*N*/           uno::Reference<xml::sax::XDocumentHandler>  xHandler( xWriter, uno::UNO_QUERY );
/*N*/
/*N*/           if( bNeedStorage )
/*N*/           {
/*N*/               pStorage = new SvStorage( sal_True, rURL, STREAM_WRITE | STREAM_TRUNC, 0 );
/*N*/               aStorage = pStorage;
/*N*/
/*N*/               if( NULL == pStorage )
/*N*/               {
/*N*/                   DBG_ERROR( "no storage!" );
/*N*/                   break;
/*N*/               }
/*N*/
/*N*/               OUString sMetaName( RTL_CONSTASCII_USTRINGPARAM( "Content.xml" ) );
/*N*/               xStream = pStorage->OpenStream( sMetaName, STREAM_WRITE | STREAM_SHARE_DENYWRITE );
/*N*/               xStream->SetBufferSize( 16*1024 );
/*N*/
/*N*/               pGraphicHelper = SvXMLGraphicHelper::Create( *pStorage, GRAPHICHELPER_MODE_WRITE );
/*N*/               xGrfResolver = pGraphicHelper;
/*N*/               xOut = new ::utl::OOutputStreamWrapper( *xStream );
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               pMedium = new SfxMedium( rURL, STREAM_WRITE | STREAM_TRUNC, TRUE );
/*N*/               pMedium->IsRemote();
/*N*/
/*N*/               SvStream* pStream = pMedium->GetOutStream();
/*N*/               if( NULL == pStream )
/*N*/               {
/*N*/                   DBG_ERROR( "no output stream!" );
/*N*/                   break;
/*N*/               }
/*N*/               xOut = new ::utl::OOutputStreamWrapper( *pStream );
/*N*/           }
/*N*/
/*N*/
/*N*/           uno::Reference<io::XActiveDataSource> xMetaSrc( xWriter, uno::UNO_QUERY );
/*N*/           xMetaSrc->setOutputStream( xOut );
/*N*/
/*N*/           const OUString aName;
/*N*/           // #110680#
/*N*/           // SvxXMLXTableExportComponent aExporter( aName, xHandler, xTable, xGrfResolver );
/*N*/           SvxXMLXTableExportComponent aExporter( xServiceFactory, aName, xHandler, xTable, xGrfResolver );
/*N*/           bRet = aExporter.exportTable();
/*N*/
/*N*/       }
/*N*/       while( 0 );
/*N*/
/*N*/       if( pGraphicHelper )
/*N*/           SvXMLGraphicHelper::Destroy( pGraphicHelper );
/*N*/   }
/*N*/   catch( uno::Exception& e )
/*N*/   {
/*N*/       bRet = sal_False;
/*N*/   }
/*N*/
/*N*/   if( pMedium )
/*N*/   {
/*N*/       pMedium->Commit();
/*N*/       delete pMedium;
/*N*/   }
/*N*/
/*N*/   return bRet;
/*N*/ }
/*N*/
/*N*/ sal_Bool SvxXMLXTableExportComponent::exportTable() throw()
/*N*/ {
/*N*/   sal_Bool bRet = sal_False;
/*N*/
/*N*/   try
/*N*/   {
/*N*/       GetDocHandler()->startDocument();
/*N*/
/*N*/       // export namespaces
/*N*/       sal_uInt16 nPos = GetNamespaceMap().GetFirstKey();
/*N*/       while( USHRT_MAX != nPos )
/*N*/       {
/*N*/           GetAttrList().AddAttribute( GetNamespaceMap().GetAttrNameByKey( nPos ), GetNamespaceMap().GetNameByKey( nPos ) );
/*N*/           nPos = GetNamespaceMap().GetNextKey( nPos );
/*N*/       }
/*N*/
/*N*/       do
/*N*/       {
/*N*/           const OUString sWS( RTL_CONSTASCII_USTRINGPARAM( sXML_WS ) );
/*N*/
/*N*/           if( !mxTable.is() )
/*N*/               break;
/*N*/
/*N*/           char* pEleName;
/*N*/           Type aExportType = mxTable->getElementType();
/*N*/           SvxXMLTableEntryExporter* pExporter = NULL;
/*N*/
/*N*/           if( aExportType == ::getCppuType((const sal_Int32*)0) )
/*N*/           {
/*N*/               pExporter = new SvxXMLColorEntryExporter(*this);
/*N*/               pEleName = "color-table";
/*N*/           }
/*N*/           else if( aExportType == ::getCppuType((const drawing::PolyPolygonBezierCoords*)0) )
/*N*/           {
/*N*/               pExporter = new SvxXMLLineEndEntryExporter(*this);
/*N*/               pEleName = "marker-table";
/*N*/           }
/*N*/           else if( aExportType == ::getCppuType((const drawing::LineDash*)0) )
/*N*/           {
/*N*/               pExporter = new SvxXMLDashEntryExporter(*this);
/*N*/               pEleName = "dash-table";
/*N*/           }
/*N*/           else if( aExportType == ::getCppuType((const drawing::Hatch*)0) )
/*N*/           {
/*N*/               pExporter = new SvxXMLHatchEntryExporter(*this);
/*N*/               pEleName = "hatch-table";
/*N*/           }
/*N*/           else if( aExportType == ::getCppuType((const awt::Gradient*)0))
/*N*/           {
/*N*/               pExporter = new SvxXMLGradientEntryExporter(*this);
/*N*/               pEleName = "gradient-table";
/*N*/           }
/*N*/           else if( aExportType == ::getCppuType((const OUString*)0))
/*N*/           {
/*N*/               pExporter = new SvxXMLBitmapEntryExporter(*this);
/*N*/               pEleName = "bitmap-table";
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               DBG_ERROR( "unknown type for export");
/*N*/               break;
/*N*/           }
/*N*/
/*N*/           SvXMLElementExport aElem( *this, XML_NAMESPACE_OFFICE, pEleName, sal_True, sal_True );
/*N*/
/*N*/           Sequence< OUString > aNames = mxTable->getElementNames();
/*N*/           const sal_Int32 nCount = aNames.getLength();
/*N*/           const OUString* pNames = aNames.getConstArray();
/*N*/           Any aAny;
/*N*/
/*N*/           sal_Int32 nIndex;
/*N*/           for( nIndex = 0; nIndex < nCount; nIndex++, pNames++ )
/*N*/           {
/*N*/               aAny = mxTable->getByName( *pNames );
/*N*/               pExporter->exportEntry( *pNames, aAny );
/*N*/           }
/*N*/
/*N*/           bRet = sal_True;
/*N*/       }
/*N*/       while(0);
/*N*/
/*N*/       GetDocHandler()->endDocument();
/*N*/   }
/*N*/   catch( Exception e )
/*N*/   {
/*N*/       bRet = sal_False;
/*N*/   }
/*N*/
/*N*/   return bRet;
/*N*/ }
/*N*/
/*N*/ // methods without content:
/*N*/ void SvxXMLXTableExportComponent::_ExportAutoStyles() {}
/*N*/ void SvxXMLXTableExportComponent::_ExportMasterStyles() {}
/*N*/ void SvxXMLXTableExportComponent::_ExportContent() {}
/*N*/
/*N*/ ///////////////////////////////////////////////////////////////////////
/*N*/
/*N*/ SvxXMLTableEntryExporter::~SvxXMLTableEntryExporter()
/*N*/ {
/*N*/ }
/*N*/
/*N*/ ///////////////////////////////////////////////////////////////////////
/*N*/
/*N*/ SvxXMLColorEntryExporter::SvxXMLColorEntryExporter( SvXMLExport& rExport )
/*N*/ : SvxXMLTableEntryExporter( rExport )
/*N*/ {
/*N*/ }
/*N*/
/*N*/ SvxXMLColorEntryExporter::~SvxXMLColorEntryExporter()
/*N*/ {
/*N*/ }
/*N*/
/*N*/ void SvxXMLColorEntryExporter::exportEntry( const OUString& rStrName, const Any& rValue )
/*N*/ {
/*N*/   mrExport.AddAttribute( XML_NAMESPACE_DRAW, sXML_name, rStrName );
/*N*/
/*N*/   sal_Int32 nColor;
/*N*/   rValue >>= nColor;
/*N*/
/*N*/   OUStringBuffer aOut;
/*N*/   mrExport.GetMM100UnitConverter().convertColor( aOut, nColor );
/*N*/   mrExport.AddAttribute( XML_NAMESPACE_DRAW, sXML_color, aOut.makeStringAndClear() );
/*N*/
/*N*/   SvXMLElementExport aElem( mrExport, XML_NAMESPACE_DRAW, sXML_color, sal_True, sal_True );
/*N*/ }
/*N*/
/*N*/ ///////////////////////////////////////////////////////////////////////
/*N*/
/*N*/ SvxXMLLineEndEntryExporter::SvxXMLLineEndEntryExporter( SvXMLExport& rExport )
/*N*/ : SvxXMLTableEntryExporter( rExport ), maMarkerStyle( rExport )
/*N*/ {
/*N*/ }
/*N*/
/*N*/ SvxXMLLineEndEntryExporter::~SvxXMLLineEndEntryExporter()
/*N*/ {
/*N*/ }
/*N*/
/*N*/ void SvxXMLLineEndEntryExporter::exportEntry( const OUString& rStrName, const Any& rValue )
/*N*/ {
/*N*/   maMarkerStyle.exportXML( rStrName, rValue );
/*N*/ }
/*N*/
/*N*/ ///////////////////////////////////////////////////////////////////////
/*N*/
/*N*/ SvxXMLDashEntryExporter::SvxXMLDashEntryExporter( SvXMLExport& rExport )
/*N*/ : SvxXMLTableEntryExporter( rExport ), maDashStyle( rExport )
/*N*/ {
/*N*/ }
/*N*/
/*N*/ SvxXMLDashEntryExporter::~SvxXMLDashEntryExporter()
/*N*/ {
/*N*/ }
/*N*/
/*N*/ void SvxXMLDashEntryExporter::exportEntry( const OUString& rStrName, const Any& rValue )
/*N*/ {
/*N*/   maDashStyle.exportXML( rStrName, rValue );
/*N*/ }
/*N*/
/*N*/ ///////////////////////////////////////////////////////////////////////
/*N*/
/*N*/ SvxXMLHatchEntryExporter::SvxXMLHatchEntryExporter( SvXMLExport& rExport )
/*N*/ : SvxXMLTableEntryExporter( rExport ), maHatchStyle( rExport )
/*N*/ {
/*N*/ }
/*N*/
/*N*/ SvxXMLHatchEntryExporter::~SvxXMLHatchEntryExporter()
/*N*/ {
/*N*/ }
/*N*/
/*N*/ void SvxXMLHatchEntryExporter::exportEntry( const OUString& rStrName, const Any& rValue )
/*N*/ {
/*N*/   maHatchStyle.exportXML( rStrName, rValue );
/*N*/ }
/*N*/
/*N*/ ///////////////////////////////////////////////////////////////////////
/*N*/
/*N*/ SvxXMLGradientEntryExporter::SvxXMLGradientEntryExporter( SvXMLExport& rExport )
/*N*/ : SvxXMLTableEntryExporter( rExport ), maGradientStyle( rExport )
/*N*/ {
/*N*/ }
/*N*/
/*N*/ SvxXMLGradientEntryExporter::~SvxXMLGradientEntryExporter()
/*N*/ {
/*N*/ }
/*N*/
/*N*/ void SvxXMLGradientEntryExporter::exportEntry( const OUString& rStrName, const Any& rValue )
/*N*/ {
/*N*/   maGradientStyle.exportXML( rStrName, rValue );
/*N*/ }
/*N*/
/*N*/ ///////////////////////////////////////////////////////////////////////
/*N*/
/*N*/ SvxXMLBitmapEntryExporter::SvxXMLBitmapEntryExporter( SvXMLExport& rExport )
/*N*/ : SvxXMLTableEntryExporter( rExport )
/*N*/ {
/*N*/ }
/*N*/
/*N*/ SvxXMLBitmapEntryExporter::~SvxXMLBitmapEntryExporter()
/*N*/ {
/*N*/ }
/*N*/
/*N*/ void SvxXMLBitmapEntryExporter::exportEntry( const OUString& rStrName, const Any& rValue )
/*N*/ {
/*N*/   maImageStyle.exportXML( rStrName, rValue, mrExport );
/*N*/ }
}
