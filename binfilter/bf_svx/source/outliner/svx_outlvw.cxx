/*************************************************************************
 *
 *  $RCSfile: svx_outlvw.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:37 $
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

#include <outl_pch.hxx>

#pragma hdrstop

#ifndef _SFXSTYLE_HXX //autogen
#include <svtools/style.hxx>
#endif

#define _OUTLINER_CXX
#include <outliner.hxx>
#include <outleeng.hxx>
#include <paralist.hxx>
#include <outlundo.hxx>
#include <outlobj.hxx>
#include <flditem.hxx>
#include <flditem.hxx>
#include <eeitem.hxx>
#include <numitem.hxx>

#ifndef _SV_WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif

#ifndef _SFXITEMSET_HXX //autogen
#include <svtools/itemset.hxx>
#endif

#ifndef _EDITSTAT_HXX //autogen
#include <editstat.hxx>
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

//STRIP001 void OutlinerView::Paint( const Rectangle& rRect )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001
//STRIP001  // beim ersten Paint/KeyInput/Drop wird aus einem leeren Outliner ein
//STRIP001  // Outliner mit genau einem Absatz
//STRIP001  if( pOwner->bFirstParaIsEmpty )
//STRIP001      pOwner->Insert( String() );
//STRIP001
//STRIP001  pEditView->Paint( rRect );
//STRIP001 }

//STRIP001 BOOL OutlinerView::PostKeyEvent( const KeyEvent& rKEvt )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( OutlinerView, 0 );
//STRIP001
//STRIP001  // beim ersten Paint/KeyInput/Drop wird aus einem leeren Outliner ein
//STRIP001  // Outliner mit genau einem Absatz
//STRIP001  if( pOwner->bFirstParaIsEmpty )
//STRIP001      pOwner->Insert( String() );
//STRIP001
//STRIP001
//STRIP001  BOOL bKeyProcessed = FALSE;
//STRIP001  ESelection aSel( pEditView->GetSelection() );
//STRIP001  BOOL bSelection = aSel.HasRange();
//STRIP001  KeyCode aKeyCode = rKEvt.GetKeyCode();
//STRIP001  KeyFuncType eFunc = aKeyCode.GetFunction();
//STRIP001  USHORT nCode = aKeyCode.GetCode();
//STRIP001  BOOL bReadOnly = IsReadOnly();
//STRIP001
//STRIP001  if( bSelection && ( nCode != KEY_TAB ) && EditEngine::DoesKeyChangeText( rKEvt ) )
//STRIP001  {
//STRIP001      if ( ImpCalcSelectedPages( FALSE ) && !pOwner->ImpCanDeleteSelectedPages( this ) )
//STRIP001          return TRUE;
//STRIP001  }
//STRIP001
//STRIP001  if ( eFunc != KEYFUNC_DONTKNOW )
//STRIP001  {
//STRIP001      switch ( eFunc )
//STRIP001      {
//STRIP001          case KEYFUNC_CUT:
//STRIP001          {
//STRIP001              if ( !bReadOnly )
//STRIP001              {
//STRIP001                  Cut();
//STRIP001                  bKeyProcessed = TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001          case KEYFUNC_COPY:
//STRIP001          {
//STRIP001              Copy();
//STRIP001              bKeyProcessed = TRUE;
//STRIP001          }
//STRIP001          break;
//STRIP001          case KEYFUNC_PASTE:
//STRIP001          {
//STRIP001              if ( !bReadOnly )
//STRIP001              {
//STRIP001                  PasteSpecial();
//STRIP001                  bKeyProcessed = TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001          case KEYFUNC_DELETE:
//STRIP001          {
//STRIP001              if( !bReadOnly && !bSelection && ( pOwner->ImplGetOutlinerMode() != OUTLINERMODE_TEXTOBJECT ) )
//STRIP001              {
//STRIP001                  if( aSel.nEndPos == pOwner->pEditEngine->GetTextLen( aSel.nEndPara ) )
//STRIP001                  {
//STRIP001                      Paragraph* pNext = pOwner->pParaList->GetParagraph( aSel.nEndPara+1 );
//STRIP001                      if( pNext && pNext->GetDepth() == 0 )
//STRIP001                      {
//STRIP001                          if( !pOwner->ImpCanDeleteSelectedPages( this, aSel.nEndPara, 1 ) )
//STRIP001                              return FALSE;
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001          default:    // wird dann evtl. unten bearbeitet.
//STRIP001                      eFunc = KEYFUNC_DONTKNOW;
//STRIP001      }
//STRIP001  }
//STRIP001  if ( eFunc == KEYFUNC_DONTKNOW )
//STRIP001  {
//STRIP001      switch ( nCode )
//STRIP001      {
//STRIP001          case KEY_TAB:
//STRIP001          {
//STRIP001              if ( !bReadOnly && !aKeyCode.IsMod1() && !aKeyCode.IsMod2() )
//STRIP001              {
//STRIP001                  if ( ( pOwner->ImplGetOutlinerMode() != OUTLINERMODE_TEXTOBJECT ) &&
//STRIP001                       ( pOwner->ImplGetOutlinerMode() != OUTLINERMODE_TITLEOBJECT ) &&
//STRIP001                       ( bSelection || !aSel.nStartPos ) )
//STRIP001                  {
//STRIP001                      Indent( aKeyCode.IsShift() ? (-1) : (+1) );
//STRIP001                      bKeyProcessed = TRUE;
//STRIP001                  }
//STRIP001                  else if ( ( pOwner->ImplGetOutlinerMode() == OUTLINERMODE_TEXTOBJECT ) &&
//STRIP001                            !bSelection && !aSel.nEndPos && pOwner->ImplHasBullet( aSel.nEndPara ) )
//STRIP001                  {
//STRIP001                      Indent( aKeyCode.IsShift() ? (-1) : (+1) );
//STRIP001                      bKeyProcessed = TRUE;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001          case KEY_BACKSPACE:
//STRIP001          {
//STRIP001              if( !bReadOnly && !bSelection && aSel.nEndPara && !aSel.nEndPos )
//STRIP001              {
//STRIP001                  Paragraph* pPara = pOwner->pParaList->GetParagraph( aSel.nEndPara );
//STRIP001                  Paragraph* pPrev = pOwner->pParaList->GetParagraph( aSel.nEndPara-1 );
//STRIP001                  if( !pPrev->IsVisible()  )
//STRIP001                      return TRUE;
//STRIP001                  if( !pPara->GetDepth() )
//STRIP001                  {
//STRIP001                      if(!pOwner->ImpCanDeleteSelectedPages(this, aSel.nEndPara , 1 ) )
//STRIP001                          return TRUE;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001          case KEY_RETURN:
//STRIP001          {
//STRIP001              if ( !bReadOnly )
//STRIP001              {
//STRIP001                  // Sonderbehandlung: Hartes Return am Ende eines Absatzes,
//STRIP001                  // der eingeklappte Unterabsaetze besitzt
//STRIP001                  Paragraph* pPara = pOwner->pParaList->GetParagraph( aSel.nEndPara );
//STRIP001
//STRIP001                  if( !aKeyCode.IsShift() )
//STRIP001                  {
//STRIP001                      // Nochmal ImpGetCursor ???
//STRIP001                      if( !bSelection &&
//STRIP001                              aSel.nEndPos == pOwner->pEditEngine->GetTextLen( aSel.nEndPara ) )
//STRIP001                      {
//STRIP001                          ULONG nChilds = pOwner->pParaList->GetChildCount(pPara);
//STRIP001                          if( nChilds && !pOwner->pParaList->HasVisibleChilds(pPara))
//STRIP001                          {
//STRIP001                              pOwner->UndoActionStart( OLUNDO_INSERT );
//STRIP001                              ULONG nTemp = aSel.nEndPara;
//STRIP001                              nTemp += nChilds;
//STRIP001                              nTemp++; // einfuegen ueber naechstem Non-Child
//STRIP001                              pOwner->Insert( String(),nTemp,pPara->GetDepth());
//STRIP001                              // Cursor positionieren
//STRIP001                              ESelection aTmpSel((USHORT)nTemp,0,(USHORT)nTemp,0);
//STRIP001                              pEditView->SetSelection( aTmpSel );
//STRIP001                              pEditView->ShowCursor( TRUE, TRUE );
//STRIP001                              pOwner->UndoActionEnd( OLUNDO_INSERT );
//STRIP001                              bKeyProcessed = TRUE;
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001                  if( !bKeyProcessed && !bSelection &&
//STRIP001                              !aKeyCode.IsShift() && aKeyCode.IsMod1() &&
//STRIP001                          ( aSel.nEndPos == pOwner->pEditEngine->GetTextLen(aSel.nEndPara) ) )
//STRIP001                  {
//STRIP001                      pOwner->UndoActionStart( OLUNDO_INSERT );
//STRIP001                      ULONG nTemp = aSel.nEndPara;
//STRIP001                      nTemp++;
//STRIP001                      pOwner->Insert( String(), nTemp, pPara->GetDepth()+1 );
//STRIP001
//STRIP001                      // Cursor positionieren
//STRIP001                      ESelection aTmpSel((USHORT)nTemp,0,(USHORT)nTemp,0);
//STRIP001                      pEditView->SetSelection( aTmpSel );
//STRIP001                      pEditView->ShowCursor( TRUE, TRUE );
//STRIP001                      pOwner->UndoActionEnd( OLUNDO_INSERT );
//STRIP001                      bKeyProcessed = TRUE;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return bKeyProcessed ? TRUE : pEditView->PostKeyEvent( rKEvt );
//STRIP001 }


//STRIP001 ULONG OutlinerView::ImpCheckMousePos(const Point& rPosPix, MouseTarget& reTarget)
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  ULONG nPara = EE_PARA_NOT_FOUND;
//STRIP001
//STRIP001  Point aMousePosWin = pEditView->GetWindow()->PixelToLogic( rPosPix );
//STRIP001  if( !pEditView->GetOutputArea().IsInside( aMousePosWin ) )
//STRIP001     {
//STRIP001      reTarget = MouseOutside;
//STRIP001     }
//STRIP001  else
//STRIP001  {
//STRIP001      reTarget = MouseText;
//STRIP001
//STRIP001      Point aPaperPos( aMousePosWin );
//STRIP001      Rectangle aOutArea = pEditView->GetOutputArea();
//STRIP001      Rectangle aVisArea = pEditView->GetVisArea();
//STRIP001      aPaperPos.X() -= aOutArea.Left();
//STRIP001      aPaperPos.X() += aVisArea.Left();
//STRIP001      aPaperPos.Y() -= aOutArea.Top();
//STRIP001      aPaperPos.Y() += aVisArea.Top();
//STRIP001
//STRIP001         BOOL bBullet;
//STRIP001         if ( pOwner->IsTextPos( aPaperPos, 0, &bBullet ) )
//STRIP001         {
//STRIP001          Point aDocPos = pOwner->GetDocPos( aPaperPos );
//STRIP001          nPara = pOwner->pEditEngine->FindParagraph( aDocPos.Y() );
//STRIP001
//STRIP001             if ( bBullet )
//STRIP001             {
//STRIP001                 reTarget = MouseBullet;
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 // Check for hyperlink
//STRIP001              const SvxFieldItem* pFieldItem = pEditView->GetField( aMousePosWin );
//STRIP001              if ( pFieldItem && pFieldItem->GetField() && pFieldItem->GetField()->ISA( SvxURLField ) )
//STRIP001                  reTarget = MouseHypertext;
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001  return nPara;
//STRIP001 }

//STRIP001 BOOL __EXPORT OutlinerView::MouseMove( const MouseEvent& rMEvt )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001
//STRIP001     if( ( pOwner->ImplGetOutlinerMode() == OUTLINERMODE_TEXTOBJECT ) || pEditView->GetEditEngine()->IsInSelectionMode())
//STRIP001      return pEditView->MouseMove( rMEvt );
//STRIP001
//STRIP001  Point aMousePosWin( pEditView->GetWindow()->PixelToLogic( rMEvt.GetPosPixel() ) );
//STRIP001  if( !pEditView->GetOutputArea().IsInside( aMousePosWin ) )
//STRIP001         return FALSE;
//STRIP001
//STRIP001     Pointer aPointer = GetPointer( rMEvt.GetPosPixel() );
//STRIP001     pEditView->GetWindow()->SetPointer( aPointer );
//STRIP001     return pEditView->MouseMove( rMEvt );
//STRIP001 }


//STRIP001 BOOL __EXPORT OutlinerView::MouseButtonDown( const MouseEvent& rMEvt )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  if ( ( pOwner->ImplGetOutlinerMode() == OUTLINERMODE_TEXTOBJECT ) || pEditView->GetEditEngine()->IsInSelectionMode() )
//STRIP001      return pEditView->MouseButtonDown( rMEvt );
//STRIP001
//STRIP001  Point aMousePosWin( pEditView->GetWindow()->PixelToLogic( rMEvt.GetPosPixel() ) );
//STRIP001  if( !pEditView->GetOutputArea().IsInside( aMousePosWin ) )
//STRIP001         return FALSE;
//STRIP001
//STRIP001  Pointer aPointer = GetPointer( rMEvt.GetPosPixel() );
//STRIP001     pEditView->GetWindow()->SetPointer( aPointer );
//STRIP001
//STRIP001  MouseTarget eTarget;
//STRIP001  ULONG nPara = ImpCheckMousePos( rMEvt.GetPosPixel(), eTarget );
//STRIP001     if ( eTarget == MouseBullet )
//STRIP001  {
//STRIP001      Paragraph* pPara = pOwner->pParaList->GetParagraph( nPara );
//STRIP001      BOOL bHasChilds = (pPara && pOwner->pParaList->HasChilds(pPara));
//STRIP001      if( rMEvt.GetClicks() == 1 )
//STRIP001      {
//STRIP001          ULONG nEndPara = nPara;
//STRIP001          if ( bHasChilds && pOwner->pParaList->HasVisibleChilds(pPara) )
//STRIP001              nEndPara += pOwner->pParaList->GetChildCount( pPara );
//STRIP001          // umgekehrt rum selektieren, damit EditEngine nicht scrollt
//STRIP001          ESelection aSel((USHORT)nEndPara, 0xffff,(USHORT)nPara, 0 );
//STRIP001          pEditView->SetSelection( aSel );
//STRIP001         }
//STRIP001      else if( rMEvt.GetClicks() == 2 && bHasChilds )
//STRIP001          ImpToggleExpand( pPara );
//STRIP001
//STRIP001      aDDStartPosPix = rMEvt.GetPosPixel();
//STRIP001      aDDStartPosRef=pEditView->GetWindow()->PixelToLogic( aDDStartPosPix,pOwner->GetRefMapMode());
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  return pEditView->MouseButtonDown( rMEvt );
//STRIP001 }


//STRIP001 BOOL __EXPORT OutlinerView::MouseButtonUp( const MouseEvent& rMEvt )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  if ( ( pOwner->ImplGetOutlinerMode() == OUTLINERMODE_TEXTOBJECT ) || pEditView->GetEditEngine()->IsInSelectionMode() )
//STRIP001      return pEditView->MouseButtonUp( rMEvt );
//STRIP001
//STRIP001  Point aMousePosWin( pEditView->GetWindow()->PixelToLogic( rMEvt.GetPosPixel() ) );
//STRIP001  if( !pEditView->GetOutputArea().IsInside( aMousePosWin ) )
//STRIP001         return FALSE;
//STRIP001
//STRIP001     Pointer aPointer = GetPointer( rMEvt.GetPosPixel() );
//STRIP001     pEditView->GetWindow()->SetPointer( aPointer );
//STRIP001
//STRIP001     return pEditView->MouseButtonUp( rMEvt );
//STRIP001 }

//STRIP001 void OutlinerView::ImpHideDDCursor()
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  if ( bDDCursorVisible )
//STRIP001  {
//STRIP001      bDDCursorVisible = FALSE;
//STRIP001      ImpPaintDDCursor();
//STRIP001  }
//STRIP001 }

//STRIP001 void OutlinerView::ImpShowDDCursor()
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  if ( !bDDCursorVisible )
//STRIP001  {
//STRIP001      bDDCursorVisible = TRUE;
//STRIP001      ImpPaintDDCursor();
//STRIP001  }
//STRIP001 }

//STRIP001 void OutlinerView::ImpPaintDDCursor()
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001
//STRIP001  Window* pWindow = pEditView->GetWindow();
//STRIP001  RasterOp eOldOp = pWindow->GetRasterOp();
//STRIP001  pWindow->SetRasterOp( ROP_INVERT );
//STRIP001
//STRIP001  const Color& rOldLineColor = pWindow->GetLineColor();
//STRIP001  pWindow->SetLineColor( Color( COL_BLACK ) );
//STRIP001
//STRIP001  Point aStartPointWin, aEndPointWin;
//STRIP001  Rectangle aOutputArWin = pEditView->GetOutputArea();
//STRIP001  Rectangle aVisAreaRef = pEditView->GetVisArea();
//STRIP001
//STRIP001  if( bDDChangingDepth )
//STRIP001  {
//STRIP001      aStartPointWin.X() = pHorTabArrDoc[ nDDCurDepth ];
//STRIP001      aStartPointWin.X() += aOutputArWin.Left();
//STRIP001      aStartPointWin.Y() = aOutputArWin.Top();
//STRIP001      aEndPointWin.X() = aStartPointWin.X();
//STRIP001      aEndPointWin.Y() = aOutputArWin.Bottom();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      ULONG nPara = nDDCurPara;
//STRIP001      if ( nDDCurPara == LIST_APPEND )
//STRIP001      {
//STRIP001          Paragraph* pTemp = pOwner->pParaList->LastVisible();
//STRIP001          nPara = pOwner->pParaList->GetAbsPos( pTemp );
//STRIP001      }
//STRIP001      aStartPointWin = pEditView->GetWindowPosTopLeft((USHORT) nPara );
//STRIP001      if ( nDDCurPara == LIST_APPEND )
//STRIP001      {
//STRIP001          long nHeight = pOwner->pEditEngine->GetTextHeight((USHORT)nPara );
//STRIP001          aStartPointWin.Y() += nHeight;
//STRIP001      }
//STRIP001      aStartPointWin.X() = aOutputArWin.Left();
//STRIP001      aEndPointWin.Y() = aStartPointWin.Y();
//STRIP001      aEndPointWin.X() = aOutputArWin.Right();
//STRIP001  }
//STRIP001
//STRIP001  pWindow->DrawLine( aStartPointWin, aEndPointWin );
//STRIP001  pWindow->SetLineColor( rOldLineColor );
//STRIP001  pWindow->SetRasterOp( eOldOp );
//STRIP001 }

// Berechnet, ueber welchem Absatz eingefuegt werden muss

//STRIP001 ULONG OutlinerView::ImpGetInsertionPara( const Point& rPosPixel  )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  ULONG nCurPara = pEditView->GetParagraph( rPosPixel );
//STRIP001  ParagraphList* pParaList = pOwner->pParaList;
//STRIP001
//STRIP001  if ( nCurPara == EE_PARA_NOT_FOUND )
//STRIP001      nCurPara = LIST_APPEND;
//STRIP001  else
//STRIP001  {
//STRIP001      Point aPosWin = pEditView->GetWindow()->PixelToLogic( rPosPixel );
//STRIP001      Point aParaPosWin = pEditView->GetWindowPosTopLeft((USHORT)nCurPara);
//STRIP001      long nHeightRef = pOwner->pEditEngine->GetTextHeight((USHORT)nCurPara);
//STRIP001      long nParaYOffs = aPosWin.Y() - aParaPosWin.Y();
//STRIP001
//STRIP001      if ( nParaYOffs > nHeightRef / 2  )
//STRIP001      {
//STRIP001          Paragraph* p = pParaList->GetParagraph( nCurPara );
//STRIP001          p = pParaList->NextVisible( p );
//STRIP001          nCurPara = p ? pParaList->GetAbsPos( p ) : LIST_APPEND;
//STRIP001      }
//STRIP001  }
//STRIP001  return nCurPara;
//STRIP001 }


//STRIP001 void OutlinerView::ImpToggleExpand( Paragraph* pPara )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001
//STRIP001  USHORT nPara = (USHORT) pOwner->pParaList->GetAbsPos( pPara );
//STRIP001  pEditView->SetSelection( ESelection( nPara, 0, nPara, 0 ) );
//STRIP001  ImplExpandOrCollaps( nPara, nPara, !pOwner->pParaList->HasVisibleChilds( pPara ) );
//STRIP001  pEditView->ShowCursor();
//STRIP001 }


//STRIP001 void OutlinerView::SetOutliner( Outliner* pOutliner )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pOwner = pOutliner;
//STRIP001  pEditView->SetEditEngine( pOutliner->pEditEngine );
//STRIP001 }


//STRIP001 ULONG OutlinerView::Select( Paragraph* pParagraph, BOOL bSelect,
//STRIP001  BOOL bWithChilds )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001
//STRIP001  ULONG nPara = pOwner->pParaList->GetAbsPos( pParagraph );
//STRIP001  USHORT nEnd = 0;
//STRIP001  if ( bSelect )
//STRIP001      nEnd = 0xffff;
//STRIP001
//STRIP001  ULONG nChildCount = 0;
//STRIP001  if ( bWithChilds )
//STRIP001      nChildCount = pOwner->pParaList->GetChildCount( pParagraph );
//STRIP001
//STRIP001  ESelection aSel( (USHORT)nPara, 0,(USHORT)(nPara+nChildCount), nEnd );
//STRIP001  pEditView->SetSelection( aSel );
//STRIP001  return nChildCount+1;
//STRIP001 }


//STRIP001 void OutlinerView::SetAttribs( const SfxItemSet& rAttrs )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001
//STRIP001  BOOL bUpdate = pOwner->pEditEngine->GetUpdateMode();
//STRIP001  pOwner->pEditEngine->SetUpdateMode( FALSE );
//STRIP001
//STRIP001  if( !pOwner->IsInUndo() && pOwner->IsUndoEnabled() )
//STRIP001      pOwner->UndoActionStart( OLUNDO_ATTR );
//STRIP001
//STRIP001  ParaRange aSel = ImpGetSelectedParagraphs( FALSE );
//STRIP001
//STRIP001  if ( rAttrs.GetItemState( EE_PARA_LRSPACE) == SFX_ITEM_ON )
//STRIP001  {
//STRIP001      // Erstmal ohne LRSpace einstellen, damit Konvertierung ins
//STRIP001      // NumBulletItem nur dann, wenn geaendert.
//STRIP001      SfxItemSet aSet( rAttrs );
//STRIP001      aSet.ClearItem( EE_PARA_LRSPACE );
//STRIP001      pEditView->SetAttribs( aSet );
//STRIP001
//STRIP001      // Jetzt ggf. LRSpace in NumBulletItem mergen...
//STRIP001      EditEngine* pEditEng = pOwner->pEditEngine;
//STRIP001      const SvxLRSpaceItem& rLR = (const SvxLRSpaceItem&) rAttrs.Get( EE_PARA_LRSPACE );
//STRIP001      for ( USHORT n = aSel.nStartPara; n <= aSel.nEndPara; n++ )
//STRIP001      {
//STRIP001          SfxItemSet aAttribs = pEditEng->GetParaAttribs( n );
//STRIP001          if ( !( rLR == pEditEng->GetParaAttrib( (USHORT)n, EE_PARA_LRSPACE ) ) )
//STRIP001          {
//STRIP001                 // Use Item from Style/ParaAttribs, ImplGetNumBulletItem could return a pool default in OutlineView on Level 0
//STRIP001              const SvxNumBulletItem& rNumBullet = (const SvxNumBulletItem&)pEditEng->GetParaAttrib( (USHORT)n, EE_PARA_NUMBULLET );
//STRIP001              Paragraph* pPara = pOwner->pParaList->GetParagraph( n );
//STRIP001              if ( rNumBullet.GetNumRule()->GetLevelCount() > pPara->GetDepth() )
//STRIP001              {
//STRIP001                  SvxNumBulletItem* pNewNumBullet = (SvxNumBulletItem*) rNumBullet.Clone();
//STRIP001                  EditEngine::ImportBulletItem( *pNewNumBullet, pPara->GetDepth(), NULL, &rLR );
//STRIP001                  aAttribs.Put( *pNewNumBullet );
//STRIP001                  delete pNewNumBullet;
//STRIP001              }
//STRIP001          }
//STRIP001          aAttribs.Put( rLR );
//STRIP001          pEditEng->SetParaAttribs( (USHORT)n, aAttribs );
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pEditView->SetAttribs( rAttrs );
//STRIP001  }
//STRIP001
//STRIP001  // Bullet-Texte aktualisieren
//STRIP001  for( USHORT nPara= aSel.nStartPara; nPara <= aSel.nEndPara; nPara++ )
//STRIP001  {
//STRIP001      pOwner->ImplCheckNumBulletItem( nPara );
//STRIP001      pOwner->ImplCalcBulletText( nPara, FALSE, FALSE );
//STRIP001
//STRIP001 #ifndef SVX_LIGHT
//STRIP001      if( !pOwner->IsInUndo() && pOwner->IsUndoEnabled() )
//STRIP001          pOwner->InsertUndo( new OutlinerUndoCheckPara( pOwner, nPara ) );
//STRIP001 #endif
//STRIP001  }
//STRIP001
//STRIP001  if( !pOwner->IsInUndo() && pOwner->IsUndoEnabled() )
//STRIP001      pOwner->UndoActionEnd( OLUNDO_ATTR );
//STRIP001
//STRIP001  pEditView->SetEditEngineUpdateMode( bUpdate );
//STRIP001 }

//STRIP001 ParaRange OutlinerView::ImpGetSelectedParagraphs( BOOL bIncludeHiddenChilds )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( OutlinerView, 0 );
//STRIP001
//STRIP001  ESelection aSel = pEditView->GetSelection();
//STRIP001  ParaRange aParas( aSel.nStartPara, aSel.nEndPara );
//STRIP001  aParas.Adjust();
//STRIP001
//STRIP001  // unsichtbare Childs des letzten Parents in Selektion mit aufnehmen
//STRIP001  if ( bIncludeHiddenChilds )
//STRIP001  {
//STRIP001      Paragraph* pLast = pOwner->pParaList->GetParagraph( aParas.nEndPara );
//STRIP001      if ( pOwner->pParaList->HasHiddenChilds( pLast ) )
//STRIP001          aParas.nEndPara += (USHORT) pOwner->pParaList->GetChildCount( pLast );
//STRIP001  }
//STRIP001  return aParas;
//STRIP001 }

// MT: Name sollte mal geaendert werden!
//STRIP001 void OutlinerView::AdjustDepth( short nDX )
//STRIP001 {
//STRIP001  Indent( nDX );
//STRIP001 }

//STRIP001 void OutlinerView::Indent( short nDiff )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( OutlinerView, 0 );
//STRIP001
//STRIP001  if( !nDiff || ( ( nDiff > 0 ) && ImpCalcSelectedPages( TRUE ) && !pOwner->ImpCanIndentSelectedPages( this ) ) )
//STRIP001      return;
//STRIP001
//STRIP001  BOOL bUpdate = pOwner->pEditEngine->GetUpdateMode();
//STRIP001  pOwner->pEditEngine->SetUpdateMode( FALSE );
//STRIP001
//STRIP001  BOOL bUndo = !pOwner->IsInUndo() && pOwner->IsUndoEnabled();
//STRIP001
//STRIP001  if( bUndo )
//STRIP001      pOwner->UndoActionStart( OLUNDO_DEPTH );
//STRIP001
//STRIP001  USHORT nMinDepth = 0xFFFF;  // Optimierung: Nicht unnoetig viele Absatze neu berechnen
//STRIP001
//STRIP001  ParaRange aSel = ImpGetSelectedParagraphs( TRUE );
//STRIP001  for ( USHORT nPara = aSel.nStartPara; nPara <= aSel.nEndPara; nPara++ )
//STRIP001  {
//STRIP001      Paragraph* pPara = pOwner->pParaList->GetParagraph( nPara );
//STRIP001      if ( !nPara && !pPara->GetDepth() && ( pOwner->ImplGetOutlinerMode() != OUTLINERMODE_TEXTOBJECT ) )
//STRIP001      {
//STRIP001          // Seite 0 nicht einruecken.
//STRIP001          // Absatz muss neu gepaintet werden (wg. doppeltem Highlight beim Painten der Selektion )
//STRIP001          pOwner->pEditEngine->QuickMarkInvalid( ESelection( 0, 0, 0, 0 ) );
//STRIP001          continue;
//STRIP001      }
//STRIP001
//STRIP001      USHORT nOldDepth = pPara->GetDepth();
//STRIP001      USHORT nNewDepth = nOldDepth + nDiff;
//STRIP001      if ( ( nDiff < 0 ) && ( nOldDepth < (-nDiff) ) )
//STRIP001          nNewDepth = 0;
//STRIP001
//STRIP001      if ( nNewDepth < pOwner->nMinDepth )
//STRIP001          nNewDepth = pOwner->nMinDepth;
//STRIP001      if ( nNewDepth > pOwner->nMaxDepth )
//STRIP001          nNewDepth = pOwner->nMaxDepth;
//STRIP001
//STRIP001      if( nOldDepth < nMinDepth )
//STRIP001          nMinDepth = nOldDepth;
//STRIP001      if( nNewDepth < nMinDepth )
//STRIP001          nMinDepth = nNewDepth;
//STRIP001
//STRIP001      if( nOldDepth != nNewDepth )
//STRIP001      {
//STRIP001          if ( ( nPara == aSel.nStartPara ) && aSel.nStartPara && ( pOwner->ImplGetOutlinerMode() != OUTLINERMODE_TEXTOBJECT ))
//STRIP001          {
//STRIP001              // Sonderfall: Der Vorgaenger eines eingerueckten Absatzes ist
//STRIP001              // unsichtbar und steht jetzt auf der gleichen Ebene wie der
//STRIP001              // sichtbare Absatz. In diesem Fall wird der naechste sichtbare
//STRIP001              // Absatz gesucht und aufgeplustert.
//STRIP001              Paragraph* pPara = pOwner->pParaList->GetParagraph( aSel.nStartPara );
//STRIP001              DBG_ASSERT(pPara->IsVisible(),"Selected Paragraph invisible ?!")
//STRIP001
//STRIP001              Paragraph* pPrev= pOwner->pParaList->GetParagraph( aSel.nStartPara-1 );
//STRIP001
//STRIP001              if( !pPrev->IsVisible() && ( pPrev->GetDepth() == nNewDepth ) )
//STRIP001              {
//STRIP001                  // Vorgaenger ist eingeklappt und steht auf gleicher Ebene
//STRIP001                  // => naechsten sichtbaren Absatz suchen und expandieren
//STRIP001                  USHORT nDummy;
//STRIP001                  pPrev = pOwner->pParaList->GetParent( pPrev, nDummy );
//STRIP001                  while( !pPrev->IsVisible() )
//STRIP001                      pPrev = pOwner->pParaList->GetParent( pPrev, nDummy );
//STRIP001
//STRIP001                  pOwner->Expand( pPrev );
//STRIP001                  pOwner->InvalidateBullet( pPrev, pOwner->pParaList->GetAbsPos( pPrev ) );
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          pOwner->ImplInitDepth( nPara, nNewDepth, TRUE, FALSE );
//STRIP001          pOwner->ImplCalcBulletText( nPara, FALSE, FALSE );
//STRIP001
//STRIP001          if ( pOwner->ImplGetOutlinerMode() == OUTLINERMODE_OUTLINEOBJECT )
//STRIP001              pOwner->ImplSetLevelDependendStyleSheet( nPara );
//STRIP001
//STRIP001          // App benachrichtigen
//STRIP001          pOwner->nDepthChangedHdlPrevDepth = (USHORT)nOldDepth;
//STRIP001          pOwner->pHdlParagraph = pPara;
//STRIP001          pOwner->DepthChangedHdl();
//STRIP001      }
//STRIP001         else
//STRIP001         {
//STRIP001             // Needs at least a repaint...
//STRIP001             pOwner->pEditEngine->QuickMarkInvalid( ESelection( nPara, 0, nPara, 0 ) );
//STRIP001         }
//STRIP001  }
//STRIP001
//STRIP001  // MT 19.08.99: War mal fuer Optimierung (outliner.cxx#1.193),
//STRIP001  // hat aber zu zuviel Wartungsaufwand / doppelten Funktionen gefuehrt
//STRIP001  // und zu wenig gebracht:
//STRIP001  // pOwner->ImpSetBulletTextsFrom( aSel.nStartPara+1, nMinDepth );
//STRIP001  // Wird jetzt direkt in Schleife mit ImplCalcBulletText() erledigt.
//STRIP001  // Jetzt fehlen nur noch die folgenden Ansaetze, die davon betroffen sind.
//STRIP001  USHORT nParas = (USHORT)pOwner->pParaList->GetParagraphCount();
//STRIP001  for ( USHORT n = aSel.nEndPara+1; n < nParas; n++ )
//STRIP001  {
//STRIP001      Paragraph* pPara = pOwner->pParaList->GetParagraph( n );
//STRIP001      if ( pPara->GetDepth() < nMinDepth )
//STRIP001          break;
//STRIP001      pOwner->ImplCalcBulletText( n, FALSE, FALSE );
//STRIP001  }
//STRIP001
//STRIP001  if ( bUpdate )
//STRIP001  {
//STRIP001      pEditView->SetEditEngineUpdateMode( TRUE );
//STRIP001      pEditView->ShowCursor();
//STRIP001  }
//STRIP001
//STRIP001  if( bUndo )
//STRIP001      pOwner->UndoActionEnd( OLUNDO_DEPTH );
//STRIP001 }

//STRIP001 BOOL OutlinerView::AdjustHeight( long nDY )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001     pEditView->MoveParagraphs( nDY );
//STRIP001     return TRUE;    // remove return value...
//STRIP001 }

//STRIP001 void OutlinerView::AdjustDepth( Paragraph* pPara, short nDX, BOOL bWithChilds)
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  ULONG nStartPara = pOwner->pParaList->GetAbsPos( pPara );
//STRIP001  ULONG nEndPara = nStartPara;
//STRIP001  if ( bWithChilds )
//STRIP001      nEndPara += pOwner->pParaList->GetChildCount( pPara );
//STRIP001  ESelection aSel((USHORT)nStartPara, 0,(USHORT)nEndPara, 0xffff );
//STRIP001  pEditView->SetSelection( aSel );
//STRIP001  AdjustDepth( nDX );
//STRIP001 }


//STRIP001 void OutlinerView::AdjustHeight( Paragraph* pPara, long nDY, BOOL bWithChilds )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  ULONG nStartPara = pOwner->pParaList->GetAbsPos( pPara );
//STRIP001  ULONG nEndPara = nStartPara;
//STRIP001  if ( bWithChilds )
//STRIP001      nEndPara += pOwner->pParaList->GetChildCount( pPara );
//STRIP001  ESelection aSel( (USHORT)nStartPara, 0, (USHORT)nEndPara, 0xffff );
//STRIP001  pEditView->SetSelection( aSel );
//STRIP001  AdjustHeight( nDY );
//STRIP001 }


/*N*/ Rectangle OutlinerView::GetVisArea() const
/*N*/ {
/*N*/   DBG_CHKTHIS(OutlinerView,0);
/*N*/   return pEditView->GetVisArea();
/*N*/ }


