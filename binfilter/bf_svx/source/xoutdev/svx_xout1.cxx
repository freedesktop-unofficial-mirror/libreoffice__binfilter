/*************************************************************************
 *
 *  $RCSfile: svx_xout1.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 16:52:33 $
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

#include "xoutx.hxx"

#ifdef JOEDEBUG
// auto strip #include "Q:\joedebug.hxx"
#endif
namespace binfilter {

#define GLOBALOVERFLOW

/*************************************************************************
|*
|*    XOutputDevice::SetOffset()
|*
|*    Beschreibung
|*    Ersterstellung    08.11.94
|*    Letzte Aenderung  08.11.94
|*
*************************************************************************/

/*N*/ void XOutputDevice::SetOffset( const Point& rOfs )
/*N*/ {
/*N*/   if (rOfs!=aOfs)
/*N*/   {
/*N*/       Point aDelta(rOfs);
/*N*/       Fraction aFact1(1,1);
/*N*/       aDelta-=aOfs;
/*N*/ #ifdef neeJOEDEBUG
/*N*/       DebWrite("XOutputDevice::SetOffset(");
/*N*/       DebOut(rOfs);
/*N*/       DebWrite("Alter Offset: ");
/*N*/       DebOut(aOfs);
/*N*/       DebWrite("Alter Origin: ");
/*N*/       DebOut(pOut->GetMapMode().GetOrigin());
/*N*/       DebWrite("Delta: ");
/*N*/       DebOut(aDelta);
/*N*/ #endif
//#ifdef JOEDEBUG
////        pOut->SetMapMode(MapMode(MAP_RELATIVE,Point(-aOfs.X(),-aOfs.Y()),aFact1,aFact1));
////        pOut->SetMapMode(MapMode(MAP_RELATIVE,rOfs,aFact1,aFact1));
/*N*/       pOut->SetMapMode(MapMode(MAP_RELATIVE,aDelta,aFact1,aFact1));
//#else
//        MapMode aMap(pOut->GetMapMode());
//        Point   aOrg(aMap.GetOrigin());
//        aOrg.X()+=aDelta.X();
//        aOrg.Y()+=aDelta.Y();
//        aMap.SetOrigin(aOrg);
//        pOut->SetMapMode(aMap);
//#endif
/*N*/       aOfs=rOfs;
/*N*/ #ifdef neeJOEDEBUG
/*N*/       DebWrite("Neuer Offset: ");
/*N*/       DebOut(aOfs);
/*N*/       DebWrite("Neuer Origin: ");
/*N*/       DebOut(pOut->GetMapMode().GetOrigin());
/*N*/ #endif
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|*    XOutputDevice::GetMapMode()
|*
|*    Beschreibung
|*    Ersterstellung    08.11.94
|*    Letzte Aenderung  08.11.94
|*
*************************************************************************/

/*N*/ MapMode XOutputDevice::GetMapMode() const
/*N*/ {
/*N*/   MapMode aMap = pOut->GetMapMode();
/*N*/   Point   aPos = aMap.GetOrigin();
/*N*/
/*N*/   aPos.X() -= aOfs.X();
/*N*/   aPos.Y() -= aOfs.Y();
/*N*/
/*N*/   aMap.SetOrigin( aPos );
/*N*/
/*N*/   return aMap;
/*N*/ }


/*************************************************************************
|*
|*    XOutputDevice::SetMapMode()
|*
|*    Beschreibung
|*    Ersterstellung    08.11.94
|*    Letzte Aenderung  08.11.94
|*
*************************************************************************/

/*N*/ void XOutputDevice::SetMapMode( const MapMode& rMap )
/*N*/ {
/*N*/   Point aPos = rMap.GetOrigin();
/*N*/   aPos.X() += aOfs.X();
/*N*/   aPos.Y() += aOfs.Y();
/*N*/
/*N*/   MapMode aMap( rMap );
/*N*/   aMap.SetOrigin( aPos );
/*N*/
/*N*/   pOut->SetMapMode( aMap );
/*N*/ }



}
