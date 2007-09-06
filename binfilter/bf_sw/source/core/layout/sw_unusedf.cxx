/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_unusedf.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:23:01 $
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

#include "cntfrm.hxx"

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

namespace binfilter {




/*N*/ BOOL SwCntntFrm::WouldFit( SwTwips &, BOOL& )
/*N*/ {
/*N*/   ASSERT( FALSE, "WouldFit des CntntFrm gerufen." );
/*N*/   return FALSE;
/*N*/ }







/*N*/ BOOL SwFrm::GetCharRect( SwRect&, const SwPosition&,
/*N*/                        SwCrsrMoveState* ) const
/*N*/ {
/*N*/   ASSERT( FALSE, "GetCharRect() der Basis gerufen." );
/*N*/   return FALSE;
/*N*/ }


}
