/*************************************************************************
 *
 *  $RCSfile: sc_docsh5.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:39:41 $
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

// System - Includes -----------------------------------------------------

#define _BASEDLGS_HXX
#define _BIGINT_HXX
#define _CACHESTR_HXX
//#define _CLIP_HXX
#define _CONFIG_HXX
#define _CURSOR_HXX
//#define _COLOR_HXX
//#define _CTRLBOX_HXX
//#define _CTRLTOOL_HXX
#define _DIALOGS_HXX
#define _DLGCFG_HXX
#define _DYNARR_HXX
#define _EXTATTR_HXX
//#define _FIELD_HXX
#define _FILDLG_HXX
//#define _FILTER_HXX
#define _FONTDLG_HXX
#define _FRM3D_HXX
//#define _GRAPH_HXX
//#define _GDIMTF_HXX
#define _INTRO_HXX
#define _ISETBWR_HXX
#define _NO_SVRTF_PARSER_HXX
//#define _MDIFRM_HXX
#define _MACRODLG_HXX
#define _MODALDLG_HXX
#define _MOREBUTTON_HXX
//#define _MAPMOD_HXX
#define _OUTLINER_HXX
//#define _PAL_HXX
#define _PASSWD_HXX
//#define _PRNDLG_HXX   //
#define _POLY_HXX
#define _PVRWIN_HXX
#define _QUEUE_HXX
#define _RULER_HXX
#define _SCRWIN_HXX
//#define _SELENG_HXX
#define _SETBRW_HXX
//#define _SOUND_HXX
#define _STACK_HXX
//#define _STATUS_HXX ***
#define _STDMENU_HXX
//#define _STDCTRL_HXX
//#define _SYSDLG_HXX
//#define _TAB_HXX
#define _TABBAR_HXX
//#define _TREELIST_HXX
//#define _VALUESET_HXX
#define _VCBRW_HXX
#define _VCTRLS_HXX
//#define _VCATTR_HXX
#define _VCSBX_HXX
#define _VCONT_HXX
#define _VDRWOBJ_HXX
//#define _VIEWFAC_HXX


#define _SFX_PRNMON_HXX
#define _SFX_RESMGR_HXX
//#define _SFX_SAVEOPT_HXX
#define _SFX_TEMPLDLG_HXX
//#define _SFXAPP_HXX
#define _SFXBASIC_HXX
//#define _SFXCTRLITEM_HXX
//#define _SFXDISPATCH_HXX
#define _SFXFILEDLG_HXX
#define _SFXIMGMGR_HXX
#define _SFXMNUMGR_HXX
//#define _SFXMSG_HXX
#define _SFXMSGDESCR_HXX
#define _SFXMSGPOOL_HXX
//#define _SFXOBJFACE_HXX
//#define _SFXREQUEST_HXX
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


#ifdef PCH
#include "ui_pch.hxx"
#endif

#pragma hdrstop


#include "scitems.hxx"
#include <vcl/svapp.hxx>
#include <vcl/msgbox.hxx>
#include <vcl/waitobj.hxx>
#include <bf_sfx2/app.hxx>
#include <bf_sfx2/bindings.hxx>
#include <svtools/smplhint.hxx>

#include <com/sun/star/sdbc/XResultSet.hpp>

// INCLUDE ---------------------------------------------------------------

#include "docsh.hxx"
#include "global.hxx"
#include "globstr.hrc"
#include "undodat.hxx"
#include "undotab.hxx"
#include "undoblk.hxx"
//#include "pivot.hxx"
#include "dpobject.hxx"
#include "dpshttab.hxx"
#include "dbdocfun.hxx"
#include "consoli.hxx"
#include "dbcolect.hxx"
#include "olinetab.hxx"
#include "patattr.hxx"
#include "attrib.hxx"
#include "docpool.hxx"
#include "uiitems.hxx"
#include "bf_sc.hrc"
#include "waitoff.hxx"
#include "sizedev.hxx"
namespace binfilter {

// ---------------------------------------------------------------------------

//
//  ehemalige viewfunc/dbfunc Methoden
//

/*N*/ void ScDocShell::ErrorMessage( USHORT nGlobStrId )
/*N*/ {
/*N*/   //! StopMarking an der (aktiven) View?
/*N*/
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 Window* pParent = GetDialogParent();
//STRIP001 /*?*/    ScWaitCursorOff aWaitOff( pParent );
//STRIP001 /*?*/    BOOL bFocus = pParent && pParent->HasFocus();
//STRIP001 /*?*/
//STRIP001 /*?*/    if(nGlobStrId==STR_PROTECTIONERR)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        if(IsReadOnly())
//STRIP001 /*?*/        {
//STRIP001 /*?*/            nGlobStrId=STR_READONLYERR;
//STRIP001 /*?*/        }
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    InfoBox aBox( pParent, ScGlobal::GetRscString( nGlobStrId ) );
//STRIP001 /*?*/    aBox.Execute();
//STRIP001 /*?*/    if (bFocus)
//STRIP001 /*?*/        pParent->GrabFocus();
/*N*/ }

