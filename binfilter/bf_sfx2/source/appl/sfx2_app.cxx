/*************************************************************************
 *
 *  $RCSfile: sfx2_app.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 14:25:03 $
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

#if defined UNX
#include <limits.h>
#else // UNX
#include <stdlib.h>
#define PATH_MAX _MAX_PATH
#endif // UNX

// auto strip #include "app.hxx"
// auto strip #include "frame.hxx"

// auto strip #ifndef _VOS_PROCESS_HXX_
// auto strip #include <vos/process.hxx>
// auto strip #endif
// auto strip #ifndef _TOOLS_SIMPLERESMGR_HXX_
// auto strip #include <tools/simplerm.hxx>
// auto strip #endif
// auto strip #ifndef _CONFIG_HXX
// auto strip #include <tools/config.hxx>
// auto strip #endif

// auto strip #ifndef SVTOOLS_ASYNCLINK_HXX
// auto strip #include <svtools/asynclink.hxx>
// auto strip #endif
// auto strip #ifndef _SFXSTRITEM_HXX //autogen
// auto strip #include <svtools/stritem.hxx>
// auto strip #endif
// auto strip #ifndef _SOUND_HXX //autogen
// auto strip #include <vcl/sound.hxx>
// auto strip #endif
// auto strip #ifndef _SFXENUMITEM_HXX //autogen
// auto strip #include <svtools/eitem.hxx>
// auto strip #endif
// auto strip #ifndef _FILELIST_HXX //autogen
// auto strip #include <so3/filelist.hxx>
// auto strip #endif
// auto strip #ifndef _URLBMK_HXX //autogen
// auto strip #include <svtools/urlbmk.hxx>
// auto strip #endif
// auto strip #ifndef _MSGBOX_HXX //autogen
// auto strip #include <vcl/msgbox.hxx>
// auto strip #endif
// auto strip #ifndef _EXTATTR_HXX //autogen
// auto strip #include <svtools/extattr.hxx>
// auto strip #endif
// auto strip #ifndef _SFXECODE_HXX
// auto strip #include <svtools/sfxecode.hxx>
// auto strip #endif
// auto strip #ifndef _EHDL_HXX
// auto strip #include <svtools/ehdl.hxx>
// auto strip #endif

#include <svtools/svdde.hxx>
#include <tools/urlobj.hxx>
// auto strip #include <unotools/tempfile.hxx>
// auto strip #include <osl/file.hxx>
#pragma hdrstop

#define _SVSTDARR_STRINGSDTOR
// auto strip #include <svtools/svstdarr.hxx>

// auto strip #include <com/sun/star/uno/Sequence.hxx>
// auto strip #include <com/sun/star/uno/Any.hxx>
// auto strip #include <com/sun/star/lang/XInitialization.hpp>

// auto strip #ifndef _COM_SUN_STAR_FRAME_XFRAMEACTIONLISTENER_HPP_
// auto strip #include <com/sun/star/frame/XFrameActionListener.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_XCOMPONENTLOADER_HPP_
// auto strip #include <com/sun/star/frame/XComponentLoader.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_XFRAME_HPP_
// auto strip #include <com/sun/star/frame/XFrame.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_FRAMEACTIONEVENT_HPP_
// auto strip #include <com/sun/star/frame/FrameActionEvent.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_FRAMEACTION_HPP_
// auto strip #include <com/sun/star/frame/FrameAction.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_LOADER_XIMPLEMENTATIONLOADER_HPP_
// auto strip #include <com/sun/star/loader/XImplementationLoader.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_LOADER_CANNOTACTIVATEFACTORYEXCEPTION_HPP_
// auto strip #include <com/sun/star/loader/CannotActivateFactoryException.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_MOZILLA_XPLUGININSTANCE_HPP_
// auto strip #include <com/sun/star/mozilla/XPluginInstance.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_FRAME_XFRAMESSUPPLIER_HPP_
// auto strip #include <com/sun/star/frame/XFramesSupplier.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_CONTAINER_XINDEXACCESS_HPP_
// auto strip #include <com/sun/star/container/XIndexAccess.hpp>
// auto strip #endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
// auto strip #ifndef _UNOTOOLS_PROCESSFACTORY_HXX
// auto strip #include <comphelper/processfactory.hxx>
// auto strip #endif
// auto strip #ifndef _ISOLANG_HXX
// auto strip #include <tools/isolang.hxx>
// auto strip #endif
// auto strip #include <basic/basmgr.hxx>
// auto strip #include <toolkit/helper/vclunohelper.hxx>
// auto strip #include <vcl/svapp.hxx>

#if SUPD>637
#include <rtl/logfile.hxx>
#endif

#include <appuno.hxx>
// auto strip #include "sfxhelp.hxx"
// auto strip #include "request.hxx"
// auto strip #include "sfxtypes.hxx"
// auto strip #include "sfxresid.hxx"
#include "arrdecl.hxx"
#include "progress.hxx"
// auto strip #include "objsh.hxx"
#include "docfac.hxx"
// auto strip #include "docfile.hxx"
// auto strip #include "docfilt.hxx"
#include "cfgmgr.hxx"
#include "fltfnc.hxx"
// auto strip #include "nfltdlg.hxx"
// auto strip #include "new.hxx"
// auto strip #include "bindings.hxx"
#include "dispatch.hxx"
// auto strip #include "viewsh.hxx"
// auto strip #include "genlink.hxx"
// auto strip #include "accmgr.hxx"

#ifndef _SVTOOLS_IMGDEF_HXX
#include <svtools/imgdef.hxx>
#endif

// auto strip #include "tbxmgr.hxx"
// auto strip #include "mnumgr.hxx"
// auto strip #include "topfrm.hxx"
// auto strip #include "newhdl.hxx"
#include "appdata.hxx"
// auto strip #include "openflag.hxx"
#include "app.hrc"
#include "interno.hxx"
#include "ipenv.hxx"
#include "intfrm.hxx"
// auto strip #include "virtmenu.hxx"
// auto strip #include "module.hxx"
// auto strip #include "sfxdir.hxx"
#include "event.hxx"
#include "appimp.hxx"
#include "imestatuswindow.hxx"

#ifdef DBG_UTIL
#include "tbxctrl.hxx"
// auto strip #include "stbitem.hxx"
// auto strip #include "mnuitem.hxx"
#endif

#if defined( WIN ) || defined( WNT ) || defined( OS2 )
#define DDE_AVAILABLE
#endif

#include <svtools/saveopt.hxx>
#include <svtools/undoopt.hxx>
#include <svtools/helpopt.hxx>
#include <svtools/pathoptions.hxx>
#include <svtools/viewoptions.hxx>
#include <svtools/moduleoptions.hxx>
#include <svtools/historyoptions.hxx>
#include <svtools/menuoptions.hxx>
#include <svtools/addxmltostorageoptions.hxx>
#include <svtools/miscopt.hxx>
#include <svtools/useroptions.hxx>
#include <svtools/startoptions.hxx>
#include <svtools/securityoptions.hxx>
#include <svtools/localisationoptions.hxx>
#include <svtools/inetoptions.hxx>
#include <svtools/fontoptions.hxx>
#include <svtools/internaloptions.hxx>
// auto strip #include <svtools/workingsetoptions.hxx>
#include <svtools/syslocaleoptions.hxx>
#include <svtools/syslocale.hxx>
#include <framework/addonsoptions.hxx>
// auto strip #ifndef _SVTOOLS_TTPROPS_HXX // handmade
// auto strip #include <svtools/ttprops.hxx>
// auto strip #endif
#include <svtools/extendedsecurityoptions.hxx>

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {

// Static member
SfxApplication* SfxApplication::pApp = NULL;

static SvtSaveOptions *pSaveOptions = NULL;
static SvtUndoOptions *pUndoOptions = NULL;
static SvtHelpOptions *pHelpOptions = NULL;
static SvtModuleOptions *pModuleOptions = NULL;
static SvtHistoryOptions *pHistoryOptions = NULL;
static SvtMenuOptions *pMenuOptions = NULL;
static SvtAddXMLToStorageOptions *pXMLOptions = NULL;
static SvtMiscOptions *pMiscOptions = NULL;
static SvtUserOptions *pUserOptions = NULL;
static SvtStartOptions *pStartOptions = NULL;
static SvtSecurityOptions *pSecurityOptions = NULL;
static SvtLocalisationOptions *pLocalisationOptions = NULL;
static SvtInetOptions *pInetOptions = NULL;
static SvtFontOptions *pFontOptions = NULL;
static SvtInternalOptions *pInternalOptions = NULL;
static SvtSysLocaleOptions *pSysLocaleOptions = NULL;
static SvtSysLocale *pSysLocale = NULL;
static SvtExtendedSecurityOptions* pExtendedSecurityOptions = NULL;
static framework::AddonsOptions* pAddonsOptions = NULL;


class SfxPropertyHandler : public PropertyHandler
{
    virtual void Property( ApplicationProperty& );
};

static SfxPropertyHandler*  pPropertyHandler = 0;

/*N*/ SfxPropertyHandler* GetOrCreatePropertyHandler()
/*N*/ {
/*N*/   if ( !pPropertyHandler )
/*N*/   {
/*N*/       ::osl::MutexGuard aGuard( ::osl::Mutex::getGlobalMutex() );
/*N*/       if ( !pPropertyHandler )
/*N*/           pPropertyHandler = new SfxPropertyHandler;
/*N*/   }
/*N*/
/*N*/   return pPropertyHandler;
/*N*/ }

