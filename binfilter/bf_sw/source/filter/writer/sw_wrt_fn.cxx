/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_wrt_fn.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 03:26:55 $
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


#pragma hdrstop

// auto strip #ifndef _SFXITEMITER_HXX //autogen
// auto strip #include <svtools/itemiter.hxx>
// auto strip #endif
// auto strip #ifndef _SFX_WHITER_HXX //autogen
// auto strip #include <svtools/whiter.hxx>
// auto strip #endif


#include "shellio.hxx"
#include "wrt_fn.hxx"

// auto strip #ifndef _HORIORNT_HXX
// auto strip #include <horiornt.hxx>
// auto strip #endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

// auto strip #include "pam.hxx"
#include "node.hxx"
// auto strip #include "format.hxx"
namespace binfilter {



//STRIP001 Writer& Out( const SwAttrFnTab pTab, const SfxPoolItem& rHt, Writer & rWrt )
//STRIP001 {
//STRIP001  USHORT nId = rHt.Which();
//STRIP001  ASSERT(  nId < POOLATTR_END && nId >= POOLATTR_BEGIN, "SwAttrFnTab::Out()" );
//STRIP001  FnAttrOut pOut;
//STRIP001  if( 0 != ( pOut = pTab[ nId - RES_CHRATR_BEGIN] ))
//STRIP001      (*pOut)( rWrt, rHt );
//STRIP001  return rWrt;
//STRIP001
//STRIP001 }

//STRIP001 Writer& Out_SfxItemSet( const SwAttrFnTab pTab, Writer& rWrt,
//STRIP001                      const SfxItemSet& rSet, BOOL bDeep,
//STRIP001                      BOOL bTstForDefault )
//STRIP001 {
//STRIP001  // erst die eigenen Attribute ausgeben
//STRIP001  const SfxItemPool& rPool = *rSet.GetPool();
//STRIP001  const SfxItemSet* pSet = &rSet;
//STRIP001  if( !pSet->Count() )        // Optimierung - leere Sets
//STRIP001  {
//STRIP001      if( !bDeep )
//STRIP001          return rWrt;
//STRIP001      while( 0 != ( pSet = pSet->GetParent() ) && !pSet->Count() )
//STRIP001          ;
//STRIP001      if( !pSet )
//STRIP001          return rWrt;
//STRIP001  }
//STRIP001  const SfxPoolItem* pItem;
//STRIP001  FnAttrOut pOut;
//STRIP001  if( !bDeep || !pSet->GetParent() )
//STRIP001  {
//STRIP001      ASSERT( rSet.Count(), "Wurde doch schon behandelt oder?" );
//STRIP001      SfxItemIter aIter( *pSet );
//STRIP001      pItem = aIter.GetCurItem();
//STRIP001      do {
//STRIP001          if( 0 != ( pOut = pTab[ pItem->Which() - RES_CHRATR_BEGIN] ))
//STRIP001                  (*pOut)( rWrt, *pItem );
//STRIP001      } while( !aIter.IsAtEnd() && 0 != ( pItem = aIter.NextItem() ) );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SfxWhichIter aIter( *pSet );
//STRIP001      register USHORT nWhich = aIter.FirstWhich();
//STRIP001      while( nWhich )
//STRIP001      {
//STRIP001          if( SFX_ITEM_SET == pSet->GetItemState( nWhich, bDeep, &pItem ) &&
//STRIP001              ( !bTstForDefault || (
//STRIP001                  *pItem != rPool.GetDefaultItem( nWhich )
//STRIP001                  || ( pSet->GetParent() &&
//STRIP001                      *pItem != pSet->GetParent()->Get( nWhich ))
//STRIP001              )) && 0 != ( pOut = pTab[ nWhich - RES_CHRATR_BEGIN] ))
//STRIP001                  (*pOut)( rWrt, *pItem );
//STRIP001          nWhich = aIter.NextWhich();
//STRIP001      }
//STRIP001  }
//STRIP001  return rWrt;
//STRIP001 }



/*N*/ Writer& Out( const SwNodeFnTab pTab, SwNode& rNode, Writer & rWrt )
/*N*/ {
/*N*/   // es muss ein CntntNode sein !!
/*N*/   SwCntntNode * pCNd = rNode.GetCntntNode();
/*N*/   if( !pCNd )
/*?*/       return rWrt;
/*N*/
/*N*/   USHORT nId;
/*N*/   switch( pCNd->GetNodeType() )
/*N*/   {
/*N*/   case ND_TEXTNODE:   nId = RES_TXTNODE;  break;
/*?*/   case ND_GRFNODE:    nId = RES_GRFNODE;  break;
/*?*/   case ND_OLENODE:    nId = RES_OLENODE;  break;
/*?*/   default:
/*?*/       ASSERT( FALSE, "was fuer ein Node ist es denn nun?" );
/*N*/   }
/*N*/   FnNodeOut pOut;
/*N*/   if( 0 != ( pOut = pTab[ nId - RES_NODE_BEGIN ] ))
/*N*/       (*pOut)( rWrt, *pCNd );
/*N*/   return rWrt;
/*N*/ }


}
