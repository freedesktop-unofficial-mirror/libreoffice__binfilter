/*************************************************************************
 *
 *  $RCSfile: svx_chrtitem.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:45:04 $
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

// include ---------------------------------------------------------------

#ifndef _STREAM_HXX
#include <tools/stream.hxx>
#endif
#ifndef __SBX_SBXVARIABLE_HXX
#include <svtools/sbxvar.hxx>
#endif
#if defined UNX && !defined LINUX
#include <wchar.h>
#endif
#ifndef INCLUDED_RTL_MATH_HXX
#include <rtl/math.hxx>
#endif
#ifndef _UNOTOOLS_INTLWRAPPER_HXX
#include <unotools/intlwrapper.hxx>
#endif

#ifdef MAC
#include <stdlib.h>
#endif

#include <stdio.h>
#include <float.h>
#include <rtl/math.hxx>

#define ITEMID_CHARTSTYLE       0
#define ITEMID_CHARTDATADESCR   0
#define ITEMID_CHARTLEGENDPOS   0
#define ITEMID_CHARTTEXTORDER   0
#define ITEMID_CHARTTEXTORIENT  0
#define ITEMID_CHARTKINDERROR   0
#define ITEMID_CHARTINDICATE    0
#define ITEMID_DOUBLE           0
#define ITEMID_CHARTREGRESS     0

#include "chrtitem.hxx"

#pragma hdrstop
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;
// -----------------------------------------------------------------------

/*N*/ TYPEINIT1_AUTOFACTORY(SvxChartStyleItem, SfxEnumItem);
/*N*/ TYPEINIT1(SvxChartDataDescrItem, SfxEnumItem);
/*N*/ TYPEINIT1(SvxChartLegendPosItem, SfxEnumItem);
/*N*/ TYPEINIT1(SvxChartTextOrderItem, SfxEnumItem);
/*N*/ TYPEINIT1(SvxChartTextOrientItem, SfxEnumItem);
//STRIP001 TYPEINIT1(SvxChartIndicateItem, SfxEnumItem);
//STRIP001 TYPEINIT1(SvxChartKindErrorItem, SfxEnumItem);
//STRIP001 TYPEINIT1(SvxChartRegressItem, SfxEnumItem);
/*N*/ TYPEINIT1(SvxDoubleItem, SfxPoolItem);

/*************************************************************************
|*
|*  SvxChartStyleItem
|*
*************************************************************************/

