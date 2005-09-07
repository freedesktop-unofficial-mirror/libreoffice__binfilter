/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_dpshttab.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 16:46:45 $
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

// INCLUDE --------------------------------------------------------------

#include <tools/debug.hxx>
#include <svtools/zforlist.hxx>

#include "dpshttab.hxx"
#include "document.hxx"
#include "collect.hxx"
// auto strip #include "cell.hxx"
#include "globstr.hrc"
namespace binfilter {

// -----------------------------------------------------------------------

/*N*/ class ScSheetDPData_Impl
/*N*/ {
/*N*/ public:
/*N*/   ScDocument*     pDoc;
/*N*/   ScRange         aRange;
/*N*/   ScQueryParam    aQuery;
/*N*/   long            nColCount;
/*N*/   BOOL            bIgnoreEmptyRows;
/*N*/   BOOL            bRepeatIfEmpty;
/*N*/   TypedStrCollection**    ppStrings;
/*N*/   BOOL*           pDateDim;
/*N*/   USHORT          nNextRow;       // for iterator, within range
/*N*/
/*N*/   ScSheetDPData_Impl() {}
/*N*/ };

// -----------------------------------------------------------------------

/*M*/ ScSheetDPData::ScSheetDPData( ScDocument* pD, const ScSheetSourceDesc& rDesc )
/*M*/     : pSpecial(NULL)
/*M*/ {
/*M*/   long nCount = rDesc.aSourceRange.aEnd.Col() - rDesc.aSourceRange.aStart.Col() + 1;
/*M*/   pImpl = new ScSheetDPData_Impl;
/*M*/   pImpl->pDoc = pD;
/*M*/   pImpl->aRange = rDesc.aSourceRange;
/*M*/   pImpl->aQuery = rDesc.aQueryParam;
/*M*/   pImpl->bIgnoreEmptyRows = FALSE;
/*M*/   pImpl->bRepeatIfEmpty = FALSE;
/*M*/   pImpl->nColCount = nCount;
/*M*/   pImpl->ppStrings = new TypedStrCollection*[nCount];
/*M*/   pImpl->pDateDim = NULL;
/*M*/   for (long i=0; i<nCount; i++)
/*M*/       pImpl->ppStrings[i] = NULL;
/*M*/
/*M*/   pImpl->nNextRow = pImpl->aRange.aStart.Row() + 1;
/*M*/
/*M*/     long nEntryCount(pImpl->aQuery.GetEntryCount());
/*M*/     pSpecial = new BOOL[nEntryCount];
/*M*/     for (long j = 0; j < nEntryCount; ++j )
/*M*/     {
/*M*/         ScQueryEntry& rEntry = pImpl->aQuery.GetEntry(j);
/*M*/         if (rEntry.bDoQuery)
/*M*/         {
/*M*/             pSpecial[j] = false;
/*M*/             if (!rEntry.bQueryByString)
/*M*/             {
/*M*/                 if (*rEntry.pStr == EMPTY_STRING &&
/*M*/                    ((rEntry.nVal == SC_EMPTYFIELDS) || (rEntry.nVal == SC_NONEMPTYFIELDS)))
/*M*/                     pSpecial[j] = true;
/*M*/             }
/*M*/             else
/*M*/             {
/*M*/               ULONG nIndex = 0;
/*M*/               rEntry.bQueryByString =
/*M*/                           !(pD->GetFormatTable()->
/*M*/                               IsNumberFormat(*rEntry.pStr, nIndex, rEntry.nVal));
/*M*/             }
/*M*/       }
/*M*/     }
/*M*/ }

/*N*/ ScSheetDPData::~ScSheetDPData()
/*N*/ {
/*N*/   for (long i=0; i<pImpl->nColCount; i++)
/*N*/       delete pImpl->ppStrings[i];
/*N*/   delete[] pImpl->ppStrings;
/*N*/   delete[] pImpl->pDateDim;
/*N*/   delete pImpl;
/*M*/     delete[] pSpecial;
/*N*/ }

/*N*/ void ScSheetDPData::DisposeData()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  for (long i=0; i<pImpl->nColCount; i++)
//STRIP001  {
//STRIP001      delete pImpl->ppStrings[i];
//STRIP001      pImpl->ppStrings[i] = NULL;
//STRIP001  }
/*N*/ }

/*N*/ long ScSheetDPData::GetColumnCount()
/*N*/ {
/*N*/   return pImpl->nColCount;
/*N*/ }

//STRIP001 BOOL lcl_HasQuery( const ScQueryParam& rParam )
//STRIP001 {
//STRIP001  return rParam.GetEntryCount() > 0 &&
//STRIP001          rParam.GetEntry(0).bDoQuery;
//STRIP001 }

