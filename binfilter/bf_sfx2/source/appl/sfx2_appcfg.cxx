/*************************************************************************
 *
 *  $RCSfile: sfx2_appcfg.cxx,v $
 *
 *  $Revision: 1.3 $
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
/*?*/ {DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001     BOOL bRet = FALSE;
//STRIP001     SfxItemPool &rPool = GetPool();
//STRIP001  String aTRUEStr = 0x0031; // ^= '1'
//STRIP001
//STRIP001  const USHORT *pRanges = rSet.GetRanges();
//STRIP001     SvtSaveOptions aSaveOptions;
//STRIP001     SvtUndoOptions aUndoOptions;
//STRIP001     SvtHelpOptions aHelpOptions;
//STRIP001  SvtInetOptions aInetOptions;
//STRIP001  SvtSecurityOptions  aSecurityOptions;
//STRIP001     SvtMiscOptions aMiscOptions;
//STRIP001
//STRIP001  while ( *pRanges )
//STRIP001  {
//STRIP001      for(USHORT nWhich = *pRanges++; nWhich <= *pRanges; ++nWhich)
//STRIP001      {
//STRIP001          switch(nWhich)
//STRIP001          {
//STRIP001              case SID_ATTR_BUTTON_OUTSTYLE3D :
//STRIP001                  if(rSet.Put( SfxBoolItem( rPool.GetWhich( SID_ATTR_BUTTON_OUTSTYLE3D ),
//STRIP001                               aMiscOptions.GetToolboxStyle() != TOOLBOX_STYLE_FLAT)))
//STRIP001                      bRet = TRUE;
//STRIP001                  break;
//STRIP001              case SID_ATTR_BUTTON_BIGSIZE :
//STRIP001                  if(rSet.Put( SfxBoolItem( rPool.GetWhich( SID_ATTR_BUTTON_BIGSIZE ),
//STRIP001                               SfxImageManager::GetCurrentSymbolSet() == SFX_SYMBOLS_LARGE)))
//STRIP001                      bRet = TRUE;
//STRIP001                  break;
//STRIP001              case SID_ATTR_BACKUP :
//STRIP001                     {
//STRIP001                         bRet = TRUE;
//STRIP001                         if (!aSaveOptions.IsReadOnly(SvtSaveOptions::E_BACKUP))
//STRIP001                             if (!rSet.Put( SfxBoolItem( rPool.GetWhich( SID_ATTR_BACKUP ),aSaveOptions.IsBackup())))
//STRIP001                                 bRet = FALSE;
//STRIP001                     }
//STRIP001                  break;
//STRIP001              case SID_ATTR_PRETTYPRINTING:
//STRIP001                     {
//STRIP001                         bRet = TRUE;
//STRIP001                         if (!aSaveOptions.IsReadOnly(SvtSaveOptions::E_DOPRETTYPRINTING))
//STRIP001                             if (!rSet.Put( SfxBoolItem( rPool.GetWhich( SID_ATTR_PRETTYPRINTING ), aSaveOptions.IsPrettyPrinting())))
//STRIP001                                 bRet = FALSE;
//STRIP001                     }
//STRIP001                  break;
//STRIP001              case SID_ATTR_AUTOSAVE :
//STRIP001                     {
//STRIP001                         bRet = TRUE;
//STRIP001                         if (!aSaveOptions.IsReadOnly(SvtSaveOptions::E_AUTOSAVE))
//STRIP001                             if (!rSet.Put( SfxBoolItem( rPool.GetWhich( SID_ATTR_AUTOSAVE ), aSaveOptions.IsAutoSave())))
//STRIP001                                 bRet = FALSE;
//STRIP001                     }
//STRIP001                  break;
//STRIP001              case SID_ATTR_AUTOSAVEPROMPT :
//STRIP001                     {
//STRIP001                         bRet = TRUE;
//STRIP001                         if (!aSaveOptions.IsReadOnly(SvtSaveOptions::E_AUTOSAVEPROMPT))
//STRIP001                             if (!rSet.Put( SfxBoolItem( rPool.GetWhich( SID_ATTR_AUTOSAVEPROMPT ), aSaveOptions.IsAutoSavePrompt())))
//STRIP001                                 bRet = FALSE;
//STRIP001                     }
//STRIP001                  break;
//STRIP001              case SID_ATTR_AUTOSAVEMINUTE :
//STRIP001                     {
//STRIP001                         bRet = TRUE;
//STRIP001                         if (!aSaveOptions.IsReadOnly(SvtSaveOptions::E_AUTOSAVETIME))
//STRIP001                             if (!rSet.Put( SfxUInt16Item( rPool.GetWhich( SID_ATTR_AUTOSAVEMINUTE ), (UINT16)aSaveOptions.GetAutoSaveTime())))
//STRIP001                                 bRet = FALSE;
//STRIP001                     }
//STRIP001                  break;
//STRIP001              case SID_ATTR_DOCINFO :
//STRIP001                     {
//STRIP001                         bRet = TRUE;
//STRIP001                         if (!aSaveOptions.IsReadOnly(SvtSaveOptions::E_DOCINFSAVE))
//STRIP001                             if (!rSet.Put( SfxBoolItem( rPool.GetWhich( SID_ATTR_DOCINFO ), aSaveOptions.IsDocInfoSave())))
//STRIP001                                 bRet = FALSE;
//STRIP001                     }
//STRIP001                  break;
//STRIP001              case SID_OPT_SAVEGRAPHICSCOMPRESSED :
//STRIP001              {
//STRIP001                     {
//STRIP001                         bRet = TRUE;
//STRIP001                         if (!aSaveOptions.IsReadOnly(SvtSaveOptions::E_SAVEGRAPHICS))
//STRIP001                         {
//STRIP001                             SfxDocumentInfo *pDocInf = SfxObjectShell::Current() ? &SfxObjectShell::Current()->GetDocInfo() : 0;
//STRIP001                             BOOL bComprGraph = pDocInf ? pDocInf->IsSaveGraphicsCompressed() : aSaveOptions.GetSaveGraphicsMode() == SvtSaveOptions::SaveGraphicsCompressed;
//STRIP001                             if (!rSet.Put( SfxBoolItem( rPool.GetWhich( SID_OPT_SAVEGRAPHICSCOMPRESSED ),bComprGraph )))
//STRIP001                                 bRet = FALSE;
//STRIP001                         }
//STRIP001                     }
//STRIP001                  break;
//STRIP001              }
//STRIP001              case SID_OPT_SAVEORIGINALGRAPHICS :
//STRIP001              {
//STRIP001                     {
//STRIP001                         bRet = TRUE;
//STRIP001                         if (!aSaveOptions.IsReadOnly(SvtSaveOptions::E_SAVEGRAPHICS))
//STRIP001                         {
//STRIP001                             SfxDocumentInfo *pDocInf = SfxObjectShell::Current() ? &SfxObjectShell::Current()->GetDocInfo() : 0;
//STRIP001                             BOOL bOrigGraph = pDocInf ? pDocInf->IsSaveOriginalGraphics() : aSaveOptions.GetSaveGraphicsMode() == SvtSaveOptions::SaveGraphicsOriginal;
//STRIP001                             if (!rSet.Put( SfxBoolItem( rPool.GetWhich( SID_OPT_SAVEORIGINALGRAPHICS ), bOrigGraph )))
//STRIP001                                 bRet = FALSE;
//STRIP001                         }
//STRIP001                     }
//STRIP001                  break;
//STRIP001              }
//STRIP001              case SID_ATTR_WORKINGSET :
//STRIP001                     {
//STRIP001                         bRet = TRUE;
//STRIP001                         if (!aSaveOptions.IsReadOnly(SvtSaveOptions::E_SAVEWORKINGSET))
//STRIP001                             if (!rSet.Put( SfxBoolItem( rPool.GetWhich( SID_ATTR_WORKINGSET ), aSaveOptions.IsSaveWorkingSet())))
//STRIP001                                 bRet = FALSE;
//STRIP001                     }
//STRIP001                  break;
//STRIP001              case SID_ATTR_SAVEDOCWINS :
//STRIP001                     {
//STRIP001                         bRet = TRUE;
//STRIP001                         if (!aSaveOptions.IsReadOnly(SvtSaveOptions::E_SAVEDOCWINS))
//STRIP001                             if (!rSet.Put( SfxBoolItem( rPool.GetWhich( SID_ATTR_SAVEDOCWINS ), aSaveOptions.IsSaveDocWins())))
//STRIP001                                 bRet = FALSE;
//STRIP001                     }
//STRIP001                  break;
//STRIP001              case SID_ATTR_SAVEDOCVIEW :
//STRIP001                     {
//STRIP001                         bRet = TRUE;
//STRIP001                         if (!aSaveOptions.IsReadOnly(SvtSaveOptions::E_SAVEDOCVIEW))
//STRIP001                             if (!rSet.Put( SfxBoolItem( rPool.GetWhich( SID_ATTR_SAVEDOCVIEW ), aSaveOptions.IsSaveDocView())))
//STRIP001                                 bRet = FALSE;
//STRIP001                     }
//STRIP001                  break;
//STRIP001              case SID_ATTR_METRIC :
//STRIP001 //                    if(rSet.Put( SfxUInt16Item( rPool.GetWhich( SID_ATTR_METRIC ),
//STRIP001 //                                pOptions->GetMetric() ) ) )
//STRIP001 //                        bRet = TRUE;
//STRIP001                  break;
//STRIP001              case SID_HELPBALLOONS :
//STRIP001                  if(rSet.Put( SfxBoolItem ( rPool.GetWhich( SID_HELPBALLOONS ),
//STRIP001                                aHelpOptions.IsExtendedHelp() ) ) )
//STRIP001                      bRet = TRUE;
//STRIP001                  break;
//STRIP001              case SID_HELPTIPS :
//STRIP001                  if(rSet.Put( SfxBoolItem ( rPool.GetWhich( SID_HELPTIPS ),
//STRIP001                                aHelpOptions.IsHelpTips() ) ) )
//STRIP001                      bRet = TRUE;
//STRIP001                  break;
//STRIP001              case SID_ATTR_AUTOHELPAGENT :
//STRIP001                  if(rSet.Put( SfxBoolItem ( rPool.GetWhich( SID_ATTR_AUTOHELPAGENT ),
//STRIP001                                aHelpOptions.IsHelpAgentAutoStartMode() ) ) )
//STRIP001                      bRet = TRUE;
//STRIP001                  break;
//STRIP001              case SID_HELPAGENT_TIMEOUT :
//STRIP001                  if ( rSet.Put( SfxInt32Item( rPool.GetWhich( SID_HELPAGENT_TIMEOUT ),
//STRIP001                                               aHelpOptions.GetHelpAgentTimeoutPeriod() ) ) )
//STRIP001                      bRet = TRUE;
//STRIP001                  break;
//STRIP001              case SID_ATTR_WELCOMESCREEN :
//STRIP001                  if(rSet.Put( SfxBoolItem ( rPool.GetWhich( SID_ATTR_WELCOMESCREEN ),
//STRIP001                                aHelpOptions.IsWelcomeScreen() ) ) )
//STRIP001                      bRet = TRUE;
//STRIP001                  break;
//STRIP001                 case SID_HELP_STYLESHEET :
//STRIP001                     if(rSet.Put( SfxStringItem ( rPool.GetWhich( SID_HELP_STYLESHEET ),
//STRIP001                                aHelpOptions.GetHelpStyleSheet() ) ) )
//STRIP001                      bRet = TRUE;
//STRIP001                 break;
//STRIP001              case SID_ATTR_UNDO_COUNT :
//STRIP001                  if(rSet.Put( SfxUInt16Item ( rPool.GetWhich( SID_ATTR_UNDO_COUNT ),
//STRIP001                                  (UINT16)aUndoOptions.GetUndoCount() ) ) )
//STRIP001                      bRet = TRUE;
//STRIP001                  break;
//STRIP001              case SID_ATTR_QUICKLAUNCHER :
//STRIP001                  if(rSet.Put( SfxBoolItem ( rPool.GetWhich( SID_ATTR_QUICKLAUNCHER ),
//STRIP001                         ShutdownIcon::GetAutostart()  ) ) )
//STRIP001                      bRet = TRUE;
//STRIP001                  break;
//STRIP001              case SID_SAVEREL_INET :
//STRIP001                     {
//STRIP001                         bRet = TRUE;
//STRIP001                         if (!aSaveOptions.IsReadOnly(SvtSaveOptions::E_SAVERELINET))
//STRIP001                             if (!rSet.Put( SfxBoolItem ( rPool.GetWhich( SID_SAVEREL_INET ), aSaveOptions.IsSaveRelINet() )))
//STRIP001                                 bRet = FALSE;
//STRIP001                     }
//STRIP001                  break;
//STRIP001              case SID_SAVEREL_FSYS :
//STRIP001                     {
//STRIP001                         bRet = TRUE;
//STRIP001                         if (!aSaveOptions.IsReadOnly(SvtSaveOptions::E_SAVERELFSYS))
//STRIP001                             if (!rSet.Put( SfxBoolItem ( rPool.GetWhich( SID_SAVEREL_FSYS ), aSaveOptions.IsSaveRelFSys() )))
//STRIP001                                 bRet = FALSE;
//STRIP001                     }
//STRIP001                  break;
//STRIP001                 case SID_BASIC_ENABLED :
//STRIP001                     {
//STRIP001                         bRet = TRUE;
//STRIP001                         if (!aSecurityOptions.IsReadOnly(SvtSecurityOptions::E_BASICMODE))
//STRIP001                         {
//STRIP001                             if ( !rSet.Put( SfxUInt16Item( rPool.GetWhich( SID_BASIC_ENABLED ), aSecurityOptions.GetBasicMode())))
//STRIP001                                 bRet = FALSE;
//STRIP001                         }
//STRIP001                     }
//STRIP001                     break;
//STRIP001                 case SID_INET_EXE_PLUGIN  :
//STRIP001                     {
//STRIP001                         bRet = TRUE;
//STRIP001                         if (!aSecurityOptions.IsReadOnly(SvtSecurityOptions::E_EXECUTEPLUGINS))
//STRIP001                         {
//STRIP001                             if ( !rSet.Put( SfxBoolItem( SID_INET_EXE_PLUGIN, aSecurityOptions.IsExecutePlugins() ) ) )
//STRIP001                                 bRet = FALSE;
//STRIP001                         }
//STRIP001                     }
//STRIP001                     break;
//STRIP001                 case SID_MACRO_WARNING :
//STRIP001                     {
//STRIP001                         bRet = TRUE;
//STRIP001                         if (!aSecurityOptions.IsReadOnly(SvtSecurityOptions::E_WARNING))
//STRIP001                         {
//STRIP001                             if ( !rSet.Put( SfxBoolItem( SID_MACRO_WARNING, aSecurityOptions.IsWarningEnabled() ) ) )
//STRIP001                                 bRet = FALSE;
//STRIP001                         }
//STRIP001                     }
//STRIP001                     break;
//STRIP001                 case SID_MACRO_CONFIRMATION :
//STRIP001                     {
//STRIP001                         bRet = TRUE;
//STRIP001                         if (!aSecurityOptions.IsReadOnly(SvtSecurityOptions::E_CONFIRMATION))
//STRIP001                         {
//STRIP001                             if ( !rSet.Put( SfxBoolItem( SID_MACRO_CONFIRMATION, aSecurityOptions.IsConfirmationEnabled() ) ) )
//STRIP001                                 bRet = FALSE;
//STRIP001                         }
//STRIP001                     }
//STRIP001                     break;
//STRIP001                 case SID_SECURE_URL :
//STRIP001                     {
//STRIP001                         bRet = TRUE;
//STRIP001                         if (!aSecurityOptions.IsReadOnly(SvtSecurityOptions::E_SECUREURLS))
//STRIP001                         {
//STRIP001                             ::com::sun::star::uno::Sequence< ::rtl::OUString > seqURLs = aSecurityOptions.GetSecureURLs();
//STRIP001                             List aList;
//STRIP001                             sal_uInt32 nCount = seqURLs.getLength();
//STRIP001                             sal_uInt32 nURL;
//STRIP001                             for( nURL=0; nURL<nCount; ++nURL )
//STRIP001                             {
//STRIP001                                 aList.Insert( new String( seqURLs[nURL] ), LIST_APPEND );
//STRIP001                             }
//STRIP001                             if( !rSet.Put( SfxStringListItem( rPool.GetWhich(SID_SECURE_URL),
//STRIP001                                     &aList ) ) )
//STRIP001                             {
//STRIP001                                 bRet = FALSE;
//STRIP001                             }
//STRIP001                             for( nURL=0; nURL<nCount; ++nURL )
//STRIP001                             {
//STRIP001                                 delete (String*)aList.GetObject(nURL);
//STRIP001                             }
//STRIP001                             aList.Clear();
//STRIP001                         }
//STRIP001                     }
//STRIP001                     break;
//STRIP001              case SID_ENABLE_METAFILEPRINT :
//STRIP001 #ifdef ENABLE_MISSINGKEYASSERTIONS//MUSTINI
//STRIP001                  DBG_ASSERT(sal_False, "SfxApplication::GetOptions()\nSoffice.ini key \"Common\\MetafilePrint\" is obsolete! .. How I can support SID_ENABLE_METAFILEPRINT any longer?\n");
//STRIP001 #endif
//STRIP001                  break;
//STRIP001                 case SID_INET_PROXY_TYPE :
//STRIP001                 {
//STRIP001                     if ( IsPlugin() )
//STRIP001                     {
//STRIP001                         UINT16 nType = 1; // default is "use browser settings"!
//STRIP001                         String sName    ; // set it only for type=2! otherwise=defaults!
//STRIP001                         INT32  nPort = 0;
//STRIP001                         // Use propertyset of remote(!) login dialog service to get right informations ....
//STRIP001                         ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > xRemoteProxyConfig( ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance( DEFINE_CONST_OUSTRING("com.sun.star.comp.framework.LoginDialog")), ::com::sun::star::uno::UNO_QUERY );
//STRIP001                         if( xRemoteProxyConfig.is() == sal_True )
//STRIP001                         {
//STRIP001                             ::com::sun::star::uno::Any aPropValue = xRemoteProxyConfig->getPropertyValue( DEFINE_CONST_OUSTRING("UseProxy") );
//STRIP001                             ::rtl::OUString sProxyType;
//STRIP001                             aPropValue >>= sProxyType;
//STRIP001                             if( sProxyType.compareToAscii("none")==0 )
//STRIP001                                 nType = 0;
//STRIP001                             else
//STRIP001                             if( sProxyType.compareToAscii("browser")==0 )
//STRIP001                                 nType = 1;
//STRIP001                             else
//STRIP001                             if( sProxyType.compareToAscii("custom")==0 )
//STRIP001                             {
//STRIP001                                 nType = 2;
//STRIP001                                 aPropValue = xRemoteProxyConfig->getPropertyValue( DEFINE_CONST_OUSTRING("SecurityProxy") );
//STRIP001                                 ::rtl::OUString sProxyValues;
//STRIP001                                 aPropValue >>= sProxyValues;
//STRIP001
//STRIP001                                 if( sProxyValues.indexOf( (sal_Unicode)':' ) > 0 )
//STRIP001                                 {
//STRIP001                                     sal_Int32 nToken = 0;
//STRIP001                                     sName = sProxyValues.getToken( 0, (sal_Unicode)':', nToken );
//STRIP001                                     if( nToken != -1 )
//STRIP001                                         nPort = sProxyValues.getToken( 0, (sal_Unicode)':', nToken ).toInt32();
//STRIP001                                 }
//STRIP001                             }
//STRIP001                         }
//STRIP001                         if(
//STRIP001                             ( rSet.Put( SfxUInt16Item ( rPool.GetWhich( SID_INET_PROXY_TYPE      ), nType )))    &&
//STRIP001                             ( rSet.Put( SfxStringItem ( rPool.GetWhich( SID_INET_HTTP_PROXY_NAME ), sName )))    &&
//STRIP001                             ( rSet.Put( SfxInt32Item  ( rPool.GetWhich( SID_INET_HTTP_PROXY_PORT ), nPort )))
//STRIP001                           )
//STRIP001                         {
//STRIP001                             bRet = TRUE;
//STRIP001                         }
//STRIP001                     }
//STRIP001                     else if( rSet.Put( SfxUInt16Item ( rPool.GetWhich( SID_INET_PROXY_TYPE ),
//STRIP001                                 (UINT16)aInetOptions.GetProxyType() )))
//STRIP001                             bRet = TRUE;
//STRIP001                     break;
//STRIP001                 }
//STRIP001                 case SID_INET_HTTP_PROXY_NAME :
//STRIP001                 {
//STRIP001                     if ( IsPlugin() )
//STRIP001                     {
//STRIP001                         // This value is neccessary for SID_INET_PROXY_TYPE=2 only!
//STRIP001                         // So we do nothing here! No defaults (otherwise we overwrite real values!)
//STRIP001                         // no right values (they are superflous then) ...
//STRIP001                         // We set it for SID_INET_PROXY_TYPE queries only!!!
//STRIP001                         bRet = TRUE;
//STRIP001                     }
//STRIP001                     else if ( rSet.Put( SfxStringItem ( rPool.GetWhich(SID_INET_HTTP_PROXY_NAME ),
//STRIP001                             aInetOptions.GetProxyHttpName() )))
//STRIP001                         bRet = TRUE;
//STRIP001                     break;
//STRIP001                 }
//STRIP001                 case SID_INET_HTTP_PROXY_PORT :
//STRIP001                     if ( IsPlugin() )
//STRIP001                     {
//STRIP001                         // This value is neccessary for SID_INET_PROXY_TYPE=2 only!
//STRIP001                         // So we do nothing here! No defaults (otherwise we overwrite real values!)
//STRIP001                         // no right values (they are superflous then) ...
//STRIP001                         // We set it for SID_INET_PROXY_TYPE queries only!!!
//STRIP001                         bRet = TRUE;
//STRIP001                     }
//STRIP001                     else if ( rSet.Put( SfxInt32Item( rPool.GetWhich(SID_INET_HTTP_PROXY_PORT ),
//STRIP001                             aInetOptions.GetProxyHttpPort() )))
//STRIP001                         bRet = TRUE;
//STRIP001                     break;
//STRIP001                 case SID_INET_FTP_PROXY_NAME :
//STRIP001                     if ( !IsPlugin() && rSet.Put( SfxStringItem ( rPool.GetWhich(SID_INET_FTP_PROXY_NAME ),
//STRIP001                             aInetOptions.GetProxyFtpName() )))
//STRIP001                         bRet = TRUE;
//STRIP001                     break;
//STRIP001                 case SID_INET_FTP_PROXY_PORT :
//STRIP001                     if ( !IsPlugin() && rSet.Put( SfxInt32Item ( rPool.GetWhich(SID_INET_FTP_PROXY_PORT ),
//STRIP001                             aInetOptions.GetProxyFtpPort() )))
//STRIP001                         bRet = TRUE;
//STRIP001                     break;
//STRIP001                 case SID_INET_SECURITY_PROXY_NAME :
//STRIP001                 case SID_INET_SECURITY_PROXY_PORT :
//STRIP001 #ifdef ENABLE_MISSINGKEYASSERTIONS//MUSTINI
//STRIP001                     DBG_ASSERT( sal_False, "SfxApplication::GetOptions()\nSome INET values no longer supported!\n" );
//STRIP001 #endif
//STRIP001                     break;
//STRIP001                 case SID_INET_NOPROXY :
//STRIP001                     if( !IsPlugin() && rSet.Put( SfxStringItem ( rPool.GetWhich( SID_INET_NOPROXY),
//STRIP001                                 aInetOptions.GetProxyNoProxy() )))
//STRIP001                         bRet = TRUE;
//STRIP001                     break;
//STRIP001              case SID_ATTR_PATHNAME :
//STRIP001              case SID_ATTR_PATHGROUP :
//STRIP001              {
//STRIP001                  SfxAllEnumItem aNames(rPool.GetWhich(SID_ATTR_PATHGROUP));
//STRIP001                  SfxAllEnumItem aValues(rPool.GetWhich(SID_ATTR_PATHNAME));
//STRIP001                     SvtPathOptions aPathCfg;
//STRIP001                     for ( int nProp = SvtPathOptions::PATH_ADDIN;
//STRIP001                        nProp <= SvtPathOptions::PATH_WORK; nProp++ )
//STRIP001                     {
//STRIP001                      const String aName( SfxResId( CONFIG_PATH_START + nProp ) );
//STRIP001                      aNames.InsertValue( nProp, aName );
//STRIP001                         String aValue;
//STRIP001                         switch ( nProp )
//STRIP001                         {
//STRIP001                             case SvtPathOptions::PATH_ADDIN:        ::utl::LocalFileHelper::ConvertPhysicalNameToURL( aPathCfg.GetAddinPath(), aValue ); break;
//STRIP001                             case SvtPathOptions::PATH_AUTOCORRECT:  aValue = aPathCfg.GetAutoCorrectPath(); break;
//STRIP001                             case SvtPathOptions::PATH_AUTOTEXT:     aValue = aPathCfg.GetAutoTextPath(); break;
//STRIP001                             case SvtPathOptions::PATH_BACKUP:       aValue = aPathCfg.GetBackupPath(); break;
//STRIP001                             case SvtPathOptions::PATH_BASIC:        aValue = aPathCfg.GetBasicPath(); break;
//STRIP001                             case SvtPathOptions::PATH_BITMAP:       aValue = aPathCfg.GetBitmapPath(); break;
//STRIP001                             case SvtPathOptions::PATH_CONFIG:       aValue = aPathCfg.GetConfigPath(); break;
//STRIP001                             case SvtPathOptions::PATH_DICTIONARY:   aValue = aPathCfg.GetDictionaryPath(); break;
//STRIP001                             case SvtPathOptions::PATH_FAVORITES:    aValue = aPathCfg.GetFavoritesPath(); break;
//STRIP001                             case SvtPathOptions::PATH_FILTER:       ::utl::LocalFileHelper::ConvertPhysicalNameToURL( aPathCfg.GetFilterPath(), aValue ); break;
//STRIP001                             case SvtPathOptions::PATH_GALLERY:      aValue = aPathCfg.GetGalleryPath(); break;
//STRIP001                             case SvtPathOptions::PATH_GRAPHIC:      aValue = aPathCfg.GetGraphicPath(); break;
//STRIP001                             case SvtPathOptions::PATH_HELP:         ::utl::LocalFileHelper::ConvertPhysicalNameToURL( aPathCfg.GetHelpPath(), aValue ); break;
//STRIP001                             case SvtPathOptions::PATH_LINGUISTIC:   aValue = aPathCfg.GetLinguisticPath(); break;
//STRIP001                             case SvtPathOptions::PATH_MODULE:       ::utl::LocalFileHelper::ConvertPhysicalNameToURL( aPathCfg.GetModulePath(), aValue ); break;
//STRIP001                             case SvtPathOptions::PATH_PALETTE:      aValue = aPathCfg.GetPalettePath(); break;
//STRIP001                             case SvtPathOptions::PATH_PLUGIN:       ::utl::LocalFileHelper::ConvertPhysicalNameToURL( aPathCfg.GetPluginPath(), aValue ); break;
//STRIP001                             case SvtPathOptions::PATH_STORAGE:      ::utl::LocalFileHelper::ConvertPhysicalNameToURL( aPathCfg.GetStoragePath(), aValue ); break;
//STRIP001                             case SvtPathOptions::PATH_TEMP:         aValue = aPathCfg.GetTempPath(); break;
//STRIP001                             case SvtPathOptions::PATH_TEMPLATE:     aValue = aPathCfg.GetTemplatePath(); break;
//STRIP001                             case SvtPathOptions::PATH_USERCONFIG:   aValue = aPathCfg.GetUserConfigPath(); break;
//STRIP001                             case SvtPathOptions::PATH_USERDICTIONARY: aValue = aPathCfg.GetUserDictionaryPath(); break;
//STRIP001                             case SvtPathOptions::PATH_WORK:         aValue = aPathCfg.GetWorkPath(); break;
//STRIP001                         }
//STRIP001                         aValues.InsertValue( nProp, aValue );
//STRIP001                     }
//STRIP001
//STRIP001                  if ( rSet.Put(aNames) || rSet.Put(aValues) )
//STRIP001                      bRet = TRUE;
//STRIP001              }
//STRIP001
//STRIP001              default:
//STRIP001                  DBG_WARNING( "W1:Wrong ID while getting Options!" );
//STRIP001                  break;
//STRIP001          }
//STRIP001 #ifdef DBG_UTIL
//STRIP001          if ( !bRet )
//STRIP001              DBG_ERROR( "Putting options failed!" );
//STRIP001 #endif
//STRIP001      }
//STRIP001      pRanges++;
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
/*?*/ }

