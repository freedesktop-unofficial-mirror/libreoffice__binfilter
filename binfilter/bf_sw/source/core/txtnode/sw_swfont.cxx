/*************************************************************************
 *
 *  $RCSfile: sw_swfont.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:38:59 $
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


#pragma hdrstop

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _COM_SUN_STAR_I18N_SCRIPTTYPE_HDL_
#include <com/sun/star/i18n/ScriptType.hdl>
#endif
#ifndef _OUTDEV_HXX //autogen
#include <vcl/outdev.hxx>
#endif
#ifndef _UNOTOOLS_LOCALEDATAWRAPPER_HXX
#include <unotools/localedatawrapper.hxx>
#endif
#ifndef _UNO_LINGU_HXX
#include <bf_svx/unolingu.hxx>
#endif
#ifndef _SVX_BRSHITEM_HXX //autogen
#include <bf_svx/brshitem.hxx>
#endif
#ifndef _SVX_WRLMITEM_HXX //autogen
#include <bf_svx/wrlmitem.hxx>
#endif
#ifndef _SVX_BLNKITEM_HXX //autogen
#include <bf_svx/blnkitem.hxx>
#endif
#ifndef _SVX_NHYPITEM_HXX //autogen
#include <bf_svx/nhypitem.hxx>
#endif
#ifndef _SVX_KERNITEM_HXX //autogen
#include <bf_svx/kernitem.hxx>
#endif
#ifndef _SVX_CMAPITEM_HXX //autogen
#include <bf_svx/cmapitem.hxx>
#endif
#ifndef _SVX_LANGITEM_HXX //autogen
#include <bf_svx/langitem.hxx>
#endif
#ifndef _SVX_ESCPITEM_HXX //autogen
#include <bf_svx/escpitem.hxx>
#endif
#ifndef _SVX_AKRNITEM_HXX //autogen
#include <bf_svx/akrnitem.hxx>
#endif
#ifndef _SVX_SHDDITEM_HXX //autogen
#include <bf_svx/shdditem.hxx>
#endif
#ifndef _SVX_CHARRELIEFITEM_HXX
#include <bf_svx/charreliefitem.hxx>
#endif
#ifndef _SVX_CNTRITEM_HXX //autogen
#include <bf_svx/cntritem.hxx>
#endif
#ifndef _SVX_COLRITEM_HXX //autogen
#include <bf_svx/colritem.hxx>
#endif
#ifndef _SVX_CSCOITEM_HXX //autogen
#include <bf_svx/cscoitem.hxx>
#endif
#ifndef _SVX_CRSDITEM_HXX //autogen
#include <bf_svx/crsditem.hxx>
#endif
#ifndef _SVX_UDLNITEM_HXX //autogen
#include <bf_svx/udlnitem.hxx>
#endif
#ifndef _SVX_WGHTITEM_HXX //autogen
#include <bf_svx/wghtitem.hxx>
#endif
#ifndef _SVX_POSTITEM_HXX //autogen
#include <bf_svx/postitem.hxx>
#endif
#ifndef _SVX_FHGTITEM_HXX //autogen
#include <bf_svx/fhgtitem.hxx>
#endif
#ifndef _SVX_FONTITEM_HXX //autogen
#include <bf_svx/fontitem.hxx>
#endif
#ifndef _SVX_EMPHITEM_HXX //autogen
#include <bf_svx/emphitem.hxx>
#endif
#ifndef _SVX_CHARSCALEITEM_HXX
#include <bf_svx/charscaleitem.hxx>
#endif
#ifndef _SVX_CHARROTATEITEM_HXX
#include <bf_svx/charrotateitem.hxx>
#endif
#ifndef _SVX_TWOLINESITEM_HXX
#include <bf_svx/twolinesitem.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif

#ifndef _CHARATR_HXX
#include <charatr.hxx>
#endif
#ifndef _SWATRSET_HXX //autogen
#include <swatrset.hxx>
#endif
#ifndef _VIEWSH_HXX
#include <viewsh.hxx>       // Bildschirmabgleich
#endif
#ifndef _SWFONT_HXX
#include <swfont.hxx>
#endif
#ifndef _FNTCACHE_HXX
#include <fntcache.hxx>     // FontCache
#endif
#ifndef _DRAWFONT_HXX
#include <drawfont.hxx>     // SwDrawTextInfo
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>       // SwTxtFrm
#endif

#if defined(WIN) || defined(WNT) || defined(PM2)
#define FNT_LEADING_HACK
#endif

#if defined(WIN) || defined(WNT)
#define FNT_ATM_HACK
#endif

#ifndef PRODUCT
// globale Variable
SvStatistics aSvStat;
#endif

using namespace ::com::sun::star::i18n::ScriptType;

/************************************************************************
 * Hintergrundbrush setzen, z.B. bei Zeichenvorlagen
 ***********************************************************************/

/*N*/ void SwFont::SetBackColor( Color* pNewColor )
/*N*/ {
/*N*/   delete pBackColor;
/*N*/   pBackColor = pNewColor;
/*N*/   bFntChg = TRUE;
/*N*/   aSub[SW_LATIN].pMagic = aSub[SW_CJK].pMagic = aSub[SW_CTL].pMagic = 0;
/*N*/ }

/************************************************************************
 * Hintergrundbrush setzen,
 * die alte Brush wird _nicht_ destruiert, sondern ist der Rueckgabewert.
 ***********************************************************************/

//STRIP001 Color* SwFont::XChgBackColor( Color* pNewColor )
//STRIP001 {
//STRIP001  Color* pRet = pBackColor;
//STRIP001  pBackColor = pNewColor;
//STRIP001  bFntChg = TRUE;
//STRIP001  aSub[SW_LATIN].pMagic = aSub[SW_CJK].pMagic = aSub[SW_CTL].pMagic = 0;
//STRIP001  return pRet;
//STRIP001 }


// maps directions for vertical layout
/*N*/ USHORT MapDirection( USHORT nDir, const BOOL bVertFormat )
/*N*/ {
/*N*/     if ( bVertFormat )
/*N*/     {
/*N*/         switch ( nDir )
/*N*/         {
/*N*/         case 0 :
/*N*/             nDir = 2700;
/*N*/             break;
/*N*/         case 900 :
/*N*/             nDir = 0;
/*N*/             break;
/*N*/         case 2700 :
/*N*/             nDir = 1800;
/*N*/             break;
/*N*/ #if OSL_DEBUG_LEVEL > 1
/*N*/         default :
/*N*/             ASSERT( sal_False, "Unsupported direction" );
/*N*/             break;
/*N*/ #endif
/*N*/         }
/*N*/     }
/*N*/     return nDir;
/*N*/ }

// maps the absolute direction set at the font to its logical conterpart
// in the rotated environment
/*N*/ USHORT UnMapDirection( USHORT nDir, const BOOL bVertFormat )
/*N*/ {
/*N*/     if ( bVertFormat )
/*N*/     {
/*?*/         switch ( nDir )
/*?*/         {
/*?*/         case 0 :
/*?*/             nDir = 900;
/*?*/             break;
/*?*/         case 1800 :
/*?*/             nDir = 2700;
/*?*/             break;
/*?*/         case 2700 :
/*?*/             nDir = 0;
/*?*/             break;
/*?*/ #if OSL_DEBUG_LEVEL > 1
/*?*/         default :
/*?*/             ASSERT( sal_False, "Unsupported direction" );
/*?*/             break;
/*?*/ #endif
/*?*/         }
/*N*/     }
/*N*/     return nDir;
/*N*/ }

/*N*/ USHORT SwFont::GetOrientation( const BOOL bVertFormat ) const
/*N*/ {
/*N*/     return UnMapDirection( aSub[nActual].GetOrientation(), bVertFormat );
/*N*/ }

/*N*/ void SwFont::SetVertical( USHORT nDir, const BOOL bVertFormat )
/*N*/ {
/*N*/     // map direction if frame has vertical layout
/*N*/     nDir = MapDirection( nDir, bVertFormat );
/*N*/
/*N*/     if( nDir != aSub[0].GetOrientation() )
/*N*/   {
/*N*/       bFntChg = TRUE;
/*N*/       aSub[0].SetVertical( nDir, bVertFormat );
/*N*/         aSub[1].SetVertical( nDir, bVertFormat || nDir > 1000 );
/*N*/       aSub[2].SetVertical( nDir, bVertFormat );
/*N*/   }
/*N*/ }

