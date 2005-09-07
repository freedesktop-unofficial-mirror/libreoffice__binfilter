/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_table4.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 16:54:17 $
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

// System - Includes -----------------------------------------------------

#ifdef PCH
// auto strip #include "core_pch.hxx"
#endif

#pragma hdrstop

#pragma optimize("",off)
                                        // sonst Absturz Win beim Fuellen

// INCLUDE ---------------------------------------------------------------

#include "scitems.hxx"
// auto strip #include <bf_svx/algitem.hxx>
// auto strip #include <bf_svx/boxitem.hxx>
// auto strip #include <bf_svx/brshitem.hxx>
// auto strip #include <bf_svx/cntritem.hxx>
// auto strip #include <bf_svx/colritem.hxx>
// auto strip #include <bf_svx/crsditem.hxx>
// auto strip #include <bf_svx/fhgtitem.hxx>
// auto strip #include <bf_svx/fontitem.hxx>
// auto strip #include <bf_svx/langitem.hxx>
// auto strip #include <bf_svx/postitem.hxx>
// auto strip #include <bf_svx/shdditem.hxx>
// auto strip #include <bf_svx/udlnitem.hxx>
// auto strip #include <bf_svx/wghtitem.hxx>
// auto strip #ifndef _SVX_ROTMODIT_HXX //autogen
// auto strip #include <bf_svx/rotmodit.hxx>
// auto strip #endif
// auto strip #include <svtools/zforlist.hxx>
// auto strip #include <vcl/keycodes.hxx>
// auto strip #include <rtl/math.hxx>
// auto strip #include <unotools/charclass.hxx>
#include <math.h>

