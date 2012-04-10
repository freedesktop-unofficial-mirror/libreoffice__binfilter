/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

namespace binfilter
{

// -----------------------------------------------------------------------

static sal_Int32 ImplStringCompareWithoutZero( const STRCODE* pStr1, const STRCODE* pStr2,
                                               sal_Int32 nCount )
{
    sal_Int32 nRet = 0;
    while ( nCount &&
            ((nRet = ((sal_Int32)((STRCODEU)*pStr1))-((sal_Int32)((STRCODEU)*pStr2))) == 0) )
    {
        ++pStr1,
        ++pStr2,
        --nCount;
    }

    return nRet;
}

// =======================================================================

#ifdef DBG_UTIL
const char* DBGCHECKSTRING( const void* pString )
{
    STRING* p = (STRING*)pString;

    if ( p->GetBuffer()[p->Len()] != 0 )
        return "String damaged: aStr[nLen] != 0";

    return NULL;
}
#endif

// =======================================================================

static STRINGDATA* ImplAllocData( sal_Int32 nLen )
{
    // Dann kopiere die Daten
    STRINGDATA* pData   = (STRINGDATA*)rtl_allocateMemory( sizeof(STRINGDATA)+(nLen*sizeof( STRCODE )) );
    pData->mnRefCount   = 1;
    pData->mnLen        = nLen;
    pData->maStr[nLen]  = 0;
    return pData;
}

// -----------------------------------------------------------------------

static STRINGDATA* _ImplCopyData( STRINGDATA* pData )
{
    unsigned int    nSize       = sizeof(STRINGDATA)+(pData->mnLen*sizeof( STRCODE ));
    STRINGDATA*     pNewData    = (STRINGDATA*)rtl_allocateMemory( nSize );
    memcpy( pNewData, pData, nSize );
    pNewData->mnRefCount = 1;
    STRING_RELEASE((STRING_TYPE *)pData);
    return pNewData;
}

// -----------------------------------------------------------------------

inline void STRING::ImplCopyData()
{
    DBG_ASSERT( (mpData->mnRefCount != 0), "String::ImplCopyData() - RefCount == 0" );

    // ist es ein referenzierter String, dann die Daten abkoppeln
    if ( mpData->mnRefCount != 1 )
        mpData = _ImplCopyData( mpData );
}

// -----------------------------------------------------------------------

inline STRCODE* STRING::ImplCopyStringData( STRCODE* pStr )
{
    // Ist der Referenzzaehler groesser 0
    if ( mpData->mnRefCount != 1 ) {
        DBG_ASSERT( (pStr >= mpData->maStr) &&
                    ((pStr-mpData->maStr) < mpData->mnLen),
                    "ImplCopyStringData - pStr from other String-Instanz" );
        unsigned int nIndex = (unsigned int)(pStr-mpData->maStr);
        mpData = _ImplCopyData( mpData );
        pStr = mpData->maStr + nIndex;
    }
    return pStr;
}

// -----------------------------------------------------------------------

inline sal_Int32 ImplGetCopyLen( sal_Int32 nStrLen, sal_Int32 nCopyLen )
{
    OSL_ASSERT(nStrLen <= STRING_MAXLEN && nCopyLen <= STRING_MAXLEN);
    if ( nCopyLen > STRING_MAXLEN-nStrLen )
        nCopyLen = STRING_MAXLEN-nStrLen;
    return nCopyLen;
}

// =======================================================================

STRING::STRING()
    : mpData(NULL)
{
    DBG_CTOR( STRING, DBGCHECKSTRING );

    STRING_NEW((STRING_TYPE **)&mpData);
}

// -----------------------------------------------------------------------

STRING::STRING( const STRING& rStr )
{
    DBG_CTOR( STRING, DBGCHECKSTRING );
    DBG_CHKOBJ( &rStr, STRING, DBGCHECKSTRING );

    // Pointer auf die Daten des uebergebenen Strings setzen und
    // Referenzzaehler erhoehen
    STRING_ACQUIRE((STRING_TYPE *)rStr.mpData);
    mpData = rStr.mpData;
}

// -----------------------------------------------------------------------

STRING::STRING( const STRING& rStr, xub_StrLen nPos, xub_StrLen nLen )
: mpData( NULL )
{
    DBG_CTOR( STRING, DBGCHECKSTRING );
    DBG_CHKOBJ( &rStr, STRING, DBGCHECKSTRING );

    // Stringlaenge ermitteln
    if ( nPos > rStr.mpData->mnLen )
        nLen = 0;
    else
    {
        // Laenge korrigieren, wenn noetig
        sal_Int32 nMaxLen = rStr.mpData->mnLen-nPos;
        if ( nLen > nMaxLen )
            nLen = static_cast< xub_StrLen >(nMaxLen);
    }

    // Ist es kein leerer String
    if ( nLen )
    {
        // Reicht ein einfaches erhoehen des Referenzcounters
        if ( (nPos == 0) && (nLen == rStr.mpData->mnLen) )
        {
            STRING_ACQUIRE((STRING_TYPE *)rStr.mpData);
            mpData = rStr.mpData;
        }
        else
        {
            // Verwaltungsdaten anlegen und String kopieren
            mpData = ImplAllocData( nLen );
            memcpy( mpData->maStr, rStr.mpData->maStr+nPos, nLen*sizeof( STRCODE ) );
        }
    }
    else
    {
        STRING_NEW((STRING_TYPE **)&mpData);
    }
}

// -----------------------------------------------------------------------

STRING::STRING( const STRCODE* pCharStr )
    : mpData(NULL)
{
    DBG_CTOR( STRING, DBGCHECKSTRING );

    // Stringlaenge ermitteln
    // Bei diesem Ctor darf NULL uebergeben werden
    xub_StrLen nLen;
    if ( pCharStr )
        nLen = ImplStringLen( pCharStr );
    else
        nLen = 0;

    // Ist es kein leerer String
    if ( nLen )
    {
        // Verwaltungsdaten anlegen und String kopieren
        mpData = ImplAllocData( nLen );
        memcpy( mpData->maStr, pCharStr, nLen*sizeof( STRCODE ) );
    }
    else
    {
        STRING_NEW((STRING_TYPE **)&mpData);
    }
}

// -----------------------------------------------------------------------

STRING::~STRING()
{
    DBG_DTOR( STRING, DBGCHECKSTRING );

    // Daten loeschen
    STRING_RELEASE((STRING_TYPE *)mpData);
}

// -----------------------------------------------------------------------

STRING& STRING::Assign( const STRING& rStr )
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );
    DBG_CHKOBJ( &rStr, STRING, DBGCHECKSTRING );

    STRING_ACQUIRE((STRING_TYPE *)rStr.mpData);
    STRING_RELEASE((STRING_TYPE *)mpData);
    mpData = rStr.mpData;
    return *this;
}

