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

#include "XMLIndexTitleTemplateContext.hxx"


#include "xmlimp.hxx"

#include "nmspmap.hxx"

#include "xmlnmspe.hxx"

namespace binfilter {


using ::rtl::OUString;
using ::rtl::OUStringBuffer;
using ::com::sun::star::beans::XPropertySet;
using ::com::sun::star::uno::Any;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::xml::sax::XAttributeList;
using ::binfilter::xmloff::token::IsXMLToken;
using ::binfilter::xmloff::token::XML_STYLE_NAME;


const sal_Char sAPI_Title[] = "Title";
const sal_Char sAPI_ParaStyleHeading[] = "ParaStyleHeading";


TYPEINIT1( XMLIndexTitleTemplateContext, SvXMLImportContext );

XMLIndexTitleTemplateContext::XMLIndexTitleTemplateContext(
    SvXMLImport& rInImport,
    Reference<XPropertySet> & rPropSet,
    sal_uInt16 nPrfx,
    const OUString& rLocalName) :
        SvXMLImportContext(rInImport, nPrfx, rLocalName),
        sTitle(RTL_CONSTASCII_USTRINGPARAM(sAPI_Title)),
        sParaStyleHeading(RTL_CONSTASCII_USTRINGPARAM(sAPI_ParaStyleHeading)),
        sStyleName(),
        bStyleNameOK(sal_False),
        sContent(),
        rTOCPropertySet(rPropSet)
{
}


XMLIndexTitleTemplateContext::~XMLIndexTitleTemplateContext()
{
}

void XMLIndexTitleTemplateContext::StartElement(
    const Reference<XAttributeList> & xAttrList)
{
    // there's only one attribute: style-name
    sal_Int16 nLength = xAttrList->getLength();
    for(sal_Int16 nAttr = 0; nAttr < nLength; nAttr++)
    {
        OUString sLocalName;
        sal_uInt16 nLclPrefix = GetImport().GetNamespaceMap().
            GetKeyByAttrName( xAttrList->getNameByIndex(nAttr),
                              &sLocalName );
        if ( (XML_NAMESPACE_TEXT == nLclPrefix) &&
             (IsXMLToken(sLocalName, XML_STYLE_NAME)) )
        {
            sStyleName = xAttrList->getValueByIndex(nAttr);
            bStyleNameOK = sal_True;
        }
    }
}

void XMLIndexTitleTemplateContext::EndElement()
{
    Any aAny;

    aAny <<= sContent.makeStringAndClear();
    rTOCPropertySet->setPropertyValue(sTitle, aAny);

    if (bStyleNameOK)
    {
        aAny <<= sStyleName;
        rTOCPropertySet->setPropertyValue(sParaStyleHeading, aAny);
    }
}

void XMLIndexTitleTemplateContext::Characters(
    const OUString& sString)
{
    sContent.append(sString);
}
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
