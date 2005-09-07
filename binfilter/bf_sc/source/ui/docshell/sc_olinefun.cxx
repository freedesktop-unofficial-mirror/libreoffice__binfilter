/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_olinefun.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 19:10:38 $
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
// auto strip #include "ui_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------

// auto strip #include <vcl/sound.hxx>
#include <bf_sfx2/bindings.hxx>

#include "olinefun.hxx"

#include "docsh.hxx"
// auto strip #include "olinetab.hxx"
// auto strip #include "undodat.hxx"
#include "globstr.hrc"
#include "bf_sc.hrc"
namespace binfilter {


//========================================================================

/*N*/ void lcl_InvalidateOutliner( SfxBindings* pBindings )
/*N*/ {
/*N*/   if ( pBindings )
/*N*/   {
/*N*/       pBindings->Invalidate( SID_OUTLINE_SHOW );
/*N*/       pBindings->Invalidate( SID_OUTLINE_HIDE );
/*N*/       pBindings->Invalidate( SID_OUTLINE_REMOVE );
/*N*/
/*N*/       pBindings->Invalidate( SID_STATUS_SUM );            // wegen ein-/ausblenden
/*N*/       pBindings->Invalidate( SID_ATTR_SIZE );
/*N*/   }
/*N*/ }

//------------------------------------------------------------------------

//! PaintWidthHeight zur DocShell verschieben?

/*N*/ void lcl_PaintWidthHeight( ScDocShell& rDocShell, USHORT nTab,
/*N*/                                   BOOL bColumns, USHORT nStart, USHORT nEnd )
/*N*/ {
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/
/*N*/   USHORT nParts = PAINT_GRID;
/*N*/   USHORT nStartCol = 0;
/*N*/   USHORT nStartRow = 0;
/*N*/   USHORT nEndCol = MAXCOL;            // fuer Test auf Merge
/*N*/   USHORT nEndRow = MAXROW;
/*N*/   if ( bColumns )
/*N*/   {
/*N*/       nParts |= PAINT_TOP;
/*N*/       nStartCol = nStart;
/*N*/       nEndCol = nEnd;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       nParts |= PAINT_LEFT;
/*N*/       nStartRow = nStart;
/*N*/       nEndRow = nEnd;
/*N*/   }
/*N*/   if (pDoc->HasAttrib( nStartCol,nStartRow,nTab, nEndCol,nEndRow,nTab,
/*N*/                           HASATTR_MERGED | HASATTR_OVERLAPPED ))
/*N*/   {
/*N*/       nStartCol = 0;
/*N*/       nStartRow = 0;
/*N*/   }
/*N*/   rDocShell.PostPaint( nStartCol,nStartRow,nTab, MAXCOL,MAXROW,nTab, nParts );
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL ScOutlineDocFunc::MakeOutline( const ScRange& rRange, BOOL bColumns, BOOL bRecord, BOOL bApi )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE; //STRIP001 BOOL bSuccess = FALSE;
//STRIP001 /*?*/    USHORT nStartCol = rRange.aStart.Col();
//STRIP001 /*?*/    USHORT nStartRow = rRange.aStart.Row();
//STRIP001 /*?*/    USHORT nEndCol = rRange.aEnd.Col();
//STRIP001 /*?*/    USHORT nEndRow = rRange.aEnd.Row();
//STRIP001 /*?*/    USHORT nTab = rRange.aStart.Tab();
//STRIP001 /*?*/
//STRIP001 /*?*/    ScDocument* pDoc = rDocShell.GetDocument();
//STRIP001 /*?*/    ScOutlineTable* pTable = pDoc->GetOutlineTable( nTab, TRUE );
//STRIP001 /*?*/    ScOutlineTable* pUndoTab = NULL;
//STRIP001 /*?*/
//STRIP001 /*?*/    if (bRecord && !pDoc->IsUndoEnabled())
//STRIP001 /*?*/        bRecord = FALSE;
//STRIP001 /*?*/
//STRIP001 /*?*/    if (bRecord)
//STRIP001 /*?*/        pUndoTab = new ScOutlineTable( *pTable );
//STRIP001 /*?*/
//STRIP001 /*?*/    ScOutlineArray* pArray = bColumns ? pTable->GetColArray() : pTable->GetRowArray();
//STRIP001 /*?*/
//STRIP001 /*?*/    BOOL bRes;
//STRIP001 /*?*/    BOOL bSize = FALSE;
//STRIP001 /*?*/    if ( bColumns )
//STRIP001 /*?*/        bRes = pArray->Insert( nStartCol, nEndCol, bSize );
//STRIP001 /*?*/    else
//STRIP001 /*?*/        bRes = pArray->Insert( nStartRow, nEndRow, bSize );
//STRIP001 /*?*/
//STRIP001 /*?*/    if ( bRes )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        if (bRecord)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                new ScUndoMakeOutline( &rDocShell,
//STRIP001 /*?*/                                        nStartCol,nStartRow,nTab,nEndCol,nEndRow,nTab,
//STRIP001 /*?*/                                        pUndoTab, bColumns, TRUE ) );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        USHORT nParts = 0;              // Datenbereich nicht geaendert
//STRIP001 /*?*/        if ( bColumns )
//STRIP001 /*?*/            nParts |= PAINT_TOP;
//STRIP001 /*?*/        else
//STRIP001 /*?*/            nParts |= PAINT_LEFT;
//STRIP001 /*?*/        if ( bSize )
//STRIP001 /*?*/            nParts |= PAINT_SIZE;
//STRIP001 /*?*/
//STRIP001 /*?*/        rDocShell.PostPaint( 0,0,nTab, MAXCOL,MAXROW,nTab, nParts );
//STRIP001 /*?*/        rDocShell.SetDocumentModified();
//STRIP001 /*?*/        lcl_InvalidateOutliner( rDocShell.GetViewBindings() );
//STRIP001 /*?*/        bSuccess = TRUE;
//STRIP001 /*?*/    }
//STRIP001 /*?*/    else
//STRIP001 /*?*/    {
//STRIP001 /*?*/        if (!bApi)
//STRIP001 /*?*/            rDocShell.ErrorMessage(STR_MSSG_MAKEOUTLINE_0); // "Gruppierung nicht moeglich"
//STRIP001 /*?*/        delete pUndoTab;
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    return bSuccess;
/*N*/ }

/*N*/ BOOL ScOutlineDocFunc::RemoveOutline( const ScRange& rRange, BOOL bColumns, BOOL bRecord, BOOL bApi )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE; //STRIP001 BOOL bDone = FALSE;
//STRIP001 /*?*/
//STRIP001 /*?*/    USHORT nStartCol = rRange.aStart.Col();
//STRIP001 /*?*/    USHORT nStartRow = rRange.aStart.Row();
//STRIP001 /*?*/    USHORT nEndCol = rRange.aEnd.Col();
//STRIP001 /*?*/    USHORT nEndRow = rRange.aEnd.Row();
//STRIP001 /*?*/    USHORT nTab = rRange.aStart.Tab();
//STRIP001 /*?*/
//STRIP001 /*?*/    ScDocument* pDoc = rDocShell.GetDocument();
//STRIP001 /*?*/
//STRIP001 /*?*/    if (bRecord && !pDoc->IsUndoEnabled())
//STRIP001 /*?*/        bRecord = FALSE;
//STRIP001 /*?*/    ScOutlineTable* pTable = pDoc->GetOutlineTable( nTab );
//STRIP001 /*?*/    if (pTable)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        ScOutlineTable* pUndoTab = NULL;
//STRIP001 /*?*/        if (bRecord)
//STRIP001 /*?*/            pUndoTab = new ScOutlineTable( *pTable );
//STRIP001 /*?*/
//STRIP001 /*?*/        ScOutlineArray* pArray = bColumns ? pTable->GetColArray() : pTable->GetRowArray();
//STRIP001 /*?*/
//STRIP001 /*?*/        BOOL bRes;
//STRIP001 /*?*/        BOOL bSize = FALSE;
//STRIP001 /*?*/        if ( bColumns )
//STRIP001 /*?*/            bRes = pArray->Remove( nStartCol, nEndCol, bSize );
//STRIP001 /*?*/        else
//STRIP001 /*?*/            bRes = pArray->Remove( nStartRow, nEndRow, bSize );
//STRIP001 /*?*/
//STRIP001 /*?*/        if ( bRes )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            if (bRecord)
//STRIP001 /*?*/            {
//STRIP001 /*?*/                rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                    new ScUndoMakeOutline( &rDocShell,
//STRIP001 /*?*/                                            nStartCol,nStartRow,nTab, nEndCol,nEndRow,nTab,
//STRIP001 /*?*/                                            pUndoTab, bColumns, FALSE ) );
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            USHORT nParts = 0;              // Datenbereich nicht geaendert
//STRIP001 /*?*/            if ( bColumns )
//STRIP001 /*?*/                nParts |= PAINT_TOP;
//STRIP001 /*?*/            else
//STRIP001 /*?*/                nParts |= PAINT_LEFT;
//STRIP001 /*?*/            if ( bSize )
//STRIP001 /*?*/                nParts |= PAINT_SIZE;
//STRIP001 /*?*/
//STRIP001 /*?*/            rDocShell.PostPaint( 0,0,nTab, MAXCOL,MAXROW,nTab, nParts );
//STRIP001 /*?*/            rDocShell.SetDocumentModified();
//STRIP001 /*?*/            bDone = TRUE;
//STRIP001 /*?*/            lcl_InvalidateOutliner( rDocShell.GetViewBindings() );
//STRIP001 /*?*/
//STRIP001 /*?*/            // es wird nicht wieder eingeblendet -> kein UpdatePageBreaks
//STRIP001 /*?*/        }
//STRIP001 /*?*/        else
//STRIP001 /*?*/            delete pUndoTab;
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    if (!bDone && !bApi)
//STRIP001 /*?*/        rDocShell.ErrorMessage(STR_MSSG_REMOVEOUTLINE_0);   // "Aufheben nicht moeglich"
//STRIP001 /*?*/
//STRIP001 /*?*/    return bDone;
/*N*/ }

