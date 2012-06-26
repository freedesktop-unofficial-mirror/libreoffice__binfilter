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
#ifndef _INDEX_HXX
#define _INDEX_HXX

#include <bf_svtools/bf_solar.h>

#include <limits.h>

#include <tools/rtti.hxx>               // for RTTI of SwIndexReg
/*N*/ #include <tools/debug.hxx> //for stripping
namespace binfilter {
#define INVALID_INDEX STRING_NOTFOUND

// Maximale Anzahl von Indizies im IndexArray (zum Abtesten auf Ueberlaeufe)
class SwIndex;
class SwIndexReg;

class SwIndex
{
    friend class SwIndexReg;

#ifdef DBG_UTIL
    static int nSerial;
    int MySerial;
#endif

    xub_StrLen  nIndex;
    SwIndexReg* pArray;
    SwIndex *pNext, *pPrev;

    SwIndex& ChgValue( const SwIndex& rIdx, xub_StrLen nNewValue );
    void Remove();                  // Ausketten

public:
    SwIndex( SwIndexReg * pReg, xub_StrLen nIdx = 0 );
    SwIndex( const SwIndex & );
    ~SwIndex() { Remove(); }

    inline xub_StrLen operator++();
    inline xub_StrLen operator++(int);
    inline xub_StrLen operator--(int);

    inline xub_StrLen operator+=( xub_StrLen );
    inline xub_StrLen operator+=( const SwIndex& );

    inline BOOL operator<( const SwIndex& ) const;
    inline BOOL operator<=( const SwIndex& ) const;
    inline BOOL operator>( const SwIndex& ) const;
    inline BOOL operator>=( const SwIndex& ) const;
    BOOL operator==( const SwIndex& rSwIndex ) const
    { return (nIndex == rSwIndex.nIndex) &&  (pArray == rSwIndex.pArray); }

    BOOL operator!=( const SwIndex& rSwIndex ) const
    { return (nIndex != rSwIndex.nIndex) ||  (pArray != rSwIndex.pArray); }

    BOOL operator<( xub_StrLen nWert ) const    { return nIndex <  nWert; }
    BOOL operator<=( xub_StrLen nWert ) const   { return nIndex <= nWert; }
    BOOL operator>( xub_StrLen nWert ) const    { return nIndex >  nWert; }
    BOOL operator>=( xub_StrLen nWert ) const   { return nIndex >= nWert; }
    BOOL operator==( xub_StrLen nWert ) const   { return nIndex == nWert; }
    BOOL operator!=( xub_StrLen nWert ) const   { return nIndex != nWert; }

    inline SwIndex& operator=( xub_StrLen );
    SwIndex& operator=( const SwIndex & );

    // gebe den Wert vom Index als xub_StrLen zurueck
    xub_StrLen GetIndex() const { return nIndex; }

    // ermoeglicht Zuweisungen ohne Erzeugen eines temporaeren
    // Objektes
    SwIndex &Assign(SwIndexReg *,xub_StrLen);

        // Herausgabe des Pointers auf das IndexArray,
        // (fuers RTTI am SwIndexReg)
    const SwIndexReg* GetIdxReg() const { return pArray; }
};

#undef inline

class SwIndexReg
{
    friend class SwIndex;
    const SwIndex *pFirst, *pLast, *pMiddle;

    // ein globales Array, in das Indizies verschoben werden, die mal
    // temporaer "ausgelagert" werden muessen; oder die zum Zeitpunkt des
    // anlegens kein gueltiges Array kennen (SwPaM/SwPosition!)
    friend void _InitCore();
    friend void _FinitCore();
    static SwIndexReg* pEmptyIndexArray;

protected:
    virtual void Update( const SwIndex & aPos, xub_StrLen nLen,
                        BOOL bNegativ = FALSE );


    BOOL HasAnyIndex() const { return 0 != pFirst; }

    // fuer das Move am RegArray:

public:
    SwIndexReg();
    virtual ~SwIndexReg();

    // rtti, abgeleitete moegens gleichtun oder nicht. Wenn sie es gleichtun
    // kann ueber das SwIndexReg typsicher gecastet werden.
    TYPEINFO();

    void SetDefMiddle( const SwIndex* pIdx ) { pMiddle = pIdx; }
    void MoveTo( SwIndexReg& rArr );
};


inline xub_StrLen SwIndex::operator++() {DBG_BF_ASSERT(0, "STRIP"); return 0;}
inline xub_StrLen SwIndex::operator++(int) {DBG_BF_ASSERT(0, "STRIP"); return 0;}
 inline xub_StrLen SwIndex::operator--(int)
 {
     xub_StrLen nOldIndex = nIndex;
     ChgValue( *this, nIndex-1 );
     return nOldIndex;
 }

inline xub_StrLen SwIndex::operator+=( xub_StrLen nWert )
{
    return ChgValue( *this, nIndex + nWert ).nIndex;
}
inline xub_StrLen SwIndex::operator+=( const  SwIndex& rIndex )
{
    return ChgValue( *this, nIndex + rIndex.nIndex ).nIndex;
}

inline BOOL SwIndex::operator<( const SwIndex& rIndex ) const
{
    return nIndex < rIndex.nIndex;
}
inline BOOL SwIndex::operator<=( const SwIndex& rIndex ) const
{
    return nIndex <= rIndex.nIndex;
}
inline BOOL SwIndex::operator>( const SwIndex& rIndex ) const
{
    return nIndex > rIndex.nIndex;
}
inline BOOL SwIndex::operator>=( const SwIndex& rIndex ) const
{
    return nIndex >= rIndex.nIndex;
}
inline SwIndex& SwIndex::operator=( xub_StrLen nWert )
{
   if( nIndex != nWert )
       ChgValue( *this, nWert );
   return *this;
}

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
