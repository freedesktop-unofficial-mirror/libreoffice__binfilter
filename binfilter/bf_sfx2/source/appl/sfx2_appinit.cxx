/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_appinit.cxx,v $
 *
 *  $Revision: 1.11 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 10:35:11 $
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

#include "appimp.hxx"
#include "appdata.hxx"
#include "arrdecl.hxx"
#include "cfgmgr.hxx"
#include "docfac.hxx"
#include "evntconf.hxx"
#include "frameobj.hxx"
#include "interno.hxx"
#include "macrconf.hxx"
#include "plugobj.hxx"
#include "progress.hxx"
#include "sfxtypes.hxx"

#include <svtools/imgdef.hxx>

#include "eacopier.hxx"
#include "nochaos.hxx"
#include "fcontnr.hxx"
#include "helper.hxx"   // SfxContentHelper::Kill()

#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002

#ifndef _VOS_MUTEX_HXX_
#include <vos/mutex.hxx>
#endif

#include <cppuhelper/implbase1.hxx>

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
/*N*/ }

/*N*/ void SAL_CALL SfxTerminateListener_Impl::notifyTermination( const EventObject& aEvent ) throw(RuntimeException )
/*N*/ {
/*N*/     Reference< XDesktop > xDesktop( aEvent.Source, UNO_QUERY );
/*N*/     if( xDesktop.is() == sal_True )
/*N*/         xDesktop->removeTerminateListener( this );
/*N*/
/*N*/     ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/     SfxApplication* pApp = SFX_APP();
/*N*/     pApp->Broadcast( SfxSimpleHint( SFX_HINT_DEINITIALIZING ) );
/*N*/     pApp->NotifyEvent(SfxEventHint( SFX_EVENT_CLOSEAPP) );
/*N*/     pApp->Deinitialize();
/*N*/   Application::Quit();
/*N*/ }

//====================================================================

//====================================================================

/*N*/ FASTBOOL SfxApplication::Initialize_Impl()
/*N*/ {
/*N*/
/*N*/     Reference < XDesktop > xDesktop ( ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(
                                           ::rtl::OUString::createFromAscii("com.sun.star.frame.Desktop") ), UNO_QUERY );
/*N*/     xDesktop->addTerminateListener( new SfxTerminateListener_Impl() );
/*N*/
/*N*/     // StarObjects initialisieren
/*N*/   SvFactory::Init();
/*N*/
/*N*/   // Factory f"ur das SfxFrameObject anlegen; da der Pointer in den AppDaten
/*N*/   // liegt, dieser aber nicht exportierbar ist, mu\s ein exportierbarer
/*N*/   // Wrapper angelegt werden
/*N*/   pAppData_Impl->pSfxFrameObjectFactoryPtr = new SfxFrameObjectFactoryPtr;
/*N*/   pAppData_Impl->pSfxFrameObjectFactoryPtr->pSfxFrameObjectFactory = SfxFrameObject::ClassFactory();
/*N*/   SvBindStatusCallback::SetProgressCallback( STATIC_LINK( 0, SfxProgress, DefaultBindingProgress ) );
/*N*/
/*N*/   pImp->pEventHdl = new UniqueIndex( 1, 4, 4 );
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
/*N*/   /////////////////////////////////////////////////////////////////
/*N*/
/*N*/   pImp->pObjShells = new SfxObjectShellArr_Impl;
/*N*/
/*N*/ //    ::vos::OGuard aGuard( Application::GetSolarMutex() );
/*N*/
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_STARTAPP,        String(),   String::CreateFromAscii("OnStartApp") );
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_CLOSEAPP,        String(),   String::CreateFromAscii("OnCloseApp") );
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_CREATEDOC,       String(),   String::CreateFromAscii("OnNew") );
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_OPENDOC,         String(),   String::CreateFromAscii("OnLoad") );
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_SAVEASDOC,       String(),   String::CreateFromAscii("OnSaveAs") );
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_SAVEASDOCDONE,   String(),   String::CreateFromAscii("OnSaveAsDone") );
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_SAVEDOC,         String(),   String::CreateFromAscii("OnSave") );
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_SAVEDOCDONE,     String(),   String::CreateFromAscii("OnSaveDone") );
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_PREPARECLOSEDOC, String(),   String::CreateFromAscii("OnPrepareUnload") );
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_CLOSEDOC,        String(),   String::CreateFromAscii("OnUnload") );
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_ACTIVATEDOC,     String(),   String::CreateFromAscii("OnFocus") );
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_DEACTIVATEDOC,   String(),   String::CreateFromAscii("OnUnfocus") );
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_PRINTDOC,        String(),   String::CreateFromAscii("OnPrint") );
/*N*/   SfxEventConfiguration::RegisterEvent(SFX_EVENT_MODIFYCHANGED,   String(),   String::CreateFromAscii("OnModifyChanged") );
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
/*N*/   bInInit = sal_False;
/*N*/   if ( bDowning )
/*N*/       return sal_False;
/*N*/
/*N*/     return sal_True;
/*N*/ }
}
