/*************************************************************************
 *
 *  $RCSfile: sfx2_appmain.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2003-11-11 15:30:15 $
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

//#define TF_NEWDESKTOP

#define _SDINTERN_HXX

#pragma hdrstop

#ifndef _PVER_HXX //autogen
#include <svtools/pver.hxx>
#endif
#ifndef _URLOBJ_HXX //autogen
#include <tools/urlobj.hxx>
#endif
#if SUPD<613//MUSTINI
#ifndef _SFXINIMGR_HXX //autogen
#include <svtools/iniman.hxx>
#endif
#endif
#ifndef _CSTITEM_HXX //autogen
#include <svtools/cstitem.hxx>
#endif
#ifndef _SV_CONFIG_HXX //autogen
#include <vcl/config.hxx>
#endif
#ifndef _EHDL_HXX
#include <svtools/ehdl.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_STARTOPTIONS_HXX
#include <svtools/startoptions.hxx>
#endif
#include <svtools/itempool.hxx>
#include <svtools/urihelper.hxx>
#include <svtools/helpopt.hxx>
#include <vos/process.hxx>

#include "appimp.hxx"
#include "sfxtypes.hxx"
#include "appdata.hxx"
#include "docfac.hxx"
#include "app.hxx"
#include "arrdecl.hxx"
#include "dispatch.hxx"
#include "sfxresid.hxx"
#include "interno.hxx"
#include "fcontnr.hxx"
#include "viewsh.hxx"
#include "intro.hxx"
#include "msgpool.hxx"
#include "cfgmgr.hxx"
#include "accmgr.hxx"
#include "mnumgr.hxx"
#include "stbmgr.hxx"
#include "imgmgr.hxx"
#include "appuno.hxx"
#include "objuno.hxx"
#include "app.hrc"
#include "docfile.hxx"
#if SUPD<613//MUSTINI
#include "inimgr.hxx"
#endif

#ifdef WNT
#include <tools/svwin.h>
#endif
namespace binfilter {

#ifdef UNX
#define stricmp(a,b) strcmp(a,b)
#endif


//===================================================================

/*DBG_NAME(SfxAppMainIntro);
DBG_NAME(SfxAppMainSO_Init);
DBG_NAME(SfxAppMainAppRes);
DBG_NAME(SfxAppMainInit0);
DBG_NAME(SfxAppMainCreateAppWin);
DBG_NAME(SfxAppMainInit1);
DBG_NAME(SfxAppMainCfgMgr);
DBG_NAME(SfxAppMainInitController);
DBG_NAME(SfxAppMainInitException);
DBG_NAME(SfxAppMainRegisterIF);
DBG_NAME(SfxAppMainInit);
DBG_NAME(SfxAppMainLoadBasMgr);
DBG_NAME(SfxAppMainSbxInit);*/
//STRIP001 DBG_NAME(SfxAppMainNewMenu);
//STRIP001 DBG_NAME(SfxAppMainBmkMenu);
//STRIP001 DBG_NAME(SfxAppMainWizMenu);
//STRIP001 DBG_NAME(SfxAppMainOLEReg);
//STRIP001 DBG_NAME(SfxAppMainCHAOSReg);
/*DBG_NAME(SfxAppMainInitDispatcher);
DBG_NAME(SfxAppMainLoadConfig);
DBG_NAME(SfxAppMainInitAppWin);
DBG_NAME(SfxAppMainAppEvents);*/

//===================================================================

#define SFX_TEMPNAMEBASE_DIR    "soffice.tmp"
#define SFX_KEY_TEMPNAMEBASE    "Temp-Dir"

//===================================================================

#pragma code_seg("STATICS")
static SfxVoidItem aStaticDefault(1);
#pragma code_seg()

static SfxPoolItem* aStaticDefaults[1] =
{
    &aStaticDefault
};

#ifdef TF_POOLABLE
static SfxItemInfo __READONLY_DATA aItemInfos[] =
{
    { 0, 0 }
};
#endif

//===================================================================

typedef Link* LinkPtr;
SV_DECL_PTRARR(SfxInitLinkList, LinkPtr, 4, 4)//STRIP008 ;

/*N*/ TYPEINIT1(SfxSysChangeHint, SfxHint);
/*N*/ TYPEINIT2(SfxApplication,SfxShell,SfxBroadcaster);

//--------------------------------------------------------------------

