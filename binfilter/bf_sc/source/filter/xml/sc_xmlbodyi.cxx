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



#include "xmlbodyi.hxx"
#include "xmltabi.hxx"
#include "xmlnexpi.hxx"
#include "xmldrani.hxx"
#include "xmldpimp.hxx"
#include "xmlcvali.hxx"
#include "xmlstyli.hxx"

#include "xmllabri.hxx"
#include "XMLConsolidationContext.hxx"
#include "XMLDDELinksContext.hxx"
#include "XMLCalculationSettingsContext.hxx"
#include "XMLTrackedChangesContext.hxx"
#include "XMLEmptyContext.hxx"
#include "scerrors.hxx"

#include <bf_xmloff/xmlnmspe.hxx>
#include <bf_xmloff/nmspmap.hxx>
#include <bf_xmloff/xmluconv.hxx>

#include <com/sun/star/sheet/XSpreadsheetDocument.hpp>

#include <sal/types.h>

#include <sax/tools/converter.hxx>

namespace binfilter {

using namespace ::com::sun::star;
using namespace ::binfilter::xmloff::token;

//------------------------------------------------------------------

ScXMLBodyContext::ScXMLBodyContext( ScXMLImport& rInImport,
                                              USHORT nPrfx,
                                                   const ::rtl::OUString& rLName,
                                              const uno::Reference<xml::sax::XAttributeList>& xAttrList ) :
    SvXMLImportContext( rInImport, nPrfx, rLName ),
    sPassword(),
    bProtected(sal_False),
    pChangeTrackingImportHelper(NULL)
{
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
        ::rtl::OUString aLclLocalName;
        USHORT nLclPrefix = GetScImport().GetNamespaceMap().GetKeyByAttrName(
                                            sAttrName, &aLclLocalName );
        ::rtl::OUString sValue = xAttrList->getValueByIndex( i );

        if (nLclPrefix == XML_NAMESPACE_TABLE)
        {
            if (IsXMLToken(aLclLocalName, XML_STRUCTURE_PROTECTED))
                bProtected = IsXMLToken(sValue, XML_TRUE);
            else if (IsXMLToken(aLclLocalName, XML_PROTECTION_KEY))
                sPassword = sValue;
        }
    }
}

ScXMLBodyContext::~ScXMLBodyContext()
{
}

SvXMLImportContext *ScXMLBodyContext::CreateChildContext( USHORT nInPrefix,
                                     const ::rtl::OUString& rLocalName,
                                     const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = 0;

    const SvXMLTokenMap& rTokenMap = GetScImport().GetBodyElemTokenMap();
    switch( rTokenMap.Get( nInPrefix, rLocalName ) )
    {
    case XML_TOK_BODY_TRACKED_CHANGES :
    {
        pChangeTrackingImportHelper = GetScImport().GetChangeTrackingImportHelper();
        if (pChangeTrackingImportHelper)
            pContext = new ScXMLTrackedChangesContext( GetScImport(), nInPrefix, rLocalName, xAttrList, pChangeTrackingImportHelper);
    }
    break;
    case XML_TOK_BODY_CALCULATION_SETTINGS :
        pContext = new ScXMLCalculationSettingsContext( GetScImport(), nInPrefix, rLocalName, xAttrList );
        break;
    case XML_TOK_BODY_CONTENT_VALIDATIONS :
        pContext = new ScXMLContentValidationsContext( GetScImport(), nInPrefix, rLocalName, xAttrList );
        break;
    case XML_TOK_BODY_LABEL_RANGES:
        pContext = new ScXMLLabelRangesContext( GetScImport(), nInPrefix, rLocalName, xAttrList );
        break;
    case XML_TOK_BODY_TABLE:
        {
            if (GetScImport().GetTables().GetCurrentSheet() >= MAXTAB)
            {
                GetScImport().SetRangeOverflowType(SCWARN_IMPORT_SHEET_OVERFLOW);
                pContext = new ScXMLEmptyContext(GetScImport(), nInPrefix, rLocalName);
            }
            else
            {
                pContext = new ScXMLTableContext( GetScImport(),nInPrefix, rLocalName,
                                                  xAttrList );
            }
        }
        break;
    case XML_TOK_BODY_NAMED_EXPRESSIONS:
        pContext = new ScXMLNamedExpressionsContext ( GetScImport(), nInPrefix, rLocalName,
                                                        xAttrList );
        break;
    case XML_TOK_BODY_DATABASE_RANGES:
        pContext = new ScXMLDatabaseRangesContext ( GetScImport(), nInPrefix, rLocalName,
                                                        xAttrList );
        break;
    case XML_TOK_BODY_DATABASE_RANGE:
        pContext = new ScXMLDatabaseRangeContext ( GetScImport(), nInPrefix, rLocalName,
                                                        xAttrList );
        break;
    case XML_TOK_BODY_DATA_PILOT_TABLES:
        pContext = new ScXMLDataPilotTablesContext ( GetScImport(), nInPrefix, rLocalName,
                                                        xAttrList );
        break;
    case XML_TOK_BODY_CONSOLIDATION:
        pContext = new ScXMLConsolidationContext ( GetScImport(), nInPrefix, rLocalName,
                                                        xAttrList );
        break;
    case XML_TOK_BODY_DDE_LINKS:
        pContext = new ScXMLDDELinksContext ( GetScImport(), nInPrefix, rLocalName,
                                                        xAttrList );
        break;
    }

    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nInPrefix, rLocalName );

    return pContext;
}

