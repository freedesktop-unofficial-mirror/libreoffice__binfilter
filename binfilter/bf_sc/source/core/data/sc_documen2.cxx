/*************************************************************************
 *
 *  $RCSfile: sc_documen2.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: vg $ $Date: 2005-03-08 15:34:51 $
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
// auto strip #include "core_pch.hxx"
#endif


#pragma hdrstop

#define _BIGINT_HXX
#define _SFXMULTISEL_HXX
//#define _STACK_HXX
//#define _QUEUE_HXX
#define _DYNARR_HXX
#define _TREELIST_HXX
#define _CACHESTR_HXX
#define _NEW_HXX
//#define _SHL_HXX ***
//#define _LINK_HXX ***
//#define _ERRCODE_HXX ***
//#define _GEN_HXX ***
//#define _FRACT_HXX ***
//#define _STRING_HXX ***
//#define _MTF_HXX ***
//#define _CONTNR_HXX ***
//#define _LIST_HXX ***
//#define _TABLE_HXX ***
#define _DYNARY_HXX
//#define _UNQIDX_HXX ***
//#define _SVMEMPOOL_HXX ***
//#define _UNQID_HXX ***
//#define _DEBUG_HXX ***
//#define _DATE_HXX ***
//#define _TIME_HXX ***
//#define _DATETIME_HXX ***
//#define _INTN_HXX ***
//#define _WLDCRD_HXX ***
//#define _FSYS_HXX ***
//#define _STREAM_HXX ***
#define _CACHESTR_HXX
#define _SV_MULTISEL_HXX



#define _SV_NOXSOUND

#define _BASDLG_HXX
#define _CACHESTR_HXX
#define _CTRLTOOL_HXX
#define _DLGCFG_HXX
#define _EXTATTR_HXX
#define _FILDLG_HXX
#define _FRM3D_HXX
#define _INTRO_HXX
#define _ISETBWR_HXX
#define _NO_SVRTF_PARSER_HXX
#define _MACRODLG_HXX
#define _MODALDLG_HXX
#define _MOREBUTTON_HXX
#define _OUTLINER_HXX
#define _PASSWD_HXX
//#define _QUEUE_HXX
#define _RULER_HXX
#define _SCRWIN_HXX
#define _SETBRW_HXX
#define _STATUS_HXX
#define _STDMENU_HXX
#define _TABBAR_HXX
#define _RULER_HXX
#define _SCRWIN_HXX
#define _SELENG_HXX
#define _SETBRW_HXX
#define _SOUND_HXX
#define _STATUS_HXX
#define _STDMENU_HXX


//#define _PRNDLG_HXX ***
//#define _POLY_HXX **
// TOOLS
#define _BIGINT_HXX
#define _SFXMULTISEL_HXX
//#define _STACK_HXX
//#define _QUEUE_HXX
#define _DYNARR_HXX
#define _TREELIST_HXX
#define _CACHESTR_HXX

//SV
//#define _CLIP_HXX
#define _CONFIG_HXX
#define _CURSOR_HXX
#define _FONTDLG_HXX
#define _PRVWIN_HXX

#ifndef OS2
#define _MENUBTN_HXX
#endif

//#define _SOBASE_HXX
//#define _SOSTOR_HXX
//#define _SOCORE_HXX
//#define _SOINPL_HXX

#define _SFX_DOCFILE_HXX
#define _SFX_DOCFILT_HXX
#define _SFX_DOCINF_HXX
#define _SFX_DOCSH_HXX
#define _SFX_INTERNO_HXX
#define _SFX_PRNMON_HXX
#define _SFX_RESMGR_HXX
#define _SFX_TEMPLDLG_HXX
#define _SFXAPPWIN_HXX
#define _SFXBASIC_HXX
#define _SFXCTRLITEM
#define _SFXDLGCFG_HXX
#define _SFXDISPATCH_HXX
#define _SFXDOCFILE_HXX
#define _SFXDOCMAN_HXX
#define _SFXDOCMGR_HXX
#define _SFXDOCTDLG_HXX
#define _SFXFILEDLG_HXX
#define _SFXIMGMGR_HXX
#define _SFXIPFRM_HXX
#define _SFX_MACRO_HXX
#define _SFXMNUITEM_HXX
#define _SFXMNUMGR_HXX
#define _SFXMULTISEL_HXX
//#define _SFXMSG_HXX
#define _SFXMSGDESCR_HXX
#define _SFXMSGPOOL_HXX
#define _SFX_MINFITEM_HXX
#define _SFXOBJFACE_HXX
#define _SFXOBJFAC_HXX
#define _SFX_SAVEOPT_HXX
#define _SFXSTBITEM_HXX
#define _SFXSTBMGR_HXX
#define _SFXTBXCTRL_HXX
#define _SFXTBXMGR_HXX

//#define _SI_HXX
//#define SI_NODRW
#define _SI_DLL_HXX
#define _SIDLL_HXX
#define _SI_NOITEMS
#define _SI_NOOTHERFORMS
#define _SI_NOSBXCONTROLS
#define _SINOSBXCONTROLS
#define _SI_NODRW         //
#define _SI_NOCONTROL
#define _VCBRW_HXX
#define _VCTRLS_HXX
//#define _VCSBX_HXX
#define _VCONT_HXX
#define _VDRWOBJ_HXX
#define _VCATTR_HXX


#define _SVBOXITM_HXX
#define _SVCONTNR_HXX
#define _SVDIALDLL_HXX
//#define _SVDATTR_HXX
#define _SVDRAG_HXX
#define _SVDXOUT_HXX
#define _SVDEC_HXX
#define _SVDIO_HXX
//#define _SVDLAYER_HXX
#define _SVINCVW_HXX
#define _SV_MULTISEL_HXX
#define _SVRTV_HXX
#define _SVTABBX_HXX
#define _SVTREEBOX_HXX
#define _SVTREELIST_HXX

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


// INCLUDE ---------------------------------------------------------------

#define _ZFORLIST_DECLARE_TABLE
#include "scitems.hxx"
// auto strip #include <bf_svx/eeitem.hxx>
#define ITEMID_FIELD EE_FEATURE_FIELD

// auto strip #include <bf_svx/editeng.hxx>
#include <bf_svx/forbiddencharacterstable.hxx>
#include <bf_svx/linkmgr.hxx>
// auto strip #include <bf_sfx2/bindings.hxx>
#include <bf_sfx2/objsh.hxx>
#include <bf_sfx2/printer.hxx>
// auto strip #include <svtools/zforlist.hxx>
#include <svtools/zformat.hxx>
// auto strip #include <comphelper/processfactory.hxx>
#ifndef _SVTOOLS_PASSWORDHELPER_HXX
#include <svtools/PasswordHelper.hxx>
#endif
#ifndef _TOOLS_TENCCVT_HXX
#include <tools/tenccvt.hxx>
#endif
// auto strip #ifndef _LIST_HXX
// auto strip #include <tools/list.hxx>
// auto strip #endif
#ifndef _RTL_CRC_H_
#include <rtl/crc.h>
#endif

// auto strip #include "document.hxx"
// auto strip #include "table.hxx"
#include "attrib.hxx"
#include "patattr.hxx"
#include "rangenam.hxx"
#include "dbcolect.hxx"
#include "pivot.hxx"
#include "docpool.hxx"
#include "stlpool.hxx"
#include "stlsheet.hxx"
#include "globstr.hrc"
#include "chartarr.hxx"
#include "rechead.hxx"
// auto strip #include "global.hxx"
// auto strip #include "brdcst.hxx"
#include "bcaslot.hxx"
// auto strip #include "adiasync.hxx"
#include "addinlis.hxx"
#include "chartlis.hxx"
// auto strip #include "markdata.hxx"
// auto strip #include "conditio.hxx"
#include "validat.hxx"
// auto strip #include "progress.hxx"
#include "detdata.hxx"
#include "bf_sc.hrc"                // FID_DATACHANGED
// auto strip #include "ddelink.hxx"
#include "chgtrack.hxx"
#include "chgviset.hxx"
#include "editutil.hxx"
// auto strip #include "hints.hxx"
#include "dpobject.hxx"
#include "indexmap.hxx"
#include "scrdata.hxx"
#include "poolhelp.hxx"
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {
// STATIC DATA -----------------------------------------------------------

/*N*/ ScDocument::ScDocument( ScDocumentMode    eMode,
/*N*/                       SfxObjectShell* pDocShell ) :
/*N*/       xServiceManager( ::legacy_binfilters::getLegacyProcessServiceFactory() ),
/*N*/       pDrawLayer( NULL ),
/*N*/       pColorTable( NULL ),
/*N*/       pShell( pDocShell ),
/*N*/       pPrinter( NULL ),
/*N*/       bAutoCalc( eMode == SCDOCMODE_DOCUMENT ),
/*N*/       bAutoCalcShellDisabled( FALSE ),
/*N*/       bForcedFormulaPending( FALSE ),
/*N*/       bCalculatingFormulaTree( FALSE ),
/*N*/       bIsUndo( eMode == SCDOCMODE_UNDO ),
/*N*/       bIsClip( eMode == SCDOCMODE_CLIP ),
/*N*/       bCutMode( FALSE ),
/*N*/       nMaxTableNumber( 0 ),
/*N*/       pCondFormList( NULL ),
/*N*/       pValidationList( NULL ),
/*N*/       pFormatExchangeList( NULL ),
/*N*/       bIsEmbedded( FALSE ),
/*N*/       bProtected( FALSE ),
/*N*/       pLinkManager( NULL ),
/*N*/       pDocOptions( NULL ),
/*N*/       pViewOptions( NULL ),
/*N*/       pExtDocOptions( NULL ),
/*N*/       pConsolidateDlgData( NULL ),
/*N*/       pFormulaTree( NULL ),
/*N*/       pEOFormulaTree( NULL ),
/*N*/       aCurTextWidthCalcPos(MAXCOL,0,0),
/*N*/ //        bNoSetDirty( TRUE ),
/*N*/       bNoSetDirty( FALSE ),
/*N*/       pFormulaTrack( NULL ),
/*N*/       pEOFormulaTrack( NULL ),
/*N*/       nFormulaTrackCount(0),
/*N*/       bInsertingFromOtherDoc( FALSE ),
            bImportingXML( FALSE ),             // #i41083# this has to be set in ScXMLImport::startDocument
