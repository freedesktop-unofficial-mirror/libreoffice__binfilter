/*************************************************************************
 *
 *  $RCSfile: svx_editattr.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:21:39 $
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

#include <eeng_pch.hxx>

#pragma hdrstop

#include <svxfont.hxx>
#include <flditem.hxx>
#include <fontitem.hxx>
#include <postitem.hxx>
#include <wghtitem.hxx>
#include <udlnitem.hxx>
#include <cntritem.hxx>
#include <shdditem.hxx>
#include <escpitem.hxx>
#include <colritem.hxx>
#include <wrlmitem.hxx>
#include <fhgtitem.hxx>
#include <crsditem.hxx>
#include <cscoitem.hxx>
#include <kernitem.hxx>
#include <akrnitem.hxx>
#include <langitem.hxx>
#include <emphitem.hxx>
#include <charscaleitem.hxx>
#include <charreliefitem.hxx>


#include <editattr.hxx>

/*N*/ DBG_NAME( EE_EditAttrib );

// -------------------------------------------------------------------------
// class EditAttrib
// -------------------------------------------------------------------------
/*N*/ EditAttrib::EditAttrib( const SfxPoolItem& rAttr )
/*N*/ {
/*N*/   DBG_CTOR( EE_EditAttrib, 0 );
/*N*/   pItem = &rAttr;
/*N*/ }

/*N*/ EditAttrib::~EditAttrib()
/*N*/ {
/*N*/   DBG_DTOR( EE_EditAttrib, 0 );
/*N*/ }

// -------------------------------------------------------------------------
// class EditCharAttrib
// -------------------------------------------------------------------------
/*N*/ EditCharAttrib::EditCharAttrib( const SfxPoolItem& rAttr, USHORT nS, USHORT nE )
/*N*/                   : EditAttrib( rAttr )
/*N*/ {
/*N*/   nStart      = nS;
/*N*/   nEnd        = nE;
/*N*/   bFeature    = FALSE;
/*N*/   bEdge       = FALSE;
/*N*/
/*N*/     DBG_ASSERT( ( rAttr.Which() >= EE_ITEMS_START ) && ( rAttr.Which() <= EE_ITEMS_END ), "EditCharAttrib CTOR: Invalid id!" );
/*N*/     DBG_ASSERT( ( rAttr.Which() < EE_FEATURE_START ) || ( rAttr.Which() > EE_FEATURE_END ) || ( nE = (nS+1) ), "EditCharAttrib CTOR: Invalid feature!" );
/*N*/ }

/*N*/ void EditCharAttrib::SetFont( SvxFont&, OutputDevice* )
/*N*/ {
/*N*/ }


// -------------------------------------------------------------------------
// class EditCharAttribFont
// -------------------------------------------------------------------------
/*N*/ EditCharAttribFont::EditCharAttribFont( const SvxFontItem& rAttr, USHORT nStart, USHORT nEnd )
/*N*/   : EditCharAttrib( rAttr, nStart, nEnd )
/*N*/ {
/*N*/   DBG_ASSERT( rAttr.Which() == EE_CHAR_FONTINFO || rAttr.Which() == EE_CHAR_FONTINFO_CJK || rAttr.Which() == EE_CHAR_FONTINFO_CTL, "Kein Fontattribut!" );
/*N*/ }

/*N*/ void EditCharAttribFont::SetFont( SvxFont& rFont, OutputDevice* )
/*N*/ {
/*N*/   const SvxFontItem& rAttr = (const SvxFontItem&)(*GetItem());
/*N*/
/*N*/   rFont.SetName( rAttr.GetFamilyName() );
/*N*/   rFont.SetFamily( rAttr.GetFamily() );
/*N*/   rFont.SetPitch( rAttr.GetPitch() );
/*N*/   rFont.SetCharSet( rAttr.GetCharSet() );
/*N*/ }

// -------------------------------------------------------------------------
// class EditCharAttribItalic
// -------------------------------------------------------------------------
/*N*/ EditCharAttribItalic::EditCharAttribItalic( const SvxPostureItem& rAttr, USHORT nStart, USHORT nEnd )
/*N*/   : EditCharAttrib( rAttr, nStart, nEnd )
/*N*/ {
/*N*/   DBG_ASSERT( rAttr.Which() == EE_CHAR_ITALIC || rAttr.Which() == EE_CHAR_ITALIC_CJK || rAttr.Which() == EE_CHAR_ITALIC_CTL, "Kein Italicattribut!" );
/*N*/ }

