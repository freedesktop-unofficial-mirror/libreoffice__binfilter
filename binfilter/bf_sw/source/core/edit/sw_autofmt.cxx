/*************************************************************************
 *
 *  $RCSfile: sw_autofmt.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:19:22 $
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

#define ITEMID_BOXINFO      SID_ATTR_BORDER_INNER
#define _SVSTDARR_LONGS
#define _SVSTDARR_USHORTS

#include <ctype.h>
#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

// auto strip #include <svtools/svstdarr.hxx>
// auto strip #ifndef _UNOTOOLS_CHARCLASS_HXX
// auto strip #include <unotools/charclass.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_BOXITEM_HXX //autogen
// auto strip #include <bf_svx/boxitem.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_LRSPITEM_HXX //autogen
// auto strip #include <bf_svx/lrspitem.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_BRKITEM_HXX //autogen
// auto strip #include <bf_svx/brkitem.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_ADJITEM_HXX //autogen
// auto strip #include <bf_svx/adjitem.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_TSTPITEM_HXX //autogen
// auto strip #include <bf_svx/tstpitem.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_FONTITEM_HXX //autogen
// auto strip #include <bf_svx/fontitem.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_LANGITEM_HXX //autogen
// auto strip #include <bf_svx/langitem.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_CSCOITEM_HXX
// auto strip #include <bf_svx/cscoitem.hxx>
// auto strip #endif
// auto strip #ifndef _UNO_LINGU_HXX
// auto strip #include <bf_svx/unolingu.hxx>
// auto strip #endif
// auto strip #ifndef _OFF_APP_HXX //autogen
// auto strip #include <bf_offmgr/app.hxx>
// auto strip #endif

// auto strip #ifndef _SWWAIT_HXX
// auto strip #include <swwait.hxx>
// auto strip #endif
// auto strip #ifndef _FMTPDSC_HXX //autogen
// auto strip #include <fmtpdsc.hxx>
// auto strip #endif
// auto strip #ifndef _FMTANCHR_HXX //autogen
// auto strip #include <fmtanchr.hxx>
// auto strip #endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

// auto strip #ifndef _DOC_HXX
// auto strip #include <doc.hxx>
// auto strip #endif
// auto strip #ifndef _DOCARY_HXX
// auto strip #include <docary.hxx>
// auto strip #endif
#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif
// auto strip #ifndef _INDEX_HXX
// auto strip #include <index.hxx>
// auto strip #endif
// auto strip #ifndef _PAM_HXX
// auto strip #include <pam.hxx>
// auto strip #endif
// auto strip #ifndef _EDIMP_HXX
// auto strip #include <edimp.hxx>
// auto strip #endif
// auto strip #ifndef _FESH_HXX
// auto strip #include <fesh.hxx>
// auto strip #endif
// auto strip #ifndef _SWUNDO_HXX
// auto strip #include <swundo.hxx>     // fuer die UndoIds
// auto strip #endif
// auto strip #ifndef _POOLFMT_HXX
// auto strip #include <poolfmt.hxx>
// auto strip #endif
// auto strip #ifndef _NDTXT_HXX
// auto strip #include <ndtxt.hxx>
// auto strip #endif
// auto strip #ifndef _TXTFRM_HXX
// auto strip #include <txtfrm.hxx>
// auto strip #endif
// auto strip #ifndef _FRMINF_HXX
// auto strip #include <frminf.hxx>
// auto strip #endif
// auto strip #ifndef _PAGEDESC_HXX
// auto strip #include <pagedesc.hxx>
// auto strip #endif
// auto strip #ifndef _PARATR_HXX
// auto strip #include <paratr.hxx>
// auto strip #endif
// auto strip #ifndef _SWTABLE_HXX
// auto strip #include <swtable.hxx>
// auto strip #endif
// auto strip #ifndef _ACORRECT_HXX
// auto strip #include <acorrect.hxx>
// auto strip #endif
// auto strip #ifndef _SHELLRES_HXX
// auto strip #include <shellres.hxx>
// auto strip #endif
// auto strip #ifndef _ITABENUM_HXX
// auto strip #include <itabenum.hxx>
// auto strip #endif
// auto strip #ifndef _SECTION_HXX //autogen
// auto strip #include <section.hxx>
// auto strip #endif
// auto strip #ifndef _FMTHBSH_HXX //autogen
// auto strip #include <fmthbsh.hxx>
// auto strip #endif
// auto strip #ifndef _FRMATR_HXX
// auto strip #include <frmatr.hxx>
// auto strip #endif
// auto strip #ifndef _CHARATR_HXX
// auto strip #include <charatr.hxx>
// auto strip #endif

// auto strip #ifndef _MDIEXP_HXX
// auto strip #include <mdiexp.hxx>
// auto strip #endif
#ifndef _STATSTR_HRC
#include <statstr.hrc>
#endif
#ifndef _COMCORE_HRC
#include <comcore.hrc>
#endif

// auto strip #ifndef _SV_MSGBOX_HXX
// auto strip #include <vcl/msgbox.hxx>
// auto strip #endif
namespace binfilter {

//-------------------------------------------------------------------

//JP 16.12.99: definition:
//      from pos cPosEnDash to cPosEmDash all chars changed to endashes,
//      from pos cPosEmDash to cPosEnd    all chars changed to emdashes
//      all other chars are changed to the user configuration

//STRIP001 const sal_Unicode pBulletChar[6] = { '+', '*', '-', 0x2013, 0x2014, 0 };
//STRIP001 const int cnPosEnDash = 2, cnPosEmDash = 4, cnPosEnd = 5;

//STRIP001 const sal_Unicode cStarSymbolEnDash = 0x2013;
//STRIP001 const sal_Unicode cStarSymbolEmDash = 0x2014;


/*N*/ SvxSwAutoFmtFlags* SwEditShell::pAutoFmtFlags = 0;

// Anzahl von Num-/Bullet-Absatzvorlagen. MAXLEVEL wird demnaechst auf
// x erhoeht, die Anzahl Vorlagen aber nicht (Ueberbleibsel aus <= 4.0)
//STRIP001 const USHORT cnNumBullColls = 4;

//STRIP001 class SwAutoFormat
//STRIP001 {
//STRIP001  SvxSwAutoFmtFlags aFlags;
//STRIP001  SwPaM aDelPam;              // ein Pam der benutzt werden kann
//STRIP001  SwNodeIndex aNdIdx;         // der Index auf den akt. TextNode
//STRIP001  SwNodeIndex aEndNdIdx;      // Index auf das Ende vom Bereich
//STRIP001
//STRIP001  SwEditShell* pEditShell;
//STRIP001  SwDoc* pDoc;
//STRIP001  SwTxtNode* pAktTxtNd;       // der akt. TextNode
//STRIP001  SwTxtFrm* pAktTxtFrm;       // Frame vom akt. TextNode
//STRIP001  CharClass* pCharClass;      // Character classification
//STRIP001  ULONG nEndNdIdx;            // fuer die Prozent-Anzeige
//STRIP001  LanguageType eCharClassLang;
//STRIP001
//STRIP001  USHORT nLastHeadLvl, nLastCalcHeadLvl;
//STRIP001  USHORT nLastEnumLvl, nLastCalcEnumLvl;
//STRIP001  USHORT nRedlAutoFmtSeqId;
//STRIP001
//STRIP001  enum
//STRIP001  {
//STRIP001      NONE = 0,
//STRIP001      DELIM = 1,
//STRIP001      DIGIT = 2,
//STRIP001      CHG = 4,
//STRIP001      LOWER_ALPHA = 8,
//STRIP001      UPPER_ALPHA = 16,
//STRIP001      LOWER_ROMAN = 32,
//STRIP001      UPPER_ROMAN = 64,
//STRIP001      NO_DELIM = (DIGIT|LOWER_ALPHA|UPPER_ALPHA|LOWER_ROMAN|UPPER_ROMAN)
//STRIP001  };
//STRIP001
//STRIP001  enum Format_Status
//STRIP001  {
//STRIP001      READ_NEXT_PARA,
//STRIP001      TST_EMPTY_LINE,
//STRIP001      TST_ALPHA_LINE,
//STRIP001      GET_ALL_INFO,
//STRIP001      IS_ONE_LINE,
//STRIP001      TST_ENUMERIC,
//STRIP001      TST_IDENT,
//STRIP001      TST_NEG_IDENT,
//STRIP001      TST_TXT_BODY,
//STRIP001      HAS_FMTCOLL,
//STRIP001      IS_ENDE
//STRIP001  } eStat;
//STRIP001
//STRIP001  BOOL bEnde : 1;
//STRIP001  BOOL bEmptyLine : 1;
//STRIP001  BOOL bMoreLines : 1;
//STRIP001
    static BOOL  m_bAskForCancelUndoWhileBufferOverflow;
    static short m_nActionWhileAutoformatUndoBufferOverflow;


//STRIP001  // ------------- private methods -----------------------------
//STRIP001  void _GetCharClass( LanguageType eLang );
//STRIP001  CharClass& GetCharClass( LanguageType eLang ) const
//STRIP001  {
//STRIP001      if( !pCharClass || eLang != eCharClassLang )
//STRIP001      {
//STRIP001          SwAutoFormat* pThis = (SwAutoFormat*)this;
//STRIP001          pThis->_GetCharClass( eLang );
//STRIP001      }
//STRIP001      return *pCharClass;
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001  BOOL IsSpace( const sal_Unicode c ) const
//STRIP001      { return (' ' == c || '\t' == c || 0x0a == c) ? TRUE : FALSE; }
//STRIP001
//STRIP001  void SetColl( USHORT nId, BOOL bHdLineOrText = FALSE );
//STRIP001  String GoNextPara();
//STRIP001  BOOL HasObjects( const SwNode& rNd );
//STRIP001
//STRIP001  // TxtNode Methoden
//STRIP001  const SwTxtNode* GetNextNode() const;
//STRIP001  BOOL IsEmptyLine( const SwTxtNode& rNd ) const
//STRIP001      {   return 0 == rNd.GetTxt().Len() ||
//STRIP001              rNd.GetTxt().Len() == GetLeadingBlanks( rNd.GetTxt() ); }
//STRIP001
//STRIP001  BOOL IsOneLine( const SwTxtNode& ) const;
//STRIP001  BOOL IsFastFullLine( const SwTxtNode& ) const;
//STRIP001  BOOL IsNoAlphaLine( const SwTxtNode&) const;
//STRIP001  BOOL IsEnumericChar( const SwTxtNode&) const;
//STRIP001  BOOL IsBlanksInString( const SwTxtNode&) const;
//STRIP001  USHORT CalcLevel( const SwTxtNode&, USHORT *pDigitLvl = 0 ) const;
//STRIP001  xub_StrLen GetBigIndent( xub_StrLen& rAktSpacePos ) const;
//STRIP001
//STRIP001  String& DelLeadingBlanks( String& rStr ) const;
//STRIP001  String& DelTrailingBlanks( String& rStr ) const;
//STRIP001  xub_StrLen GetLeadingBlanks( const String& rStr ) const;
//STRIP001  xub_StrLen GetTrailingBlanks( const String& rStr ) const;
//STRIP001
//STRIP001  BOOL IsFirstCharCapital( const SwTxtNode& rNd ) const;
//STRIP001  USHORT GetDigitLevel( const SwTxtNode& rTxtNd, xub_StrLen& rPos,
//STRIP001                          String* pPreFix = 0, String* pPostFix = 0,
//STRIP001                          String* pNumTypes = 0 ) const;
//STRIP001      // hole den FORMATIERTEN TextFrame
//STRIP001  SwTxtFrm* GetFrm( const SwTxtNode& rTxtNd ) const;
//STRIP001
//STRIP001  void BuildIndent();
//STRIP001  void BuildText();
//STRIP001  void BuildTextIndent();
//STRIP001  void BuildEnum( USHORT nLvl, USHORT nDigitLevel );
//STRIP001  void BuildNegIndent( SwTwips nSpaces );
//STRIP001  void BuildHeadLine( USHORT nLvl );
//STRIP001
//STRIP001  BOOL HasSelBlanks( SwPaM& rPam ) const;
//STRIP001  BOOL HasBreakAttr( const SwTxtNode& ) const;
//STRIP001  void DeleteSel( SwPaM& rPam );
//STRIP001  BOOL DeleteAktNxtPara( const String& rNxtPara );
//STRIP001  // loesche im Node Anfang oder/und Ende
//STRIP001  void DeleteAktPara( BOOL bStart = TRUE, BOOL nEnd = TRUE );
//STRIP001  void DelEmptyLine( BOOL bTstNextPara = TRUE );
//STRIP001      // loesche bei mehrzeiligen Absaetzen die "linken" und/oder
//STRIP001      // "rechten" Raender
//STRIP001  void DelMoreLinesBlanks( BOOL bWithLineBreaks = FALSE );
//STRIP001      // loesche den vorherigen Absatz
//STRIP001  void DelPrevPara();
//STRIP001      // dann lasse doch mal das AutoCorrect auf den akt. TextNode los
//STRIP001  void AutoCorrect( xub_StrLen nSttPos = 0 );
//STRIP001
//STRIP001  BOOL CanJoin( const SwTxtNode* pTxtNd ) const
//STRIP001  {
//STRIP001      return !bEnde && pTxtNd &&
//STRIP001           !IsEmptyLine( *pTxtNd ) &&
//STRIP001           !IsNoAlphaLine( *pTxtNd) &&
//STRIP001           !IsEnumericChar( *pTxtNd ) &&
//STRIP001           ((STRING_MAXLEN - 50 - pTxtNd->GetTxt().Len()) >
//STRIP001                  pAktTxtNd->GetTxt().Len()) &&
//STRIP001           !HasBreakAttr( *pTxtNd );
//STRIP001  }
//STRIP001
//STRIP001  // ist ein Punkt am Ende ??
//STRIP001  BOOL IsSentenceAtEnd( const SwTxtNode& rTxtNd ) const;
//STRIP001
//STRIP001  BOOL DoUnderline();
//STRIP001  BOOL DoTable();
//STRIP001
//STRIP001  void _SetRedlineTxt( USHORT nId );
//STRIP001  BOOL SetRedlineTxt( USHORT nId )
//STRIP001      { if( aFlags.bWithRedlining )   _SetRedlineTxt( nId );  return TRUE; }
//STRIP001  BOOL ClearRedlineTxt()
//STRIP001      { if( aFlags.bWithRedlining )   pDoc->SetAutoFmtRedlineComment(0);  return TRUE; }
//STRIP001
//STRIP001 public:
//STRIP001  SwAutoFormat( SwEditShell* pEdShell, SvxSwAutoFmtFlags& rFlags,
//STRIP001              SwNodeIndex* pSttNd = 0, SwNodeIndex* pEndNd = 0 );
//STRIP001  ~SwAutoFormat() {
//STRIP001      delete pCharClass;
//STRIP001  }
//STRIP001 };

//STRIP001 BOOL  SwAutoFormat::m_bAskForCancelUndoWhileBufferOverflow     = TRUE;
//STRIP001 short SwAutoFormat::m_nActionWhileAutoformatUndoBufferOverflow = RET_YES;

//STRIP001 const sal_Unicode* StrChr( const sal_Unicode* pSrc, sal_Unicode c )
//STRIP001 {
//STRIP001  while( *pSrc && *pSrc != c )
//STRIP001      ++pSrc;
//STRIP001  return *pSrc ? pSrc : 0;
//STRIP001 }

//STRIP001 SwTxtFrm* SwAutoFormat::GetFrm( const SwTxtNode& rTxtNd ) const
//STRIP001 {
//STRIP001  // besorge mal den Frame
//STRIP001  const SwCntntFrm *pFrm = rTxtNd.GetFrm();
//STRIP001  ASSERT( pFrm, "zum Autoformat muss das Layout vorhanden sein" );
//STRIP001  if( aFlags.bAFmtByInput && !pFrm->IsValid() )
//STRIP001  {
//STRIP001      SwRect aTmpFrm( pFrm->Frm() );
//STRIP001      SwRect aTmpPrt( pFrm->Prt() );
//STRIP001      pFrm->Calc();
//STRIP001      if( pFrm->Frm() != aTmpFrm || pFrm->Prt() != aTmpPrt ||
//STRIP001          ( pFrm->IsTxtFrm() && !((SwTxtFrm*)pFrm)->Paint().IsEmpty() ) )
//STRIP001          pFrm->SetCompletePaint();
//STRIP001  }
//STRIP001  return ((SwTxtFrm*)pFrm)->GetFormatted();
//STRIP001 }

//STRIP001 void SwAutoFormat::_GetCharClass( LanguageType eLang )
//STRIP001 {
//STRIP001  delete pCharClass;
//STRIP001  pCharClass = new CharClass( SvxCreateLocale( eLang ));
//STRIP001  eCharClassLang = eLang;
//STRIP001 }

//STRIP001 void SwAutoFormat::_SetRedlineTxt( USHORT nActionId )
//STRIP001 {
//STRIP001  String sTxt;
//STRIP001  USHORT nSeqNo = 0;
//STRIP001  if( STR_AUTOFMTREDL_END > nActionId )
//STRIP001  {
//STRIP001      sTxt = *ViewShell::GetShellRes()->GetAutoFmtNameLst()[ nActionId ];
//STRIP001      switch( nActionId )
//STRIP001      {
//STRIP001      case STR_AUTOFMTREDL_SET_NUMBULET:
//STRIP001      case STR_AUTOFMTREDL_DEL_MORELINES:
//STRIP001
//STRIP001      // AutoCorrect-Actions
//STRIP001      case STR_AUTOFMTREDL_USE_REPLACE:
//STRIP001      case STR_AUTOFMTREDL_CPTL_STT_WORD:
//STRIP001      case STR_AUTOFMTREDL_CPTL_STT_SENT:
//STRIP001      case STR_AUTOFMTREDL_TYPO:
//STRIP001      case STR_AUTOFMTREDL_UNDER:
//STRIP001      case STR_AUTOFMTREDL_BOLD:
//STRIP001      case STR_AUTOFMTREDL_FRACTION:
//STRIP001      case STR_AUTOFMTREDL_DASH:
//STRIP001      case STR_AUTOFMTREDL_ORDINAL:
//STRIP001          nSeqNo = ++nRedlAutoFmtSeqId;
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001 #if OSL_DEBUG_LEVEL > 1
//STRIP001  else
//STRIP001      sTxt = String::CreateFromAscii(
//STRIP001                          RTL_CONSTASCII_STRINGPARAM( "Action-Text fehlt" ));
//STRIP001 #endif
//STRIP001
//STRIP001  pDoc->SetAutoFmtRedlineComment( &sTxt, nSeqNo );
//STRIP001 }