/*N*/       nHardRecalcState(0),
/*N*/       bCalcingAfterLoad( FALSE ),
/*N*/       bNoListening( FALSE ),
/*N*/       bLoadingDone( TRUE ),
/*N*/       nVisibleTab( 0 ),
/*N*/       bIdleDisabled( FALSE ),
/*N*/       bInLinkUpdate( FALSE ),
/*N*/       bDetectiveDirty( FALSE ),
/*N*/       nMacroCallMode( SC_MACROCALL_ALLOWED ),
/*N*/       bHasMacroFunc( FALSE ),
/*N*/       bChartListenerCollectionNeedsUpdate( FALSE ),
/*N*/       bHasForcedFormulas( FALSE ),
/*N*/       nVisSpellState( 0 ),
/*N*/       pOtherObjects( NULL ),
/*N*/       pClipData( NULL ),
/*N*/       nFormulaCodeInTree(0),
/*N*/       nInterpretLevel(0),
/*N*/       nMacroInterpretLevel(0),
/*N*/       nInterpreterTableOpLevel(0),
/*N*/       bLostData(FALSE),
/*N*/       pDetOpList(NULL),
/*N*/       bInDtorClear( FALSE ),
/*N*/       bExpandRefs( FALSE ),
/*N*/       pUnoBroadcaster( NULL ),
/*N*/       pChangeTrack( NULL ),
/*N*/       pChangeViewSettings( NULL ),
/*N*/       pEditEngine( NULL ),
/*N*/       eLinkMode(LM_UNKNOWN),
/*N*/       pDPCollection( NULL ),
/*N*/       pScriptTypeData( NULL ),
/*N*/         nAsianCompression(SC_ASIANCOMPRESSION_INVALID),
/*N*/         nAsianKerning(SC_ASIANKERNING_INVALID),
/*N*/         pLoadedSymbolStringCellList( NULL ),
/*N*/         bPastingDrawFromOtherDoc( FALSE ),
/*N*/         pCacheFieldEditEngine( NULL ),
/*N*/         nInDdeLinkUpdate( 0 ),
/*N*/         nXMLImportedFormulaCount( 0 ),
/*N*/         bInUnoBroadcast( FALSE ),
/*N*/         bStyleSheetUsageInvalid( TRUE )
/*N*/ {
/*N*/   eSrcSet = gsl_getSystemTextEncoding();
/*N*/   nSrcVer = SC_CURRENT_VERSION;
/*N*/   nSrcMaxRow = MAXROW;
/*N*/
/*N*/   if ( eMode == SCDOCMODE_DOCUMENT )
/*N*/   {
/*N*/       if ( pDocShell )
/*N*/           pLinkManager = new SvxLinkManager( pDocShell );
/*N*/
/*N*/       xPoolHelper = new ScPoolHelper( this );
/*N*/
/*N*/       pTab[0]  = NULL;
/*N*/       pBASM = new ScBroadcastAreaSlotMachine( this );
/*N*/       pChartListenerCollection = new ScChartListenerCollection( this );
/*N*/       pRefreshTimerControl = new ScRefreshTimerControl;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       pTab[0]     = NULL;
/*N*/       pBASM       = NULL;
/*N*/       pChartListenerCollection = NULL;
/*N*/       pRefreshTimerControl = NULL;
/*N*/   }
/*N*/
/*N*/   for (USHORT i=1; i<=MAXTAB; i++)
/*N*/       pTab[i] = NULL;
/*N*/
/*N*/   pRangeName = new ScRangeName( 4, 4, FALSE, this );
/*N*/   pDBCollection = new ScDBCollection( 4, 4, FALSE, this );
/*N*/   pPivotCollection = new ScPivotCollection(4, 4, this );
/*N*/   pSelectionAttr = NULL;
/*N*/   pChartCollection = new ScChartCollection;
/*N*/   xColNameRanges = new ScRangePairList;
/*N*/   xRowNameRanges = new ScRangePairList;
/*N*/   ImplCreateOptions();
/*N*/   // languages for a visible document are set by docshell later (from options)
/*N*/   SetLanguage( ScGlobal::eLnge, ScGlobal::eLnge, ScGlobal::eLnge );
/*N*/
/*N*/   aTrackTimer.SetTimeoutHdl( LINK( this, ScDocument, TrackTimeHdl ) );
/*N*/   aTrackTimer.SetTimeout( 100 );
/*N*/ }


//STRIP001 sal_uInt32 ScDocument::GetDocumentID() const
//STRIP001 {
//STRIP001     const ScDocument* pThis = this;
//STRIP001     sal_uInt32 nCrc = rtl_crc32( 0, &pThis, sizeof(ScDocument*) );
//STRIP001     // the this pointer only might not be sufficient
//STRIP001     nCrc = rtl_crc32( nCrc, &pShell, sizeof(SfxObjectShell*) );
//STRIP001     return nCrc;
//STRIP001 }


/*N*/ void ScDocument::StartChangeTracking() // Changetracking.sdc
/*N*/ {
/*N*/   if (!pChangeTrack)
/*N*/       pChangeTrack = new ScChangeTrack( this );
/*N*/ }

/*N*/ void ScDocument::EndChangeTracking() // Changetracking.sdc
/*N*/ {
/*N*/   delete pChangeTrack;
/*N*/   pChangeTrack = NULL;
/*N*/ }

/*N*/ void ScDocument::SetChangeTrack( ScChangeTrack* pTrack )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001   DBG_ASSERT( pTrack->GetDocument() == this, "SetChangeTrack: different documents" );
//STRIP001  if ( !pTrack || pTrack == pChangeTrack || pTrack->GetDocument() != this )
//STRIP001      return ;
//STRIP001  EndChangeTracking();
//STRIP001  pChangeTrack = pTrack;
/*N*/ }


/*N*/  IMPL_LINK( ScDocument, TrackTimeHdl, Timer*, pTimer )
/*N*/  {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if ( ScDdeLink::IsInUpdate() )        // nicht verschachteln
//STRIP001  {
//STRIP001      aTrackTimer.Start();            // spaeter nochmal versuchen
//STRIP001  }
//STRIP001  else if (pShell)                    // ausfuehren
//STRIP001  {
//STRIP001      TrackFormulas();
//STRIP001      pShell->Broadcast( SfxSimpleHint( FID_DATACHANGED ) );
//STRIP001      ResetChanged( ScRange(0,0,0,MAXCOL,MAXROW,MAXTAB) );
//STRIP001
//STRIP001          //  modified...
//STRIP001
//STRIP001      if (!pShell->IsModified())
//STRIP001      {
//STRIP001          pShell->SetModified( TRUE );
//STRIP001          SfxBindings* pBindings = GetViewBindings();
//STRIP001          if (pBindings)
//STRIP001          {
//STRIP001              pBindings->Invalidate( SID_SAVEDOC );
//STRIP001              pBindings->Invalidate( SID_DOC_MODIFIED );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
/*N*/   return 0;
/*N*/ }

//STRIP001 void ScDocument::StartTrackTimer()
//STRIP001 {
//STRIP001  if (!aTrackTimer.IsActive())        // nicht ewig aufschieben
//STRIP001      aTrackTimer.Start();
//STRIP001 }

/*N*/ ScDocument::~ScDocument()
/*N*/ {
/*N*/   DBG_ASSERT( !bInLinkUpdate, "bInLinkUpdate in dtor" );
/*N*/
/*N*/   bInDtorClear = TRUE;
/*N*/
/*N*/   // first of all disable all refresh timers by deleting the control
/*N*/   if ( pRefreshTimerControl )
/*N*/   {   // To be sure there isn't anything running do it with a protector,
/*N*/       // this ensures also that nothing needs the control anymore.
/*N*/       ScRefreshTimerProtector aProt( GetRefreshTimerControlAddress() );
/*N*/       delete pRefreshTimerControl, pRefreshTimerControl = NULL;
/*N*/   }
/*N*/
/*N*/   // Links aufrauemen
/*N*/
/*N*/   if ( pLinkManager )
/*N*/   {
/*N*/       // BaseLinks freigeben
/*N*/       for ( USHORT n = pLinkManager->GetServers().Count(); n; )
/*?*/           pLinkManager->GetServers()[ --n ]->Closed();
/*N*/
/*N*/       if ( pLinkManager->GetLinks().Count() )
/*N*/           pLinkManager->Remove( 0, pLinkManager->GetLinks().Count() );
/*N*/   }
/*N*/
/*N*/   ScAddInAsync::RemoveDocument( this );
/*N*/   ScAddInListener::RemoveDocument( this );
/*N*/   delete pChartListenerCollection;    // vor pBASM wg. evtl. Listener!
/*N*/   pChartListenerCollection = NULL;
/*N*/   // BroadcastAreas vor allen Zellen zerstoeren um unnoetige
/*N*/   // Einzel-EndListenings der Formelzellen zu vermeiden
/*N*/   delete pBASM;       // BroadcastAreaSlotMachine
/*N*/   pBASM = NULL;
/*N*/
/*N*/   if (pUnoBroadcaster)
/*N*/   {
/*N*/       delete pUnoBroadcaster;     // broadcasted nochmal SFX_HINT_DYING
/*N*/       pUnoBroadcaster = NULL;
/*N*/   }
/*N*/
/*N*/   Clear();
/*N*/
/*N*/   if (pCondFormList)
/*N*/   {
/*N*/       pCondFormList->DeleteAndDestroy( 0, pCondFormList->Count() );
/*N*/       DELETEZ(pCondFormList);
/*N*/   }
/*N*/   if (pValidationList)
/*N*/   {
/*N*/       pValidationList->DeleteAndDestroy( 0, pValidationList->Count() );
/*N*/       DELETEZ(pValidationList);
/*N*/   }
/*N*/   delete pRangeName;
/*N*/   delete pDBCollection;
/*N*/   delete pPivotCollection;
/*N*/   delete pSelectionAttr;
/*N*/   delete pChartCollection;
/*N*/   DeleteDrawLayer();
/*N*/   delete pFormatExchangeList;
/*N*/   delete pPrinter;
/*N*/   ImplDeleteOptions();
/*N*/   delete pConsolidateDlgData;
/*N*/   delete pLinkManager;
/*N*/   delete pClipData;
/*N*/   delete pDetOpList;                  // loescht auch die Eintraege
/*N*/   delete pChangeTrack;
/*N*/   delete pEditEngine;
/*N*/   delete pChangeViewSettings;         // und weg damit
/*N*/
/*N*/   delete pDPCollection;
/*N*/
/*N*/   // delete the EditEngine before destroying the xPoolHelper
/*N*/   delete pCacheFieldEditEngine;
/*N*/
/*N*/   if ( xPoolHelper.isValid() && !bIsClip )
/*N*/       xPoolHelper->SourceDocumentGone();
/*N*/   xPoolHelper.unbind();
/*N*/
/*N*/   DeleteColorTable();
/*N*/   delete pScriptTypeData;
/*N*/   delete pOtherObjects;
/*N*/
/*N*/ }

