/*************************************************************************
 *
 *  $RCSfile: sfx2_appmisc.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 14:27:03 $
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

#ifndef _SV_STATUS_HXX
#include <vcl/status.hxx>
#endif
#ifndef _SV_MSGBOX_HXX
#include <vcl/msgbox.hxx>
#endif
#ifndef _VOS_PROCESS_HXX //autogen
#include <vos/process.hxx>
#endif
#ifndef _XCEPTION_HXX_
#include <vos/xception.hxx>
#endif
#ifndef _SFX_WHITER_HXX //autogen
#include <svtools/whiter.hxx>
#endif
#ifndef _SFXSTRITEM_HXX //autogen
#include <svtools/stritem.hxx>
#endif
#ifndef _SFXINTITEM_HXX //autogen
#include <svtools/intitem.hxx>
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#ifndef _FILTER_HXX //autogen
#include <svtools/filter.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_INTERNALOPTIONS_HXX
#include <svtools/internaloptions.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_PATHOPTIONS_HXX
#include <svtools/pathoptions.hxx>
#endif

#ifndef _COM_SUN_STAR_REGISTRY_INVALIDREGISTRYEXCEPTION_HPP_
#include <com/sun/star/registry/InvalidRegistryException.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PropertyValue_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XFRAME_HPP_
#include <com/sun/star/frame/XFrame.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XURLTRANSFORMER_HPP_
#include <com/sun/star/util/XURLTransformer.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XFRAMESSUPPLIER_HPP_
#include <com/sun/star/frame/XFramesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
#include <com/sun/star/uno/Reference.h>
#endif
#ifndef _CONFIG_HXX
#include <tools/config.hxx>
#endif
#include <tools/rcid.h>
#include <vos/mutex.hxx>
#include <svtools/pver.hxx>
#pragma hdrstop
#ifndef _UTL_CONFIGMGR_HXX_
#include <unotools/configmgr.hxx>
#endif
#ifndef _COM_SUN_STAR_FRAME_XDESKTOP_HPP_
#include <com/sun/star/frame/XDesktop.hpp>
#endif

#include <unotools/ucbstreamhelper.hxx>
#include <framework/menuconfiguration.hxx>
#include <comphelper/processfactory.hxx>
#include <unotools/localfilehelper.hxx>
#include <unotools/bootstrap.hxx>
#include <svtools/moduleoptions.hxx>
#include <osl/file.hxx>

#include "sfxresid.hxx"
#include "app.hxx"
#include "appdata.hxx"
#include "arrdecl.hxx"
#include "cfgmgr.hxx"
#include "cfgitem.hxx"
#include "tbxctrl.hxx"

#ifndef _SVTOOLS_IMGDEF_HXX
#include <svtools/imgdef.hxx>
#endif

#include "tbxconf.hxx"
#include "stbitem.hxx"
#include "accitem.hxx"
#include "mnuitem.hxx"
#include "docfac.hxx"
#include "docfile.hxx"
#include "docfilt.hxx"
#include "request.hxx"
#include "bindings.hxx"
#include "dispatch.hxx"
#include "workwin.hxx"
//#include "iodlg.hxx"
#include "intro.hxx"
#include "about.hxx"
#include "fcontnr.hxx"
#include "sfxlocal.hrc"
#include "sfx.hrc"
#include "app.hrc"
#include "templdlg.hxx"
#include "module.hxx"
#include "msgpool.hxx"
#include "topfrm.hxx"
#include "openflag.hxx"
#include "viewsh.hxx"
#include "appimp.hxx"
//#include "bmkmenu.hxx"
#include "objface.hxx"
#include "helper.hxx"   // SfxContentHelper::Kill()

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif

using namespace ::vos;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::container;

//===================================================================
namespace binfilter {

/*N*/ SV_IMPL_PTRARR( SfxTbxCtrlFactArr_Impl, SfxTbxCtrlFactory* );
/*N*/ SV_IMPL_PTRARR( SfxStbCtrlFactArr_Impl, SfxStbCtrlFactory* );
/*N*/ SV_IMPL_PTRARR( SfxMenuCtrlFactArr_Impl, SfxMenuCtrlFactory* );
/*N*/ SV_IMPL_PTRARR( SfxChildWinFactArr_Impl, SfxChildWinFactory* );
//STRIP001 SV_IMPL_PTRARR( SfxModuleArr_Impl, SfxModule* );

//===================================================================

#define SfxApplication
#include "sfxslots.hxx"

