/*************************************************************************
 *
 *  $RCSfile: sc_dbdocfun.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:18:20 $
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
#include "ui_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------

#include <bf_sfx2/app.hxx>
#include <vcl/msgbox.hxx>
#include <vcl/waitobj.hxx>

#include <com/sun/star/sdbc/XResultSet.hpp>

#include "dbdocfun.hxx"
#include "bf_sc.hrc"
#include "dbcolect.hxx"
#include "undodat.hxx"
#include "docsh.hxx"
#include "docfunc.hxx"
#include "globstr.hrc"
#include "tabvwsh.hxx"
#include "patattr.hxx"
#include "rangenam.hxx"
#include "olinetab.hxx"
#include "dpobject.hxx"
#include "dociter.hxx"      // for lcl_EmptyExcept
#include "cell.hxx"         // for lcl_EmptyExcept
#include "editable.hxx"

// -----------------------------------------------------------------

/*N*/ BOOL ScDBDocFunc::AddDBRange( const String& rName, const ScRange& rRange, BOOL bApi )
/*N*/ {
/*N*/
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   ScDBCollection* pDocColl = pDoc->GetDBCollection();
/*N*/   BOOL bUndo (pDoc->IsUndoEnabled());
/*N*/
/*N*/   ScDBCollection* pUndoColl = NULL;
/*N*/   if (bUndo)
/*N*/       pUndoColl = new ScDBCollection( *pDocColl );
/*N*/
/*N*/   ScDBData* pNew = new ScDBData( rName, rRange.aStart.Tab(),
/*N*/                                   rRange.aStart.Col(), rRange.aStart.Row(),
/*N*/                                   rRange.aEnd.Col(), rRange.aEnd.Row() );
/*N*/
/*N*/   pDoc->CompileDBFormula( TRUE );     // CreateFormulaString
/*N*/   BOOL bOk = pDocColl->Insert( pNew );
/*N*/   pDoc->CompileDBFormula( FALSE );    // CompileFormulaString
/*N*/   if (!bOk)
/*N*/   {
/*N*/       delete pNew;
/*N*/       delete pUndoColl;
/*N*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   if (bUndo)
/*N*/   {
/*N*/       ScDBCollection* pRedoColl = new ScDBCollection( *pDocColl );
/*N*/       rDocShell.GetUndoManager()->AddUndoAction(
/*N*/                       new ScUndoDBData( &rDocShell, pUndoColl, pRedoColl ) );
/*N*/   }
/*N*/
/*N*/   aModificator.SetDocumentModified();
/*N*/   SFX_APP()->Broadcast( SfxSimpleHint( SC_HINT_DBAREAS_CHANGED ) );
/*N*/   return TRUE;
/*N*/ }
/*N*/
/*N*/ BOOL ScDBDocFunc::DeleteDBRange( const String& rName, BOOL bApi )
/*N*/ {
/*N*/   BOOL bDone = FALSE;
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   ScDBCollection* pDocColl = pDoc->GetDBCollection();
/*N*/   BOOL bUndo (pDoc->IsUndoEnabled());
/*N*/
/*N*/   USHORT nPos = 0;
/*N*/   if (pDocColl->SearchName( rName, nPos ))
/*N*/   {
/*N*/       ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/       ScDBCollection* pUndoColl = NULL;
/*N*/       if (bUndo)
/*N*/           pUndoColl = new ScDBCollection( *pDocColl );
/*N*/
/*N*/       pDoc->CompileDBFormula( TRUE );     // CreateFormulaString
/*N*/       pDocColl->AtFree( nPos );
/*N*/       pDoc->CompileDBFormula( FALSE );    // CompileFormulaString
/*N*/
/*N*/       if (bUndo)
/*N*/       {
/*N*/           DBG_ASSERT(0, "STRIP"); //STRIP001 ScDBCollection* pRedoColl = new ScDBCollection( *pDocColl );
//STRIP001 /*?*/            rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                            new ScUndoDBData( &rDocShell, pUndoColl, pRedoColl ) );
/*N*/       }
/*N*/
/*N*/       aModificator.SetDocumentModified();
/*N*/       SFX_APP()->Broadcast( SfxSimpleHint( SC_HINT_DBAREAS_CHANGED ) );
/*N*/       bDone = TRUE;
/*N*/   }
/*N*/
/*N*/   return bDone;
/*N*/ }

/*N*/ BOOL ScDBDocFunc::RenameDBRange( const String& rOld, const String& rNew, BOOL bApi )
/*N*/ {
/*N*/   BOOL bDone = FALSE;
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   ScDBCollection* pDocColl = pDoc->GetDBCollection();
/*N*/   BOOL bUndo (pDoc->IsUndoEnabled());
/*N*/
/*N*/   USHORT nPos = 0;
/*N*/   USHORT nDummy = 0;
/*N*/   if ( pDocColl->SearchName( rOld, nPos ) &&
/*N*/        !pDocColl->SearchName( rNew, nDummy ) )
/*N*/   {
/*N*/       ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/       ScDBData* pData = (*pDocColl)[nPos];
/*N*/       ScDBData* pNewData = new ScDBData(*pData);
/*N*/       pNewData->SetName(rNew);
/*N*/
/*N*/       ScDBCollection* pUndoColl = new ScDBCollection( *pDocColl );
/*N*/
/*N*/       pDoc->CompileDBFormula( TRUE );             // CreateFormulaString
/*N*/       pDocColl->AtFree( nPos );
/*N*/       BOOL bInserted = pDocColl->Insert( pNewData );
/*N*/       if (!bInserted)                             // Fehler -> alten Zustand wiederherstellen
/*N*/       {
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 delete pNewData;
//STRIP001 /*?*/            pDoc->SetDBCollection( pUndoColl );     // gehoert dann dem Dokument
/*N*/       }
/*N*/       pDoc->CompileDBFormula( FALSE );            // CompileFormulaString
/*N*/
/*N*/       if (bInserted)                              // Einfuegen hat geklappt
/*N*/       {
/*N*/           if (bUndo)
/*N*/           {
/*?*/               DBG_ASSERT(0, "STRIP"); //STRIP001 ScDBCollection* pRedoColl = new ScDBCollection( *pDocColl );
//STRIP001 /*?*/                rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                                new ScUndoDBData( &rDocShell, pUndoColl, pRedoColl ) );
/*N*/           }
/*N*/           else
/*N*/               delete pUndoColl;
/*N*/
/*N*/           aModificator.SetDocumentModified();
/*N*/           SFX_APP()->Broadcast( SfxSimpleHint( SC_HINT_DBAREAS_CHANGED ) );
/*N*/           bDone = TRUE;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return bDone;
/*N*/ }

/*N*/ BOOL ScDBDocFunc::ModifyDBData( const ScDBData& rNewData, BOOL bApi )
/*N*/ {
/*N*/   BOOL bDone = FALSE;
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   ScDBCollection* pDocColl = pDoc->GetDBCollection();
/*N*/   BOOL bUndo (pDoc->IsUndoEnabled());
/*N*/
/*N*/   USHORT nPos = 0;
/*N*/   if (pDocColl->SearchName( rNewData.GetName(), nPos ))
/*N*/   {
/*N*/       ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/       ScDBData* pData = (*pDocColl)[nPos];
/*N*/
/*N*/       ScRange aOldRange, aNewRange;
/*N*/       pData->GetArea(aOldRange);
/*N*/       rNewData.GetArea(aNewRange);
/*N*/       BOOL bAreaChanged = ( aOldRange != aNewRange );     // dann muss neu compiliert werden
/*N*/
/*N*/       ScDBCollection* pUndoColl = NULL;
/*N*/       if (bUndo)
/*N*/           pUndoColl = new ScDBCollection( *pDocColl );
/*N*/
/*N*/       *pData = rNewData;
/*N*/       if (bAreaChanged)
/*N*/           pDoc->CompileDBFormula();
/*N*/
/*N*/       if (bUndo)
/*N*/       {
/*N*/           ScDBCollection* pRedoColl = new ScDBCollection( *pDocColl );
/*N*/           rDocShell.GetUndoManager()->AddUndoAction(
/*N*/                           new ScUndoDBData( &rDocShell, pUndoColl, pRedoColl ) );
/*N*/       }
/*N*/
/*N*/       aModificator.SetDocumentModified();
/*N*/       bDone = TRUE;
/*N*/   }
/*N*/
/*N*/   return bDone;
/*N*/ }

// -----------------------------------------------------------------

/*N*/ BOOL ScDBDocFunc::RepeatDB( const String& rDBName, BOOL bRecord, BOOL bApi )
/*N*/ {
/*N*/   //! auch fuer ScDBFunc::RepeatDB benutzen!
/*N*/
/*N*/   BOOL bDone = FALSE;
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   if (bRecord && !pDoc->IsUndoEnabled())
/*N*/       bRecord = FALSE;
/*N*/   ScDBCollection* pColl = pDoc->GetDBCollection();
/*N*/   USHORT nIndex;
/*N*/   if ( pColl && pColl->SearchName( rDBName, nIndex ) )
/*N*/   {
/*N*/       ScDBData* pDBData = (*pColl)[nIndex];
/*N*/
/*N*/       ScQueryParam aQueryParam;
/*N*/       pDBData->GetQueryParam( aQueryParam );
/*N*/       BOOL bQuery = aQueryParam.GetEntry(0).bDoQuery;
/*N*/
/*N*/       ScSortParam aSortParam;
/*N*/       pDBData->GetSortParam( aSortParam );
/*N*/       BOOL bSort = aSortParam.bDoSort[0];
/*N*/
/*N*/       ScSubTotalParam aSubTotalParam;
/*N*/       pDBData->GetSubTotalParam( aSubTotalParam );
/*N*/       BOOL bSubTotal = aSubTotalParam.bGroupActive[0] && !aSubTotalParam.bRemoveOnly;
/*N*/
/*N*/       if ( bQuery || bSort || bSubTotal )
/*N*/       {
/*N*/           BOOL bQuerySize = FALSE;
/*N*/           ScRange aOldQuery;
/*N*/           ScRange aNewQuery;
/*N*/           if (bQuery && !aQueryParam.bInplace)
/*N*/           {
/*N*/               ScDBData* pDest = pDoc->GetDBAtCursor( aQueryParam.nDestCol, aQueryParam.nDestRow,
/*N*/                                                       aQueryParam.nDestTab, TRUE );
/*N*/               if (pDest && pDest->IsDoSize())
/*N*/               {
/*N*/                   pDest->GetArea( aOldQuery );
/*N*/                   bQuerySize = TRUE;
/*N*/               }
/*N*/           }
/*N*/
/*N*/           USHORT nTab;
/*N*/           USHORT nStartCol;
/*N*/           USHORT nStartRow;
/*N*/           USHORT nEndCol;
/*N*/           USHORT nEndRow;
/*N*/           pDBData->GetArea( nTab, nStartCol, nStartRow, nEndCol, nEndRow );
/*N*/
/*N*/           //!     Undo nur benoetigte Daten ?
/*N*/
/*N*/           ScDocument* pUndoDoc = NULL;
/*N*/           ScOutlineTable* pUndoTab = NULL;
/*N*/           ScRangeName* pUndoRange = NULL;
/*N*/           ScDBCollection* pUndoDB = NULL;
/*N*/
/*N*/           if (bRecord)
/*N*/           {
/*N*/               USHORT nTabCount = pDoc->GetTableCount();
/*N*/               pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
/*N*/               ScOutlineTable* pTable = pDoc->GetOutlineTable( nTab );
/*N*/               if (pTable)
/*N*/               {
/*?*/                   DBG_ASSERT(0, "STRIP"); //STRIP001 pUndoTab = new ScOutlineTable( *pTable );
//STRIP001 /*?*/
//STRIP001 /*?*/                    USHORT nOutStartCol;                            // Zeilen/Spaltenstatus
//STRIP001 /*?*/                    USHORT nOutStartRow;
//STRIP001 /*?*/                    USHORT nOutEndCol;
//STRIP001 /*?*/                    USHORT nOutEndRow;
//STRIP001 /*?*/                    pTable->GetColArray()->GetRange( nOutStartCol, nOutEndCol );
//STRIP001 /*?*/                    pTable->GetRowArray()->GetRange( nOutStartRow, nOutEndRow );
//STRIP001 /*?*/
//STRIP001 /*?*/                    pUndoDoc->InitUndo( pDoc, nTab, nTab, TRUE, TRUE );
//STRIP001 /*?*/                    pDoc->CopyToDocument( nOutStartCol, 0, nTab, nOutEndCol, MAXROW, nTab, IDF_NONE, FALSE, pUndoDoc );
//STRIP001 /*?*/                    pDoc->CopyToDocument( 0, nOutStartRow, nTab, MAXCOL, nOutEndRow, nTab, IDF_NONE, FALSE, pUndoDoc );
/*N*/               }
/*N*/               else
/*N*/                   pUndoDoc->InitUndo( pDoc, nTab, nTab, FALSE, TRUE );
/*N*/
/*N*/               //  Datenbereich sichern - incl. Filter-Ergebnis
/*N*/               pDoc->CopyToDocument( 0,nStartRow,nTab, MAXCOL,nEndRow,nTab, IDF_ALL, FALSE, pUndoDoc );
/*N*/
/*N*/               //  alle Formeln wegen Referenzen
/*N*/               pDoc->CopyToDocument( 0,0,0, MAXCOL,MAXROW,nTabCount-1, IDF_FORMULA, FALSE, pUndoDoc );
/*N*/
/*N*/               //  DB- und andere Bereiche
/*N*/               ScRangeName* pDocRange = pDoc->GetRangeName();
/*N*/               if (pDocRange->GetCount())
/*N*/                   pUndoRange = new ScRangeName( *pDocRange );
/*N*/               ScDBCollection* pDocDB = pDoc->GetDBCollection();
/*N*/               if (pDocDB->GetCount())
/*N*/                   pUndoDB = new ScDBCollection( *pDocDB );
/*N*/           }
/*N*/
/*N*/           if (bSort && bSubTotal)
/*N*/           {
/*N*/               //  Sortieren ohne SubTotals
/*N*/
/*N*/               aSubTotalParam.bRemoveOnly = TRUE;      // wird unten wieder zurueckgesetzt
/*N*/               DoSubTotals( nTab, aSubTotalParam, NULL, FALSE, bApi );
/*N*/           }
/*N*/
/*N*/           if (bSort)
/*N*/           {
/*N*/               pDBData->GetSortParam( aSortParam );            // Bereich kann sich geaendert haben
/*N*/               Sort( nTab, aSortParam, FALSE, FALSE, bApi );
/*N*/           }
/*N*/           if (bQuery)
/*N*/           {
/*N*/               pDBData->GetQueryParam( aQueryParam );          // Bereich kann sich geaendert haben
/*N*/               ScRange aAdvSource;
/*N*/               if (pDBData->GetAdvancedQuerySource(aAdvSource))
/*N*/                   Query( nTab, aQueryParam, &aAdvSource, FALSE, bApi );
/*N*/               else
/*N*/                   Query( nTab, aQueryParam, NULL, FALSE, bApi );
/*N*/
/*N*/               //  bei nicht-inplace kann die Tabelle umgestellt worden sein
/*N*/ //                if ( !aQueryParam.bInplace && aQueryParam.nDestTab != nTab )
/*N*/ //                    SetTabNo( nTab );
/*N*/           }
/*N*/           if (bSubTotal)
/*N*/           {
/*N*/               pDBData->GetSubTotalParam( aSubTotalParam );    // Bereich kann sich geaendert haben
/*N*/               aSubTotalParam.bRemoveOnly = FALSE;
/*N*/               DoSubTotals( nTab, aSubTotalParam, NULL, FALSE, bApi );
/*N*/           }
/*N*/
/*N*/           if (bRecord)
/*N*/           {
/*?*/               DBG_ASSERT(0, "STRIP"); //STRIP001 USHORT nDummy;
//STRIP001 /*?*/                USHORT nNewEndRow;
//STRIP001 /*?*/                pDBData->GetArea( nDummy, nDummy,nDummy, nDummy,nNewEndRow );
//STRIP001 /*?*/
//STRIP001 /*?*/                const ScRange* pOld = NULL;
//STRIP001 /*?*/                const ScRange* pNew = NULL;
//STRIP001 /*?*/                if (bQuerySize)
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    ScDBData* pDest = pDoc->GetDBAtCursor( aQueryParam.nDestCol, aQueryParam.nDestRow,
//STRIP001 /*?*/                                                            aQueryParam.nDestTab, TRUE );
//STRIP001 /*?*/                    if (pDest)
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        pDest->GetArea( aNewQuery );
//STRIP001 /*?*/                        pOld = &aOldQuery;
//STRIP001 /*?*/                        pNew = &aNewQuery;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/                rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                    new ScUndoRepeatDB( &rDocShell, nTab,
//STRIP001 /*?*/                                            nStartCol, nStartRow, nEndCol, nEndRow,
//STRIP001 /*?*/                                            nNewEndRow,
//STRIP001 /*?*/                                            //nCurX, nCurY,
//STRIP001 /*?*/                                            nStartCol, nStartRow,
//STRIP001 /*?*/                                            pUndoDoc, pUndoTab,
//STRIP001 /*?*/                                            pUndoRange, pUndoDB,
//STRIP001 /*?*/                                            pOld, pNew ) );
/*N*/           }
/*N*/
/*N*/           rDocShell.PostPaint( 0,0,nTab, MAXCOL,MAXROW,nTab,
/*N*/                                   PAINT_GRID | PAINT_LEFT | PAINT_TOP | PAINT_SIZE );
/*N*/           bDone = TRUE;
/*N*/       }
/*N*/       else if (!bApi)     // "Keine Operationen auszufuehren"
/*N*/           rDocShell.ErrorMessage(STR_MSSG_REPEATDB_0);
/*N*/   }
/*N*/
/*N*/   return bDone;
/*N*/ }

// -----------------------------------------------------------------

/*N*/ BOOL ScDBDocFunc::Sort( USHORT nTab, const ScSortParam& rSortParam,
/*N*/                           BOOL bRecord, BOOL bPaint, BOOL bApi )
/*N*/ {
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   if (bRecord && !pDoc->IsUndoEnabled())
/*N*/       bRecord = FALSE;
/*N*/   USHORT nSrcTab = nTab;
/*N*/
/*N*/   ScDBData* pDBData = pDoc->GetDBAtArea( nTab, rSortParam.nCol1, rSortParam.nRow1,
/*N*/                                                   rSortParam.nCol2, rSortParam.nRow2 );
/*N*/   if (!pDBData)
/*N*/   {
/*N*/       DBG_ERROR( "Sort: keine DBData" );
/*N*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   ScDBData* pDestData = NULL;
/*N*/   ScRange aOldDest;
/*N*/   BOOL bCopy = !rSortParam.bInplace;
/*N*/   if ( bCopy && rSortParam.nDestCol == rSortParam.nCol1 &&
/*N*/                 rSortParam.nDestRow == rSortParam.nRow1 && rSortParam.nDestTab == nTab )
/*N*/       bCopy = FALSE;
/*N*/   ScSortParam aLocalParam( rSortParam );
/*N*/   if ( bCopy )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 aLocalParam.MoveToDest();
//STRIP001 /*?*/        nTab = rSortParam.nDestTab;
//STRIP001 /*?*/        pDestData = pDoc->GetDBAtCursor( rSortParam.nDestCol, rSortParam.nDestRow,
//STRIP001 /*?*/                                            rSortParam.nDestTab, TRUE );
//STRIP001 /*?*/        if (pDestData)
//STRIP001 /*?*/            pDestData->GetArea(aOldDest);
/*N*/   }
/*N*/
/*N*/   ScEditableTester aTester( pDoc, nTab, aLocalParam.nCol1,aLocalParam.nRow1,
/*N*/                                       aLocalParam.nCol2,aLocalParam.nRow2 );
/*N*/   if (!aTester.IsEditable())
/*N*/   {
/*N*/       if (!bApi)
/*N*/           rDocShell.ErrorMessage(aTester.GetMessageId());
/*N*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   if ( aLocalParam.bIncludePattern && pDoc->HasAttrib(
/*N*/                                       aLocalParam.nCol1, aLocalParam.nRow1, nTab,
/*N*/                                       aLocalParam.nCol2, aLocalParam.nRow2, nTab,
/*N*/                                       HASATTR_MERGED | HASATTR_OVERLAPPED ) )
/*N*/   {
/*N*/       //  Merge-Attribute wuerden beim Sortieren durcheinanderkommen
/*N*/       if (!bApi)
/*N*/           rDocShell.ErrorMessage(STR_SORT_ERR_MERGED);
/*N*/       return FALSE;
/*N*/   }
/*N*/
/*N*/
/*N*/   //      ausfuehren
/*N*/
/*N*/   WaitObject aWait( rDocShell.GetDialogParent() );
/*N*/
/*N*/   BOOL bRepeatQuery = FALSE;                          // bestehenden Filter wiederholen?
/*N*/   ScQueryParam aQueryParam;
/*N*/   pDBData->GetQueryParam( aQueryParam );
/*N*/   if ( aQueryParam.GetEntry(0).bDoQuery )
/*N*/       bRepeatQuery = TRUE;
/*N*/
/*N*/   if (bRepeatQuery && bCopy)
/*N*/   {
/*N*/       if ( aQueryParam.bInplace ||
/*N*/               aQueryParam.nDestCol != rSortParam.nDestCol ||
/*N*/               aQueryParam.nDestRow != rSortParam.nDestRow ||
/*N*/               aQueryParam.nDestTab != rSortParam.nDestTab )       // Query auf selben Zielbereich?
/*N*/           bRepeatQuery = FALSE;
/*N*/   }
/*N*/
/*N*/   if ( bRecord )
/*N*/   {
/*?*/       //  Referenzen ausserhalb des Bereichs werden nicht veraendert !
/*?*/
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 ScDocument* pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 /*?*/        //  Zeilenhoehen immer (wegen automatischer Anpassung)
//STRIP001 /*?*/        //! auf ScBlockUndo umstellen
//STRIP001 /*?*/        pUndoDoc->InitUndo( pDoc, nTab, nTab, FALSE, TRUE );
//STRIP001 /*?*/        pDoc->CopyToDocument( aLocalParam.nCol1, aLocalParam.nRow1, nTab,
//STRIP001 /*?*/                                aLocalParam.nCol2, aLocalParam.nRow2, nTab,
//STRIP001 /*?*/                                IDF_ALL, FALSE, pUndoDoc );
//STRIP001 /*?*/
//STRIP001 /*?*/        const ScRange* pR = 0;
//STRIP001 /*?*/        if (pDestData)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pDoc->CopyToDocument( aOldDest, IDF_ALL, FALSE, pUndoDoc );
//STRIP001 /*?*/            pR = &aOldDest;
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        //  Zeilenhoehen immer (wegen automatischer Anpassung)
//STRIP001 /*?*/        //! auf ScBlockUndo umstellen
//STRIP001 /*?*/ //     if (bRepeatQuery)
//STRIP001 /*?*/            pDoc->CopyToDocument( 0, aLocalParam.nRow1, nTab, MAXCOL, aLocalParam.nRow2, nTab,
//STRIP001 /*?*/                                    IDF_NONE, FALSE, pUndoDoc );
//STRIP001 /*?*/
//STRIP001 /*?*/        ScDBCollection* pUndoDB = NULL;
//STRIP001 /*?*/        ScDBCollection* pDocDB = pDoc->GetDBCollection();
//STRIP001 /*?*/        if (pDocDB->GetCount())
//STRIP001 /*?*/            pUndoDB = new ScDBCollection( *pDocDB );
//STRIP001 /*?*/
//STRIP001 /*?*/
//STRIP001 /*?*/        rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/            new ScUndoSort( &rDocShell, nTab,
//STRIP001 /*?*/                            rSortParam, bRepeatQuery, pUndoDoc, pUndoDB, pR ) );
/*N*/   }
/*N*/
/*N*/   if ( bCopy )
/*N*/   {
/*N*/       if (pDestData)
/*N*/           pDoc->DeleteAreaTab(aOldDest, IDF_CONTENTS);            // Zielbereich vorher loeschen
/*N*/
/*N*/       ScRange aSource( rSortParam.nCol1,rSortParam.nRow1,nSrcTab,
/*N*/                           rSortParam.nCol2,rSortParam.nRow2,nSrcTab );
/*N*/       ScAddress aDest( rSortParam.nDestCol, rSortParam.nDestRow, rSortParam.nDestTab );
/*N*/
/*N*/       rDocShell.GetDocFunc().MoveBlock( aSource, aDest, FALSE, FALSE, FALSE, TRUE );
/*N*/   }
/*N*/
/*N*/   // #105780# don't call ScDocument::Sort with an empty SortParam (may be empty here if bCopy is set)
/*N*/   if ( aLocalParam.bDoSort[0] )
/*N*/       pDoc->Sort( nTab, aLocalParam, bRepeatQuery );
/*N*/
/*N*/   BOOL bSave = TRUE;
/*N*/   if (bCopy)
/*N*/   {
/*N*/       ScSortParam aOldSortParam;
/*N*/       pDBData->GetSortParam( aOldSortParam );
/*N*/       if ( aOldSortParam.bDoSort[0] && aOldSortParam.bInplace )   // Inplace-Sortierung gemerkt?
/*N*/       {
/*N*/           bSave = FALSE;
/*N*/           aOldSortParam.nDestCol = rSortParam.nDestCol;
/*N*/           aOldSortParam.nDestRow = rSortParam.nDestRow;
/*N*/           aOldSortParam.nDestTab = rSortParam.nDestTab;
/*N*/           pDBData->SetSortParam( aOldSortParam );                 // dann nur DestPos merken
/*N*/       }
/*N*/   }
/*N*/   if (bSave)                                              // Parameter merken
/*N*/   {
/*N*/       pDBData->SetSortParam( rSortParam );
/*N*/       pDBData->SetHeader( rSortParam.bHasHeader );        //! ???
/*N*/       pDBData->SetByRow( rSortParam.bByRow );             //! ???
/*N*/   }
/*N*/
/*N*/   if (bCopy)                                          // neuen DB-Bereich merken
/*N*/   {
/*N*/       //  Tabelle umschalten von aussen (View)
/*N*/       //! SetCursor ??!?!
/*N*/
/*N*/       ScRange aDestPos( aLocalParam.nCol1, aLocalParam.nRow1, nTab,
/*N*/                           aLocalParam.nCol2, aLocalParam.nRow2, nTab );
/*N*/       ScDBData* pNewData;
/*N*/       if (pDestData)
/*N*/           pNewData = pDestData;               // Bereich vorhanden -> anpassen
/*N*/       else                                    // Bereich ab Cursor/Markierung wird angelegt
/*N*/           pNewData = rDocShell.GetDBData(aDestPos, SC_DB_MAKE, TRUE );
/*N*/       if (pNewData)
/*N*/       {
/*N*/           pNewData->SetArea( nTab,
/*N*/                               aLocalParam.nCol1,aLocalParam.nRow1,
/*N*/                               aLocalParam.nCol2,aLocalParam.nRow2 );
/*N*/           pNewData->SetSortParam( aLocalParam );
/*N*/           pNewData->SetHeader( aLocalParam.bHasHeader );      //! ???
/*N*/           pNewData->SetByRow( aLocalParam.bByRow );
/*N*/       }
/*N*/       else
/*N*/           DBG_ERROR("Zielbereich nicht da");
/*N*/   }
/*N*/
/*N*/   ScRange aDirtyRange( aLocalParam.nCol1, aLocalParam.nRow1, nTab,
/*N*/       aLocalParam.nCol2, aLocalParam.nRow2, nTab );
/*N*/   pDoc->SetDirty( aDirtyRange );
/*N*/
/*N*/   if (bPaint)
/*N*/   {
/*N*/       USHORT nPaint = PAINT_GRID;
/*N*/       USHORT nStartX = aLocalParam.nCol1;
/*N*/       USHORT nStartY = aLocalParam.nRow1;
/*N*/       USHORT nEndX = aLocalParam.nCol2;
/*N*/       USHORT nEndY = aLocalParam.nRow2;
/*N*/       if ( bRepeatQuery )
/*N*/       {
/*N*/           nPaint |= PAINT_LEFT;
/*N*/           nStartX = 0;
/*N*/           nEndX = MAXCOL;
/*N*/       }
/*N*/       if (pDestData)
/*N*/       {
/*N*/           if ( nEndX < aOldDest.aEnd.Col() )
/*N*/               nEndX = aOldDest.aEnd.Col();
/*N*/           if ( nEndY < aOldDest.aEnd.Row() )
/*N*/               nEndY = aOldDest.aEnd.Row();
/*N*/       }
/*N*/       rDocShell.PostPaint( nStartX, nStartY, nTab, nEndX, nEndY, nTab, nPaint );
/*N*/   }
/*N*/
/*N*/ //    AdjustRowHeight( aLocalParam.nRow1, aLocalParam.nRow2, bPaint );
/*N*/   rDocShell.AdjustRowHeight( aLocalParam.nRow1, aLocalParam.nRow2, nTab );
/*N*/
/*N*/   aModificator.SetDocumentModified();
/*N*/
/*N*/   return TRUE;
/*N*/ }

// -----------------------------------------------------------------

/*N*/ BOOL ScDBDocFunc::Query( USHORT nTab, const ScQueryParam& rQueryParam,
/*N*/                       const ScRange* pAdvSource, BOOL bRecord, BOOL bApi )
/*N*/ {
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   if (bRecord && !pDoc->IsUndoEnabled())
/*N*/       bRecord = FALSE;
/*N*/   ScDBData* pDBData = pDoc->GetDBAtArea( nTab, rQueryParam.nCol1, rQueryParam.nRow1,
/*N*/                                                   rQueryParam.nCol2, rQueryParam.nRow2 );
/*N*/   if (!pDBData)
/*N*/   {
/*N*/       DBG_ERROR( "Query: keine DBData" );
/*N*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   //  Wechsel von Inplace auf nicht-Inplace, dann erst Inplace aufheben:
/*N*/   //  (nur, wenn im Dialog "Persistent" ausgewaehlt ist)
/*N*/
/*N*/   if ( !rQueryParam.bInplace && pDBData->HasQueryParam() && rQueryParam.bDestPers )
/*N*/   {
/*N*/       ScQueryParam aOldQuery;
/*N*/       pDBData->GetQueryParam(aOldQuery);
/*N*/       if (aOldQuery.bInplace)
/*N*/       {
/*N*/           //  alte Filterung aufheben
/*N*/
/*N*/           USHORT nEC = aOldQuery.GetEntryCount();
/*N*/           for (USHORT i=0; i<nEC; i++)
/*N*/               aOldQuery.GetEntry(i).bDoQuery = FALSE;
/*N*/           aOldQuery.bDuplicate = TRUE;
/*N*/           Query( nTab, aOldQuery, NULL, bRecord, bApi );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   ScQueryParam aLocalParam( rQueryParam );        // fuer Paint / Zielbereich
/*N*/   BOOL bCopy = !rQueryParam.bInplace;             // kopiert wird in Table::Query
/*N*/   ScDBData* pDestData = NULL;                     // Bereich, in den kopiert wird
/*N*/   BOOL bDoSize = FALSE;                           // Zielgroesse anpassen (einf./loeschen)
/*N*/   USHORT nFormulaCols = 0;                        // nur bei bDoSize
/*N*/   BOOL bKeepFmt = FALSE;
/*N*/   ScRange aOldDest;
/*N*/   ScRange aDestTotal;
/*N*/   if ( bCopy && rQueryParam.nDestCol == rQueryParam.nCol1 &&
/*N*/                 rQueryParam.nDestRow == rQueryParam.nRow1 && rQueryParam.nDestTab == nTab )
/*N*/       bCopy = FALSE;
/*N*/   USHORT nDestTab = nTab;
/*N*/   if ( bCopy )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 aLocalParam.MoveToDest();
//STRIP001 /*?*/        nDestTab = rQueryParam.nDestTab;
//STRIP001 /*?*/
//STRIP001 /*?*/        ScEditableTester aTester( pDoc, nDestTab, aLocalParam.nCol1,aLocalParam.nRow1,
//STRIP001 /*?*/                                                aLocalParam.nCol2,aLocalParam.nRow2);
//STRIP001 /*?*/        if (!aTester.IsEditable())
//STRIP001 /*?*/        {
//STRIP001 /*?*/            if (!bApi)
//STRIP001 /*?*/                rDocShell.ErrorMessage(aTester.GetMessageId());
//STRIP001 /*?*/            return FALSE;
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        pDestData = pDoc->GetDBAtCursor( rQueryParam.nDestCol, rQueryParam.nDestRow,
//STRIP001 /*?*/                                            rQueryParam.nDestTab, TRUE );
//STRIP001 /*?*/        if (pDestData)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pDestData->GetArea( aOldDest );
//STRIP001 /*?*/            aDestTotal=ScRange( rQueryParam.nDestCol,
//STRIP001 /*?*/                                rQueryParam.nDestRow,
//STRIP001 /*?*/                                nDestTab,
//STRIP001 /*?*/                                rQueryParam.nDestCol + rQueryParam.nCol2 - rQueryParam.nCol1,
//STRIP001 /*?*/                                rQueryParam.nDestRow + rQueryParam.nRow2 - rQueryParam.nRow1,
//STRIP001 /*?*/                                nDestTab );
//STRIP001 /*?*/
//STRIP001 /*?*/            bDoSize = pDestData->IsDoSize();
//STRIP001 /*?*/            //  Test, ob Formeln aufgefuellt werden muessen (nFormulaCols):
//STRIP001 /*?*/            if ( bDoSize && aOldDest.aEnd.Col() == aDestTotal.aEnd.Col() )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                USHORT nTestCol = aOldDest.aEnd.Col() + 1;      // neben dem Bereich
//STRIP001 /*?*/                USHORT nTestRow = rQueryParam.nDestRow +
//STRIP001 /*?*/                                    ( aLocalParam.bHasHeader ? 1 : 0 );
//STRIP001 /*?*/                while ( nTestCol <= MAXCOL &&
//STRIP001 /*?*/                        pDoc->GetCellType(ScAddress( nTestCol, nTestRow, nTab )) == CELLTYPE_FORMULA )
//STRIP001 /*?*/                    ++nTestCol, ++nFormulaCols;
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            bKeepFmt = pDestData->IsKeepFmt();
//STRIP001 /*?*/            if ( bDoSize && !pDoc->CanFitBlock( aOldDest, aDestTotal ) )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                if (!bApi)
//STRIP001 /*?*/                    rDocShell.ErrorMessage(STR_MSSG_DOSUBTOTALS_2);     // kann keine Zeilen einfuegen
//STRIP001 /*?*/                return FALSE;
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
/*N*/   }
/*N*/
/*N*/   //      ausfuehren
/*N*/
/*N*/   WaitObject aWait( rDocShell.GetDialogParent() );
/*N*/
/*N*/   BOOL bKeepSub = FALSE;                          // bestehende Teilergebnisse wiederholen?
/*N*/   ScSubTotalParam aSubTotalParam;
/*N*/   if (rQueryParam.GetEntry(0).bDoQuery)           // nicht beim Aufheben
/*N*/   {
/*N*/       pDBData->GetSubTotalParam( aSubTotalParam );    // Teilergebnisse vorhanden?
/*N*/
/*N*/       if ( aSubTotalParam.bGroupActive[0] && !aSubTotalParam.bRemoveOnly )
/*N*/           bKeepSub = TRUE;
/*N*/   }
/*N*/
/*N*/   if ( bRecord )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 const ScRange* pOld = 0;
//STRIP001 /*?*/        ScDocument* pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 /*?*/        if (bCopy)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pUndoDoc->InitUndo( pDoc, nDestTab, nDestTab, FALSE, TRUE );
//STRIP001 /*?*/            pDoc->CopyToDocument( aLocalParam.nCol1, aLocalParam.nRow1, nDestTab,
//STRIP001 /*?*/                                    aLocalParam.nCol2, aLocalParam.nRow2, nDestTab,
//STRIP001 /*?*/                                    IDF_ALL, FALSE, pUndoDoc );
//STRIP001 /*?*/            //  Attribute sichern, falls beim Filtern mitkopiert
//STRIP001 /*?*/
//STRIP001 /*?*/            if (pDestData)
//STRIP001 /*?*/            {
//STRIP001 /*?*/                pDoc->CopyToDocument( aOldDest, IDF_ALL, FALSE, pUndoDoc );
//STRIP001 /*?*/                pOld = &aOldDest;
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
//STRIP001 /*?*/        else
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pUndoDoc->InitUndo( pDoc, nTab, nTab, FALSE, TRUE );
//STRIP001 /*?*/            pDoc->CopyToDocument( 0, rQueryParam.nRow1, nTab, MAXCOL, rQueryParam.nRow2, nTab,
//STRIP001 /*?*/                                        IDF_NONE, FALSE, pUndoDoc );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        ScDBCollection* pUndoDB = NULL;
//STRIP001 /*?*/        ScDBCollection* pDocDB = pDoc->GetDBCollection();
//STRIP001 /*?*/        if (pDocDB->GetCount())
//STRIP001 /*?*/            pUndoDB = new ScDBCollection( *pDocDB );
//STRIP001 /*?*/
//STRIP001 /*?*/        rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                    new ScUndoQuery( &rDocShell, nTab, rQueryParam, pUndoDoc, pUndoDB,
//STRIP001 /*?*/                                        pOld, bDoSize, pAdvSource ) );
/*N*/   }
/*N*/
/*N*/   ScDocument* pAttribDoc = NULL;
/*N*/   ScRange aAttribRange;
/*N*/   if (pDestData)                                      // Zielbereich loeschen
/*N*/   {
/*N*/       if ( bKeepFmt )
/*N*/       {
/*N*/           //  kleinere der End-Spalten, Header+1 Zeile
/*N*/           aAttribRange = aOldDest;
/*N*/           if ( aAttribRange.aEnd.Col() > aDestTotal.aEnd.Col() )
/*N*/               aAttribRange.aEnd.SetCol( aDestTotal.aEnd.Col() );
/*N*/           aAttribRange.aEnd.SetRow( aAttribRange.aStart.Row() +
/*N*/                                       ( aLocalParam.bHasHeader ? 1 : 0 ) );
/*N*/
/*N*/           //  auch fuer aufgefuellte Formeln
/*N*/           aAttribRange.aEnd.SetCol( aAttribRange.aEnd.Col() + nFormulaCols );
/*N*/
/*N*/           pAttribDoc = new ScDocument( SCDOCMODE_UNDO );
/*N*/           pAttribDoc->InitUndo( pDoc, nDestTab, nDestTab, FALSE, TRUE );
/*N*/           pDoc->CopyToDocument( aAttribRange, IDF_ATTRIB, FALSE, pAttribDoc );
/*N*/       }
/*N*/
/*N*/       if ( bDoSize )
/*N*/           pDoc->FitBlock( aOldDest, aDestTotal );
/*N*/       else
/*N*/           pDoc->DeleteAreaTab(aOldDest, IDF_ALL);         // einfach loeschen
/*N*/   }
/*N*/
/*N*/   //  Filtern am Dokument ausfuehren
/*N*/   USHORT nCount = pDoc->Query( nTab, rQueryParam, bKeepSub );
/*N*/   if (bCopy)
/*N*/   {
/*N*/       aLocalParam.nRow2 = aLocalParam.nRow1 + nCount;
/*N*/       if (!aLocalParam.bHasHeader && nCount)
/*N*/           --aLocalParam.nRow2;
/*N*/
/*N*/       if ( bDoSize )
/*N*/       {
/*N*/           //  auf wirklichen Ergebnis-Bereich anpassen
/*N*/           //  (das hier ist immer eine Verkleinerung)
/*N*/
/*N*/           ScRange aNewDest( aLocalParam.nCol1, aLocalParam.nRow1, nDestTab,
/*N*/                               aLocalParam.nCol2, aLocalParam.nRow2, nDestTab );
/*N*/           pDoc->FitBlock( aDestTotal, aNewDest, FALSE );      // FALSE - nicht loeschen
/*N*/
/*N*/           if ( nFormulaCols )
/*N*/           {
/*N*/               //  Formeln ausfuellen
/*N*/               //! Undo (Query und Repeat) !!!
/*N*/
/*N*/               ScRange aNewForm( aLocalParam.nCol2+1, aLocalParam.nRow1, nDestTab,
/*N*/                                 aLocalParam.nCol2+nFormulaCols, aLocalParam.nRow2, nDestTab );
/*N*/               ScRange aOldForm = aNewForm;
/*N*/               aOldForm.aEnd.SetRow( aOldDest.aEnd.Row() );
/*N*/               pDoc->FitBlock( aOldForm, aNewForm, FALSE );
/*N*/
/*N*/               ScMarkData aMark;
/*N*/               aMark.SelectOneTable(nDestTab);
/*N*/               USHORT nFStartY = aLocalParam.nRow1 + ( aLocalParam.bHasHeader ? 1 : 0 );
/*N*/               pDoc->Fill( aLocalParam.nCol2+1, nFStartY,
/*N*/                           aLocalParam.nCol2+nFormulaCols, nFStartY, aMark,
/*N*/                           aLocalParam.nRow2 - nFStartY,
/*N*/                           FILL_TO_BOTTOM, FILL_SIMPLE );
/*N*/           }
/*N*/       }
/*N*/
/*N*/       if ( pAttribDoc )       // gemerkte Attribute zurueckkopieren
/*N*/       {
/*N*/           //  Header
/*N*/           if (aLocalParam.bHasHeader)
/*N*/           {
/*N*/               ScRange aHdrRange = aAttribRange;
/*N*/               aHdrRange.aEnd.SetRow( aHdrRange.aStart.Row() );
/*N*/               pAttribDoc->CopyToDocument( aHdrRange, IDF_ATTRIB, FALSE, pDoc );
/*N*/           }
/*N*/
/*N*/           //  Daten
/*N*/           USHORT nAttrEndCol = aAttribRange.aEnd.Col();
/*N*/           USHORT nAttrRow = aAttribRange.aStart.Row() + ( aLocalParam.bHasHeader ? 1 : 0 );
/*N*/           for (USHORT nCol = aAttribRange.aStart.Col(); nCol<=nAttrEndCol; nCol++)
/*N*/           {
/*N*/               const ScPatternAttr* pSrcPattern = pAttribDoc->GetPattern(
/*N*/                                                   nCol, nAttrRow, nDestTab );
/*N*/               DBG_ASSERT(pSrcPattern,"Pattern ist 0");
/*N*/               if (pSrcPattern)
/*N*/                   pDoc->ApplyPatternAreaTab( nCol, nAttrRow, nCol, aLocalParam.nRow2,
/*N*/                                                   nDestTab, *pSrcPattern );
/*N*/               const ScStyleSheet* pStyle = pSrcPattern->GetStyleSheet();
/*N*/               if (pStyle)
/*N*/                   pDoc->ApplyStyleAreaTab( nCol, nAttrRow, nCol, aLocalParam.nRow2,
/*N*/                                                   nDestTab, *pStyle );
/*N*/           }
/*N*/
/*N*/           delete pAttribDoc;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   //  speichern: Inplace immer, sonst je nach Einstellung
/*N*/   //             alter Inplace-Filter ist ggf. schon aufgehoben
/*N*/
/*N*/   BOOL bSave = rQueryParam.bInplace || rQueryParam.bDestPers;
/*N*/   if (bSave)                                                  // merken
/*N*/   {
/*N*/       pDBData->SetQueryParam( rQueryParam );
/*N*/       pDBData->SetHeader( rQueryParam.bHasHeader );       //! ???
/*N*/       pDBData->SetAdvancedQuerySource( pAdvSource );      // after SetQueryParam
/*N*/   }
/*N*/
/*N*/   if (bCopy)                                              // neuen DB-Bereich merken
/*N*/   {
/*N*/       //  selektieren wird hinterher von aussen (dbfunc)
/*N*/       //  momentan ueber DB-Bereich an der Zielposition, darum muss dort
/*N*/       //  auf jeden Fall ein Bereich angelegt werden.
/*N*/
/*N*/       ScDBData* pNewData;
/*N*/       if (pDestData)
/*N*/           pNewData = pDestData;               // Bereich vorhanden -> anpassen (immer!)
/*N*/       else                                    // Bereich anlegen
/*N*/           pNewData = rDocShell.GetDBData(
/*N*/                           ScRange( aLocalParam.nCol1, aLocalParam.nRow1, nDestTab,
/*N*/                                    aLocalParam.nCol2, aLocalParam.nRow2, nDestTab ),
/*N*/                           SC_DB_MAKE, TRUE );
/*N*/
/*N*/       if (pNewData)
/*N*/       {
/*N*/           pNewData->SetArea( nDestTab, aLocalParam.nCol1, aLocalParam.nRow1,
/*N*/                                           aLocalParam.nCol2, aLocalParam.nRow2 );
/*N*/
/*N*/           //  Query-Param wird am Ziel nicht mehr eingestellt, fuehrt nur zu Verwirrung
/*N*/           //  und Verwechslung mit dem Query-Param am Quellbereich (#37187#)
/*N*/       }
/*N*/       else
/*N*/           DBG_ERROR("Zielbereich nicht da");
/*N*/   }
/*N*/
/*N*/   if (!bCopy)
/*N*/       pDoc->UpdatePageBreaks( nTab );
/*N*/
/*N*/   ScRange aDirtyRange( aLocalParam.nCol1, aLocalParam.nRow1, nDestTab,
/*N*/       aLocalParam.nCol2, aLocalParam.nRow2, nDestTab );
/*N*/   pDoc->SetDirty( aDirtyRange );
/*N*/
/*N*/   if (bCopy)
/*N*/   {
/*N*/       USHORT nEndX = aLocalParam.nCol2;
/*N*/       USHORT nEndY = aLocalParam.nRow2;
/*N*/       if (pDestData)
/*N*/       {
/*N*/           if ( aOldDest.aEnd.Col() > nEndX )
/*N*/               nEndX = aOldDest.aEnd.Col();
/*N*/           if ( aOldDest.aEnd.Row() > nEndY )
/*N*/               nEndY = aOldDest.aEnd.Row();
/*N*/       }
/*N*/       if (bDoSize)
/*N*/           nEndY = MAXROW;
/*N*/       rDocShell.PostPaint( aLocalParam.nCol1, aLocalParam.nRow1, nDestTab,
/*N*/                                   nEndX, nEndY, nDestTab, PAINT_GRID );
/*N*/   }
/*N*/   else
/*N*/       rDocShell.PostPaint( 0, rQueryParam.nRow1, nTab, MAXCOL, MAXROW, nTab,
/*N*/                                               PAINT_GRID | PAINT_LEFT );
/*N*/   aModificator.SetDocumentModified();
/*N*/
/*N*/   return TRUE;
/*N*/ }

// -----------------------------------------------------------------

/*N*/ BOOL ScDBDocFunc::DoSubTotals( USHORT nTab, const ScSubTotalParam& rParam,
/*N*/                               const ScSortParam* pForceNewSort, BOOL bRecord, BOOL bApi )
/*N*/ {
/*N*/   //! auch fuer ScDBFunc::DoSubTotals benutzen!
/*N*/   //  dann bleibt aussen:
/*N*/   //  - neuen Bereich (aus DBData) markieren
/*N*/   //  - SelectionChanged (?)
/*N*/
/*N*/   BOOL bDo = !rParam.bRemoveOnly;                         // FALSE = nur loeschen
/*N*/   BOOL bRet = FALSE;
/*N*/
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   if (bRecord && !pDoc->IsUndoEnabled())
/*N*/       bRecord = FALSE;
/*N*/   ScDBData* pDBData = pDoc->GetDBAtArea( nTab, rParam.nCol1, rParam.nRow1,
/*N*/                                               rParam.nCol2, rParam.nRow2 );
/*N*/   if (!pDBData)
/*N*/   {
/*N*/       DBG_ERROR( "SubTotals: keine DBData" );
/*N*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   ScEditableTester aTester( pDoc, nTab, 0,rParam.nRow1+1, MAXCOL,MAXROW );
/*N*/   if (!aTester.IsEditable())
/*N*/   {
/*N*/       if (!bApi)
/*N*/           rDocShell.ErrorMessage(aTester.GetMessageId());
/*N*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   if (pDoc->HasAttrib( rParam.nCol1, rParam.nRow1+1, nTab,
/*N*/                        rParam.nCol2, rParam.nRow2, nTab, HASATTR_MERGED | HASATTR_OVERLAPPED ))
/*N*/   {
/*N*/       if (!bApi)
/*N*/           rDocShell.ErrorMessage(STR_MSSG_INSERTCELLS_0); // nicht in zusammengefasste einfuegen
/*N*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   BOOL bOk = TRUE;
/*N*/   BOOL bDelete = FALSE;
/*N*/   if (rParam.bReplace)
/*?*/       {DBG_ASSERT(0, "STRIP"); }//STRIP001 if (pDoc->TestRemoveSubTotals( nTab, rParam ))
//STRIP001 /*?*/        {
//STRIP001 /*?*/            bDelete = TRUE;
//STRIP001 /*?*/            bOk = ( MessBox( rDocShell.GetDialogParent(), WinBits(WB_YES_NO | WB_DEF_YES),
//STRIP001 /*?*/                // "StarCalc" "Daten loeschen?"
//STRIP001 /*?*/                ScGlobal::GetRscString( STR_MSSG_DOSUBTOTALS_0 ),
//STRIP001 /*?*/                ScGlobal::GetRscString( STR_MSSG_DOSUBTOTALS_1 ) ).Execute()
//STRIP001 /*?*/                == RET_YES );
//STRIP001 /*?*/        }
/*N*/
/*N*/   if (bOk)
/*N*/   {
/*N*/       WaitObject aWait( rDocShell.GetDialogParent() );
/*N*/       ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/       ScSubTotalParam aNewParam( rParam );        // Bereichsende wird veraendert
/*N*/       ScDocument*     pUndoDoc = NULL;
/*N*/       ScOutlineTable* pUndoTab = NULL;
/*N*/       ScRangeName*    pUndoRange = NULL;
/*N*/       ScDBCollection* pUndoDB = NULL;
/*N*/       USHORT          nTabCount = 0;              // fuer Referenz-Undo
/*N*/
/*N*/       if (bRecord)                                        // alte Daten sichern
/*N*/       {
/*N*/           BOOL bOldFilter = bDo && rParam.bDoSort;
/*N*/
/*N*/           nTabCount = pDoc->GetTableCount();
/*N*/           pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
/*N*/           ScOutlineTable* pTable = pDoc->GetOutlineTable( nTab );
/*N*/           if (pTable)
/*N*/           {
/*?*/               DBG_ASSERT(0, "STRIP"); //STRIP001 pUndoTab = new ScOutlineTable( *pTable );
//STRIP001 /*?*/
//STRIP001 /*?*/                USHORT nOutStartCol;                            // Zeilen/Spaltenstatus
//STRIP001 /*?*/                USHORT nOutStartRow;
//STRIP001 /*?*/                USHORT nOutEndCol;
//STRIP001 /*?*/                USHORT nOutEndRow;
//STRIP001 /*?*/                pTable->GetColArray()->GetRange( nOutStartCol, nOutEndCol );
//STRIP001 /*?*/                pTable->GetRowArray()->GetRange( nOutStartRow, nOutEndRow );
//STRIP001 /*?*/
//STRIP001 /*?*/                pUndoDoc->InitUndo( pDoc, nTab, nTab, TRUE, TRUE );
//STRIP001 /*?*/                pDoc->CopyToDocument( nOutStartCol, 0, nTab, nOutEndCol, MAXROW, nTab, IDF_NONE, FALSE, pUndoDoc );
//STRIP001 /*?*/                pDoc->CopyToDocument( 0, nOutStartRow, nTab, MAXCOL, nOutEndRow, nTab, IDF_NONE, FALSE, pUndoDoc );
/*N*/           }
/*N*/           else
/*N*/               pUndoDoc->InitUndo( pDoc, nTab, nTab, FALSE, bOldFilter );
/*N*/
/*N*/           //  Datenbereich sichern - incl. Filter-Ergebnis
/*N*/           pDoc->CopyToDocument( 0,rParam.nRow1+1,nTab, MAXCOL,rParam.nRow2,nTab,
/*N*/                                   IDF_ALL, FALSE, pUndoDoc );
/*N*/
/*N*/           //  alle Formeln wegen Referenzen
/*N*/           pDoc->CopyToDocument( 0,0,0, MAXCOL,MAXROW,nTabCount-1,
/*N*/                                       IDF_FORMULA, FALSE, pUndoDoc );
/*N*/
/*N*/           //  DB- und andere Bereiche
/*N*/           ScRangeName* pDocRange = pDoc->GetRangeName();
/*N*/           if (pDocRange->GetCount())
/*N*/               pUndoRange = new ScRangeName( *pDocRange );
/*N*/           ScDBCollection* pDocDB = pDoc->GetDBCollection();
/*N*/           if (pDocDB->GetCount())
/*N*/               pUndoDB = new ScDBCollection( *pDocDB );
/*N*/       }
/*N*/
/*N*/ //        pDoc->SetOutlineTable( nTab, NULL );
/*N*/       ScOutlineTable* pOut = pDoc->GetOutlineTable( nTab );
/*N*/       if (pOut)
/*?*/       {   DBG_ASSERT(0, "STRIP"); }//STRIP001 pOut->GetRowArray()->RemoveAll();       // nur Zeilen-Outlines loeschen
/*N*/
/*N*/       if (rParam.bReplace)
/*?*/           {DBG_ASSERT(0, "STRIP");} //STRIP001 pDoc->RemoveSubTotals( nTab, aNewParam );
/*N*/       BOOL bSuccess = TRUE;
/*N*/       if (bDo)
/*N*/       {
/*?*/           // Sortieren
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 if ( rParam.bDoSort || pForceNewSort )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                pDBData->SetArea( nTab, aNewParam.nCol1,aNewParam.nRow1, aNewParam.nCol2,aNewParam.nRow2 );
//STRIP001 /*?*/
//STRIP001 /*?*/                //  Teilergebnis-Felder vor die Sortierung setzen
//STRIP001 /*?*/                //  (doppelte werden weggelassen, kann darum auch wieder aufgerufen werden)
//STRIP001 /*?*/
//STRIP001 /*?*/                ScSortParam aOldSort;
//STRIP001 /*?*/                pDBData->GetSortParam( aOldSort );
//STRIP001 /*?*/                ScSortParam aSortParam( aNewParam, pForceNewSort ? *pForceNewSort : aOldSort );
//STRIP001 /*?*/                Sort( nTab, aSortParam, FALSE, FALSE, bApi );
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            bSuccess = pDoc->DoSubTotals( nTab, aNewParam );
/*N*/       }
/*N*/       ScRange aDirtyRange( aNewParam.nCol1, aNewParam.nRow1, nTab,
/*N*/           aNewParam.nCol2, aNewParam.nRow2, nTab );
/*N*/       pDoc->SetDirty( aDirtyRange );
/*N*/
/*N*/       if (bRecord)
/*N*/       {
/*N*/ //            ScDBData* pUndoDBData = pDBData ? new ScDBData( *pDBData ) : NULL;
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                new ScUndoSubTotals( &rDocShell, nTab,
//STRIP001 /*?*/                                        rParam, aNewParam.nRow2,
//STRIP001 /*?*/                                        pUndoDoc, pUndoTab, // pUndoDBData,
//STRIP001 /*?*/                                        pUndoRange, pUndoDB ) );
/*N*/       }
/*N*/
/*N*/       if (!bSuccess)
/*N*/       {
/*N*/           // "Kann keine Zeilen einfuegen"
/*N*/           if (!bApi)
/*N*/               rDocShell.ErrorMessage(STR_MSSG_DOSUBTOTALS_2);
/*N*/       }
/*N*/
/*N*/                                                   // merken
/*N*/       pDBData->SetSubTotalParam( aNewParam );
/*N*/       pDBData->SetArea( nTab, aNewParam.nCol1,aNewParam.nRow1, aNewParam.nCol2,aNewParam.nRow2 );
/*N*/       pDoc->CompileDBFormula();
/*N*/
/*N*/       rDocShell.PostPaint( 0,0,nTab, MAXCOL,MAXROW,nTab,
/*N*/                                               PAINT_GRID | PAINT_LEFT | PAINT_TOP | PAINT_SIZE );
/*N*/       aModificator.SetDocumentModified();
/*N*/
/*N*/       bRet = bSuccess;
/*N*/   }
/*N*/   return bRet;
/*N*/ }

//==================================================================

/*N*/ BOOL lcl_EmptyExcept( ScDocument* pDoc, const ScRange& rRange, const ScRange& rExcept )
/*N*/ {
/*N*/   ScCellIterator aIter( pDoc, rRange );
/*N*/   ScBaseCell* pCell = aIter.GetFirst();
/*N*/   while (pCell)
/*N*/   {
/*N*/       if ( pCell->GetCellType() != CELLTYPE_NOTE || pCell->GetNotePtr() )     // real content?
/*N*/       {
/*N*/           if ( !rExcept.In( ScAddress( aIter.GetCol(), aIter.GetRow(), aIter.GetTab() ) ) )
/*N*/               return FALSE;       // cell found
/*N*/       }
/*N*/       pCell = aIter.GetNext();
/*N*/   }
/*N*/
/*N*/   return TRUE;        // nothing found - empty
/*N*/ }

/*N*/ BOOL ScDBDocFunc::DataPilotUpdate( ScDPObject* pOldObj, const ScDPObject* pNewObj,
/*N*/                                       BOOL bRecord, BOOL bApi )
/*N*/ {
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/   WaitObject aWait( rDocShell.GetDialogParent() );
/*N*/
/*N*/   BOOL bDone = FALSE;
/*N*/   BOOL bUndoSelf = FALSE;
/*N*/   USHORT nErrId = 0;
/*N*/
/*N*/   ScDocument* pOldUndoDoc = NULL;
/*N*/   ScDocument* pNewUndoDoc = NULL;
/*N*/   ScDPObject* pUndoDPObj = NULL;
/*N*/   if ( bRecord && pOldObj )
/*N*/       pUndoDPObj = new ScDPObject( *pOldObj );    // copy old settings for undo
/*N*/
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   if (bRecord && !pDoc->IsUndoEnabled())
/*N*/       bRecord = FALSE;
/*N*/   if ( !rDocShell.IsEditable() || pDoc->GetChangeTrack() )
/*N*/   {
/*N*/       //  not recorded -> disallow
/*N*/       //! different error messages?
/*N*/
/*N*/       nErrId = STR_PROTECTIONERR;
/*N*/   }
/*N*/   if ( pOldObj && !nErrId )
/*N*/   {
/*N*/       ScRange aOldOut = pOldObj->GetOutRange();
/*N*/       ScEditableTester aTester( pDoc, aOldOut );
/*N*/       if ( !aTester.IsEditable() )
/*N*/           nErrId = aTester.GetMessageId();
/*N*/   }
/*N*/   if ( pNewObj && !nErrId )
/*N*/   {
/*N*/       //  at least one cell at the output position must be editable
/*N*/       //  -> check in advance
/*N*/       //  (start of output range in pNewObj is valid)
/*N*/
/*N*/       ScRange aNewStart( pNewObj->GetOutRange().aStart );
/*N*/       ScEditableTester aTester( pDoc, aNewStart );
/*N*/       if ( !aTester.IsEditable() )
/*N*/           nErrId = aTester.GetMessageId();
/*N*/   }
/*N*/
/*N*/   ScDPObject* pDestObj = NULL;
/*N*/   if ( !nErrId )
/*N*/   {
/*N*/       if ( pOldObj && !pNewObj )
/*N*/       {
/*N*/           //  delete table
/*N*/
/*N*/           ScRange aRange = pOldObj->GetOutRange();
/*N*/           USHORT nTab = aRange.aStart.Tab();
/*N*/
/*N*/           if ( bRecord )
/*N*/           {
/*N*/               pOldUndoDoc = new ScDocument( SCDOCMODE_UNDO );
/*N*/               pOldUndoDoc->InitUndo( pDoc, nTab, nTab );
/*N*/               pDoc->CopyToDocument( aRange, IDF_ALL, FALSE, pOldUndoDoc );
/*N*/           }
/*N*/
/*N*/           pDoc->DeleteAreaTab( aRange.aStart.Col(), aRange.aStart.Row(),
/*N*/                                aRange.aEnd.Col(),   aRange.aEnd.Row(),
/*N*/                                nTab, IDF_ALL );
/*N*/
/*N*/           pDoc->GetDPCollection()->Free( pOldObj );   // object is deleted here
/*N*/
/*N*/           rDocShell.PostPaintGridAll();   //! only necessary parts
/*N*/           rDocShell.PostPaint( aRange.aStart.Col(), aRange.aStart.Row(), nTab,
/*N*/                                aRange.aEnd.Col(),   aRange.aEnd.Row(),   nTab,
/*N*/                                PAINT_GRID );
/*N*/           bDone = TRUE;
/*N*/       }
/*N*/       else if ( pNewObj )
/*N*/       {
/*N*/           if ( pOldObj )
/*N*/           {
/*N*/               if ( bRecord )
/*N*/               {
/*N*/                   ScRange aRange = pOldObj->GetOutRange();
/*N*/                   USHORT nTab = aRange.aStart.Tab();
/*N*/                   pOldUndoDoc = new ScDocument( SCDOCMODE_UNDO );
/*N*/                   pOldUndoDoc->InitUndo( pDoc, nTab, nTab );
/*N*/                   pDoc->CopyToDocument( aRange, IDF_ALL, FALSE, pOldUndoDoc );
/*N*/               }
/*N*/
/*N*/               if ( pNewObj == pOldObj )
/*N*/               {
/*N*/                   //  refresh only - no settings modified
/*N*/               }
/*N*/               else
/*N*/               {
/*?*/                   DBG_ASSERT(0, "STRIP"); //STRIP001 pNewObj->WriteSourceDataTo( *pOldObj );      // copy source data
//STRIP001 /*?*/
//STRIP001 /*?*/                    ScDPSaveData* pData = pNewObj->GetSaveData();
//STRIP001 /*?*/                    DBG_ASSERT( pData, "no SaveData from living DPObject" );
//STRIP001 /*?*/                    if ( pData )
//STRIP001 /*?*/                        pOldObj->SetSaveData( *pData );     // copy SaveData
/*N*/               }
/*N*/
/*N*/               pDestObj = pOldObj;
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               //  output range must be set at pNewObj
/*N*/
/*N*/               pDestObj = new ScDPObject( *pNewObj );
/*N*/               pDestObj->SetAlive(TRUE);
/*N*/               if ( !pDoc->GetDPCollection()->Insert(pDestObj) )
/*N*/               {
/*N*/                   DBG_ERROR("cannot insert DPObject");
/*N*/                   DELETEZ( pDestObj );
/*N*/               }
/*N*/           }
/*N*/           if ( pDestObj )
/*N*/           {
/*N*/               // #78541# create new database connection for "refresh"
/*N*/               // (and re-read column entry collections)
/*N*/               // so all changes take effect
/*?*/               DBG_ASSERT(0, "STRIP"); //STRIP001 if ( pNewObj == pOldObj && pDestObj->IsImportData() )
//STRIP001 /*?*/                    pDestObj->InvalidateSource();
//STRIP001 /*?*/
//STRIP001 /*?*/                pDestObj->InvalidateData();             // before getting the new output area
//STRIP001 /*?*/
//STRIP001 /*?*/                //  make sure the table has a name (not set by dialog)
//STRIP001 /*?*/                if ( !pDestObj->GetName().Len() )
//STRIP001 /*?*/                    pDestObj->SetName( pDoc->GetDPCollection()->CreateNewName() );
//STRIP001 /*?*/
//STRIP001 /*?*/                BOOL bOverflow = FALSE;
//STRIP001 /*?*/                ScRange aNewOut = pDestObj->GetNewOutputRange( bOverflow );
//STRIP001 /*?*/                if ( bOverflow )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    //  like with STR_PROTECTIONERR, use undo to reverse everything
//STRIP001 /*?*/                    DBG_ASSERT( bRecord, "DataPilotUpdate: can't undo" );
//STRIP001 /*?*/                    bUndoSelf = TRUE;
//STRIP001 /*?*/                    nErrId = STR_PIVOT_ERROR;
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    ScEditableTester aTester( pDoc, aNewOut );
//STRIP001 /*?*/                    if ( !aTester.IsEditable() )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        //  destination area isn't editable
//STRIP001 /*?*/                        //! reverse everything done so far, don't proceed
//STRIP001 /*?*/
//STRIP001 /*?*/                        //  quick solution: proceed to end, use undo action
//STRIP001 /*?*/                        //  to reverse everything:
//STRIP001 /*?*/                        DBG_ASSERT( bRecord, "DataPilotUpdate: can't undo" );
//STRIP001 /*?*/                        bUndoSelf = TRUE;
//STRIP001 /*?*/                        nErrId = aTester.GetMessageId();
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/                //  test if new output area is empty except for old area
//STRIP001 /*?*/                if ( !bApi )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    BOOL bEmpty;
//STRIP001 /*?*/                    if ( pOldObj )  // OutRange of pOldObj (pDestObj) is still old area
//STRIP001 /*?*/                        bEmpty = lcl_EmptyExcept( pDoc, aNewOut, pOldObj->GetOutRange() );
//STRIP001 /*?*/                    else
//STRIP001 /*?*/                        bEmpty = pDoc->IsBlockEmpty( aNewOut.aStart.Tab(),
//STRIP001 /*?*/                                            aNewOut.aStart.Col(), aNewOut.aStart.Row(),
//STRIP001 /*?*/                                            aNewOut.aEnd.Col(), aNewOut.aEnd.Row() );
//STRIP001 /*?*/
//STRIP001 /*?*/                    if ( !bEmpty )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        QueryBox aBox( rDocShell.GetDialogParent(), WinBits(WB_YES_NO | WB_DEF_YES),
//STRIP001 /*?*/                                         ScGlobal::GetRscString(STR_PIVOT_NOTEMPTY) );
//STRIP001 /*?*/                        if (aBox.Execute() == RET_NO)
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            //! like above (not editable), use undo to reverse everything
//STRIP001 /*?*/                            DBG_ASSERT( bRecord, "DataPilotUpdate: can't undo" );
//STRIP001 /*?*/                            bUndoSelf = TRUE;
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/                if ( bRecord )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    USHORT nTab = aNewOut.aStart.Tab();
//STRIP001 /*?*/                    pNewUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 /*?*/                    pNewUndoDoc->InitUndo( pDoc, nTab, nTab );
//STRIP001 /*?*/                    pDoc->CopyToDocument( aNewOut, IDF_ALL, FALSE, pNewUndoDoc );
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/                //! test for overlap with other data pilot tables
//STRIP001 /*?*/
//STRIP001 /*?*/                pDestObj->Output();
//STRIP001 /*?*/
//STRIP001 /*?*/                rDocShell.PostPaintGridAll();           //! only necessary parts
//STRIP001 /*?*/                bDone = TRUE;
/*N*/           }
/*N*/       }
/*N*/       // else nothing (no old, no new)
/*N*/   }
/*N*/
/*N*/   if ( bRecord && bDone )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 SfxUndoAction* pAction = new ScUndoDataPilot( &rDocShell,
//STRIP001 /*?*/                                    pOldUndoDoc, pNewUndoDoc, pUndoDPObj, pDestObj );
//STRIP001 /*?*/        pOldUndoDoc = NULL;
//STRIP001 /*?*/        pNewUndoDoc = NULL;     // pointers are used in undo action
//STRIP001 /*?*/        // pUndoDPObj is copied
//STRIP001 /*?*/
//STRIP001 /*?*/        if (bUndoSelf)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            //  use undo action to restore original state
//STRIP001 /*?*/            //! prevent setting the document modified? (ScDocShellModificator)
//STRIP001 /*?*/
//STRIP001 /*?*/            pAction->Undo();
//STRIP001 /*?*/            delete pAction;
//STRIP001 /*?*/            bDone = FALSE;
//STRIP001 /*?*/        }
//STRIP001 /*?*/        else
//STRIP001 /*?*/            rDocShell.GetUndoManager()->AddUndoAction( pAction );
/*N*/   }
/*N*/
/*N*/   delete pOldUndoDoc;     // if not used for undo
/*N*/   delete pNewUndoDoc;
/*N*/   delete pUndoDPObj;
/*N*/
/*N*/   if (bDone)
/*N*/       aModificator.SetDocumentModified();
/*N*/
/*N*/   if ( nErrId && !bApi )
/*N*/       rDocShell.ErrorMessage( nErrId );
/*N*/
/*N*/   return bDone;
/*N*/ }

//==================================================================
//
//      Datenbank-Import...

/*M*/ void ScDBDocFunc::UpdateImport( const String& rTarget, const String& rDBName,
/*M*/         const String& rTableName, const String& rStatement, BOOL bNative,
/*M*/         BYTE nType, const ::com::sun::star::uno::Reference<
/*M*/         ::com::sun::star::sdbc::XResultSet >& xResultSet,
/*M*/         const SbaSelectionList* pSelection )
/*M*/ {
/*M*/   //  Target ist jetzt einfach der Bereichsname
/*M*/
/*M*/   ScDocument* pDoc = rDocShell.GetDocument();
/*M*/   ScDBCollection& rDBColl = *pDoc->GetDBCollection();
/*M*/   ScDBData* pData;
/*M*/   ScImportParam aImportParam;
/*M*/   BOOL bFound = FALSE;
/*M*/   USHORT nCount = rDBColl.GetCount();
/*M*/   for (USHORT i=0; i<nCount && !bFound; i++)
/*M*/   {
/*M*/       pData = rDBColl[i];
/*M*/       if (pData->GetName() == rTarget)
/*M*/           bFound = TRUE;
/*M*/   }
/*M*/   if (!bFound)
/*M*/   {
/*M*/       InfoBox aInfoBox(rDocShell.GetDialogParent(),
/*M*/                   ScGlobal::GetRscString( STR_TARGETNOTFOUND ) );
/*M*/       aInfoBox.Execute();
/*M*/       return;
/*M*/   }
/*M*/
/*M*/   USHORT nTab;
/*M*/   USHORT nDummy;
/*M*/   pData->GetArea( nTab, nDummy,nDummy,nDummy,nDummy );
/*M*/   pData->GetImportParam( aImportParam );
/*M*/
/*M*/   BOOL bSql = ( rStatement.Len() != 0 );
/*M*/
/*M*/   aImportParam.aDBName    = rDBName;
/*M*/   aImportParam.bSql       = bSql;
/*M*/   aImportParam.aStatement = bSql ? rStatement : rTableName;
/*M*/   aImportParam.bNative    = bNative;
/*M*/   aImportParam.nType      = nType;
/*M*/   aImportParam.bImport    = TRUE;
/*M*/   BOOL bContinue = DoImport( nTab, aImportParam, xResultSet, pSelection, TRUE );
/*M*/
/*M*/   //  DB-Operationen wiederholen
/*M*/
/*M*/   ScTabViewShell* pViewSh = rDocShell.GetBestViewShell();
/*M*/   if (pViewSh)
/*M*/   {
/*M*/       ScRange aRange;
/*M*/       pData->GetArea(aRange);
/*M*/       pViewSh->MarkRange(aRange);         // selektieren
/*M*/
/*M*/       if ( bContinue )        // #41905# Fehler beim Import -> Abbruch
/*M*/       {
/*M*/           //  interne Operationen, wenn welche gespeichert
/*M*/
/*M*/           DBG_ASSERT(0, "STRIP"); //STRIP001 if ( pData->HasQueryParam() || pData->HasSortParam() || pData->HasSubTotalParam() )
//STRIP001 /*M*/                pViewSh->RepeatDB();
//STRIP001 /*M*/
//STRIP001 /*M*/            //  Pivottabellen die den Bereich als Quelldaten haben
//STRIP001 /*M*/
//STRIP001 /*M*/            rDocShell.RefreshPivotTables(aRange);
/*M*/       }
/*M*/   }
/*M*/ }




