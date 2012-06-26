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

#ifndef SC_CONSOLI_HXX
#define SC_CONSOLI_HXX

#include <bf_svtools/bf_solar.h>

#include "global.hxx"
namespace binfilter {

class ScDocument;

// -----------------------------------------------------------------------

struct ScReferenceEntry             // ohne Constructor !
{
    USHORT  nCol;
    USHORT  nRow;
    USHORT  nTab;
};


//!     Delta-Wert fuer Daten benutzen?

class ScReferenceList           // ohne Constructor !
{
private:
    USHORT              nCount;
    USHORT              nFullSize;          // inkl. Fuell-Eintraege
    ScReferenceEntry*   pData;

public:
    void                    Init()                      { nCount=0; nFullSize=0; pData=NULL; }
    void                    Clear()                     { delete[] pData; }

    USHORT                  GetCount()                  { return nCount; }
    const ScReferenceEntry& GetEntry( USHORT nPos )     { return pData[nPos]; }
    void                    SetFullSize( USHORT nNew )  { nFullSize = nNew; }
};

// -----------------------------------------------------------------------


//
//  Reihenfolge:
//      1)  ScConsData anlegen
//      2)  Parameter (Size/Flags)
//      3)  AddFields fuer alle Bereiche (nur noetig bei bColByName oder bRowByName)
//      4)  DoneFields                   (      "                       "          )
//      5)  AddData fuer alle Bereiche
//          evtl. AddName nach jedem Bereich
//      6)  OutputToDocument
//

//! ab bestimmter Groesse ScDocument Struktur benutzen?


class ScConsData
{
private:
    ScSubTotalFunc      eFunction;
    BOOL                bReference;
    BOOL                bColByName;
    BOOL                bRowByName;
    BOOL                bSubTitles;
    USHORT              nColCount;
    USHORT              nRowCount;
    BOOL**              ppUsed;
    double**            ppSum;
    double**            ppCount;
    double**            ppSumSqr;
    ScReferenceList**   ppRefs;
    String**            ppColHeaders;
    String**            ppRowHeaders;
    USHORT              nDataCount;
    USHORT              nTitleCount;
    String**            ppTitles;
    USHORT**            ppTitlePos;
    BOOL                bCornerUsed;
    String              aCornerText;        // nur bei bColByName && bRowByName

public:
                ScConsData();
                ~ScConsData();

    void        SetSize( USHORT nCols, USHORT nRows );
    void        SetFlags( ScSubTotalFunc eFunc, BOOL bColName, BOOL bRowName, BOOL bRef );

    void        InitData(BOOL bDelete=TRUE);
    void        DeleteData();

    void        AddFields( ScDocument* pSrcDoc, USHORT nTab,
                            USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2 );
    void        DoneFields();

    void        AddData( ScDocument* pSrcDoc, USHORT nTab,
                            USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2 );
    void        AddName( const String& rName );

    void        OutputToDocument( ScDocument* pDestDoc, USHORT nCol, USHORT nRow, USHORT nTab );

    void        GetSize( USHORT& rCols, USHORT& rRows ) const;
};


} //namespace binfilter
#endif


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
