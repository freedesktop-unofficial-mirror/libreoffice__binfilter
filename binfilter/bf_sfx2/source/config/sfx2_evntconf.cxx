/*************************************************************************
 *
 *  $RCSfile: sfx2_evntconf.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 14:36:01 $
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

#ifndef _SV_MSGBOX_HXX //autogen
#include <vcl/msgbox.hxx>
#endif
// auto strip #ifndef _SV_RESARY_HXX
// auto strip #include <tools/resary.hxx>
// auto strip #endif
// auto strip #ifndef _SFXLSTNER_HXX //autogen
// auto strip #include <svtools/lstner.hxx>
// auto strip #endif
// auto strip #ifndef _SVSTOR_HXX //autogen
// auto strip #include <so3/svstor.hxx>
// auto strip #endif
// auto strip #ifndef _BASMGR_HXX //autogen
// auto strip #include <basic/basmgr.hxx>
// auto strip #endif
// auto strip #ifndef _SB_SBMOD_HXX //autogen
// auto strip #include <basic/sbmod.hxx>
// auto strip #endif
// auto strip #ifndef _URLOBJ_HXX //autogen
// auto strip #include <tools/urlobj.hxx>
// auto strip #endif
// auto strip #ifndef _SBXCLASS_HXX //autogen
// auto strip #include <svtools/sbx.hxx>
// auto strip #endif

// auto strip #include <svtools/securityoptions.hxx>

#pragma hdrstop

#ifndef _RTL_USTRING_
#include <rtl/ustring.h>
#endif

// auto strip #include <com/sun/star/uno/Any.hxx>
// auto strip #include <framework/eventsconfiguration.hxx>
// auto strip #include <comphelper/processfactory.hxx>

// auto strip #include "evntconf.hxx"

#include "macrconf.hxx"
// auto strip #include "docfile.hxx"
// auto strip #include "app.hxx"
#include "objsh.hxx"
#include "dispatch.hxx"
#include "config.hrc"
#include "sfxresid.hxx"
// auto strip #include "cfgmgr.hxx"
// auto strip #include "macropg.hxx"
// auto strip #include "docinf.hxx"
#include "eventsupplier.hxx"

#include "sfxsids.hrc"
#include "sfxlocal.hrc"

// auto strip #ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
// auto strip #include <com/sun/star/beans/PropertyValue.hpp>
// auto strip #endif
// auto strip #ifndef  _COM_SUN_STAR_CONTAINER_XNAMEREPLACE_HPP_
// auto strip #include <com/sun/star/container/XNameReplace.hpp>
// auto strip #endif
// auto strip #ifndef  _COM_SUN_STAR_DOCUMENT_XEVENTSSUPPLIER_HPP_
// auto strip #include <com/sun/star/document/XEventsSupplier.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
// auto strip #include <com/sun/star/uno/Sequence.hxx>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_UNO_REFERENCE_HXX_
// auto strip #include <com/sun/star/uno/Reference.hxx>
// auto strip #endif

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {

// -----------------------------------------------------------------------

#define PROPERTYVALUE           ::com::sun::star::beans::PropertyValue
#define XNAMEREPLACE            ::com::sun::star::container::XNameReplace
#define XEVENTSSUPPLIER         ::com::sun::star::document::XEventsSupplier
#define ANY                     ::com::sun::star::uno::Any
#define REFERENCE               ::com::sun::star::uno::Reference
#define SEQUENCE                ::com::sun::star::uno::Sequence
#define UNO_QUERY               ::com::sun::star::uno::UNO_QUERY

#define OUSTRING                ::rtl::OUString

// -----------------------------------------------------------------------

static const USHORT nCompatVersion = 3;
static const USHORT nOldVersion = 4;
static const USHORT nVersion = 5;

/*N*/ TYPEINIT1(SfxEventHint, SfxHint);

// class SfxMacroQueryDlg_Impl -------------------------------------------

class SfxMacroQueryDlg_Impl : public QueryBox
{
public:
                            SfxMacroQueryDlg_Impl( const String& rMacro, BOOL bDefault );
};

// class SfxMacroQueryDlg_Impl -------------------------------------------

/*?*/ SfxMacroQueryDlg_Impl::SfxMacroQueryDlg_Impl( const String& rMacName, BOOL bDefault ) :
/*?*/     QueryBox( NULL, SfxResId( DLG_MACROQUERY ) )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     SetButtonText( GetButtonId(0), String( SfxResId(BTN_OK) ) );
//STRIP001     SetButtonText( GetButtonId(1), String( SfxResId(BTN_CANCEL) ) );
//STRIP001
//STRIP001     String aText = GetMessText();
//STRIP001     aText.SearchAndReplace( String::CreateFromAscii("$(MACRO)"), rMacName );
//STRIP001
//STRIP001     if ( bDefault )
//STRIP001     {
//STRIP001         SetFocusButton(GetButtonId(0));
//STRIP001         aText.SearchAndReplace( String::CreateFromAscii("$(TEXT)"), String( SfxResId(FT_OK) ) );
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         SetFocusButton(GetButtonId(1));
//STRIP001         aText.SearchAndReplace( String::CreateFromAscii("$(TEXT)"), String( SfxResId(FT_CANCEL) ) );
//STRIP001     }
//STRIP001
//STRIP001     SetMessText( aText );
//STRIP001     FreeResource();
/*?*/ }

// class SfxAsyncEvent_Impl ----------------------------------------------

/*?*/ class SfxAsyncEvent_Impl : public SfxListener
/*?*/ {
/*?*/     String          aArgs;
/*?*/     SfxObjectShell* pSh;
/*?*/     const SvxMacro* pMacro;
/*?*/     Timer *pTimer;
/*?*/
/*?*/ public:
/*?*/
/*?*/     virtual void        Notify( SfxBroadcaster& rBC, const SfxHint& rHint );
/*?*/     SfxAsyncEvent_Impl( SfxObjectShell *pDoc, const SvxMacro *pMacro, const String& rArgs );
/*?*/     ~SfxAsyncEvent_Impl();
/*?*/     DECL_LINK( TimerHdl, Timer*);
/*?*/ };