void ScXMLBodyContext::EndElement()
{
    GetScImport().LockSolarMutex();
    ScMyImpDetectiveOpArray*    pDetOpArray = GetScImport().GetDetectiveOpArray();
    ScDocument*                 pDoc        = GetScImport().GetDocument();
    ScMyImpDetectiveOp          aDetOp;

    if (pDoc && GetScImport().GetModel().is())
    {
        if (pDetOpArray)
        {
            pDetOpArray->Sort();
            while( pDetOpArray->GetFirstOp( aDetOp ) )
            {
                ScDetOpData aOpData( aDetOp.aPosition, aDetOp.eOpType );
                pDoc->AddDetectiveOperation( aOpData );
            }
        }

        if (pChangeTrackingImportHelper)
            pChangeTrackingImportHelper->CreateChangeTrack(GetScImport().GetDocument());

        if (bProtected)
        {
            uno::Sequence<sal_Int8> aPass;
            if (sPassword.getLength())
                ::sax::Converter::decodeBase64(aPass, sPassword);
            pDoc->SetDocProtection(bProtected, aPass);
        }
        uno::Reference <sheet::XSpreadsheetDocument> xSpreadDoc( GetScImport().GetModel(), uno::UNO_QUERY );
        if ( xSpreadDoc.is() )
        {
            uno::Reference<sheet::XSpreadsheets> xSheets = xSpreadDoc->getSheets();
            uno::Reference <container::XIndexAccess> xIndex( xSheets, uno::UNO_QUERY );
            if ( xIndex.is() )
            {
                uno::Any aSheet = xIndex->getByIndex(0);
                uno::Reference< sheet::XSpreadsheet > xSheet;
                if ( aSheet >>= xSheet )
                {
                    uno::Reference <beans::XPropertySet> xProperties(xSheet, uno::UNO_QUERY);
                    if (xProperties.is())
                    {
                        XMLTableStylesContext *pStyles = (XMLTableStylesContext *)GetScImport().GetAutoStyles();
                        ::rtl::OUString sTableStyleName(GetScImport().GetFirstTableStyle());
                        if (sTableStyleName.getLength())
                        {
                            XMLTableStyleContext* pStyle = (XMLTableStyleContext *)pStyles->FindStyleChildContext(
                                XML_STYLE_FAMILY_TABLE_TABLE, sTableStyleName, sal_True);
                            if (pStyle)
                                pStyle->FillPropertySet(xProperties);
                        }
                    }
                }
            }
        }
    }
    GetScImport().UnlockSolarMutex();
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
