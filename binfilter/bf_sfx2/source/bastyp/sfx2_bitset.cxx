/*************************************************************************
 *
 *  $RCSfile: sfx2_bitset.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:08 $
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

#ifndef _TOOLS_DEBUG_HXX //autogen
#include <tools/debug.hxx>
#endif
#pragma hdrstop

#include "bitset.hxx"

#include <string.h>     // memset(), memcpy()
#include <limits.h>     // USHRT_MAX

//====================================================================
// add nOffset to each bit-value in the set

/*N*/ BitSet BitSet::operator<<( USHORT nOffset ) const
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/   // create a work-copy, return it if nothing to shift
/*N*/   BitSet aSet(*this);
/*N*/   if ( nOffset == 0 )
/*N*/       return aSet;
/*N*/
/*N*/   // compute the shiftment in long-words and bits
/*N*/   USHORT nBlockDiff = nOffset / 32;
/*N*/   ULONG nBitValDiff = nOffset % 32;
/*N*/
/*N*/   // compute the new number of bits
/*N*/   for ( USHORT nBlock = 0; nBlock < nBlockDiff; ++nBlock )
/*?*/       aSet.nCount -= CountBits( *(aSet.pBitmap+nBlock) );
/*N*/   aSet.nCount -= CountBits( *(aSet.pBitmap+nBlockDiff) >> (32-nBitValDiff) );
/*N*/
/*N*/   // shift complete long-words
/*N*/   USHORT nTarget, nSource;
/*N*/   for ( nTarget = 0, nSource = nBlockDiff;
/*N*/         (nSource+1) < aSet.nBlocks;
/*N*/         ++nTarget, ++nSource )
/*N*/       *(aSet.pBitmap+nTarget) =
/*N*/           ( *(aSet.pBitmap+nSource) << nBitValDiff ) |
/*N*/           ( *(aSet.pBitmap+nSource+1) >> (32-nBitValDiff) );
/*N*/
/*N*/   // shift the remainder (if in total minor 32 bits, only this)
/*N*/   *(aSet.pBitmap+nTarget) = *(aSet.pBitmap+nSource) << nBitValDiff;
/*N*/
/*N*/   // determine the last used block
/*N*/   while ( *(aSet.pBitmap+nTarget) == 0 )
/*N*/       --nTarget;
/*N*/
/*N*/   // shorten the block-array
/*N*/   if ( nTarget < aSet.nBlocks )
/*N*/   {
/*N*/       ULONG* pNewMap = new ULONG[nTarget];
/*N*/       memcpy( pNewMap, aSet.pBitmap, 4 * nTarget );
/*N*/         delete [] aSet.pBitmap;
/*N*/       aSet.pBitmap = pNewMap;
/*N*/       aSet.nBlocks = nTarget;
/*N*/   }
/*N*/
/*N*/   return aSet;
/*N*/ }

//--------------------------------------------------------------------

// substracts nOffset from each bit-value in the set

//STRIP001 BitSet BitSet::operator>>( USHORT nOffset ) const
//STRIP001 {
//STRIP001  DBG_MEMTEST();
//STRIP001  return BitSet();
//STRIP001 }

//--------------------------------------------------------------------

// internal code for operator= and copy-ctor

/*N*/ void BitSet::CopyFrom( const BitSet& rSet )
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/   nCount = rSet.nCount;
/*N*/   nBlocks = rSet.nBlocks;
/*N*/   if ( rSet.nBlocks )
/*N*/   {
/*N*/       DBG_MEMTEST();
/*N*/       pBitmap = new ULONG[nBlocks];
/*N*/       memcpy( pBitmap, rSet.pBitmap, 4 * nBlocks );
/*N*/   }
/*N*/   else
/*N*/       pBitmap = 0;
/*N*/ }

//--------------------------------------------------------------------

// creates an empty bitset

/*N*/ BitSet::BitSet()
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/   nCount = 0;
/*N*/   nBlocks = 0;
/*N*/   pBitmap = 0;
/*N*/ }

//--------------------------------------------------------------------

// creates a copy of bitset rOrig

/*N*/ BitSet::BitSet( const BitSet& rOrig )
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/   CopyFrom(rOrig);
/*N*/ }

//--------------------------------------------------------------------

// creates a bitset from an array