//STRIP001 Point OutlinerView::ImpGetDocPos( const Point& rPosPixel )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  Rectangle aOutArWin = GetOutputArea();
//STRIP001  // Position in der OutputArea berechnen
//STRIP001  Point aCurPosDoc( rPosPixel );
//STRIP001  aCurPosDoc = pEditView->GetWindow()->PixelToLogic( aCurPosDoc );
//STRIP001  aCurPosDoc -= aOutArWin.TopLeft();
//STRIP001  aCurPosDoc += pEditView->GetVisArea().TopLeft();
//STRIP001  return aCurPosDoc;
//STRIP001 }

// MT 05/00: Wofuer dies ImpXXXScroll, sollte das nicht die EditEngine machen???

//STRIP001 void OutlinerView::ImpDragScroll( const Point& rPosPix )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  Point aPosWin = pEditView->GetWindow()->PixelToLogic( rPosPix );
//STRIP001  Rectangle aOutputArWin = pEditView->GetOutputArea();
//STRIP001  if ( aPosWin.X() <= aOutputArWin.Left() + nDDScrollLRBorderWidthWin)
//STRIP001      ImpScrollLeft();
//STRIP001  else if( aPosWin.X() >= aOutputArWin.Right()- nDDScrollLRBorderWidthWin)
//STRIP001      ImpScrollRight();
//STRIP001  else if( aPosWin.Y() <= aOutputArWin.Top() + nDDScrollTBBorderWidthWin)
//STRIP001      ImpScrollUp();
//STRIP001  else if(aPosWin.Y() >= aOutputArWin.Bottom() - nDDScrollTBBorderWidthWin)
//STRIP001      ImpScrollDown();
//STRIP001 }


