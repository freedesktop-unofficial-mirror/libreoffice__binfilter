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

#include <vcl/window.hxx>

#include <impedit.hxx>
#include <editeng.hxx>

#include "itemdata.hxx"

#include <flditem.hxx>

namespace binfilter {


using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::linguistic2;

#define SCRLRANGE   20      // 1/20 der Breite/Hoehe scrollen, wenn im QueryDrop


/*N*/ ImpEditView::~ImpEditView()
/*N*/ {
/*N*/     if ( pOutWin && ( pOutWin->GetCursor() == pCursor ) )
/*N*/       pOutWin->SetCursor( NULL );
/*N*/
/*N*/   delete pCursor;
/*N*/   delete pBackgroundColor;
/*N*/   delete pPointer;
/*N*/ }


/*N*/ void ImpEditView::SetEditSelection( const EditSelection& rEditSelection )
/*N*/ {
/*N*/   // #100856# set state before notification
/*N*/     aEditSelection = rEditSelection;
/*N*/ }


/*N*/ void ImpEditView::DrawSelection( EditSelection aTmpSel, Region* pRegion )
/*N*/ {
/*N*/   // Vor dem Zeichnen der Selektion muss sichergestellt werden,
/*N*/   // das der Fensterinhalt komplett gueltig ist!
/*N*/   // Muss hier stehen, damit auf jeden Fall weg wenn lerr, nicht spaeter
/*N*/   // zwei Paint-Events!
/*N*/   // 19.10: Muss sogar vor Abfrage von bUpdate, falls nach Invalidate
/*N*/   // noch Paints in der Queue, aber jemand schaltet den UpdateMode um!
/*N*/
/*N*/   // pRegion: Wenn nicht NULL, dann nur Region berechnen.
/*N*/   PolyPolygon* pPolyPoly = NULL;
/*N*/   if ( pRegion )
/*?*/       pPolyPoly = new PolyPolygon;
/*N*/
/*N*/   sal_Bool bClipRegion = pOutWin->IsClipRegion();
/*N*/   Region aOldRegion = pOutWin->GetClipRegion();
/*N*/
/*N*/   if ( !pRegion )
/*N*/   {
/*N*/       if ( pEditEngine->pImpEditEngine->GetUpdateMode() == sal_False )
/*N*/           return;
/*N*/       if ( pEditEngine->pImpEditEngine->IsInUndo() )
/*N*/           return;
/*N*/
/*N*/       if ( !aTmpSel.HasRange() )
/*N*/           return;
/*N*/
/*?*/       // aTmpOutArea: Falls OutputArea > Papierbreite und
/*?*/       // Text > Papierbreite ( uebergrosse Felder )
/*?*/       Rectangle aTmpOutArea( aOutArea );
/*?*/       if ( aTmpOutArea.GetWidth() > pEditEngine->pImpEditEngine->GetPaperSize().Width() )
/*?*/           aTmpOutArea.Right() = aTmpOutArea.Left() + pEditEngine->pImpEditEngine->GetPaperSize().Width();
/*?*/       pOutWin->IntersectClipRegion( aTmpOutArea );
/*?*/
/*?*/       if ( pOutWin->GetCursor() )
/*?*/           pOutWin->GetCursor()->Hide();
/*?*/   }
/*?*/
/*?*/   aTmpSel.Adjust( pEditEngine->pImpEditEngine->GetEditDoc() );
/*?*/
/*?*/   ContentNode* pStartNode = aTmpSel.Min().GetNode();
/*?*/   ContentNode* pEndNode = aTmpSel.Max().GetNode();
/*?*/   sal_uInt16 nStartPara = pEditEngine->pImpEditEngine->GetEditDoc().GetPos( pStartNode );
/*?*/   sal_uInt16 nEndPara = pEditEngine->pImpEditEngine->GetEditDoc().GetPos( pEndNode );
/*?*/   // ueber die Absaetze iterieren....
/*?*/   for ( sal_uInt16 nPara = nStartPara; nPara <= nEndPara; nPara++ )
/*?*/   {
/*?*/       ParaPortion* pTmpPortion = pEditEngine->pImpEditEngine->GetParaPortions().SaveGetObject( nPara );
/*?*/       DBG_ASSERT( pTmpPortion, "Portion in Selektion nicht gefunden!" );
/*?*/       DBG_ASSERT( !pTmpPortion->IsInvalid(), "Portion in Selektion nicht formatiert!" );
/*?*/
/*?*/       if ( !pTmpPortion->IsVisible() || pTmpPortion->IsInvalid() )
/*?*/           continue;
/*?*/
/*?*/       long nParaStart = pEditEngine->pImpEditEngine->GetParaPortions().GetYOffset( pTmpPortion );
/*?*/       if ( ( nParaStart + pTmpPortion->GetHeight() ) < GetVisDocTop() )
/*?*/           continue;
/*?*/       if ( nParaStart > GetVisDocBottom() )
/*?*/           break;
/*?*/   }
/*?*/
/*?*/   if ( pRegion )
/*?*/   {
/*?*/       *pRegion = Region( *pPolyPoly );
/*?*/       delete pPolyPoly;
/*?*/   }
/*?*/   else
/*?*/   {
/*?*/       if ( pOutWin->GetCursor() )
/*?*/           pOutWin->GetCursor()->Show();
/*?*/
/*?*/       if ( bClipRegion )
/*?*/           pOutWin->SetClipRegion( aOldRegion );
/*?*/       else
/*?*/           pOutWin->SetClipRegion();
/*?*/   }
/*N*/ }



/*N*/ BOOL ImpEditView::IsVertical() const
/*N*/ {
/*N*/   return pEditEngine->pImpEditEngine->IsVertical();
/*N*/ }

/*N*/ Rectangle ImpEditView::GetVisDocArea() const
/*N*/ {
/*N*/   return Rectangle( GetVisDocLeft(), GetVisDocTop(), GetVisDocRight(), GetVisDocBottom() );
/*N*/ }

/*N*/ Point ImpEditView::GetDocPos( const Point& rWindowPos ) const
/*N*/ {
/*N*/   // Fensterposition => Dokumentposition
/*N*/   Point aPoint;
/*N*/
/*N*/   if ( !pEditEngine->pImpEditEngine->IsVertical() )
/*N*/   {
/*N*/       aPoint.X() = rWindowPos.X() - aOutArea.Left() + GetVisDocLeft();
/*N*/       aPoint.Y() = rWindowPos.Y() - aOutArea.Top() + GetVisDocTop();
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       aPoint.X() = rWindowPos.Y() - aOutArea.Top() + GetVisDocLeft();
/*?*/       aPoint.Y() = aOutArea.Right() - rWindowPos.X() + GetVisDocTop();
/*N*/   }
/*N*/
/*N*/   return aPoint;
/*N*/ }

/*N*/ Point ImpEditView::GetWindowPos( const Point& rDocPos ) const
/*N*/ {
/*N*/   // Dokumentposition => Fensterposition
/*N*/   Point aPoint;
/*N*/
/*N*/   if ( !pEditEngine->pImpEditEngine->IsVertical() )
/*N*/   {
/*N*/       aPoint.X() = rDocPos.X() + aOutArea.Left() - GetVisDocLeft();
/*N*/       aPoint.Y() = rDocPos.Y() + aOutArea.Top() - GetVisDocTop();
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       aPoint.X() = aOutArea.Right() - rDocPos.Y() + GetVisDocTop();
/*?*/       aPoint.Y() = rDocPos.X() + aOutArea.Top() - GetVisDocLeft();
/*N*/   }
/*N*/
/*N*/   return aPoint;
/*N*/ }

/*N*/ Rectangle ImpEditView::GetWindowPos( const Rectangle& rDocRect ) const
/*N*/ {
/*N*/   // Dokumentposition => Fensterposition
/*N*/   Point aPos( GetWindowPos( rDocRect.TopLeft() ) );
/*N*/   Size aSz = rDocRect.GetSize();
/*N*/   Rectangle aRect;
/*N*/   if ( !pEditEngine->pImpEditEngine->IsVertical() )
/*N*/   {
/*N*/       aRect = Rectangle( aPos, aSz );
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       Point aNewPos( aPos.X()-aSz.Height(), aPos.Y() );
/*?*/       aRect = Rectangle( aNewPos, Size( aSz.Height(), aSz.Width() ) );
/*N*/   }
/*N*/   return aRect;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