//STRIP001 String SwAutoFormat::GoNextPara()
//STRIP001 {
//STRIP001  SwNode* pNewNd = 0;
//STRIP001  do {
//STRIP001      //has to be checed twice before and after incrementation
//STRIP001      if( aNdIdx.GetIndex() >= aEndNdIdx.GetIndex() )
//STRIP001      {
//STRIP001          bEnde = TRUE;
//STRIP001          return aEmptyStr;
//STRIP001      }
//STRIP001
//STRIP001      aNdIdx++;
//STRIP001      if( aNdIdx.GetIndex() >= aEndNdIdx.GetIndex() )
//STRIP001      {
//STRIP001          bEnde = TRUE;
//STRIP001          return aEmptyStr;
//STRIP001      }
//STRIP001      else
//STRIP001          pNewNd = &aNdIdx.GetNode();
//STRIP001
//STRIP001      // kein TextNode ->
//STRIP001      //      TableNode   : Tabelle ueberspringen
//STRIP001      //      NoTxtNode   : Nodes ueberspringen
//STRIP001      //      EndNode     : Ende erreicht, beenden
//STRIP001      if( pNewNd->IsEndNode() )
//STRIP001      {
//STRIP001          bEnde = TRUE;
//STRIP001          return aEmptyStr;
//STRIP001      }
//STRIP001      else if( pNewNd->IsTableNode() )
//STRIP001          aNdIdx = *pNewNd->EndOfSectionNode();
//STRIP001      else if( pNewNd->IsSectionNode() )
//STRIP001      {
//STRIP001          const SwSection& rSect = pNewNd->GetSectionNode()->GetSection();
//STRIP001          if( rSect.IsHiddenFlag() || rSect.IsProtectFlag() )
//STRIP001              aNdIdx = *pNewNd->EndOfSectionNode();
//STRIP001      }
//STRIP001  } while( !pNewNd->IsTxtNode() );
//STRIP001
//STRIP001  if( !aFlags.bAFmtByInput )
//STRIP001      ::binfilter::SetProgressState( aNdIdx.GetIndex() + nEndNdIdx - aEndNdIdx.GetIndex(),
//STRIP001                          pDoc->GetDocShell() );
//STRIP001
//STRIP001  pAktTxtNd = (SwTxtNode*)pNewNd;
//STRIP001  pAktTxtFrm = GetFrm( *pAktTxtNd );
//STRIP001  return pAktTxtNd->GetTxt();
//STRIP001 }

//STRIP001 BOOL SwAutoFormat::HasObjects( const SwNode& rNd )
//STRIP001 {
//STRIP001  // haengt irgend etwas absatzgebundenes am Absatz?
//STRIP001  // z.B. Rahmen, DrawObjecte, ..
//STRIP001  BOOL bRet = FALSE;
//STRIP001  const SwSpzFrmFmts& rFmts = *pDoc->GetSpzFrmFmts();
//STRIP001  for( USHORT n = 0; n < rFmts.Count(); ++n )
//STRIP001  {
//STRIP001      const SwFmtAnchor& rAnchor = rFmts[ n ]->GetAnchor();
//STRIP001      if( FLY_PAGE != rAnchor.GetAnchorId() &&
//STRIP001          rAnchor.GetCntntAnchor() &&
//STRIP001          &rAnchor.GetCntntAnchor()->nNode.GetNode() == &rNd )
//STRIP001      {
//STRIP001          bRet = TRUE;
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 const SwTxtNode* SwAutoFormat::GetNextNode() const
//STRIP001 {
//STRIP001  if( aNdIdx.GetIndex()+1 >= aEndNdIdx.GetIndex() )
//STRIP001      return 0;
//STRIP001  return pDoc->GetNodes()[ aNdIdx.GetIndex() + 1 ]->GetTxtNode();
//STRIP001 }


//STRIP001 BOOL SwAutoFormat::IsOneLine( const SwTxtNode& rNd ) const
//STRIP001 {
//STRIP001  SwTxtFrmInfo aFInfo( GetFrm( rNd ) );
//STRIP001  return aFInfo.IsOneLine();
//STRIP001 }


//STRIP001 BOOL SwAutoFormat::IsFastFullLine( const SwTxtNode& rNd ) const
//STRIP001 {
//STRIP001  BOOL bRet = aFlags.bRightMargin;
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001      SwTxtFrmInfo aFInfo( GetFrm( rNd ) );
//STRIP001      bRet = aFInfo.IsFilled( aFlags.nRightMargin );
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }


//STRIP001 BOOL SwAutoFormat::IsEnumericChar( const SwTxtNode& rNd ) const
//STRIP001 {
//STRIP001  const String& rTxt = rNd.GetTxt();
//STRIP001  String sTmp( rTxt );
//STRIP001  xub_StrLen nBlnks = GetLeadingBlanks( sTmp );
//STRIP001  xub_StrLen nLen = rTxt.Len() - nBlnks;
//STRIP001  if( !nLen )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // -, +, * getrennt durch Blank ??
//STRIP001  if( 2 < nLen && IsSpace( rTxt.GetChar( nBlnks + 1 ) ) )
//STRIP001  {
//STRIP001      if( StrChr( pBulletChar, rTxt.GetChar( nBlnks ) ) )
//STRIP001          return TRUE;
//STRIP001      // sollte an der Position ein Symbolfont existieren ?
//STRIP001      SwTxtFrmInfo aFInfo( GetFrm( rNd ) );
//STRIP001      if( aFInfo.IsBullet( nBlnks ))
//STRIP001          return TRUE;
//STRIP001  }
//STRIP001
//STRIP001  // 1.) / 1. / 1.1.1 / (1). / (1) / ....
//STRIP001  return USHRT_MAX != GetDigitLevel( rNd, nBlnks );
//STRIP001 }


//STRIP001 BOOL SwAutoFormat::IsBlanksInString( const SwTxtNode& rNd ) const
//STRIP001 {
//STRIP001  // suche im String mehr als 5 Blanks/Tabs
//STRIP001  String sTmp( rNd.GetTxt() );
//STRIP001  DelTrailingBlanks( DelLeadingBlanks( sTmp ));
//STRIP001  const sal_Unicode* pTmp = sTmp.GetBuffer();
//STRIP001  while( *pTmp )
//STRIP001  {
//STRIP001      if( IsSpace( *pTmp ) )
//STRIP001      {
//STRIP001          if( IsSpace( *++pTmp ))     // 2 Space nach einander
//STRIP001          {
//STRIP001              const sal_Unicode* pStt = pTmp;
//STRIP001              while( *pTmp && IsSpace( *++pTmp ))
//STRIP001                  ;
//STRIP001              if( 5 <= pTmp - pStt )
//STRIP001                  return TRUE;
//STRIP001          }
//STRIP001          else
//STRIP001              ++pTmp;
//STRIP001      }
//STRIP001      else
//STRIP001          ++pTmp;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }


//STRIP001 USHORT SwAutoFormat::CalcLevel( const SwTxtNode& rNd, USHORT *pDigitLvl ) const
//STRIP001 {
//STRIP001  USHORT nLvl = 0, nBlnk = 0;
//STRIP001  const String& rTxt = rNd.GetTxt();
//STRIP001  if( pDigitLvl )
//STRIP001      *pDigitLvl = USHRT_MAX;
//STRIP001
//STRIP001  if( RES_POOLCOLL_TEXT_MOVE == rNd.GetTxtColl()->GetPoolFmtId() )
//STRIP001  {
//STRIP001      if( aFlags.bAFmtByInput )
//STRIP001      {
//STRIP001          nLvl = rNd.GetAutoFmtLvl();
//STRIP001          ((SwTxtNode&)rNd).SetAutoFmtLvl( 0 );
//STRIP001          if( nLvl )
//STRIP001              return nLvl;
//STRIP001      }
//STRIP001      ++nLvl;
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001  for( xub_StrLen n = 0, nEnd = rTxt.Len(); n < nEnd; ++n )
//STRIP001  {
//STRIP001      switch( rTxt.GetChar( n ) )
//STRIP001      {
//STRIP001      case ' ':   if( 3 == ++nBlnk )
//STRIP001                      ++nLvl, nBlnk = 0;
//STRIP001                  break;
//STRIP001      case '\t':  ++nLvl, nBlnk = 0;
//STRIP001                  break;
//STRIP001      default:
//STRIP001          if( pDigitLvl )
//STRIP001              // Teste auf 1.) / 1. / 1.1.1 / (1). / (1) / ....
//STRIP001              *pDigitLvl = GetDigitLevel( rNd, n );
//STRIP001          return nLvl;
//STRIP001      }
//STRIP001  }
//STRIP001  return nLvl;
//STRIP001 }



//STRIP001 xub_StrLen SwAutoFormat::GetBigIndent( xub_StrLen& rAktSpacePos ) const
//STRIP001 {
//STRIP001  SwTxtFrmInfo aFInfo( GetFrm( *pAktTxtNd ) );
//STRIP001  const SwTxtFrm* pNxtFrm = 0;
//STRIP001
//STRIP001  if( !bMoreLines )
//STRIP001  {
//STRIP001      const SwTxtNode* pNxtNd = GetNextNode();
//STRIP001      if( !CanJoin( pNxtNd ) || !IsOneLine( *pNxtNd ) )
//STRIP001          return 0;
//STRIP001
//STRIP001      pNxtFrm = GetFrm( *pNxtNd );
//STRIP001  }
//STRIP001
//STRIP001  return aFInfo.GetBigIndent( rAktSpacePos, pNxtFrm );
//STRIP001 }


//STRIP001 BOOL SwAutoFormat::IsNoAlphaLine( const SwTxtNode& rNd ) const
//STRIP001 {
//STRIP001  const String& rStr = rNd.GetTxt();
//STRIP001  if( !rStr.Len() )
//STRIP001      return FALSE;
//STRIP001  // oder besser: ueber die Anzahl von Alpha/Num- und !AN-Zeichen
//STRIP001  //              bestimmen.
//STRIP001  xub_StrLen nANChar = 0, nBlnk = 0;
//STRIP001
//STRIP001  CharClass& rCC = GetCharClass( rNd.GetSwAttrSet().GetLanguage().GetLanguage() );
//STRIP001  for( xub_StrLen n = 0, nEnd = rStr.Len(); n < nEnd; ++n )
//STRIP001      if( IsSpace( rStr.GetChar( n ) ) )
//STRIP001          ++nBlnk;
//STRIP001      else if( rCC.isLetterNumeric( rStr, n ))
//STRIP001          ++nANChar;
//STRIP001
//STRIP001  // sind zu 75% keine Alpha-Nummerische-Zeichen, dann TRUE
//STRIP001  ULONG nLen = rStr.Len() - nBlnk;
//STRIP001  nLen = ( nLen * 3 ) / 4;            // long overflow, if the strlen > USHORT
//STRIP001  return xub_StrLen(nLen) < (rStr.Len() - nANChar - nBlnk);
//STRIP001 }



//STRIP001 BOOL SwAutoFormat::DoUnderline()
//STRIP001 {
//STRIP001  if( !aFlags.bSetBorder )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  const sal_Unicode* pStr = pAktTxtNd->GetTxt().GetBuffer();
//STRIP001  int eState = 0;
//STRIP001  xub_StrLen nCnt = 0;
//STRIP001  while( *pStr )
//STRIP001  {
//STRIP001 //JP 29.03.96: Spaces unterbrechen die Umrandung!
//STRIP001 //       if( !IsSpace( *pStr ) )
//STRIP001      {
//STRIP001          int eTmp = 0;
//STRIP001          switch( *pStr )
//STRIP001          {
//STRIP001          case '-': eTmp = 1; break;
//STRIP001          case '_': eTmp = 2; break;
//STRIP001          case '=': eTmp = 3; break;
//STRIP001          case '*': eTmp = 4; break;
//STRIP001          case '~': eTmp = 5; break;
//STRIP001          case '#': eTmp = 6; break;
//STRIP001          default:
//STRIP001              return FALSE;
//STRIP001          }
//STRIP001          if( 0 == eState )
//STRIP001              eState = eTmp;
//STRIP001          else if( eState != eTmp )
//STRIP001              return FALSE;
//STRIP001          ++nCnt;
//STRIP001      }
//STRIP001      ++pStr;
//STRIP001  }
//STRIP001
//STRIP001  if( 2 < nCnt )
//STRIP001  {
//STRIP001      // dann unterstreiche mal den vorherigen Absatz, wenn es diesen gibt!
//STRIP001      DelEmptyLine( FALSE );
//STRIP001      aDelPam.SetMark();
//STRIP001      aDelPam.GetMark()->nContent = 0;
//STRIP001 //JP 19.03.96: kein Underline sondern eine Umrandung setzen!
//STRIP001 //       pDoc->Insert( aDelPam, SvxUnderlineItem( eState ) );
//STRIP001
//STRIP001      SvxBorderLine aLine;
//STRIP001      switch( eState )
//STRIP001      {
//STRIP001      case 1:         // einfach, 0,05 pt
//STRIP001          aLine.SetOutWidth( DEF_LINE_WIDTH_0 );
//STRIP001          break;
//STRIP001      case 2:         // einfach, 1,0 pt
//STRIP001          aLine.SetOutWidth( DEF_LINE_WIDTH_1 );
//STRIP001          break;
//STRIP001      case 3:         // doppelt, 1,1 pt
//STRIP001          aLine.SetOutWidth( DEF_DOUBLE_LINE0_OUT );
//STRIP001          aLine.SetInWidth( DEF_DOUBLE_LINE0_IN );
//STRIP001          aLine.SetDistance( DEF_DOUBLE_LINE0_DIST );
//STRIP001          break;
//STRIP001      case 4:         // doppelt, 4,5 pt
//STRIP001          aLine.SetOutWidth( DEF_DOUBLE_LINE4_OUT );
//STRIP001          aLine.SetInWidth( DEF_DOUBLE_LINE4_IN );
//STRIP001          aLine.SetDistance( DEF_DOUBLE_LINE4_DIST );
//STRIP001          break;
//STRIP001      case 5:         // doppelt, 6,0 pt
//STRIP001          aLine.SetOutWidth( DEF_DOUBLE_LINE5_OUT );
//STRIP001          aLine.SetInWidth( DEF_DOUBLE_LINE5_IN );
//STRIP001          aLine.SetDistance( DEF_DOUBLE_LINE5_DIST );
//STRIP001          break;
//STRIP001      case 6:         // doppelt, 9,0 pt
//STRIP001          aLine.SetOutWidth( DEF_DOUBLE_LINE6_OUT );
//STRIP001          aLine.SetInWidth( DEF_DOUBLE_LINE6_IN );
//STRIP001          aLine.SetDistance( DEF_DOUBLE_LINE6_DIST );
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      SvxBoxItem aBox;
//STRIP001      aBox.SetLine( &aLine, BOX_LINE_BOTTOM );
//STRIP001      aBox.SetDistance( 42 );     // ~0,75 mm
//STRIP001      pDoc->Insert( aDelPam, aBox );
//STRIP001
//STRIP001      aDelPam.DeleteMark();
//STRIP001  }
//STRIP001  return 2 < nCnt;
//STRIP001 }


//STRIP001 BOOL SwAutoFormat::DoTable()
//STRIP001 {
//STRIP001  if( !aFlags.bCreateTable || !aFlags.bAFmtByInput ||
//STRIP001      pAktTxtNd->FindTableNode() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  const String& rTmp = pAktTxtNd->GetTxt();
//STRIP001  xub_StrLen nSttPlus = GetLeadingBlanks( rTmp );
//STRIP001  xub_StrLen nEndPlus = GetTrailingBlanks( rTmp );
//STRIP001  sal_Unicode cChar;
//STRIP001
//STRIP001  if( 2 > nEndPlus - nSttPlus ||
//STRIP001      ( '+' != ( cChar = rTmp.GetChar( nSttPlus )) && '|' != cChar ) ||
//STRIP001      ( '+' != ( cChar = rTmp.GetChar( nEndPlus - 1)) && '|' != cChar ))
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SwTxtFrmInfo aInfo( pAktTxtFrm );
//STRIP001
//STRIP001  xub_StrLen n = nSttPlus;
//STRIP001  const sal_Unicode* pStr = rTmp.GetBuffer() + n;
//STRIP001  SvUShorts aPosArr( 5, 5 );
//STRIP001
//STRIP001  while( *pStr )
//STRIP001  {
//STRIP001      switch( *pStr )
//STRIP001      {
//STRIP001      case '-':
//STRIP001      case '_':
//STRIP001      case '=':
//STRIP001      case ' ':
//STRIP001      case '\t':
//STRIP001          break;
//STRIP001
//STRIP001      case '+':
//STRIP001      case '|':
//STRIP001          aPosArr.Insert( aInfo.GetCharPos(n), aPosArr.Count() );
//STRIP001          break;
//STRIP001
//STRIP001      default:
//STRIP001          return FALSE;
//STRIP001      }
//STRIP001      if( ++n == nEndPlus )
//STRIP001          break;
//STRIP001
//STRIP001      ++pStr;
//STRIP001  }
//STRIP001
//STRIP001  if( 1 < aPosArr.Count() )
//STRIP001  {
//STRIP001      // Ausrichtung vom Textnode besorgen:
//STRIP001      USHORT nColCnt = aPosArr.Count() - 1;
//STRIP001      SwTwips nSttPos = aPosArr[ 0 ];
//STRIP001      SwHoriOrient eHori;
//STRIP001      switch( pAktTxtNd->GetSwAttrSet().GetAdjust().GetAdjust() )
//STRIP001      {
//STRIP001      case SVX_ADJUST_CENTER:     eHori = HORI_CENTER;    break;
//STRIP001      case SVX_ADJUST_RIGHT:      eHori = HORI_RIGHT;     break;
//STRIP001
//STRIP001      default:
//STRIP001          if( nSttPos )
//STRIP001          {
//STRIP001              eHori = HORI_NONE;
//STRIP001              // dann muss als letztes noch die akt. FrameBreite
//STRIP001              // ins Array
//STRIP001              aPosArr.Insert( pAktTxtFrm->Frm().Width(), aPosArr.Count() );
//STRIP001          }
//STRIP001          else
//STRIP001              eHori = HORI_LEFT;
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      // dann erzeuge eine Tabelle, die den Zeichen entspricht
//STRIP001      DelEmptyLine();
//STRIP001      SwNodeIndex aIdx( aDelPam.GetPoint()->nNode );
//STRIP001      aDelPam.Move( fnMoveForward );
//STRIP001      pDoc->InsertTable( *aDelPam.GetPoint(), 1, nColCnt, eHori, ALL_TBL_INS_ATTR,
//STRIP001                          0, &aPosArr );
//STRIP001      aDelPam.GetPoint()->nNode = aIdx;
//STRIP001  }
//STRIP001  return 1 < aPosArr.Count();
//STRIP001 }


