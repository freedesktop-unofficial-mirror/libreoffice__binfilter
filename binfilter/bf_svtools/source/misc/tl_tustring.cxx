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


#include <string.h>

#include "boost/static_assert.hpp"

#include <osl/interlck.h>
#include <rtl/alloc.h>
#include <rtl/memory.h>
#include <rtl/tencinfo.h>
#include <rtl/instance.hxx>

#include <bf_tools/string.hxx>
#include <impstrg.hxx>

#include <tools/debug.hxx>

namespace binfilter
{

// =======================================================================

DBG_NAME( UniString )
DBG_NAMEEX( ByteString )

// -----------------------------------------------------------------------

#define STRCODE         sal_Unicode
#define STRCODEU        sal_Unicode
#define STRING          UniString
#define STRINGDATA      UniStringData
#define DBGCHECKSTRING  DbgCheckUniString
#define STRING_TYPE     rtl_uString
#define STRING_ACQUIRE  rtl_uString_acquire
#define STRING_RELEASE  rtl_uString_release
#define STRING_NEW      rtl_uString_new

// -----------------------------------------------------------------------

}

#include <tl_strimp.cxx>
#include <tl_strucvt.cxx>
#include <tl_strascii.cxx>

namespace binfilter
{

UniString::UniString(char c): mpData(ImplAllocData(1)) { mpData->maStr[0] = c; }

// -----------------------------------------------------------------------

UniString UniString::CreateFromInt32( sal_Int32 n, sal_Int16 nRadix )
{
    sal_Unicode aBuf[RTL_USTR_MAX_VALUEOFINT32];
    BOOST_STATIC_ASSERT(RTL_USTR_MAX_VALUEOFINT32 <= STRING_MAXLEN);
    return UniString(
        aBuf,
        static_cast< xub_StrLen >(rtl_ustr_valueOfInt32( aBuf, n, nRadix )) );
}

// -----------------------------------------------------------------------

UniString UniString::CreateFromInt64( sal_Int64 n, sal_Int16 nRadix )
{
    sal_Unicode aBuf[RTL_USTR_MAX_VALUEOFINT64];
    BOOST_STATIC_ASSERT(RTL_USTR_MAX_VALUEOFINT64 <= STRING_MAXLEN);
    return UniString(
        aBuf,
        static_cast< xub_StrLen >(rtl_ustr_valueOfInt64( aBuf, n, nRadix )) );
}

// -----------------------------------------------------------------------

namespace { struct Empty : public rtl::Static< const UniString, Empty> {}; }
const UniString& UniString::EmptyString()
{
    return Empty::get();
}

// -----------------------------------------------------------------------

sal_Int32 UniString::ToInt32() const
{
    DBG_CHKTHIS( UniString, DbgCheckUniString );

    return rtl_ustr_toInt32( mpData->maStr, 10 );
}

// -----------------------------------------------------------------------

sal_Int64 UniString::ToInt64() const
{
    DBG_CHKTHIS( UniString, DbgCheckUniString );

    return rtl_ustr_toInt64( mpData->maStr, 10 );
}

// -----------------------------------------------------------------------

double UniString::ToDouble() const
{
    DBG_CHKTHIS( UniString, DbgCheckUniString );

    return rtl_ustr_toDouble( mpData->maStr );
}

// -----------------------------------------------------------------------

xub_StrLen STRING::SearchChar( const STRCODE* pChars, xub_StrLen nIndex ) const
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );

    sal_Int32       nLen = mpData->mnLen;
    const STRCODE*  pStr = mpData->maStr;
    pStr += nIndex;
    while ( nIndex < nLen )
    {
        STRCODE         c = *pStr;
        const STRCODE*  pCompStr = pChars;
        while ( *pCompStr )
        {
            if ( *pCompStr == c )
                return nIndex;
            ++pCompStr;
        }
        ++pStr,
        ++nIndex;
    }

    return STRING_NOTFOUND;
}

