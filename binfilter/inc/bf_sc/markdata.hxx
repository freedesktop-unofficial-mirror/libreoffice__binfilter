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

#ifndef SC_MARKDATA_HXX
#define SC_MARKDATA_HXX

#include <bf_svtools/bf_solar.h>

#include "global.hxx"
namespace binfilter {

class ScMarkArray;
class ScRangeList;

//!     todo:
//!     Es muss auch die Moeglichkeit geben, MarkArrays pro Tabelle zu halten,
//!     damit "alle suchen" ueber mehrere Tabellen wieder funktioniert!


class ScMarkData
{
private:
    ScRange         aMarkRange;             // Bereich
    ScRange         aMultiRange;            // maximaler Bereich insgesamt
    ScMarkArray*    pMultiSel;              // Mehrfachselektion
    BOOL            bTabMarked[MAXTAB+1];   // Tabelle selektiert
    BOOL            bMarked;                // Rechteck markiert
    BOOL            bMultiMarked;           // mehrfach markiert

    BOOL            bMarking;               // Bereich wird aufgezogen -> kein MarkToMulti
    BOOL            bMarkIsNeg;             // Aufheben bei Mehrfachselektion

public:
                ScMarkData();
                ScMarkData(const ScMarkData& rData);
                ~ScMarkData();


    void        ResetMark();
    void        SetMarkArea( const ScRange& rRange );

    void        SetMultiMarkArea( const ScRange& rRange, BOOL bMark = TRUE );

    void        MarkToMulti();
    void        MarkToSimple();

    BOOL        IsMarked() const                { return bMarked; }
    BOOL        IsMultiMarked() const           { return bMultiMarked; }

    void        GetMarkArea( ScRange& rRange ) const;
    void        GetMultiMarkArea( ScRange& rRange ) const;


    void        SelectTable( USHORT nTab, BOOL bNew )       { bTabMarked[nTab] = bNew; }
    BOOL        GetTableSelect( USHORT nTab ) const         { return bTabMarked[nTab]; }

    void        SelectOneTable( USHORT nTab );
    USHORT      GetSelectCount() const;
    void        SetMarkNegative( BOOL bFlag )   { bMarkIsNeg = bFlag; }
    BOOL        IsMarkNegative() const          { return bMarkIsNeg;  }
    void        SetMarking( BOOL bFlag )        { bMarking = bFlag;   }
    BOOL        GetMarkingFlag() const          { return bMarking;    }

    //  fuer FillInfo / Document etc.
    const ScMarkArray* GetArray() const         { return pMultiSel; }

    BOOL        IsCellMarked( USHORT nCol, USHORT nRow, BOOL bNoSimple = FALSE ) const;
    void        FillRangeListWithMarks( ScRangeList* pList, BOOL bClear ) const;

    void        MarkFromRangeList( const ScRangeList& rList, BOOL bReset );


    BOOL        IsAllMarked( const ScRange& rRange ) const;     // Multi

    BOOL        HasMultiMarks( USHORT nCol ) const;
    BOOL        HasAnyMultiMarks() const;
};



} //namespace binfilter
#endif


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
