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

#include <tools/debug.hxx>

#include "XMLShapeStyleContext.hxx"
#include "XMLShapePropertySetContext.hxx"

#include "contextid.hxx"

#include <com/sun/star/drawing/XControlShape.hpp>

#include "xmlimp.hxx"

#include "xmlnumi.hxx"

#include <xmlnmspe.hxx>



namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using ::binfilter::xmloff::token::IsXMLToken;
using ::binfilter::xmloff::token::XML_PROPERTIES;

using rtl::OUString;

//////////////////////////////////////////////////////////////////////////////

TYPEINIT1( XMLShapeStyleContext, XMLPropStyleContext );

XMLShapeStyleContext::XMLShapeStyleContext(
    SvXMLImport& rInImport,
    sal_uInt16 nPrfx,
    const OUString& rLName,
    const uno::Reference< xml::sax::XAttributeList >& xAttrList,
    SvXMLStylesContext& rStyles,
    sal_uInt16 nInFamily)
:   XMLPropStyleContext(rInImport, nPrfx, rLName, xAttrList, rStyles, nInFamily ),
    m_bIsNumRuleAlreadyConverted( sal_False )
{
}

XMLShapeStyleContext::~XMLShapeStyleContext()
{
}

void XMLShapeStyleContext::SetAttribute( sal_uInt16 nPrefixKey, const ::rtl::OUString& rLocalName, const ::rtl::OUString& rValue )
{
    if ((0 == m_sControlDataStyleName.getLength()) && (::binfilter::xmloff::token::GetXMLToken(::binfilter::xmloff::token::XML_DATA_STYLE_NAME) == rLocalName))
    {
        m_sControlDataStyleName = rValue;
    }
    else if( (XML_NAMESPACE_STYLE == nPrefixKey) && IsXMLToken( rLocalName, ::binfilter::xmloff::token::XML_LIST_STYLE_NAME ) )
    {
        m_sListStyleName = rValue;
    }
    else
    {
        XMLPropStyleContext::SetAttribute( nPrefixKey, rLocalName, rValue );
    }
}

SvXMLImportContext *XMLShapeStyleContext::CreateChildContext(
        sal_uInt16 nInPrefix,
        const OUString& rLocalName,
        const Reference< xml::sax::XAttributeList > & xAttrList )
{
    SvXMLImportContext *pContext = 0;

    if( XML_NAMESPACE_STYLE == nInPrefix &&
        IsXMLToken( rLocalName, XML_PROPERTIES ) )
    {
        UniReference < SvXMLImportPropertyMapper > xImpPrMap =
            GetStyles()->GetImportPropertyMapper( GetFamily() );
        if( xImpPrMap.is() )
            pContext = new XMLShapePropertySetContext( GetImport(), nInPrefix,
                                                    rLocalName, xAttrList,
                                                    GetProperties(),
                                                    xImpPrMap );
    }

    if( !pContext )
        pContext = XMLPropStyleContext::CreateChildContext( nInPrefix, rLocalName,
                                                          xAttrList );

    return pContext;
}

void XMLShapeStyleContext::FillPropertySet( const Reference< beans::XPropertySet > & rPropSet )
{
    if( !m_bIsNumRuleAlreadyConverted )
    {
        m_bIsNumRuleAlreadyConverted = sal_True;

        // for compatibility to beta files, search for CTF_SD_NUMBERINGRULES_NAME to
        // import numbering rules from the style:properties element
        const UniReference< XMLPropertySetMapper >&rMapper = GetStyles()->GetImportPropertyMapper( GetFamily() )->getPropertySetMapper();

        ::std::vector< XMLPropertyState > &rProperties = GetProperties();
        ::std::vector< XMLPropertyState >::iterator end( rProperties.end() );
        ::std::vector< XMLPropertyState >::iterator property;

        // first, look for the old format, where we had a text:list-style-name
        // attribute in the style:properties element
        for( property = rProperties.begin(); property != end; ++property )
        {
            // find properties with context
            if( rMapper->GetEntryContextId( property->mnIndex ) == CTF_SD_NUMBERINGRULES_NAME )
                break;
        }

        // if we did not find an old list-style-name in the properties, and we need one
        // because we got a style:list-style attribute in the style-style element
        // we generate one
        if( (property == end) && ( 0 != m_sListStyleName.getLength() ) )
        {
            sal_Int32 nIndex = rMapper->FindEntryIndex( CTF_SD_NUMBERINGRULES_NAME );
            DBG_ASSERT( -1 != nIndex, "can't find numbering rules property entry, can't set numbering rule!" );

            XMLPropertyState aNewState( nIndex );
            rProperties.push_back( aNewState );
            end = rProperties.end();
            property = end - 1;
        }

        // so, if we have an old or a new list style name, we set its value to
        // a numbering rule
        if( property != end )
        {
            if( 0 == m_sListStyleName.getLength() )
            {
                property->maValue >>= m_sListStyleName;
            }

            const SvxXMLListStyleContext *pListStyle = GetImport().GetTextImport()->FindAutoListStyle( m_sListStyleName );

            DBG_ASSERT( pListStyle, "list-style not found for shape style" );
            if( pListStyle )
            {
                uno::Reference< container::XIndexReplace > xNumRule( pListStyle->CreateNumRule( GetImport().GetModel() ) );
                pListStyle->FillUnoNumRule(xNumRule, NULL /* const SvI18NMap * ??? */ );
                property->maValue <<= xNumRule;
            }
            else
            {
                property->mnIndex = -1;
            }
        }
    }

    XMLPropStyleContext::FillPropertySet(rPropSet);

    if (m_sControlDataStyleName.getLength())
    {   // we had a data-style-name attribute

        // set the formatting on the control model of the control shape
        uno::Reference< drawing::XControlShape > xControlShape(rPropSet, uno::UNO_QUERY);
        DBG_ASSERT(xControlShape.is(), "XMLShapeStyleContext::FillPropertySet: data style for a non-control shape!");
        if (xControlShape.is())
        {
            uno::Reference< beans::XPropertySet > xControlModel(xControlShape->getControl(), uno::UNO_QUERY);
            DBG_ASSERT(xControlModel.is(), "XMLShapeStyleContext::FillPropertySet: no control model for the shape!");
            if (xControlModel.is())
            {
                GetImport().GetFormImport()->applyControlNumberStyle(xControlModel, m_sControlDataStyleName);
            }
        }
    }
}

void XMLShapeStyleContext::Finish( sal_Bool /*bOverwrite*/ )
{
}

}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
