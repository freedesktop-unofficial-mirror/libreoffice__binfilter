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

#define _SVARRAY_CXX

#define _SVSTDARR_BOOLS
#define _SVSTDARR_BYTES
#define _SVSTDARR_ULONGS
#define _SVSTDARR_ULONGSSORT
#define _SVSTDARR_USHORTS
#define _SVSTDARR_LONGS
#define _SVSTDARR_LONGSSORT
#define _SVSTDARR_SHORTS
#define _SVSTDARR_STRINGS
#define _SVSTDARR_STRINGSDTOR
#define _SVSTDARR_STRINGSSORT
#define _SVSTDARR_STRINGSSORTDTOR
#define _SVSTDARR_STRINGSISORT
#define _SVSTDARR_STRINGSISORTDTOR
#define _SVSTDARR_USHORTSSORT

#define _SVSTDARR_BYTESTRINGS
#define _SVSTDARR_BYTESTRINGSDTOR
#define _SVSTDARR_BYTESTRINGSSORT
#define _SVSTDARR_BYTESTRINGSSORTDTOR
#define _SVSTDARR_BYTESTRINGSISORT
#define _SVSTDARR_BYTESTRINGSISORTDTOR

#define _SVSTDARR_XUB_STRLEN
#define _SVSTDARR_XUB_STRLENSORT

#include <bf_svtools/svstdarr.hxx>

#include <bf_tools/string.hxx>

#include <tools/debug.hxx>

namespace binfilter
{

SV_IMPL_VARARR(SvPtrarr,VoidPtr)

USHORT SvPtrarr::GetPos( const VoidPtr& aElement ) const
{   USHORT n;
    for( n=0; n < nA && *(GetData()+n) != aElement; ) n++;
    return ( n >= nA ? USHRT_MAX : n );
}

SV_IMPL_VARARR( SvBools, BOOL )
SV_IMPL_VARARR( SvBytes, BYTE )
SV_IMPL_VARARR( SvULongs, ULONG )
SV_IMPL_VARARR( SvUShorts, USHORT )
SV_IMPL_VARARR( SvLongs, long)
SV_IMPL_VARARR( SvShorts, short )

SV_IMPL_VARARR( SvXub_StrLens, xub_StrLen )

SV_IMPL_PTRARR( SvStrings, StringPtr )
SV_IMPL_PTRARR( SvStringsDtor, StringPtr )
SV_IMPL_OP_PTRARR_SORT( SvStringsSort, StringPtr )
SV_IMPL_OP_PTRARR_SORT( SvStringsSortDtor, StringPtr )

// ---------------- strings -------------------------------------

// Array mit anderer Seek-Methode!
_SV_IMPL_SORTAR_ALG( SvStringsISort, StringPtr )
void SvStringsISort::DeleteAndDestroy( USHORT nP, USHORT nL )
{
    if( nL )
    {
        DBG_ASSERT( nP < nA && nP + nL <= nA, "ERR_VAR_DEL" );
        for( USHORT n=nP; n < nP + nL; n++ )
            delete *((StringPtr*)pData+n);
        SvPtrarr::Remove( nP, nL );
    }
}
BOOL SvStringsISort::Seek_Entry( const StringPtr aE, USHORT* pP ) const
{
    register USHORT nO  = SvStringsISort_SAR::Count(),
            nM,
            nU = 0;
    if( nO > 0 )
    {
        nO--;
        while( nU <= nO )
        {
            nM = nU + ( nO - nU ) / 2;
            StringCompare eCmp = (*((StringPtr*)pData + nM))->
                                        CompareIgnoreCaseToAscii( *(aE) );
            if( COMPARE_EQUAL == eCmp )
            {
                if( pP ) *pP = nM;
                return TRUE;
            }
            else if( COMPARE_LESS == eCmp )
                nU = nM + 1;
            else if( nM == 0 )
            {
                if( pP ) *pP = nU;
                return FALSE;
            }
            else
                nO = nM - 1;
        }
    }
    if( pP ) *pP = nU;
    return FALSE;
}

// ---------------- strings -------------------------------------

// Array mit anderer Seek-Methode!
_SV_IMPL_SORTAR_ALG( SvStringsISortDtor, StringPtr )
void SvStringsISortDtor::DeleteAndDestroy( USHORT nP, USHORT nL )
{
    if( nL )
    {
        DBG_ASSERT( nP < nA && nP + nL <= nA, "ERR_VAR_DEL" );
        for( USHORT n=nP; n < nP + nL; n++ )
            delete *((StringPtr*)pData+n);
        SvPtrarr::Remove( nP, nL );
    }
}
BOOL SvStringsISortDtor::Seek_Entry( const StringPtr aE, USHORT* pP ) const
{
    register USHORT nO  = SvStringsISortDtor_SAR::Count(),
            nM,
            nU = 0;
    if( nO > 0 )
    {
        nO--;
        while( nU <= nO )
        {
            nM = nU + ( nO - nU ) / 2;
            StringCompare eCmp = (*((StringPtr*)pData + nM))->
                                    CompareIgnoreCaseToAscii( *(aE) );
            if( COMPARE_EQUAL == eCmp )
            {
                if( pP ) *pP = nM;
                return TRUE;
            }
            else if( COMPARE_LESS == eCmp )
                nU = nM + 1;
            else if( nM == 0 )
            {
                if( pP ) *pP = nU;
                return FALSE;
            }
            else
                nO = nM - 1;
        }
    }
    if( pP ) *pP = nU;
    return FALSE;
}

// ---------------- Ushorts -------------------------------------

/* SortArray fuer UShorts */
BOOL SvUShortsSort::Seek_Entry( const USHORT aE, USHORT* pP ) const
{
    register USHORT nO  = SvUShorts::Count(),
            nM,
            nU = 0;
    if( nO > 0 )
    {
        nO--;
        while( nU <= nO )
        {
            nM = nU + ( nO - nU ) / 2;
            if( *(pData + nM) == aE )
            {
                if( pP ) *pP = nM;
                return TRUE;
            }
            else if( *(pData + nM) < aE )
                nU = nM + 1;
            else if( nM == 0 )
            {
                if( pP ) *pP = nU;
                return FALSE;
            }
            else
                nO = nM - 1;
        }
    }
    if( pP ) *pP = nU;
    return FALSE;
}

BOOL SvUShortsSort::Insert( const USHORT aE )
{
    USHORT nP;
    BOOL bExist = Seek_Entry( aE, &nP );
    if( !bExist )
        SvUShorts::Insert( aE, nP );
    return !bExist;
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
