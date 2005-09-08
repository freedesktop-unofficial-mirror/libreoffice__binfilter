/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_unusedf.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 09:54:01 $
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

// auto strip #include "rootfrm.hxx"
#include "cntfrm.hxx"

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

// auto strip #include "flyfrm.hxx"
// auto strip #include "errhdl.hxx"
namespace binfilter {


//STRIP001 void SwFrm::Format( const SwBorderAttrs * )
//STRIP001 {
//STRIP001  ASSERT( FALSE, "Format() der Basisklasse gerufen." );
//STRIP001 }

//STRIP001 void SwFrm::Paint(const SwRect &) const
//STRIP001 {
//STRIP001  ASSERT( FALSE, "Paint() der Basisklasse gerufen." );
//STRIP001 }

/*N*/ BOOL SwCntntFrm::WouldFit( SwTwips &, BOOL& )
/*N*/ {
/*N*/   ASSERT( FALSE, "WouldFit des CntntFrm gerufen." );
/*N*/   return FALSE;
/*N*/ }

//STRIP001 BOOL SwFrm::GetCrsrOfst( SwPosition *, Point&, const SwCrsrMoveState*  ) const
//STRIP001 {
//STRIP001  ASSERT( FALSE, "GetCrsrOfst der Basisklasse, hi!" );
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 #ifndef PRODUCT

//STRIP001 void SwRootFrm::Cut()
//STRIP001 {
//STRIP001  ASSERT( FALSE, "Cut() des RootFrm gerufen." );
//STRIP001 }

//STRIP001 void SwRootFrm::Paste( SwFrm *, SwFrm * )
//STRIP001 {
//STRIP001  ASSERT( FALSE, "Paste() des RootFrm gerufen." );
//STRIP001 }

//STRIP001 void SwFlyFrm::Paste( SwFrm *, SwFrm * )
//STRIP001 {
//STRIP001  ASSERT( FALSE, "Paste() des FlyFrm gerufen." );
//STRIP001 }

//STRIP001 #endif

/*N*/ BOOL SwFrm::GetCharRect( SwRect&, const SwPosition&,
/*N*/                        SwCrsrMoveState* ) const
/*N*/ {
/*N*/   ASSERT( FALSE, "GetCharRect() der Basis gerufen." );
/*N*/   return FALSE;
/*N*/ }


}
