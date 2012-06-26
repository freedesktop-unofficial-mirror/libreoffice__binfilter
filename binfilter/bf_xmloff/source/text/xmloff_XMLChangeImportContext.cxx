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

#include "XMLChangeImportContext.hxx"


#include <tools/debug.hxx>

#include "xmlimp.hxx"

#include "xmlnmspe.hxx"

#include "nmspmap.hxx"

namespace binfilter {

using ::rtl::OUString;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::text::XTextRange;
using ::com::sun::star::xml::sax::XAttributeList;
using ::binfilter::xmloff::token::IsXMLToken;
using ::binfilter::xmloff::token::XML_CHANGE_ID;

TYPEINIT1( XMLChangeImportContext, SvXMLImportContext );

XMLChangeImportContext::XMLChangeImportContext(
    SvXMLImport& rInImport,
    sal_Int16 nInPrefix,
    const OUString& rLocalName,
    sal_Bool bStart,
    sal_Bool bEnd,
    sal_Bool bOutsideOfParagraph) :
        SvXMLImportContext(rInImport, nInPrefix, rLocalName),
        bIsStart(bStart),
        bIsEnd(bEnd),
        bIsOutsideOfParagraph(bOutsideOfParagraph)
{
    DBG_ASSERT(bStart || bEnd, "Must be either start, end, or both!");
}

XMLChangeImportContext::~XMLChangeImportContext()
{
}

void XMLChangeImportContext::StartElement(
    const Reference<XAttributeList>& xAttrList)
{
    sal_Int16 nLength = xAttrList->getLength();
    for(sal_Int16 nAttr = 0; nAttr < nLength; nAttr++)
    {
        OUString sLocalName;
        sal_uInt16 nLclPrefix = GetImport().GetNamespaceMap().
            GetKeyByAttrName( xAttrList->getNameByIndex(nAttr),
                              &sLocalName );
        if ( (XML_NAMESPACE_TEXT == nLclPrefix) &&
             IsXMLToken( sLocalName, XML_CHANGE_ID ) )
        {
            // Id found! Now call RedlineImportHelper

            // prepare parameters
            UniReference<XMLTextImportHelper> rHelper =
                GetImport().GetTextImport();
            OUString sID = xAttrList->getValueByIndex(nAttr);

            // call for bStart and bEnd (may both be true)
            if (bIsStart)
                rHelper->RedlineSetCursor(sID,sal_True,bIsOutsideOfParagraph);
            if (bIsEnd)
                rHelper->RedlineSetCursor(sID,sal_False,bIsOutsideOfParagraph);

            // outside of paragraph and still open? set open redline ID
            if (bIsOutsideOfParagraph)
            {
                rHelper->SetOpenRedlineId(sID);
            }
        }
        // else: ignore
    }
}
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