//STRIP001 void ScDocument::InitClipPtrs( ScDocument* pSourceDoc )
//STRIP001 {
//STRIP001  DBG_ASSERT(bIsClip, "InitClipPtrs und nicht bIsClip");
//STRIP001
//STRIP001  if (pCondFormList)
//STRIP001  {
//STRIP001      pCondFormList->DeleteAndDestroy( 0, pCondFormList->Count() );
//STRIP001      DELETEZ(pCondFormList);
//STRIP001  }
//STRIP001  if (pValidationList)
//STRIP001  {
//STRIP001      pValidationList->DeleteAndDestroy( 0, pValidationList->Count() );
//STRIP001      DELETEZ(pValidationList);
//STRIP001  }
//STRIP001
//STRIP001  Clear();
//STRIP001
//STRIP001  xPoolHelper = pSourceDoc->xPoolHelper;
//STRIP001
//STRIP001  //  bedingte Formate / Gueltigkeiten
//STRIP001  //! Vorlagen kopieren?
//STRIP001  const ScConditionalFormatList* pSourceCond = pSourceDoc->pCondFormList;
//STRIP001  if ( pSourceCond )
//STRIP001      pCondFormList = new ScConditionalFormatList(this, *pSourceCond);
//STRIP001  const ScValidationDataList* pSourceValid = pSourceDoc->pValidationList;
//STRIP001  if ( pSourceValid )
//STRIP001      pValidationList = new ScValidationDataList(this, *pSourceValid);
//STRIP001
//STRIP001                      // Links in Stream speichern
//STRIP001  delete pClipData;
//STRIP001  if (pSourceDoc->HasDdeLinks())
//STRIP001  {
//STRIP001      pClipData = new SvMemoryStream;
//STRIP001      pSourceDoc->SaveDdeLinks(*pClipData);
//STRIP001  }
//STRIP001  else
//STRIP001      pClipData = NULL;
//STRIP001 }

/*N*/ SvNumberFormatter* ScDocument::GetFormatTable() const
/*N*/ {
/*N*/   return xPoolHelper->GetFormTable();
/*N*/ }

/*N*/ SfxItemPool* ScDocument::GetEditPool() const
/*N*/ {
/*N*/   return xPoolHelper->GetEditPool();
/*N*/ }

/*N*/ SfxItemPool* ScDocument::GetEnginePool() const
/*N*/ {
/*N*/   return xPoolHelper->GetEnginePool();
/*N*/ }

/*N*/ ScFieldEditEngine& ScDocument::GetEditEngine()
/*N*/ {
/*N*/   if ( !pEditEngine )
/*N*/   {
/*N*/       pEditEngine = new ScFieldEditEngine( GetEnginePool(), GetEditPool() );
/*N*/       pEditEngine->SetUpdateMode( FALSE );
/*N*/       pEditEngine->EnableUndo( FALSE );
/*N*/       pEditEngine->SetRefMapMode( MAP_100TH_MM );
/*N*/       pEditEngine->SetForbiddenCharsTable( xForbiddenCharacters );
/*N*/   }
/*N*/   return *pEditEngine;
/*N*/ }

/*N*/ void ScDocument::ResetClip( ScDocument* pSourceDoc, const ScMarkData* pMarks )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //STRIP001    if (bIsClip)
//STRIP001  {
//STRIP001      InitClipPtrs(pSourceDoc);
//STRIP001
//STRIP001      for (USHORT i = 0; i <= MAXTAB; i++)
//STRIP001          if (pSourceDoc->pTab[i])
//STRIP001              if (!pMarks || pMarks->GetTableSelect(i))
//STRIP001              {
//STRIP001                  String aString;
//STRIP001                  pSourceDoc->pTab[i]->GetName(aString);
//STRIP001                  pTab[i] = new ScTable(this, i, aString);
//STRIP001                  nMaxTableNumber = i+1;
//STRIP001              }
//STRIP001  }
//STRIP001  else
//STRIP001      DBG_ERROR("ResetClip");
/*N*/ }

/*N*/ void ScDocument::ResetClip( ScDocument* pSourceDoc, USHORT nTab )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //STRIP001    if (bIsClip)
//STRIP001  {
//STRIP001      InitClipPtrs(pSourceDoc);
//STRIP001
//STRIP001      pTab[nTab] = new ScTable(this, nTab,
//STRIP001                          String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("baeh")));
//STRIP001      nMaxTableNumber = nTab+1;
//STRIP001  }
//STRIP001  else
//STRIP001      DBG_ERROR("ResetClip");
}

/*N*/ void lcl_RefreshPivotData( ScPivotCollection* pColl )
/*N*/ {
/*N*/   USHORT nCount = pColl->GetCount();
/*N*/   for (USHORT i=0; i<nCount; i++)
/*N*/   {
/*N*/       ScPivot* pPivot = (*pColl)[i];
/*N*/       if (pPivot->CreateData(TRUE))
/*N*/           pPivot->ReleaseData();
/*N*/   }
/*N*/ }


/*N*/ BOOL ScDocument::SymbolStringCellsPending() const
/*N*/ {
/*N*/     return pLoadedSymbolStringCellList && pLoadedSymbolStringCellList->Count();
/*N*/ }


/*N*/ List& ScDocument::GetLoadedSymbolStringCellsList()
/*N*/ {
/*N*/     if ( !pLoadedSymbolStringCellList )
/*N*/         pLoadedSymbolStringCellList = new List;
/*N*/     return *pLoadedSymbolStringCellList;
/*N*/ }


