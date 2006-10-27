/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_appcfg.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 18:53:27 $
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

#ifndef _COM_SUN_STAR_UNO_REFERENCE_HXX_
#include <com/sun/star/uno/Reference.hxx>
#endif
#ifndef _COM_SUN_STAR_FRAME_XDESKTOP_HPP_
#include <com/sun/star/frame/XDesktop.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XURLTRANSFORMER_HPP_
#include <com/sun/star/util/XURLTransformer.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PropertyValue_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XFLUSHABLE_HPP_
#include <com/sun/star/util/XFlushable.hpp>
#endif

#ifndef _STDLIB_H
#include <stdlib.h>
#endif

#ifndef _CONFIG_HXX
#include <tools/config.hxx>
#endif
#ifndef _SV_SOUND_HXX //autogen
#include <vcl/sound.hxx>
#endif
#ifndef _SV_MSGBOX_HXX //autogen
#include <vcl/msgbox.hxx>
#endif

#ifndef _STRING_HXX
#include <tools/string.hxx>
#endif

#ifndef _SFXITEMPOOL_HXX //autogen
#include <svtools/itempool.hxx>
#endif
#ifndef _AEITEM_HXX //autogen
#include <svtools/aeitem.hxx>
#endif
#ifndef _SFXSLSTITM_HXX //autogen
#include <svtools/slstitm.hxx>
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
#ifndef _SFXSZITEM_HXX
#include <svtools/szitem.hxx>
#endif
#ifndef _UNDO_HXX //autogen
#include <svtools/undo.hxx>
#endif

#define _SVSTDARR_STRINGS
#include <svtools/svstdarr.hxx>

#ifndef _SVTOOLS_TTPROPS_HXX // handmade
#include <svtools/ttprops.hxx>
#endif
#ifndef _SFXSIDS_HRC // handmade
#include <sfxsids.hrc>
#endif
#ifndef _SOT_EXCHANGE_HXX //autogen
#include <sot/exchange.hxx>
#endif

#pragma hdrstop

//#include <svtools/agprop.hxx>
#include <sj2/sjapplet.hxx>

#ifndef _SFXISETHINT_HXX
#include <svtools/isethint.hxx>
#endif

#include <unotools/configmgr.hxx>
#include <tools/urlobj.hxx>
#include <tools/wldcrd.hxx>
#include <svtools/saveopt.hxx>
#include <svtools/helpopt.hxx>
#include <svtools/undoopt.hxx>
#include <svtools/securityoptions.hxx>
#include <svtools/pathoptions.hxx>
#include <svtools/inetoptions.hxx>
#include <svtools/miscopt.hxx>
#include <vcl/toolbox.hxx>
#include <unotools/localfilehelper.hxx>
#include <comphelper/processfactory.hxx>
#include <rtl/ustrbuf.hxx>

#include "docfile.hxx"
#include "viewfrm.hxx"
#include "sfxhelp.hxx"
#include "sfxtypes.hxx"
#include "dispatch.hxx"
#include "objsh.hxx"
#include "objshimp.hxx"
#include "viewsh.hxx"
#include "request.hxx"
#include "evntconf.hxx"
#include "cfgmgr.hxx"
#include "docinf.hxx"
#include "appdata.hxx"
#include "workwin.hxx"
#include <misccfg.hxx>
#include <macrconf.hxx>
#include "appimp.hxx"
#include "helper.hxx"   // SfxContentHelper::...
#include "app.hrc"
#include "sfxresid.hxx"
#include "shutdownicon.hxx"
#include "imgmgr.hxx"

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::beans;

//-------------------------------------------------------------------------

class SfxEventAsyncer_Impl : public SfxListener
{
    SfxEventHint        aHint;
    Timer*              pTimer;

public:

    virtual void        Notify( SfxBroadcaster& rBC, const SfxHint& rHint );
    SfxEventAsyncer_Impl( const SfxEventHint& rHint );
    ~SfxEventAsyncer_Impl();
    DECL_LINK( TimerHdl, Timer*);
};

// -----------------------------------------------------------------------

