/*************************************************************************
 *
 *  $RCSfile: sw_blink.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:41:06 $
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

#ifndef _DEBUG_HXX //autogen
#include <tools/debug.hxx>
#endif
#include "viewsh.hxx"
#include "rootfrm.hxx"  // GetOleShell()

#include "txtfrm.hxx"   // FindRootFrm()
#include "blink.hxx"
#include "porlin.hxx"
#include "porlay.hxx"   // SwLineLayout
namespace binfilter {

// Sichtbare Zeit:
#define BLINK_ON_TIME       2400L
// Nihct sichtbare Zeit:
#define BLINK_OFF_TIME      800L

/*************************************************************************
 * pBlink zeigt auf die Instanz, bei der sich blinkende Portions anmelden
 * muessen, ggf. muss pBlink erst per new SwBlink angelegt werden.
 * Diese werden dann rhythmisch zum Repaint angeregt und koennen abfragen,
 * ob sie zur Zeit sichtbar oder unsichtbar sein sollen ( IsVisible() ).
 *************************************************************************/
/*N*/ SwBlink *pBlink = NULL;


// Liste von blinkenden Portions
//STRIP001 SV_IMPL_OP_PTRARR_SORT( SwBlinkList, SwBlinkPortionPtr )

/*N*/ SwBlink::SwBlink()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  bVisible = sal_True;
//STRIP001  // Den Timer vorbereiten
//STRIP001  aTimer.SetTimeout( BLINK_ON_TIME );
//STRIP001  aTimer.SetTimeoutHdl( LINK(this, SwBlink, Blinker) );
/*N*/ }

//STRIP001 SwBlink::~SwBlink( )
//STRIP001 {
//STRIP001  aTimer.Stop();
//STRIP001 }

/*************************************************************************
 * SwBlink::Blinker (Timerablauf):
 * Sichtbar/unsichtbar-Flag toggeln.
 * Repaint-Rechtecke der Blinkportions ermitteln und an ihren OleShells
 * invalidieren.
 *************************************************************************/

//STRIP001 IMPL_LINK( SwBlink, Blinker, Timer *, pTimer )
//STRIP001 {
//STRIP001  bVisible = !bVisible;
//STRIP001  if( bVisible )
//STRIP001      aTimer.SetTimeout( BLINK_ON_TIME );
//STRIP001  else
//STRIP001      aTimer.SetTimeout( BLINK_OFF_TIME );
//STRIP001  if( aList.Count() )
//STRIP001  {
//STRIP001
//STRIP001      for( MSHORT nPos = 0; nPos < aList.Count(); )
//STRIP001      {
//STRIP001          const SwBlinkPortion* pTmp = aList[ nPos ];
//STRIP001          if( pTmp->GetRootFrm() &&
//STRIP001              ((SwRootFrm*)pTmp->GetRootFrm())->GetCurrShell() )
//STRIP001          {
//STRIP001              ++nPos;
//STRIP001
//STRIP001                 Point aPos = pTmp->GetPos();
//STRIP001                 long nWidth, nHeight;
//STRIP001                 switch ( pTmp->GetDirection() )
//STRIP001                 {
//STRIP001                     case 900:
//STRIP001                         aPos.X() -= pTmp->GetPortion()->GetAscent();
//STRIP001                         aPos.Y() -= pTmp->GetPortion()->Width();
//STRIP001                         nWidth = pTmp->GetPortion()->SvLSize().Height();
//STRIP001                         nHeight = pTmp->GetPortion()->SvLSize().Width();
//STRIP001                         break;
//STRIP001                  case 1800:
//STRIP001                         aPos.Y() -= pTmp->GetPortion()->Height() -
//STRIP001                                  pTmp->GetPortion()->GetAscent();
//STRIP001                      aPos.X() -= pTmp->GetPortion()->Width();
//STRIP001                         nWidth = pTmp->GetPortion()->SvLSize().Width();
//STRIP001                         nHeight = pTmp->GetPortion()->SvLSize().Height();
//STRIP001                      break;
//STRIP001                     case 2700:
//STRIP001                         aPos.X() -= pTmp->GetPortion()->Height() -
//STRIP001                                     pTmp->GetPortion()->GetAscent();
//STRIP001                         nWidth = pTmp->GetPortion()->SvLSize().Height();
//STRIP001                         nHeight = pTmp->GetPortion()->SvLSize().Width();
//STRIP001                         break;
//STRIP001                     default:
//STRIP001                         aPos.Y() -= pTmp->GetPortion()->GetAscent();
//STRIP001                         nWidth = pTmp->GetPortion()->SvLSize().Width();
//STRIP001                         nHeight = pTmp->GetPortion()->SvLSize().Height();
//STRIP001                 }
//STRIP001
//STRIP001                 Rectangle aRefresh( aPos, Size( nWidth, nHeight ) );
//STRIP001              aRefresh.Right() += ( aRefresh.Bottom()- aRefresh.Top() ) / 8;
//STRIP001              ((SwRootFrm*)pTmp->GetRootFrm())
//STRIP001                  ->GetCurrShell()->InvalidateWindows( aRefresh );
//STRIP001          }
//STRIP001          else // Portions ohne Shell koennen aus der Liste entfernt werden.
//STRIP001              aList.Remove( nPos );
//STRIP001      }
//STRIP001  }
//STRIP001  else // Wenn die Liste leer ist, kann der Timer gestoppt werden.
//STRIP001      aTimer.Stop();
//STRIP001  return sal_True;
//STRIP001 }

