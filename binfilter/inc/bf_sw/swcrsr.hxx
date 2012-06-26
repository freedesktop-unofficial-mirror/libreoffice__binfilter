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
#ifndef _SWCRSR_HXX
#define _SWCRSR_HXX

#include <bf_svtools/bf_solar.h>

#include <pam.hxx>
#include <tblsel.hxx>
#include <cshtyp.hxx>
namespace com { namespace sun { namespace star { namespace util {
    struct SearchOptions;
} } } }

namespace binfilter {


class SwShellCrsr;
class SwShellTableCrsr;
class SwTableCursor;
class SwUnoCrsr;
class SwUnoTableCrsr;
struct _SwCursor_SavePos;



// ein Basis-Struktur fuer die Parameter der Find-Methoden
// return - Werte vom Found-Aufruf.
const int FIND_NOT_FOUND    = 0;
const int FIND_FOUND        = 1;
const int FIND_NO_RING      = 2;

struct SwFindParas
{
    virtual int Find( SwPaM*, SwMoveFn, const SwPaM*, bool ) = 0;
    virtual int IsReplaceMode() const = 0;

protected:
    ~SwFindParas() {}
};

enum SwCursorSelOverFlags
{
    SELOVER_NONE                = 0x00,
    SELOVER_CHECKNODESSECTION   = 0x01,
    SELOVER_TOGGLE              = 0x02,
    SELOVER_ENABLEREVDIREKTION  = 0x04,
    SELOVER_CHANGEPOS           = 0x08
};

class SwCursor : public SwPaM
{
    friend class SwCrsrSaveState;

    _SwCursor_SavePos* pSavePos;
    BYTE nCursorBidiLevel;              // bidi level of the cursor

protected:
    virtual _SwCursor_SavePos* CreateNewSavePos() const;
    void SaveState();
    void RestoreState();

    const _SwCursor_SavePos* GetSavePos() const { return pSavePos; }

public:
    SwCursor( const SwPosition &rPos, SwPaM* pRing = 0 );
    virtual ~SwCursor();


    virtual operator SwShellCrsr* ()        { return NULL; }   // DBG_BF_ASSERT
    virtual operator SwShellTableCrsr* ()   { return NULL; }   // DBG_BF_ASSERT
    virtual operator SwTableCursor* ()      { return NULL; }   // DBG_BF_ASSERT
    virtual operator SwUnoCrsr* ()          { return NULL; }   // DBG_BF_ASSERT
    virtual operator SwUnoTableCrsr* ()     { return NULL; }   // DBG_BF_ASSERT

    inline operator const SwShellCrsr* () const;
    inline operator const SwShellTableCrsr* () const;
    inline operator const SwTableCursor* () const;
    inline operator const SwUnoCrsr* () const;
    inline operator const SwUnoTableCrsr* () const;

    virtual void SaveTblBoxCntnt( const SwPosition* = NULL ) {} // DBG_BF_ASSERT

    bool LeftRight( BOOL bLeft, USHORT nCnt, USHORT nMode, BOOL bAllowVisual,
                        BOOL bInsertCrsr );

    bool Left( USHORT nCnt, USHORT nMode, BOOL bAllowVisual = FALSE )
                                    { return LeftRight( TRUE, nCnt, nMode, bAllowVisual, FALSE ); }
    bool Right( USHORT nCnt, USHORT nMode, BOOL bAllowVisual = FALSE )
                                    { return LeftRight( FALSE, nCnt, nMode, bAllowVisual, FALSE ); }

    bool MovePara( SwWhichPara, SwPosPara );
    bool MoveSection( SwWhichSection, SwPosSection );
    bool MoveTable( SwWhichTable, SwPosTable );


    // gibt es eine Selection vom Content in die Tabelle
    // Return Wert gibt an, ob der Crsr auf der alten Position verbleibt
    virtual bool IsSelOvr( int eFlags =
                                ( SELOVER_CHECKNODESSECTION |
                                  SELOVER_TOGGLE | SELOVER_CHANGEPOS ));
    virtual bool IsInProtectTable( bool bMove = FALSE,
                                        bool bChgCrsr = TRUE );


    // TRUE: an die Position kann der Cursor gesetzt werden
    virtual bool IsAtValidPos( BOOL = TRUE ) const { return false; } // DBG_BF_ASSERT

    // darf der Cursor in ReadOnlyBereiche?
    bool IsReadOnlyAvailable() const;

    BYTE GetCrsrBidiLevel() const { return nCursorBidiLevel; }
    void SetCrsrBidiLevel( BYTE nNewLevel ) { nCursorBidiLevel = nNewLevel; }

    DECL_FIXEDMEMPOOL_NEWDEL( SwCursor )
};


class SwCrsrSaveState
{
    SwCursor& rCrsr;
public:
    SwCrsrSaveState( SwCursor& rC ) : rCrsr( rC ) { rC.SaveState(); }
    ~SwCrsrSaveState() { rCrsr.RestoreState(); }
};

struct _SwCursor_SavePos
{
    ULONG nNode;
    xub_StrLen nCntnt;
    _SwCursor_SavePos* pNext;

    _SwCursor_SavePos( const SwCursor& rCrsr )
        : nNode( rCrsr.GetPoint()->nNode.GetIndex() ),
        nCntnt( rCrsr.GetPoint()->nContent.GetIndex() ),
        pNext( 0 )
    {}
    virtual ~_SwCursor_SavePos() {}

    DECL_FIXEDMEMPOOL_NEWDEL( _SwCursor_SavePos )
};



class SwTableCursor : public virtual SwCursor
{

protected:
    ULONG nTblPtNd, nTblMkNd;
    xub_StrLen nTblPtCnt, nTblMkCnt;
    SwSelBoxes aSelBoxes;
    BOOL bChg : 1;
    BOOL bParked : 1;       // Tabellen-Cursor wurde geparkt

public:
    SwTableCursor( SwTableCursor& );
    virtual ~SwTableCursor();

    virtual operator SwTableCursor* ();

    void DeleteBox( USHORT nPos ) { aSelBoxes.Remove( nPos ); bChg = TRUE; }
     USHORT GetBoxesCount() const { return aSelBoxes.Count(); }
     const SwSelBoxes& GetBoxes() const { return aSelBoxes; }
};


// --------------------------- inline Methoden ----------------------

inline SwCursor::operator const SwShellCrsr* () const
{
    return (SwShellCrsr*)*((SwCursor*)this);
}

inline SwCursor::operator const SwShellTableCrsr* () const
{
    return (SwShellTableCrsr*)*((SwCursor*)this);
}

inline SwCursor::operator const SwTableCursor* () const
{
    return (SwTableCursor*)*((SwCursor*)this);
}

inline SwCursor::operator const SwUnoCrsr* () const
{
    return (SwUnoCrsr*)*((SwCursor*)this);
}

inline SwCursor::operator const SwUnoTableCrsr* () const
{
    return (SwUnoTableCrsr*)*((SwCursor*)this);
}


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
