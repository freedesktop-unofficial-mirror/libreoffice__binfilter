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
#include "XMLChartPropertyContext.hxx"
#include "PropertyMap.hxx"

#include "XMLSymbolImageContext.hxx"
namespace binfilter {

TYPEINIT1( XMLChartPropertyContext, SvXMLImportContext );

using namespace ::com::sun::star;

XMLChartPropertyContext::XMLChartPropertyContext(
    SvXMLImport& rInImport,
    sal_uInt16 nPrfx,
    const ::rtl::OUString& rLName,
    const uno::Reference< xml::sax::XAttributeList > & xAttrList,
    ::std::vector< XMLPropertyState >& rProps,
    const UniReference< SvXMLImportPropertyMapper >& rMapper ) :
        SvXMLPropertySetContext( rInImport, nPrfx, rLName, xAttrList, rProps, rMapper )
{
}

XMLChartPropertyContext::~XMLChartPropertyContext()
{}

SvXMLImportContext* XMLChartPropertyContext::CreateChildContext(
    sal_uInt16 nInPrefix,
    const ::rtl::OUString& rLocalName,
    const uno::Reference< xml::sax::XAttributeList > & xAttrList,
    ::std::vector< XMLPropertyState > &rInProperties,
    const XMLPropertyState& rProp )
{
    SvXMLImportContext *pContext = 0;

    switch( xMapper->getPropertySetMapper()->GetEntryContextId( rProp.mnIndex ) )
    {
        case XML_SCH_CONTEXT_SPECIAL_SYMBOL_IMAGE:
            pContext = new XMLSymbolImageContext( GetImport(), nInPrefix, rLocalName, rProp, rInProperties );
            break;
    }

    // default / no context yet: create child context by base class
    if( !pContext )
    {
        pContext = SvXMLPropertySetContext::CreateChildContext(
            nInPrefix, rLocalName, xAttrList, rInProperties, rProp );
    }

    return pContext;
}
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
