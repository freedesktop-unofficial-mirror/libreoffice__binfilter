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

#ifndef _ORNTENUM_HXX
#define _ORNTENUM_HXX
namespace binfilter {

//SwFmtVertOrient, wie und woran orientiert --
//  sich der FlyFrm in der Vertikalen -----------

enum SwRelationOrient
{
    FRAME,          // Absatz inkl. Raender
    PRTAREA,        // Absatz ohne Raender
    REL_CHAR,       // an einem Zeichen
    REL_PG_LEFT,    // im linken Seitenrand
    REL_PG_RIGHT,   // im rechten Seitenrand
    REL_FRM_LEFT,   // im linken Absatzrand
    REL_FRM_RIGHT,  // im rechten Absatzrand
    REL_PG_FRAME,   // Seite inkl. Raender, bei seitengeb. identisch mit FRAME
    REL_PG_PRTAREA, // Seite ohne Raender, bei seitengeb. identisch mit PRTAREA
    // Wenn neue enums benoetigt werden, muessen die Ausweich-Arrays mitgepflegt
    // werden, LAST_ENUM_DUMMY muss immer das letzte enum bleiben
    LAST_ENUM_DUMMY
};

enum SwVertOrient
{
    VERT_NONE,  //Der Wert in nYPos gibt die RelPos direkt an.
    VERT_TOP,   //Der Rest ist fuer automatische Ausrichtung.
    VERT_CENTER,
    VERT_BOTTOM,
    VERT_CHAR_TOP,      //Ausrichtung _nur_ fuer Zeichengebundene Rahmen
    VERT_CHAR_CENTER,   //wie der Name jew. sagt wird der RefPoint des Rahmens
    VERT_CHAR_BOTTOM,   //entsprechend auf die Oberkante, Mitte oder Unterkante
    VERT_LINE_TOP,      //der Zeile gesetzt. Der Rahmen richtet sich  dann
    VERT_LINE_CENTER,   //entsprechend aus.
    VERT_LINE_BOTTOM
};

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
