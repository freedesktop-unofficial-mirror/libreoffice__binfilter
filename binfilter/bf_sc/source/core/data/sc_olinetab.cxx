/*************************************************************************
 *
 *  $RCSfile: sc_olinetab.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:39:31 $
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

// System - Includes -----------------------------------------------------

#ifdef PCH
#include "core_pch.hxx"
#endif

#pragma hdrstop

#include <tools/debug.hxx>
#include <limits.h>

// INCLUDE ---------------------------------------------------------------

#include "olinetab.hxx"
#include "global.hxx"
#include "rechead.hxx"
namespace binfilter {

//------------------------------------------------------------------------

/*N*/ ScOutlineEntry::ScOutlineEntry( USHORT nNewStart, USHORT nNewSize, BOOL bNewHidden ) :
/*N*/   nStart  ( nNewStart ),
/*N*/   nSize   ( nNewSize ),
/*N*/   bHidden ( bNewHidden ),
/*N*/   bVisible( TRUE )
/*N*/ {
/*N*/ }

/*N*/ ScOutlineEntry::ScOutlineEntry( const ScOutlineEntry& rEntry ) :
/*N*/   nStart  ( rEntry.nStart ),
/*N*/   nSize   ( rEntry.nSize ),
/*N*/   bHidden ( rEntry.bHidden ),
/*N*/   bVisible( rEntry.bVisible )
/*N*/ {
/*N*/ }

/*N*/ ScOutlineEntry::ScOutlineEntry( SvStream& rStream, ScMultipleReadHeader& rHdr )
/*N*/ {
/*N*/   rHdr.StartEntry();
/*N*/
/*N*/   rStream >> nStart;
/*N*/   rStream >> nSize;
/*N*/   rStream >> bHidden;
/*N*/   rStream >> bVisible;
/*N*/
/*N*/   rHdr.EndEntry();
/*N*/ }

/*N*/ void ScOutlineEntry::Store( SvStream& rStream, ScMultipleWriteHeader& rHdr )
/*N*/ {
/*N*/   rHdr.StartEntry();
/*N*/
/*N*/   rStream << nStart;
/*N*/   rStream << nSize;
/*N*/   rStream << bHidden;
/*N*/   rStream << bVisible;
/*N*/
/*N*/   rHdr.EndEntry();
/*N*/ }

/*N*/ DataObject* ScOutlineEntry::Clone() const
/*N*/ {
/*N*/   return new ScOutlineEntry( *this );
/*N*/ }

/*N*/ void ScOutlineEntry::Move( short nDelta )
/*N*/ {
/*N*/   short nNewPos = ((short) nStart) + nDelta;
/*N*/   if (nNewPos<0)
/*N*/   {
/*N*/       DBG_ERROR("OutlineEntry < 0");
/*N*/       nNewPos = 0;
/*N*/   }
/*N*/   nStart = (USHORT) nNewPos;
/*N*/ }

/*N*/ void ScOutlineEntry::SetSize( USHORT nNewSize )
/*N*/ {
/*N*/   if (nNewSize)
/*N*/       nSize = nNewSize;
/*N*/   else
/*N*/       DBG_ERROR("ScOutlineEntry Size == 0");
/*N*/ }

/*N*/ void ScOutlineEntry::SetPosSize( USHORT nNewPos, USHORT nNewSize )
/*N*/ {
/*N*/   nStart = nNewPos;
/*N*/   SetSize( nNewSize );
/*N*/ }
/*N*/
/*N*/ void ScOutlineEntry::SetHidden( BOOL bNewHidden )
/*N*/ {
/*N*/   bHidden = bNewHidden;
/*N*/ }

