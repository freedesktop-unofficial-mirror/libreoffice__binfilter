/*************************************************************************
 *
 *  $RCSfile: sc_documen4.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 14:35:23 $
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
#include "core_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------

#include <svtools/intitem.hxx>
#include <svtools/zforlist.hxx>
#include <vcl/sound.hxx>

#include "document.hxx"
#include "table.hxx"
#include "globstr.hrc"
#include "subtotal.hxx"
#include "docoptio.hxx"
#include "interpre.hxx"
#include "markdata.hxx"
#include "validat.hxx"
#include "scitems.hxx"
#include "stlpool.hxx"
#include "poolhelp.hxx"
#include "detdata.hxx"
#include "patattr.hxx"
#include "chgtrack.hxx"
#include "progress.hxx"

// -----------------------------------------------------------------------

// Nach der Regula Falsi Methode
/*N*/ BOOL ScDocument::Solver(USHORT nFCol, USHORT nFRow, USHORT nFTab,
/*N*/                       USHORT nVCol, USHORT nVRow, USHORT nVTab,
/*N*/                       const String& sValStr, double& nX)
/*N*/ {
/*N*/   BOOL bRet = FALSE;
/*N*/   nX = 0.0;
/*N*/   if (ValidColRow(nFCol, nFRow) && ValidColRow(nVCol, nVRow) &&
/*N*/       VALIDTAB(nFTab) && VALIDTAB(nVTab) && pTab[nFTab] && pTab[nVTab])
/*N*/   {
/*N*/       CellType eFType, eVType;
/*N*/       GetCellType(nFCol, nFRow, nFTab, eFType);
/*N*/       GetCellType(nVCol, nVRow, nVTab, eVType);
/*N*/       // CELLTYPE_NOTE: kein Value aber von Formel referiert
/*N*/       if (eFType == CELLTYPE_FORMULA && (eVType == CELLTYPE_VALUE
/*N*/               || eVType == CELLTYPE_NOTE) )
/*N*/       {
/*N*/           SingleRefData aRefData;
/*N*/           aRefData.InitFlags();
/*N*/           aRefData.nCol = nVCol;
/*N*/           aRefData.nRow = nVRow;
/*N*/           aRefData.nTab = nVTab;
/*N*/
/*N*/           ScTokenArray aArr;
/*N*/           aArr.AddOpCode( ocBackSolver );
/*N*/           aArr.AddOpCode( ocOpen );
/*N*/           aArr.AddSingleReference( aRefData );
/*N*/           aArr.AddOpCode( ocSep );
/*N*/
/*N*/           aRefData.nCol = nFCol;
/*N*/           aRefData.nRow = nFRow;
/*N*/           aRefData.nTab = nFTab;
/*N*/
/*N*/           aArr.AddSingleReference( aRefData );
/*N*/           aArr.AddOpCode( ocSep );
/*N*/           aArr.AddString( sValStr.GetBuffer() );
/*N*/           aArr.AddOpCode( ocClose );
/*N*/           aArr.AddOpCode( ocStop );
/*N*/
/*N*/           ScFormulaCell* pCell = new ScFormulaCell( this, ScAddress(), &aArr );
/*N*/
/*N*/           if (pCell)
/*N*/           {
/*N*/               pCell->Interpret();
/*N*/               USHORT nErrCode = pCell->GetErrCode();
/*N*/               nX = pCell->GetValueAlways();
/*N*/               if (nErrCode == 0)                  // kein fehler beim Rechnen
/*N*/                   bRet = TRUE;
/*N*/               delete pCell;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }

/*N*/ void ScDocument::InsertMatrixFormula(USHORT nCol1, USHORT nRow1,
/*N*/                                    USHORT nCol2, USHORT nRow2,
/*N*/                                    const ScMarkData& rMark,
/*N*/                                    const String& rFormula,
/*N*/                                    const ScTokenArray* pArr )
/*N*/ {
/*N*/   PutInOrder(nCol1, nCol2);
/*N*/   PutInOrder(nRow1, nRow2);
/*N*/   USHORT i, j, k, nTab1;
/*N*/   i = 0;
/*N*/   BOOL bStop = FALSE;
/*N*/   while (i <= MAXTAB && !bStop)               // erste markierte Tabelle finden
/*N*/   {
/*N*/       if (pTab[i] && rMark.GetTableSelect(i))
/*N*/           bStop = TRUE;
/*N*/       else
/*N*/           i++;
/*N*/   }
/*N*/   nTab1 = i;
/*N*/   if (i == MAXTAB + 1)
/*N*/   {
/*N*/       Sound::Beep();
/*N*/       DBG_ERROR("ScDocument::InsertMatrixFormula Keine Tabelle markiert");
/*N*/       return;
/*N*/   }
/*N*/
/*N*/   ScFormulaCell* pCell;
/*N*/   ScAddress aPos( nCol1, nRow1, nTab1 );
/*N*/   if (pArr)
/*N*/       pCell = new ScFormulaCell( this, aPos, pArr, MM_FORMULA );
/*N*/   else
/*N*/       pCell = new ScFormulaCell( this, aPos, rFormula, MM_FORMULA );
/*N*/   pCell->SetMatColsRows( nCol2 - nCol1 + 1, nRow2 - nRow1 + 1 );
/*N*/   for (i = 0; i <= MAXTAB; i++)
/*N*/   {
/*N*/       if (pTab[i] && rMark.GetTableSelect(i))
/*N*/       {
/*N*/           if (i == nTab1)
/*N*/               pTab[i]->PutCell(nCol1, nRow1, pCell);
/*N*/           else
DBG_ASSERT(0, "STRIP"); //STRIP001 /*?*/                pTab[i]->PutCell(nCol1, nRow1, pCell->Clone(this, ScAddress( nCol1, nRow1, i)));
/*N*/       }
/*N*/   }
/*N*/
/*N*/   SingleRefData aRefData;
/*N*/   aRefData.InitFlags();
/*N*/   aRefData.nCol = nCol1;
/*N*/   aRefData.nRow = nRow1;
/*N*/   aRefData.nTab = nTab1;
/*N*/   aRefData.SetColRel( TRUE );
/*N*/   aRefData.SetRowRel( TRUE );
/*N*/   aRefData.SetTabRel( TRUE );
/*N*/   aRefData.CalcRelFromAbs( ScAddress( nCol1, nRow1, nTab1 ) );
/*N*/
/*N*/   ScTokenArray aArr;
/*N*/   ScToken* t = aArr.AddSingleReference(aRefData);
/*N*/   t->NewOpCode( ocMatRef );
/*N*/
/*N*/   for (i = 0; i <= MAXTAB; i++)
/*N*/   {
/*N*/       if (pTab[i] && rMark.GetTableSelect(i))
/*N*/       {
/*N*/           pTab[i]->DoColResize( nCol1, nCol2, nRow2 - nRow1 + 1 );
/*N*/           if (i != nTab1)
/*N*/           {
/*?*/               aRefData.nTab = i;
/*?*/               aRefData.nRelTab = i - nTab1;
/*?*/               t->GetSingleRef() = aRefData;
/*N*/           }
/*N*/           for (j = nCol1; j <= nCol2; j++)
/*N*/           {
/*N*/               for (k = nRow1; k <= nRow2; k++)
/*N*/               {
/*N*/                   if (j != nCol1 || k != nRow1)       // nicht in der ersten Zelle
/*N*/                   {
/*N*/                       // Array muss geklont werden, damit jede
/*N*/                       // Zelle ein eigenes Array erhaelt!
/*N*/                       aPos = ScAddress( j, k, i );
/*N*/                       t->CalcRelFromAbs( aPos );
/*N*/                       pCell = new ScFormulaCell( this, aPos, aArr.Clone(), MM_REFERENCE );
/*N*/                       pTab[i]->PutCell(j, k, (ScBaseCell*) pCell);
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

//STRIP001 void ScDocument::InsertTableOp(const ScTabOpParam& rParam,      // Mehrfachoperation
//STRIP001                             USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2,
//STRIP001                             const ScMarkData& rMark)
//STRIP001 {
//STRIP001  PutInOrder(nCol1, nCol2);
//STRIP001  PutInOrder(nRow1, nRow2);
//STRIP001  USHORT i, j, k, nTab1;
//STRIP001  i = 0;
//STRIP001  BOOL bStop = FALSE;
//STRIP001  while (i <= MAXTAB && !bStop)               // erste markierte Tabelle finden
//STRIP001  {
//STRIP001      if (pTab[i] && rMark.GetTableSelect(i))
//STRIP001          bStop = TRUE;
//STRIP001      else
//STRIP001          i++;
//STRIP001  }
//STRIP001  nTab1 = i;
//STRIP001  if (i == MAXTAB + 1)
//STRIP001  {
//STRIP001      Sound::Beep();
//STRIP001      DBG_ERROR("ScDocument::InsertTableOp: Keine Tabelle markiert");
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001     ScRefTripel aTrip;
//STRIP001  String aForString = '=';
//STRIP001  if (ScCompiler::pSymbolTableNative)
//STRIP001      aForString += ScCompiler::pSymbolTableNative[SC_OPCODE_TABLE_OP];
//STRIP001  aForString += '(';
//STRIP001  if (rParam.nMode == 0)                          // nur Spalte
//STRIP001  {
//STRIP001         aTrip.Put( rParam.aRefFormulaCell.GetCol(), rParam.aRefFormulaCell.GetRow(),
//STRIP001             rParam.aRefFormulaCell.GetTab(), TRUE, FALSE, FALSE );
//STRIP001         aForString += aTrip.GetRefString(this, nTab1);
//STRIP001         aForString += ';';
//STRIP001         aForString += rParam.aRefColCell.GetRefString(this, nTab1);
//STRIP001         aForString += ';';
//STRIP001         aTrip.Put( nCol1, nRow1, nTab1, FALSE, TRUE, TRUE );
//STRIP001         aForString += aTrip.GetRefString(this, nTab1);
//STRIP001         nCol1++;
//STRIP001         nCol2 = Min( nCol2, (USHORT)(rParam.aRefFormulaEnd.GetCol()-rParam.aRefFormulaCell.GetCol()+nCol1+1) );
//STRIP001     }
//STRIP001  else if (rParam.nMode == 1)                 // nur zeilenweise
//STRIP001  {
//STRIP001         aTrip.Put( rParam.aRefFormulaCell.GetCol(), rParam.aRefFormulaCell.GetRow(),
//STRIP001             rParam.aRefFormulaCell.GetTab(), FALSE, TRUE, FALSE );
//STRIP001         aForString += aTrip.GetRefString(this, nTab1);
//STRIP001         aForString += ';';
//STRIP001         aForString += rParam.aRefRowCell.GetRefString(this, nTab1);
//STRIP001         aForString += ';';
//STRIP001         aTrip.Put( nCol1, nRow1, nTab1, TRUE, FALSE, TRUE );
//STRIP001         aForString += aTrip.GetRefString(this, nTab1);
//STRIP001         nRow1++;
//STRIP001         nRow2 = Min( nRow2, (USHORT)(rParam.aRefFormulaEnd.GetRow()-rParam.aRefFormulaCell.GetRow()+nRow1+1) );
//STRIP001  }
//STRIP001  else                    // beides
//STRIP001  {
//STRIP001         aForString += rParam.aRefFormulaCell.GetRefString(this, nTab1);
//STRIP001         aForString += ';';
//STRIP001         aForString += rParam.aRefColCell.GetRefString(this, nTab1);
//STRIP001         aForString += ';';
//STRIP001         aTrip.Put( nCol1, nRow1 + 1, nTab1, FALSE, TRUE, TRUE );
//STRIP001         aForString += aTrip.GetRefString(this, nTab1);
//STRIP001         aForString += ';';
//STRIP001         aForString += rParam.aRefRowCell.GetRefString(this, nTab1);
//STRIP001         aForString += ';';
//STRIP001         aTrip.Put( nCol1 + 1, nRow1, nTab1, TRUE, FALSE, TRUE );
//STRIP001         aForString += aTrip.GetRefString(this, nTab1);
//STRIP001         nCol1++; nRow1++;
//STRIP001  }
//STRIP001     aForString += ')';
//STRIP001
//STRIP001     ScFormulaCell aRefCell( this, ScAddress( nCol1, nRow1, nTab1 ), aForString, 0l );
//STRIP001     for( i = nCol1; i <= nCol2; i++ )
//STRIP001         for( j = nRow1; j <= nRow2; j++ )
//STRIP001             for (k = 0; k <= MAXTAB; k++)
//STRIP001                 if( pTab[k] && rMark.GetTableSelect(k) )
//STRIP001                     pTab[k]->PutCell( i, j, aRefCell.Clone( this, ScAddress( i, j, k ) ) );
//STRIP001 }

//STRIP001 USHORT ScDocument::GetErrorData( USHORT nCol, USHORT nRow, USHORT nTab ) const
//STRIP001 {
//STRIP001  if (nTab<=MAXTAB && pTab[nTab])
//STRIP001      return pTab[nTab]->GetErrorData( nCol, nRow );
//STRIP001  else
//STRIP001      return 0;
//STRIP001 }

//STRIP001 BOOL ScDocument::GetNextSpellingCell(USHORT& nCol, USHORT& nRow, USHORT nTab,
//STRIP001                      BOOL bInSel, const ScMarkData& rMark) const
//STRIP001 {
//STRIP001  if (nTab<=MAXTAB && pTab[nTab])
//STRIP001      return pTab[nTab]->GetNextSpellingCell( nCol, nRow, bInSel, rMark );
//STRIP001  else
//STRIP001      return FALSE;
//STRIP001 }

/*N*/ BOOL ScDocument::GetNextMarkedCell( USHORT& rCol, USHORT& rRow, USHORT nTab,
/*N*/                                       const ScMarkData& rMark )
/*N*/ {
/*N*/   if (nTab<=MAXTAB && pTab[nTab])
/*N*/       return pTab[nTab]->GetNextMarkedCell( rCol, rRow, rMark );
/*N*/   else
/*N*/       return FALSE;
/*N*/ }

//STRIP001 BOOL ScDocument::ReplaceStyle(const SvxSearchItem& rSearchItem,
//STRIP001                            USHORT nCol, USHORT nRow, USHORT nTab,
//STRIP001                            ScMarkData& rMark,
//STRIP001                            BOOL bIsUndo)
//STRIP001 {
//STRIP001  if (pTab[nTab])
//STRIP001      return pTab[nTab]->ReplaceStyle(rSearchItem, nCol, nRow, rMark, bIsUndo);
//STRIP001  else
//STRIP001      return FALSE;
//STRIP001 }

/*N*/ void ScDocument::CompileDBFormula()
/*N*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001 for (USHORT i=0; i<=MAXTAB; i++)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        if (pTab[i]) pTab[i]->CompileDBFormula();
//STRIP001 /*?*/    }
/*N*/ }

/*N*/ void ScDocument::CompileDBFormula( BOOL bCreateFormulaString )
/*N*/ {
/*N*/   for (USHORT i=0; i<=MAXTAB; i++)
/*N*/   {
/*N*/       if (pTab[i]) pTab[i]->CompileDBFormula( bCreateFormulaString );
/*N*/   }
/*N*/ }

/*N*/ void ScDocument::CompileNameFormula( BOOL bCreateFormulaString )
/*N*/ {
/*N*/   if ( pCondFormList )
DBG_ASSERT(0, "STRIP"); //STRIP001 /*?*/        pCondFormList->CompileAll();    // nach ScNameDlg noetig
/*N*/
/*N*/   for (USHORT i=0; i<=MAXTAB; i++)
/*N*/   {
/*N*/       if (pTab[i]) pTab[i]->CompileNameFormula( bCreateFormulaString );
/*N*/   }
/*N*/ }

/*N*/ void ScDocument::CompileColRowNameFormula()
/*N*/ {
/*N*/   for (USHORT i=0; i<=MAXTAB; i++)
/*N*/   {
/*N*/       if (pTab[i]) pTab[i]->CompileColRowNameFormula();
/*N*/   }
/*N*/ }

/*N*/ void ScDocument::DoColResize( USHORT nTab, USHORT nCol1, USHORT nCol2, USHORT nAdd )
/*N*/ {
/*N*/   if (nTab<=MAXTAB && pTab[nTab])
/*N*/       pTab[nTab]->DoColResize( nCol1, nCol2, nAdd );
/*N*/   else
/*N*/       DBG_ERROR("DoColResize: falsche Tabelle");
/*N*/ }

/*N*/ void ScDocument::InvalidateTableArea()
/*N*/ {
/*N*/   for (USHORT nTab=0; nTab<=MAXTAB && pTab[nTab]; nTab++)
/*N*/   {
/*N*/       pTab[nTab]->InvalidateTableArea();
/*N*/       if ( pTab[nTab]->IsScenario() )
/*N*/           pTab[nTab]->InvalidateScenarioRanges();
/*N*/   }
/*N*/ }

//STRIP001 xub_StrLen ScDocument::GetMaxStringLen( USHORT nTab, USHORT nCol,
//STRIP001                                  USHORT nRowStart, USHORT nRowEnd ) const
//STRIP001 {
//STRIP001  if (nTab<=MAXTAB && pTab[nTab])
//STRIP001      return pTab[nTab]->GetMaxStringLen( nCol, nRowStart, nRowEnd );
//STRIP001  else
//STRIP001      return 0;
//STRIP001 }

//STRIP001 xub_StrLen ScDocument::GetMaxNumberStringLen( USHORT& nPrecision, USHORT nTab,
//STRIP001                                  USHORT nCol,
//STRIP001                                  USHORT nRowStart, USHORT nRowEnd ) const
//STRIP001 {
//STRIP001  if (nTab<=MAXTAB && pTab[nTab])
//STRIP001      return pTab[nTab]->GetMaxNumberStringLen( nPrecision, nCol,
//STRIP001          nRowStart, nRowEnd );
//STRIP001  else
//STRIP001      return 0;
//STRIP001 }

/*N*/ BOOL ScDocument::GetSelectionFunction( ScSubTotalFunc eFunc,
/*N*/                                       const ScAddress& rCursor, const ScMarkData& rMark,
/*N*/                                       double& rResult )
/*N*/ {
/*N*/   ScFunctionData aData(eFunc);
/*N*/
/*N*/   ScRange aSingle( rCursor );
/*N*/   if ( rMark.IsMarked() )
/*N*/       rMark.GetMarkArea(aSingle);
/*N*/
/*N*/   USHORT nStartCol = aSingle.aStart.Col();
/*N*/   USHORT nStartRow = aSingle.aStart.Row();
/*N*/   USHORT nEndCol = aSingle.aEnd.Col();
/*N*/   USHORT nEndRow = aSingle.aEnd.Row();
/*N*/
/*N*/   for (USHORT nTab=0; nTab<=MAXTAB && !aData.bError; nTab++)
/*N*/       if (pTab[nTab] && rMark.GetTableSelect(nTab))
/*N*/           pTab[nTab]->UpdateSelectionFunction( aData,
/*N*/                           nStartCol, nStartRow, nEndCol, nEndRow, rMark );
/*N*/
/*N*/           //! rMark an UpdateSelectionFunction uebergeben !!!!!
/*N*/
/*N*/   if (!aData.bError)
/*N*/       switch (eFunc)
/*N*/       {
/*N*/           case SUBTOTAL_FUNC_SUM:
/*N*/               rResult = aData.nVal;
/*N*/               break;
/*N*/           case SUBTOTAL_FUNC_CNT:
/*N*/           case SUBTOTAL_FUNC_CNT2:
/*N*/               rResult = aData.nCount;
/*N*/               break;
/*N*/           case SUBTOTAL_FUNC_AVE:
/*N*/               if (aData.nCount)
/*N*/                   rResult = aData.nVal / (double) aData.nCount;
/*N*/               else
/*N*/                   aData.bError = TRUE;
/*N*/               break;
/*N*/           case SUBTOTAL_FUNC_MAX:
/*N*/           case SUBTOTAL_FUNC_MIN:
/*N*/               if (aData.nCount)
/*N*/                   rResult = aData.nVal;
/*N*/               else
/*N*/                   aData.bError = TRUE;
/*N*/               break;
/*N*/       }
/*N*/
/*N*/   if (aData.bError)
/*N*/       rResult = 0.0;
/*N*/
/*N*/   return !aData.bError;
/*N*/ }

/*N*/ double ScDocument::RoundValueAsShown( double fVal, ULONG nFormat )
/*N*/ {
DBG_ASSERT(0, "STRIP"); //STRIP001  short nType;
//STRIP001  if ( (nType = GetFormatTable()->GetType( nFormat )) != NUMBERFORMAT_DATE
//STRIP001    && nType != NUMBERFORMAT_TIME && nType != NUMBERFORMAT_DATETIME )
//STRIP001  {
//STRIP001      short nPrecision;
//STRIP001      if ( nFormat )
//STRIP001      {
//STRIP001          nPrecision = (short)GetFormatTable()->GetFormatPrecision( nFormat );
//STRIP001          switch ( nType )
//STRIP001          {
//STRIP001              case NUMBERFORMAT_PERCENT:      // 0,41% == 0,0041
//STRIP001                  nPrecision += 2;
//STRIP001                  break;
//STRIP001              case NUMBERFORMAT_SCIENTIFIC:   // 1,23e-3 == 0,00123
//STRIP001              {
//STRIP001                  if ( fVal > 0.0 )
//STRIP001                      nPrecision -= (short)floor( log10( fVal ) );
//STRIP001                  else if ( fVal < 0.0 )
//STRIP001                      nPrecision -= (short)floor( log10( -fVal ) );
//STRIP001                  break;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001          nPrecision = (short)GetDocOptions().GetStdPrecision();
//STRIP001      double fRound = ::rtl::math::round( fVal, nPrecision );
//STRIP001      if ( ::rtl::math::approxEqual( fVal, fRound ) )
//STRIP001          return fVal;        // durch Rundung hoechstens Fehler
//STRIP001      else
//STRIP001          return fRound;
//STRIP001  }
//STRIP001  else
        return 0;//STRIP001 return fVal;
}

//
//          bedingte Formate und Gueltigkeitsbereiche
//

/*N*/ ULONG ScDocument::AddCondFormat( const ScConditionalFormat& rNew )
/*N*/ {
/*N*/   if (rNew.IsEmpty())
/*N*/       return 0;                   // leer ist immer 0
/*N*/
/*N*/   if (!pCondFormList)
/*N*/       pCondFormList = new ScConditionalFormatList;
/*N*/
/*N*/   ULONG nMax = 0;
/*N*/   USHORT nCount = pCondFormList->Count();
/*N*/   for (USHORT i=0; i<nCount; i++)
/*N*/   {
/*N*/       const ScConditionalFormat* pForm = (*pCondFormList)[i];
/*N*/       ULONG nKey = pForm->GetKey();
/*N*/       if ( pForm->EqualEntries( rNew ) )
/*N*/           return nKey;
/*N*/       if ( nKey > nMax )
/*N*/           nMax = nKey;
/*N*/   }
/*N*/
/*N*/   // Der Aufruf kann aus ScPatternAttr::PutInPool kommen, darum Clone (echte Kopie)
/*N*/
/*N*/   ULONG nNewKey = nMax + 1;
/*N*/   ScConditionalFormat* pInsert = rNew.Clone(this);
/*N*/   pInsert->SetKey( nNewKey );
/*N*/   pCondFormList->InsertNew( pInsert );
/*N*/   return nNewKey;
/*N*/ }

/*N*/ ULONG ScDocument::AddValidationEntry( const ScValidationData& rNew )
/*N*/ {
/*N*/   if (rNew.IsEmpty())
/*N*/       return 0;                   // leer ist immer 0
/*N*/
/*N*/   if (!pValidationList)
/*N*/       pValidationList = new ScValidationDataList;
/*N*/
/*N*/   ULONG nMax = 0;
/*N*/   USHORT nCount = pValidationList->Count();
/*N*/   for (USHORT i=0; i<nCount; i++)
/*N*/   {
/*N*/       const ScValidationData* pData = (*pValidationList)[i];
/*N*/       ULONG nKey = pData->GetKey();
/*N*/       if ( pData->EqualEntries( rNew ) )
/*N*/           return nKey;
/*N*/       if ( nKey > nMax )
/*N*/           nMax = nKey;
/*N*/   }
/*N*/
/*N*/   // Der Aufruf kann aus ScPatternAttr::PutInPool kommen, darum Clone (echte Kopie)
/*N*/
/*N*/   ULONG nNewKey = nMax + 1;
/*N*/   ScValidationData* pInsert = rNew.Clone(this);
/*N*/   pInsert->SetKey( nNewKey );
/*N*/   pValidationList->InsertNew( pInsert );
/*N*/   return nNewKey;
/*N*/ }

//STRIP001 const SfxPoolItem* ScDocument::GetEffItem(
//STRIP001                      USHORT nCol, USHORT nRow, USHORT nTab, USHORT nWhich ) const
//STRIP001 {
//STRIP001  const ScPatternAttr* pPattern = GetPattern( nCol, nRow, nTab );
//STRIP001  if ( pPattern )
//STRIP001  {
//STRIP001      const SfxItemSet& rSet = pPattern->GetItemSet();
//STRIP001      const SfxPoolItem* pItem;
//STRIP001      if ( rSet.GetItemState( ATTR_CONDITIONAL, TRUE, &pItem ) == SFX_ITEM_SET )
//STRIP001      {
//STRIP001          ULONG nIndex = ((const SfxUInt32Item*)pItem)->GetValue();
//STRIP001          if (nIndex && pCondFormList)
//STRIP001          {
//STRIP001              const ScConditionalFormat* pForm = pCondFormList->GetFormat( nIndex );
//STRIP001              if ( pForm )
//STRIP001              {
//STRIP001                  ScBaseCell* pCell = ((ScDocument*)this)->GetCell(ScAddress(nCol,nRow,nTab));
//STRIP001                  String aStyle = pForm->GetCellStyle( pCell, ScAddress(nCol, nRow, nTab) );
//STRIP001                  if (aStyle.Len())
//STRIP001                  {
//STRIP001                      SfxStyleSheetBase* pStyleSheet = xPoolHelper->GetStylePool()->Find(
//STRIP001                                                              aStyle, SFX_STYLE_FAMILY_PARA );
//STRIP001                      if ( pStyleSheet && pStyleSheet->GetItemSet().GetItemState(
//STRIP001                                              nWhich, TRUE, &pItem ) == SFX_ITEM_SET )
//STRIP001                          return pItem;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      return &rSet.Get( nWhich );
//STRIP001  }
//STRIP001  DBG_ERROR("kein Pattern");
//STRIP001  return NULL;
//STRIP001 }

/*N*/ const SfxItemSet* ScDocument::GetCondResult( USHORT nCol, USHORT nRow, USHORT nTab ) const
/*N*/ {
/*N*/   const ScConditionalFormat* pForm = GetCondFormat( nCol, nRow, nTab );
/*N*/   if ( pForm )
/*N*/   {
/*N*/       ScBaseCell* pCell = ((ScDocument*)this)->GetCell(ScAddress(nCol,nRow,nTab));
/*N*/       String aStyle = pForm->GetCellStyle( pCell, ScAddress(nCol, nRow, nTab) );
/*N*/       if (aStyle.Len())
/*N*/       {
/*N*/           SfxStyleSheetBase* pStyleSheet = xPoolHelper->GetStylePool()->Find( aStyle, SFX_STYLE_FAMILY_PARA );
/*N*/           if ( pStyleSheet )
/*N*/               return &pStyleSheet->GetItemSet();
/*N*/           // if style is not there, treat like no condition
/*N*/       }
/*N*/   }
/*N*/   return NULL;
/*N*/ }

/*N*/ const ScConditionalFormat* ScDocument::GetCondFormat(
/*N*/                           USHORT nCol, USHORT nRow, USHORT nTab ) const
/*N*/ {
/*N*/   ULONG nIndex = ((const SfxUInt32Item*)GetAttr(nCol,nRow,nTab,ATTR_CONDITIONAL))->GetValue();
/*N*/   if (nIndex)
/*N*/   {
/*N*/       if (pCondFormList)
/*N*/           return pCondFormList->GetFormat( nIndex );
/*N*/       else
/*N*/           DBG_ERROR("pCondFormList ist 0");
/*N*/   }
/*N*/
/*N*/   return NULL;
/*N*/ }

/*N*/ const ScValidationData*   ScDocument::GetValidationEntry( ULONG nIndex ) const
/*N*/ {
/*N*/   if ( pValidationList )
/*N*/       return pValidationList->GetData( nIndex );
/*N*/   else
/*N*/       return NULL;
/*N*/ }

/*N*/ void ScDocument::FindConditionalFormat( ULONG nKey, ScRangeList& rRanges )
/*N*/ {
/*N*/   for (USHORT i=0; i<=MAXTAB && pTab[i]; i++)
/*N*/       pTab[i]->FindConditionalFormat( nKey, rRanges );
/*N*/ }

//STRIP001 void ScDocument::FindConditionalFormat( ULONG nKey, ScRangeList& rRanges, USHORT nTab )
//STRIP001 {
//STRIP001     if(VALIDTAB(nTab) && pTab[nTab])
//STRIP001         pTab[nTab]->FindConditionalFormat( nKey, rRanges );
//STRIP001 }

/*N*/ void ScDocument::ConditionalChanged( ULONG nKey )
/*N*/ {
/*N*/   if ( nKey && pCondFormList && !bIsClip && !bIsUndo )        // nKey==0 -> noop
/*N*/   {
/*N*/       ScConditionalFormat* pForm = pCondFormList->GetFormat( nKey );
/*N*/       if (pForm)
/*N*/           pForm->InvalidateArea();
/*N*/   }
/*N*/ }

/*N*/ void ScDocument::SetConditionalUsed( ULONG nKey ) // aus dem Speichern der Tabellen
/*N*/ {
/*N*/   if ( nKey && pCondFormList )        // nKey==0 -> noop
/*N*/   {
/*N*/       ScConditionalFormat* pForm = pCondFormList->GetFormat( nKey );
/*N*/       if (pForm)
/*N*/           pForm->SetUsed(TRUE);
/*N*/   }
/*N*/ }

/*N*/ void ScDocument::SetValidationUsed( ULONG nKey )  // aus dem Speichern der Tabellen
/*N*/ {
/*N*/   if ( nKey && pValidationList )      // nKey==0 -> noop
/*N*/   {
/*N*/       ScValidationData* pData = pValidationList->GetData( nKey );
/*N*/       if (pData)
/*N*/           pData->SetUsed(TRUE);
/*N*/   }
/*N*/ }

//STRIP001 void ScDocument::SetCondFormList(ScConditionalFormatList* pNew)
//STRIP001 {
//STRIP001  if (pCondFormList)
//STRIP001  {
//STRIP001      pCondFormList->DeleteAndDestroy( 0, pCondFormList->Count() );
//STRIP001      delete pCondFormList;
//STRIP001  }
//STRIP001
//STRIP001  pCondFormList = pNew;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 BOOL ScDocument::HasDetectiveOperations() const
//STRIP001 {
//STRIP001  return pDetOpList && pDetOpList->Count();
//STRIP001 }

/*N*/ void ScDocument::AddDetectiveOperation( const ScDetOpData& rData )
/*N*/ {
/*N*/   if (!pDetOpList)
/*N*/       pDetOpList = new ScDetOpList;
/*N*/
/*N*/   pDetOpList->Append( new ScDetOpData( rData ) );
/*N*/ }

/*N*/ void ScDocument::ClearDetectiveOperations()
/*N*/ {
/*N*/   delete pDetOpList;      // loescht auch die Eintraege
/*N*/   pDetOpList = NULL;
/*N*/ }

//STRIP001 void ScDocument::SetDetOpList(ScDetOpList* pNew)
//STRIP001 {
//STRIP001  delete pDetOpList;      // loescht auch die Eintraege
//STRIP001  pDetOpList = pNew;
//STRIP001 }

//------------------------------------------------------------------------
//
//      Vergleich von Dokumenten
//
//------------------------------------------------------------------------

//  Pfriemel-Faktoren
#define SC_DOCCOMP_MAXDIFF  256
#define SC_DOCCOMP_MINGOOD  128
#define SC_DOCCOMP_COLUMNS  10
#define SC_DOCCOMP_ROWS     100


//STRIP001 USHORT ScDocument::RowDifferences( USHORT nThisRow, USHORT nThisTab,
//STRIP001                                  ScDocument& rOtherDoc, USHORT nOtherRow, USHORT nOtherTab,
//STRIP001                                  USHORT nMaxCol, USHORT* pOtherCols )
//STRIP001 {
//STRIP001  USHORT nDif = 0;
//STRIP001  USHORT nUsed = 0;
//STRIP001  for (USHORT nThisCol=0; nThisCol<=nMaxCol; nThisCol++)
//STRIP001  {
//STRIP001      USHORT nOtherCol;
//STRIP001      if ( pOtherCols )
//STRIP001          nOtherCol = pOtherCols[nThisCol];
//STRIP001      else
//STRIP001          nOtherCol = nThisCol;
//STRIP001
//STRIP001      if (nOtherCol <= MAXCOL)    // nur Spalten vergleichen, die in beiden Dateien sind
//STRIP001      {
//STRIP001          const ScBaseCell* pThisCell = GetCell( ScAddress( nThisCol, nThisRow, nThisTab ) );
//STRIP001          const ScBaseCell* pOtherCell = rOtherDoc.GetCell( ScAddress( nOtherCol, nOtherRow, nOtherTab ) );
//STRIP001          if (!ScBaseCell::CellEqual( pThisCell, pOtherCell ))
//STRIP001          {
//STRIP001              if ( pThisCell && pOtherCell )
//STRIP001                  nDif += 3;
//STRIP001              else
//STRIP001                  nDif += 4;      // Inhalt <-> leer zaehlt mehr
//STRIP001          }
//STRIP001
//STRIP001          if ( ( pThisCell  && pThisCell->GetCellType()!=CELLTYPE_NOTE ) ||
//STRIP001               ( pOtherCell && pOtherCell->GetCellType()!=CELLTYPE_NOTE ) )
//STRIP001              ++nUsed;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if (nUsed)
//STRIP001      return (nDif*64)/nUsed;         // max.256 (SC_DOCCOMP_MAXDIFF)
//STRIP001
//STRIP001  DBG_ASSERT(!nDif,"Diff ohne Used");
//STRIP001  return 0;
//STRIP001 }

//STRIP001 USHORT ScDocument::ColDifferences( USHORT nThisCol, USHORT nThisTab,
//STRIP001                                  ScDocument& rOtherDoc, USHORT nOtherCol, USHORT nOtherTab,
//STRIP001                                  USHORT nMaxRow, USHORT* pOtherRows )
//STRIP001 {
//STRIP001  //! optimieren mit Iterator oder so
//STRIP001
//STRIP001  USHORT nDif = 0;
//STRIP001  USHORT nUsed = 0;
//STRIP001  for (USHORT nThisRow=0; nThisRow<=nMaxRow; nThisRow++)
//STRIP001  {
//STRIP001      USHORT nOtherRow;
//STRIP001      if ( pOtherRows )
//STRIP001          nOtherRow = pOtherRows[nThisRow];
//STRIP001      else
//STRIP001          nOtherRow = nThisRow;
//STRIP001
//STRIP001      if (nOtherRow <= MAXROW)    // nur Zeilen vergleichen, die in beiden Dateien sind
//STRIP001      {
//STRIP001          const ScBaseCell* pThisCell = GetCell( ScAddress( nThisCol, nThisRow, nThisTab ) );
//STRIP001          const ScBaseCell* pOtherCell = rOtherDoc.GetCell( ScAddress( nOtherCol, nOtherRow, nOtherTab ) );
//STRIP001          if (!ScBaseCell::CellEqual( pThisCell, pOtherCell ))
//STRIP001          {
//STRIP001              if ( pThisCell && pOtherCell )
//STRIP001                  nDif += 3;
//STRIP001              else
//STRIP001                  nDif += 4;      // Inhalt <-> leer zaehlt mehr
//STRIP001          }
//STRIP001
//STRIP001          if ( ( pThisCell  && pThisCell->GetCellType()!=CELLTYPE_NOTE ) ||
//STRIP001               ( pOtherCell && pOtherCell->GetCellType()!=CELLTYPE_NOTE ) )
//STRIP001              ++nUsed;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if (nUsed)
//STRIP001      return (nDif*64)/nUsed;         // max.256
//STRIP001
//STRIP001  DBG_ASSERT(!nDif,"Diff ohne Used");
//STRIP001  return 0;
//STRIP001 }

//STRIP001 void ScDocument::FindOrder( USHORT* pOtherRows, USHORT nThisEndRow, USHORT nOtherEndRow,
//STRIP001                          BOOL bColumns, ScDocument& rOtherDoc, USHORT nThisTab, USHORT nOtherTab,
//STRIP001                          USHORT nEndCol, USHORT* pTranslate, ScProgress* pProgress, ULONG nProAdd )
//STRIP001 {
//STRIP001  //  bColumns=TRUE: Zeilen sind Spalten und umgekehrt
//STRIP001
//STRIP001  USHORT nMaxCont;                        // wieviel weiter
//STRIP001  USHORT nMinGood;                        // was ist ein Treffer (incl.)
//STRIP001  if ( bColumns )
//STRIP001  {
//STRIP001      nMaxCont = SC_DOCCOMP_COLUMNS;      // 10 Spalten
//STRIP001      nMinGood = SC_DOCCOMP_MINGOOD;
//STRIP001      //! Extra Durchgang mit nMinGood = 0 ????
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      nMaxCont = SC_DOCCOMP_ROWS;         // 100 Zeilen
//STRIP001      nMinGood = SC_DOCCOMP_MINGOOD;
//STRIP001  }
//STRIP001  BOOL bUseTotal = bColumns && !pTranslate;       // nur beim ersten Durchgang
//STRIP001
//STRIP001
//STRIP001  USHORT nOtherRow = 0;
//STRIP001  USHORT nComp;
//STRIP001  USHORT nThisRow;
//STRIP001  BOOL bTotal = FALSE;        // ueber verschiedene nThisRow beibehalten
//STRIP001  USHORT nUnknown = 0;
//STRIP001  for (nThisRow = 0; nThisRow <= nThisEndRow; nThisRow++)
//STRIP001  {
//STRIP001      USHORT nTempOther = nOtherRow;
//STRIP001      BOOL bFound = FALSE;
//STRIP001      USHORT nBest = SC_DOCCOMP_MAXDIFF;
//STRIP001      USHORT nMax = Min( nOtherEndRow, (USHORT)( nTempOther + nMaxCont + nUnknown ) );
//STRIP001      for (USHORT i=nTempOther; i<=nMax && nBest; i++)    // bei 0 abbrechen
//STRIP001      {
//STRIP001          if (bColumns)
//STRIP001              nComp = ColDifferences( nThisRow, nThisTab, rOtherDoc, i, nOtherTab, nEndCol, pTranslate );
//STRIP001          else
//STRIP001              nComp = RowDifferences( nThisRow, nThisTab, rOtherDoc, i, nOtherTab, nEndCol, pTranslate );
//STRIP001          if ( nComp < nBest && ( nComp <= nMinGood || bTotal ) )
//STRIP001          {
//STRIP001              nTempOther = i;
//STRIP001              nBest = nComp;
//STRIP001              bFound = TRUE;
//STRIP001          }
//STRIP001          if ( nComp < SC_DOCCOMP_MAXDIFF || bFound )
//STRIP001              bTotal = FALSE;
//STRIP001          else if ( i == nTempOther && bUseTotal )
//STRIP001              bTotal = TRUE;                          // nur ganz oben
//STRIP001      }
//STRIP001      if ( bFound )
//STRIP001      {
//STRIP001          pOtherRows[nThisRow] = nTempOther;
//STRIP001          nOtherRow = nTempOther + 1;
//STRIP001          nUnknown = 0;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pOtherRows[nThisRow] = USHRT_MAX;
//STRIP001          ++nUnknown;
//STRIP001      }
//STRIP001
//STRIP001      if (pProgress)
//STRIP001          pProgress->SetStateOnPercent(nProAdd+nThisRow);
//STRIP001  }
//STRIP001
//STRIP001  //  Bloecke ohne Uebereinstimmung ausfuellen
//STRIP001
//STRIP001  USHORT nFillStart = 0;
//STRIP001  USHORT nFillPos = 0;
//STRIP001  BOOL bInFill = FALSE;
//STRIP001  for (nThisRow = 0; nThisRow <= nThisEndRow+1; nThisRow++)
//STRIP001  {
//STRIP001      USHORT nThisOther = ( nThisRow <= nThisEndRow ) ? pOtherRows[nThisRow] : (nOtherEndRow+1);
//STRIP001      if ( nThisOther <= MAXROW )
//STRIP001      {
//STRIP001          if ( bInFill )
//STRIP001          {
//STRIP001              if ( nThisOther > nFillStart )      // ist was zu verteilen da?
//STRIP001              {
//STRIP001                  USHORT nDiff1 = nThisOther - nFillStart;
//STRIP001                  USHORT nDiff2 = nThisRow   - nFillPos;
//STRIP001                  USHORT nMinDiff = Min(nDiff1, nDiff2);
//STRIP001                  for (USHORT i=0; i<nMinDiff; i++)
//STRIP001                      pOtherRows[nFillPos+i] = nFillStart+i;
//STRIP001              }
//STRIP001
//STRIP001              bInFill = FALSE;
//STRIP001          }
//STRIP001          nFillStart = nThisOther + 1;
//STRIP001          nFillPos = nThisRow + 1;
//STRIP001      }
//STRIP001      else
//STRIP001          bInFill = TRUE;
//STRIP001  }
//STRIP001 }

//STRIP001 void ScDocument::CompareDocument( ScDocument& rOtherDoc )
//STRIP001 {
//STRIP001  if (!pChangeTrack)
//STRIP001      return;
//STRIP001
//STRIP001  USHORT nThisCount = GetTableCount();
//STRIP001  USHORT nOtherCount = rOtherDoc.GetTableCount();
//STRIP001  USHORT* pOtherTabs = new USHORT[nThisCount];
//STRIP001  USHORT nThisTab;
//STRIP001
//STRIP001  //  Tabellen mit gleichen Namen vergleichen
//STRIP001  String aThisName;
//STRIP001  String aOtherName;
//STRIP001  for (nThisTab=0; nThisTab<nThisCount; nThisTab++)
//STRIP001  {
//STRIP001      USHORT nOtherTab = USHRT_MAX;
//STRIP001      if (!IsScenario(nThisTab))  // Szenarien weglassen
//STRIP001      {
//STRIP001          GetName( nThisTab, aThisName );
//STRIP001          for (USHORT nTemp=0; nTemp<nOtherCount && nOtherTab>MAXTAB; nTemp++)
//STRIP001              if (!rOtherDoc.IsScenario(nTemp))
//STRIP001              {
//STRIP001                  rOtherDoc.GetName( nTemp, aOtherName );
//STRIP001                  if ( aThisName == aOtherName )
//STRIP001                      nOtherTab = nTemp;
//STRIP001              }
//STRIP001      }
//STRIP001      pOtherTabs[nThisTab] = nOtherTab;
//STRIP001  }
//STRIP001  //  auffuellen, damit einzeln umbenannte Tabellen nicht wegfallen
//STRIP001  USHORT nFillStart = 0;
//STRIP001  USHORT nFillPos = 0;
//STRIP001  BOOL bInFill = FALSE;
//STRIP001  for (nThisTab = 0; nThisTab <= nThisCount; nThisTab++)
//STRIP001  {
//STRIP001      USHORT nThisOther = ( nThisTab < nThisCount ) ? pOtherTabs[nThisTab] : nOtherCount;
//STRIP001      if ( nThisOther <= MAXTAB )
//STRIP001      {
//STRIP001          if ( bInFill )
//STRIP001          {
//STRIP001              if ( nThisOther > nFillStart )      // ist was zu verteilen da?
//STRIP001              {
//STRIP001                  USHORT nDiff1 = nThisOther - nFillStart;
//STRIP001                  USHORT nDiff2 = nThisTab   - nFillPos;
//STRIP001                  USHORT nMinDiff = Min(nDiff1, nDiff2);
//STRIP001                  for (USHORT i=0; i<nMinDiff; i++)
//STRIP001                      if ( !IsScenario(nFillPos+i) && !rOtherDoc.IsScenario(nFillStart+i) )
//STRIP001                          pOtherTabs[nFillPos+i] = nFillStart+i;
//STRIP001              }
//STRIP001
//STRIP001              bInFill = FALSE;
//STRIP001          }
//STRIP001          nFillStart = nThisOther + 1;
//STRIP001          nFillPos = nThisTab + 1;
//STRIP001      }
//STRIP001      else
//STRIP001          bInFill = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  //
//STRIP001  //  Tabellen in der gefundenen Reihenfolge vergleichen
//STRIP001  //
//STRIP001
//STRIP001  for (nThisTab=0; nThisTab<nThisCount; nThisTab++)
//STRIP001  {
//STRIP001      USHORT nOtherTab = pOtherTabs[nThisTab];
//STRIP001      if ( nOtherTab <= MAXTAB )
//STRIP001      {
//STRIP001          USHORT nThisEndCol = 0;
//STRIP001          USHORT nThisEndRow = 0;
//STRIP001          USHORT nOtherEndCol = 0;
//STRIP001          USHORT nOtherEndRow = 0;
//STRIP001          GetCellArea( nThisTab, nThisEndCol, nThisEndRow );
//STRIP001          rOtherDoc.GetCellArea( nOtherTab, nOtherEndCol, nOtherEndRow );
//STRIP001          USHORT nEndCol = Max(nThisEndCol, nOtherEndCol);
//STRIP001          USHORT nEndRow = Max(nThisEndRow, nOtherEndRow);
//STRIP001          USHORT nThisCol, nThisRow;
//STRIP001          ULONG n1,n2;    // fuer AppendDeleteRange
//STRIP001
//STRIP001          //! ein Progress ueber alle Tabellen ???
//STRIP001          String aTabName;
//STRIP001          GetName( nThisTab, aTabName );
//STRIP001          String aTemplate = ScGlobal::GetRscString(STR_PROGRESS_COMPARING);
//STRIP001          String aProText = aTemplate.GetToken( 0, '#' );
//STRIP001          aProText += aTabName;
//STRIP001          aProText += aTemplate.GetToken( 1, '#' );
//STRIP001          ScProgress aProgress( GetDocumentShell(),
//STRIP001                                      aProText, 3*nThisEndRow );  // 2x FindOrder, 1x hier
//STRIP001          long nProgressStart = 2*nThisEndRow;                    // start fuer hier
//STRIP001
//STRIP001          USHORT* pTempRows = new USHORT[nThisEndRow+1];
//STRIP001          USHORT* pOtherRows = new USHORT[nThisEndRow+1];
//STRIP001          USHORT* pOtherCols = new USHORT[nThisEndCol+1];
//STRIP001
//STRIP001          //  eingefuegte/geloeschte Spalten/Zeilen finden:
//STRIP001          //  Zwei Versuche:
//STRIP001          //  1) Original Zeilen vergleichen                          (pTempRows)
//STRIP001          //  2) Original Spalten vergleichen                         (pOtherCols)
//STRIP001          //     mit dieser Spaltenreihenfolge Zeilen vergleichen     (pOtherRows)
//STRIP001
//STRIP001          //! Spalten vergleichen zweimal mit unterschiedlichem nMinGood ???
//STRIP001
//STRIP001          // 1
//STRIP001          FindOrder( pTempRows, nThisEndRow, nOtherEndRow, FALSE,
//STRIP001                      rOtherDoc, nThisTab, nOtherTab, nEndCol, NULL, &aProgress, 0 );
//STRIP001          // 2
//STRIP001          FindOrder( pOtherCols, nThisEndCol, nOtherEndCol, TRUE,
//STRIP001                      rOtherDoc, nThisTab, nOtherTab, nEndRow, NULL, NULL, 0 );
//STRIP001          FindOrder( pOtherRows, nThisEndRow, nOtherEndRow, FALSE,
//STRIP001                      rOtherDoc, nThisTab, nOtherTab, nThisEndCol,
//STRIP001                      pOtherCols, &aProgress, nThisEndRow );
//STRIP001
//STRIP001          ULONG nMatch1 = 0;  // pTempRows, keine Spalten
//STRIP001          for (nThisRow = 0; nThisRow<=nThisEndRow; nThisRow++)
//STRIP001              if (pTempRows[nThisRow] <= MAXROW)
//STRIP001                  nMatch1 += SC_DOCCOMP_MAXDIFF -
//STRIP001                             RowDifferences( nThisRow, nThisTab, rOtherDoc, pTempRows[nThisRow],
//STRIP001                                              nOtherTab, nEndCol, NULL );
//STRIP001
//STRIP001          ULONG nMatch2 = 0;  // pOtherRows, pOtherCols
//STRIP001          for (nThisRow = 0; nThisRow<=nThisEndRow; nThisRow++)
//STRIP001              if (pOtherRows[nThisRow] <= MAXROW)
//STRIP001                  nMatch2 += SC_DOCCOMP_MAXDIFF -
//STRIP001                             RowDifferences( nThisRow, nThisTab, rOtherDoc, pOtherRows[nThisRow],
//STRIP001                                              nOtherTab, nThisEndCol, pOtherCols );
//STRIP001
//STRIP001          if ( nMatch1 >= nMatch2 )           // ohne Spalten ?
//STRIP001          {
//STRIP001              //  Spalten zuruecksetzen
//STRIP001              for (nThisCol = 0; nThisCol<=nThisEndCol; nThisCol++)
//STRIP001                  pOtherCols[nThisCol] = nThisCol;
//STRIP001
//STRIP001              //  Zeilenarrays vertauschen (geloescht werden sowieso beide)
//STRIP001              USHORT* pSwap = pTempRows;
//STRIP001              pTempRows = pOtherRows;
//STRIP001              pOtherRows = pSwap;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              //  bleibt bei pOtherCols, pOtherRows
//STRIP001          }
//STRIP001
//STRIP001
//STRIP001          //  Change-Actions erzeugen
//STRIP001          //  1) Spalten von rechts
//STRIP001          //  2) Zeilen von unten
//STRIP001          //  3) einzelne Zellen in normaler Reihenfolge
//STRIP001
//STRIP001          //  Actions fuer eingefuegte/geloeschte Spalten
//STRIP001
//STRIP001          USHORT nLastOtherCol = nOtherEndCol + 1;
//STRIP001          //  nThisEndCol ... 0
//STRIP001          for ( nThisCol = nThisEndCol+1; nThisCol > 0; )
//STRIP001          {
//STRIP001              --nThisCol;
//STRIP001              USHORT nOtherCol = pOtherCols[nThisCol];
//STRIP001              if ( nOtherCol <= MAXCOL && nOtherCol+1 < nLastOtherCol )
//STRIP001              {
//STRIP001                  // Luecke -> geloescht
//STRIP001                  ScRange aDelRange( nOtherCol+1, 0, nOtherTab,
//STRIP001                                      nLastOtherCol-1, MAXROW, nOtherTab );
//STRIP001                  pChangeTrack->AppendDeleteRange( aDelRange, &rOtherDoc, n1, n2 );
//STRIP001              }
//STRIP001              if ( nOtherCol > MAXCOL )                       // eingefuegt
//STRIP001              {
//STRIP001                  //  zusammenfassen
//STRIP001                  if ( nThisCol == nThisEndCol || pOtherCols[nThisCol+1] <= MAXCOL )
//STRIP001                  {
//STRIP001                      USHORT nFirstNew = nThisCol;
//STRIP001                      while ( nFirstNew > 0 && pOtherCols[nFirstNew-1] > MAXCOL )
//STRIP001                          --nFirstNew;
//STRIP001                      USHORT nDiff = nThisCol - nFirstNew;
//STRIP001                      ScRange aRange( nLastOtherCol, 0, nOtherTab,
//STRIP001                                      nLastOtherCol+nDiff, MAXROW, nOtherTab );
//STRIP001                      pChangeTrack->AppendInsert( aRange );
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001                  nLastOtherCol = nOtherCol;
//STRIP001          }
//STRIP001          if ( nLastOtherCol > 0 )                            // ganz oben geloescht
//STRIP001          {
//STRIP001              ScRange aDelRange( 0, 0, nOtherTab,
//STRIP001                                  nLastOtherCol-1, MAXROW, nOtherTab );
//STRIP001              pChangeTrack->AppendDeleteRange( aDelRange, &rOtherDoc, n1, n2 );
//STRIP001          }
//STRIP001
//STRIP001          //  Actions fuer eingefuegte/geloeschte Zeilen
//STRIP001
//STRIP001          USHORT nLastOtherRow = nOtherEndRow + 1;
//STRIP001          //  nThisEndRow ... 0
//STRIP001          for ( nThisRow = nThisEndRow+1; nThisRow > 0; )
//STRIP001          {
//STRIP001              --nThisRow;
//STRIP001              USHORT nOtherRow = pOtherRows[nThisRow];
//STRIP001              if ( nOtherRow <= MAXROW && nOtherRow+1 < nLastOtherRow )
//STRIP001              {
//STRIP001                  // Luecke -> geloescht
//STRIP001                  ScRange aDelRange( 0, nOtherRow+1, nOtherTab,
//STRIP001                                      MAXCOL, nLastOtherRow-1, nOtherTab );
//STRIP001                  pChangeTrack->AppendDeleteRange( aDelRange, &rOtherDoc, n1, n2 );
//STRIP001              }
//STRIP001              if ( nOtherRow > MAXROW )                       // eingefuegt
//STRIP001              {
//STRIP001                  //  zusammenfassen
//STRIP001                  if ( nThisRow == nThisEndRow || pOtherRows[nThisRow+1] <= MAXROW )
//STRIP001                  {
//STRIP001                      USHORT nFirstNew = nThisRow;
//STRIP001                      while ( nFirstNew > 0 && pOtherRows[nFirstNew-1] > MAXROW )
//STRIP001                          --nFirstNew;
//STRIP001                      USHORT nDiff = nThisRow - nFirstNew;
//STRIP001                      ScRange aRange( 0, nLastOtherRow, nOtherTab,
//STRIP001                                      MAXCOL, nLastOtherRow+nDiff, nOtherTab );
//STRIP001                      pChangeTrack->AppendInsert( aRange );
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001                  nLastOtherRow = nOtherRow;
//STRIP001          }
//STRIP001          if ( nLastOtherRow > 0 )                            // ganz oben geloescht
//STRIP001          {
//STRIP001              ScRange aDelRange( 0, 0, nOtherTab,
//STRIP001                                  MAXCOL, nLastOtherRow-1, nOtherTab );
//STRIP001              pChangeTrack->AppendDeleteRange( aDelRange, &rOtherDoc, n1, n2 );
//STRIP001          }
//STRIP001
//STRIP001          //  Zeilen durchgehen um einzelne Zellen zu finden
//STRIP001
//STRIP001          for (nThisRow = 0; nThisRow <= nThisEndRow; nThisRow++)
//STRIP001          {
//STRIP001              USHORT nOtherRow = pOtherRows[nThisRow];
//STRIP001              for (USHORT nThisCol = 0; nThisCol <= nThisEndCol; nThisCol++)
//STRIP001              {
//STRIP001                  USHORT nOtherCol = pOtherCols[nThisCol];
//STRIP001                  ScAddress aThisPos( nThisCol, nThisRow, nThisTab );
//STRIP001                  const ScBaseCell* pThisCell = GetCell( aThisPos );
//STRIP001                  const ScBaseCell* pOtherCell = NULL;
//STRIP001                  if ( nOtherCol <= MAXCOL && nOtherRow <= MAXROW )
//STRIP001                  {
//STRIP001                      ScAddress aOtherPos( nOtherCol, nOtherRow, nOtherTab );
//STRIP001                      pOtherCell = rOtherDoc.GetCell( aOtherPos );
//STRIP001                  }
//STRIP001                  if ( !ScBaseCell::CellEqual( pThisCell, pOtherCell ) )
//STRIP001                  {
//STRIP001                      ScRange aRange( aThisPos );
//STRIP001                      ScChangeActionContent* pAction = new ScChangeActionContent( aRange );
//STRIP001                      pAction->SetOldValue( pOtherCell, &rOtherDoc, this );
//STRIP001                      pAction->SetNewValue( pThisCell, this );
//STRIP001                      pChangeTrack->Append( pAction );
//STRIP001                  }
//STRIP001              }
//STRIP001              aProgress.SetStateOnPercent(nProgressStart+nThisRow);
//STRIP001          }
//STRIP001
//STRIP001          delete[] pOtherCols;
//STRIP001          delete[] pOtherRows;
//STRIP001          delete[] pTempRows;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  //! Inhalt von eingefuegten / geloeschten Tabellen ???
//STRIP001  //! Aktionen fuer eingefuegte / geloeschte Tabellen ???
//STRIP001
//STRIP001  delete[] pOtherTabs;
//STRIP001 }





