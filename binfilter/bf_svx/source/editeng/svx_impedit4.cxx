/*************************************************************************
 *
 *  $RCSfile: svx_impedit4.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2004-02-13 14:30:39 $
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

#ifndef _MSGBOX_HXX //autogen
#include <vcl/msgbox.hxx>
#endif
#include <vcl/svapp.hxx>
#pragma hdrstop

//#include <vcl/system.hxx>
#include <srchitem.hxx>
#include <lspcitem.hxx>
#include <adjitem.hxx>
#include <tstpitem.hxx>

#include <eertfpar.hxx>
#include <impedit.hxx>
#include <editview.hxx>
#include <eehtml.hxx>
#include <editobj2.hxx>
#include <tools/isolang.hxx>

#include <editxml.hxx>


#include "akrnitem.hxx"
#include "cntritem.hxx"
#include "colritem.hxx"
#include "crsditem.hxx"
#include "escpitem.hxx"
#include "fhgtitem.hxx"
#include "fontitem.hxx"
#include "kernitem.hxx"
#include "lrspitem.hxx"
#include "postitem.hxx"
#include "shdditem.hxx"
#include "udlnitem.hxx"
#include "ulspitem.hxx"
#include "wghtitem.hxx"
#include "langitem.hxx"
#include <charreliefitem.hxx>
#include <frmdiritem.hxx>
#include <emphitem.hxx>

#include <rtl/tencinfo.h>

#include <svtools/rtfout.hxx>

#ifndef SVX_LIGHT
#include <edtspell.hxx>
#endif

#ifndef _UNO_LINGU_HXX
#include <unolingu.hxx>
#endif
#ifndef _SFX_SFXUNO_HXX
#include <bf_sfx2/sfxuno.hxx>
#endif
#ifndef _LINGUISTIC_LNGPROPS_HHX_
#include <bf_linguistic/lngprops.hxx>
#endif
#ifndef _COM_SUN_STAR_LINGUISTIC2_XTHESAURUS_HPP_
#include <com/sun/star/linguistic2/XThesaurus.hpp>
#endif
#ifndef _COM_SUN_STAR_LINGUISTIC2_XMEANING_HPP_
#include <com/sun/star/linguistic2/XMeaning.hpp>
#endif

#ifndef _UNOTOOLS_TRANSLITERATIONWRAPPER_HXX
#include <unotools/transliterationwrapper.hxx>
#endif

#ifndef _TXTCMP_HXX //autogen
#include <unotools/textsearch.hxx>
#endif

#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif

#ifndef _SV_HELP_HXX //autogen
#include <vcl/help.hxx>
#endif

#include <svtools/rtfkeywd.hxx>
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::linguistic2;

//STRIP001 void SwapUSHORTs( sal_uInt16& rX, sal_uInt16& rY )
//STRIP001 {
//STRIP001  sal_uInt16 n = rX;
//STRIP001  rX = rY;
//STRIP001  rY = n;
//STRIP001 }

//STRIP001 EditPaM ImpEditEngine::Read( SvStream& rInput, EETextFormat eFormat, EditSelection aSel, SvKeyValueIterator* pHTTPHeaderAttrs )
//STRIP001 {
//STRIP001  sal_Bool bUpdate = GetUpdateMode();
//STRIP001  SetUpdateMode( sal_False );
//STRIP001  EditPaM aPaM;
//STRIP001  if ( eFormat == EE_FORMAT_TEXT )
//STRIP001      aPaM = ReadText( rInput, aSel );
//STRIP001  else if ( eFormat == EE_FORMAT_RTF )
//STRIP001      aPaM = ReadRTF( rInput, aSel );
//STRIP001  else if ( eFormat == EE_FORMAT_XML )
//STRIP001      aPaM = ReadXML( rInput, aSel );
//STRIP001  else if ( eFormat == EE_FORMAT_HTML )
//STRIP001      aPaM = ReadHTML( rInput, aSel, pHTTPHeaderAttrs );
//STRIP001  else if ( eFormat == EE_FORMAT_BIN)
//STRIP001      aPaM = ReadBin( rInput, aSel );
//STRIP001  else
//STRIP001      DBG_ERROR( "Read: Unbekanntes Format" );
//STRIP001
//STRIP001  FormatFullDoc();        // reicht vielleicht auch ein einfaches Format?
//STRIP001  SetUpdateMode( bUpdate );
//STRIP001
//STRIP001  return aPaM;
//STRIP001 }

//STRIP001 EditPaM ImpEditEngine::ReadText( SvStream& rInput, EditSelection aSel )
//STRIP001 {
//STRIP001  if ( aSel.HasRange() )
//STRIP001      aSel = ImpDeleteSelection( aSel );
//STRIP001  EditPaM aPaM = aSel.Max();
//STRIP001
//STRIP001  XubString aTmpStr, aStr;
//STRIP001  sal_Bool bDone = rInput.ReadByteStringLine( aTmpStr );
//STRIP001  while ( bDone )
//STRIP001  {
//STRIP001      aTmpStr.Erase( MAXCHARSINPARA );
//STRIP001      aPaM = ImpInsertText( EditSelection( aPaM, aPaM ), aTmpStr );
//STRIP001      aPaM = ImpInsertParaBreak( aPaM );
//STRIP001      bDone = rInput.ReadByteStringLine( aTmpStr );
//STRIP001  }
//STRIP001  return aPaM;
//STRIP001 }

//STRIP001 EditPaM ImpEditEngine::ReadXML( SvStream& rInput, EditSelection aSel )
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  if ( aSel.HasRange() )
//STRIP001      aSel = ImpDeleteSelection( aSel );
//STRIP001
//STRIP001     ESelection aESel = CreateESel( aSel );
//STRIP001
//STRIP001     ::SvxReadXML( *GetEditEnginePtr(), rInput, aESel );
//STRIP001
//STRIP001     return aSel.Max();
//STRIP001 #else
//STRIP001  return EditPaM();
//STRIP001 #endif
//STRIP001 }

//STRIP001 EditPaM ImpEditEngine::ReadRTF( SvStream& rInput, EditSelection aSel )
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001
//STRIP001 #if defined (EDITDEBUG) && !defined(MAC) && !defined( UNX )
//STRIP001  SvFileStream aRTFOut( String( RTL_CONSTASCII_USTRINGPARAM ( "d:\\rtf_in.rtf" ) ), STREAM_WRITE );
//STRIP001  aRTFOut << rInput;
//STRIP001  aRTFOut.Close();
//STRIP001  rInput.Seek( 0 );
//STRIP001 #endif
//STRIP001  if ( aSel.HasRange() )
//STRIP001      aSel = ImpDeleteSelection( aSel );
//STRIP001
//STRIP001  sal_Bool bCharsBeforeInsertPos = ( aSel.Min().GetIndex() ) ? sal_True : sal_False;
//STRIP001  sal_Bool bCharsBehindInsertPos = ( aSel.Min().GetIndex() < aSel.Min().GetNode()->Len() ) ? sal_True : sal_False;
//STRIP001
//STRIP001  // Der SvRTF-Parser erwartet, dass das Which-Mapping am uebergebenen Pool,
//STRIP001  // nicht an einem Secondary haengt.
//STRIP001  SfxItemPool* pPool = &aEditDoc.GetItemPool();
//STRIP001  while ( pPool->GetSecondaryPool() && !pPool->GetName().EqualsAscii( "EditEngineItemPool" ) )
//STRIP001  {
//STRIP001      pPool = pPool->GetSecondaryPool();
//STRIP001
//STRIP001  }
//STRIP001  DBG_ASSERT( pPool && pPool->GetName().EqualsAscii( "EditEngineItemPool" ), "ReadRTF: Kein EditEnginePool!" );
//STRIP001
//STRIP001  EditRTFParserRef xPrsr = new EditRTFParser( rInput, aSel, *pPool, this );
//STRIP001  SvParserState eState = xPrsr->CallParser();
//STRIP001  if ( ( eState != SVPAR_ACCEPTED ) && ( !rInput.GetError() ) )
//STRIP001  {
//STRIP001      rInput.SetError( EE_READWRITE_WRONGFORMAT );
//STRIP001      return aSel.Min();
//STRIP001  }
//STRIP001  return xPrsr->GetCurPaM();
//STRIP001 #else
//STRIP001  return EditPaM();
//STRIP001 #endif
//STRIP001 }

//STRIP001 EditPaM ImpEditEngine::ReadHTML( SvStream& rInput, EditSelection aSel, SvKeyValueIterator* pHTTPHeaderAttrs )
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001
//STRIP001  if ( aSel.HasRange() )
//STRIP001      aSel = ImpDeleteSelection( aSel );
//STRIP001
//STRIP001  sal_Bool bCharsBeforeInsertPos = ( aSel.Min().GetIndex() ) ? sal_True : sal_False;
//STRIP001  sal_Bool bCharsBehindInsertPos = ( aSel.Min().GetIndex() < aSel.Min().GetNode()->Len() ) ? sal_True : sal_False;
//STRIP001
//STRIP001  EditHTMLParserRef xPrsr = new EditHTMLParser( rInput, pHTTPHeaderAttrs );
//STRIP001  SvParserState eState = xPrsr->CallParser( this, aSel.Max() );
//STRIP001  if ( ( eState != SVPAR_ACCEPTED ) && ( !rInput.GetError() ) )
//STRIP001  {
//STRIP001      rInput.SetError( EE_READWRITE_WRONGFORMAT );
//STRIP001      return aSel.Min();
//STRIP001  }
//STRIP001  return xPrsr->GetCurSelection().Max();
//STRIP001 #else
//STRIP001  return EditPaM();
//STRIP001 #endif
//STRIP001 }

//STRIP001 EditPaM ImpEditEngine::ReadBin( SvStream& rInput, EditSelection aSel )
//STRIP001 {
//STRIP001  // Einfach ein temporaeres TextObject missbrauchen...
//STRIP001  EditTextObject* pObj = EditTextObject::Create( rInput, NULL );
//STRIP001
//STRIP001  EditPaM aLastPaM = aSel.Max();
//STRIP001  if ( pObj )
//STRIP001      aLastPaM = InsertText( *pObj, aSel ).Max();
//STRIP001
//STRIP001  delete pObj;
//STRIP001  return aLastPaM;
//STRIP001 }

#ifndef SVX_LIGHT
//STRIP001 void ImpEditEngine::Write( SvStream& rOutput, EETextFormat eFormat, EditSelection aSel )
//STRIP001 {
//STRIP001  if ( !rOutput.IsWritable() )
//STRIP001      rOutput.SetError( SVSTREAM_WRITE_ERROR );
//STRIP001
//STRIP001  if ( !rOutput.GetError() )
//STRIP001  {
//STRIP001      if ( eFormat == EE_FORMAT_TEXT )
//STRIP001          WriteText( rOutput, aSel );
//STRIP001      else if ( eFormat == EE_FORMAT_RTF )
//STRIP001          WriteRTF( rOutput, aSel );
//STRIP001      else if ( eFormat == EE_FORMAT_XML )
//STRIP001          WriteXML( rOutput, aSel );
//STRIP001      else if ( eFormat == EE_FORMAT_HTML )
//STRIP001          WriteHTML( rOutput, aSel );
//STRIP001      else if ( eFormat == EE_FORMAT_BIN)
//STRIP001          WriteBin( rOutput, aSel );
//STRIP001      else
//STRIP001          DBG_ERROR( "Write: Unbekanntes Format" );
//STRIP001  }
//STRIP001 }
#endif

//STRIP001 sal_uInt32 ImpEditEngine::WriteText( SvStream& rOutput, EditSelection aSel )
//STRIP001 {
//STRIP001  sal_uInt16 nStartNode, nEndNode;
//STRIP001  sal_Bool bRange = aSel.HasRange();
//STRIP001  if ( bRange )
//STRIP001  {
//STRIP001      aSel.Adjust( aEditDoc );
//STRIP001      nStartNode = aEditDoc.GetPos( aSel.Min().GetNode() );
//STRIP001      nEndNode = aEditDoc.GetPos( aSel.Max().GetNode() );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      nStartNode = 0;
//STRIP001      nEndNode = aEditDoc.Count()-1;
//STRIP001  }
//STRIP001
//STRIP001  // ueber die Absaetze iterieren...
//STRIP001  for ( sal_uInt16 nNode = nStartNode; nNode <= nEndNode; nNode++  )
//STRIP001  {
//STRIP001      ContentNode* pNode = aEditDoc.GetObject( nNode );
//STRIP001      DBG_ASSERT( pNode, "Node nicht gefunden: Search&Replace" );
//STRIP001
//STRIP001      sal_uInt16 nStartPos = 0;
//STRIP001      sal_uInt16 nEndPos = pNode->Len();
//STRIP001      if ( bRange )
//STRIP001      {
//STRIP001          if ( nNode == nStartNode )
//STRIP001              nStartPos = aSel.Min().GetIndex();
//STRIP001          if ( nNode == nEndNode ) // kann auch == nStart sein!
//STRIP001              nEndPos = aSel.Max().GetIndex();
//STRIP001      }
//STRIP001      XubString aTmpStr = aEditDoc.GetParaAsString( pNode, nStartPos, nEndPos );
//STRIP001      rOutput.WriteByteStringLine( aTmpStr );
//STRIP001  }
//STRIP001
//STRIP001  return rOutput.GetError();
//STRIP001 }

//STRIP001 sal_Bool ImpEditEngine::WriteItemListAsRTF( ItemList& rLst, SvStream& rOutput, sal_uInt16 nPara, sal_uInt16 nPos,
//STRIP001                      SvxFontTable& rFontTable, SvxColorList& rColorList )
//STRIP001 {
//STRIP001  const SfxPoolItem* pAttrItem = rLst.First();
//STRIP001  while ( pAttrItem )
//STRIP001  {
//STRIP001      WriteItemAsRTF( *pAttrItem, rOutput, nPara, nPos,rFontTable, rColorList );
//STRIP001      pAttrItem = rLst.Next();
//STRIP001  }
//STRIP001  return ( rLst.Count() ? sal_True : sal_False );
//STRIP001 }

//STRIP001 void lcl_FindValidAttribs( ItemList& rLst, ContentNode* pNode, sal_uInt16 nIndex, USHORT nScriptType )
//STRIP001 {
//STRIP001  sal_uInt16 nAttr = 0;
//STRIP001  EditCharAttrib* pAttr = GetAttrib( pNode->GetCharAttribs().GetAttribs(), nAttr );
//STRIP001  while ( pAttr && ( pAttr->GetStart() <= nIndex ) )
//STRIP001  {
//STRIP001      // Start wird in While ueberprueft...
//STRIP001      if ( pAttr->GetEnd() > nIndex )
//STRIP001         {
//STRIP001             if ( IsScriptItemValid( pAttr->GetItem()->Which(), nScriptType ) )
//STRIP001              rLst.Insert( pAttr->GetItem(), LIST_APPEND );
//STRIP001      }
//STRIP001      nAttr++;
//STRIP001      pAttr = GetAttrib( pNode->GetCharAttribs().GetAttribs(), nAttr );
//STRIP001  }
//STRIP001 }

//STRIP001 sal_uInt32 ImpEditEngine::WriteBin( SvStream& rOutput, EditSelection aSel, BOOL bStoreUnicodeStrings ) const
//STRIP001 {
//STRIP001  BinTextObject* pObj = (BinTextObject*)CreateBinTextObject( aSel, NULL );
//STRIP001  pObj->StoreUnicodeStrings( bStoreUnicodeStrings );
//STRIP001  pObj->Store( rOutput );
//STRIP001  delete pObj;
//STRIP001  return 0;
//STRIP001 }

#ifndef SVX_LIGHT
//STRIP001 sal_uInt32 ImpEditEngine::WriteXML( SvStream& rOutput, EditSelection aSel )
//STRIP001 {
//STRIP001     ESelection aESel = CreateESel( aSel );
//STRIP001
//STRIP001     SvxWriteXML( *GetEditEnginePtr(), rOutput, aESel );
//STRIP001
//STRIP001     return 0;
//STRIP001 }
#endif

//STRIP001 sal_uInt32 ImpEditEngine::WriteRTF( SvStream& rOutput, EditSelection aSel )
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  DBG_ASSERT( GetUpdateMode(), "WriteRTF bei UpdateMode = sal_False!" );
//STRIP001  CheckIdleFormatter();
//STRIP001  if ( !IsFormatted() )
//STRIP001      FormatDoc();
//STRIP001
//STRIP001  sal_uInt16 nStartNode, nEndNode;
//STRIP001  aSel.Adjust( aEditDoc );
//STRIP001
//STRIP001  nStartNode = aEditDoc.GetPos( aSel.Min().GetNode() );
//STRIP001  nEndNode = aEditDoc.GetPos( aSel.Max().GetNode() );
//STRIP001
//STRIP001  // RTF-Vorspann...
//STRIP001  rOutput << '{' ;
//STRIP001
//STRIP001  rOutput << sRTF_RTF;
//STRIP001
//STRIP001 #ifndef MAC
//STRIP001  rOutput << sRTF_ANSI;
//STRIP001  rtl_TextEncoding eDestEnc = RTL_TEXTENCODING_MS_1252;
//STRIP001 #else
//STRIP001  rOutput << sRTF_MAC;
//STRIP001  rtl_TextEncoding eDestEnc = RTL_TEXTENCODING_APPLE_ROMAN;
//STRIP001 #endif
//STRIP001
//STRIP001  // Fonttabelle erzeugen und rausschreiben...
//STRIP001  SvxFontTable aFontTable;
//STRIP001  // DefaultFont muss ganz vorne stehen, damit DEF-Font im RTF
//STRIP001  aFontTable.Insert( 0, new SvxFontItem( (const SvxFontItem&)aEditDoc.GetItemPool().GetDefaultItem( EE_CHAR_FONTINFO ) ) );
//STRIP001  aFontTable.Insert( 1, new SvxFontItem( (const SvxFontItem&)aEditDoc.GetItemPool().GetDefaultItem( EE_CHAR_FONTINFO_CJK ) ) );
//STRIP001  aFontTable.Insert( 2, new SvxFontItem( (const SvxFontItem&)aEditDoc.GetItemPool().GetDefaultItem( EE_CHAR_FONTINFO_CTL ) ) );
//STRIP001     for ( USHORT nScriptType = 0; nScriptType < 3; nScriptType++ )
//STRIP001     {
//STRIP001         USHORT nWhich = EE_CHAR_FONTINFO;
//STRIP001         if ( nScriptType == 1 )
//STRIP001             nWhich = EE_CHAR_FONTINFO_CJK;
//STRIP001         else if ( nScriptType == 2 )
//STRIP001             nWhich = EE_CHAR_FONTINFO_CTL;
//STRIP001
//STRIP001         sal_uInt16 i = 0;
//STRIP001      SvxFontItem* pFontItem = (SvxFontItem*)aEditDoc.GetItemPool().GetItem( nWhich, i );
//STRIP001      while ( pFontItem )
//STRIP001      {
//STRIP001             BOOL bAlreadyExist = FALSE;
//STRIP001             USHORT nTestMax = nScriptType ? aFontTable.Count() : 1;
//STRIP001             for ( USHORT nTest = 0; !bAlreadyExist && ( nTest < nTestMax ); nTest++ )
//STRIP001             {
//STRIP001                 bAlreadyExist = *aFontTable.Get( nTest ) == *pFontItem;
//STRIP001             }
//STRIP001
//STRIP001             if ( !bAlreadyExist )
//STRIP001              aFontTable.Insert( aFontTable.Count(), new SvxFontItem( *pFontItem ) );
//STRIP001
//STRIP001             pFontItem = (SvxFontItem*)aEditDoc.GetItemPool().GetItem( nWhich, ++i );
//STRIP001      }
//STRIP001     }
//STRIP001
//STRIP001  rOutput << endl << '{' << sRTF_FONTTBL;
//STRIP001  sal_uInt16 j;
//STRIP001  for ( j = 0; j < aFontTable.Count(); j++ )
//STRIP001  {
//STRIP001      SvxFontItem* pFontItem = aFontTable.Get( j );
//STRIP001      rOutput << '{';
//STRIP001      rOutput << sRTF_F;
//STRIP001      rOutput.WriteNumber( j );
//STRIP001      switch ( pFontItem->GetFamily()  )
//STRIP001      {
//STRIP001          case FAMILY_DONTKNOW:       rOutput << sRTF_FNIL;
//STRIP001                                      break;
//STRIP001          case FAMILY_DECORATIVE:     rOutput << sRTF_FDECOR;
//STRIP001                                      break;
//STRIP001          case FAMILY_MODERN:         rOutput << sRTF_FMODERN;
//STRIP001                                      break;
//STRIP001          case FAMILY_ROMAN:          rOutput << sRTF_FROMAN;
//STRIP001                                      break;
//STRIP001          case FAMILY_SCRIPT:         rOutput << sRTF_FSCRIPT;
//STRIP001                                      break;
//STRIP001          case FAMILY_SWISS:          rOutput << sRTF_FSWISS;
//STRIP001                                      break;
//STRIP001      }
//STRIP001      rOutput << sRTF_FPRQ;
//STRIP001      sal_uInt16 nVal = 0;
//STRIP001      switch( pFontItem->GetPitch() )
//STRIP001      {
//STRIP001          case PITCH_FIXED:       nVal = 1;       break;
//STRIP001          case PITCH_VARIABLE:    nVal = 2;       break;
//STRIP001      }
//STRIP001      rOutput.WriteNumber( nVal );
//STRIP001
//STRIP001      CharSet eChrSet = pFontItem->GetCharSet();
//STRIP001      DBG_ASSERT( eChrSet != 9, "SystemCharSet?!" );
//STRIP001      if( RTL_TEXTENCODING_DONTKNOW == eChrSet )
//STRIP001          eChrSet = gsl_getSystemTextEncoding();
//STRIP001      rOutput << sRTF_FCHARSET;
//STRIP001      rOutput.WriteNumber( rtl_getBestWindowsCharsetFromTextEncoding( eChrSet ) );
//STRIP001
//STRIP001      rOutput << ' ';
//STRIP001         RTFOutFuncs::Out_String( rOutput, pFontItem->GetFamilyName(), eDestEnc );
//STRIP001      rOutput << ";}";
//STRIP001  }
//STRIP001  rOutput << '}';
//STRIP001  rOutput << endl;
//STRIP001
//STRIP001  // ColorList rausschreiben...
//STRIP001  SvxColorList aColorList;
//STRIP001  sal_uInt16 i = 0;
//STRIP001  SvxColorItem* pColorItem = (SvxColorItem*)aEditDoc.GetItemPool().GetItem( EE_CHAR_COLOR, i );
//STRIP001  while ( pColorItem )
//STRIP001  {
//STRIP001      USHORT nPos = i;
//STRIP001      if ( pColorItem->GetValue() == COL_AUTO )
//STRIP001          nPos = 0;
//STRIP001      aColorList.Insert( new SvxColorItem( *pColorItem ), nPos );
//STRIP001      pColorItem = (SvxColorItem*)aEditDoc.GetItemPool().GetItem( EE_CHAR_COLOR, ++i );
//STRIP001  }
//STRIP001  aColorList.Insert( new SvxColorItem( (const SvxColorItem&)aEditDoc.GetItemPool().GetDefaultItem( EE_CHAR_COLOR) ), (sal_uInt32)i );
//STRIP001
//STRIP001  rOutput << '{' << sRTF_COLORTBL;
//STRIP001  for ( j = 0; j < aColorList.Count(); j++ )
//STRIP001  {
//STRIP001      pColorItem = aColorList.GetObject( j );
//STRIP001      if ( !j || ( pColorItem->GetValue() != COL_AUTO ) )
//STRIP001      {
//STRIP001          rOutput << sRTF_RED;
//STRIP001          rOutput.WriteNumber( pColorItem->GetValue().GetRed() );
//STRIP001          rOutput << sRTF_GREEN;
//STRIP001          rOutput.WriteNumber( pColorItem->GetValue().GetGreen() );
//STRIP001          rOutput << sRTF_BLUE;
//STRIP001          rOutput.WriteNumber( pColorItem->GetValue().GetBlue() );
//STRIP001      }
//STRIP001      rOutput << ';';
//STRIP001  }
//STRIP001  rOutput << '}';
//STRIP001  rOutput << endl;
//STRIP001
//STRIP001  // StyleSheets...
//STRIP001  if ( GetStyleSheetPool() )
//STRIP001  {
//STRIP001      sal_uInt16 nStyles = (sal_uInt16)GetStyleSheetPool()->GetStyles().Count();
//STRIP001      if ( nStyles )
//STRIP001      {
//STRIP001          rOutput << '{' << sRTF_STYLESHEET;
//STRIP001
//STRIP001          for ( sal_uInt16 nStyle = 0; nStyle < nStyles; nStyle++ )
//STRIP001          {
//STRIP001
//STRIP001              SfxStyleSheet* pStyle = (SfxStyleSheet*)GetStyleSheetPool()->GetStyles().GetObject( nStyle );
//STRIP001
//STRIP001              rOutput << endl << '{' << sRTF_S;
//STRIP001              sal_uInt16 nNumber = (sal_uInt16) (nStyle + 1);
//STRIP001              rOutput.WriteNumber( nNumber );
//STRIP001
//STRIP001              // Attribute, auch aus Parent!
//STRIP001              for ( sal_uInt16 nParAttr = EE_PARA_START; nParAttr <= EE_CHAR_END; nParAttr++ )
//STRIP001              {
//STRIP001                  if ( pStyle->GetItemSet().GetItemState( nParAttr ) == SFX_ITEM_ON )
//STRIP001                  {
//STRIP001                      const SfxPoolItem& rItem = pStyle->GetItemSet().Get( nParAttr );
//STRIP001                      WriteItemAsRTF( rItem, rOutput, 0, 0, aFontTable, aColorList );
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              // Parent...(nur wenn noetig)
//STRIP001              if ( pStyle->GetParent().Len() && ( pStyle->GetParent() != pStyle->GetName() ) )
//STRIP001              {
//STRIP001                  SfxStyleSheet* pParent = (SfxStyleSheet*)GetStyleSheetPool()->Find( pStyle->GetParent(), pStyle->GetFamily() );
//STRIP001                  DBG_ASSERT( pParent, "Parent nicht gefunden!" );
//STRIP001                  rOutput << sRTF_SBASEDON;
//STRIP001                  nNumber = (sal_uInt16) GetStyleSheetPool()->GetStyles().GetPos( pParent ) + 1;
//STRIP001                  rOutput.WriteNumber( nNumber );
//STRIP001              }
//STRIP001
//STRIP001              // Folgevorlage...(immer)
//STRIP001              SfxStyleSheet* pNext = pStyle;
//STRIP001              if ( pStyle->GetFollow().Len() && ( pStyle->GetFollow() != pStyle->GetName() ) )
//STRIP001                  pNext = (SfxStyleSheet*)GetStyleSheetPool()->Find( pStyle->GetFollow(), pStyle->GetFamily() );
//STRIP001
//STRIP001              DBG_ASSERT( pNext, "Naechsten nicht gefunden!" );
//STRIP001              rOutput << sRTF_SNEXT;
//STRIP001              nNumber = (sal_uInt16) GetStyleSheetPool()->GetStyles().GetPos( pNext ) + 1;
//STRIP001              rOutput.WriteNumber( nNumber );
//STRIP001
//STRIP001              // Namen der Vorlage...
//STRIP001              rOutput << " " << ByteString( pStyle->GetName(), eDestEnc ).GetBuffer();
//STRIP001              rOutput << ";}";
//STRIP001          }
//STRIP001          rOutput << '}';
//STRIP001          rOutput << endl;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Die Pool-Defaults vorweg schreiben...
//STRIP001  rOutput << '{' << sRTF_IGNORE << "\\EditEnginePoolDefaults";
//STRIP001  for ( sal_uInt16 nPoolDefItem = EE_PARA_START; nPoolDefItem <= EE_CHAR_END; nPoolDefItem++)
//STRIP001  {
//STRIP001      const SfxPoolItem& rItem = aEditDoc.GetItemPool().GetDefaultItem( nPoolDefItem );
//STRIP001      WriteItemAsRTF( rItem, rOutput, 0, 0, aFontTable, aColorList );
//STRIP001  }
//STRIP001  rOutput << '}' << endl;
//STRIP001
//STRIP001  // Def-Hoehe vorweg, da sonst 12Pt
//STRIP001  // Doch nicht, onst in jedem Absatz hart!
//STRIP001  // SfxItemSet aTmpSet( GetEmptyItemSet() );
//STRIP001  // const SvxFontHeightItem& rDefFontHeight = (const SvxFontHeightItem&)aTmpSet.Get( EE_CHAR_FONTHEIGHT );
//STRIP001  // WriteItemAsRTF( rDefFontHeight, rOutput, aFontTable, aColorList );
//STRIP001  // rOutput << '{' << sRTF_IGNORE << "\\EditEnginePoolDefaultHeight}" << endl;
//STRIP001
//STRIP001  // DefTab:
//STRIP001  MapMode aTwpMode( MAP_TWIP );
//STRIP001  sal_uInt16 nDefTabTwps = (sal_uInt16) GetRefDevice()->LogicToLogic(
//STRIP001                                      Point( aEditDoc.GetDefTab(), 0 ),
//STRIP001                                      &GetRefMapMode(), &aTwpMode ).X();
//STRIP001  rOutput << sRTF_DEFTAB;
//STRIP001  rOutput.WriteNumber( nDefTabTwps );
//STRIP001  rOutput << endl;
//STRIP001
//STRIP001  // ueber die Absaetze iterieren...
//STRIP001  rOutput << '{' << endl;
//STRIP001  for ( sal_uInt16 nNode = nStartNode; nNode <= nEndNode; nNode++  )
//STRIP001  {
//STRIP001      ContentNode* pNode = aEditDoc.SaveGetObject( nNode );
//STRIP001      DBG_ASSERT( pNode, "Node nicht gefunden: Search&Replace" );
//STRIP001
//STRIP001      // Die Absatzattribute vorweg...
//STRIP001      sal_Bool bAttr = sal_False;
//STRIP001
//STRIP001      // Vorlage ?
//STRIP001      if ( pNode->GetStyleSheet() )
//STRIP001      {
//STRIP001          // Nummer der Vorlage
//STRIP001          rOutput << sRTF_S;
//STRIP001          sal_uInt16 nNumber = (sal_uInt16) GetStyleSheetPool()->GetStyles().GetPos( pNode->GetStyleSheet() ) + 1;
//STRIP001          rOutput.WriteNumber( nNumber );
//STRIP001
//STRIP001          // Alle Attribute
//STRIP001          // Attribute, auch aus Parent!
//STRIP001          for ( sal_uInt16 nParAttr = EE_PARA_START; nParAttr <= EE_CHAR_END; nParAttr++ )
//STRIP001          {
//STRIP001              if ( pNode->GetStyleSheet()->GetItemSet().GetItemState( nParAttr ) == SFX_ITEM_ON )
//STRIP001              {
//STRIP001                  const SfxPoolItem& rItem = pNode->GetStyleSheet()->GetItemSet().Get( nParAttr );
//STRIP001                  WriteItemAsRTF( rItem, rOutput, nNode, 0, aFontTable, aColorList );
//STRIP001                  bAttr = sal_True;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      for ( sal_uInt16 nParAttr = EE_PARA_START; nParAttr <= EE_CHAR_END; nParAttr++ )
//STRIP001      {
//STRIP001 //           const SfxPoolItem& rItem = pNode->GetContentAttribs().GetItem( nParAttr );
//STRIP001          // Jetzt, wo StyleSheet-Verarbeitung, nur noch harte Absatzattribute!
//STRIP001          if ( pNode->GetContentAttribs().GetItems().GetItemState( nParAttr ) == SFX_ITEM_ON )
//STRIP001          {
//STRIP001              const SfxPoolItem& rItem = pNode->GetContentAttribs().GetItems().Get( nParAttr );
//STRIP001              WriteItemAsRTF( rItem, rOutput, nNode, 0, aFontTable, aColorList );
//STRIP001              bAttr = sal_True;
//STRIP001          }
//STRIP001      }
//STRIP001      if ( bAttr )
//STRIP001          rOutput << ' '; // Separator
//STRIP001
//STRIP001      ItemList aAttribItems;
//STRIP001      ParaPortion* pParaPortion = FindParaPortion( pNode );
//STRIP001      DBG_ASSERT( pParaPortion, "Portion nicht gefunden: WriteRTF" );
//STRIP001
//STRIP001      sal_uInt16 nIndex = 0;
//STRIP001      sal_uInt16 nStartPos = 0;
//STRIP001      sal_uInt16 nEndPos = pNode->Len();
//STRIP001      sal_uInt16 nStartPortion = 0;
//STRIP001      sal_uInt16 nEndPortion = (sal_uInt16)pParaPortion->GetTextPortions().Count() - 1;
//STRIP001      sal_Bool bFinishPortion = sal_False;
//STRIP001      sal_uInt16 nPortionStart;
//STRIP001
//STRIP001      if ( nNode == nStartNode )
//STRIP001      {
//STRIP001          nStartPos = aSel.Min().GetIndex();
//STRIP001          nStartPortion = pParaPortion->GetTextPortions().FindPortion( nStartPos, nPortionStart );
//STRIP001          if ( nStartPos != 0 )
//STRIP001          {
//STRIP001              aAttribItems.Clear();
//STRIP001                 lcl_FindValidAttribs( aAttribItems, pNode, nStartPos, GetScriptType( EditPaM( pNode, 0 ) ) );
//STRIP001              if ( aAttribItems.Count() )
//STRIP001              {
//STRIP001                  // Diese Attribute duerfen nicht fuer den gesamten
//STRIP001                  // Absatz gelten:
//STRIP001                  rOutput << '{';
//STRIP001                  WriteItemListAsRTF( aAttribItems, rOutput, nNode, nStartPos, aFontTable, aColorList );
//STRIP001                  bFinishPortion = sal_True;
//STRIP001              }
//STRIP001              aAttribItems.Clear();
//STRIP001          }
//STRIP001      }
//STRIP001      if ( nNode == nEndNode ) // kann auch == nStart sein!
//STRIP001      {
//STRIP001          nEndPos = aSel.Max().GetIndex();
//STRIP001          nEndPortion = pParaPortion->GetTextPortions().FindPortion( nEndPos, nPortionStart );
//STRIP001      }
//STRIP001
//STRIP001      EditCharAttrib* pNextFeature = pNode->GetCharAttribs().FindFeature( nIndex );
//STRIP001      // Bei 0 anfangen, damit der Index richtig ist...
//STRIP001
//STRIP001      for ( sal_uInt16 n = 0; n <= nEndPortion; n++ )
//STRIP001      {
//STRIP001          TextPortion* pTextPortion = pParaPortion->GetTextPortions().GetObject(n);
//STRIP001          if ( n < nStartPortion )
//STRIP001          {
//STRIP001              nIndex += pTextPortion->GetLen();
//STRIP001              continue;
//STRIP001          }
//STRIP001
//STRIP001          if ( pNextFeature && ( pNextFeature->GetStart() == nIndex ) && ( pNextFeature->GetItem()->Which() != EE_FEATURE_FIELD ) )
//STRIP001          {
//STRIP001              WriteItemAsRTF( *pNextFeature->GetItem(), rOutput, nNode, nIndex, aFontTable, aColorList );
//STRIP001              pNextFeature = pNode->GetCharAttribs().FindFeature( pNextFeature->GetStart() + 1 );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              aAttribItems.Clear();
//STRIP001                 USHORT nScriptType = GetScriptType( EditPaM( pNode, nIndex+1 ) );
//STRIP001                 if ( !n || IsScriptChange( EditPaM( pNode, nIndex ) ) )
//STRIP001                 {
//STRIP001                     SfxItemSet aAttribs = GetAttribs( nNode, nIndex+1, nIndex+1 );
//STRIP001                     aAttribItems.Insert( &aAttribs.Get( GetScriptItemId( EE_CHAR_FONTINFO, nScriptType ) ), LIST_APPEND );
//STRIP001                     aAttribItems.Insert( &aAttribs.Get( GetScriptItemId( EE_CHAR_FONTHEIGHT, nScriptType ) ), LIST_APPEND );
//STRIP001                     aAttribItems.Insert( &aAttribs.Get( GetScriptItemId( EE_CHAR_WEIGHT, nScriptType ) ), LIST_APPEND );
//STRIP001                     aAttribItems.Insert( &aAttribs.Get( GetScriptItemId( EE_CHAR_ITALIC, nScriptType ) ), LIST_APPEND );
//STRIP001                     aAttribItems.Insert( &aAttribs.Get( GetScriptItemId( EE_CHAR_LANGUAGE, nScriptType ) ), LIST_APPEND );
//STRIP001                 }
//STRIP001                 // #96298# Insert hard attribs AFTER CJK attribs...
//STRIP001              lcl_FindValidAttribs( aAttribItems, pNode, nIndex, nScriptType );
//STRIP001
//STRIP001              rOutput << '{';
//STRIP001              if ( WriteItemListAsRTF( aAttribItems, rOutput, nNode, nIndex, aFontTable, aColorList ) )
//STRIP001                  rOutput << ' ';
//STRIP001
//STRIP001              USHORT nS = nIndex;
//STRIP001              USHORT nE = nIndex + pTextPortion->GetLen();
//STRIP001              if ( n == nStartPortion )
//STRIP001                  nS = nStartPos;
//STRIP001              if ( n == nEndPortion )
//STRIP001                  nE = nEndPos;
//STRIP001
//STRIP001              XubString aRTFStr = aEditDoc.GetParaAsString( pNode, nS, nE);
//STRIP001              RTFOutFuncs::Out_String( rOutput, aRTFStr, eDestEnc );
//STRIP001              rOutput << '}';
//STRIP001          }
//STRIP001          if ( bFinishPortion )
//STRIP001          {
//STRIP001              rOutput << '}';
//STRIP001              bFinishPortion = sal_False;
//STRIP001          }
//STRIP001
//STRIP001          nIndex += pTextPortion->GetLen();
//STRIP001      }
//STRIP001
//STRIP001      rOutput << sRTF_PAR << sRTF_PARD << sRTF_PLAIN;;
//STRIP001      rOutput << endl;
//STRIP001  }
//STRIP001  // RTF-Nachspann...
//STRIP001  rOutput << "}}";    // 1xKlammerung Absaetze, 1x Klammerung RTF-Dokument
//STRIP001  rOutput.Flush();
//STRIP001
//STRIP001 #if defined (EDITDEBUG) && !defined(MAC) && !defined( UNX )
//STRIP001     {
//STRIP001         SvFileStream aStream( String( RTL_CONSTASCII_USTRINGPARAM ( "d:\\rtf_out.rtf" ) ), STREAM_WRITE|STREAM_TRUNC );
//STRIP001         ULONG nP = rOutput.Tell();
//STRIP001         rOutput.Seek( 0 );
//STRIP001         aStream << rOutput;
//STRIP001         rOutput.Seek( nP );
//STRIP001     }
//STRIP001 #endif
//STRIP001
//STRIP001  return rOutput.GetError();
//STRIP001 #else
//STRIP001  return 0;
//STRIP001 #endif
//STRIP001 }


//STRIP001 void ImpEditEngine::WriteItemAsRTF( const SfxPoolItem& rItem, SvStream& rOutput, sal_uInt16 nPara, sal_uInt16 nPos,
//STRIP001                          SvxFontTable& rFontTable, SvxColorList& rColorList )
//STRIP001 {
//STRIP001  sal_uInt16 nWhich = rItem.Which();
//STRIP001  switch ( nWhich )
//STRIP001  {
//STRIP001         case EE_PARA_WRITINGDIR:
//STRIP001         {
//STRIP001             const SvxFrameDirectionItem& rWritingMode = (const SvxFrameDirectionItem&)rItem;
//STRIP001             if ( rWritingMode.GetValue() == FRMDIR_HORI_RIGHT_TOP )
//STRIP001                 rOutput << "\\rtlpar";
//STRIP001             else
//STRIP001                 rOutput << "\\ltrpar";
//STRIP001         }
//STRIP001         break;
//STRIP001      case EE_PARA_OUTLLEVEL:
//STRIP001      {
//STRIP001          rOutput << "\\level";
//STRIP001          sal_uInt16 nLevel = ((const SfxUInt16Item&)rItem).GetValue();
//STRIP001          rOutput.WriteNumber( nLevel );
//STRIP001      }
//STRIP001      break;
//STRIP001      case EE_PARA_OUTLLRSPACE:
//STRIP001      case EE_PARA_LRSPACE:
//STRIP001      {
//STRIP001          rOutput << sRTF_FI;
//STRIP001          short nTxtFirst = ((const SvxLRSpaceItem&)rItem).GetTxtFirstLineOfst();
//STRIP001          nTxtFirst = (short)LogicToTwips( nTxtFirst );
//STRIP001          rOutput.WriteNumber( nTxtFirst );
//STRIP001          rOutput << sRTF_LI;
//STRIP001          sal_uInt16 nTxtLeft = (USHORT)((const SvxLRSpaceItem&)rItem).GetTxtLeft();
//STRIP001          nTxtLeft = (sal_uInt16)LogicToTwips( nTxtLeft );
//STRIP001          rOutput.WriteNumber( nTxtLeft );
//STRIP001          rOutput << sRTF_RI;
//STRIP001          sal_uInt32 nTxtRight = ((const SvxLRSpaceItem&)rItem).GetRight();
//STRIP001          nTxtRight = LogicToTwips( nTxtRight);
//STRIP001          rOutput.WriteNumber( nTxtRight );
//STRIP001      }
//STRIP001      break;
//STRIP001      case EE_PARA_ULSPACE:
//STRIP001      {
//STRIP001          rOutput << sRTF_SB;
//STRIP001          sal_uInt16 nUpper = ((const SvxULSpaceItem&)rItem).GetUpper();
//STRIP001          nUpper = (sal_uInt16)LogicToTwips( nUpper );
//STRIP001          rOutput.WriteNumber( nUpper );
//STRIP001          rOutput << sRTF_SA;
//STRIP001          sal_uInt16 nLower = ((const SvxULSpaceItem&)rItem).GetLower();
//STRIP001          nLower = (sal_uInt16)LogicToTwips( nLower );
//STRIP001          rOutput.WriteNumber( nLower );
//STRIP001      }
//STRIP001      break;
//STRIP001      case EE_PARA_SBL:
//STRIP001      {
//STRIP001          rOutput << sRTF_SL;
//STRIP001          long nVal = ((const SvxLineSpacingItem&)rItem).GetLineHeight();
//STRIP001             char cMult = '0';
//STRIP001          if ( ((const SvxLineSpacingItem&)rItem).GetInterLineSpaceRule() == SVX_INTER_LINE_SPACE_PROP )
//STRIP001          {
//STRIP001              // Woher kriege ich jetzt den Wert?
//STRIP001              // Der SwRTF-Parser geht von einem 240er Font aus!
//STRIP001              nVal = ((const SvxLineSpacingItem&)rItem).GetPropLineSpace();
//STRIP001              nVal *= 240;
//STRIP001              nVal /= 100;
//STRIP001                 cMult = '1';
//STRIP001          }
//STRIP001          rOutput.WriteNumber( nVal );
//STRIP001             rOutput << sRTF_SLMULT << cMult;
//STRIP001      }
//STRIP001      break;
//STRIP001      case EE_PARA_JUST:
//STRIP001      {
//STRIP001          SvxAdjust eJustification = ((const SvxAdjustItem&)rItem).GetAdjust();
//STRIP001          switch ( eJustification )
//STRIP001          {
//STRIP001              case SVX_ADJUST_CENTER: rOutput << sRTF_QC;
//STRIP001                                      break;
//STRIP001              case SVX_ADJUST_RIGHT:  rOutput << sRTF_QR;
//STRIP001                                      break;
//STRIP001              default:                rOutput << sRTF_QL;
//STRIP001                                      break;
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001      case EE_PARA_TABS:
//STRIP001      {
//STRIP001          const SvxTabStopItem& rTabs = (const SvxTabStopItem&) rItem;
//STRIP001          for ( sal_uInt16 i = 0; i < rTabs.Count(); i++ )
//STRIP001          {
//STRIP001              const SvxTabStop& rTab = rTabs[i];
//STRIP001              rOutput << sRTF_TX;
//STRIP001              rOutput.WriteNumber( LogicToTwips( rTab.GetTabPos() ) );
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001      case EE_CHAR_COLOR:
//STRIP001      {
//STRIP001          sal_uInt32 n = rColorList.GetId( (const SvxColorItem&)rItem );
//STRIP001          rOutput << sRTF_CF;
//STRIP001          rOutput.WriteNumber( n );
//STRIP001      }
//STRIP001      break;
//STRIP001      case EE_CHAR_FONTINFO:
//STRIP001      case EE_CHAR_FONTINFO_CJK:
//STRIP001      case EE_CHAR_FONTINFO_CTL:
//STRIP001      {
//STRIP001          sal_uInt32 n = rFontTable.GetId( (const SvxFontItem&)rItem );
//STRIP001          rOutput << sRTF_F;
//STRIP001          rOutput.WriteNumber( n );
//STRIP001      }
//STRIP001      break;
//STRIP001      case EE_CHAR_FONTHEIGHT:
//STRIP001      case EE_CHAR_FONTHEIGHT_CJK:
//STRIP001      case EE_CHAR_FONTHEIGHT_CTL:
//STRIP001      {
//STRIP001          rOutput << sRTF_FS;
//STRIP001          long nHeight = ((const SvxFontHeightItem&)rItem).GetHeight();
//STRIP001          nHeight = LogicToTwips( nHeight );
//STRIP001          // Twips => HalfPoints
//STRIP001          nHeight /= 10;
//STRIP001          rOutput.WriteNumber( nHeight );
//STRIP001      }
//STRIP001      break;
//STRIP001      case EE_CHAR_WEIGHT:
//STRIP001      case EE_CHAR_WEIGHT_CJK:
//STRIP001      case EE_CHAR_WEIGHT_CTL:
//STRIP001      {
//STRIP001          FontWeight e = ((const SvxWeightItem&)rItem).GetWeight();
//STRIP001          switch ( e )
//STRIP001          {
//STRIP001              case WEIGHT_BOLD:   rOutput << sRTF_B;              break;
//STRIP001              default:            rOutput << sRTF_B << '0';       break;
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001      case EE_CHAR_UNDERLINE:
//STRIP001      {
//STRIP001          // muesste bei WordLineMode ggf. ulw werden,
//STRIP001          // aber die Information fehlt hier
//STRIP001          FontUnderline e = ((const SvxUnderlineItem&)rItem).GetUnderline();
//STRIP001          switch ( e )
//STRIP001          {
//STRIP001              case UNDERLINE_NONE:    rOutput << sRTF_ULNONE;     break;
//STRIP001              case UNDERLINE_SINGLE:  rOutput << sRTF_UL;         break;
//STRIP001              case UNDERLINE_DOUBLE:  rOutput << sRTF_ULDB;       break;
//STRIP001              case UNDERLINE_DOTTED:  rOutput << sRTF_ULD;        break;
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001      case EE_CHAR_STRIKEOUT:
//STRIP001      {
//STRIP001          FontStrikeout e = ((const SvxCrossedOutItem&)rItem).GetStrikeout();
//STRIP001          switch ( e )
//STRIP001          {
//STRIP001              case STRIKEOUT_SINGLE:
//STRIP001              case STRIKEOUT_DOUBLE:  rOutput << sRTF_STRIKE;         break;
//STRIP001              case STRIKEOUT_NONE:    rOutput << sRTF_STRIKE << '0';  break;
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001      case EE_CHAR_ITALIC:
//STRIP001      case EE_CHAR_ITALIC_CJK:
//STRIP001      case EE_CHAR_ITALIC_CTL:
//STRIP001      {
//STRIP001          FontItalic e = ((const SvxPostureItem&)rItem).GetPosture();
//STRIP001          switch ( e )
//STRIP001          {
//STRIP001              case ITALIC_OBLIQUE:
//STRIP001              case ITALIC_NORMAL: rOutput << sRTF_I;      break;
//STRIP001              case ITALIC_NONE:   rOutput << sRTF_I << '0';   break;
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001      case EE_CHAR_OUTLINE:
//STRIP001      {
//STRIP001          rOutput << sRTF_OUTL;
//STRIP001          if ( ((const SvxContourItem&)rItem).GetValue() == 0 )
//STRIP001              rOutput << '0';
//STRIP001      }
//STRIP001      break;
//STRIP001      case EE_CHAR_RELIEF:
//STRIP001      {
//STRIP001          USHORT nRelief = ((const SvxCharReliefItem&)rItem).GetValue();
//STRIP001          if ( nRelief == RELIEF_EMBOSSED )
//STRIP001              rOutput << sRTF_EMBO;
//STRIP001          if ( nRelief == RELIEF_ENGRAVED )
//STRIP001              rOutput << sRTF_IMPR;
//STRIP001      }
//STRIP001      break;
//STRIP001      case EE_CHAR_EMPHASISMARK:
//STRIP001      {
//STRIP001          USHORT nMark = ((const SvxEmphasisMarkItem&)rItem).GetValue();
//STRIP001          if ( nMark == EMPHASISMARK_NONE )
//STRIP001              rOutput << sRTF_ACCNONE;
//STRIP001          else if ( nMark == EMPHASISMARK_SIDE_DOTS )
//STRIP001              rOutput << sRTF_ACCCOMMA;
//STRIP001          else
//STRIP001              rOutput << sRTF_ACCDOT;
//STRIP001      }
//STRIP001      break;
//STRIP001      case EE_CHAR_SHADOW:
//STRIP001      {
//STRIP001          rOutput << sRTF_SHAD;
//STRIP001          if ( ((const SvxShadowedItem&)rItem).GetValue() == 0 )
//STRIP001              rOutput << '0';
//STRIP001      }
//STRIP001      break;
//STRIP001      case EE_FEATURE_TAB:
//STRIP001      {
//STRIP001          rOutput << sRTF_TAB;
//STRIP001      }
//STRIP001      break;
//STRIP001      case EE_FEATURE_LINEBR:
//STRIP001      {
//STRIP001          rOutput << sRTF_SL;
//STRIP001      }
//STRIP001      break;
//STRIP001      case EE_CHAR_KERNING:
//STRIP001      {
//STRIP001          rOutput << sRTF_EXPNDTW;
//STRIP001          rOutput.WriteNumber( LogicToTwips(
//STRIP001              ((const SvxKerningItem&)rItem).GetValue() ) );
//STRIP001      }
//STRIP001      break;
//STRIP001      case EE_CHAR_PAIRKERNING:
//STRIP001      {
//STRIP001          rOutput << sRTF_KERNING;
//STRIP001          rOutput.WriteNumber( ((const SvxAutoKernItem&)rItem).GetValue() ? 1 : 0 );
//STRIP001      }
//STRIP001      break;
//STRIP001      case EE_CHAR_ESCAPEMENT:
//STRIP001      {
//STRIP001          SvxFont aFont;
//STRIP001          ContentNode* pNode = aEditDoc.GetObject( nPara );
//STRIP001          SeekCursor( pNode, nPos, aFont );
//STRIP001          MapMode aPntMode( MAP_POINT );
//STRIP001          long nFontHeight = GetRefDevice()->LogicToLogic(
//STRIP001                  aFont.GetSize(), &GetRefMapMode(), &aPntMode ).Height();
//STRIP001          nFontHeight *=2;    // HalfPoints
//STRIP001          sal_uInt16 nProp = ((const SvxEscapementItem&)rItem).GetProp();
//STRIP001          sal_uInt16 nProp100 = nProp*100;    // Fuer SWG-Token Prop in 100tel Prozent.
//STRIP001          short nEsc = ((const SvxEscapementItem&)rItem).GetEsc();
//STRIP001          if ( nEsc == DFLT_ESC_AUTO_SUPER )
//STRIP001          {
//STRIP001              nEsc = 100 - nProp;
//STRIP001              nProp100++; // Eine 1 hinten bedeutet 'automatisch'.
//STRIP001          }
//STRIP001          else if ( nEsc == DFLT_ESC_AUTO_SUB )
//STRIP001          {
//STRIP001              nEsc = -( 100 - nProp );
//STRIP001              nProp100++;
//STRIP001          }
//STRIP001          // SWG:
//STRIP001          if ( nEsc )
//STRIP001              rOutput << "{\\*\\updnprop" << ByteString::CreateFromInt32( nProp100 ).GetBuffer() << '}';
//STRIP001          long nUpDown = nFontHeight * Abs( nEsc ) / 100;
//STRIP001          ByteString aUpDown = ByteString::CreateFromInt32( nUpDown );
//STRIP001          if ( nEsc < 0 )
//STRIP001              rOutput << sRTF_DN << aUpDown.GetBuffer();
//STRIP001          else if ( nEsc > 0 )
//STRIP001              rOutput << sRTF_UP << aUpDown.GetBuffer();
//STRIP001      }
//STRIP001      break;
//STRIP001  }
//STRIP001 }

//STRIP001 sal_uInt32 ImpEditEngine::WriteHTML( SvStream& rOutput, EditSelection aSel )
//STRIP001 {
//STRIP001  return 0;
//STRIP001 }


/*N*/ EditTextObject*   ImpEditEngine::CreateTextObject()
/*N*/ {
/*N*/   EditSelection aCompleteSelection;
/*N*/   aCompleteSelection.Min() = aEditDoc.GetStartPaM();
/*N*/   aCompleteSelection.Max() = aEditDoc.GetEndPaM();
/*N*/
/*N*/   return CreateTextObject( aCompleteSelection );
/*N*/ }

