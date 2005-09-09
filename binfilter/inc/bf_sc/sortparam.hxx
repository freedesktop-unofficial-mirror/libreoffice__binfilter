/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sortparam.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:30:23 $
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

#ifndef SC_SORTPARAM_HXX
#define SC_SORTPARAM_HXX

#ifndef _STRING_HXX
#include <tools/string.hxx>
#endif
#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
#ifndef _COM_SUN_STAR_LANG_LOCALE_HPP_
#include <com/sun/star/lang/Locale.hpp>
#endif
namespace binfilter {


#define MAXSORT     3


struct ScSubTotalParam;
struct ScQueryParam;

struct ScSortParam
{
    USHORT      nCol1;
    USHORT      nRow1;
    USHORT      nCol2;
    USHORT      nRow2;
    BOOL        bHasHeader;
    BOOL        bByRow;
    BOOL        bCaseSens;
    BOOL        bUserDef;
    USHORT      nUserIndex;
    BOOL        bIncludePattern;
    BOOL        bInplace;
    USHORT      nDestTab;
    USHORT      nDestCol;
    USHORT      nDestRow;
    BOOL        bDoSort[MAXSORT];
    USHORT      nField[MAXSORT];
    BOOL        bAscending[MAXSORT];
    ::com::sun::star::lang::Locale      aCollatorLocale;
    String      aCollatorAlgorithm;

    ScSortParam();
    ScSortParam( const ScSortParam& r );
    /// SubTotals sort
//STRIP001  ScSortParam( const ScSubTotalParam& rSub, const ScSortParam& rOld );
    /// TopTen sort
//STRIP001  ScSortParam( const ScQueryParam&, USHORT nCol );

//STRIP001  ScSortParam&    operator=   ( const ScSortParam& r );
//STRIP001  BOOL            operator==  ( const ScSortParam& rOther ) const;
    void            Clear       ();

//STRIP001  void            MoveToDest();
};


} //namespace binfilter
#endif // SC_SORTPARAM_HXX