// -----------------------------------------------------------------------

xub_StrLen STRING::SearchAndReplace( STRCODE c, STRCODE cRep, xub_StrLen nIndex )
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );

    sal_Int32       nLen = mpData->mnLen;
    const STRCODE*  pStr = mpData->maStr;
    pStr += nIndex;
    while ( nIndex < nLen )
    {
        if ( *pStr == c )
        {
            ImplCopyData();
            mpData->maStr[nIndex] = cRep;
            return nIndex;
        }
        ++pStr,
        ++nIndex;
    }

    return STRING_NOTFOUND;
}

// -----------------------------------------------------------------------

STRING& STRING::Reverse()
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );

    if ( !mpData->mnLen )
        return *this;

    // Daten kopieren, wenn noetig
    ImplCopyData();

    // Reverse
    sal_Int32 nCount = mpData->mnLen / 2;
    for ( sal_Int32 i = 0; i < nCount; ++i )
    {
        STRCODE cTemp = mpData->maStr[i];
        mpData->maStr[i] = mpData->maStr[mpData->mnLen-i-1];
        mpData->maStr[mpData->mnLen-i-1] = cTemp;
    }

    return *this;
}

// -----------------------------------------------------------------------

STRING& STRING::Insert( const STRING& rStr, xub_StrLen nPos, xub_StrLen nLen,
                        xub_StrLen nIndex )
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );
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

    // Ueberlauf abfangen
    sal_Int32 nCopyLen = ImplGetCopyLen( mpData->mnLen, nLen );

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
    memcpy( pNewData->maStr+nIndex, rStr.mpData->maStr+nPos, nCopyLen*sizeof( STRCODE ) );
    memcpy( pNewData->maStr+nIndex+nCopyLen, mpData->maStr+nIndex,
            (mpData->mnLen-nIndex)*sizeof( STRCODE ) );

    // Alte Daten loeschen und Neue zuweisen
    STRING_RELEASE((STRING_TYPE *)mpData);
    mpData = pNewData;

    return *this;
}

// -----------------------------------------------------------------------

xub_StrLen STRING::GetQuotedTokenCount( const STRING& rQuotedPairs, STRCODE cTok ) const
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );
    DBG_CHKOBJ( &rQuotedPairs, STRING, DBGCHECKSTRING );
    DBG_ASSERT( !(rQuotedPairs.Len()%2), "String::GetQuotedTokenCount() - QuotedString%2 != 0" );
    DBG_ASSERT( rQuotedPairs.Search(cTok) == STRING_NOTFOUND, "String::GetQuotedTokenCount() - cTok in QuotedString" );

    // Leerer String: TokenCount per Definition 0
    if ( !mpData->mnLen )
        return 0;

    xub_StrLen      nTokCount       = 1;
    sal_Int32       nLen            = mpData->mnLen;
    xub_StrLen      nQuotedLen      = rQuotedPairs.Len();
    STRCODE         cQuotedEndChar  = 0;
    const STRCODE*  pQuotedStr      = rQuotedPairs.mpData->maStr;
    const STRCODE*  pStr            = mpData->maStr;
    sal_Int32       nIndex          = 0;
    while ( nIndex < nLen )
    {
        STRCODE c = *pStr;
        if ( cQuotedEndChar )
        {
            // Ende des Quotes erreicht ?
            if ( c == cQuotedEndChar )
                cQuotedEndChar = 0;
        }
        else
        {
            // Ist das Zeichen ein Quote-Anfang-Zeichen ?
            xub_StrLen nQuoteIndex = 0;
            while ( nQuoteIndex < nQuotedLen )
            {
                if ( pQuotedStr[nQuoteIndex] == c )
                {
                    cQuotedEndChar = pQuotedStr[nQuoteIndex+1];
                    break;
                }
                else
                    nQuoteIndex += 2;
            }

            // Stimmt das Tokenzeichen ueberein, dann erhoehe TokCount
            if ( c == cTok )
                ++nTokCount;
        }

        ++pStr,
        ++nIndex;
    }

    return nTokCount;
}

