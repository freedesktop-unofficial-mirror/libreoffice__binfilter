/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_txatbase.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 10:22:17 $
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


#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef _SFXITEMPOOL_HXX
#include <bf_svtools/itempool.hxx>
#endif
#ifndef _TXATBASE_HXX
#include <txatbase.hxx>
#endif
namespace binfilter {

/*N*/ SwTxtAttr::SwTxtAttr( const SfxPoolItem& rAttr, xub_StrLen nStt )
/*N*/   : pAttr( &rAttr ), nStart( nStt )
/*N*/ {
/*N*/   bDontExpand = bLockExpandFlag = bDontMergeAttr = bDontMoveAttr =
/*N*/         bCharFmtAttr = bOverlapAllowedAttr = bPriorityAttr =
/*N*/       bDontExpandStart = FALSE;
/*N*/ }

/*N*/ SwTxtAttr::~SwTxtAttr( )
/*N*/ {
/*N*/ }

/*N*/ xub_StrLen* SwTxtAttr::GetEnd()
/*N*/ {
/*N*/   return 0;
/*N*/ }

    // RemoveFromPool muss immer vorm DTOR Aufruf erfolgen!!
    // Meldet sein Attribut beim Pool ab
/*N*/ void SwTxtAttr::RemoveFromPool( SfxItemPool& rPool )
/*N*/ {
/*N*/   rPool.Remove( GetAttr() );
/*N*/   pAttr = 0;
/*N*/ }


/*N*/ SwTxtAttrEnd::SwTxtAttrEnd( const SfxPoolItem& rAttr, xub_StrLen nS,
/*N*/                           xub_StrLen nE )
/*N*/   : SwTxtAttr( rAttr, nS ), nEnd( nE )
/*N*/ {
/*N*/ }

/*N*/ xub_StrLen* SwTxtAttrEnd::GetEnd()
/*N*/ {
/*N*/   return &nEnd;
/*N*/ }
}
