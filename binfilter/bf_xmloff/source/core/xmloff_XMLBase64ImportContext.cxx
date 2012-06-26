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
#include "xmluconv.hxx"

#include <com/sun/star/io/XOutputStream.hpp>

#include <sax/tools/converter.hxx>

#include "XMLBase64ImportContext.hxx"
namespace binfilter {

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::xml::sax;
using namespace ::com::sun::star::io;

using rtl::OUString;

//-----------------------------------------------------------------------------

TYPEINIT1( XMLBase64ImportContext, SvXMLImportContext );


XMLBase64ImportContext::XMLBase64ImportContext(
        SvXMLImport& rInImport, USHORT nPrfx, const OUString& rLName,
        const Reference< XAttributeList >& /*xAttrList*/,
        const Reference< XOutputStream >& rOut ) :
    SvXMLImportContext( rInImport, nPrfx, rLName ),
    xOut( rOut )
{
}

XMLBase64ImportContext::~XMLBase64ImportContext()
{
}


void XMLBase64ImportContext::EndElement()
{
    xOut->closeOutput();
}

void XMLBase64ImportContext::Characters( const ::rtl::OUString& rChars )
{
    OUString sTrimmedChars( rChars. trim() );
    if( sTrimmedChars.getLength() )
    {
        OUString sChars;
        if( sBase64CharsLeft.getLength() )
        {
            sChars = sBase64CharsLeft;
            sChars += sTrimmedChars;
            sBase64CharsLeft = OUString();
        }
        else
        {
            sChars = sTrimmedChars;
        }
        Sequence< sal_Int8 > aBuffer( (sChars.getLength() / 4) * 3 );
        sal_Int32 nCharsDecoded =
            ::sax::Converter::decodeBase64SomeChars(aBuffer, sChars);
        xOut->writeBytes( aBuffer );
        if( nCharsDecoded != sChars.getLength() )
            sBase64CharsLeft = sChars.copy( nCharsDecoded );
    }
}

}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
