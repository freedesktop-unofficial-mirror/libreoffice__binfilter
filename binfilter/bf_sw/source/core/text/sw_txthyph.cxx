/*************************************************************************
 *
 *  $RCSfile: sw_txthyph.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:41:08 $
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

#ifndef _UNO_LINGU_HXX
#include <bf_svx/unolingu.hxx>
#endif
#ifndef _COM_SUN_STAR_I18N_WORDTYPE_HPP_
#include <com/sun/star/i18n/WordType.hpp>
#endif

#ifndef _VIEWOPT_HXX
#include <viewopt.hxx>  // SwViewOptions
#endif
#ifndef _VIEWSH_HXX
#include <viewsh.hxx>
#endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif
#ifndef _TXTCFG_HXX
#include <txtcfg.hxx>
#endif
#ifndef _SW_PORTIONHANDLER_HXX
#include <SwPortionHandler.hxx>
#endif
#ifndef _PORHYPH_HXX
#include <porhyph.hxx>  //
#endif
#ifndef _INFTXT_HXX
#include <inftxt.hxx>
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>
#endif
#ifndef _ITRFORM2_HXX
#include <itrform2.hxx> //
#endif
#ifndef _GUESS_HXX
#include <guess.hxx>    //
#endif
#ifndef _SPLARGS_HXX
#include <splargs.hxx>  // SwInterHyphInfo
#endif
#ifndef _PORRST_HXX
#include <porrst.hxx>   // SwKernPortion
#endif
namespace binfilter {

#ifndef PRODUCT
extern const sal_Char *GetLangName( const MSHORT nLang );
#endif

using namespace ::rtl;
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::linguistic2;
using namespace ::com::sun::star::i18n;

/*************************************************************************
 *                      SwTxtFormatInfo::HyphWord()
 *************************************************************************/

//STRIP001 Reference< XHyphenatedWord >  SwTxtFormatInfo::HyphWord(
//STRIP001                              const XubString &rTxt, const MSHORT nMinTrail )
//STRIP001 {
//STRIP001  if( rTxt.Len() < 4 || pFnt->IsSymbol(pVsh) )
//STRIP001      return 0;
//STRIP001 //   ASSERT( IsHyphenate(), "SwTxtFormatter::HyphWord: why?" );
//STRIP001  Reference< XHyphenator >  xHyph = ::GetHyphenator();
//STRIP001  Reference< XHyphenatedWord > xHyphWord;
//STRIP001
//STRIP001  if( xHyph.is() )
//STRIP001      xHyphWord = xHyph->hyphenate( OUString(rTxt),
//STRIP001                          pBreakIt->GetLocale( pFnt->GetLanguage() ),
//STRIP001                          rTxt.Len() - nMinTrail, GetHyphValues() );
//STRIP001  return xHyphWord;
//STRIP001
//STRIP001 }

/*************************************************************************
 *                      SwTxtFrm::Hyphenate
 *
 * Wir formatieren eine Zeile fuer die interaktive Trennung
 *************************************************************************/

