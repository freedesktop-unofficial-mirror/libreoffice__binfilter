/*************************************************************************
 *
 *  $RCSfile: sc_scmod.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:18:14 $
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

#ifndef _COM_SUN_STAR_UI_DIALOGS_XEXECUTABLEDIALOG_HPP_
#include <com/sun/star/ui/dialogs/XExecutableDialog.hpp>
#endif
#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif

#ifdef PCH
#include "ui_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------

#include "scitems.hxx"

#include <bf_svx/eeitem.hxx>
#define ITEMID_FIELD EE_FEATURE_FIELD
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
#include "msgpool.hxx"
#include "scresid.hxx"
#include "anyrefdg.hxx"
#include "teamdlg.hxx"
#include "dwfunctr.hxx"
#include "formdata.hxx"
#include "tpview.hxx"
#include "tpusrlst.hxx"
#include "tpcalc.hxx"
#include "tpprint.hxx"
#include "opredlin.hxx"
#include "transobj.hxx"
#include "detfunc.hxx"
#include "preview.hxx"

#define ScModule
#include "scslots.hxx"
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
#define SC_IDLE_MIN     150
#define SC_IDLE_MAX     3000
#define SC_IDLE_STEP    75
#define SC_IDLE_COUNT   50

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
//STRIP001 /*?*/            //  Test if detective objects have to be updated with new colors
//STRIP001 /*?*/            //  (if the detective colors haven't been used yet, there's nothing to update)
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001  if ( ScDetectiveFunc::IsColorsInitialized() )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                 const svtools::ColorConfig& rColors = GetColorConfig();
//STRIP001 /*?*/                BOOL bArrows =
//STRIP001 /*?*/                     ( ScDetectiveFunc::GetArrowColor() != (ColorData)rColors.GetColorValue(svtools::CALCDETECTIVE).nColor ||
//STRIP001 /*?*/                       ScDetectiveFunc::GetErrorColor() != (ColorData)rColors.GetColorValue(svtools::CALCDETECTIVEERROR).nColor );
//STRIP001 /*?*/                BOOL bComments =
//STRIP001 /*?*/                     ( ScDetectiveFunc::GetCommentColor() != (ColorData)rColors.GetColorValue(svtools::CALCNOTESBACKGROUND).nColor );
//STRIP001 /*?*/                if ( bArrows || bComments )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    ScDetectiveFunc::InitializeColors();        // get the new colors
//STRIP001 /*?*/
//STRIP001 /*?*/                    //  update detective objects in all open documents
//STRIP001 /*?*/                    SfxObjectShell* pObjSh = SfxObjectShell::GetFirst();
//STRIP001 /*?*/                    while ( pObjSh )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        if ( pObjSh->Type() == TYPE(ScDocShell) )
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            ScDocShell* pDocSh = ((ScDocShell*)pObjSh);
//STRIP001 /*?*/                            ScDetectiveFunc aFunc( pDocSh->GetDocument(), 0 );
//STRIP001 /*?*/                            if ( bArrows )
//STRIP001 /*?*/                                aFunc.UpdateAllArrowColors();
//STRIP001 /*?*/                            if ( bComments )
//STRIP001 /*?*/                                aFunc.UpdateAllComments();
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                        pObjSh = SfxObjectShell::GetNext( *pObjSh );
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            //  force all views to repaint, using the new options
//STRIP001 /*?*/
//STRIP001 /*?*/             SfxViewShell* pViewShell = SfxViewShell::GetFirst();
//STRIP001 /*?*/             while(pViewShell)
//STRIP001 /*?*/             {
//STRIP001 /*?*/                if ( pViewShell->ISA(ScTabViewShell) )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    ScTabViewShell* pViewSh = (ScTabViewShell*)pViewShell;
//STRIP001 /*?*/                    pViewSh->PaintGrid();
//STRIP001 /*?*/                    pViewSh->PaintTop();
//STRIP001 /*?*/                    pViewSh->PaintLeft();
//STRIP001 /*?*/                    pViewSh->PaintExtras();
//STRIP001 /*M*/
//STRIP001 /*M*/                    ScInputHandler* pHdl = pViewSh->GetInputHandler();
//STRIP001 /*M*/                    if ( pHdl )
//STRIP001 /*M*/                        pHdl->ForgetLastPattern();  // EditEngine BackgroundColor may change
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else if ( pViewShell->ISA(ScPreviewShell) )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    Window* pWin = pViewShell->GetWindow();
//STRIP001 /*?*/                    if (pWin)
//STRIP001 /*?*/                        pWin->Invalidate();
//STRIP001 /*?*/                }
//STRIP001 /*?*/                 pViewShell = SfxViewShell::GetNext( *pViewShell );
//STRIP001 /*?*/             }
/*N*/       }
/*N*/         else if ( nHintId == SFX_HINT_CTL_SETTINGS_CHANGED )
/*N*/         {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001          //  for all documents: set digit language for printer, recalc output factor, update row heights
//STRIP001          SfxObjectShell* pObjSh = SfxObjectShell::GetFirst();
//STRIP001          while ( pObjSh )
//STRIP001          {
//STRIP001              if ( pObjSh->Type() == TYPE(ScDocShell) )
//STRIP001              {
//STRIP001                  ScDocShell* pDocSh = ((ScDocShell*)pObjSh);
//STRIP001                  OutputDevice* pPrinter = pDocSh->GetPrinter();
//STRIP001                  if ( pPrinter )
//STRIP001                      pPrinter->SetDigitLanguage( GetOptDigitLanguage() );
//STRIP001
//STRIP001                  pDocSh->CalcOutputFactor();
//STRIP001
//STRIP001                  USHORT nTabCount = pDocSh->GetDocument()->GetTableCount();
//STRIP001                  for (USHORT nTab=0; nTab<nTabCount; nTab++)
//STRIP001                      pDocSh->AdjustRowHeight( 0, MAXROW, nTab );
//STRIP001              }
//STRIP001              pObjSh = SfxObjectShell::GetNext( *pObjSh );
//STRIP001          }
//STRIP001
//STRIP001          //  for all views (table and preview): update digit language
//STRIP001          SfxViewShell* pSh = SfxViewShell::GetFirst();
//STRIP001          while ( pSh )
//STRIP001          {
//STRIP001              if ( pSh->ISA( ScTabViewShell ) )
//STRIP001              {
//STRIP001                  ScTabViewShell* pViewSh = (ScTabViewShell*)pSh;
//STRIP001
//STRIP001                  //  set ref-device for EditEngine (re-evaluates digit settings)
//STRIP001                  ScInputHandler* pHdl = GetInputHdl(pViewSh);
//STRIP001                  if (pHdl)
//STRIP001                      pHdl->UpdateRefDevice();
//STRIP001
//STRIP001                  pViewSh->DigitLanguageChanged();
//STRIP001                  pViewSh->PaintGrid();
//STRIP001              }
//STRIP001              else if ( pSh->ISA( ScPreviewShell ) )
//STRIP001              {
//STRIP001                  ScPreviewShell* pPreviewSh = (ScPreviewShell*)pSh;
//STRIP001                  ScPreview* pPreview = pPreviewSh->GetPreview();
//STRIP001
//STRIP001                  pPreview->SetDigitLanguage( GetOptDigitLanguage() );
//STRIP001                  pPreview->Invalidate();
//STRIP001              }
//STRIP001
//STRIP001              pSh = SfxViewShell::GetNext( *pSh );
//STRIP001          }
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

//STRIP001 void ScModule::Execute( SfxRequest& rReq )
//STRIP001 {
//STRIP001  SfxViewFrame* pViewFrm = SfxViewFrame::Current();
//STRIP001  SfxBindings* pBindings = pViewFrm ? &pViewFrm->GetBindings() : NULL;
//STRIP001
//STRIP001  const SfxItemSet*   pReqArgs    = rReq.GetArgs();
//STRIP001  USHORT              nSlot       = rReq.GetSlot();
//STRIP001
//STRIP001  switch ( nSlot )
//STRIP001  {
//STRIP001      case SID_CHOOSE_DESIGN:
//STRIP001          {
//STRIP001              String aMacroName =
//STRIP001                  String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("Template.Samples.ShowStyles"));
//STRIP001              SfxApplication* pApp = SFX_APP();
//STRIP001              pApp->EnterBasicCall();
//STRIP001              pApp->GetMacroConfig()->Call( NULL, aMacroName, pApp->GetBasicManager() );
//STRIP001              pApp->LeaveBasicCall();
//STRIP001          }
//STRIP001          break;
//STRIP001      case SID_EURO_CONVERTER:
//STRIP001          {
//STRIP001              String aMacroName =
//STRIP001                  String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("Euro.ConvertRun.Main"));
//STRIP001              SfxApplication* pApp = SFX_APP();
//STRIP001              pApp->EnterBasicCall();
//STRIP001              pApp->GetMacroConfig()->Call( NULL, aMacroName, pApp->GetBasicManager() );
//STRIP001              pApp->LeaveBasicCall();
//STRIP001          }
//STRIP001          break;
//STRIP001      case SID_AUTOSPELL_CHECK:
//STRIP001          {
//STRIP001              BOOL bSet;
//STRIP001              const SfxPoolItem* pItem;
//STRIP001              if ( pReqArgs && SFX_ITEM_SET == pReqArgs->GetItemState( nSlot, TRUE, &pItem ) )
//STRIP001                  bSet = ((const SfxBoolItem*)pItem)->GetValue();
//STRIP001              else
//STRIP001              {                       //  Toggle
//STRIP001                  ScDocShell* pDocSh = PTR_CAST(ScDocShell, SfxObjectShell::Current());
//STRIP001                  if ( pDocSh )
//STRIP001                      bSet = !pDocSh->GetDocument()->GetDocOptions().IsAutoSpell();
//STRIP001                  else
//STRIP001                      bSet = !GetDocOptions().IsAutoSpell();
//STRIP001              }
//STRIP001
//STRIP001              SfxItemSet aSet( GetPool(), SID_AUTOSPELL_CHECK, SID_AUTOSPELL_CHECK );
//STRIP001              aSet.Put( SfxBoolItem( SID_AUTOSPELL_CHECK, bSet ) );
//STRIP001              ModifyOptions( aSet );
//STRIP001              rReq.Done();
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case SID_AUTOSPELL_MARKOFF:
//STRIP001          {
//STRIP001              BOOL bSet;
//STRIP001              const SfxPoolItem* pItem;
//STRIP001              if ( pReqArgs && SFX_ITEM_SET == pReqArgs->GetItemState( nSlot, TRUE, &pItem ) )
//STRIP001                  bSet = ((const SfxBoolItem*)pItem)->GetValue();
//STRIP001              else
//STRIP001              {                       //  Toggle
//STRIP001                  ScTabViewShell* pViewSh = PTR_CAST(ScTabViewShell, SfxViewShell::Current());
//STRIP001                  ScDocShell* pDocSh = PTR_CAST(ScDocShell, SfxObjectShell::Current());
//STRIP001                  if ( pViewSh )
//STRIP001                      bSet = !pViewSh->GetViewData()->GetOptions().IsHideAutoSpell();
//STRIP001                  else if ( pDocSh )
//STRIP001                      bSet = !pDocSh->GetDocument()->GetViewOptions().IsHideAutoSpell();
//STRIP001                  else
//STRIP001                      bSet = !GetViewOptions().IsHideAutoSpell();
//STRIP001              }
//STRIP001
//STRIP001              SfxItemSet aSet( GetPool(), SID_AUTOSPELL_MARKOFF, SID_AUTOSPELL_MARKOFF );
//STRIP001              aSet.Put( SfxBoolItem( SID_AUTOSPELL_MARKOFF, bSet ) );
//STRIP001              ModifyOptions( aSet );
//STRIP001              rReq.Done();
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case SID_ATTR_METRIC:
//STRIP001          {
//STRIP001              const SfxPoolItem* pItem;
//STRIP001              if ( pReqArgs && SFX_ITEM_SET == pReqArgs->GetItemState( nSlot, TRUE, &pItem ) )
//STRIP001              {
//STRIP001                  FieldUnit eUnit = (FieldUnit)((const SfxUInt16Item*)pItem)->GetValue();
//STRIP001                  switch( eUnit )
//STRIP001                  {
//STRIP001                      case FUNIT_MM:      // nur die Einheiten, die auch im Dialog stehen
//STRIP001                      case FUNIT_CM:
//STRIP001                      case FUNIT_INCH:
//STRIP001                      case FUNIT_PICA:
//STRIP001                      case FUNIT_POINT:
//STRIP001                          {
//STRIP001                              PutItem( *pItem );
//STRIP001                              ScAppOptions aNewOpts( GetAppOptions() );
//STRIP001                              aNewOpts.SetAppMetric( eUnit );
//STRIP001                              SetAppOptions( aNewOpts );
//STRIP001                              rReq.Done();
//STRIP001                          }
//STRIP001                          break;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case FID_AUTOCOMPLETE:
//STRIP001          {
//STRIP001              ScAppOptions aNewOpts( GetAppOptions() );
//STRIP001              BOOL bNew = !aNewOpts.GetAutoComplete();
//STRIP001              aNewOpts.SetAutoComplete( bNew );
//STRIP001              SetAppOptions( aNewOpts );
//STRIP001              ScInputHandler::SetAutoComplete( bNew );
//STRIP001              if (pBindings)
//STRIP001                  pBindings->Invalidate( FID_AUTOCOMPLETE );
//STRIP001              rReq.Done();
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case SID_DETECTIVE_AUTO:
//STRIP001          {
//STRIP001              ScAppOptions aNewOpts( GetAppOptions() );
//STRIP001              BOOL bNew = !aNewOpts.GetDetectiveAuto();
//STRIP001                 SFX_REQUEST_ARG( rReq, pAuto, SfxBoolItem, SID_DETECTIVE_AUTO, sal_False );
//STRIP001                 if ( pAuto )
//STRIP001                     bNew = pAuto->GetValue();
//STRIP001
//STRIP001              aNewOpts.SetDetectiveAuto( bNew );
//STRIP001              SetAppOptions( aNewOpts );
//STRIP001              if (pBindings)
//STRIP001                  pBindings->Invalidate( SID_DETECTIVE_AUTO );
//STRIP001                 rReq.AppendItem( SfxBoolItem( SID_DETECTIVE_AUTO, bNew ) );
//STRIP001              rReq.Done();
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case SID_PSZ_FUNCTION:
//STRIP001          if (pReqArgs)
//STRIP001          {
//STRIP001              const SfxUInt16Item& rItem = (const SfxUInt16Item&)pReqArgs->Get(SID_PSZ_FUNCTION);
//STRIP001              DBG_ASSERT(rItem.ISA(SfxUInt16Item),"falscher Parameter");
//STRIP001
//STRIP001              ScAppOptions aNewOpts( GetAppOptions() );
//STRIP001              aNewOpts.SetStatusFunc( rItem.GetValue() );
//STRIP001              SetAppOptions( aNewOpts );
//STRIP001
//STRIP001              if (pBindings)
//STRIP001              {
//STRIP001                  pBindings->Invalidate( SID_TABLE_CELL );
//STRIP001                  pBindings->Update( SID_TABLE_CELL );            // sofort
//STRIP001
//STRIP001                  pBindings->Invalidate( SID_PSZ_FUNCTION );
//STRIP001                  pBindings->Update( SID_PSZ_FUNCTION );
//STRIP001                  // falls Menue gleich wieder aufgeklappt wird
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case SID_ATTR_LANGUAGE:
//STRIP001      case SID_ATTR_CHAR_CJK_LANGUAGE:
//STRIP001      case SID_ATTR_CHAR_CTL_LANGUAGE:
//STRIP001          {
//STRIP001              const SfxPoolItem* pItem;
//STRIP001              if ( pReqArgs && SFX_ITEM_SET == pReqArgs->GetItemState( GetPool().GetWhich(nSlot), TRUE, &pItem ) )
//STRIP001              {
//STRIP001                  ScDocShell* pDocSh = PTR_CAST(ScDocShell, SfxObjectShell::Current());
//STRIP001                  ScDocument* pDoc = pDocSh ? pDocSh->GetDocument() : NULL;
//STRIP001                  if ( pDoc )
//STRIP001                  {
//STRIP001                      LanguageType eNewLang = ((SvxLanguageItem*)pItem)->GetLanguage();
//STRIP001                      LanguageType eLatin, eCjk, eCtl;
//STRIP001                      pDoc->GetLanguage( eLatin, eCjk, eCtl );
//STRIP001                      LanguageType eOld = ( nSlot == SID_ATTR_CHAR_CJK_LANGUAGE ) ? eCjk :
//STRIP001                                          ( ( nSlot == SID_ATTR_CHAR_CTL_LANGUAGE ) ? eCtl : eLatin );
//STRIP001                      if ( eNewLang != eOld )
//STRIP001                      {
//STRIP001                          if ( nSlot == SID_ATTR_CHAR_CJK_LANGUAGE )
//STRIP001                              eCjk = eNewLang;
//STRIP001                          else if ( nSlot == SID_ATTR_CHAR_CTL_LANGUAGE )
//STRIP001                              eCtl = eNewLang;
//STRIP001                          else
//STRIP001                              eLatin = eNewLang;
//STRIP001
//STRIP001                          pDoc->SetLanguage( eLatin, eCjk, eCtl );
//STRIP001
//STRIP001                          ScInputHandler* pInputHandler = GetInputHdl();
//STRIP001                          if ( pInputHandler )
//STRIP001                              pInputHandler->UpdateSpellSettings();   // EditEngine-Flags
//STRIP001                          ScTabViewShell* pViewSh = PTR_CAST(ScTabViewShell, SfxViewShell::Current());
//STRIP001                          if ( pViewSh )
//STRIP001                              pViewSh->UpdateDrawTextOutliner();      // EditEngine-Flags
//STRIP001
//STRIP001                             pDocSh->SetDocumentModified();
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case FID_FOCUS_POSWND:
//STRIP001          {
//STRIP001              ScInputHandler* pHdl = GetInputHdl();
//STRIP001              if (pHdl)
//STRIP001              {
//STRIP001                  ScInputWindow* pWin = pHdl->GetInputWindow();
//STRIP001                  if (pWin)
//STRIP001                      pWin->PosGrabFocus();
//STRIP001              }
//STRIP001              rReq.Done();
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001         case SID_OPEN_XML_FILTERSETTINGS:
//STRIP001         {
//STRIP001          try
//STRIP001          {
//STRIP001              com::sun::star::uno::Reference < ::com::sun::star::ui::dialogs::XExecutableDialog > xDialog(::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(rtl::OUString::createFromAscii("com.sun.star.comp.ui.XSLTFilterDialog")), com::sun::star::uno::UNO_QUERY);
//STRIP001              if( xDialog.is() )
//STRIP001              {
//STRIP001                  xDialog->execute();
//STRIP001              }
//STRIP001          }
//STRIP001          catch( ::com::sun::star::uno::RuntimeException& )
//STRIP001          {
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001      default:
//STRIP001          DBG_ERROR( "ScApplication: Unknown Message." );
//STRIP001          break;
//STRIP001  }
//STRIP001 }

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

//STRIP001 void ScModule::SetDragObject( ScTransferObj* pCellObj, ScDrawTransferObj* pDrawObj )
//STRIP001 {
//STRIP001  ResetDragObject();
//STRIP001  aDragData.pCellTransfer = pCellObj;
//STRIP001  aDragData.pDrawTransfer = pDrawObj;
//STRIP001 }

//STRIP001 void ScModule::SetDragLink( const String& rDoc, const String& rTab, const String& rArea )
//STRIP001 {
//STRIP001  ResetDragObject();
//STRIP001
//STRIP001  aDragData.aLinkDoc   = rDoc;
//STRIP001  aDragData.aLinkTable = rTab;
//STRIP001  aDragData.aLinkArea  = rArea;
//STRIP001 }

//STRIP001 void ScModule::SetDragJump( ScDocument* pLocalDoc, const String& rTarget, const String& rText )
//STRIP001 {
//STRIP001  ResetDragObject();
//STRIP001
//STRIP001  aDragData.pJumpLocalDoc = pLocalDoc;
//STRIP001  aDragData.aJumpTarget = rTarget;
//STRIP001  aDragData.aJumpText = rText;
//STRIP001 }

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
DBG_ASSERT(0, "STRIP"); //STRIP001 //STRIP001   //  called from document
//STRIP001
//STRIP001  ScTransferObj* pObj = ScTransferObj::GetOwnClipboard( NULL );
//STRIP001  if (pObj)
//STRIP001      return pObj->GetDocument();
//STRIP001
/*N*/   return NULL;
/*N*/ }

