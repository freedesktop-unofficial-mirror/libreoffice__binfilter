/*************************************************************************
 *
 *  $RCSfile: svx_impedit.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:26 $
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

#include <eeng_pch.hxx>

#pragma hdrstop


#include <impedit.hxx>
#include <editeng.hxx>
#include <editview.hxx>

#ifndef _TL_POLY_HXX
#include <tools/poly.hxx>
#endif

#ifndef _UNO_LINGU_HXX
#include <unolingu.hxx>
#endif
#ifndef _SFX_SFXUNO_HXX
#include <bf_sfx2/sfxuno.hxx>
#endif
#ifndef _COM_SUN_STAR_LINGUISTIC2_XDICTIONARYENTRY_HPP_
#include <com/sun/star/linguistic2/XDictionaryEntry.hpp>
#endif
#ifndef _COM_SUN_STAR_LINGUISTIC2_DICTIONARYTYPE_HPP_
#include <com/sun/star/linguistic2/DictionaryType.hpp>
#endif
#ifndef _COM_SUN_STAR_LINGUISTIC2_DICTIONARYEVENT_HPP_
#include <com/sun/star/linguistic2/DictionaryEvent.hpp>
#endif
#ifndef _COM_SUN_STAR_LINGUISTIC2_XDICTIONARYEVENTLISTENER_HPP_
#include <com/sun/star/linguistic2/XDictionaryEventListener.hpp>
#endif
#ifndef _COM_SUN_STAR_LINGUISTIC2_DICTIONARYEVENTFLAGS_HPP_
#include <com/sun/star/linguistic2/DictionaryEventFlags.hpp>
#endif
#ifndef _COM_SUN_STAR_LINGUISTIC2_XDICTIONARY_HPP_
#include <com/sun/star/linguistic2/XDictionary.hpp>
#endif
#ifndef _COM_SUN_STAR_LINGUISTIC2_XDICTIONARY1_HPP_
#include <com/sun/star/linguistic2/XDictionary1.hpp>
#endif

#ifndef _COM_SUN_STAR_DATATRANSFER_DND_DNDCONSTANS_HPP_
#include <com/sun/star/datatransfer/dnd/DNDConstants.hpp>
#endif

#ifndef _COM_SUN_STAR_DATATRANSFER_DND_XDRAGGESTURERECOGNIZER_HPP_
#include <com/sun/star/datatransfer/dnd/XDragGestureRecognizer.hpp>
#endif

#ifndef _COM_SUN_STAR_DATATRANSFER_DND_XDROPTARGET_HPP_
#include <com/sun/star/datatransfer/dnd/XDropTarget.hpp>
#endif

#ifndef _COM_SUN_STAR_DATATRANSFER_CLIPBOARD_XCLIPBOARD_HPP_
#include <com/sun/star/datatransfer/clipboard/XClipboard.hpp>
#endif

#ifndef _COM_SUN_STAR_DATATRANSFER_CLIPBOARD_XFLUSHABLECLIPBOARD_HPP_
#include <com/sun/star/datatransfer/clipboard/XFlushableClipboard.hpp>
#endif

#include <vos/mutex.hxx>

#include <flditem.hxx>
#include <svtools/intitem.hxx>
#include <svtools/transfer.hxx>

#include <sot/exchange.hxx>
#include <sot/formats.hxx>
namespace binfilter {


using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::linguistic2;

#define SCRLRANGE   20      // 1/20 der Breite/Hoehe scrollen, wenn im QueryDrop

//STRIP001 inline void lcl_AllignToPixel( Point& rPoint, OutputDevice* pOutDev, short nDiffX, short nDiffY )
//STRIP001 {
//STRIP001  rPoint = pOutDev->LogicToPixel( rPoint );
//STRIP001
//STRIP001  if ( nDiffX )
//STRIP001      rPoint.X() += nDiffX;
//STRIP001  if ( nDiffY )
//STRIP001      rPoint.Y() += nDiffY;
//STRIP001
//STRIP001  rPoint = pOutDev->PixelToLogic( rPoint );
//STRIP001 }

// ----------------------------------------------------------------------
//  class ImpEditView
//  ----------------------------------------------------------------------
/*N*/ ImpEditView::ImpEditView( EditView* pView, EditEngine* pEng, Window* pWindow ) :
/*N*/   aOutArea( Point(), pEng->GetPaperSize() )
/*N*/ {
/*N*/     pEditView           = pView;
/*N*/   pEditEngine         = pEng;
/*N*/   pOutWin             = pWindow;
/*N*/   pPointer            = NULL;
/*N*/   pBackgroundColor    = NULL;
/*N*/   nScrollDiffX        = 0;
/*N*/     nExtraCursorFlags   = 0;
/*N*/     nCursorBidiLevel    = CURSOR_BIDILEVEL_DONTKNOW;
/*N*/   pCursor             = NULL;
//STRIP001      pDragAndDropInfo    = NULL;
/*N*/   bReadOnly           = sal_False;
/*N*/     bClickedInSelection = sal_False;
/*N*/   eSelectionMode      = EE_SELMODE_TXTONLY;
/*N*/   eAnchorMode         = ANCHOR_TOP_LEFT;
/*N*/   nInvMore            = 1;
/*N*/   nTravelXPos         = TRAVEL_X_DONTKNOW;
/*N*/   nControl            = EV_CNTRL_AUTOSCROLL | EV_CNTRL_ENABLEPASTE;
/*N*/     bActiveDragAndDropListener = FALSE;
/*N*/
/*N*/   aEditSelection.Min() = pEng->pImpEditEngine->GetEditDoc().GetStartPaM();
/*N*/   aEditSelection.Max() = pEng->pImpEditEngine->GetEditDoc().GetEndPaM();
/*N*/ }

/*N*/ ImpEditView::~ImpEditView()
/*N*/ {
/*N*/     RemoveDragAndDropListeners();
/*N*/
/*N*/     if ( pOutWin && ( pOutWin->GetCursor() == pCursor ) )
/*N*/       pOutWin->SetCursor( NULL );
/*N*/
/*N*/   delete pCursor;
/*N*/   delete pBackgroundColor;
/*N*/   delete pPointer;
//STRIP001  delete pDragAndDropInfo;
/*N*/ }

//STRIP001 void ImpEditView::SetBackgroundColor( const Color& rColor )
//STRIP001 {
//STRIP001  delete pBackgroundColor;
//STRIP001  pBackgroundColor = new Color( rColor );
//STRIP001 }

