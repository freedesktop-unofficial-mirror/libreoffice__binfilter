/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */



#ifdef _MSC_VER
#pragma hdrstop
#endif


#include <vcl/metric.hxx>
#include <vcl/window.hxx>
#include <vcl/svapp.hxx>

#include <paratr.hxx>
#include <charfmt.hxx>
#include <viewsh.hxx>   // ViewShell
#include <pordrop.hxx>
#include <itrform2.hxx>
#include <breakit.hxx>
#include <com/sun/star/i18n/ScriptType.hdl>
#include <com/sun/star/i18n/WordType.hpp>
#include <bf_svx/langitem.hxx>
#include <charatr.hxx>
namespace binfilter {

using namespace ::com::sun::star::i18n;
using namespace ::com::sun::star;

/*************************************************************************
 *                SwDropPortionPart DTor
 *************************************************************************/

/*N*/ SwDropPortionPart::~SwDropPortionPart()
/*N*/ {
/*N*/     if ( pFollow )
/*N*/         delete pFollow;
/*N*/     delete pFnt;
/*N*/ }

/*************************************************************************
 *                SwDropPortion CTor, DTor
 *************************************************************************/

/*N*/ SwDropPortion::SwDropPortion( const MSHORT nLineCnt,
/*N*/                               const KSHORT nDropHeight1,
/*N*/                               const KSHORT nDropDescent1,
/*N*/                               const KSHORT nDistance1 )
/*N*/   : pPart( 0 )
/*N*/   , nLines( nLineCnt )
/*N*/   , nDropHeight(nDropHeight1)
/*N*/   , nDropDescent(nDropDescent1)
/*N*/   , nDistance(nDistance1)
/*N*/   , nFix(0)
/*N*/   , nX(0)
/*N*/ {
/*N*/     SetWhichPor( POR_DROP );
/*N*/ }

/*N*/ SwDropPortion::~SwDropPortion()
/*N*/ {
/*N*/     delete pPart;
/*N*/ }

/*N*/ sal_Bool SwTxtSizeInfo::_HasHint( const SwTxtNode* pTxtNode, xub_StrLen nPos )
/*N*/ {
/*N*/   const SwpHints *pHints = pTxtNode->GetpSwpHints();
/*N*/   if( !pHints )
/*N*/       return sal_False;
/*N*/   for( MSHORT i = 0; i < pHints->Count(); ++i )
/*N*/   {
/*N*/       const SwTxtAttr *pPos = (*pHints)[i];
/*N*/       xub_StrLen nStart = *pPos->GetStart();
/*N*/       if( nPos < nStart )
/*N*/           return sal_False;
/*N*/       if( nPos == nStart && !pPos->GetEnd() )
/*N*/           return sal_True;
/*N*/   }
/*N*/   return sal_False;
/*N*/ }

/*************************************************************************
 *                    SwTxtNode::GetDropLen()
 *
 * nWishLen = 0 indicates that we want a whole word
 *************************************************************************/

/*N*/ MSHORT SwTxtNode::GetDropLen( MSHORT nWishLen ) const
/*N*/ {
/*N*/     xub_StrLen nEnd = GetTxt().Len();
/*N*/     if( nWishLen && nWishLen < nEnd )
/*N*/         nEnd = nWishLen;
/*N*/
/*N*/     if ( ! nWishLen && pBreakIt->xBreak.is() )
/*N*/     {
/*N*/         // find first word
/*?*/         const SwAttrSet& rAttrSet = GetSwAttrSet();
/*?*/         const USHORT nTxtScript = pBreakIt->GetRealScriptOfText( GetTxt(), 0 );
/*?*/
/*?*/         LanguageType eLanguage;
/*?*/
/*?*/         switch ( nTxtScript )
/*?*/         {
/*?*/         case i18n::ScriptType::ASIAN :
/*?*/             eLanguage = rAttrSet.GetCJKLanguage().GetLanguage();
/*?*/             break;
/*?*/         case i18n::ScriptType::COMPLEX :
/*?*/             eLanguage = rAttrSet.GetCTLLanguage().GetLanguage();
/*?*/             break;
/*?*/         default :
/*?*/             eLanguage = rAttrSet.GetLanguage().GetLanguage();
/*?*/             break;
/*?*/         }
/*?*/
/*?*/         Boundary aBound =
/*?*/             pBreakIt->xBreak->getWordBoundary( GetTxt(), 0,
/*?*/             pBreakIt->GetLocale( eLanguage ), WordType::DICTIONARY_WORD, sal_True );
/*?*/
/*?*/         nEnd = (xub_StrLen)aBound.endPos;
/*N*/     }
/*N*/
/*N*/     xub_StrLen i = 0;
/*N*/     for( ; i < nEnd; ++i )
/*N*/     {
/*N*/         sal_Unicode cChar = GetTxt().GetChar( i );
/*N*/         if( CH_TAB == cChar || CH_BREAK == cChar ||
/*N*/             (( CH_TXTATR_BREAKWORD == cChar || CH_TXTATR_INWORD == cChar )
/*N*/                 && SwTxtSizeInfo::_HasHint( this, i ) ) )
/*N*/             break;
/*N*/     }
/*N*/     return i;
/*N*/ }

/*************************************************************************
 *                SwTxtFormatter::CalcDropHeight()
 *************************************************************************/

/*N*/ void SwTxtFormatter::CalcDropHeight( const MSHORT nLines )
/*N*/  {
/*N*/   const SwLinePortion *const pOldCurr = GetCurr();
/*N*/   KSHORT nDropHght = 0;
/*N*/   KSHORT nAscent = 0;
/*N*/   KSHORT nHeight = 0;
/*N*/   KSHORT nDropLns = 0;
/*N*/   sal_Bool bRegisterOld = IsRegisterOn();
/*N*/   bRegisterOn = sal_False;
/*N*/
/*N*/   Top();
/*N*/
/*N*/   while( GetCurr()->IsDummy() )
/*N*/   {
/*N*/       if ( !Next() )
/*N*/           break;
/*N*/   }
/*N*/
/*N*/   // Wenn wir nur eine Zeile haben returnen wir 0
/*N*/   if( GetNext() || GetDropLines() == 1 )
/*N*/   {
/*N*/       for( ; nDropLns < nLines; nDropLns++ )
/*N*/       {
/*N*/           if ( GetCurr()->IsDummy() )
/*N*/               break;
/*N*/           else
/*N*/           {
/*N*/               CalcAscentAndHeight( nAscent, nHeight );
/*N*/               nDropHght += nHeight;
/*N*/               bRegisterOn = bRegisterOld;
/*N*/           }
/*N*/           if ( !Next() )
/*N*/           {
/*N*/               nDropLns++; // Fix: 11356
/*N*/               break;
/*N*/           }
/*N*/       }
/*N*/
/*N*/       // In der letzten Zeile plumpsen wir auf den Zeilenascent!
/*N*/       nDropHght -= nHeight;
/*N*/       nDropHght += nAscent;
/*N*/       Top();
/*N*/   }
/*N*/   bRegisterOn = bRegisterOld;
/*N*/   SetDropDescent( nHeight - nAscent );
/*N*/   SetDropHeight( nDropHght );
/*N*/   SetDropLines( nDropLns );
/*N*/   // Alte Stelle wiederfinden!
/*N*/   while( pOldCurr != GetCurr() )
/*N*/   {
/*N*/       if( !Next() )
/*N*/       {
/*N*/           OSL_ENSURE( !this, "SwTxtFormatter::_CalcDropHeight: left Toulouse" );
/*N*/           break;
/*N*/       }
/*N*/   }
/*N*/  }

/*************************************************************************
 *                SwTxtFormatter::GuessDropHeight()
 *
 *  Wir schaetzen mal, dass die Fonthoehe sich nicht aendert und dass
 *  erst mindestens soviele Zeilen gibt, wie die DropCap-Einstellung angibt.
 *
 *************************************************************************/



/*N*/ void SwTxtFormatter::GuessDropHeight( const MSHORT nLines )
/*N*/ {
/*N*/   OSL_ENSURE( nLines, "GuessDropHeight: Give me more Lines!" );
/*N*/   KSHORT nAscent = 0;
/*N*/   KSHORT nHeight = 0;
/*N*/   SetDropLines( nLines );
/*N*/   if ( GetDropLines() > 1 )
/*N*/   {
/*N*/       CalcRealHeight();
/*N*/       CalcAscentAndHeight( nAscent, nHeight );
/*N*/   }
/*N*/   SetDropDescent( nHeight - nAscent );
/*N*/   SetDropHeight( nHeight * nLines - GetDropDescent() );
/*N*/ }

/*************************************************************************
 *                SwTxtFormatter::NewDropPortion
 *************************************************************************/

/*N*/ SwDropPortion *SwTxtFormatter::NewDropPortion( SwTxtFormatInfo &rInf )
/*N*/ {
/*N*/   if( !pDropFmt )
/*N*/       return 0;
/*N*/
/*N*/   xub_StrLen nPorLen = pDropFmt->GetWholeWord() ? 0 : pDropFmt->GetChars();
/*N*/     nPorLen = pFrm->GetTxtNode()->GetDropLen( nPorLen );
/*N*/   if( !nPorLen )
/*N*/   {
/*?*/       ((SwTxtFormatter*)this)->ClearDropFmt();
/*?*/       return 0;
/*N*/   }
/*N*/
/*N*/   SwDropPortion *pDropPor = 0;
/*N*/
/*N*/   // erste oder zweite Runde?
/*N*/   if ( !( GetDropHeight() || IsOnceMore() ) )
/*N*/   {
/*N*/       if ( GetNext() )
/*?*/             CalcDropHeight( pDropFmt->GetLines() );
/*N*/       else
/*N*/             GuessDropHeight( pDropFmt->GetLines() );
/*N*/   }
/*N*/
/*N*/     // the DropPortion
/*N*/     if( GetDropHeight() )
/*?*/         pDropPor = new SwDropPortion( GetDropLines(), GetDropHeight(),
/*N*/                                       GetDropDescent(), pDropFmt->GetDistance() );
/*N*/   else
/*N*/         pDropPor = new SwDropPortion( 0,0,0,pDropFmt->GetDistance() );
/*N*/
/*N*/     pDropPor->SetLen( nPorLen );
/*N*/
/*N*/     // If it was not possible to create a proper drop cap portion
/*N*/     // due to avoiding endless loops. We return a drop cap portion
/*N*/     // with an empty SwDropCapPart. For these portions the current
/*N*/     // font is used.
/*N*/     if ( GetDropLines() < 2 )
/*N*/     {
/*?*/         ((SwTxtFormatter*)this)->SetPaintDrop( sal_True );
/*?*/         return pDropPor;
/*N*/     }
/*N*/
/*N*/     // build DropPortionParts:
/*N*/     OSL_ENSURE( ! rInf.GetIdx(), "Drop Portion not at 0 position!" );
/*N*/     xub_StrLen nNextChg = 0;
/*N*/     const SwCharFmt* pFmt = pDropFmt->GetCharFmt();
/*N*/     SwDropPortionPart* pCurrPart = 0;
/*N*/
/*N*/     while ( nNextChg  < nPorLen )
/*N*/     {
/*N*/         // check for attribute changes and if the portion has to split:
/*N*/         Seek( nNextChg );
/*N*/
/*N*/         // the font is deleted in the destructor of the drop portion part
/*N*/         SwFont* pTmpFnt = new SwFont( *rInf.GetFont() );
/*N*/         if ( pFmt )
/*N*/         {
/*N*/             const SwAttrSet& rSet = pFmt->GetAttrSet();
/*N*/             pTmpFnt->SetDiffFnt( &rSet, rInf.GetDoc() );
/*N*/         }
/*N*/
/*N*/         // we do not allow a vertical font for the drop portion
/*N*/ #ifdef VERTICAL_LAYOUT
/*N*/         pTmpFnt->SetVertical( 0, rInf.GetTxtFrm()->IsVertical() );
/*N*/ #else
/*N*/         pTmpFnt->SetVertical( 0 );
/*N*/ #endif
/*N*/
/*N*/         // find next attribute change / script change
/*N*/         const xub_StrLen nIdx2 = nNextChg;
/*N*/         xub_StrLen nNextAttr = Min( GetNextAttr(), rInf.GetTxt().Len() );
/*N*/         nNextChg = pScriptInfo->NextScriptChg( nIdx2 );
/*N*/         if( nNextChg > nNextAttr )
/*N*/             nNextChg = nNextAttr;
/*N*/         if ( nNextChg > nPorLen )
/*N*/             nNextChg = nPorLen;
/*N*/
/*N*/         SwDropPortionPart* pPart =
/*N*/                 new SwDropPortionPart( *pTmpFnt, nNextChg - nIdx2 );
/*N*/
/*N*/         if ( ! pCurrPart )
/*N*/             pDropPor->SetPart( pPart );
/*N*/         else
/*?*/             pCurrPart->SetFollow( pPart );
/*N*/
/*N*/         pCurrPart = pPart;
/*N*/     }
/*N*/
/*N*/   ((SwTxtFormatter*)this)->SetPaintDrop( sal_True );
/*N*/   return pDropPor;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
