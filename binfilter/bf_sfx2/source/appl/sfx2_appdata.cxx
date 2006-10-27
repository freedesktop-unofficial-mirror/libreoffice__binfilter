/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_appdata.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 18:53:48 $
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
#ifndef _CONFIG_HXX
#include <tools/config.hxx>
#endif

#define _SVSTDARR_STRINGS



#include "appdata.hxx"
#include "dispatch.hxx"
#include "doctempl.hxx"
#include "arrdecl.hxx"
#include "docfile.hxx"
#include "app.hrc"
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
/*?*/         {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 pTemplates->ReInitFromComponent();
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
