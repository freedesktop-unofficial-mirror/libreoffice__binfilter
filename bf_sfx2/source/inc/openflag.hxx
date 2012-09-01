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
#ifndef _SFX_OPENFLAG_HXX
#define _SFX_OPENFLAG_HXX
namespace binfilter {

// Datei zum Bearbeiten "offnen, anschliessend funktioniert nur noch
// die dritte Variante (Lesen einer Kopie)
#define SFX_STREAM_READWRITE  (STREAM_READWRITE |  STREAM_SHARE_DENYWRITE)
// Ich arbeite roh auf dem Original, keine Kopie
// -> Datei kann anschliessend nicht zum Bearbeiten ge"offnet werden
#define SFX_STREAM_READONLY   (STREAM_READ | STREAM_SHARE_DENYWRITE) // + !bDirect
// Jemand anders bearbeitet das File, es wird eine Kopie erstellt
// -> Datei kann anschliessend zum Bearbeiten ge"offnet werden
#define SFX_STREAM_READONLY_MAKECOPY   (STREAM_READ | STREAM_SHARE_DENYNONE)


}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