//STRIP001 void OutlinerView::ImpScrollLeft()
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  Rectangle aVisArea( pEditView->GetVisArea() );
//STRIP001  long nMaxScrollOffs = aVisArea.Left();
//STRIP001  if ( !nMaxScrollOffs )
//STRIP001      return;
//STRIP001  long nScrollOffsRef = (aVisArea.GetWidth() * OL_SCROLL_HOROFFSET) / 100;
//STRIP001  if ( !nScrollOffsRef )
//STRIP001      nScrollOffsRef = 1;
//STRIP001  if ( nScrollOffsRef > nMaxScrollOffs )
//STRIP001      nScrollOffsRef = nMaxScrollOffs;
//STRIP001
//STRIP001  ImpHideDDCursor();
//STRIP001  Scroll( -nScrollOffsRef, 0 );
//STRIP001
//STRIP001  EditStatus aScrollStat;
//STRIP001  aScrollStat.GetStatusWord() = EE_STAT_HSCROLL;
//STRIP001  pOwner->pEditEngine->GetStatusEventHdl().Call( &aScrollStat );
//STRIP001 }


//STRIP001 void OutlinerView::ImpScrollRight()
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  Rectangle aVisArea( pEditView->GetVisArea() );
//STRIP001  long nMaxScrollOffs = pOwner->pEditEngine->GetPaperSize().Width() -
//STRIP001                        aVisArea.Right();
//STRIP001  if ( !nMaxScrollOffs )
//STRIP001      return;
//STRIP001  long nScrollOffsRef = (aVisArea.GetWidth() * OL_SCROLL_HOROFFSET) / 100;
//STRIP001  if ( !nScrollOffsRef )
//STRIP001      nScrollOffsRef = 1;
//STRIP001  if ( nScrollOffsRef > nMaxScrollOffs )
//STRIP001      nScrollOffsRef = nMaxScrollOffs;
//STRIP001
//STRIP001  ImpHideDDCursor();
//STRIP001  Scroll( nScrollOffsRef, 0 );
//STRIP001
//STRIP001  EditStatus aScrollStat;
//STRIP001  aScrollStat.GetStatusWord() = EE_STAT_HSCROLL;
//STRIP001  pOwner->pEditEngine->GetStatusEventHdl().Call( &aScrollStat );
//STRIP001 }


