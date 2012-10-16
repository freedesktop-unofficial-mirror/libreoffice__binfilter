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

#include "winmtf.hxx"
#include "emfwr.hxx"
#include "wmfwr.hxx"
#include <bf_svtools/wmf.hxx>

namespace binfilter
{

// -----------------------------------------------------------------------------

BOOL ConvertWMFToGDIMetaFile( SvStream & rStreamWMF, GDIMetaFile & rGDIMetaFile, FilterConfigItem* pConfigItem )
{
    UINT32 nMetaType;
    UINT32 nOrgPos = rStreamWMF.Tell();
    UINT16 nOrigNumberFormat = rStreamWMF.GetNumberFormatInt();
    rStreamWMF.SetNumberFormatInt( NUMBERFORMAT_INT_LITTLEENDIAN );
    rStreamWMF.Seek( 0x28 );
    rStreamWMF >> nMetaType;
    rStreamWMF.Seek( nOrgPos );
    if ( nMetaType == 0x464d4520 )
    {
        if ( EnhWMFReader( rStreamWMF, rGDIMetaFile, pConfigItem ).ReadEnhWMF() == FALSE )
            rStreamWMF.SetError( SVSTREAM_FILEFORMAT_ERROR );
    }
    else
    {
        WMFReader( rStreamWMF, rGDIMetaFile, pConfigItem ).ReadWMF();
    }
    rStreamWMF.SetNumberFormatInt( nOrigNumberFormat );
    return !rStreamWMF.GetError();
}

// -----------------------------------------------------------------------------

BOOL ReadWindowMetafile( SvStream& rStream, GDIMetaFile& rMTF, FilterConfigItem* pFilterConfigItem )
{
    UINT32 nMetaType;
    UINT32 nOrgPos = rStream.Tell();
    UINT16 nOrigNumberFormat = rStream.GetNumberFormatInt();
    rStream.SetNumberFormatInt( NUMBERFORMAT_INT_LITTLEENDIAN );
    rStream.Seek( 0x28 );
    rStream >> nMetaType;
    rStream.Seek( nOrgPos );
    if ( nMetaType == 0x464d4520 )
    {
        if ( EnhWMFReader( rStream, rMTF, NULL ).ReadEnhWMF() == FALSE )
            rStream.SetError( SVSTREAM_FILEFORMAT_ERROR );
    }
    else
    {
        WMFReader( rStream, rMTF, pFilterConfigItem ).ReadWMF();
    }
    rStream.SetNumberFormatInt( nOrigNumberFormat );
    return !rStream.GetError();
}

// -----------------------------------------------------------------------------

BOOL ConvertGDIMetaFileToWMF( const GDIMetaFile & rMTF, SvStream & rTargetStream,
                              FilterConfigItem* pConfigItem, BOOL bPlaceable)
{
    WMFWriter aWMFWriter;
    return aWMFWriter.WriteWMF( rMTF, rTargetStream, pConfigItem, bPlaceable );
}

// -----------------------------------------------------------------------------

BOOL ConvertGDIMetaFileToEMF( const GDIMetaFile & rMTF, SvStream & rTargetStream,
                              FilterConfigItem* pConfigItem )
{
    EMFWriter aEMFWriter;
    return aEMFWriter.WriteEMF( rMTF, rTargetStream, pConfigItem );
}

// -----------------------------------------------------------------------------

BOOL WriteWindowMetafileBits( SvStream& rStream, const GDIMetaFile& rMTF )
{
    return WMFWriter().WriteWMF( rMTF, rStream, NULL, FALSE );
}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
