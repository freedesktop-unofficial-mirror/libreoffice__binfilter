/*************************************************************************
 *
 *  $RCSfile: sw_porglue.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:53:33 $
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

// auto strip #include "swrect.hxx"
#include "paratr.hxx"   // pTabStop, ADJ*
// auto strip #include "viewopt.hxx"    // SwViewOptions
// auto strip #include "errhdl.hxx"     // ASSERT

// auto strip #ifndef _SW_PORTIONHANDLER_HXX
// auto strip #include <SwPortionHandler.hxx>
// auto strip #endif

#include "txtcfg.hxx"
// auto strip #include "porglue.hxx"
// auto strip #include "inftxt.hxx"
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
 *                virtual SwGluePortion::GetCrsrOfst()
 *************************************************************************/

//STRIP001 xub_StrLen SwGluePortion::GetCrsrOfst( const KSHORT nOfst ) const
//STRIP001 {
//STRIP001  if( !GetLen() || nOfst > GetLen() || !Width() )
//STRIP001      return SwLinePortion::GetCrsrOfst( nOfst );
//STRIP001  else
//STRIP001      return nOfst / (Width() / GetLen());
//STRIP001 }

/*************************************************************************
 *                virtual SwGluePortion::GetTxtSize()
 *************************************************************************/

//STRIP001 SwPosSize SwGluePortion::GetTxtSize( const SwTxtSizeInfo &rInf ) const
//STRIP001 {
//STRIP001  if( 1 >= GetLen() || rInf.GetLen() > GetLen() || !Width() || !GetLen() )
//STRIP001      return SwPosSize(*this);
//STRIP001  else
//STRIP001      return SwPosSize( (Width() / GetLen()) * rInf.GetLen(), Height() );
//STRIP001 }

/*************************************************************************
 *              virtual SwGluePortion::GetExpTxt()
 *************************************************************************/

//STRIP001 sal_Bool SwGluePortion::GetExpTxt( const SwTxtSizeInfo &rInf, XubString &rTxt ) const
//STRIP001 {
//STRIP001  if( GetLen() && rInf.OnWin() &&
//STRIP001      rInf.GetOpt().IsBlank() && rInf.IsNoSymbol() )
//STRIP001  {
//STRIP001      rTxt.Fill( GetLen(), CH_BULLET );
//STRIP001      return sal_True;
//STRIP001  }
//STRIP001  return sal_False;
//STRIP001 }

/*************************************************************************
 *                virtual SwGluePortion::Paint()
 *************************************************************************/

//STRIP001 void SwGluePortion::Paint( const SwTxtPaintInfo &rInf ) const
//STRIP001 {
//STRIP001  if( !GetLen() )
//STRIP001      return;
//STRIP001
//STRIP001  if( rInf.GetFont()->IsPaintBlank() )
//STRIP001  {
//STRIP001      XubString aTxt;
//STRIP001      aTxt.Fill( GetFixWidth() / GetLen(), ' ' );
//STRIP001      SwTxtPaintInfo aInf( rInf, aTxt );
//STRIP001      aInf.DrawText( *this, aTxt.Len(), sal_True );
//STRIP001  }
//STRIP001
//STRIP001  if( rInf.OnWin() && rInf.GetOpt().IsBlank() && rInf.IsNoSymbol() )
//STRIP001  {
//STRIP001 #ifndef PRODUCT
//STRIP001      const xub_Unicode cChar = rInf.GetChar( rInf.GetIdx() );
//STRIP001      ASSERT( CH_BLANK  == cChar || CH_BULLET == cChar,
//STRIP001              "SwGluePortion::Paint: blank expected" );
//STRIP001 #endif
//STRIP001      if( 1 == GetLen() )
//STRIP001      {
//STRIP001          String aBullet( CH_BULLET, RTL_TEXTENCODING_MS_1252 );
//STRIP001          SwPosSize aBulletSize( rInf.GetTxtSize( aBullet ) );
//STRIP001          Point aPos( rInf.GetPos() );
//STRIP001          aPos.X() += (Width()/2) - (aBulletSize.Width()/2);
//STRIP001          SwTxtPaintInfo aInf( rInf, aBullet );
//STRIP001          aInf.SetPos( aPos );
//STRIP001          SwTxtPortion aBulletPor;
//STRIP001          aBulletPor.Width( aBulletSize.Width() );
//STRIP001          aBulletPor.Height( aBulletSize.Height() );
//STRIP001          aBulletPor.SetAscent( GetAscent() );
//STRIP001          aInf.DrawText( aBulletPor, aBullet.Len(), sal_True );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          SwTxtSlotLen aSlot( &rInf, this );
//STRIP001          rInf.DrawText( *this, rInf.GetLen(), sal_True );
//STRIP001      }
//STRIP001  }
//STRIP001 }

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
/*N*/ SwFixPortion::SwFixPortion(const KSHORT nFixWidth, const KSHORT nFixPos)
/*N*/      : SwGluePortion(nFixWidth), nFix(nFixPos)
/*N*/ {
/*N*/   SetWhichPor( POR_FIX );
/*N*/ }

/*************************************************************************
 *                class SwMarginPortion
 *************************************************************************/

/*N*/ SwMarginPortion::SwMarginPortion( const KSHORT nFixWidth )
/*N*/   :SwGluePortion( nFixWidth )
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
/*N*/           DBG_LOOP;
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
/*?*/               DBG_LOOP;
/*?*/
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