/*************************************************************************
 Escapement:
    frEsc:  Fraction, Grad des Escapements
    Esc = resultierendes Escapement
    A1 = Original-Ascent            (nOrgAscent)
    A2 = verkleinerter Ascent       (nEscAscent)
    Ax = resultierender Ascent      (GetAscent())
    H1 = Original-Hoehe             (nOrgHeight)
    H2 = verkleinerter Hoehe        (nEscHeight)
    Hx = resultierender Hoehe       (GetHeight())
    Bx = resultierende Baseline fuer die Textausgabe (CalcPos())
         (Vorsicht: Y - A1!)

    Escapement:
        Esc = H1 * frEsc;

    Hochstellung:
        Ax = A2 + Esc;
        Hx = H2 + Esc;
        Bx = A1 - Esc;

    Tiefstellung:
        Ax = A1;
        Hx = A1 + Esc + (H2 - A2);
        Bx = A1 + Esc;

*************************************************************************/

/*************************************************************************
 *                  SwSubFont::CalcEscAscent( const USHORT nOldAscent )
 *************************************************************************/

// nEsc ist der Prozentwert
/*N*/ USHORT SwSubFont::CalcEscAscent( const USHORT nOldAscent ) const
/*N*/ {
/*N*/   if( DFLT_ESC_AUTO_SUPER != GetEscapement() &&
/*N*/       DFLT_ESC_AUTO_SUB != GetEscapement() )
/*N*/   {
/*N*/       const long nAscent = nOldAscent +
/*N*/                            ( (long) nOrgHeight * GetEscapement() ) / 100L;
/*N*/       if ( nAscent>0 )
/*N*/           return ( Max( USHORT (nAscent), nOrgAscent ));
/*N*/   }
/*N*/   return nOrgAscent;
/*N*/ }

/*************************************************************************
 *                      SwFont::SetDiffFnt()
 *************************************************************************/

/*N*/ void SwFont::SetDiffFnt( const SfxItemSet *pAttrSet, const SwDoc *pDoc )
/*N*/ {
/*N*/   delete pBackColor;
/*N*/   pBackColor = NULL;
/*N*/
/*N*/
/*N*/     if( pAttrSet )
/*N*/   {
/*N*/       const SfxPoolItem* pItem;
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_FONT,
/*N*/           TRUE, &pItem ))
/*N*/       {
/*N*/           const SvxFontItem *pFont = (const SvxFontItem *)pItem;
/*N*/           aSub[SW_LATIN].SetFamily( pFont->GetFamily() );
/*N*/           aSub[SW_LATIN].Font::SetName( pFont->GetFamilyName() );
/*N*/           aSub[SW_LATIN].Font::SetStyleName( pFont->GetStyleName() );
/*N*/           aSub[SW_LATIN].Font::SetPitch( pFont->GetPitch() );
/*N*/           aSub[SW_LATIN].Font::SetCharSet( pFont->GetCharSet() );
/*N*/       }
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_FONTSIZE,
/*N*/           TRUE, &pItem ))
/*N*/       {
/*N*/           const SvxFontHeightItem *pHeight = (const SvxFontHeightItem *)pItem;
/*N*/           aSub[SW_LATIN].SvxFont::SetPropr( 100 );
/*N*/           aSub[SW_LATIN].aSize = aSub[SW_LATIN].Font::GetSize();
/*N*/           Size aTmpSize = aSub[SW_LATIN].aSize;
/*N*/           aTmpSize.Height() = pHeight->GetHeight();
/*N*/           aSub[SW_LATIN].SetSize( aTmpSize );
/*N*/       }
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_POSTURE,
/*N*/           TRUE, &pItem ))
/*?*/           aSub[SW_LATIN].Font::SetItalic( ((SvxPostureItem*)pItem)->GetPosture() );
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_WEIGHT,
/*N*/           TRUE, &pItem ))
/*?*/           aSub[SW_LATIN].Font::SetWeight( ((SvxWeightItem*)pItem)->GetWeight() );
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_LANGUAGE,
/*N*/           TRUE, &pItem ))
/*?*/           aSub[SW_LATIN].SetLanguage( ((SvxLanguageItem*)pItem)->GetLanguage() );
/*N*/
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_CJK_FONT,
/*N*/           TRUE, &pItem ))
/*N*/       {
/*?*/           const SvxFontItem *pFont = (const SvxFontItem *)pItem;
/*?*/           aSub[SW_CJK].SetFamily( pFont->GetFamily() );
/*?*/           aSub[SW_CJK].Font::SetName( pFont->GetFamilyName() );
/*?*/           aSub[SW_CJK].Font::SetStyleName( pFont->GetStyleName() );
/*?*/           aSub[SW_CJK].Font::SetPitch( pFont->GetPitch() );
/*?*/           aSub[SW_CJK].Font::SetCharSet( pFont->GetCharSet() );
/*N*/       }
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_CJK_FONTSIZE,
/*N*/           TRUE, &pItem ))
/*N*/       {
/*?*/           const SvxFontHeightItem *pHeight = (const SvxFontHeightItem *)pItem;
/*?*/           aSub[SW_CJK].SvxFont::SetPropr( 100 );
/*?*/           aSub[SW_CJK].aSize = aSub[SW_CJK].Font::GetSize();
/*?*/           Size aTmpSize = aSub[SW_CJK].aSize;
/*?*/           aTmpSize.Height() = pHeight->GetHeight();
/*?*/           aSub[SW_CJK].SetSize( aTmpSize );
/*N*/       }
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_CJK_POSTURE,
/*N*/           TRUE, &pItem ))
/*?*/           aSub[SW_CJK].Font::SetItalic( ((SvxPostureItem*)pItem)->GetPosture() );
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_CJK_WEIGHT,
/*N*/           TRUE, &pItem ))
/*?*/           aSub[SW_CJK].Font::SetWeight( ((SvxWeightItem*)pItem)->GetWeight() );
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_CJK_LANGUAGE,
/*N*/           TRUE, &pItem ))
/*N*/       {
/*?*/           LanguageType eNewLang = ((SvxLanguageItem*)pItem)->GetLanguage();
/*?*/           aSub[SW_CJK].SetLanguage( eNewLang );
/*?*/           aSub[SW_LATIN].SetCJKContextLanguage( eNewLang );
/*?*/           aSub[SW_CJK].SetCJKContextLanguage( eNewLang );
/*?*/           aSub[SW_CTL].SetCJKContextLanguage( eNewLang );
/*N*/       }
/*N*/
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_CTL_FONT,
/*N*/           TRUE, &pItem ))
/*N*/       {
/*?*/           const SvxFontItem *pFont = (const SvxFontItem *)pItem;
/*?*/           aSub[SW_CTL].SetFamily( pFont->GetFamily() );
/*?*/           aSub[SW_CTL].Font::SetName( pFont->GetFamilyName() );
/*?*/           aSub[SW_CTL].Font::SetStyleName( pFont->GetStyleName() );
/*?*/           aSub[SW_CTL].Font::SetPitch( pFont->GetPitch() );
/*?*/           aSub[SW_CTL].Font::SetCharSet( pFont->GetCharSet() );
/*N*/       }
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_CTL_FONTSIZE,
/*N*/           TRUE, &pItem ))
/*N*/       {
/*?*/           const SvxFontHeightItem *pHeight = (const SvxFontHeightItem *)pItem;
/*?*/           aSub[SW_CTL].SvxFont::SetPropr( 100 );
/*?*/           aSub[SW_CTL].aSize = aSub[SW_CTL].Font::GetSize();
/*?*/           Size aTmpSize = aSub[SW_CTL].aSize;
/*?*/           aTmpSize.Height() = pHeight->GetHeight();
/*?*/           aSub[SW_CTL].SetSize( aTmpSize );
/*N*/       }
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_CTL_POSTURE,
/*N*/           TRUE, &pItem ))
/*?*/           aSub[SW_CTL].Font::SetItalic( ((SvxPostureItem*)pItem)->GetPosture() );
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_CTL_WEIGHT,
/*N*/           TRUE, &pItem ))
/*?*/           aSub[SW_CTL].Font::SetWeight( ((SvxWeightItem*)pItem)->GetWeight() );
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_CTL_LANGUAGE,
/*N*/           TRUE, &pItem ))
/*?*/           aSub[SW_CTL].SetLanguage( ((SvxLanguageItem*)pItem)->GetLanguage() );
/*N*/
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_UNDERLINE,
/*N*/           TRUE, &pItem ))
/*N*/       {
/*N*/           SetUnderline( ((SvxUnderlineItem*)pItem)->GetUnderline() );
/*N*/           SetUnderColor( ((SvxUnderlineItem*)pItem)->GetColor() );
/*N*/       }
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_CROSSEDOUT,
/*N*/           TRUE, &pItem ))
/*?*/           SetStrikeout( ((SvxCrossedOutItem*)pItem)->GetStrikeout() );
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_COLOR,
/*N*/           TRUE, &pItem ))
/*N*/           SetColor( ((SvxColorItem*)pItem)->GetValue() );
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_EMPHASIS_MARK,
/*N*/           TRUE, &pItem ))
/*?*/           SetEmphasisMark( ((SvxEmphasisMarkItem*)pItem)->GetEmphasisMark() );
/*N*/
/*N*/       SetTransparent( TRUE );
/*N*/       SetAlign( ALIGN_BASELINE );
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_CONTOUR,
/*N*/           TRUE, &pItem ))
/*?*/           SetOutline( ((SvxContourItem*)pItem)->GetValue() );
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_SHADOWED,
/*N*/           TRUE, &pItem ))
/*?*/           SetShadow( ((SvxShadowedItem*)pItem)->GetValue() );
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_RELIEF,
/*N*/           TRUE, &pItem ))
/*?*/           SetRelief( (FontRelief)((SvxCharReliefItem*)pItem)->GetValue() );
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_SHADOWED,
/*N*/           TRUE, &pItem ))
/*N*/           SetPropWidth(((SvxShadowedItem*)pItem)->GetValue() ? 50 : 100 );
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_AUTOKERN,
/*N*/           TRUE, &pItem ))
/*N*/       {
/*?*/           if( ((SvxAutoKernItem*)pItem)->GetValue() )
/*?*/               SetAutoKern( ( !pDoc || !pDoc->IsKernAsianPunctuation() ) ?
/*?*/                        KERNING_FONTSPECIFIC : KERNING_ASIAN );
/*?*/           else
/*?*/               SetAutoKern( 0 );
/*N*/       }
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_WORDLINEMODE,
/*N*/           TRUE, &pItem ))
/*?*/           SetWordLineMode( ((SvxWordLineModeItem*)pItem)->GetValue() );
/*N*/
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_ESCAPEMENT,
/*N*/           TRUE, &pItem ))
/*N*/       {
/*N*/           const SvxEscapementItem *pEsc = (const SvxEscapementItem *)pItem;
/*N*/           SetEscapement( pEsc->GetEsc() );
/*N*/           if( aSub[SW_LATIN].IsEsc() )
/*N*/               SetProportion( pEsc->GetProp() );
/*N*/       }
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_CASEMAP,
/*N*/           TRUE, &pItem ))
/*N*/           SetCaseMap( ((SvxCaseMapItem*)pItem)->GetCaseMap() );
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_KERNING,
/*N*/           TRUE, &pItem ))
/*?*/           SetFixKerning( ((SvxKerningItem*)pItem)->GetValue() );
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_NOHYPHEN,
/*N*/           TRUE, &pItem ))
/*?*/           SetNoHyph( ((SvxNoHyphenItem*)pItem)->GetValue() );
/*N*/       if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_BLINK,
/*N*/           TRUE, &pItem ))
/*?*/           SetBlink( ((SvxBlinkItem*)pItem)->GetValue() );
/*N*/         if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_ROTATE,
/*N*/             TRUE, &pItem ))
/*?*/             SetVertical( ((SvxCharRotateItem*)pItem)->GetValue() );
/*N*/         if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_BACKGROUND,
/*N*/             TRUE, &pItem ))
/*N*/             pBackColor = new Color( ((SvxBrushItem*)pItem)->GetColor() );
/*N*/         else
/*N*/             pBackColor = NULL;
/*N*/         const SfxPoolItem* pTwoLinesItem = 0;
/*N*/         if( SFX_ITEM_SET ==
/*N*/                 pAttrSet->GetItemState( RES_CHRATR_TWO_LINES, TRUE, &pTwoLinesItem ))
/*?*/             if ( ((SvxTwoLinesItem*)pTwoLinesItem)->GetValue() )
/*?*/                 SetVertical( 0 );
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       Invalidate();
/*?*/       bNoHyph = FALSE;
/*?*/       bBlink = FALSE;
/*N*/   }
/*N*/   bPaintBlank = FALSE;
/*N*/   bPaintWrong = FALSE;
/*N*/   ASSERT( aSub[SW_LATIN].IsTransparent(), "SwFont: Transparent revolution" );
/*N*/ }

