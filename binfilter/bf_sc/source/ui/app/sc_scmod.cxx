/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_scmod.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 17:02:13 $
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

#ifndef _COM_SUN_STAR_UI_DIALOGS_XEXECUTABLEDIALOG_HPP_
#include <com/sun/star/ui/dialogs/XExecutableDialog.hpp>
#endif
#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif

// INCLUDE ---------------------------------------------------------------

#include "scitems.hxx"

#include <bf_svx/eeitem.hxx>
#define ITEMID_FIELD EE_FEATURE_FIELD

#ifndef _PSTM_HXX
#include <tools/pstm.hxx>
#endif

#ifndef _SFXPOOLITEM_HXX
#include <svtools/poolitem.hxx>
#endif

#ifndef _SVX_ITEMDATA_HXX
#include <bf_svx/itemdata.hxx>
#endif

#ifndef _DATE_HXX
#include <tools/date.hxx>
#endif

#ifndef _TOOLS_TIME_HXX
#include <tools/time.hxx>
#endif

#include <bf_svx/flditem.hxx>
#include <bf_svx/outliner.hxx>
#include <basic/sbstar.hxx>

#include <bf_offmgr/hyprlink.hxx>
#include <bf_offmgr/osplcfg.hxx>
#ifndef _OFFAPP_INTERNATIONALOPTIONS_HXX_
#include <bf_offmgr/internationaloptions.hxx>
#endif
#include <svtools/ehdl.hxx>
#include <svtools/accessibilityoptions.hxx>
#include <svtools/ctloptions.hxx>
#include <vcl/status.hxx>
#include <bf_sfx2/bindings.hxx>
#include <bf_sfx2/request.hxx>
#include <bf_sfx2/macrconf.hxx>
#include <bf_sfx2/printer.hxx>
#include <bf_svx/langitem.hxx>
#include <svtools/colorcfg.hxx>

#include <svtools/whiter.hxx>
#include <bf_offmgr/app.hxx>
#include <bf_svx/selctrl.hxx>
#include <bf_svx/insctrl.hxx>
#include <bf_svx/zoomctrl.hxx>
#include <bf_svx/modctrl.hxx>
#include <bf_svx/pszctrl.hxx>
#include <vcl/msgbox.hxx>
#include <bf_offmgr/ofaids.hrc>
#include <svtools/inethist.hxx>
#include <vcl/waitobj.hxx>

#define ITEMID_SPELLCHECK 0

#include "scmod.hxx"
#include "global.hxx"
#include "viewopti.hxx"
#include "docoptio.hxx"
#include "appoptio.hxx"
#include "inputopt.hxx"
#include "printopt.hxx"
#include "navicfg.hxx"
#include "tabvwsh.hxx"
#include "prevwsh.hxx"
#include "docsh.hxx"
#include "drwlayer.hxx"
#include "uiitems.hxx"
#include "bf_sc.hrc"
#include "cfgids.hxx"
#include "inputhdl.hxx"
#include "inputwin.hxx"

#ifndef _SFX_SRCHITEM_HXX
#include <bf_sfx2/srchitem.hxx>
#endif

#include "msgpool.hxx"
#include "scresid.hxx"
#include "teamdlg.hxx"
#include "dwfunctr.hxx"
#include "formdata.hxx"
#include "tpusrlst.hxx"
#include "tpcalc.hxx"
#include "tpprint.hxx"
#include "transobj.hxx"
#include "detfunc.hxx"
#include "preview.hxx"

