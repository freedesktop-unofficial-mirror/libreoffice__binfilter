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

#ifdef _MSC_VER
#pragma hdrstop
#endif


#include "XMLCalculationSettingsContext.hxx"
#include "xmlimprt.hxx"
#include "unonames.hxx"
#include "docoptio.hxx"
#include "document.hxx"

#include <bf_xmloff/xmlnmspe.hxx>
#include <bf_xmloff/xmluconv.hxx>
#include <bf_xmloff/nmspmap.hxx>

#include <com/sun/star/sheet/XSpreadsheetDocument.hpp>
#include <comphelper/extract.hxx>
namespace binfilter {

using namespace ::com::sun::star;
using namespace xmloff::token;

//------------------------------------------------------------------

ScXMLCalculationSettingsContext::ScXMLCalculationSettingsContext( ScXMLImport& rInImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList) :
    SvXMLImportContext( rInImport, nPrfx, rLName ),
    fIterationEpsilon(0.001),
    nIterationCount(100),
    nYear2000(1930),
    bIsIterationEnabled(sal_False),
    bCalcAsShown(sal_False),
    bIgnoreCase(sal_False),
    bLookUpLabels(sal_True),
    bMatchWholeCell(sal_True),
    bUseRegularExpressions(sal_True)
{
    aNullDate.Day = 30;
    aNullDate.Month = 12;
    aNullDate.Year = 1899;
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
        ::rtl::OUString aLclLocalName;
        sal_uInt16 nLclPrefix = GetScImport().GetNamespaceMap().GetKeyByAttrName(
                                            sAttrName, &aLclLocalName );
        ::rtl::OUString sValue = xAttrList->getValueByIndex( i );

        if (nLclPrefix == XML_NAMESPACE_TABLE)
        {
            if (IsXMLToken(aLclLocalName, XML_CASE_SENSITIVE))
            {
                if (IsXMLToken(sValue, XML_FALSE))
                    bIgnoreCase = sal_True;
            }
            else if (IsXMLToken(aLclLocalName, XML_PRECISION_AS_SHOWN))
            {
                if (IsXMLToken(sValue, XML_TRUE))
                    bCalcAsShown = sal_True;
            }
            else if (IsXMLToken(aLclLocalName, XML_SEARCH_CRITERIA_MUST_APPLY_TO_WHOLE_CELL))
            {
                if (IsXMLToken(sValue, XML_FALSE))
                    bMatchWholeCell = sal_False;
            }
            else if (IsXMLToken(aLclLocalName, XML_AUTOMATIC_FIND_LABELS))
            {
                if (IsXMLToken(sValue, XML_FALSE))
                    bLookUpLabels = sal_False;
            }
            else if (IsXMLToken(aLclLocalName, XML_NULL_YEAR))
            {
                sal_Int32 nTemp;
                GetScImport().GetMM100UnitConverter().convertNumber(nTemp, sValue);
                nYear2000 = static_cast<sal_uInt16>(nTemp);
            }
            else if (IsXMLToken(aLclLocalName, XML_USE_REGULAR_EXPRESSIONS))
            {
                if (IsXMLToken(sValue, XML_FALSE))
                    bUseRegularExpressions = sal_False;
            }
        }
    }
}

ScXMLCalculationSettingsContext::~ScXMLCalculationSettingsContext()
{
}

SvXMLImportContext *ScXMLCalculationSettingsContext::CreateChildContext( USHORT nInPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = 0;

    if (nInPrefix == XML_NAMESPACE_TABLE)
    {
        if (IsXMLToken(rLName, XML_NULL_DATE))
            pContext = new ScXMLNullDateContext(GetScImport(), nInPrefix, rLName, xAttrList, this);
        else if (IsXMLToken(rLName, XML_ITERATION))
            pContext = new ScXMLIterationContext(GetScImport(), nInPrefix, rLName, xAttrList, this);
    }

    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nInPrefix, rLName );

    return pContext;
}