class SfxSpecialConfigError_Impl
{
    String aError;

public:

//STRIP001  SfxSpecialConfigError_Impl( const String& rStr );
//STRIP001  DECL_LINK( TimerHdl, Timer*);
};


//STRIP001 SfxSpecialConfigError_Impl::SfxSpecialConfigError_Impl( const String& rStr ) :
//STRIP001  aError( rStr )
//STRIP001 {
//STRIP001  Timer *pTimer = new Timer;
//STRIP001  pTimer->SetTimeoutHdl( LINK(this, SfxSpecialConfigError_Impl, TimerHdl) );
//STRIP001  pTimer->SetTimeout( 0 );
//STRIP001  pTimer->Start();
//STRIP001 }

//STRIP001 IMPL_LINK( SfxSpecialConfigError_Impl, TimerHdl, Timer*, pTimer )
//STRIP001 {
//STRIP001  delete pTimer;
//STRIP001  ErrorBox( 0, WinBits( WB_OK ) , aError ).Execute();
//STRIP001  delete this;
//STRIP001     SFX_APP()->GetAppDispatcher_Impl()->Execute( SID_QUITAPP );
//STRIP001  return 0L;
//STRIP001 }

//====================================================================


/*N*/ SFX_IMPL_INTERFACE(SfxApplication,SfxShell,SfxResId(0))
/*N*/ {
/*N*/     SFX_CHILDWINDOW_REGISTRATION( SID_CUSTOMIZETOOLBOX );
/*N*/
/*N*/     // Menu ist auf dem Macintosh sowieso sichtbar
/*N*/     SFX_OBJECTBAR_REGISTRATION(
/*N*/             SFX_OBJECTBAR_FULLSCREEN | SFX_VISIBILITY_FULLSCREEN,
/*N*/             SfxResId(RID_FULLSCREENTOOLBOX) );
/*N*/     SFX_OBJECTBAR_REGISTRATION( SFX_OBJECTBAR_APPLICATION |
/*N*/             SFX_VISIBILITY_DESKTOP | SFX_VISIBILITY_STANDARD | SFX_VISIBILITY_CLIENT,
/*N*/             SfxResId(RID_ENVTOOLBOX) );
/*N*/
/*N*/     SFX_STATUSBAR_REGISTRATION(SfxResId(SFX_ITEMTYPE_STATBAR));
/*N*/ }

//--------------------------------------------------------------------

/*?*/ SfxViewFrame* SfxApplication::CreateViewFrame(
/*?*/     SfxObjectShell& rDoc, sal_uInt16 nViewId, sal_Bool bHidden )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001
//STRIP001  SfxItemSet *pSet = rDoc.GetMedium()->GetItemSet();
//STRIP001  if ( nViewId )
//STRIP001      pSet->Put( SfxUInt16Item( SID_VIEW_ID, nViewId ) );
//STRIP001     if ( bHidden )
//STRIP001      pSet->Put( SfxBoolItem( SID_HIDDEN, sal_True ) );
//STRIP001
//STRIP001     SfxFrame *pFrame = SfxTopFrame::Create( &rDoc, 0, bHidden );
//STRIP001  return pFrame->GetCurrentViewFrame();
/*?*/ }

//STRIP001 void SfxApplication::InitializeDisplayName_Impl()
//STRIP001 {
//STRIP001     SfxAppData_Impl* pAppData_Impl = Get_Impl();
//STRIP001     if ( !pAppData_Impl->pLabelResMgr )
//STRIP001         return;
//STRIP001
//STRIP001  String aTitle = Application::GetDisplayName();
//STRIP001     if ( !aTitle.Len() )
//STRIP001  {
//STRIP001      OClearableGuard aGuard( OMutex::getGlobalMutex() );
//STRIP001
//STRIP001      // create version string
//STRIP001 /*!!! (pb) don't show a version number at the moment
//STRIP001      USHORT nProductVersion = ProductVersion::GetVersion().ToInt32();
//STRIP001         String aVersion( String::CreateFromInt32( nProductVersion / 10 ) );
//STRIP001      aVersion += 0x002E ; // 2Eh ^= '.'
//STRIP001      aVersion += ( String::CreateFromInt32( nProductVersion % 10 ) );
//STRIP001 */
//STRIP001      // load application title
//STRIP001      aTitle = String( ResId( RID_APPTITLE, pAppData_Impl->pLabelResMgr ) );
//STRIP001      // merge version into title
//STRIP001      aTitle.SearchAndReplaceAscii( "$(VER)", String() /*aVersion*/ );
//STRIP001
//STRIP001      aGuard.clear();
//STRIP001
//STRIP001 #ifndef PRODUCT
//STRIP001      ::rtl::OUString aDefault;
//STRIP001      aTitle += DEFINE_CONST_UNICODE(" [");
//STRIP001
//STRIP001      String aVerId( utl::Bootstrap::getBuildIdData( aDefault ));
//STRIP001      aTitle += aVerId;
//STRIP001      aTitle += 0x005D ; // 5Dh ^= ']'
//STRIP001 #endif
//STRIP001      if ( GetDemoKind() == SFX_DEMOKIND_DEMO )
//STRIP001          aTitle += DEFINE_CONST_UNICODE(" (Demo Version)");
//STRIP001
//STRIP001      Application::SetDisplayName( aTitle );
//STRIP001  }
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 void SfxApplication::OpenClients()
//STRIP001 {
//STRIP001 }

