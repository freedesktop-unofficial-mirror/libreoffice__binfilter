/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#include "progress.hxx"

#include <com/sun/star/task/XStatusIndicatorFactory.hpp>

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <bf_svtools/eitem.hxx>

#include "appdata.hxx"
#include "app.hxx"
#include "request.hxx"
#include "sfxtypes.hxx"
#include "docfile.hxx"
#include "sfxsids.hrc"
#include "objsh.hxx"
#include "appuno.hxx"

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

    SfxProgress*            pActiveProgress;
    SfxObjectShellRef       xObjSh;

                            SfxProgress_Impl( const String& );
};

//========================================================================

#define TIMEOUT_PROGRESS         5L /* 10th s */
#define MAXPERCENT_PROGRESS     33

#define TIMEOUT_RESCHEDULE      10L /* 10th s */
#define MAXPERCENT_RESCHEDULE   50

#define Progress

#define aTypeLibInfo aProgressTypeLibImpl

//========================================================================
inline ULONG Get10ThSec()
{
#if defined (MSC) && defined (WIN)
    ULONG n10Ticks = 10 * (ULONG)GetTickCount();
#else
    ULONG n10Ticks = 10 * (ULONG)clock();
#endif

    return n10Ticks / CLOCKS_PER_SEC;
}

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

/*N*/ : pImp( new SfxProgress_Impl( rText ) )
/*N*/ , nVal(0)
/*N*/ , bSuspended(TRUE)
/*N*/ {
/*N*/   pImp->bRunning = TRUE;
/*N*/   pImp->bAllowRescheduling = Application::IsInExecute();;
/*N*/
/*N*/
/*N*/   pImp->xObjSh = pObjSh;
/*N*/   pImp->aText = rText;
/*N*/   pImp->nMax = nRange;
/*N*/   pImp->bLocked = FALSE;
/*N*/   pImp->bWaitMode = bWait;
/*N*/   pImp->nCreate = Get10ThSec();
/*N*/   pImp->nNextReschedule = pImp->nCreate;
/*N*/   DBG( DbgOutf( "SfxProgress: created for '%s' at %luds",
/*N*/                 rText.GetBuffer(), pImp->nCreate ) );
/*N*/   pImp->bAllDocs = bAll;
/*N*/
/*N*/   pImp->pActiveProgress = GetActiveProgress( pObjSh );
/*N*/   if ( pObjSh )
/*N*/       pObjSh->SetProgress_Impl(this);
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
/*N*/ }

// -----------------------------------------------------------------------
BOOL SfxProgress::SetState
(
    ULONG   nNewVal,    /* neuer Wert f"ur die Fortschritts-Anzeige */
    ULONG   nNewRange   /* neuer Maximalwert, 0 f"ur Beibehaltung des alten */
)
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
/*N*/   nVal = nNewVal;
/*N*/
/*N*/   // neuer Range?
/*N*/   if ( nNewRange && nNewRange != pImp->nMax )
/*N*/   {
/*?*/       DBG( DbgOutf( "SfxProgress: range changed from %lu to %lu",
/*?*/                     pImp->nMax, nNewRange ) );
/*?*/       pImp->nMax = nNewRange;
/*N*/   }
/*N*/
/*N*/     if ( !pImp->xStatusInd.is() )
/*N*/   {
/*N*/         // get the active ViewFrame of the document this progress is working on
/*N*/         // if it doesn't work on a document, take the current ViewFrame
/*N*/         SfxObjectShell* pObjSh = pImp->xObjSh;
/*N*/             {
/*N*/                 // don't show status indicator for hidden documents
/*N*/                 SfxMedium* pMedium = pObjSh->GetMedium();
/*N*/                 SFX_ITEMSET_ARG( pMedium->GetItemSet(), pHiddenItem, SfxBoolItem, SID_HIDDEN, FALSE );
/*N*/                 if ( !pHiddenItem || !pHiddenItem->GetValue() )
/*N*/                 {
/*N*/                     // not in a view, perhaps it's just loading
/*N*/                     {
/*N*/                         SFX_ITEMSET_ARG( pMedium->GetItemSet(), pIndicatorItem, SfxUnoAnyItem, SID_PROGRESS_STATUSBAR_CONTROL, FALSE );
/*N*/                         Reference< XStatusIndicator > xInd;
/*N*/                         if ( pIndicatorItem && (pIndicatorItem->GetValue()>>=xInd) )
/*?*/                             pImp->xStatusInd = xInd;
/*N*/                     }
/*N*/                 }
/*N*/             }
/*N*/
/*N*/         if ( pImp->xStatusInd.is() )
/*N*/         {
/*?*/             pImp->xStatusInd->start( pImp->aText, pImp->nMax );
/*N*/         }
/*N*/   }
/*N*/
/*N*/   // schon ein StbManager?
/*N*/     if ( pImp->xStatusInd.is() )
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
/*N*/         if ( pImp->xStatusInd.is() )
/*N*/         {
/*?*/             pImp->xStatusInd->start( pImp->aText, pImp->nMax );
/*?*/             pImp->xStatusInd->setValue( nVal );
/*N*/         }
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
/*N*/         if ( pImp->xStatusInd.is() )
/*N*/         {
/*?*/             pImp->xStatusInd->reset();
/*N*/         }
/*N*/
/*N*/   }
/*N*/ }

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


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
