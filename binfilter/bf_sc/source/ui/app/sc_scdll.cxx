/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_scdll.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2007-04-26 07:11:10 $
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

#include <bf_svx/eeitem.hxx>
#define ITEMID_FIELD EE_FEATURE_FIELD

#include "scitems.hxx"      // fuer tbxctrls etc.
#include "scmod.hxx"
#include "scresid.hxx"
#include "bf_sc.hrc"
#include "cfgids.hxx"

//! die Registrierung wird wegen CLOOKs in ein eigenes File wandern muessen...

// Interface-Registrierung
#include "docsh.hxx"
#include "tabvwsh.hxx"
#include "prevwsh.hxx"
#include "drformsh.hxx"
#include "drtxtob.hxx"
#include "editsh.hxx"
#include "pivotsh.hxx"
#include "auditsh.hxx"
#include "cellsh.hxx"
#include "oleobjsh.hxx"
#include "chartsh.hxx"
#include "graphsh.hxx"
#include "pgbrksh.hxx"

#include "docpool.hxx"
#include "appoptio.hxx"

// Controls

#include <bf_svx/tbxalign.hxx>
#include <bf_svx/tbxctl.hxx>
#include <bf_svx/fillctrl.hxx>
#include <bf_svx/linectrl.hxx>
#include <bf_svx/tbcontrl.hxx>
#include <bf_svx/selctrl.hxx>
#include <bf_svx/insctrl.hxx>
#include <bf_svx/zoomctrl.hxx>

#ifndef _SVX_ITEMDATA_HXX
#include <bf_svx/itemdata.hxx>
#endif

#include <bf_svx/modctrl.hxx>
#include <bf_svx/pszctrl.hxx>
#include <bf_svx/grafctrl.hxx>
#include <bf_svx/galbrws.hxx>
#include <bf_svx/clipboardctl.hxx>
#include <bf_svx/lboxctrl.hxx>
#ifndef _SVX_VERT_TEXT_TBXCTRL_HXX
#include <bf_svx/verttexttbxctrl.hxx>
#endif

#ifndef _SVTOOLS_IMGDEF_HXX
#include <svtools/imgdef.hxx>
#endif

#include "tbinsert.hxx"

// Child-Windows
#include "reffact.hxx"
#include "navipi.hxx"
#include "inputwin.hxx"
#include <bf_svx/fontwork.hxx>
#include <bf_offmgr/hyprlink.hxx>
#include <bf_svx/imapdlg.hxx>

#include <bf_svx/svdfield.hxx>      //  SdrRegisterFieldClasses
#include <rtl/logfile.hxx>