#define ScModule
//STRIP008 #include "scslots.hxx"
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
#define SC_IDLE_MIN     150
#define SC_IDLE_MAX     3000
#define SC_IDLE_STEP    75
#define SC_IDLE_COUNT   50
namespace binfilter {
#include "scslots.hxx"

static USHORT nIdleCount = 0;

//------------------------------------------------------------------

/*N*/ SFX_IMPL_INTERFACE( ScModule, SfxShell, ScResId(RID_APPTITLE) )
/*N*/ {
/*N*/   SFX_OBJECTBAR_REGISTRATION( SFX_OBJECTBAR_APPLICATION | SFX_VISIBILITY_DESKTOP | SFX_VISIBILITY_STANDARD | SFX_VISIBILITY_CLIENT | SFX_VISIBILITY_VIEWER,
/*N*/                               ScResId(RID_OBJECTBAR_APP) );
/*N*/   SFX_STATUSBAR_REGISTRATION( ScResId(SCCFG_STATUSBAR) );     // nur ID wichtig
/*N*/   SFX_CHILDWINDOW_REGISTRATION( SvxHyperlinkDlgWrapper::GetChildWindowId() );
/*N*/ }

//------------------------------------------------------------------

/*N*/ ScModule::ScModule( SfxObjectFactory* pFact ) :
/*N*/   ScModuleDummy( SFX_APP()->CreateResManager( "bf_sc" ), FALSE, pFact ), //STRIP005
/*N*/   bIsWaterCan( FALSE ),
/*N*/   bIsInEditCommand( FALSE ),
/*N*/   pSelTransfer( NULL ),
/*N*/   pRefInputHandler( NULL ),
/*N*/   pViewCfg( NULL ),
/*N*/   pDocCfg( NULL ),
/*N*/   pAppCfg( NULL ),
/*N*/   pInputCfg( NULL ),
/*N*/   pPrintCfg( NULL ),
/*N*/   pNavipiCfg( NULL ),
/*N*/   pColorConfig( NULL ),
/*N*/   pAccessOptions( NULL ),
/*N*/   pCTLOptions( NULL ),
/*N*/   pTeamDlg( NULL ),
/*N*/   nCurRefDlgId( 0 ),
/*N*/   pErrorHdl( NULL ),
/*N*/   pSvxErrorHdl( NULL ),
/*N*/   pMessagePool( NULL ),
/*N*/   pFormEditData( NULL )
/*N*/ {
/*N*/   //  im ctor ist der ResManager (DLL-Daten) noch nicht initialisiert!
/*N*/
/*N*/   SetName(String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("StarCalc")));       // fuer Basic
/*N*/
/*N*/   ResetDragObject();
/*N*/   SetClipObject( NULL, NULL );
/*N*/
/*N*/   //  InputHandler braucht nicht mehr angelegt zu werden
/*N*/
/*N*/   //  ErrorHandler anlegen - war in Init()
/*N*/   //  zwischen OfficeApplication::Init und ScGlobal::Init
/*N*/ //    pSvxErrorHdl = new SvxErrorHandler();
/*N*/   pErrorHdl    = new SfxErrorHandler( RID_ERRHDLSC,
/*N*/                                       ERRCODE_AREA_SC,
/*N*/                                       ERRCODE_AREA_APP2-1,
/*N*/                                       GetResMgr() );
/*N*/
/*N*/   aSpellTimer.SetTimeout(10);
/*N*/   aSpellTimer.SetTimeoutHdl( LINK( this, ScModule, SpellTimerHdl ) );
/*N*/   aIdleTimer.SetTimeout(SC_IDLE_MIN);
/*N*/   aIdleTimer.SetTimeoutHdl( LINK( this, ScModule, IdleHandler ) );
/*N*/   aIdleTimer.Start();
/*N*/
/*N*/   pMessagePool = new ScMessagePool;
/*N*/   pMessagePool->FreezeIdRanges();
/*N*/   SetPool( pMessagePool );
/*N*/   ScGlobal::InitTextHeight( pMessagePool );
/*N*/
/*N*/   StartListening( *SFX_APP() );       // for SFX_HINT_DEINITIALIZING
/*N*/ }

