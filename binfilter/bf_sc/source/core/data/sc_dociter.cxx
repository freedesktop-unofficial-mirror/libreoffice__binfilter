/*************************************************************************
 *
 *  $RCSfile: sc_dociter.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 11:03:56 $
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

#include <svtools/zforlist.hxx>

// auto strip #include "scitems.hxx"
// auto strip #include "global.hxx"
#include "dociter.hxx"
#include "document.hxx"
// auto strip #include "table.hxx"
// auto strip #include "column.hxx"
#include "cell.hxx"
#include "attarray.hxx"
// auto strip #include "patattr.hxx"
#include "docoptio.hxx"
namespace binfilter {


// STATIC DATA -----------------------------------------------------------

/*N*/ ScDocumentIterator::ScDocumentIterator( ScDocument* pDocument,
/*N*/                           USHORT nStartTable, USHORT nEndTable ) :
/*N*/   pDoc( pDocument ),
/*N*/   nStartTab( nStartTable ),
/*N*/   nEndTab( nEndTable )
/*N*/ {
/*N*/   PutInOrder( nStartTab, nEndTab );
/*N*/   if (nStartTab > MAXTAB) nStartTab = MAXTAB;
/*N*/   if (nEndTab > MAXTAB) nEndTab = MAXTAB;
/*N*/
/*N*/   pDefPattern = pDoc->GetDefPattern();
/*N*/
/*N*/   nCol = 0;
/*N*/   nRow = 0;
/*N*/   nTab = nStartTab;
/*N*/
/*N*/   nColPos = 0;
/*N*/   nAttrPos = 0;
/*N*/ }

/*N*/ ScDocumentIterator::~ScDocumentIterator()
/*N*/ {
/*N*/ }

/*N*/ BOOL ScDocumentIterator::GetThisCol()
/*N*/ {
/*N*/   ScTable*        pTab;
/*N*/   while ( (pTab = pDoc->pTab[nTab]) == NULL )
/*N*/   {
/*N*/       if ( nTab == nEndTab )
/*N*/       {
/*N*/           nCol = MAXCOL;
/*N*/           nRow = MAXROW;
/*N*/           return FALSE;
/*N*/       }
/*N*/       ++nTab;
/*N*/   }
/*N*/   ScColumn*       pCol = &pTab->aCol[nCol];
/*N*/   ScAttrArray*    pAtt = pCol->pAttrArray;
/*N*/
/*N*/   BOOL bFound = FALSE;
/*N*/   do
/*N*/   {
/*N*/       USHORT nColRow;
/*N*/       USHORT nAttrEnd;
/*N*/
/*N*/       do
/*N*/       {
/*N*/           nAttrEnd = pAtt->pData[nAttrPos].nRow;
/*N*/           if (nAttrEnd < nRow)
/*N*/               ++nAttrPos;
/*N*/       }
/*N*/       while (nAttrEnd < nRow);
/*N*/
/*N*/       do
/*N*/       {
/*N*/           nColRow = (nColPos < pCol->nCount) ? pCol->pItems[nColPos].nRow : MAXROW+1;
/*N*/           if (nColRow < nRow)
/*N*/               ++nColPos;
/*N*/       }
/*N*/       while (nColRow < nRow);
/*N*/
/*N*/       if (nColRow == nRow)
/*N*/       {
/*N*/           bFound   = TRUE;
/*N*/           pCell    = pCol->pItems[nColPos].pCell;
/*N*/           pPattern = pAtt->pData[nAttrPos].pPattern;
/*N*/       }
/*N*/       else if ( pAtt->pData[nAttrPos].pPattern != pDefPattern )
/*N*/       {
/*N*/           bFound = TRUE;
/*N*/           pCell = NULL;
/*N*/           pPattern = pAtt->pData[nAttrPos].pPattern;
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           nRow = Min( (USHORT)nColRow, (USHORT)(nAttrEnd+1) );
/*N*/       }
/*N*/   }
/*N*/   while (!bFound && nRow <= MAXROW);
/*N*/
/*N*/   return bFound;
/*N*/ }