/*N*/ EditTextObject*   ImpEditEngine::CreateTextObject( EditSelection aSel )
/*N*/ {
/*N*/   return CreateBinTextObject( aSel, GetEditTextObjectPool(), aStatus.AllowBigObjects(), nBigTextObjectStart );
/*N*/ }

/*N*/ EditTextObject*   ImpEditEngine::CreateBinTextObject( EditSelection aSel, SfxItemPool* pPool, sal_Bool bAllowBigObjects, sal_uInt16 nBigObjectStart ) const
/*N*/ {
/*N*/   BinTextObject* pTxtObj = new BinTextObject( pPool );
/*N*/   pTxtObj->SetVertical( IsVertical() );
/*N*/   MapUnit eMapUnit = (MapUnit)aEditDoc.GetItemPool().GetMetric( DEF_METRIC );
/*N*/   pTxtObj->SetMetric( (sal_uInt16) eMapUnit );
/*N*/   if ( pTxtObj->IsOwnerOfPool() )
/*N*/       pTxtObj->GetPool()->SetDefaultMetric( (SfxMapUnit) eMapUnit );
/*N*/
/*N*/   sal_uInt16 nStartNode, nEndNode;
/*N*/   sal_uInt32 nTextPortions = 0;
/*N*/
/*N*/   aSel.Adjust( aEditDoc );
/*N*/   nStartNode = aEditDoc.GetPos( aSel.Min().GetNode() );
/*N*/   nEndNode = aEditDoc.GetPos( aSel.Max().GetNode() );
/*N*/
/*N*/   sal_Bool bOnlyFullParagraphs = ( aSel.Min().GetIndex() ||
/*N*/       ( aSel.Max().GetIndex() < aSel.Max().GetNode()->Len() ) ) ?
/*N*/           sal_False : sal_True;
/*N*/
/*N*/   // Vorlagen werden nicht gespeichert!
/*N*/   // ( Nur Name und Familie, Vorlage selbst muss in App stehen! )
/*N*/
/*N*/   pTxtObj->SetScriptType( GetScriptType( aSel ) );
/*N*/
/*N*/   // ueber die Absaetze iterieren...
/*N*/   sal_uInt16 nNode;
/*N*/   for ( nNode = nStartNode; nNode <= nEndNode; nNode++  )
/*N*/   {
/*N*/       ContentNode* pNode = aEditDoc.SaveGetObject( nNode );
/*N*/       DBG_ASSERT( pNode, "Node nicht gefunden: Search&Replace" );
/*N*/
/*N*/       if ( bOnlyFullParagraphs )
/*N*/       {
/*N*/           ParaPortion* pParaPortion = GetParaPortions()[nNode];
/*N*/           nTextPortions += pParaPortion->GetTextPortions().Count();
/*N*/       }
/*N*/
/*N*/       sal_uInt16 nStartPos = 0;
/*N*/       sal_uInt16 nEndPos = pNode->Len();
/*N*/
/*N*/       sal_Bool bEmptyPara = nEndPos ? sal_False : sal_True;
/*N*/
/*N*/       if ( ( nNode == nStartNode ) && !bOnlyFullParagraphs )
/*?*/           nStartPos = aSel.Min().GetIndex();
/*N*/       if ( ( nNode == nEndNode ) && !bOnlyFullParagraphs )
/*?*/           nEndPos = aSel.Max().GetIndex();
/*N*/
/*N*/
/*N*/       ContentInfo* pC = pTxtObj->CreateAndInsertContent();
/*N*/
/*N*/       // Die Absatzattribute...
/*N*/       pC->GetParaAttribs().Set( pNode->GetContentAttribs().GetItems() );
/*N*/
/*N*/       // Seit der 5.1 werden im Outliner die LRSpaceItems anders interpretiert.
/*N*/       // Damit sie in einer 5.0 und aelter richtig sind, muss das Flag
/*N*/       // richtig gesetzt sein...
/*N*/       sal_Bool bOutliner = aStatus.IsAnyOutliner();
/*N*/       for ( sal_uInt16 n = 0; n <=1; n++ )
/*N*/       {
/*N*/           sal_uInt16 nItemId = n ? EE_PARA_LRSPACE : EE_PARA_OUTLLRSPACE;
/*N*/           if ( pC->GetParaAttribs().GetItemState( nItemId ) == SFX_ITEM_ON )
/*N*/           {
/*N*/               const SvxLRSpaceItem& rItem = (const SvxLRSpaceItem&) pC->GetParaAttribs().Get( nItemId );
/*N*/               if ( rItem.IsBulletFI() != bOutliner )
/*N*/               {
/*N*/                   SvxLRSpaceItem aNewItem( rItem );
/*N*/                   aNewItem.SetBulletFI( bOutliner );
/*N*/                   pC->GetParaAttribs().Put( aNewItem );
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/
/*N*/
/*N*/       // Das StyleSheet...
/*N*/       if ( pNode->GetStyleSheet() )
/*N*/       {
/*N*/           pC->GetStyle() = pNode->GetStyleSheet()->GetName();
/*N*/           pC->GetFamily() = pNode->GetStyleSheet()->GetFamily();
/*N*/       }
/*N*/
/*N*/       // Der Text...
/*N*/       pC->GetText() = pNode->Copy( nStartPos, nEndPos-nStartPos );
/*N*/
/*N*/       // und die Attribute...
/*N*/       sal_uInt16 nAttr = 0;
/*N*/       EditCharAttrib* pAttr = GetAttrib( pNode->GetCharAttribs().GetAttribs(), nAttr );
/*N*/       while ( pAttr )
/*N*/       {
/*N*/           // In einem leeren Absatz die Attribute behalten!
/*N*/           if ( bEmptyPara ||
/*N*/                ( ( pAttr->GetEnd() > nStartPos ) && ( pAttr->GetStart() < nEndPos ) ) )
/*N*/           {
/*N*/               XEditAttribute* pX = pTxtObj->CreateAttrib( *pAttr->GetItem(), pAttr->GetStart(), pAttr->GetEnd() );
/*N*/               // Evtl. korrigieren...
/*N*/               if ( ( nNode == nStartNode ) && ( nStartPos != 0 ) )
/*N*/               {
/*?*/                   pX->GetStart() = ( pX->GetStart() > nStartPos ) ? pX->GetStart()-nStartPos : 0;
/*?*/                   pX->GetEnd() -= nStartPos;
/*N*/
/*N*/               }
/*N*/               if ( nNode == nEndNode )
/*N*/               {
/*N*/                   if ( pX->GetEnd() > (nEndPos-nStartPos) )
/*?*/                       pX->GetEnd() = nEndPos-nStartPos;
/*N*/               }
/*N*/               DBG_ASSERT( pX->GetEnd() <= (nEndPos-nStartPos), "CreateBinTextObject: Attribut zu lang!" );
/*N*/               if ( !pX->GetLen() && !bEmptyPara )
/*?*/                   pTxtObj->DestroyAttrib( pX );
/*N*/               else
/*N*/                   pC->GetAttribs().Insert( pX, pC->GetAttribs().Count() );
/*N*/           }
/*N*/           nAttr++;
/*N*/           pAttr = GetAttrib( pNode->GetCharAttribs().GetAttribs(), nAttr );
/*N*/       }
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/       // ggf. Online-Spelling
/*N*/       if ( bAllowBigObjects && bOnlyFullParagraphs && pNode->GetWrongList() )
/*?*/       {DBG_ASSERT(0, "STRIP");} //STRIP001    pC->SetWrongList( pNode->GetWrongList()->Clone() );
/*N*/ #endif // !SVX_LIGHT
/*N*/
/*N*/   }
/*N*/
/*N*/   // Bei grossen Textobjekten die PortionInfos merken:
/*N*/   // Schwelle rauf setzen, wenn Olli die Absaetze nicht mehr zerhackt!
/*N*/   if ( bAllowBigObjects && bOnlyFullParagraphs && IsFormatted() && GetUpdateMode() && ( nTextPortions >= nBigObjectStart ) )
/*N*/   {
/*?*/       XParaPortionList* pXList = new XParaPortionList( GetRefDevice(), aPaperSize.Width() );
/*?*/       pTxtObj->SetPortionInfo( pXList );
/*?*/       for ( nNode = nStartNode; nNode <= nEndNode; nNode++  )
/*?*/       {
/*?*/           ParaPortion* pParaPortion = GetParaPortions()[nNode];
/*?*/           XParaPortion* pX = new XParaPortion;
/*?*/           pXList->Insert( pX, pXList->Count() );
/*?*/
/*?*/           pX->nHeight = pParaPortion->GetHeight();
/*?*/           pX->nFirstLineOffset = pParaPortion->GetFirstLineOffset();
/*?*/
/*?*/           // Die TextPortions
/*?*/           sal_uInt16 nCount = pParaPortion->GetTextPortions().Count();
/*?*/           sal_uInt16 n;
/*?*/           for ( n = 0; n < nCount; n++ )
/*?*/           {
/*?*/               TextPortion* pTextPortion = pParaPortion->GetTextPortions()[n];
/*?*/               TextPortion* pNew = new TextPortion( *pTextPortion );
/*?*/               pX->aTextPortions.Insert( pNew, pX->aTextPortions.Count() );
/*?*/           }
/*?*/
/*?*/           // Die Zeilen
/*?*/           nCount = pParaPortion->GetLines().Count();
/*?*/           for ( n = 0; n < nCount; n++ )
/*?*/           {
/*?*/               DBG_ASSERT(0, "STRIP"); //STRIP001 EditLine* pLine = pParaPortion->GetLines()[n];
//STRIP001 /*?*/                EditLine* pNew = pLine->Clone();
//STRIP001 /*?*/                pX->aLines.Insert( pNew, pX->aLines.Count() );
/*?*/           }
/*?*/ #ifdef DBG_UTIL
/*?*/           USHORT nTest, nTPLen = 0, nTxtLen = 0;
/*?*/           for ( nTest = pParaPortion->GetTextPortions().Count(); nTest; )
/*?*/               nTPLen += pParaPortion->GetTextPortions().GetObject( --nTest )->GetLen();
/*?*/           for ( nTest = pParaPortion->GetLines().Count(); nTest; )
/*?*/               nTxtLen += pParaPortion->GetLines().GetObject( --nTest )->GetLen();
/*?*/           DBG_ASSERT( ( nTPLen == pParaPortion->GetNode()->Len() ) && ( nTxtLen == pParaPortion->GetNode()->Len() ), "CreateBinTextObject: ParaPortion not completely formatted!" );
/*?*/ #endif
/*?*/       }
/*N*/   }
/*N*/   return pTxtObj;
/*N*/ }

/*N*/ void ImpEditEngine::SetText( const EditTextObject& rTextObject )
/*N*/ {
/*N*/   // Da Setzen eines TextObject ist nicht Undo-faehig!
/*N*/   ResetUndoManager();
/*N*/   sal_Bool bUpdate = GetUpdateMode();
/*N*/   sal_Bool bUndo = IsUndoEnabled();
/*N*/
/*N*/   SetText( XubString() );
/*N*/   EditPaM aPaM = aEditDoc.GetStartPaM();
/*N*/
/*N*/   SetUpdateMode( sal_False );
/*N*/   EnableUndo( sal_False );
/*N*/
/*N*/   InsertText( rTextObject, EditSelection( aPaM, aPaM ) );
/*N*/   SetVertical( rTextObject.IsVertical() );
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/   DBG_ASSERT( !HasUndoManager() || !GetUndoManager().GetUndoActionCount(), "Woher kommt das Undo in SetText ?!" );
/*N*/ #endif
/*N*/   SetUpdateMode( bUpdate );
/*N*/   EnableUndo( bUndo );
/*N*/ }

/*N*/ EditSelection ImpEditEngine::InsertText( const EditTextObject& rTextObject, EditSelection aSel )
/*N*/ {
/*N*/     EnterBlockNotifications();
/*N*/   aSel.Adjust( aEditDoc );
/*N*/   if ( aSel.HasRange() )
/*?*/       aSel = ImpDeleteSelection( aSel );
/*N*/   EditSelection aNewSel = InsertBinTextObject( (BinTextObject&)rTextObject, aSel.Max() );
/*N*/     LeaveBlockNotifications();
/*N*/     return aNewSel;
/*N*/
/*N*/   // MT 05/00: InsertBinTextObject direkt hier machen...
/*N*/ }

/*N*/ EditSelection ImpEditEngine::InsertBinTextObject( BinTextObject& rTextObject, EditPaM aPaM )
/*N*/ {
/*N*/   // Optimieren:
/*N*/   // Kein GetPos undFindParaportion, sondern Index berechnen!
/*N*/   EditSelection aSel( aPaM, aPaM );
/*N*/   DBG_ASSERT( !aSel.DbgIsBuggy( aEditDoc ), "InsertBibTextObject: Selektion kaput!(1)" );
/*N*/
/*N*/   sal_Bool bUsePortionInfo = sal_False;
/*N*/   sal_Bool bFields = sal_False;
/*N*/   XParaPortionList* pPortionInfo = rTextObject.GetPortionInfo();
/*N*/
/*N*/   if ( pPortionInfo && ( (long)pPortionInfo->GetPaperWidth() == aPaperSize.Width() )
/*N*/           && ( pPortionInfo->GetRefMapMode() == GetRefDevice()->GetMapMode() ) )
/*N*/   {
/*?*/       if ( ( pPortionInfo->GetRefDevPtr() == (sal_uInt32)GetRefDevice() ) ||
/*?*/            ( ( pPortionInfo->GetRefDevType() == OUTDEV_VIRDEV ) &&
/*?*/              ( GetRefDevice()->GetOutDevType() == OUTDEV_VIRDEV ) ) )
/*?*/       bUsePortionInfo = sal_True;
/*N*/   }
/*N*/
/*N*/   sal_Bool bConvertItems = sal_False;
/*N*/   MapUnit eSourceUnit, eDestUnit;
/*N*/   if ( rTextObject.HasMetric() )
/*N*/   {
/*N*/       eSourceUnit = (MapUnit)rTextObject.GetMetric();
/*N*/       eDestUnit = (MapUnit)aEditDoc.GetItemPool().GetMetric( DEF_METRIC );
/*N*/       if ( eSourceUnit != eDestUnit )
/*N*/           bConvertItems = sal_True;
/*N*/   }
/*N*/
/*N*/   sal_uInt16 nContents = rTextObject.GetContents().Count();
/*N*/   sal_uInt16 nPara = aEditDoc.GetPos( aPaM.GetNode() );
/*N*/
/*N*/   for ( sal_uInt16 n = 0; n < nContents; n++, nPara++ )
/*N*/   {
/*N*/       ContentInfo* pC = rTextObject.GetContents().GetObject( n );
/*N*/       sal_Bool bNewContent = aPaM.GetNode()->Len() ? sal_False: sal_True;
/*N*/       sal_uInt16 nStartPos = aPaM.GetIndex();
/*N*/
/*N*/       aPaM = ImpFastInsertText( aPaM, pC->GetText() );
/*N*/
/*N*/       ParaPortion* pPortion = FindParaPortion( aPaM.GetNode() );
/*N*/       DBG_ASSERT( pPortion, "Blinde Portion in FastInsertText" );
/*N*/       pPortion->MarkInvalid( nStartPos, pC->GetText().Len() );
/*N*/
/*N*/       // Zeicheattribute...
/*N*/       sal_Bool bAllreadyHasAttribs = aPaM.GetNode()->GetCharAttribs().Count() ? sal_True : sal_False;
/*N*/       sal_uInt16 nNewAttribs = pC->GetAttribs().Count();
/*N*/       if ( nNewAttribs )
/*N*/       {
/*N*/             BOOL bUpdateFields = FALSE;
/*N*/           for ( sal_uInt16 nAttr = 0; nAttr < nNewAttribs; nAttr++ )
/*N*/           {
/*N*/               XEditAttribute* pX = pC->GetAttribs().GetObject( nAttr );
/*N*/               // Kann passieren wenn Absaetze >16K entstehen, dann wird einfach umgebrochen.
/*N*/               if ( pX->GetEnd() <= aPaM.GetNode()->Len() )
/*N*/               {
/*N*/                   if ( !bAllreadyHasAttribs || pX->IsFeature() )
/*N*/                   {
/*N*/                       // Normale Attribute gehen dann schneller...
/*N*/                       // Features duerfen nicht ueber EditDoc::InsertAttrib
/*N*/                       // eingefuegt werden, sie sind bei FastInsertText schon im TextFluss
/*N*/                       DBG_ASSERT( pX->GetEnd() <= aPaM.GetNode()->Len(), "InsertBinTextObject: Attribut zu gross!" );
/*N*/                       EditCharAttrib* pAttr;
/*N*/                       if ( !bConvertItems )
/*N*/                           pAttr = MakeCharAttrib( aEditDoc.GetItemPool(), *(pX->GetItem()), pX->GetStart()+nStartPos, pX->GetEnd()+nStartPos );
/*N*/                       else
/*N*/                       {
/*?*/                           SfxPoolItem* pNew = pX->GetItem()->Clone();
/*?*/                           ConvertItem( *pNew, eSourceUnit, eDestUnit );
/*?*/                           pAttr = MakeCharAttrib( aEditDoc.GetItemPool(), *pNew, pX->GetStart()+nStartPos, pX->GetEnd()+nStartPos );
/*?*/                           delete pNew;
/*N*/                       }
/*N*/                       DBG_ASSERT( pAttr->GetEnd() <= aPaM.GetNode()->Len(), "InsertBinTextObject: Attribut passt nicht! (1)" );
/*N*/                       aPaM.GetNode()->GetCharAttribs().InsertAttrib( pAttr );
/*N*/                       if ( pAttr->Which() == EE_FEATURE_FIELD )
/*N*/                             bUpdateFields = TRUE;
/*N*/                   }
/*N*/                   else
/*N*/                   {
/*?*/                       DBG_ASSERT( pX->GetEnd()+nStartPos <= aPaM.GetNode()->Len(), "InsertBinTextObject: Attribut passt nicht! (2)" );
/*?*/                       // Tabs und andere Features koennen nicht ueber InsertAttrib eingefuegt werden:
/*?*/                       aEditDoc.InsertAttrib( aPaM.GetNode(), pX->GetStart()+nStartPos, pX->GetEnd()+nStartPos, *pX->GetItem() );
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/             if ( bUpdateFields )
/*N*/                 UpdateFields();
/*N*/
/*N*/             // Sonst QuickFormat => Keine Attribute!
/*N*/           pPortion->MarkSelectionInvalid( nStartPos, pC->GetText().Len() );
/*N*/       }
/*N*/
/*N*/       DBG_ASSERT( CheckOrderedList( aPaM.GetNode()->GetCharAttribs().GetAttribs(), sal_True ), "InsertBinTextObject: Start-Liste verdreht" );
/*N*/
/*N*/       sal_Bool bParaAttribs = sal_False;
/*N*/       if ( bNewContent || ( ( n > 0 ) && ( n < (nContents-1) ) ) )
/*N*/       {
/*N*/             bParaAttribs = sal_False;
/*N*/             // #101512# Don't overwrite level/style from existing paragraph in OutlineView
/*N*/             // MT 10/2002: Removed because of #103874#, handled in Outliner::EndPasteOrDropHdl now.
/*N*/ //            if ( !aStatus.IsOutliner() || n )
/*N*/             {
/*N*/               // nur dann Style und ParaAttribs, wenn neuer Absatz, oder
/*N*/               // komplett inneliegender...
/*N*/               bParaAttribs = pC->GetParaAttribs().Count() ? sal_True : sal_False;
/*N*/               if ( GetStyleSheetPool() && pC->GetStyle().Len() )
/*N*/               {
/*N*/                   SfxStyleSheet* pStyle = (SfxStyleSheet*)GetStyleSheetPool()->Find( pC->GetStyle(), pC->GetFamily() );
/*N*/                   DBG_ASSERT( pStyle, "InsertBinTextObject - Style not found!" );
/*N*/                   SetStyleSheet( nPara, pStyle );
/*N*/               }
/*N*/               if ( !bConvertItems )
/*N*/                   SetParaAttribs( aEditDoc.GetPos( aPaM.GetNode() ), pC->GetParaAttribs() );
/*N*/               else
/*N*/               {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/                    SfxItemSet aAttribs( GetEmptyItemSet() );
//STRIP001 /*?*/                    ConvertAndPutItems( aAttribs, pC->GetParaAttribs(), &eSourceUnit, &eDestUnit );
//STRIP001 /*?*/                    SetParaAttribs( aEditDoc.GetPos( aPaM.GetNode() ), aAttribs );
/*N*/               }
/*N*/             }
/*N*/           if ( bNewContent && bUsePortionInfo )
/*N*/           {
/*?*/               XParaPortion* pXP = pPortionInfo->GetObject( n );
/*?*/               DBG_ASSERT( pXP, "InsertBinTextObject: PortionInfo?" );
/*?*/               ParaPortion* pParaPortion = GetParaPortions()[ nPara ];
/*?*/               DBG_ASSERT( pParaPortion, "InsertBinTextObject: ParaPortion?" );
/*?*/               pParaPortion->nHeight = pXP->nHeight;
/*?*/               pParaPortion->nFirstLineOffset = pXP->nFirstLineOffset;
/*?*/               pParaPortion->bForceRepaint = sal_True;
/*?*/               pParaPortion->SetValid();   // Nicht formatieren
/*?*/
/*?*/               // Die TextPortions
/*?*/               pParaPortion->GetTextPortions().Reset();
/*?*/               sal_uInt16 nCount = pXP->aTextPortions.Count();
/*?*/               for ( sal_uInt16 n = 0; n < nCount; n++ )
/*?*/               {
/*?*/                   TextPortion* pTextPortion = pXP->aTextPortions[n];
/*?*/                   TextPortion* pNew = new TextPortion( *pTextPortion );
/*?*/                   pParaPortion->GetTextPortions().Insert( pNew, n );
/*?*/               }
/*?*/
/*?*/               // Die Zeilen
/*?*/               pParaPortion->GetLines().Reset();
/*?*/               nCount = pXP->aLines.Count();
/*?*/               for ( sal_uInt16 m = 0; m < nCount; m++ )
/*?*/               {
/*?*/                   DBG_ASSERT(0, "STRIP"); //STRIP001 EditLine* pLine = pXP->aLines[m];
//STRIP001 /*?*/                    EditLine* pNew = pLine->Clone();
//STRIP001 /*?*/                    pNew->SetInvalid(); // neu Painten!
//STRIP001 /*?*/                    pParaPortion->GetLines().Insert( pNew, m );
/*?*/               }
/*?*/ #ifdef DBG_UTIL
/*?*/               USHORT nTest, nTPLen = 0, nTxtLen = 0;
/*?*/               for ( nTest = pParaPortion->GetTextPortions().Count(); nTest; )
/*?*/                   nTPLen += pParaPortion->GetTextPortions().GetObject( --nTest )->GetLen();
/*?*/               for ( nTest = pParaPortion->GetLines().Count(); nTest; )
/*?*/                   nTxtLen += pParaPortion->GetLines().GetObject( --nTest )->GetLen();
/*?*/               DBG_ASSERT( ( nTPLen == pParaPortion->GetNode()->Len() ) && ( nTxtLen == pParaPortion->GetNode()->Len() ), "InsertBinTextObject: ParaPortion not completely formatted!" );
/*?*/ #endif
/*N*/           }
/*N*/       }
/*N*/       if ( !bParaAttribs ) // DefFont wird bei FastInsertParagraph nicht berechnet
/*N*/       {
/*N*/           aPaM.GetNode()->GetCharAttribs().GetDefFont() = aEditDoc.GetDefFont();
/*N*/           if ( aStatus.UseCharAttribs() )
/*N*/               aPaM.GetNode()->CreateDefFont();
/*N*/       }
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/       if ( bNewContent && GetStatus().DoOnlineSpelling() && pC->GetWrongList() )
/*?*/       {DBG_ASSERT(0, "STRIP");} //STRIP001    aPaM.GetNode()->SetWrongList( pC->GetWrongList()->Clone() );
/*N*/ #endif // !SVX_LIGHT
/*N*/
/*N*/       // Zeilenumbruch, wenn weitere folgen...
/*N*/       if ( n < ( nContents-1) )
/*N*/       {
/*N*/           if ( bNewContent )
/*N*/               aPaM = ImpFastInsertParagraph( nPara+1 );
/*N*/           else
/*?*/               aPaM = ImpInsertParaBreak( aPaM, sal_False );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   aSel.Max() = aPaM;
/*N*/   DBG_ASSERT( !aSel.DbgIsBuggy( aEditDoc ), "InsertBibTextObject: Selektion kaput!(1)" );
/*N*/   return aSel;
/*N*/ }

/*N*/ LanguageType ImpEditEngine::GetLanguage( const EditPaM& rPaM, USHORT* pEndPos ) const
/*N*/ {
/*N*/   short nScriptType = GetScriptType( rPaM, pEndPos ); // pEndPos will be valid now, pointing to ScriptChange or NodeLen
/*N*/   USHORT nLangId = GetScriptItemId( EE_CHAR_LANGUAGE, nScriptType );
/*N*/   const SvxLanguageItem* pLangItem = &(const SvxLanguageItem&)rPaM.GetNode()->GetContentAttribs().GetItem( nLangId );
/*N*/   EditCharAttrib* pAttr = rPaM.GetNode()->GetCharAttribs().FindAttrib( nLangId, rPaM.GetIndex() );
/*N*/   if ( pAttr )
/*?*/       pLangItem = (const SvxLanguageItem*)pAttr->GetItem();
/*N*/
/*N*/   if ( pEndPos && pAttr && ( pAttr->GetEnd() < *pEndPos ) )
/*?*/       *pEndPos = pAttr->GetEnd();
/*N*/
/*N*/   return pLangItem->GetLanguage();
/*N*/ }

/*N*/ ::com::sun::star::lang::Locale ImpEditEngine::GetLocale( const EditPaM& rPaM ) const
/*N*/ {
/*N*/   return SvxCreateLocale( GetLanguage( rPaM ) );
/*N*/ }

//STRIP001 Reference< XSpellChecker1 > ImpEditEngine::GetSpeller()
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  if ( !xSpeller.is() )
//STRIP001      xSpeller = SvxGetSpellChecker();
//STRIP001 #endif
//STRIP001  return xSpeller;
//STRIP001 }

//STRIP001 EESpellState ImpEditEngine::Spell( EditView* pEditView, sal_Bool bMultipleDoc )
//STRIP001 {
//STRIP001 #ifdef SVX_LIGHT
//STRIP001  return EE_SPELL_NOSPELLER;
//STRIP001 #else
//STRIP001
//STRIP001  DBG_ASSERTWARNING( xSpeller.is(), "Kein Speller gesetzt!" );
//STRIP001
//STRIP001  if ( !xSpeller.is() )
//STRIP001      return EE_SPELL_NOSPELLER;
//STRIP001
//STRIP001  aOnlineSpellTimer.Stop();
//STRIP001
//STRIP001  sal_Bool bForward = !EditSpellWrapper::IsSpellReverse();
//STRIP001
//STRIP001  // Bei MultipleDoc immer von vorne/hinten...
//STRIP001  if ( bMultipleDoc )
//STRIP001  {
//STRIP001      if ( bForward )
//STRIP001          pEditView->pImpEditView->SetEditSelection( aEditDoc.GetStartPaM() );
//STRIP001      else
//STRIP001          pEditView->pImpEditView->SetEditSelection( aEditDoc.GetEndPaM() );
//STRIP001  }
//STRIP001
//STRIP001  EditSelection aCurSel( pEditView->pImpEditView->GetEditSelection() );
//STRIP001  pSpellInfo = new SpellInfo;
//STRIP001  pSpellInfo->bMultipleDoc = bMultipleDoc;
//STRIP001  if ( bForward )
//STRIP001      pSpellInfo->aSpellStart = CreateEPaM( SelectWord( aCurSel, ::com::sun::star::i18n::WordType::DICTIONARY_WORD ).Min() );
//STRIP001  else
//STRIP001      pSpellInfo->aSpellStart = CreateEPaM( SelectWord( aCurSel, ::com::sun::star::i18n::WordType::DICTIONARY_WORD ).Max() );
//STRIP001
//STRIP001  sal_Bool bIsStart = sal_False;
//STRIP001  if ( bMultipleDoc )
//STRIP001      bIsStart = sal_True;    // Immer von Vorne bzw. von hinten...
//STRIP001  else if ( bForward && ( CreateEPaM( aEditDoc.GetStartPaM() ) == pSpellInfo->aSpellStart ) )
//STRIP001      bIsStart = sal_True;
//STRIP001  else if ( !bForward && ( CreateEPaM( aEditDoc.GetEndPaM() ) == pSpellInfo->aSpellStart ) )
//STRIP001      bIsStart = sal_True;
//STRIP001
//STRIP001  EditSpellWrapper* pWrp = new EditSpellWrapper( Application::GetDefModalDialogParent(),
//STRIP001          xSpeller, bIsStart, sal_False, pEditView );
//STRIP001  pWrp->SpellDocument();
//STRIP001  delete pWrp;
//STRIP001
//STRIP001  if ( !bMultipleDoc )
//STRIP001  {
//STRIP001      pEditView->pImpEditView->DrawSelection();
//STRIP001      if ( aCurSel.Max().GetIndex() > aCurSel.Max().GetNode()->Len() )
//STRIP001          aCurSel.Max().GetIndex() = aCurSel.Max().GetNode()->Len();
//STRIP001      aCurSel.Min() = aCurSel.Max();
//STRIP001      pEditView->pImpEditView->SetEditSelection( aCurSel );
//STRIP001      pEditView->pImpEditView->DrawSelection();
//STRIP001      pEditView->ShowCursor( sal_True, sal_False );
//STRIP001  }
//STRIP001  EESpellState eState = pSpellInfo->eState;
//STRIP001  delete pSpellInfo;
//STRIP001  pSpellInfo = 0;
//STRIP001  return eState;
//STRIP001 #endif
//STRIP001 }

//STRIP001 Reference< XSpellAlternatives > ImpEditEngine::ImpSpell( EditView* pEditView )
//STRIP001 {
//STRIP001 #ifdef SVX_LIGHT
//STRIP001  return Reference< XSpellAlternatives >();
//STRIP001 #else
//STRIP001
//STRIP001  DBG_ASSERT( xSpeller.is(), "Kein Speller gesetzt!" );
//STRIP001
//STRIP001  sal_Bool bForward = !EditSpellWrapper::IsSpellReverse();
//STRIP001  ContentNode* pLastNode = aEditDoc.SaveGetObject( bForward ? (aEditDoc.Count()-1) : 0 );
//STRIP001  EditSelection aCurSel( pEditView->pImpEditView->GetEditSelection() );
//STRIP001  if ( bForward )
//STRIP001      aCurSel.Min() = aCurSel.Max();
//STRIP001  else
//STRIP001      aCurSel.Max() = aCurSel.Min();
//STRIP001
//STRIP001  String aWord;
//STRIP001  Reference< XSpellAlternatives > xSpellAlt;
//STRIP001  Sequence< PropertyValue > aEmptySeq;
//STRIP001  while (!xSpellAlt.is())
//STRIP001  {
//STRIP001
//STRIP001      // Bekannter (wahrscheinlicher) Bug: Wenn SpellToCurrent, muss
//STRIP001      // Current bei jeder Ersetzung korrigiert werden, sonst passt
//STRIP001      // das Ende evtl. nicht mehr genau...
//STRIP001      if ( pSpellInfo->bSpellToEnd || pSpellInfo->bMultipleDoc )
//STRIP001      {
//STRIP001          if ( aCurSel.Max().GetNode() == pLastNode )
//STRIP001          {
//STRIP001              if ( bForward && ( aCurSel.Max().GetIndex() >= pLastNode->Len() ) )
//STRIP001                  break;
//STRIP001              else if ( !bForward && ( !aCurSel.Min().GetIndex() ) )
//STRIP001                  break;
//STRIP001          }
//STRIP001      }
//STRIP001      else if ( !pSpellInfo->bSpellToEnd )
//STRIP001      {
//STRIP001          EPaM aEPaM( CreateEPaM( aCurSel.Max() ) );
//STRIP001          if ( bForward && !( aEPaM < pSpellInfo->aSpellTo ) )
//STRIP001              break;
//STRIP001          else if ( !bForward && ( aEPaM < pSpellInfo->aSpellTo ) )
//STRIP001              break;
//STRIP001      }
//STRIP001
//STRIP001      // Bei Rueckwaerts-Suche erst zurueck, sonst wird das gleiche Wort wieder gespellt.
//STRIP001      if ( !bForward )
//STRIP001          aCurSel = WordLeft( aCurSel.Min(), ::com::sun::star::i18n::WordType::DICTIONARY_WORD );
//STRIP001
//STRIP001      aCurSel = SelectWord( aCurSel, ::com::sun::star::i18n::WordType::DICTIONARY_WORD );
//STRIP001      aWord = GetSelected( aCurSel );
//STRIP001
//STRIP001      // Wenn Punkt dahinter, muss dieser mit uebergeben werden !
//STRIP001      // Falls Abkuerzung...
//STRIP001      if ( aWord.Len() && ( aCurSel.Max().GetIndex() < aCurSel.Max().GetNode()->Len() ) )
//STRIP001      {
//STRIP001          sal_Unicode cNext = aCurSel.Max().GetNode()->GetChar( aCurSel.Max().GetIndex() );
//STRIP001          if ( cNext == '.' )
//STRIP001          {
//STRIP001              aCurSel.Max().GetIndex()++;
//STRIP001              aWord += cNext;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if ( aWord.Len() > 1 )
//STRIP001          xSpellAlt = xSpeller->spell( aWord, GetLanguage( aCurSel.Max() ), aEmptySeq );
//STRIP001
//STRIP001      if ( bForward && !xSpellAlt.is() )
//STRIP001          aCurSel = WordRight( aCurSel.Min(), ::com::sun::star::i18n::WordType::DICTIONARY_WORD );
//STRIP001      else
//STRIP001          pSpellInfo->eState = EE_SPELL_ERRORFOUND;
//STRIP001  }
//STRIP001
//STRIP001  pEditView->pImpEditView->DrawSelection();
//STRIP001  pEditView->pImpEditView->SetEditSelection( aCurSel );
//STRIP001  pEditView->pImpEditView->DrawSelection();
//STRIP001  pEditView->ShowCursor( sal_True, sal_False );
//STRIP001  return xSpellAlt;
//STRIP001 #endif
//STRIP001 }

//STRIP001 void ImpEditEngine::DoOnlineSpelling( ContentNode* pThisNodeOnly, sal_Bool bSpellAtCursorPos, sal_Bool bInteruptable )
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  /*
//STRIP001   Er wird ueber alle Absaetze iteriert, nur Absaetze mit invalidierter
//STRIP001   WrongList werden geprueft...
//STRIP001
//STRIP001   Es werden alle Woerter im invalidierten Bereich geprueft.
//STRIP001   Ist ein Wort falsch, aber noch nicht in der WrongList, oder umgekehrt,
//STRIP001   wird der Bereich des Wortes invalidiert
//STRIP001    ( kein Invalidate, sondern wenn nur Uebergaenge von richtig=>falsch,
//STRIP001      einfaches Paint, bei Uebergaengen von falsch=>richtig mit VDev
//STRIP001      ueberplaetten )
//STRIP001  */
//STRIP001
//STRIP001      if ( !xSpeller.is() )
//STRIP001      return;
//STRIP001
//STRIP001  EditPaM aCursorPos;
//STRIP001  if( pActiveView && !bSpellAtCursorPos )
//STRIP001  {
//STRIP001      DBG_CHKOBJ( pActiveView, EditView, 0 );
//STRIP001      aCursorPos = pActiveView->pImpEditView->GetEditSelection().Max();
//STRIP001  }
//STRIP001  sal_Bool bRestartTimer = sal_False;
//STRIP001
//STRIP001  ContentNode* pLastNode = aEditDoc.SaveGetObject( aEditDoc.Count() - 1 );
//STRIP001  sal_uInt16 nNodes = GetEditDoc().Count();
//STRIP001  sal_uInt16 nInvalids = 0;
//STRIP001  Sequence< PropertyValue > aEmptySeq;
//STRIP001  for ( sal_uInt16 n = 0; n < nNodes; n++ )
//STRIP001  {
//STRIP001      ContentNode* pNode = GetEditDoc().GetObject( n );
//STRIP001      if ( pThisNodeOnly )
//STRIP001          pNode = pThisNodeOnly;
//STRIP001
//STRIP001      if ( pNode->GetWrongList()->IsInvalid() )
//STRIP001      {
//STRIP001          WrongList* pWrongList = pNode->GetWrongList();
//STRIP001          sal_uInt16 nInvStart = pWrongList->GetInvalidStart();
//STRIP001          sal_uInt16 nInvEnd = pWrongList->GetInvalidEnd();
//STRIP001
//STRIP001          sal_uInt16 nWrongs = 0; // Auch im Absatz mal die Kontrolle abgeben...
//STRIP001 //           sal_Bool bStop = sal_False;
//STRIP001
//STRIP001          sal_uInt16 nPaintFrom = 0xFFFF, nPaintTo;
//STRIP001          sal_Bool bSimpleRepaint = sal_True;
//STRIP001
//STRIP001          pWrongList->SetValid();
//STRIP001
//STRIP001          EditPaM aPaM( pNode, nInvStart );
//STRIP001          EditSelection aSel( aPaM, aPaM );
//STRIP001          while ( ( aSel.Max().GetNode() == pNode ) /* && !bStop */ )
//STRIP001          {
//STRIP001              if ( ( aSel.Min().GetIndex() > nInvEnd )
//STRIP001                      || ( ( aSel.Max().GetNode() == pLastNode ) && ( aSel.Max().GetIndex() >= pLastNode->Len() ) ) )
//STRIP001                  break;  // Dokument- oder Ungueltigkeitsbereich-Ende
//STRIP001
//STRIP001              aSel = SelectWord( aSel, ::com::sun::star::i18n::WordType::DICTIONARY_WORD );
//STRIP001              String aWord( GetSelected( aSel ) );
//STRIP001              // Wenn Punkt dahinter, muss dieser mit uebergeben werden !
//STRIP001              // Falls Abkuerzung...
//STRIP001              sal_Bool bDottAdded = sal_False;
//STRIP001              if ( aSel.Max().GetIndex() < aSel.Max().GetNode()->Len() )
//STRIP001              {
//STRIP001                  sal_Unicode cNext = aSel.Max().GetNode()->GetChar( aSel.Max().GetIndex() );
//STRIP001                  if ( cNext == '.' )
//STRIP001                  {
//STRIP001                      aSel.Max().GetIndex()++;
//STRIP001                      aWord += cNext;
//STRIP001                      bDottAdded = sal_True;
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              sal_Bool bChanged = sal_False;
//STRIP001              if ( aWord.Len() > 1 )
//STRIP001              {
//STRIP001                  sal_uInt16 nWStart = aSel.Min().GetIndex();
//STRIP001                  sal_uInt16 nWEnd= aSel.Max().GetIndex();
//STRIP001                  if ( !xSpeller->isValid( aWord, GetLanguage( EditPaM( aSel.Min().GetNode(), nWStart+1 ) ), aEmptySeq ) )
//STRIP001                  {
//STRIP001                      // Pruefen, ob schon richtig markiert...
//STRIP001                      nWrongs++;
//STRIP001                      // Nur bei SimpleRepaint stoppen, sonst zu oft VDev
//STRIP001 //                       if ( ( nWrongs > 8 ) && bSimpleRepaint )
//STRIP001 //                       {
//STRIP001 //                           bStop = sal_True;
//STRIP001 //                           pWrongList->MarkInvalid( aSel.Max().GetIndex(), nInvEnd );
//STRIP001 //                       }
//STRIP001                      sal_uInt16 nXEnd = bDottAdded ? nWEnd -1 : nWEnd;
//STRIP001                      if ( !pWrongList->HasWrong( nWStart, nXEnd ) )
//STRIP001                      {
//STRIP001                          // Wort als falsch markieren...
//STRIP001                          // Aber nur, wenn nicht an Cursor-Position...
//STRIP001                          sal_Bool bCursorPos = sal_False;
//STRIP001                          if ( aCursorPos.GetNode() == pNode )
//STRIP001                          {
//STRIP001                              if ( ( nWStart <= aCursorPos.GetIndex() ) && nWEnd >= aCursorPos.GetIndex() )
//STRIP001                                  bCursorPos = sal_True;
//STRIP001                          }
//STRIP001                          if ( bCursorPos )
//STRIP001                          {
//STRIP001                              // Dann weiter als ungueltig markieren...
//STRIP001                              pWrongList->GetInvalidStart() = nWStart;
//STRIP001                              pWrongList->GetInvalidEnd() = nWEnd;
//STRIP001                              bRestartTimer = sal_True;
//STRIP001                          }
//STRIP001                          else
//STRIP001                          {
//STRIP001                              // Es kann sein, dass die Wrongs in der Liste nicht
//STRIP001                              // genau ueber Woerter aufgespannt sind, weil die
//STRIP001                              // WordDelimiters beim Expandieren nicht ausgewrtet werden.
//STRIP001                              pWrongList->InsertWrong( nWStart, nXEnd, sal_True );
//STRIP001                              bChanged = sal_True;
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      // Pruefen, ob nicht als als falsch markiert....
//STRIP001                      if ( pWrongList->HasAnyWrong( nWStart, nWEnd ) )
//STRIP001                      {
//STRIP001                          pWrongList->ClearWrongs( nWStart, nWEnd, pNode );
//STRIP001                          bSimpleRepaint = sal_False;
//STRIP001                          bChanged = sal_True;
//STRIP001                      }
//STRIP001                  }
//STRIP001                  if ( bChanged  )
//STRIP001                  {
//STRIP001                      if ( nPaintFrom == 0xFFFF )
//STRIP001                          nPaintFrom = nWStart;
//STRIP001                      nPaintTo = nWEnd;
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              EditPaM aLastEnd( aSel.Max() );
//STRIP001              aSel = WordRight( aSel.Max(), ::com::sun::star::i18n::WordType::DICTIONARY_WORD );
//STRIP001              if ( bChanged && ( aSel.Min().GetNode() == pNode ) &&
//STRIP001                      ( ( aSel.Min().GetIndex()-aLastEnd.GetIndex() > 1 ) ) )
//STRIP001              {
//STRIP001                  // Wenn zwei Worte durch mehr Zeichen als ein Blank getrennt
//STRIP001                  // sind, kann es passieren, dass beim Aufsplitten eines Wrongs
//STRIP001                  // der Start den zweiten Wortes vor dem tatsaechlich Wort liegt
//STRIP001                  pWrongList->ClearWrongs( aLastEnd.GetIndex(), aSel.Min().GetIndex(), pNode );
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          // Invalidieren?
//STRIP001          if ( ( nPaintFrom != 0xFFFF ) && ( GetStatus().DoDrawRedLines() ) )
//STRIP001          {
//STRIP001              aStatus.GetStatusWord() |= EE_STAT_WRONGWORDCHANGED;
//STRIP001              CallStatusHdl();
//STRIP001
//STRIP001              if ( aEditViews.Count() )
//STRIP001              {
//STRIP001                  // Bei SimpleRepaint wuerde ein uebermalen ohne VDev reichen,
//STRIP001                  // aber dann muesste ich ueber alle Views, Intersecten,
//STRIP001                  // Clippen, ...
//STRIP001                  // Lohnt wahrscheinlich nicht.
//STRIP001                  EditPaM aStartPaM( pNode, nPaintFrom );
//STRIP001                  EditPaM aEndPaM( pNode, nPaintTo );
//STRIP001                  Rectangle aStartCursor( PaMtoEditCursor( aStartPaM ) );
//STRIP001                  Rectangle aEndCursor( PaMtoEditCursor( aEndPaM ) );
//STRIP001                  DBG_ASSERT( aInvalidRec.IsEmpty(), "InvalidRect gesetzt!" );
//STRIP001                  aInvalidRec.Left() = 0;
//STRIP001                  aInvalidRec.Right() = GetPaperSize().Width();
//STRIP001                  aInvalidRec.Top() = aStartCursor.Top();
//STRIP001                  aInvalidRec.Bottom() = aEndCursor.Bottom();
//STRIP001                  if ( pActiveView && pActiveView->HasSelection() )
//STRIP001                  {
//STRIP001                      // Dann darf nicht ueber VDev ausgegeben werden
//STRIP001                      UpdateViews( NULL );
//STRIP001                  }
//STRIP001                  else if ( bSimpleRepaint )
//STRIP001                  {
//STRIP001                      for ( sal_uInt16 nView = 0; nView < aEditViews.Count(); nView++ )
//STRIP001                      {
//STRIP001                          EditView* pView = aEditViews[nView];
//STRIP001                          Rectangle aClipRec( aInvalidRec );
//STRIP001                          aClipRec.Intersection( pView->GetVisArea() );
//STRIP001                          if ( !aClipRec.IsEmpty() )
//STRIP001                          {
//STRIP001                              // in Fensterkoordinaten umwandeln....
//STRIP001                              aClipRec.SetPos( pView->pImpEditView->GetWindowPos( aClipRec.TopLeft() ) );
//STRIP001                              // Wenn Selektion, dann VDev...
//STRIP001                              Paint( pView->pImpEditView, aClipRec, pView->HasSelection() );
//STRIP001                              aInvalidRec = Rectangle();
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001                  else
//STRIP001                      UpdateViews( pActiveView );
//STRIP001              }
//STRIP001
//STRIP001          }
//STRIP001          // Nach zwei korrigierten Nodes die Kontrolle abgeben...
//STRIP001          nInvalids++;
//STRIP001          if ( bInteruptable && ( nInvalids >= 2 ) )
//STRIP001          {
//STRIP001              bRestartTimer = sal_True;
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if ( pThisNodeOnly )
//STRIP001          break;
//STRIP001  }
//STRIP001  if ( bRestartTimer )
//STRIP001      aOnlineSpellTimer.Start();
//STRIP001 #endif // !SVX_LIGHT
//STRIP001 }


//STRIP001 EESpellState ImpEditEngine::HasSpellErrors()
//STRIP001 {
//STRIP001  DBG_ASSERT( xSpeller.is(), "Kein Speller gesetzt!" );
//STRIP001
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  ContentNode* pLastNode = aEditDoc.SaveGetObject( aEditDoc.Count() - 1 );
//STRIP001  EditSelection aCurSel( aEditDoc.GetStartPaM() );
//STRIP001
//STRIP001  String aWord;
//STRIP001  Reference< XSpellAlternatives > xSpellAlt;
//STRIP001  Sequence< PropertyValue > aEmptySeq;
//STRIP001  while ( !xSpellAlt.is() )
//STRIP001  {
//STRIP001      if ( ( aCurSel.Max().GetNode() == pLastNode ) &&
//STRIP001           ( aCurSel.Max().GetIndex() >= pLastNode->Len() ) )
//STRIP001      {
//STRIP001          return EE_SPELL_OK;
//STRIP001      }
//STRIP001
//STRIP001      aCurSel = SelectWord( aCurSel, ::com::sun::star::i18n::WordType::DICTIONARY_WORD );
//STRIP001      aWord = GetSelected( aCurSel );
//STRIP001      if ( aWord.Len() > 1 )
//STRIP001          xSpellAlt = xSpeller->spell( aWord, GetLanguage( aCurSel.Max() ), aEmptySeq );
//STRIP001      aCurSel = WordRight( aCurSel.Max(), ::com::sun::star::i18n::WordType::DICTIONARY_WORD );
//STRIP001  }
//STRIP001 #endif
//STRIP001
//STRIP001  return EE_SPELL_ERRORFOUND;
//STRIP001 }

//STRIP001 EESpellState ImpEditEngine::StartThesaurus( EditView* pEditView )
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  EditSelection aCurSel( pEditView->pImpEditView->GetEditSelection() );
//STRIP001  if ( !aCurSel.HasRange() )
//STRIP001      aCurSel = SelectWord( aCurSel, ::com::sun::star::i18n::WordType::DICTIONARY_WORD );
//STRIP001  String aWord( GetSelected( aCurSel ) );
//STRIP001
//STRIP001  Reference< XThesaurus > xThes( SvxGetThesaurus() );
//STRIP001  if (!xThes.is())
//STRIP001      return EE_SPELL_ERRORFOUND;
//STRIP001
//STRIP001  SvxThesaurusDialog aDialog( pEditView->GetWindow(), xThes, aWord, GetLanguage( aCurSel.Max() ) );
//STRIP001
//STRIP001  if ( aDialog.Execute() == RET_OK )
//STRIP001  {
//STRIP001      // Wort ersetzen...
//STRIP001      pEditView->pImpEditView->DrawSelection();
//STRIP001      pEditView->pImpEditView->SetEditSelection( aCurSel );
//STRIP001      pEditView->pImpEditView->DrawSelection();
//STRIP001      pEditView->InsertText( aDialog.GetWord() );
//STRIP001      pEditView->ShowCursor( sal_True, sal_False );
//STRIP001  }
//STRIP001
//STRIP001  return EE_SPELL_OK;
//STRIP001 #else
//STRIP001  return EE_SPELL_NOSPELLER;
//STRIP001 #endif
//STRIP001 }

//STRIP001 sal_uInt16 ImpEditEngine::StartSearchAndReplace( EditView* pEditView, const SvxSearchItem& rSearchItem )
//STRIP001 {
//STRIP001  sal_uInt16 nFound = 0;
//STRIP001
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  EditSelection aCurSel( pEditView->pImpEditView->GetEditSelection() );
//STRIP001
//STRIP001  // FIND_ALL ohne Mehrfachselektion nicht moeglich.
//STRIP001  if ( ( rSearchItem.GetCommand() == SVX_SEARCHCMD_FIND ) ||
//STRIP001       ( rSearchItem.GetCommand() == SVX_SEARCHCMD_FIND_ALL ) )
//STRIP001  {
//STRIP001      if ( Search( rSearchItem, pEditView ) )
//STRIP001          nFound++;
//STRIP001  }
//STRIP001  else if ( rSearchItem.GetCommand() == SVX_SEARCHCMD_REPLACE )
//STRIP001  {
//STRIP001      // Das Wort ist selektiert, wenn der Anwender die Selektion
//STRIP001      // nicht zwischendurch manipuliert:
//STRIP001      if ( aCurSel.HasRange() )
//STRIP001      {
//STRIP001          pEditView->InsertText( rSearchItem.GetReplaceString() );
//STRIP001          nFound = 1;
//STRIP001      }
//STRIP001      else
//STRIP001          if( Search( rSearchItem, pEditView ) )
//STRIP001              nFound = 1;
//STRIP001  }
//STRIP001  else if ( rSearchItem.GetCommand() == SVX_SEARCHCMD_REPLACE_ALL )
//STRIP001  {
//STRIP001      // Der Writer ersetzt alle, vorn Anfang bis Ende...
//STRIP001      SvxSearchItem aTmpItem( rSearchItem );
//STRIP001      aTmpItem.SetBackward( sal_False );
//STRIP001
//STRIP001      pEditView->pImpEditView->DrawSelection();
//STRIP001
//STRIP001         aCurSel.Adjust( aEditDoc );
//STRIP001      EditPaM aStartPaM = aTmpItem.GetSelection() ? aCurSel.Min() : aEditDoc.GetStartPaM();
//STRIP001      EditSelection aFoundSel( aCurSel.Max() );
//STRIP001      sal_Bool bFound = ImpSearch( aTmpItem, aCurSel, aStartPaM, aFoundSel );
//STRIP001      if ( bFound )
//STRIP001          UndoActionStart( EDITUNDO_REPLACEALL );
//STRIP001      while ( bFound )
//STRIP001      {
//STRIP001          nFound++;
//STRIP001          aStartPaM = ImpInsertText( aFoundSel, rSearchItem.GetReplaceString() );
//STRIP001          bFound = ImpSearch( aTmpItem, aCurSel, aStartPaM, aFoundSel );
//STRIP001      }
//STRIP001      if ( nFound )
//STRIP001      {
//STRIP001          EditPaM aNewPaM( aFoundSel.Max() );
//STRIP001          if ( aNewPaM.GetIndex() > aNewPaM.GetNode()->Len() )
//STRIP001              aNewPaM.GetIndex() =  aNewPaM.GetNode()->Len();
//STRIP001          pEditView->pImpEditView->SetEditSelection( aNewPaM );
//STRIP001          FormatAndUpdate( pEditView );
//STRIP001          UndoActionEnd( EDITUNDO_REPLACEALL );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pEditView->pImpEditView->DrawSelection();
//STRIP001          pEditView->ShowCursor( sal_True, sal_False );
//STRIP001      }
//STRIP001  }
//STRIP001 #endif // !SVX_LIGHT
//STRIP001  return nFound;
//STRIP001 }

//STRIP001 BOOL ImpEditEngine::Search( const SvxSearchItem& rSearchItem, EditView* pEditView )
//STRIP001 {
//STRIP001  EditSelection aSel( pEditView->pImpEditView->GetEditSelection() );
//STRIP001  aSel.Adjust( aEditDoc );
//STRIP001  EditPaM aStartPaM( aSel.Max() );
//STRIP001  if ( rSearchItem.GetSelection() && !rSearchItem.GetBackward() )
//STRIP001      aStartPaM = aSel.Min();
//STRIP001
//STRIP001  EditSelection aFoundSel;
//STRIP001  BOOL bFound = ImpSearch( rSearchItem, aSel, aStartPaM, aFoundSel );
//STRIP001  if ( bFound && ( aFoundSel == aSel ) )  // Bei Rueckwaetssuche
//STRIP001  {
//STRIP001      aStartPaM = aSel.Min();
//STRIP001      bFound = ImpSearch( rSearchItem, aSel, aStartPaM, aFoundSel );
//STRIP001  }
//STRIP001
//STRIP001  pEditView->pImpEditView->DrawSelection();
//STRIP001  if ( bFound )
//STRIP001  {
//STRIP001      // Erstmal das Min einstellen, damit das ganze Wort in den sichtbaren Bereich kommt.
//STRIP001      pEditView->pImpEditView->SetEditSelection( aFoundSel.Min() );
//STRIP001      pEditView->ShowCursor( TRUE, FALSE );
//STRIP001      pEditView->pImpEditView->SetEditSelection( aFoundSel );
//STRIP001  }
//STRIP001  else
//STRIP001      pEditView->pImpEditView->SetEditSelection( aSel.Max() );
//STRIP001
//STRIP001  pEditView->pImpEditView->DrawSelection();
//STRIP001  pEditView->ShowCursor( TRUE, FALSE );
//STRIP001  return bFound;
//STRIP001 }

//STRIP001 sal_Bool ImpEditEngine::ImpSearch( const SvxSearchItem& rSearchItem,
//STRIP001  const EditSelection& rSearchSelection, const EditPaM& rStartPos, EditSelection& rFoundSel )
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  util::SearchOptions aSearchOptions( rSearchItem.GetSearchOptions() );
//STRIP001  aSearchOptions.Locale = GetLocale( rStartPos );
//STRIP001
//STRIP001  sal_Bool bBack = rSearchItem.GetBackward();
//STRIP001  sal_Bool bSearchInSelection = rSearchItem.GetSelection();
//STRIP001  sal_uInt16 nStartNode = aEditDoc.GetPos( rStartPos.GetNode() );
//STRIP001  sal_uInt16 nEndNode;
//STRIP001  if ( bSearchInSelection )
//STRIP001  {
//STRIP001      nEndNode = aEditDoc.GetPos( bBack ? rSearchSelection.Min().GetNode() : rSearchSelection.Max().GetNode() );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      nEndNode = bBack ? 0 : aEditDoc.Count()-1;
//STRIP001  }
//STRIP001
//STRIP001  utl::TextSearch aSearcher( aSearchOptions );
//STRIP001
//STRIP001  // ueber die Absaetze iterieren...
//STRIP001  for ( sal_uInt16 nNode = nStartNode;
//STRIP001          bBack ? ( nNode >= nEndNode ) : ( nNode <= nEndNode) ;
//STRIP001          bBack ? nNode-- : nNode++ )
//STRIP001  {
//STRIP001      // Bei rueckwaertsuche, wenn nEndNode = 0:
//STRIP001      if ( nNode >= 0xFFFF )
//STRIP001          return sal_False;
//STRIP001
//STRIP001      ContentNode* pNode = aEditDoc.GetObject( nNode );
//STRIP001
//STRIP001      sal_uInt16 nStartPos = 0;
//STRIP001      sal_uInt16 nEndPos = pNode->Len();
//STRIP001      if ( nNode == nStartNode )
//STRIP001      {
//STRIP001          if ( bBack )
//STRIP001              nEndPos = rStartPos.GetIndex();
//STRIP001          else
//STRIP001              nStartPos = rStartPos.GetIndex();
//STRIP001      }
//STRIP001      if ( ( nNode == nEndNode ) && bSearchInSelection )
//STRIP001      {
//STRIP001          if ( bBack )
//STRIP001              nStartPos = rSearchSelection.Min().GetIndex();
//STRIP001          else
//STRIP001              nEndPos = rSearchSelection.Max().GetIndex();
//STRIP001      }
//STRIP001
//STRIP001      // Suchen...
//STRIP001      XubString aParaStr( GetEditDoc().GetParaAsString( pNode ) );
//STRIP001      sal_Bool bFound = sal_False;
//STRIP001      if ( bBack )
//STRIP001      {
//STRIP001          SwapUSHORTs( nStartPos, nEndPos );
//STRIP001          bFound = aSearcher.SearchBkwrd( aParaStr, &nStartPos, &nEndPos);
//STRIP001      }
//STRIP001      else
//STRIP001          bFound = aSearcher.SearchFrwrd( aParaStr, &nStartPos, &nEndPos);
//STRIP001
//STRIP001      if ( bFound )
//STRIP001      {
//STRIP001          rFoundSel.Min().SetNode( pNode );
//STRIP001          rFoundSel.Min().SetIndex( nStartPos );
//STRIP001          rFoundSel.Max().SetNode( pNode );
//STRIP001          rFoundSel.Max().SetIndex( nEndPos );
//STRIP001          return sal_True;
//STRIP001      }
//STRIP001  }
//STRIP001 #endif // !SVX_LIGHT
//STRIP001  return sal_False;
//STRIP001 }

//STRIP001 sal_Bool ImpEditEngine::HasText( const SvxSearchItem& rSearchItem )
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  SvxSearchItem aTmpItem( rSearchItem );
//STRIP001  aTmpItem.SetBackward( sal_False );
//STRIP001  aTmpItem.SetSelection( sal_False );
//STRIP001
//STRIP001  EditPaM aStartPaM( aEditDoc.GetStartPaM() );
//STRIP001  EditSelection aDummySel( aStartPaM );
//STRIP001  EditSelection aFoundSel;
//STRIP001  return ImpSearch( aTmpItem, aDummySel, aStartPaM, aFoundSel );
//STRIP001 #else
//STRIP001  return sal_False;
//STRIP001 #endif
//STRIP001 }

//STRIP001 void ImpEditEngine::SetAutoCompleteText( const String& rStr, sal_Bool bClearTipWindow )
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  aAutoCompleteText = rStr;
//STRIP001  if ( bClearTipWindow && pActiveView )
//STRIP001      Help::ShowQuickHelp( pActiveView->GetWindow(), Rectangle(), String(), 0 );
//STRIP001 #endif // !SVX_LIGHT
//STRIP001 }

//STRIP001 EditSelection ImpEditEngine::TransliterateText( const EditSelection& rSelection, sal_Int32 nTransliterationMode )
//STRIP001 {
//STRIP001  EditSelection aSel( rSelection );
//STRIP001  aSel.Adjust( aEditDoc );
//STRIP001
//STRIP001  if ( !aSel.HasRange() )
//STRIP001      aSel = SelectWord( aSel );
//STRIP001
//STRIP001     EditSelection aNewSel( aSel );
//STRIP001
//STRIP001  USHORT nStartNode = aEditDoc.GetPos( aSel.Min().GetNode() );
//STRIP001  USHORT nEndNode = aEditDoc.GetPos( aSel.Max().GetNode() );
//STRIP001
//STRIP001  BOOL bChanges = FALSE;
//STRIP001     BOOL bLenChanged = FALSE;
//STRIP001  EditUndoTransliteration* pUndo = NULL;
//STRIP001
//STRIP001  utl::TransliterationWrapper aTranslitarationWrapper( ::legacy_binfilters::getLegacyProcessServiceFactory(), nTransliterationMode );
//STRIP001  BOOL bConsiderLanguage = aTranslitarationWrapper.needLanguageForTheMode();
//STRIP001
//STRIP001  for ( USHORT nNode = nStartNode; nNode <= nEndNode; nNode++ )
//STRIP001  {
//STRIP001      ContentNode* pNode = aEditDoc.GetObject( nNode );
//STRIP001      xub_StrLen nStartPos = 0;
//STRIP001      xub_StrLen nEndPos = pNode->Len();
//STRIP001      if ( nNode == nStartNode )
//STRIP001          nStartPos = aSel.Min().GetIndex();
//STRIP001      if ( nNode == nEndNode ) // kann auch == nStart sein!
//STRIP001          nEndPos = aSel.Max().GetIndex();
//STRIP001
//STRIP001      USHORT nCurrentStart = nStartPos;
//STRIP001      USHORT nCurrentEnd = nEndPos;
//STRIP001      sal_uInt16 nLanguage = LANGUAGE_SYSTEM;
//STRIP001
//STRIP001      do
//STRIP001      {
//STRIP001          if ( bConsiderLanguage )
//STRIP001          {
//STRIP001              nLanguage = GetLanguage( EditPaM( pNode, nCurrentStart+1 ), &nCurrentEnd );
//STRIP001              if ( nCurrentEnd > nEndPos )
//STRIP001                  nCurrentEnd = nEndPos;
//STRIP001          }
//STRIP001
//STRIP001          xub_StrLen nLen = nCurrentEnd - nCurrentStart;
//STRIP001
//STRIP001          Sequence <long> aOffsets;
//STRIP001          String aNewText( aTranslitarationWrapper.transliterate( *pNode, nLanguage, nCurrentStart, nLen, &aOffsets ) );
//STRIP001
//STRIP001          if( ( nLen != aNewText.Len() ) || !pNode->Equals( aNewText, nCurrentStart, nLen ) )
//STRIP001          {
//STRIP001              bChanges = TRUE;
//STRIP001                 if ( nLen != aNewText.Len() )
//STRIP001                     bLenChanged = TRUE;
//STRIP001
//STRIP001 #ifndef SVX_LIGHT
//STRIP001                 // Create UndoAction on Demand....
//STRIP001              if ( !pUndo && IsUndoEnabled() && !IsInUndo() )
//STRIP001              {
//STRIP001                  ESelection aESel( CreateESel( aSel ) );
//STRIP001                  pUndo = new EditUndoTransliteration( this, aESel, nTransliterationMode );
//STRIP001
//STRIP001                  if ( ( nStartNode == nEndNode ) && !aSel.Min().GetNode()->GetCharAttribs().HasAttrib( aSel.Min().GetIndex(), aSel.Max().GetIndex() ) )
//STRIP001                      pUndo->SetText( aSel.Min().GetNode()->Copy( aSel.Min().GetIndex(), aSel.Max().GetIndex()-aSel.Min().GetIndex() ) );
//STRIP001                  else
//STRIP001                      pUndo->SetText( CreateBinTextObject( aSel, NULL ) );
//STRIP001              }
//STRIP001 #endif
//STRIP001
//STRIP001                 // Change text without loosing the attributes
//STRIP001                 USHORT nCharsAfterTransliteration = aOffsets.getLength();
//STRIP001                 const long* pOffsets = aOffsets.getConstArray();
//STRIP001                 short nDiffs = 0;
//STRIP001                 for ( USHORT n = 0; n < nCharsAfterTransliteration; n++ )
//STRIP001                 {
//STRIP001                     USHORT nCurrentPos = nCurrentStart+n;
//STRIP001                     short nDiff = (nCurrentPos-nDiffs) - pOffsets[n];
//STRIP001
//STRIP001                     if ( !nDiff )
//STRIP001                     {
//STRIP001                         DBG_ASSERT( nCurrentPos < pNode->Len(), "TransliterateText - String smaller than expected!" );
//STRIP001                         pNode->SetChar( nCurrentPos, aNewText.GetChar(n) );
//STRIP001                     }
//STRIP001                     else if ( nDiff < 0 )
//STRIP001                     {
//STRIP001                         // Replace first char, delete the rest...
//STRIP001                         DBG_ASSERT( nCurrentPos < pNode->Len(), "TransliterateText - String smaller than expected!" );
//STRIP001                         pNode->SetChar( nCurrentPos, aNewText.GetChar(n) );
//STRIP001
//STRIP001                         DBG_ASSERT( (nCurrentPos+1) < pNode->Len(), "TransliterateText - String smaller than expected!" );
//STRIP001                         GetEditDoc().RemoveChars( EditPaM( pNode, nCurrentPos+1 ), -nDiff );
//STRIP001                     }
//STRIP001                     else
//STRIP001                     {
//STRIP001                         DBG_ASSERT( nDiff == 1, "TransliterateText - Diff other than expected! But should work..." );
//STRIP001                         GetEditDoc().InsertText( EditPaM( pNode, nCurrentPos ), aNewText.GetChar(n) );
//STRIP001
//STRIP001                     }
//STRIP001                     nDiffs += nDiff;
//STRIP001                 }
//STRIP001
//STRIP001                 if ( nNode == nEndNode )
//STRIP001                     aNewSel.Max().GetIndex() += nDiffs;
//STRIP001
//STRIP001                 ParaPortion* pParaPortion = GetParaPortions()[nNode];
//STRIP001              pParaPortion->MarkSelectionInvalid( nCurrentStart, Max( nCurrentStart+nLen, nCurrentStart+aNewText.Len() ) );
//STRIP001
//STRIP001          }
//STRIP001          nCurrentStart = nCurrentEnd;
//STRIP001      } while( nCurrentEnd < nEndPos );
//STRIP001  }
//STRIP001
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  if ( pUndo )
//STRIP001  {
//STRIP001      ESelection aESel( CreateESel( aNewSel ) );
//STRIP001      pUndo->SetNewSelection( aESel );
//STRIP001      InsertUndo( pUndo );
//STRIP001  }
//STRIP001 #endif
//STRIP001
//STRIP001  if ( bChanges )
//STRIP001     {
//STRIP001         TextModified();
//STRIP001         SetModifyFlag( sal_True );
//STRIP001         if ( bLenChanged )
//STRIP001             UpdateSelections();
//STRIP001      FormatAndUpdate();
//STRIP001     }
//STRIP001
//STRIP001     return aNewSel;
//STRIP001 }

/*N*/ void ImpEditEngine::SetAsianCompressionMode( USHORT n )
/*N*/ {
/*N*/     if ( n != nAsianCompressionMode )
/*N*/     {
/*N*/         nAsianCompressionMode = n;
/*N*/         if ( ImplHasText() )
/*N*/         {
/*N*/             FormatFullDoc();
/*N*/             UpdateViews();
/*N*/         }
/*N*/     }
/*N*/ }

/*N*/ void ImpEditEngine::SetKernAsianPunctuation( BOOL b )
/*N*/ {
/*N*/     if ( b != bKernAsianPunctuation )
/*N*/     {
/*?*/         DBG_ASSERT(0, "STRIP"); //STRIP001 bKernAsianPunctuation = b;
//STRIP001 /*?*/         if ( ImplHasText() )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             FormatFullDoc();
//STRIP001 /*?*/             UpdateViews();
//STRIP001 /*?*/         }
/*N*/     }
/*N*/ }


/*N*/ BOOL ImpEditEngine::ImplHasText() const
/*N*/ {
/*N*/     return ( ( GetEditDoc().Count() > 1 ) || GetEditDoc().GetObject(0)->Len() );
/*N*/ }

//STRIP001 long ImpEditEngine::LogicToTwips( long n )
//STRIP001 {
//STRIP001  Size aSz( n, 0 );
//STRIP001  MapMode aTwipsMode( MAP_TWIP );
//STRIP001  aSz = pRefDev->LogicToLogic( aSz, NULL, &aTwipsMode );
//STRIP001  return aSz.Width();
//STRIP001 }


}
