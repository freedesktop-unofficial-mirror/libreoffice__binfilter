/*************************************************************************
 *
 *  $RCSfile: sw_wrt_fn.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 18:21:05 $
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
