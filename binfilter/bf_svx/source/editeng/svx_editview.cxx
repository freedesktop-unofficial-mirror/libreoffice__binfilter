/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_editview.cxx,v $
 *
 *  $Revision: 1.9 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 11:32:58 $
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

#define _SOLAR__PRIVATE 1




#ifndef _SV_WINDOW_HXX
#include <vcl/window.hxx>
#endif

#include <impedit.hxx>
#include <editeng.hxx>
#include <editview.hxx>



#ifndef _SVX_ITEMDATA_HXX
#include "itemdata.hxx"
#endif



#include <editeng.hrc>
#include <helpid.hrc>

#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUES_HDL_
#include <com/sun/star/beans/PropertyValues.hdl>
#endif
namespace binfilter {

using namespace rtl;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::linguistic2;


/*N*/ DBG_NAME( EditView )

// From SW => Create common method


// ----------------------------------------------------------------------
// class EditView
// ----------------------------------------------------------------------
/*N*/ EditView::EditView( EditEngine* pEng, Window* pWindow )
/*N*/ {
/*N*/   DBG_CTOR( EditView, 0 );
/*N*/   pImpEditView = new ImpEditView( this, pEng, pWindow );
/*N*/ }

/*N*/ EditView::~EditView()
/*N*/ {
/*N*/   DBG_DTOR( EditView, 0 );
/*N*/   delete pImpEditView;
/*N*/ }


/*N*/ EditEngine* EditView::GetEditEngine() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditView, 0 );
/*N*/   DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
/*N*/   return pImpEditView->pEditEngine;
/*N*/ }

/*N*/ void EditView::SetSelection( const ESelection& rESel )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditView, 0 );
/*N*/   DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
/*N*/
/*N*/   // Falls jemand gerade ein leeres Attribut hinterlassen hat,
/*N*/   // und dann der Outliner die Selektion manipulitert:
/*N*/   if ( !pImpEditView->GetEditSelection().HasRange() )
/*N*/   {
/*N*/       ContentNode* pNode = pImpEditView->GetEditSelection().Max().GetNode();
/*N*/       PIMPEE->CursorMoved( pNode );
/*N*/   }
/*N*/   EditSelection aNewSelection( PIMPEE->ConvertSelection( rESel.nStartPara, rESel.nStartPos, rESel.nEndPara, rESel.nEndPos ) );
/*N*/
/*N*/   // Selektion darf nicht bei einem unsichtbaren Absatz Starten/Enden:
/*N*/   ParaPortion* pPortion = PIMPEE->FindParaPortion( aNewSelection.Min().GetNode() );
/*N*/   if ( !pPortion->IsVisible() )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 pPortion = PIMPEE->GetPrevVisPortion( pPortion );
/*N*/   }
/*N*/   pPortion = PIMPEE->FindParaPortion( aNewSelection.Max().GetNode() );
/*N*/   if ( !pPortion->IsVisible() )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 pPortion = PIMPEE->GetPrevVisPortion( pPortion );
/*N*/   }
/*N*/
/*N*/   pImpEditView->DrawSelection();  // alte Selektion 'weg-zeichnen'
/*N*/   pImpEditView->SetEditSelection( aNewSelection );
/*N*/   pImpEditView->DrawSelection();
/*N*/   sal_Bool bGotoCursor = pImpEditView->DoAutoScroll();
/*N*/   ShowCursor( bGotoCursor );
/*N*/ }

/*N*/ ESelection EditView::GetSelection() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditView, 0 );
/*N*/   DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
/*N*/
/*N*/   ESelection aSelection;
/*N*/
/*N*/   aSelection.nStartPara = PIMPEE->GetEditDoc().GetPos( pImpEditView->GetEditSelection().Min().GetNode() );
/*N*/   aSelection.nEndPara = PIMPEE->GetEditDoc().GetPos( pImpEditView->GetEditSelection().Max().GetNode() );
/*N*/
/*N*/   aSelection.nStartPos = pImpEditView->GetEditSelection().Min().GetIndex();
/*N*/   aSelection.nEndPos = pImpEditView->GetEditSelection().Max().GetIndex();
/*N*/
/*N*/   return aSelection;
/*N*/ }

/*N*/ sal_Bool EditView::HasSelection() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditView, 0 );
/*N*/   return pImpEditView->HasSelection();
/*N*/ }






/*N*/ Window*   EditView::GetWindow() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditView, 0 );
/*N*/   return pImpEditView->pOutWin;
/*N*/ }

/*N*/ void EditView::SetVisArea( const Rectangle& rRec )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

/*N*/ const Rectangle& EditView::GetVisArea() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditView, 0 );
/*N*/   // Change return value to Rectangle in next incompatible build !!!
/*N*/   static Rectangle aRect;
/*N*/   aRect = pImpEditView->GetVisDocArea();
/*N*/   return aRect;
/*N*/ }

/*N*/ void EditView::SetOutputArea( const Rectangle& rRec )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditView, 0 );
/*N*/   pImpEditView->SetOutputArea( rRec );
/*N*/
/*N*/   // Rest nur hier, wenn API-Aufruf:
/*N*/   pImpEditView->CalcAnchorPoint();
/*N*/   if ( PIMPEE->GetStatus().AutoPageSize() )
/*?*/   {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     pImpEditView->RecalcOutputArea();
/*N*/   pImpEditView->ShowCursor( sal_False, sal_False );
/*N*/ }

/*N*/ const Rectangle& EditView::GetOutputArea() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditView, 0 );
/*N*/   return pImpEditView->GetOutputArea();
/*N*/ }


/*N*/ void EditView::ShowCursor( sal_Bool bGotoCursor, sal_Bool bForceVisCursor )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditView, 0 );
/*N*/   DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
/*N*/
/*N*/ // Draw vertraegt die Assertion nicht, spaeter mal aktivieren
/*N*/ //    DBG_ASSERT( pImpEditView->pEditEngine->HasView( this ), "ShowCursor - View nicht angemeldet!" );
/*N*/ //    DBG_ASSERT( !GetWindow()->IsInPaint(), "ShowCursor - Why in Paint ?!" );
/*N*/
/*N*/   if ( pImpEditView->pEditEngine->HasView( this ) )
/*N*/   {
/*N*/       // Das ControlWord hat mehr Gewicht:
/*N*/       if ( !pImpEditView->DoAutoScroll() )
/*N*/           bGotoCursor = sal_False;
/*N*/       pImpEditView->ShowCursor( bGotoCursor, bForceVisCursor );
/*N*/   }
/*N*/ }

/*N*/ void EditView::HideCursor()
/*N*/ {
/*N*/   DBG_CHKTHIS( EditView, 0 );
/*N*/   pImpEditView->GetCursor()->Hide();
/*N*/ }











#ifndef SVX_LIGHT
#endif

/*N*/ void EditView::Cut()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

/*N*/ void EditView::Copy()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

/*N*/ void EditView::Paste()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }









/*N*/ void EditView::SetSelectionMode( EESelectionMode eMode )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditView, 0 );
/*N*/   pImpEditView->SetSelectionMode( eMode );
/*N*/ }

/*N*/ const SvxFieldItem* EditView::GetField( const Point& rPos, sal_uInt16* pPara, sal_uInt16* pPos ) const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditView, 0 );
/*N*/   DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
/*N*/   return pImpEditView->GetField( rPos, pPara, pPos );
/*N*/ }








}
