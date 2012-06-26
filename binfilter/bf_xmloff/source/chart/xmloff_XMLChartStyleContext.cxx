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
#include "XMLChartStyleContext.hxx"

#include "xmlnmspe.hxx"
#include "xmlnumfi.hxx"
#include "families.hxx"

#include "XMLChartPropertyContext.hxx"
namespace binfilter {

using namespace ::com::sun::star;
using ::binfilter::xmloff::token::IsXMLToken;
using ::binfilter::xmloff::token::XML_DATA_STYLE_NAME;


TYPEINIT1( XMLChartStyleContext, XMLPropStyleContext );

// protected

void XMLChartStyleContext::SetAttribute(
    sal_uInt16 nPrefixKey,
    const ::rtl::OUString& rLocalName,
    const ::rtl::OUString& rValue )
{
    if( IsXMLToken( rLocalName, XML_DATA_STYLE_NAME ) )
    {
        msDataStyleName = rValue;
    }
    else
    {
        XMLPropStyleContext::SetAttribute( nPrefixKey, rLocalName, rValue );
    }
}

//public

// CTOR
XMLChartStyleContext::XMLChartStyleContext(
    SvXMLImport& rInImport, sal_uInt16 nPrfx,
    const ::rtl::OUString& rLName,
    const uno::Reference< xml::sax::XAttributeList > & xAttrList,
    SvXMLStylesContext& rStyles, sal_uInt16 nInFamily ) :

        XMLPropStyleContext( rInImport, nPrfx, rLName, xAttrList, rStyles, nInFamily ),
        mrStyles( rStyles )
{}

// DTOR
XMLChartStyleContext::~XMLChartStyleContext()
{}

void XMLChartStyleContext::FillPropertySet(
    const uno::Reference< beans::XPropertySet > & rPropSet )
{
    XMLPropStyleContext::FillPropertySet( rPropSet );
    if( msDataStyleName.getLength())
    {
        SvXMLNumFormatContext* pStyle = (SvXMLNumFormatContext *)mrStyles.FindStyleChildContext(
            XML_STYLE_FAMILY_DATA_STYLE, msDataStyleName, sal_True );
        if( pStyle )
        {
            uno::Any aNumberFormat;
            sal_Int32 nNumberFormat = pStyle->GetKey();
            aNumberFormat <<= nNumberFormat;
            rPropSet->setPropertyValue( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "NumberFormat" )),
                                        aNumberFormat );
        }
    }
}

SvXMLImportContext *XMLChartStyleContext::CreateChildContext(
    sal_uInt16 nInPrefix,
    const ::rtl::OUString& rLocalName,
    const uno::Reference< xml::sax::XAttributeList > & xAttrList )
{
    SvXMLImportContext* pContext = NULL;

    if( XML_NAMESPACE_STYLE == nInPrefix &&
        IsXMLToken( rLocalName, ::binfilter::xmloff::token::XML_PROPERTIES ) )
    {
        UniReference < SvXMLImportPropertyMapper > xImpPrMap =
            GetStyles()->GetImportPropertyMapper( GetFamily() );
        if( xImpPrMap.is() )
            pContext = new XMLChartPropertyContext(
                GetImport(), nInPrefix, rLocalName, xAttrList,
                GetProperties(), xImpPrMap );
    }

    if( !pContext )
        pContext = XMLPropStyleContext::CreateChildContext( nInPrefix, rLocalName,
                                                          xAttrList );

    return pContext;
}
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
