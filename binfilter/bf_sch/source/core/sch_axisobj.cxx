/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sch_axisobj.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 21:50:02 $
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

// header for SdrObjListIter
// auto strip #ifndef _SVDITER_HXX
// auto strip #include <bf_svx/svditer.hxx>
// auto strip #endif
// header for SdrHdlList
// auto strip #ifndef _SVDHDL_HXX
// auto strip #include <bf_svx/svdhdl.hxx>
// auto strip #endif

#include "axisobj.hxx"
namespace binfilter {

// ==================== SchAxisObj ====================

/*N*/ TYPEINIT1( SchAxisObj, SchObjGroup );

/*N*/ SchAxisObj::SchAxisObj( ChartModel *pModel ) :
/*N*/       SchObjGroup( pModel )
/*N*/ {
/*N*/ }

//STRIP001 void SchAxisObj::AddToHdlList( SdrHdlList& rHdlList ) const
//STRIP001 {
//STRIP001  // don't use method overloaded by Schgroup
//STRIP001  SdrObject::AddToHdlList( rHdlList );
//STRIP001 }

//STRIP001 USHORT SchAxisObj::GetHdlCount() const
//STRIP001 {
//STRIP001  // there are just two handles: the start and end of the main axis line
//STRIP001  return GetSubList()? 2: 0;
//STRIP001 }

//STRIP001 SdrHdl* SchAxisObj::GetHdl( USHORT nHdlNum ) const
//STRIP001 {
//STRIP001  // return the handles of the first line in the axis group
//STRIP001  SdrObjList* pList = GetSubList();
//STRIP001  if( pList )
//STRIP001  {
//STRIP001      SdrObjListIter aListIter( *this );
//STRIP001      if( aListIter.IsMore() )
//STRIP001      {
//STRIP001          return aListIter.Next()->GetHdl( nHdlNum );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return NULL;
//STRIP001 }

// ==================== Sch3dAxisObj ====================

/*N*/ TYPEINIT1( Sch3dAxisObj, SchE3dObject );

/*N*/ Sch3dAxisObj::Sch3dAxisObj()
/*N*/       : SchE3dObject()
/*N*/ {
/*N*/ }

//STRIP001 void Sch3dAxisObj::AddToHdlList( SdrHdlList& rHdlList ) const
//STRIP001 {
//STRIP001  SdrObjList* pList = GetSubList();
//STRIP001  if( pList &&
//STRIP001      pList->GetObjCount() )
//STRIP001  {
//STRIP001      pList->GetObj( 0 )->AddToHdlList( rHdlList );
//STRIP001  }
//STRIP001  else
//STRIP001      E3dObject::AddToHdlList( rHdlList );
//STRIP001 }

}
