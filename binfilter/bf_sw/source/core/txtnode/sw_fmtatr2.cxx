/*************************************************************************
 *
 *  $RCSfile: sw_fmtatr2.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2004-04-22 09:40:27 $
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

#include "hintids.hxx"
#include "unomid.h"

#ifndef __SBX_SBXVARIABLE_HXX //autogen
#include <svtools/sbxvar.hxx>
#endif
#ifndef _SFXMACITEM_HXX //autogen
#include <svtools/macitem.hxx>
#endif
#ifndef _SFXSTRITEM_HXX //autogen
#include <svtools/stritem.hxx>
#endif

#ifndef _FCHRFMT_HXX //autogen
#include <fchrfmt.hxx>
#endif
#ifndef _FMTINFMT_HXX //autogen
#include <fmtinfmt.hxx>
#endif
#ifndef _TXTATR_HXX //autogen
#include <txtatr.hxx>
#endif
#ifndef _FMTRUBY_HXX
#include <fmtruby.hxx>
#endif
#ifndef _CHARFMT_HXX
#include <charfmt.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>        // SwUpdateAttr
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _UNOSTYLE_HXX
#include <unostyle.hxx>
#endif
#ifndef _UNOEVENT_HXX
#include <unoevent.hxx>     // SwHyperlinkEventDescriptor
#endif
#ifndef _COM_SUN_STAR_TEXT_RUBYADJUST_HDL_
#include <com/sun/star/text/RubyAdjust.hdl>
#endif

#ifndef _CMDID_H
#include <cmdid.h>
#endif
#ifndef _COM_SUN_STAR_UNO_ANY_H_
#include <com/sun/star/uno/Any.h>
#endif
#ifndef _SWSTYLENAMEMAPPER_HXX
#include <SwStyleNameMapper.hxx>
#endif
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::rtl;

/*************************************************************************
|*
|*    class SwFmtCharFmt
|*    Beschreibung
|*    Ersterstellung    JP 23.11.90
|*    Letzte Aenderung  JP 09.08.94
|*
*************************************************************************/

/*N*/ TYPEINIT1_AUTOFACTORY(SwFmtINetFmt, SfxPoolItem);

/*N*/ SwFmtCharFmt::SwFmtCharFmt( SwCharFmt *pFmt )
/*N*/   : SfxPoolItem( RES_TXTATR_CHARFMT ),
/*N*/   SwClient(pFmt),
/*N*/   pTxtAttr( 0 )
/*N*/ {
/*N*/ }



/*N*/ SwFmtCharFmt::SwFmtCharFmt( const SwFmtCharFmt& rAttr )
/*N*/   : SfxPoolItem( RES_TXTATR_CHARFMT ),
/*N*/   SwClient( rAttr.GetCharFmt() ),
/*N*/   pTxtAttr( 0 )
/*N*/ {
/*N*/ }



/*N*/ SwFmtCharFmt::~SwFmtCharFmt() {}



/*N*/ int SwFmtCharFmt::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/   ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
/*N*/   return GetCharFmt() == ((SwFmtCharFmt&)rAttr).GetCharFmt();
/*N*/ }



/*N*/ SfxPoolItem* SwFmtCharFmt::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SwFmtCharFmt( *this );
/*N*/ }



//STRIP001 // weiterleiten an das TextAttribut
//STRIP001 void SwFmtCharFmt::Modify( SfxPoolItem* pOld, SfxPoolItem* pNew )
//STRIP001 {
//STRIP001  if( pTxtAttr )
//STRIP001      pTxtAttr->Modify( pOld, pNew );
//STRIP001 }



/*N*/ // weiterleiten an das TextAttribut
/*N*/ BOOL SwFmtCharFmt::GetInfo( SfxPoolItem& rInfo ) const
/*N*/ {
/*N*/   return pTxtAttr ? pTxtAttr->GetInfo( rInfo ) : FALSE;
/*N*/ }
/*N*/ BOOL SwFmtCharFmt::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/   String sCharFmtName;
/*N*/   if(GetCharFmt())
/*N*/       SwStyleNameMapper::FillProgName(GetCharFmt()->GetName(), sCharFmtName,  GET_POOLID_CHRFMT, sal_True );
/*N*/   rVal <<= OUString( sCharFmtName );
/*N*/   return TRUE;
/*N*/ }
//STRIP001 BOOL SwFmtCharFmt::PutValue( const uno::Any& rVal, BYTE nMemberId  )
//STRIP001 {
//STRIP001  DBG_ERROR("Zeichenvorlage kann mit PutValue nicht gesetzt werden!")
//STRIP001  return FALSE;
//STRIP001 }