// -----------------------------------------------------------------------

/*?*/ void SfxAsyncEvent_Impl::Notify( SfxBroadcaster& rBC, const SfxHint& rHint )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     SfxSimpleHint* pHint = PTR_CAST( SfxSimpleHint, &rHint );
//STRIP001     if( pHint && pHint->GetId() == SFX_HINT_DYING && pTimer->IsActive() )
//STRIP001     {
//STRIP001         pTimer->Stop();
//STRIP001         delete this;
//STRIP001     }
/*?*/ }

// -----------------------------------------------------------------------

/*?*/ SfxAsyncEvent_Impl::SfxAsyncEvent_Impl( SfxObjectShell *pDoc, const SvxMacro *pMac, const String& rArgs )
/*?*/  : aArgs( rArgs )
/*?*/  , pSh( pDoc )
/*?*/  , pMacro( pMac )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     if( pSh ) StartListening( *pSh );
//STRIP001     pTimer = new Timer;
//STRIP001     pTimer->SetTimeoutHdl( LINK(this, SfxAsyncEvent_Impl, TimerHdl) );
//STRIP001     pTimer->SetTimeout( 0 );
//STRIP001     pTimer->Start();
/*?*/ }

// -----------------------------------------------------------------------

/*?*/ SfxAsyncEvent_Impl::~SfxAsyncEvent_Impl()
/*?*/ {
/*?*/     delete pTimer;
/*?*/ }

// -----------------------------------------------------------------------

/*?*/ IMPL_LINK(SfxAsyncEvent_Impl, TimerHdl, Timer*, pTimer)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     pTimer->Stop();
//STRIP001     ScriptType eSType = pMacro->GetScriptType();
//STRIP001     BOOL bIsBasic = ( eSType == STARBASIC );
//STRIP001     if ( bIsBasic && StarBASIC::IsRunning() )
//STRIP001         // Neues eventgebundenes Macro erst ausf"uhren, wenn gerade kein anderes Macro mehr l"auft
//STRIP001         pTimer->Start();
//STRIP001     else
//STRIP001     {
//STRIP001         SFX_APP()->GetMacroConfig()->ExecuteMacro( pSh, pMacro, aArgs );
//STRIP001         delete this;
//STRIP001     }
//STRIP001
/*?*/     return 0L;
/*?*/ }

// class SfxEventList_Impl -----------------------------------------------

/*N*/ struct EventNames_Impl
/*N*/ {
/*N*/     USHORT  mnId;
/*N*/     String  maEventName;
/*N*/     String  maUIName;
/*N*/
/*N*/             EventNames_Impl( USHORT nId,
/*N*/                              const String& rEventName,
/*N*/                              const String& rUIName )
/*N*/                 : mnId( nId )
/*N*/                 , maEventName( rEventName )
/*N*/                 , maUIName( rUIName ) {}
/*N*/ };

/*?*/ DECLARE_LIST( SfxEventList_Impl, EventNames_Impl* )//STRIP008 ;
/*?*/
/*?*/ SfxEventList_Impl   *gp_Id_SortList = NULL;
/*?*/ SfxEventList_Impl   *gp_Name_SortList = NULL;

//==========================================================================

/*N*/ SfxEventConfiguration::SfxEventConfiguration()
/*N*/  : pDocEventConfig( NULL )
/*N*/  , pAppEventConfig( NULL )
/*N*/ {
/*N*/     bIgnoreConfigure = sal_False;
/*N*/
/*N*/     // Array zum Ermitteln der Bindungen
/*N*/     pEventArr = new SfxEventArr_Impl;
/*N*/
/*N*/     // Einen default entry eingf"ugen
/*N*/     const SfxEvent_Impl *pEvent = new SfxEvent_Impl(String(), 0);
/*N*/     pEventArr->Insert(pEvent, 0);
/*N*/ }

/*N*/ SfxEventConfigItem_Impl* SfxEventConfiguration::GetAppEventConfig_Impl()
/*N*/ {
/*N*/   if ( !pAppEventConfig )
/*N*/   {
/*N*/       pAppEventConfig = new SfxEventConfigItem_Impl( SFX_ITEMTYPE_APPEVENTCONFIG, this );
/*N*/       pAppEventConfig->Initialize();
/*N*/   }
/*N*/
/*N*/   return pAppEventConfig;
/*N*/ }

//==========================================================================

/*N*/ SfxEventConfiguration::~SfxEventConfiguration()
/*N*/ {
/*N*/     for (USHORT n=0; n<pEventArr->Count(); n++)
/*N*/         delete (*pEventArr)[n];
/*N*/     delete pEventArr;
/*N*/     delete pAppEventConfig;
/*N*/
/*N*/     if ( gp_Id_SortList )
/*N*/     {
/*N*/         EventNames_Impl* pData = gp_Id_SortList->First();
/*N*/         while ( pData )
/*N*/         {
/*N*/             delete pData;
/*N*/             pData = gp_Id_SortList->Next();
/*N*/         }
/*N*/         delete gp_Id_SortList;
/*N*/         delete gp_Name_SortList;
/*N*/
/*N*/         gp_Id_SortList = NULL;
/*N*/         gp_Name_SortList = NULL;
/*N*/     }
/*N*/ }

//==========================================================================

/*N*/ void SfxEventConfiguration::RegisterEvent(USHORT nId, const String& rName)
/*N*/ {
/*N*/     USHORT nCount = pEventArr->Count();
/*N*/     const SfxEvent_Impl *pEvent = new SfxEvent_Impl(rName, nId);
/*N*/     pEventArr->Insert(pEvent, nCount);
/*N*/ }

//==========================================================================