/*************************************************************************
 *                      class SwFont
 *************************************************************************/

/*N*/ SwFont::SwFont( const SwFont &rFont )
/*N*/ {
/*N*/   aSub[SW_LATIN] = rFont.aSub[SW_LATIN];
/*N*/   aSub[SW_CJK] = rFont.aSub[SW_CJK];
/*N*/   aSub[SW_CTL] = rFont.aSub[SW_CTL];
/*N*/     nActual = rFont.nActual;
/*N*/   pBackColor = rFont.pBackColor ? new Color( *rFont.pBackColor ) : NULL;
/*N*/   aUnderColor = rFont.GetUnderColor();
/*N*/   nToxCnt = nRefCnt = 0;
/*N*/   bFntChg = rFont.bFntChg;
/*N*/   bOrgChg = rFont.bOrgChg;
/*N*/   bPaintBlank = rFont.bPaintBlank;
/*N*/   bPaintWrong = FALSE;
/*N*/   bURL = rFont.bURL;
/*N*/   bGreyWave = rFont.bGreyWave;
/*N*/   bNoColReplace = rFont.bNoColReplace;
/*N*/   bNoHyph = rFont.bNoHyph;
/*N*/   bBlink = rFont.bBlink;
/*N*/ }

/*N*/ SwFont::SwFont( const SwAttrSet* pAttrSet, const SwDoc *pDoc )
/*N*/ {
/*N*/     nActual = SW_LATIN;
/*N*/     nToxCnt = nRefCnt = 0;
/*N*/     bPaintBlank = FALSE;
/*N*/     bPaintWrong = FALSE;
/*N*/     bURL = FALSE;
/*N*/     bGreyWave = FALSE;
/*N*/     bNoColReplace = FALSE;
/*N*/     bNoHyph = pAttrSet->GetNoHyphenHere().GetValue();
/*N*/     bBlink = pAttrSet->GetBlink().GetValue();
/*N*/     {
/*N*/         const SvxFontItem& rFont = pAttrSet->GetFont();
/*N*/         aSub[SW_LATIN].SetFamily( rFont.GetFamily() );
/*N*/         aSub[SW_LATIN].SetName( rFont.GetFamilyName() );
/*N*/         aSub[SW_LATIN].SetStyleName( rFont.GetStyleName() );
/*N*/         aSub[SW_LATIN].SetPitch( rFont.GetPitch() );
/*N*/         aSub[SW_LATIN].SetCharSet( rFont.GetCharSet() );
/*N*/         aSub[SW_LATIN].SvxFont::SetPropr( 100 );   // 100% der FontSize
/*N*/         Size aTmpSize = aSub[SW_LATIN].aSize;
/*N*/         aTmpSize.Height() = pAttrSet->GetSize().GetHeight();
/*N*/         aSub[SW_LATIN].SetSize( aTmpSize );
/*N*/         aSub[SW_LATIN].SetItalic( pAttrSet->GetPosture().GetPosture() );
/*N*/         aSub[SW_LATIN].SetWeight( pAttrSet->GetWeight().GetWeight() );
/*N*/         aSub[SW_LATIN].SetLanguage( pAttrSet->GetLanguage().GetLanguage() );
/*N*/     }
/*N*/
/*N*/     {
/*N*/         const SvxFontItem& rFont = pAttrSet->GetCJKFont();
/*N*/         aSub[SW_CJK].SetFamily( rFont.GetFamily() );
/*N*/         aSub[SW_CJK].SetName( rFont.GetFamilyName() );
/*N*/         aSub[SW_CJK].SetStyleName( rFont.GetStyleName() );
/*N*/         aSub[SW_CJK].SetPitch( rFont.GetPitch() );
/*N*/         aSub[SW_CJK].SetCharSet( rFont.GetCharSet() );
/*N*/         aSub[SW_CJK].SvxFont::SetPropr( 100 );   // 100% der FontSize
/*N*/         Size aTmpSize = aSub[SW_CJK].aSize;
/*N*/         aTmpSize.Height() = pAttrSet->GetCJKSize().GetHeight();
/*N*/         aSub[SW_CJK].SetSize( aTmpSize );
/*N*/         aSub[SW_CJK].SetItalic( pAttrSet->GetCJKPosture().GetPosture() );
/*N*/         aSub[SW_CJK].SetWeight( pAttrSet->GetCJKWeight().GetWeight() );
/*N*/         LanguageType eNewLang = pAttrSet->GetCJKLanguage().GetLanguage();
/*N*/         aSub[SW_CJK].SetLanguage( eNewLang );
/*N*/         aSub[SW_LATIN].SetCJKContextLanguage( eNewLang );
/*N*/         aSub[SW_CJK].SetCJKContextLanguage( eNewLang );
/*N*/         aSub[SW_CTL].SetCJKContextLanguage( eNewLang );
/*N*/     }
/*N*/
/*N*/     {
/*N*/         const SvxFontItem& rFont = pAttrSet->GetCTLFont();
/*N*/         aSub[SW_CTL].SetFamily( rFont.GetFamily() );
/*N*/         aSub[SW_CTL].SetName( rFont.GetFamilyName() );
/*N*/         aSub[SW_CTL].SetStyleName( rFont.GetStyleName() );
/*N*/         aSub[SW_CTL].SetPitch( rFont.GetPitch() );
/*N*/         aSub[SW_CTL].SetCharSet( rFont.GetCharSet() );
/*N*/         aSub[SW_CTL].SvxFont::SetPropr( 100 );   // 100% der FontSize
/*N*/         Size aTmpSize = aSub[SW_CTL].aSize;
/*N*/         aTmpSize.Height() = pAttrSet->GetCTLSize().GetHeight();
/*N*/         aSub[SW_CTL].SetSize( aTmpSize );
/*N*/         aSub[SW_CTL].SetItalic( pAttrSet->GetCTLPosture().GetPosture() );
/*N*/         aSub[SW_CTL].SetWeight( pAttrSet->GetCTLWeight().GetWeight() );
/*N*/         aSub[SW_CTL].SetLanguage( pAttrSet->GetCTLLanguage().GetLanguage() );
/*N*/     }
/*N*/
/*N*/     SetUnderline( pAttrSet->GetUnderline().GetUnderline() );
/*N*/     SetUnderColor( pAttrSet->GetUnderline().GetColor() );
/*N*/     SetEmphasisMark( pAttrSet->GetEmphasisMark().GetEmphasisMark() );
/*N*/     SetStrikeout( pAttrSet->GetCrossedOut().GetStrikeout() );
/*N*/     SetColor( pAttrSet->GetColor().GetValue() );
/*N*/     SetTransparent( TRUE );
/*N*/     SetAlign( ALIGN_BASELINE );
/*N*/     SetOutline( pAttrSet->GetContour().GetValue() );
/*N*/     SetShadow( pAttrSet->GetShadowed().GetValue() );
/*M*/     SetPropWidth( pAttrSet->GetCharScaleW().GetValue() );
/*N*/     SetRelief( (FontRelief)pAttrSet->GetCharRelief().GetValue() );
/*N*/   if( pAttrSet->GetAutoKern().GetValue() )
/*?*/       SetAutoKern( ( !pDoc || !pDoc->IsKernAsianPunctuation() ) ?
/*?*/                    KERNING_FONTSPECIFIC : KERNING_ASIAN );
/*N*/   else
/*N*/       SetAutoKern( 0 );
/*N*/     SetWordLineMode( pAttrSet->GetWordLineMode().GetValue() );
/*N*/     const SvxEscapementItem &rEsc = pAttrSet->GetEscapement();
/*N*/     SetEscapement( rEsc.GetEsc() );
/*N*/     if( aSub[SW_LATIN].IsEsc() )
/*?*/         SetProportion( rEsc.GetProp() );
/*N*/     SetCaseMap( pAttrSet->GetCaseMap().GetCaseMap() );
/*N*/     SetFixKerning( pAttrSet->GetKerning().GetValue() );
/*N*/     const SfxPoolItem* pItem;
/*N*/     if( SFX_ITEM_SET == pAttrSet->GetItemState( RES_CHRATR_BACKGROUND,
/*N*/         TRUE, &pItem ))
/*N*/         pBackColor = new Color( ((SvxBrushItem*)pItem)->GetColor() );
/*N*/     else
/*N*/         pBackColor = NULL;
/*N*/     const SvxTwoLinesItem& rTwoLinesItem = pAttrSet->Get2Lines();
/*N*/     if ( ! rTwoLinesItem.GetValue() )
/*N*/         SetVertical( pAttrSet->GetCharRotate().GetValue() );
/*N*/     else
/*?*/         SetVertical( 0 );
/*N*/ }

