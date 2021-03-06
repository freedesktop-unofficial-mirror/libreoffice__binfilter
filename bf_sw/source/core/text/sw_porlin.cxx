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

#include "txtcfg.hxx"
#include "pormulti.hxx"
#include "inftxt.hxx"
namespace binfilter {

#ifdef DBG_UTIL

/*N*/ sal_Bool ChkChain( SwLinePortion *pStart )
/*N*/ {
/*N*/   SwLinePortion *pPor = pStart->GetPortion();
/*N*/   MSHORT nCount = 0;
/*N*/   while( pPor )
/*N*/   {
/*N*/       ++nCount;
/*N*/       OSL_ENSURE( nCount < 200 && pPor != pStart,
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

/*N*/ SwLinePortion::~SwLinePortion()
/*N*/ {
/*N*/ }

/*N*/ SwLinePortion *SwLinePortion::Compress()
/*N*/ {
/*N*/   return GetLen() || Width() ? this : 0;
/*N*/ }


/*************************************************************************
 *               SwLinePortion::SwLinePortion( )
 *************************************************************************/

/*N*/ SwLinePortion::SwLinePortion( )
/*N*/   : pPortion( NULL )
/*N*/   , nLineLength( 0 )
/*N*/   , nAscent( 0 )
/*N*/ {
/*N*/ }

/*************************************************************************
 *               SwLinePortion::PrePaint()
 *************************************************************************/


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
/*N*/   {   OSL_ENSURE( pPos != this, "SwLinePortion::Truncate: loop" );
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
/*N*/ #ifdef DBG_UTIL
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
/*N*/ #ifdef DBG_UTIL
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
/*N*/   OSL_ENSURE( pPrev, "SwLinePortion::Cut(): can't cut" );
/*N*/   pPrev->SetPortion( pVictim->GetPortion() );
/*N*/   pVictim->SetPortion(0);
/*N*/   return pVictim;
/*N*/ }

/*************************************************************************
 *                SwLinePortion::FindPrevPortion()
 *************************************************************************/

/*N*/ SwLinePortion *SwLinePortion::FindPrevPortion( const SwLinePortion *pRoot )
/*N*/ {
/*N*/   OSL_ENSURE( pRoot != this, "SwLinePortion::FindPrevPortion(): invalid root" );
/*N*/   SwLinePortion *pPos = (SwLinePortion*)pRoot;
/*N*/   while( pPos->GetPortion() && pPos->GetPortion() != this )
/*N*/   {
///*N*/         DBG_LOOP;
/*N*/       pPos = pPos->GetPortion();
/*N*/   }
/*N*/   OSL_ENSURE( pPos->GetPortion(),
/*N*/           "SwLinePortion::FindPrevPortion: blowing in the wind");
/*N*/   return pPos;
/*N*/ }

/*************************************************************************
 *                virtual SwLinePortion::GetCrsrOfst()
 *************************************************************************/


/*************************************************************************
 *                virtual SwLinePortion::GetTxtSize()
 *************************************************************************/
/*N*/
/*N*/ SwPosSize SwLinePortion::GetTxtSize( const SwTxtSizeInfo & ) const
/*N*/ {
/*N*/   OSL_ENSURE( !this, "SwLinePortion::GetTxtSize: don't ask me about sizes, "
/*N*/                  "I'm only a stupid SwLinePortion" );
/*N*/   return SwPosSize();
/*N*/ }

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

/*N*/ void SwLinePortion::FormatEOL( SwTxtFormatInfo & /*rInf*/ )
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

/*N*/ long SwLinePortion::CalcSpacing( short /*nSpaceAdd*/, const SwTxtSizeInfo & /*rInf*/ ) const
/*N*/ {
/*N*/   return 0;
/*N*/ }

/*************************************************************************
 *              virtual SwLinePortion::GetExpTxt()
 *************************************************************************/

/*N*/ sal_Bool SwLinePortion::GetExpTxt( const SwTxtSizeInfo & /*rInf*/, XubString &/*rTxt*/ ) const
/*N*/ {
/*N*/   return sal_False;
/*N*/ }

/*************************************************************************
 *              virtual SwLinePortion::HandlePortion()
 *************************************************************************/


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
