/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_pivot.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 16:51:16 $
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

// -----------------------------------------------------------------------

#pragma optimize("",off)
#pragma optimize("q",off) // p-code off


// INCLUDE ---------------------------------------------------------------

// auto strip #include <svtools/zforlist.hxx>
#include <tools/solar.h>
#include <string.h>
#include <math.h>


#include "globstr.hrc"
// auto strip #include "global.hxx"
#include "subtotal.hxx"
// auto strip #include "scitems.hxx"
// auto strip #include "attrib.hxx"
// auto strip #include "patattr.hxx"
#include "docpool.hxx"
#include "document.hxx"
#include "userlist.hxx"
#include "pivot.hxx"
#include "cell.hxx"
#include "rechead.hxx"
// auto strip #include "compiler.hxx"                           // fuer errNoValue
// auto strip #include "progress.hxx"
namespace binfilter {


// STATIC DATA -----------------------------------------------------------

//! bei Gelegenheit...

static short    nStaticStrRefCount = 0;
static String*  pLabel[PIVOT_MAXFUNC+1];            // incl. "auto"
static String*  pLabelTotal;
static String*  pLabelData;

static USHORT nDataMult = 1;

#define nFirstLine  2

static const USHORT nFuncMaskArr[PIVOT_MAXFUNC+1] =
    {   PIVOT_FUNC_SUM,
        PIVOT_FUNC_COUNT,
        PIVOT_FUNC_AVERAGE,
        PIVOT_FUNC_MAX,
        PIVOT_FUNC_MIN,
        PIVOT_FUNC_PRODUCT,
        PIVOT_FUNC_COUNT_NUM,
        PIVOT_FUNC_STD_DEV,
        PIVOT_FUNC_STD_DEVP,
        PIVOT_FUNC_STD_VAR,
        PIVOT_FUNC_STD_VARP,
        PIVOT_FUNC_AUTO };              // automatisch

// -----------------------------------------------------------------------

//  1   Filter-Knopf
//  2   Feldnamen links
//  3   "Daten" links
//  4   Feldnamen oben
//  5   "Daten" oben
//  6   einzelne "Gesamt" oben rechts
//  7   "Gesamt" oben rechts
//  8   einzelne "Gesamt" unten links
//  9   "Gesamt" unten links
//  10  innere Kategorie links
//  11  Teilergebnis Label einzeln links
//  12  Teilergebnis Label gesamt links
//  13  letzte Kategorie links
//  14  innere Kategorie oben
//  15  Teilergebnis Label einzeln oben
//  16  Teilergebnis Label gesamt oben
//  17  letzte Kategorie oben
//  18  Werte innen
//  19  Werte in Teilergebnisspalte
//  20  Werte in Gesamt-Spalte
//  21  Werte in einzelnen Gesamt-Spalten
//  22  Werte in Ergebnis-Zeile Teilergebnis oder Gesamt
//  23  Kreuzung von Spalte/Zeile (Teilergebnis-Spalte)
//  24  Kreuzung von Spalte/Zeile (Gesamt-Spalte)
//  25  wie 24 bei einzelnen "Gesamt"

//STRIP001 short lcl_MaskToIndex( USHORT nFuncMask )
//STRIP001 {
//STRIP001  short i;
//STRIP001  for (i=0; i<=PIVOT_MAXFUNC; i++)
//STRIP001      if (nFuncMask == nFuncMaskArr[i])
//STRIP001          return i;
//STRIP001
//STRIP001  DBG_ERROR("Falsche Maske in MaskToIndex");
//STRIP001  return 0;
//STRIP001 }

//STRIP001 BOOL lcl_IsEmptyLine( ScDocument* pDoc, const ScAddress& rPos, USHORT nCol2 )
//STRIP001 {
//STRIP001          //! ans Document verschieben !!!
//STRIP001
//STRIP001  ScAddress aAdr( rPos );
//STRIP001  for (USHORT nCol=aAdr.Col(); nCol<=nCol2; nCol++)
//STRIP001  {
//STRIP001      aAdr.SetCol( nCol );
//STRIP001      if ( pDoc->GetCell( aAdr ) )
//STRIP001          return FALSE;
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

/*N*/ ScPivot::ScPivot(ScDocument* pDocument) :
/*N*/   pDoc            (pDocument),
/*N*/   aQuery          (),
/*N*/   bHasHeader      (FALSE),
/*N*/   bIgnoreEmpty    (FALSE),
/*N*/   bDetectCat      (FALSE),
/*N*/   bMakeTotalCol   (TRUE),
/*N*/   bMakeTotalRow   (TRUE),
/*N*/   nColNameCount   (0),
/*N*/   pColNames       (NULL),
/*N*/   nSrcCol1        (0),
/*N*/   nSrcRow1        (0),
/*N*/   nSrcCol2        (0),
/*N*/   nSrcRow2        (0),
/*N*/   nSrcTab         (0),
/*N*/   nDestCol1       (0),
/*N*/   nDestRow1       (0),
/*N*/   nDestCol2       (0),
/*N*/   nDestRow2       (0),
/*N*/   nDestTab        (0),
/*N*/   nDataStartCol   (0),
/*N*/   nDataStartRow   (0),
/*N*/   nColCount       (0),
/*N*/   nRowCount       (0),
/*N*/   nDataCount      (0),
/*N*/   bValidArea      (FALSE),
/*N*/   bDataAtCol      (FALSE)
/*N*/ {
/*N*/   short i;
/*N*/   for (i=0; i<PIVOT_MAXFIELD; i++)
/*N*/   {
/*N*/       pColList[i] = new PivotStrCollection();
/*N*/       pRowList[i] = new PivotStrCollection();
/*N*/   }
/*N*/   pDataList = pColList[0];
/*N*/   ppDataArr = NULL;
/*N*/   nDataColCount = 0;
/*N*/   nDataRowCount = 0;
/*N*/   nRecCount = 0;
/*N*/   pColRef = NULL;
/*N*/
/*N*/   // Initialisierung der statischen Strings, wenn noetig
/*N*/   nStaticStrRefCount += 1;
/*N*/   if ( nStaticStrRefCount < 2 )
/*N*/   {
/*N*/       pLabelTotal = new String( ScGlobal::GetRscString(STR_PIVOT_TOTAL) );
/*N*/       pLabelData  = new String( ScGlobal::GetRscString(STR_PIVOT_DATA) );
/*N*/
/*N*/       for ( i=0; i<=PIVOT_MAXFUNC; i++ )          //  incl. "auto"
/*N*/           pLabel[i] = new String;                 //  kein Leerzeichen
/*N*/
/*N*/       *pLabel[ 0] = ScGlobal::GetRscString(STR_FUN_TEXT_SUM);
/*N*/       *pLabel[ 1] = ScGlobal::GetRscString(STR_FUN_TEXT_COUNT);
/*N*/       *pLabel[ 2] = ScGlobal::GetRscString(STR_FUN_TEXT_AVG);
/*N*/       *pLabel[ 3] = ScGlobal::GetRscString(STR_FUN_TEXT_MAX);
/*N*/       *pLabel[ 4] = ScGlobal::GetRscString(STR_FUN_TEXT_MIN);
/*N*/       *pLabel[ 5] = ScGlobal::GetRscString(STR_FUN_TEXT_PRODUCT);
/*N*/       *pLabel[ 6] = ScGlobal::GetRscString(STR_FUN_TEXT_COUNT);           // Count2
/*N*/       *pLabel[ 7] = ScGlobal::GetRscString(STR_FUN_TEXT_STDDEV);
/*N*/       *pLabel[ 8] = ScGlobal::GetRscString(STR_FUN_TEXT_STDDEV);          // Stddev2
/*N*/       *pLabel[ 9] = ScGlobal::GetRscString(STR_FUN_TEXT_VAR);
/*N*/       *pLabel[10] = ScGlobal::GetRscString(STR_FUN_TEXT_VAR);             // Var2
/*N*/       *pLabel[11] = ScGlobal::GetRscString(STR_TABLE_ERGEBNIS);
/*N*/   }
/*N*/ }
/*N*/
/*N*/ ScPivot::ScPivot(const ScPivot& rPivot):
/*N*/   pDoc            (rPivot.pDoc),
/*N*/   aQuery          (rPivot.aQuery),
/*N*/   bHasHeader      (rPivot.bHasHeader),
/*N*/   bIgnoreEmpty    (rPivot.bIgnoreEmpty),
/*N*/   bDetectCat      (rPivot.bDetectCat),
/*N*/   bMakeTotalCol   (rPivot.bMakeTotalCol),
/*N*/   bMakeTotalRow   (rPivot.bMakeTotalRow),
/*N*/   nColNameCount   (0),
/*N*/   pColNames       (NULL),
/*N*/   aName           (rPivot.aName),
/*N*/   aTag            (rPivot.aTag),
/*N*/   nSrcCol1        (rPivot.nSrcCol1),
/*N*/   nSrcRow1        (rPivot.nSrcRow1),
/*N*/   nSrcCol2        (rPivot.nSrcCol2),
/*N*/   nSrcRow2        (rPivot.nSrcRow2),
/*N*/   nSrcTab         (rPivot.nSrcTab),
/*N*/   nDestCol1       (rPivot.nDestCol1),
/*N*/   nDestRow1       (rPivot.nDestRow1),
/*N*/   nDestCol2       (rPivot.nDestCol2),
/*N*/   nDestRow2       (rPivot.nDestRow2),
/*N*/   nDestTab        (rPivot.nDestTab),
/*N*/   nDataStartCol   (0),
/*N*/   nDataStartRow   (0),
/*N*/   nColCount       (0),
/*N*/   nRowCount       (0),
/*N*/   nDataCount      (0),
/*N*/   bValidArea      (FALSE),
/*N*/   bDataAtCol      (FALSE)
/*N*/ {
/*N*/   if (rPivot.nColNameCount && rPivot.pColNames)
/*N*/   {
/*N*/       nColNameCount = rPivot.nColNameCount;
/*N*/       pColNames = new String[nColNameCount];
/*N*/       for (USHORT nCol=0; nCol<nColNameCount; nCol++)
/*N*/           pColNames[nCol] = rPivot.pColNames[nCol];
/*N*/   }
/*N*/
/*N*/   short i;
/*N*/   for (i=0; i<PIVOT_MAXFIELD; i++)
/*N*/   {
/*N*/       pColList[i] = new PivotStrCollection();
/*N*/       pRowList[i] = new PivotStrCollection();
/*N*/   }
/*N*/   pDataList = pColList[0];
/*N*/   ppDataArr = NULL;
/*N*/   nRecCount = 0;
/*N*/   pColRef = NULL;
/*N*/
/*N*/   SetColFields( rPivot.aColArr, rPivot.nColCount );
/*N*/   SetRowFields( rPivot.aRowArr, rPivot.nRowCount );
/*N*/   SetDataFields( rPivot.aDataArr, rPivot.nDataCount );
/*N*/
/*N*/   nStaticStrRefCount += 1;
/*N*/ }

/*N*/ ScPivot::~ScPivot()
/*N*/ {
/*N*/   short i;
/*N*/   for (i=0; i<PIVOT_MAXFIELD; i++)
/*N*/   {
/*N*/       delete pColList[i];
/*N*/       delete pRowList[i];
/*N*/   }
/*N*/   if (ppDataArr)
/*N*/   {
/*N*/       for (i=0; i<nDataRowCount; i++)
/*N*/           delete[] ppDataArr[i];
/*N*/       delete[] ppDataArr;
/*N*/       ppDataArr = NULL;
/*N*/   }
/*N*/   delete[] pColRef;
/*N*/
/*N*/   delete[] pColNames;
/*N*/
/*N*/   // statische Strings ggF. wieder abraeumen
/*N*/   nStaticStrRefCount -= 1;
/*N*/   if ( nStaticStrRefCount == 0 )
/*N*/   {
/*N*/       delete pLabelTotal;
/*N*/       delete pLabelData;
/*N*/
/*N*/       for ( i=0; i<=PIVOT_MAXFUNC; i++ )          // incl. "auto"
/*N*/           delete pLabel[i];
/*N*/   }
/*N*/ }

//STRIP001 ScPivot* ScPivot::CreateNew() const
//STRIP001 {
//STRIP001  ScPivot* pNewPivot = new ScPivot( pDoc );
//STRIP001
//STRIP001  pNewPivot->SetQuery(aQuery);
//STRIP001  pNewPivot->SetHeader(bHasHeader);
//STRIP001  pNewPivot->SetIgnoreEmpty(bIgnoreEmpty);
//STRIP001  pNewPivot->SetDetectCat(bDetectCat);
//STRIP001  pNewPivot->SetMakeTotalCol(bMakeTotalCol);
//STRIP001  pNewPivot->SetMakeTotalRow(bMakeTotalRow);
//STRIP001
//STRIP001  pNewPivot->SetSrcArea( nSrcCol1, nSrcRow1, nSrcCol2, nSrcRow2, nSrcTab );
//STRIP001  pNewPivot->SetDestPos( nDestCol1, nDestRow1, nDestTab );
//STRIP001
//STRIP001  return pNewPivot;
//STRIP001 }

/*N*/ void lcl_LoadFieldArr30( SvStream& rStream, PivotField* pField, USHORT nCount )
/*N*/ {
/*N*/   USHORT i;
/*N*/
/*N*/   for (i=0; i<nCount; i++)
/*N*/   {
/*N*/       rStream >> pField[i].nCol
/*N*/               >> pField[i].nFuncMask
/*N*/               >> pField[i].nFuncCount;
/*N*/   }
/*N*/ }

/*N*/ void lcl_LoadFieldArr( SvStream& rStream, PivotField* pField, USHORT nCount )
/*N*/ {
/*N*/   USHORT i;
/*N*/
/*N*/   for (i=0; i<nCount; i++)
/*N*/   {
/*N*/       BYTE cData;
/*N*/       rStream >> cData;
/*N*/       if( cData & 0x0F )
/*N*/           rStream.SeekRel( cData & 0x0F );
/*N*/       rStream >> pField[i].nCol
/*N*/               >> pField[i].nFuncMask
/*N*/               >> pField[i].nFuncCount;
/*N*/   }
/*N*/ }

/*N*/ void lcl_SaveFieldArr( SvStream& rStream, const PivotField* pField, USHORT nCount )
/*N*/ {
/*N*/   USHORT i;
/*N*/
/*N*/   for (i=0; i<nCount; i++)
/*N*/   {
/*N*/       rStream << (BYTE) 0x00
/*N*/               << pField[i].nCol
/*N*/               << pField[i].nFuncMask
/*N*/               << pField[i].nFuncCount;
/*N*/   }
/*N*/ }

//  nach Load muessen Daten neu berechnet werden !

/*N*/ BOOL ScPivot::Load( SvStream& rStream, ScMultipleReadHeader& rHdr )
/*N*/ {
/*N*/   rHdr.StartEntry();
/*N*/
/*N*/   rStream >> bHasHeader
/*N*/
/*N*/           >> nSrcCol1
/*N*/           >> nSrcRow1
/*N*/           >> nSrcCol2
/*N*/           >> nSrcRow2
/*N*/           >> nSrcTab
/*N*/
/*N*/           >> nDestCol1
/*N*/           >> nDestRow1
/*N*/           >> nDestCol2
/*N*/           >> nDestRow2
/*N*/           >> nDestTab;
/*N*/
/*N*/                       //  Arrays immer ueber Set...Fields initalisieren!
/*N*/
/*N*/   short nCount;
/*N*/   PivotFieldArr aFieldArr;
/*N*/
/*N*/   if( pDoc->GetSrcVersion() >= SC_DATABYTES2 )
/*N*/   {
/*N*/       rStream >> nCount;
/*N*/       lcl_LoadFieldArr( rStream, aFieldArr, nCount );
/*N*/       SetColFields(aFieldArr, nCount);
/*N*/
/*N*/       rStream >> nCount;
/*N*/       lcl_LoadFieldArr( rStream, aFieldArr, nCount );
/*N*/       SetRowFields(aFieldArr, nCount);
/*N*/
/*N*/       rStream >> nCount;
/*N*/       lcl_LoadFieldArr( rStream, aFieldArr, nCount );
/*N*/       SetDataFields(aFieldArr, nCount);
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       rStream >> nCount;
/*N*/       lcl_LoadFieldArr30( rStream, aFieldArr, nCount );
/*N*/       SetColFields(aFieldArr, nCount);
/*N*/
/*N*/       rStream >> nCount;
/*N*/       lcl_LoadFieldArr30( rStream, aFieldArr, nCount );
/*N*/       SetRowFields(aFieldArr, nCount);
/*N*/
/*N*/       rStream >> nCount;
/*N*/       lcl_LoadFieldArr30( rStream, aFieldArr, nCount );
/*N*/       SetDataFields(aFieldArr, nCount);
/*N*/   }
/*N*/
/*N*/   aQuery.Load( rStream );
/*N*/
/*N*/   rStream >> bIgnoreEmpty;
/*N*/   rStream >> bDetectCat;
/*N*/
/*N*/   if (rHdr.BytesLeft())
/*N*/   {
/*N*/       rStream >> bMakeTotalCol;       // ab 355i
/*N*/       rStream >> bMakeTotalRow;
/*N*/   }
/*N*/
/*N*/   if (rHdr.BytesLeft())               // ab 500a
/*N*/   {
/*N*/       rStream.ReadByteString( aName, rStream.GetStreamCharSet() );
/*N*/       rStream.ReadByteString( aTag,  rStream.GetStreamCharSet() );
/*N*/
/*N*/       DBG_ASSERT(!pColNames, "Spaltennamen schon gesetzt?")
/*N*/       rStream >> nColNameCount;
/*N*/       if (nColNameCount)
/*N*/       {
/*N*/           pColNames = new String[nColNameCount];
/*N*/           for (USHORT nCol=0; nCol<nColNameCount; nCol++)
/*N*/               rStream.ReadByteString( pColNames[nCol], rStream.GetStreamCharSet() );
/*N*/       }
/*N*/   }
/*N*/   // sonst wird hinterher aus ScPivotCollection::Load ein Name vergeben
/*N*/
/*N*/   rHdr.EndEntry();
/*N*/   return TRUE;
/*N*/ }

/*N*/ BOOL ScPivot::Store( SvStream& rStream, ScMultipleWriteHeader& rHdr ) const
/*N*/ {
/*N*/   rHdr.StartEntry();
/*N*/
/*N*/   rStream << bHasHeader
/*N*/
/*N*/           << nSrcCol1
/*N*/           << nSrcRow1
/*N*/           << nSrcCol2
/*N*/           << nSrcRow2
/*N*/           << nSrcTab
/*N*/
/*N*/           << nDestCol1
/*N*/           << nDestRow1
/*N*/           << nDestCol2
/*N*/           << nDestRow2
/*N*/           << nDestTab
/*N*/
/*N*/           << nColCount;
/*N*/   lcl_SaveFieldArr( rStream, aColArr, nColCount );
/*N*/   rStream << nRowCount;
/*N*/   lcl_SaveFieldArr( rStream, aRowArr, nRowCount );
/*N*/   rStream << nDataCount;
/*N*/   lcl_SaveFieldArr( rStream, aDataArr, nDataCount );
/*N*/
/*N*/   aQuery.Store( rStream );
/*N*/
/*N*/   rStream << bIgnoreEmpty;
/*N*/   rStream << bDetectCat;
/*N*/
/*N*/   rStream << bMakeTotalCol;       // ab 355i
/*N*/   rStream << bMakeTotalRow;
/*N*/
/*N*/   if( rStream.GetVersion() > SOFFICE_FILEFORMAT_40 )  // Name/Tag/Spalten ab 5.0
/*N*/   {
/*N*/       rStream.WriteByteString( aName, rStream.GetStreamCharSet() );
/*N*/       rStream.WriteByteString( aTag,  rStream.GetStreamCharSet() );
/*N*/
/*N*/       if (!pColNames) ((ScPivot*)this)->nColNameCount = 0;        // soll nicht sein
/*N*/       rStream << nColNameCount;
/*N*/       for (USHORT nCol=0; nCol<nColNameCount; nCol++)
/*N*/           rStream.WriteByteString( pColNames[nCol], rStream.GetStreamCharSet() );
/*N*/   }
/*N*/
/*N*/   rHdr.EndEntry();
/*N*/   return TRUE;
/*N*/ }

/*N*/ void ScPivot::SetQuery(const ScQueryParam& rQuery)
/*N*/ {
/*N*/   aQuery = rQuery;
/*N*/
/*N*/   bValidArea = FALSE;
/*N*/ }

/*N*/ void ScPivot::GetQuery(ScQueryParam& rQuery) const
/*N*/ {
/*N*/   rQuery = aQuery;
/*N*/ }

/*N*/ void ScPivot::SetHeader(BOOL bHeader)
/*N*/ {
/*N*/   bHasHeader = bHeader;
/*N*/   bValidArea = FALSE;
/*N*/ }

//STRIP001 BOOL ScPivot::GetHeader() const
//STRIP001 {
//STRIP001  return bHasHeader;
//STRIP001 }

/*N*/ void ScPivot::SetIgnoreEmpty(BOOL bIgnore)
/*N*/ {
/*N*/   bIgnoreEmpty = bIgnore;
/*N*/   bValidArea   = FALSE;
/*N*/ }

/*N*/ BOOL ScPivot::GetIgnoreEmpty() const
/*N*/ {
/*N*/   return bIgnoreEmpty;
/*N*/ }

/*N*/ void ScPivot::SetDetectCat(BOOL bDetect)
/*N*/ {
/*N*/   bDetectCat = bDetect;
/*N*/   bValidArea = FALSE;
/*N*/ }

/*N*/ BOOL ScPivot::GetDetectCat() const
/*N*/ {
/*N*/   return bDetectCat;
/*N*/ }

/*N*/ void ScPivot::SetMakeTotalCol(BOOL bSet)
/*N*/ {
/*N*/   bMakeTotalCol = bSet;
/*N*/   bValidArea    = FALSE;
/*N*/ }

/*N*/ BOOL ScPivot::GetMakeTotalCol() const
/*N*/ {
/*N*/   return bMakeTotalCol;
/*N*/ }

/*N*/ void ScPivot::SetMakeTotalRow(BOOL bSet)
/*N*/ {
/*N*/   bMakeTotalRow = bSet;
/*N*/   bValidArea    = FALSE;
/*N*/ }

/*N*/ BOOL ScPivot::GetMakeTotalRow() const
/*N*/ {
/*N*/   return bMakeTotalRow;
/*N*/ }

/*N*/ void ScPivot::SetName(const String& rNew)
/*N*/ {
/*N*/   aName = rNew;
/*N*/ }

/*N*/ const String& ScPivot::GetName() const
/*N*/ {
/*N*/   return aName;
/*N*/ }

/*N*/ void ScPivot::SetTag(const String& rNew)
/*N*/ {
/*N*/   aTag = rNew;
/*N*/ }

/*N*/ const String& ScPivot::GetTag() const
/*N*/ {
/*N*/   return aTag;
/*N*/ }

/*N*/ void ScPivot::SetSrcArea(USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2, USHORT nTab)
/*N*/ {
/*N*/   nSrcCol1 = Min(nCol1, (USHORT)MAXCOL);
/*N*/   nSrcRow1 = Min(nRow1, (USHORT)MAXROW);
/*N*/   nSrcCol2 = Min(nCol2, (USHORT)MAXCOL);
/*N*/   nSrcRow2 = Min(nRow2, (USHORT)MAXROW);
/*N*/   nSrcTab = nTab;
/*N*/   bValidArea = FALSE;
/*N*/ }

/*N*/ void ScPivot::GetSrcArea(USHORT& rCol1, USHORT& rRow1, USHORT& rCol2, USHORT& rRow2, USHORT& rTab) const
/*N*/ {
/*N*/   rCol1 = nSrcCol1;
/*N*/   rRow1 = nSrcRow1;
/*N*/   rCol2 = nSrcCol2;
/*N*/   rRow2 = nSrcRow2;
/*N*/   rTab = nSrcTab;
/*N*/ }

/*N*/ ScRange ScPivot::GetSrcArea() const
/*N*/ {
/*N*/   return ScRange( nSrcCol1,nSrcRow1,nSrcTab, nSrcCol2,nSrcRow2,nSrcTab );
/*N*/ }

/*N*/ void ScPivot::SetDestPos(USHORT nCol, USHORT nRow, USHORT nTab)
/*N*/ {
/*N*/   nDestCol1 = nCol;
/*N*/   nDestRow1 = nRow;
/*N*/   nDestTab = nTab;
/*N*/   bValidArea = FALSE;
/*N*/ }

/*N*/ void ScPivot::GetDestArea(USHORT& rCol1, USHORT& rRow1, USHORT& rCol2, USHORT& rRow2, USHORT& rTab) const
/*N*/ {
/*N*/   rCol1 = nDestCol1;
/*N*/   rRow1 = nDestRow1;
/*N*/   rTab = nDestTab;
/*N*/   if (bValidArea)
/*N*/   {
/*N*/       rCol2 = nDestCol2;
/*N*/       rRow2 = nDestRow2;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       rCol2 = nDestCol1;
/*N*/       rRow2 = nDestRow1;
/*N*/   }
/*N*/ }

/*N*/ ScRange ScPivot::GetDestArea() const
/*N*/ {
/*N*/   ScAddress aStart( nDestCol1, nDestRow1, nDestTab );
/*N*/   ScAddress aEnd = aStart;
/*N*/   if ( bValidArea )
/*N*/       aEnd = ScAddress( nDestCol2, nDestRow2, nDestTab );
/*N*/   return ScRange( aStart, aEnd );
/*N*/ }

/*N*/ void ScPivot::MoveSrcArea( USHORT nNewCol, USHORT nNewRow, USHORT nNewTab )
/*N*/ {
/*N*/   if ( nNewCol != nSrcCol1 || nNewRow != nSrcRow1 || nNewTab != nSrcTab )
/*N*/   {
/*N*/       USHORT i;
/*N*/       short nDiffX = nNewCol - (short) nSrcCol1;
/*N*/       short nDiffY = nNewRow - (short) nSrcRow1;
/*N*/
/*N*/       nSrcTab = nNewTab;
/*N*/       nSrcCol1 += nDiffX;
/*N*/       nSrcCol2 += nDiffX;
/*N*/       nSrcRow1 += nDiffY;
/*N*/       nSrcRow2 += nDiffY;
/*N*/
/*N*/       aQuery.nCol1 += nDiffX;
/*N*/       aQuery.nCol2 += nDiffX;
/*N*/       aQuery.nRow1 += nDiffY;
/*N*/       aQuery.nRow2 += nDiffY;
/*N*/
/*N*/       USHORT nEC = aQuery.GetEntryCount();
/*N*/       for (i=0; i<nEC; i++)
/*N*/           if (aQuery.GetEntry(i).bDoQuery)
/*N*/               aQuery.GetEntry(i).nField += nDiffX;
/*N*/
/*N*/       if (bValidArea)
/*N*/       {
/*N*/           short nC;
/*N*/           for (nC=0; nC<nColCount; nC++)
/*N*/               if (aColArr[nC].nCol != PIVOT_DATA_FIELD)
/*N*/                   aColArr[nC].nCol += nDiffX;
/*N*/           for (nC=0; nC<nRowCount; nC++)
/*N*/               if (aRowArr[nC].nCol != PIVOT_DATA_FIELD)
/*N*/                   aRowArr[nC].nCol += nDiffX;
/*N*/           for (nC=0; nC<nDataCount; nC++)
/*N*/               if (aDataArr[nC].nCol != PIVOT_DATA_FIELD)
/*N*/                   aDataArr[nC].nCol += nDiffX;
/*N*/       }
/*N*/   }
/*N*/ }

//STRIP001 void ScPivot::ExtendSrcArea( USHORT nNewEndCol, USHORT nNewEndRow )
//STRIP001 {
//STRIP001  DBG_ASSERT( nNewEndCol >= nSrcCol2 && nNewEndRow >= nSrcRow2, "ExtendSrcArea: zu klein" );
//STRIP001
//STRIP001  nSrcCol2 = nNewEndCol;
//STRIP001  nSrcRow2 = nNewEndRow;
//STRIP001
//STRIP001  //  alles andere bleibt erhalten
//STRIP001 }

/*N*/ void ScPivot::MoveDestArea( USHORT nNewCol, USHORT nNewRow, USHORT nNewTab )
/*N*/ {
/*N*/   if ( nNewCol != nDestCol1 || nNewRow != nDestRow1 || nNewTab != nDestTab )
/*N*/   {
/*N*/       short nDiffX = nNewCol - (short) nDestCol1;
/*N*/       short nDiffY = nNewRow - (short) nDestRow1;
/*N*/
/*N*/       nDestTab = nNewTab;
/*N*/       nDestCol1 += nDiffX;
/*N*/       nDestRow1 += nDiffY;
/*N*/
/*N*/       if (bValidArea)
/*N*/       {
/*N*/           nDestCol2 += nDiffX;
/*N*/           nDestRow2 += nDiffY;
/*N*/
/*N*/           nDataStartCol += nDiffX;
/*N*/           nDataStartRow += nDiffY;
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void ScPivot::SetColFields(const PivotField* pFieldArr, short nCount)
/*N*/ {
/*N*/   nColCount = Max((short)0, Min(nCount, (short)PIVOT_MAXFIELD));
/*N*/   for (short i = 0; i < nColCount; i++)
/*N*/   {
/*N*/       aColArr[i] = pFieldArr[i];
/*N*/       aColArr[i].nFuncCount = 0;
/*N*/       if (aColArr[i].nCol == PIVOT_DATA_FIELD)
/*N*/       {
/*N*/           aColArr[i].nFuncMask = PIVOT_FUNC_NONE;
/*N*/           pDataList = pColList[i];
/*N*/           bDataAtCol = TRUE;
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           for (short j=0; j<=PIVOT_MAXFUNC; j++)              // incl. "auto"
/*N*/               if (aColArr[i].nFuncMask & nFuncMaskArr[j])
/*N*/                   aColArr[i].nFuncCount++;
/*N*/       }
/*N*/   }
/*N*/   bValidArea = FALSE;
/*N*/ }

/*N*/ void ScPivot::GetColFields(PivotField* pFieldArr, short& rCount) const
/*N*/ {
/*N*/   for (short i=0; i<nColCount; i++)
/*N*/       pFieldArr[i] = aColArr[i];
/*N*/   rCount = nColCount;
/*N*/ }

/*N*/ void ScPivot::SetRowFields(const PivotField* pFieldArr, short nCount)
/*N*/ {
/*N*/   nRowCount = Max((short)0, Min(nCount, (short)PIVOT_MAXFIELD));
/*N*/   for (short i = 0; i < nRowCount; i++)
/*N*/   {
/*N*/       aRowArr[i] = pFieldArr[i];
/*N*/       aRowArr[i].nFuncCount = 0;
/*N*/       if (aRowArr[i].nCol == PIVOT_DATA_FIELD)
/*N*/       {
/*N*/           aRowArr[i].nFuncMask = PIVOT_FUNC_NONE;
/*N*/           pDataList = pRowList[i];
/*N*/           bDataAtCol = FALSE;
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           for (short j=0; j<=PIVOT_MAXFUNC; j++)              // incl. "auto"
/*N*/               if (aRowArr[i].nFuncMask & nFuncMaskArr[j])
/*N*/                   aRowArr[i].nFuncCount++;
/*N*/       }
/*N*/   }
/*N*/   bValidArea = FALSE;
/*N*/ }

/*N*/ void ScPivot::GetRowFields(PivotField* pFieldArr, short& rCount) const
/*N*/ {
/*N*/   for (short i=0; i<nRowCount; i++)
/*N*/       pFieldArr[i] = aRowArr[i];
/*N*/   rCount = nRowCount;
/*N*/ }

/*N*/ void ScPivot::SetDataFields(const PivotField* pFieldArr, short nCount)
/*N*/ {
/*N*/   USHORT nFuncNo;
/*N*/   short i;
/*N*/
/*N*/   //
/*N*/   //      nDataCount vorausberechnen (wie unten)
/*N*/   //
/*N*/
/*N*/   nDataCount = 0;
/*N*/   for (i = 0; i < nCount; i++)
/*N*/       for (nFuncNo=0; nFuncNo<PIVOT_MAXFUNC; nFuncNo++)
/*N*/           if (pFieldArr[i].nFuncMask & nFuncMaskArr[nFuncNo])
/*N*/               if (nDataCount+1 < PIVOT_MAXFIELD)
/*N*/                   ++nDataCount;
/*N*/
/*N*/   //
/*N*/   //      Eintraege anpassen
/*N*/   //
/*N*/
/*N*/   if ((nRowCount == 1) && (aRowArr[0].nCol == PIVOT_DATA_FIELD) && (nDataCount == 1))
/*N*/   {
/*?*/       aColArr[nColCount] = aRowArr[0];
/*?*/       pDataList = pColList[nColCount];
/*?*/       nColCount++;
/*?*/       nRowCount--;
/*?*/       bDataAtCol = TRUE;
/*N*/   }
/*N*/   if ((nColCount == 1) && (aColArr[0].nCol == PIVOT_DATA_FIELD) && (nDataCount == 1))
/*N*/   {
/*?*/       aRowArr[nRowCount] = aColArr[0];
/*?*/       pDataList = pRowList[nRowCount];
/*?*/       nRowCount++;
/*?*/       nColCount--;
/*?*/       bDataAtCol = FALSE;
/*N*/   }
/*N*/
/*N*/   if ((nDataCount == 1)
/*N*/       && (aColArr[nColCount-1].nCol != PIVOT_DATA_FIELD)
/*N*/       && (aColArr[nRowCount-1].nCol != PIVOT_DATA_FIELD))
/*N*/   {
/*?*/       if (bDataAtCol)
/*?*/       {
/*?*/           PivotField aField;
/*?*/           short nIndex = PIVOT_MAXFIELD;
/*?*/           for (i=0; i<nColCount; i++)
/*?*/           {
/*?*/               if (aColArr[i].nCol == PIVOT_DATA_FIELD)
/*?*/               {
/*?*/                   aField = aColArr[i];
/*?*/                   nIndex = i;
/*?*/               }
/*?*/           }
/*?*/           DBG_ASSERT(nIndex < PIVOT_MAXFIELD, "no data field (GPF in old versions!)");
/*?*/           if ( nIndex < PIVOT_MAXFIELD )
/*?*/           {
/*?*/               memcpy(&aColArr[nIndex], &aColArr[nIndex+1], (PIVOT_MAXFIELD - nIndex - 1) * sizeof(PivotField));
/*?*/               aColArr[nColCount-1] = aField;
/*?*/               pDataList = pColList[nColCount-1];
/*?*/           }
/*?*/       }
/*?*/       else
/*?*/       {
/*?*/           PivotField aField;
/*?*/           short nIndex = PIVOT_MAXFIELD;
/*?*/           for (i=0; i<nRowCount; i++)
/*?*/           {
/*?*/               if (aRowArr[i].nCol == PIVOT_DATA_FIELD)
/*?*/               {
/*?*/                   aField = aRowArr[i];
/*?*/                   nIndex = i;
/*?*/               }
/*?*/           }
/*?*/           DBG_ASSERT(nIndex < PIVOT_MAXFIELD, "no data field (GPF in old versions!)");
/*?*/           if ( nIndex < PIVOT_MAXFIELD )
/*?*/           {
/*?*/               memcpy(&aRowArr[nIndex], &aRowArr[nIndex+1], (PIVOT_MAXFIELD - nIndex - 1) * sizeof(PivotField));
/*?*/               aRowArr[nRowCount-1] = aField;
/*?*/               pDataList = pRowList[nRowCount-1];
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/
/*N*/   //
/*N*/   //      Datenfelder in Eintraege mit nur einer Funktion aufteilen
/*N*/   //
/*N*/
/*N*/   pDataList->FreeAll();
/*N*/   nDataCount = 0;
/*N*/   for (i = 0; i < nCount; i++)
/*N*/   {
/*N*/       for (nFuncNo=0; nFuncNo<PIVOT_MAXFUNC; nFuncNo++)
/*N*/           if (pFieldArr[i].nFuncMask & nFuncMaskArr[nFuncNo])
/*N*/               if (nDataCount+1 < PIVOT_MAXFIELD)
/*N*/               {
/*N*/                   aDataArr[nDataCount] = pFieldArr[i];
/*N*/                   aDataArr[nDataCount].nFuncCount = 0;
/*N*/                   aDataArr[nDataCount].nFuncMask  = nFuncMaskArr[nFuncNo];
/*N*/
/*N*/                   String aStr;
/*N*/                   pDoc->GetString(aDataArr[nDataCount].nCol, nSrcRow1, nSrcTab, aStr);
/*N*/                   if (aStr.Len() == 0)
/*?*/                       aStr = ColToAlpha( aDataArr[nDataCount].nCol );
/*N*/                   TypedStrData* pStrData = new TypedStrData(aStr);
/*N*/                   if (!(pDataList->AtInsert(pDataList->GetCount(), pStrData)))
/*N*/                   {
/*?*/                       delete pStrData;
/*?*/                       DBG_ERROR("Fehler bei pDataList->AtInsert");
/*N*/                   }
/*N*/
/*N*/                   ++nDataCount;
/*N*/               }
/*N*/   }
/*N*/
/*N*/   //
/*N*/   //
/*N*/   //
/*N*/
/*N*/   bValidArea = FALSE;
/*N*/ }

/*N*/ void ScPivot::GetDataFields(PivotField* pFieldArr, short& rCount) const
/*N*/ {
/*  for (short i=0; i<nDataCount; i++)
        pFieldArr[i] = aDataArr[i];
    rCount = nDataCount;
*/
/*N*/
/*N*/   rCount = 0;
/*N*/   for (short i=0; i<nDataCount; i++)
/*N*/   {
/*N*/       BOOL bFound = FALSE;
/*N*/       for (short j=0; j<rCount && !bFound; j++)
/*?*/           if (pFieldArr[j].nCol == aDataArr[i].nCol)
/*?*/           {
/*?*/               //  add to previous column only if new bits aren't already set there
/*?*/               if ( ( pFieldArr[j].nFuncMask & aDataArr[i].nFuncMask ) == 0 )
/*?*/               {
/*?*/                   pFieldArr[j].nFuncMask |= aDataArr[i].nFuncMask;
/*?*/                   pFieldArr[j].nFuncCount++;
/*?*/                   bFound = TRUE;
/*?*/               }
/*?*/           }
/*N*/       if (!bFound)
/*N*/       {
/*N*/           pFieldArr[rCount] = aDataArr[i];
/*N*/           ++rCount;
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ BOOL ScPivot::CreateData(BOOL bKeepDest)
/*N*/ {
/*N*/   //
/*N*/   //
/*N*/   //
/*N*/
/*N*/   USHORT nOldCol2 = nDestCol2;
/*N*/   USHORT nOldRow2 = nDestRow2;
/*N*/
/*N*/   pColRef = new PivotColRef[MAXCOL];
/*N*/   aQuery.nCol1 = nSrcCol1;
/*N*/   aQuery.nRow1 = nSrcRow1;
/*N*/   aQuery.nCol2 = nSrcCol2;
/*N*/   aQuery.nRow2 = nSrcRow2;
/*N*/   aQuery.bHasHeader = bHasHeader;
/*N*/   BOOL bRet = CreateFields();
/*N*/   if (bRet)
/*N*/   {
/*N*/       short i=0;                  // nDataMult berechnen - nach CreateFields, vor CreateFieldData !!!
/*N*/       nDataMult = 1;
/*N*/       if (nDataCount > 1)
/*N*/       {
/*?*/           if (bDataAtCol)
/*?*/           {
/*?*/               while (i<nColCount && aColArr[i].nCol != PIVOT_DATA_FIELD) i++;
/*?*/               i++;
/*?*/               while (i<nColCount)
/*?*/                   nDataMult *= pColList[i++]->GetCount();
/*?*/           }
/*?*/           else
/*?*/           {
/*?*/               while (i<nRowCount && aRowArr[i].nCol != PIVOT_DATA_FIELD) i++;
/*?*/               i++;
/*?*/               while (i<nRowCount)
/*?*/                   nDataMult *= pRowList[i++]->GetCount();
/*?*/           }
/*N*/       }
/*N*/       DBG_ASSERT(nDataMult,"nDataMult==0");
/*N*/
/*N*/       CalcArea();
/*N*/       if ((nDestCol2 <= MAXCOL) && (nDestRow2 <= MAXROW))
/*N*/       {
/*N*/           CreateFieldData();
/*N*/           bValidArea = TRUE;
/*N*/       }
/*N*/       else
/*N*/           bRet = FALSE;
/*N*/   }
/*N*/
/*N*/   if ( bKeepDest )
/*N*/   {
/*N*/       bValidArea = TRUE;          //! ???
/*N*/       nDestCol2 = nOldCol2;
/*N*/       nDestRow2 = nOldRow2;
/*N*/   }
/*N*/
/*N*/   return bRet;
/*N*/ }

//STRIP001 void ScPivot::DrawData()
//STRIP001 {
//STRIP001  ScProgress aProgress( pDoc->GetDocumentShell(), ScGlobal::GetRscString(STR_PIVOT_PROGRESS), nDestRow2-nDestRow1 );
//STRIP001
//STRIP001  short i;
//STRIP001
//STRIP001  USHORT nCol;
//STRIP001  USHORT nRow;
//STRIP001  String aStr;
//STRIP001  pDoc->pTab[nDestTab]->DeleteArea(nDestCol1, nDestRow1, nDestCol2, nDestRow2, IDF_ALL);
//STRIP001
//STRIP001  if ( nDataStartRow > nDestRow1+nFirstLine )
//STRIP001      SetStyle(nDestCol1, nDestRow1+nFirstLine, nDestCol2, nDataStartRow-1, PIVOT_STYLE_TOP);
//STRIP001  SetStyle(nDataStartCol, nDataStartRow, nDestCol2, nDestRow2, PIVOT_STYLE_INNER);
//STRIP001
//STRIP001  pDoc->SetString(nDestCol1, nDestRow1, nDestTab, ScGlobal::GetRscString(STR_CELL_FILTER));
//STRIP001  //  Kategorie 1
//STRIP001  SetButton(nDestCol1, nDestRow1, nDestCol1, nDestRow1);
//STRIP001
//STRIP001  if (bHasHeader)                     // Spalten / Zeilennamen ausgeben
//STRIP001  {
//STRIP001      if (nColCount != 0)
//STRIP001      {
//STRIP001          nCol = nDestCol1;
//STRIP001          nRow = nDataStartRow - 1;
//STRIP001          for (i=0; i<nColCount; i++)
//STRIP001          {
//STRIP001              if (aColArr[i].nCol != PIVOT_DATA_FIELD)
//STRIP001              {
//STRIP001                  pDoc->GetString(aColArr[i].nCol, nSrcRow1, nSrcTab, aStr);
//STRIP001                  if ( !aStr.Len() )
//STRIP001                      aStr = ColToAlpha( aColArr[i].nCol );
//STRIP001                  pDoc->SetString(nCol, nRow, nDestTab, aStr);
//STRIP001                  //  Kategorie 2
//STRIP001                  nCol++;
//STRIP001              }
//STRIP001              else if (nDataCount > 1)
//STRIP001              {
//STRIP001                  pDoc->SetString(nCol, nRow, nDestTab, *pLabelData);
//STRIP001                  //  Kategorie 3
//STRIP001                  nCol++;
//STRIP001              }
//STRIP001          }
//STRIP001          SetButton(nDestCol1, nRow, nCol-1, nRow);
//STRIP001          SetStyle(nDestCol1, nRow, nCol-1, nRow, PIVOT_STYLE_FIELDNAME);
//STRIP001      }
//STRIP001      if (nRowCount != 0)
//STRIP001      {
//STRIP001          nCol = nDataStartCol;
//STRIP001          nRow = nDestRow1 + nFirstLine;
//STRIP001          for (i=0; i<nRowCount; i++)
//STRIP001          {
//STRIP001              if (aRowArr[i].nCol != PIVOT_DATA_FIELD)
//STRIP001              {
//STRIP001                  pDoc->GetString(aRowArr[i].nCol, nSrcRow1, nSrcTab, aStr);
//STRIP001                  if ( !aStr.Len() )
//STRIP001                      aStr = ColToAlpha( aRowArr[i].nCol );
//STRIP001                  pDoc->SetString(nCol, nRow, nDestTab, aStr);
//STRIP001                  //  Kategorie 4
//STRIP001                  nCol++;
//STRIP001              }
//STRIP001              else if (nDataCount > 1)
//STRIP001              {
//STRIP001                  pDoc->SetString(nCol, nRow, nDestTab, *pLabelData);
//STRIP001                  //  Kategorie 5
//STRIP001                  nCol++;
//STRIP001              }
//STRIP001          }
//STRIP001          SetButton(nDataStartCol, nRow, nCol-1, nRow);
//STRIP001          SetStyle(nDataStartCol, nRow, nCol-1, nRow, PIVOT_STYLE_FIELDNAME);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  BOOL bNoRows = (nRowCount == 0) || ( nRowCount == 1 && aRowArr[0].nCol == PIVOT_DATA_FIELD );
//STRIP001  BOOL bNoCols = (nColCount == 0) || ( nColCount == 1 && aColArr[0].nCol == PIVOT_DATA_FIELD );
//STRIP001  if (!bMakeTotalCol) bNoRows = TRUE;
//STRIP001  if (!bMakeTotalRow) bNoCols = TRUE;
//STRIP001
//STRIP001  USHORT nTotalCol = nDestCol2;
//STRIP001  USHORT nTotalRow = nDestRow2;
//STRIP001  if (bDataAtCol)
//STRIP001      nTotalRow -= nDataCount - 1;
//STRIP001  else
//STRIP001      nTotalCol -= nDataCount - 1;
//STRIP001
//STRIP001                          // Spaltenkoepfe ausgeben und ColRef initialisieren
//STRIP001                          // (String-Collections sind initialisiert)
//STRIP001  nDataIndex = 0;
//STRIP001  nColIndex = 0;
//STRIP001  nCol = nDataStartCol;
//STRIP001  nRecCount = 0;
//STRIP001  RowToTable(0, nCol);
//STRIP001
//STRIP001                          // Zeilenkoepfe und Daten ausgeben
//STRIP001                          // (ruft SetDataLine/SetFuncLine auf)
//STRIP001  nRowIndex = 0;
//STRIP001  nRow = nDataStartRow;
//STRIP001  ColToTable(0, nRow, aProgress);
//STRIP001
//STRIP001                          // Gesamtergebnis-Zeilen
//STRIP001
//STRIP001  if (!bNoCols)
//STRIP001  {
//STRIP001      if (bDataAtCol)
//STRIP001          for (short nTotCnt = 0; nTotCnt<nDataCount; nTotCnt++)
//STRIP001              SetFuncLine(nDataStartCol, nRow+nTotCnt, nDestTab,
//STRIP001                          aDataArr[nTotCnt].nFuncMask, nTotCnt, 0, nDataRowCount);
//STRIP001      else
//STRIP001          SetFuncLine(nDataStartCol, nRow, nDestTab, PIVOT_FUNC_AUTO, 0xffff, 0, nDataRowCount);
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001  // Rahmen Spaltenergebnis
//STRIP001
//STRIP001  if (!bNoRows)
//STRIP001  {
//STRIP001      if (!bDataAtCol)
//STRIP001      {
//STRIP001          for (short i=0; i<nDataCount; i++)
//STRIP001          {
//STRIP001              String aLab = *pLabelTotal;
//STRIP001              aLab += ' ';
//STRIP001              aLab += *pLabel[lcl_MaskToIndex( aDataArr[i].nFuncMask )];
//STRIP001              aLab += ' ';
//STRIP001              aLab += pDataList->GetString(i);
//STRIP001              pDoc->SetString(nTotalCol+i, nDestRow1 + nFirstLine, nDestTab, aLab);
//STRIP001              //  Kategorie 6
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pDoc->SetString(nTotalCol, nDestRow1 + nFirstLine, nDestTab, *pLabelTotal);
//STRIP001          //  Kategorie 7
//STRIP001      }
//STRIP001
//STRIP001      if ( nDataStartRow )
//STRIP001          SetStyle(nTotalCol, nDestRow1+nFirstLine, nDestCol2, nDataStartRow-1, PIVOT_STYLE_TITLE);
//STRIP001      SetStyle(nTotalCol, nDataStartRow, nDestCol2, nDestRow2, PIVOT_STYLE_RESULT);
//STRIP001      SetFrame(nTotalCol, nDestRow1 + nFirstLine, nDestCol2, nDestRow2);
//STRIP001  }
//STRIP001
//STRIP001  // Rahmen Zeilenergebnis
//STRIP001
//STRIP001  if (!bNoCols)
//STRIP001  {
//STRIP001      if (bDataAtCol)
//STRIP001      {
//STRIP001          for (short i=0; i<nDataCount; i++)
//STRIP001          {
//STRIP001              String aLab = *pLabelTotal;
//STRIP001              aLab += ' ';
//STRIP001              aLab += *pLabel[lcl_MaskToIndex( aDataArr[i].nFuncMask )];
//STRIP001              aLab += ' ';
//STRIP001              aLab += pDataList->GetString(i);
//STRIP001              pDoc->SetString(nDestCol1, nTotalRow+i, nDestTab, aLab);
//STRIP001              //  Kategorie 8
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pDoc->SetString(nDestCol1, nTotalRow, nDestTab, *pLabelTotal);
//STRIP001          //  Kategorie 9
//STRIP001      }
//STRIP001
//STRIP001      if ( nDataStartCol )
//STRIP001          SetStyle(nDestCol1, nTotalRow, nDataStartCol-1, nDestRow2, PIVOT_STYLE_TITLE);
//STRIP001      SetStyle(nDataStartCol, nTotalRow, nDestCol2, nDestRow2, PIVOT_STYLE_RESULT);
//STRIP001      SetFrame(nDestCol1, nTotalRow, nDestCol2, nDestRow2);
//STRIP001  }
//STRIP001
//STRIP001  // Rahmen gesamt
//STRIP001  SetFrame(nDestCol1, nDestRow1 + nFirstLine, nDestCol2, nDestRow2, 40);
//STRIP001 }

/*N*/ void ScPivot::ReleaseData()
/*N*/ {
/*N*/   short i;
/*N*/   for (i = 0; i < PIVOT_MAXFIELD; i++)
/*N*/   {
/*N*/       pColList[i]->FreeAll();
/*N*/       pRowList[i]->FreeAll();
/*N*/   }
/*N*/   if (ppDataArr)
/*N*/   {
/*N*/       for (i=0; i<nDataRowCount; i++)
/*N*/           delete[] ppDataArr[i];
/*N*/       delete[] ppDataArr;
/*N*/       ppDataArr = NULL;
/*N*/   }
/*N*/   nDataColCount = 0;
/*N*/   nDataRowCount = 0;
/*N*/   delete[] pColRef;
/*N*/   pColRef = NULL;
/*N*/ }

//STRIP001 BOOL ScPivot::IsPivotAtCursor(USHORT nCol, USHORT nRow, USHORT nTab) const
//STRIP001 {
//STRIP001  if (bValidArea)
//STRIP001      return ( nTab == nDestTab
//STRIP001                  && nCol >= nDestCol1 && nCol <= nDestCol2
//STRIP001                  && nRow >= nDestRow1 && nRow <= nDestRow2 );
//STRIP001  else
//STRIP001      return FALSE;
//STRIP001 }

//STRIP001 BOOL ScPivot::IsFilterAtCursor(USHORT nCol, USHORT nRow, USHORT nTab) const
//STRIP001 {
//STRIP001  if (bValidArea)
//STRIP001      return (nCol == nDestCol1 && nRow == nDestRow1 && nTab == nDestTab);
//STRIP001  else
//STRIP001      return FALSE;
//STRIP001 }

//STRIP001 BOOL ScPivot::GetColFieldAtCursor(USHORT nCol, USHORT nRow, USHORT nTab, USHORT& rField) const
//STRIP001 {
//STRIP001  rField = 0;
//STRIP001  BOOL bRet = FALSE;
//STRIP001  if (bValidArea)
//STRIP001  {
//STRIP001      bRet = ( nCol >= nDestCol1 && nCol < nDataStartCol
//STRIP001              && nRow == nDataStartRow - 1
//STRIP001              && nTab == nDestTab );
//STRIP001      if (bRet)
//STRIP001      {
//STRIP001          rField = aColArr[nCol - nDestCol1].nCol;
//STRIP001          if (rField == PIVOT_DATA_FIELD)
//STRIP001              bRet = (nDataCount > 1);
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL ScPivot::GetRowFieldAtCursor(USHORT nCol, USHORT nRow, USHORT nTab, USHORT& rField) const
//STRIP001 {
//STRIP001  rField = 0;
//STRIP001  BOOL bRet = FALSE;
//STRIP001  if (bValidArea)
//STRIP001  {
//STRIP001      bRet = ( nCol >= nDataStartCol && nCol < nDataStartCol + nRowCount
//STRIP001              && nRow == nDestRow1 + nFirstLine
//STRIP001              && nTab == nDestTab );
//STRIP001      if (bRet)
//STRIP001      {
//STRIP001          rField = aRowArr[nCol - nDataStartCol].nCol;
//STRIP001          if (rField == PIVOT_DATA_FIELD)
//STRIP001              bRet = (nDataCount > 1);
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }


//--------------------------------------------------------------------------------------------------
// Private Methoden
//--------------------------------------------------------------------------------------------------

/*N*/ BOOL ScPivot::CreateFields()
/*N*/ {
/*N*/   short   i;
/*N*/   USHORT  nRow;
/*N*/   USHORT  nHeader;
/*N*/   String  aStr;
/*N*/   TypedStrData* pStrData;
/*N*/   if (bHasHeader)
/*N*/       nHeader = 1;
/*N*/   else
/*N*/       nHeader = 0;
/*N*/
/*N*/   // Sortieren nach Benutzerdefinierte Listen ??
/*N*/   for (i = 0; i < nColCount; i++)
/*N*/   {
/*N*/       if (aColArr[i].nCol != PIVOT_DATA_FIELD)
/*N*/       {
/*N*/           pDoc->GetString(aColArr[i].nCol, nSrcRow1 + nHeader, nSrcTab, aStr);
/*N*/           pColList[i]->SetUserData(ScGlobal::GetUserList()->GetData(aStr));
/*N*/       }
/*N*/       else
/*N*/           pColList[i]->SetUserData(NULL);
/*N*/   }
/*N*/   for (i = 0; i < nRowCount; i++)
/*N*/   {
/*N*/       if (aRowArr[i].nCol != PIVOT_DATA_FIELD)
/*N*/       {
/*N*/           pDoc->GetString(aRowArr[i].nCol, nSrcRow1 + nHeader, nSrcTab, aStr);
/*N*/           pRowList[i]->SetUserData(ScGlobal::GetUserList()->GetData(aStr));
/*N*/       }
/*N*/       else
/*?*/           pRowList[i]->SetUserData(NULL);
/*N*/   }
/*N*/
/*N*/   ScAddress aSrcAdr( nSrcCol1, 0, nSrcTab );
/*N*/   for (nRow = nSrcRow1 + nHeader; nRow <= nSrcRow2; nRow++)
/*N*/   {
/*N*/       BOOL bValidLine = TRUE;
/*N*/       if (bIgnoreEmpty)
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 aSrcAdr.SetRow( nRow );
//STRIP001 /*?*/            bValidLine = !lcl_IsEmptyLine( pDoc, aSrcAdr, nSrcCol2 );
/*N*/       }
/*N*/       if (bValidLine)
/*N*/           bValidLine = pDoc->pTab[nSrcTab]->ValidQuery(nRow, aQuery);
/*N*/       if (bValidLine)
/*N*/       {
/*N*/           //  Sortierte Liste der Felder erzeugen
/*N*/           //! statt GetCategoryString leere weglassen !
/*N*/
/*N*/           for (i = 0; i < nColCount; i++)
/*N*/           {
/*N*/               if (aColArr[i].nCol != PIVOT_DATA_FIELD)
/*N*/               {
/*N*/                   USHORT nCatRow = bDetectCat ? GetCategoryRow( aColArr[i].nCol, nRow ) : nRow;
/*N*/                   pStrData = new TypedStrData( pDoc, aColArr[i].nCol, nCatRow, nSrcTab, TRUE );
/*N*/                   if (!(pColList[i]->Insert(pStrData)))
/*N*/                       delete pStrData;
/*N*/               }
/*N*/           }
/*N*/           for (i = 0; i < nRowCount; i++)
/*N*/           {
/*N*/               if (aRowArr[i].nCol != PIVOT_DATA_FIELD)
/*N*/               {
/*N*/                   USHORT nCatRow = bDetectCat ? GetCategoryRow( aRowArr[i].nCol, nRow ) : nRow;
/*N*/                   pStrData = new TypedStrData( pDoc, aRowArr[i].nCol, nCatRow, nSrcTab, TRUE );
/*N*/                   if (!(pRowList[i]->Insert(pStrData)))
/*N*/                       delete pStrData;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return TRUE;
/*N*/ }

/*N*/ void ScPivot::CreateFieldData()
/*N*/ {
/*N*/   USHORT* pRowListIndex = nRowCount ? new USHORT[nRowCount] : NULL;
/*N*/   USHORT* pColListIndex = nColCount ? new USHORT[nColCount] : NULL;
/*N*/
/*N*/   short i,j,k;
/*N*/
/*N*/   ppDataArr = new SubTotal*[nDataRowCount];
/*N*/   for (i=0; i<nDataRowCount; i++)
/*N*/       ppDataArr[i] = new SubTotal[nDataColCount];
/*N*/
/*N*/   if (bDataAtCol)
/*N*/       for (j=0; j<nDataRowCount; j++)
/*N*/           for (i=0; i<nDataColCount; i++)
/*N*/               ppDataArr[j][i].nIndex = j/nDataMult%nDataCount;
/*N*/   else
/*?*/       for (j=0; j<nDataRowCount; j++)
/*?*/           for (i=0; i<nDataColCount; i++)
/*?*/               ppDataArr[j][i].nIndex = i/nDataMult%nDataCount;
/*N*/
/*N*/   short nHeader;
/*N*/   if (bHasHeader)
/*N*/       nHeader = 1;
/*N*/   else
/*N*/       nHeader = 0;
/*N*/   ScAddress aSrcAdr( nSrcCol1, 0, nSrcTab );
/*N*/   for (USHORT nRow = nSrcRow1 + nHeader; nRow <= nSrcRow2; nRow++)
/*N*/   {
/*N*/       BOOL bValidLine = TRUE;
/*N*/       if (bIgnoreEmpty)
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 aSrcAdr.SetRow( nRow );
//STRIP001 /*?*/            bValidLine = !lcl_IsEmptyLine( pDoc, aSrcAdr, nSrcCol2 );
/*N*/       }
/*N*/       if (bValidLine)
/*N*/           bValidLine = pDoc->pTab[nSrcTab]->ValidQuery(nRow, aQuery);
/*N*/       if (bValidLine)
/*N*/       {
/*N*/           //      Indizes der Kategorien nur einmal ausserhalb nDataCount
/*N*/           for (j=0; j<nRowCount; j++)
/*N*/               if (aRowArr[j].nCol != PIVOT_DATA_FIELD)
/*N*/               {
/*N*/                   USHORT nCatRow = bDetectCat ? GetCategoryRow( aRowArr[j].nCol, nRow ) : nRow;
/*N*/                   TypedStrData aStrData( pDoc, aRowArr[j].nCol, nCatRow, nSrcTab, TRUE );
/*N*/                   pRowListIndex[j] = pRowList[j]->GetIndex(&aStrData);
/*N*/               }
/*N*/           for (j=0; j<nColCount; j++)
/*N*/               if (aColArr[j].nCol != PIVOT_DATA_FIELD)
/*N*/               {
/*N*/                   USHORT nCatRow = bDetectCat ? GetCategoryRow( aColArr[j].nCol, nRow ) : nRow;
/*N*/                   TypedStrData aStrData( pDoc, aColArr[j].nCol, nCatRow, nSrcTab, TRUE );
/*N*/                   pColListIndex[j] = pColList[j]->GetIndex(&aStrData);
/*N*/               }
/*N*/
/*N*/           String aStr;
/*N*/           short nCIndex;
/*N*/           short nRIndex;
/*N*/           short nIndex;
/*N*/           ScAddress aAdr( 0, nRow, nSrcTab );
/*N*/
/*N*/           for (i=0; i<nDataCount; i++)
/*N*/           {
/*N*/               // ColIndex Berechnen
/*N*/               nCIndex = 0;
/*N*/               for (j=0; j<nRowCount; j++)
/*N*/               {
/*N*/                   if (aRowArr[j].nCol == PIVOT_DATA_FIELD)
/*N*/                       nIndex = i;
/*N*/                   else
/*N*/                       nIndex = pRowListIndex[j];
/*N*/                   if (nIndex)
/*N*/                   {
/*N*/                       for (k=j+1; k<nRowCount; k++)
/*?*/                           nIndex *= pRowList[k]->GetCount();
/*N*/                       nCIndex += nIndex;
/*N*/                   }
/*N*/               }
/*N*/               // RowIndex Berechnen
/*N*/               nRIndex = 0;
/*N*/               for (j=0; j<nColCount; j++)
/*N*/               {
/*N*/                   if (aColArr[j].nCol == PIVOT_DATA_FIELD)
/*N*/                       nIndex = i;
/*N*/                   else
/*N*/                       nIndex = pColListIndex[j];
/*N*/                   if (nIndex)
/*N*/                   {
/*N*/                       for (k=j+1; k<nColCount; k++)
/*N*/                           nIndex *= pColList[k]->GetCount();
/*N*/                       nRIndex += nIndex;
/*N*/                   }
/*N*/               }
/*N*/               //  Daten eintragen
/*N*/               if ((nCIndex < nDataColCount) && (nRIndex < nDataRowCount))
/*N*/               {
/*N*/                   DBG_ASSERT((short)ppDataArr[nRIndex][nCIndex].nIndex == i, "falsch init.")
/*N*/
/*N*/                   ppDataArr[nRIndex][nCIndex].nIndex = i;
/*N*/                   aAdr.SetCol( aDataArr[i].nCol );
/*N*/                   CellType eCellType = pDoc->GetCellType( aAdr );
/*N*/                   if ((eCellType != CELLTYPE_NONE) && (eCellType != CELLTYPE_NOTE))
/*N*/                   {
/*N*/                       BOOL bValue = (eCellType == CELLTYPE_VALUE);
/*N*/                       if (eCellType == CELLTYPE_FORMULA)
/*N*/                       {
/*N*/                           ScBaseCell* pCell = pDoc->GetCell( aAdr );
/*N*/                           bValue = ((ScFormulaCell*)pCell)->IsValue();
/*N*/                       }
/*N*/
/*N*/                       if (bValue)
/*N*/                       {
/*N*/                           double nVal = pDoc->GetValue( aAdr );
/*N*/                           ppDataArr[nRIndex][nCIndex].Update(nVal);
/*N*/                       }
/*N*/                       else
/*?*/                       {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     ppDataArr[nRIndex][nCIndex].UpdateNoVal();      // nur nCount
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   delete pColListIndex;
/*N*/   delete pRowListIndex;
/*N*/ }

/*N*/ void ScPivot::CalcArea()
/*N*/ {
/*N*/   BOOL bNoRows = (nRowCount == 0) || ( nRowCount == 1 && aRowArr[0].nCol == PIVOT_DATA_FIELD );
/*N*/   BOOL bNoCols = (nColCount == 0) || ( nColCount == 1 && aColArr[0].nCol == PIVOT_DATA_FIELD );
/*N*/   if (!bMakeTotalCol) bNoRows = TRUE;
/*N*/   if (!bMakeTotalRow) bNoCols = TRUE;
/*N*/
/*N*/   short i;
/*N*/   short nDx;
/*N*/   // StartSpalte/StartZeile des Datenbereichs berechnen
/*N*/   if (bDataAtCol)
/*N*/   {
/*N*/       if (nDataCount > 1)
/*?*/           nDataStartCol = nDestCol1 + nColCount;
/*N*/       else
/*N*/           nDataStartCol = nDestCol1 + Max(0, nColCount - 1);
/*N*/   }
/*N*/   else
/*?*/       nDataStartCol = nDestCol1 + nColCount;
/*N*/   if (!bDataAtCol)
/*N*/   {
/*?*/       if (nDataCount > 1)
/*?*/           nDataStartRow = nDestRow1 + nRowCount + nFirstLine + 1;
/*?*/       else
/*?*/           nDataStartRow = nDestRow1 + Max(0, nRowCount - 1) + nFirstLine + 1;
/*N*/   }
/*N*/   else
/*N*/       nDataStartRow = nDestRow1 + nRowCount + nFirstLine + 1;
/*N*/
/*N*/   //
/*N*/   //      Groesse der PivotTabelle berechnen
/*N*/   //
/*N*/
/*N*/   if (nRowCount == 0 || (nRowCount==1 && aRowArr[0].nCol==PIVOT_DATA_FIELD && nDataCount==1))
/*N*/   {
/*?*/       nDataColCount = 1;
/*?*/       if (nDataCount == 1)
/*?*/           nDestCol2 = nDestCol1 + nColCount - 1;
/*?*/       else
/*?*/           nDestCol2 = nDestCol1 + nColCount;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       // Anzahl Spalten
/*N*/       if ((aRowArr[nRowCount-1].nCol == PIVOT_DATA_FIELD) && (nDataCount == 1))
/*N*/           nDx = 2;
/*N*/       else
/*N*/           nDx = 1;
/*N*/       long nColLines = pRowList[nRowCount-nDx]->GetCount();   // long um Ueberlauf zu erkennen
/*N*/       nDataColCount = pRowList[nRowCount-nDx]->GetCount();
/*N*/       for (i=nRowCount-nDx-1; i >= 0; i--)
/*N*/       {
/*?*/           nColLines *= pRowList[i]->GetCount();
/*?*/           nDataColCount *= pRowList[i]->GetCount();
/*?*/           if (!bDataAtCol)
/*?*/               nColLines += (pRowList[i]->GetCount() * aRowArr[i].nFuncCount * nDataCount);
/*?*/           else
/*?*/               nColLines += (pRowList[i]->GetCount() * aRowArr[i].nFuncCount);
/*N*/       }
/*N*/       /*
        // Ergebnisspalten des letzten Elements
        if (aRowArr[nRowCount-1].nCol != PIVOT_DATA_FIELD)
            nColLines += (pRowList[nRowCount-1]->GetCount() * aRowArr[nRowCount-1].nFuncCount);
        */
/*N*/       if (nColLines > MAXCOL)
/*?*/           nDestCol2 = MAXCOL+2;   // ungueltig, 1 wird unten abgezogen
/*N*/       else if (bDataAtCol)
/*N*/       {
/*N*/           if (nDataCount > 1)
/*?*/               nDestCol2 = nDestCol1 + nColCount + nColLines;
/*N*/           else
/*N*/               nDestCol2 = nDestCol1 + (nColCount - 1) + nColLines;
/*N*/           if (!bMakeTotalCol)
/*?*/               --nDestCol2;
/*N*/       }
/*N*/       else
/*?*/           nDestCol2 = nDestCol1 + nColCount + nColLines;
/*N*/   }
/*N*/
/*N*/   if (nColCount == 0 || (nColCount==1 && aColArr[0].nCol==PIVOT_DATA_FIELD && nDataCount==1))
/*N*/   {
/*?*/       nDataRowCount = 1;
/*?*/       if (nDataCount == 1)
/*?*/           nDestRow2 = nDestRow1 + (nRowCount - 1) + nFirstLine + 1;
/*?*/       else
/*?*/           nDestRow2 = nDestRow1 + nRowCount + nFirstLine + 1;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       // Anzahl Zeilen
/*N*/       if ((aColArr[nColCount-1].nCol == PIVOT_DATA_FIELD) && (nDataCount == 1))
/*N*/           nDx = 2;
/*N*/       else
/*N*/           nDx = 1;
/*N*/       long nRowLines = pColList[nColCount-nDx]->GetCount();   // long um Ueberlauf zu erkennen
/*N*/       nDataRowCount = pColList[nColCount-nDx]->GetCount();
/*N*/       for (i=nColCount-nDx-1; i >= 0; i--)
/*N*/       {
/*?*/           nRowLines *= pColList[i]->GetCount();
/*?*/           nDataRowCount *= pColList[i]->GetCount();
/*?*/           if (bDataAtCol)
/*?*/               nRowLines += (pColList[i]->GetCount() * aColArr[i].nFuncCount * nDataCount);
/*?*/           else
/*?*/               nRowLines += (pColList[i]->GetCount() * aColArr[i].nFuncCount);
/*N*/       }
        /*
        // Ergebniszeilen des letzten Elements
        if (aColArr[nColCount-1].nCol != PIVOT_DATA_FIELD)
             nRowLines += (pColList[nColCount-1]->GetCount() * aColArr[nColCount-1].nFuncCount);
         */
/*N*/       if (nRowLines > MAXROW)
/*?*/           nDestRow2 = MAXROW+2;   // ungueltig, 1 wird unten abgezogen
/*N*/       else if (!bDataAtCol)
/*N*/       {
/*?*/           if (nDataCount > 1)
/*?*/               nDestRow2 = nDestRow1 + nRowCount + nRowLines + nFirstLine + 1;
/*?*/           else
/*?*/               nDestRow2 = nDestRow1 + (nRowCount - 1) + nRowLines + nFirstLine + 1;
/*?*/           if (!bMakeTotalRow)
/*?*/               --nDestRow2;
/*N*/       }
/*N*/       else
/*N*/           nDestRow2 = nDestRow1 + nRowCount + nRowLines + nFirstLine + 1;
/*N*/   }
/*N*/
/*N*/   if (bDataAtCol)
/*N*/   {
/*N*/       if (!bNoCols)
/*N*/           nDestRow2 += nDataCount;
/*N*/       nDestRow2 --;
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       if (!bNoRows)
/*?*/           nDestCol2 += nDataCount;
/*?*/       nDestCol2 --;
/*N*/   }
/*N*/ }

//STRIP001 void ScPivot::SetDataLine(USHORT nCol, USHORT nRow, USHORT nTab, USHORT nRIndex)
//STRIP001 {
//STRIP001  USHORT nCIndex2;
//STRIP001  short j;
//STRIP001  short i;
//STRIP001
//STRIP001  SubTotal aGrandTotal[PIVOT_MAXFIELD];           // pro Daten-Feld
//STRIP001
//STRIP001  for (i=0; i < nColIndex; i++)
//STRIP001  {
//STRIP001      USHORT nCIndex = pColRef[i].nDataIndex;
//STRIP001      if (nCIndex != PIVOT_FUNC_REF)
//STRIP001      {
//STRIP001 //           if ( ppDataArr[nRIndex][nCIndex].GetCount() )
//STRIP001          {
//STRIP001              USHORT nDIndex = ppDataArr[nRIndex][nCIndex].nIndex;
//STRIP001              SetValue( nCol+i, nRow, ppDataArr[nRIndex][nCIndex], aDataArr[nDIndex].nFuncMask );
//STRIP001              //  Kategorie 18
//STRIP001
//STRIP001              if (bDataAtCol)
//STRIP001                  aGrandTotal[0].Update(ppDataArr[nRIndex][nCIndex]);
//STRIP001              else
//STRIP001                  aGrandTotal[nDIndex].Update(ppDataArr[nRIndex][nCIndex]);
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          SubTotal aTotal;
//STRIP001          short k = i-1;
//STRIP001          while ((pColRef[k].nDataIndex == PIVOT_FUNC_REF) && (k > 0)) k--;
//STRIP001          for (j=k; (j>=0) && (pColRef[j].nRecCount > pColRef[i].nRecCount); j--)
//STRIP001          {
//STRIP001              nCIndex2 = pColRef[j].nDataIndex;
//STRIP001              if (nCIndex2 != PIVOT_FUNC_REF)
//STRIP001              {
//STRIP001                  if ((pColRef[i].nIndex == ppDataArr[nRIndex][nCIndex2].nIndex) ||
//STRIP001                      (pColRef[i].nIndex == 0xffff))
//STRIP001                  {
//STRIP001                      aTotal.Update( ppDataArr[nRIndex][nCIndex2] );
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          USHORT nFunc = pColRef[i].nFuncMask;
//STRIP001          if (nFunc == PIVOT_FUNC_AUTO)
//STRIP001              nFunc = aDataArr[nRIndex/nDataMult%nDataCount].nFuncMask;
//STRIP001          SetValue( nCol+i, nRow, aTotal, nFunc );
//STRIP001          //  Kategorie 19
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  BOOL bNoRows = (nRowCount == 0) || ( nRowCount == 1 && aRowArr[0].nCol == PIVOT_DATA_FIELD );
//STRIP001  if (!bMakeTotalCol) bNoRows = TRUE;
//STRIP001
//STRIP001  if (!bNoRows)
//STRIP001  {
//STRIP001      if (bDataAtCol)
//STRIP001      {
//STRIP001          SetValue( nDestCol2, nRow, aGrandTotal[0], aDataArr[nRIndex/nDataMult%nDataCount].nFuncMask );
//STRIP001          //  Kategorie 20
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          USHORT nTotalCol = nDestCol2 - nDataCount + 1;
//STRIP001          for (short nTotCnt = 0; nTotCnt<nDataCount; nTotCnt++)
//STRIP001          {
//STRIP001              SetValue( nTotalCol+nTotCnt, nRow, aGrandTotal[nTotCnt], aDataArr[nTotCnt].nFuncMask );
//STRIP001              //  Kategorie 21
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void ScPivot::SetFuncLine(USHORT nCol, USHORT nRow, USHORT nTab, USHORT nFunc, USHORT nIndex, USHORT nStartRIndex, USHORT nEndRIndex)
//STRIP001 {
//STRIP001  short nSubtCount = 0;
//STRIP001  SubTotal aGrandTotal[PIVOT_MAXFIELD];
//STRIP001  USHORT nThisFunc = nFunc;
//STRIP001
//STRIP001  for (short i=0; i<nColIndex; i++)
//STRIP001  {
//STRIP001      USHORT nCIndex = pColRef[i].nDataIndex;
//STRIP001      if (nCIndex != PIVOT_FUNC_REF)
//STRIP001      {
//STRIP001          SubTotal aTotal;
//STRIP001          for (USHORT j = nStartRIndex; j < nEndRIndex; j++)
//STRIP001          {
//STRIP001              USHORT nDIndex = ppDataArr[j][nCIndex].nIndex;
//STRIP001              if ((nIndex == nDIndex) || (nIndex == 0xffff))
//STRIP001              {
//STRIP001                  aTotal.Update( ppDataArr[j][nCIndex] );
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          if (bDataAtCol)
//STRIP001              aGrandTotal[0].Update( aTotal );
//STRIP001          else
//STRIP001              aGrandTotal[nCIndex/nDataMult%nDataCount].Update( aTotal );     //! immer ?
//STRIP001
//STRIP001          if (nFunc == PIVOT_FUNC_AUTO)
//STRIP001          {
//STRIP001              if (bDataAtCol)
//STRIP001              {
//STRIP001                  if ((short)nIndex<nDataCount)
//STRIP001                      nThisFunc = aDataArr[nIndex].nFuncMask;
//STRIP001                  else
//STRIP001                      DBG_ERROR("wat fuer'n Index ???");
//STRIP001              }
//STRIP001              else
//STRIP001                  nThisFunc = aDataArr[nCIndex/nDataMult%nDataCount].nFuncMask;
//STRIP001          }
//STRIP001          SetValue( nCol+i, nRow, aTotal, nThisFunc );
//STRIP001          //  Kategorie 22
//STRIP001      }
//STRIP001      else
//STRIP001      {                       //  Kreuzungspunkte kompatibel ?
//STRIP001
//STRIP001          if ( nFunc == pColRef[i].nFuncMask )
//STRIP001          {
//STRIP001              USHORT nEffIndex = nIndex;
//STRIP001              if (nEffIndex == 0xffff)
//STRIP001              {
//STRIP001                  nEffIndex = nSubtCount % nDataCount;
//STRIP001                  ++nSubtCount;
//STRIP001              }
//STRIP001              SubTotal aTotal;
//STRIP001
//STRIP001              short k = i-1;
//STRIP001              short j;
//STRIP001              while ((pColRef[k].nDataIndex == PIVOT_FUNC_REF) && (k > 0)) k--;
//STRIP001              for (j=k; (j>=0) && (pColRef[j].nRecCount > pColRef[i].nRecCount); j--)
//STRIP001              {
//STRIP001                  nCIndex = pColRef[j].nDataIndex;
//STRIP001                  if (nCIndex != PIVOT_FUNC_REF)
//STRIP001                  {
//STRIP001                      for (USHORT nRIndex = nStartRIndex; nRIndex < nEndRIndex; nRIndex++)
//STRIP001                      {
//STRIP001                          USHORT nDIndex = ppDataArr[nRIndex][nCIndex].nIndex;
//STRIP001                          if (nEffIndex == nDIndex)
//STRIP001                          {
//STRIP001                              aTotal.Update( ppDataArr[nRIndex][nCIndex] );
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              if (nFunc == PIVOT_FUNC_AUTO)
//STRIP001              {
//STRIP001                  if ((short)nEffIndex<nDataCount)
//STRIP001                      nThisFunc = aDataArr[nEffIndex].nFuncMask;
//STRIP001                  else
//STRIP001                      DBG_ERROR("wat fuer'n Index ???");
//STRIP001              }
//STRIP001              SetValue( nCol+i, nRow, aTotal, nThisFunc );
//STRIP001              //  Kategorie 23
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  BOOL bNoRows = (nRowCount == 0) || ( nRowCount == 1 && aRowArr[0].nCol == PIVOT_DATA_FIELD );
//STRIP001  if (!bMakeTotalCol) bNoRows = TRUE;
//STRIP001
//STRIP001  if (!bNoRows)
//STRIP001  {
//STRIP001      if (bDataAtCol)
//STRIP001      {
//STRIP001          if (nFunc == PIVOT_FUNC_AUTO)
//STRIP001          {
//STRIP001              if ((short)nIndex<nDataCount)
//STRIP001                  nThisFunc = aDataArr[nIndex].nFuncMask;
//STRIP001              else
//STRIP001                  DBG_ERROR("wat fuer'n Index ???");
//STRIP001          }
//STRIP001          SetValue( nDestCol2, nRow, aGrandTotal[0], nThisFunc );
//STRIP001          //  Kategorie 24
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          USHORT nTotalCol = nDestCol2 - nDataCount + 1;
//STRIP001          for (short nTotCnt = 0; nTotCnt<nDataCount; nTotCnt++)
//STRIP001          {
//STRIP001              if (nFunc == PIVOT_FUNC_AUTO)
//STRIP001                  nThisFunc = aDataArr[nTotCnt%nDataCount].nFuncMask;
//STRIP001              SetValue( nTotalCol+nTotCnt, nRow, aGrandTotal[nTotCnt], nThisFunc );
//STRIP001              //  Kategorie 25
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void ScPivot::ColToTable(short nField, USHORT& nRow, ScProgress& rProgress)
//STRIP001 {
//STRIP001  USHORT nCol = nDestCol1 + nField;
//STRIP001  if (nColCount == 0)
//STRIP001  {
//STRIP001 //       SetDataLine(nCol + 1, nRow, nDestTab, nRowIndex);
//STRIP001      SetDataLine(nCol, nRow, nDestTab, nRowIndex);
//STRIP001      nRowIndex++;
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  USHORT i;
//STRIP001  short nDx;
//STRIP001  if ((aColArr[nColCount -1].nCol == PIVOT_DATA_FIELD) && (nDataCount == 1))
//STRIP001      nDx = 2;
//STRIP001  else
//STRIP001      nDx = 1;
//STRIP001  if (nField < nColCount - nDx)
//STRIP001  {
//STRIP001      for (i = 0; i < pColList[nField]->GetCount(); i++)
//STRIP001      {
//STRIP001          USHORT nSaveIndex = nRowIndex;
//STRIP001          String aStr = pColList[nField]->GetString(i);
//STRIP001          if (!aStr.Len()) aStr = ScGlobal::GetRscString(STR_EMPTYDATA);
//STRIP001          pDoc->SetString(nCol, nRow, nDestTab, aStr);
//STRIP001          //  Kategorie 10
//STRIP001          USHORT nSaveRow = nRow;
//STRIP001          ColToTable(nField + 1, nRow, rProgress);
//STRIP001          SetStyle(nCol, nSaveRow, nCol, nRow - 1, PIVOT_STYLE_CATEGORY);
//STRIP001          SetFrame(nCol, nSaveRow, nCol, nRow - 1);
//STRIP001          if (aColArr[nField].nFuncCount > 0)                 // Zwischenergebnisse eingestellt?
//STRIP001          {
//STRIP001              nSaveRow = nRow;
//STRIP001              for (short j=0; j<=PIVOT_MAXFUNC; j++)                  // incl. "auto"
//STRIP001              {
//STRIP001                  if (aColArr[nField].nFuncMask & nFuncMaskArr[j])
//STRIP001                  {
//STRIP001                      String aLab;
//STRIP001                      if (bDataAtCol)
//STRIP001                      {
//STRIP001                          for (short k=0; k < nDataCount; k++)
//STRIP001                          {
//STRIP001                              String aDataStr = pDataList->GetString(k);  // ist immer String
//STRIP001                              aLab = aStr;
//STRIP001                              short nFuncType;
//STRIP001                              if ( j==PIVOT_MAXFUNC )
//STRIP001                                  nFuncType = lcl_MaskToIndex( aDataArr[k].nFuncMask );
//STRIP001                              else
//STRIP001                                  nFuncType = j;
//STRIP001                              aLab += ' ';
//STRIP001                              aLab += *pLabel[nFuncType];
//STRIP001                              aLab += ' ';
//STRIP001                              aLab += aDataStr;
//STRIP001                              pDoc->SetString(nCol, nRow, nDestTab, aLab);
//STRIP001                              //  Kategorie 11
//STRIP001                              SetFuncLine(nDataStartCol, nRow, nDestTab, nFuncMaskArr[j], k, nSaveIndex, nRowIndex);
//STRIP001                              nRow++;
//STRIP001                          }
//STRIP001                      }
//STRIP001                      else
//STRIP001                      {
//STRIP001                          aLab = aStr;
//STRIP001                          aLab += ' ';
//STRIP001                          aLab += *pLabel[j];
//STRIP001                          pDoc->SetString(nCol, nRow, nDestTab, aLab);
//STRIP001                          //  Kategorie 12
//STRIP001                          SetFuncLine(nDataStartCol, nRow, nDestTab, nFuncMaskArr[j], 0xffff, nSaveIndex, nRowIndex);
//STRIP001                          nRow++;
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001              if ( nDataStartCol )
//STRIP001                  SetStyle(nCol, nSaveRow, nDataStartCol-1, nRow-1, PIVOT_STYLE_TITLE);
//STRIP001              SetStyle(nDataStartCol, nSaveRow, nDestCol2, nRow-1, PIVOT_STYLE_RESULT);
//STRIP001              SetFrameHor(nCol, nSaveRow, nDestCol2, nRow-1);
//STRIP001          }
//STRIP001          nSaveIndex = nRowIndex;
//STRIP001      }
//STRIP001  }
//STRIP001  else if (nField < nColCount)
//STRIP001  {
//STRIP001      USHORT nCatCount = pColList[nField]->GetCount();
//STRIP001      SetStyle(nCol, nRow, nCol, nRow+nCatCount-1, PIVOT_STYLE_CATEGORY);
//STRIP001      SetFrame(nCol, nRow, nDestCol2, nRow+nCatCount-1);
//STRIP001      for (i = 0; i < nCatCount; i++)
//STRIP001      {
//STRIP001          String aTmpStr = pColList[nField]->GetString(i);
//STRIP001          if (!aTmpStr.Len()) aTmpStr = ScGlobal::GetRscString(STR_EMPTYDATA);
//STRIP001
//STRIP001          String aPutStr;
//STRIP001          if (pColList[nField] == pDataList)
//STRIP001          {
//STRIP001              short nFuncType = lcl_MaskToIndex( aDataArr[i].nFuncMask );
//STRIP001              aPutStr  = *pLabel[nFuncType];
//STRIP001              aPutStr += ' ';
//STRIP001              aPutStr += aTmpStr;
//STRIP001          }
//STRIP001          else
//STRIP001              aPutStr += aTmpStr;
//STRIP001
//STRIP001          pDoc->SetString(nCol, nRow, nDestTab, aPutStr);
//STRIP001          //  Kategorie 13
//STRIP001          SetDataLine(nCol + 1, nRow, nDestTab, nRowIndex);
//STRIP001          nRowIndex++;
//STRIP001          nRow++;
//STRIP001
//STRIP001          rProgress.SetState( nRow - nDestRow1 );
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void ScPivot::RowToTable(short nField, USHORT& nCol)
//STRIP001 {
//STRIP001  nRecCount++;
//STRIP001  USHORT nRow = nDestRow1 + nFirstLine + nField + 1;
//STRIP001  USHORT i;
//STRIP001  if (nRowCount == 0)
//STRIP001  {
//STRIP001      pColRef[nColIndex].nDataIndex = nDataIndex;
//STRIP001      nColIndex++;
//STRIP001      nDataIndex++;
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  short nDx;
//STRIP001  if ((aRowArr[nRowCount -1].nCol == PIVOT_DATA_FIELD) && (nDataCount == 1))
//STRIP001      nDx = 2;
//STRIP001  else
//STRIP001      nDx = 1;
//STRIP001
//STRIP001  if (nField < nRowCount - nDx)
//STRIP001  {
//STRIP001      for (i = 0; i < pRowList[nField]->GetCount(); i++)
//STRIP001      {
//STRIP001          String aStr = pRowList[nField]->GetString(i);
//STRIP001          if (!aStr.Len()) aStr = ScGlobal::GetRscString(STR_EMPTYDATA);
//STRIP001          pDoc->SetString(nCol, nRow, nDestTab, aStr);
//STRIP001          //  Kategorie 14
//STRIP001          USHORT nSaveCol = nCol;
//STRIP001          RowToTable(nField + 1, nCol);
//STRIP001          SetStyle(nSaveCol, nRow, nCol - 1, nRow, PIVOT_STYLE_CATEGORY);
//STRIP001          SetFrame(nSaveCol, nRow, nCol - 1, nRow);
//STRIP001          if (aRowArr[nField].nFuncCount > 0)
//STRIP001          {
//STRIP001              nSaveCol = nCol;
//STRIP001              for (USHORT j=0; j<=PIVOT_MAXFUNC; j++)                 // incl. "auto"
//STRIP001              {
//STRIP001                  if (aRowArr[nField].nFuncMask & nFuncMaskArr[j])
//STRIP001                  {
//STRIP001                      String aLab;
//STRIP001                      if (!bDataAtCol)
//STRIP001                      {
//STRIP001                          for (short k=0; k < nDataCount; k++)
//STRIP001                          {
//STRIP001                              aLab = aStr;
//STRIP001                              short nFuncType;
//STRIP001                              if ( j==PIVOT_MAXFUNC )
//STRIP001                                  nFuncType = lcl_MaskToIndex( aDataArr[k].nFuncMask );
//STRIP001                              else
//STRIP001                                  nFuncType = j;
//STRIP001                              aLab += ' ';
//STRIP001                              aLab += *pLabel[nFuncType];
//STRIP001                              aLab += ' ';
//STRIP001                              aLab += pDataList->GetString(k);
//STRIP001                              pDoc->SetString(nCol, nRow, nDestTab, aLab);
//STRIP001                              //  Kategorie 15
//STRIP001                              pColRef[nColIndex].nDataIndex = PIVOT_FUNC_REF;
//STRIP001                              pColRef[nColIndex].nRecCount = nRecCount;
//STRIP001                              pColRef[nColIndex].nIndex = k;
//STRIP001                              pColRef[nColIndex].nFuncMask = nFuncMaskArr[j];
//STRIP001                              nColIndex++;
//STRIP001                              nCol++;
//STRIP001                          }
//STRIP001                      }
//STRIP001                      else
//STRIP001                      {
//STRIP001                          aLab = aStr;
//STRIP001                          aLab += ' ';
//STRIP001                          aLab += *pLabel[j];
//STRIP001                          pDoc->SetString(nCol, nRow, nDestTab, aLab);
//STRIP001                          //  Kategorie 16
//STRIP001                          pColRef[nColIndex].nDataIndex = PIVOT_FUNC_REF;
//STRIP001                          pColRef[nColIndex].nRecCount = nRecCount;
//STRIP001                          pColRef[nColIndex].nIndex = 0xffff;
//STRIP001                          pColRef[nColIndex].nFuncMask = nFuncMaskArr[j];
//STRIP001                          nColIndex++;
//STRIP001                          nCol++;
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001              if ( nDataStartRow )
//STRIP001                  SetStyle(nSaveCol, nRow,
//STRIP001                              nCol-1, nDataStartRow-1, PIVOT_STYLE_TITLE);
//STRIP001              SetStyle(nSaveCol, nDataStartRow, nCol-1, nDestRow2, PIVOT_STYLE_RESULT);
//STRIP001              SetFrameVer(nSaveCol, nRow, nCol-1, nDestRow2);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else if (nField < nRowCount)
//STRIP001  {
//STRIP001      USHORT nCatCount = pRowList[nField]->GetCount();
//STRIP001      SetStyle(nCol, nRow, nCol+nCatCount-1, nRow, PIVOT_STYLE_CATEGORY);
//STRIP001      SetFrame(nCol, nRow, nCol+nCatCount-1, nDestRow2);
//STRIP001      for (i = 0; i < nCatCount; i++)
//STRIP001      {
//STRIP001          String aTmpStr = pRowList[nField]->GetString(i);
//STRIP001          if (!aTmpStr.Len()) aTmpStr = ScGlobal::GetRscString(STR_EMPTYDATA);
//STRIP001
//STRIP001          String aPutStr;
//STRIP001          if (pRowList[nField] == pDataList)
//STRIP001          {
//STRIP001              short nFuncType = lcl_MaskToIndex( aDataArr[i].nFuncMask );
//STRIP001              aPutStr  = *pLabel[nFuncType];
//STRIP001              aPutStr += ' ';
//STRIP001              aPutStr += aTmpStr;
//STRIP001          }
//STRIP001          else
//STRIP001              aPutStr = aTmpStr;
//STRIP001
//STRIP001          pDoc->SetString(nCol, nRow, nDestTab, aPutStr);
//STRIP001          //  Kategorie 17
//STRIP001          pColRef[nColIndex].nDataIndex = nDataIndex;
//STRIP001          pColRef[nColIndex].nRecCount = nRecCount;
//STRIP001          pColRef[nColIndex].nIndex = 0xffff;
//STRIP001          pColRef[nColIndex].nFuncMask = PIVOT_FUNC_NONE;
//STRIP001          nColIndex++;
//STRIP001          nDataIndex++;
//STRIP001          nCol++;
//STRIP001      }
//STRIP001  }
//STRIP001  nRecCount--;
//STRIP001 }

/*N*/ USHORT ScPivot::GetCategoryRow( USHORT nCol, USHORT nRow )
/*N*/ {
/*N*/   USHORT nMinRow = nSrcRow1;
/*N*/   if (bHasHeader) ++nMinRow;
/*N*/   BOOL bFound = FALSE;
/*N*/   do
/*N*/   {
/*N*/       if ( !pDoc->HasData( nCol, nRow, nSrcTab ) && nRow>nMinRow )
/*N*/           --nRow;
/*N*/       else
/*N*/           bFound = TRUE;
/*N*/   }
/*N*/   while (!bFound);
/*N*/   return nRow;
/*N*/ }



}
