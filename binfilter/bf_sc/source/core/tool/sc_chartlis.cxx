/*************************************************************************
 *
 *  $RCSfile: sc_chartlis.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:26:26 $
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

#ifdef PCH
#include "core_pch.hxx"
#endif

#pragma hdrstop

#include <vcl/svapp.hxx>

#include "chartlis.hxx"
#include "brdcst.hxx"
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
/*N*/   pDoc( pDocP ),
/*N*/   pUnoData( NULL ),
/*N*/   bUsed( FALSE ),
/*N*/   bDirty( FALSE ),
/*N*/   bSeriesRangesScheduled( FALSE )
/*N*/ {
/*N*/   SetRangeList( rRange );
/*N*/ }

/*N*/ ScChartListener::ScChartListener( const String& rName, ScDocument* pDocP,
/*N*/       const ScRangeListRef& rRangeList ) :
/*N*/   StrData( rName ),
/*N*/   aRangeListRef( rRangeList ),
/*N*/   pDoc( pDocP ),
/*N*/   pUnoData( NULL ),
/*N*/   bUsed( FALSE ),
/*N*/   bDirty( FALSE ),
/*N*/   bSeriesRangesScheduled( FALSE )
/*N*/ {
/*N*/ }

/*N*/ ScChartListener::ScChartListener( const ScChartListener& r ) :
/*N*/       StrData( r ),
/*N*/       pDoc( r.pDoc ),
/*N*/       pUnoData( NULL ),
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

/*N*/ DataObject* ScChartListener::Clone() const
/*N*/ {
        DBG_ASSERT(0, "STRIP");return NULL; //STRIP001 return new ScChartListener( *this );
/*N*/ }

