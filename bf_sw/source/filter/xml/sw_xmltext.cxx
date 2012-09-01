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

#include <bf_xmloff/xmlnmspe.hxx>
#include "xmlimp.hxx"
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::text;

using rtl::OUString;

// ---------------------------------------------------------------------

class SwXMLBodyContext_Impl : public SvXMLImportContext
{
    SwXMLImport& GetSwImport() { return (SwXMLImport&)GetImport(); }

public:

    SwXMLBodyContext_Impl( SwXMLImport& rInImport, sal_uInt16 nPrfx,
                             const OUString& rLName );
    virtual ~SwXMLBodyContext_Impl();

    virtual SvXMLImportContext *CreateChildContext(
            sal_uInt16 nInPrefix, const OUString& rLocalName,
            const Reference< xml::sax::XAttributeList > & xAttrList );

    virtual void EndElement();
};

SwXMLBodyContext_Impl::SwXMLBodyContext_Impl( SwXMLImport& rInImport,
                                              sal_uInt16 nPrfx,
                                                   const OUString& rLName ) :
    SvXMLImportContext( rInImport, nPrfx, rLName )
{
}

SwXMLBodyContext_Impl::~SwXMLBodyContext_Impl()
{
}

SvXMLImportContext *SwXMLBodyContext_Impl::CreateChildContext(
        sal_uInt16 nInPrefix, const OUString& rLocalName,
        const Reference< xml::sax::XAttributeList > & xAttrList )
{
    SvXMLImportContext *pContext = 0;

    pContext = GetSwImport().GetTextImport()->CreateTextChildContext(
            GetImport(), nInPrefix, rLocalName, xAttrList,
               XML_TEXT_TYPE_BODY );
    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nInPrefix, rLocalName );

    return pContext;
}

void SwXMLBodyContext_Impl::EndElement()
{
    /* #108146# Code moved to SwXMLOmport::endDocument */
    GetImport().GetTextImport()->SetOutlineStyles();
}

SvXMLImportContext *SwXMLImport::CreateBodyContext(
                                       const OUString& rLocalName )
{
    SvXMLImportContext *pContext = 0;

    if( !IsStylesOnlyMode() )
         pContext = new SwXMLBodyContext_Impl( *this, XML_NAMESPACE_OFFICE,
                                              rLocalName );
    else
        pContext = new SvXMLImportContext( *this, XML_NAMESPACE_OFFICE,
                                           rLocalName );

    return pContext;
}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