// -----------------------------------------------------------------------

STRING STRING::GetQuotedToken( xub_StrLen nToken, const STRING& rQuotedPairs,
                               STRCODE cTok, xub_StrLen& rIndex ) const
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );
    DBG_CHKOBJ( &rQuotedPairs, STRING, DBGCHECKSTRING );
    DBG_ASSERT( !(rQuotedPairs.Len()%2), "String::GetQuotedToken() - QuotedString%2 != 0" );
    DBG_ASSERT( rQuotedPairs.Search(cTok) == STRING_NOTFOUND, "String::GetQuotedToken() - cTok in QuotedString" );

    const STRCODE*  pStr            = mpData->maStr;
    const STRCODE*  pQuotedStr      = rQuotedPairs.mpData->maStr;
    STRCODE         cQuotedEndChar  = 0;
    xub_StrLen      nQuotedLen      = rQuotedPairs.Len();
    xub_StrLen      nLen            = (xub_StrLen)mpData->mnLen;
    xub_StrLen      nTok            = 0;
    xub_StrLen      nFirstChar      = rIndex;
    xub_StrLen      i               = nFirstChar;

    // Bestimme die Token-Position und Laenge
    pStr += i;
    while ( i < nLen )
    {
        STRCODE c = *pStr;
        if ( cQuotedEndChar )
        {
            // Ende des Quotes erreicht ?
            if ( c == cQuotedEndChar )
                cQuotedEndChar = 0;
        }
        else
        {
            // Ist das Zeichen ein Quote-Anfang-Zeichen ?
            xub_StrLen nQuoteIndex = 0;
            while ( nQuoteIndex < nQuotedLen )
            {
                if ( pQuotedStr[nQuoteIndex] == c )
                {
                    cQuotedEndChar = pQuotedStr[nQuoteIndex+1];
                    break;
                }
                else
                    nQuoteIndex += 2;
            }

            // Stimmt das Tokenzeichen ueberein, dann erhoehe TokCount
            if ( c == cTok )
            {
                ++nTok;

                if ( nTok == nToken )
                    nFirstChar = i+1;
                else
                {
                    if ( nTok > nToken )
                        break;
                }
            }
        }

        ++pStr,
        ++i;
    }

    if ( nTok >= nToken )
    {
        if ( i < nLen )
            rIndex = i+1;
        else
            rIndex = STRING_NOTFOUND;
        return Copy( nFirstChar, i-nFirstChar );
    }
    else
    {
        rIndex = STRING_NOTFOUND;
        return STRING();
    }
}

// -----------------------------------------------------------------------

static sal_Int32 ImplStringICompareWithoutZero( const STRCODE* pStr1, const STRCODE* pStr2,
                                                sal_Int32 nCount )
{
    sal_Int32   nRet = 0;
    STRCODE     c1;
    STRCODE     c2;
    do
    {
        if ( !nCount )
            break;

        // Ist das Zeichen zwischen 'A' und 'Z' dann umwandeln
        c1 = *pStr1;
        c2 = *pStr2;
        if ( (c1 >= 65) && (c1 <= 90) )
            c1 += 32;
        if ( (c2 >= 65) && (c2 <= 90) )
            c2 += 32;
        nRet = ((sal_Int32)((STRCODEU)c1))-((sal_Int32)((STRCODEU)c2));

        ++pStr1,
        ++pStr2,
        --nCount;
    }
    while ( nRet == 0 );

    return nRet;
}

// -----------------------------------------------------------------------

