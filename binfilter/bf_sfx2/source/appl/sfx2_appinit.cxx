/*************************************************************************
 *
 *  $RCSfile: sfx2_appinit.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: aw $ $Date: 2004-02-13 14:30:27 $
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

#include "app.hxx"

#ifndef _COM_SUN_STAR_FRAME_XTERMINATELISTENER_HPP_
#include <com/sun/star/frame/XTerminateListener.hpp>
#endif
#ifndef _COM_SUN_STAR_UNO_REFERENCE_HXX_
#include <com/sun/star/uno/Reference.hxx>
#endif
#ifndef _COM_SUN_STAR_FRAME_XDESKTOP_HPP_
#include <com/sun/star/frame/XDesktop.hpp>
#endif

#include <svtools/svtools.hrc>
#include <svtools/saveopt.hxx>
#include <svtools/localisationoptions.hxx>

#ifndef _CONFIG_HXX
#include <tools/config.hxx>
#endif
#ifndef _SV_RESARY_HXX
#include <tools/resary.hxx>
#endif

#ifndef _SOERR_HXX //autogen
#include <so3/soerr.hxx>
#endif
#ifndef _SFXINTITEM_HXX //autogen
#include <svtools/intitem.hxx>
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#ifndef _SFXSTRITEM_HXX //autogen
#include <svtools/stritem.hxx>
#endif
#ifndef _INETBND_HXX //autogen
#include <so3/inetbnd.hxx>
#endif
#ifndef _MSGBOX_HXX //autogen
#include <vcl/msgbox.hxx>
#endif
#ifndef _EHDL_HXX
#include <svtools/ehdl.hxx>
#endif
#include <svtools/inethist.hxx>
#ifndef _UNOTOOLS_PROCESSFACTORY_HXX
#include <comphelper/processfactory.hxx>
#endif
#ifndef _RTL_USTRBUF_HXX_
#include <rtl/ustrbuf.hxx>
#endif
#ifndef _VOS_SECURITY_HXX_
#include <vos/security.hxx>
#endif
#ifndef _UCBHELPER_CONFIGURATIONKEYS_HXX_
#include <ucbhelper/configurationkeys.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_PATHOPTIONS_HXX
#include <svtools/pathoptions.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_HISTORYOPTIONS_HXX
#include <svtools/historyoptions.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_MODULEOPTIONS_HXX
#include <svtools/moduleoptions.hxx>
#endif

#if SUPD>637
#include <rtl/logfile.hxx>
#endif

#pragma hdrstop

#include "unoctitm.hxx"
#include "appimp.hxx"
#include "accmgr.hxx"
#include "app.hrc"
#include "sfxlocal.hrc"
#include "appdata.hxx"
#include "arrdecl.hxx"
#include "cfgmgr.hxx"
#include "dispatch.hxx"
#include "docfac.hxx"
#include "evntconf.hxx"
#include "frameobj.hxx"
#include "fsetobsh.hxx"
#include "fsetview.hxx"
#include "imgmgr.hxx"
#include "interno.hxx"
#include "intro.hxx"
#include "macrconf.hxx"
#include "mnumgr.hxx"
#include "msgpool.hxx"
#include "newhdl.hxx"
#include "plugobj.hxx"
#include "progress.hxx"
#include "sfxhelp.hxx"
#include "sfxresid.hxx"
#include "sfxtypes.hxx"
#include "stbmgr.hxx"
#include "tbxconf.hxx"
#include "viewsh.hxx"
#include "eacopier.hxx"
#include "nochaos.hxx"
#include "fcontnr.hxx"
#include "helper.hxx"   // SfxContentHelper::Kill()
#include "sfxpicklist.hxx"

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {

#ifdef UNX
#define stricmp(a,b) strcmp(a,b)
#endif

#ifdef MAC
int svstricmp( const char* pStr1, const char* pStr2);
#define stricmp svstricmp
#endif

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star;

void doFirstTimeInit();

class SfxTerminateListener_Impl : public ::cppu::WeakImplHelper1< XTerminateListener  >
{
public:
    virtual void SAL_CALL queryTermination( const EventObject& aEvent ) throw( TerminationVetoException, RuntimeException );
    virtual void SAL_CALL notifyTermination( const EventObject& aEvent ) throw( RuntimeException );
    virtual void SAL_CALL disposing( const EventObject& Source ) throw( RuntimeException );
};

/*N*/ void SAL_CALL SfxTerminateListener_Impl::disposing( const EventObject& Source ) throw( RuntimeException )
/*N*/ {
/*N*/ }