//STRIP001 String& SwAutoFormat::DelLeadingBlanks( String& rStr ) const
//STRIP001 {
//STRIP001  for( xub_StrLen nL = rStr.Len(), n = 0;
//STRIP001          n < nL && IsSpace( rStr.GetChar(n) ); ++n )
//STRIP001      ;
//STRIP001  if( n )     // keine Spaces
//STRIP001      rStr.Erase( 0, n );
//STRIP001  return rStr;
//STRIP001 }


//STRIP001 String& SwAutoFormat::DelTrailingBlanks( String& rStr ) const
//STRIP001 {
//STRIP001  xub_StrLen nL = rStr.Len(), n = nL;
//STRIP001  if( !nL )
//STRIP001      return rStr;
//STRIP001
//STRIP001  while( --n && IsSpace( rStr.GetChar( n ) )  )
//STRIP001      ;
//STRIP001  if( n+1 != nL )     // keine Spaces
//STRIP001      rStr.Erase( n+1 );
//STRIP001  return rStr;
//STRIP001 }


//STRIP001 xub_StrLen SwAutoFormat::GetLeadingBlanks( const String& rStr ) const
//STRIP001 {
//STRIP001  for( xub_StrLen nL = rStr.Len(), n = 0;
//STRIP001      n < nL && IsSpace( rStr.GetChar( n ) ); ++n )
//STRIP001      ;
//STRIP001  return n;
//STRIP001 }


//STRIP001 xub_StrLen SwAutoFormat::GetTrailingBlanks( const String& rStr ) const
//STRIP001 {
//STRIP001  xub_StrLen nL = rStr.Len(), n = nL;
//STRIP001  if( !nL )
//STRIP001      return 0;
//STRIP001
//STRIP001  while( --n && IsSpace( rStr.GetChar( n ) )  )
//STRIP001      ;
//STRIP001  return ++n;
//STRIP001 }


//STRIP001 BOOL SwAutoFormat::IsFirstCharCapital( const SwTxtNode& rNd ) const
//STRIP001 {
//STRIP001  const String& rTxt = rNd.GetTxt();
//STRIP001  for( xub_StrLen n = 0, nEnd = rTxt.Len(); n < nEnd; ++n )
//STRIP001      if( !IsSpace( rTxt.GetChar( n ) ) )
//STRIP001      {
//STRIP001          CharClass& rCC = GetCharClass( rNd.GetSwAttrSet().
//STRIP001                                      GetLanguage().GetLanguage() );
//STRIP001          sal_Int32 nCharType = rCC.getCharacterType( rTxt, n );
//STRIP001          return CharClass::isLetterType( nCharType ) &&
//STRIP001                 0 != ( ::com::sun::star::i18n::KCharacterType::UPPER &
//STRIP001                                                  nCharType );
//STRIP001      }
//STRIP001  return FALSE;
//STRIP001 }


//STRIP001 USHORT SwAutoFormat::GetDigitLevel( const SwTxtNode& rNd, xub_StrLen& rPos,
//STRIP001      String* pPreFix, String* pPostFix, String* pNumTypes ) const
//STRIP001 {
//STRIP001  // Teste auf 1.) / 1. / 1.1.1 / (1). / (1) / ....
//STRIP001  const String& rTxt = rNd.GetTxt();
//STRIP001  xub_StrLen nPos = rPos;
//STRIP001  int eScan = NONE;
//STRIP001
//STRIP001  USHORT nStart = 0;
//STRIP001  BYTE nDigitLvl = 0, nDigitCnt = 0;
//STRIP001
//STRIP001  CharClass& rCC = GetCharClass( rNd.GetSwAttrSet().GetLanguage().GetLanguage() );
//STRIP001
//STRIP001  while( nPos < rTxt.Len() && nDigitLvl < MAXLEVEL - 1)
//STRIP001  {
//STRIP001      if( '0' <= rTxt.GetChar( nPos ) &&  '9' >= rTxt.GetChar( nPos ))
//STRIP001      {
//STRIP001          if( eScan & DELIM )
//STRIP001          {
//STRIP001              if( eScan & CHG )       // nicht wenns mit einer Zahl beginnt
//STRIP001              {
//STRIP001                  ++nDigitLvl;
//STRIP001                  if( pPostFix )
//STRIP001                      *pPostFix += (sal_Unicode)1;
//STRIP001              }
//STRIP001
//STRIP001              if( pNumTypes )
//STRIP001                  *pNumTypes += (sal_Unicode)('0' + SVX_NUM_ARABIC);
//STRIP001
//STRIP001              eScan = eScan | CHG;
//STRIP001          }
//STRIP001          else if( pNumTypes && !(eScan & DIGIT) )
//STRIP001              *pNumTypes += (sal_Unicode)('0' + SVX_NUM_ARABIC);
//STRIP001
//STRIP001          eScan &= ~DELIM;        // Delim raus
//STRIP001          if( 0 != (eScan & ~CHG) && DIGIT != (eScan & ~CHG))
//STRIP001              return USHRT_MAX;
//STRIP001
//STRIP001          eScan |= DIGIT;         // Digit rein
//STRIP001          if( 3 == ++nDigitCnt )  // mehr als 2 Nummern sind kein Enum mehr
//STRIP001              return USHRT_MAX;
//STRIP001
//STRIP001          nStart *= 10;
//STRIP001          nStart += rTxt.GetChar( nPos ) - '0';
//STRIP001      }
//STRIP001      else if( rCC.isAlpha( rTxt, nPos ) )
//STRIP001      {
//STRIP001          BOOL bIsUpper =
//STRIP001              0 != ( ::com::sun::star::i18n::KCharacterType::UPPER &
//STRIP001                                      rCC.getCharacterType( rTxt, nPos ));
//STRIP001          sal_Unicode cLow = rCC.toLower( rTxt, nPos, 1 ).GetChar(0), cNumTyp;
//STRIP001          int eTmpScan;
//STRIP001
//STRIP001          // roemische Zeichen sind "mdclxvi". Da man aber eher mal eine
//STRIP001          // Numerierung mit c oder d anfangen will, werden diese erstmal
//STRIP001          // zu chars und spaeter ggfs. zu romischen Zeichen!
//STRIP001 //           if( strchr( "mdclxvi", cLow ))
//STRIP001 #ifdef WITH_ALPHANUM_AS_NUMFMT
//STRIP001          //detection of 'c' and 'd' a ROMAN numbering should not be done here
//STRIP001          if( 256 > cLow  &&( (eScan & (LOWER_ROMAN|UPPER_ROMAN))
//STRIP001                                  ? strchr( "mdclxvi", cLow )
//STRIP001                                  : strchr( "mlxvi", cLow ) ))
//STRIP001 #else
//STRIP001          if( 256 > cLow  && ( strchr( "mdclxvi", cLow ) ))
//STRIP001 #endif
//STRIP001          {
//STRIP001              if( bIsUpper )
//STRIP001                  cNumTyp = '0' + SVX_NUM_ROMAN_UPPER, eTmpScan = UPPER_ROMAN;
//STRIP001              else
//STRIP001                  cNumTyp = '0' + SVX_NUM_ROMAN_LOWER, eTmpScan = LOWER_ROMAN;
//STRIP001          }
//STRIP001          else if( bIsUpper )
//STRIP001              cNumTyp = '0' + SVX_NUM_CHARS_UPPER_LETTER, eTmpScan = UPPER_ALPHA;
//STRIP001          else
//STRIP001              cNumTyp = '0' + SVX_NUM_CHARS_LOWER_LETTER, eTmpScan = LOWER_ALPHA;
//STRIP001
//STRIP001
//STRIP001          //ggfs. auf roemische Zeichen umschalten (nur bei c/d!)?
//STRIP001          if( 1 == nDigitCnt && ( eScan & (UPPER_ALPHA|LOWER_ALPHA) ) &&
//STRIP001              ( 3 == nStart || 4 == nStart) && 256 > cLow &&
//STRIP001              strchr( "mdclxvi", cLow ) &&
//STRIP001              (( eScan & UPPER_ALPHA ) ? (eTmpScan & (UPPER_ALPHA|UPPER_ROMAN))
//STRIP001                                       : (eTmpScan & (LOWER_ALPHA|LOWER_ROMAN))) )
//STRIP001          {
//STRIP001              sal_Unicode c = '0';
//STRIP001              nStart = 3 == nStart ? 100 : 500;
//STRIP001              if( UPPER_ALPHA == eTmpScan )
//STRIP001                  eTmpScan = UPPER_ROMAN, c += SVX_NUM_ROMAN_UPPER;
//STRIP001              else
//STRIP001                  eTmpScan = LOWER_ROMAN, c += SVX_NUM_ROMAN_LOWER;
//STRIP001
//STRIP001 #ifndef MAC
//STRIP001              ( eScan &= ~(UPPER_ALPHA|LOWER_ALPHA)) |= eTmpScan;
//STRIP001 #else
//STRIP001              eScan &= ~(UPPER_ALPHA|LOWER_ALPHA);
//STRIP001              eScan |= eTmpScan;
//STRIP001 #endif
//STRIP001              if( pNumTypes )
//STRIP001                  pNumTypes->SetChar( pNumTypes->Len() - 1, c );
//STRIP001          }
//STRIP001
//STRIP001          if( eScan & DELIM )
//STRIP001          {
//STRIP001              if( eScan & CHG )       // nicht wenns mit einer Zahl beginnt
//STRIP001              {
//STRIP001                  ++nDigitLvl;
//STRIP001                  if( pPostFix )
//STRIP001                      *pPostFix += (sal_Unicode)1;
//STRIP001              }
//STRIP001
//STRIP001              if( pNumTypes )
//STRIP001                  *pNumTypes += cNumTyp;
//STRIP001              eScan = eScan | CHG;
//STRIP001          }
//STRIP001          else if( pNumTypes && !(eScan & eTmpScan) )
//STRIP001              *pNumTypes += cNumTyp;
//STRIP001
//STRIP001          eScan &= ~DELIM;        // Delim raus
//STRIP001
//STRIP001          // falls ein andere Type gesetzt ist, brechen wir ab
//STRIP001          if( 0 != ( eScan & ~CHG ) && eTmpScan != ( eScan & ~CHG ))
//STRIP001              return USHRT_MAX;
//STRIP001
//STRIP001          if( eTmpScan & (UPPER_ALPHA | LOWER_ALPHA) )
//STRIP001          {
//STRIP001              // Buchstaben nur zulassen, wenn sie einmalig vorkommen
//STRIP001 #ifdef WITH_ALPHANUM_AS_NUMFMT
//STRIP001 //JP 17.06.98: um Abkuerzungen wie P.S. oder Z.b. am Absatzanfang nicht zu
//STRIP001 //               Numerierungen zu expandieren, hier erstmal bei erkannten
//STRIP001 //               ALPHA keinen gueltigen DigitLevel returnen.
//STRIP001              if( nDigitCnt )
//STRIP001 #endif
//STRIP001                  return USHRT_MAX;
//STRIP001              nStart = (USHORT)(cLow - 'a') + 1;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              // roemische Zahlen: checke ob das gueltige Zeichen sind
//STRIP001              USHORT nVal;
//STRIP001              BOOL bError = FALSE;
//STRIP001              switch( cLow )
//STRIP001              {
//STRIP001              case 'm':   nVal = 1000; goto CHECK_ROMAN_1;
//STRIP001              case 'd':   nVal =  500; goto CHECK_ROMAN_5;
//STRIP001              case 'c':   nVal =  100; goto CHECK_ROMAN_1;
//STRIP001              case 'l':   nVal =   50; goto CHECK_ROMAN_5;
//STRIP001              case 'x':   nVal =   10; goto CHECK_ROMAN_1;
//STRIP001              case 'v':   nVal =    5; goto CHECK_ROMAN_5;
//STRIP001
//STRIP001 CHECK_ROMAN_1:
//STRIP001                  {
//STRIP001                      int nMod5 = nStart % (nVal * 5);
//STRIP001                      int nLast = nStart % nVal;
//STRIP001                      int n10 = nVal / 10;
//STRIP001
//STRIP001                      if( nMod5 == ((3 * nVal) + n10 ) ||
//STRIP001                          nMod5 == ((4 * nVal) + n10 ) ||
//STRIP001                          nLast == n10 )
//STRIP001                          nStart += n10 * 8;
//STRIP001                      else if( nMod5 == 0 ||
//STRIP001                               nMod5 == (1 * nVal) ||
//STRIP001                               nMod5 == (2 * nVal) )
//STRIP001                          nStart += nVal;
//STRIP001                      else
//STRIP001                          bError = TRUE;
//STRIP001                  }
//STRIP001                  break;
//STRIP001
//STRIP001 CHECK_ROMAN_5:
//STRIP001                  {
//STRIP001                      if( ( nStart / nVal ) & 1 )
//STRIP001                          bError = TRUE;
//STRIP001                      else
//STRIP001                      {
//STRIP001                          int nMod = nStart % nVal;
//STRIP001                          int n10 = nVal / 5;
//STRIP001                          if( n10 == nMod )
//STRIP001                              nStart += 3 * n10;
//STRIP001                          else if( 0 == nMod )
//STRIP001                              nStart += nVal;
//STRIP001                          else
//STRIP001                              bError = TRUE;
//STRIP001                      }
//STRIP001                  }
//STRIP001                  break;
//STRIP001
//STRIP001              case 'i':
//STRIP001                      if( nStart % 5 >= 3 )
//STRIP001                          bError = TRUE;
//STRIP001                      else
//STRIP001                          nStart += 1;
//STRIP001                      break;
//STRIP001
//STRIP001              default:
//STRIP001                  bError = TRUE;
//STRIP001              }
//STRIP001
//STRIP001              if( bError )
//STRIP001                  return USHRT_MAX;
//STRIP001          }
//STRIP001          eScan |= eTmpScan;          // Digit rein
//STRIP001          ++nDigitCnt;
//STRIP001      }
//STRIP001      else if( 256 > rTxt.GetChar( nPos ) &&
//STRIP001               strchr( /*".,)([]{}"*/ ".,)(<>", rTxt.GetChar( nPos ) ) )
//STRIP001      {
//STRIP001          // nur wenn noch keine Zahlen gelesen wurden!
//STRIP001          if( pPreFix && !( eScan & ( NO_DELIM | CHG )) )
//STRIP001              *pPreFix += rTxt.GetChar( nPos );
//STRIP001          else if( pPostFix )
//STRIP001              *pPostFix += rTxt.GetChar( nPos );
//STRIP001
//STRIP001          if( NO_DELIM & eScan )
//STRIP001          {
//STRIP001              eScan |= CHG;
//STRIP001              if( pPreFix )
//STRIP001                  (*pPreFix += (sal_Unicode)1)
//STRIP001                            += String::CreateFromInt32( nStart );
//STRIP001          }
//STRIP001          eScan &= ~NO_DELIM;     // Delim raus
//STRIP001          eScan |= DELIM;         // Digit rein
//STRIP001          nDigitCnt = 0;
//STRIP001          nStart = 0;
//STRIP001      }
//STRIP001      else
//STRIP001          break;
//STRIP001      ++nPos;
//STRIP001  }
//STRIP001  if( !( CHG & eScan ) || rPos == nPos ||
//STRIP001      nPos == rTxt.Len() || !IsSpace( rTxt.GetChar( nPos ) ))
//STRIP001      return USHRT_MAX;
//STRIP001
//STRIP001  if( (NO_DELIM & eScan) && pPreFix )     // den letzen nicht vergessen
//STRIP001      (*pPreFix += (sal_Unicode)1) += String::CreateFromInt32( nStart );
//STRIP001
//STRIP001  rPos = nPos;
//STRIP001  return nDigitLvl;       // 0 .. 9 (MAXLEVEL - 1)
//STRIP001 }


//STRIP001 void SwAutoFormat::SetColl( USHORT nId, BOOL bHdLineOrText )
//STRIP001 {
//STRIP001  aDelPam.DeleteMark();
//STRIP001  aDelPam.GetPoint()->nNode = aNdIdx;
//STRIP001  aDelPam.GetPoint()->nContent.Assign( pAktTxtNd, 0 );
//STRIP001
//STRIP001  // behalte harte Tabs, Ausrichtung, Sprache, Silbentrennung,
//STRIP001  // DropCaps und fast alle Frame-Attribute
//STRIP001  SfxItemSet aSet( pDoc->GetAttrPool(),
//STRIP001                      RES_PARATR_ADJUST, RES_PARATR_ADJUST,
//STRIP001                      RES_PARATR_TABSTOP, RES_PARATR_DROP,
//STRIP001                      RES_CHRATR_LANGUAGE, RES_CHRATR_LANGUAGE,
//STRIP001                      RES_BACKGROUND, RES_SHADOW,
//STRIP001                      0 );
//STRIP001
//STRIP001  if( pAktTxtNd->GetpSwAttrSet() )
//STRIP001  {
//STRIP001      aSet.Put( *pAktTxtNd->GetpSwAttrSet() );
//STRIP001      // einige Sonderbedingungen:
//STRIP001      // HeaderLine/Textkoerper: nur zentriert oder rechts mitnehmem
//STRIP001      // sonst nur den Blocksatz
//STRIP001      SvxAdjustItem* pAdj;
//STRIP001      if( SFX_ITEM_SET == aSet.GetItemState( RES_PARATR_ADJUST,
//STRIP001                      FALSE, (const SfxPoolItem**)&pAdj ))
//STRIP001      {
//STRIP001          SvxAdjust eAdj = pAdj->GetAdjust();
//STRIP001          if( bHdLineOrText ? (SVX_ADJUST_RIGHT != eAdj &&
//STRIP001                               SVX_ADJUST_CENTER != eAdj)
//STRIP001                            : SVX_ADJUST_BLOCK != eAdj )
//STRIP001              aSet.ClearItem( RES_PARATR_ADJUST );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  pDoc->SetTxtFmtCollByAutoFmt( *aDelPam.GetPoint(), nId, &aSet );
//STRIP001 }


