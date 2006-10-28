/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_XMLAutoMarkFileContext.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:08:54 $
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

#ifndef _XMLOFF_XMLAUTOMARKFILECONTEXT_HXX_
#include "XMLAutoMarkFileContext.hxx"
#endif

#ifndef _XMLOFF_XMLIMP_HXX
#include "xmlimp.hxx"
#endif


#ifndef _XMLOFF_NMSPMAP_HXX
#include "nmspmap.hxx"
#endif

#ifndef _XMLOFF_XMLNMSPE_HXX
#include "xmlnmspe.hxx"
#endif




namespace binfilter {


using ::rtl::OUString;
using ::com::sun::star::uno::Any;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::UNO_QUERY;
using ::com::sun::star::xml::sax::XAttributeList;
using ::com::sun::star::beans::XPropertySet;

using ::binfilter::xmloff::token::IsXMLToken;
using ::binfilter::xmloff::token::XML_HREF;


TYPEINIT1( XMLAutoMarkFileContext, SvXMLImportContext );

XMLAutoMarkFileContext::XMLAutoMarkFileContext(
    SvXMLImport& rImport,
    sal_uInt16 nPrefix,
    const OUString& rLocalName) :
        SvXMLImportContext(rImport, nPrefix, rLocalName),
        sIndexAutoMarkFileURL(
            RTL_CONSTASCII_USTRINGPARAM("IndexAutoMarkFileURL"))
{
}

XMLAutoMarkFileContext::~XMLAutoMarkFileContext()
{
}


void XMLAutoMarkFileContext::StartElement(
    const Reference<XAttributeList> & xAttrList)
{
    // scan for text:alphabetical-index-auto-mark-file attribute, and if
    // found set value with the document

    sal_Int16 nLength = xAttrList->getLength();
    for( sal_Int16 i = 0; i < nLength; i++ )
    {
        OUString sLocalName;
        sal_uInt16 nPrefix = GetImport().GetNamespaceMap().
            GetKeyByAttrName( xAttrList->getNameByIndex(i), &sLocalName );

        if ( ( XML_NAMESPACE_XLINK == nPrefix ) &&
             IsXMLToken(sLocalName, XML_HREF) )
        {
            Any aAny;
            aAny <<= GetImport().GetAbsoluteReference( xAttrList->getValueByIndex(i) );
            Reference<XPropertySet> xPropertySet(
                GetImport().GetModel(), UNO_QUERY );
            if (xPropertySet.is())
            {
                xPropertySet->setPropertyValue( sIndexAutoMarkFileURL, aAny );
            }
        }
    }
}
}//end of namespace binfilter
