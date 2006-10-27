/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_progress.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 19:05:48 $
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

#include "progress.hxx"

#ifndef _COM_SUN_STAR_TASK_XSTATUSINDICATORFACTORY_HPP_
#include <com/sun/star/task/XStatusIndicatorFactory.hpp>
#endif

#pragma hdrstop

#include <svtools/eitem.hxx>

#include "appdata.hxx"
#include "request.hxx"
#include "ipfrm.hxx"
#include "dispatch.hxx"
#include "sfxtypes.hxx"
#include "docfile.hxx"
#include "workwin.hxx"
#include "bastyp.hrc"

#include <time.h>
namespace binfilter {


using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::task;




struct SfxProgress_Impl : public SfxCancellable
{
    Reference < XStatusIndicator > xStatusInd;
    String                  aText, aStateText;
    ULONG                   nMax;
    clock_t                 nCreate;
    clock_t                 nNextReschedule;
    BOOL                    bLocked, bAllDocs;
    BOOL                    bWaitMode;
    BOOL                    bAllowRescheduling;
    BOOL                    bRunning;
    BOOL                    bIsStatusText;

    SfxProgress*            pActiveProgress;
    SfxObjectShellRef       xObjSh;
    SfxStatusBarManager*    pMgr;
    SfxWorkWindow*          pWorkWin;
    SfxViewFrame*           pView;