//STRIP001 BOOL SwAutoFormat::HasSelBlanks( SwPaM& rPam ) const
//STRIP001 {
//STRIP001  // noch ein Blank am Anfang oder Ende ?
//STRIP001  // nicht loeschen, wird wieder eingefuegt.
//STRIP001  SwPosition * pPos = rPam.End();
//STRIP001  xub_StrLen nBlnkPos = pPos->nContent.GetIndex();
//STRIP001  SwTxtNode* pTxtNd = pPos->nNode.GetNode().GetTxtNode();
//STRIP001  if( nBlnkPos && nBlnkPos-- < pTxtNd->GetTxt().Len() &&
//STRIP001      ( ' ' == pTxtNd->GetTxt().GetChar( nBlnkPos ) ))
//STRIP001 // JP 23.08.95: keine Tabs stehen lassen, diese in Blanks wandeln
//STRIP001 //        ( ' ' == ( cCh = pTxtNd->GetTxt()[ nBlnkPos ] ) || '\t' == cCh ))
//STRIP001      pPos->nContent--;
//STRIP001  else
//STRIP001  {
//STRIP001      pPos = rPam.GetPoint() == pPos ? rPam.GetMark() : rPam.GetPoint();
//STRIP001      nBlnkPos = pPos->nContent.GetIndex();
//STRIP001      pTxtNd = pPos->nNode.GetNode().GetTxtNode();
//STRIP001      if( nBlnkPos < pTxtNd->GetTxt().Len() &&
//STRIP001          ( ' ' == pTxtNd->GetTxt().GetChar( nBlnkPos )))
//STRIP001 // JP 23.08.95: keine Tabs stehen lassen, diese in Blanks wandeln
//STRIP001 //            ( ' ' == ( cCh = pTxtNd->GetTxt()[ nBlnkPos ] ) || '\t' == cCh ))
//STRIP001          pPos->nContent++;
//STRIP001      else
//STRIP001          return FALSE;
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 BOOL SwAutoFormat::HasBreakAttr( const SwTxtNode& rTxtNd ) const
//STRIP001 {
//STRIP001  const SwAttrSet* pSet = rTxtNd.GetpSwAttrSet();
//STRIP001  if( !pSet )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  const SfxPoolItem* pItem;
//STRIP001  if( SFX_ITEM_SET == pSet->GetItemState( RES_BREAK, FALSE, &pItem )
//STRIP001      && SVX_BREAK_NONE != ((SvxFmtBreakItem*)pItem)->GetBreak() )
//STRIP001      return TRUE;
//STRIP001
//STRIP001  if( SFX_ITEM_SET == pSet->GetItemState( RES_PAGEDESC, FALSE, &pItem )
//STRIP001      && ((SwFmtPageDesc*)pItem)->GetPageDesc()
//STRIP001      && PD_NONE != ((SwFmtPageDesc*)pItem)->GetPageDesc()->GetUseOn() )
//STRIP001      return TRUE;
//STRIP001  return FALSE;
//STRIP001 }


// ist ein Punkt am Ende ??
//STRIP001 BOOL SwAutoFormat::IsSentenceAtEnd( const SwTxtNode& rTxtNd ) const
//STRIP001 {
//STRIP001  const String& rStr = rTxtNd.GetTxt();
//STRIP001  xub_StrLen n = rStr.Len();
//STRIP001  if( !n )
//STRIP001      return TRUE;
//STRIP001
//STRIP001  while( --n && IsSpace( rStr.GetChar( n  ) ) )
//STRIP001      ;
//STRIP001  return '.' == rStr.GetChar( n );
//STRIP001 }


// loesche im Node Anfang oder/und Ende
//STRIP001 void SwAutoFormat::DeleteAktPara( BOOL bStart, BOOL bEnd )
//STRIP001 {
//STRIP001  if( aFlags.bAFmtByInput
//STRIP001      ? aFlags.bAFmtByInpDelSpacesAtSttEnd
//STRIP001      : aFlags.bAFmtDelSpacesAtSttEnd )
//STRIP001  {
//STRIP001      // Loesche Blanks am Ende vom akt. und am Anfang vom naechsten
//STRIP001      aDelPam.DeleteMark();
//STRIP001      aDelPam.GetPoint()->nNode = aNdIdx;
//STRIP001      xub_StrLen nPos;
//STRIP001      if( bStart && 0 != ( nPos = GetLeadingBlanks( pAktTxtNd->GetTxt() )))
//STRIP001      {
//STRIP001          aDelPam.GetPoint()->nContent.Assign( pAktTxtNd, 0 );
//STRIP001          aDelPam.SetMark();
//STRIP001          aDelPam.GetPoint()->nContent = nPos;
//STRIP001          DeleteSel( aDelPam );
//STRIP001          aDelPam.DeleteMark();
//STRIP001      }
//STRIP001      if( bEnd && pAktTxtNd->GetTxt().Len() !=
//STRIP001                  ( nPos = GetTrailingBlanks( pAktTxtNd->GetTxt() )) )
//STRIP001      {
//STRIP001          aDelPam.GetPoint()->nContent.Assign( pAktTxtNd, pAktTxtNd->GetTxt().Len() );
//STRIP001          aDelPam.SetMark();
//STRIP001          aDelPam.GetPoint()->nContent = nPos;
//STRIP001          DeleteSel( aDelPam );
//STRIP001          aDelPam.DeleteMark();
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SwAutoFormat::DeleteSel( SwPaM& rDelPam )
//STRIP001 {
//STRIP001  if( aFlags.bWithRedlining )
//STRIP001  {
//STRIP001      // damit der DelPam auch verschoben wird, in den Shell-Cursr-Ring
//STRIP001      // mit aufnehmen !!
//STRIP001      SwPaM* pShCrsr = pEditShell->_GetCrsr();
//STRIP001      SwPaM aTmp( *pAktTxtNd, 0, pShCrsr );
//STRIP001
//STRIP001      Ring *pPrev = rDelPam.GetPrev();
//STRIP001      rDelPam.MoveRingTo( pShCrsr );
//STRIP001
//STRIP001      pEditShell->DeleteSel( rDelPam );
//STRIP001
//STRIP001      // und den Pam wieder herausnehmen:
//STRIP001      Ring *p, *pNext = (Ring*)&rDelPam;
//STRIP001      do {
//STRIP001          p = pNext;
//STRIP001          pNext = p->GetNext();
//STRIP001          p->MoveTo( &rDelPam );
//STRIP001      } while( p != pPrev );
//STRIP001
//STRIP001      aNdIdx = aTmp.GetPoint()->nNode;
//STRIP001      pAktTxtNd = aNdIdx.GetNode().GetTxtNode();
//STRIP001  }
//STRIP001  else
//STRIP001      pEditShell->DeleteSel( rDelPam );
//STRIP001 }

//STRIP001 BOOL SwAutoFormat::DeleteAktNxtPara( const String& rNxtPara )
//STRIP001 {
//STRIP001  // Loesche Blanks am Ende vom akt. und am Anfang vom naechsten
//STRIP001  aDelPam.DeleteMark();
//STRIP001  aDelPam.GetPoint()->nNode = aNdIdx;
//STRIP001  aDelPam.GetPoint()->nContent.Assign( pAktTxtNd,
//STRIP001                  GetTrailingBlanks( pAktTxtNd->GetTxt() ) );
//STRIP001  aDelPam.SetMark();
//STRIP001
//STRIP001  aDelPam.GetPoint()->nNode++;
//STRIP001  SwTxtNode* pTNd = aDelPam.GetNode()->GetTxtNode();
//STRIP001  if( !pTNd )
//STRIP001  {
//STRIP001      // dann nur bis zum Ende von Absatz loeschen
//STRIP001      aDelPam.GetPoint()->nNode--;
//STRIP001      aDelPam.GetPoint()->nContent = pAktTxtNd->GetTxt().Len();
//STRIP001  }
//STRIP001  else
//STRIP001      aDelPam.GetPoint()->nContent.Assign( pTNd,
//STRIP001                          GetLeadingBlanks( rNxtPara ));
//STRIP001
//STRIP001  // noch ein Blank am Anfang oder Ende ?
//STRIP001  // nicht loeschen, wird wieder eingefuegt.
//STRIP001  BOOL bHasBlnks = HasSelBlanks( aDelPam );
//STRIP001
//STRIP001  if( *aDelPam.GetPoint() != *aDelPam.GetMark() )
//STRIP001      DeleteSel( aDelPam );
//STRIP001  aDelPam.DeleteMark();
//STRIP001
//STRIP001  return !bHasBlnks;
//STRIP001 }


//STRIP001 void SwAutoFormat::DelEmptyLine( BOOL bTstNextPara )
//STRIP001 {
//STRIP001  SetRedlineTxt( STR_AUTOFMTREDL_DEL_EMPTY_PARA );
//STRIP001  // Loesche Blanks den leeren Absatz
//STRIP001  aDelPam.DeleteMark();
//STRIP001  aDelPam.GetPoint()->nNode = aNdIdx;
//STRIP001  aDelPam.GetPoint()->nContent.Assign( pAktTxtNd, pAktTxtNd->GetTxt().Len() );
//STRIP001  aDelPam.SetMark();
//STRIP001
//STRIP001  aDelPam.GetMark()->nNode--;
//STRIP001  SwTxtNode* pTNd = aDelPam.GetNode( FALSE )->GetTxtNode();
//STRIP001  if( pTNd )
//STRIP001      // erstmal den vorherigen Textnode benutzen.
//STRIP001      aDelPam.GetMark()->nContent.Assign( pTNd, pTNd->GetTxt().Len() );
//STRIP001  else if( bTstNextPara )
//STRIP001  {
//STRIP001      // dann versuche den naechsten (am Anfang vom Dok, Tabellen-Zellen,
//STRIP001      // Rahmen, ...
//STRIP001      aDelPam.GetMark()->nNode += 2;
//STRIP001      pTNd = aDelPam.GetNode( FALSE )->GetTxtNode();
//STRIP001      if( pTNd )
//STRIP001      {
//STRIP001          aDelPam.GetMark()->nContent.Assign( pTNd, 0 );
//STRIP001          aDelPam.GetPoint()->nContent = 0;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      aDelPam.GetMark()->nNode = aNdIdx;
//STRIP001      aDelPam.GetMark()->nContent = 0;
//STRIP001      pTNd = pAktTxtNd;
//STRIP001  }
//STRIP001  if( pTNd )
//STRIP001      DeleteSel( aDelPam );
//STRIP001
//STRIP001  aDelPam.DeleteMark();
//STRIP001  ClearRedlineTxt();
//STRIP001 }


//STRIP001 void SwAutoFormat::DelMoreLinesBlanks( BOOL bWithLineBreaks )
//STRIP001 {
//STRIP001  if( aFlags.bAFmtByInput
//STRIP001      ? aFlags.bAFmtByInpDelSpacesBetweenLines
//STRIP001      : aFlags.bAFmtDelSpacesBetweenLines )
//STRIP001  {
//STRIP001      // loesche alle "Blanks" Links und Rechts vom Einzug
//STRIP001      aDelPam.DeleteMark();
//STRIP001      aDelPam.GetPoint()->nNode = aNdIdx;
//STRIP001      aDelPam.GetPoint()->nContent.Assign( pAktTxtNd, 0 );
//STRIP001
//STRIP001      SwTxtFrmInfo aFInfo( pAktTxtFrm );
//STRIP001      aFInfo.GetSpaces( aDelPam, !aFlags.bAFmtByInput || bWithLineBreaks );
//STRIP001
//STRIP001      SwPaM* pNxt;
//STRIP001      do {
//STRIP001          pNxt = (SwPaM*)aDelPam.GetNext();
//STRIP001          if( pNxt->HasMark() && *pNxt->GetPoint() != *pNxt->GetMark() )
//STRIP001          {
//STRIP001              BOOL bHasBlnks = HasSelBlanks( *pNxt );
//STRIP001              DeleteSel( *pNxt );
//STRIP001              if( !bHasBlnks )
//STRIP001                  pDoc->Insert( *pNxt, ' ' );
//STRIP001          }
//STRIP001
//STRIP001          if( pNxt == &aDelPam )
//STRIP001              break;
//STRIP001          delete pNxt;
//STRIP001      } while( TRUE );
//STRIP001
//STRIP001      aDelPam.DeleteMark();
//STRIP001  }
//STRIP001 }


        // loesche den vorherigen Absatz
//STRIP001 void SwAutoFormat::DelPrevPara()
//STRIP001 {
//STRIP001  aDelPam.DeleteMark();
//STRIP001  aDelPam.GetPoint()->nNode = aNdIdx;
//STRIP001  aDelPam.GetPoint()->nContent.Assign( pAktTxtNd, 0 );
//STRIP001  aDelPam.SetMark();
//STRIP001
//STRIP001  aDelPam.GetPoint()->nNode--;
//STRIP001  SwTxtNode* pTNd = aDelPam.GetNode()->GetTxtNode();
//STRIP001  if( pTNd )
//STRIP001  {
//STRIP001      // erstmal den vorherigen Textnode benutzen.
//STRIP001      aDelPam.GetPoint()->nContent.Assign( pTNd, pTNd->GetTxt().Len() );
//STRIP001      DeleteSel( aDelPam );
//STRIP001  }
//STRIP001  aDelPam.DeleteMark();
//STRIP001 }


//STRIP001 void SwAutoFormat::BuildIndent()
//STRIP001 {
//STRIP001  SetRedlineTxt( STR_AUTOFMTREDL_SET_TMPL_INDENT );
//STRIP001
//STRIP001  // lese alle nachfolgenden Absaetze die zu diesem Einzug gehoeren
//STRIP001  BOOL bBreak = TRUE;
//STRIP001  if( bMoreLines )
//STRIP001      DelMoreLinesBlanks( TRUE );
//STRIP001  else
//STRIP001      bBreak = !IsFastFullLine( *pAktTxtNd ) ||
//STRIP001              IsBlanksInString( *pAktTxtNd ) ||
//STRIP001              IsSentenceAtEnd( *pAktTxtNd );
//STRIP001  SetColl( RES_POOLCOLL_TEXT_IDENT );
//STRIP001  if( !bBreak )
//STRIP001  {
//STRIP001      SetRedlineTxt( STR_AUTOFMTREDL_DEL_MORELINES );
//STRIP001      const SwTxtNode* pNxtNd = GetNextNode();
//STRIP001      if( pNxtNd && !bEnde )
//STRIP001      {
//STRIP001          do {
//STRIP001              bBreak = !IsFastFullLine( *pNxtNd ) ||
//STRIP001                      IsBlanksInString( *pNxtNd ) ||
//STRIP001                      IsSentenceAtEnd( *pNxtNd );
//STRIP001              if( DeleteAktNxtPara( pNxtNd->GetTxt() ))
//STRIP001                  pDoc->Insert( aDelPam, ' ' );
//STRIP001              if( bBreak )
//STRIP001                  break;
//STRIP001              pNxtNd = GetNextNode();
//STRIP001          } while( CanJoin( pNxtNd ) &&
//STRIP001                  !CalcLevel( *pNxtNd ) );
//STRIP001      }
//STRIP001  }
//STRIP001  DeleteAktPara( TRUE, TRUE );
//STRIP001  AutoCorrect();
//STRIP001 }


//STRIP001 void SwAutoFormat::BuildTextIndent()
//STRIP001 {
//STRIP001  SetRedlineTxt( STR_AUTOFMTREDL_SET_TMPL_TEXT_INDENT);
//STRIP001  // lese alle nachfolgenden Absaetze die zu diesem Einzug gehoeren
//STRIP001  BOOL bBreak = TRUE;
//STRIP001  if( bMoreLines )
//STRIP001      DelMoreLinesBlanks( TRUE );
//STRIP001  else
//STRIP001      bBreak = !IsFastFullLine( *pAktTxtNd ) ||
//STRIP001                  IsBlanksInString( *pAktTxtNd ) ||
//STRIP001                  IsSentenceAtEnd( *pAktTxtNd );
//STRIP001
//STRIP001  if( aFlags.bAFmtByInput )
//STRIP001      pAktTxtNd->SetAutoFmtLvl( (BYTE)CalcLevel( *pAktTxtNd ) );
//STRIP001
//STRIP001  SetColl( RES_POOLCOLL_TEXT_MOVE );
//STRIP001  if( !bBreak )
//STRIP001  {
//STRIP001      SetRedlineTxt( STR_AUTOFMTREDL_DEL_MORELINES );
//STRIP001      const SwTxtNode* pNxtNd = GetNextNode();
//STRIP001      while(  CanJoin( pNxtNd ) &&
//STRIP001              CalcLevel( *pNxtNd ) )
//STRIP001      {
//STRIP001          bBreak = !IsFastFullLine( *pNxtNd ) || IsBlanksInString( *pNxtNd ) ||
//STRIP001                  IsSentenceAtEnd( *pNxtNd );
//STRIP001          if( DeleteAktNxtPara( pNxtNd->GetTxt() ) )
//STRIP001              pDoc->Insert( aDelPam, ' ' );
//STRIP001          if( bBreak )
//STRIP001              break;
//STRIP001          pNxtNd = GetNextNode();
//STRIP001      }
//STRIP001  }
//STRIP001  DeleteAktPara( TRUE, TRUE );
//STRIP001  AutoCorrect();
//STRIP001 }