/*N*/ void EditCharAttribItalic::SetFont( SvxFont& rFont, OutputDevice* )
/*N*/ {
/*N*/   rFont.SetItalic( ((const SvxPostureItem*)GetItem())->GetPosture() );
/*N*/ }

// -------------------------------------------------------------------------
// class EditCharAttribWeight
// -------------------------------------------------------------------------
/*N*/ EditCharAttribWeight::EditCharAttribWeight( const SvxWeightItem& rAttr, USHORT nStart, USHORT nEnd )
/*N*/   : EditCharAttrib( rAttr, nStart, nEnd )
/*N*/ {
/*N*/   DBG_ASSERT( rAttr.Which() == EE_CHAR_WEIGHT || rAttr.Which() == EE_CHAR_WEIGHT_CJK || rAttr.Which() == EE_CHAR_WEIGHT_CTL, "Kein Weightttribut!" );
/*N*/ }

/*N*/ void EditCharAttribWeight::SetFont( SvxFont& rFont, OutputDevice* )
/*N*/ {
/*N*/   rFont.SetWeight( (FontWeight)((const SvxWeightItem*)GetItem())->GetValue() );
/*N*/ }

// -------------------------------------------------------------------------
// class EditCharAttribUnderline
// -------------------------------------------------------------------------
/*N*/ EditCharAttribUnderline::EditCharAttribUnderline( const SvxUnderlineItem& rAttr, USHORT nStart, USHORT nEnd )
/*N*/   : EditCharAttrib( rAttr, nStart, nEnd )
/*N*/ {
/*N*/   DBG_ASSERT( rAttr.Which() == EE_CHAR_UNDERLINE, "Kein Underlineattribut!" );
/*N*/ }

/*N*/ void EditCharAttribUnderline::SetFont( SvxFont& rFont, OutputDevice* pOutDev )
/*N*/ {
/*N*/   rFont.SetUnderline( (FontUnderline)((const SvxUnderlineItem*)GetItem())->GetValue() );
/*N*/   if ( pOutDev )
/*?*/       pOutDev->SetTextLineColor( ((const SvxUnderlineItem*)GetItem())->GetColor() );
/*N*/ }

// -------------------------------------------------------------------------
// class EditCharAttribFontHeight
// -------------------------------------------------------------------------
/*N*/ EditCharAttribFontHeight::EditCharAttribFontHeight( const SvxFontHeightItem& rAttr, USHORT nStart, USHORT nEnd )
/*N*/   : EditCharAttrib( rAttr, nStart, nEnd )
/*N*/ {
/*N*/   DBG_ASSERT( rAttr.Which() == EE_CHAR_FONTHEIGHT || rAttr.Which() == EE_CHAR_FONTHEIGHT_CJK || rAttr.Which() == EE_CHAR_FONTHEIGHT_CTL, "Kein Heightattribut!" );
/*N*/ }

/*N*/ void EditCharAttribFontHeight::SetFont( SvxFont& rFont, OutputDevice* )
/*N*/ {
/*N*/   // Prop wird ignoriert
/*N*/   rFont.SetSize( Size( rFont.GetSize().Width(), ((const SvxFontHeightItem*)GetItem())->GetHeight() ) );
/*N*/ }

// -------------------------------------------------------------------------
// class EditCharAttribFontWidth
// -------------------------------------------------------------------------
/*N*/ EditCharAttribFontWidth::EditCharAttribFontWidth( const SvxCharScaleWidthItem& rAttr, USHORT nStart, USHORT nEnd )
/*N*/   : EditCharAttrib( rAttr, nStart, nEnd )
/*N*/ {
/*N*/   DBG_ASSERT( rAttr.Which() == EE_CHAR_FONTWIDTH, "Kein Widthattribut!" );
/*N*/ }

/*N*/ void EditCharAttribFontWidth::SetFont( SvxFont& rFont, OutputDevice* )
/*N*/ {
/*N*/   // must be calculated outside, because f(device)...
/*N*/ }

// -------------------------------------------------------------------------
// class EditCharAttribStrikeout
// -------------------------------------------------------------------------
/*N*/ EditCharAttribStrikeout::EditCharAttribStrikeout( const SvxCrossedOutItem& rAttr, USHORT nStart, USHORT nEnd )
/*N*/   : EditCharAttrib( rAttr, nStart, nEnd )
/*N*/ {
/*N*/   DBG_ASSERT( rAttr.Which() == EE_CHAR_STRIKEOUT, "Kein Sizeattribut!" );
/*N*/ }

