/*************************************************************************
 *
 *  $RCSfile: sw_paratr.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:50:47 $
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
#include <swtypes.hxx>
#include "unomid.h"
#ifndef _COM_SUN_STAR_STYLE_LINESPACINGMODE_HPP_
#include <com/sun/star/style/LineSpacingMode.hpp>
#endif
#ifndef _COM_SUN_STAR_STYLE_PARAGRAPHADJUST_HPP_
#include <com/sun/star/style/ParagraphAdjust.hpp>
#endif
#ifndef _COM_SUN_STAR_STYLE_DROPCAPFORMAT_HPP_
#include <com/sun/star/style/DropCapFormat.hpp>
#endif
#ifndef _COM_SUN_STAR_STYLE_LINESPACING_HPP_
#include <com/sun/star/style/LineSpacing.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_RELORIENTATION_HPP_
#include <com/sun/star/text/RelOrientation.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_VERTORIENTATION_HPP_
#include <com/sun/star/text/VertOrientation.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_HORIZONTALADJUST_HPP_
#include <com/sun/star/text/HorizontalAdjust.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_DOCUMENTSTATISTIC_HPP_
#include <com/sun/star/text/DocumentStatistic.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_HORIORIENTATION_HPP_
#include <com/sun/star/text/HoriOrientation.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_HORIORIENTATIONFORMAT_HPP_
#include <com/sun/star/text/HoriOrientationFormat.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_NOTEPRINTMODE_HPP_
#include <com/sun/star/text/NotePrintMode.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_SIZETYPE_HPP_
#include <com/sun/star/text/SizeType.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_VERTORIENTATIONFORMAT_HPP_
#include <com/sun/star/text/VertOrientationFormat.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_WRAPTEXTMODE_HPP_
#include <com/sun/star/text/WrapTextMode.hpp>
#endif
#ifndef _UNOSTYLE_HXX
#include <unostyle.hxx>
#endif
#ifndef _SWSTYLENAMEMAPPER_HXX
#include <SwStyleNameMapper.hxx>
#endif
#include "errhdl.hxx"
#include "paratr.hxx"
#include "charfmt.hxx"
#include "cmdid.h"
namespace binfilter {

using namespace ::com::sun::star;

/*N*/ TYPEINIT2_AUTOFACTORY( SwFmtDrop, SfxPoolItem, SwClient);
/*N*/ TYPEINIT1_AUTOFACTORY( SwRegisterItem, SfxBoolItem);
/*N*/ TYPEINIT1_AUTOFACTORY( SwNumRuleItem, SfxStringItem);
/*N*/ TYPEINIT1_AUTOFACTORY( SwParaConnectBorderItem, SfxBoolItem);

/*************************************************************************
|*    Beschreibung      Methoden von SwFmtDrop
|*    Ersterstellung    MS  19.02.91
|*    Letzte Aenderung  JP 08.08.94
*************************************************************************/



/*N*/ SwFmtDrop::SwFmtDrop()
/*N*/   : SfxPoolItem( RES_PARATR_DROP ),
/*N*/   SwClient( 0 ),
/*N*/   nLines( 0 ),
/*N*/   nChars( 0 ),
/*N*/   nDistance( 0 ),
/*N*/   pDefinedIn( 0 ),
/*N*/   bWholeWord( sal_False ),
/*N*/   nReadFmt( USHRT_MAX )
/*N*/ {
/*N*/ }



/*N*/ SwFmtDrop::SwFmtDrop( const SwFmtDrop &rCpy )
/*N*/   : SfxPoolItem( RES_PARATR_DROP ),
/*N*/   SwClient( rCpy.pRegisteredIn ),
/*N*/   nLines( rCpy.GetLines() ),
/*N*/   nChars( rCpy.GetChars() ),
/*N*/   nDistance( rCpy.GetDistance() ),
/*N*/   bWholeWord( rCpy.GetWholeWord() ),
/*N*/   pDefinedIn( 0 ),
/*N*/   nReadFmt( rCpy.nReadFmt )
/*N*/ {
/*N*/ }



/*N*/ SwFmtDrop::~SwFmtDrop()
/*N*/ {
/*N*/ }



/*N*/ void SwFmtDrop::SetCharFmt( SwCharFmt *pNew )
/*N*/ {
/*N*/   //Ummelden
/*N*/   if ( pRegisteredIn )
/*?*/       pRegisteredIn->Remove( this );
/*N*/     if(pNew)
/*N*/         pNew->Add( this );
/*N*/   nReadFmt = USHRT_MAX;
/*N*/ }



