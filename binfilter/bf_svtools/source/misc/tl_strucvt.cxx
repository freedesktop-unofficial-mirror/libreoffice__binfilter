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

// =======================================================================

UniString::UniString( const ByteString& rByteStr, rtl_TextEncoding eTextEncoding, sal_uInt32 nCvtFlags )
{
    DBG_CTOR( UniString, DbgCheckUniString );
    DBG_CHKOBJ( &rByteStr, ByteString, DbgCheckByteString );

    mpData = NULL;
    rtl_string2UString( (rtl_uString **)(&mpData),
                        rByteStr.mpData->maStr, rByteStr.mpData->mnLen,
                        eTextEncoding, nCvtFlags );
}

// -----------------------------------------------------------------------

UniString::UniString( const ByteString& rByteStr, xub_StrLen nPos, xub_StrLen nLen,
                      rtl_TextEncoding eTextEncoding, sal_uInt32 nCvtFlags )
{
    DBG_CTOR( UniString, DbgCheckUniString );
    DBG_CHKOBJ( &rByteStr, ByteString, DbgCheckByteString );

    // Stringlaenge ermitteln
    if ( nPos > rByteStr.mpData->mnLen )
        nLen = 0;
    else
    {
        // Laenge korrigieren, wenn noetig
        sal_Int32 nMaxLen = rByteStr.mpData->mnLen-nPos;
        if ( nLen > nMaxLen )
            nLen = static_cast< xub_StrLen >(nMaxLen);
    }

    mpData = NULL;
    rtl_string2UString( (rtl_uString **)(&mpData),
                        rByteStr.mpData->maStr+nPos, nLen,
                        eTextEncoding, nCvtFlags );
}

// -----------------------------------------------------------------------

UniString::UniString( const char* pByteStr,
                      rtl_TextEncoding eTextEncoding, sal_uInt32 nCvtFlags )
{
    DBG_CTOR( UniString, DbgCheckUniString );
    DBG_ASSERT( pByteStr, "UniString::UniString() - pByteStr is NULL" );

    mpData = NULL;
    rtl_string2UString( (rtl_uString **)(&mpData),
                        pByteStr, ImplStringLen( pByteStr ),
                        eTextEncoding, nCvtFlags );
}

// -----------------------------------------------------------------------

UniString::UniString( const char* pByteStr, xub_StrLen nLen,
                      rtl_TextEncoding eTextEncoding, sal_uInt32 nCvtFlags )
{
    DBG_CTOR( UniString, DbgCheckUniString );
    DBG_ASSERT( pByteStr, "UniString::UniString() - pByteStr is NULL" );

    if ( nLen == STRING_LEN )
        nLen = ImplStringLen( pByteStr );

    mpData = NULL;
    rtl_string2UString( (rtl_uString **)(&mpData),
                        pByteStr, nLen,
                        eTextEncoding, nCvtFlags );
}

// =======================================================================

UniString::UniString( const rtl::OUString& rStr )
    : mpData(NULL)
{
    DBG_CTOR( UniString, DbgCheckUniString );

    OSL_ENSURE(rStr.pData->length < STRING_MAXLEN,
               "Overflowing rtl::OUString -> UniString cut to zero length");


    if (rStr.pData->length < STRING_MAXLEN)
    {
        mpData = reinterpret_cast< UniStringData * >(const_cast< rtl::OUString & >(rStr).pData);
        STRING_ACQUIRE((STRING_TYPE *)mpData);
    }
    else
    {
        STRING_NEW((STRING_TYPE **)&mpData);
    }
}

// -----------------------------------------------------------------------

UniString& UniString::Assign( const rtl::OUString& rStr )
{
    DBG_CHKTHIS( UniString, DbgCheckUniString );

    OSL_ENSURE(rStr.pData->length < STRING_MAXLEN,
               "Overflowing rtl::OUString -> UniString cut to zero length");


    if (rStr.pData->length < STRING_MAXLEN)
    {
        STRING_RELEASE((STRING_TYPE *)mpData);
        mpData = reinterpret_cast< UniStringData * >(const_cast< rtl::OUString & >(rStr).pData);
        STRING_ACQUIRE((STRING_TYPE *)mpData);
    }
    else
    {
        STRING_NEW((STRING_TYPE **)&mpData);
    }

    return *this;
}

UniString UniString::intern() const
{
    UniString aStr;

    rtl_uString_intern( reinterpret_cast<rtl_uString **>(&aStr.mpData),
                        (rtl_uString *)(mpData) );

    return aStr;
}

// =======================================================================

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