/*N*/ const TypedStrCollection& ScSheetDPData::GetColumnEntries(long nColumn)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001
//STRIP001  DBG_ASSERT(nColumn>=0 && nColumn<pImpl->nColCount, "ScSheetDPData: wrong column");
//STRIP001
//STRIP001  if (!pImpl->ppStrings[nColumn])
//STRIP001  {
//STRIP001      TypedStrCollection* pColl = new TypedStrCollection;
//STRIP001
//STRIP001      //! document must have function to fill collection!!!
//STRIP001      String aDocStr;
//STRIP001      USHORT nDocCol = (USHORT)(pImpl->aRange.aStart.Col() + nColumn);
//STRIP001      USHORT nDocTab = pImpl->aRange.aStart.Tab();
//STRIP001      USHORT nStartRow = pImpl->aRange.aStart.Row()+1;    // start of data
//STRIP001      USHORT nEndRow = pImpl->aRange.aEnd.Row();
//STRIP001      USHORT nStartCol = pImpl->aRange.aStart.Col();
//STRIP001      USHORT nEndCol = pImpl->aRange.aEnd.Col();
//STRIP001      for (USHORT nRow = nStartRow; nRow <= nEndRow; nRow++)
//STRIP001      {
//STRIP001          if ( pImpl->bIgnoreEmptyRows &&
//STRIP001                  pImpl->pDoc->IsBlockEmpty( nDocTab, nStartCol, nRow, nEndCol, nRow ) )
//STRIP001          {
//STRIP001              //  ignore this (empty) row
//STRIP001              //! count and skip empty rows?
//STRIP001          }
//STRIP001          else if ( pImpl->bRepeatIfEmpty && nRow > nStartRow &&
//STRIP001                      !pImpl->pDoc->HasData( nDocCol, nRow, nDocTab ) )
//STRIP001          {
//STRIP001              //  ignore empty member (if it's not the first row)
//STRIP001          }
//STRIP001          else if ( lcl_HasQuery(pImpl->aQuery) &&
//STRIP001                      !pImpl->pDoc->ValidQuery( nRow, nDocTab, pImpl->aQuery, pSpecial ) )
//STRIP001          {
//STRIP001              //  this row is filtered out
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              TypedStrData* pNew;
//STRIP001              pImpl->pDoc->GetString( nDocCol, nRow, nDocTab, aDocStr );
//STRIP001              if ( pImpl->pDoc->HasValueData( nDocCol, nRow, nDocTab ) )
//STRIP001              {
//STRIP001                  double fVal = pImpl->pDoc->GetValue(ScAddress(nDocCol, nRow, nDocTab));
//STRIP001                  pNew = new TypedStrData( aDocStr, fVal, SC_STRTYPE_VALUE );
//STRIP001              }
//STRIP001              else
//STRIP001                  pNew = new TypedStrData( aDocStr );
//STRIP001
//STRIP001              if (!pColl->Insert(pNew))
//STRIP001                  delete pNew;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      pImpl->ppStrings[nColumn] = pColl;
//STRIP001  }
//STRIP001  return *pImpl->ppStrings[nColumn];
/*N*/ }

/*N*/ String ScSheetDPData::getDimensionName(long nColumn)
/*N*/ {
/*N*/   if (getIsDataLayoutDimension(nColumn))
/*N*/   {
/*N*/       //! different internal and display names?
/*N*/       //return "Data";
/*N*/       return ScGlobal::GetRscString(STR_PIVOT_DATA);
/*N*/   }
/*N*/   else if ( nColumn >= pImpl->nColCount )
/*N*/   {
/*?*/       DBG_ERROR("getDimensionName: invalid dimension");
/*?*/       return String();
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       USHORT nDocCol = (USHORT)(pImpl->aRange.aStart.Col() + nColumn);
/*N*/       USHORT nDocRow = pImpl->aRange.aStart.Row();
/*N*/       USHORT nDocTab = pImpl->aRange.aStart.Tab();
/*N*/       String aDocStr;
/*N*/       pImpl->pDoc->GetString( nDocCol, nDocRow, nDocTab, aDocStr );
/*N*/       return aDocStr;
/*N*/   }
/*N*/ }

/*N*/ BOOL lcl_HasDateFormat( ScDocument* pDoc, const ScRange& rRange )
/*N*/ {
/*N*/   //! iterate formats in range?
/*N*/
/*N*/   ScAddress aPos = rRange.aStart;
/*N*/   aPos.SetRow( aPos.Row() + 1 );      // below title
/*N*/   ULONG nFormat = pDoc->GetNumberFormat( aPos );
/*N*/   SvNumberFormatter* pFormatter = pDoc->GetFormatTable();
/*N*/   return ( pFormatter->GetType(nFormat) & NUMBERFORMAT_DATE ) != 0;
/*N*/ }