sal_Bool STRING::EqualsIgnoreCaseAscii( const STRING& rStr, xub_StrLen nIndex, xub_StrLen nLen ) const
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );
    DBG_CHKOBJ( &rStr, STRING, DBGCHECKSTRING );

    // Are there enough codes for comparing?
    if ( nIndex > mpData->mnLen )
        return (rStr.mpData->mnLen == 0);
    sal_Int32 nMaxLen = mpData->mnLen-nIndex;
    if ( nMaxLen < nLen )
    {
        if ( rStr.mpData->mnLen != nMaxLen )
            return sal_False;
        nLen = static_cast< xub_StrLen >(nMaxLen);
    }

    // String vergleichen
    return (ImplStringICompareWithoutZero( mpData->maStr+nIndex, rStr.mpData->maStr, nLen ) == 0);
}

// -----------------------------------------------------------------------

StringCompare STRING::CompareIgnoreCaseToAscii( const STRING& rStr,
                                                xub_StrLen nLen ) const
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );
    DBG_CHKOBJ( &rStr, STRING, DBGCHECKSTRING );

    // Auf Gleichheit der Pointer testen
    if ( mpData == rStr.mpData )
        return COMPARE_EQUAL;

    // Maximale Laenge ermitteln
    if ( mpData->mnLen < nLen )
        nLen = static_cast< xub_StrLen >(mpData->mnLen+1);
    if ( rStr.mpData->mnLen < nLen )
        nLen = static_cast< xub_StrLen >(rStr.mpData->mnLen+1);

    // String vergleichen
    sal_Int32 nCompare = ImplStringICompareWithoutZero( mpData->maStr, rStr.mpData->maStr, nLen );

    // Rueckgabewert anpassen
    if ( nCompare == 0 )
        return COMPARE_EQUAL;
    else if ( nCompare < 0 )
        return COMPARE_LESS;
    else
        return COMPARE_GREATER;
}

// -----------------------------------------------------------------------

STRING& STRING::Fill( xub_StrLen nCount, STRCODE cFillChar )
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );

    if ( !nCount )
        return *this;

    // Ist nCount groesser wie der jetzige String, dann verlaengern
    if ( nCount > mpData->mnLen )
    {
        // dann neuen String mit der neuen Laenge anlegen
        STRINGDATA* pNewData = ImplAllocData( nCount );
        STRING_RELEASE((STRING_TYPE *)mpData);
        mpData = pNewData;
    }
    else
        ImplCopyData();

    STRCODE* pStr = mpData->maStr;
    do
    {
        *pStr = cFillChar;
        ++pStr,
        --nCount;
    }
    while ( nCount );

    return *this;
}

// -----------------------------------------------------------------------

STRING& STRING::Expand( xub_StrLen nCount, STRCODE cExpandChar )
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );

    // Muss der String erweitert werden
    sal_Int32 nLen = mpData->mnLen;
    if ( nCount <= nLen )
        return *this;

    // Neuen String anlegen
    STRINGDATA* pNewData = ImplAllocData( nCount );

    // Alten String kopieren
    memcpy( pNewData->maStr, mpData->maStr, nLen*sizeof( STRCODE ) );

    // und initialisieren
    STRCODE* pStr = pNewData->maStr;
    pStr += nLen;
    for (sal_Int32 i = nCount - nLen; i > 0; --i) {
        *pStr++ = cExpandChar;
    }

    // Alte Daten loeschen und Neue zuweisen
    STRING_RELEASE((STRING_TYPE *)mpData);
    mpData = pNewData;

    return *this;
}

// -----------------------------------------------------------------------

STRCODE* STRING::GetBufferAccess()
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );

    // Daten kopieren, wenn noetig
    if ( mpData->mnLen )
        ImplCopyData();

    // Pointer auf den String zurueckgeben
    return mpData->maStr;
}

// -----------------------------------------------------------------------