//--------------------------------------------------------------------
//STRIP001 BOOL SfxApplication::IsSecureURL( const INetURLObject& rURL, const String* pReferer ) const
//STRIP001 {
//STRIP001  return SvtSecurityOptions().IsSecureURL( rURL.GetMainURL( INetURLObject::NO_DECODE ), *pReferer );
//STRIP001 }
//--------------------------------------------------------------------

//STRIP001 void SfxApplication::SetOptions_Impl( const SfxItemSet& rSet )
//STRIP001 {
//STRIP001     const SfxPoolItem *pItem = 0;
//STRIP001     SfxItemPool &rPool = GetPool();
//STRIP001  BOOL bResetSession = FALSE;
//STRIP001  BOOL bProxiesModified = FALSE;
//STRIP001
//STRIP001     SvtSaveOptions aSaveOptions;
//STRIP001     SvtUndoOptions aUndoOptions;
//STRIP001     SvtHelpOptions aHelpOptions;
//STRIP001  SvtSecurityOptions aSecurityOptions;
//STRIP001  SvtPathOptions aPathOptions;
//STRIP001  SvtInetOptions aInetOptions;
//STRIP001     SvtMiscOptions aMiscOptions;
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_ATTR_BUTTON_OUTSTYLE3D), TRUE, &pItem) )
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxBoolItem), "BoolItem expected");
//STRIP001      USHORT nOutStyle =
//STRIP001          ( (const SfxBoolItem *)pItem)->GetValue() ? 0 : TOOLBOX_STYLE_FLAT;
//STRIP001         aMiscOptions.SetToolboxStyle( nOutStyle );
//STRIP001     }
//STRIP001
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_ATTR_BUTTON_BIGSIZE), TRUE, &pItem) )
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxBoolItem), "BoolItem expected");
//STRIP001      BOOL bBigSize = ( (const SfxBoolItem*)pItem )->GetValue();
//STRIP001         aMiscOptions.SetSymbolSet( bBigSize ? SFX_SYMBOLS_LARGE : SFX_SYMBOLS_SMALL );
//STRIP001         SfxViewFrame* pViewFrame = SfxViewFrame::GetFirst();
//STRIP001         while ( pViewFrame )
//STRIP001         {
//STRIP001             // update all "final" dispatchers
//STRIP001             if ( !pViewFrame->GetActiveChildFrame_Impl() )
//STRIP001                 pViewFrame->GetDispatcher()->Update_Impl(sal_True);
//STRIP001             pViewFrame = SfxViewFrame::GetNext(*pViewFrame);
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001  // Backup
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_ATTR_BACKUP), TRUE, &pItem) )
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxBoolItem), "BoolItem expected");
//STRIP001         aSaveOptions.SetBackup( ( (const SfxBoolItem*)pItem )->GetValue() );
//STRIP001     }
//STRIP001
//STRIP001  // PrettyPrinting
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState( rPool.GetWhich( SID_ATTR_PRETTYPRINTING ), TRUE, &pItem ) )
//STRIP001     {
//STRIP001         DBG_ASSERT( pItem->ISA( SfxBoolItem ), "BoolItem expected" );
//STRIP001         aSaveOptions.SetPrettyPrinting( static_cast< const SfxBoolItem*> ( pItem )->GetValue() );
//STRIP001     }
//STRIP001
//STRIP001  // AutoSave
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_ATTR_AUTOSAVE), TRUE, &pItem))
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxBoolItem), "BoolItem expected");
//STRIP001         aSaveOptions.SetAutoSave( ( (const SfxBoolItem*)pItem )->GetValue() );
//STRIP001     }
//STRIP001
//STRIP001  // AutoSave-Propt
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_ATTR_AUTOSAVEPROMPT), TRUE, &pItem))
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxBoolItem), "BoolItem expected");
//STRIP001         aSaveOptions.SetAutoSavePrompt(((const SfxBoolItem *)pItem)->GetValue());
//STRIP001     }
//STRIP001
//STRIP001  // AutoSave-Time
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_ATTR_AUTOSAVEMINUTE), TRUE, &pItem))
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxUInt16Item), "UInt16Item expected");
//STRIP001         aSaveOptions.SetAutoSaveTime(((const SfxUInt16Item *)pItem)->GetValue());
//STRIP001     }
//STRIP001
//STRIP001  // DocInfo
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_ATTR_DOCINFO), TRUE, &pItem))
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxBoolItem), "BoolItem expected");
//STRIP001         aSaveOptions.SetDocInfoSave(((const SfxBoolItem *)pItem)->GetValue());
//STRIP001     }
//STRIP001
//STRIP001  // Grafiken komprimiert speichern
//STRIP001     SvtSaveOptions::SaveGraphicsMode eMode = SvtSaveOptions::SaveGraphicsNormal;
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_OPT_SAVEGRAPHICSCOMPRESSED), TRUE, &pItem))
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxBoolItem), "BoolItem expected");
//STRIP001      BOOL b = ((const SfxBoolItem *)pItem)->GetValue();
//STRIP001         if ( b )
//STRIP001             eMode = SvtSaveOptions::SaveGraphicsCompressed;
//STRIP001     }
//STRIP001
//STRIP001  // Grafiken im Original speichern
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_OPT_SAVEORIGINALGRAPHICS), TRUE, &pItem))
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxBoolItem), "BoolItem expected");
//STRIP001      BOOL b = ((const SfxBoolItem *)pItem)->GetValue();
//STRIP001         if ( b )
//STRIP001             eMode = SvtSaveOptions::SaveGraphicsOriginal;
//STRIP001     }
//STRIP001
//STRIP001     if ( eMode != aSaveOptions.GetSaveGraphicsMode() )
//STRIP001         aSaveOptions.SetSaveGraphicsMode( eMode );
//STRIP001
//STRIP001  // offende Dokumente merken
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_ATTR_WORKINGSET), TRUE, &pItem))
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxBoolItem), "BoolItem expected");
//STRIP001         aSaveOptions.SetSaveWorkingSet(((const SfxBoolItem *)pItem)->GetValue());
//STRIP001     }
//STRIP001
//STRIP001  // offene Fenster speichern
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_ATTR_SAVEDOCWINS), TRUE, &pItem))
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxBoolItem), "BoolItem expected");
//STRIP001         aSaveOptions.SetSaveDocWins(((const SfxBoolItem *)pItem)->GetValue());
//STRIP001     }
//STRIP001
//STRIP001  // Fenster-Einstellung speichern
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_ATTR_SAVEDOCVIEW), TRUE, &pItem))
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxBoolItem), "BoolItem expected");
//STRIP001         aSaveOptions.SetSaveDocView(((const SfxBoolItem *)pItem)->GetValue());
//STRIP001     }
//STRIP001
//STRIP001  // Metric
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_ATTR_METRIC), TRUE, &pItem))
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxUInt16Item), "UInt16Item expected");
//STRIP001 //        pOptions->SetMetric((FieldUnit)((const SfxUInt16Item*)pItem)->GetValue());
//STRIP001     }
//STRIP001
//STRIP001  // HelpBalloons
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_HELPBALLOONS), TRUE, &pItem))
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxBoolItem), "BoolItem expected");
//STRIP001         aHelpOptions.SetExtendedHelp(((const SfxBoolItem *)pItem)->GetValue());
//STRIP001     }
//STRIP001
//STRIP001  // HelpTips
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_HELPTIPS), TRUE, &pItem))
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxBoolItem), "BoolItem expected");
//STRIP001         aHelpOptions.SetHelpTips(((const SfxBoolItem *)pItem)->GetValue());
//STRIP001     }
//STRIP001
//STRIP001  // AutoHelpAgent
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_ATTR_AUTOHELPAGENT ), TRUE, &pItem))
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxBoolItem), "BoolItem expected");
//STRIP001         aHelpOptions.SetHelpAgentAutoStartMode( ((const SfxBoolItem *)pItem)->GetValue() );
//STRIP001     }
//STRIP001
//STRIP001  // help agent timeout
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState( rPool.GetWhich( SID_HELPAGENT_TIMEOUT ), TRUE, &pItem ) )
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxInt32Item), "Int32Item expected");
//STRIP001      aHelpOptions.SetHelpAgentTimeoutPeriod( ( (const SfxInt32Item*)pItem )->GetValue() );
//STRIP001     }
//STRIP001
//STRIP001  // WelcomeScreen
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_ATTR_WELCOMESCREEN ), TRUE, &pItem))
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxBoolItem), "BoolItem expected");
//STRIP001         aHelpOptions.SetWelcomeScreen( ((const SfxBoolItem *)pItem)->GetValue() );
//STRIP001     }
//STRIP001
//STRIP001  // WelcomeScreen
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_WELCOMESCREEN_RESET ), TRUE, &pItem))
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxBoolItem), "BoolItem expected");
//STRIP001      BOOL bReset = ((const SfxBoolItem *)pItem)->GetValue();
//STRIP001      if ( bReset )
//STRIP001      {
//STRIP001             DBG_ERROR( "Not implemented, may be EOL!" );
//STRIP001         }                                                   }
//STRIP001
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_HELP_STYLESHEET ), TRUE, &pItem))
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxStringItem), "StringItem expected");
//STRIP001         aHelpOptions.SetHelpStyleSheet( ((const SfxStringItem *)pItem)->GetValue() );
//STRIP001     }
//STRIP001
//STRIP001     // SaveRelINet
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_SAVEREL_INET), TRUE, &pItem))
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxBoolItem), "BoolItem expected");
//STRIP001         aSaveOptions.SetSaveRelINet(((const SfxBoolItem *)pItem)->GetValue());
//STRIP001     }
//STRIP001
//STRIP001  // SaveRelFSys
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_SAVEREL_FSYS), TRUE, &pItem))
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxBoolItem), "BoolItem expected");
//STRIP001         aSaveOptions.SetSaveRelFSys(((const SfxBoolItem *)pItem)->GetValue());
//STRIP001     }
//STRIP001
//STRIP001  // Undo-Count
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_ATTR_UNDO_COUNT), TRUE, &pItem))
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxUInt16Item), "UInt16Item expected");
//STRIP001         USHORT nUndoCount = ((const SfxUInt16Item*)pItem)->GetValue();
//STRIP001         aUndoOptions.SetUndoCount( nUndoCount );
//STRIP001
//STRIP001         // um alle Undo-Manager zu erwischen: "uber alle Frames iterieren
//STRIP001         for ( SfxViewFrame *pFrame = SfxViewFrame::GetFirst();
//STRIP001               pFrame;
//STRIP001               pFrame = SfxViewFrame::GetNext(*pFrame) )
//STRIP001         {
//STRIP001             // den Dispatcher des Frames rausholen
//STRIP001             SfxDispatcher *pDispat = pFrame->GetDispatcher();
//STRIP001             pDispat->Flush();
//STRIP001
//STRIP001             // "uber alle SfxShells auf dem Stack des Dispatchers iterieren
//STRIP001             USHORT nIdx = 0;
//STRIP001             for ( SfxShell *pSh = pDispat->GetShell(nIdx);
//STRIP001                   pSh;
//STRIP001                   ++nIdx, pSh = pDispat->GetShell(nIdx) )
//STRIP001             {
//STRIP001                 SfxUndoManager *pUndoMgr = pSh->GetUndoManager();
//STRIP001                 if ( pUndoMgr )
//STRIP001                     pUndoMgr->SetMaxUndoActionCount( nUndoCount );
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001  // Office autostart
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_ATTR_QUICKLAUNCHER), TRUE, &pItem))
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxBoolItem), "BoolItem expected");
//STRIP001         ShutdownIcon::SetAutostart( ( (const SfxBoolItem*)pItem )->GetValue() != FALSE );
//STRIP001     }
//STRIP001
//STRIP001  // StarBasic Enable
//STRIP001  if ( SFX_ITEM_SET == rSet.GetItemState(SID_BASIC_ENABLED, TRUE, &pItem))
//STRIP001     {
//STRIP001      DBG_ASSERT(pItem->ISA(SfxUInt16Item), "SfxInt16Item expected");
//STRIP001      aSecurityOptions.SetBasicMode( (EBasicSecurityMode)( (const SfxUInt16Item*)pItem )->GetValue() );
//STRIP001     }
//STRIP001
//STRIP001  // Execute PlugIns
//STRIP001  if ( SFX_ITEM_SET == rSet.GetItemState(SID_INET_EXE_PLUGIN, TRUE, &pItem))
//STRIP001     {
//STRIP001      DBG_ASSERT(pItem->ISA(SfxBoolItem), "SfxBoolItem expected");
//STRIP001         aSecurityOptions.SetExecutePlugins( ( (const SfxBoolItem *)pItem )->GetValue() );
//STRIP001      bResetSession = TRUE;
//STRIP001     }
//STRIP001
//STRIP001     if ( IsPlugin() )
//STRIP001     {
//STRIP001         sal_Int32 nMode = 0;
//STRIP001         String aServerName;
//STRIP001         String aPortNumber;
//STRIP001         if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_INET_PROXY_TYPE), TRUE, &pItem))
//STRIP001         {
//STRIP001             DBG_ASSERT( pItem->ISA(SfxUInt16Item), "UInt16Item expected" );
//STRIP001             nMode = ((const SfxUInt16Item*)pItem )->GetValue();
//STRIP001         }
//STRIP001
//STRIP001         if ( nMode == 2 )
//STRIP001         {
//STRIP001             if ( SFX_ITEM_SET == rSet.GetItemState( rPool.GetWhich( SID_INET_HTTP_PROXY_NAME ), TRUE, &pItem ) )
//STRIP001             {
//STRIP001                 DBG_ASSERT( pItem->ISA(SfxStringItem), "StringItem expected" );
//STRIP001                 aServerName = ((const SfxStringItem *)pItem)->GetValue();
//STRIP001             }
//STRIP001             if ( SFX_ITEM_SET == rSet.GetItemState( rPool.GetWhich( SID_INET_HTTP_PROXY_PORT ), TRUE, &pItem ) )
//STRIP001             {
//STRIP001                 DBG_ASSERT( pItem->ISA(SfxInt32Item), "Int32Item expected" );
//STRIP001                 aPortNumber = String::CreateFromInt32( ((const SfxInt32Item*)pItem )->GetValue() );
//STRIP001             }
//STRIP001
//STRIP001             if ( !aServerName.Len() || !aPortNumber.Len() )
//STRIP001                 nMode = 0;
//STRIP001         }
//STRIP001
//STRIP001         ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > xRemoteProxyConfig( ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance( DEFINE_CONST_OUSTRING("com.sun.star.comp.framework.LoginDialog")), ::com::sun::star::uno::UNO_QUERY );
//STRIP001         if( xRemoteProxyConfig.is() == sal_True )
//STRIP001         {
//STRIP001             ::com::sun::star::uno::Any aPropValue;
//STRIP001          if( nMode==0 )  aPropValue <<= DEFINE_CONST_OUSTRING("none");
//STRIP001          else
//STRIP001          if( nMode==1 )  aPropValue <<= DEFINE_CONST_OUSTRING("browser");
//STRIP001          else
//STRIP001          if( nMode==2 )  aPropValue <<= DEFINE_CONST_OUSTRING("custom");
//STRIP001
//STRIP001          xRemoteProxyConfig->setPropertyValue( DEFINE_CONST_OUSTRING("UseProxy"), aPropValue );
//STRIP001          if( nMode == 2 )
//STRIP001          {
//STRIP001              ::rtl::OUStringBuffer sProxyValue;
//STRIP001              sProxyValue.append     ( aServerName );
//STRIP001              sProxyValue.appendAscii( ":"         );
//STRIP001              sProxyValue.append     ( aPortNumber );
//STRIP001              aPropValue <<= sProxyValue.makeStringAndClear();
//STRIP001              xRemoteProxyConfig->setPropertyValue( DEFINE_CONST_OUSTRING("SecurityProxy"), aPropValue );
//STRIP001          }
//STRIP001          ::com::sun::star::uno::Reference< ::com::sun::star::util::XFlushable > xFlush( xRemoteProxyConfig, ::com::sun::star::uno::UNO_QUERY );
//STRIP001          if( xFlush.is() == sal_True )
//STRIP001              xFlush->flush();
//STRIP001      }
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_INET_PROXY_TYPE), TRUE, &pItem))
//STRIP001         {
//STRIP001             DBG_ASSERT( pItem->ISA(SfxUInt16Item), "UInt16Item expected" );
//STRIP001             aInetOptions.SetProxyType((SvtInetOptions::ProxyType)( (const SfxUInt16Item*)pItem )->GetValue());
//STRIP001             bResetSession = TRUE;
//STRIP001             bProxiesModified = TRUE;
//STRIP001         }
//STRIP001
//STRIP001         if ( SFX_ITEM_SET == rSet.GetItemState( rPool.GetWhich( SID_INET_HTTP_PROXY_NAME ), TRUE, &pItem ) )
//STRIP001         {
//STRIP001             DBG_ASSERT( pItem->ISA(SfxStringItem), "StringItem expected" );
//STRIP001             aInetOptions.SetProxyHttpName( ((const SfxStringItem *)pItem)->GetValue() );
//STRIP001             bResetSession = TRUE;
//STRIP001             bProxiesModified = TRUE;
//STRIP001         }
//STRIP001         if ( SFX_ITEM_SET == rSet.GetItemState( rPool.GetWhich( SID_INET_HTTP_PROXY_PORT ), TRUE, &pItem ) )
//STRIP001         {
//STRIP001             DBG_ASSERT( pItem->ISA(SfxInt32Item), "Int32Item expected" );
//STRIP001             aInetOptions.SetProxyHttpPort( ( (const SfxInt32Item*)pItem )->GetValue() );
//STRIP001             bResetSession = TRUE;
//STRIP001             bProxiesModified = TRUE;
//STRIP001         }
//STRIP001         if ( SFX_ITEM_SET == rSet.GetItemState( rPool.GetWhich( SID_INET_FTP_PROXY_NAME ), TRUE, &pItem ) )
//STRIP001         {
//STRIP001             DBG_ASSERT( pItem->ISA(SfxStringItem), "StringItem expected" );
//STRIP001             aInetOptions.SetProxyFtpName( ((const SfxStringItem *)pItem)->GetValue() );
//STRIP001             bResetSession = TRUE;
//STRIP001             bProxiesModified = TRUE;
//STRIP001         }
//STRIP001         if ( SFX_ITEM_SET == rSet.GetItemState( rPool.GetWhich( SID_INET_FTP_PROXY_PORT ), TRUE, &pItem ) )
//STRIP001         {
//STRIP001             DBG_ASSERT( pItem->ISA(SfxInt32Item), "Int32Item expected" );
//STRIP001             aInetOptions.SetProxyFtpPort( ( (const SfxInt32Item*)pItem )->GetValue() );
//STRIP001             bResetSession = TRUE;
//STRIP001             bProxiesModified = TRUE;
//STRIP001         }
//STRIP001 /*        if ( SFX_ITEM_SET == rSet.GetItemState( rPool.GetWhich( SID_INET_SOCKS_PROXY_NAME ), TRUE, &pItem ) )
//STRIP001         {
//STRIP001             DBG_ASSERT( pItem->ISA(SfxStringItem), "StringItem expected" );
//STRIP001             aInetOptions.SetProxySocksName( ((const SfxStringItem *)pItem)->GetValue() );
//STRIP001             bResetSession = TRUE;
//STRIP001             bProxiesModified = TRUE;
//STRIP001         }
//STRIP001         if ( SFX_ITEM_SET == rSet.GetItemState( rPool.GetWhich( SID_INET_SOCKS_PROXY_PORT ), TRUE, &pItem ) )
//STRIP001         {
//STRIP001             DBG_ASSERT( pItem->ISA(SfxInt32Item), "Int32Item expected" );
//STRIP001             aInetOptions.SetProxySocksPort( ( (const SfxInt32Item*)pItem )->GetValue() );
//STRIP001             bResetSession = TRUE;
//STRIP001             bProxiesModified = TRUE;
//STRIP001         }
//STRIP001         if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_INET_DNS_AUTO), TRUE, &pItem))
//STRIP001         {
//STRIP001             DBG_ASSERT(pItem->ISA(SfxBoolItem), "BoolItem expected");
//STRIP001             BOOL bIsAuto = ((const SfxBoolItem *)pItem)->GetValue();
//STRIP001             if( bIsAuto )
//STRIP001             {
//STRIP001                 aInetOptions.SetDnsIpAddress( String() );
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 String aDNS;
//STRIP001                 if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_INET_DNS_SERVER), TRUE, &pItem) )
//STRIP001                 {
//STRIP001                     DBG_ASSERT(pItem->ISA(SfxStringItem), "SfxStringItem expected");
//STRIP001                     aDNS = ((const SfxStringItem *)pItem)->GetValue();
//STRIP001                 }
//STRIP001                 aInetOptions.SetDnsIpAddress( aDNS );
//STRIP001             }
//STRIP001             bResetSession = TRUE;
//STRIP001         }*/
//STRIP001         if ( SFX_ITEM_SET == rSet.GetItemState(SID_INET_NOPROXY, TRUE, &pItem))
//STRIP001         {
//STRIP001             DBG_ASSERT(pItem->ISA(SfxStringItem), "StringItem expected");
//STRIP001             aInetOptions.SetProxyNoProxy(((const SfxStringItem *)pItem)->GetValue());
//STRIP001             bResetSession = TRUE;
//STRIP001             bProxiesModified = TRUE;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001  // Secure-Referers
//STRIP001  if ( SFX_ITEM_SET == rSet.GetItemState(SID_SECURE_URL, TRUE, &pItem))
//STRIP001     {
//STRIP001      DELETEZ(pAppData_Impl->pSecureURLs);
//STRIP001
//STRIP001      DBG_ASSERT(pItem->ISA(SfxStringListItem), "StringListItem expected");
//STRIP001      const List *pList = ((SfxStringListItem*)pItem)->GetList();
//STRIP001      sal_uInt32 nCount = pList->Count();
//STRIP001      ::com::sun::star::uno::Sequence< ::rtl::OUString > seqURLs(nCount);
//STRIP001      for( sal_uInt32 nPosition=0;nPosition<nCount;++nPosition)
//STRIP001      {
//STRIP001          seqURLs[nPosition] = *(const String*)(pList->GetObject(nPosition));
//STRIP001      }
//STRIP001      aSecurityOptions.SetSecureURLs( seqURLs );
//STRIP001     }
//STRIP001
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(SID_MACRO_WARNING, TRUE, &pItem))
//STRIP001     {
//STRIP001      DBG_ASSERT(pItem->ISA(SfxBoolItem), "SfxBoolItem expected");
//STRIP001         aSecurityOptions.SetWarningEnabled( ( (const SfxBoolItem *)pItem )->GetValue() );
//STRIP001     }
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(SID_MACRO_CONFIRMATION, TRUE, &pItem))
//STRIP001     {
//STRIP001      DBG_ASSERT(pItem->ISA(SfxBoolItem), "SfxBoolItem expected");
//STRIP001         aSecurityOptions.SetConfirmationEnabled( ( (const SfxBoolItem *)pItem )->GetValue() );
//STRIP001     }
//STRIP001
//STRIP001     // EnableMetafilePrint
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState( rPool.GetWhich( SID_ENABLE_METAFILEPRINT ), TRUE, &pItem ) )
//STRIP001     {
//STRIP001 #ifdef ENABLE_MISSINGKEYASSERTIONS//MUSTINI
//STRIP001      DBG_ASSERT(sal_False, "SfxApplication::SetOptions_Impl()\nsoffice.ini key \"MetafilPrint\" not supported any longer!\n");
//STRIP001 #endif
//STRIP001     }
//STRIP001
//STRIP001  // AutoSave starten oder anhalten
//STRIP001  UpdateAutoSave_Impl();
//STRIP001
//STRIP001  // INet Session neu aufsetzen
//STRIP001  if ( bResetSession )
//STRIP001  {
//STRIP001      try
//STRIP001      {
//STRIP001          SjApplet2::settingsChanged();
//STRIP001      }
//STRIP001      catch ( ... )
//STRIP001      {
//STRIP001          DBG_ERRORFILE( "SjApplet2::settingsChanged() throws an exception" );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // geaenderte Daten speichern
//STRIP001  aInetOptions.flush();
//STRIP001  SaveConfiguration();
//STRIP001 }

