/*************************************************************************
 *
 *  $RCSfile: sc_table3.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 11:10:54 $
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

#ifdef PCH
// auto strip #include "core_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------

#include <rtl/math.hxx>
#include <unotools/textsearch.hxx>
// auto strip #include <svtools/zforlist.hxx>
// auto strip #include <unotools/charclass.hxx>
#include <unotools/collatorwrapper.hxx>
// auto strip #include <com/sun/star/i18n/CollatorOptions.hpp>
#include <stdlib.h>
#ifndef _UNOTOOLS_TRANSLITERATIONWRAPPER_HXX
#include <unotools/transliterationwrapper.hxx>
#endif

// auto strip #include "table.hxx"
#include "scitems.hxx"
// auto strip #include "collect.hxx"
// auto strip #include "attrib.hxx"
#include "cell.hxx"
#include "document.hxx"
#include "globstr.hrc"
// auto strip #include "global.hxx"
// auto strip #include "stlpool.hxx"
// auto strip #include "compiler.hxx"
#include "patattr.hxx"
#include "subtotal.hxx"
#include "docoptio.hxx"
#include "markdata.hxx"
// auto strip #include "rangelst.hxx"
#include "attarray.hxx"
// auto strip #include "userlist.hxx"
// auto strip #include "progress.hxx"
#include "cellform.hxx"

#include <vector>
namespace binfilter {

// STATIC DATA -----------------------------------------------------------

const USHORT nMaxSorts = 3;     // maximale Anzahl Sortierkriterien in aSortParam

struct ScSortInfo
{
    ScBaseCell*     pCell;
    USHORT          nOrg;
    DECL_FIXEDMEMPOOL_NEWDEL( ScSortInfo );
};
/*N*/ const USHORT nMemPoolSortInfo = (0x8000 - 64) / sizeof(ScSortInfo);
/*N*/ IMPL_FIXEDMEMPOOL_NEWDEL( ScSortInfo, nMemPoolSortInfo, nMemPoolSortInfo )//STRIP008 ;

// END OF STATIC DATA -----------------------------------------------------


//STRIP001 class ScSortInfoArray
//STRIP001 {
//STRIP001 private:
//STRIP001  ScSortInfo**    pppInfo[nMaxSorts];
//STRIP001  USHORT          nCount;
//STRIP001  USHORT          nStart;
//STRIP001  USHORT          nUsedSorts;
//STRIP001
//STRIP001 public:
//STRIP001              ScSortInfoArray( USHORT nSorts, USHORT nInd1, USHORT nInd2 ) :
//STRIP001                      nCount( nInd2 - nInd1 + 1 ), nStart( nInd1 ),
//STRIP001                      nUsedSorts( Min( nSorts, nMaxSorts ) )
//STRIP001                  {
//STRIP001                      for ( USHORT nSort = 0; nSort < nUsedSorts; nSort++ )
//STRIP001                      {
//STRIP001                          ScSortInfo** ppInfo = new ScSortInfo* [nCount];
//STRIP001                          for ( USHORT j = 0; j < nCount; j++ )
//STRIP001                              ppInfo[j] = new ScSortInfo;
//STRIP001                          pppInfo[nSort] = ppInfo;
//STRIP001                      }
//STRIP001                  }
//STRIP001              ~ScSortInfoArray()
//STRIP001                  {
//STRIP001                      for ( USHORT nSort = 0; nSort < nUsedSorts; nSort++ )
//STRIP001                      {
//STRIP001                          ScSortInfo** ppInfo = pppInfo[nSort];
//STRIP001                          for ( USHORT j = 0; j < nCount; j++ )
//STRIP001                              delete ppInfo[j];
//STRIP001                          delete [] ppInfo;
//STRIP001                      }
//STRIP001                  }
//STRIP001  ScSortInfo* Get( USHORT nSort, USHORT nInd )
//STRIP001                  { return (pppInfo[nSort])[ nInd - nStart ]; }
//STRIP001  void        Swap( USHORT nInd1, USHORT nInd2 )
//STRIP001                  {
//STRIP001                      USHORT n1 = nInd1 - nStart;
//STRIP001                      USHORT n2 = nInd2 - nStart;
//STRIP001                      for ( USHORT nSort = 0; nSort < nUsedSorts; nSort++ )
//STRIP001                      {
//STRIP001                          ScSortInfo** ppInfo = pppInfo[nSort];
//STRIP001                          ScSortInfo* pTmp = ppInfo[n1];
//STRIP001                          ppInfo[n1] = ppInfo[n2];
//STRIP001                          ppInfo[n2] = pTmp;
//STRIP001                      }
//STRIP001                  }
//STRIP001  USHORT      GetUsedSorts() { return nUsedSorts; }
//STRIP001  ScSortInfo**    GetFirstArray() { return pppInfo[0]; }
//STRIP001  USHORT      GetStart() { return nStart; }
//STRIP001  USHORT      GetCount() { return nCount; }
//STRIP001 };

//STRIP001 ScSortInfoArray* ScTable::CreateSortInfoArray( USHORT nInd1, USHORT nInd2 )
//STRIP001 {
//STRIP001  USHORT nUsedSorts = 1;
//STRIP001  while ( nUsedSorts < nMaxSorts && aSortParam.bDoSort[nUsedSorts] )
//STRIP001      nUsedSorts++;
//STRIP001  ScSortInfoArray* pArray = new ScSortInfoArray( nUsedSorts, nInd1, nInd2 );
//STRIP001  if ( aSortParam.bByRow )
//STRIP001  {
//STRIP001      for ( USHORT nSort = 0; nSort < nUsedSorts; nSort++ )
//STRIP001      {
//STRIP001          USHORT nCol = aSortParam.nField[nSort];
//STRIP001          ScColumn* pCol = &aCol[nCol];
//STRIP001          for ( USHORT nRow = nInd1; nRow <= nInd2; nRow++ )
//STRIP001          {
//STRIP001 //2do: FillSortInfo an ScColumn und Array abklappern statt Search in GetCell
//STRIP001              ScSortInfo* pInfo = pArray->Get( nSort, nRow );
//STRIP001              pInfo->pCell = pCol->GetCell( nRow );
//STRIP001              pInfo->nOrg = nRow;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      for ( USHORT nSort = 0; nSort < nUsedSorts; nSort++ )
//STRIP001      {
//STRIP001          USHORT nRow = aSortParam.nField[nSort];
//STRIP001          for ( USHORT nCol = nInd1; nCol <= nInd2; nCol++ )
//STRIP001          {
//STRIP001              ScSortInfo* pInfo = pArray->Get( nSort, nCol );
//STRIP001              pInfo->pCell = GetCell( nCol, nRow );
//STRIP001              pInfo->nOrg = nCol;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return pArray;
//STRIP001 }


//STRIP001 BOOL ScTable::IsSortCollatorGlobal() const
//STRIP001 {
//STRIP001  return  pSortCollator == ScGlobal::pCollator ||
//STRIP001          pSortCollator == ScGlobal::pCaseCollator;
//STRIP001 }


//STRIP001 void ScTable::InitSortCollator( const ScSortParam& rPar )
//STRIP001 {
//STRIP001  if ( rPar.aCollatorLocale.Language.getLength() )
//STRIP001  {
//STRIP001      if ( !pSortCollator || IsSortCollatorGlobal() )
//STRIP001          pSortCollator = new CollatorWrapper( pDocument->GetServiceManager() );
//STRIP001      pSortCollator->loadCollatorAlgorithm( rPar.aCollatorAlgorithm,
//STRIP001          rPar.aCollatorLocale, (rPar.bCaseSens ? 0 : SC_COLLATOR_IGNORES) );
//STRIP001  }
//STRIP001  else
//STRIP001  {   // SYSTEM
//STRIP001      DestroySortCollator();
//STRIP001      pSortCollator = (rPar.bCaseSens ? ScGlobal::pCaseCollator :
//STRIP001          ScGlobal::pCollator);
//STRIP001  }
//STRIP001 }


/*N*/ void ScTable::DestroySortCollator()
/*N*/ {
/*N*/   if ( pSortCollator )
/*N*/   {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*?*/         if ( !IsSortCollatorGlobal() )
//STRIP001 /*?*/            delete pSortCollator;
//STRIP001 /*?*/        pSortCollator = NULL;
/*N*/   }
/*N*/ }


//STRIP001 void ScTable::SortReorder( ScSortInfoArray* pArray, ScProgress& rProgress )
//STRIP001 {
//STRIP001  BOOL bByRow = aSortParam.bByRow;
//STRIP001  USHORT nCount = pArray->GetCount();
//STRIP001  ScSortInfo** ppInfo = pArray->GetFirstArray();
//STRIP001  Table aTable( nCount );
//STRIP001  USHORT nPos;
//STRIP001  for ( nPos = 0; nPos < nCount; nPos++ )
//STRIP001  {
//STRIP001      aTable.Insert( ppInfo[nPos]->nOrg, (void*) ppInfo[nPos] );
//STRIP001  }
//STRIP001  USHORT nDest = pArray->GetStart();
//STRIP001  for ( nPos = 0; nPos < nCount; nPos++, nDest++ )
//STRIP001  {
//STRIP001      USHORT nOrg = ppInfo[nPos]->nOrg;
//STRIP001      if ( nDest != nOrg )
//STRIP001      {
//STRIP001          if ( bByRow )
//STRIP001              SwapRow( nDest, nOrg );
//STRIP001          else
//STRIP001              SwapCol( nDest, nOrg );
//STRIP001          // neue Position des weggeswapten eintragen
//STRIP001          ScSortInfo* p = ppInfo[nPos];
//STRIP001          p->nOrg = nDest;
//STRIP001          p = (ScSortInfo*) aTable.Replace( nDest, (void*) p );
//STRIP001          p->nOrg = nOrg;
//STRIP001          p = (ScSortInfo*) aTable.Replace( nOrg, (void*) p );
//STRIP001          DBG_ASSERT( p == ppInfo[nPos], "SortReorder: nOrg MisMatch" );
//STRIP001      }
//STRIP001      rProgress.SetStateOnPercent( nPos );
//STRIP001  }
//STRIP001 }

