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
#ifndef __EXCCRTS_HXX__
#define __EXCCRTS_HXX__

#include "fltglbls.hxx"

#include <tools/debug.hxx>
namespace binfilter {

// ----------------------------------------------- class ColRowSettings --
class ColRowSettings
    {
    // ACHTUNG:     Col-/Row-Angaben in TWIPS
    //              ExcelKoordinaten -> Klasse( -> SwKoordinaten )
    private:
        INT32   *pWidth;
        INT32   *pHeight;
        BOOL    *pColHidden;
        BOOL    *pRowHidden;
        BOOL    *pColUsed;
        BOOL    *pRowUsed;
        USHORT  nDefWidth;
        USHORT  nDefHeight;
        USHORT  nAktTab;
        USHORT  nTabLimit, nColLimit, nRowLimit;
    public:
        ColRowSettings();
        ~ColRowSettings();
        void NewTab( USHORT nNew );
        void Apply();
#ifdef USED
        void HideColRange( USHORT nColFirst, USHORT nColLast );
        void HideRowRange( USHORT nRowFirst, USHORT nRowLast );
#endif
        void SetWidthRange( USHORT nColF, USHORT nColL, USHORT nNew );
        void SetDefaults( USHORT nWidth, USHORT nHeight )
            {
            nDefWidth = nWidth;
            nDefHeight = nHeight;
            }

        void SetDefWidth( USHORT nNew ) { nDefWidth = nNew; }

        void SetDefHeight( USHORT nNew ) { nDefHeight = nNew; }

        void SetWidth( USHORT nCol, INT32 nNew )
            {
            pExcGlob->NormalizeCol( nCol );

            DBG_ASSERT( nCol < nColLimit,
                "+ColRowSettings::SetWidth(): ungueltige Column" );
            if( nCol < nColLimit )
                {
                pWidth[ nCol ] = nNew;
                pColUsed[ nCol ] = TRUE;
                }
            }

        void SetHeight( USHORT nRow, INT32 nNew )
            {
            pExcGlob->NormalizeRow( nRow );

            DBG_ASSERT( nRow < nRowLimit,
                "+ColRowSettings::SetHeight(): ungueltige Row" );
            if( nRow < nRowLimit )
                {
                pHeight[ nRow ] = nNew;
                pRowUsed[ nRow ] = TRUE;
                }
            }

        void Used( USHORT nCol, USHORT nRow )
            {
            pExcGlob->Normalize( nCol, nRow );

            DBG_ASSERT( nRow < nRowLimit,
                "+ColRowSettings::Used(): ungueltige Row" );
            DBG_ASSERT( nCol < nColLimit,
                "+ColRowSettings::Used(): ungueltige Column" );
            if( nCol < nColLimit && nRow < nRowLimit )
                {
                pColUsed[ nCol ] = TRUE;
                pRowUsed[ nRow ] = TRUE;
                }
            }

        void ColUsed( USHORT nCol )
            {
            pExcGlob->NormalizeCol( nCol );

            DBG_ASSERT( nCol < nColLimit,
                "+ColRowSettings::ColUsed(): ungueltige Column" );
            if( nCol < nColLimit ) pColUsed[ nCol ] = TRUE;
            }

        void RowUsed( USHORT nRow )
            {
            pExcGlob->NormalizeRow( nRow );

            DBG_ASSERT( nRow < nRowLimit,
                "+ColRowSettings::RowUsed(): ungueltige Row" );
            if( nRow < nRowLimit ) pRowUsed[ nRow ] = TRUE;
            }

    };

// ---------------------------------------------------- class FltColumn --

class FltColumn
    {
    //  ACHTUNG:    SwKoordinaten -> Klasse( -> SwKoordinaten )
    private:
        USHORT *pData;      // Daten-Array fuer XF-Indizes
        USHORT nSize;       // Groesse des pData-Arrays, teilbar durch 2
        USHORT nLastRow;
        USHORT nCol;        // Column-Nummer
        static USHORT nTab; // Tabellen-Nummer

        static const USHORT nDefSize;
        static const USHORT nLevelSize;
        static UINT32 nDefCleared;

        void Grow( USHORT nRecIndex );
    public:
        FltColumn( USHORT nNewCol );
#ifdef USED
        FltColumn( USHORT nNewCol, USHORT nNewSize );
#endif

        ~FltColumn() { delete[] pData; }

        void SetXF( USHORT nRow, USHORT nNewXF )
            {
            if( nRow < pExcGlob->AnzRows() )
                {
                if( nRow >= nSize ) Grow( nRow );
                if( nRow > nLastRow ) nLastRow = nRow;

                DBG_ASSERT( nRow < nSize,
                    "-FltColumn::SetXF(): nSize nicht an nRow angepasst!" );

                pData[ nRow ] = nNewXF;
                }
            }

        void SetTab( USHORT nNewTab )
            {
            nTab = nNewTab;
            }

        void Settings( USHORT nNewTab )
            {
            nTab = nNewTab;
            }

#ifdef USED
        void Reset( USHORT nNewTab );
#endif
        void Reset();
        void Apply();
    };

// --------------------------------------------------- class FltTabelle --

class FltTabelle
    {
    //  ACHTUNG:    ExcelKoordinaten -> Klasse( -> SwKoordinaten )
    private:
        FltColumn **pData;  // Array mit Column-Daten
        USHORT nSize;
        USHORT nLastCol;
    public:
        FltTabelle();
        ~FltTabelle();
        void Settings( USHORT nTab );
        void SetXF( USHORT nCol, USHORT nRow, USHORT nNewXF );
#ifdef USED
        void Reset( USHORT nTab );
#endif
        void Apply();
    };

// -----------------------------------------------------------------------

} //namespace binfilter
#endif


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
