/*************************************************************************
 *
 *  $RCSfile: sw_portxt.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:36:01 $
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

#include <ctype.h>

#ifndef _COM_SUN_STAR_I18N_SCRIPTTYPE_HDL_
#include <com/sun/star/i18n/ScriptType.hdl>
#endif
#ifndef _HINTIDS_HXX
#include <hintids.hxx>     // CH_TXTATR
#endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>   // ASSERT
#endif
#ifndef _SW_PORTIONHANDLER_HXX
#include <SwPortionHandler.hxx>
#endif
#ifndef _TXTCFG_HXX
#include <txtcfg.hxx>
#endif
#ifndef _PORLAY_HXX
#include <porlay.hxx>
#endif
#ifndef _INFTXT_HXX
#include <inftxt.hxx>
#endif
#ifndef _GUESS_HXX
#include <guess.hxx>    // SwTxtGuess, Zeilenumbruch
#endif
#ifndef _PORGLUE_HXX
#include <porglue.hxx>
#endif
#ifndef _POREXP_HXX
#include <porexp.hxx>   // HyphPortion
#endif
#ifndef _PORRST_HXX
#include <porrst.hxx>   // SwKernPortion
#endif
#ifndef _PORFLD_HXX
#include <porfld.hxx>       // SwFldPortion
#endif
#ifndef _WRONG_HXX
#include <wrong.hxx>
#endif

#if OSL_DEBUG_LEVEL > 1
const sal_Char *GetLangName( const MSHORT nLang );
#endif

using namespace ::com::sun::star::i18n::ScriptType;

/*************************************************************************
 *                          lcl_AddSpace
 * Returns for how many characters an extra space has to be added
 * (for justified alignment).
 *************************************************************************/

