/*************************************************************************
 *
 *  $RCSfile: sw_rdnds.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:51:02 $
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

#ifndef _PERSIST_HXX //autogen
#include <so3/persist.hxx>
#endif
#ifndef _EMBOBJ_HXX //autogen
#include <so3/embobj.hxx>
#endif
#ifndef SVTOOLS_URIHELPER_HXX
#include <svtools/urihelper.hxx>
#endif
#ifndef _SVX_FONTITEM_HXX //autogen
#include <bf_svx/fontitem.hxx>
#endif
#ifndef _SVX_CSCOITEM_HXX //autogen
#include <bf_svx/cscoitem.hxx>
#endif
#ifndef _SVX_LRSPITEM_HXX //autogen
#include <bf_svx/lrspitem.hxx>
#endif

#ifndef _TXTFTN_HXX //autogen
#include <txtftn.hxx>
#endif
#ifndef _FCHRFMT_HXX //autogen
#include <fchrfmt.hxx>
#endif
#ifndef _CHARATR_HXX
#include <charatr.hxx>
#endif
#ifndef _CHARFMT_HXX //autogen
#include <charfmt.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _RDSWG_HXX
#include <rdswg.hxx>
#endif
#ifndef _SW3IO_HXX
#include <sw3io.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _NDGRF_HXX
#include <ndgrf.hxx>
#endif
#ifndef _NDOLE_HXX
#include <ndole.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _FLYPOS_HXX
#include <flypos.hxx>
#endif
#ifndef _BOOKMRK_HXX
#include <bookmrk.hxx>
#endif
#ifndef _SWGPAR_HXX
#include <swgpar.hxx>
#endif
#ifndef _SWSWERROR_H
#include <swerror.h>
#endif
namespace binfilter {


//////////////////////////////////////////////////////////////////////////////

// Achtung: Jede Routine nimmt an, dass der Record-Header bereits eingelesen
// ist. Sie arbeitet den Record so weit ab wie moeglich und schliesst den
// Vorgang mit end() ab.

//////////////////////////////////////////////////////////////////////////////

// Text-Hints
// nOffset ist ungleich Null, wenn innerhalb eines Nodes eingefuegt werden
// soll. Dann ist nOffset die Start-Position des Textes.

//STRIP001 void SwSwgReader::InTextHints( SwTxtNode& rNd, xub_StrLen nOffset )
//STRIP001 {
//STRIP001  // Dieser Record kann auch leer sein
//STRIP001  // (bei teilweisem Speichern eines Nodes, z.B.)
//STRIP001  short nHt;
//STRIP001  r >> nHt;
//STRIP001  if( nHt < 0 )
//STRIP001  {
//STRIP001      Error(); r.skipnext(); return;
//STRIP001  }
//STRIP001  xub_StrLen nLen = rNd.GetTxt().Len();
//STRIP001  if( nLen ) nLen --;
//STRIP001  for( int i = 0; i < nHt; i++ ) {
//STRIP001      USHORT nOldStart, nOldEnd;
//STRIP001      r >> nOldStart >> nOldEnd;
//STRIP001      r.next();
//STRIP001      xub_StrLen nStart = nOldStart + nOffset;
//STRIP001      xub_StrLen nEnd   = nOldEnd + nOffset;
//STRIP001      if( nOldEnd < nOldStart ) nEnd = nLen;
//STRIP001      USHORT nWhich = InHint( rNd, nStart, nEnd );
//STRIP001      if( nWhich == RES_TXTATR_FTN )
//STRIP001      {
//STRIP001          // Der Footnote-Hint ist somewhat special. Er erhaelt
//STRIP001          // eine Section, wenn er in den TextNode eingefuegt wird.
//STRIP001          // Daher muss der Text getrennt geparst werden
//STRIP001          SwTxtFtn* pFtn = (SwTxtFtn*) rNd.GetTxtAttr( nStart, nWhich );
//STRIP001          SwNodeIndex aIdx( *pFtn->GetStartNode() );
//STRIP001          FillSection( aIdx );
//STRIP001          // den zuletzt eingelesenen Record zuruecksetzen
//STRIP001          r.undonext();
//STRIP001      }
//STRIP001  }
//STRIP001  r.next();
//STRIP001 }

// Bookmarks:

//STRIP001 void SwSwgReader::InNodeBookmark( SwNodeIndex& rPos )
//STRIP001 {
//STRIP001  BYTE cFlags = 0;
//STRIP001  // Flag-Byte: 0x01 = Startmakro, 0x02 = Endmakro
//STRIP001  r >> cFlags;
//STRIP001  String aName = GetText();
//STRIP001  String aShort = GetText();
//STRIP001  if( !r )
//STRIP001      return; // must have
//STRIP001  USHORT nOffset, nKey, nMod;
//STRIP001  r >> nOffset >> nKey >> nMod;
//STRIP001  const SwBookmarks& rMarks = pDoc->GetBookmarks();
//STRIP001  short nArrLen = rMarks.Count();
//STRIP001  SwPaM aPaM( rPos.GetNode(), (xub_StrLen)nOffset );
//STRIP001  pDoc->MakeBookmark( aPaM, KeyCode( nKey, nMod ), aName, aShort );
//STRIP001  if( cFlags )
//STRIP001  {
//STRIP001      SwBookmark* pMark = rMarks[ nArrLen ];
//STRIP001      if( cFlags & 0x01 )
//STRIP001      {
//STRIP001          String aMac = GetText();
//STRIP001          String aLib = GetText();
//STRIP001          SvxMacro aStart( aMac, aLib, STARBASIC );
//STRIP001          pMark->SetStartMacro( aStart );
//STRIP001      }
//STRIP001      if( cFlags & 0x02 )
//STRIP001      {
//STRIP001          String aMac = GetText();
//STRIP001          String aLib = GetText();
//STRIP001          SvxMacro aEnd( aMac, aLib, STARBASIC );
//STRIP001          pMark->SetEndMacro( aEnd );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  r.next();
//STRIP001 }

// Hilfsroutine fuer ConvertText: Suche nach dem naechsten Hint,
// der eine Konversion verbietet. Zur Zeit sind dies Hints, die entweder
// direkt oder indirekt auf einen Font mit CHARSET_SYMBOL hinweisen.

//STRIP001 USHORT SwSwgReader::GetNextSymbolFontHint
//STRIP001 ( SwpHints* pHints, USHORT idx, xub_StrLen& start, xub_StrLen& end )
//STRIP001 {
//STRIP001  if( !pHints ) return 0;
//STRIP001  for( ; idx < pHints->Count(); idx++ )
//STRIP001  {
//STRIP001      const SwTxtAttr* pHnt = (*pHints) [ idx ];
//STRIP001      if( pHnt->Which() == RES_CHRATR_FONT )
//STRIP001      {
//STRIP001          if( pHnt->GetFont().GetCharSet() == RTL_TEXTENCODING_SYMBOL )
//STRIP001          {
//STRIP001              start = *pHnt->GetStart();
//STRIP001              end   = *pHnt->GetEnd() - 1;
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001      // Gibt es einen CharFormat-Hint mit einem Symbol-Font?
//STRIP001      if( pHnt->Which() == RES_TXTATR_CHARFMT )
//STRIP001      {
//STRIP001          SwCharFmt* pFmt = pHnt->GetCharFmt().GetCharFmt();
//STRIP001          if( pFmt->GetAttrSet().GetItemState( RES_CHRATR_FONT, FALSE )
//STRIP001              == SFX_ITEM_SET )
//STRIP001          {
//STRIP001              const SvxFontItem& rAttr = pFmt->GetFont();
//STRIP001              if( rAttr.GetCharSet() == RTL_TEXTENCODING_SYMBOL )
//STRIP001              {
//STRIP001                  start = *pHnt->GetStart();
//STRIP001                  end   = *pHnt->GetEnd();
//STRIP001                  break;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return idx;
//STRIP001 }

//STRIP001 USHORT SwSwgReader::GetNextCharsetColorHint
//STRIP001 ( SwpHints* pHints, USHORT idx, xub_StrLen& start, xub_StrLen& end,
//STRIP001   rtl_TextEncoding eDfltEnc, rtl_TextEncoding& rEnc )
//STRIP001 {
//STRIP001  rEnc = eDfltEnc;
//STRIP001
//STRIP001  if( !pHints ) return 0;
//STRIP001  for( ; idx < pHints->Count(); idx++ )
//STRIP001  {
//STRIP001      const SwTxtAttr* pHnt = (*pHints) [ idx ];
//STRIP001      if( pHnt->Which() == RES_CHRATR_CHARSETCOLOR )
//STRIP001      {
//STRIP001          if( pHnt->GetCharSetColor().GetCharSet() != eDfltEnc )
//STRIP001          {
//STRIP001              rEnc = pHnt->GetCharSetColor().GetCharSet();
//STRIP001              start = *pHnt->GetStart();
//STRIP001              end   = *pHnt->GetEnd() - 1;
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return idx;
//STRIP001 }
// Text Node konvertieren
// Wird aufgerufen, wenn sich die Systeme unterscheiden. Der Text wird
// vom einen in den anderen Zeichensatz konvertiert. Nicht konvertierbare
// Zeichen werden farblich unterlegt; Hints mit CHARSET_SYMBOL-Zeichensaetzen
// werden uebersprungen

//STRIP001 void SwSwgReader::ConvertText( SwTxtNode& rNd, rtl_TextEncoding eSrc )
//STRIP001 {
//STRIP001  const ByteString* pText = GetReadTxt();
//STRIP001  xub_StrLen nLength;
//STRIP001  if( !pText || 0 == ( nLength = pText->Len() ) )
//STRIP001      return;
//STRIP001
//STRIP001  // Variablen fuer das Hint-Array
//STRIP001  USHORT hntidx = 0;
//STRIP001  xub_StrLen symfrom = (xub_StrLen)-1, symto = 0;
//STRIP001  SwpHints* pHints = rNd.GetpSwpHints();
//STRIP001  USHORT hntsiz = pHints ? pHints->Count() : 0;
//STRIP001  String& rNdText = (String &)rNd.GetTxt();
//STRIP001
//STRIP001  const SvxFontItem& rFont = rNd.GetSwAttrSet().GetFont();
//STRIP001  BOOL bNdSym = rFont.GetCharSet() == RTL_TEXTENCODING_SYMBOL;
//STRIP001
//STRIP001  // Step 1: Replace all characters that are symbol font.
//STRIP001  hntidx = GetNextSymbolFontHint( pHints, hntidx, symfrom, symto );
//STRIP001  for( xub_StrLen pos = 0; pos < nLength; pos++ )
//STRIP001  {
//STRIP001      sal_Unicode cNew = 0;
//STRIP001      // Eventuell neuen Font-Hint suchen
//STRIP001      if( symfrom != (xub_StrLen)-1 && symto < pos )
//STRIP001      {
//STRIP001          symfrom = (xub_StrLen)-1;
//STRIP001          hntidx = GetNextSymbolFontHint( pHints, hntidx, symfrom, symto );
//STRIP001      }
//STRIP001      sal_Char ch = pText->GetChar( pos );
//STRIP001      // Darf das Zeichen konvertiert werden?
//STRIP001      if( '\xff' == ch )
//STRIP001      {
//STRIP001          // Sonderzeichen: liegt dort ein Hint ohne Ende-Index?
//STRIP001          for( USHORT i = 0; i < hntsiz; ++i )
//STRIP001          {
//STRIP001              const SwTxtAttr *pPos = (*pHints)[ i ];
//STRIP001              const xub_StrLen nStart = *pPos->GetStart();
//STRIP001              if( pos == nStart && !pPos->GetEnd() )
//STRIP001              {
//STRIP001                  // Wenn ja, dann darf ch nicht konvertiert werden!
//STRIP001                  ch = 0;
//STRIP001                  cNew = GetCharOfTxtAttr( *pPos );
//STRIP001                  break;
//STRIP001              }
//STRIP001              if( nStart > pos ) break;
//STRIP001          }
//STRIP001      }
//STRIP001      if( ch == '\t' || ch == '\n' ) ch = 0;
//STRIP001      // Testen, ob man sich im verbotenen Bereich befindet:
//STRIP001      if( ch )
//STRIP001      {
//STRIP001          if( bNdSym || (symfrom != (xub_StrLen)-1 &&
//STRIP001                         pos >= symfrom && pos < symto) )
//STRIP001          {
//STRIP001              // TODO: unicode: What happens with symbol characters?
//STRIP001 //               cNew = String::ConvertToUnicode( ch, eSrc );
//STRIP001              cNew = (sal_Unicode)ch;
//STRIP001          }
//STRIP001      }
//STRIP001      if( cNew )
//STRIP001          rNdText.SetChar( pos, cNew );
//STRIP001  }
//STRIP001
//STRIP001  // Step 2: Replace all characters that have a charset color attribute set
//STRIP001  rtl_TextEncoding eEnc = eSrc;
//STRIP001  hntidx = GetNextCharsetColorHint( pHints, hntidx, symfrom, symto,
//STRIP001                                    eSrc, eEnc);
//STRIP001
//STRIP001  for( pos = 0; pos < nLength; pos++ )
//STRIP001  {
//STRIP001      // Eventuell neuen Font-Hint suchen
//STRIP001      if( symfrom != (xub_StrLen)-1 && symto < pos )
//STRIP001      {
//STRIP001          symfrom = (xub_StrLen)-1;
//STRIP001          hntidx = GetNextCharsetColorHint( pHints, hntidx, symfrom, symto,
//STRIP001                                            eSrc, eEnc );
//STRIP001      }
//STRIP001      sal_Char ch = pText->GetChar( pos );
//STRIP001      // Darf das Zeichen konvertiert werden?
//STRIP001      if( '\xff' == ch )
//STRIP001      {
//STRIP001          // Sonderzeichen: liegt dort ein Hint ohne Ende-Index?
//STRIP001          for( USHORT i = 0; i < hntsiz; ++i )
//STRIP001          {
//STRIP001              const SwTxtAttr *pPos = (*pHints)[ i ];
//STRIP001              const xub_StrLen nStart = *pPos->GetStart();
//STRIP001              if( pos == nStart && !pPos->GetEnd() )
//STRIP001              {
//STRIP001                  // Wenn ja, dann darf ch nicht konvertiert werden!
//STRIP001                  ch = 0;
//STRIP001                  break;
//STRIP001              }
//STRIP001              if( nStart > pos ) break;
//STRIP001          }
//STRIP001      }
//STRIP001      if( ch == '\t' || ch == '\n' ) ch = 0;
//STRIP001      // Testen, ob man sich im verbotenen Bereich befindet:
//STRIP001      if( ch && (symfrom != (xub_StrLen)-1 &&
//STRIP001                 pos >= symfrom && pos < symto) )
//STRIP001      {
//STRIP001          sal_Unicode cNew = ByteString::ConvertToUnicode( ch, eEnc );
//STRIP001          if( cNew )
//STRIP001              rNdText.SetChar( pos, cNew );
//STRIP001      }
//STRIP001  }
//STRIP001 }

// Attributsack mit einem anderen Sack fuellen. Dies ist der Fall,
// wenn auf Autoformate eines anderen Nodes Bezug genommen wird.

//STRIP001 void SwSwgReader::SetAttrSet( SwCntntNode& rNd, USHORT nIdx )
//STRIP001 {
//STRIP001  if( !rNd.GetpSwAttrSet() )
//STRIP001      rNd.NewAttrSet( pDoc->GetAttrPool() );
//STRIP001  FillAttrSet( *rNd.GetpSwAttrSet(), nIdx );
//STRIP001 }

// all textattributes can ask for here textcharacter. But in the node is the
// converted text, were they don't found the right characters. So they need
// a access to the original text, which will be done by this class. The read
// can be called recursiv!!
//STRIP001 class _SetOrigTextAtReader
//STRIP001 {
//STRIP001  ByteString sReadTxt;
//STRIP001  const ByteString* pOldTxt;
//STRIP001  SwSwgReader& rRdr;
//STRIP001
//STRIP001 public:
//STRIP001  _SetOrigTextAtReader( SwSwgReader& rR, xub_StrLen nOffset )
//STRIP001      : rRdr( rR )
//STRIP001  {
//STRIP001      if( nOffset )
//STRIP001          sReadTxt.Expand( nOffset );
//STRIP001      pOldTxt = rRdr.GetReadTxt();
//STRIP001      rRdr.SetReadTxt( &sReadTxt );
//STRIP001  }
//STRIP001
//STRIP001  ~_SetOrigTextAtReader()
//STRIP001  {
//STRIP001      rRdr.SetReadTxt( pOldTxt );
//STRIP001  }
//STRIP001
//STRIP001  void AppendText( const ByteString& rTxt )   { sReadTxt += rTxt; }
//STRIP001  const ByteString& GetReadText() const       { return sReadTxt; }
//STRIP001 };


// Text Node einlesen
// Falls kein Node angegeben ist, wird ein neuer Node an der angegebenen
// Position erzeugt.
//STRIP001 void lcl_sw3io__ConvertNumTabStop( SwTxtNode& rTxtNd, long nOffset,
//STRIP001                                 BOOL bDeep );
//STRIP001 void SwSwgReader::FillTxtNode( SwTxtNode* pNd, SwNodeIndex& rPos,
//STRIP001                             xub_StrLen nOffset, USHORT nInsFirstPara )
//STRIP001 {
//STRIP001  long nextrec = r.getskip();
//STRIP001
//STRIP001  // Flags-Aufbau:
//STRIP001  // Bit 0x01 - hat Collection-Wert
//STRIP001  // Bit 0x02 - hat eigenes Frameformat
//STRIP001  // Bit 0x04 - hat eigenes Zeichenformat
//STRIP001  // Bit 0x08 - hat eigenes Absatzformat
//STRIP001  // Bit 0x10 - hat Numerierung
//STRIP001
//STRIP001  BYTE cFlags = 0, cNumLevel = NO_NUMBERING;
//STRIP001  USHORT nNumRule = IDX_NO_VALUE;
//STRIP001  USHORT nColl     = 0,
//STRIP001         nAutoFrm  = IDX_NO_VALUE,
//STRIP001         nAutoChar = IDX_NO_VALUE,
//STRIP001         nAutoPara = IDX_NO_VALUE;
//STRIP001
//STRIP001  r >> cFlags;
//STRIP001  if( cFlags & 0x01 ) r >> nColl;
//STRIP001  if( cFlags & 0x02 ) r >> nAutoFrm;
//STRIP001  if( cFlags & 0x04 ) r >> nAutoChar;
//STRIP001  if( cFlags & 0x08 ) r >> nAutoPara;
//STRIP001  if( cFlags & 0x10 ) r >> cNumLevel >> nNumRule;
//STRIP001
//STRIP001  // Werden nur Seitenvorlagen eingelesen, muss die Collection
//STRIP001  // immer 0 sein, da andere Coll-Idxe immer falsch sind
//STRIP001  if( ( nOptions != SWGRD_NORMAL ) && !( nOptions & SWGRD_PARAFMTS ) )
//STRIP001      nColl = 0;
//STRIP001  SwTxtFmtColl* pColl = (SwTxtFmtColl*) FindFmt( nColl | IDX_COLLECTION, 0 );
//STRIP001  if( !pColl )
//STRIP001      pColl = (SwTxtFmtColl*) FindFmt( IDX_COLLECTION + 0, 0 );
//STRIP001
//STRIP001  BOOL bDone = FALSE;
//STRIP001
//STRIP001  // Ggf. den Node neu einrichten
//STRIP001  BOOL bNewNd = FALSE;
//STRIP001  if( !pNd )
//STRIP001  {
//STRIP001      pNd = pDoc->GetNodes().MakeTxtNode( rPos, pColl );
//STRIP001      rPos--;
//STRIP001      nOffset = 0;
//STRIP001      bNewNd = TRUE;
//STRIP001  }
//STRIP001  else if( !nInsFirstPara )
//STRIP001      pNd->ChgFmtColl( pColl );
//STRIP001
//STRIP001  _SetOrigTextAtReader aOrigTxtAtReader( *this, nOffset );
//STRIP001
//STRIP001  SwAttrSet aTmpSet( pDoc->GetAttrPool(), RES_CHRATR_BEGIN, RES_CHRATR_END - 1 );
//STRIP001
//STRIP001  r.next();
//STRIP001  while( !bDone && ( r.tell() < nextrec ) ) switch( r.cur() )
//STRIP001  {
//STRIP001      case SWG_COMMENT:
//STRIP001          if( r.tell() >= nextrec )
//STRIP001              bDone = TRUE;
//STRIP001          else
//STRIP001              r.skipnext();
//STRIP001          break;
//STRIP001      case SWG_FRAMEFMT:
//STRIP001          if( nInsFirstPara )
//STRIP001          {
//STRIP001              r.skipnext();
//STRIP001              nAutoFrm = IDX_NO_VALUE;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              if( InAttrSet( *pNd ) == nAutoFrm ) nAutoFrm = IDX_NO_VALUE;
//STRIP001              // Wurde ein PageDesc-Attr gelesen? Dann das AttrSet des Nodes
//STRIP001              // im PageDescLink noch nachtragen!
//STRIP001              if( pPageLinks && !pPageLinks->pSet )
//STRIP001              {
//STRIP001                  pPageLinks->pSet = pNd->GetpSwAttrSet();
//STRIP001                  pPageLinks->cFmt = FALSE;
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001      case SWG_CHARFMT:
//STRIP001          if( nInsFirstPara )
//STRIP001          {
//STRIP001              if( InAttrSet( aTmpSet ) == nAutoChar )
//STRIP001                  nAutoChar = IDX_NO_VALUE;
//STRIP001          }
//STRIP001          else if( InAttrSet( *pNd ) == nAutoChar )
//STRIP001              nAutoChar = IDX_NO_VALUE;
//STRIP001          break;
//STRIP001      case SWG_PARAFMT:
//STRIP001          if( nInsFirstPara )
//STRIP001          {
//STRIP001              r.skipnext();
//STRIP001              nAutoPara = IDX_NO_VALUE;
//STRIP001          }
//STRIP001          else
//STRIP001              if( InAttrSet( *pNd ) == nAutoPara ) nAutoPara = IDX_NO_VALUE;
//STRIP001          break;
//STRIP001      case SWG_TEXT:
//STRIP001          {
//STRIP001              ByteString aTxt( r.text() );    // Hier nicht konvertieren!
//STRIP001              aOrigTxtAtReader.AppendText( aTxt );
//STRIP001              // The conversion that takes place may lead to wrong results.
//STRIP001              // This will be fixed in ConvertText.
//STRIP001              String aText( aTxt, aHdr.cCodeSet );
//STRIP001              r.next();
//STRIP001              if( bNewNd )
//STRIP001                  (String&) pNd->GetTxt() = aText;
//STRIP001              else {
//STRIP001                  SwIndex aOff( pNd, nOffset );
//STRIP001                  pNd->Insert( aText, aOff );
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001      case SWG_TEXTHINTS:
//STRIP001          InTextHints( *pNd, nOffset );
//STRIP001          break;
//STRIP001      case SWG_FLYFMT:
//STRIP001          InFlyFrame( &rPos );
//STRIP001          break;
//STRIP001      case SWG_BOOKMARK:
//STRIP001          if( !( nStatus & SWGSTAT_NO_BOOKMARKS ) )
//STRIP001              InNodeBookmark( rPos );
//STRIP001          else
//STRIP001              r.skipnext();
//STRIP001          break;
//STRIP001      case SWG_OUTLINE:
//STRIP001          // alter Numerierungs-Record, jetzt nicht mehr da!
//STRIP001          r.skipnext();
//STRIP001          break;
//STRIP001      default:
//STRIP001          bDone = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  if( aTmpSet.Count() )
//STRIP001  {
//STRIP001      if( 2 == nInsFirstPara )
//STRIP001          pNd->SetAttr( aTmpSet, 0, GetReadTxt()->Len() - nOffset );
//STRIP001      else
//STRIP001          pNd->SetAttr( aTmpSet, nOffset, pNd->GetTxt().Len() );
//STRIP001  }
//STRIP001
//STRIP001  // Wird noch auf Autoformate Bezug genommen?
//STRIP001  if( nAutoFrm != IDX_NO_VALUE )
//STRIP001      SetAttrSet( *pNd, nAutoFrm );
//STRIP001  if( nAutoChar != IDX_NO_VALUE )
//STRIP001      SetAttrSet( *pNd, nAutoChar );
//STRIP001  if( nAutoPara != IDX_NO_VALUE )
//STRIP001      SetAttrSet( *pNd, nAutoPara );
//STRIP001
//STRIP001  // Numerierung uebernehmen
//STRIP001  if( cNumLevel != NO_NUMBERING )
//STRIP001  {
//STRIP001      if( nNumRule != IDX_NO_VALUE )
//STRIP001          UpdateRuleRange( nNumRule, pNd );
//STRIP001      pNd->UpdateNum( SwNodeNum( cNumLevel ));
//STRIP001  }
//STRIP001 #ifdef NUM_RELSPACE
//STRIP001  else if( pNd->GetpSwAttrSet() &&
//STRIP001      NO_NUMBERING != pColl->GetOutlineLevel() &&
//STRIP001      pDoc->GetOutlineNumRule() )
//STRIP001  {
//STRIP001      const SwNumRule *pOutline = pDoc->GetOutlineNumRule();
//STRIP001      const SfxPoolItem *pItem;
//STRIP001
//STRIP001      const SwNumFmt& rNumFmt = pOutline->Get(
//STRIP001              GetRealLevel(((const SwTxtFmtColl*)pColl)->GetOutlineLevel()) );
//STRIP001      USHORT nNumLSpace = rNumFmt.GetAbsLSpace();
//STRIP001
//STRIP001      if( SFX_ITEM_SET == pNd->GetpSwAttrSet()->GetItemState( RES_LR_SPACE,
//STRIP001                                                            FALSE,
//STRIP001                                                            &pItem ) )
//STRIP001      {
//STRIP001          const SvxLRSpaceItem *pParaLRSpace =
//STRIP001              (const SvxLRSpaceItem *)pItem;
//STRIP001
//STRIP001          USHORT nWishLSpace = pParaLRSpace->GetTxtLeft();
//STRIP001          USHORT nNewLSpace =
//STRIP001                      nWishLSpace > nNumLSpace ? nWishLSpace-nNumLSpace : 0U;
//STRIP001
//STRIP001          const SvxLRSpaceItem& rCollLRSpace = pColl->GetLRSpace();
//STRIP001          if( nNewLSpace == rCollLRSpace.GetTxtLeft() &&
//STRIP001              pParaLRSpace->GetRight() == rCollLRSpace.GetRight() &&
//STRIP001              pParaLRSpace->GetTxtFirstLineOfst() ==
//STRIP001                                          rCollLRSpace.GetTxtFirstLineOfst() )
//STRIP001          {
//STRIP001              pNd->ResetAttr( RES_LR_SPACE );
//STRIP001          }
//STRIP001          else if( nNewLSpace != pParaLRSpace->GetTxtLeft() )
//STRIP001          {
//STRIP001              SvxLRSpaceItem aLRSpace( *pParaLRSpace );
//STRIP001              short nFirst = aLRSpace.GetTxtFirstLineOfst();
//STRIP001              if( nFirst < 0 && (USHORT)-nFirst > nNewLSpace )
//STRIP001                  aLRSpace.SetTxtFirstLineOfst( -(short)nNewLSpace );
//STRIP001              aLRSpace.SetTxtLeft( nNewLSpace );
//STRIP001              ((SwCntntNode *)pNd)->SetAttr( aLRSpace );
//STRIP001          }
//STRIP001
//STRIP001          if( nWishLSpace != nNewLSpace )
//STRIP001              lcl_sw3io__ConvertNumTabStop( *pNd, (long)nWishLSpace -
//STRIP001                                                  (long)nNewLSpace, FALSE );
//STRIP001      }
//STRIP001      else if( nNumLSpace > 0 )
//STRIP001      {
//STRIP001          lcl_sw3io__ConvertNumTabStop( *pNd, nNumLSpace, FALSE   );
//STRIP001      }
//STRIP001  }
//STRIP001 #endif
//STRIP001
//STRIP001  // Eventuell den Text konvertieren
//STRIP001  ConvertText( *pNd, (rtl_TextEncoding)aHdr.cCodeSet );
//STRIP001  rPos++;
//STRIP001 }

// Einlesen des puren Textes eines TextNodes. Der Text wird an den vorhandenen
// Text im String angefuegt.

//STRIP001 void SwSwgReader::FillString( String& rText )
//STRIP001 {
//STRIP001  // Flags-Aufbau:
//STRIP001  // Bit 0x01 - hat Collection-Wert
//STRIP001  // Bit 0x02 - hat eigenes Frameformat
//STRIP001  // Bit 0x04 - hat eigenes Zeichenformat
//STRIP001  // Bit 0x08 - hat eigenes Absatzformat
//STRIP001  // Bit 0x10 - hat Numerierung
//STRIP001
//STRIP001  BYTE cFlags = 0;
//STRIP001  USHORT nDummyBytes = 0;
//STRIP001  String aTxt;
//STRIP001  long nextrec = r.getskip();
//STRIP001
//STRIP001  r >> cFlags;
//STRIP001  if( cFlags & 0x01 ) nDummyBytes += 2;
//STRIP001  if( cFlags & 0x02 ) nDummyBytes += 2;
//STRIP001  if( cFlags & 0x04 ) nDummyBytes += 2;
//STRIP001  if( cFlags & 0x08 ) nDummyBytes += 2;
//STRIP001  if( cFlags & 0x10 ) nDummyBytes += 3;
//STRIP001
//STRIP001  BOOL bDone = FALSE;
//STRIP001  r.seek( r.tell() + nDummyBytes );
//STRIP001  r.next();
//STRIP001  while( !bDone ) switch( r.cur() )
//STRIP001  {
//STRIP001      case SWG_PARAFMT:
//STRIP001      case SWG_CHARFMT:
//STRIP001      case SWG_FRAMEFMT:
//STRIP001      case SWG_TEXTHINTS:
//STRIP001      case SWG_FLYFMT:
//STRIP001      case SWG_BOOKMARK:
//STRIP001      case SWG_OUTLINE:
//STRIP001          r.skipnext(); break;
//STRIP001      case SWG_COMMENT:
//STRIP001          if( r.tell() >= nextrec ) bDone = TRUE;
//STRIP001          else r.skipnext(); break;
//STRIP001      case SWG_TEXT:
//STRIP001          aTxt = ParseText();
//STRIP001          if( rText.Len() ) rText += ' ';
//STRIP001          rText += aTxt;
//STRIP001          r.next();
//STRIP001          break;
//STRIP001      default:
//STRIP001          bDone = TRUE;
//STRIP001  }
//STRIP001 }

// Die Formate von Grafik- und OLE-Nodes muessen nicht registriert
// werden; die Layout-Frames erhalten ja eine Node-Referenz.

//STRIP001 void SwSwgReader::InGrfNode( SwNodeIndex& rPos )
//STRIP001 {
//STRIP001  Graphic aGrf;
//STRIP001  Graphic* pGrf = &aGrf;
//STRIP001  String aGrfName, aFltName;
//STRIP001  USHORT nFrmFmt = IDX_NO_VALUE;
//STRIP001  USHORT nGrfFmt = IDX_NO_VALUE;
//STRIP001  long nextrec = r.getskip();
//STRIP001
//STRIP001  r >> nFrmFmt >> nGrfFmt;
//STRIP001  r.next();
//STRIP001  BOOL bLink = FALSE;
//STRIP001  BOOL bDone = FALSE;
//STRIP001  SwAttrSet aSet( pDoc->GetAttrPool(), RES_CHRATR_BEGIN, RES_GRFATR_END );
//STRIP001  while( !bDone ) switch( r.cur() )
//STRIP001  {
//STRIP001      case SWG_FRAMEFMT:
//STRIP001      case SWG_GRFFMT:
//STRIP001          InAttrSet( aSet );
//STRIP001          break;
//STRIP001      case SWG_GRAPHIC: {
//STRIP001          long pos = r.getskip();
//STRIP001          aGrfName = GetText();
//STRIP001          aFltName = GetText();
//STRIP001          if( !aGrfName.Len() )
//STRIP001          {
//STRIP001              long nPos = r.tell();
//STRIP001              if( nPos < pos )
//STRIP001              {
//STRIP001                  // Immer sofort einlesen (kann spaeter rausgeswapt werden)
//STRIP001                  if( aHdr.nVersion >= SWG_VER_PORTGRF )
//STRIP001                      aGrf.ReadEmbedded( r.Strm(), FALSE );
//STRIP001                  else
//STRIP001                      r.Strm() >> aGrf;
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              pGrf = NULL, bLink = TRUE;
//STRIP001              aGrfName = URIHelper::SmartRelToAbs( aGrfName );
//STRIP001          }
//STRIP001          r.skip( pos );
//STRIP001          r.next();
//STRIP001          if( r.good() ) break;
//STRIP001          }
//STRIP001      case SWG_COMMENT:
//STRIP001      case SWG_DATA:
//STRIP001          if( r.tell() >= nextrec ) bDone = TRUE;
//STRIP001          else r.skipnext(); break;
//STRIP001      default:
//STRIP001          bDone = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  if( r.good() )
//STRIP001      pDoc->GetNodes().MakeGrfNode( rPos,
//STRIP001                                aGrfName, aFltName, pGrf,
//STRIP001                                (SwGrfFmtColl*) pDoc->GetDfltGrfFmtColl(),
//STRIP001                                &aSet, bLink );
//STRIP001  else
//STRIP001      Error( ERR_SWG_READ_ERROR );
//STRIP001
//STRIP001 }

// OLE-Node:

//STRIP001 void SwSwgReader::InOleNode( SwNodeIndex& rPos )
//STRIP001 {
//STRIP001  USHORT nFrmFmt = IDX_NO_VALUE;
//STRIP001  USHORT nGrfFmt = IDX_NO_VALUE;
//STRIP001  long nextrec = r.getskip();
//STRIP001
//STRIP001  r >> nFrmFmt >> nGrfFmt;
//STRIP001  r.next();
//STRIP001  SwAttrSet aSet( pDoc->GetAttrPool(), RES_CHRATR_BEGIN, RES_GRFATR_END );
//STRIP001  String aObjName;
//STRIP001  BOOL bDone = FALSE;
//STRIP001  while( !bDone ) switch( r.cur() )
//STRIP001  {
//STRIP001      case SWG_FRAMEFMT:
//STRIP001      case SWG_GRFFMT:
//STRIP001          InAttrSet( aSet );
//STRIP001          break;
//STRIP001      case SWG_OLE:
//STRIP001      {
//STRIP001          SvStorage* pStg = pDoc->GetPersist()->GetStorage();
//STRIP001          aObjName = Sw3Io::UniqueName( pStg, "StarObj" );
//STRIP001          ULONG nStart = r.Strm().Tell();
//STRIP001          if( !SvEmbeddedObject::InsertStarObject
//STRIP001              ( aObjName, aObjName, r.Strm(), pDoc->GetPersist() ) )
//STRIP001          {
//STRIP001              // Vielleicht geht es ja als Grafik...
//STRIP001              GDIMetaFile aMtf;
//STRIP001              r.Strm().Seek( nStart );
//STRIP001              if( SvEmbeddedObject::LoadStarObjectPicture( r.Strm(), aMtf ) )
//STRIP001              {
//STRIP001                  r.Strm().ResetError();
//STRIP001                  aObjName.Erase();
//STRIP001                  Graphic aGrf( aMtf );
//STRIP001                  pDoc->GetNodes().MakeGrfNode( rPos,
//STRIP001                               aObjName, aObjName, &aGrf,
//STRIP001                               (SwGrfFmtColl*) pDoc->GetDfltGrfFmtColl(),
//STRIP001                               &aSet, FALSE );
//STRIP001                  nErrno = WARN_SWG_OLE | WARN_SW_READ_BASE;
//STRIP001                  return;
//STRIP001              }
//STRIP001              else
//STRIP001                  Error( ERR_SWG_READ_ERROR );
//STRIP001          }
//STRIP001          r.skipnext(); break;
//STRIP001      }
//STRIP001      case SWG_COMMENT:
//STRIP001      case SWG_DATA:
//STRIP001          if( r.tell() >= nextrec ) bDone = TRUE;
//STRIP001          else r.skipnext(); break;
//STRIP001      default:
//STRIP001          bDone = TRUE;
//STRIP001  }
//STRIP001  if ( !r )
//STRIP001  {
//STRIP001      Error( ERR_SWG_READ_ERROR );
//STRIP001  }
//STRIP001  else
//STRIP001      pDoc->GetNodes().MakeOLENode( rPos, aObjName,
//STRIP001                      (SwGrfFmtColl*) pDoc->GetDfltGrfFmtColl(),
//STRIP001                      &aSet );
//STRIP001 }



}
