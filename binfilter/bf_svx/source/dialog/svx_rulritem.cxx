/*************************************************************************
 *
 *  $RCSfile: svx_rulritem.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:42:34 $
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

#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif
#pragma hdrstop

#include "dialogs.hrc"
#include "rulritem.hxx"
namespace binfilter {

//------------------------------------------------------------------------

/*N*/ TYPEINIT1(SvxPagePosSizeItem, SfxPoolItem);
/*N*/ TYPEINIT1(SvxLongLRSpaceItem, SfxPoolItem);
/*N*/ TYPEINIT1(SvxLongULSpaceItem, SfxPoolItem);
/*N*/ TYPEINIT1(SvxColumnItem, SfxPoolItem);
/*N*/ TYPEINIT1(SvxObjectItem, SfxPoolItem);

//------------------------------------------------------------------------

/*N*/ int SvxLongLRSpaceItem::operator==( const SfxPoolItem& rCmp) const
/*N*/ {
/*N*/   return SfxPoolItem::operator==(rCmp) &&
/*N*/       lLeft==((const SvxLongLRSpaceItem &)rCmp).lLeft &&
/*N*/       lRight==((const SvxLongLRSpaceItem &)rCmp).lRight;
/*N*/ }


//------------------------------------------------------------------------

//STRIP001 String SvxLongLRSpaceItem::GetValueText() const
//STRIP001 {
//STRIP001  return String();
//STRIP001 }

/*N*/ #define TWIP_TO_MM100(TWIP)   ((TWIP) >= 0 ? (((TWIP)*127L+36L)/72L) : (((TWIP)*127L-36L)/72L))
/*N*/ #define MM100_TO_TWIP(MM100)  ((MM100) >= 0 ? (((MM100)*72L+63L)/127L) : (((MM100)*72L-63L)/127L))

//STRIP001 sal_Bool SvxLongLRSpaceItem::QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId ) const
//STRIP001 {
//STRIP001  sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
//STRIP001  nMemberId &= ~CONVERT_TWIPS;
//STRIP001
//STRIP001     sal_Int32 nVal;
//STRIP001     switch( nMemberId )
//STRIP001  {
//STRIP001         case MID_LEFT: nVal = lLeft; break;
//STRIP001         case MID_RIGHT: nVal = lRight; break;
//STRIP001         default: DBG_ERROR("Wrong MemberId!"); return sal_False;
//STRIP001  }
//STRIP001
//STRIP001     if ( bConvert )
//STRIP001         nVal = TWIP_TO_MM100( nVal );
//STRIP001
//STRIP001     rVal <<= nVal;
//STRIP001     return TRUE;
//STRIP001 }