/*N*/ USHORT lcl_AddSpace( const SwTxtSizeInfo &rInf, const XubString* pStr,
/*N*/                      const SwLinePortion& rPor )
/*N*/ {
/*N*/     xub_StrLen nPos, nEnd;
/*N*/     const SwScriptInfo* pSI = 0;
/*N*/
/*N*/     if ( pStr )
/*N*/     {
/*N*/         // passing a string means we are inside a field
/*?*/         nPos = 0;
/*?*/         nEnd = pStr->Len();
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         nPos = rInf.GetIdx();
/*N*/         nEnd = rInf.GetIdx() + rPor.GetLen();
/*N*/         pStr = &rInf.GetTxt();
/*N*/         pSI = &((SwParaPortion*)rInf.GetParaPortion())->GetScriptInfo();
/*N*/     }
/*N*/
/*N*/     USHORT nCnt = 0;
/*N*/     BYTE nScript = 0;
/*N*/
/*N*/     // If portion consists of Asian characters and language is not
/*N*/     // Korean, we add extra space to each character.
/*N*/     // first we get the script type
/*N*/     if ( pSI )
/*N*/         nScript = pSI->ScriptType( nPos );
/*N*/     else if ( pBreakIt->xBreak.is() )
/*?*/         nScript = (BYTE)pBreakIt->xBreak->getScriptType( *pStr, nPos );
/*N*/
/*N*/     // Note: rInf.GetIdx() can differ from nPos,
/*N*/     // e.g., when rPor is a field portion. nPos referes to the string passed
/*N*/     // to the function, rInf.GetIdx() referes to the original string.
/*N*/
/*N*/     // We try to find out which justification mode is required. This is done by
/*N*/     // evaluating the script type and the language attribute set for this portion
/*N*/
/*N*/     // Asian Justification: Each character get some extra space
/*N*/     if ( nEnd > nPos && ASIAN == nScript )
/*N*/     {
/*N*/         LanguageType aLang =
/*N*/             rInf.GetTxtFrm()->GetTxtNode()->GetLang( rInf.GetIdx(), 1, nScript );
/*N*/
/*N*/         if ( LANGUAGE_KOREAN != aLang && LANGUAGE_KOREAN_JOHAB != aLang )
/*N*/         {
/*N*/             const SwLinePortion* pPor = rPor.GetPortion();
/*N*/             if ( pPor && pPor->IsKernPortion() )
/*N*/                 pPor = pPor->GetPortion();
/*N*/
/*N*/             nCnt += nEnd - nPos;
/*N*/
/*N*/             if ( !pPor || pPor->IsHolePortion() || pPor->InFixMargGrp() ||
/*N*/                   pPor->IsBreakPortion() )
/*N*/                 --nCnt;
/*N*/
/*N*/             return nCnt;
/*N*/         }
/*N*/     }
/*N*/
/*N*/     // Thai Justification: Each character cell gets some extra space
/*N*/     if ( nEnd > nPos && COMPLEX == nScript )
/*N*/     {
/*N*/         LanguageType aLang =
/*N*/             rInf.GetTxtFrm()->GetTxtNode()->GetLang( rInf.GetIdx(), 1, nScript );
/*N*/
/*N*/         if ( LANGUAGE_THAI == aLang )
/*N*/         {
                DBG_ASSERT(0, "STRIP"); //STRIP001 /*?*/             nCnt = SwScriptInfo::ThaiJustify( *pStr, 0, 0, nPos, nEnd - nPos );
//STRIP001 /*?*/
//STRIP001 /*?*/             const SwLinePortion* pPor = rPor.GetPortion();
//STRIP001 /*?*/             if ( pPor && pPor->IsKernPortion() )
//STRIP001 /*?*/                 pPor = pPor->GetPortion();
//STRIP001 /*?*/
//STRIP001 /*?*/             if ( nCnt && ( ! pPor || pPor->IsHolePortion() || pPor->InFixMargGrp() ) )
//STRIP001 /*?*/                 --nCnt;
//STRIP001 /*?*/
/*?*/             return nCnt;
/*N*/         }
/*N*/     }
/*N*/
/*N*/ #ifdef BIDI
/*N*/     // Kashida Justification: Insert Kashidas
/*N*/     if ( nEnd > nPos && pSI && COMPLEX == nScript )
/*N*/     {
            DBG_ASSERT(0, "STRIP"); //STRIP001 /*?*/         LanguageType aLang =
//STRIP001 /*?*/             rInf.GetTxtFrm()->GetTxtNode()->GetLang( rInf.GetIdx(), 1, nScript );
//STRIP001 /*?*/
//STRIP001 /*?*/         if ( SwScriptInfo::IsArabicLanguage( aLang ) )
//STRIP001 /*?*/             return pSI->KashidaJustify( 0, 0, nPos, nEnd - nPos );
/*N*/     }
/*N*/ #endif
/*N*/
/*N*/     // Here starts the good old "Look for blanks and add space to them" part.
/*N*/               // Note: We do not want to add space to an isolated latin blank in front
/*N*/     // of some complex characters in RTL environment
/*N*/     const sal_Bool bDoNotAddSpace =
/*N*/             LATIN == nScript && ( nEnd == nPos + 1 ) && pSI &&
/*N*/             ( ::com::sun::star::i18n::ScriptType::COMPLEX ==
/*N*/               pSI->ScriptType( nPos + 1 ) ) &&
/*N*/             rInf.GetTxtFrm() && rInf.GetTxtFrm()->IsRightToLeft();
/*N*/
/*N*/     if ( bDoNotAddSpace )
/*N*/         return nCnt;
/*N*/
/*N*/     for ( ; nPos < nEnd; ++nPos )
/*N*/     {
/*N*/         if( CH_BLANK == pStr->GetChar( nPos ) )
/*N*/             ++nCnt;
/*N*/     }
/*N*/
/*N*/     // We still have to examine the next character:
/*N*/     // If the next character is ASIAN and not KOREAN we have
/*N*/     // to add an extra space
/*N*/     // nPos referes to the original string, even if a field string has
/*N*/     // been passed to this function
/*N*/     nPos = rInf.GetIdx() + rPor.GetLen();
/*N*/     if ( nPos < rInf.GetTxt().Len() )
/*N*/     {
/*N*/         BYTE nNextScript = 0;
/*N*/         const SwLinePortion* pPor = rPor.GetPortion();
/*N*/         if ( pPor && pPor->IsKernPortion() )
/*?*/             pPor = pPor->GetPortion();
/*N*/
/*N*/         if ( ! pBreakIt->xBreak.is() || ! pPor || pPor->InFixMargGrp() )
/*N*/             return nCnt;
/*N*/
/*N*/         // next character is inside a field?
/*N*/         if ( CH_TXTATR_BREAKWORD == rInf.GetChar( nPos ) && pPor->InExpGrp() )
/*N*/         {
/*?*/             sal_Bool bOldOnWin = rInf.OnWin();
/*?*/             ((SwTxtSizeInfo &)rInf).SetOnWin( sal_False );
/*?*/
/*?*/             XubString aStr( aEmptyStr );
/*?*/             pPor->GetExpTxt( rInf, aStr );
/*?*/             ((SwTxtSizeInfo &)rInf).SetOnWin( bOldOnWin );
/*?*/
/*?*/             nNextScript = (BYTE)pBreakIt->xBreak->getScriptType( aStr, 0 );
/*N*/         }
/*N*/         else
/*N*/             nNextScript = (BYTE)pBreakIt->xBreak->getScriptType( rInf.GetTxt(), nPos );
/*N*/
/*N*/         if( ASIAN == nNextScript )
/*N*/         {
/*?*/             LanguageType aLang =
/*?*/                 rInf.GetTxtFrm()->GetTxtNode()->GetLang( nPos, 1, nNextScript );
/*?*/
/*?*/             if ( LANGUAGE_KOREAN != aLang && LANGUAGE_KOREAN_JOHAB != aLang )
/*?*/                 ++nCnt;
/*N*/         }
/*N*/     }
/*N*/
/*N*/     return nCnt;
/*N*/ }