// -----------------------------------------------------------------------

STRING& STRING::Assign( const STRCODE* pCharStr )
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );
    DBG_ASSERT( pCharStr, "String::Assign() - pCharStr is NULL" );

    // Stringlaenge ermitteln
    xub_StrLen nLen = ImplStringLen( pCharStr );

    if ( !nLen )
    {
        STRING_NEW((STRING_TYPE **)&mpData);
    }
    else
    {
        // Wenn String genauso lang ist, wie der String, dann direkt kopieren
        if ( (nLen == mpData->mnLen) && (mpData->mnRefCount == 1) )
            memcpy( mpData->maStr, pCharStr, nLen*sizeof( STRCODE ) );
        else
        {
            // Alte Daten loeschen
            STRING_RELEASE((STRING_TYPE *)mpData);

            // Daten initialisieren und String kopieren
            mpData = ImplAllocData( nLen );
            memcpy( mpData->maStr, pCharStr, nLen*sizeof( STRCODE ) );
        }
    }

    return *this;
}

// -----------------------------------------------------------------------

STRING& STRING::Append( const STRING& rStr )
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );
    DBG_CHKOBJ( &rStr, STRING, DBGCHECKSTRING );

    // Wenn String leer, dann reicht eine Zuweisung
    sal_Int32 nLen = mpData->mnLen;
    if ( !nLen )
    {
        STRING_ACQUIRE((STRING_TYPE *)rStr.mpData);
        STRING_RELEASE((STRING_TYPE *)mpData);
        mpData = rStr.mpData;
    }
    else
    {
        // Ueberlauf abfangen
        sal_Int32 nCopyLen = ImplGetCopyLen( nLen, rStr.mpData->mnLen );

        // Ist der uebergebene String kein Leerstring
        if ( nCopyLen )
        {
            // Neue Datenstruktur und neuen String erzeugen
            STRINGDATA* pNewData = ImplAllocData( nLen+nCopyLen );

            // String kopieren
            memcpy( pNewData->maStr, mpData->maStr, nLen*sizeof( STRCODE ) );
            memcpy( pNewData->maStr+nLen, rStr.mpData->maStr, nCopyLen*sizeof( STRCODE ) );

            // Alte Daten loeschen und Neue zuweisen
            STRING_RELEASE((STRING_TYPE *)mpData);
            mpData = pNewData;
        }
    }

    return *this;
}

