/*************************************************************************
 *
 *  $RCSfile: sw_porexp.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:52:57 $
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

// auto strip #ifndef _VIEWOPT_HXX
// auto strip #include <viewopt.hxx>    // SwViewOptions
// auto strip #endif
// auto strip #ifndef _SW_PORTIONHANDLER_HXX
// auto strip #include <SwPortionHandler.hxx>
// auto strip #endif
#ifndef _INFTXT_HXX
#include <inftxt.hxx>
#endif
#ifndef _POREXP_HXX
#include <porexp.hxx>
#endif
// auto strip #ifndef _PORLAY_HXX
// auto strip #include <porlay.hxx>
// auto strip #endif
namespace binfilter {

/*************************************************************************
 *                      class SwExpandPortion
 *************************************************************************/

//STRIP001 xub_StrLen SwExpandPortion::GetCrsrOfst( const MSHORT nOfst ) const
//STRIP001 { return SwLinePortion::GetCrsrOfst( nOfst ); }

/*************************************************************************
 *              virtual SwExpandPortion::GetExpTxt()
 *************************************************************************/

//STRIP001 sal_Bool SwExpandPortion::GetExpTxt( const SwTxtSizeInfo &rInf,
//STRIP001                               XubString &rTxt ) const
//STRIP001 {
//STRIP001  rTxt.Erase();
//STRIP001  // Nicht etwa: return 0 != rTxt.Len();
//STRIP001  // Weil: leere Felder ersetzen CH_TXTATR gegen einen Leerstring
//STRIP001  return sal_True;
//STRIP001 }

/*************************************************************************
 *              virtual SwExpandPortion::HandlePortion()
 *************************************************************************/

//STRIP001 void SwExpandPortion::HandlePortion( SwPortionHandler& rPH ) const
//STRIP001 {
//STRIP001     String aString;
//STRIP001     rPH.Special( GetLen(), aString, GetWhichPor() );
//STRIP001 }

/*************************************************************************
 *              virtual SwExpandPortion::GetTxtSize()
 *************************************************************************/

/*N*/ SwPosSize SwExpandPortion::GetTxtSize( const SwTxtSizeInfo &rInf ) const
/*N*/ {
/*N*/   SwTxtSlot aDiffTxt( &rInf, this );
/*N*/   return rInf.GetTxtSize();
/*N*/ }

/*************************************************************************
 *                 virtual SwExpandPortion::Format()
 *************************************************************************/

// 5010: Exp und Tabs

/*N*/ sal_Bool SwExpandPortion::Format( SwTxtFormatInfo &rInf )
/*N*/ {
/*N*/   SwTxtSlotLen aDiffTxt( &rInf, this );
/*N*/   const xub_StrLen nFullLen = rInf.GetLen();
/*N*/
/*N*/   // So komisch es aussieht, die Abfrage auf GetLen() muss wegen der
/*N*/   // ExpandPortions _hinter_ aDiffTxt (vgl. SoftHyphs)
/*N*/   // sal_False returnen wegen SetFull ...
/*N*/   if( !nFullLen )
/*N*/   {
/*N*/       // nicht Init(), weil wir Hoehe und Ascent brauchen
/*?*/       Width(0);
/*?*/       return sal_False;
/*N*/   }
/*N*/   return SwTxtPortion::Format( rInf );
/*N*/ }

/*************************************************************************
 *              virtual SwExpandPortion::Paint()
 *************************************************************************/

//STRIP001 void SwExpandPortion::Paint( const SwTxtPaintInfo &rInf ) const
//STRIP001 {
//STRIP001  SwTxtSlotLen aDiffTxt( &rInf, this );
//STRIP001  rInf.DrawBackBrush( *this );
//STRIP001
//STRIP001     // do we have to repaint a post it portion?
//STRIP001     if( rInf.OnWin() && pPortion && !pPortion->Width() )
//STRIP001         pPortion->PrePaint( rInf, this );
//STRIP001
//STRIP001     // The contents of field portions is not considered during the
//STRIP001     // calculation of the directions. Therefore we let vcl handle
//STRIP001     // the calculation by removing the BIDI_STRONG_FLAG temporarily.
//STRIP001     SwLayoutModeModifier aLayoutModeModifier( *rInf.GetOut() );
//STRIP001     aLayoutModeModifier.SetAuto();
//STRIP001
//STRIP001  rInf.DrawText( *this, rInf.GetLen(), sal_False );
//STRIP001 }