/*?*/ void SfxPropertyHandler::Property( ApplicationProperty& rProp )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 #if SUPD<613//MUSTINI
//STRIP001  SfxApplication* pApp = SFX_APP();
//STRIP001     SfxIniManager* pIni = pApp->GetIniManager();
//STRIP001
//STRIP001  // AppIniManger?
//STRIP001  SfxAppIniManagerProperty* pAppIniMgr = PTR_CAST(SfxAppIniManagerProperty, &rProp);
//STRIP001  if ( pAppIniMgr )
//STRIP001  {
//STRIP001      pAppIniMgr->SetIniManager( pIni );
//STRIP001      return;
//STRIP001  }
//STRIP001 #endif
//STRIP001  TTProperties* pTTProperties = PTR_CAST( TTProperties, &rProp );
//STRIP001  if ( pTTProperties )
//STRIP001  {
//STRIP001      pTTProperties->nPropertyVersion = TT_PROPERTIES_VERSION;
//STRIP001      switch ( pTTProperties->nActualPR )
//STRIP001      {
//STRIP001          case TT_PR_SLOTS:
//STRIP001          {
//STRIP001              pTTProperties->nSidOpenUrl = SID_OPENURL;
//STRIP001              pTTProperties->nSidFileName = SID_FILE_NAME;
//STRIP001              pTTProperties->nSidNewDocDirect = SID_NEWDOCDIRECT;
//STRIP001              pTTProperties->nSidCopy = SID_COPY;
//STRIP001              pTTProperties->nSidPaste = SID_PASTE;
//STRIP001              pTTProperties->nSidSourceView = SID_SOURCEVIEW;
//STRIP001              pTTProperties->nSidSelectAll = SID_SELECTALL;
//STRIP001              pTTProperties->nSidReferer = SID_REFERER;
//STRIP001              pTTProperties->nActualPR = 0;
//STRIP001          }
//STRIP001          break;
//STRIP001          case TT_PR_DISPATCHER:
//STRIP001          {
//STRIP001                 // interface for TestTool
//STRIP001              SfxViewFrame* pViewFrame;
//STRIP001              SfxDispatcher* pDispatcher;
//STRIP001              pViewFrame = SfxViewFrame::Current();
//STRIP001              if ( !pViewFrame )
//STRIP001                  pViewFrame = SfxViewFrame::GetFirst();
//STRIP001              if ( pViewFrame )
//STRIP001                  pDispatcher = pViewFrame->GetDispatcher();
//STRIP001              else
//STRIP001                  pDispatcher = NULL;
//STRIP001              if ( !pDispatcher )
//STRIP001                  pTTProperties->nActualPR = TT_PR_ERR_NODISPATCHER;
//STRIP001              else
//STRIP001              {
//STRIP001                  pDispatcher->SetExecuteMode(EXECUTEMODE_DIALOGASYNCHRON);
//STRIP001                     if ( pTTProperties->mnSID == SID_NEWDOCDIRECT
//STRIP001                       || pTTProperties->mnSID == SID_OPENDOC )
//STRIP001                     {
//STRIP001                         pTTProperties->mnSID;
//STRIP001                         SfxPoolItem** pArgs = pTTProperties->mppArgs;
//STRIP001                         SfxAllItemSet aSet( SFX_APP()->GetPool() );
//STRIP001                         if ( pArgs && *pArgs )
//STRIP001                         {
//STRIP001                             for ( SfxPoolItem **pArg = pArgs; *pArg; ++pArg )
//STRIP001                                 aSet.Put( **pArg );
//STRIP001                         }
//STRIP001                         if ( pTTProperties->mnSID == SID_NEWDOCDIRECT )
//STRIP001                         {
//STRIP001                             String aFactory = String::CreateFromAscii("private:factory/");
//STRIP001                             if ( pArgs && *pArgs )
//STRIP001                             {
//STRIP001                                 SFX_ITEMSET_ARG( &aSet, pFactoryName, SfxStringItem, SID_NEWDOCDIRECT, FALSE );
//STRIP001                                 if ( pFactoryName )
//STRIP001                                     aFactory += pFactoryName->GetValue();
//STRIP001                                 else
//STRIP001                                     aFactory += String::CreateFromAscii("swriter");
//STRIP001                             }
//STRIP001                             else
//STRIP001                                 aFactory += String::CreateFromAscii("swriter");
//STRIP001
//STRIP001                             aSet.Put( SfxStringItem( SID_FILE_NAME, aFactory ) );
//STRIP001                             aSet.ClearItem( SID_NEWDOCDIRECT );
//STRIP001                             pTTProperties->mnSID = SID_OPENDOC;
//STRIP001                         }
//STRIP001
//STRIP001                         aSet.Put( SfxStringItem( SID_TARGETNAME, DEFINE_CONST_UNICODE("_blank") ) );
//STRIP001                         if ( pDispatcher->ExecuteFunction( pTTProperties->mnSID, aSet, pTTProperties->mnMode )
//STRIP001                                     == EXECUTE_NO )
//STRIP001                             pTTProperties->nActualPR = TT_PR_ERR_NOEXECUTE;
//STRIP001                         else
//STRIP001                             pTTProperties->nActualPR = 0;
//STRIP001                     }
//STRIP001                     else
//STRIP001                     {
//STRIP001                         if ( pDispatcher->ExecuteFunction(
//STRIP001                                 pTTProperties->mnSID, pTTProperties->mppArgs, pTTProperties->mnMode )
//STRIP001                             == EXECUTE_NO )
//STRIP001                             pTTProperties->nActualPR = TT_PR_ERR_NOEXECUTE;
//STRIP001                         else
//STRIP001                             pTTProperties->nActualPR = 0;
//STRIP001                     }
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001 /*
//STRIP001          case TT_PR_IMG:
//STRIP001          {
//STRIP001              SvDataMemberObjectRef aDataObject = new SvDataMemberObject();
//STRIP001              SvData* pDataBmp = new SvData( FORMAT_BITMAP );
//STRIP001              pDataBmp->SetData( pTTProperties->mpBmp );
//STRIP001              aDataObject->Append( pDataBmp );
//STRIP001              aDataObject->CopyClipboard();
//STRIP001              pTTProperties->nActualPR = 0;
//STRIP001          }
//STRIP001          break;
//STRIP001 */
//STRIP001          default:
//STRIP001          {
//STRIP001              pTTProperties->nPropertyVersion = 0;
//STRIP001          }
//STRIP001      }
//STRIP001      return;
//STRIP001  }
/*?*/ }

/*N*/ SfxApplication* SfxApplication::GetOrCreate()
/*N*/ {
/*N*/   ::osl::MutexGuard aGuard( ::osl::Mutex::getGlobalMutex() );
/*N*/
/*N*/   // SFX on demand
/*N*/     if ( !pApp )
/*N*/     {
/*N*/       ::com::sun::star::uno::Reference < ::com::sun::star::lang::XInitialization >
/*N*/           xWrp(::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance( DEFINE_CONST_UNICODE("com.sun.star.office.OfficeWrapper")), ::com::sun::star::uno::UNO_QUERY );
/*N*/           xWrp->initialize( ::com::sun::star::uno::Sequence < ::com::sun::star::uno::Any >() );
/*N*/ //        SfxApplication *pNew = new SfxApplication;
/*N*/ //        pNew->StartUpScreen( NULL );
/*N*/ //        SetApp( pNew );
/*N*/     }
/*N*/
/*N*/   return pApp;
/*N*/ }

/*N*/ void SfxApplication::SetApp( SfxApplication* pSfxApp )
/*N*/ {
/*N*/   static ::osl::Mutex aProtector;
/*N*/   ::osl::MutexGuard aGuard( aProtector );
/*N*/
/*N*/ #if SUPD>637
/*N*/   RTL_LOGFILE_CONTEXT( aLog, "sfx2 (mb93783) ::SfxApplication::SetApp" );
/*N*/ #endif
/*N*/   DBG_ASSERT( !pApp, "SfxApplication already created!" );
/*N*/   if ( pApp )
/*?*/       DELETEZ( pApp );
/*N*/
/*N*/     pApp = pSfxApp;
/*N*/
/*N*/     // at the moment a bug may occur when Initialize_Impl returns FALSE, but this is only temporary because all code that may cause such a
/*N*/     // fault will be moved outside the SFX
/*N*/     pApp->Initialize_Impl();
/*N*/ }

