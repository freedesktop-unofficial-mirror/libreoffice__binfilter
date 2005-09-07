/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_docsh4.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 19:08:17 $
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
#if STLPORT_VERSION>=321
#include <math.h>       // prevent conflict between exception and std::exception
#endif

// auto strip #include "scitems.hxx"
// auto strip #include <bf_svx/eeitem.hxx>
#define ITEMID_FIELD EE_FEATURE_FIELD

#include <bf_sfx2/bindings.hxx>
#include <bf_sfx2/docfile.hxx>
// auto strip #include <bf_sfx2/docfilt.hxx>
#include <svtools/ehdl.hxx>
#include <basic/sbxcore.hxx>
// auto strip #include <bf_sfx2/printer.hxx>
#include <bf_sfx2/request.hxx>
#include <svtools/sfxecode.hxx>
#include <bf_sfx2/topfrm.hxx>
// auto strip #include <bf_offmgr/ofaitem.hxx>
#include <bf_offmgr/sbaitems.hxx>
// auto strip #include <sot/formats.hxx>
// auto strip #include <svtools/printdlg.hxx>
#include <svtools/whiter.hxx>
#include <vcl/msgbox.hxx>
#include <vcl/waitobj.hxx>
// auto strip #include <tools/multisel.hxx>
// auto strip #include <bf_svx/drawitem.hxx>
// auto strip #include <bf_svx/fmview.hxx>
// auto strip #include <bf_svx/pageitem.hxx>
// auto strip #include <bf_svx/svditer.hxx>
// auto strip #include <bf_svx/svdpage.hxx>
// auto strip #include <bf_sch/schdll.hxx>
// auto strip #ifndef _SVX_FMSHELL_HXX //autogen
// auto strip #include <bf_svx/fmshell.hxx>
// auto strip #endif
// auto strip #ifndef _SFX_PASSWD_HXX
// auto strip #include <bf_sfx2/passwd.hxx>
// auto strip #endif
// auto strip #ifndef _SVTOOLS_PASSWORDHELPER_HXX
// auto strip #include <svtools/PasswordHelper.hxx>
// auto strip #endif

#include "docsh.hxx"
#include "docfunc.hxx"
#include "bf_sc.hrc"
// auto strip #include "stlsheet.hxx"
#include "stlpool.hxx"
#include "appoptio.hxx"
#include "globstr.hrc"
// auto strip #include "global.hxx"
// auto strip #include "styledlg.hxx"
// auto strip #include "hfedtdlg.hxx"
#include "dbdocfun.hxx"
#include "printfun.hxx"              // DrawToDev
// auto strip #include "viewdata.hxx"
#include "tabvwsh.hxx"
// auto strip #include "impex.hxx"
// auto strip #include "attrib.hxx"
// auto strip #include "corodlg.hxx"
// auto strip #include "undodat.hxx"
// auto strip #include "autostyl.hxx"
// auto strip #include "undocell.hxx"
// auto strip #include "undotab.hxx"
// auto strip #include "inputhdl.hxx"
#include "dbcolect.hxx"
// auto strip #include "servobj.hxx"
// auto strip #include "rangenam.hxx"
#include "scmod.hxx"
// auto strip #include "scendlg.hxx"
// auto strip #include "chgviset.hxx"
// auto strip #include "reffact.hxx"
// auto strip #include "chartlis.hxx"
// auto strip #include "waitoff.hxx"
#include "tablink.hxx"      // ScDocumentLoader statics
// auto strip #include "drwlayer.hxx"
#include "docoptio.hxx"
// auto strip #include "undostyl.hxx"
// auto strip #include "rangeseq.hxx"
// auto strip #include "chgtrack.hxx"
// auto strip #include "printopt.hxx"

