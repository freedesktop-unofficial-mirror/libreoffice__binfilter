/*************************************************************************
 *
 *  $RCSfile: sfx2_progress.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:38:23 $
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

#include "progress.hxx"

#ifndef _COM_SUN_STAR_UNO_REFERENCE_HXX_
#include <com/sun/star/uno/Reference.hxx>
#endif
#ifndef _COM_SUN_STAR_TASK_XSTATUSINDICATORFACTORY_HPP_
#include <com/sun/star/task/XStatusIndicatorFactory.hpp>
#endif

#ifndef _SBX_HXX //autogen
#include <svtools/sbx.hxx>
#endif
#pragma hdrstop

#include <so3/transbnd.hxx>             // SvProgressArg
#include <svtools/eitem.hxx>

#include "appdata.hxx"
#include "request.hxx"
#include "frame.hxx"
#include "viewfrm.hxx"
#include "ipfrm.hxx"
#include "viewsh.hxx"
#include "objsh.hxx"
#include "app.hxx"
#include "stbmgr.hxx"
#include "dispatch.hxx"
#include "sfxtypes.hxx"
#include "docfile.hxx"
#include "workwin.hxx"
#include "sfxresid.hxx"
#include "bastyp.hrc"

#include <time.h>
namespace binfilter {
#include "sfxslots.hxx"


using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::task;

//STRIP001 void AddNumber_Impl( String& aNumber, sal_uInt32 nArg )
//STRIP001 {
//STRIP001  if ( nArg >= 10240 )
//STRIP001  {
//STRIP001      aNumber += String::CreateFromInt32( (sal_uInt16)( ( nArg + 512 ) / 1024 ) );
//STRIP001      aNumber += ' ';
//STRIP001      aNumber += SfxResId( STR_KB );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      aNumber += String::CreateFromInt32( nArg );
//STRIP001      aNumber += ' ';
//STRIP001      aNumber += SfxResId( STR_BYTES );
//STRIP001  }
//STRIP001 }

//STRIP001 String GetStatusString( const SvProgressArg* pArg )
//STRIP001 {
//STRIP001  String aString;
//STRIP001  StringList_Impl aSL( SfxResId( RID_DLSTATUS2 ), (USHORT)pArg->eStatus );
//STRIP001  USHORT nTotal = 0;
//STRIP001
//STRIP001  if ( pArg->eStatus == SVBINDSTATUS_ENDDOWNLOADDATA && nTotal <= 1 )
//STRIP001      return aString;
//STRIP001
//STRIP001  if( aSL )
//STRIP001  {
//STRIP001      INetURLObject aObj( pArg->rStatus );
//STRIP001      aString = aSL.GetString();
//STRIP001      aString.SearchAndReplaceAscii( "$(HOST)", aObj.GetHost() );
//STRIP001      String aTarget = aObj.GetFull();
//STRIP001      if( aTarget.Len() <= 1 && pArg->eStatus != SVBINDSTATUS_CONNECTING )
//STRIP001          aTarget = aObj.GetHost();
//STRIP001      if( pArg->nMax )
//STRIP001      {
//STRIP001          aTarget += DEFINE_CONST_UNICODE( " (" );
//STRIP001          AddNumber_Impl( aTarget, pArg->nMax );
//STRIP001          aTarget += ')';
//STRIP001      }
//STRIP001
//STRIP001      aString.SearchAndReplaceAscii( "$(TARGET)",aTarget );
//STRIP001      String aNumber;
//STRIP001      AddNumber_Impl( aNumber, pArg->nProgress );
//STRIP001      if( pArg->nRate )
//STRIP001      {
//STRIP001          aNumber+= DEFINE_CONST_UNICODE( " (" );
//STRIP001          AddNumber_Impl( aNumber, (ULONG)pArg->nRate );
//STRIP001          aNumber+= DEFINE_CONST_UNICODE( "/s)" );
//STRIP001      }
//STRIP001      if( pArg->nMax && pArg->nProgress && pArg->nMax != pArg->nProgress )
//STRIP001      {
//STRIP001          aNumber += DEFINE_CONST_UNICODE( " [" );
//STRIP001          float aPerc = pArg->nProgress / (float)pArg->nMax;
//STRIP001          aNumber += String::CreateFromInt32( (USHORT)(aPerc * 100) );
//STRIP001          aNumber += DEFINE_CONST_UNICODE( "%]" );
//STRIP001      }
//STRIP001      aString.SearchAndReplaceAscii( "$(BYTE)", aNumber );
//STRIP001  }
//STRIP001  return aString;
//STRIP001 }


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
/*?*/       {DBG_ASSERT(0, "STRIP");} //STRIP001 SFX_APP()->LockDispatcher( !bEnable );
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
/*?*/         {DBG_ASSERT(0, "STRIP");} //STRIP001 SFX_APP()->SetProgress_Impl(this);
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
/*?*/         {DBG_ASSERT(0, "STRIP"); }//STRIP001 SFX_APP()->SetProgress_Impl(0);
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

