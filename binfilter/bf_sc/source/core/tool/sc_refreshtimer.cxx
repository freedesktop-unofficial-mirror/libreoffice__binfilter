/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_refreshtimer.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 17:17:04 $
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

#ifdef PCH
// auto strip #include "core_pch.hxx"
#endif

#pragma hdrstop

#include "refreshtimer.hxx"
#include <tools/debug.hxx>//STRIP001
namespace binfilter {

/*N*/ ScRefreshTimerProtector::ScRefreshTimerProtector( ScRefreshTimerControl * const * pp )
/*N*/       :
/*N*/       ppControl( pp )
/*N*/ {
/*N*/   if ( ppControl && *ppControl )
/*N*/   {
/*N*/       (*ppControl)->SetAllowRefresh( FALSE );
/*N*/       // wait for any running refresh in another thread to finnish
/*N*/       ::vos::OGuard aGuard( (*ppControl)->GetMutex() );
/*N*/   }
/*N*/ }


/*N*/ ScRefreshTimer::~ScRefreshTimer()
/*N*/ {
/*N*/   if ( IsActive() )
/*?*/       Stop();
/*N*/   RemoveFromControl();
/*N*/ }


/*N*/ void ScRefreshTimer::SetRefreshDelay( ULONG nSeconds )
/*N*/ {
/*N*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 BOOL bActive = IsActive();
//STRIP001  if ( bActive && !nSeconds )
//STRIP001      Stop();
//STRIP001  SetTimeout( nSeconds * 1000 );
//STRIP001  if ( !bActive && nSeconds )
//STRIP001      Start();
/*N*/ }


//STRIP001 void ScRefreshTimer::Timeout()
//STRIP001 {
//STRIP001  if ( ppControl && *ppControl && (*ppControl)->IsRefreshAllowed() )
//STRIP001  {
//STRIP001      // now we COULD make the call in another thread ...
//STRIP001      ::vos::OGuard aGuard( (*ppControl)->GetMutex() );
//STRIP001      maTimeoutHdl.Call( this );
//STRIP001      // restart from now on, don't execute immediately again if timed out
//STRIP001      // a second time during refresh
//STRIP001      if ( IsActive() )
//STRIP001          Start();
//STRIP001  }
//STRIP001 }

}
