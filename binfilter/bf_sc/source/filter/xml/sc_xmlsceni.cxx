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


#include "document.hxx"
#include "xmlimprt.hxx"
#include "xmlsceni.hxx"
#include "attrib.hxx"

#include "XMLConverter.hxx"

#include <bf_xmloff/nmspmap.hxx>
#include <bf_xmloff/xmluconv.hxx>
namespace binfilter {

using namespace ::com::sun::star;
using namespace xmloff::token;

using rtl::OUString;

//------------------------------------------------------------------

ScXMLTableScenarioContext::ScXMLTableScenarioContext(
        ScXMLImport& rInImport,
        USHORT nPrfx,
        const OUString& rLName,
        const uno::Reference< xml::sax::XAttributeList >& xAttrList ):
    SvXMLImportContext( rInImport, nPrfx, rLName ),
    aBorderColor( COL_BLACK ),
    bDisplayBorder( sal_True ),
    bCopyBack( sal_True ),
    bCopyStyles( sal_True ),
    bCopyFormulas( sal_True ),
    bIsActive( sal_False )
{
    rInImport.LockSolarMutex();
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    const SvXMLTokenMap& rAttrTokenMap = GetScImport().GetTableScenarioAttrTokenMap();
    for( sal_Int16 i = 0; i < nAttrCount; i++ )
    {
        OUString sAttrName = xAttrList->getNameByIndex( i );
        OUString aLclLocalName;
        USHORT nLclPrefix = GetScImport().GetNamespaceMap().GetKeyByAttrName(
                                            sAttrName, &aLclLocalName );
        OUString sValue = xAttrList->getValueByIndex( i );

        switch( rAttrTokenMap.Get( nLclPrefix, aLclLocalName ) )
        {
            case XML_TOK_TABLE_SCENARIO_ATTR_DISPLAY_BORDER:
            {
                bDisplayBorder = IsXMLToken(sValue, XML_TRUE);
            }
            break;
            case XML_TOK_TABLE_SCENARIO_ATTR_BORDER_COLOR:
            {
                SvXMLUnitConverter::convertColor(aBorderColor, sValue);
            }
            break;
            case XML_TOK_TABLE_SCENARIO_ATTR_COPY_BACK:
            {
                bCopyBack = IsXMLToken(sValue, XML_TRUE);
            }
            break;
            case XML_TOK_TABLE_SCENARIO_ATTR_COPY_STYLES:
            {
                bCopyStyles = IsXMLToken(sValue, XML_TRUE);
            }
            break;
            case XML_TOK_TABLE_SCENARIO_ATTR_COPY_FORMULAS:
            {
                bCopyFormulas = IsXMLToken(sValue, XML_TRUE);
            }
            break;
            case XML_TOK_TABLE_SCENARIO_ATTR_IS_ACTIVE:
            {
                bIsActive = IsXMLToken(sValue, XML_TRUE);
            }
            break;
            case XML_TOK_TABLE_SCENARIO_ATTR_SCENARIO_RANGES:
            {
                ScXMLConverter::GetRangeListFromString(
                    aScenarioRanges, sValue, GetScImport().GetDocument() );
            }
            break;
            case XML_TOK_TABLE_SCENARIO_ATTR_COMMENT:
            {
                sComment = sValue;
            }
            break;
        }
    }
}

ScXMLTableScenarioContext::~ScXMLTableScenarioContext()
{
    GetScImport().UnlockSolarMutex();
}

SvXMLImportContext *ScXMLTableScenarioContext::CreateChildContext(
        USHORT nInPrefix,
        const OUString& rLName,
        const uno::Reference< xml::sax::XAttributeList >& /*xAttrList*/ )
{
    return new SvXMLImportContext( GetImport(), nInPrefix, rLName );
}

void ScXMLTableScenarioContext::EndElement()
{
    sal_Int16   nCurrTable( GetScImport().GetTables().GetCurrentSheet() );
    ScDocument* pDoc = GetScImport().GetDocument();
    if (pDoc)
    {
        pDoc->SetScenario( nCurrTable, TRUE );
        USHORT nFlags( 0 );
        if( bDisplayBorder )
            nFlags |= SC_SCENARIO_SHOWFRAME;
        if( bCopyBack )
            nFlags |= SC_SCENARIO_TWOWAY;
        if( bCopyStyles )
            nFlags |= SC_SCENARIO_ATTRIB;
        if( !bCopyFormulas )
            nFlags |= SC_SCENARIO_VALUE;
        pDoc->SetScenarioData( nCurrTable, String( sComment ), aBorderColor, nFlags );
        for( sal_Int32 i = 0; i < static_cast<sal_Int32>(aScenarioRanges.Count()); i++ )
        {
            ScRange* pRange = aScenarioRanges.GetObject( i );
            if( pRange )
                pDoc->ApplyFlagsTab( pRange->aStart.Col(), pRange->aStart.Row(),
                    pRange->aEnd.Col(), pRange->aEnd.Row(), nCurrTable, SC_MF_SCENARIO );
        }
        pDoc->SetActiveScenario( nCurrTable, bIsActive );
    }
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