//STRIP001 void SwAutoFormat::BuildText()
//STRIP001 {
//STRIP001  SetRedlineTxt( STR_AUTOFMTREDL_SET_TMPL_TEXT );
//STRIP001  // lese alle nachfolgenden Absaetze die zu diesem Text
//STRIP001  // ohne Einzug gehoeren
//STRIP001  BOOL bBreak = TRUE;
//STRIP001  if( bMoreLines )
//STRIP001      DelMoreLinesBlanks();
//STRIP001  else
//STRIP001      bBreak = !IsFastFullLine( *pAktTxtNd ) ||
//STRIP001                  IsBlanksInString( *pAktTxtNd ) ||
//STRIP001                  IsSentenceAtEnd( *pAktTxtNd );
//STRIP001  SetColl( RES_POOLCOLL_TEXT, TRUE );
//STRIP001  if( !bBreak )
//STRIP001  {
//STRIP001      SetRedlineTxt( STR_AUTOFMTREDL_DEL_MORELINES );
//STRIP001      const SwTxtNode* pNxtNd = GetNextNode();
//STRIP001      while(  CanJoin( pNxtNd ) &&
//STRIP001              !CalcLevel( *pNxtNd ) )
//STRIP001      {
//STRIP001          bBreak = !IsFastFullLine( *pNxtNd ) || IsBlanksInString( *pNxtNd ) ||
//STRIP001                  IsSentenceAtEnd( *pNxtNd );
//STRIP001          if( DeleteAktNxtPara( pNxtNd->GetTxt() ) )
//STRIP001              pDoc->Insert( aDelPam, ' ' );
//STRIP001          if( bBreak )
//STRIP001              break;
//STRIP001          pNxtNd = GetNextNode();
//STRIP001      }
//STRIP001  }
//STRIP001  DeleteAktPara( TRUE, TRUE );
//STRIP001  AutoCorrect();
//STRIP001 }


//STRIP001 void SwAutoFormat::BuildEnum( USHORT nLvl, USHORT nDigitLevel )
//STRIP001 {
//STRIP001  SetRedlineTxt( STR_AUTOFMTREDL_SET_NUMBULET );
//STRIP001
//STRIP001  BOOL bBreak = TRUE;
//STRIP001
//STRIP001  // als erstes den akt. Einzug bestimmen und die Framebreite bestimmen
//STRIP001  SwTwips nFrmWidth = pAktTxtFrm->Prt().Width();;
//STRIP001  SwTwips nLeftTxtPos;
//STRIP001  {
//STRIP001      const sal_Unicode* pTxt = pAktTxtNd->GetTxt().GetBuffer(), *pSav = pTxt;
//STRIP001      while( IsSpace( *pTxt ) )
//STRIP001          ++pTxt;
//STRIP001
//STRIP001      SwTxtFrmInfo aInfo( pAktTxtFrm );
//STRIP001      nLeftTxtPos = aInfo.GetCharPos( pTxt - pSav );
//STRIP001 #ifdef NUM_RELSPACE
//STRIP001      nLeftTxtPos -= pAktTxtNd->GetSwAttrSet().GetLRSpace().GetLeft();
//STRIP001 #endif
//STRIP001  }
//STRIP001
//STRIP001  if( bMoreLines )
//STRIP001      DelMoreLinesBlanks();
//STRIP001  else
//STRIP001      bBreak = !IsFastFullLine( *pAktTxtNd ) ||
//STRIP001                  IsBlanksInString( *pAktTxtNd ) ||
//STRIP001                  IsSentenceAtEnd( *pAktTxtNd );
//STRIP001
//STRIP001 //   SetColl( RES_POOLCOLL_NUM_LEVEL1 + ( nLvl * 4 ) );
//STRIP001  DeleteAktPara( TRUE, TRUE );
//STRIP001
//STRIP001  BOOL bChgBullet = FALSE, bChgEnum = FALSE;
//STRIP001  xub_StrLen nAutoCorrPos = 0;
//STRIP001
//STRIP001  // falls die Numerierung gesetzt werden, die akt. besorgen
//STRIP001  SwNumRule aRule( pDoc->GetUniqueNumRuleName() );
//STRIP001  const SwNumRule* pCur;
//STRIP001  if( aFlags.bSetNumRule && 0 != (pCur = pAktTxtNd->GetNumRule()) )
//STRIP001      aRule = *pCur;
//STRIP001
//STRIP001  // ersetze das Bullet-Zeichen mit dem definiertem
//STRIP001  const String& rStr = pAktTxtNd->GetTxt();
//STRIP001  xub_StrLen nTxtStt = 0, nOrigTxtStt = 0;
//STRIP001  const sal_Unicode* pFndBulletChr;
//STRIP001 //   if( aFlags.bAFmtByInput ? aFlags.bSetNumRule : aFlags.bChgEnumNum &&
//STRIP001  if( aFlags.bChgEnumNum &&
//STRIP001      2 < rStr.Len() &&
//STRIP001      0 != ( pFndBulletChr = StrChr( pBulletChar, rStr.GetChar( nTxtStt ) ))
//STRIP001      && IsSpace( rStr.GetChar( nTxtStt + 1 ) ) )
//STRIP001  {
//STRIP001      if( aFlags.bAFmtByInput )
//STRIP001      {
//STRIP001          if( aFlags.bSetNumRule )
//STRIP001          {
//STRIP001              SwCharFmt* pCFmt = pDoc->GetCharFmtFromPool(
//STRIP001                                          RES_POOLCHR_BUL_LEVEL );
//STRIP001              bChgBullet = TRUE;
//STRIP001              // wurde das Format schon mal angepasst?
//STRIP001              if( !aRule.GetNumFmt( nLvl ) )
//STRIP001              {
//STRIP001                  int nBulletPos = pFndBulletChr - pBulletChar;
//STRIP001                  sal_Unicode cBullChar;
//STRIP001                  const Font* pBullFnt;
//STRIP001                  if( nBulletPos < cnPosEnDash )
//STRIP001                  {
//STRIP001                      cBullChar = aFlags.cBullet;
//STRIP001                      pBullFnt = &aFlags.aBulletFont;
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      cBullChar = nBulletPos < cnPosEmDash
//STRIP001                                      ? cStarSymbolEnDash
//STRIP001                                      : cStarSymbolEmDash;
//STRIP001                      pBullFnt = &SwNumRule::GetDefBulletFont();
//STRIP001                  }
//STRIP001
//STRIP001                  USHORT nAbsPos = lBullIndent;
//STRIP001                  USHORT nSpaceSteps = nLvl
//STRIP001                                          ? USHORT(nLeftTxtPos / nLvl)
//STRIP001                                          : lBullIndent;
//STRIP001                  for( BYTE n = 0; n < MAXLEVEL; ++n, nAbsPos += nSpaceSteps )
//STRIP001                  {
//STRIP001                      SwNumFmt aFmt( aRule.Get( n ) );
//STRIP001                      aFmt.SetBulletFont( pBullFnt );
//STRIP001                      aFmt.SetBulletChar( cBullChar );
//STRIP001                      aFmt.SetNumberingType(SVX_NUM_CHAR_SPECIAL);
//STRIP001                      aFmt.SetFirstLineOffset( lBullFirstLineOffset );
//STRIP001                      aFmt.SetAbsLSpace( nAbsPos );
//STRIP001                      if( !aFmt.GetCharFmt() )
//STRIP001                          aFmt.SetCharFmt( pCFmt );
//STRIP001
//STRIP001                      aRule.Set( n, aFmt );
//STRIP001
//STRIP001                      if( n == nLvl &&
//STRIP001                          nFrmWidth < ( nSpaceSteps * MAXLEVEL ) )
//STRIP001                          nSpaceSteps = ( nFrmWidth - nLeftTxtPos ) /
//STRIP001                                              ( MAXLEVEL - nLvl );
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          bChgBullet = TRUE;
//STRIP001          SetColl( RES_POOLCOLL_BUL_LEVEL1 + ( Min( nLvl, cnNumBullColls ) * 4 ) );
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // dann ist das eine Nummerierung
//STRIP001
//STRIP001      //JP 21.11.97: Der NumLevel wird entweder der DigitLevel oder
//STRIP001      //              wenn der nicht vorhanden oder 0 ist, durch den
//STRIP001      //              (Einrueckungs-)Level.
//STRIP001
//STRIP001      String aPostFix, aPreFix, aNumTypes;
//STRIP001      if( USHRT_MAX != ( nDigitLevel = GetDigitLevel( *pAktTxtNd, nTxtStt,
//STRIP001                                      &aPreFix, &aPostFix, &aNumTypes )) )
//STRIP001      {
//STRIP001          bChgEnum = TRUE;
//STRIP001
//STRIP001          // Ebene 0 und Einrueckung dann wird die Ebene durch den linken
//STRIP001          // Einzug und der default NumEinrueckung bestimmt.
//STRIP001          if( !nDigitLevel && nLeftTxtPos )
//STRIP001              nLvl = Min( USHORT( nLeftTxtPos / lNumIndent ),
//STRIP001                          USHORT( MAXLEVEL - 1 ) );
//STRIP001          else
//STRIP001              nLvl = nDigitLevel;
//STRIP001      }
//STRIP001
//STRIP001      if( bChgEnum && aFlags.bSetNumRule )
//STRIP001      {
//STRIP001          if( !pCur )         // NumRule anpassen, wenn sie neu ist
//STRIP001          {
//STRIP001              SwCharFmt* pCFmt = pDoc->GetCharFmtFromPool(
//STRIP001                                          RES_POOLCHR_NUM_LEVEL );
//STRIP001              if( !nDigitLevel )
//STRIP001              {
//STRIP001                  SwNumFmt aFmt( aRule.Get( nLvl ) );
//STRIP001                  aFmt.SetStart( aPreFix.GetToken( 1,
//STRIP001                                          (sal_Unicode)1 ).ToInt32());
//STRIP001                  aFmt.SetPrefix( aPreFix.GetToken( 0, (sal_Unicode)1 ));
//STRIP001                  aFmt.SetSuffix( aPostFix.GetToken( 0, (sal_Unicode)1 ));
//STRIP001                  aFmt.SetIncludeUpperLevels( 0 );
//STRIP001
//STRIP001                  if( !aFmt.GetCharFmt() )
//STRIP001                      aFmt.SetCharFmt( pCFmt );
//STRIP001
//STRIP001                  if( aNumTypes.Len() )
//STRIP001                      aFmt.SetNumberingType(aNumTypes.GetChar( 0 ) - '0');
//STRIP001
//STRIP001                  aRule.Set( nLvl, aFmt );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  USHORT nSpaceSteps = nLvl ? USHORT(nLeftTxtPos / nLvl) : 0;
//STRIP001                  for( BYTE n = 0; n <= nLvl; ++n )
//STRIP001                  {
//STRIP001                      SwNumFmt aFmt( aRule.Get( n ) );
//STRIP001
//STRIP001                      aFmt.SetStart( aPreFix.GetToken( n+1,
//STRIP001                                                  (sal_Unicode)1 ).ToInt32() );
//STRIP001                      if( !n )
//STRIP001                          aFmt.SetPrefix( aPreFix.GetToken( n, (sal_Unicode)1 ));
//STRIP001                      aFmt.SetSuffix( aPostFix.GetToken( n, (sal_Unicode)1 ));
//STRIP001                      aFmt.SetIncludeUpperLevels( MAXLEVEL );
//STRIP001                      if( n < aNumTypes.Len() )
//STRIP001                          aFmt.SetNumberingType((aNumTypes.GetChar( n ) - '0'));
//STRIP001
//STRIP001                      aFmt.SetAbsLSpace( USHORT( nSpaceSteps * n )
//STRIP001                                          + lNumIndent );
//STRIP001
//STRIP001                      if( !aFmt.GetCharFmt() )
//STRIP001                          aFmt.SetCharFmt( pCFmt );
//STRIP001
//STRIP001                      aRule.Set( n, aFmt );
//STRIP001                  }
//STRIP001
//STRIP001                  // passt alles vollstaendig in den Frame?
//STRIP001                  BOOL bDefStep = nFrmWidth < (nSpaceSteps * MAXLEVEL);
//STRIP001                  for( ; n < MAXLEVEL; ++n )
//STRIP001                  {
//STRIP001                      SwNumFmt aFmt( aRule.Get( n ) );
//STRIP001                      aFmt.SetIncludeUpperLevels( MAXLEVEL );
//STRIP001                      if( bDefStep )
//STRIP001                          aFmt.SetAbsLSpace( USHORT( (nLeftTxtPos +
//STRIP001                                      SwNumRule::GetNumIndent( n - nLvl ))));
//STRIP001                      else
//STRIP001                          aFmt.SetAbsLSpace( USHORT( nSpaceSteps * n )
//STRIP001                                              + lNumIndent );
//STRIP001                      aRule.Set( n, aFmt );
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      else if( !aFlags.bAFmtByInput )
//STRIP001          SetColl( RES_POOLCOLL_NUM_LEVEL1 + ( Min( nLvl, cnNumBullColls ) * 4 ) );
//STRIP001      else
//STRIP001          bChgEnum = FALSE;
//STRIP001  }
//STRIP001
//STRIP001  if( bChgEnum || bChgBullet )
//STRIP001  {
//STRIP001      aDelPam.DeleteMark();
//STRIP001      aDelPam.GetPoint()->nNode = aNdIdx;
//STRIP001
//STRIP001      if( aFlags.bSetNumRule )
//STRIP001      {
//STRIP001          if( aFlags.bAFmtByInput )
//STRIP001          {
//STRIP001              aDelPam.SetMark();
//STRIP001              aDelPam.GetMark()->nNode++;
//STRIP001              aDelPam.GetNode(FALSE)->GetTxtNode()->UpdateNum( SwNodeNum( (BYTE)nLvl ) );
//STRIP001          }
//STRIP001
//STRIP001          pAktTxtNd->UpdateNum( SwNodeNum( (BYTE)nLvl ) );
//STRIP001          pAktTxtNd->SetNumLSpace( TRUE );
//STRIP001
//STRIP001          pDoc->SetNumRule( aDelPam, aRule );
//STRIP001          aDelPam.DeleteMark();
//STRIP001
//STRIP001          aDelPam.GetPoint()->nContent.Assign( pAktTxtNd, 0 );
//STRIP001      }
//STRIP001      else
//STRIP001          aDelPam.GetPoint()->nContent.Assign( pAktTxtNd,
//STRIP001                      bChgEnum ? (nTxtStt - nOrigTxtStt) : 0 );
//STRIP001      aDelPam.SetMark();
//STRIP001
//STRIP001      if( bChgBullet )
//STRIP001          nTxtStt += 2;
//STRIP001
//STRIP001      while( nTxtStt < rStr.Len() && IsSpace( rStr.GetChar( nTxtStt ) ))
//STRIP001          nTxtStt++;
//STRIP001
//STRIP001      aDelPam.GetPoint()->nContent = nTxtStt - nOrigTxtStt;
//STRIP001      DeleteSel( aDelPam );
//STRIP001
//STRIP001      if( !aFlags.bSetNumRule )
//STRIP001      {
//STRIP001          String sChgStr( '\t' );
//STRIP001          if( bChgBullet )
//STRIP001              sChgStr.Insert( aFlags.cBullet, 0 );
//STRIP001          pDoc->Insert( aDelPam, sChgStr );
//STRIP001
//STRIP001          SfxItemSet aSet( pDoc->GetAttrPool(), aTxtNodeSetRange );
//STRIP001          if( bChgBullet )
//STRIP001          {
//STRIP001              aDelPam.GetPoint()->nContent = 0;
//STRIP001              aDelPam.SetMark();
//STRIP001              aDelPam.GetMark()->nContent = 1;
//STRIP001              SetAllScriptItem( aSet,
//STRIP001                   SvxFontItem( aFlags.aBulletFont.GetFamily(),
//STRIP001                                aFlags.aBulletFont.GetName(),
//STRIP001                                aFlags.aBulletFont.GetStyleName(),
//STRIP001                                aFlags.aBulletFont.GetPitch(),
//STRIP001                                aFlags.aBulletFont.GetCharSet() ) );
//STRIP001              pDoc->SetFmtItemByAutoFmt( aDelPam, aSet );
//STRIP001              aDelPam.DeleteMark();
//STRIP001              nAutoCorrPos = 2;
//STRIP001              aSet.ClearItem();
//STRIP001          }
//STRIP001          SvxTabStopItem aTStops;     aTStops.Insert( SvxTabStop( 0 ));
//STRIP001          aSet.Put( aTStops );
//STRIP001          pDoc->SetFmtItemByAutoFmt( aDelPam, aSet );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( bBreak )
//STRIP001  {
//STRIP001      AutoCorrect( nAutoCorrPos );       /* Offset wegen Bullet + Tab */
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  const SwTxtNode* pNxtNd = GetNextNode();
//STRIP001  while( CanJoin( pNxtNd ) &&
//STRIP001          nLvl == CalcLevel( *pNxtNd ) )
//STRIP001  {
//STRIP001      SetRedlineTxt( STR_AUTOFMTREDL_DEL_MORELINES );
//STRIP001      bBreak = !IsFastFullLine( *pNxtNd ) || IsBlanksInString( *pNxtNd ) ||
//STRIP001              IsSentenceAtEnd( *pNxtNd );
//STRIP001      if( DeleteAktNxtPara( pNxtNd->GetTxt() ) )
//STRIP001          pDoc->Insert( aDelPam, ' ' );
//STRIP001      if( bBreak )
//STRIP001          break;
//STRIP001      pNxtNd = GetNextNode();
//STRIP001  }
//STRIP001  DeleteAktPara( FALSE, TRUE );
//STRIP001  AutoCorrect( nAutoCorrPos );
//STRIP001 }


