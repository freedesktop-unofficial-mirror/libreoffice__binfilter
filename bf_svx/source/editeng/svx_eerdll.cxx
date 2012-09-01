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

#include <bf_svtools/solar.hrc>
#include <eerdll.hxx>


#include <vcl/outdev.hxx>

#include <eerdll2.hxx>

#include "eeitem.hxx"
#include "eeitemid.hxx"

#include <lspcitem.hxx>
#include <adjitem.hxx>
#include <tstpitem.hxx>
#include <bulitem.hxx>



#include "itemdata.hxx"



#include <flditem.hxx>
#include <emphitem.hxx>
#include <scriptspaceitem.hxx>

#include <bf_svtools/itempool.hxx>

#include <vcl/virdev.hxx>

#include <vcl/svapp.hxx>

#include <akrnitem.hxx>
#include <cntritem.hxx>
#include <crsditem.hxx>
#include <cscoitem.hxx>
#include <escpitem.hxx>
#include <fhgtitem.hxx>
#include <fontitem.hxx>
#include <kernitem.hxx>
#include <lrspitem.hxx>
#include <postitem.hxx>
#include <shdditem.hxx>
#include <udlnitem.hxx>
#include <ulspitem.hxx>
#include <wghtitem.hxx>
#include <wrlmitem.hxx>
#include <numitem.hxx>
#include <langitem.hxx>
#include <charscaleitem.hxx>
#include <charreliefitem.hxx>
#include <frmdiritem.hxx>
#include <xmlcnitm.hxx>



