/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_wrt_fn.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 23:46:39 $
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



#include "shellio.hxx"
#include "wrt_fn.hxx"

#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

#include "node.hxx"
namespace binfilter {







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