/*?*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if( pImp->pActiveProgress ) return;
//STRIP001  if ( pImp->pMgr && pImp->pMgr->IsProgressMode() )
//STRIP001  {
//STRIP001      pImp->pMgr->EndProgressMode();
//STRIP001      pImp->aText = rText;
//STRIP001      pImp->pMgr->StartProgressMode( pImp->aText, pImp->nMax );
//STRIP001  }
//STRIP001     else if ( pImp->xStatusInd.is() )
//STRIP001     {
//STRIP001         pImp->xStatusInd->reset();
//STRIP001         pImp->xStatusInd->start( pImp->aText, pImp->nMax );
//STRIP001     }
/*?*/ }

// -----------------------------------------------------------------------

//STRIP001 const String& SfxProgress::GetStateText_Impl() const
//STRIP001 {
//STRIP001  return pImp->aStateText;
//STRIP001 }

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

//STRIP001 long TimeOut_Impl( void* pThis, void* pArgV )
//STRIP001 {
//STRIP001  Timer *pArg = (Timer*)pArgV;
//STRIP001  if( Time::GetSystemTicks() - nLastTime > 3000 )
//STRIP001  {
//STRIP001      GetpApp()->HideStatusText();
//STRIP001      nLastTime = 0;
//STRIP001      delete pArg;
//STRIP001  }
//STRIP001  else pArg->Start();
//STRIP001  return 0;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ IMPL_STATIC_LINK( SfxProgress, DefaultBindingProgress, SvProgressArg*, pArg )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if( !nLastTime )
//STRIP001  {
//STRIP001      Timer *pTimer = new Timer();
//STRIP001      pTimer->SetTimeout( 3000 );
//STRIP001      pTimer->SetTimeoutHdl( Link( 0, TimeOut_Impl ) );
//STRIP001      pTimer->Start();
//STRIP001  }
//STRIP001  if( Time::GetSystemTicks( ) - nLastTime > 100 )
//STRIP001  {
//STRIP001      nLastTime = Time::GetSystemTicks();
//STRIP001         String aString = GetStatusString( pArg );
//STRIP001      if( aString.Len() )
//STRIP001          GetpApp()->ShowStatusText( aString );
//STRIP001  }
/*N*/   return 0;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 BOOL SfxProgress::SetStateText
//STRIP001 (
//STRIP001  ULONG           nNewVal,    /* neuer Wert f"ur die Fortschritts-Anzeige */
//STRIP001  const String&   rNewVal,    /* Status als Text */
//STRIP001  ULONG           nNewRange   /* neuer Maximalwert, 0 f"ur Beibehaltung des alten */
//STRIP001 )
//STRIP001
//STRIP001 {
//STRIP001  pImp->aStateText = rNewVal;
//STRIP001  return SetState( nNewVal, nNewRange );
//STRIP001 }

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