/*N*/ ScModule::~ScModule()
/*N*/ {
/*N*/   DBG_ASSERT( !pSelTransfer, "Selection Transfer object not deleted" );
/*N*/
/*N*/   //  InputHandler braucht nicht mehr geloescht zu werden (gibt keinen an der App mehr)
/*N*/
/*N*/   DELETEZ( pMessagePool );
/*N*/
/*N*/   DELETEZ( pFormEditData );
/*N*/
/*N*/   delete pErrorHdl;
/*N*/ //    delete pSvxErrorHdl;
/*N*/
/*N*/   ScGlobal::Clear();      // ruft auch ScDocumentPool::DeleteVersionMaps();
/*N*/
/*N*/   DeleteCfg();            // wurde mal aus Exit() gerufen
/*N*/ }

//------------------------------------------------------------------

/*N*/ void ScModule::Notify( SfxBroadcaster& rBC, const SfxHint& rHint )
/*N*/ {
/*N*/   if ( rHint.ISA(SfxSimpleHint) )
/*N*/   {
/*N*/         ULONG nHintId = ((SfxSimpleHint&)rHint).GetId();
/*N*/         if ( nHintId == SFX_HINT_DEINITIALIZING )
/*N*/       {
/*N*/           //  ConfigItems must be removed before ConfigManager
/*N*/           DeleteCfg();
/*N*/       }
/*N*/       else if ( nHintId == SFX_HINT_COLORS_CHANGED || nHintId == SFX_HINT_ACCESSIBILITY_CHANGED )
/*N*/       {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001   if ( ScDetectiveFunc::IsColorsInitialized() )
/*N*/       }
/*N*/         else if ( nHintId == SFX_HINT_CTL_SETTINGS_CHANGED )
/*N*/         {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/         }
/*N*/   }
/*N*/ }

//------------------------------------------------------------------

/*N*/ void ScModule::DeleteCfg()
/*N*/ {
/*N*/   DELETEZ( pViewCfg ); // Speichern passiert vor Exit() automatisch
/*N*/   DELETEZ( pDocCfg );
/*N*/   DELETEZ( pAppCfg );
/*N*/   DELETEZ( pInputCfg );
/*N*/   DELETEZ( pPrintCfg );
/*N*/   DELETEZ( pNavipiCfg );
/*N*/
/*N*/   if ( pColorConfig )
/*N*/   {
/*N*/       EndListening(*pColorConfig);
/*N*/       DELETEZ( pColorConfig );
/*N*/   }
/*N*/   if ( pAccessOptions )
/*N*/   {
/*N*/       EndListening(*pAccessOptions);
/*N*/       DELETEZ( pAccessOptions );
/*N*/   }
/*N*/   if ( pCTLOptions )
/*N*/   {
/*N*/       EndListening(*pCTLOptions);
/*N*/       DELETEZ( pCTLOptions );
/*N*/   }
/*N*/ }

//------------------------------------------------------------------

/*N*/ SfxModule* ScModule::Load()
/*N*/ {
/*N*/   return this;                    // ist schon geladen
/*N*/ }

/*N*/ SfxModule* ScModuleDummy::Load()
/*N*/ {
/*N*/   return NULL;                    // Dummy zum Linken der DLL, wird nicht gerufen
/*N*/ }

//------------------------------------------------------------------

#define TEXT_WIDTH(s)   rStatusBar.GetTextWidth((s))