//--------------------------------------------------------------------

/*?*/ void SfxApplication::SetOptions(const SfxItemSet &rSet)
/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  SvtPathOptions aPathOptions;
//STRIP001
//STRIP001  // Daten werden in DocInfo und IniManager gespeichert
//STRIP001  SfxDocumentInfo *pDocInf = SfxObjectShell::Current()
//STRIP001                              ? &SfxObjectShell::Current()->GetDocInfo()
//STRIP001                              : 0;
//STRIP001     const SfxPoolItem *pItem = 0;
//STRIP001     SfxItemPool &rPool = GetPool();
//STRIP001
//STRIP001  SfxAllItemSet aSendSet( rSet );
//STRIP001
//STRIP001  // portable Grafiken
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_ATTR_INDEP_METAFILE), TRUE, &pItem))
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxBoolItem), "BoolItem expected");
//STRIP001      BOOL b = ((const SfxBoolItem *)pItem)->GetValue();
//STRIP001      if ( pDocInf )
//STRIP001          pDocInf->SetPortableGraphics(b);
//STRIP001     }
//STRIP001
//STRIP001  // Grafiken komprimiert speichern
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_OPT_SAVEGRAPHICSCOMPRESSED), TRUE, &pItem))
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxBoolItem), "BoolItem expected");
//STRIP001      BOOL b = ((const SfxBoolItem *)pItem)->GetValue();
//STRIP001      if ( pDocInf )
//STRIP001          pDocInf->SetSaveGraphicsCompressed(b);
//STRIP001     }
//STRIP001
//STRIP001  // Grafiken im Original speichern
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_OPT_SAVEORIGINALGRAPHICS), TRUE, &pItem))
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxBoolItem), "BoolItem expected");
//STRIP001      BOOL b = ((const SfxBoolItem *)pItem)->GetValue();
//STRIP001      if ( pDocInf )
//STRIP001          pDocInf->SetSaveOriginalGraphics(b);
//STRIP001     }
//STRIP001
//STRIP001  // PathName
//STRIP001     if ( SFX_ITEM_SET == rSet.GetItemState(rPool.GetWhich(SID_ATTR_PATHNAME), TRUE, &pItem))
//STRIP001     {
//STRIP001         DBG_ASSERT(pItem->ISA(SfxAllEnumItem), "AllEnumItem expected");
//STRIP001      const SfxAllEnumItem* pEnumItem = (const SfxAllEnumItem *)pItem;
//STRIP001      sal_uInt32 nCount = pEnumItem->GetValueCount();
//STRIP001      String aNoChangeStr( ' ' );
//STRIP001      for( sal_uInt32 nPath=0; nPath<nCount; ++nPath )
//STRIP001      {
//STRIP001          String sValue = pEnumItem->GetValueTextByPos((USHORT)nPath);
//STRIP001          if ( sValue != aNoChangeStr )
//STRIP001          {
//STRIP001              switch( nPath )
//STRIP001              {
//STRIP001                     case SvtPathOptions::PATH_ADDIN:
//STRIP001                     {
//STRIP001                         String aTmp;
//STRIP001                         if( ::utl::LocalFileHelper::ConvertURLToPhysicalName( sValue, aTmp ) )
//STRIP001                             aPathOptions.SetAddinPath( aTmp );
//STRIP001                         break;
//STRIP001                     }
//STRIP001
//STRIP001                  case SvtPathOptions::PATH_AUTOCORRECT:  aPathOptions.SetAutoCorrectPath( sValue );break;
//STRIP001                  case SvtPathOptions::PATH_AUTOTEXT:     aPathOptions.SetAutoTextPath( sValue );break;
//STRIP001                  case SvtPathOptions::PATH_BACKUP:       aPathOptions.SetBackupPath( sValue );break;
//STRIP001                  case SvtPathOptions::PATH_BASIC:        aPathOptions.SetBasicPath( sValue );break;
//STRIP001                  case SvtPathOptions::PATH_BITMAP:       aPathOptions.SetBitmapPath( sValue );break;
//STRIP001                  case SvtPathOptions::PATH_CONFIG:       aPathOptions.SetConfigPath( sValue );break;
//STRIP001                  case SvtPathOptions::PATH_DICTIONARY:   aPathOptions.SetDictionaryPath( sValue );break;
//STRIP001                  case SvtPathOptions::PATH_FAVORITES:    aPathOptions.SetFavoritesPath( sValue );break;
//STRIP001                     case SvtPathOptions::PATH_FILTER:
//STRIP001                     {
//STRIP001                         String aTmp;
//STRIP001                         if( ::utl::LocalFileHelper::ConvertURLToPhysicalName( sValue, aTmp ) )
//STRIP001                             aPathOptions.SetFilterPath( aTmp );
//STRIP001                         break;
//STRIP001                     }
//STRIP001                  case SvtPathOptions::PATH_GALLERY:      aPathOptions.SetGalleryPath( sValue );break;
//STRIP001                  case SvtPathOptions::PATH_GRAPHIC:      aPathOptions.SetGraphicPath( sValue );break;
//STRIP001                     case SvtPathOptions::PATH_HELP:
//STRIP001                     {
//STRIP001                         String aTmp;
//STRIP001                         if( ::utl::LocalFileHelper::ConvertURLToPhysicalName( sValue, aTmp ) )
//STRIP001                             aPathOptions.SetHelpPath( aTmp );
//STRIP001                         break;
//STRIP001                     }
//STRIP001
//STRIP001                  case SvtPathOptions::PATH_LINGUISTIC:   aPathOptions.SetLinguisticPath( sValue );break;
//STRIP001                     case SvtPathOptions::PATH_MODULE:
//STRIP001                     {
//STRIP001                         String aTmp;
//STRIP001                         if( ::utl::LocalFileHelper::ConvertURLToPhysicalName( sValue, aTmp ) )
//STRIP001                             aPathOptions.SetModulePath( aTmp );
//STRIP001                         break;
//STRIP001                     }
//STRIP001
//STRIP001                  case SvtPathOptions::PATH_PALETTE:      aPathOptions.SetPalettePath( sValue );break;
//STRIP001                     case SvtPathOptions::PATH_PLUGIN:
//STRIP001                     {
//STRIP001                         String aTmp;
//STRIP001                         if( ::utl::LocalFileHelper::ConvertURLToPhysicalName( sValue, aTmp ) )
//STRIP001                             aPathOptions.SetPluginPath( aTmp );
//STRIP001                         break;
//STRIP001                     }
//STRIP001
//STRIP001                     case SvtPathOptions::PATH_STORAGE:
//STRIP001                     {
//STRIP001                         String aTmp;
//STRIP001                         if( ::utl::LocalFileHelper::ConvertURLToPhysicalName( sValue, aTmp ) )
//STRIP001                             aPathOptions.SetStoragePath( aTmp );
//STRIP001                         break;
//STRIP001                     }
//STRIP001
//STRIP001                  case SvtPathOptions::PATH_TEMP:         aPathOptions.SetTempPath( sValue );break;
//STRIP001                  case SvtPathOptions::PATH_TEMPLATE:     aPathOptions.SetTemplatePath( sValue );break;
//STRIP001                  case SvtPathOptions::PATH_USERCONFIG:   aPathOptions.SetUserConfigPath( sValue );break;
//STRIP001                  case SvtPathOptions::PATH_USERDICTIONARY:aPathOptions.SetUserDictionaryPath( sValue );break;
//STRIP001                  case SvtPathOptions::PATH_WORK:         aPathOptions.SetWorkPath( sValue );break;
//STRIP001                  default: DBG_ERRORFILE("SfxApplication::SetOptions_Impl()\nInvalid path number found for set directories!");
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      aSendSet.ClearItem( rPool.GetWhich( SID_ATTR_PATHNAME ) );
//STRIP001     }
//STRIP001
//STRIP001  SetOptions_Impl( rSet );
//STRIP001
//STRIP001  // Undo-Count
//STRIP001  Broadcast( SfxItemSetHint( rSet ) );
/*?*/ }