/*?*/ String SfxEventConfiguration::GetEventName(USHORT nId) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return String();//STRIP001
//STRIP001     DBG_ASSERT(pEventArr,"Keine Events angemeldet!");
//STRIP001     USHORT nCount = pEventArr->Count();
//STRIP001     for (USHORT n=1; n<nCount; n++)
//STRIP001     {
//STRIP001         if ((*pEventArr)[n]->nEventId == nId)
//STRIP001         {
//STRIP001             return (*pEventArr)[n]->aEventName;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     DBG_ERROR("Event nicht gefunden!");
//STRIP001     return (*pEventArr)[0]->aEventName;
/*?*/ }

//==========================================================================

/*?*/ USHORT SfxEventConfiguration::GetEventId(const String& rName) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     DBG_ASSERT(pEventArr,"Keine Events angemeldet!");
//STRIP001     USHORT nCount = pEventArr->Count();
//STRIP001     for (USHORT n=1; n<nCount; n++)
//STRIP001     {
//STRIP001         if ((*pEventArr)[n]->aEventName == rName)
//STRIP001         {
//STRIP001             return (*pEventArr)[n]->nEventId;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     DBG_ERROR("Event nicht gefunden!");
/*?*/     return SFX_NO_EVENT;
/*?*/ }

/*N*/ void SfxEventConfiguration::ConfigureEvent( USHORT nId, const SvxMacro& rMacro, SfxObjectShell *pDoc )
/*N*/ {
/*N*/     if ( bIgnoreConfigure )
/*N*/         return;
/*?*/
/*?*/     SvxMacro *pMacro = NULL;
/*?*/     if ( rMacro.GetMacName().Len() )
/*?*/         pMacro = new SvxMacro( rMacro.GetMacName(), rMacro.GetLibName(), rMacro.GetScriptType() );
/*?*/     if ( pDoc )
/*?*/     {
/*?*/         //pDocEventConfig = pDoc->GetEventConfig_Impl( TRUE );
/*?*/         //pDocEventConfig->ConfigureEvent( nId, pMacro );
/*?*/         PropagateEvent_Impl( pDoc, nId, pMacro );
/*?*/     }
/*?*/     else
/*?*/     {
/*?*/         // globale Bindung
/*?*/         //GetAppEventConfig_Impl()->ConfigureEvent( nId, pMacro );
/*?*/         PropagateEvent_Impl( NULL, nId, pMacro );
/*?*/     }
/*N*/ }

//==========================================================================

/*?*/ const SvxMacro* SfxEventConfiguration::GetMacroForEventId
/*?*/ (
/*?*/     USHORT          nId,
/*?*/     SfxObjectShell* pDoc
/*?*/ )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001     pDocEventConfig = pDoc ? pDoc->GetEventConfig_Impl() : NULL;
//STRIP001     const SvxMacro* pMacro=NULL;
//STRIP001     if ( pDocEventConfig )
//STRIP001         pMacro = pDocEventConfig->aMacroTable.Seek( nId );
//STRIP001     if ( !pMacro )
//STRIP001         pMacro = GetAppEventConfig_Impl()->aMacroTable.Seek( nId );
//STRIP001     return pMacro;
/*?*/ }

/*?*/ const SfxMacroInfo* SfxEventConfiguration::GetMacroInfo
/*?*/ (
/*?*/     USHORT          nId,
/*?*/     SfxObjectShell* pDoc
/*?*/ ) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001     DBG_ASSERT(pEventArr,"Keine Events angemeldet!");
//STRIP001
//STRIP001     SfxEventConfigItem_Impl *pDocEventConfig = pDoc ? pDoc->GetEventConfig_Impl() : NULL;
//STRIP001     const SvxMacro* pMacro=NULL;
//STRIP001     if ( pDocEventConfig )
//STRIP001         pMacro = pDocEventConfig->aMacroTable.Seek( nId );
//STRIP001     if ( !pMacro )
//STRIP001         pMacro = const_cast< SfxEventConfiguration* >(this)->GetAppEventConfig_Impl()->aMacroTable.Seek( nId );
//STRIP001
//STRIP001     return SFX_APP()->GetMacroConfig()->GetMacroInfo_Impl( pMacro );
/*?*/ }

//==========================================================================

/*N*/ SfxEventConfigItem_Impl::SfxEventConfigItem_Impl( USHORT nConfigId,
/*N*/     SfxEventConfiguration *pCfg,
/*N*/     SfxObjectShell *pObjSh)
/*N*/     : SfxConfigItem( nConfigId, pObjSh ? NULL : SFX_APP()->GetConfigManager_Impl() )
/*N*/     , aMacroTable( 2, 2 )
/*N*/     , pEvConfig( pCfg )
/*N*/     , pObjShell( pObjSh )
/*N*/   , bInitialized( FALSE )
/*N*/ {
/*N*/   bInitialized = TRUE;
/*N*/ }

/*
void SfxEventConfigItem_Impl::Init( SfxConfigManager *pMgr )
{
    if ( GetConfigManager() == pMgr )
        Initialize();
    else
        ReInitialize( pMgr );
}
*/

//==========================================================================