//--------------------------------------------------------------------

/*N*/ void SfxApplication::FillStatusBar( StatusBar& rBar )
/*N*/
/*  [Beschreibung]

    Diese virtuelle Factory-Methode wird vom SFx gerufen, um die
    StatusBar f"ur das Applikationsfenster zu erzeugen. Im Ggs. zu
    den anderen Standard-Controllern Menu, Accelerator und ToolBoxen
    kann die Status-Zeile nur mit dieser Factory erzeugt werden,
    da in der SV-Resource keine StatusBar-Items angegeben werden k"oennen.
*/

/*N*/ {
/*N*/   rBar.InsertItem( SID_EXPLORER_SELECTIONSIZE, 200, SIB_IN|SIB_LEFT|SIB_AUTOSIZE );
/*N*/ }

//--------------------------------------------------------------------

//STRIP001 void SfxApplication::IntroSlide()
//STRIP001
//STRIP001 /*  [Beschreibung]
//STRIP001
//STRIP001     Diese virtuelle Methode wird vom SFx gerufen, um die bei einem
//STRIP001     Mehrbild-Intro das n"achte Bild anzuzeigen. Sie sollte w"ahrend
//STRIP001     des Startups mehrmals gerufen werden, wenn l"angere Initialisierungen
//STRIP001     ausgef"uhrt werden.
//STRIP001 */
//STRIP001
//STRIP001 {
//STRIP001     if ( pImp->pIntro )
//STRIP001         pImp->pIntro->Slide();
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 PrinterDialog* SfxApplication::CreatePrinterDialog()
//STRIP001
//STRIP001 /*  [Beschreibung]
//STRIP001
//STRIP001     Diese virtuelle Factory-Methode wird vom SFx gerufen, um einen
//STRIP001     Applikations-spezifischen PrinterDialog zu erzeugen.
//STRIP001
//STRIP001     Die Default-Implementierung liefert einen 0-Pointer zur"uck.
//STRIP001 */
//STRIP001
//STRIP001 {
//STRIP001     return 0;
//STRIP001 }
//--------------------------------------------------------------------

