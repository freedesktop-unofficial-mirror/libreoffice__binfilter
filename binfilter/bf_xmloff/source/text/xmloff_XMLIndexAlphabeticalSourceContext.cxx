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


#include "XMLIndexAlphabeticalSourceContext.hxx"



#include "XMLIndexTemplateContext.hxx"






#include "xmlnmspe.hxx"



#include "xmluconv.hxx"


namespace binfilter {




using ::rtl::OUString;
using ::com::sun::star::beans::XPropertySet;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::Any;
using ::com::sun::star::xml::sax::XAttributeList;
using ::binfilter::xmloff::token::IsXMLToken;
using ::binfilter::xmloff::token::XML_ALPHABETICAL_INDEX_ENTRY_TEMPLATE;
using ::binfilter::xmloff::token::XML_OUTLINE_LEVEL;

const sal_Char sAPI_MainEntryCharacterStyleName[] = "MainEntryCharacterStyleName";
const sal_Char sAPI_UseAlphabeticalSeparators[] = "UseAlphabeticalSeparators";
const sal_Char sAPI_UseCombinedEntries[] = "UseCombinedEntries";
const sal_Char sAPI_IsCaseSensitive[] = "IsCaseSensitive";
const sal_Char sAPI_UseKeyAsEntry[] = "UseKeyAsEntry";
const sal_Char sAPI_UseUpperCase[] = "UseUpperCase";
const sal_Char sAPI_UseDash[] = "UseDash";
const sal_Char sAPI_UsePP[] = "UsePP";
const sal_Char sAPI_SortAlgorithm[] = "SortAlgorithm";
const sal_Char sAPI_Locale[] = "Locale";


TYPEINIT1( XMLIndexAlphabeticalSourceContext, XMLIndexSourceBaseContext );

XMLIndexAlphabeticalSourceContext::XMLIndexAlphabeticalSourceContext(
    SvXMLImport& rInImport,
    sal_uInt16 nPrfx,
    const OUString& rLocalName,
    Reference<XPropertySet> & rPropSet) :
        XMLIndexSourceBaseContext(rInImport, nPrfx, rLocalName,
                                  rPropSet, sal_False),
        sMainEntryCharacterStyleName(RTL_CONSTASCII_USTRINGPARAM(
            sAPI_MainEntryCharacterStyleName)),
        sUseAlphabeticalSeparators(RTL_CONSTASCII_USTRINGPARAM(
            sAPI_UseAlphabeticalSeparators)),
        sUseCombinedEntries(RTL_CONSTASCII_USTRINGPARAM(
            sAPI_UseCombinedEntries)),
        sIsCaseSensitive(RTL_CONSTASCII_USTRINGPARAM(sAPI_IsCaseSensitive)),
        sUseKeyAsEntry(RTL_CONSTASCII_USTRINGPARAM(sAPI_UseKeyAsEntry)),
        sUseUpperCase(RTL_CONSTASCII_USTRINGPARAM(sAPI_UseUpperCase)),
        sUseDash(RTL_CONSTASCII_USTRINGPARAM(sAPI_UseDash)),
        sUsePP(RTL_CONSTASCII_USTRINGPARAM(sAPI_UsePP)),
        sIsCommaSeparated(RTL_CONSTASCII_USTRINGPARAM("IsCommaSeparated")),
        sSortAlgorithm(RTL_CONSTASCII_USTRINGPARAM(sAPI_SortAlgorithm)),
        sLocale(RTL_CONSTASCII_USTRINGPARAM(sAPI_Locale)),
        sMainEntryStyleName(),
        bMainEntryStyleNameOK(sal_False),
        bSeparators(sal_False),
        bCombineEntries(sal_True),
        bCaseSensitive(sal_True),
        bEntry(sal_False),
        bUpperCase(sal_False),
        bCombineDash(sal_False),
        bCombinePP(sal_True),
        bCommaSeparated(sal_False)
{
}

XMLIndexAlphabeticalSourceContext::~XMLIndexAlphabeticalSourceContext()
{
}

void XMLIndexAlphabeticalSourceContext::ProcessAttribute(
    enum IndexSourceParamEnum eParam,
    const OUString& rValue)
{
    sal_Bool bTmp;

    switch (eParam)
    {
        case XML_TOK_INDEXSOURCE_MAIN_ENTRY_STYLE:
            sMainEntryStyleName = rValue;
            bMainEntryStyleNameOK = sal_True;
            break;

        case XML_TOK_INDEXSOURCE_IGNORE_CASE:
            if (SvXMLUnitConverter::convertBool(bTmp, rValue))
            {
                bCaseSensitive = !bTmp;
            }
            break;

        case XML_TOK_INDEXSOURCE_SEPARATORS:
            if (SvXMLUnitConverter::convertBool(bTmp, rValue))
            {
                bSeparators = bTmp;
            }
            break;

        case XML_TOK_INDEXSOURCE_COMBINE_ENTRIES:
            if (SvXMLUnitConverter::convertBool(bTmp, rValue))
            {
                bCombineEntries = bTmp;
            }
            break;

        case XML_TOK_INDEXSOURCE_COMBINE_WITH_DASH:
            if (SvXMLUnitConverter::convertBool(bTmp, rValue))
            {
                bCombineDash = bTmp;
            }
            break;
        case XML_TOK_INDEXSOURCE_KEYS_AS_ENTRIES:
            if (SvXMLUnitConverter::convertBool(bTmp, rValue))
            {
                bEntry = bTmp;
            }
            break;

        case XML_TOK_INDEXSOURCE_COMBINE_WITH_PP:
            if (SvXMLUnitConverter::convertBool(bTmp, rValue))
            {
                bCombinePP = bTmp;
            }
            break;

        case XML_TOK_INDEXSOURCE_CAPITALIZE:
            if (SvXMLUnitConverter::convertBool(bTmp, rValue))
            {
                bUpperCase = bTmp;
            }
            break;

        case XML_TOK_INDEXSOURCE_COMMA_SEPARATED:
            if (SvXMLUnitConverter::convertBool(bTmp, rValue))
            {
                bCommaSeparated = bTmp;
            }
            break;

        case XML_TOK_INDEXSOURCE_SORT_ALGORITHM:
            sAlgorithm = rValue;
            break;
        case XML_TOK_INDEXSOURCE_LANGUAGE:
            aLocale.Language = rValue;
            break;
        case XML_TOK_INDEXSOURCE_COUNTRY:
            aLocale.Country = rValue;
            break;

        default:
            XMLIndexSourceBaseContext::ProcessAttribute(eParam, rValue);
            break;
    }
}

void XMLIndexAlphabeticalSourceContext::EndElement()
{

    Any aAny;

    if (bMainEntryStyleNameOK)
    {
        aAny <<= sMainEntryStyleName;
        rIndexPropertySet->setPropertyValue(sMainEntryCharacterStyleName,aAny);
    }

    aAny.setValue(&bSeparators, ::getBooleanCppuType());
    rIndexPropertySet->setPropertyValue(sUseAlphabeticalSeparators, aAny);

    aAny.setValue(&bCombineEntries, ::getBooleanCppuType());
    rIndexPropertySet->setPropertyValue(sUseCombinedEntries, aAny);

    aAny.setValue(&bCaseSensitive, ::getBooleanCppuType());
    rIndexPropertySet->setPropertyValue(sIsCaseSensitive, aAny);

    aAny.setValue(&bEntry, ::getBooleanCppuType());
    rIndexPropertySet->setPropertyValue(sUseKeyAsEntry, aAny);

    aAny.setValue(&bUpperCase, ::getBooleanCppuType());
    rIndexPropertySet->setPropertyValue(sUseUpperCase, aAny);

    aAny.setValue(&bCombineDash, ::getBooleanCppuType());
    rIndexPropertySet->setPropertyValue(sUseDash, aAny);

    aAny.setValue(&bCombinePP, ::getBooleanCppuType());
    rIndexPropertySet->setPropertyValue(sUsePP, aAny);

    aAny.setValue(&bCommaSeparated, ::getBooleanCppuType());
    rIndexPropertySet->setPropertyValue(sIsCommaSeparated, aAny);


    if (sAlgorithm.getLength() > 0)
    {
        aAny <<= sAlgorithm;
        rIndexPropertySet->setPropertyValue(sSortAlgorithm, aAny);
    }

    if ( (aLocale.Language.getLength() > 0) &&
         (aLocale.Country.getLength() > 0)      )
    {
        aAny <<= aLocale;
        rIndexPropertySet->setPropertyValue(sLocale, aAny);
    }

    XMLIndexSourceBaseContext::EndElement();
}

SvXMLImportContext* XMLIndexAlphabeticalSourceContext::CreateChildContext(
    sal_uInt16 nInPrefix,
    const OUString& rLocalName,
    const Reference<XAttributeList> & xAttrList )
{
    if ( (XML_NAMESPACE_TEXT == nInPrefix) &&
         IsXMLToken( rLocalName, XML_ALPHABETICAL_INDEX_ENTRY_TEMPLATE ) )
    {
        return new XMLIndexTemplateContext(GetImport(), rIndexPropertySet,
                                           nInPrefix, rLocalName,
                                           aLevelNameAlphaMap,
                                           XML_OUTLINE_LEVEL,
                                           aLevelStylePropNameAlphaMap,
                                           aAllowedTokenTypesAlpha);
    }
    else
    {
        return XMLIndexSourceBaseContext::CreateChildContext(nInPrefix,
                                                             rLocalName,
                                                             xAttrList);
    }
}
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
