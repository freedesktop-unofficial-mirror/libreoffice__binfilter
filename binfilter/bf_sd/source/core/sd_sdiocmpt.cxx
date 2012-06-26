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

#include <tools/debug.hxx>

#include "sdiocmpt.hxx"
namespace binfilter {





/*************************************************************************
|*
|* Konstruktor, schreibt bzw. liest Versionsnummer
|*
\************************************************************************/

/*N*/ SdIOCompat::SdIOCompat(SvStream& rNewStream, USHORT nNewMode, UINT16 nVer)
/*N*/          : SdrDownCompat(rNewStream, nNewMode, TRUE),
/*N*/            nVersion(nVer)
/*N*/ {
/*N*/   if (nNewMode == STREAM_WRITE)
/*N*/   {
/*N*/       DBG_ASSERT(nVer != SDIOCOMPAT_VERSIONDONTKNOW,
/*N*/                  "kann unbekannte Version nicht schreiben");
/*N*/       rNewStream << nVersion;
/*N*/   }
/*N*/   else if (nNewMode == STREAM_READ)
/*N*/   {
/*N*/       DBG_ASSERT(nVer == SDIOCOMPAT_VERSIONDONTKNOW,
/*N*/                  "Lesen mit Angabe der Version ist Quatsch!");
/*N*/       rNewStream >> nVersion;
/*N*/   }
/*N*/ }





}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