#ifndef _COM_SUN_STAR_DOCUMENT_UPDATEDOCMODE_HPP_
#include <com/sun/star/document/UpdateDocMode.hpp>
#endif
namespace binfilter {

//------------------------------------------------------------------

#define IS_SHARE_HEADER(set) \
    ((SfxBoolItem&) \
        ((SvxSetItem&)(set).Get(ATTR_PAGE_HEADERSET)).GetItemSet(). \
            Get(ATTR_PAGE_SHARED)).GetValue()

#define IS_SHARE_FOOTER(set) \
    ((SfxBoolItem&) \
        ((SvxSetItem&)(set).Get(ATTR_PAGE_FOOTERSET)).GetItemSet(). \
            Get(ATTR_PAGE_SHARED)).GetValue()

#define IS_AVAILABLE(WhichId,ppItem) \
    (pReqArgs->GetItemState((WhichId), TRUE, ppItem ) == SFX_ITEM_SET)

#define SC_PREVIEW_SIZE_X   10000
#define SC_PREVIEW_SIZE_Y   12400


//------------------------------------------------------------------

//STRIP001 BOOL ScDocShell::GetTabParam( const SfxItemSet* pArgs, USHORT nId, USHORT& rTab )
//STRIP001 {
//STRIP001  BOOL bOk = TRUE;
//STRIP001  rTab = 0;                   // zur Sicherheit...
//STRIP001
//STRIP001  const SfxPoolItem* pTabItem;
//STRIP001  if ( pArgs && pArgs->GetItemState( nId, TRUE, &pTabItem ) == SFX_ITEM_SET )
//STRIP001  {
//STRIP001      //  Parameter sind 1-based !!!
//STRIP001      USHORT nItemTab = ((const SfxUInt16Item*)pTabItem)->GetValue();
//STRIP001      USHORT nTabCount = aDocument.GetTableCount();
//STRIP001      if (nItemTab>0 && nItemTab<=nTabCount)
//STRIP001          rTab = nItemTab-1;
//STRIP001      else
//STRIP001          bOk = FALSE;
//STRIP001  }
//STRIP001  else                        // nichts angegeben -> sichtbare
//STRIP001  {
//STRIP001      ScTabViewShell* pVisibleSh = GetBestViewShell();
//STRIP001      if ( pVisibleSh )
//STRIP001          rTab = pVisibleSh->GetViewData()->GetTabNo();
//STRIP001      else
//STRIP001          bOk = FALSE;
//STRIP001  }
//STRIP001
//STRIP001  return bOk;
//STRIP001 }

//------------------------------------------------------------------

/*N*/ void ScDocShell::Execute( SfxRequest& rReq )
/*N*/ {
/*N*/   //  SID_SC_RANGE (Range),
/*N*/   //  SID_SC_CELLTEXT (CellText),
/*N*/   //  SID_SC_CELLS (Cells) - removed (old Basic)
/*N*/
/*N*/   const SfxItemSet* pReqArgs = rReq.GetArgs();
/*N*/   SfxBindings* pBindings = GetViewBindings();
/*N*/   BOOL bUndo (aDocument.IsUndoEnabled());
/*N*/
/*N*/   USHORT nSlot = rReq.GetSlot();
/*N*/   switch ( nSlot )
/*N*/   {
/*?*/       case SID_SC_SETTEXT:
/*?*/       {
/*?*/           const SfxPoolItem* pColItem;
/*?*/           const SfxPoolItem* pRowItem;
/*?*/           const SfxPoolItem* pTabItem;
/*?*/           const SfxPoolItem* pTextItem;
/*?*/           if( pReqArgs && IS_AVAILABLE( FN_PARAM_1, &pColItem ) &&
/*?*/                           IS_AVAILABLE( FN_PARAM_2, &pRowItem ) &&
/*?*/                           IS_AVAILABLE( FN_PARAM_3, &pTabItem ) &&
/*?*/                           IS_AVAILABLE( SID_SC_SETTEXT, &pTextItem ) )
/*?*/           {
/*?*/               //  Parameter sind 1-based !!!
/*?*/               USHORT nCol = ((SfxUInt16Item*)pColItem)->GetValue() - 1;
/*?*/               USHORT nRow = ((SfxUInt16Item*)pRowItem)->GetValue() - 1;
/*?*/               USHORT nTab = ((SfxUInt16Item*)pTabItem)->GetValue() - 1;
/*?*/
/*?*/               USHORT nTabCount = aDocument.GetTableCount();
/*?*/               if ( nCol <= MAXCOL && nRow <= MAXROW && nTab < nTabCount )
/*?*/               {
/*?*/                   if ( aDocument.IsBlockEditable( nTab, nCol,nRow, nCol, nRow ) )
/*?*/                   {
/*?*/                       String aVal = ((const SfxStringItem*)pTextItem)->GetValue();
/*?*/                       aDocument.SetString( nCol, nRow, nTab, aVal );
/*?*/
/*?*/                       PostPaintCell( nCol, nRow, nTab );
/*?*/                       SetDocumentModified();
/*?*/
/*?*/                       rReq.Done();
/*?*/                       break;
/*?*/                   }
/*?*/                   else                // geschuetzte Zelle
/*?*/                   {
/*?*/                       SbxBase::SetError( SbxERR_BAD_PARAMETER );      //! welchen Fehler ?
/*?*/                       break;
/*?*/                   }
/*?*/               }
/*?*/           }
/*?*/           SbxBase::SetError( SbxERR_NO_OBJECT );
/*?*/       }
/*?*/       break;
/*?*/
/*?*/
/*?*/       //  SID_SBA_QRY_CHANGETARGET gibts nicht mehr - auch in idl raus
/*?*/
/*?*/       case SID_SBA_IMPORT:
/*?*/       {
/*?*/           if (pReqArgs)
/*?*/           {
/*?*/               const sal_Unicode cSbaSep = 11;     // Trennzeichen
/*?*/
/*?*/               const SfxPoolItem* pItem;
/*?*/               String sSbaData, sTarget;
/*?*/               if ( pReqArgs->GetItemState( nSlot, TRUE, &pItem ) == SFX_ITEM_SET )
/*?*/                   sSbaData = ((const SfxStringItem*)pItem)->GetValue();
/*?*/               if ( pReqArgs->GetItemState( FN_PARAM_1, TRUE, &pItem ) == SFX_ITEM_SET )
/*?*/                   sTarget = ((const SfxStringItem*)pItem)->GetValue();
/*?*/
/*?*/               BOOL bIsNewArea = TRUE;         // Default TRUE (keine Nachfrage)
/*?*/               if ( pReqArgs->GetItemState( FN_PARAM_2, TRUE, &pItem ) == SFX_ITEM_SET )
/*?*/                   bIsNewArea = ((const SfxBoolItem*)pItem)->GetValue();
/*?*/
/*?*/               String sDBName  = sSbaData.GetToken(0,cSbaSep);     // Datenbankname
/*?*/               String sDBTable = sSbaData.GetToken(1,cSbaSep);     // Tabellen- oder Query-Name
/*?*/               String sTabFlag = sSbaData.GetToken(2,cSbaSep);
/*?*/               String sDBSql   = sSbaData.GetToken(3,cSbaSep);     // SQL im Klartext
/*?*/
/*?*/               BYTE nType = ScDbTable;     // "0" oder "1"
/*?*/               if ( sTabFlag.EqualsAscii("0") )        // "0" = Query, "1" = Table (Default)
/*?*/                   nType = ScDbQuery;
/*?*/
/*?*/               SbaSelectionListRef pSelectionList = new SbaSelectionList;
/*?*/               xub_StrLen nCount = sSbaData.GetTokenCount(cSbaSep);
/*?*/
/*?*/               for (xub_StrLen i = 4; i < nCount; i++)
/*?*/               {
/*?*/                   String aSelItem = sSbaData.GetToken(i,cSbaSep);
/*?*/                   if (aSelItem.Len())
/*?*/                   {
/*?*/                       void *pPtr = (void*)aSelItem.ToInt32();
/*?*/                       pSelectionList->Insert( pPtr, LIST_APPEND );
/*?*/                   }
/*?*/               }
/*?*/
/*?*/               // bei Bedarf neuen Datenbankbereich anlegen
/*?*/               BOOL bMakeArea = FALSE;
/*?*/               if (bIsNewArea)
/*?*/               {
/*?*/                   ScDBCollection* pDBColl = aDocument.GetDBCollection();
/*?*/                   USHORT nDummy;
/*?*/                   if ( !pDBColl || !pDBColl->SearchName( sTarget, nDummy ) )
/*?*/                   {
/*?*/                       ScAddress aPos;
/*?*/                       if ( aPos.Parse( sTarget, &aDocument ) & SCA_VALID )
/*?*/                       {
/*?*/                           bMakeArea = TRUE;
/*?*/                           if (bUndo)
/*?*/                           {
/*?*/                               String aStrImport = ScGlobal::GetRscString( STR_UNDO_IMPORTDATA );
/*?*/                               GetUndoManager()->EnterListAction( aStrImport, aStrImport );
/*?*/                           }
/*?*/
/*?*/                           ScDBData* pDBData = GetDBData( ScRange(aPos), SC_DB_IMPORT, FALSE );
/*?*/                           DBG_ASSERT(pDBData, "kann DB-Daten nicht anlegen");
/*?*/                           sTarget = pDBData->GetName();
/*?*/                       }
/*?*/                   }
/*?*/               }
/*?*/
/*?*/               // nachfragen, bevor alter DB-Bereich ueberschrieben wird
/*?*/               BOOL bDo = TRUE;
/*?*/               if (!bIsNewArea)
/*?*/               {
/*?*/                   String aTemplate = ScGlobal::GetRscString( STR_IMPORT_REPLACE );
/*?*/                   String aMessage = aTemplate.GetToken( 0, '#' );
/*?*/                   aMessage += sTarget;
/*?*/                   aMessage += aTemplate.GetToken( 1, '#' );
/*?*/
/*?*/                   QueryBox aBox( 0, WinBits(WB_YES_NO | WB_DEF_YES), aMessage );
/*?*/                   bDo = ( aBox.Execute() == RET_YES );
/*?*/               }
/*?*/
/*?*/               if (bDo)
/*M*/               {
/*M*/                     ::com::sun::star::uno::Reference<
/*M*/                         ::com::sun::star::sdbc::XResultSet > xResultSet;
/*M*/                     ScDBDocFunc(*this).UpdateImport( sTarget, sDBName,
/*M*/                             sDBTable, sDBSql, TRUE, nType, xResultSet,
/*M*/                             pSelectionList );
/*M*/                   rReq.Done();
/*M*/
/*M*/                   //  UpdateImport aktualisiert auch die internen Operationen
/*M*/               }
/*?*/               else
/*?*/                   rReq.Ignore();
/*?*/
/*?*/               if ( bMakeArea && bUndo)
/*?*/                   GetUndoManager()->LeaveListAction();
/*?*/           }
/*?*/           else
/*?*/               DBG_ERROR( "arguments expected" );
/*?*/       }
/*?*/       break;
/*?*/
/*?*/       case SID_CHART_SOURCE:
/*?*/       case SID_CHART_ADDSOURCE:
/*?*/           if (pReqArgs)
/*?*/           {
/*?*/               ScDocument* pDoc = GetDocument();
/*?*/               BOOL bUndo (pDoc->IsUndoEnabled());
/*?*/               const   SfxPoolItem* pItem;
/*?*/               String  aChartName, aRangeName;
/*?*/
/*?*/               ScRange         aSingleRange;
/*?*/               ScRangeListRef  aRangeListRef;
/*?*/               BOOL            bMultiRange = FALSE;
/*?*/
/*?*/               BOOL bColHeaders = TRUE;
/*?*/               BOOL bRowHeaders = TRUE;
/*?*/               BOOL bColInit = FALSE;
/*?*/               BOOL bRowInit = FALSE;
/*?*/               BOOL bAddRange = (nSlot == SID_CHART_ADDSOURCE);
/*?*/
/*?*/               if( IS_AVAILABLE( SID_CHART_NAME, &pItem ) )
/*?*/                   aChartName = ((const SfxStringItem*)pItem)->GetValue();
/*?*/
/*?*/               if( IS_AVAILABLE( SID_CHART_SOURCE, &pItem ) )
/*?*/                   aRangeName = ((const SfxStringItem*)pItem)->GetValue();
/*?*/
/*?*/               if( IS_AVAILABLE( FN_PARAM_1, &pItem ) )
/*?*/               {
/*?*/                   bColHeaders = ((const SfxBoolItem*)pItem)->GetValue();
/*?*/                   bColInit = TRUE;
/*?*/               }
/*?*/               if( IS_AVAILABLE( FN_PARAM_2, &pItem ) )
/*?*/               {
/*?*/                   bRowHeaders = ((const SfxBoolItem*)pItem)->GetValue();
/*?*/                   bRowInit = TRUE;
/*?*/               }
/*?*/
/*?*/               BOOL bValid = ( aSingleRange.ParseAny( aRangeName, pDoc ) & SCA_VALID ) != 0;
/*?*/               if (!bValid)
/*?*/               {
/*?*/                   aRangeListRef = new ScRangeList;
/*?*/                   aRangeListRef->Parse( aRangeName, pDoc );
/*?*/                   if ( aRangeListRef->Count() )
/*?*/                   {
/*?*/                       bMultiRange = TRUE;
/*?*/                       aSingleRange = *aRangeListRef->GetObject(0);    // fuer Header
/*?*/                       bValid = TRUE;
/*?*/                   }
/*?*/                   else
/*?*/                       aRangeListRef.Clear();
/*?*/               }
/*?*/
/*?*/               ScTabViewShell* pViewSh = ScTabViewShell::GetActiveViewShell();
/*?*/               if (pViewSh && bValid && aChartName.Len() != 0 )
/*?*/               {
/*?*/                   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 Window*   pParent = pViewSh->GetDialogParent();
//STRIP001 /*?*/                    Window* pDataWin = pViewSh->GetActiveWin();
//STRIP001 /*?*/
//STRIP001 /*?*/                    USHORT nCol1 = aSingleRange.aStart.Col();
//STRIP001 /*?*/                    USHORT nRow1 = aSingleRange.aStart.Row();
//STRIP001 /*?*/                    USHORT nCol2 = aSingleRange.aEnd.Col();
//STRIP001 /*?*/                    USHORT nRow2 = aSingleRange.aEnd.Row();
//STRIP001 /*?*/                    USHORT nTab = aSingleRange.aStart.Tab();
//STRIP001 /*?*/
//STRIP001 /*?*/                    //! immer oder gar nicht begrenzen ???
//STRIP001 /*?*/                    if (!bMultiRange)
//STRIP001 /*?*/                        aDocument.LimitChartArea( nTab, nCol1,nRow1, nCol2,nRow2 );
//STRIP001 /*?*/
//STRIP001 /*?*/                                        // Dialog fuer Spalten/Zeilenkoepfe
//STRIP001 /*?*/                    BOOL bOk = TRUE;
//STRIP001 /*?*/                    if ( !bAddRange && ( !bColInit || !bRowInit ) )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                                                // Spalten/Zeilenkoepfe testen wie in chartarr
//STRIP001 /*?*/                        USHORT i;
//STRIP001 /*?*/                        if (!bColInit)
//STRIP001 /*?*/                            for (i=nCol1; i<=nCol2 && bColHeaders; i++)
//STRIP001 /*?*/                                if (aDocument.HasValueData( i, nRow1, nTab ))
//STRIP001 /*?*/                                    bColHeaders = FALSE;
//STRIP001 /*?*/                        if (!bRowInit)
//STRIP001 /*?*/                            for (i=nRow1; i<=nRow2 && bRowHeaders; i++)
//STRIP001 /*?*/                                if (aDocument.HasValueData( nCol1, i, nTab ))
//STRIP001 /*?*/                                    bRowHeaders = FALSE;
//STRIP001 /*?*/
//STRIP001 /*?*/                        ScColRowLabelDlg aDlg( pParent, bRowHeaders, bColHeaders );
//STRIP001 /*?*/                        if ( aDlg.Execute() == RET_OK )
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            bColHeaders = aDlg.IsRow();     // Spaltenkoepfe = 1. Zeile
//STRIP001 /*?*/                            bRowHeaders = aDlg.IsCol();
//STRIP001 /*?*/
//STRIP001 /*?*/                            rReq.AppendItem(SfxBoolItem(FN_PARAM_1, bColHeaders));
//STRIP001 /*?*/                            rReq.AppendItem(SfxBoolItem(FN_PARAM_2, bRowHeaders));
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                        else
//STRIP001 /*?*/                            bOk = FALSE;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/
//STRIP001 /*?*/                    if (bOk)            // ausfuehren
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        if (bMultiRange)
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            if (bUndo)
//STRIP001 /*?*/                            {
//STRIP001 /*?*/                                GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                                    new ScUndoChartData( this, aChartName, aRangeListRef,
//STRIP001 /*?*/                                                            bColHeaders, bRowHeaders, bAddRange ) );
//STRIP001 /*?*/                            }
//STRIP001 /*?*/                            aDocument.UpdateChartArea( aChartName, aRangeListRef,
//STRIP001 /*?*/                                                        bColHeaders, bRowHeaders, bAddRange,
//STRIP001 /*?*/                                                        pDataWin );
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                        else
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            ScRange aNewRange( nCol1,nRow1,nTab, nCol2,nRow2,nTab );
//STRIP001 /*?*/                            if (bUndo)
//STRIP001 /*?*/                            {
//STRIP001 /*?*/                                GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                                    new ScUndoChartData( this, aChartName, aNewRange,
//STRIP001 /*?*/                                                            bColHeaders, bRowHeaders, bAddRange ) );
//STRIP001 /*?*/                            }
//STRIP001 /*?*/                            aDocument.UpdateChartArea( aChartName, aNewRange,
//STRIP001 /*?*/                                                        bColHeaders, bRowHeaders, bAddRange,
//STRIP001 /*?*/                                                        pDataWin );
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                    }
/*?*/               }
/*?*/               else
/*?*/                   DBG_ERROR("UpdateChartArea: keine ViewShell oder falsche Daten");
/*?*/               rReq.Done();
/*?*/           }
/*?*/           else
/*?*/               DBG_ERROR("SID_CHART_SOURCE ohne Argumente");
/*?*/           break;
/*?*/
/*?*/       case FID_AUTO_CALC:
/*?*/           {
/*?*/               BOOL bNewVal;
/*?*/               const SfxPoolItem* pItem;
/*?*/               if ( pReqArgs && SFX_ITEM_SET == pReqArgs->GetItemState( nSlot, TRUE, &pItem ) )
/*?*/                   bNewVal = ((const SfxBoolItem*)pItem)->GetValue();
/*?*/               else
/*?*/                   bNewVal = !aDocument.GetAutoCalc();     // Toggle fuer Menue
/*?*/               aDocument.SetAutoCalc( bNewVal );
/*?*/               SetDocumentModified();
/*?*/               if (pBindings)
/*?*/               {
/*?*/                   pBindings->Invalidate( FID_AUTO_CALC );
/*?*/ //                    pBindings->Invalidate( FID_RECALC );        // jetzt immer enabled
/*?*/               }
/*?*/                 rReq.AppendItem( SfxBoolItem( FID_AUTO_CALC, bNewVal ) );
/*?*/               rReq.Done();
/*?*/           }
/*?*/           break;
/*?*/       case FID_RECALC:
/*?*/           DoRecalc( rReq.IsAPI() );
/*?*/           rReq.Done();
/*?*/           break;
/*?*/       case FID_HARD_RECALC:
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 DoHardRecalc( rReq.IsAPI() );
//STRIP001 /*?*/            rReq.Done();
/*?*/           break;
/*N*/       case SID_UPDATETABLINKS:
/*N*/           {
/*N*/               ScDocument* pDoc = GetDocument();
/*N*/
/*N*/               ScLkUpdMode nSet=pDoc->GetLinkMode();
/*N*/
/*N*/               USHORT nDlgRet=RET_NO;
/*N*/               if(nSet==LM_UNKNOWN)
/*N*/               {
/*N*/                   ScAppOptions aAppOptions=SC_MOD()->GetAppOptions();
/*N*/                   nSet=aAppOptions.GetLinkMode();
/*N*/               }
/*N*/
/*N*/                 if (nCanUpdate == ::com::sun::star::document::UpdateDocMode::NO_UPDATE)
/*N*/                     nSet = LM_NEVER;
/*N*/                 else if (nCanUpdate == ::com::sun::star::document::UpdateDocMode::QUIET_UPDATE &&
/*N*/                     nSet == LM_ON_DEMAND)
/*N*/                     nSet = LM_NEVER;
/*N*/                 else if (nCanUpdate == ::com::sun::star::document::UpdateDocMode::FULL_UPDATE)
/*N*/                     nSet = LM_ALWAYS;
/*N*/
/*N*/               if(nSet==LM_ON_DEMAND)
/*N*/               {
/*N*/                   QueryBox aBox( GetDialogParent(), WinBits(WB_YES_NO | WB_DEF_YES),
/*N*/                                            ScGlobal::GetRscString(STR_RELOAD_TABLES) );
/*N*/
/*N*/                   nDlgRet=aBox.Execute();
/*N*/               }
/*N*/
/*N*/               if (nDlgRet == RET_YES || nSet==LM_ALWAYS)
/*N*/               {
/*N*/                   ReloadTabLinks();
/*N*/                   aDocument.UpdateDdeLinks();
/*N*/                   aDocument.UpdateAreaLinks();
/*N*/
/*N*/                   //! Test, ob Fehler
/*N*/                   rReq.Done();
/*N*/               }
/*N*/               else
/*N*/                   rReq.Ignore();
/*N*/           }
/*N*/           break;
/*N*/
/*?*/       case SID_REIMPORT_AFTER_LOAD:
/*?*/           {
/*?*/               //  wird nach dem Laden aufgerufen, wenn DB-Bereiche mit
/*?*/               //  weggelassenen Daten enthalten sind
/*?*/
/*?*/               BOOL bDone = FALSE;
/*?*/                 ScDBCollection* pDBColl = aDocument.GetDBCollection();
/*?*/
/*?*/                 if ((nCanUpdate != ::com::sun::star::document::UpdateDocMode::NO_UPDATE) &&
/*?*/                    (nCanUpdate != ::com::sun::star::document::UpdateDocMode::QUIET_UPDATE))
/*?*/                 {
/*?*/                   ScRange aRange;
/*?*/                   ScTabViewShell* pViewSh = GetBestViewShell();
/*?*/                   DBG_ASSERT(pViewSh,"SID_REIMPORT_AFTER_LOAD: keine View");
/*?*/                     if (pViewSh && pDBColl)
/*?*/                   {
/*?*/                       QueryBox aBox( GetDialogParent(), WinBits(WB_YES_NO | WB_DEF_YES),
/*?*/                                               ScGlobal::GetRscString(STR_REIMPORT_AFTER_LOAD) );
/*?*/                       if (aBox.Execute() == RET_YES)
/*?*/                       {
/*?*/                           for (USHORT i=0; i<pDBColl->GetCount(); i++)
/*?*/                           {
/*?*/                               ScDBData* pDBData = (*pDBColl)[i];
/*?*/                               if ( pDBData->IsStripData() &&
/*?*/                                       pDBData->HasImportParam() && !pDBData->HasImportSelection() )
/*?*/                               {
/*?*/                                   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 pDBData->GetArea(aRange);
//STRIP001 /*?*/                                    pViewSh->MarkRange(aRange);
//STRIP001 /*?*/
//STRIP001 /*?*/                                    //  Import und interne Operationen wie SID_REFRESH_DBAREA
//STRIP001 /*?*/                                    //  (Abfrage auf Import hier nicht noetig)
//STRIP001 /*?*/
//STRIP001 /*?*/                                    ScImportParam aImportParam;
//STRIP001 /*?*/                                    pDBData->GetImportParam( aImportParam );
//STRIP001 /*?*/                                    BOOL bContinue = pViewSh->ImportData( aImportParam );
//STRIP001 /*?*/                                    pDBData->SetImportParam( aImportParam );
//STRIP001 /*?*/
//STRIP001 /*?*/                                    //  markieren (Groesse kann sich geaendert haben)
//STRIP001 /*?*/                                    pDBData->GetArea(aRange);
//STRIP001 /*?*/                                    pViewSh->MarkRange(aRange);
//STRIP001 /*?*/
//STRIP001 /*?*/                                    if ( bContinue )    // #41905# Fehler beim Import -> Abbruch
//STRIP001 /*?*/                                    {
//STRIP001 /*?*/                                        //  interne Operationen, wenn welche gespeichert
//STRIP001 /*?*/
//STRIP001 /*?*/                                        if ( pDBData->HasQueryParam() || pDBData->HasSortParam() ||
//STRIP001 /*?*/                                                                        pDBData->HasSubTotalParam() )
//STRIP001 /*?*/                                            pViewSh->RepeatDB();
//STRIP001 /*?*/
//STRIP001 /*?*/                                        //  Pivottabellen die den Bereich als Quelldaten haben
//STRIP001 /*?*/
//STRIP001 /*?*/                                        RefreshPivotTables(aRange);
//STRIP001 /*?*/                                    }
/*?*/                               }
/*?*/                           }
/*?*/                           bDone = TRUE;
/*?*/                       }
/*?*/                   }
/*?*/                 }
/*?*/
/*?*/                 if ( !bDone && pDBColl )
/*?*/                 {
/*?*/                     //    wenn nicht, dann aber die abhaengigen Formeln updaten
/*?*/                     //! auch fuer einzelne Bereiche, die nicht aktualisiert werden koennen
/*?*/
/*?*/                     aDocument.CalcAll();      //! nur die abhaengigen
/*?*/                     PostDataChanged();
/*?*/                 }
/*?*/
/*?*/                 if (bDone)
/*?*/                   rReq.Done();
/*?*/               else
/*?*/                   rReq.Ignore();
/*?*/           }
/*?*/           break;
/*?*/
/*?*/
/*?*/       case SID_AUTO_STYLE:
/*?*/           DBG_ERROR("use ScAutoStyleHint instead of SID_AUTO_STYLE");
/*?*/           break;
/*?*/
/*?*/       case SID_GET_COLORTABLE:
/*?*/           {
/*?*/               DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //    passende ColorTable ist per PutItem gesetzt worden
//STRIP001 /*?*/                SvxColorTableItem* pColItem = (SvxColorTableItem*)GetItem(SID_COLOR_TABLE);
//STRIP001 /*?*/                XColorTable* pTable = pColItem->GetColorTable();
//STRIP001 /*?*/                rReq.SetReturnValue(OfaPtrItem(SID_GET_COLORTABLE, pTable));
/*?*/           }
/*?*/           break;
/*?*/
/*?*/       case FID_CHG_RECORD:
/*?*/           {
/*?*/               ScDocument* pDoc = GetDocument();
/*?*/               if(pDoc!=NULL)
/*?*/               {
/*?*/                     // get argument (recorded macro)
/*?*/                     SFX_REQUEST_ARG( rReq, pItem, SfxBoolItem, FID_CHG_RECORD, sal_False );
/*?*/                     BOOL bDo = TRUE;
/*?*/
/*?*/                     // desired state
/*?*/                     ScChangeTrack* pChangeTrack = pDoc->GetChangeTrack();
/*?*/                     BOOL bActivateTracking = (pChangeTrack == 0);   // toggle
/*?*/                     if ( pItem )
/*?*/                         bActivateTracking = pItem->GetValue();      // from argument
/*?*/
/*?*/                     if ( !bActivateTracking )
/*?*/                   {
/*?*/                         if ( !pItem )
/*?*/                         {
/*?*/                             // no dialog on playing the macro
/*?*/                             WarningBox aBox( GetDialogParent(),
/*?*/                                 WinBits(WB_YES_NO | WB_DEF_NO),
/*?*/                                 ScGlobal::GetRscString( STR_END_REDLINING ) );
/*?*/                             bDo = ( aBox.Execute() == RET_YES );
/*?*/                         }
/*?*/
/*?*/                         if ( bDo )
/*?*/                         {
/*?*/                             DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if ( pChangeTrack->IsProtected() )
//STRIP001 /*?*/                                 bDo = ExecuteChangeProtectionDialog();
//STRIP001 /*?*/                             if ( bDo )
//STRIP001 /*?*/                             {
//STRIP001 /*?*/                                 pDoc->EndChangeTracking();
//STRIP001 /*?*/                                 PostPaintGridAll();
//STRIP001 /*?*/                             }
/*?*/                         }
/*?*/                   }
/*?*/                   else
/*?*/                   {
//STRIP001 /*?*/                        pDoc->StartChangeTracking();
//STRIP001 /*?*/                        ScChangeViewSettings aChangeViewSet;
//STRIP001 /*?*/                        aChangeViewSet.SetShowChanges(TRUE);
//STRIP001 /*?*/                        pDoc->SetChangeViewSettings(aChangeViewSet);
/*?*/                   }
/*?*/
/*?*/                     if ( bDo )
/*?*/                     {
/*?*/                         //  update "accept changes" dialog
/*?*/                         //! notify all views
/*?*/                         SfxViewFrame* pViewFrm = SfxViewFrame::Current();
/*?*/                         if ( pViewFrm && pViewFrm->HasChildWindow(FID_CHG_ACCEPT) )
/*?*/                         {
/*?*/                             SfxChildWindow* pChild = pViewFrm->GetChildWindow(FID_CHG_ACCEPT);
/*?*/                             if (pChild)
/*?*/                             {
/*?*/                                 DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ((ScAcceptChgDlgWrapper*)pChild)->ReInitDlg();
/*?*/                             }
/*?*/                         }
/*?*/
/*?*/                         // Slots invalidieren
/*?*/                         if (pBindings)
/*?*/                             pBindings->InvalidateAll(FALSE);
/*?*/                         if ( !pItem )
/*?*/                             rReq.AppendItem( SfxBoolItem( FID_CHG_RECORD, bActivateTracking ) );
/*?*/                         rReq.Done();
/*?*/                     }
/*?*/                     else
/*?*/                         rReq.Ignore();
/*?*/               }
/*?*/           }
/*?*/           break;
/*?*/
/*?*/         case SID_CHG_PROTECT :
/*?*/             {
/*?*/                 DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if ( ExecuteChangeProtectionDialog() )
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                    rReq.Done();
//STRIP001 /*?*/                    SetDocumentModified();
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else
//STRIP001 /*?*/                    rReq.Ignore();
/*?*/             }
/*?*/             break;
/*?*/
/*?*/       case SID_DOCUMENT_MERGE:
/*?*/       case SID_DOCUMENT_COMPARE:
/*?*/           {
/*?*/                 BOOL bDo = TRUE;
/*?*/                 ScChangeTrack* pChangeTrack = aDocument.GetChangeTrack();
/*?*/                 if ( pChangeTrack )
/*?*/                 {
/*?*/                     DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if ( nSlot == SID_DOCUMENT_COMPARE )
//STRIP001 /*?*/                     {   //! old changes trace will be lost
//STRIP001 /*?*/                         WarningBox aBox( GetDialogParent(),
//STRIP001 /*?*/                             WinBits(WB_YES_NO | WB_DEF_NO),
//STRIP001 /*?*/                             ScGlobal::GetRscString( STR_END_REDLINING ) );
//STRIP001 /*?*/                         if( aBox.Execute() == RET_YES )
//STRIP001 /*?*/                             bDo = ExecuteChangeProtectionDialog( TRUE );
//STRIP001 /*?*/                         else
//STRIP001 /*?*/                             bDo = FALSE;
//STRIP001 /*?*/                     }
//STRIP001 /*?*/                     else    // merge might reject some actions
//STRIP001 /*?*/                         bDo = ExecuteChangeProtectionDialog( TRUE );
/*?*/                 }
/*?*/                 if ( !bDo )
/*?*/                 {
/*?*/                     rReq.Ignore();
/*?*/                     break;
/*?*/                 }
/*?*/               SfxApplication* pApp = SFX_APP();
/*?*/               const SfxPoolItem* pItem;
/*?*/               SfxMedium* pMed = NULL;
/*?*/               if ( pReqArgs &&
/*?*/                    pReqArgs->GetItemState( SID_FILE_NAME, TRUE, &pItem ) == SFX_ITEM_SET &&
/*?*/                    pItem->ISA(SfxStringItem) )
/*?*/               {
/*?*/                   String aFileName = ((const SfxStringItem*)pItem)->GetValue();
/*?*/
/*?*/                   String aFilterName;
/*?*/                   if ( pReqArgs->GetItemState( SID_FILTER_NAME, TRUE, &pItem ) == SFX_ITEM_SET &&
/*?*/                        pItem->ISA(SfxStringItem) )
/*?*/                   {
/*?*/                       aFilterName = ((const SfxStringItem*)pItem)->GetValue();
/*?*/                   }
/*?*/                   String aOptions;
/*?*/                   if ( pReqArgs->GetItemState( SID_FILE_FILTEROPTIONS, TRUE, &pItem ) == SFX_ITEM_SET &&
/*?*/                        pItem->ISA(SfxStringItem) )
/*?*/                   {
/*?*/                       aOptions = ((const SfxStringItem*)pItem)->GetValue();
/*?*/                   }
/*?*/                   short nVersion = 0;
/*?*/                   if ( pReqArgs->GetItemState( SID_VERSION, TRUE, &pItem ) == SFX_ITEM_SET &&
/*?*/                        pItem->ISA(SfxInt16Item) )
/*?*/                   {
/*?*/                       nVersion = ((const SfxInt16Item*)pItem)->GetValue();
/*?*/                   }
/*?*/
/*?*/                   //  kein Filter angegeben -> Detection
/*?*/                   if ( !aFilterName.Len() )
/*?*/                       ScDocumentLoader::GetFilterName( aFileName, aFilterName, aOptions );
/*?*/
/*?*/                   //  filter name from dialog contains application prefix,
/*?*/                   //  GetFilter needs name without the prefix.
/*?*/                   ScDocumentLoader::RemoveAppPrefix( aFilterName );
/*?*/
/*?*/                   const SfxFilter* pFilter = pApp->GetFilter( ScDocShell::Factory(), aFilterName );
/*?*/                   SfxItemSet* pSet = new SfxAllItemSet( pApp->GetPool() );
/*?*/                   if ( aOptions.Len() )
/*?*/                       pSet->Put( SfxStringItem( SID_FILE_FILTEROPTIONS, aOptions ) );
/*?*/                   if ( nVersion != 0 )
/*?*/                       pSet->Put( SfxInt16Item( SID_VERSION, nVersion ) );
/*?*/                   pMed = new SfxMedium( aFileName, STREAM_STD_READ, FALSE, pFilter, pSet );
/*?*/               }
/*?*/               else
/*?*/               {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/                    pMed = pApp->InsertDocumentDialog( 0, ScDocShell::Factory() );
//STRIP001 /*?*/                    if ( pMed )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        //  kompletten Request zum Aufzeichnen zusammenbasteln
//STRIP001 /*?*/                        rReq.AppendItem( SfxStringItem( SID_FILE_NAME, pMed->GetName() ) );
//STRIP001 /*?*/                        if ( nSlot == SID_DOCUMENT_COMPARE )
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            // Filter und Options nur bei Compare
//STRIP001 /*?*/                            if (pMed->GetFilter())
//STRIP001 /*?*/                                rReq.AppendItem( SfxStringItem( SID_FILTER_NAME,
//STRIP001 /*?*/                                                pMed->GetFilter()->GetFilterName() ) );
//STRIP001 /*?*/                            String aOptions = ScDocumentLoader::GetOptions(*pMed);
//STRIP001 /*?*/                            if (aOptions.Len())
//STRIP001 /*?*/                                rReq.AppendItem( SfxStringItem( SID_FILE_FILTEROPTIONS, aOptions ) );
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                        SfxItemSet* pSet = pMed->GetItemSet();
//STRIP001 /*?*/                        if ( pSet &&
//STRIP001 /*?*/                             pSet->GetItemState( SID_VERSION, TRUE, &pItem ) == SFX_ITEM_SET &&
//STRIP001 /*?*/                             pItem->ISA(SfxInt16Item) )
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            rReq.AppendItem( *pItem );
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                    }
/*?*/               }
/*?*/
/*?*/               if ( pMed )     // nun wirklich ausfuehren...
/*?*/               {
/*?*/                   SfxErrorContext aEc( ERRCTX_SFX_OPENDOC, pMed->GetName() );
/*?*/
/*?*/                   ScDocShell* pOtherDocSh = new ScDocShell;
/*?*/                   SvEmbeddedObjectRef aDocShTablesRef = pOtherDocSh;
/*?*/                   pOtherDocSh->DoLoad( pMed );
/*?*/                   ULONG nErr = pOtherDocSh->GetErrorCode();
/*?*/                   if (nErr)
/*?*/                       ErrorHandler::HandleError( nErr );          // auch Warnings
/*?*/
/*?*/                   if ( !pOtherDocSh->GetError() )                 // nur Errors
/*?*/                   {
/*?*/                       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 BOOL bHadTrack = ( aDocument.GetChangeTrack() != NULL );
//STRIP001 /*?*/
//STRIP001 /*?*/                        if ( nSlot == SID_DOCUMENT_COMPARE )
//STRIP001 /*?*/                            CompareDocument( *pOtherDocSh->GetDocument() );
//STRIP001 /*?*/                        else
//STRIP001 /*?*/                            MergeDocument( *pOtherDocSh->GetDocument() );
//STRIP001 /*?*/
//STRIP001 /*?*/                        //  show "accept changes" dialog
//STRIP001 /*?*/                        //! get view for this document!
//STRIP001 /*?*/
//STRIP001 /*?*/                        SfxViewFrame* pViewFrm = SfxViewFrame::Current();
//STRIP001 /*?*/                        if (pViewFrm)
//STRIP001 /*?*/                            pViewFrm->ShowChildWindow(ScAcceptChgDlgWrapper::GetChildWindowId(),TRUE); //@51669
//STRIP001 /*?*/                        SfxBindings* pBindings = GetViewBindings();
//STRIP001 /*?*/                        if (pBindings)
//STRIP001 /*?*/                            pBindings->Invalidate(FID_CHG_ACCEPT);
//STRIP001 /*?*/
//STRIP001 /*?*/                        rReq.SetReturnValue( SfxInt32Item( nSlot, 0 ) );        //! ???????
//STRIP001 /*?*/                        rReq.Done();
//STRIP001 /*?*/
//STRIP001 /*?*/                        if (!bHadTrack)         //  neu eingeschaltet -> auch anzeigen
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            ScChangeViewSettings* pOldSet = aDocument.GetChangeViewSettings();
//STRIP001 /*?*/                            if ( !pOldSet || !pOldSet->ShowChanges() )
//STRIP001 /*?*/                            {
//STRIP001 /*?*/                                ScChangeViewSettings aChangeViewSet;
//STRIP001 /*?*/                                aChangeViewSet.SetShowChanges(TRUE);
//STRIP001 /*?*/                                aDocument.SetChangeViewSettings(aChangeViewSet);
//STRIP001 /*?*/                            }
//STRIP001 /*?*/                        }
/*?*/                   }
/*?*/                   pOtherDocSh->DoClose();     // delete passiert mit der Ref
/*?*/               }
/*?*/           }
/*?*/           break;
/*?*/
/*?*/       case SID_DELETE_SCENARIO:
/*?*/           if (pReqArgs)
/*?*/           {
/*?*/               const SfxPoolItem* pItem;
/*?*/               if ( pReqArgs->GetItemState( nSlot, TRUE, &pItem ) == SFX_ITEM_SET )
/*?*/               {
/*?*/                   if ( pItem->ISA(SfxStringItem) )
/*?*/                   {
/*?*/                       String aName = ((const SfxStringItem*)pItem)->GetValue();
/*?*/                       USHORT nTab;
/*?*/                       if (aDocument.GetTable( aName, nTab ))
/*?*/                       {
/*?*/                           //  DeleteTable von viewfunc nach docfunc verschieben!
/*?*/
/*?*/                           ScTabViewShell* pSh = GetBestViewShell();
/*?*/                           if ( pSh )
/*?*/                           {
/*?*/                               //! SetTabNo in DeleteTable weglassen?
/*?*/                               DBG_BF_ASSERT(0, "STRIP"); //STRIP001 USHORT nDispTab = pSh->GetViewData()->GetTabNo();
//STRIP001 /*?*/                                pSh->DeleteTable( nTab );
//STRIP001 /*?*/                                pSh->SetTabNo(nDispTab);
//STRIP001 /*?*/                                rReq.Done();
/*?*/                           }
/*?*/                       }
/*?*/                   }
/*?*/               }
/*?*/           }
/*?*/           break;
/*?*/
/*?*/       case SID_EDIT_SCENARIO:
/*?*/           {
/*?*/               const SfxPoolItem* pItem;
/*?*/               if ( pReqArgs->GetItemState( nSlot, TRUE, &pItem ) == SFX_ITEM_SET )
/*?*/               {
/*?*/                   if ( pItem->ISA(SfxStringItem) )
/*?*/                   {
/*?*/                       String aName = ((const SfxStringItem*)pItem)->GetValue();
/*?*/                       USHORT nTab;
/*?*/                       if (aDocument.GetTable( aName, nTab ))
/*?*/                       {
/*?*/                           if (aDocument.IsScenario(nTab))
/*?*/                           {
/*?*/                               DBG_BF_ASSERT(0, "STRIP"); //STRIP001 String aComment;
//STRIP001 /*?*/                                Color aColor;
//STRIP001 /*?*/                                USHORT nFlags;
//STRIP001 /*?*/                                aDocument.GetScenarioData( nTab, aComment, aColor, nFlags );
//STRIP001 /*?*/
//STRIP001 /*?*/                                //! anderen Titel am Dialog setzen
//STRIP001 /*?*/                                ScNewScenarioDlg* pNewDlg =
//STRIP001 /*?*/                                    new ScNewScenarioDlg( GetDialogParent(), aName, TRUE );
//STRIP001 /*?*/                                pNewDlg->SetScenarioData( aName, aComment, aColor, nFlags );
//STRIP001 /*?*/                                if ( pNewDlg->Execute() == RET_OK )
//STRIP001 /*?*/                                {
//STRIP001 /*?*/                                    pNewDlg->GetScenarioData( aName, aComment, aColor, nFlags );
//STRIP001 /*?*/                                    ModifyScenario( nTab, aName, aComment, aColor, nFlags );
//STRIP001 /*?*/                                    rReq.Done();
//STRIP001 /*?*/                                }
//STRIP001 /*?*/                                delete pNewDlg;
/*?*/                           }
/*?*/                       }
/*?*/                   }
/*?*/               }
/*?*/           }
/*?*/           break;
/*?*/
/*?*/       case SID_ATTR_YEAR2000 :
/*?*/       {
/*?*/           const SfxPoolItem* pItem;
/*?*/           if ( pReqArgs->GetItemState( nSlot, TRUE, &pItem ) == SFX_ITEM_SET )
/*?*/           {
/*?*/               if ( pItem->ISA(SfxUInt16Item) )
/*?*/               {
/*?*/                   UINT16 nY2k = ((SfxUInt16Item*)pItem)->GetValue();
/*?*/                   // immer an den DocOptions setzen, damit das auch fuer SO50
/*?*/                   // gespeichert wird (und alle Abfragen bisher auch darauf laufen).
/*?*/                   // SetDocOptions propagiert das an den NumberFormatter
/*?*/                   ScDocOptions aDocOpt( aDocument.GetDocOptions() );
/*?*/                   aDocOpt.SetYear2000( nY2k );
/*?*/                   aDocument.SetDocOptions( aDocOpt );
/*?*/                   // die FormShell soll es mitbekommen
/*?*/                   ScTabViewShell* pSh = GetBestViewShell();
/*?*/                   if ( pSh )
/*?*/                   {
/*?*/                       FmFormShell* pFSh = pSh->GetFormShell();
/*?*/                       if ( pFSh )
/*?*/                           {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 pFSh->SetY2KState( nY2k );
/*?*/                   }
/*?*/               }
/*?*/           }
/*?*/       }
/*?*/       break;
/*?*/
/*?*/       default:
/*?*/       {
/*?*/           // kleiner (?) Hack -> forward der Slots an TabViewShell
/*?*/           ScTabViewShell* pSh = GetBestViewShell();
/*?*/           if ( pSh )
/*?*/               pSh->Execute( rReq );
/*?*/           else
/*?*/               SbxBase::SetError( SbxERR_NO_ACTIVE_OBJECT );
/*?*/       }
/*N*/   }
/*N*/ }


