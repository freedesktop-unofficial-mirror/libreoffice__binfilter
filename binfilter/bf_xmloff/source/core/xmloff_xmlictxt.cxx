/*************************************************************************
 *
 *  $RCSfile: xmloff_xmlictxt.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 19:47:59 $
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

// auto strip #ifndef _COM_SUN_STAR_XML_SAX_SAXPARSEEXCEPTION_HPP_
// auto strip #include <com/sun/star/xml/sax/SAXParseException.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_XML_SAX_XEXTENDEDDOCUMENTHANDLER_HPP_
// auto strip #include <com/sun/star/xml/sax/XExtendedDocumentHandler.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_XML_SAX_SAXEXCEPTION_HPP_
// auto strip #include <com/sun/star/xml/sax/SAXException.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_XML_SAX_XDOCUMENTHANDLER_HPP_
// auto strip #include <com/sun/star/xml/sax/XDocumentHandler.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_XML_SAX_XATTRIBUTELIST_HPP_
// auto strip #include <com/sun/star/xml/sax/XAttributeList.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_XML_SAX_XLOCATOR_HPP_
// auto strip #include <com/sun/star/xml/sax/XLocator.hpp>
// auto strip #endif

// auto strip #ifndef _XMLOFF_NMSPMAP_HXX
// auto strip #include "nmspmap.hxx"
// auto strip #endif

#ifndef _XMLOFF_XMLIMP_HXX
#include "xmlimp.hxx"
#endif

// auto strip #ifndef _XMLOFF_XMLICTXT_HXX
// auto strip #include <xmlictxt.hxx>
// auto strip #endif
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;

TYPEINIT0( SvXMLImportContext );

SvXMLImportContext::SvXMLImportContext( SvXMLImport& rImp, USHORT nPrfx,
                              const OUString& rLName ) :
    rImport( rImp ),
    nPrefix( nPrfx ),
    aLocalName( rLName ),
    pRewindMap( 0 )
{
}

SvXMLImportContext::~SvXMLImportContext()
{
}

SvXMLImportContext *SvXMLImportContext::CreateChildContext( USHORT nPrefix,
                                            const OUString& rLocalName,
                                            const uno::Reference< xml::sax::XAttributeList >& xAttrList )
{
    return rImport.CreateContext( nPrefix, rLocalName, xAttrList );
}

void SvXMLImportContext::StartElement( const uno::Reference< xml::sax::XAttributeList >& )
{
}

void SvXMLImportContext::EndElement()
{
}

void SvXMLImportContext::Characters( const OUString& rChars )
{
}


}//end of namespace binfilter
