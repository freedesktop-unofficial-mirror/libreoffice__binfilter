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


#include "PageHeaderFooterContext.hxx"
#include "xmlnmspe.hxx"
#include "PagePropertySetContext.hxx"
namespace binfilter {

using namespace ::com::sun::star;
using ::binfilter::xmloff::token::IsXMLToken;
using ::binfilter::xmloff::token::XML_PROPERTIES;

//------------------------------------------------------------------

PageHeaderFooterContext::PageHeaderFooterContext( SvXMLImport& rInImport,
                                      USHORT nPrfx,
                                      const ::rtl::OUString& rLName,
                                      const ::com::sun::star::uno::Reference<
                                      ::com::sun::star::xml::sax::XAttributeList>& /*xAttrList*/,
                                      ::std::vector< XMLPropertyState > & rTempProperties,
                                      const UniReference < SvXMLImportPropertyMapper > &rTempMap,
                                      sal_Int32 nStart, sal_Int32 nEnd,
                                      const sal_Bool bTempHeader ) :
    SvXMLImportContext( rInImport, nPrfx, rLName ),
    rProperties(rTempProperties),
    nStartIndex(nStart),
    nEndIndex(nEnd),
    rMap(rTempMap)
{
    bHeader = bTempHeader;
}

PageHeaderFooterContext::~PageHeaderFooterContext()
{
}

SvXMLImportContext *PageHeaderFooterContext::CreateChildContext( USHORT nInPrefix,
                                            const ::rtl::OUString& rLName,
                                            const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList )
{
    SvXMLImportContext *pContext = 0;

    if( XML_NAMESPACE_STYLE == nInPrefix && IsXMLToken( rLName, XML_PROPERTIES ) )
    {
        PageContextType aType = Header;
        if (!bHeader)
            aType = Footer;
        pContext = new PagePropertySetContext( GetImport(), nInPrefix,
                                                rLName, xAttrList,
                                                rProperties,
                                                rMap,  nStartIndex, nEndIndex, aType);
    }


    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nInPrefix, rLName );

    return pContext;
}

void PageHeaderFooterContext::EndElement()
{
}

}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
