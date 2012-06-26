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

#include "eeitem.hxx"


#include <toolkit/helper/vclunohelper.hxx>

#define ITEMID_FONT EE_CHAR_FONTINFO
#include <fontitem.hxx>

#define ITEMID_FONTHEIGHT EE_CHAR_FONTHEIGHT
#include <fhgtitem.hxx>

#define ITEMID_POSTURE EE_CHAR_ITALIC
#include <postitem.hxx>

#define ITEMID_UNDERLINE EE_CHAR_UNDERLINE
#include <udlnitem.hxx>

#define ITEMID_WEIGHT EE_CHAR_WEIGHT
#include <wghtitem.hxx>

#define ITEMID_CROSSEDOUT EE_CHAR_STRIKEOUT
#include <crsditem.hxx>

#define ITEMID_WORDLINEMODE EE_CHAR_WLM
#include <wrlmitem.hxx>


#include <bf_svtools/itempool.hxx>

#include "unofdesc.hxx"
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;


void SvxUnoFontDescriptor::ConvertToFont( const awt::FontDescriptor& rDesc, Font& rFont )
{
    rFont.SetName( rDesc.Name );
    rFont.SetStyleName( rDesc.StyleName );
    rFont.SetSize( Size( rDesc.Width, rDesc.Height ) );
    rFont.SetFamily( (FontFamily)rDesc.Family );
    rFont.SetCharSet( (CharSet)rDesc.CharSet );
    rFont.SetPitch( (FontPitch)rDesc.Pitch );
    rFont.SetOrientation( (short)(rDesc.Orientation*10) );
    rFont.SetKerning( rDesc.Kerning );
    rFont.SetWeight( VCLUnoHelper::ConvertFontWeight(rDesc.Weight) );
    rFont.SetItalic( (FontItalic)rDesc.Slant );
    rFont.SetUnderline( (FontUnderline)rDesc.Underline );
    rFont.SetStrikeout( (FontStrikeout)rDesc.Strikeout );
    rFont.SetWordLineMode( rDesc.WordLineMode );
}

void SvxUnoFontDescriptor::ConvertFromFont( const Font& rFont, awt::FontDescriptor& rDesc )
{
    rDesc.Name = rFont.GetName();
    rDesc.StyleName = rFont.GetStyleName();
    rDesc.Width = rFont.GetSize().Width();
    rDesc.Height = rFont.GetSize().Height();
    rDesc.Family = rFont.GetFamily();
    rDesc.CharSet = rFont.GetCharSet();
    rDesc.Pitch = rFont.GetPitch();
    rDesc.Orientation = rFont.GetOrientation() / 10.0;
    rDesc.Kerning = rFont.IsKerning();
    rDesc.Weight = VCLUnoHelper::ConvertFontWeight( rFont.GetWeight() );
    rDesc.Slant = (awt::FontSlant)rFont.GetItalic();
    rDesc.Underline = rFont.GetUnderline();
    rDesc.Strikeout = rFont.GetStrikeout();
    rDesc.WordLineMode = rFont.IsWordLineMode();
}

void SvxUnoFontDescriptor::FillItemSet( const awt::FontDescriptor& rDesc, SfxItemSet& rSet )
{
    uno::Any aTemp;

    {
        SvxFontItem aFontItem( EE_CHAR_FONTINFO );
        aFontItem.GetFamilyName()= rDesc.Name;
        aFontItem.GetStyleName() = rDesc.StyleName;
        aFontItem.GetFamily()    = (FontFamily)rDesc.Family;
        aFontItem.GetCharSet()   = rDesc.CharSet;
        aFontItem.GetPitch()     = (FontPitch)rDesc.Pitch;
        rSet.Put(aFontItem);
    }

    {
        SvxFontHeightItem aFontHeightItem( 0, 100, EE_CHAR_FONTHEIGHT );
        aTemp <<= (float)rDesc.Height;
        ((SfxPoolItem*)&aFontHeightItem)->PutValue( aTemp, MID_FONTHEIGHT|CONVERT_TWIPS );
        rSet.Put(aFontHeightItem);
    }

    {
        SvxPostureItem aPostureItem( (FontItalic)0, EE_CHAR_ITALIC );
        aTemp <<= rDesc.Slant;
        ((SfxPoolItem*)&aPostureItem)->PutValue( aTemp, MID_POSTURE );
        rSet.Put(aPostureItem);
    }

    {
        SvxUnderlineItem aUnderlineItem( (FontUnderline)0, EE_CHAR_UNDERLINE );
        aTemp <<= (sal_Int16)rDesc.Underline;
        ((SfxPoolItem*)&aUnderlineItem)->PutValue( aTemp, MID_UNDERLINE );
        rSet.Put( aUnderlineItem );
    }

    {
        SvxWeightItem aWeightItem( (FontWeight)0, EE_CHAR_WEIGHT );
        aTemp <<= rDesc.Weight;
        ((SfxPoolItem*)&aWeightItem)->PutValue( aTemp, MID_WEIGHT );
        rSet.Put( aWeightItem );
    }

    {
        SvxCrossedOutItem aCrossedOutItem( (FontStrikeout)0, EE_CHAR_STRIKEOUT );
        aTemp <<= rDesc.Strikeout;
        ((SfxPoolItem*)&aCrossedOutItem)->PutValue( aTemp, MID_CROSS_OUT );
        rSet.Put( aCrossedOutItem );
    }

    {
        SvxWordLineModeItem aWLMItem( rDesc.WordLineMode, EE_CHAR_WLM );
        rSet.Put( aWLMItem );
    }
}

