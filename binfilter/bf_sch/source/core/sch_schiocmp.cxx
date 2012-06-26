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

#include <tools/debug.hxx>
#include "schiocmp.hxx"
namespace binfilter {


//  CTOR: writes/reads version number

/*N*/ SchIOCompat::SchIOCompat( SvStream& rNewStream, USHORT nNewMode,
/*N*/                         UINT16 nVer ) :
/*N*/       SdrDownCompat( rNewStream, nNewMode, TRUE ),
/*N*/       nVersion( nVer )
/*N*/ {
/*N*/   switch( nNewMode )
/*N*/   {
/*N*/       case STREAM_WRITE:
/*N*/           DBG_ASSERT( nVer != SCHIOCOMPAT_VERSIONDONTKNOW,
/*N*/                       "Requesting writing of unknown File Version" );
/*N*/           rNewStream << nVersion;
/*N*/           break;
/*N*/
/*N*/       case STREAM_READ:
/*N*/           DBG_ASSERT( nVer == SCHIOCOMPAT_VERSIONDONTKNOW,
/*N*/                       "Requesting reading of unknown File Version" );
/*N*/           rNewStream >> nVersion;
/*N*/           break;
/*N*/   }
/*N*/ }



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