/*N*/ void EditCharAttribStrikeout::SetFont( SvxFont& rFont, OutputDevice* )
/*N*/ {
/*N*/   rFont.SetStrikeout( (FontStrikeout)((const SvxCrossedOutItem*)GetItem())->GetValue() );
/*N*/ }

// -------------------------------------------------------------------------
// class EditCharAttribColor
// -------------------------------------------------------------------------
/*N*/ EditCharAttribColor::EditCharAttribColor( const SvxColorItem& rAttr, USHORT nStart, USHORT nEnd )
/*N*/   : EditCharAttrib( rAttr, nStart, nEnd )
/*N*/ {
/*N*/   DBG_ASSERT( rAttr.Which() == EE_CHAR_COLOR, "Kein Colorattribut!" );
/*N*/ }

/*N*/ void EditCharAttribColor::SetFont( SvxFont& rFont, OutputDevice* )
/*N*/ {
/*N*/   rFont.SetColor( ((const SvxColorItem*)GetItem())->GetValue() );
/*N*/ }

// -------------------------------------------------------------------------
// class EditCharAttribLanguage
// -------------------------------------------------------------------------
/*N*/ EditCharAttribLanguage::EditCharAttribLanguage( const SvxLanguageItem& rAttr, USHORT nStart, USHORT nEnd )
/*N*/   : EditCharAttrib( rAttr, nStart, nEnd )
/*N*/ {
/*N*/   DBG_ASSERT( ( rAttr.Which() == EE_CHAR_LANGUAGE ) || ( rAttr.Which() == EE_CHAR_LANGUAGE_CJK ) || ( rAttr.Which() == EE_CHAR_LANGUAGE_CTL ), "Kein Languageattribut!" );
/*N*/ }

/*N*/ void EditCharAttribLanguage::SetFont( SvxFont& rFont, OutputDevice* )
/*N*/ {
/*N*/   rFont.SetLanguage( ((const SvxLanguageItem*)GetItem())->GetLanguage() );
/*N*/ }

// -------------------------------------------------------------------------
// class EditCharAttribShadow
// -------------------------------------------------------------------------
/*N*/ EditCharAttribShadow::EditCharAttribShadow( const SvxShadowedItem& rAttr, USHORT nStart, USHORT nEnd )
/*N*/   : EditCharAttrib( rAttr, nStart, nEnd )
/*N*/ {
/*N*/   DBG_ASSERT( rAttr.Which() == EE_CHAR_SHADOW, "Kein Shadowattribut!" );
/*N*/ }

/*N*/ void EditCharAttribShadow::SetFont( SvxFont& rFont, OutputDevice* )
/*N*/ {
/*N*/   rFont.SetShadow( (BOOL)((const SvxShadowedItem*)GetItem())->GetValue() );
/*N*/ }

// -------------------------------------------------------------------------
// class EditCharAttribEscapement
// -------------------------------------------------------------------------
/*N*/ EditCharAttribEscapement::EditCharAttribEscapement( const SvxEscapementItem& rAttr, USHORT nStart, USHORT nEnd )
/*N*/   : EditCharAttrib( rAttr, nStart, nEnd )
/*N*/ {
/*N*/   DBG_ASSERT( rAttr.Which() == EE_CHAR_ESCAPEMENT, "Kein Escapementattribut!" );
/*N*/ }

#if defined( WIN ) && !defined( WNT )
#pragma optimize ("", off)
#endif

/*N*/ void EditCharAttribEscapement::SetFont( SvxFont& rFont, OutputDevice* )
/*N*/ {
/*N*/   USHORT nProp = ((const SvxEscapementItem*)GetItem())->GetProp();
/*N*/   rFont.SetPropr( (BYTE)nProp );
/*N*/
/*N*/   short nEsc = ((const SvxEscapementItem*)GetItem())->GetEsc();
/*N*/   if ( nEsc == DFLT_ESC_AUTO_SUPER )
/*N*/       nEsc = 100 - nProp;
/*N*/   else if ( nEsc == DFLT_ESC_AUTO_SUB )
/*N*/       nEsc = -( 100 - nProp );
/*N*/   rFont.SetEscapement( nEsc );
/*N*/ }