/*************************************************************************
|*
|*    class SwFmtINetFmt
|*    Beschreibung
|*    Ersterstellung    AMA 02.08.96
|*    Letzte Aenderung  AMA 02.08.96
|*
*************************************************************************/

/*N*/ SwFmtINetFmt::SwFmtINetFmt()
/*N*/   : SfxPoolItem( RES_TXTATR_INETFMT ),
/*N*/   pTxtAttr( 0 ),
/*N*/   pMacroTbl( 0 ),
/*N*/   nINetId( 0 ),
/*N*/   nVisitedId( 0 )
/*N*/ {}

/*N*/ SwFmtINetFmt::SwFmtINetFmt( const XubString& rURL, const XubString& rTarget )
/*N*/   : SfxPoolItem( RES_TXTATR_INETFMT ),
/*N*/   aURL( rURL ),
/*N*/   aTargetFrame( rTarget ),
/*N*/   pTxtAttr( 0 ),
/*N*/   pMacroTbl( 0 ),
/*N*/   nINetId( 0 ),
/*N*/   nVisitedId( 0 )
/*N*/ {
/*N*/ }



/*N*/ SwFmtINetFmt::SwFmtINetFmt( const SwFmtINetFmt& rAttr )
/*N*/   : SfxPoolItem( RES_TXTATR_INETFMT ),
/*N*/   aURL( rAttr.GetValue() ),
/*N*/   aName( rAttr.aName ),
/*N*/   aTargetFrame( rAttr.aTargetFrame ),
/*N*/   aINetFmt( rAttr.aINetFmt ),
/*N*/   aVisitedFmt( rAttr.aVisitedFmt ),
/*N*/   pTxtAttr( 0 ),
/*N*/   pMacroTbl( 0 ),
/*N*/   nINetId( rAttr.nINetId ),
/*N*/   nVisitedId( rAttr.nVisitedId )
/*N*/ {
/*N*/   if( rAttr.GetMacroTbl() )
/*?*/       pMacroTbl = new SvxMacroTableDtor( *rAttr.GetMacroTbl() );
/*N*/ }



/*N*/ SwFmtINetFmt::~SwFmtINetFmt()
/*N*/ {
/*N*/   delete pMacroTbl;
/*N*/ }



/*N*/ int SwFmtINetFmt::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/   ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
/*N*/   BOOL bRet = SfxPoolItem::operator==( (SfxPoolItem&) rAttr )
/*N*/               && aURL == ((SwFmtINetFmt&)rAttr).aURL
/*N*/               && aName == ((SwFmtINetFmt&)rAttr).aName
/*N*/               && aTargetFrame == ((SwFmtINetFmt&)rAttr).aTargetFrame
/*N*/               && aINetFmt == ((SwFmtINetFmt&)rAttr).aINetFmt
/*N*/               && aVisitedFmt == ((SwFmtINetFmt&)rAttr).aVisitedFmt
/*N*/               && nINetId == ((SwFmtINetFmt&)rAttr).nINetId
/*N*/               && nVisitedId == ((SwFmtINetFmt&)rAttr).nVisitedId;
/*N*/
/*N*/   if( !bRet )
/*N*/       return FALSE;
/*N*/
/*N*/   const SvxMacroTableDtor* pOther = ((SwFmtINetFmt&)rAttr).pMacroTbl;
/*N*/   if( !pMacroTbl )
/*N*/       return ( !pOther || !pOther->Count() );
/*N*/   if( !pOther )
/*?*/       return 0 == pMacroTbl->Count();
/*?*/
/*?*/   const SvxMacroTableDtor& rOwn = *pMacroTbl;
/*?*/   const SvxMacroTableDtor& rOther = *pOther;
/*?*/
/*?*/   // Anzahl unterschiedlich => auf jeden Fall ungleich
/*?*/   if( rOwn.Count() != rOther.Count() )
/*?*/       return FALSE;
/*?*/
/*?*/   // einzeln vergleichen; wegen Performance ist die Reihenfolge wichtig
/*?*/   for( USHORT nNo = 0; nNo < rOwn.Count(); ++nNo )
/*?*/   {
/*?*/       const SvxMacro *pOwnMac = rOwn.GetObject(nNo);
/*?*/       const SvxMacro *pOtherMac = rOther.GetObject(nNo);
/*?*/       if (    rOwn.GetKey(pOwnMac) != rOther.GetKey(pOtherMac)  ||
/*?*/               pOwnMac->GetLibName() != pOtherMac->GetLibName() ||
/*?*/               pOwnMac->GetMacName() != pOtherMac->GetMacName() )
/*?*/           return FALSE;
/*?*/   }
/*?*/   return TRUE;
/*N*/ }



