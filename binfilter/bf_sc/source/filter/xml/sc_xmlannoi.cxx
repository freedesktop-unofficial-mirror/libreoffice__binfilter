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


#include "xmlannoi.hxx"
#include "xmlimprt.hxx"
#include "xmlcelli.hxx"
#include "xmlconti.hxx"

#include <bf_xmloff/nmspmap.hxx>
#include <bf_xmloff/xmlnmspe.hxx>
namespace binfilter {

using namespace ::com::sun::star;
using namespace xmloff::token;

//------------------------------------------------------------------

ScXMLAnnotationContext::ScXMLAnnotationContext( ScXMLImport& rInImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const uno::Reference<xml::sax::XAttributeList>& xAttrList,
                                      ScXMLTableRowCellContext* pTempCellContext) :
    SvXMLImportContext( rInImport, nPrfx, rLName ),
    nParagraphCount(0),
    bDisplay(sal_False),
    bHasTextP(sal_False)
{
    pCellContext = pTempCellContext;
    sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    const SvXMLTokenMap& rAttrTokenMap = GetScImport().GetTableAnnotationAttrTokenMap();
    for( sal_Int16 i=0; i < nAttrCount; i++ )
    {
        ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
        ::rtl::OUString aLclLocalName;
        USHORT nLclPrefix = GetScImport().GetNamespaceMap().GetKeyByAttrName(
                                            sAttrName, &aLclLocalName );
        ::rtl::OUString sValue = xAttrList->getValueByIndex( i );

        switch( rAttrTokenMap.Get( nLclPrefix, aLclLocalName ) )
        {
            case XML_TOK_TABLE_ANNOTATION_ATTR_AUTHOR:
            {
                sAuthor = sValue;
            }
            break;
            case XML_TOK_TABLE_ANNOTATION_ATTR_CREATE_DATE:
            {
                sCreateDate = sValue;
            }
            break;
            case XML_TOK_TABLE_ANNOTATION_ATTR_CREATE_DATE_STRING:
            {
                if (!sCreateDate.getLength())
                    sCreateDate = sValue;
            }
            break;
            case XML_TOK_TABLE_ANNOTATION_ATTR_DISPLAY:
            {
                bDisplay = IsXMLToken(sValue, XML_TRUE);
            }
            break;
        }
    }
}

ScXMLAnnotationContext::~ScXMLAnnotationContext()
{
}

SvXMLImportContext *ScXMLAnnotationContext::CreateChildContext( USHORT nInPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = 0;

    if ((nInPrefix == XML_NAMESPACE_TEXT) && IsXMLToken(rLName, XML_P) )
    {
        if (!bHasTextP)
        {
            bHasTextP = sal_True;
            sOUText.setLength(0);
        }
        if(nParagraphCount)
            sOUText.append(static_cast<sal_Unicode>('\n'));
        nParagraphCount++;
        pContext = new ScXMLContentContext( GetScImport(), nInPrefix, rLName, xAttrList, sOUText);
    }

    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nInPrefix, rLName );

    return pContext;
}

void ScXMLAnnotationContext::Characters( const ::rtl::OUString& rChars )
{
    if (!bHasTextP)
        sOUText.append(rChars);
}

void ScXMLAnnotationContext::EndElement()
{
    ScMyImportAnnotation* pMyAnnotation = new ScMyImportAnnotation();
    pMyAnnotation->sAuthor = sAuthor;
    pMyAnnotation->sCreateDate = sCreateDate;
    pMyAnnotation->sText = sOUText.makeStringAndClear();
    pMyAnnotation->bDisplay = bDisplay;
    pCellContext->AddAnnotation(pMyAnnotation);
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