//STRIP001 sal_Bool SwTxtFrm::Hyphenate( SwInterHyphInfo &rHyphInf )
//STRIP001 {
//STRIP001 #ifdef VERTICAL_LAYOUT
//STRIP001     ASSERT( ! IsVertical() || ! IsSwapped(),"swapped frame at SwTxtFrm::Hyphenate" );
//STRIP001 #endif
//STRIP001     if( !pBreakIt->xBreak.is() )
//STRIP001      return sal_False;;
//STRIP001  // Wir machen den Laden erstmal dicht:
//STRIP001  ASSERT( !IsLocked(), "SwTxtFrm::Hyphenate: this is locked" );
//STRIP001  // 4935: Der ::com::sun::star::frame::Frame muss eine gueltige SSize haben!
//STRIP001  Calc();
//STRIP001  GetFormatted();
//STRIP001
//STRIP001  sal_Bool bRet = sal_False;
//STRIP001  if( !IsEmpty() )
//STRIP001  {
//STRIP001      // Wir muessen die Trennung immer einschalten.
//STRIP001      // Keine Angst, der SwTxtIter sichert im Hyphenate die alte Zeile.
//STRIP001      SwTxtFrmLocker aLock( this );
//STRIP001
//STRIP001 #ifdef VERTICAL_LAYOUT
//STRIP001         if ( IsVertical() )
//STRIP001             SwapWidthAndHeight();
//STRIP001 #endif
//STRIP001
//STRIP001         SwTxtFormatInfo aInf( this, sal_True );     // sal_True fuer interactive hyph!
//STRIP001      SwTxtFormatter aLine( this, &aInf );
//STRIP001         aLine.CharToLine( rHyphInf.nStart );
//STRIP001      // Wenn wir innerhalb des ersten Wortes einer Zeile stehen, so koennte
//STRIP001      // dieses in der vorherigen getrennt werden, deshalb gehen wir ein Zeile
//STRIP001      // zurueck.
//STRIP001      if( aLine.Prev() )
//STRIP001      {
//STRIP001          SwLinePortion *pPor = aLine.GetCurr()->GetFirstPortion();
//STRIP001          while( pPor->GetPortion() )
//STRIP001              pPor = pPor->GetPortion();
//STRIP001          if( pPor->GetWhichPor() == POR_SOFTHYPH ||
//STRIP001              pPor->GetWhichPor() == POR_SOFTHYPHSTR )
//STRIP001              aLine.Next();
//STRIP001      }
//STRIP001
//STRIP001      const xub_StrLen nEnd = rHyphInf.GetEnd();
//STRIP001      while( !bRet && aLine.GetStart() < nEnd )
//STRIP001      {
//STRIP001          DBG_LOOP;
//STRIP001          bRet = aLine.Hyphenate( rHyphInf );
//STRIP001          if( !aLine.Next() )
//STRIP001              break;
//STRIP001      }
//STRIP001
//STRIP001 #ifdef VERTICAL_LAYOUT
//STRIP001         if ( IsVertical() )
//STRIP001             SwapWidthAndHeight();
//STRIP001 #endif
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*************************************************************************
 *                      SwTxtFormatter::Hyphenate
 *
 * Wir formatieren eine Zeile fuer die interaktive Trennung
 *************************************************************************/
// Wir koennen davon ausgehen, dass bereits formatiert wurde.
// Fuer die CeBIT'93 gehen wir den einfachen, sicheren Weg:
// Die Zeile wird einfach neu formatiert, der Hyphenator wird dann
// so vorbereitet, wie ihn die UI erwartet.
// Hier stehen natuerlich enorme Optimierungsmoeglichkeiten offen.

//STRIP001 void SetParaPortion( SwTxtInfo *pInf, SwParaPortion *pRoot )
//STRIP001 {
//STRIP001  ASSERT( pRoot, "SetParaPortion: no root anymore" );
//STRIP001  pInf->pPara = pRoot;
//STRIP001 }

