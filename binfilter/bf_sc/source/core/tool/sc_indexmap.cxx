/*************************************************************************
 *
 *  $RCSfile: sc_indexmap.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 11:17:05 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/


#ifdef PCH
// auto strip #include "core_pch.hxx"
#endif

#pragma hdrstop


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
