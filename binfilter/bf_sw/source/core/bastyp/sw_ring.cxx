/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_ring.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:52:26 $
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


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "ring.hxx"
namespace binfilter {


/*************************************************************************
|*
|*    Ring::Ring()
|*
|*    Ersterstellung    VB  02.07.91
|*    Letzte Aenderung  JP 10.10.97
|*
*************************************************************************/

/*N*/ Ring::Ring( Ring *pObj )
/*N*/ {
/*N*/   if( !pObj )
/*N*/       pNext = this, pPrev = this;
/*N*/   else
/*N*/   {
/*?*/       pNext = pObj;
/*?*/       pPrev = pObj->pPrev;
/*?*/       pObj->pPrev = this;
/*?*/       pPrev->pNext = this;
/*N*/   }
}

/*************************************************************************
|*
|*    Ring::~Ring()
|*
|*    Ersterstellung    VB  02.07.91
|*    Letzte Aenderung  JP 10.10.97
|*
*************************************************************************/

/*N*/ Ring::~Ring()
/*N*/ {
/*N*/   pNext->pPrev = pPrev;
/*N*/   pPrev->pNext = pNext;
/*N*/ }

/*************************************************************************
|*
|*    Ring::MoveTo
|*
|*    Ersterstellung    VB 4.3.91
|*    Letzte Aenderung  JP 10.10.97
|*
*************************************************************************/

/*N*/ void Ring::MoveTo(Ring *pDestRing)
/*N*/ {
/*N*/   // loeschen aus dem alten
/*N*/   pNext->pPrev = pPrev;
/*N*/   pPrev->pNext = pNext;
/*N*/
/*N*/   // im neuen einfuegen
/*N*/   if( pDestRing )
/*N*/   {
/*N*/       pNext = pDestRing;
/*N*/       pPrev = pDestRing->pPrev;
/*N*/       pDestRing->pPrev = this;
/*N*/       pPrev->pNext = this;
/*N*/   }
/*N*/   else
/*N*/       pNext = pPrev = this;
/*N*/
/*N*/ }



}
