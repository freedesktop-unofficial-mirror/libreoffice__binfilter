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

#include "XMLLineNumberingSeparatorImportContext.hxx"

#include "XMLLineNumberingImportContext.hxx"

#include "xmlimp.hxx"

#include "nmspmap.hxx"

#include "xmlnmspe.hxx"


#include "xmluconv.hxx"
namespace binfilter {


using namespace ::com::sun::star::uno;

using ::com::sun::star::xml::sax::XAttributeList;
using ::rtl::OUString;
using ::rtl::OUStringBuffer;
using ::binfilter::xmloff::token::IsXMLToken;
using ::binfilter::xmloff::token::XML_INCREMENT;

TYPEINIT1( XMLLineNumberingSeparatorImportContext, SvXMLImportContext );

XMLLineNumberingSeparatorImportContext::XMLLineNumberingSeparatorImportContext(
    SvXMLImport& rInImport,
    sal_uInt16 nPrfx,
    const OUString& rLocalName,
    XMLLineNumberingImportContext& rLineNumbering) :
        SvXMLImportContext(rInImport, nPrfx, rLocalName),
        rLineNumberingContext(rLineNumbering)
{
}

XMLLineNumberingSeparatorImportContext::~XMLLineNumberingSeparatorImportContext()
{
}

void XMLLineNumberingSeparatorImportContext::StartElement(
    const Reference<XAttributeList> & xAttrList)
{
    sal_Int16 nLength = xAttrList->getLength();
    for(sal_Int16 i=0; i<nLength; i++)
    {
        OUString sLocalName;
        sal_uInt16 nLclPrefix = GetImport().GetNamespaceMap().
            GetKeyByAttrName( xAttrList->getNameByIndex(i), &sLocalName );

        if ( (nLclPrefix == XML_NAMESPACE_TEXT) &&
             IsXMLToken(sLocalName, XML_INCREMENT) )
        {
            sal_Int32 nTmp;
            if (SvXMLUnitConverter::convertNumber(
                nTmp, xAttrList->getValueByIndex(i), 0))
            {
                rLineNumberingContext.SetSeparatorIncrement((sal_Int16)nTmp);
            }
            // else: invalid number -> ignore
        }
        // else: unknown attribute -> ignore
    }
}

void XMLLineNumberingSeparatorImportContext::Characters(
    const OUString& rChars )
{
    sSeparatorBuf.append(rChars);
}

void XMLLineNumberingSeparatorImportContext::EndElement()
{
    rLineNumberingContext.SetSeparatorText(sSeparatorBuf.makeStringAndClear());
}
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
