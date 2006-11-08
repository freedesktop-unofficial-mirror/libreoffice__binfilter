/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_appquit.cxx,v $
 *
 *  $Revision: 1.9 $
 *
 *  last change: $Author: kz $ $Date: 2006-11-08 11:50:47 $
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
#ifndef _BASMGR_HXX //autogen
#include <basic/basmgr.hxx>
#endif

#ifdef WIN
#define _TL_LANG_SPECIAL
#endif

#ifndef _MSGBOX_HXX //autogen
#include <vcl/msgbox.hxx>
#endif



#pragma hdrstop

#include "app.hrc"

#ifndef _COM_SUN_STAR_LANG_XTYPEPROVIDER_HPP_
#include <com/sun/star/lang/XTypeProvider.hpp>
#endif

#include "appdata.hxx"
#include "dispatch.hxx"
#include "plugobj.hxx"
#include "arrdecl.hxx"
#include "sfxresid.hxx"
#include "newhdl.hxx"
#include "accmgr.hxx"
#include "macrconf.hxx"
#include "mnumgr.hxx"
#include "templdlg.hxx"

#ifndef _SVTOOLS_IMGDEF_HXX
#include <svtools/imgdef.hxx>
#endif

#include "tbxconf.hxx"
#include "msgpool.hxx"
#include "frameobj.hxx"
#include "docfile.hxx"
#include "sfxtypes.hxx"
#include "appimp.hxx"
#include "sfxlocal.hrc"
#include "fcontnr.hxx"
#include "nochaos.hxx"
#include "doctempl.hxx"
#include "viewfrm.hxx"
#include "dlgcont.hxx"
#include "scriptcont.hxx"
#include <misccfg.hxx>
#include "docfac.hxx"
#include <basic/basicmanagerrepository.hxx>
namespace binfilter {

#ifndef PRODUCT
DECLARE_LIST( SfxFrameWindowFactoryArray_Impl, SfxFrameWindowFactory* )
SV_DECL_PTRARR(SfxInitLinkList, Link*, 2, 2)//STRIP008 ;
#endif

//===================================================================
/*
void SfxApplication::Quit()
{
    QueryExit_Impl();
}
*/
//--------------------------------------------------------------------
/*?*/ BOOL SfxApplication::QueryExit_Impl()

/*  [Beschreibung]

    Liefert FALSE, wenn entweder ein modaler Dialog offen ist, oder
    der Printer einer SfxViewShell einen laufenden Druckjob hat.

    [Anmerkung]

    Wenn diese aus StarView stammende virtuelle Methode vom Applikations-
    entwickler "uberladen wird, mu"s diese SfxApplication::QueryExit() rufen
    und falls diese FALSE zur"uckgibt, ebenfalls FALSE zur"uckgeben.
*/

/*?*/ {
/*?*/     SaveConfiguration();
/*?*/   BOOL bQuit = TRUE;

/*
    BOOL bPrinting = FALSE;
    for ( SfxViewShell *pViewSh = SfxViewShell::GetFirst();
          !bPrinting && pViewSh;
          pViewSh = SfxViewShell::GetNext(*pViewSh) )
    {
        SfxPrinter *pPrinter = pViewSh->GetPrinter();
        bPrinting = pPrinter && pPrinter->IsPrinting();
    }

    if ( bPrinting )
    {
        // Benutzer fragen, ob abgebrochen werden soll
        if ( RET_OK == QueryBox( 0, SfxResId( MSG_ISPRINTING_QUERYABORT ) ).Execute() )
        {
            // alle Jobs canceln
            for ( SfxViewShell *pViewSh = SfxViewShell::GetFirst();
                  !bPrinting && pViewSh;
                  pViewSh = SfxViewShell::GetNext(*pViewSh) )
            {
                SfxPrinter *pPrinter = pViewSh->GetPrinter();
                if ( pPrinter && pPrinter->IsPrinting() )
                    pPrinter->AbortJob();
            }

            // da das Canceln asynchron ist, Quit erstmal wieder verlassen
            GetDispatcher_Impl()->Execute( SID_QUITAPP, SFX_CALLMODE_ASYNCHRON );
            DBG_TRACE( "QueryExit => FALSE (printing)" );
            return FALSE;
        }
    }
*/
    // alles canceln was zu canceln ist
/*?*/   GetCancelManager()->Cancel(TRUE);
/*?*/
/*?*/   // direkte Benutzung is beendet
//STRIP007  if ( pAppData_Impl->bDirectAliveCount )
//STRIP007  {
//STRIP007      SvFactory::DecAliveCount();
//STRIP007      pAppData_Impl->bDirectAliveCount = FALSE;
//STRIP007  }
/*?*/
/*
    SfxObjectShell *pLastDocSh = SfxObjectShell::GetFirst();
    if ( bQuit )
    {
        // Jetzt zur Sicherheit auch hidden Frames abr"aumen
        SfxViewFrame::CloseHiddenFrames_Impl();
        pLastDocSh = SfxObjectShell::GetFirst();
    }
*/
    // will trotzdem noch jemand, den man nicht abschiessen kann, die App haben?
/*?*/     if ( !bQuit )
/*?*/   {
/*?*/       // nicht wirklich beenden, nur minimieren
/*?*/       pAppData_Impl->bOLEResize = TRUE;
/*?*/         InfoBox aInfoBox( NULL, SfxResId(MSG_CANT_QUIT) );
/*?*/       aInfoBox.Execute();
/*?*/       DBG_TRACE( "QueryExit => FALSE (in use)" );
/*?*/       return FALSE;
/*?*/   }
/*?*/
/*?*/   return TRUE;
/*?*/ }

//-------------------------------------------------------------------------

/*?*/ void SfxApplication::Deinitialize()
/*?*/ {
/*?*/     if ( bDowning )
/*?*/         return;
/*?*/
/*?*/     // Falls man nochmal beim Runterfahren in ein Reschedule l"auft
/*?*/     pAppData_Impl->EndListening( *this );
/*?*/     if ( pAppData_Impl->pCancelMgr )
/*?*/         pAppData_Impl->EndListening( *pAppData_Impl->pCancelMgr );
/*?*/
/*
    // Falls noch mal zwischendurch eine Task ( BasicIDE! ) angelegt wurde ...
    do
    {
        SfxObjectShell* pFirst = SfxObjectShell::GetFirst();
        if ( pFirst )
            pFirst->DoClose();
        else
            break;
    }
    while ( sal_True );
*/
/*?*/   //!Wait();
/*?*/   StarBASIC::Stop();
/*?*/
/*?*/   // ggf. BASIC speichern
        BasicManager* pBasMgr = ::basic::BasicManagerRepository::getApplicationBasicManager( false );
        if ( pBasMgr && pBasMgr->IsModified() )
            SaveBasicManager();
/*?*/
/*?*/   SaveBasicContainer();
/*?*/   SaveDialogContainer();
/*?*/
/*?*/   bDowning = TRUE; // wegen Timer aus DecAliveCount und QueryExit
/*?*/
/*?*/     DELETEZ( pAppData_Impl->pTemplates );
/*?*/
//STRIP007  SvFactory::ClearDemandObjects();
/*?*/   DELETEZ(pImp->pTemplateDlg);
/*?*/   SetViewFrame(0);
/*?*/   bDowning = FALSE;
/*?*/   DBG_ASSERT( !SfxViewFrame::GetFirst(),
/*?*/               "existing SfxViewFrame after Execute" );
/*?*/   DBG_ASSERT( !SfxObjectShell::GetFirst(),
/*?*/               "existing SfxObjectShell after Execute" );
/*?*/   pAppDispat->Pop( *this, SFX_SHELL_POP_UNTIL );
/*?*/   pAppDispat->Flush();
/*?*/   bDowning = TRUE;
/*?*/   pAppDispat->DoDeactivate_Impl( TRUE );
/*?*/
/*?*/   // call derived application-exit
/*?*/   bInExit = TRUE;
/*?*/   Exit();
/*?*/
/*?*/     // Controller u."a. freigeben
/*?*/     // dabei sollten auch restliche Komponenten ( Beamer! ) verschwinden
/*?*/   DELETEZ(pMenuMgr);
/*?*/   DELETEZ(pAcceleratorMgr);
/*?*/   SfxObjectFactory::ClearAll_Impl();
/*?*/   pBasMgr = NULL;
/*?*/   if( pImp->pBasicLibContainer )
/*?*/       pImp->pBasicLibContainer->release();
/*?*/   if( pImp->pDialogLibContainer )
/*?*/       pImp->pDialogLibContainer->release();
/*?*/
//STRIP007  SvFactory::ClearDemandObjects();
/*?*/   bInExit = FALSE;
/*?*/
/*?*/   DBG_ASSERT( pViewFrame == 0, "active foreign ViewFrame" );
/*?*/
/*?*/   delete[] pInterfaces, pInterfaces = 0;
/*?*/   DELETEZ(pImageMgr);
/*?*/
/*?*/   // free administration managers
/*?*/   DELETEZ(pImp->pAutoSaveTimer);
/*?*/   DELETEZ(pAppDispat);
/*?*/   DELETEZ(pImp->pSfxResManager);
/*?*/
/*?*/   // ab hier d"urfen keine SvObjects mehr existieren
/*?*/   DELETEX(pAppData_Impl->pMatcher);
/*?*/   DELETEX(pAppData_Impl->pSfxFrameObjectFactoryPtr);
/*?*/   DELETEX(pAppData_Impl->pSfxPluginObjectFactoryPtr);
/*?*/
/*?*/   delete pAppData_Impl->pLabelResMgr;
/*?*/
/*?*/ #ifndef PRODUCT
/*?*/   DELETEX(pSlotPool);
/*?*/   DELETEX(pAppData_Impl->pEventConfig);
/*?*/     DELETEX(pAppData_Impl->pMiscConfig);
/*?*/   SfxMacroConfig::Release_Impl();
/*?*/   DELETEX(pAppData_Impl->pVerbs);
/*?*/   DELETEX(pAppData_Impl->pFactArr);
/*?*/   DELETEX(pAppData_Impl->pInitLinkList);
/*?*/ #endif
/*?*/
/*?*/ #ifndef PRODUCT
/*?*/     DELETEX(pImp->pTbxCtrlFac);
/*?*/     DELETEX(pImp->pStbCtrlFac);
/*?*/     DELETEX(pImp->pMenuCtrlFac);
/*?*/     DELETEX(pImp->pEventHdl);
/*?*/     SfxNewHdl::Delete();
/*?*/     DELETEX(pImp->pAutoSaveTimer);
/*?*/     DELETEX(pImp->pViewFrames);
/*?*/     DELETEX(pImp->pViewShells);
/*?*/     DELETEX(pImp->pObjShells);
/*?*/ #endif
/*?*/
/*?*/   NoChaos::ReleaseItemPool();
/*?*/   pAppData_Impl->pPool = NULL;
/*?*/ }
}
