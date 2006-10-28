/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: dpoutput.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:34:15 $
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

#ifndef SC_DPOUTPUT_HXX
#define SC_DPOUTPUT_HXX

#ifndef _COM_SUN_STAR_SHEET_XDIMENSIONSSUPPLIER_HPP_
#include <com/sun/star/sheet/XDimensionsSupplier.hpp>
#endif

#ifndef _COM_SUN_STAR_SHEET_DATARESULT_HPP_
#include <com/sun/star/sheet/DataResult.hpp>
#endif


#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif
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
                     ScDPOutput( ScDocument* pD,
                                const ::com::sun::star::uno::Reference<
                                     ::com::sun::star::sheet::XDimensionsSupplier>& xSrc,
                                 const ScAddress& rPos, BOOL bFilter );
                     ~ScDPOutput();

    void            SetPosition( const ScAddress& rPos );


};


} //namespace binfilter
#endif