/*N*/ SfxPoolItem* SwFmtINetFmt::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SwFmtINetFmt( *this );
/*N*/ }



//STRIP001 void SwFmtINetFmt::SetMacroTbl( const SvxMacroTableDtor* pNewTbl )
//STRIP001 {
//STRIP001  if( pNewTbl )
//STRIP001  {
//STRIP001      if( pMacroTbl )
//STRIP001          *pMacroTbl = *pNewTbl;
//STRIP001      else
//STRIP001          pMacroTbl = new SvxMacroTableDtor( *pNewTbl );
//STRIP001  }
//STRIP001  else if( pMacroTbl )
//STRIP001      delete pMacroTbl, pMacroTbl = 0;
//STRIP001 }



/*N #i27164#*/ void SwFmtINetFmt::SetMacro( USHORT nEvent, const SvxMacro& rMacro )
/*N #i27164#*/ {
/*N #i27164#*/  if( !pMacroTbl )
/*N #i27164#*/  pMacroTbl = new SvxMacroTableDtor;
/*N #i27164#*/
/*N #i27164#*/  SvxMacro *pOldMacro;
/*N #i27164#*/  if( 0 != ( pOldMacro = pMacroTbl->Get( nEvent )) )
/*N #i27164#*/  {
/*N #i27164#*/  delete pOldMacro;
/*N #i27164#*/  pMacroTbl->Replace( nEvent, new SvxMacro( rMacro ) );
/*N #i27164#*/  }
/*N #i27164#*/  else
/*N #i27164#*/  pMacroTbl->Insert( nEvent, new SvxMacro( rMacro ) );
/*N #i27164#*/ }



/*N*/ const SvxMacro* SwFmtINetFmt::GetMacro( USHORT nEvent ) const
/*N*/ {
/*N*/   const SvxMacro* pRet = 0;
/*N*/   if( pMacroTbl && pMacroTbl->IsKeyValid( nEvent ) )
/*?*/       pRet = pMacroTbl->Get( nEvent );
/*N*/   return pRet;
/*N*/ }