                            SfxProgress_Impl( const String& );
    void                    Enable_Impl( BOOL );

};

//========================================================================

#define TIMEOUT_PROGRESS         5L /* 10th s */
#define MAXPERCENT_PROGRESS     33

#define TIMEOUT_RESCHEDULE      10L /* 10th s */
#define MAXPERCENT_RESCHEDULE   50

#define Progress

#define aTypeLibInfo aProgressTypeLibImpl

//========================================================================
#if (_MSC_VER < 1300)
inline ULONG Get10ThSec()
{
#if defined (MSC) && defined (WIN)
    ULONG n10Ticks = 10 * (ULONG)GetTickCount();
#else
    ULONG n10Ticks = 10 * (ULONG)clock();
#endif

    return n10Ticks / CLOCKS_PER_SEC;
}
#else
extern ULONG Get10ThSec();
#endif
// -----------------------------------------------------------------------

/*N*/ void SfxProgress_Impl::Enable_Impl( BOOL bEnable )
/*N*/ {
/*N*/     SfxObjectShell* pDoc = bAllDocs ? NULL : (SfxObjectShell*) xObjSh;
/*N*/   SfxViewFrame *pFrame= SfxViewFrame::GetFirst(pDoc);
/*N*/   while ( pFrame )
/*N*/   {
/*N*/       pFrame->Enable(bEnable);
/*N*/       if ( pDoc )
/*N*/           pFrame->GetDispatcher()->Lock( !bEnable );
/*N*/       pFrame = SfxViewFrame::GetNext(*pFrame, pDoc);
/*N*/   }
/*N*/
/*N*/     if ( pView )
/*N*/     {
/*N*/         pView->Enable( bEnable );
/*N*/         pView->GetDispatcher()->Lock( !bEnable );
/*N*/     }
/*N*/
/*N*/   if ( pDoc )
/*N*/   {
/*N*/       SfxFrame* pFrm = pDoc->GetMedium()->GetLoadTargetFrame();
/*N*/       pFrame = pFrm ? pFrm->GetCurrentViewFrame() : NULL;
/*N*/       if ( pFrame )
/*N*/       {
/*?*/           pFrame->Enable( bEnable );
/*?*/           pFrame->GetDispatcher()->Lock( !bEnable );
/*N*/       }
/*N*/   }
/*N*/   else
/*?*/       {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 SFX_APP()->LockDispatcher( !bEnable );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxProgress_Impl::SfxProgress_Impl( const String &rTitle )
/*N*/     :   SfxCancellable( SFX_APP()->GetCancelManager(), rTitle ),
/*N*/       pActiveProgress( 0 )
/*N*/ {
/*N*/     SFX_APP()->GetCancelManager()->RemoveCancellable(this);
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxProgress::SfxProgress
/*N*/ (
/*N*/   SfxObjectShell* pObjSh, /* SfxObjectShell, an der die Aktion ausgef"uhrt
                               wird. Kann NULL sein, dann wird die Applikation
                                verwendet */
/*N*/
/*N*/   const String&   rText,  /* Text, der in der Statuszeile vor den Statusmonitor
                               erscheint */
/*N*/
/*N*/   ULONG           nRange, /* Maximalwert des Bereiches */
/*N*/
/*N*/   BOOL            bAll    /* alle Dokumente oder nur das Dokument des ViewFrames
                               disablen (FALSE) */
/*N*/   ,BOOL           bWait   /* initial den Wait-Pointer aktivieren (TRUE) */
/*N*/ )

/*  [Beschreibung]

    Der Konstruktor der Klasse SfxProgress schaltet den als Parameter
    "ubergebenen SfxObjectShell und SfxViewFrames, welche dieses Dokument
    anzeigen in einen Progress-Mode. D.h. solange eine dieser SfxViewFrame
    Instanzen aktiv ist, ist der dazugeh"orige SfxDispatcher und das
    dazugeh"orige Window disabled. In der Statuszeile wird ein Balken zur
    Fortschritts-Anzeige angezeigt.
*/

/*N*/ : nVal(0),
/*N*/   bSuspended(TRUE),
/*N*/   pImp( new SfxProgress_Impl( rText ) )
/*N*/ {
/*N*/   pImp->bRunning = TRUE;
/*N*/   pImp->bAllowRescheduling = Application::IsInExecute();;
/*N*/
/*N*/     if ( pObjSh )
/*N*/     {
/*N*/         for( SfxViewFrame* pFrame = SfxViewFrame::GetFirst( pObjSh ); pFrame; pFrame = SfxViewFrame::GetNext( *pFrame, pObjSh ) )
/*N*/         {
/*N*/             pFrame->GetCancelManager()->InsertCancellable( pImp );
/*
            SfxBindings& rBindings = pFrame->GetBindings();
            rBindings.Invalidate( SID_BROWSE_STOP );
            if ( !rBindings.IsInRegistrations() )
                rBindings.Update( SID_BROWSE_STOP );
            rBindings.Invalidate( SID_BROWSE_STOP );
 */
/*N*/         }
/*N*/     }
/*N*/
/*N*/   pImp->xObjSh = pObjSh;
/*N*/   pImp->aText = rText;
/*N*/   pImp->nMax = nRange;
/*N*/   pImp->bLocked = FALSE;
/*N*/   pImp->bWaitMode = bWait;
/*N*/   pImp->bIsStatusText = FALSE;
/*N*/   pImp->nCreate = Get10ThSec();
/*N*/   pImp->nNextReschedule = pImp->nCreate;
/*N*/   DBG( DbgOutf( "SfxProgress: created for '%s' at %luds",
/*N*/                 rText.GetBuffer(), pImp->nCreate ) );
/*N*/   pImp->bAllDocs = bAll;
/*N*/   pImp->pMgr = 0;
/*N*/   pImp->pWorkWin = 0;
/*N*/     pImp->pView = 0;
/*N*/
/*N*/   pImp->pActiveProgress = GetActiveProgress( pObjSh );
/*N*/   if ( pObjSh )
/*N*/       pObjSh->SetProgress_Impl(this);
/*N*/   else if( !pImp->pActiveProgress )
/*?*/         {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 SFX_APP()->SetProgress_Impl(this);
/*N*/   Resume();
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxProgress::~SfxProgress()

/*  [Beschreibung]

    Der Destruktor der Klasse SfxProgress restauriert den alten Zustand;
    die Dokumente werden wieder freigeschaltet und die Statuszeile zeigt
    wieder Items an.
*/

/*N*/ {
/*N*/   Stop();
/*N*/     if ( pImp->xStatusInd.is() )
/*?*/         pImp->xStatusInd->end();
/*N*/
/*N*/   if( pImp->bIsStatusText == TRUE )
/*?*/       GetpApp()->HideStatusText( );
/*N*/     SfxObjectShell* pDoc = pImp->xObjSh;
/*N*/     if ( pDoc )
/*N*/     {
/*N*/         for( SfxViewFrame* pFrame = SfxViewFrame::GetFirst( pDoc ); pFrame; pFrame = SfxViewFrame::GetNext( *pFrame, pDoc ) )
/*N*/             pFrame->GetCancelManager()->RemoveCancellable( pImp );//Invalidate( SID_BROWSE_STOP );
/*N*/     }
/*N*/     else
/*?*/         SFX_APP()->Invalidate( SID_BROWSE_STOP );
/*N*/   delete pImp;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ void SfxProgress::Stop()

/*  [Beschreibung]

    Vorzeitiges Beenden des <SfxProgress>.
*/

/*N*/ {
/*N*/     if( pImp->pActiveProgress )
/*N*/     {
/*?*/         if ( pImp->xObjSh.Is() && pImp->xObjSh->GetProgress() == this )
/*?*/             pImp->xObjSh->SetProgress_Impl(0);
/*?*/         return;
/*N*/     }
/*N*/
/*N*/   if ( !pImp->bRunning )
/*N*/       return;
/*N*/   pImp->bRunning = FALSE;
/*N*/   DBG( DbgOutf( "SfxProgress: destroyed at %luds", Get10ThSec() ) );
/*N*/
/*N*/   Suspend();
/*N*/   if ( pImp->xObjSh.Is() )
/*N*/       pImp->xObjSh->SetProgress_Impl(0);
/*N*/   else
/*?*/         {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 SFX_APP()->SetProgress_Impl(0);
/*N*/   if ( pImp->bLocked )
/*N*/         pImp->Enable_Impl(TRUE);
/*N*/ }

// -----------------------------------------------------------------------

/*?*/ void SfxProgress::SetText
/*?*/ (
/*?*/   const String&   rText   /*  neuer Text */
/*?*/ )

/*  [Beschreibung]

    "Andert den Text, der links neben dem Fortschritts-Balken
    angezeigt wird.
*/

/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }

// -----------------------------------------------------------------------


// -----------------------------------------------------------------------
/*
IMPL_STATIC_LINK( SfxProgress, SetStateHdl, PlugInLoadStatus*, pStatus )
{
    INetRequest* pReq = 0;
    const INetHint *pHint = PTR_CAST( INetHint, pStatus->pHint );
    pReq = PTR_CAST( INetRequest, pStatus->pBC );

    String aString;
    if( pReq )
        aString = SfxMedium::GetStatusString( pHint->GetId(), pReq, pHint );
    if( aString.Len() )
    {
        GetpApp()->ShowStatusText( aString );
        if( pThis )
            pThis->pImp->bIsStatusText = TRUE;
    }
    return 0;
}
*/

// -----------------------------------------------------------------------

// muss in AppDaten
static ULONG nLastTime = 0;


// -----------------------------------------------------------------------

/*N*/ IMPL_STATIC_LINK( SfxProgress, DefaultBindingProgress, SvProgressArg*, pArg )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   return 0;
/*N*/ }

// -----------------------------------------------------------------------


// -----------------------------------------------------------------------

/*N*/ BOOL SfxProgress::SetState
/*N*/ (
/*N*/   ULONG   nNewVal,    /* neuer Wert f"ur die Fortschritts-Anzeige */
/*N*/
/*N*/   ULONG   nNewRange   /* neuer Maximalwert, 0 f"ur Beibehaltung des alten */
/*N*/ )
/*  [Beschreibung]

    Setzen des aktuellen Status; nach einem zeitlichen Versatz
    wird Reschedule aufgerufen.


    [R"uckgabewert]

    BOOL                TRUE
                        Fortfahren mit der Aktion

                        FALSE
                        Abbrechen der Aktion
*/

/*N*/ {
/*N*/   // wurde via Stop-Button angehalten?
/*N*/   if ( pImp->IsCancelled() )
/*N*/       return FALSE;
/*N*/
/*N*/   if( pImp->pActiveProgress ) return TRUE;
/*N*/
/*N*/   // neuen Wert "ubernehmen
/*N*/   BOOL bOver=FALSE;
/*N*/   nVal = nNewVal;
/*N*/
/*N*/   // neuer Range?
/*N*/   if ( nNewRange && nNewRange != pImp->nMax )
/*N*/   {
/*?*/       DBG( DbgOutf( "SfxProgress: range changed from %lu to %lu",
/*?*/                     pImp->nMax, nNewRange ) );
/*?*/       pImp->nMax = nNewRange;
/*?*/       bOver = TRUE;
/*N*/   }
/*N*/
/*N*/     if ( !pImp->pMgr && !pImp->xStatusInd.is() )
/*N*/   {
/*N*/         // get the active ViewFrame of the document this progress is working on
/*N*/         // if it doesn't work on a document, take the current ViewFrame
/*N*/         SfxObjectShell* pObjSh = pImp->xObjSh;
/*N*/         pImp->pView = SfxViewFrame::Current();
/*N*/         DBG_ASSERT( pImp->pView || pObjSh, "Can't make progress bar!");
/*N*/         if ( pObjSh && ( !pImp->pView || pObjSh != pImp->pView->GetObjectShell() ) )
/*N*/         {
/*N*/             // current document does not belong to current ViewFrame; take it's first visible ViewFrame
/*N*/             SfxViewFrame* pDocView = SfxViewFrame::GetFirst( pObjSh );
/*N*/             if ( pDocView )
/*N*/                 pImp->pView = pDocView;
/*N*/             else
/*N*/             {
/*N*/                 // don't show status indicator for hidden documents
/*N*/                 SfxMedium* pMedium = pObjSh->GetMedium();
/*N*/                 SFX_ITEMSET_ARG( pMedium->GetItemSet(), pHiddenItem, SfxBoolItem, SID_HIDDEN, FALSE );
/*N*/                 if ( !pHiddenItem || !pHiddenItem->GetValue() )
/*N*/                 {
/*N*/                     // not in a view, perhaps it's just loading
/*N*/                     SfxFrame* pFrame = pMedium->GetLoadTargetFrame();
/*N*/                     if ( pFrame && pFrame->GetCurrentViewFrame() )
/*N*/                     {
/*N*/                         // recycling frame
/*?*/                         pImp->pView = pFrame->GetCurrentViewFrame();
/*N*/                     }
/*N*/                     else
/*N*/                     {
/*N*/                         SFX_ITEMSET_ARG( pMedium->GetItemSet(), pIndicatorItem, SfxUnoAnyItem, SID_PROGRESS_STATUSBAR_CONTROL, FALSE );
/*N*/                         Reference< XStatusIndicator > xInd;
/*N*/                         if ( pIndicatorItem && (pIndicatorItem->GetValue()>>=xInd) )
/*?*/                             pImp->xStatusInd = xInd;
/*N*/                     }
/*N*/                 }
/*N*/             }
/*N*/         }
/*N*/
/*N*/         if ( pImp->xStatusInd.is() )
/*N*/         {
/*?*/             pImp->xStatusInd->start( pImp->aText, pImp->nMax );
/*?*/             pImp->pView = NULL;
/*N*/         }
/*N*/         else if ( pImp->pView )
/*N*/         {
/*N*/             ULONG nTime = Get10ThSec();
/*N*/             ULONG nTimeDiff = nTime - pImp->nCreate;
/*N*/             ULONG nPercent = pImp->nMax ? nNewVal * 100 / pImp->nMax : 0;
/*N*/             DBG( DbgOutf( "SfxProgress: SetState invisible at %luds (%luds/%luds), %ld%%/%d%%",
/*N*/                         nTime, nTimeDiff, TIMEOUT_PROGRESS,
/*N*/                         nPercent, MAXPERCENT_PROGRESS ) );
/*N*/             if ( nTimeDiff > TIMEOUT_PROGRESS && nPercent <= MAXPERCENT_PROGRESS )
/*N*/             {
/*N*/                 pImp->pWorkWin = SFX_APP()->GetWorkWindow_Impl( pImp->pView );
/*N*/                 if( pImp->pWorkWin )
/*N*/                 {
/*N*/                     pImp->pWorkWin->SetTempStatusBar_Impl( TRUE );
/*N*/                     pImp->pMgr = pImp->pWorkWin->GetStatusBarManager_Impl();
/*N*/                 }
/*N*/
/*N*/                 DBG( DbgOutf( "SfxProgress: visible" ) );
/*N*/             }
/*N*/         }
/*N*/   }
/*N*/
/*N*/   // schon ein StbManager?
/*N*/   if ( pImp->pMgr )
/*N*/   {
/*N*/ //        if ( ( !pImp->xObjSh.Is() || &pImp->xObjSh == SfxObjectShell::Current() ) )
/*N*/       {
/*N*/           // Rescheduling noch nicht aktiv?
/*N*/           if ( !pImp->bLocked && pImp->bAllowRescheduling )
/*N*/           {
/*N*/               ULONG nTime = Get10ThSec();
/*N*/               ULONG nTimeDiff = nTime - pImp->nCreate;
/*N*/               ULONG nPercent = pImp->nMax ? nNewVal * 100 / pImp->nMax : 0;
/*N*/               DBG( DbgOutf( "SfxProgress: SetState unlocked at %luds (%luds/%luds), %ld%%/%d%%",
/*N*/                             nTime, nTimeDiff, TIMEOUT_RESCHEDULE,
/*N*/                             nPercent, MAXPERCENT_RESCHEDULE ) );
/*N*/               // Zeitpunkt zum verz"ogerten Rescheduling erreicht?
/*N*/               if ( nTimeDiff > TIMEOUT_RESCHEDULE && nPercent <= MAXPERCENT_RESCHEDULE )
/*N*/                   Lock();
/*N*/           }
/*N*/
/*N*/           if ( !bSuspended )
/*N*/           {
/*N*/               // reiner Text-Progress?
/*N*/               if ( !pImp->nMax )
/*?*/                   GetpApp()->ShowStatusText( pImp->aStateText );
/*N*/               else
/*N*/               {
/*N*/                   // Progress-Fortschritt anzeigen
/*N*/                   if ( bOver )
/*?*/                       pImp->pMgr->SetProgressMaxValue( pImp->nMax );
/*N*/                   if ( !pImp->pMgr->IsProgressMode() )
/*N*/                       pImp->pMgr->StartProgressMode( pImp->aText, pImp->nMax );
/*N*/                   pImp->pMgr->SetProgressState(nNewVal);
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/
/*N*/       Reschedule();
/*N*/   }
/*N*/     else if ( pImp->xStatusInd.is() )
/*N*/     {
/*?*/         pImp->xStatusInd->setValue( nNewVal );
/*N*/     }
/*N*/
/*N*/   return TRUE;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ void SfxProgress::Resume()

/*  [Beschreibung]

    Nimmt die Anzeige des Status nach einer Unterbrechung wieder auf.

    [Querverweise]
    <SfxProgress::Suspend()>
*/

/*N*/ {
/*N*/   if( pImp->pActiveProgress ) return;
/*N*/   if ( bSuspended )
/*N*/   {
/*N*/       DBG( DbgOutf( "SfxProgress: resumed" ) );
/*N*/       if ( pImp->pMgr && pImp->nMax )
/*N*/       {
/*?*/           pImp->pMgr->StartProgressMode( pImp->aText, pImp->nMax );
/*?*/           pImp->pMgr->SetProgressState( nVal );
/*N*/       }
/*N*/         else if ( pImp->xStatusInd.is() )
/*N*/         {
/*?*/             pImp->xStatusInd->start( pImp->aText, pImp->nMax );
/*?*/             pImp->xStatusInd->setValue( nVal );
/*N*/         }
/*N*/
/*N*/       if ( pImp->bWaitMode )
/*N*/       {
/*N*/           if ( pImp->xObjSh.Is() && !pImp->bAllDocs )
/*N*/           {
/*N*/               for ( SfxViewFrame *pFrame = SfxViewFrame::GetFirst(pImp->xObjSh);
/*N*/                       pFrame;
/*N*/                       pFrame = SfxViewFrame::GetNext( *pFrame, pImp->xObjSh ) )
/*N*/                   pFrame->GetWindow().EnterWait();
/*N*/               SfxFrame* pFrm = pImp->xObjSh->GetMedium()->GetLoadTargetFrame();
/*N*/               if ( pFrm )
/*N*/                   pFrm->GetWindow().EnterWait();
/*N*/           }
/*N*/ //(mba)/task
/*
            else if ( Application::GetAppWindow() )
                Application::GetAppWindow()->EnterWait();
 */
/*N*/       }
/*N*/
/*N*/       SfxBindings *pBindings = 0;
/*N*/       if ( pImp->xObjSh )
/*N*/       {
/*N*/           SfxViewFrame *pFrame = SfxViewFrame::GetFirst(pImp->xObjSh);
/*N*/             if ( pFrame )
/*N*/                 pFrame->GetBindings().ENTERREGISTRATIONS();
/*N*/       }
/*N*/
/*N*/       bSuspended = FALSE;
/*N*/   }
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ void SfxProgress::Suspend()

/*  [Beschreibung]

    Unterbricht die Anzeige des Status

    [Querverweise]
    <SfxProgress::Resume()>
*/

/*N*/ {
/*N*/   if( pImp->pActiveProgress ) return;
/*N*/   if ( !bSuspended )
/*N*/   {
/*N*/       DBG( DbgOutf( "SfxProgress: suspended" ) );
/*N*/       bSuspended = TRUE;
/*N*/       if ( pImp->pMgr )
/*N*/       {
/*N*/           if ( pImp->pMgr->IsProgressMode() )
/*N*/               pImp->pMgr->EndProgressMode();
/*N*/           pImp->pMgr->ShowItems();
/*N*/             pImp->pWorkWin->SetTempStatusBar_Impl( FALSE );
/*N*/       }
/*N*/         else if ( pImp->xStatusInd.is() )
/*N*/         {
/*?*/             pImp->xStatusInd->reset();
/*N*/         }
/*N*/
/*N*/       if ( pImp->xObjSh.Is() && !pImp->bAllDocs )
/*N*/       {
/*N*/           for ( SfxViewFrame *pFrame =
/*N*/                   SfxViewFrame::GetFirst(pImp->xObjSh);
/*N*/                   pFrame;
/*N*/                   pFrame = SfxViewFrame::GetNext( *pFrame, pImp->xObjSh ) )
/*N*/               pFrame->GetWindow().LeaveWait();
/*N*/               SfxFrame* pFrm = pImp->xObjSh->GetMedium()->GetLoadTargetFrame();
/*N*/               if ( pFrm )
/*N*/                   pFrm->GetWindow().LeaveWait();
/*N*/       }
/*N*/ //(mba)/task
/*
        else if ( Application::GetAppWindow() )
            Application::GetAppWindow()->LeaveWait();
*/
/*N*/       SfxBindings *pBindings = 0;
/*N*/       if ( pImp->xObjSh.Is() )
/*N*/       {
/*N*/           SfxViewFrame *pFrame = SfxViewFrame::GetFirst(pImp->xObjSh);
/*N*/             if ( pFrame )
/*N*/                 pFrame->GetBindings().LEAVEREGISTRATIONS();
/*N*/       }
/*N*/   }
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ void SfxProgress::Lock()
/*N*/ {
/*N*/   if( pImp->pActiveProgress ) return;
/*N*/   // kein Reschedule bei Embedded-Objekten,
/*N*/   // da wir gegen das OLE Protokoll wehrlos sind
/*N*/   if ( !pImp->xObjSh.Is() )
/*N*/   {
/*?*/       for ( SfxObjectShell *pDocSh = SfxObjectShell::GetFirst();
/*?*/             pDocSh;
/*?*/             pDocSh = SfxObjectShell::GetNext(*pDocSh) )
/*?*/       {
/*?*/           SfxObjectCreateMode eMode = pDocSh->GetCreateMode();
/*?*/           if ( ( eMode == SFX_CREATE_MODE_EMBEDDED ) ||
/*?*/                ( eMode == SFX_CREATE_MODE_PREVIEW ) )
/*?*/           {
/*?*/               DBG( DbgOutf( "SfxProgress: not locked because EMBEDDED/PREVIEW found" ) );
/*?*/               pImp->bAllowRescheduling = FALSE;
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       SfxObjectCreateMode eMode = pImp->xObjSh->GetCreateMode();
/*N*/       if ( ( eMode == SFX_CREATE_MODE_EMBEDDED ) ||
/*N*/            ( eMode == SFX_CREATE_MODE_PREVIEW ) )
/*N*/       {
/*N*/           DBG( DbgOutf( "SfxProgress: not locked because ObjectShell is EMBEDDED/PREVIEW" ) );
/*?*/           pImp->bAllowRescheduling = FALSE;
/*N*/       }
/*N*/   }
/*N*/
/*N*/     pImp->Enable_Impl( FALSE );
/*N*/
/*N*/   DBG( DbgOutf( "SfxProgress: locked" ) );
/*N*/   pImp->bLocked = TRUE;
/*N*/ }

// -----------------------------------------------------------------------


// -----------------------------------------------------------------------

/*N*/ void SfxProgress::Reschedule()

/*  [Beschreibung]

    Reschedule von au"sen rufbar

*/

/*N*/ {
/*N*/   SFX_STACK(SfxProgress::Reschedule);
/*N*/
/*N*/   if( pImp->pActiveProgress ) return;
/*N*/     SfxApplication* pApp = SFX_APP();
/*N*/     if ( pImp->bLocked && 0 == pApp->Get_Impl()->nRescheduleLocks )
/*N*/   {
/*N*/         DBG_ASSERTWARNING( pApp->IsInAsynchronCall_Impl(),
/*N*/                           "Reschedule in synchron-call-stack" );
/*N*/
/*N*/         SfxAppData_Impl *pAppData = pApp->Get_Impl();
/*N*/       ++pAppData->nInReschedule;
/*N*/       Application::Reschedule();
/*N*/       --pAppData->nInReschedule;
/*N*/   }
/*N*/ }

// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------

/*N*/ SfxProgress* SfxProgress::GetActiveProgress
/*N*/ (
/*N*/   SfxObjectShell* pDocSh    /*  <SfxObjectShell>, die nach einem laufenden
                                    <SfxProgress> gefragt werden soll, oder
                                    0, wenn ein f"ur die gesamte Applikation
                                    laufender SfxProgress erfragt werden soll.
                                    Der Pointer braucht nur zum Zeitpunkt des
                                    Aufrufs g"ultig zu sein. */
/*N*/ )
/*N*/
/*N*/ /*    [Beschreibung]

    Mit dieser Methode kann erfragt werden, ob und welcher <SfxProgress>-
    f"ur eine bestimmte Instanz von SfxObjectShell oder gar die gesamte
    Applikation zur Zeit aktiv ist. Dies kann z.B. zum Abfangen von
    Time-Out-Events etc. verwendet werden.

    Anstelle eines Pointer auf den SfxProgress der SfxObjectShell wird
    ggf. der auf den SfxProgress der Applikation geliefert, mit der
    Abfrage 'SfxProgress::GetActiveProgress(pMyDocSh)' wird also
    insofern vorhanden der SfxProgress von 'pMyDocSh' geliefert,
    sonst der SfxProgress der Applikation bzw. ein 0-Pointer.


    [Anmerkung]

    "auft kein SfxProgress an der Applikation und ebenfalls keiner an
    der angegebenen SfxObjectShell, dann wird immer 0 zur"uckgeliefert,
    auch wenn an einer anderen SfxObjectShell ein SfxProgress l"uft.


    [Querverweise]

    <SfxApplication::GetProgress()const>
    <SfxObjectShell::GetProgress()const>
*/
/*N*/
/*N*/ {
/*N*/   SfxProgress *pProgress = 0;
/*N*/   if ( pDocSh )
/*N*/       pProgress = pDocSh->GetProgress();
/*N*/   if ( !pProgress )
/*N*/       pProgress = SFX_APP()->GetProgress();
/*N*/   return pProgress;
/*N*/ }

// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------

/*N*/ FASTBOOL SfxProgress::StatusBarManagerGone_Impl
/*N*/ (
/*N*/   SfxStatusBarManager *pStb   // dieser <SfxStatusBarManager> wird zerst"ort
/*N*/ )

/*  [Beschreibung]

    Interne Methode zum Benachrichtigen des SfxProgress, da\s der angegebene
    SfxStatusBarManger zerst"ort wird. Damit der Progress ihn loslassen
    kann.
*/

/*N*/ {
/*N*/   if ( pImp->pMgr != pStb )
/*N*/       return FALSE;
/*N*/
/*N*/   DBG( DbgOutf( "SfxProgress: StatusBarManager gone" ) );
/*N*/   pImp->pMgr = 0;
/*N*/   return TRUE;
/*N*/ }

}