/*N*/ BOOL ScSheetDPData::IsDateDimension(long nDim)
/*N*/ {
/*N*/   if (getIsDataLayoutDimension(nDim))
/*N*/   {
/*N*/       return FALSE;
/*N*/   }
/*N*/   else if ( nDim >= pImpl->nColCount )
/*N*/   {
/*?*/       DBG_ERROR("IsDateDimension: invalid dimension");
/*?*/       return FALSE;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       if (!pImpl->pDateDim)
/*N*/       {
/*N*/           pImpl->pDateDim = new BOOL[pImpl->nColCount];
/*N*/           ScRange aTestRange = pImpl->aRange;
/*N*/           for (long i=0; i<pImpl->nColCount; i++)
/*N*/           {
/*N*/               USHORT nCol = (USHORT)( pImpl->aRange.aStart.Col() + i );
/*N*/               aTestRange.aStart.SetCol(nCol);
/*N*/               aTestRange.aEnd.SetCol(nCol);
/*N*/               pImpl->pDateDim[i] = lcl_HasDateFormat( pImpl->pDoc, aTestRange );
/*N*/           }
/*N*/       }
/*N*/       return pImpl->pDateDim[nDim];
/*N*/   }
/*N*/ }

/*N*/ UINT32 ScSheetDPData::GetNumberFormat(long nDim)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return 0; //STRIP001
//STRIP001  if (getIsDataLayoutDimension(nDim))
//STRIP001  {
//STRIP001      return 0;
//STRIP001  }
//STRIP001  else if ( nDim >= pImpl->nColCount )
//STRIP001  {
//STRIP001      DBG_ERROR("GetNumberFormat: invalid dimension");
//STRIP001      return 0;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      //  is queried only once per dimension from ScDPOutput -> no need to cache
//STRIP001
//STRIP001      ScAddress aPos = pImpl->aRange.aStart;
//STRIP001      aPos.SetCol( aPos.Col() + nDim );
//STRIP001      aPos.SetRow( aPos.Row() + 1 );      // below title
//STRIP001      return pImpl->pDoc->GetNumberFormat( aPos );
//STRIP001  }
/*N*/ }

/*N*/ BOOL ScSheetDPData::getIsDataLayoutDimension(long nColumn)
/*N*/ {
/*N*/   return ( nColumn == pImpl->nColCount );
/*N*/ }

/*N*/ void ScSheetDPData::SetEmptyFlags( BOOL bIgnoreEmptyRows, BOOL bRepeatIfEmpty )
/*N*/ {
/*N*/   pImpl->bIgnoreEmptyRows = bIgnoreEmptyRows;
/*N*/   pImpl->bRepeatIfEmpty   = bRepeatIfEmpty;
/*N*/ }

/*N*/ void ScSheetDPData::ResetIterator()
/*N*/ {
/*N*/   pImpl->nNextRow = pImpl->aRange.aStart.Row() + 1;
/*N*/ }

//STRIP001 void lcl_GetStringOrValue( ScDPItemData& rData, ScDocument* pDoc,
//STRIP001                          USHORT nCol, USHORT nRow, USHORT nTab,
//STRIP001                          BOOL bRepeatIfEmpty, USHORT nFirstDataRow )
//STRIP001 {
//STRIP001  if ( bRepeatIfEmpty )
//STRIP001  {
//STRIP001      //  use first non-empty entry
//STRIP001      //! just keep old ItemData ????
//STRIP001      //! otherwise count empty cells and subtract!
//STRIP001
//STRIP001      while ( !pDoc->HasData( nCol, nRow, nTab ) && nRow > nFirstDataRow )
//STRIP001          --nRow;
//STRIP001  }
//STRIP001
//STRIP001  BOOL bVal = pDoc->HasValueData( nCol, nRow, nTab );
//STRIP001  rData.bHasValue = bVal;
//STRIP001  if (bVal)
//STRIP001      rData.fValue = pDoc->GetValue( ScAddress( nCol, nRow, nTab ) );
//STRIP001  else
//STRIP001      pDoc->GetString( nCol, nRow, nTab, rData.aString );
//STRIP001 }