void SvxUnoFontDescriptor::FillFromItemSet( const SfxItemSet& rSet, awt::FontDescriptor& rDesc )
{
    const SfxPoolItem* pItem = NULL;
    {
        SvxFontItem* pFontItem = (SvxFontItem*)&rSet.Get( EE_CHAR_FONTINFO, TRUE );
        rDesc.Name      = pFontItem->GetFamilyName();
        rDesc.StyleName = pFontItem->GetStyleName();
        rDesc.Family    = pFontItem->GetFamily();
        rDesc.CharSet   = pFontItem->GetCharSet();
        rDesc.Pitch     = pFontItem->GetPitch();
    }
    {
        pItem = &rSet.Get( EE_CHAR_FONTHEIGHT, TRUE );
        uno::Any aHeight;
        if( pItem->QueryValue( aHeight, MID_FONTHEIGHT ) )
            aHeight >>= rDesc.Height;
    }
    {
        pItem = &rSet.Get( EE_CHAR_ITALIC, TRUE );
        uno::Any aFontSlant;
        if(pItem->QueryValue( aFontSlant, MID_POSTURE ))
            aFontSlant >>= rDesc.Slant;
    }
    {
        pItem = &rSet.Get( EE_CHAR_UNDERLINE, TRUE );
        uno::Any aUnderline;
        if(pItem->QueryValue( aUnderline, MID_UNDERLINE ))
            aUnderline >>= rDesc.Underline;
    }
    {
        pItem = &rSet.Get( EE_CHAR_WEIGHT, TRUE );
        uno::Any aWeight;
        if(pItem->QueryValue( aWeight, MID_WEIGHT ))
            aWeight >>= rDesc.Weight;
    }
    {
        pItem = &rSet.Get( EE_CHAR_STRIKEOUT, TRUE );
        uno::Any aStrikeOut;
        if(pItem->QueryValue( aStrikeOut, MID_CROSS_OUT ))
            aStrikeOut >>= rDesc.Strikeout;
    }
    {
        SvxWordLineModeItem* pWLMItem = (SvxWordLineModeItem*)&rSet.Get( EE_CHAR_WLM, TRUE );
        rDesc.WordLineMode = pWLMItem->GetValue();
    }
}

#define CheckState( state ) \
    switch( state ) \
    { \
    case SFX_ITEM_DONTCARE: \
    case SFX_ITEM_DISABLED: \
        return beans::PropertyState_AMBIGUOUS_VALUE; \
    case SFX_ITEM_READONLY: \
    case SFX_ITEM_SET: \
        return beans::PropertyState_DIRECT_VALUE; \
    }

void SvxUnoFontDescriptor::setPropertyToDefault( SfxItemSet& rSet )
{
    rSet.InvalidateItem( EE_CHAR_FONTINFO );
    rSet.InvalidateItem( EE_CHAR_FONTHEIGHT );
    rSet.InvalidateItem( EE_CHAR_ITALIC );
    rSet.InvalidateItem( EE_CHAR_UNDERLINE );
    rSet.InvalidateItem( EE_CHAR_WEIGHT );
    rSet.InvalidateItem( EE_CHAR_STRIKEOUT );
    rSet.InvalidateItem( EE_CHAR_WLM );
}

uno::Any SvxUnoFontDescriptor::getPropertyDefault( SfxItemPool* pPool )
{
    SfxItemSet aSet( *pPool, EE_CHAR_FONTINFO, EE_CHAR_FONTINFO,
                             EE_CHAR_FONTHEIGHT, EE_CHAR_FONTHEIGHT,
                             EE_CHAR_ITALIC, EE_CHAR_ITALIC,
                             EE_CHAR_UNDERLINE, EE_CHAR_UNDERLINE,
                             EE_CHAR_WEIGHT, EE_CHAR_WEIGHT,
                             EE_CHAR_STRIKEOUT, EE_CHAR_STRIKEOUT,
                             EE_CHAR_WLM, EE_CHAR_WLM, 0 );

    uno::Any aAny;

    if(!pPool->IsWhich(EE_CHAR_FONTINFO)||
        !pPool->IsWhich(EE_CHAR_FONTHEIGHT)||
        !pPool->IsWhich(EE_CHAR_ITALIC)||
        !pPool->IsWhich(EE_CHAR_UNDERLINE)||
        !pPool->IsWhich(EE_CHAR_WEIGHT)||
        !pPool->IsWhich(EE_CHAR_STRIKEOUT)||
        !pPool->IsWhich(EE_CHAR_WLM))
        return aAny;

    aSet.Put(pPool->GetDefaultItem(EE_CHAR_FONTINFO));
    aSet.Put(pPool->GetDefaultItem(EE_CHAR_FONTHEIGHT));
    aSet.Put(pPool->GetDefaultItem(EE_CHAR_ITALIC));
    aSet.Put(pPool->GetDefaultItem(EE_CHAR_UNDERLINE));
    aSet.Put(pPool->GetDefaultItem(EE_CHAR_WEIGHT));
    aSet.Put(pPool->GetDefaultItem(EE_CHAR_STRIKEOUT));
    aSet.Put(pPool->GetDefaultItem(EE_CHAR_WLM));

    awt::FontDescriptor aDesc;

    FillFromItemSet( aSet, aDesc );

    aAny <<= aDesc;

    return aAny;
}



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