/*N*/ void ScModule::FillStatusBar(StatusBar& rStatusBar)
/*N*/ {
/*N*/   // Dokumentposition (Tabelle x / y)
/*N*/   rStatusBar.InsertItem( SID_STATUS_DOCPOS,
/*N*/                           TEXT_WIDTH( String().Fill( 10, 'X' ) ),
/*N*/                           SIB_LEFT|SIB_AUTOSIZE );
/*N*/   rStatusBar.SetHelpId( SID_STATUS_DOCPOS, SID_STATUS_DOCPOS );
/*N*/
/*N*/   // Seitenvorlage
/*N*/   rStatusBar.InsertItem( SID_STATUS_PAGESTYLE,
/*N*/                           TEXT_WIDTH( String().Fill( 15, 'X' ) ),
/*N*/                           SIB_LEFT|SIB_AUTOSIZE );
/*N*/   rStatusBar.SetHelpId( SID_STATUS_PAGESTYLE, SID_STATUS_PAGESTYLE );
/*N*/
/*N*/   // Ma"sstab
/*N*/   rStatusBar.InsertItem( SID_ATTR_ZOOM,
/*N*/                           SvxZoomStatusBarControl::GetDefItemWidth(rStatusBar),
/*N*/                           SIB_CENTER );
/*N*/   rStatusBar.SetHelpId( SID_ATTR_ZOOM, SID_ATTR_ZOOM );
/*N*/
/*N*/   // Einfuege-/Ueberschreibmodus
/*N*/   rStatusBar.InsertItem( SID_ATTR_INSERT,
/*N*/                           SvxInsertStatusBarControl::GetDefItemWidth(rStatusBar),
/*N*/                           SIB_CENTER );
/*N*/   rStatusBar.SetHelpId( SID_ATTR_INSERT, SID_ATTR_INSERT );
/*N*/
/*N*/   // Selektionsmodus
/*N*/   rStatusBar.InsertItem( SID_STATUS_SELMODE,
/*N*/                           SvxSelectionModeControl::GetDefItemWidth(rStatusBar),
/*N*/                           SIB_CENTER );
/*N*/   rStatusBar.SetHelpId( SID_STATUS_SELMODE, SID_STATUS_SELMODE );
/*N*/
/*N*/   // Dokument geaendert
/*N*/   rStatusBar.InsertItem( SID_DOC_MODIFIED,
/*N*/                           SvxModifyControl::GetDefItemWidth(rStatusBar));
/*N*/
/*N*/   rStatusBar.SetHelpId( SID_DOC_MODIFIED, SID_DOC_MODIFIED );
/*N*/
/*N*/   // den aktuellen Kontext anzeigen Uhrzeit / FramePos / TabellenInfo / Errors
/*N*/   rStatusBar.InsertItem( SID_ATTR_SIZE,
/*N*/                           SvxPosSizeStatusBarControl::GetDefItemWidth(rStatusBar),
/*N*/                           SIB_AUTOSIZE|SIB_LEFT|SIB_USERDRAW);
/*N*/   rStatusBar.SetHelpId( SID_ATTR_SIZE, SID_ATTR_SIZE );
/*N*/ }

#undef TEXT_WIDTH

//------------------------------------------------------------------
//
//      von der Applikation verschoben:
//
//------------------------------------------------------------------