/*N*/ SwSubFont& SwSubFont::operator=( const SwSubFont &rFont )
/*N*/ {
/*N*/   SvxFont::operator=( rFont );
/*N*/   pMagic = rFont.pMagic;
/*N*/   nFntIndex = rFont.nFntIndex;
/*N*/   nOrgHeight = rFont.nOrgHeight;
/*N*/   nOrgAscent = rFont.nOrgAscent;
/*N*/   nPropWidth = rFont.nPropWidth;
/*N*/   aSize = rFont.aSize;
/*N*/   return *this;
/*N*/ }

/*N*/ SwFont& SwFont::operator=( const SwFont &rFont )
/*N*/ {
/*N*/   aSub[SW_LATIN] = rFont.aSub[SW_LATIN];
/*N*/   aSub[SW_CJK] = rFont.aSub[SW_CJK];
/*N*/   aSub[SW_CTL] = rFont.aSub[SW_CTL];
/*N*/     nActual = rFont.nActual;
/*N*/   delete pBackColor;
/*N*/   pBackColor = rFont.pBackColor ? new Color( *rFont.pBackColor ) : NULL;
/*N*/   aUnderColor = rFont.GetUnderColor();
/*N*/   nToxCnt = nRefCnt = 0;
/*N*/   bFntChg = rFont.bFntChg;
/*N*/   bOrgChg = rFont.bOrgChg;
/*N*/   bPaintBlank = rFont.bPaintBlank;
/*N*/   bPaintWrong = FALSE;
/*N*/   bURL = rFont.bURL;
/*N*/   bGreyWave = rFont.bGreyWave;
/*N*/   bNoColReplace = rFont.bNoColReplace;
/*N*/   bNoHyph = rFont.bNoHyph;
/*N*/   bBlink = rFont.bBlink;
/*N*/   return *this;
/*N*/ }

/*************************************************************************
 *                      SwFont::GoMagic()
 *************************************************************************/

/*N*/ void SwFont::GoMagic( ViewShell *pSh, BYTE nWhich )
/*N*/ {
/*N*/   SwFntAccess aFntAccess( aSub[nWhich].pMagic, aSub[nWhich].nFntIndex,
/*N*/                           &aSub[nWhich], pSh, TRUE );
/*N*/ }

/*************************************************************************
 *                      SwSubFont::IsSymbol()
 *************************************************************************/

