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


#include "ftnboss.hxx"
#include "paratr.hxx"

#include <bf_svx/orphitem.hxx>
#include <bf_svx/widwitem.hxx>
#include <bf_svx/keepitem.hxx>
#include <bf_svx/spltitem.hxx>
#include <frmatr.hxx>
#include <txtftn.hxx>
#include <fmtftn.hxx>

#include "txtcfg.hxx"
#include "widorp.hxx"
#include "sectfrm.hxx"  //SwSectionFrm
#include "ftnfrm.hxx"
namespace binfilter {

#undef WIDOWTWIPS


/*************************************************************************
 *                  inline IsNastyFollow()
 *************************************************************************/
// Ein Follow, der auf der selben Seite steht, wie sein Master ist nasty.
/*N*/ inline sal_Bool IsNastyFollow( const SwTxtFrm *pFrm )
/*N*/ {
/*N*/   OSL_ENSURE( !pFrm->IsFollow() || !pFrm->GetPrev() ||
/*N*/           ((const SwTxtFrm*)pFrm->GetPrev())->GetFollow() == pFrm,
/*N*/           "IsNastyFollow: Was ist denn hier los?" );
/*N*/   return  pFrm->IsFollow() && pFrm->GetPrev();
/*N*/ }

/*************************************************************************
 *                  SwTxtFrmBreak::SwTxtFrmBreak()
 *************************************************************************/

/*N*/ SwTxtFrmBreak::SwTxtFrmBreak( SwTxtFrm *pFrm1, const SwTwips nRst )
/*N*/     : nRstHeight(nRst)
/*N*/     , pFrm(pFrm1)
/*N*/ {
/*N*/     SWAP_IF_SWAPPED( pFrm1 )
/*N*/     SWRECTFN( pFrm1 )
/*N*/     nOrigin = (pFrm1->*fnRect->fnGetPrtTop)();
/*N*/     SwSectionFrm* pSct;
/*N*/   bKeep = !pFrm1->IsMoveable() || IsNastyFollow( pFrm1 ) ||
/*N*/           ( pFrm1->IsInSct() && (pSct=pFrm1->FindSctFrm())->Lower()->IsColumnFrm()
/*N*/             && !pSct->MoveAllowed( pFrm1 ) ) ||
/*N*/           !pFrm1->GetTxtNode()->GetSwAttrSet().GetSplit().GetValue() ||
/*N*/           pFrm1->GetTxtNode()->GetSwAttrSet().GetKeep().GetValue();
/*N*/   bBreak = sal_False;
/*N*/
/*N*/   if( !nRstHeight && !pFrm1->IsFollow() && pFrm1->IsInFtn() && pFrm1->HasPara() )
/*N*/   {
/*N*/       nRstHeight = pFrm1->GetFtnFrmHeight();
/*N*/         nRstHeight += (pFrm1->Prt().*fnRect->fnGetHeight)() -
/*N*/                       (pFrm1->Frm().*fnRect->fnGetHeight)();
/*N*/       if( nRstHeight < 0 )
/*N*/           nRstHeight = 0;
/*N*/   }
/*N*/
/*N*/     UNDO_SWAP( pFrm1 )
/*N*/ }

/* BP 18.6.93: Widows.
 * Im Gegensatz zur ersten Implementierung werden die Widows nicht
 * mehr vorausschauend berechnet, sondern erst beim Formatieren des
 * gesplitteten Follows festgestellt. Im Master faellt die Widows-
 * Berechnung also generell weg (nWidows wird manipuliert).
 * Wenn der Follow feststellt, dass die Widowsregel zutrifft,
 * verschickt er an seinen Vorgaenger ein Prepare.
 * Ein besonderes Problem ergibt sich, wenn die Widows zuschlagen,
 * aber im Master noch ein paar Zeilen zur Verfuegung stehen.
 *
 */

/*************************************************************************
 *                  SwTxtFrmBreak::IsInside()
 *************************************************************************/

/* BP(22.07.92): Berechnung von Witwen und Waisen.
 * Die Methode liefert sal_True zurueck, wenn eine dieser Regelung zutrifft.
 *
 * Eine Schwierigkeit gibt es im Zusammenhang mit Widows und
 * unterschiedlichen Formaten zwischen Master- und Folgeframes:
 * Beispiel: Wenn die erste Spalte 3cm und die zweite 4cm breit ist
 * und Widows auf sagen wir 3 gesetzt ist, so ist erst bei der Formatierung
 * des Follows entscheidbar, ob die Widowsbedingung einhaltbar ist oder
 * nicht. Leider ist davon abhaengig, ob der Absatz als Ganzes auf die
 * naechste Seite rutscht.
 */

/*N*/ sal_Bool SwTxtFrmBreak::IsInside( SwTxtMargin &rLine ) const
/*N*/ {
/*N*/   register sal_Bool bFit = sal_False;
/*N*/
/*N*/     SWAP_IF_SWAPPED( pFrm )
/*N*/     SWRECTFN( pFrm )
/*N*/     // nOrigin is an absolut value, rLine referes to the swapped situation.
/*N*/
/*N*/     SwTwips nTmpY(0);
/*N*/     if ( !( pFrm->IsVertical() ) )
/*N*/         nTmpY = rLine.Y() + rLine.GetLineHeight();
/*N*/
/*N*/     SwTwips nLineHeight = (*fnRect->fnYDiff)( nTmpY , nOrigin );
/*N*/
/*N*/   // 7455 und 6114: Raum fuer die Umrandung unten einkalkulieren.
/*N*/     nLineHeight += (pFrm->*fnRect->fnGetBottomMargin)();
/*N*/
/*N*/
/*N*/   if( nRstHeight )
/*N*/       bFit = nRstHeight >= nLineHeight;
/*N*/   else
/*N*/   {
/*N*/       // Der Frm besitzt eine Hoehe, mit der er auf die Seite passt.
/*N*/         SwTwips nHeight =
/*N*/             (*fnRect->fnYDiff)( (pFrm->GetUpper()->*fnRect->fnGetPrtBottom)(), nOrigin );
/*N*/
/*N*/       // Wenn sich alles innerhalb des bestehenden Frames abspielt,
/*N*/       // ist das Ergebnis sal_True;
/*N*/       bFit = nHeight >= nLineHeight;
/*N*/       if( !bFit )
/*N*/       {
/*N*/           // Die LineHeight sprengt die aktuelle Frm-Hoehe.
/*N*/           // Nun rufen wir ein Probe-Grow, um zu ermitteln, ob der
/*N*/           // Frame um den gewuenschten Bereich wachsen wuerde.
/*N*/           nHeight += pFrm->GrowTst( LONG_MAX );
/*N*/
/*N*/           // Das Grow() returnt die Hoehe, um die der Upper des TxtFrm
/*N*/           // den TxtFrm wachsen lassen wuerde.
/*N*/           // Der TxtFrm selbst darf wachsen wie er will.
/*N*/           bFit = nHeight >= nLineHeight;
/*N*/       }
/*N*/   }
/*N*/
/*N*/     UNDO_SWAP( pFrm );
/*N*/
/*N*/     return bFit;
/*N*/ }

/*************************************************************************
 *                  SwTxtFrmBreak::IsBreakNow()
 *************************************************************************/

/*N*/ sal_Bool SwTxtFrmBreak::IsBreakNow( SwTxtMargin &rLine )
/*N*/ {
/*N*/     SWAP_IF_SWAPPED( pFrm )
/*N*/
/*N*/   // bKeep ist staerker als IsBreakNow()
/*N*/   // Ist noch genug Platz ?
/*N*/   if( bKeep || IsInside( rLine ) )
/*N*/       bBreak = sal_False;
/*N*/   else
/*N*/   {
         /* Diese Klasse geht davon aus, dass der SwTxtMargin von Top nach Bottom
          * durchgearbeitet wird. Aus Performancegruenden wird in folgenden
          * Faellen der Laden fuer das weitere Aufspalten dicht gemacht:
          * Wenn eine einzige Zeile nicht mehr passt.
          * Sonderfall: bei DummyPortions ist LineNr == 1, obwohl wir splitten
          * wollen.
          */
/*N*/       // 6010: DropLines mit einbeziehen
/*N*/
/*N*/       sal_Bool bFirstLine = 1 == rLine.GetLineNr() && !rLine.GetPrev();
/*N*/       bBreak = sal_True;
/*N*/       if( ( bFirstLine && pFrm->GetIndPrev() )
/*N*/           || ( rLine.GetLineNr() <= rLine.GetDropLines() ) )
/*N*/       {
/*N*/           bKeep = sal_True;
/*N*/           bBreak = sal_False;
/*N*/       }
/*N*/       else if(bFirstLine && pFrm->IsInFtn() && !pFrm->FindFtnFrm()->GetPrev())
/*N*/       {
/*?*/           SwLayoutFrm* pTmp = pFrm->FindFtnBossFrm()->FindBodyCont();
/*?*/           if( !pTmp || !pTmp->Lower() )
/*?*/               bBreak = sal_False;
/*N*/       }
/*N*/   }
/*N*/
/*N*/     UNDO_SWAP( pFrm )
/*N*/
/*N*/   return bBreak;
/*N*/ }

/*************************************************************************
 *                  WidowsAndOrphans::WidowsAndOrphans()
 *************************************************************************/

/*N*/ WidowsAndOrphans::WidowsAndOrphans( SwTxtFrm *pFrm2, const SwTwips nRst,
/*N*/   sal_Bool bChkKeep   )
/*N*/   : SwTxtFrmBreak( pFrm2, nRst )
/*N*/   , nWidLines( 0 )
/*N*/   , nOrphLines( 0 )
/*N*/ {
/*N*/     SWAP_IF_SWAPPED( pFrm2 )
/*N*/
/*N*/   if( bKeep )
/*N*/   {
/*N*/       // 5652: bei Absaetzen, die zusammengehalten werden sollen und
/*N*/       // groesser sind als die Seite wird bKeep aufgehoben.
/*N*/       if( bChkKeep && !pFrm2->GetPrev() && !pFrm2->IsInFtn() &&
/*N*/           pFrm2->IsMoveable() &&
/*N*/           ( !pFrm2->IsInSct() || pFrm2->FindSctFrm()->MoveAllowed(pFrm2) ) )
/*N*/           bKeep = sal_False;
/*N*/       //Auch bei gesetztem Keep muessen Orphans beachtet werden,
/*N*/       //z.B. bei verketteten Rahmen erhaelt ein Follow im letzten Rahmen ein Keep,
/*N*/       //da er nicht (vorwaerts) Moveable ist,
/*N*/       //er darf aber trotzdem vom Master Zeilen anfordern wg. der Orphanregel.
/*N*/       if( pFrm2->IsFollow() )
/*N*/           nWidLines = pFrm2->GetTxtNode()->GetSwAttrSet().GetWidows().GetValue();
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       const SwAttrSet& rSet = pFrm2->GetTxtNode()->GetSwAttrSet();
/*N*/       const SvxOrphansItem  &rOrph = rSet.GetOrphans();
/*N*/       if ( rOrph.GetValue() > 1 )
/*N*/           nOrphLines = rOrph.GetValue();
/*N*/       if ( pFrm2->IsFollow() )
/*N*/           nWidLines = rSet.GetWidows().GetValue();
/*N*/
/*N*/   }
/*N*/   if( pFrm2->IsInFtn() && !pFrm2->GetIndPrev() &&
/*N*/       ( bKeep || nWidLines || nOrphLines ) )
/*N*/   {
/*N*/       // Innerhalb von Fussnoten gibt es gute Gruende, das Keep-Attribut und
/*N*/       // die Widows/Orphans abzuschalten.
/*?*/       SwFtnFrm *pFtn = pFrm2->FindFtnFrm();
/*?*/       sal_Bool bFt = !pFtn->GetAttr()->GetFtn().IsEndNote();
/*?*/       if( !pFtn->GetPrev() &&
/*?*/           pFtn->FindFtnBossFrm( bFt ) != pFtn->GetRef()->FindFtnBossFrm( bFt )
/*?*/           && ( !pFrm2->IsInSct() || pFrm2->FindSctFrm()->MoveAllowed(pFrm2) ) )
/*?*/       {
/*?*/           bKeep = sal_False;
/*?*/           nOrphLines = 0;
/*?*/           nWidLines = 0;
/*?*/       }
/*N*/   }
/*N*/
/*N*/     UNDO_SWAP( pFrm2 )
/*N*/ }

/*************************************************************************
 *                  WidowsAndOrphans::FindBreak()
 *************************************************************************/

/* Die Find*-Methoden suchen nicht nur, sondern stellen den SwTxtMargin auf
 * die Zeile ein, wo der Absatz gebrochen werden soll und kuerzen ihn dort.
 * FindBreak()
 */

/*N*/ sal_Bool WidowsAndOrphans::FindBreak( SwTxtFrm *pFrame, SwTxtMargin &rLine,
/*N*/   sal_Bool bHasToFit )
/*N*/ {
/*N*/     SWAP_IF_SWAPPED( pFrm )
/*N*/
/*N*/   sal_Bool bRet = sal_True;
/*N*/   MSHORT nOldOrphans = nOrphLines;
/*N*/     if( bHasToFit )
/*N*/       nOrphLines = 0;
/*N*/   rLine.Bottom();
/*N*/   if( !IsBreakNow( rLine ) )
/*N*/       bRet = sal_False;
/*N*/     if( !FindWidows( pFrame, rLine ) )
/*N*/   {
/*N*/       sal_Bool bBack = sal_False;
/*N*/       while( IsBreakNow( rLine ) )
/*N*/       {
/*N*/           if( rLine.PrevLine() )
/*N*/               bBack = sal_True;
/*N*/           else
/*N*/               break;
/*N*/       }
/*N*/       // Eigentlich werden bei HasToFit Schusterjungen (Orphans) nicht
/*N*/       // beruecksichtigt, wenn allerdings Dummy-Lines im Spiel sind und
/*N*/       // die Orphansregel verletzt wird, machen wir mal eine Ausnahme:
/*N*/       // Wir lassen einfach eine Dummyline zurueck und wandern mit dem Text
/*N*/       // komplett auf die naechste Seite/Spalte.
/*N*/         if( rLine.GetLineNr() <= nOldOrphans &&
/*N*/             rLine.GetInfo().GetParaPortion()->IsDummy() &&
/*N*/             ( ( bHasToFit && bRet ) || SwTxtFrmBreak::IsBreakNow( rLine ) ) )
/*N*/           rLine.Top();
/*N*/
/*N*/       rLine.TruncLines( sal_True );
/*N*/       bRet = bBack;
/*N*/   }
/*N*/   nOrphLines = nOldOrphans;
/*N*/
/*N*/     UNDO_SWAP( pFrm )
/*N*/
/*N*/   return bRet;
/*N*/ }

/*************************************************************************
 *                  WidowsAndOrphans::FindWidows()
 *************************************************************************/

/*  FindWidows positioniert den SwTxtMargin des Masters auf die umzubrechende
 *  Zeile, indem der Follow formatiert und untersucht wird.
 *  Liefert sal_True zurueck, wenn die Widows-Regelung in Kraft tritt,
 *  d.h. der Absatz _zusammengehalten_ werden soll !
 */

/*N*/ sal_Bool WidowsAndOrphans::FindWidows( SwTxtFrm *pFrm4, SwTxtMargin &rLine )
/*N*/ {
/*N*/     OSL_ENSURE( ! pFrm4->IsVertical() || ! pFrm4->IsSwapped(),
/*N*/             "WidowsAndOrphans::FindWidows with swapped frame" );
/*N*/
/*N*/   if( !nWidLines || !pFrm4->IsFollow() )
/*N*/       return sal_False;
/*N*/
/*N*/   rLine.Bottom();
/*N*/
/*N*/   // Wir koennen noch was abzwacken
/*N*/   SwTxtFrm *pMaster = pFrm4->FindMaster();
/*N*/   OSL_ENSURE(pMaster, "+WidowsAndOrphans::FindWidows: Widows in a master?");
/*N*/   if( !pMaster )
/*N*/       return sal_False;
/*N*/
/*N*/   // 5156: Wenn die erste Zeile des Follows nicht passt, wird der Master
/*N*/   // wohl voll mit Dummies sein. In diesem Fall waere ein PREP_WIDOWS fatal.
/*N*/   if( pMaster->GetOfst() == pFrm4->GetOfst() )
/*N*/       return sal_False;
/*N*/
/*N*/   // Resthoehe des Masters
/*N*/     SWRECTFN( pFrm4 )
/*N*/
/*N*/     const SwTwips nDocPrtTop = (pFrm4->*fnRect->fnGetPrtTop)();
/*N*/     SwTwips nOldHeight(0);
/*N*/     SwTwips nTmpY = rLine.Y() + rLine.GetLineHeight();
/*N*/
/*N*/     if ( !bVert )
/*N*/         nOldHeight = (pFrm4->Prt().*fnRect->fnGetHeight)();
/*N*/
/*N*/     const SwTwips nChg = (*fnRect->fnYDiff)( nTmpY, nDocPrtTop + nOldHeight );
/*N*/
/*N*/   // Unterhalb der Widows-Schwelle...
/*N*/   if( rLine.GetLineNr() >= nWidLines )
/*N*/   {
/*N*/       // 8575: Follow to Master I
/*N*/       // Wenn der Follow *waechst*, so besteht fuer den Master die Chance,
/*N*/       // Zeilen entgegenzunehmen, die er vor Kurzem gezwungen war an den
/*N*/       // Follow abzugeben: Prepare(Need); diese Abfrage unterhalb von nChg!
/*N*/       // (0W, 2O, 2M, 2F) + 1F = 3M, 2F
/*N*/       if( rLine.GetLineNr() > nWidLines && pFrm4->IsJustWidow() )
/*N*/       {
/*?*/           // Wenn der Master gelockt ist, so hat er vermutlich gerade erst
/*?*/           // eine Zeile an uns abgegeben, diese geben nicht zurueck, nur
/*?*/           // weil bei uns daraus mehrere geworden sind (z.B. durch Rahmen).
/*?*/             if( !pMaster->IsLocked() && pMaster->GetUpper() )
/*?*/             {
/*?*/                 const SwTwips nRstHeight1 = (pMaster->Frm().*fnRect->fnBottomDist)
/*?*/                             ( (pMaster->GetUpper()->*fnRect->fnGetPrtBottom)() );
/*?*/                 if ( nRstHeight1 >=
/*?*/                      SwTwips(rLine.GetInfo().GetParaPortion()->Height() ) )
/*?*/                 {
/*?*/                     pMaster->Prepare( PREP_ADJUST_FRM );
/*?*/                     pMaster->_InvalidateSize();
/*?*/                     pMaster->InvalidatePage();
/*?*/                 }
/*?*/             }
/*?*/
/*?*/           pFrm4->SetJustWidow( sal_False );
/*N*/       }
/*N*/       return sal_False;
/*N*/               }

    // 8575: Follow to Master II
    // Wenn der Follow *schrumpft*, so besteht fuer den Master die Chance,
    // den kompletten Orphan zu inhalieren.
    // (0W, 2O, 2M, 1F) - 1F = 3M, 0F     -> PREP_ADJUST_FRM
    // (0W, 2O, 3M, 2F) - 1F = 2M, 2F     -> PREP_WIDOWS

/*N*/     if( 0 > nChg && !pMaster->IsLocked() && pMaster->GetUpper() )
/*N*/     {
/*N*/         SwTwips nRstHeight2 = (pMaster->Frm().*fnRect->fnBottomDist)
/*N*/                              ( (pMaster->GetUpper()->*fnRect->fnGetPrtBottom)() );
/*N*/         if( nRstHeight2 >= SwTwips(rLine.GetInfo().GetParaPortion()->Height() ) )
/*N*/         {
/*N*/             pMaster->Prepare( PREP_ADJUST_FRM );
/*N*/             pMaster->_InvalidateSize();
/*N*/             pMaster->InvalidatePage();
/*N*/             pFrm4->SetJustWidow( sal_False );
/*N*/             return sal_False;
/*N*/         }
/*N*/   }
/*N*/
/*N*/   // Master to Follow
/*N*/   // Wenn der Follow nach seiner Formatierung weniger Zeilen enthaelt
/*N*/   // als Widows, so besteht noch die Chance, einige Zeilen des Masters
/*N*/   // abzuzwacken. Wenn dadurch die Orphans-Regel des Masters in Kraft
/*N*/   // tritt muss im CalcPrep() des Master-Frame der Frame so vergroessert
/*N*/   // werden, dass er nicht mehr auf seine urspruengliche Seite passt.
/*N*/   // Wenn er noch ein paar Zeilen entbehren kann, dann muss im CalcPrep()
/*N*/   // ein Shrink() erfolgen, der Follow mit dem Widows rutscht dann auf
/*N*/   // die Seite des Masters, haelt sich aber zusammen, so dass er (endlich)
/*N*/   // auf die naechste Seite rutscht. - So die Theorie!
/*N*/
/*N*/
/*N*/   // Wir fordern nur noch ein Zeile zur Zeit an, weil eine Zeile des Masters
/*N*/   // bei uns durchaus mehrere Zeilen ergeben koennten.
/*N*/   // Dafuer behaelt CalcFollow solange die Kontrolle, bis der Follow alle
/*N*/   // notwendigen Zeilen bekommen hat.
/*N*/   MSHORT nNeed = 1; // frueher: nWidLines - rLine.GetLineNr();
/*N*/
/*N*/     // Special case: Master cannot give lines to follow
/*N*/     if ( ! pMaster->GetIndPrev() && pMaster->GetThisLines() <= nNeed )
/*N*/         return sal_False;
/*N*/
/*N*/   pMaster->Prepare( PREP_WIDOWS, (void*)&nNeed );
/*N*/   return sal_True;
/*N*/ }

/*************************************************************************
 *                  WidowsAndOrphans::WouldFit()
 *************************************************************************/

/*N*/ sal_Bool WidowsAndOrphans::WouldFit( SwTxtMargin &rLine, SwTwips &rMaxHeight )
/*N*/ {
/*N*/     // Here it does not matter, if pFrm is swapped or not.
/*N*/     // IsInside() takes care for itself
/*N*/
/*N*/   // Wir erwarten, dass rLine auf der letzten Zeile steht!!
/*N*/   OSL_ENSURE( !rLine.GetNext(), "WouldFit: aLine::Bottom missed!" );
/*N*/   MSHORT nLineCnt = rLine.GetLineNr();
/*N*/
/*N*/   // Erstmal die Orphansregel und den Initialenwunsch erfuellen ...
/*N*/ #ifndef USED
/*N*/   const MSHORT nMinLines = Max( GetOrphansLines(), rLine.GetDropLines() );
/*N*/ #else
/*N*/   const MSHORT nMinLines = rLine.GetDropLines();
/*N*/ #endif
/*N*/   if ( nLineCnt < nMinLines )
/*N*/       return sal_False;
/*N*/
/*N*/   rLine.Top();
/*N*/   SwTwips nLineSum = rLine.GetLineHeight();
/*N*/
/*N*/   while( nMinLines > rLine.GetLineNr() )
/*N*/   {
///*N*/         DBG_LOOP;
/*N*/       if( !rLine.NextLine() )
/*N*/           return sal_False;
/*N*/       nLineSum += rLine.GetLineHeight();
/*N*/   }
/*N*/
/*N*/   // Wenn wir jetzt schon nicht mehr passen ...
/*N*/   if( !IsInside( rLine ) )
/*N*/       return sal_False;
/*N*/
/*N*/   // Jetzt noch die Widows-Regel ueberpruefen
/*N*/   if( !nWidLines && !pFrm->IsFollow() )
/*N*/   {
/*N*/       // I.A. brauchen Widows nur ueberprueft werden, wenn wir ein Follow
/*N*/       // sind. Bei WouldFit muss aber auch fuer den Master die Regel ueber-
/*N*/       // prueft werden, weil wir ja gerade erst die Trennstelle ermitteln.
/*N*/       // Im Ctor von WidowsAndOrphans wurde nWidLines aber nur fuer Follows
/*N*/       // aus dem AttrSet ermittelt, deshalb holen wir es hier nach:
/*N*/       const SwAttrSet& rSet = pFrm->GetTxtNode()->GetSwAttrSet();
/*N*/       nWidLines = rSet.GetWidows().GetValue();
/*N*/   }
/*N*/
/*N*/   // Sind nach Orphans/Initialen noch genug Zeilen fuer die Widows uebrig?
/*N*/   if( nLineCnt - nMinLines >= GetWidowsLines() )
/*N*/   {
/*N*/         if( rMaxHeight >= nLineSum )
/*N*/       {
/*N*/           rMaxHeight -= nLineSum;
/*N*/           return sal_True;
/*N*/       }
/*N*/   }
/*N*/   return sal_False;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