/*N*/ int SfxEventConfigItem_Impl::Load(SvStream& rStream)
/*N*/ {
/*N*/     USHORT nFileVersion;
/*N*/     rStream >> nFileVersion;
/*N*/     if ( nFileVersion < nCompatVersion || nFileVersion > nVersion )
/*?*/         return SfxConfigItem::WARNING_VERSION;
/*N*/
/*N*/     SvxMacroTableDtor aLocalMacroTable;
/*N*/     if ( nFileVersion <= nOldVersion )
/*N*/     {
/*?*/         if ( nFileVersion > nCompatVersion )
/*?*/         {
/*?*/             USHORT nWarn;
/*?*/             rStream >> nWarn;
/*?*/             bWarning = ( nWarn & 0x01 ) != 0;
/*?*/             bAlwaysWarning = ( nWarn & 0x02 ) != 0;
/*?*/         }
/*?*/         else
/*?*/             bWarning = bAlwaysWarning = FALSE;
/*?*/
/*?*/         USHORT nCount, nEventCount = pEvConfig->GetEventCount();
/*?*/         rStream >> nCount;
/*?*/
/*?*/         USHORT i;
/*?*/         for (i=0; i<nCount; i++)
/*?*/         {
/*?*/           USHORT nId;
/*?*/             SfxMacroInfo aInfo( pObjShell );
/*?*/             rStream >> nId >> aInfo;
/*?*/
/*?*/             for (USHORT n=0; n<nEventCount; n++)
/*?*/             {
/*?*/               USHORT nEventId = (*pEvConfig->pEventArr)[n+1]->nEventId;
/*?*/                 if ( nEventId == nId )
/*?*/                 {
/*?*/                   SvxMacro *pMacro = new SvxMacro( aInfo.GetQualifiedName(), aInfo.GetBasicName(), STARBASIC );
/*?*/                   aLocalMacroTable.Insert( nEventId, pMacro );
/*?*/                     break;
/*?*/                 }
/*?*/             }
/*?*/         }
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         USHORT nWarn;
/*N*/         rStream >> nWarn;
/*N*/         bWarning = ( nWarn & 0x01 ) != 0;
/*N*/         bAlwaysWarning = ( nWarn & 0x02 ) != 0;
/*N*/         aLocalMacroTable.Read( rStream );
/*N*/     }
/*N*/
/*N*/     if ( pObjShell && pEvConfig )
/*N*/         pEvConfig->PropagateEvents_Impl( pObjShell, aLocalMacroTable );
/*N*/
/*N*/     return SfxConfigItem::ERR_OK;
/*N*/ }

/*?*/ BOOL SfxEventConfigItem_Impl::LoadXML( SvStream& rInStream )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001     ::framework::EventsConfig aCfg;
//STRIP001     if ( ::framework::EventsConfiguration::LoadEventsConfig( rInStream, aCfg ) )
//STRIP001     {
//STRIP001         long nCount = aCfg.aEventNames.getLength();
//STRIP001         for ( long i=0; i<nCount; i++ )
//STRIP001         {
//STRIP001             SvxMacro* pMacro = SfxEvents_Impl::ConvertToMacro( aCfg.aEventsProperties[i], NULL, TRUE );
//STRIP001             USHORT nID = (USHORT) SfxEventConfiguration::GetEventId_Impl( aCfg.aEventNames[i] );
//STRIP001             if ( nID && pMacro )
//STRIP001                 pEvConfig->PropagateEvent_Impl( pObjShell, nID, pMacro );
//STRIP001          else
//STRIP001              DBG_ERROR("Suspicious event binding!");
//STRIP001         }
//STRIP001
//STRIP001      return TRUE;
//STRIP001     }
//STRIP001
//STRIP001     return FALSE;
/*?*/ }

//==========================================================================

/*?*/ BOOL SfxEventConfigItem_Impl::Store(SvStream& rStream)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001     USHORT nWarn=0;
//STRIP001     if ( bWarning )
//STRIP001         nWarn |= 0x01;
//STRIP001     if ( bAlwaysWarning )
//STRIP001         nWarn |= 0x02;
//STRIP001     rStream << nVersion << nWarn;
//STRIP001     aMacroTable.Write( rStream );
//STRIP001     return TRUE;
/*?*/ }

/*?*/ BOOL SfxEventConfigItem_Impl::StoreXML( SvStream& rOutStream )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001     // get the event names
//STRIP001     ResStringArray aEventNames( SfxResId( EVENT_NAMES_ARY ) );
//STRIP001     long nNamesCount = aEventNames.Count();
//STRIP001
//STRIP001     // create two sequences for names and properties
//STRIP001     SEQUENCE < OUSTRING > aSequence( nNamesCount );
//STRIP001     SEQUENCE < ANY > aData( nNamesCount );
//STRIP001
//STRIP001     // fill in the names
//STRIP001     OUSTRING* pNames = aSequence.getArray();
//STRIP001     long i;
//STRIP001     for ( i=0; i<nNamesCount; i++ )
//STRIP001         pNames[i] = aEventNames.GetString( (USHORT) i);
//STRIP001
//STRIP001     REFERENCE< XEVENTSSUPPLIER > xSupplier;
//STRIP001  if ( pObjShell )
//STRIP001  {
//STRIP001      xSupplier = REFERENCE< XEVENTSSUPPLIER >( pObjShell->GetModel(), UNO_QUERY );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      xSupplier = REFERENCE< XEVENTSSUPPLIER >
//STRIP001                 ( ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(
//STRIP001                         ::rtl::OUString::createFromAscii("com.sun.star.frame.GlobalEventBroadcaster" )), UNO_QUERY );
//STRIP001  }
//STRIP001
//STRIP001     // fill in the bindings
//STRIP001     REFERENCE< XNAMEREPLACE > xEvents = xSupplier->getEvents();
//STRIP001     SvxMacroTableDtor& rTable = aMacroTable;
//STRIP001     long nCount = (long) rTable.Count();
//STRIP001     for ( i=0; i<nCount; i++ )
//STRIP001     {
//STRIP001         USHORT nID = (USHORT) rTable.GetObjectKey( i );
//STRIP001         OUSTRING aEventName = pEvConfig->GetEventName_Impl( nID );
//STRIP001         if ( aEventName.getLength() )
//STRIP001         {
//STRIP001             // search name
//STRIP001             for ( long n=0; n<(long)nNamesCount; n++ )
//STRIP001             {
//STRIP001                 if ( aSequence[n] == aEventName )
//STRIP001                 {
//STRIP001                     aData[n] = xEvents->getByName( aEventName );
//STRIP001                     break;
//STRIP001                 }
//STRIP001             }
//STRIP001
//STRIP001          DBG_ASSERT( n<nNamesCount, "Unknown event!" );
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     ::framework::EventsConfig aCfg;
//STRIP001     aCfg.aEventNames = aSequence;
//STRIP001     aCfg.aEventsProperties = aData;
//STRIP001
//STRIP001     return ::framework::EventsConfiguration::StoreEventsConfig( rOutStream, aCfg );
/*?*/ }

//==========================================================================

/*?*/ String SfxEventConfigItem_Impl::GetStreamName() const
/*?*/ {
/*?*/     return SfxConfigItem::GetStreamName( GetType() );
/*?*/ }

