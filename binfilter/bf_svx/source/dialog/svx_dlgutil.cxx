/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_dlgutil.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: obo $ $Date: 2007-03-09 15:29:32 $
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

// include ---------------------------------------------------------------

#include <limits.h>

#include "dialogs.hrc"

#include "dlgutil.hxx"
namespace binfilter {

/*N*/ FieldUnit GetModuleFieldUnit( const SfxItemSet* pSet )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   FieldUnit eUnit = FUNIT_INCH;
/*N*/   return eUnit;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ long CalcToUnit( float nIn, SfxMapUnit eUnit )
/*N*/ {
/*N*/   // nIn ist in Points
/*N*/
/*N*/   DBG_ASSERT( eUnit == SFX_MAPUNIT_TWIP       ||
/*N*/               eUnit == SFX_MAPUNIT_100TH_MM   ||
/*N*/               eUnit == SFX_MAPUNIT_10TH_MM    ||
/*N*/               eUnit == SFX_MAPUNIT_MM         ||
/*N*/               eUnit == SFX_MAPUNIT_CM, "this unit is not implemented" );
/*N*/
/*N*/   float nTmp = nIn;
/*N*/
/*N*/   if ( SFX_MAPUNIT_TWIP != eUnit )
/*N*/       nTmp = nIn * 10 / 567;
/*N*/
/*N*/   switch ( eUnit )
/*N*/   {
/*N*/       case SFX_MAPUNIT_100TH_MM:  nTmp *= 100; break;
/*?*/       case SFX_MAPUNIT_10TH_MM:   nTmp *= 10;  break;
/*?*/       case SFX_MAPUNIT_MM:                     break;
/*?*/       case SFX_MAPUNIT_CM:        nTmp /= 10;  break;
/*N*/   }
/*N*/
/*N*/   nTmp *= 20;
/*N*/   long nRet = (long)nTmp;
/*N*/   return nRet;
/*N*/ //!   return (long)(nTmp * 20);
/*N*/ }

// -----------------------------------------------------------------------

/*?*/ long ItemToControl( long nIn, SfxMapUnit eItem, SfxFieldUnit eCtrl )
/*?*/ {
/*?*/ DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001 //STRIP001     long nOut = 0;
/*?*/ }

// -----------------------------------------------------------------------

/*N*/ long CalcToPoint( long nIn, SfxMapUnit eUnit, USHORT nFaktor )
/*N*/ {
/*N*/   DBG_ASSERT( eUnit == SFX_MAPUNIT_TWIP       ||
/*N*/               eUnit == SFX_MAPUNIT_100TH_MM   ||
/*N*/               eUnit == SFX_MAPUNIT_10TH_MM    ||
/*N*/               eUnit == SFX_MAPUNIT_MM         ||
/*N*/               eUnit == SFX_MAPUNIT_CM, "this unit is not implemented" );
/*N*/
/*N*/   long nRet = 0;
/*N*/
/*N*/   if ( SFX_MAPUNIT_TWIP == eUnit )
/*N*/       nRet = nIn;
/*N*/   else
/*N*/       nRet = nIn * 567;
/*N*/
/*N*/   switch ( eUnit )
/*N*/   {
/*N*/       case SFX_MAPUNIT_100TH_MM:  nRet /= 100; break;
/*?*/       case SFX_MAPUNIT_10TH_MM:   nRet /= 10;  break;
/*?*/       case SFX_MAPUNIT_MM:                     break;
/*?*/       case SFX_MAPUNIT_CM:        nRet *= 10;  break;
/*N*/   }
/*N*/
/*N*/   // ggf. aufrunden
/*N*/   if ( SFX_MAPUNIT_TWIP != eUnit )
/*N*/   {
/*N*/       long nMod = 10;
/*N*/       long nTmp = nRet % nMod;
/*N*/
/*N*/       if ( nTmp >= 4 )
/*N*/           nRet += 10 - nTmp;
/*N*/       nRet /= 10;
/*N*/   }
/*N*/   return nRet * nFaktor / 20;
/*N*/ }

}