// -----------------------------------------------------------------------

STRING& STRING::Append( const STRCODE* pCharStr )
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );
    DBG_ASSERT( pCharStr, "String::Append() - pCharStr is NULL" );

    // Stringlaenge ermitteln
    sal_Int32 nLen = mpData->mnLen;
    sal_Int32 nCopyLen = ImplStringLen( pCharStr );

    // Ueberlauf abfangen
    nCopyLen = ImplGetCopyLen( nLen, nCopyLen );

    // Ist es kein leerer String
    if ( nCopyLen )
    {
        // Neue Datenstruktur und neuen String erzeugen
        STRINGDATA* pNewData = ImplAllocData( nLen+nCopyLen );

        // String kopieren
        memcpy( pNewData->maStr, mpData->maStr, nLen*sizeof( STRCODE ) );
        memcpy( pNewData->maStr+nLen, pCharStr, nCopyLen*sizeof( STRCODE ) );

        // Alte Daten loeschen und Neue zuweisen
        STRING_RELEASE((STRING_TYPE *)mpData);
        mpData = pNewData;
    }

    return *this;
}

// -----------------------------------------------------------------------

STRING& STRING::Append( const STRCODE* pCharStr, xub_StrLen nCharLen )
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );
    DBG_ASSERT( pCharStr, "String::Append() - pCharStr is NULL" );

    if ( nCharLen == STRING_LEN )
        nCharLen = ImplStringLen( pCharStr );

#ifdef DBG_UTIL
    if ( DbgIsAssert() )
    {
        for ( xub_StrLen i = 0; i < nCharLen; i++ )
        {
            if ( !pCharStr[i] )
            {
                OSL_FAIL( "String::Append() : nLen is wrong" );
            }
        }
    }
#endif

    // Ueberlauf abfangen
    sal_Int32 nLen = mpData->mnLen;
    sal_Int32 nCopyLen = ImplGetCopyLen( nLen, nCharLen );

    // Ist es kein leerer String
    if ( nCopyLen )
    {
        // Neue Datenstruktur und neuen String erzeugen
        STRINGDATA* pNewData = ImplAllocData( nLen+nCopyLen );

        // String kopieren
        memcpy( pNewData->maStr, mpData->maStr, nLen*sizeof( STRCODE ) );
        memcpy( pNewData->maStr+nLen, pCharStr, nCopyLen*sizeof( STRCODE ) );

        // Alte Daten loeschen und Neue zuweisen
        STRING_RELEASE((STRING_TYPE *)mpData);
        mpData = pNewData;
    }

    return *this;
}

// -----------------------------------------------------------------------

STRING& STRING::Insert( const STRING& rStr, xub_StrLen nIndex )
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );
    DBG_CHKOBJ( &rStr, STRING, DBGCHECKSTRING );

    // Ueberlauf abfangen
    sal_Int32 nCopyLen = ImplGetCopyLen( mpData->mnLen, rStr.mpData->mnLen );

    // Ist der einzufuegende String ein Leerstring
    if ( !nCopyLen )
        return *this;

    // Index groesser als Laenge
    if ( nIndex > mpData->mnLen )
        nIndex = static_cast< xub_StrLen >(mpData->mnLen);

    // Neue Laenge ermitteln und neuen String anlegen
    STRINGDATA* pNewData = ImplAllocData( mpData->mnLen+nCopyLen );

    // String kopieren
    memcpy( pNewData->maStr, mpData->maStr, nIndex*sizeof( STRCODE ) );
    memcpy( pNewData->maStr+nIndex, rStr.mpData->maStr, nCopyLen*sizeof( STRCODE ) );
    memcpy( pNewData->maStr+nIndex+nCopyLen, mpData->maStr+nIndex,
            (mpData->mnLen-nIndex)*sizeof( STRCODE ) );

    // Alte Daten loeschen und Neue zuweisen
    STRING_RELEASE((STRING_TYPE *)mpData);
    mpData = pNewData;

    return *this;
}

// -----------------------------------------------------------------------

