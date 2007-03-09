/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_rulritem.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: obo $ $Date: 2007-03-09 15:47:00 $
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

/*N*/ #define TWIP_TO_MM100(TWIP)   ((TWIP) >= 0 ? (((TWIP)*127L+36L)/72L) : (((TWIP)*127L-36L)/72L))
/*N*/ #define MM100_TO_TWIP(MM100)  ((MM100) >= 0 ? (((MM100)*72L+63L)/127L) : (((MM100)*72L-63L)/127L))

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
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   return TRUE;
/*N*/ }

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
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

}
