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

#include <propread.hxx>
#include "rtl/tencinfo.h"
#include "rtl/textenc.h"
namespace binfilter {

// ------------------------------------------------------------------------

PropItem& PropItem::operator=( PropItem& rPropItem )
{
    if ( this != &rPropItem )
    {
        Seek( STREAM_SEEK_TO_BEGIN );
        delete[] (sal_uInt8*)SwitchBuffer();

        mnTextEnc = rPropItem.mnTextEnc;
        sal_uInt32 nLclPos = rPropItem.Tell();
        rPropItem.Seek( STREAM_SEEK_TO_END );
        SvMemoryStream::Write( rPropItem.GetData(), rPropItem.Tell() );
        rPropItem.Seek( nLclPos );
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

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