/*N*/ void ImpEditView::SetEditSelection( const EditSelection& rEditSelection )
/*N*/ {
/*N*/   // #100856# set state before notification
/*N*/     aEditSelection = rEditSelection;
/*N*/
/*N*/     if ( pEditEngine->pImpEditEngine->GetNotifyHdl().IsSet() )
/*N*/     {
/*?*/         DBG_BF_ASSERT(0, "STRIP"); //STRIP001 EENotify aNotify( EE_NOTIFY_TEXTVIEWSELECTIONCHANGED );
//STRIP001 /*?*/         aNotify.pEditEngine = pEditEngine;
//STRIP001 /*?*/         aNotify.pEditView = GetEditViewPtr();
//STRIP001 /*?*/         pEditEngine->pImpEditEngine->CallNotify( aNotify );
/*N*/     }
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
/*?*/   DBG_ASSERT( !pEditEngine->pImpEditEngine->aIdleFormatter.IsActive(), "DrawSelection: Not formatted!" );
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
/*?*/
/*?*/       sal_uInt16 nStartLine = 0;
/*?*/       sal_uInt16 nEndLine = pTmpPortion->GetLines().Count() -1;
/*?*/       if ( nPara == nStartPara )
/*?*/       {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     nStartLine = pTmpPortion->GetLines().FindLine( aTmpSel.Min().GetIndex(), sal_False );
/*?*/       if ( nPara == nEndPara )
/*?*/       {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     nEndLine = pTmpPortion->GetLines().FindLine( aTmpSel.Max().GetIndex(), sal_True );
/*?*/
/*?*/       // ueber die Zeilen iterieren....
/*?*/       for ( sal_uInt16 nLine = nStartLine; nLine <= nEndLine; nLine++ )
/*?*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 EditLine* pLine = pTmpPortion->GetLines().GetObject( nLine );
//STRIP001 /*?*/            DBG_ASSERT( pLine, "Zeile nicht gefunden: DrawSelection()" );
//STRIP001 /*?*/
//STRIP001 /*?*/             BOOL bPartOfLine = FALSE;
//STRIP001 /*?*/            sal_uInt16 nStartIndex = pLine->GetStart();
//STRIP001 /*?*/            sal_uInt16 nEndIndex = pLine->GetEnd();
//STRIP001 /*?*/            if ( ( nPara == nStartPara ) && ( nLine == nStartLine ) && ( nStartIndex != aTmpSel.Min().GetIndex() ) )
//STRIP001 /*?*/             {
//STRIP001 /*?*/                nStartIndex = aTmpSel.Min().GetIndex();
//STRIP001 /*?*/                 bPartOfLine = TRUE;
//STRIP001 /*?*/             }
//STRIP001 /*?*/            if ( ( nPara == nEndPara ) && ( nLine == nEndLine ) && ( nEndIndex != aTmpSel.Max().GetIndex() ) )
//STRIP001 /*?*/             {
//STRIP001 /*?*/                nEndIndex = aTmpSel.Max().GetIndex();
//STRIP001 /*?*/                 bPartOfLine = TRUE;
//STRIP001 /*?*/             }
//STRIP001 /*?*/
//STRIP001 /*?*/            // Kann passieren, wenn am Anfang einer umgebrochenen Zeile.
//STRIP001 /*?*/            if ( nEndIndex < nStartIndex )
//STRIP001 /*?*/                nEndIndex = nStartIndex;
//STRIP001 /*?*/
//STRIP001 /*?*/            Rectangle aTmpRec( pEditEngine->pImpEditEngine->GetEditCursor( pTmpPortion, nStartIndex ) );
//STRIP001 /*?*/            Point aTopLeft( aTmpRec.TopLeft() );
//STRIP001 /*?*/            Point aBottomRight( aTmpRec.BottomRight() );
//STRIP001 /*?*/
//STRIP001 /*?*/             aTopLeft.Y() += nParaStart;
//STRIP001 /*?*/            aBottomRight.Y() += nParaStart;
//STRIP001 /*?*/
//STRIP001 /*?*/             // Nur Painten, wenn im sichtbaren Bereich...
//STRIP001 /*?*/            if ( aTopLeft.Y() > GetVisDocBottom() )
//STRIP001 /*?*/                break;
//STRIP001 /*?*/
//STRIP001 /*?*/             if ( aBottomRight.Y() < GetVisDocTop() )
//STRIP001 /*?*/                 continue;
//STRIP001 /*?*/
//STRIP001 /*?*/             // Now that we have Bidi, the first/last index doesn't have to be the 'most outside' postion
//STRIP001 /*?*/             if ( !bPartOfLine )
//STRIP001 /*?*/             {
//STRIP001 /*?*/                 Range aLineXPosStartEnd = pEditEngine->pImpEditEngine->GetLineXPosStartEnd( pTmpPortion, pLine );
//STRIP001 /*?*/                 aTopLeft.X() = aLineXPosStartEnd.Min();
//STRIP001 /*?*/                 aBottomRight.X() = aLineXPosStartEnd.Max();
//STRIP001 /*?*/                 ImplDrawHighlightRect( pOutWin, aTopLeft, aBottomRight, pPolyPoly );
//STRIP001 /*?*/             }
//STRIP001 /*?*/             else
//STRIP001 /*?*/             {
//STRIP001 /*?*/                 USHORT nTmpStartIndex = nStartIndex;
//STRIP001 /*?*/                 USHORT nWritingDirStart, nTmpEndIndex;
//STRIP001 /*?*/
//STRIP001 /*?*/                 while ( nTmpStartIndex < nEndIndex )
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     pEditEngine->pImpEditEngine->GetRightToLeft( nPara, nTmpStartIndex+1, &nWritingDirStart, &nTmpEndIndex );
//STRIP001 /*?*/                     if ( nTmpEndIndex > nEndIndex )
//STRIP001 /*?*/                         nTmpEndIndex = nEndIndex;
//STRIP001 /*?*/
//STRIP001 /*?*/                     DBG_ASSERT( nTmpEndIndex > nTmpStartIndex, "DrawSelection, Start >= End?" );
//STRIP001 /*?*/
//STRIP001 /*?*/                     long nX1 = pEditEngine->pImpEditEngine->GetXPos( pTmpPortion, pLine, nTmpStartIndex, TRUE );
//STRIP001 /*?*/                     long nX2 = pEditEngine->pImpEditEngine->GetXPos( pTmpPortion, pLine, nTmpEndIndex );
//STRIP001 /*?*/
//STRIP001 /*?*/                     Point aPt1( Min( nX1, nX2 ), aTopLeft.Y() );
//STRIP001 /*?*/                     Point aPt2( Max( nX1, nX2 ), aBottomRight.Y() );
//STRIP001 /*?*/
//STRIP001 /*?*/                     ImplDrawHighlightRect( pOutWin, aPt1, aPt2, pPolyPoly );
//STRIP001 /*?*/
//STRIP001 /*?*/                     nTmpStartIndex = nTmpEndIndex;
//STRIP001 /*?*/                 }
//STRIP001 /*?*/             }
//STRIP001 /*?*/
/*?*/       }
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

//STRIP001 void ImpEditView::ImplDrawHighlightRect( Window* pOutWin, const Point& rDocPosTopLeft, const Point& rDocPosBottomRight, PolyPolygon* pPolyPoly )
//STRIP001 {
//STRIP001  if ( rDocPosTopLeft.X() != rDocPosBottomRight.X() )
//STRIP001  {
//STRIP001      sal_Bool bPixelMode = pOutWin->GetMapMode() == MAP_PIXEL;
//STRIP001
//STRIP001         Point aPnt1( GetWindowPos( rDocPosTopLeft ) );
//STRIP001      Point aPnt2( GetWindowPos( rDocPosBottomRight ) );
//STRIP001
//STRIP001      if ( !IsVertical() )
//STRIP001      {
//STRIP001          lcl_AllignToPixel( aPnt1, pOutWin, +1, 0 );
//STRIP001          lcl_AllignToPixel( aPnt2, pOutWin, 0, ( bPixelMode ? 0 : -1 ) );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          lcl_AllignToPixel( aPnt1, pOutWin, 0, +1 );
//STRIP001          lcl_AllignToPixel( aPnt2, pOutWin, ( bPixelMode ? 0 : +1 ), 0 );
//STRIP001      }
//STRIP001
//STRIP001      Rectangle aRect( aPnt1, aPnt2 );
//STRIP001      if ( pPolyPoly )
//STRIP001      {
//STRIP001          Polygon aTmpPoly( 4 );
//STRIP001          aTmpPoly[0] = aRect.TopLeft();
//STRIP001          aTmpPoly[1] = aRect.TopRight();
//STRIP001          aTmpPoly[2] = aRect.BottomRight();
//STRIP001          aTmpPoly[3] = aRect.BottomLeft();
//STRIP001          pPolyPoly->Insert( aTmpPoly );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pOutWin->HighlightRect( aRect );
//STRIP001      }
//STRIP001  }
//STRIP001 }


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


//STRIP001 Region* ImpEditView::CalcSelectedRegion()
//STRIP001 {
//STRIP001  Region* pRegion = new Region;
//STRIP001  DrawSelection( GetEditSelection(), pRegion );
//STRIP001  return pRegion;
//STRIP001 }

/*N*/ void ImpEditView::SetSelectionMode( EESelectionMode   eNewMode )
/*N*/ {
/*N*/   if ( eSelectionMode != eNewMode )
/*N*/   {
/*?*/       DrawSelection();    // 'Wegmalen' ...
/*?*/       eSelectionMode = eNewMode;
/*?*/       DrawSelection();    // und neu zeichnen.
/*N*/   }
/*N*/ }

/*N*/ void ImpEditView::SetOutputArea( const Rectangle& rRec )
/*N*/ {
/*N*/   // sollte besser auf Pixel allignt sein!
/*N*/   Rectangle aNewRec( pOutWin->LogicToPixel( rRec ) );
/*N*/   aNewRec = pOutWin->PixelToLogic( aNewRec );
/*N*/   aOutArea = aNewRec;
/*N*/   if ( aOutArea.Right() < aOutArea.Left() )
/*N*/       aOutArea.Right() = aOutArea.Left();
/*N*/   if ( aOutArea.Bottom() < aOutArea.Top() )
/*N*/       aOutArea.Bottom() = aOutArea.Top();
/*N*/
/*N*/   if ( DoBigScroll() )
/*?*/       SetScrollDiffX( (sal_uInt16)aOutArea.GetWidth() * 3 / 10 );
/*N*/   else
/*N*/       SetScrollDiffX( (sal_uInt16)aOutArea.GetWidth() * 2 / 10 );
/*N*/ }

//STRIP001 void ImpEditView::ResetOutputArea( const Rectangle& rRec )
//STRIP001 {
//STRIP001  Rectangle aCurArea( aOutArea );
//STRIP001  SetOutputArea( rRec );
//STRIP001  // Umliegende Bereiche invalidieren, wenn UpdateMode der Engine auf sal_True
//STRIP001  if ( !aCurArea.IsEmpty() && pEditEngine->pImpEditEngine->GetUpdateMode() )
//STRIP001  {
//STRIP001      long nMore = 0;
//STRIP001      if ( DoInvalidateMore() )
//STRIP001          nMore = GetWindow()->PixelToLogic( Size( nInvMore, 0 ) ).Width();
//STRIP001      if ( aCurArea.Left() < aOutArea.Left() )
//STRIP001      {
//STRIP001          Rectangle aRect( aCurArea.TopLeft(),
//STRIP001              Size( aOutArea.Left()-aCurArea.Left(), aCurArea.GetHeight() ) );
//STRIP001          if ( nMore )
//STRIP001          {
//STRIP001              aRect.Left() -= nMore;
//STRIP001              aRect.Top() -= nMore;
//STRIP001              aRect.Bottom() += nMore;
//STRIP001          }
//STRIP001          GetWindow()->Invalidate( aRect );
//STRIP001      }
//STRIP001      if ( aCurArea.Right() > aOutArea.Right() )
//STRIP001      {
//STRIP001          long nW = aCurArea.Right() - aOutArea.Right();
//STRIP001          Point aPos( aCurArea.TopRight() );
//STRIP001          aPos.X() -= nW;
//STRIP001          Rectangle aRect( aPos, Size( nW, aCurArea.GetHeight() ) );
//STRIP001          if ( nMore )
//STRIP001          {
//STRIP001              aRect.Right() += nMore;
//STRIP001              aRect.Top() -= nMore;
//STRIP001              aRect.Bottom() += nMore;
//STRIP001          }
//STRIP001          GetWindow()->Invalidate( aRect );
//STRIP001      }
//STRIP001      if ( aCurArea.Top() < aOutArea.Top() )
//STRIP001      {
//STRIP001          Rectangle aRect( aCurArea.TopLeft(), Size( aCurArea.GetWidth(), aOutArea.Top() - aCurArea.Top() ) );
//STRIP001          if ( nMore )
//STRIP001          {
//STRIP001              aRect.Top() -= nMore;
//STRIP001              aRect.Left() -= nMore;
//STRIP001              aRect.Right() += nMore;
//STRIP001          }
//STRIP001          GetWindow()->Invalidate( aRect );
//STRIP001      }
//STRIP001      if ( aCurArea.Bottom() > aOutArea.Bottom() )
//STRIP001      {
//STRIP001          long nH = aCurArea.Bottom() - aOutArea.Bottom();
//STRIP001          Point aPos( aCurArea.BottomLeft() );
//STRIP001          aPos.Y() -= nH;
//STRIP001          Rectangle aRect( aPos, Size( aCurArea.GetWidth(), nH ) );
//STRIP001          if ( nMore )
//STRIP001          {
//STRIP001              aRect.Bottom() += nMore;
//STRIP001              aRect.Left() -= nMore;
//STRIP001              aRect.Right() += nMore;
//STRIP001          }
//STRIP001
//STRIP001          GetWindow()->Invalidate( aRect );
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void ImpEditView::RecalcOutputArea()
//STRIP001 {
//STRIP001  Rectangle aOldArea( aOutArea );
//STRIP001  Point aNewTopLeft( aOutArea.TopLeft() );
//STRIP001  Size aNewSz( aOutArea.GetSize() );
//STRIP001
//STRIP001  // X:
//STRIP001  if ( DoAutoWidth() )
//STRIP001  {
//STRIP001      if ( pEditEngine->pImpEditEngine->GetStatus().AutoPageWidth() )
//STRIP001          aNewSz.Width() = pEditEngine->pImpEditEngine->GetPaperSize().Width();
//STRIP001      switch ( eAnchorMode )
//STRIP001      {
//STRIP001          case ANCHOR_TOP_LEFT:
//STRIP001          case ANCHOR_VCENTER_LEFT:
//STRIP001          case ANCHOR_BOTTOM_LEFT:
//STRIP001          {
//STRIP001              aNewTopLeft.X() = aAnchorPoint.X();
//STRIP001          }
//STRIP001          break;
//STRIP001          case ANCHOR_TOP_HCENTER:
//STRIP001          case ANCHOR_VCENTER_HCENTER:
//STRIP001          case ANCHOR_BOTTOM_HCENTER:
//STRIP001          {
//STRIP001              aNewTopLeft.X() = aAnchorPoint.X() - aNewSz.Width() / 2;
//STRIP001          }
//STRIP001          break;
//STRIP001          case ANCHOR_TOP_RIGHT:
//STRIP001          case ANCHOR_VCENTER_RIGHT:
//STRIP001          case ANCHOR_BOTTOM_RIGHT:
//STRIP001          {
//STRIP001              aNewTopLeft.X() = aAnchorPoint.X() - aNewSz.Width() - 1;
//STRIP001          }
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Y:
//STRIP001  if ( DoAutoHeight() )
//STRIP001  {
//STRIP001      if ( pEditEngine->pImpEditEngine->GetStatus().AutoPageHeight() )
//STRIP001          aNewSz.Height() = pEditEngine->pImpEditEngine->GetPaperSize().Height();
//STRIP001      switch ( eAnchorMode )
//STRIP001      {
//STRIP001          case ANCHOR_TOP_LEFT:
//STRIP001          case ANCHOR_TOP_HCENTER:
//STRIP001          case ANCHOR_TOP_RIGHT:
//STRIP001          {
//STRIP001              aNewTopLeft.Y() = aAnchorPoint.Y();
//STRIP001          }
//STRIP001          break;
//STRIP001          case ANCHOR_VCENTER_LEFT:
//STRIP001          case ANCHOR_VCENTER_HCENTER:
//STRIP001          case ANCHOR_VCENTER_RIGHT:
//STRIP001          {
//STRIP001              aNewTopLeft.Y() = aAnchorPoint.Y() - aNewSz.Height() / 2;
//STRIP001          }
//STRIP001          break;
//STRIP001          case ANCHOR_BOTTOM_LEFT:
//STRIP001          case ANCHOR_BOTTOM_HCENTER:
//STRIP001          case ANCHOR_BOTTOM_RIGHT:
//STRIP001          {
//STRIP001              aNewTopLeft.Y() = aAnchorPoint.Y() - aNewSz.Height() - 1;
//STRIP001          }
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001  ResetOutputArea( Rectangle( aNewTopLeft, aNewSz ) );
//STRIP001 }

//STRIP001 void ImpEditView::SetAnchorMode( EVAnchorMode eMode )
//STRIP001 {
//STRIP001  eAnchorMode = eMode;
//STRIP001  CalcAnchorPoint();
//STRIP001 }

/*N*/ void ImpEditView::CalcAnchorPoint()
/*N*/ {
/*N*/   // GetHeight() und GetWidth() -1, da Rectangle-Berechnung nicht erwuenscht.
/*N*/
/*N*/   // X:
/*N*/   switch ( eAnchorMode )
/*N*/   {
/*N*/       case ANCHOR_TOP_LEFT:
/*N*/       case ANCHOR_VCENTER_LEFT:
/*N*/       case ANCHOR_BOTTOM_LEFT:
/*N*/       {
/*N*/           aAnchorPoint.X() = aOutArea.Left();
/*N*/       }
/*N*/       break;
/*N*/       case ANCHOR_TOP_HCENTER:
/*N*/       case ANCHOR_VCENTER_HCENTER:
/*N*/       case ANCHOR_BOTTOM_HCENTER:
/*N*/       {
/*?*/           aAnchorPoint.X() = aOutArea.Left() + (aOutArea.GetWidth()-1) / 2;
/*N*/       }
/*N*/       break;
/*N*/       case ANCHOR_TOP_RIGHT:
/*N*/       case ANCHOR_VCENTER_RIGHT:
/*N*/       case ANCHOR_BOTTOM_RIGHT:
/*N*/       {
/*?*/           aAnchorPoint.X() = aOutArea.Right();
/*N*/       }
/*N*/       break;
/*N*/   }
/*N*/
/*N*/   // Y:
/*N*/   switch ( eAnchorMode )
/*N*/   {
/*N*/       case ANCHOR_TOP_LEFT:
/*N*/       case ANCHOR_TOP_HCENTER:
/*N*/       case ANCHOR_TOP_RIGHT:
/*N*/       {
/*N*/           aAnchorPoint.Y() = aOutArea.Top();
/*N*/       }
/*N*/       break;
/*N*/       case ANCHOR_VCENTER_LEFT:
/*N*/       case ANCHOR_VCENTER_HCENTER:
/*N*/       case ANCHOR_VCENTER_RIGHT:
/*N*/       {
/*?*/           aAnchorPoint.Y() = aOutArea.Top() + (aOutArea.GetHeight()-1) / 2;
/*N*/       }
/*N*/       break;
/*N*/       case ANCHOR_BOTTOM_LEFT:
/*N*/       case ANCHOR_BOTTOM_HCENTER:
/*N*/       case ANCHOR_BOTTOM_RIGHT:
/*N*/       {
/*?*/           aAnchorPoint.Y() = aOutArea.Bottom() - 1;
/*N*/       }
/*N*/       break;
/*N*/   }
/*N*/ }

/*N*/ void ImpEditView::ShowCursor( sal_Bool bGotoCursor, sal_Bool bForceVisCursor, USHORT nShowCursorFlags )
/*N*/ {
/*N*/   // Kein ShowCursor bei einer leeren View...
/*N*/   if ( ( aOutArea.Left() >= aOutArea.Right() ) && ( aOutArea.Top() >= aOutArea.Bottom() ) )
/*N*/       return;
/*N*/
//STRIP001 /*?*/    pEditEngine->pImpEditEngine->CheckIdleFormatter();
//STRIP001 /*?*/    if ( !pEditEngine->pImpEditEngine->IsFormatted() )
//STRIP001 /*?*/        pEditEngine->pImpEditEngine->FormatDoc();
//STRIP001 /*?*/
//STRIP001 /*?*/    // Aus irgendwelchen Gruenden lande ich waehrend der Formatierung hier,
//STRIP001 /*?*/    // wenn sich der Outiner im Paint initialisiert, weil kein SetPool();
//STRIP001 /*?*/    if ( pEditEngine->pImpEditEngine->IsFormatting() )
//STRIP001 /*?*/        return;
//STRIP001 /*?*/    if ( pEditEngine->pImpEditEngine->GetUpdateMode() == sal_False )
//STRIP001 /*?*/        return;
//STRIP001 /*?*/    if ( pEditEngine->pImpEditEngine->IsInUndo() )
//STRIP001 /*?*/        return;
//STRIP001 /*?*/
//STRIP001 /*?*/    if ( pOutWin->GetCursor() != GetCursor() )
//STRIP001 /*?*/        pOutWin->SetCursor( GetCursor() );
//STRIP001 /*?*/
//STRIP001 /*?*/    EditPaM aPaM( aEditSelection.Max() );
//STRIP001 /*?*/
//STRIP001 /*?*/     USHORT nTextPortionStart = 0;
//STRIP001 /*?*/     USHORT nPara = pEditEngine->pImpEditEngine->aEditDoc.GetPos( aPaM.GetNode() );
//STRIP001 /*?*/     ParaPortion* pParaPortion = pEditEngine->pImpEditEngine->GetParaPortions().GetObject( nPara );
//STRIP001 /*?*/
//STRIP001 /*?*/     nShowCursorFlags |= nExtraCursorFlags;
//STRIP001 /*?*/
//STRIP001 /*?*/     nShowCursorFlags |= GETCRSR_TXTONLY;
//STRIP001 /*?*/
//STRIP001 /*?*/     // Use CursorBidiLevel 0/1 in meaning of
//STRIP001 /*?*/     // 0: prefer portion end, normal mode
//STRIP001 /*?*/     // 1: prefer portion start
//STRIP001 /*?*/
//STRIP001 /*?*/     if ( ( GetCursorBidiLevel() != CURSOR_BIDILEVEL_DONTKNOW ) && GetCursorBidiLevel() )
//STRIP001 /*?*/     {
//STRIP001 /*?*/         nShowCursorFlags |= GETCRSR_PREFERPORTIONSTART;
//STRIP001 /*?*/     }
//STRIP001 /*?*/
//STRIP001 /*?*/     Rectangle aEditCursor = pEditEngine->pImpEditEngine->PaMtoEditCursor( aPaM, nShowCursorFlags );
//STRIP001 /*?*/    if ( !IsInsertMode() && !aEditSelection.HasRange() )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        if ( aPaM.GetNode()->Len() && ( aPaM.GetIndex() < aPaM.GetNode()->Len() ) )
//STRIP001 /*?*/        {
//STRIP001 /*?*/             // If we are behind a portion, and the next portion has other direction, we must change position...
//STRIP001 /*?*/            aEditCursor.Left() = aEditCursor.Right() = pEditEngine->pImpEditEngine->PaMtoEditCursor( aPaM, GETCRSR_TXTONLY|GETCRSR_PREFERPORTIONSTART ).Left();
//STRIP001 /*?*/
//STRIP001 /*?*/             USHORT nTextPortion = pParaPortion->GetTextPortions().FindPortion( aPaM.GetIndex(), nTextPortionStart, TRUE );
//STRIP001 /*?*/             TextPortion* pTextPortion = pParaPortion->GetTextPortions().GetObject( nTextPortion );
//STRIP001 /*?*/             if ( pTextPortion->GetKind() == PORTIONKIND_TAB )
//STRIP001 /*?*/             {
//STRIP001 /*?*/                aEditCursor.Right() += pTextPortion->GetSize().Width();
//STRIP001 /*?*/             }
//STRIP001 /*?*/             else
//STRIP001 /*?*/             {
//STRIP001 /*?*/                 EditPaM aNext = pEditEngine->pImpEditEngine->CursorRight( aPaM, (USHORT)i18n::CharacterIteratorMode::SKIPCELL );
//STRIP001 /*?*/                Rectangle aTmpRect = pEditEngine->pImpEditEngine->PaMtoEditCursor( aNext, GETCRSR_TXTONLY );
//STRIP001 /*?*/                 if ( aTmpRect.Top() != aEditCursor.Top() )
//STRIP001 /*?*/                     aTmpRect = pEditEngine->pImpEditEngine->PaMtoEditCursor( aNext, GETCRSR_TXTONLY|GETCRSR_ENDOFLINE );
//STRIP001 /*?*/                aEditCursor.Right() = aTmpRect.Left();
//STRIP001 /*?*/             }
//STRIP001 /*?*/        }
//STRIP001 /*?*/    }
//STRIP001 /*?*/    long nMaxHeight = !IsVertical() ? aOutArea.GetHeight() : aOutArea.GetWidth();
//STRIP001 /*?*/    if ( aEditCursor.GetHeight() > nMaxHeight )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        aEditCursor.Bottom() = aEditCursor.Top() + nMaxHeight - 1;
//STRIP001 /*?*/    }
//STRIP001 /*?*/    if ( bGotoCursor  ) // && (!pEditEngine->pImpEditEngine->GetStatus().AutoPageSize() ) )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        // pruefen, ob scrollen notwendig...
//STRIP001 /*?*/        // wenn scrollen, dann Update() und Scroll() !
//STRIP001 /*?*/        long nDocDiffX = 0;
//STRIP001 /*?*/        long nDocDiffY = 0;
//STRIP001 /*?*/
//STRIP001 /*?*/        Rectangle aTmpVisArea( GetVisDocArea() );
//STRIP001 /*?*/        // aTmpOutArea: Falls OutputArea > Papierbreite und
//STRIP001 /*?*/        // Text > Papierbreite ( uebergrosse Felder )
//STRIP001 /*?*/        long nMaxTextWidth = !IsVertical() ? pEditEngine->pImpEditEngine->GetPaperSize().Width() : pEditEngine->pImpEditEngine->GetPaperSize().Height();
//STRIP001 /*?*/        if ( aTmpVisArea.GetWidth() > nMaxTextWidth )
//STRIP001 /*?*/            aTmpVisArea.Right() = aTmpVisArea.Left() + nMaxTextWidth;
//STRIP001 /*?*/
//STRIP001 /*?*/        if ( aEditCursor.Bottom() > aTmpVisArea.Bottom() )
//STRIP001 /*?*/        {   // hochscrollen, hier positiv
//STRIP001 /*?*/            nDocDiffY = aEditCursor.Bottom() - aTmpVisArea.Bottom();
//STRIP001 /*?*/        }
//STRIP001 /*?*/        else if ( aEditCursor.Top() < aTmpVisArea.Top() )
//STRIP001 /*?*/        {   // runterscrollen, negativ
//STRIP001 /*?*/            nDocDiffY = aEditCursor.Top() - aTmpVisArea.Top();
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        if ( aEditCursor.Right() > aTmpVisArea.Right() )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            // linksscrollen, positiv
//STRIP001 /*?*/            nDocDiffX = aEditCursor.Right() - aTmpVisArea.Right();
//STRIP001 /*?*/            // Darfs ein bischen mehr sein?
//STRIP001 /*?*/            if ( aEditCursor.Right() < ( nMaxTextWidth - GetScrollDiffX() ) )
//STRIP001 /*?*/                nDocDiffX += GetScrollDiffX();
//STRIP001 /*?*/            else
//STRIP001 /*?*/            {
//STRIP001 /*?*/                long n = nMaxTextWidth - aEditCursor.Right();
//STRIP001 /*?*/                // Bei einem MapMode != RefMapMode kann der EditCursor auch mal ueber
//STRIP001 /*?*/                // die Papierbreite Wandern!
//STRIP001 /*?*/                nDocDiffX += ( n > 0 ? n : -n );
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
//STRIP001 /*?*/        else if ( aEditCursor.Left() < aTmpVisArea.Left() )
//STRIP001 /*?*/        {   // rechtsscrollen
//STRIP001 /*?*/            // negativ:
//STRIP001 /*?*/            nDocDiffX = aEditCursor.Left() - aTmpVisArea.Left();
//STRIP001 /*?*/            // Darfs ein bischen mehr sein?
//STRIP001 /*?*/            if ( aEditCursor.Left() > ( - (long)GetScrollDiffX() ) )
//STRIP001 /*?*/                nDocDiffX -= GetScrollDiffX();
//STRIP001 /*?*/            else
//STRIP001 /*?*/                nDocDiffX -= aEditCursor.Left();
//STRIP001 /*?*/        }
//STRIP001 /*?*/        if ( aPaM.GetIndex() == 0 )     // braucht Olli fuer den Outliner
//STRIP001 /*?*/        {
//STRIP001 /*?*/            // Aber sicherstellen, dass dadurch der Cursor nicht den
//STRIP001 /*?*/            // sichtbaren bereich verlaesst!
//STRIP001 /*?*/            if ( aEditCursor.Left() < aTmpVisArea.GetWidth() )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                nDocDiffX = -aTmpVisArea.Left();
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        if ( nDocDiffX | nDocDiffY )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            long nDiffX = !IsVertical() ? nDocDiffX : -nDocDiffY;
//STRIP001 /*?*/            long nDiffY = !IsVertical() ? nDocDiffY : nDocDiffX;
//STRIP001 /*?*/
//STRIP001 /*?*/            // Negativ: Zum Anfang bzw. linken Rand
//STRIP001 /*?*/            if ( ( Abs( nDiffY ) > pEditEngine->pImpEditEngine->nOnePixelInRef ) && DoBigScroll() )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                long nH = aOutArea.GetHeight() / 4;
//STRIP001 /*?*/                if ( ( nH > aEditCursor.GetHeight() ) && ( Abs( nDiffY ) < nH ) )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    if ( nDiffY < 0 )
//STRIP001 /*?*/                        nDiffY -= nH;
//STRIP001 /*?*/                    else
//STRIP001 /*?*/                        nDiffY += nH;
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            if ( ( Abs( nDiffX ) > pEditEngine->pImpEditEngine->nOnePixelInRef ) && DoBigScroll() )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                long nW = aOutArea.GetWidth() / 4;
//STRIP001 /*?*/                if ( Abs( nDiffX ) < nW )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    if ( nDiffY < 0 )
//STRIP001 /*?*/                        nDiffY -= nW;
//STRIP001 /*?*/                    else
//STRIP001 /*?*/                        nDiffY += nW;
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            if ( nDiffX )
//STRIP001 /*?*/                pEditEngine->pImpEditEngine->aStatus.GetStatusWord() = pEditEngine->pImpEditEngine->aStatus.GetStatusWord() | EE_STAT_HSCROLL;
//STRIP001 /*?*/            if ( nDiffY )
//STRIP001 /*?*/                pEditEngine->pImpEditEngine->aStatus.GetStatusWord() = pEditEngine->pImpEditEngine->aStatus.GetStatusWord() | EE_STAT_VSCROLL;
//STRIP001 /*?*/            Scroll( -nDiffX, -nDiffY );
//STRIP001 /*?*/            pEditEngine->pImpEditEngine->DelayedCallStatusHdl();
//STRIP001 /*?*/        }
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    // Cursor evtl. etwas stutzen...
//STRIP001 /*?*/    if ( ( aEditCursor.Bottom() > GetVisDocTop() ) &&
//STRIP001 /*?*/         ( aEditCursor.Top() < GetVisDocBottom() ) )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        if ( aEditCursor.Bottom() > GetVisDocBottom() )
//STRIP001 /*?*/            aEditCursor.Bottom() = GetVisDocBottom();
//STRIP001 /*?*/        if ( aEditCursor.Top() < GetVisDocTop() )
//STRIP001 /*?*/            aEditCursor.Top() = GetVisDocTop();
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    long nOnePixel = pOutWin->PixelToLogic( Size( 1, 0 ) ).Width();
//STRIP001 /*?*/
//STRIP001 /*?*/    if ( /* pEditEngine->pImpEditEngine->GetStatus().AutoPageSize() || */
//STRIP001 /*?*/         ( ( aEditCursor.Top() + nOnePixel >= GetVisDocTop() ) &&
//STRIP001 /*?*/         ( aEditCursor.Bottom() - nOnePixel <= GetVisDocBottom() ) &&
//STRIP001 /*?*/         ( aEditCursor.Left() + nOnePixel >= GetVisDocLeft() ) &&
//STRIP001 /*?*/         ( aEditCursor.Right() - nOnePixel <= GetVisDocRight() ) ) )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        Rectangle aCursorRect = GetWindowPos( aEditCursor );
//STRIP001 /*?*/        GetCursor()->SetPos( aCursorRect.TopLeft() );
//STRIP001 /*?*/        Size aCursorSz( aCursorRect.GetSize() );
//STRIP001 /*?*/        // Rectangle is inclusive
//STRIP001 /*?*/        aCursorSz.Width()--;
//STRIP001 /*?*/        aCursorSz.Height()--;
//STRIP001 /*?*/        if ( !aCursorSz.Width() || !aCursorSz.Height() )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            long nCursorSz = pOutWin->GetSettings().GetStyleSettings().GetCursorSize();
//STRIP001 /*?*/            nCursorSz = pOutWin->PixelToLogic( Size( nCursorSz, 0 ) ).Width();
//STRIP001 /*?*/            if ( !aCursorSz.Width() )
//STRIP001 /*?*/                aCursorSz.Width() = nCursorSz;
//STRIP001 /*?*/            if ( !aCursorSz.Height() )
//STRIP001 /*?*/                aCursorSz.Height() = nCursorSz;
//STRIP001 /*?*/        }
//STRIP001 /*?*/        GetCursor()->SetSize( aCursorSz );
//STRIP001 /*?*/
//STRIP001 /*?*/         unsigned char nCursorDir = CURSOR_DIRECTION_NONE;
//STRIP001 /*?*/         if ( IsInsertMode() && !aEditSelection.HasRange() && ( pEditEngine->pImpEditEngine->HasDifferentRTLLevels( aPaM.GetNode() ) ) )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             USHORT nTextPortion = pParaPortion->GetTextPortions().FindPortion( aPaM.GetIndex(), nTextPortionStart, nShowCursorFlags & GETCRSR_PREFERPORTIONSTART ? TRUE : FALSE );
//STRIP001 /*?*/             TextPortion* pTextPortion = pParaPortion->GetTextPortions().GetObject( nTextPortion );
//STRIP001 /*?*/             USHORT nRTLLevel = pTextPortion->GetRightToLeft();
//STRIP001 /*?*/             if ( nRTLLevel%2 )
//STRIP001 /*?*/                 nCursorDir = CURSOR_DIRECTION_RTL;
//STRIP001 /*?*/             else
//STRIP001 /*?*/                 nCursorDir = CURSOR_DIRECTION_LTR;
//STRIP001 /*?*/
//STRIP001 /*?*/         }
//STRIP001 /*?*/         GetCursor()->SetDirection( nCursorDir );
//STRIP001 /*?*/
//STRIP001 /*?*/         if ( bForceVisCursor )
//STRIP001 /*?*/            GetCursor()->Show();
//STRIP001 /*?*/
//STRIP001 /*?*/         // #102936# Call SetInputContext every time, otherwise we may have the wrong font
//STRIP001 /*?*/        // if ( !pEditEngine->pImpEditEngine->mpIMEInfos )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            SvxFont aFont;
//STRIP001 /*?*/            pEditEngine->pImpEditEngine->SeekCursor( aPaM.GetNode(), aPaM.GetIndex()+1, aFont );
//STRIP001 /*?*/            ULONG nContextFlags = INPUTCONTEXT_TEXT|INPUTCONTEXT_EXTTEXTINPUT;
//STRIP001 /*?*/            GetWindow()->SetInputContext( InputContext( aFont, nContextFlags ) );
//STRIP001 /*?*/        }
//STRIP001 /*?*/    }
//STRIP001 /*?*/    else
//STRIP001 /*?*/    {
//STRIP001 /*?*/        pEditEngine->pImpEditEngine->GetStatus().GetStatusWord() = pEditEngine->pImpEditEngine->GetStatus().GetStatusWord() | EE_STAT_CURSOROUT;
//STRIP001 /*?*/        GetCursor()->Hide();
//STRIP001 /*?*/        GetCursor()->SetPos( Point( -1, -1 ) );
//STRIP001 /*?*/        GetCursor()->SetSize( Size( 0, 0 ) );
//STRIP001 /*?*/    }
/*?*/ }

//STRIP001 Pair ImpEditView::Scroll( long ndX, long ndY, BYTE nRangeCheck )
//STRIP001 {
//STRIP001 /*?*/    DBG_ASSERT( pEditEngine->pImpEditEngine->IsFormatted(), "Scroll: Nicht formatiert!" );
//STRIP001 /*?*/    if ( !ndX && !ndY )
//STRIP001 /*?*/        return Range( 0, 0 );
//STRIP001
//STRIP001 /*?*/ #ifdef DBG_UTIL
//STRIP001 /*?*/    Rectangle aR( aOutArea );
//STRIP001 /*?*/    aR = pOutWin->LogicToPixel( aR );
//STRIP001 /*?*/    aR = pOutWin->PixelToLogic( aR );
//STRIP001 /*?*/    DBG_ASSERTWARNING( aR == aOutArea, "OutArea vor Scroll nicht aligned" );
//STRIP001 /*?*/ #endif
//STRIP001 /*?*/
//STRIP001 /*?*/    Rectangle aNewVisArea( GetVisDocArea() );
//STRIP001 /*?*/    Size aPaperSz( pEditEngine->pImpEditEngine->GetPaperSize() );
//STRIP001 /*?*/
//STRIP001 /*?*/    // Vertical:
//STRIP001 /*?*/    if ( !IsVertical() )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        aNewVisArea.Top() -= ndY;
//STRIP001 /*?*/        aNewVisArea.Bottom() -= ndY;
//STRIP001 /*?*/    }
//STRIP001 /*?*/    else
//STRIP001 /*?*/    {
//STRIP001 /*?*/        aNewVisArea.Top() += ndX;
//STRIP001 /*?*/        aNewVisArea.Bottom() += ndX;
//STRIP001 /*?*/    }
//STRIP001 /*?*/    if ( ( nRangeCheck == RGCHK_PAPERSZ1 ) && ( aNewVisArea.Bottom() > (long)pEditEngine->pImpEditEngine->GetTextHeight() ) )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        // GetTextHeight noch optimieren!
//STRIP001 /*?*/        long nDiff = pEditEngine->pImpEditEngine->GetTextHeight() - aNewVisArea.Bottom(); // negativ
//STRIP001 /*?*/        aNewVisArea.Move( 0, nDiff );   // koennte im neg. Bereich landen...
//STRIP001 /*?*/    }
//STRIP001 /*?*/    if ( ( aNewVisArea.Top() < 0 ) && ( nRangeCheck != RGCHK_NONE ) )
//STRIP001 /*?*/        aNewVisArea.Move( 0, -aNewVisArea.Top() );
//STRIP001 /*?*/
//STRIP001 /*?*/    // Horizontal:
//STRIP001 /*?*/    if ( !IsVertical() )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        aNewVisArea.Left() -= ndX;
//STRIP001 /*?*/        aNewVisArea.Right() -= ndX;
//STRIP001 /*?*/    }
//STRIP001 /*?*/    else
//STRIP001 /*?*/    {
//STRIP001 /*?*/        aNewVisArea.Left() -= ndY;
//STRIP001 /*?*/        aNewVisArea.Right() -= ndY;
//STRIP001 /*?*/    }
//STRIP001 /*?*/    if ( ( nRangeCheck == RGCHK_PAPERSZ1 ) && ( aNewVisArea.Right() > (long)pEditEngine->pImpEditEngine->CalcTextWidth( FALSE ) ) )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        long nDiff = pEditEngine->pImpEditEngine->CalcTextWidth( FALSE ) - aNewVisArea.Right();     // negativ
//STRIP001 /*?*/        aNewVisArea.Move( nDiff, 0 );   // koennte im neg. Bereich landen...
//STRIP001 /*?*/    }
//STRIP001 /*?*/    if ( ( aNewVisArea.Left() < 0 ) && ( nRangeCheck != RGCHK_NONE ) )
//STRIP001 /*?*/        aNewVisArea.Move( -aNewVisArea.Left(), 0 );
//STRIP001 /*?*/
//STRIP001 /*?*/    // Die Differenz muss auf Pixel alignt sein (wegen Scroll!)
//STRIP001 /*?*/    long nDiffX = !IsVertical() ? ( GetVisDocLeft() - aNewVisArea.Left() ) : -( GetVisDocTop() - aNewVisArea.Top() );
//STRIP001 /*?*/    long nDiffY = !IsVertical() ? ( GetVisDocTop() - aNewVisArea.Top() ) : ( GetVisDocLeft() - aNewVisArea.Left() );
//STRIP001 /*?*/
//STRIP001 /*?*/    Size aDiffs( nDiffX, nDiffY );
//STRIP001 /*?*/    aDiffs = pOutWin->LogicToPixel( aDiffs );
//STRIP001 /*?*/    aDiffs = pOutWin->PixelToLogic( aDiffs );
//STRIP001 /*?*/
//STRIP001 /*?*/    long nRealDiffX = aDiffs.Width();
//STRIP001 /*?*/    long nRealDiffY = aDiffs.Height();
//STRIP001 /*?*/
//STRIP001 /*?*/
//STRIP001 /*?*/    if ( nRealDiffX || nRealDiffY )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        Cursor* pCrsr = GetCursor();
//STRIP001 /*?*/        sal_Bool bVisCursor = pCrsr->IsVisible();
//STRIP001 /*?*/        pCrsr->Hide();
//STRIP001 /*?*/        pOutWin->Update();
//STRIP001 /*?*/        if ( !IsVertical() )
//STRIP001 /*?*/            aVisDocStartPos.Move( -nRealDiffX, -nRealDiffY );
//STRIP001 /*?*/        else
//STRIP001 /*?*/            aVisDocStartPos.Move( -nRealDiffY, nRealDiffX );
//STRIP001 /*?*/        // Das Move um den allignten Wert ergibt nicht unbedingt ein
//STRIP001 /*?*/        // alligntes Rechteck...
//STRIP001 /*?*/        // MT 11/00: Align VisArea???
//STRIP001 /*?*/        aVisDocStartPos = pOutWin->LogicToPixel( aVisDocStartPos );
//STRIP001 /*?*/        aVisDocStartPos = pOutWin->PixelToLogic( aVisDocStartPos );
//STRIP001 /*?*/        Rectangle aRec( aOutArea );
//STRIP001 /*?*/        pOutWin->Scroll( nRealDiffX, nRealDiffY, aRec, sal_True );
//STRIP001 /*?*/        pOutWin->Update();
//STRIP001 /*?*/        pCrsr->SetPos( pCrsr->GetPos() + Point( nRealDiffX, nRealDiffY ) );
//STRIP001 /*?*/        if ( bVisCursor )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            Rectangle aCursorRec( pCrsr->GetPos(), pCrsr->GetSize() );
//STRIP001 /*?*/            if ( aOutArea.IsInside( aCursorRec ) )
//STRIP001 /*?*/                pCrsr->Show();
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/         if ( pEditEngine->pImpEditEngine->GetNotifyHdl().IsSet() )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             EENotify aNotify( EE_NOTIFY_TEXTVIEWSCROLLED );
//STRIP001 /*?*/             aNotify.pEditEngine = pEditEngine;
//STRIP001 /*?*/             aNotify.pEditView = GetEditViewPtr();
//STRIP001 /*?*/             pEditEngine->pImpEditEngine->CallNotify( aNotify );
//STRIP001 /*?*/         }
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    return Pair( nRealDiffX, nRealDiffY );
//STRIP001 }

/*N*/ sal_Bool ImpEditView::PostKeyEvent( const KeyEvent& rKeyEvent )
/*N*/ {
/*N*/     BOOL bDone = FALSE;
/*N*/
/*N*/   KeyFuncType eFunc = rKeyEvent.GetKeyCode().GetFunction();
/*N*/   if ( eFunc != KEYFUNC_DONTKNOW )
/*N*/   {
/*?*/       switch ( eFunc )
/*?*/       {
/*?*/           case KEYFUNC_CUT:
/*?*/           {
/*?*/               if ( !bReadOnly )
/*?*/               {
/*?*/                   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 Reference< ::com::sun::star::datatransfer::clipboard::XClipboard> aClipBoard(GetWindow()->GetClipboard());
//STRIP001 /*?*/                    CutCopy( aClipBoard, sal_True );
//STRIP001 /*?*/                    bDone = sal_True;
/*?*/               }
/*?*/           }
/*?*/           break;
/*?*/           case KEYFUNC_COPY:
/*?*/           {
/*?*/               DBG_BF_ASSERT(0, "STRIP"); //STRIP001   Reference< ::com::sun::star::datatransfer::clipboard::XClipboard> aClipBoard(GetWindow()->GetClipboard());
//STRIP001 /*?*/                CutCopy( aClipBoard, sal_False );
//STRIP001 /*?*/                 bDone = TRUE;
/*?*/           }
/*?*/           break;
/*?*/           case KEYFUNC_PASTE:
/*?*/           {
/*?*/               if ( !bReadOnly && IsPasteEnabled() )
/*?*/               {
/*?*/                   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 pEditEngine->pImpEditEngine->UndoActionStart( EDITUNDO_PASTE );
//STRIP001 /*?*/                     Reference< ::com::sun::star::datatransfer::clipboard::XClipboard> aClipBoard(GetWindow()->GetClipboard());
//STRIP001 /*?*/                    Paste( aClipBoard, pEditEngine->pImpEditEngine->GetStatus().AllowPasteSpecial() );
//STRIP001 /*?*/                    pEditEngine->pImpEditEngine->UndoActionEnd( EDITUNDO_PASTE );
//STRIP001 /*?*/                    bDone = sal_True;
/*?*/               }
/*?*/           }
/*?*/           break;
/*?*/         }
/*N*/     }
/*N*/
/*N*/     if( !bDone )
/*N*/       bDone = pEditEngine->PostKeyEvent( rKeyEvent, GetEditViewPtr() );
/*N*/
/*N*/     return bDone;
/*N*/ }

//STRIP001 sal_Bool ImpEditView::MouseButtonUp( const MouseEvent& rMouseEvent )
//STRIP001 {
//STRIP001  if ( pEditEngine->pImpEditEngine->aStatus.NotifyCursorMovements() )
//STRIP001  {
//STRIP001      if ( pEditEngine->pImpEditEngine->aStatus.GetPrevParagraph() != pEditEngine->pImpEditEngine->GetEditDoc().GetPos( GetEditSelection().Max().GetNode() ) )
//STRIP001      {
//STRIP001          pEditEngine->pImpEditEngine->aStatus.GetStatusWord() = pEditEngine->pImpEditEngine->aStatus.GetStatusWord() | EE_STAT_CRSRLEFTPARA;
//STRIP001          pEditEngine->pImpEditEngine->CallStatusHdl();
//STRIP001      }
//STRIP001  }
//STRIP001  nTravelXPos = TRAVEL_X_DONTKNOW;
//STRIP001     nCursorBidiLevel = CURSOR_BIDILEVEL_DONTKNOW;
//STRIP001     nExtraCursorFlags = 0;
//STRIP001     bClickedInSelection = sal_False;
//STRIP001
//STRIP001     if ( rMouseEvent.IsMiddle() && !bReadOnly &&
//STRIP001          ( GetWindow()->GetSettings().GetMouseSettings().GetMiddleButtonAction() == MOUSE_MIDDLE_PASTESELECTION ) )
//STRIP001     {
//STRIP001         Reference< ::com::sun::star::datatransfer::clipboard::XClipboard> aClipBoard(GetWindow()->GetSelection());
//STRIP001         Paste( aClipBoard );
//STRIP001     }
//STRIP001     else if ( rMouseEvent.IsLeft() && GetEditSelection().HasRange() )
//STRIP001     {
//STRIP001         Reference< ::com::sun::star::datatransfer::clipboard::XClipboard> aClipBoard(GetWindow()->GetSelection());
//STRIP001         CutCopy( aClipBoard, FALSE );
//STRIP001     }
//STRIP001
//STRIP001  return pEditEngine->pImpEditEngine->MouseButtonUp( rMouseEvent, GetEditViewPtr() );
//STRIP001 }

//STRIP001 sal_Bool ImpEditView::MouseButtonDown( const MouseEvent& rMouseEvent )
//STRIP001 {
//STRIP001  pEditEngine->pImpEditEngine->CheckIdleFormatter();  // Falls schnelles Tippen und MouseButtonDown
//STRIP001  if ( pEditEngine->pImpEditEngine->aStatus.NotifyCursorMovements() )
//STRIP001      pEditEngine->pImpEditEngine->aStatus.GetPrevParagraph() = pEditEngine->pImpEditEngine->GetEditDoc().GetPos( GetEditSelection().Max().GetNode() );
//STRIP001  nTravelXPos = TRAVEL_X_DONTKNOW;
//STRIP001     nExtraCursorFlags = 0;
//STRIP001     nCursorBidiLevel    = CURSOR_BIDILEVEL_DONTKNOW;
//STRIP001     bClickedInSelection = IsSelectionAtPoint( rMouseEvent.GetPosPixel() );
//STRIP001  return pEditEngine->pImpEditEngine->MouseButtonDown( rMouseEvent, GetEditViewPtr() );
//STRIP001 }

//STRIP001 sal_Bool ImpEditView::MouseMove( const MouseEvent& rMouseEvent )
//STRIP001 {
//STRIP001  return pEditEngine->pImpEditEngine->MouseMove( rMouseEvent, GetEditViewPtr() );
//STRIP001 }

//STRIP001 void ImpEditView::Command( const CommandEvent& rCEvt )
//STRIP001 {
//STRIP001  pEditEngine->pImpEditEngine->CheckIdleFormatter();  // Falls schnelles Tippen und MouseButtonDown
//STRIP001  pEditEngine->pImpEditEngine->Command( rCEvt, GetEditViewPtr() );
//STRIP001 }


//STRIP001 void ImpEditView::SetInsertMode( sal_Bool bInsert )
//STRIP001 {
//STRIP001  if ( bInsert != IsInsertMode() )
//STRIP001  {
//STRIP001      SetFlags( nControl, EV_CNTRL_OVERWRITE, !bInsert );
//STRIP001      ShowCursor( DoAutoScroll(), sal_False );
//STRIP001  }
//STRIP001 }

//STRIP001 sal_Bool ImpEditView::IsWrongSpelledWord( const EditPaM& rPaM, sal_Bool bMarkIfWrong )
//STRIP001 {
//STRIP001  sal_Bool bIsWrong = sal_False;
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  if ( rPaM.GetNode()->GetWrongList() )
//STRIP001  {
//STRIP001      EditSelection aSel = pEditEngine->pImpEditEngine->SelectWord( rPaM, ::com::sun::star::i18n::WordType::DICTIONARY_WORD );
//STRIP001      bIsWrong = rPaM.GetNode()->GetWrongList()->HasWrong( aSel.Min().GetIndex(), aSel.Max().GetIndex() );
//STRIP001      if ( bIsWrong && bMarkIfWrong )
//STRIP001      {
//STRIP001          DrawSelection();    // alte Selektion 'weg-zeichnen'
//STRIP001          SetEditSelection( aSel );
//STRIP001          DrawSelection();
//STRIP001      }
//STRIP001  }
//STRIP001 #endif // !SVX_LIGHT
//STRIP001  return bIsWrong;
//STRIP001 }

//STRIP001 String ImpEditView::SpellIgnoreOrAddWord( sal_Bool bAdd )
//STRIP001 {
//STRIP001  String aWord;
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  if ( pEditEngine->pImpEditEngine->GetSpeller().is() )
//STRIP001  {
//STRIP001      EditPaM aPaM = GetEditSelection().Max();
//STRIP001      if ( !HasSelection() )
//STRIP001      {
//STRIP001          EditSelection aSel = pEditEngine->pImpEditEngine->SelectWord( aPaM );
//STRIP001          aWord = pEditEngine->pImpEditEngine->GetSelected( aSel );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          aWord = pEditEngine->pImpEditEngine->GetSelected( GetEditSelection() );
//STRIP001          // Und deselektieren
//STRIP001          DrawSelection();    // alte Selektion 'weg-zeichnen'
//STRIP001          SetEditSelection( EditSelection( aPaM, aPaM ) );
//STRIP001          DrawSelection();
//STRIP001      }
//STRIP001
//STRIP001      if ( aWord.Len() )
//STRIP001      {
//STRIP001          if ( bAdd )
//STRIP001          {
//STRIP001              DBG_ERROR( "Sorry, AddWord not implemented" );
//STRIP001          }
//STRIP001          else // Ignore
//STRIP001          {
//STRIP001              Reference< XDictionary1 >  xDic( SvxGetIgnoreAllList(), UNO_QUERY );
//STRIP001              if (xDic.is())
//STRIP001                  xDic->add( aWord, sal_False, String() );
//STRIP001          }
//STRIP001          const EditDoc& rDoc = pEditEngine->pImpEditEngine->GetEditDoc();
//STRIP001          sal_uInt16 nNodes = rDoc.Count();
//STRIP001          for ( sal_uInt16 n = 0; n < nNodes; n++ )
//STRIP001          {
//STRIP001              ContentNode* pNode = rDoc.GetObject( n );
//STRIP001              pNode->GetWrongList()->MarkWrongsInvalid();
//STRIP001          }
//STRIP001          pEditEngine->pImpEditEngine->DoOnlineSpelling( aPaM.GetNode() );
//STRIP001          pEditEngine->pImpEditEngine->StartOnlineSpellTimer();
//STRIP001      }
//STRIP001  }
//STRIP001 #endif // !SVX_LIGHT
//STRIP001  return aWord;
//STRIP001 }

//STRIP001 void ImpEditView::DeleteSelected()
//STRIP001 {
//STRIP001  DrawSelection();
//STRIP001
//STRIP001  pEditEngine->pImpEditEngine->UndoActionStart( EDITUNDO_DELETE );
//STRIP001
//STRIP001  EditPaM aPaM = pEditEngine->pImpEditEngine->DeleteSelected( GetEditSelection() );
//STRIP001
//STRIP001  pEditEngine->pImpEditEngine->UndoActionEnd( EDITUNDO_DELETE );
//STRIP001
//STRIP001  SetEditSelection( EditSelection( aPaM, aPaM ) );
//STRIP001  pEditEngine->pImpEditEngine->FormatAndUpdate( GetEditViewPtr() );
//STRIP001  ShowCursor( DoAutoScroll(), TRUE );
//STRIP001 }

/*N*/ const SvxFieldItem* ImpEditView::GetField( const Point& rPos, sal_uInt16* pPara, sal_uInt16* pPos ) const
/*N*/ {
/*N*/   if( !GetOutputArea().IsInside( rPos ) )
/*N*/       return 0;
/*N*/
/*N*/   Point aDocPos( GetDocPos( rPos ) );
/*N*/   EditPaM aPaM = pEditEngine->pImpEditEngine->GetPaM( aDocPos, sal_False );
/*N*/
/*N*/   if ( aPaM.GetIndex() == aPaM.GetNode()->Len() )
/*N*/   {
/*N*/       // Sonst immer, wenn Feld ganz am Schluss und Mouse unter Text
/*N*/       return 0;
/*N*/   }
/*N*/
/*N*/   const CharAttribArray& rAttrs = aPaM.GetNode()->GetCharAttribs().GetAttribs();
/*N*/   sal_uInt16 nXPos = aPaM.GetIndex();
/*N*/   for ( sal_uInt16 nAttr = rAttrs.Count(); nAttr; )
/*N*/   {
/*N*/       EditCharAttrib* pAttr = rAttrs[--nAttr];
/*N*/       if ( pAttr->GetStart() == nXPos )
/*?*/           if ( pAttr->Which() == EE_FEATURE_FIELD )
/*?*/           {
/*?*/               DBG_ASSERT( pAttr->GetItem()->ISA( SvxFieldItem ), "Kein FeldItem..." );
/*?*/               if ( pPara )
/*?*/                   *pPara = pEditEngine->pImpEditEngine->GetEditDoc().GetPos( aPaM.GetNode() );
/*?*/               if ( pPos )
/*?*/                   *pPos = pAttr->GetStart();
/*?*/               return (const SvxFieldItem*)pAttr->GetItem();
/*?*/           }
/*N*/   }
/*N*/   return NULL;
/*N*/ }

//STRIP001 BOOL ImpEditView::IsBulletArea( const Point& rPos, sal_uInt16* pPara )
//STRIP001 {
//STRIP001     if ( pPara )
//STRIP001         *pPara = 0xFFFF;
//STRIP001
//STRIP001     if( !GetOutputArea().IsInside( rPos ) )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  Point aDocPos( GetDocPos( rPos ) );
//STRIP001  EditPaM aPaM = pEditEngine->pImpEditEngine->GetPaM( aDocPos, sal_False );
//STRIP001
//STRIP001  if ( aPaM.GetIndex() == 0 )
//STRIP001  {
//STRIP001         USHORT nPara = pEditEngine->pImpEditEngine->aEditDoc.GetPos( aPaM.GetNode() );
//STRIP001      Rectangle aBulletArea = pEditEngine->GetBulletArea( nPara );
//STRIP001         long nY = pEditEngine->GetDocPosTopLeft( nPara ).Y();
//STRIP001         ParaPortion* pParaPortion = pEditEngine->pImpEditEngine->GetParaPortions().GetObject( nPara );
//STRIP001         nY += pParaPortion->GetFirstLineOffset();
//STRIP001         if ( ( aDocPos.Y() > ( nY + aBulletArea.Top() ) ) &&
//STRIP001              ( aDocPos.Y() < ( nY + aBulletArea.Bottom() ) ) &&
//STRIP001              ( aDocPos.X() > ( aBulletArea.Left() ) ) &&
//STRIP001              ( aDocPos.X() < ( aBulletArea.Right() ) ) )
//STRIP001         {
//STRIP001             if ( pPara )
//STRIP001                 *pPara = nPara;
//STRIP001          return TRUE;
//STRIP001         }
//STRIP001  }
//STRIP001
//STRIP001     return FALSE;
//STRIP001 }

//STRIP001 void ImpEditView::CutCopy( ::com::sun::star::uno::Reference< ::com::sun::star::datatransfer::clipboard::XClipboard >& rxClipboard, BOOL bCut )
//STRIP001 {
//STRIP001  if ( rxClipboard.is() && GetEditSelection().HasRange() )
//STRIP001     {
//STRIP001      uno::Reference< datatransfer::XTransferable > xData = pEditEngine->pImpEditEngine->CreateTransferable( GetEditSelection() );
//STRIP001
//STRIP001         const sal_uInt32 nRef = Application::ReleaseSolarMutex();
//STRIP001
//STRIP001         try
//STRIP001      {
//STRIP001             rxClipboard->setContents( xData, NULL );
//STRIP001
//STRIP001             // #87756# FlushClipboard, but it would be better to become a TerminateListener to the Desktop and flush on demand...
//STRIP001             uno::Reference< datatransfer::clipboard::XFlushableClipboard > xFlushableClipboard( rxClipboard, uno::UNO_QUERY );
//STRIP001          if( xFlushableClipboard.is() )
//STRIP001              xFlushableClipboard->flushClipboard();
//STRIP001      }
//STRIP001      catch( const ::com::sun::star::uno::Exception& )
//STRIP001      {
//STRIP001      }
//STRIP001
//STRIP001         Application::AcquireSolarMutex( nRef );
//STRIP001
//STRIP001         if ( bCut )
//STRIP001      {
//STRIP001             pEditEngine->pImpEditEngine->UndoActionStart( EDITUNDO_CUT );
//STRIP001          DeleteSelected();
//STRIP001             pEditEngine->pImpEditEngine->UndoActionEnd( EDITUNDO_CUT );
//STRIP001
//STRIP001      }
//STRIP001     }
//STRIP001 }

//STRIP001 void ImpEditView::Paste( ::com::sun::star::uno::Reference< ::com::sun::star::datatransfer::clipboard::XClipboard >& rxClipboard, BOOL bUseSpecial )
//STRIP001 {
//STRIP001  if ( rxClipboard.is() )
//STRIP001  {
//STRIP001         uno::Reference< datatransfer::XTransferable > xDataObj;
//STRIP001
//STRIP001         const sal_uInt32 nRef = Application::ReleaseSolarMutex();
//STRIP001
//STRIP001         try
//STRIP001      {
//STRIP001          xDataObj = rxClipboard->getContents();
//STRIP001      }
//STRIP001      catch( const ::com::sun::star::uno::Exception& )
//STRIP001      {
//STRIP001      }
//STRIP001
//STRIP001         Application::AcquireSolarMutex( nRef );
//STRIP001
//STRIP001         if ( xDataObj.is() && EditEngine::HasValidData( xDataObj ) )
//STRIP001      {
//STRIP001          pEditEngine->pImpEditEngine->UndoActionStart( EDITUNDO_PASTE );
//STRIP001
//STRIP001             EditSelection aSel( GetEditSelection() );
//STRIP001             if ( aSel.HasRange() )
//STRIP001          {
//STRIP001              DrawSelection();
//STRIP001              aSel = pEditEngine->pImpEditEngine->ImpDeleteSelection( aSel );
//STRIP001             }
//STRIP001
//STRIP001             PasteOrDropInfos aPasteOrDropInfos;
//STRIP001             aPasteOrDropInfos.nAction = EE_ACTION_PASTE;
//STRIP001             aPasteOrDropInfos.nStartPara = pEditEngine->pImpEditEngine->GetEditDoc().GetPos( aSel.Min().GetNode() );
//STRIP001             pEditEngine->pImpEditEngine->aBeginPasteOrDropHdl.Call( &aPasteOrDropInfos );
//STRIP001
//STRIP001             if ( DoSingleLinePaste() )
//STRIP001          {
//STRIP001              datatransfer::DataFlavor aFlavor;
//STRIP001              SotExchange::GetFormatDataFlavor( SOT_FORMAT_STRING, aFlavor );
//STRIP001              if ( xDataObj->isDataFlavorSupported( aFlavor ) )
//STRIP001              {
//STRIP001                  try
//STRIP001                  {
//STRIP001                      uno::Any aData = xDataObj->getTransferData( aFlavor );
//STRIP001                      ::rtl::OUString aTmpText;
//STRIP001                      aData >>= aTmpText;
//STRIP001                      String aText( aTmpText );
//STRIP001                      aText.ConvertLineEnd( LINEEND_LF );
//STRIP001                      aText.SearchAndReplaceAll( LINE_SEP, ' ' );
//STRIP001                      aSel = pEditEngine->pImpEditEngine->ImpInsertText( aSel, aText );
//STRIP001                  }
//STRIP001                  catch( ... )
//STRIP001                  {
//STRIP001                      ; // #i9286# can happen, even if isDataFlavorSupported returns true...
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              aSel = pEditEngine->pImpEditEngine->InsertText( xDataObj, aSel.Min(), bUseSpecial && pEditEngine->pImpEditEngine->GetStatus().AllowPasteSpecial() );
//STRIP001          }
//STRIP001
//STRIP001             aPasteOrDropInfos.nEndPara = pEditEngine->pImpEditEngine->GetEditDoc().GetPos( aSel.Max().GetNode() );
//STRIP001             pEditEngine->pImpEditEngine->aEndPasteOrDropHdl.Call( &aPasteOrDropInfos );
//STRIP001
//STRIP001          pEditEngine->pImpEditEngine->UndoActionEnd( EDITUNDO_PASTE );
//STRIP001          SetEditSelection( aSel );
//STRIP001          pEditEngine->pImpEditEngine->UpdateSelections();
//STRIP001          pEditEngine->pImpEditEngine->FormatAndUpdate( GetEditViewPtr() );
//STRIP001             ShowCursor( DoAutoScroll(), TRUE );
//STRIP001         }
//STRIP001  }
//STRIP001 }


//STRIP001 BOOL ImpEditView::IsInSelection( const EditPaM& rPaM )
//STRIP001 {
//STRIP001  EditSelection aSel = GetEditSelection();
//STRIP001  if ( !aSel.HasRange() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  aSel.Adjust( pEditEngine->pImpEditEngine->GetEditDoc() );
//STRIP001
//STRIP001  USHORT nStartNode = pEditEngine->pImpEditEngine->GetEditDoc().GetPos( aSel.Min().GetNode() );
//STRIP001  USHORT nEndNode = pEditEngine->pImpEditEngine->GetEditDoc().GetPos( aSel.Max().GetNode() );
//STRIP001  USHORT nCurNode = pEditEngine->pImpEditEngine->GetEditDoc().GetPos( rPaM.GetNode() );
//STRIP001
//STRIP001  if ( ( nCurNode > nStartNode ) && ( nCurNode < nEndNode ) )
//STRIP001      return TRUE;
//STRIP001
//STRIP001  if ( nStartNode == nEndNode )
//STRIP001  {
//STRIP001      if ( nCurNode == nStartNode )
//STRIP001          if ( ( rPaM.GetIndex() >= aSel.Min().GetIndex() ) && ( rPaM.GetIndex() < aSel.Max().GetIndex() ) )
//STRIP001              return TRUE;
//STRIP001  }
//STRIP001  else if ( ( nCurNode == nStartNode ) && ( rPaM.GetIndex() >= aSel.Min().GetIndex() ) )
//STRIP001      return TRUE;
//STRIP001  else if ( ( nCurNode == nEndNode ) && ( rPaM.GetIndex() < aSel.Max().GetIndex() ) )
//STRIP001      return TRUE;
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 void ImpEditView::CreateAnchor()
//STRIP001 {
//STRIP001  pEditEngine->pImpEditEngine->bInSelection = TRUE;
//STRIP001  GetEditSelection().Min() = GetEditSelection().Max();
//STRIP001 }

//STRIP001 void ImpEditView::DeselectAll()
//STRIP001 {
//STRIP001  pEditEngine->pImpEditEngine->bInSelection = FALSE;
//STRIP001  DrawSelection();
//STRIP001  GetEditSelection().Min() = GetEditSelection().Max();
//STRIP001 }

//STRIP001 BOOL ImpEditView::IsSelectionAtPoint( const Point& rPosPixel )
//STRIP001 {
//STRIP001  if ( pDragAndDropInfo && pDragAndDropInfo->pField )
//STRIP001      return TRUE;
//STRIP001
//STRIP001  Point aMousePos( rPosPixel );
//STRIP001
//STRIP001  // Logische Einheiten...
//STRIP001  aMousePos = GetWindow()->PixelToLogic( aMousePos );
//STRIP001
//STRIP001  if ( ( !GetOutputArea().IsInside( aMousePos ) ) && !pEditEngine->pImpEditEngine->IsInSelectionMode() )
//STRIP001  {
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  Point aDocPos( GetDocPos( aMousePos ) );
//STRIP001  EditPaM aPaM = pEditEngine->pImpEditEngine->GetPaM( aDocPos, FALSE );
//STRIP001  return IsInSelection( aPaM );
//STRIP001 }

//STRIP001 BOOL ImpEditView::SetCursorAtPoint( const Point& rPointPixel )
//STRIP001 {
//STRIP001  pEditEngine->pImpEditEngine->CheckIdleFormatter();
//STRIP001
//STRIP001  Point aMousePos( rPointPixel );
//STRIP001
//STRIP001  // Logische Einheiten...
//STRIP001  aMousePos = GetWindow()->PixelToLogic( aMousePos );
//STRIP001
//STRIP001  if ( ( !GetOutputArea().IsInside( aMousePos ) ) && !pEditEngine->pImpEditEngine->IsInSelectionMode() )
//STRIP001  {
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  Point aDocPos( GetDocPos( aMousePos ) );
//STRIP001
//STRIP001  // Kann optimiert werden: Erst innerhalb eines Absatzes die Zeilen
//STRIP001  // fuer den PaM durchwuehlen, dann nochmal mit dem PaM fuer das Rect,
//STRIP001  // obwohl die Zeile schon bekannt ist....
//STRIP001  // Das muss doch nicht sein !
//STRIP001
//STRIP001  EditPaM aPaM = pEditEngine->pImpEditEngine->GetPaM( aDocPos );
//STRIP001  BOOL bGotoCursor = DoAutoScroll();
//STRIP001
//STRIP001  // aTmpNewSel: Diff zwischen alt und neu, nicht die neue Selektion
//STRIP001  EditSelection aTmpNewSel( GetEditSelection().Max(), aPaM );
//STRIP001
//STRIP001  GetEditSelection().Max() = aPaM;
//STRIP001  if ( !pEditEngine->pImpEditEngine->aSelEngine.HasAnchor() )
//STRIP001  {
//STRIP001      if ( GetEditSelection().Min() != aPaM )
//STRIP001          pEditEngine->pImpEditEngine->CursorMoved( GetEditSelection().Min().GetNode() );
//STRIP001      GetEditSelection().Min() = aPaM;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      DrawSelection( aTmpNewSel );
//STRIP001  }
//STRIP001
//STRIP001  BOOL bForceCursor = ( pDragAndDropInfo ? FALSE : TRUE ) && !pEditEngine->pImpEditEngine->IsInSelectionMode();
//STRIP001  ShowCursor( bGotoCursor, bForceCursor );
//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 void ImpEditView::HideDDCursor()
//STRIP001 {
//STRIP001  if ( pDragAndDropInfo && pDragAndDropInfo->bVisCursor )
//STRIP001  {
//STRIP001      GetWindow()->DrawOutDev( pDragAndDropInfo->aCurSavedCursor.TopLeft(), pDragAndDropInfo->aCurSavedCursor.GetSize(),
//STRIP001                          Point(0,0), pDragAndDropInfo->aCurSavedCursor.GetSize(),*pDragAndDropInfo->pBackground );
//STRIP001      pDragAndDropInfo->bVisCursor = sal_False;
//STRIP001  }
//STRIP001 }

//STRIP001 void ImpEditView::ShowDDCursor( const Rectangle& rRect )
//STRIP001 {
//STRIP001  if ( !pDragAndDropInfo->bVisCursor )
//STRIP001  {
//STRIP001      if ( pOutWin->GetCursor() )
//STRIP001          pOutWin->GetCursor()->Hide();
//STRIP001
//STRIP001      Brush aOldBrush = GetWindow()->GetFillInBrush( );
//STRIP001      GetWindow()->SetFillInBrush( Brush( Color( COL_GRAY), BRUSH_50 ) );
//STRIP001
//STRIP001      // Hintergrund sichern...
//STRIP001      Rectangle aSaveRec( GetWindow()->LogicToPixel( rRect ) );
//STRIP001      // lieber etwas mehr sichern...
//STRIP001      aSaveRec.Right() += 1;
//STRIP001      aSaveRec.Bottom() += 1;
//STRIP001
//STRIP001      Size aNewSzPx( aSaveRec.GetSize() );
//STRIP001      if ( !pDragAndDropInfo->pBackground )
//STRIP001      {
//STRIP001          pDragAndDropInfo->pBackground = new VirtualDevice( *GetWindow() );
//STRIP001          MapMode aMapMode( GetWindow()->GetMapMode() );
//STRIP001          aMapMode.SetOrigin( Point( 0, 0 ) );
//STRIP001          pDragAndDropInfo->pBackground->SetMapMode( aMapMode );
//STRIP001
//STRIP001      }
//STRIP001      Size aCurSzPx( pDragAndDropInfo->pBackground->GetOutputSizePixel() );
//STRIP001      if ( ( aCurSzPx.Width() < aNewSzPx.Width() ) ||( aCurSzPx.Height() < aNewSzPx.Height() ) )
//STRIP001      {
//STRIP001          sal_Bool bDone = pDragAndDropInfo->pBackground->SetOutputSizePixel( aNewSzPx );
//STRIP001          DBG_ASSERT( bDone, "Virtuelles Device kaputt?" );
//STRIP001      }
//STRIP001
//STRIP001
//STRIP001      aSaveRec = GetWindow()->PixelToLogic( aSaveRec );
//STRIP001
//STRIP001      pDragAndDropInfo->pBackground->DrawOutDev( Point(0,0), aSaveRec.GetSize(),
//STRIP001                                  aSaveRec.TopLeft(), aSaveRec.GetSize(), *GetWindow() );
//STRIP001      pDragAndDropInfo->aCurSavedCursor = aSaveRec;
//STRIP001
//STRIP001      // Cursor malen...
//STRIP001      GetWindow()->DrawRect( rRect );
//STRIP001
//STRIP001      pDragAndDropInfo->bVisCursor = sal_True;
//STRIP001      pDragAndDropInfo->aCurCursor = rRect;
//STRIP001
//STRIP001      GetWindow()->SetFillInBrush( aOldBrush );
//STRIP001  }
//STRIP001 }

//STRIP001 void ImpEditView::dragGestureRecognized( const ::com::sun::star::datatransfer::dnd::DragGestureEvent& rDGE ) throw (::com::sun::star::uno::RuntimeException)
//STRIP001 {
//STRIP001     DBG_ASSERT( !pDragAndDropInfo, "dragGestureRecognized - DragAndDropInfo exist!" );
//STRIP001
//STRIP001     vos::OGuard aVclGuard( Application::GetSolarMutex() );
//STRIP001
//STRIP001     Point aMousePosPixel( rDGE.DragOriginX, rDGE.DragOriginY );
//STRIP001
//STRIP001     EditSelection aCopySel( GetEditSelection() );
//STRIP001     aCopySel.Adjust( pEditEngine->pImpEditEngine->GetEditDoc() );
//STRIP001
//STRIP001     if ( GetEditSelection().HasRange() && bClickedInSelection )
//STRIP001     {
//STRIP001         pDragAndDropInfo = new DragAndDropInfo();
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001      // Field?!
//STRIP001      USHORT nPara, nPos;
//STRIP001      Point aMousePos = GetWindow()->PixelToLogic( aMousePosPixel );
//STRIP001      const SvxFieldItem* pField = GetField( aMousePos, &nPara, &nPos );
//STRIP001      if ( pField )
//STRIP001      {
//STRIP001          pDragAndDropInfo = new DragAndDropInfo();
//STRIP001          pDragAndDropInfo->pField = pField;
//STRIP001             ContentNode* pNode = pEditEngine->pImpEditEngine->GetEditDoc().GetObject( nPara );
//STRIP001             aCopySel = EditSelection( EditPaM( pNode, nPos ), EditPaM( pNode, nPos+1 ) );
//STRIP001          GetEditSelection() = aCopySel;
//STRIP001          DrawSelection();
//STRIP001          BOOL bGotoCursor = DoAutoScroll();
//STRIP001          BOOL bForceCursor = ( pDragAndDropInfo ? FALSE : TRUE ) && !pEditEngine->pImpEditEngine->IsInSelectionMode();
//STRIP001          ShowCursor( bGotoCursor, bForceCursor );
//STRIP001      }
//STRIP001         else if ( IsBulletArea( aMousePos, &nPara ) )
//STRIP001         {
//STRIP001             pDragAndDropInfo = new DragAndDropInfo();
//STRIP001             pDragAndDropInfo->bOutlinerMode = TRUE;
//STRIP001             EditPaM aStartPaM( pEditEngine->pImpEditEngine->GetEditDoc().GetObject( nPara ), 0 );
//STRIP001             EditPaM aEndPaM( aStartPaM );
//STRIP001             const SfxUInt16Item& rLevel = (const SfxUInt16Item&) pEditEngine->GetParaAttrib( nPara, EE_PARA_OUTLLEVEL );
//STRIP001             for ( USHORT n = nPara +1; n < pEditEngine->pImpEditEngine->GetEditDoc().Count(); n++ )
//STRIP001             {
//STRIP001                 const SfxUInt16Item& rL = (const SfxUInt16Item&) pEditEngine->GetParaAttrib( n, EE_PARA_OUTLLEVEL );
//STRIP001                 if ( rL.GetValue() > rLevel.GetValue() )
//STRIP001                 {
//STRIP001                     aEndPaM.SetNode( pEditEngine->pImpEditEngine->GetEditDoc().GetObject( n ) );
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     break;
//STRIP001                 }
//STRIP001             }
//STRIP001             aEndPaM.GetIndex() = aEndPaM.GetNode()->Len();
//STRIP001             SetEditSelection( EditSelection( aStartPaM, aEndPaM ) );
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     if ( pDragAndDropInfo )
//STRIP001     {
//STRIP001
//STRIP001      pDragAndDropInfo->bStarterOfDD = sal_True;
//STRIP001
//STRIP001      // Sensibler Bereich, wo gescrollt werden soll.
//STRIP001      Size aSz( 5, 0 );
//STRIP001      aSz = GetWindow()->PixelToLogic( aSz );
//STRIP001      pDragAndDropInfo->nSensibleRange = (sal_uInt16) aSz.Width();
//STRIP001      pDragAndDropInfo->nCursorWidth = (sal_uInt16) aSz.Width() / 2;
//STRIP001      pDragAndDropInfo->aBeginDragSel = pEditEngine->pImpEditEngine->CreateESel( aCopySel );
//STRIP001
//STRIP001         uno::Reference< datatransfer::XTransferable > xData = pEditEngine->pImpEditEngine->CreateTransferable( aCopySel );
//STRIP001
//STRIP001         sal_Int8 nActions = bReadOnly ? datatransfer::dnd::DNDConstants::ACTION_COPY : datatransfer::dnd::DNDConstants::ACTION_COPY_OR_MOVE;
//STRIP001
//STRIP001         rDGE.DragSource->startDrag( rDGE, nActions, 0 /*cursor*/, 0 /*image*/, xData, mxDnDListener );
//STRIP001      // Falls Drag&Move in einer Engine, muessen Copy&Del geklammert sein!
//STRIP001      GetCursor()->Hide();
//STRIP001
//STRIP001     }
//STRIP001 }

//STRIP001 void ImpEditView::dragDropEnd( const ::com::sun::star::datatransfer::dnd::DragSourceDropEvent& rDSDE ) throw (::com::sun::star::uno::RuntimeException)
//STRIP001 {
//STRIP001  vos::OGuard aVclGuard( Application::GetSolarMutex() );
//STRIP001
//STRIP001     if ( !bReadOnly && rDSDE.DropSuccess && !pDragAndDropInfo->bOutlinerMode && ( rDSDE.DropAction & datatransfer::dnd::DNDConstants::ACTION_MOVE ) )
//STRIP001  {
//STRIP001      if ( pDragAndDropInfo->bStarterOfDD && pDragAndDropInfo->bDroppedInMe )
//STRIP001      {
//STRIP001          // DropPos: Wohin wurde gedroppt, unabhaengig von laenge.
//STRIP001          ESelection aDropPos( pDragAndDropInfo->aDropSel.nStartPara, pDragAndDropInfo->aDropSel.nStartPos, pDragAndDropInfo->aDropSel.nStartPara, pDragAndDropInfo->aDropSel.nStartPos );
//STRIP001          ESelection aToBeDelSel = pDragAndDropInfo->aBeginDragSel;
//STRIP001          ESelection aNewSel( pDragAndDropInfo->aDropSel.nEndPara, pDragAndDropInfo->aDropSel.nEndPos,
//STRIP001                              pDragAndDropInfo->aDropSel.nEndPara, pDragAndDropInfo->aDropSel.nEndPos );
//STRIP001          sal_Bool bBeforeSelection = aDropPos.IsLess( pDragAndDropInfo->aBeginDragSel );
//STRIP001          sal_uInt16 nParaDiff = pDragAndDropInfo->aBeginDragSel.nEndPara - pDragAndDropInfo->aBeginDragSel.nStartPara;
//STRIP001          if ( bBeforeSelection )
//STRIP001          {
//STRIP001              // aToBeDelSel anpassen.
//STRIP001              DBG_ASSERT( pDragAndDropInfo->aBeginDragSel.nStartPara >= pDragAndDropInfo->aDropSel.nStartPara, "Doch nicht davor?" );
//STRIP001              aToBeDelSel.nStartPara += nParaDiff;
//STRIP001              aToBeDelSel.nEndPara += nParaDiff;
//STRIP001              // Zeichen korrigieren?
//STRIP001              if ( aToBeDelSel.nStartPara == pDragAndDropInfo->aDropSel.nEndPara )
//STRIP001              {
//STRIP001                  sal_uInt16 nMoreChars;
//STRIP001                  if ( pDragAndDropInfo->aDropSel.nStartPara == pDragAndDropInfo->aDropSel.nEndPara )
//STRIP001                      nMoreChars = pDragAndDropInfo->aDropSel.nEndPos - pDragAndDropInfo->aDropSel.nStartPos;
//STRIP001                  else
//STRIP001                      nMoreChars = pDragAndDropInfo->aDropSel.nEndPos;
//STRIP001                  aToBeDelSel.nStartPos += nMoreChars;
//STRIP001                  if ( aToBeDelSel.nStartPara == aToBeDelSel.nEndPara )
//STRIP001                      aToBeDelSel.nEndPos += nMoreChars;
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              // aToBeDelSel ist ok, aber Selektion der View
//STRIP001              // muss angepasst werden, wenn davor geloescht wird!
//STRIP001              DBG_ASSERT( pDragAndDropInfo->aBeginDragSel.nStartPara <= pDragAndDropInfo->aDropSel.nStartPara, "Doch nicht davor?" );
//STRIP001              aNewSel.nStartPara -= nParaDiff;
//STRIP001              aNewSel.nEndPara -= nParaDiff;
//STRIP001              // Zeichen korrigieren?
//STRIP001              if ( pDragAndDropInfo->aBeginDragSel.nEndPara == pDragAndDropInfo->aDropSel.nStartPara )
//STRIP001              {
//STRIP001                  sal_uInt16 nLessChars;
//STRIP001                  if ( pDragAndDropInfo->aBeginDragSel.nStartPara == pDragAndDropInfo->aBeginDragSel.nEndPara )
//STRIP001                      nLessChars = pDragAndDropInfo->aBeginDragSel.nEndPos - pDragAndDropInfo->aBeginDragSel.nStartPos;
//STRIP001                  else
//STRIP001                      nLessChars = pDragAndDropInfo->aBeginDragSel.nEndPos;
//STRIP001                  aNewSel.nStartPos -= nLessChars;
//STRIP001                  if ( aNewSel.nStartPara == aNewSel.nEndPara )
//STRIP001                      aNewSel.nEndPos -= nLessChars;
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          DrawSelection();
//STRIP001          EditSelection aDelSel( pEditEngine->pImpEditEngine->CreateSel( aToBeDelSel ) );
//STRIP001          DBG_ASSERT( !aDelSel.DbgIsBuggy( pEditEngine->pImpEditEngine->aEditDoc ), "ToBeDel ist buggy!" );
//STRIP001          pEditEngine->pImpEditEngine->ImpDeleteSelection( aDelSel );
//STRIP001          if ( !bBeforeSelection )
//STRIP001          {
//STRIP001              DBG_ASSERT( !pEditEngine->pImpEditEngine->CreateSel( aNewSel ).DbgIsBuggy(pEditEngine->pImpEditEngine->aEditDoc), "Bad" );
//STRIP001              SetEditSelection( pEditEngine->pImpEditEngine->CreateSel( aNewSel ) );
//STRIP001          }
//STRIP001          pEditEngine->pImpEditEngine->FormatAndUpdate( pEditEngine->pImpEditEngine->GetActiveView() );
//STRIP001          DrawSelection();
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // andere EditEngine...
//STRIP001             if ( pEditEngine->pImpEditEngine->ImplHasText() )   // #88630# SC ist removing the content when switching the task
//STRIP001                 DeleteSelected();
//STRIP001         }
//STRIP001  }
//STRIP001
//STRIP001     if ( pDragAndDropInfo && pDragAndDropInfo->bUndoAction )
//STRIP001         pEditEngine->pImpEditEngine->UndoActionEnd( EDITUNDO_DRAGANDDROP );
//STRIP001
//STRIP001  HideDDCursor();
//STRIP001  ShowCursor( DoAutoScroll(), TRUE );
//STRIP001  delete pDragAndDropInfo;
//STRIP001     pDragAndDropInfo = NULL;
//STRIP001 }

//STRIP001 void ImpEditView::drop( const ::com::sun::star::datatransfer::dnd::DropTargetDropEvent& rDTDE ) throw (::com::sun::star::uno::RuntimeException)
//STRIP001 {
//STRIP001  vos::OGuard aVclGuard( Application::GetSolarMutex() );
//STRIP001
//STRIP001     DBG_ASSERT( pDragAndDropInfo, "Drop - No Drag&Drop info?!" );
//STRIP001
//STRIP001     if ( pDragAndDropInfo->bDragAccepted )
//STRIP001     {
//STRIP001      BOOL bChanges = FALSE;
//STRIP001
//STRIP001         HideDDCursor();
//STRIP001
//STRIP001         if ( pDragAndDropInfo->bStarterOfDD )
//STRIP001         {
//STRIP001             pEditEngine->pImpEditEngine->UndoActionStart( EDITUNDO_DRAGANDDROP );
//STRIP001             pDragAndDropInfo->bUndoAction = TRUE;
//STRIP001         }
//STRIP001
//STRIP001         if ( pDragAndDropInfo->bOutlinerMode )
//STRIP001         {
//STRIP001             bChanges = TRUE;
//STRIP001             GetEditViewPtr()->MoveParagraphs( Range( pDragAndDropInfo->aBeginDragSel.nStartPara, pDragAndDropInfo->aBeginDragSel.nEndPara ), pDragAndDropInfo->nOutlinerDropDest );
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001          uno::Reference< datatransfer::XTransferable > xDataObj = rDTDE.Transferable;
//STRIP001          if ( xDataObj.is() )
//STRIP001          {
//STRIP001                 bChanges = TRUE;
//STRIP001              // Selektion wegmalen...
//STRIP001              DrawSelection();
//STRIP001                 EditPaM aPaM( pDragAndDropInfo->aDropDest );
//STRIP001
//STRIP001                 PasteOrDropInfos aPasteOrDropInfos;
//STRIP001                 aPasteOrDropInfos.nAction = EE_ACTION_DROP;
//STRIP001                 aPasteOrDropInfos.nStartPara = pEditEngine->pImpEditEngine->GetEditDoc().GetPos( aPaM.GetNode() );
//STRIP001                 pEditEngine->pImpEditEngine->aBeginPasteOrDropHdl.Call( &aPasteOrDropInfos );
//STRIP001
//STRIP001                 EditSelection aNewSel = pEditEngine->pImpEditEngine->InsertText( xDataObj, aPaM, pEditEngine->pImpEditEngine->GetStatus().AllowPasteSpecial() );
//STRIP001
//STRIP001                 aPasteOrDropInfos.nEndPara = pEditEngine->pImpEditEngine->GetEditDoc().GetPos( aNewSel.Max().GetNode() );
//STRIP001                 pEditEngine->pImpEditEngine->aEndPasteOrDropHdl.Call( &aPasteOrDropInfos );
//STRIP001
//STRIP001                 SetEditSelection( aNewSel );
//STRIP001              pEditEngine->pImpEditEngine->FormatAndUpdate( pEditEngine->pImpEditEngine->GetActiveView() );
//STRIP001              if ( pDragAndDropInfo->bStarterOfDD )
//STRIP001              {
//STRIP001                  // Nur dann setzen, wenn in gleicher Engine!
//STRIP001                  pDragAndDropInfo->aDropSel.nStartPara = pEditEngine->pImpEditEngine->aEditDoc.GetPos( aPaM.GetNode() );
//STRIP001                  pDragAndDropInfo->aDropSel.nStartPos = aPaM.GetIndex();
//STRIP001                  pDragAndDropInfo->aDropSel.nEndPara = pEditEngine->pImpEditEngine->aEditDoc.GetPos( aNewSel.Max().GetNode() );
//STRIP001                  pDragAndDropInfo->aDropSel.nEndPos = aNewSel.Max().GetIndex();
//STRIP001                  pDragAndDropInfo->bDroppedInMe = sal_True;
//STRIP001              }
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         if ( bChanges )
//STRIP001         {
//STRIP001             rDTDE.Context->acceptDrop( rDTDE.DropAction );
//STRIP001         }
//STRIP001
//STRIP001      if ( !pDragAndDropInfo->bStarterOfDD )
//STRIP001      {
//STRIP001          delete pDragAndDropInfo;
//STRIP001          pDragAndDropInfo = NULL;
//STRIP001      }
//STRIP001
//STRIP001         rDTDE.Context->dropComplete( bChanges );
//STRIP001     }
//STRIP001 }

//STRIP001 void ImpEditView::dragEnter( const ::com::sun::star::datatransfer::dnd::DropTargetDragEnterEvent& rDTDEE ) throw (::com::sun::star::uno::RuntimeException)
//STRIP001 {
//STRIP001  vos::OGuard aVclGuard( Application::GetSolarMutex() );
//STRIP001
//STRIP001     if ( !pDragAndDropInfo )
//STRIP001         pDragAndDropInfo = new DragAndDropInfo( );
//STRIP001
//STRIP001     pDragAndDropInfo->bHasValidData = sal_False;
//STRIP001
//STRIP001     // Check for supported format...
//STRIP001     // Only check for text, will also be there if bin or rtf
//STRIP001     datatransfer::DataFlavor aTextFlavor;
//STRIP001  SotExchange::GetFormatDataFlavor( SOT_FORMAT_STRING, aTextFlavor );
//STRIP001     const ::com::sun::star::datatransfer::DataFlavor* pFlavors = rDTDEE.SupportedDataFlavors.getConstArray();
//STRIP001     int nFlavors = rDTDEE.SupportedDataFlavors.getLength();
//STRIP001     for ( int n = 0; n < nFlavors; n++ )
//STRIP001     {
//STRIP001         if( TransferableDataHelper::IsEqual( pFlavors[n], aTextFlavor ) )
//STRIP001         {
//STRIP001             pDragAndDropInfo->bHasValidData = sal_True;
//STRIP001             break;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     dragOver( rDTDEE );
//STRIP001 }

//STRIP001 void ImpEditView::dragExit( const ::com::sun::star::datatransfer::dnd::DropTargetEvent& dte ) throw (::com::sun::star::uno::RuntimeException)
//STRIP001 {
//STRIP001  vos::OGuard aVclGuard( Application::GetSolarMutex() );
//STRIP001
//STRIP001     HideDDCursor();
//STRIP001
//STRIP001  if ( !pDragAndDropInfo->bStarterOfDD )
//STRIP001  {
//STRIP001      delete pDragAndDropInfo;
//STRIP001      pDragAndDropInfo = NULL;
//STRIP001  }
//STRIP001 }

//STRIP001 void ImpEditView::dragOver( const ::com::sun::star::datatransfer::dnd::DropTargetDragEvent& rDTDE ) throw (::com::sun::star::uno::RuntimeException)
//STRIP001 {
//STRIP001     vos::OGuard aVclGuard( Application::GetSolarMutex() );
//STRIP001
//STRIP001     Point aMousePos( rDTDE.LocationX, rDTDE.LocationY );
//STRIP001  aMousePos = GetWindow()->PixelToLogic( aMousePos );
//STRIP001
//STRIP001     sal_Bool bAccept = sal_False;
//STRIP001
//STRIP001     if ( GetOutputArea().IsInside( aMousePos ) && !bReadOnly )
//STRIP001     {
//STRIP001         sal_Int8 nSupportedActions = bReadOnly ? datatransfer::dnd::DNDConstants::ACTION_COPY : datatransfer::dnd::DNDConstants::ACTION_COPY_OR_MOVE;
//STRIP001
//STRIP001         if ( pDragAndDropInfo->bHasValidData /* && ( nSupportedActions & rDTDE.DropAction ) MT: Default = 0x80 ?! */ )
//STRIP001         {
//STRIP001             bAccept = sal_True;
//STRIP001
//STRIP001             sal_Bool bAllowScroll = DoAutoScroll();
//STRIP001          if ( bAllowScroll )
//STRIP001          {
//STRIP001              long nScrollX = 0;
//STRIP001              long nScrollY = 0;
//STRIP001              // pruefen, ob im sensitiven Bereich
//STRIP001              if ( ( (aMousePos.X()-pDragAndDropInfo->nSensibleRange) < GetOutputArea().Left() ) && ( ( aMousePos.X() + pDragAndDropInfo->nSensibleRange ) > GetOutputArea().Left() ) )
//STRIP001                      nScrollX = GetOutputArea().GetWidth() / SCRLRANGE;
//STRIP001              else if ( ( (aMousePos.X()+pDragAndDropInfo->nSensibleRange) > GetOutputArea().Right() ) && ( ( aMousePos.X() - pDragAndDropInfo->nSensibleRange ) < GetOutputArea().Right() ) )
//STRIP001                      nScrollX = -( GetOutputArea().GetWidth() / SCRLRANGE );
//STRIP001
//STRIP001              if ( ( (aMousePos.Y()-pDragAndDropInfo->nSensibleRange) < GetOutputArea().Top() ) && ( ( aMousePos.Y() + pDragAndDropInfo->nSensibleRange ) > GetOutputArea().Top() ) )
//STRIP001                      nScrollY = GetOutputArea().GetHeight() / SCRLRANGE;
//STRIP001              else if ( ( (aMousePos.Y()+pDragAndDropInfo->nSensibleRange) > GetOutputArea().Bottom() ) && ( ( aMousePos.Y() - pDragAndDropInfo->nSensibleRange ) < GetOutputArea().Bottom() ) )
//STRIP001                      nScrollY = -( GetOutputArea().GetHeight() / SCRLRANGE );
//STRIP001
//STRIP001              if ( nScrollX || nScrollY )
//STRIP001              {
//STRIP001                  HideDDCursor();
//STRIP001                  Scroll( nScrollX, nScrollY, RGCHK_PAPERSZ1 );
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          Point aDocPos( GetDocPos( aMousePos ) );
//STRIP001          EditPaM aPaM = pEditEngine->pImpEditEngine->GetPaM( aDocPos );
//STRIP001          pDragAndDropInfo->aDropDest = aPaM;
//STRIP001             if ( pDragAndDropInfo->bOutlinerMode )
//STRIP001             {
//STRIP001                 USHORT nPara = pEditEngine->pImpEditEngine->aEditDoc.GetPos( aPaM.GetNode() );
//STRIP001              ParaPortion* pPPortion = pEditEngine->pImpEditEngine->GetParaPortions().SaveGetObject( nPara );
//STRIP001                 long nDestParaStartY = pEditEngine->pImpEditEngine->GetParaPortions().GetYOffset( pPPortion );
//STRIP001                 long nRel = aDocPos.Y() - nDestParaStartY;
//STRIP001                 if ( nRel < ( pPPortion->GetHeight() / 2 ) )
//STRIP001                 {
//STRIP001                     pDragAndDropInfo->nOutlinerDropDest = nPara;
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     pDragAndDropInfo->nOutlinerDropDest = nPara+1;
//STRIP001                 }
//STRIP001
//STRIP001                 if( ( pDragAndDropInfo->nOutlinerDropDest >= pDragAndDropInfo->aBeginDragSel.nStartPara ) &&
//STRIP001                     ( pDragAndDropInfo->nOutlinerDropDest <= (pDragAndDropInfo->aBeginDragSel.nEndPara+1) ) )
//STRIP001                 {
//STRIP001                     bAccept = FALSE;
//STRIP001                 }
//STRIP001             }
//STRIP001          else if ( HasSelection() )
//STRIP001          {
//STRIP001              // es darf nicht in eine Selektion gedroppt werden
//STRIP001              EPaM aP = pEditEngine->pImpEditEngine->CreateEPaM( aPaM );
//STRIP001              ESelection aDestSel( aP.nPara, aP.nIndex, aP.nPara, aP.nIndex);
//STRIP001              ESelection aCurSel = pEditEngine->pImpEditEngine->CreateESel( GetEditSelection() );
//STRIP001              aCurSel.Adjust();
//STRIP001              if ( !aDestSel.IsLess( aCurSel ) && !aDestSel.IsGreater( aCurSel ) )
//STRIP001              {
//STRIP001                     bAccept = FALSE;
//STRIP001              }
//STRIP001          }
//STRIP001             if ( bAccept )
//STRIP001             {
//STRIP001              Rectangle aEditCursor;
//STRIP001                 if ( pDragAndDropInfo->bOutlinerMode )
//STRIP001                 {
//STRIP001                     long nDDYPos;
//STRIP001                     if ( pDragAndDropInfo->nOutlinerDropDest < pEditEngine->pImpEditEngine->GetEditDoc().Count() )
//STRIP001                     {
//STRIP001                      ParaPortion* pPPortion = pEditEngine->pImpEditEngine->GetParaPortions().SaveGetObject( pDragAndDropInfo->nOutlinerDropDest );
//STRIP001                         nDDYPos = pEditEngine->pImpEditEngine->GetParaPortions().GetYOffset( pPPortion );
//STRIP001                     }
//STRIP001                     else
//STRIP001                     {
//STRIP001                         nDDYPos = pEditEngine->pImpEditEngine->GetTextHeight();
//STRIP001                     }
//STRIP001                     Point aStartPos( 0, nDDYPos );
//STRIP001                     aStartPos = GetWindowPos( aStartPos );
//STRIP001                     Point aEndPos( GetOutputArea().GetWidth(), nDDYPos );
//STRIP001                     aEndPos = GetWindowPos( aEndPos );
//STRIP001                  aEditCursor = GetWindow()->LogicToPixel( Rectangle( aStartPos, aEndPos ) );
//STRIP001                     if ( !pEditEngine->IsVertical() )
//STRIP001                     {
//STRIP001                         aEditCursor.Top()--;
//STRIP001                         aEditCursor.Bottom()++;
//STRIP001                     }
//STRIP001                     else
//STRIP001                     {
//STRIP001                         aEditCursor.Left()--;
//STRIP001                         aEditCursor.Right()++;
//STRIP001                     }
//STRIP001                  aEditCursor = GetWindow()->PixelToLogic( aEditCursor );
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                  aEditCursor = pEditEngine->pImpEditEngine->PaMtoEditCursor( aPaM );
//STRIP001                  Point aTopLeft( GetWindowPos( aEditCursor.TopLeft() ) );
//STRIP001                  aEditCursor.SetPos( aTopLeft );
//STRIP001                  aEditCursor.Right() = aEditCursor.Left() + pDragAndDropInfo->nCursorWidth;
//STRIP001                  aEditCursor = GetWindow()->LogicToPixel( aEditCursor );
//STRIP001                  aEditCursor = GetWindow()->PixelToLogic( aEditCursor );
//STRIP001                 }
//STRIP001
//STRIP001                 sal_Bool bCursorChanged = !pDragAndDropInfo->bVisCursor || ( pDragAndDropInfo->aCurCursor != aEditCursor );
//STRIP001              if ( bCursorChanged )
//STRIP001              {
//STRIP001                  HideDDCursor();
//STRIP001                  ShowDDCursor(aEditCursor );
//STRIP001              }
//STRIP001                 pDragAndDropInfo->bDragAccepted = TRUE;
//STRIP001                 rDTDE.Context->acceptDrag( rDTDE.DropAction );
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     if ( !bAccept )
//STRIP001     {
//STRIP001         HideDDCursor();
//STRIP001         pDragAndDropInfo->bDragAccepted = FALSE;
//STRIP001         rDTDE.Context->rejectDrag();
//STRIP001     }
//STRIP001 }

/*N*/ void ImpEditView::AddDragAndDropListeners()
/*N*/ {
/*N*/     Window* pWindow = GetWindow();
/*N*/     if ( !bActiveDragAndDropListener && pWindow && pWindow->GetDragGestureRecognizer().is() )
/*N*/     {
/*N*/         vcl::unohelper::DragAndDropWrapper* pDnDWrapper = new vcl::unohelper::DragAndDropWrapper( this );
/*N*/         mxDnDListener = pDnDWrapper;
/*N*/
/*N*/         uno::Reference< datatransfer::dnd::XDragGestureListener> xDGL( mxDnDListener, uno::UNO_QUERY );
/*N*/         pWindow->GetDragGestureRecognizer()->addDragGestureListener( xDGL );
/*N*/         uno::Reference< datatransfer::dnd::XDropTargetListener> xDTL( xDGL, uno::UNO_QUERY );
/*N*/         pWindow->GetDropTarget()->addDropTargetListener( xDTL );
/*N*/         pWindow->GetDropTarget()->setActive( sal_True );
/*N*/         pWindow->GetDropTarget()->setDefaultActions( datatransfer::dnd::DNDConstants::ACTION_COPY_OR_MOVE );
/*N*/
/*N*/         bActiveDragAndDropListener = TRUE;
/*N*/     }
/*N*/ }

/*N*/ void ImpEditView::RemoveDragAndDropListeners()
/*N*/ {
/*N*/     if ( bActiveDragAndDropListener && GetWindow() && GetWindow()->GetDragGestureRecognizer().is() )
/*N*/     {
/*N*/         uno::Reference< datatransfer::dnd::XDragGestureListener> xDGL( mxDnDListener, uno::UNO_QUERY );
/*N*/         GetWindow()->GetDragGestureRecognizer()->removeDragGestureListener( xDGL );
/*N*/         uno::Reference< datatransfer::dnd::XDropTargetListener> xDTL( xDGL, uno::UNO_QUERY );
/*N*/         GetWindow()->GetDropTarget()->removeDropTargetListener( xDTL );
/*N*/
/*N*/         if ( mxDnDListener.is() )
/*N*/         {
/*N*/             uno::Reference< lang::XEventListener> xEL( mxDnDListener, uno::UNO_QUERY );
/*N*/             xEL->disposing( lang::EventObject() );  // #95154# Empty Source means it's the Client
/*N*/             mxDnDListener.clear();
/*N*/         }
/*N*/
/*N*/         bActiveDragAndDropListener = FALSE;
/*N*/     }
/*N*/ }}