// -----------------------------------------------------------------------
//STRIP001 sal_Bool SvxLongLRSpaceItem::PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId )
//STRIP001 {
//STRIP001  sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
//STRIP001  nMemberId &= ~CONVERT_TWIPS;
//STRIP001
//STRIP001     sal_Int32 nVal;
//STRIP001     if ( rVal >>= nVal )
//STRIP001     {
//STRIP001         if ( bConvert )
//STRIP001             nVal = MM100_TO_TWIP( nVal );
//STRIP001
//STRIP001         switch( nMemberId )
//STRIP001         {
//STRIP001             case MID_LEFT: lLeft = nVal; break;
//STRIP001             case MID_RIGHT: lRight = nVal; break;
//STRIP001             default: DBG_ERROR("Wrong MemberId!"); return sal_False;
//STRIP001         }
//STRIP001
//STRIP001         return sal_True;
//STRIP001     }
//STRIP001
//STRIP001     return sal_False;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxLongLRSpaceItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     String&             rText, const IntlWrapper *
//STRIP001 )    const
//STRIP001 {
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxLongLRSpaceItem::Clone(SfxItemPool *pPool) const
/*N*/ {
/*N*/   return new SvxLongLRSpaceItem(*this);
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SvxLongLRSpaceItem::SvxLongLRSpaceItem(long lL, long lR, USHORT nId)
/*N*/   : SfxPoolItem(nId),
/*N*/   lLeft(lL),
/*N*/   lRight(lR)
/*N*/ {}

//------------------------------------------------------------------------

/*N*/ SvxLongLRSpaceItem::SvxLongLRSpaceItem(const SvxLongLRSpaceItem &rCpy)
/*N*/   : SfxPoolItem(rCpy),
/*N*/   lLeft(rCpy.lLeft),
/*N*/   lRight(rCpy.lRight)
/*N*/       {}

//------------------------------------------------------------------------

/*N*/ int SvxLongULSpaceItem::operator==( const SfxPoolItem& rCmp) const
/*N*/ {
/*N*/   return SfxPoolItem::operator==(rCmp) &&
/*N*/       lLeft==((const SvxLongULSpaceItem &)rCmp).lLeft &&
/*N*/       lRight==((const SvxLongULSpaceItem &)rCmp).lRight;
/*N*/ }


//------------------------------------------------------------------------

//STRIP001 String SvxLongULSpaceItem::GetValueText() const
//STRIP001 {
//STRIP001  return String();
//STRIP001 }

//STRIP001 sal_Bool SvxLongULSpaceItem::QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId ) const
//STRIP001 {
//STRIP001  sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
//STRIP001  nMemberId &= ~CONVERT_TWIPS;
//STRIP001
//STRIP001     sal_Int32 nVal;
//STRIP001     switch( nMemberId )
//STRIP001  {
//STRIP001         case MID_UPPER: nVal = lLeft; break;
//STRIP001         case MID_LOWER: nVal = lRight; break;
//STRIP001         default: DBG_ERROR("Wrong MemberId!"); return sal_False;
//STRIP001  }
//STRIP001
//STRIP001     if ( bConvert )
//STRIP001         nVal = TWIP_TO_MM100( nVal );
//STRIP001
//STRIP001     rVal <<= nVal;
//STRIP001     return TRUE;
//STRIP001 }

// -----------------------------------------------------------------------
//STRIP001 sal_Bool SvxLongULSpaceItem::PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId )
//STRIP001 {
//STRIP001  sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
//STRIP001  nMemberId &= ~CONVERT_TWIPS;
//STRIP001
//STRIP001     sal_Int32 nVal;
//STRIP001     if ( rVal >>= nVal )
//STRIP001     {
//STRIP001         if ( bConvert )
//STRIP001             nVal = MM100_TO_TWIP( nVal );
//STRIP001
//STRIP001         switch( nMemberId )
//STRIP001         {
//STRIP001             case MID_UPPER: lLeft = nVal; break;
//STRIP001             case MID_LOWER: lRight = nVal; break;
//STRIP001             default: DBG_ERROR("Wrong MemberId!"); return sal_False;
//STRIP001         }
//STRIP001
//STRIP001         return sal_True;
//STRIP001     }
//STRIP001
//STRIP001     return sal_False;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxLongULSpaceItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     String&             rText, const IntlWrapper *
//STRIP001 )    const
//STRIP001 {
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxLongULSpaceItem::Clone(SfxItemPool *pPool) const
/*N*/ {
/*N*/   return new SvxLongULSpaceItem(*this);
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SvxLongULSpaceItem::SvxLongULSpaceItem(long lL, long lR, USHORT nId)
/*N*/   : SfxPoolItem(nId),
/*N*/   lLeft(lL),
/*N*/   lRight(lR)
/*N*/ {}

//------------------------------------------------------------------------

/*N*/ SvxLongULSpaceItem::SvxLongULSpaceItem(const SvxLongULSpaceItem &rCpy)
/*N*/   : SfxPoolItem(rCpy),
/*N*/   lLeft(rCpy.lLeft),
/*N*/   lRight(rCpy.lRight)
/*N*/       {}

//------------------------------------------------------------------------

/*N*/ int SvxPagePosSizeItem::operator==( const SfxPoolItem& rCmp) const
/*N*/ {
/*N*/   return SfxPoolItem::operator==(rCmp) &&
/*N*/       aPos == ((const SvxPagePosSizeItem &)rCmp).aPos &&
/*N*/           lWidth == ((const SvxPagePosSizeItem &)rCmp).lWidth  &&
/*N*/           lHeight == ((const SvxPagePosSizeItem &)rCmp).lHeight;
/*N*/ }

//STRIP001 sal_Bool SvxPagePosSizeItem::QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId ) const
//STRIP001 {
//STRIP001  sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
//STRIP001  nMemberId &= ~CONVERT_TWIPS;
//STRIP001
//STRIP001     sal_Int32 nVal;
//STRIP001     switch ( nMemberId )
//STRIP001     {
//STRIP001         case MID_X: nVal = aPos.X(); break;
//STRIP001         case MID_Y: nVal = aPos.Y(); break;
//STRIP001         case MID_WIDTH: nVal = lWidth; break;
//STRIP001         case MID_HEIGHT: nVal = lHeight; break;
//STRIP001         default: DBG_ERROR("Wrong MemberId!"); return sal_False;
//STRIP001     }
//STRIP001
//STRIP001     rVal <<= nVal;
//STRIP001     return TRUE;
//STRIP001 }

//STRIP001 sal_Bool SvxPagePosSizeItem::PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId )
//STRIP001 {
//STRIP001  sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
//STRIP001  nMemberId &= ~CONVERT_TWIPS;
//STRIP001
//STRIP001     sal_Int32 nVal;
//STRIP001     if ( rVal >>= nVal )
//STRIP001     {
//STRIP001         switch ( nMemberId )
//STRIP001         {
//STRIP001             case MID_X: aPos.X() = nVal; break;
//STRIP001             case MID_Y: aPos.Y() = nVal; break;
//STRIP001             case MID_WIDTH: lWidth = nVal; break;
//STRIP001             case MID_HEIGHT: lHeight = nVal; break;
//STRIP001             default: DBG_ERROR("Wrong MemberId!"); return sal_False;
//STRIP001         }
//STRIP001
//STRIP001         return sal_True;
//STRIP001     }
//STRIP001
//STRIP001     return sal_False;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 String SvxPagePosSizeItem::GetValueText() const
//STRIP001 {
//STRIP001  return String();
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxPagePosSizeItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     String&             rText, const IntlWrapper *
//STRIP001 )    const
//STRIP001 {
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxPagePosSizeItem::Clone(SfxItemPool *pPool) const
/*N*/ {
/*N*/   return new SvxPagePosSizeItem(*this);
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SvxPagePosSizeItem::SvxPagePosSizeItem(const Point &rP, long lW, long lH)
/*N*/   : SfxPoolItem(SID_RULER_PAGE_POS),
/*N*/   aPos(rP),
/*N*/   lWidth(lW),
/*N*/   lHeight(lH)
/*N*/ {}

//------------------------------------------------------------------------

/*N*/ SvxPagePosSizeItem::SvxPagePosSizeItem(const SvxPagePosSizeItem &rCpy)
/*N*/   : SfxPoolItem(rCpy),
/*N*/   aPos(rCpy.aPos),
/*N*/   lWidth(rCpy.lWidth),
/*N*/   lHeight(rCpy.lHeight)
/*N*/       {}


//------------------------------------------------------------------------

/*N*/ void SvxColumnItem::DeleteAndDestroyColumns()
/*N*/ {
/*N*/   for( USHORT i = aColumns.Count(); i>0; )
/*N*/   {
/*N*/       SvxColumnDescription *pTmp = (SvxColumnDescription *)aColumns[--i];
/*N*/       aColumns.Remove( i );
/*N*/       delete pTmp;
/*N*/   }
/*N*/ }

//------------------------------------------------------------------------

/*N*/ int SvxColumnItem::operator==(const SfxPoolItem& rCmp) const
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if(!SfxPoolItem::operator==(rCmp) ||
//STRIP001     nActColumn != ((const SvxColumnItem&)rCmp).nActColumn ||
//STRIP001     nLeft != ((const SvxColumnItem&)rCmp).nLeft ||
//STRIP001     nRight != ((const SvxColumnItem&)rCmp).nRight ||
//STRIP001     bTable != ((const SvxColumnItem&)rCmp).bTable ||
//STRIP001     Count() != ((const SvxColumnItem&)rCmp).Count())
//STRIP001      return FALSE;
//STRIP001
//STRIP001  const USHORT nCount = ((const SvxColumnItem&)rCmp).Count();
//STRIP001  for(USHORT i = 0; i < nCount;++i) {
//STRIP001 #if OSL_DEBUG_LEVEL > 1
//STRIP001      SvxColumnDescription *p1 = (SvxColumnDescription *)aColumns[i],
//STRIP001                           *p2 = (SvxColumnDescription *)
//STRIP001                                  ((const SvxColumnItem&)rCmp).aColumns[i];
//STRIP001 #endif
//STRIP001      if( (*this)[i] != ((const SvxColumnItem&)rCmp)[i] )
//STRIP001          return FALSE;
//STRIP001  }
/*N*/   return TRUE;
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 String SvxColumnItem::GetValueText() const
//STRIP001 {
//STRIP001  return String();
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxColumnItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     String&             rText, const IntlWrapper *
//STRIP001 )    const
//STRIP001 {
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxColumnItem::Clone( SfxItemPool *pPool ) const
/*N*/ {
/*N*/   return new SvxColumnItem(*this);
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SvxColumnItem::SvxColumnItem( USHORT nAct ) :
/*N*/
/*N*/   SfxPoolItem( SID_RULER_BORDERS ),
/*N*/
/*N*/   nActColumn  ( nAct ),
/*N*/   nLeft       ( 0 ),
/*N*/   nRight      ( 0 ),
/*N*/   bTable      ( FALSE )
/*N*/
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SvxColumnItem::SvxColumnItem( USHORT nActCol, USHORT left, USHORT right ) :
//STRIP001
//STRIP001  SfxPoolItem( SID_RULER_BORDERS ),
//STRIP001
//STRIP001  nActColumn  ( nActCol ),
//STRIP001  nLeft       ( left ),
//STRIP001  nRight      ( right ),
//STRIP001  bTable      ( TRUE )
//STRIP001
//STRIP001 {
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ SvxColumnItem::SvxColumnItem( const SvxColumnItem& rCopy ) :
/*N*/
/*N*/   SfxPoolItem( rCopy ),
/*N*/
/*N*/     nActColumn( rCopy.nActColumn ),
/*N*/     nLeft     ( rCopy.nLeft ),
/*N*/     nRight    ( rCopy.nRight ),
/*N*/     bTable    ( rCopy.bTable ),
/*N*/     aColumns  ( (BYTE)rCopy.Count() )
/*N*/
/*N*/ {
/*N*/   const USHORT nCount = rCopy.Count();
/*N*/
/*N*/   for ( USHORT i = 0; i < nCount; ++i )
/*N*/       Append( rCopy[i] );
/*N*/ }

//------------------------------------------------------------------------

/*N*/ SvxColumnItem::~SvxColumnItem()
/*N*/ {
/*N*/   DeleteAndDestroyColumns();
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 const SvxColumnItem &SvxColumnItem::operator=(const SvxColumnItem &rCopy)
//STRIP001 {
//STRIP001  nLeft = rCopy.nLeft;
//STRIP001  nRight = rCopy.nRight;
//STRIP001  bTable = rCopy.bTable;
//STRIP001  nActColumn = rCopy.nActColumn;
//STRIP001  DeleteAndDestroyColumns();
//STRIP001  const USHORT nCount = rCopy.Count();
//STRIP001  for(USHORT i = 0; i < nCount;++i)
//STRIP001      Insert(rCopy[i], i);
//STRIP001  return *this;
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ BOOL SvxColumnItem::CalcOrtho() const
/*N*/ {
/*N*/   const USHORT nCount = Count();
/*N*/   DBG_ASSERT(nCount >= 2, "keine Spalten");
/*N*/   if(nCount < 2)
/*N*/       return FALSE;
/*N*/
/*N*/   const USHORT nColWidth = (*this)[0].GetWidth();
/*N*/   for(USHORT i = 1; i < nCount; ++i) {
/*N*/       if( (*this)[i].GetWidth() != nColWidth)
/*N*/           return FALSE;
/*N*/   }
/*N*/   //!! Breite Trenner
/*N*/   return TRUE;
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 long SvxColumnItem::GetVisibleRight() const
//STRIP001 {
//STRIP001  USHORT nIdx = 0;
//STRIP001
//STRIP001  for ( USHORT i = 0; i < nActColumn; ++i )
//STRIP001  {
//STRIP001      if ( (*this)[i].bVisible )
//STRIP001          ++nIdx;
//STRIP001  }
//STRIP001  return (*this)[nIdx].nEnd;
//STRIP001 }

//STRIP001 sal_Bool SvxColumnItem::QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId ) const
//STRIP001 {
//STRIP001  sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
//STRIP001  nMemberId &= ~CONVERT_TWIPS;
//STRIP001     switch ( nMemberId )
//STRIP001     {
//STRIP001         case MID_COLUMNARRAY:
//STRIP001         {
//STRIP001             return sal_False;
//STRIP001             break;
//STRIP001         }
//STRIP001         case MID_RIGHT: rVal <<= nRight; break;
//STRIP001         case MID_LEFT: rVal <<= nLeft; break;
//STRIP001         case MID_ORTHO: rVal <<= (sal_Bool) bOrtho; break;
//STRIP001         case MID_ACTUAL: rVal <<= (sal_Int32) nActColumn; break;
//STRIP001         case MID_TABLE: rVal <<= (sal_Bool) bTable; break;
//STRIP001         default: DBG_ERROR("Wrong MemberId!"); return sal_False;
//STRIP001     }
//STRIP001
//STRIP001     return sal_True;
//STRIP001 }

//STRIP001 sal_Bool SvxColumnItem::PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId )
//STRIP001 {
//STRIP001  sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
//STRIP001  nMemberId &= ~CONVERT_TWIPS;
//STRIP001     sal_Int32 nVal;
//STRIP001     switch ( nMemberId )
//STRIP001     {
//STRIP001         case MID_COLUMNARRAY:
//STRIP001         {
//STRIP001             return sal_False;
//STRIP001             break;
//STRIP001         }
//STRIP001         case MID_RIGHT: rVal >>= nRight; break;
//STRIP001         case MID_LEFT: rVal >>= nLeft; break;
//STRIP001         case MID_ORTHO: rVal >>= nVal; bOrtho = (BOOL) nVal; break;
//STRIP001         case MID_ACTUAL: rVal >>= nVal; nActColumn = (USHORT) nVal; break;
//STRIP001         case MID_TABLE: rVal >>= nVal; bTable = (BOOL) nVal; break;
//STRIP001         default: DBG_ERROR("Wrong MemberId!"); return sal_False;
//STRIP001     }
//STRIP001
//STRIP001     return sal_True;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 int SvxObjectItem::operator==( const SfxPoolItem& rCmp ) const
//STRIP001 {
//STRIP001  return SfxPoolItem::operator==(rCmp) &&
//STRIP001     nStartX == ((const SvxObjectItem&)rCmp).nStartX &&
//STRIP001     nEndX == ((const SvxObjectItem&)rCmp).nEndX &&
//STRIP001     nStartY == ((const SvxObjectItem&)rCmp).nStartY &&
//STRIP001     nEndY == ((const SvxObjectItem&)rCmp).nEndY &&
//STRIP001     bLimits == ((const SvxObjectItem&)rCmp).bLimits;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 String SvxObjectItem::GetValueText() const
//STRIP001 {
//STRIP001  return String();
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxObjectItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     String&             rText, const IntlWrapper *
//STRIP001 )    const
//STRIP001 {
//STRIP001  return SFX_ITEM_PRESENTATION_NONE;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxPoolItem* SvxObjectItem::Clone(SfxItemPool *pPool) const
//STRIP001 {
//STRIP001  return new SvxObjectItem(*this);
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ SvxObjectItem::SvxObjectItem( long nSX, long nEX,
/*N*/                             long nSY, long nEY, BOOL limits ) :
/*N*/
/*N*/   SfxPoolItem( SID_RULER_OBJECT ),
/*N*/
/*N*/   nStartX ( nSX ),
/*N*/   nEndX   ( nEX ),
/*N*/   nStartY ( nSY ),
/*N*/   nEndY   ( nEY ),
/*N*/   bLimits ( limits )
/*N*/
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SvxObjectItem::SvxObjectItem( const SvxObjectItem& rCopy ) :
//STRIP001
//STRIP001  SfxPoolItem( rCopy ),
//STRIP001
//STRIP001  nStartX ( rCopy.nStartX ),
//STRIP001  nEndX   ( rCopy.nEndX ),
//STRIP001  nStartY ( rCopy.nStartY ),
//STRIP001  nEndY   ( rCopy.nEndY ),
//STRIP001  bLimits ( rCopy.bLimits )
//STRIP001
//STRIP001 {
//STRIP001 }

//STRIP001 sal_Bool SvxObjectItem::QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId ) const
//STRIP001 {
//STRIP001     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
//STRIP001     nMemberId &= ~CONVERT_TWIPS;
//STRIP001     sal_Int32 nVal = 0;
//STRIP001     switch ( nMemberId )
//STRIP001     {
//STRIP001         case MID_START_X : rVal <<= nStartX; break;
//STRIP001         case MID_START_Y : rVal <<= nStartY; break;
//STRIP001         case MID_END_X : rVal <<= nEndX; break;
//STRIP001         case MID_END_Y : rVal <<= nEndY; break;
//STRIP001         case MID_LIMIT : rVal <<= bLimits; break;
//STRIP001         default:
//STRIP001             DBG_ERROR( "Wrong MemberId" );
//STRIP001             return sal_False;
//STRIP001     }
//STRIP001
//STRIP001     return TRUE;
//STRIP001 }

//STRIP001 sal_Bool SvxObjectItem::PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId )
//STRIP001 {
//STRIP001     sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
//STRIP001     nMemberId &= ~CONVERT_TWIPS;
//STRIP001     BOOL bRet=FALSE;
//STRIP001     switch ( nMemberId )
//STRIP001     {
//STRIP001         case MID_START_X : bRet = (rVal >>= nStartX); break;
//STRIP001         case MID_START_Y : bRet = (rVal >>= nStartY); break;
//STRIP001         case MID_END_X : bRet = (rVal >>= nEndX); break;
//STRIP001         case MID_END_Y : bRet = (rVal >>= nEndY); break;
//STRIP001         case MID_LIMIT : bRet = (rVal >>= bLimits); break;
//STRIP001         default: DBG_ERROR( "Wrong MemberId" );
//STRIP001     }
//STRIP001
//STRIP001     return bRet;
//STRIP001 }

}
