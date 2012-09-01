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

#include "hintids.hxx"

#include <com/sun/star/text/XTextDocument.hpp>
#include <com/sun/star/text/XText.hpp>

#include <com/sun/star/text/XTextDocument.hpp>
#include <com/sun/star/text/XText.hpp>
#include <bf_xmloff/XMLFontAutoStylePool.hxx>
#include <bf_svx/fontitem.hxx>

#include <osl/diagnose.h>

#include <unoobj.hxx>

#include <horiornt.hxx>

#include <doc.hxx>

#include <xmlexp.hxx>
namespace binfilter {

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::text;

class SwXMLFontAutoStylePool_Impl: public XMLFontAutoStylePool
{
    public:

    SwXMLFontAutoStylePool_Impl( SwXMLExport& rInExport );

};

SwXMLFontAutoStylePool_Impl::SwXMLFontAutoStylePool_Impl(
    SwXMLExport& rInExport ) :
    XMLFontAutoStylePool( rInExport )
{
    sal_uInt16 aWhichIds[3] = { RES_CHRATR_FONT, RES_CHRATR_CJK_FONT,
                                RES_CHRATR_CTL_FONT };

    Reference < XTextDocument > xTextDoc( rInExport.GetModel(), UNO_QUERY );
    Reference < XText > xText = xTextDoc->getText();
    Reference<XUnoTunnel> xTextTunnel( xText, UNO_QUERY);
    OSL_ENSURE( xTextTunnel.is(), "missing XUnoTunnel for Cursor" );
    if( !xTextTunnel.is() )
        return;

    SwXText *pText = (SwXText *)xTextTunnel->getSomething(
                                        SwXText::getUnoTunnelId() );
    OSL_ENSURE( pText, "SwXText missing" );
    if( !pText )
        return;

    const SfxItemPool& rPool = pText->GetDoc()->GetAttrPool();
    const SfxPoolItem* pItem;
    for( sal_uInt16 i=0; i<3; i++ )
    {
        sal_uInt16 nWhichId = aWhichIds[i];

        const SvxFontItem& rFont =
            (const SvxFontItem&)rPool.GetDefaultItem( nWhichId );
        Add( rFont.GetFamilyName(), rFont.GetStyleName(),
             rFont.GetFamily(), rFont.GetPitch(), rFont.GetCharSet() );
        sal_uInt16 nItems = rPool.GetItemCount( nWhichId );
        for( sal_uInt16 j = 0; j < nItems; ++j )
        {
            if( 0 != (pItem = rPool.GetItem( nWhichId, j ) ) )
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


XMLFontAutoStylePool* SwXMLExport::CreateFontAutoStylePool()
{
    return new SwXMLFontAutoStylePool_Impl( *this );
}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
