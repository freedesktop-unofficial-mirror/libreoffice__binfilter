/*************************************************************************
 *
 *  $RCSfile: sc_documen3.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 14:36:12 $
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

#ifdef PCH
#include "core_pch.hxx"
#endif

#pragma hdrstop

#ifdef WIN
// SFX
#define _SFXAPPWIN_HXX
#define _SFX_SAVEOPT_HXX
//#define _SFX_CHILDWIN_HXX ***
#define _SFXCTRLITEM_HXX
#define _SFXPRNMON_HXX
#define _INTRO_HXX
#define _SFXMSGDESCR_HXX
#define _SFXMSGPOOL_HXX
#define _SFXFILEDLG_HXX
#define _PASSWD_HXX
#define _SFXTBXCTRL_HXX
#define _SFXSTBITEM_HXX
#define _SFXMNUITEM_HXX
#define _SFXIMGMGR_HXX
#define _SFXTBXMGR_HXX
#define _SFXSTBMGR_HXX
#define _SFX_MINFITEM_HXX
#define _SFXEVENT_HXX

//sfxdlg.hxx
//#define _SFXTABDLG_HXX
#define _BASEDLGS_HXX
#define _SFX_DINFDLG_HXX
#define _SFXDINFEDT_HXX
#define _SFX_MGETEMPL_HXX
#define _SFX_TPLPITEM_HXX
#define _SFX_STYLEDLG_HXX
#define _NEWSTYLE_HXX
#define _SFXDOCTEMPL_HXX
#define _SFXDOCTDLG_HXX
#define _SFX_TEMPLDLG_HXX
#define _SFXNEW_HXX
#define _SFXDOCMAN_HXX
//#define _SFXDOCKWIN_HXX ***

//sfxdoc.hxx
//#define _SFX_OBJSH_HXX
//#define _SFX_CLIENTSH_HXX ***
//#define _SFXDOCINF_HXX
#define _SFX_OBJFAC_HXX
#define _SFX_DOCFILT_HXX
#define _SFXDOCFILE_HXX
#define _VIEWFAC_HXX
#define _SFXVIEWFRM_HXX
//#define _SFXVIEWSH_HXX ***
#define _MDIFRM_HXX
#define _SFX_IPFRM_HXX
#define _SFX_INTERNO_HXX

#endif  //WIN

// INCLUDE ---------------------------------------------------------------

#include "scitems.hxx"
#include <bf_svx/langitem.hxx>
#include <bf_svx/srchitem.hxx>
#include <bf_svx/linkmgr.hxx>
#include <bf_sfx2/bindings.hxx>
#include <bf_sfx2/objsh.hxx>
#include <svtools/zforlist.hxx>

#include "document.hxx"
#include "attrib.hxx"
#include "cell.hxx"
#include "table.hxx"
#include "rangenam.hxx"
#include "dbcolect.hxx"
#include "pivot.hxx"
#include "docpool.hxx"
#include "poolhelp.hxx"
#include "autoform.hxx"
#include "rangelst.hxx"
#include "chartarr.hxx"
#include "refupdat.hxx"
#include "docoptio.hxx"
#include "viewopti.hxx"
#include "scextopt.hxx"
#include "brdcst.hxx"
#include "bcaslot.hxx"
#include "tablink.hxx"
#include "markdata.hxx"
#include "conditio.hxx"
#include "dociter.hxx"
#include "detdata.hxx"
#include "detfunc.hxx"
#include "scmod.hxx"        // SC_MOD
#include "inputopt.hxx"     // GetExpandRefs
#include "chartlis.hxx"
#include "bf_sc.hrc"            // SID_LINK
#include "hints.hxx"
#include "dpobject.hxx"
#include "unoguard.hxx"

using namespace com::sun::star;

//------------------------------------------------------------------------

/*N*/ ScRangeName* ScDocument::GetRangeName()
/*N*/ {
/*N*/   return pRangeName;
/*N*/ }

/*N*/ void ScDocument::SetRangeName( ScRangeName* pNewRangeName )
/*N*/ {
/*N*/   if (pRangeName)
/*N*/       delete pRangeName;
/*N*/   pRangeName = pNewRangeName;
/*N*/ }

//STRIP001 ScRangeData* ScDocument::GetRangeAtCursor(USHORT nCol, USHORT nRow, USHORT nTab,
//STRIP001                                          BOOL bStartOnly) const
//STRIP001 {
//STRIP001  if ( pRangeName )
//STRIP001      return pRangeName->GetRangeAtCursor( ScAddress( nCol, nRow, nTab ), bStartOnly );
//STRIP001  else
//STRIP001      return NULL;
//STRIP001 }

//STRIP001 ScRangeData* ScDocument::GetRangeAtBlock( const ScRange& rBlock, String* pName ) const
//STRIP001 {
//STRIP001  ScRangeData* pData = NULL;
//STRIP001  if ( pRangeName )
//STRIP001  {
//STRIP001      pData = pRangeName->GetRangeAtBlock( rBlock );
//STRIP001      if (pData && pName)
//STRIP001          *pName = pData->GetName();
//STRIP001  }
//STRIP001  return pData;
//STRIP001 }

/*N*/ ScDBCollection* ScDocument::GetDBCollection() const
/*N*/ {
/*N*/   return pDBCollection;
/*N*/ }

//STRIP001 void ScDocument::SetDBCollection( ScDBCollection* pNewDBCollection, BOOL bRemoveAutoFilter )
//STRIP001 {
//STRIP001  if ( bRemoveAutoFilter )
//STRIP001  {
//STRIP001      //  remove auto filter attribute if new db data don't contain auto filter flag
//STRIP001      //  start position is also compared, so bRemoveAutoFilter must not be set from ref-undo!
//STRIP001
//STRIP001      if ( pDBCollection )
//STRIP001      {
//STRIP001          USHORT nOldCount = pDBCollection->GetCount();
//STRIP001          for (USHORT nOld=0; nOld<nOldCount; nOld++)
//STRIP001          {
//STRIP001              ScDBData* pOldData = (*pDBCollection)[nOld];
//STRIP001              if ( pOldData->HasAutoFilter() )
//STRIP001              {
//STRIP001                  ScRange aOldRange;
//STRIP001                  pOldData->GetArea( aOldRange );
//STRIP001
//STRIP001                  BOOL bFound = FALSE;
//STRIP001                  USHORT nNewIndex = 0;
//STRIP001                  if ( pNewDBCollection &&
//STRIP001                      pNewDBCollection->SearchName( pOldData->GetName(), nNewIndex ) )
//STRIP001                  {
//STRIP001                      ScDBData* pNewData = (*pNewDBCollection)[nNewIndex];
//STRIP001                      if ( pNewData->HasAutoFilter() )
//STRIP001                      {
//STRIP001                          ScRange aNewRange;
//STRIP001                          pNewData->GetArea( aNewRange );
//STRIP001                          if ( aOldRange.aStart == aNewRange.aStart )
//STRIP001                              bFound = TRUE;
//STRIP001                      }
//STRIP001                  }
//STRIP001
//STRIP001                  if ( !bFound )
//STRIP001                  {
//STRIP001                      aOldRange.aEnd.SetRow( aOldRange.aStart.Row() );
//STRIP001                      RemoveFlagsTab( aOldRange.aStart.Col(), aOldRange.aStart.Row(),
//STRIP001                                      aOldRange.aEnd.Col(),   aOldRange.aEnd.Row(),
//STRIP001                                      aOldRange.aStart.Tab(), SC_MF_AUTO );
//STRIP001                      if (pShell)
//STRIP001                          pShell->Broadcast( ScPaintHint( aOldRange, PAINT_GRID ) );
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if (pDBCollection)
//STRIP001      delete pDBCollection;
//STRIP001  pDBCollection = pNewDBCollection;
//STRIP001 }

/*N*/ ScDBData* ScDocument::GetDBAtCursor(USHORT nCol, USHORT nRow, USHORT nTab, BOOL bStartOnly) const
/*N*/ {
/*N*/   if (pDBCollection)
/*N*/       return pDBCollection->GetDBAtCursor(nCol, nRow, nTab, bStartOnly);
/*N*/   else
/*N*/       return NULL;
/*N*/ }

/*N*/ ScDBData* ScDocument::GetDBAtArea(USHORT nTab, USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2) const
/*N*/ {
/*N*/   if (pDBCollection)
/*N*/       return pDBCollection->GetDBAtArea(nTab, nCol1, nRow1, nCol2, nRow2);
/*N*/   else
/*N*/       return NULL;
/*N*/ }

/*N*/ ScDPCollection* ScDocument::GetDPCollection()
/*N*/ {
/*N*/   if (!pDPCollection)
/*N*/       pDPCollection = new ScDPCollection(this);
/*N*/   return pDPCollection;
/*N*/ }

//STRIP001 ScDPObject* ScDocument::GetDPAtCursor(USHORT nCol, USHORT nRow, USHORT nTab) const
//STRIP001 {
//STRIP001  if (!pDPCollection)
//STRIP001      return NULL;
//STRIP001
//STRIP001  USHORT nCount = pDPCollection->GetCount();
//STRIP001  ScAddress aPos( nCol, nRow, nTab );
//STRIP001  for (USHORT i=0; i<nCount; i++)
//STRIP001      if ( (*pDPCollection)[i]->GetOutRange().In( aPos ) )
//STRIP001          return (*pDPCollection)[i];
//STRIP001
//STRIP001  return NULL;
//STRIP001 }

//STRIP001 ScPivotCollection* ScDocument::GetPivotCollection() const
//STRIP001 {
//STRIP001  return pPivotCollection;
//STRIP001 }

//STRIP001 void ScDocument::SetPivotCollection(ScPivotCollection* pNewPivotCollection)
//STRIP001 {
//STRIP001  if ( pPivotCollection && pNewPivotCollection &&
//STRIP001          *pPivotCollection == *pNewPivotCollection )
//STRIP001  {
//STRIP001      delete pNewPivotCollection;
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  if (pPivotCollection)
//STRIP001      delete pPivotCollection;
//STRIP001  pPivotCollection = pNewPivotCollection;
//STRIP001
//STRIP001  if (pPivotCollection)
//STRIP001  {
//STRIP001      USHORT nCount = pPivotCollection->GetCount();
//STRIP001      for (USHORT i=0; i<nCount; i++)
//STRIP001      {
//STRIP001          ScPivot* pPivot = (*pPivotCollection)[i];
//STRIP001          if (pPivot->CreateData())
//STRIP001              pPivot->ReleaseData();
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 ScPivot* ScDocument::GetPivotAtCursor(USHORT nCol, USHORT nRow, USHORT nTab) const
//STRIP001 {
//STRIP001  if (pPivotCollection)
//STRIP001      return pPivotCollection->GetPivotAtCursor(nCol, nRow, nTab);
//STRIP001  else
//STRIP001      return NULL;
//STRIP001 }