/*N*/ void ScOutlineEntry::SetVisible( BOOL bNewVisible )
/*N*/ {
/*N*/   bVisible = bNewVisible;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScOutlineCollection::ScOutlineCollection() :
/*N*/   SortedCollection( 4,4,FALSE )
/*N*/ {
/*N*/ }

/*N*/ inline short IntCompare( USHORT nX, USHORT nY )
/*N*/ {
/*N*/   if ( nX==nY ) return 0;
/*N*/   else if ( nX<nY ) return -1;
/*N*/   else return 1;
/*N*/ }

/*N*/ short ScOutlineCollection::Compare(DataObject* pKey1, DataObject* pKey2) const
/*N*/ {
/*N*/   return IntCompare( ((ScOutlineEntry*)pKey1)->GetStart(),
/*N*/                       ((ScOutlineEntry*)pKey2)->GetStart() );
/*N*/ }
/*N*/
//STRIP001 USHORT ScOutlineCollection::FindStart( USHORT nMinStart )
//STRIP001 {
//STRIP001  //!                 binaer suchen ?
//STRIP001
//STRIP001  USHORT nPos = 0;
//STRIP001  USHORT nCount = GetCount();
//STRIP001  while ( (nPos<nCount) ? (((ScOutlineEntry*)At(nPos))->GetStart() < nMinStart) : FALSE )
//STRIP001      ++nPos;
//STRIP001
//STRIP001  return nPos;
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ ScOutlineArray::ScOutlineArray() :
/*N*/   nDepth( 0 )
/*N*/ {
/*N*/ }

/*N*/ ScOutlineArray::ScOutlineArray( const ScOutlineArray& rArray ) :
/*N*/   nDepth( rArray.nDepth )
/*N*/ {
/*N*/   for (USHORT nLevel=0; nLevel<nDepth; nLevel++)
/*N*/   {
/*N*/       USHORT nCount = rArray.aCollections[nLevel].GetCount();
/*N*/       for (USHORT nEntry=0; nEntry<nCount; nEntry++)
/*N*/       {
/*N*/           ScOutlineEntry* pEntry = (ScOutlineEntry*) rArray.aCollections[nLevel].At(nEntry);
/*N*/           aCollections[nLevel].Insert( new ScOutlineEntry( *pEntry ) );
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void ScOutlineArray::FindEntry( USHORT nSearchPos, USHORT& rFindLevel, USHORT& rFindIndex,
/*N*/                               USHORT nMaxLevel )
/*N*/ {
/*N*/   rFindLevel = rFindIndex = 0;
/*N*/
/*N*/   if (nMaxLevel > nDepth)
/*N*/       nMaxLevel = nDepth;
/*N*/
/*N*/   for (USHORT nLevel=0; nLevel<nMaxLevel; nLevel++)               //! rueckwaerts suchen ?
/*N*/   {
/*N*/       ScOutlineCollection* pCollect = &aCollections[nLevel];
/*N*/       USHORT nCount = pCollect->GetCount();
/*N*/       for (USHORT i=0; i<nCount; i++)
/*N*/       {
/*N*/           ScOutlineEntry* pEntry = (ScOutlineEntry*) pCollect->At(i);
/*N*/           if ( pEntry->GetStart() <= nSearchPos && pEntry->GetEnd() >= nSearchPos )
/*N*/           {
/*N*/               rFindLevel = nLevel + 1;            // naechster Level (zum Einfuegen)
/*N*/               rFindIndex = i;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ BOOL ScOutlineArray::Insert( USHORT nStartCol, USHORT nEndCol, BOOL& rSizeChanged,
/*N*/                               BOOL bHidden, BOOL bVisible )
/*N*/ {
/*N*/   rSizeChanged = FALSE;
/*N*/
/*N*/   USHORT nStartLevel;
/*N*/   USHORT nStartIndex;
/*N*/   USHORT nEndLevel;
/*N*/   USHORT nEndIndex;
/*N*/   BOOL bFound = FALSE;
/*N*/
/*N*/   BOOL bCont;
/*N*/   USHORT nFindMax;
/*N*/   FindEntry( nStartCol, nStartLevel, nStartIndex );       // nLevel = neuer Level (alter+1) !!!
/*N*/   FindEntry( nEndCol, nEndLevel, nEndIndex );
/*N*/   nFindMax = Max(nStartLevel,nEndLevel);
/*N*/   do
/*N*/   {
/*N*/       bCont = FALSE;
/*N*/
/*N*/       if ( nStartLevel == nEndLevel && nStartIndex == nEndIndex && nStartLevel < SC_OL_MAXDEPTH )
/*N*/           bFound = TRUE;
/*N*/
/*N*/       if (!bFound)
/*N*/       {
/*N*/           if (nFindMax>0)
/*N*/           {
/*N*/               --nFindMax;
/*N*/               if (nStartLevel)
/*N*/                   if ( ((ScOutlineEntry*)aCollections[nStartLevel-1].At(nStartIndex))->
/*N*/                               GetStart() == nStartCol )
/*N*/                       FindEntry( nStartCol, nStartLevel, nStartIndex, nFindMax );
/*N*/               if (nEndLevel)
/*?*/                   if ( ((ScOutlineEntry*)aCollections[nEndLevel-1].At(nEndIndex))->
/*?*/                               GetEnd() == nEndCol )
/*N*/                       FindEntry( nEndCol, nEndLevel, nEndIndex, nFindMax );
/*N*/               bCont = TRUE;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   while ( !bFound && bCont );
/*N*/
/*N*/   if (!bFound)
/*N*/       return FALSE;
/*N*/
/*N*/   USHORT nLevel = nStartLevel;
/*N*/
/*N*/   //  untere verschieben
/*N*/
/*N*/   BOOL bNeedSize = FALSE;
/*N*/   for ( short nMoveLevel = nDepth-1; nMoveLevel >= (short) nLevel; nMoveLevel-- )
/*N*/   {
/*N*/       USHORT nCount = aCollections[nMoveLevel].GetCount();
/*N*/       BOOL bMoved = FALSE;
/*N*/       for ( USHORT i=0; i<nCount; i += bMoved ? 0 : 1 )
/*N*/       {
/*N*/           ScOutlineEntry* pEntry = (ScOutlineEntry*) aCollections[nMoveLevel].At(i);
/*N*/           USHORT nEntryStart = pEntry->GetStart();
/*N*/           if ( nEntryStart >= nStartCol && nEntryStart <= nEndCol )
/*N*/           {
/*N*/               if (nMoveLevel >= SC_OL_MAXDEPTH - 1)
/*N*/               {
/*?*/                   rSizeChanged = FALSE;               // kein Platz
/*?*/                   return FALSE;
/*N*/               }
/*N*/               aCollections[nMoveLevel+1].Insert( new ScOutlineEntry( *pEntry ) );
/*N*/               aCollections[nMoveLevel].AtFree( i );
/*N*/               nCount = aCollections[nMoveLevel].GetCount();
/*N*/               bMoved = TRUE;
/*N*/               if (nMoveLevel == (short) nDepth - 1)
/*N*/                   bNeedSize = TRUE;
/*N*/           }
/*N*/           else
/*N*/               bMoved = FALSE;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (bNeedSize)
/*N*/   {
/*N*/       ++nDepth;
/*N*/       rSizeChanged = TRUE;
/*N*/   }
/*N*/
/*N*/   if (nDepth <= nLevel)
/*N*/   {
/*N*/       nDepth = nLevel+1;
/*N*/       rSizeChanged = TRUE;
/*N*/   }
/*N*/
/*          nicht zusammenfassen!

    //  zusammenfassen

    USHORT nCount = aCollections[nLevel].GetCount();
    USHORT nIndex;
    bFound = FALSE;
    for ( nIndex=0; nIndex<nCount && !bFound; nIndex++ )
    {
        if ( ((ScOutlineEntry*) aCollections[nLevel].At(nIndex))->GetEnd() + 1 == nStartCol )
        {
            nStartCol = ((ScOutlineEntry*) aCollections[nLevel].At(nIndex))->GetStart();
            aCollections[nLevel].AtFree(nIndex);
            nCount = aCollections[nLevel].GetCount();       // Daten geaendert
            bFound = TRUE;
        }
    }

    bFound = FALSE;
    for ( nIndex=0; nIndex<nCount && !bFound; nIndex++ )
    {
        if ( ((ScOutlineEntry*) aCollections[nLevel].At(nIndex))->GetStart() == nEndCol + 1 )
        {
            nEndCol = ((ScOutlineEntry*) aCollections[nLevel].At(nIndex))->GetEnd();
            aCollections[nLevel].AtFree(nIndex);
            bFound = TRUE;
        }
    }
*/
/*N*/   ScOutlineEntry* pNewEntry = new ScOutlineEntry( nStartCol, nEndCol+1-nStartCol, bHidden );
/*N*/   pNewEntry->SetVisible( bVisible );
/*N*/   aCollections[nLevel].Insert( pNewEntry );
/*N*/
/*N*/   return TRUE;
/*N*/ }

//STRIP001 BOOL ScOutlineArray::FindTouchedLevel( USHORT nBlockStart, USHORT nBlockEnd, USHORT& rFindLevel ) const
//STRIP001 {
//STRIP001  BOOL bFound = FALSE;
//STRIP001  rFindLevel = 0;
//STRIP001
//STRIP001  for (USHORT nLevel=0; nLevel<nDepth; nLevel++)
//STRIP001  {
//STRIP001         const ScOutlineCollection* pCollect = &aCollections[nLevel];
//STRIP001      USHORT nCount = pCollect->GetCount();
//STRIP001      for (USHORT i=0; i<nCount; i++)
//STRIP001      {
//STRIP001          ScOutlineEntry* pEntry = (ScOutlineEntry*) pCollect->At(i);
//STRIP001          USHORT nStart = pEntry->GetStart();
//STRIP001          USHORT nEnd   = pEntry->GetEnd();
//STRIP001
//STRIP001          if ( ( nBlockStart>=nStart && nBlockStart<=nEnd ) ||
//STRIP001               ( nBlockEnd  >=nStart && nBlockEnd  <=nEnd ) )
//STRIP001          {
//STRIP001              rFindLevel = nLevel;            // wirklicher Level
//STRIP001              bFound = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return bFound;
//STRIP001 }

//STRIP001 void ScOutlineArray::RemoveSub( USHORT nStartPos, USHORT nEndPos, USHORT nLevel )
//STRIP001 {
//STRIP001     if ( nLevel >= nDepth )
//STRIP001         return;
//STRIP001     ScOutlineCollection* pCollect = &aCollections[nLevel];
//STRIP001  USHORT nCount = pCollect->GetCount();
//STRIP001  BOOL bFound = FALSE;
//STRIP001  for ( USHORT i=0; i<nCount; i += ( bFound ? 0 : 1 ) )
//STRIP001  {
//STRIP001      bFound = FALSE;
//STRIP001      ScOutlineEntry* pEntry = (ScOutlineEntry*) pCollect->At(i);
//STRIP001      USHORT nStart = pEntry->GetStart();
//STRIP001      USHORT nEnd   = pEntry->GetEnd();
//STRIP001
//STRIP001      if ( nStart>=nStartPos && nEnd<=nEndPos )
//STRIP001      {
//STRIP001          RemoveSub( nStart, nEnd, nLevel+1 );
//STRIP001          pCollect->AtFree(i);
//STRIP001          nCount = pCollect->GetCount();
//STRIP001          bFound = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void ScOutlineArray::PromoteSub( USHORT nStartPos, USHORT nEndPos, USHORT nStartLevel )
//STRIP001 {
//STRIP001  if (nStartLevel==0)
//STRIP001  {
//STRIP001      DBG_ERROR("PromoteSub mit Level 0");
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  for (USHORT nLevel = nStartLevel; nLevel < nDepth; nLevel++)
//STRIP001  {
//STRIP001      ScOutlineCollection* pCollect = &aCollections[nLevel];
//STRIP001      USHORT nCount = pCollect->GetCount();
//STRIP001      BOOL bFound = FALSE;
//STRIP001      for ( USHORT i=0; i<nCount; i += ( bFound ? 0 : 1 ) )
//STRIP001      {
//STRIP001          bFound = FALSE;
//STRIP001          ScOutlineEntry* pEntry = (ScOutlineEntry*) pCollect->At(i);
//STRIP001          USHORT nStart = pEntry->GetStart();
//STRIP001          USHORT nEnd   = pEntry->GetEnd();
//STRIP001
//STRIP001          if ( nStart>=nStartPos && nEnd<=nEndPos )
//STRIP001          {
//STRIP001              aCollections[nLevel-1].Insert( new ScOutlineEntry( *pEntry ) );
//STRIP001              pCollect->AtFree(i);
//STRIP001              nCount = pCollect->GetCount();
//STRIP001              bFound = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*N*/ BOOL ScOutlineArray::DecDepth()                           // nDepth auf leere Levels anpassen
/*N*/ {
/*N*/   BOOL bChanged = FALSE;
/*N*/   BOOL bCont;
/*N*/   do
/*N*/   {
/*N*/       bCont = FALSE;
/*N*/       if (nDepth)
/*N*/           if (aCollections[nDepth-1].GetCount() == 0)
/*N*/           {
/*N*/               --nDepth;
/*N*/               bChanged = TRUE;
/*N*/               bCont = TRUE;
/*N*/           }
/*N*/   }
/*N*/   while (bCont);
/*N*/   return bChanged;
/*N*/ }

//STRIP001 BOOL ScOutlineArray::Remove( USHORT nBlockStart, USHORT nBlockEnd, BOOL& rSizeChanged )
//STRIP001 {
//STRIP001  USHORT nLevel;
//STRIP001  FindTouchedLevel( nBlockStart, nBlockEnd, nLevel );
//STRIP001
//STRIP001  ScOutlineCollection* pCollect = &aCollections[nLevel];
//STRIP001  USHORT nCount = pCollect->GetCount();
//STRIP001  BOOL bFound = FALSE;
//STRIP001  BOOL bAny = FALSE;
//STRIP001  for ( USHORT i=0; i<nCount; i += ( bFound ? 0 : 1 ) )
//STRIP001  {
//STRIP001      bFound = FALSE;
//STRIP001      ScOutlineEntry* pEntry = (ScOutlineEntry*) pCollect->At(i);
//STRIP001      USHORT nStart = pEntry->GetStart();
//STRIP001      USHORT nEnd   = pEntry->GetEnd();
//STRIP001
//STRIP001      if ( nBlockStart<=nEnd && nBlockEnd>=nStart )
//STRIP001      {
//STRIP001 //           RemoveSub( nStart, nEnd, nLevel+1 );
//STRIP001          pCollect->AtFree(i);
//STRIP001          PromoteSub( nStart, nEnd, nLevel+1 );
//STRIP001          nCount = pCollect->GetCount();
//STRIP001          i = pCollect->FindStart( nEnd+1 );
//STRIP001          bFound = TRUE;
//STRIP001          bAny = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if (bAny)                                   // Depth anpassen
//STRIP001      if (DecDepth())
//STRIP001          rSizeChanged = TRUE;
//STRIP001
//STRIP001  return bAny;
//STRIP001 }

/*M*/ ScOutlineEntry* ScOutlineArray::GetEntry( USHORT nLevel, USHORT nIndex ) const
/*M*/ {
/*M*/     return (ScOutlineEntry*)((nLevel < nDepth) ? aCollections[nLevel].At(nIndex) : NULL);
/*M*/ }

/*M*/ USHORT ScOutlineArray::GetCount( USHORT nLevel ) const
/*M*/ {
/*M*/     return (nLevel < nDepth) ? aCollections[nLevel].GetCount() : 0;
/*M*/ }

//STRIP001 ScOutlineEntry* ScOutlineArray::GetEntryByPos( USHORT nLevel, USHORT nPos ) const
//STRIP001 {
//STRIP001  USHORT          nCount  = GetCount( nLevel );
//STRIP001  ScOutlineEntry* pEntry;
//STRIP001
//STRIP001  for (USHORT nIndex = 0; nIndex < nCount; nIndex++)
//STRIP001  {
//STRIP001      pEntry = GetEntry( nLevel, nIndex );
//STRIP001      if ((pEntry->GetStart() <= nPos) && (nPos <= pEntry->GetEnd()))
//STRIP001          return pEntry;
//STRIP001  }
//STRIP001  return NULL;
//STRIP001 }

/*M*/ BOOL ScOutlineArray::GetEntryIndex( USHORT nLevel, USHORT nPos, USHORT& rnIndex ) const
/*M*/ {
/*M*/     // found entry contains passed position
/*M*/     USHORT nCount  = GetCount( nLevel );
/*M*/     for ( rnIndex = 0; rnIndex < nCount; ++rnIndex )
/*M*/     {
/*M*/         const ScOutlineEntry* pEntry = GetEntry( nLevel, rnIndex );
/*M*/         if ( (pEntry->GetStart() <= nPos) && (nPos <= pEntry->GetEnd()) )
/*M*/             return TRUE;
/*M*/     }
/*M*/     return FALSE;
/*M*/ }

/*M*/ BOOL ScOutlineArray::GetEntryIndexInRange(
/*M*/         USHORT nLevel, USHORT nBlockStart, USHORT nBlockEnd, USHORT& rnIndex ) const
/*M*/ {
/*M*/     // found entry will be completely inside of passed range
/*M*/     USHORT nCount  = GetCount( nLevel );
/*M*/     for ( rnIndex = 0; rnIndex < nCount; ++rnIndex )
/*M*/     {
/*M*/         const ScOutlineEntry* pEntry = GetEntry( nLevel, rnIndex );
/*M*/         if ( (nBlockStart <= pEntry->GetStart()) && (pEntry->GetEnd() <= nBlockEnd) )
/*M*/             return TRUE;
/*M*/     }
/*M*/     return FALSE;
/*M*/ }

/*M*/ void ScOutlineArray::SetVisibleBelow( USHORT nLevel, USHORT nEntry, BOOL bValue, BOOL bSkipHidden )
/*M*/ {
/*M*/     ScOutlineEntry* pEntry = GetEntry( nLevel, nEntry );
/*M*/     if( pEntry )
/*M*/     {
/*M*/         USHORT nStart = pEntry->GetStart();
/*M*/         USHORT nEnd   = pEntry->GetEnd();
/*M*/
/*M*/         for (USHORT nSubLevel=nLevel+1; nSubLevel<nDepth; nSubLevel++)
/*M*/         {
/*M*/             USHORT i = 0;
/*M*/             pEntry = (ScOutlineEntry*) aCollections[nSubLevel].At(i);
/*M*/             while (pEntry)
/*M*/             {
/*M*/                 if (pEntry->GetStart() >= nStart && pEntry->GetEnd() <= nEnd)
/*M*/                 {
/*M*/                     pEntry->SetVisible(bValue);
/*M*/
/*M*/                     if (bSkipHidden)
/*M*/                         if (!pEntry->IsHidden())
/*M*/                             SetVisibleBelow( nSubLevel, i, bValue, TRUE );
/*M*/                 }
/*M*/
/*M*/                 ++i;
/*M*/                 pEntry = (ScOutlineEntry*) aCollections[nSubLevel].At(i);
/*M*/             }
/*M*/
/*M*/             if (bSkipHidden)
/*M*/                 nSubLevel = nDepth;             // Abbruch
/*M*/         }
/*M*/     }
/*M*/ }

//STRIP001 void ScOutlineArray::GetRange( USHORT& rStart, USHORT& rEnd ) const
//STRIP001 {
//STRIP001  USHORT nCount = aCollections[0].GetCount();
//STRIP001  if (nCount)
//STRIP001  {
//STRIP001      rStart = ((ScOutlineEntry*) aCollections[0].At(0))->GetStart();
//STRIP001      rEnd   = ((ScOutlineEntry*) aCollections[0].At(nCount-1))->GetEnd();
//STRIP001  }
//STRIP001  else
//STRIP001      rStart = rEnd = 0;
//STRIP001 }

//STRIP001 void ScOutlineArray::ExtendBlock( USHORT nLevel, USHORT& rBlkStart, USHORT& rBlkEnd )
//STRIP001 {
//STRIP001  USHORT  nCount;
//STRIP001  USHORT  nStart;
//STRIP001  USHORT  nEnd;
//STRIP001  USHORT  i;
//STRIP001  ScOutlineEntry* pEntry;
//STRIP001
//STRIP001  nCount = GetCount(nLevel);
//STRIP001  for ( i=0; i<nCount; i++ )
//STRIP001  {
//STRIP001      pEntry = (ScOutlineEntry*) aCollections[nLevel].At(i);
//STRIP001      nStart = pEntry->GetStart();
//STRIP001      nEnd   = pEntry->GetEnd();
//STRIP001
//STRIP001      if ( rBlkStart<=nEnd && rBlkEnd>=nStart )
//STRIP001      {
//STRIP001          if (nStart<rBlkStart) rBlkStart = nStart;
//STRIP001          if (nEnd>rBlkEnd) rBlkEnd = nEnd;
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*N*/ BOOL ScOutlineArray::TestInsertSpace( USHORT nSize, USHORT nMaxVal ) const
/*N*/ {
/*N*/   USHORT nCount = aCollections[0].GetCount();
/*N*/   if (nCount)
/*N*/   {
/*N*/       USHORT nEnd = ((ScOutlineEntry*) aCollections[0].At(nCount-1))->GetEnd();
/*N*/       return ( nEnd+nSize <= nMaxVal );
/*N*/   }
/*N*/
/*N*/   return TRUE;
/*N*/ }

/*N*/ void ScOutlineArray::InsertSpace( USHORT nStartPos, USHORT nSize )
/*N*/ {
/*N*/   ScSubOutlineIterator aIter( this );
/*N*/   ScOutlineEntry* pEntry;
/*N*/   while((pEntry=aIter.GetNext())!=NULL)
/*N*/   {
/*N*/       if ( pEntry->GetStart() >= nStartPos )
/*N*/           pEntry->Move(nSize);
/*N*/       else
/*N*/       {
/*N*/           USHORT nEnd = pEntry->GetEnd();
/*N*/           //  immer erweitern, wenn innerhalb der Gruppe eingefuegt
/*N*/           //  beim Einfuegen am Ende nur, wenn die Gruppe nicht ausgeblendet ist
/*N*/           if ( nEnd >= nStartPos || ( nEnd+1 >= nStartPos && !pEntry->IsHidden() ) )
/*N*/           {
/*N*/               USHORT nEntrySize = pEntry->GetSize();
/*N*/               nEntrySize += nSize;
/*N*/               pEntry->SetSize( nEntrySize );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ BOOL ScOutlineArray::DeleteSpace( USHORT nStartPos, USHORT nSize )
/*N*/ {
/*N*/   USHORT nEndPos = nStartPos + nSize - 1;
/*N*/   BOOL bNeedSave = FALSE;                         // Original fuer Undo benoetigt?
/*N*/   BOOL bChanged = FALSE;                          // fuer Test auf Level
/*N*/
/*N*/   ScSubOutlineIterator aIter( this );
/*N*/   ScOutlineEntry* pEntry;
/*N*/   while((pEntry=aIter.GetNext())!=NULL)
/*N*/   {
/*N*/       USHORT nEntryStart = pEntry->GetStart();
/*N*/       USHORT nEntryEnd   = pEntry->GetEnd();
/*N*/       USHORT nEntrySize  = pEntry->GetSize();
/*N*/
/*N*/       if ( nEntryEnd >= nStartPos )
/*N*/       {
/*N*/           if ( nEntryStart > nEndPos )                                        // rechts
/*N*/               pEntry->Move(-(short)nSize);
/*N*/           else if ( nEntryStart < nStartPos && nEntryEnd >= nEndPos )         // aussen
/*N*/               pEntry->SetSize( nEntrySize-nSize );
/*N*/           else
/*N*/           {
/*N*/               bNeedSave = TRUE;
/*N*/               if ( nEntryStart >= nStartPos && nEntryEnd <= nEndPos )             // innen
/*N*/               {
/*N*/                   aIter.DeleteLast();
/*N*/                   bChanged = TRUE;
/*N*/               }
/*N*/               else if ( nEntryStart >= nStartPos )                                // rechts ueber
/*N*/                   pEntry->SetPosSize( nStartPos, nEntryEnd-nEndPos );
/*N*/               else                                                                // links ueber
/*N*/                   pEntry->SetSize( nStartPos-nEntryStart );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (bChanged)
/*N*/       DecDepth();
/*N*/
/*N*/   return bNeedSave;
/*N*/ }

/*N*/ BOOL ScOutlineArray::ManualAction( USHORT nStartPos, USHORT nEndPos, BOOL bShow, BYTE* pHiddenFlags )
/*N*/ {
/*N*/   BOOL bModified = FALSE;
/*N*/   ScSubOutlineIterator aIter( this );
/*N*/   ScOutlineEntry* pEntry;
/*N*/   while((pEntry=aIter.GetNext())!=NULL)
/*N*/   {
/*N*/       USHORT nEntryStart = pEntry->GetStart();
/*N*/       USHORT nEntryEnd   = pEntry->GetEnd();
/*N*/
/*N*/       if (nEntryEnd>=nStartPos && nEntryStart<=nEndPos)
/*N*/       {
/*?*/           if ( pEntry->IsHidden() == bShow )
/*?*/           {
/*?*/               //  #i12341# hide if all columns/rows are hidden, show if at least one
/*?*/               //  is visible
/*?*/
/*?*/               BOOL bAllHidden = TRUE;
/*?*/               for ( USHORT i=nEntryStart; i<=nEntryEnd && bAllHidden; i++ )
/*?*/                   if ( ( pHiddenFlags[i] & CR_HIDDEN ) == 0 )
/*?*/                       bAllHidden = FALSE;
/*?*/
/*?*/               BOOL bToggle = ( bShow != bAllHidden );
/*?*/               if ( bToggle )
/*?*/               {
/*?*/                   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 pEntry->SetHidden( !bShow );
//STRIP001 /*?*/                    SetVisibleBelow( aIter.LastLevel(), aIter.LastEntry(), bShow, bShow );
//STRIP001 /*?*/                    bModified = TRUE;
/*?*/               }
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/   return bModified;
/*N*/ }

//STRIP001 void ScOutlineArray::RemoveAll()
//STRIP001 {
//STRIP001  for (USHORT nLevel=0; nLevel<nDepth; nLevel++)
//STRIP001      aCollections[nLevel].FreeAll();
//STRIP001
//STRIP001  nDepth = 0;
//STRIP001 }

/*N*/ void ScOutlineArray::Load( SvStream& rStream )
/*N*/ {
/*N*/   ScMultipleReadHeader aHdr( rStream );
/*N*/
/*N*/   rStream >> nDepth;
/*N*/   for (USHORT nLevel=0; nLevel<nDepth; nLevel++)
/*N*/   {
/*N*/       USHORT nCount;
/*N*/       rStream >> nCount;
/*N*/       for (USHORT nIndex=0; nIndex<nCount; nIndex++)
/*N*/       {
/*N*/           ScOutlineEntry* pEntry = new ScOutlineEntry( rStream, aHdr );
/*N*/           aCollections[nLevel].Insert( pEntry );
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void ScOutlineArray::Store( SvStream& rStream )
/*N*/ {
/*N*/   ScMultipleWriteHeader aHdr( rStream );
/*N*/
/*N*/   rStream << nDepth;
/*N*/   for (USHORT nLevel=0; nLevel<nDepth; nLevel++)
/*N*/   {
/*N*/       USHORT nCount = aCollections[nLevel].GetCount();
/*N*/       rStream << nCount;
/*N*/       for (USHORT nIndex=0; nIndex<nCount; nIndex++)
/*N*/           ((ScOutlineEntry*) aCollections[nLevel].At(nIndex))->Store( rStream, aHdr );
/*N*/   }
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScOutlineTable::ScOutlineTable()
/*N*/ {
/*N*/ }

/*N*/ ScOutlineTable::ScOutlineTable( const ScOutlineTable& rOutline ) :
/*N*/   aColOutline( rOutline.aColOutline ),
/*N*/   aRowOutline( rOutline.aRowOutline )
/*N*/ {
/*N*/ }

/*N*/ BOOL ScOutlineTable::TestInsertCol( USHORT nSize )
/*N*/ {
/*N*/   return aColOutline.TestInsertSpace( nSize, MAXCOL );
/*N*/ }

/*N*/ void ScOutlineTable::InsertCol( USHORT nStartCol, USHORT nSize )
/*N*/ {
/*N*/   aColOutline.InsertSpace( nStartCol, nSize );
/*N*/ }

/*N*/ BOOL ScOutlineTable::DeleteCol( USHORT nStartCol, USHORT nSize )
/*N*/ {
/*N*/   return aColOutline.DeleteSpace( nStartCol, nSize );
/*N*/ }

/*N*/ BOOL ScOutlineTable::TestInsertRow( USHORT nSize )
/*N*/ {
/*N*/   return aRowOutline.TestInsertSpace( nSize, MAXROW );
/*N*/ }

/*N*/ void ScOutlineTable::InsertRow( USHORT nStartRow, USHORT nSize )
/*N*/ {
/*N*/   aRowOutline.InsertSpace( nStartRow, nSize );
/*N*/ }

/*N*/ BOOL ScOutlineTable::DeleteRow( USHORT nStartRow, USHORT nSize )
/*N*/ {
/*N*/   return aRowOutline.DeleteSpace( nStartRow, nSize );
/*N*/ }

/*N*/ void ScOutlineTable::Load( SvStream& rStream )
/*N*/ {
/*N*/   DBG_ASSERT( aColOutline.GetDepth()==0 && aRowOutline.GetDepth()==0,
/*N*/                   "Load auf nicht leere ScOutlineTable" );
/*N*/   aColOutline.Load( rStream );
/*N*/   aRowOutline.Load( rStream );
/*N*/ }

/*N*/ void ScOutlineTable::Store( SvStream& rStream )
/*N*/ {
/*N*/   aColOutline.Store( rStream );
/*N*/   aRowOutline.Store( rStream );
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScSubOutlineIterator::ScSubOutlineIterator( ScOutlineArray* pOutlineArray ) :
/*N*/       pArray( pOutlineArray ),
/*N*/       nStart( 0 ),
/*N*/       nEnd( USHRT_MAX ),                          // alle durchgehen
/*N*/       nSubLevel( 0 ),
/*N*/       nSubEntry( 0 )
/*N*/ {
/*N*/   nDepth = pArray->nDepth;
/*N*/ }

//STRIP001 ScSubOutlineIterator::ScSubOutlineIterator( ScOutlineArray* pOutlineArray,
//STRIP001                                          USHORT nLevel, USHORT nEntry ) :
//STRIP001      pArray( pOutlineArray )
//STRIP001 {
//STRIP001  ScOutlineEntry* pEntry = (ScOutlineEntry*) pArray->aCollections[nLevel].At(nEntry);
//STRIP001  nStart = pEntry->GetStart();
//STRIP001  nEnd   = pEntry->GetEnd();
//STRIP001  nSubLevel = nLevel + 1;
//STRIP001  nSubEntry = 0;
//STRIP001  nDepth = pArray->nDepth;
//STRIP001 }
/*N*/
/*N*/ ScOutlineEntry* ScSubOutlineIterator::GetNext()
/*N*/ {
/*N*/   ScOutlineEntry* pEntry;
/*N*/   BOOL bFound = FALSE;
/*N*/   do
/*N*/   {
/*N*/       if (nSubLevel >= nDepth)
/*N*/           return NULL;
/*N*/
/*N*/       pEntry = (ScOutlineEntry*) pArray->aCollections[nSubLevel].At(nSubEntry);
/*N*/       if (!pEntry)
/*N*/       {
/*N*/           nSubEntry = 0;
/*N*/           ++nSubLevel;
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           if ( pEntry->GetStart() >= nStart && pEntry->GetEnd() <= nEnd )
/*N*/               bFound = TRUE;
/*N*/           ++nSubEntry;
/*N*/       }
/*N*/   }
/*N*/   while (!bFound);
/*N*/   return pEntry;                  // nSubLevel gueltig, wenn pEntry != 0
/*N*/ }
/*N*/
//STRIP001 USHORT ScSubOutlineIterator::LastLevel() const
//STRIP001 {
//STRIP001  return nSubLevel;
//STRIP001 }
//STRIP001
//STRIP001 USHORT ScSubOutlineIterator::LastEntry() const
//STRIP001 {
//STRIP001  if (nSubEntry == 0)
//STRIP001  {
//STRIP001      DBG_ERROR("ScSubOutlineIterator::LastEntry vor GetNext");
//STRIP001      return 0;
//STRIP001  }
//STRIP001  return nSubEntry-1;
//STRIP001 }
//STRIP001
/*N*/ void ScSubOutlineIterator::DeleteLast()
/*N*/ {
/*N*/   if (nSubLevel >= nDepth)
/*N*/   {
/*N*/       DBG_ERROR("ScSubOutlineIterator::DeleteLast nach Ende");
/*N*/       return;
/*N*/   }
/*N*/   if (nSubEntry == 0)
/*N*/   {
/*N*/       DBG_ERROR("ScSubOutlineIterator::DeleteLast vor GetNext");
/*N*/       return;
/*N*/   }
/*N*/
/*N*/   --nSubEntry;
/*N*/   pArray->aCollections[nSubLevel].AtFree(nSubEntry);
/*N*/ }


}
