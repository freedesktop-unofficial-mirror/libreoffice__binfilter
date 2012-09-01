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

#ifndef _HORIORNT_HXX
#define _HORIORNT_HXX
namespace binfilter {


//SwFmtHoriOrient, wie und woran orientiert --
//  sich der FlyFrm in der Hoizontalen ----------

enum SwHoriOrient
{
    HORI_NONE,      //Der Wert in nYPos gibt die RelPos direkt an.
    HORI_RIGHT,     //Der Rest ist fuer automatische Ausrichtung.
    HORI_CENTER,
    HORI_LEFT,
    HORI_INSIDE,
    HORI_OUTSIDE,
    HORI_FULL,          //Spezialwert fuer Tabellen
    HORI_LEFT_AND_WIDTH  //Auch fuer Tabellen

    //Die Verwendung fuer FlyFrms ist klar. Fuer Tabellen ist die
    //Auswertung folgendermassen definiert:
    //NONE                == Die Randattribute zaehlen.
    //LEFT, CENTER, RIGHT == Wunschbreite wird falls moegliche eingehalten
    //                       und wenn noch Platz zur Verfuegung steht wird
    //                       ausgerichtet.
    //FULL                == Die Tabelle nutzt die ganze verfuegbare Breite.
    //LEFT_AND_WIDTH      == Linker Rand und Wunschbreite werden beruecksichtigt.
};



} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
