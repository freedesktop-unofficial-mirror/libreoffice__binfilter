/*************************************************************************
 *
 *  $RCSfile: sfx2_appdata.cxx,v $
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
#ifndef _CACHESTR_HXX //autogen
#include <tools/cachestr.hxx>
#endif
#ifndef _SV_CONFIG_HXX //autogen
#include <vcl/config.hxx>
#endif
#ifndef _INETSTRM_HXX //autogen
#include <svtools/inetstrm.hxx>
#endif
#ifndef _SFXSTRITEM_HXX //autogen
#include <svtools/stritem.hxx>
#endif

#define _SVSTDARR_STRINGS
#include <svtools/svstdarr.hxx>
#include <vos/mutex.hxx>

#include <vcl/menu.hxx>

#ifndef _LOGINERR_HXX
#include <svtools/loginerr.hxx>
#endif
#ifndef _SV_MSGBOX_HXX
#include <vcl/msgbox.hxx>
#endif
#ifndef _DATETIMEITEM_HXX //autogen
#include <svtools/dateitem.hxx>
#endif
#ifndef _SV_MENU_HXX
#include <vcl/menu.hxx>
#endif
#ifndef _SV_WRKWIN_HXX
#include <vcl/wrkwin.hxx>
#endif
#include "comphelper/processfactory.hxx"

#include "viewfrm.hxx"
#include "appdata.hxx"
#include "dispatch.hxx"
#include "event.hxx"
#include "sfxtypes.hxx"
#include "sfxdir.hxx"
#include "doctempl.hxx"
#include "dataurl.hxx"
#include "arrdecl.hxx"
#include "docfac.hxx"
#include "docfile.hxx"
#include "request.hxx"
#include "referers.hxx"
#include "app.hrc"
#include "sfxresid.hxx"
#include "objshimp.hxx"
#include "appuno.hxx"
#include "imestatuswindow.hxx"

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {

/*N*/ SfxAppData_Impl::SfxAppData_Impl( SfxApplication* pApp ) :
/*N*/       bServer( false ),
/*N*/       pProgress(0),
/*N*/       pPool(0),
/*N*/       pFactArr(0),
/*N*/       pDdeService( 0 ),
/*N*/       pDocTopics( 0 ),
/*N*/       pEventConfig(0),
/*N*/       nAsynchronCalls(0),
/*N*/       pVerbs(0),
/*N*/       nBasicCallLevel(0),
/*N*/       nRescheduleLocks(0),
/*N*/       nInReschedule(0),
/*N*/       pInitLinkList(0),
/*N*/       pMatcher( 0 ),
/*N*/       pSfxPlugInObjectShellFactory( 0 ),
/*N*/       pDefFocusWin( 0 ),
/*N*/       pSfxFrameObjectFactoryPtr( 0 ),
/*N*/       pCancelMgr( 0 ),
/*N*/       nDocModalMode(0),
/*N*/       pDisabledSlotList( 0 ),
/*N*/       pFilterIni( 0 ),
/*N*/       pSfxPluginObjectFactoryPtr( 0 ),
/*N*/       pTemplateCommon( 0 ),
/*N*/       pLabelResMgr( 0 ),
/*N*/       pTopFrames( new SfxFrameArr_Impl ),
/*N*/       pSecureURLs(0),
/*N*/       nAutoTabPageId(0),
/*N*/       nExecutingSID( 0 ),
/*N*/       pAppDispatch(NULL),
/*N*/       pTriggerTopic(0),
/*N*/       pDdeService2(0),
/*N*/       pMiscConfig(0),
/*N*/       pThisDocument(0),
/*N*/         bPlugged(sal_False),
/*N*/       bOLEResize(sal_False),
//STRIP007      bDirectAliveCount(sal_False),
/*N*/       bInQuit(sal_False),
/*N*/       bInvalidateOnUnlock(sal_False),
/*N*/       bBean( sal_False ),
/*N*/       bMinimized( sal_False ),
/*N*/       bInvisible( sal_False ),
/*N*/       bInException( sal_False ),
/*N*/         nAppEvent( 0 ),
/*N*/         pTemplates( 0 ),
/*N*/         pSaveOptions( 0 ),
/*N*/         pUndoOptions( 0 ),
/*N*/         pHelpOptions( 0 ),
/*N*/         m_xImeStatusWindow(new sfx2::appl::ImeStatusWindow(
/*N*/                                *pApp, ::legacy_binfilters::getLegacyProcessServiceFactory()))
/*N*/ {
/*N*/   StartListening( *pApp );
/*N*/ }

/*N*/ SfxAppData_Impl::~SfxAppData_Impl()
/*N*/ {
/*N*/ //#ifdef DBG_UTIL
/*N*/     DeInitDDE();
/*N*/   delete pTopFrames;
/*N*/   delete pCancelMgr;
/*N*/   delete pFilterIni;
/*N*/   delete pSecureURLs;
/*N*/ //#endif
/*N*/ }

/*N*/ IMPL_STATIC_LINK( SfxAppData_Impl, CreateDocumentTemplates, void*, EMPTYARG)
/*N*/ {
/*N*/     pThis->GetDocumentTemplates();
/*N*/   return 0;
/*N*/ }

/*N*/ void SfxAppData_Impl::UpdateApplicationSettings( sal_Bool bDontHide )
/*N*/ {
/*N*/   AllSettings aAllSet = Application::GetSettings();
/*N*/   StyleSettings aStyleSet = aAllSet.GetStyleSettings();
/*N*/   sal_uInt32 nStyleOptions = aStyleSet.GetOptions();
/*N*/   if ( bDontHide )
/*N*/       nStyleOptions &= ~STYLE_OPTION_HIDEDISABLED;
/*N*/   else
/*?*/       nStyleOptions |= STYLE_OPTION_HIDEDISABLED;
/*N*/   aStyleSet.SetOptions( nStyleOptions );
/*N*/   aAllSet.SetStyleSettings( aStyleSet );
/*N*/   Application::SetSettings( aAllSet );
/*N*/ }

/*N*/ SfxDocumentTemplates* SfxAppData_Impl::GetDocumentTemplates()
/*N*/ {
/*N*/     if ( !pTemplates )
/*N*/         pTemplates = new SfxDocumentTemplates;
/*N*/     else
/*?*/         {DBG_ASSERT(0, "STRIP");} //STRIP001 pTemplates->ReInitFromComponent();
/*N*/     return pTemplates;
/*N*/ }

/*N*/ void SfxAppData_Impl::Notify( SfxBroadcaster &rBC, const SfxHint &rHint )
/*N*/ {
/*N*/   SfxSimpleHint* pHint = PTR_CAST( SfxSimpleHint, &rHint );
/*N*/     if( pHint && pHint->GetId() == SFX_HINT_CANCELLABLE )
/*N*/   {
/*
        // vom Cancel-Manager
        for ( SfxViewFrame *pFrame = SfxViewFrame::GetFirst();
              pFrame;
              pFrame = SfxViewFrame::GetNext(*pFrame) )
        {
            SfxBindings &rBind = pFrame->GetBindings();
            rBind.Invalidate( SID_BROWSE_STOP );
            if ( !rBind.IsInRegistrations() )
                rBind.Update( SID_BROWSE_STOP );
            rBind.Invalidate( SID_BROWSE_STOP );
        }
 */
/*N*/   }
/*N*/ }

}