/*N*/ void ScModule::GetState( SfxItemSet& rSet )
/*N*/ {
/*N*/   SfxWhichIter aIter(rSet);
/*N*/   USHORT nWhich = aIter.FirstWhich();
/*N*/   while ( nWhich )
/*N*/   {
/*N*/       switch ( nWhich )
/*N*/       {
/*?*/           case FID_AUTOCOMPLETE:
/*?*/               rSet.Put( SfxBoolItem( nWhich, GetAppOptions().GetAutoComplete() ) );
/*?*/               break;
/*?*/           case SID_DETECTIVE_AUTO:
/*?*/               rSet.Put( SfxBoolItem( nWhich, GetAppOptions().GetDetectiveAuto() ) );
/*?*/               break;
/*N*/           case SID_PSZ_FUNCTION:
/*N*/               rSet.Put( SfxUInt16Item( nWhich, GetAppOptions().GetStatusFunc() ) );
/*N*/               break;
/*?*/           case SID_ATTR_METRIC:
/*?*/               rSet.Put( SfxUInt16Item( nWhich, GetAppOptions().GetAppMetric() ) );
/*?*/               break;
/*N*/           case SID_AUTOSPELL_CHECK:
/*N*/               {
/*N*/                   BOOL bAuto;
/*N*/                   ScDocShell* pDocSh = PTR_CAST(ScDocShell, SfxObjectShell::Current());
/*N*/                   if ( pDocSh )
/*?*/                       bAuto = pDocSh->GetDocument()->GetDocOptions().IsAutoSpell();
/*N*/                   else
/*N*/                   {
/*N*/                       USHORT nDummyLang, nDummyCjk, nDummyCtl;
/*N*/                       BOOL bDummy;
/*N*/                       GetSpellSettings( nDummyLang, nDummyCjk, nDummyCtl, bAuto, bDummy );
/*N*/                   }
/*N*/                   rSet.Put( SfxBoolItem( nWhich, bAuto ) );
/*N*/               }
/*N*/               break;
/*?*/           case SID_AUTOSPELL_MARKOFF:
/*?*/               {
/*?*/                   BOOL bHide;
/*?*/                   ScTabViewShell* pViewSh = PTR_CAST(ScTabViewShell, SfxViewShell::Current());
/*?*/                   ScDocShell* pDocSh = PTR_CAST(ScDocShell, SfxObjectShell::Current());
/*?*/                   if ( pViewSh )
/*?*/                       bHide = pViewSh->GetViewData()->GetOptions().IsHideAutoSpell();
/*?*/                   else if ( pDocSh )
/*?*/                       bHide = pDocSh->GetDocument()->GetViewOptions().IsHideAutoSpell();
/*?*/                   else
/*?*/                   {
/*?*/                       USHORT nDummyLang, nDummyCjk, nDummyCtl;
/*?*/                       BOOL bDummy;
/*?*/                       GetSpellSettings( nDummyLang, nDummyCjk, nDummyCtl, bDummy, bHide );
/*?*/                   }
/*?*/                   rSet.Put( SfxBoolItem( nWhich, bHide ) );
/*?*/               }
/*?*/               break;
/*?*/           case SID_ATTR_LANGUAGE:
/*?*/           case ATTR_CJK_FONT_LANGUAGE:        // WID for SID_ATTR_CHAR_CJK_LANGUAGE
/*?*/           case ATTR_CTL_FONT_LANGUAGE:        // WID for SID_ATTR_CHAR_CTL_LANGUAGE
/*?*/               {
/*?*/                   ScDocShell* pDocSh = PTR_CAST(ScDocShell, SfxObjectShell::Current());
/*?*/                   ScDocument* pDoc = pDocSh ? pDocSh->GetDocument() : NULL;
/*?*/                   if ( pDoc )
/*?*/                   {
/*?*/                       LanguageType eLatin, eCjk, eCtl;
/*?*/                       pDoc->GetLanguage( eLatin, eCjk, eCtl );
/*?*/                       LanguageType eLang = ( nWhich == ATTR_CJK_FONT_LANGUAGE ) ? eCjk :
/*?*/                                           ( ( nWhich == ATTR_CTL_FONT_LANGUAGE ) ? eCtl : eLatin );
/*?*/                       rSet.Put( SvxLanguageItem( eLang, nWhich ) );
/*?*/                   }
/*?*/               }
/*?*/               break;
/*?*/
/*N*/       }
/*N*/       nWhich = aIter.NextWhich();
/*N*/   }
/*N*/ }


//------------------------------------------------------------------

/*N*/ void ScModule::ResetDragObject()
/*N*/ {
/*N*/   aDragData.pCellTransfer = NULL;
/*N*/   aDragData.pDrawTransfer = NULL;
/*N*/
/*N*/   aDragData.aLinkDoc.Erase();
/*N*/   aDragData.aLinkTable.Erase();
/*N*/   aDragData.aLinkArea.Erase();
/*N*/   aDragData.pJumpLocalDoc = NULL;
/*N*/   aDragData.aJumpTarget.Erase();
/*N*/   aDragData.aJumpText.Erase();
/*N*/ }




