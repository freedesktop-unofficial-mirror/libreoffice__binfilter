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

/*
    WICHTIG:
    Folgende Reihenfolge beim Aufbau der Pivot-Tabelle unbedingt einzuhalten:

    pPivot->SetColFields(aColArr, aColCount)
    pPivot->SetRowFields(aRowArr, aRowCount)
    pPivot->SetDataFields(aDataArr, aDataCount)
    if (pPivot->CreateData())
    {
        pPivotDrawData();
        pPivotReleaseData();
    }

    ausserdem ist sicherzustellen, dass entweder das ColArr oder das RowArr
    einen PivotDataField Eintrag enthalten

*/


#ifndef SC_PIVOT_HXX
#define SC_PIVOT_HXX

#include <bf_svtools/bf_solar.h>

#include <global.hxx>


#include "collect.hxx"

#define PIVOT_DATA_FIELD        (MAXCOL + 1)
#define PIVOT_FUNC_REF          (MAXCOL + 1)

#define PIVOT_STYLE_INNER       0
#define PIVOT_STYLE_RESULT      1
#define PIVOT_STYLE_CATEGORY    2
#define PIVOT_STYLE_TITLE       3
#define PIVOT_STYLE_FIELDNAME   4
#define PIVOT_STYLE_TOP         5
class SvStream;
namespace binfilter {
class SubTotal;
class ScDocument;
class ScUserListData;
class ScMultipleReadHeader;
class ScProgress;

struct PivotColRef
{
    USHORT nDataIndex;
    USHORT nRecCount;
    USHORT nFuncMask;
    USHORT nIndex;

    PivotColRef()
    {
        nDataIndex = nRecCount = nIndex = 0;
        nFuncMask = PIVOT_FUNC_NONE;
    }
};

typedef PivotField          PivotFieldArr[PIVOT_MAXFIELD];

class PivotStrCollection : public StrCollection
{
    ScUserListData* pUserData;
public:
    PivotStrCollection(USHORT nLim = 4, USHORT nDel = 4, BOOL bDup = FALSE) :
                        StrCollection   ( nLim, nDel, bDup ),
                        pUserData       (NULL) { }
    PivotStrCollection(const PivotStrCollection& rPivotStrCollection) :
                        StrCollection   ( rPivotStrCollection ),
                        pUserData       ( rPivotStrCollection.pUserData) {}

    virtual short       Compare(DataObject* pKey1, DataObject* pKey2) const;

    TypedStrData*       operator[]( const USHORT nIndex) const
                            { return (TypedStrData*)At(nIndex); }
            void        SetUserData(ScUserListData* pData)
                            { pUserData = pData; }
    const   String&     GetString(USHORT nIndex)
                            { return ((TypedStrData*)At(nIndex))->GetString(); }
            short       GetIndex(TypedStrData* pData) const;
};

class ScPivot : public DataObject
{
    ScDocument*         pDoc;
    ScQueryParam        aQuery;
    BOOL                bHasHeader;

    BOOL                bIgnoreEmpty;           // Flags aus Dialog
    BOOL                bDetectCat;
    BOOL                bMakeTotalCol;
    BOOL                bMakeTotalRow;

    String              aName;
    String              aTag;
    USHORT              nColNameCount;
    String*             pColNames;              // Array

    USHORT              nSrcCol1;
    USHORT              nSrcRow1;
    USHORT              nSrcCol2;
    USHORT              nSrcRow2;
    USHORT              nSrcTab;

    USHORT              nDestCol1;
    USHORT              nDestRow1;
    USHORT              nDestCol2;
    USHORT              nDestRow2;
    USHORT              nDestTab;

    USHORT              nDataStartCol;
    USHORT              nDataStartRow;

    short               nColCount;
    short               nRowCount;
    short               nDataCount;

    PivotFieldArr       aColArr;
    PivotFieldArr       aRowArr;
    PivotFieldArr       aDataArr;

    PivotStrCollection* pColList[PIVOT_MAXFIELD];       // pro Zeile alle Eintraege
    PivotStrCollection* pRowList[PIVOT_MAXFIELD];
    PivotStrCollection* pDataList;                      // Shortcut auf Col/RowList mit Daten

    SubTotal**          ppDataArr;
    short               nDataColCount;
    short               nDataRowCount;
    short               nRowIndex;
    short               nColIndex;
    short               nDataIndex;
    short               nRecCount;

    PivotColRef*        pColRef;

    BOOL                bValidArea;
    BOOL                bDataAtCol;

public:
    ScPivot(ScDocument* pDocument);
    ScPivot(const ScPivot& rPivot);
    ~ScPivot();

    virtual DataObject* Clone() const;


    BOOL        Load(SvStream& rStream, ScMultipleReadHeader& rHdr );

