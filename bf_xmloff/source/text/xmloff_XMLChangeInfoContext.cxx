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

#include "XMLChangeInfoContext.hxx"

#include "XMLChangedRegionImportContext.hxx"

#include "XMLStringBufferImportContext.hxx"

#include <com/sun/star/uno/Reference.h>

#include "xmlnmspe.hxx"

#include "nmspmap.hxx"


#include "xmlimp.hxx"
namespace binfilter {



using namespace ::binfilter::xmloff::token;

using ::rtl::OUString;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::xml::sax::XAttributeList;


TYPEINIT1(XMLChangeInfoContext, SvXMLImportContext);

XMLChangeInfoContext::XMLChangeInfoContext(
    SvXMLImport& rInImport,
    sal_uInt16 nInPrefix,
    const OUString& rLocalName,
    XMLChangedRegionImportContext& rPParent,
    const OUString& rChangeType) :
        SvXMLImportContext(rInImport, nInPrefix, rLocalName),
        rType(rChangeType),
        rChangedRegion(rPParent)
{
}

XMLChangeInfoContext::~XMLChangeInfoContext()
{
}

void XMLChangeInfoContext::StartElement(
    const Reference<XAttributeList> & xAttrList)
{
    // process attributes: chg-author, chg-date-time
    sal_Int16 nLength = xAttrList->getLength();
    for(sal_Int16 nAttr = 0; nAttr < nLength; nAttr++)
    {
        OUString sLocalName;
        sal_uInt16 nLclPrefix = GetImport().GetNamespaceMap().
            GetKeyByAttrName( xAttrList->getNameByIndex(nAttr),
                              &sLocalName );
        OUString sValue = xAttrList->getValueByIndex(nAttr);
        if (XML_NAMESPACE_OFFICE == nLclPrefix)
        {
            if ( IsXMLToken( sLocalName, XML_CHG_AUTHOR ) )
            {
                sAuthor = sValue;
            }
            else if ( IsXMLToken( sLocalName, XML_CHG_DATE_TIME ) )
            {
                sDateTime = sValue;
            }
            // else: unknown attribute
        }
        // else: unknown namespace
    }

}

SvXMLImportContext* XMLChangeInfoContext::CreateChildContext(
    USHORT nInPrefix,
    const OUString& rLocalName,
    const Reference<XAttributeList >& xAttrList )
{
    SvXMLImportContext* pContext = NULL;

    if ( ( XML_NAMESPACE_TEXT == nInPrefix ) &&
         IsXMLToken( rLocalName, XML_P )       )
    {
        pContext = new XMLStringBufferImportContext(GetImport(), nInPrefix,
                                                   rLocalName, sCommentBuffer);
    }
    else
    {
        pContext = SvXMLImportContext::CreateChildContext(nInPrefix, rLocalName,
                                                          xAttrList);
    }

    return pContext;
}

void XMLChangeInfoContext::EndElement()
{
    // set values at changed region context
    rChangedRegion.SetChangeInfo(rType, sAuthor,
                                 sCommentBuffer.makeStringAndClear(),
                                 sDateTime);
}
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
