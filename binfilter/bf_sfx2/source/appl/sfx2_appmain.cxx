/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_appmain.cxx,v $
 *
 *  $Revision: 1.11 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:24:27 $
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

//#define TF_NEWDESKTOP

#define _SDINTERN_HXX

#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef _URLOBJ_HXX //autogen
#include <tools/urlobj.hxx>
#endif
#ifndef _CSTITEM_HXX //autogen
#include <svtools/cstitem.hxx>
#endif
#ifndef _CONFIG_HXX
#include <tools/config.hxx>
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
#include "interno.hxx"
#include "fcontnr.hxx"
#include "cfgmgr.hxx"
#include "appuno.hxx"
#include "objuno.hxx"
#include "docfile.hxx"

#ifdef WNT
#include <tools/svwin.h>
#endif
namespace binfilter {

#ifdef UNX
#define stricmp(a,b) strcmp(a,b)
#endif


//===================================================================

/*DBG_NAME(SfxAppMainIntro)
DBG_NAME(SfxAppMainSO_Init)
DBG_NAME(SfxAppMainAppRes)
DBG_NAME(SfxAppMainInit0)
DBG_NAME(SfxAppMainCreateAppWin)
DBG_NAME(SfxAppMainInit1)
DBG_NAME(SfxAppMainCfgMgr)
DBG_NAME(SfxAppMainInitController)
DBG_NAME(SfxAppMainInitException)
DBG_NAME(SfxAppMainRegisterIF)
DBG_NAME(SfxAppMainInit)
DBG_NAME(SfxAppMainLoadBasMgr)
DBG_NAME(SfxAppMainSbxInit)*/
/*DBG_NAME(SfxAppMainInitDispatcher)
DBG_NAME(SfxAppMainLoadConfig)
DBG_NAME(SfxAppMainInitAppWin)
DBG_NAME(SfxAppMainAppEvents)*/

//===================================================================

#define SFX_TEMPNAMEBASE_DIR    "soffice.tmp"
#define SFX_KEY_TEMPNAMEBASE    "Temp-Dir"

//===================================================================

#ifdef _MSC_VER
#pragma code_seg("STATICS")
#endif
static SfxVoidItem aStaticDefault(1);
#ifdef _MSC_VER
#pragma code_seg()
#endif

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


void SfxApplication::Main( )
{
}

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

}
