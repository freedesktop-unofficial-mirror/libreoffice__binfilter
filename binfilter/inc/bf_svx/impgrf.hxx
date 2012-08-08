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
#ifndef _SVX_IMPGRF_HXX
#define _SVX_IMPGRF_HXX

#include <bf_svtools/filter.hxx>

namespace binfilter {

// Funktionen ------------------------------------------------------------

// returnt einen static Graphic-Filter, wird einmalig angelegt,
// steht immer zur Verfuegung, DARF NIE geloescht werden!!!!
GraphicFilter* GetGrfFilter();
USHORT  FillFilter( GraphicFilter& rFilter );

// class SvxImportGraphicDialog ------------------------------------------
#ifndef SV_NODIALOG

#define ENABLE_STANDARD         ((USHORT)0x0001)    // Standard-Button
#define ENABLE_LINK             ((USHORT)0x0002)    // Verkn"upfungs-Box
#define ENABLE_STD_AND_LINK     (ENABLE_STANDARD | ENABLE_LINK)
#define ENABLE_PROPERTY         ((USHORT)0x0004)    // Eigenschaften-Button
#define ENABLE_ALL              ((USHORT)0x0007)    // alle
#define ENABLE_PROP_WITHOUTLINK ((USHORT)0x0008)    // Eigenschaften ohne Link
#define ENABLE_EMPTY_FILENAMES  ((USHORT)0x0010)    // Leere Dateinamen zulassen

#endif  // SV_NODIALOG

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