/*N*/ BOOL ScDocument::Load( SvStream& rStream, ScProgress* pProgress )
/*N*/ {
/*N*/   bLoadingDone = FALSE;
/*N*/
/*N*/   //----------------------------------------------------
/*N*/
/*N*/   Clear();
/*N*/   USHORT nOldBufSize = rStream.GetBufferSize();
/*N*/   rStream.SetBufferSize( 32768 );
/*N*/
/*N*/       //  Progress-Bar
/*N*/
/*N*/ //    ULONG nCurPos = rStream.Tell();
/*N*/ //    ULONG nEndPos = rStream.Seek( STREAM_SEEK_TO_END );
/*N*/ //    rStream.Seek( nCurPos );
/*N*/ //    ScProgress aProgress( NULL, ScGlobal::GetRscString(STR_LOAD_DOC), nEndPos - nCurPos );
/*N*/
/*N*/   BOOL bError = FALSE;
/*N*/   USHORT nVersion = 0;
/*N*/   USHORT nVerMaxRow = MAXROW_30;      // 8191, wenn in der Datei nichts steht
/*N*/   USHORT nTab = 0;
/*N*/   USHORT nEnumDummy;
/*N*/   String aEmptyName;
/*N*/   String aPageStyle;
/*N*/   CharSet eOldSet = rStream.GetStreamCharSet();
/*N*/
/*N*/   USHORT nID;
/*N*/   rStream >> nID;
/*N*/   if (nID == SCID_DOCUMENT || nID == SCID_NEWDOCUMENT )
/*N*/   {
/*N*/       ScReadHeader aHdr( rStream );
/*N*/       while (aHdr.BytesLeft() && !bError )
/*N*/       {
/*N*/           USHORT nSubID;
/*N*/           rStream >> nSubID;
/*N*/           switch (nSubID)
/*N*/           {
/*N*/               case SCID_DOCFLAGS:
/*N*/                   {
/*N*/                       ScReadHeader aFlagsHdr( rStream );
/*N*/
/*N*/                       rStream >> nVersion;                // 312 abwaerts
/*N*/                       rStream.ReadByteString( aPageStyle, rStream.GetStreamCharSet() );
/*N*/                       rStream >> bProtected;              // Dokument geschuetzt
/*N*/                       String aPass;
/*N*/                       rStream.ReadByteString( aPass, rStream.GetStreamCharSet() );
/*N*/                       if (aPass.Len())
/*?*/                           SvPasswordHelper::GetHashPassword(aProtectPass, aPass);
/*N*/                       if ( aFlagsHdr.BytesLeft() )
/*N*/                       {
/*N*/                           rStream >> nEnumDummy;
/*N*/                           eLanguage = LanguageType( nEnumDummy );
/*N*/                       }
/*N*/                       if ( aFlagsHdr.BytesLeft() )
/*N*/                           rStream >> bAutoCalc;
/*N*/                       if ( aFlagsHdr.BytesLeft() )
/*N*/                           rStream >> nVisibleTab;
/*N*/                       if ( aFlagsHdr.BytesLeft() )
/*N*/                           rStream >> nVersion;            // echte Version
/*N*/                       if ( aFlagsHdr.BytesLeft() )
/*N*/                           rStream >> nVerMaxRow;          // sonst auf 8191 lassen
/*N*/
/*N*/                       nSrcVer     = nVersion;             // Member
/*N*/                       nSrcMaxRow  = nVerMaxRow;           // Member
/*N*/
/*N*/                       // Fuer Debugging bis hin zur SC 3.0a:
/*N*/                       if( nVersion > 0x0002 && nVersion < SC_NUMFMT )
/*N*/                       {
/*N*/                           bError = TRUE;
/*N*/                           rStream.SetError( SVSTREAM_WRONGVERSION );
/*N*/                       }
/*N*/
/*N*/                       // Das obere Byte muss kleiner oder gleich sein
/*N*/                       //  (3.1 Dateien mit 8192 Zeilen koennen noch gelesen werden)
/*N*/
/*N*/                       if( ( nSrcVer & 0xFF00 ) > ( SC_CURRENT_VERSION & 0xFF00 ) )
/*N*/                       {
/*N*/                           bError = TRUE;
/*N*/                           rStream.SetError( SVSTREAM_WRONGVERSION );
/*N*/                       }
/*N*/                   }
/*N*/                   break;
/*N*/               case SCID_CHARSET:
/*N*/                   {
/*N*/                       ScReadHeader aSetHdr( rStream );
/*N*/                       BYTE cSet, cGUI;    // cGUI is dummy, old GUIType
/*N*/                       rStream >> cGUI >> cSet;
/*N*/                       eSrcSet = (CharSet) cSet;
/*N*/                         rStream.SetStreamCharSet( ::GetSOLoadTextEncoding(
/*N*/                             eSrcSet, (USHORT)rStream.GetVersion() ) );
/*N*/                   }
/*N*/                   break;
/*?*/               case SCID_LINKUPMODE: //    Link Update Mode
/*?*/                   {
/*?*/                       ScReadHeader aSetHdr( rStream );
/*?*/                       BYTE cSet;
/*?*/                       rStream >> cSet;
/*?*/                       eLinkMode=(ScLkUpdMode) cSet;
/*?*/                   }
/*?*/                   break;
/*N*/               case SCID_TABLE:
/*N*/                   pTab[nTab] = new ScTable(this, nTab, aEmptyName);
/*N*/                   pTab[nTab]->SetPageStyle( aPageStyle );
/*N*/                   pTab[nTab]->Load(rStream,nVersion,pProgress);
/*N*/                   ++nTab;
/*N*/                   break;
/*N*/               case SCID_DRAWING:
/*N*/                   LoadDrawLayer(rStream);
/*N*/                   break;
/*N*/               case SCID_DDELINKS:
/*N*/                   LoadDdeLinks(rStream);
/*N*/                   break;
/*N*/               case SCID_AREALINKS:
/*N*/                   LoadAreaLinks(rStream);
/*N*/                   break;
/*N*/               case SCID_RANGENAME:
/*N*/                   pRangeName->Load(rStream, nVersion );
/*N*/                   break;
/*N*/               case SCID_DBAREAS:
/*N*/                   pDBCollection->Load( rStream );
/*N*/                   break;
/*?*/               case SCID_DATAPILOT:
/*?*/                   GetDPCollection()->LoadNew( rStream );
/*?*/                   break;
/*N*/               case SCID_PIVOT:
/*N*/                   pPivotCollection->Load( rStream );
/*N*/                   break;
/*N*/               case SCID_CHARTS:
/*N*/                   pChartCollection->Load( this, rStream );
/*N*/                   break;
/*N*/               case SCID_COLNAMERANGES:
/*N*/                   xColNameRanges->Load( rStream, nVersion );
/*N*/                   break;
/*N*/               case SCID_ROWNAMERANGES:
/*N*/                   xRowNameRanges->Load( rStream, nVersion );
/*N*/                   break;
/*N*/               case SCID_CONDFORMATS:
/*N*/                   if (!pCondFormList)
/*N*/                       pCondFormList = new ScConditionalFormatList;
/*N*/                   pCondFormList->Load( rStream, this );
/*N*/                   break;
/*N*/               case SCID_VALIDATION:
/*N*/                   if (!pValidationList)
/*N*/                       pValidationList = new ScValidationDataList;
/*N*/                   pValidationList->Load( rStream, this );
/*N*/                   break;
/*N*/               case SCID_DETOPLIST:
/*N*/                   if (!pDetOpList)
/*N*/                       pDetOpList = new ScDetOpList;
/*N*/                   pDetOpList->Load( rStream );
/*N*/                   break;
/*N*/               case SCID_NUMFORMAT:
/*N*/                   {
/*N*/                       ScReadHeader aNumHeader(rStream);
/*N*/                       xPoolHelper->GetFormTable()->Load(rStream);
/*N*/                   }
/*N*/                   break;
/*N*/               case SCID_DOCOPTIONS:
/*N*/                   ImplLoadDocOptions(rStream);
/*N*/                   break;
/*N*/               case SCID_VIEWOPTIONS:
/*N*/                   ImplLoadViewOptions(rStream);
/*N*/                   break;
/*N*/               case SCID_PRINTSETUP:
/*N*/                   {
/*N*/                       ScReadHeader aJobHeader(rStream);
/*N*/                       SfxItemSet* pSet = new SfxItemSet( *xPoolHelper->GetDocPool(),
/*N*/                               SID_PRINTER_NOTFOUND_WARN, SID_PRINTER_NOTFOUND_WARN,
/*N*/                               SID_PRINTER_CHANGESTODOC,  SID_PRINTER_CHANGESTODOC,
/*N*/                               SID_SCPRINTOPTIONS,        SID_SCPRINTOPTIONS,
/*N*/                               NULL );
/*N*/                       SetPrinter( SfxPrinter::Create( rStream, pSet ) );
/*N*/                   }
/*N*/                   break;
/*?*/               case SCID_CONSOLIDATA:
/*?*/                   if (!pConsolidateDlgData)
/*?*/                       pConsolidateDlgData = new ScConsolidateParam;
/*?*/                   pConsolidateDlgData->Load( rStream );
/*?*/                   break;
/*?*/               case SCID_CHANGETRACK:
/*N*/                   if ( pChangeTrack ) // Changetracking.sdc
/*N*/ /*?*/                         pChangeTrack->Clear();  // es kann nur einen geben
/*N*/ /*?*/                     else
/*N*/ /*?*/                         StartChangeTracking();
/*N*/ /*?*/                     pChangeTrack->Load( rStream, nVersion );
/*?*/                   break;
/*N*/               case SCID_CHGVIEWSET:
/*N*/                   if (!pChangeViewSettings)
/*N*/                       pChangeViewSettings = new ScChangeViewSettings;
/*N*/                   pChangeViewSettings->Load( rStream, nVersion );
/*N*/                   break;
/*N*/               default:
/*N*/                   {
/*N*/                       DBG_ERROR("unbekannter Sub-Record in ScDocument::Load");
/*N*/                       ScReadHeader aDummyHdr( rStream );
/*N*/                   }
/*N*/           }
/*N*/
/*N*/           if (rStream.GetError() != SVSTREAM_OK)
/*N*/               bError = TRUE;
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       //  Assertion nur, wenn kein Passwort gesetzt ist
/*N*/       DBG_ASSERT( rStream.GetKey().Len(), "Load: SCID_DOCUMENT nicht gefunden" );
/*N*/       bError = TRUE;
/*N*/   }
/*N*/
/*N*/   rStream.SetStreamCharSet( eOldSet );
/*N*/   rStream.SetBufferSize( nOldBufSize );
/*N*/
/*N*/   if (!bError)                                    // Neuberechnungen
/*N*/   {
/*N*/       xPoolHelper->GetStylePool()->UpdateStdNames();  // falls mit Version in anderer Sprache gespeichert
/*N*/
/*N*/       //  Zahlformat-Sprache
/*N*/       //  (kann nicht in LoadPool passieren, weil der Numberformatter geladen sein muss)
/*N*/
/*N*/       ScDocumentPool* pPool = xPoolHelper->GetDocPool();
/*N*/       if ( pPool->GetLoadingVersion() == 0 )              // 0 = Pool-Version bis 3.1
/*N*/       {
/*N*/           //  in 3.1-Dokumenten gibt es ATTR_LANGUAGE_FORMAT noch nicht
/*N*/           //  darum bei Bedarf zu ATTR_VALUE_FORMAT noch die Sprache dazutun
/*N*/           //  (Bug #37441#)
/*N*/
/*N*/           //  harte Attribute:
/*N*/
/*N*/           SvNumberFormatter* pFormatter = xPoolHelper->GetFormTable();
/*N*/           USHORT nCount = pPool->GetItemCount(ATTR_PATTERN);
/*N*/           ScPatternAttr* pPattern;
/*N*/           for (USHORT i=0; i<nCount; i++)
/*N*/           {
/*N*/               pPattern = (ScPatternAttr*)pPool->GetItem(ATTR_PATTERN, i);
/*N*/               if (pPattern)
/*N*/                     ScGlobal::AddLanguage( pPattern->GetItemSet(), *pFormatter );
/*N*/           }
/*N*/
/*N*/           //  Vorlagen:
/*N*/
/*N*/           SfxStyleSheetIterator aIter( xPoolHelper->GetStylePool(), SFX_STYLE_FAMILY_PARA );
/*N*/           for ( SfxStyleSheetBase* pStyle = aIter.First(); pStyle; pStyle = aIter.Next() )
/*N*/                 ScGlobal::AddLanguage( pStyle->GetItemSet(), *pFormatter );
/*N*/       }
/*N*/
/*N*/         // change FontItems in styles
/*N*/         xPoolHelper->GetStylePool()->ConvertFontsAfterLoad();
/*N*/
/*N*/       //  Druckbereiche etc.
/*N*/
/*N*/       SfxStyleSheetIterator   aIter( xPoolHelper->GetStylePool(), SFX_STYLE_FAMILY_PAGE );
/*N*/       ScStyleSheet*           pStyleSheet = NULL;
/*N*/
/*N*/       nMaxTableNumber = 0;
/*N*/       for (USHORT i=0; i<=MAXTAB; i++)
/*N*/           if (pTab[i])
/*N*/           {
/*N*/               // MaxTableNumber ermitteln
/*N*/
/*N*/               nMaxTableNumber = i+1;
/*N*/
/*N*/               // Druckbereiche aus <= 3.00.2 Dokumenten
/*N*/               // aus den PageStyles holen und jetzt an
/*N*/               // der Tabelle speichern.
/*N*/
/*N*/               pStyleSheet = (ScStyleSheet*)aIter.Find( pTab[i]->GetPageStyle() );
/*N*/
/*N*/               if ( pStyleSheet )
/*N*/               {
/*N*/                   SfxItemSet&         rSet            = pStyleSheet->GetItemSet();
/*N*/                   const ScRangeItem*  pPrintAreaItem  = NULL;
/*N*/                   const ScRangeItem*  pRepeatColItem  = NULL;
/*N*/                   const ScRangeItem*  pRepeatRowItem  = NULL;
/*N*/
/*N*/                   rSet.GetItemState( ATTR_PAGE_PRINTAREA, TRUE,
/*N*/                                      (const SfxPoolItem**)&pPrintAreaItem );
/*N*/                   rSet.GetItemState( ATTR_PAGE_REPEATCOL, TRUE,
/*N*/                                      (const SfxPoolItem**)&pRepeatColItem );
/*N*/                   rSet.GetItemState( ATTR_PAGE_REPEATROW, TRUE,
/*N*/                                      (const SfxPoolItem**)&pRepeatRowItem );
/*N*/
/*N*/                   if ( pPrintAreaItem ) // Druckbereiche
/*N*/                   {
/*N*/                       if ( !pPrintAreaItem->GetFlags() )
/*N*/                       {
/*N*/                           SetPrintRangeCount( i, 1 );
/*N*/                           SetPrintRange( i, 0, pPrintAreaItem->GetRange() );
/*N*/                       }
/*N*/                       rSet.ClearItem( ATTR_PAGE_PRINTAREA );
/*N*/                   }
/*N*/
/*N*/                   if ( pRepeatColItem ) // Wiederholungsspalte
/*N*/                   {
/*?*/                       SetRepeatColRange( i, !pRepeatColItem->GetFlags()
/*?*/                                           ? &pRepeatColItem->GetRange()
/*?*/                                           : (const ScRange *)NULL );
/*?*/                       rSet.ClearItem( ATTR_PAGE_REPEATCOL );
/*N*/                   }
/*N*/
/*N*/                   if ( pRepeatRowItem ) // Wiederholungszeile
/*N*/                   {
/*?*/                       SetRepeatRowRange( i, !pRepeatRowItem->GetFlags()
/*?*/                                           ? &pRepeatRowItem->GetRange()
/*?*/                                           : (const ScRange *)NULL );
/*?*/                       rSet.ClearItem( ATTR_PAGE_REPEATROW );
/*?*/                   }
/*N*/               }
/*N*/           }
/*N*/
/*N*/
/*N*/       if ( pDPCollection && pDPCollection->GetCount() )
/*?*/           pPivotCollection->FreeAll();
/*N*/       else
/*N*/       {
/*N*/           lcl_RefreshPivotData( pPivotCollection );
/*N*/           GetDPCollection()->ConvertOldTables( *pPivotCollection );
/*N*/       }
/*N*/       if ( pDPCollection )
/*N*/           pDPCollection->EnsureNames();   // make sure every table has a name
/*N*/
/*N*/       SetAutoFilterFlags();
/*N*/       if (pDrawLayer)
/*N*/           UpdateAllCharts();
/*N*/ #ifndef PRODUCT
/*N*/ //2do: wg. #62107
/*N*/ // ChartListenerCollection speichern/laden, damit nach dem Laden das Update
/*N*/ // hier einmal eingespart werden kann und somit nicht mehr alle Charts
/*N*/ // angefasst werden muessen. Die ChartListenerCollection muss dann zum Master
/*N*/ // der Referenzen werden.
/*N*/ //        static BOOL bShown = 0;
/*N*/ //        if ( !bShown && SOFFICE_FILEFORMAT_NOW > SOFFICE_FILEFORMAT_50 )
/*N*/ //        {
/*N*/ //            bShown = 1;
/*N*/ //            DBG_ERRORFILE( "bei inkompatiblem FileFormat ChartListenerCollection speichern!" );
/*N*/ //        }
/*N*/ #endif
/*N*/       UpdateChartListenerCollection();
/*N*/       if (pDrawLayer)
/*N*/           RefreshNoteFlags();
/*N*/       CalcAfterLoad();
/*N*/   }
/*N*/
/*N*/     if ( pLoadedSymbolStringCellList )
/*N*/     {   // we had symbol string cells, list was cleared by columns, delete it
/*N*/         delete pLoadedSymbolStringCellList;
/*N*/         pLoadedSymbolStringCellList = NULL;
/*N*/     }
/*N*/
/*N*/   //----------------------------------------------------
/*N*/
/*N*/   bLoadingDone = TRUE;
/*N*/
/*N*/   return !bError;
/*N*/ }

/*N*/ BOOL ScDocument::Save( SvStream& rStream, ScProgress* pProgress ) const
/*N*/ {
/*N*/   ((ScDocument*)this)->bLoadingDone = FALSE;      // nicht zwischendrin reinpfuschen lassen
/*N*/
/*N*/   ((ScDocument*)this)->bLostData = FALSE;         // wird beim Speichern gesetzt
/*N*/
/*N*/   ((ScDocument*)this)->nSrcVer = SC_CURRENT_VERSION;
/*N*/   ((ScDocument*)this)->nSrcMaxRow = MAXROW;
/*N*/   if ( rStream.GetVersion() <= SOFFICE_FILEFORMAT_31 )
/*N*/   {
/*N*/       //  3.1 Export -> nur 8192 Zeilen schreiben, und kompatible Versionsnummer
/*N*/
/*N*/       ((ScDocument*)this)->nSrcVer = SC_31_EXPORT_VER;
/*N*/       ((ScDocument*)this)->nSrcMaxRow = MAXROW_30;
/*N*/   }
/*N*/   else if ( rStream.GetVersion() <= SOFFICE_FILEFORMAT_40 )
/*N*/   {   //  4.0 Export -> kompatible Versionsnummer
/*N*/       ((ScDocument*)this)->nSrcVer = SC_40_EXPORT_VER;
/*N*/   }
/*N*/
/*N*/   USHORT i;
/*N*/   USHORT nOldBufSize = rStream.GetBufferSize();
/*N*/   rStream.SetBufferSize( 32768 );
/*N*/
/*N*/   CharSet eOldSet = rStream.GetStreamCharSet();
/*N*/     CharSet eStoreCharSet = ::GetSOStoreTextEncoding(
/*N*/         gsl_getSystemTextEncoding(), (USHORT)rStream.GetVersion() );
/*N*/     rStream.SetStreamCharSet( eStoreCharSet );
/*N*/
/*N*/
/*N*/       //  Progress-Bar
/*N*/
/*N*/   long nSavedDocCells = 0;
/*N*/ //    ScProgress aProgress( NULL, ScGlobal::GetRscString( STR_SAVE_DOC ), GetWeightedCount() + 1 );
/*N*/
/*N*/   {
/*N*/       rStream << (USHORT) SCID_NEWDOCUMENT;
/*N*/       ScWriteHeader aHdr( rStream );
/*N*/
/*N*/       //  Flags
/*N*/
/*N*/       {
/*N*/           rStream << (USHORT) SCID_DOCFLAGS;
/*N*/           ScWriteHeader aFlagsHdr( rStream, 18 );         //! ausprobieren
/*N*/
/*N*/           // wg. Bug in 312 ScToken::RelToRelAbs mit DoubleRefs bekommt
/*N*/           // die 312er immer vorgegaukelt, dass es keine RelRefs gaebe,
/*N*/           // was auch ok ist, da immer absolut gespeichert wird und
/*N*/           // SR_RELATIVE nie zur Verwendung kam und nicht kommen darf.
/*N*/           if ( nSrcVer & 0xFF00 )
/*N*/               rStream << (USHORT) nSrcVer;
/*N*/               // hoehere Major-Version darf von 312 nicht geladen werden
/*N*/           else
/*N*/               rStream << (USHORT) (SC_RELATIVE_REFS - 1);
/*N*/
/*N*/           // dummy page style (for compatibility)
/*N*/           rStream.WriteByteString(
/*N*/                       String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM(STRING_STANDARD)),
/*N*/                       rStream.GetStreamCharSet() );
/*N*/           rStream << bProtected;                  // Dokument geschuetzt
/*N*/           String aPass;
/*N*/           //rStream.WriteByteString( aProtectPass, rStream.GetStreamCharSet() );
/*N*/           rStream.WriteByteString( aPass, rStream.GetStreamCharSet() );
/*N*/           rStream << (USHORT) eLanguage;
/*N*/           rStream << bAutoCalc;
/*N*/
/*N*/           rStream << nVisibleTab;
/*N*/
/*N*/           // und hier jetzt die echte Versionsnummer
/*N*/           rStream << (USHORT) nSrcVer;
/*N*/
/*N*/           rStream << nSrcMaxRow;                  // Zeilenanzahl
/*N*/       }
/*N*/
/*N*/       //  Zeichensatz
/*N*/
/*N*/       {
/*N*/           rStream << (USHORT) SCID_CHARSET;
/*N*/           ScWriteHeader aSetHdr( rStream, 2 );
/*N*/           rStream << (BYTE) 0     // dummy, old System::GetGUIType()
/*N*/                     << (BYTE) eStoreCharSet;
/*N*/       }
/*N*/
/*N*/       //  Link Update Mode
/*N*/
/*N*/       if(eLinkMode!=LM_UNKNOWN)
/*N*/       {
/*?*/           rStream << (USHORT) SCID_LINKUPMODE;
/*?*/           ScWriteHeader aSetHdr( rStream, 1 );
/*?*/           rStream << (BYTE) eLinkMode;
/*N*/       }
/*N*/
/*N*/       rStream << (USHORT) SCID_RANGENAME;
/*N*/       pRangeName->Store( rStream );
/*N*/
/*N*/       rStream << (USHORT) SCID_DBAREAS;
/*N*/       pDBCollection->Store( rStream );
/*N*/
/*N*/       rStream << (USHORT) SCID_DDELINKS;
/*N*/       SaveDdeLinks( rStream );
/*N*/
/*N*/       rStream << (USHORT) SCID_AREALINKS;
/*N*/       SaveAreaLinks( rStream );
/*N*/
/*N*/       {
/*N*/           rStream << (USHORT) SCID_NUMFORMAT;
/*N*/           ScWriteHeader aNumHeader(rStream);
/*N*/           xPoolHelper->GetFormTable()->Save(rStream);
/*N*/       }
/*N*/
/*N*/       if ( xColNameRanges->Count() )
/*N*/       {
/*N*/           rStream << (USHORT) SCID_COLNAMERANGES;
/*N*/           xColNameRanges->Store( rStream );
/*N*/       }
/*N*/       if ( xRowNameRanges->Count() )
/*N*/       {
/*N*/           rStream << (USHORT) SCID_ROWNAMERANGES;
/*N*/           xRowNameRanges->Store( rStream );
/*N*/       }
/*N*/
/*N*/       if (pCondFormList)
/*N*/           pCondFormList->ResetUsed();     // wird beim Speichern der Tabellen gesetzt
/*N*/       if (pValidationList)
/*N*/           pValidationList->ResetUsed();   // wird beim Speichern der Tabellen gesetzt
/*N*/
/*N*/       //  Tabellen (Daten)
/*N*/
/*N*/       for (i=0; i<=MAXTAB; i++)
/*N*/       {
/*N*/           if (pTab[i])
/*N*/           {
/*N*/               rStream << (USHORT) SCID_TABLE;
/*N*/               pTab[i]->Save(rStream, nSavedDocCells, pProgress);
/*N*/           }
/*N*/       }
/*N*/
/*N*/       //  bedingte Formate / Gueltigkeit
/*N*/       //  beim Speichern der Tabellen ist eingetragen worden,
/*N*/       //  welche Eintraege benutzt werden
/*N*/
/*N*/       if (pCondFormList)
/*N*/       {
/*N*/           rStream << (USHORT) SCID_CONDFORMATS;
/*N*/           pCondFormList->Store(rStream);
/*N*/       }
/*N*/       if (pValidationList)
/*N*/       {
/*N*/           rStream << (USHORT) SCID_VALIDATION;
/*N*/           pValidationList->Store(rStream);
/*N*/       }
/*N*/
/*N*/       //  Liste der Detektiv-Operationen (zum Aktualisieren)
/*N*/       if (pDetOpList)
/*N*/       {
/*N*/           rStream << (USHORT) SCID_DETOPLIST;
/*N*/           pDetOpList->Store(rStream);
/*N*/       }
/*N*/
/*N*/       //  Drawing
/*N*/
/*N*/ //        if (pDrawLayer && pDrawLayer->HasObjects())
/*N*/       //  auch ohne Objekte - wegen ColorTable etc.
/*N*/
/*N*/       if (pDrawLayer)
/*N*/       {
/*N*/           rStream << (USHORT) SCID_DRAWING;
/*N*/           StoreDrawLayer(rStream);
/*N*/       }
/*N*/
/*N*/       //  Collections
/*N*/
/*N*/       //  (new) DataPilot collection must be saved before old Pivot collection
/*N*/       //  so old data can be skipped by new office
/*N*/       //  not in 3.0 or 4.0 export to avoid warning messages
/*N*/
/*N*/       if ( nSrcVer > SC_40_EXPORT_VER && pDPCollection && pDPCollection->GetCount() )
/*N*/       {
/*?*/           rStream << (USHORT) SCID_DATAPILOT;             // new data
/*?*/           pDPCollection->StoreNew( rStream );
/*N*/       }
/*N*/
/*N*/       rStream << (USHORT) SCID_PIVOT;                     // old data
/*N*/       if ( pDPCollection && pDPCollection->GetCount() )
/*N*/           pDPCollection->StoreOld( rStream );
/*N*/       else
/*N*/           pPivotCollection->Store( rStream );             // not converted or all empty
/*N*/
/*N*/               //  Charts werden hier nicht mehr gespeichert, weil
/*N*/               //  jedes Chart seine Daten selber speichert
/*N*/
/*N*/       DBG_ASSERT(!pChartCollection || !pChartCollection->GetCount(),
/*N*/                       "wer hat da ein Chart eingetragen?");
/*N*/
/*N*/       rStream << (USHORT) SCID_DOCOPTIONS;
/*N*/       ImplSaveDocOptions(rStream);
/*N*/
/*N*/       rStream << (USHORT) SCID_VIEWOPTIONS;
/*N*/       ImplSaveViewOptions(rStream);
/*N*/
/*N*/       //  Job-Setup vom Printer
/*N*/
/*N*/       if (pPrinter)
/*N*/       {
/*N*/           rStream << (USHORT) SCID_PRINTSETUP;
/*N*/           ScWriteHeader aJobHeader(rStream);
/*N*/
/*N*/           ((ScDocument*)this)->GetPrinter()->Store( rStream );
/*N*/       }
/*N*/
/*N*/       if ( nSrcVer > SC_40_EXPORT_VER )   //  Das folgende nicht bei 3.0 oder 4.0 Export...
/*N*/       {
/*N*/           if (pConsolidateDlgData)        //  Einstellungen fuer den Konsolidieren-Dialog
/*N*/           {
/*?*/               rStream << (USHORT) SCID_CONSOLIDATA;
/*?*/               pConsolidateDlgData->Store( rStream );
/*N*/           }
/*N*/           if ( pChangeTrack )
/*N*/           {
/*N*/               rStream << (USHORT) SCID_CHANGETRACK;
/*N*/               pChangeTrack->Store( rStream );
/*N*/           }
/*N*/           if ( pChangeViewSettings )
/*N*/           {
/*N*/               rStream << (USHORT) SCID_CHGVIEWSET;
/*N*/               pChangeViewSettings->Store( rStream );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   rStream.SetStreamCharSet( eOldSet );
/*N*/   rStream.SetBufferSize( nOldBufSize );
/*N*/
/*N*/   ((ScDocument*)this)->bLoadingDone = TRUE;
/*N*/
/*N*/   return ( rStream.GetError() == SVSTREAM_OK );
/*N*/ }

/*N*/ void ScDocument::SetLostData()
/*N*/ {
/*N*/   bLostData = TRUE;
/*N*/ }

//STRIP001 void ScDocument::DeleteNumberFormat( const ULONG* pDelKeys, ULONG nCount )
//STRIP001 {
//STRIP001 /*
//STRIP001  for (ULONG i = 0; i < nCount; i++)
//STRIP001      xPoolHelper->GetFormTable()->DeleteEntry(pDelKeys[i]);
//STRIP001 */
//STRIP001 }

/*N*/ void ScDocument::PutCell( USHORT nCol, USHORT nRow, USHORT nTab,
/*N*/                         ScBaseCell* pCell, ULONG nFormatIndex, BOOL bForceTab )
/*N*/ {
/*N*/   if (VALIDTAB(nTab))
/*N*/   {
/*N*/       if ( bForceTab && !pTab[nTab] )
/*N*/       {
/*?*/           BOOL bExtras = !bIsUndo;        // Spaltenbreiten, Zeilenhoehen, Flags
/*?*/
/*?*/           pTab[nTab] = new ScTable(this, nTab,
/*?*/                               String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("temp")),
/*?*/                               bExtras, bExtras);
/*N*/       }
/*N*/
/*N*/       if (pTab[nTab])
/*N*/           pTab[nTab]->PutCell( nCol, nRow, nFormatIndex, pCell );
/*N*/   }
/*N*/ }

/*N*/ void ScDocument::PutCell( const ScAddress& rPos, ScBaseCell* pCell,
/*N*/                           ULONG nFormatIndex, BOOL bForceTab )
/*N*/ {
/*N*/   USHORT nTab = rPos.Tab();
/*N*/   if ( bForceTab && !pTab[nTab] )
/*N*/   {
/*N*/       BOOL bExtras = !bIsUndo;        // Spaltenbreiten, Zeilenhoehen, Flags
/*N*/
/*N*/       pTab[nTab] = new ScTable(this, nTab,
/*N*/                           String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("temp")),
/*N*/                           bExtras, bExtras);
/*N*/   }
/*N*/
/*N*/   if (pTab[nTab])
/*N*/       pTab[nTab]->PutCell( rPos, nFormatIndex, pCell );
/*N*/ }

/*N*/ BOOL ScDocument::GetPrintArea( USHORT nTab, USHORT& rEndCol, USHORT& rEndRow,
/*N*/                               BOOL bNotes ) const
/*N*/ {
/*N*/   if (nTab<=MAXTAB && pTab[nTab])
/*N*/   {
/*N*/       BOOL bAny = pTab[nTab]->GetPrintArea( rEndCol, rEndRow, bNotes );
/*N*/       if (pDrawLayer)
/*N*/       {
/*N*/           ScRange aDrawRange(0,0,nTab, MAXCOL,MAXROW,nTab);
/*N*/           if (DrawGetPrintArea( aDrawRange, TRUE, TRUE ))
/*N*/           {
/*N*/               if (aDrawRange.aEnd.Col()>rEndCol) rEndCol=aDrawRange.aEnd.Col();
/*N*/               if (aDrawRange.aEnd.Row()>rEndRow) rEndRow=aDrawRange.aEnd.Row();
/*N*/               bAny = TRUE;
/*N*/           }
/*N*/       }
/*N*/       return bAny;
/*N*/   }
/*N*/
/*N*/   rEndCol = 0;
/*N*/   rEndRow = 0;
/*N*/   return FALSE;
/*N*/ }

//STRIP001 BOOL ScDocument::GetPrintAreaHor( USHORT nTab, USHORT nStartRow, USHORT nEndRow,
//STRIP001                                      USHORT& rEndCol, BOOL bNotes ) const
//STRIP001 {
//STRIP001  if (nTab<=MAXTAB && pTab[nTab])
//STRIP001  {
//STRIP001      BOOL bAny = pTab[nTab]->GetPrintAreaHor( nStartRow, nEndRow, rEndCol, bNotes );
//STRIP001      if (pDrawLayer)
//STRIP001      {
//STRIP001          ScRange aDrawRange(0,nStartRow,nTab, MAXCOL,nEndRow,nTab);
//STRIP001          if (DrawGetPrintArea( aDrawRange, TRUE, FALSE ))
//STRIP001          {
//STRIP001              if (aDrawRange.aEnd.Col()>rEndCol) rEndCol=aDrawRange.aEnd.Col();
//STRIP001              bAny = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001      return bAny;
//STRIP001  }
//STRIP001
//STRIP001  rEndCol = 0;
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 BOOL ScDocument::GetPrintAreaVer( USHORT nTab, USHORT nStartCol, USHORT nEndCol,
//STRIP001                                      USHORT& rEndRow, BOOL bNotes ) const
//STRIP001 {
//STRIP001  if (nTab<=MAXTAB && pTab[nTab])
//STRIP001  {
//STRIP001      BOOL bAny = pTab[nTab]->GetPrintAreaVer( nStartCol, nEndCol, rEndRow, bNotes );
//STRIP001      if (pDrawLayer)
//STRIP001      {
//STRIP001          ScRange aDrawRange(nStartCol,0,nTab, nEndCol,MAXROW,nTab);
//STRIP001          if (DrawGetPrintArea( aDrawRange, FALSE, TRUE ))
//STRIP001          {
//STRIP001              if (aDrawRange.aEnd.Row()>rEndRow) rEndRow=aDrawRange.aEnd.Row();
//STRIP001              bAny = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001      return bAny;
//STRIP001  }
//STRIP001
//STRIP001  rEndRow = 0;
//STRIP001  return FALSE;
//STRIP001 }

/*N*/ BOOL ScDocument::GetDataStart( USHORT nTab, USHORT& rStartCol, USHORT& rStartRow ) const
/*N*/ {
/*N*/   if (nTab<=MAXTAB && pTab[nTab])
/*N*/   {
/*N*/       BOOL bAny = pTab[nTab]->GetDataStart( rStartCol, rStartRow );
/*N*/       if (pDrawLayer)
/*N*/       {
/*N*/           ScRange aDrawRange(0,0,nTab, MAXCOL,MAXROW,nTab);
/*N*/           if (DrawGetPrintArea( aDrawRange, TRUE, TRUE ))
/*N*/           {
/*N*/               if (aDrawRange.aStart.Col()<rStartCol) rStartCol=aDrawRange.aStart.Col();
/*N*/               if (aDrawRange.aStart.Row()<rStartRow) rStartRow=aDrawRange.aStart.Row();
/*N*/               bAny = TRUE;
/*N*/           }
/*N*/       }
/*N*/       return bAny;
/*N*/   }
/*N*/
/*N*/   rStartCol = 0;
/*N*/   rStartRow = 0;
/*N*/   return FALSE;
/*N*/ }

//STRIP001 BOOL ScDocument::MoveTab( USHORT nOldPos, USHORT nNewPos )
//STRIP001 {
//STRIP001  if (nOldPos == nNewPos) return FALSE;
//STRIP001  BOOL bValid = FALSE;
//STRIP001  if (VALIDTAB(nOldPos))
//STRIP001  {
//STRIP001      if (pTab[nOldPos])
//STRIP001      {
//STRIP001          USHORT nTabCount = GetTableCount();
//STRIP001          if (nTabCount > 1)
//STRIP001          {
//STRIP001              BOOL bOldAutoCalc = GetAutoCalc();
//STRIP001              SetAutoCalc( FALSE );   // Mehrfachberechnungen vermeiden
//STRIP001              SetNoListening( TRUE );
//STRIP001              ScProgress* pProgress = new ScProgress( GetDocumentShell(),
//STRIP001                  ScGlobal::GetRscString(STR_UNDO_MOVE_TAB), GetCodeCount() );
//STRIP001              if (nNewPos == SC_TAB_APPEND)
//STRIP001                  nNewPos = nTabCount-1;
//STRIP001
//STRIP001              //  Referenz-Updaterei
//STRIP001              //! mit UpdateReference zusammenfassen!
//STRIP001
//STRIP001              short nDz = ((short)nNewPos) - (short)nOldPos;
//STRIP001              ScRange aSourceRange( 0,0,nOldPos, MAXCOL,MAXROW,nOldPos );
//STRIP001              pRangeName->UpdateTabRef(nOldPos, 3, nNewPos);
//STRIP001              pDBCollection->UpdateMoveTab( nOldPos, nNewPos );
//STRIP001              xColNameRanges->UpdateReference( URM_REORDER, this, aSourceRange, 0,0,nDz );
//STRIP001              xRowNameRanges->UpdateReference( URM_REORDER, this, aSourceRange, 0,0,nDz );
//STRIP001              if (pPivotCollection)
//STRIP001                  pPivotCollection->UpdateReference( URM_REORDER,
//STRIP001                                  0,0,nOldPos, MAXCOL,MAXROW,nOldPos, 0,0,nDz );
//STRIP001              if (pDPCollection)
//STRIP001                  pDPCollection->UpdateReference( URM_REORDER, aSourceRange, 0,0,nDz );
//STRIP001              if (pDetOpList)
//STRIP001                  pDetOpList->UpdateReference( this, URM_REORDER, aSourceRange, 0,0,nDz );
//STRIP001              UpdateChartRef( URM_REORDER,
//STRIP001                                  0,0,nOldPos, MAXCOL,MAXROW,nOldPos, 0,0,nDz );
//STRIP001              UpdateRefAreaLinks( URM_REORDER, aSourceRange, 0,0,nDz );
//STRIP001              if ( pCondFormList )
//STRIP001                  pCondFormList->UpdateMoveTab( nOldPos, nNewPos );
//STRIP001              if ( pUnoBroadcaster )
//STRIP001                  pUnoBroadcaster->Broadcast( ScUpdateRefHint( URM_REORDER,
//STRIP001                                  aSourceRange, 0,0,nDz ) );
//STRIP001
//STRIP001              ScTable* pSaveTab = pTab[nOldPos];
//STRIP001              USHORT i;
//STRIP001              for (i = nOldPos + 1; i < nTabCount; i++)
//STRIP001                  pTab[i - 1] = pTab[i];
//STRIP001              pTab[i-1] = NULL;
//STRIP001              for (i = nTabCount - 1; i > nNewPos; i--)
//STRIP001                  pTab[i] = pTab[i - 1];
//STRIP001              pTab[nNewPos] = pSaveTab;
//STRIP001              for (i = 0; i <= MAXTAB; i++)
//STRIP001                  if (pTab[i])
//STRIP001                      pTab[i]->UpdateMoveTab( nOldPos, nNewPos, i, *pProgress );
//STRIP001              delete pProgress;   // freimachen fuer evtl. andere
//STRIP001              for (i = 0; i <= MAXTAB; i++)
//STRIP001                  if (pTab[i])
//STRIP001                      pTab[i]->UpdateCompile();
//STRIP001              SetNoListening( FALSE );
//STRIP001              for (i = 0; i <= MAXTAB; i++)
//STRIP001                  if (pTab[i])
//STRIP001                      pTab[i]->StartAllListeners();
//STRIP001              // #81844# sheet names of references may not be valid until sheet is moved
//STRIP001              pChartListenerCollection->UpdateScheduledSeriesRanges();
//STRIP001              SetDirty();
//STRIP001              SetAutoCalc( bOldAutoCalc );
//STRIP001
//STRIP001              if (pDrawLayer)
//STRIP001                  DrawMovePage( nOldPos, nNewPos );
//STRIP001
//STRIP001              bValid = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return bValid;
//STRIP001 }

//STRIP001 BOOL ScDocument::CopyTab( USHORT nOldPos, USHORT nNewPos, const ScMarkData* pOnlyMarked )
//STRIP001 {
//STRIP001  if (SC_TAB_APPEND == nNewPos ) nNewPos = nMaxTableNumber;
//STRIP001  String aName;
//STRIP001  GetName(nOldPos, aName);
//STRIP001
//STRIP001  //  vorneweg testen, ob der Prefix als gueltig erkannt wird
//STRIP001  //  wenn nicht, nur doppelte vermeiden
//STRIP001  BOOL bPrefix = ValidTabName( aName );
//STRIP001  DBG_ASSERT(bPrefix, "ungueltiger Tabellenname");
//STRIP001  USHORT nDummy;
//STRIP001
//STRIP001  CreateValidTabName(aName);
//STRIP001
//STRIP001  BOOL bValid;
//STRIP001  if (bPrefix)
//STRIP001      bValid = ( ValidNewTabName(aName) && (nMaxTableNumber <= MAXTAB) );
//STRIP001  else
//STRIP001      bValid = ( !GetTable( aName, nDummy ) && (nMaxTableNumber <= MAXTAB) );
//STRIP001
//STRIP001  BOOL bOldAutoCalc = GetAutoCalc();
//STRIP001  SetAutoCalc( FALSE );   // Mehrfachberechnungen vermeiden
//STRIP001  if (bValid)
//STRIP001  {
//STRIP001      if (nNewPos == nMaxTableNumber)
//STRIP001      {
//STRIP001          pTab[nMaxTableNumber] = new ScTable(this, nMaxTableNumber, aName);
//STRIP001          ++nMaxTableNumber;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if (VALIDTAB(nNewPos) && (nNewPos < nMaxTableNumber))
//STRIP001          {
//STRIP001              SetNoListening( TRUE );
//STRIP001
//STRIP001              ScRange aRange( 0,0,nNewPos, MAXCOL,MAXROW,MAXTAB );
//STRIP001              xColNameRanges->UpdateReference( URM_INSDEL, this, aRange, 0,0,1 );
//STRIP001              xRowNameRanges->UpdateReference( URM_INSDEL, this, aRange, 0,0,1 );
//STRIP001              pRangeName->UpdateTabRef(nNewPos, 1);
//STRIP001              pDBCollection->UpdateReference(
//STRIP001                                  URM_INSDEL, 0,0,nNewPos, MAXCOL,MAXROW,MAXTAB, 0,0,1 );
//STRIP001              if (pPivotCollection)
//STRIP001                  pPivotCollection->UpdateReference(
//STRIP001                                  URM_INSDEL, 0,0,nNewPos, MAXCOL,MAXROW,MAXTAB, 0,0,1 );
//STRIP001              if (pDPCollection)
//STRIP001                  pDPCollection->UpdateReference( URM_INSDEL, aRange, 0,0,1 );
//STRIP001              if (pDetOpList)
//STRIP001                  pDetOpList->UpdateReference( this, URM_INSDEL, aRange, 0,0,1 );
//STRIP001              UpdateChartRef( URM_INSDEL, 0,0,nNewPos, MAXCOL,MAXROW,MAXTAB, 0,0,1 );
//STRIP001              UpdateRefAreaLinks( URM_INSDEL, aRange, 0,0,1 );
//STRIP001              if ( pUnoBroadcaster )
//STRIP001                  pUnoBroadcaster->Broadcast( ScUpdateRefHint( URM_INSDEL, aRange, 0,0,1 ) );
//STRIP001
//STRIP001              USHORT i;
//STRIP001              for (i = 0; i <= MAXTAB; i++)
//STRIP001                  if (pTab[i] && i != nOldPos)
//STRIP001                      pTab[i]->UpdateInsertTab(nNewPos);
//STRIP001              for (i = nMaxTableNumber; i > nNewPos; i--)
//STRIP001                  pTab[i] = pTab[i - 1];
//STRIP001              if (nNewPos <= nOldPos)
//STRIP001                  nOldPos++;
//STRIP001              pTab[nNewPos] = new ScTable(this, nNewPos, aName);
//STRIP001              ++nMaxTableNumber;
//STRIP001              bValid = TRUE;
//STRIP001              for (i = 0; i <= MAXTAB; i++)
//STRIP001                  if (pTab[i] && i != nOldPos && i != nNewPos)
//STRIP001                      pTab[i]->UpdateCompile();
//STRIP001              SetNoListening( FALSE );
//STRIP001              for (i = 0; i <= MAXTAB; i++)
//STRIP001                  if (pTab[i] && i != nOldPos && i != nNewPos)
//STRIP001                      pTab[i]->StartAllListeners();
//STRIP001
//STRIP001              //  update conditional formats after table is inserted
//STRIP001              if ( pCondFormList )
//STRIP001                  pCondFormList->UpdateReference( URM_INSDEL, aRange, 0,0,1 );
//STRIP001              // #81844# sheet names of references may not be valid until sheet is copied
//STRIP001              pChartListenerCollection->UpdateScheduledSeriesRanges();
//STRIP001          }
//STRIP001          else
//STRIP001              bValid = FALSE;
//STRIP001      }
//STRIP001  }
//STRIP001  if (bValid)
//STRIP001  {
//STRIP001      SetNoListening( TRUE );     // noch nicht bei CopyToTable/Insert
//STRIP001      pTab[nOldPos]->CopyToTable(0, 0, MAXCOL, MAXROW, IDF_ALL, (pOnlyMarked != NULL),
//STRIP001                                      pTab[nNewPos], pOnlyMarked );
//STRIP001      short nDz;
//STRIP001 /*       if (nNewPos < nOldPos)
//STRIP001          nDz = ((short)nNewPos) - (short)nOldPos + 1;
//STRIP001      else
//STRIP001 */           nDz = ((short)nNewPos) - (short)nOldPos;
//STRIP001      pTab[nNewPos]->UpdateReference(URM_COPY, 0, 0, nNewPos , MAXCOL, MAXROW,
//STRIP001                                      nNewPos, 0, 0, nDz, NULL);
//STRIP001
//STRIP001      pTab[nNewPos]->UpdateInsertTabAbs(nNewPos); // alle abs. um eins hoch!!
//STRIP001      pTab[nOldPos]->UpdateInsertTab(nNewPos);
//STRIP001
//STRIP001      pTab[nOldPos]->UpdateCompile();
//STRIP001      pTab[nNewPos]->UpdateCompile( TRUE );   // #67996# maybe already compiled in Clone, but used names need recompilation
//STRIP001      SetNoListening( FALSE );
//STRIP001      pTab[nOldPos]->StartAllListeners();
//STRIP001      pTab[nNewPos]->StartAllListeners();
//STRIP001      SetDirty();
//STRIP001      SetAutoCalc( bOldAutoCalc );
//STRIP001
//STRIP001      if (pDrawLayer)
//STRIP001          DrawCopyPage( nOldPos, nNewPos );
//STRIP001
//STRIP001      pTab[nNewPos]->SetPageStyle( pTab[nOldPos]->GetPageStyle() );
//STRIP001  }
//STRIP001  else
//STRIP001      SetAutoCalc( bOldAutoCalc );
//STRIP001  return bValid;
//STRIP001 }

/*N*/ ULONG ScDocument::TransferTab( ScDocument* pSrcDoc, USHORT nSrcPos,
/*N*/                               USHORT nDestPos, BOOL bInsertNew,
/*N*/                               BOOL bResultsOnly )
/*N*/ {
/*N*/   ULONG nRetVal = 1;                      // 0 => Fehler 1 = ok
/*N*/                                           // 2 => RefBox, 3 => NameBox
/*N*/                                           // 4 => beides
/*N*/   BOOL bValid = TRUE;
/*N*/   if (bInsertNew)             // neu einfuegen
/*N*/   {
/*?*/       String aName;
/*?*/       pSrcDoc->GetName(nSrcPos, aName);
/*?*/       CreateValidTabName(aName);
/*?*/       bValid = InsertTab(nDestPos, aName);
/*N*/   }
/*N*/   else                        // bestehende Tabelle ersetzen
/*N*/   {
/*N*/       if (VALIDTAB(nDestPos) && pTab[nDestPos])
/*N*/       {
/*N*/           pTab[nDestPos]->DeleteArea( 0,0, MAXCOL,MAXROW, IDF_ALL );
/*N*/ //            ClearDrawPage(nDestPos);
/*N*/       }
/*N*/       else
/*N*/           bValid = FALSE;
/*N*/   }
/*N*/
/*N*/   if (bValid)
/*N*/   {
/*N*/       BOOL bOldAutoCalcSrc;
/*N*/       BOOL bOldAutoCalc = GetAutoCalc();
/*N*/       SetAutoCalc( FALSE );   // Mehrfachberechnungen vermeiden
/*N*/       SetNoListening( TRUE );
/*N*/       if ( bResultsOnly )
/*N*/       {
/*N*/           bOldAutoCalcSrc = pSrcDoc->GetAutoCalc();
/*N*/           pSrcDoc->SetAutoCalc( TRUE );   // falls was berechnet werden muss
/*N*/       }
/*N*/       SvNumberFormatter* pThisFormatter = xPoolHelper->GetFormTable();
/*N*/       SvNumberFormatter* pOtherFormatter = pSrcDoc->xPoolHelper->GetFormTable();
/*N*/       if (pOtherFormatter && pOtherFormatter != pThisFormatter)
/*N*/       {
/*N*/           SvULONGTable* pExchangeList =
/*N*/                    pThisFormatter->MergeFormatter(*(pOtherFormatter));
/*N*/           if (pExchangeList->Count() > 0)
/*N*/               pFormatExchangeList = pExchangeList;
/*N*/       }
/*N*/       nDestPos = Min(nDestPos, (USHORT)(GetTableCount() - 1));
/*N*/       pSrcDoc->pTab[nSrcPos]->CopyToTable(0, 0, MAXCOL, MAXROW,
/*N*/           ( bResultsOnly ? IDF_ALL & ~IDF_FORMULA : IDF_ALL),
/*N*/           FALSE, pTab[nDestPos] );
/*N*/       pFormatExchangeList = NULL;
/*N*/       pTab[nDestPos]->SetTabNo(nDestPos);
/*N*/
/*N*/       if ( !bResultsOnly )
/*N*/       {
/*N*/           USHORT nSrcRangeNames = pSrcDoc->pRangeName->GetCount();
/*N*/           // array containing range names which might need update of indices
/*N*/           ScRangeData** pSrcRangeNames = nSrcRangeNames ? new ScRangeData* [nSrcRangeNames] : NULL;
/*N*/           // the index mapping thereof
/*N*/           ScIndexMap aSrcRangeMap( nSrcRangeNames );
/*N*/           BOOL bRangeNameReplace = FALSE;
/*N*/
/*N*/           for (USHORT i = 0; i < nSrcRangeNames; i++)     //! DB-Bereiche Pivot-Bereiche auch !!!
/*N*/           {
/*?*/               ScRangeData* pSrcData = (*pSrcDoc->pRangeName)[i];
/*?*/               USHORT nOldIndex = pSrcData->GetIndex();
/*?*/               BOOL bInUse = FALSE;
/*?*/               for (USHORT j = 0; !bInUse && (j <= MAXTAB); j++)
/*?*/               {
/*?*/                   if (pSrcDoc->pTab[j])
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*?*/                         bInUse = pSrcDoc->pTab[j]->IsRangeNameInUse(0, 0, MAXCOL, MAXROW,
//STRIP001 /*?*/                                                           nOldIndex);
/*?*/               }
/*?*/               if (bInUse)
/*?*/               {
/*?*/               DBG_BF_ASSERT(0, "STRIP"); //STRIP001   ScRangeData* pData = new ScRangeData( *pSrcData );
//STRIP001 /*?*/                    pData->SetDocument(this);
//STRIP001 /*?*/                    if ( pRangeName->FindIndex( pData->GetIndex() ) )
//STRIP001 /*?*/                        pData->SetIndex(0);     // need new index, done in Insert
//STRIP001 /*?*/                    if (!pRangeName->Insert(pData))
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        delete pData;
//STRIP001 /*?*/                        nRetVal += 2;
//STRIP001 /*?*/                        // InfoBox :: Name doppelt
//STRIP001 /*?*/                        pSrcRangeNames[i] = NULL;
//STRIP001 /*?*/                        aSrcRangeMap.SetPair( i, nOldIndex, 0 );
//STRIP001 /*?*/                        bRangeNameReplace = TRUE;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    else
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        pData->TransferTabRef( nSrcPos, nDestPos );
//STRIP001 /*?*/                        pSrcRangeNames[i] = pData;
//STRIP001 /*?*/                        USHORT nNewIndex = pData->GetIndex();
//STRIP001 /*?*/                        aSrcRangeMap.SetPair( i, nOldIndex, nNewIndex );
//STRIP001 /*?*/                        if ( !bRangeNameReplace )
//STRIP001 /*?*/                            bRangeNameReplace = ( nOldIndex != nNewIndex );
//STRIP001 /*?*/                    }
/*?*/               }
/*?*/               else
/*?*/               {
/*?*/                   pSrcRangeNames[i] = NULL;
/*?*/                   //aSrcRangeMap.SetPair( i, 0, 0 );      // not needed, defaulted
/*?*/               }
/*N*/           }
/*N*/           if ( bRangeNameReplace )
/*N*/           {
/*?*/               // first update all inserted named formulas if they contain other
/*?*/               // range names and used indices changed
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 /*?*/                 for (USHORT i = 0; i < nSrcRangeNames; i++)     //! DB-Bereiche Pivot-Bereiche auch
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    if ( pSrcRangeNames[i] )
//STRIP001 /*?*/                        pSrcRangeNames[i]->ReplaceRangeNamesInUse( aSrcRangeMap );
//STRIP001 /*?*/                }
//STRIP001 /*?*/                // then update the formulas, they might need the just updated range names
//STRIP001 /*?*/                pTab[nDestPos]->ReplaceRangeNamesInUse( 0, 0, MAXCOL, MAXROW, aSrcRangeMap );
/*N*/           }
/*N*/           if ( pSrcRangeNames )
/*?*/               delete [] pSrcRangeNames;
/*N*/
/*N*/           short nDz = ((short)nDestPos) - (short)nSrcPos;
/*N*/           pTab[nDestPos]->UpdateReference(URM_COPY, 0, 0, nDestPos,
/*N*/                                                    MAXCOL, MAXROW, nDestPos,
/*N*/                                                    0, 0, nDz, NULL);
/*N*/             // Test for outside absolute references for info box
/*N*/             BOOL bIsAbsRef = pSrcDoc->pTab[nSrcPos]->TestTabRefAbs(nSrcPos);
/*N*/             // Readjust self-contained absolute references to this sheet
/*N*/             pTab[nDestPos]->TestTabRefAbs(nSrcPos);
/*N*/           if (bIsAbsRef)
/*N*/           {
/*N*/               nRetVal += 1;
/*N*/                   // InfoBox AbsoluteRefs sind möglicherweise nicht mehr korrekt!!
/*N*/           }
/*N*/           pTab[nDestPos]->CompileAll();
/*N*/       }
/*N*/
/*N*/       SetNoListening( FALSE );
/*N*/       if ( !bResultsOnly )
/*N*/           pTab[nDestPos]->StartAllListeners();
/*N*/       SetDirty();     // ist das wirklich dokumentweit noetig?!?
/*N*/       if ( bResultsOnly )
/*N*/           pSrcDoc->SetAutoCalc( bOldAutoCalcSrc );
/*N*/       SetAutoCalc( bOldAutoCalc );
/*N*/
/*N*/       //  Drawing kopieren
/*N*/
/*N*/       if (bInsertNew)
/*?*/           TransferDrawPage( pSrcDoc, nSrcPos, nDestPos );
/*N*/   }
/*N*/   if (!bValid)
/*N*/       nRetVal = 0;
/*N*/   return nRetVal;
/*N*/ }

//  ----------------------------------------------------------------------------

/*N*/ void ScDocument::SetError( USHORT nCol, USHORT nRow, USHORT nTab, const USHORT nError)
/*N*/ {
/*N*/   if (VALIDTAB(nTab))
/*N*/       if (pTab[nTab])
/*N*/           pTab[nTab]->SetError( nCol, nRow, nError );
/*N*/ }

//STRIP001 void ScDocument::EraseNonUsedSharedNames(USHORT nLevel)
//STRIP001 {
//STRIP001  for (USHORT i = 0; i < pRangeName->GetCount(); i++)
//STRIP001  {
//STRIP001      ScRangeData* pRangeData = (*pRangeName)[i];
//STRIP001      if (pRangeData && pRangeData->HasType(RT_SHARED))
//STRIP001      {
//STRIP001          String aName;
//STRIP001          pRangeData->GetName(aName);
//STRIP001          aName.Erase(0, 6);                      // !!! vgl. Table4, FillFormula !!
//STRIP001          USHORT nInd = (USHORT) aName.ToInt32();
//STRIP001          if (nInd <= nLevel)
//STRIP001          {
//STRIP001              USHORT nIndex = pRangeData->GetIndex();
//STRIP001              BOOL bInUse = FALSE;
//STRIP001              for (USHORT j = 0; !bInUse && (j <= MAXTAB); j++)
//STRIP001              {
//STRIP001                  if (pTab[j])
//STRIP001                      bInUse = pTab[j]->IsRangeNameInUse(0, 0, MAXCOL-1, MAXROW-1,
//STRIP001                                                         nIndex);
//STRIP001              }
//STRIP001              if (!bInUse)
//STRIP001                  pRangeName->AtFree(i);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//  ----------------------------------------------------------------------------

/*N*/ void ScDocument::SetConsolidateDlgData( const ScConsolidateParam* pData )
/*N*/ {
/*N*/   delete pConsolidateDlgData;
/*N*/
/*N*/   if ( pData )
/*N*/       pConsolidateDlgData = new ScConsolidateParam( *pData );
/*N*/   else
/*N*/       pConsolidateDlgData = NULL;
/*N*/ }

/*N*/ void ScDocument::SetChangeViewSettings(const ScChangeViewSettings& rNew)
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001   if (pChangeViewSettings==NULL)
//STRIP001      pChangeViewSettings = new ScChangeViewSettings;
//STRIP001
//STRIP001  DBG_ASSERT( pChangeViewSettings, "Oops. No ChangeViewSettings :-( by!" );
//STRIP001
//STRIP001  *pChangeViewSettings=rNew;
/*N*/ }

//  ----------------------------------------------------------------------------

/*N*/ ScFieldEditEngine* ScDocument::CreateFieldEditEngine()
/*N*/ {
/*N*/   ScFieldEditEngine* pEditEngine = NULL;
/*N*/   if (!pCacheFieldEditEngine)
/*N*/   {
/*N*/       pEditEngine = new ScFieldEditEngine( GetEnginePool(),
/*N*/           GetEditPool(), FALSE );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       pEditEngine = pCacheFieldEditEngine;
/*N*/       pCacheFieldEditEngine = NULL;
/*N*/   }
/*N*/   return pEditEngine;
/*N*/ }

/*N*/ void ScDocument::DisposeFieldEditEngine(ScFieldEditEngine*& rpEditEngine)
/*N*/ {
/*N*/   if (!pCacheFieldEditEngine && rpEditEngine)
/*N*/   {
/*N*/       pCacheFieldEditEngine = rpEditEngine;
/*N*/       pCacheFieldEditEngine->Clear();
/*N*/   }
/*N*/   else
/*N*/       delete rpEditEngine;
/*N*/   rpEditEngine = NULL;
/*N*/ }

} //namespace binfilter