//STRIP001 short ScTable::CompareCell( USHORT nSort,
//STRIP001          ScBaseCell* pCell1, USHORT nCell1Col, USHORT nCell1Row,
//STRIP001          ScBaseCell* pCell2, USHORT nCell2Col, USHORT nCell2Row )
//STRIP001 {
//STRIP001  short nRes = 0;
//STRIP001
//STRIP001  CellType eType1, eType2;
//STRIP001  if (pCell1)
//STRIP001  {
//STRIP001      eType1 = pCell1->GetCellType();
//STRIP001      if (eType1 == CELLTYPE_NOTE)
//STRIP001          pCell1 = NULL;
//STRIP001  }
//STRIP001  if (pCell2)
//STRIP001  {
//STRIP001      eType2 = pCell2->GetCellType();
//STRIP001      if (eType2 == CELLTYPE_NOTE)
//STRIP001          pCell2 = NULL;
//STRIP001  }
//STRIP001
//STRIP001  if (pCell1)
//STRIP001  {
//STRIP001      if (pCell2)
//STRIP001      {
//STRIP001          BOOL bStr1 = ( eType1 != CELLTYPE_VALUE );
//STRIP001          if ( eType1 == CELLTYPE_FORMULA && ((ScFormulaCell*)pCell1)->IsValue() )
//STRIP001              bStr1 = FALSE;
//STRIP001          BOOL bStr2 = ( eType2 != CELLTYPE_VALUE );
//STRIP001          if ( eType2 == CELLTYPE_FORMULA && ((ScFormulaCell*)pCell2)->IsValue() )
//STRIP001              bStr2 = FALSE;
//STRIP001
//STRIP001          if ( bStr1 && bStr2 )           // nur Strings untereinander als String vergleichen!
//STRIP001          {
//STRIP001              String aStr1;
//STRIP001              String aStr2;
//STRIP001              if (eType1 == CELLTYPE_STRING)
//STRIP001                  ((ScStringCell*)pCell1)->GetString(aStr1);
//STRIP001              else
//STRIP001                  GetString(nCell1Col, nCell1Row, aStr1);
//STRIP001              if (eType2 == CELLTYPE_STRING)
//STRIP001                  ((ScStringCell*)pCell2)->GetString(aStr2);
//STRIP001              else
//STRIP001                  GetString(nCell2Col, nCell2Row, aStr2);
//STRIP001              BOOL bUserDef = aSortParam.bUserDef;
//STRIP001              if (bUserDef)
//STRIP001              {
//STRIP001                  ScUserListData* pData =
//STRIP001                      (ScUserListData*)(ScGlobal::GetUserList()->At(
//STRIP001                      aSortParam.nUserIndex));
//STRIP001                  if (pData)
//STRIP001                  {
//STRIP001                      if ( aSortParam.bCaseSens )
//STRIP001                          nRes = pData->Compare(aStr1, aStr2);
//STRIP001                      else
//STRIP001                          nRes = pData->ICompare(aStr1, aStr2);
//STRIP001                  }
//STRIP001                  else
//STRIP001                      bUserDef = FALSE;
//STRIP001
//STRIP001              }
//STRIP001              if (!bUserDef)
//STRIP001                  nRes = (short) pSortCollator->compareString( aStr1, aStr2 );
//STRIP001          }
//STRIP001          else if ( bStr1 )               // String <-> Zahl
//STRIP001              nRes = 1;                   // Zahl vorne
//STRIP001          else if ( bStr2 )               // Zahl <-> String
//STRIP001              nRes = -1;                  // Zahl vorne
//STRIP001          else                            // Zahlen untereinander
//STRIP001          {
//STRIP001              double nVal1;
//STRIP001              double nVal2;
//STRIP001              if (eType1 == CELLTYPE_VALUE)
//STRIP001                  nVal1 = ((ScValueCell*)pCell1)->GetValue();
//STRIP001              else if (eType1 == CELLTYPE_FORMULA)
//STRIP001                  nVal1 = ((ScFormulaCell*)pCell1)->GetValue();
//STRIP001              else
//STRIP001                  nVal1 = 0;
//STRIP001              if (eType2 == CELLTYPE_VALUE)
//STRIP001                  nVal2 = ((ScValueCell*)pCell2)->GetValue();
//STRIP001              else if (eType2 == CELLTYPE_FORMULA)
//STRIP001                  nVal2 = ((ScFormulaCell*)pCell2)->GetValue();
//STRIP001              else
//STRIP001                  nVal2 = 0;
//STRIP001              if (nVal1 < nVal2)
//STRIP001                  nRes = -1;
//STRIP001              else if (nVal1 > nVal2)
//STRIP001                  nRes = 1;
//STRIP001          }
//STRIP001          if ( !aSortParam.bAscending[nSort] )
//STRIP001              nRes = -nRes;
//STRIP001      }
//STRIP001      else
//STRIP001          nRes = -1;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if ( pCell2 )
//STRIP001          nRes = 1;
//STRIP001      else
//STRIP001          nRes = 0;                   // beide leer
//STRIP001  }
//STRIP001  return nRes;
//STRIP001 }

//STRIP001 short ScTable::Compare( ScSortInfoArray* pArray, USHORT nIndex1, USHORT nIndex2 )
//STRIP001 {
//STRIP001  short nRes;
//STRIP001  USHORT nSort = 0;
//STRIP001  do
//STRIP001  {
//STRIP001      ScSortInfo* pInfo1 = pArray->Get( nSort, nIndex1 );
//STRIP001      ScSortInfo* pInfo2 = pArray->Get( nSort, nIndex2 );
//STRIP001      if ( aSortParam.bByRow )
//STRIP001          nRes = CompareCell( nSort,
//STRIP001              pInfo1->pCell, aSortParam.nField[nSort], pInfo1->nOrg,
//STRIP001              pInfo2->pCell, aSortParam.nField[nSort], pInfo2->nOrg );
//STRIP001      else
//STRIP001          nRes = CompareCell( nSort,
//STRIP001              pInfo1->pCell, pInfo1->nOrg, aSortParam.nField[nSort],
//STRIP001              pInfo2->pCell, pInfo2->nOrg, aSortParam.nField[nSort] );
//STRIP001  } while ( nRes == 0 && ++nSort < pArray->GetUsedSorts() );
//STRIP001  return nRes;
//STRIP001 }

//STRIP001 void ScTable::QuickSort( ScSortInfoArray* pArray, short nLo, short nHi )
//STRIP001 {
//STRIP001  if ((nHi - nLo) == 1)
//STRIP001  {
//STRIP001      if (Compare(pArray, nLo, nHi) > 0)
//STRIP001          pArray->Swap( nLo, nHi );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      short ni = nLo;
//STRIP001      short nj = nHi;
//STRIP001      do
//STRIP001      {
//STRIP001          while ((ni <= nHi) && (Compare(pArray, ni, nLo)) < 0)
//STRIP001              ni++;
//STRIP001          while ((nj >= nLo) && (Compare(pArray, nLo, nj)) < 0)
//STRIP001              nj--;
//STRIP001          if (ni <= nj)
//STRIP001          {
//STRIP001              if (ni != nj)
//STRIP001                  pArray->Swap( ni, nj );
//STRIP001              ni++;
//STRIP001              nj--;
//STRIP001          }
//STRIP001      } while (ni < nj);
//STRIP001      if ((nj - nLo) < (nHi - ni))
//STRIP001      {
//STRIP001          if (nLo < nj)
//STRIP001              QuickSort(pArray, nLo, nj);
//STRIP001          if (ni < nHi)
//STRIP001              QuickSort(pArray, ni, nHi);
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if (ni < nHi)
//STRIP001              QuickSort(pArray, ni, nHi);
//STRIP001          if (nLo < nj)
//STRIP001              QuickSort(pArray, nLo, nj);
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void ScTable::SwapCol(USHORT nCol1, USHORT nCol2)
//STRIP001 {
//STRIP001  for (USHORT nRow = aSortParam.nRow1; nRow <= aSortParam.nRow2; nRow++)
//STRIP001  {
//STRIP001      aCol[nCol1].SwapCell(nRow, aCol[nCol2]);
//STRIP001      if (aSortParam.bIncludePattern)
//STRIP001      {
//STRIP001          const ScPatternAttr* pPat1 = GetPattern(nCol1, nRow);
//STRIP001          const ScPatternAttr* pPat2 = GetPattern(nCol2, nRow);
//STRIP001          if (pPat1 != pPat2)
//STRIP001          {
//STRIP001              SetPattern(nCol1, nRow, *pPat2, TRUE);
//STRIP001              SetPattern(nCol2, nRow, *pPat1, TRUE);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void ScTable::SwapRow(USHORT nRow1, USHORT nRow2)
//STRIP001 {
//STRIP001  for (USHORT nCol = aSortParam.nCol1; nCol <= aSortParam.nCol2; nCol++)
//STRIP001  {
//STRIP001      aCol[nCol].SwapRow(nRow1, nRow2);
//STRIP001      if (aSortParam.bIncludePattern)
//STRIP001      {
//STRIP001          const ScPatternAttr* pPat1 = GetPattern(nCol, nRow1);
//STRIP001          const ScPatternAttr* pPat2 = GetPattern(nCol, nRow2);
//STRIP001          if (pPat1 != pPat2)
//STRIP001          {
//STRIP001              SetPattern(nCol, nRow1, *pPat2, TRUE);
//STRIP001              SetPattern(nCol, nRow2, *pPat1, TRUE);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if (bGlobalKeepQuery && pRowFlags)
//STRIP001  {
//STRIP001      BYTE nFlags1 = pRowFlags[nRow1] & ( CR_HIDDEN | CR_FILTERED );
//STRIP001      BYTE nFlags2 = pRowFlags[nRow2] & ( CR_HIDDEN | CR_FILTERED );
//STRIP001      pRowFlags[nRow1] = (pRowFlags[nRow1] & ~( CR_HIDDEN | CR_FILTERED )) | nFlags2;
//STRIP001      pRowFlags[nRow2] = (pRowFlags[nRow2] & ~( CR_HIDDEN | CR_FILTERED )) | nFlags1;
//STRIP001  }
//STRIP001 }

//STRIP001 short ScTable::Compare(USHORT nIndex1, USHORT nIndex2)
//STRIP001 {
//STRIP001  short nRes;
//STRIP001  USHORT nSort = 0;
//STRIP001  if (aSortParam.bByRow)
//STRIP001  {
//STRIP001      do
//STRIP001      {
//STRIP001          USHORT nCol = aSortParam.nField[nSort];
//STRIP001          ScBaseCell* pCell1 = aCol[nCol].GetCell( nIndex1 );
//STRIP001          ScBaseCell* pCell2 = aCol[nCol].GetCell( nIndex2 );
//STRIP001          nRes = CompareCell( nSort, pCell1, nCol, nIndex1, pCell2, nCol, nIndex2 );
//STRIP001      } while ( nRes == 0 && ++nSort < nMaxSorts && aSortParam.bDoSort[nSort] );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      do
//STRIP001      {
//STRIP001          USHORT nRow = aSortParam.nField[nSort];
//STRIP001          ScBaseCell* pCell1 = aCol[nIndex1].GetCell( nRow );
//STRIP001          ScBaseCell* pCell2 = aCol[nIndex2].GetCell( nRow );
//STRIP001          nRes = CompareCell( nSort, pCell1, nIndex1, nRow, pCell2, nIndex2, nRow );
//STRIP001      } while ( nRes == 0 && ++nSort < nMaxSorts && aSortParam.bDoSort[nSort] );
//STRIP001  }
//STRIP001  return nRes;
//STRIP001 }