//------------------------------------------------------------------

/*N*/ void ScModule::SetClipObject( ScTransferObj* pCellObj, ScDrawTransferObj* pDrawObj )
/*N*/ {
/*N*/   DBG_ASSERT( !pCellObj || !pDrawObj, "SetClipObject: not allowed to set both objects" );
/*N*/
/*N*/   aClipData.pCellClipboard = pCellObj;
/*N*/   aClipData.pDrawClipboard = pDrawObj;
/*N*/ }

/*N*/ ScDocument* ScModule::GetClipDoc()
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //STRIP001    //  called from document
/*N*/   return NULL;
/*N*/ }


/*N*/ const ScViewOptions& ScModule::GetViewOptions()
/*N*/ {
/*N*/   if ( !pViewCfg )
/*N*/       pViewCfg = new ScViewCfg;
/*N*/
/*N*/   return *pViewCfg;
/*N*/ }


/*N*/ const ScDocOptions& ScModule::GetDocOptions()
/*N*/ {
/*N*/   if ( !pDocCfg )
/*N*/       pDocCfg = new ScDocCfg;
/*N*/
/*N*/   return *pDocCfg;
/*N*/ }

#ifndef LRU_MAX
#define LRU_MAX 10
#endif


/*N*/ void ScModule::RecentFunctionsChanged()
/*N*/ {
/*N*/   //  update function list window
/*N*/   USHORT nFuncListID = ScFunctionChildWindow::GetChildWindowId();
/*N*/
/*N*/   //! notify all views
/*N*/   SfxViewFrame* pViewFrm = SfxViewFrame::Current();
/*N*/   if ( pViewFrm && pViewFrm->HasChildWindow(nFuncListID) )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ScFunctionChildWindow* pWnd =(ScFunctionChildWindow*)pViewFrm->GetChildWindow( nFuncListID );
/*?*/
/*N*/   }
/*N*/ }

/*N*/ void ScModule::SetAppOptions( const ScAppOptions& rOpt )
/*N*/ {
/*N*/   if ( !pAppCfg )
/*N*/       pAppCfg = new ScAppCfg;
/*N*/
/*N*/   pAppCfg->SetOptions( rOpt );
/*N*/ }

/*N*/ void global_InitAppOptions()
/*N*/ {
/*N*/   SC_MOD()->GetAppOptions();
/*N*/ }

/*N*/ const ScAppOptions& ScModule::GetAppOptions()
/*N*/ {
/*N*/   if ( !pAppCfg )
/*N*/       pAppCfg = new ScAppCfg;
/*N*/
/*N*/   return *pAppCfg;
/*N*/ }

/*N*/ void ScModule::SetInputOptions( const ScInputOptions& rOpt )
/*N*/ {
/*N*/   if ( !pInputCfg )
/*N*/       pInputCfg = new ScInputCfg;
/*N*/
/*N*/   pInputCfg->SetOptions( rOpt );
/*N*/ }

/*N*/ const ScInputOptions& ScModule::GetInputOptions()
/*N*/ {
/*N*/   if ( !pInputCfg )
/*N*/       pInputCfg = new ScInputCfg;
/*N*/
/*N*/   return *pInputCfg;
/*N*/ }

/*N*/ void ScModule::SetPrintOptions( const ScPrintOptions& rOpt )
/*N*/ {
/*N*/   if ( !pPrintCfg )
/*N*/       pPrintCfg = new ScPrintCfg;
/*N*/
/*N*/   pPrintCfg->SetOptions( rOpt );
/*N*/ }

/*N*/ const ScPrintOptions& ScModule::GetPrintOptions()
/*N*/ {
/*N*/   if ( !pPrintCfg )
/*N*/       pPrintCfg = new ScPrintCfg;
/*N*/
/*N*/   return *pPrintCfg;
/*N*/ }