//==========================================================================

/*N*/ void SfxEventConfigItem_Impl::UseDefault()
/*N*/ {
/*N*/     bWarning = TRUE;
/*N*/     bAlwaysWarning = FALSE;
/*N*/
/*N*/     aMacroTable.DelDtor();
/*N*/     SetDefault( TRUE );
/*N*/     pEvConfig->PropagateEvents_Impl( pObjShell, aMacroTable );
/*N*/ }

/*?*/ int SfxEventConfigItem_Impl::Load( SotStorage& rStorage )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001     SotStorageStreamRef xStream = rStorage.OpenSotStream( SfxEventConfigItem_Impl::GetStreamName(), STREAM_STD_READ );
//STRIP001     if ( xStream->GetError() )
//STRIP001         return SfxConfigItem::ERR_READ;
//STRIP001     else
//STRIP001  {
//STRIP001      if ( bInitialized )
//STRIP001      {
//STRIP001          aMacroTable.DelDtor();
//STRIP001          pEvConfig->PropagateEvents_Impl( pObjShell, aMacroTable );
//STRIP001      }
//STRIP001
//STRIP001         if ( LoadXML( *xStream ) )
//STRIP001          return SfxConfigItem::ERR_OK;
//STRIP001      else
//STRIP001          return SfxConfigItem::ERR_READ;
//STRIP001  }
/*?*/ }

/*?*/ BOOL SfxEventConfigItem_Impl::Store( SotStorage& rStorage )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  if ( pObjShell )
//STRIP001      // DocEventConfig is stored with the document
//STRIP001      return TRUE;
//STRIP001
//STRIP001     SotStorageStreamRef xStream = rStorage.OpenSotStream( SfxEventConfigItem_Impl::GetStreamName(), STREAM_STD_READWRITE|STREAM_TRUNC );
//STRIP001     if ( xStream->GetError() )
//STRIP001         return FALSE;
//STRIP001     else
//STRIP001         return StoreXML( *xStream );
/*?*/ }


//==========================================================================

/*N*/ SfxEventConfigItem_Impl::~SfxEventConfigItem_Impl()
/*N*/ {
/*N*/ }

//==========================================================================

/*N*/ void SfxEventConfigItem_Impl::ConfigureEvent( USHORT nId, SvxMacro *pMacro )
/*N*/ {
/*N*/     if ( aMacroTable.Seek( nId ) )
/*N*/     {
/*?*/         if ( pMacro )
/*?*/             aMacroTable.Replace( nId, pMacro );
/*?*/         else
/*?*/             aMacroTable.Remove( nId );
/*N*/     }
/*N*/     else if ( pMacro )
/*N*/         aMacroTable.Insert( nId, pMacro );
/*N*/     SetDefault(FALSE);
/*N*/ }

/*?*/ void SfxEventConfiguration::AddEvents( SfxMacroTabPage* pPage ) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     DBG_ASSERT(pEventArr,"Keine Events angemeldet!");
//STRIP001     USHORT nCount = pEventArr->Count();
//STRIP001     for (USHORT n=1; n<nCount; n++)
//STRIP001      if ( (*pEventArr)[n]->aEventName.Len() )
//STRIP001          pPage->AddEvent( (*pEventArr)[n]->aEventName, (*pEventArr)[n]->nEventId );
/*?*/ }

/*?*/ SvxMacroTableDtor* SfxEventConfiguration::GetAppEventTable()
/*?*/ {
/*?*/     return &GetAppEventConfig_Impl()->aMacroTable;
/*?*/ }

/*N*/ SvxMacroTableDtor* SfxEventConfiguration::GetDocEventTable( SfxObjectShell*pDoc )
/*N*/ {
/*N*/     pDocEventConfig = pDoc ? pDoc->GetEventConfig_Impl() : NULL;
/*N*/     if ( pDocEventConfig )
/*N*/         return &pDocEventConfig->aMacroTable;
/*?*/     return NULL;
/*N*/ }

/*?*/ void SfxEventConfiguration::SetAppEventTable( const SvxMacroTableDtor& rTable )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     //GetAppEventConfig_Impl()->aMacroTable = rTable;
//STRIP001     //pAppEventConfig->SetDefault(FALSE);
//STRIP001     PropagateEvents_Impl( NULL, rTable );
/*?*/ }

/*?*/ void SfxEventConfiguration::SetDocEventTable( SfxObjectShell *pDoc,
/*?*/     const SvxMacroTableDtor& rTable )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     if ( pDoc )
//STRIP001     {
//STRIP001      // if CfgMgr does not exist, create it, otherwise ConfigItem will not have a ConfigManager!
//STRIP001      pDoc->GetConfigManager(TRUE);
//STRIP001         pDocEventConfig = pDoc->GetEventConfig_Impl( TRUE );
//STRIP001         //pDocEventConfig->aMacroTable = rTable;
//STRIP001         //pDocEventConfig->SetDefault(FALSE);
//STRIP001         pDoc->SetModified(TRUE);
//STRIP001         PropagateEvents_Impl( pDoc, rTable );
//STRIP001     }
//STRIP001     else
//STRIP001         DBG_ERROR( "Kein Dokument!" );
/*?*/ }