/*N*/ BOOL SwSubFont::IsSymbol( ViewShell *pSh )
/*N*/ {
/*N*/   SwFntAccess aFntAccess( pMagic, nFntIndex, this, pSh, FALSE );
/*N*/   return aFntAccess.Get()->IsSymbol();
/*N*/ }

/*************************************************************************
 *                      SwSubFont::ChgFnt()
 *************************************************************************/

/*N*/ BOOL SwSubFont::ChgFnt( ViewShell *pSh, OutputDevice *pOut )
/*N*/ {
/*N*/   if ( pLastFont )
/*N*/       pLastFont->Unlock();
/*N*/   SwFntAccess aFntAccess( pMagic, nFntIndex, this, pSh, TRUE );
/*N*/   SV_STAT( nChangeFont );
/*N*/
/*N*/   pLastFont = aFntAccess.Get();
/*N*/
/*N*/   pLastFont->SetDevFont( pSh, pOut );
/*N*/
/*N*/   pLastFont->Lock();
/*N*/   return UNDERLINE_NONE != GetUnderline() || STRIKEOUT_NONE != GetStrikeout();
/*N*/ }

/*************************************************************************
 *                    SwFont::ChgPhysFnt()
 *************************************************************************/

/*N*/ void SwFont::ChgPhysFnt( ViewShell *pSh, OutputDevice *pOut )
/*N*/ {
/*N*/   ASSERT( pOut, "SwFont:;ChgPhysFnt, not OutDev." );
/*N*/
/*N*/   if( bOrgChg && aSub[nActual].IsEsc() )
/*N*/   {
/*N*/       const BYTE nOldProp = aSub[nActual].GetPropr();
/*N*/         SetProportion( 100 );
/*N*/       ChgFnt( pSh, pOut );
/*N*/       SwFntAccess aFntAccess( aSub[nActual].pMagic, aSub[nActual].nFntIndex,
/*N*/                               &aSub[nActual], pSh );
/*N*/       aSub[nActual].nOrgHeight = aFntAccess.Get()->GetHeight( pSh, pOut );
/*N*/       aSub[nActual].nOrgAscent = aFntAccess.Get()->GetAscent( pSh, pOut );
/*N*/       SetProportion( nOldProp );
/*N*/       bOrgChg = FALSE;
/*N*/   }
/*N*/
/*N*/   if( bFntChg )
/*N*/   {
/*N*/       ChgFnt( pSh, pOut );
/*N*/       bFntChg = bOrgChg;
/*N*/   }
/*N*/   if( pOut->GetTextLineColor() != aUnderColor )
/*?*/       pOut->SetTextLineColor( aUnderColor );
/*N*/ }

/*************************************************************************
 *                      SwFont::CalcEscHeight()
 *         Height = MaxAscent + MaxDescent
 *      MaxAscent = Max (T1_ascent, T2_ascent + (Esc * T1_height) );
 *     MaxDescent = Max (T1_height-T1_ascent,
 *                       T2_height-T2_ascent - (Esc * T1_height)
 *************************************************************************/

/*N*/ USHORT SwSubFont::CalcEscHeight( const USHORT nOldHeight,
/*N*/                             const USHORT nOldAscent  ) const
/*N*/ {
/*N*/   if( DFLT_ESC_AUTO_SUPER != GetEscapement() &&
/*N*/       DFLT_ESC_AUTO_SUB != GetEscapement() )
/*N*/   {
/*N*/       long nDescent = nOldHeight - nOldAscent -
/*N*/                            ( (long) nOrgHeight * GetEscapement() ) / 100L;
/*N*/       const USHORT nDesc = ( nDescent>0 ) ? Max ( USHORT(nDescent),
/*N*/                  USHORT(nOrgHeight - nOrgAscent) ) : nOrgHeight - nOrgAscent;
/*N*/       return ( nDesc + CalcEscAscent( nOldAscent ) );
/*N*/   }
/*N*/   return nOrgHeight;
/*N*/ }

/*N*/ short SwSubFont::_CheckKerning( )
/*N*/ {
/*N*/ #if OSL_DEBUG_LEVEL > 1
/*N*/   static nTst = 6;
/*N*/   short nKernx = - short( Font::GetSize().Height() / nTst );
/*N*/ #else
/*N*/   short nKernx = - short( Font::GetSize().Height() / 6 );
/*N*/ #endif
/*N*/   if ( nKernx < GetFixKerning() )
/*N*/       return GetFixKerning();
/*N*/   return nKernx;
/*N*/ }

/*************************************************************************
 *                    SwFont::GetLeading()
 *************************************************************************/

/*N*/ USHORT SwFont::GetLeading( ViewShell *pSh, const OutputDevice *pOut )
/*N*/ {
/*N*/     if( pSh && pSh->GetWin() )
/*N*/       return 0;
/*N*/   else
/*N*/   {
/*N*/       SwFntAccess aFntAccess( aSub[nActual].pMagic, aSub[nActual].nFntIndex,
/*N*/                               &aSub[nActual], pSh );
/*N*/       return aFntAccess.Get()->GetLeading();
/*N*/   }
/*N*/ }

/*************************************************************************
 *                    SwSubFont::GetAscent()
 *************************************************************************/

/*N*/ USHORT SwSubFont::GetAscent( ViewShell *pSh, const OutputDevice *pOut )
/*N*/ {
/*N*/   register USHORT nAscent;
/*N*/   SwFntAccess aFntAccess( pMagic, nFntIndex, this, pSh );
/*N*/   nAscent = aFntAccess.Get()->GetAscent( pSh, pOut );
/*N*/   if( GetEscapement() )
/*N*/       nAscent = CalcEscAscent( nAscent );
/*N*/   return nAscent;
/*N*/ }

/*************************************************************************
 *                    SwSubFont::GetHeight()
 *************************************************************************/

/*N*/ USHORT SwSubFont::GetHeight( ViewShell *pSh, const OutputDevice *pOut )
/*N*/ {
/*N*/   SV_STAT( nGetTextSize );
/*N*/   SwFntAccess aFntAccess( pMagic, nFntIndex, this, pSh );
/*N*/   const USHORT nHeight = aFntAccess.Get()->GetHeight( pSh, pOut );
/*N*/   if ( GetEscapement() )
/*N*/   {
/*N*/       const USHORT nAscent = aFntAccess.Get()->GetAscent( pSh, pOut );
/*N*/       return CalcEscHeight( nHeight, nAscent ); // + nLeading;
/*N*/   }
/*N*/   return nHeight; // + nLeading;
/*N*/ }

/*************************************************************************
 *                    SwSubFont::_GetTxtSize()
 *************************************************************************/