/*N*/ void SAL_CALL SfxTerminateListener_Impl::queryTermination( const EventObject& aEvent ) throw(TerminationVetoException, RuntimeException )
/*N*/ {
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/     if ( !SFX_APP()->QueryExit_Impl() )
/*?*/         throw TerminationVetoException();
/*N*/ }

/*N*/ void SAL_CALL SfxTerminateListener_Impl::notifyTermination( const EventObject& aEvent ) throw(RuntimeException )
/*N*/ {
/*N*/     Reference< XDesktop > xDesktop( aEvent.Source, UNO_QUERY );
/*N*/     if( xDesktop.is() == sal_True )
/*N*/         xDesktop->removeTerminateListener( this );
/*N*/
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/     SfxApplication* pApp = SFX_APP();
/*N*/     pApp->Get_Impl()->aLateInitTimer.Stop();
/*N*/     pApp->Broadcast( SfxSimpleHint( SFX_HINT_DEINITIALIZING ) );
/*N*/     pApp->Get_Impl()->pAppDispatch->ReleaseAll();
/*N*/     pApp->Get_Impl()->pAppDispatch->release();
/*N*/     pApp->NotifyEvent(SfxEventHint( SFX_EVENT_CLOSEAPP) );
/*N*/     pApp->Deinitialize();
/*N*/   Application::Quit();
/*N*/ }

//====================================================================

//====================================================================

