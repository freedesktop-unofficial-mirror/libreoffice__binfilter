/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_markdata.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 16:50:11 $
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

#ifdef PCH
// auto strip #include "core_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------

#include <tools/debug.hxx>

#include "markdata.hxx"
#include "markarr.hxx"
#include "rangelst.hxx"
namespace binfilter {

// STATIC DATA -----------------------------------------------------------

//------------------------------------------------------------------------

/*N*/ ScMarkData::ScMarkData() :
/*N*/   pMultiSel( NULL )
/*N*/ {
/*N*/   for (USHORT i=0; i<=MAXTAB; i++)
/*N*/       bTabMarked[i] = FALSE;
/*N*/
/*N*/   ResetMark();
/*N*/ }

/*N*/ ScMarkData::ScMarkData(const ScMarkData& rData) :
/*N*/   pMultiSel( NULL ),
/*N*/   aMarkRange( rData.aMarkRange ),
/*N*/   aMultiRange( rData.aMultiRange )
/*N*/ {
/*N*/   bMarked      = rData.bMarked;
/*N*/   bMultiMarked = rData.bMultiMarked;
/*N*/   bMarking     = rData.bMarking;
/*N*/   bMarkIsNeg   = rData.bMarkIsNeg;
/*N*/
/*N*/   USHORT i;
/*N*/   for (i=0; i<=MAXTAB; i++)
/*N*/       bTabMarked[i] = rData.bTabMarked[i];
/*N*/
/*N*/   if (rData.pMultiSel)
/*N*/   {
/*N*/       pMultiSel = new ScMarkArray[MAXCOL+1];
/*N*/       for (i=0; i<=MAXCOL; i++)
/*N*/           rData.pMultiSel[i].CopyMarksTo( pMultiSel[i] );
/*N*/   }
/*N*/ }

//STRIP001 ScMarkData&  ScMarkData::operator=(const ScMarkData& rData)
//STRIP001 {
//STRIP001  if ( &rData == this )
//STRIP001      return *this;
//STRIP001
//STRIP001  delete[] pMultiSel;
//STRIP001  pMultiSel = NULL;
//STRIP001
//STRIP001  aMarkRange   = rData.aMarkRange;
//STRIP001  aMultiRange  = rData.aMultiRange;
//STRIP001  bMarked      = rData.bMarked;
//STRIP001  bMultiMarked = rData.bMultiMarked;
//STRIP001  bMarking     = rData.bMarking;
//STRIP001  bMarkIsNeg   = rData.bMarkIsNeg;
//STRIP001
//STRIP001  USHORT i;
//STRIP001  for (i=0; i<=MAXTAB; i++)
//STRIP001      bTabMarked[i] = rData.bTabMarked[i];
//STRIP001
//STRIP001  if (rData.pMultiSel)
//STRIP001  {
//STRIP001      pMultiSel = new ScMarkArray[MAXCOL+1];
//STRIP001      for (i=0; i<=MAXCOL; i++)
//STRIP001          rData.pMultiSel[i].CopyMarksTo( pMultiSel[i] );
//STRIP001  }
//STRIP001
//STRIP001  return *this;
//STRIP001 }

/*N*/ ScMarkData::~ScMarkData()
/*N*/ {
/*N*/   delete[] pMultiSel;
/*N*/ }

/*N*/ void ScMarkData::ResetMark()
/*N*/ {
/*N*/   delete[] pMultiSel;
/*N*/   pMultiSel = NULL;
/*N*/
/*N*/   bMarked = bMultiMarked = FALSE;
/*N*/   bMarking = bMarkIsNeg = FALSE;
/*N*/ }

/*N*/ void ScMarkData::SetMarkArea( const ScRange& rRange )
/*N*/ {
/*N*/   aMarkRange = rRange;
/*N*/   aMarkRange.Justify();
/*N*/   if ( !bMarked )
/*N*/   {
/*N*/       // #77987# Upon creation of a document ScFormatShell GetTextAttrState
/*N*/       // may query (default) attributes although no sheet is marked yet.
/*N*/       // => mark that one.
/*N*/       if ( !GetSelectCount() )
/*N*/           bTabMarked[ aMarkRange.aStart.Tab() ] = TRUE;
/*N*/       bMarked = TRUE;
/*N*/   }
/*N*/ }

/*N*/ void ScMarkData::GetMarkArea( ScRange& rRange ) const
/*N*/ {
/*N*/   rRange = aMarkRange;        //! inline ?
/*N*/ }

/*N*/ void ScMarkData::GetMultiMarkArea( ScRange& rRange ) const
/*N*/ {
/*N*/   rRange = aMultiRange;
/*N*/ }

/*N*/ void ScMarkData::SetMultiMarkArea( const ScRange& rRange, BOOL bMark )
/*N*/ {
/*N*/   if (!pMultiSel)
/*N*/   {
/*N*/       pMultiSel = new ScMarkArray[MAXCOL+1];
/*N*/
/*N*/       // if simple mark range is set, copy to multi marks
/*N*/       if ( bMarked && !bMarkIsNeg )
/*N*/       {
/*N*/           bMarked = FALSE;
/*N*/           SetMultiMarkArea( aMarkRange, TRUE );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   USHORT nStartCol = rRange.aStart.Col();
/*N*/   USHORT nStartRow = rRange.aStart.Row();
/*N*/   USHORT nEndCol = rRange.aEnd.Col();
/*N*/   USHORT nEndRow = rRange.aEnd.Row();
/*N*/   PutInOrder( nStartRow, nEndRow );
/*N*/   PutInOrder( nStartCol, nEndCol );
/*N*/
/*N*/   USHORT nCol;
/*N*/   for (nCol=nStartCol; nCol<=nEndCol; nCol++)
/*N*/       pMultiSel[nCol].SetMarkArea( nStartRow, nEndRow, bMark );
/*N*/
/*N*/   if ( bMultiMarked )                 // aMultiRange updaten
/*N*/   {
/*N*/       if ( nStartCol < aMultiRange.aStart.Col() )
/*N*/           aMultiRange.aStart.SetCol( nStartCol );
/*N*/       if ( nStartRow < aMultiRange.aStart.Row() )
/*N*/           aMultiRange.aStart.SetRow( nStartRow );
/*N*/       if ( nEndCol > aMultiRange.aEnd.Col() )
/*N*/           aMultiRange.aEnd.SetCol( nEndCol );
/*N*/       if ( nEndRow > aMultiRange.aEnd.Row() )
/*N*/           aMultiRange.aEnd.SetRow( nEndRow );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       aMultiRange = rRange;           // neu
/*N*/       bMultiMarked = TRUE;
/*N*/   }
/*N*/ }

//STRIP001 void ScMarkData::SetAreaTab( USHORT nTab )
//STRIP001 {
//STRIP001  aMarkRange.aStart.SetTab(nTab);
//STRIP001  aMarkRange.aEnd.SetTab(nTab);
//STRIP001  aMultiRange.aStart.SetTab(nTab);
//STRIP001  aMultiRange.aEnd.SetTab(nTab);
//STRIP001 }

/*N*/ void ScMarkData::SelectOneTable( USHORT nTab )
/*N*/ {
/*N*/   for (USHORT i=0; i<=MAXTAB; i++)
/*N*/       bTabMarked[i] = ( nTab == i );
/*N*/ }

/*N*/ USHORT ScMarkData::GetSelectCount() const
/*N*/ {
/*N*/   USHORT nCount = 0;
/*N*/   for (USHORT i=0; i<=MAXTAB; i++)
/*N*/       if (bTabMarked[i])
/*N*/           ++nCount;
/*N*/
/*N*/   return nCount;
/*N*/ }

/*N*/ USHORT ScMarkData::GetFirstSelected() const
/*N*/ {
/*N*/   for (USHORT i=0; i<=MAXTAB; i++)
/*N*/       if (bTabMarked[i])
/*N*/           return i;
/*N*/
/*N*/   DBG_ERROR("GetFirstSelected: keine markiert");
/*N*/   return 0;
/*N*/ }

/*N*/ void ScMarkData::MarkToMulti()
/*N*/ {
/*N*/   if ( bMarked && !bMarking )
/*N*/   {
/*N*/       SetMultiMarkArea( aMarkRange, !bMarkIsNeg );
/*N*/       bMarked = FALSE;
/*N*/
/*N*/       //  check if all multi mark ranges have been removed
/*N*/       if ( bMarkIsNeg && !HasAnyMultiMarks() )
/*?*/           ResetMark();
/*N*/   }
/*N*/ }

/*N*/ void ScMarkData::MarkToSimple()
/*N*/ {
/*N*/   if ( bMarking )
/*N*/       return;
/*N*/
/*N*/   if ( bMultiMarked && bMarked )
/*?*/       MarkToMulti();                  // may result in bMarked and bMultiMarked reset
/*N*/
/*N*/   if ( bMultiMarked )
/*N*/   {
/*N*/       DBG_ASSERT(pMultiSel, "bMultiMarked, aber pMultiSel == 0");
/*N*/
/*N*/       ScRange aNew = aMultiRange;
/*N*/
/*N*/       BOOL bOk = FALSE;
/*N*/       USHORT nStartCol = aNew.aStart.Col();
/*N*/       USHORT nEndCol   = aNew.aEnd.Col();
/*N*/
/*N*/       while ( nStartCol < nEndCol && !pMultiSel[nStartCol].HasMarks() )
/*N*/           ++nStartCol;
/*N*/       while ( nStartCol < nEndCol && !pMultiSel[nEndCol].HasMarks() )
/*N*/           --nEndCol;
/*N*/
/*N*/       //  Zeilen werden nur aus MarkArray genommen
/*N*/       USHORT nStartRow, nEndRow;
/*N*/       if ( pMultiSel[nStartCol].HasOneMark( nStartRow, nEndRow ) )
/*N*/       {
/*N*/           bOk = TRUE;
/*N*/           USHORT nCmpStart, nCmpEnd;
/*N*/           for (USHORT nCol=nStartCol+1; nCol<=nEndCol && bOk; nCol++)
/*N*/               if ( !pMultiSel[nCol].HasOneMark( nCmpStart, nCmpEnd )
/*N*/                       || nCmpStart != nStartRow || nCmpEnd != nEndRow )
/*N*/                   bOk = FALSE;
/*N*/       }
/*N*/
/*N*/       if (bOk)
/*N*/       {
/*?*/           aNew.aStart.SetCol(nStartCol);
/*?*/           aNew.aStart.SetRow(nStartRow);
/*?*/           aNew.aEnd.SetCol(nEndCol);
/*?*/           aNew.aEnd.SetRow(nEndRow);
/*?*/
/*?*/           ResetMark();
/*?*/           aMarkRange = aNew;
/*?*/           bMarked = TRUE;
/*?*/           bMarkIsNeg = FALSE;
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ BOOL ScMarkData::IsCellMarked( USHORT nCol, USHORT nRow, BOOL bNoSimple ) const
/*N*/ {
/*N*/   if ( bMarked && !bNoSimple && !bMarkIsNeg )
/*?*/       if ( aMarkRange.aStart.Col() <= nCol && aMarkRange.aEnd.Col() >= nCol &&
/*?*/            aMarkRange.aStart.Row() <= nRow && aMarkRange.aEnd.Row() >= nRow )
/*?*/           return TRUE;
/*N*/
/*N*/   if (bMultiMarked)
/*N*/   {
/*N*/       //! hier auf negative Markierung testen ?
/*N*/
/*N*/       DBG_ASSERT(pMultiSel, "bMultiMarked, aber pMultiSel == 0");
/*N*/       return pMultiSel[nCol].GetMark( nRow );
/*N*/   }
/*N*/
/*N*/   return FALSE;
/*N*/ }

//STRIP001 BOOL ScMarkData::IsColumnMarked( USHORT nCol ) const
//STRIP001 {
//STRIP001  //  bMarkIsNeg inzwischen auch fuer Spaltenkoepfe
//STRIP001  //! GetMarkColumnRanges fuer komplett markierte Spalten
//STRIP001
//STRIP001  if ( bMarked && !bMarkIsNeg &&
//STRIP001                  aMarkRange.aStart.Col() <= nCol && aMarkRange.aEnd.Col() >= nCol &&
//STRIP001                  aMarkRange.aStart.Row() == 0    && aMarkRange.aEnd.Row() == MAXROW )
//STRIP001      return TRUE;
//STRIP001
//STRIP001  if ( bMultiMarked && pMultiSel[nCol].IsAllMarked(0,MAXROW) )
//STRIP001      return TRUE;
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 BOOL ScMarkData::IsRowMarked( USHORT nRow ) const
//STRIP001 {
//STRIP001  //  bMarkIsNeg inzwischen auch fuer Zeilenkoepfe
//STRIP001  //! GetMarkRowRanges fuer komplett markierte Zeilen
//STRIP001
//STRIP001  if ( bMarked && !bMarkIsNeg &&
//STRIP001                  aMarkRange.aStart.Col() == 0    && aMarkRange.aEnd.Col() == MAXCOL &&
//STRIP001                  aMarkRange.aStart.Row() <= nRow && aMarkRange.aEnd.Row() >= nRow )
//STRIP001      return TRUE;
//STRIP001
//STRIP001  if ( bMultiMarked )
//STRIP001  {
//STRIP001      DBG_ASSERT(pMultiSel, "bMultiMarked, aber pMultiSel == 0");
//STRIP001      for (USHORT nCol=0; nCol<=MAXCOL; nCol++)
//STRIP001          if (!pMultiSel[nCol].GetMark(nRow))
//STRIP001              return FALSE;
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }

/*N*/ void ScMarkData::MarkFromRangeList( const ScRangeList& rList, BOOL bReset )
/*N*/ {
/*N*/   if (bReset)
/*N*/   {
/*?*/       for (USHORT i=0; i<=MAXTAB; i++)
/*?*/           bTabMarked[i] = FALSE;              // Tabellen sind nicht in ResetMark
/*?*/       ResetMark();
/*N*/   }
/*N*/
/*N*/   ULONG nCount = rList.Count();
/*N*/   if ( nCount == 1 && !bMarked && !bMultiMarked )
/*N*/   {
/*N*/       ScRange aRange = *rList.GetObject(0);
/*N*/       SetMarkArea( aRange );
/*N*/       SelectTable( aRange.aStart.Tab(), TRUE );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       for (ULONG i=0; i<nCount; i++)
/*N*/       {
/*N*/           ScRange aRange = *rList.GetObject(i);
/*N*/           SetMultiMarkArea( aRange, TRUE );
/*N*/           SelectTable( aRange.aStart.Tab(), TRUE );
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void ScMarkData::FillRangeListWithMarks( ScRangeList* pList, BOOL bClear ) const
/*N*/ {
/*N*/   if (!pList)
/*N*/       return;
/*N*/
/*N*/   if (bClear)
/*?*/       pList->RemoveAll();
/*N*/
/*N*/   //!     bei mehreren selektierten Tabellen mehrere Ranges eintragen !!!
/*N*/
/*N*/   if ( bMultiMarked )
/*N*/   {
/*N*/       DBG_ASSERT(pMultiSel, "bMultiMarked, aber pMultiSel == 0");
/*N*/
/*N*/       USHORT nTab = aMultiRange.aStart.Tab();
/*N*/
/*N*/       USHORT nStartCol = aMultiRange.aStart.Col();
/*N*/       USHORT nEndCol = aMultiRange.aEnd.Col();
/*N*/       for (USHORT nCol=nStartCol; nCol<=nEndCol; nCol++)
/*N*/           if (pMultiSel[nCol].HasMarks())
/*N*/           {
/*N*/               USHORT nTop, nBottom;
/*N*/               ScRange aRange( nCol, 0, nTab );
/*N*/               ScMarkArrayIter aMarkIter( &pMultiSel[nCol] );
/*N*/               while ( aMarkIter.Next( nTop, nBottom ) )
/*N*/               {
/*N*/                   aRange.aStart.SetRow( nTop );
/*N*/                   aRange.aEnd.SetRow( nBottom );
/*N*/                   pList->Join( aRange );
/*N*/               }
/*N*/           }
/*N*/   }
/*N*/
/*N*/   if ( bMarked )
/*?*/       pList->Append( aMarkRange );
/*N*/ }

/*N*/ void ScMarkData::ExtendRangeListTables( ScRangeList* pList ) const
/*N*/ {
/*N*/   if (!pList)
/*N*/       return;
/*N*/
/*N*/   ScRangeList aOldList(*pList);
/*N*/   pList->RemoveAll();                 //! oder die vorhandenen unten weglassen
/*N*/
/*N*/   for (USHORT nTab=0; nTab<=MAXTAB; nTab++)
/*N*/       if (bTabMarked[nTab])
/*N*/       {
/*N*/           ULONG nCount = aOldList.Count();
/*N*/           for (ULONG i=0; i<nCount; i++)
/*N*/           {
/*N*/               ScRange aRange = *aOldList.GetObject(i);
/*N*/               aRange.aStart.SetTab(nTab);
/*N*/               aRange.aEnd.SetTab(nTab);
/*N*/               pList->Append( aRange );
/*N*/           }
/*N*/       }
/*N*/ }

//STRIP001 USHORT ScMarkData::GetMarkColumnRanges( USHORT* pRanges )
//STRIP001 {
//STRIP001  if (bMarked)
//STRIP001      MarkToMulti();
//STRIP001
//STRIP001  if (!bMultiMarked)
//STRIP001      return 0;
//STRIP001
//STRIP001  DBG_ASSERT(pMultiSel, "bMultiMarked, aber pMultiSel == 0");
//STRIP001
//STRIP001  USHORT nRangeCnt = 0;
//STRIP001  USHORT nStart = 0;
//STRIP001  while (nStart<=MAXCOL)
//STRIP001  {
//STRIP001      while (nStart<MAXCOL && !pMultiSel[nStart].HasMarks())
//STRIP001          ++nStart;
//STRIP001      if (pMultiSel[nStart].HasMarks())
//STRIP001      {
//STRIP001          USHORT nEnd = nStart;
//STRIP001          while (nEnd<MAXCOL && pMultiSel[nEnd].HasMarks())
//STRIP001              ++nEnd;
//STRIP001          if (!pMultiSel[nEnd].HasMarks())
//STRIP001              --nEnd;
//STRIP001          pRanges[2*nRangeCnt  ] = nStart;
//STRIP001          pRanges[2*nRangeCnt+1] = nEnd;
//STRIP001          ++nRangeCnt;
//STRIP001          nStart = nEnd+1;
//STRIP001      }
//STRIP001      else
//STRIP001          nStart = MAXCOL+1;
//STRIP001  }
//STRIP001
//STRIP001  return nRangeCnt;
//STRIP001 }

//STRIP001 USHORT ScMarkData::GetMarkRowRanges( USHORT* pRanges )
//STRIP001 {
//STRIP001  if (bMarked)
//STRIP001      MarkToMulti();
//STRIP001
//STRIP001  if (!bMultiMarked)
//STRIP001      return 0;
//STRIP001
//STRIP001  DBG_ASSERT(pMultiSel, "bMultiMarked, aber pMultiSel == 0");
//STRIP001
//STRIP001  //  Welche Zeilen sind markiert?
//STRIP001
//STRIP001  BOOL*   bMarked = new BOOL[MAXROW+1];
//STRIP001  USHORT  nRow;
//STRIP001  USHORT  nCol;
//STRIP001  for (nRow=0; nRow<=MAXROW; nRow++)
//STRIP001      bMarked[nRow] = FALSE;
//STRIP001
//STRIP001  USHORT nTop;
//STRIP001  USHORT nBottom;
//STRIP001  for (nCol=0; nCol<=MAXCOL; nCol++)
//STRIP001  {
//STRIP001      ScMarkArrayIter aMarkIter( &pMultiSel[nCol] );
//STRIP001      while (aMarkIter.Next( nTop, nBottom ))
//STRIP001          for (nRow=nTop; nRow<=nBottom; nRow++)
//STRIP001              bMarked[nRow] = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  //  zu Bereichen zusammenfassen
//STRIP001
//STRIP001  USHORT nRangeCnt = 0;
//STRIP001  USHORT nStart = 0;
//STRIP001  while (nStart<=MAXROW)
//STRIP001  {
//STRIP001      while (nStart<MAXROW && !bMarked[nStart])
//STRIP001          ++nStart;
//STRIP001      if (bMarked[nStart])
//STRIP001      {
//STRIP001          USHORT nEnd = nStart;
//STRIP001          while (nEnd<MAXROW && bMarked[nEnd])
//STRIP001              ++nEnd;
//STRIP001          if (!bMarked[nEnd])
//STRIP001              --nEnd;
//STRIP001          pRanges[2*nRangeCnt  ] = nStart;
//STRIP001          pRanges[2*nRangeCnt+1] = nEnd;
//STRIP001          ++nRangeCnt;
//STRIP001          nStart = nEnd+1;
//STRIP001      }
//STRIP001      else
//STRIP001          nStart = MAXROW+1;
//STRIP001  }
//STRIP001
//STRIP001  delete[] bMarked;
//STRIP001  return nRangeCnt;
//STRIP001 }

/*N*/ BOOL ScMarkData::IsAllMarked( const ScRange& rRange ) const
/*N*/ {
/*N*/   if ( !bMultiMarked )
/*N*/       return FALSE;
/*N*/
/*N*/   DBG_ASSERT(pMultiSel, "bMultiMarked, aber pMultiSel == 0");
/*N*/
/*N*/   USHORT nStartCol = rRange.aStart.Col();
/*N*/   USHORT nStartRow = rRange.aStart.Row();
/*N*/   USHORT nEndCol = rRange.aEnd.Col();
/*N*/   USHORT nEndRow = rRange.aEnd.Row();
/*N*/   BOOL bOk = TRUE;
/*N*/   for (USHORT nCol=nStartCol; nCol<=nEndCol && bOk; nCol++)
/*N*/       if ( !pMultiSel[nCol].IsAllMarked( nStartRow, nEndRow ) )
/*N*/           bOk = FALSE;
/*N*/
/*N*/   return bOk;
/*N*/ }

//STRIP001 short ScMarkData::GetNextMarked( USHORT nCol, short nRow, BOOL bUp ) const
//STRIP001 {
//STRIP001  if ( !bMultiMarked )
//STRIP001      return nRow;
//STRIP001
//STRIP001  DBG_ASSERT(pMultiSel, "bMultiMarked, aber pMultiSel == 0");
//STRIP001
//STRIP001  return pMultiSel[nCol].GetNextMarked( nRow, bUp );
//STRIP001 }

/*N*/ BOOL ScMarkData::HasMultiMarks( USHORT nCol ) const
/*N*/ {
/*N*/   if ( !bMultiMarked )
/*N*/       return FALSE;
/*N*/
/*N*/   DBG_ASSERT(pMultiSel, "bMultiMarked, aber pMultiSel == 0");
/*N*/
/*N*/   return pMultiSel[nCol].HasMarks();
/*N*/ }

/*N*/ BOOL ScMarkData::HasAnyMultiMarks() const
/*N*/ {
/*N*/   if ( !bMultiMarked )
/*N*/       return FALSE;
/*N*/
/*N*/   DBG_ASSERT(pMultiSel, "bMultiMarked, aber pMultiSel == 0");
/*N*/
/*N*/   for (USHORT nCol=0; nCol<=MAXCOL; nCol++)
/*N*/       if ( pMultiSel[nCol].HasMarks() )
/*N*/           return TRUE;
/*N*/
/*N*/   return FALSE;       // nix
/*N*/ }

/*N*/ void ScMarkData::InsertTab( USHORT nTab )
/*N*/ {
/*N*/   for (USHORT i=MAXTAB; i>nTab; i--)
/*N*/       bTabMarked[i] = bTabMarked[i-1];
/*N*/   bTabMarked[nTab] = FALSE;
/*N*/ }

//STRIP001 void ScMarkData::DeleteTab( USHORT nTab )
//STRIP001 {
//STRIP001  for (USHORT i=nTab; i<MAXTAB; i++)
//STRIP001      bTabMarked[i] = bTabMarked[i+1];
//STRIP001  bTabMarked[MAXTAB] = FALSE;
//STRIP001 }





}
