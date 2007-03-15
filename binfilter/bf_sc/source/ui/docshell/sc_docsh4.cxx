/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_docsh4.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: obo $ $Date: 2007-03-15 15:19:15 $
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
#endif

#pragma hdrstop


// INCLUDE ---------------------------------------------------------------
#if STLPORT_VERSION>=321
#include <math.h>       // prevent conflict between exception and std::exception
#endif

#define ITEMID_FIELD EE_FEATURE_FIELD

#include <bf_sfx2/bindings.hxx>
#include <bf_sfx2/docfile.hxx>
#include <svtools/ehdl.hxx>
#include "bf_basic/sbxcore.hxx"
#include <bf_sfx2/request.hxx>
#include <svtools/sfxecode.hxx>
#include <bf_sfx2/topfrm.hxx>
#include <bf_offmgr/sbaitems.hxx>
#include <svtools/whiter.hxx>
#include <vcl/msgbox.hxx>
#include <vcl/waitobj.hxx>

#include "docsh.hxx"
#include "docfunc.hxx"
#include "bf_sc.hrc"
#include "stlpool.hxx"
#include "appoptio.hxx"
#include "globstr.hrc"
#include "dbdocfun.hxx"
#include "printfun.hxx"              // DrawToDev
#include "tabvwsh.hxx"
#include "dbcolect.hxx"
#include "scmod.hxx"
#include "tablink.hxx"      // ScDocumentLoader statics
#include "docoptio.hxx"

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
/*?*/                         }
/*?*/                   }
/*?*/                   else
/*?*/                   {
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



//------------------------------------------------------------------

/*N*/ void ScDocShell::DoRecalc( BOOL bApi )
/*N*/ {
/*N*/   BOOL bDone = FALSE;
/*N*/   ScTabViewShell* pSh = GetBestViewShell();
/*N*/   if ( pSh )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ScInputHandler* pHdl = SC_MOD()->GetInputHdl(pSh);
/*N*/   }
/*N*/   if (!bDone)                         // sonst Dokument neu berechnen
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 WaitObject aWaitObj( GetDialogParent() );
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
/*N*/       }
/*N*/   }
/*N*/
/*N*/   //  alles andere geht ueber Slots...
/*N*/ }

//  wie in printfun.cxx
#define ZOOM_MIN    10



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
/*?*/                   }
/*?*/               }
/*?*/               break;
/*N*/       }
/*N*/
/*N*/       nWhich = aIter.NextWhich();
/*N*/   }
/*N*/ }







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


//------------------------------------------------------------------




}
