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

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <vcl/svapp.hxx>

#include "chartlis.hxx"
#include "document.hxx"
#include <tools/debug.hxx>
namespace binfilter {

using namespace ::com::sun::star;


//2do: DocOption TimeOut?
#define SC_CHARTTIMEOUT 1000        // eine Sekunde keine Aenderung/KeyEvent


// ====================================================================

/*N*/ class ScChartUnoData
/*N*/ {
/*N*/   uno::Reference< chart::XChartDataChangeEventListener >  xListener;
/*N*/   uno::Reference< chart::XChartData >                     xSource;
/*N*/
/*N*/ public:
/*N*/           ScChartUnoData( const uno::Reference< chart::XChartDataChangeEventListener >& rL,
/*N*/                           const uno::Reference< chart::XChartData >& rS ) :
/*N*/                   xListener( rL ), xSource( rS ) {}
/*N*/           ~ScChartUnoData() {}
/*N*/
/*N*/   const uno::Reference< chart::XChartDataChangeEventListener >& GetListener() const   { return xListener; }
/*N*/   const uno::Reference< chart::XChartData >& GetSource() const                        { return xSource; }
/*N*/ };


// === ScChartListener ================================================

/*N*/ ScChartListener::ScChartListener( const String& rName, ScDocument* pDocP,
/*N*/       const ScRange& rRange ) :
/*N*/   StrData( rName ),
/*N*/   SfxListener(),
/*N*/   pUnoData( NULL ),
/*N*/   pDoc( pDocP ),
/*N*/   bUsed( FALSE ),
/*N*/   bDirty( FALSE ),
/*N*/   bSeriesRangesScheduled( FALSE )
/*N*/ {
/*N*/   SetRangeList( rRange );
/*N*/ }

/*N*/ ScChartListener::ScChartListener( const String& rName, ScDocument* pDocP,
/*N*/       const ScRangeListRef& rRangeList ) :
/*N*/   StrData( rName ),
/*N*/   SfxListener(),
/*N*/   aRangeListRef( rRangeList ),
/*N*/   pUnoData( NULL ),
/*N*/   pDoc( pDocP ),
/*N*/   bUsed( FALSE ),
/*N*/   bDirty( FALSE ),
/*N*/   bSeriesRangesScheduled( FALSE )
/*N*/ {
/*N*/ }

/*N*/ ScChartListener::ScChartListener( const ScChartListener& r ) :
/*N*/       StrData( r ),
/*N*/       SfxListener(),
/*N*/       pUnoData( NULL ),
/*N*/       pDoc( r.pDoc ),
/*N*/       bUsed( FALSE ),
/*N*/       bDirty( r.bDirty ),
/*N*/       bSeriesRangesScheduled( r.bSeriesRangesScheduled )
/*N*/ {
/*N*/   if ( r.pUnoData )
/*N*/       pUnoData = new ScChartUnoData( *r.pUnoData );
/*N*/   if ( r.aRangeListRef.Is() )
/*N*/       aRangeListRef = new ScRangeList( *r.aRangeListRef );
/*N*/ }

/*N*/ ScChartListener::~ScChartListener()
/*N*/ {
/*N*/   if ( GetBroadcasterCount() )
/*N*/       EndListeningTo();
/*N*/   delete pUnoData;
/*N*/ }

/*N*/ void ScChartListener::SetUno(
/*N*/       const uno::Reference< chart::XChartDataChangeEventListener >& rListener,
/*N*/       const uno::Reference< chart::XChartData >& rSource )
/*N*/ {
/*N*/   delete pUnoData;
/*N*/   pUnoData = new ScChartUnoData( rListener, rSource );
/*N*/ }

/*N*/ uno::Reference< chart::XChartDataChangeEventListener > ScChartListener::GetUnoListener() const
/*N*/ {
/*N*/   if ( pUnoData )
/*N*/       return pUnoData->GetListener();
/*N*/   return uno::Reference< chart::XChartDataChangeEventListener >();
/*N*/ }

/*N*/ uno::Reference< chart::XChartData > ScChartListener::GetUnoSource() const
/*N*/ {
/*N*/   if ( pUnoData )
/*N*/       return pUnoData->GetSource();
/*N*/   return uno::Reference< chart::XChartData >();
/*N*/ }

/*N*/ void ScChartListener::Notify( SfxBroadcaster& /*rBC*/, const SfxHint& rHint )
/*N*/ {
/*N*/   const ScHint* p = PTR_CAST( ScHint, &rHint );
/*N*/   if( p && (p->GetId() & (SC_HINT_DATACHANGED | SC_HINT_DYING)) )
/*N*/   {
/*N*/       bDirty = TRUE;
/*N*/       pDoc->GetChartListenerCollection()->StartTimer();
/*N*/   }
/*N*/ }

/*N*/ void ScChartListener::Update()
/*N*/ {
/*N*/   if ( pDoc->IsInInterpreter() )
/*N*/   {   // #73482# If interpreting do nothing and restart timer so we don't
/*?*/       // interfere with interpreter and don't produce an Err522 or similar.
/*?*/       // This may happen if we are rescheduled via Basic function.
/*?*/       pDoc->GetChartListenerCollection()->StartTimer();
/*?*/       return ;
/*N*/   }
/*N*/   if ( pUnoData )
/*N*/   {
/*?*/       bDirty = FALSE;
/*?*/       //! irgendwann mal erkennen, was sich innerhalb des Charts geaendert hat
/*?*/       chart::ChartDataChangeEvent aEvent( pUnoData->GetSource(),
/*?*/                                       chart::ChartDataChangeType_ALL,
/*?*/                                       0, 0, 0, 0 );
/*?*/       pUnoData->GetListener()->chartDataChanged( aEvent );
/*N*/   }
/*N*/   else if ( pDoc->GetAutoCalc() )
/*N*/   {
/*N*/       bDirty = FALSE;
/*N*/       pDoc->UpdateChart( GetString(), NULL );
/*N*/   }
/*N*/ }

/*N*/ void ScChartListener::StartListeningTo()
/*N*/ {
/*N*/   if ( aRangeListRef.Is() )
/*N*/       for ( ScRangePtr pR = aRangeListRef->First(); pR;
/*N*/                        pR = aRangeListRef->Next() )
/*N*/       {
/*N*/           if ( pR->aStart == pR->aEnd )
/*?*/               pDoc->StartListeningCell( pR->aStart, this );
/*N*/           else
/*N*/               pDoc->StartListeningArea( *pR, this );
/*N*/       }
/*N*/ }

/*N*/ void ScChartListener::EndListeningTo()
/*N*/ {
/*N*/   if ( aRangeListRef.Is() )
/*N*/       for ( ScRangePtr pR = aRangeListRef->First(); pR;
/*N*/                        pR = aRangeListRef->Next() )
/*N*/       {
/*N*/           if ( pR->aStart == pR->aEnd )
/*?*/               pDoc->EndListeningCell( pR->aStart, this );
/*N*/           else
/*N*/               pDoc->EndListeningArea( *pR, this );
/*N*/       }
/*N*/ }


/*N*/ void ScChartListener::SetRangeList( const ScRange& rRange )
/*N*/ {
/*N*/   aRangeListRef = new ScRangeList;
/*N*/   aRangeListRef->Append( rRange );
/*N*/ }










// === ScChartListenerCollection ======================================

/*N*/ ScChartListenerCollection::ScChartListenerCollection( ScDocument* pDocP ) :
/*N*/   StrCollection( 4, 4, FALSE ),
/*N*/   pDoc( pDocP )
/*N*/ {
/*N*/   aTimer.SetTimeoutHdl( LINK( this, ScChartListenerCollection, TimerHdl ) );
/*N*/ }


/*N*/ ScChartListenerCollection::~ScChartListenerCollection()
/*N*/ {
/*N*/   //  #96783# remove ChartListener objects before aTimer dtor is called, because
/*N*/   //  ScChartListener::EndListeningTo may cause ScChartListenerCollection::StartTimer
/*N*/   //  to be called if an empty ScNoteCell is deleted
/*N*/
/*N*/   if (GetCount())
/*N*/       FreeAll();
/*N*/ }

/*N*/ void ScChartListenerCollection::FreeUnused()
/*N*/ {
/*N*/   // rueckwaerts wg. Pointer-Aufrueckerei im Array
/*N*/   for ( USHORT nIndex = nCount; nIndex-- >0; )
/*N*/   {
/*N*/       ScChartListener* pCL = (ScChartListener*) pItems[ nIndex ];
/*N*/       //  Uno-Charts nicht rauskicken
/*N*/       //  (werden per FreeUno von aussen geloescht)
/*N*/       if ( !pCL->IsUno() )
/*N*/       {
/*N*/           if ( pCL->IsUsed() )
/*N*/               pCL->SetUsed( FALSE );
/*N*/           else
/*?*/               Free( pCL );
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void ScChartListenerCollection::FreeUno( const uno::Reference< chart::XChartDataChangeEventListener >& rListener,
/*N*/                                        const uno::Reference< chart::XChartData >& rSource )
/*N*/ {
/*N*/   // rueckwaerts wg. Pointer-Aufrueckerei im Array
/*N*/   for ( USHORT nIndex = nCount; nIndex-- >0; )
/*N*/   {
/*N*/       ScChartListener* pCL = (ScChartListener*) pItems[ nIndex ];
/*N*/       if ( pCL->IsUno() &&
/*N*/            pCL->GetUnoListener() == rListener &&
/*N*/            pCL->GetUnoSource() == rSource )
/*N*/       {
/*N*/           Free( pCL );
/*N*/       }
/*N*/       //! sollte nur einmal vorkommen?
/*N*/   }
/*N*/ }

/*N*/ void ScChartListenerCollection::StartTimer()
/*N*/ {
/*N*/   aTimer.SetTimeout( SC_CHARTTIMEOUT );
/*N*/   aTimer.Start();
/*N*/ }

/*N*/ IMPL_LINK( ScChartListenerCollection, TimerHdl, Timer*, EMPTYARG )
/*N*/ {
/*N*/   if ( Application::AnyInput( VCL_INPUT_KEYBOARD ) )
/*N*/   {
/*?*/       aTimer.Start();
/*?*/       return 0;
/*N*/   }
/*N*/   UpdateDirtyCharts();
/*N*/   return 0;
/*N*/ }

/*N*/ void ScChartListenerCollection::UpdateDirtyCharts()
/*N*/ {
/*N*/   for ( USHORT nIndex = 0; nIndex < nCount; nIndex++ )
/*N*/   {
/*N*/       ScChartListener* pCL = (ScChartListener*) pItems[ nIndex ];
/*N*/       if ( pCL->IsDirty() )
/*N*/           pCL->Update();
/*N*/       if ( aTimer.IsActive() && !pDoc->IsImportingXML())
/*N*/           break;                      // da kam einer dazwischen
/*N*/   }
/*N*/ }


/*N*/ void ScChartListenerCollection::SetDirty()
/*N*/ {
/*N*/   for ( USHORT nIndex = 0; nIndex < nCount; nIndex++ )
/*N*/   {
/*?*/       ScChartListener* pCL = (ScChartListener*) pItems[ nIndex ];
/*?*/       pCL->SetDirty( TRUE );
/*N*/   }
/*N*/   StartTimer();
/*N*/ }


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