/*N*/ SfxApplication::SfxApplication()
/*N*/   : _nFeatures( ULONG_MAX )
/*N*/   , pImp( 0 )
/*N*/   , pAppData_Impl( 0 )
/*N*/     , pMenuMgr( 0 )
/*N*/   , pAcceleratorMgr( 0 )
/*N*/   , pStatusBarMgr( 0 )
/*N*/   , pAppDispat( 0 )
/*N*/   , bDispatcherLocked( sal_False )
/*N*/   , pResMgr( 0 )
/*N*/     , pCfgMgr( 0 )
/*N*/     , pSlotPool( 0 )
/*N*/   , pInterfaces( 0 )
/*N*/     , bInInit( sal_False )
/*N*/     , bInExit( sal_False )
/*N*/     , bDowning( sal_True )
/*N*/   , bCreatedExternal( sal_False )
/*N*/   , pOptions( 0 )
/*N*/   , pViewFrame( 0 )
/*N*/   , pImageMgr( 0 )
/*N*/   , nInterfaces( 0 )
/*N*/ {
/*N*/ #if SUPD>637
/*N*/   RTL_LOGFILE_CONTEXT( aLog, "sfx2 (mb93783) ::SfxApplication::SfxApplication" );
/*N*/ #endif
/*N*/
/*N*/   GetpApp()->SetPropertyHandler( GetOrCreatePropertyHandler() );
/*N*/
/*N*/ #if SUPD>637
/*N*/   RTL_LOGFILE_CONTEXT_TRACE( aLog, "{ precreate svtools options objects" );
/*N*/ #endif
/*N*/     pSaveOptions = new SvtSaveOptions;
/*N*/     pUndoOptions = new SvtUndoOptions;
/*N*/     pHelpOptions = new SvtHelpOptions;
/*N*/     pModuleOptions = new SvtModuleOptions;
/*N*/     pHistoryOptions = new SvtHistoryOptions;
/*N*/     pMenuOptions = new SvtMenuOptions;
/*N*/     pXMLOptions = new SvtAddXMLToStorageOptions;
/*N*/     pMiscOptions = new SvtMiscOptions;
/*N*/     pUserOptions = new SvtUserOptions;
/*N*/     pStartOptions = new SvtStartOptions;
/*N*/     pSecurityOptions = new SvtSecurityOptions;
/*N*/     pLocalisationOptions = new SvtLocalisationOptions;
/*N*/     pInetOptions = new SvtInetOptions;
/*N*/     pFontOptions = new SvtFontOptions;
/*N*/     pInternalOptions = new SvtInternalOptions;
/*N*/     pSysLocaleOptions = new SvtSysLocaleOptions;
/*N*/   pExtendedSecurityOptions = new SvtExtendedSecurityOptions;
/*N*/   pAddonsOptions = new framework::AddonsOptions;
/*N*/     SvtViewOptions::AcquireOptions();
/*N*/ #if SUPD>637
/*N*/   RTL_LOGFILE_CONTEXT_TRACE( aLog, "} precreate svtools options objects" );
/*N*/ #endif
/*N*/
/*
#if SUPD>637
    RTL_LOGFILE_CONTEXT_TRACE( aLog, "{ UCB_Helper::Initialize" );
#endif
    UCB_Helper::Initialize();
#if SUPD>637
    RTL_LOGFILE_CONTEXT_TRACE( aLog, "} UCB_Helper::Initialize" );
#endif
*/
/*N*/   pImp = new SfxApplication_Impl;
/*N*/   pImp->bConfigLoaded = sal_False;
/*N*/   pImp->pEmptyMenu = 0;
/*N*/   pImp->nDocNo = 0;
/*N*/   pImp->pIntro = 0;
/*N*/   pImp->pTbxCtrlFac = 0;
/*N*/   pImp->pStbCtrlFac = 0;
/*N*/   pImp->pViewFrames = 0;
/*N*/   pImp->pObjShells = 0;
/*N*/   pImp->bAutoSaveNow = sal_False;
/*N*/   pImp->pTemplateDlg = 0;
/*N*/   pImp->pBasicMgr = 0;
/*N*/   pImp->pBasicLibContainer = 0;
/*N*/   pImp->pDialogLibContainer = 0;
/*N*/   pImp->pBasicTestWin = 0;
/*N*/   pImp->pSfxResManager = 0;
/*N*/   pImp->pSimpleResManager = 0;
/*N*/   pImp->nWarnLevel = 0;
/*N*/   pImp->pAutoSaveTimer = 0;
/*AS
#if SUPD>637
    RTL_LOGFILE_CONTEXT_TRACE( aLog, "{ set locale settings" );
#endif
    String sLanguage = SvtPathOptions().SubstituteVariable(String::CreateFromAscii("$(langid)"));
    LanguageType eUILanguage = (LanguageType) sLanguage.ToInt32();
    LanguageType eLanguage = pSysLocaleOptions->GetLocaleLanguageType();
    AllSettings aSettings( Application::GetSettings() );
    aSettings.SetUILanguage( eUILanguage );
    aSettings.SetLanguage( eLanguage );
    Application::SetSettings( aSettings );

#if SUPD>637
    RTL_LOGFILE_CONTEXT_TRACE( aLog, "} set locale settings" );
#endif
*/
/*N*/     // Create instance of SvtSysLocale _after_ setting the locale at the application,
/*N*/     // so that it can initialize itself correctly.
/*N*/     pSysLocale = new SvtSysLocale;
/*N*/
/*N*/   pAppData_Impl = new SfxAppData_Impl( this );
/*N*/   pAppData_Impl->UpdateApplicationSettings( SvtMenuOptions().IsEntryHidingEnabled() );
/*N*/     pAppData_Impl->m_xImeStatusWindow->init();
/*N*/     pApp->PreInit();
/*N*/
/*N*/ #if SUPD>637
/*N*/   RTL_LOGFILE_CONTEXT_TRACE( aLog, "{ create SfxConfigManager" );
/*N*/ #endif
/*N*/     pCfgMgr = new SfxConfigManager;
/*N*/ #if SUPD>637
/*N*/   RTL_LOGFILE_CONTEXT_TRACE( aLog, "} create SfxConfigManager" );
/*N*/ #endif
/*N*/
/*N*/ #if SUPD>637
/*N*/   RTL_LOGFILE_CONTEXT_TRACE( aLog, "{ initialize DDE" );
/*N*/ #endif
/*N*/ #ifdef DDE_AVAILABLE
/*N*/ #ifdef PRODUCT
/*N*/     InitializeDde();
/*N*/ #else
/*N*/     if( !InitializeDde() )
/*N*/     {
/*?*/         ByteString aStr( "Kein DDE-Service moeglich. Fehler: " );
/*?*/         if( GetDdeService() )
/*?*/             aStr += ByteString::CreateFromInt32(GetDdeService()->GetError());
/*?*/         else
/*?*/             aStr += '?';
/*?*/         DBG_ASSERT( sal_False, aStr.GetBuffer() )
/*N*/     }
/*N*/ #endif
/*N*/ #endif
/*N*/ #if SUPD>637
/*N*/   RTL_LOGFILE_CONTEXT_TRACE( aLog, "} initialize DDE" );
/*N*/ #endif
/*N*/ }

/*N*/ SfxApplication::~SfxApplication()
/*N*/ {
/*N*/   // delete global options
/*N*/   SvtViewOptions::ReleaseOptions();
/*N*/     delete pSaveOptions;
/*N*/     delete pUndoOptions;
/*N*/     delete pHelpOptions;
/*N*/     delete pModuleOptions;
/*N*/     delete pHistoryOptions;
/*N*/     delete pMenuOptions;
/*N*/     delete pXMLOptions;
/*N*/     delete pMiscOptions;
/*N*/     delete pUserOptions;
/*N*/     delete pStartOptions;
/*N*/     delete pSecurityOptions;
/*N*/     delete pLocalisationOptions;
/*N*/     delete pInetOptions;
/*N*/     delete pFontOptions;
/*N*/     delete pInternalOptions;
/*N*/     delete pSysLocaleOptions;
/*N*/     delete pSysLocale;
/*N*/   delete pExtendedSecurityOptions;
/*N*/   delete pAddonsOptions;
/*N*/
/*N*/     if ( !bDowning )
/*?*/         Deinitialize();
/*N*/
/*N*/   Broadcast( SfxSimpleHint(SFX_HINT_DYING) );
/*N*/
/*N*/     // better call SvFactory::DeInit, because this will remove ALL factories,
/*N*/     // but it will fail because the ConfigManager has a storage that is a SvObject
/*N*/     SfxObjectFactory::RemoveAll_Impl();
/*N*/
/*N*/ //    UCB_Helper::Deinitialize();
/*N*/
/*N*/     delete pCfgMgr;
/*N*/   delete pImp;
/*N*/     delete pAppData_Impl;
/*N*/     pApp = 0;
/*N*/ }

//====================================================================

class SfxResourceTimer : public Timer
{
    sal_uInt16 *pnWarnLevel;
public:
    SfxResourceTimer(sal_uInt16 *pn, sal_uInt32 nTimeOut) : pnWarnLevel(pn)
    { SetTimeout(nTimeOut); Start(); }
    virtual void Timeout() { --*pnWarnLevel; delete this; }
};