    void        SetQuery(const ScQueryParam& rQuery);
    void        GetQuery(ScQueryParam& rQuery) const;

    void        SetHeader(BOOL bHeader);
    void        SetIgnoreEmpty(BOOL bIgnore);
    BOOL        GetIgnoreEmpty() const;
    void        SetDetectCat(BOOL bDetect);
    BOOL        GetDetectCat() const;
    void        SetMakeTotalCol(BOOL bSet);
    BOOL        GetMakeTotalCol() const;
    void        SetMakeTotalRow(BOOL bSet);
    BOOL        GetMakeTotalRow() const;

    void            SetName(const String& rNew);
    const String&   GetName() const;
    void            SetTag(const String& rNew);
    const String&   GetTag() const;

    void        SetSrcArea(USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2, USHORT nTab);
    void        GetSrcArea(USHORT& rCol1, USHORT& rRow1, USHORT& rCol2, USHORT& rRow2, USHORT& rTab) const;
    ScRange     GetSrcArea() const;

    void        SetDestPos(USHORT nCol, USHORT nRow, USHORT nTab);
    void        GetDestArea(USHORT& rCol1, USHORT& rRow1, USHORT& rCol2, USHORT& rRow2, USHORT& rTab) const;
    ScRange     GetDestArea() const;

    void        SetColFields(const PivotField* pFieldArr, short nCount);
     void       GetColFields(PivotField* pFieldArr, short& rCount) const;
    short       GetColFieldCount() const    { return nColCount; }

    void        SetRowFields(const PivotField* pFieldArr, short nCount);
    void        GetRowFields(PivotField* pFieldArr, short& rCount) const;
    short       GetRowFieldCount() const    { return nRowCount; }

    void        SetDataFields(const PivotField* pFieldArr, short nCount);
    void        GetDataFields(PivotField* pFieldArr, short& rCount) const;

    void        GetParam( ScPivotParam& rParam, ScQueryParam& rQuery, ScArea& rSrcArea ) const;
    void        SetParam( const ScPivotParam& rParam, const ScQueryParam& rQuery,
                            const ScArea& rSrcArea );

    BOOL        CreateData(BOOL bKeepDest = FALSE);
    void        ReleaseData();


                //  Referenz-Anpassung:

    void        MoveSrcArea( USHORT nNewCol, USHORT nNewRow, USHORT nNewTab );
    void        MoveDestArea( USHORT nNewCol, USHORT nNewRow, USHORT nNewTab );

private:
    BOOL    CreateFields();
    void    CreateFieldData();
    void    CalcArea();

    USHORT  GetCategoryRow( USHORT nCol, USHORT nRow );
};

//------------------------------------------------------------------------
class ScPivotCollection : public Collection
{

private:
    ScDocument* pDoc;
public:
    ScPivotCollection(USHORT nLim = 4, USHORT nDel = 4, ScDocument* pDocument = NULL) :
                    Collection  ( nLim, nDel),
                    pDoc        ( pDocument ) {}
    ScPivotCollection(const ScPivotCollection& rScPivotCollection) :
                    Collection  ( rScPivotCollection ),
                    pDoc        ( rScPivotCollection.pDoc ) {}

            ScPivot*    operator[]( const USHORT nIndex) const {return (ScPivot*)At(nIndex);}

    BOOL    Load( SvStream& rStream );
    BOOL Store( SvStream& ) const {return FALSE;}

    void    UpdateReference(UpdateRefMode eUpdateRefMode,
                                USHORT nCol1, USHORT nRow1, USHORT nTab1,
                                USHORT nCol2, USHORT nRow2, USHORT nTab2,
                                short nDx, short nDy, short nDz );


    String  CreateNewName( USHORT nMin = 1 ) const;
};

//------------------------------------------------------------------------
struct LabelData
{
    String* pStrColName;
    short   nCol;
    BOOL    bIsValue; // Summe oder Anzahl im Data-Feld
    USHORT  nFuncMask;


        LabelData( const String&    rColName,
                   short            nColumn,
                   BOOL             bVal,
                   USHORT           nMask = PIVOT_FUNC_NONE )
            :   nCol        (nColumn),
                bIsValue    (bVal),
                nFuncMask   (nMask)
            { pStrColName = new String( rColName ); }

        LabelData( const LabelData& rCpy )
            :   nCol        (rCpy.nCol),
                bIsValue    (rCpy.bIsValue),
                nFuncMask   (rCpy.nFuncMask)
            { pStrColName = new String( *(rCpy.pStrColName) ); }

        ~LabelData()
            { delete pStrColName; }

    LabelData& operator=( const LabelData& r )
        {
            nCol        = r.nCol;
            bIsValue    = r.bIsValue;
            nFuncMask   = r.nFuncMask;
            pStrColName = new String( *(r.pStrColName) );

            return *this;
        }
};


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