/*N*/ void ScChartListener::SetUno(
/*N*/       const uno::Reference< chart::XChartDataChangeEventListener >& rListener,
/*N*/       const uno::Reference< chart::XChartData >& rSource )
/*N*/ {
/*N*/ //    DBG_ASSERT( rListener.is() && rSource.is(), "Nullpointer bei SetUno" );
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

/*N*/ void __EXPORT ScChartListener::Notify( SfxBroadcaster& rBC, const SfxHint& rHint )
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


/*N*/ void ScChartListener::ChangeListening( const ScRangeListRef& rRangeListRef,
/*N*/           BOOL bDirtyP  )
/*N*/ {
/*N*/   EndListeningTo();
/*N*/   SetRangeList( rRangeListRef );
/*N*/   StartListeningTo();
/*N*/   if ( bDirtyP )
/*N*/       SetDirty( TRUE );
/*N*/ }


/*N*/ void ScChartListener::SetRangeList( const ScRange& rRange )
/*N*/ {
/*N*/   aRangeListRef = new ScRangeList;
/*N*/   aRangeListRef->Append( rRange );
/*N*/ }


//STRIP001 void ScChartListener::UpdateScheduledSeriesRanges()
//STRIP001 {
//STRIP001  if ( bSeriesRangesScheduled )
//STRIP001  {
//STRIP001      bSeriesRangesScheduled = FALSE;
//STRIP001      UpdateSeriesRanges();
//STRIP001  }
//STRIP001 }


//STRIP001 void ScChartListener::UpdateSeriesRangesIntersecting( const ScRange& rRange )
//STRIP001 {
//STRIP001  if ( aRangeListRef->Intersects( rRange ) )
//STRIP001      UpdateSeriesRanges();
//STRIP001 }


//STRIP001 void ScChartListener::UpdateSeriesRanges()
//STRIP001 {
//STRIP001  pDoc->SetChartRangeList( GetString(), aRangeListRef );
//STRIP001 }


//STRIP001 BOOL ScChartListener::operator==( const ScChartListener& r )
//STRIP001 {
//STRIP001  BOOL b1 = aRangeListRef.Is();
//STRIP001  BOOL b2 = r.aRangeListRef.Is();
//STRIP001  return
//STRIP001      pDoc == r.pDoc &&
//STRIP001      bUsed == r.bUsed &&
//STRIP001      bDirty == r.bDirty &&
//STRIP001      bSeriesRangesScheduled == r.bSeriesRangesScheduled &&
//STRIP001      GetString() == r.GetString() &&
//STRIP001      b1 == b2 &&
//STRIP001      ((!b1 && !b2) || (*aRangeListRef == *r.aRangeListRef))
//STRIP001      ;
//STRIP001 }


// === ScChartListenerCollection ======================================

/*N*/ ScChartListenerCollection::ScChartListenerCollection( ScDocument* pDocP ) :
/*N*/   StrCollection( 4, 4, FALSE ),
/*N*/   pDoc( pDocP )
/*N*/ {
/*N*/   aTimer.SetTimeoutHdl( LINK( this, ScChartListenerCollection, TimerHdl ) );
/*N*/ }

//STRIP001 ScChartListenerCollection::ScChartListenerCollection(
//STRIP001      const ScChartListenerCollection& rColl ) :
//STRIP001  StrCollection( rColl ),
//STRIP001  pDoc( rColl.pDoc )
//STRIP001 {
//STRIP001  aTimer.SetTimeoutHdl( LINK( this, ScChartListenerCollection, TimerHdl ) );
//STRIP001 }

/*N*/ ScChartListenerCollection::~ScChartListenerCollection()
/*N*/ {
/*N*/   //  #96783# remove ChartListener objects before aTimer dtor is called, because
/*N*/   //  ScChartListener::EndListeningTo may cause ScChartListenerCollection::StartTimer
/*N*/   //  to be called if an empty ScNoteCell is deleted
/*N*/
/*N*/   if (GetCount())
/*N*/       FreeAll();
/*N*/ }

/*N*/ DataObject*   ScChartListenerCollection::Clone() const
/*N*/ {
        DBG_ASSERT(0, "STRIP");return NULL;//STRIP001   return new ScChartListenerCollection( *this );
/*N*/ }

//STRIP001 void ScChartListenerCollection::StartAllListeners()
//STRIP001 {
//STRIP001  for ( USHORT nIndex = 0; nIndex < nCount; nIndex++ )
//STRIP001  {
//STRIP001      ((ScChartListener*) pItems[ nIndex ])->StartListeningTo();
//STRIP001  }
//STRIP001 }

/*N*/ void ScChartListenerCollection::ChangeListening( const String& rName,
/*N*/       const ScRangeListRef& rRangeListRef, BOOL bDirty )
/*N*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001 ScChartListener aCLSearcher( rName, pDoc, rRangeListRef );
//STRIP001  ScChartListener* pCL;
//STRIP001  USHORT nIndex;
//STRIP001  if ( Search( &aCLSearcher, nIndex ) )
//STRIP001  {
//STRIP001      pCL = (ScChartListener*) pItems[ nIndex ];
//STRIP001      pCL->EndListeningTo();
//STRIP001      pCL->SetRangeList( rRangeListRef );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pCL = new ScChartListener( aCLSearcher );
//STRIP001      Insert( pCL );
//STRIP001  }
//STRIP001  pCL->StartListeningTo();
//STRIP001  if ( bDirty )
//STRIP001      pCL->SetDirty( TRUE );
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

/*N*/ IMPL_LINK( ScChartListenerCollection, TimerHdl, Timer*, pTimer )
/*N*/ {
/*N*/   if ( Application::AnyInput( INPUT_KEYBOARD ) )
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


//STRIP001 void ScChartListenerCollection::SetDiffDirty(
//STRIP001          const ScChartListenerCollection& rCmp, BOOL bSetChartRangeLists )
//STRIP001 {
//STRIP001  BOOL bDirty = FALSE;
//STRIP001  for ( USHORT nIndex = 0; nIndex < nCount; nIndex++ )
//STRIP001  {
//STRIP001      ScChartListener* pCL = (ScChartListener*) pItems[ nIndex ];
//STRIP001      USHORT nFound;
//STRIP001      BOOL bFound = rCmp.Search( pCL, nFound );
//STRIP001      if ( !bFound || (*pCL != *((const ScChartListener*) rCmp.pItems[ nFound ])) )
//STRIP001      {
//STRIP001          if ( bSetChartRangeLists )
//STRIP001          {
//STRIP001              if ( bFound )
//STRIP001              {
//STRIP001                  const ScRangeListRef& rList1 = pCL->GetRangeList();
//STRIP001                  const ScRangeListRef& rList2 =
//STRIP001                      ((const ScChartListener*) rCmp.pItems[ nFound ])->GetRangeList();
//STRIP001                  BOOL b1 = rList1.Is();
//STRIP001                  BOOL b2 = rList2.Is();
//STRIP001                  if ( b1 != b2 || (b1 && b2 && (*rList1 != *rList2)) )
//STRIP001                      pDoc->SetChartRangeList( pCL->GetString(), rList1 );
//STRIP001              }
//STRIP001              else
//STRIP001                  pDoc->SetChartRangeList( pCL->GetString(), pCL->GetRangeList() );
//STRIP001          }
//STRIP001          bDirty = TRUE;
//STRIP001          pCL->SetDirty( TRUE );
//STRIP001      }
//STRIP001  }
//STRIP001  if ( bDirty )
//STRIP001      StartTimer();
//STRIP001 }


//STRIP001 void ScChartListenerCollection::SetRangeDirty( const ScRange& rRange )
//STRIP001 {
//STRIP001  BOOL bDirty = FALSE;
//STRIP001  for ( USHORT nIndex = 0; nIndex < nCount; nIndex++ )
//STRIP001  {
//STRIP001      ScChartListener* pCL = (ScChartListener*) pItems[ nIndex ];
//STRIP001      const ScRangeListRef& rList = pCL->GetRangeList();
//STRIP001      if ( rList.Is() && rList->Intersects( rRange ) )
//STRIP001      {
//STRIP001          bDirty = TRUE;
//STRIP001          pCL->SetDirty( TRUE );
//STRIP001      }
//STRIP001  }
//STRIP001  if ( bDirty )
//STRIP001      StartTimer();
//STRIP001 }


/*N*/ void ScChartListenerCollection::UpdateScheduledSeriesRanges()
/*N*/ {
/*N*/   for ( USHORT nIndex = 0; nIndex < nCount; nIndex++ )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 ScChartListener* pCL = (ScChartListener*) pItems[ nIndex ];
//STRIP001 /*?*/        pCL->UpdateScheduledSeriesRanges();
/*N*/   }
/*N*/ }


/*N*/ void ScChartListenerCollection::UpdateSeriesRangesContainingTab( USHORT nTab )
/*N*/ {
/*N*/   ScRange aRange( 0, 0, nTab, MAXCOL, MAXROW, nTab );
/*N*/   for ( USHORT nIndex = 0; nIndex < nCount; nIndex++ )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 ScChartListener* pCL = (ScChartListener*) pItems[ nIndex ];
//STRIP001 /*?*/        pCL->UpdateSeriesRangesIntersecting( aRange );
/*N*/   }
/*N*/ }


//STRIP001 BOOL ScChartListenerCollection::operator==( const ScChartListenerCollection& r )
//STRIP001 {
//STRIP001  // hier nicht StrCollection::operator==() verwenden, der umstaendlich via
//STRIP001  // IsEqual und Compare laeuft, stattdessen ScChartListener::operator==()
//STRIP001  if ( pDoc != r.pDoc || nCount != r.nCount )
//STRIP001      return FALSE;
//STRIP001  for ( USHORT nIndex = 0; nIndex < nCount; nIndex++ )
//STRIP001  {
//STRIP001      if ( *((ScChartListener*) pItems[ nIndex ]) !=
//STRIP001              *((ScChartListener*) r.pItems[ nIndex ]) )
//STRIP001          return FALSE;
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }




}