/*N*/ BOOL ScDocShell::IsEditable() const
/*N*/ {
/*N*/   // import into read-only document is possible - must be extended if other filters use api
/*N*/
/*N*/   return !IsReadOnly() || aDocument.IsImportingXML();
/*N*/ }

/*N*/ void ScDocShell::DBAreaDeleted( USHORT nTab, USHORT nX1, USHORT nY1, USHORT nX2, USHORT nY2 )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ScDocShellModificator aModificator( *this );
//STRIP001 /*?*/    aDocument.RemoveFlagsTab( nX1, nY1, nX2, nY1, nTab, SC_MF_AUTO );
//STRIP001 /*?*/    PostPaint( nX1, nY1, nTab, nX2, nY1, nTab, PAINT_GRID );
//STRIP001 /*?*/    aModificator.SetDocumentModified();
/*N*/ }

//STRIP001 ScDBData* lcl_GetDBNearCursor( ScDBCollection* pColl, USHORT nCol, USHORT nRow, USHORT nTab )
//STRIP001 {
//STRIP001  //! nach document/dbcolect verschieben
//STRIP001
//STRIP001  if (!pColl)
//STRIP001      return NULL;
//STRIP001
//STRIP001  ScDBData* pNoNameData = NULL;
//STRIP001  ScDBData* pNearData = NULL;
//STRIP001  USHORT nCount = pColl->GetCount();
//STRIP001  String aNoName = ScGlobal::GetRscString( STR_DB_NONAME );
//STRIP001  USHORT nAreaTab, nStartCol, nStartRow, nEndCol, nEndRow;
//STRIP001  for (USHORT i = 0; i < nCount; i++)
//STRIP001  {
//STRIP001      ScDBData* pDB = (*pColl)[i];
//STRIP001      pDB->GetArea( nAreaTab, nStartCol, nStartRow, nEndCol, nEndRow );
//STRIP001      if ( nTab == nAreaTab && nCol+1 >= nStartCol && nCol <= nEndCol+1 &&
//STRIP001                               nRow+1 >= nStartRow && nRow <= nEndRow+1 )
//STRIP001      {
//STRIP001          if ( pDB->GetName() == aNoName )
//STRIP001              pNoNameData = pDB;
//STRIP001          else if ( nCol < nStartCol || nCol > nEndCol || nRow < nStartRow || nRow > nEndRow )
//STRIP001          {
//STRIP001              if (!pNearData)
//STRIP001                  pNearData = pDB;    // ersten angrenzenden Bereich merken
//STRIP001          }
//STRIP001          else
//STRIP001              return pDB;             // nicht "unbenannt" und Cursor steht wirklich drin
//STRIP001      }
//STRIP001  }
//STRIP001  if (pNearData)
//STRIP001      return pNearData;               // angrenzender, wenn nichts direkt getroffen
//STRIP001  return pNoNameData;                 // "unbenannt" nur zurueck, wenn sonst nichts gefunden
//STRIP001 }