void STRING::ReleaseBufferAccess( xub_StrLen nLen )
{
    // Hier ohne Funktionstest, da String nicht konsistent
    DBG_CHKTHIS( STRING, NULL );
    DBG_ASSERT( mpData->mnRefCount == 1, "String::ReleaseCharStr() called for String with RefCount" );

    if ( nLen > mpData->mnLen )
        nLen = ImplStringLen( mpData->maStr );
    OSL_ASSERT(nLen <= mpData->mnLen);
    if ( !nLen )
    {
        STRING_NEW((STRING_TYPE **)&mpData);
    }
    // Bei mehr als 8 Zeichen unterschied, kuerzen wir den Buffer
    else if ( mpData->mnLen - nLen > 8 )
    {
        STRINGDATA* pNewData = ImplAllocData( nLen );
        memcpy( pNewData->maStr, mpData->maStr, nLen*sizeof( STRCODE ) );
        STRING_RELEASE((STRING_TYPE *)mpData);
        mpData = pNewData;
    }
    else
        mpData->mnLen = nLen;
}

// -----------------------------------------------------------------------

STRCODE* STRING::AllocBuffer( xub_StrLen nLen )
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );

    STRING_RELEASE((STRING_TYPE *)mpData);
    if ( nLen )
        mpData = ImplAllocData( nLen );
    else
    {
        mpData = NULL;
        STRING_NEW((STRING_TYPE **)&mpData);
    }

    return mpData->maStr;
}

// -----------------------------------------------------------------------

STRING::STRING( STRCODE c )
{
    DBG_CTOR( STRING, DBGCHECKSTRING );
    DBG_ASSERT( c, "String::String() - c is 0" );

    // Verwaltungsdaten anlegen und initialisieren
    mpData = ImplAllocData( 1 );
    mpData->maStr[0] = c;
}

// -----------------------------------------------------------------------

STRING& STRING::EraseLeadingChars( STRCODE c )
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );

    if ( mpData->maStr[0] != c )
        return *this;

    xub_StrLen nStart = 0;
    while ( mpData->maStr[nStart] == c )
        ++nStart;

    return Erase( 0, nStart );
}

// -----------------------------------------------------------------------

STRING& STRING::EraseTrailingChars( STRCODE c )
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );

    sal_Int32 nEnd = mpData->mnLen;
    while ( nEnd && (mpData->maStr[nEnd-1] == c) )
        nEnd--;

    if ( nEnd != mpData->mnLen )
        Erase( static_cast< xub_StrLen >(nEnd) );

    return *this;
}

STRING::STRING( const ::STRING& rStr )
{
    DBG_CTOR( STRING, DBGCHECKSTRING );
    DBG_CHKOBJ( &rStr, STRING, DBGCHECKSTRING );

    // this is good enough for binfilter...
    STRING temp;
    temp.Assign(rStr);

    STRING_ACQUIRE((STRING_TYPE *)temp.mpData);
    mpData = temp.mpData;
}

// -----------------------------------------------------------------------

STRING& STRING::Assign( const STRCODE* pCharStr, xub_StrLen nLen )
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );
    DBG_ASSERT( pCharStr, "String::Assign() - pCharStr is NULL" );

    if ( nLen == STRING_LEN )
        nLen = ImplStringLen( pCharStr );

#ifdef DBG_UTIL
    if ( DbgIsAssert() )
    {
        for ( xub_StrLen i = 0; i < nLen; i++ )
        {
            if ( !pCharStr[i] )
            {
                OSL_FAIL( "String::Assign() : nLen is wrong" );
            }
        }
    }
#endif

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

xub_StrLen STRING::SearchBackward( STRCODE c, xub_StrLen nIndex ) const
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );

    if ( nIndex > mpData->mnLen )
        nIndex = (xub_StrLen)mpData->mnLen;

    const STRCODE* pStr = mpData->maStr;
    pStr += nIndex;

    while ( nIndex )
    {
        nIndex--;
        pStr--;
        if ( *pStr == c )
            return nIndex;
    }

    return STRING_NOTFOUND;
}

// -----------------------------------------------------------------------

