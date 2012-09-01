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

#include <hintids.hxx>

#include <rtl/ustring.hxx>
#include <rsc/rscsfx.hxx>

#include "xmlitmap.hxx"
#include "xmlimpit.hxx"
#include "xmlitem.hxx"
#include <bf_xmloff/i18nmap.hxx>
#include <bf_xmloff/xmluconv.hxx>
#include <bf_xmloff/families.hxx>

#include <bf_svx/unomid.hxx>
#include <bf_svx/boxitem.hxx>
#include <bf_svx/fontitem.hxx>
#include <bf_svx/tstpitem.hxx>
#include <bf_svx/boxitem.hxx>
#include <bf_svx/brshitem.hxx>
#include <bf_svx/langitem.hxx>

#include "xmlbrshi.hxx"

#include <paratr.hxx>

#include <horiornt.hxx>

#include <doc.hxx>
#include <unomid.h>

#include "xmlimp.hxx"
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;

using rtl::OUString;

extern SvXMLItemMapEntry aXMLTableItemMap[];
extern SvXMLItemMapEntry aXMLTableColItemMap[];
extern SvXMLItemMapEntry aXMLTableRowItemMap[];
extern SvXMLItemMapEntry aXMLTableCellItemMap[];

class SwXMLImportTableItemMapper_Impl: public SvXMLImportItemMapper
{

public:

    SwXMLImportTableItemMapper_Impl( SvXMLItemMapEntriesRef rMapEntries );
    virtual ~SwXMLImportTableItemMapper_Impl();

    virtual sal_Bool handleSpecialItem( const SvXMLItemMapEntry& rEntry,
                                SfxPoolItem& rItem,
                                SfxItemSet& rSet,
                                const OUString& rValue,
                                const SvXMLUnitConverter& rInUnitConverter,
                                const SvXMLNamespaceMap& rNamespaceMap ) const;
    virtual void finished( SfxItemSet& rSet ) const;
};

SwXMLImportTableItemMapper_Impl::SwXMLImportTableItemMapper_Impl(
                                        SvXMLItemMapEntriesRef rMapEntries ) :
    SvXMLImportItemMapper( rMapEntries, RES_UNKNOWNATR_CONTAINER)
{
}

SwXMLImportTableItemMapper_Impl::~SwXMLImportTableItemMapper_Impl()
{
}

sal_Bool SwXMLImportTableItemMapper_Impl::handleSpecialItem(
                                        const SvXMLItemMapEntry& rEntry,
                                        SfxPoolItem& rItem,
                                        SfxItemSet& rInItemSet,
                                        const OUString& rValue,
                                        const SvXMLUnitConverter& rInUnitConv,
                                        const SvXMLNamespaceMap& ) const
{
    sal_Bool bRet = sal_False;
    sal_uInt16 nMemberId = rEntry.nMemberId & MID_FLAG_MASK;
    switch( rItem.Which() )
    {
    case RES_FRM_SIZE:
        switch( nMemberId )
        {
        case MID_FRMSIZE_COL_WIDTH:
            // If the item is existing already, a relative value has been set
            // already that must be preserved.
            if( SFX_ITEM_SET != rInItemSet.GetItemState( RES_FRM_SIZE,
                                                       sal_False ) )
                bRet = SvXMLImportItemMapper::PutXMLValue(
                    rItem, rValue, nMemberId, rInUnitConv );
            break;
        }
    }

    return bRet;
}

void SwXMLImportTableItemMapper_Impl::finished( SfxItemSet& /*rSet*/ ) const { }

// ---------------------------------------------------------------------

class SwXMLItemSetContext_Impl : public SvXMLItemSetContext
{
    SvXMLImportContextRef xBackground;

public:
    SwXMLItemSetContext_Impl( SwXMLImport& rInImport, sal_uInt16 nPrfx,
                  const OUString& rLName,
                  const Reference< xml::sax::XAttributeList > & xAttrList,
                  SfxItemSet&  rInItemSet,
                  const SvXMLImportItemMapper& rInIMapper,
                  const SvXMLUnitConverter& rInUnitConv );
    virtual ~SwXMLItemSetContext_Impl();

    using SvXMLItemSetContext::CreateChildContext;
    virtual SvXMLImportContext *CreateChildContext( sal_uInt16 nInPrefix,
                   const OUString& rLocalName,
                   const Reference< xml::sax::XAttributeList > & xAttrList,
                   SfxItemSet&  rInItemSet,
                   const SvXMLItemMapEntry& rEntry,
                   const SvXMLUnitConverter& rInUnitConv );
};

