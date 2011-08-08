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

// MARKER(update_precomp.py): autogen include statement, do not remove

#include <bf_tools/string.hxx>
#include "boost/static_assert.hpp"

namespace binfilter
{
    ByteString ByteString_CreateFromInt32(sal_Int32 n, sal_Int16 nRadix)
    {
        sal_Char aBuf[RTL_STR_MAX_VALUEOFINT32];
        BOOST_STATIC_ASSERT(RTL_STR_MAX_VALUEOFINT32 <= STRING_MAXLEN);
        return ByteString(
            aBuf,
            static_cast< xub_StrLen >(rtl_str_valueOfInt32( aBuf, n, nRadix )) );
    }

    sal_Unicode ConvertToUnicode( const char* pChar, sal_Size* pLen, rtl_TextEncoding eTextEncoding )
    {
        // TextEncoding Dontknow wird nicht konvertiert
        if ( eTextEncoding == RTL_TEXTENCODING_DONTKNOW )
            return 0;

        rtl_TextToUnicodeConverter	hConverter;
        sal_uInt32					nInfo;
        sal_Size					nSrcBytes;
        sal_Size					nDestChars;
        sal_Unicode 				nConvChar;
        hConverter = rtl_createTextToUnicodeConverter( eTextEncoding );
        nDestChars = rtl_convertTextToUnicode( hConverter, 0,
                                               (const sal_Char*)pChar, *pLen,
                                               &nConvChar, 1,
                                               RTL_TEXTTOUNICODE_FLAGS_UNDEFINED_DEFAULT |
                                               RTL_TEXTTOUNICODE_FLAGS_MBUNDEFINED_DEFAULT |
                                               RTL_TEXTTOUNICODE_FLAGS_INVALID_DEFAULT |
                                               RTL_TEXTTOUNICODE_FLAGS_FLUSH,
                                               &nInfo, &nSrcBytes );
        rtl_destroyTextToUnicodeConverter( hConverter );

        if ( nDestChars == 1 )
        {
            *pLen = nSrcBytes;
            return nConvChar;
        }
        else
        {
            *pLen = 0;
            return 0;
        }
    }

    sal_Unicode ByteString_ConvertToUnicode( char c, rtl_TextEncoding eTextEncoding )
    {
        sal_Size nLen = 1;
        return ConvertToUnicode( &c, &nLen, eTextEncoding );
    }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