STRING& STRING::ToUpperAscii()
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );

    sal_Int32 nIndex = 0;
    sal_Int32 nLen = mpData->mnLen;
    STRCODE*    pStr = mpData->maStr;
    while ( nIndex < nLen )
    {
        // Ist das Zeichen zwischen 'a' und 'z' dann umwandeln
        if ( (*pStr >= 97) && (*pStr <= 122) )
        {
            // Daten kopieren, wenn noetig
            pStr = ImplCopyStringData( pStr );
            *pStr -= 32;
        }

        ++pStr,
        ++nIndex;
    }

    return *this;
}

// -----------------------------------------------------------------------

STRING& STRING::Append( STRCODE c )
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );

    // kein 0-Character und maximale Stringlaenge nicht ueberschreiten
    sal_Int32 nLen = mpData->mnLen;
    if ( c && (nLen < STRING_MAXLEN) )
    {
        // Neue Datenstruktur und neuen String erzeugen
        STRINGDATA* pNewData = ImplAllocData( nLen+1 );

        // String kopieren
        memcpy( pNewData->maStr, mpData->maStr, nLen*sizeof( STRCODE ) );
        pNewData->maStr[nLen] = c;

        // Alte Daten loeschen und Neue zuweisen
        STRING_RELEASE((STRING_TYPE *)mpData);
        mpData = pNewData;
    }

    return *this;
}

// -----------------------------------------------------------------------

STRING& STRING::Assign( STRCODE c )
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );
    DBG_ASSERT( c, "String::Assign() - c is 0" );

    // Verwaltungsdaten anlegen und initialisieren
    STRING_RELEASE((STRING_TYPE *)mpData);
    mpData = ImplAllocData( 1 );
    mpData->maStr[0] = c;
    return *this;
}

// -----------------------------------------------------------------------

StringCompare STRING::CompareTo( const STRING& rStr, xub_StrLen nLen ) const
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );
    DBG_CHKOBJ( &rStr, STRING, DBGCHECKSTRING );

    // Auf Gleichheit der Pointer testen
    if ( mpData == rStr.mpData )
        return COMPARE_EQUAL;

    // Maximale Laenge ermitteln
    if ( mpData->mnLen < nLen )
        nLen = static_cast< xub_StrLen >(mpData->mnLen+1);
    if ( rStr.mpData->mnLen < nLen )
        nLen = static_cast< xub_StrLen >(rStr.mpData->mnLen+1);

    // String vergleichen
    sal_Int32 nCompare = ImplStringCompareWithoutZero( mpData->maStr, rStr.mpData->maStr, nLen );

    // Rueckgabewert anpassen
    if ( nCompare == 0 )
        return COMPARE_EQUAL;
    else if ( nCompare < 0 )
        return COMPARE_LESS;
    else
        return COMPARE_GREATER;
}

// -----------------------------------------------------------------------

STRING::STRING( const STRCODE* pCharStr, xub_StrLen nLen )
: mpData(NULL)
{
    DBG_CTOR( STRING, DBGCHECKSTRING );
    DBG_ASSERT( pCharStr, "String::String() - pCharStr is NULL" );

    if ( nLen == STRING_LEN )
        nLen = ImplStringLen( pCharStr );

#ifdef DBG_UTIL
    if ( DbgIsAssert() )
    {
        for ( xub_StrLen i = 0; i < nLen; i++ )
        {
            if ( !pCharStr[i] )
            {
                OSL_FAIL( "String::String() : nLen is wrong" );
            }
        }
    }
#endif

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

STRING STRING::GetToken( xub_StrLen nToken, STRCODE cTok, xub_StrLen& rIndex ) const
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );

    const STRCODE*  pStr            = mpData->maStr;
    xub_StrLen      nLen            = (xub_StrLen)mpData->mnLen;
    xub_StrLen      nTok            = 0;
    xub_StrLen      nFirstChar      = rIndex;
    xub_StrLen      i               = nFirstChar;

    // Bestimme die Token-Position und Laenge
    pStr += i;
    while ( i < nLen )
    {
        // Stimmt das Tokenzeichen ueberein, dann erhoehe TokCount
        if ( *pStr == cTok )
        {
            ++nTok;

            if ( nTok == nToken )
                nFirstChar = i+1;
            else
            {
                if ( nTok > nToken )
                    break;
            }
        }

        ++pStr,
        ++i;
    }

    if ( nTok >= nToken )
    {
        if ( i < nLen )
            rIndex = i+1;
        else
            rIndex = STRING_NOTFOUND;
        return Copy( nFirstChar, i-nFirstChar );
    }
    else
    {
        rIndex = STRING_NOTFOUND;
        return STRING();
    }
}

