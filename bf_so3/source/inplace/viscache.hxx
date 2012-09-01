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
#include <vcl/gdimtf.hxx>
#include <vcl/bitmap.hxx>

namespace binfilter {

/************************************************************************
|*    Impl_CacheElement
|*    Impl_Cache
|*
|*    Beschreibung
*************************************************************************/
class Impl_OlePres
{
    ULONG   nFormat;
    USHORT  nAspect;
    Bitmap *        pBmp;
    GDIMetaFile *   pMtf;

    UINT32  nAdvFlags;
    INT32   nJobLen;
    BYTE*   pJob;
    Size    aSize;      // Groesse in 100TH_MM
public:
                    Impl_OlePres( ULONG nF )
                        : nFormat( nF )
                        , pBmp( NULL )
                        , pMtf( NULL )
                        , nAdvFlags( 0x2 ) // in Dokument gefunden
                        , nJobLen( 0 )
                        , pJob( NULL )
                    {}
                    ~Impl_OlePres()
                    {
                        delete [] pJob;
                        delete pBmp;
                        delete pMtf;
                    }
    void    SetMtf( const GDIMetaFile & rMtf )
            {
                if( pMtf )
                    delete pMtf;
                pMtf = new GDIMetaFile( rMtf );
            }
    Bitmap *GetBitmap() const { return pBmp; }
    GDIMetaFile *GetMetaFile() const { return pMtf; }
    ULONG   GetFormat() const { return nFormat; }
    void    SetAspect( USHORT nAsp ) { nAspect = nAsp; }
    ULONG   GetAdviseFlags() const { return nAdvFlags; }
    void    SetAdviseFlags( ULONG nAdv ) { nAdvFlags = nAdv; }
    void    SetSize( const Size & rSize ) { aSize = rSize; }
            /// return FALSE => unknown format
    BOOL    Read( SvStream & rStm );
    void    Write( SvStream & rStm );
};


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
