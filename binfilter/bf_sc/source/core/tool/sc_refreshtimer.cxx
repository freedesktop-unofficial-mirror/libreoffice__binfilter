/*************************************************************************
 *
 *  $RCSfile: sc_refreshtimer.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:26:35 $
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
/*N*/   DBG_ASSERT(0, "STRIP"); //STRIP001 BOOL bActive = IsActive();
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
