/*************************************************************************
 *
 *  $RCSfile: sw_docruby.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:09:24 $
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

#include <string.h>         // fuer strchr()

// auto strip #ifndef _HINTIDS_HXX
// auto strip #include <hintids.hxx>
// auto strip #endif

#ifndef _COM_SUN_STAR_I18N_UNICODETYPE_HDL
#include <com/sun/star/i18n/UnicodeType.hdl>
#endif
#ifndef _COM_SUN_STAR_I18N_WORDTYPE_HDL
#include <com/sun/star/i18n/WordType.hdl>
#endif
// auto strip #ifndef _UNOTOOLS_CHARCLASS_HXX
// auto strip #include <unotools/charclass.hxx>
// auto strip #endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
// auto strip #ifndef _DOCARY_HXX
// auto strip #include <docary.hxx>
// auto strip #endif
// auto strip #ifndef _MVSAVE_HXX
// auto strip #include <mvsave.hxx>     // Strukturen zum Sichern beim Move/Delete
// auto strip #endif
// auto strip #ifndef _NDTXT_HXX
// auto strip #include <ndtxt.hxx>
// auto strip #endif
// auto strip #ifndef _TXATBASE_HXX
// auto strip #include <txatbase.hxx>
// auto strip #endif
#ifndef _RUBYLIST_HXX
#include <rubylist.hxx>
#endif
// auto strip #ifndef _NODE_HXX
// auto strip #include <node.hxx>
// auto strip #endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
// auto strip #ifndef _SWUNDO_HXX
// auto strip #include <swundo.hxx>     // fuer die UndoIds
// auto strip #endif
// auto strip #ifndef _UNDOBJ_HXX
// auto strip #include <undobj.hxx>
// auto strip #endif
// auto strip #ifndef _BREAKIT_HXX
// auto strip #include <breakit.hxx>
// auto strip #endif
// auto strip #ifndef _CRSSKIP_HXX
// auto strip #include <crsskip.hxx>
// auto strip #endif
namespace binfilter {

/*N*/ SV_IMPL_PTRARR( SwRubyList, SwRubyListEntryPtr )

using namespace ::com::sun::star::i18n;


/*
 * Members in the list:
 *   - String - the orig text
 *   - SwFmtRuby - the ruby attribut
 *
 *
 */
/*N*/ USHORT SwDoc::FillRubyList( const SwPaM& rPam, SwRubyList& rList,
/*N*/                           USHORT nMode )
/*N*/ {
/*N*/   const SwPaM *_pStartCrsr = (SwPaM*)rPam.GetNext(),
/*N*/               *__pStartCrsr = _pStartCrsr;
/*N*/   BOOL bCheckEmpty = &rPam != _pStartCrsr;
/*N*/   do {
/*N*/       const SwPosition* pStt = _pStartCrsr->Start(),
/*N*/                       * pEnd = pStt == _pStartCrsr->GetPoint()
/*N*/                                               ? _pStartCrsr->GetMark()
/*N*/                                               : _pStartCrsr->GetPoint();
/*N*/       if( !bCheckEmpty || ( pStt != pEnd && *pStt != *pEnd ))
/*N*/       {
/*N*/           SwPaM aPam( *pStt );
/*N*/           do {
/*N*/               SwRubyListEntry* pNew = new SwRubyListEntry;
/*N*/               if( pEnd != pStt )
/*N*/               {
/*N*/                   aPam.SetMark();
/*N*/                   *aPam.GetMark() = *pEnd;
/*N*/               }
/*N*/               if( _SelectNextRubyChars( aPam, *pNew, nMode ))
/*N*/               {
/*N*/                   rList.Insert( pNew, rList.Count() );
/*N*/                   aPam.DeleteMark();
/*N*/               }
/*N*/               else
/*N*/               {
/*N*/                   delete pNew;
/*N*/                   if( *aPam.GetPoint() < *pEnd )
/*N*/                   {
/*N*/                       // goto next paragraph
/*N*/                       aPam.DeleteMark();
/*N*/                       aPam.Move( fnMoveForward, fnGoNode );
/*N*/                   }
/*N*/                   else
/*N*/                       break;
/*N*/               }
/*N*/           } while( 30 > rList.Count() && *aPam.GetPoint() < *pEnd );
/*N*/       }
/*N*/   } while( 30 > rList.Count() &&
/*N*/       (_pStartCrsr=(SwPaM *)_pStartCrsr->GetNext()) != __pStartCrsr );
/*N*/
/*N*/   return rList.Count();
/*N*/ }

