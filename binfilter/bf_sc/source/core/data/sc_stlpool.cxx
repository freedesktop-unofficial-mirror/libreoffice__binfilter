/*************************************************************************
 *
 *  $RCSfile: sc_stlpool.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:26:08 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifdef PCH
#include "core_pch.hxx"
#endif

#pragma hdrstop

//------------------------------------------------------------------------

#include "scitems.hxx"
#include <bf_svx/eeitem.hxx>
#define ITEMID_FIELD EE_FEATURE_FIELD

#include <bf_svx/algitem.hxx>
#include <bf_svx/boxitem.hxx>
#include <bf_svx/brshitem.hxx>
#include <bf_svx/editdata.hxx>
#include <bf_svx/editeng.hxx>
#include <bf_svx/editobj.hxx>
#include <bf_svx/fhgtitem.hxx>
#include <bf_svx/flditem.hxx>
#include <bf_svx/fontitem.hxx>
#include <bf_svx/pageitem.hxx>
#include <bf_svx/postitem.hxx>
#include <bf_svx/udlnitem.hxx>
#include <bf_svx/wghtitem.hxx>
#include <svtools/itemset.hxx>
#include <svtools/zforlist.hxx>
#include <unotools/charclass.hxx>
#include <vcl/fontcvt.hxx>
#include <vcl/outdev.hxx>
#include <vcl/svapp.hxx>

#include "bf_sc.hrc"
#include "attrib.hxx"
#include "global.hxx"
#include "globstr.hrc"
#include "document.hxx"
#include "docpool.hxx"
#include "stlpool.hxx"
#include "stlsheet.hxx"
#include "rechead.hxx"
#include "editutil.hxx"
#include "patattr.hxx"
namespace binfilter {


//========================================================================

/*N*/ ScStyleSheetPool::ScStyleSheetPool( SfxItemPool&  rPool,
/*N*/                                   ScDocument*     pDocument )
/*N*/   :   SfxStyleSheetPool( rPool ),
/*N*/       pActualStyleSheet( NULL ),
/*N*/       pDoc( pDocument ),
/*N*/       pForceStdName( NULL )
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

