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


#include <rtl/math.hxx>
#include <unotools/textsearch.hxx>
#include <unotools/collatorwrapper.hxx>
#include <stdlib.h>
#include <unotools/transliterationwrapper.hxx>

#include "scitems.hxx"
#include "cell.hxx"
#include "document.hxx"
#include "globstr.hrc"
#include "patattr.hxx"
#include "subtotal.hxx"
#include "docoptio.hxx"
#include "markdata.hxx"
#include "attarray.hxx"
#include "cellform.hxx"

#include <vector>
namespace binfilter {

//      Testen, ob beim Loeschen von Zwischenergebnissen andere Daten mit geloescht werden
//      (fuer Hinweis-Box)


//      alte Ergebnisse loeschen
//      rParam.nRow2 wird veraendert !


//  harte Zahlenformate loeschen (fuer Ergebnisformeln)



// at least MSC needs this at linkage level to be able to use it in a template

//      neue Zwischenergebnisse
//      rParam.nRow2 wird veraendert !



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
/*?*/                 nCellVal = 0.0;
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
/*?*/               default :
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
/*N*/                         ::com::sun::star::uno::Sequence< sal_Int32 > xOff;
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
/*?*/                       default :
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
/*N*/   USHORT nStartRow(0), nEndRow(0);
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

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