#if defined( WIN ) && !defined( WNT )
#pragma optimize ("", on)
#endif


// -------------------------------------------------------------------------
// class EditCharAttribOutline
// -------------------------------------------------------------------------
/*N*/ EditCharAttribOutline::EditCharAttribOutline( const SvxContourItem& rAttr, USHORT nStart, USHORT nEnd )
/*N*/   : EditCharAttrib( rAttr, nStart, nEnd )
/*N*/ {
/*N*/   DBG_ASSERT( rAttr.Which() == EE_CHAR_OUTLINE, "Kein Outlineattribut!" );
/*N*/ }

/*N*/ void EditCharAttribOutline::SetFont( SvxFont& rFont, OutputDevice* )
/*N*/ {
/*N*/   rFont.SetOutline( (BOOL)((const SvxContourItem*)GetItem())->GetValue() );
/*N*/ }

// -------------------------------------------------------------------------
// class EditCharAttribTab
// -------------------------------------------------------------------------
/*N*/ EditCharAttribTab::EditCharAttribTab( const SfxVoidItem& rAttr, USHORT nPos )
/*N*/   : EditCharAttrib( rAttr, nPos, nPos+1 )
/*N*/ {
/*N*/   SetFeature( TRUE );
/*N*/ }

/*N*/ void EditCharAttribTab::SetFont( SvxFont&, OutputDevice* )
/*N*/ {
/*N*/ }

// -------------------------------------------------------------------------
// class EditCharAttribLineBreak
// -------------------------------------------------------------------------
/*N*/ EditCharAttribLineBreak::EditCharAttribLineBreak( const SfxVoidItem& rAttr, USHORT nPos )
/*N*/   : EditCharAttrib( rAttr, nPos, nPos+1 )
/*N*/ {
/*N*/   SetFeature( TRUE );
/*N*/ }

/*N*/ void EditCharAttribLineBreak::SetFont( SvxFont&, OutputDevice* )
/*N*/ {
/*N*/ }

// -------------------------------------------------------------------------
// class EditCharAttribField
// -------------------------------------------------------------------------
/*N*/ EditCharAttribField::EditCharAttribField( const SvxFieldItem& rAttr, USHORT nPos )
/*N*/   : EditCharAttrib( rAttr, nPos, nPos+1 )
/*N*/ {
/*N*/   SetFeature( TRUE ); // !!!
/*N*/   pTxtColor = 0;
/*N*/   pFldColor = 0;
/*N*/ }

/*N*/ void EditCharAttribField::SetFont( SvxFont& rFont, OutputDevice* )
/*N*/ {
/*N*/   if ( pFldColor )
/*N*/   {
/*N*/       rFont.SetFillColor( *pFldColor );
/*N*/       rFont.SetTransparent( FALSE );
/*N*/   }
/*N*/   if ( pTxtColor )
/*N*/       rFont.SetColor( *pTxtColor );
/*N*/ }

/*N*/ EditCharAttribField::EditCharAttribField( const EditCharAttribField& rAttr )
/*N*/   : EditCharAttrib( *rAttr.GetItem(), rAttr.GetStart(), rAttr.GetEnd() ),
/*N*/       aFieldValue( rAttr.aFieldValue )
/*N*/ {
/*N*/   // Diesen CCTOR nur fuer temporaeres Object verwenden,
/*N*/   // Item wird nicht gepoolt.
/*N*/   pTxtColor = rAttr.pTxtColor ? new Color( *rAttr.pTxtColor ) : 0;
/*N*/   pFldColor = rAttr.pFldColor ? new Color( *rAttr.pFldColor ) : 0;
/*N*/ }

/*N*/ EditCharAttribField::~EditCharAttribField()
/*N*/ {
/*N*/   Reset();
/*N*/ }

/*N*/ BOOL EditCharAttribField::operator == ( const EditCharAttribField& rAttr ) const
/*N*/ {
/*N*/   if ( aFieldValue != rAttr.aFieldValue )
/*N*/       return FALSE;
/*N*/
/*N*/   if ( ( pTxtColor && !rAttr.pTxtColor ) || ( !pTxtColor && rAttr.pTxtColor ) )
/*N*/       return FALSE;
/*N*/   if ( ( pTxtColor && rAttr.pTxtColor ) && ( *pTxtColor != *rAttr.pTxtColor ) )
/*N*/       return FALSE;
/*N*/
/*N*/   if ( ( pFldColor && !rAttr.pFldColor ) || ( !pFldColor && rAttr.pFldColor ) )
/*N*/       return FALSE;
/*N*/   if ( ( pFldColor && rAttr.pFldColor ) && ( *pFldColor != *rAttr.pFldColor ) )
/*N*/       return FALSE;
/*N*/
/*N*/   return TRUE;
/*N*/ }

