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

#include "XMLTrackedChangesImportContext.hxx"
#include "XMLChangedRegionImportContext.hxx"
#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/uno/Sequence.h>
#include <sax/tools/converter.hxx>
#include "xmlimp.hxx"
#include "xmlnmspe.hxx"
#include "nmspmap.hxx"
#include "xmluconv.hxx"

namespace binfilter {

using ::rtl::OUString;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::Sequence;
using ::com::sun::star::xml::sax::XAttributeList;
using namespace ::binfilter::xmloff::token;

TYPEINIT1( XMLTrackedChangesImportContext, SvXMLImportContext );

XMLTrackedChangesImportContext::XMLTrackedChangesImportContext(
    SvXMLImport& rInImport,
    sal_uInt16 nInPrefix,
    const OUString& rLocalName) :
        SvXMLImportContext(rInImport, nInPrefix, rLocalName)
{
}

XMLTrackedChangesImportContext::~XMLTrackedChangesImportContext()
{
}

void XMLTrackedChangesImportContext::StartElement(
    const Reference<XAttributeList> & xAttrList )
{
    sal_Bool bTrackChanges = sal_True;
    Sequence<sal_Int8> aProtectionKey;

    // scan for text:track-changes and text:protection-key attributes
    sal_Int16 nLength = xAttrList->getLength();
    for( sal_Int16 i = 0; i < nLength; i++ )
    {
        OUString sLocalName;
        sal_uInt16 nLclPrefix = GetImport().GetNamespaceMap().
            GetKeyByAttrName( xAttrList->getNameByIndex(i), &sLocalName );

        if ( XML_NAMESPACE_TEXT == nLclPrefix )
        {
            if ( IsXMLToken( sLocalName, XML_TRACK_CHANGES ) )
            {
                sal_Bool bTmp;
                if( SvXMLUnitConverter::convertBool(
                    bTmp, xAttrList->getValueByIndex(i)) )
                {
                    bTrackChanges = bTmp;
                }
            }
            else if ( IsXMLToken( sLocalName, XML_PROTECTION_KEY ) )            {
                Sequence<sal_Int8> aSequence;
                ::sax::Converter::decodeBase64(
                    aSequence, xAttrList->getValueByIndex(i));
                if ( aSequence.getLength() > 0 )
                {
                    aProtectionKey = aSequence;
                }
            }
        }
    }

    // set tracked changes
    GetImport().GetTextImport()->SetRecordChanges( bTrackChanges );
    GetImport().GetTextImport()->SetChangesProtectionKey( aProtectionKey );
}


SvXMLImportContext* XMLTrackedChangesImportContext::CreateChildContext(
    sal_uInt16 nInPrefix,
    const OUString& rLocalName,
    const Reference<XAttributeList> & xAttrList)
{
    SvXMLImportContext* pContext = NULL;

    if ( (XML_NAMESPACE_TEXT == nInPrefix) &&
         IsXMLToken( rLocalName, XML_CHANGED_REGION ) )
    {
        pContext = new XMLChangedRegionImportContext(GetImport(),
                                                     nInPrefix, rLocalName);
    }

    if (NULL == pContext)
    {
        pContext = SvXMLImportContext::CreateChildContext(nInPrefix, rLocalName,
                                                          xAttrList);
    }

    return pContext;
}
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