//STRIP001 void SwAutoFormat::BuildNegIndent( SwTwips nSpaces )
//STRIP001 {
//STRIP001  SetRedlineTxt( STR_AUTOFMTREDL_SET_TMPL_NEG_INDENT );
//STRIP001  // Test auf Gegenueberstellung:
//STRIP001  // (n Worte, durch Space/Tabs getrennt, mit gleicher
//STRIP001  //   Einrueckung in der 2.Zeile)
//STRIP001
//STRIP001  // lese alle nachfolgenden Absaetze die zu dieser Aufzaehlung gehoeren
//STRIP001  BOOL bBreak = TRUE;
//STRIP001  xub_StrLen nSpacePos, nTxtPos = GetBigIndent( nSpacePos );
//STRIP001  if( bMoreLines )
//STRIP001      DelMoreLinesBlanks( TRUE );
//STRIP001  else
//STRIP001      bBreak = !IsFastFullLine( *pAktTxtNd ) ||
//STRIP001                  ( !nTxtPos && IsBlanksInString( *pAktTxtNd )) ||
//STRIP001                  IsSentenceAtEnd( *pAktTxtNd );
//STRIP001
//STRIP001  SetColl( nTxtPos
//STRIP001              ? RES_POOLCOLL_CONFRONTATION
//STRIP001              : RES_POOLCOLL_TEXT_NEGIDENT );
//STRIP001
//STRIP001  if( nTxtPos )
//STRIP001  {
//STRIP001      const String& rStr = pAktTxtNd->GetTxt();
//STRIP001      BOOL bInsTab = TRUE;
//STRIP001
//STRIP001      if( '\t' == rStr.GetChar( nSpacePos+1 ))       // ein Tab, das belassen wir
//STRIP001      {
//STRIP001          --nSpacePos;
//STRIP001          bInsTab = FALSE;
//STRIP001      }
//STRIP001
//STRIP001      xub_StrLen nSpaceStt = nSpacePos;
//STRIP001      while( nSpaceStt && IsSpace( rStr.GetChar( --nSpaceStt ) ) )
//STRIP001          ;
//STRIP001      ++nSpaceStt;
//STRIP001
//STRIP001      if( bInsTab && '\t' == rStr.GetChar( nSpaceStt ) )      // ein Tab, das belassen wir
//STRIP001      {
//STRIP001          ++nSpaceStt;
//STRIP001          bInsTab = FALSE;
//STRIP001      }
//STRIP001
//STRIP001
//STRIP001      aDelPam.DeleteMark();
//STRIP001      aDelPam.GetPoint()->nNode = aNdIdx;
//STRIP001      aDelPam.GetPoint()->nContent.Assign( pAktTxtNd, nSpacePos );
//STRIP001
//STRIP001 #if 0
//STRIP001 // nicht auf den akt. Einzug setzen, sondern Vorlagen benutzen
//STRIP001      // das Attr. setzen
//STRIP001      // hier sollte die richtige Vorlage benutzt werden !!!
//STRIP001      SvxLRSpaceItem aLSpace;
//STRIP001      aLSpace.SetTxtFirstLineOfst( -(SwTwips)nTxtPos );
//STRIP001      aLSpace.SetTxtLeft( nTxtPos );
//STRIP001      pDoc->Insert( aDelPam, aLSpace );
//STRIP001 #endif
//STRIP001      // alten Spaces, usw. loeschen
//STRIP001      if( nSpaceStt < nSpacePos )
//STRIP001      {
//STRIP001          aDelPam.SetMark();
//STRIP001          aDelPam.GetMark()->nContent = nSpaceStt;
//STRIP001          DeleteSel( aDelPam );
//STRIP001          if( bInsTab )
//STRIP001              pDoc->Insert( aDelPam, '\t' );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( !bBreak )
//STRIP001  {
//STRIP001      SetRedlineTxt( STR_AUTOFMTREDL_DEL_MORELINES );
//STRIP001      SwTxtFrmInfo aFInfo( pAktTxtFrm );
//STRIP001      const SwTxtNode* pNxtNd = GetNextNode();
//STRIP001      while(  CanJoin( pNxtNd ) &&
//STRIP001              20 < Abs( (long)(nSpaces - aFInfo.SetFrm(
//STRIP001                              GetFrm( *pNxtNd ) ).GetLineStart() ))
//STRIP001          )
//STRIP001      {
//STRIP001          bBreak = !IsFastFullLine( *pNxtNd ) ||
//STRIP001                  IsBlanksInString( *pNxtNd ) ||
//STRIP001                  IsSentenceAtEnd( *pNxtNd );
//STRIP001          if( DeleteAktNxtPara( pNxtNd->GetTxt() ) )
//STRIP001              pDoc->Insert( aDelPam, ' ' );
//STRIP001          if( bBreak )
//STRIP001              break;
//STRIP001          pNxtNd = GetNextNode();
//STRIP001      }
//STRIP001  }
//STRIP001  DeleteAktPara( TRUE, TRUE );
//STRIP001  AutoCorrect();
//STRIP001 }


//STRIP001 void SwAutoFormat::BuildHeadLine( USHORT nLvl )
//STRIP001 {
//STRIP001  if( aFlags.bWithRedlining )
//STRIP001  {
//STRIP001      String sTxt( *ViewShell::GetShellRes()->GetAutoFmtNameLst()[
//STRIP001                                  STR_AUTOFMTREDL_SET_TMPL_HEADLINE ] );
//STRIP001      sTxt.SearchAndReplace( String::CreateFromAscii(
//STRIP001                                  RTL_CONSTASCII_STRINGPARAM( "$(ARG1)" )),
//STRIP001                              String::CreateFromInt32( nLvl + 1 ) );
//STRIP001      pDoc->SetAutoFmtRedlineComment( &sTxt );
//STRIP001  }
//STRIP001
//STRIP001  SetColl( RES_POOLCOLL_HEADLINE1 + nLvl, TRUE );
//STRIP001  if( aFlags.bAFmtByInput )
//STRIP001  {
//STRIP001      SwTxtFmtColl& rNxtColl = pAktTxtNd->GetTxtColl()->GetNextTxtFmtColl();
//STRIP001
//STRIP001      DelPrevPara();
//STRIP001
//STRIP001      DeleteAktPara( TRUE, FALSE );
//STRIP001      DeleteAktNxtPara( aEmptyStr );
//STRIP001
//STRIP001      aDelPam.DeleteMark();
//STRIP001      aDelPam.GetPoint()->nNode = aNdIdx.GetIndex() + 1;
//STRIP001      aDelPam.GetPoint()->nContent.Assign( aDelPam.GetCntntNode(), 0 );
//STRIP001      pDoc->SetTxtFmtColl( aDelPam, &rNxtColl );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      DeleteAktPara( TRUE, TRUE );
//STRIP001      AutoCorrect();
//STRIP001  }
//STRIP001 }


        // dann lasse doch mal das AutoCorrect auf den akt. TextNode los
//STRIP001 void SwAutoFormat::AutoCorrect( xub_StrLen nPos )
//STRIP001 {
//STRIP001  if( aFlags.bAFmtByInput ||
//STRIP001      (!aFlags.bAutoCorrect && !aFlags.bReplaceQuote &&
//STRIP001      !aFlags.bCptlSttSntnc && !aFlags.bCptlSttWrd &&
//STRIP001      !aFlags.bChgFracionSymbol && !aFlags.bChgOrdinalNumber &&
//STRIP001      !aFlags.bChgToEnEmDash && !aFlags.bSetINetAttr &&
//STRIP001      !aFlags.bChgWeightUnderl) )
//STRIP001      return;
//STRIP001
//STRIP001  const String* pTxt = &pAktTxtNd->GetTxt();
//STRIP001  if( nPos >= pTxt->Len() )
//STRIP001      return;
//STRIP001
//STRIP001  BOOL bGetLanguage = aFlags.bChgOrdinalNumber ||
//STRIP001                      aFlags.bChgToEnEmDash || aFlags.bSetINetAttr ||
//STRIP001                      aFlags.bCptlSttWrd || aFlags.bCptlSttSntnc;
//STRIP001
//STRIP001
//STRIP001  aDelPam.DeleteMark();
//STRIP001  aDelPam.GetPoint()->nNode = aNdIdx;
//STRIP001  aDelPam.GetPoint()->nContent.Assign( pAktTxtNd, 0 );
//STRIP001
//STRIP001  SwAutoCorrDoc aACorrDoc( *pEditShell, aDelPam );
//STRIP001  SvxAutoCorrect* pATst = OFF_APP()->GetAutoCorrect();
//STRIP001
//STRIP001  SwTxtFrmInfo aFInfo( 0 );
//STRIP001
//STRIP001  xub_StrLen nSttPos, nLastBlank = nPos;
//STRIP001  BOOL bFirst = aFlags.bCptlSttSntnc, bFirstSent = bFirst;
//STRIP001  sal_Unicode cChar;
//STRIP001
//STRIP001  CharClass& rAppCC = GetAppCharClass();
//STRIP001
//STRIP001  do {
//STRIP001      while( nPos < pTxt->Len() && IsSpace( cChar = pTxt->GetChar( nPos ) ))
//STRIP001          ++nPos;
//STRIP001      if( nPos == pTxt->Len() )
//STRIP001          break;      // das wars
//STRIP001
//STRIP001      if( aFlags.bReplaceQuote &&
//STRIP001          ( '\"' == cChar || '\'' == cChar ) &&
//STRIP001          ( !nPos || ' ' == pTxt->GetChar( nPos-1 ) ) )
//STRIP001      {
//STRIP001          // --------------------------------------
//STRIP001          // beachte: Sonderfall Symbolfonts !!!
//STRIP001          if( !aFInfo.GetFrm() )
//STRIP001              aFInfo.SetFrm( GetFrm( *pAktTxtNd ) );
//STRIP001          if( !aFInfo.IsBullet( nPos ))
//STRIP001          {
//STRIP001              SetRedlineTxt( STR_AUTOFMTREDL_TYPO );
//STRIP001              aDelPam.GetPoint()->nContent = nPos;
//STRIP001              BOOL bSetHardBlank = FALSE;
//STRIP001
//STRIP001              String sReplace( pATst->GetQuote( aACorrDoc,
//STRIP001                                  nPos, cChar, TRUE ));
//STRIP001
//STRIP001              aDelPam.SetMark();
//STRIP001              aDelPam.GetPoint()->nContent = nPos+1;
//STRIP001              if( 2 == sReplace.Len() && ' ' == sReplace.GetChar( 1 ))
//STRIP001              {
//STRIP001                  sReplace.Erase( 1 );
//STRIP001                  bSetHardBlank = TRUE;
//STRIP001              }
//STRIP001              pDoc->Replace( aDelPam, sReplace, FALSE );
//STRIP001
//STRIP001              if( aFlags.bWithRedlining )
//STRIP001              {
//STRIP001                  aNdIdx = aDelPam.GetPoint()->nNode;
//STRIP001                  pAktTxtNd = aNdIdx.GetNode().GetTxtNode();
//STRIP001                  pTxt = &pAktTxtNd->GetTxt();
//STRIP001                  aDelPam.SetMark();
//STRIP001                  aFInfo.SetFrm( 0 );
//STRIP001              }
//STRIP001
//STRIP001              nPos += sReplace.Len() - 1;
//STRIP001              aDelPam.DeleteMark();
//STRIP001              if( bSetHardBlank )
//STRIP001              {
//STRIP001                  pDoc->Insert( aDelPam, CHAR_HARDBLANK );
//STRIP001                  ++nPos;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      int bCallACorr = FALSE;
//STRIP001      int bBreak = 0;
//STRIP001      if( nPos && IsSpace( pTxt->GetChar( nPos-1 )))
//STRIP001          nLastBlank = nPos;
//STRIP001      for( nSttPos = nPos; !bBreak && nPos < pTxt->Len(); ++nPos )
//STRIP001          switch( cChar = pTxt->GetChar( nPos ) )
//STRIP001          {
//STRIP001          case '\"':
//STRIP001          case '\'':
//STRIP001              if( aFlags.bReplaceQuote )
//STRIP001              {
//STRIP001                  // --------------------------------------
//STRIP001                  // beachte: Sonderfall Symbolfonts !!!
//STRIP001                  if( !aFInfo.GetFrm() )
//STRIP001                      aFInfo.SetFrm( GetFrm( *pAktTxtNd ) );
//STRIP001                  if( !aFInfo.IsBullet( nPos ))
//STRIP001                  {
//STRIP001                      SetRedlineTxt( STR_AUTOFMTREDL_TYPO );
//STRIP001                      BOOL bSetHardBlank = FALSE;
//STRIP001                      aDelPam.GetPoint()->nContent = nPos;
//STRIP001                      String sReplace( pATst->GetQuote( aACorrDoc,
//STRIP001                                                  nPos, cChar, FALSE ));
//STRIP001
//STRIP001                      if( 2 == sReplace.Len() && ' ' == sReplace.GetChar( 0 ))
//STRIP001                      {
//STRIP001                          sReplace.Erase( 0, 1 );
//STRIP001                          bSetHardBlank = TRUE;
//STRIP001                      }
//STRIP001
//STRIP001                      aDelPam.SetMark();
//STRIP001                      aDelPam.GetPoint()->nContent = nPos+1;
//STRIP001                      pDoc->Replace( aDelPam, sReplace, FALSE );
//STRIP001
//STRIP001                      if( aFlags.bWithRedlining )
//STRIP001                      {
//STRIP001                          aNdIdx = aDelPam.GetPoint()->nNode;
//STRIP001                          pAktTxtNd = aNdIdx.GetNode().GetTxtNode();
//STRIP001                          pTxt = &pAktTxtNd->GetTxt();
//STRIP001                          aDelPam.SetMark();
//STRIP001                          aDelPam.DeleteMark();
//STRIP001                          aFInfo.SetFrm( 0 );
//STRIP001                      }
//STRIP001
//STRIP001                      nPos += sReplace.Len() - 1;
//STRIP001                      aDelPam.DeleteMark();
//STRIP001
//STRIP001                      if( bSetHardBlank )
//STRIP001                      {
//STRIP001                          aDelPam.GetPoint()->nContent = nPos;
//STRIP001                          pDoc->Insert( aDelPam, CHAR_HARDBLANK );
//STRIP001                          aDelPam.GetPoint()->nContent = ++nPos;
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001              break;
//STRIP001          case '*':
//STRIP001          case '_':
//STRIP001              if( aFlags.bChgWeightUnderl )
//STRIP001              {
//STRIP001                  // --------------------------------------
//STRIP001                  // beachte: Sonderfall Symbolfonts !!!
//STRIP001                  if( !aFInfo.GetFrm() )
//STRIP001                      aFInfo.SetFrm( GetFrm( *pAktTxtNd ) );
//STRIP001                  if( !aFInfo.IsBullet( nPos ))
//STRIP001                  {
//STRIP001                      SetRedlineTxt( '*' == cChar
//STRIP001                                          ? STR_AUTOFMTREDL_BOLD
//STRIP001                                          : STR_AUTOFMTREDL_UNDER );
//STRIP001
//STRIP001                      sal_Unicode cBlank = nSttPos ? pTxt->GetChar(nSttPos - 1) : 0;
//STRIP001                      aDelPam.GetPoint()->nContent = nPos;
//STRIP001
//STRIP001                      if( pATst->FnChgWeightUnderl( aACorrDoc, *pTxt,
//STRIP001                                                          nSttPos, nPos ))
//STRIP001                      {
//STRIP001                             if( aFlags.bWithRedlining )
//STRIP001                             {
//STRIP001                                 aNdIdx = aDelPam.GetPoint()->nNode;
//STRIP001                                 pAktTxtNd = aNdIdx.GetNode().GetTxtNode();
//STRIP001                                 pTxt = &pAktTxtNd->GetTxt();
//STRIP001                                 aDelPam.SetMark();
//STRIP001                                 aDelPam.DeleteMark();
//STRIP001                                 aFInfo.SetFrm( 0 );
//STRIP001                             }
//STRIP001                          nPos = aDelPam.GetPoint()->nContent.GetIndex() - 1;
//STRIP001                          // wurde vorm Start ein Zeichen entfernt?
//STRIP001                          if( cBlank && cBlank != pTxt->GetChar(nSttPos - 1) )
//STRIP001                              --nSttPos;
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001          case '.':
//STRIP001          case '!':
//STRIP001          case '?':
//STRIP001              if( aFlags.bCptlSttSntnc )
//STRIP001                  bFirstSent = TRUE;
//STRIP001 //alle Wortrenner loesen die Autokorrektur aus!
//STRIP001 //               break;
//STRIP001
//STRIP001          default:
//STRIP001 //alle Wortrenner loesen die Autokorrektur aus!
//STRIP001 //           case ' ':
//STRIP001 //           case '\t':
//STRIP001              if( !( rAppCC.isLetterNumeric( *pTxt, nPos )
//STRIP001                         || '/' == cChar )) //  '/' should not be a word seperator (e.g. '1/2' needs to be handled as one word for replacement)
//STRIP001              {
//STRIP001                  --nPos;     // ++nPos von dem for ungueltig machen !
//STRIP001                  ++bBreak;
//STRIP001              }
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001      if( nPos == nSttPos )
//STRIP001      {
//STRIP001          if( ++nPos == pTxt->Len() )
//STRIP001              bCallACorr = TRUE;
//STRIP001      }
//STRIP001      else
//STRIP001          bCallACorr = TRUE;
//STRIP001
//STRIP001
//STRIP001      if( bCallACorr )
//STRIP001      {
//STRIP001          bCallACorr = FALSE;
//STRIP001          aDelPam.GetPoint()->nContent = nPos;
//STRIP001          SetRedlineTxt( STR_AUTOFMTREDL_USE_REPLACE );
//STRIP001          if( aFlags.bAutoCorrect &&
//STRIP001              aACorrDoc.ChgAutoCorrWord( nSttPos, nPos, *pATst, 0 ) )
//STRIP001          {
//STRIP001              nPos = aDelPam.GetPoint()->nContent.GetIndex();
//STRIP001
//STRIP001              if( aFlags.bWithRedlining )
//STRIP001              {
//STRIP001                  aNdIdx = aDelPam.GetPoint()->nNode;
//STRIP001                  pAktTxtNd = aNdIdx.GetNode().GetTxtNode();
//STRIP001                  pTxt = &pAktTxtNd->GetTxt();
//STRIP001                  aDelPam.SetMark();
//STRIP001                  aDelPam.DeleteMark();
//STRIP001              }
//STRIP001
//STRIP001              continue;       // nichts weiter mehr abpruefen
//STRIP001          }
//STRIP001
//STRIP001          LanguageType eLang = (bGetLanguage && pAktTxtNd)
//STRIP001                                         ? pAktTxtNd->GetLang( nSttPos )
//STRIP001                                         : LANGUAGE_SYSTEM;
//STRIP001
//STRIP001          if( ( aFlags.bChgFracionSymbol &&
//STRIP001                  SetRedlineTxt( STR_AUTOFMTREDL_FRACTION ) &&
//STRIP001                  pATst->FnChgFractionSymbol( aACorrDoc, *pTxt, nSttPos, nPos ) ) ||
//STRIP001              ( aFlags.bChgOrdinalNumber &&
//STRIP001                  SetRedlineTxt( STR_AUTOFMTREDL_ORDINAL ) &&
//STRIP001                  pATst->FnChgOrdinalNumber( aACorrDoc, *pTxt, nSttPos, nPos, eLang ) ) ||
//STRIP001              ( aFlags.bChgToEnEmDash &&
//STRIP001                  SetRedlineTxt( STR_AUTOFMTREDL_DASH ) &&
//STRIP001                  pATst->FnChgToEnEmDash( aACorrDoc, *pTxt, nSttPos, nPos, eLang ) ) ||
//STRIP001              ( aFlags.bSetINetAttr &&
//STRIP001                  ( nPos == pTxt->Len() || IsSpace( pTxt->GetChar( nPos )) ) &&
//STRIP001                  SetRedlineTxt( STR_AUTOFMTREDL_DETECT_URL ) &&
//STRIP001                  pATst->FnSetINetAttr( aACorrDoc, *pTxt, nLastBlank, nPos, eLang ) ) )
//STRIP001                  nPos = aDelPam.GetPoint()->nContent.GetIndex();
//STRIP001          else
//STRIP001          {
//STRIP001              // Zwei Grossbuchstaben am Wort-Anfang ??
//STRIP001              if( aFlags.bCptlSttWrd )
//STRIP001              {
//STRIP001                  SetRedlineTxt( STR_AUTOFMTREDL_CPTL_STT_WORD );
//STRIP001                  pATst->FnCptlSttWrd( aACorrDoc, *pTxt, nSttPos, nPos, eLang );
//STRIP001              }
//STRIP001              // Grossbuchstabe am Satz-Anfang ??
//STRIP001              if( aFlags.bCptlSttSntnc && bFirst )
//STRIP001              {
//STRIP001                  SetRedlineTxt( STR_AUTOFMTREDL_CPTL_STT_SENT );
//STRIP001                  pATst->FnCptlSttSntnc( aACorrDoc, *pTxt, TRUE, nSttPos, nPos, eLang);
//STRIP001                  bFirst = FALSE;
//STRIP001              }
//STRIP001
//STRIP001              bFirst = bFirstSent;
//STRIP001              bFirstSent = FALSE;
//STRIP001
//STRIP001              if( aFlags.bWithRedlining )
//STRIP001              {
//STRIP001                  aNdIdx = aDelPam.GetPoint()->nNode;
//STRIP001                  pAktTxtNd = aNdIdx.GetNode().GetTxtNode();
//STRIP001                  pTxt = &pAktTxtNd->GetTxt();
//STRIP001                  aDelPam.SetMark();
//STRIP001                  aDelPam.DeleteMark();
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  } while( nPos < pTxt->Len() );
//STRIP001  ClearRedlineTxt();
//STRIP001 }