/*************************************************************************
 *                      class SwBlankPortion
 *************************************************************************/

/*N*/ SwLinePortion *SwBlankPortion::Compress() { return this; }

/*************************************************************************
 *                 SwBlankPortion::MayUnderFlow()
 *************************************************************************/

// 5497: Es gibt schon Gemeinheiten auf der Welt...
// Wenn eine Zeile voll mit HardBlanks ist und diese ueberlaeuft,
// dann duerfen keine Underflows generiert werden!
// Komplikationen bei Flys...

/*N*/ MSHORT SwBlankPortion::MayUnderFlow( const SwTxtFormatInfo &rInf,
/*N*/   xub_StrLen nIdx, sal_Bool bUnderFlow ) const
/*N*/ {
/*N*/   if( rInf.StopUnderFlow() )
/*N*/       return 0;
/*N*/   const SwLinePortion *pPos = rInf.GetRoot();
/*N*/   if( pPos->GetPortion() )
/*N*/       pPos = pPos->GetPortion();
/*N*/   while( pPos && pPos->IsBlankPortion() )
/*?*/       pPos = pPos->GetPortion();
/*N*/   if( !pPos || !rInf.GetIdx() || ( !pPos->GetLen() && pPos == rInf.GetRoot() ) )
/*N*/       return 0; // Nur noch BlankPortions unterwegs
/*N*/   // Wenn vor uns ein Blank ist, brauchen wir kein Underflow ausloesen,
/*N*/   // wenn hinter uns ein Blank ist, brauchen wir kein Underflow weiterreichen
/*N*/   if( bUnderFlow && CH_BLANK == rInf.GetTxt().GetChar( nIdx + 1) )
/*N*/       return 0;
/*N*/   if( nIdx && !((SwTxtFormatInfo&)rInf).GetFly() )
/*N*/   {
/*N*/       while( pPos && !pPos->IsFlyPortion() )
/*N*/           pPos = pPos->GetPortion();
/*N*/       if( !pPos )
/*N*/       {
/*N*/       //Hier wird ueberprueft, ob es in dieser Zeile noch sinnvolle Umbrueche
/*N*/       //gibt, Blanks oder Felder etc., wenn nicht, kein Underflow.
/*N*/       //Wenn Flys im Spiel sind, lassen wir das Underflow trotzdem zu.
/*N*/           xub_StrLen nBlank = nIdx;
/*N*/           while( --nBlank > rInf.GetLineStart() )
/*N*/           {
/*N*/               const xub_Unicode cCh = rInf.GetChar( nBlank );
/*N*/               if( CH_BLANK == cCh ||
/*N*/                   (( CH_TXTATR_BREAKWORD == cCh || CH_TXTATR_INWORD == cCh )
/*N*/                       && rInf.HasHint( nBlank ) ) )
/*N*/                   break;
/*N*/           }
/*N*/           if( nBlank <= rInf.GetLineStart() )
/*N*/               return 0;
/*N*/       }
/*N*/   }
/*N*/   xub_Unicode cCh;
/*N*/   if( nIdx < 2 || CH_BLANK == (cCh = rInf.GetChar( nIdx - 1 )) )
/*N*/       return 1;
/*N*/   if( CH_BREAK == cCh )
/*N*/       return 0;
/*N*/   return 2;
/*N*/ }

/*************************************************************************
 *                 virtual SwBlankPortion::FormatEOL()
 *************************************************************************/
// Format end of Line

//STRIP001 void SwBlankPortion::FormatEOL( SwTxtFormatInfo &rInf )
//STRIP001 {
//STRIP001  MSHORT nMay = MayUnderFlow( rInf, rInf.GetIdx() - nLineLength, sal_True );
//STRIP001  if( nMay )
//STRIP001  {
//STRIP001      if( nMay > 1 )
//STRIP001      {
//STRIP001          if( rInf.GetLast() == this )
//STRIP001             rInf.SetLast( FindPrevPortion( rInf.GetRoot() ) );
//STRIP001          rInf.X( rInf.X() - PrtWidth() );
//STRIP001          rInf.SetIdx( rInf.GetIdx() - GetLen() );
//STRIP001      }
//STRIP001      Truncate();
//STRIP001      rInf.SetUnderFlow( this );
//STRIP001      if( rInf.GetLast()->IsKernPortion() )
//STRIP001          rInf.SetUnderFlow( rInf.GetLast() );
//STRIP001  }
//STRIP001 }

