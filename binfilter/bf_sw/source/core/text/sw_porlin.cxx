/*************************************************************************
 *
 *  $RCSfile: sw_porlin.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: obo $ $Date: 2004-11-17 09:10:57 $
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

#ifdef BIDI
// auto strip #ifndef _OUTDEV_HXX //autogen
// auto strip #include <vcl/outdev.hxx>
// auto strip #endif
#endif
// auto strip #ifndef _SW_PORTIONHANDLER_HXX
// auto strip #include <SwPortionHandler.hxx>
// auto strip #endif

// auto strip #include "errhdl.hxx"   // ASSERT

#include "txtcfg.hxx"
// auto strip #include "porlin.hxx"
// auto strip #include "inftxt.hxx"
// auto strip #include "portxt.hxx"
#include "pormulti.hxx"
// auto strip #include "porglue.hxx"
#include "inftxt.hxx"
#include "blink.hxx"
namespace binfilter {

#ifndef PRODUCT

/*N*/ sal_Bool ChkChain( SwLinePortion *pStart )
/*N*/ {
/*N*/   SwLinePortion *pPor = pStart->GetPortion();
/*N*/   MSHORT nCount = 0;
/*N*/   while( pPor )
/*N*/   {
/*N*/       ++nCount;
/*N*/       ASSERT( nCount < 200 && pPor != pStart,
/*N*/               "ChkChain(): lost in chains" );
/*N*/       if( nCount >= 200 || pPor == pStart )
/*N*/       {
/*N*/           // der Lebensretter
/*?*/           pPor = pStart->GetPortion();
/*?*/           pStart->SetPortion(0);
/*?*/           pPor->Truncate();
/*?*/           pStart->SetPortion( pPor );
/*?*/           return sal_False;
/*N*/       }
/*N*/       pPor = pPor->GetPortion();
/*N*/   }
/*N*/   return sal_True;
/*N*/ }
#endif

#if OSL_DEBUG_LEVEL > 1
const sal_Char *GetPortionName( const MSHORT nType );
#endif