//--------------------------------------------------------------------

//====================================================================

//STRIP001 void SfxApplication::LockDispatcher
//STRIP001 (
//STRIP001     sal_Bool bLock              /*  sal_True
//STRIP001                                 schaltet alle SfxDispatcher ein
//STRIP001
//STRIP001                                 sal_False
//STRIP001                                 schaltet alle SfxDispatcher aus */
//STRIP001 )
//STRIP001
//STRIP001 /*  [Beschreibung]
//STRIP001
//STRIP001     Mit dieser Methode werden alle Dispatcher der Applikation global
//STRIP001     blockiert (bLock==sal_True) bzw. grundsaetzlich freigegeben
//STRIP001     (bLock==sal_False).
//STRIP001
//STRIP001     Unabhaengig von diesem zentralen Schalter kann jeder Dispatcher
//STRIP001     einzeln gelockt sein:
//STRIP001
//STRIP001         Dispatcher X    global      =>  gesamt
//STRIP001
//STRIP001         gelockt         gelockt     =>  gelockt
//STRIP001         freigegeben     gelockt     =>  gelockt
//STRIP001         gelockt         freigegeben =>  gelockt
//STRIP001         freigegeben     freigegeben =>  freigegeben
//STRIP001
//STRIP001     Wenn der aktive Dispatcher gelockt ist, werden keine Requests mehr
//STRIP001     dispatcht.
//STRIP001
//STRIP001     [Querverweise]
//STRIP001     <SfxDispatcher::Lock(sal_Bool)> */
//STRIP001
//STRIP001 {
//STRIP001     bDispatcherLocked = bLock;
//STRIP001     if ( !bLock )
//STRIP001     {
//STRIP001         GetDispatcher_Impl()->InvalidateBindings_Impl( pAppData_Impl->bInvalidateOnUnlock );
//STRIP001         pAppData_Impl->bInvalidateOnUnlock = sal_False;
//STRIP001     }
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 SfxObjectShell* SfxApplication::GetActiveObjectShell() const
//STRIP001
//STRIP001 /*  [Beschreibung]
//STRIP001
//STRIP001     Diese Methode liefert einen Zeiger auf die aktive <SfxObjectShell>-
//STRIP001     Instanz oder einen 0-Pointer, falls keine SfxObjectShell-Instanz
//STRIP001     aktiv ist.
//STRIP001 */
//STRIP001
//STRIP001 {
//STRIP001     if ( pViewFrame )
//STRIP001         return pViewFrame->GetObjectShell();
//STRIP001     return 0;
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 sal_Bool IsTemplate_Impl( const String& aPath )
//STRIP001 {
//STRIP001     INetURLObject aObj( aPath );
//STRIP001     DBG_ASSERT( aObj.GetProtocol() != INET_PROT_NOT_VALID, "Invalid URL!" );
//STRIP001
//STRIP001  if ( aObj.getExtension().CompareIgnoreCaseToAscii( "vor" ) == COMPARE_EQUAL )
//STRIP001      return sal_True;
//STRIP001
//STRIP001  SvEaMgr aMgr( aPath );
//STRIP001  String aType;
//STRIP001
//STRIP001  if ( aMgr.GetFileType(aType) )
//STRIP001  {
//STRIP001      const SfxFilter* pFilter = SFX_APP()->GetFilterMatcher().GetFilter4EA( aType );
//STRIP001      if( pFilter && pFilter->IsOwnTemplateFormat() )
//STRIP001          return sal_True;
//STRIP001  }
//STRIP001
//STRIP001  return sal_False;
//STRIP001 }

extern void FATToVFat_Impl( String& );

#if 0
String GetURL_Impl( const String& rName )
{
    // if the filename is a physical name, it is the client file system, not the file system
    // of the machine where the office is running ( if this are different machines )
    // so in the remote case we can't handle relative filenames as arguments, because they
    // are parsed relative to the program path
    // the file system of the client is addressed through the "file:" protocol
    ::rtl::OUString aProgName, aTmp;
    ::vos::OStartupInfo aInfo;
    aInfo.getExecutableFile( aProgName );
    aTmp = aProgName;
    INetURLObject aObj( aTmp );
    bool bWasAbsolute;
    INetURLObject aURL = aObj.smartRel2Abs( rName, bWasAbsolute );
    return aURL.GetMainURL(INetURLObject::NO_DECODE);
}

