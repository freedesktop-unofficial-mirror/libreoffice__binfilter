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

#include "refreshtimer.hxx"
#include <tools/debug.hxx>
namespace binfilter {

/*N*/ ScRefreshTimerProtector::ScRefreshTimerProtector( ScRefreshTimerControl * const * pp )
/*N*/       :
/*N*/       ppControl( pp )
/*N*/ {
/*N*/   if ( ppControl && *ppControl )
/*N*/   {
/*N*/       (*ppControl)->SetAllowRefresh( FALSE );
/*N*/       // wait for any running refresh in another thread to finnish
/*N*/       ::osl::MutexGuard aGuard( (*ppControl)->GetMutex() );
/*N*/   }
/*N*/ }


/*N*/ ScRefreshTimer::~ScRefreshTimer()
/*N*/ {
/*N*/   if ( IsActive() )
/*?*/       Stop();
/*N*/   RemoveFromControl();
/*N*/ }


void ScRefreshTimer::SetRefreshDelay( ULONG /*nSeconds*/ )
{
    DBG_BF_ASSERT(0, "STRIP");  // VIRTUAL
}



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
