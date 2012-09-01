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

#include "XMLAutoMarkFileContext.hxx"

#include "xmlimp.hxx"


#include "nmspmap.hxx"

#include "xmlnmspe.hxx"




namespace binfilter {


using ::rtl::OUString;
using ::com::sun::star::uno::Any;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::UNO_QUERY;
using ::com::sun::star::xml::sax::XAttributeList;
using ::com::sun::star::beans::XPropertySet;

using ::binfilter::xmloff::token::IsXMLToken;
using ::binfilter::xmloff::token::XML_HREF;


TYPEINIT1( XMLAutoMarkFileContext, SvXMLImportContext );

XMLAutoMarkFileContext::XMLAutoMarkFileContext(
    SvXMLImport& rInImport,
    sal_uInt16 nInPrefix,
    const OUString& rLocalName) :
        SvXMLImportContext(rInImport, nInPrefix, rLocalName),
        sIndexAutoMarkFileURL(
            RTL_CONSTASCII_USTRINGPARAM("IndexAutoMarkFileURL"))
{
}

XMLAutoMarkFileContext::~XMLAutoMarkFileContext()
{
}


void XMLAutoMarkFileContext::StartElement(
    const Reference<XAttributeList> & xAttrList)
{
    // scan for text:alphabetical-index-auto-mark-file attribute, and if
    // found set value with the document

    sal_Int16 nLength = xAttrList->getLength();
    for( sal_Int16 i = 0; i < nLength; i++ )
    {
        OUString sLocalName;
        sal_uInt16 nLclPrefix = GetImport().GetNamespaceMap().
            GetKeyByAttrName( xAttrList->getNameByIndex(i), &sLocalName );

        if ( ( XML_NAMESPACE_XLINK == nLclPrefix ) &&
             IsXMLToken(sLocalName, XML_HREF) )
        {
            Any aAny;
            aAny <<= GetImport().GetAbsoluteReference( xAttrList->getValueByIndex(i) );
            Reference<XPropertySet> xPropertySet(
                GetImport().GetModel(), UNO_QUERY );
            if (xPropertySet.is())
            {
                xPropertySet->setPropertyValue( sIndexAutoMarkFileURL, aAny );
            }
        }
    }
}
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
