/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_xmlxtexp.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 17:38:06 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif

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
