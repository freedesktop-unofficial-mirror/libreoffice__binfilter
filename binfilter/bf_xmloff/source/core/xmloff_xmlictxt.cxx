/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_xmlictxt.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 01:41:31 $
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



#ifndef _XMLOFF_XMLIMP_HXX
#include "xmlimp.hxx"
#endif

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
