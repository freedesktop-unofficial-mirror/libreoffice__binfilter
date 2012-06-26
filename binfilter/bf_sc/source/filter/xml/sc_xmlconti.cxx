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


#include "xmlconti.hxx"
#include "xmlimprt.hxx"

#include <bf_xmloff/nmspmap.hxx>
#include <bf_xmloff/xmlnmspe.hxx>
namespace binfilter {

using namespace xmloff::token;

//------------------------------------------------------------------

ScXMLContentContext::ScXMLContentContext( ScXMLImport& rInImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& /*xAttrList*/,
                                      ::rtl::OUStringBuffer& sTempValue) :
    SvXMLImportContext( rInImport, nPrfx, rLName ),
    sOUText(),
    sValue(sTempValue)
{
}

ScXMLContentContext::~ScXMLContentContext()
{
}

SvXMLImportContext *ScXMLContentContext::CreateChildContext( USHORT nInPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = 0;

    if ((nInPrefix == XML_NAMESPACE_TEXT) && IsXMLToken(rLName, XML_S))
    {
        sal_Int32 nRepeat(0);
        sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
        for( sal_Int16 i=0; i < nAttrCount; i++ )
        {
            ::rtl::OUString sAttrName = xAttrList->getNameByIndex( i );
            ::rtl::OUString sLclValue = xAttrList->getValueByIndex( i );
            ::rtl::OUString aLclLocalName;
            USHORT nPrfx = GetScImport().GetNamespaceMap().GetKeyByAttrName(
                                                sAttrName, &aLclLocalName );
            if ((nPrfx == XML_NAMESPACE_TEXT) && IsXMLToken(aLclLocalName, XML_C))
                nRepeat = sLclValue.toInt32();
        }
        if (nRepeat)
            for (sal_Int32 j = 0; j < nRepeat; j++)
                sOUText.append(static_cast<sal_Unicode>(' '));
        else
            sOUText.append(static_cast<sal_Unicode>(' '));
    }

    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nInPrefix, rLName );

    return pContext;
}

void ScXMLContentContext::Characters( const ::rtl::OUString& rChars )
{
    sOUText.append(rChars);
}

void ScXMLContentContext::EndElement()
{
    sValue.append(sOUText.toString());
}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
