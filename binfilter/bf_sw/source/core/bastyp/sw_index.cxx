/*************************************************************************
 *
 *  $RCSfile: sw_index.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:06:21 $
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

#include <stdlib.h>             // fuer qsort

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif

#include "errhdl.hxx"           // fuers ASSERT
#include "index.hxx"
#include "error.h"              // fuers ASSERT

#ifndef PRODUCT
int SwIndex::nSerial = 0;
#endif


/*N*/ TYPEINIT0(SwIndexReg);    // rtti


#ifdef CHK

#define IDX_CHK_ARRAY       pArray->ChhkArr();
#define ARR_CHK_ARRAY       ChhkArr();


//STRIP001 void SwIndexReg::ChkArr()
//STRIP001 {
//STRIP001  ASSERT( (pFirst && pLast) || (!pFirst && !pLast),
//STRIP001          "Array falsch Indiziert" );
//STRIP001
//STRIP001  if( !pFirst )
//STRIP001      return;
//STRIP001
//STRIP001  xub_StrLen nVal = 0;
//STRIP001  const SwIndex* pIdx = pFirst, *pPrev = 0;
//STRIP001  ASSERT( !pIdx->pPrev, "Array-pFirst nicht am Anfang" );
//STRIP001
//STRIP001  while( pIdx != pLast )
//STRIP001  {
//STRIP001      ASSERT( pIdx->pPrev != pIdx && pIdx->pNext != pIdx,
//STRIP001              "Index zeigt auf sich selbst" )
//STRIP001
//STRIP001      ASSERT( pIdx->nIndex >= nVal, "Reihenfolge stimmt nicht" );
//STRIP001      ASSERT( pPrev == pIdx->pPrev, "Verkettung stimmt nicht" );
//STRIP001      pPrev = pIdx;
//STRIP001      pIdx = pIdx->pNext;
//STRIP001      nVal = pPrev->nIndex;
//STRIP001  }
//STRIP001 }

#else                                   // CHK

#define IDX_CHK_ARRAY
#define ARR_CHK_ARRAY

#endif                                  // CHK



/*N*/ SwIndex::SwIndex( SwIndexReg* pArr, xub_StrLen nIdx )
/*N*/   : pArray( pArr ), nIndex( nIdx ), pNext( 0 ), pPrev( 0 )
/*N*/ {
/*N*/   if( !pArray )
/*N*/   {
/*N*/       pArray = SwIndexReg::pEmptyIndexArray;
/*N*/       nIndex = 0;     // steht immer auf 0 !!!
/*N*/   }
/*N*/
/*N*/   if( !pArray->pFirst )         // 1. Index ??
/*N*/       pArray->pFirst = pArray->pLast = this;
/*N*/   else if( pArray->pMiddle )
/*N*/   {
/*N*/       if( pArray->pMiddle->nIndex <= nIdx )
/*N*/       {
/*N*/           if( nIdx > ((pArray->pLast->nIndex - pArray->pMiddle->nIndex) / 2) )
/*N*/               ChgValue( *pArray->pLast, nIdx );
/*N*/           else
/*N*/               ChgValue( *pArray->pMiddle, nIdx );
/*N*/       }
/*N*/       else if( nIdx > ((pArray->pMiddle->nIndex - pArray->pFirst->nIndex) / 2) )
/*N*/           ChgValue( *pArray->pMiddle, nIdx );
/*N*/       else
/*N*/           ChgValue( *pArray->pFirst, nIdx );
/*N*/   }
/*N*/   else if( nIdx > ((pArray->pLast->nIndex - pArray->pFirst->nIndex) / 2) )
/*N*/       ChgValue( *pArray->pLast, nIdx );
/*N*/   else
/*N*/       ChgValue( *pArray->pFirst, nIdx );
/*N*/
/*N*/ #ifndef PRODUCT
/*N*/   MySerial = ++nSerial;       // nur in der nicht PRODUCT-Version
/*N*/ #endif
/*N*/ IDX_CHK_ARRAY
/*N*/ }


//STRIP001 SwIndex::SwIndex( const SwIndex& rIdx, short nIdx )
//STRIP001  : pArray( rIdx.pArray ), pNext( 0 ), pPrev( 0 )
//STRIP001 {
//STRIP001  ChgValue( rIdx, rIdx.nIndex + nIdx );
//STRIP001
//STRIP001 #ifndef PRODUCT
//STRIP001  MySerial = ++nSerial;       // nur in der nicht PRODUCT-Version
//STRIP001 #endif
//STRIP001 IDX_CHK_ARRAY
//STRIP001 }