/*N*/ void SwFmtDrop::Modify( SfxPoolItem *pA, SfxPoolItem *pB )
/*N*/ {
/*N*/   if( pDefinedIn )
/*N*/   {
/*N*/       if( !pDefinedIn->ISA( SwFmt ))
/*N*/           pDefinedIn->Modify( this, this );
/*N*/       else if( pDefinedIn->GetDepends() &&
/*N*/               !pDefinedIn->IsModifyLocked() )
/*N*/       {
/*?*/           // selbst den Abhaengigen vom Format bescheid sagen. Das
/*?*/           // Format selbst wuerde es nicht weitergeben, weil es ueber
/*?*/           // die Abpruefung nicht hinauskommt.
/*?*/           SwClientIter aIter( *pDefinedIn );
/*?*/           SwClient * pLast = aIter.GoStart();
/*?*/           if( pLast )     // konnte zum Anfang gesprungen werden ??
/*?*/               do {
/*?*/                   pLast->Modify( this, this );
/*?*/                   if( !pDefinedIn->GetDepends() ) // Baum schon Weg ??
/*?*/                       break;
/*?*/               } while( 0 != ( pLast = aIter++ ));
/*?*/       }
/*N*/   }
/*N*/ }



/*N*/ sal_Bool SwFmtDrop::GetInfo( SfxPoolItem& rInfo ) const
/*N*/ {
/*N*/   // fuers UNDO: pruefe ob das Attribut wirklich in diesem Format steht
/*N*/ #ifdef USED_30
/*N*/   if( pDefinedIn )
/*N*/   {
/*N*/       if( IS_TYPE( SwTxtNode, pDefinedIn )
/*N*/           && ((SwTxtNode*)pDefinedIn)->....... )
/*N*/           ;
/*N*/       else if( IS_TYPE( SwTxtFmtColl, pDefinedIn )
/*N*/           && ((SwTxtFmtColl*)pDefinedIn)->....... )
/*N*/           ;
/*N*/ //     this == pFmt->GetAttr( RES_PARATR_DROP, sal_False ))
/*N*/ //        return pFmt->GetInfo( rInfo );
/*N*/
/*N*/   }
/*N*/ #endif
/*N*/   return sal_True;    // weiter
/*N*/ }



/*N*/ int SwFmtDrop::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/   ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
/*N*/   return ( nLines == ((SwFmtDrop&)rAttr).GetLines() &&
/*N*/            nChars == ((SwFmtDrop&)rAttr).GetChars() &&
/*N*/            nDistance ==  ((SwFmtDrop&)rAttr).GetDistance() &&
/*N*/            bWholeWord == ((SwFmtDrop&)rAttr).GetWholeWord() &&
/*N*/            GetCharFmt() == ((SwFmtDrop&)rAttr).GetCharFmt() &&
/*N*/            pDefinedIn == ((SwFmtDrop&)rAttr).pDefinedIn );
/*N*/ }



/*N*/ SfxPoolItem* SwFmtDrop::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SwFmtDrop( *this );
/*N*/ }




/*N*/ sal_Bool SwFmtDrop::QueryValue( uno::Any& rVal, sal_uInt8 nMemberId ) const
/*N*/ {
/*N*/   switch(nMemberId&~CONVERT_TWIPS)
/*N*/   {
/*N*/         case MID_DROPCAP_LINES : rVal <<= (sal_Int16)nLines; break;
/*N*/         case MID_DROPCAP_COUNT : rVal <<= (sal_Int16)nChars; break;
/*N*/         case MID_DROPCAP_DISTANCE : rVal <<= (sal_Int16) TWIP_TO_MM100(nDistance); break;
/*N*/       case MID_DROPCAP_FORMAT:
/*N*/       {
/*N*/           style::DropCapFormat aDrop;
/*N*/           aDrop.Lines = nLines   ;
/*N*/           aDrop.Count = nChars   ;
/*N*/           aDrop.Distance  = TWIP_TO_MM100(nDistance);
/*N*/           rVal.setValue(&aDrop, ::getCppuType((const style::DropCapFormat*)0));
/*N*/       }
/*N*/       break;
/*N*/       case MID_DROPCAP_WHOLE_WORD:
/*N*/           rVal.setValue(&bWholeWord, ::getBooleanCppuType());
/*N*/       break;
/*N*/       case MID_DROPCAP_CHAR_STYLE_NAME :
/*N*/       {
/*N*/           ::rtl::OUString sName;
/*N*/           if(GetCharFmt())
/*N*/               sName = SwStyleNameMapper::GetProgName(
/*N*/                       GetCharFmt()->GetName(), GET_POOLID_CHRFMT );
/*N*/           rVal <<= sName;
/*N*/       }
/*N*/       break;
/*N*/   }
/*N*/   return sal_True;
/*N*/ }

