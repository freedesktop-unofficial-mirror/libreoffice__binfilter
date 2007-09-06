/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_flypos.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:19:10 $
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

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#include "doc.hxx"

#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif


#ifndef _FMTANCHR_HXX //autogen
#include <fmtanchr.hxx>
#endif
#include "flypos.hxx"
#include "frmfmt.hxx"
#include "dcontact.hxx"
#include "flyfrm.hxx"
#include "dflyobj.hxx"
#include "ndindex.hxx"
namespace binfilter {



/*N*/ SV_IMPL_OP_PTRARR_SORT( SwPosFlyFrms, SwPosFlyFrmPtr )

/*N*/ SwPosFlyFrm::SwPosFlyFrm( const SwNodeIndex& rIdx, const SwFrmFmt* pFmt,
/*N*/                           USHORT nArrPos )
/*N*/   : pNdIdx( (SwNodeIndex*) &rIdx ), pFrmFmt( pFmt )
/*N*/ {
/*N*/   BOOL bFnd = FALSE;
/*N*/   const SwFmtAnchor& rAnchor = pFmt->GetAnchor();
/*N*/   if( FLY_PAGE == rAnchor.GetAnchorId() )
/*?*/       pNdIdx = new SwNodeIndex( rIdx );
/*N*/   else if( pFmt->GetDoc()->GetRootFrm() )
/*N*/   {
/*N*/       SwClientIter aIter( (SwFmt&)*pFmt );
/*N*/       if( RES_FLYFRMFMT == pFmt->Which() )
/*N*/       {
/*N*/           // Schauen, ob es ein SdrObject dafuer gibt
/*N*/           if( aIter.First( TYPE( SwFlyFrm) ) )
/*N*/               nOrdNum = ((SwFlyFrm*)aIter())->GetVirtDrawObj()->GetOrdNum(),
/*N*/               bFnd = TRUE;
/*N*/       }
/*N*/       else if( RES_DRAWFRMFMT == pFmt->Which() )
/*N*/       {
/*N*/           // Schauen, ob es ein SdrObject dafuer gibt
/*N*/           if( aIter.First( TYPE(SwDrawContact) ) )
/*N*/               nOrdNum = ((SwDrawContact*)aIter())->GetMaster()->GetOrdNum(),
/*N*/               bFnd = TRUE;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if( !bFnd )
/*N*/   {
/*N*/       nOrdNum = pFmt->GetDoc()->GetSpzFrmFmts()->Count();
/*N*/       nOrdNum += nArrPos;
/*N*/   }
/*N*/ }

/*N*/ SwPosFlyFrm::~SwPosFlyFrm()
/*N*/ {
/*N*/   const SwFmtAnchor& rAnchor = pFrmFmt->GetAnchor();
/*N*/   if( FLY_PAGE == rAnchor.GetAnchorId() )
/*?*/       delete pNdIdx;
/*N*/ }

/*N*/ BOOL SwPosFlyFrm::operator==( const SwPosFlyFrm& rPosFly )
/*N*/ {
/*N*/   return FALSE;   // FlyFrames koennen auf der gleichen Position stehen
/*N*/ }

/*N*/ BOOL SwPosFlyFrm::operator<( const SwPosFlyFrm& rPosFly )
/*N*/ {
/*N*/   if( pNdIdx->GetIndex() == rPosFly.pNdIdx->GetIndex() )
/*N*/   {
/*N*/       // dann entscheidet die Ordnungsnummer!
/*N*/       return nOrdNum < rPosFly.nOrdNum;
/*N*/   }
/*N*/   return pNdIdx->GetIndex() < rPosFly.pNdIdx->GetIndex();
/*N*/ }



}