//STRIP001 void OutlinerView::ImpScrollDown()
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  Rectangle aVisArea( pEditView->GetVisArea() );
//STRIP001  Size aDocSize( 0, (long)pOwner->pEditEngine->GetTextHeight() );
//STRIP001
//STRIP001  long nMaxScrollOffs = aDocSize.Height();
//STRIP001  nMaxScrollOffs -= aVisArea.Top();
//STRIP001  nMaxScrollOffs -= aVisArea.GetHeight();
//STRIP001  if ( !nMaxScrollOffs )
//STRIP001      return;
//STRIP001
//STRIP001  long nScrollOffsRef = (aVisArea.GetHeight() * OL_SCROLL_VEROFFSET) / 100;
//STRIP001
//STRIP001  if ( nScrollOffsRef > nMaxScrollOffs )
//STRIP001      nScrollOffsRef = nMaxScrollOffs;
//STRIP001  if ( !nScrollOffsRef )
//STRIP001      nScrollOffsRef = 1;
//STRIP001
//STRIP001  ImpHideDDCursor();
//STRIP001  Scroll( 0, -nScrollOffsRef );
//STRIP001
//STRIP001  EditStatus aScrollStat;
//STRIP001  aScrollStat.GetStatusWord() = EE_STAT_VSCROLL;
//STRIP001  pOwner->pEditEngine->GetStatusEventHdl().Call( &aScrollStat );
//STRIP001 }


