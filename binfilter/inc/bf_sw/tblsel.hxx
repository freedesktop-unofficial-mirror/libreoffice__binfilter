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
#ifndef _TBLSEL_HXX
#define _TBLSEL_HXX

#include <bf_svtools/bf_solar.h>


#include <swtable.hxx>
#include <swrect.hxx>
namespace binfilter {

class SwCrsrShell;
class SwCursor;
class SwTableCursor;
class SwFrm;
class SwTabFrm;
class SwTableBox;
class SwTableLine;
class SwLayoutFrm;
class SwPaM;
class SwNode;
class SwTable;
class SwCellFrm;

SV_DECL_PTRARR( SwCellFrms, SwCellFrm*, 16, 16 )
SV_DECL_PTRARR_SORT( SwSelBoxes, SwTableBoxPtr, 10, 20 )


//Sucht alle Boxen zusammen, die in der Tabelle selektiert sind.
//Je nach enum-Parameter wird die Selektion in der angegebenen Richtung
//erweitert.
//Die Boxen werden ueber das Layout zusammengsucht, es wird auch bei
//aufgespaltenen Tabellen korrekt gearbeitet (siehe: MakeSelUnions()).
enum SwTblSearchType
{
    TBLSEARCH_NONE      = 0x1,       // keine Erweiterung
    TBLSEARCH_ROW       = 0x2,       // erweiter auf Zeilen
    TBLSEARCH_COL       = 0x3,       // erweiter auf Spalten

    // als Flag zu den anderen Werten!!
    TBLSEARCH_PROTECT           = 0x8,      // auch geschuetzte Boxen einsammeln
    TBLSEARCH_NO_UNION_CORRECT  = 0x10      // die zusammenges. Union nicht korrigieren
};

//wie vor, jedoch wird nicht von der Selektion sondern von den
//Start- EndFrms ausgegangen.
void GetTblSel( const SwLayoutFrm* pStart, const SwLayoutFrm* pEnd,
                SwSelBoxes& rBoxes, const SwTblSearchType = TBLSEARCH_NONE );

// suche fuer eine AutoSumme die beteiligten Boxen zusammen
BOOL GetAutoSumSel( const SwCrsrShell&, SwCellFrms& );

// teste, ob die Selektion ausgeglichen ist
SV_DECL_PTRARR( SwChartBoxes, SwTableBoxPtr, 16, 16)
SV_DECL_PTRARR_DEL( SwChartLines, SwChartBoxes*, 25, 50)

// teste ob die Celle in die SSelection gehoert
// (wurde eine Funktion, damit GetTblSel() und MakeTblCrsr() immer
// das "gleiche Verstaendnis" fuer die Selektion haben)
BOOL IsFrmInTblSel( const SwRect& rUnion, const SwFrm* pCell );

// bestimme die Boxen, die zusammen gefasst werden sollen.
// Dabei wird auf Layout Basis das Rechteck "angepasst". D.H. es
// werden Boxen zugefuegt wenn welche an den Seiten ueberlappen
// Zusaetzlich wird die neue Box erzeugt und mit dem entsprechenden
// Inhalt gefuellt.
void GetMergeSel( const SwPaM& rPam, SwSelBoxes& rBoxes,
                  SwTableBox** ppMergeBox );

BOOL IsEmptyBox( const SwTableBox& rBox, SwPaM& rPam );

// teste ob ein Split oder InsertCol dazu fuehrt, das eine Box
// kleiner als MINLAY wird.
BOOL CheckSplitCells( const SwCrsrShell& rShell, USHORT nDiv,
                        const SwTblSearchType = TBLSEARCH_NONE );
BOOL CheckSplitCells( const SwCursor& rCrsr, USHORT nDiv,
                        const SwTblSearchType = TBLSEARCH_NONE );

//Fuer das Arbeiten auf TabSelektion auch fuer aufgespaltene Tabellen.
class SwSelUnion
{
    SwRect   aUnion;        //Das die Sel umschliessende Rechteck.
    SwTabFrm *pTable;       //Die (Follow-)Table zu der Union.

public:
    SwSelUnion( const SwRect &rRect, SwTabFrm *pTab ) :
        aUnion( rRect ), pTable( pTab ) {}

