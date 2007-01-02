/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_outlvw.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 17:29:30 $
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


#define _OUTLINER_CXX
#include <outleeng.hxx>










#ifndef _MyEDITVIEW_HXX
#include "editview.hxx"
#endif

namespace binfilter {


// Breite der Randzonen innerhalb derer beim D&D gescrollt wird
#define OL_SCROLL_LRBORDERWIDTHPIX  10
#define OL_SCROLL_TBBORDERWIDTHPIX  10

// Wert, um den Fensterinhalt beim D&D gescrollt wird
#define OL_SCROLL_HOROFFSET         20  /* in % von VisibleSize.Width */
#define OL_SCROLL_VEROFFSET         20  /* in % von VisibleSize.Height */

/*N*/ DBG_NAME(OutlinerView)


/*N*/ OutlinerView::OutlinerView( Outliner* pOut, Window* pWin )
/*N*/ {
/*N*/   DBG_CTOR( OutlinerView, 0 );
/*N*/
/*N*/   pOwner                      = pOut;
/*N*/   bDDCursorVisible            = FALSE;
/*N*/   bInDragMode                 = FALSE;
/*N*/   nDDScrollLRBorderWidthWin   = 0;
/*N*/   nDDScrollTBBorderWidthWin   = 0;
/*N*/   pHorTabArrDoc               = 0;
/*N*/
/*N*/   pEditView = new EditView( pOut->pEditEngine, pWin );
/*N*/   pEditView->SetSelectionMode( EE_SELMODE_TXTONLY );
/*N*/ }

/*N*/ OutlinerView::~OutlinerView()
/*N*/ {
/*N*/   DBG_DTOR(OutlinerView,0);
/*N*/   delete pEditView;
/*N*/ }













// Berechnet, ueber welchem Absatz eingefuegt werden muss











// MT: Name sollte mal geaendert werden!







/*N*/ Rectangle OutlinerView::GetVisArea() const
/*N*/ {
/*N*/   DBG_CHKTHIS(OutlinerView,0);
/*N*/   return pEditView->GetVisArea();
/*N*/ }



// MT 05/00: Wofuer dies ImpXXXScroll, sollte das nicht die EditEngine machen???


























/*N*/ void OutlinerView::Cut()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

/*N*/ void OutlinerView::Paste()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }




// =====================================================================
// ======================   Einfache Durchreicher =======================
// ======================================================================





/*N*/ void OutlinerView::SetSelection( const ESelection& rSel )
/*N*/ {
/*N*/   DBG_CHKTHIS(OutlinerView,0);
/*N*/   pEditView->SetSelection( rSel );
/*N*/ }


/*N*/ Window* OutlinerView::GetWindow() const
/*N*/ {
/*N*/   DBG_CHKTHIS(OutlinerView,0);
/*N*/   return pEditView->GetWindow();
/*N*/ }




/*N*/ Rectangle OutlinerView::GetOutputArea() const
/*N*/ {
/*N*/   DBG_CHKTHIS(OutlinerView,0);
/*N*/   return pEditView->GetOutputArea();
/*N*/ }

/*N*/ ESelection OutlinerView::GetSelection()
/*N*/ {
/*N*/   DBG_CHKTHIS(OutlinerView,0);
/*N*/   return pEditView->GetSelection();
/*N*/ }


















/*N*/ void OutlinerView::Copy()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }





















#ifndef SVX_LIGHT
#endif





}
