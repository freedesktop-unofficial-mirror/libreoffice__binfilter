/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: pfuncache.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 20:06:17 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#ifndef SC_PFUNCACHE_HXX
#define SC_PFUNCACHE_HXX

#ifndef SC_RANGELST_HXX
#include "rangelst.hxx"
#endif
namespace binfilter {

class ScDocShell;
class ScMarkData;


/** Possible types of selection for print functions */

enum ScPrintSelectionMode
{
    SC_PRINTSEL_INVALID,
    SC_PRINTSEL_DOCUMENT,
    SC_PRINTSEL_CURSOR,
    SC_PRINTSEL_RANGE
};


/** Stores the selection in the ScPrintFuncCache so it is only used
    for the same selection again. */

class ScPrintSelectionStatus
{
    ScPrintSelectionMode    eMode;
    ScRangeList             aRanges;

public:
            ScPrintSelectionStatus() : eMode(SC_PRINTSEL_INVALID) {}
            ~ScPrintSelectionStatus() {}

    void    SetMode(ScPrintSelectionMode eNew)  { eMode = eNew; }
    void    SetRanges(const ScRangeList& rNew)  { aRanges = rNew; }

    BOOL    operator==(const ScPrintSelectionStatus& rOther) const
            { return eMode == rOther.eMode && aRanges == rOther.aRanges; }
};


/** Stores the data for printing that is needed from several sheets,
    so it doesn't have to be calculated for rendering each page. */

class ScPrintFuncCache
{
    ScPrintSelectionStatus  aSelection;
    ScDocShell*             pDocSh;
    long                    nTotalPages;
    long                    nPages[MAXTAB+1];
    long                    nFirstAttr[MAXTAB+1];

public:
            ScPrintFuncCache( ScDocShell* pD, const ScMarkData& rMark,
                                const ScPrintSelectionStatus& rStatus );
            ~ScPrintFuncCache();

    BOOL    IsSameSelection( const ScPrintSelectionStatus& rStatus ) const;

    long    GetPageCount() const                { return nTotalPages; }
    long    GetFirstAttr( USHORT nTab ) const   { return nFirstAttr[nTab]; }
    USHORT  GetTabForPage( long nPage ) const;
    long    GetTabStart( USHORT nTab ) const;
    long    GetDisplayStart( USHORT nTab ) const;
};

} //namespace binfilter
#endif