/*N*/ __EXPORT ScStyleSheetPool::~ScStyleSheetPool()
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void ScStyleSheetPool::SetDocument( ScDocument* pDocument )
/*N*/ {
/*N*/   pDoc = pDocument;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void ScStyleSheetPool::SetForceStdName( const String* pSet )
/*N*/ {
/*N*/   pForceStdName = pSet;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxStyleSheetBase& ScStyleSheetPool::Make( const String& rName,
/*N*/                           SfxStyleFamily eFam, USHORT mask, USHORT nPos )
/*N*/ {
/*N*/   //  When updating styles from a template, Office 5.1 sometimes created
/*N*/   //  files with multiple default styles.
/*N*/   //  Create new styles in that case:
/*N*/
/*N*/   //! only when loading?
/*N*/
/*N*/   if ( rName.EqualsAscii(STRING_STANDARD) && Find( rName, eFam ) != NULL )
/*N*/   {
/*?*/       DBG_ERROR("renaming additional default style");
/*?*/       long nCount = aStyles.Count();
/*?*/       for ( long nAdd = 1; nAdd <= nCount; nAdd++ )
/*?*/       {
/*?*/           String aNewName = ScGlobal::GetRscString(STR_STYLENAME_STANDARD);
/*?*/           aNewName += String::CreateFromInt32( nAdd );
/*?*/           if ( Find( aNewName, eFam ) == NULL )
/*?*/               return SfxStyleSheetPool::Make( aNewName, eFam, mask, nPos );
/*?*/       }
/*N*/   }
/*N*/
/*N*/   return SfxStyleSheetPool::Make( rName, eFam, mask, nPos );
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxStyleSheetBase* __EXPORT ScStyleSheetPool::Create(
/*N*/                                           const String&   rName,
/*N*/                                           SfxStyleFamily  eFamily,
/*N*/                                           USHORT          nMask )
/*N*/ {
/*N*/   ScStyleSheet* pSheet = new ScStyleSheet( rName, *this, eFamily, nMask );
/*N*/   if ( eFamily == SFX_STYLE_FAMILY_PARA && ScGlobal::GetRscString(STR_STYLENAME_STANDARD) != rName )
/*N*/       pSheet->SetParent( ScGlobal::GetRscString(STR_STYLENAME_STANDARD) );
/*N*/
/*N*/   return pSheet;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SfxStyleSheetBase* __EXPORT ScStyleSheetPool::Create( const SfxStyleSheetBase& rStyle )
/*N*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001 DBG_ASSERT( rStyle.ISA(ScStyleSheet), "Invalid StyleSheet-class! :-/" );
//STRIP001  return new ScStyleSheet( (const ScStyleSheet&) rStyle );
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 void __EXPORT ScStyleSheetPool::Erase( SfxStyleSheetBase* pStyle )
//STRIP001 {
//STRIP001  if ( pStyle )
//STRIP001  {
//STRIP001      DBG_ASSERT( IS_SET( SFXSTYLEBIT_USERDEF, pStyle->GetMask() ),
//STRIP001                  "SFXSTYLEBIT_USERDEF not set!" );
//STRIP001
//STRIP001      ((ScDocumentPool&)rPool).StyleDeleted((ScStyleSheet*)pStyle);
//STRIP001      SfxStyleSheetPool::Erase(pStyle);
//STRIP001  }
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 void ScStyleSheetPool::CopyStyleFrom( ScStyleSheetPool* pSrcPool,
//STRIP001                                      const String& rName, SfxStyleFamily eFamily )
//STRIP001 {
//STRIP001  //  this ist Dest-Pool
//STRIP001
//STRIP001  SfxStyleSheetBase* pStyleSheet = pSrcPool->Find( rName, eFamily );
//STRIP001  if (pStyleSheet)
//STRIP001  {
//STRIP001      const SfxItemSet& rSourceSet = pStyleSheet->GetItemSet();
//STRIP001      SfxStyleSheetBase* pDestSheet = Find( rName, eFamily );
//STRIP001      if (!pDestSheet)
//STRIP001          pDestSheet = &Make( rName, eFamily );
//STRIP001      SfxItemSet& rDestSet = pDestSheet->GetItemSet();
//STRIP001      rDestSet.PutExtended( rSourceSet, SFX_ITEM_DONTCARE, SFX_ITEM_DEFAULT );
//STRIP001
//STRIP001      if ( eFamily == SFX_STYLE_FAMILY_PAGE )
//STRIP001      {
//STRIP001          //  Set-Items
//STRIP001
//STRIP001          const SfxPoolItem* pItem;
//STRIP001
//STRIP001          if ( rSourceSet.GetItemState( ATTR_PAGE_HEADERSET, FALSE, &pItem ) == SFX_ITEM_SET )
//STRIP001          {
//STRIP001              const SfxItemSet& rSrcSub = ((const SvxSetItem*) pItem)->GetItemSet();
//STRIP001              SfxItemSet aDestSub( *rDestSet.GetPool(), rSrcSub.GetRanges() );
//STRIP001              aDestSub.PutExtended( rSrcSub, SFX_ITEM_DONTCARE, SFX_ITEM_DEFAULT );
//STRIP001              rDestSet.Put( SvxSetItem( ATTR_PAGE_HEADERSET, aDestSub ) );
//STRIP001          }
//STRIP001          if ( rSourceSet.GetItemState( ATTR_PAGE_FOOTERSET, FALSE, &pItem ) == SFX_ITEM_SET )
//STRIP001          {
//STRIP001              const SfxItemSet& rSrcSub = ((const SvxSetItem*) pItem)->GetItemSet();
//STRIP001              SfxItemSet aDestSub( *rDestSet.GetPool(), rSrcSub.GetRanges() );
//STRIP001              aDestSub.PutExtended( rSrcSub, SFX_ITEM_DONTCARE, SFX_ITEM_DEFAULT );
//STRIP001              rDestSet.Put( SvxSetItem( ATTR_PAGE_FOOTERSET, aDestSub ) );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//------------------------------------------------------------------------
//
//                      Standard-Vorlagen
//
//------------------------------------------------------------------------

#define SCSTR(id)   ScGlobal::GetRscString(id)

//STRIP001 void ScStyleSheetPool::CopyStdStylesFrom( ScStyleSheetPool* pSrcPool )
//STRIP001 {
//STRIP001  //  Default-Styles kopieren
//STRIP001
//STRIP001  CopyStyleFrom( pSrcPool, SCSTR(STR_STYLENAME_STANDARD),     SFX_STYLE_FAMILY_PARA );
//STRIP001  CopyStyleFrom( pSrcPool, SCSTR(STR_STYLENAME_RESULT),       SFX_STYLE_FAMILY_PARA );
//STRIP001  CopyStyleFrom( pSrcPool, SCSTR(STR_STYLENAME_RESULT1),      SFX_STYLE_FAMILY_PARA );
//STRIP001  CopyStyleFrom( pSrcPool, SCSTR(STR_STYLENAME_HEADLINE),     SFX_STYLE_FAMILY_PARA );
//STRIP001  CopyStyleFrom( pSrcPool, SCSTR(STR_STYLENAME_HEADLINE1),    SFX_STYLE_FAMILY_PARA );
//STRIP001  CopyStyleFrom( pSrcPool, SCSTR(STR_STYLENAME_STANDARD),     SFX_STYLE_FAMILY_PAGE );
//STRIP001  CopyStyleFrom( pSrcPool, SCSTR(STR_STYLENAME_REPORT),       SFX_STYLE_FAMILY_PAGE );
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ void lcl_CheckFont( SfxItemSet& rSet, LanguageType eLang, USHORT nFontType, USHORT nItemId )
/*N*/ {
/*N*/   if ( eLang != LANGUAGE_NONE && eLang != LANGUAGE_DONTKNOW && eLang != LANGUAGE_SYSTEM )
/*N*/   {
/*N*/       Font aDefFont = OutputDevice::GetDefaultFont( nFontType, eLang, DEFAULTFONT_FLAGS_ONLYONE );
/*N*/       SvxFontItem aNewItem( aDefFont.GetFamily(), aDefFont.GetName(), aDefFont.GetStyleName(),
/*N*/                             aDefFont.GetPitch(), aDefFont.GetCharSet(), nItemId );
/*N*/       if ( aNewItem != rSet.Get( nItemId ) )
/*N*/       {
/*?*/           // put item into style's ItemSet only if different from (static) default
/*?*/           rSet.Put( aNewItem );
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void ScStyleSheetPool::CreateStandardStyles()
/*N*/ {
/*N*/   //  neue Eintraege auch bei CopyStdStylesFrom eintragen
/*N*/
/*N*/   Color           aColBlack   ( COL_BLACK );
/*N*/   Color           aColGrey    ( COL_LIGHTGRAY );
/*N*/   String          aStr;
/*N*/   xub_StrLen      nStrLen;
/*N*/   String          aHelpFile;//XXX JN welcher Text???
/*N*/   ULONG           nNumFmt         = 0L;
/*N*/   SfxItemSet*     pSet            = NULL;
/*N*/   SfxItemSet*     pHFSet          = NULL;
/*N*/   SvxSetItem*     pHFSetItem      = NULL;
/*N*/   ScEditEngineDefaulter*  pEdEngine   = new ScEditEngineDefaulter( EditEngine::CreatePool(), TRUE );
/*N*/   pEdEngine->SetUpdateMode( FALSE );
/*N*/   EditTextObject* pEmptyTxtObj    = pEdEngine->CreateTextObject();
/*N*/   EditTextObject* pTxtObj         = NULL;
/*N*/   ScPageHFItem*   pHeaderItem     = new ScPageHFItem( ATTR_PAGE_HEADERRIGHT );
/*N*/   ScPageHFItem*   pFooterItem     = new ScPageHFItem( ATTR_PAGE_FOOTERRIGHT );
/*N*/   ScStyleSheet*   pSheet          = NULL;
/*N*/   SvxBorderLine   aBorderLine     ( &aColBlack, DEF_LINE_WIDTH_2 );
/*N*/   SvxBoxItem      aBoxItem        ( ATTR_BORDER );
/*N*/   SvxBoxInfoItem  aBoxInfoItem    ( ATTR_BORDER_INNER );
/*N*/
/*N*/   String aStrStandard = ScGlobal::GetRscString(STR_STYLENAME_STANDARD);
/*N*/
/*N*/   //==========================================================
/*N*/   // Zellformatvorlagen:
/*N*/   //==========================================================
/*N*/
/*N*/   //------------
/*N*/   // 1. Standard
/*N*/   //------------
/*N*/   pSheet = (ScStyleSheet*) &Make( aStrStandard, SFX_STYLE_FAMILY_PARA, SCSTYLEBIT_STANDARD );
/*N*/   pSheet->SetHelpId( aHelpFile, HID_SC_SHEET_CELL_STD );
/*N*/
/*N*/   //  if default fonts for the document's languages are different from the pool default,
/*N*/   //  put them into the default style
/*N*/   //  (not as pool defaults, because pool defaults can't be changed by the user)
/*N*/   //  the document languages must be set before creating the default styles!
/*N*/
/*N*/   pSet = &pSheet->GetItemSet();
/*N*/   LanguageType eLatin, eCjk, eCtl;
/*N*/   pDoc->GetLanguage( eLatin, eCjk, eCtl );
/*N*/
/*N*/   //  #108374# / #107782#: If the UI language is Korean, the default Latin font has to
/*N*/   //  be queried for Korean, too (the Latin language from the document can't be Korean).
/*N*/   //  This is the same logic as in SwDocShell::InitNew.
/*N*/   LanguageType eUiLanguage = Application::GetSettings().GetUILanguage();
/*N*/   switch( eUiLanguage )
/*N*/   {
/*N*/       case LANGUAGE_KOREAN:
/*N*/       case LANGUAGE_KOREAN_JOHAB:
/*N*/           eLatin = eUiLanguage;
/*N*/       break;
/*N*/   }
/*N*/
/*N*/   lcl_CheckFont( *pSet, eLatin, DEFAULTFONT_LATIN_SPREADSHEET, ATTR_FONT );
/*N*/   lcl_CheckFont( *pSet, eCjk, DEFAULTFONT_CJK_SPREADSHEET, ATTR_CJK_FONT );
/*N*/   lcl_CheckFont( *pSet, eCtl, DEFAULTFONT_CTL_SPREADSHEET, ATTR_CTL_FONT );
/*N*/
/*N*/   //------------
/*N*/   // 2. Ergebnis
/*N*/   //------------
/*N*/
/*N*/   pSheet = (ScStyleSheet*) &Make( SCSTR( STR_STYLENAME_RESULT ),
/*N*/                                   SFX_STYLE_FAMILY_PARA,
/*N*/                                   SCSTYLEBIT_STANDARD );
/*N*/   pSheet->SetParent( aStrStandard );
/*N*/   pSheet->SetHelpId( aHelpFile, HID_SC_SHEET_CELL_ERG );
/*N*/   pSet = &pSheet->GetItemSet();
/*N*/   pSet->Put( SvxWeightItem( WEIGHT_BOLD, ATTR_FONT_WEIGHT ) );
/*N*/   pSet->Put( SvxPostureItem( ITALIC_NORMAL, ATTR_FONT_POSTURE ) );
/*N*/   pSet->Put( SvxUnderlineItem( UNDERLINE_SINGLE, ATTR_FONT_UNDERLINE ) );
/*N*/
/*N*/   //-------------
/*N*/   // 3. Ergebnis1
/*N*/   //-------------
/*N*/
/*N*/   pSheet = (ScStyleSheet*) &Make( SCSTR( STR_STYLENAME_RESULT1 ),
/*N*/                                   SFX_STYLE_FAMILY_PARA,
/*N*/                                   SCSTYLEBIT_STANDARD );
/*N*/
/*N*/   pSheet->SetParent( SCSTR( STR_STYLENAME_RESULT ) );
/*N*/   pSheet->SetHelpId( aHelpFile, HID_SC_SHEET_CELL_ERG1 );
/*N*/   pSet = &pSheet->GetItemSet();
/*N*/   nNumFmt = pDoc->GetFormatTable()->GetStandardFormat( NUMBERFORMAT_CURRENCY,
/*N*/                                                       ScGlobal::eLnge );
/*N*/   pSet->Put( SfxUInt32Item( ATTR_VALUE_FORMAT, nNumFmt ) );
/*N*/
/*N*/   //----------------
/*N*/   // 4. Ueberschrift
/*N*/   //----------------
/*N*/
/*N*/   pSheet = (ScStyleSheet*) &Make( SCSTR( STR_STYLENAME_HEADLINE ),
/*N*/                                   SFX_STYLE_FAMILY_PARA,
/*N*/                                   SCSTYLEBIT_STANDARD );
/*N*/
/*N*/   pSheet->SetParent( aStrStandard );
/*N*/   pSheet->SetHelpId( aHelpFile, HID_SC_SHEET_CELL_UEB );
/*N*/   pSet = &pSheet->GetItemSet();
/*N*/   pSet->Put( SvxFontHeightItem( 320, 100, ATTR_FONT_HEIGHT ) ); // 16pt
/*N*/   pSet->Put( SvxWeightItem( WEIGHT_BOLD, ATTR_FONT_WEIGHT ) );
/*N*/   pSet->Put( SvxPostureItem( ITALIC_NORMAL, ATTR_FONT_POSTURE ) );
/*N*/   pSet->Put( SvxHorJustifyItem( SVX_HOR_JUSTIFY_CENTER, ATTR_HOR_JUSTIFY ) );
/*N*/
/*N*/   //-----------------
/*N*/   // 5. Ueberschrift1
/*N*/   //-----------------
/*N*/
/*N*/   pSheet = (ScStyleSheet*) &Make( SCSTR( STR_STYLENAME_HEADLINE1 ),
/*N*/                                   SFX_STYLE_FAMILY_PARA,
/*N*/                                   SCSTYLEBIT_STANDARD );
/*N*/
/*N*/   pSheet->SetParent( SCSTR( STR_STYLENAME_HEADLINE ) );
/*N*/   pSheet->SetHelpId( aHelpFile, HID_SC_SHEET_CELL_UEB1 );
/*N*/   pSet = &pSheet->GetItemSet();
/*N*/   pSet->Put( SvxOrientationItem( SVX_ORIENTATION_BOTTOMTOP, ATTR_ORIENTATION ) );
/*N*/
/*N*/   //==========================================================
/*N*/   // Seitenformat-Vorlagen:
/*N*/   //==========================================================
/*N*/
/*N*/   //------------
/*N*/   // 1. Standard
/*N*/   //------------
/*N*/
/*N*/   pSheet = (ScStyleSheet*) &Make( aStrStandard,
/*N*/                                   SFX_STYLE_FAMILY_PAGE,
/*N*/                                   SCSTYLEBIT_STANDARD );
/*N*/
/*N*/   pSet = &pSheet->GetItemSet();
/*N*/   pSheet->SetHelpId( aHelpFile, HID_SC_SHEET_PAGE_STD );
/*N*/
/*N*/   // Abstand der Kopf-/Fusszeilen von der Tabelle
/*N*/   pHFSetItem = new SvxSetItem( ((SvxSetItem&)pSet->Get( ATTR_PAGE_HEADERSET ) ) );
/*N*/   pSet->Put( *pHFSetItem, ATTR_PAGE_HEADERSET );
/*N*/   pSet->Put( *pHFSetItem, ATTR_PAGE_FOOTERSET );
/*N*/   DELETEZ( pHFSetItem );
/*N*/
/*N*/   //----------------------------------------
/*N*/   // Kopfzeile:
/*N*/   // [leer][\TABELLE\][leer]
/*N*/   //----------------------------------------
/*N*/   pEdEngine->SetText(EMPTY_STRING);
/*N*/   pEdEngine->QuickInsertField( SvxFieldItem(SvxTableField()), ESelection() );
/*N*/   pTxtObj = pEdEngine->CreateTextObject();
/*N*/   pHeaderItem->SetLeftArea  ( *pEmptyTxtObj );
/*N*/   pHeaderItem->SetCenterArea( *pTxtObj );
/*N*/   pHeaderItem->SetRightArea ( *pEmptyTxtObj );
/*N*/   pSet->Put( *pHeaderItem );
/*N*/   DELETEZ( pTxtObj );
/*N*/
/*N*/   //----------------------------------------
/*N*/   // Fusszeile:
/*N*/   // [leer][Seite \SEITE\][leer]
/*N*/   //----------------------------------------
/*N*/   aStr = SCSTR( STR_PAGE ); aStr += ' ';
/*N*/   pEdEngine->SetText( aStr );
/*N*/   nStrLen = aStr.Len();
/*N*/   pEdEngine->QuickInsertField( SvxFieldItem(SvxPageField()), ESelection(0,nStrLen,0,nStrLen) );
/*N*/   pTxtObj = pEdEngine->CreateTextObject();
/*N*/   pFooterItem->SetLeftArea  ( *pEmptyTxtObj );
/*N*/   pFooterItem->SetCenterArea( *pTxtObj );
/*N*/   pFooterItem->SetRightArea ( *pEmptyTxtObj );
/*N*/   pSet->Put( *pFooterItem );
/*N*/   DELETEZ( pTxtObj );
/*N*/
/*N*/   //----------
/*N*/   // 2. Report
/*N*/   //----------
/*N*/
/*N*/   pSheet = (ScStyleSheet*) &Make( SCSTR( STR_STYLENAME_REPORT ),
/*N*/                                   SFX_STYLE_FAMILY_PAGE,
/*N*/                                   SCSTYLEBIT_STANDARD );
/*N*/   pSet = &pSheet->GetItemSet();
/*N*/   pSheet->SetHelpId( aHelpFile, HID_SC_SHEET_PAGE_REP );
/*N*/
/*N*/   // Hintergrund und Umrandung
/*N*/   aBoxItem.SetLine( &aBorderLine, BOX_LINE_TOP );
/*N*/   aBoxItem.SetLine( &aBorderLine, BOX_LINE_BOTTOM );
/*N*/   aBoxItem.SetLine( &aBorderLine, BOX_LINE_LEFT );
/*N*/   aBoxItem.SetLine( &aBorderLine, BOX_LINE_RIGHT );
/*N*/   aBoxItem.SetDistance( 10 ); // 0.2mm
/*N*/   aBoxInfoItem.SetValid( VALID_TOP, TRUE );
/*N*/   aBoxInfoItem.SetValid( VALID_BOTTOM, TRUE );
/*N*/   aBoxInfoItem.SetValid( VALID_LEFT, TRUE );
/*N*/   aBoxInfoItem.SetValid( VALID_RIGHT, TRUE );
/*N*/   aBoxInfoItem.SetValid( VALID_DISTANCE, TRUE );
/*N*/   aBoxInfoItem.SetTable( FALSE );
/*N*/   aBoxInfoItem.SetDist ( TRUE );
/*N*/
/*N*/   pHFSetItem = new SvxSetItem( ((SvxSetItem&)pSet->Get( ATTR_PAGE_HEADERSET ) ) );
/*N*/   pHFSet = &(pHFSetItem->GetItemSet());
/*N*/
/*N*/   pHFSet->Put( SvxBrushItem( aColGrey, ATTR_BACKGROUND ) );
/*N*/   pHFSet->Put( aBoxItem );
/*N*/   pHFSet->Put( aBoxInfoItem );
/*N*/   pSet->Put( *pHFSetItem, ATTR_PAGE_HEADERSET );
/*N*/   pSet->Put( *pHFSetItem, ATTR_PAGE_FOOTERSET );
/*N*/   DELETEZ( pHFSetItem );
/*N*/
/*N*/   //----------------------------------------
/*N*/   // Kopfzeile:
/*N*/   // [\TABELLE\ (\DATEI\)][leer][\DATUM\, \ZEIT\]
/*N*/   //----------------------------------------
/*N*/   aStr = String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM(" ()"));
/*N*/   pEdEngine->SetText( aStr );
/*N*/   pEdEngine->QuickInsertField( SvxFieldItem(SvxFileField()), ESelection(0,2,0,2) );
/*N*/   pEdEngine->QuickInsertField( SvxFieldItem(SvxTableField()), ESelection() );
/*N*/   pTxtObj = pEdEngine->CreateTextObject();
/*N*/   pHeaderItem->SetLeftArea( *pTxtObj );
/*N*/   pHeaderItem->SetCenterArea( *pEmptyTxtObj );
/*N*/   DELETEZ( pTxtObj );
/*N*/   aStr = String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM(", "));
/*N*/   pEdEngine->SetText( aStr );
/*N*/   pEdEngine->QuickInsertField( SvxFieldItem(SvxTimeField()), ESelection(0,2,0,2) );
/*N*/   pEdEngine->QuickInsertField( SvxFieldItem(SvxDateField(Date(),SVXDATETYPE_VAR)),
/*N*/                                   ESelection() );
/*N*/   pTxtObj = pEdEngine->CreateTextObject();
/*N*/   pHeaderItem->SetRightArea( *pTxtObj );
/*N*/   DELETEZ( pTxtObj );
/*N*/   pSet->Put( *pHeaderItem );
/*N*/
/*N*/   //----------------------------------------
/*N*/   // Fusszeile:
/*N*/   // [leer][Seite: \SEITE\ / \SEITEN\][leer]
/*N*/   //----------------------------------------
/*N*/   aStr = SCSTR( STR_PAGE ); aStr += ' ';
/*N*/   nStrLen = aStr.Len();
/*N*/   aStr.AppendAscii(RTL_CONSTASCII_STRINGPARAM(" / "));
/*N*/   xub_StrLen nStrLen2 = aStr.Len();
/*N*/   pEdEngine->SetText( aStr );
/*N*/   pEdEngine->QuickInsertField( SvxFieldItem(SvxPagesField()), ESelection(0,nStrLen2,0,nStrLen2) );
/*N*/   pEdEngine->QuickInsertField( SvxFieldItem(SvxPageField()), ESelection(0,nStrLen,0,nStrLen) );
/*N*/   pTxtObj = pEdEngine->CreateTextObject();
/*N*/   pFooterItem->SetLeftArea  ( *pEmptyTxtObj );
/*N*/   pFooterItem->SetCenterArea( *pTxtObj );
/*N*/   pFooterItem->SetRightArea ( *pEmptyTxtObj );
/*N*/   pSet->Put( *pFooterItem );
/*N*/   DELETEZ( pTxtObj );
/*N*/
/*N*/   //----------------------------------------------------
/*N*/   DELETEZ( pEmptyTxtObj );
/*N*/   DELETEZ( pHeaderItem );
/*N*/   DELETEZ( pFooterItem );
/*N*/   DELETEZ( pEdEngine );
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void ScStyleSheetPool::UpdateStdNames()
/*N*/ {
/*N*/   //  Standard-Styles den richtigen Namen in der Programm-Sprache geben
/*N*/
/*N*/   String aHelpFile;
/*N*/   ULONG nCount = aStyles.Count();
/*N*/   for (ULONG n=0; n<nCount; n++)
/*N*/   {
/*N*/       SfxStyleSheetBase* pStyle = aStyles.GetObject(n);
/*N*/       if (!pStyle->IsUserDefined())
/*N*/       {
/*N*/           String aOldName     = pStyle->GetName();
/*N*/           ULONG nHelpId       = pStyle->GetHelpId( aHelpFile );
/*N*/           SfxStyleFamily eFam = pStyle->GetFamily();
/*N*/
/*N*/           BOOL bHelpKnown = TRUE;
/*N*/           String aNewName;
/*N*/           USHORT nNameId = 0;
/*N*/           switch( nHelpId )
/*N*/           {
/*N*/               case HID_SC_SHEET_CELL_STD:
/*N*/               case HID_SC_SHEET_PAGE_STD:  nNameId = STR_STYLENAME_STANDARD;  break;
/*N*/               case HID_SC_SHEET_CELL_ERG:  nNameId = STR_STYLENAME_RESULT;    break;
/*N*/               case HID_SC_SHEET_CELL_ERG1: nNameId = STR_STYLENAME_RESULT1;   break;
/*N*/               case HID_SC_SHEET_CELL_UEB:  nNameId = STR_STYLENAME_HEADLINE;  break;
/*N*/               case HID_SC_SHEET_CELL_UEB1: nNameId = STR_STYLENAME_HEADLINE1; break;
/*N*/               case HID_SC_SHEET_PAGE_REP:  nNameId = STR_STYLENAME_REPORT;    break;
/*N*/               default:
/*N*/                   // 0 oder falsche (alte) HelpId
/*N*/                   bHelpKnown = FALSE;
/*N*/           }
/*N*/           if (bHelpKnown)
/*N*/           {
/*N*/               if ( nNameId )
/*N*/                   aNewName = SCSTR( nNameId );
/*N*/
/*N*/               if ( aNewName.Len() && aNewName != aOldName && !Find( aNewName, eFam ) )
/*N*/               {
/*N*/                   DBG_TRACE( "Renaming style..." );
/*N*/
/*N*/                   pStyle->SetName( aNewName );    // setzt auch Parents um
/*N*/
/*N*/                   //  Styles in Patterns sind schon auf Pointer umgesetzt
/*N*/                   if (eFam == SFX_STYLE_FAMILY_PAGE)
/*N*/                   {
/*N*/                       //  Page-Styles umsetzen
/*N*/                       //  TableCount am Doc ist noch nicht initialisiert
/*N*/                       for (USHORT nTab=0; nTab<=MAXTAB && pDoc->HasTable(nTab); nTab++)
/*N*/                           if (pDoc->GetPageStyle(nTab) == aOldName)
/*?*/                               pDoc->SetPageStyle(nTab, aNewName);
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               //  wrong or no HelpId -> set new HelpId
/*N*/
/*N*/               //  no assertion for wrong HelpIds because this happens
/*N*/               //  with old files (#67218#) or with old files that were
/*N*/               //  saved again with a new version in a different language
/*N*/               //  (so SrcVersion doesn't help)
/*N*/
/*N*/               USHORT nNewId = 0;
/*N*/               if ( eFam == SFX_STYLE_FAMILY_PARA )
/*N*/               {
/*N*/                   if ( aOldName == SCSTR( STR_STYLENAME_STANDARD ) )
/*N*/                       nNewId = HID_SC_SHEET_CELL_STD;
/*N*/                   else if ( aOldName == SCSTR( STR_STYLENAME_RESULT ) )
/*N*/                       nNewId = HID_SC_SHEET_CELL_ERG;
/*N*/                   else if ( aOldName == SCSTR( STR_STYLENAME_RESULT1 ) )
/*N*/                       nNewId = HID_SC_SHEET_CELL_ERG1;
/*N*/                   else if ( aOldName == SCSTR( STR_STYLENAME_HEADLINE ) )
/*N*/                       nNewId = HID_SC_SHEET_CELL_UEB;
/*N*/                   else if ( aOldName == SCSTR( STR_STYLENAME_HEADLINE1 ) )
/*N*/                       nNewId = HID_SC_SHEET_CELL_UEB1;
/*N*/               }
/*N*/               else        // PAGE
/*N*/               {
/*N*/                   if ( aOldName == SCSTR( STR_STYLENAME_STANDARD ) )
/*N*/                       nNewId = HID_SC_SHEET_PAGE_STD;
/*N*/                   else if ( aOldName == SCSTR( STR_STYLENAME_REPORT ) )
/*N*/                       nNewId = HID_SC_SHEET_PAGE_REP;
/*N*/               }
/*N*/
/*N*/               if ( nNewId )               // new ID found from name -> set ID
/*N*/               {
/*?*/                   pStyle->SetHelpId( aHelpFile, nNewId );
/*N*/               }
/*N*/               else if ( nHelpId == 0 )    // no old and no new ID
/*N*/               {
/*N*/                   //  #71471# probably user defined style without SFXSTYLEBIT_USERDEF set
/*N*/                   //  (from StarCalc 1.0 import), fixed in src563 and above
/*N*/                   //! may also be default style from a different language
/*N*/                   //! test if name was generated from StarCalc 1.0 import?
/*N*/                   DBG_ASSERT(pDoc->GetSrcVersion() <= SC_SUBTOTAL_BUGFIX,
/*N*/                               "user defined style without SFXSTYLEBIT_USERDEF");
/*N*/                   pStyle->SetMask( pStyle->GetMask() | SFXSTYLEBIT_USERDEF );
/*N*/               }
/*N*/               // else: wrong old ID and no new ID found:
/*N*/               //  probably default style from a different language
/*N*/               //  -> leave unchanged (HelpId will be set if loaded with matching
/*N*/               //  language version later)
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 ScStyleSheet* ScStyleSheetPool::FindCaseIns( const String& rName, SfxStyleFamily eFam )
//STRIP001 {
//STRIP001  String aUpSearch = rName;
//STRIP001  ScGlobal::pCharClass->toUpper(aUpSearch);
//STRIP001
//STRIP001  ULONG nCount = aStyles.Count();
//STRIP001  for (ULONG n=0; n<nCount; n++)
//STRIP001  {
//STRIP001      SfxStyleSheetBase* pStyle = aStyles.GetObject(n);
//STRIP001      if ( pStyle->GetFamily() == eFam )
//STRIP001      {
//STRIP001          String aUpName = pStyle->GetName();
//STRIP001          ScGlobal::pCharClass->toUpper(aUpName);
//STRIP001          if (aUpName == aUpSearch)
//STRIP001              return (ScStyleSheet*)pStyle;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return NULL;
//STRIP001 }


/*N*/ void ScStyleSheetPool::ConvertFontsAfterLoad()
/*N*/ {
/*N*/     ScFontToSubsFontConverter_AutoPtr xFontConverter;
/*N*/     const ULONG nFlags = FONTTOSUBSFONT_IMPORT | FONTTOSUBSFONT_ONLYOLDSOSYMBOLFONTS;
/*N*/     SfxStyleSheetIterator aIter( this, SFX_STYLE_FAMILY_PARA );
/*N*/     for ( SfxStyleSheetBase* pStyle = aIter.First(); pStyle; pStyle = aIter.Next() )
/*N*/     {
/*N*/         const SfxPoolItem* pItem;
/*N*/         if( pStyle->GetItemSet().GetItemState( ATTR_FONT, FALSE, &pItem ) == SFX_ITEM_SET )
/*N*/         {
/*N*/             const SvxFontItem* pFontItem = (const SvxFontItem*) pItem;
/*N*/             const String& rOldName = pFontItem->GetFamilyName();
/*N*/             xFontConverter = CreateFontToSubsFontConverter( rOldName, nFlags );
/*N*/             if ( xFontConverter )
/*N*/             {
/*?*/                 String aNewName( GetFontToSubsFontName( xFontConverter ) );
/*?*/                 if ( aNewName != rOldName )
/*?*/                 {
/*?*/                     SvxFontItem aNewItem( pFontItem->GetFamily(), aNewName,
/*?*/                         pFontItem->GetStyleName(), pFontItem->GetPitch(),
/*?*/                         RTL_TEXTENCODING_DONTKNOW, ATTR_FONT );
/*?*/                     pStyle->GetItemSet().Put( aNewItem );
/*?*/                 }
/*N*/             }
/*N*/         }
/*N*/     }
/*N*/ }

}