STRING& STRING::Insert( STRCODE c, xub_StrLen nIndex )
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );

    // Ist es kein 0-Character
    if ( !c || (mpData->mnLen == STRING_MAXLEN) )
        return *this;

    // Index groesser als Laenge
    if ( nIndex > mpData->mnLen )
        nIndex = static_cast< xub_StrLen >(mpData->mnLen);

    // Neue Laenge ermitteln und neuen String anlegen
    STRINGDATA* pNewData = ImplAllocData( mpData->mnLen+1 );

    // String kopieren
    memcpy( pNewData->maStr, mpData->maStr, nIndex*sizeof( STRCODE ) );
    pNewData->maStr[nIndex] = c;
    memcpy( pNewData->maStr+nIndex+1, mpData->maStr+nIndex,
            (mpData->mnLen-nIndex)*sizeof( STRCODE ) );

    // Alte Daten loeschen und Neue zuweisen
    STRING_RELEASE((STRING_TYPE *)mpData);
    mpData = pNewData;

    return *this;
}

// -----------------------------------------------------------------------

STRING& STRING::Replace( xub_StrLen nIndex, xub_StrLen nCount, const STRING& rStr )
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );
    DBG_CHKOBJ( &rStr, STRING, DBGCHECKSTRING );

    // Wenn Index groessergleich Laenge ist, dann ist es ein Append
    if ( nIndex >= mpData->mnLen )
    {
        Append( rStr );
        return *this;
    }

    // Ist es eine Zuweisung
    if ( (nIndex == 0) && (nCount >= mpData->mnLen) )
    {
        Assign( rStr );
        return *this;
    }

    // Reicht ein Erase
    sal_Int32 nStrLen = rStr.mpData->mnLen;
    if ( !nStrLen )
        return Erase( nIndex, nCount );

    // nCount darf nicht ueber das Stringende hinnausgehen
    if ( nCount > mpData->mnLen - nIndex )
        nCount = static_cast< xub_StrLen >(mpData->mnLen-nIndex);

    // Reicht ein Insert
    if ( !nCount )
        return Insert( rStr, nIndex );

    // Reicht eine zeichenweise Zuweisung
    if ( nCount == nStrLen )
    {
        ImplCopyData();
        memcpy( mpData->maStr+nIndex, rStr.mpData->maStr, nCount*sizeof( STRCODE ) );
        return *this;
    }

    // Ueberlauf abfangen
    nStrLen = ImplGetCopyLen( mpData->mnLen-nCount, nStrLen );

    // Neue Daten anlegen
    STRINGDATA* pNewData = ImplAllocData( mpData->mnLen-nCount+nStrLen );

    // String kopieren
    memcpy( pNewData->maStr, mpData->maStr, nIndex*sizeof( STRCODE ) );
    memcpy( pNewData->maStr+nIndex, rStr.mpData->maStr, nStrLen*sizeof( STRCODE ) );
    memcpy( pNewData->maStr+nIndex+nStrLen, mpData->maStr+nIndex+nCount,
            (mpData->mnLen-nIndex-nCount+1)*sizeof( STRCODE ) );

    // Alte Daten loeschen und Neue zuweisen
    STRING_RELEASE((STRING_TYPE *)mpData);
    mpData = pNewData;

    return *this;
}

// -----------------------------------------------------------------------

STRING& STRING::Erase( xub_StrLen nIndex, xub_StrLen nCount )
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );

    // Ist der Index ausserhalb des Strings oder ist nCount == 0
    if ( (nIndex >= mpData->mnLen) || !nCount )
        return *this;

    // nCount darf nicht ueber das Stringende hinnausgehen
    if ( nCount > mpData->mnLen - nIndex )
        nCount = static_cast< xub_StrLen >(mpData->mnLen-nIndex);

    // Ist das Ergebnis kein Leerstring
    if ( mpData->mnLen - nCount )
    {
        // Neue Daten anlegen
        STRINGDATA* pNewData = ImplAllocData( mpData->mnLen-nCount );

        // String kopieren
        memcpy( pNewData->maStr, mpData->maStr, nIndex*sizeof( STRCODE ) );
        memcpy( pNewData->maStr+nIndex, mpData->maStr+nIndex+nCount,
                (mpData->mnLen-nIndex-nCount+1)*sizeof( STRCODE ) );

        // Alte Daten loeschen und Neue zuweisen
        STRING_RELEASE((STRING_TYPE *)mpData);
        mpData = pNewData;
    }
    else
    {
        STRING_NEW((STRING_TYPE **)&mpData);
    }

    return *this;
}

// -----------------------------------------------------------------------

STRING& STRING::ToLowerAscii()
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );

    sal_Int32 nIndex = 0;
    sal_Int32 nLen = mpData->mnLen;
    STRCODE*    pStr = mpData->maStr;
    while ( nIndex < nLen )
    {
        // Ist das Zeichen zwischen 'A' und 'Z' dann umwandeln
        if ( (*pStr >= 65) && (*pStr <= 90) )
        {
            // Daten kopieren, wenn noetig
            pStr = ImplCopyStringData( pStr );
            *pStr += 32;
        }

        ++pStr,
        ++nIndex;
    }

    return *this;
}