// auto strip #include "attrib.hxx"
// auto strip #include "patattr.hxx"
// auto strip #include "cell.hxx"
// auto strip #include "table.hxx"
#include "globstr.hrc"
// auto strip #include "global.hxx"
#include "document.hxx"
#include "autoform.hxx"
// auto strip #include "userlist.hxx"
// auto strip #include "zforauto.hxx"
// auto strip #include "subtotal.hxx"
// auto strip #include "compiler.hxx"
// auto strip #include "rangenam.hxx"
// auto strip #include "docpool.hxx"
// auto strip #include "progress.hxx"
namespace binfilter {

// STATIC DATA -----------------------------------------------------------

#define _D_MAX_LONG_  (double) 0x7fffffff

extern USHORT nScFillModeMouseModifier;     // global.cxx

// -----------------------------------------------------------------------

//STRIP001 short lcl_DecompValueString( String& aValue, long& nVal, USHORT* pMinDigits = NULL )
//STRIP001 {
//STRIP001  if ( !aValue.Len() )
//STRIP001  {
//STRIP001      nVal = 0;
//STRIP001      return 0;
//STRIP001  }
//STRIP001  const sal_Unicode* p = aValue.GetBuffer();
//STRIP001  xub_StrLen nNeg = 0;
//STRIP001  xub_StrLen nNum = 0;
//STRIP001  if ( p[nNum] == '-' )
//STRIP001      nNum = nNeg = 1;
//STRIP001  while ( p[nNum] && CharClass::isAsciiNumeric( p[nNum] ) )
//STRIP001      nNum++;
//STRIP001  if ( nNum > nNeg )
//STRIP001  {   // number at the beginning
//STRIP001      nVal = aValue.Copy( 0, nNum ).ToInt32();
//STRIP001      //  #60893# any number with a leading zero sets the minimum number of digits
//STRIP001      if ( p[nNeg] == '0' && pMinDigits && ( nNum - nNeg > *pMinDigits ) )
//STRIP001          *pMinDigits = nNum - nNeg;
//STRIP001      aValue.Erase( 0, nNum );
//STRIP001      return -1;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      nNeg = 0;
//STRIP001      xub_StrLen nEnd = nNum = aValue.Len() - 1;
//STRIP001      while ( nNum && CharClass::isAsciiNumeric( p[nNum] ) )
//STRIP001          nNum--;
//STRIP001      if ( p[nNum] == '-' )
//STRIP001      {
//STRIP001          nNum--;
//STRIP001          nNeg = 1;
//STRIP001      }
//STRIP001      if ( nNum < nEnd - nNeg )
//STRIP001      {   // number at the end
//STRIP001          nVal = aValue.Copy( nNum + 1 ).ToInt32();
//STRIP001          //  #60893# any number with a leading zero sets the minimum number of digits
//STRIP001          if ( p[nNum+1+nNeg] == '0' && pMinDigits && ( nEnd - nNum - nNeg > *pMinDigits ) )
//STRIP001              *pMinDigits = nEnd - nNum - nNeg;
//STRIP001          aValue.Erase( nNum + 1 );
//STRIP001          return 1;
//STRIP001      }
//STRIP001  }
//STRIP001  nVal = 0;
//STRIP001  return 0;
//STRIP001 }

//STRIP001 String lcl_ValueString( long nValue, USHORT nMinDigits )
//STRIP001 {
//STRIP001  if ( nMinDigits <= 1 )
//STRIP001      return String::CreateFromInt32( nValue );           // simple case...
//STRIP001  else
//STRIP001  {
//STRIP001      String aStr = String::CreateFromInt32( Abs( nValue ) );
//STRIP001      if ( aStr.Len() < nMinDigits )
//STRIP001      {
//STRIP001          String aZero;
//STRIP001          aZero.Fill( nMinDigits - aStr.Len(), '0' );
//STRIP001          aStr.Insert( aZero, 0 );
//STRIP001      }
//STRIP001      //  nMinDigits doesn't include the '-' sign -> add after inserting zeros
//STRIP001      if ( nValue < 0 )
//STRIP001          aStr.Insert( '-', 0 );
//STRIP001      return aStr;
//STRIP001  }
//STRIP001 }

//STRIP001 void ScTable::FillAnalyse( USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2,
//STRIP001                          FillCmd& rCmd, FillDateCmd& rDateCmd,
//STRIP001                          double& rInc, USHORT& rMinDigits,
//STRIP001                          ScUserListData*& rListData, USHORT& rListIndex)
//STRIP001 {
//STRIP001  DBG_ASSERT( nCol1==nCol2 || nRow1==nRow2, "FillAnalyse: falscher Bereich" );
//STRIP001
//STRIP001  rInc = 0.0;
//STRIP001  rMinDigits = 0;
//STRIP001  rListData = NULL;
//STRIP001  rCmd = FILL_SIMPLE;
//STRIP001  if ( nScFillModeMouseModifier & KEY_MOD1 )
//STRIP001      return ;        // Ctrl-Taste: Copy
//STRIP001
//STRIP001  USHORT nAddX;
//STRIP001  USHORT nAddY;
//STRIP001  USHORT nCount;
//STRIP001  if (nCol1 == nCol2)
//STRIP001  {
//STRIP001      nAddX = 0;
//STRIP001      nAddY = 1;
//STRIP001      nCount = nRow2 - nRow1 + 1;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      nAddX = 1;
//STRIP001      nAddY = 0;
//STRIP001      nCount = nCol2 - nCol1 + 1;
//STRIP001  }
//STRIP001
//STRIP001  USHORT nCol = nCol1;
//STRIP001  USHORT nRow = nRow1;
//STRIP001
//STRIP001  ScBaseCell* pFirstCell = GetCell( nCol, nRow );
//STRIP001  CellType eCellType = pFirstCell ? pFirstCell->GetCellType() : CELLTYPE_NONE;
//STRIP001
//STRIP001  if (eCellType == CELLTYPE_VALUE)
//STRIP001  {
//STRIP001      UINT32 nFormat = ((const SfxUInt32Item*)GetAttr(nCol,nRow,ATTR_VALUE_FORMAT))->GetValue();
//STRIP001      BOOL bDate = ( pDocument->GetFormatTable()->GetType(nFormat) == NUMBERFORMAT_DATE );
//STRIP001      if (bDate)
//STRIP001      {
//STRIP001          if (nCount > 1)
//STRIP001          {
//STRIP001              long nCmpInc = 0;
//STRIP001              double nVal;
//STRIP001              Date aNullDate = *pDocument->GetFormatTable()->GetNullDate();
//STRIP001              Date aDate1 = aNullDate;
//STRIP001              nVal = ((ScValueCell*)pFirstCell)->GetValue();
//STRIP001              aDate1 += (long)nVal;
//STRIP001              Date aDate2 = aNullDate;
//STRIP001              nVal = GetValue(nCol+nAddX, nRow+nAddY);
//STRIP001              aDate2 += (long)nVal;
//STRIP001              if ( aDate1 != aDate2 )
//STRIP001              {
//STRIP001                  FillDateCmd eType;
//STRIP001                  long nDDiff = aDate2.GetDay()   - (long) aDate1.GetDay();
//STRIP001                  long nMDiff = aDate2.GetMonth() - (long) aDate1.GetMonth();
//STRIP001                  long nYDiff = aDate2.GetYear()  - (long) aDate1.GetYear();
//STRIP001                  if ( nDDiff )
//STRIP001                  {
//STRIP001                      eType = FILL_DAY;
//STRIP001                      nCmpInc = aDate2 - aDate1;
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      eType = FILL_MONTH;
//STRIP001                      nCmpInc = nMDiff + 12 * nYDiff;
//STRIP001                  }
//STRIP001
//STRIP001                  nCol += nAddX; nRow += nAddY;
//STRIP001                  BOOL bVal = TRUE;
//STRIP001                  for (USHORT i=1; i<nCount && bVal; i++)
//STRIP001                  {
//STRIP001                      ScBaseCell* pCell = GetCell(nCol,nRow);
//STRIP001                      if (pCell && pCell->GetCellType() == CELLTYPE_VALUE)
//STRIP001                      {
//STRIP001                          nVal = ((ScValueCell*)pCell)->GetValue();
//STRIP001                          aDate2 = aNullDate + (long) nVal;
//STRIP001                          if ( eType == FILL_DAY )
//STRIP001                          {
//STRIP001                              if ( aDate2-aDate1 != nCmpInc )
//STRIP001                                  bVal = FALSE;
//STRIP001                          }
//STRIP001                          else
//STRIP001                          {
//STRIP001                              nDDiff = aDate2.GetDay()   - (long) aDate1.GetDay();
//STRIP001                              nMDiff = aDate2.GetMonth() - (long) aDate1.GetMonth();
//STRIP001                              nYDiff = aDate2.GetYear()  - (long) aDate1.GetYear();
//STRIP001                              if (nDDiff || ( nMDiff + 12 * nYDiff != nCmpInc ))
//STRIP001                                  bVal = FALSE;
//STRIP001                          }
//STRIP001                          aDate1 = aDate2;
//STRIP001                          nCol += nAddX; nRow += nAddY;
//STRIP001                      }
//STRIP001                      else
//STRIP001                          bVal = FALSE;   // #50965# kein Datum passt auch nicht
//STRIP001                  }
//STRIP001                  if (bVal)
//STRIP001                  {
//STRIP001                      if ( eType == FILL_MONTH && ( nCmpInc % 12 == 0 ) )
//STRIP001                      {
//STRIP001                          eType = FILL_YEAR;
//STRIP001                          nCmpInc /= 12;
//STRIP001                      }
//STRIP001                      rCmd = FILL_DATE;
//STRIP001                      rDateCmd = eType;
//STRIP001                      rInc = nCmpInc;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          else                            // einzelnes Datum -> Tage hochzaehlen
//STRIP001          {
//STRIP001              rCmd = FILL_DATE;
//STRIP001              rDateCmd = FILL_DAY;
//STRIP001              rInc = 1.0;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if (nCount > 1)
//STRIP001          {
//STRIP001              double nVal1 = ((ScValueCell*)pFirstCell)->GetValue();
//STRIP001              double nVal2 = GetValue(nCol+nAddX, nRow+nAddY);
//STRIP001              rInc = nVal2 - nVal1;
//STRIP001              nCol += nAddX; nRow += nAddY;
//STRIP001              BOOL bVal = TRUE;
//STRIP001              for (USHORT i=1; i<nCount && bVal; i++)
//STRIP001              {
//STRIP001                  ScBaseCell* pCell = GetCell(nCol,nRow);
//STRIP001                  if (pCell && pCell->GetCellType() == CELLTYPE_VALUE)
//STRIP001                  {
//STRIP001                      nVal2 = ((ScValueCell*)pCell)->GetValue();
//STRIP001                      double nDiff = nVal2 - nVal1;
//STRIP001                      if ( !::rtl::math::approxEqual( nDiff, rInc ) )
//STRIP001                          bVal = FALSE;
//STRIP001                      nVal1 = nVal2;
//STRIP001                  }
//STRIP001                  else
//STRIP001                      bVal = FALSE;
//STRIP001                  nCol += nAddX; nRow += nAddY;
//STRIP001              }
//STRIP001              if (bVal)
//STRIP001                  rCmd = FILL_LINEAR;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else if (eCellType == CELLTYPE_STRING || eCellType == CELLTYPE_EDIT)
//STRIP001  {
//STRIP001      String aStr;
//STRIP001      GetString(nCol, nRow, aStr);
//STRIP001      rListData = (ScUserListData*)(ScGlobal::GetUserList()->GetData(aStr));
//STRIP001      if (rListData)
//STRIP001      {
//STRIP001          rListData->GetSubIndex(aStr, rListIndex);
//STRIP001          nCol += nAddX; nRow += nAddY;
//STRIP001          for (USHORT i=1; i<nCount && rListData; i++)
//STRIP001          {
//STRIP001              GetString(nCol, nRow, aStr);
//STRIP001              if (!rListData->GetSubIndex(aStr, rListIndex))
//STRIP001                  rListData = NULL;
//STRIP001              nCol += nAddX; nRow += nAddY;
//STRIP001          }
//STRIP001      }
//STRIP001      else if ( nCount > 1 )
//STRIP001      {
//STRIP001          //  pass rMinDigits to all DecompValueString calls
//STRIP001          //  -> longest number defines rMinDigits
//STRIP001
//STRIP001          long nVal1;
//STRIP001          short nFlag1 = lcl_DecompValueString( aStr, nVal1, &rMinDigits );
//STRIP001          if ( nFlag1 )
//STRIP001          {
//STRIP001              long nVal2;
//STRIP001              GetString( nCol+nAddX, nRow+nAddY, aStr );
//STRIP001              short nFlag2 = lcl_DecompValueString( aStr, nVal2, &rMinDigits );
//STRIP001              if ( nFlag1 == nFlag2 )
//STRIP001              {
//STRIP001                  rInc = (double)nVal2 - (double)nVal1;
//STRIP001                  nCol += nAddX; nRow += nAddY;
//STRIP001                  BOOL bVal = TRUE;
//STRIP001                  for (USHORT i=1; i<nCount && bVal; i++)
//STRIP001                  {
//STRIP001                      ScBaseCell* pCell = GetCell(nCol,nRow);
//STRIP001                      CellType eType = pCell->GetCellType();
//STRIP001                      if (pCell && (eType == CELLTYPE_STRING
//STRIP001                              || eType == CELLTYPE_EDIT) )
//STRIP001                      {
//STRIP001                          if ( eType == CELLTYPE_STRING )
//STRIP001                              ((ScStringCell*)pCell)->GetString( aStr );
//STRIP001                          else
//STRIP001                              ((ScEditCell*)pCell)->GetString( aStr );
//STRIP001                          nFlag2 = lcl_DecompValueString( aStr, nVal2, &rMinDigits );
//STRIP001                          if ( nFlag1 == nFlag2 )
//STRIP001                          {
//STRIP001                              double nDiff = (double)nVal2 - (double)nVal1;
//STRIP001                              if ( !::rtl::math::approxEqual( nDiff, rInc ) )
//STRIP001                                  bVal = FALSE;
//STRIP001                              nVal1 = nVal2;
//STRIP001                          }
//STRIP001                          else
//STRIP001                              bVal = FALSE;
//STRIP001                      }
//STRIP001                      else
//STRIP001                          bVal = FALSE;
//STRIP001                      nCol += nAddX; nRow += nAddY;
//STRIP001                  }
//STRIP001                  if (bVal)
//STRIP001                      rCmd = FILL_LINEAR;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          //  call DecompValueString to set rMinDigits
//STRIP001          long nDummy;
//STRIP001          lcl_DecompValueString( aStr, nDummy, &rMinDigits );
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void ScTable::FillFormula(USHORT& nFormulaCounter, BOOL bFirst, ScFormulaCell* pSrcCell,
//STRIP001                        USHORT nDestCol, USHORT nDestRow, BOOL bLast )
//STRIP001 {
//STRIP001 /*   USHORT nTokArrLen = pSrcCell->GetTokenArrayLen();
//STRIP001  if ( nTokArrLen > 15 )                          // mehr als =A1 oder =67
//STRIP001  {
//STRIP001      ScRangeName* pRangeName = pDocument->GetRangeName();
//STRIP001      String aName("___SC_");                     // Wird dieser String veraendert,
//STRIP001                                                  // auch in document2 EraseNonUsed...
//STRIP001                                                  // mitaendern!!
//STRIP001      aName += pRangeName->GetSharedMaxIndex() + 1;
//STRIP001      aName += '_';
//STRIP001      aName += nFormulaCounter;
//STRIP001      nFormulaCounter++;
//STRIP001      if (bFirst)
//STRIP001      {
//STRIP001          ScRangeData *pAktRange = new ScRangeData(
//STRIP001                          pDocument, aName, pSrcCell->GetTokenArray(), nTokArrLen,
//STRIP001                          pSrcCell->GetCol(), pSrcCell->GetRow(), nTab ,RT_SHARED);
//STRIP001          if (!pRangeName->Insert( pAktRange ))
//STRIP001              delete pAktRange;
//STRIP001          else
//STRIP001              bSharedNameInserted = TRUE;
//STRIP001      }
//STRIP001      USHORT nIndex;
//STRIP001      pRangeName->SearchName(aName, nIndex);
//STRIP001      if (!pRangeName)
//STRIP001      {
//STRIP001          DBG_ERROR("ScTable::FillFormula: Falscher Name");
//STRIP001          return;
//STRIP001      }
//STRIP001      nIndex = ((ScRangeData*) ((*pRangeName)[nIndex]))->GetIndex();
//STRIP001      ScTokenArray aArr;
//STRIP001      aArr.AddName(nIndex);
//STRIP001      aArr.AddOpCode(ocStop);
//STRIP001      ScFormulaCell* pDestCell = new ScFormulaCell
//STRIP001          (pDocument, ScAddress( nDestCol, nDestRow, nTab ), aArr );
//STRIP001      aCol[nDestCol].Insert(nDestRow, pDestCell);
//STRIP001  }
//STRIP001  else
//STRIP001 */   {
//STRIP001      pDocument->SetNoListening( TRUE );  // noch falsche Referenzen
//STRIP001      ScFormulaCell* pDestCell = (ScFormulaCell*) pSrcCell->Clone( pDocument,
//STRIP001          ScAddress( nDestCol, nDestRow, nTab ), TRUE );
//STRIP001      aCol[nDestCol].Insert(nDestRow, pDestCell);
//STRIP001 #if 0
//STRIP001 // mit RelRefs unnoetig
//STRIP001      ScAddress aAddr( nDestCol, nDestRow, nTab );
//STRIP001      pDestCell->UpdateReference(URM_COPY,
//STRIP001                       ScRange( aAddr, aAddr ),
//STRIP001                       nDestCol - pSrcCell->aPos.Col(),
//STRIP001                       nDestRow - pSrcCell->aPos.Row(), 0);
//STRIP001 #endif
//STRIP001      if ( bLast && pDestCell->GetMatrixFlag() )
//STRIP001      {
//STRIP001          ScAddress aOrg;
//STRIP001          if ( pDestCell->GetMatrixOrigin( aOrg ) )
//STRIP001          {
//STRIP001              if ( nDestCol >= aOrg.Col() && nDestRow >= aOrg.Row() )
//STRIP001              {
//STRIP001                  ScBaseCell* pOrgCell = pDocument->GetCell( aOrg );
//STRIP001                  if ( pOrgCell && pOrgCell->GetCellType() == CELLTYPE_FORMULA
//STRIP001                    && ((ScFormulaCell*)pOrgCell)->GetMatrixFlag() == MM_FORMULA )
//STRIP001                  {
//STRIP001                      ((ScFormulaCell*)pOrgCell)->SetMatColsRows(
//STRIP001                          nDestCol - aOrg.Col() + 1,
//STRIP001                          nDestRow - aOrg.Row() + 1 );
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      DBG_ERRORFILE( "FillFormula: MatrixOrigin keine Formelzelle mit MM_FORMULA" );
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  DBG_ERRORFILE( "FillFormula: MatrixOrigin rechts unten" );
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              DBG_ERRORFILE( "FillFormula: kein MatrixOrigin" );
//STRIP001          }
//STRIP001      }
//STRIP001      pDocument->SetNoListening( FALSE );
//STRIP001      pDestCell->StartListeningTo( pDocument );
//STRIP001  }
//STRIP001 }

//STRIP001 void ScTable::FillAuto( USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2,
//STRIP001                      USHORT nFillCount, FillDir eFillDir, ScProgress& rProgress )
//STRIP001 {
//STRIP001  if ( (nFillCount == 0) || !ValidColRow(nCol1, nRow1) || !ValidColRow(nCol2, nRow2) )
//STRIP001      return;
//STRIP001
//STRIP001  //
//STRIP001  //  Richtung auswerten
//STRIP001  //
//STRIP001
//STRIP001  BOOL bVertical = (eFillDir == FILL_TO_BOTTOM || eFillDir == FILL_TO_TOP);
//STRIP001  BOOL bPositive = (eFillDir == FILL_TO_BOTTOM || eFillDir == FILL_TO_RIGHT);
//STRIP001
//STRIP001  USHORT nCol;
//STRIP001  USHORT nRow;
//STRIP001  USHORT& rInner = bVertical ? nRow : nCol;       // Schleifenvariablen
//STRIP001  USHORT& rOuter = bVertical ? nCol : nRow;
//STRIP001  USHORT nOStart;
//STRIP001  USHORT nOEnd;
//STRIP001  USHORT nIStart;
//STRIP001  USHORT nIEnd;
//STRIP001  USHORT nISrcStart;
//STRIP001  USHORT nISrcEnd;
//STRIP001
//STRIP001  if (bVertical)
//STRIP001  {
//STRIP001      nOStart = nCol1;
//STRIP001      nOEnd = nCol2;
//STRIP001      if (bPositive)
//STRIP001      {
//STRIP001          nISrcStart = nRow1;
//STRIP001          nISrcEnd = nRow2;
//STRIP001          nIStart = nRow2 + 1;
//STRIP001          nIEnd = nRow2 + nFillCount;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          nISrcStart = nRow2;
//STRIP001          nISrcEnd = nRow1;
//STRIP001          nIStart = nRow1 - 1;
//STRIP001          nIEnd = nRow1 - nFillCount;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      nOStart = nRow1;
//STRIP001      nOEnd = nRow2;
//STRIP001      if (bPositive)
//STRIP001      {
//STRIP001          nISrcStart = nCol1;
//STRIP001          nISrcEnd = nCol2;
//STRIP001          nIStart = nCol2 + 1;
//STRIP001          nIEnd = nCol2 + nFillCount;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          nISrcStart = nCol2;
//STRIP001          nISrcEnd = nCol1;
//STRIP001          nIStart = nCol1 - 1;
//STRIP001          nIEnd = nCol1 - nFillCount;
//STRIP001      }
//STRIP001  }
//STRIP001  USHORT nIMin = nIStart;
//STRIP001  USHORT nIMax = nIEnd;
//STRIP001  PutInOrder(nIMin,nIMax);
//STRIP001  if (bVertical)
//STRIP001      DeleteArea(nCol1, nIMin, nCol2, nIMax, IDF_ALL);
//STRIP001  else
//STRIP001      DeleteArea(nIMin, nRow1, nIMax, nRow2, IDF_ALL);
//STRIP001
//STRIP001  ULONG nProgress = rProgress.GetState();
//STRIP001
//STRIP001  //
//STRIP001  //  ausfuehren
//STRIP001  //
//STRIP001
//STRIP001  USHORT nActFormCnt = 0;
//STRIP001  for (rOuter = nOStart; rOuter <= nOEnd; rOuter++)
//STRIP001  {
//STRIP001      USHORT nMaxFormCnt = 0;                     // fuer Formeln
//STRIP001
//STRIP001      //  Attributierung uebertragen
//STRIP001
//STRIP001      const ScPatternAttr* pSrcPattern;
//STRIP001      USHORT nAtSrc = nISrcStart;
//STRIP001      ScPatternAttr* pNewPattern = NULL;
//STRIP001      BOOL bGetPattern = TRUE;
//STRIP001      for (rInner = nIStart;;)
//STRIP001      {
//STRIP001          const ScStyleSheet* pStyleSheet;
//STRIP001          if ( bGetPattern )
//STRIP001          {
//STRIP001              if ( pNewPattern )
//STRIP001                  delete pNewPattern;
//STRIP001              if (bVertical)      // rInner&:=nRow, rOuter&:=nCol
//STRIP001                  pSrcPattern = aCol[nCol].GetPattern(nAtSrc);
//STRIP001              else                // rInner&:=nCol, rOuter&:=nRow
//STRIP001                  pSrcPattern = aCol[nAtSrc].GetPattern(nRow);
//STRIP001              bGetPattern = FALSE;
//STRIP001              pStyleSheet = pSrcPattern->GetStyleSheet();
//STRIP001              //  Merge/Mergeflag nicht uebernehmen,
//STRIP001              const SfxItemSet& rSet = pSrcPattern->GetItemSet();
//STRIP001              if ( rSet.GetItemState(ATTR_MERGE, FALSE) == SFX_ITEM_SET
//STRIP001                || rSet.GetItemState(ATTR_MERGE_FLAG, FALSE) == SFX_ITEM_SET )
//STRIP001              {
//STRIP001                  pNewPattern = new ScPatternAttr( *pSrcPattern );
//STRIP001                  SfxItemSet& rNewSet = pNewPattern->GetItemSet();
//STRIP001                  rNewSet.ClearItem(ATTR_MERGE);
//STRIP001                  rNewSet.ClearItem(ATTR_MERGE_FLAG);
//STRIP001              }
//STRIP001              else
//STRIP001                  pNewPattern = NULL;
//STRIP001          }
//STRIP001
//STRIP001          if ( bVertical && nISrcStart == nISrcEnd )
//STRIP001          {
//STRIP001              //  Attribute komplett am Stueck setzen
//STRIP001              if (pNewPattern || pSrcPattern != pDocument->GetDefPattern())
//STRIP001              {
//STRIP001                  //  Default steht schon da (DeleteArea)
//STRIP001                  USHORT nY1 = Min( nIStart, nIEnd );
//STRIP001                  USHORT nY2 = Max( nIStart, nIEnd );
//STRIP001                  if ( pStyleSheet )
//STRIP001                      aCol[nCol].ApplyStyleArea( nY1, nY2, *pStyleSheet );
//STRIP001                  if ( pNewPattern )
//STRIP001                      aCol[nCol].ApplyPatternArea( nY1, nY2, *pNewPattern );
//STRIP001                  else
//STRIP001                      aCol[nCol].ApplyPatternArea( nY1, nY2, *pSrcPattern );
//STRIP001              }
//STRIP001              break;      // Schleife abbrechen
//STRIP001          }
//STRIP001
//STRIP001          if ( pSrcPattern != aCol[nCol].GetPattern( nRow ) )
//STRIP001          {
//STRIP001              //  Vorlage auch uebernehmen
//STRIP001              //! am AttrArray mit ApplyPattern zusammenfassen ??
//STRIP001              if ( pStyleSheet )
//STRIP001                  aCol[nCol].ApplyStyle( nRow, *pStyleSheet );
//STRIP001
//STRIP001              //  ApplyPattern statt SetPattern um alte MergeFlags stehenzulassen
//STRIP001              if ( pNewPattern )
//STRIP001                  aCol[nCol].ApplyPattern( nRow, *pNewPattern );
//STRIP001              else
//STRIP001                  aCol[nCol].ApplyPattern( nRow, *pSrcPattern );
//STRIP001          }
//STRIP001
//STRIP001          if (nAtSrc==nISrcEnd)
//STRIP001          {
//STRIP001              if ( nAtSrc != nISrcStart )
//STRIP001              {   // mehr als eine Source-Zelle
//STRIP001                  nAtSrc = nISrcStart;
//STRIP001                  bGetPattern = TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001          else if (bPositive)
//STRIP001          {
//STRIP001              ++nAtSrc;
//STRIP001              bGetPattern = TRUE;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              --nAtSrc;
//STRIP001              bGetPattern = TRUE;
//STRIP001          }
//STRIP001
//STRIP001          if (rInner == nIEnd) break;
//STRIP001          if (bPositive) ++rInner; else --rInner;
//STRIP001      }
//STRIP001      if ( pNewPattern )
//STRIP001          delete pNewPattern;
//STRIP001
//STRIP001      //  Analyse
//STRIP001
//STRIP001      FillCmd eFillCmd;
//STRIP001      FillDateCmd eDateCmd;
//STRIP001      double nInc;
//STRIP001      USHORT nMinDigits;
//STRIP001      ScUserListData* pListData = NULL;
//STRIP001      USHORT nListIndex;
//STRIP001      if (bVertical)
//STRIP001          FillAnalyse(nCol,nRow1, nCol,nRow2, eFillCmd,eDateCmd, nInc,nMinDigits, pListData,nListIndex);
//STRIP001      else
//STRIP001          FillAnalyse(nCol1,nRow, nCol2,nRow, eFillCmd,eDateCmd, nInc,nMinDigits, pListData,nListIndex);
//STRIP001
//STRIP001      if (bVertical)
//STRIP001          aCol[nCol].Resize( aCol[nCol].GetCellCount() + nFillCount );
//STRIP001
//STRIP001      if (pListData)
//STRIP001      {
//STRIP001          USHORT nListCount = pListData->GetSubCount();
//STRIP001          if ( !bPositive )
//STRIP001          {
//STRIP001              //  nListIndex auf FillAnalyse zeigt auf den letzten Eintrag -> anpassen
//STRIP001              USHORT nSub = nISrcStart - nISrcEnd;
//STRIP001              for (USHORT i=0; i<nSub; i++)
//STRIP001              {
//STRIP001                  if (nListIndex == 0) nListIndex = nListCount;
//STRIP001                  --nListIndex;
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          for (rInner = nIStart;;)
//STRIP001          {
//STRIP001              if (bPositive)
//STRIP001              {
//STRIP001                  ++nListIndex;
//STRIP001                  if (nListIndex >= nListCount) nListIndex = 0;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  if (nListIndex == 0) nListIndex = nListCount;
//STRIP001                  --nListIndex;
//STRIP001              }
//STRIP001              aCol[nCol].Insert(nRow, new ScStringCell(pListData->GetSubStr(nListIndex)));
//STRIP001
//STRIP001              if (rInner == nIEnd) break;
//STRIP001              if (bPositive) ++rInner; else --rInner;
//STRIP001          }
//STRIP001          nProgress += nIMax - nIMin + 1;
//STRIP001          rProgress.SetStateOnPercent( nProgress );
//STRIP001      }
//STRIP001      else if (eFillCmd == FILL_SIMPLE)           // Auffuellen mit Muster
//STRIP001      {
//STRIP001          USHORT nSource = nISrcStart;
//STRIP001          double nDelta;
//STRIP001          if ( nScFillModeMouseModifier & KEY_MOD1 )
//STRIP001              nDelta = 0.0;
//STRIP001          else if ( bPositive )
//STRIP001              nDelta = 1.0;
//STRIP001          else
//STRIP001              nDelta = -1.0;
//STRIP001          double nVal;
//STRIP001          USHORT nFormulaCounter = nActFormCnt;
//STRIP001          BOOL bFirst = TRUE;
//STRIP001          BOOL bGetCell = TRUE;
//STRIP001          USHORT nCellDigits = 0;
//STRIP001          short nHeadNoneTail = 0;
//STRIP001          long nStringValue;
//STRIP001          String aValue;
//STRIP001          ScBaseCell* pSrcCell;
//STRIP001          CellType eCellType;
//STRIP001
//STRIP001          for (rInner = nIStart;;)
//STRIP001          {
//STRIP001              if ( bGetCell )
//STRIP001              {
//STRIP001                  if (bVertical)      // rInner&:=nRow, rOuter&:=nCol
//STRIP001                      pSrcCell = aCol[nCol].GetCell( nSource );
//STRIP001                  else                // rInner&:=nCol, rOuter&:=nRow
//STRIP001                      pSrcCell = aCol[nSource].GetCell( nRow );
//STRIP001                  bGetCell = FALSE;
//STRIP001                  if ( pSrcCell )
//STRIP001                  {
//STRIP001                      eCellType = pSrcCell->GetCellType();
//STRIP001                      switch ( eCellType )
//STRIP001                      {
//STRIP001                          case CELLTYPE_VALUE:
//STRIP001                              nVal = ((ScValueCell*)pSrcCell)->GetValue();
//STRIP001                          break;
//STRIP001                          case CELLTYPE_STRING:
//STRIP001                          case CELLTYPE_EDIT:
//STRIP001                              if ( eCellType == CELLTYPE_STRING )
//STRIP001                                  ((ScStringCell*)pSrcCell)->GetString( aValue );
//STRIP001                              else
//STRIP001                                  ((ScEditCell*)pSrcCell)->GetString( aValue );
//STRIP001                              if ( !(nScFillModeMouseModifier & KEY_MOD1) )
//STRIP001                              {
//STRIP001                                  nCellDigits = 0;    // look at each source cell individually
//STRIP001                                  nHeadNoneTail = lcl_DecompValueString(
//STRIP001                                      aValue, nStringValue, &nCellDigits );
//STRIP001                              }
//STRIP001                          break;
//STRIP001                      }
//STRIP001                  }
//STRIP001                  else
//STRIP001                      eCellType = CELLTYPE_NONE;
//STRIP001              }
//STRIP001              switch (eCellType)
//STRIP001              {
//STRIP001                  case CELLTYPE_VALUE:
//STRIP001                      aCol[nCol].Insert(nRow, new ScValueCell(nVal + nDelta));
//STRIP001                      break;
//STRIP001                  case CELLTYPE_STRING:
//STRIP001                  case CELLTYPE_EDIT:
//STRIP001                      if ( nHeadNoneTail )
//STRIP001                      {
//STRIP001                          String aStr;
//STRIP001                          if ( nHeadNoneTail < 0 )
//STRIP001                          {
//STRIP001                              aStr = lcl_ValueString( nStringValue+(long)nDelta, nCellDigits );
//STRIP001                              aStr += aValue;
//STRIP001                          }
//STRIP001                          else
//STRIP001                          {
//STRIP001                              aStr = aValue;
//STRIP001                              aStr += lcl_ValueString( nStringValue+(long)nDelta, nCellDigits );
//STRIP001                          }
//STRIP001                          aCol[nCol].Insert(nRow, new ScStringCell( aStr ) );
//STRIP001                      }
//STRIP001                      else
//STRIP001                      {
//STRIP001                          switch ( eCellType )
//STRIP001                          {
//STRIP001                              case CELLTYPE_STRING:
//STRIP001                                  aCol[nCol].Insert(nRow,
//STRIP001                                      new ScStringCell(*(ScStringCell*)pSrcCell));
//STRIP001                              break;
//STRIP001                              case CELLTYPE_EDIT:
//STRIP001                                  aCol[nCol].Insert(nRow,
//STRIP001                                      new ScEditCell( *(ScEditCell*)pSrcCell,
//STRIP001                                          pDocument ));
//STRIP001                              break;
//STRIP001                          }
//STRIP001                      }
//STRIP001                      break;
//STRIP001                  case CELLTYPE_FORMULA :
//STRIP001                      FillFormula(nFormulaCounter, bFirst,
//STRIP001                          (ScFormulaCell*) pSrcCell, nCol, nRow,
//STRIP001                          (rInner == nIEnd) );
//STRIP001                      if (nFormulaCounter - nActFormCnt > nMaxFormCnt)
//STRIP001                          nMaxFormCnt = nFormulaCounter - nActFormCnt;
//STRIP001                      break;
//STRIP001              }
//STRIP001
//STRIP001              if (nSource==nISrcEnd)
//STRIP001              {
//STRIP001                  if ( nSource != nISrcStart )
//STRIP001                  {   // mehr als eine Source-Zelle
//STRIP001                      nSource = nISrcStart;
//STRIP001                      bGetCell = TRUE;
//STRIP001                  }
//STRIP001                  if ( !(nScFillModeMouseModifier & KEY_MOD1) )
//STRIP001                  {
//STRIP001                      if ( bPositive )
//STRIP001                          nDelta += 1.0;
//STRIP001                      else
//STRIP001                          nDelta -= 1.0;
//STRIP001                  }
//STRIP001                  nFormulaCounter = nActFormCnt;
//STRIP001                  bFirst = FALSE;
//STRIP001              }
//STRIP001              else if (bPositive)
//STRIP001              {
//STRIP001                  ++nSource;
//STRIP001                  bGetCell = TRUE;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  --nSource;
//STRIP001                  bGetCell = TRUE;
//STRIP001              }
//STRIP001
//STRIP001              //  Progress in der inneren Schleife nur bei teuren Zellen,
//STRIP001              //  und auch dann nicht fuer jede einzelne
//STRIP001
//STRIP001              ++nProgress;
//STRIP001              if ( eCellType == CELLTYPE_FORMULA || eCellType == CELLTYPE_EDIT )
//STRIP001                  rProgress.SetStateOnPercent( nProgress );
//STRIP001
//STRIP001              if (rInner == nIEnd) break;
//STRIP001              if (bPositive) ++rInner; else --rInner;
//STRIP001          }
//STRIP001          rProgress.SetStateOnPercent( nProgress );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if (!bPositive)
//STRIP001              nInc = -nInc;
//STRIP001          double nEndVal = (nInc>=0.0) ? MAXDOUBLE : -MAXDOUBLE;
//STRIP001          if (bVertical)
//STRIP001              FillSeries( nCol, nRow1, nCol, nRow2, nFillCount, eFillDir,
//STRIP001                          eFillCmd, eDateCmd, nInc, nEndVal, nMinDigits, FALSE, rProgress );
//STRIP001          else
//STRIP001              FillSeries( nCol1, nRow, nCol2, nRow, nFillCount, eFillDir,
//STRIP001                          eFillCmd, eDateCmd, nInc, nEndVal, nMinDigits, FALSE, rProgress );
//STRIP001          nProgress = rProgress.GetState();
//STRIP001      }
//STRIP001
//STRIP001      nActFormCnt += nMaxFormCnt;
//STRIP001  }
//STRIP001 }

//STRIP001 String ScTable::GetAutoFillPreview( const ScRange& rSource, USHORT nEndX, USHORT nEndY )
//STRIP001 {
//STRIP001  String aValue;
//STRIP001
//STRIP001  USHORT nCol1 = rSource.aStart.Col();
//STRIP001  USHORT nRow1 = rSource.aStart.Row();
//STRIP001  USHORT nCol2 = rSource.aEnd.Col();
//STRIP001  USHORT nRow2 = rSource.aEnd.Row();
//STRIP001  BOOL bOk = TRUE;
//STRIP001  long nIndex;
//STRIP001  USHORT nSrcCount;
//STRIP001  FillDir eFillDir;
//STRIP001  if ( nEndX == nCol2 && nEndY == nRow2 )     // leer
//STRIP001      bOk = FALSE;
//STRIP001  else if ( nEndX == nCol2 )                  // nach oben/unten
//STRIP001  {
//STRIP001      nEndX = nCol2 = nCol1;                  // nur erste Spalte ansehen
//STRIP001      nSrcCount = nRow2 - nRow1 + 1;
//STRIP001      nIndex = ((long)nEndY) - nRow1;         // kann negativ werden
//STRIP001      if ( nEndY >= nRow1 )
//STRIP001          eFillDir = FILL_TO_BOTTOM;
//STRIP001      else
//STRIP001          eFillDir = FILL_TO_TOP;
//STRIP001  }
//STRIP001  else if ( nEndY == nRow2 )                  // nach links/rechts
//STRIP001  {
//STRIP001      nEndY = nRow2 = nRow1;                  // nur erste Zeile ansehen
//STRIP001      nSrcCount = nCol2 - nCol1 + 1;
//STRIP001      nIndex = ((long)nEndX) - nCol1;         // kann negativ werden
//STRIP001      if ( nEndX >= nCol1 )
//STRIP001          eFillDir = FILL_TO_RIGHT;
//STRIP001      else
//STRIP001          eFillDir = FILL_TO_LEFT;
//STRIP001  }
//STRIP001  else                                        // Richtung nicht eindeutig
//STRIP001      bOk = FALSE;
//STRIP001
//STRIP001  if ( bOk )
//STRIP001  {
//STRIP001      FillCmd eFillCmd;
//STRIP001      FillDateCmd eDateCmd;
//STRIP001      double nInc;
//STRIP001      USHORT nMinDigits;
//STRIP001      ScUserListData* pListData = NULL;
//STRIP001      USHORT nListIndex;
//STRIP001
//STRIP001      FillAnalyse(nCol1,nRow1, nCol2,nRow2, eFillCmd,eDateCmd, nInc,nMinDigits, pListData,nListIndex);
//STRIP001
//STRIP001      if ( pListData )                            // benutzerdefinierte Liste
//STRIP001      {
//STRIP001          USHORT nListCount = pListData->GetSubCount();
//STRIP001          if ( nListCount )
//STRIP001          {
//STRIP001              USHORT nSub = nSrcCount - 1;    //  nListIndex ist vom letzten Source-Eintrag
//STRIP001              while ( nIndex < nSub )
//STRIP001                  nIndex += nListCount;
//STRIP001              USHORT nPos = ( nListIndex + nIndex - nSub ) % nListCount;
//STRIP001              aValue = pListData->GetSubStr(nPos);
//STRIP001          }
//STRIP001      }
//STRIP001      else if ( eFillCmd == FILL_SIMPLE )         // Auffuellen mit Muster
//STRIP001      {
//STRIP001          long nPosIndex = nIndex;
//STRIP001          while ( nPosIndex < 0 )
//STRIP001              nPosIndex += nSrcCount;
//STRIP001          USHORT nPos = nPosIndex % nSrcCount;
//STRIP001          USHORT nSrcX = nCol1;
//STRIP001          USHORT nSrcY = nRow1;
//STRIP001          if ( eFillDir == FILL_TO_TOP || eFillDir == FILL_TO_BOTTOM )
//STRIP001              nSrcY += nPos;
//STRIP001          else
//STRIP001              nSrcX += nPos;
//STRIP001
//STRIP001          ScBaseCell* pCell = GetCell( nSrcX, nSrcY );
//STRIP001          if ( pCell )
//STRIP001          {
//STRIP001              long nDelta;
//STRIP001              if (nIndex >= 0)
//STRIP001                  nDelta = nIndex / nSrcCount;
//STRIP001              else
//STRIP001                  nDelta = ( nIndex - nSrcCount + 1 ) / nSrcCount;    // -1 -> -1
//STRIP001
//STRIP001              CellType eType = pCell->GetCellType();
//STRIP001              switch ( eType )
//STRIP001              {
//STRIP001                  case CELLTYPE_STRING:
//STRIP001                  case CELLTYPE_EDIT:
//STRIP001                  {
//STRIP001                      if ( eType == CELLTYPE_STRING )
//STRIP001                          ((ScStringCell*)pCell)->GetString( aValue );
//STRIP001                      else
//STRIP001                          ((ScEditCell*)pCell)->GetString( aValue );
//STRIP001                      if ( !(nScFillModeMouseModifier & KEY_MOD1) )
//STRIP001                      {
//STRIP001                          long nVal;
//STRIP001                          USHORT nCellDigits = 0; // look at each source cell individually
//STRIP001                          short nFlag = lcl_DecompValueString( aValue, nVal, &nCellDigits );
//STRIP001                          if ( nFlag < 0 )
//STRIP001                              aValue.Insert( lcl_ValueString( nVal + nDelta, nCellDigits ), 0 );
//STRIP001                          else if ( nFlag > 0 )
//STRIP001                              aValue += lcl_ValueString( nVal + nDelta, nCellDigits );
//STRIP001                      }
//STRIP001                  }
//STRIP001                  break;
//STRIP001                  case CELLTYPE_VALUE:
//STRIP001                  {
//STRIP001                      //  dabei kann's keinen Ueberlauf geben...
//STRIP001                      double nVal = ((ScValueCell*)pCell)->GetValue();
//STRIP001                      if ( !(nScFillModeMouseModifier & KEY_MOD1) )
//STRIP001                          nVal += (double) nDelta;
//STRIP001
//STRIP001                      Color* pColor;
//STRIP001                      ULONG nNumFmt = GetNumberFormat( nSrcX, nSrcY );
//STRIP001                      pDocument->GetFormatTable()->
//STRIP001                          GetOutputString( nVal, nNumFmt, aValue, &pColor );
//STRIP001                  }
//STRIP001                  break;
//STRIP001                  //  Formeln nicht
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      else if ( eFillCmd == FILL_LINEAR || eFillCmd == FILL_DATE )        // Werte
//STRIP001      {
//STRIP001          BOOL bOk;
//STRIP001          double nStart;
//STRIP001          short nHeadNoneTail = 0;
//STRIP001          ScBaseCell* pCell = GetCell( nCol1, nRow1 );
//STRIP001          if ( pCell )
//STRIP001          {
//STRIP001              CellType eType = pCell->GetCellType();
//STRIP001              switch ( eType )
//STRIP001              {
//STRIP001                  case CELLTYPE_STRING:
//STRIP001                  case CELLTYPE_EDIT:
//STRIP001                  {
//STRIP001                      if ( eType == CELLTYPE_STRING )
//STRIP001                          ((ScStringCell*)pCell)->GetString( aValue );
//STRIP001                      else
//STRIP001                          ((ScEditCell*)pCell)->GetString( aValue );
//STRIP001                      long nVal;
//STRIP001                      nHeadNoneTail = lcl_DecompValueString( aValue, nVal );
//STRIP001                      if ( nHeadNoneTail )
//STRIP001                          nStart = (double)nVal;
//STRIP001                      else
//STRIP001                          nStart = 0.0;
//STRIP001                  }
//STRIP001                  break;
//STRIP001                  case CELLTYPE_VALUE:
//STRIP001                      nStart = ((ScValueCell*)pCell)->GetValue();
//STRIP001                  break;
//STRIP001                  case CELLTYPE_FORMULA:
//STRIP001                      nStart = ((ScFormulaCell*)pCell)->GetValue();
//STRIP001                  break;
//STRIP001                  default:
//STRIP001                      nStart = 0.0;
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001              nStart = 0.0;
//STRIP001          if ( eFillCmd == FILL_LINEAR )
//STRIP001          {
//STRIP001              double nAdd = nInc;
//STRIP001              bOk = ( SubTotal::SafeMult( nAdd, (double) nIndex ) &&
//STRIP001                      SubTotal::SafePlus( nStart, nAdd ) );
//STRIP001          }
//STRIP001          else        // Datum
//STRIP001          {
//STRIP001              bOk = TRUE;
//STRIP001              USHORT nDayOfMonth = 0;
//STRIP001              if ( nIndex < 0 )
//STRIP001              {
//STRIP001                  nIndex = -nIndex;
//STRIP001                  nInc = -nInc;
//STRIP001              }
//STRIP001              for (long i=0; i<nIndex; i++)
//STRIP001                  IncDate( nStart, nDayOfMonth, nInc, eDateCmd );
//STRIP001          }
//STRIP001
//STRIP001          if (bOk)
//STRIP001          {
//STRIP001              if ( nHeadNoneTail )
//STRIP001              {
//STRIP001                  if ( nHeadNoneTail < 0 )
//STRIP001                      aValue.Insert( lcl_ValueString( (long)nStart, nMinDigits ), 0 );
//STRIP001                  else
//STRIP001                      aValue += lcl_ValueString( (long)nStart, nMinDigits );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  //! Zahlformat je nach Index holen?
//STRIP001                  Color* pColor;
//STRIP001                  ULONG nNumFmt = GetNumberFormat( nCol1, nRow1 );
//STRIP001                  pDocument->GetFormatTable()->
//STRIP001                      GetOutputString( nStart, nNumFmt, aValue, &pColor );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001          DBG_ERROR("GetAutoFillPreview: falscher Modus");
//STRIP001  }
//STRIP001
//STRIP001  return aValue;
//STRIP001 }

//STRIP001 void ScTable::IncDate(double& rVal, USHORT& nDayOfMonth, double nStep, FillDateCmd eCmd)
//STRIP001 {
//STRIP001  if (eCmd == FILL_DAY)
//STRIP001  {
//STRIP001      rVal += nStep;
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  // class Date Grenzen
//STRIP001  const USHORT nMinYear = 1583;
//STRIP001  const USHORT nMaxYear = 9956;
//STRIP001
//STRIP001  long nInc = (long) nStep;       // nach oben/unten begrenzen ?
//STRIP001  Date aNullDate = *pDocument->GetFormatTable()->GetNullDate();
//STRIP001  Date aDate = aNullDate;
//STRIP001  aDate += (long)rVal;
//STRIP001  switch (eCmd)
//STRIP001  {
//STRIP001      case FILL_WEEKDAY:
//STRIP001          {
//STRIP001              aDate += nInc;
//STRIP001              DayOfWeek eWeekDay = aDate.GetDayOfWeek();
//STRIP001              if (nInc >= 0)
//STRIP001              {
//STRIP001                  if (eWeekDay == SATURDAY)
//STRIP001                      aDate += 2;
//STRIP001                  else if (eWeekDay == SUNDAY)
//STRIP001                      aDate += 1;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  if (eWeekDay == SATURDAY)
//STRIP001                      aDate -= 1;
//STRIP001                  else if (eWeekDay == SUNDAY)
//STRIP001                      aDate -= 2;
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001      case FILL_MONTH:
//STRIP001          {
//STRIP001              if ( nDayOfMonth == 0 )
//STRIP001                  nDayOfMonth = aDate.GetDay();       // init
//STRIP001              long nMonth = aDate.GetMonth();
//STRIP001              long nYear = aDate.GetYear();
//STRIP001
//STRIP001              nMonth += nInc;
//STRIP001
//STRIP001              if (nInc >= 0)
//STRIP001              {
//STRIP001                  if (nMonth > 12)
//STRIP001                  {
//STRIP001                      long nYAdd = (nMonth-1) / 12;
//STRIP001                      nMonth -= nYAdd * 12;
//STRIP001                      nYear += nYAdd;
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  if (nMonth < 1)
//STRIP001                  {
//STRIP001                      long nYAdd = 1 - nMonth / 12;       // positiv
//STRIP001                      nMonth += nYAdd * 12;
//STRIP001                      nYear -= nYAdd;
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              if ( nYear < nMinYear )
//STRIP001                  aDate = Date( 1,1, nMinYear );
//STRIP001              else if ( nYear > nMaxYear )
//STRIP001                  aDate = Date( 31,12, nMaxYear );
//STRIP001              else
//STRIP001              {
//STRIP001                  aDate.SetMonth((USHORT) nMonth);
//STRIP001                  aDate.SetYear((USHORT) nYear);
//STRIP001                  if ( nDayOfMonth > 28 )
//STRIP001                      aDate.SetDay( Min( aDate.GetDaysInMonth(), nDayOfMonth ) );
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001      case FILL_YEAR:
//STRIP001          {
//STRIP001              long nYear = aDate.GetYear();
//STRIP001              nYear += nInc;
//STRIP001              if ( nYear < nMinYear )
//STRIP001                  aDate = Date( 1,1, nMinYear );
//STRIP001              else if ( nYear > nMaxYear )
//STRIP001                  aDate = Date( 31,12, nMaxYear );
//STRIP001              else
//STRIP001                  aDate.SetYear((USHORT) nYear);
//STRIP001          }
//STRIP001          break;
//STRIP001  }
//STRIP001
//STRIP001  rVal = aDate - aNullDate;
//STRIP001 }

//STRIP001 void ScTable::FillSeries( USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2,
//STRIP001                  USHORT nFillCount, FillDir eFillDir, FillCmd eFillCmd, FillDateCmd eFillDateCmd,
//STRIP001                  double nStepValue, double nMaxValue, USHORT nArgMinDigits,
//STRIP001                  BOOL bAttribs, ScProgress& rProgress )
//STRIP001 {
//STRIP001  //
//STRIP001  //  Richtung auswerten
//STRIP001  //
//STRIP001
//STRIP001  BOOL bVertical = (eFillDir == FILL_TO_BOTTOM || eFillDir == FILL_TO_TOP);
//STRIP001  BOOL bPositive = (eFillDir == FILL_TO_BOTTOM || eFillDir == FILL_TO_RIGHT);
//STRIP001
//STRIP001  USHORT nCol;
//STRIP001  USHORT nRow;
//STRIP001  USHORT& rInner = bVertical ? nRow : nCol;       // Schleifenvariablen
//STRIP001  USHORT& rOuter = bVertical ? nCol : nRow;
//STRIP001  USHORT nOStart;
//STRIP001  USHORT nOEnd;
//STRIP001  USHORT nIStart;
//STRIP001  USHORT nIEnd;
//STRIP001  USHORT nISource;
//STRIP001
//STRIP001  if (bVertical)
//STRIP001  {
//STRIP001      nFillCount += (nRow2 - nRow1);
//STRIP001      if (nFillCount == 0)
//STRIP001          return;
//STRIP001      nOStart = nCol1;
//STRIP001      nOEnd = nCol2;
//STRIP001      if (bPositive)
//STRIP001      {
//STRIP001          nISource = nRow1;
//STRIP001          nIStart = nRow1 + 1;
//STRIP001          nIEnd = nRow1 + nFillCount;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          nISource = nRow2;
//STRIP001          nIStart = nRow2 - 1;
//STRIP001          nIEnd = nRow2 - nFillCount;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      nFillCount += (nCol2 - nCol1);
//STRIP001      if (nFillCount == 0)
//STRIP001          return;
//STRIP001      nOStart = nRow1;
//STRIP001      nOEnd = nRow2;
//STRIP001      if (bPositive)
//STRIP001      {
//STRIP001          nISource = nCol1;
//STRIP001          nIStart = nCol1 + 1;
//STRIP001          nIEnd = nCol1 + nFillCount;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          nISource = nCol2;
//STRIP001          nIStart = nCol2 - 1;
//STRIP001          nIEnd = nCol2 - nFillCount;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  USHORT nIMin = nIStart;
//STRIP001  USHORT nIMax = nIEnd;
//STRIP001  PutInOrder(nIMin,nIMax);
//STRIP001  USHORT nDel = bAttribs ? IDF_ALL : IDF_CONTENTS;
//STRIP001  if (bVertical)
//STRIP001      DeleteArea(nCol1, nIMin, nCol2, nIMax, nDel);
//STRIP001  else
//STRIP001      DeleteArea(nIMin, nRow1, nIMax, nRow2, nDel);
//STRIP001
//STRIP001  ULONG nProgress = rProgress.GetState();
//STRIP001
//STRIP001  //
//STRIP001  //  ausfuehren
//STRIP001  //
//STRIP001
//STRIP001  USHORT nActFormCnt = 0;
//STRIP001  for (rOuter = nOStart; rOuter <= nOEnd; rOuter++)
//STRIP001  {
//STRIP001      BOOL bFirst = TRUE;
//STRIP001      rInner = nISource;
//STRIP001      ScBaseCell* pSrcCell = aCol[nCol].GetCell(nRow);
//STRIP001
//STRIP001      if (bVertical && bAttribs)
//STRIP001          aCol[nCol].Resize( aCol[nCol].GetCellCount() + nFillCount );
//STRIP001
//STRIP001      if (bAttribs)
//STRIP001      {
//STRIP001          const ScPatternAttr* pSrcPattern = aCol[nCol].GetPattern(nRow);
//STRIP001          if (bVertical)
//STRIP001              aCol[nCol].SetPatternArea( nIMin, nIMax, *pSrcPattern, TRUE );
//STRIP001          else
//STRIP001              for (USHORT nAtCol = nIMin; nAtCol <= nIMax; nAtCol++)
//STRIP001                  aCol[nAtCol].SetPattern(nRow, *pSrcPattern, TRUE);
//STRIP001      }
//STRIP001
//STRIP001      if (pSrcCell)
//STRIP001      {
//STRIP001          CellType eCellType = pSrcCell->GetCellType();
//STRIP001
//STRIP001          if (eFillCmd == FILL_SIMPLE)                // kopieren
//STRIP001          {
//STRIP001              if (eCellType == CELLTYPE_FORMULA)
//STRIP001              {
//STRIP001                  for (rInner = nIMin; rInner <= nIMax; rInner++)
//STRIP001                  {
//STRIP001                      USHORT nInd = nActFormCnt;
//STRIP001                      FillFormula(nInd, bFirst, (ScFormulaCell*)pSrcCell,
//STRIP001                          nCol, nRow, (rInner == nIEnd) );
//STRIP001                      bFirst = FALSE;
//STRIP001                      rProgress.SetStateOnPercent( ++nProgress );
//STRIP001                  }
//STRIP001              }
//STRIP001              else if (eCellType != CELLTYPE_NOTE)
//STRIP001              {
//STRIP001                  for (rInner = nIMin; rInner <= nIMax; rInner++)
//STRIP001                  {
//STRIP001                      aCol[nCol].Insert(nRow, pSrcCell->Clone(pDocument));
//STRIP001                  }
//STRIP001                  nProgress += nIMax - nIMin + 1;
//STRIP001                  rProgress.SetStateOnPercent( nProgress );
//STRIP001              }
//STRIP001          }
//STRIP001          else if (eCellType == CELLTYPE_VALUE || eCellType == CELLTYPE_FORMULA)
//STRIP001          {
//STRIP001              double nStartVal;
//STRIP001              if (eCellType == CELLTYPE_VALUE)
//STRIP001                  nStartVal = ((ScValueCell*)pSrcCell)->GetValue();
//STRIP001              else
//STRIP001                  nStartVal = ((ScFormulaCell*)pSrcCell)->GetValue();
//STRIP001              double nVal = nStartVal;
//STRIP001              long nIndex = 0;
//STRIP001
//STRIP001              BOOL bError = FALSE;
//STRIP001              BOOL bOverflow = FALSE;
//STRIP001
//STRIP001              USHORT nDayOfMonth = 0;
//STRIP001              for (rInner = nIStart;;)
//STRIP001              {
//STRIP001                  if (!bError && !bOverflow)
//STRIP001                  {
//STRIP001                      switch (eFillCmd)
//STRIP001                      {
//STRIP001                          case FILL_LINEAR:
//STRIP001                              {
//STRIP001                                  //  #86365# use multiplication instead of repeated addition
//STRIP001                                  //  to avoid accumulating rounding errors
//STRIP001                                  nVal = nStartVal;
//STRIP001                                  double nAdd = nStepValue;
//STRIP001                                  if ( !SubTotal::SafeMult( nAdd, (double) ++nIndex ) ||
//STRIP001                                       !SubTotal::SafePlus( nVal, nAdd ) )
//STRIP001                                      bError = TRUE;
//STRIP001                              }
//STRIP001                              break;
//STRIP001                          case FILL_GROWTH:
//STRIP001                              if (!SubTotal::SafeMult(nVal, nStepValue))
//STRIP001                                  bError = TRUE;
//STRIP001                              break;
//STRIP001                          case FILL_DATE:
//STRIP001                              if (fabs(nVal) > _D_MAX_LONG_)
//STRIP001                                  bError = TRUE;
//STRIP001                              else
//STRIP001                                  IncDate(nVal, nDayOfMonth, nStepValue, eFillDateCmd);
//STRIP001                              break;
//STRIP001                      }
//STRIP001
//STRIP001                      if (nStepValue >= 0)
//STRIP001                      {
//STRIP001                          if (nVal > nMaxValue)           // Zielwert erreicht?
//STRIP001                          {
//STRIP001                              nVal = nMaxValue;
//STRIP001                              bOverflow = TRUE;
//STRIP001                          }
//STRIP001                      }
//STRIP001                      else
//STRIP001                      {
//STRIP001                          if (nVal < nMaxValue)
//STRIP001                          {
//STRIP001                              nVal = nMaxValue;
//STRIP001                              bOverflow = TRUE;
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001
//STRIP001                  if (bError)
//STRIP001                      aCol[nCol].SetError(nRow, errNoValue);
//STRIP001                  else if (!bOverflow)
//STRIP001                      aCol[nCol].SetValue(nRow, nVal);
//STRIP001
//STRIP001                  if (rInner == nIEnd) break;
//STRIP001                  if (bPositive) ++rInner; else --rInner;
//STRIP001              }
//STRIP001              nProgress += nIMax - nIMin + 1;
//STRIP001              rProgress.SetStateOnPercent( nProgress );
//STRIP001          }
//STRIP001          else if (eCellType == CELLTYPE_STRING || eCellType == CELLTYPE_EDIT)
//STRIP001          {
//STRIP001              if ( nStepValue >= 0 )
//STRIP001              {
//STRIP001                  if ( nMaxValue >= (double)LONG_MAX )
//STRIP001                      nMaxValue = (double)LONG_MAX - 1;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  if ( nMaxValue <= (double)LONG_MIN )
//STRIP001                      nMaxValue = (double)LONG_MIN + 1;
//STRIP001              }
//STRIP001              String aValue;
//STRIP001              if (eCellType == CELLTYPE_STRING)
//STRIP001                  ((ScStringCell*)pSrcCell)->GetString( aValue );
//STRIP001              else
//STRIP001                  ((ScEditCell*)pSrcCell)->GetString( aValue );
//STRIP001              long nStringValue;
//STRIP001              USHORT nMinDigits = nArgMinDigits;
//STRIP001              short nHeadNoneTail = lcl_DecompValueString( aValue, nStringValue, &nMinDigits );
//STRIP001              if ( nHeadNoneTail )
//STRIP001              {
//STRIP001                  double nStartVal = (double)nStringValue;
//STRIP001                  double nVal = nStartVal;
//STRIP001                  long nIndex = 0;
//STRIP001                  BOOL bError = FALSE;
//STRIP001                  BOOL bOverflow = FALSE;
//STRIP001
//STRIP001                  for (rInner = nIStart;;)
//STRIP001                  {
//STRIP001                      if (!bError && !bOverflow)
//STRIP001                      {
//STRIP001                          switch (eFillCmd)
//STRIP001                          {
//STRIP001                              case FILL_LINEAR:
//STRIP001                                  {
//STRIP001                                      //  #86365# use multiplication instead of repeated addition
//STRIP001                                      //  to avoid accumulating rounding errors
//STRIP001                                      nVal = nStartVal;
//STRIP001                                      double nAdd = nStepValue;
//STRIP001                                      if ( !SubTotal::SafeMult( nAdd, (double) ++nIndex ) ||
//STRIP001                                           !SubTotal::SafePlus( nVal, nAdd ) )
//STRIP001                                          bError = TRUE;
//STRIP001                                  }
//STRIP001                                  break;
//STRIP001                              case FILL_GROWTH:
//STRIP001                                  if (!SubTotal::SafeMult(nVal, nStepValue))
//STRIP001                                      bError = TRUE;
//STRIP001                                  break;
//STRIP001                          }
//STRIP001
//STRIP001                          if (nStepValue >= 0)
//STRIP001                          {
//STRIP001                              if (nVal > nMaxValue)           // Zielwert erreicht?
//STRIP001                              {
//STRIP001                                  nVal = nMaxValue;
//STRIP001                                  bOverflow = TRUE;
//STRIP001                              }
//STRIP001                          }
//STRIP001                          else
//STRIP001                          {
//STRIP001                              if (nVal < nMaxValue)
//STRIP001                              {
//STRIP001                                  nVal = nMaxValue;
//STRIP001                                  bOverflow = TRUE;
//STRIP001                              }
//STRIP001                          }
//STRIP001                      }
//STRIP001
//STRIP001                      if (bError)
//STRIP001                          aCol[nCol].SetError(nRow, errNoValue);
//STRIP001                      else if (!bOverflow)
//STRIP001                      {
//STRIP001                          nStringValue = (long)nVal;
//STRIP001                          String aStr;
//STRIP001                          if ( nHeadNoneTail < 0 )
//STRIP001                          {
//STRIP001                              aStr = lcl_ValueString( nStringValue, nMinDigits );
//STRIP001                              aStr += aValue;
//STRIP001                          }
//STRIP001                          else
//STRIP001                          {
//STRIP001                              aStr = aValue;
//STRIP001                              aStr += lcl_ValueString( nStringValue, nMinDigits );
//STRIP001                          }
//STRIP001                          ScStringCell* pCell = new ScStringCell( aStr );
//STRIP001                          aCol[nCol].Insert(nRow, pCell);
//STRIP001                      }
//STRIP001
//STRIP001                      if (rInner == nIEnd) break;
//STRIP001                      if (bPositive) ++rInner; else --rInner;
//STRIP001                  }
//STRIP001              }
//STRIP001              nProgress += nIMax - nIMin + 1;
//STRIP001              rProgress.SetStateOnPercent( nProgress );
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          nProgress += nIMax - nIMin + 1;
//STRIP001          rProgress.SetStateOnPercent( nProgress );
//STRIP001      }
//STRIP001      ++nActFormCnt;
//STRIP001  }
//STRIP001 }

//STRIP001 void ScTable::Fill( USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2,
//STRIP001                  USHORT nFillCount, FillDir eFillDir, FillCmd eFillCmd, FillDateCmd eFillDateCmd,
//STRIP001                  double nStepValue, double nMaxValue)
//STRIP001 {
//STRIP001  ULONG nProgCount;
//STRIP001  if (eFillDir == FILL_TO_BOTTOM || eFillDir == FILL_TO_TOP)
//STRIP001      nProgCount = nCol2 - nCol1 + 1;
//STRIP001  else
//STRIP001      nProgCount = nRow2 - nRow1 + 1;
//STRIP001  nProgCount *= nFillCount;
//STRIP001  ScProgress aProgress( pDocument->GetDocumentShell(),
//STRIP001                          ScGlobal::GetRscString(STR_FILL_SERIES_PROGRESS), nProgCount );
//STRIP001
//STRIP001  bSharedNameInserted = FALSE;
//STRIP001
//STRIP001  if (eFillCmd == FILL_AUTO)
//STRIP001      FillAuto(nCol1, nRow1, nCol2, nRow2, nFillCount, eFillDir, aProgress);
//STRIP001  else
//STRIP001      FillSeries(nCol1, nRow1, nCol2, nRow2, nFillCount, eFillDir,
//STRIP001                  eFillCmd, eFillDateCmd, nStepValue, nMaxValue, 0, TRUE, aProgress);
//STRIP001
//STRIP001  if (bSharedNameInserted)                        // Wurde Shared-Name eingefuegt?
//STRIP001      pDocument->GetRangeName()->SetSharedMaxIndex(
//STRIP001          pDocument->GetRangeName()->GetSharedMaxIndex()+1);  // dann hochzaehlen
//STRIP001 }


//STRIP001 void ScTable::AutoFormatArea(USHORT nStartCol, USHORT nStartRow, USHORT nEndCol, USHORT nEndRow,
//STRIP001                              const ScPatternAttr& rAttr, USHORT nFormatNo)
//STRIP001 {
//STRIP001  ScAutoFormat* pAutoFormat = ScGlobal::GetAutoFormat();
//STRIP001  if (pAutoFormat)
//STRIP001  {
//STRIP001      ScAutoFormatData* pData = (*pAutoFormat)[nFormatNo];
//STRIP001      if (pData)
//STRIP001      {
//STRIP001 //           ScPatternAttr aPattern(pDocument->GetPool());
//STRIP001 //            pData->FillToItemSet(nIndex, aPattern.GetItemSet(), *pDocument);
//STRIP001          ApplyPatternArea(nStartCol, nStartRow, nEndCol, nEndRow, rAttr);
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void ScTable::AutoFormat( USHORT nStartCol, USHORT nStartRow, USHORT nEndCol, USHORT nEndRow,
//STRIP001                          USHORT nFormatNo )
//STRIP001 {
//STRIP001  if (ValidColRow(nStartCol, nStartRow) && ValidColRow(nEndCol, nEndRow))
//STRIP001  {
//STRIP001      ScAutoFormat* pAutoFormat = ScGlobal::GetAutoFormat();
//STRIP001      if (pAutoFormat)
//STRIP001      {
//STRIP001             ScAutoFormatData* pData = (*pAutoFormat)[nFormatNo];
//STRIP001          if (pData)
//STRIP001          {
//STRIP001                 ScPatternAttr* pPatternAttrs[16];
//STRIP001                 for (sal_uInt8 i = 0; i < 16; ++i)
//STRIP001                 {
//STRIP001                     pPatternAttrs[i] = new ScPatternAttr(pDocument->GetPool());
//STRIP001                     pData->FillToItemSet(i, pPatternAttrs[i]->GetItemSet(), *pDocument);
//STRIP001                 }
//STRIP001
//STRIP001              USHORT nCol = nStartCol;
//STRIP001              USHORT nRow = nStartRow;
//STRIP001              USHORT nIndex = 0;
//STRIP001              // Linke obere Ecke
//STRIP001              AutoFormatArea(nCol, nRow, nCol, nRow, *pPatternAttrs[nIndex], nFormatNo);
//STRIP001              // Linke Spalte
//STRIP001              if (pData->IsEqualData(4, 8))
//STRIP001                  AutoFormatArea(nStartCol, nStartRow + 1, nStartCol, nEndRow - 1, *pPatternAttrs[4], nFormatNo);
//STRIP001              else
//STRIP001              {
//STRIP001                  nIndex = 4;
//STRIP001                  for (nRow = nStartRow + 1; nRow < nEndRow; nRow++)
//STRIP001                  {
//STRIP001                      AutoFormatArea(nCol, nRow, nCol, nRow, *pPatternAttrs[nIndex], nFormatNo);
//STRIP001                      if (nIndex == 4)
//STRIP001                          nIndex = 8;
//STRIP001                      else
//STRIP001                          nIndex = 4;
//STRIP001                  }
//STRIP001              }
//STRIP001              // Linke untere Ecke
//STRIP001              nRow = nEndRow;
//STRIP001              nIndex = 12;
//STRIP001              AutoFormatArea(nCol, nRow, nCol, nRow, *pPatternAttrs[nIndex], nFormatNo);
//STRIP001              // Rechte obere Ecke
//STRIP001              nCol = nEndCol;
//STRIP001              nRow = nStartRow;
//STRIP001              nIndex = 3;
//STRIP001              AutoFormatArea(nCol, nRow, nCol, nRow, *pPatternAttrs[nIndex], nFormatNo);
//STRIP001              // Rechte Spalte
//STRIP001              if (pData->IsEqualData(7, 11))
//STRIP001                  AutoFormatArea(nEndCol, nStartRow + 1, nEndCol, nEndRow - 1, *pPatternAttrs[7], nFormatNo);
//STRIP001              else
//STRIP001              {
//STRIP001                  nIndex = 7;
//STRIP001                  for (nRow = nStartRow + 1; nRow < nEndRow; nRow++)
//STRIP001                  {
//STRIP001                      AutoFormatArea(nCol, nRow, nCol, nRow, *pPatternAttrs[nIndex], nFormatNo);
//STRIP001                      if (nIndex == 7)
//STRIP001                          nIndex = 11;
//STRIP001                      else
//STRIP001                          nIndex = 7;
//STRIP001                  }
//STRIP001              }
//STRIP001              // Rechte untere Ecke
//STRIP001              nRow = nEndRow;
//STRIP001              nIndex = 15;
//STRIP001              AutoFormatArea(nCol, nRow, nCol, nRow, *pPatternAttrs[nIndex], nFormatNo);
//STRIP001              nRow = nStartRow;
//STRIP001              nIndex = 1;
//STRIP001              for (nCol = nStartCol + 1; nCol < nEndCol; nCol++)
//STRIP001              {
//STRIP001                  AutoFormatArea(nCol, nRow, nCol, nRow, *pPatternAttrs[nIndex], nFormatNo);
//STRIP001                  if (nIndex == 1)
//STRIP001                      nIndex = 2;
//STRIP001                  else
//STRIP001                      nIndex = 1;
//STRIP001              }
//STRIP001              // Untere Zeile
//STRIP001              nRow = nEndRow;
//STRIP001              nIndex = 13;
//STRIP001              for (nCol = nStartCol + 1; nCol < nEndCol; nCol++)
//STRIP001              {
//STRIP001                  AutoFormatArea(nCol, nRow, nCol, nRow, *pPatternAttrs[nIndex], nFormatNo);
//STRIP001                  if (nIndex == 13)
//STRIP001                      nIndex = 14;
//STRIP001                  else
//STRIP001                      nIndex = 13;
//STRIP001              }
//STRIP001              // Boddy
//STRIP001              if ((pData->IsEqualData(5, 6)) && (pData->IsEqualData(9, 10)) && (pData->IsEqualData(5, 9)))
//STRIP001                  AutoFormatArea(nStartCol + 1, nStartRow + 1, nEndCol-1, nEndRow - 1, *pPatternAttrs[5], nFormatNo);
//STRIP001              else
//STRIP001              {
//STRIP001                  if ((pData->IsEqualData(5, 9)) && (pData->IsEqualData(6, 10)))
//STRIP001                  {
//STRIP001                      nIndex = 5;
//STRIP001                      for (nCol = nStartCol + 1; nCol < nEndCol; nCol++)
//STRIP001                      {
//STRIP001                          AutoFormatArea(nCol, nStartRow + 1, nCol, nEndRow - 1, *pPatternAttrs[nIndex], nFormatNo);
//STRIP001                          if (nIndex == 5)
//STRIP001                              nIndex = 6;
//STRIP001                          else
//STRIP001                              nIndex = 5;
//STRIP001                      }
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      nIndex = 5;
//STRIP001                      for (nCol = nStartCol + 1; nCol < nEndCol; nCol++)
//STRIP001                      {
//STRIP001                          for (nRow = nStartRow + 1; nRow < nEndRow; nRow++)
//STRIP001                          {
//STRIP001                              AutoFormatArea(nCol, nRow, nCol, nRow, *pPatternAttrs[nIndex], nFormatNo);
//STRIP001                              if ((nIndex == 5) || (nIndex == 9))
//STRIP001                              {
//STRIP001                                  if (nIndex == 5)
//STRIP001                                      nIndex = 9;
//STRIP001                                  else
//STRIP001                                      nIndex = 5;
//STRIP001                              }
//STRIP001                              else
//STRIP001                              {
//STRIP001                                  if (nIndex == 6)
//STRIP001                                      nIndex = 10;
//STRIP001                                  else
//STRIP001                                      nIndex = 6;
//STRIP001                              }
//STRIP001                          } // for nRow
//STRIP001                          if ((nIndex == 5) || (nIndex == 9))
//STRIP001                              nIndex = 6;
//STRIP001                          else
//STRIP001                              nIndex = 5;
//STRIP001                      } // for nCol
//STRIP001                  } // if not equal Column
//STRIP001              } // if not all equal
//STRIP001
//STRIP001                 for (sal_uInt8 j = 0; j < 16; ++j)
//STRIP001                     delete pPatternAttrs[j];
//STRIP001          } // if AutoFormatData != NULL
//STRIP001      } // if AutoFormat != NULL
//STRIP001  } // if ValidColRow
//STRIP001 }

//STRIP001 void ScTable::GetAutoFormatAttr(USHORT nCol, USHORT nRow, USHORT nIndex, ScAutoFormatData& rData)
//STRIP001 {
//STRIP001  UINT32 nFormatIndex = GetNumberFormat( nCol, nRow );
//STRIP001  ScNumFormatAbbrev   aNumFormat( nFormatIndex, *pDocument->GetFormatTable() );
//STRIP001     rData.GetFromItemSet( nIndex, GetPattern( nCol, nRow )->GetItemSet(), aNumFormat );
//STRIP001 }

#define LF_LEFT         1
#define LF_TOP          2
#define LF_RIGHT        4
#define LF_BOTTOM       8
#define LF_ALL          (LF_LEFT | LF_TOP | LF_RIGHT | LF_BOTTOM)

//STRIP001 void ScTable::GetAutoFormatFrame(USHORT nCol, USHORT nRow, USHORT nFlags, USHORT nIndex, ScAutoFormatData& rData)
//STRIP001 {
//STRIP001  const SvxBoxItem* pTheBox = (SvxBoxItem*)GetAttr(nCol, nRow, ATTR_BORDER);
//STRIP001  const SvxBoxItem* pLeftBox = (SvxBoxItem*)GetAttr(nCol - 1, nRow, ATTR_BORDER);
//STRIP001  const SvxBoxItem* pTopBox = (SvxBoxItem*)GetAttr(nCol, nRow - 1, ATTR_BORDER);
//STRIP001  const SvxBoxItem* pRightBox = (SvxBoxItem*)GetAttr(nCol + 1, nRow, ATTR_BORDER);
//STRIP001  const SvxBoxItem* pBottomBox = (SvxBoxItem*)GetAttr(nCol, nRow + 1, ATTR_BORDER);
//STRIP001
//STRIP001  SvxBoxItem aBox;
//STRIP001  if (nFlags & LF_LEFT)
//STRIP001  {
//STRIP001      if (pLeftBox)
//STRIP001      {
//STRIP001          if (HasPriority(pTheBox->GetLeft(), pLeftBox->GetRight()))
//STRIP001              aBox.SetLine(pTheBox->GetLeft(), BOX_LINE_LEFT);
//STRIP001          else
//STRIP001              aBox.SetLine(pLeftBox->GetRight(), BOX_LINE_LEFT);
//STRIP001      }
//STRIP001      else
//STRIP001          aBox.SetLine(pTheBox->GetLeft(), BOX_LINE_LEFT);
//STRIP001  }
//STRIP001  if (nFlags & LF_TOP)
//STRIP001  {
//STRIP001      if (pTopBox)
//STRIP001      {
//STRIP001          if (HasPriority(pTheBox->GetTop(), pTopBox->GetBottom()))
//STRIP001              aBox.SetLine(pTheBox->GetTop(), BOX_LINE_TOP);
//STRIP001          else
//STRIP001              aBox.SetLine(pTopBox->GetBottom(), BOX_LINE_TOP);
//STRIP001      }
//STRIP001      else
//STRIP001          aBox.SetLine(pTheBox->GetTop(), BOX_LINE_TOP);
//STRIP001  }
//STRIP001  if (nFlags & LF_RIGHT)
//STRIP001  {
//STRIP001      if (pRightBox)
//STRIP001      {
//STRIP001          if (HasPriority(pTheBox->GetRight(), pRightBox->GetLeft()))
//STRIP001              aBox.SetLine(pTheBox->GetRight(), BOX_LINE_RIGHT);
//STRIP001          else
//STRIP001              aBox.SetLine(pRightBox->GetLeft(), BOX_LINE_RIGHT);
//STRIP001      }
//STRIP001      else
//STRIP001          aBox.SetLine(pTheBox->GetRight(), BOX_LINE_RIGHT);
//STRIP001  }
//STRIP001  if (nFlags & LF_BOTTOM)
//STRIP001  {
//STRIP001      if (pBottomBox)
//STRIP001      {
//STRIP001          if (HasPriority(pTheBox->GetBottom(), pBottomBox->GetTop()))
//STRIP001              aBox.SetLine(pTheBox->GetBottom(), BOX_LINE_BOTTOM);
//STRIP001          else
//STRIP001              aBox.SetLine(pBottomBox->GetTop(), BOX_LINE_BOTTOM);
//STRIP001      }
//STRIP001      else
//STRIP001          aBox.SetLine(pTheBox->GetBottom(), BOX_LINE_BOTTOM);
//STRIP001  }
//STRIP001     rData.PutItem( nIndex, aBox );
//STRIP001 }

//STRIP001 void ScTable::GetAutoFormatData(USHORT nStartCol, USHORT nStartRow, USHORT nEndCol, USHORT nEndRow, ScAutoFormatData& rData)
//STRIP001 {
//STRIP001  if (ValidColRow(nStartCol, nStartRow) && ValidColRow(nEndCol, nEndRow))
//STRIP001  {
//STRIP001      if ((nEndCol - nStartCol >= 3) && (nEndRow - nStartRow >= 3))
//STRIP001      {
//STRIP001          // Linke obere Ecke
//STRIP001          GetAutoFormatAttr(nStartCol, nStartRow, 0, rData);
//STRIP001          GetAutoFormatFrame(nStartCol, nStartRow, LF_ALL, 0, rData);
//STRIP001          // Linke Spalte
//STRIP001          GetAutoFormatAttr(nStartCol, nStartRow + 1, 4, rData);
//STRIP001          GetAutoFormatAttr(nStartCol, nStartRow + 2, 8, rData);
//STRIP001          GetAutoFormatFrame(nStartCol, nStartRow + 1, LF_LEFT | LF_RIGHT | LF_BOTTOM, 4, rData);
//STRIP001          if (nEndRow - nStartRow >= 4)
//STRIP001              GetAutoFormatFrame(nStartCol, nStartRow + 2, LF_LEFT | LF_RIGHT | LF_BOTTOM, 8, rData);
//STRIP001          else
//STRIP001                 rData.CopyItem( 8, 4, ATTR_BORDER );
//STRIP001          // Linke untere Ecke
//STRIP001          GetAutoFormatAttr(nStartCol, nEndRow, 12, rData);
//STRIP001          GetAutoFormatFrame(nStartCol, nEndRow, LF_ALL, 12, rData);
//STRIP001          // Rechte obere Ecke
//STRIP001          GetAutoFormatAttr(nEndCol, nStartRow, 3, rData);
//STRIP001          GetAutoFormatFrame(nEndCol, nStartRow, LF_ALL, 3, rData);
//STRIP001          // Rechte Spalte
//STRIP001          GetAutoFormatAttr(nEndCol, nStartRow + 1, 7, rData);
//STRIP001          GetAutoFormatAttr(nEndCol, nStartRow + 2, 11, rData);
//STRIP001          GetAutoFormatFrame(nEndCol, nStartRow + 1, LF_LEFT | LF_RIGHT | LF_BOTTOM, 7, rData);
//STRIP001          if (nEndRow - nStartRow >= 4)
//STRIP001              GetAutoFormatFrame(nEndCol, nStartRow + 2, LF_LEFT | LF_RIGHT | LF_BOTTOM, 11, rData);
//STRIP001          else
//STRIP001                 rData.CopyItem( 11, 7, ATTR_BORDER );
//STRIP001          // Rechte untere Ecke
//STRIP001          GetAutoFormatAttr(nEndCol, nEndRow, 15, rData);
//STRIP001          GetAutoFormatFrame(nEndCol, nEndRow, LF_ALL, 15, rData);
//STRIP001          // Ober Zeile
//STRIP001          GetAutoFormatAttr(nStartCol + 1, nStartRow, 1, rData);
//STRIP001          GetAutoFormatAttr(nStartCol + 2, nStartRow, 2, rData);
//STRIP001          GetAutoFormatFrame(nStartCol + 1, nStartRow, LF_TOP | LF_BOTTOM | LF_RIGHT, 1, rData);
//STRIP001          if (nEndCol - nStartCol >= 4)
//STRIP001              GetAutoFormatFrame(nStartCol + 2, nStartRow, LF_TOP | LF_BOTTOM | LF_RIGHT, 2, rData);
//STRIP001          else
//STRIP001                 rData.CopyItem( 2, 1, ATTR_BORDER );
//STRIP001          // Untere Zeile
//STRIP001          GetAutoFormatAttr(nStartCol + 1, nEndRow, 13, rData);
//STRIP001          GetAutoFormatAttr(nStartCol + 2, nEndRow, 14, rData);
//STRIP001          GetAutoFormatFrame(nStartCol + 1, nEndRow, LF_TOP | LF_BOTTOM | LF_RIGHT, 13, rData);
//STRIP001          if (nEndCol - nStartCol >= 4)
//STRIP001              GetAutoFormatFrame(nStartCol + 2, nEndRow, LF_TOP | LF_BOTTOM | LF_RIGHT, 14, rData);
//STRIP001          else
//STRIP001                 rData.CopyItem( 14, 13, ATTR_BORDER );
//STRIP001          // Body
//STRIP001          GetAutoFormatAttr(nStartCol + 1, nStartRow + 1, 5, rData);
//STRIP001          GetAutoFormatAttr(nStartCol + 2, nStartRow + 1, 6, rData);
//STRIP001          GetAutoFormatAttr(nStartCol + 1, nStartRow + 2, 9, rData);
//STRIP001          GetAutoFormatAttr(nStartCol + 2, nStartRow + 2, 10, rData);
//STRIP001          GetAutoFormatFrame(nStartCol + 1, nStartRow + 1, LF_RIGHT | LF_BOTTOM, 5, rData);
//STRIP001          if ((nEndCol - nStartCol >= 4) && (nEndRow - nStartRow >= 4))
//STRIP001          {
//STRIP001              GetAutoFormatFrame(nStartCol + 2, nStartRow + 1, LF_RIGHT | LF_BOTTOM, 6, rData);
//STRIP001              GetAutoFormatFrame(nStartCol + 1, nStartRow + 2, LF_RIGHT | LF_BOTTOM, 9, rData);
//STRIP001              GetAutoFormatFrame(nStartCol + 2, nStartRow + 2, LF_RIGHT | LF_BOTTOM, 10, rData);
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001                 rData.CopyItem( 6, 5, ATTR_BORDER );
//STRIP001                 rData.CopyItem( 9, 5, ATTR_BORDER );
//STRIP001                 rData.CopyItem( 10, 5, ATTR_BORDER );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*N*/ void ScTable::SetError( USHORT nCol, USHORT nRow, USHORT nError)
/*N*/ {
/*N*/   if (ValidColRow(nCol, nRow))
/*N*/       aCol[nCol].SetError( nRow, nError );
/*N*/ }

//STRIP001 void ScTable::UpdateInsertTabAbs(USHORT nTable)
//STRIP001 {
//STRIP001  for (USHORT i=0; i <= MAXCOL; i++)
//STRIP001      aCol[i].UpdateInsertTabAbs(nTable);
//STRIP001 }

//STRIP001 USHORT ScTable::GetErrorData( USHORT nCol, USHORT nRow ) const
//STRIP001 {
//STRIP001  if (ValidColRow(nCol,nRow))
//STRIP001      return aCol[nCol].GetErrorData( nRow );
//STRIP001  else
//STRIP001      return 0;
//STRIP001 }

//STRIP001 BOOL ScTable::GetNextSpellingCell(USHORT& rCol, USHORT& rRow, BOOL bInSel,
//STRIP001                                  const ScMarkData& rMark) const
//STRIP001 {
//STRIP001  if (rRow == MAXROW+2)                       // Tabellenende
//STRIP001  {
//STRIP001      rRow = 0;
//STRIP001      rCol = 0;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      rRow++;
//STRIP001      if (rRow == MAXROW+1)
//STRIP001      {
//STRIP001          rCol++;
//STRIP001          rRow = 0;
//STRIP001      }
//STRIP001  }
//STRIP001  if (rCol == MAXCOL+1)
//STRIP001      return TRUE;
//STRIP001  else
//STRIP001  {
//STRIP001      BOOL bStop = FALSE;
//STRIP001      while (!bStop)
//STRIP001      {
//STRIP001          if (rCol <= MAXCOL)
//STRIP001          {
//STRIP001              bStop = aCol[rCol].GetNextSpellingCell(rRow, bInSel, rMark);
//STRIP001              if (bStop)
//STRIP001                  return TRUE;
//STRIP001              else /*if (rRow == MAXROW+1) */
//STRIP001              {
//STRIP001                  rCol++;
//STRIP001                  rRow = 0;
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001              return TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 void ScTable::RemoveAutoSpellObj()
//STRIP001 {
//STRIP001  for (USHORT i=0; i <= MAXCOL; i++)
//STRIP001      aCol[i].RemoveAutoSpellObj();
//STRIP001 }

/*N*/ BOOL ScTable::TestTabRefAbs(USHORT nTable)
/*N*/ {
/*N*/   BOOL bRet = FALSE;
/*N*/   for (USHORT i=0; i <= MAXCOL; i++)
/*N*/       if (aCol[i].TestTabRefAbs(nTable))
/*N*/           bRet = TRUE;
/*N*/   return bRet;
/*N*/ }

//STRIP001 void ScTable::CompileDBFormula()
//STRIP001 {
//STRIP001  for (USHORT i=0; i<=MAXCOL; i++) aCol[i].CompileDBFormula();
//STRIP001 }

/*N*/ void ScTable::CompileDBFormula( BOOL bCreateFormulaString )
/*N*/ {
/*N*/   for (USHORT i=0; i<=MAXCOL; i++) aCol[i].CompileDBFormula( bCreateFormulaString );
/*N*/ }

/*N*/ void ScTable::CompileNameFormula( BOOL bCreateFormulaString )
/*N*/ {
/*N*/   for (USHORT i=0; i<=MAXCOL; i++) aCol[i].CompileNameFormula( bCreateFormulaString );
/*N*/ }

/*N*/ void ScTable::CompileColRowNameFormula()
/*N*/ {
/*N*/   for (USHORT i=0; i<=MAXCOL; i++) aCol[i].CompileColRowNameFormula();
/*N*/ }






}
