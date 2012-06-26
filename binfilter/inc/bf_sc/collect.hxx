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

#ifndef SC_COLLECT_HXX
#define SC_COLLECT_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_tools/string.hxx>

#include <limits.h>
class SvStream;
namespace binfilter {

#define MAXCOLLECTIONSIZE       16384
#define MAXDELTA                1024
#define SCPOS_INVALID           USHRT_MAX

#define SC_STRTYPE_VALUE        0
#define SC_STRTYPE_STANDARD     1

class ScDocument;

class DataObject
{
public:
                            DataObject() {}
    virtual                 ~DataObject();
    virtual DataObject*     Clone() const = 0;
};

class Collection : public DataObject
{
protected:
    USHORT          nCount;
    USHORT          nLimit;
    USHORT          nDelta;
    DataObject**    pItems;
public:
                        Collection(USHORT nLim = 4, USHORT nDel = 4);
                        Collection(const Collection& rCollection);
    virtual             ~Collection();

    virtual DataObject* Clone() const   { return NULL; }    // DBG_BF_ASSERT

            void        AtFree(USHORT nIndex);
            void        Free(DataObject* pDataObject);
            void        FreeAll();

            BOOL        AtInsert(USHORT nIndex, DataObject* pDataObject);
    virtual BOOL        Insert(DataObject* pDataObject);

            DataObject* At(USHORT nIndex) const;
    virtual USHORT      IndexOf(DataObject* pDataObject) const;
            USHORT      GetCount() const { return nCount; }

            DataObject* operator[]( const USHORT nIndex) const {return At(nIndex);}
            Collection& operator=( const Collection& rCol );
};


class SortedCollection : public Collection
{
private:
    BOOL    bDuplicates;
protected:
                        // fuer StrCollection Load/Store
            void        SetDups( BOOL bVal ) { bDuplicates = bVal; }
            BOOL        IsDups() const { return bDuplicates; }
public:
                        SortedCollection(USHORT nLim = 4, USHORT nDel = 4, BOOL bDup = FALSE);
                        SortedCollection(const SortedCollection& rSortedCollection) :
                            Collection(rSortedCollection),
                            bDuplicates(rSortedCollection.bDuplicates) {}

    virtual short       Compare(DataObject* pKey1, DataObject* pKey2) const = 0;
            BOOL        Search(DataObject* pDataObject, USHORT& rIndex) const;
    virtual BOOL        Insert(DataObject* pDataObject);

};



//------------------------------------------------------------------------
class StrData : public DataObject
{
friend class StrCollection;
    String aStr;
public:
                        StrData(const String& rStr) : aStr(rStr) {}
                        StrData(const StrData& rData) : DataObject(rData), aStr(rData.aStr) {}
    virtual DataObject* Clone() const;
    const String&       GetString() const { return aStr; }
    // SetString nur, wenn StrData nicht in StrCollection ist! !!!
    // z.B. fuer Searcher
    void                SetString( const String& rNew ) { aStr = rNew; }
};

//------------------------------------------------------------------------


class StrCollection : public SortedCollection
{
public:
    StrCollection(USHORT nLim = 4, USHORT nDel = 4, BOOL bDup = FALSE) :
                        SortedCollection    ( nLim, nDel, bDup ) {}
    StrCollection(const StrCollection& rStrCollection) :
                        SortedCollection    ( rStrCollection ) {}

    virtual DataObject* Clone() const { return NULL; }  // DBG_BF_ASSERT
            StrData*    operator[]( const USHORT nIndex) const {return (StrData*)At(nIndex);}
    virtual short       Compare(DataObject* pKey1, DataObject* pKey2) const;

/*N*/           void        Load( SvStream& );
/*N*/   void  Store( SvStream& ) const {}
};

//------------------------------------------------------------------------
// TypedStrCollection: wie StrCollection, nur, dass Zahlen vor Strings
//                     sortiert werden

class TypedStrData : public DataObject
{
public:
            TypedStrData( const String& rStr, double nVal = 0.0,
                          USHORT nType = SC_STRTYPE_STANDARD )
                : aStrValue(rStr),
                  nValue(nVal),
                  nStrType(nType) {}

            TypedStrData( ScDocument* pDoc, USHORT nCol, USHORT nRow, USHORT nTab,
                            BOOL bAllStrings );

            TypedStrData( const TypedStrData& rCpy )
                : DataObject(rCpy),
                  aStrValue(rCpy.aStrValue),
                  nValue(rCpy.nValue),
                  nStrType(rCpy.nStrType) {}

    virtual DataObject* Clone() const;

    const String&       GetString() const { return aStrValue; }

private:
    friend class PivotStrCollection;

    String  aStrValue;
    double  nValue;
    USHORT  nStrType;           // 0 = Value
};

} //namespace binfilter
#endif


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
