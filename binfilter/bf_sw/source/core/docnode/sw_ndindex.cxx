/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_ndindex.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 17:46:35 $
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

#include "errhdl.hxx"           // fuers ASSERT
#include "error.h"              // fuers ASSERT
#include "ndindex.hxx"
namespace binfilter {

#ifndef PRODUCT
int SwNodeIndex::nSerial = 0;
#endif


/*N*/ SwNodeRange::SwNodeRange( const SwNodeIndex &rS, const SwNodeIndex &rE )
/*N*/   : aStart( rS ), aEnd( rE )
/*N*/ {}

/*N*/ SwNodeRange::SwNodeRange( const SwNodeRange &rRange )
/*N*/   : aStart( rRange.aStart ), aEnd( rRange.aEnd )
/*N*/ {}

/*N*/ SwNodeRange::SwNodeRange( const SwNodeIndex& rS, long nSttDiff,
/*N*/                         const SwNodeIndex& rE, long nEndDiff )
/*N*/   : aStart( rS, nSttDiff ), aEnd( rE, nEndDiff )
/*N*/ {}

/*N*/ SwNodeRange::SwNodeRange( const SwNode& rS, long nSttDiff,
/*N*/                         const SwNode& rE, long nEndDiff )
/*N*/   : aStart( rS, nSttDiff ), aEnd( rE, nEndDiff )
/*N*/ {}


/*N*/ SwNodeIndex::SwNodeIndex( SwNodes& rNds, ULONG nIdx )
/*N*/   : pNd( rNds[ nIdx ] ), pNext( 0 ), pPrev( 0 )
/*N*/ {
/*N*/   rNds.RegisterIndex( *this );
/*N*/
/*N*/ #ifndef PRODUCT
/*N*/   MySerial = ++nSerial;       // nur in der nicht PRODUCT-Version
/*N*/ #endif
/*N*/ }


/*N*/ SwNodeIndex::SwNodeIndex( const SwNodeIndex& rIdx, long nDiff )
/*N*/   : pNext( 0 ), pPrev( 0 )
/*N*/ {
/*N*/   if( nDiff )
/*N*/       pNd = rIdx.GetNodes()[ rIdx.GetIndex() + nDiff ];
/*N*/   else
/*N*/       pNd = rIdx.pNd;
/*N*/
/*N*/   pNd->GetNodes().RegisterIndex( *this );
/*N*/ #ifndef PRODUCT
/*N*/   MySerial = ++nSerial;       // nur in der nicht PRODUCT-Version
/*N*/ #endif
/*N*/ }


/*N*/ SwNodeIndex::SwNodeIndex( const SwNode& rNd, long nDiff )
/*N*/   : pNext( 0 ), pPrev( 0 )
/*N*/ {
/*N*/   if( nDiff )
/*N*/       pNd = rNd.GetNodes()[ rNd.GetIndex() + nDiff ];
/*N*/   else
/*N*/       pNd = (SwNode*)&rNd;
/*N*/
/*N*/   pNd->GetNodes().RegisterIndex( *this );
/*N*/ #ifndef PRODUCT
/*N*/   MySerial = ++nSerial;       // nur in der nicht PRODUCT-Version
/*N*/ #endif
/*N*/ }


/*N*/ void SwNodeIndex::Remove()
/*N*/ {
/*N*/   pNd->GetNodes().DeRegisterIndex( *this );
/*N*/ }

/*N*/ SwNodeIndex& SwNodeIndex::operator=( const SwNodeIndex& rIdx )
/*N*/ {
/*N*/   if( &pNd->GetNodes() != &rIdx.pNd->GetNodes() )
/*N*/   {
/*N*/       pNd->GetNodes().DeRegisterIndex( *this );
/*N*/       pNd = rIdx.pNd;
/*N*/       pNd->GetNodes().RegisterIndex( *this );
/*N*/   }
/*N*/   else
/*N*/       pNd = rIdx.pNd;
/*N*/   return *this;
/*N*/ }

/*N*/ SwNodeIndex& SwNodeIndex::operator=( const SwNode& rNd )
/*N*/ {
/*N*/   if( &pNd->GetNodes() != &rNd.GetNodes() )
/*N*/   {
/*?*/       pNd->GetNodes().DeRegisterIndex( *this );
/*?*/       pNd = (SwNode*)&rNd;
/*?*/       pNd->GetNodes().RegisterIndex( *this );
/*N*/   }
/*N*/   else
/*N*/       pNd = (SwNode*)&rNd;
/*N*/   return *this;
/*N*/ }


/*N*/ SwNodeIndex& SwNodeIndex::Assign( const SwNode& rNd, long nOffset )
/*N*/ {
/*N*/   if( &pNd->GetNodes() != &rNd.GetNodes() )
/*N*/   {
/*?*/       pNd->GetNodes().DeRegisterIndex( *this );
/*?*/       pNd = (SwNode*)&rNd;
/*?*/       pNd->GetNodes().RegisterIndex( *this );
/*N*/   }
/*N*/   else
/*N*/       pNd = (SwNode*)&rNd;
/*N*/
/*N*/   if( nOffset )
/*N*/       pNd = pNd->GetNodes()[ pNd->GetIndex() + nOffset ];
/*N*/
/*N*/   return *this;
/*N*/ }


}