/*N*/ FASTBOOL SfxApplication::Initialize_Impl()
/*N*/ {
/*N*/ #if SUPD>637
/*N*/   RTL_LOGFILE_CONTEXT( aLog, "sfx2 (mb93783) ::SfxApplication::Initialize_Impl" );
/*N*/ #endif
/*N*/
/*N*/ #ifdef TLX_VALIDATE
/*N*/   StgIo::SetErrorLink( LINK( this, SfxStorageErrHdl, Error ) );
/*N*/ #endif
/*N*/
/*N*/ //!   FSysEnableSysErrorBox( FALSE ); (pb) replaceable?
/*N*/
/*N*/     Reference < XDesktop > xDesktop ( ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance( DEFINE_CONST_UNICODE("com.sun.star.frame.Desktop") ), UNO_QUERY );
/*N*/     xDesktop->addTerminateListener( new SfxTerminateListener_Impl() );
/*N*/
/*N*/     if( !CheckTryBuy_Impl() )
/*N*/     {
/*?*/         exit(-1);
/*N*/         return FALSE;;
/*N*/     }
/*N*/
/*N*/   Application::EnableAutoHelpId();
/*N*/
/*N*/   pAppData_Impl->pAppDispatch = new SfxStatusDispatcher;
/*N*/   pAppData_Impl->pAppDispatch->acquire();
/*N*/
/*N*/   // SV-Look
/*N*/   Help::EnableContextHelp();
/*N*/   Help::EnableExtHelp();
/*N*/
/*N*/   SvtLocalisationOptions aLocalisation;
/*N*/   Application::EnableAutoMnemonic ( aLocalisation.IsAutoMnemonic() );
/*N*/   Application::SetDialogScaleX    ( (short)(aLocalisation.GetDialogScale()) );
/*N*/
/*N*/     // StarObjects initialisieren
/*N*/   if ( !SvFactory::Init() )
/*N*/       ErrorBox( 0, SfxResId(MSG_ERR_SOINIT) ).Execute();
/*N*/
/*N*/   // Factory f"ur das SfxFrameObject anlegen; da der Pointer in den AppDaten
/*N*/   // liegt, dieser aber nicht exportierbar ist, mu\s ein exportierbarer
/*N*/   // Wrapper angelegt werden
/*N*/   pAppData_Impl->pSfxFrameObjectFactoryPtr = new SfxFrameObjectFactoryPtr;
/*N*/   pAppData_Impl->pSfxFrameObjectFactoryPtr->pSfxFrameObjectFactory = SfxFrameObject::ClassFactory();
/*N*/   SvBindStatusCallback::SetProgressCallback( STATIC_LINK( 0, SfxProgress, DefaultBindingProgress ) );
/*N*/     INetURLHistory::GetOrCreate()->SetLocation( SvtPathOptions().GetUserConfigPath() );
/*N*/
/*N*/   // merken, falls Applikation normal gestartet wurde
//STRIP007  if ( pAppData_Impl->bDirectAliveCount )
//STRIP007      SvFactory::IncAliveCount();
/*N*/
/*N*/   pImp->pEventHdl = new UniqueIndex( 1, 4, 4 );
/*N*/     //InitializeDisplayName_Impl();
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/   // Der SimplerErrorHandler dient Debugzwecken. In der Product werden
/*N*/   // nichtgehandelte Fehler durch Errorcode 1 an SFX gegeben.
/*N*/   new SimpleErrorHandler;
/*N*/ #endif
/*N*/   new SfxErrorHandler(RID_ERRHDL, ERRCODE_AREA_TOOLS, ERRCODE_AREA_LIB1);
/*N*/   new SfxErrorHandler(
/*N*/       RID_SO_ERROR_HANDLER, ERRCODE_AREA_SO, ERRCODE_AREA_SO_END);
/*N*/   new SfxErrorHandler(
/*N*/       (RID_SJ_START +1), ERRCODE_AREA_JAVA, ERRCODE_AREA_JAVA_END);
/*N*/   new SfxErrorHandler(
/*N*/       RID_BASIC_START, ERRCODE_AREA_SBX, ERRCODE_AREA_SBX_END );
/*N*/
/*N*/   // diverse Pointer
/*N*/   pImp->pAutoSaveTimer = new Timer;
/*N*/   SfxPickList::GetOrCreate( SvtHistoryOptions().GetSize( ePICKLIST ) );
/*N*/
/*N*/   /////////////////////////////////////////////////////////////////
/*N*/
/*N*/   DBG_ASSERT( !pAppDispat, "AppDispatcher already exists" );
/*N*/   pAppDispat = new SfxDispatcher((SfxDispatcher*)0);
/*N*/   pSlotPool = new SfxSlotPool;
/*N*/   pImp->pTbxCtrlFac = new SfxTbxCtrlFactArr_Impl;
/*N*/   pImp->pStbCtrlFac = new SfxStbCtrlFactArr_Impl;
/*N*/   pImp->pMenuCtrlFac = new SfxMenuCtrlFactArr_Impl;
/*N*/   pImp->pViewFrames = new SfxViewFrameArr_Impl;
/*N*/   pImp->pViewShells = new SfxViewShellArr_Impl;
/*N*/   pImp->pObjShells = new SfxObjectShellArr_Impl;
/*N*/   nInterfaces = SFX_INTERFACE_APP+8;
/*N*/   pInterfaces = new SfxInterface*[nInterfaces];
/*N*/   memset( pInterfaces, 0, sizeof(SfxInterface*) * nInterfaces );
/*N*/
/*N*/     pAcceleratorMgr = new SfxAcceleratorManager( pCfgMgr );
/*N*/
/*N*/   pImageMgr = new SfxImageManager( NULL );
/*N*/     SfxNewHdl* pNewHdl = SfxNewHdl::GetOrCreate();
/*N*/
/*N*/   // Die Strings muessen leider zur Laufzeit gehalten werden, da wir bei
/*N*/   // einer ::com::sun::star::uno::Exception keine Resourcen mehr laden duerfen.
/*N*/   pImp->aMemExceptionString = pNewHdl->GetMemExceptionString();
/*N*/   pImp->aResWarningString       = String( SfxResId( STR_RESWARNING ) );
/*N*/   pImp->aResExceptionString     = String( SfxResId( STR_RESEXCEPTION ) );
/*N*/   pImp->aSysResExceptionString  = String( SfxResId( STR_SYSRESEXCEPTION ) );
/*N*/
/*N*/   Registrations_Impl();
/*N*/
/*N*/ //    ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/   ResStringArray aEventNames( SfxResId( EVENT_NAMES_ARY ) );
/*N*/
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_STARTAPP,        String(SfxResId(STR_EVENT_STARTAPP)),   aEventNames.GetString( 0 ) );
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_CLOSEAPP,        String(SfxResId(STR_EVENT_CLOSEAPP)),   aEventNames.GetString( 1 ) );
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_CREATEDOC,       String(SfxResId(STR_EVENT_CREATEDOC)),  aEventNames.GetString( 2 ) );
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_OPENDOC,         String(SfxResId(STR_EVENT_OPENDOC)),    aEventNames.GetString( 3 ) );
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_SAVEASDOC,       String(SfxResId(STR_EVENT_SAVEASDOC)),  aEventNames.GetString( 4 ) );
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_SAVEASDOCDONE,   String(SfxResId(STR_EVENT_SAVEASDOCDONE)),  aEventNames.GetString( 5 ) );
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_SAVEDOC,         String(SfxResId(STR_EVENT_SAVEDOC)),        aEventNames.GetString( 6 ) );
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_SAVEDOCDONE,     String(SfxResId(STR_EVENT_SAVEDOCDONE)),    aEventNames.GetString( 7 ) );
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_PREPARECLOSEDOC, String(SfxResId(STR_EVENT_PREPARECLOSEDOC)),aEventNames.GetString( 8 ) );
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_CLOSEDOC,        String(SfxResId(STR_EVENT_CLOSEDOC)),       aEventNames.GetString( 9 ) );
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_ACTIVATEDOC,     String(SfxResId(STR_EVENT_ACTIVATEDOC)),    aEventNames.GetString( 10 ) );
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_DEACTIVATEDOC,   String(SfxResId(STR_EVENT_DEACTIVATEDOC)),  aEventNames.GetString( 11 ) );
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_PRINTDOC,        String(SfxResId(STR_EVENT_PRINTDOC)),       aEventNames.GetString( 12 ) );
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_MODIFYCHANGED,   String(SfxResId(STR_EVENT_MODIFYCHANGED)), aEventNames.GetString( 13 ) );
/*N*/
/*N*/   // Subklasse initialisieren
/*N*/   bDowning = sal_False;
/*N*/   bInInit = sal_True;
/*N*/   Init();
/*N*/
/*N*/   // get CHAOS item pool...
/*N*/   pAppData_Impl->pPool = NoChaos::GetItemPool();
/*N*/   SetPool( pAppData_Impl->pPool );
/*N*/
/*N*/   InsertLateInitHdl( LINK(pNewHdl, SfxNewHdl, InitMem_Impl) );
/*N*/   InsertLateInitHdl( LINK(this, SfxApplication,SpecialService_Impl) );
/*N*/     InsertLateInitHdl( STATIC_LINK( pAppData_Impl, SfxAppData_Impl, CreateDocumentTemplates ) );
/*N*/
/*N*/   bInInit = sal_False;
/*N*/   if ( bDowning )
/*N*/       return sal_False;
/*N*/
/*N*/   // App-Dispatcher aufbauen
/*N*/   pAppDispat->Push(*this);
/*N*/     pAppDispat->Flush();
/*N*/   pAppDispat->DoActivate_Impl( sal_True );
/*N*/
/*N*/     SvtSaveOptions aSaveOptions;
/*N*/     pImp->pAutoSaveTimer->SetTimeout( aSaveOptions.GetAutoSaveTime() * 60000 );
/*N*/   pImp->pAutoSaveTimer->SetTimeoutHdl( LINK( pApp, SfxApplication, AutoSaveHdl_Impl ) );
/*N*/
/*N*/ //(dv)    if ( !pAppData_Impl->bBean )
/*N*/ //(mba)        doFirstTimeInit();
/*N*/
/*N*/ //    Application::PostUserEvent( LINK( this, SfxApplication, OpenClients_Impl ) );
/*N*/
/*N*/ //    DELETEZ(pImp->pIntro);
/*N*/
/*N*/     // start LateInit
/*N*/     SfxAppData_Impl *pAppData = Get_Impl();
/*N*/     pAppData->aLateInitTimer.SetTimeout( 250 );
/*N*/     pAppData->aLateInitTimer.SetTimeoutHdl( LINK( this, SfxApplication, LateInitTimerHdl_Impl ) );
/*N*/     pAppData->aLateInitTimer.Start();
/*N*/
/*N*/     return sal_True;
/*N*/ }