//STRIP001 BOOL SfxApplication::HasFeature( ULONG nFeature ) const
//STRIP001
//STRIP001 /**  [Description]
//STRIP001
//STRIP001  Determines if 'nFeature' is supported by this running application.
//STRIP001  If more than one feature is given (by arithmetic 'or') and at least
//STRIP001  one of them is supported, it will return TRUE.
//STRIP001
//STRIP001  The supported features are set in the ctor of SfxApplication.
//STRIP001 */
//STRIP001
//STRIP001 {
//STRIP001  return 0 != ( nFeature & _nFeatures );
//STRIP001 }

//--------------------------------------------------------------------
/*N*/ void SfxApplication::Init
/*N*/ (
/*N*/ )
/*N*/
/*  [Beschreibung]

    Diese virtuelle Methode wird vom SFx aus Application:a:Main() gerufen,
    bevor Execute() ausgef"uhrt wird und
    - das Intro bereits angezeigt ist,
    - das Applikationsfenster exisitiert, aber noch hidden ist,
    - die Bindings bereits existieren (Controller sind anmeldbar),
    - der Ini- und Config-Manager bereits existiert,
    - die Standard-Controller bereits exisitieren,
    - die SFx-Shells ihre Interfaces bereits registriert haben.

    [Querverweise]
    <SfxApplication::Exit()>
    <SfxApplication::OpenClients()>
*/
/*N*/ {
/*N*/ #ifdef DDE_AVAILABLE
/*N*/ #ifdef PRODUCT
/*N*/     InitializeDde();
/*N*/ #else
/*N*/     if( !InitializeDde() )
/*N*/     {
/*N*/         ByteString aStr( "Kein DDE-Service moeglich. Fehler: " );
/*N*/         if( GetDdeService() )
/*N*/             aStr += GetDdeService()->GetError();
/*N*/         else
/*N*/             aStr += '?';
/*N*/         DBG_ASSERT( sal_False, aStr.GetBuffer() )
/*N*/     }
/*N*/ #endif
/*N*/ #endif
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxApplication::Exit()
/*N*/
/*  [Beschreibung]

    Diese virtuelle Methode wird vom SFx aus Application::Main() gerufen,
    nachdem Execute() beendet ist und
    - die Konfiguration (SfxConfigManager) bereits gespeichert wurde,
    - die Fensterpostionen etc. in den SfxIniManager geschrieben wurden,
    - das Applikationsfenster noch existiert, aber hidden ist
    - s"amtliche Dokumente und deren Views bereits geschlossen sind.
    - Dispatcher, Bindings etc. bereits zerst"ort sind

    [Querverweise]
    <SfxApplication::Init(int,char*[])>
*/
/*N*/
/*N*/ {
/*N*/ }

//---------------------------------------------------------------------------

/*N*/ void SfxApplication::PreInit( )
/*N*/ {
/*N*/ }

/*N*/ USHORT SfxApplication::ParseCommandLine_Impl()
/*N*/ {
/*N*/     USHORT nEvents = 0;                 // return value ( event mask )
/*N*/
/*N*/     BOOL   bPrintEvent = FALSE;
/*N*/     BOOL   bOpenEvent  = TRUE;
/*N*/
/*N*/     ::vos::OExtCommandLine aCmdLine;
/*N*/     USHORT nCount = aCmdLine.getCommandArgCount();
/*N*/     for( USHORT i=0; i < nCount; i++ )
/*N*/   {
/*N*/         String aArg;
/*N*/         ::rtl::OUString aDummy;
/*N*/         aCmdLine.getCommandArg( i, aDummy );
/*N*/         aArg = aDummy;
/*N*/
/*N*/         if ( aArg.EqualsIgnoreCaseAscii("-minimized") == sal_True )
/*?*/           pAppData_Impl->bMinimized = TRUE;
/*N*/         else if ( aArg.EqualsIgnoreCaseAscii("-invisible") == sal_True )
/*N*/           pAppData_Impl->bInvisible = TRUE;
/*N*/         else if ( aArg.EqualsIgnoreCaseAscii("-embedding") == sal_True )
/*?*/           pAppData_Impl->nAppEvent |= DISPATCH_SERVER;
/*?*/         else if ( aArg.EqualsIgnoreCaseAscii("-bean") == sal_True )
/*?*/       {
/*?*/           pAppData_Impl->bBean = TRUE;
/*?*/           pAppData_Impl->bInvisible = TRUE;
/*?*/       }
/*?*/         else if ( aArg.EqualsIgnoreCaseAscii("-plugin") == sal_True )
/*?*/       {
/*?*/           pAppData_Impl->bBean = TRUE;
/*?*/           pAppData_Impl->bInvisible = TRUE;
/*?*/             pAppData_Impl->bPlugged = TRUE;
/*?*/       }
/*?*/       else if ( aArg.EqualsIgnoreCaseAscii("-server") )
/*?*/           pAppData_Impl->bServer = true;
/*?*/       else if ( aArg.CompareIgnoreCaseToAscii("-portal,",
/*?*/                                               RTL_CONSTASCII_LENGTH(
/*?*/                                                   "-portal,"))
/*?*/                     == COMPARE_EQUAL )
/*?*/           pAppData_Impl->aPortalConnect
/*?*/               = aArg.Copy(RTL_CONSTASCII_LENGTH("-portal,"));
/*N*/
/*N*/       const xub_Unicode* pArg = aArg.GetBuffer();
/*N*/       // Erstmal nur mit -, da unter Unix Dateinmane auch mit Slasch anfangen koennen
/*N*/       if ( (*pArg == '-') /* || (*pArg == '/') */ )
/*N*/       {
/*N*/           pArg++;
/*N*/
/*N*/           // Ein Schalter
/*N*/           if ( (*pArg == 'p') || (*pArg == 'P') )
/*N*/           {
/*?*/               bPrintEvent = TRUE;
/*?*/               bOpenEvent = FALSE;    // Ab hier keine OpenEvents mehr
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           // Dies wird als Dateiname interpretiert
/*?*/           if ( bOpenEvent )
/*?*/           {
/*?*/               // Open Event anhaengen
/*?*/                 if ( pAppData_Impl->aOpenList.Len() )
/*?*/                     pAppData_Impl->aOpenList += APPEVENT_PARAM_DELIMITER;
/*?*/                 pAppData_Impl->aOpenList += aArg;
/*?*/           }
/*?*/           else if ( bPrintEvent )
/*?*/           {
/*?*/               // Print Event anhaengen
/*?*/                 if( pAppData_Impl->aPrintList.Len() )
/*?*/                     pAppData_Impl->aPrintList += APPEVENT_PARAM_DELIMITER;
/*?*/                 pAppData_Impl->aPrintList += aArg;
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/     if ( pAppData_Impl->aOpenList.Len() )
/*?*/       nEvents |= DISPATCH_OPEN;
/*N*/
/*N*/     if ( pAppData_Impl->aPrintList.Len() )
/*?*/       nEvents |= DISPATCH_PRINT;
/*N*/
/*N*/   return nEvents;
/*N*/ }

//---------------------------------------------------------------------------
/*N*/ void SfxApplication::InitLabelResMgr( const char* pLabelPrefix )
/*N*/ {
/*N*/   // Label-DLL mit diversen Resourcen fuer OEM-Ver. etc. (Intro, Titel, About)
/*N*/   pAppData_Impl->bBean = FALSE;
/*N*/     pAppData_Impl->nAppEvent = ParseCommandLine_Impl();
/*N*/     if ( pLabelPrefix )
/*N*/     {
/*N*/       // versuchen, die Label-DLL zu erzeugen
/*N*/       pAppData_Impl->pLabelResMgr = CreateResManager( pLabelPrefix );
/*N*/
/*N*/       // keine separate Label-DLL vorhanden?
/*N*/       if ( !pAppData_Impl->pLabelResMgr )
/*N*/           // dann den ResMgr vom Executable verwenden
/*?*/           pAppData_Impl->pLabelResMgr = new ResMgr;
/*N*/   }
/*N*/     else
/*N*/     {
/*?*/         pAppData_Impl->bBean = TRUE;
/*?*/         pAppData_Impl->bInvisible = TRUE;
/*N*/     }
/*N*/
/*N*/     // merken, falls Applikation normal gestartet wurde
//STRIP007     if ( 0 == pAppData_Impl->nAppEvent || DISPATCH_OPEN == pAppData_Impl->nAppEvent )
//STRIP007         pAppData_Impl->bDirectAliveCount = TRUE;
/*N*/ }

void SfxApplication::Main( )
{
}

//--------------------------------------------------------------------
#if defined( MAC )
    void InstallAppleScriptHdl();
#endif

//-------------------------------------------------------------------------
/*N*/ void SfxApplication::InsertLateInitHdl(const Link& rLink)
/*N*/ {
/*N*/   if ( Application::IsInExecute() )
/*?*/       Application::PostUserEvent( rLink );
/*N*/   else
/*N*/   {
/*N*/       if ( !pAppData_Impl->pInitLinkList )
/*N*/           pAppData_Impl->pInitLinkList = new SfxInitLinkList;
/*N*/
/*N*/       Link *pLink = new Link;
/*N*/       *pLink = rLink;
/*N*/       USHORT nCount = ( USHORT ) pAppData_Impl->pInitLinkList->Count();
/*N*/       pAppData_Impl->pInitLinkList->Insert(pLink, nCount);
/*N*/   }
/*N*/ }

/*N*/ void SfxApplication::ForcePendingInitFactories()
/*N*/ {
/*N*/   List& rList = Get_Impl()->aPendingInitFactories;
/*N*/   USHORT nPos = (USHORT) rList.Count();
/*N*/ #if LATEINIT
/*N*/   DBG_ASSERT( !nPos, "Filter nicht im LateInit" );
/*N*/ #endif
/*N*/   while( nPos = rList.Count() )
/*N*/   {
/*N*/       SfxObjectFactory* pFac = (SfxObjectFactory*)rList.Remove( --nPos );
/*N*/       pFac->DoInitFactory();
/*N*/   }
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ IMPL_LINK( SfxApplication, LateInitTimerHdl_Impl, void*, pvoid)
/*N*/ {
/*N*/     if ( !SfxViewFrame::GetFirst( 0,0,FALSE ) )
/*N*/     {
/*N*/         pAppData_Impl->aLateInitTimer.Start();
/*N*/         return 0;
/*N*/     }
/*N*/
/*N*/   // Ersten Link aus der Liste holen und ausf"uhren
/*N*/   Link *pLink = (*pAppData_Impl->pInitLinkList)[0];
/*N*/   pLink->Call(0);
/*N*/
/*N*/   // Link entfernen
/*N*/   pAppData_Impl->pInitLinkList->Remove(0);
/*N*/   delete pLink;
/*N*/
/*N*/   // Timer wieder starten, wenn noch weitere Links da sind
/*N*/   if ( pAppData_Impl->pInitLinkList->Count() )
/*N*/       pAppData_Impl->aLateInitTimer.Start();
/*N*/   else
/*N*/   {
/*N*/       // LateInit ist fertig
/*N*/       DELETEZ (pAppData_Impl->pInitLinkList);
/*N*/ #if SUPD<613//MUSTINI
/*N*/       pAppIniMgr->ResetLock();
/*N*/ #endif
/*N*/   }
/*N*/   return 0;
/*N*/ }

//-------------------------------------------------------------------------

//-------------------------------------------------------------------------

/*N*/ SfxFilterMatcher& SfxApplication::GetFilterMatcher()
/*N*/ {
/*N*/   if( !pAppData_Impl->pMatcher )
/*N*/   {
/*N*/       pAppData_Impl->pMatcher = new SfxFilterMatcher( TRUE );
/*N*/         URIHelper::SetMaybeFileHdl( STATIC_LINK(
/*N*/           pAppData_Impl->pMatcher, SfxFilterMatcher, MaybeFileHdl_Impl ) );
/*N*/   }
/*N*/   return *pAppData_Impl->pMatcher;
/*N*/ }

//-------------------------------------------------------------------------

//STRIP001 BOOL SfxApplication::IsStandalone() const
//STRIP001 {
//STRIP001 #if SUPD<613//MUSTINI
//STRIP001  // Wenn ohne UI gestartet, nat"urlich niemals integrierter Desktop
//STRIP001  if ( pAppData_Impl->bBean )
//STRIP001      return TRUE;
//STRIP001
//STRIP001  String aExt = SFX_INIMANAGER()->Get( String::CreateFromAscii( "Common"), 0, 0, String::CreateFromAscii("FullScreenDesktop") );
//STRIP001  if ( aExt.Len() )
//STRIP001  {
//STRIP001      // INI-Eintrag auswerten
//STRIP001      return !( (BOOL) (USHORT) aExt.ToInt32() );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // Defaults: bei AppServer kein integrierter Desktop, bei FatOffice
//STRIP001      // unter WNT integriert, ansonsten nicht
//STRIP001      if ( Application::IsRemoteServer() )
//STRIP001          return TRUE;
//STRIP001 #ifdef WNT
//STRIP001      return FALSE;
//STRIP001 #else
//STRIP001      return TRUE;
//STRIP001 #endif
//STRIP001  }
//STRIP001 #else//MUSTINI
//STRIP001  return FALSE;
//STRIP001 #endif
//STRIP001 }
}