/*N*/ svtools::ColorConfig& ScModule::GetColorConfig()
/*N*/ {
/*N*/   if ( !pColorConfig )
/*N*/   {
/*N*/         pColorConfig = new svtools::ColorConfig;
/*N*/       StartListening(*pColorConfig);
/*N*/   }
/*N*/
/*N*/   return *pColorConfig;
/*N*/ }

/*N*/ SvtAccessibilityOptions& ScModule::GetAccessOptions()
/*N*/ {
/*N*/   if ( !pAccessOptions )
/*N*/   {
/*N*/       pAccessOptions = new SvtAccessibilityOptions;
/*N*/       StartListening(*pAccessOptions);
/*N*/   }
/*N*/
/*N*/   return *pAccessOptions;
/*N*/ }

/*N*/ SvtCTLOptions& ScModule::GetCTLOptions()
/*N*/ {
/*N*/   if ( !pCTLOptions )
/*N*/   {
/*N*/       pCTLOptions = new SvtCTLOptions;
/*N*/       StartListening(*pCTLOptions);
/*N*/   }
/*N*/
/*N*/   return *pCTLOptions;
/*N*/ }

/*N*/ USHORT ScModule::GetOptDigitLanguage()
/*N*/ {
/*N*/   SvtCTLOptions::TextNumerals eNumerals = GetCTLOptions().GetCTLTextNumerals();
/*N*/   return ( eNumerals == SvtCTLOptions::NUMERALS_ARABIC ) ? LANGUAGE_ENGLISH_US :
/*N*/          ( eNumerals == SvtCTLOptions::NUMERALS_HINDI)   ? LANGUAGE_ARABIC :
/*N*/                                                            LANGUAGE_SYSTEM;
/*N*/ }


#define IS_AVAILABLE(w,item) (SFX_ITEM_SET==rOptSet.GetItemState((w),TRUE,&item))


#undef IS_AVAILABLE

//------------------------------------------------------------------
//
//                      Input-Handler
//
//------------------------------------------------------------------

/*N*/ ScInputHandler* ScModule::GetInputHdl( ScTabViewShell* pViewSh, BOOL bUseRef )
/*N*/ {
/*N*/   if ( pRefInputHandler && bUseRef )
/*N*/       return pRefInputHandler;
/*N*/
/*N*/   ScInputHandler* pHdl = NULL;
/*N*/   if ( !pViewSh )
/*N*/       pViewSh = PTR_CAST( ScTabViewShell, SfxViewShell::Current() );
/*N*/   if ( pViewSh )
/*N*/       pHdl = pViewSh->GetInputHandler();      // Viewshell hat jetzt immer einen
/*N*/
/*N*/   //  #57989# wenn keine ViewShell uebergeben oder aktiv, kann NULL herauskommen
/*N*/   DBG_ASSERT( pHdl || !pViewSh, "GetInputHdl: kein InputHandler gefunden" );
/*N*/   return pHdl;
/*N*/ }

/*N*/ void ScModule::InputEnterHandler( BYTE nBlockMode )
/*N*/ {
/*N*/   if ( !SFX_APP()->IsDowning() )                                  // nicht beim Programmende
/*N*/   {
/*N*/       ScInputHandler* pHdl = GetInputHdl();
/*N*/       if (pHdl)
/*?*/           pHdl->EnterHandler( nBlockMode );
/*N*/   }
/*N*/ }





/*N*/ void ScModule::ViewShellGone( ScTabViewShell* pViewSh )
/*N*/ {
/*N*/   ScInputHandler* pHdl = GetInputHdl();
/*N*/   if (pHdl)
/*?*/       pHdl->ViewShellGone( pViewSh );
/*N*/
/*N*/   //  Team dialog is opened with the window from a view as parent
/*N*/   //  -> close it if any view is closed
/*N*/   if (pTeamDlg)
/*?*/       pTeamDlg->Close();          // resets variable pTeamDlg
/*N*/ }