/*************************************************************************
 *                      class SwTxtPortion
 *************************************************************************/

/*N*/ SwTxtPortion::SwTxtPortion( const SwLinePortion &rPortion )
/*N*/   : SwLinePortion( rPortion )
/*N*/ {
/*N*/   SetWhichPor( POR_TXT );
/*N*/ }

/*************************************************************************
 *                      SwTxtPortion::BreakCut()
 *************************************************************************/

/*N*/ void SwTxtPortion::BreakCut( SwTxtFormatInfo &rInf, const SwTxtGuess &rGuess )
/*N*/ {
/*N*/   // Das Wort/Zeichen ist groesser als die Zeile
/*N*/   // Sonderfall Nr.1: Das Wort ist groesser als die Zeile
/*N*/   // Wir kappen...
/*N*/   const KSHORT nLineWidth = (KSHORT)(rInf.Width() - rInf.X());
/*N*/   xub_StrLen nLen = rGuess.CutPos() - rInf.GetIdx();
/*N*/   if( nLen )
/*N*/   {
/*N*/       // special case: guess does not always provide the correct
/*N*/       // width, only in common cases.
/*N*/       if ( !rGuess.BreakWidth() )
/*N*/       {
/*N*/           rInf.SetLen( nLen );
/*N*/           SetLen( nLen );
/*N*/           CalcTxtSize( rInf );
/*N*/
/*N*/           // changing these values requires also changing them in
/*N*/           // guess.cxx
/*N*/           KSHORT nItalic = 0;
/*N*/           if( ITALIC_NONE != rInf.GetFont()->GetItalic() && !rInf.NotEOL() )
/*N*/           {
/*N*/ #ifdef MAC
/*N*/               nItalic = Height() / 4;
/*N*/ #else
/*N*/               nItalic = Height() / 12;
/*N*/ #endif
/*N*/           }
/*N*/           Width( Width() + nItalic );
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           Width( rGuess.BreakWidth() );
/*N*/           SetLen( nLen );
/*N*/       }
/*N*/   }
/*N*/     // special case: first character does not fit to line
/*N*/     else if ( rGuess.CutPos() == rInf.GetLineStart() )
/*N*/   {
/*N*/       SetLen( 1 );
/*N*/       Width( nLineWidth );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       SetLen( 0 );
/*N*/       Width( 0 );
/*N*/   }
/*N*/ }

/*************************************************************************
 *                      SwTxtPortion::BreakUnderflow()
 *************************************************************************/

/*N*/ void SwTxtPortion::BreakUnderflow( SwTxtFormatInfo &rInf )
/*N*/ {
/*N*/   Truncate();
/*N*/   Height( 0 );
/*N*/   Width( 0 );
/*N*/   SetLen( 0 );
/*N*/   SetAscent( 0 );
/*N*/   rInf.SetUnderFlow( this );
/*N*/ }

 /*************************************************************************
 *                      SwTxtPortion::_Format()
 *************************************************************************/

