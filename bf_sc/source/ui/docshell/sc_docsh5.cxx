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

#define _BASEDLGS_HXX
#define _BIGINT_HXX
#define _CACHESTR_HXX
#define _CONFIG_HXX
#define _CURSOR_HXX
#define _DIALOGS_HXX
#define _DLGCFG_HXX
#define _DYNARR_HXX
#define _EXTATTR_HXX
#define _FILDLG_HXX
#define _FONTDLG_HXX
#define _FRM3D_HXX
#define _INTRO_HXX
#define _ISETBWR_HXX
#define _NO_SVRTF_PARSER_HXX
#define _MACRODLG_HXX
#define _MODALDLG_HXX
#define _MOREBUTTON_HXX
#define _OUTLINER_HXX
#define _PASSWD_HXX
#define _POLY_HXX
#define _PVRWIN_HXX
#define _QUEUE_HXX
#define _RULER_HXX
#define _SCRWIN_HXX
#define _SETBRW_HXX
#define _STACK_HXX
#define _STDMENU_HXX
#define _TABBAR_HXX
#define _VCBRW_HXX
#define _VCTRLS_HXX
#define _VCSBX_HXX
#define _VCONT_HXX
#define _VDRWOBJ_HXX


#define _SFX_PRNMON_HXX
#define _SFX_RESMGR_HXX
#define _SFX_TEMPLDLG_HXX
#define _SFXBASIC_HXX
#define _SFXFILEDLG_HXX
#define _SFXIMGMGR_HXX
#define _SFXMNUMGR_HXX
#define _SFXMSGDESCR_HXX
#define _SFXMSGPOOL_HXX
#define _SFXSTBITEM_HXX
#define _SFXSTBMGR_HXX
#define _SFXTBXCTRL_HXX
#define _SFXTBXMGR_HXX
#define _SFX_TEMPLDLG_HXX

#define _SI_DLL_HXX
#define _SIDLL_HXX
#define _SI_NOITEMS
#define _SI_NOOTHERFORMS
#define _SI_NOSBXCONTROLS
#define _SINOSBXCONTROLS
#define _SI_NODRW
#define _SI_NOCONTROL

#define _SV_NOXSOUND
#define _SVDATTR_HXX
#define _SVDETC_HXX
#define _SVDIO_HXX
#define _SVDRAG_HXX
#define _SVDLAYER_HXX
#define _SVDXOUT_HXX

#define _SVX_DAILDLL_HXX
#define _SVX_HYPHEN_HXX
#define _SVX_IMPGRF_HXX
#define _SVX_OPTITEMS_HXX
#define _SVX_OPTGERL_HXX
#define _SVX_OPTSAVE_HXX
#define _SVX_OPTSPELL_HXX
#define _SVX_OPTPATH_HXX
#define _SVX_OPTLINGU_HXX
#define _SVX_RULER_HXX
#define _SVX_RULRITEM_HXX
#define _SVX_SPLWRAP_HXX
#define _SVX_SPLDLG_HXX
#define _SVX_THESDLG_HXX


#ifdef _MSC_VER
#pragma hdrstop
#endif


#include <vcl/msgbox.hxx>
#include <vcl/waitobj.hxx>
#include <bf_sfx2/app.hxx>


