/*************************************************************************
 *
 *  $RCSfile: sw_uiitems.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:58:18 $
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

#ifndef _SVX_ITEMTYPE_HXX
#include <bf_svx/itemtype.hxx>
#endif
#ifndef _UNOSETT_HXX
#include <unosett.hxx>
#endif

#include "uiparam.hxx"
#include "swtypes.hxx"
#include "cmdid.h"
#include "pagedesc.hxx"
#include "uiitems.hxx"

#include "utlui.hrc"
#include "attrdesc.hrc"
#ifndef _UNOMID_H
#include <unomid.h>
#endif
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;

// Breitenangaben der Fussnotenlinien, mit TabPage abstimmen
static const USHORT __FAR_DATA nFtnLines[] = {
    0,
    10,
    50,
    80,
    100,
    150
};

#define FTN_LINE_STYLE_COUNT 5


/*N*/ SwPageFtnInfoItem::SwPageFtnInfoItem( const USHORT nId, SwPageFtnInfo& rInfo) :
/*N*/   SfxPoolItem( nId ),
/*N*/   aFtnInfo(rInfo)
/*N*/ {
/*N*/ }


/*N*/ SwPageFtnInfoItem::SwPageFtnInfoItem( const SwPageFtnInfoItem& rItem ) :
/*N*/   SfxPoolItem( rItem ),
/*N*/   aFtnInfo(rItem.GetPageFtnInfo())
/*N*/ {
/*N*/ }


/*N*/  SwPageFtnInfoItem::~SwPageFtnInfoItem()
/*N*/ {
/*N*/ }


/*N*/ SfxPoolItem*  SwPageFtnInfoItem::Clone( SfxItemPool *pPool ) const
/*N*/ {
/*N*/   return new SwPageFtnInfoItem( *this );
/*N*/ }


/*N*/ int  SwPageFtnInfoItem::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/   DBG_ASSERT( Which() == rAttr.Which(), "keine gleichen Attribute" );
/*N*/   return ( aFtnInfo == ((SwPageFtnInfoItem&)rAttr).GetPageFtnInfo());
/*N*/ }


