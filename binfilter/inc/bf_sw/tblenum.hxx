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
#ifndef _TBLENUM_HXX
#define _TBLENUM_HXX
namespace binfilter {

//fuers aendern der Tabellen/Spalten/Zeilen Breiten/Hoehen
enum TblChgWidthHeightType
{
    WH_COL_LEFT,
    WH_COL_RIGHT,
    WH_ROW_TOP,
    WH_ROW_BOTTOM,
    WH_CELL_LEFT,
    WH_CELL_RIGHT,
    WH_CELL_TOP,
    WH_CELL_BOTTOM,


    // folgende koennen hinein verodert werden
    WH_FLAG_INSDEL  = 0x4000,           // Insert/Del-Modus: das Bigger-Flag
                                        // besagt was passiert:
                                        // bBigger -> Box wird entfernt
                                        // !bBigger-> Box wird eingefuegt
    WH_FLAG_BIGGER  = 0x8000            // Box wird groesser -> sonst kleiner
};

enum TblChgMode
{
    TBLFIX_CHGABS,          // Tabelle feste Breite, den Nachbar andern
    TBLFIX_CHGPROP,         // Tabelle feste Breite, alle Nachbarn aendern
    TBLVAR_CHGABS           // Tabelle variable, alle Nachbarn aendern
};


enum SplitTbl_HeadlineOption
{
    HEADLINE_NONE = 0,          // lasse alles wie es ist
    HEADLINE_BORDERCOPY,        // von der davor obere Line der vorhergehen Line
    HEADLINE_CNTNTCOPY,         // kopiere die 1. Line komplett mit Inhalt
    HEADLINE_BOXATTRCOPY,       // kopiere von der 1. Line die Box Attribute
    HEADLINE_BOXATRCOLLCOPY     // kopiere von der 1. Line die Box Attribute
                                // und die Absatzvorlagen
};

enum TableMergeErr
{
    TBLMERGE_OK,
    TBLMERGE_NOSELECTION,
    TBLMERGE_TOOCOMPLEX
};


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