#include "docsh.hxx"
#include "globstr.hrc"
#include "undodat.hxx"
#include "consoli.hxx"
#include "dbcolect.hxx"
#include "bf_sc.hrc"
#include "sizedev.hxx"
namespace binfilter {

// ---------------------------------------------------------------------------

//
//  ehemalige viewfunc/dbfunc Methoden
//

/*N*/ BOOL ScDocShell::IsEditable() const
/*N*/ {
/*N*/   // import into read-only document is possible - must be extended if other filters use api
/*N*/
/*N*/   return !IsReadOnly() || aDocument.IsImportingXML();
/*N*/ }

/*N*/ ScDBData* ScDocShell::GetDBData( const ScRange& rMarked, ScGetDBMode eMode, BOOL bForceMark )
/*N*/ {
/*N*/   USHORT nCol = rMarked.aStart.Col();
/*N*/   USHORT nRow = rMarked.aStart.Row();
/*N*/   USHORT nTab = rMarked.aStart.Tab();
/*N*/
/*N*/   USHORT nStartCol = nCol;
/*N*/   USHORT nStartRow = nRow;
/*N*/   USHORT nEndCol = rMarked.aEnd.Col();
/*N*/   USHORT nEndRow = rMarked.aEnd.Row();
/*N*/
/*N*/   //  Wegen #49655# nicht einfach GetDBAtCursor: Der zusammenhaengende Datenbereich
/*N*/   //  fuer "unbenannt" (GetDataArea) kann neben dem Cursor legen, also muss auch ein
/*N*/   //  benannter DB-Bereich dort gesucht werden.
/*N*/
/*N*/   ScDBData* pData = NULL;
/*N*/
/*N*/   BOOL bSelected = ( bForceMark || rMarked.aStart != rMarked.aEnd );
/*N*/
/*N*/   if ( eMode == SC_DB_OLD )
/*N*/   {
/*N*/       pData = NULL;                           // nichts gefunden
/*N*/       nStartCol = nEndCol = nCol;
/*N*/       nStartRow = nEndRow = nRow;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       if ( !bSelected )
/*N*/       {                                       // zusammenhaengender Bereich
/*N*/           nStartCol = nCol;
/*N*/           nStartRow = nRow;
/*N*/           nEndCol = nStartCol;
/*N*/           nEndRow = nStartRow;
/*N*/       }
/*N*/
/*N*/       BOOL bHasHeader = FALSE;
/*N*/
/*N*/       ScDBData* pNoNameData;
/*N*/       USHORT nNoNameIndex;
/*N*/       ScDBCollection* pColl = aDocument.GetDBCollection();
/*N*/       if ( eMode != SC_DB_IMPORT &&
/*N*/               pColl->SearchName( ScGlobal::GetRscString( STR_DB_NONAME ), nNoNameIndex ) )
/*N*/       {
/*N*/           pNoNameData = (*pColl)[nNoNameIndex];
/*N*/
/*N*/           USHORT nOldX1;                                  // alten Bereich sauber wegnehmen
/*N*/           USHORT nOldY1;                                  //! (UNDO ???)
/*N*/           USHORT nOldX2;
/*N*/           USHORT nOldY2;
/*N*/           USHORT nOldTab;
/*N*/           pNoNameData->GetArea( nOldTab, nOldX1, nOldY1, nOldX2, nOldY2 );
/*N*/
/*N*/           pNoNameData->SetSortParam( ScSortParam() );             // Parameter zuruecksetzen
/*N*/           pNoNameData->SetQueryParam( ScQueryParam() );
/*N*/           pNoNameData->SetSubTotalParam( ScSubTotalParam() );
/*N*/
/*N*/           pNoNameData->SetArea( nTab, nStartCol,nStartRow, nEndCol,nEndRow );     // neu setzen
/*N*/           pNoNameData->SetByRow( TRUE );
/*N*/           pNoNameData->SetHeader( bHasHeader );
/*N*/           pNoNameData->SetAutoFilter( FALSE );
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           String aNewName;
/*N*/           if (eMode==SC_DB_IMPORT)
/*N*/           {
/*N*/               aDocument.CompileDBFormula( TRUE );         // CreateFormulaString
/*N*/
/*N*/               String aImport = ScGlobal::GetRscString( STR_DBNAME_IMPORT );
/*N*/               long nCount = 0;
/*N*/               USHORT nDummy;
/*N*/               do
/*N*/               {
/*N*/                   ++nCount;
/*N*/                   aNewName = aImport;
/*N*/                   aNewName += String::CreateFromInt32( nCount );
/*N*/               }
/*N*/               while (pColl->SearchName( aNewName, nDummy ));
/*N*/           }
/*N*/           else
/*N*/               aNewName = ScGlobal::GetRscString( STR_DB_NONAME );
/*N*/           pNoNameData = new ScDBData( aNewName, nTab,
/*N*/                               nStartCol,nStartRow, nEndCol,nEndRow,
/*N*/                               TRUE, bHasHeader );
/*N*/           pColl->Insert( pNoNameData );
/*N*/
/*N*/           //  neuen Bereich am Sba anmelden nicht mehr noetig
/*N*/
/*N*/           //  "Import1" etc am Navigator bekanntmachen
/*N*/           if (eMode==SC_DB_IMPORT)
/*N*/               SFX_APP()->Broadcast( SfxSimpleHint( SC_HINT_DBAREAS_CHANGED ) );
/*N*/       }
/*N*/       pData = pNoNameData;
/*N*/   }
/*N*/
/*N*/   return pData;
/*N*/ }


