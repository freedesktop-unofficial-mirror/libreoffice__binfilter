/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: starmath_config.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 08:24:17 $
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

#ifndef _SFXITEMSET_HXX //autogen
#include <bf_svtools/itemset.hxx>
#endif
#ifndef _SFXSIDS_HRC //autogen
#include <bf_sfx2/sfxsids.hrc>
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <bf_svtools/eitem.hxx>
#endif
#ifndef _SFXITEMPOOL_HXX //autogen
#include <bf_svtools/itempool.hxx>
#endif
#ifndef _SFXINTITEM_HXX //autogen
#include <bf_svtools/intitem.hxx>
#endif


#ifndef CONFIG_HXX
#include "config.hxx"
#endif
#ifndef _STARMATH_HRC
#include "starmath.hrc"
#endif
namespace binfilter {

/////////////////////////////////////////////////////////////////

/*N*/ SmConfig::SmConfig()
/*N*/ {
/*N*/ }


/*N*/ SmConfig::~SmConfig()
/*N*/ {
/*N*/ }




/*N*/ void SmConfig::ConfigToItemSet(SfxItemSet &rSet) const
/*N*/ {
/*N*/   const SfxItemPool *pPool = rSet.GetPool();
/*N*/
/*N*/   rSet.Put(SfxUInt16Item(pPool->GetWhich(SID_PRINTSIZE),
/*N*/                            (UINT16) GetPrintSize()));
/*N*/   rSet.Put(SfxUInt16Item(pPool->GetWhich(SID_PRINTZOOM),
/*N*/                            (UINT16) GetPrintZoomFactor()));
/*N*/
/*N*/     rSet.Put(SfxBoolItem(pPool->GetWhich(SID_PRINTTITLE), IsPrintTitle()));
/*N*/     rSet.Put(SfxBoolItem(pPool->GetWhich(SID_PRINTTEXT),  IsPrintFormulaText()));
/*N*/     rSet.Put(SfxBoolItem(pPool->GetWhich(SID_PRINTFRAME), IsPrintFrame()));
/*N*/     rSet.Put(SfxBoolItem(pPool->GetWhich(SID_AUTOREDRAW), IsAutoRedraw()));
/*N*/     rSet.Put(SfxBoolItem(pPool->GetWhich(SID_NO_RIGHT_SPACES), IsIgnoreSpacesRight()));
/*N*/ }


/////////////////////////////////////////////////////////////////


}
