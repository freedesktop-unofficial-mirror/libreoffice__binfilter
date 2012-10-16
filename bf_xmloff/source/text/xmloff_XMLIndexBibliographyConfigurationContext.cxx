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


#include "XMLIndexBibliographyConfigurationContext.hxx"

#include "XMLIndexBibliographyEntryContext.hxx"


#include "xmlimp.hxx"


#include "nmspmap.hxx"

#include "xmlnmspe.hxx"


#include "xmluconv.hxx"




namespace binfilter {

using namespace ::com::sun::star::text;
using namespace ::com::sun::star::uno;
using namespace ::binfilter::xmloff::token;

using ::rtl::OUString;
using ::com::sun::star::xml::sax::XAttributeList;
using ::com::sun::star::beans::PropertyValue;
using ::com::sun::star::beans::XPropertySet;
using ::com::sun::star::lang::XMultiServiceFactory;

const sal_Char sAPI_FieldMaster_Bibliography[] =
                                "com.sun.star.text.FieldMaster.Bibliography";


TYPEINIT1( XMLIndexBibliographyConfigurationContext, SvXMLStyleContext );

XMLIndexBibliographyConfigurationContext::XMLIndexBibliographyConfigurationContext(
    SvXMLImport& rInImport,
    sal_uInt16 nPrfx,
    const OUString& rLocalName,
    const Reference<XAttributeList> & xAttrList) :
        SvXMLStyleContext(rInImport, nPrfx, rLocalName, xAttrList, XML_STYLE_FAMILY_TEXT_BIBLIOGRAPHYCONFIG),
        sFieldMaster_Bibliography(
            RTL_CONSTASCII_USTRINGPARAM(sAPI_FieldMaster_Bibliography)),
        sBracketBefore(RTL_CONSTASCII_USTRINGPARAM("BracketBefore")),
        sBracketAfter(RTL_CONSTASCII_USTRINGPARAM("BracketAfter")),
        sIsNumberEntries(RTL_CONSTASCII_USTRINGPARAM("IsNumberEntries")),
        sIsSortByPosition(RTL_CONSTASCII_USTRINGPARAM("IsSortByPosition")),
        sSortKeys(RTL_CONSTASCII_USTRINGPARAM("SortKeys")),
        sSortKey(RTL_CONSTASCII_USTRINGPARAM("SortKey")),
        sIsSortAscending(RTL_CONSTASCII_USTRINGPARAM("IsSortAscending")),
        sSortAlgorithm(RTL_CONSTASCII_USTRINGPARAM("SortAlgorithm")),
        sLocale(RTL_CONSTASCII_USTRINGPARAM("Locale")),
        sSuffix(),
        sPrefix(),
        sAlgorithm(),
        aLocale(),
        bNumberedEntries(sal_False),
        bSortByPosition(sal_True)
{
}

XMLIndexBibliographyConfigurationContext::~XMLIndexBibliographyConfigurationContext()
{
}

void XMLIndexBibliographyConfigurationContext::StartElement(
    const Reference<XAttributeList> & xAttrList)
{
    sal_Int16 nLength = xAttrList->getLength();
    for(sal_Int16 nAttr = 0; nAttr < nLength; nAttr++)
    {
        OUString sLocalName;
        sal_uInt16 nLclPrefix = GetImport().GetNamespaceMap().
            GetKeyByAttrName( xAttrList->getNameByIndex(nAttr),
                              &sLocalName );

        ProcessAttribute(nLclPrefix, sLocalName,
                         xAttrList->getValueByIndex(nAttr));
        // else: ignore
    }
}

void XMLIndexBibliographyConfigurationContext::ProcessAttribute(
    sal_uInt16 nInPrefix,
    OUString sLocalName,
    OUString sValue)
{
    if( XML_NAMESPACE_TEXT == nInPrefix )
    {
        if( IsXMLToken(sLocalName, XML_PREFIX) )
        {
            sPrefix = sValue;
        }
        else if( IsXMLToken(sLocalName, XML_SUFFIX) )
        {
            sSuffix = sValue;
        }
        else if( IsXMLToken(sLocalName, XML_NUMBERED_ENTRIES) )
        {
            sal_Bool bTmp;
            if( SvXMLUnitConverter::convertBool(bTmp, sValue) )
            {
                bNumberedEntries = bTmp;
            }
        }
        else if( IsXMLToken(sLocalName, XML_SORT_BY_POSITION) )
        {
            sal_Bool bTmp;
            if (SvXMLUnitConverter::convertBool(bTmp, sValue))
            {
                bSortByPosition = bTmp;
            }
        }
        else if( IsXMLToken(sLocalName, XML_SORT_ALGORITHM) )
        {
            sAlgorithm = sValue;
        }
    }
    else if( XML_NAMESPACE_FO == nInPrefix )
    {
        if( IsXMLToken(sLocalName, XML_LANGUAGE) )
        {
            aLocale.Language = sValue;
        }
        else if( IsXMLToken(sLocalName, XML_COUNTRY) )
        {
            aLocale.Country = sValue;
        }
    }
}


SvXMLImportContext *XMLIndexBibliographyConfigurationContext::CreateChildContext(
    sal_uInt16 nInPrefix,
    const OUString& rLocalName,
    const Reference<XAttributeList> & xAttrList )
{
    OUString sKey;
    sal_Bool bSort(sal_True);

    // process children here and use default context!
    if ( ( nInPrefix == XML_NAMESPACE_TEXT ) &&
         IsXMLToken( rLocalName, XML_SORT_KEY ) )
    {
        sal_Int16 nLength = xAttrList->getLength();
        for(sal_Int16 nAttr = 0; nAttr < nLength; nAttr++)
        {
            OUString sLocalName;
            sal_uInt16 nPrfx = GetImport().GetNamespaceMap().
                GetKeyByAttrName( xAttrList->getNameByIndex(nAttr),
                                  &sLocalName );

            if (nPrfx == XML_NAMESPACE_TEXT)
            {
                if ( IsXMLToken( sLocalName, XML_KEY ) )
                {
                    sKey = xAttrList->getValueByIndex(nAttr);
                }
                else if ( IsXMLToken( sLocalName, XML_SORT_ASCENDING ) )
                {
                    sal_Bool bTmp;
                    if (SvXMLUnitConverter::convertBool(
                        bTmp, xAttrList->getValueByIndex(nAttr)))
                    {
                        bSort = bTmp;
                    }
                }
            }
        }

        // valid data?
        sal_uInt16 nKey;
        if (SvXMLUnitConverter::convertEnum(nKey, sKey,
                                            aBibliographyDataFieldMap))
        {

            Any aAny;
            Sequence<PropertyValue> aKey(2);

            PropertyValue aNameValue;
            aNameValue.Name = sSortKey;
            aAny <<= (sal_Int16)nKey;
            aNameValue.Value = aAny;
            aKey[0] = aNameValue;

            PropertyValue aSortValue;
            aSortValue.Name = sIsSortAscending;
            aAny.setValue(&bSort, ::getBooleanCppuType());
            aSortValue.Value = aAny;
            aKey[1] = aSortValue;

            aSortKeys.push_back(aKey);
        }
    }

    return SvXMLImportContext::CreateChildContext(nInPrefix, rLocalName,
                                                  xAttrList);
}

void XMLIndexBibliographyConfigurationContext::CreateAndInsert(
    sal_Bool /*bOverwrite*/)
{
    // (code almost the same as export...)

    // insert and block mode is handled in insertStyleFamily

    // first: get field master
    // (we'll create one, and get the only master for this type)
    Reference<XMultiServiceFactory> xFactory(GetImport().GetModel(),UNO_QUERY);
    if( xFactory.is() )
    {
        Sequence<rtl::OUString> aServices = xFactory->getAvailableServiceNames();
        sal_Bool bFound(sal_False);
        sal_Int32 i(0);
        sal_Int32 nServiceCount(aServices.getLength());
        while (i < nServiceCount && !bFound)
        {
            if (aServices[i].equals(sFieldMaster_Bibliography))
            // here we should use a method which compares in reverse order if available
            // #85282#
                bFound = sal_True;
            else
                i++;
        }
        if (bFound)
        {
            Reference<XInterface> xIfc =
                xFactory->createInstance(sFieldMaster_Bibliography);
            if( xIfc.is() )
            {
                Reference<XPropertySet> xPropSet( xIfc, UNO_QUERY );
                Any aAny;

                aAny <<= sSuffix;
                xPropSet->setPropertyValue(sBracketAfter, aAny);

                aAny <<= sPrefix;
                xPropSet->setPropertyValue(sBracketBefore, aAny);

                aAny.setValue(&bNumberedEntries, ::getBooleanCppuType());
                xPropSet->setPropertyValue(sIsNumberEntries, aAny);

                aAny.setValue(&bSortByPosition, ::getBooleanCppuType());
                xPropSet->setPropertyValue(sIsSortByPosition, aAny);

                if( (aLocale.Language.getLength() > 0) &&
                    (aLocale.Country.getLength() > 0)     )
                {
                    aAny <<= aLocale;
                    xPropSet->setPropertyValue(sLocale, aAny);
                }

                if( sAlgorithm.getLength() > 0 )
                {
                    aAny <<= sAlgorithm;
                    xPropSet->setPropertyValue(sSortAlgorithm, aAny);
                }

                sal_Int32 nCount = aSortKeys.size();
                Sequence<Sequence<PropertyValue> > aKeysSeq(nCount);
                for(i = 0; i < nCount; i++)
                {
                    aKeysSeq[i] = aSortKeys[i];
                }
                aAny <<= aKeysSeq;
                xPropSet->setPropertyValue(sSortKeys, aAny);
            }
            // else: can't get FieldMaster -> ignore
        }
    }
    // else: can't even get Factory -> ignore
}
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
