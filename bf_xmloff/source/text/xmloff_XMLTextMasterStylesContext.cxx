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

#include "xmlimp.hxx"
#include "xmlnmspe.hxx"

#include "XMLTextMasterPageContext.hxx"
#include "XMLTextMasterStylesContext.hxx"
namespace binfilter {

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::xml::sax;

using rtl::OUString;

using ::binfilter::xmloff::token::IsXMLToken;
using ::binfilter::xmloff::token::XML_MASTER_PAGE;

// ------------------------------------------------------------------------

TYPEINIT1( XMLTextMasterStylesContext, SvXMLStylesContext );

sal_Bool XMLTextMasterStylesContext::InsertStyleFamily( sal_uInt16 ) const
{
    return sal_True;
}

XMLTextMasterStylesContext::XMLTextMasterStylesContext(
        SvXMLImport& rInImport,
        sal_uInt16 nPrfx, const OUString& rLName,
        const Reference< XAttributeList > & xAttrList ) :
    SvXMLStylesContext( rInImport, nPrfx, rLName, xAttrList )
{
}

XMLTextMasterStylesContext::~XMLTextMasterStylesContext()
{
}

SvXMLStyleContext *XMLTextMasterStylesContext::CreateStyleChildContext(
        sal_uInt16 nInPrefix,
        const OUString& rLocalName,
        const Reference< XAttributeList > & xAttrList )
{
    SvXMLStyleContext *pContext = 0;

    if( XML_NAMESPACE_STYLE == nInPrefix &&
        IsXMLToken( rLocalName, XML_MASTER_PAGE ) &&
         InsertStyleFamily( XML_STYLE_FAMILY_MASTER_PAGE ) )
        pContext = new XMLTextMasterPageContext(
                        GetImport(), nInPrefix, rLocalName,
                          xAttrList,
                        !GetImport().GetTextImport()->IsInsertMode() );

    // any other style will be ignored here!

    return pContext;
}

SvXMLStyleContext *XMLTextMasterStylesContext::CreateStyleStyleChildContext(
        sal_uInt16 /*nFamily*/,
        sal_uInt16 /*nInPrefix*/,
        const OUString& /*rLocalName*/,
        const Reference< XAttributeList > & /*xAttrList*/ )
{
    return 0;
}
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