/*N*/ sal_Bool lcl_HasContent( const SwFldPortion& rFld, SwTxtFormatInfo &rInf )
/*N*/ {
/*N*/       String aTxt;
/*N*/   return rFld.GetExpTxt( rInf, aTxt ) && aTxt.Len();
/*N*/ }

/*M*/ sal_Bool SwTxtPortion::_Format( SwTxtFormatInfo &rInf )
/*M*/ {
/*M*/   // 5744: wenn nur der Trennstrich nicht mehr passt,
/*M*/   // muss trotzdem das Wort umgebrochen werden, ansonsten return sal_True!
/*M*/   if( rInf.IsUnderFlow() && rInf.GetSoftHyphPos() )
/*M*/   {
/*M*/       // soft hyphen portion has triggered an underflow event because
/*M*/       // of an alternative spelling position
/*M*/       sal_Bool bFull = sal_False;
/*M*/       const sal_Bool bHyph = rInf.ChgHyph( sal_True );
/*M*/       if( rInf.IsHyphenate() )
/*M*/       {
/*M*/           SwTxtGuess aGuess;
/*M*/           // check for alternative spelling left from the soft hyphen
/*M*/           // this should usually be true but
/*M*/           aGuess.AlternativeSpelling( rInf, rInf.GetSoftHyphPos() - 1 );
/*M*/           bFull = CreateHyphen( rInf, aGuess );
/*M*/             ASSERT( bFull, "Problem with hyphenation!!!" );
/*M*/       }
/*M*/       rInf.ChgHyph( bHyph );
/*M*/       rInf.SetSoftHyphPos( 0 );
/*M*/       return bFull;
/*M*/   }
/*M*/
/*M*/   SwTxtGuess aGuess;
/*M*/     const sal_Bool bFull = !aGuess.Guess( *this, rInf, Height() );
/*M*/
/*M*/   // these are the possible cases:
/*M*/   // A Portion fits to current line
/*M*/   // B Portion does not fit to current line but a possible line break
/*M*/   //   within the portion has been found by the break iterator, 2 subcases
/*M*/   //   B1 break is hyphen
/*M*/   //   B2 break is word end
/*M*/   // C Portion does not fit to current line and no possible line break
/*M*/   //   has been found by break iterator, 2 subcases:
/*M*/   //   C1 break iterator found a possible line break in portion before us
/*M*/   //      ==> this break is used (underflow)
/*M*/   //   C2 break iterator does not found a possible line break at all:
/*M*/   //      ==> line break
/*M*/
/*M*/       // case A: line not yet full
/*M*/   if ( !bFull )
/*M*/   {
/*M*/       Width( aGuess.BreakWidth() );
/*M*/       // Vorsicht !
/*M*/       if( !InExpGrp() || InFldGrp() )
/*M*/           SetLen( rInf.GetLen() );
/*M*/
/*M*/       short nKern = rInf.GetFont()->CheckKerning();
/*M*/       if( nKern > 0 && rInf.Width() < rInf.X() + Width() + nKern )
/*M*/       {
/*N*/           nKern = rInf.Width() - rInf.X() - Width() - 1;
/*M*/           if( nKern < 0 )
/*M*/               nKern = 0;
/*M*/       }
/*M*/       if( nKern )
/*M*/           new SwKernPortion( *this, nKern );
/*M*/   }
/*M*/     // special case: hanging portion
/*M*/     else if( bFull && aGuess.GetHangingPortion() )
/*M*/     {
/*M*/       Width( aGuess.BreakWidth() );
/*M*/         SetLen( aGuess.BreakPos() - rInf.GetIdx() );
/*M*/         Insert( aGuess.GetHangingPortion() );
/*M*/         aGuess.GetHangingPortion()->SetAscent( GetAscent() );
/*M*/         aGuess.ClearHangingPortion();
/*M*/     }
/*M*/   // breakPos >= index
/*M*/   else if ( aGuess.BreakPos() >= rInf.GetIdx() && aGuess.BreakPos() != STRING_LEN )
/*M*/   {
/*M*/       // case B1
/*N*/       if( aGuess.HyphWord().is() && aGuess.BreakPos() > rInf.GetLineStart()
/*N*/             && ( aGuess.BreakPos() > rInf.GetIdx() ||
/*M*/             ( rInf.GetLast() && ! rInf.GetLast()->IsFlyPortion() ) ) )
/*M*/       {
/*M*/           CreateHyphen( rInf, aGuess );
/*M*/           if ( rInf.GetFly() )
/*M*/               rInf.GetRoot()->SetMidHyph( sal_True );
/*M*/           else
/*M*/               rInf.GetRoot()->SetEndHyph( sal_True );
/*M*/       }
/*M*/       // case C1
/*M*/         else if ( IsFtnPortion() && rInf.IsFakeLineStart() )
/*M*/           BreakUnderflow( rInf );
/*M*/       // case B2
/*M*/       else if( rInf.GetIdx() > rInf.GetLineStart() ||
/*M*/                aGuess.BreakPos() > rInf.GetIdx() ||
/*M*/                  // this is weird: during formatting the follow of a field
/*M*/                  // the values rInf.GetIdx and rInf.GetLineStart are replaced
/*M*/                  // IsFakeLineStart indicates GetIdx > GetLineStart
/*M*/                  rInf.IsFakeLineStart() ||
/*M*/                  rInf.GetFly() ||
/*M*/                  rInf.IsFirstMulti() ||
/*M*/                  ( rInf.GetLast() &&
/*M*/                     ( rInf.GetLast()->IsFlyPortion() ||
/*M*/                         ( rInf.GetLast()->InFldGrp() &&
/*M*/                           ! rInf.GetLast()->InNumberGrp() &&
/*M*/                           ! rInf.GetLast()->IsErgoSumPortion() &&
/*M*/                           lcl_HasContent(*((SwFldPortion*)rInf.GetLast()),rInf ) ) ) ) )
/*M*/       {
/*M*/             if ( rInf.X() + aGuess.BreakWidth() <= rInf.Width() )
/*M*/                 Width( aGuess.BreakWidth() );
/*M*/             else
/*M*/                 // this actually should not happen
/*M*/                 Width( KSHORT(rInf.Width() - rInf.X()) );
/*M*/
/*M*/             SetLen( aGuess.BreakPos() - rInf.GetIdx() );
/*M*/
/*M*/             ASSERT( aGuess.BreakStart() >= aGuess.FieldDiff(),
/*M*/                     "Trouble with expanded field portions during line break" );
/*M*/             const xub_StrLen nRealStart = aGuess.BreakStart() - aGuess.FieldDiff();
/*N*/             if( aGuess.BreakPos() < nRealStart && !InExpGrp() )
/*M*/           {
/*M*/               SwHolePortion *pNew = new SwHolePortion( *this );
/*M*/                 pNew->SetLen( nRealStart - aGuess.BreakPos() );
/*M*/               Insert( pNew );
/*M*/           }
/*M*/       }
/*M*/       else    // case C2, last exit
/*M*/           BreakCut( rInf, aGuess );
/*M*/   }
/*M*/   // breakPos < index or no breakpos at all
/*M*/   else
/*M*/   {
/*M*/         sal_Bool bFirstPor = rInf.GetLineStart() == rInf.GetIdx();
/*M*/       if( aGuess.BreakPos() != STRING_LEN &&
/*M*/           aGuess.BreakPos() != rInf.GetLineStart() &&
/*M*/             ( !bFirstPor || rInf.GetFly() || rInf.GetLast()->IsFlyPortion() ||
/*M*/               rInf.IsFirstMulti() ) &&
/*M*/           ( !rInf.GetLast()->IsBlankPortion() ||  ((SwBlankPortion*)
/*M*/             rInf.GetLast())->MayUnderFlow( rInf, rInf.GetIdx()-1, sal_True )))
/*M*/       {       // case C1 (former BreakUnderflow())
/*M*/           BreakUnderflow( rInf );
/*M*/       }
/*M*/         else
/*M*/              // case C2, last exit
/*M*/           BreakCut( rInf, aGuess );
/*M*/   }
/*M*/
/*M*/   return bFull;
/*M*/ }