/*N*/ BOOL SwFmtINetFmt::QueryValue( uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/   BOOL bRet = TRUE;
/*N*/   XubString sVal;
/*N*/     nMemberId &= ~CONVERT_TWIPS;
/*N*/   switch(nMemberId)
/*N*/   {
/*N*/       case MID_URL_URL:
/*N*/           sVal = aURL;
/*N*/       break;
/*N*/       case MID_URL_TARGET:
/*N*/           sVal = aTargetFrame;
/*N*/       break;
/*N*/       case MID_URL_HYPERLINKNAME:
/*N*/           sVal = aName;
/*N*/       break;
/*N*/       case MID_URL_VISITED_FMT:
/*N*/           sVal = aVisitedFmt;
/*N*/           if( !sVal.Len() && nVisitedId != 0 )
/*?*/               SwStyleNameMapper::FillUIName( nVisitedId, sVal );
/*N*/           if( sVal.Len() )
/*?*/               SwStyleNameMapper::FillProgName( sVal, sVal, GET_POOLID_CHRFMT, sal_True );
/*N*/       break;
/*N*/       case MID_URL_UNVISITED_FMT:
/*N*/           sVal = aINetFmt;
/*N*/           if( !sVal.Len() && nINetId != 0 )
/*?*/               SwStyleNameMapper::FillUIName( nINetId, sVal );
/*N*/           if( sVal.Len() )
/*?*/               SwStyleNameMapper::FillProgName( sVal, sVal, GET_POOLID_CHRFMT, sal_True );
/*N*/       break;
/*N*/       case MID_URL_HYPERLINKEVENTS:
/*N*/       {
/*N*/           // create (and return) event descriptor
/*N*/           SwHyperlinkEventDescriptor* pEvents =
/*N*/               new SwHyperlinkEventDescriptor();
/*N*/           pEvents->copyMacrosFromINetFmt(*this);
/*N*/           uno::Reference<container::XNameReplace> xNameReplace(pEvents);
/*N*/
/*N*/           // all others return a string; so we just set rVal here and exit
/*N*/           rVal <<= xNameReplace;
/*N*/           return bRet;
/*N*/       }
/*N*/       break;
/*N*/       default:
/*N*/           bRet = FALSE;
/*N*/   }
/*N*/   rVal <<= OUString(sVal);
/*N*/   return bRet;
/*N*/ }
/*N*/ BOOL SwFmtINetFmt::PutValue( const uno::Any& rVal, BYTE nMemberId  )
/*N*/ {
/*N*/   BOOL bRet = TRUE;
/*N*/     nMemberId &= ~CONVERT_TWIPS;
/*N*/
/*N*/   // all properties except HyperlinkEvents are of type string, hence
/*N*/   // we treat HyperlinkEvents specially
/*N*/   if (MID_URL_HYPERLINKEVENTS == nMemberId)
/*N*/   {
/*?*/       uno::Reference<container::XNameReplace> xReplace;
/*?*/       rVal >>= xReplace;
/*?*/       if (xReplace.is())
/*?*/       {
/*?*/           // Create hyperlink event descriptor. Then copy events
/*?*/           // from argument into descriptor. Then copy events from
/*?*/           // the descriptor into the format.
/*?*/           SwHyperlinkEventDescriptor* pEvents = new SwHyperlinkEventDescriptor();
/*?*/           uno::Reference< ::com::sun::star::lang::XServiceInfo> xHold = pEvents;
/*?*/           pEvents->copyMacrosFromNameReplace(xReplace);
/*?*/           pEvents->copyMacrosIntoINetFmt(*this);
/*?*/       }
/*?*/       else
/*?*/       {
/*?*/           // wrong type!
/*?*/           bRet = FALSE;
/*?*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       // all string properties:
/*N*/       if(rVal.getValueType() != ::getCppuType((::rtl::OUString*)0))
/*N*/           return FALSE;
/*N*/       XubString sVal = *(::rtl::OUString*)rVal.getValue();
/*N*/       switch(nMemberId)
/*N*/       {
/*N*/           case MID_URL_URL:
/*N*/               aURL = sVal;
/*N*/               break;
/*N*/           case MID_URL_TARGET:
/*N*/               aTargetFrame = sVal;
/*N*/               break;
/*N*/           case MID_URL_HYPERLINKNAME:
/*N*/               aName = sVal;
/*N*/               break;
/*?*/           case MID_URL_VISITED_FMT:
/*?*/           {
/*?*/               String aString;
/*?*/               SwStyleNameMapper::FillUIName( sVal, aString, GET_POOLID_CHRFMT, sal_True );
/*?*/               aVisitedFmt = OUString ( aString );
/*?*/               nVisitedId = SwStyleNameMapper::GetPoolIdFromUIName( aVisitedFmt,
/*?*/                                              GET_POOLID_CHRFMT );
/*?*/           }
/*?*/           break;
/*?*/           case MID_URL_UNVISITED_FMT:
/*?*/           {
/*?*/               String aString;
/*?*/               SwStyleNameMapper::FillUIName( sVal, aString, GET_POOLID_CHRFMT, sal_True );
/*?*/               aINetFmt = OUString ( aString );
/*?*/               nINetId = SwStyleNameMapper::GetPoolIdFromUIName( aINetFmt, GET_POOLID_CHRFMT );
/*?*/           }
/*?*/           break;
/*?*/           default:
/*?*/               bRet = FALSE;
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }


/*************************************************************************
|*    class SwFmtRuby
*************************************************************************/

/*N*/ SwFmtRuby::SwFmtRuby( const String& rRubyTxt )
/*N*/   : SfxPoolItem( RES_TXTATR_CJK_RUBY ),
/*N*/   sRubyTxt( rRubyTxt ),
/*N*/   nCharFmtId( 0 ),
/*N*/   nPosition( 0 ), nAdjustment( 0 ),
/*N*/   pTxtAttr( 0 )
/*N*/ {
/*N*/ }

/*?*/ SwFmtRuby::SwFmtRuby( const SwFmtRuby& rAttr )
/*?*/   : SfxPoolItem( RES_TXTATR_CJK_RUBY ),
/*?*/   sRubyTxt( rAttr.sRubyTxt ),
/*?*/   sCharFmtName( rAttr.sCharFmtName ),
/*?*/   nCharFmtId( rAttr.nCharFmtId),
/*?*/   nPosition( rAttr.nPosition ), nAdjustment( rAttr.nAdjustment ),
/*?*/   pTxtAttr( 0 )
/*?*/ {
/*?*/ }

/*N*/ SwFmtRuby::~SwFmtRuby()
/*N*/ {
/*N*/ }

/*N*/  SwFmtRuby& SwFmtRuby::operator=( const SwFmtRuby& rAttr )
/*N*/  {
/*N*/   sRubyTxt = rAttr.sRubyTxt;
/*N*/   sCharFmtName = rAttr.sCharFmtName;
/*N*/   nCharFmtId = rAttr.nCharFmtId;
/*N*/   nPosition = rAttr.nPosition;
/*N*/   nAdjustment = rAttr.nAdjustment;
/*N*/   pTxtAttr =  0;
/*N*/   return *this;
/*N*/  }

//STRIP001 int SwFmtRuby::operator==( const SfxPoolItem& rAttr ) const
//STRIP001 {
//STRIP001  ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
//STRIP001  return sRubyTxt == ((SwFmtRuby&)rAttr).sRubyTxt &&
//STRIP001         sCharFmtName == ((SwFmtRuby&)rAttr).sCharFmtName &&
//STRIP001         nCharFmtId == ((SwFmtRuby&)rAttr).nCharFmtId &&
//STRIP001         nPosition == ((SwFmtRuby&)rAttr).nPosition &&
//STRIP001         nAdjustment == ((SwFmtRuby&)rAttr).nAdjustment;
//STRIP001 }

//STRIP001 SfxPoolItem* SwFmtRuby::Clone( SfxItemPool* ) const
//STRIP001 {
//STRIP001  return new SwFmtRuby( *this );
//STRIP001 }

//STRIP001 BOOL SwFmtRuby::QueryValue( ::com::sun::star::uno::Any& rVal,
//STRIP001                              BYTE nMemberId ) const
//STRIP001 {
//STRIP001  BOOL bRet = TRUE;
//STRIP001     nMemberId &= ~CONVERT_TWIPS;
//STRIP001  switch( nMemberId )
//STRIP001  {
//STRIP001      case MID_RUBY_TEXT: rVal <<= (OUString)sRubyTxt;                    break;
//STRIP001          case MID_RUBY_ADJUST:   rVal <<= (sal_Int16)nAdjustment;    break;
//STRIP001      case MID_RUBY_CHARSTYLE:
//STRIP001      {
//STRIP001          String aString;
//STRIP001          SwStyleNameMapper::FillProgName(sCharFmtName, aString, GET_POOLID_CHRFMT, sal_True );
//STRIP001          rVal <<= OUString ( aString );
//STRIP001      }
//STRIP001      break;
//STRIP001         case MID_RUBY_ABOVE:
//STRIP001         {
//STRIP001             sal_Bool bAbove = !nPosition;
//STRIP001             rVal.setValue(&bAbove, ::getBooleanCppuType());
//STRIP001         }
//STRIP001         break;
//STRIP001         default:
//STRIP001          bRet = FALSE;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }
/*N*/ BOOL SwFmtRuby::PutValue( const ::com::sun::star::uno::Any& rVal,
/*N*/                           BYTE nMemberId  )
/*N*/ {
/*N*/   BOOL bRet = TRUE;
/*N*/     nMemberId &= ~CONVERT_TWIPS;
/*N*/   switch( nMemberId )
/*N*/   {
/*N*/       case MID_RUBY_TEXT:
/*N*/       {
/*N*/           OUString sTmp;
/*N*/           bRet = rVal >>= sTmp;
/*N*/           sRubyTxt = sTmp;
/*N*/       }
/*N*/       break;
/*N*/       case MID_RUBY_ADJUST:
/*N*/       {
/*N*/           sal_Int16 nSet; rVal >>= nSet;
/*N*/           if(nSet >= 0 && nSet <= ::com::sun::star::text::RubyAdjust_INDENT_BLOCK)
/*N*/               nAdjustment = nSet;
/*N*/           else
/*N*/               bRet = sal_False;
/*N*/       }
/*N*/       break;
/*N*/         case MID_RUBY_ABOVE:
/*N*/         {
/*N*/             const uno::Type& rType = ::getBooleanCppuType();
/*N*/             if(rVal.hasValue() && rVal.getValueType() == rType)
/*N*/             {
/*N*/                 sal_Bool bAbove = *(sal_Bool*)rVal.getValue();
/*N*/                 nPosition = bAbove ? 0 : 1;
/*N*/             }
/*N*/         }
/*N*/         break;
/*N*/         case MID_RUBY_CHARSTYLE:
/*N*/         {
/*N*/             OUString sTmp;
/*N*/             bRet = rVal >>= sTmp;
/*N*/             if(bRet)
/*N*/                 sCharFmtName = SwStyleNameMapper::GetUIName(sTmp, GET_POOLID_CHRFMT );
/*N*/         }
/*N*/         break;
/*N*/       default:
/*N*/           bRet = FALSE;
/*N*/   }
/*N*/   return bRet;
/*N*/ }

}