/*N*/ SwIndex::SwIndex( const SwIndex& rIdx )
/*N*/   : pArray( rIdx.pArray ), nIndex( rIdx.nIndex ), pNext( 0 ), pPrev( 0 )
/*N*/ {
/*N*/   ChgValue( rIdx, rIdx.nIndex );
/*N*/ #ifndef PRODUCT
/*N*/   MySerial = ++nSerial;       // nur in der nicht PRODUCT-Version
/*N*/ #endif
/*N*/ IDX_CHK_ARRAY
/*N*/ }


/*N*/ SwIndex& SwIndex::ChgValue( const SwIndex& rIdx, xub_StrLen nNewValue )
/*N*/ {
/*N*/   register SwIndex* pFnd = (SwIndex*)&rIdx;
/*N*/   if( rIdx.nIndex > nNewValue )               // nach vorne versuchen
/*N*/   {
/*N*/       register SwIndex* pPrv;
/*N*/       while( 0 != ( pPrv = pFnd->pPrev ) && pPrv->nIndex > nNewValue )
/*N*/           pFnd = pPrv;
/*N*/
/*N*/       if( pFnd != this )
/*N*/       {
/*N*/           // an alter Position ausketten
/*N*/           // erstmal an alter Position ausketten
/*N*/           if( pPrev )
/*N*/               pPrev->pNext = pNext;
/*N*/           else if( pArray->pFirst == this )
/*?*/               pArray->pFirst = pNext;
/*N*/
/*N*/           if( pNext )
/*N*/               pNext->pPrev = pPrev;
/*N*/           else if( pArray->pLast == this )
/*N*/               pArray->pLast = pPrev;
/*N*/
/*N*/           pNext = pFnd;
/*N*/           pPrev = pFnd->pPrev;
/*N*/           if( pPrev )
/*N*/               pPrev->pNext = this;
/*N*/           else
/*N*/               pArray->pFirst = this;
/*N*/           pFnd->pPrev = this;
/*N*/       }
/*N*/   }
/*N*/   else if( rIdx.nIndex < nNewValue )
/*N*/   {
/*N*/       register SwIndex* pNxt;
/*N*/       while( 0 != ( pNxt = pFnd->pNext ) && pNxt->nIndex < nNewValue )
/*N*/           pFnd = pNxt;
/*N*/
/*N*/       if( pFnd != this )
/*N*/       {
/*N*/           // erstmal an alter Position ausketten
/*N*/           if( pPrev )
/*N*/               pPrev->pNext = pNext;
/*N*/           else if( pArray->pFirst == this )
/*N*/               pArray->pFirst = pNext;
/*N*/
/*N*/           if( pNext )
/*N*/               pNext->pPrev = pPrev;
/*N*/           else if( pArray->pLast == this )
/*?*/               pArray->pLast = pPrev;
/*N*/
/*N*/           pPrev = pFnd;
/*N*/           pNext = pFnd->pNext;
/*N*/           if( pNext )
/*N*/               pNext->pPrev = this;
/*N*/           else
/*N*/               pArray->pLast = this;
/*N*/           pFnd->pNext = this;
/*N*/       }
/*N*/   }
/*N*/   else if( pFnd != this )
/*N*/   {
/*N*/       // erstmal an alter Position ausketten
/*N*/       if( pPrev )
/*N*/           pPrev->pNext = pNext;
/*N*/       else if( pArray->pFirst == this )
/*N*/           pArray->pFirst = pNext;
/*N*/
/*N*/       if( pNext )
/*N*/           pNext->pPrev = pPrev;
/*N*/       else if( pArray->pLast == this )
/*N*/           pArray->pLast = pPrev;
/*N*/
/*N*/       pPrev = (SwIndex*)&rIdx;
/*N*/       pNext = rIdx.pNext;
/*N*/       pPrev->pNext = this;
/*N*/
/*N*/       if( !pNext )            // im IndexArray als letzes
/*N*/           pArray->pLast = this;
/*N*/       else
/*N*/           pNext->pPrev = this;
/*N*/   }
/*N*/   pArray = rIdx.pArray;
/*N*/
/*N*/   if( pArray->pFirst == pNext )
/*?*/       pArray->pFirst = this;
/*N*/   if( pArray->pLast == pPrev )
/*?*/       pArray->pLast = this;
/*N*/
/*N*/   nIndex = nNewValue;
/*N*/
/*N*/ IDX_CHK_ARRAY
/*N*/
/*N*/   return *this; }