//STRIP001 void OutlinerView::ImpScrollUp()
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  Rectangle aVisArea( pEditView->GetVisArea() );
//STRIP001  long nMaxScrollOffs = aVisArea.Top();
//STRIP001  if ( !nMaxScrollOffs )
//STRIP001      return;
//STRIP001  long nScrollOffsRef = (aVisArea.GetHeight() * OL_SCROLL_VEROFFSET) / 100;
//STRIP001
//STRIP001
//STRIP001  if ( nScrollOffsRef > nMaxScrollOffs )
//STRIP001      nScrollOffsRef = nMaxScrollOffs;
//STRIP001  if ( !nScrollOffsRef )
//STRIP001      nScrollOffsRef = 1;
//STRIP001
//STRIP001  ImpHideDDCursor();
//STRIP001  Scroll( 0, nScrollOffsRef );
//STRIP001
//STRIP001  EditStatus aScrollStat;
//STRIP001  aScrollStat.GetStatusWord() = EE_STAT_VSCROLL;
//STRIP001  pOwner->pEditEngine->GetStatusEventHdl().Call( &aScrollStat );
//STRIP001 }


//STRIP001 void OutlinerView::Expand()
//STRIP001 {
//STRIP001  DBG_CHKTHIS( OutlinerView, 0 );
//STRIP001  ParaRange aParas = ImpGetSelectedParagraphs( FALSE );
//STRIP001  ImplExpandOrCollaps( aParas.nStartPara, aParas.nEndPara, TRUE );
//STRIP001 }