//STRIP001 BitSet::BitSet( USHORT* pArray, USHORT nSize ):
//STRIP001  nCount(0)
//STRIP001 {
//STRIP001  DBG_MEMTEST();
//STRIP001  // find the highest bit to set
//STRIP001  USHORT nMax = 0;
//STRIP001  for ( USHORT n = 0; n < nCount; ++n )
//STRIP001      if ( pArray[n] > nMax )
//STRIP001          nMax = pArray[n];
//STRIP001
//STRIP001  // if there are bits at all
//STRIP001  if ( nMax > 0 )
//STRIP001  {
//STRIP001      // allocate memory for all blocks needed
//STRIP001      nBlocks = nMax / 32 + 1;
//STRIP001      pBitmap = new ULONG[nBlocks];
//STRIP001      memset( pBitmap, 0, 4 * nBlocks );
//STRIP001
//STRIP001      // set all the bits
//STRIP001      for ( USHORT n = 0; n < nCount; ++n )
//STRIP001      {
//STRIP001          // compute the block no. and bitvalue
//STRIP001          USHORT nBlock = n / 32;
//STRIP001          ULONG nBitVal = 1L << (n % 32);
//STRIP001
//STRIP001          // set a single bit
//STRIP001          if ( ( *(pBitmap+nBlock) & nBitVal ) == 0 )
//STRIP001          {
//STRIP001              *(pBitmap+nBlock) |= nBitVal;
//STRIP001              ++nCount;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // initalize emtpy set
//STRIP001      nBlocks = 0;
//STRIP001      pBitmap = 0;
//STRIP001  }
//STRIP001 }

//--------------------------------------------------------------------

// frees the storage

/*N*/ BitSet::~BitSet()
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/     delete [] pBitmap;
/*N*/ }

//--------------------------------------------------------------------

// creates a bitmap with all bits in rRange set

//STRIP001 BitSet::BitSet( const Range& rRange )
//STRIP001 {
//STRIP001  DBG_MEMTEST();
//STRIP001
//STRIP001 }

//--------------------------------------------------------------------

// assignment from another bitset

//STRIP001 BitSet& BitSet::operator=( const BitSet& rOrig )
//STRIP001 {
//STRIP001  DBG_MEMTEST();
//STRIP001  if ( this != &rOrig )
//STRIP001  {
//STRIP001         delete [] pBitmap;
//STRIP001      CopyFrom(rOrig);
//STRIP001  }
//STRIP001  return *this;
//STRIP001 }

//--------------------------------------------------------------------

// assignment from a single bit

//STRIP001 BitSet& BitSet::operator=( USHORT nBit )
//STRIP001 {
//STRIP001  DBG_MEMTEST();
//STRIP001     delete [] pBitmap;
//STRIP001
//STRIP001  USHORT nBlocks = nBit / 32;
//STRIP001  ULONG nBitVal = 1L << (nBit % 32);
//STRIP001  nCount = 1;
//STRIP001
//STRIP001  ULONG *pBitmap = new ULONG[nBlocks];
//STRIP001  memset( pBitmap + nBlocks, 0, 4 * nBlocks );
//STRIP001
//STRIP001  *(pBitmap+nBlocks) = nBitVal;
//STRIP001
//STRIP001  return *this;
//STRIP001 }

//--------------------------------------------------------------------

// creates the asymetric difference with another bitset

/*N*/ BitSet& BitSet::operator-=(USHORT nBit)
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/   USHORT nBlock = nBit / 32;
/*N*/   ULONG nBitVal = 1L << (nBit % 32);
/*N*/
/*N*/   if ( nBlock >= nBlocks )
/*N*/     return *this;
/*N*/
/*N*/   if ( (*(pBitmap+nBlock) & nBitVal) )
/*N*/   {
/*N*/       *(pBitmap+nBlock) &= ~nBitVal;
/*N*/       --nCount;
/*N*/   }
/*N*/
/*N*/   return *this;
/*N*/ }

//--------------------------------------------------------------------

// unites with the bits of rSet

