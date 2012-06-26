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
#ifndef _REDLENUM_HXX
#define _REDLENUM_HXX
namespace binfilter {


// Redline Typen
enum SwRedlineType
{
    // die RedlineTypen gehen von 0 bis 127
    REDLINE_INSERT,             // Inhalt wurde eingefuegt
    REDLINE_DELETE,             // Inhalt wurde geloescht
    REDLINE_FORMAT,             // Attributierung wurde angewendet
    REDLINE_TABLE,              // TabellenStruktur wurde veraendert
    REDLINE_FMTCOLL,            // FormatVorlage wurde veraendert (Autoformat!)

    // ab 128 koennen Flags hineinverodert werden
    REDLINE_NO_FLAG_MASK    = 0x007f,
    REDLINE_FLAG_MASK       = 0xff80,
    REDLINE_FORM_AUTOFMT    = 0x0080    // kann als Flag im RedlineType stehen
};


// Redline Modus vom Doc
enum SwRedlineMode
{
    REDLINE_NONE,                       // kein RedlineMode
    REDLINE_ON      = 0x01,             // RedlineMode on
    REDLINE_IGNORE  = 0x02,             // auf Redlines nicht reagieren

    REDLINE_SHOW_INSERT = 0x10,     // alle Einfuegungen anzeigen
    REDLINE_SHOW_DELETE = 0x20,     // alle Loeschungen anzeigen

    REDLINE_SHOW_MASK = REDLINE_SHOW_INSERT | REDLINE_SHOW_DELETE,

    // fuer die interne Verwaltung:
    //  die originalen Redlines inclusive des Contents entfernen
    //  (ClipBoard/Textbausteine)
    REDLINE_DELETE_REDLINES = 0x100,
    //  beim Loeschen innerhalb ein RedlineObjectes, waehrend des Appends,
    // das DeleteRedline ignorieren
    REDLINE_IGNOREDELETE_REDLINES = 0x200,
    // don't combine any readlines. This flags is may only used in the Undo.
    REDLINE_DONTCOMBINE_REDLINES = 0x400
};

inline bool IsShowChanges( const USHORT eM )
{
    return (REDLINE_SHOW_INSERT | REDLINE_SHOW_DELETE) ==
                    (eM & REDLINE_SHOW_MASK);
}
inline bool IsHideChanges( const USHORT eM )
{
    return REDLINE_SHOW_INSERT == (eM & REDLINE_SHOW_MASK);
}
inline bool IsShowOriginal( const USHORT eM )
{
    return REDLINE_SHOW_DELETE == (eM & REDLINE_SHOW_MASK);
}
inline bool IsRedlineOn( const USHORT eM )
{
    return REDLINE_ON == (eM & (REDLINE_ON | REDLINE_IGNORE ));
}



} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