//STRIP001 void SwBlink::Insert( const Point& rPoint, const SwLinePortion* pPor,
//STRIP001                       const SwTxtFrm *pTxtFrm, USHORT nDir )
//STRIP001 {
//STRIP001     SwBlinkPortion *pBlinkPor = new SwBlinkPortion( pPor, nDir );
//STRIP001
//STRIP001  MSHORT nPos;
//STRIP001  if( aList.Seek_Entry( pBlinkPor, &nPos ) )
//STRIP001  {
//STRIP001         aList[ nPos ]->SetPos( rPoint );
//STRIP001      delete pBlinkPor;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001         pBlinkPor->SetPos( rPoint );
//STRIP001      pBlinkPor->SetRootFrm( pTxtFrm->FindRootFrm() );
//STRIP001      aList.Insert( pBlinkPor );
//STRIP001      pTxtFrm->SetBlinkPor();
//STRIP001      if( pPor->IsLayPortion() || pPor->IsParaPortion() )
//STRIP001          ((SwLineLayout*)pPor)->SetBlinking( sal_True );
//STRIP001
//STRIP001      if( !aTimer.IsActive() )
//STRIP001          aTimer.Start();
//STRIP001  }
//STRIP001 }

//STRIP001 void SwBlink::Replace( const SwLinePortion* pOld, const SwLinePortion* pNew )
//STRIP001 {
//STRIP001     // setting direction to 0 because direction does not matter
//STRIP001     // for this operation
//STRIP001     SwBlinkPortion aBlink( pOld, 0 );
//STRIP001  MSHORT nPos;
//STRIP001  if( aList.Seek_Entry( &aBlink, &nPos ) )
//STRIP001  {
//STRIP001      SwBlinkPortion* pTmp = new SwBlinkPortion( aList[ nPos ], pNew );
//STRIP001      aList.Remove( nPos );
//STRIP001      aList.Insert( pTmp );
//STRIP001  }
//STRIP001 }

//STRIP001 void SwBlink::Delete( const SwLinePortion* pPor )
//STRIP001 {
//STRIP001     // setting direction to 0 because direction does not matter
//STRIP001     // for this operation
//STRIP001     SwBlinkPortion aBlink( pPor, 0 );
//STRIP001  MSHORT nPos;
//STRIP001  if( aList.Seek_Entry( &aBlink, &nPos ) )
//STRIP001      aList.Remove( nPos );
//STRIP001 }

//STRIP001 void SwBlink::FrmDelete( const SwRootFrm* pRoot )
//STRIP001 {
//STRIP001  for( MSHORT nPos = 0; nPos < aList.Count(); )
//STRIP001  {
//STRIP001      if( pRoot == aList[ nPos ]->GetRootFrm() )
//STRIP001          aList.Remove( nPos );
//STRIP001      else
//STRIP001          ++nPos;
//STRIP001  }
//STRIP001 }



}