//STRIP001 void OutlinerView::Collapse()
//STRIP001 {
//STRIP001  DBG_CHKTHIS( OutlinerView, 0 );
//STRIP001  ParaRange aParas = ImpGetSelectedParagraphs( FALSE );
//STRIP001  ImplExpandOrCollaps( aParas.nStartPara, aParas.nEndPara, FALSE );
//STRIP001 }


//STRIP001 void OutlinerView::ExpandAll()
//STRIP001 {
//STRIP001  DBG_CHKTHIS( OutlinerView, 0 );
//STRIP001  ImplExpandOrCollaps( 0, (USHORT)(pOwner->pParaList->GetParagraphCount()-1), TRUE );
//STRIP001 }


//STRIP001 void OutlinerView::CollapseAll()
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  ImplExpandOrCollaps( 0, (USHORT)(pOwner->pParaList->GetParagraphCount()-1), FALSE );
//STRIP001 }

//STRIP001 void OutlinerView::ImplExpandOrCollaps( USHORT nStartPara, USHORT nEndPara, BOOL bExpand )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( OutlinerView, 0 );
//STRIP001
//STRIP001  BOOL bUpdate = pOwner->GetUpdateMode();
//STRIP001  pOwner->SetUpdateMode( FALSE );
//STRIP001
//STRIP001  BOOL bUndo = !pOwner->IsInUndo() && pOwner->IsUndoEnabled();
//STRIP001  if( bUndo )
//STRIP001      pOwner->UndoActionStart( bExpand ? OLUNDO_EXPAND : OLUNDO_COLLAPSE );
//STRIP001
//STRIP001  for ( USHORT nPara = nStartPara; nPara <= nEndPara; nPara++ )
//STRIP001  {
//STRIP001      Paragraph* pPara = pOwner->pParaList->GetParagraph( nPara );
//STRIP001      BOOL bDone = bExpand ? pOwner->Expand( pPara ) : pOwner->Collapse( pPara );
//STRIP001      if( bDone )
//STRIP001      {
//STRIP001          // Der Strich unter dem Absatz muss verschwinden...
//STRIP001          pOwner->pEditEngine->QuickMarkToBeRepainted( nPara );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( bUndo )
//STRIP001      pOwner->UndoActionEnd( bExpand ? OLUNDO_EXPAND : OLUNDO_COLLAPSE );
//STRIP001
//STRIP001  if ( bUpdate )
//STRIP001  {
//STRIP001      pOwner->SetUpdateMode( TRUE );
//STRIP001      pEditView->ShowCursor();
//STRIP001  }
//STRIP001 }


//STRIP001 void OutlinerView::Expand( Paragraph* pPara)
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pOwner->Expand( pPara );
//STRIP001 }


//STRIP001 void OutlinerView::Collapse( Paragraph* pPara)
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pOwner->Collapse( pPara );
//STRIP001 }

//STRIP001 void OutlinerView::InsertText( const OutlinerParaObject& rParaObj )
//STRIP001 {
//STRIP001  // MT: Wie Paste, nur EditView::Insert, statt EditView::Paste.
//STRIP001  // Eigentlich nicht ganz richtig, das evtl. Einrueckungen
//STRIP001  // korrigiert werden muessen, aber das kommt spaeter durch ein
//STRIP001  // allgemeingueltiges Import.
//STRIP001  // Dann wird im Inserted gleich ermittelt, was fr eine Einrueckebene
//STRIP001  // Moegliche Struktur:
//STRIP001  // pImportInfo mit DestPara, DestPos, nFormat, pParaObj...
//STRIP001  // Evtl. Problematisch:
//STRIP001  // EditEngine, RTF => Absplittung des Bereichs, spaeter
//STRIP001  // zusammenfuehrung
//STRIP001
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001
//STRIP001  if ( ImpCalcSelectedPages( FALSE ) && !pOwner->ImpCanDeleteSelectedPages( this ) )
//STRIP001      return;
//STRIP001
//STRIP001  pOwner->UndoActionStart( OLUNDO_INSERT );
//STRIP001
//STRIP001  pOwner->pEditEngine->SetUpdateMode( FALSE );
//STRIP001  ULONG nStart, nParaCount;
//STRIP001  nParaCount = pOwner->pEditEngine->GetParagraphCount();
//STRIP001  USHORT nSize = ImpInitPaste( nStart );
//STRIP001  pEditView->InsertText( rParaObj.GetTextObject() );
//STRIP001  ImpPasted( nStart, nParaCount, nSize);
//STRIP001  pEditView->SetEditEngineUpdateMode( TRUE );
//STRIP001
//STRIP001  pOwner->UndoActionEnd( OLUNDO_INSERT );
//STRIP001
//STRIP001  pEditView->ShowCursor( TRUE, TRUE );
//STRIP001 }



/*N*/ void OutlinerView::Cut()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  if ( !ImpCalcSelectedPages( FALSE ) || pOwner->ImpCanDeleteSelectedPages( this ) )
//STRIP001      pEditView->Cut();
/*N*/ }

/*N*/ void OutlinerView::Paste()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  PasteSpecial(); // HACK(SD ruft nicht PasteSpecial auf)
/*N*/ }

//STRIP001 void OutlinerView::PasteSpecial()
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  if ( !ImpCalcSelectedPages( FALSE ) || pOwner->ImpCanDeleteSelectedPages( this ) )
//STRIP001  {
//STRIP001      pOwner->UndoActionStart( OLUNDO_INSERT );
//STRIP001
//STRIP001      pOwner->pEditEngine->SetUpdateMode( FALSE );
//STRIP001      ULONG nStart, nParaCount;
//STRIP001 //       nParaCount = pOwner->pEditEngine->GetParagraphCount();
//STRIP001         pOwner->bPasting = TRUE;
//STRIP001         pEditView->PasteSpecial();
//STRIP001 //       ImpPasted( nStart, nParaCount, nSize);
//STRIP001
//STRIP001         pEditView->SetEditEngineUpdateMode( TRUE );
//STRIP001      pOwner->UndoActionEnd( OLUNDO_INSERT );
//STRIP001      pEditView->ShowCursor( TRUE, TRUE );
//STRIP001  }
//STRIP001 }

//STRIP001 List* OutlinerView::CreateSelectionList()
//STRIP001 {
//STRIP001  DBG_CHKTHIS( OutlinerView, 0 );
//STRIP001
//STRIP001  ParaRange aParas = ImpGetSelectedParagraphs( TRUE );
//STRIP001  List* pSelList = new List;
//STRIP001  for ( USHORT nPara = aParas.nStartPara; nPara <= aParas.nEndPara; nPara++ )
//STRIP001  {
//STRIP001      Paragraph* pPara = pOwner->pParaList->GetParagraph( nPara );
//STRIP001      pSelList->Insert( pPara, LIST_APPEND );
//STRIP001  }
//STRIP001  return pSelList;
//STRIP001 }

//STRIP001 SfxStyleSheet* OutlinerView::GetStyleSheet() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  return pEditView->GetStyleSheet();
//STRIP001 }

/*N*/ void OutlinerView::SetStyleSheet( SfxStyleSheet* pStyle )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pEditView->SetStyleSheet( pStyle );
//STRIP001
//STRIP001  ParaRange aSel = ImpGetSelectedParagraphs( TRUE );
//STRIP001  for( USHORT nPara = aSel.nStartPara; nPara <= aSel.nEndPara; nPara++ )
//STRIP001  {
//STRIP001      pOwner->ImplCheckNumBulletItem( nPara );
//STRIP001      pOwner->ImplCalcBulletText( nPara, FALSE, FALSE );
//STRIP001  }
/*N*/ }

//STRIP001 Pointer OutlinerView::GetPointer( const Point& rPosPixel )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001
//STRIP001     MouseTarget eTarget;
//STRIP001  ImpCheckMousePos( rPosPixel, eTarget );
//STRIP001
//STRIP001     PointerStyle ePointerStyle = POINTER_ARROW;
//STRIP001     if ( eTarget == MouseText )
//STRIP001     {
//STRIP001         ePointerStyle = GetOutliner()->IsVertical() ? POINTER_TEXT_VERTICAL : POINTER_TEXT;
//STRIP001     }
//STRIP001     else if ( eTarget == MouseHypertext )
//STRIP001     {
//STRIP001         ePointerStyle = POINTER_REFHAND;
//STRIP001     }
//STRIP001     else if ( eTarget == MouseBullet )
//STRIP001     {
//STRIP001         ePointerStyle = POINTER_MOVE;
//STRIP001     }
//STRIP001
//STRIP001     return Pointer( ePointerStyle );
//STRIP001 }


