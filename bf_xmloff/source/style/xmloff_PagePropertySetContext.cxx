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

#include <tools/debug.hxx>

#include "PagePropertySetContext.hxx"
#include "XMLBackgroundImageContext.hxx"
#include "XMLTextColumnsContext.hxx"
#include "PageMasterStyleMap.hxx"
#include "XMLFootnoteSeparatorImport.hxx"
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star;

PagePropertySetContext::PagePropertySetContext(
                 SvXMLImport& rInImport, sal_uInt16 nPrfx,
                 const OUString& rLName,
                 const Reference< xml::sax::XAttributeList > & xAttrList,
                 ::std::vector< XMLPropertyState > &rProps,
                 const UniReference < SvXMLImportPropertyMapper > &rMap,
                 sal_Int32 nStartIndex, sal_Int32 nEndIndex,
                 const PageContextType aTempType ) :
    SvXMLPropertySetContext( rInImport, nPrfx, rLName, xAttrList, rProps, rMap, nStartIndex, nEndIndex )
{
    aType = aTempType;
}

PagePropertySetContext::~PagePropertySetContext()
{
}

SvXMLImportContext *PagePropertySetContext::CreateChildContext(
                   sal_uInt16 nInPrefix,
                   const OUString& rLocalName,
                   const Reference< xml::sax::XAttributeList > & xAttrList,
                   ::std::vector< XMLPropertyState > &rInProperties,
                   const XMLPropertyState& rProp )
{
    sal_Int32 nPos = CTF_PM_GRAPHICPOSITION;
    sal_Int32 nFil = CTF_PM_GRAPHICFILTER;
    switch ( aType )
    {
        case Header:
        {
            nPos = CTF_PM_HEADERGRAPHICPOSITION;
            nFil = CTF_PM_HEADERGRAPHICFILTER;
        }
        break;
        case Footer:
        {
            nPos = CTF_PM_FOOTERGRAPHICPOSITION;
            nFil = CTF_PM_FOOTERGRAPHICFILTER;
        }
        break;
        default:
        break;
    }
    SvXMLImportContext *pContext = 0;

    switch( xMapper->getPropertySetMapper()
                    ->GetEntryContextId( rProp.mnIndex ) )
    {
    case CTF_PM_GRAPHICURL:
    case CTF_PM_HEADERGRAPHICURL:
    case CTF_PM_FOOTERGRAPHICURL:
        DBG_ASSERT( rProp.mnIndex >= 2 &&
                    nPos  == xMapper->getPropertySetMapper()
                        ->GetEntryContextId( rProp.mnIndex-2 ) &&
                    nFil  == xMapper->getPropertySetMapper()
                        ->GetEntryContextId( rProp.mnIndex-1 ),
                    "invalid property map!");
        (void)nPos;
        (void)nFil;
        pContext =
            new XMLBackgroundImageContext( GetImport(), nInPrefix,
                                           rLocalName, xAttrList,
                                           rProp,
                                           rProp.mnIndex-2,
                                           rProp.mnIndex-1,
                                           -1,
                                           rInProperties );
        break;

    case CTF_PM_TEXTCOLUMNS:
#ifndef SVX_LIGHT
        pContext = new XMLTextColumnsContext( GetImport(), nInPrefix,
                                              rLocalName, xAttrList, rProp,
                                              rInProperties );
#else
        // create default context to skip content
        pContext = new SvXMLImportContext( GetImport(), nInPrefix, rLocalName );
#endif // #ifndef SVX_LIGHT
        break;

    case CTF_PM_FTN_LINE_WEIGTH:
#ifndef SVX_LIGHT
        pContext = new XMLFootnoteSeparatorImport(
            GetImport(), nInPrefix, rLocalName, rInProperties,
            xMapper->getPropertySetMapper(), rProp.mnIndex);
#else
        // create default context to skip content
        pContext = new SvXMLImportContext( GetImport(), nInPrefix, rLocalName);
#endif // #ifndef SVX_LIGHT
        break;
    }

    if( !pContext )
        pContext = SvXMLPropertySetContext::CreateChildContext( nInPrefix, rLocalName,
                                                            xAttrList,
                                                            rInProperties, rProp );

    return pContext;
}


}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
