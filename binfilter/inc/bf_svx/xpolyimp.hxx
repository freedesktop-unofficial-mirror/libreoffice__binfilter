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

#ifndef _XPOLYIMP_HXX
#define _XPOLYIMP_HXX

#include <bf_svtools/bf_solar.h>

#include <tools/gen.hxx>
#include <bf_svx/xpoly.hxx>
#include <vector>

#ifdef _MSC_VER
#pragma hdrstop
#endif
namespace binfilter {


/*************************************************************************
|*
|*    class ImpXPolygon
|*
*************************************************************************/
class ImpXPolygon
{
public:
    Point*          pPointAry;
    BYTE*           pFlagAry;
    Point*          pOldPointAry;
    BOOL            bDeleteOldPoints;
    USHORT          nSize;
    USHORT          nResize;
    USHORT          nPoints;
    USHORT          nRefCount;

    ImpXPolygon( USHORT nInitSize = 16, USHORT nResize=16 );
    ImpXPolygon( const ImpXPolygon& rImpXPoly );
    ~ImpXPolygon();

    bool operator==(const ImpXPolygon& rImpXPoly) const;
    bool operator!=(const ImpXPolygon& rImpXPoly) const { return !operator==(rImpXPoly); }

    void CheckPointDelete()
    {
        if ( bDeleteOldPoints )
        {
            delete[] (char*)pOldPointAry;
            bDeleteOldPoints = FALSE;
        }
    }

    void Resize( USHORT nNewSize, BOOL bDeletePoints = TRUE );
    void InsertSpace( USHORT nPos, USHORT nCount );
    void Remove( USHORT nPos, USHORT nCount );
};


/*************************************************************************
|*
|*    class ImpXPolyPolygon
|*
*************************************************************************/
typedef ::std::vector< XPolygon* > XPolygonList;

class ImpXPolyPolygon
{
public:
    XPolygonList aXPolyList;
    USHORT       nRefCount;

                 ImpXPolyPolygon()
                    { nRefCount = 1; }

                ImpXPolyPolygon( const ImpXPolyPolygon& rImpXPolyPoly );
                ~ImpXPolyPolygon();

};



}//end of namespace binfilter
#endif      // _XPOLYIMP_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