//STRIP001 ModalDialog* SfxApplication::CreateAboutDialog()
//STRIP001
//STRIP001 /*  [Beschreibung]
//STRIP001
//STRIP001     Diese virtuelle Factory-Methode wird vom SFx gerufen, um einen
//STRIP001     Modul-spezifischen AboutDialog zu erzeugen.
//STRIP001
//STRIP001     Die Default-Implementierung erzeugt einen AboutDialog aus
//STRIP001     der Resource 'ModalDialog RID_DEFAULTABOUT' und verwendet
//STRIP001     zus"atzlich einen String RID_BUILDVERSION, f"ur die Update-Version
//STRIP001     der Applikation. Letztere wird angezeigt, sobald der Anwender
//STRIP001     eine spezielle, im Dialog definierte, Sequenz von Zeichen
//STRIP001     eingibt (z.B. 'Ctrl' 's' 'f' 'x').
//STRIP001 */
//STRIP001
//STRIP001 {
//STRIP001  // Buildversion suchen
//STRIP001  ::rtl::OUString aDefault;
//STRIP001  String          aVerId( utl::Bootstrap::getBuildIdData( aDefault ));
//STRIP001
//STRIP001  if ( aVerId.Len() == 0 )
//STRIP001      DBG_ERROR( "No BUILDID in bootstrap file" );
//STRIP001
//STRIP001  String aVersion( '[' );
//STRIP001  ( aVersion += aVerId ) += ']';
//STRIP001
//STRIP001  // About-Dialog suchen
//STRIP001  ResId aDialogResId( RID_DEFAULTABOUT, pAppData_Impl->pLabelResMgr );
//STRIP001  ResMgr* pResMgr = pAppData_Impl->pLabelResMgr->IsAvailable(
//STRIP001                      aDialogResId.SetRT( RSC_MODALDIALOG ) )
//STRIP001                  ? pAppData_Impl->pLabelResMgr
//STRIP001                  : 0;
//STRIP001     aDialogResId.SetResMgr( pResMgr );
//STRIP001     if ( !Resource::GetResManager()->IsAvailable( aDialogResId ) )
//STRIP001      DBG_ERROR( "No RID_DEFAULTABOUT in label-resource-dll" );
//STRIP001
//STRIP001  // About-Dialog anzeigen
//STRIP001     AboutDialog* pDlg = new AboutDialog( 0, aDialogResId, aVersion );
//STRIP001     return pDlg;
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 void SfxApplication::HandleConfigError_Impl( sal_uInt16 nErrorCode ) const
//STRIP001 {
//STRIP001     sal_uInt16 nResId = 0;
//STRIP001     switch(nErrorCode)
//STRIP001     {
//STRIP001         case SfxConfigManager::ERR_READ:
//STRIP001             nResId = MSG_ERR_READ_CFG;
//STRIP001             break;
//STRIP001         case SfxConfigManager::ERR_WRITE:
//STRIP001             nResId = MSG_ERR_WRITE_CFG;
//STRIP001             break;
//STRIP001         case SfxConfigManager::ERR_OPEN:
//STRIP001             nResId = MSG_ERR_OPEN_CFG;
//STRIP001             break;
//STRIP001         case SfxConfigManager::ERR_FILETYPE:
//STRIP001             nResId = MSG_ERR_FILETYPE_CFG;
//STRIP001             break;
//STRIP001         case SfxConfigManager::ERR_VERSION:
//STRIP001             nResId = MSG_ERR_VERSION_CFG;
//STRIP001             break;
//STRIP001     }
//STRIP001     DBG_ASSERT(nResId != 0, "unbekannte Fehlerkonstante aus Konfiguration");
//STRIP001     if(nResId)
//STRIP001     {
//STRIP001         ErrorBox aErrorBox(NULL, SfxResId(nResId));
//STRIP001         aErrorBox.Execute();
//STRIP001     }
//STRIP001 }

//--------------------------------------------------------------------
#ifdef WNT
extern String GetUserID();
#endif

//------------------------------------------------------------------------

/*N*/ SfxProgress* SfxApplication::GetProgress() const

/*  [Beschreibung]

    Liefert den f"ur die gesamte Applikation laufenden SfxProgress
    oder 0, falls keiner f"ur die gesamte Applikation l"auft.


    [Querverweise]

    <SfxProgress::GetActiveProgress(SfxViewFrame*)>
    <SfxViewFrame::GetProgress()const>
*/

