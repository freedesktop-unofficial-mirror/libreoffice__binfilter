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

//___________________________________________________________________

#include "xmllabri.hxx"

#include <bf_xmloff/nmspmap.hxx>

#include <com/sun/star/sheet/XLabelRanges.hpp>

#include "XMLConverter.hxx"
#include "unonames.hxx"
#include "xmlimprt.hxx"
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::rtl;
using namespace xmloff::token;


//___________________________________________________________________

ScXMLLabelRangesContext::ScXMLLabelRangesContext(
        ScXMLImport& rInImport,
        USHORT nInPrefix,
        const OUString& rLName,
        const uno::Reference< xml::sax::XAttributeList >& /*xAttrList*/ ):
    SvXMLImportContext( rInImport, nInPrefix, rLName )
{
    rInImport.LockSolarMutex();
}

ScXMLLabelRangesContext::~ScXMLLabelRangesContext()
{
    GetScImport().UnlockSolarMutex();
}

SvXMLImportContext* ScXMLLabelRangesContext::CreateChildContext(
        USHORT nInPrefix,
        const OUString& rLName,
        const uno::Reference< xml::sax::XAttributeList >& xAttrList )
{
    SvXMLImportContext*     pContext    = NULL;
    const SvXMLTokenMap&    rTokenMap   = GetScImport().GetLabelRangesElemTokenMap();

    switch( rTokenMap.Get( nInPrefix, rLName ) )
    {
        case XML_TOK_LABEL_RANGE_ELEM:
            pContext = new ScXMLLabelRangeContext( GetScImport(), nInPrefix, rLName, xAttrList );
        break;
    }
    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nInPrefix, rLName );

    return pContext;
}

void ScXMLLabelRangesContext::EndElement()
{
}


//___________________________________________________________________

ScXMLLabelRangeContext::ScXMLLabelRangeContext(
        ScXMLImport& rInImport,
        USHORT nPrfx,
        const OUString& rLName,
        const uno::Reference< xml::sax::XAttributeList >& xAttrList ) :
    SvXMLImportContext( rInImport, nPrfx, rLName ),
    bColumnOrientation( sal_False )
{
    sal_Int16               nAttrCount      = xAttrList.is() ? xAttrList->getLength() : 0;
    const SvXMLTokenMap&    rAttrTokenMap   = GetScImport().GetLabelRangeAttrTokenMap();

    for( sal_Int16 nIndex = 0; nIndex < nAttrCount; nIndex++ )
    {
        OUString    sAttrName   = xAttrList->getNameByIndex( nIndex );
        OUString    sValue      = xAttrList->getValueByIndex( nIndex );
        OUString    aLclLocalName;
        USHORT      nLclPrefix      = GetScImport().GetNamespaceMap().GetKeyByAttrName( sAttrName, &aLclLocalName );

        switch( rAttrTokenMap.Get( nLclPrefix, aLclLocalName ) )
        {
            case XML_TOK_LABEL_RANGE_ATTR_LABEL_RANGE:
                sLabelRangeStr = sValue;
            break;
            case XML_TOK_LABEL_RANGE_ATTR_DATA_RANGE:
                sDataRangeStr = sValue;
            break;
            case XML_TOK_LABEL_RANGE_ATTR_ORIENTATION:
                bColumnOrientation = IsXMLToken(sValue, XML_COLUMN );
            break;
        }
    }
}

ScXMLLabelRangeContext::~ScXMLLabelRangeContext()
{
}

SvXMLImportContext* ScXMLLabelRangeContext::CreateChildContext(
        USHORT nInPrefix,
        const OUString& rLName,
        const uno::Reference< xml::sax::XAttributeList >& /*xAttrList*/ )
{
    return new SvXMLImportContext( GetImport(), nInPrefix, rLName );
}

void ScXMLLabelRangeContext::EndElement()
{
    if (GetScImport().GetModel().is())
    {
        uno::Reference< beans::XPropertySet > xPropSet( GetScImport().GetModel(), uno::UNO_QUERY );
        if( xPropSet.is() )
        {
            uno::Any aAny = xPropSet->getPropertyValue( bColumnOrientation ?
                OUString( RTL_CONSTASCII_USTRINGPARAM( SC_UNO_COLLABELRNG ) ) :
                OUString( RTL_CONSTASCII_USTRINGPARAM( SC_UNO_ROWLABELRNG ) ) );
            uno::Reference< sheet::XLabelRanges > xLabelRanges;
            if( aAny >>= xLabelRanges )
            {
                table::CellRangeAddress aLabelRange;
                table::CellRangeAddress aDataRange;
                sal_Int32 nOffset1(0);
                sal_Int32 nOffset2(0);
                if (ScXMLConverter::GetRangeFromString( aLabelRange, sLabelRangeStr, GetScImport().GetDocument(), nOffset1 ) &&
                    ScXMLConverter::GetRangeFromString( aDataRange, sDataRangeStr, GetScImport().GetDocument(), nOffset2 ))
                    xLabelRanges->addNew( aLabelRange, aDataRange );
            }
        }
    }
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
