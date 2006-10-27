/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_swmodule.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 00:01:03 $
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


#pragma hdrstop

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif
#ifndef _UIPARAM_HXX
#include <uiparam.hxx>
#endif
#ifndef _SWERROR_H
#include <swerror.h>
#endif

#ifndef _SV_WRKWIN_HXX //autogen
#include <vcl/wrkwin.hxx>
#endif
#ifndef _SV_GRAPH_HXX
#include <vcl/graph.hxx>
#endif
#ifndef _SVX_GALBRWS_HXX_
#include <bf_svx/galbrws.hxx>
#endif
#ifndef _SVDOBJ_HXX //autogen
#include <bf_svx/svdobj.hxx>
#endif
#ifndef _OFF_APP_HXX //autogen
#include <bf_offmgr/app.hxx>
#endif
#ifndef _EHDL_HXX //autogen
#include <svtools/ehdl.hxx>
#endif
#ifndef _OFAACCFG_HXX //autogen
#include <bf_offmgr/ofaaccfg.hxx>
#endif
#ifndef _SVX_FNTSZCTL_HXX //autogen
#include <bf_svx/fntszctl.hxx>
#endif
#ifndef _SVX_FNTCTL_HXX //autogen
#include <bf_svx/fntctl.hxx>
#endif
#ifndef _SVX_PSZCTRL_HXX //autogen
#include <bf_svx/pszctrl.hxx>
#endif
#ifndef _SVX_INSCTRL_HXX //autogen
#include <bf_svx/insctrl.hxx>
#endif
#ifndef _SVX_SELCTRL_HXX //autogen
#include <bf_svx/selctrl.hxx>
#endif
#ifndef _SVX_LINECTRL_HXX //autogen
#include <bf_svx/linectrl.hxx>
#endif
#include <bf_svx/tbxctl.hxx>            //z-Zt falscher includeschutz!
#ifndef _FILLCTRL_HXX //autogen
#include <bf_svx/fillctrl.hxx>
#endif
#ifndef _SVX_TBCONTRL_HXX //autogen
#include <bf_svx/tbcontrl.hxx>
#endif
#ifndef _SVX_VERT_TEXT_TBXCTRL_HXX
#include <bf_svx/verttexttbxctrl.hxx>
#endif
#ifndef _CONTDLG_HXX_ //autogen
#include <bf_svx/contdlg.hxx>
#endif
#ifndef _SVX_LAYCTRL_HXX //autogen
#include <bf_svx/layctrl.hxx>
#endif
#ifndef _SVX_FONTWORK_HXX //autogen
#include <bf_svx/fontwork.hxx>
#endif
#ifndef _TBXALIGN_HXX //autogen
#include <bf_svx/tbxalign.hxx>
#endif
#ifndef _SVX_GRAFCTRL_HXX
#include <bf_svx/grafctrl.hxx>
#endif
#ifndef _SVX_CLIPBOARDCTL_HXX_
#include <bf_svx/clipboardctl.hxx>
#endif
#ifndef _SVX_LBOXCTRL_HXX_
#include <bf_svx/lboxctrl.hxx>
#endif
#ifndef _SVX_DLG_HYPERLINK_HXX //autogen
#include <bf_offmgr/hyprlink.hxx>
#endif
#ifndef _SVSTDARR_STRINGSDTOR
#define _SVSTDARR_STRINGSDTOR
#include <svtools/svstdarr.hxx>
#endif
#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XSINGLESERVICEFACTORY_HPP_
#include <com/sun/star/lang/XSingleServiceFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_SCANNER_XSCANNERMANAGER_HPP_
#include <com/sun/star/scanner/XScannerManager.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XSET_HPP_
#include <com/sun/star/container/XSet.hpp>
#endif
#ifndef _CPPUHELPER_FACTORY_HXX_
#include <cppuhelper/factory.hxx>
#endif
#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif
#ifndef _SVX_VERT_TEXT_TBXCTRL_HXX
#include <bf_svx/verttexttbxctrl.hxx>
#endif
#ifndef _DOCSH_HXX
#include <docsh.hxx>
#endif
#ifndef _SWMODULE_HXX
#include <swmodule.hxx>
#endif
#ifndef _SWTYPES_HXX
#include <swtypes.hxx>
#endif
#ifndef _SWEVENT_HXX
#include <swevent.hxx>
#endif
#ifndef _SWACORR_HXX
#include <swacorr.hxx>
#endif
#ifndef _CMDID_H
#include <cmdid.h>
#endif
#ifndef _DOBJFAC_HXX
#include <dobjfac.hxx>
#endif
#ifndef _INIT_HXX
#include <init.hxx>
#endif
#ifndef _SWPVIEW_HXX //autogen
#include <pview.hxx>
#endif
#ifndef _SWWVIEW_HXX //autogen
#include <wview.hxx>
#endif
#ifndef _SWWDOCSH_HXX //autogen
#include <wdocsh.hxx>
#endif
#ifndef _SWGLOBDOCSH_HXX //autogen
#include <globdoc.hxx>
#endif
#ifndef _SRCVIEW_HXX //autogen
#include <srcview.hxx>
#endif
#ifndef _AUTODOC_HXX //autogen
#include <glshell.hxx>
#endif
#ifndef _SWTABSH_HXX //autogen
#include <tabsh.hxx>
#endif
#ifndef _SWLISTSH_HXX //autogen
#include <listsh.hxx>
#endif
#ifndef _SWGRFSH_HXX //autogen
#include <grfsh.hxx>
#endif
#ifndef _SWOLESH_HXX //autogen
#include <olesh.hxx>
#endif
#ifndef _SWDRAWSH_HXX //autogen
#include <drawsh.hxx>
#endif
#ifndef _SWWDRWFORMSH_HXX //autogen
#include <wformsh.hxx>
#endif
#ifndef _SWDRWTXTSH_HXX //autogen
#include <drwtxtsh.hxx>
#endif
#ifndef _SWBEZIERSH_HXX //autogen
#include <beziersh.hxx>
#endif
#ifndef _SWWTEXTSH_HXX //autogen
#include <wtextsh.hxx>
#endif
#ifndef _SWWFRMSH_HXX //autogen
#include <wfrmsh.hxx>
#endif
#ifndef _DRFORMSH_HXX
#include <drformsh.hxx>
#endif
#ifndef _WGRFSH_HXX
#include <wgrfsh.hxx>
#endif
#ifndef _WOLESH_HXX
#include <wolesh.hxx>
#endif
#ifndef _WLISTSH_HXX
#include <wlistsh.hxx>
#endif
#ifndef _WTABSH_HXX
#include <wtabsh.hxx>
#endif
#ifndef _WDRWBASE_HXX
#include <wdrwbase.hxx>
#endif
#ifndef _NAVIPI_HXX //autogen
#include <navipi.hxx>
#endif
#ifndef _CHARTINS_HXX //autogen
#include <chartins.hxx>
#endif
#ifndef SW_INPUTWIN_HXX //autogen
#include <inputwin.hxx>
#endif
#ifndef _USRPREF_HXX //autogen
#include <usrpref.hxx>
#endif
#ifndef _UINUMS_HXX //autogen
#include <uinums.hxx>
#endif
#ifndef _PRTOPT_HXX //autogen
#include <prtopt.hxx>
#endif
#ifndef _BOOKCTRL_HXX
#include <bookctrl.hxx>
#endif
#ifndef _TMPLCTRL_HXX
#include <tmplctrl.hxx>
#endif
#ifndef _TBLCTRL_HXX
#include <tblctrl.hxx>
#endif
#ifndef _ZOOMCTRL_HXX
#include <zoomctrl.hxx>
#endif
#ifndef _SWSTBCTL_HXX
#include <swstbctl.hxx>
#endif
#ifndef _WORKCTRL_HXX
#include <workctrl.hxx>
#endif
#ifndef _TBXANCHR_HXX
#include <tbxanchr.hxx>
#endif
#ifndef _FLDWRAP_HXX
#include <fldwrap.hxx>
#endif
#ifndef _REDLNDLG_HXX
#include <redlndlg.hxx>
#endif
#ifndef _SYNCBTN_HXX
#include <syncbtn.hxx>
#endif
#ifndef _HDFTCTRL_HXX
#include <hdftctrl.hxx>
#endif
#ifndef _MODOPT_HXX //autogen
#include <modcfg.hxx>
#endif
#ifndef _FONTCFG_HXX //autogen
#include <fontcfg.hxx>
#endif
#ifndef _SFX_EVENTCONF_HXX
#include <bf_sfx2/evntconf.hxx>
#endif
#ifndef _SFX_APPUNO_HXX //autogen
#include <bf_sfx2/appuno.hxx>
#endif
#ifndef _SWATRSET_HXX //autogen
#include <swatrset.hxx>
#endif
#ifndef _IDXMRK_HXX
#include <idxmrk.hxx>
#endif
#ifndef _DLELSTNR_HXX_
#include <dlelstnr.hxx>
#endif
#ifndef _BARCFG_HXX
#include <barcfg.hxx>
#endif
#ifndef _SVX_RUBYDLG_HXX_
#include <bf_svx/rubydialog.hxx>
#endif
// OD 14.02.2003 #107424#
#ifndef INCLUDED_SVTOOLS_COLORCFG_HXX
#include <svtools/colorcfg.hxx>
#endif

