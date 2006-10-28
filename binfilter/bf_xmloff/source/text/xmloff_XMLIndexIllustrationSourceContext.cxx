/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_XMLIndexIllustrationSourceContext.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:12:17 $
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


#ifndef _XMLOFF_XMLINDEXILLUSTRATIONSOURCECONTEXT_HXX_
#include "XMLIndexIllustrationSourceContext.hxx"
#endif


#ifndef _XMLOFF_XMLINDEXTEMPLATECONTEXT_HXX_
#include "XMLIndexTemplateContext.hxx"
#endif




#ifndef _XMLOFF_XMLNMSPE_HXX
#include "xmlnmspe.hxx"
#endif





namespace binfilter {

using ::rtl::OUString;
using ::com::sun::star::beans::XPropertySet;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::Any;
using ::com::sun::star::xml::sax::XAttributeList;
using ::binfilter::xmloff::token::IsXMLToken;
using ::binfilter::xmloff::token::XML_ILLUSTRATION_INDEX_ENTRY_TEMPLATE;
using ::binfilter::xmloff::token::XML_TOKEN_INVALID;

TYPEINIT1(XMLIndexIllustrationSourceContext, XMLIndexTableSourceContext);


XMLIndexIllustrationSourceContext::XMLIndexIllustrationSourceContext(
    SvXMLImport& rImport,
    sal_uInt16 nPrfx,
    const OUString& rLocalName,
    Reference<XPropertySet> & rPropSet) :
        XMLIndexTableSourceContext(rImport, nPrfx, rLocalName, rPropSet)
{
}

XMLIndexIllustrationSourceContext::~XMLIndexIllustrationSourceContext()
{
}

SvXMLImportContext* XMLIndexIllustrationSourceContext::CreateChildContext(
    sal_uInt16 nPrefix,
    const OUString& rLocalName,
    const Reference<XAttributeList> & xAttrList )
{
    if ( ( XML_NAMESPACE_TEXT == nPrefix ) &&
         ( IsXMLToken( rLocalName, XML_ILLUSTRATION_INDEX_ENTRY_TEMPLATE ) ) )
    {
        return new XMLIndexTemplateContext(GetImport(), rIndexPropertySet,
                                           nPrefix, rLocalName,
                                           aLevelNameTableMap,
                                           XML_TOKEN_INVALID, // no outline-level attr
                                           aLevelStylePropNameTableMap,
                                           aAllowedTokenTypesTable);
    }
    else
    {
        return XMLIndexSourceBaseContext::CreateChildContext(nPrefix,
                                                             rLocalName,
                                                             xAttrList);
    }

}
}//end of namespace binfilter