//STRIP001 SwAutoFormat::SwAutoFormat( SwEditShell* pEdShell, SvxSwAutoFmtFlags& rFlags,
//STRIP001                          SwNodeIndex* pSttNd, SwNodeIndex* pEndNd )
//STRIP001  : aFlags( rFlags ),
//STRIP001  aDelPam( pEdShell->GetDoc()->GetNodes().GetEndOfExtras() ),
//STRIP001  aNdIdx( pEdShell->GetDoc()->GetNodes().GetEndOfExtras(), +1 ),
//STRIP001  aEndNdIdx( pEdShell->GetDoc()->GetNodes().GetEndOfContent() ),
//STRIP001  pEditShell( pEdShell ),
//STRIP001  pDoc( pEdShell->GetDoc() ),
//STRIP001  pAktTxtNd( 0 ), pAktTxtFrm( 0 ),
//STRIP001  pCharClass( 0 ),
//STRIP001  nRedlAutoFmtSeqId( 0 )
//STRIP001 {
//STRIP001  ASSERT( (pSttNd && pEndNd) || (!pSttNd && !pEndNd),
//STRIP001          "Kein Bereich angegeben" );
//STRIP001
//STRIP001  if( aFlags.bSetNumRule && !aFlags.bAFmtByInput )
//STRIP001      aFlags.bSetNumRule = FALSE;
//STRIP001
//STRIP001  BOOL bReplaceStyles = !aFlags.bAFmtByInput || aFlags.bReplaceStyles;
//STRIP001
//STRIP001  const SwTxtNode* pNxtNd;
//STRIP001  BOOL bNxtEmpty, bNxtAlpha;
//STRIP001  USHORT nNxtLevel;
//STRIP001
//STRIP001  // setze den Bereich zum Autoformatieren
//STRIP001  if( pSttNd )
//STRIP001  {
//STRIP001      aNdIdx = *pSttNd;
//STRIP001      aNdIdx--;           // fuer GoNextPara, ein Absatz davor
//STRIP001      aEndNdIdx = *pEndNd;
//STRIP001      aEndNdIdx++;
//STRIP001
//STRIP001      // teste den vorhergehenden TextNode
//STRIP001      pNxtNd = aNdIdx.GetNode().GetTxtNode();
//STRIP001      bEmptyLine = !pNxtNd ||
//STRIP001                  IsEmptyLine( *pNxtNd ) ||
//STRIP001                  IsNoAlphaLine( *pNxtNd );
//STRIP001  }
//STRIP001  else
//STRIP001      bEmptyLine = TRUE;      // am Dokument Anfang
//STRIP001
//STRIP001  bEnde = FALSE;
//STRIP001
//STRIP001  // setze die Werte fuer die Prozent-Anzeige
//STRIP001  nEndNdIdx = aEndNdIdx.GetIndex();
//STRIP001
//STRIP001  if( !aFlags.bAFmtByInput )
//STRIP001      ::StartProgress( STR_STATSTR_AUTOFORMAT, aNdIdx.GetIndex(),
//STRIP001                       nEndNdIdx = aEndNdIdx.GetIndex(),
//STRIP001                       pDoc->GetDocShell() );
//STRIP001
//STRIP001  SwRedlineMode eRedlMode = pDoc->GetRedlineMode(), eOldMode = eRedlMode;
//STRIP001  if( aFlags.bWithRedlining )
//STRIP001  {
//STRIP001      pDoc->SetAutoFmtRedline( TRUE );
//STRIP001      eRedlMode = SwRedlineMode(REDLINE_ON | REDLINE_SHOW_INSERT );
//STRIP001      eOldMode = SwRedlineMode( eOldMode | REDLINE_SHOW_DELETE | REDLINE_SHOW_INSERT );
//STRIP001  }
//STRIP001  else
//STRIP001      eRedlMode = SwRedlineMode( REDLINE_SHOW_INSERT | REDLINE_IGNORE );
//STRIP001  pDoc->SetRedlineMode( eRedlMode );
//STRIP001
//STRIP001     // save undo state (might be turned off)
//STRIP001     sal_Bool bUndoState = pDoc->DoesUndo();
//STRIP001
//STRIP001  // wenn mehrere Zeilen, dann erstmal nicht mit
//STRIP001  // dem nachfolgenden Absatz zusammenfassen.
//STRIP001  bMoreLines = FALSE;
//STRIP001
//STRIP001  nLastCalcHeadLvl = nLastCalcEnumLvl = 0;
//STRIP001  nLastHeadLvl = nLastEnumLvl = USHRT_MAX;
//STRIP001  USHORT nLevel, nDigitLvl;
//STRIP001
//STRIP001  // defaulten
//STRIP001  SwTxtFrmInfo aFInfo( 0 );
//STRIP001
//STRIP001  // das ist unser Automat fuer die Auto-Formatierung
//STRIP001  eStat = READ_NEXT_PARA;
//STRIP001  while( !bEnde )
//STRIP001  {
//STRIP001         // #95884# limit redline array size to prevent overflow and to conserve
//STRIP001         // memory
//STRIP001         if( pDoc->HasTooManyUndos() )
//STRIP001         {
//STRIP001             DBG_ASSERT( bUndoState, "undo overflow without undo?" );
//STRIP001
//STRIP001             //ask user
//STRIP001             short nResult = m_nActionWhileAutoformatUndoBufferOverflow; // TODO: #102007# read the last decision of the user from configuration
//STRIP001             if(m_bAskForCancelUndoWhileBufferOverflow) // #102007# TODO: read the last decision of the user from configuration
//STRIP001             {
//STRIP001              Window* pParent = pEditShell?pEditShell->GetWin():NULL;
//STRIP001                 WarningBox aWarning( pParent,SW_RES(MSG_DISABLE_UNDO_QUESTION));
//STRIP001                 aWarning.SetDefaultCheckBoxText();
//STRIP001                 USHORT nDefaultButton = nResult==RET_YES?BUTTONID_YES:(nResult==RET_NO?BUTTONID_NO:BUTTONID_CANCEL);
//STRIP001                 aWarning.SetFocusButton(nDefaultButton);
//STRIP001                 nResult      = aWarning.Execute();
//STRIP001                 m_bAskForCancelUndoWhileBufferOverflow = !aWarning.GetCheckBoxState();
//STRIP001                 m_nActionWhileAutoformatUndoBufferOverflow = nResult;
//STRIP001                 // TODO: #102007# store m_bAskForCancelUndoWhileBufferOverflow in configuration
//STRIP001                 // TODO: #102007# store m_nActionWhileAutoformatUndoBufferOverflow in configuration
//STRIP001             }
//STRIP001
//STRIP001             DBG_ASSERT( (nResult == RET_YES) || (nResult == RET_CANCEL) || (nResult == RET_NO),
//STRIP001                         "unexpected result" );
//STRIP001
//STRIP001             if( nResult == RET_YES )
//STRIP001             {
//STRIP001                 // turn off undo and continue
//STRIP001                 pDoc->DoUndo( sal_False );
//STRIP001                 pDoc->DelAllUndoObj();
//STRIP001             }
//STRIP001             else if( nResult == RET_NO )
//STRIP001             {
//STRIP001              //stop autoformatting and keep changes
//STRIP001                 eStat = IS_ENDE;
//STRIP001             }
//STRIP001             else if( nResult == RET_CANCEL )
//STRIP001          {
//STRIP001              //cancel autoformatting and undo changes
//STRIP001              eStat = IS_ENDE;
//STRIP001
//STRIP001              // TODO: #102004# undo changes
//STRIP001          }
//STRIP001         }
//STRIP001
//STRIP001      switch( eStat )
//STRIP001      {
//STRIP001      case READ_NEXT_PARA:
//STRIP001          {
//STRIP001              GoNextPara();
//STRIP001              eStat = bEnde ? IS_ENDE : TST_EMPTY_LINE;
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case TST_EMPTY_LINE:
//STRIP001          if( IsEmptyLine( *pAktTxtNd ) )
//STRIP001          {
//STRIP001              if( aFlags.bDelEmptyNode && !HasObjects( *pAktTxtNd ) )
//STRIP001              {
//STRIP001                  bEmptyLine = TRUE;
//STRIP001                  ULONG nOldCnt = pDoc->GetNodes().Count();
//STRIP001                  DelEmptyLine();
//STRIP001                  // wurde wiklich ein Node geloescht ?
//STRIP001                  if( nOldCnt != pDoc->GetNodes().Count() )
//STRIP001                      aNdIdx--;       // nicht den naechsten Absatz ueberspringen
//STRIP001              }
//STRIP001              eStat = READ_NEXT_PARA;
//STRIP001          }
//STRIP001          else
//STRIP001              eStat = TST_ALPHA_LINE;
//STRIP001          break;
//STRIP001
//STRIP001      case TST_ALPHA_LINE:
//STRIP001          if( IsNoAlphaLine( *pAktTxtNd ))
//STRIP001          {
//STRIP001              // erkenne eine Tabellendefinition +---+---+
//STRIP001              if( aFlags.bAFmtByInput && aFlags.bCreateTable && DoTable() )
//STRIP001              {
//STRIP001                  //JP 30.09.96: das DoTable() verlaesst sich auf das
//STRIP001                  //              Pop und Move - Crsr nach dem AutoFormat!
//STRIP001                  pEdShell->Pop( FALSE );
//STRIP001                  *pEdShell->GetCrsr() = aDelPam;
//STRIP001                  pEdShell->Push();
//STRIP001
//STRIP001                  eStat = IS_ENDE;
//STRIP001                  break;
//STRIP001              }
//STRIP001
//STRIP001              // dann teste mal auf 3 "---" oder "===". In dem Fall
//STRIP001              // soll der vorherige Absatz unterstrichen und dieser
//STRIP001              // geloescht werden!
//STRIP001              if( !DoUnderline() && bReplaceStyles )
//STRIP001              {
//STRIP001                  SetColl( RES_POOLCOLL_STANDARD, TRUE );
//STRIP001                  bEmptyLine = TRUE;
//STRIP001              }
//STRIP001              eStat = READ_NEXT_PARA;
//STRIP001          }
//STRIP001          else
//STRIP001              eStat = GET_ALL_INFO;
//STRIP001          break;
//STRIP001
//STRIP001      case GET_ALL_INFO:
//STRIP001          {
//STRIP001              if( pAktTxtNd->GetNumRule() )
//STRIP001              {
//STRIP001                  // in Numerierung nichts machen, zum naechsten
//STRIP001                  bEmptyLine = FALSE;
//STRIP001                  eStat = READ_NEXT_PARA;
//STRIP001                  // loesche alle Blanks am Anfang/Ende
//STRIP001                  // und alle mitten drin
//STRIP001                  //JP 29.04.98: erstmal nur alle "mitten drin".
//STRIP001                  DelMoreLinesBlanks( FALSE );
//STRIP001                  break;
//STRIP001              }
//STRIP001
//STRIP001              aFInfo.SetFrm( pAktTxtFrm );
//STRIP001
//STRIP001              // erstmal: wurden schon mal entsprechende Vorlagen
//STRIP001              //          vergeben, so behalte die bei, gehe zum
//STRIP001              //          naechsten Node.
//STRIP001              USHORT nPoolId = pAktTxtNd->GetTxtColl()->GetPoolFmtId();
//STRIP001              if( IsPoolUserFmt( nPoolId )
//STRIP001                      ? !aFlags.bChgUserColl
//STRIP001                      : ( RES_POOLCOLL_STANDARD != nPoolId &&
//STRIP001                         ( !aFlags.bAFmtByInput ||
//STRIP001                          (RES_POOLCOLL_TEXT_MOVE != nPoolId &&
//STRIP001                           RES_POOLCOLL_TEXT != nPoolId )) ))
//STRIP001              {
//STRIP001                  eStat = HAS_FMTCOLL;
//STRIP001                  break;
//STRIP001              }
//STRIP001
//STRIP001              // teste auf Harte oder aus Vorlagen gesetzte LRSpaces
//STRIP001              if( IsPoolUserFmt( nPoolId ) ||
//STRIP001                  RES_POOLCOLL_STANDARD == nPoolId )
//STRIP001              {
//STRIP001                  short nSz;
//STRIP001                  SvxLRSpaceItem* pLRSpace;
//STRIP001                  if( SFX_ITEM_SET == pAktTxtNd->GetSwAttrSet().
//STRIP001                      GetItemState( RES_LR_SPACE, TRUE,
//STRIP001                                      (const SfxPoolItem**)&pLRSpace ) &&
//STRIP001                      ( 0 != (nSz = pLRSpace->GetTxtFirstLineOfst()) ||
//STRIP001                          0 != pLRSpace->GetTxtLeft() ) )
//STRIP001                  {
//STRIP001                      // Ausnahme: Numerierun/Aufzaehlung kann mit Einzug
//STRIP001                      //      existieren!!
//STRIP001                      if( IsEnumericChar( *pAktTxtNd ))
//STRIP001                      {
//STRIP001                          nLevel = CalcLevel( *pAktTxtNd, &nDigitLvl );
//STRIP001                          if( nLevel >= MAXLEVEL )
//STRIP001                              nLevel = MAXLEVEL-1;
//STRIP001                          BuildEnum( nLevel, nDigitLvl );
//STRIP001                          eStat = READ_NEXT_PARA;
//STRIP001                          break;
//STRIP001                      }
//STRIP001
//STRIP001
//STRIP001                      // nie zusammenfassen, so belassen
//STRIP001                      // (Opt. vielleicht als Ausnahmen nur Einzug)
//STRIP001                      bMoreLines = TRUE;
//STRIP001
//STRIP001                      if( bReplaceStyles )
//STRIP001                      {
//STRIP001                          // dann setze doch eine unserer Vorlagen
//STRIP001                          if( 0 < nSz )           // positiver 1. Zeileneinzug
//STRIP001                              BuildIndent();
//STRIP001                          else if( 0 > nSz )      // negativer 1. Zeileneinzug
//STRIP001                              BuildNegIndent( aFInfo.GetLineStart() );
//STRIP001                          else if( pLRSpace->GetTxtLeft() )   // ist ein Einzug
//STRIP001                              BuildTextIndent();
//STRIP001                      }
//STRIP001                      eStat = READ_NEXT_PARA;
//STRIP001                      break;
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              nLevel = CalcLevel( *pAktTxtNd, &nDigitLvl );
//STRIP001              bMoreLines = !IsOneLine( *pAktTxtNd );
//STRIP001              pNxtNd = GetNextNode();
//STRIP001              if( pNxtNd )
//STRIP001              {
//STRIP001                  bNxtEmpty = IsEmptyLine( *pNxtNd );
//STRIP001                  bNxtAlpha = IsNoAlphaLine( *pNxtNd );
//STRIP001                  nNxtLevel = CalcLevel( *pNxtNd );
//STRIP001
//STRIP001                  if( !bEmptyLine && HasBreakAttr( *pAktTxtNd ) )
//STRIP001                      bEmptyLine = TRUE;
//STRIP001                  if( !bNxtEmpty && HasBreakAttr( *pNxtNd ) )
//STRIP001                      bNxtEmpty = TRUE;
//STRIP001
//STRIP001                  // fuer z.B. selbst definierte Einzuege oder
//STRIP001                  // rechts/zentierte Ausrichtung
//STRIP001 //                   if( !nLevel && 0 != aFInfo.GetLineStart() )
//STRIP001 //                       nLevel = 1;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  bNxtEmpty = FALSE; // TRUE;
//STRIP001                  bNxtAlpha = FALSE;
//STRIP001                  nNxtLevel = 0;
//STRIP001              }
//STRIP001              eStat = !bMoreLines ? IS_ONE_LINE : TST_ENUMERIC;
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case IS_ONE_LINE:
//STRIP001          {
//STRIP001              eStat = TST_ENUMERIC;
//STRIP001              if( !bReplaceStyles )
//STRIP001                  break;
//STRIP001
//STRIP001              String sClrStr( pAktTxtNd->GetTxt() );
//STRIP001
//STRIP001              if( !DelLeadingBlanks( sClrStr ).Len() )
//STRIP001              {
//STRIP001                  bEmptyLine = TRUE;
//STRIP001                  eStat = READ_NEXT_PARA;
//STRIP001                  break;      // naechsten Absatz lesen
//STRIP001              }
//STRIP001
//STRIP001              // Teste auf Ueberschrift
//STRIP001              if( !bEmptyLine || !IsFirstCharCapital( *pAktTxtNd ) ||
//STRIP001                  IsBlanksInString( *pAktTxtNd ) )
//STRIP001                  break;
//STRIP001
//STRIP001              bEmptyLine = FALSE;
//STRIP001              String sEndClrStr( sClrStr );
//STRIP001              xub_StrLen nLen = DelTrailingBlanks( sEndClrStr ).Len();
//STRIP001
//STRIP001              // nicht, dann teste auf Ueberschrift
//STRIP001              if( ':' == sEndClrStr.GetChar( nLen - 1 ) )
//STRIP001              {
//STRIP001 //---------------------------------------------------------------------------
//STRIP001 // Wie ist denn nun die Bedingung fuer die Ueberschrift auf Ebene 3 ??
//STRIP001 // Zur Zeit: generell wenn am Ende ein ':' ist.
//STRIP001 //
//STRIP001 //                   if( bNxtEmpty || bNxtAlpha )
//STRIP001 //                       !IsEnumericChar( *pNxtNd ) )
//STRIP001 //---------------------------------------------------------------------------
//STRIP001                  {
//STRIP001                      BuildHeadLine( 2 );
//STRIP001                      eStat = READ_NEXT_PARA;
//STRIP001                      break;
//STRIP001                  }
//STRIP001              }
//STRIP001              else if( 256 <= sEndClrStr.GetChar( nLen-1 ) ||
//STRIP001                       !strchr( ",.;", sEndClrStr.GetChar( nLen-1 )) )
//STRIP001              {
//STRIP001                  if( bNxtEmpty || bNxtAlpha
//STRIP001                      || ( pNxtNd && IsEnumericChar( *pNxtNd ))
//STRIP001
//STRIP001 //---------------------------------------------------------------------------
//STRIP001 // ist zum Verwechseln mit neg. Einzug !!
//STRIP001                      /*|| nLevel < nNxtLevel*/
//STRIP001 //---------------------------------------------------------------------------
//STRIP001
//STRIP001                      )
//STRIP001                  {
//STRIP001                      // wurde Level vom Text vorgegeben ?
//STRIP001 //                       if( USHRT_MAX != nDigitLvl )
//STRIP001 //                           nLevel = nDigitLvl;
//STRIP001
//STRIP001                      // eine Ebene runter ?
//STRIP001                      if( nLevel >= MAXLEVEL )
//STRIP001                          nLevel = MAXLEVEL-1;
//STRIP001
//STRIP001                      if( USHRT_MAX == nLastHeadLvl )
//STRIP001                          nLastHeadLvl = 0;
//STRIP001                      else if( nLastCalcHeadLvl < nLevel )
//STRIP001                      {
//STRIP001                          if( nLastHeadLvl+1 < MAXLEVEL )
//STRIP001                              ++nLastHeadLvl;
//STRIP001                      }
//STRIP001                      // eine Ebene hoch ?
//STRIP001                      else if( nLastCalcHeadLvl > nLevel )
//STRIP001                      {
//STRIP001                          if( nLastHeadLvl )
//STRIP001                              --nLastHeadLvl;
//STRIP001                      }
//STRIP001                      nLastCalcHeadLvl = nLevel;
//STRIP001
//STRIP001                      if( aFlags.bAFmtByInput )
//STRIP001                          BuildHeadLine( nLevel );
//STRIP001                      else
//STRIP001                          BuildHeadLine( nLastHeadLvl );
//STRIP001                      eStat = READ_NEXT_PARA;
//STRIP001                      break;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case TST_ENUMERIC:
//STRIP001          {
//STRIP001              bEmptyLine = FALSE;
//STRIP001              if( IsEnumericChar( *pAktTxtNd ))
//STRIP001              {
//STRIP001                  if( nLevel >= MAXLEVEL )
//STRIP001                      nLevel = MAXLEVEL-1;
//STRIP001                  BuildEnum( nLevel, nDigitLvl );
//STRIP001                  eStat = READ_NEXT_PARA;
//STRIP001              }
//STRIP001 //JP 25.03.96: Vorlagen fuer Einzug zulassen
//STRIP001 //               else if( aFlags.bAFmtByInput )
//STRIP001 //                   eStat = READ_NEXT_PARA;
//STRIP001              else if( bReplaceStyles )
//STRIP001                  eStat = nLevel ? TST_IDENT : TST_NEG_IDENT;
//STRIP001              else
//STRIP001                  eStat = READ_NEXT_PARA;
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case TST_IDENT:
//STRIP001          // Spaces am Anfang, dann teste doch mal auf Einzuege
//STRIP001          if( bMoreLines && nLevel )
//STRIP001          {
//STRIP001              SwTwips nSz = aFInfo.GetFirstIndent();
//STRIP001              if( 0 < nSz )           // positiver 1. Zeileneinzug
//STRIP001                  BuildIndent();
//STRIP001              else if( 0 > nSz )      // negativer 1. Zeileneinzug
//STRIP001                  BuildNegIndent( aFInfo.GetLineStart() );
//STRIP001              else                    // ist ein Einzug
//STRIP001                  BuildTextIndent();
//STRIP001              eStat = READ_NEXT_PARA;
//STRIP001          }
//STRIP001          else if( nLevel && pNxtNd && !bEnde &&
//STRIP001                   !bNxtEmpty && !bNxtAlpha && !nNxtLevel &&
//STRIP001                   !IsEnumericChar( *pNxtNd ) )
//STRIP001          {
//STRIP001              // ist ein Einzug
//STRIP001              BuildIndent();
//STRIP001              eStat = READ_NEXT_PARA;
//STRIP001          }
//STRIP001          else
//STRIP001              eStat = TST_TXT_BODY;
//STRIP001          break;
//STRIP001
//STRIP001      case TST_NEG_IDENT:
//STRIP001          // keine Spaces am Anfang, dann teste doch mal auf neg. Einzuege
//STRIP001          {
//STRIP001              if( bMoreLines && !nLevel )
//STRIP001              {
//STRIP001                  SwTwips nSz = aFInfo.GetFirstIndent();
//STRIP001                  if( 0 < nSz )           // positiver 1. Zeileneinzug
//STRIP001                      BuildIndent();
//STRIP001                  else if( 0 > nSz )      // negativer 1. Zeileneinzug
//STRIP001                      BuildNegIndent( aFInfo.GetLineStart() );
//STRIP001                  else                    // ist ein kein Einzug
//STRIP001                      BuildText();
//STRIP001                  eStat = READ_NEXT_PARA;
//STRIP001              }
//STRIP001              else if( !nLevel && pNxtNd && !bEnde &&
//STRIP001                       !bNxtEmpty && !bNxtAlpha && nNxtLevel &&
//STRIP001                       !IsEnumericChar( *pNxtNd ) )
//STRIP001              {
//STRIP001                  // ist ein neg. Einzug
//STRIP001                  BuildNegIndent( aFInfo.GetLineStart() );
//STRIP001                  eStat = READ_NEXT_PARA;
//STRIP001              }
//STRIP001              else
//STRIP001                  eStat = TST_TXT_BODY;
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case TST_TXT_BODY:
//STRIP001          {
//STRIP001              if( bMoreLines )
//STRIP001              {
//STRIP001                  SwTwips nSz = aFInfo.GetFirstIndent();
//STRIP001                  if( 0 < nSz )           // positiver 1. Zeileneinzug
//STRIP001                      BuildIndent();
//STRIP001                  else if( 0 > nSz )      // negativer 1. Zeileneinzug
//STRIP001                      BuildNegIndent( aFInfo.GetLineStart() );
//STRIP001                  else if( nLevel )       // ist ein Einzug
//STRIP001                      BuildTextIndent();
//STRIP001                  else
//STRIP001                      BuildText();
//STRIP001              }
//STRIP001              else if( nLevel )
//STRIP001                  BuildTextIndent();
//STRIP001              else
//STRIP001                  BuildText();
//STRIP001              eStat = READ_NEXT_PARA;
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case HAS_FMTCOLL:
//STRIP001          {
//STRIP001              // erstmal: wurden schon mal entsprechende Vorlagen
//STRIP001              //          vergeben, so behalte die bei, gehe zum
//STRIP001              //          naechsten Node.
//STRIP001              bEmptyLine = FALSE;
//STRIP001              eStat = READ_NEXT_PARA;
//STRIP001              // loesche alle Blanks am Anfang/Ende
//STRIP001              // und alle mitten drin
//STRIP001              //JP 29.04.98: erstmal nur alle "mitten drin".
//STRIP001              DelMoreLinesBlanks( FALSE );
//STRIP001
//STRIP001              // behandel die harte Attributierung
//STRIP001              if( pAktTxtNd->GetpSwAttrSet() )
//STRIP001              {
//STRIP001                  short nSz;
//STRIP001                  SvxLRSpaceItem* pLRSpace;
//STRIP001                  if( SFX_ITEM_SET == pAktTxtNd->GetpSwAttrSet()->
//STRIP001                      GetItemState( RES_LR_SPACE, FALSE,
//STRIP001                                      (const SfxPoolItem**)&pLRSpace ) &&
//STRIP001                      ( 0 != (nSz = pLRSpace->GetTxtFirstLineOfst()) ||
//STRIP001                          0 != pLRSpace->GetTxtLeft() ) )
//STRIP001                  {
//STRIP001                      // dann setze doch eine unserer Vorlagen
//STRIP001                      if( 0 < nSz )           // positiver 1. Zeileneinzug
//STRIP001                          BuildIndent();
//STRIP001                      else if( 0 > nSz )      // negativer 1. Zeileneinzug
//STRIP001                      {
//STRIP001                          BuildNegIndent( aFInfo.GetLineStart() );
//STRIP001                      }
//STRIP001                      else if( pLRSpace->GetTxtLeft() )   // ist ein Einzug
//STRIP001                          BuildTextIndent();
//STRIP001                      else
//STRIP001                          BuildText();
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case IS_ENDE:
//STRIP001          bEnde = TRUE;
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( aFlags.bWithRedlining )
//STRIP001      pDoc->SetAutoFmtRedline( FALSE );
//STRIP001  pDoc->SetRedlineMode( eOldMode );
//STRIP001
//STRIP001     // restore undo (in case it has been changed)
//STRIP001     pDoc->DoUndo( bUndoState );
//STRIP001
//STRIP001  // Prozent-Anzeige wieder abschalten
//STRIP001  if( !aFlags.bAFmtByInput )
//STRIP001      ::EndProgress( pDoc->GetDocShell() );
//STRIP001 }