#include <svtools/moduleoptions.hxx>

#include <app.hrc>
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {
ResMgr *pSwResMgr = 0;
sal_Bool    bNoInterrupt    = sal_False;

#ifndef PROFILE
// Code zum Initialisieren von Statics im eigenen Code-Segment
#pragma code_seg( "SWSTATICS" )
#endif

#ifndef PROFILE
#pragma code_seg()
#endif

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::scanner;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::linguistic2;
using namespace ::rtl;

#define C2S(cChar) String::CreateFromAscii(cChar)

/*N*/ TYPEINIT1( SwModuleDummy, SfxModule );
/*N*/ TYPEINIT1( SwModule, SwModuleDummy );


//************************************************************************

/*N*/ SwModule::SwModule( SvFactory* pFact,
/*N*/                   SvFactory* pWebFact,
/*N*/                   SvFactory* pGlobalFact )
/*N*/   : SwModuleDummy( SFX_APP()->CreateResManager( "bf_sw" ), sal_False, pFact,  //STRIP005
/*N*/                    pWebFact, pGlobalFact ),
/*N*/   pModuleConfig(0),
/*N*/   pView(0),
/*N*/   pChapterNumRules(0),
/*N*/   pStdFontConfig(0),
/*N*/   pPrtOpt(0),
/*N*/   pWebPrtOpt(0),
/*N*/   pWebUsrPref(0),
/*N*/   pUsrPref(0),
/*N*/   pToolbarConfig(0),
/*N*/   pWebToolbarConfig(0),
/*N*/   pDBConfig(0),
/*N*/     pColorConfig(0),
/*N*/     pAccessibilityOptions(0),
/*N*/     pCTLOptions(0),
/*N*/   pClipboard(0),
/*N*/   pDragDrop(0),
/*N*/   pXSelection(0),
/*N*/   pAttrPool(0),
/*N*/   bAuthorInitialised(sal_False),
/*N*/   bEmbeddedLoadSave( sal_False )
/*N*/ {
/*N*/   SetName( String::CreateFromAscii("StarWriter") );
/*N*/   pSwResMgr = GetResMgr();
/*N*/   pErrorHdl = new SfxErrorHandler( RID_SW_ERRHDL,
/*N*/                                    ERRCODE_AREA_SW,
/*N*/                                    ERRCODE_AREA_SW_END,
/*N*/                                    pSwResMgr );
/*N*/
/*N*/   SfxEventConfiguration::RegisterEvent(SW_EVENT_MAIL_MERGE, SW_RES(STR_PRINT_MERGE_MACRO), String::CreateFromAscii("OnMailMerge"));
/*N*/   SfxEventConfiguration::RegisterEvent(SW_EVENT_MAIL_MERGE_END, SW_RES(STR_PRINT_MERGE_MACRO), String::CreateFromAscii("OnMailMergeFinished"));
/*N*/   SfxEventConfiguration::RegisterEvent(SW_EVENT_PAGE_COUNT, SW_RES(STR_PAGE_COUNT_MACRO), String::CreateFromAscii("OnPageCountChange"));
/*N*/   pModuleConfig = new SwModuleOptions;
/*N*/
/*N*/   //Die brauchen wie sowieso
/*N*/   pToolbarConfig = new SwToolbarConfigItem( sal_False );
/*N*/   pWebToolbarConfig = new SwToolbarConfigItem( sal_True );
/*N*/
/*N*/   pStdFontConfig = new SwStdFontConfig;
/*N*/
/*N*/   pAuthorNames = new SvStringsDtor(5, 1); // Alle Redlining-Autoren
/*N*/
/*N*/   //JP 18.10.96: SvxAutocorrect gegen die SwAutocorrect austauschen
/*N*/   OfficeApplication* pOffApp = OFF_APP();
/*N*/   OfaAutoCorrCfg* pACfg = pOffApp->GetAutoCorrConfig();
/*N*/   if( pACfg )
/*N*/   {
/*N*/       const SvxAutoCorrect* pOld = pACfg->GetAutoCorrect();
/*N*/       pACfg->SetAutoCorrect(new SwAutoCorrect( *pOld ));
/*N*/   }
/*N*/   StartListening( *pOffApp );
/*N*/
/*N*/   Reference< XMultiServiceFactory > xMgr( ::legacy_binfilters::getLegacyProcessServiceFactory() );
/*N*/   if( xMgr.is() )
/*N*/   {
/*N*/       m_xScannerManager = Reference< XScannerManager >(
/*N*/                       xMgr->createInstance( OUString::createFromAscii( "com.sun.star.scanner.ScannerManager" ) ),
/*N*/                       UNO_QUERY );
/*N*/
/*N*/ //        if( m_xScannerManager.is() )
/*N*/ //        {
/*N*/ //            m_xScannerListener = Reference< lang::XEventListener >(
/*N*/ //                                        OWeakObject* ( new ScannerEventListener( this ) ), UNO_QUERY );
/*N*/ //        }
/*N*/   }
/*N*/
/*N*/     // OD 14.02.2003 #107424# - init color configuration
/*N*/     // member <pColorConfig> is created and the color configuration is applied
/*N*/     // at the view options.
/*N*/     GetColorConfig();
/*N*/ }

//************************************************************************

/*N*/ SwModule::~SwModule()
/*N*/ {
/*N*/   SetPool(0);
/*N*/   delete pAttrPool;
/*N*/   delete pErrorHdl;
/*N*/   EndListening( *OFF_APP() );
/*N*/ }

//************************************************************************

/*N*/ void SwModule::CreateLngSvcEvtListener()
/*N*/ {
/*N*/     if (!xLngSvcEvtListener.is())
/*N*/         xLngSvcEvtListener = new SwLinguServiceEventListener;
/*N*/ }

//************************************************************************

/*N*/ void SwDLL::RegisterFactories()
/*N*/ {
/*N*/   //Diese Id's duerfen nicht geaendert werden. Mittels der Id's wird vom
/*N*/   //Sfx die sdbcx::View (Dokumentansicht wiederherstellen) erzeugt.
/*N*/     if ( SvtModuleOptions().IsWriter() )
/*N*/         SwView::RegisterFactory         ( 2 );
/*N*/
/*N*/   SwWebView::RegisterFactory      ( 5 );
/*N*/
/*N*/     if ( SvtModuleOptions().IsWriter() )
/*N*/     {
/*N*/         SwSrcView::RegisterFactory      ( 6 );
/*N*/         SwPagePreView::RegisterFactory  ( 7 );
/*N*/     }
/*N*/ }

//************************************************************************


/*N*/ void SwDLL::RegisterInterfaces()
/*N*/ {
/*N*/   SwModule* pMod = SW_MOD();
/*N*/   SwModule::RegisterInterface( pMod );
/*N*/   SwDocShell::RegisterInterface( pMod );
/*N*/   SwWebDocShell::RegisterInterface( pMod );
/*N*/   SwGlosDocShell::RegisterInterface( pMod );
/*N*/   SwWebGlosDocShell::RegisterInterface( pMod );
/*N*/   SwView::RegisterInterface( pMod );
/*N*/   SwWebView::RegisterInterface( pMod );
/*N*/   SwPagePreView::RegisterInterface( pMod );
/*N*/   SwSrcView::RegisterInterface( pMod );
/*N*/
/*N*/
/*N*/   SwBaseShell::RegisterInterface(pMod);
/*N*/   SwTextShell::RegisterInterface(pMod);
/*N*/   SwTableShell::RegisterInterface(pMod);
/*N*/   SwListShell::RegisterInterface(pMod);
/*N*/   SwFrameShell::RegisterInterface(pMod);
/*N*/   SwDrawBaseShell::RegisterInterface(pMod);
/*N*/   SwDrawShell::RegisterInterface(pMod);
/*N*/   SwDrawFormShell::RegisterInterface(pMod);
/*N*/   SwDrawTextShell::RegisterInterface(pMod);
/*N*/   SwBezierShell::RegisterInterface(pMod);
/*N*/   SwGrfShell::RegisterInterface(pMod);
/*N*/   SwOleShell::RegisterInterface(pMod);
/*N*/   SwWebTextShell::RegisterInterface(pMod);
/*N*/   SwWebFrameShell::RegisterInterface(pMod);
/*N*/   SwWebGrfShell::RegisterInterface(pMod);
/*N*/   SwWebListShell::RegisterInterface(pMod);
/*N*/   SwWebTableShell::RegisterInterface(pMod);
/*N*/   SwWebDrawBaseShell::RegisterInterface(pMod);
/*N*/   SwWebDrawFormShell::RegisterInterface(pMod);
/*N*/   SwWebOleShell::RegisterInterface(pMod);
/*N*/ }

//************************************************************************

/*N*/ void SwDLL::RegisterControls()
/*N*/ {
/*N*/   SwModule* pMod = SW_MOD();
/*N*/   SvxTbxCtlDraw::RegisterControl(SID_INSERT_DRAW, pMod );
/*N*/   SvxTbxCtlAlign::RegisterControl(SID_OBJECT_ALIGN, pMod );
/*N*/   SwTbxAnchor::RegisterControl(FN_TOOL_ANKER, pMod );
/*N*/   SwTbxInsertCtrl::RegisterControl(FN_INSERT_CTRL, pMod );
/*N*/   SwTbxInsertCtrl::RegisterControl(FN_INSERT_OBJ_CTRL, pMod );
/*N*/   SwTbxAutoTextCtrl::RegisterControl(FN_INSERT_FIELD_CTRL, pMod );
/*N*/   SwTbxAutoTextCtrl::RegisterControl(FN_GLOSSARY_DLG, pMod );
/*N*/
/*N*/   SvxClipBoardControl::RegisterControl(SID_PASTE, pMod );
/*N*/   SvxUndoRedoControl::RegisterControl(SID_UNDO, pMod );
/*N*/   SvxUndoRedoControl::RegisterControl(SID_REDO, pMod );
/*N*/
/*N*/   SvxFillToolBoxControl::RegisterControl(SID_ATTR_FILL_STYLE, pMod );
/*N*/   SvxLineStyleToolBoxControl::RegisterControl(SID_ATTR_LINE_STYLE, pMod );
/*N*/   SvxLineWidthToolBoxControl::RegisterControl(SID_ATTR_LINE_WIDTH, pMod );
/*N*/   SvxLineColorToolBoxControl::RegisterControl(SID_ATTR_LINE_COLOR, pMod );
/*N*/   SvxLineEndToolBoxControl::RegisterControl(SID_ATTR_LINEEND_STYLE, pMod );
/*N*/
/*N*/   SvxFontNameToolBoxControl::RegisterControl(SID_ATTR_CHAR_FONT, pMod );
/*N*/   SvxFontHeightToolBoxControl::RegisterControl(SID_ATTR_CHAR_FONTHEIGHT, pMod );
/*N*/   SvxFontColorToolBoxControl::RegisterControl(SID_ATTR_CHAR_COLOR, pMod );
/*N*/   SvxFontColorExtToolBoxControl::RegisterControl(SID_ATTR_CHAR_COLOR2, pMod );
/*N*/   SvxFontColorExtToolBoxControl::RegisterControl(SID_ATTR_CHAR_COLOR_BACKGROUND, pMod );
/*N*/   SvxStyleToolBoxControl::RegisterControl(SID_STYLE_APPLY, pMod );
/*N*/   SvxColorToolBoxControl::RegisterControl(SID_BACKGROUND_COLOR, pMod );
/*N*/   SvxFrameToolBoxControl::RegisterControl(SID_ATTR_BORDER, pMod );
/*N*/   SvxFrameLineStyleToolBoxControl::RegisterControl(SID_FRAME_LINESTYLE, pMod );
/*N*/   SvxFrameLineColorToolBoxControl::RegisterControl(SID_FRAME_LINECOLOR, pMod );
/*N*/
/*N*/   SvxColumnsToolBoxControl::RegisterControl(FN_INSERT_FRAME_INTERACT, pMod );
/*N*/   SvxColumnsToolBoxControl::RegisterControl(FN_INSERT_FRAME, pMod );
/*N*/     SvxColumnsToolBoxControl::RegisterControl(FN_INSERT_REGION, pMod );
/*N*/   SvxTableToolBoxControl::RegisterControl(FN_INSERT_TABLE, pMod );
/*N*/   SvxTableToolBoxControl::RegisterControl(FN_SHOW_MULTIPLE_PAGES, pMod );
/*N*/
/*N*/
/*N*/   SwZoomControl::RegisterControl(SID_ATTR_ZOOM, pMod );
/*N*/     SwPreviewZoomControl::RegisterControl(FN_PREVIEW_ZOOM, pMod);
/*N*/   SwHyperlinkControl::RegisterControl(FN_STAT_HYPERLINKS, pMod );
/*N*/   SvxPosSizeStatusBarControl::RegisterControl(0, pMod );
/*N*/   SvxInsertStatusBarControl::RegisterControl(0, pMod );
/*N*/   SvxSelectionModeControl::RegisterControl(FN_STAT_SELMODE, pMod );
/*N*/
/*N*/   SwBookmarkControl::RegisterControl(FN_STAT_PAGE, pMod );
/*N*/   SwTemplateControl::RegisterControl(FN_STAT_TEMPLATE, pMod );
/*N*/
/*N*/   SwTableOptimizeCtrl::RegisterControl(FN_OPTIMIZE_TABLE, pMod);
/*N*/
/*N*/   SfxMenuControl::RegisterControl(FN_FRAME_ALIGN_VERT_TOP, pMod );
/*N*/   SfxMenuControl::RegisterControl(FN_FRAME_ALIGN_VERT_BOTTOM, pMod );
/*N*/   SfxMenuControl::RegisterControl(FN_FRAME_ALIGN_VERT_CENTER, pMod );
/*N*/
/*N*/   SwHeadFootMenuControl::RegisterControl( FN_INSERT_PAGEHEADER, pMod );
/*N*/   SwHeadFootMenuControl::RegisterControl( FN_INSERT_PAGEFOOTER, pMod );
/*N*/
/*N*/   SvxHyperlinkDlgWrapper::RegisterChildWindow( sal_False, pMod );
/*N*/   SvxFontWorkChildWindow::RegisterChildWindow( sal_False, pMod );
/*N*/   SwFldDlgWrapper::RegisterChildWindow( sal_False, pMod );
/*N*/   SvxContourDlgChildWindow::RegisterChildWindow( sal_False, pMod );
/*N*/   SwInsertChartChild::RegisterChildWindow( sal_False, pMod );
/*N*/   SwNavigationChild::RegisterChildWindowContext( pMod );
/*N*/   SwInputChild::RegisterChildWindow( sal_False, pMod );
/*N*/   SwRedlineAcceptChild::RegisterChildWindow( sal_False, pMod );
/*N*/   SwSyncChildWin::RegisterChildWindow( sal_True, pMod );
/*N*/   SwInsertIdxMarkWrapper::RegisterChildWindow( sal_False, pMod );
/*N*/   SwInsertAuthMarkWrapper::RegisterChildWindow( sal_False, pMod );
/*N*/   SvxRubyChildWindow::RegisterChildWindow( sal_False, pMod);
/*N*/
/*N*/   SvxGrafRedToolBoxControl::RegisterControl( SID_ATTR_GRAF_RED, pMod );
/*N*/   SvxGrafGreenToolBoxControl::RegisterControl( SID_ATTR_GRAF_GREEN, pMod );
/*N*/   SvxGrafBlueToolBoxControl::RegisterControl( SID_ATTR_GRAF_BLUE, pMod );
/*N*/   SvxGrafLuminanceToolBoxControl::RegisterControl( SID_ATTR_GRAF_LUMINANCE, pMod );
/*N*/   SvxGrafContrastToolBoxControl::RegisterControl( SID_ATTR_GRAF_CONTRAST, pMod );
/*N*/   SvxGrafGammaToolBoxControl::RegisterControl( SID_ATTR_GRAF_GAMMA, pMod );
/*N*/   SvxGrafTransparenceToolBoxControl::RegisterControl( SID_ATTR_GRAF_TRANSPARENCE, pMod );
/*N*/   SvxGrafModeToolBoxControl::RegisterControl( SID_ATTR_GRAF_MODE, pMod );
/*N*/     SvxGrafFilterToolBoxControl::RegisterControl( SID_GRFFILTER, pMod );
/*N*/     SvxVertTextTbxCtrl::RegisterControl(SID_TEXTDIRECTION_LEFT_TO_RIGHT, pMod);
/*N*/     SvxVertTextTbxCtrl::RegisterControl(SID_TEXTDIRECTION_TOP_TO_BOTTOM, pMod);
/*N*/     SvxVertTextTbxCtrl::RegisterControl(SID_DRAW_CAPTION_VERTICAL, pMod);
/*N*/     SvxVertTextTbxCtrl::RegisterControl(SID_DRAW_TEXT_VERTICAL, pMod);

/*M*/     SvxCTLTextTbxCtrl::RegisterControl(SID_ATTR_PARA_LEFT_TO_RIGHT, pMod);
/*M*/     SvxCTLTextTbxCtrl::RegisterControl(SID_ATTR_PARA_RIGHT_TO_LEFT, pMod);
/*M*/
/*N*/   GalleryChildWindow::RegisterChildWindow(0, pMod);
/*N*/ }


/*************************************************************************
|*
|* Modul laden (nur Attrappe fuer das Linken der DLL)
|*
\************************************************************************/


/*N*/ SfxModule* SwModuleDummy::Load()
/*N*/ {
/*N*/   return (NULL);
/*N*/ }

/*N*/ SwModuleDummy::~SwModuleDummy()
/*N*/ {
/*N*/ }


/*************************************************************************
|*
|* Modul laden
|*
\************************************************************************/

/*N*/ SfxModule* SwModule::Load()
/*N*/ {
/*N*/   return (this);
/*N*/ }

/*-----------------15.03.98 11:50-------------------

--------------------------------------------------*/
/*Reflection*   SwModule::GetReflection( UsrUik aUIK )
{
    DBG_ERROR("GetReflection - new method not yet available")
    return 0;

    if(aUIK == ::getCppuType((const uno::Reference< text::XModule >*)0))
        return ::getCppuType((const SwXModule*)0)();
    else if(aUIK == ::getCppuType((const uno::Reference< text::XAutoTextContainer >*)0)())
        return ::getCppuType((const SwXAutoTextContainer*)0)();
    else
        return SfxModule::GetReflection(aUIK);
}*/
/* -----------------20.04.99 10:46-------------------
 *
 * --------------------------------------------------*/
/*N*/ void  SwModule::InitAttrPool()
/*N*/ {
/*N*/   DBG_ASSERT(!pAttrPool, "Pool ist schon da!")
/*N*/   pAttrPool = new SwAttrPool(0);
/*N*/   SetPool(pAttrPool);
/*N*/ }
/* -----------------20.04.99 10:46-------------------
 *
 * --------------------------------------------------*/
/*N*/ void  SwModule::RemoveAttrPool()
/*N*/ {
/*N*/   SetPool(0);
/*N*/   DELETEZ(pAttrPool);
/*N*/ }


}