//STRIP001 SfxItemPresentation  SwPageFtnInfoItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001  String&             rText,
//STRIP001     const IntlWrapper*    pIntl
//STRIP001 )    const
//STRIP001 {
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          return SFX_ITEM_PRESENTATION_NONE;
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001      {
//STRIP001          USHORT nHght = (USHORT) GetPageFtnInfo().GetHeight();
//STRIP001          if ( nHght )
//STRIP001          {
//STRIP001              rText = SW_RESSTR( STR_MAX_FTN_HEIGHT );
//STRIP001              rText += ' ';
//STRIP001              rText += ::GetMetricText( nHght, eCoreUnit, ePresUnit, pIntl );
//STRIP001              rText += ::GetSvxString( ::GetMetricId( ePresUnit ) );
//STRIP001          }
//STRIP001          return ePres;
//STRIP001      }
//STRIP001  }
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }
/* -----------------------------26.04.01 12:25--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ BOOL SwPageFtnInfoItem::QueryValue( Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/     sal_Bool bRet = sal_True;
/*N*/     switch(nMemberId & ~CONVERT_TWIPS)
/*N*/     {
/*N*/         case MID_FTN_HEIGHT        :     rVal <<= (sal_Int32)TWIP_TO_MM100(aFtnInfo.GetHeight());break;
/*N*/         case MID_LINE_WEIGHT       :     rVal <<= (sal_Int16)TWIP_TO_MM100(aFtnInfo.GetLineWidth());break;
/*N*/         case MID_LINE_COLOR        :     rVal <<= (sal_Int32)aFtnInfo.GetLineColor().GetColor();break;
/*N*/         case MID_LINE_RELWIDTH     :
/*N*/         {
/*N*/             Fraction aTmp( 100, 1 );
/*N*/             aTmp *= aFtnInfo.GetWidth();
/*N*/             rVal <<= (sal_Int8)(long)aTmp;
/*N*/         }
/*N*/         break;
/*N*/         case MID_LINE_ADJUST       :     rVal <<= (sal_Int16)aFtnInfo.GetAdj();break;//com::sun::star::text::HorizontalAdjust
/*N*/         case MID_LINE_TEXT_DIST    :     rVal <<= (sal_Int32)TWIP_TO_MM100(aFtnInfo.GetTopDist());break;
/*N*/         case MID_LINE_FOOTNOTE_DIST:     rVal <<= (sal_Int32)TWIP_TO_MM100(aFtnInfo.GetBottomDist());break;
/*N*/         default:
/*N*/             bRet = sal_False;
/*N*/     }
/*N*/     return bRet;
/*N*/ }
/* -----------------------------26.04.01 12:26--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ BOOL SwPageFtnInfoItem::PutValue(const Any& rVal, BYTE nMemberId)
/*N*/ {
/*N*/     sal_Int32 nSet32;
/*N*/     sal_Bool bRet = sal_True;
/*N*/     switch(nMemberId  & ~CONVERT_TWIPS)
/*N*/     {
/*N*/         case MID_LINE_COLOR        :
/*N*/             rVal >>= nSet32;
/*N*/             aFtnInfo.SetLineColor(nSet32);
/*N*/         break;
/*N*/         case MID_FTN_HEIGHT:
/*N*/         case MID_LINE_TEXT_DIST    :
/*N*/         case MID_LINE_FOOTNOTE_DIST:
/*N*/                 rVal >>= nSet32;
/*N*/                 if(nSet32 < 0)
/*N*/                     bRet = sal_False;
/*N*/                 else
/*N*/                 {
/*N*/                     nSet32 = MM100_TO_TWIP(nSet32);
/*N*/                     switch(nMemberId & ~CONVERT_TWIPS)
/*N*/                     {
/*N*/                         case MID_FTN_HEIGHT:            aFtnInfo.SetHeight(nSet32);    break;
/*N*/                         case MID_LINE_TEXT_DIST:        aFtnInfo.SetTopDist(nSet32);break;
/*N*/                         case MID_LINE_FOOTNOTE_DIST:    aFtnInfo.SetBottomDist(nSet32);break;
/*N*/                     }
/*N*/                 }
/*N*/         break;
/*N*/         case MID_LINE_WEIGHT       :
/*N*/         {
/*N*/             sal_Int16 nSet; rVal >>= nSet;
/*N*/             if(nSet >= 0)
/*N*/                 aFtnInfo.SetLineWidth(MM100_TO_TWIP(nSet));
/*N*/             else
/*N*/                 bRet = sal_False;
/*N*/         }
/*N*/         break;
/*N*/         case MID_LINE_RELWIDTH     :
/*N*/         {
/*N*/             sal_Int8 nSet; rVal >>= nSet;
/*N*/             if(nSet < 0)
/*N*/                 bRet = sal_False;
/*N*/             else
/*N*/                 aFtnInfo.SetWidth(Fraction(nSet, 100));
/*N*/         }
/*N*/         break;
/*N*/         case MID_LINE_ADJUST       :
/*N*/         {
/*N*/             sal_Int16 nSet; rVal >>= nSet;
/*N*/             if(nSet >= 0 && nSet < 3) //com::sun::star::text::HorizontalAdjust
/*N*/                 aFtnInfo.SetAdj((SwFtnAdj)nSet);
/*N*/             else
/*N*/                 bRet = sal_False;
/*N*/         }
/*N*/         break;
/*N*/         default:
/*N*/             bRet = sal_False;
/*N*/     }
/*N*/     return bRet;
/*N*/ }

//STRIP001 SwPtrItem::SwPtrItem( const USHORT nId, void* pPtr ) :
//STRIP001  SfxPoolItem( nId ),
//STRIP001  pMisc(pPtr)
//STRIP001 {
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Copy-Konstruktor
 --------------------------------------------------------------------*/


//STRIP001 SwPtrItem::SwPtrItem( const SwPtrItem& rItem ) : SfxPoolItem( rItem )
//STRIP001 {
//STRIP001  pMisc = rItem.pMisc;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Clonen
 --------------------------------------------------------------------*/