//------------------------------------------------------------------

//STRIP001 void ScModule::SetSelectionTransfer( ScSelectionTransferObj* pNew )
//STRIP001 {
//STRIP001  pSelTransfer = pNew;
//STRIP001 }

//------------------------------------------------------------------

//STRIP001 void ScModule::InitFormEditData()
//STRIP001 {
//STRIP001  pFormEditData = new ScFormEditData;
//STRIP001 }

//STRIP001 void ScModule::ClearFormEditData()
//STRIP001 {
//STRIP001  DELETEZ( pFormEditData );
//STRIP001 }

//------------------------------------------------------------------

//STRIP001 void ScModule::SetViewOptions( const ScViewOptions& rOpt )
//STRIP001 {
//STRIP001  if ( !pViewCfg )
//STRIP001      pViewCfg = new ScViewCfg;
//STRIP001
//STRIP001  pViewCfg->SetOptions( rOpt );
//STRIP001 }

/*N*/ const ScViewOptions& ScModule::GetViewOptions()
/*N*/ {
/*N*/   if ( !pViewCfg )
/*N*/       pViewCfg = new ScViewCfg;
/*N*/
/*N*/   return *pViewCfg;
/*N*/ }

//STRIP001 void ScModule::SetDocOptions( const ScDocOptions& rOpt )
//STRIP001 {
//STRIP001  if ( !pDocCfg )
//STRIP001      pDocCfg = new ScDocCfg;
//STRIP001
//STRIP001  pDocCfg->SetOptions( rOpt );
//STRIP001 }

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