/*N*/ SwLinePortion::~SwLinePortion()
/*N*/ {
/*N*/   if( pBlink )
            {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/       pBlink->Delete( this );
/*N*/ }

/*N*/ SwLinePortion *SwLinePortion::Compress()
/*N*/ {
/*N*/   return GetLen() || Width() ? this : 0;
/*N*/ }

//STRIP001 KSHORT SwLinePortion::GetViewWidth( const SwTxtSizeInfo & ) const
//STRIP001 {
//STRIP001  return 0;
//STRIP001 }

/*************************************************************************
 *               SwLinePortion::SwLinePortion( )
 *************************************************************************/

/*N*/ SwLinePortion::SwLinePortion( ) :
/*N*/   nLineLength( 0 ),
/*N*/   nAscent( 0 ),
/*N*/   pPortion( NULL )
/*N*/ {
/*N*/ }

/*************************************************************************
 *               SwLinePortion::PrePaint()
 *************************************************************************/

//STRIP001 void SwLinePortion::PrePaint( const SwTxtPaintInfo& rInf,
//STRIP001                               const SwLinePortion* pLast ) const
//STRIP001 {
//STRIP001     ASSERT( rInf.OnWin(), "SwLinePortion::PrePaint: don't prepaint on a printer");
//STRIP001  ASSERT( !Width(), "SwLinePortion::PrePaint: For Width()==0 only!");
//STRIP001
//STRIP001     const KSHORT nViewWidth = GetViewWidth( rInf );
//STRIP001
//STRIP001     if( ! nViewWidth )
//STRIP001         return;
//STRIP001
//STRIP001     const KSHORT nHalfView = nViewWidth / 2;
//STRIP001     USHORT nLastWidth = pLast->Width();
//STRIP001
//STRIP001     if ( pLast->InSpaceGrp() && rInf.GetSpaceAdd() )
//STRIP001         nLastWidth += (USHORT)pLast->CalcSpacing( rInf.GetSpaceAdd(), rInf );
//STRIP001
//STRIP001     KSHORT nPos;
//STRIP001     SwTxtPaintInfo aInf( rInf );
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001     const BOOL bBidiPor = ( rInf.GetTxtFrm()->IsRightToLeft() ) !=
//STRIP001                           ( 0 != ( TEXT_LAYOUT_BIDI_RTL & rInf.GetOut()->GetLayoutMode() ) );
//STRIP001
//STRIP001     USHORT nDir = bBidiPor ?
//STRIP001                   1800 :
//STRIP001                   rInf.GetFont()->GetOrientation( rInf.GetTxtFrm()->IsVertical() );
//STRIP001 #else
//STRIP001     USHORT nDir = rInf.GetFont()->GetOrientation( rInf.GetTxtFrm()->IsVertical() );
//STRIP001 #endif
//STRIP001
//STRIP001     switch ( nDir )
//STRIP001     {
//STRIP001     case 0 :
//STRIP001         nPos = KSHORT( rInf.X() );
//STRIP001         if( nLastWidth > nHalfView )
//STRIP001             nPos += nLastWidth - nHalfView;
//STRIP001         aInf.X( nPos );
//STRIP001         break;
//STRIP001     case 900 :
//STRIP001         nPos = KSHORT( rInf.Y() );
//STRIP001         if( nLastWidth > nHalfView )
//STRIP001             nPos -= nLastWidth + nHalfView;
//STRIP001         aInf.Y( nPos );
//STRIP001         break;
//STRIP001 #ifdef BIDI
//STRIP001     case 1800 :
//STRIP001         nPos = KSHORT( rInf.X() );
//STRIP001         if( nLastWidth > nHalfView )
//STRIP001             nPos -= nLastWidth + nHalfView;
//STRIP001         aInf.X( nPos );
//STRIP001         break;
//STRIP001 #endif
//STRIP001     case 2700 :
//STRIP001         nPos = KSHORT( rInf.Y() );
//STRIP001         if( nLastWidth > nHalfView )
//STRIP001             nPos += nLastWidth - nHalfView;
//STRIP001         aInf.Y( nPos );
//STRIP001         break;
//STRIP001     }
//STRIP001
//STRIP001  SwLinePortion *pThis = (SwLinePortion*)this;
//STRIP001  pThis->Width( nViewWidth );
//STRIP001  Paint( aInf );
//STRIP001  pThis->Width(0);
//STRIP001 }

/*************************************************************************
 *                  SwLinePortion::CalcTxtSize()
 *************************************************************************/

/*N*/ void SwLinePortion::CalcTxtSize( const SwTxtSizeInfo &rInf )
/*N*/ {
/*N*/   if( GetLen() == rInf.GetLen()  )
/*N*/       *((SwPosSize*)this) = GetTxtSize( rInf );
/*N*/   else
/*N*/   {
/*?*/       SwTxtSizeInfo aInf( rInf );
/*?*/       aInf.SetLen( GetLen() );
/*?*/       *((SwPosSize*)this) = GetTxtSize( aInf );
/*N*/   }
/*N*/ }

/*************************************************************************
 *                  SwLinePortion::Truncate()
 *
 * Es werden alle nachfolgenden Portions geloescht.
 *************************************************************************/

/*N*/ void SwLinePortion::_Truncate()
/*N*/ {
/*N*/   SwLinePortion *pPos = pPortion;
/*N*/   do
/*N*/   {   ASSERT( pPos != this, "SwLinePortion::Truncate: loop" );
/*N*/       SwLinePortion *pLast = pPos;
/*N*/       pPos = pPos->GetPortion();
/*N*/       pLast->SetPortion( 0 );
/*N*/       delete pLast;
/*N*/
/*N*/   } while( pPos );
/*N*/
/*N*/   pPortion = 0;
/*N*/ }

/*************************************************************************
 *                virtual SwLinePortion::Insert()
 *
 * Es wird immer hinter uns eingefuegt.
 *************************************************************************/

/*N*/ SwLinePortion *SwLinePortion::Insert( SwLinePortion *pIns )
/*N*/ {
/*N*/   pIns->FindLastPortion()->SetPortion( pPortion );
/*N*/   SetPortion( pIns );
/*N*/ #ifndef PRODUCT
/*N*/   ChkChain( this );
/*N*/ #endif
/*N*/   return pIns;
/*N*/ }

/*************************************************************************
 *                  SwLinePortion::FindLastPortion()
 *************************************************************************/

/*N*/ SwLinePortion *SwLinePortion::FindLastPortion()
/*N*/ {
/*N*/   register SwLinePortion *pPos = this;
/*N*/   // An das Ende wandern und pLinPortion an den letzten haengen ...
/*N*/   while( pPos->GetPortion() )
/*N*/   {
///*N*/         DBG_LOOP;
/*N*/       pPos = pPos->GetPortion();
/*N*/   }
/*N*/   return pPos;
/*N*/ }

/*************************************************************************
 *                virtual SwLinePortion::Append()
 *************************************************************************/

/*N*/ SwLinePortion *SwLinePortion::Append( SwLinePortion *pIns )
/*N*/ {
/*N*/   SwLinePortion *pPos = FindLastPortion();
/*N*/   pPos->SetPortion( pIns );
/*N*/   pIns->SetPortion( 0 );
/*N*/ #ifndef PRODUCT
/*N*/   ChkChain( this );
/*N*/ #endif
/*N*/   return pIns;
/*N*/ }

/*************************************************************************
 *                virtual SwLinePortion::Cut()
 *************************************************************************/

/*N*/ SwLinePortion *SwLinePortion::Cut( SwLinePortion *pVictim )
/*N*/ {
/*N*/   SwLinePortion *pPrev = pVictim->FindPrevPortion( this );
/*N*/   ASSERT( pPrev, "SwLinePortion::Cut(): can't cut" );
/*N*/   pPrev->SetPortion( pVictim->GetPortion() );
/*N*/   pVictim->SetPortion(0);
/*N*/   return pVictim;
/*N*/ }

/*************************************************************************
 *                SwLinePortion::FindPrevPortion()
 *************************************************************************/

/*N*/ SwLinePortion *SwLinePortion::FindPrevPortion( const SwLinePortion *pRoot )
/*N*/ {
/*N*/   ASSERT( pRoot != this, "SwLinePortion::FindPrevPortion(): invalid root" );
/*N*/   SwLinePortion *pPos = (SwLinePortion*)pRoot;
/*N*/   while( pPos->GetPortion() && pPos->GetPortion() != this )
/*N*/   {
///*N*/         DBG_LOOP;
/*N*/       pPos = pPos->GetPortion();
/*N*/   }
/*N*/   ASSERT( pPos->GetPortion(),
/*N*/           "SwLinePortion::FindPrevPortion: blowing in the wind");
/*N*/   return pPos;
/*N*/ }

/*************************************************************************
 *                virtual SwLinePortion::GetCrsrOfst()
 *************************************************************************/

//STRIP001 xub_StrLen SwLinePortion::GetCrsrOfst( const KSHORT nOfst ) const
//STRIP001 {
//STRIP001  if( nOfst > ( PrtWidth() / 2 ) )
//STRIP001      return GetLen();
//STRIP001  else
//STRIP001      return 0;
//STRIP001 }

/*************************************************************************
 *                virtual SwLinePortion::GetTxtSize()
 *************************************************************************/
/*N*/
/*N*/ SwPosSize SwLinePortion::GetTxtSize( const SwTxtSizeInfo & ) const
/*N*/ {
/*N*/   ASSERT( !this, "SwLinePortion::GetTxtSize: don't ask me about sizes, "
/*N*/                  "I'm only a stupid SwLinePortion" );
/*N*/   return SwPosSize();
/*N*/ }

#ifndef PRODUCT

/*************************************************************************
 *                virtual SwLinePortion::Check()
 *************************************************************************/

//STRIP001 sal_Bool SwLinePortion::Check( SvStream &, SwTxtSizeInfo & ) //$ ostream
//STRIP001 {
//STRIP001 #ifdef USED
//STRIP001  SwPosSize aSize( GetTxtSize( rInfo ) );
//STRIP001  if( Width() != aSize.Width() )
//STRIP001  {
//STRIP001      CONSTCHAR( pDbgTxt, "Error in width of SwLinePortion: " );
//STRIP001      rOs << pDbgTxt << endl;
//STRIP001      operator<<( rOs );
//STRIP001      rOs << endl;
//STRIP001      rOs << "Had: " << Width() << " And: " << aSize.Width();
//STRIP001      return sal_False;
//STRIP001  }
//STRIP001 #endif /* USED */
//STRIP001  return sal_True;
//STRIP001 }
#endif

/*************************************************************************
 *                 virtual SwLinePortion::Format()
 *************************************************************************/

/*N*/ sal_Bool SwLinePortion::Format( SwTxtFormatInfo &rInf )
/*N*/ {
/*N*/   if( rInf.X() > rInf.Width() )
/*N*/   {
/*?*/       Truncate();
/*?*/       rInf.SetUnderFlow( this );
/*?*/       return sal_True;
/*N*/   }
/*N*/
/*N*/   register const SwLinePortion *pLast = rInf.GetLast();
/*N*/   Height( pLast->Height() );
/*N*/   SetAscent( pLast->GetAscent() );
/*N*/   const KSHORT nNewWidth = rInf.X() + PrtWidth();
/*N*/   // Nur Portions mit echter Breite koennen ein sal_True zurueckliefern
/*N*/   // Notizen beispielsweise setzen niemals bFull==sal_True
/*N*/     if( rInf.Width() <= nNewWidth && PrtWidth() && ! IsKernPortion() )
/*N*/   {
/*?*/       Truncate();
/*?*/       if( nNewWidth > rInf.Width() )
/*?*/           PrtWidth( nNewWidth - rInf.Width() );
/*?*/       rInf.GetLast()->FormatEOL( rInf );
/*?*/       return sal_True;
/*N*/   }
/*N*/   return sal_False;
/*N*/ }

/*************************************************************************
 *                 virtual SwLinePortion::FormatEOL()
 *************************************************************************/

// Format end of line

/*N*/ void SwLinePortion::FormatEOL( SwTxtFormatInfo &rInf )
/*N*/ { }

/*************************************************************************
 *                      SwLinePortion::Move()
 *************************************************************************/

/*N*/ void SwLinePortion::Move( SwTxtPaintInfo &rInf )
/*N*/ {
/*N*/   BOOL bB2T = rInf.GetDirection() == DIR_BOTTOM2TOP;
/*N*/ #ifdef BIDI
/*N*/     const BOOL bFrmDir = rInf.GetTxtFrm()->IsRightToLeft();
/*N*/     BOOL bCounterDir = ( ! bFrmDir && DIR_RIGHT2LEFT == rInf.GetDirection() ) ||
/*N*/                        (   bFrmDir && DIR_LEFT2RIGHT == rInf.GetDirection() );
/*N*/ #endif
/*N*/
/*N*/     if ( InSpaceGrp() && rInf.GetSpaceAdd() )
/*N*/   {
/*?*/       SwTwips nTmp = PrtWidth() + CalcSpacing( rInf.GetSpaceAdd(), rInf );
/*?*/       if( rInf.IsRotated() )
/*?*/           rInf.Y( rInf.Y() + ( bB2T ? -nTmp : nTmp ) );
/*?*/ #ifdef BIDI
/*?*/         else if ( bCounterDir )
/*?*/             rInf.X( rInf.X() - nTmp );
/*?*/ #endif
/*?*/         else
/*?*/             rInf.X( rInf.X() + nTmp );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/         if( InFixMargGrp() && !IsMarginPortion() )
/*N*/       {
/*N*/           rInf.IncSpaceIdx();
/*N*/             rInf.IncKanaIdx();
/*N*/       }
/*N*/       if( rInf.IsRotated() )
/*?*/           rInf.Y( rInf.Y() + ( bB2T ? -PrtWidth() : PrtWidth() ) );
/*N*/ #ifdef BIDI
/*N*/         else if ( bCounterDir )
/*?*/             rInf.X( rInf.X() - PrtWidth() );
/*N*/ #endif
/*N*/         else
/*N*/           rInf.X( rInf.X() + PrtWidth() );
/*N*/   }
/*N*/   if( IsMultiPortion() && ((SwMultiPortion*)this)->HasTabulator() )
/*?*/       rInf.IncSpaceIdx();
/*N*/
/*N*/   rInf.SetIdx( rInf.GetIdx() + GetLen() );
/*N*/ }

/*************************************************************************
 *              virtual SwLinePortion::CalcSpacing()
 *************************************************************************/

/*N*/ long SwLinePortion::CalcSpacing( short nSpaceAdd, const SwTxtSizeInfo &rInf ) const
/*N*/ {
/*N*/   return 0;
/*N*/ }

/*************************************************************************
 *              virtual SwLinePortion::GetExpTxt()
 *************************************************************************/

/*N*/ sal_Bool SwLinePortion::GetExpTxt( const SwTxtSizeInfo &rInf, XubString &rTxt ) const
/*N*/ {
/*N*/   return sal_False;
/*N*/ }

/*************************************************************************
 *              virtual SwLinePortion::HandlePortion()
 *************************************************************************/

//STRIP001 void SwLinePortion::HandlePortion( SwPortionHandler& rPH ) const
//STRIP001 {
//STRIP001     String aString;
//STRIP001     rPH.Special( GetLen(), aString, GetWhichPor() );
//STRIP001 }

}