//--------------------------------------------------------------------

//STRIP001 void SfxApplication::UpdateAutoSave_Impl()
//STRIP001 {
//STRIP001     pImp->pAutoSaveTimer->Stop();
//STRIP001
//STRIP001     // AutoSave soll ab jetzt neu anlaufen
//STRIP001     SvtSaveOptions aSaveOptions;
//STRIP001     if ( aSaveOptions.IsAutoSave() )
//STRIP001     {
//STRIP001         pImp->pAutoSaveTimer->SetTimeout( aSaveOptions.GetAutoSaveTime() * 60000 );
//STRIP001         pImp->pAutoSaveTimer->Start();
//STRIP001     }
//STRIP001 }

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
/*N*/     {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/         SaveAll_Impl( aSaveOptions.IsAutoSavePrompt(), TRUE );
//STRIP001 /*?*/        pImp->bAutoSaveNow = FALSE;
//STRIP001 /*?*/        pImp->pAutoSaveTimer->SetTimeout( aSaveOptions.GetAutoSaveTime() * 60000 );
//STRIP001 /*?*/        pImp->pAutoSaveTimer->Start();
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

//STRIP001 BOOL SfxApplication::SaveAll_Impl(BOOL bPrompt, BOOL bAutoSave)
//STRIP001 {
//STRIP001     BOOL bFunc = TRUE;
//STRIP001     short nRet;
//STRIP001
//STRIP001     for ( SfxObjectShell *pDoc = SfxObjectShell::GetFirst();
//STRIP001           pDoc;
//STRIP001           pDoc = SfxObjectShell::GetNext(*pDoc) )
//STRIP001     {
//STRIP001      if( SFX_CREATE_MODE_STANDARD == pDoc->GetCreateMode() &&
//STRIP001          SfxViewFrame::GetFirst(pDoc) &&
//STRIP001          !pDoc->IsInModalMode() &&
//STRIP001          !pDoc->HasModalViews() )
//STRIP001      {
//STRIP001          if ( pDoc->GetProgress() == 0 )
//STRIP001          {
//STRIP001              if ( !pDoc->IsModified() )
//STRIP001                  continue;
//STRIP001
//STRIP001              if ( bPrompt || (bAutoSave && !pDoc->HasName()) )
//STRIP001                  nRet = QuerySave_Impl( *pDoc, bAutoSave );
//STRIP001              else
//STRIP001                  nRet = RET_YES;
//STRIP001
//STRIP001              if ( nRet == RET_YES )
//STRIP001              {
//STRIP001                  SfxRequest aReq( SID_SAVEDOC, 0, pDoc->GetPool() );
//STRIP001                  const SfxPoolItem *pPoolItem = pDoc->ExecuteSlot( aReq );
//STRIP001                  if ( !pPoolItem || !pPoolItem->ISA(SfxBoolItem) ||
//STRIP001                      !( (const SfxBoolItem*) pPoolItem )->GetValue() )
//STRIP001                      bFunc = FALSE;
//STRIP001              }
//STRIP001              else if ( nRet == RET_CANCEL )
//STRIP001              {
//STRIP001                  bFunc = FALSE;
//STRIP001                  break;
//STRIP001              }
//STRIP001              else if ( nRet == RET_NO )
//STRIP001              {
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001     }
//STRIP001  pImp->aAutoSaveTime=Time();
//STRIP001
//STRIP001     return bFunc;
//STRIP001 }

//--------------------------------------------------------------------

/*N*/ SfxMacroConfig* SfxApplication::GetMacroConfig() const
/*N*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); return NULL; //STRIP001   return SfxMacroConfig::GetOrCreate();
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
/*?*/           {DBG_ASSERT(0, "STRIP");} //STRIP001 /*?*/         HandleConfigError_Impl( (sal_uInt16)pCfgMgr->GetErrorCode() );
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
