/*************************************************************************
 *
 *  $RCSfile: starmath_config.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:19:17 $
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

#ifndef _SFXITEMSET_HXX //autogen
#include <svtools/itemset.hxx>
#endif
#ifndef _SFXHINT_HXX //autogen
#include <svtools/hint.hxx>
#endif
#ifndef _SFXSMPLHINT_HXX //autogen
#include <svtools/smplhint.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_PATHOPTIONS_HXX
#include <svtools/pathoptions.hxx>
#endif
#ifndef _SFXSIDS_HRC //autogen
#include <bf_sfx2/sfxsids.hrc>
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#ifndef _SFXITEMPOOL_HXX //autogen
#include <svtools/itempool.hxx>
#endif
#ifndef _SFXSTRITEM_HXX //autogen
#include <svtools/stritem.hxx>
#endif
#ifndef _SFXINTITEM_HXX //autogen
#include <svtools/intitem.hxx>
#endif
#ifndef _STREAM_HXX
#include <tools/stream.hxx>
#endif


#ifndef CONFIG_HXX
#include "config.hxx"
#endif
#ifndef FORMAT_HXX
#include "format.hxx"
#endif
#ifndef _SMMOD_HXX
#include "smmod.hxx"
#endif
#ifndef _STARMATH_HRC
#include "starmath.hrc"
#endif

/////////////////////////////////////////////////////////////////

/*N*/ SmConfig::SmConfig()
/*N*/ {
/*N*/ }


/*N*/ SmConfig::~SmConfig()
/*N*/ {
/*N*/ }


//STRIP001 void SmConfig::ItemSetToConfig(const SfxItemSet &rSet)
//STRIP001 {
//STRIP001  const SfxPoolItem *pItem     = NULL;
//STRIP001
//STRIP001  UINT16 nU16;
//STRIP001  BOOL bVal;
//STRIP001  if (rSet.GetItemState(SID_PRINTSIZE, TRUE, &pItem) == SFX_ITEM_SET)
//STRIP001  {   nU16 = ((const SfxUInt16Item *) pItem)->GetValue();
//STRIP001         SetPrintSize( (SmPrintSize) nU16 );
//STRIP001  }
//STRIP001     if (rSet.GetItemState(SID_PRINTZOOM, TRUE, &pItem) == SFX_ITEM_SET)
//STRIP001  {   nU16 = ((const SfxUInt16Item *) pItem)->GetValue();
//STRIP001         SetPrintZoomFactor( nU16 );
//STRIP001  }
//STRIP001  if (rSet.GetItemState(SID_PRINTTITLE, TRUE, &pItem) == SFX_ITEM_SET)
//STRIP001  {   bVal = ((const SfxBoolItem *) pItem)->GetValue();
//STRIP001         SetPrintTitle( bVal );
//STRIP001  }
//STRIP001  if (rSet.GetItemState(SID_PRINTTEXT, TRUE, &pItem) == SFX_ITEM_SET)
//STRIP001  {   bVal = ((const SfxBoolItem *) pItem)->GetValue();
//STRIP001         SetPrintFormulaText( bVal );
//STRIP001  }
//STRIP001  if (rSet.GetItemState(SID_PRINTFRAME, TRUE, &pItem) == SFX_ITEM_SET)
//STRIP001  {   bVal = ((const SfxBoolItem *) pItem)->GetValue();
//STRIP001         SetPrintFrame( bVal );
//STRIP001  }
//STRIP001  if (rSet.GetItemState(SID_AUTOREDRAW, TRUE, &pItem) == SFX_ITEM_SET)
//STRIP001  {   bVal = ((const SfxBoolItem *) pItem)->GetValue();
//STRIP001         SetAutoRedraw( bVal );
//STRIP001  }
//STRIP001  if (rSet.GetItemState(SID_NO_RIGHT_SPACES, TRUE, &pItem) == SFX_ITEM_SET)
//STRIP001  {   bVal = ((const SfxBoolItem *) pItem)->GetValue();
//STRIP001         if (IsIgnoreSpacesRight() != bVal)
//STRIP001         {
//STRIP001             SetIgnoreSpacesRight( bVal );
//STRIP001
//STRIP001          // (angezeigte) Formeln müssen entsprechen neu formatiert werden.
//STRIP001          // Das erreichen wir mit:
//STRIP001          Broadcast(SfxSimpleHint(HINT_FORMATCHANGED));
//STRIP001      }
//STRIP001  }
//STRIP001 }


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