/*************************************************************************
 *                 virtual SwBlankPortion::Format()
 *************************************************************************/

// 7771: UnderFlows weiterreichen und selbst ausloesen!
/*N*/ sal_Bool SwBlankPortion::Format( SwTxtFormatInfo &rInf )
/*N*/ {
/*N*/   const sal_Bool bFull = rInf.IsUnderFlow() || SwExpandPortion::Format( rInf );
/*N*/   if( bFull && MayUnderFlow( rInf, rInf.GetIdx(), rInf.IsUnderFlow() ) )
/*N*/   {
/*N*/       Truncate();
/*N*/       rInf.SetUnderFlow( this );
/*N*/       if( rInf.GetLast()->IsKernPortion() )
/*?*/           rInf.SetUnderFlow( rInf.GetLast() );
/*N*/   }
/*N*/   return bFull;
/*N*/ }

/*************************************************************************
 *                 virtual SwBlankPortion::Paint()
 *************************************************************************/

//STRIP001 void SwBlankPortion::Paint( const SwTxtPaintInfo &rInf ) const
//STRIP001 {
//STRIP001  if( !bMulti ) // No gray background for multiportion brackets
//STRIP001      rInf.DrawViewOpt( *this, POR_BLANK );
//STRIP001  SwExpandPortion::Paint( rInf );
//STRIP001 }

/*************************************************************************
 *              virtual SwBlankPortion::GetExpTxt()
 *************************************************************************/

/*N*/ sal_Bool SwBlankPortion::GetExpTxt( const SwTxtSizeInfo &rInf, XubString &rTxt ) const
/*N*/ {
/*N*/   rTxt = cChar;
/*N*/   return sal_True;
/*N*/ }

/*************************************************************************
 *              virtual SwBlankPortion::HandlePortion()
 *************************************************************************/

//STRIP001 void SwBlankPortion::HandlePortion( SwPortionHandler& rPH ) const
//STRIP001 {
//STRIP001     String aString( cChar );
//STRIP001     rPH.Special( GetLen(), aString, GetWhichPor() );
//STRIP001 }

/*************************************************************************
 *                      class SwPostItsPortion
 *************************************************************************/

//STRIP001 SwPostItsPortion::SwPostItsPortion( sal_Bool bScrpt )
//STRIP001  : nViewWidth(0), bScript( bScrpt )
//STRIP001 {
//STRIP001  nLineLength = 1;
//STRIP001  SetWhichPor( POR_POSTITS );
//STRIP001 }

//STRIP001 void SwPostItsPortion::Paint( const SwTxtPaintInfo &rInf ) const
//STRIP001 {
//STRIP001  if( rInf.OnWin() && Width() )
//STRIP001      rInf.DrawPostIts( *this, IsScript() );
//STRIP001 }

//STRIP001 KSHORT SwPostItsPortion::GetViewWidth( const SwTxtSizeInfo &rInf ) const
//STRIP001 {
//STRIP001  // Nicht zu fassen: PostIts sind immer zu sehen.
//STRIP001  return rInf.OnWin() ?
//STRIP001                 (KSHORT)rInf.GetOpt().GetPostItsWidth( rInf.GetOut() ) : 0;
//STRIP001 }

/*************************************************************************
 *                 virtual SwPostItsPortion::Format()
 *************************************************************************/

//STRIP001 sal_Bool SwPostItsPortion::Format( SwTxtFormatInfo &rInf )
//STRIP001 {
//STRIP001  sal_Bool bRet = SwLinePortion::Format( rInf );
//STRIP001  // 32749: PostIts sollen keine Auswirkung auf Zeilenhoehe etc. haben
//STRIP001  SetAscent( 1 );
//STRIP001  Height( 1 );
//STRIP001  return bRet;
//STRIP001 }

/*************************************************************************
 *              virtual SwPostItsPortion::GetExpTxt()
 *************************************************************************/

//STRIP001 sal_Bool SwPostItsPortion::GetExpTxt( const SwTxtSizeInfo &rInf,
//STRIP001                                XubString &rTxt ) const
//STRIP001 {
//STRIP001  if( rInf.OnWin() && rInf.GetOpt().IsPostIts() )
//STRIP001      rTxt = ' ';
//STRIP001  else
//STRIP001      rTxt.Erase();
//STRIP001  return sal_True;
//STRIP001 }

}