//------------------------------------------------------------------

//STRIP001 BOOL ScDocShell::ExecuteChangeProtectionDialog( BOOL bJustQueryIfProtected )
//STRIP001 {
//STRIP001     BOOL bDone = FALSE;
//STRIP001     ScChangeTrack* pChangeTrack = aDocument.GetChangeTrack();
//STRIP001     if ( pChangeTrack )
//STRIP001     {
//STRIP001         BOOL bProtected = pChangeTrack->IsProtected();
//STRIP001         if ( bJustQueryIfProtected && !bProtected )
//STRIP001             return TRUE;
//STRIP001
//STRIP001         String aTitle( ScResId( bProtected ? SCSTR_CHG_UNPROTECT : SCSTR_CHG_PROTECT ) );
//STRIP001         String aText( ScResId( SCSTR_PASSWORD ) );
//STRIP001         String aPassword;
//STRIP001
//STRIP001         SfxPasswordDialog* pDlg = new SfxPasswordDialog(
//STRIP001             GetDialogParent(), &aText );
//STRIP001         pDlg->SetText( aTitle );
//STRIP001         pDlg->SetMinLen( 1 );
//STRIP001         pDlg->SetHelpId( SID_CHG_PROTECT );
//STRIP001         pDlg->SetEditHelpId( HID_CHG_PROTECT );
//STRIP001         if ( !bProtected )
//STRIP001             pDlg->ShowExtras( SHOWEXTRAS_CONFIRM );
//STRIP001         if ( pDlg->Execute() == RET_OK )
//STRIP001             aPassword = pDlg->GetPassword();
//STRIP001         delete pDlg;
//STRIP001
//STRIP001         if ( aPassword.Len() )
//STRIP001         {
//STRIP001             if ( bProtected )
//STRIP001             {
//STRIP001                 if ( SvPasswordHelper::CompareHashPassword(pChangeTrack->GetProtection(), aPassword) )
//STRIP001                 {
//STRIP001                     if ( bJustQueryIfProtected )
//STRIP001                         bDone = TRUE;
//STRIP001                     else
//STRIP001                         pChangeTrack->SetProtection(
//STRIP001                             ::com::sun::star::uno::Sequence< sal_Int8 > (0) );
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     InfoBox aBox( GetDialogParent(),
//STRIP001                         String( ScResId( SCSTR_WRONGPASSWORD ) ) );
//STRIP001                     aBox.Execute();
//STRIP001                 }
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 ::com::sun::star::uno::Sequence< sal_Int8 > aPass;
//STRIP001                 SvPasswordHelper::GetHashPassword( aPass, aPassword );
//STRIP001                 pChangeTrack->SetProtection( aPass );
//STRIP001             }
//STRIP001             if ( bProtected != pChangeTrack->IsProtected() )
//STRIP001             {
//STRIP001                 //  update "accept changes" dialog
//STRIP001                 //! notify all views
//STRIP001                 SfxViewFrame* pViewFrm = SfxViewFrame::Current();
//STRIP001                 if ( pViewFrm && pViewFrm->HasChildWindow( FID_CHG_ACCEPT ) )
//STRIP001                 {
//STRIP001                     SfxChildWindow* pChild = pViewFrm->GetChildWindow( FID_CHG_ACCEPT );
//STRIP001                     if ( pChild )
//STRIP001                         ((ScAcceptChgDlgWrapper*)pChild)->ReInitDlg();
//STRIP001                 }
//STRIP001                 bDone = TRUE;
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001     else if ( bJustQueryIfProtected )
//STRIP001         bDone = TRUE;
//STRIP001     return bDone;
//STRIP001 }


//------------------------------------------------------------------

/*N*/ void ScDocShell::DoRecalc( BOOL bApi )
/*N*/ {
/*N*/   BOOL bDone = FALSE;
/*N*/   ScTabViewShell* pSh = GetBestViewShell();
/*N*/   if ( pSh )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ScInputHandler* pHdl = SC_MOD()->GetInputHdl(pSh);
//STRIP001 /*?*/        if ( pHdl && pHdl->IsInputMode() && pHdl->IsFormulaMode() && !bApi )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pHdl->FormulaPreview();     // Teilergebnis als QuickHelp
//STRIP001 /*?*/            bDone = TRUE;
//STRIP001 /*?*/        }
//STRIP001 /*?*/        else
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pSh->UpdateInputLine();     // InputEnterHandler
//STRIP001 /*?*/            pSh->UpdateInputHandler();
//STRIP001 /*?*/        }
/*N*/   }
/*N*/   if (!bDone)                         // sonst Dokument neu berechnen
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 WaitObject aWaitObj( GetDialogParent() );
//STRIP001 /*?*/        aDocument.CalcFormulaTree();
//STRIP001 /*?*/        if ( pSh )
//STRIP001 /*?*/            pSh->UpdateCharts(TRUE);
//STRIP001 /*?*/
//STRIP001 /*?*/        //  #47939# Wenn es Charts gibt, dann alles painten, damit nicht
//STRIP001 /*?*/        //  PostDataChanged und die Charts nacheinander kommen und Teile
//STRIP001 /*?*/        //  doppelt gepainted werden.
//STRIP001 /*?*/
//STRIP001 /*?*/        ScChartListenerCollection* pCharts = aDocument.GetChartListenerCollection();
//STRIP001 /*?*/        if ( pCharts && pCharts->GetCount() )
//STRIP001 /*?*/            PostPaintGridAll();
//STRIP001 /*?*/        else
//STRIP001 /*?*/            PostDataChanged();
/*N*/   }
/*N*/ }