//--------------------------------------------------------------------------
/*N*/ void SfxEventConfiguration::PropagateEvents_Impl( SfxObjectShell *pDoc,
/*N*/     const SvxMacroTableDtor& rTable )
/*N*/ {
/*N*/     REFERENCE< XEVENTSSUPPLIER > xSupplier;
/*N*/   if ( pDoc )
/*N*/   {
/*N*/       xSupplier = REFERENCE< XEVENTSSUPPLIER >( pDoc->GetModel(), UNO_QUERY );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       xSupplier = REFERENCE< XEVENTSSUPPLIER >
/*N*/                 ( ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(
/*N*/                         ::rtl::OUString::createFromAscii("com.sun.star.frame.GlobalEventBroadcaster" )), UNO_QUERY );
/*N*/   }
/*N*/
/*N*/     if ( xSupplier.is() )
/*N*/     {
/*N*/         SvxMacro   *pMacro;
/*N*/         ULONG       nCount;
/*N*/         ULONG       nID, i;
/*N*/
/*N*/         REFERENCE< XNAMEREPLACE > xEvents = xSupplier->getEvents();
/*N*/
/*N*/         bIgnoreConfigure = sal_True;
/*N*/
/*N*/         // Erase old values first, because we don't know anything about the
/*N*/         // changes here
/*N*/
/*N*/         SEQUENCE < PROPERTYVALUE > aProperties;
/*N*/         SEQUENCE < OUSTRING > aEventNames = xEvents->getElementNames();
/*N*/         OUSTRING*   pNames  = aEventNames.getArray();
/*N*/         ANY aEmpty;
/*N*/
/*N*/         aEmpty <<= aProperties;
/*N*/         nCount  = aEventNames.getLength();
/*N*/
/*N*/         for ( i=0; i<nCount; i++ )
/*N*/         {
/*N*/             try
/*N*/             {
/*N*/                 xEvents->replaceByName( pNames[i], aEmpty );
/*N*/             }
/*N*/             catch( ::com::sun::star::lang::IllegalArgumentException )
/*N*/             { DBG_ERRORFILE( "PropagateEvents_Impl: caught IllegalArgumentException" ) }
/*N*/             catch( ::com::sun::star::container::NoSuchElementException )
/*N*/             { DBG_ERRORFILE( "PropagateEvents_Impl: caught NoSuchElementException" ) }
/*N*/         }
/*N*/
/*N*/         // now set the new values
/*N*/
/*N*/         nCount = rTable.Count();
/*N*/
/*N*/         for ( i=0; i<nCount; i++ )
/*N*/         {
/*N*/             pMacro = rTable.GetObject( i );
/*N*/             nID = rTable.GetObjectKey( i );
/*N*/             OUSTRING aEventName = GetEventName_Impl( nID );
/*N*/
/*N*/             if ( aEventName.getLength() )
/*N*/             {
/*N*/                 ANY aEventData = CreateEventData_Impl( pMacro );
/*N*/                 try
/*N*/                 {
/*N*/                     xEvents->replaceByName( aEventName, aEventData );
/*N*/                 }
/*N*/                 catch( ::com::sun::star::lang::IllegalArgumentException )
/*N*/                 { DBG_ERRORFILE( "PropagateEvents_Impl: caught IllegalArgumentException" ) }
/*N*/                 catch( ::com::sun::star::container::NoSuchElementException )
/*N*/                 { DBG_ERRORFILE( "PropagateEvents_Impl: caught NoSuchElementException" ) }
/*N*/             }
/*N*/             else
/*N*/                 DBG_WARNING( "PropagateEvents_Impl: Got unkown event" );
/*N*/         }
/*N*/
/*N*/         bIgnoreConfigure = sal_False;
/*N*/     }
/*N*/ }

//--------------------------------------------------------------------------
/*?*/ void SfxEventConfiguration::PropagateEvent_Impl( SfxObjectShell *pDoc,
/*?*/                                                  USHORT nId,
/*?*/                                                  const SvxMacro* pMacro )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     REFERENCE< XEVENTSSUPPLIER > xSupplier;
//STRIP001  if ( pDoc )
//STRIP001  {
//STRIP001      xSupplier = REFERENCE< XEVENTSSUPPLIER >( pDoc->GetModel(), UNO_QUERY );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      xSupplier = REFERENCE< XEVENTSSUPPLIER >
//STRIP001                 ( ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(
//STRIP001                         ::rtl::OUString::createFromAscii("com.sun.star.frame.GlobalEventBroadcaster" )), UNO_QUERY );
//STRIP001  }
//STRIP001
//STRIP001     if ( xSupplier.is() )
//STRIP001     {
//STRIP001         REFERENCE< XNAMEREPLACE > xEvents = xSupplier->getEvents();
//STRIP001
//STRIP001         bIgnoreConfigure = sal_True;
//STRIP001
//STRIP001         OUSTRING aEventName = GetEventName_Impl( nId );
//STRIP001
//STRIP001         if ( aEventName.getLength() )
//STRIP001         {
//STRIP001             ANY aEventData = CreateEventData_Impl( pMacro );
//STRIP001
//STRIP001             try
//STRIP001             {
//STRIP001                 xEvents->replaceByName( aEventName, aEventData );
//STRIP001             }
//STRIP001             catch( ::com::sun::star::lang::IllegalArgumentException )
//STRIP001             { DBG_ERRORFILE( "PropagateEvents_Impl: caught IllegalArgumentException" ) }
//STRIP001             catch( ::com::sun::star::container::NoSuchElementException )
//STRIP001             { DBG_ERRORFILE( "PropagateEvents_Impl: caught NoSuchElementException" ) }
//STRIP001         }
//STRIP001         else
//STRIP001             DBG_WARNING( "PropagateEvents_Impl: Got unkown event" );
//STRIP001
//STRIP001         bIgnoreConfigure = sal_False;
//STRIP001     }
/*?*/ }

