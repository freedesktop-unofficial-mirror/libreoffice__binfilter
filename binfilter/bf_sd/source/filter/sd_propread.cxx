/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: sd_propread.cxx,v $
 * $Revision: 1.8 $
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

#ifndef _PROPREAD_HXX_
#include <propread.hxx>
#endif
#include "rtl/tencinfo.h"
#include "rtl/textenc.h"
namespace binfilter {

// ------------------------------------------------------------------------

struct PropEntry
{
    sal_uInt32  mnId;
    sal_uInt32  mnSize;
    sal_uInt16  mnTextEnc;
    sal_uInt8*  mpBuf;

                        PropEntry( sal_uInt32 nId, const sal_uInt8* pBuf, sal_uInt32 nBufSize, sal_uInt16 nTextEnc );
                        PropEntry( const PropEntry& rProp );
                        ~PropEntry() { delete[] mpBuf; } ;

    const PropEntry&    operator=(const PropEntry& rPropEntry);
};

PropEntry::PropEntry( sal_uInt32 nId, const sal_uInt8* pBuf, sal_uInt32 nBufSize, sal_uInt16 nTextEnc ) :
    mnId        ( nId ),
    mnSize      ( nBufSize ),
    mnTextEnc   ( nTextEnc ),
    mpBuf       ( new sal_uInt8[ nBufSize ] )
{
    memcpy( (void*)mpBuf, (void*)pBuf, nBufSize );
};

PropEntry::PropEntry( const PropEntry& rProp ) :
    mnId        ( rProp.mnId ),
    mnSize      ( rProp.mnSize ),
    mpBuf       ( new sal_uInt8[ mnSize ] ),
    mnTextEnc   ( rProp.mnTextEnc )
{
    memcpy( (void*)mpBuf, (void*)rProp.mpBuf, mnSize );
};

const PropEntry& PropEntry::operator=(const PropEntry& rPropEntry)
{
    if ( this != &rPropEntry )
    {
        delete[] mpBuf;
        mnId = rPropEntry.mnId;
        mnSize = rPropEntry.mnSize;
        mnTextEnc = rPropEntry.mnTextEnc;
        mpBuf = new sal_uInt8[ mnSize ];
        memcpy( (void*)mpBuf, (void*)rPropEntry.mpBuf, mnSize );
    }
    return *this;
}

//  -----------------------------------------------------------------------

PropItem& PropItem::operator=( PropItem& rPropItem )
{
    if ( this != &rPropItem )
    {
        Seek( STREAM_SEEK_TO_BEGIN );
        delete[] SwitchBuffer();

        mnTextEnc = rPropItem.mnTextEnc;
        sal_uInt32 nPos = rPropItem.Tell();
        rPropItem.Seek( STREAM_SEEK_TO_END );
        SvMemoryStream::Write( rPropItem.GetData(), rPropItem.Tell() );
        rPropItem.Seek( nPos );
    }
    return *this;
}

//  -----------------------------------------------------------------------

struct Dict
{
    sal_uInt32  mnId;
    String      aString;

            Dict( sal_uInt32 nId, String rString ) { mnId = nId; aString = rString; };
};

//  -----------------------------------------------------------------------

Dictionary::~Dictionary()
{
    for ( void* pPtr = First(); pPtr; pPtr = Next() )
        delete (Dict*)pPtr;
}

//  -----------------------------------------------------------------------

Dictionary& Dictionary::operator=( Dictionary& rDictionary )
{
    if ( this != &rDictionary )
    {
        void* pPtr; for ( pPtr = First(); pPtr; pPtr = Next() )
            delete (Dict*)pPtr;

        for ( pPtr = rDictionary.First(); pPtr; pPtr = rDictionary.Next() )
            Insert( new Dict( ((Dict*)pPtr)->mnId, ((Dict*)pPtr)->aString ), LIST_APPEND );
    }
    return *this;
}
}
