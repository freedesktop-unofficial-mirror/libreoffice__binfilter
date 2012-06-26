/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#ifdef _MSC_VER
#pragma hdrstop
#endif

#define _SOLAR__PRIVATE 1

#include <vcl/window.hxx>

#include <impedit.hxx>
#include <editeng.hxx>
#include <editview.hxx>

#include "itemdata.hxx"

#include <editeng.hrc>
#include <helpid.hrc>

#include <com/sun/star/beans/PropertyValues.hdl>

namespace binfilter {

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::linguistic2;


/*N*/ DBG_NAME( EditView )

// From SW => Create common method

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
/*N*/   EditSelection aNewSelection( PIMPEE->ConvertSelection( rESel.nStartPara, rESel.nStartPos, rESel.nEndPara, rESel.nEndPos ) );
/*N*/
/*N*/   // Selektion darf nicht bei einem unsichtbaren Absatz Starten/Enden:
/*N*/   PIMPEE->FindParaPortion( aNewSelection.Min().GetNode() ); // WaE cleanup: left in for potential side effects
/*N*/   PIMPEE->FindParaPortion( aNewSelection.Max().GetNode() ); // WaE cleanup: left in for potential side effects
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

/*N*/ const Rectangle& EditView::GetVisArea() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditView, 0 );
/*N*/   // Change return value to Rectangle in next incompatible build !!!
/*N*/   static Rectangle aRect;
/*N*/   aRect = pImpEditView->GetVisDocArea();
/*N*/   return aRect;
/*N*/ }

/*N*/ const Rectangle& EditView::GetOutputArea() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditView, 0 );
/*N*/   return pImpEditView->GetOutputArea();
/*N*/ }


/*N*/ void EditView::ShowCursor( sal_Bool, sal_Bool )
/*N*/ {
/*N*/ }

/*N*/ void EditView::HideCursor()
/*N*/ {
/*N*/   DBG_CHKTHIS( EditView, 0 );
/*N*/   pImpEditView->GetCursor()->Hide();
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
