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

#include <tools/stream.hxx>
#include <tools/tenccvt.hxx>
#include "sbx.hxx"
#include "sb.hxx"
#include <string.h>     // memset() etc
#include "image.hxx"
#include "codegen.hxx"

namespace binfilter {

SbiImage::SbiImage()
{
    pStringOff = NULL;
    pStrings   = NULL;
    pCode      = NULL;
    pLegacyPCode       = NULL;
    nFlags     = 0;
    nStrings   = 0;
    nStringSize= 0;
    nCodeSize  = 0;
    nLegacyCodeSize  =
    nDimBase   = 0;
    bInit      =
    bError     = FALSE;
    bFirstInit = TRUE;
    eCharSet   = osl_getThreadTextEncoding();
}

SbiImage::~SbiImage()
{
    Clear();
}

void SbiImage::Clear()
{
    delete[] pStringOff;
    delete[] pStrings;
    delete[] pCode;
    ReleaseLegacyBuffer();
    pStringOff = NULL;
    pStrings   = NULL;
    pCode      = NULL;
    nFlags     = 0;
    nStrings   = 0;
    nStringSize= 0;
    nLegacyCodeSize  = 0;
    nCodeSize  = 0;
    eCharSet   = osl_getThreadTextEncoding();
    nDimBase   = 0;
    bError     = FALSE;
}

/**************************************************************************
*
*   Service routes for saving and loading
*
**************************************************************************/

BOOL SbiGood( SvStream& r )
{
    return BOOL( !r.IsEof() && r.GetError() == SVSTREAM_OK );
}

BOOL SbiImage::Load( SvStream& r, UINT32& nVersion )
{

    UINT16 nSign, nCount;
    UINT32 nLen, nOff;

    Clear();
    // Master-Record einlesen
    r >> nSign >> nLen >> nCount;
    ULONG nLast = r.Tell() + nLen;
    UINT32 nCharSet;                // System-Zeichensatz
    UINT32 lDimBase;
    UINT16 nReserved1;
    UINT32 nReserved2;
    UINT32 nReserved3;
    BOOL bBadVer = FALSE;
    if( nSign == B_MODULE )
    {
        r >> nVersion >> nCharSet >> lDimBase
          >> nFlags >> nReserved1 >> nReserved2 >> nReserved3;
        eCharSet = (CharSet) nCharSet;
        eCharSet = GetSOLoadTextEncoding( eCharSet );
        bBadVer  = BOOL( nVersion > B_CURVERSION );
        nDimBase = (USHORT) lDimBase;
    }

    bool bLegacy = ( nVersion < B_EXT_IMG_VERSION );

    ULONG nNext;
    while( ( nNext = r.Tell() ) < nLast )
    {
        short i;

        r >> nSign >> nLen >> nCount;
        nNext += nLen + 8;
        if( r.GetError() == SVSTREAM_OK )
          switch( nSign )
        {
            case B_NAME:
                aName = r.ReadUniOrByteString( eCharSet );
                break;
            case B_COMMENT:
                aComment = r.ReadUniOrByteString( eCharSet );
                break;
            case B_SOURCE:
            {
                aOUSource = r.ReadUniOrByteString( eCharSet );
                break;
            }
            case B_EXTSOURCE:
            {
                for( UINT16 j = 0 ; j < nCount ; j++ )
                {
                    String aTmp = r.ReadUniOrByteString( eCharSet );
                    aOUSource += aTmp;
                }
                break;
            }
            case B_PCODE:
                if( bBadVer ) break;
                pCode = new char[ nLen ];
                nCodeSize = nLen;
                r.Read( pCode, nCodeSize );
                if ( bLegacy )
                {
                    ReleaseLegacyBuffer(); // release any previously held buffer
                    nLegacyCodeSize = (UINT16) nCodeSize;
                    pLegacyPCode = pCode;

                    PCodeBuffConvertor< UINT16, UINT32 > aLegacyToNew( (BYTE*)pLegacyPCode, nLegacyCodeSize );
                    aLegacyToNew.convert();
                    pCode = (char*)aLegacyToNew.GetBuffer();
                    nCodeSize = aLegacyToNew.GetSize();
                    // we don't release the legacy buffer
                    // right now, thats because the module
                    // needs it to fix up the method
                    // nStart members. When that is done
                    // the module can release the buffer
                    // or it can wait until this routine
                    // is called again or when this class                       // destructs all of which will trigger
                    // release of the buffer.
                }
                break;
            case B_PUBLICS:
            case B_POOLDIR:
            case B_SYMPOOL:
            case B_LINERANGES:
                break;
            case B_STRINGPOOL:
                if( bBadVer ) break;
                MakeStrings( nCount );
                for( i = 0; i < nStrings && SbiGood( r ); i++ )
                {
                    r >> nOff;
                    pStringOff[ i ] = (USHORT) nOff;
                }
                r >> nLen;
                if( SbiGood( r ) )
                {
                    delete [] pStrings;
                    pStrings = new sal_Unicode[ nLen ];
                    nStringSize = (USHORT) nLen;

                    char* pByteStrings = new char[ nLen ];
                    r.Read( pByteStrings, nStringSize );
                    for( short j = 0; j < nStrings; j++ )
                    {
                        USHORT nOff2 = (USHORT) pStringOff[ j ];
                        String aStr( pByteStrings + nOff2, eCharSet );
                        memcpy( pStrings + nOff2, aStr.GetBuffer(), (aStr.Len() + 1) * sizeof( sal_Unicode ) );
                    }
                    delete[] pByteStrings;
                } break;
            case B_MODEND:
                goto done;
            default:
                break;
        }
        else
            break;
        r.Seek( nNext );
    }
done:
    r.Seek( nLast );
    if( !SbiGood( r ) )
        bError = TRUE;
    return BOOL( !bError );
}

/**************************************************************************
*
*   Routinen, die auch vom Compiler gerufen werden
*
**************************************************************************/

void SbiImage::MakeStrings( short nSize )
{
    nStrings = 0;
    nStringIdx = 0;
    nStringOff = 0;
    nStringSize = 1024;
    pStrings = new sal_Unicode[ nStringSize ];
    pStringOff = new UINT32[ nSize ];
    if( pStrings && pStringOff )
    {
        nStrings = nSize;
        memset( pStringOff, 0, nSize * sizeof( UINT32 ) );
        memset( pStrings, 0, nStringSize * sizeof( sal_Unicode ) );
    }
    else
        bError = TRUE;
}

/**************************************************************************
*
*   Zugriffe auf das Image
*
**************************************************************************/

const SbxObject* SbiImage::FindType (String aTypeName) const
{
    return rTypes.Is() ? (SbxObject*)rTypes->Find(aTypeName,SbxCLASS_OBJECT) : NULL;
}

UINT16
SbiImage::CalcLegacyOffset( INT32 nOffset )
{
    return SbiCodeGen::calcLegacyOffSet( (BYTE*)pCode, nOffset ) ;
}
UINT32
SbiImage::CalcNewOffset( INT16 nOffset )
{
    return SbiCodeGen::calcNewOffSet( (BYTE*)pLegacyPCode, nOffset ) ;
}

void
SbiImage::ReleaseLegacyBuffer()
{
    delete[] pLegacyPCode;
    pLegacyPCode = NULL;
    nLegacyCodeSize = 0;
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