void ScXMLCalculationSettingsContext::EndElement()
{
    if (GetScImport().GetModel().is())
    {
        uno::Reference <sheet::XSpreadsheetDocument> xSpreadDoc (GetScImport().GetModel(), uno::UNO_QUERY);
        if (xSpreadDoc.is())
        {
            uno::Reference <beans::XPropertySet> xPropertySet (xSpreadDoc, uno::UNO_QUERY);
            if (xPropertySet.is())
            {
                uno::Any aAny = ::cppu::bool2any( bCalcAsShown );
                xPropertySet->setPropertyValue(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNO_CALCASSHOWN)), aAny );
                aAny = ::cppu::bool2any( bIgnoreCase );
                xPropertySet->setPropertyValue(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNO_IGNORECASE)), aAny );
                aAny = ::cppu::bool2any( bLookUpLabels );
                xPropertySet->setPropertyValue(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNO_LOOKUPLABELS)), aAny );
                aAny = ::cppu::bool2any( bMatchWholeCell );
                xPropertySet->setPropertyValue(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNO_MATCHWHOLE)), aAny );
                aAny = ::cppu::bool2any( bUseRegularExpressions );
                xPropertySet->setPropertyValue(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNO_REGEXENABLED)), aAny );
                aAny = ::cppu::bool2any( bIsIterationEnabled );
                xPropertySet->setPropertyValue(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNO_ITERENABLED)), aAny );
                aAny <<= nIterationCount;
                xPropertySet->setPropertyValue( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNO_ITERCOUNT)), aAny);
                aAny <<= fIterationEpsilon;
                xPropertySet->setPropertyValue( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNO_ITEREPSILON)), aAny);
                aAny <<= aNullDate;
                xPropertySet->setPropertyValue( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(SC_UNO_NULLDATE)), aAny);
                if (GetScImport().GetDocument())
                {
                    GetScImport().LockSolarMutex();
                    ScDocOptions aDocOptions (GetScImport().GetDocument()->GetDocOptions());
                    aDocOptions.SetYear2000(nYear2000);
                    GetScImport().GetDocument()->SetDocOptions(aDocOptions);
                    GetScImport().UnlockSolarMutex();
                }
            }
        }
    }
}

ScXMLNullDateContext::ScXMLNullDateContext( ScXMLImport& rInImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                      ScXMLCalculationSettingsContext* pCalcSet) :
    SvXMLImportContext( rInImport, nPrfx, rLName )
{
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
        ::rtl::OUString aLclLocalName;
        sal_uInt16 nLclPrefix = GetScImport().GetNamespaceMap().GetKeyByAttrName(
                                            sAttrName, &aLclLocalName );
        ::rtl::OUString sValue = xAttrList->getValueByIndex( i );

        if (nLclPrefix == XML_NAMESPACE_TABLE && IsXMLToken(aLclLocalName, XML_DATE_VALUE))
        {
            util::DateTime aDateTime;
            GetScImport().GetMM100UnitConverter().convertDateTime(aDateTime, sValue);
            util::Date aDate;
            aDate.Day = aDateTime.Day;
            aDate.Month = aDateTime.Month;
            aDate.Year = aDateTime.Year;
            pCalcSet->SetNullDate(aDate);
        }
    }
}

ScXMLNullDateContext::~ScXMLNullDateContext()
{
}

SvXMLImportContext *ScXMLNullDateContext::CreateChildContext( USHORT nInPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& /*xAttrList*/ )
{
    SvXMLImportContext *pContext = new SvXMLImportContext( GetImport(), nInPrefix, rLName );

    return pContext;
}

void ScXMLNullDateContext::EndElement()
{
}

ScXMLIterationContext::ScXMLIterationContext( ScXMLImport& rInImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
                                      ScXMLCalculationSettingsContext* pCalcSet) :
    SvXMLImportContext( rInImport, nPrfx, rLName )
{
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
        ::rtl::OUString aLclLocalName;
        sal_uInt16 nLclPrefix = GetScImport().GetNamespaceMap().GetKeyByAttrName(
                                            sAttrName, &aLclLocalName );
        ::rtl::OUString sValue = xAttrList->getValueByIndex( i );

        if (nLclPrefix == XML_NAMESPACE_TABLE)
        {
            if (IsXMLToken(aLclLocalName, XML_STATUS))
            {
                if (IsXMLToken(sValue, XML_ENABLE))
                    pCalcSet->SetIterationStatus(sal_True);
            }
            else if (IsXMLToken(aLclLocalName, XML_STEPS))
            {
                sal_Int32 nSteps;
                GetScImport().GetMM100UnitConverter().convertNumber(nSteps, sValue);
                pCalcSet->SetIterationCount(nSteps);
            }
            else if (IsXMLToken(aLclLocalName, XML_MAXIMUM_DIFFERENCE))
            {
                double fDif;
                GetScImport().GetMM100UnitConverter().convertDouble(fDif, sValue);
                pCalcSet->SetIterationEpsilon(fDif);
            }
        }
    }
}

ScXMLIterationContext::~ScXMLIterationContext()
{
}

SvXMLImportContext *ScXMLIterationContext::CreateChildContext( USHORT nInPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& /*xAttrList*/ )
{
    SvXMLImportContext *pContext = new SvXMLImportContext( GetImport(), nInPrefix, rLName );

    return pContext;
}

void ScXMLIterationContext::EndElement()
{
}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