/*N*/ BitSet& BitSet::operator|=( const BitSet& rSet )
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/   USHORT nMax = Min(nBlocks, rSet.nBlocks);
/*N*/
/*N*/   // expand the bitmap
/*N*/   if ( nBlocks < rSet.nBlocks )
/*N*/   {
/*N*/       ULONG *pNewMap = new ULONG[rSet.nBlocks];
/*N*/       memset( pNewMap + nBlocks, 0, 4 * (rSet.nBlocks - nBlocks) );
/*N*/
/*N*/       if ( pBitmap )
/*N*/       {
/*?*/           memcpy( pNewMap, pBitmap, 4 * nBlocks );
/*?*/             delete [] pBitmap;
/*N*/       }
/*N*/       pBitmap = pNewMap;
/*N*/       nBlocks = rSet.nBlocks;
/*N*/   }
/*N*/
/*N*/   // add the bits blocks by block
/*N*/   for ( USHORT nBlock = 0; nBlock < nMax; ++nBlock )
/*N*/   {
/*N*/       // compute numberof additional bits
/*?*/       ULONG nDiff = ~*(pBitmap+nBlock) & *(rSet.pBitmap+nBlock);
/*?*/       nCount += CountBits(nDiff);
/*?*/
/*?*/       *(pBitmap+nBlock) |= *(rSet.pBitmap+nBlock);
/*N*/   }
/*N*/
/*N*/   return *this;
/*N*/ }

//--------------------------------------------------------------------

// unites with a single bit

/*N*/ BitSet& BitSet::operator|=( USHORT nBit )
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/   USHORT nBlock = nBit / 32;
/*N*/   ULONG nBitVal = 1L << (nBit % 32);
/*N*/
/*N*/   if ( nBlock >= nBlocks )
/*N*/   {
/*N*/       ULONG *pNewMap = new ULONG[nBlock+1];
/*N*/       memset( pNewMap + nBlocks, 0, 4 * (nBlock - nBlocks + 1) );
/*N*/
/*N*/       if ( pBitmap )
/*N*/       {
/*N*/           memcpy( pNewMap, pBitmap, 4 * nBlocks );
/*N*/             delete [] pBitmap;
/*N*/       }
/*N*/       pBitmap = pNewMap;
/*N*/       nBlocks = nBlock+1;
/*N*/   }
/*N*/
/*N*/   if ( (*(pBitmap+nBlock) & nBitVal) == 0 )
/*N*/   {
/*N*/       *(pBitmap+nBlock) |= nBitVal;
/*N*/       ++nCount;
/*N*/   }
/*N*/
/*N*/   return *this;
/*N*/ }

//--------------------------------------------------------------------

// determines if the bit is set (may be the only one)

/*N*/ BOOL BitSet::Contains( USHORT nBit ) const
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/   USHORT nBlock = nBit / 32;
/*N*/   ULONG nBitVal = 1L << (nBit % 32);
/*N*/
/*N*/   if ( nBlock >= nBlocks )
/*N*/       return FALSE;
/*N*/   return ( nBitVal & *(pBitmap+nBlock) ) == nBitVal;
/*N*/ }

//--------------------------------------------------------------------

// determines if the bitsets are equal

//STRIP001 BOOL BitSet::operator==( const BitSet& rSet ) const
//STRIP001 {
//STRIP001  DBG_MEMTEST();
//STRIP001  if ( nBlocks != rSet.nBlocks )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  USHORT nBlock = nBlocks;
//STRIP001  while ( nBlock-- > 0 )
//STRIP001      if ( *(pBitmap+nBlock) != *(rSet.pBitmap+nBlock) )
//STRIP001          return FALSE;
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }

//--------------------------------------------------------------------

// counts the number of 1-bits in the parameter

/*N*/ USHORT BitSet::CountBits( ULONG nBits )
/*N*/ {
/*N*/   USHORT nCount = 0;
/*N*/   int nBit = 32;
/*N*/   while ( nBit-- && nBits )
/*?*/   {   if ( ( (long)nBits ) < 0 )
/*?*/           ++nCount;
/*?*/       nBits = nBits << 1;
/*N*/   }
/*N*/   return nCount;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ USHORT IndexBitSet::GetFreeIndex()
/*N*/ {
/*N*/   for(USHORT i=0;i<USHRT_MAX;i++)
/*N*/   if(!Contains(i))
/*N*/     {
/*N*/       *this|=i;
/*N*/       return i;
/*N*/     }
/*N*/   DBG_ASSERT(FALSE, "IndexBitSet enthaelt mehr als USHRT_MAX Eintraege");
/*N*/   return 0;
/*N*/ }


