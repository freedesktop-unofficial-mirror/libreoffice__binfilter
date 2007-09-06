/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_editsel.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:36:18 $
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




#ifndef _SV_WINDOW_HXX
#include <vcl/window.hxx>
#endif

#include <impedit.hxx>
#include <editview.hxx>
namespace binfilter {

//  ----------------------------------------------------------------------
//  class EditSelFunctionSet
//  ----------------------------------------------------------------------
/*N*/ EditSelFunctionSet::EditSelFunctionSet()
/*N*/ {
/*N*/   pCurView = NULL;
/*N*/ }

/*N*/ void __EXPORT EditSelFunctionSet::CreateAnchor()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

/*N*/ void __EXPORT EditSelFunctionSet::DestroyAnchor()
/*N*/ {
/*N*/   // Nur bei Mehrfachselektion
/*N*/ }

/*N*/ BOOL __EXPORT EditSelFunctionSet::SetCursorAtPoint( const Point& rPointPixel, BOOL )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   return FALSE;
/*N*/ }

/*N*/ BOOL __EXPORT EditSelFunctionSet::IsSelectionAtPoint( const Point& rPointPixel )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/     return FALSE;
/*N*/ }

/*N*/ void __EXPORT EditSelFunctionSet::DeselectAtPoint( const Point& )
/*N*/ {
/*N*/ // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*N*/ // !  Implementieren, wenn Mehrfachselektion moeglich  !
/*N*/ // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*N*/ }

/*N*/ void __EXPORT EditSelFunctionSet::BeginDrag()
/*N*/ {
/*N*/   // Nur bei Mehrfachselektion
/*N*/ }


/*N*/ void __EXPORT EditSelFunctionSet::DeselectAll()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

//  ----------------------------------------------------------------------
//  class EditSelectionEngine
//  ----------------------------------------------------------------------
/*N*/ EditSelectionEngine::EditSelectionEngine() : SelectionEngine( (Window*)0 )
/*N*/ {
/*N*/   // Wegen Bug OV: (1994)
/*N*/   // 1995: RangeSelection lassen, SingleSelection nur fuer ListBoxen geeignet!
/*N*/   SetSelectionMode( RANGE_SELECTION );
/*N*/   EnableDrag( TRUE );
/*N*/ }

/*N*/ void EditSelectionEngine::SetCurView( EditView* pNewView )
/*N*/ {
/*N*/   if ( GetFunctionSet() )
/*N*/       ((EditSelFunctionSet*)GetFunctionSet())->SetCurView( pNewView );
/*N*/
/*N*/   if ( pNewView )
/*?*/       SetWindow( pNewView->GetWindow() );
/*N*/   else
/*N*/       SetWindow( (Window*)0 );
/*N*/ }


}