// -------------------------------------------------------------------------
// class EditCharAttribPairKerning
// -------------------------------------------------------------------------
/*N*/ EditCharAttribPairKerning::EditCharAttribPairKerning( const SvxAutoKernItem& rAttr, USHORT nStart, USHORT nEnd )
/*N*/   : EditCharAttrib( rAttr, nStart, nEnd )
/*N*/ {
/*N*/   DBG_ASSERT( rAttr.Which() == EE_CHAR_PAIRKERNING, "Kein PairKerning!" );
/*N*/ }

/*N*/ void EditCharAttribPairKerning::SetFont( SvxFont& rFont, OutputDevice* )
/*N*/ {
/*N*/   rFont.SetKerning( ((const SvxAutoKernItem*)GetItem())->GetValue() );
/*N*/ }

// -------------------------------------------------------------------------
// class EditCharAttribKerning
// -------------------------------------------------------------------------
/*N*/ EditCharAttribKerning::EditCharAttribKerning( const SvxKerningItem& rAttr, USHORT nStart, USHORT nEnd )
/*N*/   : EditCharAttrib( rAttr, nStart, nEnd )
/*N*/ {
/*N*/   DBG_ASSERT( rAttr.Which() == EE_CHAR_KERNING, "Kein Kerning!" );
/*N*/ }

/*N*/ void EditCharAttribKerning::SetFont( SvxFont& rFont, OutputDevice* )
/*N*/ {
/*N*/   rFont.SetFixKerning( ((const SvxKerningItem*)GetItem())->GetValue() );
/*N*/ }

// -------------------------------------------------------------------------
// class EditCharAttribWordLineMode
// -------------------------------------------------------------------------
/*N*/ EditCharAttribWordLineMode::EditCharAttribWordLineMode( const SvxWordLineModeItem& rAttr, USHORT nStart, USHORT nEnd )
/*N*/   : EditCharAttrib( rAttr, nStart, nEnd )
/*N*/ {
/*N*/   DBG_ASSERT( rAttr.Which() == EE_CHAR_WLM, "Kein Kerning!" );
/*N*/ }

/*N*/ void EditCharAttribWordLineMode::SetFont( SvxFont& rFont, OutputDevice* )
/*N*/ {
/*N*/   rFont.SetWordLineMode( ((const SvxWordLineModeItem*)GetItem())->GetValue() );
/*N*/ }

// -------------------------------------------------------------------------
// class EditCharAttribEmphasisMark
// -------------------------------------------------------------------------
/*N*/ EditCharAttribEmphasisMark::EditCharAttribEmphasisMark( const SvxEmphasisMarkItem& rAttr, USHORT nStart, USHORT nEnd )
/*N*/   : EditCharAttrib( rAttr, nStart, nEnd )
/*N*/ {
/*N*/   DBG_ASSERT( rAttr.Which() == EE_CHAR_EMPHASISMARK, "Kein Emphasisattribut!" );
/*N*/ }

/*N*/ void EditCharAttribEmphasisMark::SetFont( SvxFont& rFont, OutputDevice* )
/*N*/ {
/*N*/   rFont.SetEmphasisMark( ((const SvxEmphasisMarkItem*)GetItem())->GetEmphasisMark() );
/*N*/ }

// -------------------------------------------------------------------------
// class EditCharAttribRelief
// -------------------------------------------------------------------------
/*N*/ EditCharAttribRelief::EditCharAttribRelief( const SvxCharReliefItem& rAttr, USHORT nStart, USHORT nEnd )
/*N*/   : EditCharAttrib( rAttr, nStart, nEnd )
/*N*/ {
/*N*/   DBG_ASSERT( rAttr.Which() == EE_CHAR_RELIEF, "Not a relief attribute!" );
/*N*/ }

/*N*/ void EditCharAttribRelief::SetFont( SvxFont& rFont, OutputDevice* )
/*N*/ {
/*N*/   rFont.SetRelief( (FontRelief)((const SvxCharReliefItem*)GetItem())->GetValue() );
/*N*/ }