/*N*/ void ScDocShell::DoHardRecalc( BOOL bApi )
/*N*/ {
/*N*/    WaitObject aWaitObj( GetDialogParent() );
/*N*/   ScTabViewShell* pSh = GetBestViewShell();
/*N*/   if ( pSh )
/*N*/   {
/*N*/       pSh->UpdateInputLine();     // InputEnterHandler
/*N*/       pSh->UpdateInputHandler();
/*N*/   }
/*N*/   aDocument.CalcAll();
/*N*/   GetDocFunc().DetectiveRefresh();    // erzeugt eigenes Undo
/*N*/   if ( pSh )
/*N*/       pSh->UpdateCharts(TRUE);
/*N*/   PostPaintGridAll();
/*N*/ }

//------------------------------------------------------------------

//STRIP001 void ScDocShell::DoAutoStyle( const ScRange& rRange, const String& rStyle )
//STRIP001 {
//STRIP001  ScStyleSheetPool* pStylePool = aDocument.GetStyleSheetPool();
//STRIP001  ScStyleSheet* pStyleSheet =
//STRIP001      pStylePool->FindCaseIns( rStyle, SFX_STYLE_FAMILY_PARA );
//STRIP001  if (!pStyleSheet)
//STRIP001      pStyleSheet = (ScStyleSheet*)
//STRIP001          pStylePool->Find( ScGlobal::GetRscString(STR_STYLENAME_STANDARD), SFX_STYLE_FAMILY_PARA );
//STRIP001  if (pStyleSheet)
//STRIP001  {
//STRIP001      DBG_ASSERT(rRange.aStart.Tab() == rRange.aEnd.Tab(),
//STRIP001                      "DoAutoStyle mit mehreren Tabellen");
//STRIP001      USHORT nTab = rRange.aStart.Tab();
//STRIP001      USHORT nStartCol = rRange.aStart.Col();
//STRIP001      USHORT nStartRow = rRange.aStart.Row();
//STRIP001      USHORT nEndCol = rRange.aEnd.Col();
//STRIP001      USHORT nEndRow = rRange.aEnd.Row();
//STRIP001      aDocument.ApplyStyleAreaTab( nStartCol, nStartRow, nEndCol, nEndRow, nTab, *pStyleSheet );
//STRIP001      aDocument.ExtendMerge( nStartCol, nStartRow, nEndCol, nEndRow, nTab );
//STRIP001      PostPaint( nStartCol, nStartRow, nTab, nEndCol, nEndRow, nTab, PAINT_GRID );
//STRIP001  }
//STRIP001 }

//------------------------------------------------------------------