//STRIP001 sal_Bool SwTxtFormatter::Hyphenate( SwInterHyphInfo &rHyphInf )
//STRIP001 {
//STRIP001  SwTxtFormatInfo &rInf = GetInfo();
//STRIP001  sal_Bool bRet = sal_False;
//STRIP001
//STRIP001  // In der letzten Zeile gibt es nie etwas zu trennen.
//STRIP001  // Es sei denn, es befindet sich eine FlyPortion darin,
//STRIP001  // oder es ist die letzte Zeile des Masters
//STRIP001  if( !GetNext() && !rInf.GetTxtFly()->IsOn() && !pFrm->GetFollow() )
//STRIP001      return bRet;
//STRIP001
//STRIP001  xub_StrLen nWrdStart = nStart;
//STRIP001
//STRIP001  // Wir muessen die alte Zeile erhalten. Ein Beispiel:
//STRIP001  // Das Attribut fuer Trennung wurde nicht gesetzt,
//STRIP001  // in SwTxtFrm::Hyphenate wird es jedoch immer gesetzt,
//STRIP001  // weil wir Trennpositionen im Hyphenator einstellen wollen.
//STRIP001  SwLineLayout *pOldCurr = pCurr;
//STRIP001
//STRIP001  InitCntHyph();
//STRIP001
//STRIP001  // 5298: IsParaLine() (ex.IsFirstLine) fragt auf GetParaPortion() ab.
//STRIP001  // wir muessen gleiche Bedingungen schaffen: in der ersten
//STRIP001  // Zeile formatieren wir SwParaPortions...
//STRIP001  if( pOldCurr->IsParaPortion() )
//STRIP001  {
//STRIP001      SwParaPortion *pPara = new SwParaPortion();
//STRIP001      SetParaPortion( &rInf, pPara );
//STRIP001      pCurr = pPara;
//STRIP001      ASSERT( IsParaLine(), "SwTxtFormatter::Hyphenate: not the first" );
//STRIP001  }
//STRIP001  else
//STRIP001      pCurr = new SwLineLayout();
//STRIP001
//STRIP001  nWrdStart = FormatLine( nWrdStart );
//STRIP001
//STRIP001  // Man muss immer im Hinterkopf behalten, dass es z.B.
//STRIP001  // Felder gibt, die aufgetrennt werden koennen ...
//STRIP001  if( pCurr->PrtWidth() && pCurr->GetLen() )
//STRIP001  {
//STRIP001      // Wir muessen uns darauf einstellen, dass in der Zeile
//STRIP001      // FlyFrms haengen, an denen auch umgebrochen werden darf.
//STRIP001      // Wir suchen also die erste HyphPortion in dem angegebenen
//STRIP001      // Bereich.
//STRIP001
//STRIP001      SwLinePortion *pPos = pCurr->GetPortion();
//STRIP001      const xub_StrLen nPamStart = rHyphInf.nStart;
//STRIP001      nWrdStart = nStart;
//STRIP001      const xub_StrLen nEnd = rHyphInf.GetEnd();
//STRIP001      while( pPos )
//STRIP001      {
//STRIP001          // Entweder wir liegen drueber oder wir laufen gerade auf eine
//STRIP001          // Hyphportion die am Ende der Zeile oder vor einem Flys steht.
//STRIP001          if( nWrdStart >= nEnd )
//STRIP001          {
//STRIP001              nWrdStart = 0;
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001          if( nWrdStart >= nPamStart && pPos->InHyphGrp()
//STRIP001              && ( !pPos->IsSoftHyphPortion()
//STRIP001                   || ((SwSoftHyphPortion*)pPos)->IsExpand() ) )
//STRIP001          {
//STRIP001                 nWrdStart += pPos->GetLen();
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001          nWrdStart += pPos->GetLen();
//STRIP001          pPos = pPos->GetPortion();
//STRIP001      }
//STRIP001      // Wenn pPos 0 ist, wurde keine Trennstelle ermittelt.
//STRIP001      if( !pPos )
//STRIP001          nWrdStart = 0;
//STRIP001  }
//STRIP001
//STRIP001  // Das alte LineLayout wird wieder eingestellt ...
//STRIP001  delete pCurr;
//STRIP001  pCurr = pOldCurr;
//STRIP001
//STRIP001  if( pOldCurr->IsParaPortion() )
//STRIP001  {
//STRIP001      SetParaPortion( &rInf, (SwParaPortion*)pOldCurr );
//STRIP001      ASSERT( IsParaLine(), "SwTxtFormatter::Hyphenate: even not the first" );
//STRIP001  }
//STRIP001
//STRIP001  if( nWrdStart )
//STRIP001  {
//STRIP001      // nWrdStart bezeichnet nun die Position im String, der
//STRIP001      // fuer eine Trennung zur Debatte steht.
//STRIP001      // Start() hangelt sich zum End()
//STRIP001      rHyphInf.nWordStart = nWrdStart;
//STRIP001
//STRIP001      xub_StrLen nLen = 0;
//STRIP001      const xub_StrLen nEnd = nWrdStart;
//STRIP001
//STRIP001      // Wir suchen vorwaerts
//STRIP001      Reference< XHyphenatedWord > xHyphWord;
//STRIP001
//STRIP001      Boundary aBound =
//STRIP001          pBreakIt->xBreak->getWordBoundary( rInf.GetTxt(), nWrdStart,
//STRIP001          pBreakIt->GetLocale( rInf.GetFont()->GetLanguage() ), WordType::DICTIONARY_WORD, sal_True );
//STRIP001      nWrdStart = aBound.startPos;
//STRIP001      nLen = aBound.endPos - nWrdStart;
//STRIP001      bRet = 0 != nLen;
//STRIP001      if( bRet )
//STRIP001      {
//STRIP001          XubString aSelTxt( rInf.GetTxt().Copy(nWrdStart, nLen) );
//STRIP001          xub_StrLen nCnt = 0;
//STRIP001
//STRIP001 // these things should be handled by the dialog
//STRIP001 //            for( xub_StrLen i = 0; i < nLen; ++i )
//STRIP001 //            {
//STRIP001 //                sal_Unicode cCh = aSelTxt.GetChar(i);
//STRIP001 //                if( (CH_TXTATR_BREAKWORD == cCh || CH_TXTATR_INWORD == cCh )
//STRIP001 //                     && rInf.HasHint( nWrdStart + i ) )
//STRIP001 //                {
//STRIP001 //                    aSelTxt.Erase( i , 1 );
//STRIP001 //                    nCnt++;
//STRIP001 //                    --nLen;
//STRIP001 //                    if( i )
//STRIP001 //                        --i;
//STRIP001 //                }
//STRIP001 //            }
//STRIP001
//STRIP001          {
//STRIP001              MSHORT nMinTrail = 0;
//STRIP001              if( nWrdStart + nLen > nEnd )
//STRIP001                  nMinTrail = nWrdStart + nLen - nEnd - 1;
//STRIP001
//STRIP001              //!! rHyphInf.SetHyphWord( ... ) mu?hier geschehen
//STRIP001              xHyphWord = rInf.HyphWord( aSelTxt, nMinTrail );
//STRIP001              bRet = xHyphWord.is();
//STRIP001              if ( !rHyphInf.IsCheck() && sal_False == bRet )
//STRIP001                  rHyphInf.SetNoLang( sal_True );
//STRIP001          }
//STRIP001
//STRIP001          if( bRet )
//STRIP001          {
//STRIP001              rHyphInf.SetHyphWord( xHyphWord );
//STRIP001              rHyphInf.nWordStart = nWrdStart;
//STRIP001              rHyphInf.nWordLen   = nLen+nCnt;
//STRIP001              rHyphInf.SetNoLang( sal_False );
//STRIP001              rHyphInf.SetCheck( sal_True );
//STRIP001          }
//STRIP001 #ifdef DEBUGGY
//STRIP001          if( OPTDBG( rInf ) )
//STRIP001          {
//STRIP001              ASSERT( aSelTxt == aHyphWord,
//STRIP001                      "!SwTxtFormatter::Hyphenate: different words, different planets" );
//STRIP001              aDbstream << "Diff: \"" << aSelTxt.GetStr() << "\" != \""
//STRIP001                        << aHyphWord.GetStr() << "\"" << endl;
//STRIP001              ASSERT( bRet, "!SwTxtFormatter::Hyphenate: three of a perfect pair" );
//STRIP001              aDbstream << "Hyphenate: ";
//STRIP001          }
//STRIP001 #endif
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*************************************************************************
 *                      SwTxtPortion::CreateHyphen()
 *************************************************************************/

/*N*/ sal_Bool SwTxtPortion::CreateHyphen( SwTxtFormatInfo &rInf, SwTxtGuess &rGuess )
/*N*/ {
/*N*/   ASSERT( !pPortion, "SwTxtPortion::Hyphenate: another portion, another planet..." );
/*N*/   if( rInf.IsHyphForbud() ||
/*N*/       pPortion || // robust
/*N*/       // Mehrzeilige Felder duerfen nicht interaktiv getrennt werden.
/*N*/       ( rInf.IsInterHyph() && InFldGrp() ) )
/*N*/       return sal_False;
/*N*/
/*N*/   Reference< XHyphenatedWord >  xHyphWord = rGuess.HyphWord();
/*N*/   SwHyphPortion *pHyphPor;
/*N*/   xub_StrLen nPorEnd;
/*N*/   SwTxtSizeInfo aInf( rInf );
/*N*/
/*N*/   // first case: hyphenated word has alternative spelling
/*N*/   if ( xHyphWord.is() && xHyphWord->isAlternativeSpelling() ) {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001   SvxAlternativeSpelling aAltSpell;
//STRIP001 /*?*/        aAltSpell = SvxGetAltSpelling( xHyphWord );
//STRIP001 /*?*/        ASSERT( aAltSpell.bIsAltSpelling, "no alternatve spelling" );
//STRIP001 /*?*/
//STRIP001 /*?*/        XubString  aAltTxt   = aAltSpell.aReplacement;
//STRIP001 /*?*/         nPorEnd = aAltSpell.nChangedPos + rGuess.BreakStart() - rGuess.FieldDiff();
//STRIP001 /*?*/        xub_StrLen nTmpLen = 0;
//STRIP001 /*?*/
//STRIP001 /*?*/        // soft hyphen at alternative spelling position?
//STRIP001 /*?*/        if( rInf.GetTxt().GetChar( rInf.GetSoftHyphPos() ) == CHAR_SOFTHYPHEN )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pHyphPor = new SwSoftHyphStrPortion( aAltTxt );
//STRIP001 /*?*/            nTmpLen = 1;
//STRIP001 /*?*/        }
//STRIP001 /*?*/        else {
//STRIP001 /*?*/            pHyphPor = new SwHyphStrPortion( aAltTxt );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        // length of pHyphPor is adjusted
//STRIP001 /*?*/        pHyphPor->SetLen( aAltTxt.Len() + 1 );
//STRIP001 /*?*/        (SwPosSize&)(*pHyphPor) = pHyphPor->GetTxtSize( rInf );
//STRIP001 /*?*/        pHyphPor->SetLen( aAltSpell.nChangedLength + nTmpLen );
/*N*/   } else {
/*N*/       // second case: no alternative spelling
/*N*/       SwHyphPortion aHyphPor;
/*N*/       aHyphPor.SetLen( 1 );
/*N*/
/*N*/       static const void* pLastMagicNo = 0;
/*N*/       static KSHORT aMiniCacheH = 0, aMiniCacheW = 0;
/*N*/       const void* pTmpMagic;
/*N*/       MSHORT nFntIdx;
/*N*/       rInf.GetFont()->GetMagic( pTmpMagic, nFntIdx, rInf.GetFont()->GetActual() );
/*N*/       if( !pLastMagicNo || pLastMagicNo != pTmpMagic ) {
/*N*/           pLastMagicNo = pTmpMagic;
/*N*/           (SwPosSize&)aHyphPor = aHyphPor.GetTxtSize( rInf );
/*N*/           aMiniCacheH = aHyphPor.Height(), aMiniCacheW = aHyphPor.Width();
/*N*/       } else {
/*N*/           aHyphPor.Height( aMiniCacheH ), aHyphPor.Width( aMiniCacheW );
/*N*/       }
/*N*/       aHyphPor.SetLen( 0 );
/*N*/       pHyphPor = new SwHyphPortion( aHyphPor );
/*N*/
/*N*/       pHyphPor->SetWhichPor( POR_HYPH );
/*N*/
/*N*/       // values required for this
/*N*/         nPorEnd = xHyphWord->getHyphenPos() + 1 + rGuess.BreakStart()
/*N*/                 - rGuess.FieldDiff();
/*N*/   }
/*N*/
/*N*/   // portion end must be in front of us
/*N*/   // we do not put hyphens at start of line
/*N*/   if ( nPorEnd > rInf.GetIdx() ||
/*N*/        ( nPorEnd == rInf.GetIdx() && rInf.GetLineStart() != rInf.GetIdx() ) )
/*N*/   {
/*N*/       aInf.SetLen( nPorEnd - rInf.GetIdx() );
/*N*/       pHyphPor->SetAscent( GetAscent() );
/*N*/       SetLen( aInf.GetLen() );
/*N*/       CalcTxtSize( aInf );
/*N*/
/*N*/       Insert( pHyphPor );
/*N*/
/*N*/       short nKern = rInf.GetFont()->CheckKerning();
/*N*/       if( nKern )
/*N*/           new SwKernPortion( *this, nKern );
/*N*/
/*N*/       return sal_True;
/*N*/   }
/*N*/
/*N*/   // last exit for the lost
/*N*/   delete pHyphPor;
/*N*/   BreakCut( rInf, rGuess );
/*N*/   return sal_False;
/*N*/ }


/*************************************************************************
 *              virtual SwHyphPortion::GetExpTxt()
 *************************************************************************/

/*N*/ sal_Bool SwHyphPortion::GetExpTxt( const SwTxtSizeInfo &rInf, XubString &rTxt ) const
/*N*/ {
/*N*/   rTxt = '-';
/*N*/   return sal_True;
/*N*/ }

/*************************************************************************
 *              virtual SwHyphPortion::HandlePortion()
 *************************************************************************/

//STRIP001 void SwHyphPortion::HandlePortion( SwPortionHandler& rPH ) const
//STRIP001 {
//STRIP001     String aString( '-' );
//STRIP001     rPH.Special( GetLen(), aString, GetWhichPor() );
//STRIP001 }

/*************************************************************************
 *                 virtual SwHyphPortion::Format()
 *************************************************************************/

/*N*/ sal_Bool SwHyphPortion::Format( SwTxtFormatInfo &rInf )
/*N*/ {
/*N*/   register const SwLinePortion *pLast = rInf.GetLast();
/*N*/   Height( pLast->Height() );
/*N*/   SetAscent( pLast->GetAscent() );
/*N*/   XubString aTxt;
/*N*/
/*N*/   if( !GetExpTxt( rInf, aTxt ) )
/*N*/       return sal_False;
/*N*/
/*N*/   PrtWidth( rInf.GetTxtSize( aTxt ).Width() );
/*N*/   const sal_Bool bFull = rInf.Width() <= rInf.X() + PrtWidth();
/*N*/   if( bFull && !rInf.IsUnderFlow() ) {
/*?*/       Truncate();
/*?*/       rInf.SetUnderFlow( this );
/*N*/   }
/*N*/
/*N*/   return bFull;
/*N*/ }

/*************************************************************************
 *              virtual SwHyphStrPortion::GetExpTxt()
 *************************************************************************/

//STRIP001 sal_Bool SwHyphStrPortion::GetExpTxt( const SwTxtSizeInfo &, XubString &rTxt ) const
//STRIP001 {
//STRIP001  rTxt = aExpand;
//STRIP001  return sal_True;
//STRIP001 }

/*************************************************************************
 *              virtual SwHyphStrPortion::HandlePortion()
 *************************************************************************/

//STRIP001 void SwHyphStrPortion::HandlePortion( SwPortionHandler& rPH ) const
//STRIP001 {
//STRIP001     rPH.Special( GetLen(), aExpand, GetWhichPor() );
//STRIP001 }

/*************************************************************************
 *                      class SwSoftHyphPortion
 *************************************************************************/

/*N*/ SwLinePortion *SwSoftHyphPortion::Compress() { return this; }

/*N*/ SwSoftHyphPortion::SwSoftHyphPortion() :
/*N*/   bExpand(sal_False), nViewWidth(0), nHyphWidth(0)
/*N*/ {
/*N*/   SetLen(1);
/*N*/   SetWhichPor( POR_SOFTHYPH );
/*N*/ }

//STRIP001 KSHORT SwSoftHyphPortion::GetViewWidth( const SwTxtSizeInfo &rInf ) const
//STRIP001 {
//STRIP001  // Wir stehen zwar im const, aber nViewWidth sollte erst im letzten
//STRIP001  // Moment errechnet werden:
//STRIP001  if( !Width() && rInf.OnWin() && rInf.GetOpt().IsSoftHyph() && !IsExpand() )
//STRIP001  {
//STRIP001      if( !nViewWidth )
//STRIP001          ((SwSoftHyphPortion*)this)->nViewWidth
//STRIP001              = rInf.GetTxtSize( '-' ).Width();
//STRIP001  }
//STRIP001  else
//STRIP001      ((SwSoftHyphPortion*)this)->nViewWidth = 0;
//STRIP001  return nViewWidth;
//STRIP001 }

/*  Faelle:
 *  1) SoftHyph steht in der Zeile, ViewOpt aus.
 *     -> unsichtbar, Nachbarn unveraendert
 *  2) SoftHyph steht in der Zeile, ViewOpt an.
 *     -> sichtbar, Nachbarn veraendert
 *  3) SoftHyph steht am Zeilenende, ViewOpt aus/an.
 *     -> immer sichtbar, Nachbarn unveraendert
 */

//STRIP001 void SwSoftHyphPortion::Paint( const SwTxtPaintInfo &rInf ) const
//STRIP001 {
//STRIP001  if( Width() )
//STRIP001  {
//STRIP001      rInf.DrawViewOpt( *this, POR_SOFTHYPH );
//STRIP001      SwExpandPortion::Paint( rInf );
//STRIP001  }
//STRIP001 }

/*************************************************************************
 *                 virtual SwSoftHyphPortion::Format()
 *************************************************************************/

/* Die endgueltige Breite erhalten wir im FormatEOL().
 * In der Underflow-Phase stellen wir fest, ob ueberhaupt ein
 * alternatives Spelling vorliegt. Wenn ja ...
 *
 * Fall 1: "Au-to"
 * 1) {Au}{-}{to}, {to} passt nicht mehr => Underflow
 * 2) {-} ruft Hyphenate => keine Alternative
 * 3) FormatEOL() und bFull = sal_True
 *
 * Fall 2: "Zuc-ker"
 * 1) {Zuc}{-}{ker}, {ker} passt nicht mehr => Underflow
 * 2) {-} ruft Hyphenate => Alternative!
 * 3) Underflow() und bFull = sal_True
 * 4) {Zuc} ruft Hyphenate => {Zuk}{-}{ker}
 */

/*N*/ sal_Bool SwSoftHyphPortion::Format( SwTxtFormatInfo &rInf )
/*N*/ {
/*N*/   sal_Bool bFull = sal_True;
/*N*/
/*N*/   // special case for old german spelling
/*N*/   if( rInf.IsUnderFlow()  )
/*N*/   {
/*N*/       if( rInf.GetSoftHyphPos() )
/*N*/           return sal_True;
/*N*/
/*N*/       const sal_Bool bHyph = rInf.ChgHyph( sal_True );
/*N*/       if( rInf.IsHyphenate() )
/*N*/       {
/*N*/           rInf.SetSoftHyphPos( rInf.GetIdx() );
/*N*/           Width(0);
/*N*/           // if the soft hyphend word has an alternative spelling
/*N*/           // when hyphenated (old german spelling), the soft hyphen
/*N*/           // portion has to trigger an underflow
/*N*/           SwTxtGuess aGuess;
/*N*/           bFull = rInf.IsInterHyph() ||
/*N*/                   !aGuess.AlternativeSpelling( rInf, rInf.GetIdx() - 1 );
/*N*/       }
/*N*/       rInf.ChgHyph( bHyph );
/*N*/
/*N*/       if( bFull && !rInf.IsHyphForbud() )
/*N*/       {
/*N*/           rInf.SetSoftHyphPos(0);
/*N*/           FormatEOL( rInf );
/*N*/           if ( rInf.GetFly() )
/*?*/               rInf.GetRoot()->SetMidHyph( sal_True );
/*N*/           else
/*N*/               rInf.GetRoot()->SetEndHyph( sal_True );
/*N*/       }
/*N*/       else
/*N*/       {
/*?*/           rInf.SetSoftHyphPos( rInf.GetIdx() );
/*?*/           Truncate();
/*?*/           rInf.SetUnderFlow( this );
/*N*/       }
/*N*/       return sal_True;
/*N*/   }
/*N*/
/*N*/   rInf.SetSoftHyphPos(0);
/*N*/   SetExpand( sal_True );
/*N*/   bFull = SwHyphPortion::Format( rInf );
/*N*/   SetExpand( sal_False );
/*N*/   if( !bFull )
/*N*/   {
/*N*/       // default-maessig besitzen wir keine Breite, aber eine Hoehe
/*N*/       nHyphWidth = Width();
/*N*/       Width(0);
/*N*/   }
/*N*/   return bFull;
/*N*/ }

/*************************************************************************
 *                 virtual SwSoftHyphPortion::FormatEOL()
 *************************************************************************/
// Format end of Line

/*N*/ void SwSoftHyphPortion::FormatEOL( SwTxtFormatInfo &rInf )
/*N*/ {
/*N*/   if( !IsExpand() )
/*N*/   {
/*N*/       SetExpand( sal_True );
/*N*/       if( rInf.GetLast() == this )
/*?*/           rInf.SetLast( FindPrevPortion( rInf.GetRoot() ) );
/*N*/
/*N*/       // 5964: alte Werte muessen wieder zurueckgesetzt werden.
/*N*/       const KSHORT nOldX   = rInf.X();
/*N*/       const xub_StrLen nOldIdx = rInf.GetIdx();
/*N*/       rInf.X( rInf.X() - PrtWidth() );
/*N*/       rInf.SetIdx( rInf.GetIdx() - GetLen() );
/*N*/       const sal_Bool bFull = SwHyphPortion::Format( rInf );
/*N*/       nHyphWidth = Width();
/*N*/
/*N*/       // 6976: Eine truebe Sache: Wir werden erlaubterweise breiter,
/*N*/       // aber gleich wird noch ein Fly verarbeitet, der eine korrekte
/*N*/       // X-Position braucht.
/*N*/       if( bFull || !rInf.GetFly() )
/*N*/           rInf.X( nOldX );
/*N*/       else
/*?*/           rInf.X( nOldX + Width() );
/*N*/       rInf.SetIdx( nOldIdx );
/*N*/   }
/*N*/ }

/*************************************************************************
 *              virtual SwSoftHyphPortion::GetExpTxt()
 *
 * Wir expandieren:
 * - wenn die Sonderzeichen sichtbar sein sollen
 * - wenn wir am Ende der Zeile stehen.
 * - wenn wir vor einem (echten/emuliertem) Zeilenumbruch stehen
 *************************************************************************/

/*N*/ sal_Bool SwSoftHyphPortion::GetExpTxt( const SwTxtSizeInfo &rInf, XubString &rTxt ) const
/*N*/ {
/*N*/   if( IsExpand() || ( rInf.OnWin() && rInf.GetOpt().IsSoftHyph() ) ||
/*N*/       ( GetPortion() && ( GetPortion()->InFixGrp() ||
/*N*/         GetPortion()->IsDropPortion() || GetPortion()->IsLayPortion() ||
/*N*/         GetPortion()->IsParaPortion() || GetPortion()->IsBreakPortion() ) ) )
/*N*/   {
/*N*/       return SwHyphPortion::GetExpTxt( rInf, rTxt );
/*N*/   }
/*N*/   return sal_False;
/*N*/ }

/*************************************************************************
 *              virtual SwSoftHyphPortion::HandlePortion()
 *************************************************************************/

//STRIP001 void SwSoftHyphPortion::HandlePortion( SwPortionHandler& rPH ) const
//STRIP001 {
//STRIP001     const String aString( '-' );
//STRIP001     const USHORT nWhich = ! Width() ?
//STRIP001                           POR_SOFTHYPH_COMP :
//STRIP001                           GetWhichPor();
//STRIP001     rPH.Special( GetLen(), aString, nWhich );
//STRIP001 }

/*************************************************************************
 *                      SwSoftHyphStrPortion::Paint
 *************************************************************************/

/*N*/ void SwSoftHyphStrPortion::Paint( const SwTxtPaintInfo &rInf ) const
/*N*/ {
/*N*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //STRIP001    // Bug oder feature?:
//STRIP001  // {Zu}{k-}{ker}, {k-} wird grau statt {-}
//STRIP001  rInf.DrawViewOpt( *this, POR_SOFTHYPH );
//STRIP001  SwHyphStrPortion::Paint( rInf );
/*N*/ }

/*N*/ SwSoftHyphStrPortion::SwSoftHyphStrPortion( const XubString &rStr )
/*N*/   : SwHyphStrPortion( rStr )
/*N*/ {
/*N*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //STRIP001    SetLen( 1 );
//STRIP001  SetWhichPor( POR_SOFTHYPHSTR );
/*N*/ }



}
