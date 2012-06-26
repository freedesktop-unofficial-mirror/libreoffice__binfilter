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

#include "paratr.hxx"   // pTabStop, ADJ*


#include "txtcfg.hxx"
#include "porlay.hxx"   // SwParaPortion, SetFull
#include "porfly.hxx"   // SwParaPortion, SetFull
namespace binfilter {

/*************************************************************************
 *                      class SwGluePortion
 *************************************************************************/

/*N*/ SwGluePortion::SwGluePortion( const KSHORT nInitFixWidth )
/*N*/   : nFixWidth( nInitFixWidth )
/*N*/ {
/*N*/   PrtWidth( nFixWidth );
/*N*/   SetWhichPor( POR_GLUE );
/*N*/ }

/*************************************************************************
 *                      SwGluePortion::MoveGlue()
 *************************************************************************/

/*N*/ void SwGluePortion::MoveGlue( SwGluePortion *pTarget, const short nPrtGlue )
/*N*/ {
/*N*/   short nPrt = Min( nPrtGlue, GetPrtGlue() );
/*N*/   if( 0 < nPrt )
/*N*/   {
/*N*/       pTarget->AddPrtWidth( nPrt );
/*N*/       SubPrtWidth( nPrt );
/*N*/   }
/*N*/ }

/*************************************************************************
 *                void SwGluePortion::Join()
 *************************************************************************/

/*N*/ void SwGluePortion::Join( SwGluePortion *pVictim )
/*N*/ {
/*N*/   // Die GluePortion wird ausgesogen und weggespuelt ...
/*N*/   AddPrtWidth( pVictim->PrtWidth() );
/*N*/   SetLen( pVictim->GetLen() + GetLen() );
/*N*/   if( Height() < pVictim->Height() )
/*N*/       Height( pVictim->Height() );
/*N*/
/*N*/   AdjFixWidth();
/*N*/   Cut( pVictim );
/*N*/   delete pVictim;
/*N*/ }

/*************************************************************************
 *                class SwFixPortion
 *************************************************************************/

// Wir erwarten ein framelokales SwRect !
/*N*/ SwFixPortion::SwFixPortion( const SwRect &rRect )
/*N*/      :SwGluePortion( KSHORT(rRect.Width()) ), nFix( KSHORT(rRect.Left()) )
/*N*/ {
/*N*/   Height( KSHORT(rRect.Height()) );
/*N*/   SetWhichPor( POR_FIX );
/*N*/ }
/*N*/
/*N*/ SwFixPortion::SwFixPortion(const KSHORT nFixWidth1, const KSHORT nFixPos)
/*N*/      : SwGluePortion(nFixWidth1), nFix(nFixPos)
/*N*/ {
/*N*/   SetWhichPor( POR_FIX );
/*N*/ }

/*************************************************************************
 *                class SwMarginPortion
 *************************************************************************/

/*N*/ SwMarginPortion::SwMarginPortion( const KSHORT nFixWidth2 )
/*N*/   :SwGluePortion( nFixWidth2 )
/*N*/ {
/*N*/   SetWhichPor( POR_MARGIN );
/*N*/ }

/*************************************************************************
 *                SwMarginPortion::AdjustRight()
 *
 * In der umschliessenden Schleife werden alle Portions durchsucht,
 * dabei werden erst die am Ende liegenden GluePortions verarbeitet.
 * Das Ende wird nach jeder Schleife nach vorne verlegt, bis keine
 * GluePortions mehr vorhanden sind.
 * Es werden immer GluePortion-Paare betrachtet (pLeft und pRight),
 * wobei Textportions zwischen pLeft und pRight hinter pRight verschoben
 * werden, wenn pRight genuegend Glue besitzt. Bei jeder Verschiebung
 * wandert ein Teil des Glues von pRight nach pLeft.
 * Im naechsten Schleifendurchlauf ist pLeft das pRight und das Spiel
 * beginnt von vorne.
 *************************************************************************/

/*N*/ void SwMarginPortion::AdjustRight( const SwLineLayout *pCurr )
/*N*/ {
/*N*/   SwGluePortion *pRight = 0;
/*N*/   BOOL bNoMove = 0 != pCurr->GetpKanaComp();
/*N*/   while( pRight != this )
/*N*/   {
/*N*/
/*N*/       // 1) Wir suchen den linken Glue
/*N*/       SwLinePortion *pPos = (SwLinePortion*)this;
/*N*/       SwGluePortion *pLeft = 0;
/*N*/       while( pPos )
/*N*/       {
/*N*/           if( pPos->InFixMargGrp() )
/*N*/               pLeft = (SwGluePortion*)pPos;
/*N*/           pPos = pPos->GetPortion();
/*N*/           if( pPos == pRight)
/*N*/               pPos = 0;
/*N*/       }
/*N*/
/*N*/       // Zwei nebeneinander liegende FlyPortions verschmelzen
/*N*/       if( pRight && pLeft->GetPortion() == pRight )
/*N*/       {
/*?*/           pRight->MoveAllGlue( pLeft );
/*?*/           pRight = 0;
/*N*/       }
/*N*/       KSHORT nRightGlue = pRight && 0 < pRight->GetPrtGlue()
/*N*/                         ? KSHORT(pRight->GetPrtGlue()) : 0;
/*N*/       // 2) linken und rechten Glue ausgleichen
/*N*/       //    Bei Tabs haengen wir nix um ...
/*N*/       if( pLeft && nRightGlue && !pRight->InTabGrp() )
/*N*/       {
/*?*/           // pPrev ist die Portion, die unmittelbar vor pRight liegt.
/*?*/           SwLinePortion *pPrev = pRight->FindPrevPortion( pLeft );
/*?*/
/*?*/           if ( pRight->IsFlyPortion() && pRight->GetLen() )
/*?*/           {
/*?*/               SwFlyPortion *pFly = (SwFlyPortion *)pRight;
/*?*/               if ( pFly->GetBlankWidth() < nRightGlue )
/*?*/               {
/*?*/                   // Hier entsteht eine neue TxtPortion, die dass zuvor
/*?*/                   // vom Fly verschluckte Blank reaktiviert.
/*?*/                   nRightGlue -= pFly->GetBlankWidth();
/*?*/                   pFly->SubPrtWidth( pFly->GetBlankWidth() );
/*?*/                   pFly->SetLen( 0 );
/*?*/                   SwTxtPortion *pNewPor = new SwTxtPortion;
/*?*/                   pNewPor->SetLen( 1 );
/*?*/                   pNewPor->Height( pFly->Height() );
/*?*/                   pNewPor->Width( pFly->GetBlankWidth() );
/*?*/                   pFly->Insert( pNewPor );
/*?*/               }
/*?*/               else
/*?*/                   pPrev = pLeft;
/*?*/           }
/*?*/           while( pPrev != pLeft )
/*?*/           {
/*?*/               if( bNoMove || pPrev->PrtWidth() >= nRightGlue ||
/*?*/                   pPrev->InHyphGrp() || pPrev->IsKernPortion() )
/*?*/               {
/*?*/                   // Die Portion, die vor pRight liegt kann nicht
/*?*/                   // verschoben werden, weil kein Glue mehr vorhanden ist.
/*?*/                   // Wir fuehren die Abbruchbedingung herbei:
/*?*/                   pPrev = pLeft;
/*?*/               }
/*?*/               else
/*?*/               {
/*?*/                   nRightGlue -= pPrev->PrtWidth();
/*?*/                   // pPrev wird hinter pRight verschoben.
/*?*/                   // Dazu wird der Gluewert zwischen pRight und pLeft
/*?*/                   // ausgeglichen.
/*?*/                   pRight->MoveGlue( pLeft, short( pPrev->PrtWidth() ) );
/*?*/                   // Jetzt wird die Verkettung gerichtet.
/*?*/                   SwLinePortion *pPrevPrev = pPrev->FindPrevPortion( pLeft );
/*?*/                   pPrevPrev->SetPortion( pRight );
/*?*/                   pPrev->SetPortion( pRight->GetPortion() );
/*?*/                   pRight->SetPortion( pPrev );
/*?*/                   if ( pPrev->GetPortion() && pPrev->InTxtGrp()
/*?*/                        && pPrev->GetPortion()->IsHolePortion() )
/*?*/                   {
/*?*/                       SwHolePortion *pHolePor =
/*?*/                           (SwHolePortion*)pPrev->GetPortion();
/*?*/                       if ( !pHolePor->GetPortion() ||
/*?*/                            !pHolePor->GetPortion()->InFixMargGrp() )
/*?*/                       {
/*?*/                           pPrev->AddPrtWidth( pHolePor->GetBlankWidth() );
/*?*/                           pPrev->SetLen( pPrev->GetLen() + 1 );
/*?*/                           pPrev->SetPortion( pHolePor->GetPortion() );
/*?*/                           delete pHolePor;
/*?*/                       }
/*?*/                   }
/*?*/                   pPrev = pPrevPrev;
/*?*/               }
/*?*/           }
/*N*/       }
/*N*/       // Wenn es keinen linken Glue mehr gibt, wird die Abbruchbedingung
/*N*/       // herbeigefuehrt.
/*N*/       pRight = pLeft ? pLeft : (SwGluePortion*)this;
/*N*/   }
/*N*/ }


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