//STRIP001 void SfxProgress::UnLock()
//STRIP001 {
//STRIP001  if( pImp->pActiveProgress ) return;
//STRIP001  if ( !pImp->bLocked )
//STRIP001      return;
//STRIP001
//STRIP001  DBG( DbgOutf( "SfxProgress: unlocked" ) );
//STRIP001  pImp->bLocked = FALSE;
//STRIP001     pImp->Enable_Impl(TRUE);
//STRIP001 }

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

//STRIP001 void SfxProgress::SetWaitMode
//STRIP001 (
//STRIP001  BOOL    bWait       /*  TRUE
//STRIP001                          Wartecursor wird verwendet
//STRIP001
//STRIP001                          FALSE
//STRIP001                          Es wird kein Wartecursor verwendet */
//STRIP001 )
//STRIP001
//STRIP001 /*   [Beschreibung]
//STRIP001
//STRIP001  Wartecursor-Modus umschalten.
//STRIP001
//STRIP001 */
//STRIP001
//STRIP001 {
//STRIP001  if( pImp->pActiveProgress ) return;
//STRIP001  if ( !bSuspended && pImp->bWaitMode != bWait )
//STRIP001  {
//STRIP001      if ( bWait )
//STRIP001      {
//STRIP001          if ( pImp->xObjSh.Is() && !pImp->bAllDocs )
//STRIP001          {
//STRIP001              for ( SfxViewFrame *pFrame =
//STRIP001                      SfxViewFrame::GetFirst(pImp->xObjSh);
//STRIP001                      pFrame;
//STRIP001                      pFrame = SfxViewFrame::GetNext( *pFrame, pImp->xObjSh ) )
//STRIP001                  pFrame->GetWindow().EnterWait();
//STRIP001              SfxFrame* pFrm = pImp->xObjSh->GetMedium()->GetLoadTargetFrame();
//STRIP001              if ( pFrm )
//STRIP001                  pFrm->GetWindow().EnterWait();
//STRIP001          }
//STRIP001 //(mba)/task
//STRIP001 /*
//STRIP001          else if ( Application::GetAppWindow() )
//STRIP001              Application::GetAppWindow()->EnterWait();
//STRIP001  */
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if ( pImp->xObjSh.Is() && !pImp->bAllDocs )
//STRIP001          {
//STRIP001              for ( SfxViewFrame *pFrame =
//STRIP001                      SfxViewFrame::GetFirst(pImp->xObjSh);
//STRIP001                      pFrame;
//STRIP001                      pFrame = SfxViewFrame::GetNext( *pFrame, pImp->xObjSh ) )
//STRIP001                  pFrame->GetWindow().LeaveWait();
//STRIP001              SfxFrame* pFrm = pImp->xObjSh->GetMedium()->GetLoadTargetFrame();
//STRIP001              if ( pFrm )
//STRIP001                  pFrm->GetWindow().LeaveWait();
//STRIP001          }
//STRIP001 //(mba)/task
//STRIP001             /*
//STRIP001
//STRIP001          else if ( Application::GetAppWindow() )
//STRIP001              Application::GetAppWindow()->LeaveWait();
//STRIP001              */
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  pImp->bWaitMode = bWait;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 BOOL SfxProgress::GetWaitMode() const
//STRIP001
//STRIP001 /*   [Beschreibung]
//STRIP001
//STRIP001  Wartecursor-Modus abfragen.
//STRIP001
//STRIP001 */
//STRIP001
//STRIP001 {
//STRIP001  return pImp->bWaitMode;
//STRIP001 }

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

//STRIP001 void SfxProgress::EnterLock()
//STRIP001 {
//STRIP001  SFX_APP()->Get_Impl()->nRescheduleLocks++;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 void SfxProgress::LeaveLock()
//STRIP001 {
//STRIP001  SfxAppData_Impl *pImp = SFX_APP()->Get_Impl();
//STRIP001  DBG_ASSERT( 0 != pImp->nRescheduleLocks, "SFxProgress::LeaveLock but no locks" )
//STRIP001  pImp->nRescheduleLocks--;
//STRIP001 }

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