    const SwRect&   GetUnion() const { return aUnion; }
          SwRect&   GetUnion()       { return aUnion; }
    const SwTabFrm *GetTable() const { return pTable; }
          SwTabFrm *GetTable()       { return pTable; }
};

SV_DECL_PTRARR_DEL( SwSelUnions, SwSelUnion*, 10, 20 )

//Ermittelt die von einer Tabellenselektion betroffenen Tabellen und die
//Union-Rechteckte der Selektionen - auch fuer aufgespaltene Tabellen.
//Wenn ein Parameter != TBLSEARCH_NONE uebergeben wird, so wird die
//Selektion in der angegebenen Richtung erweitert.
void MakeSelUnions( SwSelUnions&, const SwLayoutFrm *pStart,
                    const SwLayoutFrm *pEnd,
                    const SwTblSearchType = TBLSEARCH_NONE );


// -------------------------------------------------------------------
// Diese Klassen kopieren die aktuelle Tabellen-Selektion (rBoxes)
// unter Beibehaltung der Tabellen-Strubktur in eine eigene Struktur

class _FndBox;
class _FndLine;

SV_DECL_PTRARR_DEL( _FndBoxes, _FndBox*, 10, 20 )
SV_DECL_PTRARR_DEL( _FndLines, _FndLine*,10, 20 )

class _FndBox
{
    SwTableBox* pBox;
    _FndLines aLines;
    _FndLine* pUpper;

    SwTableLine *pLineBefore;   //Zum Loeschen/Restaurieren des Layouts.
    SwTableLine *pLineBehind;

public:
    _FndBox( SwTableBox* pB, _FndLine* pFL ) :
        pBox(pB), pUpper(pFL), pLineBefore( 0 ), pLineBehind( 0 ) {}

    const _FndLines&    GetLines() const    { return aLines; }
        _FndLines&      GetLines()          { return aLines; }
    const SwTableBox*   GetBox() const      { return pBox; }
        SwTableBox*     GetBox()            { return pBox; }
    const _FndLine*     GetUpper() const    { return pUpper; }
        _FndLine*       GetUpper()          { return pUpper; }

    void MakeNewFrms( SwTable &rTable, const USHORT nNumber,
                                       const BOOL bBehind );
};


class _FndLine
{
    SwTableLine* pLine;
    _FndBoxes aBoxes;
    _FndBox* pUpper;
public:
    _FndLine(SwTableLine* pL, _FndBox* pFB=0) : pLine(pL), pUpper(pFB) {}
    const _FndBoxes&    GetBoxes() const    { return aBoxes; }
        _FndBoxes&      GetBoxes()          { return aBoxes; }
    const SwTableLine*  GetLine() const     { return pLine; }
        SwTableLine*    GetLine()           { return pLine; }
    const _FndBox*      GetUpper() const    { return pUpper; }
        _FndBox*        GetUpper()          { return pUpper; }

    void SetUpper( _FndBox* pUp ) { pUpper = pUp; }
};


struct _FndPara
{
    _FndBox* pFndBox;
    _FndLine* pFndLine;
    const SwSelBoxes& rBoxes;

    _FndPara( const SwSelBoxes& rBxs, _FndBox* pFB )
        : pFndBox( pFB ), rBoxes( rBxs ) {}
    _FndPara( const _FndPara& rPara, _FndBox* pFB )
        : pFndBox(pFB), pFndLine(rPara.pFndLine), rBoxes(rPara.rBoxes) {}
    _FndPara( const _FndPara& rPara, _FndLine* pFL )
        : pFndBox(rPara.pFndBox), pFndLine(pFL), rBoxes(rPara.rBoxes) {}
};

BOOL _FndBoxCopyCol( const SwTableBox*& rpBox, void* pPara );
BOOL _FndLineCopyCol( const SwTableLine*& rpLine, void* pPara );


} //namespace binfilter
#endif  //  _TBLSEL_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
