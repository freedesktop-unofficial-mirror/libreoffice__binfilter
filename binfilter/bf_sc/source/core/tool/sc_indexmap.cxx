/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_indexmap.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 10:46:35 $
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


#include <memory.h>

#include "indexmap.hxx"
namespace binfilter {


/*N*/ ScIndexMap::ScIndexMap( USHORT nEntries )
/*N*/ {
/*N*/   nCount = nEntries;
/*N*/   ULONG nC = nEntries ? ((ULONG) nEntries * 2) : 2;
/*N*/   pMap = new USHORT [ nC ];
/*N*/   memset( pMap, 0, nC * sizeof(USHORT) );
/*N*/ }


/*N*/ ScIndexMap::~ScIndexMap()
/*N*/ {
/*N*/   delete [] pMap;
/*N*/ }


/*N*/ void ScIndexMap::SetPair( USHORT nEntry, USHORT nIndex1, USHORT nIndex2 )
/*N*/ {
/*N*/   if ( nEntry < nCount )
/*N*/   {
/*N*/       ULONG nOff = (ULONG) nEntry * 2;
/*N*/       pMap[nOff] = nIndex1;
/*N*/       pMap[nOff+1] = nIndex2;
/*N*/   }
/*N*/ }


/*N*/  USHORT ScIndexMap::Find( USHORT nIndex1 ) const
/*N*/  {
/*N*/   USHORT* pStop = pMap + (ULONG) nCount * 2;
/*N*/   for ( USHORT* pOff = pMap; pOff < pStop; pOff += 2 )
/*N*/   {
/*N*/       if ( *pOff == nIndex1 )
/*N*/           return *(pOff+1);
/*N*/   }
/*N*/   return nIndex1;
/*N*/  }


}