/*N*/ sal_Bool SwFmtDrop::PutValue( const uno::Any& rVal, sal_uInt8 nMemberId )
/*N*/ {
/*N*/   switch(nMemberId&~CONVERT_TWIPS)
/*N*/   {
/*N*/         case MID_DROPCAP_LINES :
/*N*/         {
/*N*/             sal_Int8 nTemp;
/*N*/             rVal >>= nTemp;
/*N*/             if(nTemp >=1 && nTemp < 0x7f)
/*N*/                 nLines = (BYTE)nTemp;
/*N*/         }
/*N*/         break;
/*N*/         case MID_DROPCAP_COUNT :
/*N*/         {
/*N*/             sal_Int16 nTemp;
/*N*/             rVal >>= nTemp;
/*N*/             if(nTemp >=1 && nTemp < 0x7f)
/*N*/                 nChars = (BYTE)nTemp;
/*N*/         }
/*N*/         break;
/*N*/         case MID_DROPCAP_DISTANCE :
/*N*/         {
/*N*/             sal_Int16 nVal;
/*N*/             if ( rVal >>= nVal )
/*N*/                 nDistance = (sal_Int16) MM100_TO_TWIP((sal_Int32)nVal);
/*N*/             else
/*N*/                 return sal_False;
/*N*/             break;
/*N*/         }
/*N*/       case MID_DROPCAP_FORMAT:
/*N*/       {
/*N*/           if(rVal.getValueType()  == ::getCppuType((const style::DropCapFormat*)0))
/*N*/           {
/*N*/               const style::DropCapFormat* pDrop = (const style::DropCapFormat*)rVal.getValue();
/*N*/               nLines      = pDrop->Lines;
/*N*/               nChars      = pDrop->Count;
/*N*/               nDistance   = MM100_TO_TWIP(pDrop->Distance);
/*N*/           }
/*N*/           else
/*N*/               //exception( wrong_type)
/*N*/               ;
/*N*/       }
/*N*/       break;
/*N*/       case MID_DROPCAP_WHOLE_WORD:
/*N*/           bWholeWord = *(sal_Bool*)rVal.getValue();
/*N*/       break;
/*N*/       case MID_DROPCAP_CHAR_STYLE_NAME :
/*N*/           DBG_ERROR("char format cannot be set in PutValue()!")
/*N*/       break;
/*N*/   }
/*N*/   return sal_True;
/*N*/ }

// class SwRegisterItem -------------------------------------------------


/*N*/ SfxPoolItem* SwRegisterItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/   return new SwRegisterItem( *this );
/*N*/ }

// class SwNumRuleItem -------------------------------------------------
/*N*/ SfxPoolItem* SwNumRuleItem::Clone( SfxItemPool *pPool  ) const
/*N*/ {
/*N*/   return new SwNumRuleItem( *this );
/*N*/ }
//STRIP001 int SwNumRuleItem::operator==( const SfxPoolItem& rAttr ) const
//STRIP001 {
//STRIP001  ASSERT( SfxPoolItem::operator==( rAttr ), "keine gleichen Attribute" );
//STRIP001  return GetValue() == ((SwNumRuleItem&)rAttr).GetValue() &&
//STRIP001          GetDefinedIn() == ((SwNumRuleItem&)rAttr).GetDefinedIn();
//STRIP001 }
/* -----------------------------27.06.00 11:05--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ BOOL    SwNumRuleItem::QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId ) const
/*N*/ {
/*N*/   ::rtl::OUString sRet = SwStyleNameMapper::GetProgName(GetValue(), GET_POOLID_NUMRULE );
/*N*/   rVal <<= sRet;
/*N*/   return TRUE;
/*N*/ }
/* -----------------------------27.06.00 11:05--------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ BOOL  SwNumRuleItem::PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId )
/*N*/ {
/*N*/   ::rtl::OUString uName;
/*N*/   rVal >>= uName;
/*N*/   SetValue(SwStyleNameMapper::GetUIName(uName, GET_POOLID_NUMRULE));
/*N*/   return TRUE;
/*N*/ }
/* -----------------19.05.2003 10:44-----------------

 --------------------------------------------------*/
 SfxPoolItem* SwParaConnectBorderItem::Clone( SfxItemPool * ) const
{
    return new SwParaConnectBorderItem( *this );
}



}
