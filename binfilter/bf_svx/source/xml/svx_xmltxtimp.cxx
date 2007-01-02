/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_xmltxtimp.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 17:37:55 $
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


#ifndef _COM_SUN_STAR_XML_SAX_XPARSER_HPP_
#include <com/sun/star/xml/sax/XParser.hpp>
#endif


#ifndef _UTL_STREAM_WRAPPER_HXX_
#include <unotools/streamwrap.hxx>
#endif





#ifndef _XMLOFF_XMLIMP_HXX
#include <bf_xmloff/xmlimp.hxx>
#endif

#ifndef _XMLOFF_XMLNMSPE_HXX
#include <bf_xmloff/xmlnmspe.hxx>
#endif
#ifndef _XMLOFF_XMLSTYLE_HXX
#include <bf_xmloff/xmlstyle.hxx>
#endif

#ifndef _SVX_EDITSOURCE_HXX
#include "editsource.hxx"
#endif

#ifndef _SVX_UNOTEXT_HXX
#include "unotext.hxx"
#endif
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {
using namespace ::com::sun::star;
using namespace ::com::sun::star::document;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::xml::sax;
using namespace ::com::sun::star::text;
using namespace ::rtl;
using namespace cppu;
using namespace xmloff::token;


///////////////////////////////////////////////////////////////////////

/*N*/ class SvxXMLTextImportContext : public SvXMLImportContext
/*N*/ {
/*N*/ public:
/*N*/   SvxXMLTextImportContext( SvXMLImport& rImport, USHORT nPrfx, const OUString& rLName, const Reference< XAttributeList >& xAttrList, const Reference< XText >& xText );
/*N*/   virtual ~SvxXMLTextImportContext();
/*N*/
/*N*/   virtual SvXMLImportContext *CreateChildContext( USHORT nPrefix, const OUString& rLocalName, const Reference< XAttributeList >& xAttrList );
/*N*/
/*N*/ //    SvxXMLXTableImport& getImport() const { return *(SvxXMLXTableImport*)&GetImport(); }
/*N*/
/*N*/ private:
/*N*/   const Reference< XText > mxText;
/*N*/ };
/*N*/
/*N*/ ///////////////////////////////////////////////////////////////////////
/*N*/
/*N*/ SvxXMLTextImportContext::SvxXMLTextImportContext( SvXMLImport& rImport, USHORT nPrfx, const OUString& rLName, const Reference< XAttributeList >& xAttrList, const Reference< XText >& xText )
/*N*/ : SvXMLImportContext( rImport, nPrfx, rLName ), mxText( xText )
/*N*/ {
/*N*/ }
/*N*/
/*N*/ SvxXMLTextImportContext::~SvxXMLTextImportContext()
/*N*/ {
/*N*/ }
/*N*/
/*N*/ SvXMLImportContext *SvxXMLTextImportContext::CreateChildContext( USHORT nPrefix, const OUString& rLocalName, const Reference< XAttributeList >& xAttrList )
/*N*/ {
/*N*/   SvXMLImportContext* pContext = NULL;
/*N*/   if(XML_NAMESPACE_OFFICE == nPrefix && IsXMLToken( rLocalName, XML_BODY ) )
/*N*/   {
/*N*/       pContext = new SvxXMLTextImportContext( GetImport(), nPrefix, rLocalName, xAttrList, mxText );
/*N*/   }
/*N*/   else if( XML_NAMESPACE_OFFICE == nPrefix && IsXMLToken( rLocalName, XML_AUTOMATIC_STYLES ) )
/*N*/   {
/*N*/       pContext = new SvXMLStylesContext( GetImport(), nPrefix, rLocalName, xAttrList );
/*N*/       GetImport().GetTextImport()->SetAutoStyles( (SvXMLStylesContext*)pContext );
/*N*/
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       pContext = GetImport().GetTextImport()->CreateTextChildContext( GetImport(), nPrefix, rLocalName, xAttrList );
/*N*/   }
/*N*/
/*N*/   if( NULL == pContext )
/*N*/       pContext = new SvXMLImportContext( GetImport(), nPrefix, rLocalName );
/*N*/
/*N*/   return pContext;
/*N*/ }
/*N*/
/*N*/ ///////////////////////////////////////////////////////////////////////
/*N*/
/*N*/ class SvxXMLXTextImportComponent : public SvXMLImport
/*N*/ {
/*N*/ public:
/*N*/   // #110680#
/*N*/   SvxXMLXTextImportComponent(
/*N*/       const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xServiceFactory,
/*N*/       const Reference< XText > & xText );
/*N*/   virtual ~SvxXMLXTextImportComponent() throw ();
/*N*/
/*N*/   static sal_Bool load( const ::rtl::OUString& rUrl, const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer >& xTable ) throw();
/*N*/ protected:
/*N*/   virtual SvXMLImportContext *CreateChildContext( USHORT nPrefix, const OUString& rLocalName, const Reference< XAttributeList >& xAttrList );
/*N*/
/*N*/ private:
/*N*/   const Reference< XText > mxText;
/*N*/ };
/*N*/
/*N*/ // --------------------------------------------------------------------
/*N*/
/*N*/ // #110680#
/*N*/ SvxXMLXTextImportComponent::SvxXMLXTextImportComponent(
/*N*/   const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xServiceFactory,
/*N*/   const Reference< XText > & xText )
/*N*/ : SvXMLImport(xServiceFactory),
/*N*/   mxText( xText )
/*N*/ {
/*N*/   GetTextImport()->SetCursor( mxText->createTextCursor() );
/*N*/ }
/*N*/
/*N*/ SvxXMLXTextImportComponent::~SvxXMLXTextImportComponent() throw ()
/*N*/ {
/*N*/ }
/*N*/
/*N*/ SvXMLImportContext *SvxXMLXTextImportComponent::CreateChildContext( USHORT nPrefix, const OUString& rLocalName, const Reference< XAttributeList >& xAttrList )
/*N*/ {
/*N*/   SvXMLImportContext* pContext;
/*N*/   if(XML_NAMESPACE_OFFICE == nPrefix && ( IsXMLToken( rLocalName, XML_DOCUMENT ) || IsXMLToken( rLocalName, XML_DOCUMENT_CONTENT ) ) )
/*N*/   {
/*N*/        pContext = new SvxXMLTextImportContext(*this, nPrefix, rLocalName, xAttrList, mxText );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       pContext = SvXMLImport::CreateContext(nPrefix, rLocalName, xAttrList);
/*N*/   }
/*N*/   return pContext;
/*N*/ }

}
