/*************************************************************************
 *
 *  $RCSfile: svx_editsel.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 15:34:30 $
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
