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

#include "XMLChangeElementImportContext.hxx"

#include "XMLChangedRegionImportContext.hxx"

#include "XMLChangeInfoContext.hxx"

#include <com/sun/star/uno/Reference.h>

#include "xmlimp.hxx"

#include "xmlnmspe.hxx"

namespace binfilter {



using ::rtl::OUString;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::xml::sax::XAttributeList;
using ::binfilter::xmloff::token::IsXMLToken;
using ::binfilter::xmloff::token::XML_P;
using ::binfilter::xmloff::token::XML_CHANGE_INFO;

TYPEINIT1( XMLChangeElementImportContext, SvXMLImportContext );

XMLChangeElementImportContext::XMLChangeElementImportContext(
    SvXMLImport& rInImport,
    sal_uInt16 nInPrefix,
    const OUString& rLocalName,
    sal_Bool bAccContent,
    XMLChangedRegionImportContext& rParent) :
        SvXMLImportContext(rInImport, nInPrefix, rLocalName),
        bAcceptContent(bAccContent),
        rChangedRegion(rParent)
{
}

SvXMLImportContext* XMLChangeElementImportContext::CreateChildContext(
    sal_uInt16 nInPrefix,
    const OUString& rLocalName,
    const Reference<XAttributeList> & xAttrList)
{
    SvXMLImportContext* pContext = NULL;

    if ( (XML_NAMESPACE_OFFICE == nInPrefix) &&
         IsXMLToken( rLocalName, XML_CHANGE_INFO) )
    {
        pContext = new XMLChangeInfoContext(GetImport(), nInPrefix, rLocalName,
                                            rChangedRegion, GetLocalName());
    }
    else
    {
        // import into redline -> create XText
        rChangedRegion.UseRedlineText();

        pContext = GetImport().GetTextImport()->CreateTextChildContext(
            GetImport(), nInPrefix, rLocalName, xAttrList,
            XML_TEXT_TYPE_CHANGED_REGION);

        if (NULL == pContext)
        {
            // no text element -> use default
            pContext = SvXMLImportContext::CreateChildContext(
                nInPrefix, rLocalName, xAttrList);

            // illegal element content! TODO: discard this redline!
        }
    }


    return pContext;
}

// #107848#
void XMLChangeElementImportContext::StartElement( const Reference< XAttributeList >& /*xAttrList*/ )
{
    if(bAcceptContent)
    {
        GetImport().GetTextImport()->SetInsideDeleteContext(sal_True);
    }
}

// #107848#
void XMLChangeElementImportContext::EndElement()
{
    if(bAcceptContent)
    {
        GetImport().GetTextImport()->SetInsideDeleteContext(sal_False);
    }
}
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
