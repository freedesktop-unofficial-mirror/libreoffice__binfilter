/*************************************************************************
 *
 *  $RCSfile: sw_txtedt.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:39:06 $
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


// So kann man die Linguistik-Statistik ( (Tmp-Path)\swlingu.stk ) aktivieren:
//#define LINGU_STATISTIK
#ifdef LINGU_STATISTIK
    #include <stdio.h>          // in SwLinguStatistik::DTOR
    #include <stdlib.h>         // getenv()
    #include <time.h>           // clock()
    #include "viewsh.hxx"       // ViewShell::GetHyphenator
    #include <tools/stream.hxx>
#endif

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _SV_SVAPP_HXX //autogen wg. Application
#include <vcl/svapp.hxx>
#endif
#ifndef _SVX_SPLWRAP_HXX
#include <bf_svx/splwrap.hxx>
#endif
#ifndef _SVX_LANGITEM_HXX //autogen
#include <bf_svx/langitem.hxx>
#endif
#ifndef _SVX_SCRIPTTYPEITEM_HXX
#include <bf_svx/scripttypeitem.hxx>
#endif
#ifndef _LINGUISTIC_LNGPROPS_HHX_
#include <bf_linguistic/lngprops.hxx>
#endif
#ifndef _STRING_HXX
#include <tools/string.hxx>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_I18N_WORDTYPE_HDL
#include <com/sun/star/i18n/WordType.hdl>
#endif
#ifndef _COM_SUN_STAR_I18N_SCRIPTTYPE_HDL_
#include <com/sun/star/i18n/ScriptType.hdl>
#endif
#ifndef _UNOTOOLS_TRANSLITERATIONWRAPPER_HXX
#include <unotools/transliterationwrapper.hxx>
#endif

#ifndef _DLELSTNR_HXX_
#include <dlelstnr.hxx>
#endif
#ifndef _SWMODULE_HXX
#include <swmodule.hxx>
#endif
#ifndef _SHL_HXX
#include <tools/shl.hxx>    // needed for SW_MOD() macro
#endif
#ifndef _SPLARGS_HXX
#include <splargs.hxx>
#endif
#ifndef _VIEWSH_HXX
#include <viewsh.hxx>   // ViewShell
#endif
#ifndef _VIEWOPT_HXX
#include <viewopt.hxx>
#endif
#ifndef _ACMPLWRD_HXX
#include <acmplwrd.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>      // GetDoc()
#endif
#ifndef _FRMSH_HXX
#include <frmsh.hxx>
#endif
#ifndef _TXATBASE_HXX //autogen
#include <txatbase.hxx>
#endif
#ifndef _CHARATR_HXX
#include <charatr.hxx>
#endif
#ifndef _FLDBAS_HXX
#include <fldbas.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _SPLARGS_HXX
#include <splargs.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>
#endif
#ifndef _WRONG_HXX
#include <wrong.hxx>
#endif
#ifndef _TXTTYPES_HXX
#include <txttypes.hxx>
#endif
#ifndef _BREAKIT_HXX
#include <breakit.hxx>
#endif
#ifndef _CRSTATE_HXX
#include <crstate.hxx>
#endif
#ifndef _UNDOBJ_HXX
#include <undobj.hxx>
#endif
#ifndef _TXATRITR_HXX
#include <txatritr.hxx>
#endif
#ifndef _REDLINE_HXX
#include <redline.hxx>      // SwRedline
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>       // SwRedlineTbl
#endif
#ifndef _DRAWFONT_HXX
#include <drawfont.hxx> // SwDrawTextInfo
#endif

using namespace ::com::sun::star;
using namespace ::com::sun::star::i18n;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::linguistic2;

#define C2U(cChar) rtl::OUString::createFromAscii(cChar)

// Wir ersparen uns in Hyphenate ein GetFrm()
// Achtung: in edlingu.cxx stehen die Variablen!
extern const SwTxtNode *pLinguNode;
extern       SwTxtFrm  *pLinguFrm;

bool lcl_IsSkippableWhiteSpace( xub_Unicode cCh )
{
    return 0x3000 == cCh ||
           ' ' == cCh ||
           '\t' == cCh ||
           0x0a == cCh;
}

/*
 * Ein Zeichen wurde eingefuegt.
 */

