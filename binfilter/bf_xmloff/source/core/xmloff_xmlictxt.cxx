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

#include "xmlimp.hxx"

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

SvXMLImportContext *SvXMLImportContext::CreateChildContext( USHORT nInPrefix,
                                            const OUString& rLocalName,
                                            const uno::Reference< xml::sax::XAttributeList >& xAttrList )
{
    return rImport.CreateContext( nInPrefix, rLocalName, xAttrList );
}

void SvXMLImportContext::StartElement( const uno::Reference< xml::sax::XAttributeList >& )
{
}

void SvXMLImportContext::EndElement()
{
}

void SvXMLImportContext::Characters( const OUString& /*rChars*/ )
{
}


}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