/*N*/ IMPL_LINK( SfxApplication, SpecialService_Impl, void*, pVoid )
/*N*/ {
/*N*/   if ( pAppData_Impl->bBean )
/*N*/           return 0;
/*N*/
/*N*/ #if SUPD<613//MUSTINI
/*N*/   String aWizard = GetIniManager()->Get( DEFINE_CONST_UNICODE("Common"), 0, 0, DEFINE_CONST_UNICODE("RunWizard") );
/*N*/   sal_Bool bRunWizard = (sal_Bool) (sal_uInt16) aWizard.ToInt32();
/*N*/     if ( bRunWizard )
/*N*/   {
/*N*/       SfxStringItem aReferer( SID_REFERER, DEFINE_CONST_UNICODE("private:user") );
/*N*/       SfxStringItem aMacro( SID_FILE_NAME, DEFINE_CONST_UNICODE("macro://#InternetSetup.Run.Main()") );
/*N*/ //(mba)        pAppDispat->Execute( SID_OPENDOC, SFX_CALLMODE_ASYNCHRON, &aMacro, &aReferer, 0L );
/*N*/         GetIniManager()->DeleteKey( DEFINE_CONST_UNICODE("Common"), DEFINE_CONST_UNICODE("RunWizard") );
/*N*/         GetIniManager()->Flush();
/*N*/   }
/*N*/     else if ( !pAppData_Impl->bBean )
/*N*/   {
/*N*/       // StarOffice registration
/*N*/       INetURLObject aORegObj( GetIniManager()->Get( SFX_KEY_USERCONFIG_PATH ), INET_PROT_FILE );
/*N*/       aORegObj.insertName( DEFINE_CONST_UNICODE( "oreg.ini" ) );
/*N*/         Config aCfg( aORegObj.PathToFileName() );
/*N*/         aCfg.SetGroup( "reg" );
/*N*/         sal_uInt16 nRegKey = (sal_uInt16) aCfg.ReadKey( "registration", "0" ).ToInt32();
/*N*/         if( nRegKey == 0 )
/*N*/             GetAppDispatcher_Impl()->Execute(SID_ONLINE_REGISTRATION_DLG, SFX_CALLMODE_ASYNCHRON);
/*N*/   }
/*N*/ #else
/*N*/     if ( !pAppData_Impl->bBean )
/*N*/   {
/*N*/       // StarOffice registration
/*N*/       INetURLObject aORegObj( SvtPathOptions().GetUserConfigPath(), INET_PROT_FILE );
/*N*/       aORegObj.insertName( DEFINE_CONST_UNICODE( "oreg.ini" ) );
/*N*/         Config aCfg( aORegObj.PathToFileName() );
/*N*/         aCfg.SetGroup( "reg" );
/*N*/         sal_uInt16 nRegKey = (sal_uInt16) aCfg.ReadKey( "registration", "0" ).ToInt32();
/*N*/         if( nRegKey == 0 )
/*N*/             GetAppDispatcher_Impl()->Execute(SID_ONLINE_REGISTRATION_DLG, SFX_CALLMODE_ASYNCHRON);
/*N*/   }
/*N*/ #endif
/*N*/   return 0;
/*N*/ }

}