/*N*/ SvxChartStyleItem::SvxChartStyleItem(SvxChartStyle eStyle, USHORT nId) :
/*N*/   SfxEnumItem(nId, eStyle)
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 SvxChartStyleItem::SvxChartStyleItem(SvStream& rIn, USHORT nId) :
//STRIP001  SfxEnumItem(nId, rIn)
//STRIP001 {
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxChartStyleItem::Clone(SfxItemPool* pPool) const
/*N*/ {
/*N*/   return new SvxChartStyleItem(*this);
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 SfxPoolItem* SvxChartStyleItem::Create(SvStream& rIn, USHORT nVer) const
//STRIP001 {
//STRIP001  return new SvxChartStyleItem(rIn, Which());
//STRIP001 }

/*************************************************************************
|*
|*  SvxChartDataDescrItem
|*
*************************************************************************/

/*N*/ SvxChartDataDescrItem::SvxChartDataDescrItem(SvxChartDataDescr eDataDescr,
/*N*/                                            USHORT nId) :
/*N*/   SfxEnumItem(nId, eDataDescr)
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxChartDataDescrItem::SvxChartDataDescrItem(SvStream& rIn, USHORT nId) :
/*N*/   SfxEnumItem(nId, rIn)
/*N*/ {
/*N*/ }

/*N*/ // -----------------------------------------------------------------------
/*N*/
/*N*/ SfxPoolItem* SvxChartDataDescrItem::Clone(SfxItemPool* pPool) const
/*N*/ {
/*N*/   return new SvxChartDataDescrItem(*this);
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxChartDataDescrItem::Create(SvStream& rIn, USHORT nVer) const
/*N*/ {
/*N*/   return new SvxChartDataDescrItem(rIn, Which());
/*N*/ }

/*************************************************************************
|*
|*  SvxChartLegendPosItem
|*
*************************************************************************/

/*N*/ SvxChartLegendPosItem::SvxChartLegendPosItem(SvxChartLegendPos eLegendPos,
/*N*/                                            USHORT nId) :
/*N*/   SfxEnumItem(nId, eLegendPos)
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxChartLegendPosItem::SvxChartLegendPosItem(SvStream& rIn, USHORT nId) :
/*N*/   SfxEnumItem(nId, rIn)
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxChartLegendPosItem::Clone(SfxItemPool* pPool) const
/*N*/ {
/*N*/   return new SvxChartLegendPosItem(*this);
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxChartLegendPosItem::Create(SvStream& rIn, USHORT nVer) const
/*N*/ {
/*N*/   return new SvxChartLegendPosItem(rIn, Which());
/*N*/ }

/*************************************************************************
|*
|*  SvxChartTextOrderItem
|*
*************************************************************************/

/*N*/ SvxChartTextOrderItem::SvxChartTextOrderItem(SvxChartTextOrder eOrder,
/*N*/                                            USHORT nId) :
/*N*/   SfxEnumItem(nId, eOrder)
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxChartTextOrderItem::SvxChartTextOrderItem(SvStream& rIn, USHORT nId) :
/*N*/   SfxEnumItem(nId, rIn)
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxChartTextOrderItem::Clone(SfxItemPool* pPool) const
/*N*/ {
/*N*/   return new SvxChartTextOrderItem(*this);
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxChartTextOrderItem::Create(SvStream& rIn, USHORT nVer) const
/*N*/ {
/*N*/   return new SvxChartTextOrderItem(rIn, Which());
/*N*/ }

/*************************************************************************
|*
|*  SvxChartTextOrientItem
|*
*************************************************************************/

/*N*/ SvxChartTextOrientItem::SvxChartTextOrientItem(SvxChartTextOrient eOrient,
/*N*/                                              USHORT nId) :
/*N*/   SfxEnumItem(nId, eOrient)
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxChartTextOrientItem::SvxChartTextOrientItem(SvStream& rIn, USHORT nId) :
/*N*/   SfxEnumItem(nId, rIn)
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxChartTextOrientItem::Clone(SfxItemPool* pPool) const
/*N*/ {
/*N*/   return new SvxChartTextOrientItem(*this);
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxChartTextOrientItem::Create(SvStream& rIn, USHORT nVer) const
/*N*/ {
/*N*/   return new SvxChartTextOrientItem(rIn, Which());
/*N*/ }

/*************************************************************************
|*
|*  SvxDoubleItem
|*
*************************************************************************/

/*N*/ SvxDoubleItem::SvxDoubleItem(double fValue, USHORT nId) :
/*N*/   SfxPoolItem(nId),
/*N*/   fVal(fValue)
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 SvxDoubleItem::SvxDoubleItem(SvStream& rIn, USHORT nId) :
//STRIP001  SfxPoolItem(nId)
//STRIP001 {
//STRIP001  rIn >> fVal;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ SvxDoubleItem::SvxDoubleItem(const SvxDoubleItem& rItem) :
/*N*/   SfxPoolItem(rItem),
/*N*/   fVal(rItem.fVal)
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 XubString SvxDoubleItem::GetValueText() const
//STRIP001 {
//STRIP001  ::rtl::OString aOStr( ::rtl::math::doubleToString( fVal, rtl_math_StringFormat_E, 4, '.', false ) );
//STRIP001  return String( aOStr.getStr(), (sal_uInt16)aOStr.getLength() );
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxDoubleItem::GetPresentation
//STRIP001          ( SfxItemPresentation ePresentation, SfxMapUnit eCoreMetric,
//STRIP001               SfxMapUnit ePresentationMetric, XubString& rText,
//STRIP001               const IntlWrapper * pIntlWrapper) const
//STRIP001 {
//STRIP001     DBG_ASSERT( pIntlWrapper, "SvxDoubleItem::GetPresentation: no IntlWrapper" );
//STRIP001     if ( pIntlWrapper )
//STRIP001     {
//STRIP001         rText = ::rtl::math::doubleToUString( fVal, rtl_math_StringFormat_E, 4,
//STRIP001             pIntlWrapper->getLocaleData()->getNumDecimalSep().GetChar(0), true );
//STRIP001     }
//STRIP001     else
//STRIP001      rText = GetValueText();
//STRIP001  return SFX_ITEM_PRESENTATION_NAMELESS;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ int SvxDoubleItem::operator == (const SfxPoolItem& rItem) const
/*N*/ {
/*N*/   return (((SvxDoubleItem&)rItem).fVal == fVal);
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxDoubleItem::Clone(SfxItemPool* Pool) const
/*N*/ {
/*N*/   return new SvxDoubleItem(*this);
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxDoubleItem::Create(SvStream& rIn, USHORT nVersion) const
/*N*/ {
/*N*/   double fVal;
/*N*/   rIn >> fVal;
/*N*/   return new SvxDoubleItem(fVal, Which());
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxDoubleItem::Store(SvStream& rOut, USHORT nItemVersion) const
/*N*/ {
/*N*/   rOut << fVal;
/*N*/   return rOut;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 double SvxDoubleItem::GetMin() const
//STRIP001 {
//STRIP001  return DBL_MIN;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 double SvxDoubleItem::GetMax() const
//STRIP001 {
//STRIP001  return DBL_MAX;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SfxFieldUnit SvxDoubleItem::GetUnit() const
//STRIP001 {
//STRIP001  return SFX_FUNIT_NONE;
//STRIP001 }




// -----------------------------------------------------------------------
/*N*/ sal_Bool SvxDoubleItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/   rVal <<= fVal;
/*N*/   return sal_True;
/*N*/ }

// -----------------------------------------------------------------------
/*N*/ sal_Bool SvxDoubleItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/   return rVal >>= fVal;
/*N*/ }



/*************************************************************************
|*
|*  SvxChartKindErrorItem
|*
*************************************************************************/

//STRIP001 SvxChartKindErrorItem::SvxChartKindErrorItem(SvxChartKindError eOrient,
//STRIP001                                             USHORT nId) :
//STRIP001  SfxEnumItem(nId, eOrient)
//STRIP001 {
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SvxChartKindErrorItem::SvxChartKindErrorItem(SvStream& rIn, USHORT nId) :
//STRIP001  SfxEnumItem(nId, rIn)
//STRIP001 {
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SfxPoolItem* SvxChartKindErrorItem::Clone(SfxItemPool* pPool) const
//STRIP001 {
//STRIP001  return new SvxChartKindErrorItem(*this);
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SfxPoolItem* SvxChartKindErrorItem::Create(SvStream& rIn, USHORT nVer) const
//STRIP001 {
//STRIP001  return new SvxChartKindErrorItem(rIn, Which());
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 USHORT SvxChartKindErrorItem::GetVersion (USHORT nFileFormatVersion) const
//STRIP001 {
//STRIP001  return (nFileFormatVersion == SOFFICE_FILEFORMAT_31)
//STRIP001             ? USHRT_MAX
//STRIP001             : 0;
//STRIP001 }

/*************************************************************************
|*
|*  SvxChartIndicateItem
|*
*************************************************************************/

//STRIP001 SvxChartIndicateItem::SvxChartIndicateItem(SvxChartIndicate eOrient,
//STRIP001                                             USHORT nId) :
//STRIP001  SfxEnumItem(nId, eOrient)
//STRIP001 {
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SvxChartIndicateItem::SvxChartIndicateItem(SvStream& rIn, USHORT nId) :
//STRIP001  SfxEnumItem(nId, rIn)
//STRIP001 {
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SfxPoolItem* SvxChartIndicateItem::Clone(SfxItemPool* pPool) const
//STRIP001 {
//STRIP001  return new SvxChartIndicateItem(*this);
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SfxPoolItem* SvxChartIndicateItem::Create(SvStream& rIn, USHORT nVer) const
//STRIP001 {
//STRIP001  return new SvxChartIndicateItem(rIn, Which());
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 USHORT SvxChartIndicateItem::GetVersion (USHORT nFileFormatVersion) const
//STRIP001 {
//STRIP001  return (nFileFormatVersion == SOFFICE_FILEFORMAT_31)
//STRIP001             ? USHRT_MAX
//STRIP001             : 0;
//STRIP001 }

/*************************************************************************
|*
|*  SvxChartRegressItem
|*
*************************************************************************/

//STRIP001 SvxChartRegressItem::SvxChartRegressItem(SvxChartRegress eOrient,
//STRIP001                                             USHORT nId) :
//STRIP001  SfxEnumItem(nId, eOrient)
//STRIP001 {
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SvxChartRegressItem::SvxChartRegressItem(SvStream& rIn, USHORT nId) :
//STRIP001  SfxEnumItem(nId, rIn)
//STRIP001 {
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SfxPoolItem* SvxChartRegressItem::Clone(SfxItemPool* pPool) const
//STRIP001 {
//STRIP001  return new SvxChartRegressItem(*this);
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SfxPoolItem* SvxChartRegressItem::Create(SvStream& rIn, USHORT nVer) const
//STRIP001 {
//STRIP001  return new SvxChartRegressItem(rIn, Which());
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 USHORT SvxChartRegressItem::GetVersion (USHORT nFileFormatVersion) const
//STRIP001 {
//STRIP001  return (nFileFormatVersion == SOFFICE_FILEFORMAT_31)
//STRIP001             ? USHRT_MAX
//STRIP001             : 0;
//STRIP001 }


}
