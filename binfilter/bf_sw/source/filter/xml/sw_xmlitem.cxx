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


#include <bf_xmloff/xmlimp.hxx>

#include "xmlimpit.hxx"

#include "xmlitem.hxx"
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;

SvXMLItemSetContext::SvXMLItemSetContext( SvXMLImport& rImp, USHORT nPrfx,
                                          const OUString& rLName,
                                          const uno::Reference< xml::sax::XAttributeList >& xAttrList,
                                          SfxItemSet& rISet,
                                          const SvXMLImportItemMapper& rIMap,
                                          const SvXMLUnitConverter& rUnitConverter ):
    SvXMLImportContext( rImp, nPrfx, rLName ),
    rItemSet( rISet ),
    rIMapper( rIMap ),
    rUnitConv( rUnitConverter )

{
    rIMapper.importXML( rItemSet, xAttrList, rUnitConv,
                           GetImport().GetNamespaceMap() );
}

SvXMLItemSetContext::~SvXMLItemSetContext()
{
}

SvXMLImportContext *SvXMLItemSetContext::CreateChildContext( USHORT nInPrefix,
                                            const OUString& rLocalName,
                                            const uno::Reference< xml::sax::XAttributeList >& xAttrList )
{
    SvXMLItemMapEntriesRef xMapEntries = rIMapper.getMapEntries();
    SvXMLItemMapEntry* pEntry = xMapEntries->getByName( nInPrefix, rLocalName );

    if( pEntry && 0 != (pEntry->nMemberId & MID_FLAG_ELEMENT_ITEM_IMPORT) )
    {
        return CreateChildContext( nInPrefix, rLocalName, xAttrList,
                                   rItemSet, *pEntry, rUnitConv );
    }
    else
    {
        return new SvXMLImportContext( GetImport(), nInPrefix, rLocalName );
    }
}

/** This method is called from this instance implementation of
    CreateChildContext if the element matches an entry in the
    SvXMLImportItemMapper with the mid flag MID_FLAG_ELEMENT
*/
SvXMLImportContext *SvXMLItemSetContext::CreateChildContext( USHORT nInPrefix,
                                   const ::rtl::OUString& rLocalName,
                                   const uno::Reference< xml::sax::XAttributeList >& /*xAttrList*/,
                                    SfxItemSet&  /*rItemSet*/,
                                   const SvXMLItemMapEntry& /*rEntry*/,
                                   const SvXMLUnitConverter& /*rUnitConv*/ )
{
    return new SvXMLImportContext( GetImport(), nInPrefix, rLocalName );
}


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