/*N*/ {
/*N*/     return pAppData_Impl->pProgress;
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 void SfxApplication::ToolboxExec_Impl( SfxRequest &rReq )
//STRIP001 {
//STRIP001     // Object-Bar-Id ermitteln
//STRIP001     sal_uInt16 nSID = rReq.GetSlot(), nTbxID;
//STRIP001     switch ( nSID )
//STRIP001     {
//STRIP001         case SID_TOGGLEFUNCTIONBAR:     nTbxID = SFX_OBJECTBAR_APPLICATION; break;
//STRIP001         case SID_TOGGLEOBJECTBAR:       nTbxID = SFX_OBJECTBAR_OBJECT; break;
//STRIP001         case SID_TOGGLETOOLBAR:         nTbxID = SFX_OBJECTBAR_TOOLS; break;
//STRIP001         case SID_TOGGLEMACROBAR:        nTbxID = SFX_OBJECTBAR_MACRO; break;
//STRIP001         case SID_TOGGLEOPTIONBAR:       nTbxID = SFX_OBJECTBAR_OPTIONS; break;
//STRIP001         case SID_TOGGLECOMMONTASKBAR:   nTbxID = SFX_OBJECTBAR_COMMONTASK; break;
//STRIP001         case SID_TOGGLENAVBAR:           nTbxID = SFX_OBJECTBAR_NAVIGATION; break;
//STRIP001         //case SID_TOGGLERECORDINGBAR:  nTbxID = SFX_OBJECTBAR_RECORDING; break;
//STRIP001         //case SID_TOGGLEFULLSCREENBAR: nTbxID = SFX_OBJECTBAR_FULLSCREEN; break;
//STRIP001         default:
//STRIP001             DBG_ERROR( "invalid ObjectBar`s SID" );
//STRIP001     }
//STRIP001
//STRIP001     // Parameter auswerten
//STRIP001     SfxToolBoxConfig *pTbxConfig = pViewFrame->GetBindings().GetToolBoxConfig();
//STRIP001     SFX_REQUEST_ARG(rReq, pShowItem, SfxBoolItem, nSID, sal_False);
//STRIP001     sal_Bool bShow = pShowItem ? pShowItem->GetValue() : !pTbxConfig->IsToolBoxPositionVisible(nTbxID);
//STRIP001
//STRIP001     // ausfuehren
//STRIP001     pTbxConfig->SetToolBoxPositionVisible(nTbxID, bShow);
//STRIP001     Invalidate( nSID );
//STRIP001
//STRIP001  SfxViewFrame* pViewFrame = SfxViewFrame::GetFirst();
//STRIP001  while ( pViewFrame )
//STRIP001  {
//STRIP001      // update all "final" dispatchers
//STRIP001      if ( !pViewFrame->GetActiveChildFrame_Impl() )
//STRIP001          pViewFrame->GetDispatcher()->Update_Impl(sal_True);
//STRIP001      pViewFrame = SfxViewFrame::GetNext(*pViewFrame);
//STRIP001  }
//STRIP001
//STRIP001     // ggf. recorden
//STRIP001     if ( !rReq.IsAPI() )
//STRIP001         rReq.AppendItem( SfxBoolItem( nSID, bShow ) );
//STRIP001     rReq.Done();
//STRIP001 }

//------------------------------------------------------------------------


//STRIP001 void SfxApplication::ToolboxState_Impl( SfxItemSet &rSet )
//STRIP001 {
//STRIP001     SfxWhichIter aIter(rSet);
//STRIP001     for ( sal_uInt16 nSID = aIter.FirstWhich(); nSID; nSID = aIter.NextWhich() )
//STRIP001     {
//STRIP001         SfxToolBoxConfig *pTbxConfig = pViewFrame->GetBindings().GetToolBoxConfig();
//STRIP001         switch ( nSID )
//STRIP001         {
//STRIP001             case SID_TOGGLEFUNCTIONBAR:
//STRIP001                     rSet.Put( SfxBoolItem( nSID, pTbxConfig->
//STRIP001                         IsToolBoxPositionVisible(SFX_OBJECTBAR_APPLICATION)));
//STRIP001                 break;
//STRIP001
//STRIP001             case SID_TOGGLEOBJECTBAR:
//STRIP001                     rSet.Put( SfxBoolItem( nSID, pTbxConfig->
//STRIP001                         IsToolBoxPositionVisible(SFX_OBJECTBAR_OBJECT)));
//STRIP001                 break;
//STRIP001
//STRIP001             case SID_TOGGLEOPTIONBAR:
//STRIP001                     rSet.Put( SfxBoolItem( nSID, pTbxConfig->
//STRIP001                         IsToolBoxPositionVisible(SFX_OBJECTBAR_OPTIONS)));
//STRIP001                 break;
//STRIP001
//STRIP001             case SID_TOGGLETOOLBAR:
//STRIP001                  rSet.Put( SfxBoolItem( nSID, pTbxConfig->
//STRIP001                      IsToolBoxPositionVisible(SFX_OBJECTBAR_TOOLS)));
//STRIP001                 break;
//STRIP001
//STRIP001             case SID_TOGGLEMACROBAR:
//STRIP001                  rSet.Put( SfxBoolItem( nSID, pTbxConfig->
//STRIP001                      IsToolBoxPositionVisible(SFX_OBJECTBAR_MACRO)));
//STRIP001                 break;
//STRIP001
//STRIP001             case SID_TOGGLECOMMONTASKBAR:
//STRIP001                  rSet.Put( SfxBoolItem( nSID, pTbxConfig->
//STRIP001                      IsToolBoxPositionVisible(SFX_OBJECTBAR_COMMONTASK)));
//STRIP001                 break;
//STRIP001
//STRIP001             case SID_TOGGLENAVBAR:
//STRIP001                  rSet.Put( SfxBoolItem( nSID, pTbxConfig->
//STRIP001                      IsToolBoxPositionVisible(SFX_OBJECTBAR_NAVIGATION)));
//STRIP001                 break;
//STRIP001
//STRIP001             default:
//STRIP001                 DBG_ERROR( "invalid ObjectBar`s SID" );
//STRIP001         }
//STRIP001     }
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ SvUShorts* SfxApplication::GetDisabledSlotList_Impl()
/*N*/ {
/*N*/   sal_Bool bError = sal_False;
/*N*/   SvUShorts* pList = pAppData_Impl->pDisabledSlotList;
/*N*/   if ( !pList )
/*N*/   {
/*N*/       // Gibt es eine Slotdatei ?
/*N*/         INetURLObject aUserObj( SvtPathOptions().GetUserConfigPath() );
/*N*/         aUserObj.insertName( DEFINE_CONST_UNICODE( "slots.cfg" ) );
/*N*/         SvStream* pStream = ::utl::UcbStreamHelper::CreateStream( aUserObj.GetMainURL( INetURLObject::NO_DECODE ), STREAM_STD_READ );
/*N*/         if ( !pStream || pStream->GetError() == ERRCODE_IO_NOTEXISTS )
/*N*/         {
/*N*/             delete pStream;
/*N*/             INetURLObject aObj( SvtPathOptions().GetConfigPath() );
/*N*/             aObj.insertName( DEFINE_CONST_UNICODE( "slots.cfg" ) );
/*N*/             pStream = ::utl::UcbStreamHelper::CreateStream( aObj.GetMainURL( INetURLObject::NO_DECODE ), STREAM_STD_READ );
/*N*/         }
/*N*/
/*N*/         BOOL bSlotsEnabled = SvtInternalOptions().SlotCFGEnabled();
/*N*/         BOOL bSlots = ( pStream && !pStream->GetError() );
/*N*/         if( bSlots && bSlotsEnabled )
/*N*/       {
/*N*/             // SlotDatei einlesen
/*?*/             String aTitle;
/*?*/             pStream->ReadByteString(aTitle);
/*?*/             if ( aTitle.CompareToAscii("SfxSlotFile" ) == COMPARE_EQUAL )
/*?*/             {
/*?*/                 sal_uInt16 nCount;
/*?*/                 (*pStream) >> nCount;
/*?*/                 pList = pAppData_Impl->pDisabledSlotList =
/*?*/                         new SvUShorts( nCount < 255 ? (sal_Int8) nCount : 255, 255 );
/*?*/
/*?*/                 sal_uInt16 nSlot;
/*?*/                 for ( sal_uInt16 n=0; n<nCount; n++ )
/*?*/                 {
/*?*/                     (*pStream) >> nSlot;
/*?*/                     pList->Insert( nSlot, n );
/*?*/                 }
/*?*/
/*?*/                 pStream->ReadByteString(aTitle);
/*?*/                 if ( aTitle.CompareToAscii("END" ) != COMPARE_EQUAL || pStream->GetError() )
/*?*/                 {
/*?*/                     // Lesen schief gegangen
/*?*/                     DELETEZ( pList );
/*?*/                     bError = sal_True;
/*?*/                 }
/*?*/             }
/*?*/             else
/*?*/             {
/*?*/                 // Streamerkennung  fehlgeschlagen
/*?*/                 bError = sal_True;
/*N*/             }
/*N*/       }
/*N*/         else if ( bSlots != bSlotsEnabled )
/*N*/       {
/*N*/           // Wenn kein Slotlist-Eintrag, dann darf auch keine SlotDatei
/*N*/           // vorhanden sein
/*N*/             bError = sal_True;
/*N*/       }
/*N*/
/*N*/         delete pStream;
/*N*/   }
/*N*/   else if ( pList == (SvUShorts*) -1L )
/*N*/   {
/*N*/       return NULL;
/*N*/   }
/*N*/
/*N*/   if ( !pList )
/*N*/       pAppData_Impl->pDisabledSlotList = (SvUShorts*) -1L;
/*N*/
/*N*/   if ( bError )
/*N*/   {
/*N*/       // Wenn ein Sloteintrag vorhanden ist, aber keine oder eine fehlerhafte
/*N*/       // SlotDatei, oder aber eine Slotdatei, aber kein Sloteintrag, dann
/*N*/       // gilt dies als fehlerhafte Konfiguration
/*?*/         DBG_BF_ASSERT(0, "STRIP"); //STRIP001 new SfxSpecialConfigError_Impl( String( SfxResId( RID_SPECIALCONFIG_ERROR ) ) );
/*N*/   }
/*N*/
/*N*/       return pList;
/*N*/ }


//STRIP001 Config* SfxApplication::GetFilterIni()
//STRIP001 {
//STRIP001  if ( !pAppData_Impl->pFilterIni )
//STRIP001  {
//STRIP001      OStartupInfo aInfo;
//STRIP001      ::rtl::OUString aApplicationName;
//STRIP001      // get the path of the executable
//STRIP001      if ( aInfo.getExecutableFile( aApplicationName ) == OStartupInfo::E_None )
//STRIP001      {
//STRIP001          // cut the name of the executable
//STRIP001          ::rtl::OUString aIniFile = aApplicationName.copy( 0, aApplicationName.lastIndexOf( '/' ) );
//STRIP001          // append the name of the filter ini
//STRIP001          aIniFile += ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "/install.ini" ) );
//STRIP001          // and create the Config instance
//STRIP001          pAppData_Impl->pFilterIni = new Config( aIniFile );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return pAppData_Impl->pFilterIni;
//STRIP001 }


/*N*/ SfxModule* SfxApplication::GetActiveModule( SfxViewFrame *pFrame ) const
/*N*/ {
/*N*/   if ( !pFrame )
/*N*/       pFrame = SfxViewFrame::Current();
/*N*/   SfxObjectShell* pSh = 0;
/*N*/   if( pFrame ) pSh = pFrame->GetObjectShell();
/*N*/   return pSh ? pSh->GetModule() : 0;
/*N*/ }

//STRIP001 SfxModule* SfxApplication::GetModule_Impl()
//STRIP001 {
//STRIP001     SfxModule* pModule = GetActiveModule();
//STRIP001     if ( !pModule )
//STRIP001         pModule = GetActiveModule( SfxViewFrame::GetFirst( FALSE ) );
//STRIP001  if( pModule )
//STRIP001      return pModule;
//STRIP001     else
//STRIP001     {
//STRIP001         DBG_ERROR( "No module!" );
//STRIP001         return NULL;
//STRIP001     }
//STRIP001 }


/*N*/ SfxSlotPool& SfxApplication::GetSlotPool( SfxViewFrame *pFrame ) const
/*N*/ {
/*N*/   SfxModule *pMod = GetActiveModule( pFrame );
/*N*/   if ( pMod && pMod->GetSlotPool() )
/*N*/       return *pMod->GetSlotPool();
/*N*/   else
/*N*/       return *pSlotPool;
/*N*/ }


//STRIP001 SfxAcceleratorManager* SfxApplication::GetAcceleratorManager() const
//STRIP001 {
//STRIP001  // Accelerator immer mit ContainerBindings
//STRIP001  SfxViewFrame *pFrame = pViewFrame;
//STRIP001  if ( !pFrame )
//STRIP001      return pAcceleratorMgr;
//STRIP001
//STRIP001  while ( pFrame->GetParentViewFrame_Impl() )
//STRIP001      pFrame = pFrame->GetParentViewFrame_Impl();
//STRIP001
//STRIP001  SfxViewShell* pSh = 0;
//STRIP001  if( pFrame )
//STRIP001      pSh = pFrame->GetViewShell();
//STRIP001  if ( pSh )
//STRIP001  {
//STRIP001      SfxAcceleratorManager *pMgr = pSh->GetAccMgr_Impl();
//STRIP001      if ( pMgr )
//STRIP001          return pMgr;
//STRIP001  }
//STRIP001
//STRIP001  return pAcceleratorMgr;
//STRIP001 }

/*N*/ SfxAcceleratorManager* SfxApplication::GetGlobalAcceleratorManager() const
/*N*/ {
/*N*/     return pAcceleratorMgr;
/*N*/ }

//STRIP001 ISfxTemplateCommon* SfxApplication::GetCurrentTemplateCommon()
//STRIP001 {
//STRIP001  if( pAppData_Impl->pTemplateCommon )
//STRIP001      return pAppData_Impl->pTemplateCommon;
//STRIP001  return NULL;
//STRIP001 }


/*N*/ ISfxTemplateCommon* SfxApplication::GetCurrentTemplateCommon( SfxBindings& rBindings )
/*N*/ {
/*N*/   if( pAppData_Impl->pTemplateCommon )
/*?*/       return pAppData_Impl->pTemplateCommon;
/*N*/   SfxChildWindow *pChild = rBindings.GetWorkWindow_Impl()->GetChildWindow_Impl(
/*N*/       SfxTemplateDialogWrapper::GetChildWindowId() );
/*N*/   if ( pChild )
/*N*/       return ((SfxTemplateDialog*) pChild->GetWindow())->GetISfxTemplateCommon();
/*N*/   return 0;
/*N*/ }

//STRIP001 long Select_Impl( void* pHdl, void* pVoid )
//STRIP001 {
//STRIP001     Menu* pMenu = (Menu*) pVoid;
//STRIP001     String aURL( pMenu->GetItemCommand( pMenu->GetCurItemId() ) );
//STRIP001  if( !aURL.Len() )
//STRIP001         return 0;
//STRIP001
//STRIP001     SfxDispatcher* pDispatcher = ((SfxBindings*)pHdl)->GetDispatcher_Impl();
//STRIP001     if ( ! pDispatcher )
//STRIP001         return 0;
//STRIP001     Reference< ::com::sun::star::frame::XFrame> xFrame( pDispatcher->GetFrame()->GetFrame()->GetFrameInterface() );
//STRIP001     if (! xFrame.is())
//STRIP001     {
//STRIP001         Reference < ::com::sun::star::frame::XFramesSupplier > xDesktop =
//STRIP001                 Reference < ::com::sun::star::frame::XFramesSupplier >( ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance( DEFINE_CONST_UNICODE("com.sun.star.frame.Desktop") ), UNO_QUERY );
//STRIP001         xFrame = Reference < ::com::sun::star::frame::XFrame > ( xDesktop->getActiveFrame() );
//STRIP001         if ( !xFrame.is() )
//STRIP001             xFrame = Reference < ::com::sun::star::frame::XFrame >( xDesktop, UNO_QUERY );
//STRIP001     }
//STRIP001
//STRIP001     URL aTargetURL;
//STRIP001     aTargetURL.Complete = aURL;
//STRIP001     Reference < XURLTransformer > xTrans( ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance( ::rtl::OUString::createFromAscii("com.sun.star.util.URLTransformer" )), UNO_QUERY );
//STRIP001     xTrans->parseStrict( aTargetURL );
//STRIP001
//STRIP001     Reference < ::com::sun::star::frame::XDispatchProvider > xProv( xFrame, UNO_QUERY );
//STRIP001     Reference < ::com::sun::star::frame::XDispatch > xDisp;
//STRIP001  if ( xProv.is() )
//STRIP001  {
//STRIP001         if ( aTargetURL.Protocol.compareToAscii("slot:") == COMPARE_EQUAL )
//STRIP001             xDisp = xProv->queryDispatch( aTargetURL, ::rtl::OUString(), 0 );
//STRIP001         else
//STRIP001         {
//STRIP001          ::rtl::OUString aTargetFrame( ::rtl::OUString::createFromAscii("_blank") );
//STRIP001          ::framework::MenuConfiguration::Attributes* pMenuAttributes =
//STRIP001              (::framework::MenuConfiguration::Attributes*)pMenu->GetUserValue( pMenu->GetCurItemId() );
//STRIP001
//STRIP001          if ( pMenuAttributes )
//STRIP001              aTargetFrame = pMenuAttributes->aTargetFrame;
//STRIP001
//STRIP001          xDisp = xProv->queryDispatch( aTargetURL, aTargetFrame , 0 );
//STRIP001      }
//STRIP001  }
//STRIP001     if ( xDisp.is() )
//STRIP001  {
//STRIP001 /*
//STRIP001      Sequence<PropertyValue> aArgs(1);
//STRIP001      PropertyValue* pArg = aArgs.getArray();
//STRIP001      pArg[0].Name = ::rtl::OUString::createFromAscii("Referer");
//STRIP001         pArg[0].Value <<= ::rtl::OUString::createFromAscii("private:user");
//STRIP001      xDisp->dispatch( aTargetURL, aArgs );
//STRIP001  */
//STRIP001      xDisp->dispatch( aTargetURL, Sequence<PropertyValue>() );
//STRIP001  }
//STRIP001
//STRIP001     return TRUE;
//STRIP001 }

//STRIP001 SfxMenuBarManager* SfxApplication::GetMenuBarManager() const
//STRIP001 {
//STRIP001     SfxViewFrame *pFrame = SfxViewFrame::Current();
//STRIP001     if ( pFrame )
//STRIP001         return pFrame->GetViewShell()->GetMenuBar_Impl();
//STRIP001     else
//STRIP001         return 0;
//STRIP001 }

/*N*/ SfxCancelManager *SfxApplication::GetCancelManager() const
/*N*/ {
/*N*/   if ( !pAppData_Impl->pCancelMgr )
/*N*/   {
/*N*/       pAppData_Impl->pCancelMgr = new SfxCancelManager;
/*N*/       pAppData_Impl->StartListening( *pAppData_Impl->pCancelMgr );
/*N*/   }
/*N*/   return pAppData_Impl->pCancelMgr;
/*N*/ }


}