/*N*/ ScDBData* ScDocShell::GetDBData( const ScRange& rMarked, ScGetDBMode eMode, BOOL bForceMark )
/*N*/ {
/*N*/   USHORT nCol = rMarked.aStart.Col();
/*N*/   USHORT nRow = rMarked.aStart.Row();
/*N*/   USHORT nTab = rMarked.aStart.Tab();
/*N*/
/*N*/   USHORT nStartCol = nCol;
/*N*/   USHORT nStartRow = nRow;
/*N*/   USHORT nStartTab = nTab;
/*N*/   USHORT nEndCol = rMarked.aEnd.Col();
/*N*/   USHORT nEndRow = rMarked.aEnd.Row();
/*N*/   USHORT nEndTab = rMarked.aEnd.Tab();
/*N*/
/*N*/   //  Wegen #49655# nicht einfach GetDBAtCursor: Der zusammenhaengende Datenbereich
/*N*/   //  fuer "unbenannt" (GetDataArea) kann neben dem Cursor legen, also muss auch ein
/*N*/   //  benannter DB-Bereich dort gesucht werden.
/*N*/
/*N*/   ScDBData* pData = aDocument.GetDBAtArea( nTab, nStartCol, nStartRow, nEndCol, nEndRow );
/*N*/   if (!pData)
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 pData = lcl_GetDBNearCursor( aDocument.GetDBCollection(), nCol, nRow, nTab );
/*N*/
/*N*/   BOOL bSelected = ( bForceMark || rMarked.aStart != rMarked.aEnd );
/*N*/
/*N*/   BOOL bUseThis = FALSE;
/*N*/   if (pData)
/*N*/   {
/*N*/       //      Bereich nehmen, wenn nichts anderes markiert
/*N*/
/*N*/       USHORT nDummy;
/*N*/       USHORT nOldCol1;
/*N*/       USHORT nOldRow1;
/*N*/       USHORT nOldCol2;
/*N*/       USHORT nOldRow2;
/*N*/       pData->GetArea( nDummy, nOldCol1,nOldRow1, nOldCol2,nOldRow2 );
/*N*/       BOOL bIsNoName = ( pData->GetName() == ScGlobal::GetRscString( STR_DB_NONAME ) );
/*N*/
/*N*/       if (!bSelected)
/*N*/       {
/*N*/           bUseThis = TRUE;
/*N*/           if ( bIsNoName && eMode == SC_DB_MAKE )
/*N*/           {
/*N*/               //  wenn nichts markiert, "unbenannt" auf zusammenhaengenden Bereich anpassen
/*N*/               nStartCol = nCol;
/*N*/               nStartRow = nRow;
/*N*/               nEndCol = nStartCol;
/*N*/               nEndRow = nStartRow;
/*N*/               aDocument.GetDataArea( nTab, nStartCol, nStartRow, nEndCol, nEndRow, FALSE );
/*N*/               if ( nOldCol1 != nStartCol || nOldCol2 != nEndCol || nOldRow1 != nStartRow )
/*N*/                   bUseThis = FALSE;               // passt gar nicht
/*N*/               else if ( nOldRow2 != nEndRow )
/*N*/               {
/*N*/                   //  Bereich auf neue End-Zeile erweitern
/*N*/                   pData->SetArea( nTab, nOldCol1,nOldRow1, nOldCol2,nEndRow );
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           if ( nOldCol1 == nStartCol && nOldRow1 == nStartRow &&
/*N*/                nOldCol2 == nEndCol && nOldRow2 == nEndRow )               // genau markiert?
/*N*/               bUseThis = TRUE;
/*N*/           else
/*N*/               bUseThis = FALSE;           // immer Markierung nehmen (Bug 11964)
/*N*/       }
/*N*/
/*N*/       //      fuer Import nie "unbenannt" nehmen
/*N*/
/*N*/       if ( bUseThis && eMode == SC_DB_IMPORT && bIsNoName )
/*N*/           bUseThis = FALSE;
/*N*/   }
/*N*/
/*N*/   if ( bUseThis )
/*N*/   {
/*N*/       pData->GetArea( nStartTab, nStartCol,nStartRow, nEndCol,nEndRow );
/*N*/       nEndTab = nStartTab;
/*N*/   }
/*N*/   else if ( eMode == SC_DB_OLD )
/*N*/   {
/*N*/       pData = NULL;                           // nichts gefunden
/*N*/       nStartCol = nEndCol = nCol;
/*N*/       nStartRow = nEndRow = nRow;
/*N*/       nStartTab = nEndTab = nTab;
/*N*/ //        bMark = FALSE;                          // nichts zu markieren
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       if ( bSelected )
/*N*/       {
/*N*/ //            bMark = FALSE;
/*N*/       }
/*N*/       else
/*N*/       {                                       // zusammenhaengender Bereich
/*N*/           nStartCol = nCol;
/*N*/           nStartRow = nRow;
/*N*/           nEndCol = nStartCol;
/*N*/           nEndRow = nStartRow;
/*N*/           aDocument.GetDataArea( nTab, nStartCol, nStartRow, nEndCol, nEndRow, FALSE );
/*N*/       }
/*N*/
/*N*/       BOOL bHasHeader = aDocument.HasColHeader( nStartCol,nStartRow, nEndCol,nEndRow, nTab );
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
/*N*/           DBAreaDeleted( nOldTab, nOldX1, nOldY1, nOldX2, nOldY2 );
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
/*N*/           ScDBCollection* pUndoColl = NULL;
/*N*/
/*N*/           String aNewName;
/*N*/           if (eMode==SC_DB_IMPORT)
/*N*/           {
/*N*/               aDocument.CompileDBFormula( TRUE );         // CreateFormulaString
/*N*/               pUndoColl = new ScDBCollection( *pColl );   // Undo fuer Import1-Bereich
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
/*N*/           if ( pUndoColl )
/*N*/           {
/*?*/               DBG_BF_ASSERT(0, "STRIP"); //STRIP001 aDocument.CompileDBFormula( FALSE );      // CompileFormulaString
//STRIP001 /*?*/
//STRIP001 /*?*/                ScDBCollection* pRedoColl = new ScDBCollection( *pColl );
//STRIP001 /*?*/                GetUndoManager()->AddUndoAction( new ScUndoDBData( this, pUndoColl, pRedoColl ) );
/*N*/           }
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
/*N*/ //    if (bMark)
/*N*/ //        MarkRange( ScRange( nStartCol, nStartRow, nTab, nEndCol, nEndRow, nTab ), FALSE );
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

//STRIP001 void ScDocShell::PivotUpdate( ScPivot* pOldPivot, ScPivot* pNewPivot, BOOL bRecord, BOOL bApi )
//STRIP001 {
//STRIP001  DBG_ERRORFILE("PivotUpdate is obsolete!");
//STRIP001 }

//STRIP001 void ScDocShell::RefreshPivotTables( const ScRange& rSource )
//STRIP001 {
//STRIP001  //! rename to RefreshDataPilotTables?
//STRIP001
//STRIP001  ScDPCollection* pColl = aDocument.GetDPCollection();
//STRIP001  if ( pColl )
//STRIP001  {
//STRIP001      //  DataPilotUpdate doesn't modify the collection order like PivotUpdate did,
//STRIP001      //  so a simple loop can be used.
//STRIP001
//STRIP001      USHORT nCount = pColl->GetCount();
//STRIP001      for ( USHORT i=0; i<nCount; i++ )
//STRIP001      {
//STRIP001          ScDPObject* pOld = (*pColl)[i];
//STRIP001          if ( pOld )
//STRIP001          {
//STRIP001              const ScSheetSourceDesc* pSheetDesc = pOld->GetSheetDesc();
//STRIP001              if ( pSheetDesc && pSheetDesc->aSourceRange.Intersects( rSource ) )
//STRIP001              {
//STRIP001                  ScDPObject* pNew = new ScDPObject( *pOld );
//STRIP001                  ScDBDocFunc aFunc( *this );
//STRIP001                  aFunc.DataPilotUpdate( pOld, pNew, TRUE, FALSE );
//STRIP001                  delete pNew;    // DataPilotUpdate copies settings from "new" object
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*N*/ String lcl_GetAreaName( ScDocument* pDoc, ScArea* pArea )
/*N*/ {
/*N*/   String aName;
/*N*/   BOOL bOk = FALSE;
/*N*/   ScDBData* pData = pDoc->GetDBAtArea( pArea->nTab, pArea->nColStart, pArea->nRowStart,
/*N*/                                                       pArea->nColEnd, pArea->nRowEnd );
/*N*/   if (pData)
/*N*/   {
/*N*/       pData->GetName( aName );
/*N*/       if ( aName != ScGlobal::GetRscString( STR_DB_NONAME ) )
/*N*/           bOk = TRUE;
/*N*/   }
/*N*/
/*N*/   if (!bOk)
/*N*/       pDoc->GetName( pArea->nTab, aName );
/*N*/
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
/*N*/       ScDBData* pUndoData = pDestData ? new ScDBData(*pDestData) : NULL;
/*N*/
/*N*/       USHORT nDestTab = rParam.nTab;
/*N*/       ScArea aDestArea( rParam.nTab, rParam.nCol, rParam.nRow,
/*N*/                           rParam.nCol+nColSize-1, rParam.nRow+nRowSize-1 );
/*N*/       if (rParam.bByCol) ++aDestArea.nColEnd;
/*N*/       if (rParam.bByRow) ++aDestArea.nRowEnd;
/*N*/
/*N*/       if (rParam.bReferenceData)
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 USHORT nTabCount = aDocument.GetTableCount();
//STRIP001 /*?*/            USHORT nInsertCount = aData.GetInsertCount();
//STRIP001 /*?*/
//STRIP001 /*?*/            // alte Outlines
//STRIP001 /*?*/            ScOutlineTable* pTable = aDocument.GetOutlineTable( nDestTab );
//STRIP001 /*?*/            ScOutlineTable* pUndoTab = pTable ? new ScOutlineTable( *pTable ) : NULL;
//STRIP001 /*?*/
//STRIP001 /*?*/            ScDocument* pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 /*?*/            pUndoDoc->InitUndo( &aDocument, 0, nTabCount-1, FALSE, TRUE );
//STRIP001 /*?*/
//STRIP001 /*?*/            // Zeilenstatus
//STRIP001 /*?*/            aDocument.CopyToDocument( 0,0,nDestTab, MAXCOL,MAXROW,nDestTab,
//STRIP001 /*?*/                                    IDF_NONE, FALSE, pUndoDoc );
//STRIP001 /*?*/
//STRIP001 /*?*/            // alle Formeln
//STRIP001 /*?*/            aDocument.CopyToDocument( 0,0,0, MAXCOL,MAXROW,nTabCount-1,
//STRIP001 /*?*/                                        IDF_FORMULA, FALSE, pUndoDoc );
//STRIP001 /*?*/
//STRIP001 /*?*/            // komplette Ausgangszeilen
//STRIP001 /*?*/            aDocument.CopyToDocument( 0,aDestArea.nRowStart,nDestTab,
//STRIP001 /*?*/                                    MAXCOL,aDestArea.nRowEnd,nDestTab,
//STRIP001 /*?*/                                    IDF_ALL, FALSE, pUndoDoc );
//STRIP001 /*?*/
//STRIP001 /*?*/            // alten Ausgabebereich
//STRIP001 /*?*/            if (pDestData)
//STRIP001 /*?*/                aDocument.CopyToDocument( aOldDest, IDF_ALL, FALSE, pUndoDoc );
//STRIP001 /*?*/
//STRIP001 /*?*/            GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                    new ScUndoConsolidate( this, aDestArea, rParam, pUndoDoc,
//STRIP001 /*?*/                                            TRUE, nInsertCount, pUndoTab, pUndoData ) );
/*N*/       }
/*N*/       else
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ScDocument* pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 /*?*/            pUndoDoc->InitUndo( &aDocument, aDestArea.nTab, aDestArea.nTab );
//STRIP001 /*?*/
//STRIP001 /*?*/            aDocument.CopyToDocument( aDestArea.nColStart, aDestArea.nRowStart, aDestArea.nTab,
//STRIP001 /*?*/                                    aDestArea.nColEnd, aDestArea.nRowEnd, aDestArea.nTab,
//STRIP001 /*?*/                                    IDF_ALL, FALSE, pUndoDoc );
//STRIP001 /*?*/
//STRIP001 /*?*/            // alten Ausgabebereich
//STRIP001 /*?*/            if (pDestData)
//STRIP001 /*?*/                aDocument.CopyToDocument( aOldDest, IDF_ALL, FALSE, pUndoDoc );
//STRIP001 /*?*/
//STRIP001 /*?*/            GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                    new ScUndoConsolidate( this, aDestArea, rParam, pUndoDoc,
//STRIP001 /*?*/                                            FALSE, 0, NULL, pUndoData ) );
/*N*/       }
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

/*N*/ void ScDocShell::UseScenario( USHORT nTab, const String& rName, BOOL bRecord )
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
/*N*/       if (nSrcTab <= MAXTAB)
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if ( aDocument.TestCopyScenario( nSrcTab, nTab ) )            // Zellschutz testen
//STRIP001 /*?*/            {
//STRIP001 /*?*/                ScDocShellModificator aModificator( *this );
//STRIP001 /*?*/                ScMarkData aScenMark;
//STRIP001 /*?*/                aDocument.MarkScenario( nSrcTab, nTab, aScenMark );
//STRIP001 /*?*/                ScRange aMultiRange;
//STRIP001 /*?*/                aScenMark.GetMultiMarkArea( aMultiRange );
//STRIP001 /*?*/                USHORT nStartCol = aMultiRange.aStart.Col();
//STRIP001 /*?*/                USHORT nStartRow = aMultiRange.aStart.Row();
//STRIP001 /*?*/                USHORT nEndCol = aMultiRange.aEnd.Col();
//STRIP001 /*?*/                USHORT nEndRow = aMultiRange.aEnd.Row();
//STRIP001 /*?*/
//STRIP001 /*?*/                if (bRecord)
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    ScDocument* pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 /*?*/                    pUndoDoc->InitUndo( &aDocument, nTab,nEndTab );             // auch alle Szenarien
//STRIP001 /*?*/                    //  angezeigte Tabelle:
//STRIP001 /*?*/                    aDocument.CopyToDocument( nStartCol,nStartRow,nTab,
//STRIP001 /*?*/                                    nEndCol,nEndRow,nTab, IDF_ALL,TRUE, pUndoDoc, &aScenMark );
//STRIP001 /*?*/                    //  Szenarien
//STRIP001 /*?*/                    for (USHORT i=nTab+1; i<=nEndTab; i++)
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        pUndoDoc->SetScenario( i, TRUE );
//STRIP001 /*?*/                        String aComment;
//STRIP001 /*?*/                        Color  aColor;
//STRIP001 /*?*/                        USHORT nScenFlags;
//STRIP001 /*?*/                        aDocument.GetScenarioData( i, aComment, aColor, nScenFlags );
//STRIP001 /*?*/                        pUndoDoc->SetScenarioData( i, aComment, aColor, nScenFlags );
//STRIP001 /*?*/                        BOOL bActive = aDocument.IsActiveScenario( i );
//STRIP001 /*?*/                        pUndoDoc->SetActiveScenario( i, bActive );
//STRIP001 /*?*/                        //  Bei Zurueckkopier-Szenarios auch Inhalte
//STRIP001 /*?*/                        if ( nScenFlags & SC_SCENARIO_TWOWAY )
//STRIP001 /*?*/                            aDocument.CopyToDocument( 0,0,i, MAXCOL,MAXROW,i,
//STRIP001 /*?*/                                                        IDF_ALL,FALSE, pUndoDoc );
//STRIP001 /*?*/                    }
//STRIP001 /*?*/
//STRIP001 /*?*/                    GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                        new ScUndoUseScenario( this, aScenMark,
//STRIP001 /*?*/                                        ScArea( nTab,nStartCol,nStartRow,nEndCol,nEndRow ),
//STRIP001 /*?*/                                        pUndoDoc, rName ) );
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/                aDocument.CopyScenario( nSrcTab, nTab );
//STRIP001 /*?*/                aDocument.SetDirty();
//STRIP001 /*?*/
//STRIP001 /*?*/                //  alles painten, weil in anderen Bereichen das aktive Szenario
//STRIP001 /*?*/                //  geaendert sein kann
//STRIP001 /*?*/                //! nur, wenn sichtbare Rahmen vorhanden?
//STRIP001 /*?*/                PostPaint( 0,0,nTab, MAXCOL,MAXROW,nTab, PAINT_GRID );
//STRIP001 /*?*/                aModificator.SetDocumentModified();
//STRIP001 /*?*/            }
//STRIP001 /*?*/            else
//STRIP001 /*?*/            {
//STRIP001 /*?*/                InfoBox aBox(GetDialogParent(),
//STRIP001 /*?*/                    ScGlobal::GetRscString( STR_PROTECTIONERR ) );
//STRIP001 /*?*/                aBox.Execute();
//STRIP001 /*?*/            }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           InfoBox aBox(GetDialogParent(),
/*N*/               ScGlobal::GetRscString( STR_SCENARIO_NOTFOUND ) );
/*N*/           aBox.Execute();
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/       DBG_ERROR( "UseScenario auf Szenario-Blatt" );
/*N*/ }

/*N*/ void ScDocShell::ModifyScenario( USHORT nTab, const String& rName, const String& rComment,
/*N*/                                   const Color& rColor, USHORT nFlags )
/*N*/ {
/*?*/   //  Undo
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 String aOldName;
//STRIP001 /*?*/    aDocument.GetName( nTab, aOldName );
//STRIP001 /*?*/    String aOldComment;
//STRIP001 /*?*/    Color aOldColor;
//STRIP001 /*?*/    USHORT nOldFlags;
//STRIP001 /*?*/    aDocument.GetScenarioData( nTab, aOldComment, aOldColor, nOldFlags );
//STRIP001 /*?*/    GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/        new ScUndoScenarioFlags( this, nTab,
//STRIP001 /*?*/                aOldName, rName, aOldComment, rComment,
//STRIP001 /*?*/                aOldColor, rColor, nOldFlags, nFlags ) );
//STRIP001 /*?*/
//STRIP001 /*?*/    //  ausfuehren
//STRIP001 /*?*/    ScDocShellModificator aModificator( *this );
//STRIP001 /*?*/    aDocument.RenameTab( nTab, rName );
//STRIP001 /*?*/    aDocument.SetScenarioData( nTab, rComment, rColor, nFlags );
//STRIP001 /*?*/    PostPaintGridAll();
//STRIP001 /*?*/    aModificator.SetDocumentModified();
//STRIP001 /*?*/
//STRIP001 /*?*/    if ( rName != aOldName )
//STRIP001 /*?*/        SFX_APP()->Broadcast( SfxSimpleHint( SC_HINT_TABLES_CHANGED ) );
//STRIP001 /*?*/
//STRIP001 /*?*/    SfxBindings* pBindings = GetViewBindings();
//STRIP001 /*?*/    if (pBindings)
//STRIP001 /*?*/        pBindings->Invalidate( SID_SELECT_SCENARIO );
/*N*/ }

/*N*/ USHORT ScDocShell::MakeScenario( USHORT nTab, const String& rName, const String& rComment,
/*N*/                                   const Color& rColor, USHORT nFlags,
/*N*/                                   ScMarkData& rMark, BOOL bRecord )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return 0; //STRIP001 rMark.MarkToMulti();
//STRIP001 /*?*/    if (rMark.IsMultiMarked())
//STRIP001 /*?*/    {
//STRIP001 /*?*/        USHORT nNewTab = nTab + 1;
//STRIP001 /*?*/        while (aDocument.IsScenario(nNewTab))
//STRIP001 /*?*/            ++nNewTab;
//STRIP001 /*?*/
//STRIP001 /*?*/        BOOL bCopyAll = ( (nFlags & SC_SCENARIO_COPYALL) != 0 );
//STRIP001 /*?*/        const ScMarkData* pCopyMark = NULL;
//STRIP001 /*?*/        if (!bCopyAll)
//STRIP001 /*?*/            pCopyMark = &rMark;
//STRIP001 /*?*/
//STRIP001 /*?*/        ScDocShellModificator aModificator( *this );
//STRIP001 /*?*/
//STRIP001 /*?*/        if (aDocument.CopyTab( nTab, nNewTab, pCopyMark ))
//STRIP001 /*?*/        {
//STRIP001 /*?*/            if (bRecord)
//STRIP001 /*?*/            {
//STRIP001 /*?*/                ScDocument* pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 /*?*/                pUndoDoc->InitUndo( &aDocument, nTab,nTab );
//STRIP001 /*?*/                GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                        new ScUndoMakeScenario( this, nTab, nNewTab, pUndoDoc,
//STRIP001 /*?*/                                                rName, rComment, rColor, nFlags, rMark ));
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            aDocument.RenameTab( nNewTab, rName, FALSE );           // ohne Formel-Update
//STRIP001 /*?*/            aDocument.SetScenario( nNewTab, TRUE );
//STRIP001 /*?*/            aDocument.SetScenarioData( nNewTab, rComment, rColor, nFlags );
//STRIP001 /*?*/
//STRIP001 /*?*/            ScMarkData aDestMark = rMark;
//STRIP001 /*?*/            aDestMark.SelectOneTable( nNewTab );
//STRIP001 /*?*/
//STRIP001 /*?*/            //!     auf Filter / Buttons / Merging testen !
//STRIP001 /*?*/
//STRIP001 /*?*/            ScPatternAttr aProtPattern( aDocument.GetPool() );
//STRIP001 /*?*/            aProtPattern.GetItemSet().Put( ScProtectionAttr( TRUE ) );
//STRIP001 /*?*/            aDocument.ApplyPatternAreaTab( 0,0, MAXCOL,MAXROW, nNewTab, aProtPattern );
//STRIP001 /*?*/
//STRIP001 /*?*/            ScPatternAttr aPattern( aDocument.GetPool() );
//STRIP001 /*?*/            aPattern.GetItemSet().Put( ScMergeFlagAttr( SC_MF_SCENARIO ) );
//STRIP001 /*?*/            aPattern.GetItemSet().Put( ScProtectionAttr( TRUE ) );
//STRIP001 /*?*/            aDocument.ApplySelectionPattern( aPattern, aDestMark );
//STRIP001 /*?*/
//STRIP001 /*?*/            if (!bCopyAll)
//STRIP001 /*?*/                aDocument.SetVisible( nNewTab, FALSE );
//STRIP001 /*?*/
//STRIP001 /*?*/            //  dies ist dann das aktive Szenario
//STRIP001 /*?*/            aDocument.CopyScenario( nNewTab, nTab, TRUE );  // TRUE - nicht aus Szenario kopieren
//STRIP001 /*?*/
//STRIP001 /*?*/            if (nFlags & SC_SCENARIO_SHOWFRAME)
//STRIP001 /*?*/                PostPaint( 0,0,nTab, MAXCOL,MAXROW,nTab, PAINT_GRID );  // Rahmen painten
//STRIP001 /*?*/            PostPaintExtras();                                          // Tabellenreiter
//STRIP001 /*?*/            aModificator.SetDocumentModified();
//STRIP001 /*?*/
//STRIP001 /*?*/            SFX_APP()->Broadcast( SfxSimpleHint( SC_HINT_TABLES_CHANGED ) );
//STRIP001 /*?*/
//STRIP001 /*?*/            return nNewTab;
//STRIP001 /*?*/        }
//STRIP001 /*?*/    }
//STRIP001 /*?*/    return nTab;
/*N*/ }

/*N*/ BOOL ScDocShell::MoveTable( USHORT nSrcTab, USHORT nDestTab, BOOL bCopy, BOOL bRecord )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ScDocShellModificator aModificator( *this );
//STRIP001 /*?*/
//STRIP001 /*?*/    if (bCopy)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        if (bRecord)
//STRIP001 /*?*/            aDocument.BeginDrawUndo();          // drawing layer must do its own undo actions
//STRIP001 /*?*/
//STRIP001 /*?*/        if (!aDocument.CopyTab( nSrcTab, nDestTab ))
//STRIP001 /*?*/        {
//STRIP001 /*?*/            //! EndDrawUndo?
//STRIP001 /*?*/            return FALSE;
//STRIP001 /*?*/        }
//STRIP001 /*?*/        else
//STRIP001 /*?*/        {
//STRIP001 /*?*/            USHORT nAdjSource = nSrcTab;
//STRIP001 /*?*/            if ( nDestTab <= nSrcTab )
//STRIP001 /*?*/                ++nAdjSource;               // new position of source table after CopyTab
//STRIP001 /*?*/
//STRIP001 /*?*/            if ( aDocument.IsTabProtected( nAdjSource ) )
//STRIP001 /*?*/                aDocument.SetTabProtection( nDestTab, TRUE, aDocument.GetTabPassword( nAdjSource ) );
//STRIP001 /*?*/
//STRIP001 /*?*/            if (bRecord)
//STRIP001 /*?*/            {
//STRIP001 /*?*/                SvUShorts aSrcList;
//STRIP001 /*?*/                SvUShorts aDestList;
//STRIP001 /*?*/                aSrcList.Insert(nSrcTab,0);
//STRIP001 /*?*/                aDestList.Insert(nDestTab,0);
//STRIP001 /*?*/                GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                        new ScUndoCopyTab( this, aSrcList, aDestList ) );
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        Broadcast( ScTablesHint( SC_TAB_COPIED, nSrcTab, nDestTab ) );
//STRIP001 /*?*/    }
//STRIP001 /*?*/    else
//STRIP001 /*?*/    {
//STRIP001 /*?*/        if ( aDocument.GetChangeTrack() )
//STRIP001 /*?*/            return FALSE;
//STRIP001 /*?*/
//STRIP001 /*?*/        if ( nSrcTab<nDestTab && nDestTab!=SC_TAB_APPEND )
//STRIP001 /*?*/            nDestTab--;
//STRIP001 /*?*/
//STRIP001 /*?*/        if ( nSrcTab == nDestTab )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            //! allow only for api calls?
//STRIP001 /*?*/            return TRUE;    // nothing to do, but valid
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        if (!aDocument.MoveTab( nSrcTab, nDestTab ))
//STRIP001 /*?*/            return FALSE;
//STRIP001 /*?*/        else if (bRecord)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            SvUShorts aSrcList;
//STRIP001 /*?*/            SvUShorts aDestList;
//STRIP001 /*?*/            aSrcList.Insert(nSrcTab,0);
//STRIP001 /*?*/            aDestList.Insert(nDestTab,0);
//STRIP001 /*?*/            GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                    new ScUndoMoveTab( this, aSrcList, aDestList ) );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        Broadcast( ScTablesHint( SC_TAB_MOVED, nSrcTab, nDestTab ) );
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    PostPaintGridAll();
//STRIP001 /*?*/    PostPaintExtras();
//STRIP001 /*?*/    aModificator.SetDocumentModified();
//STRIP001 /*?*/    SFX_APP()->Broadcast( SfxSimpleHint( SC_HINT_TABLES_CHANGED ) );
//STRIP001 /*?*/
/*?*/   return TRUE;
/*N*/ }


/*N*/ IMPL_LINK( ScDocShell, RefreshDBDataHdl, ScDBData*, pDBData )
/*N*/ {
    DBG_BF_ASSERT(0, "STRIP"); return 0; //STRIP001 ScDBDocFunc aFunc(*this);
//STRIP001
//STRIP001  BOOL bContinue = TRUE;
//STRIP001  ScImportParam aImportParam;
//STRIP001  pDBData->GetImportParam( aImportParam );
//STRIP001  if (aImportParam.bImport && !pDBData->HasImportSelection())
//STRIP001  {
//STRIP001      ScRange aRange;
//STRIP001      pDBData->GetArea( aRange );
//STRIP001         ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet> xResultSet;
//STRIP001      bContinue = aFunc.DoImport( aRange.aStart.Tab(), aImportParam, xResultSet, NULL, TRUE, FALSE ); //! Api-Flag as parameter
//STRIP001      // internal operations (sort, query, subtotal) only if no error
//STRIP001      if (bContinue)
//STRIP001      {
//STRIP001          aFunc.RepeatDB( pDBData->GetName(), TRUE, TRUE );
//STRIP001          RefreshPivotTables(aRange);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return bContinue != 0;
/*N*/ }

}