/*N*/ BOOL ScDocumentIterator::GetThis()
/*N*/ {
/*N*/   BOOL bEnd = FALSE;
/*N*/   BOOL bSuccess = FALSE;
/*N*/
/*N*/   while ( !bSuccess && !bEnd )
/*N*/   {
/*N*/       if ( nRow > MAXROW )
/*N*/           bSuccess = FALSE;
/*N*/       else
/*N*/           bSuccess = GetThisCol();
/*N*/
/*N*/       if ( !bSuccess )
/*N*/       {
/*N*/           ++nCol;
/*N*/           if (nCol > MAXCOL)
/*N*/           {
/*N*/               nCol = 0;
/*N*/               ++nTab;
/*N*/               if (nTab > nEndTab)
/*N*/                   bEnd = TRUE;
/*N*/           }
/*N*/           nRow = 0;
/*N*/           nColPos = 0;
/*N*/           nAttrPos = 0;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return !bEnd;
/*N*/ }

/*N*/ BOOL ScDocumentIterator::GetFirst()
/*N*/ {
/*N*/   nCol = 0;
/*N*/   nTab = nStartTab;
/*N*/
/*N*/   nRow = 0;
/*N*/   nColPos = 0;
/*N*/   nAttrPos = 0;
/*N*/
/*N*/   return GetThis();
/*N*/ }

/*N*/ BOOL ScDocumentIterator::GetNext()
/*N*/ {
/*N*/   ++nRow;
/*N*/
/*N*/   return GetThis();
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScBaseCell* ScDocumentIterator::GetCell()
/*N*/ {
/*N*/   return pCell;
/*N*/ }

/*N*/ const ScPatternAttr* ScDocumentIterator::GetPattern()
/*N*/ {
/*N*/   return pPattern;
/*N*/ }

/*N*/ void ScDocumentIterator::GetPos( USHORT& rCol, USHORT& rRow, USHORT& rTab )
/*N*/ {
/*N*/   rCol = nCol;
/*N*/   rRow = nRow;
/*N*/   rTab = nTab;
/*N*/ }


//------------------------------------------------------------------------
//------------------------------------------------------------------------
void lcl_IterGetNumberFormat( ULONG& nFormat, const ScAttrArray*& rpArr,
        USHORT& nAttrEndRow, const ScAttrArray* pNewArr, USHORT nRow,
        ScDocument* pDoc )
{
    DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if ( rpArr != pNewArr || nAttrEndRow < nRow )
//STRIP001  {
//STRIP001      short nPos;
//STRIP001      pNewArr->Search( nRow, nPos );  // nPos 0 gueltig wenn nicht gefunden
//STRIP001      const ScPatternAttr* pPattern = pNewArr->pData[nPos].pPattern;
//STRIP001      nFormat = pPattern->GetNumberFormat( pDoc->GetFormatTable() );
//STRIP001      rpArr = pNewArr;
//STRIP001      nAttrEndRow = pNewArr->pData[nPos].nRow;
//STRIP001  }
}

/*N*/ ScValueIterator::ScValueIterator( ScDocument* pDocument,
/*N*/                                   USHORT nSCol, USHORT nSRow, USHORT nSTab,
/*N*/                                   USHORT nECol, USHORT nERow, USHORT nETab,
/*N*/                                   BOOL bSTotal, BOOL bTextZero ) :
/*N*/   pDoc( pDocument ),
/*N*/   nStartCol( nSCol),
/*N*/   nStartRow( nSRow),
/*N*/   nStartTab( nSTab ),
/*N*/   nEndCol( nECol ),
/*N*/   nEndRow( nERow),
/*N*/   nEndTab( nETab ),
/*N*/   bSubTotal(bSTotal),
/*N*/   nNumFmtType( NUMBERFORMAT_UNDEFINED ),
/*N*/   nNumFmtIndex(0),
/*N*/   bNumValid( FALSE ),
/*N*/   bNextValid( FALSE ),
/*N*/   bCalcAsShown( pDocument->GetDocOptions().IsCalcAsShown() ),
/*N*/   bTextAsZero( bTextZero )
/*N*/ {
/*N*/   PutInOrder( nStartCol, nEndCol);
/*N*/   PutInOrder( nStartRow, nEndRow);
/*N*/   PutInOrder( nStartTab, nEndTab );
/*N*/
/*N*/   if (nStartCol > MAXCOL) nStartCol = MAXCOL;
/*N*/   if (nEndCol > MAXCOL) nEndCol = MAXCOL;
/*N*/   if (nStartRow > MAXROW) nStartRow = MAXROW;
/*N*/   if (nEndRow > MAXROW) nEndRow = MAXROW;
/*N*/   if (nStartTab > MAXTAB) nStartTab = MAXTAB;
/*N*/   if (nEndTab > MAXTAB) nEndTab = MAXTAB;
/*N*/
/*N*/   nCol = nStartCol;
/*N*/   nRow = nStartRow;
/*N*/   nTab = nStartTab;
/*N*/
/*N*/   nColRow = 0;                    // wird bei GetFirst initialisiert
/*N*/
/*N*/   nNumFormat = 0;                 // werden bei GetNumberFormat initialisiert
/*N*/   pAttrArray = 0;
/*N*/   nAttrEndRow = 0;
/*N*/ }

/*N*/ ScValueIterator::ScValueIterator( ScDocument* pDocument, const ScRange& rRange,
/*N*/           BOOL bSTotal, BOOL bTextZero ) :
/*N*/   pDoc( pDocument ),
/*N*/   nStartCol( rRange.aStart.Col() ),
/*N*/   nStartRow( rRange.aStart.Row() ),
/*N*/   nStartTab( rRange.aStart.Tab() ),
/*N*/   nEndCol( rRange.aEnd.Col() ),
/*N*/   nEndRow( rRange.aEnd.Row() ),
/*N*/   nEndTab( rRange.aEnd.Tab() ),
/*N*/   bSubTotal(bSTotal),
/*N*/   nNumFmtType( NUMBERFORMAT_UNDEFINED ),
/*N*/   nNumFmtIndex(0),
/*N*/   bNumValid( FALSE ),
/*N*/   bNextValid( FALSE ),
/*N*/   bCalcAsShown( pDocument->GetDocOptions().IsCalcAsShown() ),
/*N*/   bTextAsZero( bTextZero )
/*N*/ {
/*N*/   PutInOrder( nStartCol, nEndCol);
/*N*/   PutInOrder( nStartRow, nEndRow);
/*N*/   PutInOrder( nStartTab, nEndTab );
/*N*/
/*N*/   if (nStartCol > MAXCOL) nStartCol = MAXCOL;
/*N*/   if (nEndCol > MAXCOL) nEndCol = MAXCOL;
/*N*/   if (nStartRow > MAXROW) nStartRow = MAXROW;
/*N*/   if (nEndRow > MAXROW) nEndRow = MAXROW;
/*N*/   if (nStartTab > MAXTAB) nStartTab = MAXTAB;
/*N*/   if (nEndTab > MAXTAB) nEndTab = MAXTAB;
/*N*/
/*N*/   nCol = nStartCol;
/*N*/   nRow = nStartRow;
/*N*/   nTab = nStartTab;
/*N*/
/*N*/   nColRow = 0;                    // wird bei GetFirst initialisiert
/*N*/
/*N*/   nNumFormat = 0;                 // werden bei GetNumberFormat initialisiert
/*N*/   pAttrArray = 0;
/*N*/   nAttrEndRow = 0;
/*N*/ }

/*N*/ BOOL ScValueIterator::GetThis(double& rValue, USHORT& rErr)
/*N*/ {
/*N*/   ScColumn* pCol = &(pDoc->pTab[nTab])->aCol[nCol];
/*N*/   for (;;)
/*N*/   {
/*N*/       if ( nRow > nEndRow )
/*N*/       {
/*N*/           nRow = nStartRow;
/*N*/           do
/*N*/           {
/*N*/               nCol++;
/*N*/               if ( nCol > nEndCol )
/*N*/               {
/*N*/                   nCol = nStartCol;
/*N*/                   nTab++;
/*N*/                   if ( nTab > nEndTab )
/*N*/                   {
/*N*/                       rValue = 0.0;
/*N*/                       rErr = 0;
/*N*/                       return FALSE;               // Ende und Aus
/*N*/                   }
/*N*/               }
/*N*/               pCol = &(pDoc->pTab[nTab])->aCol[nCol];
/*N*/           } while ( pCol->nCount == 0 );
/*N*/           pCol->Search( nRow, nColRow );
/*N*/       }
/*N*/
/*N*/       while (( nColRow < pCol->nCount ) && ( pCol->pItems[nColRow].nRow < nRow ))
/*N*/           nColRow++;
/*N*/
/*N*/       if ( nColRow < pCol->nCount && pCol->pItems[nColRow].nRow <= nEndRow )
/*N*/       {
/*N*/           nRow = pCol->pItems[nColRow].nRow + 1;
/*N*/           if ( !bSubTotal || !pDoc->pTab[nTab]->IsFiltered( nRow-1 ) )
/*N*/           {
/*N*/               ScBaseCell* pCell = pCol->pItems[nColRow].pCell;
/*N*/               ++nColRow;
/*N*/               switch (pCell->GetCellType())
/*N*/               {
/*N*/                   case CELLTYPE_VALUE:
/*N*/                   {
/*N*/                       bNumValid = FALSE;
/*N*/                       rValue = ((ScValueCell*)pCell)->GetValue();
/*N*/                       rErr = 0;
/*N*/                       --nRow;
/*N*/                       if ( bCalcAsShown )
/*N*/                       {
/*?*/ #ifndef WTC
/*?*/                           lcl_IterGetNumberFormat( nNumFormat,pAttrArray,
/*?*/ #else
/*?*/                           lcl_IterGetNumberFormat( nNumFormat,
/*?*/                               (ScAttrArray const *&)pAttrArray,
/*?*/ #endif
/*?*/                               nAttrEndRow, pCol->pAttrArray, nRow, pDoc );
/*?*/                           rValue = pDoc->RoundValueAsShown( rValue, nNumFormat );
/*N*/                       }
/*N*/                       //
/*N*/                       //  wenn in der selben Spalte gleich noch eine Value-Cell folgt, die
/*N*/                       //  auch noch im Block liegt, den Wert jetzt schon holen
/*N*/                       //
/*N*/                       if ( nColRow < pCol->nCount &&
/*N*/                            pCol->pItems[nColRow].nRow <= nEndRow &&
/*N*/                            pCol->pItems[nColRow].pCell->GetCellType() == CELLTYPE_VALUE &&
/*N*/                            !bSubTotal )
/*N*/                       {
/*N*/                           fNextValue = ((ScValueCell*)pCol->pItems[nColRow].pCell)->GetValue();
/*N*/                           nNextRow = pCol->pItems[nColRow].nRow;
/*N*/                           bNextValid = TRUE;
/*N*/                           if ( bCalcAsShown )
/*N*/                           {
/*?*/ #ifndef WTC
/*?*/                               lcl_IterGetNumberFormat( nNumFormat, pAttrArray,
/*?*/ #else
/*?*/                               lcl_IterGetNumberFormat( nNumFormat,
/*?*/                                   (ScAttrArray const *&)pAttrArray,
/*?*/ #endif
/*?*/                                   nAttrEndRow, pCol->pAttrArray, nNextRow, pDoc );
/*?*/                               fNextValue = pDoc->RoundValueAsShown( fNextValue, nNumFormat );
/*N*/                           }
/*N*/                       }
/*N*/
/*N*/                       return TRUE;                                    // gefunden
/*N*/                   }
/*N*/                   break;
/*N*/                   case CELLTYPE_FORMULA:
/*N*/                   {
/*N*/                       if (!bSubTotal || !((ScFormulaCell*)pCell)->IsSubTotal())
/*N*/                       {
/*N*/                           rErr = ((ScFormulaCell*)pCell)->GetErrCode();
/*N*/                           if ( rErr || ((ScFormulaCell*)pCell)->IsValue() )
/*N*/                           {
/*N*/                               rValue = ((ScFormulaCell*)pCell)->GetValue();
/*N*/                               nRow--;
/*N*/                               bNumValid = FALSE;
/*N*/                               return TRUE;                            // gefunden
/*N*/                           }
/*N*/                       }
/*N*/                   }
/*N*/                   break;
/*N*/                   case CELLTYPE_STRING :
/*N*/                   case CELLTYPE_EDIT :
/*N*/                   {
/*N*/                       if ( bTextAsZero )
/*N*/                       {
/*N*/                           rErr = 0;
/*N*/                           rValue = 0.0;
/*N*/                           nNumFmtType = NUMBERFORMAT_NUMBER;
/*N*/                           nNumFmtIndex = 0;
/*N*/                           bNumValid = TRUE;
/*N*/                           --nRow;
/*N*/                           return TRUE;
/*N*/                       }
/*N*/                   }
/*N*/                   break;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/           nRow = nEndRow + 1;         // naechste Spalte
/*N*/   }
/*N*/ }

/*N*/ void ScValueIterator::GetCurNumFmtInfo( short& nType, ULONG& nIndex )
/*N*/ {
/*N*/   if (!bNumValid)
/*N*/   {
/*N*/       const ScColumn* pCol = &(pDoc->pTab[nTab])->aCol[nCol];
/*N*/       nNumFmtIndex = pCol->GetNumberFormat( nRow );
/*N*/       if ( (nNumFmtIndex % SV_COUNTRY_LANGUAGE_OFFSET) == 0 )
/*N*/       {
/*N*/           const ScBaseCell* pCell;
/*N*/           USHORT nIdx = nColRow - 1;
/*N*/           // there might be rearranged something, so be on the safe side
/*N*/           if ( nIdx < pCol->nCount && pCol->pItems[nIdx].nRow == nRow )
/*N*/               pCell = pCol->pItems[nIdx].pCell;
/*N*/           else
/*N*/           {
/*?*/               if ( pCol->Search( nRow, nIdx ) )
/*?*/                   pCell = pCol->pItems[nIdx].pCell;
/*?*/               else
/*?*/                   pCell = NULL;
/*N*/           }
/*N*/           if ( pCell && pCell->GetCellType() == CELLTYPE_FORMULA )
/*N*/               ((const ScFormulaCell*)pCell)->GetFormatInfo( nNumFmtType, nNumFmtIndex );
/*N*/           else
/*N*/               nNumFmtType = pDoc->GetFormatTable()->GetType( nNumFmtIndex );
/*N*/       }
/*N*/       else
/*N*/           nNumFmtType = pDoc->GetFormatTable()->GetType( nNumFmtIndex );
/*N*/       bNumValid = TRUE;
/*N*/   }
/*N*/   nType = nNumFmtType;
/*N*/   nIndex = nNumFmtIndex;
/*N*/ }

/*N*/ BOOL ScValueIterator::GetFirst(double& rValue, USHORT& rErr)
/*N*/ {
/*N*/   nCol = nStartCol;
/*N*/   nRow = nStartRow;
/*N*/   nTab = nStartTab;
/*N*/
/*N*/ //    nColRow = 0;
/*N*/   ScColumn* pCol = &(pDoc->pTab[nTab])->aCol[nCol];
/*N*/   pCol->Search( nRow, nColRow );
/*N*/
/*N*/   nNumFormat = 0;                 // werden bei GetNumberFormat initialisiert
/*N*/   pAttrArray = 0;
/*N*/   nAttrEndRow = 0;
/*N*/
/*N*/   return GetThis(rValue, rErr);
/*N*/ }

/*  ist inline:
BOOL ScValueIterator::GetNext(double& rValue, USHORT& rErr)
{
    ++nRow;
    return GetThis(rValue, rErr);
}
*/

//------------------------------------------------------------------------
//------------------------------------------------------------------------

/*N*/  ScQueryValueIterator::ScQueryValueIterator(ScDocument* pDocument, USHORT nTable, const ScQueryParam& rParam) :
/*N*/   pDoc( pDocument ),
/*N*/   nTab( nTable),
/*N*/   aParam (rParam),
/*N*/   nNumFmtType( NUMBERFORMAT_UNDEFINED ),
/*N*/   nNumFmtIndex(0),
/*N*/   bCalcAsShown( pDocument->GetDocOptions().IsCalcAsShown() )
/*N*/  {
/*N*/   nCol = aParam.nCol1;
/*N*/   nRow = aParam.nRow1;
/*N*/   nColRow = 0;                    // wird bei GetFirst initialisiert
/*N*/   USHORT i;
/*N*/   USHORT nCount = aParam.GetEntryCount();
/*N*/   for (i=0; (i<nCount) && (aParam.GetEntry(i).bDoQuery); i++)
/*N*/   {
/*N*/       ScQueryEntry& rEntry = aParam.GetEntry(i);
/*N*/       ULONG nIndex = 0;
/*N*/       rEntry.bQueryByString =
/*N*/               !(pDoc->GetFormatTable()->IsNumberFormat(*rEntry.pStr, nIndex, rEntry.nVal));
/*N*/   }
/*N*/   nNumFormat = 0;                 // werden bei GetNumberFormat initialisiert
/*N*/   pAttrArray = 0;
/*N*/   nAttrEndRow = 0;
/*N*/  }
/*N*/
/*N*/  BOOL ScQueryValueIterator::GetThis(double& rValue, USHORT& rErr)
/*N*/  {
/*N*/   ScColumn* pCol = &(pDoc->pTab[nTab])->aCol[nCol];
/*N*/      USHORT nFirstQueryField = aParam.GetEntry(0).nField;
/*N*/   for ( ;; )
/*N*/   {
/*N*/       if ( nRow > aParam.nRow2 )
/*N*/       {
/*N*/           nRow = aParam.nRow1;
/*N*/           if (aParam.bHasHeader)
/*N*/               nRow++;
/*N*/           do
/*N*/           {
/*N*/               nCol++;
/*N*/               if ( nCol > aParam.nCol2 )
/*N*/               {
/*N*/                   rValue = 0.0;
/*N*/                   rErr = 0;
/*N*/                   return FALSE;               // Ende und Aus
/*N*/               }
/*N*/               pCol = &(pDoc->pTab[nTab])->aCol[nCol];
/*N*/           } while ( pCol->nCount == 0 );
/*N*/           pCol->Search( nRow, nColRow );
/*N*/       }
/*N*/
/*N*/       while ( (nColRow < pCol->nCount) && (pCol->pItems[nColRow].nRow < nRow) )
/*N*/           nColRow++;
/*N*/
/*N*/       if ( nColRow < pCol->nCount && pCol->pItems[nColRow].nRow <= aParam.nRow2 )
/*N*/       {
/*N*/           nRow = pCol->pItems[nColRow].nRow;
/*N*/              ScBaseCell* pCell = pCol->pItems[nColRow].pCell;
/*N*/              if ( (pDoc->pTab[nTab])->ValidQuery( nRow, aParam, NULL,
/*N*/                      (nCol == nFirstQueryField ? pCell : NULL) ) )
/*N*/           {
/*N*/               switch (pCell->GetCellType())
/*N*/               {
/*N*/                   case CELLTYPE_VALUE:
/*N*/                       {
/*N*/                           rValue = ((ScValueCell*)pCell)->GetValue();
/*N*/                           if ( bCalcAsShown )
/*N*/                           {
/*N*/  #if ! ( defined WTC || defined IRIX || defined ICC || defined HPUX || defined C50 || defined C52  || ( defined GCC && __GNUC__ >= 3 ) )
/*N*/                               lcl_IterGetNumberFormat( nNumFormat, pAttrArray,
/*N*/  #else
/*N*/                               lcl_IterGetNumberFormat( nNumFormat,
/*N*/                                   (ScAttrArray const *&)pAttrArray,
/*N*/  #endif
/*N*/                                   nAttrEndRow, pCol->pAttrArray, nRow, pDoc );
/*N*/                               rValue = pDoc->RoundValueAsShown( rValue, nNumFormat );
/*N*/                           }
/*N*/                           nNumFmtType = NUMBERFORMAT_NUMBER;
/*N*/                           nNumFmtIndex = 0;
/*N*/                           rErr = 0;
/*N*/                           return TRUE;        // gefunden
/*N*/                       }
/*N*/                       break;
/*N*/                   case CELLTYPE_FORMULA:
/*N*/                       {
/*N*/                           if (((ScFormulaCell*)pCell)->IsValue())
/*N*/                           {
/*N*/                               rValue = ((ScFormulaCell*)pCell)->GetValue();
/*N*/                               pDoc->GetNumberFormatInfo( nNumFmtType,
/*N*/                                   nNumFmtIndex, ScAddress( nCol, nRow, nTab ),
/*N*/                                   *((ScFormulaCell*)pCell) );
/*N*/                               rErr = ((ScFormulaCell*)pCell)->GetErrCode();
/*N*/                               return TRUE;    // gefunden
/*N*/                           }
/*N*/                           else
/*N*/                               nRow++;
/*N*/                       }
/*N*/                       break;
/*N*/                   default:
/*N*/                       nRow++;
/*N*/                       break;
/*N*/               }
/*N*/           }
/*N*/           else
/*N*/               nRow++;
/*N*/       }
/*N*/       else
/*N*/           nRow = aParam.nRow2 + 1; // Naechste Spalte
/*N*/   }
/*N*/   return FALSE;
/*N*/  }
/*N*/
/*N*/  BOOL ScQueryValueIterator::GetFirst(double& rValue, USHORT& rErr)
/*N*/  {
/*N*/   nCol = aParam.nCol1;
/*N*/   nRow = aParam.nRow1;
/*N*/   if (aParam.bHasHeader)
/*N*/       nRow++;
/*N*/  //   nColRow = 0;
/*N*/   ScColumn* pCol = &(pDoc->pTab[nTab])->aCol[nCol];
/*N*/   pCol->Search( nRow, nColRow );
/*N*/   return GetThis(rValue, rErr);
/*N*/  }
/*N*/
/*N*/  BOOL ScQueryValueIterator::GetNext(double& rValue, USHORT& rErr)
/*N*/  {
/*N*/   ++nRow;
/*N*/   return GetThis(rValue, rErr);
/*N*/  }

//-------------------------------------------------------------------------------

/*N*/ ScCellIterator::ScCellIterator( ScDocument* pDocument,
/*N*/                               USHORT nSCol, USHORT nSRow, USHORT nSTab,
/*N*/                               USHORT nECol, USHORT nERow, USHORT nETab, BOOL bSTotal ) :
/*N*/   pDoc( pDocument ),
/*N*/   nStartCol( nSCol),
/*N*/   nStartRow( nSRow),
/*N*/   nStartTab( nSTab ),
/*N*/   nEndCol( nECol ),
/*N*/   nEndRow( nERow),
/*N*/   nEndTab( nETab ),
/*N*/   bSubTotal(bSTotal)
/*N*/
/*N*/ {
/*N*/   PutInOrder( nStartCol, nEndCol);
/*N*/   PutInOrder( nStartRow, nEndRow);
/*N*/   PutInOrder( nStartTab, nEndTab );
/*N*/
/*N*/   if (nStartCol > MAXCOL) nStartCol = MAXCOL;
/*N*/   if (nEndCol > MAXCOL) nEndCol = MAXCOL;
/*N*/   if (nStartRow > MAXROW) nStartRow = MAXROW;
/*N*/   if (nEndRow > MAXROW) nEndRow = MAXROW;
/*N*/   if (nStartTab > MAXTAB) nStartTab = MAXTAB;
/*N*/   if (nEndTab > MAXTAB) nEndTab = MAXTAB;
/*N*/
/*N*/   while (nEndTab>0 && !pDoc->pTab[nEndTab])
/*N*/       --nEndTab;                                      // nur benutzte Tabellen
/*N*/   if (nStartTab>nEndTab)
/*N*/       nStartTab = nEndTab;
/*N*/
/*N*/   nCol = nStartCol;
/*N*/   nRow = nStartRow;
/*N*/   nTab = nStartTab;
/*N*/   nColRow = 0;                    // wird bei GetFirst initialisiert
/*N*/
/*N*/   if (!pDoc->pTab[nTab])
/*N*/   {
/*N*/       DBG_ERROR("Tabelle nicht gefunden");
/*N*/       nStartCol = nCol = MAXCOL+1;
/*N*/       nStartRow = nRow = MAXROW+1;
/*N*/       nStartTab = nTab = MAXTAB+1;    // -> Abbruch bei GetFirst
/*N*/   }
/*N*/ }

/*N*/ ScCellIterator::ScCellIterator
/*N*/   ( ScDocument* pDocument, const ScRange& rRange, BOOL bSTotal ) :
/*N*/   pDoc( pDocument ),
/*N*/   nStartCol( rRange.aStart.Col() ),
/*N*/   nStartRow( rRange.aStart.Row() ),
/*N*/   nStartTab( rRange.aStart.Tab() ),
/*N*/   nEndCol( rRange.aEnd.Col() ),
/*N*/   nEndRow( rRange.aEnd.Row() ),
/*N*/   nEndTab( rRange.aEnd.Tab() ),
/*N*/   bSubTotal(bSTotal)
/*N*/
/*N*/ {
/*N*/   PutInOrder( nStartCol, nEndCol);
/*N*/   PutInOrder( nStartRow, nEndRow);
/*N*/   PutInOrder( nStartTab, nEndTab );
/*N*/
/*N*/   if (nStartCol > MAXCOL) nStartCol = MAXCOL;
/*N*/   if (nEndCol > MAXCOL) nEndCol = MAXCOL;
/*N*/   if (nStartRow > MAXROW) nStartRow = MAXROW;
/*N*/   if (nEndRow > MAXROW) nEndRow = MAXROW;
/*N*/   if (nStartTab > MAXTAB) nStartTab = MAXTAB;
/*N*/   if (nEndTab > MAXTAB) nEndTab = MAXTAB;
/*N*/
/*N*/   while (nEndTab>0 && !pDoc->pTab[nEndTab])
/*N*/       --nEndTab;                                      // nur benutzte Tabellen
/*N*/   if (nStartTab>nEndTab)
/*N*/       nStartTab = nEndTab;
/*N*/
/*N*/   nCol = nStartCol;
/*N*/   nRow = nStartRow;
/*N*/   nTab = nStartTab;
/*N*/   nColRow = 0;                    // wird bei GetFirst initialisiert
/*N*/
/*N*/   if (!pDoc->pTab[nTab])
/*N*/   {
/*N*/       DBG_ERROR("Tabelle nicht gefunden");
/*N*/       nStartCol = nCol = MAXCOL+1;
/*N*/       nStartRow = nRow = MAXROW+1;
/*N*/       nStartTab = nTab = MAXTAB+1;    // -> Abbruch bei GetFirst
/*N*/   }
/*N*/ }

/*N*/ ScBaseCell* ScCellIterator::GetThis()
/*N*/ {
/*N*/   ScColumn* pCol = &(pDoc->pTab[nTab])->aCol[nCol];
/*N*/   for ( ;; )
/*N*/   {
/*N*/       if ( nRow > nEndRow )
/*N*/       {
/*N*/           nRow = nStartRow;
/*N*/           do
/*N*/           {
/*N*/               nCol++;
/*N*/               if ( nCol > nEndCol )
/*N*/               {
/*N*/                   nCol = nStartCol;
/*N*/                   nTab++;
/*N*/                   if ( nTab > nEndTab )
/*N*/                       return NULL;                // Ende und Aus
/*N*/               }
/*N*/               pCol = &(pDoc->pTab[nTab])->aCol[nCol];
/*N*/           } while ( pCol->nCount == 0 );
/*N*/           pCol->Search( nRow, nColRow );
/*N*/       }
/*N*/
/*N*/       while ( (nColRow < pCol->nCount) && (pCol->pItems[nColRow].nRow < nRow) )
/*N*/           nColRow++;
/*N*/
/*N*/       if ( nColRow < pCol->nCount && pCol->pItems[nColRow].nRow <= nEndRow )
/*N*/       {
/*N*/           nRow = pCol->pItems[nColRow].nRow;
/*N*/           if ( !bSubTotal || !pDoc->pTab[nTab]->IsFiltered( nRow ) )
/*N*/           {
/*N*/               ScBaseCell* pCell = pCol->pItems[nColRow].pCell;
/*N*/
/*N*/               if ( bSubTotal && pCell->GetCellType() == CELLTYPE_FORMULA
/*N*/                               && ((ScFormulaCell*)pCell)->IsSubTotal() )
/*N*/                   nRow++;             // Sub-Total-Zeilen nicht
/*N*/               else
/*N*/                   return pCell;       // gefunden
/*N*/           }
/*N*/           else
/*N*/               nRow++;
/*N*/       }
/*N*/       else
/*N*/           nRow = nEndRow + 1; // Naechste Spalte
/*N*/   }
/*N*/ }

/*N*/ ScBaseCell* ScCellIterator::GetFirst()
/*N*/ {
/*N*/   if ( nTab > MAXTAB )
/*N*/       return NULL;
/*N*/   nCol = nStartCol;
/*N*/   nRow = nStartRow;
/*N*/   nTab = nStartTab;
/*N*/ //    nColRow = 0;
/*N*/   ScColumn* pCol = &(pDoc->pTab[nTab])->aCol[nCol];
/*N*/   pCol->Search( nRow, nColRow );
/*N*/   return GetThis();
/*N*/ }

/*N*/ ScBaseCell* ScCellIterator::GetNext()
/*N*/ {
/*N*/   ++nRow;
/*N*/   return GetThis();
/*N*/ }

//-------------------------------------------------------------------------------

/*N*/ ScQueryCellIterator::ScQueryCellIterator(ScDocument* pDocument, USHORT nTable,
/*N*/            const ScQueryParam& rParam, BOOL bMod ) :
/*N*/   pDoc( pDocument ),
/*N*/   nTab( nTable),
/*N*/   aParam (rParam),
/*N*/     nStopOnMismatch( nStopOnMismatchDisabled ),
/*N*/     nTestEqualCondition( nTestEqualConditionDisabled ),
/*N*/     bAdvanceQuery( FALSE )
/*N*/ {
/*N*/   nCol = aParam.nCol1;
/*N*/   nRow = aParam.nRow1;
/*N*/   nColRow = 0;                    // wird bei GetFirst initialisiert
/*N*/   USHORT i;
/*N*/   if (bMod)                               // sonst schon eingetragen
/*N*/   {
/*N*/       for (i=0; (i<MAXQUERY) && (aParam.GetEntry(i).bDoQuery); i++)
/*N*/       {
/*?*/           ScQueryEntry& rEntry = aParam.GetEntry(i);
/*?*/           ULONG nIndex = 0;
/*?*/           rEntry.bQueryByString =
/*?*/                    !(pDoc->GetFormatTable()->IsNumberFormat(*rEntry.pStr,
/*?*/                                                             nIndex, rEntry.nVal));
/*N*/       }
/*N*/   }
/*N*/   nNumFormat = 0;                 // werden bei GetNumberFormat initialisiert
/*N*/   pAttrArray = 0;
/*N*/   nAttrEndRow = 0;
/*N*/ }
/*N*/
/*N*/ ScBaseCell* ScQueryCellIterator::GetThis()
/*N*/ {
/*N*/   ScColumn* pCol = &(pDoc->pTab[nTab])->aCol[nCol];
/*N*/     USHORT nFirstQueryField = aParam.GetEntry(0).nField;
/*N*/   for ( ;; )
/*N*/   {
/*N*/       if ( nRow > aParam.nRow2 )
/*N*/       {
/*N*/           nRow = aParam.nRow1;
/*N*/           if (aParam.bHasHeader)
/*?*/               nRow++;
/*N*/           do
/*M*/           {
/*M*/               if ( ++nCol > aParam.nCol2 )
/*M*/                   return NULL;                // Ende und Aus
/*M*/               if ( bAdvanceQuery )
/*M*/                 {
/*M*/                    AdvanceQueryParamEntryField();
/*M*/                     nFirstQueryField = aParam.GetEntry(0).nField;
/*M*/                 }
/*M*/               pCol = &(pDoc->pTab[nTab])->aCol[nCol];
/*M*/           } while ( pCol->nCount == 0 );
/*N*/           pCol->Search( nRow, nColRow );
/*N*/       }
/*N*/
/*N*/       while ( nColRow < pCol->nCount && pCol->pItems[nColRow].nRow < nRow )
/*N*/           nColRow++;
/*N*/
/*N*/       if ( nColRow < pCol->nCount && pCol->pItems[nColRow].nRow <= aParam.nRow2 )
/*N*/       {
/*N*/           if ( pCol->pItems[nColRow].pCell->GetCellType() == CELLTYPE_NOTE )
/*?*/               nRow++;
/*N*/           else
/*N*/           {
/*N*/                 BOOL bTestEqualCondition;
/*N*/               nRow = pCol->pItems[nColRow].nRow;
/*N*/                 ScBaseCell* pCell = pCol->pItems[nColRow].pCell;
/*N*/                 if ( (pDoc->pTab[nTab])->ValidQuery( nRow, aParam, NULL,
/*N*/                         (nCol == nFirstQueryField ? pCell : NULL),
/*N*/                         (nTestEqualCondition ? &bTestEqualCondition : NULL) ) )
/*N*/                 {
/*N*/                     if ( nTestEqualCondition && bTestEqualCondition )
/*N*/                         nTestEqualCondition |= nTestEqualConditionMatched;
/*N*/                     return pCell;     // found
/*N*/                 }
/*N*/                 else if ( nStopOnMismatch )
/*N*/                 {
/*N*/                     nStopOnMismatch |= nStopOnMismatchOccured;
/*N*/                     // Yes, even a mismatch may have a fulfilled equal
/*N*/                     // condition if regular expressions were involved and
/*N*/                     // SC_LESS_EQUAL or SC_GREATER_EQUAL were queried.
/*N*/                     if ( nTestEqualCondition && bTestEqualCondition )
/*?*/                         nTestEqualCondition |= nTestEqualConditionMatched;
/*N*/                     return NULL;
/*N*/                 }
/*N*/               else
/*N*/                   nRow++;
/*N*/           }
/*N*/       }
/*N*/       else
/*?*/           nRow = aParam.nRow2 + 1; // Naechste Spalte
/*N*/   }
/*N*/ }
/*N*/
/*N*/ ScBaseCell* ScQueryCellIterator::GetFirst()
/*N*/ {
/*N*/   nCol = aParam.nCol1;
/*N*/   nRow = aParam.nRow1;
/*N*/   if (aParam.bHasHeader)
/*?*/       nRow++;
/*N*/ //    nColRow = 0;
/*N*/   ScColumn* pCol = &(pDoc->pTab[nTab])->aCol[nCol];
/*N*/   pCol->Search( nRow, nColRow );
/*N*/   return GetThis();
/*N*/ }
/*N*/
/*N*/ ScBaseCell* ScQueryCellIterator::GetNext()
/*N*/ {
/*N*/   ++nRow;
/*N*/     if ( nStopOnMismatch )
/*N*/         nStopOnMismatch = nStopOnMismatchEnabled;
/*N*/     if ( nTestEqualCondition )
/*N*/         nTestEqualCondition = nTestEqualConditionEnabled;
/*N*/   return GetThis();
/*N*/ }
/*N*/
/*N*/  ULONG ScQueryCellIterator::GetNumberFormat()
/*N*/  {
/*N*/   ScColumn* pCol = &(pDoc->pTab[nTab])->aCol[nCol];
/*N*/  #if ! ( defined WTC || defined IRIX  || defined ICC || defined HPUX || defined C50 || defined C52 || ( defined GCC && __GNUC__ >= 3 ) )
/*N*/   lcl_IterGetNumberFormat( nNumFormat, pAttrArray,
/*N*/  #else
/*N*/   lcl_IterGetNumberFormat( nNumFormat,
/*N*/       (ScAttrArray const *&)pAttrArray,
/*N*/  #endif
/*N*/       nAttrEndRow, pCol->pAttrArray, nRow, pDoc );
/*N*/   return nNumFormat;
/*N*/  }

/*N*/  void ScQueryCellIterator::AdvanceQueryParamEntryField()
/*N*/  {
/*N*/   USHORT nEntries = aParam.GetEntryCount();
/*N*/   for ( USHORT j = 0; j < nEntries; j++  )
/*N*/   {
/*N*/       ScQueryEntry& rEntry = aParam.GetEntry( j );
/*N*/       if ( rEntry.bDoQuery )
/*N*/       {
/*N*/           if ( rEntry.nField < MAXCOL )
/*N*/               rEntry.nField++;
/*N*/           else
/*N*/           {
/*N*/               DBG_ERRORFILE( "AdvanceQueryParamEntryField: ++rEntry.nField > MAXCOL" );
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/           break;  // for
/*N*/   }
/*N*/  }


/*N*/ BOOL ScQueryCellIterator::FindEqualOrSortedLastInRange( USHORT& nFoundCol, USHORT& nFoundRow )
/*N*/ {
/*N*/     nFoundCol = MAXCOL+1;
/*N*/     nFoundRow = MAXROW+1;
/*N*/     SetStopOnMismatch( TRUE );      // assume sorted keys
/*N*/     SetTestEqualCondition( TRUE );
/*N*/     if ( GetFirst() )
/*N*/     {
/*N*/         do
/*N*/         {
/*N*/             nFoundCol = GetCol();
/*N*/             nFoundRow = GetRow();
/*N*/         } while ( !IsEqualConditionFulfilled() && GetNext() );
/*N*/     }
/*N*/     if ( IsEqualConditionFulfilled() )
/*N*/     {
/*N*/         nFoundCol = GetCol();
/*N*/         nFoundRow = GetRow();
/*N*/         return TRUE;
/*N*/     }
/*N*/     if ( StoppedOnMismatch() )
/*N*/     {   // Assume found entry to be the last value less than or equal to query.
/*N*/         // But keep on searching for an equal match.
/*N*/         SetStopOnMismatch( FALSE );
/*N*/         SetTestEqualCondition( FALSE );
/*N*/         USHORT nEntries = aParam.GetEntryCount();
/*N*/         for ( USHORT j = 0; j < nEntries; j++  )
/*N*/         {
/*N*/             ScQueryEntry& rEntry = aParam.GetEntry( j );
/*N*/             if ( rEntry.bDoQuery )
/*N*/             {
/*N*/                 switch ( rEntry.eOp )
/*N*/                 {
/*N*/                     case SC_LESS_EQUAL :
/*N*/                     case SC_GREATER_EQUAL :
/*N*/                         rEntry.eOp = SC_EQUAL;
/*N*/                     break;
/*N*/                 }
/*N*/             }
/*N*/             else
/*N*/                 break;  // for
/*N*/         }
/*N*/         if ( GetNext() )
/*N*/         {
/*?*/             nFoundCol = GetCol();
/*?*/             nFoundRow = GetRow();
/*N*/         }
/*N*/     }
/*N*/     return (nFoundCol <= MAXCOL) && (nFoundRow <= MAXROW);
/*N*/ }


//-------------------------------------------------------------------------------

/*N*/ ScHorizontalCellIterator::ScHorizontalCellIterator(ScDocument* pDocument, USHORT nTable,
/*N*/                                   USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2 ) :
/*N*/   pDoc( pDocument ),
/*N*/   nTab( nTable ),
/*N*/   nStartCol( nCol1 ),
/*N*/   nEndCol( nCol2 ),
/*N*/   nEndRow( nRow2 ),
/*N*/   nCol( nCol1 ),
/*N*/   nRow( nRow1 ),
/*N*/   bMore( TRUE )
/*N*/ {
/*N*/   USHORT i;
/*N*/   USHORT nIndex;
/*N*/
/*N*/   pNextRows = new USHORT[ nCol2-nCol1+1 ];
/*N*/   pNextIndices = new USHORT[ nCol2-nCol1+1 ];
/*N*/
/*N*/   for (i=nStartCol; i<=nEndCol; i++)
/*N*/   {
/*N*/       ScColumn* pCol = &pDoc->pTab[nTab]->aCol[i];
/*N*/
/*N*/       pCol->Search( nRow1, nIndex );
/*N*/       if ( nIndex < pCol->nCount )
/*N*/       {
/*N*/           pNextRows[i-nStartCol] = pCol->pItems[nIndex].nRow;
/*N*/           pNextIndices[i-nStartCol] = nIndex;
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           pNextRows[i-nStartCol] = MAXROW+1;      // nichts gefunden
/*N*/           pNextIndices[i-nStartCol] = MAXROW+1;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (pNextRows[0] != nRow1)
/*N*/       Advance();
/*N*/ }

/*N*/ ScHorizontalCellIterator::~ScHorizontalCellIterator()
/*N*/ {
/*N*/   delete [] pNextRows;
/*N*/   delete [] pNextIndices;
/*N*/ }

/*N*/ ScBaseCell* ScHorizontalCellIterator::GetNext( USHORT& rCol, USHORT& rRow )
/*N*/ {
/*N*/   if ( bMore )
/*N*/   {
/*N*/       rCol = nCol;
/*N*/       rRow = nRow;
/*N*/
/*N*/       ScColumn* pCol = &pDoc->pTab[nTab]->aCol[nCol];
/*N*/       USHORT nIndex = pNextIndices[nCol-nStartCol];
/*N*/       DBG_ASSERT( nIndex < pCol->nCount, "ScHorizontalCellIterator::GetNext: nIndex out of range" );
/*N*/       ScBaseCell* pCell = pCol->pItems[nIndex].pCell;
/*N*/       if ( ++nIndex < pCol->nCount )
/*N*/       {
/*N*/           pNextRows[nCol-nStartCol] = pCol->pItems[nIndex].nRow;
/*N*/           pNextIndices[nCol-nStartCol] = nIndex;
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           pNextRows[nCol-nStartCol] = MAXROW+1;       // nichts gefunden
/*N*/           pNextIndices[nCol-nStartCol] = MAXROW+1;
/*N*/       }
/*N*/
/*N*/       Advance();
/*N*/       return pCell;
/*N*/   }
/*N*/   else
/*N*/       return NULL;
/*N*/ }

/*N*/ BOOL ScHorizontalCellIterator::ReturnNext( USHORT& rCol, USHORT& rRow )
/*N*/ {
/*N*/   rCol = nCol;
/*N*/   rRow = nRow;
/*N*/   return bMore;
/*N*/ }

/*N*/ void ScHorizontalCellIterator::Advance()
/*N*/ {
/*N*/   BOOL bFound = FALSE;
/*N*/   USHORT i;
/*N*/
/*N*/   for (i=nCol+1; i<=nEndCol && !bFound; i++)
/*N*/       if (pNextRows[i-nStartCol] == nRow)
/*N*/       {
/*N*/           nCol = i;
/*N*/           bFound = TRUE;
/*N*/       }
/*N*/
/*N*/   if (!bFound)
/*N*/   {
/*N*/       USHORT nMinRow = MAXROW+1;
/*N*/       for (i=nStartCol; i<=nEndCol; i++)
/*N*/           if (pNextRows[i-nStartCol] < nMinRow)
/*N*/           {
/*N*/               nCol = i;
/*N*/               nMinRow = pNextRows[i-nStartCol];
/*N*/           }
/*N*/
/*N*/       if (nMinRow <= nEndRow)
/*N*/       {
/*N*/           nRow = nMinRow;
/*N*/           bFound = TRUE;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if ( !bFound )
/*N*/       bMore = FALSE;
/*N*/ }

//-------------------------------------------------------------------------------

//STRIP001 ScHorizontalAttrIterator::ScHorizontalAttrIterator( ScDocument* pDocument, USHORT nTable,
//STRIP001                          USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2 ) :
//STRIP001  pDoc( pDocument ),
//STRIP001  nTab( nTable ),
//STRIP001  nStartCol( nCol1 ),
//STRIP001  nStartRow( nRow1 ),
//STRIP001  nEndCol( nCol2 ),
//STRIP001  nEndRow( nRow2 )
//STRIP001 {
//STRIP001  DBG_ASSERT( pDoc->pTab[nTab], "Tabelle nicht da" );
//STRIP001
//STRIP001  USHORT i;
//STRIP001
//STRIP001  nRow = nStartRow;
//STRIP001  nCol = nStartCol;
//STRIP001  bRowEmpty = FALSE;
//STRIP001
//STRIP001  pIndices    = new USHORT[nEndCol-nStartCol+1];
//STRIP001  pNextEnd    = new USHORT[nEndCol-nStartCol+1];
//STRIP001  ppPatterns  = new const ScPatternAttr*[nEndCol-nStartCol+1];
//STRIP001
//STRIP001  USHORT nSkipTo = MAXROW;
//STRIP001  BOOL bEmpty = TRUE;
//STRIP001  for (i=nStartCol; i<=nEndCol; i++)
//STRIP001  {
//STRIP001      USHORT nPos = i - nStartCol;
//STRIP001      ScAttrArray* pArray = pDoc->pTab[nTab]->aCol[i].pAttrArray;
//STRIP001      DBG_ASSERT( pArray, "pArray == 0" );
//STRIP001
//STRIP001      short s;
//STRIP001      pArray->Search( nStartRow, s );
//STRIP001      USHORT nIndex = (USHORT) s;
//STRIP001
//STRIP001      const ScPatternAttr* pPattern = pArray->pData[nIndex].pPattern;
//STRIP001      USHORT nThisEnd = pArray->pData[nIndex].nRow;
//STRIP001      if ( IsDefaultItem( pPattern ) )
//STRIP001      {
//STRIP001          pPattern = NULL;
//STRIP001          if ( nThisEnd < nSkipTo )
//STRIP001              nSkipTo = nThisEnd;         // nSkipTo kann gleich hier gesetzt werden
//STRIP001      }
//STRIP001      else
//STRIP001          bEmpty = FALSE;                 // Attribute gefunden
//STRIP001
//STRIP001      pIndices[nPos] = nIndex;
//STRIP001      pNextEnd[nPos] = nThisEnd;
//STRIP001      ppPatterns[nPos] = pPattern;
//STRIP001  }
//STRIP001
//STRIP001  if (bEmpty)
//STRIP001      nRow = nSkipTo;                     // bis zum naechsten Bereichsende ueberspringen
//STRIP001  bRowEmpty = bEmpty;
//STRIP001 }
//STRIP001
//STRIP001 ScHorizontalAttrIterator::~ScHorizontalAttrIterator()
//STRIP001 {
//STRIP001  delete[] (ScPatternAttr**)ppPatterns;
//STRIP001  delete[] pNextEnd;
//STRIP001  delete[] pIndices;
//STRIP001 }
//STRIP001
//STRIP001 const ScPatternAttr* ScHorizontalAttrIterator::GetNext( USHORT& rCol1, USHORT& rCol2, USHORT& rRow )
//STRIP001 {
//STRIP001  for (;;)
//STRIP001  {
//STRIP001      if (!bRowEmpty)
//STRIP001      {
//STRIP001          // in dieser Zeile suchen
//STRIP001
//STRIP001          while ( nCol <= nEndCol && !ppPatterns[nCol-nStartCol] )
//STRIP001              ++nCol;
//STRIP001
//STRIP001          if ( nCol <= nEndCol )
//STRIP001          {
//STRIP001              const ScPatternAttr* pPat = ppPatterns[nCol-nStartCol];
//STRIP001              rRow = nRow;
//STRIP001              rCol1 = nCol;
//STRIP001              while ( nCol < nEndCol && ppPatterns[nCol+1-nStartCol] == pPat )
//STRIP001                  ++nCol;
//STRIP001              rCol2 = nCol;
//STRIP001              ++nCol;                 // hochzaehlen fuer naechsten Aufruf
//STRIP001              return pPat;            // gefunden
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // naechste Zeile
//STRIP001
//STRIP001      ++nRow;
//STRIP001      if ( nRow > nEndRow )       // schon am Ende?
//STRIP001          return NULL;            // nichts gefunden
//STRIP001
//STRIP001      BOOL bEmpty = TRUE;
//STRIP001      for (USHORT i=nStartCol; i<=nEndCol; i++)
//STRIP001      {
//STRIP001          USHORT nPos = i-nStartCol;
//STRIP001          if ( pNextEnd[nPos] < nRow )
//STRIP001          {
//STRIP001              ScAttrArray* pArray = pDoc->pTab[nTab]->aCol[i].pAttrArray;
//STRIP001
//STRIP001              USHORT nIndex = ++pIndices[nPos];
//STRIP001              if ( nIndex < pArray->nCount )
//STRIP001              {
//STRIP001                  const ScPatternAttr* pPattern = pArray->pData[nIndex].pPattern;
//STRIP001                  USHORT nThisEnd = pArray->pData[nIndex].nRow;
//STRIP001                  if ( IsDefaultItem( pPattern ) )
//STRIP001                      pPattern = NULL;
//STRIP001                  else
//STRIP001                      bEmpty = FALSE;                 // Attribute gefunden
//STRIP001
//STRIP001                  pNextEnd[nPos] = nThisEnd;
//STRIP001                  ppPatterns[nPos] = pPattern;
//STRIP001
//STRIP001                  DBG_ASSERT( pNextEnd[nPos] >= nRow, "Reihenfolge durcheinander" );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  DBG_ERROR("AttrArray reicht nicht bis MAXROW");
//STRIP001                  pNextEnd[nPos] = MAXROW;
//STRIP001                  ppPatterns[nPos] = NULL;
//STRIP001              }
//STRIP001          }
//STRIP001          else if ( ppPatterns[nPos] )
//STRIP001              bEmpty = FALSE;                         // Bereich noch nicht zuende
//STRIP001      }
//STRIP001
//STRIP001      if (bEmpty)
//STRIP001      {
//STRIP001          USHORT nCount = nEndCol-nStartCol+1;
//STRIP001          USHORT nSkipTo = pNextEnd[0];               // naechstes Bereichsende suchen
//STRIP001          for (i=1; i<nCount; i++)
//STRIP001              if ( pNextEnd[i] < nSkipTo )
//STRIP001                  nSkipTo = pNextEnd[i];
//STRIP001          nRow = nSkipTo;                             // leere Zeilen ueberspringen
//STRIP001      }
//STRIP001      bRowEmpty = bEmpty;
//STRIP001      nCol = nStartCol;           // wieder links anfangen
//STRIP001  }
//STRIP001
//STRIP001  return NULL;
//STRIP001 }

//-------------------------------------------------------------------------------

//STRIP001 inline BOOL IsGreater( USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2 )
//STRIP001 {
//STRIP001  return ( nRow1 > nRow2 ) || ( nRow1 == nRow2 && nCol1 > nCol2 );
//STRIP001 }
//STRIP001
//STRIP001 ScUsedAreaIterator::ScUsedAreaIterator( ScDocument* pDocument, USHORT nTable,
//STRIP001                          USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2 ) :
//STRIP001  aCellIter( pDocument, nTable, nCol1, nRow1, nCol2, nRow2 ),
//STRIP001  aAttrIter( pDocument, nTable, nCol1, nRow1, nCol2, nRow2 ),
//STRIP001  nNextCol( nCol1 ),
//STRIP001  nNextRow( nRow1 )
//STRIP001 {
//STRIP001  pCell    = aCellIter.GetNext( nCellCol, nCellRow );
//STRIP001  pPattern = aAttrIter.GetNext( nAttrCol1, nAttrCol2, nAttrRow );
//STRIP001 }
//STRIP001
//STRIP001 ScUsedAreaIterator::~ScUsedAreaIterator()
//STRIP001 {
//STRIP001 }
//STRIP001
//STRIP001 BOOL ScUsedAreaIterator::GetNext()
//STRIP001 {
//STRIP001  //  Iteratoren weiterzaehlen
//STRIP001
//STRIP001  if ( pCell && IsGreater( nNextCol, nNextRow, nCellCol, nCellRow ) )
//STRIP001      pCell = aCellIter.GetNext( nCellCol, nCellRow );
//STRIP001
//STRIP001  while ( pCell && pCell->GetCellType() == CELLTYPE_NOTE && !pCell->GetNotePtr() )
//STRIP001      pCell = aCellIter.GetNext( nCellCol, nCellRow );
//STRIP001
//STRIP001  if ( pPattern && IsGreater( nNextCol, nNextRow, nAttrCol2, nAttrRow ) )
//STRIP001      pPattern = aAttrIter.GetNext( nAttrCol1, nAttrCol2, nAttrRow );
//STRIP001
//STRIP001  if ( pPattern && nAttrRow == nNextRow && nAttrCol1 < nNextCol )
//STRIP001      nAttrCol1 = nNextCol;
//STRIP001
//STRIP001  //  naechsten Abschnitt heraussuchen
//STRIP001
//STRIP001  BOOL bFound = TRUE;
//STRIP001  BOOL bUseCell = FALSE;
//STRIP001
//STRIP001  if ( pCell && pPattern )
//STRIP001  {
//STRIP001      if ( IsGreater( nCellCol, nCellRow, nAttrCol1, nAttrRow ) )     // vorne nur Attribute ?
//STRIP001      {
//STRIP001          pFoundCell = NULL;
//STRIP001          pFoundPattern = pPattern;
//STRIP001          nFoundRow = nAttrRow;
//STRIP001          nFoundStartCol = nAttrCol1;
//STRIP001          if ( nCellRow == nAttrRow && nCellCol <= nAttrCol2 )        // auch Zelle im Bereich ?
//STRIP001              nFoundEndCol = nCellCol - 1;                            // nur bis vor der Zelle
//STRIP001          else
//STRIP001              nFoundEndCol = nAttrCol2;                               // alles
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          bUseCell = TRUE;
//STRIP001          if ( nAttrRow == nCellRow && nAttrCol1 == nCellCol )        // Attribute auf der Zelle ?
//STRIP001              pFoundPattern = pPattern;
//STRIP001          else
//STRIP001              pFoundPattern = NULL;
//STRIP001      }
//STRIP001  }
//STRIP001  else if ( pCell )                   // nur Zelle -> direkt uebernehmen
//STRIP001  {
//STRIP001      pFoundPattern = NULL;
//STRIP001      bUseCell = TRUE;                // Position von Zelle
//STRIP001  }
//STRIP001  else if ( pPattern )                // nur Attribute -> direkt uebernehmen
//STRIP001  {
//STRIP001      pFoundCell = NULL;
//STRIP001      pFoundPattern = pPattern;
//STRIP001      nFoundRow = nAttrRow;
//STRIP001      nFoundStartCol = nAttrCol1;
//STRIP001      nFoundEndCol = nAttrCol2;
//STRIP001  }
//STRIP001  else                                // gar nichts
//STRIP001      bFound = FALSE;
//STRIP001
//STRIP001  if ( bUseCell )                     // Position von Zelle
//STRIP001  {
//STRIP001      pFoundCell = pCell;
//STRIP001      nFoundRow = nCellRow;
//STRIP001      nFoundStartCol = nFoundEndCol = nCellCol;
//STRIP001  }
//STRIP001
//STRIP001  if (bFound)
//STRIP001  {
//STRIP001      nNextRow = nFoundRow;
//STRIP001      nNextCol = nFoundEndCol + 1;
//STRIP001  }
//STRIP001
//STRIP001  return bFound;
//STRIP001 }

//-------------------------------------------------------------------------------

/*N*/ ScDocAttrIterator::ScDocAttrIterator(ScDocument* pDocument, USHORT nTable,
/*N*/                                   USHORT nCol1, USHORT nRow1,
/*N*/                                   USHORT nCol2, USHORT nRow2) :
/*N*/   pDoc( pDocument ),
/*N*/   nTab( nTable ),
/*N*/   nCol( nCol1 ),
/*N*/   nEndCol( nCol2 ),
/*N*/   nStartRow( nRow1 ),
/*N*/   nEndRow( nRow2 )
/*N*/ {
/*N*/   if ( nTab<=MAXTAB && pDoc->pTab[nTab] )
/*N*/       pColIter = pDoc->pTab[nTab]->aCol[nCol].CreateAttrIterator( nStartRow, nEndRow );
/*N*/   else
/*N*/       pColIter = NULL;
/*N*/ }

/*N*/ ScDocAttrIterator::~ScDocAttrIterator()
/*N*/ {
/*N*/   delete pColIter;
/*N*/ }

/*N*/ const ScPatternAttr* ScDocAttrIterator::GetNext( USHORT& rCol, USHORT& rRow1, USHORT& rRow2 )
/*N*/ {
/*N*/   while ( pColIter )
/*N*/   {
/*N*/       const ScPatternAttr* pPattern = pColIter->Next( rRow1, rRow2 );
/*N*/       if ( pPattern )
/*N*/       {
/*N*/           rCol = nCol;
/*N*/           return pPattern;
/*N*/       }
/*N*/
/*N*/       delete pColIter;
/*N*/       ++nCol;
/*N*/       if ( nCol <= nEndCol )
/*N*/           pColIter = pDoc->pTab[nTab]->aCol[nCol].CreateAttrIterator( nStartRow, nEndRow );
/*N*/       else
/*N*/           pColIter = NULL;
/*N*/   }
/*N*/   return NULL;        // is nix mehr
/*N*/ }

//-------------------------------------------------------------------------------

/*N*/ ScAttrRectIterator::ScAttrRectIterator(ScDocument* pDocument, USHORT nTable,
/*N*/                                   USHORT nCol1, USHORT nRow1,
/*N*/                                   USHORT nCol2, USHORT nRow2) :
/*N*/   pDoc( pDocument ),
/*N*/   nTab( nTable ),
/*N*/   nEndCol( nCol2 ),
/*N*/   nStartRow( nRow1 ),
/*N*/   nEndRow( nRow2 ),
/*N*/   nIterStartCol( nCol1 ),
/*N*/   nIterEndCol( nCol1 )
/*N*/ {
/*N*/   if ( nTab<=MAXTAB && pDoc->pTab[nTab] )
/*N*/   {
/*N*/       pColIter = pDoc->pTab[nTab]->aCol[nIterStartCol].CreateAttrIterator( nStartRow, nEndRow );
/*N*/       while ( nIterEndCol < nEndCol &&
/*N*/               pDoc->pTab[nTab]->aCol[nIterEndCol].IsAllAttrEqual(
/*N*/                   pDoc->pTab[nTab]->aCol[nIterEndCol+1], nStartRow, nEndRow ) )
/*N*/           ++nIterEndCol;
/*N*/   }
/*N*/   else
/*N*/       pColIter = NULL;
/*N*/ }

/*N*/ ScAttrRectIterator::~ScAttrRectIterator()
/*N*/ {
/*N*/   delete pColIter;
/*N*/ }

/*N*/ void ScAttrRectIterator::DataChanged()
/*N*/ {
/*N*/   if (pColIter)
/*N*/   {
/*N*/       USHORT nNextRow = pColIter->GetNextRow();
/*N*/       delete pColIter;
/*N*/       pColIter = pDoc->pTab[nTab]->aCol[nIterStartCol].CreateAttrIterator( nNextRow, nEndRow );
/*N*/   }
/*N*/ }

/*N*/ const ScPatternAttr* ScAttrRectIterator::GetNext( USHORT& rCol1, USHORT& rCol2,
/*N*/                                                   USHORT& rRow1, USHORT& rRow2 )
/*N*/ {
/*N*/   while ( pColIter )
/*N*/   {
/*N*/       const ScPatternAttr* pPattern = pColIter->Next( rRow1, rRow2 );
/*N*/       if ( pPattern )
/*N*/       {
/*N*/           rCol1 = nIterStartCol;
/*N*/           rCol2 = nIterEndCol;
/*N*/           return pPattern;
/*N*/       }
/*N*/
/*N*/       delete pColIter;
/*N*/       nIterStartCol = nIterEndCol+1;
/*N*/       if ( nIterStartCol <= nEndCol )
/*N*/       {
/*N*/           nIterEndCol = nIterStartCol;
/*N*/           pColIter = pDoc->pTab[nTab]->aCol[nIterStartCol].CreateAttrIterator( nStartRow, nEndRow );
/*N*/           while ( nIterEndCol < nEndCol &&
/*N*/                   pDoc->pTab[nTab]->aCol[nIterEndCol].IsAllAttrEqual(
/*N*/                       pDoc->pTab[nTab]->aCol[nIterEndCol+1], nStartRow, nEndRow ) )
/*N*/               ++nIterEndCol;
/*N*/       }
/*N*/       else
/*N*/           pColIter = NULL;
/*N*/   }
/*N*/   return NULL;        // is nix mehr
/*N*/ }

}