/*N*/ void SwIndex::Remove()
/*N*/ {
/*N*/   if( !pPrev )
/*N*/       pArray->pFirst = pNext;
/*N*/   else
/*N*/       pPrev->pNext = pNext;
/*N*/
/*N*/   if( !pNext )
/*N*/       pArray->pLast = pPrev;
/*N*/   else
/*N*/       pNext->pPrev = pPrev;
/*N*/
/*N*/   if( this == pArray->pMiddle )   pArray->pMiddle = pPrev;
/*N*/ IDX_CHK_ARRAY
/*N*/ }

/*************************************************************************
|*
|*    SwIndex & SwIndex::operator=( const SwIndex & aSwIndex )
|*
|*    Beschreibung
|*    Ersterstellung    JP 07.11.90
|*    Letzte Aenderung  JP 07.03.94
|*
*************************************************************************/


/*N*/ SwIndex& SwIndex::operator=( const SwIndex& rIdx )
/*N*/ {
/*N*/   int bEqual;
/*N*/   if( rIdx.pArray != pArray )         // im alten abmelden !!
/*N*/   {
/*N*/       Remove();
/*N*/       pArray = rIdx.pArray;
/*N*/       pNext = pPrev = 0;
/*N*/       bEqual = FALSE;
/*N*/   }
/*N*/   else
/*N*/       bEqual = rIdx.nIndex == nIndex;
/*N*/
/*N*/   if( !bEqual )
/*N*/       ChgValue( rIdx, rIdx.nIndex );
/*N*/   return *this;
/*N*/ }

/*************************************************************************
|*
|*    SwIndex &SwIndex::Assign
|*
|*    Beschreibung
|*    Ersterstellung    VB 25.03.91
|*    Letzte Aenderung  JP 07.03.94
|*
*************************************************************************/


/*N*/ SwIndex& SwIndex::Assign( SwIndexReg* pArr, xub_StrLen nIdx )
/*N*/ {
/*N*/   if( !pArr )
/*N*/   {
/*N*/       pArr = SwIndexReg::pEmptyIndexArray;
/*N*/       nIdx = 0;       // steht immer auf 0 !!!
/*N*/   }
/*N*/
/*N*/   if( pArr != pArray )            // im alten abmelden !!
/*N*/   {
/*N*/       Remove();
/*N*/       pArray = pArr;
/*N*/       pNext = pPrev = 0;
/*N*/       if( !pArr->pFirst )         // 1. Index ??
/*N*/       {
/*N*/           pArr->pFirst = pArr->pLast = this;
/*N*/           nIndex = nIdx;
/*N*/       }
/*N*/       else if( pArray->pMiddle )
/*N*/       {
/*?*/           if( pArray->pMiddle->nIndex <= nIdx )
/*?*/           {
/*?*/               if( nIdx > ((pArr->pLast->nIndex - pArr->pMiddle->nIndex) / 2) )
/*?*/                   ChgValue( *pArr->pLast, nIdx );
/*?*/               else
/*?*/                   ChgValue( *pArr->pMiddle, nIdx );
/*?*/           }
/*?*/           else if( nIdx > ((pArr->pMiddle->nIndex - pArr->pFirst->nIndex) / 2) )
/*?*/               ChgValue( *pArr->pMiddle, nIdx );
/*?*/           else
/*?*/               ChgValue( *pArr->pFirst, nIdx );
/*N*/       }
/*N*/       else if( nIdx > ((pArr->pLast->nIndex - pArr->pFirst->nIndex) / 2) )
/*N*/           ChgValue( *pArr->pLast, nIdx );
/*N*/       else
/*N*/           ChgValue( *pArr->pFirst, nIdx );
/*N*/   }
/*N*/   else if( nIndex != nIdx )
/*N*/       ChgValue( *this, nIdx );
/*N*/ IDX_CHK_ARRAY
/*N*/   return *this;
/*N*/ }


/*N*/ SwIndexReg::SwIndexReg()
/*N*/   : pFirst( 0 ), pLast( 0 ), pMiddle( 0 )
/*N*/ {
/*N*/ }

#ifndef PRODUCT


/*N*/ SwIndexReg::~SwIndexReg()
/*N*/ {
/*N*/   ASSERT( !pFirst || !pLast, "Es sind noch Indizies angemeldet" );
/*N*/ }

#endif


