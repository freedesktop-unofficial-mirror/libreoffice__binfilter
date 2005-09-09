/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_XMLGraphicsDefaultStyle.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 07:54:44 $
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

// auto strip #ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
// auto strip #include <com/sun/star/lang/XMultiServiceFactory.hpp>
// auto strip #endif

// auto strip #ifndef _TOOLS_DEBUG_HXX
// auto strip #include <tools/debug.hxx>
// auto strip #endif

#ifndef _XMLOFF_XMLIMP_HXX
#include "xmlimp.hxx"
#endif

// auto strip #ifndef _XMLOFF_NMSPMAP_HXX
// auto strip #include "nmspmap.hxx"
// auto strip #endif

#ifndef _XMLOFF_XMLNMSPE_HXX
#include "xmlnmspe.hxx"
#endif

// auto strip #ifndef _XMLOFF_XMLTOKEN_HXX
// auto strip #include "xmltoken.hxx"
// auto strip #endif

// auto strip #ifndef _XMLOFF_FAMILIES_HXX
// auto strip #include "families.hxx"
// auto strip #endif

#ifndef _XMLOFF_XMLSHAPEPROPERTYSETCONTEXT_HXX
#include "XMLShapePropertySetContext.hxx"
#endif

#ifndef _XMLOFF_XMLGRAPHICSDEFAULTSTYLE_HXX
#include "XMLGraphicsDefaultStyle.hxx"
#endif
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::xml::sax;

using ::binfilter::xmloff::token::IsXMLToken;
using ::binfilter::xmloff::token::XML_PROPERTIES;

// ---------------------------------------------------------------------

TYPEINIT1( XMLGraphicsDefaultStyle, XMLPropStyleContext );

XMLGraphicsDefaultStyle::XMLGraphicsDefaultStyle( SvXMLImport& rImport, sal_uInt16 nPrfx, const OUString& rLName, const Reference< XAttributeList >& xAttrList, SvXMLStylesContext& rStyles )
: XMLPropStyleContext( rImport, nPrfx, rLName, xAttrList, rStyles, XML_STYLE_FAMILY_SD_GRAPHICS_ID, sal_True )
{
}

XMLGraphicsDefaultStyle::~XMLGraphicsDefaultStyle()
{
}

SvXMLImportContext *XMLGraphicsDefaultStyle::CreateChildContext( sal_uInt16 nPrefix, const OUString& rLocalName, const Reference< XAttributeList > & xAttrList )
{
    SvXMLImportContext *pContext = 0;

    if( XML_NAMESPACE_STYLE == nPrefix && IsXMLToken( rLocalName, XML_PROPERTIES ) )
    {
        UniReference < SvXMLImportPropertyMapper > xImpPrMap = GetStyles()->GetImportPropertyMapper( GetFamily() );
        if( xImpPrMap.is() )
            pContext = new XMLShapePropertySetContext( GetImport(), nPrefix, rLocalName, xAttrList, GetProperties(), xImpPrMap );
    }

    if( !pContext )
        pContext = XMLPropStyleContext::CreateChildContext( nPrefix, rLocalName, xAttrList );

    return pContext;
}

// This method is called for every default style
void XMLGraphicsDefaultStyle::SetDefaults()
{
    Reference< XMultiServiceFactory > xFact( GetImport().GetModel(), UNO_QUERY );
    if( !xFact.is() )
        return;

    Reference< XPropertySet > xDefaults( xFact->createInstance( OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.drawing.Defaults") ) ), UNO_QUERY );
    if( !xDefaults.is() )
        return;

    FillPropertySet( xDefaults );
}


}//end of namespace binfilter