/*N*/ SwTxtNode& SwTxtNode::Insert( xub_Unicode c, const SwIndex &rIdx )
/*N*/ {
/*N*/   xub_StrLen nOrigLen = aText.Len();
/*N*/
/*N*/   ASSERT( rIdx <= nOrigLen, "Array ueberindiziert." );
/*N*/   ASSERT( nOrigLen < STRING_LEN, "USHRT_MAX ueberschritten." );
/*N*/
/*N*/   if( nOrigLen == aText.Insert( c, rIdx.GetIndex() ).Len() )
/*N*/       return *this;
/*N*/
/*N*/   Update(rIdx,1);
/*N*/
/*N*/   // leere Hints und Feldattribute an rIdx.GetIndex suchen
/*N*/   if( pSwpHints )
/*N*/   {
/*N*/       USHORT* pEndIdx;
/*N*/       for( USHORT i=0; i < pSwpHints->Count() &&
/*N*/               rIdx >= *(*pSwpHints)[i]->GetStart(); ++i)
/*N*/       {
/*N*/           SwTxtAttr *pHt = pSwpHints->GetHt(i);
/*N*/           if( 0 != ( pEndIdx = pHt->GetEnd()) )
/*N*/           {
/*N*/               // leere Hints an rIdx.GetIndex ?
/*N*/               BOOL bEmpty = *pEndIdx == *pHt->GetStart()
/*N*/                           && rIdx == *pHt->GetStart();
/*N*/
/*N*/               if( bEmpty )
/*N*/               {
/*N*/                   pSwpHints->DeleteAtPos(i);
/*N*/                   if( bEmpty )
/*N*/                       *pHt->GetStart() -= 1;
/*N*/                   else
/*N*/                       *pEndIdx -= 1;
/*N*/                   Insert(pHt);
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/       if ( pSwpHints->CanBeDeleted() )
/*N*/           DELETEZ( pSwpHints );
/*N*/   }
/*N*/   // den Frames Bescheid sagen
/*N*/   SwInsChr aHint( rIdx.GetIndex()-1 );
/*N*/   SwModify::Modify( 0, &aHint );
/*N*/   return *this;
/*N*/ }

//STRIP001 inline BOOL InRange(xub_StrLen nIdx, xub_StrLen nStart, xub_StrLen nEnd) {
//STRIP001  return ((nIdx >=nStart) && (nIdx <= nEnd));
//STRIP001 }

/*
 * void SwTxtNode::RstAttr(const SwIndex &rIdx, USHORT nLen)
 *
 * loescht alle Attribute ab der Position rIdx ueber eine Laenge
 * von nLen.
 */

/* 5 Faelle:
 * 1) Das Attribut liegt vollstaendig im Bereich:
 *    -> loeschen
 * 2) Das Attributende liegt im Bereich:
 *    -> Loeschen, mit neuem Ende einfuegen
 * 3) Der Attributanfang liegt im Bereich:
 *    -> Loeschen, mit neuem Anfang einfuegen
 * 4) Das Attrib umfasst den Bereich:
 *       Aufsplitten, d.h.
 *    -> Loeschen, mit alten Anfang und Anfang des Bereiches einfuegen
 *    -> Neues Attribut mit Ende des Bereiches und altem Ende einfuegen
 * 5) Das Attribut liegt ausserhalb des Bereiches
 *     -> nichts tun.
 */



/*M*/ void SwTxtNode::RstAttr(const SwIndex &rIdx, xub_StrLen nLen, USHORT nWhich,
/*M*/                       const SfxItemSet* pSet, BOOL bInclRefToxMark )
/*M*/ {
/*M*/   // Attribute?
/*M*/   if ( !GetpSwpHints() )
/*M*/       return;
/*M*/
/*M*/   USHORT i = 0;
/*M*/   xub_StrLen nStart = rIdx.GetIndex();
/*M*/   xub_StrLen nEnd = nStart + nLen;
/*M*/   xub_StrLen *pAttrEnd;
/*M*/   xub_StrLen nAttrStart;
/*M*/   SwTxtAttr *pHt;
/*M*/
/*M*/   BOOL    bChanged = FALSE;
/*M*/
/*M*/   // nMin und nMax werden invers auf das Maximum bzw. Minimum gesetzt.
/*M*/   xub_StrLen nMin = aText.Len();
/*M*/   xub_StrLen nMax = nStart;
/*M*/
/*M*/   const BOOL bNoLen = !nMin;
/*M*/
/*M*/     // We have to remember the "new" attributes, which have
/*M*/     // been introduced by splitting surrounding attributes (case 4).
/*M*/     // They may not be forgotten inside the "Forget" function
/*M*/     std::vector< const SwTxtAttr* > aNewAttributes;
/*M*/
/*M*/   // durch das Attribute-Array, bis der Anfang des Geltungsbereiches
/*M*/   // des Attributs hinter dem Bereich liegt
/*M*/   while( (i < pSwpHints->Count()) &&
/*M*/               ((( nAttrStart = *(*pSwpHints)[i]->GetStart()) < nEnd )
/*M*/                   || nLen==0) )
/*M*/   {
/*M*/       pHt = pSwpHints->GetHt(i);
/*M*/
/*M*/       // Attribute ohne Ende bleiben drin!
/*M*/       if ( 0 == (pAttrEnd=pHt->GetEnd()) )
/*M*/       {
/*M*/           i++;
/*M*/           continue;
/*M*/       }
/*M*/
/*M*/       // loesche alle TextAttribute die als Attribut im Set vorhanden sind
/*M*/       if( pSet ? SFX_ITEM_SET != pSet->GetItemState( pHt->Which(), FALSE )
/*M*/                : ( nWhich ? nWhich != pHt->Which()
/*M*/                           : (!bInclRefToxMark &&
/*M*/                               ( RES_TXTATR_REFMARK == pHt->Which() ||
/*M*/                               RES_TXTATR_TOXMARK == pHt->Which() ))))
/*M*/       {
/*M*/           // Es sollen nur Attribute mit nWhich beachtet werden
/*M*/           i++;
/*M*/           continue;
/*M*/       }
/*M*/
/*M*/
/*M*/       if( nStart <= nAttrStart )          // Faelle: 1,3,5
/*M*/       {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            if( nEnd > nAttrStart
//STRIP001 /*?*/                || ( nEnd == *pAttrEnd && nEnd==nAttrStart ) )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                // Faelle: 1,3
//STRIP001 /*?*/                if ( nMin > nAttrStart )
//STRIP001 /*?*/                    nMin = nAttrStart;
//STRIP001 /*?*/                if ( nMax < *pAttrEnd )
//STRIP001 /*?*/                    nMax = *pAttrEnd;
//STRIP001 /*?*/                // Falls wir nur ein nichtaufgespanntes Attribut entfernen,
//STRIP001 /*?*/                // tun wir mal so, als ob sich nichts geaendert hat.
//STRIP001 /*?*/                bChanged = bChanged || nEnd > nAttrStart || bNoLen;
//STRIP001 /*?*/                if( *pAttrEnd <= nEnd )     // Fall: 1
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    pSwpHints->DeleteAtPos(i);
//STRIP001 /*?*/                    DestroyAttr( pHt );
//STRIP001 /*?*/
//STRIP001 /*?*/                    // falls das letzte Attribut ein Field ist, loescht
//STRIP001 /*?*/                    // dieses das HintsArray !!!
//STRIP001 /*?*/                    if( !pSwpHints )
//STRIP001 /*?*/                        break;
//STRIP001 /*?*/
//STRIP001 /*?*/                    //JP 26.11.96:
//STRIP001 /*?*/                    // beim DeleteAtPos wird ein Resort ausgefuehrt!!
//STRIP001 /*?*/                    // darum muessen wir wieder bei 0 anfangen!!!
//STRIP001 /*?*/                    // ueber den Fall 3 koennen Attribute nach hinten
//STRIP001 /*?*/                    // verschoben worden sein; damit stimmt jetzt das i
//STRIP001 /*?*/                    // nicht mehr!!!
//STRIP001 /*?*/                    i = 0;
//STRIP001 /*?*/
//STRIP001 /*?*/                    continue;
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else                        // Fall: 3
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    pSwpHints->NoteInHistory( pHt );
//STRIP001 /*?*/                    *pHt->GetStart() = nEnd;
//STRIP001 /*?*/                    pSwpHints->NoteInHistory( pHt, TRUE );
//STRIP001 /*?*/                    bChanged = TRUE;
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
/*M*/       }
/*M*/       else                                // Faelle: 2,4,5
/*M*/           if( *pAttrEnd > nStart )        // Faelle: 2,4
/*M*/           {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/                if( *pAttrEnd < nEnd )      // Fall: 2
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    if ( nMin > nAttrStart )
//STRIP001 /*?*/                        nMin = nAttrStart;
//STRIP001 /*?*/                    if ( nMax < *pAttrEnd )
//STRIP001 /*?*/                        nMax = *pAttrEnd;
//STRIP001 /*?*/                    bChanged = TRUE;
//STRIP001 /*?*/                    pSwpHints->NoteInHistory( pHt );
//STRIP001 /*?*/                    *pAttrEnd = nStart;
//STRIP001 /*?*/                    pSwpHints->NoteInHistory( pHt, TRUE );
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else if( nLen )             // Fall: 4
//STRIP001 /*?*/                {       // bei Lange 0 werden beide Hints vom Insert(Ht)
//STRIP001 /*?*/                        // wieder zu einem zusammengezogen !!!!
//STRIP001 /*?*/                    if ( nMin > nAttrStart )
//STRIP001 /*?*/                        nMin = nAttrStart;
//STRIP001 /*?*/                    if ( nMax < *pAttrEnd )
//STRIP001 /*?*/                        nMax = *pAttrEnd;
//STRIP001 /*?*/                    bChanged = TRUE;
//STRIP001 /*?*/                    xub_StrLen nTmpEnd = *pAttrEnd;
//STRIP001 /*?*/                    pSwpHints->NoteInHistory( pHt );
//STRIP001 /*?*/                    *pAttrEnd = nStart;
//STRIP001 /*?*/                    pSwpHints->NoteInHistory( pHt, TRUE );
//STRIP001 /*?*/
//STRIP001 /*?*/                     if( nEnd < nTmpEnd &&
//STRIP001 /*?*/                         ! pSwpHints->Forget( &aNewAttributes, i, pHt->Which(),
//STRIP001 /*?*/                                              nEnd, nTmpEnd ) )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                         const SwTxtAttr* pNewAttr =
//STRIP001 /*?*/                                 Insert( pHt->GetAttr(), nEnd, nTmpEnd,
//STRIP001 /*?*/                                         SETATTR_NOHINTADJUST );
//STRIP001 /*?*/
//STRIP001 /*?*/                         aNewAttributes.push_back( pHt );
//STRIP001 /*?*/                         aNewAttributes.push_back( pNewAttr );
//STRIP001 /*?*/
//STRIP001 /*?*/                        // jetzt kein i+1, weil das eingefuegte Attribut
//STRIP001 /*?*/                        // ein anderes auf die Position geschoben hat !
//STRIP001 /*?*/                        continue;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
/*M*/       }
/*M*/       ++i;
/*M*/   }
/*M*/
/*M*/   if ( pSwpHints && pSwpHints->CanBeDeleted() )
/*M*/       DELETEZ( pSwpHints );
/*M*/   if(bChanged)
/*M*/   {
/*M*/       if ( pSwpHints )
/*M*/       {
/*M*/           pSwpHints->ClearDummies( *this );
/*M*/           ((SwpHintsArr*)pSwpHints)->Resort();
/*M*/           pSwpHints->Merge( *this );
/*M*/       }
/*M*/       //TxtFrm's reagieren auf aHint, andere auf aNew
/*M*/       SwUpdateAttr aHint( nMin, nMax, 0 );
/*M*/       SwModify::Modify( 0, &aHint );
/*M*/       SwFmtChg aNew( GetFmtColl() );
/*M*/       SwModify::Modify( 0, &aNew );
/*M*/   }
/*M*/ }



/*************************************************************************
 *                SwTxtNode::GetCurWord()
 *
 * Aktuelles Wort zurueckliefern:
 * Wir suchen immer von links nach rechts, es wird also das Wort
 * vor nPos gesucht. Es sei denn, wir befinden uns am Anfang des
 * Absatzes, dann wird das erste Wort zurueckgeliefert.
 * Wenn dieses erste Wort nur aus Whitespaces besteht, returnen wir
 * einen leeren String.
 *************************************************************************/



//STRIP001 XubString SwTxtNode::GetCurWord( xub_StrLen nPos )
//STRIP001 {
//STRIP001  ASSERT( nPos<=aText.Len() , "SwTxtNode::GetCurWord: Pos hinter String?");
//STRIP001     if (!aText.Len())
//STRIP001      return aText;
//STRIP001
//STRIP001  Boundary aBndry;
//STRIP001     const Reference< XBreakIterator > &rxBreak = pBreakIt->xBreak;
//STRIP001     if (rxBreak.is())
//STRIP001     {
//STRIP001         sal_Int16 nWordType = WordType::DICTIONARY_WORD;
//STRIP001         lang::Locale aLocale( pBreakIt->GetLocale( GetLang( nPos ) ) );
//STRIP001 #ifdef DEBUG
//STRIP001         BOOL bBegin = rxBreak->isBeginWord( aText, nPos, aLocale, nWordType );
//STRIP001         BOOL bEnd   = rxBreak->isEndWord  ( aText, nPos, aLocale, nWordType );
//STRIP001 #endif
//STRIP001         aBndry = rxBreak->getWordBoundary( aText, nPos, aLocale, nWordType, TRUE );
//STRIP001
//STRIP001         // if no word was found use previous word (if any)
//STRIP001         if (aBndry.startPos == aBndry.endPos)
//STRIP001             aBndry = rxBreak->previousWord( aText, nPos, aLocale, nWordType );
//STRIP001     }
//STRIP001
//STRIP001     // check if word was found and if it uses a symbol font, if so
//STRIP001     // enforce returning an empty string
//STRIP001     if (aBndry.endPos != aBndry.startPos && IsSymbol( (xub_StrLen)aBndry.startPos ))
//STRIP001      aBndry.endPos = aBndry.startPos;
//STRIP001
//STRIP001     return aText.Copy( (xub_StrLen) aBndry.startPos,
//STRIP001                        (xub_StrLen) (aBndry.endPos - aBndry.startPos) );
//STRIP001 }


/*M*/ void SwTxtNode::SetWrong( SwWrongList *pNew )
/*M*/ {
/*M*/   delete pWrong;
/*M*/   pWrong = pNew;
/*M*/ }

/*M*/ SwScanner::SwScanner( const SwTxtNode& rNd, const SwWrongList* pWrng,
/*M*/                       USHORT nType, xub_StrLen nStart, xub_StrLen nEnde,
/*M*/                       BOOL bRev, BOOL bOS )
/*M*/     : rNode( rNd ), pWrong( pWrng ), nWordType( nType ), nLen( 0 ),
/*M*/       bReverse( bRev ), bStart( TRUE ), bIsOnlineSpell( bOS )
/*M*/ {
/*M*/     ASSERT( rNd.GetTxt().Len(), "SwScanner: EmptyString" );
/*M*/   if( bReverse )
/*M*/   {
/*M*/       nBegin = nEnde;
/*M*/       nEndPos = nStart;
/*M*/   }
/*M*/   else
/*M*/   {
/*M*/       nBegin = nStart;
/*M*/       nEndPos = nEnde;
/*M*/   }
/*M*/
/*M*/     aCurrLang = rNd.GetLang( nBegin );
/*M*/ }


/*N*/ BOOL SwScanner::NextWord()
/*N*/ {
/*N*/     ASSERT( ! bReverse,
/*N*/             "SwScanner::NextWord() currently not implemented for reverse mode" )
/*N*/
/*N*/     nBegin += nLen;
/*N*/
/*N*/     // first we have to skip some whitespace characters
/*N*/     const XubString& rText = rNode.GetTxt();
/*N*/     while ( nBegin < rText.Len() &&
/*N*/             lcl_IsSkippableWhiteSpace( rText.GetChar( nBegin ) ) )
/*N*/         ++nBegin;
/*N*/
/*N*/     if ( nBegin >= rText.Len() || nBegin >= nEndPos )
/*N*/         return FALSE;
/*N*/
/*N*/     // get next language in order to find next or previous word
/*N*/     const USHORT nNextScript =
/*N*/             pBreakIt->xBreak->getScriptType( rText, nBegin );
/*N*/     if ( nNextScript != GetI18NScriptTypeOfLanguage( aCurrLang ) )
/*N*/     {
/*N*/         LanguageType aNextLang = rNode.GetLang( nBegin, nNextScript );
/*N*/         aCurrLang = aNextLang;
/*N*/     }
/*N*/
/*N*/     // get the word boundaries
/*N*/     Boundary aBound = pBreakIt->xBreak->getWordBoundary( rText, nBegin,
/*N*/             pBreakIt->GetLocale( aCurrLang ), nWordType, sal_True );
/*N*/
/*N*/     // we have to differenciate between these cases:
/*N*/     if ( aBound.startPos <= nBegin )
/*N*/     {
/*N*/         ASSERT( aBound.endPos >= nBegin, "Unexpected aBound result" )
/*N*/
/*N*/         // restrict boundaries to script boundaries and nEndPos
/*N*/         const USHORT nCurrScript =
/*N*/                 pBreakIt->xBreak->getScriptType( rText, nBegin );
/*N*/
/*N*/         XubString aTmpWord = rText.Copy( nBegin, aBound.endPos - nBegin );
/*N*/         const long nScriptEnd = nBegin +
/*N*/             pBreakIt->xBreak->endOfScript( aTmpWord, 0, nCurrScript );
/*N*/         const long nEnd = Min( aBound.endPos, nScriptEnd );
/*N*/
/*N*/         // restrict word start to last script change position
/*N*/         long nScriptBegin = 0;
/*N*/         if ( aBound.startPos < nBegin )
/*N*/         {
/*N*/             // search from nBegin backwards until the next script change
/*N*/             aTmpWord = rText.Copy( aBound.startPos, nBegin - aBound.startPos + 1 );
/*N*/             nScriptBegin = aBound.startPos +
/*N*/                 pBreakIt->xBreak->beginOfScript( aTmpWord, nBegin - aBound.startPos,
/*N*/                                                 nCurrScript );
/*N*/         }
/*N*/
/*N*/         nBegin = (xub_StrLen)Max( aBound.startPos, nScriptBegin );
/*N*/         nLen = (xub_StrLen)(nEnd - nBegin);
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         const USHORT nCurrScript =
/*N*/                 pBreakIt->xBreak->getScriptType( rText, aBound.startPos );
/*N*/         XubString aTmpWord = rText.Copy( aBound.startPos, aBound.endPos - aBound.startPos );
/*N*/         const long nScriptEnd = aBound.startPos +
/*N*/             pBreakIt->xBreak->endOfScript( aTmpWord, 0, nCurrScript );
/*N*/         const long nEnd = Min( aBound.endPos, nScriptEnd );
/*N*/         nBegin = (xub_StrLen)aBound.startPos;
/*N*/         nLen = (xub_StrLen)(nEnd - nBegin);
/*N*/     }
/*N*/
/*N*/     if( ! nLen )
/*N*/         return FALSE;
/*N*/
/*N*/     aWord = rText.Copy( nBegin, nLen );
/*N*/
/*N*/     return TRUE;
/*N*/ }


/*M*/ BOOL SwScanner::NextWord( LanguageType aLang )
/*M*/ {
/*M*/     const XubString& rText = rNode.GetTxt();
/*M*/   if( bReverse )
/*M*/   {
/*M*/       if( nBegin )
/*M*/       {
/*M*/           --nBegin;
/*M*/             if( rNode.GetpSwpHints() )
/*M*/           {
/*M*/               while( CH_TXTATR_BREAKWORD == rText.GetChar( nBegin ) ||
/*M*/                       CH_TXTATR_INWORD == rText.GetChar( nBegin ) )
/*M*/               {
/*M*/                     if( rNode.GetTxtAttr( nBegin ) )
/*M*/                   {
/*M*/                       if( nBegin )
/*M*/                           --nBegin;
/*M*/                       else
/*M*/                           return FALSE;
/*M*/                   }
/*M*/                   else
/*M*/                       break;
/*M*/               }
/*M*/           }
/*M*/       }
/*M*/       else
/*M*/           return FALSE;
/*M*/   }
/*M*/   else if( nBegin + nLen >= rText.Len() )
/*M*/       return FALSE;
/*M*/
/*M*/     if( pWrong )
/*M*/   {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/         xub_StrLen nOldBegin = nBegin;
//STRIP001 /*?*/        nBegin = bReverse ? pWrong->LastWrong( nBegin )
//STRIP001 /*?*/                          : pWrong->NextWrong( nBegin );
//STRIP001 /*?*/
//STRIP001 /*?*/        if( STRING_LEN == nBegin )
//STRIP001 /*?*/            return FALSE;
//STRIP001 /*?*/
//STRIP001 /*?*/         // We make sure that we do not step backwards in order to avoid
//STRIP001 /*?*/         // endless loops.
//STRIP001 /*?*/         if ( ( bReverse && nBegin > nOldBegin ) ||
//STRIP001 /*?*/              ( ! bReverse && nBegin < nOldBegin ) )
//STRIP001 /*?*/              nBegin = nOldBegin;
//STRIP001 /*?*/
//STRIP001 /*?*/         // if we jumped over a range marked as valid, we have to adjust
//STRIP001 /*?*/         // the word boundaries
//STRIP001 /*?*/         if ( nBegin != nOldBegin )
//STRIP001 /*?*/             bStart = TRUE;
/*M*/   }
/*M*/
/*M*/   Boundary aBound;
/*M*/     if( bStart )
/*M*/   {
/*M*/       aBound = pBreakIt->xBreak->getWordBoundary( rText, nBegin,
/*M*/             pBreakIt->GetLocale( aLang ), nWordType, !bReverse );
/*M*/         bStart = aBound.startPos != aBound.endPos;
/*M*/   }
/*M*/   if( !bStart )
/*M*/   {
/*M*/       if( bReverse )
/*M*/           aBound = pBreakIt->xBreak->previousWord( rText, nBegin,
/*M*/                     pBreakIt->GetLocale( aLang ), nWordType );
/*M*/       else
/*M*/           aBound = pBreakIt->xBreak->nextWord( rText, nBegin,
/*M*/                     pBreakIt->GetLocale( aLang ), nWordType );
/*M*/   }
/*M*/   else
/*M*/       bStart = FALSE;
/*M*/
/*M*/   nBegin = (xub_StrLen)aBound.startPos;
/*N*/     nLen = (xub_StrLen)(aBound.endPos - nBegin);
/*M*/   if( !nLen )
/*M*/       return FALSE;
/*M*/
/*M*/     // only in online spelling mode we want to consider the last word
/*M*/     // surrounding nEndPos
/*M*/     if( bReverse )
/*M*/   {
/*M*/         if( nBegin + ( bIsOnlineSpell ? nLen : 0 ) < nEndPos )
/*M*/           return FALSE;
/*M*/   }
/*M*/   else
/*M*/   {
/*M*/         if( nBegin + ( bIsOnlineSpell ? 0 : nLen ) > nEndPos )
/*M*/           return FALSE;
/*M*/   }
/*M*/
/*M*/     aWord = rText.Copy( nBegin, nLen );
/*M*/
/*M*/     return TRUE;
/*M*/ }

//STRIP001 USHORT SwTxtNode::Spell(SwSpellArgs* pArgs)
//STRIP001 {
//STRIP001  // Die Aehnlichkeiten zu SwTxtFrm::_AutoSpell sind beabsichtigt ...
//STRIP001  // ACHTUNG: Ev. Bugs in beiden Routinen fixen!
//STRIP001
//STRIP001     //!! please check SwTxtNode::Convert when modifying this one !!
//STRIP001
//STRIP001  Reference<beans::XPropertySet> xProp( GetLinguPropertySet() );
//STRIP001  BOOL bReverse = xProp.is() ?
//STRIP001      *(sal_Bool*)xProp->getPropertyValue( C2U(UPN_IS_WRAP_REVERSE) ).getValue() : FALSE;
//STRIP001
//STRIP001  xub_StrLen nBegin, nEnd;
//STRIP001
//STRIP001     // modify string according to redline information
//STRIP001     const SwDoc* pDoc = GetDoc();
//STRIP001     const XubString aOldTxt( aText );
//STRIP001     const sal_Bool bShowChg = ::IsShowChanges( pDoc->GetRedlineMode() );
//STRIP001     if ( bShowChg )
//STRIP001     {
//STRIP001         USHORT nAct = pDoc->GetRedlinePos( *this );
//STRIP001
//STRIP001         for ( ; nAct < pDoc->GetRedlineTbl().Count(); nAct++ )
//STRIP001         {
//STRIP001             const SwRedline* pRed = pDoc->GetRedlineTbl()[ nAct ];
//STRIP001
//STRIP001             if ( pRed->Start()->nNode > GetIndex() )
//STRIP001                 break;
//STRIP001
//STRIP001             if( REDLINE_DELETE == pRed->GetType() )
//STRIP001             {
//STRIP001                 USHORT nStart, nEnd;
//STRIP001                 pRed->CalcStartEnd( GetIndex(), nStart, nEnd );
//STRIP001
//STRIP001                 while ( nStart < nEnd && nStart < aText.Len() )
//STRIP001                     aText.SetChar( nStart++, CH_TXTATR_INWORD );
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     if ( pArgs->pStartNode != this )
//STRIP001      nBegin = 0;
//STRIP001  else
//STRIP001      nBegin = pArgs->rStartIdx.GetIndex();
//STRIP001
//STRIP001  if ( pArgs->pEndNode != this )
//STRIP001      nEnd = aText.Len();
//STRIP001  else
//STRIP001      nEnd = pArgs->rEndIdx.GetIndex();
//STRIP001
//STRIP001  pArgs->xSpellAlt = NULL;
//STRIP001
//STRIP001     // 4 cases:
//STRIP001     //
//STRIP001     // 1. IsWrongDirty = 0 and GetWrong = 0
//STRIP001     //      Everything is checked and correct
//STRIP001     // 2. IsWrongDirty = 0 and GetWrong = 1
//STRIP001     //      Everything is checked and errors are identified in the wrong list
//STRIP001     // 3. IsWrongDirty = 1 and GetWrong = 0
//STRIP001     //      Nothing has been checked
//STRIP001     // 4. IsWrongDirty = 1 and GetWrong = 1
//STRIP001     //      Text has been checked but there is an invalid range in the wrong list
//STRIP001     //
//STRIP001     // Nothing has to be done for case 1.
//STRIP001  if( ( IsWrongDirty() || GetWrong() ) && aText.Len() )
//STRIP001  {
//STRIP001      if( nBegin > aText.Len() )
//STRIP001          nBegin = aText.Len();
//STRIP001      if( nEnd > aText.Len() )
//STRIP001          nEnd = aText.Len();
//STRIP001
//STRIP001         LanguageType eActLang = GetLang( nBegin );
//STRIP001
//STRIP001         // In case 2. we pass the wrong list to the scanned, because only
//STRIP001         // the words in the wrong list have to be checked
//STRIP001         SwScanner aScanner( *this, IsWrongDirty() ? NULL : GetWrong(),
//STRIP001                             WordType::DICTIONARY_WORD,
//STRIP001                             nBegin, nEnd, bReverse, FALSE );
//STRIP001      while( !pArgs->xSpellAlt.is() && aScanner.NextWord( eActLang ) )
//STRIP001      {
//STRIP001          const XubString& rWord = aScanner.GetWord();
//STRIP001
//STRIP001             // get next language for next word, consider language attributes
//STRIP001             // within the word
//STRIP001             eActLang = GetLang( aScanner.GetBegin(), rWord.Len() );
//STRIP001
//STRIP001             if( rWord.Len() > 1 && LANGUAGE_NONE != eActLang )
//STRIP001          {
//STRIP001              if (pArgs->xSpeller.is())
//STRIP001              {
//STRIP001                  SvxSpellWrapper::CheckSpellLang( pArgs->xSpeller, eActLang );
//STRIP001                  pArgs->xSpellAlt = pArgs->xSpeller->spell( rWord, eActLang,
//STRIP001                                          Sequence< PropertyValue >() );
//STRIP001              }
//STRIP001              if( (pArgs->xSpellAlt).is() )
//STRIP001              {
//STRIP001                  if( IsSymbol( aScanner.GetBegin() ) )
//STRIP001                  {
//STRIP001                      pArgs->xSpellAlt = NULL;
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      pArgs->pStartNode = this;
//STRIP001                      pArgs->pEndNode = this;
//STRIP001                      pArgs->rStartIdx.Assign(this, aScanner.GetEnd() );
//STRIP001                      pArgs->rEndIdx.Assign(this, aScanner.GetBegin() );
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001             // get next language in order to find next or previous word
//STRIP001             xub_StrLen nNextBegin;
//STRIP001             short nInc;
//STRIP001
//STRIP001             if ( bReverse )
//STRIP001             {
//STRIP001                 nNextBegin = aScanner.GetBegin() ? aScanner.GetBegin() - 1 : 0;
//STRIP001                 nInc = -1;
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 nNextBegin = aScanner.GetBegin() + rWord.Len();
//STRIP001                 nInc = 1;
//STRIP001             }
//STRIP001
//STRIP001             // first we have to skip some whitespace characters
//STRIP001             while ( ( bReverse ? nNextBegin : ( nNextBegin < aText.Len() ) ) &&
//STRIP001                     lcl_IsSkippableWhiteSpace( aText.GetChar( nNextBegin ) ) )
//STRIP001             {
//STRIP001                 nNextBegin += nInc;
//STRIP001             }
//STRIP001
//STRIP001             if ( nNextBegin < aText.Len() )
//STRIP001                 eActLang = GetLang( nNextBegin );
//STRIP001             else
//STRIP001                 break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001     // reset original text
//STRIP001     if ( bShowChg )
//STRIP001         aText = aOldTxt;
//STRIP001
//STRIP001     return pArgs->xSpellAlt.is() ? 1 : 0;
//STRIP001 }

//STRIP001 USHORT SwTxtNode::Convert( SwConversionArgs &rArgs )
//STRIP001 {
//STRIP001     //!! mofified version of SwTxtNode::Spell.          !!
//STRIP001     //!! please check the above when modifying this one !!
//STRIP001
//STRIP001     xub_StrLen nBegin, nEnd;
//STRIP001
//STRIP001     // modify string according to redline information
//STRIP001     const SwDoc* pDoc = GetDoc();
//STRIP001     const XubString aOldTxt( aText );
//STRIP001     const sal_Bool bShowChg = ::IsShowChanges( pDoc->GetRedlineMode() );
//STRIP001     if ( bShowChg )
//STRIP001     {
//STRIP001         USHORT nAct = pDoc->GetRedlinePos( *this );
//STRIP001
//STRIP001         for ( ; nAct < pDoc->GetRedlineTbl().Count(); nAct++ )
//STRIP001         {
//STRIP001             const SwRedline* pRed = pDoc->GetRedlineTbl()[ nAct ];
//STRIP001
//STRIP001             if ( pRed->Start()->nNode > GetIndex() )
//STRIP001                 break;
//STRIP001
//STRIP001             if( REDLINE_DELETE == pRed->GetType() )
//STRIP001             {
//STRIP001                 USHORT nStart, nEnd;
//STRIP001                 pRed->CalcStartEnd( GetIndex(), nStart, nEnd );
//STRIP001
//STRIP001                 while ( nStart < nEnd && nStart < aText.Len() )
//STRIP001                     aText.SetChar( nStart++, CH_TXTATR_INWORD );
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     if ( rArgs.pStartNode != this )
//STRIP001         nBegin = 0;
//STRIP001     else
//STRIP001         nBegin = rArgs.rStartIdx.GetIndex();
//STRIP001
//STRIP001     if ( rArgs.pEndNode != this )
//STRIP001         nEnd = aText.Len();
//STRIP001     else
//STRIP001         nEnd = rArgs.rEndIdx.GetIndex();
//STRIP001
//STRIP001     rArgs.bConvTextFound = sal_False;
//STRIP001
//STRIP001     if(aText.Len() )
//STRIP001     {
//STRIP001         if( nBegin > aText.Len() )
//STRIP001             nBegin = aText.Len();
//STRIP001         if( nEnd > aText.Len() )
//STRIP001             nEnd = aText.Len();
//STRIP001
//STRIP001         LanguageType eActLang = GetLang( nBegin );
//STRIP001
//STRIP001         // In case 2. we pass the wrong list to the scanned, because only
//STRIP001         // the words in the wrong list have to be checked
//STRIP001         SwScanner aScanner( *this, NULL,
//STRIP001                             WordType::DICTIONARY_WORD,
//STRIP001                             nBegin, nEnd, FALSE, TRUE );
//STRIP001         while( !rArgs.bConvTextFound && aScanner.NextWord() )
//STRIP001         {
//STRIP001             const XubString& rWord = aScanner.GetWord();
//STRIP001
//STRIP001             // get next language for next word, consider language attributes
//STRIP001             // within the word
//STRIP001             eActLang = GetLang( aScanner.GetBegin(), rWord.Len() );
//STRIP001
//STRIP001             if( rWord.Len() > 0 && LANGUAGE_KOREAN == eActLang )
//STRIP001             {
//STRIP001                 // clip result to provided begin and end (that may be
//STRIP001                 // obtained from a selection) in order to restrict the
//STRIP001                 // results to that selection
//STRIP001                 xub_StrLen nRealBegin = aScanner.GetBegin();
//STRIP001                 xub_StrLen nRealEnd   = aScanner.GetEnd();
//STRIP001                 if (nRealBegin < nBegin)
//STRIP001                     nRealBegin = nBegin;
//STRIP001                 if (nRealEnd > nEnd)
//STRIP001                     nRealEnd = nEnd;
//STRIP001
//STRIP001                 rArgs.bConvTextFound = sal_True;
//STRIP001                 xub_StrLen nCpStart, nCpLen;
//STRIP001                 nCpStart = nRealBegin - aScanner.GetBegin();
//STRIP001                 nCpLen = nRealEnd - nRealBegin;
//STRIP001                 rArgs.aConvText = rWord.Copy( nCpStart, nCpLen );
//STRIP001                 rArgs.pStartNode = this;
//STRIP001                 rArgs.pEndNode = this;
//STRIP001                 rArgs.rStartIdx.Assign(this, nRealEnd );
//STRIP001                 rArgs.rEndIdx.Assign(this, nRealBegin );
//STRIP001             }
//STRIP001
//STRIP001             // get next language in order to find next or previous word
//STRIP001             xub_StrLen nNextBegin = aScanner.GetBegin() + rWord.Len();
//STRIP001
//STRIP001             // first we have to skip some whitespace characters
//STRIP001             short nInc = 1;
//STRIP001             while ( nNextBegin < aText.Len() &&
//STRIP001                     lcl_IsSkippableWhiteSpace( aText.GetChar( nNextBegin ) ) )
//STRIP001             {
//STRIP001                 nNextBegin += nInc;
//STRIP001             }
//STRIP001
//STRIP001             if ( nNextBegin < aText.Len() )
//STRIP001                 eActLang = GetLang( nNextBegin );
//STRIP001             else
//STRIP001                 break;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     // reset original text
//STRIP001     if ( bShowChg )
//STRIP001         aText = aOldTxt;
//STRIP001
//STRIP001     return rArgs.bConvTextFound ? 1 : 0;
//STRIP001 }


//STRIP001 SwRect SwTxtFrm::_AutoSpell( SwCntntNode* pActNode, xub_StrLen nActPos )
//STRIP001 {
//STRIP001  SwRect aRect;
//STRIP001 #if OSL_DEBUG_LEVEL > 1
//STRIP001  static BOOL bStop = FALSE;
//STRIP001  if ( bStop )
//STRIP001      return aRect;
//STRIP001 #endif
//STRIP001  // Die Aehnlichkeiten zu SwTxtNode::Spell sind beabsichtigt ...
//STRIP001  // ACHTUNG: Ev. Bugs in beiden Routinen fixen!
//STRIP001  SwTxtNode *pNode = GetTxtNode();
//STRIP001  if( pNode != pActNode || !nActPos )
//STRIP001      nActPos = STRING_LEN;
//STRIP001
//STRIP001     SwDoc* pDoc = pNode->GetDoc();
//STRIP001     SwAutoCompleteWord& rACW = SwDoc::GetAutoCompleteWords();
//STRIP001
//STRIP001     // modify string according to redline information
//STRIP001     USHORT nAct = pDoc->GetRedlinePos( *pNode );
//STRIP001     const XubString aOldTxt( pNode->aText );
//STRIP001
//STRIP001     const sal_Bool bShowChg = ::IsShowChanges( pDoc->GetRedlineMode() );
//STRIP001     if ( bShowChg )
//STRIP001     {
//STRIP001         for ( ; nAct < pDoc->GetRedlineTbl().Count(); nAct++ )
//STRIP001         {
//STRIP001             const SwRedline* pRed = pDoc->GetRedlineTbl()[ nAct ];
//STRIP001
//STRIP001             if ( pRed->Start()->nNode > pNode->GetIndex() )
//STRIP001                 break;
//STRIP001
//STRIP001             if( REDLINE_DELETE == pRed->GetType() )
//STRIP001             {
//STRIP001                 USHORT nStart, nEnd;
//STRIP001                 pRed->CalcStartEnd( pNode->GetIndex(), nStart, nEnd );
//STRIP001
//STRIP001                 while ( nStart < nEnd && nStart < pNode->aText.Len() )
//STRIP001                     pNode->aText.SetChar( nStart++, CH_TXTATR_INWORD );
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     // a change of data indicates that at least one word has been modified
//STRIP001     sal_Bool bRedlineChg = ( pNode->aText.GetBuffer() != aOldTxt.GetBuffer() );
//STRIP001
//STRIP001     xub_StrLen nBegin;
//STRIP001  xub_StrLen nEnd;
//STRIP001  xub_StrLen nLen;
//STRIP001  xub_StrLen nInsertPos = pNode->aText.Len();
//STRIP001  xub_StrLen nChgStart = STRING_LEN;
//STRIP001  xub_StrLen nChgEnd = 0;
//STRIP001  xub_StrLen nInvStart = STRING_LEN;
//STRIP001  xub_StrLen nInvEnd = 0;
//STRIP001
//STRIP001  BOOL bAddAutoCmpl = pNode->IsAutoCompleteWordDirty() &&
//STRIP001                      GetShell()->GetViewOptions()->IsAutoCompleteWords();
//STRIP001
//STRIP001  if( pNode->GetWrong() )
//STRIP001  {
//STRIP001      if( STRING_LEN != ( nBegin = pNode->GetWrong()->GetBeginInv() ) )
//STRIP001      {
//STRIP001          nBegin = pNode->GetWrong()->GetBeginInv();
//STRIP001          nEnd = pNode->GetWrong()->GetEndInv();
//STRIP001          if ( nEnd > nInsertPos )
//STRIP001              nEnd = nInsertPos;
//STRIP001      }
//STRIP001      else
//STRIP001          nEnd = nInsertPos;
//STRIP001
//STRIP001         // get word around nBegin, we start at nBegin - 1
//STRIP001         if ( STRING_LEN != nBegin )
//STRIP001         {
//STRIP001             if ( nBegin )
//STRIP001                 --nBegin;
//STRIP001
//STRIP001             LanguageType eActLang = pNode->GetLang( nBegin );
//STRIP001             Boundary aBound = pBreakIt->xBreak->getWordBoundary( pNode->aText, nBegin,
//STRIP001                             pBreakIt->GetLocale( eActLang ), WordType::DICTIONARY_WORD, TRUE );
//STRIP001             nBegin = xub_StrLen(aBound.startPos);
//STRIP001         }
//STRIP001
//STRIP001         // get the position in the wrong list
//STRIP001         nInsertPos = pNode->GetWrong()->GetPos( nBegin );
//STRIP001
//STRIP001         // sometimes we have to skip one entry
//STRIP001      if( nInsertPos < pNode->GetWrong()->Count() &&
//STRIP001             nBegin == pNode->GetWrong()->Pos( nInsertPos ) +
//STRIP001                    pNode->GetWrong()->Len( nInsertPos ) )
//STRIP001                 nInsertPos++;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      nBegin = 0;
//STRIP001      nEnd = nInsertPos;
//STRIP001      nInsertPos = 0;
//STRIP001  }
//STRIP001
//STRIP001  BOOL bFresh = nBegin < nEnd;
//STRIP001  BOOL bACWDirty = FALSE;
//STRIP001
//STRIP001  if( nBegin < nEnd )
//STRIP001  {
//STRIP001         //! register listener to LinguServiceEvents now in order to get
//STRIP001         //! notified about relevant changes in the future
//STRIP001         SwModule *pModule = SW_MOD();
//STRIP001         if (!pModule->GetLngSvcEvtListener().is())
//STRIP001             pModule->CreateLngSvcEvtListener();
//STRIP001
//STRIP001         Reference< XSpellChecker1 > xSpell( ::GetSpellChecker() );
//STRIP001
//STRIP001         LanguageType eActLang = pNode->GetLang( nBegin );
//STRIP001
//STRIP001         SwScanner aScanner( *pNode, NULL, WordType::DICTIONARY_WORD,
//STRIP001                             nBegin, nEnd, FALSE, TRUE );
//STRIP001      while( aScanner.NextWord( eActLang ) )
//STRIP001      {
//STRIP001             const XubString& rWord = aScanner.GetWord();
//STRIP001          nBegin = aScanner.GetBegin();
//STRIP001          nLen = aScanner.GetLen();
//STRIP001
//STRIP001             // get next language for next word, consider language attributes
//STRIP001             // within the word
//STRIP001             eActLang = pNode->GetLang( aScanner.GetBegin(), rWord.Len() );
//STRIP001
//STRIP001          BOOL bSpell = TRUE;
//STRIP001          BOOL bSoft = FALSE;
//STRIP001          bSpell = xSpell.is() ? xSpell->hasLanguage( eActLang ) : FALSE;
//STRIP001          if( bSpell && rWord.Len() > 1 )
//STRIP001          {
//STRIP001              // check for: bAlter => xHyphWord.is()
//STRIP001              DBG_ASSERT(!bSpell || xSpell.is(), "NULL pointer");
//STRIP001
//STRIP001              if( !xSpell->isValid( rWord, eActLang, Sequence< PropertyValue >() ) )
//STRIP001              {
//STRIP001                  bACWDirty = TRUE;
//STRIP001                  if( !pNode->GetWrong() )
//STRIP001                  {
//STRIP001                      pNode->SetWrong( new SwWrongList() );
//STRIP001                      pNode->GetWrong()->SetInvalid( 0, nEnd );
//STRIP001                  }
//STRIP001                  if( pNode->GetWrong()->Fresh( nChgStart, nChgEnd,
//STRIP001                      nBegin, nLen, nInsertPos, nActPos ) )
//STRIP001                      pNode->GetWrong()->Insert( nBegin, nLen, nInsertPos++ );
//STRIP001                  else
//STRIP001                  {
//STRIP001                      nInvStart = nBegin;
//STRIP001                      nInvEnd = nBegin + nLen;
//STRIP001                  }
//STRIP001              }
//STRIP001              else if( bAddAutoCmpl && rACW.GetMinWordLen() <= rWord.Len() )
//STRIP001                 {
//STRIP001                     if ( bRedlineChg )
//STRIP001                     {
//STRIP001                         XubString rNewWord( rWord );
//STRIP001                         rNewWord.EraseAllChars( CH_TXTATR_INWORD );
//STRIP001                         rACW.InsertWord( rNewWord, *pDoc );
//STRIP001                     }
//STRIP001                     else
//STRIP001                         rACW.InsertWord( rWord, *pDoc );
//STRIP001                 }
//STRIP001          }
//STRIP001
//STRIP001             // get next language in order to find next word
//STRIP001             xub_StrLen nNextBegin = aScanner.GetBegin() + rWord.Len();
//STRIP001             // first we have to skip some whitespace characters
//STRIP001             while ( nNextBegin < pNode->aText.Len() &&
//STRIP001                     lcl_IsSkippableWhiteSpace( pNode->aText.GetChar( nNextBegin ) ) )
//STRIP001                 nNextBegin++;
//STRIP001
//STRIP001             if ( nNextBegin < pNode->aText.Len() )
//STRIP001                 eActLang = pNode->GetLang( nNextBegin );
//STRIP001             else
//STRIP001                 break;
//STRIP001      }
//STRIP001  }
//STRIP001  if( pNode->GetWrong() )
//STRIP001  {
//STRIP001      if( bFresh )
//STRIP001          pNode->GetWrong()->Fresh( nChgStart, nChgEnd,
//STRIP001                                    nEnd, 0, nInsertPos, nActPos );
//STRIP001      ViewShell *pSh = GetShell();
//STRIP001      if( nChgStart < nChgEnd &&
//STRIP001          (pSh && !GetShell()->GetViewOptions()->IsHideSpell()) )
//STRIP001      {
//STRIP001             SwNodeIndex aNdIdx( *pNode );
//STRIP001          SwPosition aPos( aNdIdx, SwIndex( pNode, nChgEnd ) );
//STRIP001          SwCrsrMoveState aTmpState( MV_NONE );
//STRIP001             aTmpState.b2Lines = sal_True;
//STRIP001             GetCharRect( aRect, aPos, &aTmpState );
//STRIP001             // information about end of repaint area
//STRIP001             Sw2LinesPos* pEnd2Pos = aTmpState.p2Lines;
//STRIP001
//STRIP001          SwTxtFrm* pStartFrm = this;
//STRIP001
//STRIP001             while( pStartFrm->HasFollow() &&
//STRIP001                    nChgStart >= pStartFrm->GetFollow()->GetOfst() )
//STRIP001                 pStartFrm = pStartFrm->GetFollow();
//STRIP001
//STRIP001             SwTxtFrm *pEndFrm = pStartFrm;
//STRIP001
//STRIP001             while( pEndFrm->HasFollow() &&
//STRIP001                    nChgEnd >= pEndFrm->GetFollow()->GetOfst() )
//STRIP001                 pEndFrm = pEndFrm->GetFollow();
//STRIP001
//STRIP001             if ( pEnd2Pos )
//STRIP001             {
//STRIP001                 // we are inside a special portion, take left border
//STRIP001                 SWRECTFN( pEndFrm )
//STRIP001                 (aRect.*fnRect->fnSetTop)( (pEnd2Pos->aLine.*fnRect->fnGetTop)() );
//STRIP001                 if ( pEndFrm->IsRightToLeft() )
//STRIP001                     (aRect.*fnRect->fnSetLeft)( (pEnd2Pos->aPortion.*fnRect->fnGetLeft)() );
//STRIP001                 else
//STRIP001                     (aRect.*fnRect->fnSetLeft)( (pEnd2Pos->aPortion.*fnRect->fnGetRight)() );
//STRIP001                 (aRect.*fnRect->fnSetWidth)( 1 );
//STRIP001                 (aRect.*fnRect->fnSetHeight)( (pEnd2Pos->aLine.*fnRect->fnGetHeight)() );
//STRIP001                 delete pEnd2Pos;
//STRIP001             }
//STRIP001
//STRIP001             aTmpState.p2Lines = NULL;
//STRIP001             SwRect aTmp;
//STRIP001          aPos = SwPosition( aNdIdx, SwIndex( pNode, nChgStart ) );
//STRIP001          GetCharRect( aTmp, aPos, &aTmpState );
//STRIP001             // information about start of repaint area
//STRIP001             Sw2LinesPos* pSt2Pos = aTmpState.p2Lines;
//STRIP001             if ( pSt2Pos )
//STRIP001             {
//STRIP001                 // we are inside a special portion, take right border
//STRIP001                 SWRECTFN( pStartFrm )
//STRIP001                 (aTmp.*fnRect->fnSetTop)( (pSt2Pos->aLine.*fnRect->fnGetTop)() );
//STRIP001                 if ( pStartFrm->IsRightToLeft() )
//STRIP001                     (aTmp.*fnRect->fnSetLeft)( (pSt2Pos->aPortion.*fnRect->fnGetRight)() );
//STRIP001                 else
//STRIP001                     (aTmp.*fnRect->fnSetLeft)( (pSt2Pos->aPortion.*fnRect->fnGetLeft)() );
//STRIP001                 (aTmp.*fnRect->fnSetWidth)( 1 );
//STRIP001                 (aTmp.*fnRect->fnSetHeight)( (pSt2Pos->aLine.*fnRect->fnGetHeight)() );
//STRIP001                 delete pSt2Pos;
//STRIP001             }
//STRIP001
//STRIP001          BOOL bSameFrame = TRUE;
//STRIP001
//STRIP001          if( HasFollow() )
//STRIP001          {
//STRIP001              if( pEndFrm != pStartFrm )
//STRIP001              {
//STRIP001                  bSameFrame = FALSE;
//STRIP001                  SwRect aStFrm( pStartFrm->PaintArea() );
//STRIP001                     {
//STRIP001                         SWRECTFN( pStartFrm )
//STRIP001                         (aTmp.*fnRect->fnSetLeft)( (aStFrm.*fnRect->fnGetLeft)() );
//STRIP001                         (aTmp.*fnRect->fnSetRight)( (aStFrm.*fnRect->fnGetRight)() );
//STRIP001                         (aTmp.*fnRect->fnSetBottom)( (aStFrm.*fnRect->fnGetBottom)() );
//STRIP001                     }
//STRIP001                     aStFrm = pEndFrm->PaintArea();
//STRIP001                     {
//STRIP001                         SWRECTFN( pEndFrm )
//STRIP001                         (aRect.*fnRect->fnSetTop)( (aStFrm.*fnRect->fnGetTop)() );
//STRIP001                         (aRect.*fnRect->fnSetLeft)( (aStFrm.*fnRect->fnGetLeft)() );
//STRIP001                         (aRect.*fnRect->fnSetRight)( (aStFrm.*fnRect->fnGetRight)() );
//STRIP001                     }
//STRIP001                  aRect.Union( aTmp );
//STRIP001                  while( TRUE )
//STRIP001                  {
//STRIP001                      pStartFrm = pStartFrm->GetFollow();
//STRIP001                      if( pStartFrm == pEndFrm )
//STRIP001                          break;
//STRIP001                      aRect.Union( pStartFrm->PaintArea() );
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          if( bSameFrame )
//STRIP001          {
//STRIP001                 SWRECTFN( pStartFrm )
//STRIP001                 if( (aTmp.*fnRect->fnGetTop)() == (aRect.*fnRect->fnGetTop)() )
//STRIP001                     (aRect.*fnRect->fnSetLeft)( (aTmp.*fnRect->fnGetLeft)() );
//STRIP001              else
//STRIP001              {
//STRIP001                  SwRect aStFrm( pStartFrm->PaintArea() );
//STRIP001                     (aRect.*fnRect->fnSetLeft)( (aStFrm.*fnRect->fnGetLeft)() );
//STRIP001                     (aRect.*fnRect->fnSetRight)( (aStFrm.*fnRect->fnGetRight)() );
//STRIP001                     (aRect.*fnRect->fnSetTop)( (aTmp.*fnRect->fnGetTop)() );
//STRIP001              }
//STRIP001
//STRIP001              if( aTmp.Height() > aRect.Height() )
//STRIP001                  aRect.Height( aTmp.Height() );
//STRIP001          }
//STRIP001      }
//STRIP001      pNode->GetWrong()->SetInvalid( nInvStart, nInvEnd );
//STRIP001      pNode->SetWrongDirty( STRING_LEN != pNode->GetWrong()->GetBeginInv() );
//STRIP001         if( !pNode->GetWrong()->Count() && ! pNode->IsWrongDirty() )
//STRIP001             pNode->SetWrong( NULL );
//STRIP001  }
//STRIP001  else
//STRIP001      pNode->SetWrongDirty( FALSE );
//STRIP001
//STRIP001     // reset original text
//STRIP001     if ( bShowChg )
//STRIP001         pNode->aText = aOldTxt;
//STRIP001
//STRIP001  if( bAddAutoCmpl )
//STRIP001      pNode->SetAutoCompleteWordDirty( FALSE );
//STRIP001  return aRect;
//STRIP001 }

// Wird vom CollectAutoCmplWords gerufen
/*M*/ void SwTxtFrm::CollectAutoCmplWrds( SwCntntNode* pActNode, xub_StrLen nActPos,
/*M*/                                   BOOL bIsVisArea )
/*M*/ {
/*M*/   SwTxtNode *pNode = GetTxtNode();
/*M*/   if( pNode != pActNode || !nActPos )
/*M*/       nActPos = STRING_LEN;
/*M*/
/*M*/   const XubString& rTxt = pNode->aText;
/*M*/     SwDoc* pDoc = pNode->GetDoc();
/*M*/     SwAutoCompleteWord& rACW = SwDoc::GetAutoCompleteWords();
/*M*/
/*M*/   xub_StrLen nBegin = 0;
/*M*/   xub_StrLen nEnd = pNode->aText.Len();
/*M*/   xub_StrLen nLen;
/*M*/   BOOL bACWDirty = FALSE, bAnyWrd = FALSE;
/*M*/
/*M*/
/*M*/   if( nBegin < nEnd )
/*M*/   {
/*M*/         USHORT nCnt = 200;
/*M*/         SwScanner aScanner( *pNode, NULL, WordType::DICTIONARY_WORD,
/*M*/                             nBegin, nEnd, FALSE, FALSE );
/*M*/       while( aScanner.NextWord( pNode->GetLang( nBegin ) ) )
/*M*/       {
/*M*/           nBegin = aScanner.GetBegin();
/*M*/           nLen = aScanner.GetLen();
/*M*/           if( rACW.GetMinWordLen() <= nLen )
/*M*/           {
/*M*/               const XubString& rWord = aScanner.GetWord();
/*M*/
/*M*/               if( nActPos < nBegin || ( nBegin + nLen ) < nActPos )
/*M*/               {
/*M*/ // !!! ---> ggfs. das Flag bIsVisarea auswerten
/*M*/                   if( rACW.GetMinWordLen() <= rWord.Len() )
/*M*/                         rACW.InsertWord( rWord, *pDoc );
/*M*/ // !!! ---> ggfs. das Flag bIsVisarea auswerten
/*M*/                   bAnyWrd = TRUE;
/*M*/               }
/*M*/               else
/*M*/                   bACWDirty = TRUE;
/*M*/           }
/*M*/             if( !--nCnt )
/*M*/             {
/*M*/                 if ( Application::AnyInput( INPUT_ANY ) )
/*M*/                     return;
/*M*/                 nCnt = 100;
/*M*/             }
/*M*/       }
/*M*/   }
/*M*/
/*M*/   if( bAnyWrd && !bACWDirty )
/*M*/       pNode->SetAutoCompleteWordDirty( FALSE );
/*M*/ }


/*************************************************************************
 *                      SwTxtNode::Hyphenate
 *************************************************************************/
// Findet den TxtFrm und sucht dessen CalcHyph



//STRIP001 BOOL SwTxtNode::Hyphenate( SwInterHyphInfo &rHyphInf )
//STRIP001 {
//STRIP001  // Abkuerzung: am Absatz ist keine Sprache eingestellt:
//STRIP001  if( LANGUAGE_NONE == USHORT( GetSwAttrSet().GetLanguage().GetLanguage() ) &&
//STRIP001      USHRT_MAX == GetLang( 0, aText.Len() ) )
//STRIP001  {
//STRIP001      if( !rHyphInf.IsCheck() )
//STRIP001          rHyphInf.SetNoLang( TRUE );
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  if( pLinguNode != this )
//STRIP001  {
//STRIP001      pLinguNode = this;
//STRIP001      pLinguFrm = (SwTxtFrm*)GetFrm( (Point*)(rHyphInf.GetCrsrPos()) );
//STRIP001  }
//STRIP001  SwTxtFrm *pFrm = pLinguFrm;
//STRIP001  if( pFrm )
//STRIP001      pFrm = pFrm->GetFrmAtOfst( rHyphInf.nStart );
//STRIP001  else
//STRIP001  {
//STRIP001      // 4935: Seit der Trennung ueber Sonderbereiche sind Faelle
//STRIP001      // moeglich, in denen kein Frame zum Node vorliegt.
//STRIP001      // Also kein ASSERT!
//STRIP001 #if OSL_DEBUG_LEVEL > 1
//STRIP001      ASSERT( pFrm, "!SwTxtNode::Hyphenate: can't find any frame" );
//STRIP001 #endif
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  while( pFrm )
//STRIP001  {
//STRIP001      if( pFrm->Hyphenate( rHyphInf ) )
//STRIP001      {
//STRIP001          // Das Layout ist nicht robust gegen "Direktformatierung"
//STRIP001          // (7821, 7662, 7408); vgl. layact.cxx,
//STRIP001          // SwLayAction::_TurboAction(), if( !pCnt->IsValid() ...
//STRIP001          pFrm->SetCompletePaint();
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001      pFrm = (SwTxtFrm*)(pFrm->GetFollow());
//STRIP001      if( pFrm )
//STRIP001      {
//STRIP001          rHyphInf.nLen = rHyphInf.nLen - (pFrm->GetOfst() - rHyphInf.nStart);
//STRIP001          rHyphInf.nStart = pFrm->GetOfst();
//STRIP001      }
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

#ifdef LINGU_STATISTIK

// globale Variable
SwLinguStatistik aSwLinguStat;


//STRIP001 void SwLinguStatistik::Flush()
//STRIP001 {
//STRIP001  if ( !nWords )
//STRIP001      return ;
//STRIP001
//STRIP001 #ifndef MAC
//STRIP001  static char *pLogName = 0;
//STRIP001  const BOOL bFirstOpen = pLogName ? FALSE : TRUE;
//STRIP001  if( bFirstOpen )
//STRIP001  {
//STRIP001      char *pPath = getenv( "TEMP" );
//STRIP001      char *pName = "swlingu.stk";
//STRIP001      if( !pPath )
//STRIP001          pLogName = pName;
//STRIP001      else
//STRIP001      {
//STRIP001          const int nLen = strlen(pPath);
//STRIP001          // fuer dieses new wird es kein delete geben.
//STRIP001          pLogName = new char[nLen + strlen(pName) + 3];
//STRIP001          if(nLen && (pPath[nLen-1] == '\\') || (pPath[nLen-1] == '/'))
//STRIP001              snprintf( pLogName, sizeof(pLogName), "%s%s", pPath, pName );
//STRIP001          else
//STRIP001              snprintf( pLogName, sizeof(pLogName), "%s/%s", pPath, pName );
//STRIP001      }
//STRIP001  }
//STRIP001  SvFileStream aStream( String::CreateFromAscii(pLogName), (bFirstOpen
//STRIP001                                      ? STREAM_WRITE | STREAM_TRUNC
//STRIP001                                      : STREAM_WRITE ));
//STRIP001
//STRIP001  if( !aStream.GetError() )
//STRIP001  {
//STRIP001      if ( bFirstOpen )
//STRIP001          aStream << "\nLinguistik-Statistik\n";
//STRIP001      aStream << endl << ++nFlushCnt << ". Messung\n";
//STRIP001      aStream << "Rechtschreibung\n";
//STRIP001      aStream << "gepruefte Worte: \t" << nWords << endl;
//STRIP001      aStream << "als fehlerhaft erkannt:\t" << nWrong << endl;
//STRIP001      aStream << "Alternativvorschlaege:\t" << nAlter << endl;
//STRIP001      if ( nWrong )
//STRIP001          aStream << "Durchschnitt:\t\t" << nAlter*1.0 / nWrong << endl;
//STRIP001      aStream << "Dauer (msec):\t\t" << nSpellTime << endl;
//STRIP001      aStream << "\nThesaurus\n";
//STRIP001      aStream << "Synonyme gesamt:\t" << nSynonym << endl;
//STRIP001      if ( nSynonym )
//STRIP001          aStream << "Synonym-Durchschnitt:\t" <<
//STRIP001                          nSynonym*1.0 / ( nWords - nNoSynonym ) << endl;
//STRIP001      aStream << "ohne Synonyme:\t\t" << nNoSynonym << endl;
//STRIP001      aStream << "Bedeutungen gesamt:\t" << nSynonym << endl;
//STRIP001      aStream << "keine Bedeutungen:\t"<< nNoSynonym << endl;
//STRIP001      aStream << "Dauer (msec):\t\t" << nTheTime << endl;
//STRIP001      aStream << "\nHyphenator\n";
//STRIP001      aStream << "Trennstellen gesamt:\t" << nHyphens << endl;
//STRIP001      if ( nHyphens )
//STRIP001          aStream << "Hyphen-Durchschnitt:\t" <<
//STRIP001                  nHyphens*1.0 / ( nWords - nNoHyph - nHyphErr ) << endl;
//STRIP001      aStream << "keine Trennstellen:\t" << nNoHyph << endl;
//STRIP001      aStream << "Trennung verweigert:\t" << nHyphErr << endl;
//STRIP001      aStream << "Dauer (msec):\t\t" << nHyphTime << endl;
//STRIP001      aStream << "---------------------------------------------\n";
//STRIP001  }
//STRIP001  nWords = nWrong = nAlter = nSynonym = nNoSynonym =
//STRIP001  nHyphens = nNoHyph = nHyphErr = nSpellTime = nTheTime =
//STRIP001  nHyphTime = 0;
//STRIP001  //pThes = NULL;
//STRIP001 #endif
//STRIP001 }

#endif

// change text to Upper/Lower/Hiragana/Katagana/...
//STRIP001 void SwTxtNode::TransliterateText( utl::TransliterationWrapper& rTrans,
//STRIP001      xub_StrLen nStart, xub_StrLen nEnd, SwUndoTransliterate* pUndo )
//STRIP001 {
//STRIP001  if( nStart < nEnd )
//STRIP001  {
//STRIP001      SwLanguageIterator* pIter;
//STRIP001      if( rTrans.needLanguageForTheMode() )
//STRIP001          pIter = new SwLanguageIterator( *this, nStart );
//STRIP001      else
//STRIP001          pIter = 0;
//STRIP001
//STRIP001      xub_StrLen nEndPos;
//STRIP001      sal_uInt16 nLang;
//STRIP001      do {
//STRIP001          if( pIter )
//STRIP001          {
//STRIP001              nLang = pIter->GetLanguage();
//STRIP001              nEndPos = pIter->GetChgPos();
//STRIP001              if( nEndPos > nEnd )
//STRIP001                  nEndPos = nEnd;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              nLang = LANGUAGE_SYSTEM;
//STRIP001              nEndPos = nEnd;
//STRIP001          }
//STRIP001          xub_StrLen nLen = nEndPos - nStart;
//STRIP001
//STRIP001          Sequence <long> aOffsets;
//STRIP001          String sChgd( rTrans.transliterate( aText, nLang, nStart, nLen,
//STRIP001                                                  &aOffsets ));
//STRIP001          if( !aText.Equals( sChgd, nStart, nLen ) )
//STRIP001          {
//STRIP001              if( pUndo )
//STRIP001                  pUndo->AddChanges( *this, nStart, nLen, aOffsets );
//STRIP001              ReplaceTextOnly( nStart, nLen, sChgd, aOffsets );
//STRIP001          }
//STRIP001          nStart = nEndPos;
//STRIP001      } while( nEndPos < nEnd && pIter && pIter->Next() );
//STRIP001      delete pIter;
//STRIP001  }
//STRIP001 }

//STRIP001 void SwTxtNode::ReplaceTextOnly( xub_StrLen nPos, xub_StrLen nLen,
//STRIP001                              const XubString& rText,
//STRIP001                              const Sequence<long>& rOffsets )
//STRIP001 {
//STRIP001  aText.Replace( nPos, nLen, rText );
//STRIP001
//STRIP001  xub_StrLen nTLen = rText.Len();
//STRIP001  const long* pOffsets = rOffsets.getConstArray();
//STRIP001  // now look for no 1-1 mapping -> move the indizies!
//STRIP001  xub_StrLen nI, nMyOff;
//STRIP001  for( nI = 0, nMyOff = nPos; nI < nTLen; ++nI, ++nMyOff )
//STRIP001  {
//STRIP001      xub_StrLen nOff = (xub_StrLen)pOffsets[ nI ];
//STRIP001      if( nOff < nMyOff )
//STRIP001      {
//STRIP001          // something is inserted
//STRIP001          xub_StrLen nCnt = 1;
//STRIP001          while( nI + nCnt < nTLen && nOff == pOffsets[ nI + nCnt ] )
//STRIP001              ++nCnt;
//STRIP001
//STRIP001          Update( SwIndex( this, nMyOff ), nCnt, FALSE );
//STRIP001          nMyOff = nOff;
//STRIP001          //nMyOff -= nCnt;
//STRIP001          nI += nCnt - 1;
//STRIP001      }
//STRIP001      else if( nOff > nMyOff )
//STRIP001      {
//STRIP001          // something is deleted
//STRIP001          Update( SwIndex( this, nMyOff+1 ), nOff - nMyOff, TRUE );
//STRIP001          nMyOff = nOff;
//STRIP001      }
//STRIP001  }
//STRIP001  if( nMyOff < nLen )
//STRIP001      // something is deleted at the end
//STRIP001      Update( SwIndex( this, nMyOff ), nLen - nMyOff, TRUE );
//STRIP001
//STRIP001  // notify the layout!
//STRIP001  SwDelTxt aDelHint( nPos, nTLen );
//STRIP001  SwModify::Modify( 0, &aDelHint );
//STRIP001
//STRIP001  SwInsTxt aHint( nPos, nTLen );
//STRIP001  SwModify::Modify( 0, &aHint );
//STRIP001 }