// -------------------------------------------------------------------------------------------------------
/*N*/ ANY SfxEventConfiguration::CreateEventData_Impl( const SvxMacro *pMacro )
/*N*/ {
/*
    This function converts a SvxMacro into an Any containing three
    properties. These properties are EventType and Script. Possible
    values for EventType ar StarBasic, JavaScript, ...
    The Script property should contain the URL to the macro and looks
    like "macro://./standard.module1.main()"

    If pMacro is NULL, we return an empty property sequence, so PropagateEvent_Impl
    can delete an event binding.
*/
/*N*/     ANY aEventData;
/*N*/
/*N*/     if ( pMacro )
/*N*/     {
/*N*/         if ( pMacro->GetScriptType() == STARBASIC )
/*N*/         {
/*N*/             SEQUENCE < PROPERTYVALUE > aProperties(3);
/*N*/             PROPERTYVALUE  *pValues = aProperties.getArray();
/*N*/
/*N*/             OUSTRING    aType   = OUSTRING::createFromAscii( STAR_BASIC );;
/*N*/             OUSTRING    aLib    = pMacro->GetLibName();
/*N*/             OUSTRING    aMacro  = pMacro->GetMacName();
/*N*/
/*N*/             pValues[ 0 ].Name = OUSTRING::createFromAscii( PROP_EVENT_TYPE );
/*N*/             pValues[ 0 ].Value <<= aType;
/*N*/
/*N*/             pValues[ 1 ].Name = OUSTRING::createFromAscii( PROP_LIBRARY );
/*N*/             pValues[ 1 ].Value <<= aLib;
/*N*/
/*N*/             pValues[ 2 ].Name = OUSTRING::createFromAscii( PROP_MACRO_NAME );
/*N*/             pValues[ 2 ].Value <<= aMacro;
/*N*/
/*N*/             aEventData <<= aProperties;
/*N*/         }
/*N*/         else if ( pMacro->GetScriptType() == EXTENDED_STYPE )
/*N*/         {
/*?*/             SEQUENCE < PROPERTYVALUE > aProperties(2);
/*?*/             PROPERTYVALUE  *pValues = aProperties.getArray();
/*?*/
/*?*/             OUSTRING    aLib    = pMacro->GetLibName();
/*?*/             OUSTRING    aMacro  = pMacro->GetMacName();
/*?*/
/*?*/             pValues[ 0 ].Name = OUSTRING::createFromAscii( PROP_EVENT_TYPE );
/*?*/             pValues[ 0 ].Value <<= aLib;
/*?*/
/*?*/             pValues[ 1 ].Name = OUSTRING::createFromAscii( PROP_SCRIPT );
/*?*/             pValues[ 1 ].Value <<= aMacro;
/*?*/
/*?*/             aEventData <<= aProperties;
/*N*/       }
/*N*/         else if ( pMacro->GetScriptType() == JAVASCRIPT )
/*N*/         {
/*?*/             SEQUENCE < PROPERTYVALUE > aProperties(2);
/*?*/             PROPERTYVALUE  *pValues = aProperties.getArray();
/*?*/
/*?*/             OUSTRING    aMacro  = pMacro->GetMacName();
/*?*/
/*?*/             pValues[ 0 ].Name = OUSTRING::createFromAscii( PROP_EVENT_TYPE );
/*?*/             pValues[ 0 ].Value <<= ::rtl::OUString::createFromAscii(SVX_MACRO_LANGUAGE_JAVASCRIPT);
/*?*/
/*?*/             pValues[ 1 ].Name = OUSTRING::createFromAscii( PROP_MACRO_NAME );
/*?*/             pValues[ 1 ].Value <<= aMacro;
/*?*/
/*?*/             aEventData <<= aProperties;
/*N*/       }
/*N*/         else
/*N*/         {
/*N*/             DBG_ERRORFILE( "CreateEventData_Impl(): ScriptType not supported!");
/*N*/         }
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         SEQUENCE < PROPERTYVALUE > aProperties;
/*N*/         aEventData <<= aProperties;
/*N*/     }
/*N*/
/*N*/     return aEventData;
/*N*/ }

// -------------------------------------------------------------------------------------------------------
/*N*/ ULONG SfxEventConfiguration::GetPos_Impl( USHORT nId, sal_Bool &rFound )
/*N*/ {
/*N*/     rFound = sal_False;
/*N*/
/*N*/     if ( ! gp_Id_SortList->Count() )
/*N*/         return 0;
/*N*/
/*N*/     // use binary search to find the correct position
/*N*/     // in the list
/*N*/
/*N*/     int     nCompVal = 1;
/*N*/     long    nStart = 0;
/*N*/     long    nEnd = gp_Id_SortList->Count() - 1;
/*N*/     long    nMid;
/*N*/
/*N*/     EventNames_Impl* pMid;
/*N*/
/*N*/     rFound = sal_False;
/*N*/
/*N*/     while ( nCompVal && ( nStart <= nEnd ) )
/*N*/     {
/*N*/         nMid = ( nEnd - nStart ) / 2 + nStart;
/*N*/         pMid = gp_Id_SortList->GetObject( (USHORT) nMid );
/*N*/
/*N*/         nCompVal = pMid->mnId - nId;
/*N*/
/*N*/         if ( nCompVal < 0 )     // pMid < pData
/*N*/             nStart = nMid + 1;
/*N*/         else
/*N*/             nEnd = nMid - 1;
/*N*/     }
/*N*/
/*N*/     if ( nCompVal == 0 )
/*N*/     {
/*N*/         rFound = sal_True;
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         if ( nCompVal < 0 )     // pMid < pData
/*N*/             nMid++;
/*N*/     }
/*N*/
/*N*/     return (USHORT) nMid;
/*N*/ }

// -------------------------------------------------------------------------------------------------------
/*N*/ ULONG SfxEventConfiguration::GetPos_Impl( const String& rName, sal_Bool &rFound )
/*N*/ {
/*N*/     rFound = sal_False;
/*N*/
/*N*/     if ( ! gp_Name_SortList->Count() )
/*N*/         return 0;
/*N*/
/*N*/     // use binary search to find the correct position
/*N*/     // in the list
/*N*/
/*N*/     int     nCompVal = 1;
/*N*/     long    nStart = 0;
/*N*/     long    nEnd = gp_Name_SortList->Count() - 1;
/*N*/     long    nMid;
/*N*/
/*N*/     EventNames_Impl* pMid;
/*N*/
/*N*/     rFound = sal_False;
/*N*/
/*N*/     while ( nCompVal && ( nStart <= nEnd ) )
/*N*/     {
/*N*/         nMid = ( nEnd - nStart ) / 2 + nStart;
/*N*/         pMid = gp_Name_SortList->GetObject( (USHORT) nMid );
/*N*/
/*N*/         nCompVal = rName.CompareTo( pMid->maEventName );
/*N*/
/*N*/         if ( nCompVal < 0 )     // pMid < pData
/*N*/             nStart = nMid + 1;
/*N*/         else
/*N*/             nEnd = nMid - 1;
/*N*/     }
/*N*/
/*N*/     if ( nCompVal == 0 )
/*N*/     {
/*N*/         rFound = sal_True;
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         if ( nCompVal < 0 )     // pMid < pData
/*N*/             nMid++;
/*N*/     }
/*N*/
/*N*/     return (USHORT) nMid;
/*N*/ }