//STRIP001 ScChartCollection* ScDocument::GetChartCollection() const
//STRIP001 {
//STRIP001  return pChartCollection;
//STRIP001 }

//STRIP001 void ScDocument::SetChartCollection(ScChartCollection* pNewChartCollection)
//STRIP001 {
//STRIP001  if (pChartCollection)
//STRIP001      delete pChartCollection;
//STRIP001  pChartCollection = pNewChartCollection;
//STRIP001 }

//STRIP001 void ScDocument::SetChartListenerCollection(
//STRIP001          ScChartListenerCollection* pNewChartListenerCollection,
//STRIP001          BOOL bSetChartRangeLists )
//STRIP001 {
//STRIP001  ScChartListenerCollection* pOld = pChartListenerCollection;
//STRIP001  pChartListenerCollection = pNewChartListenerCollection;
//STRIP001  if ( pChartListenerCollection )
//STRIP001  {
//STRIP001      if ( pOld )
//STRIP001          pChartListenerCollection->SetDiffDirty( *pOld, bSetChartRangeLists );
//STRIP001      pChartListenerCollection->StartAllListeners();
//STRIP001  }
//STRIP001  delete pOld;
//STRIP001 }

/*N*/ void ScDocument::SetScenario( USHORT nTab, BOOL bFlag )
/*N*/ {
/*N*/   if (nTab<=MAXTAB && pTab[nTab])
/*N*/       pTab[nTab]->SetScenario(bFlag);
/*N*/ }

/*N*/ BOOL ScDocument::IsScenario( USHORT nTab ) const
/*N*/ {
/*N*/   if (nTab<=MAXTAB && pTab[nTab])
/*N*/       return pTab[nTab]->IsScenario();
/*N*/
/*N*/   return FALSE;
/*N*/ }

/*N*/ void ScDocument::SetScenarioData( USHORT nTab, const String& rComment,
/*N*/                                       const Color& rColor, USHORT nFlags )
/*N*/ {
/*N*/   if (nTab<=MAXTAB && pTab[nTab] && pTab[nTab]->IsScenario())
/*N*/   {
/*N*/       pTab[nTab]->SetScenarioComment( rComment );
/*N*/       pTab[nTab]->SetScenarioColor( rColor );
/*N*/       pTab[nTab]->SetScenarioFlags( nFlags );
/*N*/   }
/*N*/ }

/*N*/ void ScDocument::GetScenarioData( USHORT nTab, String& rComment,
/*N*/                                       Color& rColor, USHORT& rFlags ) const
/*N*/ {
/*N*/   if (nTab<=MAXTAB && pTab[nTab] && pTab[nTab]->IsScenario())
/*N*/   {
/*N*/       pTab[nTab]->GetScenarioComment( rComment );
/*N*/       rColor = pTab[nTab]->GetScenarioColor();
/*N*/       rFlags = pTab[nTab]->GetScenarioFlags();
/*N*/   }
/*N*/ }

/*N*/ BOOL ScDocument::IsLinked( USHORT nTab ) const
/*N*/ {
/*N*/   if (nTab<=MAXTAB && pTab[nTab])
/*N*/       return pTab[nTab]->IsLinked();
/*N*/   return FALSE;
/*N*/ }

/*N*/ BOOL ScDocument::GetLinkMode( USHORT nTab ) const
/*N*/ {
/*N*/   if (nTab<=MAXTAB && pTab[nTab])
/*N*/       return pTab[nTab]->GetLinkMode();
/*N*/   return SC_LINK_NONE;
/*N*/ }

/*N*/ const String& ScDocument::GetLinkDoc( USHORT nTab ) const
/*N*/ {
/*N*/   if (nTab<=MAXTAB && pTab[nTab])
/*N*/       return pTab[nTab]->GetLinkDoc();
/*N*/   return EMPTY_STRING;
/*N*/ }

/*N*/ const String& ScDocument::GetLinkFlt( USHORT nTab ) const
/*N*/ {
/*N*/   if (nTab<=MAXTAB && pTab[nTab])
/*N*/       return pTab[nTab]->GetLinkFlt();
/*N*/   return EMPTY_STRING;
/*N*/ }

/*N*/ const String& ScDocument::GetLinkOpt( USHORT nTab ) const
/*N*/ {
/*N*/   if (nTab<=MAXTAB && pTab[nTab])
/*N*/       return pTab[nTab]->GetLinkOpt();
/*N*/   return EMPTY_STRING;
/*N*/ }

/*N*/ const String& ScDocument::GetLinkTab( USHORT nTab ) const
/*N*/ {
/*N*/   if (nTab<=MAXTAB && pTab[nTab])
/*N*/       return pTab[nTab]->GetLinkTab();
/*N*/   return EMPTY_STRING;
/*N*/ }

/*N*/ ULONG ScDocument::GetLinkRefreshDelay( USHORT nTab ) const
/*N*/ {
/*N*/   if (nTab<=MAXTAB && pTab[nTab])
/*N*/       return pTab[nTab]->GetLinkRefreshDelay();
/*N*/   return 0;
/*N*/ }

/*N*/ void ScDocument::SetLink( USHORT nTab, BYTE nMode, const String& rDoc,
/*N*/                           const String& rFilter, const String& rOptions,
/*N*/                           const String& rTabName, ULONG nRefreshDelay )
/*N*/ {
/*N*/   if (nTab<=MAXTAB && pTab[nTab])
/*N*/       pTab[nTab]->SetLink( nMode, rDoc, rFilter, rOptions, rTabName, nRefreshDelay );
/*N*/ }

/*N*/ BOOL ScDocument::HasLink( const String& rDoc,
/*N*/                           const String& rFilter, const String& rOptions ) const
/*N*/ {
/*N*/   USHORT nCount = GetTableCount();
/*N*/   for (USHORT i=0; i<nCount; i++)
/*N*/       if (pTab[i]->IsLinked()
/*N*/               && pTab[i]->GetLinkDoc() == rDoc
/*N*/               && pTab[i]->GetLinkFlt() == rFilter
/*N*/               && pTab[i]->GetLinkOpt() == rOptions)
/*N*/           return TRUE;
/*N*/
/*N*/   return FALSE;
/*N*/ }

//STRIP001 BOOL ScDocument::LinkEmptyTab( USHORT& rTab, const String& aDocTab,
//STRIP001      const String& aFileName, const String& aTabName )
//STRIP001 {
//STRIP001  if ( IsClipboard() )
//STRIP001  {
//STRIP001      DBG_ERRORFILE( "LinkExternalTab in Clipboard" );
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001  rTab = 0;
//STRIP001  String  aFilterName;    // wird vom Loader gefuellt
//STRIP001  String  aOptions;       // Filter-Optionen
//STRIP001  ScDocumentLoader::GetFilterName( aFileName, aFilterName, aOptions );
//STRIP001
//STRIP001  if ( !InsertTab( SC_TAB_APPEND, aDocTab, TRUE ) )
//STRIP001  {
//STRIP001      DBG_ERRORFILE("can't insert external document table");
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001  rTab = GetTableCount() - 1;
//STRIP001
//STRIP001  ULONG nRefreshDelay = 0;
//STRIP001
//STRIP001  BOOL bWasThere = HasLink( aFileName, aFilterName, aOptions );
//STRIP001  SetLink( rTab, SC_LINK_VALUE, aFileName, aFilterName, aOptions, aTabName, nRefreshDelay );
//STRIP001  if ( !bWasThere )       // Link pro Quelldokument nur einmal eintragen
//STRIP001  {
//STRIP001      ScTableLink* pLink = new ScTableLink( pShell, aFileName, aFilterName, aOptions, nRefreshDelay );
//STRIP001      pLink->SetInCreate( TRUE );
//STRIP001      pLinkManager->InsertFileLink( *pLink, OBJECT_CLIENT_FILE, aFileName,
//STRIP001                                      &aFilterName );
//STRIP001      pLink->Update();
//STRIP001      pLink->SetInCreate( FALSE );
//STRIP001      SfxBindings* pBindings = GetViewBindings();
//STRIP001      if (pBindings)
//STRIP001          pBindings->Invalidate( SID_LINKS );
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

/*N*/ BOOL ScDocument::LinkExternalTab( USHORT& rTab, const String& aDocTab,
/*N*/       const String& aFileName, const String& aTabName )
/*N*/ {
/*N*/   if ( IsClipboard() )
/*N*/   {
/*N*/       DBG_ERRORFILE( "LinkExternalTab in Clipboard" );
/*N*/       return FALSE;
/*N*/   }
/*N*/   rTab = 0;
/*N*/   String  aFilterName;        // wird vom Loader gefuellt
/*N*/   String  aOptions;       // Filter-Optionen
/*N*/   ScDocumentLoader aLoader( aFileName, aFilterName, aOptions,
/*N*/       pExtDocOptions ? pExtDocOptions->nLinkCnt + 1 : 1 );
/*N*/   if ( aLoader.IsError() )
/*N*/       return FALSE;
/*N*/   ScDocument* pSrcDoc = aLoader.GetDocument();
/*N*/
/*N*/   //  Tabelle kopieren
/*N*/   USHORT nSrcTab;
/*N*/   if ( pSrcDoc->GetTable( aTabName, nSrcTab ) )
/*N*/   {
/*N*/       if ( !InsertTab( SC_TAB_APPEND, aDocTab, TRUE ) )
/*N*/       {
/*N*/           DBG_ERRORFILE("can't insert external document table");
/*N*/           return FALSE;
/*N*/       }
/*N*/       rTab = GetTableCount() - 1;
/*N*/       // nicht neu einfuegen, nur Ergebnisse
/*N*/       TransferTab( pSrcDoc, nSrcTab, rTab, FALSE, TRUE );
/*N*/   }
/*N*/   else
/*N*/       return FALSE;
/*N*/
/*N*/   ULONG nRefreshDelay = 0;
/*N*/
/*N*/   BOOL bWasThere = HasLink( aFileName, aFilterName, aOptions );
/*N*/   SetLink( rTab, SC_LINK_VALUE, aFileName, aFilterName, aOptions, aTabName, nRefreshDelay );
/*N*/   if ( !bWasThere )       // Link pro Quelldokument nur einmal eintragen
/*N*/   {
/*N*/       ScTableLink* pLink = new ScTableLink( pShell, aFileName, aFilterName, aOptions, nRefreshDelay );
/*N*/       pLink->SetInCreate( TRUE );
/*N*/       pLinkManager->InsertFileLink( *pLink, OBJECT_CLIENT_FILE, aFileName,
/*N*/                                       &aFilterName );
/*N*/       pLink->Update();
/*N*/       pLink->SetInCreate( FALSE );
/*N*/       SfxBindings* pBindings = GetViewBindings();
/*N*/       if (pBindings)
/*N*/           pBindings->Invalidate( SID_LINKS );
/*N*/   }
/*N*/   return TRUE;
/*N*/ }