/*?*/ void SfxApplication::HandleAppEvent( const ApplicationEvent& rAppEvent )
/*?*/ {
/*?*/     if ( rAppEvent.IsOpenEvent() )
/*?*/     {
/*?*/         // die Parameter enthalten die zu "offnenden Dateien
/*?*/         for(sal_uInt16 i=0;i<rAppEvent.GetParamCount();i++)
/*?*/         {
/*?*/             // Dateiname rausholen
/*?*/             String aName( rAppEvent.GetParam(i) );
/*?*/             if ( COMPARE_EQUAL == aName.CompareToAscii("/userid:",8) )
/*?*/                 continue;
/*?*/ #ifdef WNT
/*?*/             FATToVFat_Impl( aName );
/*?*/ #endif
/*?*/             aName = GetURL_Impl(aName);
/*?*/             SfxStringItem aFileName( SID_FILE_NAME, aName );
/*?*/
/*?*/             // is it a template ?
/*?*/             const SfxPoolItem* pItem = NULL;
/*?*/             SfxBoolItem aTemplate( SID_TEMPLATE, TRUE );
/*?*/             if ( IsTemplate_Impl( aName ) )
/*?*/                 pItem = &aTemplate;
/*?*/
/*?*/             // open the document
/*?*/             if ( pItem || !DocAlreadyLoaded( aName, sal_True, sal_True, sal_False ) )
/*?*/             {
/*?*/                 SfxBoolItem aNewView( SID_OPEN_NEW_VIEW, sal_False );
/*?*/                 SfxStringItem aTargetName( SID_TARGETNAME, DEFINE_CONST_UNICODE("_blank") );
/*?*/                 SfxStringItem aReferer( SID_REFERER, DEFINE_CONST_UNICODE("private:OpenEvent") );
/*?*/                 pAppDispat->Execute( SID_OPENDOC, SFX_CALLMODE_SYNCHRON,
/*?*/                         &aTargetName, &aFileName, &aNewView, &aReferer, pItem, 0L );
/*?*/             }
/*?*/         }
/*?*/     }
/*?*/     else if(rAppEvent.IsPrintEvent() )
/*?*/     {
/*?*/         // loop on parameters: files to print and name of printer
/*?*/         SfxStringItem aPrinterName(SID_PRINTER_NAME, String());
/*?*/         for (sal_uInt16 i=0;i<rAppEvent.GetParamCount();i++)
/*?*/         {
/*?*/             // is the parameter a printername ?
/*?*/             String aName(rAppEvent.GetParam(i));
/*?*/             if(aName.Len()>1 && *aName.GetBuffer()=='@')
/*?*/             {
/*?*/                 aPrinterName.SetValue( aName.Copy(1) );
/*?*/                 continue;
/*?*/             }
/*?*/
/*?*/ #ifdef WNT
/*?*/             FATToVFat_Impl( aName );
/*?*/ #endif
/*?*/             SfxStringItem aTargetName( SID_TARGETNAME, DEFINE_CONST_UNICODE("_blank") );
/*?*/             SfxStringItem aFileName( SID_FILE_NAME, GetURL_Impl( aName ) );
/*?*/             SfxBoolItem aNewView(SID_OPEN_NEW_VIEW, sal_True);
/*?*/             SfxBoolItem aHidden(SID_HIDDEN, sal_True);
/*?*/             SfxBoolItem aSilent(SID_SILENT, sal_True);
/*?*/             const SfxPoolItem *pRet = pAppDispat->Execute( SID_OPENDOC, SFX_CALLMODE_SYNCHRON,
/*?*/                     &aTargetName, &aFileName, &aNewView, &aHidden, &aSilent, 0L );
/*?*/             if ( !pRet )
/*?*/                 continue;
/*?*/
/*?*/             const SfxViewFrameItem *pFrameItem = PTR_CAST(SfxViewFrameItem, pRet);
/*?*/             if ( pFrameItem && pFrameItem->GetFrame() )
/*?*/             {
/*?*/                 SfxViewFrame *pFrame = pFrameItem->GetFrame();
/*?*/                 SfxBoolItem aSilent( SID_SILENT, sal_True );
/*?*/                 pFrame->GetDispatcher()->Execute( SID_PRINTDOC, SFX_CALLMODE_SYNCHRON,
/*?*/                         &aPrinterName, &aSilent, 0L );
/*?*/                 pFrame->GetFrame()->DoClose();
/*?*/             }
/*?*/         }
/*?*/     }
/*?*/     else if ( rAppEvent.GetEvent() == "APPEAR" )
/*?*/     {
/*?*/         if( !pAppData_Impl->bInvisible )
/*?*/         {
/*?*/             ::com::sun::star::uno::Reference< ::com::sun::star::frame::XFramesSupplier >
/*?*/                     xDesktop( ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance( OUSTRING(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.frame.Desktop")) ),
/*?*/                     ::com::sun::star::uno::UNO_QUERY );
/*?*/             ::com::sun::star::uno::Reference< ::com::sun::star::frame::XFrame > xTask = xDesktop->getActiveFrame();
/*?*/             if ( !xTask.is() )
/*?*/             {
/*?*/                 // If no frame is currently active - we searh for any other one which exist in general.
/*?*/                 ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess > xList( xDesktop->getFrames(), ::com::sun::star::uno::UNO_QUERY );
/*?*/                 sal_Int32 nCount = xList->getCount();
/*?*/                 if (nCount>0)
/*?*/                 {
/*?*/                     ::com::sun::star::uno::Any aItem = xList->getByIndex(0);
/*?*/                     if ( !(aItem>>=xTask) || !xTask.is() )
/*?*/                         pAppData_Impl->bInvisible = TRUE;
/*?*/                 }
/*?*/             }
/*?*/
/*?*/             if ( xTask.is() )
/*?*/             {
/*?*/                 Window* pWindow = VCLUnoHelper::GetWindow( xTask->getContainerWindow() );
/*?*/                 pWindow->ToTop();
/*?*/             }
/*?*/         }
/*?*/
/*?*/         if( pAppData_Impl->bInvisible )
/*?*/         {
/*?*/             pAppData_Impl->bInvisible = FALSE;
/*?*/             OpenClients();
/*?*/         }
/*?*/     }
/*?*/ }
/*?*/ #endif

//--------------------------------------------------------------------

//STRIP001 long SfxAppFocusChanged_Impl( void* pObj, void* pArg )
//STRIP001 {
//STRIP001 /*
//STRIP001  SfxApplication *pApp = SFX_APP();
//STRIP001     if ( pApp && !pApp->IsDowning() )
//STRIP001     {
//STRIP001         Help* pHelp = Application::GetHelp();
//STRIP001         Window* pFocusWindow = Application::GetFocusWindow();
//STRIP001         if ( pHelp && pFocusWindow )
//STRIP001         {
//STRIP001             sal_uInt32 nId = pFocusWindow->GetHelpId();
//STRIP001             while ( !nId && pFocusWindow )
//STRIP001             {
//STRIP001                 pFocusWindow = pFocusWindow->GetParent();
//STRIP001                 nId = pFocusWindow ? pFocusWindow->GetHelpId() : 0;
//STRIP001             }
//STRIP001             ((SfxHelp_Impl*)pHelp)->SlotExecutedOrFocusChanged(
//STRIP001                 nId, sal_False, SvtHelpOptions().IsHelpAgentAutoStartMode() );
//STRIP001         }
//STRIP001     }
//STRIP001  */
//STRIP001  return 0;
//STRIP001 }

//STRIP001 void SfxApplication::FocusChanged()
//STRIP001 {
//STRIP001     static svtools::AsynchronLink *pFocusCallback = new svtools::AsynchronLink( Link( 0, SfxAppFocusChanged_Impl ) );
//STRIP001  pFocusCallback->Call( this, sal_True );
//STRIP001 }

//--------------------------------------------------------------------

/*N*/ const String& SfxApplication::GetLastDir_Impl() const

/*  [Beschreibung]

    Interne Methode, mit der im SFx das zuletzt mit der Methode
    <SfxApplication::SetLastDir_Impl()> gesetzte Verzeichnis
    zurueckgegeben wird.

    Dieses ist i.d.R. das zuletzt durch den SfxFileDialog
    angesprochene Verzeichnis.

    [Querverweis]
    <SfxApplication::SetLastDir_Impl()>
*/

/*N*/ {
/*N*/     return pAppData_Impl->aLastDir;
/*N*/ }

//STRIP001 const String& SfxApplication::GetLastSaveDirectory() const

//STRIP001 /*  [Beschreibung]
//STRIP001
//STRIP001     Wie <SfxApplication::GetLastDir_Impl()>, nur extern
//STRIP001
//STRIP001     [Querverweis]
//STRIP001     <SfxApplication::GetLastDir_Impl()>
//STRIP001 */
//STRIP001
//STRIP001 {
//STRIP001     return GetLastDir_Impl();
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 void SfxApplication::SetLastDir_Impl
//STRIP001 (
//STRIP001     const String&   rNewDir     /*  kompletter Verzeichnis-Pfad als String */
//STRIP001     )
//STRIP001
//STRIP001 /*  [Beschreibung]
//STRIP001
//STRIP001     Interne Methode, mit der ein Verzeichnis-Pfad gesetzt wird, der
//STRIP001     zuletzt (z.B. durch den SfxFileDialog) angesprochen wurde.
//STRIP001
//STRIP001     [Querverweis]
//STRIP001     <SfxApplication::GetLastDir_Impl()>
//STRIP001 */
//STRIP001
//STRIP001 {
//STRIP001     pAppData_Impl->aLastDir = rNewDir;
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 const String& SfxApplication::GetLastFilter_Impl() const
//STRIP001 {
//STRIP001     return pAppData_Impl->aLastFilter;
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 void SfxApplication::SetLastFilter_Impl( const String &rNewFilter )
//STRIP001 {
//STRIP001     pAppData_Impl->aLastFilter = rNewFilter;
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 SfxDispatcher* SfxApplication::GetDispatcher_Impl()
//STRIP001 {
//STRIP001     return pViewFrame? pViewFrame->GetDispatcher(): pAppDispat;
//STRIP001 }

//--------------------------------------------------------------------
/*N*/ void SfxApplication::SetViewFrame( SfxViewFrame *pFrame )
/*N*/ {
/*N*/     if( pFrame && !pFrame->IsSetViewFrameAllowed_Impl() )
/*N*/         return;
/*N*/
/*N*/     if ( pFrame != pViewFrame )
/*N*/     {
/*N*/         if ( !pFrame && !bDowning )
/*N*/         {
/*N*/             // activate any frame to avoid CurrentViewFrame == NULL
/*N*/             SfxFrameArr_Impl& rArr = *pAppData_Impl->pTopFrames;
/*N*/             for( sal_uInt16 nPos = rArr.Count(); nPos--; )
/*N*/             {
/*N*/                 SfxFrame* pCurFrame = rArr[ nPos ];
/*N*/                 SfxViewFrame* pView = pCurFrame->GetCurrentViewFrame();
/*N*/                 if ( pView && pView != pViewFrame )
/*N*/                 {
/*N*/                     pFrame = pView;
/*N*/                     break;
/*N*/                 }
/*N*/             }
/*N*/         }
/*N*/
/*N*/       // check if activated or deactivated frame is a InPlaceFrame
/*N*/       SfxInPlaceFrame *pOld = PTR_CAST( SfxInPlaceFrame, pViewFrame );
/*N*/         SfxInPlaceFrame *pNew = PTR_CAST( SfxInPlaceFrame, pFrame );
/*N*/
/*N*/       // get the containerframes ( if one of the frames is an InPlaceFrame )
/*N*/         SfxViewFrame *pOldContainerFrame = pViewFrame;
/*N*/         while ( pOldContainerFrame && pOldContainerFrame->GetParentViewFrame_Impl() )
/*?*/             pOldContainerFrame = pOldContainerFrame->GetParentViewFrame_Impl();
/*N*/         SfxViewFrame *pNewContainerFrame = pFrame;
/*N*/         while ( pNewContainerFrame && pNewContainerFrame->GetParentViewFrame_Impl() )
/*?*/             pNewContainerFrame = pNewContainerFrame->GetParentViewFrame_Impl();
/*N*/
/*N*/       // DocWinActivate : both frames belong to the same TopWindow
/*N*/       // TopWinActivate : both frames belong to different TopWindows
/*N*/       BOOL bDocWinActivate = pOldContainerFrame && pNewContainerFrame &&
/*N*/                   pOldContainerFrame->GetTopViewFrame() == pNewContainerFrame->GetTopViewFrame();
/*N*/       BOOL bTaskActivate = pOldContainerFrame != pNewContainerFrame;
/*N*/         if ( pViewFrame )
/*N*/         {
/*N*/             if ( bTaskActivate )
/*N*/             {
/*N*/                 // prepare UI for deacivation
/*N*/                 pViewFrame->GetFrame()->Deactivate_Impl();
/*N*/
/*N*/                 if ( pOld )
/*N*/                 {
/*?*/                   // broadcast deactivation event
/*?*/                   NotifyEvent( SfxEventHint( SFX_EVENT_DEACTIVATEDOC, pViewFrame->GetObjectShell() ) );
/*?*/
/*?*/                   // inplace deactivation needed
/*?*/                     SvInPlaceClient *pCli = pOldContainerFrame->GetViewShell() ? pOldContainerFrame->GetViewShell()->GetIPClient() : NULL;
/*?*/                     if ( pCli && pCli->GetProtocol().IsUIActive() )
/*?*/                     {
/*?*/                         if ( bDocWinActivate )
/*?*/                         {
/*?*/                             pCli->GetIPObj()->GetIPEnv()->DoShowUITools( sal_False );
/*?*/                             pCli->GetProtocol().DocWinActivate( sal_False );
/*?*/                         }
/*?*/                         else
/*?*/                             pCli->GetProtocol().TopWinActivate( sal_False );
/*N*/                     }
/*N*/               }
/*N*/             }
/*N*/         }
/*N*/
/*N*/       if ( pOldContainerFrame )
/*N*/       {
/*N*/           if ( bTaskActivate )
/*N*/               NotifyEvent( SfxEventHint( SFX_EVENT_DEACTIVATEDOC, pOldContainerFrame->GetObjectShell() ) );
/*N*/           pOldContainerFrame->DoDeactivate( bTaskActivate, pFrame );
/*N*/
/*N*/           if( pOldContainerFrame->GetProgress() )
/*?*/               pOldContainerFrame->GetProgress()->Suspend();
/*N*/       }
/*N*/
/*N*/       pViewFrame = pFrame;
/*N*/
/*N*/         SfxWorkWindow* pWork = pViewFrame ? pViewFrame->GetFrame()->GetWorkWindow_Impl() : NULL;
/*N*/         Window* pWin = pWork ? pWork->GetTopWindow() : NULL;
/*N*/         const SfxObjectShell* pSh = pViewFrame ? pViewFrame->GetObjectShell() : 0;
/*N*/         if ( !pSh )
/*N*/         {
/*N*/             // otherwise BaseURL is set in activation of document
/*N*/             INetURLObject aObject( SvtPathOptions().GetWorkPath() );
/*N*/           aObject.setFinalSlash();
/*N*/             INetURLObject::SetBaseURL( aObject.GetMainURL( INetURLObject::NO_DECODE ) );
/*N*/         }
/*N*/
/*N*/         if( pNewContainerFrame )
/*N*/       {
/*N*/             pNewContainerFrame->DoActivate( bTaskActivate );
/*N*/           if ( bTaskActivate )
/*N*/               pNewContainerFrame->GetObjectShell()->PostActivateEvent_Impl();
/*N*/
/*N*/             SfxProgress *pProgress = pNewContainerFrame->GetProgress();
/*N*/             if ( pProgress )
/*N*/             {
/*?*/                 if( pProgress->IsSuspended() )
/*?*/                     pProgress->Resume();
/*?*/                 else
/*?*/                     pProgress->SetState( pProgress->GetState() );
/*N*/             }
/*N*/
/*N*/             if ( !pNew )
/*N*/             {
/*N*/                 SfxDispatcher* pDisp = pViewFrame->GetDispatcher();
/*N*/                 pDisp->Flush();
/*N*/                 pDisp->Update_Impl(sal_True);
/*N*/           }
/*N*/       }
/*N*/
/*N*/         if ( pViewFrame && pViewFrame->GetViewShell() )
/*N*/         {
/*N*/           if ( bTaskActivate )
/*N*/           {
/*N*/               if ( pNew )
/*N*/               {
/*?*/                   // Activate IPClient if present
/*?*/                   SvInPlaceClient *pCli = pNewContainerFrame->GetViewShell()->GetIPClient();
/*?*/                   if ( pCli && pCli->GetProtocol().IsUIActive() )
/*?*/                   {
/*?*/                       if ( bDocWinActivate )
/*?*/                       {
/*?*/                           pCli->GetIPObj()->GetIPEnv()->DoShowUITools( sal_True );
/*?*/                           pCli->GetProtocol().DocWinActivate( sal_True );
/*?*/                       }
/*?*/                       else
/*?*/                           pCli->GetProtocol().TopWinActivate( sal_True );
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/     }
/*N*/ }

//--------------------------------------------------------------------

//--------------------------------------------------------------------

//STRIP001 sal_uInt32 SfxApplication::DetectFilter( const String &rFileName,
//STRIP001                                     const SfxFilter **ppFilter,
//STRIP001                                     sal_uInt16 nFilterClass )
//STRIP001 {
//STRIP001     SfxMedium aSfxMedium(rFileName,(STREAM_READ | STREAM_SHARE_DENYNONE),sal_False);
//STRIP001
//STRIP001     return DetectFilter(aSfxMedium, ppFilter, nFilterClass );
//STRIP001 }

//-------------------------------------------------------------------------

//STRIP001 sal_uInt32 SfxApplication::DetectFilter(
//STRIP001     SfxMedium& rMedium,const SfxFilter **ppFilter, sal_uInt16 nFilterClass )
//STRIP001 {
//STRIP001     const SfxFilter *pFilter=0;
//STRIP001     SvEaMgr aMgr( rMedium.GetName() );
//STRIP001     String aType;
//STRIP001     if ( !SfxObjectFactory::HasObjectFactories() )
//STRIP001         return 1; HACK(Error-Code verwenden) ;
//STRIP001
//STRIP001     SfxFilterMatcher rMatcher( SfxObjectFactory::GetDefaultFactory().GetFilterContainer()  );
//STRIP001     if( aMgr.GetFileType( aType ))
//STRIP001         pFilter = rMatcher.GetFilter4EA( aType );
//STRIP001
//STRIP001     if( !pFilter)
//STRIP001     {
//STRIP001         if ( !rMedium.IsRemote() )
//STRIP001         {
//STRIP001             SvStorageRef aStor = rMedium.GetStorage();
//STRIP001             if ( !aStor.Is() )
//STRIP001                 return ERRCODE_IO_GENERAL;
//STRIP001             pFilter = rMatcher.GetFilter4ClipBoardId(aStor->GetFormat());
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             // Finden anhand der Extension
//STRIP001             pFilter = rMatcher.GetFilter4Extension( INetURLObject( rMedium.GetName() ).GetName() );
//STRIP001             if ( pFilter && pFilter->UsesStorage() )
//STRIP001                 pFilter = 0;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     if(pFilter)
//STRIP001         *ppFilter=pFilter;
//STRIP001
//STRIP001     return pFilter? 0: 1; HACK(Error-Code verwenden)
//STRIP001 }



//--------------------------------------------------------------------

//STRIP001 SfxNewFileDialog*  SfxApplication::CreateNewDialog()
//STRIP001 {
//STRIP001  return new SfxNewFileDialog(GetTopWindow(), SFXWB_DOCINFO | SFXWB_PREVIEW );
//STRIP001 }

//--------------------------------------------------------------------

/*N*/ const SfxFilter* SfxApplication::GetFilter
/*N*/ (
/*N*/     const SfxObjectFactory &rFact,
/*N*/     const String &rFilterName
/*N*/     )   const
/*N*/ {
/*N*/     DBG_ASSERT( rFilterName.Search( ':' ) == STRING_NOTFOUND,
/*N*/                 "SfxApplication::GetFilter erwartet unqualifizierte Namen" );
/*N*/     return rFact.GetFilterContainer()->GetFilter4FilterName(rFilterName);
/*N*/ }

//--------------------------------------------------------------------

//STRIP001 short SfxApplication::QuerySave_Impl( SfxObjectShell& rDoc, sal_Bool bAutoSave )
//STRIP001 {
//STRIP001     if ( !rDoc.IsModified() )
//STRIP001         return RET_NO;
//STRIP001
//STRIP001     String aMsg( SfxResId( STR_ISMODIFIED ) );
//STRIP001     aMsg.SearchAndReplaceAscii( "%1", rDoc.GetTitle() );
//STRIP001
//STRIP001     SfxFrame *pFrame = SfxViewFrame::GetFirst(&rDoc)->GetFrame();
//STRIP001     pFrame->Appear();
//STRIP001
//STRIP001  WinBits nBits = WB_YES_NO_CANCEL;
//STRIP001  nBits |= bAutoSave ? WB_DEF_YES : WB_DEF_NO;
//STRIP001     QueryBox aBox( &pFrame->GetWindow(), nBits, aMsg );
//STRIP001
//STRIP001     if ( bAutoSave )
//STRIP001         aBox.SetText( String( SfxResId( STR_AUTOSAVE ) ) );
//STRIP001
//STRIP001     return aBox.Execute();
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 sal_Bool SfxApplication::IsInException() const
//STRIP001 {
//STRIP001     return pAppData_Impl->bInException;
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 sal_uInt16 SfxApplication::Exception( sal_uInt16 nError )
//STRIP001 {
//STRIP001     if ( pAppData_Impl->bInException )
//STRIP001         Application::Abort( pImp->aDoubleExceptionString );
//STRIP001
//STRIP001     pAppData_Impl->bInException = sal_True;
//STRIP001
//STRIP001     if( SfxNewHdl::Get() )
//STRIP001     {
//STRIP001         SfxNewHdl::Get()->FlushWarnMem();
//STRIP001         SfxNewHdl::Get()->FlushExceptMem();
//STRIP001     }
//STRIP001
//STRIP001     INetURLObject aSaveObj( SvtPathOptions().GetBackupPath() );
//STRIP001
//STRIP001     // save all modified documents and close all documents
//STRIP001  // Do it only, if it's allowed! Ask configuration for right flag.
//STRIP001     if( Application::IsInExecute() )
//STRIP001     {
//STRIP001         SfxObjectShell *pIter, *pNext;
//STRIP001         for(pIter = SfxObjectShell::GetFirst(); pIter; pIter = pNext)
//STRIP001         {
//STRIP001             pNext = SfxObjectShell::GetNext(*pIter);
//STRIP001             if( pIter->IsModified() && pIter->GetName().CompareToAscii("BasicIDE") != COMPARE_EQUAL && !pIter->IsLoading() )
//STRIP001             {
//STRIP001                 //try
//STRIP001                 {
//STRIP001                     // backup unsaved document
//STRIP001                     SFX_ITEMSET_ARG( pIter->GetMedium()->GetItemSet(), pPassItem, SfxStringItem, SID_PASSWORD, sal_False );
//STRIP001                     SfxRequest aReq(SID_SAVEASDOC, SFX_CALLMODE_SYNCHRON, pIter->GetPool());
//STRIP001
//STRIP001                     sal_Bool     bHadName    = pIter->HasName()                  ;
//STRIP001                     INetURLObject    aOldURL( pIter->GetMedium()->GetName() );
//STRIP001                     String           aOldName    = pIter->GetTitle()                 ;
//STRIP001
//STRIP001                     const SfxFilter *pFilter = pIter->GetMedium()->GetFilter();
//STRIP001                     const SfxFilter *pOrigFilter = pFilter;
//STRIP001                     if ( !pFilter || ( pFilter->GetFilterFlags() & SFX_FILTER_PACKED ) || !( pFilter->GetFilterFlags() & SFX_FILTER_EXPORT ) )
//STRIP001                         // packed files must be saved with default format, but remember original filter !
//STRIP001                         pFilter = pIter->GetFactory().GetFilter(0);
//STRIP001
//STRIP001                  String aSaveName, aSavePath = aSaveObj.GetMainURL( INetURLObject::NO_DECODE );
//STRIP001                     String aFilterName;
//STRIP001                     if ( pFilter )
//STRIP001                  {
//STRIP001                         aFilterName = pFilter->GetFilterName();
//STRIP001                      ::utl::TempFile aTempFile( &aSavePath );
//STRIP001                      aSaveName = aTempFile.GetURL();
//STRIP001                  }
//STRIP001                     else
//STRIP001                  {
//STRIP001                      String aExt( DEFINE_CONST_UNICODE( ".sav" ) );
//STRIP001                      ::utl::TempFile aTempFile( DEFINE_CONST_UNICODE( "exc" ), &aExt, &aSavePath );
//STRIP001                      aSaveName = aTempFile.GetURL();
//STRIP001                  }
//STRIP001
//STRIP001                     aReq.AppendItem( SfxStringItem( SID_FILE_NAME, aSaveName ) );
//STRIP001                     aReq.AppendItem( SfxStringItem( SID_FILTER_NAME, aFilterName ) );
//STRIP001                     if ( pPassItem )
//STRIP001                         aReq.AppendItem( *pPassItem );
//STRIP001
//STRIP001                     pIter->ExecuteSlot(aReq);
//STRIP001
//STRIP001                  pInternalOptions->PushRecoveryItem( bHadName ? aOldURL.GetMainURL( INetURLObject::NO_DECODE ) : aOldName                ,
//STRIP001                                                         pOrigFilter ? pOrigFilter->GetFilterName() : aFilterName      ,
//STRIP001                                                      aSaveName                                               );
//STRIP001                 }
//STRIP001                 /*catch ( ::Exception & )
//STRIP001                 {
//STRIP001                 }*/
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         if ( ( nError & EXC_MAJORTYPE ) != EXC_DISPLAY && ( nError & EXC_MAJORTYPE ) != EXC_REMOTE )
//STRIP001         {
//STRIP001             Window *pTopWindow = GetTopWindow(); // GCC needs temporary
//STRIP001             WarningBox( pTopWindow, SfxResId(STR_RECOVER_PREPARED) ).Execute();
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     // transfer configuration data
//STRIP001     ::utl::ConfigManager::GetConfigManager()->StoreConfigItems();
//STRIP001
//STRIP001     // make sure that it is written to disk
//STRIP001     ::com::sun::star::uno::Reference< ::com::sun::star::lang::XComponent >
//STRIP001         xProvider( ::utl::ConfigManager::GetConfigManager()->GetConfigurationProvider(), ::com::sun::star::uno::UNO_QUERY );
//STRIP001     if ( xProvider.is() )
//STRIP001         xProvider->dispose();
//STRIP001
//STRIP001     switch( nError & EXC_MAJORTYPE )
//STRIP001     {
//STRIP001         case EXC_USER:
//STRIP001          if( nError == EXC_OUTOFMEMORY )
//STRIP001              Application::Abort( pImp->aMemExceptionString );
//STRIP001             break;
//STRIP001
//STRIP001         case EXC_RSCNOTLOADED:
//STRIP001             Application::Abort( pImp->aResExceptionString );
//STRIP001             break;
//STRIP001
//STRIP001         case EXC_SYSOBJNOTCREATED:
//STRIP001             Application::Abort( pImp->aSysResExceptionString );
//STRIP001             break;
//STRIP001     }
//STRIP001
//STRIP001     pAppData_Impl->bInException = sal_False;
//STRIP001     return 0;
//STRIP001 }

//---------------------------------------------------------------------

/*N*/ ResMgr* SfxApplication::CreateResManager( const char *pPrefix )
/*N*/ {
/*N*/     String aMgrName = String::CreateFromAscii( pPrefix );
/*N*/     aMgrName += String::CreateFromInt32(SOLARUPD); // aktuelle Versionsnummer
/*N*/     return ResMgr::CreateResMgr(U2S(aMgrName));
/*N*/ }

//---------------------------------------------------------------------

//STRIP001 SimpleResMgr* SfxApplication::CreateSimpleResManager()
//STRIP001 {
//STRIP001  SimpleResMgr    *pRet;
//STRIP001  ::rtl::OUString sAppName;
//STRIP001
//STRIP001  if ( ::vos::OStartupInfo().getExecutableFile(sAppName) != ::vos::OStartupInfo::E_None )
//STRIP001      sAppName = ::rtl::OUString();
//STRIP001
//STRIP001  const AllSettings& rAllSettings = Application::GetSettings();
//STRIP001     LanguageType nType = rAllSettings.GetUILanguage();
//STRIP001  String sTemp( sAppName );
//STRIP001  pRet = new SimpleResMgr( CREATEVERSIONRESMGR_NAME(sfx), nType, &sTemp, 0 );
//STRIP001
//STRIP001  return pRet;
//STRIP001 }

//--------------------------------------------------------------------

/*N*/ ResMgr* SfxApplication::GetSfxResManager()
/*N*/ {
/*N*/     if ( !pImp->pSfxResManager )
/*N*/         pImp->pSfxResManager = CreateResManager("bf_sfx");    //STRIP005
/*N*/     return pImp->pSfxResManager;
/*N*/ }

//--------------------------------------------------------------------

//STRIP001 ResMgr* SfxApplication::GetLabelResManager() const
//STRIP001 {
//STRIP001     return pAppData_Impl->pLabelResMgr;
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 SimpleResMgr* SfxApplication::GetSimpleResManager()
//STRIP001 {
//STRIP001     if ( !pImp->pSimpleResManager )
//STRIP001     {
//STRIP001      pImp->pSimpleResManager = CreateSimpleResManager();
//STRIP001     }
//STRIP001     return pImp->pSimpleResManager;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 void SfxApplication::SetProgress_Impl
//STRIP001 (
//STRIP001     SfxProgress *pProgress  /*  zu startender <SfxProgress> oder 0, falls
//STRIP001                                 der Progress zurueckgesetzt werden soll */
//STRIP001 )
//STRIP001
//STRIP001 /*  [Beschreibung]
//STRIP001
//STRIP001     Interne Methode zum setzen oder zuruecksetzen des Progress-Modes
//STRIP001     fuer die gesamte Applikation.
//STRIP001 */
//STRIP001
//STRIP001 {
//STRIP001     DBG_ASSERT( ( !pAppData_Impl->pProgress && pProgress ) ||
//STRIP001                 ( pAppData_Impl->pProgress && !pProgress ),
//STRIP001                 "Progress acitivation/deacitivation mismatch" );
//STRIP001
//STRIP001     if ( pAppData_Impl->pProgress && pProgress )
//STRIP001     {
//STRIP001         pAppData_Impl->pProgress->Suspend();
//STRIP001         pAppData_Impl->pProgress->UnLock();
//STRIP001         delete pAppData_Impl->pProgress;
//STRIP001     }
//STRIP001
//STRIP001     pAppData_Impl->pProgress = pProgress;
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ sal_uInt16 SfxApplication::GetFreeIndex()
/*N*/ {
/*N*/     return pAppData_Impl->aIndexBitSet.GetFreeIndex()+1;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void SfxApplication::ReleaseIndex(sal_uInt16 i)
/*N*/ {
/*N*/     pAppData_Impl->aIndexBitSet.ReleaseIndex(i-1);
/*N*/ }

//--------------------------------------------------------------------

//STRIP001 void SfxApplication::EnterAsynchronCall_Impl()
//STRIP001 {
//STRIP001     ++pAppData_Impl->nAsynchronCalls;
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 void SfxApplication::LeaveAsynchronCall_Impl()
//STRIP001 {
//STRIP001     --pAppData_Impl->nAsynchronCalls;
//STRIP001 }

//--------------------------------------------------------------------

/*?*/ FASTBOOL SfxApplication::IsInAsynchronCall_Impl() const
/*?*/ {
/*?*/     return pAppData_Impl->nAsynchronCalls > 0;
/*?*/ }

//--------------------------------------------------------------------

/*N*/ Window* SfxApplication::GetTopWindow() const
/*N*/ {
/*N*/     SfxWorkWindow* pWork = GetWorkWindow_Impl( SfxViewFrame::Current() );
/*N*/     return pWork ? pWork->GetWindow() : NULL;
/*N*/ }

//--------------------------------------------------------------------

//STRIP001 void SfxApplication::SetTopWindow( WorkWindow *pWindow )
//STRIP001 {
//STRIP001 /*
//STRIP001     sal_Bool bMode = sal_True;
//STRIP001     if ( !pWindow || pWindow == GetAppWindow() )
//STRIP001         bMode = sal_False;
//STRIP001
//STRIP001     SfxPlugInFrame* pPlug = PTR_CAST( SfxPlugInFrame,
//STRIP001         GetViewFrame()->GetTopViewFrame() );
//STRIP001     if ( pPlug )
//STRIP001         pPlug->GetEnv_Impl()->SetPresentationMode( bMode, pWindow );
//STRIP001     else
//STRIP001         GetAppWindow()->SetPresentationMode( bMode, pWindow );
//STRIP001 */
//STRIP001 }

/*N*/ sal_Bool SfxApplication::IsPlugin()
/*N*/ {
/*N*/     // ask property of desktop to get this information
/*N*/   sal_Bool bReturn = sal_False;
/*N*/     ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > xDesktop( ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance( OUSTRING(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.frame.Desktop")) ), ::com::sun::star::uno::UNO_QUERY );
/*N*/     if(xDesktop.is())
/*N*/     {
/*N*/         ::com::sun::star::uno::Any aVal = xDesktop->getPropertyValue( ::rtl::OUString::createFromAscii("IsPlugged") );
/*N*/         aVal >>= bReturn;
/*N*/     }
/*N*/
/*N*/   return bReturn;
/*N*/ }

//--------------------------------------------------------------------

//STRIP001 String SfxApplication::LocalizeDBName
//STRIP001 (
//STRIP001     SfxDBNameConvert eConvert,
//STRIP001     const String& rList,
//STRIP001     char aDel
//STRIP001 ) const
//STRIP001 {
//STRIP001 /*    String  aActName;
//STRIP001     String  aResult;
//STRIP001     String  aNationalName = SfxResId(STR_ADDRESS_NAME);
//STRIP001     String  aIniName( "Address" );
//STRIP001     sal_uInt16  nCnt = rList.GetTokenCount( aDel );
//STRIP001
//STRIP001     for( sal_uInt16 i=0 ; i<nCnt ; i++ )
//STRIP001     {
//STRIP001         aActName = rList.GetToken( i, aDel );
//STRIP001
//STRIP001         if( eConvert == INI2NATIONAL )
//STRIP001         {
//STRIP001             if( aActName == aIniName )
//STRIP001                 aResult += aNationalName;
//STRIP001             else
//STRIP001                 aResult += aActName;
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             if( aActName == aNationalName )
//STRIP001                 aResult += aIniName;
//STRIP001             else
//STRIP001                 aResult += aActName;
//STRIP001         }
//STRIP001
//STRIP001         aResult += aDel;
//STRIP001     }
//STRIP001
//STRIP001     aResult.EraseTrailingChars( aDel );
//STRIP001
//STRIP001     return aResult;*/
//STRIP001
//STRIP001     return rList;
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 IMPL_STATIC_LINK( SfxApplication, CookieAlertHdl_Impl, void*, EMPTYARG )
//STRIP001 {
//STRIP001     return 0;
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 void SfxApplication::SetUserEMailAddress( const String &rEMail )
//STRIP001 {
//STRIP001     DBG_ERROR( "Obsolete call!" );
//STRIP001 }

//-------------------------------------------------------------------------

//STRIP001 void SfxApplication::SetDefFocusWindow( Window *pWin )
//STRIP001
//STRIP001 /*  [Beschreibung]
//STRIP001
//STRIP001     Mit dieser Methode wird das Window gesetzt, auf das beim n"achsten
//STRIP001     <SfxApplication::GrabFocus()> der Focus gesetzt werden soll.
//STRIP001
//STRIP001     Ein 'SetDefFocusWindow()' wirkt f"ur genau einen einzigen Aufruf von
//STRIP001     'SfxApplication::GrabFocus()'.
//STRIP001
//STRIP001     Damit kann z.B. das in verschiedenen Situationen von Windows kommende
//STRIP001     Focus-Setzen auf MDIWindows verhindert werden.
//STRIP001 */
//STRIP001
//STRIP001 {
//STRIP001     pAppData_Impl->pDefFocusWin = pWin;
//STRIP001 }

//-------------------------------------------------------------------------

//STRIP001 void SfxApplication::GrabFocus( Window *pAlternate )
//STRIP001
//STRIP001 /*  [Beschreibung]
//STRIP001
//STRIP001     Mit dieser Methode wird der Focus auf das zuvor mit der Methode
//STRIP001     <SfxApplicaton::SetDefFocusWindow()> gesetzte Window gegrabt. Ist
//STRIP001     keins mehr gesetzt oder wurde es bereits verwendet, wird der Focus
//STRIP001     auf 'pAlternate' gesetzt. Ein 'SetDefFocusWindow()' wirkt f"ur genau
//STRIP001     ein einziges 'SfxApplication::GrabFocus()'.
//STRIP001 */
//STRIP001
//STRIP001 {
//STRIP001     Window *pWin = pAppData_Impl->pDefFocusWin
//STRIP001                         ? pAppData_Impl->pDefFocusWin
//STRIP001                         : pAlternate;
//STRIP001     pWin->GrabFocus();
//STRIP001     pAppData_Impl->pDefFocusWin = 0;
//STRIP001 }


/*N*/ SfxStatusBarManager* SfxApplication::GetStatusBarManager() const
/*N*/ {
/*N*/     if ( !pViewFrame )
/*N*/         return NULL;
/*N*/
/*?*/     SfxViewFrame *pTop = pViewFrame;
/*?*/     while ( pTop->GetParentViewFrame_Impl() )
/*?*/         pTop = pTop->GetParentViewFrame_Impl();
/*?*/
/*?*/     return pTop->GetFrame()->GetWorkWindow_Impl()->GetStatusBarManager_Impl();
/*N*/ }

/*N*/ SfxViewFrame* SfxApplication::GetViewFrame()
/*N*/ {
/*N*/   return pViewFrame;
/*N*/ }

//STRIP001 UniqueIndex* SfxApplication::GetEventHandler_Impl()
//STRIP001 {
//STRIP001  return pImp->pEventHdl;
//STRIP001 }

/*N*/ SfxTbxCtrlFactArr_Impl&     SfxApplication::GetTbxCtrlFactories_Impl() const
/*N*/ {
/*N*/   return *pImp->pTbxCtrlFac;
/*N*/ }

/*N*/ SfxStbCtrlFactArr_Impl&     SfxApplication::GetStbCtrlFactories_Impl() const
/*N*/ {
/*N*/   return *pImp->pStbCtrlFac;
/*N*/ }

/*N*/ SfxMenuCtrlFactArr_Impl&    SfxApplication::GetMenuCtrlFactories_Impl() const
/*N*/ {
/*N*/   return *pImp->pMenuCtrlFac;
/*N*/ }

/*N*/ SfxViewFrameArr_Impl&       SfxApplication::GetViewFrames_Impl() const
/*N*/ {
/*N*/   return *pImp->pViewFrames;
/*N*/ }

/*N*/ SfxViewShellArr_Impl&       SfxApplication::GetViewShells_Impl() const
/*N*/ {
/*N*/   return *pImp->pViewShells;
/*N*/ }

/*N*/ SfxObjectShellArr_Impl&     SfxApplication::GetObjectShells_Impl() const
/*N*/ {
/*N*/   return *pImp->pObjShells;
/*N*/ }

/*?*/ void SfxApplication::Invalidate( USHORT nId )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     for( SfxViewFrame* pFrame = SfxViewFrame::GetFirst(); pFrame; pFrame = SfxViewFrame::GetNext( *pFrame ) )
//STRIP001         Invalidate_Impl( pFrame->GetBindings(), nId );
/*?*/ }
}