//STRIP001 USHORT OutlinerView::ImpInitPaste( ULONG& rStart )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pOwner->bPasting = TRUE;
//STRIP001  ESelection aSelection( pEditView->GetSelection() );
//STRIP001  aSelection.Adjust();
//STRIP001  rStart = aSelection.nStartPara;
//STRIP001  USHORT nSize = aSelection.nEndPara - aSelection.nStartPara + 1;
//STRIP001  return nSize;
//STRIP001 }


//STRIP001 void OutlinerView::ImpPasted( ULONG nStart, ULONG nPrevParaCount, USHORT nSize)
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pOwner->bPasting = FALSE;
//STRIP001  ULONG nCurParaCount = (ULONG)pOwner->pEditEngine->GetParagraphCount();
//STRIP001  if( nCurParaCount < nPrevParaCount )
//STRIP001      nSize -= (USHORT)( nPrevParaCount - nCurParaCount );
//STRIP001  else
//STRIP001      nSize += (USHORT)( nCurParaCount - nPrevParaCount );
//STRIP001  pOwner->ImpTextPasted( nStart, nSize );
//STRIP001 }


//STRIP001 void OutlinerView::Command( const CommandEvent& rCEvt )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pEditView->Command( rCEvt );
//STRIP001 }


//STRIP001 void OutlinerView::SelectRange( ULONG nFirst, USHORT nCount )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  ULONG nLast = nFirst+nCount;
//STRIP001  nCount = (USHORT)pOwner->pParaList->GetParagraphCount();
//STRIP001  if( nLast <= nCount )
//STRIP001      nLast = nCount - 1;
//STRIP001  ESelection aSel( (USHORT)nFirst, 0, (USHORT)nLast, 0xffff );
//STRIP001  pEditView->SetSelection( aSel );
//STRIP001 }


//STRIP001 USHORT OutlinerView::ImpCalcSelectedPages( BOOL bIncludeFirstSelected )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001
//STRIP001  ESelection aSel( pEditView->GetSelection() );
//STRIP001  aSel.Adjust();
//STRIP001
//STRIP001  USHORT nPages = 0;
//STRIP001  USHORT nFirstPage = 0xFFFF;
//STRIP001  USHORT nStartPara = aSel.nStartPara;
//STRIP001  if ( !bIncludeFirstSelected )
//STRIP001      nStartPara++;   // alle nach StartPara kommenden Absaetze werden geloescht
//STRIP001  for ( USHORT nPara = nStartPara; nPara <= aSel.nEndPara; nPara++ )
//STRIP001  {
//STRIP001      Paragraph* pPara = pOwner->pParaList->GetParagraph( nPara );
//STRIP001      DBG_ASSERT(pPara, "ImpCalcSelectedPages: ungueltige Selection? ");
//STRIP001      if( pPara->GetDepth() == 0 )
//STRIP001      {
//STRIP001          nPages++;
//STRIP001          if( nFirstPage == 0xFFFF )
//STRIP001              nFirstPage = nPara;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( nPages )
//STRIP001  {
//STRIP001      pOwner->nDepthChangedHdlPrevDepth = nPages;
//STRIP001      pOwner->pHdlParagraph = (Paragraph*)nFirstPage;
//STRIP001  }
//STRIP001
//STRIP001  return nPages;
//STRIP001 }


//STRIP001 void OutlinerView::ShowBullets( BOOL bShow, BOOL bAffectLevel0 )
//STRIP001 {
//STRIP001  pOwner->UndoActionStart( OLUNDO_ATTR );
//STRIP001
//STRIP001  ESelection aSel( pEditView->GetSelection() );
//STRIP001  aSel.Adjust();
//STRIP001
//STRIP001  BOOL bUpdate = pOwner->pEditEngine->GetUpdateMode();
//STRIP001  pOwner->pEditEngine->SetUpdateMode( FALSE );
//STRIP001
//STRIP001  for ( USHORT nPara = aSel.nStartPara; nPara <= aSel.nEndPara; nPara++ )
//STRIP001  {
//STRIP001      Paragraph* pPara = pOwner->pParaList->GetParagraph( nPara );
//STRIP001      DBG_ASSERT(pPara, "ShowBullets: ungueltige Selection? ");
//STRIP001      if( pPara && ( bAffectLevel0 || pPara->GetDepth() ) )
//STRIP001      {
//STRIP001          SfxItemSet aAttribs( pOwner->pEditEngine->GetParaAttribs( nPara ) );
//STRIP001          BOOL bVis = ((const SfxUInt16Item&)aAttribs.Get( EE_PARA_BULLETSTATE )).
//STRIP001                              GetValue() ? TRUE : FALSE;
//STRIP001          if ( bVis != bShow )
//STRIP001          {
//STRIP001              aAttribs.Put( SfxUInt16Item( EE_PARA_BULLETSTATE, bShow ? 1 : 0 ) );
//STRIP001              pOwner->pEditEngine->SetParaAttribs( nPara, aAttribs );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  pOwner->pEditEngine->SetUpdateMode( bUpdate );
//STRIP001
//STRIP001  pOwner->UndoActionEnd( OLUNDO_ATTR );
//STRIP001 }

//STRIP001 void OutlinerView::RemoveAttribs( BOOL bRemoveParaAttribs, USHORT nWhich )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  BOOL bUpdate = pOwner->GetUpdateMode();
//STRIP001  pOwner->SetUpdateMode( FALSE );
//STRIP001  pOwner->UndoActionStart( OLUNDO_ATTR );
//STRIP001  pEditView->RemoveAttribs( bRemoveParaAttribs, nWhich );
//STRIP001  if ( bRemoveParaAttribs )
//STRIP001  {
//STRIP001      // Ueber alle Absaetze, und Einrueckung und Level einstellen
//STRIP001      ESelection aSel = pEditView->GetSelection();
//STRIP001      aSel.Adjust();
//STRIP001      for ( USHORT nPara = aSel.nStartPara; nPara <= aSel.nEndPara; nPara++ )
//STRIP001      {
//STRIP001          Paragraph* pPara = pOwner->pParaList->GetParagraph( nPara );
//STRIP001             pOwner->ImplInitDepth( nPara, pPara->GetDepth(), FALSE, FALSE );
//STRIP001      }
//STRIP001  }
//STRIP001  pOwner->UndoActionEnd( OLUNDO_ATTR );
//STRIP001  pOwner->SetUpdateMode( bUpdate );
//STRIP001 }



// =====================================================================
// ======================   Einfache Durchreicher =======================
// ======================================================================


//STRIP001 void OutlinerView::InsertText( const XubString& rNew, BOOL bSelect )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  if( pOwner->bFirstParaIsEmpty )
//STRIP001      pOwner->Insert( String() );
//STRIP001  pEditView->InsertText( rNew, bSelect );
//STRIP001 }

//STRIP001 void OutlinerView::SetVisArea( const Rectangle& rRec )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pEditView->SetVisArea( rRec );
//STRIP001 }


/*N*/ void OutlinerView::SetSelection( const ESelection& rSel )
/*N*/ {
/*N*/   DBG_CHKTHIS(OutlinerView,0);
/*N*/   pEditView->SetSelection( rSel );
/*N*/ }

//STRIP001 void OutlinerView::SetReadOnly( BOOL bReadOnly )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pEditView->SetReadOnly( bReadOnly );
//STRIP001 }

//STRIP001 BOOL OutlinerView::IsReadOnly() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  return pEditView->IsReadOnly();
//STRIP001 }

//STRIP001 BOOL OutlinerView::HasSelection() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  return pEditView->HasSelection();
//STRIP001 }


//STRIP001 void OutlinerView::ShowCursor( BOOL bGotoCursor )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pEditView->ShowCursor( bGotoCursor );
//STRIP001 }


//STRIP001 void OutlinerView::HideCursor()
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pEditView->HideCursor();
//STRIP001 }


//STRIP001 void OutlinerView::SetWindow( Window* pWin )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pEditView->SetWindow( pWin );
//STRIP001 }


/*N*/ Window* OutlinerView::GetWindow() const
/*N*/ {
/*N*/   DBG_CHKTHIS(OutlinerView,0);
/*N*/   return pEditView->GetWindow();
/*N*/ }