/*N*/ void SwIndexReg::Update( const SwIndex& rIdx, xub_StrLen nDiff, BOOL bNeg )
/*N*/ {
/*N*/   register SwIndex* pStt = (SwIndex*)&rIdx;
/*N*/   register xub_StrLen nNewVal = rIdx.nIndex;
/*N*/   if( bNeg )
/*N*/   {
/*N*/       register xub_StrLen nLast = rIdx.GetIndex() + nDiff;
/*N*/       while( pStt && pStt->nIndex == nNewVal )
/*N*/       {
/*N*/           pStt->nIndex = nNewVal;
/*N*/           pStt = pStt->pPrev;
/*N*/       }
/*N*/       pStt = rIdx.pNext;
/*N*/       while( pStt && pStt->nIndex >= nNewVal &&
/*N*/               pStt->nIndex <= nLast )
/*N*/       {
/*N*/           pStt->nIndex = nNewVal;
/*N*/           pStt = pStt->pNext;
/*N*/       }
/*N*/       while( pStt )
/*N*/       {
/*?*/           pStt->nIndex -= nDiff;
/*?*/           pStt = pStt->pNext;
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       while( pStt && pStt->nIndex == nNewVal )
/*N*/       {
/*N*/           pStt->nIndex += nDiff;
/*N*/           pStt = pStt->pPrev;
/*N*/       }
/*N*/       pStt = rIdx.pNext;
/*N*/       while( pStt )
/*N*/       {
/*N*/           pStt->nIndex += nDiff;
/*N*/           pStt = pStt->pNext;
/*N*/       }
/*N*/   }
/*N*/ ARR_CHK_ARRAY
/*N*/ }


/*************************************************************************
|*
|*    SwIndex::operator++()
|*
|*    Beschreibung
|*    Ersterstellung    JP 07.11.90
|*    Letzte Aenderung  JP 07.03.94
|*
*************************************************************************/

#ifndef PRODUCT

#ifndef CFRONT


//STRIP001 xub_StrLen SwIndex::operator++(int)
//STRIP001 {
//STRIP001  ASSERT_ID( nIndex < INVALID_INDEX, ERR_OUTOFSCOPE );
//STRIP001
//STRIP001  xub_StrLen nOldIndex = nIndex;
//STRIP001  ChgValue( *this, nIndex+1 );
//STRIP001  return nOldIndex;
//STRIP001 }

#endif


//STRIP001 xub_StrLen SwIndex::operator++()
//STRIP001 {
//STRIP001  ASSERT_ID( nIndex < INVALID_INDEX, ERR_OUTOFSCOPE );
//STRIP001
//STRIP001  ChgValue( *this, nIndex+1 );
//STRIP001  return nIndex;
//STRIP001 }

/*************************************************************************
|*
|*    SwIndex::operator--()
|*
|*    Beschreibung
|*    Ersterstellung    JP 07.11.90
|*    Letzte Aenderung  JP 07.03.94
|*
*************************************************************************/

#ifndef CFRONT


/*N*/ xub_StrLen SwIndex::operator--(int)
/*N*/ {
/*N*/   ASSERT_ID( nIndex, ERR_OUTOFSCOPE );
/*N*/
/*N*/   xub_StrLen nOldIndex = nIndex;
/*N*/   ChgValue( *this, nIndex-1 );
/*N*/   return nOldIndex;
/*N*/ }

#endif


//STRIP001 xub_StrLen SwIndex::operator--()
//STRIP001 {
//STRIP001  ASSERT_ID( nIndex, ERR_OUTOFSCOPE );
//STRIP001  return ChgValue( *this, nIndex-1 ).nIndex;
//STRIP001 }

/*************************************************************************
|*
|*    SwIndex::operator+=( xub_StrLen )
|*
|*    Beschreibung
|*    Ersterstellung    JP 07.11.90
|*    Letzte Aenderung  JP 07.03.94
|*
*************************************************************************/


/*N*/ xub_StrLen SwIndex::operator+=( xub_StrLen nWert )
/*N*/ {
/*N*/   ASSERT_ID( nIndex < INVALID_INDEX - nWert, ERR_OUTOFSCOPE);
/*N*/   return ChgValue( *this, nIndex + nWert ).nIndex;
/*N*/ }

/*************************************************************************
|*
|*    SwIndex::operator-=( xub_StrLen )
|*
|*    Beschreibung
|*    Ersterstellung    JP 07.11.90
|*    Letzte Aenderung  JP 07.03.94
|*
*************************************************************************/


//STRIP001 xub_StrLen SwIndex::operator-=( xub_StrLen nWert )
//STRIP001 {
//STRIP001  ASSERT_ID( nIndex >= nWert, ERR_OUTOFSCOPE );
//STRIP001  return ChgValue( *this, nIndex - nWert ).nIndex;
//STRIP001 }

/*************************************************************************
|*
|*    SwIndex::operator+=( const SwIndex & )
|*
|*    Beschreibung
|*    Ersterstellung    JP 07.11.90
|*    Letzte Aenderung  JP 07.03.94
|*
*************************************************************************/


/*N*/ xub_StrLen SwIndex::operator+=( const SwIndex & rIndex )
/*N*/ {
/*N*/   ASSERT_ID( nIndex < INVALID_INDEX - rIndex.nIndex, ERR_OUTOFSCOPE );
/*N*/   return ChgValue( *this, nIndex + rIndex.nIndex ).nIndex;
/*N*/ }


/*************************************************************************
|*
|*    SwIndex::operator-=( const SwIndex & )
|*
|*    Beschreibung
|*    Ersterstellung    JP 07.11.90
|*    Letzte Aenderung  JP 07.03.94
|*
*************************************************************************/


//STRIP001 xub_StrLen SwIndex::operator-=( const SwIndex & rIndex )
//STRIP001 {
//STRIP001  ASSERT_ID( nIndex >= rIndex.nIndex, ERR_OUTOFSCOPE );
//STRIP001  return ChgValue( *this, nIndex - rIndex.nIndex ).nIndex;
//STRIP001 }


/*************************************************************************
|*
|*    SwIndex::operator<( const SwIndex & )
|*
|*    Beschreibung
|*    Ersterstellung    JP 07.11.90
|*    Letzte Aenderung  JP 07.03.94
|*
*************************************************************************/


/*N*/ BOOL SwIndex::operator<( const SwIndex & rIndex ) const
/*N*/ {
/*N*/   ASSERT( pArray == rIndex.pArray, "Attempt to compare indices into different arrays.");
/*N*/   return nIndex < rIndex.nIndex;
/*N*/ }

/*************************************************************************
|*
|*    SwIndex::operator<=( const SwIndex & )
|*
|*    Beschreibung
|*    Ersterstellung    JP 07.11.90
|*    Letzte Aenderung  JP 04.06.92
|*
*************************************************************************/


/*N*/ BOOL SwIndex::operator<=( const SwIndex & rIndex ) const
/*N*/ {
/*N*/   ASSERT( pArray == rIndex.pArray, "Attempt to compare indices into different arrays.");
/*N*/   return nIndex <= rIndex.nIndex;
/*N*/ }

/*************************************************************************
|*
|*    SwIndex::operator>( const SwIndex & )
|*
|*    Beschreibung
|*    Ersterstellung    JP 07.11.90
|*    Letzte Aenderung  JP 04.06.92
|*
*************************************************************************/


/*N*/ BOOL SwIndex::operator>( const SwIndex & rIndex ) const
/*N*/ {
/*N*/   ASSERT( pArray == rIndex.pArray, "Attempt to compare indices into different arrays.");
/*N*/   return nIndex > rIndex.nIndex;
/*N*/ }

/*************************************************************************
|*
|*    SwIndex::operator>=( const SwIndex & )
|*
|*    Beschreibung
|*    Ersterstellung    JP 07.11.90
|*    Letzte Aenderung  JP 04.06.92
|*
*************************************************************************/


/*N*/ BOOL SwIndex::operator>=( const SwIndex & rIndex ) const
/*N*/ {
/*N*/   ASSERT( pArray == rIndex.pArray, "Attempt to compare indices into different arrays.");
/*N*/   return nIndex >= rIndex.nIndex;
/*N*/ }

#endif

/*************************************************************************
|*
|*    SwIndex & SwIndex::operator=( xub_StrLen )
|*
|*    Beschreibung
|*    Ersterstellung    JP 10.12.90
|*    Letzte Aenderung  JP 07.03.94
|*
*************************************************************************/

#ifndef PRODUCT


/*N*/ SwIndex& SwIndex::operator=( xub_StrLen nWert )
/*N*/ {
/*N*/   // Werte kopieren und im neuen Array anmelden
/*N*/   if( nIndex != nWert )
/*N*/       ChgValue( *this, nWert );
/*N*/
/*N*/   return *this;
/*N*/ }

#endif



//STRIP001 void SwIndexReg::MoveIdx( const SwIndex& rOldPos, const SwIndex& rNewPos )
//STRIP001 {
//STRIP001  ASSERT( rOldPos.pArray == rNewPos.pArray,
//STRIP001          "stehen in unterschiedlichen Arrays" );
//STRIP001
//STRIP001  SwIndex* pStt = (SwIndex*)&rOldPos, *pEnd = pStt;
//STRIP001  SwIndex* pInsPos = (SwIndex*)&rNewPos;
//STRIP001  xub_StrLen nOldIndex = rOldPos.nIndex,
//STRIP001          nNewIndex = rNewPos.nIndex;
//STRIP001
//STRIP001  if( nOldIndex == nNewIndex )
//STRIP001      return;
//STRIP001
//STRIP001  while( pInsPos->pPrev && pInsPos->pPrev->nIndex == nNewIndex )
//STRIP001      pInsPos = pInsPos->pPrev;
//STRIP001
//STRIP001  if( nNewIndex > nOldIndex )
//STRIP001      --nNewIndex;
//STRIP001
//STRIP001  while( pStt->pPrev && pStt->pPrev->nIndex == nOldIndex )
//STRIP001  {
//STRIP001      pStt = pStt->pPrev;
//STRIP001      pStt->nIndex = nNewIndex;
//STRIP001  }
//STRIP001  while( pEnd->pNext && pEnd->pNext->nIndex == nOldIndex )
//STRIP001  {
//STRIP001      pEnd = pEnd->pNext;
//STRIP001      pEnd->nIndex = nNewIndex;
//STRIP001  }
//STRIP001
//STRIP001  {
//STRIP001      for( SwIndex* pTmp = pStt; pTmp != pEnd; pTmp = pTmp->pNext )
//STRIP001          pTmp->nIndex = nNewIndex;
//STRIP001      pTmp->nIndex = nNewIndex;
//STRIP001  }
//STRIP001
//STRIP001  // Ausketten
//STRIP001  if( !pStt->pPrev )
//STRIP001  {
//STRIP001      pFirst = pEnd->pNext;
//STRIP001      pEnd->pNext->pPrev = 0;
//STRIP001  }
//STRIP001  else
//STRIP001      pStt->pPrev->pNext = pEnd->pNext;
//STRIP001
//STRIP001  if( !pEnd->pNext )
//STRIP001  {
//STRIP001      pLast = pStt->pPrev;
//STRIP001      pStt->pPrev->pNext = 0;
//STRIP001  }
//STRIP001  else
//STRIP001      pEnd->pNext->pPrev = pStt->pPrev;
//STRIP001
//STRIP001  // wieder einketten
//STRIP001  pStt->pPrev = pInsPos->pPrev;
//STRIP001  pEnd->pNext = pInsPos;
//STRIP001
//STRIP001  if( pInsPos->pPrev )
//STRIP001      pInsPos->pPrev->pNext = pStt;
//STRIP001  pInsPos->pPrev = pEnd;
//STRIP001
//STRIP001  if( pInsPos == pFirst )
//STRIP001      pFirst = pStt;
//STRIP001
//STRIP001  if( nNewIndex < nOldIndex )     // es wurde nach vorne verschoben
//STRIP001  {
//STRIP001      while( pInsPos && pInsPos->nIndex <= nOldIndex )
//STRIP001      {
//STRIP001          ++pInsPos->nIndex;
//STRIP001          pInsPos = pInsPos->pNext;
//STRIP001      }
//STRIP001  }
//STRIP001  else                            // es wurde nach hinten verschoben
//STRIP001  {
//STRIP001      while( pStt->pPrev && pStt->pPrev->nIndex > nOldIndex )
//STRIP001      {
//STRIP001          pStt = pStt->pPrev;
//STRIP001          --pStt->nIndex;
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*N*/ void SwIndexReg::MoveTo( SwIndexReg& rArr )
/*N*/ {
/*N*/   if( this != &rArr && pFirst )
/*N*/   {
/*N*/       SwIndex* pIdx = (SwIndex*)pFirst, *pNext;
/*N*/       while( pIdx )
/*N*/       {
/*N*/           pNext = pIdx->pNext;
/*N*/           pIdx->Assign( &rArr, pIdx->GetIndex() );
/*N*/           pIdx = pNext;
/*N*/       }
/*N*/       pFirst = 0, pLast = 0, pMiddle = 0;
/*N*/   }
/*N*/ }




