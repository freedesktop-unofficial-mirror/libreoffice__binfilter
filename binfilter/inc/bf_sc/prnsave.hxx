/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: prnsave.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:22:49 $
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

#ifndef SC_PRNSAVE_HXX
#define SC_PRNSAVE_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
namespace binfilter {

class ScRange;

class ScPrintSaverTab
{
    USHORT      nPrintCount;
    ScRange*    pPrintRanges;   // Array
    ScRange*    pRepeatCol;     // einzeln
    ScRange*    pRepeatRow;     // einzeln

public:
            ScPrintSaverTab();
            ~ScPrintSaverTab();

    void    SetAreas( USHORT nCount, const ScRange* pRanges );
    void    SetRepeat( const ScRange* pCol, const ScRange* pRow );

    USHORT          GetPrintCount() const   { return nPrintCount; }
    const ScRange*  GetPrintRanges() const  { return pPrintRanges; }
    const ScRange*  GetRepeatCol() const    { return pRepeatCol; }
    const ScRange*  GetRepeatRow() const    { return pRepeatRow; }

//STRIP001  BOOL    operator==( const ScPrintSaverTab& rCmp ) const;
};

class ScPrintRangeSaver
{
    USHORT              nTabCount;
    ScPrintSaverTab*    pData;      // Array

public:
            ScPrintRangeSaver( USHORT nCount );
            ~ScPrintRangeSaver();

    USHORT                  GetTabCount() const     { return nTabCount; }
    ScPrintSaverTab&        GetTabData(USHORT nTab);
//STRIP001  const ScPrintSaverTab&  GetTabData(USHORT nTab) const;

//STRIP001  BOOL    operator==( const ScPrintRangeSaver& rCmp ) const;
};


} //namespace binfilter
#endif


