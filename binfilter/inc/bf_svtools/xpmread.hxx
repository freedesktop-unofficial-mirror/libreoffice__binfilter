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

#ifndef _XPMREAD_HXX
#define _XPMREAD_HXX

#include <bf_svtools/bf_solar.h>

#include <vcl/bitmap.hxx>

class BitmapWriteAccess;
class Graphic;

namespace binfilter
{

#ifdef _XPMPRIVATE

#define XPMTEMPBUFSIZE      0x00008000
#define XPMSTRINGBUF        0x00008000

#define XPMIDENTIFIER       0x00000001          // mnIdentifier includes on of the six phases
#define XPMDEFINITION       0x00000002          // the XPM format consists of
#define XPMVALUES           0x00000003
#define XPMCOLORS           0x00000004
#define XPMPIXELS           0x00000005
#define XPMEXTENSIONS       0x00000006
#define XPMENDEXT           0x00000007


#define XPMREMARK           0x00000001          // defines used by mnStatus
#define XPMDOUBLE           0x00000002
#define XPMSTRING           0x00000004
#define XPMFINISHED         0x00000008

#define XPMCASESENSITIVE    0x00000001
#define XPMCASENONSENSITIVE 0x00000002

// ---------
// - Enums -
// ---------

enum ReadState
{
    XPMREAD_OK,
    XPMREAD_ERROR,
    XPMREAD_NEED_MORE
};

// -------------
// - XPMReader -
// -------------

class XPMReader : public GraphicReader
{
private:

    SvStream&           mrIStm;
    Bitmap              maBmp;
    BitmapWriteAccess*  mpAcc;
    Bitmap              maMaskBmp;
    BitmapWriteAccess*  mpMaskAcc;
    long                mnLastPos;

    ULONG               mnWidth;
    ULONG               mnHeight;
    ULONG               mnColors;
    ULONG               mnCpp;                              // characters per pix
    BOOL                mbTransparent;
    BOOL                mbStatus;
    ULONG               mnStatus;
    ULONG               mnIdentifier;
    BYTE                mcThisByte;
    BYTE                mcLastByte;
    ULONG               mnTempAvail;
    BYTE*               mpTempBuf;
    BYTE*               mpTempPtr;
    BYTE*               mpFastColorTable;
    BYTE*               mpColMap;
    ULONG               mnStringSize;
    BYTE*               mpStringBuf;
    ULONG               mnParaSize;
    BYTE*               mpPara;

    BOOL                ImplGetString( void );
    BOOL                ImplGetColor( ULONG );
    BOOL                ImplGetScanLine( ULONG );
    BOOL                ImplGetColSub( BYTE* );
    BOOL                ImplGetColKey( BYTE );
    void                ImplGetRGBHex( BYTE*, ULONG );
    BOOL                ImplGetPara( ULONG numb );
    BOOL                ImplCompare( BYTE*, BYTE*, ULONG, ULONG nmode = XPMCASENONSENSITIVE );
    ULONG               ImplGetULONG( ULONG nPara );

public:
                        XPMReader( SvStream& rStm );
    virtual             ~XPMReader();

    ReadState           ReadXPM( Graphic& rGraphic );
};

#endif // _XPMPRIVATE

// -------------
// - ImportXPM -
// -------------

BOOL ImportXPM( SvStream& rStream, Graphic& rGraphic );

}

#endif // _XPMREAD_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