/*N*/ Size SwSubFont::_GetTxtSize( SwDrawTextInfo& rInf )
/*N*/ {
/*N*/   // Robust: Eigentlich sollte der Font bereits eingestellt sein, aber
/*N*/   // sicher ist sicher ...
/*N*/   if ( !pLastFont || pLastFont->GetOwner()!=pMagic ||
/*N*/        !IsSameInstance( rInf.GetpOut()->GetFont() ) )
/*N*/       ChgFnt( rInf.GetShell(), rInf.GetpOut() );
/*N*/
/*N*/   Size aTxtSize;
/*N*/   xub_StrLen nLn = ( rInf.GetLen() == STRING_LEN ? rInf.GetText().Len()
/*N*/                                                  : rInf.GetLen() );
/*N*/   rInf.SetLen( nLn );
/*N*/   if( IsCapital() && nLn )
/*N*/       aTxtSize = GetCapitalSize( rInf );
/*N*/   else
/*N*/   {
/*N*/       SV_STAT( nGetTextSize );
/*N*/       short nOldKern = rInf.GetKern();
/*N*/       const XubString &rOldTxt = rInf.GetText();
/*N*/       rInf.SetKern( CheckKerning() );
/*N*/       if ( !IsCaseMap() )
/*N*/           aTxtSize = pLastFont->GetTextSize( rInf );
/*N*/       else
/*N*/       {
/*N*/           String aTmp = CalcCaseMap( rInf.GetText() );
/*N*/           const XubString &rOldStr = rInf.GetText();
/*N*/           sal_Bool bCaseMapLengthDiffers(aTmp.Len() != rOldStr.Len());
/*N*/
/*N*/           if(bCaseMapLengthDiffers && rInf.GetLen())
/*N*/           {
/*N*/               // #108203#
/*N*/               // If the length of the original string and the CaseMapped one
/*N*/               // are different, it is necessary to handle the given text part as
/*N*/               // a single snippet since itÄs size may differ, too.
/*N*/               xub_StrLen nOldIdx(rInf.GetIdx());
/*N*/               xub_StrLen nOldLen(rInf.GetLen());
/*N*/               const XubString aSnippet(rOldStr, nOldIdx, nOldLen);
/*N*/               XubString aNewText(CalcCaseMap(aSnippet));
/*N*/
/*N*/               rInf.SetText( aNewText );
/*N*/               rInf.SetIdx( 0 );
/*N*/               rInf.SetLen( aNewText.Len() );
/*N*/
/*N*/               aTxtSize = pLastFont->GetTextSize( rInf );
/*N*/
/*N*/               rInf.SetIdx( nOldIdx );
/*N*/               rInf.SetLen( nOldLen );
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               rInf.SetText( aTmp );
/*N*/               aTxtSize = pLastFont->GetTextSize( rInf );
/*N*/           }
/*N*/
/*N*/           rInf.SetText( rOldStr );
/*N*/       }
/*N*/       rInf.SetKern( nOldKern );
/*N*/       rInf.SetText( rOldTxt );
/*N*/       // 15142: Ein Wort laenger als eine Zeile, beim Zeilenumbruch
/*N*/       //        hochgestellt, muss seine effektive Hoehe melden.
/*N*/       if( GetEscapement() )
/*N*/       {
/*N*/           const USHORT nAscent = pLastFont->GetAscent( rInf.GetShell(),
/*N*/                                                        rInf.GetpOut() );
/*N*/           aTxtSize.Height() =
/*N*/               (long)CalcEscHeight( (USHORT)aTxtSize.Height(), nAscent);
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return aTxtSize;
/*N*/ }

/*************************************************************************
 *                    SwFont::GetTxtBreak()
 *************************************************************************/

//STRIP001 xub_StrLen SwFont::GetTxtBreak( ViewShell *pSh,  const OutputDevice *pOut,
//STRIP001  const SwScriptInfo* pScript, const XubString &rTxt, long nTextWidth,
//STRIP001  const xub_StrLen nIdx, const xub_StrLen nLen )
//STRIP001 {
//STRIP001      ChgFnt( pSh, (OutputDevice *)pOut );
//STRIP001
//STRIP001  USHORT nTxtBreak = 0;
//STRIP001
//STRIP001  USHORT nLn = ( nLen == STRING_LEN ? rTxt.Len() : nLen );
//STRIP001  if( aSub[nActual].IsCapital() && nLn )
//STRIP001      nTxtBreak = GetCapitalBreak( pSh, pOut, pScript, rTxt, nTextWidth,
//STRIP001                                   0, nIdx, nLn );
//STRIP001  else
//STRIP001  {
//STRIP001      if ( !aSub[nActual].IsCaseMap() )
//STRIP001          nTxtBreak = pOut->GetTextBreak( rTxt, nTextWidth,
//STRIP001                                             nIdx, nLn, CheckKerning() );
//STRIP001      else
//STRIP001          nTxtBreak = pOut->GetTextBreak( aSub[nActual].CalcCaseMap( rTxt ),
//STRIP001                      nTextWidth, nIdx, nLn, CheckKerning() );
//STRIP001  }
//STRIP001  return nTxtBreak;
//STRIP001 }

/*************************************************************************
 *                    SwFont::GetTxtBreak()
 *************************************************************************/

//STRIP001 xub_StrLen SwFont::GetTxtBreak( ViewShell *pSh, const OutputDevice *pOut,
//STRIP001    const SwScriptInfo* pScript, const XubString &rTxt, long nTextWidth,
//STRIP001    xub_StrLen& rExtraCharPos, const xub_StrLen nIdx, const xub_StrLen nLen )
//STRIP001 {
//STRIP001  // Robust ...
//STRIP001  if ( !pLastFont || pLastFont->GetOwner()!= aSub[nActual].pMagic )
//STRIP001      ChgFnt( pSh, (OutputDevice *)pOut );
//STRIP001
//STRIP001  xub_StrLen nTxtBreak = 0;
//STRIP001
//STRIP001  xub_StrLen nLn = ( nLen == STRING_LEN ? rTxt.Len() : nLen );
//STRIP001  if( aSub[nActual].IsCapital() && nLn )
//STRIP001          nTxtBreak = GetCapitalBreak( pSh, pOut, pScript, rTxt, nTextWidth,
//STRIP001                              &rExtraCharPos, nIdx, nLn );
//STRIP001  else
//STRIP001  {
//STRIP001      if ( !aSub[nActual].IsCaseMap() )
//STRIP001          nTxtBreak = pOut->GetTextBreak( rTxt, nTextWidth,
//STRIP001                          '-', rExtraCharPos, nIdx, nLn, CheckKerning() );
//STRIP001      else
//STRIP001          nTxtBreak = pOut->GetTextBreak( aSub[nActual].CalcCaseMap( rTxt ),
//STRIP001              nTextWidth, '-', rExtraCharPos, nIdx, nLn, CheckKerning() );
//STRIP001  }
//STRIP001  return nTxtBreak;
//STRIP001 }

/*************************************************************************
 *                    SwSubFont::_DrawText()
 *************************************************************************/

//STRIP001 void SwSubFont::_DrawText( SwDrawTextInfo &rInf, const BOOL bGrey )
//STRIP001 {
//STRIP001     rInf.SetGreyWave( bGrey );
//STRIP001  xub_StrLen nLn = rInf.GetText().Len();
//STRIP001  if( !rInf.GetLen() || !nLn )
//STRIP001      return;
//STRIP001  if( STRING_LEN == rInf.GetLen() )
//STRIP001      rInf.SetLen( nLn );
//STRIP001
//STRIP001  FontUnderline nOldUnder;
//STRIP001     SwUnderlineFont* pUnderFnt = 0;
//STRIP001
//STRIP001     if( rInf.GetUnderFnt() )
//STRIP001  {
//STRIP001      nOldUnder = GetUnderline();
//STRIP001      SetUnderline( UNDERLINE_NONE );
//STRIP001         pUnderFnt = rInf.GetUnderFnt();
//STRIP001  }
//STRIP001
//STRIP001  if( !pLastFont || pLastFont->GetOwner()!=pMagic )
//STRIP001      ChgFnt( rInf.GetShell(), rInf.GetpOut() );
//STRIP001
//STRIP001  Point aPos( rInf.GetPos() );
//STRIP001  const Point &rOld = rInf.GetPos();
//STRIP001  rInf.SetPos( aPos );
//STRIP001
//STRIP001  if( GetEscapement() )
//STRIP001         CalcEsc( rInf, aPos );
//STRIP001
//STRIP001  rInf.SetKern( CheckKerning() + rInf.GetSperren() );
//STRIP001
//STRIP001  if( IsCapital() )
//STRIP001         DrawCapital( rInf );
//STRIP001  else
//STRIP001  {
//STRIP001      SV_STAT( nDrawText );
//STRIP001      if ( !IsCaseMap() )
//STRIP001          pLastFont->DrawText( rInf );
//STRIP001      else
//STRIP001      {
//STRIP001          const XubString &rOldStr = rInf.GetText();
//STRIP001          XubString aString( CalcCaseMap( rOldStr ) );
//STRIP001          sal_Bool bCaseMapLengthDiffers(aString.Len() != rOldStr.Len());
//STRIP001
//STRIP001          if(bCaseMapLengthDiffers && rInf.GetLen())
//STRIP001          {
//STRIP001              // #108203#
//STRIP001              // If the length of the original string and the CaseMapped one
//STRIP001              // are different, it is necessary to handle the given text part as
//STRIP001              // a single snippet since itÄs size may differ, too.
//STRIP001              xub_StrLen nOldIdx(rInf.GetIdx());
//STRIP001              xub_StrLen nOldLen(rInf.GetLen());
//STRIP001              const XubString aSnippet(rOldStr, nOldIdx, nOldLen);
//STRIP001              XubString aNewText = CalcCaseMap(aSnippet);
//STRIP001
//STRIP001              rInf.SetText( aNewText );
//STRIP001              rInf.SetIdx( 0 );
//STRIP001              rInf.SetLen( aNewText.Len() );
//STRIP001
//STRIP001              pLastFont->DrawText( rInf );
//STRIP001
//STRIP001              rInf.SetIdx( nOldIdx );
//STRIP001              rInf.SetLen( nOldLen );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              rInf.SetText( aString );
//STRIP001              pLastFont->DrawText( rInf );
//STRIP001          }
//STRIP001
//STRIP001          rInf.SetText( rOldStr );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001     if( pUnderFnt && nOldUnder != UNDERLINE_NONE )
//STRIP001  {
//STRIP001 static sal_Char __READONLY_DATA sDoubleSpace[] = "  ";
//STRIP001      Size aSize = _GetTxtSize( rInf );
//STRIP001         const XubString &rOldStr = rInf.GetText();
//STRIP001         XubString aStr( sDoubleSpace, RTL_TEXTENCODING_MS_1252 );
//STRIP001
//STRIP001         xub_StrLen nOldIdx = rInf.GetIdx();
//STRIP001      xub_StrLen nOldLen = rInf.GetLen();
//STRIP001         long nSpace = 0;
//STRIP001      if( rInf.GetSpace() )
//STRIP001      {
//STRIP001             xub_StrLen nTmpEnd = nOldIdx + nOldLen;
//STRIP001          if( nTmpEnd > rOldStr.Len() )
//STRIP001              nTmpEnd = rOldStr.Len();
//STRIP001
//STRIP001             const SwScriptInfo* pSI = rInf.GetScriptInfo();
//STRIP001
//STRIP001             const sal_Bool bAsianFont =
//STRIP001                 ( rInf.GetFont() && SW_CJK == rInf.GetFont()->GetActual() );
//STRIP001             for( xub_StrLen nTmp = nOldIdx; nTmp < nTmpEnd; ++nTmp )
//STRIP001                 if( CH_BLANK == rOldStr.GetChar( nTmp ) || bAsianFont ||
//STRIP001                     ( nTmp + 1 < rOldStr.Len() && pSI &&
//STRIP001                       ASIAN == pSI->ScriptType( nTmp + 1 ) ) )
//STRIP001                  ++nSpace;
//STRIP001
//STRIP001             // if next portion if a hole portion we do not consider any
//STRIP001             // extra space added because the last character was ASIAN
//STRIP001             if ( nSpace && rInf.IsSpaceStop() && bAsianFont )
//STRIP001                  --nSpace;
//STRIP001
//STRIP001          nSpace *= rInf.GetSpace();
//STRIP001      }
//STRIP001
//STRIP001         rInf.SetWidth( USHORT(aSize.Width() + nSpace) );
//STRIP001         rInf.SetText( aStr );
//STRIP001      rInf.SetIdx( 0 );
//STRIP001      rInf.SetLen( 2 );
//STRIP001         SetUnderline( nOldUnder );
//STRIP001         rInf.SetUnderFnt( 0 );
//STRIP001
//STRIP001         // set position for underline font
//STRIP001         rInf.SetPos( pUnderFnt->GetPos() );
//STRIP001
//STRIP001         pUnderFnt->GetFont()._DrawStretchText( rInf );
//STRIP001
//STRIP001         rInf.SetUnderFnt( pUnderFnt );
//STRIP001         rInf.SetText( rOldStr );
//STRIP001      rInf.SetIdx( nOldIdx );
//STRIP001      rInf.SetLen( nOldLen );
//STRIP001  }
//STRIP001
//STRIP001     rInf.SetPos( rOld );
//STRIP001 }

//STRIP001 void SwSubFont::_DrawStretchText( SwDrawTextInfo &rInf )
//STRIP001 {
//STRIP001  if( !rInf.GetLen() || !rInf.GetText().Len() )
//STRIP001      return;
//STRIP001
//STRIP001  FontUnderline nOldUnder;
//STRIP001     SwUnderlineFont* pUnderFnt = 0;
//STRIP001
//STRIP001     if( rInf.GetUnderFnt() )
//STRIP001  {
//STRIP001      nOldUnder = GetUnderline();
//STRIP001      SetUnderline( UNDERLINE_NONE );
//STRIP001         pUnderFnt = rInf.GetUnderFnt();
//STRIP001  }
//STRIP001
//STRIP001     if ( !pLastFont || pLastFont->GetOwner() != pMagic )
//STRIP001      ChgFnt( rInf.GetShell(), rInf.GetpOut() );
//STRIP001
//STRIP001     rInf.ApplyAutoColor();
//STRIP001
//STRIP001  Point aPos( rInf.GetPos() );
//STRIP001
//STRIP001  if( GetEscapement() )
//STRIP001         CalcEsc( rInf, aPos );
//STRIP001
//STRIP001  rInf.SetKern( CheckKerning() + rInf.GetSperren() );
//STRIP001     const Point &rOld = rInf.GetPos();
//STRIP001     rInf.SetPos( aPos );
//STRIP001
//STRIP001  if( IsCapital() )
//STRIP001      DrawStretchCapital( rInf );
//STRIP001  else
//STRIP001  {
//STRIP001      SV_STAT( nDrawStretchText );
//STRIP001
//STRIP001         if ( rInf.GetFrm() )
//STRIP001         {
//STRIP001 #ifdef BIDI
//STRIP001             if ( rInf.GetFrm()->IsRightToLeft() )
//STRIP001                 rInf.GetFrm()->SwitchLTRtoRTL( aPos );
//STRIP001 #endif
//STRIP001
//STRIP001             if ( rInf.GetFrm()->IsVertical() )
//STRIP001                 rInf.GetFrm()->SwitchHorizontalToVertical( aPos );
//STRIP001         }
//STRIP001
//STRIP001      if ( !IsCaseMap() )
//STRIP001          rInf.GetOut().DrawStretchText( aPos, rInf.GetWidth(),
//STRIP001                          rInf.GetText(), rInf.GetIdx(), rInf.GetLen() );
//STRIP001      else
//STRIP001          rInf.GetOut().DrawStretchText( aPos, rInf.GetWidth(), CalcCaseMap(
//STRIP001                          rInf.GetText() ), rInf.GetIdx(), rInf.GetLen() );
//STRIP001  }
//STRIP001
//STRIP001     if( pUnderFnt && nOldUnder != UNDERLINE_NONE )
//STRIP001  {
//STRIP001 static sal_Char __READONLY_DATA sDoubleSpace[] = "  ";
//STRIP001      const XubString &rOldStr = rInf.GetText();
//STRIP001      XubString aStr( sDoubleSpace, RTL_TEXTENCODING_MS_1252 );
//STRIP001      xub_StrLen nOldIdx = rInf.GetIdx();
//STRIP001      xub_StrLen nOldLen = rInf.GetLen();
//STRIP001      rInf.SetText( aStr );
//STRIP001      rInf.SetIdx( 0 );
//STRIP001      rInf.SetLen( 2 );
//STRIP001      SetUnderline( nOldUnder );
//STRIP001         rInf.SetUnderFnt( 0 );
//STRIP001
//STRIP001         // set position for underline font
//STRIP001         rInf.SetPos( pUnderFnt->GetPos() );
//STRIP001
//STRIP001         pUnderFnt->GetFont()._DrawStretchText( rInf );
//STRIP001
//STRIP001         rInf.SetUnderFnt( pUnderFnt );
//STRIP001         rInf.SetText( rOldStr );
//STRIP001      rInf.SetIdx( nOldIdx );
//STRIP001      rInf.SetLen( nOldLen );
//STRIP001  }
//STRIP001
//STRIP001     rInf.SetPos( rOld );
//STRIP001 }

/*************************************************************************
 *                    SwSubFont::_GetCrsrOfst()
 *************************************************************************/

/*N*/ xub_StrLen SwSubFont::_GetCrsrOfst( SwDrawTextInfo& rInf )
/*N*/ {
/*N*/   if ( !pLastFont || pLastFont->GetOwner()!=pMagic )
/*?*/       ChgFnt( rInf.GetShell(), rInf.GetpOut() );
/*N*/
/*N*/   xub_StrLen nLn = rInf.GetLen() == STRING_LEN ? rInf.GetText().Len()
/*N*/                                                : rInf.GetLen();
/*N*/   rInf.SetLen( nLn );
/*N*/   xub_StrLen nCrsr = 0;
/*N*/   if( IsCapital() && nLn )
            {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/      nCrsr = GetCapitalCrsrOfst( rInf );
/*N*/   else
/*N*/   {
/*N*/       const XubString &rOldTxt = rInf.GetText();
/*N*/       short nOldKern = rInf.GetKern();
/*N*/       rInf.SetKern( CheckKerning() );
/*N*/       SV_STAT( nGetTextSize );
/*N*/       if ( !IsCaseMap() )
/*?*/           {DBG_ASSERT(0, "STRIP"); }//STRIP001 nCrsr = pLastFont->GetCrsrOfst( rInf );
/*N*/       else
/*N*/       {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            String aTmp = CalcCaseMap( rInf.GetText() );
//STRIP001 /*?*/            rInf.SetText( aTmp );
//STRIP001 /*?*/            nCrsr = pLastFont->GetCrsrOfst( rInf );
/*N*/       }
/*N*/       rInf.SetKern( nOldKern );
/*N*/       rInf.SetText( rOldTxt );
/*N*/   }
/*N*/   return nCrsr;
/*N*/ }

/*************************************************************************
 *                    SwSubFont::CalcEsc()
 *************************************************************************/

//STRIP001 void SwSubFont::CalcEsc( SwDrawTextInfo& rInf, Point& rPos )
//STRIP001 {
//STRIP001     long nOfst;
//STRIP001
//STRIP001     USHORT nDir = UnMapDirection(
//STRIP001                 GetOrientation(), rInf.GetFrm() && rInf.GetFrm()->IsVertical() );
//STRIP001
//STRIP001     switch ( GetEscapement() )
//STRIP001     {
//STRIP001     case DFLT_ESC_AUTO_SUB :
//STRIP001         nOfst = nOrgHeight - nOrgAscent -
//STRIP001             pLastFont->GetHeight( rInf.GetShell(), rInf.GetpOut() ) +
//STRIP001             pLastFont->GetAscent( rInf.GetShell(), rInf.GetpOut() );
//STRIP001
//STRIP001         switch ( nDir )
//STRIP001         {
//STRIP001         case 0 :
//STRIP001             rPos.Y() += nOfst;
//STRIP001             break;
//STRIP001         case 900 :
//STRIP001             rPos.X() += nOfst;
//STRIP001             break;
//STRIP001         case 2700 :
//STRIP001             rPos.X() -= nOfst;
//STRIP001             break;
//STRIP001         }
//STRIP001
//STRIP001         break;
//STRIP001     case DFLT_ESC_AUTO_SUPER :
//STRIP001         nOfst = pLastFont->GetAscent( rInf.GetShell(), rInf.GetpOut() ) -
//STRIP001                 nOrgAscent;
//STRIP001
//STRIP001
//STRIP001         switch ( nDir )
//STRIP001         {
//STRIP001         case 0 :
//STRIP001             rPos.Y() += nOfst;
//STRIP001             break;
//STRIP001         case 900 :
//STRIP001             rPos.X() += nOfst;
//STRIP001             break;
//STRIP001         case 2700 :
//STRIP001             rPos.X() -= nOfst;
//STRIP001             break;
//STRIP001         }
//STRIP001
//STRIP001         break;
//STRIP001     default :
//STRIP001         nOfst = ((long)nOrgHeight * GetEscapement()) / 100L;
//STRIP001
//STRIP001         switch ( nDir )
//STRIP001         {
//STRIP001         case 0 :
//STRIP001             rPos.Y() -= nOfst;
//STRIP001             break;
//STRIP001         case 900 :
//STRIP001             rPos.X() -= nOfst;
//STRIP001             break;
//STRIP001         case 2700 :
//STRIP001             rPos.X() += nOfst;
//STRIP001             break;
//STRIP001         }
//STRIP001     }
//STRIP001 }

// used during painting of small capitals
//STRIP001 void SwDrawTextInfo::Shift( USHORT nDir )
//STRIP001 {
//STRIP001     ASSERT( bPos, "DrawTextInfo: Undefined Position" );
//STRIP001     ASSERT( bSize, "DrawTextInfo: Undefined Width" );
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001     const BOOL bBidiPor = ( GetFrm() && GetFrm()->IsRightToLeft() ) !=
//STRIP001                           ( 0 != ( TEXT_LAYOUT_BIDI_RTL & GetpOut()->GetLayoutMode() ) );
//STRIP001
//STRIP001     nDir = bBidiPor ?
//STRIP001             1800 :
//STRIP001             UnMapDirection( nDir, GetFrm() && GetFrm()->IsVertical() );
//STRIP001 #else
//STRIP001     nDir = UnMapDirection( nDir, GetFrm() && GetFrm()->IsVertical() );
//STRIP001 #endif
//STRIP001
//STRIP001     switch ( nDir )
//STRIP001     {
//STRIP001     case 0 :
//STRIP001         ((Point*)pPos)->X() += GetSize().Width();
//STRIP001         break;
//STRIP001     case 900 :
//STRIP001         ASSERT( ((Point*)pPos)->Y() >= GetSize().Width(), "Going underground" );
//STRIP001         ((Point*)pPos)->Y() -= GetSize().Width();
//STRIP001         break;
//STRIP001     case 1800 :
//STRIP001         ((Point*)pPos)->X() -= GetSize().Width();
//STRIP001         break;
//STRIP001     case 2700 :
//STRIP001         ((Point*)pPos)->Y() += GetSize().Width();
//STRIP001         break;
//STRIP001     }
//STRIP001 }

/*************************************************************************
 *                      SwUnderlineFont::~SwUnderlineFont
 *
 * Used for the "continuous underline" feature.
 *************************************************************************/

//STRIP001 SwUnderlineFont::SwUnderlineFont( SwFont& rFnt, const Point& rPoint )
//STRIP001         : pFnt( &rFnt ), aPos( rPoint )
//STRIP001 {
//STRIP001 };

//STRIP001 SwUnderlineFont::~SwUnderlineFont()
//STRIP001 {
//STRIP001      delete pFnt;
//STRIP001 }

//Helper for filters to find true lineheight of a font
//STRIP001 long AttrSetToLineHeight(const SwDoc &rDoc, const SwAttrSet &rSet,
//STRIP001     const OutputDevice &rOut, sal_Int16 nScript)
//STRIP001 {
//STRIP001     SwFont aFont(&rSet, &rDoc);
//STRIP001     BYTE nActual;
//STRIP001     switch (nScript)
//STRIP001     {
//STRIP001         default:
//STRIP001         case com::sun::star::i18n::ScriptType::LATIN:
//STRIP001             nActual = SW_LATIN;
//STRIP001             break;
//STRIP001         case com::sun::star::i18n::ScriptType::ASIAN:
//STRIP001             nActual = SW_CJK;
//STRIP001             break;
//STRIP001         case com::sun::star::i18n::ScriptType::COMPLEX:
//STRIP001             nActual = SW_CTL;
//STRIP001             break;
//STRIP001     }
//STRIP001     aFont.SetActual(nActual);
//STRIP001
//STRIP001     OutputDevice &rMutableOut = const_cast<OutputDevice &>(rOut);
//STRIP001     const Font aOldFont(rMutableOut.GetFont());
//STRIP001
//STRIP001     rMutableOut.SetFont(aFont.GetActualFont());
//STRIP001     long nHeight = rMutableOut.GetTextHeight();
//STRIP001
//STRIP001     rMutableOut.SetFont(aOldFont);
//STRIP001     return nHeight;
//STRIP001 }