//STRIP001 BOOL ScTable::IsSorted( USHORT nStart, USHORT nEnd )                 // ueber aSortParam
//STRIP001 {
//STRIP001  for (USHORT i=nStart; i<nEnd; i++)
//STRIP001  {
//STRIP001      if (Compare( i, i+1 ) > 0)
//STRIP001          return FALSE;
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 void ScTable::DecoladeRow( ScSortInfoArray* pArray, USHORT nRow1, USHORT nRow2 )
//STRIP001 {
//STRIP001  USHORT nRow;
//STRIP001  USHORT nMax = nRow2 - nRow1;
//STRIP001  for (USHORT i = nRow1; (i + 4) <= nRow2; i += 4)
//STRIP001  {
//STRIP001      nRow = rand() % nMax;
//STRIP001      pArray->Swap(i, nRow1 + nRow);
//STRIP001  }
//STRIP001 }

//STRIP001 void ScTable::Sort(const ScSortParam& rSortParam, BOOL bKeepQuery)
//STRIP001 {
//STRIP001  aSortParam = rSortParam;
//STRIP001  InitSortCollator( rSortParam );
//STRIP001  bGlobalKeepQuery = bKeepQuery;
//STRIP001  if (rSortParam.bByRow)
//STRIP001  {
//STRIP001      USHORT nLastRow = 0;
//STRIP001      for (USHORT nCol = aSortParam.nCol1; nCol <= aSortParam.nCol2; nCol++)
//STRIP001          nLastRow = Max(nLastRow, aCol[nCol].GetLastDataPos());
//STRIP001      nLastRow = Min(nLastRow, aSortParam.nRow2);
//STRIP001      USHORT nRow1 = (rSortParam.bHasHeader ?
//STRIP001          aSortParam.nRow1 + 1 : aSortParam.nRow1);
//STRIP001      if (!IsSorted(nRow1, nLastRow))
//STRIP001      {
//STRIP001          ScProgress aProgress( pDocument->GetDocumentShell(),
//STRIP001                                  ScGlobal::GetRscString(STR_PROGRESS_SORTING), nLastRow - nRow1 );
//STRIP001          ScSortInfoArray* pArray = CreateSortInfoArray( nRow1, nLastRow );
//STRIP001          if ( nLastRow - nRow1 > 255 )
//STRIP001              DecoladeRow( pArray, nRow1, nLastRow );
//STRIP001          QuickSort( pArray, nRow1, nLastRow );
//STRIP001          SortReorder( pArray, aProgress );
//STRIP001          delete pArray;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      USHORT nLastCol;
//STRIP001      for (nLastCol = aSortParam.nCol2;
//STRIP001           (nLastCol > aSortParam.nCol1) && aCol[nLastCol].IsEmptyBlock(aSortParam.nRow1, aSortParam.nRow2); nLastCol--)
//STRIP001      {
//STRIP001      }
//STRIP001      USHORT nCol1 = (rSortParam.bHasHeader ?
//STRIP001          aSortParam.nCol1 + 1 : aSortParam.nCol1);
//STRIP001      if (!IsSorted(nCol1, nLastCol))
//STRIP001      {
//STRIP001          ScProgress aProgress( pDocument->GetDocumentShell(),
//STRIP001                                  ScGlobal::GetRscString(STR_PROGRESS_SORTING), nLastCol - nCol1 );
//STRIP001          ScSortInfoArray* pArray = CreateSortInfoArray( nCol1, nLastCol );
//STRIP001          QuickSort( pArray, nCol1, nLastCol );
//STRIP001          SortReorder( pArray, aProgress );
//STRIP001          delete pArray;
//STRIP001      }
//STRIP001  }
//STRIP001  DestroySortCollator();
//STRIP001 }


//      Testen, ob beim Loeschen von Zwischenergebnissen andere Daten mit geloescht werden
//      (fuer Hinweis-Box)

//STRIP001 BOOL ScTable::TestRemoveSubTotals( const ScSubTotalParam& rParam )
//STRIP001 {
//STRIP001  USHORT nStartCol = rParam.nCol1;
//STRIP001  USHORT nStartRow = rParam.nRow1 + 1;        // Header
//STRIP001  USHORT nEndCol   = rParam.nCol2;
//STRIP001  USHORT nEndRow   = rParam.nRow2;
//STRIP001
//STRIP001  USHORT nCol;
//STRIP001  USHORT nRow;
//STRIP001  ScBaseCell* pCell;
//STRIP001
//STRIP001  BOOL bWillDelete = FALSE;
//STRIP001  for ( nCol=nStartCol; nCol<=nEndCol && !bWillDelete; nCol++ )
//STRIP001  {
//STRIP001      ScColumnIterator aIter( &aCol[nCol],nStartRow,nEndRow );
//STRIP001      while ( aIter.Next( nRow, pCell ) && !bWillDelete )
//STRIP001      {
//STRIP001          if ( pCell->GetCellType() == CELLTYPE_FORMULA )
//STRIP001              if (((ScFormulaCell*)pCell)->IsSubTotal())
//STRIP001              {
//STRIP001                  for (USHORT nTestCol=0; nTestCol<=MAXCOL; nTestCol++)
//STRIP001                      if (nTestCol<nStartCol || nTestCol>nEndCol)
//STRIP001                          if (aCol[nTestCol].HasDataAt(nRow))
//STRIP001                              bWillDelete = TRUE;
//STRIP001              }
//STRIP001      }
//STRIP001  }
//STRIP001  return bWillDelete;
//STRIP001 }

//      alte Ergebnisse loeschen
//      rParam.nRow2 wird veraendert !

//STRIP001 void ScTable::RemoveSubTotals( ScSubTotalParam& rParam )
//STRIP001 {
//STRIP001  USHORT nStartCol = rParam.nCol1;
//STRIP001  USHORT nStartRow = rParam.nRow1 + 1;        // Header
//STRIP001  USHORT nEndCol   = rParam.nCol2;
//STRIP001  USHORT nEndRow   = rParam.nRow2;            // wird veraendert
//STRIP001
//STRIP001  USHORT nCol;
//STRIP001  USHORT nRow;
//STRIP001  ScBaseCell* pCell;
//STRIP001
//STRIP001  for ( nCol=nStartCol; nCol<=nEndCol; nCol++ )
//STRIP001  {
//STRIP001      ScColumnIterator aIter( &aCol[nCol],nStartRow,nEndRow );
//STRIP001      while ( aIter.Next( nRow, pCell ) )
//STRIP001      {
//STRIP001          if ( pCell->GetCellType() == CELLTYPE_FORMULA )
//STRIP001              if (((ScFormulaCell*)pCell)->IsSubTotal())
//STRIP001              {
//STRIP001                  SetRowFlags(nRow+1,GetRowFlags(nRow+1)&(~CR_MANUALBREAK));
//STRIP001                  pDocument->DeleteRow( 0,nTab, MAXCOL,nTab, nRow, 1 );
//STRIP001                  --nEndRow;
//STRIP001                  aIter = ScColumnIterator( &aCol[nCol],nRow,nEndRow );
//STRIP001              }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  rParam.nRow2 = nEndRow;                 // neues Ende
//STRIP001 }

//  harte Zahlenformate loeschen (fuer Ergebnisformeln)

//STRIP001 void lcl_RemoveNumberFormat( ScTable* pTab, USHORT nCol, USHORT nRow )
//STRIP001 {
//STRIP001  const ScPatternAttr* pPattern = pTab->GetPattern( nCol, nRow );
//STRIP001  if ( pPattern->GetItemSet().GetItemState( ATTR_VALUE_FORMAT, FALSE )
//STRIP001          == SFX_ITEM_SET )
//STRIP001  {
//STRIP001      ScPatternAttr aNewPattern( *pPattern );
//STRIP001      SfxItemSet& rSet = aNewPattern.GetItemSet();
//STRIP001      rSet.ClearItem( ATTR_VALUE_FORMAT );
//STRIP001      rSet.ClearItem( ATTR_LANGUAGE_FORMAT );
//STRIP001      pTab->SetPattern( nCol, nRow, aNewPattern, TRUE );
//STRIP001  }
//STRIP001 }


// at least MSC needs this at linkage level to be able to use it in a template
//STRIP001 typedef struct lcl_ScTable_DoSubTotals_RowEntry
//STRIP001 {
//STRIP001     USHORT  nGroupNo;
//STRIP001     USHORT  nSubStartRow;
//STRIP001     USHORT  nDestRow;
//STRIP001     USHORT  nFuncStart;
//STRIP001     USHORT  nFuncEnd;
//STRIP001 } RowEntry;

//      neue Zwischenergebnisse
//      rParam.nRow2 wird veraendert !