/*N*/ void ScDocShell::NotifyStyle( const SfxStyleSheetHint& rHint )
/*N*/ {
/*N*/   USHORT nId = rHint.GetHint();
/*N*/   const SfxStyleSheetBase* pStyle = rHint.GetStyleSheet();
/*N*/   if (!pStyle)
/*N*/       return;
/*N*/
/*N*/   if ( pStyle->GetFamily() == SFX_STYLE_FAMILY_PAGE )
/*N*/   {
/*N*/       if ( nId == SFX_STYLESHEET_MODIFIED )
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ScDocShellModificator aModificator( *this );
//STRIP001 /*?*/
//STRIP001 /*?*/            String aNewName = pStyle->GetName();
//STRIP001 /*?*/            String aOldName = aNewName;
//STRIP001 /*?*/            BOOL bExtended = rHint.ISA(SfxStyleSheetHintExtended);      // Name geaendert?
//STRIP001 /*?*/            if (bExtended)
//STRIP001 /*?*/                aOldName = ((SfxStyleSheetHintExtended&)rHint).GetOldName();
//STRIP001 /*?*/
//STRIP001 /*?*/            if ( aNewName != aOldName )
//STRIP001 /*?*/                aDocument.RenamePageStyleInUse( aOldName, aNewName );
//STRIP001 /*?*/
//STRIP001 /*?*/            USHORT nTabCount = aDocument.GetTableCount();
//STRIP001 /*?*/            for (USHORT nTab=0; nTab<nTabCount; nTab++)
//STRIP001 /*?*/                if (aDocument.GetPageStyle(nTab) == aNewName)   // schon auf neu angepasst
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    aDocument.PageStyleModified( nTab, aNewName );
//STRIP001 /*?*/                    ScPrintFunc aPrintFunc( this, GetPrinter(), nTab );
//STRIP001 /*?*/                    aPrintFunc.UpdatePages();
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/            aModificator.SetDocumentModified();
//STRIP001 /*?*/
//STRIP001 /*?*/            if (bExtended)
//STRIP001 /*?*/            {
//STRIP001 /*?*/                SfxBindings* pBindings = GetViewBindings();
//STRIP001 /*?*/                if (pBindings)
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    pBindings->Invalidate( SID_STATUS_PAGESTYLE );
//STRIP001 /*?*/                    pBindings->Invalidate( SID_STYLE_FAMILY4 );
//STRIP001 /*?*/                    pBindings->Invalidate( FID_RESET_PRINTZOOM );
//STRIP001 /*M*/                    pBindings->Invalidate( SID_ATTR_PARA_LEFT_TO_RIGHT );
//STRIP001 /*M*/                    pBindings->Invalidate( SID_ATTR_PARA_RIGHT_TO_LEFT );
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   //  alles andere geht ueber Slots...
/*N*/ }

//  wie in printfun.cxx
#define ZOOM_MIN    10

//STRIP001 void ScDocShell::SetPrintZoom( USHORT nTab, USHORT nScale, USHORT nPages )
//STRIP001 {
//STRIP001  BOOL bUndo(aDocument.IsUndoEnabled());
//STRIP001  String aStyleName = aDocument.GetPageStyle( nTab );
//STRIP001  ScStyleSheetPool* pStylePool = aDocument.GetStyleSheetPool();
//STRIP001  SfxStyleSheetBase* pStyleSheet = pStylePool->Find( aStyleName, SFX_STYLE_FAMILY_PAGE );
//STRIP001  DBG_ASSERT( pStyleSheet, "PageStyle not found" );
//STRIP001  if ( pStyleSheet )
//STRIP001  {
//STRIP001      ScDocShellModificator aModificator( *this );
//STRIP001
//STRIP001      SfxItemSet& rSet = pStyleSheet->GetItemSet();
//STRIP001      if (bUndo)
//STRIP001      {
//STRIP001          USHORT nOldScale = ((const SfxUInt16Item&)rSet.Get(ATTR_PAGE_SCALE)).GetValue();
//STRIP001          USHORT nOldPages = ((const SfxUInt16Item&)rSet.Get(ATTR_PAGE_SCALETOPAGES)).GetValue();
//STRIP001          GetUndoManager()->AddUndoAction( new ScUndoPrintZoom(
//STRIP001                          this, nTab, nOldScale, nOldPages, nScale, nPages ) );
//STRIP001      }
//STRIP001
//STRIP001      rSet.Put( SfxUInt16Item( ATTR_PAGE_SCALE, nScale ) );
//STRIP001      rSet.Put( SfxUInt16Item( ATTR_PAGE_SCALETOPAGES, nPages ) );
//STRIP001
//STRIP001      ScPrintFunc aPrintFunc( this, GetPrinter(), nTab );
//STRIP001      aPrintFunc.UpdatePages();
//STRIP001      aModificator.SetDocumentModified();
//STRIP001
//STRIP001      SfxBindings* pBindings = GetViewBindings();
//STRIP001      if (pBindings)
//STRIP001          pBindings->Invalidate( FID_RESET_PRINTZOOM );
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL ScDocShell::AdjustPrintZoom( const ScRange& rRange )
//STRIP001 {
//STRIP001  BOOL bChange = FALSE;
//STRIP001  USHORT nTab = rRange.aStart.Tab();
//STRIP001
//STRIP001  String aStyleName = aDocument.GetPageStyle( nTab );
//STRIP001  ScStyleSheetPool* pStylePool = aDocument.GetStyleSheetPool();
//STRIP001  SfxStyleSheetBase* pStyleSheet = pStylePool->Find( aStyleName, SFX_STYLE_FAMILY_PAGE );
//STRIP001  DBG_ASSERT( pStyleSheet, "PageStyle not found" );
//STRIP001  if ( pStyleSheet )
//STRIP001  {
//STRIP001      SfxItemSet& rSet = pStyleSheet->GetItemSet();
//STRIP001      BOOL bHeaders = ((const SfxBoolItem&)rSet.Get(ATTR_PAGE_HEADERS)).GetValue();
//STRIP001      USHORT nOldScale = ((const SfxUInt16Item&)rSet.Get(ATTR_PAGE_SCALE)).GetValue();
//STRIP001      USHORT nOldPages = ((const SfxUInt16Item&)rSet.Get(ATTR_PAGE_SCALETOPAGES)).GetValue();
//STRIP001      const ScRange* pRepeatCol = aDocument.GetRepeatColRange( nTab );
//STRIP001      const ScRange* pRepeatRow = aDocument.GetRepeatRowRange( nTab );
//STRIP001
//STRIP001      //  benoetigte Skalierung fuer Selektion ausrechnen
//STRIP001
//STRIP001      USHORT nNewScale = nOldScale;
//STRIP001      USHORT i;
//STRIP001
//STRIP001      long nBlkTwipsX = 0;
//STRIP001      if (bHeaders)
//STRIP001          nBlkTwipsX += (long) PRINT_HEADER_WIDTH;
//STRIP001      USHORT nStartCol = rRange.aStart.Col();
//STRIP001      USHORT nEndCol = rRange.aEnd.Col();
//STRIP001      if ( pRepeatCol && nStartCol >= pRepeatCol->aStart.Col() )
//STRIP001      {
//STRIP001          for ( i=pRepeatCol->aStart.Col(); i<=pRepeatCol->aEnd.Col(); i++ )
//STRIP001              nBlkTwipsX += aDocument.GetColWidth( i, nTab );
//STRIP001          if ( nStartCol <= pRepeatCol->aEnd.Col() )
//STRIP001              nStartCol = pRepeatCol->aEnd.Col() + 1;
//STRIP001      }
//STRIP001      for ( i=nStartCol; i<=nEndCol; i++ )
//STRIP001          nBlkTwipsX += aDocument.GetColWidth( i, nTab );
//STRIP001
//STRIP001      long nBlkTwipsY = 0;
//STRIP001      if (bHeaders)
//STRIP001          nBlkTwipsY += (long) PRINT_HEADER_HEIGHT;
//STRIP001      USHORT nStartRow = rRange.aStart.Row();
//STRIP001      USHORT nEndRow = rRange.aEnd.Row();
//STRIP001      if ( pRepeatRow && nStartRow >= pRepeatRow->aStart.Row() )
//STRIP001      {
//STRIP001          for ( i=pRepeatRow->aStart.Row(); i<=pRepeatRow->aEnd.Row(); i++ )
//STRIP001              nBlkTwipsY += aDocument.FastGetRowHeight( i, nTab );
//STRIP001          if ( nStartRow <= pRepeatRow->aEnd.Row() )
//STRIP001              nStartRow = pRepeatRow->aEnd.Row() + 1;
//STRIP001      }
//STRIP001      for ( i=nStartRow; i<=nEndRow; i++ )
//STRIP001          nBlkTwipsY += aDocument.FastGetRowHeight( i, nTab );
//STRIP001
//STRIP001      Size aPhysPage;
//STRIP001      long nHdr, nFtr;
//STRIP001      ScPrintFunc aOldPrFunc( this, GetPrinter(), nTab );
//STRIP001      aOldPrFunc.GetScaleData( aPhysPage, nHdr, nFtr );
//STRIP001      nBlkTwipsY += nHdr + nFtr;
//STRIP001
//STRIP001      if ( nBlkTwipsX == 0 )      // #100639# hidden columns/rows may lead to 0
//STRIP001          nBlkTwipsX = 1;
//STRIP001      if ( nBlkTwipsY == 0 )
//STRIP001          nBlkTwipsY = 1;
//STRIP001
//STRIP001      long nNeeded = Min( aPhysPage.Width()  * 100 / nBlkTwipsX,
//STRIP001                          aPhysPage.Height() * 100 / nBlkTwipsY );
//STRIP001      if ( nNeeded < ZOOM_MIN )
//STRIP001          nNeeded = ZOOM_MIN;         // Begrenzung
//STRIP001      if ( nNeeded < (long) nNewScale )
//STRIP001          nNewScale = (USHORT) nNeeded;
//STRIP001
//STRIP001      bChange = ( nNewScale != nOldScale || nOldPages != 0 );
//STRIP001      if ( bChange )
//STRIP001          SetPrintZoom( nTab, nNewScale, 0 );
//STRIP001  }
//STRIP001  return bChange;
//STRIP001 }

/*N*/ void ScDocShell::PageStyleModified( const String& rStyleName, BOOL bApi )
/*N*/ {
/*N*/   ScDocShellModificator aModificator( *this );
/*N*/
/*N*/   BOOL bWarn = FALSE;
/*N*/
/*N*/   USHORT nTabCount = aDocument.GetTableCount();
/*N*/   USHORT nUseTab = MAXTAB+1;
/*N*/   for (USHORT nTab=0; nTab<nTabCount && nUseTab>MAXTAB; nTab++)
/*N*/       if ( aDocument.GetPageStyle(nTab) == rStyleName &&
/*N*/               ( !bApi || aDocument.GetPageSize(nTab).Width() ) )
/*N*/           nUseTab = nTab;
/*N*/                               // bei bApi nur, wenn Umbrueche schon angezeigt
/*N*/
/*N*/   if (nUseTab<=MAXTAB)        // nicht verwendet -> nichts zu tun
/*N*/   {
/*?*/       ScPrintFunc aPrintFunc( this, GetPrinter(), nUseTab );  //! ohne CountPages auskommen
/*?*/       if (!aPrintFunc.UpdatePages())                          //  setzt Umbrueche auf allen Tabs
/*?*/           bWarn = TRUE;
/*?*/
/*?*/       if (bWarn && !bApi)
/*?*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ScWaitCursorOff aWaitOff( GetDialogParent() );
//STRIP001 /*?*/            InfoBox aInfoBox(GetDialogParent(),
//STRIP001 /*?*/                             ScGlobal::GetRscString(STR_PRINT_INVALID_AREA));
//STRIP001 /*?*/            aInfoBox.Execute();
/*?*/       }
/*N*/   }
/*N*/
/*N*/   aModificator.SetDocumentModified();
/*N*/
/*N*/   SfxBindings* pBindings = GetViewBindings();
/*M*/   if (pBindings)
/*M*/   {
/*M*/       pBindings->Invalidate( FID_RESET_PRINTZOOM );
/*M*/       pBindings->Invalidate( SID_ATTR_PARA_LEFT_TO_RIGHT );
/*M*/       pBindings->Invalidate( SID_ATTR_PARA_RIGHT_TO_LEFT );
/*M*/   }
/*N*/ }

//STRIP001 void ScDocShell::ExecutePageStyle( SfxViewShell& rCaller,
//STRIP001                                 SfxRequest&   rReq,
//STRIP001                                 USHORT        nCurTab )
//STRIP001 {
//STRIP001  const SfxItemSet* pReqArgs = rReq.GetArgs();
//STRIP001
//STRIP001  switch ( rReq.GetSlot() )
//STRIP001  {
//STRIP001      case SID_STATUS_PAGESTYLE:  // Click auf StatusBar-Control
//STRIP001      case SID_FORMATPAGE:
//STRIP001          {
//STRIP001              if ( pReqArgs != NULL )
//STRIP001              {
//STRIP001              }
//STRIP001              else if ( pReqArgs == NULL )
//STRIP001              {
//STRIP001                  BOOL bUndo(aDocument.IsUndoEnabled());
//STRIP001                  String aOldName = aDocument.GetPageStyle( nCurTab );
//STRIP001                  ScStyleSheetPool* pStylePool = aDocument.GetStyleSheetPool();
//STRIP001                  SfxStyleSheetBase* pStyleSheet
//STRIP001                      = pStylePool->Find( aOldName, SFX_STYLE_FAMILY_PAGE );
//STRIP001
//STRIP001                  DBG_ASSERT( pStyleSheet, "PageStyle not found! :-/" );
//STRIP001
//STRIP001                  if ( pStyleSheet )
//STRIP001                  {
//STRIP001                      ScStyleSaveData aOldData;
//STRIP001                      if (bUndo)
//STRIP001                          aOldData.InitFromStyle( pStyleSheet );
//STRIP001
//STRIP001                      SfxItemSet&     rStyleSet = pStyleSheet->GetItemSet();
//STRIP001
//STRIP001                      ScStyleDlg* pDlg = new ScStyleDlg( GetDialogParent(),
//STRIP001                                                         *pStyleSheet,
//STRIP001                                                         RID_SCDLG_STYLES_PAGE );
//STRIP001
//STRIP001                      if ( pDlg->Execute() == RET_OK )
//STRIP001                      {
//STRIP001                          const SfxItemSet* pOutSet = pDlg->GetOutputItemSet();
//STRIP001
//STRIP001                          WaitObject aWait( GetDialogParent() );
//STRIP001
//STRIP001                          String aNewName = pStyleSheet->GetName();
//STRIP001                          if ( aNewName != aOldName &&
//STRIP001                              aDocument.RenamePageStyleInUse( aOldName, aNewName ) )
//STRIP001                          {
//STRIP001                              SfxBindings* pBindings = GetViewBindings();
//STRIP001                              if (pBindings)
//STRIP001                              {
//STRIP001                                  pBindings->Invalidate( SID_STATUS_PAGESTYLE );
//STRIP001                                  pBindings->Invalidate( FID_RESET_PRINTZOOM );
//STRIP001                              }
//STRIP001                          }
//STRIP001
//STRIP001                          if ( pOutSet )
//STRIP001                              aDocument.ModifyStyleSheet( *pStyleSheet, *pOutSet );
//STRIP001
//STRIP001                          // merken fuer GetState():
//STRIP001                          GetPageOnFromPageStyleSet( &rStyleSet, nCurTab, bHeaderOn, bFooterOn );
//STRIP001                          rCaller.GetViewFrame()->GetBindings().Invalidate( SID_HFEDIT );
//STRIP001
//STRIP001                          ScStyleSaveData aNewData;
//STRIP001                          aNewData.InitFromStyle( pStyleSheet );
//STRIP001                          if (bUndo)
//STRIP001                          {
//STRIP001                              GetUndoManager()->AddUndoAction(
//STRIP001                                      new ScUndoModifyStyle( this, SFX_STYLE_FAMILY_PAGE,
//STRIP001                                                  aOldData, aNewData ) );
//STRIP001                          }
//STRIP001
//STRIP001                          PageStyleModified( aNewName, FALSE );
//STRIP001                          rReq.Done();
//STRIP001                      }
//STRIP001                      delete pDlg;
//STRIP001
//STRIP001                      rStyleSet.ClearItem( ATTR_PAGE_PAPERTRAY );
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case SID_HFEDIT:
//STRIP001          {
//STRIP001              if ( pReqArgs != NULL )
//STRIP001              {
//STRIP001              }
//STRIP001              else if ( pReqArgs == NULL )
//STRIP001              {
//STRIP001                  String aStr( aDocument.GetPageStyle( nCurTab ) );
//STRIP001
//STRIP001                  ScStyleSheetPool* pStylePool
//STRIP001                      = aDocument.GetStyleSheetPool();
//STRIP001
//STRIP001                  SfxStyleSheetBase* pStyleSheet
//STRIP001                      = pStylePool->Find( aStr, SFX_STYLE_FAMILY_PAGE );
//STRIP001
//STRIP001                  DBG_ASSERT( pStyleSheet, "PageStyle not found! :-/" );
//STRIP001
//STRIP001                  if ( pStyleSheet )
//STRIP001                  {
//STRIP001                      SfxItemSet&  rStyleSet = pStyleSheet->GetItemSet();
//STRIP001
//STRIP001                      SvxPageUsage eUsage =
//STRIP001                          SvxPageUsage( ((const SvxPageItem&)
//STRIP001                                          rStyleSet.Get( ATTR_PAGE )).
//STRIP001                                              GetPageUsage() );
//STRIP001                      BOOL bShareHeader = IS_SHARE_HEADER(rStyleSet);
//STRIP001                      BOOL bShareFooter = IS_SHARE_FOOTER(rStyleSet);
//STRIP001                      USHORT nResId = 0;
//STRIP001
//STRIP001                      switch ( eUsage )
//STRIP001                      {
//STRIP001                          case SVX_PAGE_LEFT:
//STRIP001                          case SVX_PAGE_RIGHT:
//STRIP001                          {
//STRIP001                              if ( bHeaderOn && bFooterOn )
//STRIP001                                  nResId = RID_SCDLG_HFEDIT;
//STRIP001                              else if ( SVX_PAGE_RIGHT == eUsage )
//STRIP001                              {
//STRIP001                                  if ( !bHeaderOn && bFooterOn )
//STRIP001                                      nResId = RID_SCDLG_HFEDIT_RIGHTFOOTER;
//STRIP001                                  else if ( bHeaderOn && !bFooterOn )
//STRIP001                                      nResId = RID_SCDLG_HFEDIT_RIGHTHEADER;
//STRIP001                              }
//STRIP001                              else
//STRIP001                              {
//STRIP001                                  //  #69193a# respect "shared" setting
//STRIP001                                  if ( !bHeaderOn && bFooterOn )
//STRIP001                                      nResId = bShareFooter ?
//STRIP001                                                  RID_SCDLG_HFEDIT_RIGHTFOOTER :
//STRIP001                                                  RID_SCDLG_HFEDIT_LEFTFOOTER;
//STRIP001                                  else if ( bHeaderOn && !bFooterOn )
//STRIP001                                      nResId = bShareHeader ?
//STRIP001                                                  RID_SCDLG_HFEDIT_RIGHTHEADER :
//STRIP001                                                  RID_SCDLG_HFEDIT_LEFTHEADER;
//STRIP001                              }
//STRIP001                          }
//STRIP001                          break;
//STRIP001
//STRIP001                          case SVX_PAGE_MIRROR:
//STRIP001                          case SVX_PAGE_ALL:
//STRIP001                          default:
//STRIP001                          {
//STRIP001                              if ( !bShareHeader && !bShareFooter )
//STRIP001                              {
//STRIP001                                  if ( bHeaderOn && bFooterOn )
//STRIP001                                      nResId = RID_SCDLG_HFEDIT_ALL;
//STRIP001                                  else if ( !bHeaderOn && bFooterOn )
//STRIP001                                      nResId = RID_SCDLG_HFEDIT_FOOTER;
//STRIP001                                  else if ( bHeaderOn && !bFooterOn )
//STRIP001                                      nResId = RID_SCDLG_HFEDIT_HEADER;
//STRIP001                              }
//STRIP001                              else if ( bShareHeader && bShareFooter )
//STRIP001                              {
//STRIP001                                  if ( bHeaderOn && bFooterOn )
//STRIP001                                      nResId = RID_SCDLG_HFEDIT;
//STRIP001                                  else
//STRIP001                                  {
//STRIP001                                      if ( !bHeaderOn && bFooterOn )
//STRIP001                                          nResId = RID_SCDLG_HFEDIT_RIGHTFOOTER;
//STRIP001                                      else if ( bHeaderOn && !bFooterOn )
//STRIP001                                          nResId = RID_SCDLG_HFEDIT_RIGHTHEADER;
//STRIP001                                  }
//STRIP001                              }
//STRIP001                              else if ( !bShareHeader &&  bShareFooter )
//STRIP001                              {
//STRIP001                                  if ( bHeaderOn && bFooterOn )
//STRIP001                                      nResId = RID_SCDLG_HFEDIT_SFTR;
//STRIP001                                  else if ( !bHeaderOn && bFooterOn )
//STRIP001                                      nResId = RID_SCDLG_HFEDIT_RIGHTFOOTER;
//STRIP001                                  else if ( bHeaderOn && !bFooterOn )
//STRIP001                                      nResId = RID_SCDLG_HFEDIT_HEADER;
//STRIP001                              }
//STRIP001                              else if (  bShareHeader && !bShareFooter )
//STRIP001                              {
//STRIP001                                  if ( bHeaderOn && bFooterOn )
//STRIP001                                      nResId = RID_SCDLG_HFEDIT_SHDR;
//STRIP001                                  else if ( !bHeaderOn && bFooterOn )
//STRIP001                                      nResId = RID_SCDLG_HFEDIT_FOOTER;
//STRIP001                                  else if ( bHeaderOn && !bFooterOn )
//STRIP001                                      nResId = RID_SCDLG_HFEDIT_RIGHTHEADER;
//STRIP001                              }
//STRIP001                          }
//STRIP001                      }
//STRIP001
//STRIP001                      ScHFEditDlg* pDlg
//STRIP001                           = new ScHFEditDlg( SFX_APP()->GetViewFrame(),
//STRIP001                                              GetDialogParent(),
//STRIP001                                              rStyleSet,
//STRIP001                                              aStr,
//STRIP001                                              nResId );
//STRIP001
//STRIP001                      if ( pDlg->Execute() == RET_OK )
//STRIP001                      {
//STRIP001                          const SfxItemSet* pOutSet = pDlg->GetOutputItemSet();
//STRIP001
//STRIP001                          if ( pOutSet )
//STRIP001                              aDocument.ModifyStyleSheet( *pStyleSheet, *pOutSet );
//STRIP001
//STRIP001                          SetDocumentModified();
//STRIP001                          rReq.Done();
//STRIP001                      }
//STRIP001                      delete pDlg;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      default:
//STRIP001      break;
//STRIP001  }
//STRIP001 }

/*N*/ void ScDocShell::GetStatePageStyle( SfxViewShell& rCaller,
/*N*/                                   SfxItemSet&     rSet,
/*N*/                                   USHORT          nCurTab )
/*N*/ {
/*N*/   SfxWhichIter aIter(rSet);
/*N*/   USHORT nWhich = aIter.FirstWhich();
/*N*/   while ( nWhich )
/*N*/   {
/*N*/       switch (nWhich)
/*N*/       {
/*N*/           case SID_STATUS_PAGESTYLE:
/*N*/               rSet.Put( SfxStringItem( nWhich, aDocument.GetPageStyle( nCurTab ) ) );
/*N*/               break;
/*N*/
/*?*/           case SID_HFEDIT:
/*?*/               {
/*?*/                   String              aStr        = aDocument.GetPageStyle( nCurTab );
/*?*/                   ScStyleSheetPool*   pStylePool  = aDocument.GetStyleSheetPool();
/*?*/                   SfxStyleSheetBase*  pStyleSheet = pStylePool->Find( aStr, SFX_STYLE_FAMILY_PAGE );
/*?*/
/*?*/                   DBG_ASSERT( pStyleSheet, "PageStyle not found! :-/" );
/*?*/
/*?*/                   if ( pStyleSheet )
/*?*/                   {
/*?*/                       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SfxItemSet& rStyleSet = pStyleSheet->GetItemSet();
//STRIP001 /*?*/
//STRIP001 /*?*/                        GetPageOnFromPageStyleSet( &rStyleSet, nCurTab, bHeaderOn, bFooterOn );
//STRIP001 /*?*/
//STRIP001 /*?*/                        if ( !bHeaderOn && !bFooterOn )
//STRIP001 /*?*/                            rSet.DisableItem( nWhich );
/*?*/                   }
/*?*/               }
/*?*/               break;
/*N*/       }
/*N*/
/*N*/       nWhich = aIter.NextWhich();
/*N*/   }
/*N*/ }

//STRIP001 void ScDocShell::PreparePrint( PrintDialog* pPrintDialog, ScMarkData* pMarkData )
//STRIP001 {
//STRIP001  SfxPrinter* pPrinter = GetPrinter();
//STRIP001  if ( !pPrinter ) return;
//STRIP001
//STRIP001  delete pOldJobSetup;                        // gesetzt nur bei Fehler in StartJob()
//STRIP001  pOldJobSetup = new ScJobSetup( pPrinter );  // Einstellungen merken
//STRIP001
//STRIP001  //  Einstellungen fuer die erste gedruckte Seite muessen hier (vor StartJob) gesetzt werden
//STRIP001  //! Selection etc. mit Print() zusammenfassen !!!
//STRIP001  //! Seiten nur einmal zaehlen
//STRIP001
//STRIP001  //  get settings from print options sub-dialog
//STRIP001  ScPrintOptions aOptions;
//STRIP001     const SfxItemSet& rOptionSet = pPrinter->GetOptions();
//STRIP001  const SfxPoolItem* pItem;
//STRIP001  BOOL bHasOptions = ( rOptionSet.GetItemState(SID_SCPRINTOPTIONS, FALSE, &pItem) == SFX_ITEM_SET );
//STRIP001  if (bHasOptions)
//STRIP001      aOptions = ((const ScTpPrintItem*)pItem)->GetPrintOptions();
//STRIP001  else
//STRIP001      aOptions = SC_MOD()->GetPrintOptions();     // use configuration
//STRIP001
//STRIP001  BOOL bAllTabs = TRUE;
//STRIP001  USHORT nTabCount = aDocument.GetTableCount();
//STRIP001  USHORT nTab;
//STRIP001  long nTotalPages = 0;                       // alle Seiten
//STRIP001  long aPageArr[MAXTAB+1];                    // Seiten pro Tabelle
//STRIP001  for ( nTab=0; nTab<nTabCount; nTab++ )      // nPages und nTotalPages ermitteln
//STRIP001  {
//STRIP001      ScPrintFunc aPrintFunc( this, pPrinter, nTab, 0,0,NULL, &aOptions );
//STRIP001      long nThisTab = aPrintFunc.GetTotalPages();
//STRIP001      aPageArr[nTab] = nThisTab;
//STRIP001      nTotalPages += nThisTab;
//STRIP001  }
//STRIP001
//STRIP001  MultiSelection aPageRanges;         // zu druckende Seiten
//STRIP001  aPageRanges.SetTotalRange( Range( 0, RANGE_MAX ) );
//STRIP001  aPageRanges.Select( Range(1,nTotalPages) );
//STRIP001  PrintDialogRange eDlgOption = pPrintDialog ? pPrintDialog->GetCheckedRange() : PRINTDIALOG_ALL;
//STRIP001  switch ( eDlgOption )
//STRIP001  {
//STRIP001      case PRINTDIALOG_RANGE:
//STRIP001          aPageRanges = MultiSelection( pPrintDialog->GetRangeText() );
//STRIP001          break;
//STRIP001
//STRIP001      case PRINTDIALOG_SELECTION:
//STRIP001          //  pMarkedRange interessiert hier nicht
//STRIP001          bAllTabs = FALSE;
//STRIP001          break;
//STRIP001  }
//STRIP001
//STRIP001  if ( !aOptions.GetAllSheets() )      // option "only selected sheets" - also for ALL and RANGE
//STRIP001      bAllTabs = FALSE;
//STRIP001
//STRIP001  if (!bAllTabs)          // Gesamt-Seitenzahl bei Selektion
//STRIP001  {
//STRIP001      nTotalPages = 0;
//STRIP001      for (nTab=0; nTab<nTabCount; nTab++)
//STRIP001          if ( !pMarkData || pMarkData->GetTableSelect(nTab) )
//STRIP001              nTotalPages += aPageArr[nTab];
//STRIP001      if ( eDlgOption != PRINTDIALOG_RANGE )
//STRIP001          aPageRanges.Select( Range(1,nTotalPages) );
//STRIP001  }
//STRIP001
//STRIP001  BOOL bFound = FALSE;        // erste Seite gefunden
//STRIP001  long nTabStart = 0;
//STRIP001  for ( nTab=0; nTab<nTabCount && !bFound; nTab++ )
//STRIP001  {
//STRIP001      if ( bAllTabs || !pMarkData || pMarkData->GetTableSelect( nTab ) )
//STRIP001      {
//STRIP001          long nNext = nTabStart + aPageArr[nTab];
//STRIP001          BOOL bSelected = FALSE;
//STRIP001          for (long nP=nTabStart+1; nP<=nNext; nP++)  // 1-basiert
//STRIP001              if (aPageRanges.IsSelected( nP ))       // eine Seite von dieser Tabelle selektiert?
//STRIP001                  bSelected = TRUE;
//STRIP001
//STRIP001          if (bSelected)
//STRIP001          {
//STRIP001              ScPrintFunc aPrintFunc( this, pPrinter, nTab );
//STRIP001
//STRIP001              aPrintFunc.ApplyPrintSettings();        // dann Settings fuer diese Tabelle
//STRIP001              bFound = TRUE;
//STRIP001          }
//STRIP001          nTabStart = nNext;
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL lcl_HasTransparent( ScDocument* pDoc, USHORT nTab, const ScRange* pRange )
//STRIP001 {
//STRIP001  BOOL bFound = FALSE;
//STRIP001  ScDrawLayer* pDrawLayer = pDoc->GetDrawLayer();
//STRIP001  if (pDrawLayer)
//STRIP001  {
//STRIP001      SdrPage* pPage = pDrawLayer->GetPage(nTab);
//STRIP001      DBG_ASSERT(pPage,"Page ?");
//STRIP001      if (pPage)
//STRIP001      {
//STRIP001          Rectangle aMMRect;
//STRIP001          if ( pRange )
//STRIP001              aMMRect = pDoc->GetMMRect( pRange->aStart.Col(), pRange->aStart.Row(),
//STRIP001                                           pRange->aEnd.Col(), pRange->aEnd.Row(), nTab );
//STRIP001
//STRIP001          SdrObjListIter aIter( *pPage, IM_DEEPNOGROUPS );
//STRIP001          SdrObject* pObject = aIter.Next();
//STRIP001          while (pObject && !bFound)
//STRIP001          {
//STRIP001              if (pObject->IsTransparent())
//STRIP001              {
//STRIP001                  if ( pRange )
//STRIP001                  {
//STRIP001                      Rectangle aObjRect = pObject->GetLogicRect();
//STRIP001                      if ( aObjRect.IsOver( aMMRect ) )
//STRIP001                          bFound = TRUE;
//STRIP001                  }
//STRIP001                  else
//STRIP001                      bFound = TRUE;
//STRIP001              }
//STRIP001
//STRIP001              pObject = aIter.Next();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return bFound;
//STRIP001 }

//STRIP001 void ScDocShell::Print( SfxProgress& rProgress, PrintDialog* pPrintDialog,
//STRIP001                      ScMarkData* pMarkData, Window* pDialogParent, BOOL bForceSelected )
//STRIP001 {
//STRIP001  SfxPrinter* pPrinter = GetPrinter();
//STRIP001  if ( !pPrinter ) return;
//STRIP001
//STRIP001  PrintDialogRange eDlgOption = PRINTDIALOG_ALL;
//STRIP001  if ( bForceSelected )
//STRIP001      eDlgOption = PRINTDIALOG_SELECTION;
//STRIP001
//STRIP001  ScRange* pMarkedRange = NULL;
//STRIP001
//STRIP001  //  get settings from print options sub-dialog
//STRIP001  ScPrintOptions aOptions;
//STRIP001     const SfxItemSet& rOptionSet = pPrinter->GetOptions();
//STRIP001  const SfxPoolItem* pItem;
//STRIP001  BOOL bHasOptions = ( rOptionSet.GetItemState(SID_SCPRINTOPTIONS, FALSE, &pItem) == SFX_ITEM_SET );
//STRIP001  if (bHasOptions)
//STRIP001      aOptions = ((const ScTpPrintItem*)pItem)->GetPrintOptions();
//STRIP001  else
//STRIP001      aOptions = SC_MOD()->GetPrintOptions();     // use configuration
//STRIP001
//STRIP001  BOOL bAllTabs = TRUE;
//STRIP001  USHORT nTabCount = aDocument.GetTableCount();
//STRIP001  USHORT nTab;
//STRIP001  long nTotalPages = 0;                       // alle Seiten
//STRIP001  long aPageArr[MAXTAB+1];                    // Seiten pro Tabelle
//STRIP001  for ( nTab=0; nTab<nTabCount; nTab++ )      // nPages und nTotalPages ermitteln
//STRIP001  {
//STRIP001      ScPrintFunc aPrintFunc( this, pPrinter, nTab, 0,0,NULL, &aOptions );
//STRIP001      long nThisTab = aPrintFunc.GetTotalPages();
//STRIP001      aPageArr[nTab] = nThisTab;
//STRIP001      nTotalPages += nThisTab;
//STRIP001  }
//STRIP001
//STRIP001  MultiSelection aPageRanges;         // zu druckende Seiten
//STRIP001  aPageRanges.SetTotalRange( Range( 0, RANGE_MAX ) );
//STRIP001  aPageRanges.Select( Range(1,nTotalPages) );
//STRIP001  if ( pPrintDialog )
//STRIP001      eDlgOption = pPrintDialog->GetCheckedRange();
//STRIP001  switch ( eDlgOption )
//STRIP001  {
//STRIP001      case PRINTDIALOG_RANGE:
//STRIP001          aPageRanges = MultiSelection( pPrintDialog->GetRangeText() );
//STRIP001          break;
//STRIP001
//STRIP001      case PRINTDIALOG_SELECTION:
//STRIP001          if ( pMarkData && ( pMarkData->IsMarked() || pMarkData->IsMultiMarked() ) )
//STRIP001          {
//STRIP001              pMarkData->MarkToMulti();
//STRIP001              pMarkedRange = new ScRange;
//STRIP001              pMarkData->GetMultiMarkArea( *pMarkedRange );
//STRIP001              pMarkData->MarkToSimple();
//STRIP001          }
//STRIP001          bAllTabs = FALSE;
//STRIP001          break;
//STRIP001
//STRIP001      //case PRINTDIALOG_ALL:
//STRIP001      //default:
//STRIP001  }
//STRIP001
//STRIP001  if ( !aOptions.GetAllSheets() )      // option "only selected sheets" - also for ALL and RANGE
//STRIP001      bAllTabs = FALSE;
//STRIP001
//STRIP001  if (!bAllTabs)          // Gesamt-Seitenzahl bei Selektion
//STRIP001  {
//STRIP001      nTotalPages = 0;
//STRIP001      for (nTab=0; nTab<nTabCount; nTab++)
//STRIP001          if ( !pMarkData || pMarkData->GetTableSelect(nTab) )
//STRIP001              nTotalPages += aPageArr[nTab];
//STRIP001      if ( eDlgOption != PRINTDIALOG_RANGE )
//STRIP001          aPageRanges.Select( Range(1,nTotalPages) );
//STRIP001  }
//STRIP001
//STRIP001  USHORT nCollateCopies = 1;
//STRIP001  if ( pPrintDialog && pPrintDialog->IsCollateEnabled() && pPrintDialog->IsCollateChecked() )
//STRIP001      nCollateCopies = pPrintDialog->GetCopyCount();
//STRIP001
//STRIP001  //  test if printed range contains transparent objects
//STRIP001
//STRIP001  BOOL bHasTransp = FALSE;
//STRIP001  BOOL bAnyPrintRanges = aDocument.HasPrintRange();
//STRIP001  ScStyleSheetPool* pStylePool = aDocument.GetStyleSheetPool();
//STRIP001  for ( nTab=0; nTab<nTabCount && !bHasTransp; nTab++ )
//STRIP001  {
//STRIP001      if ( bAllTabs || !pMarkData || pMarkData->GetTableSelect( nTab ) )
//STRIP001      {
//STRIP001          SfxStyleSheetBase* pStyleSheet = pStylePool->Find(
//STRIP001                          aDocument.GetPageStyle( nTab ), SFX_STYLE_FAMILY_PAGE );
//STRIP001          if ( pStyleSheet )
//STRIP001          {
//STRIP001              const SfxItemSet& rSet = pStyleSheet->GetItemSet();
//STRIP001              if ( ((const ScViewObjectModeItem&)rSet.Get(ATTR_PAGE_CHARTS)).GetValue() == VOBJ_MODE_SHOW ||
//STRIP001                   ((const ScViewObjectModeItem&)rSet.Get(ATTR_PAGE_OBJECTS)).GetValue() == VOBJ_MODE_SHOW ||
//STRIP001                   ((const ScViewObjectModeItem&)rSet.Get(ATTR_PAGE_DRAWINGS)).GetValue() == VOBJ_MODE_SHOW )
//STRIP001              {
//STRIP001                  if ( pMarkedRange )
//STRIP001                      bHasTransp = bHasTransp || lcl_HasTransparent( &aDocument, nTab, pMarkedRange );
//STRIP001                  else if ( aDocument.GetPrintRangeCount(nTab) )
//STRIP001                  {
//STRIP001                      USHORT nRangeCount = aDocument.GetPrintRangeCount(nTab);
//STRIP001                      for (USHORT i=0; i<nRangeCount; i++)
//STRIP001                          bHasTransp = bHasTransp ||
//STRIP001                              lcl_HasTransparent( &aDocument, nTab, aDocument.GetPrintRange( nTab, i ) );
//STRIP001                  }
//STRIP001                  else if (!bAnyPrintRanges)
//STRIP001                      bHasTransp = bHasTransp || lcl_HasTransparent( &aDocument, nTab, NULL );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  BOOL bContinue = pPrinter->InitJob( pDialogParent, bHasTransp );
//STRIP001
//STRIP001  if ( bContinue )
//STRIP001  {
//STRIP001      for ( USHORT n=0; n<nCollateCopies; n++ )
//STRIP001      {
//STRIP001          long nTabStart = 0;
//STRIP001          long nDisplayStart = 0;
//STRIP001          long nAttrPage = 1;
//STRIP001
//STRIP001          for ( nTab=0; nTab<nTabCount; nTab++ )
//STRIP001          {
//STRIP001              if ( bAllTabs || !pMarkData || pMarkData->GetTableSelect( nTab ) )
//STRIP001              {
//STRIP001                  FmFormView* pDrawView = NULL;
//STRIP001                  Rectangle aFull( 0, 0, LONG_MAX, LONG_MAX );
//STRIP001                  if ( aDocument.HasControl( nTab, aFull ) )
//STRIP001                  {
//STRIP001                      ScDrawLayer* pModel = aDocument.GetDrawLayer();     // ist nicht NULL
//STRIP001                      pDrawView = new FmFormView( pModel, pPrinter );
//STRIP001                      pDrawView->ShowPagePgNum( nTab, Point() );
//STRIP001                      pDrawView->SetPrintPreview( TRUE );
//STRIP001                  }
//STRIP001
//STRIP001                  ScPrintFunc aPrintFunc( this, pPrinter, nTab, nAttrPage, nTotalPages, pMarkedRange, &aOptions );
//STRIP001                  aPrintFunc.SetDrawView( pDrawView );
//STRIP001                  aPrintFunc.DoPrint( aPageRanges, nTabStart, nDisplayStart, TRUE, &rProgress, NULL );
//STRIP001
//STRIP001                  nTabStart += aPageArr[nTab];
//STRIP001                  if ( aDocument.NeedPageResetAfterTab(nTab) )
//STRIP001                      nDisplayStart = 0;
//STRIP001                  else
//STRIP001                      nDisplayStart += aPageArr[nTab];
//STRIP001                  nAttrPage = aPrintFunc.GetFirstPageNo();    // behalten oder aus Vorlage
//STRIP001
//STRIP001                  delete pDrawView;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  delete pMarkedRange;
//STRIP001
//STRIP001  if (pOldJobSetup)
//STRIP001  {
//STRIP001      pPrinter->SetOrientation( pOldJobSetup->eOrientation );
//STRIP001      pPrinter->SetPaperBin   ( pOldJobSetup->nPaperBin );
//STRIP001      pPrinter->SetPaper      ( pOldJobSetup->ePaper );
//STRIP001
//STRIP001      if ( PAPER_USER == pOldJobSetup->ePaper )
//STRIP001      {
//STRIP001          pPrinter->SetMapMode( pOldJobSetup->aUserMapMode );
//STRIP001          pPrinter->SetPaperSizeUser( pOldJobSetup->aUserSize );
//STRIP001      }
//STRIP001
//STRIP001      delete pOldJobSetup;
//STRIP001      pOldJobSetup = NULL;
//STRIP001  }
//STRIP001
//STRIP001  if ( bHasOptions )
//STRIP001  {
//STRIP001      //  remove PrintOptions from printer ItemSet,
//STRIP001      //  so next time the options from the configuration are used
//STRIP001
//STRIP001      SfxItemSet aSet( pPrinter->GetOptions() );
//STRIP001      aSet.ClearItem( SID_SCPRINTOPTIONS );
//STRIP001      pPrinter->SetOptions( aSet );
//STRIP001  }
//STRIP001
//STRIP001  PostPaintGridAll();                 //! nur wenn geaendert
//STRIP001 }

//STRIP001 void ScDocShell::GetState( SfxItemSet &rSet )
//STRIP001 {
//STRIP001  SfxWhichIter aIter(rSet);
//STRIP001  USHORT nWhich = aIter.FirstWhich();
//STRIP001  while ( nWhich )
//STRIP001  {
//STRIP001      switch (nWhich)
//STRIP001      {
//STRIP001          case FID_AUTO_CALC:
//STRIP001              if ( (BOOL) aDocument.GetHardRecalcState() )
//STRIP001                  rSet.DisableItem( nWhich );
//STRIP001              else
//STRIP001                  rSet.Put( SfxBoolItem( nWhich, aDocument.GetAutoCalc() ) );
//STRIP001              break;
//STRIP001
//STRIP001          case FID_CHG_RECORD:
//STRIP001                     rSet.Put( SfxBoolItem( nWhich,
//STRIP001                         aDocument.GetChangeTrack() != NULL ) );
//STRIP001              break;
//STRIP001
//STRIP001             case SID_CHG_PROTECT:
//STRIP001              {
//STRIP001                     ScChangeTrack* pChangeTrack = aDocument.GetChangeTrack();
//STRIP001                     if ( pChangeTrack )
//STRIP001                         rSet.Put( SfxBoolItem( nWhich,
//STRIP001                             pChangeTrack->IsProtected() ) );
//STRIP001                     else
//STRIP001                         rSet.DisableItem( nWhich );
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001          //  Wenn eine Formel editiert wird, muss FID_RECALC auf jeden Fall enabled sein.
//STRIP001          //  Recalc fuer das Doc war mal wegen #29898# disabled, wenn AutoCalc an war,
//STRIP001          //  ist jetzt wegen #41540# aber auch immer enabled.
//STRIP001 //           case FID_RECALC:
//STRIP001 //               if ( aDocument.GetAutoCalc() )
//STRIP001 //                   rSet.DisableItem( nWhich );
//STRIP001 //               break;
//STRIP001
//STRIP001          case SID_TABLES_COUNT:
//STRIP001              rSet.Put( SfxUInt16Item( nWhich, aDocument.GetTableCount() ) );
//STRIP001              break;
//STRIP001
//STRIP001          case SID_ATTR_YEAR2000 :
//STRIP001              rSet.Put( SfxUInt16Item( nWhich,
//STRIP001                  aDocument.GetDocOptions().GetYear2000() ) );
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      nWhich = aIter.NextWhich();
//STRIP001  }
//STRIP001 }

//STRIP001 void ScDocShell::GetSbxState( SfxItemSet &rSet )
//STRIP001 {
//STRIP001  //  SID_SC_SELECTION (Selection),
//STRIP001  //  SID_SC_ACTIVECELL (ActiveCell),
//STRIP001  //  SID_SC_ACTIVETAB (ActiveTable),
//STRIP001  //  SID_TABLES_GET (Tables),
//STRIP001  //  SID_PIVOT_GET (DataPilotTables) - removed (old Basic)
//STRIP001
//STRIP001      //
//STRIP001      //  Wenn hier Slots von der View-Shell executed werden, muss auch der
//STRIP001      //  GetState weitergeleitet werden!
//STRIP001      //
//STRIP001
//STRIP001  ScTabViewShell* pVisibleSh = GetBestViewShell();        // sichtbare View
//STRIP001  if ( pVisibleSh )
//STRIP001      pVisibleSh->GetState( rSet );
//STRIP001 }

//STRIP001 void __EXPORT ScDocShell::Draw( OutputDevice* pDev, const JobSetup & rSetup, USHORT nAspect )
//STRIP001 {
//STRIP001 //   bIsOle = TRUE;      // jetzt ueber den CreateMode
//STRIP001
//STRIP001  USHORT nVisTab = aDocument.GetVisibleTab();
//STRIP001  if (!aDocument.HasTable(nVisTab))
//STRIP001      return;
//STRIP001
//STRIP001  if ( nAspect == ASPECT_THUMBNAIL )
//STRIP001  {
//STRIP001      Rectangle aBoundRect = GetVisArea( ASPECT_THUMBNAIL );
//STRIP001      ScViewData aTmpData( this, NULL );
//STRIP001      aTmpData.SetTabNo(nVisTab);
//STRIP001      aDocument.SnapVisArea( aBoundRect );
//STRIP001      aTmpData.SetScreen( aBoundRect );
//STRIP001      ScPrintFunc::DrawToDev( &aDocument, pDev, 1.0, aBoundRect, &aTmpData, TRUE );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      Rectangle aBoundRect = SfxInPlaceObject::GetVisArea();
//STRIP001      ScViewData aTmpData( this, NULL );
//STRIP001      aTmpData.SetTabNo(nVisTab);
//STRIP001      aDocument.SnapVisArea( aBoundRect );
//STRIP001      aTmpData.SetScreen( aBoundRect );
//STRIP001      ScPrintFunc::DrawToDev( &aDocument, pDev, 1.0, aBoundRect, &aTmpData, TRUE );
//STRIP001  }
//STRIP001 }

/*N*/ Rectangle __EXPORT ScDocShell::GetVisArea( USHORT nAspect ) const
/*N*/ {
/*N*/   SfxObjectCreateMode eShellMode = GetCreateMode();
/*N*/   if ( eShellMode == SFX_CREATE_MODE_ORGANIZER )
/*N*/   {
/*?*/       //  ohne Inhalte wissen wir auch nicht, wie gross die Inhalte sind
/*?*/       //  leeres Rechteck zurueckgeben, das wird dann nach dem Laden berechnet
/*?*/       return Rectangle();
/*N*/   }
/*N*/
/*N*/   if( nAspect == ASPECT_THUMBNAIL )
/*N*/   {
/*?*/ //        Rectangle aArea( 0,0, 3175,3175 );                          //  120x120 Pixel in 1:1
/*?*/       Rectangle aArea( 0,0, SC_PREVIEW_SIZE_X,SC_PREVIEW_SIZE_Y );
/*?*/       aDocument.SnapVisArea( aArea );
/*?*/       return aArea;
/*N*/   }
/*N*/   else if( nAspect == ASPECT_CONTENT && eShellMode != SFX_CREATE_MODE_EMBEDDED )
/*N*/   {
/*N*/       //  Visarea holen wie nach Load
/*N*/
/*N*/       USHORT nVisTab = aDocument.GetVisibleTab();
/*N*/       if (!aDocument.HasTable(nVisTab))
/*N*/       {
/*?*/           nVisTab = 0;
/*?*/           ((ScDocShell*)this)->aDocument.SetVisibleTab(nVisTab);
/*N*/       }
/*N*/       USHORT nStartCol,nStartRow;
/*N*/       aDocument.GetDataStart( nVisTab, nStartCol, nStartRow );
/*N*/       USHORT nEndCol,nEndRow;
/*N*/       aDocument.GetPrintArea( nVisTab, nEndCol, nEndRow );
/*N*/       if (nStartCol>nEndCol)
/*?*/           nStartCol = nEndCol;
/*N*/       if (nStartRow>nEndRow)
/*?*/           nStartRow = nEndRow;
/*N*/       Rectangle aNewArea = ((ScDocument&)aDocument)
/*N*/                               .GetMMRect( nStartCol,nStartRow, nEndCol,nEndRow, nVisTab );
/*N*/       ((ScDocShell*)this)->SvEmbeddedObject::SetVisArea( aNewArea );
/*N*/       return aNewArea;
/*N*/   }
/*N*/   else
/*N*/       return SfxInPlaceObject::GetVisArea( nAspect );
/*N*/ }

//STRIP001 void ScDocShell::GetPageOnFromPageStyleSet( const SfxItemSet* pStyleSet,
//STRIP001                                          USHORT            nCurTab,
//STRIP001                                          BOOL&             rbHeader,
//STRIP001                                          BOOL&             rbFooter )
//STRIP001 {
//STRIP001  if ( !pStyleSet )
//STRIP001  {
//STRIP001      ScStyleSheetPool*  pStylePool  = aDocument.GetStyleSheetPool();
//STRIP001      SfxStyleSheetBase* pStyleSheet = pStylePool->
//STRIP001                                          Find( aDocument.GetPageStyle( nCurTab ),
//STRIP001                                                SFX_STYLE_FAMILY_PAGE );
//STRIP001
//STRIP001      DBG_ASSERT( pStyleSheet, "PageStyle not found! :-/" );
//STRIP001
//STRIP001      if ( pStyleSheet )
//STRIP001          pStyleSet = &pStyleSheet->GetItemSet();
//STRIP001      else
//STRIP001          rbHeader = rbFooter = FALSE;
//STRIP001  }
//STRIP001
//STRIP001  DBG_ASSERT( pStyleSet, "PageStyle-Set not found! :-(" );
//STRIP001
//STRIP001  //--------------------------------------------------------------------
//STRIP001
//STRIP001  const SvxSetItem*   pSetItem = NULL;
//STRIP001  const SfxItemSet*   pSet     = NULL;
//STRIP001
//STRIP001  pSetItem = (const SvxSetItem*) &pStyleSet->Get( ATTR_PAGE_HEADERSET );
//STRIP001  pSet     = &pSetItem->GetItemSet();
//STRIP001  rbHeader = ((const SfxBoolItem&)pSet->Get(ATTR_PAGE_ON)).GetValue();
//STRIP001
//STRIP001  pSetItem = (const SvxSetItem*) &pStyleSet->Get( ATTR_PAGE_FOOTERSET );
//STRIP001  pSet     = &pSetItem->GetItemSet();
//STRIP001  rbFooter = ((const SfxBoolItem&)pSet->Get(ATTR_PAGE_ON)).GetValue();
//STRIP001 }

//STRIP001 long __EXPORT ScDocShell::DdeGetData( const String& rItem,
//STRIP001                                    const String& rMimeType,
//STRIP001                                    ::com::sun::star::uno::Any & rValue )
//STRIP001 {
//STRIP001  if( FORMAT_STRING == SotExchange::GetFormatIdFromMimeType( rMimeType ) )
//STRIP001  {
//STRIP001      if( rItem.EqualsIgnoreCaseAscii( "Format" ) )
//STRIP001      {
//STRIP001          ByteString aFmtByte( aDdeTextFmt, gsl_getSystemTextEncoding() );
//STRIP001          rValue <<= ::com::sun::star::uno::Sequence< sal_Int8 >(
//STRIP001                                      (sal_Int8*)aFmtByte.GetBuffer(),
//STRIP001                                      aFmtByte.Len() + 1 );
//STRIP001          return 1;
//STRIP001      }
//STRIP001      ScImportExport aObj( &aDocument, rItem );
//STRIP001      if ( !aObj.IsRef() )
//STRIP001          return 0;                           // ungueltiger Bereich
//STRIP001
//STRIP001      if( aDdeTextFmt.GetChar(0) == 'F' )
//STRIP001          aObj.SetFormulas( TRUE );
//STRIP001      if( aDdeTextFmt.EqualsAscii( "SYLK" ) ||
//STRIP001          aDdeTextFmt.EqualsAscii( "FSYLK" ) )
//STRIP001      {
//STRIP001          ByteString aData;
//STRIP001          if( aObj.ExportByteString( aData, gsl_getSystemTextEncoding(),
//STRIP001                                      SOT_FORMATSTR_ID_SYLK ) )
//STRIP001          {
//STRIP001              rValue <<= ::com::sun::star::uno::Sequence< sal_Int8 >(
//STRIP001                                          (sal_Int8*)aData.GetBuffer(),
//STRIP001                                          aData.Len() + 1 );
//STRIP001              return 1;
//STRIP001          }
//STRIP001          else
//STRIP001              return 0;
//STRIP001      }
//STRIP001      if( aDdeTextFmt.EqualsAscii( "CSV" ) ||
//STRIP001          aDdeTextFmt.EqualsAscii( "FCSV" ) )
//STRIP001          aObj.SetSeparator( ',' );
//STRIP001      return aObj.ExportData( rMimeType, rValue ) ? 1 : 0;
//STRIP001  }
//STRIP001
//STRIP001  ScImportExport aObj( &aDocument, rItem );
//STRIP001  if( aObj.IsRef() )
//STRIP001      return aObj.ExportData( rMimeType, rValue ) ? 1 : 0;
//STRIP001  return 0;
//STRIP001 }

//STRIP001 long __EXPORT ScDocShell::DdeSetData( const String& rItem,
//STRIP001                                      const String& rMimeType,
//STRIP001                              const ::com::sun::star::uno::Any & rValue )
//STRIP001 {
//STRIP001  if( FORMAT_STRING == SotExchange::GetFormatIdFromMimeType( rMimeType ))
//STRIP001  {
//STRIP001      if( rItem.EqualsIgnoreCaseAscii( "Format" ) )
//STRIP001      {
//STRIP001          if ( ScByteSequenceToString::GetString( aDdeTextFmt, rValue, gsl_getSystemTextEncoding() ) )
//STRIP001          {
//STRIP001              aDdeTextFmt.ToUpperAscii();
//STRIP001              return 1;
//STRIP001          }
//STRIP001          return 0;
//STRIP001      }
//STRIP001      ScImportExport aObj( &aDocument, rItem );
//STRIP001      if( aDdeTextFmt.GetChar(0) == 'F' )
//STRIP001          aObj.SetFormulas( TRUE );
//STRIP001      if( aDdeTextFmt.EqualsAscii( "SYLK" ) ||
//STRIP001          aDdeTextFmt.EqualsAscii( "FSYLK" ) )
//STRIP001      {
//STRIP001          String aData;
//STRIP001          if ( ScByteSequenceToString::GetString( aData, rValue, gsl_getSystemTextEncoding() ) )
//STRIP001          {
//STRIP001              return aObj.ImportString( aData, SOT_FORMATSTR_ID_SYLK ) ? 1 : 0;
//STRIP001          }
//STRIP001          return 0;
//STRIP001      }
//STRIP001      if( aDdeTextFmt.EqualsAscii( "CSV" ) ||
//STRIP001          aDdeTextFmt.EqualsAscii( "FCSV" ) )
//STRIP001          aObj.SetSeparator( ',' );
//STRIP001      return aObj.ImportData( rMimeType, rValue ) ? 1 : 0;
//STRIP001  }
//STRIP001  ScImportExport aObj( &aDocument, rItem );
//STRIP001  if( aObj.IsRef() )
//STRIP001      return aObj.ImportData( rMimeType, rValue ) ? 1 : 0;
//STRIP001  return 0;
//STRIP001 }

//STRIP001 ::so3::SvLinkSource* __EXPORT ScDocShell::DdeCreateLinkSource( const String& rItem )
//STRIP001 {
//STRIP001  //  only check for valid item string - range is parsed again in ScServerObject ctor
//STRIP001
//STRIP001  //  named range?
//STRIP001  String aPos = rItem;
//STRIP001  ScRangeName* pRange = aDocument.GetRangeName();
//STRIP001  if( pRange )
//STRIP001  {
//STRIP001      USHORT nPos;
//STRIP001      if( pRange->SearchName( aPos, nPos ) )
//STRIP001      {
//STRIP001          ScRangeData* pData = (*pRange)[ nPos ];
//STRIP001          if( pData->HasType( RT_REFAREA )
//STRIP001              || pData->HasType( RT_ABSAREA )
//STRIP001              || pData->HasType( RT_ABSPOS ) )
//STRIP001              pData->GetSymbol( aPos );           // continue with the name's contents
//STRIP001      }
//STRIP001  }
//STRIP001  ScRange aRange;
//STRIP001  BOOL bValid = ( ( aRange.Parse( aPos, &aDocument ) & SCA_VALID ) ||
//STRIP001                  ( aRange.aStart.Parse( aPos, &aDocument ) & SCA_VALID ) );
//STRIP001
//STRIP001  ScServerObject* pObj = NULL;            // NULL = error
//STRIP001  if ( bValid )
//STRIP001      pObj = new ScServerObject( this, rItem );
//STRIP001
//STRIP001  //  GetLinkManager()->InsertServer() is in the ScServerObject ctor
//STRIP001
//STRIP001  return pObj;
//STRIP001 }

//------------------------------------------------------------------

/*N*/ ScViewData* ScDocShell::GetViewData()
/*N*/ {
/*N*/   SfxViewShell* pCur = SfxViewShell::Current();
/*N*/   ScTabViewShell* pViewSh = PTR_CAST(ScTabViewShell,pCur);
/*N*/   return pViewSh ? pViewSh->GetViewData() : NULL;
/*N*/ }

//------------------------------------------------------------------

/*N*/ USHORT ScDocShell::GetCurTab()
/*N*/ {
/*N*/   //! this must be made non-static and use a ViewShell from this document!
/*N*/
/*N*/   ScViewData* pViewData = GetViewData();
/*N*/
/*N*/   return pViewData ? pViewData->GetTabNo() : 0;
/*N*/ }

/*N*/ ScTabViewShell* ScDocShell::GetBestViewShell()
/*N*/ {
/*N*/   ScTabViewShell* pViewSh = ScTabViewShell::GetActiveViewShell();
/*N*/   // falsches Doc?
/*N*/   if( pViewSh && pViewSh->GetViewData()->GetDocShell() != this )
/*N*/       pViewSh = NULL;
/*N*/   if( !pViewSh )
/*N*/   {
/*N*/       // 1. ViewShell suchen
/*N*/       SfxViewFrame* pFrame = SfxViewFrame::GetFirst( this, TYPE(SfxTopViewFrame) );
/*N*/       if( pFrame )
/*N*/       {
/*N*/           SfxViewShell* p = pFrame->GetViewShell();
/*N*/           pViewSh = PTR_CAST(ScTabViewShell,p);
/*N*/       }
/*N*/   }
/*N*/   return pViewSh;
/*N*/ }

/*N*/ SfxBindings* ScDocShell::GetViewBindings()
/*N*/ {
/*N*/   //  used to invalidate slots after changes to this document
/*N*/
/*N*/   SfxViewShell* pViewSh = GetBestViewShell();
/*N*/   if (pViewSh)
/*N*/       return &pViewSh->GetViewFrame()->GetBindings();
/*N*/   else
/*N*/       return NULL;
/*N*/ }

//------------------------------------------------------------------

//STRIP001 ScDocShell* ScDocShell::GetShellByNum( USHORT nDocNo )       // static
//STRIP001 {
//STRIP001  ScDocShell* pFound = NULL;
//STRIP001  SfxObjectShell* pShell = SfxObjectShell::GetFirst();
//STRIP001  USHORT nShellCnt = 0;
//STRIP001
//STRIP001  while ( pShell && !pFound )
//STRIP001  {
//STRIP001      if ( pShell->Type() == TYPE(ScDocShell) )
//STRIP001      {
//STRIP001          if ( nShellCnt == nDocNo )
//STRIP001              pFound = (ScDocShell*) pShell;
//STRIP001          else
//STRIP001              ++nShellCnt;
//STRIP001      }
//STRIP001      pShell = SfxObjectShell::GetNext( *pShell );
//STRIP001  }
//STRIP001
//STRIP001  return pFound;
//STRIP001 }

//------------------------------------------------------------------

//STRIP001 IMPL_LINK( ScDocShell, ChartSelectionHdl, ChartSelectionInfo*, pInfo )
//STRIP001 {
//STRIP001  if (!pInfo)
//STRIP001      return 0;
//STRIP001
//STRIP001  //  die View suchen, auf der das Objekt aktiv ist
//STRIP001
//STRIP001  SfxViewFrame *pFrame = SfxViewFrame::GetFirst( this );
//STRIP001  while (pFrame)
//STRIP001  {
//STRIP001      SfxViewShell* pSh = pFrame->GetViewShell();
//STRIP001      if (pSh && pSh->ISA(ScTabViewShell))
//STRIP001      {
//STRIP001          ScTabViewShell* pViewSh = (ScTabViewShell*)pSh;
//STRIP001          SfxInPlaceClient* pClient = pViewSh->GetIPClient();
//STRIP001          if ( pClient && pClient->IsInPlaceActive() )
//STRIP001          {
//STRIP001              SvInPlaceObjectRef xIPObj = pClient->GetIPObj();
//STRIP001              if (xIPObj.Is())
//STRIP001              {
//STRIP001                  SchMemChart* pMemChart = SchDLL::GetChartData(xIPObj);
//STRIP001                  if (pMemChart)
//STRIP001                      return pViewSh->DoChartSelection( *pInfo, *pMemChart );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      pFrame = SfxViewFrame::GetNext( *pFrame, this );
//STRIP001  }
//STRIP001
//STRIP001  return 0;
//STRIP001 }



}