/*N*/ BOOL ScOutlineDocFunc::RemoveAllOutlines( USHORT nTab, BOOL bRecord, BOOL bApi )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE; //STRIP001 BOOL bSuccess = FALSE;
//STRIP001 /*?*/    ScDocument* pDoc = rDocShell.GetDocument();
//STRIP001 /*?*/
//STRIP001 /*?*/    if (bRecord && !pDoc->IsUndoEnabled())
//STRIP001 /*?*/        bRecord = FALSE;
//STRIP001 /*?*/    ScOutlineTable* pTable = pDoc->GetOutlineTable( nTab );
//STRIP001 /*?*/    if (pTable)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        USHORT nStartCol;
//STRIP001 /*?*/        USHORT nStartRow;
//STRIP001 /*?*/        USHORT nEndCol;
//STRIP001 /*?*/        USHORT nEndRow;
//STRIP001 /*?*/        pTable->GetColArray()->GetRange( nStartCol, nEndCol );
//STRIP001 /*?*/        pTable->GetRowArray()->GetRange( nStartRow, nEndRow );
//STRIP001 /*?*/
//STRIP001 /*?*/        if (bRecord)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            ScDocument* pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 /*?*/            pUndoDoc->InitUndo( pDoc, nTab, nTab, TRUE, TRUE );
//STRIP001 /*?*/            pDoc->CopyToDocument( nStartCol, 0, nTab, nEndCol, MAXROW, nTab, IDF_NONE, FALSE, pUndoDoc );
//STRIP001 /*?*/            pDoc->CopyToDocument( 0, nStartRow, nTab, MAXCOL, nEndRow, nTab, IDF_NONE, FALSE, pUndoDoc );
//STRIP001 /*?*/
//STRIP001 /*?*/            ScOutlineTable* pUndoTab = new ScOutlineTable( *pTable );
//STRIP001 /*?*/
//STRIP001 /*?*/            rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                new ScUndoRemoveAllOutlines( &rDocShell,
//STRIP001 /*?*/                                                nStartCol, nStartRow, nTab,
//STRIP001 /*?*/                                                nEndCol, nEndRow, nTab,
//STRIP001 /*?*/                                                pUndoDoc, pUndoTab ) );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        SelectLevel( nTab, TRUE,  pTable->GetColArray()->GetDepth(), FALSE, FALSE, bApi );
//STRIP001 /*?*/        SelectLevel( nTab, FALSE, pTable->GetRowArray()->GetDepth(), FALSE, FALSE, bApi );
//STRIP001 /*?*/        pDoc->SetOutlineTable( nTab, NULL );
//STRIP001 /*?*/
//STRIP001 /*?*/        pDoc->UpdatePageBreaks( nTab );
//STRIP001 /*?*/
//STRIP001 /*?*/        rDocShell.PostPaint( 0,0,nTab, MAXCOL,MAXROW,nTab,
//STRIP001 /*?*/                                    PAINT_GRID | PAINT_LEFT | PAINT_TOP | PAINT_SIZE );
//STRIP001 /*?*/        rDocShell.SetDocumentModified();
//STRIP001 /*?*/        lcl_InvalidateOutliner( rDocShell.GetViewBindings() );
//STRIP001 /*?*/        bSuccess = TRUE;
//STRIP001 /*?*/    }
//STRIP001 /*?*/    else if (!bApi)
//STRIP001 /*?*/        Sound::Beep();
//STRIP001 /*?*/
//STRIP001 /*?*/    return bSuccess;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL ScOutlineDocFunc::AutoOutline( const ScRange& rRange, BOOL bRecord, BOOL bApi )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 USHORT nStartCol = rRange.aStart.Col();
//STRIP001 /*?*/    USHORT nStartRow = rRange.aStart.Row();
//STRIP001 /*?*/    USHORT nEndCol = rRange.aEnd.Col();
//STRIP001 /*?*/    USHORT nEndRow = rRange.aEnd.Row();
//STRIP001 /*?*/    USHORT nTab = rRange.aStart.Tab();
//STRIP001 /*?*/
//STRIP001 /*?*/    ScDocument* pDoc = rDocShell.GetDocument();
//STRIP001 /*?*/
//STRIP001 /*?*/    if (bRecord && !pDoc->IsUndoEnabled())
//STRIP001 /*?*/        bRecord = FALSE;
//STRIP001 /*?*/    ScOutlineTable* pTable = pDoc->GetOutlineTable( nTab );
//STRIP001 /*?*/
//STRIP001 /*?*/    ScDocument* pUndoDoc = NULL;
//STRIP001 /*?*/    ScOutlineTable* pUndoTab = NULL;
//STRIP001 /*?*/
//STRIP001 /*?*/    if ( pTable )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        if ( bRecord )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pUndoTab = new ScOutlineTable( *pTable );
//STRIP001 /*?*/
//STRIP001 /*?*/            USHORT nOutStartCol;
//STRIP001 /*?*/            USHORT nOutStartRow;
//STRIP001 /*?*/            USHORT nOutEndCol;
//STRIP001 /*?*/            USHORT nOutEndRow;
//STRIP001 /*?*/            pTable->GetColArray()->GetRange( nOutStartCol, nOutEndCol );
//STRIP001 /*?*/            pTable->GetRowArray()->GetRange( nOutStartRow, nOutEndRow );
//STRIP001 /*?*/
//STRIP001 /*?*/            pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 /*?*/            pUndoDoc->InitUndo( pDoc, nTab, nTab, TRUE, TRUE );
//STRIP001 /*?*/            pDoc->CopyToDocument( nOutStartCol, 0, nTab, nOutEndCol, MAXROW, nTab, IDF_NONE, FALSE, pUndoDoc );
//STRIP001 /*?*/            pDoc->CopyToDocument( 0, nOutStartRow, nTab, MAXCOL, nOutEndRow, nTab, IDF_NONE, FALSE, pUndoDoc );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        // einblenden
//STRIP001 /*?*/        SelectLevel( nTab, TRUE,  pTable->GetColArray()->GetDepth(), FALSE, FALSE, bApi );
//STRIP001 /*?*/        SelectLevel( nTab, FALSE, pTable->GetRowArray()->GetDepth(), FALSE, FALSE, bApi );
//STRIP001 /*?*/        pDoc->SetOutlineTable( nTab, NULL );
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    pDoc->DoAutoOutline( nStartCol,nStartRow, nEndCol,nEndRow, nTab );
//STRIP001 /*?*/
//STRIP001 /*?*/    if (bRecord)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/            new ScUndoAutoOutline( &rDocShell,
//STRIP001 /*?*/                                    nStartCol, nStartRow, nTab,
//STRIP001 /*?*/                                    nEndCol, nEndRow, nTab,
//STRIP001 /*?*/                                    pUndoDoc, pUndoTab ) );
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    rDocShell.PostPaint( 0,0,nTab, MAXCOL,MAXROW,nTab, PAINT_LEFT | PAINT_TOP | PAINT_SIZE );
//STRIP001 /*?*/    rDocShell.SetDocumentModified();
//STRIP001 /*?*/    lcl_InvalidateOutliner( rDocShell.GetViewBindings() );
//STRIP001 /*?*/
/*N*/   return TRUE;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL ScOutlineDocFunc::SelectLevel( USHORT nTab, BOOL bColumns, USHORT nLevel,
/*N*/                                   BOOL bRecord, BOOL bPaint, BOOL bApi )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ScDocument* pDoc = rDocShell.GetDocument();
//STRIP001 /*?*/
//STRIP001 /*?*/    if (bRecord && !pDoc->IsUndoEnabled())
//STRIP001 /*?*/        bRecord = FALSE;
//STRIP001 /*?*/    ScOutlineTable* pTable = pDoc->GetOutlineTable( nTab );             // ist schon da
//STRIP001 /*?*/    if (!pTable)
//STRIP001 /*?*/        return FALSE;
//STRIP001 /*?*/    ScOutlineArray* pArray = bColumns ? pTable->GetColArray() : pTable->GetRowArray();
//STRIP001 /*?*/    if (!pArray)
//STRIP001 /*?*/        return FALSE;
//STRIP001 /*?*/
//STRIP001 /*?*/    USHORT nStart;
//STRIP001 /*?*/    USHORT nEnd;
//STRIP001 /*?*/    pArray->GetRange( nStart, nEnd );
//STRIP001 /*?*/
//STRIP001 /*?*/    if ( bRecord )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        ScOutlineTable* pUndoTab = new ScOutlineTable( *pTable );
//STRIP001 /*?*/        ScDocument* pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 /*?*/        if (bColumns)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pUndoDoc->InitUndo( pDoc, nTab, nTab, TRUE, FALSE );
//STRIP001 /*?*/            pDoc->CopyToDocument( nStart, 0, nTab, nEnd, MAXROW, nTab, IDF_NONE, FALSE, pUndoDoc );
//STRIP001 /*?*/        }
//STRIP001 /*?*/        else
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pUndoDoc->InitUndo( pDoc, nTab, nTab, FALSE, TRUE );
//STRIP001 /*?*/            pDoc->CopyToDocument( 0, nStart, nTab, MAXCOL, nEnd, nTab, IDF_NONE, FALSE, pUndoDoc );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/            new ScUndoOutlineLevel( &rDocShell,
//STRIP001 /*?*/                                    nStart, nEnd, nTab,             //! start und end berechnen
//STRIP001 /*?*/                                    pUndoDoc, pUndoTab,
//STRIP001 /*?*/                                    bColumns, nLevel ) );
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    ScSubOutlineIterator aIter( pArray );                   // alle Eintraege
//STRIP001 /*?*/    ScOutlineEntry* pEntry;
//STRIP001 /*?*/    while ((pEntry=aIter.GetNext()) != NULL)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        USHORT nThisLevel = aIter.LastLevel();
//STRIP001 /*?*/        BOOL bShow = (nThisLevel < nLevel);
//STRIP001 /*?*/        if (bShow)                                          // einblenden
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pEntry->SetHidden( FALSE );
//STRIP001 /*?*/            pEntry->SetVisible( TRUE );
//STRIP001 /*?*/        }
//STRIP001 /*?*/        else if ( nThisLevel == nLevel )                    // ausblenden
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pEntry->SetHidden( TRUE );
//STRIP001 /*?*/            pEntry->SetVisible( TRUE );
//STRIP001 /*?*/        }
//STRIP001 /*?*/        else                                                // verdeckt
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pEntry->SetVisible( FALSE );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        USHORT nThisStart = pEntry->GetStart();
//STRIP001 /*?*/        USHORT nThisEnd   = pEntry->GetEnd();
//STRIP001 /*?*/        for (USHORT i=nThisStart; i<=nThisEnd; i++)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            if ( bColumns )
//STRIP001 /*?*/                pDoc->ShowCol( i, nTab, bShow );
//STRIP001 /*?*/            else
//STRIP001 /*?*/                if ( !bShow || !pDoc->IsFiltered( i,nTab ) )
//STRIP001 /*?*/                    pDoc->ShowRow( i, nTab, bShow );
//STRIP001 /*?*/        }
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    pDoc->UpdatePageBreaks( nTab );
//STRIP001 /*?*/
//STRIP001 /*?*/    if (bPaint)
//STRIP001 /*?*/        DBG_BF_ASSERT(0, "STRIP"); //STRIP001 lcl_PaintWidthHeight( rDocShell, nTab, bColumns, nStart, nEnd );
//STRIP001 /*?*/
//STRIP001 /*?*/    rDocShell.SetDocumentModified();
//STRIP001 /*?*/    lcl_InvalidateOutliner( rDocShell.GetViewBindings() );
//STRIP001 /*?*/
/*N*/   return TRUE;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL ScOutlineDocFunc::ShowMarkedOutlines( const ScRange& rRange, BOOL bRecord, BOOL bApi )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 BOOL bDone = FALSE;
//STRIP001 /*?*/
//STRIP001 /*?*/    USHORT nStartCol = rRange.aStart.Col();
//STRIP001 /*?*/    USHORT nStartRow = rRange.aStart.Row();
//STRIP001 /*?*/    USHORT nEndCol = rRange.aEnd.Col();
//STRIP001 /*?*/    USHORT nEndRow = rRange.aEnd.Row();
//STRIP001 /*?*/    USHORT nTab = rRange.aStart.Tab();
//STRIP001 /*?*/
//STRIP001 /*?*/    ScDocument* pDoc = rDocShell.GetDocument();
//STRIP001 /*?*/
//STRIP001 /*?*/    if (bRecord && !pDoc->IsUndoEnabled())
//STRIP001 /*?*/        bRecord = FALSE;
//STRIP001 /*?*/    ScOutlineTable* pTable = pDoc->GetOutlineTable( nTab );
//STRIP001 /*?*/
//STRIP001 /*?*/    if (pTable)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        ScOutlineArray* pArray;
//STRIP001 /*?*/        ScOutlineEntry* pEntry;
//STRIP001 /*?*/        USHORT nStart;
//STRIP001 /*?*/        USHORT nEnd;
//STRIP001 /*?*/        USHORT nMin;
//STRIP001 /*?*/        USHORT nMax;
//STRIP001 /*?*/        USHORT i;
//STRIP001 /*?*/
//STRIP001 /*?*/        if ( bRecord )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            ScOutlineTable* pUndoTab = new ScOutlineTable( *pTable );
//STRIP001 /*?*/            ScDocument* pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 /*?*/            pUndoDoc->InitUndo( pDoc, nTab, nTab, TRUE, TRUE );
//STRIP001 /*?*/            pDoc->CopyToDocument( nStartCol, 0, nTab, nEndCol, MAXROW, nTab, IDF_NONE, FALSE, pUndoDoc );
//STRIP001 /*?*/            pDoc->CopyToDocument( 0, nStartRow, nTab, MAXCOL, nEndRow, nTab, IDF_NONE, FALSE, pUndoDoc );
//STRIP001 /*?*/
//STRIP001 /*?*/            rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                new ScUndoOutlineBlock( &rDocShell,
//STRIP001 /*?*/                                        nStartCol, nStartRow, nTab, nEndCol, nEndRow, nTab,
//STRIP001 /*?*/                                        pUndoDoc, pUndoTab, TRUE ) );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        //  Spalten
//STRIP001 /*?*/
//STRIP001 /*?*/        nMin=MAXCOL;
//STRIP001 /*?*/        nMax=0;
//STRIP001 /*?*/        pArray = pTable->GetColArray();
//STRIP001 /*?*/        ScSubOutlineIterator aColIter( pArray );
//STRIP001 /*?*/        while ((pEntry=aColIter.GetNext()) != NULL)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            nStart = pEntry->GetStart();
//STRIP001 /*?*/            nEnd   = pEntry->GetEnd();
//STRIP001 /*?*/            if ( nStart>=nStartCol && nEnd<=nEndCol )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                pEntry->SetHidden( FALSE );
//STRIP001 /*?*/                pEntry->SetVisible( TRUE );
//STRIP001 /*?*/                if (nStart<nMin) nMin=nStart;
//STRIP001 /*?*/                if (nEnd>nMax) nMax=nEnd;
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
//STRIP001 /*?*/        for ( i=nMin; i<=nMax; i++ )
//STRIP001 /*?*/            pDoc->ShowCol( i, nTab, TRUE );
//STRIP001 /*?*/
//STRIP001 /*?*/        //  Zeilen
//STRIP001 /*?*/
//STRIP001 /*?*/        nMin=MAXROW;
//STRIP001 /*?*/        nMax=0;
//STRIP001 /*?*/        pArray = pTable->GetRowArray();
//STRIP001 /*?*/        ScSubOutlineIterator aRowIter( pArray );
//STRIP001 /*?*/        while ((pEntry=aRowIter.GetNext()) != NULL)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            nStart = pEntry->GetStart();
//STRIP001 /*?*/            nEnd   = pEntry->GetEnd();
//STRIP001 /*?*/            if ( nStart>=nStartRow && nEnd<=nEndRow )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                pEntry->SetHidden( FALSE );
//STRIP001 /*?*/                pEntry->SetVisible( TRUE );
//STRIP001 /*?*/                if (nStart<nMin) nMin=nStart;
//STRIP001 /*?*/                if (nEnd>nMax) nMax=nEnd;
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
//STRIP001 /*?*/        for ( i=nMin; i<=nMax; i++ )
//STRIP001 /*?*/            if ( !pDoc->IsFiltered( i,nTab ) )              // weggefilterte nicht einblenden
//STRIP001 /*?*/                pDoc->ShowRow( i, nTab, TRUE );
//STRIP001 /*?*/
//STRIP001 /*?*/        pDoc->UpdatePageBreaks( nTab );
//STRIP001 /*?*/
//STRIP001 /*?*/        rDocShell.PostPaint( 0,0,nTab, MAXCOL,MAXROW,nTab, PAINT_GRID | PAINT_LEFT | PAINT_TOP );
//STRIP001 /*?*/
//STRIP001 /*?*/        rDocShell.SetDocumentModified();
//STRIP001 /*?*/        bDone = TRUE;
//STRIP001 /*?*/
//STRIP001 /*?*/        lcl_InvalidateOutliner( rDocShell.GetViewBindings() );
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    if (!bDone && !bApi)
//STRIP001 /*?*/        Sound::Beep();
//STRIP001 /*?*/
//STRIP001 /*?*/    return bDone;
/*N*/ }