//STRIP001 BOOL ScTable::DoSubTotals( ScSubTotalParam& rParam )
//STRIP001 {
//STRIP001  USHORT nStartCol = rParam.nCol1;
//STRIP001  USHORT nStartRow = rParam.nRow1 + 1;        // Header
//STRIP001  USHORT nEndCol   = rParam.nCol2;
//STRIP001  USHORT nEndRow   = rParam.nRow2;            // wird veraendert
//STRIP001  USHORT i;
//STRIP001
//STRIP001  //  Leerzeilen am Ende weglassen,
//STRIP001  //  damit alle Ueberlaeufe (MAXROW) bei InsertRow gefunden werden (#35180#)
//STRIP001  //  Wenn sortiert wurde, sind alle Leerzeilen am Ende.
//STRIP001  USHORT nEmpty = GetEmptyLinesInBlock( nStartCol, nStartRow, nEndCol, nEndRow, DIR_BOTTOM );
//STRIP001  nEndRow -= nEmpty;
//STRIP001
//STRIP001  USHORT nLevelCount = 0;             // Anzahl Gruppierungen
//STRIP001  BOOL bDoThis = TRUE;
//STRIP001  for (i=0; i<MAXSUBTOTAL && bDoThis; i++)
//STRIP001      if (rParam.bGroupActive[i])
//STRIP001          nLevelCount = i+1;
//STRIP001      else
//STRIP001          bDoThis = FALSE;
//STRIP001
//STRIP001  if (nLevelCount==0)                 // nichts tun
//STRIP001      return TRUE;
//STRIP001
//STRIP001  USHORT*         nGroupCol = rParam.nField;  // Spalten nach denen
//STRIP001                                              // gruppiert wird
//STRIP001
//STRIP001  //  #44444# Durch (leer) als eigene Kategorie muss immer auf
//STRIP001  //  Teilergebniszeilen aus den anderen Spalten getestet werden
//STRIP001  //  (frueher nur, wenn eine Spalte mehrfach vorkam)
//STRIP001  BOOL bTestPrevSub = ( nLevelCount > 1 );
//STRIP001
//STRIP001  String  aSubString;
//STRIP001  String  aOutString;
//STRIP001
//STRIP001  BOOL bIgnoreCase = !rParam.bCaseSens;
//STRIP001
//STRIP001  String *pCompString[MAXSUBTOTAL];               // Pointer wegen Compiler-Problemen
//STRIP001  for (i=0; i<MAXSUBTOTAL; i++)
//STRIP001      pCompString[i] = new String;
//STRIP001
//STRIP001                              //! sortieren?
//STRIP001
//STRIP001  ScStyleSheet* pStyle = (ScStyleSheet*) pDocument->GetStyleSheetPool()->Find(
//STRIP001                              ScGlobal::GetRscString(STR_STYLENAME_RESULT), SFX_STYLE_FAMILY_PARA );
//STRIP001
//STRIP001  BOOL bSpaceLeft = TRUE;                                         // Erfolg beim Einfuegen?
//STRIP001
//STRIP001     // #90279# For performance reasons collect formula entries so their
//STRIP001     // references don't have to be tested for updates each time a new row is
//STRIP001     // inserted
//STRIP001     RowEntry aRowEntry;
//STRIP001     ::std::vector< RowEntry > aRowVector;
//STRIP001
//STRIP001  for (USHORT nLevel=0; nLevel<=nLevelCount && bSpaceLeft; nLevel++)      // incl. Gesamtergebnis
//STRIP001  {
//STRIP001      BOOL bTotal = ( nLevel == nLevelCount );
//STRIP001      aRowEntry.nGroupNo = bTotal ? 0 : (nLevelCount-nLevel-1);
//STRIP001
//STRIP001         // how many results per level
//STRIP001         USHORT nResCount         = rParam.nSubTotals[aRowEntry.nGroupNo];
//STRIP001         // result functions
//STRIP001         ScSubTotalFunc* eResFunc = rParam.pFunctions[aRowEntry.nGroupNo];
//STRIP001
//STRIP001      if (nResCount)                                      // sonst nur sortieren
//STRIP001      {
//STRIP001          for (i=0; i<=aRowEntry.nGroupNo; i++)
//STRIP001          {
//STRIP001              GetString( nGroupCol[i], nStartRow, aSubString );
//STRIP001                 if ( bIgnoreCase )
//STRIP001                     *pCompString[i] = ScGlobal::pCharClass->upper( aSubString );
//STRIP001                 else
//STRIP001                     *pCompString[i] = aSubString;
//STRIP001          }                                                   // aSubString bleibt auf dem letzten stehen
//STRIP001
//STRIP001          BOOL bBlockVis = FALSE;             // Gruppe eingeblendet?
//STRIP001          aRowEntry.nSubStartRow = nStartRow;
//STRIP001          for (USHORT nRow=nStartRow; nRow<=nEndRow+1 && bSpaceLeft; nRow++)
//STRIP001          {
//STRIP001                 BOOL bChanged;
//STRIP001              if (nRow>nEndRow)
//STRIP001                  bChanged = TRUE;
//STRIP001              else
//STRIP001              {
//STRIP001                  bChanged = FALSE;
//STRIP001                  if (!bTotal)
//STRIP001                  {
//STRIP001                         String aString;
//STRIP001                      for (i=0; i<=aRowEntry.nGroupNo && !bChanged; i++)
//STRIP001                      {
//STRIP001                          GetString( nGroupCol[i], nRow, aString );
//STRIP001                          if (bIgnoreCase)
//STRIP001                              ScGlobal::pCharClass->toUpper( aString );
//STRIP001                          //  #41427# wenn sortiert, ist "leer" eine eigene Gruppe
//STRIP001                          //  sonst sind leere Zellen unten erlaubt
//STRIP001                          bChanged = ( ( aString.Len() || rParam.bDoSort ) &&
//STRIP001                                          aString != *pCompString[i] );
//STRIP001                      }
//STRIP001                      if ( bChanged && bTestPrevSub )
//STRIP001                      {
//STRIP001                             // No group change on rows that will contain subtotal formulas
//STRIP001                             for ( ::std::vector< RowEntry >::const_iterator
//STRIP001                                     iEntry( aRowVector.begin());
//STRIP001                                     iEntry != aRowVector.end(); ++iEntry)
//STRIP001                             {
//STRIP001                                 if ( iEntry->nDestRow == nRow )
//STRIP001                                 {
//STRIP001                                     bChanged = FALSE;
//STRIP001                                     break;
//STRIP001                                 }
//STRIP001                             }
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001              if ( bChanged )
//STRIP001              {
//STRIP001                  aRowEntry.nDestRow   = nRow;
//STRIP001                  aRowEntry.nFuncStart = aRowEntry.nSubStartRow;
//STRIP001                  aRowEntry.nFuncEnd   = nRow-1;
//STRIP001
//STRIP001                     bSpaceLeft = pDocument->InsertRow( 0, nTab, MAXCOL, nTab,
//STRIP001                             aRowEntry.nDestRow, 1 );
//STRIP001                  DBShowRow( aRowEntry.nDestRow, bBlockVis );
//STRIP001                  bBlockVis = FALSE;
//STRIP001                     if ( rParam.bPagebreak && nRow < MAXROW &&
//STRIP001                             aRowEntry.nSubStartRow != nStartRow && nLevel == 0)
//STRIP001                         SetRowFlags( aRowEntry.nSubStartRow,
//STRIP001                                 GetRowFlags(aRowEntry.nSubStartRow) |
//STRIP001                                 CR_MANUALBREAK);
//STRIP001
//STRIP001                  if (bSpaceLeft)
//STRIP001                  {
//STRIP001                         for ( ::std::vector< RowEntry >::iterator iMove(
//STRIP001                                     aRowVector.begin() );
//STRIP001                                 iMove != aRowVector.end(); ++iMove)
//STRIP001                         {
//STRIP001                             if ( aRowEntry.nDestRow <= iMove->nSubStartRow )
//STRIP001                                 ++iMove->nSubStartRow;
//STRIP001                             if ( aRowEntry.nDestRow <= iMove->nDestRow )
//STRIP001                                 ++iMove->nDestRow;
//STRIP001                             if ( aRowEntry.nDestRow <= iMove->nFuncStart )
//STRIP001                                 ++iMove->nFuncStart;
//STRIP001                             if ( aRowEntry.nDestRow <= iMove->nFuncEnd )
//STRIP001                                 ++iMove->nFuncEnd;
//STRIP001                         }
//STRIP001                         // collect formula positions
//STRIP001                         aRowVector.push_back( aRowEntry );
//STRIP001
//STRIP001                      if (bTotal)     // "Gesamtergebnis"
//STRIP001                          aOutString = ScGlobal::GetRscString( STR_TABLE_GESAMTERGEBNIS );
//STRIP001                      else
//STRIP001                      {               // " Ergebnis"
//STRIP001                          aOutString = aSubString;
//STRIP001                          if (!aOutString.Len())
//STRIP001                              aOutString = ScGlobal::GetRscString( STR_EMPTYDATA );
//STRIP001                          aOutString += ' ';
//STRIP001                          USHORT nStrId = STR_TABLE_ERGEBNIS;
//STRIP001                          if ( nResCount == 1 )
//STRIP001                              switch ( eResFunc[0] )
//STRIP001                              {
//STRIP001                                  case SUBTOTAL_FUNC_AVE:     nStrId = STR_FUN_TEXT_AVG;      break;
//STRIP001                                  case SUBTOTAL_FUNC_CNT:
//STRIP001                                  case SUBTOTAL_FUNC_CNT2:    nStrId = STR_FUN_TEXT_COUNT;    break;
//STRIP001                                  case SUBTOTAL_FUNC_MAX:     nStrId = STR_FUN_TEXT_MAX;      break;
//STRIP001                                  case SUBTOTAL_FUNC_MIN:     nStrId = STR_FUN_TEXT_MIN;      break;
//STRIP001                                  case SUBTOTAL_FUNC_PROD:    nStrId = STR_FUN_TEXT_PRODUCT;  break;
//STRIP001                                  case SUBTOTAL_FUNC_STD:
//STRIP001                                  case SUBTOTAL_FUNC_STDP:    nStrId = STR_FUN_TEXT_STDDEV;   break;
//STRIP001                                  case SUBTOTAL_FUNC_SUM:     nStrId = STR_FUN_TEXT_SUM;      break;
//STRIP001                                  case SUBTOTAL_FUNC_VAR:
//STRIP001                                  case SUBTOTAL_FUNC_VARP:    nStrId = STR_FUN_TEXT_VAR;      break;
//STRIP001                              }
//STRIP001                          aOutString += ScGlobal::GetRscString( nStrId );
//STRIP001                      }
//STRIP001                      SetString( nGroupCol[aRowEntry.nGroupNo], aRowEntry.nDestRow, nTab, aOutString );
//STRIP001                      ApplyStyle( nGroupCol[aRowEntry.nGroupNo], aRowEntry.nDestRow, *pStyle );
//STRIP001
//STRIP001 /*                       if (rParam.bPagebreak && nRow < MAXROW)
//STRIP001                      {
//STRIP001                          BYTE nFlags = GetRowFlags( nRow+1 );
//STRIP001                          nFlags |= CR_MANUALBREAK;
//STRIP001                          SetRowFlags( nRow+1, nFlags );
//STRIP001                      }
//STRIP001 */
//STRIP001                      ++nRow;
//STRIP001                      ++nEndRow;
//STRIP001                      aRowEntry.nSubStartRow = nRow;
//STRIP001                      for (i=0; i<=aRowEntry.nGroupNo; i++)
//STRIP001                      {
//STRIP001                          GetString( nGroupCol[i], nRow, aSubString );
//STRIP001                             if ( bIgnoreCase )
//STRIP001                                 *pCompString[i] = ScGlobal::pCharClass->upper( aSubString );
//STRIP001                             else
//STRIP001                                 *pCompString[i] = aSubString;
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001              if (!pRowFlags)
//STRIP001                  bBlockVis = TRUE;
//STRIP001              else
//STRIP001                  if ( (pRowFlags[nRow] & CR_FILTERED) == 0 )
//STRIP001                      bBlockVis = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001 //           DBG_ERROR( "nSubTotals==0 bei DoSubTotals" );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001     // now insert the formulas
//STRIP001     ComplRefData aRef;
//STRIP001     aRef.InitFlags();
//STRIP001     aRef.Ref1.nTab = nTab;
//STRIP001     aRef.Ref2.nTab = nTab;
//STRIP001     for ( ::std::vector< RowEntry >::const_iterator iEntry( aRowVector.begin());
//STRIP001             iEntry != aRowVector.end(); ++iEntry)
//STRIP001     {
//STRIP001         USHORT nResCount         = rParam.nSubTotals[iEntry->nGroupNo];
//STRIP001         USHORT* nResCols         = rParam.pSubTotals[iEntry->nGroupNo];
//STRIP001         ScSubTotalFunc* eResFunc = rParam.pFunctions[iEntry->nGroupNo];
//STRIP001         for ( USHORT i=0; i < nResCount; ++i )
//STRIP001         {
//STRIP001             aRef.Ref1.nCol = nResCols[i];
//STRIP001             aRef.Ref1.nRow = iEntry->nFuncStart;
//STRIP001             aRef.Ref2.nCol = nResCols[i];
//STRIP001             aRef.Ref2.nRow = iEntry->nFuncEnd;
//STRIP001
//STRIP001             ScTokenArray aArr;
//STRIP001             aArr.AddOpCode( ocSubTotal );
//STRIP001             aArr.AddOpCode( ocOpen );
//STRIP001             aArr.AddDouble( (double) eResFunc[i] );
//STRIP001             aArr.AddOpCode( ocSep );
//STRIP001             aArr.AddDoubleReference( aRef );
//STRIP001             aArr.AddOpCode( ocClose );
//STRIP001             aArr.AddOpCode( ocStop );
//STRIP001             ScBaseCell* pCell = new ScFormulaCell( pDocument, ScAddress(
//STRIP001                         nResCols[i], iEntry->nDestRow, nTab), &aArr );
//STRIP001             PutCell( nResCols[i], iEntry->nDestRow, pCell );
//STRIP001
//STRIP001             if ( nResCols[i] != nGroupCol[iEntry->nGroupNo] )
//STRIP001             {
//STRIP001                 ApplyStyle( nResCols[i], iEntry->nDestRow, *pStyle );
//STRIP001
//STRIP001                 //   Zahlformat loeschen
//STRIP001                 lcl_RemoveNumberFormat( this, nResCols[i], iEntry->nDestRow );
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001     }
//STRIP001
//STRIP001  //!     je nach Einstellung Zwischensummen-Zeilen nach oben verschieben ?
//STRIP001
//STRIP001  //!     Outlines direkt erzeugen?
//STRIP001
//STRIP001  if (bSpaceLeft)
//STRIP001      DoAutoOutline( nStartCol, nStartRow, nEndCol, nEndRow );
//STRIP001
//STRIP001  for (i=0; i<MAXSUBTOTAL; i++)
//STRIP001      delete pCompString[i];
//STRIP001
//STRIP001  rParam.nRow2 = nEndRow;                 // neues Ende
//STRIP001  return bSpaceLeft;
//STRIP001 }