// -----------------------------------------------------------------------

sal_Bool STRING::Equals( const STRING& rStr ) const
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );
    DBG_CHKOBJ( &rStr, STRING, DBGCHECKSTRING );

    // Sind die Daten gleich
    if ( mpData == rStr.mpData )
        return sal_True;

    // Gleiche Laenge
    if ( mpData->mnLen != rStr.mpData->mnLen )
        return sal_False;

    // String vergleichen
    return (ImplStringCompareWithoutZero( mpData->maStr, rStr.mpData->maStr, mpData->mnLen ) == 0);
}

// -----------------------------------------------------------------------

xub_StrLen STRING::Search( STRCODE c, xub_StrLen nIndex ) const
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );

    sal_Int32       nLen = mpData->mnLen;
    const STRCODE*  pStr = mpData->maStr;
    pStr += nIndex;
    while ( nIndex < nLen )
    {
        if ( *pStr == c )
            return nIndex;
        ++pStr,
        ++nIndex;
    }

    return STRING_NOTFOUND;
}

// -----------------------------------------------------------------------

xub_StrLen STRING::Search( const STRING& rStr, xub_StrLen nIndex ) const
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );
    DBG_CHKOBJ( &rStr, STRING, DBGCHECKSTRING );

    sal_Int32 nLen = mpData->mnLen;
    sal_Int32 nStrLen = rStr.mpData->mnLen;

    // Falls die Laenge des uebergebenen Strings 0 ist oder der Index
    // hinter dem String liegt, dann wurde der String nicht gefunden
    if ( !nStrLen || (nIndex >= nLen) )
        return STRING_NOTFOUND;

    const STRCODE* pStr1 = mpData->maStr;
    pStr1 += nIndex;

    if ( nStrLen == 1 )
    {
        STRCODE cSearch = rStr.mpData->maStr[0];
        while ( nIndex < nLen )
        {
            if ( *pStr1 == cSearch )
                return nIndex;
            ++pStr1,
            ++nIndex;
        }
    }
    else
    {
        const STRCODE* pStr2 = rStr.mpData->maStr;

        // Nur innerhalb des Strings suchen
        while ( nLen - nIndex >= nStrLen )
        {
            // Stimmt der String ueberein
            if ( ImplStringCompareWithoutZero( pStr1, pStr2, nStrLen ) == 0 )
                return nIndex;
            ++pStr1,
            ++nIndex;
        }
    }

    return STRING_NOTFOUND;
}

// -----------------------------------------------------------------------

xub_StrLen STRING::Search( const STRCODE* pCharStr, xub_StrLen nIndex ) const
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );

    sal_Int32 nLen = mpData->mnLen;
    xub_StrLen nStrLen  = ImplStringLen( pCharStr );

    // Falls die Laenge des uebergebenen Strings 0 ist oder der Index
    // hinter dem String liegt, dann wurde der String nicht gefunden
    if ( !nStrLen || (nIndex >= nLen) )
        return STRING_NOTFOUND;

    const STRCODE* pStr = mpData->maStr;
    pStr += nIndex;

    if ( nStrLen == 1 )
    {
        STRCODE cSearch = *pCharStr;
        while ( nIndex < nLen )
        {
            if ( *pStr == cSearch )
                return nIndex;
            ++pStr,
            ++nIndex;
        }
    }
    else
    {
        // Nur innerhalb des Strings suchen
        while ( nLen - nIndex >= nStrLen )
        {
            // Stimmt der String ueberein
            if ( ImplStringCompareWithoutZero( pStr, pCharStr, nStrLen ) == 0 )
                return nIndex;
            ++pStr,
            ++nIndex;
        }
    }

    return STRING_NOTFOUND;
}

// -----------------------------------------------------------------------

xub_StrLen STRING::GetTokenCount( STRCODE cTok ) const
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );

    // Leerer String: TokenCount per Definition 0
    if ( !mpData->mnLen )
        return 0;

    xub_StrLen      nTokCount       = 1;
    sal_Int32       nLen            = mpData->mnLen;
    const STRCODE*  pStr            = mpData->maStr;
    sal_Int32       nIndex          = 0;
    while ( nIndex < nLen )
    {
        // Stimmt das Tokenzeichen ueberein, dann erhoehe TokCount
        if ( *pStr == cTok )
            ++nTokCount;
        ++pStr,
        ++nIndex;
    }

    return nTokCount;
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