/*N*/ void SfxEventAsyncer_Impl::Notify( SfxBroadcaster& rBC, const SfxHint& rHint )
/*N*/ {
/*N*/   SfxSimpleHint* pHint = PTR_CAST( SfxSimpleHint, &rHint );
/*N*/   if( pHint && pHint->GetId() == SFX_HINT_DYING && pTimer->IsActive() )
/*N*/   {
/*N*/       pTimer->Stop();
/*?*/       delete this;
/*N*/   }
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxEventAsyncer_Impl::SfxEventAsyncer_Impl( const SfxEventHint& rHint )
/*N*/  : aHint( rHint )
/*N*/ {
/*N*/     if( rHint.GetObjShell() )
/*N*/         StartListening( *rHint.GetObjShell() );
/*?*/   pTimer = new Timer;
/*N*/     pTimer->SetTimeoutHdl( LINK(this, SfxEventAsyncer_Impl, TimerHdl) );
/*N*/   pTimer->SetTimeout( 0 );
/*N*/   pTimer->Start();
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxEventAsyncer_Impl::~SfxEventAsyncer_Impl()
/*N*/ {
/*?*/   delete pTimer;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ IMPL_LINK(SfxEventAsyncer_Impl, TimerHdl, Timer*, pTimer)
/*N*/ {
/*N*/   pTimer->Stop();
/*N*/     SFX_APP()->Broadcast( aHint );
/*N*/     if ( aHint.GetObjShell() )
/*N*/     {
/*?*/         SfxObjectShellRef xRef( aHint.GetObjShell() );
/*N*/         aHint.GetObjShell()->Broadcast( aHint );
/*N*/     }
/*N*/
/*N*/     delete this;
/*N*/   return 0L;
/*N*/ }

/*
const USHORT* SfxApplication::GetOptionsRanges() const
{
    static USHORT pRange[] =
    {
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0, 0,
        0,
    };

    if (0 == pRange[0])
    {
        SfxItemPool &rPool = GetPool();
        pRange[ 0] = SID_OPTIONS_START;
        pRange[ 1] = SID_OPTIONS_FIRSTFREE-1;
        pRange[ 2] = SID_HELPBALLOONS;
        pRange[ 3] = SID_HELPTIPS;
        pRange[ 4] = SID_SECURE_URL;
        pRange[ 5] = SID_SECURE_URL;
        pRange[ 6] = SID_BASIC_ENABLED;
        pRange[ 7] = SID_BASIC_ENABLED;
        pRange[ 8] = SID_AUTO_ADJUSTICONS;
        pRange[ 9] = SID_ICONGRID;
        pRange[ 10 ] = SID_RESTORE_EXPAND_STATE;
        pRange[ 11 ] = SID_RESTORE_EXPAND_STATE;
    }
    return pRange;
}
*/
//--------------------------------------------------------------------

/*?*/ BOOL SfxApplication::GetOptions( SfxItemSet& rSet )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
/*?*/ }

//--------------------------------------------------------------------
//--------------------------------------------------------------------


//--------------------------------------------------------------------

/*?*/ void SfxApplication::SetOptions(const SfxItemSet &rSet)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }

//--------------------------------------------------------------------


//--------------------------------------------------------------------


/*N*/ Timer* SfxApplication::GetAutoSaveTimer_Impl()
/*N*/ {
/*N*/   return pImp->pAutoSaveTimer;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ IMPL_LINK( SfxApplication, AutoSaveHdl_Impl, Timer*, pTimer )
/*N*/ {
/*N*/     SvtSaveOptions aSaveOptions;
/*N*/     FASTBOOL bAutoSave = aSaveOptions.IsAutoSave() &&
/*N*/       !bDispatcherLocked &&
/*N*/       !Application::IsUICaptured() && Application::GetLastInputInterval() > 300;
/*N*/     if ( bAutoSave )
/*N*/     {
/*?*/         SfxViewShell *pVSh = pViewFrame ? pViewFrame->GetViewShell() : 0;
/*?*/         bAutoSave = pVSh && pVSh->GetWindow() &&
/*?*/                   !pVSh->GetWindow()->IsMouseCaptured() ;
/*N*/     }
/*N*/
/*N*/     if ( bAutoSave )
/*N*/     {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/     }
/*N*/     else if ( aSaveOptions.IsAutoSave() )
/*N*/     {
/*N*/         // Wenn wir gelockt sind, dann in 5 Sekunden nochmal probieren
/*?*/         pImp->bAutoSaveNow = TRUE;
/*?*/         pImp->pAutoSaveTimer->SetTimeout( 5000 );
/*?*/         pImp->pAutoSaveTimer->Start();
/*?*/
/*?*/ #ifndef PRODUCT
/*?*/       Sound::Beep();
/*N*/ #endif
/*N*/     }
/*N*/
/*N*/   return 0;
/*N*/ }

//--------------------------------------------------------------------

// alle Dokumente speichern


//--------------------------------------------------------------------

/*N*/ SfxMacroConfig* SfxApplication::GetMacroConfig() const
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return NULL; //STRIP001   return SfxMacroConfig::GetOrCreate();
/*N*/ }

//--------------------------------------------------------------------
/*?*/ #if SUPD < 623
/*?*/ void SfxApplication::RegisterEvent(USHORT nId, const String& rEventName)
/*?*/ {
/*?*/     if (!pAppData_Impl->pEventConfig)
/*?*/         pAppData_Impl->pEventConfig = new SfxEventConfiguration;
/*?*/     String aDummy( "untitled event", RTL_TEXTENCODING_ASCII_US );
/*?*/   SfxEventConfiguration::RegisterEvent(nId, rEventName, aDummy);
/*?*/ }
/*?*/ #endif

//--------------------------------------------------------------------

/*N*/ SfxEventConfiguration* SfxApplication::GetEventConfig() const
/*N*/ {
/*N*/     if (!pAppData_Impl->pEventConfig)
/*N*/         pAppData_Impl->pEventConfig = new SfxEventConfiguration;
/*N*/     return pAppData_Impl->pEventConfig;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxApplication::SaveConfiguration() const
/*N*/ {
/*N*/     // Workingset schreiben?
/*N*/ //    if ( SvtOptions().IsSaveWorkingSet() )
/*N*/ //        SfxTaskManager::SaveWorkingSet();
/*N*/ //(mba/task): Implementierung fehlt
/*N*/
/*N*/     if ( !pCfgMgr->StoreConfiguration() )
/*?*/           {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 /*?*/         HandleConfigError_Impl( (sal_uInt16)pCfgMgr->GetErrorCode() );
/*N*/
/*N*/     ::utl::ConfigManager::GetConfigManager()->StoreConfigItems();
/*N*/ }

//--------------------------------------------------------------------
/*N*/ void SfxApplication::NotifyEvent( const SfxEventHint& rEventHint, FASTBOOL bSynchron )
/*N*/ {
/*N*/     DBG_ASSERT(pAppData_Impl->pEventConfig,"Keine Events angemeldet!");
/*N*/
/*N*/     SfxObjectShell *pDoc = rEventHint.GetObjShell();
/*N*/     if ( pDoc )
/*N*/   {
/*N*/       if ( pDoc->IsPreview() )
/*N*/           return;
/*N*/         SFX_ITEMSET_ARG( pDoc->GetMedium()->GetItemSet(), pItem, SfxBoolItem, SID_HIDDEN, sal_False );
/*N*/       if ( pItem && pItem->GetValue() )
/*N*/           bSynchron = TRUE;
/*N*/   }
/*N*/
/*N*/   // load on demand
/*N*/   pAppData_Impl->pEventConfig->GetAppEventConfig_Impl();
/*N*/
/*N*/   if ( bSynchron )
/*N*/     {
/*N*/         Broadcast(rEventHint);
/*N*/         if ( pDoc )
/*N*/             pDoc->Broadcast( rEventHint );
/*N*/     }
/*N*/     else
/*N*/         new SfxEventAsyncer_Impl( rEventHint );
/*N*/ }

//-------------------------------------------------------------------------
/* ASOBSOLETE
static void CorrectUpdateNumber_Impl(String& rName)
{
    String aUPD( SOLARUPD );
    USHORT nLen = aUPD.Len();
    USHORT nCount,nPos=0;
    do
    {
        nCount=0;
        xub_StrLen nNameLength = rName.Len();
        for ( USHORT i=nPos; i<nNameLength; i++ )
        {
            if ( rName.GetChar(i).CompareToAscii('?') == COMPARE_EQUAL )
            {
                if ( nCount == 0 )
                    nPos=i;
                nCount++;
            }
            else if ( nCount == nLen )
                break;
            else
                nCount=0;
        }
        if ( nCount == nLen )
        {
            rName.Replace( aUPD, nPos );
            nPos += nCount;
        }
    }
    while ( nCount );
}
*/

/*N*/ IMPL_OBJHINT( SfxStringHint, String )

/*N*/ SfxMiscCfg* SfxApplication::GetMiscConfig()
/*N*/ {
/*N*/   if ( !pAppData_Impl->pMiscConfig )
/*N*/       pAppData_Impl->pMiscConfig = new SfxMiscCfg;
/*N*/
/*N*/   return pAppData_Impl->pMiscConfig;
/*N*/ }


}