/*N*/ USHORT SwDoc::SetRubyList( const SwPaM& rPam, const SwRubyList& rList,
/*N*/                           USHORT nMode )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001 StartUndo( UNDO_SETRUBYATTR );
//STRIP001 /*?*/    SvUShortsSort aDelArr;
//STRIP001 /*?*/    aDelArr.Insert( RES_TXTATR_CJK_RUBY );
//STRIP001 /*?*/
//STRIP001 /*?*/    USHORT nListEntry = 0;
//STRIP001 /*?*/
//STRIP001 /*?*/    const SwPaM *_pStartCrsr = (SwPaM*)rPam.GetNext(),
//STRIP001 /*?*/                *__pStartCrsr = _pStartCrsr;
//STRIP001 /*?*/    BOOL bCheckEmpty = &rPam != _pStartCrsr;
//STRIP001 /*?*/    do {
//STRIP001 /*?*/        const SwPosition* pStt = _pStartCrsr->Start(),
//STRIP001 /*?*/                        * pEnd = pStt == _pStartCrsr->GetPoint()
//STRIP001 /*?*/                                                ? _pStartCrsr->GetMark()
//STRIP001 /*?*/                                                : _pStartCrsr->GetPoint();
//STRIP001 /*?*/        if( !bCheckEmpty || ( pStt != pEnd && *pStt != *pEnd ))
//STRIP001 /*?*/        {
//STRIP001 /*?*/
//STRIP001 /*?*/            SwPaM aPam( *pStt );
//STRIP001 /*?*/            do {
//STRIP001 /*?*/                SwRubyListEntry aCheckEntry;
//STRIP001 /*?*/                if( pEnd != pStt )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    aPam.SetMark();
//STRIP001 /*?*/                    *aPam.GetMark() = *pEnd;
//STRIP001 /*?*/                }
//STRIP001 /*?*/                if( _SelectNextRubyChars( aPam, aCheckEntry, nMode ))
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    const SwRubyListEntry* pEntry = rList[ nListEntry++ ];
//STRIP001 /*?*/                    if( aCheckEntry.GetRubyAttr() != pEntry->GetRubyAttr() )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        // set/reset the attribut
//STRIP001 /*?*/                        if( pEntry->GetRubyAttr().GetText().Len() )
//STRIP001 /*?*/                            Insert( aPam, pEntry->GetRubyAttr() );
//STRIP001 /*?*/                        else
//STRIP001 /*?*/                            ResetAttr( aPam, TRUE, &aDelArr );
//STRIP001 /*?*/                    }
//STRIP001 /*?*/
//STRIP001 /*?*/                    if( aCheckEntry.GetText() != pEntry->GetText() &&
//STRIP001 /*?*/                        pEntry->GetText().Len() )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        // text is changed, so replace the original
//STRIP001 /*?*/                        Replace( aPam, pEntry->GetText(), FALSE );
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    aPam.DeleteMark();
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    if( *aPam.GetPoint() < *pEnd )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        // goto next paragraph
//STRIP001 /*?*/                        aPam.DeleteMark();
//STRIP001 /*?*/                        aPam.Move( fnMoveForward, fnGoNode );
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    else
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        const SwRubyListEntry* pEntry = rList[ nListEntry++ ];
//STRIP001 /*?*/
//STRIP001 /*?*/                        // set/reset the attribut
//STRIP001 /*?*/                        if( pEntry->GetRubyAttr().GetText().Len() &&
//STRIP001 /*?*/                            pEntry->GetText().Len() )
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            Insert( aPam, pEntry->GetText() );
//STRIP001 /*?*/                            aPam.SetMark();
//STRIP001 /*?*/                            aPam.GetMark()->nContent -= pEntry->GetText().Len();
//STRIP001 /*?*/                            Insert( aPam, pEntry->GetRubyAttr(), SETATTR_DONTEXPAND );
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                        else
//STRIP001 /*?*/                            break;
//STRIP001 /*?*/                        aPam.DeleteMark();
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/            } while( nListEntry < rList.Count() && *aPam.GetPoint() < *pEnd );
//STRIP001 /*?*/        }
//STRIP001 /*?*/    } while( 30 > rList.Count() &&
//STRIP001 /*?*/        (_pStartCrsr=(SwPaM *)_pStartCrsr->GetNext()) != __pStartCrsr );
//STRIP001 /*?*/
//STRIP001 /*?*/    EndUndo( UNDO_SETRUBYATTR );
//STRIP001 /*?*/
//STRIP001 /*?*/    return nListEntry;
/*N*/ }