// -----------------------------------------------------------------------

void STRING::SetToken( xub_StrLen nToken, STRCODE cTok, const STRING& rStr,
                       xub_StrLen nIndex )
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );
    DBG_CHKOBJ( &rStr, STRING, DBGCHECKSTRING );

    const STRCODE*  pStr            = mpData->maStr;
    xub_StrLen      nLen            = (xub_StrLen)mpData->mnLen;
    xub_StrLen      nTok            = 0;
    xub_StrLen      nFirstChar      = nIndex;
    xub_StrLen      i               = nFirstChar;

    // Bestimme die Token-Position und Laenge
    pStr += i;
    while ( i < nLen )
    {
        // Stimmt das Tokenzeichen ueberein, dann erhoehe TokCount
        if ( *pStr == cTok )
        {
            ++nTok;

            if ( nTok == nToken )
                nFirstChar = i+1;
            else
            {
                if ( nTok > nToken )
                    break;
            }
        }

        ++pStr,
        ++i;
    }

    if ( nTok >= nToken )
        Replace( nFirstChar, i-nFirstChar, rStr );
}

// -----------------------------------------------------------------------

void STRING::SetChar( xub_StrLen nIndex, STRCODE c )
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );
    DBG_ASSERT( nIndex < mpData->mnLen, "String::SetChar() - nIndex > String.Len()" );

    // Daten kopieren, wenn noetig und Character zuweisen
    ImplCopyData();
    mpData->maStr[nIndex] = c;
}

// -----------------------------------------------------------------------

xub_StrLen STRING::Match( const STRING& rStr ) const
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );
    DBG_CHKOBJ( &rStr, STRING, DBGCHECKSTRING );

    // Ist dieser String leer
    if ( !mpData->mnLen )
        return STRING_MATCH;

    // Suche bis Stringende nach dem ersten nicht uebereinstimmenden Zeichen
    const STRCODE*  pStr1 = mpData->maStr;
    const STRCODE*  pStr2 = rStr.mpData->maStr;
    xub_StrLen      i = 0;
    while ( i < mpData->mnLen )
    {
        // Stimmt das Zeichen nicht ueberein, dann abbrechen
        if ( *pStr1 != *pStr2 )
            return i;
        ++pStr1,
        ++pStr2,
        ++i;
    }

    return STRING_MATCH;
}

// -----------------------------------------------------------------------

sal_Bool STRING::EqualsIgnoreCaseAscii( const STRING& rStr ) const
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
    return (ImplStringICompareWithoutZero( mpData->maStr, rStr.mpData->maStr, mpData->mnLen ) == 0);
}

// -----------------------------------------------------------------------

static sal_Int32 ImplStringICompare( const STRCODE* pStr1, const STRCODE* pStr2 )
{
    sal_Int32   nRet;
    STRCODE     c1;
    STRCODE     c2;
    do
    {
        // Ist das Zeichen zwischen 'A' und 'Z' dann umwandeln
        c1 = *pStr1;
        c2 = *pStr2;
        if ( (c1 >= 65) && (c1 <= 90) )
            c1 += 32;
        if ( (c2 >= 65) && (c2 <= 90) )
            c2 += 32;
        nRet = ((sal_Int32)((STRCODEU)c1))-((sal_Int32)((STRCODEU)c2));
        if ( nRet != 0 )
            break;

        ++pStr1,
        ++pStr2;
    }
    while ( c2 );

    return nRet;
}