/*N*/ ScOutlineTable* ScDocument::GetOutlineTable( USHORT nTab, BOOL bCreate )
/*N*/ {
/*N*/   ScOutlineTable* pVal = NULL;
/*N*/
/*N*/   if (VALIDTAB(nTab))
/*N*/       if (pTab[nTab])
/*N*/       {
/*N*/           pVal = pTab[nTab]->GetOutlineTable();
/*N*/           if (!pVal)
/*N*/               if (bCreate)
/*N*/               {
/*N*/                   pTab[nTab]->StartOutlineTable();
/*N*/                   pVal = pTab[nTab]->GetOutlineTable();
/*N*/               }
/*N*/       }
/*N*/
/*N*/   return pVal;
/*N*/ }

//STRIP001 BOOL ScDocument::SetOutlineTable( USHORT nTab, const ScOutlineTable* pNewOutline )
//STRIP001 {
//STRIP001  if (VALIDTAB(nTab))
//STRIP001      if (pTab[nTab])
//STRIP001          return pTab[nTab]->SetOutlineTable(pNewOutline);
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 void ScDocument::DoAutoOutline( USHORT nStartCol, USHORT nStartRow,
//STRIP001                              USHORT nEndCol, USHORT nEndRow, USHORT nTab )
//STRIP001 {
//STRIP001  if (VALIDTAB(nTab))
//STRIP001      if (pTab[nTab])
//STRIP001          pTab[nTab]->DoAutoOutline( nStartCol, nStartRow, nEndCol, nEndRow );
//STRIP001 }

//STRIP001 BOOL ScDocument::TestRemoveSubTotals( USHORT nTab, const ScSubTotalParam& rParam )
//STRIP001 {
//STRIP001  if (VALIDTAB(nTab))
//STRIP001      if (pTab[nTab])
//STRIP001          return pTab[nTab]->TestRemoveSubTotals( rParam );
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 void ScDocument::RemoveSubTotals( USHORT nTab, ScSubTotalParam& rParam )
//STRIP001 {
//STRIP001  if (VALIDTAB(nTab))
//STRIP001      if (pTab[nTab])
//STRIP001          pTab[nTab]->RemoveSubTotals( rParam );
//STRIP001 }

//STRIP001 BOOL ScDocument::DoSubTotals( USHORT nTab, ScSubTotalParam& rParam )
//STRIP001 {
//STRIP001  if (VALIDTAB(nTab))
//STRIP001      if (pTab[nTab])
//STRIP001          return pTab[nTab]->DoSubTotals( rParam );
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 BOOL ScDocument::HasSubTotalCells( const ScRange& rRange )
//STRIP001 {
//STRIP001  ScCellIterator aIter( this, rRange );
//STRIP001  ScBaseCell* pCell = aIter.GetFirst();
//STRIP001  while (pCell)
//STRIP001  {
//STRIP001      if ( pCell->GetCellType() == CELLTYPE_FORMULA && ((ScFormulaCell*)pCell)->IsSubTotal() )
//STRIP001          return TRUE;
//STRIP001
//STRIP001      pCell = aIter.GetNext();
//STRIP001  }
//STRIP001  return FALSE;   // none found
//STRIP001 }

//  kopiert aus diesem Dokument die Zellen von Positionen, an denen in pPosDoc
//  auch Zellen stehen, nach pDestDoc

//STRIP001 void ScDocument::CopyUpdated( ScDocument* pPosDoc, ScDocument* pDestDoc )
//STRIP001 {
//STRIP001  USHORT nCount = GetTableCount();
//STRIP001  for (USHORT nTab=0; nTab<nCount; nTab++)
//STRIP001      if (pTab[nTab] && pPosDoc->pTab[nTab] && pDestDoc->pTab[nTab])
//STRIP001          pTab[nTab]->CopyUpdated( pPosDoc->pTab[nTab], pDestDoc->pTab[nTab] );
//STRIP001 }

//STRIP001 void ScDocument::CopyScenario( USHORT nSrcTab, USHORT nDestTab, BOOL bNewScenario )
//STRIP001 {
//STRIP001  if (nSrcTab<=MAXTAB && nDestTab<=MAXTAB && pTab[nSrcTab] && pTab[nDestTab])
//STRIP001  {
//STRIP001      //  Flags fuer aktive Szenarios richtig setzen
//STRIP001      //  und aktuelle Werte in bisher aktive Szenarios zurueckschreiben
//STRIP001
//STRIP001      ScRangeList aRanges = *pTab[nSrcTab]->GetScenarioRanges();
//STRIP001      USHORT nRangeCount = (USHORT)aRanges.Count();
//STRIP001
//STRIP001      //  nDestTab ist die Zieltabelle
//STRIP001      for ( USHORT nTab = nDestTab+1;
//STRIP001              nTab<=MAXTAB && pTab[nTab] && pTab[nTab]->IsScenario();
//STRIP001              nTab++ )
//STRIP001      {
//STRIP001          if ( pTab[nTab]->IsActiveScenario() )       // auch wenn's dasselbe Szenario ist
//STRIP001          {
//STRIP001              BOOL bTouched = FALSE;
//STRIP001              for ( USHORT nR=0; nR<nRangeCount && !bTouched; nR++)
//STRIP001              {
//STRIP001                  ScRange aRange = *aRanges.GetObject(nR);
//STRIP001                  if ( pTab[nTab]->HasScenarioRange( aRange ) )
//STRIP001                      bTouched = TRUE;
//STRIP001              }
//STRIP001              if (bTouched)
//STRIP001              {
//STRIP001                  pTab[nTab]->SetActiveScenario(FALSE);
//STRIP001                  if ( pTab[nTab]->GetScenarioFlags() & SC_SCENARIO_TWOWAY )
//STRIP001                      pTab[nTab]->CopyScenarioFrom( pTab[nDestTab] );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      pTab[nSrcTab]->SetActiveScenario(TRUE);     // da kommt's her...
//STRIP001      if (!bNewScenario)                          // Daten aus dem ausgewaehlten Szenario kopieren
//STRIP001      {
//STRIP001          BOOL bOldAutoCalc = GetAutoCalc();
//STRIP001          SetAutoCalc( FALSE );   // Mehrfachberechnungen vermeiden
//STRIP001          pTab[nSrcTab]->CopyScenarioTo( pTab[nDestTab] );
//STRIP001          SetDirty();
//STRIP001          SetAutoCalc( bOldAutoCalc );
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void ScDocument::MarkScenario( USHORT nSrcTab, USHORT nDestTab, ScMarkData& rDestMark,
//STRIP001                              BOOL bResetMark, USHORT nNeededBits ) const
//STRIP001 {
//STRIP001  if (bResetMark)
//STRIP001      rDestMark.ResetMark();
//STRIP001
//STRIP001  if (nSrcTab<=MAXTAB && pTab[nSrcTab])
//STRIP001      pTab[nSrcTab]->MarkScenarioIn( rDestMark, nNeededBits );
//STRIP001
//STRIP001  rDestMark.SetAreaTab( nDestTab );
//STRIP001 }

//STRIP001 BOOL ScDocument::HasScenarioRange( USHORT nTab, const ScRange& rRange ) const
//STRIP001 {
//STRIP001  if (nTab<=MAXTAB && pTab[nTab])
//STRIP001      return pTab[nTab]->HasScenarioRange( rRange );
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }

/*N*/ const ScRangeList* ScDocument::GetScenarioRanges( USHORT nTab ) const
/*N*/ {
/*N*/   if (nTab<=MAXTAB && pTab[nTab])
/*N*/       return pTab[nTab]->GetScenarioRanges();
/*N*/
/*N*/   return NULL;
/*N*/ }

/*N*/ BOOL ScDocument::IsActiveScenario( USHORT nTab ) const
/*N*/ {
/*N*/   if (nTab<=MAXTAB && pTab[nTab])
/*N*/       return pTab[nTab]->IsActiveScenario();
/*N*/
/*N*/   return FALSE;
/*N*/ }

/*N*/ void ScDocument::SetActiveScenario( USHORT nTab, BOOL bActive )
/*N*/ {
/*N*/   if (nTab<=MAXTAB && pTab[nTab])
/*N*/       pTab[nTab]->SetActiveScenario( bActive );
/*N*/ }

//STRIP001 BOOL ScDocument::TestCopyScenario( USHORT nSrcTab, USHORT nDestTab ) const
//STRIP001 {
//STRIP001  if (nSrcTab<=MAXTAB && nDestTab<=MAXTAB)
//STRIP001      return pTab[nSrcTab]->TestCopyScenarioTo( pTab[nDestTab] );
//STRIP001
//STRIP001  DBG_ERROR("falsche Tabelle bei TestCopyScenario");
//STRIP001  return FALSE;
//STRIP001 }

/*N*/ void ScDocument::AddUnoObject( SfxListener& rObject )
/*N*/ {
/*N*/   if (!pUnoBroadcaster)
/*N*/       pUnoBroadcaster = new SfxBroadcaster;
/*N*/
/*N*/   rObject.StartListening( *pUnoBroadcaster );
/*N*/ }

/*N*/ void ScDocument::RemoveUnoObject( SfxListener& rObject )
/*N*/ {
/*N*/   if (pUnoBroadcaster)
/*N*/   {
/*N*/       rObject.EndListening( *pUnoBroadcaster );
/*N*/
/*N*/       if ( bInUnoBroadcast )
/*N*/       {
/*?*/           //  #107294# Broadcasts from ScDocument::BroadcastUno are the only way that
/*?*/           //  uno object methods are called without holding a reference.
/*?*/           //
/*?*/           //  If RemoveUnoObject is called from an object dtor in the finalizer thread
/*?*/           //  while the main thread is calling BroadcastUno, the dtor thread must wait
/*?*/           //  (or the object's Notify might try to access a deleted object).
/*?*/           //  The SolarMutex can't be locked here because if a component is called from
/*?*/           //  a VCL event, the main thread has the SolarMutex locked all the time.
/*?*/           //
/*?*/           //  This check is done after calling EndListening, so a later BroadcastUno call
/*?*/           //  won't touch this object.
/*?*/
/*?*/           vos::IMutex& rSolarMutex = Application::GetSolarMutex();
/*?*/           if ( rSolarMutex.tryToAcquire() )
/*?*/           {
/*?*/               //  BroadcastUno is always called with the SolarMutex locked, so if it
/*?*/               //  can be acquired, this is within the same thread (should not happen)
/*?*/               DBG_ERRORFILE( "RemoveUnoObject called from BroadcastUno" );
/*?*/               rSolarMutex.release();
/*?*/           }
/*?*/           else
/*?*/           {
/*?*/               //  let the thread that called BroadcastUno continue
/*?*/               while ( bInUnoBroadcast )
/*?*/               {
/*?*/                   vos::OThread::yield();
/*?*/               }
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/   else
/*?*/       DBG_ERROR("No Uno broadcaster");
/*N*/ }

/*N*/ void ScDocument::BroadcastUno( const SfxHint &rHint )
/*N*/ {
/*N*/   if (pUnoBroadcaster)
/*N*/   {
/*N*/       bInUnoBroadcast = TRUE;
/*N*/       pUnoBroadcaster->Broadcast( rHint );
/*N*/       bInUnoBroadcast = FALSE;
/*N*/   }
/*N*/ }

//STRIP001 void ScDocument::UpdateReference( UpdateRefMode eUpdateRefMode,
//STRIP001                                  USHORT nCol1, USHORT nRow1, USHORT nTab1,
//STRIP001                                  USHORT nCol2, USHORT nRow2, USHORT nTab2,
//STRIP001                                  short nDx, short nDy, short nDz,
//STRIP001                                  ScDocument* pUndoDoc, BOOL bIncludeDraw )
//STRIP001 {
//STRIP001  PutInOrder( nCol1, nCol2 );
//STRIP001  PutInOrder( nRow1, nRow2 );
//STRIP001  PutInOrder( nTab1, nTab2 );
//STRIP001  if (VALIDTAB(nTab1) && VALIDTAB(nTab2))
//STRIP001  {
//STRIP001      BOOL bExpandRefsOld = IsExpandRefs();
//STRIP001      if ( eUpdateRefMode == URM_INSDEL && (nDx > 0 || nDy > 0 || nDz > 0) )
//STRIP001          SetExpandRefs( SC_MOD()->GetInputOptions().GetExpandRefs() );
//STRIP001      USHORT i;
//STRIP001      USHORT iMax;
//STRIP001      if ( eUpdateRefMode == URM_COPY )
//STRIP001      {
//STRIP001          i = nTab1;
//STRIP001          iMax = nTab2;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          ScRange aRange( nCol1, nRow1, nTab1, nCol2, nRow2, nTab2 );
//STRIP001          xColNameRanges->UpdateReference( eUpdateRefMode, this, aRange, nDx, nDy, nDz );
//STRIP001          xRowNameRanges->UpdateReference( eUpdateRefMode, this, aRange, nDx, nDy, nDz );
//STRIP001          pDBCollection->UpdateReference( eUpdateRefMode, nCol1, nRow1, nTab1, nCol2, nRow2, nTab2, nDx, nDy, nDz );
//STRIP001          pRangeName->UpdateReference( eUpdateRefMode, aRange, nDx, nDy, nDz );
//STRIP001          if (pPivotCollection)
//STRIP001              pPivotCollection->UpdateReference( eUpdateRefMode, nCol1, nRow1, nTab1, nCol2, nRow2, nTab2, nDx, nDy, nDz );
//STRIP001          if ( pDPCollection )
//STRIP001              pDPCollection->UpdateReference( eUpdateRefMode, aRange, nDx, nDy, nDz );
//STRIP001          UpdateChartRef( eUpdateRefMode, nCol1, nRow1, nTab1, nCol2, nRow2, nTab2, nDx, nDy, nDz );
//STRIP001          UpdateRefAreaLinks( eUpdateRefMode, aRange, nDx, nDy, nDz );
//STRIP001          if ( pCondFormList )
//STRIP001              pCondFormList->UpdateReference( eUpdateRefMode, aRange, nDx, nDy, nDz );
//STRIP001          if ( pDetOpList )
//STRIP001              pDetOpList->UpdateReference( this, eUpdateRefMode, aRange, nDx, nDy, nDz );
//STRIP001          if ( pUnoBroadcaster )
//STRIP001              pUnoBroadcaster->Broadcast( ScUpdateRefHint(
//STRIP001                                  eUpdateRefMode, aRange, nDx, nDy, nDz ) );
//STRIP001          i = 0;
//STRIP001          iMax = MAXTAB;
//STRIP001      }
//STRIP001      for ( ; i<=iMax; i++)
//STRIP001          if (pTab[i])
//STRIP001              pTab[i]->UpdateReference(
//STRIP001                  eUpdateRefMode, nCol1, nRow1, nTab1, nCol2, nRow2, nTab2,
//STRIP001                  nDx, nDy, nDz, pUndoDoc, bIncludeDraw );
//STRIP001
//STRIP001      if ( bIsEmbedded )
//STRIP001      {
//STRIP001          USHORT theCol1, theRow1, theTab1, theCol2, theRow2, theTab2;
//STRIP001          theCol1 = aEmbedRange.aStart.Col();
//STRIP001          theRow1 = aEmbedRange.aStart.Row();
//STRIP001          theTab1 = aEmbedRange.aStart.Tab();
//STRIP001          theCol2 = aEmbedRange.aEnd.Col();
//STRIP001          theRow2 = aEmbedRange.aEnd.Row();
//STRIP001          theTab2 = aEmbedRange.aEnd.Tab();
//STRIP001          if ( ScRefUpdate::Update( this, eUpdateRefMode, nCol1,nRow1,nTab1, nCol2,nRow2,nTab2,
//STRIP001                                      nDx,nDy,nDz, theCol1,theRow1,theTab1, theCol2,theRow2,theTab2 ) )
//STRIP001          {
//STRIP001              aEmbedRange = ScRange( theCol1,theRow1,theTab1, theCol2,theRow2,theTab2 );
//STRIP001          }
//STRIP001      }
//STRIP001      SetExpandRefs( bExpandRefsOld );
//STRIP001
//STRIP001      // #30428# after moving, no clipboard move ref-updates are possible
//STRIP001      if ( eUpdateRefMode != URM_COPY && IsClipboardSource() )
//STRIP001      {
//STRIP001          ScDocument* pClipDoc = SC_MOD()->GetClipDoc();
//STRIP001          if (pClipDoc)
//STRIP001              pClipDoc->bCutMode = FALSE;
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void ScDocument::UpdateTranspose( const ScAddress& rDestPos, ScDocument* pClipDoc,
//STRIP001                                      const ScMarkData& rMark, ScDocument* pUndoDoc )
//STRIP001 {
//STRIP001  DBG_ASSERT(pClipDoc->bIsClip, "UpdateTranspose: kein Clip");
//STRIP001
//STRIP001  ScRange aSource = pClipDoc->aClipRange;         // Tab wird noch angepasst
//STRIP001  ScAddress aDest = rDestPos;
//STRIP001
//STRIP001  USHORT nClipTab = 0;
//STRIP001  for (USHORT nDestTab=0; nDestTab<=MAXTAB && pTab[nDestTab]; nDestTab++)
//STRIP001      if (rMark.GetTableSelect(nDestTab))
//STRIP001      {
//STRIP001          while (!pClipDoc->pTab[nClipTab]) nClipTab = (nClipTab+1) % (MAXTAB+1);
//STRIP001          aSource.aStart.SetTab( nClipTab );
//STRIP001          aSource.aEnd.SetTab( nClipTab );
//STRIP001          aDest.SetTab( nDestTab );
//STRIP001
//STRIP001          //  wie UpdateReference
//STRIP001
//STRIP001          pRangeName->UpdateTranspose( aSource, aDest );      // vor den Zellen!
//STRIP001          for (USHORT i=0; i<=MAXTAB; i++)
//STRIP001              if (pTab[i])
//STRIP001                  pTab[i]->UpdateTranspose( aSource, aDest, pUndoDoc );
//STRIP001
//STRIP001          nClipTab = (nClipTab+1) % (MAXTAB+1);
//STRIP001      }
//STRIP001 }

//STRIP001 void ScDocument::UpdateGrow( const ScRange& rArea, USHORT nGrowX, USHORT nGrowY )
//STRIP001 {
//STRIP001  //! pDBCollection
//STRIP001  //! pPivotCollection
//STRIP001  //! UpdateChartRef
//STRIP001
//STRIP001  pRangeName->UpdateGrow( rArea, nGrowX, nGrowY );
//STRIP001  pPivotCollection->UpdateGrow( rArea, nGrowX, nGrowY );
//STRIP001
//STRIP001  for (USHORT i=0; i<=MAXTAB && pTab[i]; i++)
//STRIP001      pTab[i]->UpdateGrow( rArea, nGrowX, nGrowY );
//STRIP001 }

/*N*/ void ScDocument::Fill(USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2, const ScMarkData& rMark,
/*N*/                       USHORT nFillCount, FillDir eFillDir, FillCmd eFillCmd, FillDateCmd eFillDateCmd,
/*N*/                       double nStepValue, double nMaxValue)
/*N*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001 PutInOrder( nCol1, nCol2 );
//STRIP001 /*?*/    PutInOrder( nRow1, nRow2 );
//STRIP001 /*?*/    for (USHORT i=0; i <= MAXTAB; i++)
//STRIP001 /*?*/        if (pTab[i])
//STRIP001 /*?*/            if (rMark.GetTableSelect(i))
//STRIP001 /*?*/                pTab[i]->Fill(nCol1, nRow1, nCol2, nRow2,
//STRIP001 /*?*/                                nFillCount, eFillDir, eFillCmd, eFillDateCmd,
//STRIP001 /*?*/                                nStepValue, nMaxValue);
/*N*/ }

//STRIP001 String ScDocument::GetAutoFillPreview( const ScRange& rSource, USHORT nEndX, USHORT nEndY )
//STRIP001 {
//STRIP001  USHORT nTab = rSource.aStart.Tab();
//STRIP001  if (pTab[nTab])
//STRIP001      return pTab[nTab]->GetAutoFillPreview( rSource, nEndX, nEndY );
//STRIP001
//STRIP001  return EMPTY_STRING;
//STRIP001 }

/*N*/ void ScDocument::AutoFormat( USHORT nStartCol, USHORT nStartRow, USHORT nEndCol, USHORT nEndRow,
/*N*/                                   USHORT nFormatNo, const ScMarkData& rMark )
/*N*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001 PutInOrder( nStartCol, nEndCol );
//STRIP001 /*?*/    PutInOrder( nStartRow, nEndRow );
//STRIP001 /*?*/    for (USHORT i=0; i <= MAXTAB; i++)
//STRIP001 /*?*/        if (pTab[i])
//STRIP001 /*?*/            if (rMark.GetTableSelect(i))
//STRIP001 /*?*/                pTab[i]->AutoFormat( nStartCol, nStartRow, nEndCol, nEndRow, nFormatNo );
/*N*/ }

//STRIP001 void ScDocument::GetAutoFormatData(USHORT nTab, USHORT nStartCol, USHORT nStartRow, USHORT nEndCol, USHORT nEndRow,
//STRIP001                                  ScAutoFormatData& rData)
//STRIP001 {
//STRIP001  if (VALIDTAB(nTab))
//STRIP001  {
//STRIP001      if (pTab[nTab])
//STRIP001      {
//STRIP001          PutInOrder(nStartCol, nEndCol);
//STRIP001          PutInOrder(nStartRow, nEndRow);
//STRIP001          pTab[nTab]->GetAutoFormatData(nStartCol, nStartRow, nEndCol, nEndRow, rData);
//STRIP001      }
//STRIP001  }
//STRIP001 }

// static
/*N*/ void ScDocument::GetSearchAndReplaceStart( const SvxSearchItem& rSearchItem,
/*N*/       USHORT& rCol, USHORT& rRow )
/*N*/ {
/*N*/   USHORT nCommand = rSearchItem.GetCommand();
/*N*/   BOOL bReplace = ( nCommand == SVX_SEARCHCMD_REPLACE ||
/*N*/       nCommand == SVX_SEARCHCMD_REPLACE_ALL );
/*N*/   if ( rSearchItem.GetBackward() )
/*N*/   {
/*N*/       if ( rSearchItem.GetRowDirection() )
/*N*/       {
/*N*/           if ( rSearchItem.GetPattern() )
/*N*/           {
/*N*/               rCol = MAXCOL;
/*N*/               rRow = MAXROW+1;
/*N*/           }
/*N*/           else if ( bReplace )
/*N*/           {
/*N*/               rCol = MAXCOL;
/*N*/               rRow = MAXROW;
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               rCol = MAXCOL+1;
/*N*/               rRow = MAXROW;
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           if ( rSearchItem.GetPattern() )
/*N*/           {
/*N*/               rCol = MAXCOL+1;
/*N*/               rRow = MAXROW;
/*N*/           }
/*N*/           else if ( bReplace )
/*N*/           {
/*N*/               rCol = MAXCOL;
/*N*/               rRow = MAXROW;
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               rCol = MAXCOL;
/*N*/               rRow = MAXROW+1;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       if ( rSearchItem.GetRowDirection() )
/*N*/       {
/*N*/           if ( rSearchItem.GetPattern() )
/*N*/           {
/*N*/               rCol = 0;
/*N*/               rRow = (USHORT) -1;
/*N*/           }
/*N*/           else if ( bReplace )
/*N*/           {
/*N*/               rCol = 0;
/*N*/               rRow = 0;
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               rCol = (USHORT) -1;
/*N*/               rRow = 0;
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           if ( rSearchItem.GetPattern() )
/*N*/           {
/*N*/               rCol = (USHORT) -1;
/*N*/               rRow = 0;
/*N*/           }
/*N*/           else if ( bReplace )
/*N*/           {
/*N*/               rCol = 0;
/*N*/               rRow = 0;
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               rCol = 0;
/*N*/               rRow = (USHORT) -1;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ BOOL ScDocument::SearchAndReplace(const SvxSearchItem& rSearchItem,
/*N*/                               USHORT& rCol, USHORT& rRow, USHORT& rTab,
/*N*/                               ScMarkData& rMark,
/*N*/                               String& rUndoStr, ScDocument* pUndoDoc)
/*N*/ {
/*N*/   //!     getrennte Markierungen pro Tabelle verwalten !!!!!!!!!!!!!
/*N*/
/*N*/   rMark.MarkToMulti();
/*N*/
/*N*/   BOOL bFound = FALSE;
/*N*/   if (VALIDTAB(rTab))
/*N*/   {
/*N*/       USHORT nCol;
/*N*/       USHORT nRow;
/*N*/       USHORT nTab;
/*N*/       USHORT nCommand = rSearchItem.GetCommand();
/*N*/       if ( nCommand == SVX_SEARCHCMD_FIND_ALL ||
/*N*/            nCommand == SVX_SEARCHCMD_REPLACE_ALL )
/*N*/       {
/*N*/           for (nTab = 0; nTab <= MAXTAB; nTab++)
/*N*/               if (pTab[nTab])
/*N*/               {
/*N*/                   if (rMark.GetTableSelect(nTab))
/*N*/                   {
/*N*/                       nCol = 0;
/*N*/                       nRow = 0;
/*N*/                       bFound |= pTab[nTab]->SearchAndReplace(
/*N*/                                   rSearchItem, nCol, nRow, rMark, rUndoStr, pUndoDoc );
/*N*/                   }
/*N*/               }
/*N*/
/*N*/           //  Markierung wird innen schon komplett gesetzt
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           nCol = rCol;
/*N*/           nRow = rRow;
/*N*/           if (rSearchItem.GetBackward())
/*N*/           {
/*N*/               for (nTab = rTab; ((short)nTab >= 0) && !bFound; nTab--)
/*N*/                   if (pTab[nTab])
/*N*/                   {
/*N*/                       if (rMark.GetTableSelect(nTab))
/*N*/                       {
/*N*/                           bFound = pTab[nTab]->SearchAndReplace(
/*N*/                                       rSearchItem, nCol, nRow, rMark, rUndoStr, pUndoDoc );
/*N*/                           if (bFound)
/*N*/                           {
/*N*/                               rCol = nCol;
/*N*/                               rRow = nRow;
/*N*/                               rTab = nTab;
/*N*/                           }
/*N*/                           else
/*N*/                               ScDocument::GetSearchAndReplaceStart(
/*N*/                                   rSearchItem, nCol, nRow );
/*N*/                       }
/*N*/                   }
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               for (nTab = rTab; (nTab <= MAXTAB) && !bFound; nTab++)
/*N*/                   if (pTab[nTab])
/*N*/                   {
/*N*/                       if (rMark.GetTableSelect(nTab))
/*N*/                       {
/*N*/                           bFound = pTab[nTab]->SearchAndReplace(
/*N*/                                       rSearchItem, nCol, nRow, rMark, rUndoStr, pUndoDoc );
/*N*/                           if (bFound)
/*N*/                           {
/*N*/                               rCol = nCol;
/*N*/                               rRow = nRow;
/*N*/                               rTab = nTab;
/*N*/                           }
/*N*/                           else
/*N*/                               ScDocument::GetSearchAndReplaceStart(
/*N*/                                   rSearchItem, nCol, nRow );
/*N*/                       }
/*N*/                   }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return bFound;
/*N*/ }

//STRIP001 BOOL ScDocument::IsFiltered( USHORT nRow, USHORT nTab ) const
//STRIP001 {
//STRIP001  if (VALIDTAB(nTab))
//STRIP001      if (pTab[nTab])
//STRIP001          return pTab[nTab]->IsFiltered( nRow );
//STRIP001  DBG_ERROR("Falsche Tabellennummer");
//STRIP001  return 0;
//STRIP001 }

//  Outline anpassen

/*N*/ BOOL ScDocument::UpdateOutlineCol( USHORT nStartCol, USHORT nEndCol, USHORT nTab, BOOL bShow )
/*N*/ {
/*N*/   if ( nTab<=MAXTAB && pTab[nTab] )
/*N*/       return pTab[nTab]->UpdateOutlineCol( nStartCol, nEndCol, bShow );
/*N*/
/*N*/   DBG_ERROR("missing tab");
/*N*/   return FALSE;
/*N*/ }

/*N*/ BOOL ScDocument::UpdateOutlineRow( USHORT nStartRow, USHORT nEndRow, USHORT nTab, BOOL bShow )
/*N*/ {
/*N*/   if ( nTab<=MAXTAB && pTab[nTab] )
/*N*/       return pTab[nTab]->UpdateOutlineRow( nStartRow, nEndRow, bShow );
/*N*/
/*N*/   DBG_ERROR("missing tab");
/*N*/   return FALSE;
/*N*/ }

/*N*/ void ScDocument::Sort(USHORT nTab, const ScSortParam& rSortParam, BOOL bKeepQuery)
/*N*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001 if ( nTab<=MAXTAB && pTab[nTab] )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        BOOL bOldDisableIdle = IsIdleDisabled();
//STRIP001 /*?*/        DisableIdle( TRUE );
//STRIP001 /*?*/        pTab[nTab]->Sort(rSortParam, bKeepQuery);
//STRIP001 /*?*/        DisableIdle( bOldDisableIdle );
//STRIP001 /*?*/    }
/*N*/ }

/*N*/ USHORT ScDocument::Query(USHORT nTab, const ScQueryParam& rQueryParam, BOOL bKeepSub)
/*N*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001 if ( nTab<=MAXTAB && pTab[nTab] )
//STRIP001 /*?*/        return pTab[nTab]->Query((ScQueryParam&)rQueryParam, bKeepSub);
//STRIP001 /*?*/
//STRIP001 /*?*/    DBG_ERROR("missing tab");
/*N*/   return 0;
/*N*/ }


//STRIP001 BOOL ScDocument::ValidQuery( USHORT nRow, USHORT nTab, const ScQueryParam& rQueryParam, BOOL* pSpecial )
//STRIP001 {
//STRIP001  if ( nTab<=MAXTAB && pTab[nTab] )
//STRIP001      return pTab[nTab]->ValidQuery( nRow, rQueryParam, pSpecial );
//STRIP001
//STRIP001  DBG_ERROR("missing tab");
//STRIP001  return FALSE;
//STRIP001 }


//STRIP001 void ScDocument::GetUpperCellString(USHORT nCol, USHORT nRow, USHORT nTab, String& rStr)
//STRIP001 {
//STRIP001  if ( nTab<=MAXTAB && pTab[nTab] )
//STRIP001      pTab[nTab]->GetUpperCellString( nCol, nRow, rStr );
//STRIP001  else
//STRIP001      rStr.Erase();
//STRIP001 }

/*N*/ BOOL ScDocument::CreateQueryParam(USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2, USHORT nTab, ScQueryParam& rQueryParam)
/*N*/ {
/*N*/   if ( nTab<=MAXTAB && pTab[nTab] )
/*N*/       return pTab[nTab]->CreateQueryParam(nCol1, nRow1, nCol2, nRow2, rQueryParam);
/*N*/
/*N*/   DBG_ERROR("missing tab");
/*N*/   return FALSE;
/*N*/ }

/*N*/ BOOL ScDocument::HasAutoFilter( USHORT nCurCol, USHORT nCurRow, USHORT nCurTab )
/*N*/ {
/*N*/   ScDBData*       pDBData         = GetDBAtCursor( nCurCol, nCurRow, nCurTab );
/*N*/   BOOL            bHasAutoFilter  = ( pDBData != NULL );
/*N*/
/*N*/   if ( pDBData )
/*N*/   {
/*?*/       if ( pDBData->HasHeader() )
/*?*/       {
/*?*/           USHORT nCol;
/*?*/           USHORT nRow;
/*?*/           INT16  nFlag;
/*?*/
/*?*/           ScQueryParam aParam;
/*?*/           pDBData->GetQueryParam( aParam );
/*?*/           nRow = aParam.nRow1;
/*?*/
/*?*/           for ( nCol=aParam.nCol1; nCol<=aParam.nCol2 && bHasAutoFilter; nCol++ )
/*?*/           {
/*?*/               nFlag = ((ScMergeFlagAttr*)
/*?*/                           GetAttr( nCol, nRow, nCurTab, ATTR_MERGE_FLAG ))->
/*?*/                               GetValue();
/*?*/
/*?*/               if ( (nFlag & SC_MF_AUTO) == 0 )
/*?*/                   bHasAutoFilter = FALSE;
/*?*/           }
/*?*/       }
/*?*/       else
/*?*/           bHasAutoFilter = FALSE;
/*N*/   }
/*N*/
/*N*/   return bHasAutoFilter;
/*N*/ }

/*N*/ BOOL ScDocument::HasColHeader( USHORT nStartCol, USHORT nStartRow, USHORT nEndCol, USHORT nEndRow,
/*N*/                                   USHORT nTab )
/*N*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001 if (VALIDTAB(nTab))
//STRIP001 /*?*/        if (pTab[nTab])
//STRIP001 /*?*/            return pTab[nTab]->HasColHeader( nStartCol, nStartRow, nEndCol, nEndRow );
//STRIP001 /*?*/
/*N*/   return FALSE;
/*N*/ }

/*N*/ BOOL ScDocument::HasRowHeader( USHORT nStartCol, USHORT nStartRow, USHORT nEndCol, USHORT nEndRow,
/*N*/                                   USHORT nTab )
/*N*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001 if (VALIDTAB(nTab))
//STRIP001 /*?*/        if (pTab[nTab])
//STRIP001 /*?*/            return pTab[nTab]->HasRowHeader( nStartCol, nStartRow, nEndCol, nEndRow );
//STRIP001 /*?*/
/*N*/   return FALSE;
/*N*/ }

//
//  GetFilterEntries - Eintraege fuer AutoFilter-Listbox
//

//STRIP001 BOOL ScDocument::GetFilterEntries( USHORT nCol, USHORT nRow, USHORT nTab, TypedStrCollection& rStrings )
//STRIP001 {
//STRIP001  if ( nTab<=MAXTAB && pTab[nTab] && pDBCollection )
//STRIP001  {
//STRIP001      ScDBData* pDBData = pDBCollection->GetDBAtCursor(nCol, nRow, nTab, FALSE);  //!??
//STRIP001      if (pDBData)
//STRIP001      {
//STRIP001          USHORT nAreaTab;
//STRIP001          USHORT nStartCol;
//STRIP001          USHORT nStartRow;
//STRIP001          USHORT nEndCol;
//STRIP001          USHORT nEndRow;
//STRIP001          pDBData->GetArea( nAreaTab, nStartCol, nStartRow, nEndCol, nEndRow );
//STRIP001          if (pDBData->HasHeader())
//STRIP001              ++nStartRow;
//STRIP001
//STRIP001          ScQueryParam aParam;
//STRIP001          pDBData->GetQueryParam( aParam );
//STRIP001          rStrings.SetCaseSensitive( aParam.bCaseSens );
//STRIP001
//STRIP001          pTab[nTab]->GetFilterEntries( nCol, nStartRow, nEndRow, rStrings );
//STRIP001          return TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }

//
//  GetFilterEntriesArea - Eintraege fuer Filter-Dialog
//

//STRIP001 BOOL ScDocument::GetFilterEntriesArea( USHORT nCol, USHORT nStartRow, USHORT nEndRow,
//STRIP001                                      USHORT nTab, TypedStrCollection& rStrings )
//STRIP001 {
//STRIP001  if ( nTab<=MAXTAB && pTab[nTab] )
//STRIP001  {
//STRIP001      pTab[nTab]->GetFilterEntries( nCol, nStartRow, nEndRow, rStrings );
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }

//
//  GetDataEntries - Eintraege fuer Auswahlliste-Listbox (keine Zahlen / Formeln)
//

//STRIP001 BOOL ScDocument::GetDataEntries( USHORT nCol, USHORT nRow, USHORT nTab,
//STRIP001                                  TypedStrCollection& rStrings, BOOL bLimit )
//STRIP001 {
//STRIP001  if (nTab<=MAXTAB && pTab[nTab])
//STRIP001      return pTab[nTab]->GetDataEntries( nCol, nRow, rStrings, bLimit );
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }

//
//  GetFormulaEntries - Eintraege fuer Formel-AutoEingabe
//

//  Funktionen werden als 1 schon vom InputHandler eingefuegt
#define SC_STRTYPE_NAMES        2
#define SC_STRTYPE_DBNAMES      3
#define SC_STRTYPE_HEADERS      4

//STRIP001 BOOL ScDocument::GetFormulaEntries( TypedStrCollection& rStrings )
//STRIP001 {
//STRIP001  USHORT i;
//STRIP001
//STRIP001  //
//STRIP001  //  Bereichsnamen
//STRIP001  //
//STRIP001
//STRIP001  if ( pRangeName )
//STRIP001  {
//STRIP001      USHORT nRangeCount = pRangeName->GetCount();
//STRIP001      for ( i=0; i<nRangeCount; i++ )
//STRIP001      {
//STRIP001          ScRangeData* pData = (*pRangeName)[i];
//STRIP001          if (pData)
//STRIP001          {
//STRIP001              TypedStrData* pNew = new TypedStrData( pData->GetName(), 0.0, SC_STRTYPE_NAMES );
//STRIP001              if ( !rStrings.Insert(pNew) )
//STRIP001                  delete pNew;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  //
//STRIP001  //  Datenbank-Bereiche
//STRIP001  //
//STRIP001
//STRIP001  if ( pDBCollection )
//STRIP001  {
//STRIP001      USHORT nDBCount = pDBCollection->GetCount();
//STRIP001      for ( i=0; i<nDBCount; i++ )
//STRIP001      {
//STRIP001          ScDBData* pData = (*pDBCollection)[i];
//STRIP001          if (pData)
//STRIP001          {
//STRIP001              TypedStrData* pNew = new TypedStrData( pData->GetName(), 0.0, SC_STRTYPE_DBNAMES );
//STRIP001              if ( !rStrings.Insert(pNew) )
//STRIP001                  delete pNew;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  //
//STRIP001  //  Inhalte von Beschriftungsbereichen
//STRIP001  //
//STRIP001
//STRIP001  ScRangePairList* pLists[2];
//STRIP001  pLists[0] = GetColNameRanges();
//STRIP001  pLists[1] = GetRowNameRanges();
//STRIP001  for (USHORT nListNo=0; nListNo<2; nListNo++)
//STRIP001  {
//STRIP001      ScRangePairList* pList = pLists[nListNo];
//STRIP001      if (pList)
//STRIP001          for ( ScRangePair* pPair = pList->First(); pPair; pPair = pList->Next() )
//STRIP001          {
//STRIP001              ScRange aRange = pPair->GetRange(0);
//STRIP001              ScCellIterator aIter( this, aRange );
//STRIP001              for ( ScBaseCell* pCell = aIter.GetFirst(); pCell; pCell = aIter.GetNext() )
//STRIP001                  if ( pCell->HasStringData() )
//STRIP001                  {
//STRIP001                      String aStr = pCell->GetStringData();
//STRIP001                      TypedStrData* pNew = new TypedStrData( aStr, 0.0, SC_STRTYPE_HEADERS );
//STRIP001                      if ( !rStrings.Insert(pNew) )
//STRIP001                          delete pNew;
//STRIP001                  }
//STRIP001          }
//STRIP001  }
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }


/*N*/ BOOL ScDocument::IsEmbedded() const
/*N*/ {
/*N*/   return bIsEmbedded;
/*N*/ }

//STRIP001 void ScDocument::GetEmbedded( ScTripel& rStart, ScTripel& rEnd ) const
//STRIP001 {
//STRIP001  rStart.Put( aEmbedRange.aStart.Col(), aEmbedRange.aStart.Row(), aEmbedRange.aStart.Tab() );
//STRIP001  rEnd.Put( aEmbedRange.aEnd.Col(), aEmbedRange.aEnd.Row(), aEmbedRange.aEnd.Tab() );
//STRIP001 }

//STRIP001 Rectangle ScDocument::GetEmbeddedRect() const                        // 1/100 mm
//STRIP001 {
//STRIP001  Rectangle aRect;
//STRIP001  ScTable* pTable = pTab[aEmbedRange.aStart.Tab()];
//STRIP001  if (!pTable)
//STRIP001  {
//STRIP001      DBG_ERROR("GetEmbeddedRect ohne Tabelle");
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      USHORT i;
//STRIP001
//STRIP001      for (i=0; i<aEmbedRange.aStart.Col(); i++)
//STRIP001          aRect.Left() += pTable->GetColWidth(i);
//STRIP001      for (i=0; i<aEmbedRange.aStart.Row(); i++)
//STRIP001          aRect.Top() += pTable->GetRowHeight(i);
//STRIP001      aRect.Right() = aRect.Left();
//STRIP001      for (i=aEmbedRange.aStart.Col(); i<=aEmbedRange.aEnd.Col(); i++)
//STRIP001          aRect.Right() += pTable->GetColWidth(i);
//STRIP001      aRect.Bottom() = aRect.Top();
//STRIP001      for (i=aEmbedRange.aStart.Row(); i<=aEmbedRange.aEnd.Row(); i++)
//STRIP001          aRect.Bottom() += pTable->GetRowHeight(i);
//STRIP001
//STRIP001      aRect.Left()   = (long) ( aRect.Left()   * HMM_PER_TWIPS );
//STRIP001      aRect.Right()  = (long) ( aRect.Right()  * HMM_PER_TWIPS );
//STRIP001      aRect.Top()    = (long) ( aRect.Top()    * HMM_PER_TWIPS );
//STRIP001      aRect.Bottom() = (long) ( aRect.Bottom() * HMM_PER_TWIPS );
//STRIP001  }
//STRIP001  return aRect;
//STRIP001 }

//STRIP001 void ScDocument::SetEmbedded( const ScTripel& rStart, const ScTripel& rEnd )
//STRIP001 {
//STRIP001  bIsEmbedded = TRUE;
//STRIP001  aEmbedRange = ScRange( rStart, rEnd );
//STRIP001 }

//STRIP001 void ScDocument::ResetEmbedded()
//STRIP001 {
//STRIP001  bIsEmbedded = FALSE;
//STRIP001  aEmbedRange = ScRange();
//STRIP001 }

/*N*/ ScRange ScDocument::GetRange( USHORT nTab, const Rectangle& rMMRect )
/*N*/ {
/*N*/   ScTable* pTable = pTab[nTab];
/*N*/   if (!pTable)
/*N*/   {
/*N*/       DBG_ERROR("GetRange ohne Tabelle");
/*N*/       return ScRange();
/*N*/   }
/*N*/
/*N*/   long nSize;
/*N*/   long nTwips;
/*N*/   long nAdd;
/*N*/   BOOL bEnd;
/*N*/
/*N*/   nSize = 0;
/*N*/   nTwips = (long) (rMMRect.Left() / HMM_PER_TWIPS);
/*N*/
/*N*/   USHORT nX1 = 0;
/*N*/   bEnd = FALSE;
/*N*/   while (!bEnd)
/*N*/   {
/*N*/       nAdd = (long) pTable->GetColWidth(nX1);
/*N*/       if (nSize+nAdd <= nTwips+1 && nX1<MAXCOL)
/*N*/       {
/*N*/           nSize += nAdd;
/*N*/           ++nX1;
/*N*/       }
/*N*/       else
/*N*/           bEnd = TRUE;
/*N*/   }
/*N*/
/*N*/   nTwips = (long) (rMMRect.Right() / HMM_PER_TWIPS);
/*N*/
/*N*/   USHORT nX2 = nX1;
/*N*/   bEnd = FALSE;
/*N*/   while (!bEnd)
/*N*/   {
/*N*/       nAdd = (long) pTable->GetColWidth(nX2);
/*N*/       if (nSize+nAdd < nTwips && nX2<MAXCOL)
/*N*/       {
/*N*/           nSize += nAdd;
/*N*/           ++nX2;
/*N*/       }
/*N*/       else
/*N*/           bEnd = TRUE;
/*N*/   }
/*N*/
/*N*/
/*N*/   nSize = 0;
/*N*/   nTwips = (long) (rMMRect.Top() / HMM_PER_TWIPS);
/*N*/
/*N*/   USHORT nY1 = 0;
/*N*/   bEnd = FALSE;
/*N*/   while (!bEnd)
/*N*/   {
/*N*/       nAdd = (long) pTable->GetRowHeight(nY1);
/*N*/       if (nSize+nAdd <= nTwips+1 && nY1<MAXROW)
/*N*/       {
/*N*/           nSize += nAdd;
/*N*/           ++nY1;
/*N*/       }
/*N*/       else
/*N*/           bEnd = TRUE;
/*N*/   }
/*N*/
/*N*/   nTwips = (long) (rMMRect.Bottom() / HMM_PER_TWIPS);
/*N*/
/*N*/   USHORT nY2 = nY1;
/*N*/   bEnd = FALSE;
/*N*/   while (!bEnd)
/*N*/   {
/*N*/       nAdd = (long) pTable->GetRowHeight(nY2);
/*N*/       if (nSize+nAdd < nTwips && nY2<MAXROW)
/*N*/       {
/*N*/           nSize += nAdd;
/*N*/           ++nY2;
/*N*/       }
/*N*/       else
/*N*/           bEnd = TRUE;
/*N*/   }
/*N*/
/*N*/   return ScRange( nX1,nY1,nTab, nX2,nY2,nTab );
/*N*/ }

//STRIP001 void ScDocument::SetEmbedded( const Rectangle& rRect )           // aus VisArea (1/100 mm)
//STRIP001 {
//STRIP001  bIsEmbedded = TRUE;
//STRIP001  aEmbedRange = GetRange( nVisibleTab, rRect );
//STRIP001 }

//  VisArea auf Zellgrenzen anpassen

/*N*/ void lcl_SnapHor( ScTable* pTable, long& rVal, USHORT& rStartCol )
/*N*/ {
/*N*/   USHORT nCol = 0;
/*N*/   long nTwips = (long) (rVal / HMM_PER_TWIPS);
/*N*/   long nSnap = 0;
/*N*/   while ( nCol<MAXCOL )
/*N*/   {
/*N*/       long nAdd = pTable->GetColWidth(nCol);
/*N*/       if ( nSnap + nAdd/2 < nTwips || nCol < rStartCol )
/*N*/       {
/*N*/           nSnap += nAdd;
/*N*/           ++nCol;
/*N*/       }
/*N*/       else
/*N*/           break;
/*N*/   }
/*N*/   rVal = (long) ( nSnap * HMM_PER_TWIPS );
/*N*/   rStartCol = nCol;
/*N*/ }

/*N*/ void lcl_SnapVer( ScTable* pTable, long& rVal, USHORT& rStartRow )
/*N*/ {
/*N*/   USHORT nRow = 0;
/*N*/   long nTwips = (long) (rVal / HMM_PER_TWIPS);
/*N*/   long nSnap = 0;
/*N*/   while ( nRow<MAXROW )
/*N*/   {
/*N*/       long nAdd = pTable->GetRowHeight(nRow);
/*N*/       if ( nSnap + nAdd/2 < nTwips || nRow < rStartRow )
/*N*/       {
/*N*/           nSnap += nAdd;
/*N*/           ++nRow;
/*N*/       }
/*N*/       else
/*N*/           break;
/*N*/   }
/*N*/   rVal = (long) ( nSnap * HMM_PER_TWIPS );
/*N*/   rStartRow = nRow;
/*N*/ }

/*N*/ void ScDocument::SnapVisArea( Rectangle& rRect ) const
/*N*/ {
/*N*/   ScTable* pTable = pTab[nVisibleTab];
/*N*/   if (!pTable)
/*N*/   {
/*N*/       DBG_ERROR("SetEmbedded ohne Tabelle");
/*N*/       return;
/*N*/   }
/*N*/
/*N*/   USHORT nCol = 0;
/*N*/   lcl_SnapHor( pTable, rRect.Left(), nCol );
/*N*/   ++nCol;                                         // mindestens eine Spalte
/*N*/   lcl_SnapHor( pTable, rRect.Right(), nCol );
/*N*/
/*N*/   USHORT nRow = 0;
/*N*/   lcl_SnapVer( pTable, rRect.Top(), nRow );
/*N*/   ++nRow;                                         // mindestens eine Zeile
/*N*/   lcl_SnapVer( pTable, rRect.Bottom(), nRow );
/*N*/ }

/*N*/ void ScDocument::SetDocProtection( BOOL bProtect, const uno::Sequence<sal_Int8>& rPasswd )
/*N*/ {
/*N*/   bProtected = bProtect;
/*N*/   aProtectPass = rPasswd;
/*N*/ }

/*N*/ void ScDocument::SetTabProtection( USHORT nTab, BOOL bProtect, const uno::Sequence<sal_Int8>& rPasswd )
/*N*/ {
/*N*/   if (VALIDTAB(nTab))
/*N*/       if (pTab[nTab])
/*N*/           pTab[nTab]->SetProtection( bProtect, rPasswd );
/*N*/ }

/*N*/ BOOL ScDocument::IsDocProtected() const
/*N*/ {
/*N*/   return bProtected;
/*N*/ }

/*N*/ BOOL ScDocument::IsDocEditable() const
/*N*/ {
/*N*/   // import into read-only document is possible - must be extended if other filters use api
/*N*/
/*N*/   return !bProtected && ( !pShell || !pShell->IsReadOnly() || bImportingXML );
/*N*/ }

/*N*/ BOOL ScDocument::IsTabProtected( USHORT nTab ) const
/*N*/ {
/*N*/   if (VALIDTAB(nTab))
/*N*/       if (pTab[nTab])
/*N*/           return pTab[nTab]->IsProtected();
/*N*/
/*N*/   DBG_ERROR("Falsche Tabellennummer");
/*N*/   return FALSE;
/*N*/ }

/*N*/ const uno::Sequence<sal_Int8>& ScDocument::GetDocPassword() const
/*N*/ {
/*N*/   return aProtectPass;
/*N*/ }

/*N*/ const uno::Sequence<sal_Int8>& ScDocument::GetTabPassword( USHORT nTab ) const
/*N*/ {
/*N*/   if (VALIDTAB(nTab))
/*N*/       if (pTab[nTab])
/*N*/           return pTab[nTab]->GetPassword();
/*N*/
/*N*/   DBG_ERROR("Falsche Tabellennummer");
/*N*/   return aProtectPass;
/*N*/ }

/*N*/ const ScDocOptions& ScDocument::GetDocOptions() const
/*N*/ {
/*N*/   DBG_ASSERT( pDocOptions, "No DocOptions! :-(" );
/*N*/   return *pDocOptions;
/*N*/ }

/*N*/ void ScDocument::SetDocOptions( const ScDocOptions& rOpt )
/*N*/ {
/*N*/   USHORT d,m,y;
/*N*/
/*N*/   DBG_ASSERT( pDocOptions, "No DocOptions! :-(" );
/*N*/   *pDocOptions = rOpt;
/*N*/   rOpt.GetDate( d,m,y );
/*N*/
/*N*/   SvNumberFormatter* pFormatter = xPoolHelper->GetFormTable();
/*N*/   pFormatter->ChangeNullDate( d,m,y );
/*N*/   pFormatter->ChangeStandardPrec( (USHORT)rOpt.GetStdPrecision() );
/*N*/   pFormatter->SetYear2000( rOpt.GetYear2000() );
/*N*/ }

/*N*/ const ScViewOptions& ScDocument::GetViewOptions() const
/*N*/ {
/*N*/   DBG_ASSERT( pViewOptions, "No ViewOptions! :-(" );
/*N*/   return *pViewOptions;
/*N*/ }

/*N*/ void ScDocument::SetViewOptions( const ScViewOptions& rOpt )
/*N*/ {
/*N*/   DBG_ASSERT( pViewOptions, "No ViewOptions! :-(" );
/*N*/   *pViewOptions = rOpt;
/*N*/ }

/*N*/ void ScDocument::GetLanguage( LanguageType& rLatin, LanguageType& rCjk, LanguageType& rCtl ) const
/*N*/ {
/*N*/   rLatin = eLanguage;
/*N*/   rCjk = eCjkLanguage;
/*N*/   rCtl = eCtlLanguage;
/*N*/ }

/*N*/ void ScDocument::SetLanguage( LanguageType eLatin, LanguageType eCjk, LanguageType eCtl )
/*N*/ {
/*N*/   eLanguage = eLatin;
/*N*/   eCjkLanguage = eCjk;
/*N*/   eCtlLanguage = eCtl;
/*N*/   if ( xPoolHelper.isValid() )
/*N*/   {
/*N*/       ScDocumentPool* pPool = xPoolHelper->GetDocPool();
/*N*/       pPool->SetPoolDefaultItem( SvxLanguageItem( eLanguage, ATTR_FONT_LANGUAGE ) );
/*N*/       pPool->SetPoolDefaultItem( SvxLanguageItem( eCjkLanguage, ATTR_CJK_FONT_LANGUAGE ) );
/*N*/       pPool->SetPoolDefaultItem( SvxLanguageItem( eCtlLanguage, ATTR_CTL_FONT_LANGUAGE ) );
/*N*/   }
/*N*/
/*N*/   UpdateDrawLanguages();      // set edit engine defaults in drawing layer pool
/*N*/ }

/*N*/ Rectangle ScDocument::GetMMRect( USHORT nStartCol, USHORT nStartRow,
/*N*/                               USHORT nEndCol, USHORT nEndRow, USHORT nTab )
/*N*/ {
/*N*/   if (nTab > MAXTAB || !pTab[nTab])
/*N*/   {
/*N*/       DBG_ERROR("GetMMRect: falsche Tabelle");
/*N*/       return Rectangle(0,0,0,0);
/*N*/   }
/*N*/
/*N*/   USHORT i;
/*N*/   Rectangle aRect;
/*N*/
/*N*/   for (i=0; i<nStartCol; i++)
/*N*/       aRect.Left() += GetColWidth(i,nTab);
/*N*/   for (i=0; i<nStartRow; i++)
/*N*/       aRect.Top() += FastGetRowHeight(i,nTab);
/*N*/
/*N*/   aRect.Right()  = aRect.Left();
/*N*/   aRect.Bottom() = aRect.Top();
/*N*/
/*N*/   for (i=nStartCol; i<=nEndCol; i++)
/*N*/       aRect.Right() += GetColWidth(i,nTab);
/*N*/   for (i=nStartRow; i<=nEndRow; i++)
/*N*/       aRect.Bottom() += FastGetRowHeight(i,nTab);
/*N*/
/*N*/   aRect.Left()    = (long)(aRect.Left()   * HMM_PER_TWIPS);
/*N*/   aRect.Right()   = (long)(aRect.Right()  * HMM_PER_TWIPS);
/*N*/   aRect.Top()     = (long)(aRect.Top()    * HMM_PER_TWIPS);
/*N*/   aRect.Bottom()  = (long)(aRect.Bottom() * HMM_PER_TWIPS);
/*N*/
/*N*/   return aRect;
/*N*/ }

/*N*/ void ScDocument::SetExtDocOptions( ScExtDocOptions* pNewOptions )
/*N*/ {
/*N*/    DBG_ASSERT(0, "STRIP"); //STRIP001 delete pExtDocOptions;
//STRIP001 /*N*/    pExtDocOptions = pNewOptions;
/*N*/ }

//STRIP001 void ScDocument::DoMergeContents( USHORT nTab, USHORT nStartCol, USHORT nStartRow,
//STRIP001                                  USHORT nEndCol, USHORT nEndRow )
//STRIP001 {
//STRIP001  String aEmpty;
//STRIP001  String aTotal;
//STRIP001  String aCellStr;
//STRIP001  USHORT nCol;
//STRIP001  USHORT nRow;
//STRIP001  ScPostIt aCellNote;
//STRIP001  String aNoteStr;
//STRIP001  BOOL bDoNote = FALSE;
//STRIP001
//STRIP001  for (nRow=nStartRow; nRow<=nEndRow; nRow++)
//STRIP001      for (nCol=nStartCol; nCol<=nEndCol; nCol++)
//STRIP001      {
//STRIP001          GetString(nCol,nRow,nTab,aCellStr);
//STRIP001          if (aCellStr.Len())
//STRIP001          {
//STRIP001              if (aTotal.Len())
//STRIP001                  aTotal += ' ';
//STRIP001              aTotal += aCellStr;
//STRIP001          }
//STRIP001          if (nCol != nStartCol || nRow != nStartRow)
//STRIP001              SetString(nCol,nRow,nTab,aEmpty);
//STRIP001
//STRIP001          if (GetNote(nCol,nRow,nTab,aCellNote))
//STRIP001          {
//STRIP001              if (aNoteStr.Len())
//STRIP001                  aNoteStr += '\n';
//STRIP001              aNoteStr += aCellNote.GetText();
//STRIP001
//STRIP001              if (nCol != nStartCol || nRow != nStartRow)
//STRIP001              {
//STRIP001                  if (aCellNote.IsShown())
//STRIP001                      ScDetectiveFunc( this, nTab ).HideComment( nCol, nRow );
//STRIP001                  SetNote(nCol,nRow,nTab,ScPostIt());
//STRIP001                  bDoNote = TRUE;
//STRIP001              }
//STRIP001              //! Autor/Datum beibehalten, wenn's nur eine Notiz war??
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001  SetString(nStartCol,nStartRow,nTab,aTotal);
//STRIP001  if (bDoNote)
//STRIP001      SetNote(nStartCol,nStartRow,nTab,ScPostIt(aNoteStr));
//STRIP001 }

/*N*/ void ScDocument::DoMerge( USHORT nTab, USHORT nStartCol, USHORT nStartRow,
/*N*/                                   USHORT nEndCol, USHORT nEndRow )
/*N*/ {
/*N*/   ScMergeAttr aAttr( nEndCol-nStartCol+1, nEndRow-nStartRow+1 );
/*N*/   ApplyAttr( nStartCol, nStartRow, nTab, aAttr );
/*N*/
/*N*/   if ( nEndCol > nStartCol )
/*N*/       ApplyFlagsTab( nStartCol+1, nStartRow, nEndCol, nStartRow, nTab, SC_MF_HOR );
/*N*/   if ( nEndRow > nStartRow )
/*N*/       ApplyFlagsTab( nStartCol, nStartRow+1, nStartCol, nEndRow, nTab, SC_MF_VER );
/*N*/   if ( nEndCol > nStartCol && nEndRow > nStartRow )
/*N*/       ApplyFlagsTab( nStartCol+1, nStartRow+1, nEndCol, nEndRow, nTab, SC_MF_HOR | SC_MF_VER );
/*N*/ }

//STRIP001 void ScDocument::RemoveMerge( USHORT nCol, USHORT nRow, USHORT nTab )
//STRIP001 {
//STRIP001  const ScMergeAttr* pAttr = (const ScMergeAttr*)
//STRIP001                                  GetAttr( nCol, nRow, nTab, ATTR_MERGE );
//STRIP001
//STRIP001  if ( pAttr->GetColMerge() <= 1 && pAttr->GetRowMerge() <= 1 )
//STRIP001      return;
//STRIP001
//STRIP001  USHORT nEndCol = nCol + pAttr->GetColMerge() - 1;
//STRIP001  USHORT nEndRow = nRow + pAttr->GetRowMerge() - 1;
//STRIP001
//STRIP001  RemoveFlagsTab( nCol, nRow, nEndCol, nEndRow, nTab, SC_MF_HOR | SC_MF_VER );
//STRIP001
//STRIP001  const ScMergeAttr* pDefAttr = (const ScMergeAttr*)
//STRIP001                                      &xPoolHelper->GetDocPool()->GetDefaultItem( ATTR_MERGE );
//STRIP001  ApplyAttr( nCol, nRow, nTab, *pDefAttr );
//STRIP001 }

/*N*/ void ScDocument::ExtendPrintArea( OutputDevice* pDev, USHORT nTab,
/*N*/                   USHORT nStartCol, USHORT nStartRow, USHORT& rEndCol, USHORT nEndRow )
/*N*/ {
/*N*/   if ( nTab <= MAXTAB && pTab[nTab] )
/*N*/       pTab[nTab]->ExtendPrintArea( pDev, nStartCol, nStartRow, rEndCol, nEndRow );
/*N*/ }

/*N*/ void ScDocument::IncSizeRecalcLevel( USHORT nTab )
/*N*/ {
/*N*/   if ( nTab <= MAXTAB && pTab[nTab] )
/*N*/       pTab[nTab]->IncRecalcLevel();
/*N*/ }

/*N*/ void ScDocument::DecSizeRecalcLevel( USHORT nTab )
/*N*/ {
/*N*/   if ( nTab <= MAXTAB && pTab[nTab] )
/*N*/       pTab[nTab]->DecRecalcLevel();
/*N*/ }




