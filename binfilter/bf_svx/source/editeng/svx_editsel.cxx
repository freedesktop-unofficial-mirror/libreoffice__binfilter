/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_editsel.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 05:23:42 $
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

// auto strip #include <eeng_pch.hxx>

#pragma hdrstop

// auto strip #include <editsel.hxx>

// auto strip #ifndef _SV_OUTDEV_HXX
// auto strip #include <vcl/outdev.hxx>
// auto strip #endif

// auto strip #ifndef _VCL_POINTR_HXX
// auto strip #include <vcl/pointr.hxx>
// auto strip #endif

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
//STRIP001  if ( pCurView )
//STRIP001      pCurView->pImpEditView->CreateAnchor();
/*N*/ }

/*N*/ void __EXPORT EditSelFunctionSet::DestroyAnchor()
/*N*/ {
/*N*/   // Nur bei Mehrfachselektion
/*N*/ }

/*N*/ BOOL __EXPORT EditSelFunctionSet::SetCursorAtPoint( const Point& rPointPixel, BOOL )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if ( pCurView )
//STRIP001      return pCurView->pImpEditView->SetCursorAtPoint( rPointPixel );
//STRIP001
/*N*/   return FALSE;
/*N*/ }

/*N*/ BOOL __EXPORT EditSelFunctionSet::IsSelectionAtPoint( const Point& rPointPixel )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if ( pCurView )
//STRIP001      return pCurView->pImpEditView->IsSelectionAtPoint( rPointPixel );
//STRIP001
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
//STRIP001  if ( pCurView )
//STRIP001      pCurView->pImpEditView->DeselectAll();
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

//STRIP001 EditView* EditSelectionEngine::GetCurView()
//STRIP001 {
//STRIP001  EditView* pView = 0;
//STRIP001  if ( GetFunctionSet() )
//STRIP001      pView = ((EditSelFunctionSet*)GetFunctionSet())->GetCurView();
//STRIP001
//STRIP001  return pView;
//STRIP001 }

}
