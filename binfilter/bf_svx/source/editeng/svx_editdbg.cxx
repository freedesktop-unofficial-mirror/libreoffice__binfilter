/*************************************************************************
 *
 *  $RCSfile: svx_editdbg.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 15:33:25 $
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

// auto strip #include <eeng_pch.hxx>

// auto strip #ifndef _MSGBOX_HXX //autogen
// auto strip #include <vcl/msgbox.hxx>
// auto strip #endif
#pragma hdrstop

#ifndef _EEITEM_HXX
#include "eeitem.hxx"
#endif
#ifndef _EEITEMID_HXX
#include "eeitemid.hxx"
#endif

// auto strip #include <lspcitem.hxx>

// auto strip #include <lrspitem.hxx>
// auto strip #include <ulspitem.hxx>
// auto strip #include <cntritem.hxx>
// auto strip #include <colritem.hxx>
// auto strip #include <fhgtitem.hxx>
// auto strip #include <fontitem.hxx>
// auto strip #include <adjitem.hxx>
// auto strip #include <wghtitem.hxx>
// auto strip #include <postitem.hxx>
// auto strip #include <udlnitem.hxx>
// auto strip #include <crsditem.hxx>
// auto strip #include <shdditem.hxx>
// auto strip #include <escpitem.hxx>
// auto strip #include <kernitem.hxx>
// auto strip #include <wrlmitem.hxx>
// auto strip #include <akrnitem.hxx>
// auto strip #include <langitem.hxx>
// auto strip #include <emphitem.hxx>
// auto strip #include <numitem.hxx>
// auto strip #include <tstpitem.hxx>
// auto strip #include <charscaleitem.hxx>
// auto strip #include <charreliefitem.hxx>
// auto strip #include <frmdiritem.hxx>

// auto strip #ifndef _SV_OUTDEV_HXX
// auto strip #include <vcl/outdev.hxx>
// auto strip #endif

// auto strip #ifndef _VCL_POINTR_HXX
// auto strip #include <vcl/pointr.hxx>
// auto strip #endif

#ifndef _SV_WINDOW_HXX
#include <vcl/window.hxx>
#endif

// auto strip #include <impedit.hxx>
// auto strip #include <editeng.hxx>
// auto strip #include <editview.hxx>
#include <editdoc.hxx>
// auto strip #include <editdbg.hxx>
namespace binfilter {

#if defined( DBG_UTIL ) || ( OSL_DEBUG_LEVEL > 1 )

//STRIP001 ByteString DbgOutItem( const SfxItemPool& rPool, const SfxPoolItem& rItem )
//STRIP001 {
//STRIP001  ByteString aDebStr;
//STRIP001  switch ( rItem.Which() )
//STRIP001  {
//STRIP001         case EE_PARA_WRITINGDIR:
//STRIP001          aDebStr += "WritingDir=";
//STRIP001          aDebStr += ByteString::CreateFromInt32( ((SvxFrameDirectionItem&)rItem).GetValue() );
//STRIP001         break;
//STRIP001      case EE_PARA_OUTLLRSPACE:
//STRIP001      case EE_PARA_LRSPACE:
//STRIP001          aDebStr += "FI=";
//STRIP001          aDebStr += ByteString::CreateFromInt32( ((SvxLRSpaceItem&)rItem).GetTxtFirstLineOfst() );
//STRIP001          aDebStr += ", LI=";
//STRIP001          aDebStr += ByteString::CreateFromInt32( ((SvxLRSpaceItem&)rItem).GetTxtLeft() );
//STRIP001          aDebStr += ", RI=";
//STRIP001          aDebStr += ByteString::CreateFromInt32( ((SvxLRSpaceItem&)rItem).GetRight() );
//STRIP001      break;
//STRIP001      case EE_PARA_NUMBULLET:
//STRIP001          {
//STRIP001          aDebStr += "NumItem ";
//STRIP001          for ( int nLevel = 0; nLevel < 3; nLevel++ )
//STRIP001          {
//STRIP001              aDebStr += "Level";
//STRIP001              aDebStr += ByteString::CreateFromInt32( nLevel );
//STRIP001              aDebStr += "=";
//STRIP001              const SvxNumberFormat* pFmt = ((const SvxNumBulletItem&)rItem).GetNumRule()->Get( nLevel );
//STRIP001              if ( pFmt )
//STRIP001              {
//STRIP001                  aDebStr += "(";
//STRIP001                  aDebStr += ByteString::CreateFromInt32( pFmt->GetFirstLineOffset() );
//STRIP001                  aDebStr += ",";
//STRIP001                  aDebStr += ByteString::CreateFromInt32( pFmt->GetAbsLSpace() );
//STRIP001                  aDebStr += ",";
//STRIP001                  if ( pFmt->GetNumberingType() == SVX_NUM_BITMAP )
//STRIP001                  {
//STRIP001                      aDebStr += "Bitmap";
//STRIP001                  }
//STRIP001                  else if( pFmt->GetNumberingType() != SVX_NUM_CHAR_SPECIAL )
//STRIP001                  {
//STRIP001                      aDebStr += "Number";
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      aDebStr += "Char=[";
//STRIP001                      aDebStr += ByteString::CreateFromInt32( pFmt->GetBulletChar() );
//STRIP001                      aDebStr += "]";
//STRIP001                  }
//STRIP001                  aDebStr += ") ";
//STRIP001              }
//STRIP001          }
//STRIP001          }
//STRIP001      break;
//STRIP001      case EE_PARA_BULLETSTATE:
//STRIP001          aDebStr += "ShowBullet=";
//STRIP001          aDebStr += ByteString::CreateFromInt32( ((SfxUInt16Item&)rItem).GetValue() );
//STRIP001      break;
//STRIP001      case EE_PARA_HYPHENATE:
//STRIP001          aDebStr += "Hyphenate=";
//STRIP001          aDebStr += ByteString::CreateFromInt32( ((SfxBoolItem&)rItem).GetValue() );
//STRIP001      break;
//STRIP001      case EE_PARA_OUTLLEVEL:
//STRIP001          aDebStr += "Level=";
//STRIP001          aDebStr += ByteString::CreateFromInt32( ((SfxUInt16Item&)rItem).GetValue() );
//STRIP001      break;
//STRIP001      case EE_PARA_ULSPACE:
//STRIP001          aDebStr += "SB=";
//STRIP001          aDebStr += ByteString::CreateFromInt32( ((SvxULSpaceItem&)rItem).GetUpper() );
//STRIP001          aDebStr += ", SA=";
//STRIP001          aDebStr += ByteString::CreateFromInt32( ((SvxULSpaceItem&)rItem).GetLower() );
//STRIP001      break;
//STRIP001      case EE_PARA_SBL:
//STRIP001          aDebStr += "SBL=";
//STRIP001          if ( ((SvxLineSpacingItem&)rItem).GetLineSpaceRule() == SVX_LINE_SPACE_MIN )
//STRIP001          {
//STRIP001              aDebStr += "Min: ";
//STRIP001              aDebStr += ByteString::CreateFromInt32( ((SvxLineSpacingItem&)rItem).GetInterLineSpace() );
//STRIP001          }
//STRIP001          else if ( ((SvxLineSpacingItem&)rItem).GetInterLineSpaceRule() == SVX_INTER_LINE_SPACE_PROP )
//STRIP001          {
//STRIP001              aDebStr += "Prop: ";
//STRIP001              aDebStr += ByteString::CreateFromInt32( (ULONG)((SvxLineSpacingItem&)rItem).GetPropLineSpace() );
//STRIP001          }
//STRIP001          else
//STRIP001              aDebStr += "Unsupported Type!";
//STRIP001      break;
//STRIP001      case EE_PARA_JUST:
//STRIP001          aDebStr += "SvxAdust=";
//STRIP001          aDebStr += ByteString::CreateFromInt32( (USHORT)((SvxAdjustItem&)rItem).GetAdjust() );
//STRIP001      break;
//STRIP001      case EE_PARA_TABS:
//STRIP001         {
//STRIP001          aDebStr += "Tabs: ";
//STRIP001          const SvxTabStopItem& rTabs = (const SvxTabStopItem&) rItem;
//STRIP001             aDebStr += ByteString::CreateFromInt32( rTabs.Count() );
//STRIP001             if ( rTabs.Count() )
//STRIP001             {
//STRIP001              aDebStr += "( ";
//STRIP001              for ( USHORT i = 0; i < rTabs.Count(); i++ )
//STRIP001              {
//STRIP001                  const SvxTabStop& rTab = rTabs[i];
//STRIP001                     aDebStr += ByteString::CreateFromInt32( rTab.GetTabPos() );
//STRIP001                  aDebStr += " ";
//STRIP001              }
//STRIP001              aDebStr += ")";
//STRIP001             }
//STRIP001         }
//STRIP001      break;
//STRIP001      case EE_CHAR_LANGUAGE:
//STRIP001      case EE_CHAR_LANGUAGE_CJK:
//STRIP001      case EE_CHAR_LANGUAGE_CTL:
//STRIP001          aDebStr += "Language=";
//STRIP001          aDebStr += ByteString::CreateFromInt32( (USHORT)((SvxLanguageItem&)rItem).GetLanguage() );
//STRIP001      break;
//STRIP001      case EE_CHAR_COLOR:
//STRIP001      {
//STRIP001          aDebStr += "Color= ";
//STRIP001          Color aColor( ((SvxColorItem&)rItem).GetValue() );
//STRIP001          aDebStr += ByteString::CreateFromInt32( (USHORT)aColor.GetRed() );
//STRIP001          aDebStr += ", ";
//STRIP001          aDebStr += ByteString::CreateFromInt32( (USHORT)aColor.GetGreen() );
//STRIP001          aDebStr += ", ";
//STRIP001          aDebStr += ByteString::CreateFromInt32( (USHORT)aColor.GetBlue() );
//STRIP001      }
//STRIP001      break;
//STRIP001      case EE_CHAR_FONTINFO:
//STRIP001      case EE_CHAR_FONTINFO_CJK:
//STRIP001      case EE_CHAR_FONTINFO_CTL:
//STRIP001      {
//STRIP001          aDebStr += "Font=";
//STRIP001          aDebStr += ByteString( ((SvxFontItem&)rItem).GetFamilyName(), RTL_TEXTENCODING_ASCII_US );
//STRIP001          aDebStr += " (CharSet: ";
//STRIP001          aDebStr += ByteString::CreateFromInt32( (USHORT)((SvxFontItem&)rItem).GetCharSet() );
//STRIP001          aDebStr += ')';
//STRIP001      }
//STRIP001      break;
//STRIP001      case EE_CHAR_FONTHEIGHT:
//STRIP001      case EE_CHAR_FONTHEIGHT_CJK:
//STRIP001      case EE_CHAR_FONTHEIGHT_CTL:
//STRIP001      {
//STRIP001          aDebStr += "Groesse=";
//STRIP001          aDebStr += ByteString::CreateFromInt32( ((SvxFontHeightItem&)rItem).GetHeight() );
//STRIP001          Size aSz( 0, ((SvxFontHeightItem&)rItem).GetHeight() );
//STRIP001          SfxMapUnit eUnit = rPool.GetMetric( rItem.Which() );
//STRIP001          MapMode aItemMapMode( (MapUnit) eUnit );
//STRIP001          MapMode aPntMap( MAP_POINT );
//STRIP001          aSz = OutputDevice::LogicToLogic( aSz, aItemMapMode, aPntMap );
//STRIP001          aDebStr += " Points=";
//STRIP001          aDebStr += ByteString::CreateFromInt32( aSz.Height() );
//STRIP001      }
//STRIP001      break;
//STRIP001      case EE_CHAR_FONTWIDTH:
//STRIP001      {
//STRIP001          aDebStr += "Breite=";
//STRIP001          aDebStr += ByteString::CreateFromInt32( ((SvxCharScaleWidthItem&)rItem).GetValue() );
//STRIP001          aDebStr += "%";
//STRIP001      }
//STRIP001      break;
//STRIP001      case EE_CHAR_WEIGHT:
//STRIP001      case EE_CHAR_WEIGHT_CJK:
//STRIP001      case EE_CHAR_WEIGHT_CTL:
//STRIP001          aDebStr += "FontWeight=";
//STRIP001          aDebStr += ByteString::CreateFromInt32( (USHORT)((SvxWeightItem&)rItem).GetWeight() );
//STRIP001      break;
//STRIP001      case EE_CHAR_UNDERLINE:
//STRIP001          aDebStr += "FontUnderline=";
//STRIP001          aDebStr += ByteString::CreateFromInt32( (USHORT)((SvxUnderlineItem&)rItem).GetUnderline() );
//STRIP001      break;
//STRIP001      case EE_CHAR_EMPHASISMARK:
//STRIP001          aDebStr += "FontUnderline=";
//STRIP001          aDebStr += ByteString::CreateFromInt32( (USHORT)((SvxEmphasisMarkItem&)rItem).GetEmphasisMark() );
//STRIP001      break;
//STRIP001      case EE_CHAR_RELIEF:
//STRIP001          aDebStr += "FontRelief=";
//STRIP001          aDebStr += ByteString::CreateFromInt32( (USHORT)((SvxCharReliefItem&)rItem).GetValue() );
//STRIP001      break;
//STRIP001      case EE_CHAR_STRIKEOUT:
//STRIP001          aDebStr += "FontStrikeout=";
//STRIP001          aDebStr +=ByteString::CreateFromInt32(  (USHORT)((SvxCrossedOutItem&)rItem).GetStrikeout() );
//STRIP001      break;
//STRIP001      case EE_CHAR_ITALIC:
//STRIP001      case EE_CHAR_ITALIC_CJK:
//STRIP001      case EE_CHAR_ITALIC_CTL:
//STRIP001          aDebStr += "FontPosture=";
//STRIP001          aDebStr +=ByteString::CreateFromInt32(  (USHORT)((SvxPostureItem&)rItem).GetPosture() );
//STRIP001      break;
//STRIP001      case EE_CHAR_OUTLINE:
//STRIP001          aDebStr += "FontOutline=";
//STRIP001          aDebStr += ByteString::CreateFromInt32( (USHORT)((SvxContourItem&)rItem).GetValue() );
//STRIP001      break;
//STRIP001      case EE_CHAR_SHADOW:
//STRIP001          aDebStr += "FontShadowed=";
//STRIP001          aDebStr += ByteString::CreateFromInt32( (USHORT)((SvxShadowedItem&)rItem).GetValue() );
//STRIP001      break;
//STRIP001      case EE_CHAR_ESCAPEMENT:
//STRIP001          aDebStr += "Escape=";
//STRIP001          aDebStr += ByteString::CreateFromInt32( (short)((SvxEscapementItem&)rItem).GetEsc() );
//STRIP001          aDebStr += ", ";
//STRIP001          aDebStr += ByteString::CreateFromInt32( (short)((SvxEscapementItem&)rItem).GetProp() );
//STRIP001      break;
//STRIP001      case EE_CHAR_PAIRKERNING:
//STRIP001          aDebStr += "PairKerning=";
//STRIP001          aDebStr += ByteString::CreateFromInt32( (USHORT)((SvxAutoKernItem&)rItem).GetValue() );
//STRIP001      break;
//STRIP001      case EE_CHAR_KERNING:
//STRIP001      {
//STRIP001          aDebStr += "Kerning=";
//STRIP001          aDebStr += ByteString::CreateFromInt32( (short)((SvxKerningItem&)rItem).GetValue() );
//STRIP001          Size aSz( 0, (short)((SvxKerningItem&)rItem).GetValue() );
//STRIP001          SfxMapUnit eUnit = rPool.GetMetric( rItem.Which() );
//STRIP001          MapMode aItemMapMode( (MapUnit) eUnit );
//STRIP001          MapMode aPntMap( MAP_POINT );
//STRIP001          aSz = OutputDevice::LogicToLogic( aSz, aItemMapMode, aPntMap );
//STRIP001          aDebStr += " Points=";
//STRIP001          aDebStr += ByteString::CreateFromInt32( aSz.Height() );
//STRIP001      }
//STRIP001      break;
//STRIP001      case EE_CHAR_WLM:
//STRIP001          aDebStr += "WordLineMode=";
//STRIP001          aDebStr += ByteString::CreateFromInt32( (USHORT)((SvxWordLineModeItem&)rItem).GetValue() );
//STRIP001      break;
//STRIP001      case EE_CHAR_XMLATTRIBS:
//STRIP001          aDebStr += "XMLAttribs=...";
//STRIP001      break;
//STRIP001  }
//STRIP001  return aDebStr;
//STRIP001 }

//STRIP001 void DbgOutItemSet( FILE* fp, const SfxItemSet& rSet, BOOL bSearchInParent, BOOL bShowALL )
//STRIP001 {
//STRIP001  for ( USHORT nWhich = EE_PARA_START; nWhich <= EE_CHAR_END; nWhich++ )
//STRIP001  {
//STRIP001      fprintf( fp, "\nWhich: %i\t", nWhich );
//STRIP001      if ( rSet.GetItemState( nWhich, bSearchInParent ) == SFX_ITEM_OFF )
//STRIP001          fprintf( fp, "ITEM_OFF   " );
//STRIP001      else if ( rSet.GetItemState( nWhich, bSearchInParent ) == SFX_ITEM_DONTCARE )
//STRIP001          fprintf( fp, "ITEM_DC    " );
//STRIP001      else if ( rSet.GetItemState( nWhich, bSearchInParent ) == SFX_ITEM_ON )
//STRIP001          fprintf( fp, "ITEM_ON   *" );
//STRIP001
//STRIP001      if ( !bShowALL && ( rSet.GetItemState( nWhich, bSearchInParent ) != SFX_ITEM_ON ) )
//STRIP001          continue;
//STRIP001
//STRIP001      const SfxPoolItem& rItem = rSet.Get( nWhich, bSearchInParent );
//STRIP001      ByteString aDebStr = DbgOutItem( *rSet.GetPool(), rItem );
//STRIP001      fprintf( fp, "%s", aDebStr.GetBuffer() );
//STRIP001  }
//STRIP001 }

//STRIP001 void EditDbg::ShowEditEngineData( EditEngine* pEE, BOOL bInfoBox )
//STRIP001 {
//STRIP001 #ifdef MAC
//STRIP001  FILE* fp = fopen( "debug.log", "w" );
//STRIP001 #elif defined UNX
//STRIP001  FILE* fp = fopen( "/tmp/debug.log", "w" );
//STRIP001 #else
//STRIP001  FILE* fp = fopen( "d:\\debug.log", "w" );
//STRIP001 #endif
//STRIP001  if ( fp == 0 )
//STRIP001  {
//STRIP001      DBG_ERROR( "Log-File konnte nicht angelegt werden!" );
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  const SfxItemPool& rPool = *pEE->GetEmptyItemSet().GetPool();
//STRIP001
//STRIP001  fprintf( fp, "================================================================================" );
//STRIP001  fprintf( fp, "\n==================   Dokument   ================================================" );
//STRIP001  fprintf( fp, "\n================================================================================" );
//STRIP001  for ( USHORT nPortion = 0; nPortion < pEE->pImpEditEngine->GetParaPortions(). Count(); nPortion++)
//STRIP001  {
//STRIP001
//STRIP001      ParaPortion* pPPortion = pEE->pImpEditEngine->GetParaPortions().GetObject(nPortion );
//STRIP001      fprintf( fp, "\nAbsatz %i: Laenge = %i, Invalid = %i\nText = '%s'", nPortion, pPPortion->GetNode()->Len(), pPPortion->IsInvalid(), ByteString( *pPPortion->GetNode(), RTL_TEXTENCODING_ASCII_US ).GetBuffer() );
//STRIP001      fprintf( fp, "\nVorlage:" );
//STRIP001      SfxStyleSheet* pStyle = pPPortion->GetNode()->GetStyleSheet();
//STRIP001      if ( pStyle )
//STRIP001          fprintf( fp, " %s", ByteString( pStyle->GetName(), RTL_TEXTENCODING_ASCII_US ).GetBuffer() );
//STRIP001      fprintf( fp, "\nAbsatzattribute:" );
//STRIP001      DbgOutItemSet( fp, pPPortion->GetNode()->GetContentAttribs().GetItems(), FALSE, FALSE );
//STRIP001
//STRIP001      fprintf( fp, "\nZeichenattribute:" );
//STRIP001      BOOL bZeroAttr = FALSE;
//STRIP001      for ( USHORT z = 0; z < pPPortion->GetNode()->GetCharAttribs().Count(); z++ )
//STRIP001      {
//STRIP001          EditCharAttrib* pAttr = pPPortion->GetNode()->GetCharAttribs().GetAttribs().GetObject( z );
//STRIP001          ByteString aCharAttribs;
//STRIP001          aCharAttribs += "\nA";
//STRIP001          aCharAttribs += ByteString::CreateFromInt32( nPortion );
//STRIP001          aCharAttribs += ":  ";
//STRIP001          aCharAttribs += ByteString::CreateFromInt32( pAttr->GetItem()->Which() );
//STRIP001          aCharAttribs += '\t';
//STRIP001          aCharAttribs += ByteString::CreateFromInt32( pAttr->GetStart() );
//STRIP001          aCharAttribs += '\t';
//STRIP001          aCharAttribs += ByteString::CreateFromInt32( pAttr->GetEnd() );
//STRIP001          if ( pAttr->IsEmpty() )
//STRIP001              bZeroAttr = TRUE;
//STRIP001          fprintf( fp, "%s => ", aCharAttribs.GetBuffer() );
//STRIP001
//STRIP001          ByteString aDebStr = DbgOutItem( rPool, *pAttr->GetItem() );
//STRIP001          fprintf( fp, "%s", aDebStr.GetBuffer() );
//STRIP001      }
//STRIP001      if ( bZeroAttr )
//STRIP001          fprintf( fp, "\nNULL-Attribute!" );
//STRIP001
//STRIP001      USHORT nTextPortions = pPPortion->GetTextPortions().Count();
//STRIP001      ByteString aPortionStr("\nTextportions: #");
//STRIP001      aPortionStr += ByteString::CreateFromInt32( nTextPortions );
//STRIP001      aPortionStr += " \nA";
//STRIP001      aPortionStr += ByteString::CreateFromInt32( nPortion );
//STRIP001      aPortionStr += ": Absatzlaenge = ";
//STRIP001      aPortionStr += ByteString::CreateFromInt32( pPPortion->GetNode()->Len() );
//STRIP001      aPortionStr += "\nA";
//STRIP001      aPortionStr += ByteString::CreateFromInt32( nPortion );
//STRIP001      aPortionStr += ": ";
//STRIP001      ULONG n = 0;
//STRIP001      for ( z = 0; z < nTextPortions; z++ )
//STRIP001      {
//STRIP001          TextPortion* pPortion = pPPortion->GetTextPortions().GetObject( z );
//STRIP001          aPortionStr += " ";
//STRIP001          aPortionStr += ByteString::CreateFromInt32( pPortion->GetLen() );
//STRIP001          aPortionStr += "(";
//STRIP001          aPortionStr += ByteString::CreateFromInt32( pPortion->GetSize().Width() );
//STRIP001          aPortionStr += ")";
//STRIP001          aPortionStr += "[";
//STRIP001          aPortionStr += ByteString::CreateFromInt32( (USHORT)pPortion->GetKind() );
//STRIP001          aPortionStr += "]";
//STRIP001          aPortionStr += ";";
//STRIP001          n += pPortion->GetLen();
//STRIP001      }
//STRIP001      aPortionStr += "\nA";
//STRIP001      aPortionStr += ByteString::CreateFromInt32( nPortion );
//STRIP001      aPortionStr += ": Gesamtlaenge: ";
//STRIP001      aPortionStr += ByteString::CreateFromInt32( n );
//STRIP001      if ( pPPortion->GetNode()->Len() != n )
//STRIP001          aPortionStr += " => Fehler !!!";
//STRIP001      fprintf( fp, "%s", aPortionStr.GetBuffer() );
//STRIP001
//STRIP001
//STRIP001      fprintf( fp, "\n\nZeilen:" );
//STRIP001      // Erstmal die Inhalte...
//STRIP001      for ( USHORT nLine = 0; nLine < pPPortion->GetLines().Count(); nLine++ )
//STRIP001      {
//STRIP001          EditLine* pLine = pPPortion->GetLines().GetObject( nLine );
//STRIP001
//STRIP001          ByteString aLine( *(pPPortion->GetNode()), pLine->GetStart(), pLine->GetEnd() - pLine->GetStart(), RTL_TEXTENCODING_ASCII_US );
//STRIP001          fprintf( fp, "\nZeile %i\t>%s<", nLine, aLine.GetBuffer() );
//STRIP001      }
//STRIP001      // dann die internen Daten...
//STRIP001      for ( nLine = 0; nLine < pPPortion->GetLines().Count(); nLine++ )
//STRIP001      {
//STRIP001          EditLine* pLine = pPPortion->GetLines().GetObject( nLine );
//STRIP001          fprintf( fp, "\nZeile %i:\tStart: %i,\tEnd: %i", nLine, pLine->GetStart(), pLine->GetEnd() );
//STRIP001          fprintf( fp, "\t\tPortions: %i - %i.\tHoehe: %i, Ascent=%i", pLine->GetStartPortion(), pLine->GetEndPortion(), pLine->GetHeight(), pLine->GetMaxAscent() );
//STRIP001      }
//STRIP001
//STRIP001      fprintf( fp, "\n-----------------------------------------------------------------------------" );
//STRIP001  }
//STRIP001
//STRIP001  if ( pEE->pImpEditEngine->GetStyleSheetPool() )
//STRIP001  {
//STRIP001      ULONG nStyles = pEE->pImpEditEngine->GetStyleSheetPool() ? pEE->pImpEditEngine->GetStyleSheetPool()->Count() : 0;
//STRIP001      fprintf( fp, "\n\n================================================================================" );
//STRIP001      fprintf( fp, "\n==================   Stylesheets   =============================================" );
//STRIP001      fprintf( fp, "\n================================================================================" );
//STRIP001      fprintf( fp, "\n#Vorlagen:   %lu\n", nStyles );
//STRIP001      SfxStyleSheetIterator aIter( pEE->pImpEditEngine->GetStyleSheetPool(), SFX_STYLE_FAMILY_ALL );
//STRIP001      SfxStyleSheetBase* pStyle = aIter.First();
//STRIP001      while ( pStyle )
//STRIP001      {
//STRIP001          fprintf( fp, "\nVorlage:   %s", ByteString( pStyle->GetName(), RTL_TEXTENCODING_ASCII_US ).GetBuffer() );
//STRIP001          fprintf( fp, "\nParent:    %s", ByteString( pStyle->GetParent(), RTL_TEXTENCODING_ASCII_US ).GetBuffer() );
//STRIP001          fprintf( fp, "\nFollow:    %s", ByteString( pStyle->GetFollow(), RTL_TEXTENCODING_ASCII_US ).GetBuffer() );
//STRIP001          DbgOutItemSet( fp, pStyle->GetItemSet(), FALSE, FALSE );
//STRIP001          fprintf( fp, "\n----------------------------------" );
//STRIP001
//STRIP001          pStyle = aIter.Next();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  fprintf( fp, "\n\n================================================================================" );
//STRIP001  fprintf( fp, "\n==================   Defaults   ================================================" );
//STRIP001  fprintf( fp, "\n================================================================================" );
//STRIP001  DbgOutItemSet( fp, pEE->pImpEditEngine->GetEmptyItemSet(), TRUE, TRUE );
//STRIP001
//STRIP001  fprintf( fp, "\n\n================================================================================" );
//STRIP001  fprintf( fp, "\n==================   EditEngine & Views   ======================================" );
//STRIP001  fprintf( fp, "\n================================================================================" );
//STRIP001  fprintf( fp, "\nControl: %lx", pEE->GetControlWord() );
//STRIP001  fprintf( fp, "\nRefMapMode: %i", pEE->pImpEditEngine->pRefDev->GetMapMode().GetMapUnit() );
//STRIP001  fprintf( fp, "\nPaperSize: %li x %li", pEE->GetPaperSize().Width(), pEE->GetPaperSize().Height() );
//STRIP001  fprintf( fp, "\nMaxAutoPaperSize: %li x %li", pEE->GetMaxAutoPaperSize().Width(), pEE->GetMaxAutoPaperSize().Height() );
//STRIP001  fprintf( fp, "\nMinAutoPaperSize: %li x %li", pEE->GetMinAutoPaperSize().Width(), pEE->GetMinAutoPaperSize().Height() );
//STRIP001  fprintf( fp, "\nUpdate: %i", pEE->GetUpdateMode() );
//STRIP001  fprintf( fp, "\nAnzahl der Views: %i", pEE->GetViewCount() );
//STRIP001  for ( USHORT nView = 0; nView < pEE->GetViewCount(); nView++ )
//STRIP001  {
//STRIP001      EditView* pV = pEE->GetView( nView );
//STRIP001      DBG_ASSERT( pV, "View nicht gefunden!" );
//STRIP001      fprintf( fp, "\nView %i: Focus=%i", nView, pV->GetWindow()->HasFocus() );
//STRIP001      Rectangle aR( pV->GetOutputArea() );
//STRIP001      fprintf( fp, "\n  OutputArea: nX=%li, nY=%li, dX=%li, dY=%li, MapMode = %i", aR.TopLeft().X(), aR.TopLeft().Y(), aR.GetSize().Width(), aR.GetSize().Height() , pV->GetWindow()->GetMapMode().GetMapUnit() );
//STRIP001      aR = pV->GetVisArea();
//STRIP001      fprintf( fp, "\n  VisArea: nX=%li, nY=%li, dX=%li, dY=%li", aR.TopLeft().X(), aR.TopLeft().Y(), aR.GetSize().Width(), aR.GetSize().Height() );
//STRIP001      ESelection aSel = pV->GetSelection();
//STRIP001      fprintf( fp, "\n  Selektion: Start=%u,%u, End=%u,%u", aSel.nStartPara, aSel.nStartPos, aSel.nEndPara, aSel.nEndPos );
//STRIP001  }
//STRIP001  if ( pEE->GetActiveView() )
//STRIP001  {
//STRIP001      fprintf( fp, "\n\n================================================================================" );
//STRIP001      fprintf( fp, "\n==================   Aktuelle View   ===========================================" );
//STRIP001      fprintf( fp, "\n================================================================================" );
//STRIP001      DbgOutItemSet( fp, pEE->GetActiveView()->GetAttribs(), TRUE, FALSE );
//STRIP001  }
//STRIP001  fclose( fp );
//STRIP001  if ( bInfoBox )
//STRIP001      InfoBox(0, String( RTL_CONSTASCII_USTRINGPARAM( "D:\\DEBUG.LOG !" ) ) ).Execute();
//STRIP001 }

//STRIP001 ByteString EditDbg::GetPortionInfo( ParaPortion* pPPortion )
//STRIP001 {
//STRIP001  ByteString aDebStr( "Absatzlaenge = " );
//STRIP001  aDebStr += ByteString::CreateFromInt32( pPPortion->GetNode()->Len() );
//STRIP001
//STRIP001  aDebStr += "\nZeichenattribute:";
//STRIP001  for ( USHORT z = 0; z < pPPortion->GetNode()->GetCharAttribs().Count(); z++ )
//STRIP001  {
//STRIP001      EditCharAttrib* pAttr = pPPortion->GetNode()->GetCharAttribs().GetAttribs().GetObject( z );
//STRIP001      aDebStr += "\n  ";
//STRIP001      aDebStr += ByteString::CreateFromInt32( pAttr->GetItem()->Which() );
//STRIP001      aDebStr += '\t';
//STRIP001      aDebStr += ByteString::CreateFromInt32( pAttr->GetStart() );
//STRIP001      aDebStr += '\t';
//STRIP001      aDebStr += ByteString::CreateFromInt32( pAttr->GetEnd() );
//STRIP001  }
//STRIP001
//STRIP001  aDebStr += "\nTextportions:";
//STRIP001  USHORT n = 0;
//STRIP001  for ( z = 0; z < pPPortion->GetTextPortions().Count(); z++ )
//STRIP001  {
//STRIP001      TextPortion* pPortion = pPPortion->GetTextPortions().GetObject( z );
//STRIP001      aDebStr += " ";
//STRIP001      aDebStr += ByteString::CreateFromInt32( pPortion->GetLen() );
//STRIP001      aDebStr += "(";
//STRIP001      aDebStr += ByteString::CreateFromInt32( pPortion->GetSize().Width() );
//STRIP001      aDebStr += ")";
//STRIP001      aDebStr += ";";
//STRIP001      n += pPortion->GetLen();
//STRIP001  }
//STRIP001  aDebStr += "\nGesamtlaenge: ";
//STRIP001  aDebStr += ByteString::CreateFromInt32( n );
//STRIP001  aDebStr += "\nSortiert nach Start:";
//STRIP001  for ( USHORT x = 0; x < pPPortion->GetNode()->GetCharAttribs().Count(); x++ )
//STRIP001  {
//STRIP001      EditCharAttrib* pCurAttrib = pPPortion->GetNode()->GetCharAttribs().GetAttribs().GetObject( x );
//STRIP001      aDebStr += "\nStart: ";
//STRIP001      aDebStr += ByteString::CreateFromInt32( pCurAttrib->GetStart() );
//STRIP001      aDebStr += "\tEnde: ";
//STRIP001      aDebStr += ByteString::CreateFromInt32( pCurAttrib->GetEnd() );
//STRIP001  }
//STRIP001  return aDebStr;
//STRIP001 }

//STRIP001 ByteString EditDbg::GetTextPortionInfo( TextPortionList& rPortions )
//STRIP001 {
//STRIP001  ByteString aDebStr;
//STRIP001  for ( USHORT z = 0; z < rPortions.Count(); z++ )
//STRIP001  {
//STRIP001      TextPortion* pPortion = rPortions.GetObject( z );
//STRIP001      aDebStr += " ";
//STRIP001      aDebStr += ByteString::CreateFromInt32( pPortion->GetLen() );
//STRIP001      aDebStr += "(";
//STRIP001      aDebStr += ByteString::CreateFromInt32( pPortion->GetSize().Width() );
//STRIP001      aDebStr += ")";
//STRIP001      aDebStr += ";";
//STRIP001  }
//STRIP001  return aDebStr;
//STRIP001 }

//STRIP001 void EditDbg::ShowPortionData( ParaPortion* pPortion )
//STRIP001 {
//STRIP001  ByteString aDebStr( GetPortionInfo( pPortion ) );
//STRIP001  InfoBox( 0, String( aDebStr, RTL_TEXTENCODING_ASCII_US )  ).Execute();
//STRIP001 }


//STRIP001 BOOL ParaPortion::DbgCheckTextPortions()
//STRIP001 {
//STRIP001  // pruefen, ob Portionlaenge ok:
//STRIP001  USHORT nXLen = 0;
//STRIP001  for ( USHORT nPortion = 0; nPortion < aTextPortionList.Count(); nPortion++  )
//STRIP001      nXLen += aTextPortionList[nPortion]->GetLen();
//STRIP001  return nXLen == pNode->Len() ? TRUE : FALSE;
//STRIP001 }

/*N*/ BOOL CheckOrderedList( CharAttribArray& rAttribs, BOOL bStart )
/*N*/ {
/*N*/   USHORT nPrev = 0;
/*N*/   for ( USHORT nAttr = 0; nAttr < rAttribs.Count(); nAttr++ )
/*N*/   {
/*N*/       EditCharAttrib* pAttr = rAttribs[nAttr];
/*N*/       USHORT nCur = bStart ? pAttr->GetStart() : pAttr->GetEnd();
/*N*/       if ( nCur < nPrev )
/*N*/           return FALSE;
/*N*/
/*N*/       nPrev = nCur;
/*N*/   }
/*N*/   return TRUE;
/*N*/ }

#endif

}