#include "dwfunctr.hxx"
namespace binfilter {

//------------------------------------------------------------------

/*N*/ ScResId::ScResId( USHORT nId ) :
/*N*/   ResId( nId, *SC_MOD()->GetResMgr() )
/*N*/ {
/*N*/ }

//------------------------------------------------------------------

/*N*/ void ScDLL::Init()
/*N*/ {
/*N*/   RTL_LOGFILE_CONTEXT_AUTHOR ( aLog, "sc", "nn93723", "ScDLL::Init" );
/*N*/
/*N*/   // called directly after loading the DLL
/*N*/   // do whatever you want, you may use Sxx-DLL too
/*N*/
/*N*/   ScDocumentPool::InitVersionMaps();  // wird im ScModule ctor gebraucht
/*N*/
/*N*/   // the ScModule must be created
/*N*/   ScModuleDummy **ppShlPtr = (ScModuleDummy**) GetAppData(BF_SHL_CALC);
/*N*/   SvFactory *pFact = (SvFactory*)(*ppShlPtr)->pScDocShellFactory;
/*N*/   delete (*ppShlPtr);
/*N*/   ScModule* pMod = new ScModule((SfxObjectFactory*)pFact);
/*N*/   (*ppShlPtr) = pMod;
/*N*/   (*ppShlPtr)->pScDocShellFactory = pFact;
/*N*/
/*N*/   ScGlobal::Init();       // erst wenn der ResManager initialisiert ist
/*N*/                           //  erst nach ScGlobal::Init duerfen die App-Optionen
/*N*/                           //  initialisiert werden
/*N*/
/*N*/   // register your view-factories here
/*N*/
/*N*/   ScTabViewShell      ::RegisterFactory(1);
/*N*/   ScPreviewShell      ::RegisterFactory(2);
/*N*/
/*N*/   // register your shell-interfaces here
/*N*/
/*N*/   ScModule            ::RegisterInterface(pMod);
/*N*/   ScDocShell          ::RegisterInterface(pMod);
/*N*/   ScTabViewShell      ::RegisterInterface(pMod);
/*N*/   ScPreviewShell      ::RegisterInterface(pMod);
/*N*/   ScDrawShell         ::RegisterInterface(pMod);
/*N*/   ScDrawFormShell     ::RegisterInterface(pMod);
/*N*/   ScDrawTextObjectBar ::RegisterInterface(pMod);
/*N*/   ScEditShell         ::RegisterInterface(pMod);
/*N*/   ScPivotShell        ::RegisterInterface(pMod);
/*N*/   ScAuditingShell     ::RegisterInterface(pMod);
/*N*/   ScFormatShell       ::RegisterInterface(pMod);
/*N*/   ScCellShell         ::RegisterInterface(pMod);
/*N*/   ScOleObjectShell    ::RegisterInterface(pMod);
/*N*/   ScChartShell        ::RegisterInterface(pMod);
/*N*/   ScGraphicShell      ::RegisterInterface(pMod);
/*N*/   ScPageBreakShell    ::RegisterInterface(pMod);
/*N*/
/*N*/
/*N*/
/*N*/   // register your controllers here
/*N*/
/*N*/   ScDocShell::Factory().RegisterMenuBar( ScResId(SCCFG_MENUBAR) );
/*N*/   ScDocShell::Factory().RegisterPluginMenuBar( ScResId(SCCFG_PLUGINMENU) );
/*N*/   ScDocShell::Factory().RegisterAccel( ScResId(SCCFG_ACCELERATOR) );
/*N*/
/*N*/   //  eigene Controller
/*N*/   ScTbxInsertCtrl     ::RegisterControl(SID_TBXCTL_INSERT, pMod);
/*N*/   ScTbxInsertCtrl     ::RegisterControl(SID_TBXCTL_INSCELLS, pMod);
/*N*/   ScTbxInsertCtrl     ::RegisterControl(SID_TBXCTL_INSOBJ, pMod);
/*N*/
/*N*/   //  Svx-Toolbox-Controller
/*N*/   SvxTbxCtlDraw                   ::RegisterControl(SID_INSERT_DRAW, pMod);
/*N*/   SvxTbxCtlAlign                  ::RegisterControl(SID_OBJECT_ALIGN, pMod);
/*N*/   SvxFillToolBoxControl           ::RegisterControl(0, pMod);
/*N*/   SvxLineStyleToolBoxControl      ::RegisterControl(0, pMod);
/*N*/   SvxLineWidthToolBoxControl      ::RegisterControl(0, pMod);
/*N*/   SvxLineColorToolBoxControl      ::RegisterControl(0, pMod);
/*N*/   SvxLineEndToolBoxControl        ::RegisterControl(SID_ATTR_LINEEND_STYLE,   pMod);
/*N*/   SvxStyleToolBoxControl          ::RegisterControl(SID_STYLE_APPLY,          pMod);
/*N*/   SvxFontNameToolBoxControl       ::RegisterControl(SID_ATTR_CHAR_FONT,       pMod);
/*N*/   SvxFontHeightToolBoxControl     ::RegisterControl(SID_ATTR_CHAR_FONTHEIGHT, pMod);
/*N*/   SvxFontColorToolBoxControl      ::RegisterControl(SID_ATTR_CHAR_COLOR,      pMod);
/*N*/   SvxColorToolBoxControl          ::RegisterControl(SID_BACKGROUND_COLOR,     pMod);
/*N*/   SvxFrameToolBoxControl          ::RegisterControl(SID_ATTR_BORDER,          pMod);
/*N*/   SvxFrameLineStyleToolBoxControl ::RegisterControl(SID_FRAME_LINESTYLE,      pMod);
/*N*/   SvxFrameLineColorToolBoxControl ::RegisterControl(SID_FRAME_LINECOLOR,      pMod);
/*N*/   SvxClipBoardControl             ::RegisterControl(SID_PASTE,                pMod );
/*N*/   SvxUndoRedoControl              ::RegisterControl(SID_UNDO,                 pMod );
/*N*/   SvxUndoRedoControl              ::RegisterControl(SID_REDO,                 pMod );
/*N*/
/*N*/   SvxGrafModeToolBoxControl       ::RegisterControl(SID_ATTR_GRAF_MODE,       pMod);
/*N*/   SvxGrafRedToolBoxControl        ::RegisterControl(SID_ATTR_GRAF_RED,        pMod);
/*N*/   SvxGrafGreenToolBoxControl      ::RegisterControl(SID_ATTR_GRAF_GREEN,      pMod);
/*N*/   SvxGrafBlueToolBoxControl       ::RegisterControl(SID_ATTR_GRAF_BLUE,       pMod);
/*N*/   SvxGrafLuminanceToolBoxControl  ::RegisterControl(SID_ATTR_GRAF_LUMINANCE,  pMod);
/*N*/   SvxGrafContrastToolBoxControl   ::RegisterControl(SID_ATTR_GRAF_CONTRAST,   pMod);
/*N*/   SvxGrafGammaToolBoxControl      ::RegisterControl(SID_ATTR_GRAF_GAMMA,      pMod);
/*N*/   SvxGrafTransparenceToolBoxControl::RegisterControl(SID_ATTR_GRAF_TRANSPARENCE, pMod);
/*N*/   SvxGrafFilterToolBoxControl     ::RegisterControl(SID_GRFFILTER,            pMod);
/*N*/
/*N*/     SvxVertTextTbxCtrl::RegisterControl(SID_DRAW_CAPTION_VERTICAL,          pMod);
/*N*/     SvxVertTextTbxCtrl::RegisterControl(SID_DRAW_TEXT_VERTICAL,             pMod);
/*N*/     SvxVertTextTbxCtrl::RegisterControl(SID_TEXTDIRECTION_LEFT_TO_RIGHT,    pMod);
/*N*/     SvxVertTextTbxCtrl::RegisterControl(SID_TEXTDIRECTION_TOP_TO_BOTTOM,    pMod);
/*N*/     SvxCTLTextTbxCtrl::RegisterControl(SID_ATTR_PARA_LEFT_TO_RIGHT, pMod);
/*N*/     SvxCTLTextTbxCtrl::RegisterControl(SID_ATTR_PARA_RIGHT_TO_LEFT, pMod);
/*N*/
/*N*/   // Svx-StatusBar-Controller
/*N*/   SvxInsertStatusBarControl       ::RegisterControl(SID_ATTR_INSERT,      pMod);
/*N*/   SvxSelectionModeControl         ::RegisterControl(SID_STATUS_SELMODE,   pMod);
/*N*/   SvxZoomStatusBarControl         ::RegisterControl(SID_ATTR_ZOOM,        pMod);
/*N*/   SvxModifyControl                ::RegisterControl(SID_DOC_MODIFIED,     pMod);
/*N*/   SvxPosSizeStatusBarControl      ::RegisterControl(SID_ATTR_SIZE,        pMod);
/*N*/
/*N*/   // Svx-Menue-Controller
/*N*/
/*N*/   //  Child-Windows
/*N*/
/*N*/   // Hack: Eingabezeile mit 42 registrieren, damit sie im PlugIn immer sichtbar ist
/*N*/   ScInputWindowWrapper        ::RegisterChildWindow(42, pMod, SFX_CHILDWIN_TASK);
/*N*/   ScNavigatorDialogWrapper    ::RegisterChildWindowContext(pMod);
/*N*/   ScSolverDlgWrapper          ::RegisterChildWindow(FALSE, pMod);
/*N*/   ScNameDlgWrapper            ::RegisterChildWindow(FALSE, pMod);
/*N*/   ScPivotLayoutWrapper        ::RegisterChildWindow(FALSE, pMod);
/*N*/   ScTabOpDlgWrapper           ::RegisterChildWindow(FALSE, pMod);
/*N*/   ScFilterDlgWrapper          ::RegisterChildWindow(FALSE, pMod);
/*N*/   ScSpecialFilterDlgWrapper   ::RegisterChildWindow(FALSE, pMod);
/*N*/   ScDbNameDlgWrapper          ::RegisterChildWindow(FALSE, pMod);
/*N*/   ScConsolidateDlgWrapper     ::RegisterChildWindow(FALSE, pMod);
/*N*/   ScChartDlgWrapper           ::RegisterChildWindow(FALSE, pMod);
/*N*/   ScPrintAreasDlgWrapper      ::RegisterChildWindow(FALSE, pMod);
/*N*/   ScCondFormatDlgWrapper      ::RegisterChildWindow(FALSE, pMod);
/*N*/   ScColRowNameRangesDlgWrapper::RegisterChildWindow(FALSE, pMod);
/*N*/   ScFormulaDlgWrapper         ::RegisterChildWindow(FALSE, pMod);
/*N*/
/*N*/   // First docking Window for Calc
/*N*/   ScFunctionChildWindow       ::RegisterChildWindow(FALSE, pMod);
/*N*/
/*N*/   // Redlining- Window
/*N*/   ScAcceptChgDlgWrapper       ::RegisterChildWindow(FALSE, pMod);
/*N*/   ScSimpleRefDlgWrapper       ::RegisterChildWindow(FALSE, pMod);
/*N*/   ScHighlightChgDlgWrapper    ::RegisterChildWindow(FALSE, pMod);
/*N*/
/*N*/
/*N*/   SvxFontWorkChildWindow      ::RegisterChildWindow(FALSE, pMod);
/*N*/   SvxHyperlinkDlgWrapper      ::RegisterChildWindow(FALSE, pMod);
/*N*/   SvxIMapDlgChildWindow       ::RegisterChildWindow(FALSE, pMod);
/*N*/   GalleryChildWindow          ::RegisterChildWindow(FALSE, pMod);
/*N*/
/*N*/   //  Edit-Engine-Felder, soweit nicht schon in OfficeApplication::Init
/*N*/
/*N*/   SvClassManager& rClassManager = SvxFieldItem::GetClassManager();
/*N*/ //    rClassManager.SV_CLASS_REGISTER( SvxURLField );
/*N*/ //    rClassManager.SV_CLASS_REGISTER( SvxDateField );
/*N*/ //    rClassManager.SV_CLASS_REGISTER( SvxPageField );
/*N*/   rClassManager.SV_CLASS_REGISTER( SvxPagesField );
/*N*/ //    rClassManager.SV_CLASS_REGISTER( SvxTimeField );
/*N*/   rClassManager.SV_CLASS_REGISTER( SvxFileField );
/*N*/ //    rClassManager.SV_CLASS_REGISTER( SvxExtFileField );
/*N*/   rClassManager.SV_CLASS_REGISTER( SvxTableField );
/*N*/
/*N*/   SdrRegisterFieldClasses();      // SvDraw-Felder registrieren
/*N*/
/*N*/   pMod->PutItem( SfxUInt16Item( SID_ATTR_METRIC, pMod->GetAppOptions().GetAppMetric() ) );
/*N*/
/*N*/   //  StarOne Services are now handled in the registry
/*N*/ }

/*N*/ void ScDLL::Exit()
/*N*/ {
/*N*/   // called directly befor unloading the DLL
/*N*/   // do whatever you want, Sxx-DLL is accessible
/*N*/
/*N*/   // the SxxModule must be destroyed
/*N*/   ScModuleDummy **ppShlPtr = (ScModuleDummy**) GetAppData(BF_SHL_CALC);
/*N*/   delete (*ppShlPtr);
/*N*/   (*ppShlPtr) = NULL;
/*N*/
/*N*/   //  auf keinen Fall ein neues ScModuleDummy anlegen, weil dessen vtable sonst
/*N*/   //  in der DLL waere und das Loeschen im LibExit schiefgehen wuerde
/*N*/
/*N*/   //  ScGlobal::Clear ist schon im Module-dtor
/*N*/ }

//------------------------------------------------------------------
//  Statusbar
//------------------------------------------------------------------

#define TEXT_WIDTH(s)   rStatusBar.GetTextWidth((s))


#undef TEXT_WIDTH


}