SwXMLItemSetContext_Impl::SwXMLItemSetContext_Impl(
                 SwXMLImport& rInImport, sal_uInt16 nPrfx,
                 const OUString& rLName,
                 const Reference< xml::sax::XAttributeList > & xAttrList,
                 SfxItemSet&  rInItemSet,
                 const SvXMLImportItemMapper& rInIMapper,
                 const SvXMLUnitConverter& rInUnitConv ) :
    SvXMLItemSetContext( rInImport, nPrfx, rLName, xAttrList,
                         rInItemSet, rInIMapper, rInUnitConv )
{
}

SwXMLItemSetContext_Impl::~SwXMLItemSetContext_Impl()
{
    if( xBackground.Is() )
    {
        const SvxBrushItem& rItem =
            ((SwXMLBrushItemImportContext*)&xBackground)->GetItem();
        rItemSet.Put( rItem );
    }
}

SvXMLImportContext *SwXMLItemSetContext_Impl::CreateChildContext(
                   sal_uInt16 nInPrefix,
                   const OUString& rLocalName,
                   const Reference< xml::sax::XAttributeList > & xAttrList,
                   SfxItemSet&  rInItemSet,
                   const SvXMLItemMapEntry& rEntry,
                   const SvXMLUnitConverter& rInUnitConv )
{
    SvXMLImportContext *pContext = 0;

    switch( rEntry.nWhichId )
    {
    case RES_BACKGROUND:
        {
            const SfxPoolItem *pItem;
            if( SFX_ITEM_SET == rInItemSet.GetItemState( RES_BACKGROUND,
                                                       sal_False, &pItem ) )
            {
                pContext = new SwXMLBrushItemImportContext(
                                GetImport(), nInPrefix, rLocalName, xAttrList,
                                rInUnitConv, *(const SvxBrushItem *)pItem );
            }
            else
            {
                pContext = new SwXMLBrushItemImportContext(
                                GetImport(), nInPrefix, rLocalName, xAttrList,
                                rInUnitConv, RES_BACKGROUND );
            }
            xBackground = pContext;
        }
        break;
    }

    if( !pContext )
        pContext = SvXMLItemSetContext::CreateChildContext( nInPrefix, rLocalName,
                                                            xAttrList, rInItemSet,
                                                            rEntry, rInUnitConv );

    return pContext;
}

// ---------------------------------------------------------------------

void SwXMLImport::_InitItemImport()
{
    // #110680#
    pTwipUnitConv = new SvXMLUnitConverter( MAP_TWIP, MAP_TWIP, getServiceFactory() );

    xTableItemMap = new SvXMLItemMapEntries( aXMLTableItemMap );
    xTableColItemMap = new SvXMLItemMapEntries( aXMLTableColItemMap );
    xTableRowItemMap = new SvXMLItemMapEntries( aXMLTableRowItemMap );
    xTableCellItemMap = new SvXMLItemMapEntries( aXMLTableCellItemMap );

    pTableItemMapper = new SwXMLImportTableItemMapper_Impl( xTableItemMap );
}

void SwXMLImport::_FinitItemImport()
{
    delete pTableItemMapper;
    delete pTwipUnitConv;
}

SvXMLImportContext *SwXMLImport::CreateTableItemImportContext(
                  sal_uInt16 nInPrefix,
                  const OUString& rLocalName,
                  const Reference< xml::sax::XAttributeList > & xAttrList,
                  sal_uInt16 nFamily,
                  SfxItemSet& rInItemSet )
{
    SvXMLItemMapEntriesRef xItemMap;

    switch( nFamily )
    {
    case XML_STYLE_FAMILY_TABLE_TABLE:
        xItemMap = xTableItemMap;
        break;
    case XML_STYLE_FAMILY_TABLE_COLUMN:
        xItemMap = xTableColItemMap;
        break;
    case XML_STYLE_FAMILY_TABLE_ROW:
        xItemMap = xTableRowItemMap;
        break;
    case XML_STYLE_FAMILY_TABLE_CELL:
        xItemMap = xTableCellItemMap;
        break;
    }

    pTableItemMapper->setMapEntries( xItemMap );

    return new SwXMLItemSetContext_Impl( *this, nInPrefix, rLocalName,
                                            xAttrList, rInItemSet,
                                            GetTableItemMapper(),
                                            GetTwipUnitConverter() );
}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
