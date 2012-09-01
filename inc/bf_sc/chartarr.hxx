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

#ifndef SC_CHARTARR_HXX
#define SC_CHARTARR_HXX

#include <bf_svtools/bf_solar.h>

// -----------------------------------------------------------------------

#include "collect.hxx"
#include "rangelst.hxx"
class Table;
namespace binfilter {


class ScAddress;

class ScChartPositionMap
{
    friend class ScChartArray;

            ScAddress**         ppData;
            ScAddress**         ppColHeader;
            ScAddress**         ppRowHeader;
            ULONG               nCount;
            USHORT              nColCount;
            USHORT              nRowCount;

                                ScChartPositionMap( USHORT nChartCols, USHORT nChartRows,
                                    USHORT nColAdd,     // Header-Spalten
                                    USHORT nRowAdd,     // Header-Zeilen
                                    Table& rCols        // Table mit Col-Tables mit Address*
                                    );
                                ~ScChartPositionMap();  //! deletes all ScAddress*

            const ScAddress*    GetPosition( ULONG nIndex ) const
                                    {
                                        if ( nIndex < nCount )
                                            return ppData[ nIndex ];
                                        return NULL;
                                    }

                                // not implemented
                                ScChartPositionMap( const ScChartPositionMap& );
            ScChartPositionMap& operator=( const ScChartPositionMap& );

public:

            ULONG               GetCount() const { return nCount; }
            USHORT              GetColCount() const { return nColCount; }
            USHORT              GetRowCount() const { return nRowCount; }

            BOOL                IsValid( USHORT nCol, USHORT nRow ) const
                                    { return nCol < nColCount && nRow < nRowCount; }
                                // Daten spaltenweise
            ULONG               GetIndex( USHORT nCol, USHORT nRow ) const
                                    { return (ULONG) nCol * nRowCount + nRow; }

                                //! kann NULL sein und damit "kein Wert"
            const ScAddress*    GetPosition( USHORT nChartCol, USHORT nChartRow ) const
                                    {
                                        if ( IsValid( nChartCol, nChartRow ) )
                                            return ppData[ GetIndex( nChartCol, nChartRow ) ];
                                        return NULL;
                                    }
            const ScAddress*    GetColHeaderPosition( USHORT nChartCol ) const
                                    {
                                        if ( nChartCol < nColCount )
                                            return ppColHeader[ nChartCol ];
                                        return NULL;
                                    }
            const ScAddress*    GetRowHeaderPosition( USHORT nChartRow ) const
                                    {
                                        if ( nChartRow < nRowCount )
                                            return ppRowHeader[ nChartRow ];
                                        return NULL;
                                    }
};


enum ScChartGlue {
    SC_CHARTGLUE_NA,
    SC_CHARTGLUE_NONE,      // alte Mimik
    SC_CHARTGLUE_COLS,      // alte Mimik
    SC_CHARTGLUE_ROWS,
    SC_CHARTGLUE_BOTH
};

class ScDocument;
class ScMultipleReadHeader;
class SchMemChart;

class ScChartArray : public DataObject              // nur noch Parameter-Struct
{
    ScRangeListRef  aRangeListRef;
    String      aName;
    ScDocument* pDocument;
    ScChartPositionMap* pPositionMap;
    ScChartGlue eGlue;
    USHORT      nStartCol;
    USHORT      nStartRow;
    BOOL        bColHeaders;
    BOOL        bRowHeaders;
    BOOL        bDummyUpperLeft;
    BOOL        bValid;             // fuer Erzeugung aus SchMemChart

private:
    SchMemChart* CreateMemChartSingle();
    SchMemChart* CreateMemChartMulti();

    void        GlueState();        // zusammengefasste Bereiche
    void        CreatePositionMap();

public:
    ScChartArray( ScDocument* pDoc, const ScRangeListRef& rRangeList,
                    const String& rChartName );
    ScChartArray( const ScChartArray& rArr );
    ScChartArray( ScDocument* pDoc, SvStream& rStream, ScMultipleReadHeader& rHdr );
    ScChartArray( ScDocument* pDoc, const SchMemChart& rData );

    virtual ~ScChartArray();
    virtual DataObject* Clone() const{DBG_BF_ASSERT(0, "STRIP"); return NULL;}

    const ScRangeListRef&   GetRangeList() const { return aRangeListRef; }
    void    SetRangeList( const ScRangeListRef& rNew ) { aRangeListRef = rNew; }
    void    SetRangeList( const ScRange& rNew );
    void    AddToRangeList( const ScRange& rRange );
     void   AddToRangeList( const ScRangeListRef& rAdd );

    void    SetHeaders(BOOL bCol, BOOL bRow) { bColHeaders=bCol; bRowHeaders=bRow; }
    BOOL    HasColHeaders() const            { return bColHeaders; }
    BOOL    HasRowHeaders() const            { return bRowHeaders; }
    BOOL    IsValid() const                  { return bValid; }
    void    SetName(const String& rNew)      { aName = rNew; }
    const String& GetName() const            { return aName; }



    SchMemChart* CreateMemChart();
    void        SetExtraStrings( SchMemChart& rMem );

    void                    InvalidateGlue()
                                {
                                    eGlue = SC_CHARTGLUE_NA;
                                    if ( pPositionMap )
                                    {
                                        delete pPositionMap;
                                        pPositionMap = NULL;
                                    }
                                }
    const ScChartPositionMap*   GetPositionMap();

    static void CopySettings( SchMemChart& rDest, const SchMemChart& rSource );
};

class ScChartCollection : public Collection
{
public:
    ScChartCollection() : Collection( 4,4 ) {}
    ScChartCollection( const ScChartCollection& rColl ):
            Collection( rColl ) {}

    virtual DataObject* Clone() const{DBG_BF_ASSERT(0, "STRIP"); return NULL;}
    ScChartArray*       operator[](USHORT nIndex) const
                        { return (ScChartArray*)At(nIndex); }


    BOOL    Load( ScDocument* pDoc, SvStream& rStream );
};



} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
