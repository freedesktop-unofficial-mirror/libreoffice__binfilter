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

#ifndef SC_MARKARR_HXX
#define SC_MARKARR_HXX

#include <bf_svtools/bf_solar.h>
namespace binfilter {

#define SC_MARKARRAY_DELTA    4

struct ScMarkEntry
{
    USHORT          nRow;
    BOOL            bMarked;
};

class ScMarkArray
{
    USHORT          nCount;
    USHORT          nLimit;
    ScMarkEntry*    pData;

friend class ScMarkArrayIter;
friend class ScDocument;                // fuer FillInfo

public:
            ScMarkArray();
            ~ScMarkArray();
    void    Reset( BOOL bMarked = FALSE );
    BOOL    GetMark( USHORT nRow ) const;
    void    SetMarkArea( USHORT nStartRow, USHORT nEndRow, BOOL bMarked );
    BOOL    IsAllMarked( USHORT nStartRow, USHORT nEndRow ) const;
    BOOL    HasOneMark( USHORT& rStartRow, USHORT& rEndRow ) const;
    BOOL    HasMarks() const;
    void    CopyMarksTo( ScMarkArray& rDestMarkArray ) const;

    BOOL    Search( USHORT nRow, short& nIndex ) const;

    short   GetNextMarked( short nRow, BOOL bUp ) const;        // inkl. aktuelle
    USHORT  GetMarkEnd( USHORT nRow, BOOL bUp ) const;
};


class ScMarkArrayIter                   // selektierte Bereiche durchgehen
{
    const ScMarkArray*  pArray;
    USHORT              nPos;
public:
                ScMarkArrayIter( const ScMarkArray* pNewArray );
                ~ScMarkArrayIter();

    BOOL        Next( USHORT& rTop, USHORT& rBottom );
};



} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