//--------------------------------------------------------------------------------------------------------
/*N*/ OUSTRING SfxEventConfiguration::GetEventName_Impl( ULONG nID )
/*N*/ {
/*N*/     OUSTRING    aRet;
/*N*/
/*N*/     if ( gp_Id_SortList )
/*N*/     {
/*N*/         sal_Bool    bFound;
/*N*/         ULONG       nPos = GetPos_Impl( (USHORT) nID, bFound );
/*N*/
/*N*/         if ( bFound )
/*N*/         {
/*N*/             EventNames_Impl *pData = gp_Id_SortList->GetObject( nPos );
/*N*/             aRet = pData->maEventName;
/*N*/         }
/*N*/     }
/*N*/
/*N*/     return aRet;
/*N*/ }

//--------------------------------------------------------------------------------------------------------
/*N*/ ULONG SfxEventConfiguration::GetEventId_Impl( const OUSTRING& rEventName )
/*N*/ {
/*N*/     ULONG nRet = 0;
/*N*/
/*N*/     if ( gp_Name_SortList )
/*N*/     {
/*N*/         sal_Bool    bFound;
/*N*/         ULONG       nPos = GetPos_Impl( rEventName, bFound );
/*N*/
/*N*/         if ( bFound )
/*N*/         {
/*N*/             EventNames_Impl *pData = gp_Name_SortList->GetObject( nPos );
/*N*/             nRet = pData->mnId;
/*N*/         }
/*N*/     }
/*N*/
/*N*/     return nRet;
/*N*/ }

// -------------------------------------------------------------------------------------------------------
/*N*/ void SfxEventConfiguration::RegisterEvent( USHORT nId,
/*N*/                                            const String& rUIName,
/*N*/                                            const String& rMacroName )
/*N*/ {
/*N*/     if ( ! gp_Id_SortList )
/*N*/     {
/*N*/         gp_Id_SortList = new SfxEventList_Impl;
/*N*/         gp_Name_SortList = new SfxEventList_Impl;
/*N*/     }
/*N*/
/*N*/     sal_Bool    bFound = sal_False;
/*N*/     ULONG       nPos = GetPos_Impl( nId, bFound );
/*N*/
/*N*/     if ( bFound )
/*N*/     {
/*?*/         DBG_ERRORFILE( "RegisterEvent: Event already registered?" );
/*?*/         return;
/*N*/     }
/*N*/
/*N*/     EventNames_Impl *pData;
/*N*/
/*N*/     pData = new EventNames_Impl( nId, rMacroName, rUIName );
/*N*/     gp_Id_SortList->Insert( pData, nPos );
/*N*/
/*N*/     nPos = GetPos_Impl( rMacroName, bFound );
/*N*/     DBG_ASSERT( !bFound, "RegisterEvent: Name in List, but ID not?" );
/*N*/
/*N*/     gp_Name_SortList->Insert( pData, nPos );
/*N*/
/*N*/     SFX_APP()->GetEventConfig()->RegisterEvent( nId, rUIName );
/*N*/ }

/*N*/ BOOL SfxEventConfiguration::Import( SvStream& rInStream, SvStream* pOutStream, SfxObjectShell* pDoc )
/*N*/ {
/*N*/     if ( pDoc )
/*N*/     {
/*N*/         // load events, they are automatically propagated to the document
/*N*/         DBG_ASSERT( !pOutStream, "DocEventConfig must not be converted!" );
/*N*/         SfxEventConfigItem_Impl* pCfg = pDoc->GetEventConfig_Impl( TRUE );
/*N*/       if ( pCfg )
/*N*/           return ( pCfg->Load( rInStream ) == SfxConfigItem::ERR_OK );
/*N*/       DBG_ERROR("Couldn't create EventConfiguration!");
/*N*/       return FALSE;
/*N*/     }
/*?*/     else if ( pOutStream )
/*?*/     {
/*?*/         SfxEventConfiguration aConfig;
/*?*/         if ( aConfig.GetAppEventConfig_Impl()->Load( rInStream ) == SfxConfigItem::ERR_OK )
/*?*/             return aConfig.pAppEventConfig->StoreXML( *pOutStream );
/*?*/         return FALSE;
/*?*/     }
/*?*/
/*?*/     DBG_ERROR( "No OutStream!" );
/*?*/     return FALSE;
/*N*/ }

//STRIP001 BOOL SfxEventConfiguration::Export( SvStream* pInStream, SvStream& rOutStream, SfxObjectShell* pDoc )
//STRIP001 {
//STRIP001     if ( pDoc )
//STRIP001     {
//STRIP001         DBG_ASSERT( !pInStream, "DocEventConfig can't be converted!" );
//STRIP001         SfxEventConfigItem_Impl* pCfg = pDoc->GetEventConfig_Impl();
//STRIP001         if ( pCfg )
//STRIP001             return pCfg->Store( rOutStream );
//STRIP001         DBG_ERROR("Couldn't create EventConfiguration!");
//STRIP001         return FALSE;
//STRIP001     }
//STRIP001     else if ( pInStream )
//STRIP001     {
//STRIP001         SfxEventConfiguration aConfig;
//STRIP001         if ( aConfig.GetAppEventConfig_Impl()->LoadXML( *pInStream ) )
//STRIP001             return aConfig.pAppEventConfig->Store( rOutStream );
//STRIP001         return FALSE;
//STRIP001     }
//STRIP001
//STRIP001     DBG_ERROR( "No InStream!" );
//STRIP001     return FALSE;
//STRIP001 }


}