#include <legacysmgr/legacy_binfilters_smgr.hxx>
namespace binfilter {

/*N*/ GlobalEditData::GlobalEditData()
/*N*/ {
/*N*/   ppDefItems = NULL;
/*N*/   pStdRefDevice = NULL;
/*N*/ }

/*N*/ GlobalEditData::~GlobalEditData()
/*N*/ {
/*N*/   // DefItems zerstoeren...
/*N*/   // Oder einfach stehen lassen, da sowieso App-Ende?!
/*N*/   if ( ppDefItems )
/*N*/       SfxItemPool::ReleaseDefaults( ppDefItems, EDITITEMCOUNT, TRUE );
/*N*/   delete pStdRefDevice;
/*N*/ }

/*N*/ SfxPoolItem** GlobalEditData::GetDefItems()
/*N*/ {
/*N*/   if ( !ppDefItems )
/*N*/   {
/*N*/       ppDefItems = new SfxPoolItem*[EDITITEMCOUNT];
/*N*/
/*N*/       // Absatzattribute:
/*N*/       SvxNumRule aTmpNumRule( 0, 0, FALSE );
/*N*/
/*N*/       ppDefItems[0]  = new SvxFrameDirectionItem( FRMDIR_HORI_LEFT_TOP, EE_PARA_WRITINGDIR );
/*N*/ #ifndef SVX_LIGHT
/*N*/       ppDefItems[1]  = new SvXMLAttrContainerItem( EE_PARA_XMLATTRIBS );
/*N*/ #else
/*N*/       ppDefItems[1]  = new SfxVoidItem( EE_PARA_XMLATTRIBS );
/*N*/ #endif // #ifndef SVX_LIGHT
/*N*/       ppDefItems[2]  = new SfxBoolItem( EE_PARA_HANGINGPUNCTUATION, FALSE );
/*N*/       ppDefItems[3]  = new SfxBoolItem( EE_PARA_FORBIDDENRULES, TRUE );
/*N*/       ppDefItems[4]  = new SvxScriptSpaceItem( TRUE, EE_PARA_ASIANCJKSPACING );
/*N*/       ppDefItems[5]  = new SvxNumBulletItem( aTmpNumRule, EE_PARA_NUMBULLET );
/*N*/       ppDefItems[6]  = new SfxBoolItem( EE_PARA_HYPHENATE, FALSE );
/*N*/       ppDefItems[7]  = new SfxUInt16Item( EE_PARA_BULLETSTATE, 0 );
/*N*/       ppDefItems[8]  = new SvxLRSpaceItem( EE_PARA_OUTLLRSPACE );
/*N*/       ppDefItems[9]  = new SfxUInt16Item( EE_PARA_OUTLLEVEL );
/*N*/       ppDefItems[10]  = new SvxBulletItem( EE_PARA_BULLET );
/*N*/       ppDefItems[11]  = new SvxLRSpaceItem( EE_PARA_LRSPACE );
/*N*/       ppDefItems[12]  = new SvxULSpaceItem( EE_PARA_ULSPACE );
/*N*/       ppDefItems[13]  = new SvxLineSpacingItem( 0, EE_PARA_SBL );
/*N*/       ppDefItems[14]  = new SvxAdjustItem( SVX_ADJUST_LEFT, EE_PARA_JUST );
/*N*/       ppDefItems[15]  = new SvxTabStopItem( 0, 0, SVX_TAB_ADJUST_LEFT, EE_PARA_TABS );
/*N*/
/*N*/       // Zeichenattribute:
/*N*/       ppDefItems[16]  = new SvxColorItem( Color( COL_AUTO ), EE_CHAR_COLOR );
/*N*/       ppDefItems[17]  = new SvxFontItem( EE_CHAR_FONTINFO );
/*N*/       ppDefItems[18] = new SvxFontHeightItem( 240, 100, EE_CHAR_FONTHEIGHT );
/*N*/       ppDefItems[19] = new SvxCharScaleWidthItem( 100, EE_CHAR_FONTWIDTH );
/*N*/       ppDefItems[20] = new SvxWeightItem( WEIGHT_NORMAL, EE_CHAR_WEIGHT );
/*N*/       ppDefItems[21] = new SvxUnderlineItem( UNDERLINE_NONE, EE_CHAR_UNDERLINE );
/*N*/       ppDefItems[22] = new SvxCrossedOutItem( STRIKEOUT_NONE, EE_CHAR_STRIKEOUT );
/*N*/       ppDefItems[23] = new SvxPostureItem( ITALIC_NONE, EE_CHAR_ITALIC );
/*N*/       ppDefItems[24] = new SvxContourItem( FALSE, EE_CHAR_OUTLINE );
/*N*/       ppDefItems[25] = new SvxShadowedItem( FALSE, EE_CHAR_SHADOW );
/*N*/       ppDefItems[26] = new SvxEscapementItem( 0, 100, EE_CHAR_ESCAPEMENT );
/*N*/       ppDefItems[27] = new SvxAutoKernItem( FALSE, EE_CHAR_PAIRKERNING );
/*N*/       ppDefItems[28] = new SvxKerningItem( 0, EE_CHAR_KERNING );
/*N*/       ppDefItems[29] = new SvxWordLineModeItem( FALSE, EE_CHAR_WLM );
/*N*/       ppDefItems[30] = new SvxLanguageItem( LANGUAGE_DONTKNOW, EE_CHAR_LANGUAGE );
/*N*/       ppDefItems[31] = new SvxLanguageItem( LANGUAGE_DONTKNOW, EE_CHAR_LANGUAGE_CJK );
/*N*/       ppDefItems[32] = new SvxLanguageItem( LANGUAGE_DONTKNOW, EE_CHAR_LANGUAGE_CTL );
/*N*/       ppDefItems[33] = new SvxFontItem( EE_CHAR_FONTINFO_CJK );
/*N*/       ppDefItems[34] = new SvxFontItem( EE_CHAR_FONTINFO_CTL );
/*N*/       ppDefItems[35] = new SvxFontHeightItem( 240, 100, EE_CHAR_FONTHEIGHT_CJK );
/*N*/       ppDefItems[36] = new SvxFontHeightItem( 240, 100, EE_CHAR_FONTHEIGHT_CTL );
/*N*/       ppDefItems[37] = new SvxWeightItem( WEIGHT_NORMAL, EE_CHAR_WEIGHT_CJK );
/*N*/       ppDefItems[38] = new SvxWeightItem( WEIGHT_NORMAL, EE_CHAR_WEIGHT_CTL );
/*N*/       ppDefItems[39] = new SvxPostureItem( ITALIC_NONE, EE_CHAR_ITALIC_CJK );
/*N*/       ppDefItems[40] = new SvxPostureItem( ITALIC_NONE, EE_CHAR_ITALIC_CTL );
/*N*/       ppDefItems[41] = new SvxEmphasisMarkItem( EMPHASISMARK_NONE, EE_CHAR_EMPHASISMARK );
/*N*/       ppDefItems[42] = new SvxCharReliefItem( RELIEF_NONE, EE_CHAR_RELIEF );
/*N*/       ppDefItems[43] = new SfxVoidItem( EE_CHAR_RUBI_DUMMY );
/*N*/ #ifndef SVX_LIGHT
/*N*/       ppDefItems[44] = new SvXMLAttrContainerItem( EE_CHAR_XMLATTRIBS );
/*N*/ #else
/*N*/         // no need to have alien attributes persistent
/*N*/       ppDefItems[44] = new SfxVoidItem( EE_CHAR_XMLATTRIBS );
/*N*/ #endif // #ifndef SVX_LIGHT
/*N*/
/*N*/       // Features
/*N*/       ppDefItems[45] = new SfxVoidItem( EE_FEATURE_TAB );
/*N*/       ppDefItems[46] = new SfxVoidItem( EE_FEATURE_LINEBR );
/*N*/       ppDefItems[47] = new SvxCharSetColorItem( Color( COL_RED ), RTL_TEXTENCODING_DONTKNOW, EE_FEATURE_NOTCONV );
/*N*/       ppDefItems[48] = new SvxFieldItem( SvxFieldData(), EE_FEATURE_FIELD );
/*N*/
/*N*/       DBG_ASSERT( EDITITEMCOUNT == 49, "ITEMCOUNT geaendert, DefItems nicht angepasst!" );
/*N*/
/*N*/       // Init DefFonts:
/*N*/       GetDefaultFonts( *(SvxFontItem*)ppDefItems[EE_CHAR_FONTINFO - EE_ITEMS_START],
/*N*/                        *(SvxFontItem*)ppDefItems[EE_CHAR_FONTINFO_CJK - EE_ITEMS_START],
/*N*/                        *(SvxFontItem*)ppDefItems[EE_CHAR_FONTINFO_CTL - EE_ITEMS_START] );
/*N*/   }
/*N*/
/*N*/   return ppDefItems;
/*N*/ }

/*N*/ rtl::Reference<SvxForbiddenCharactersTable> GlobalEditData::GetForbiddenCharsTable()
/*N*/ {
/*N*/   if ( !xForbiddenCharsTable.is() )
/*N*/   {
/*N*/       ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xMSF = ::legacy_binfilters::getLegacyProcessServiceFactory();
/*N*/       xForbiddenCharsTable = new SvxForbiddenCharactersTable( xMSF );
/*N*/   }
/*N*/   return xForbiddenCharsTable;
/*N*/ }


/*N*/ OutputDevice* GlobalEditData::GetStdRefDevice()
/*N*/ {
/*N*/   if ( !pStdRefDevice )
/*N*/   {
/*N*/       pStdRefDevice = new VirtualDevice;
/*N*/       pStdRefDevice->SetMapMode( MAP_TWIP );
/*N*/   }
/*N*/   return pStdRefDevice;
/*N*/ }

/*N*/ EditResId::EditResId( USHORT nId ):
/*N*/   ResId( nId, *EE_DLL()->GetResMgr() )
/*N*/ {
/*N*/ }

/*N*/ EditDLL::EditDLL()
/*N*/ {
/*N*/   pGlobalData = new GlobalEditData;
/*N*/   DBG_ASSERT( !*(EditDLL**)GetAppData(BF_SHL_EDIT), "Noch eine EditDLL ?!" );
/*N*/   *(EditDLL**)GetAppData(BF_SHL_EDIT) = this;
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/   ByteString aResMgrName( "bf_svx" );
/*N*/ #else
/*N*/   ByteString aResMgrName( "bf_svl" );
/*N*/ #endif
/*N*/   pResMgr = ResMgr::CreateResMgr(
/*N*/         aResMgrName.GetBuffer(), Application::GetSettings().GetUILocale() );
/*N*/ }

/*N*/ EditDLL::~EditDLL()
/*N*/ {
/*N*/   delete pResMgr;
/*N*/   delete pGlobalData;
/*N*/ }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
