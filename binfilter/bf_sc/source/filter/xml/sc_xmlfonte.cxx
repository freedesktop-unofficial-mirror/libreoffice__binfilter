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

#include "scitems.hxx"

#define ITEMID_FIELD EE_FEATURE_FIELD

#include <bf_svx/fontitem.hxx>
#include <bf_svx/eeitem.hxx>
#include <bf_svx/editeng.hxx>

#include "document.hxx"
#include "docpool.hxx"
#include "xmlexprt.hxx"
#include "stlpool.hxx"
#include "attrib.hxx"
namespace binfilter {

class ScXMLFontAutoStylePool_Impl: public XMLFontAutoStylePool
{
    void AddFontItems(sal_uInt16* pWhichIds, sal_uInt8 nIdCount, const SfxItemPool* pPool, const sal_Bool bExportDefaults);
    public:

    ScXMLFontAutoStylePool_Impl( ScXMLExport& rExport );

};

void ScXMLFontAutoStylePool_Impl::AddFontItems(sal_uInt16* pWhichIds, sal_uInt8 nIdCount, const SfxItemPool* pInPool, const sal_Bool bExportDefaults)
{
    const SfxPoolItem* pItem;
    for( sal_uInt16 i=0; i < nIdCount; i++ )
    {
        sal_uInt16 nWhichId = pWhichIds[i];
        if (bExportDefaults && (0 != (pItem = &pInPool->GetDefaultItem(nWhichId))))
        {
            const SvxFontItem *pFont =
                        (const SvxFontItem *)pItem;
            Add( pFont->GetFamilyName(), pFont->GetStyleName(),
                    pFont->GetFamily(), pFont->GetPitch(),
                    pFont->GetCharSet() );
        }
        sal_uInt16 nItems = pInPool->GetItemCount( nWhichId );
        for( sal_uInt16 j = 0; j < nItems; ++j )
        {
            if( 0 != (pItem = pInPool->GetItem( nWhichId, j ) ) )
            {
                const SvxFontItem *pFont =
                            (const SvxFontItem *)pItem;
                Add( pFont->GetFamilyName(), pFont->GetStyleName(),
                     pFont->GetFamily(), pFont->GetPitch(),
                     pFont->GetCharSet() );
            }
        }
    }
}

ScXMLFontAutoStylePool_Impl::ScXMLFontAutoStylePool_Impl(
    ScXMLExport& rInExport ) :
    XMLFontAutoStylePool( rInExport )
{
    sal_uInt16 aWhichIds[3] = { ATTR_FONT, ATTR_CJK_FONT,
                                ATTR_CTL_FONT };
    sal_uInt16 aEditWhichIds[3] = { EE_CHAR_FONTINFO, EE_CHAR_FONTINFO_CJK,
                                    EE_CHAR_FONTINFO_CTL };
    sal_uInt16 aPageWhichIds[4] = { ATTR_PAGE_HEADERLEFT, ATTR_PAGE_FOOTERLEFT,
                                    ATTR_PAGE_HEADERRIGHT, ATTR_PAGE_FOOTERRIGHT };

    const SfxItemPool* pLclPool = rInExport.GetDocument() ? rInExport.GetDocument()->GetPool() : NULL;
    AddFontItems(aWhichIds, 3, pLclPool, sal_True);
    const SfxItemPool* pEditPool = rInExport.GetDocument()->GetEditPool();
    AddFontItems(aEditWhichIds, 3, pEditPool, sal_False);

    SfxStyleSheetIterator* pItr = rInExport.GetDocument() ? rInExport.GetDocument()->GetStyleSheetPool()->CreateIterator(SFX_STYLE_FAMILY_PAGE, 0xFFFF) : NULL;
    if(pItr)
    {
        SfxStyleSheetBase* pStyle = pItr->First();
        SfxItemPool* pPageEditPool = EditEngine::CreatePool();
        EditEngine aEditEngine(pPageEditPool);
        while (pStyle)
        {
            const SfxItemPool& rPagePool = pStyle->GetPool().GetPool();
            for (sal_uInt8 j = 0; j < 4; j++)
            {
                sal_uInt16 nPageWhichId = aPageWhichIds[j];
                sal_uInt16 nPageHFItems = rPagePool.GetItemCount(nPageWhichId);
                const ScPageHFItem* pPageItem;
                for (sal_uInt16 k = 0; k < nPageHFItems; k++)
                {
                    if (0 != (pPageItem = static_cast<const ScPageHFItem*>(rPagePool.GetItem(nPageWhichId, k))))
                    {
                        const EditTextObject* pLeftArea = pPageItem->GetLeftArea();
                        if (pLeftArea)
                        {
                            aEditEngine.SetText(*pLeftArea);
                            AddFontItems(aEditWhichIds, 3, pPageEditPool, sal_False);
                        }
                        const EditTextObject* pCenterArea = pPageItem->GetCenterArea();
                        if (pCenterArea)
                        {
                            aEditEngine.SetText(*pCenterArea);
                            AddFontItems(aEditWhichIds, 3, pPageEditPool, sal_False);
                        }
                        const EditTextObject* pRightArea = pPageItem->GetRightArea();
                        if (pRightArea)
                        {
                            aEditEngine.SetText(*pRightArea);
                            AddFontItems(aEditWhichIds, 3, pPageEditPool, sal_False);
                        }
                    }
                }
            }
            pStyle = pItr->Next();
        }
    }
}


XMLFontAutoStylePool* ScXMLExport::CreateFontAutoStylePool()
{
    return new ScXMLFontAutoStylePool_Impl( *this );
}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