/*N*/ BOOL SwDoc::_SelectNextRubyChars( SwPaM& rPam, SwRubyListEntry& rEntry,
/*N*/                                   USHORT nMode )
/*N*/ {
    DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 // Point must be the startposition, Mark is optional the end position
//STRIP001  SwPosition* pPos = rPam.GetPoint();
//STRIP001      const SwTxtNode* pTNd = pPos->nNode.GetNode().GetTxtNode();
//STRIP001  const String* pTxt = &pTNd->GetTxt();
//STRIP001  xub_StrLen nStart = pPos->nContent.GetIndex(), nEnd = pTxt->Len();
//STRIP001
//STRIP001  BOOL bHasMark = rPam.HasMark();
//STRIP001  if( bHasMark )
//STRIP001  {
//STRIP001      // in the same node?
//STRIP001      if( rPam.GetMark()->nNode == pPos->nNode )
//STRIP001      {
//STRIP001          // then use that end
//STRIP001          xub_StrLen nTEnd = rPam.GetMark()->nContent.GetIndex();
//STRIP001          if( nTEnd < nEnd )
//STRIP001              nEnd = nTEnd;
//STRIP001      }
//STRIP001      rPam.DeleteMark();
//STRIP001  }
//STRIP001
//STRIP001  // ----- search the start
//STRIP001  // --- look where a ruby attribut starts
//STRIP001  USHORT nHtIdx = USHRT_MAX;
//STRIP001  const SwpHints* pHts = pTNd->GetpSwpHints();
//STRIP001  const SwTxtAttr* pAttr = 0;
//STRIP001  if( pHts )
//STRIP001  {
//STRIP001      const SwTxtAttr* pHt;
//STRIP001      for( nHtIdx = 0; nHtIdx < pHts->Count(); ++nHtIdx )
//STRIP001          if( RES_TXTATR_CJK_RUBY == ( pHt = (*pHts)[ nHtIdx ])->Which() &&
//STRIP001              *pHt->GetAnyEnd() > nStart )
//STRIP001          {
//STRIP001              if( *pHt->GetStart() < nEnd )
//STRIP001              {
//STRIP001                  pAttr = pHt;
//STRIP001                  if( !bHasMark && nStart > *pAttr->GetStart() )
//STRIP001                  {
//STRIP001                      nStart = *pAttr->GetStart();
//STRIP001                      pPos->nContent = nStart;
//STRIP001                  }
//STRIP001              }
//STRIP001              break;
//STRIP001          }
//STRIP001  }
//STRIP001
//STRIP001  if( !bHasMark && nStart && ( !pAttr || nStart != *pAttr->GetStart()) )
//STRIP001  {
//STRIP001      // skip to the word begin!
//STRIP001      long nWordStt = pBreakIt->xBreak->getWordBoundary(
//STRIP001                          *pTxt, nStart,
//STRIP001                          pBreakIt->GetLocale( pTNd->GetLang( nStart )),
//STRIP001                          WordType::ANYWORD_IGNOREWHITESPACES,
//STRIP001                          TRUE ).startPos;
//STRIP001      if( nWordStt < nStart && -1 != nWordStt )
//STRIP001      {
//STRIP001          nStart = (xub_StrLen)nWordStt;
//STRIP001          pPos->nContent = nStart;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  BOOL bAlphaNum = FALSE;
//STRIP001  long nWordEnd = nEnd;
//STRIP001  CharClass& rCC = GetAppCharClass();
//STRIP001  while(  nStart < nEnd )
//STRIP001  {
//STRIP001      if( pAttr && nStart == *pAttr->GetStart() )
//STRIP001      {
//STRIP001          pPos->nContent = nStart;
//STRIP001          if( !rPam.HasMark() )
//STRIP001          {
//STRIP001              rPam.SetMark();
//STRIP001              pPos->nContent = *pAttr->GetAnyEnd();
//STRIP001              if( pPos->nContent.GetIndex() > nEnd )
//STRIP001                  pPos->nContent = nEnd;
//STRIP001              rEntry.SetRubyAttr( pAttr->GetRuby() );
//STRIP001          }
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      sal_Int32 nChType = rCC.getType( *pTxt, nStart );
//STRIP001      BOOL bIgnoreChar = FALSE, bIsAlphaNum = FALSE, bChkNxtWrd = FALSE;
//STRIP001      switch( nChType )
//STRIP001      {
//STRIP001      case UnicodeType::UPPERCASE_LETTER:
//STRIP001      case UnicodeType::LOWERCASE_LETTER:
//STRIP001      case UnicodeType::TITLECASE_LETTER:
//STRIP001      case UnicodeType::DECIMAL_DIGIT_NUMBER:
//STRIP001              bChkNxtWrd = bIsAlphaNum = TRUE;
//STRIP001              break;
//STRIP001
//STRIP001      case UnicodeType::SPACE_SEPARATOR:
//STRIP001      case UnicodeType::CONTROL:
//STRIP001 /*??*/   case UnicodeType::PRIVATE_USE:
//STRIP001      case UnicodeType::START_PUNCTUATION:
//STRIP001      case UnicodeType::END_PUNCTUATION:
//STRIP001          bIgnoreChar = TRUE;
//STRIP001          break;
//STRIP001
//STRIP001
//STRIP001      case UnicodeType::OTHER_LETTER:
//STRIP001          bChkNxtWrd = TRUE;
//STRIP001          // no break!
//STRIP001 //       case UnicodeType::UNASSIGNED:
//STRIP001 //       case UnicodeType::MODIFIER_LETTER:
//STRIP001 //       case UnicodeType::NON_SPACING_MARK:
//STRIP001 //       case UnicodeType::ENCLOSING_MARK:
//STRIP001 //       case UnicodeType::COMBINING_SPACING_MARK:
//STRIP001 //       case UnicodeType::LETTER_NUMBER:
//STRIP001 //       case UnicodeType::OTHER_NUMBER:
//STRIP001 //       case UnicodeType::LINE_SEPARATOR:
//STRIP001 //       case UnicodeType::PARAGRAPH_SEPARATOR:
//STRIP001 //       case UnicodeType::FORMAT:
//STRIP001 //       case UnicodeType::SURROGATE:
//STRIP001 //       case UnicodeType::DASH_PUNCTUATION:
//STRIP001 //       case UnicodeType::CONNECTOR_PUNCTUATION:
//STRIP001 ///*?? */case UnicodeType::OTHER_PUNCTUATION:
//STRIP001 //--> char '!' is to ignore!
//STRIP001 //       case UnicodeType::MATH_SYMBOL:
//STRIP001 //       case UnicodeType::CURRENCY_SYMBOL:
//STRIP001 //       case UnicodeType::MODIFIER_SYMBOL:
//STRIP001 //       case UnicodeType::OTHER_SYMBOL:
//STRIP001 //       case UnicodeType::INITIAL_PUNCTUATION:
//STRIP001 //       case UnicodeType::FINAL_PUNCTUATION:
//STRIP001      default:
//STRIP001              bIsAlphaNum = FALSE;
//STRIP001              break;
//STRIP001      }
//STRIP001
//STRIP001      if( rPam.HasMark() )
//STRIP001      {
//STRIP001          if( bIgnoreChar || bIsAlphaNum != bAlphaNum || nStart >= nWordEnd )
//STRIP001              break;
//STRIP001      }
//STRIP001      else if( !bIgnoreChar )
//STRIP001      {
//STRIP001          rPam.SetMark();
//STRIP001          bAlphaNum = bIsAlphaNum;
//STRIP001          if( bChkNxtWrd && pBreakIt->xBreak.is() )
//STRIP001          {
//STRIP001              // search the end of this word
//STRIP001              nWordEnd = pBreakIt->xBreak->getWordBoundary(
//STRIP001                          *pTxt, nStart,
//STRIP001                          pBreakIt->GetLocale( pTNd->GetLang( nStart )),
//STRIP001                          WordType::ANYWORD_IGNOREWHITESPACES,
//STRIP001                          TRUE ).endPos;
//STRIP001              if( 0 > nWordEnd || nWordEnd > nEnd || nWordEnd == nStart )
//STRIP001                  nWordEnd = nEnd;
//STRIP001          }
//STRIP001      }
//STRIP001      pTNd->GoNext( &pPos->nContent, CRSR_SKIP_CHARS );
//STRIP001      nStart = pPos->nContent.GetIndex();
//STRIP001  }
//STRIP001
//STRIP001  nStart = rPam.GetMark()->nContent.GetIndex();
//STRIP001  rEntry.SetText( pTxt->Copy( nStart,
//STRIP001                         rPam.GetPoint()->nContent.GetIndex() - nStart ));
//STRIP001  return rPam.HasMark();
/*N*/ }

/*N*/SwRubyListEntry::~SwRubyListEntry()
/*N*/{
/*N*/}
}