//STRIP001 void OutlinerView::SetOutputArea( const Rectangle& rRect )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pEditView->SetOutputArea( rRect );
//STRIP001 }


/*N*/ Rectangle OutlinerView::GetOutputArea() const
/*N*/ {
/*N*/   DBG_CHKTHIS(OutlinerView,0);
/*N*/   return pEditView->GetOutputArea();
/*N*/ }


/*N*/ XubString OutlinerView::GetSelected() const
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return XubString(); //STRIP001
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  return pEditView->GetSelected();
/*N*/ }


//STRIP001 void OutlinerView::RemoveCharAttribs( ULONG nPara, USHORT nWhich)
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pEditView->RemoveCharAttribs( (USHORT)nPara, nWhich);
//STRIP001 }


//STRIP001 void OutlinerView::CompleteAutoCorrect()
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pEditView->CompleteAutoCorrect();
//STRIP001 }


//STRIP001 EESpellState OutlinerView::StartSpeller( BOOL bMultiDoc )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  return pEditView->StartSpeller( bMultiDoc );
//STRIP001 }

//STRIP001 EESpellState OutlinerView::StartSpeller( LanguageType eLang, BOOL bMultiDoc )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  return pEditView->StartSpeller( eLang, bMultiDoc );
//STRIP001 }


//STRIP001 EESpellState OutlinerView::StartThesaurus()
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  return pEditView->StartThesaurus();
//STRIP001 }

//STRIP001 EESpellState OutlinerView::StartThesaurus( LanguageType eLang )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  return pEditView->StartThesaurus( eLang );
//STRIP001 }


//STRIP001 USHORT OutlinerView::StartSearchAndReplace( const SvxSearchItem& rSearchItem )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  return pEditView->StartSearchAndReplace( rSearchItem );
//STRIP001 }

//STRIP001 void OutlinerView::TransliterateText( sal_Int32 nTransliterationMode )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pEditView->TransliterateText( nTransliterationMode );
//STRIP001 }



/*N*/ ESelection OutlinerView::GetSelection()
/*N*/ {
/*N*/   DBG_CHKTHIS(OutlinerView,0);
/*N*/   return pEditView->GetSelection();
/*N*/ }


//STRIP001 void OutlinerView::Scroll( long nHorzScroll, long nVertScroll )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pEditView->Scroll( nHorzScroll, nVertScroll );
//STRIP001 }


//STRIP001 void OutlinerView::SetControlWord( ULONG nWord )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pEditView->SetControlWord( nWord );
//STRIP001 }


//STRIP001 ULONG OutlinerView::GetControlWord() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  return pEditView->GetControlWord();
//STRIP001 }


//STRIP001 void OutlinerView::SetAnchorMode( EVAnchorMode eMode )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pEditView->SetAnchorMode( eMode );
//STRIP001 }


//STRIP001 EVAnchorMode OutlinerView::GetAnchorMode() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  return pEditView->GetAnchorMode();
//STRIP001 }


//STRIP001 void OutlinerView::Undo()
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pEditView->Undo();
//STRIP001 }


//STRIP001 void OutlinerView::Redo()
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pEditView->Redo();
//STRIP001 }


//STRIP001 void OutlinerView::EnablePaste( BOOL bEnable )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pEditView->EnablePaste( bEnable );
//STRIP001 }


/*N*/ void OutlinerView::Copy()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pEditView->Copy();
/*N*/ }


//STRIP001 void OutlinerView::InsertField( const SvxFieldItem& rFld )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pEditView->InsertField( rFld );
//STRIP001 }


//STRIP001 const SvxFieldItem* OutlinerView::GetFieldUnderMousePointer() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  return pEditView->GetFieldUnderMousePointer();
//STRIP001 }


//STRIP001 const SvxFieldItem* OutlinerView::GetFieldUnderMousePointer( USHORT& nPara, USHORT& nPos ) const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  return pEditView->GetFieldUnderMousePointer( nPara, nPos );
//STRIP001 }


//STRIP001 const SvxFieldItem* OutlinerView::GetFieldAtSelection() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  return pEditView->GetFieldAtSelection();
//STRIP001 }

//STRIP001 void OutlinerView::SetInvalidateMore( USHORT nPixel )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pEditView->SetInvalidateMore( nPixel );
//STRIP001 }


//STRIP001 USHORT OutlinerView::GetInvalidateMore() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  return pEditView->GetInvalidateMore();
//STRIP001 }


//STRIP001 BOOL OutlinerView::IsCursorAtWrongSpelledWord( BOOL bMarkIfWrong )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  return pEditView->IsCursorAtWrongSpelledWord( bMarkIfWrong );
//STRIP001 }


//STRIP001 BOOL OutlinerView::IsWrongSpelledWordAtPos( const Point& rPosPixel, BOOL bMarkIfWrong )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  return pEditView->IsWrongSpelledWordAtPos( rPosPixel, bMarkIfWrong );
//STRIP001 }


//STRIP001 void OutlinerView::SpellIgnoreWord()
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pEditView->SpellIgnoreWord();
//STRIP001 }


//STRIP001 void OutlinerView::ExecuteSpellPopup( const Point& rPosPixel, Link* pStartDlg )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pEditView->ExecuteSpellPopup( rPosPixel, pStartDlg );
//STRIP001 }

//STRIP001 ULONG OutlinerView::Read( SvStream& rInput, EETextFormat eFormat, BOOL bSelect, SvKeyValueIterator* pHTTPHeaderAttrs )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  USHORT nOldParaCount = pEditView->GetEditEngine()->GetParagraphCount();
//STRIP001  ESelection aOldSel = pEditView->GetSelection();
//STRIP001  aOldSel.Adjust();
//STRIP001
//STRIP001  ULONG nRet = pEditView->Read( rInput, eFormat, bSelect, pHTTPHeaderAttrs );
//STRIP001
//STRIP001  // MT 08/00: Hier sollte eigentlich das gleiche wie in PasteSpecial passieren!
//STRIP001  // Mal anpassen, wenn dieses ImplInitPaste und ImpPasted-Geraffel ueberarbeitet ist.
//STRIP001
//STRIP001  long nParaDiff = pEditView->GetEditEngine()->GetParagraphCount() - nOldParaCount;
//STRIP001  USHORT nChangesStart = aOldSel.nStartPara;
//STRIP001  USHORT nChangesEnd = nChangesStart + nParaDiff + (aOldSel.nEndPara-aOldSel.nStartPara);
//STRIP001
//STRIP001  for ( USHORT n = nChangesStart; n <= nChangesEnd; n++ )
//STRIP001  {
//STRIP001      if ( eFormat == EE_FORMAT_BIN )
//STRIP001      {
//STRIP001          USHORT nDepth = 0;
//STRIP001          const SfxItemSet& rAttrs = pOwner->GetParaAttribs( n );
//STRIP001          const SfxUInt16Item& rLevel = (const SfxUInt16Item&) rAttrs.Get( EE_PARA_OUTLLEVEL );
//STRIP001          nDepth = rLevel.GetValue();
//STRIP001          pOwner->ImplInitDepth( n, nDepth, FALSE );
//STRIP001      }
//STRIP001
//STRIP001      if ( pOwner->ImplGetOutlinerMode() == OUTLINERMODE_OUTLINEOBJECT )
//STRIP001          pOwner->ImplSetLevelDependendStyleSheet( n );
//STRIP001  }
//STRIP001
//STRIP001  if ( eFormat != EE_FORMAT_BIN )
//STRIP001  {
//STRIP001      pOwner->ImpFilterIndents( nChangesStart, nChangesEnd );
//STRIP001  }
//STRIP001
//STRIP001  return nRet;
//STRIP001 }

#ifndef SVX_LIGHT
//STRIP001 ULONG OutlinerView::Write( SvStream& rOutput, EETextFormat eFormat )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  return pEditView->Write( rOutput, eFormat );
//STRIP001 }
#endif

//STRIP001 void OutlinerView::SetBackgroundColor( const Color& rColor )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  pEditView->SetBackgroundColor( rColor );
//STRIP001 }


//STRIP001 Color OutlinerView::GetBackgroundColor()
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  return pEditView->GetBackgroundColor();
//STRIP001 }

//STRIP001 SfxItemSet OutlinerView::GetAttribs()
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  return pEditView->GetAttribs();
//STRIP001 }

//STRIP001 USHORT OutlinerView::GetSelectedScriptType() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(OutlinerView,0);
//STRIP001  return pEditView->GetSelectedScriptType();
//STRIP001 }
}
