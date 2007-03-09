/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_app.cxx,v $
 *
 *  $Revision: 1.12 $
 *
 *  last change: $Author: obo $ $Date: 2007-03-09 14:50:48 $
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

#if defined UNX
#include <limits.h>
#else // UNX
#include <stdlib.h>
#define PATH_MAX _MAX_PATH
#endif // UNX

#include <svtools/svdde.hxx>
#include <tools/urlobj.hxx>

#define _SVSTDARR_STRINGSDTOR

#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif

#include <rtl/logfile.hxx>

#include <appuno.hxx>
#include "arrdecl.hxx"
#include "progress.hxx"
#include "docfac.hxx"
#include "cfgmgr.hxx"
#include "fltfnc.hxx"
#include "dispatch.hxx"
#include "workwin.hxx"

#ifndef _SVTOOLS_IMGDEF_HXX
#include <svtools/imgdef.hxx>
#endif

#include "appdata.hxx"
#include "app.hrc"
#include "interno.hxx"
#include "intfrm.hxx"
#include "event.hxx"
#include "appimp.hxx"
#include "imestatuswindow.hxx"

#ifdef DBG_UTIL
#include "tbxctrl.hxx"
#endif

#if defined( WIN ) || defined( WNT ) || defined( OS2 )
// #i30187# DDE not needed for binfilter #define DDE_AVAILABLE
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
#include <svtools/syslocaleoptions.hxx>
#include <svtools/syslocale.hxx>
#include <framework/addonsoptions.hxx>
#include <svtools/extendedsecurityoptions.hxx>

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
#ifndef _SV_SYSWIN_HXX
#include <vcl/syswin.hxx>
#endif
#include "so3/staticbaseurl.hxx"
#include <so3/ipenv.hxx>
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
/*N*/   RTL_LOGFILE_CONTEXT( aLog, "sfx2 (mb93783) ::SfxApplication::SetApp" );
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
/*N*/   RTL_LOGFILE_CONTEXT( aLog, "sfx2 (mb93783) ::SfxApplication::SfxApplication" );
/*N*/
/*N*/   GetpApp()->SetPropertyHandler( GetOrCreatePropertyHandler() );
/*N*/
/*N*/   RTL_LOGFILE_CONTEXT_TRACE( aLog, "{ precreate svtools options objects" );
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
/*N*/   RTL_LOGFILE_CONTEXT_TRACE( aLog, "} precreate svtools options objects" );
/*N*/
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
/*N*/   pImp->pBasicLibContainer = 0;
/*N*/   pImp->pDialogLibContainer = 0;
/*N*/   pImp->pBasicTestWin = 0;
/*N*/   pImp->pSfxResManager = 0;
/*N*/   pImp->pSimpleResManager = 0;
/*N*/   pImp->nWarnLevel = 0;
/*N*/   pImp->pAutoSaveTimer = 0;
/*N*/     // Create instance of SvtSysLocale _after_ setting the locale at the application,
/*N*/     // so that it can initialize itself correctly.
/*N*/     pSysLocale = new SvtSysLocale;
/*N*/
/*N*/   pAppData_Impl = new SfxAppData_Impl( this );
/*N*/   pAppData_Impl->UpdateApplicationSettings( SvtMenuOptions().IsEntryHidingEnabled() );
/*N*/     pAppData_Impl->m_xImeStatusWindow->init();
/*N*/     pApp->PreInit();
/*N*/
/*N*/   RTL_LOGFILE_CONTEXT_TRACE( aLog, "{ create SfxConfigManager" );
/*N*/     pCfgMgr = new SfxConfigManager;
/*N*/   RTL_LOGFILE_CONTEXT_TRACE( aLog, "} create SfxConfigManager" );
/*N*/
/*N*/   RTL_LOGFILE_CONTEXT_TRACE( aLog, "{ initialize DDE" );
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
/*N*/   RTL_LOGFILE_CONTEXT_TRACE( aLog, "} initialize DDE" );
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

extern void FATToVFat_Impl( String& );


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
/*N*/             so3::StaticBaseUrl::SetBaseURL( aObject.GetMainURL( INetURLObject::NO_DECODE ) );
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

//---------------------------------------------------------------------

/*N*/ ResMgr* SfxApplication::CreateResManager( const char *pPrefix )
/*N*/ {
/*N*/     String aMgrName = String::CreateFromAscii( pPrefix );
/*N*/     aMgrName += String::CreateFromInt32(SOLARUPD); // aktuelle Versionsnummer
/*N*/     return ResMgr::CreateResMgr(U2S(aMgrName));
/*N*/ }

//--------------------------------------------------------------------

/*N*/ ResMgr* SfxApplication::GetSfxResManager()
/*N*/ {
/*N*/     if ( !pImp->pSfxResManager )
/*N*/         pImp->pSfxResManager = CreateResManager("bf_sfx");    //STRIP005
/*N*/     return pImp->pSfxResManager;
/*N*/ }

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

//-------------------------------------------------------------------------

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
/*?*/ }
}
