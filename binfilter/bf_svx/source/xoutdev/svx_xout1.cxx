/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_xout1.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:49:34 $
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

#include "xoutx.hxx"

#ifdef JOEDEBUG
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

}
