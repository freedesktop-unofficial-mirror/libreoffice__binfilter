/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_impedit.cxx,v $
 *
 *  $Revision: 1.10 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:37:08 $
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
#include <editeng.hxx>











#ifndef _SVX_ITEMDATA_HXX
#include "itemdata.hxx"
#endif



#include <flditem.hxx>
#include <svtools/transfer.hxx>

namespace binfilter {


using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::linguistic2;

#define SCRLRANGE   20      // 1/20 der Breite/Hoehe scrollen, wenn im QueryDrop


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
/*N*/ }


/*N*/ void ImpEditView::SetEditSelection( const EditSelection& rEditSelection )
/*N*/ {
/*N*/   // #100856# set state before notification
/*N*/     aEditSelection = rEditSelection;
/*N*/
/*N*/     if ( pEditEngine->pImpEditEngine->GetNotifyHdl().IsSet() )
/*N*/     {
/*?*/         DBG_BF_ASSERT(0, "STRIP"); //STRIP001 EENotify aNotify( EE_NOTIFY_TEXTVIEWSELECTIONCHANGED );
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
/*?*/ }

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