/*************************************************************************
 *                 virtual SwTxtPortion::Format()
 *************************************************************************/



/*N*/ sal_Bool SwTxtPortion::Format( SwTxtFormatInfo &rInf )
/*N*/ {
/*N*/ #if OSL_DEBUG_LEVEL > 1
/*N*/   const XubString aDbgTxt( rInf.GetTxt().Copy( rInf.GetIdx(), rInf.GetLen() ) );
/*N*/ #endif
/*N*/
/*N*/   if( rInf.X() > rInf.Width() || (!GetLen() && !InExpGrp()) )
/*N*/   {
/*N*/       Height( 0 );
/*N*/       Width( 0 );
/*N*/       SetLen( 0 );
/*N*/       SetAscent( 0 );
/*N*/       SetPortion( NULL );  // ????
/*N*/       return sal_True;
/*N*/   }
/*N*/
/*N*/   ASSERT( rInf.RealWidth() || (rInf.X() == rInf.Width()),
/*N*/       "SwTxtPortion::Format: missing real width" );
/*N*/   ASSERT( Height(), "SwTxtPortion::Format: missing height" );
/*N*/
/*N*/   return _Format( rInf );
/*N*/ }

/*************************************************************************
 *                 virtual SwTxtPortion::FormatEOL()
 *************************************************************************/