//STRIP001 void SwEditShell::AutoFormat( const SvxSwAutoFmtFlags* pAFlags )
//STRIP001 {
//STRIP001  SwWait* pWait = 0;
//STRIP001
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001  StartUndo( UNDO_AUTOFORMAT );
//STRIP001
//STRIP001  SvxSwAutoFmtFlags aAFFlags;     // erst mal default - Werte
//STRIP001  if( pAFlags )                   // oder doch angegeben ??
//STRIP001  {
//STRIP001      aAFFlags = *pAFlags;
//STRIP001      if( !aAFFlags.bAFmtByInput )
//STRIP001          pWait = new SwWait( *GetDoc()->GetDocShell(), TRUE );
//STRIP001  }
//STRIP001
//STRIP001  SwPaM* pCrsr = GetCrsr();
//STRIP001  // es gibt mehr als einen oder ist eine Selektion offen
//STRIP001  if( pCrsr->GetNext() != pCrsr || pCrsr->HasMark() )
//STRIP001  {
//STRIP001      FOREACHPAM_START(this)
//STRIP001          if( PCURCRSR->HasMark() )
//STRIP001          {
//STRIP001              SwAutoFormat aFmt( this, aAFFlags, &PCURCRSR->Start()->nNode,
//STRIP001                                   &PCURCRSR->End()->nNode );
//STRIP001          }
//STRIP001      FOREACHPAM_END()
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SwAutoFormat aFmt( this, aAFFlags );
//STRIP001  }
//STRIP001
//STRIP001  EndUndo( UNDO_AUTOFORMAT );
//STRIP001  EndAllAction();
//STRIP001
//STRIP001  delete pWait;
//STRIP001 }


//STRIP001 void SwEditShell::AutoFmtBySplitNode()
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  SwPaM* pCrsr = GetCrsr();
//STRIP001  if( pCrsr->GetNext() == pCrsr && pCrsr->Move( fnMoveBackward, fnGoNode ) )
//STRIP001  {
//STRIP001      StartAllAction();
//STRIP001      StartUndo( UNDO_AUTOFORMAT );
//STRIP001
//STRIP001      BOOL bRange = FALSE;
//STRIP001      pCrsr->SetMark();
//STRIP001      SwIndex* pCntnt = &pCrsr->GetMark()->nContent;
//STRIP001      if( pCntnt->GetIndex() )
//STRIP001      {
//STRIP001          *pCntnt = 0;
//STRIP001          bRange = TRUE;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // dann einen Node zurueckspringen
//STRIP001          SwNodeIndex aNdIdx( pCrsr->GetMark()->nNode, -1 );
//STRIP001          SwTxtNode* pTxtNd = aNdIdx.GetNode().GetTxtNode();
//STRIP001          if( pTxtNd && pTxtNd->GetTxt().Len() )
//STRIP001          {
//STRIP001              pCntnt->Assign( pTxtNd, 0 );
//STRIP001              pCrsr->GetMark()->nNode = aNdIdx;
//STRIP001              bRange = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if( bRange )
//STRIP001      {
//STRIP001          Push();     // Cursor sichern
//STRIP001
//STRIP001          SvxSwAutoFmtFlags aAFFlags = *GetAutoFmtFlags();        // erst mal default - Werte
//STRIP001
//STRIP001          SwAutoFormat aFmt( this, aAFFlags, &pCrsr->GetMark()->nNode,
//STRIP001                                  &pCrsr->GetPoint()->nNode );
//STRIP001
//STRIP001          //JP 30.09.96: das DoTable() verlaesst sich auf das PopCrsr
//STRIP001          //              und MoveCrsr!
//STRIP001          Pop( FALSE );
//STRIP001          pCrsr = GetCrsr();
//STRIP001      }
//STRIP001      pCrsr->DeleteMark();
//STRIP001      pCrsr->Move( fnMoveForward, fnGoNode );
//STRIP001
//STRIP001      EndUndo( UNDO_AUTOFORMAT );
//STRIP001      EndAllAction();
//STRIP001  }
//STRIP001 }

/*N*/ SvxSwAutoFmtFlags* SwEditShell::GetAutoFmtFlags()
/*N*/ {
/*N*/   if (!pAutoFmtFlags)
/*N*/       pAutoFmtFlags = new SvxSwAutoFmtFlags;
/*N*/
/*N*/   return pAutoFmtFlags;
/*N*/ }

/*N*/ void SwEditShell::SetAutoFmtFlags(SvxSwAutoFmtFlags * pFlags)
/*N*/ {
/*N*/   SvxSwAutoFmtFlags* pEditFlags = GetAutoFmtFlags();
/*N*/
/*N*/   pEditFlags->bSetNumRule     = pFlags->bSetNumRule;
/*N*/   pEditFlags->bChgEnumNum     = pFlags->bChgEnumNum;
/*N*/   pEditFlags->bSetBorder      = pFlags->bSetBorder;
/*N*/   pEditFlags->bCreateTable    = pFlags->bCreateTable;
/*N*/   pEditFlags->bReplaceStyles  = pFlags->bReplaceStyles;
/*N*/   pEditFlags->bAFmtByInpDelSpacesAtSttEnd =
/*N*/                                   pFlags->bAFmtByInpDelSpacesAtSttEnd;
/*N*/   pEditFlags->bAFmtByInpDelSpacesBetweenLines =
/*N*/                                   pFlags->bAFmtByInpDelSpacesBetweenLines;
/*N*/
/*N*/   //JP 15.12.98: BulletZeichen und Font in die "normalen" kopieren,
/*N*/   //          weil beim Autoformat nur mit diesen gearbeitet wird!
/*N*/   pEditFlags->cBullet             = pFlags->cByInputBullet;
/*N*/   pEditFlags->aBulletFont         = pFlags->aByInputBulletFont;
/*N*/   pEditFlags->cByInputBullet      = pFlags->cByInputBullet;
/*N*/   pEditFlags->aByInputBulletFont  = pFlags->aByInputBulletFont;
/*N*/ }

}