        //  Hoehen anpassen
        //! mit docfunc zusammenfassen

/*N*/ BOOL ScDocShell::AdjustRowHeight( USHORT nStartRow, USHORT nEndRow, USHORT nTab )
/*N*/ {
/*N*/   ScSizeDeviceProvider aProv(this);
/*N*/   Fraction aZoom(1,1);
/*N*/   BOOL bChange = aDocument.SetOptimalHeight( nStartRow,nEndRow, nTab, 0, aProv.GetDevice(),
/*N*/                                               aProv.GetPPTX(),aProv.GetPPTY(), aZoom,aZoom, FALSE );
/*N*/   if (bChange)
/*?*/       PostPaint( 0,nStartRow,nTab, MAXCOL,MAXROW,nTab, PAINT_GRID|PAINT_LEFT );
/*N*/
/*N*/   return bChange;
/*N*/ }

/*N*/ void ScDocShell::UpdateAllRowHeights()
/*N*/ {
/*N*/   // update automatic row heights
/*N*/
/*N*/   ScSizeDeviceProvider aProv(this);
/*N*/   Fraction aZoom(1,1);
/*N*/   USHORT nTabCnt = aDocument.GetTableCount();
/*N*/   for (USHORT nTab=0; nTab<nTabCnt; nTab++)
/*N*/       aDocument.SetOptimalHeight( 0,MAXROW, nTab,0, aProv.GetDevice(),
/*N*/                                   aProv.GetPPTX(),aProv.GetPPTY(), aZoom,aZoom, FALSE );
/*N*/ }



/*N*/ String lcl_GetAreaName( ScDocument* pDoc, ScArea* pArea )
/*N*/ {
/*N*/   String aName;
/*N*/   pDoc->GetName( pArea->nTab, aName );
/*N*/   return aName;
/*N*/ }

/*N*/ void ScDocShell::DoConsolidate( const ScConsolidateParam& rParam, BOOL bRecord )
/*N*/ {
/*N*/   ScConsData aData;
/*N*/
/*N*/   USHORT nPos;
/*N*/   USHORT nColSize = 0;
/*N*/   USHORT nRowSize = 0;
/*N*/   BOOL bErr = FALSE;
/*N*/   for (nPos=0; nPos<rParam.nDataAreaCount; nPos++)
/*N*/   {
/*N*/       ScArea* pArea = rParam.ppDataAreas[nPos];
/*N*/       nColSize = Max( nColSize, USHORT( pArea->nColEnd - pArea->nColStart + 1 ) );
/*N*/       nRowSize = Max( nRowSize, USHORT( pArea->nRowEnd - pArea->nRowStart + 1 ) );
/*N*/
/*N*/                                       // Test, ob Quelldaten verschoben wuerden
/*N*/       if (rParam.bReferenceData)
/*N*/           if (pArea->nTab == rParam.nTab && pArea->nRowEnd >= rParam.nRow)
/*N*/               bErr = TRUE;
/*N*/   }
/*N*/
/*N*/   if (bErr)
/*N*/   {
/*N*/       InfoBox aBox( GetDialogParent(),
/*N*/               ScGlobal::GetRscString( STR_CONSOLIDATE_ERR1 ) );
/*N*/       aBox.Execute();
/*N*/       return;
/*N*/   }
/*N*/
/*N*/   //      ausfuehren
/*N*/
/*N*/   WaitObject aWait( GetDialogParent() );
/*N*/   ScDocShellModificator aModificator( *this );
/*N*/
/*N*/   ScRange aOldDest;
/*N*/   ScDBData* pDestData = aDocument.GetDBAtCursor( rParam.nCol, rParam.nRow, rParam.nTab, TRUE );
/*N*/   if (pDestData)
/*N*/       pDestData->GetArea(aOldDest);
/*N*/
/*N*/   aData.SetSize( nColSize, nRowSize );
/*N*/   aData.SetFlags( rParam.eFunction, rParam.bByCol, rParam.bByRow, rParam.bReferenceData );
/*N*/   if ( rParam.bByCol || rParam.bByRow )
/*N*/       for (nPos=0; nPos<rParam.nDataAreaCount; nPos++)
/*N*/       {
/*N*/           ScArea* pArea = rParam.ppDataAreas[nPos];
/*N*/           aData.AddFields( &aDocument, pArea->nTab, pArea->nColStart, pArea->nRowStart,
/*N*/                                                       pArea->nColEnd, pArea->nRowEnd );
/*N*/       }
/*N*/   aData.DoneFields();
/*N*/   for (nPos=0; nPos<rParam.nDataAreaCount; nPos++)
/*N*/   {
/*N*/       ScArea* pArea = rParam.ppDataAreas[nPos];
/*N*/       aData.AddData( &aDocument, pArea->nTab, pArea->nColStart, pArea->nRowStart,
/*N*/                                                   pArea->nColEnd, pArea->nRowEnd );
/*N*/       aData.AddName( lcl_GetAreaName(&aDocument,pArea) );
/*N*/   }
/*N*/
/*N*/   aData.GetSize( nColSize, nRowSize );
/*N*/   if (bRecord && nColSize && nRowSize)
/*N*/   {
/*N*/       pDestData ? new ScDBData(*pDestData) : NULL;
/*N*/
/*N*/       ScArea aDestArea( rParam.nTab, rParam.nCol, rParam.nRow,
/*N*/                           rParam.nCol+nColSize-1, rParam.nRow+nRowSize-1 );
/*N*/       if (rParam.bByCol) ++aDestArea.nColEnd;
/*N*/       if (rParam.bByRow) ++aDestArea.nRowEnd;
/*N*/   }
/*N*/
/*N*/   if (pDestData)                                      // Zielbereich loeschen / anpassen
/*N*/   {
/*N*/       aDocument.DeleteAreaTab(aOldDest, IDF_CONTENTS);
/*N*/       pDestData->SetArea( rParam.nTab, rParam.nCol, rParam.nRow,
/*N*/                           rParam.nCol + nColSize - 1, rParam.nRow + nRowSize - 1 );
/*N*/       pDestData->SetHeader( rParam.bByRow );
/*N*/   }
/*N*/
/*N*/   aData.OutputToDocument( &aDocument, rParam.nCol, rParam.nRow, rParam.nTab );
/*N*/
/*N*/   USHORT nPaintStartCol = rParam.nCol;
/*N*/   USHORT nPaintStartRow = rParam.nRow;
/*N*/   USHORT nPaintEndCol = nPaintStartCol + nColSize - 1;
/*N*/   USHORT nPaintEndRow = nPaintStartRow + nRowSize - 1;
/*N*/   USHORT nPaintFlags = PAINT_GRID;
/*N*/   if (rParam.bByCol)
/*N*/       ++nPaintEndRow;
/*N*/   if (rParam.bByRow)
/*N*/       ++nPaintEndCol;
/*N*/   if (rParam.bReferenceData)
/*N*/   {
/*N*/       nPaintStartCol = 0;
/*N*/       nPaintEndCol = MAXCOL;
/*N*/       nPaintEndRow = MAXROW;
/*N*/       nPaintFlags |= PAINT_LEFT | PAINT_SIZE;
/*N*/   }
/*N*/   if (pDestData)
/*N*/   {
/*N*/       if ( aOldDest.aEnd.Col() > nPaintEndCol )
/*N*/           nPaintEndCol = aOldDest.aEnd.Col();
/*N*/       if ( aOldDest.aEnd.Row() > nPaintEndRow )
/*N*/           nPaintEndRow = aOldDest.aEnd.Row();
/*N*/   }
/*N*/   PostPaint( nPaintStartCol, nPaintStartRow, rParam.nTab,
/*N*/               nPaintEndCol, nPaintEndRow, rParam.nTab, nPaintFlags );
/*N*/   aModificator.SetDocumentModified();
/*N*/ }

/*N*/ void ScDocShell::UseScenario( USHORT nTab, const String& rName, BOOL /*bRecord*/ )
/*N*/ {
/*N*/   if (!aDocument.IsScenario(nTab))
/*N*/   {
/*N*/       USHORT  nTabCount = aDocument.GetTableCount();
/*N*/       USHORT  nSrcTab = USHRT_MAX;
/*N*/       USHORT  nEndTab = nTab;
/*N*/       String aCompare;
/*N*/       while ( nEndTab+1 < nTabCount && aDocument.IsScenario(nEndTab+1) )
/*N*/       {
/*N*/           ++nEndTab;
/*N*/           if (nSrcTab > MAXTAB)           // noch auf der Suche nach dem Szenario?
/*N*/           {
/*N*/               aDocument.GetName( nEndTab, aCompare );
/*N*/               if (aCompare == rName)
/*N*/                   nSrcTab = nEndTab;      // gefunden
/*N*/           }
/*N*/       }
/*N*/       if ( !(nSrcTab <= MAXTAB) )
/*N*/       {
/*N*/           InfoBox aBox(GetDialogParent(),
/*N*/               ScGlobal::GetRscString( STR_SCENARIO_NOTFOUND ) );
/*N*/           aBox.Execute();
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/       OSL_FAIL( "UseScenario auf Szenario-Blatt" );
/*N*/ }


/*N*/ IMPL_LINK( ScDocShell, RefreshDBDataHdl, ScDBData*, EMPTYARG )
/*N*/ {
    DBG_BF_ASSERT(0, "STRIP");  // IMPL_LINK()
    return 0;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