// -----------------------------------------------------------------------

sal_Bool STRING::EqualsIgnoreCaseAscii( const STRCODE* pCharStr ) const
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );

    return (ImplStringICompare( mpData->maStr, pCharStr ) == 0);
}

// -----------------------------------------------------------------------

sal_Bool STRING::Equals( const STRING& rStr, xub_StrLen nIndex, xub_StrLen nLen ) const
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );
    DBG_CHKOBJ( &rStr, STRING, DBGCHECKSTRING );

    // Are there enough codes for comparing?
    if ( nIndex > mpData->mnLen )
        return (rStr.mpData->mnLen == 0);
    sal_Int32 nMaxLen = mpData->mnLen-nIndex;
    if ( nMaxLen < nLen )
    {
        if ( rStr.mpData->mnLen != nMaxLen )
            return sal_False;
        nLen = static_cast< xub_StrLen >(nMaxLen);
    }

    // String vergleichen
    return (ImplStringCompareWithoutZero( mpData->maStr+nIndex, rStr.mpData->maStr, nLen ) == 0);
}

static sal_Int32 ImplStringCompare( const STRCODE* pStr1, const STRCODE* pStr2,
                                    xub_StrLen nCount )
{
    sal_Int32 nRet = 0;
    while ( nCount &&
            ((nRet = ((sal_Int32)((STRCODEU)*pStr1))-((sal_Int32)((STRCODEU)*pStr2))) == 0) &&
            *pStr2 )
    {
        ++pStr1,
        ++pStr2,
        --nCount;
    }

    return nRet;
}

// -----------------------------------------------------------------------

sal_Bool STRING::Equals( const STRCODE* pCharStr, xub_StrLen nIndex, xub_StrLen nLen ) const
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );

    // Are there enough codes for comparing?
    if ( nIndex > mpData->mnLen )
        return (*pCharStr == 0);

    return (ImplStringCompare( mpData->maStr+nIndex, pCharStr, nLen ) == 0);
}

// -----------------------------------------------------------------------

void STRING::SearchAndReplaceAll( STRCODE c, STRCODE cRep )
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );

    sal_Int32       nLen    = mpData->mnLen;
    const STRCODE*  pStr    = mpData->maStr;
    sal_Int32       nIndex  = 0;
    while ( nIndex < nLen )
    {
        if ( *pStr == c )
        {
            ImplCopyData();
            mpData->maStr[nIndex] = cRep;
        }
        ++pStr,
        ++nIndex;
    }
}

// -----------------------------------------------------------------------

void STRING::SearchAndReplaceAll( const STRING& rStr, const STRING& rRepStr )
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );
    DBG_CHKOBJ( &rStr, STRING, DBGCHECKSTRING );
    DBG_CHKOBJ( &rRepStr, STRING, DBGCHECKSTRING );

    xub_StrLen nSPos = Search( rStr, 0 );
    while ( nSPos != STRING_NOTFOUND )
    {
        Replace( nSPos, rStr.Len(), rRepStr );
        nSPos = nSPos + rRepStr.Len();
        nSPos = Search( rStr, nSPos );
    }
}

// -----------------------------------------------------------------------

xub_StrLen STRING::SearchAndReplace( const STRING& rStr, const STRING& rRepStr,
                                     xub_StrLen nIndex )
{
    DBG_CHKTHIS( STRING, DBGCHECKSTRING );
    DBG_CHKOBJ( &rStr, STRING, DBGCHECKSTRING );
    DBG_CHKOBJ( &rRepStr, STRING, DBGCHECKSTRING );

    xub_StrLen nSPos = Search( rStr, nIndex );
    if ( nSPos != STRING_NOTFOUND )
        Replace( nSPos, rStr.Len(), rRepStr );

    return nSPos;
}

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

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
