/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#include "SchXMLParagraphContext.hxx"

#include "xmlnmspe.hxx"
#include "xmltoken.hxx"
namespace binfilter {

using namespace ::com::sun::star;
using ::rtl::OUString;

SchXMLParagraphContext::SchXMLParagraphContext( SvXMLImport& rInImport,
                                                const OUString& rLocalName,
                                                OUString& rText ) :
        SvXMLImportContext( rInImport, XML_NAMESPACE_TEXT, rLocalName ),
        mrText( rText )
{
}

SchXMLParagraphContext::~SchXMLParagraphContext()
{}

void SchXMLParagraphContext::EndElement()
{
    mrText = maBuffer.makeStringAndClear();
}

SvXMLImportContext* SchXMLParagraphContext::CreateChildContext(
    USHORT nInPrefix,
    const OUString& rLocalName,
    const uno::Reference< xml::sax::XAttributeList >& /*xAttrList*/ )
{
    if( nInPrefix == XML_NAMESPACE_TEXT )
    {
        if( rLocalName.equals( ::binfilter::xmloff::token::GetXMLToken( ::binfilter::xmloff::token::XML_TAB_STOP )))
        {
            maBuffer.append( sal_Unicode( 0x0009 ));  // tabulator
        }
        else if( rLocalName.equals( ::binfilter::xmloff::token::GetXMLToken( ::binfilter::xmloff::token::XML_LINE_BREAK )))
        {
            maBuffer.append( sal_Unicode( 0x000A ));  // linefeed
        }
    }

    return new SvXMLImportContext( GetImport(), nInPrefix, rLocalName );
}

void SchXMLParagraphContext::Characters( const OUString& rChars )
{
    maBuffer.append( rChars );
}
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
