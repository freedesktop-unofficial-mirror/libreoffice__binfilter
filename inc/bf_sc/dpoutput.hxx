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

#ifndef SC_DPOUTPUT_HXX
#define SC_DPOUTPUT_HXX

#include <bf_svtools/bf_solar.h>

#include <com/sun/star/sheet/XDimensionsSupplier.hpp>

#include <com/sun/star/sheet/DataResult.hpp>


#include "global.hxx"
class Rectangle;
class SvStream;
namespace binfilter {

class ScDocument;

struct ScDPOutLevelData;




struct ScDPPositionData
{
    long    nDimension;
    long    nHierarchy;
    long    nLevel;
    long    nFlags;
    String  aMemberName;

    ScDPPositionData() { nDimension = nHierarchy = nLevel = -1; nFlags = 0; }   // invalid
};



class ScDPOutput            //! name???
{
private:
    //! use impl-object?
    ScDocument*             pDoc;
    ::com::sun::star::uno::Reference<
        ::com::sun::star::sheet::XDimensionsSupplier> xSource;
    ScAddress               aStartPos;
    BOOL                    bDoFilter;
    ScDPOutLevelData*       pColFields;
    ScDPOutLevelData*       pRowFields;
    ScDPOutLevelData*       pPageFields;
    long                    nColFieldCount;
    long                    nRowFieldCount;
    long                    nPageFieldCount;
    ::com::sun::star::uno::Sequence<
        ::com::sun::star::uno::Sequence<
            ::com::sun::star::sheet::DataResult> > aData;
    BOOL                    bResultsError;
    String                  aDataDescription;
    UINT32*                 pColNumFmt;
    UINT32*                 pRowNumFmt;
    long                    nColFmtCount;
    long                    nRowFmtCount;

    BOOL                    bSizesValid;
    BOOL                    bSizeOverflow;
    long                    nColCount;
    long                    nRowCount;
    long                    nHeaderSize;
    USHORT                  nTabStartCol;
    USHORT                  nTabStartRow;
    USHORT                  nMemberStartCol;
    USHORT                  nMemberStartRow;
    USHORT                  nDataStartCol;
    USHORT                  nDataStartRow;
    USHORT                  nTabEndCol;
    USHORT                  nTabEndRow;


public:
                     ~ScDPOutput();

    void            SetPosition( const ScAddress& rPos );


};


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
