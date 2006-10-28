/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_XMLIndexBibliographySourceContext.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:11:43 $
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


#ifndef _XMLOFF_XMLINDEXBIBLIOGRAPHYSOURCECONTEXT_HXX_
#include "XMLIndexBibliographySourceContext.hxx"
#endif



#ifndef _XMLOFF_XMLINDEXTEMPLATECONTEXT_HXX_
#include "XMLIndexTemplateContext.hxx"
#endif






#ifndef _XMLOFF_XMLNMSPE_HXX
#include "xmlnmspe.hxx"
#endif





namespace binfilter {


using namespace ::binfilter::xmloff::token;

using ::rtl::OUString;
using ::com::sun::star::beans::XPropertySet;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::Any;
using ::com::sun::star::xml::sax::XAttributeList;


TYPEINIT1(XMLIndexBibliographySourceContext, XMLIndexSourceBaseContext);


XMLIndexBibliographySourceContext::XMLIndexBibliographySourceContext(
    SvXMLImport& rImport,
    sal_uInt16 nPrfx,
    const OUString& rLocalName,
    Reference<XPropertySet> & rPropSet) :
        XMLIndexSourceBaseContext(rImport, nPrfx, rLocalName,
                                  rPropSet, sal_False)
{
}

XMLIndexBibliographySourceContext::~XMLIndexBibliographySourceContext()
{
}

void XMLIndexBibliographySourceContext::ProcessAttribute(
    enum IndexSourceParamEnum eParam,
    const OUString& rValue)
{
    // We have no attributes. Who wants attributes, anyway?
}


void XMLIndexBibliographySourceContext::EndElement()
{
    // No attributes, no properties.
}


SvXMLImportContext* XMLIndexBibliographySourceContext::CreateChildContext(
    sal_uInt16 nPrefix,
    const OUString& rLocalName,
    const Reference<XAttributeList> & xAttrList )
{
    if ( ( XML_NAMESPACE_TEXT == nPrefix ) &&
         ( IsXMLToken( rLocalName, XML_BIBLIOGRAPHY_ENTRY_TEMPLATE ) ) )
    {
        return new XMLIndexTemplateContext(GetImport(), rIndexPropertySet,
                                           nPrefix, rLocalName,
                                           aLevelNameBibliographyMap,
                                           XML_BIBLIOGRAPHY_TYPE,
                                           aLevelStylePropNameBibliographyMap,
                                           aAllowedTokenTypesBibliography);
    }
    else
    {
        return XMLIndexSourceBaseContext::CreateChildContext(nPrefix,
                                                             rLocalName,
                                                             xAttrList);
    }

}
}//end of namespace binfilter
