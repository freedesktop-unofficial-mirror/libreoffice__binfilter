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
#ifndef _SVX_HTMLMODE_HXX
#define _SVX_HTMLMODE_HXX
namespace binfilter {

// include ---------------------------------------------------------------

// define ----------------------------------------------------------------

#define HTMLMODE_ON                 0x0001
#define HTMLMODE_PARA_BORDER        0x0002 /* Absatzumrandungen */
#define HTMLMODE_PARA_DISTANCE      0x0004 /* bestimmte Absatzabstaende */
#define HTMLMODE_SMALL_CAPS         0x0008 /* Kapitaelchen */
#define HTMLMODE_FRM_COLUMNS        0x0010 /* spaltige Rahmen */
#define HTMLMODE_SOME_STYLES        0x0020 /* mind. MS IE */
#define HTMLMODE_FULL_STYLES        0x0040 /* == SW */
#define HTMLMODE_BLINK              0x0080 /* blinkende Zeichen*/
#define HTMLMODE_PARA_BLOCK         0x0100 /* Blocksatz */
#define HTMLMODE_DROPCAPS           0x0200 /* Initialen*/
#define HTMLMODE_FIRSTLINE          0x0400 /* Erstzeileneinzug mit Spacer == NS 3.0 */
#define HTMLMODE_GRAPH_POS          0x0800 /* Grafikpositionen Hintergrund */
#define HTMLMODE_FULL_ABS_POS       0x1000 /* abs. Rahmenpositionierung */
#define HTMLMODE_SOME_ABS_POS       0x2000 /* abs. Rahmenpositionierung vollst.*/
#define HTMLMODE_RESERVED1          0x4000
#define HTMLMODE_RESERVED0          0x8000

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
