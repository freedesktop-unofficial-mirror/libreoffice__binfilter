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

#include "ximpnote.hxx"

namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;

//////////////////////////////////////////////////////////////////////////////

SdXMLNotesContext::SdXMLNotesContext( SdXMLImport& rInImport,
    USHORT nPrfx, const OUString& rLocalName,
    const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList>& xAttrList,
    uno::Reference< drawing::XShapes >& rShapes)
:   SdXMLGenericPageContext( rInImport, nPrfx, rLocalName, xAttrList, rShapes )
{
    const sal_Int16 nAttrCount = xAttrList.is() ? xAttrList->getLength() : 0;
    for(sal_Int16 i=0; i < nAttrCount; i++)
    {
        OUString sAttrName = xAttrList->getNameByIndex( i );
        OUString aLclLocalName;
        sal_uInt16 nLclPrefix = GetSdImport().GetNamespaceMap().GetKeyByAttrName( sAttrName, &aLclLocalName );
        OUString sValue = xAttrList->getValueByIndex( i );
        const SvXMLTokenMap& rAttrTokenMap = GetSdImport().GetMasterPageAttrTokenMap();

        switch(rAttrTokenMap.Get(nLclPrefix, aLclLocalName))
        {
            case XML_TOK_MASTERPAGE_PAGE_MASTER_NAME:
            {
                msPageMasterName = sValue;
                break;
            }
        }
    }

    // now delete all up-to-now contained shapes from this notes page
    uno::Reference< drawing::XShape > xShape;
    while(rShapes->getCount())
    {
        rShapes->getByIndex(0L) >>= xShape;
        if(xShape.is())
            rShapes->remove(xShape);
    }

    // set page-master?
    if(msPageMasterName.getLength())
    {
        SetPageMaster( msPageMasterName );
    }
}

//////////////////////////////////////////////////////////////////////////////

SdXMLNotesContext::~SdXMLNotesContext()
{
}

//////////////////////////////////////////////////////////////////////////////

SvXMLImportContext *SdXMLNotesContext::CreateChildContext( USHORT nInPrefix,
    const OUString& rLocalName,
    const uno::Reference< xml::sax::XAttributeList>& xAttrList )
{
    // OK, notes page is set on base class, objects can be imported on notes page
    SvXMLImportContext *pContext = 0L;

    // some special objects inside presentation:notes context
    // ...







    // call parent when no own context was created
    if(!pContext)
        pContext = SdXMLGenericPageContext::CreateChildContext(nInPrefix, rLocalName, xAttrList);

    return pContext;
}

//////////////////////////////////////////////////////////////////////////////

void SdXMLNotesContext::EndElement()
{
    SdXMLGenericPageContext::EndElement();
}
}//end of namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