//STRIP001 SfxPoolItem* SwPtrItem::Clone( SfxItemPool *pPool ) const
//STRIP001 {
//STRIP001  return new SwPtrItem( *this );
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung:
 --------------------------------------------------------------------*/


//STRIP001 int SwPtrItem::operator==( const SfxPoolItem& rAttr ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );
//STRIP001  const SwPtrItem& rItem = (SwPtrItem&)rAttr;
//STRIP001  return ( pMisc == rItem.pMisc );
//STRIP001 }


/*-----------------12.11.97 12:55-------------------------------
 SwUINumRuleItem fuer die NumTabPages der FormatNumRule/Stylisten
---------------------------------------------------------------*/
//STRIP001 SwUINumRuleItem::SwUINumRuleItem( const SwNumRule& rRul, const USHORT nId )
//STRIP001  : SfxPoolItem( nId ), pRule( new SwNumRule( rRul ) )
//STRIP001 {
//STRIP001 }

//STRIP001 SwUINumRuleItem::SwUINumRuleItem( const String& rName, const USHORT nId )
//STRIP001  : SfxPoolItem( nId ), pRule( new SwNumRule( rName ) )
//STRIP001 {
//STRIP001 }

//STRIP001 SwUINumRuleItem::SwUINumRuleItem( const SwUINumRuleItem& rItem )
//STRIP001  : SfxPoolItem( rItem ),
//STRIP001  pRule( new SwNumRule( *rItem.pRule ))
//STRIP001 {
//STRIP001 }

//STRIP001  SwUINumRuleItem::~SwUINumRuleItem()
//STRIP001 {
//STRIP001  delete pRule;
//STRIP001 }


//STRIP001 SfxPoolItem*  SwUINumRuleItem::Clone( SfxItemPool *pPool ) const
//STRIP001 {
//STRIP001  return new SwUINumRuleItem( *this );
//STRIP001 }

//STRIP001 int  SwUINumRuleItem::operator==( const SfxPoolItem& rAttr ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );
//STRIP001  return *pRule == *((SwUINumRuleItem&)rAttr).pRule;
//STRIP001 }

//STRIP001 BOOL SwUINumRuleItem::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
//STRIP001 {
//STRIP001  uno::Reference< container::XIndexReplace >xRules = new SwXNumberingRules(*pRule);
//STRIP001  rVal.setValue(&xRules, ::getCppuType((uno::Reference< container::XIndexReplace>*)0));
//STRIP001  return TRUE;
//STRIP001 }
//STRIP001 BOOL SwUINumRuleItem::PutValue( const uno::Any& rVal, BYTE nMemberId )
//STRIP001 {
//STRIP001     uno::Reference< container::XIndexReplace> xRulesRef;
//STRIP001     if(rVal >>= xRulesRef)
//STRIP001  {
//STRIP001         uno::Reference< lang::XUnoTunnel > xTunnel(xRulesRef, uno::UNO_QUERY);
//STRIP001      SwXNumberingRules* pSwXRules = xTunnel.is() ? (SwXNumberingRules*)
//STRIP001                  xTunnel->getSomething(SwXNumberingRules::getUnoTunnelId()) : 0;
//STRIP001      if(pSwXRules)
//STRIP001      {
//STRIP001          *pRule = *pSwXRules->GetNumRule();
//STRIP001      }
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }
/* -----------------17.06.98 17:43-------------------
 *
 * --------------------------------------------------*/
//STRIP001 SwBackgroundDestinationItem::SwBackgroundDestinationItem(USHORT  nWhich, USHORT nValue) :
//STRIP001  SfxUInt16Item(nWhich, nValue)
//STRIP001 {
//STRIP001 }
/* -----------------17.06.98 17:44-------------------
 *
 * --------------------------------------------------*/
//STRIP001 SfxPoolItem*     SwBackgroundDestinationItem::Clone( SfxItemPool *pPool ) const
//STRIP001 {
//STRIP001  return new SwBackgroundDestinationItem(Which(), GetValue());
//STRIP001 }



}
