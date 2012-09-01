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

#include "XMLIndexSimpleEntryContext.hxx"
#include "XMLIndexTemplateContext.hxx"

#include "xmlimp.hxx"
#include "nmspmap.hxx"
#include "xmlnmspe.hxx"

namespace binfilter {

using ::rtl::OUString;
using ::com::sun::star::beans::PropertyValue;
using ::com::sun::star::beans::PropertyValues;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::Sequence;
using ::com::sun::star::uno::Any;
using ::com::sun::star::xml::sax::XAttributeList;
using ::binfilter::xmloff::token::IsXMLToken;
using ::binfilter::xmloff::token::XML_STYLE_NAME;

const sal_Char sAPI_TokenType[] = "TokenType";
const sal_Char sAPI_CharacterStyleName[] = "CharacterStyleName";

TYPEINIT1( XMLIndexSimpleEntryContext, SvXMLImportContext);

XMLIndexSimpleEntryContext::XMLIndexSimpleEntryContext(
    SvXMLImport& rInImport,
    const OUString& rEntry,
    XMLIndexTemplateContext& rTemplate,
    sal_uInt16 nPrfx,
    const OUString& rLocalName ) :
        SvXMLImportContext(rInImport, nPrfx, rLocalName),
        rEntryType(rEntry),
        sCharStyleName(),
        bCharStyleNameOK(sal_False),
        rTemplateContext(rTemplate),
        nValues(1)
{
}

XMLIndexSimpleEntryContext::~XMLIndexSimpleEntryContext()
{
}

void XMLIndexSimpleEntryContext::StartElement(
    const Reference<XAttributeList> & xAttrList)
{
    // we know only one attribute: style-name
    sal_Int16 nLength = xAttrList->getLength();
    for(sal_Int16 nAttr = 0; nAttr < nLength; nAttr++)
    {
        OUString sLocalName;
        sal_uInt16 nLclPrefix = GetImport().GetNamespaceMap().
            GetKeyByAttrName( xAttrList->getNameByIndex(nAttr),
                              &sLocalName );
        if ( (XML_NAMESPACE_TEXT == nLclPrefix) &&
             IsXMLToken(sLocalName, XML_STYLE_NAME) )
        {
            sCharStyleName = xAttrList->getValueByIndex(nAttr);
            bCharStyleNameOK = sal_True;
        }
    }

    // if we have a style name, set it!
    if (bCharStyleNameOK)
    {
        nValues++;
    }

}

void XMLIndexSimpleEntryContext::EndElement()
{
    Sequence<PropertyValue> aValues(nValues);

    FillPropertyValues(aValues);
    rTemplateContext.addTemplateEntry(aValues);
}

void XMLIndexSimpleEntryContext::FillPropertyValues(
    ::com::sun::star::uno::Sequence<
        ::com::sun::star::beans::PropertyValue> & rValues)
{
    // due to the limited number of subclasses, we fill the values
    // directly into the slots. Subclasses will have to know they can
    // only use slot so-and-so.

    Any aAny;

    // token type
    rValues[0].Name = rTemplateContext.sTokenType;
    aAny <<= rEntryType;
    rValues[0].Value = aAny;

    // char style
    if (bCharStyleNameOK)
    {
        rValues[1].Name = rTemplateContext.sCharacterStyleName;
        aAny <<= sCharStyleName;
        rValues[1].Value = aAny;
    }

}
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