/*N*/ ScInputHandler* ScModule::GetRefInputHdl()
/*N*/ {
/*N*/   return pRefInputHandler;
/*N*/ }

/*N*/ BOOL ScModule::IsFormulaMode()
/*N*/ {
/*N*/   //! move reference dialog handling to view
/*N*/   //! (only keep function autopilot here for references to other documents)
/*N*/
/*N*/   BOOL bIsFormula = FALSE;
/*N*/
/*N*/   if ( nCurRefDlgId )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SfxChildWindow* pChildWnd = lcl_GetChildWinFromAnyView( nCurRefDlgId );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       ScInputHandler* pHdl = GetInputHdl();
/*N*/       if ( pHdl )
/*?*/           bIsFormula = pHdl->IsFormulaMode();
/*N*/   }
/*N*/
/*N*/   if (bIsInEditCommand)
/*N*/       bIsFormula = TRUE;
/*N*/
/*N*/   return bIsFormula;
/*N*/ }





//------------------------------------------------------------------
//
//                  Idle / Online-Spelling
//
//------------------------------------------------------------------

/*N*/ void ScModule::AnythingChanged()
/*N*/ {
/*N*/   ULONG nOldTime = aIdleTimer.GetTimeout();
/*N*/   if ( nOldTime != SC_IDLE_MIN )
/*N*/       aIdleTimer.SetTimeout( SC_IDLE_MIN );
/*N*/
/*N*/   nIdleCount = 0;
/*N*/ }

/*N*/ IMPL_LINK( ScModule, IdleHandler, Timer*, pTimer )
/*N*/ {
/*N*/   if ( Application::AnyInput( INPUT_MOUSEANDKEYBOARD ) )
/*N*/   {
/*N*/       aIdleTimer.Start();         // Timeout unveraendert
/*N*/       return 0;
/*N*/   }
/*N*/
/*N*/   BOOL bMore = FALSE;
/*N*/   ScDocShell* pDocSh = PTR_CAST( ScDocShell, SfxObjectShell::Current() );
/*N*/   if ( pDocSh )
/*N*/   {
/*?*/       ScDocument* pDoc = pDocSh->GetDocument();
/*?*/       if ( pDoc->IsLoadingDone() )
/*?*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 BOOL bLinks = pDoc->IdleCheckLinks();
/*?*/       }
/*N*/   }
/*N*/
/*N*/   ULONG nOldTime = aIdleTimer.GetTimeout();
/*N*/   ULONG nNewTime = nOldTime;
/*N*/   if ( bMore )
/*N*/   {
/*?*/       nNewTime = SC_IDLE_MIN;
/*?*/       nIdleCount = 0;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       //  SC_IDLE_COUNT mal mit initialem Timeout, dann hochzaehlen
/*N*/
/*N*/       if ( nIdleCount < SC_IDLE_COUNT )
/*N*/           ++nIdleCount;
/*N*/       else
/*N*/       {
/*N*/           nNewTime += SC_IDLE_STEP;
/*N*/           if ( nNewTime > SC_IDLE_MAX )
/*N*/               nNewTime = SC_IDLE_MAX;
/*N*/       }
/*N*/   }
/*N*/   if ( nNewTime != nOldTime )
/*N*/       aIdleTimer.SetTimeout( nNewTime );
/*N*/
/*N*/   aIdleTimer.Start();
/*N*/   return 0;
/*N*/ }

IMPL_LINK( ScModule, SpellTimerHdl, Timer*, pTimer )
{
    DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //STRIP001    if ( Application::AnyInput( INPUT_KEYBOARD ) )
    return 0;
}

    //virtuelle Methoden fuer den Optionendialog



//------------------------------------------------------------------

/*N*/ IMPL_LINK( ScModule, CalcFieldValueHdl, EditFieldInfo*, pInfo )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //STRIP001    if (pInfo)
/*N*/   return 0;
/*N*/ }




}
