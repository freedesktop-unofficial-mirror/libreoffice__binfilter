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

#ifndef  _WRTSWTBL_HXX
#define  _WRTSWTBL_HXX

#include <bf_svtools/bf_solar.h>
#include <tools/color.hxx>
#include <bf_svtools/svarray.hxx>

#include <orntenum.hxx>
#include <horiornt.hxx>
class Color;

namespace binfilter {

class SwTableBox;
class SwTableBoxes;
class SwTableLine;
class SwTableLines;
class SwTable;
class SwFrmFmt;
class SvxBrushItem;
class SvxBoxItem;
class SvxBorderLine;


//---------------------------------------------------------------------------
//       Code aus dem HTML-Filter fuers schreiben von Tabellen
//---------------------------------------------------------------------------

#define COLFUZZY 20
#define ROWFUZZY 20
#define COL_DFLT_WIDTH ((2*COLFUZZY)+1)
#define ROW_DFLT_HEIGHT (2*ROWFUZZY)+1


class SwWriteTableCol
{
    USHORT nPos;                        // End Position der Spalte
    USHORT nWidthOpt;
    BOOL bRelWidthOpt : 1;
    BOOL bOutWidth : 1;                 // Spaltenbreite ausgeben?

public:
    BOOL bLeftBorder : 1;               // Welche Umrandungen sind da?
    BOOL bRightBorder : 1;
    SwWriteTableCol( USHORT nPosition );
    USHORT GetPos() const                                       { return nPos; }
    void SetLeftBorder( BOOL bBorder )                          { bLeftBorder = bBorder; }
    BOOL HasLeftBorder() const                  { return bLeftBorder; }
    void SetRightBorder( BOOL bBorder )                         { bRightBorder = bBorder; }
    BOOL HasRightBorder() const                 { return bRightBorder; }
    void SetOutWidth( BOOL bSet )               { bOutWidth = bSet; }
    BOOL GetOutWidth() const                    { return bOutWidth; }
    inline int operator==( const SwWriteTableCol& rCol ) const;
    inline int operator<( const SwWriteTableCol& rCol ) const;
    void SetWidthOpt( USHORT nWidth, BOOL bRel )
    {
        nWidthOpt = nWidth; bRelWidthOpt = bRel;
    }
    USHORT GetWidthOpt() const                  { return nWidthOpt; }
    BOOL HasRelWidthOpt() const                 { return bRelWidthOpt; }
};

inline int SwWriteTableCol::operator==( const SwWriteTableCol& rCol ) const
{
    // etwas Unschaerfe zulassen
    return (nPos >= rCol.nPos ? nPos - rCol.nPos
                                     : rCol.nPos - nPos ) <= COLFUZZY;
}

inline int SwWriteTableCol::operator<( const SwWriteTableCol& rCol ) const
{
    // Da wir hier nur die Wahrheits-Grade 0 und 1 kennen, lassen wir lieber
    // auch nicht zu, dass x==y und x<y gleichzeitig gilt ;-)
    return nPos < rCol.nPos - COLFUZZY;
}

typedef SwWriteTableCol* SwWriteTableColPtr;
SV_DECL_PTRARR_SORT_DEL( SwWriteTableCols, SwWriteTableColPtr, 5, 5 )

class SwWriteTable
{
    public:
        static long GetBoxWidth( const SwTableBox *pBox );
};


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
