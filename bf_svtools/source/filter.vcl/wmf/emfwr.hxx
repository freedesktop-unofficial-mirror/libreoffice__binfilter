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

#ifndef _EMFWR_HXX
#define _EMFWR_HXX

#include <bf_svtools/bf_solar.h>

#include <tools/debug.hxx>
#include <vcl/metaact.hxx>
#include <vcl/graph.hxx>
#include <vcl/gdimtf.hxx>
#include <vcl/virdev.hxx>
#include <bf_svtools/fltcall.hxx>

// -------------
// - EMFWriter -
// -------------

namespace binfilter
{

class EMFWriter
{
private:

    VirtualDevice       maVDev;
    FilterConfigItem*   mpFilterConfigItem;
    SvStream*           mpStm;
    BOOL*               mpHandlesUsed;
    ULONG               mnHandleCount;
    ULONG               mnLastPercent;
    ULONG               mnRecordCount;
    ULONG               mnRecordPos;
    BOOL                mbRecordOpen;
    BOOL                mbLineChanged;
    sal_uInt32          mnLineHandle;
    BOOL                mbFillChanged;
    sal_uInt32          mnFillHandle;
    BOOL                mbTextChanged;
    sal_uInt32          mnTextHandle;

    void                ImplBeginRecord( sal_uInt32 nType );
    void                ImplEndRecord();

    ULONG               ImplAcquireHandle();
    void                ImplReleaseHandle( ULONG nHandle );

    BOOL                ImplPrepareHandleSelect( sal_uInt32& rHandle, ULONG nSelectType );
    void                ImplCheckLineAttr();
    void                ImplCheckFillAttr();
    void                ImplCheckTextAttr();

    void                ImplWriteColor( const Color& rColor );
    void                ImplWriteRasterOp( RasterOp eRop );
    void                ImplWriteExtent( long nExtent );
    void                ImplWritePoint( const Point& rPoint );
    void                ImplWriteSize( const Size& rSize);
    void                ImplWriteRect( const Rectangle& rRect );
    void                ImplWritePath( const PolyPolygon& rPolyPoly, sal_Bool bClose );
    void                ImplWritePolygonRecord( const Polygon& rPoly, BOOL bClose );
    void                ImplWritePolyPolygonRecord( const PolyPolygon& rPolyPoly );
    void                ImplWriteBmpRecord( const Bitmap& rBmp, const Point& rPt, const Size& rSz, UINT32 nROP );
    void                ImplWriteTextRecord( const Point& rPos, const String rText, const sal_Int32* pDXArray, sal_uInt32 nWidth );

    void                ImplWrite( const GDIMetaFile& rMtf );

public:

                        EMFWriter() {}

    BOOL                WriteEMF( const GDIMetaFile& rMtf, SvStream& rOStm, FilterConfigItem* pConfigItem = NULL );
};

}

#endif // _EMFWR_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