/*N*/ BOOL ScTable::ValidQuery(USHORT nRow, const ScQueryParam& rParam,
/*N*/         BOOL* pSpecial /* =NULL */ , ScBaseCell* pCell /* =NULL */ ,
/*N*/         BOOL* pbTestEqualCondition /* = NULL */ )
/*N*/ {
/*N*/   if (!rParam.GetEntry(0).bDoQuery)
/*N*/       return TRUE;
/*N*/
/*N*/   //---------------------------------------------------------------
/*N*/
/*N*/   const USHORT nFixedBools = 32;
/*N*/   BOOL aBool[nFixedBools];
/*N*/     BOOL aTest[nFixedBools];
/*N*/   USHORT nEntryCount = rParam.GetEntryCount();
/*N*/     BOOL* pPasst = ( nEntryCount <= nFixedBools ? &aBool[0] : new BOOL[nEntryCount] );
/*N*/     BOOL* pTest = ( nEntryCount <= nFixedBools ? &aTest[0] : new BOOL[nEntryCount] );
/*N*/
/*N*/   short   nPos = -1;
/*N*/   USHORT  i    = 0;
/*N*/   BOOL    bMatchWholeCell = pDocument->GetDocOptions().IsMatchWholeCell();
/*N*/   CollatorWrapper* pCollator = (rParam.bCaseSens ? ScGlobal::pCaseCollator :
/*N*/       ScGlobal::pCollator);
/*N*/     ::utl::TransliterationWrapper* pTransliteration = (rParam.bCaseSens ?
/*N*/         ScGlobal::pCaseTransliteration : ScGlobal::pTransliteration);
/*N*/
/*N*/   while ( (i < nEntryCount) && rParam.GetEntry(i).bDoQuery )
/*N*/   {
/*N*/       ScQueryEntry& rEntry = rParam.GetEntry(i);
/*N*/         // we can only handle one single direct query
/*N*/         if ( !pCell || i > 0 )
/*?*/             pCell = GetCell( rEntry.nField, nRow );
/*N*/
/*N*/       BOOL bOk = FALSE;
/*N*/         BOOL bTestEqual = FALSE;
/*N*/
/*N*/       if ( pSpecial && pSpecial[i] )
/*N*/       {
/*?*/           if (rEntry.nVal == SC_EMPTYFIELDS)
/*?*/               bOk = !( aCol[rEntry.nField].HasDataAt( nRow ) );
/*?*/           else // if (rEntry.nVal == SC_NONEMPTYFIELDS)
/*?*/               bOk = aCol[rEntry.nField].HasDataAt( nRow );
/*N*/       }
/*N*/         else if ( !rEntry.bQueryByString &&
/*N*/                 (pCell ? pCell->HasValueData() : HasValueData(rEntry.nField, nRow)) )
/*N*/       {   // by Value
/*N*/             double nCellVal;
/*N*/             if ( pCell )
/*N*/             {
/*N*/                 switch ( pCell->GetCellType() )
/*N*/                 {
/*N*/                     case CELLTYPE_VALUE :
/*N*/                         nCellVal = ((ScValueCell*)pCell)->GetValue();
/*N*/                     break;
/*N*/                     case CELLTYPE_FORMULA :
/*?*/                         nCellVal = ((ScFormulaCell*)pCell)->GetValue();
/*?*/                     break;
/*?*/                     default:
/*?*/                         nCellVal = 0.0;
/*N*/                 }
/*N*/
/*N*/             }
/*N*/             else
/*?*/                 nCellVal = GetValue( rEntry.nField, nRow );
/*N*/           switch (rEntry.eOp)
/*N*/           {
/*N*/               case SC_EQUAL :
/*?*/                     bOk = ::rtl::math::approxEqual( nCellVal, rEntry.nVal );
/*?*/                   break;
/*?*/               case SC_LESS :
/*?*/                   bOk = (nCellVal < rEntry.nVal) && !::rtl::math::approxEqual( nCellVal, rEntry.nVal );
/*?*/                   break;
/*?*/               case SC_GREATER :
/*?*/                   bOk = (nCellVal > rEntry.nVal) && !::rtl::math::approxEqual( nCellVal, rEntry.nVal );
/*?*/                   break;
/*?*/               case SC_LESS_EQUAL :
/*N*/                   bOk = (nCellVal < rEntry.nVal) || ::rtl::math::approxEqual( nCellVal, rEntry.nVal );
/*N*/                     if ( bOk && pbTestEqualCondition )
/*N*/                         bTestEqual = ::rtl::math::approxEqual( nCellVal, rEntry.nVal );
/*N*/                   break;
/*?*/               case SC_GREATER_EQUAL :
/*?*/                   bOk = (nCellVal > rEntry.nVal) || ::rtl::math::approxEqual( nCellVal, rEntry.nVal );
/*?*/                     if ( bOk && pbTestEqualCondition )
/*?*/                         bTestEqual = ::rtl::math::approxEqual( nCellVal, rEntry.nVal );
/*?*/                   break;
/*?*/               case SC_NOT_EQUAL :
/*?*/                     bOk = !::rtl::math::approxEqual( nCellVal, rEntry.nVal );
/*?*/                   break;
/*N*/           }
/*N*/       }
/*N*/       else if ( (rEntry.eOp == SC_EQUAL || rEntry.eOp == SC_NOT_EQUAL)
/*N*/               || (rEntry.bQueryByString
/*N*/                     && (pCell ? pCell->HasStringData() : HasStringData(rEntry.nField, nRow)))
/*N*/           )
/*N*/       {   // by String
/*N*/           String  aCellStr;
/*N*/             if ( pCell )
/*N*/             {
/*N*/                 if (pCell->GetCellType() != CELLTYPE_NOTE)
/*N*/                 {
/*N*/                     ULONG nFormat = GetNumberFormat( rEntry.nField, nRow );
/*N*/                     ScCellFormat::GetInputString( pCell, nFormat, aCellStr, *(pDocument->GetFormatTable()) );
/*N*/                 }
/*N*/             }
/*N*/             else
/*?*/                 GetInputString( rEntry.nField, nRow, aCellStr );
/*N*/
/*N*/             BOOL bRealRegExp = (rParam.bRegExp && ((rEntry.eOp == SC_EQUAL)
/*N*/                 || (rEntry.eOp == SC_NOT_EQUAL)));
/*N*/             BOOL bTestRegExp = (pbTestEqualCondition && rParam.bRegExp
/*N*/                 && ((rEntry.eOp == SC_LESS_EQUAL)
/*N*/                     || (rEntry.eOp == SC_GREATER_EQUAL)));
/*N*/             if ( bRealRegExp || bTestRegExp )
/*N*/             {
/*N*/               xub_StrLen nStart = 0;
/*N*/               xub_StrLen nEnd   = aCellStr.Len();
/*N*/                 BOOL bMatch = (BOOL) rEntry.GetSearchTextPtr( rParam.bCaseSens )
/*N*/                   ->SearchFrwrd( aCellStr, &nStart, &nEnd );
/*N*/               // from 614 on, nEnd is behind the found text
/*N*/                 if ( bMatch && bMatchWholeCell
/*N*/                       && (nStart != 0 || nEnd != aCellStr.Len()) )
/*?*/                     bMatch = FALSE;    // RegExp must match entire cell string
/*N*/                 if ( bRealRegExp )
/*N*/                     bOk = ((rEntry.eOp == SC_NOT_EQUAL) ? !bMatch : bMatch);
/*N*/                 else
/*?*/                     bTestEqual = bMatch;
/*N*/             }
/*N*/             if ( !bRealRegExp )
/*N*/           {
/*N*/               if ( rEntry.eOp == SC_EQUAL || rEntry.eOp == SC_NOT_EQUAL )
/*N*/               {
/*N*/                   if ( bMatchWholeCell )
/*N*/                         bOk = pTransliteration->isEqual( aCellStr, *rEntry.pStr );
/*N*/                   else
/*N*/                   {
/*N*/                         ::com::sun::star::uno::Sequence< long > xOff;
/*N*/                         String aCell( pTransliteration->transliterate(
/*N*/                             aCellStr, ScGlobal::eLnge, 0, aCellStr.Len(),
/*N*/                             &xOff ) );
/*N*/                         String aQuer( pTransliteration->transliterate(
/*N*/                             *rEntry.pStr, ScGlobal::eLnge, 0, rEntry.pStr->Len(),
/*N*/                             &xOff ) );
/*N*/                         bOk = (aCell.Search( aQuer ) != STRING_NOTFOUND);
/*N*/                   }
/*N*/                   if ( rEntry.eOp == SC_NOT_EQUAL )
/*?*/                       bOk = !bOk;
/*N*/               }
/*N*/               else
/*N*/                 {   // use collator here because data was probably sorted
/*?*/                   sal_Int32 nCompare = pCollator->compareString(
/*?*/                       aCellStr, *rEntry.pStr );
/*?*/                   switch (rEntry.eOp)
/*?*/                   {
/*?*/                       case SC_LESS :
/*?*/                             bOk = (nCompare < 0);
/*?*/                           break;
/*?*/                       case SC_GREATER :
/*?*/                             bOk = (nCompare > 0);
/*?*/                           break;
/*?*/                       case SC_LESS_EQUAL :
/*?*/                             bOk = (nCompare <= 0);
/*?*/                             if ( bOk && pbTestEqualCondition && !bTestEqual )
/*?*/                                 bTestEqual = (nCompare == 0);
/*?*/                           break;
/*?*/                       case SC_GREATER_EQUAL :
/*?*/                             bOk = (nCompare >= 0);
/*?*/                             if ( bOk && pbTestEqualCondition && !bTestEqual )
/*?*/                                 bTestEqual = (nCompare == 0);
/*?*/                           break;
/*?*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/
/*N*/       if (nPos == -1)
/*N*/       {
/*N*/           nPos++;
/*N*/           pPasst[nPos] = bOk;
/*N*/             pTest[nPos] = bTestEqual;
/*N*/       }
/*N*/       else
/*N*/       {
/*?*/           if (rEntry.eConnect == SC_AND)
/*?*/             {
/*?*/               pPasst[nPos] = pPasst[nPos] && bOk;
/*?*/                 pTest[nPos] = pTest[nPos] && bTestEqual;
/*?*/             }
/*?*/           else
/*?*/           {
/*?*/               nPos++;
/*?*/               pPasst[nPos] = bOk;
/*?*/                 pTest[nPos] = bTestEqual;
/*?*/           }
/*N*/       }
/*N*/       i++;
/*N*/   }
/*N*/
/*N*/   for ( i=1; (short)i <= nPos; i++ )
/*N*/     {
/*?*/       pPasst[0] = pPasst[0] || pPasst[i];
/*?*/         pTest[0] = pTest[0] || pTest[i];
/*N*/     }
/*N*/
/*N*/   BOOL bRet = pPasst[0];
/*N*/   if ( pPasst != &aBool[0] )
/*?*/       delete [] pPasst;
/*N*/     if ( pbTestEqualCondition )
/*N*/         *pbTestEqualCondition = pTest[0];
/*N*/     if ( pTest != &aTest[0] )
/*?*/         delete [] pTest;
/*N*/
/*N*/   return bRet;
/*N*/ }

//STRIP001 void ScTable::TopTenQuery( ScQueryParam& rParam )
//STRIP001 {
//STRIP001  BOOL bSortCollatorInitialized = FALSE;
//STRIP001  USHORT nEntryCount = rParam.GetEntryCount();
//STRIP001  USHORT nRow1 = (rParam.bHasHeader ? rParam.nRow1 + 1 : rParam.nRow1);
//STRIP001  USHORT nCount = rParam.nRow2 - nRow1 + 1;
//STRIP001  USHORT i;
//STRIP001  for ( i=0; (i<nEntryCount) && (rParam.GetEntry(i).bDoQuery); i++ )
//STRIP001  {
//STRIP001      ScQueryEntry& rEntry = rParam.GetEntry(i);
//STRIP001      switch ( rEntry.eOp )
//STRIP001      {
//STRIP001          case SC_TOPVAL:
//STRIP001          case SC_BOTVAL:
//STRIP001          case SC_TOPPERC:
//STRIP001          case SC_BOTPERC:
//STRIP001          {
//STRIP001              ScSortParam aLocalSortParam( rParam, rEntry.nField );
//STRIP001              aSortParam = aLocalSortParam;       // used in CreateSortInfoArray, Compare
//STRIP001              if ( !bSortCollatorInitialized )
//STRIP001              {
//STRIP001                  bSortCollatorInitialized = TRUE;
//STRIP001                  InitSortCollator( aLocalSortParam );
//STRIP001              }
//STRIP001              ScSortInfoArray* pArray = CreateSortInfoArray( nRow1, rParam.nRow2 );
//STRIP001              DecoladeRow( pArray, nRow1, rParam.nRow2 );
//STRIP001              QuickSort( pArray, nRow1, rParam.nRow2 );
//STRIP001              ScSortInfo** ppInfo = pArray->GetFirstArray();
//STRIP001              USHORT nValidCount = nCount;
//STRIP001              // keine Note-/Leerzellen zaehlen, sind ans Ende sortiert
//STRIP001              while ( nValidCount && ppInfo[nValidCount-1]->pCell == NULL )
//STRIP001                  nValidCount--;
//STRIP001              // keine Strings zaehlen, sind zwischen Value und Leer
//STRIP001              while ( nValidCount
//STRIP001                && ppInfo[nValidCount-1]->pCell->HasStringData() )
//STRIP001                  nValidCount--;
//STRIP001              if ( nValidCount )
//STRIP001              {
//STRIP001                  if ( rEntry.bQueryByString )
//STRIP001                  {   // dat wird nix
//STRIP001                      rEntry.bQueryByString = FALSE;
//STRIP001                      rEntry.nVal = 10;   // 10 bzw. 10%
//STRIP001                  }
//STRIP001                  USHORT nVal = (rEntry.nVal >= 1 ? (USHORT)rEntry.nVal : 1);
//STRIP001                  USHORT nOffset = 0;
//STRIP001                  switch ( rEntry.eOp )
//STRIP001                  {
//STRIP001                      case SC_TOPVAL:
//STRIP001                      {
//STRIP001                          rEntry.eOp = SC_GREATER_EQUAL;
//STRIP001                          if ( nVal > nValidCount )
//STRIP001                              nVal = nValidCount;
//STRIP001                          nOffset = nValidCount - nVal;   // 1 <= nVal <= nValidCount
//STRIP001                      }
//STRIP001                      break;
//STRIP001                      case SC_BOTVAL:
//STRIP001                      {
//STRIP001                          rEntry.eOp = SC_LESS_EQUAL;
//STRIP001                          if ( nVal > nValidCount )
//STRIP001                              nVal = nValidCount;
//STRIP001                          nOffset = nVal - 1;     // 1 <= nVal <= nValidCount
//STRIP001                      }
//STRIP001                      break;
//STRIP001                      case SC_TOPPERC:
//STRIP001                      {
//STRIP001                          rEntry.eOp = SC_GREATER_EQUAL;
//STRIP001                          if ( nVal > 100 )
//STRIP001                              nVal = 100;
//STRIP001                          nOffset = nValidCount -
//STRIP001                              (USHORT)((ULONG)nValidCount * nVal / 100);
//STRIP001                          if ( nOffset >= nValidCount )
//STRIP001                              nOffset = nValidCount - 1;
//STRIP001                      }
//STRIP001                      break;
//STRIP001                      case SC_BOTPERC:
//STRIP001                      {
//STRIP001                          rEntry.eOp = SC_LESS_EQUAL;
//STRIP001                          if ( nVal > 100 )
//STRIP001                              nVal = 100;
//STRIP001                          nOffset =
//STRIP001                              (USHORT)((ULONG)nValidCount * nVal / 100);
//STRIP001                          if ( nOffset >= nValidCount )
//STRIP001                              nOffset = nValidCount - 1;
//STRIP001                      }
//STRIP001                      break;
//STRIP001                  }
//STRIP001                  ScBaseCell* pCell = ppInfo[nOffset]->pCell;
//STRIP001                  if ( pCell->HasValueData() )
//STRIP001                  {
//STRIP001                      if ( pCell->GetCellType() == CELLTYPE_VALUE )
//STRIP001                          rEntry.nVal = ((ScValueCell*)pCell)->GetValue();
//STRIP001                      else
//STRIP001                          rEntry.nVal = ((ScFormulaCell*)pCell)->GetValue();
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      DBG_ERRORFILE( "TopTenQuery: pCell kein ValueData" );
//STRIP001                      rEntry.eOp = SC_GREATER_EQUAL;
//STRIP001                      rEntry.nVal = 0;
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  rEntry.eOp = SC_GREATER_EQUAL;
//STRIP001                  rEntry.bQueryByString = FALSE;
//STRIP001                  rEntry.nVal = 0;
//STRIP001              }
//STRIP001              delete pArray;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if ( bSortCollatorInitialized )
//STRIP001      DestroySortCollator();
//STRIP001 }

//STRIP001 USHORT ScTable::Query(ScQueryParam& rParamOrg, BOOL bKeepSub)
//STRIP001 {
//STRIP001  StrCollection   aStrCollection;
//STRIP001  StrData*        pStrData = NULL;
//STRIP001
//STRIP001  BOOL    bStarted = FALSE;
//STRIP001  BOOL    bOldResult = TRUE;
//STRIP001  USHORT  nOldStart = 0;
//STRIP001  USHORT  nOldEnd = 0;
//STRIP001
//STRIP001  USHORT nCount   = 0;
//STRIP001  USHORT nOutRow  = 0;
//STRIP001  USHORT nHeader  = rParamOrg.bHasHeader ? 1 : 0;
//STRIP001  USHORT i        = 0;
//STRIP001
//STRIP001  USHORT nEntryCount = rParamOrg.GetEntryCount();
//STRIP001
//STRIP001  BOOL* pSpecial = new BOOL[nEntryCount];
//STRIP001  for (i=0; i<nEntryCount; i++)
//STRIP001      pSpecial[i] = FALSE;
//STRIP001
//STRIP001  /*
//STRIP001   * Dialog liefert die ausgezeichneten Feldwerte "leer"/"nicht leer"
//STRIP001   * als Konstanten in nVal in Verbindung mit dem Schalter
//STRIP001   * bQueryByString auf FALSE.
//STRIP001   */
//STRIP001
//STRIP001  BOOL bTopTen = FALSE;
//STRIP001  for ( i=0; (i<nEntryCount) && (rParamOrg.GetEntry(i).bDoQuery); i++ )
//STRIP001  {
//STRIP001      ScQueryEntry& rEntry = rParamOrg.GetEntry(i);
//STRIP001
//STRIP001      if ( rEntry.bQueryByString )
//STRIP001      {
//STRIP001          ULONG nIndex = 0;
//STRIP001          rEntry.bQueryByString = !(pDocument->GetFormatTable()->
//STRIP001              IsNumberFormat( *rEntry.pStr, nIndex, rEntry.nVal ));
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          double nTemp = rEntry.nVal;
//STRIP001          if (nTemp == SC_EMPTYFIELDS || nTemp == SC_NONEMPTYFIELDS)
//STRIP001              pSpecial[i] = TRUE;
//STRIP001          // #58736# QueryParam mit !bQueryByString kann per Uno oder zweitem
//STRIP001          // Aufruf per AutoFilter kommen - hier keine Assertion mehr
//STRIP001      }
//STRIP001      if ( !bTopTen )
//STRIP001      {
//STRIP001          switch ( rEntry.eOp )
//STRIP001          {
//STRIP001              case SC_TOPVAL:
//STRIP001              case SC_BOTVAL:
//STRIP001              case SC_TOPPERC:
//STRIP001              case SC_BOTPERC:
//STRIP001                  bTopTen = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  ScQueryParam* pTopTenParam;
//STRIP001  if ( bTopTen )
//STRIP001  {   // original Param erhalten und Kopie anpassen
//STRIP001      pTopTenParam = new ScQueryParam( rParamOrg );
//STRIP001      TopTenQuery( *pTopTenParam );
//STRIP001  }
//STRIP001  else
//STRIP001      pTopTenParam = NULL;
//STRIP001  ScQueryParam& rParam = (bTopTen ? *pTopTenParam : rParamOrg);
//STRIP001
//STRIP001  if (!rParam.bInplace)
//STRIP001  {
//STRIP001      nOutRow = rParam.nDestRow + nHeader;
//STRIP001      if (nHeader)
//STRIP001          CopyData( rParam.nCol1, rParam.nRow1, rParam.nCol2, rParam.nRow1,
//STRIP001                          rParam.nDestCol, rParam.nDestRow, rParam.nDestTab );
//STRIP001  }
//STRIP001
//STRIP001  for (i=rParam.nRow1 + nHeader; i<=rParam.nRow2; i++)
//STRIP001  {
//STRIP001      BOOL bResult;                                   // Filterergebnis
//STRIP001      BOOL bValid = ValidQuery(i, rParam, pSpecial);
//STRIP001      if (!bValid && bKeepSub)                        // Subtotals stehenlassen
//STRIP001      {
//STRIP001          for (USHORT nCol=rParam.nCol1; nCol<=rParam.nCol2 && !bValid; nCol++)
//STRIP001          {
//STRIP001              ScBaseCell* pCell;
//STRIP001              pCell = GetCell( nCol, i );
//STRIP001              if ( pCell )
//STRIP001                  if ( pCell->GetCellType() == CELLTYPE_FORMULA )
//STRIP001                      if (((ScFormulaCell*)pCell)->IsSubTotal())
//STRIP001                          if (RefVisible((ScFormulaCell*)pCell))
//STRIP001                              bValid = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001      if (bValid)
//STRIP001      {
//STRIP001          if (rParam.bDuplicate)
//STRIP001              bResult = TRUE;
//STRIP001          else
//STRIP001          {
//STRIP001              String aStr;
//STRIP001              for (USHORT j=rParam.nCol1; j <= rParam.nCol2; j++)
//STRIP001              {
//STRIP001                  String aCellStr;
//STRIP001                  GetString(j, i, aCellStr);
//STRIP001                  aStr += aCellStr;
//STRIP001                  aStr += (sal_Unicode)1;
//STRIP001              }
//STRIP001              pStrData = new StrData(aStr);
//STRIP001
//STRIP001              BOOL bIsUnique = TRUE;
//STRIP001              if (pStrData)
//STRIP001                  bIsUnique = aStrCollection.Insert(pStrData);
//STRIP001              if (bIsUnique)
//STRIP001                  bResult = TRUE;
//STRIP001              else
//STRIP001              {
//STRIP001                  delete pStrData;
//STRIP001                  bResult = FALSE;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001          bResult = FALSE;
//STRIP001
//STRIP001      if (rParam.bInplace)
//STRIP001      {
//STRIP001          if (bResult == bOldResult && bStarted)
//STRIP001              nOldEnd = i;
//STRIP001          else
//STRIP001          {
//STRIP001              if (bStarted)
//STRIP001                  DBShowRows(nOldStart,nOldEnd, bOldResult);
//STRIP001              nOldStart = nOldEnd = i;
//STRIP001              bOldResult = bResult;
//STRIP001          }
//STRIP001          bStarted = TRUE;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if (bResult)
//STRIP001          {
//STRIP001              CopyData( rParam.nCol1,i, rParam.nCol2,i, rParam.nDestCol,nOutRow,rParam.nDestTab );
//STRIP001              ++nOutRow;
//STRIP001          }
//STRIP001      }
//STRIP001      if (bResult)
//STRIP001          ++nCount;
//STRIP001  }
//STRIP001
//STRIP001  if (rParam.bInplace && bStarted)
//STRIP001      DBShowRows(nOldStart,nOldEnd, bOldResult);
//STRIP001
//STRIP001  delete[] pSpecial;
//STRIP001  if ( pTopTenParam )
//STRIP001      delete pTopTenParam;
//STRIP001
//STRIP001  return nCount;
//STRIP001 }

//STRIP001 BOOL ScTable::CreateExcelQuery(USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2, ScQueryParam& rQueryParam)
//STRIP001 {
//STRIP001  USHORT  i;
//STRIP001  BOOL    bValid = TRUE;
//STRIP001  USHORT* pFields = new USHORT[nCol2-nCol1+1];
//STRIP001  String  aCellStr;
//STRIP001  USHORT  nCol = nCol1;
//STRIP001  DBG_ASSERT( rQueryParam.nTab != USHRT_MAX, "rQueryParam.nTab no value, not bad but no good" );
//STRIP001  USHORT  nDBTab = (rQueryParam.nTab == USHRT_MAX ? nTab : rQueryParam.nTab);
//STRIP001  USHORT  nDBRow1 = rQueryParam.nRow1;
//STRIP001  USHORT  nDBCol2 = rQueryParam.nCol2;
//STRIP001  // Erste Zeile muessen Spaltenkoepfe sein
//STRIP001  while (bValid && (nCol <= nCol2))
//STRIP001  {
//STRIP001      String aQueryStr;
//STRIP001      GetUpperCellString(nCol, nRow1, aQueryStr);
//STRIP001      BOOL bFound = FALSE;
//STRIP001      i = rQueryParam.nCol1;
//STRIP001      while (!bFound && (i <= nDBCol2))
//STRIP001      {
//STRIP001          if ( nTab == nDBTab )
//STRIP001              GetUpperCellString(i, nDBRow1, aCellStr);
//STRIP001          else
//STRIP001              pDocument->GetUpperCellString(i, nDBRow1, nDBTab, aCellStr);
//STRIP001          bFound = (aCellStr == aQueryStr);
//STRIP001          if (!bFound) i++;
//STRIP001      }
//STRIP001      if (bFound)
//STRIP001          pFields[nCol - nCol1] = i;
//STRIP001      else
//STRIP001          bValid = FALSE;
//STRIP001      nCol++;
//STRIP001  }
//STRIP001  if (bValid)
//STRIP001  {
//STRIP001      long nVisible = 0;
//STRIP001      for ( nCol=nCol1; nCol<=nCol2; nCol++ )
//STRIP001          nVisible += aCol[nCol].VisibleCount( nRow1+1, nRow2 );
//STRIP001
//STRIP001      if ( nVisible > USHRT_MAX / sizeof(void*) )
//STRIP001      {
//STRIP001          DBG_ERROR("zu viele Filterkritierien");
//STRIP001          nVisible = 0;
//STRIP001      }
//STRIP001
//STRIP001      USHORT nNewEntries = (USHORT) nVisible;
//STRIP001      rQueryParam.Resize( nNewEntries );
//STRIP001
//STRIP001      USHORT nIndex = 0;
//STRIP001      USHORT nRow = nRow1 + 1;
//STRIP001      while (nRow <= nRow2)
//STRIP001      {
//STRIP001          nCol = nCol1;
//STRIP001          while (nCol <= nCol2)
//STRIP001          {
//STRIP001                 GetInputString( nCol, nRow, aCellStr );
//STRIP001                 ScGlobal::pCharClass->toUpper( aCellStr );
//STRIP001              if (aCellStr.Len() > 0)
//STRIP001              {
//STRIP001                  if (nIndex < nNewEntries)
//STRIP001                  {
//STRIP001                      rQueryParam.GetEntry(nIndex).nField = pFields[nCol - nCol1];
//STRIP001                      rQueryParam.FillInExcelSyntax(aCellStr, nIndex);
//STRIP001                      nIndex++;
//STRIP001                      if (nIndex < nNewEntries)
//STRIP001                          rQueryParam.GetEntry(nIndex).eConnect = SC_AND;
//STRIP001                  }
//STRIP001                  else
//STRIP001                      bValid = FALSE;
//STRIP001              }
//STRIP001              nCol++;
//STRIP001          }
//STRIP001          nRow++;
//STRIP001          if (nIndex < nNewEntries)
//STRIP001              rQueryParam.GetEntry(nIndex).eConnect = SC_OR;
//STRIP001      }
//STRIP001  }
//STRIP001  delete pFields;
//STRIP001  return bValid;
//STRIP001 }

//STRIP001 BOOL ScTable::CreateStarQuery(USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2, ScQueryParam& rQueryParam)
//STRIP001 {
//STRIP001  BOOL bValid;
//STRIP001  BOOL bFound;
//STRIP001  String aCellStr;
//STRIP001  USHORT nIndex = 0;
//STRIP001  USHORT nRow = nRow1;
//STRIP001  DBG_ASSERT( rQueryParam.nTab != USHRT_MAX, "rQueryParam.nTab no value, not bad but no good" );
//STRIP001  USHORT  nDBTab = (rQueryParam.nTab == USHRT_MAX ? nTab : rQueryParam.nTab);
//STRIP001  USHORT  nDBRow1 = rQueryParam.nRow1;
//STRIP001  USHORT  nDBCol2 = rQueryParam.nCol2;
//STRIP001
//STRIP001  USHORT nNewEntries = nRow2-nRow1+1;
//STRIP001  rQueryParam.Resize( nNewEntries );
//STRIP001
//STRIP001  do
//STRIP001  {
//STRIP001      ScQueryEntry& rEntry = rQueryParam.GetEntry(nIndex);
//STRIP001
//STRIP001      bValid = FALSE;
//STRIP001      // Erste Spalte UND/ODER
//STRIP001      if (nIndex > 0)
//STRIP001      {
//STRIP001          GetUpperCellString(nCol1, nRow, aCellStr);
//STRIP001          if ( aCellStr == ScGlobal::GetRscString(STR_TABLE_UND) )
//STRIP001          {
//STRIP001              rEntry.eConnect = SC_AND;
//STRIP001              bValid = TRUE;
//STRIP001          }
//STRIP001          else if ( aCellStr == ScGlobal::GetRscString(STR_TABLE_ODER) )
//STRIP001          {
//STRIP001              rEntry.eConnect = SC_OR;
//STRIP001              bValid = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001      // Zweite Spalte FeldName
//STRIP001      if ((nIndex < 1) || bValid)
//STRIP001      {
//STRIP001          bFound = FALSE;
//STRIP001          GetUpperCellString(nCol1 + 1, nRow, aCellStr);
//STRIP001          for (USHORT i=rQueryParam.nCol1; (i <= nDBCol2) && (!bFound); i++)
//STRIP001          {
//STRIP001              String aFieldStr;
//STRIP001              if ( nTab == nDBTab )
//STRIP001                  GetUpperCellString(i, nDBRow1, aFieldStr);
//STRIP001              else
//STRIP001                  pDocument->GetUpperCellString(i, nDBRow1, nDBTab, aFieldStr);
//STRIP001              bFound = (aCellStr == aFieldStr);
//STRIP001              if (bFound)
//STRIP001              {
//STRIP001                  rEntry.nField = i;
//STRIP001                  bValid = TRUE;
//STRIP001              }
//STRIP001              else
//STRIP001                  bValid = FALSE;
//STRIP001          }
//STRIP001      }
//STRIP001      // Dritte Spalte Operator =<>...
//STRIP001      if (bValid)
//STRIP001      {
//STRIP001          bFound = FALSE;
//STRIP001          GetUpperCellString(nCol1 + 2, nRow, aCellStr);
//STRIP001          if (aCellStr.GetChar(0) == '<')
//STRIP001          {
//STRIP001              if (aCellStr.GetChar(1) == '>')
//STRIP001                  rEntry.eOp = SC_NOT_EQUAL;
//STRIP001              else if (aCellStr.GetChar(1) == '=')
//STRIP001                  rEntry.eOp = SC_LESS_EQUAL;
//STRIP001              else
//STRIP001                  rEntry.eOp = SC_LESS;
//STRIP001          }
//STRIP001          else if (aCellStr.GetChar(0) == '>')
//STRIP001          {
//STRIP001              if (aCellStr.GetChar(1) == '=')
//STRIP001                  rEntry.eOp = SC_GREATER_EQUAL;
//STRIP001              else
//STRIP001                  rEntry.eOp = SC_GREATER;
//STRIP001          }
//STRIP001          else if (aCellStr.GetChar(0) == '=')
//STRIP001              rEntry.eOp = SC_EQUAL;
//STRIP001
//STRIP001      }
//STRIP001      // Vierte Spalte Wert
//STRIP001      if (bValid)
//STRIP001      {
//STRIP001          GetString(nCol1 + 3, nRow, *rEntry.pStr);
//STRIP001          rEntry.bDoQuery = TRUE;
//STRIP001      }
//STRIP001      nIndex++;
//STRIP001      nRow++;
//STRIP001  }
//STRIP001  while (bValid && (nRow <= nRow2) /* && (nIndex < MAXQUERY) */ );
//STRIP001  return bValid;
//STRIP001 }

/*N*/ BOOL ScTable::CreateQueryParam(USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2, ScQueryParam& rQueryParam)
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //STRIP001    USHORT i, nCount;
//STRIP001  PutInOrder(nCol1, nCol2);
//STRIP001  PutInOrder(nRow1, nRow2);
//STRIP001
//STRIP001  nCount = rQueryParam.GetEntryCount();
//STRIP001  for (i=0; i < nCount; i++)
//STRIP001      rQueryParam.GetEntry(i).Clear();
//STRIP001
//STRIP001  // Standard QueryTabelle
//STRIP001  BOOL bValid = CreateStarQuery(nCol1, nRow1, nCol2, nRow2, rQueryParam);
//STRIP001  // Excel QueryTabelle
//STRIP001  if (!bValid)
//STRIP001      bValid = CreateExcelQuery(nCol1, nRow1, nCol2, nRow2, rQueryParam);
//STRIP001
//STRIP001  nCount = rQueryParam.GetEntryCount();
//STRIP001  if (bValid)
//STRIP001  {
//STRIP001      //  bQueryByString muss gesetzt sein
//STRIP001      for (i=0; i < nCount; i++)
//STRIP001          rQueryParam.GetEntry(i).bQueryByString = TRUE;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      //  nix
//STRIP001      for (i=0; i < nCount; i++)
//STRIP001          rQueryParam.GetEntry(i).Clear();
//STRIP001  }
return FALSE;//STRIP001     return bValid;
/*N*/ }

//STRIP001 BOOL ScTable::HasColHeader( USHORT nStartCol, USHORT nStartRow, USHORT nEndCol, USHORT nEndRow )
//STRIP001 {
//STRIP001  for (USHORT nCol=nStartCol; nCol<=nEndCol; nCol++)
//STRIP001  {
//STRIP001      CellType eType = GetCellType( nCol, nStartRow );
//STRIP001      if (eType != CELLTYPE_STRING && eType != CELLTYPE_EDIT)
//STRIP001          return FALSE;
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL ScTable::HasRowHeader( USHORT nStartCol, USHORT nStartRow, USHORT nEndCol, USHORT nEndRow )
//STRIP001 {
//STRIP001  for (USHORT nRow=nStartRow; nRow<=nEndRow; nRow++)
//STRIP001  {
//STRIP001      CellType eType = GetCellType( nStartCol, nRow );
//STRIP001      if (eType != CELLTYPE_STRING && eType != CELLTYPE_EDIT)
//STRIP001          return FALSE;
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 void ScTable::GetFilterEntries(USHORT nCol, USHORT nRow1, USHORT nRow2, TypedStrCollection& rStrings)
//STRIP001 {
//STRIP001  aCol[nCol].GetFilterEntries( nRow1, nRow2, rStrings );
//STRIP001 }

//STRIP001 BOOL ScTable::GetDataEntries(USHORT nCol, USHORT nRow, TypedStrCollection& rStrings, BOOL bLimit)
//STRIP001 {
//STRIP001  return aCol[nCol].GetDataEntries( nRow, rStrings, bLimit );
//STRIP001 }

/*N*/ long ScTable::GetCellCount() const
/*N*/ {
/*N*/   long nCellCount = 0;
/*N*/
/*N*/   for ( USHORT nCol=0; nCol<=MAXCOL; nCol++ )
/*N*/       nCellCount += aCol[nCol].GetCellCount();
/*N*/
/*N*/   return nCellCount;
/*N*/ }

/*N*/ long ScTable::GetWeightedCount() const
/*N*/ {
/*N*/   long nCellCount = 0;
/*N*/
/*N*/   for ( USHORT nCol=0; nCol<=MAXCOL; nCol++ )
/*N*/       if ( aCol[nCol].GetCellCount() )                    // GetCellCount ist inline
/*N*/           nCellCount += aCol[nCol].GetWeightedCount();
/*N*/
/*N*/   return nCellCount;
/*N*/ }

/*N*/  ULONG ScTable::GetCodeCount() const
/*N*/  {
/*N*/   ULONG nCodeCount = 0;
/*N*/
/*N*/   for ( USHORT nCol=0; nCol<=MAXCOL; nCol++ )
/*N*/       if ( aCol[nCol].GetCellCount() )                    // GetCellCount ist inline
/*N*/           nCodeCount += aCol[nCol].GetCodeCount();
/*N*/
/*N*/   return nCodeCount;
/*N*/  }

//STRIP001 xub_StrLen ScTable::GetMaxStringLen( USHORT nCol,
//STRIP001                              USHORT nRowStart, USHORT nRowEnd ) const
//STRIP001 {
//STRIP001  if ( nCol <= MAXCOL )
//STRIP001      return aCol[nCol].GetMaxStringLen( nRowStart, nRowEnd );
//STRIP001  else
//STRIP001      return 0;
//STRIP001 }

//STRIP001 xub_StrLen ScTable::GetMaxNumberStringLen( USHORT& nPrecision, USHORT nCol,
//STRIP001                              USHORT nRowStart, USHORT nRowEnd ) const
//STRIP001 {
//STRIP001  if ( nCol <= MAXCOL )
//STRIP001      return aCol[nCol].GetMaxNumberStringLen( nPrecision, nRowStart, nRowEnd );
//STRIP001  else
//STRIP001      return 0;
//STRIP001 }

/*N*/ void ScTable::UpdateSelectionFunction( ScFunctionData& rData,
/*N*/                       USHORT nStartCol, USHORT nStartRow, USHORT nEndCol, USHORT nEndRow,
/*N*/                       const ScMarkData& rMark )
/*N*/ {
/*N*/   //  Cursor neben einer Markierung nicht beruecksichtigen:
/*N*/   //! nur noch MarkData uebergeben, Cursorposition ggf. hineinselektieren!!!
/*N*/   BOOL bSingle = ( rMark.IsMarked() || !rMark.IsMultiMarked() );
/*N*/
/*N*/   // Mehrfachselektion:
/*N*/
/*N*/   USHORT nCol;
/*N*/   if ( rMark.IsMultiMarked() )
/*N*/       for (nCol=0; nCol<=MAXCOL && !rData.bError; nCol++)
/*N*/           if ( !pColFlags || !( pColFlags[nCol] & CR_HIDDEN ) )
/*N*/               aCol[nCol].UpdateSelectionFunction( rMark, rData, pRowFlags,
/*N*/                                                   bSingle && ( nCol >= nStartCol && nCol <= nEndCol ),
/*N*/                                                   nStartRow, nEndRow );
/*N*/
/*N*/   //  Einfachselektion (oder Cursor) nur wenn nicht negativ (und s.o.):
/*N*/
/*N*/   if ( bSingle && !rMark.IsMarkNegative() )
/*N*/       for (nCol=nStartCol; nCol<=nEndCol && !rData.bError; nCol++)
/*N*/           if ( !pColFlags || !( pColFlags[nCol] & CR_HIDDEN ) )
/*N*/               aCol[nCol].UpdateAreaFunction( rData, pRowFlags, nStartRow, nEndRow );
/*N*/ }

/*N*/ void ScTable::FindConditionalFormat( ULONG nKey, ScRangeList& rList )
/*N*/ {
/*N*/   USHORT nStartRow, nEndRow;
/*N*/   for (USHORT nCol=0; nCol<=MAXCOL; nCol++)
/*N*/   {
/*N*/       ScAttrIterator* pIter = aCol[nCol].CreateAttrIterator( 0, MAXCOL );
/*N*/       const ScPatternAttr* pPattern = pIter->Next( nStartRow, nEndRow );
/*N*/       while (pPattern)
/*N*/       {
/*N*/           if (((SfxUInt32Item&)pPattern->GetItem(ATTR_CONDITIONAL)).GetValue() == nKey)
/*N*/               rList.Join( ScRange(nCol,nStartRow,nTab, nCol,nEndRow,nTab) );
/*N*/           pPattern = pIter->Next( nStartRow, nEndRow );
/*N*/       }
/*N*/       delete pIter;
/*N*/   }
/*N*/ }




}
