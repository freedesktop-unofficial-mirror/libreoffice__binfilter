/*************************************************************************
 *
 *  $RCSfile: sw_ring.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:06:20 $
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


#pragma hdrstop

#include "ring.hxx"


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

//STRIP001 void Ring::MoveRingTo(Ring *pDestRing)
//STRIP001 {
//STRIP001  // den gesamten Ring in den DestRing einfuegen
//STRIP001  Ring* pMyPrev = pPrev;
//STRIP001  Ring* pDestPrev = pDestRing->pPrev;
//STRIP001
//STRIP001  pMyPrev->pNext = pDestRing;
//STRIP001  pDestPrev->pNext = this;
//STRIP001  pDestRing->pPrev = pMyPrev;
//STRIP001  pPrev = pDestPrev;
//STRIP001 }


