 /*************************************************************************
 *
 *  $RCSfile: sw_itradj.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:51:18 $
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

#include "frame.hxx"       // CalcFlyAdjust()
#include "paratr.hxx"
#if OSL_DEBUG_LEVEL > 1
# include "ndtxt.hxx"        // pSwpHints, Ausgabeoperator
#endif

#include "txtcfg.hxx"
#include "itrtxt.hxx"
#include "porglue.hxx"
#include "porlay.hxx"
#include "porfly.hxx"       // CalcFlyAdjust()
#include "pordrop.hxx"       // CalcFlyAdjust()
#include "pormulti.hxx"

#ifndef _PORTAB_HXX
#include <portab.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
namespace binfilter {

#define MIN_TAB_WIDTH 60

/*************************************************************************
 *                    SwTxtAdjuster::FormatBlock()
 *************************************************************************/

/*N*/ void SwTxtAdjuster::FormatBlock( )
/*N*/ {
/*N*/   // In der letzten Zeile gibt's keinen Blocksatz.
/*N*/   // Und bei Tabulatoren aus Tradition auch nicht.
/*N*/   // 7701: wenn Flys im Spiel sind, geht's weiter
/*N*/
/*N*/   const SwLinePortion *pFly = 0;
/*N*/
/*N*/   sal_Bool bSkip = !IsLastBlock() &&
/*N*/       nStart + pCurr->GetLen() >= GetInfo().GetTxt().Len();
/*N*/
/*N*/   // ????: mehrzeilige Felder sind fies: wir muessen kontrollieren,
/*N*/   // ob es noch andere Textportions im Absatz gibt.
/*N*/   if( bSkip )
/*N*/   {
/*N*/       const SwLineLayout *pLay = pCurr->GetNext();
/*N*/       while( pLay && !pLay->GetLen() )
/*N*/       {
/*?*/           const SwLinePortion *pPor = pCurr->GetFirstPortion();
/*?*/           while( pPor && bSkip )
/*?*/           {
/*?*/               if( pPor->InTxtGrp() )
/*?*/                   bSkip = sal_False;
/*?*/               pPor = pPor->GetPortion();
/*?*/           }
/*?*/           pLay = bSkip ? pLay->GetNext() : 0;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if( bSkip )
/*N*/   {
/*N*/       if( !GetInfo().GetParaPortion()->HasFly() )
/*N*/       {
/*?*/           if( IsLastCenter() )
/*?*/               CalcFlyAdjust( pCurr );
/*?*/           pCurr->FinishSpaceAdd();
/*?*/           return;
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           const SwLinePortion *pTmpFly = NULL;
/*N*/
/*N*/           // 7701: beim letzten Fly soll Schluss sein
/*N*/           const SwLinePortion *pPos = pCurr->GetFirstPortion();
/*N*/           while( pPos )
/*N*/           {
/*N*/               // Ich suche jetzt den letzten Fly, hinter dem noch Text ist:
/*N*/               if( pPos->IsFlyPortion() )
/*N*/                   pTmpFly = pPos; // Ein Fly wurde gefunden
/*N*/               else if ( pTmpFly && pPos->InTxtGrp() )
/*N*/               {
/*N*/                   pFly = pTmpFly; // Ein Fly mit nachfolgendem Text!
/*N*/                   pTmpFly = NULL;
/*N*/               }
/*N*/               pPos = pPos->GetPortion();
/*N*/           }
/*N*/           // 8494: Wenn keiner gefunden wurde, ist sofort Schluss!
/*N*/           if( !pFly )
/*N*/           {
/*N*/               if( IsLastCenter() )
/*?*/                   CalcFlyAdjust( pCurr );
/*N*/               pCurr->FinishSpaceAdd();
/*N*/               return;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   const nOldIdx = GetInfo().GetIdx();
/*N*/   GetInfo().SetIdx( nStart );
/*N*/   CalcNewBlock( pCurr, pFly );
/*N*/   GetInfo().SetIdx( nOldIdx );
/*N*/   GetInfo().GetParaPortion()->GetRepaint()->SetOfst(0);
/*N*/ }

/*************************************************************************
 *                    SwTxtAdjuster::CalcNewBlock()
 *
 * CalcNewBlock() darf erst nach CalcLine() gerufen werden !
 * Aufgespannt wird immer zwischen zwei RandPortions oder FixPortions
 * (Tabs und Flys). Dabei werden die Glues gezaehlt und ExpandBlock gerufen.
 *************************************************************************/

/*N*/ void SwTxtAdjuster::CalcNewBlock( SwLineLayout *pCurr,
/*N*/                                 const SwLinePortion *pStopAt, SwTwips nReal )
/*N*/ {
/*N*/   ASSERT( GetInfo().IsMulti() || SVX_ADJUST_BLOCK == GetAdjust(),
/*N*/           "CalcNewBlock: Why?" );
/*N*/   ASSERT( pCurr->Height(), "SwTxtAdjuster::CalcBlockAdjust: missing CalcLine()" );
/*N*/
/*N*/   pCurr->InitSpaceAdd();
/*N*/   MSHORT nNull = 0;
/*N*/   xub_StrLen nGluePortion = 0;
/*N*/   xub_StrLen nCharCnt = 0;
/*N*/   MSHORT nSpaceIdx = 0;
/*N*/
/*N*/   // Nicht vergessen:
/*N*/   // CalcRightMargin() setzt pCurr->Width() auf die Zeilenbreite !
/*N*/   CalcRightMargin( pCurr, nReal );
/*N*/
/*N*/   SwLinePortion *pPos = pCurr->GetPortion();
/*N*/
/*N*/   while( pPos )
/*N*/   {
/*N*/       if ( pPos->IsBreakPortion() && !IsLastBlock() )
/*N*/       {
/*?*/           pCurr->FinishSpaceAdd();
/*?*/           break;
/*N*/       }
/*N*/       if ( pPos->InTxtGrp() )
/*N*/           nGluePortion += ((SwTxtPortion*)pPos)->GetSpaceCnt( GetInfo(), nCharCnt );
/*N*/       else if( pPos->IsMultiPortion() )
                {DBG_ASSERT(0, "STRIP");} //STRIP001 /*N*/      {
//STRIP001 /*?*/            SwMultiPortion* pMulti = (SwMultiPortion*)pPos;
//STRIP001 /*?*/            // a multiportion with a tabulator inside breaks the text adjustment
//STRIP001 /*?*/            // a ruby portion will not be stretched by text adjustment
//STRIP001 /*?*/            // a double line portion takes additional space for each blank
//STRIP001 /*?*/            // in the wider line
//STRIP001 /*?*/            if( pMulti->HasTabulator() )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                if ( nSpaceIdx == pCurr->GetSpaceAdd().Count() )
//STRIP001 /*?*/                    pCurr->GetSpaceAdd().Insert( nNull, nSpaceIdx );
//STRIP001 /*?*/                nSpaceIdx++;
//STRIP001 /*?*/                nGluePortion = 0;
//STRIP001 /*?*/                nCharCnt = 0;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            else if( pMulti->IsDouble() )
//STRIP001 /*?*/                nGluePortion += ((SwDoubleLinePortion*)pMulti)->GetSpaceCnt();
//STRIP001 /*?*/ #ifdef BIDI
//STRIP001 /*?*/             else if ( pMulti->IsBidi() )
//STRIP001 /*?*/                 nGluePortion += ((SwBidiPortion*)pMulti)->GetSpaceCnt();
//STRIP001 /*?*/ #endif
//STRIP001 /*N*/        }
/*N*/
/*N*/       if( pPos->InGlueGrp() )
/*N*/       {
/*N*/           if( pPos->InFixMargGrp() )
/*N*/           {
/*N*/               if ( nSpaceIdx == pCurr->GetSpaceAdd().Count() )
/*N*/                   pCurr->GetSpaceAdd().Insert( nNull, nSpaceIdx );
/*N*/               if( nGluePortion )
/*N*/               {
/*N*/                   ( pCurr->GetSpaceAdd() )[nSpaceIdx] =
/*N*/                        ( (SwGluePortion*)pPos )->GetPrtGlue() / nGluePortion;
/*N*/                   pPos->Width( ( (SwGluePortion*)pPos )->GetFixWidth() );
/*N*/               }
/*N*/               else if ( IsOneBlock() && nCharCnt > 1 )
/*N*/               {
/*?*/                   ( pCurr->GetSpaceAdd() )[nSpaceIdx] =
/*?*/                       - ( (SwGluePortion*)pPos )->GetPrtGlue() / (nCharCnt-1);
/*?*/                   pPos->Width( ( (SwGluePortion*)pPos )->GetFixWidth() );
/*N*/               }
/*N*/               nSpaceIdx++;
/*N*/               nGluePortion = 0;
/*N*/               nCharCnt = 0;
/*N*/           }
/*N*/           else
/*N*/               ++nGluePortion;
/*N*/       }
/*N*/       GetInfo().SetIdx( GetInfo().GetIdx() + pPos->GetLen() );
/*N*/       if ( pPos == pStopAt )
/*N*/       {
/*?*/           if ( nSpaceIdx == pCurr->GetSpaceAdd().Count() )
/*?*/               pCurr->GetSpaceAdd().Insert( nNull, nSpaceIdx );
/*?*/           else
/*?*/               pCurr->GetSpaceAdd()[nSpaceIdx] = 0;
/*?*/           break;
/*N*/       }
/*N*/       pPos = pPos->GetPortion();
/*N*/   }
/*N*/ }

/*************************************************************************
 *                    SwTxtAdjuster::CalcKanaAdj()
 *************************************************************************/

//STRIP001 USHORT SwTxtAdjuster::CalcKanaAdj( SwLineLayout* pCurr )
//STRIP001 {
//STRIP001     ASSERT( pCurr->Height(), "SwTxtAdjuster::CalcBlockAdjust: missing CalcLine()" );
//STRIP001     ASSERT( !pCurr->GetpKanaComp(), "pKanaComp already exists!!" );
//STRIP001
//STRIP001     SvUShorts *pNewKana = new SvUShorts;
//STRIP001     pCurr->SetKanaComp( pNewKana );
//STRIP001
//STRIP001     const USHORT nNull = 0;
//STRIP001     MSHORT nKanaIdx = 0;
//STRIP001     long nKanaDiffSum = 0;
//STRIP001     USHORT nRepaintOfst = 0;
//STRIP001     USHORT nX = 0;
//STRIP001     sal_Bool bNoCompression = sal_False;
//STRIP001
//STRIP001     // Nicht vergessen:
//STRIP001     // CalcRightMargin() setzt pCurr->Width() auf die Zeilenbreite !
//STRIP001     CalcRightMargin( pCurr, 0 );
//STRIP001
//STRIP001     SwLinePortion* pPos = pCurr->GetPortion();
//STRIP001
//STRIP001     while( pPos )
//STRIP001     {
//STRIP001         if ( pPos->InTxtGrp() )
//STRIP001         {
//STRIP001             // get maximum portion width from info structure, calculated
//STRIP001             // during text formatting
//STRIP001             USHORT nMaxWidthDiff = GetInfo().GetMaxWidthDiff( (ULONG)pPos );
//STRIP001
//STRIP001             // check, if information is stored under other key
//STRIP001             if ( !nMaxWidthDiff && pPos == pCurr->GetFirstPortion() )
//STRIP001                 nMaxWidthDiff = GetInfo().GetMaxWidthDiff( (ULONG)pCurr );
//STRIP001
//STRIP001             // calculate difference between portion width and max. width
//STRIP001             nKanaDiffSum += nMaxWidthDiff;
//STRIP001
//STRIP001             // we store the beginning of the first compressable portion
//STRIP001             // for repaint
//STRIP001             if ( nMaxWidthDiff && !nRepaintOfst )
//STRIP001                 nRepaintOfst = nX + GetLeftMargin();
//STRIP001         }
//STRIP001         else if( pPos->InGlueGrp() && pPos->InFixMargGrp() )
//STRIP001         {
//STRIP001             if ( nKanaIdx == pCurr->GetKanaComp().Count() )
//STRIP001                 pCurr->GetKanaComp().Insert( nNull, nKanaIdx );
//STRIP001
//STRIP001             USHORT nRest;
//STRIP001
//STRIP001             if ( pPos->InTabGrp() )
//STRIP001             {
//STRIP001                 nRest = ! bNoCompression &&
//STRIP001                         ( pPos->Width() > MIN_TAB_WIDTH ) ?
//STRIP001                         pPos->Width() - MIN_TAB_WIDTH :
//STRIP001                         0;
//STRIP001
//STRIP001                 // for simplifying the handling of left, right ... tabs,
//STRIP001                 // we do expand portions, which are lying behind
//STRIP001                 // those special tabs
//STRIP001                 bNoCompression = !pPos->IsTabLeftPortion();
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 nRest = ! bNoCompression ?
//STRIP001                         ((SwGluePortion*)pPos)->GetPrtGlue() :
//STRIP001                         0;
//STRIP001
//STRIP001                 bNoCompression = sal_False;
//STRIP001             }
//STRIP001
//STRIP001             if( nKanaDiffSum )
//STRIP001             {
//STRIP001                 ULONG nCompress = ( 10000 * nRest ) / nKanaDiffSum;
//STRIP001
//STRIP001                 if ( nCompress >= 10000 )
//STRIP001                     // kanas can be expanded to 100%, and there is still
//STRIP001                     // some space remaining
//STRIP001                     nCompress = 0;
//STRIP001
//STRIP001                 else
//STRIP001                     nCompress = 10000 - nCompress;
//STRIP001
//STRIP001                 ( pCurr->GetKanaComp() )[ nKanaIdx ] = (USHORT)nCompress;
//STRIP001                 nKanaDiffSum = 0;
//STRIP001             }
//STRIP001
//STRIP001             nKanaIdx++;
//STRIP001         }
//STRIP001
//STRIP001         nX += pPos->Width();
//STRIP001         pPos = pPos->GetPortion();
//STRIP001     }
//STRIP001
//STRIP001     // set portion width
//STRIP001     nKanaIdx = 0;
//STRIP001     USHORT nCompress = ( pCurr->GetKanaComp() )[ nKanaIdx ];
//STRIP001     pPos = pCurr->GetPortion();
//STRIP001  long nDecompress = 0;
//STRIP001  nKanaDiffSum = 0;
//STRIP001
//STRIP001     while( pPos )
//STRIP001     {
//STRIP001         if ( pPos->InTxtGrp() )
//STRIP001         {
//STRIP001             const USHORT nMinWidth = pPos->Width();
//STRIP001
//STRIP001             // get maximum portion width from info structure, calculated
//STRIP001             // during text formatting
//STRIP001             USHORT nMaxWidthDiff = GetInfo().GetMaxWidthDiff( (ULONG)pPos );
//STRIP001
//STRIP001             // check, if information is stored under other key
//STRIP001             if ( !nMaxWidthDiff && pPos == pCurr->GetFirstPortion() )
//STRIP001                 nMaxWidthDiff = GetInfo().GetMaxWidthDiff( (ULONG)pCurr );
//STRIP001             nKanaDiffSum += nMaxWidthDiff;
//STRIP001             pPos->Width( nMinWidth +
//STRIP001                        ( ( 10000 - nCompress ) * nMaxWidthDiff ) / 10000 );
//STRIP001          nDecompress += pPos->Width() - nMinWidth;
//STRIP001         }
//STRIP001         else if( pPos->InGlueGrp() && pPos->InFixMargGrp() )
//STRIP001         {
//STRIP001             if( nCompress )
//STRIP001             {
//STRIP001              nKanaDiffSum *= nCompress;
//STRIP001              nKanaDiffSum /= 10000;
//STRIP001             }
//STRIP001
//STRIP001             pPos->Width( pPos->Width() - nDecompress );
//STRIP001
//STRIP001             if ( pPos->InTabGrp() )
//STRIP001                 // set fix width to width
//STRIP001                 ((SwTabPortion*)pPos)->SetFixWidth( pPos->Width() );
//STRIP001
//STRIP001             const SvUShorts& rKanaComp = pCurr->GetKanaComp();
//STRIP001             if ( ++nKanaIdx < rKanaComp.Count() )
//STRIP001                 nCompress = ( pCurr->GetKanaComp() )[ nKanaIdx ];
//STRIP001
//STRIP001          nKanaDiffSum = 0;
//STRIP001          nDecompress = 0;
//STRIP001         }
//STRIP001         pPos = pPos->GetPortion();
//STRIP001     }
//STRIP001
//STRIP001     return nRepaintOfst;
//STRIP001 }

/*************************************************************************
 *                    SwTxtAdjuster::CalcRightMargin()
 *************************************************************************/

/*N*/ SwMarginPortion *SwTxtAdjuster::CalcRightMargin( SwLineLayout *pCurr,
/*N*/   SwTwips nReal )
/*N*/ {
/*N*/   long nRealWidth;
/*N*/     const USHORT nRealHeight = GetLineHeight();
/*N*/     const USHORT nLineHeight = pCurr->Height();
/*N*/
/*N*/   KSHORT nPrtWidth = pCurr->PrtWidth();
/*N*/   SwLinePortion *pLast = pCurr->FindLastPortion();
/*N*/
/*N*/   if( GetInfo().IsMulti() )
/*N*/       nRealWidth = nReal;
/*N*/   else
/*N*/   {
/*N*/       nRealWidth = GetLineWidth();
/*N*/       // Fuer jeden FlyFrm, der in den rechten Rand hineinragt,
/*N*/       // wird eine FlyPortion angelegt.
/*N*/       const long nLeftMar = GetLeftMargin();
/*N*/         SwRect aCurrRect( nLeftMar + nPrtWidth, Y() + nRealHeight - nLineHeight,
/*N*/                           nRealWidth - nPrtWidth, nLineHeight );
/*N*/
/*N*/       SwFlyPortion *pFly = CalcFlyPortion( nRealWidth, aCurrRect );
/*N*/       while( pFly && long( nPrtWidth )< nRealWidth )
/*N*/       {
/*N*/           pLast->Append( pFly );
/*N*/           pLast = pFly;
/*N*/           if( pFly->Fix() > nPrtWidth )
/*?*/               pFly->Width( ( pFly->Fix() - nPrtWidth) + pFly->Width() + 1);
/*N*/           nPrtWidth += pFly->Width() + 1;
/*N*/           aCurrRect.Left( nLeftMar + nPrtWidth );
/*N*/           pFly = CalcFlyPortion( nRealWidth, aCurrRect );
/*N*/       }
/*N*/       if( pFly )
/*?*/           delete pFly;
/*N*/   }
/*N*/
/*N*/   SwMarginPortion *pRight = new SwMarginPortion( 0 );
/*N*/   pLast->Append( pRight );
/*N*/
/*N*/   if( long( nPrtWidth )< nRealWidth )
/*N*/       pRight->PrtWidth( KSHORT( nRealWidth - nPrtWidth ) );
/*N*/
/*N*/   // pCurr->Width() wird auf die reale Groesse gesetzt,
/*N*/   // da jetzt die MarginPortions eingehaengt sind.
/*N*/   // Dieser Trick hat wundersame Auswirkungen.
/*N*/   // Wenn pCurr->Width() == nRealWidth ist, dann wird das gesamte
/*N*/   // Adjustment implizit ausgecontert. GetLeftMarginAdjust() und
/*N*/   // IsBlocksatz() sind der Meinung, sie haetten eine mit Zeichen
/*N*/   // gefuellte Zeile.
/*N*/
/*N*/   pCurr->PrtWidth( KSHORT( nRealWidth ) );
/*N*/   return pRight;
/*N*/ }

/*************************************************************************
 *                    SwTxtAdjuster::CalcFlyAdjust()
 *************************************************************************/

/*N*/ void SwTxtAdjuster::CalcFlyAdjust( SwLineLayout *pCurr )
/*N*/ {
/*N*/   // 1) Es wird ein linker Rand eingefuegt:
/*N*/   SwMarginPortion *pLeft = pCurr->CalcLeftMargin();
/*N*/   SwGluePortion *pGlue = pLeft;       // die letzte GluePortion
/*N*/
/*N*/
/*N*/   // 2) Es wird ein rechter Rand angehaengt:
/*N*/   // CalcRightMargin berechnet auch eventuelle Ueberlappungen mit
/*N*/   // FlyFrms.
/*N*/   CalcRightMargin( pCurr );
/*N*/
/*N*/   SwLinePortion *pPos = pLeft->GetPortion();
/*N*/   xub_StrLen nLen = 0;
/*N*/
/*N*/   // Wenn wir nur eine Zeile vorliegen haben und die Textportion zusammen
/*N*/   // haengend ist und wenn zentriert wird, dann ...
/*N*/
/*N*/   sal_Bool bComplete = 0 == nStart;
/*N*/     const sal_Bool bTabCompat = GetTxtFrm()->GetNode()->GetDoc()->IsTabCompat();
/*N*/     sal_Bool bMultiTab = sal_False;
/*N*/
/*N*/   while( pPos )
/*N*/   {
/*N*/         if ( pPos->IsMultiPortion() && ((SwMultiPortion*)pPos)->HasTabulator() )
/*N*/             bMultiTab = sal_True;
/*N*/         else if( pPos->InFixMargGrp() &&
/*N*/                ( bTabCompat ? ! pPos->InTabGrp() : ! bMultiTab ) )
/*N*/         {
/*N*/             // in tab compat mode we do not want to change tab portions
/*N*/             // in non tab compat mode we do not want to change margins if we
/*N*/             // found a multi portion with tabs
/*N*/             if( SVX_ADJUST_RIGHT == GetAdjust() )
/*N*/                 ((SwGluePortion*)pPos)->MoveAllGlue( pGlue );
/*N*/             else
/*N*/             {
/*N*/                 // Eine schlaue Idee von MA:
/*N*/                 // Fuer die erste Textportion wird rechtsbuendig eingestellt,
/*N*/                 // fuer die letzte linksbuendig.
/*N*/
/*N*/                 // Die erste Textportion kriegt den ganzen Glue
/*N*/                 // Aber nur, wenn wir mehr als eine Zeile besitzen.
/*N*/                 if( bComplete && GetInfo().GetTxt().Len() == nLen )
/*N*/                     ((SwGluePortion*)pPos)->MoveHalfGlue( pGlue );
/*N*/                 else
/*N*/                 {
/*N*/                     if ( ! bTabCompat )
/*N*/                     {
/*N*/                         if( pLeft == pGlue )
/*N*/                         {
/*N*/                             // Wenn es nur einen linken und rechten Rand gibt,
/*N*/                             // dann teilen sich die Raender den Glue.
/*N*/                             if( nLen + pPos->GetLen() >= pCurr->GetLen() )
/*N*/                                 ((SwGluePortion*)pPos)->MoveHalfGlue( pGlue );
/*N*/                             else
/*?*/                                 ((SwGluePortion*)pPos)->MoveAllGlue( pGlue );
/*N*/                         }
/*N*/                         else
/*N*/                         {
/*N*/                             // Die letzte Textportion behaelt sein Glue
/*N*/                          if( !pPos->IsMarginPortion() )
/*?*/                               ((SwGluePortion*)pPos)->MoveHalfGlue( pGlue );
/*N*/                          }
/*N*/                      }
/*N*/                      else
/*?*/                         ((SwGluePortion*)pPos)->MoveHalfGlue( pGlue );
/*N*/                 }
/*N*/             }
/*N*/
/*N*/             pGlue = (SwFlyPortion*)pPos;
/*N*/             bComplete = sal_False;
/*N*/         }
/*N*/       nLen += pPos->GetLen();
/*N*/       pPos = pPos->GetPortion();
/*N*/      }
/*N*/
/*N*/      if( ! bTabCompat && ! bMultiTab && SVX_ADJUST_RIGHT == GetAdjust() )
/*N*/         // portions are moved to the right if possible
/*N*/         pLeft->AdjustRight( pCurr );
/*N*/ }

/*************************************************************************
 *                  SwTxtAdjuster::CalcAdjLine()
 *************************************************************************/

/*N*/ void SwTxtAdjuster::CalcAdjLine( SwLineLayout *pCurr )
/*N*/ {
/*N*/   ASSERT( pCurr->IsFormatAdj(), "CalcAdjLine: Why?" );
/*N*/
/*N*/   pCurr->SetFormatAdj(sal_False);
/*N*/
/*N*/     SwParaPortion* pPara = GetInfo().GetParaPortion();
/*N*/
/*N*/     switch( GetAdjust() )
/*N*/   {
/*N*/       case SVX_ADJUST_RIGHT:
/*N*/       case SVX_ADJUST_CENTER:
/*N*/       {
/*N*/           CalcFlyAdjust( pCurr );
/*N*/             pPara->GetRepaint()->SetOfst( 0 );
/*N*/           break;
/*N*/       }
/*N*/       case SVX_ADJUST_BLOCK:
/*N*/       {
/*N*/           // 8311: In Zeilen mit LineBreaks gibt es keinen Blocksatz!
/*N*/           if( pCurr->GetLen() &&
/*N*/               CH_BREAK == GetInfo().GetChar( nStart + pCurr->GetLen() - 1 ) &&
/*N*/               !IsLastBlock() )
/*N*/           {
/*N*/               if( IsLastCenter() )
/*N*/               {
/*?*/                   CalcFlyAdjust( pCurr );
/*?*/                     pPara->GetRepaint()->SetOfst( 0 );
/*?*/                   break;
/*N*/               }
/*N*/               return;
/*N*/           }
/*N*/           FormatBlock();
/*N*/           break;
/*N*/       }
/*N*/       default : return;
/*N*/   }
/*N*/
/*N*/ #if OSL_DEBUG_LEVEL > 1
 /*
     if( OPTDBG( *pInf ) )
     {
         pCurr->DebugPortions( aDbstream, pInf->GetTxt(), nStart );
         if( GetHints() )
         {
             const SwpHints &rHt = *GetHints();
             aDbstream << rHt;
             SwAttrIter::Dump( aDbstream );
         }
     }
  */
/*N*/ #endif
/*N*/ }

/*************************************************************************
 *                    SwTxtAdjuster::CalcFlyPortion()
 *
 * Die Berechnung hat es in sich: nCurrWidth geibt die Breite _vor_ dem
 * aufaddieren des Wortes das noch auf die Zeile passt! Aus diesem Grund
 * stimmt die Breite der FlyPortion auch, wenn die Blockierungssituation
 * bFirstWord && !WORDFITS eintritt.
 *************************************************************************/

/*N*/ SwFlyPortion *SwTxtAdjuster::CalcFlyPortion( const long nRealWidth,
/*N*/                                            const SwRect &rCurrRect )
/*N*/ {
/*N*/     SwTxtFly aTxtFly( GetTxtFrm() );
/*N*/
/*N*/   const KSHORT nCurrWidth = pCurr->PrtWidth();
/*N*/   SwFlyPortion *pFlyPortion = 0;
/*N*/
/*N*/     SwRect aLineVert( rCurrRect );
/*N*/     if ( GetTxtFrm()->IsRightToLeft() )
/*?*/         {DBG_ASSERT(0, "STRIP");} //STRIP001 GetTxtFrm()->SwitchLTRtoRTL( aLineVert );
/*N*/     if ( GetTxtFrm()->IsVertical() )
/*?*/         GetTxtFrm()->SwitchHorizontalToVertical( aLineVert );
/*N*/
/*N*/   // aFlyRect ist dokumentglobal !
/*N*/     SwRect aFlyRect( aTxtFly.GetFrm( aLineVert ) );
/*N*/
/*N*/     if ( GetTxtFrm()->IsRightToLeft() )
/*?*/         {DBG_ASSERT(0, "STRIP");} //STRIP001 GetTxtFrm()->SwitchRTLtoLTR( aFlyRect );
/*N*/     if ( GetTxtFrm()->IsVertical() )
/*?*/         {DBG_ASSERT(0, "STRIP"); }//STRIP001 GetTxtFrm()->SwitchVerticalToHorizontal( aFlyRect );
/*N*/
/*N*/   // Wenn ein Frame ueberlappt, wird eine Portion eroeffnet.
/*N*/   if( aFlyRect.HasArea() )
/*N*/   {
/*N*/       // aLocal ist framelokal
/*?*/       SwRect aLocal( aFlyRect );
/*?*/       aLocal.Pos( aLocal.Left() - GetLeftMargin(), aLocal.Top() );
/*?*/         if( nCurrWidth > aLocal.Left() )
/*?*/           aLocal.Left( nCurrWidth );
/*?*/
/*?*/       // Wenn das Rechteck breiter als die Zeile ist, stutzen
/*?*/       // wir es ebenfalls zurecht.
/*?*/       KSHORT nLocalWidth = KSHORT( aLocal.Left() + aLocal.Width() );
/*?*/       if( nRealWidth < long( nLocalWidth ) )
/*?*/           aLocal.Width( nRealWidth - aLocal.Left() );
/*?*/       GetInfo().GetParaPortion()->SetFly( sal_True );
/*?*/       pFlyPortion = new SwFlyPortion( aLocal );
/*?*/       pFlyPortion->Height( KSHORT( rCurrRect.Height() ) );
/*?*/       // Die Width koennte kleiner sein als die FixWidth, daher:
/*?*/       pFlyPortion->AdjFixWidth();
/*N*/   }
/*N*/   return pFlyPortion;
/*N*/ }

/*************************************************************************
 *                SwTxtPainter::_CalcDropAdjust()
 *************************************************************************/

// 6721: Drops und Adjustment
// CalcDropAdjust wird ggf. am Ende von Format() gerufen.

//STRIP001 void SwTxtAdjuster::CalcDropAdjust()
//STRIP001 {
//STRIP001  ASSERT( 1<GetDropLines() && SVX_ADJUST_LEFT!=GetAdjust() && SVX_ADJUST_BLOCK!=GetAdjust(),
//STRIP001          "CalcDropAdjust: No reason for DropAdjustment." )
//STRIP001
//STRIP001  const MSHORT nLineNr = GetLineNr();
//STRIP001
//STRIP001  // 1) Dummies ueberspringen
//STRIP001  Top();
//STRIP001
//STRIP001  if( !pCurr->IsDummy() || NextLine() )
//STRIP001  {
//STRIP001      // Erst adjustieren.
//STRIP001      GetAdjusted();
//STRIP001
//STRIP001      SwLinePortion *pPor = pCurr->GetFirstPortion();
//STRIP001
//STRIP001      // 2) Sicherstellen, dass die DropPortion dabei ist.
//STRIP001      // 3) pLeft: Die GluePor vor der DropPor
//STRIP001      if( pPor->InGlueGrp() && pPor->GetPortion()
//STRIP001            && pPor->GetPortion()->IsDropPortion() )
//STRIP001      {
//STRIP001          const SwLinePortion *pDropPor = (SwDropPortion*) pPor->GetPortion();
//STRIP001          SwGluePortion *pLeft = (SwGluePortion*) pPor;
//STRIP001
//STRIP001          // 4) pRight: Die GluePor hinter der DropPor suchen
//STRIP001          pPor = pPor->GetPortion();
//STRIP001          while( pPor && !pPor->InFixMargGrp() )
//STRIP001              pPor = pPor->GetPortion();
//STRIP001
//STRIP001          SwGluePortion *pRight = ( pPor && pPor->InGlueGrp() ) ?
//STRIP001                                  (SwGluePortion*) pPor : 0;
//STRIP001          if( pRight && pRight != pLeft )
//STRIP001          {
//STRIP001              // 5) nMinLeft berechnen. Wer steht am weitesten links?
//STRIP001              const KSHORT nDropLineStart =
//STRIP001                  KSHORT(GetLineStart()) + pLeft->Width() + pDropPor->Width();
//STRIP001              KSHORT nMinLeft = nDropLineStart;
//STRIP001              for( MSHORT i = 1; i < GetDropLines(); ++i )
//STRIP001              {
//STRIP001                  if( NextLine() )
//STRIP001                  {
//STRIP001                      // Erst adjustieren.
//STRIP001                      GetAdjusted();
//STRIP001
//STRIP001                      pPor = pCurr->GetFirstPortion();
//STRIP001                      const SwMarginPortion *pMar = pPor->IsMarginPortion() ?
//STRIP001                                                    (SwMarginPortion*)pPor : 0;
//STRIP001                      if( !pMar )
//STRIP001                          nMinLeft = 0;
//STRIP001                      else
//STRIP001                      {
//STRIP001                          const KSHORT nLineStart =
//STRIP001                              KSHORT(GetLineStart()) + pMar->Width();
//STRIP001                          if( nMinLeft > nLineStart )
//STRIP001                              nMinLeft = nLineStart;
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              // 6) Den Glue zwischen pLeft und pRight neu verteilen.
//STRIP001              if( nMinLeft < nDropLineStart )
//STRIP001              {
//STRIP001                  // Glue wird immer von pLeft nach pRight abgegeben,
//STRIP001                  // damit der Text nach links wandert.
//STRIP001                  const short nGlue = nDropLineStart - nMinLeft;
//STRIP001                  if( !nMinLeft )
//STRIP001                      pLeft->MoveAllGlue( pRight );
//STRIP001                  else
//STRIP001                      pLeft->MoveGlue( pRight, nGlue );
//STRIP001 #ifdef DBGTXT
//STRIP001                  aDbstream << "Drop adjusted: " << nGlue << endl;
//STRIP001 #endif
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( nLineNr != GetLineNr() )
//STRIP001  {
//STRIP001      Top();
//STRIP001      while( nLineNr != GetLineNr() && Next() )
//STRIP001          ;
//STRIP001  }
//STRIP001 }

/*************************************************************************
 *                SwTxtAdjuster::CalcDropRepaint()
 *************************************************************************/

/*N*/ void SwTxtAdjuster::CalcDropRepaint()
/*N*/ {
/*N*/   Top();
/*N*/   SwRepaint &rRepaint = *GetInfo().GetParaPortion()->GetRepaint();
/*N*/   if( rRepaint.Top() > Y() )
/*?*/       rRepaint.Top( Y() );
/*N*/   for( MSHORT i = 1; i < GetDropLines(); ++i )
/*N*/       NextLine();
/*N*/   const SwTwips nBottom = Y() + GetLineHeight() - 1;
/*N*/   if( rRepaint.Bottom() < nBottom )
/*?*/       rRepaint.Bottom( nBottom );
/*N*/ }


}