/*N*/ BOOL ScOutlineDocFunc::HideMarkedOutlines( const ScRange& rRange, BOOL bRecord, BOOL bApi )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE; //STRIP001 BOOL bDone = FALSE;
//STRIP001 /*?*/
//STRIP001 /*?*/    USHORT nStartCol = rRange.aStart.Col();
//STRIP001 /*?*/    USHORT nStartRow = rRange.aStart.Row();
//STRIP001 /*?*/    USHORT nEndCol = rRange.aEnd.Col();
//STRIP001 /*?*/    USHORT nEndRow = rRange.aEnd.Row();
//STRIP001 /*?*/    USHORT nTab = rRange.aStart.Tab();
//STRIP001 /*?*/
//STRIP001 /*?*/    ScDocument* pDoc = rDocShell.GetDocument();
//STRIP001 /*?*/
//STRIP001 /*?*/    if (bRecord && !pDoc->IsUndoEnabled())
//STRIP001 /*?*/        bRecord = FALSE;
//STRIP001 /*?*/    ScOutlineTable* pTable = pDoc->GetOutlineTable( nTab );
//STRIP001 /*?*/
//STRIP001 /*?*/    if (pTable)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        ScOutlineEntry* pEntry;
//STRIP001 /*?*/        USHORT nColLevel;
//STRIP001 /*?*/        USHORT nRowLevel;
//STRIP001 /*?*/        USHORT nCount;
//STRIP001 /*?*/        USHORT nStart;
//STRIP001 /*?*/        USHORT nEnd;
//STRIP001 /*?*/        USHORT i;
//STRIP001 /*?*/
//STRIP001 /*?*/        USHORT nEffStartCol = nStartCol;
//STRIP001 /*?*/        USHORT nEffEndCol   = nEndCol;
//STRIP001 /*?*/        ScOutlineArray* pColArray = pTable->GetColArray();
//STRIP001 /*?*/        pColArray->FindTouchedLevel( nStartCol, nEndCol, nColLevel );
//STRIP001 /*?*/        pColArray->ExtendBlock( nColLevel, nEffStartCol, nEffEndCol );
//STRIP001 /*?*/        USHORT nEffStartRow = nStartRow;
//STRIP001 /*?*/        USHORT nEffEndRow   = nEndRow;
//STRIP001 /*?*/        ScOutlineArray* pRowArray = pTable->GetRowArray();
//STRIP001 /*?*/        pRowArray->FindTouchedLevel( nStartRow, nEndRow, nRowLevel );
//STRIP001 /*?*/        pRowArray->ExtendBlock( nRowLevel, nEffStartRow, nEffEndRow );
//STRIP001 /*?*/
//STRIP001 /*?*/        if ( bRecord )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            ScOutlineTable* pUndoTab = new ScOutlineTable( *pTable );
//STRIP001 /*?*/            ScDocument* pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 /*?*/            pUndoDoc->InitUndo( pDoc, nTab, nTab, TRUE, TRUE );
//STRIP001 /*?*/            pDoc->CopyToDocument( nEffStartCol, 0, nTab, nEffEndCol, MAXROW, nTab, IDF_NONE, FALSE, pUndoDoc );
//STRIP001 /*?*/            pDoc->CopyToDocument( 0, nEffStartRow, nTab, MAXCOL, nEffEndRow, nTab, IDF_NONE, FALSE, pUndoDoc );
//STRIP001 /*?*/
//STRIP001 /*?*/            rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                new ScUndoOutlineBlock( &rDocShell,
//STRIP001 /*?*/                                        nStartCol, nStartRow, nTab, nEndCol, nEndRow, nTab,
//STRIP001 /*?*/                                        pUndoDoc, pUndoTab, FALSE ) );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        //  Spalten
//STRIP001 /*?*/
//STRIP001 /*?*/        nCount = pColArray->GetCount(nColLevel);
//STRIP001 /*?*/        for ( i=0; i<nCount; i++ )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pEntry = pColArray->GetEntry(nColLevel,i);
//STRIP001 /*?*/            nStart = pEntry->GetStart();
//STRIP001 /*?*/            nEnd   = pEntry->GetEnd();
//STRIP001 /*?*/
//STRIP001 /*?*/            if ( nStartCol<=nEnd && nEndCol>=nStart )
//STRIP001 /*?*/                HideOutline( nTab, TRUE, nColLevel, i, FALSE, FALSE, bApi );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        //  Zeilen
//STRIP001 /*?*/
//STRIP001 /*?*/        nCount = pRowArray->GetCount(nRowLevel);
//STRIP001 /*?*/        for ( i=0; i<nCount; i++ )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pEntry = pRowArray->GetEntry(nRowLevel,i);
//STRIP001 /*?*/            nStart = pEntry->GetStart();
//STRIP001 /*?*/            nEnd   = pEntry->GetEnd();
//STRIP001 /*?*/
//STRIP001 /*?*/            if ( nStartRow<=nEnd && nEndRow>=nStart )
//STRIP001 /*?*/                HideOutline( nTab, FALSE, nRowLevel, i, FALSE, FALSE, bApi );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        pDoc->UpdatePageBreaks( nTab );
//STRIP001 /*?*/
//STRIP001 /*?*/        rDocShell.PostPaint( 0,0,nTab, MAXCOL,MAXROW,nTab, PAINT_GRID | PAINT_LEFT | PAINT_TOP );
//STRIP001 /*?*/
//STRIP001 /*?*/        rDocShell.SetDocumentModified();
//STRIP001 /*?*/        bDone = TRUE;
//STRIP001 /*?*/
//STRIP001 /*?*/        lcl_InvalidateOutliner( rDocShell.GetViewBindings() );
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    if (!bDone && !bApi)
//STRIP001 /*?*/        Sound::Beep();
//STRIP001 /*?*/
//STRIP001 /*?*/    return bDone;
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 BOOL ScOutlineDocFunc::ShowOutline( USHORT nTab, BOOL bColumns, USHORT nLevel, USHORT nEntry,
//STRIP001                                  BOOL bRecord, BOOL bPaint, BOOL bApi )
//STRIP001 {
//STRIP001  ScDocument* pDoc = rDocShell.GetDocument();
//STRIP001  if (bRecord && !pDoc->IsUndoEnabled())
//STRIP001      bRecord = FALSE;
//STRIP001
//STRIP001  ScOutlineTable* pTable = pDoc->GetOutlineTable( nTab );
//STRIP001  ScOutlineArray* pArray = bColumns ? pTable->GetColArray() : pTable->GetRowArray();
//STRIP001  ScOutlineEntry* pEntry = pArray->GetEntry( nLevel, nEntry );
//STRIP001  USHORT nStart = pEntry->GetStart();
//STRIP001  USHORT nEnd   = pEntry->GetEnd();
//STRIP001
//STRIP001  if ( bRecord )
//STRIP001  {
//STRIP001      ScDocument* pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001      if (bColumns)
//STRIP001      {
//STRIP001          pUndoDoc->InitUndo( pDoc, nTab, nTab, TRUE, FALSE );
//STRIP001          pDoc->CopyToDocument( nStart, 0, nTab, nEnd, MAXROW, nTab, IDF_NONE, FALSE, pUndoDoc );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pUndoDoc->InitUndo( pDoc, nTab, nTab, FALSE, TRUE );
//STRIP001          pDoc->CopyToDocument( 0, nStart, nTab, MAXCOL, nEnd, nTab, IDF_NONE, FALSE, pUndoDoc );
//STRIP001      }
//STRIP001
//STRIP001      rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001          new ScUndoDoOutline( &rDocShell,
//STRIP001                                  nStart, nEnd, nTab, pUndoDoc,       //! start und end berechnen
//STRIP001                                  bColumns, nLevel, nEntry, TRUE ) );
//STRIP001  }
//STRIP001
//STRIP001 //!  HideCursor();
//STRIP001
//STRIP001  pEntry->SetHidden(FALSE);
//STRIP001  USHORT i;
//STRIP001  for ( i = nStart; i <= nEnd; i++ )
//STRIP001  {
//STRIP001      if ( bColumns )
//STRIP001          pDoc->ShowCol( i, nTab, TRUE );
//STRIP001      else
//STRIP001          if ( !pDoc->IsFiltered( i,nTab ) )              // weggefilterte nicht einblenden
//STRIP001              pDoc->ShowRow( i, nTab, TRUE );
//STRIP001  }
//STRIP001
//STRIP001  ScSubOutlineIterator aIter( pArray, nLevel, nEntry );
//STRIP001  while ((pEntry=aIter.GetNext()) != NULL)
//STRIP001  {
//STRIP001      if ( pEntry->IsHidden() )
//STRIP001      {
//STRIP001          USHORT nSubStart = pEntry->GetStart();
//STRIP001          USHORT nSubEnd   = pEntry->GetEnd();
//STRIP001          for ( i = nSubStart; i <= nSubEnd; i++ )
//STRIP001          {
//STRIP001              if ( bColumns )
//STRIP001                  pDoc->ShowCol( i, nTab, FALSE );
//STRIP001              else
//STRIP001                  pDoc->ShowRow( i, nTab, FALSE );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  pArray->SetVisibleBelow( nLevel, nEntry, TRUE, TRUE );
//STRIP001
//STRIP001  pDoc->UpdatePageBreaks( nTab );
//STRIP001
//STRIP001  if (bPaint)
//STRIP001      lcl_PaintWidthHeight( rDocShell, nTab, bColumns, nStart, nEnd );
//STRIP001
//STRIP001 //!  ShowCursor();
//STRIP001  rDocShell.SetDocumentModified();
//STRIP001
//STRIP001 //!  if (bPaint)
//STRIP001 //!      UpdateScrollBars();
//STRIP001
//STRIP001  lcl_InvalidateOutliner( rDocShell.GetViewBindings() );
//STRIP001
//STRIP001  return TRUE;        //! immer ???
//STRIP001 }

/*N*/ BOOL ScOutlineDocFunc::HideOutline( USHORT nTab, BOOL bColumns, USHORT nLevel, USHORT nEntry,
/*N*/                                   BOOL bRecord, BOOL bPaint, BOOL bApi )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE; //STRIP001 ScDocument* pDoc = rDocShell.GetDocument();
//STRIP001 /*?*/    if (bRecord && !pDoc->IsUndoEnabled())
//STRIP001 /*?*/        bRecord = FALSE;
//STRIP001 /*?*/
//STRIP001 /*?*/    ScOutlineTable* pTable = pDoc->GetOutlineTable( nTab );
//STRIP001 /*?*/    ScOutlineArray* pArray = bColumns ? pTable->GetColArray() : pTable->GetRowArray();
//STRIP001 /*?*/    ScOutlineEntry* pEntry = pArray->GetEntry( nLevel, nEntry );
//STRIP001 /*?*/    USHORT nStart = pEntry->GetStart();
//STRIP001 /*?*/    USHORT nEnd   = pEntry->GetEnd();
//STRIP001 /*?*/
//STRIP001 /*?*/    if ( bRecord )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        ScDocument* pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 /*?*/        if (bColumns)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pUndoDoc->InitUndo( pDoc, nTab, nTab, TRUE, FALSE );
//STRIP001 /*?*/            pDoc->CopyToDocument( nStart, 0, nTab, nEnd, MAXROW, nTab, IDF_NONE, FALSE, pUndoDoc );
//STRIP001 /*?*/        }
//STRIP001 /*?*/        else
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pUndoDoc->InitUndo( pDoc, nTab, nTab, FALSE, TRUE );
//STRIP001 /*?*/            pDoc->CopyToDocument( 0, nStart, nTab, MAXCOL, nEnd, nTab, IDF_NONE, FALSE, pUndoDoc );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/            new ScUndoDoOutline( &rDocShell,
//STRIP001 /*?*/                                    nStart, nEnd, nTab, pUndoDoc,
//STRIP001 /*?*/                                    bColumns, nLevel, nEntry, FALSE ) );
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/ //!    HideCursor();
//STRIP001 /*?*/
//STRIP001 /*?*/    pEntry->SetHidden(TRUE);
//STRIP001 /*?*/    USHORT i;
//STRIP001 /*?*/    for ( i = nStart; i <= nEnd; i++ )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        if ( bColumns )
//STRIP001 /*?*/            pDoc->ShowCol( i, nTab, FALSE );
//STRIP001 /*?*/        else
//STRIP001 /*?*/            pDoc->ShowRow( i, nTab, FALSE );
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    pArray->SetVisibleBelow( nLevel, nEntry, FALSE );
//STRIP001 /*?*/
//STRIP001 /*?*/    pDoc->UpdatePageBreaks( nTab );
//STRIP001 /*?*/
//STRIP001 /*?*/    if (bPaint)
//STRIP001 /*?*/        lcl_PaintWidthHeight( rDocShell, nTab, bColumns, nStart, nEnd );
//STRIP001 /*?*/
//STRIP001 /*?*/ //!    ShowCursor();
//STRIP001 /*?*/    rDocShell.SetDocumentModified();
//STRIP001 /*?*/
//STRIP001 /*?*/ //!    if (bPaint)
//STRIP001 /*?*/ //!        UpdateScrollBars();
//STRIP001 /*?*/
//STRIP001 /*?*/    lcl_InvalidateOutliner( rDocShell.GetViewBindings() );
//STRIP001 /*?*/
/*N*/   return TRUE;        //! immer ???
/*N*/ }





}
