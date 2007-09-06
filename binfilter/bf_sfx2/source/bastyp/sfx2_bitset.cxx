/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_bitset.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:25:54 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#ifndef _TOOLS_DEBUG_HXX //autogen
#include <tools/debug.hxx>
#endif
#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "bitset.hxx"

#include <string.h>     // memset(), memcpy()
#include <limits.h>     // USHRT_MAX
namespace binfilter {

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


//--------------------------------------------------------------------

// frees the storage

/*N*/ BitSet::~BitSet()
/*N*/ {
/*N*/   DBG_MEMTEST();
/*N*/     delete [] pBitmap;
/*N*/ }

//--------------------------------------------------------------------

// creates a bitmap with all bits in rRange set


//--------------------------------------------------------------------

// assignment from another bitset


//--------------------------------------------------------------------

// assignment from a single bit


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


}