/*N*/ BOOL ScSheetDPData::GetNextRow( const ScDPTableIteratorParam& rParam )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE; //STRIP001
//STRIP001  if ( pImpl->nNextRow > pImpl->aRange.aEnd.Row() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  long i;
//STRIP001  long nStartCol = pImpl->aRange.aStart.Col();
//STRIP001  USHORT nDocTab = pImpl->aRange.aStart.Tab();
//STRIP001  USHORT nFirstDataRow = pImpl->aRange.aStart.Row() + 1;
//STRIP001
//STRIP001  BOOL bFilteredOut;
//STRIP001  do
//STRIP001  {
//STRIP001      if ( pImpl->bIgnoreEmptyRows )
//STRIP001      {
//STRIP001          USHORT nEndCol = pImpl->aRange.aEnd.Col();
//STRIP001          while ( pImpl->pDoc->IsBlockEmpty( nDocTab, (USHORT)nStartCol, pImpl->nNextRow,
//STRIP001                                              nEndCol, pImpl->nNextRow ) )
//STRIP001          {
//STRIP001              ++pImpl->nNextRow;
//STRIP001              if ( pImpl->nNextRow > pImpl->aRange.aEnd.Row() )
//STRIP001                  return FALSE;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      bFilteredOut = ( lcl_HasQuery(pImpl->aQuery) &&
//STRIP001              !pImpl->pDoc->ValidQuery( pImpl->nNextRow, nDocTab, pImpl->aQuery, pSpecial ) );
//STRIP001      if ( bFilteredOut )
//STRIP001      {
//STRIP001          ++pImpl->nNextRow;
//STRIP001          if ( pImpl->nNextRow > pImpl->aRange.aEnd.Row() )
//STRIP001              return FALSE;
//STRIP001      }
//STRIP001  }
//STRIP001  while (bFilteredOut);
//STRIP001
//STRIP001  //! use more efficient iterators
//STRIP001
//STRIP001  for (i=0; i<rParam.nColCount; i++)
//STRIP001  {
//STRIP001      long nDim = rParam.pCols[i];
//STRIP001      if ( getIsDataLayoutDimension(nDim) )
//STRIP001          rParam.pColData[i].SetString( String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("x")) );
//STRIP001      else
//STRIP001          lcl_GetStringOrValue( rParam.pColData[i], pImpl->pDoc,
//STRIP001                                  (USHORT)(nStartCol+nDim), pImpl->nNextRow, nDocTab,
//STRIP001                                  pImpl->bRepeatIfEmpty, nFirstDataRow );
//STRIP001  }
//STRIP001
//STRIP001  for (i=0; i<rParam.nRowCount; i++)
//STRIP001  {
//STRIP001      long nDim = rParam.pRows[i];
//STRIP001      if ( getIsDataLayoutDimension(nDim) )
//STRIP001          rParam.pRowData[i].SetString( String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("x")) );
//STRIP001      else
//STRIP001          lcl_GetStringOrValue( rParam.pRowData[i], pImpl->pDoc,
//STRIP001                                  (USHORT)(nStartCol+nDim), pImpl->nNextRow, nDocTab,
//STRIP001                                  pImpl->bRepeatIfEmpty, nFirstDataRow );
//STRIP001  }
//STRIP001
//STRIP001  for (i=0; i<rParam.nDatCount; i++)
//STRIP001  {
//STRIP001      long nDim = rParam.pDats[i];
//STRIP001      ScAddress aPos( (USHORT)(nStartCol+nDim), pImpl->nNextRow, nDocTab );
//STRIP001      ScBaseCell* pCell = pImpl->pDoc->GetCell( aPos );
//STRIP001      if ( !pCell || pCell->GetCellType() == CELLTYPE_NOTE )
//STRIP001          rParam.pValues[i].Set( 0.0, SC_VALTYPE_EMPTY );
//STRIP001      else if ( pCell->GetCellType() == CELLTYPE_FORMULA && ((ScFormulaCell*)pCell)->GetErrCode() )
//STRIP001          rParam.pValues[i].Set( 0.0, SC_VALTYPE_ERROR );
//STRIP001      else if ( pCell->HasValueData() )
//STRIP001      {
//STRIP001          //! GetValue method at BaseCell?
//STRIP001          DBG_ASSERT( pCell->GetCellType() == CELLTYPE_VALUE ||
//STRIP001                      pCell->GetCellType() == CELLTYPE_FORMULA, "wrong cell type" );
//STRIP001          double fVal;
//STRIP001          if ( pCell->GetCellType() == CELLTYPE_VALUE )
//STRIP001              fVal = ((ScValueCell*)pCell)->GetValue();
//STRIP001          else
//STRIP001              fVal = ((ScFormulaCell*)pCell)->GetValue();
//STRIP001          rParam.pValues[i].Set( fVal, SC_VALTYPE_VALUE );
//STRIP001      }
//STRIP001      else
//STRIP001          rParam.pValues[i].Set( 0.0, SC_VALTYPE_STRING );
//STRIP001  }
//STRIP001
//STRIP001  pImpl->nNextRow++;
//STRIP001  return TRUE;
/*N*/ }

// -----------------------------------------------------------------------







}