//STRIP001 void ScModule::InsertEntryToLRUList(USHORT nFIndex)
//STRIP001 {
//STRIP001  if(nFIndex != 0)
//STRIP001  {
//STRIP001      const ScAppOptions& rAppOpt = GetAppOptions();
//STRIP001      USHORT nLRUFuncCount = Min( rAppOpt.GetLRUFuncListCount(), (USHORT)LRU_MAX );
//STRIP001      USHORT* pLRUListIds = rAppOpt.GetLRUFuncList();
//STRIP001
//STRIP001      USHORT  aIdxList[LRU_MAX];
//STRIP001      USHORT  n = 0;
//STRIP001      BOOL    bFound = FALSE;
//STRIP001
//STRIP001      while ((n < LRU_MAX) && n<nLRUFuncCount)                        // alte Liste abklappern
//STRIP001      {
//STRIP001          if (!bFound && (pLRUListIds[n]== nFIndex))
//STRIP001              bFound = TRUE;                                          // erster! Treffer
//STRIP001          else if (bFound)
//STRIP001              aIdxList[n  ] = pLRUListIds[n];                         // hinter Treffer kopieren
//STRIP001          else if ((n+1) < LRU_MAX)
//STRIP001              aIdxList[n+1] = pLRUListIds[n];                         // vor Treffer verschieben
//STRIP001          n++;
//STRIP001      }
//STRIP001      if (!bFound && (n < LRU_MAX))                                   // Eintrag nicht gefunden?
//STRIP001          n++;                                                        //  einen mehr
//STRIP001      aIdxList[0] = nFIndex;                                          // Current on Top
//STRIP001
//STRIP001      ScAppOptions aNewOpts(rAppOpt);                                 // an App melden
//STRIP001      aNewOpts.SetLRUFuncList(aIdxList, n);
//STRIP001      SetAppOptions(aNewOpts);
//STRIP001
//STRIP001      RecentFunctionsChanged();
//STRIP001  }
//STRIP001 }