// Format end of line
// 5083: Es kann schon manchmal unguenstige Faelle geben...
// "vom {Nikolaus}", Nikolaus bricht um "vom " wird im Blocksatz
// zu "vom" und " ", wobei der Glue expandiert wird, statt in die
// MarginPortion aufzugehen.
// rInf.nIdx steht auf dem naechsten Wort, nIdx-1 ist der letzte
// Buchstabe der Portion.



/*N*/ void SwTxtPortion::FormatEOL( SwTxtFormatInfo &rInf )
/*N*/ {
/*N*/ #ifndef USED
/*N*/   if( ( !GetPortion() || ( GetPortion()->IsKernPortion() &&
/*N*/       !GetPortion()->GetPortion() ) ) && GetLen() &&
/*N*/       rInf.GetIdx() < rInf.GetTxt().Len() &&
/*N*/       1 < rInf.GetIdx() && ' ' == rInf.GetChar( rInf.GetIdx() - 1 )
/*N*/ #else
/*N*/   if( !GetPortion() && 1 < GetLen() &&
/*N*/       rInf.GetIdx() < rInf.GetTxt().Len() &&
/*N*/       1 < rInf.GetIdx() && ' ' == rInf.GetTxt()[xub_StrLen(rInf.GetIdx()-1)]
/*N*/       && !rInf.GetFly()
/*N*/ #endif
/*N*/
/*N*/       && !rInf.GetLast()->IsHolePortion() )
/*N*/   {
/*N*/         // calculate number of blanks
/*?*/         xub_StrLen nX = rInf.GetIdx() - 1;
/*?*/         USHORT nHoleLen = 1;
/*?*/         while( nX && nHoleLen < GetLen() && CH_BLANK == rInf.GetChar( --nX ) )
/*?*/             nHoleLen++;
/*?*/
/*?*/       // Erst uns einstellen und dann Inserten, weil wir ja auch ein
/*?*/       // SwLineLayout sein koennten.
/*?*/         KSHORT nBlankSize;
/*?*/         if( nHoleLen == GetLen() )
/*?*/           nBlankSize = Width();
/*?*/       else
/*?*/             nBlankSize = nHoleLen * rInf.GetTxtSize( ' ' ).Width();
/*?*/         Width( Width() - nBlankSize );
/*?*/       rInf.X( rInf.X() - nBlankSize );
/*?*/         SetLen( GetLen() - nHoleLen );
/*?*/       SwLinePortion *pHole = new SwHolePortion( *this );
/*?*/       ( (SwHolePortion *)pHole )->SetBlankWidth( nBlankSize );
/*?*/         ( (SwHolePortion *)pHole )->SetLen( nHoleLen );
/*?*/       Insert( pHole );
/*N*/   }
/*N*/ }

/*************************************************************************
 *               virtual SwTxtPortion::GetCrsrOfst()
 *************************************************************************/



//STRIP001 xub_StrLen SwTxtPortion::GetCrsrOfst( const KSHORT nOfst ) const
//STRIP001 {
//STRIP001  ASSERT( !this, "SwTxtPortion::GetCrsrOfst: don't use this method!" );
//STRIP001  return SwLinePortion::GetCrsrOfst( nOfst );
//STRIP001 }

/*************************************************************************
 *               SwTxtPortion::GetCrsrOfst()
 *************************************************************************/

//STRIP001 xub_StrLen SwTxtPortion::GetCrsrOfst( const KSHORT nOfst,
//STRIP001                                SwTxtSizeInfo &rSizeInf ) const
//STRIP001 {
//STRIP001     rSizeInf.SetLen( rSizeInf.GetTxtBreak( nOfst, nLineLength )
//STRIP001                    - rSizeInf.GetIdx() );
//STRIP001     return rSizeInf.GetLen();
//STRIP001 }

/*************************************************************************
 *                virtual SwTxtPortion::GetTxtSize()
 *************************************************************************/
// Das GetTxtSize() geht davon aus, dass die eigene Laenge korrekt ist

/*N*/ SwPosSize SwTxtPortion::GetTxtSize( const SwTxtSizeInfo &rInf ) const
/*N*/ {
/*N*/     return rInf.GetTxtSize();
/*N*/ }

/*************************************************************************
 *               virtual SwTxtPortion::Paint()
 *************************************************************************/



//STRIP001 void SwTxtPortion::Paint( const SwTxtPaintInfo &rInf ) const
//STRIP001 {
//STRIP001  if( GetLen() )
//STRIP001  {
//STRIP001      rInf.DrawBackBrush( *this );
//STRIP001
//STRIP001         // do we have to repaint a post it portion?
//STRIP001         if( rInf.OnWin() && pPortion && !pPortion->Width() )
//STRIP001             pPortion->PrePaint( rInf, this );
//STRIP001
//STRIP001      const SwWrongList *pWrongList = rInf.GetpWrongList();
//STRIP001      if ( pWrongList )
//STRIP001          rInf.DrawWrongText( *this, rInf.GetLen(), sal_False );
//STRIP001      else
//STRIP001          rInf.DrawText( *this, rInf.GetLen(), sal_False );
//STRIP001  }
//STRIP001 }

/*************************************************************************
 *              virtual SwTxtPortion::GetExpTxt()
 *************************************************************************/



/*N*/ sal_Bool SwTxtPortion::GetExpTxt( const SwTxtSizeInfo &rInf, XubString &rTxt ) const
/*N*/ {
/*N*/   return sal_False;
/*N*/ }

/*************************************************************************
 *        xub_StrLen SwTxtPortion::GetSpaceCnt()
 *              long SwTxtPortion::CalcSpacing()
 * sind fuer den Blocksatz zustaendig und ermitteln die Anzahl der Blanks
 * und den daraus resultierenden zusaetzlichen Zwischenraum
 *************************************************************************/

/*N*/ xub_StrLen SwTxtPortion::GetSpaceCnt( const SwTxtSizeInfo &rInf,
/*N*/                                     xub_StrLen& rCharCnt ) const
/*N*/ {
/*N*/   xub_StrLen nCnt = 0;
/*N*/   xub_StrLen nPos = 0;
/*N*/   if ( InExpGrp() )
/*N*/   {
/*?*/         if( !IsBlankPortion() && !InNumberGrp() && !IsCombinedPortion() )
/*?*/       {
/*?*/           // Bei OnWin() wird anstatt eines Leerstrings gern mal ein Blank
/*?*/           // zurueckgeliefert, das koennen wir hier aber gar nicht gebrauchen
/*?*/           sal_Bool bOldOnWin = rInf.OnWin();
/*?*/           ((SwTxtSizeInfo &)rInf).SetOnWin( sal_False );
/*?*/
/*?*/           XubString aStr( aEmptyStr );
/*?*/           GetExpTxt( rInf, aStr );
/*?*/           ((SwTxtSizeInfo &)rInf).SetOnWin( bOldOnWin );
/*?*/
/*?*/             nCnt += lcl_AddSpace( rInf, &aStr, *this );
/*?*/             nPos = aStr.Len();
/*?*/       }
/*N*/   }
/*N*/   else if( !IsDropPortion() )
/*N*/   {
/*N*/         nCnt += lcl_AddSpace( rInf, 0, *this );
/*N*/       nPos = GetLen();
/*N*/   }
/*N*/   rCharCnt += nPos;
/*N*/   return nCnt;
/*N*/ }

//STRIP001 long SwTxtPortion::CalcSpacing( short nSpaceAdd, const SwTxtSizeInfo &rInf ) const
//STRIP001 {
//STRIP001      xub_StrLen nCnt = 0;
//STRIP001  if ( InExpGrp() )
//STRIP001  {
//STRIP001      if( !IsBlankPortion() && !InNumberGrp() )
//STRIP001      {
//STRIP001          // Bei OnWin() wird anstatt eines Leerstrings gern mal ein Blank
//STRIP001          // zurueckgeliefert, das koennen wir hier aber gar nicht gebrauchen
//STRIP001          sal_Bool bOldOnWin = rInf.OnWin();
//STRIP001          ((SwTxtSizeInfo &)rInf).SetOnWin( sal_False );
//STRIP001
//STRIP001          XubString aStr( aEmptyStr );
//STRIP001          GetExpTxt( rInf, aStr );
//STRIP001          ((SwTxtSizeInfo &)rInf).SetOnWin( bOldOnWin );
//STRIP001          if( nSpaceAdd > 0 )
//STRIP001                 nCnt += lcl_AddSpace( rInf, &aStr, *this );
//STRIP001          else
//STRIP001          {
//STRIP001              nSpaceAdd = -nSpaceAdd;
//STRIP001              nCnt = aStr.Len();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else if( !IsDropPortion() )
//STRIP001  {
//STRIP001      if( nSpaceAdd > 0 )
//STRIP001             nCnt += lcl_AddSpace( rInf, 0, *this );
//STRIP001      else
//STRIP001      {
//STRIP001          nSpaceAdd = -nSpaceAdd;
//STRIP001          nCnt = GetLen();
//STRIP001             SwLinePortion* pPor = GetPortion();
//STRIP001
//STRIP001             // we do not want an extra space in front of margin portions
//STRIP001             if ( ! nCnt )
//STRIP001                 return 0;
//STRIP001
//STRIP001             while ( pPor && !pPor->Width() && ! pPor->IsHolePortion() )
//STRIP001                 pPor = pPor->GetPortion();
//STRIP001
//STRIP001             if ( !pPor || pPor->InFixMargGrp() || pPor->IsHolePortion() )
//STRIP001                 return ( nCnt - 1 ) * nSpaceAdd;
//STRIP001      }
//STRIP001  }
//STRIP001  return nCnt * nSpaceAdd;
//STRIP001 }

/*************************************************************************
 *              virtual SwTxtPortion::HandlePortion()
 *************************************************************************/

//STRIP001 void SwTxtPortion::HandlePortion( SwPortionHandler& rPH ) const
//STRIP001 {
//STRIP001     rPH.Text( GetLen(), GetWhichPor() );
//STRIP001 }

/*************************************************************************
 *                      class SwHolePortion
 *************************************************************************/



/*N*/ SwHolePortion::SwHolePortion( const SwTxtPortion &rPor )
/*N*/   : nBlankWidth( 0 )
/*N*/ {
/*N*/   SetLen( 1 );
/*N*/   Height( rPor.Height() );
/*N*/   SetAscent( rPor.GetAscent() );
/*N*/   SetWhichPor( POR_HOLE );
/*N*/ }

/*N*/ SwLinePortion *SwHolePortion::Compress() { return this; }

/*************************************************************************
 *               virtual SwHolePortion::Paint()
 *************************************************************************/



//STRIP001 void SwHolePortion::Paint( const SwTxtPaintInfo &rInf ) const
//STRIP001 {
//STRIP001 }

/*************************************************************************
 *                 virtual SwHolePortion::Format()
 *************************************************************************/



//STRIP001 sal_Bool SwHolePortion::Format( SwTxtFormatInfo &rInf )
//STRIP001 {
//STRIP001  return rInf.IsFull() || rInf.X() >= rInf.Width();
//STRIP001 }

/*************************************************************************
 *              virtual SwHolePortion::HandlePortion()
 *************************************************************************/

//STRIP001 void SwHolePortion::HandlePortion( SwPortionHandler& rPH ) const
//STRIP001 {
//STRIP001     rPH.Text( GetLen(), GetWhichPor() );
//STRIP001 }

