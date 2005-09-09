/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ImageStyle.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 17:10:38 $
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

#ifndef _XMLOFF_IMAGESTYLE_HXX
#define _XMLOFF_IMAGESTYLE_HXX

#ifndef _COM_SUN_STAR_XML_SAX_XDOCUMENTHANDLER_HPP_
#include <com/sun/star/xml/sax/XDocumentHandler.hpp>
#endif
namespace binfilter {

class SvXMLNamespaceMap;
class SvXMLAttributeList;
class SvXMLUnitConverter;
class SvXMLExport;
class SvXMLImport;

class XMLImageStyle
{
public:
    XMLImageStyle();
    ~XMLImageStyle();

    sal_Bool exportXML( const ::rtl::OUString& rStrName, const ::com::sun::star::uno::Any& rValue, SvXMLExport& rExport );
    sal_Bool importXML( const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList, ::com::sun::star::uno::Any& rValue, ::rtl::OUString& rStrName, SvXMLImport& rImport );

private:

    sal_Bool ImpExportXML( const ::rtl::OUString& rStrName, const ::com::sun::star::uno::Any& rValue,
                           SvXMLExport& rExport );
    sal_Bool ImpImportXML( const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList,
                           ::com::sun::star::uno::Any& rValue, ::rtl::OUString& rStrName,
                           SvXMLImport& rImport );
};

}//end of namespace binfilter
#endif // _XMLOFF_IMAGESTYLE_HXX