/*N*/ void ScModule::RecentFunctionsChanged()
/*N*/ {
/*N*/   //  update function list window
/*N*/   USHORT nFuncListID = ScFunctionChildWindow::GetChildWindowId();
/*N*/
/*N*/   //! notify all views
/*N*/   SfxViewFrame* pViewFrm = SfxViewFrame::Current();
/*N*/   if ( pViewFrm && pViewFrm->HasChildWindow(nFuncListID) )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 ScFunctionChildWindow* pWnd =(ScFunctionChildWindow*)pViewFrm->GetChildWindow( nFuncListID );
/*?*/
//STRIP001 /*?*/        ScFunctionDockWin* pFuncList=(ScFunctionDockWin*)pWnd->GetWindow();
//STRIP001 /*?*/
//STRIP001 /*?*/        pFuncList->InitLRUList();
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

/*N*/ ScNavipiCfg& ScModule::GetNavipiCfg()
/*N*/ {
/*N*/   if ( !pNavipiCfg )
/*N*/       pNavipiCfg = new ScNavipiCfg;
/*N*/
/*N*/   return *pNavipiCfg;
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

//------------------------------------------------------------------
//
//                          Optionen
//
//------------------------------------------------------------------

//
//      ModifyOptions - Items aus Calc-Options-Dialog
//                      und SID_AUTOSPELL_CHECK / SID_AUTOSPELL_MARKOFF
//

#define IS_AVAILABLE(w,item) (SFX_ITEM_SET==rOptSet.GetItemState((w),TRUE,&item))

//STRIP001 void ScModule::ModifyOptions( const SfxItemSet& rOptSet )
//STRIP001 {
//STRIP001  USHORT nOldSpellLang, nOldCjkLang, nOldCtlLang;
//STRIP001  BOOL bOldAutoSpell, bOldHideAuto;
//STRIP001  GetSpellSettings( nOldSpellLang, nOldCjkLang, nOldCtlLang, bOldAutoSpell, bOldHideAuto );
//STRIP001
//STRIP001  if (!pAppCfg)
//STRIP001      GetAppOptions();
//STRIP001  DBG_ASSERT( pAppCfg, "AppOptions not initialised :-(" );
//STRIP001
//STRIP001  if (!pInputCfg)
//STRIP001      GetInputOptions();
//STRIP001  DBG_ASSERT( pInputCfg, "InputOptions not initialised :-(" );
//STRIP001
//STRIP001  //--------------------------------------------------------------
//STRIP001
//STRIP001  SfxViewFrame* pViewFrm = SfxViewFrame::Current();
//STRIP001  SfxBindings* pBindings = pViewFrm ? &pViewFrm->GetBindings() : NULL;
//STRIP001
//STRIP001  ScTabViewShell*         pViewSh = PTR_CAST(ScTabViewShell, SfxViewShell::Current());
//STRIP001  ScDocShell*             pDocSh  = PTR_CAST(ScDocShell, SfxObjectShell::Current());
//STRIP001  ScDocument*             pDoc    = pDocSh ? pDocSh->GetDocument() : NULL;
//STRIP001  const SfxPoolItem*      pItem   = NULL;
//STRIP001  BOOL                    bRepaint            = FALSE;
//STRIP001  BOOL                    bUpdateMarks        = FALSE;
//STRIP001  BOOL                    bUpdateRefDev       = FALSE;
//STRIP001  BOOL                    bCalcAll            = FALSE;
//STRIP001  BOOL                    bSaveSpellCheck     = FALSE;
//STRIP001  BOOL                    bSaveAppOptions     = FALSE;
//STRIP001  BOOL                    bSaveInputOptions   = FALSE;
//STRIP001
//STRIP001  //--------------------------------------------------------------------------
//STRIP001
//STRIP001  //  OFF_APP()->SetOptions( rOptSet );
//STRIP001
//STRIP001  //  Linguistik nicht mehr
//STRIP001
//STRIP001  if ( IS_AVAILABLE(SID_ATTR_METRIC,pItem) )
//STRIP001  {
//STRIP001      PutItem( *pItem );
//STRIP001      pAppCfg->SetAppMetric( (FieldUnit)((const SfxUInt16Item*)pItem)->GetValue() );
//STRIP001      bSaveAppOptions = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  if ( IS_AVAILABLE(SCITEM_USERLIST,pItem) )
//STRIP001  {
//STRIP001      ScGlobal::SetUserList( ((const ScUserListItem*)pItem)->GetUserList() );
//STRIP001      bSaveAppOptions = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  //============================================
//STRIP001  // ViewOptions
//STRIP001  //============================================
//STRIP001
//STRIP001  if ( IS_AVAILABLE(SID_SCVIEWOPTIONS,pItem) )
//STRIP001  {
//STRIP001      const ScViewOptions& rNewOpt = ((const ScTpViewItem*)pItem)->GetViewOptions();
//STRIP001
//STRIP001      if ( pViewSh )
//STRIP001      {
//STRIP001          ScViewData*             pViewData = pViewSh->GetViewData();
//STRIP001          const ScViewOptions&    rOldOpt   = pViewData->GetOptions();
//STRIP001
//STRIP001          BOOL bAnchorList = ( rOldOpt.GetOption( VOPT_ANCHOR ) !=
//STRIP001                               rNewOpt.GetOption( VOPT_ANCHOR ) );
//STRIP001
//STRIP001          if ( rOldOpt != rNewOpt )
//STRIP001          {
//STRIP001              pViewData->SetOptions( rNewOpt );   // veraendert rOldOpt
//STRIP001              pViewData->GetDocument()->SetViewOptions( rNewOpt );
//STRIP001              pDocSh->SetDocumentModified();
//STRIP001              bRepaint = TRUE;
//STRIP001          }
//STRIP001          if ( bAnchorList )
//STRIP001              pViewSh->UpdateAnchorHandles();
//STRIP001      }
//STRIP001      SetViewOptions( rNewOpt );
//STRIP001      if (pBindings)
//STRIP001          pBindings->Invalidate(SID_HELPLINES_MOVE);
//STRIP001  }
//STRIP001
//STRIP001  //============================================
//STRIP001  // GridOptions, Auswertung nach ViewOptions,
//STRIP001  // da GridOptions Member der ViewOptions ist!
//STRIP001  //============================================
//STRIP001
//STRIP001  if ( IS_AVAILABLE(SID_ATTR_GRID_OPTIONS,pItem) )
//STRIP001  {
//STRIP001      ScGridOptions aNewGridOpt( (const SvxOptionsGrid&)((const SvxGridItem&)*pItem) );
//STRIP001
//STRIP001      if ( pViewSh )
//STRIP001      {
//STRIP001          ScViewData*          pViewData = pViewSh->GetViewData();
//STRIP001          ScViewOptions        aNewViewOpt( pViewData->GetOptions() );
//STRIP001          const ScGridOptions& rOldGridOpt = aNewViewOpt.GetGridOptions();
//STRIP001
//STRIP001          if ( rOldGridOpt != aNewGridOpt )
//STRIP001          {
//STRIP001              aNewViewOpt.SetGridOptions( aNewGridOpt );
//STRIP001              pViewData->SetOptions( aNewViewOpt );
//STRIP001              pViewData->GetDocument()->SetViewOptions( aNewViewOpt );
//STRIP001              pDocSh->SetDocumentModified();
//STRIP001              bRepaint = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001      ScViewOptions aNewViewOpt ( GetViewOptions() );
//STRIP001      aNewViewOpt.SetGridOptions( aNewGridOpt );
//STRIP001      SetViewOptions( aNewViewOpt );
//STRIP001      if (pBindings)
//STRIP001      {
//STRIP001          pBindings->Invalidate(SID_GRID_VISIBLE);
//STRIP001          pBindings->Invalidate(SID_GRID_USE);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  //
//STRIP001  //  AutoSpell ausblenden auch nach den ViewOptions
//STRIP001  //
//STRIP001
//STRIP001  if ( IS_AVAILABLE(SID_AUTOSPELL_MARKOFF,pItem) )            // an View-Options
//STRIP001  {
//STRIP001      BOOL bHideAutoSpell = ((const SfxBoolItem*)pItem)->GetValue();
//STRIP001
//STRIP001      if (pViewSh)
//STRIP001      {
//STRIP001          ScViewData* pViewData = pViewSh->GetViewData();
//STRIP001          ScViewOptions aNewOpt = pViewData->GetOptions();
//STRIP001          if ( aNewOpt.IsHideAutoSpell() != bHideAutoSpell )
//STRIP001          {
//STRIP001              aNewOpt.SetHideAutoSpell( bHideAutoSpell );
//STRIP001              pViewData->SetOptions( aNewOpt );
//STRIP001              bRepaint = TRUE;
//STRIP001          }
//STRIP001          ScViewOptions aDocView = pDoc->GetViewOptions();    // auch am Dokument
//STRIP001          if ( aDocView.IsHideAutoSpell() != bHideAutoSpell )
//STRIP001          {
//STRIP001              aDocView.SetHideAutoSpell( bHideAutoSpell );
//STRIP001              pDoc->SetViewOptions( aDocView );
//STRIP001                 //#92038#; don't set document modified, because this flag is no longer saved
//STRIP001 //               pDocSh->SetDocumentModified();
//STRIP001          }
//STRIP001      }
//STRIP001      if ( bOldHideAuto != bHideAutoSpell )
//STRIP001      {
//STRIP001          SetHideAutoProperty( bHideAutoSpell );
//STRIP001          bSaveSpellCheck = TRUE;
//STRIP001      }
//STRIP001      ScInputHandler* pInputHandler = GetInputHdl();
//STRIP001      if ( pInputHandler )
//STRIP001          pInputHandler->UpdateSpellSettings();               // EditEngine-Flags
//STRIP001      if ( pViewSh )
//STRIP001          pViewSh->UpdateDrawTextOutliner();                  // EditEngine-Flags
//STRIP001  }
//STRIP001
//STRIP001  //============================================
//STRIP001  // DocOptions
//STRIP001  //============================================
//STRIP001
//STRIP001  if ( IS_AVAILABLE(SID_SCDOCOPTIONS,pItem) )
//STRIP001  {
//STRIP001      const ScDocOptions& rNewOpt = ((const ScTpCalcItem*)pItem)->GetDocOptions();
//STRIP001
//STRIP001      if ( pDoc )
//STRIP001      {
//STRIP001          const ScDocOptions& rOldOpt = pDoc->GetDocOptions();
//STRIP001
//STRIP001          bRepaint = ( bRepaint || ( rOldOpt != rNewOpt )   );
//STRIP001          bCalcAll =   bRepaint &&
//STRIP001                       (  rOldOpt.IsIter()       != rNewOpt.IsIter()
//STRIP001                       || rOldOpt.GetIterCount() != rNewOpt.GetIterCount()
//STRIP001                       || rOldOpt.GetIterEps()   != rNewOpt.GetIterEps()
//STRIP001                       || rOldOpt.IsIgnoreCase() != rNewOpt.IsIgnoreCase()
//STRIP001                       || rOldOpt.IsCalcAsShown() != rNewOpt.IsCalcAsShown()
//STRIP001                       || (rNewOpt.IsCalcAsShown() &&
//STRIP001                          rOldOpt.GetStdPrecision() != rNewOpt.GetStdPrecision())
//STRIP001                       || rOldOpt.IsMatchWholeCell() != rNewOpt.IsMatchWholeCell()
//STRIP001                       || rOldOpt.GetYear2000()   != rNewOpt.GetYear2000()
//STRIP001                          || rOldOpt.IsFormulaRegexEnabled() != rNewOpt.IsFormulaRegexEnabled()
//STRIP001                       );
//STRIP001          pDoc->SetDocOptions( rNewOpt );
//STRIP001          pDocSh->SetDocumentModified();
//STRIP001      }
//STRIP001      SetDocOptions( rNewOpt );
//STRIP001  }
//STRIP001
//STRIP001  // nach den eigentlichen DocOptions auch noch die TabDistance setzen
//STRIP001  if ( IS_AVAILABLE(SID_ATTR_DEFTABSTOP,pItem) )
//STRIP001  {
//STRIP001      USHORT nTabDist = ((SfxUInt16Item*)pItem)->GetValue();
//STRIP001      ScDocOptions aOpt(GetDocOptions());
//STRIP001      aOpt.SetTabDistance(nTabDist);
//STRIP001      SetDocOptions( aOpt );
//STRIP001
//STRIP001      if ( pDoc )
//STRIP001      {
//STRIP001          ScDocOptions aOpt(pDoc->GetDocOptions());
//STRIP001          aOpt.SetTabDistance(nTabDist);
//STRIP001          pDoc->SetDocOptions( aOpt );
//STRIP001          pDocSh->SetDocumentModified();
//STRIP001          if(pDoc->GetDrawLayer())
//STRIP001              pDoc->GetDrawLayer()->SetDefaultTabulator(nTabDist);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  //  AutoSpell nach den Doc-Options (weil Member)
//STRIP001
//STRIP001  if ( IS_AVAILABLE(SID_AUTOSPELL_CHECK,pItem) )              // an Doc-Options
//STRIP001  {
//STRIP001      BOOL bDoAutoSpell = ((const SfxBoolItem*)pItem)->GetValue();
//STRIP001
//STRIP001      if (pDoc)
//STRIP001      {
//STRIP001          ScDocOptions aNewOpt = pDoc->GetDocOptions();
//STRIP001          if ( aNewOpt.IsAutoSpell() != bDoAutoSpell )
//STRIP001          {
//STRIP001              aNewOpt.SetAutoSpell( bDoAutoSpell );
//STRIP001              pDoc->SetDocOptions( aNewOpt );
//STRIP001
//STRIP001              if (bDoAutoSpell)
//STRIP001                  pDoc->SetOnlineSpellPos( ScAddress(0,0,0) );    // vorne anfangen
//STRIP001              else
//STRIP001              {
//STRIP001                  WaitObject aWait( pDocSh->GetDialogParent() );
//STRIP001                  pDoc->RemoveAutoSpellObj();     //  Edit-Text-Objekte wieder zurueckwandeln
//STRIP001              }
//STRIP001
//STRIP001                 //#92038#; don't set document modified, because this flag is no longer saved
//STRIP001 //               pDocSh->SetDocumentModified();
//STRIP001
//STRIP001              bRepaint = TRUE;            //  weil HideAutoSpell evtl. ungueltig
//STRIP001                                          //! alle Views painten ???
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if ( bOldAutoSpell != bDoAutoSpell )
//STRIP001      {
//STRIP001          SetAutoSpellProperty( bDoAutoSpell );
//STRIP001          bSaveSpellCheck = TRUE;
//STRIP001      }
//STRIP001      if ( pDocSh )
//STRIP001          pDocSh->PostPaintGridAll();                     // wegen Markierungen
//STRIP001      ScInputHandler* pInputHandler = GetInputHdl();
//STRIP001      if ( pInputHandler )
//STRIP001          pInputHandler->UpdateSpellSettings();           // EditEngine-Flags
//STRIP001      if ( pViewSh )
//STRIP001          pViewSh->UpdateDrawTextOutliner();              // EditEngine-Flags
//STRIP001
//STRIP001      if (pBindings)
//STRIP001          pBindings->Invalidate( SID_AUTOSPELL_CHECK );
//STRIP001  }
//STRIP001
//STRIP001  //============================================
//STRIP001  // InputOptions
//STRIP001  //============================================
//STRIP001
//STRIP001  if ( IS_AVAILABLE(SID_SC_INPUT_SELECTIONPOS,pItem) )
//STRIP001  {
//STRIP001      pInputCfg->SetMoveDir( ((const SfxUInt16Item*)pItem)->GetValue() );
//STRIP001      bSaveInputOptions = TRUE;
//STRIP001  }
//STRIP001  if ( IS_AVAILABLE(SID_SC_INPUT_SELECTION,pItem) )
//STRIP001  {
//STRIP001      pInputCfg->SetMoveSelection( ((const SfxBoolItem*)pItem)->GetValue() );
//STRIP001      bSaveInputOptions = TRUE;
//STRIP001  }
//STRIP001  if ( IS_AVAILABLE(SID_SC_INPUT_EDITMODE,pItem) )
//STRIP001  {
//STRIP001      pInputCfg->SetEnterEdit( ((const SfxBoolItem*)pItem)->GetValue() );
//STRIP001      bSaveInputOptions = TRUE;
//STRIP001  }
//STRIP001  if ( IS_AVAILABLE(SID_SC_INPUT_FMT_EXPAND,pItem) )
//STRIP001  {
//STRIP001      pInputCfg->SetExtendFormat( ((const SfxBoolItem*)pItem)->GetValue() );
//STRIP001      bSaveInputOptions = TRUE;
//STRIP001  }
//STRIP001  if ( IS_AVAILABLE(SID_SC_INPUT_RANGEFINDER,pItem) )
//STRIP001  {
//STRIP001      pInputCfg->SetRangeFinder( ((const SfxBoolItem*)pItem)->GetValue() );
//STRIP001      bSaveInputOptions = TRUE;
//STRIP001  }
//STRIP001  if ( IS_AVAILABLE(SID_SC_INPUT_REF_EXPAND,pItem) )
//STRIP001  {
//STRIP001      pInputCfg->SetExpandRefs( ((const SfxBoolItem*)pItem)->GetValue() );
//STRIP001      bSaveInputOptions = TRUE;
//STRIP001  }
//STRIP001  if ( IS_AVAILABLE(SID_SC_INPUT_MARK_HEADER,pItem) )
//STRIP001  {
//STRIP001      pInputCfg->SetMarkHeader( ((const SfxBoolItem*)pItem)->GetValue() );
//STRIP001      bSaveInputOptions = TRUE;
//STRIP001      bUpdateMarks = TRUE;
//STRIP001  }
//STRIP001  if ( IS_AVAILABLE(SID_SC_INPUT_TEXTWYSIWYG,pItem) )
//STRIP001  {
//STRIP001      BOOL bNew = ((const SfxBoolItem*)pItem)->GetValue();
//STRIP001      if ( bNew != pInputCfg->GetTextWysiwyg() )
//STRIP001      {
//STRIP001          pInputCfg->SetTextWysiwyg( bNew );
//STRIP001          bSaveInputOptions = TRUE;
//STRIP001          bUpdateRefDev = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001     if( IS_AVAILABLE( SID_SC_INPUT_REPLCELLSWARN, pItem ) )
//STRIP001  {
//STRIP001         pInputCfg->SetReplaceCellsWarn( ((const SfxBoolItem*)pItem)->GetValue() );
//STRIP001         bSaveInputOptions = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  //============================================
//STRIP001  // PrintOptions
//STRIP001  //============================================
//STRIP001
//STRIP001  if ( IS_AVAILABLE(SID_SCPRINTOPTIONS,pItem) )
//STRIP001  {
//STRIP001      const ScPrintOptions& rNewOpt = ((const ScTpPrintItem*)pItem)->GetPrintOptions();
//STRIP001      SetPrintOptions( rNewOpt );
//STRIP001
//STRIP001      //  broadcast causes all previews to recalc page numbers
//STRIP001      SFX_APP()->Broadcast( SfxSimpleHint( SID_SCPRINTOPTIONS ) );
//STRIP001  }
//STRIP001
//STRIP001  //----------------------------------------------------------
//STRIP001
//STRIP001 //   if ( bSaveSpellCheck )
//STRIP001 //   {
//STRIP001      //  currently LinguProperties are saved only at program exit.
//STRIP001      //  if a save method becomes available, it should be called here.
//STRIP001 //   }
//STRIP001
//STRIP001  if ( bSaveAppOptions )
//STRIP001      pAppCfg->OptionsChanged();
//STRIP001
//STRIP001  if ( bSaveInputOptions )
//STRIP001      pInputCfg->OptionsChanged();
//STRIP001
//STRIP001  // Neuberechnung anstossen?
//STRIP001
//STRIP001  if ( pDoc && bCalcAll )
//STRIP001  {
//STRIP001      WaitObject aWait( pDocSh->GetDialogParent() );
//STRIP001      pDoc->CalcAll();
//STRIP001      pViewSh->UpdateCharts( TRUE );
//STRIP001      if (pBindings)
//STRIP001          pBindings->Invalidate( SID_ATTR_SIZE ); //SvxPosSize-StatusControl-Update
//STRIP001  }
//STRIP001
//STRIP001  if ( pViewSh && bUpdateMarks )
//STRIP001      pViewSh->UpdateAutoFillMark();
//STRIP001
//STRIP001  // View neuzeichnen?
//STRIP001
//STRIP001  if ( pViewSh && bRepaint )
//STRIP001  {
//STRIP001      pViewSh->UpdateFixPos();
//STRIP001      pViewSh->PaintGrid();
//STRIP001      pViewSh->PaintTop();
//STRIP001      pViewSh->PaintLeft();
//STRIP001      pViewSh->PaintExtras();
//STRIP001      pViewSh->InvalidateBorder();
//STRIP001      if (pBindings)
//STRIP001      {
//STRIP001          pBindings->Invalidate( FID_TOGGLEHEADERS ); // -> Checks im Menue
//STRIP001          pBindings->Invalidate( FID_TOGGLESYNTAX );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // update ref device (for all documents)
//STRIP001
//STRIP001  if ( bUpdateRefDev )
//STRIP001  {
//STRIP001      //  for all documents: recalc output factor, update row heights
//STRIP001      SfxObjectShell* pObjSh = SfxObjectShell::GetFirst();
//STRIP001      while ( pObjSh )
//STRIP001      {
//STRIP001          if ( pObjSh->Type() == TYPE(ScDocShell) )
//STRIP001          {
//STRIP001              ScDocShell* pDocSh = ((ScDocShell*)pObjSh);
//STRIP001              pDocSh->CalcOutputFactor();
//STRIP001              USHORT nTabCount = pDocSh->GetDocument()->GetTableCount();
//STRIP001              for (USHORT nTab=0; nTab<nTabCount; nTab++)
//STRIP001                  pDocSh->AdjustRowHeight( 0, MAXROW, nTab );
//STRIP001          }
//STRIP001          pObjSh = SfxObjectShell::GetNext( *pObjSh );
//STRIP001      }
//STRIP001
//STRIP001      //  for all (tab-) views:
//STRIP001      TypeId aScType = TYPE(ScTabViewShell);
//STRIP001      SfxViewShell* pSh = SfxViewShell::GetFirst( &aScType );
//STRIP001      while ( pSh )
//STRIP001      {
//STRIP001          ScTabViewShell* pViewSh = (ScTabViewShell*)pSh;
//STRIP001
//STRIP001          //  set ref-device for EditEngine
//STRIP001          ScInputHandler* pHdl = GetInputHdl(pViewSh);
//STRIP001          if (pHdl)
//STRIP001              pHdl->UpdateRefDevice();
//STRIP001
//STRIP001          //  update view scale
//STRIP001          ScViewData* pViewData = pViewSh->GetViewData();
//STRIP001          pViewSh->SetZoom( pViewData->GetZoomX(), pViewData->GetZoomY() );
//STRIP001
//STRIP001          //  repaint
//STRIP001          pViewSh->PaintGrid();
//STRIP001          pViewSh->PaintTop();
//STRIP001          pViewSh->PaintLeft();
//STRIP001
//STRIP001          pSh = SfxViewShell::GetNext( *pSh, &aScType );
//STRIP001      }
//STRIP001  }
//STRIP001 }

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

//STRIP001 void ScModule::ViewShellChanged()
//STRIP001 {
//STRIP001  ScInputHandler* pHdl   = GetInputHdl();
//STRIP001  ScTabViewShell* pShell = ScTabViewShell::GetActiveViewShell();
//STRIP001  if ( pShell && pHdl )
//STRIP001      pShell->UpdateInputHandler();
//STRIP001 }

//STRIP001 void ScModule::SetInputMode( ScInputMode eMode )
//STRIP001 {
//STRIP001  ScInputHandler* pHdl = GetInputHdl();
//STRIP001  if (pHdl)
//STRIP001      pHdl->SetMode( eMode );
//STRIP001 }

//STRIP001 BOOL ScModule::IsEditMode()
//STRIP001 {
//STRIP001  ScInputHandler* pHdl = GetInputHdl();
//STRIP001  return pHdl && pHdl->IsEditMode();
//STRIP001 }

//STRIP001 BOOL ScModule::IsInputMode()
//STRIP001 {
//STRIP001  ScInputHandler* pHdl = GetInputHdl();
//STRIP001  return pHdl && pHdl->IsInputMode();
//STRIP001 }

//STRIP001 BOOL ScModule::InputKeyEvent( const KeyEvent& rKEvt, BOOL bStartEdit )
//STRIP001 {
//STRIP001  ScInputHandler* pHdl = GetInputHdl();
//STRIP001  return ( pHdl ? pHdl->KeyInput( rKEvt, bStartEdit ) : FALSE );
//STRIP001 }

/*N*/ void ScModule::InputEnterHandler( BYTE nBlockMode )
/*N*/ {
/*N*/   if ( !SFX_APP()->IsDowning() )                                  // nicht beim Programmende
/*N*/   {
/*N*/       ScInputHandler* pHdl = GetInputHdl();
/*N*/       if (pHdl)
/*?*/           pHdl->EnterHandler( nBlockMode );
/*N*/   }
/*N*/ }

//STRIP001 void ScModule::InputCancelHandler()
//STRIP001 {
//STRIP001  ScInputHandler* pHdl = GetInputHdl();
//STRIP001  if (pHdl)
//STRIP001      pHdl->CancelHandler();
//STRIP001 }

//STRIP001 void ScModule::InputSelection( EditView* pView )
//STRIP001 {
//STRIP001  ScInputHandler* pHdl = GetInputHdl();
//STRIP001  if (pHdl)
//STRIP001      pHdl->InputSelection( pView );
//STRIP001 }

//STRIP001 void ScModule::InputChanged( EditView* pView )
//STRIP001 {
//STRIP001  ScInputHandler* pHdl = GetInputHdl();
//STRIP001  if (pHdl)
//STRIP001      pHdl->InputChanged( pView );
//STRIP001 }

//STRIP001 void ScModule::SetInputWindow( ScInputWindow* pWin )
//STRIP001 {
//STRIP001  ScInputHandler* pHdl = GetInputHdl();
//STRIP001  if ( pHdl )
//STRIP001      pHdl->SetInputWindow( pWin );
//STRIP001 }

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

//STRIP001 void ScModule::SetRefInputHdl( ScInputHandler* pNew )
//STRIP001 {
//STRIP001  pRefInputHandler = pNew;
//STRIP001 }

/*N*/ ScInputHandler* ScModule::GetRefInputHdl()
/*N*/ {
/*N*/   return pRefInputHandler;
/*N*/ }

//------------------------------------------------------------------------
//  Olk's Krempel:

//STRIP001 void ScModule::InputGetSelection( xub_StrLen& rStart, xub_StrLen& rEnd )
//STRIP001 {
//STRIP001  ScInputHandler* pHdl = GetInputHdl();
//STRIP001  if (pHdl)
//STRIP001      pHdl->InputGetSelection( rStart, rEnd );
//STRIP001 }

//STRIP001 void ScModule::InputSetSelection( xub_StrLen nStart, xub_StrLen nEnd )
//STRIP001 {
//STRIP001  ScInputHandler* pHdl = GetInputHdl();
//STRIP001  if (pHdl)
//STRIP001      pHdl->InputSetSelection( nStart, nEnd );
//STRIP001 }

//STRIP001 void ScModule::InputReplaceSelection( const String& rStr )
//STRIP001 {
//STRIP001  ScInputHandler* pHdl = GetInputHdl();
//STRIP001  if (pHdl)
//STRIP001      pHdl->InputReplaceSelection( rStr );
//STRIP001 }

//STRIP001 String ScModule::InputGetFormulaStr()
//STRIP001 {
//STRIP001  ScInputHandler* pHdl = GetInputHdl();
//STRIP001  String aStr;
//STRIP001  if ( pHdl )
//STRIP001      aStr = pHdl->InputGetFormulaStr();
//STRIP001  return aStr;
//STRIP001 }

//STRIP001 void ScModule::ActivateInputWindow( const String* pStrFormula, BOOL bMatrix )
//STRIP001 {
//STRIP001  ScInputHandler* pHdl = GetInputHdl();
//STRIP001  if ( pHdl )
//STRIP001  {
//STRIP001      ScInputWindow* pWin = pHdl->GetInputWindow();
//STRIP001      if ( pStrFormula )
//STRIP001      {
//STRIP001          // Formel uebernehmen
//STRIP001          if ( pWin )
//STRIP001          {
//STRIP001              pWin->SetFuncString( *pStrFormula, FALSE );
//STRIP001              // SetSumAssignMode wegen FALSE nicht noetig
//STRIP001          }
//STRIP001          BYTE nMode = bMatrix ? SC_ENTER_MATRIX : SC_ENTER_NORMAL;
//STRIP001          pHdl->EnterHandler( nMode );
//STRIP001
//STRIP001          //  ohne Invalidate bleibt die Selektion stehen, wenn die Formel unveraendert ist
//STRIP001          if (pWin)
//STRIP001              pWin->TextInvalidate();
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // Abbrechen
//STRIP001          if ( pWin )
//STRIP001          {
//STRIP001              pWin->SetFuncString( EMPTY_STRING, FALSE );
//STRIP001              // SetSumAssignMode wegen FALSE nicht noetig
//STRIP001          }
//STRIP001          pHdl->CancelHandler();
//STRIP001      }
//STRIP001  }
//STRIP001 }

//------------------------------------------------------------------
//
//                  Referenz - Dialoge
//
//------------------------------------------------------------------

//STRIP001 void ScModule::CloseDialogs()
//STRIP001 {
//STRIP001  if( nCurRefDlgId )
//STRIP001      SetRefDialog( nCurRefDlgId, FALSE );
//STRIP001 }

//STRIP001 void ScModule::SetRefDialog( USHORT nId, BOOL bVis, SfxViewFrame* pViewFrm )
//STRIP001 {
//STRIP001  //! move reference dialog handling to view
//STRIP001  //! (only keep function autopilot here for references to other documents)
//STRIP001
//STRIP001  if(nCurRefDlgId==0 || (nId==nCurRefDlgId && !bVis))
//STRIP001  {
//STRIP001      if ( !pViewFrm )
//STRIP001          pViewFrm = SfxViewFrame::Current();
//STRIP001
//STRIP001      // #79379# bindings update causes problems with update of stylist if
//STRIP001      // current style family has changed
//STRIP001      //if ( pViewFrm )
//STRIP001      //  pViewFrm->GetBindings().Update();       // to avoid trouble in LockDispatcher
//STRIP001
//STRIP001      nCurRefDlgId = bVis ? nId : 0 ;             // before SetChildWindow
//STRIP001
//STRIP001      if ( pViewFrm )
//STRIP001      {
//STRIP001          //  store the dialog id also in the view shell
//STRIP001          SfxViewShell* pViewSh = pViewFrm->GetViewShell();
//STRIP001          if ( pViewSh && pViewSh->ISA( ScTabViewShell ) )
//STRIP001              ((ScTabViewShell*)pViewSh)->SetCurRefDlgId( nCurRefDlgId );
//STRIP001
//STRIP001          pViewFrm->SetChildWindow( nId, bVis );
//STRIP001      }
//STRIP001
//STRIP001      SfxApplication* pSfxApp = SFX_APP();
//STRIP001      pSfxApp->Broadcast( SfxSimpleHint( FID_REFMODECHANGED ) );
//STRIP001  }
//STRIP001 }

//STRIP001 void ScModule::OpenTeamDlg()
//STRIP001 {
//STRIP001  if ( !pTeamDlg )
//STRIP001  {
//STRIP001      //  team dialog needs an existing parent window
//STRIP001      //  -> use window from active view (dialog is closed in ViewShellGone)
//STRIP001
//STRIP001      ScTabViewShell* pShell = ScTabViewShell::GetActiveViewShell();
//STRIP001      if (pShell)
//STRIP001          pTeamDlg = new ScTeamDlg( pShell->GetActiveWin() );
//STRIP001  }
//STRIP001  else
//STRIP001      pTeamDlg->Center();
//STRIP001 }

//STRIP001 SfxChildWindow* lcl_GetChildWinFromAnyView( USHORT nId )
//STRIP001 {
//STRIP001  //  first try the current view
//STRIP001
//STRIP001  SfxViewFrame* pViewFrm = SfxViewFrame::Current();
//STRIP001  SfxChildWindow* pChildWnd = pViewFrm->GetChildWindow( nId );
//STRIP001  if ( pChildWnd )
//STRIP001      return pChildWnd;           // found in the current view
//STRIP001
//STRIP001  //  if not found there, get the child window from any open view
//STRIP001  //  it can be open only in one view because nCurRefDlgId is global
//STRIP001
//STRIP001  pViewFrm = SfxViewFrame::GetFirst();
//STRIP001  while ( pViewFrm )
//STRIP001  {
//STRIP001      pChildWnd = pViewFrm->GetChildWindow( nId );
//STRIP001      if ( pChildWnd )
//STRIP001          return pChildWnd;       // found in any view
//STRIP001
//STRIP001      pViewFrm = SfxViewFrame::GetNext( *pViewFrm );
//STRIP001  }
//STRIP001
//STRIP001  return NULL;                    // none found
//STRIP001 }

//STRIP001 BOOL ScModule::IsModalMode(SfxObjectShell* pDocSh)
//STRIP001 {
//STRIP001  //! move reference dialog handling to view
//STRIP001  //! (only keep function autopilot here for references to other documents)
//STRIP001
//STRIP001  BOOL bIsModal = FALSE;
//STRIP001
//STRIP001  if ( nCurRefDlgId )
//STRIP001  {
//STRIP001      SfxChildWindow* pChildWnd = lcl_GetChildWinFromAnyView( nCurRefDlgId );
//STRIP001      if ( pChildWnd )
//STRIP001      {
//STRIP001          ScAnyRefDlg* pRefDlg = (ScAnyRefDlg*)pChildWnd->GetWindow();
//STRIP001          bIsModal = pChildWnd->IsVisible() &&
//STRIP001              !( pRefDlg->IsRefInputMode() && pRefDlg->IsDocAllowed(pDocSh) );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // in 592 and above, the dialog isn't visible in other views
//STRIP001          //  if the dialog is open but can't be accessed, disable input
//STRIP001
//STRIP001          bIsModal = TRUE;
//STRIP001      }
//STRIP001
//STRIP001      //  pChildWnd kann 0 sein, wenn der Dialog nach dem Umschalten
//STRIP001      //  von einer anderen Shell noch nicht erzeugt wurde (z.B. in GetFocus)
//STRIP001  }
//STRIP001  else if (pDocSh)
//STRIP001  {
//STRIP001      ScInputHandler* pHdl = GetInputHdl();
//STRIP001      if ( pHdl )
//STRIP001          bIsModal = pHdl->IsModalMode(pDocSh);
//STRIP001  }
//STRIP001
//STRIP001  return bIsModal;
//STRIP001 }

//STRIP001 BOOL ScModule::IsTableLocked()
//STRIP001 {
//STRIP001  //! move reference dialog handling to view
//STRIP001  //! (only keep function autopilot here for references to other documents)
//STRIP001
//STRIP001  BOOL bLocked = FALSE;
//STRIP001
//STRIP001  //  bisher nur bei ScAnyRefDlg
//STRIP001
//STRIP001  if ( nCurRefDlgId )
//STRIP001  {
//STRIP001      SfxChildWindow* pChildWnd = lcl_GetChildWinFromAnyView( nCurRefDlgId );
//STRIP001      if ( pChildWnd )
//STRIP001          bLocked = ((ScAnyRefDlg*)pChildWnd->GetWindow())->IsTableLocked();
//STRIP001      else
//STRIP001          bLocked = TRUE;     // for other views, see IsModalMode
//STRIP001  }
//STRIP001
//STRIP001  return bLocked;
//STRIP001 }

//STRIP001 BOOL ScModule::IsRefDialogOpen()
//STRIP001 {
//STRIP001  //! move reference dialog handling to view
//STRIP001  //! (only keep function autopilot here for references to other documents)
//STRIP001
//STRIP001  BOOL bIsOpen = FALSE;
//STRIP001
//STRIP001  if ( nCurRefDlgId )
//STRIP001  {
//STRIP001      SfxChildWindow* pChildWnd = lcl_GetChildWinFromAnyView( nCurRefDlgId );
//STRIP001      if ( pChildWnd )
//STRIP001          bIsOpen = pChildWnd->IsVisible();
//STRIP001      else
//STRIP001          bIsOpen = TRUE;     // for other views, see IsModalMode
//STRIP001  }
//STRIP001
//STRIP001  return bIsOpen;
//STRIP001 }

/*N*/ BOOL ScModule::IsFormulaMode()
/*N*/ {
/*N*/   //! move reference dialog handling to view
/*N*/   //! (only keep function autopilot here for references to other documents)
/*N*/
/*N*/   BOOL bIsFormula = FALSE;
/*N*/
/*N*/   if ( nCurRefDlgId )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 SfxChildWindow* pChildWnd = lcl_GetChildWinFromAnyView( nCurRefDlgId );
//STRIP001 /*?*/        if ( pChildWnd )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            ScAnyRefDlg* pRefDlg = (ScAnyRefDlg*)pChildWnd->GetWindow();
//STRIP001 /*?*/            bIsFormula = pChildWnd->IsVisible() && pRefDlg->IsRefInputMode();
//STRIP001 /*?*/        }
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

//STRIP001 void lcl_MarkedTabs( const ScMarkData& rMark, USHORT& rStartTab, USHORT& rEndTab )
//STRIP001 {
//STRIP001  if (rMark.GetSelectCount() > 1)
//STRIP001  {
//STRIP001      BOOL bFirst = TRUE;
//STRIP001      for (USHORT i=0; i<=MAXTAB; i++)
//STRIP001          if (rMark.GetTableSelect(i))
//STRIP001          {
//STRIP001              if (bFirst)
//STRIP001                  rStartTab = i;
//STRIP001              rEndTab = i;
//STRIP001              bFirst = FALSE;
//STRIP001          }
//STRIP001  }
//STRIP001 }

//STRIP001 void ScModule::SetReference( const ScRange& rRef, ScDocument* pDoc,
//STRIP001                                  const ScMarkData* pMarkData )
//STRIP001 {
//STRIP001  //! move reference dialog handling to view
//STRIP001  //! (only keep function autopilot here for references to other documents)
//STRIP001
//STRIP001  //  in Ref-Dialogen wird hiermit auch das Zoom-In ausgeloest,
//STRIP001  //  wenn Start und Ende der Ref unterschiedlich sind
//STRIP001
//STRIP001  ScRange aNew = rRef;
//STRIP001  aNew.Justify();                 // immer "richtig herum"
//STRIP001
//STRIP001  if( nCurRefDlgId )
//STRIP001  {
//STRIP001      SfxChildWindow* pChildWnd = lcl_GetChildWinFromAnyView( nCurRefDlgId );
//STRIP001      DBG_ASSERT( pChildWnd, "NoChildWin" );
//STRIP001      if ( pChildWnd )
//STRIP001      {
//STRIP001          if ( nCurRefDlgId == SID_OPENDLG_CONSOLIDATE && pMarkData )
//STRIP001          {
//STRIP001              USHORT nStartTab = aNew.aStart.Tab();
//STRIP001              USHORT nEndTab   = aNew.aEnd.Tab();
//STRIP001              lcl_MarkedTabs( *pMarkData, nStartTab, nEndTab );
//STRIP001              aNew.aStart.SetTab(nStartTab);
//STRIP001              aNew.aEnd.SetTab(nEndTab);
//STRIP001          }
//STRIP001
//STRIP001          ScAnyRefDlg* pRefDlg = (ScAnyRefDlg*)pChildWnd->GetWindow();
//STRIP001
//STRIP001          //  hide the (color) selection now instead of later from LoseFocus,
//STRIP001          //  don't abort the ref input that causes this call (bDoneRefMode = FALSE)
//STRIP001          pRefDlg->HideReference( FALSE );
//STRIP001          pRefDlg->SetReference( aNew, pDoc );
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      ScInputHandler* pHdl = GetInputHdl();
//STRIP001      if (pHdl)
//STRIP001          pHdl->SetReference( aNew, pDoc );
//STRIP001      else
//STRIP001          DBG_ERROR("SetReference ohne Empfaenger");
//STRIP001  }
//STRIP001 }

//STRIP001 void ScModule::AddRefEntry()                     // "Mehrfachselektion"
//STRIP001 {
//STRIP001  //! move reference dialog handling to view
//STRIP001  //! (only keep function autopilot here for references to other documents)
//STRIP001
//STRIP001  if ( nCurRefDlgId )
//STRIP001  {
//STRIP001      SfxChildWindow* pChildWnd = lcl_GetChildWinFromAnyView( nCurRefDlgId );
//STRIP001      DBG_ASSERT( pChildWnd, "NoChildWin" );
//STRIP001      if ( pChildWnd )
//STRIP001      {
//STRIP001          ScAnyRefDlg* pRefDlg = (ScAnyRefDlg*)pChildWnd->GetWindow();
//STRIP001          pRefDlg->AddRefEntry();
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      ScInputHandler* pHdl = GetInputHdl();
//STRIP001      if (pHdl)
//STRIP001          pHdl->AddRefEntry();
//STRIP001  }
//STRIP001 }

//STRIP001 void ScModule::EndReference()
//STRIP001 {
//STRIP001  //! move reference dialog handling to view
//STRIP001  //! (only keep function autopilot here for references to other documents)
//STRIP001
//STRIP001  //  in Ref-Dialogen wird hiermit auch das Zoom-In wieder aufgehoben
//STRIP001
//STRIP001  //! ShowRefFrame am InputHdl, wenn der Funktions-AP offen ist ???
//STRIP001
//STRIP001  if ( nCurRefDlgId )
//STRIP001  {
//STRIP001      SfxChildWindow* pChildWnd = lcl_GetChildWinFromAnyView( nCurRefDlgId );
//STRIP001      DBG_ASSERT( pChildWnd, "NoChildWin" );
//STRIP001      if ( pChildWnd )
//STRIP001      {
//STRIP001          ScAnyRefDlg* pRefDlg = (ScAnyRefDlg*)pChildWnd->GetWindow();
//STRIP001          pRefDlg->SetActive();
//STRIP001      }
//STRIP001  }
//STRIP001 }

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

void lcl_CheckNeedsRepaint( ScDocShell* pDocShell )
{
    DBG_ASSERT(0, "STRIP"); //STRIP001 SfxViewFrame* pFrame = SfxViewFrame::GetFirst( pDocShell );
//STRIP001  while ( pFrame )
//STRIP001  {
//STRIP001      SfxViewShell* p = pFrame->GetViewShell();
//STRIP001      ScTabViewShell* pViewSh = PTR_CAST(ScTabViewShell,p);
//STRIP001      if ( pViewSh )
//STRIP001          pViewSh->CheckNeedsRepaint();
//STRIP001      pFrame = SfxViewFrame::GetNext( *pFrame, pDocShell );
//STRIP001  }
}

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
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 BOOL bLinks = pDoc->IdleCheckLinks();
//STRIP001 /*?*/            BOOL bWidth = pDoc->IdleCalcTextWidth();
//STRIP001 /*?*/            BOOL bSpell = pDoc->ContinueOnlineSpelling();
//STRIP001 /*?*/            if ( bSpell )
//STRIP001 /*?*/                aSpellTimer.Start();                    // da ist noch was
//STRIP001 /*?*/
//STRIP001 /*?*/            bMore = bLinks || bWidth || bSpell;         // ueberhaupt noch was?
//STRIP001 /*?*/
//STRIP001 /*?*/            //  While calculating a Basic formula, a paint event may have occured,
//STRIP001 /*?*/            //  so check the bNeedsRepaint flags for this document's views
//STRIP001 /*?*/            if (bWidth)
//STRIP001 /*?*/                lcl_CheckNeedsRepaint( pDocSh );
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
    DBG_ASSERT(0, "STRIP"); //STRIP001 //STRIP001   if ( Application::AnyInput( INPUT_KEYBOARD ) )
//STRIP001  {
//STRIP001      aSpellTimer.Start();
//STRIP001      return 0;                   // dann spaeter wieder...
//STRIP001  }
//STRIP001
//STRIP001  ScDocShell* pDocSh = PTR_CAST( ScDocShell, SfxObjectShell::Current() );
//STRIP001  if ( pDocSh )
//STRIP001  {
//STRIP001      ScDocument* pDoc = pDocSh->GetDocument();
//STRIP001      if ( pDoc->ContinueOnlineSpelling() )
//STRIP001          aSpellTimer.Start();
//STRIP001  }
    return 0;
}

    //virtuelle Methoden fuer den Optionendialog
//STRIP001 SfxItemSet*   ScModule::CreateItemSet( USHORT nId )
//STRIP001 {
//STRIP001  SfxItemSet*  pRet = 0;
//STRIP001  if(SID_SC_EDITOPTIONS == nId)
//STRIP001  {
//STRIP001      pRet = new SfxItemSet( GetPool(),
//STRIP001                          // TP_CALC:
//STRIP001                          SID_SCDOCOPTIONS,       SID_SCDOCOPTIONS,
//STRIP001                          // TP_VIEW:
//STRIP001                          SID_SCVIEWOPTIONS,      SID_SCVIEWOPTIONS,
//STRIP001                          // TP_INPUT:
//STRIP001                          SID_SC_INPUT_SELECTION,SID_SC_INPUT_MARK_HEADER,
//STRIP001                          SID_SC_INPUT_TEXTWYSIWYG,SID_SC_INPUT_TEXTWYSIWYG,
//STRIP001                             SID_SC_INPUT_REPLCELLSWARN,SID_SC_INPUT_REPLCELLSWARN,
//STRIP001                          // TP_USERLISTS:
//STRIP001                          SCITEM_USERLIST,        SCITEM_USERLIST,
//STRIP001                          // TP_PRINT:
//STRIP001                          SID_SCPRINTOPTIONS, SID_SCPRINTOPTIONS,
//STRIP001                          // TP_GRID:
//STRIP001                          SID_ATTR_GRID_OPTIONS, SID_ATTR_GRID_OPTIONS,
//STRIP001                          //
//STRIP001                          SID_ATTR_METRIC,        SID_ATTR_METRIC,
//STRIP001                          SID_ATTR_DEFTABSTOP,    SID_ATTR_DEFTABSTOP,
//STRIP001                          0 );
//STRIP001
//STRIP001      ScDocShell*     pDocSh = PTR_CAST(ScDocShell,
//STRIP001                                          SfxObjectShell::Current());
//STRIP001      ScDocOptions    aCalcOpt = pDocSh
//STRIP001                          ? pDocSh->GetDocument()->GetDocOptions()
//STRIP001                          : GetDocOptions();
//STRIP001
//STRIP001      ScTabViewShell* pViewSh = PTR_CAST(ScTabViewShell,
//STRIP001                                          SfxViewShell::Current());
//STRIP001      ScViewOptions   aViewOpt = pViewSh
//STRIP001                          ? pViewSh->GetViewData()->GetOptions()
//STRIP001                          : GetViewOptions();
//STRIP001
//STRIP001      ScUserListItem  aULItem( SCITEM_USERLIST );
//STRIP001      ScUserList*     pUL = ScGlobal::GetUserList();
//STRIP001
//STRIP001      //  OFF_APP()->GetOptions( aSet );
//STRIP001
//STRIP001      pRet->Put( SfxUInt16Item( SID_ATTR_METRIC,
//STRIP001                      GetAppOptions().GetAppMetric() ) );
//STRIP001
//STRIP001      // TP_CALC
//STRIP001      pRet->Put( SfxUInt16Item( SID_ATTR_DEFTABSTOP,
//STRIP001                      aCalcOpt.GetTabDistance()));
//STRIP001      pRet->Put( ScTpCalcItem( SID_SCDOCOPTIONS, aCalcOpt ) );
//STRIP001
//STRIP001      // TP_VIEW
//STRIP001      pRet->Put( ScTpViewItem( SID_SCVIEWOPTIONS, aViewOpt ) );
//STRIP001
//STRIP001      // TP_INPUT
//STRIP001      const ScInputOptions& rInpOpt = GetInputOptions();
//STRIP001      pRet->Put( SfxUInt16Item( SID_SC_INPUT_SELECTIONPOS,
//STRIP001                  rInpOpt.GetMoveDir() ) );
//STRIP001      pRet->Put( SfxBoolItem( SID_SC_INPUT_SELECTION,
//STRIP001                  rInpOpt.GetMoveSelection() ) );
//STRIP001      pRet->Put( SfxBoolItem( SID_SC_INPUT_EDITMODE,
//STRIP001                  rInpOpt.GetEnterEdit() ) );
//STRIP001      pRet->Put( SfxBoolItem( SID_SC_INPUT_FMT_EXPAND,
//STRIP001                  rInpOpt.GetExtendFormat() ) );
//STRIP001      pRet->Put( SfxBoolItem( SID_SC_INPUT_RANGEFINDER,
//STRIP001                  rInpOpt.GetRangeFinder() ) );
//STRIP001      pRet->Put( SfxBoolItem( SID_SC_INPUT_REF_EXPAND,
//STRIP001                  rInpOpt.GetExpandRefs() ) );
//STRIP001      pRet->Put( SfxBoolItem( SID_SC_INPUT_MARK_HEADER,
//STRIP001                  rInpOpt.GetMarkHeader() ) );
//STRIP001      pRet->Put( SfxBoolItem( SID_SC_INPUT_TEXTWYSIWYG,
//STRIP001                  rInpOpt.GetTextWysiwyg() ) );
//STRIP001         pRet->Put( SfxBoolItem( SID_SC_INPUT_REPLCELLSWARN,
//STRIP001                     rInpOpt.GetReplaceCellsWarn() ) );
//STRIP001
//STRIP001      // RID_SC_TP_PRINT
//STRIP001      pRet->Put( ScTpPrintItem( SID_SCPRINTOPTIONS, GetPrintOptions() ) );
//STRIP001
//STRIP001      // TP_GRID
//STRIP001      SvxGridItem* pSvxGridItem = aViewOpt.CreateGridItem();
//STRIP001      pRet->Put( *pSvxGridItem );
//STRIP001      delete pSvxGridItem;
//STRIP001
//STRIP001      // TP_USERLISTS
//STRIP001      if ( pUL )
//STRIP001          aULItem.SetUserList( *pUL );
//STRIP001      pRet->Put( aULItem );
//STRIP001
//STRIP001  }
//STRIP001  return pRet;
//STRIP001 }

//STRIP001 void ScModule::ApplyItemSet( USHORT nId, const SfxItemSet& rSet )
//STRIP001 {
//STRIP001  if(SID_SC_EDITOPTIONS == nId)
//STRIP001  {
//STRIP001      ModifyOptions( rSet );
//STRIP001  }
//STRIP001 }

//STRIP001 SfxTabPage*   ScModule::CreateTabPage( USHORT nId, Window* pParent, const SfxItemSet& rSet )
//STRIP001 {
//STRIP001  SfxTabPage* pRet = NULL;
//STRIP001  switch(nId)
//STRIP001  {
//STRIP001      case SID_SC_TP_LAYOUT:          pRet = ScTpLayoutOptions::Create(pParent, rSet); break;
//STRIP001      case SID_SC_TP_CONTENT:         pRet = ScTpContentOptions::Create(pParent, rSet); break;
//STRIP001      case SID_SC_TP_GRID:            pRet = SvxGridTabPage::Create(pParent, rSet); break;
//STRIP001      case SID_SC_TP_USERLISTS:       pRet = ScTpUserLists::Create(pParent, rSet); break;
//STRIP001      case SID_SC_TP_CALC:            pRet = ScTpCalcOptions::Create(pParent, rSet); break;
//STRIP001      case SID_SC_TP_CHANGES:         pRet = ScRedlineOptionsTabPage::Create(pParent, rSet); break;
//STRIP001      case RID_SC_TP_PRINT:           pRet = ScTpPrintOptions::Create(pParent, rSet); break;
//STRIP001      case RID_OFA_TP_INTERNATIONAL:  pRet = ::offapp::InternationalOptionsPage::CreateSc( pParent, rSet ); break;
//STRIP001  }
//STRIP001
//STRIP001  DBG_ASSERT( pRet, "ScModule::CreateTabPage(): no valid ID for TabPage!" );
//STRIP001
//STRIP001  return pRet;
//STRIP001 }

//------------------------------------------------------------------

/*N*/ IMPL_LINK( ScModule, CalcFieldValueHdl, EditFieldInfo*, pInfo )
/*N*/ {
//STRIP001  //! mit ScFieldEditEngine zusammenfassen !!!
//STRIP001
DBG_ASSERT(0, "STRIP"); //STRIP001 //STRIP001   if (pInfo)
//STRIP001  {
//STRIP001      const SvxFieldItem& rField = pInfo->GetField();
//STRIP001      const SvxFieldData* pField = rField.GetField();
//STRIP001
//STRIP001      if (pField && pField->ISA(SvxURLField))
//STRIP001      {
//STRIP001          /******************************************************************
//STRIP001          * URL-Field
//STRIP001          ******************************************************************/
//STRIP001
//STRIP001          const SvxURLField* pURLField = (const SvxURLField*) pField;
//STRIP001          String aURL = pURLField->GetURL();
//STRIP001
//STRIP001          switch ( pURLField->GetFormat() )
//STRIP001          {
//STRIP001              case SVXURLFORMAT_APPDEFAULT: //!!! einstellbar an App???
//STRIP001              case SVXURLFORMAT_REPR:
//STRIP001              {
//STRIP001                  pInfo->SetRepresentation( pURLField->GetRepresentation() );
//STRIP001              }
//STRIP001              break;
//STRIP001
//STRIP001              case SVXURLFORMAT_URL:
//STRIP001              {
//STRIP001                  pInfo->SetRepresentation( aURL );
//STRIP001              }
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001             svtools::ColorConfigEntry eEntry =
//STRIP001                 INetURLHistory::GetOrCreate()->QueryUrl( aURL ) ? svtools::LINKSVISITED : svtools::LINKS;
//STRIP001          pInfo->SetTxtColor( GetColorConfig().GetColorValue(eEntry).nColor );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          DBG_ERROR("unbekannter Feldbefehl");
//STRIP001          pInfo->SetRepresentation(String('?'));
//STRIP001      }
//STRIP001  }
//STRIP001
/*N*/   return 0;
/*N*/ }




