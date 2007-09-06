/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_pntlock.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:07:08 $
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

#ifdef PCH
#endif

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "pntlock.hxx"
namespace binfilter {

//------------------------------------------------------------------------

/*N*/ ScPaintLockData::ScPaintLockData(USHORT nNewMode) :
/*N*/   nMode( nNewMode ),
/*N*/   nParts( 0 ),
/*N*/   nLevel( 0 ),
/*N*/   nDocLevel( 0 ),
/*N*/   bModified( FALSE )
/*N*/ {
/*N*/ }

/*N*/ ScPaintLockData::~ScPaintLockData()
/*N*/ {
/*N*/ }

/*N*/ void ScPaintLockData::AddRange( const ScRange& rRange, USHORT nP )
/*N*/ {
/*N*/   if (!xRangeList.Is())
/*N*/       xRangeList = new ScRangeList;
/*N*/
/*N*/   xRangeList->Join( rRange );
/*N*/   nParts |= nP;
/*N*/ }




}
