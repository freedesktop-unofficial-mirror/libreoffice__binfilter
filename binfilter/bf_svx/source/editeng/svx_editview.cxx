/*************************************************************************
 *
 *  $RCSfile: svx_editview.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 15:35:00 $
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

#define _SOLAR__PRIVATE 1

// auto strip #ifndef SVX_LIGHT
// auto strip #include <srchitem.hxx>
// auto strip #endif

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
#include <editeng.hxx>
#include <editview.hxx>

// auto strip #ifndef _PSTM_HXX //autogen
// auto strip #include <tools/pstm.hxx>
// auto strip #endif

// auto strip #ifndef _SFXPOOLITEM_HXX //autogen
// auto strip #include <svtools/poolitem.hxx>
// auto strip #endif

#ifndef _SVX_ITEMDATA_HXX
#include "itemdata.hxx"
#endif

// auto strip #ifndef _DATE_HXX //autogen
// auto strip #include <tools/date.hxx>
// auto strip #endif

// auto strip #ifndef _TIME_HXX //autogen
// auto strip #include <tools/time.hxx>
// auto strip #endif

// auto strip #include <flditem.hxx>
// auto strip #include <svxacorr.hxx>
// auto strip #include <langitem.hxx>
// auto strip #include <eerdll.hxx>
// auto strip #include <eerdll2.hxx>
#include <editeng.hrc>
// auto strip #include <dlgutil.hxx>
#include <helpid.hrc>
// auto strip #include <tools/isolang.hxx>
// auto strip #include <vcl/menu.hxx>

// auto strip #ifndef _UNO_LINGU_HXX
// auto strip #include <unolingu.hxx>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_LINGUISTIC2_XDICTIONARY1_HPP_
// auto strip #include <com/sun/star/linguistic2/XDictionary1.hpp>
// auto strip #endif
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
//STRIP001 LanguageType lcl_CheckLanguage( const OUString &rWord, Reference< XSpellChecker1 >  xSpell )
//STRIP001 {
//STRIP001     LanguageType nLang = LANGUAGE_NONE;
//STRIP001
//STRIP001  Reference< XSpellAlternatives >     xAlt;
//STRIP001  Sequence< short >   aLangs;
//STRIP001  if (xSpell.is())
//STRIP001      aLangs = xSpell->getLanguages();
//STRIP001  const short *pLang = aLangs.getConstArray();
//STRIP001     INT32   nCount = aLangs.getLength();
//STRIP001
//STRIP001     //! due to dieckmann (new german) spellchecker excepting many english
//STRIP001     //! (and other?) words as correct
//STRIP001     //! GERMAN and GERMAN_SWISS should be checked last.
//STRIP001     //! Otherwise e.g. english words might be reported as being german words!
//STRIP001     for (INT32 i = 0;  i < nCount;  i++)
//STRIP001  {
//STRIP001         INT16 nTmpLang = pLang[i];
//STRIP001         if (nTmpLang != LANGUAGE_NONE  &&
//STRIP001             nTmpLang != LANGUAGE_GERMAN  &&
//STRIP001             nTmpLang != LANGUAGE_GERMAN_SWISS)
//STRIP001      {
//STRIP001             if (xSpell->isValid( rWord, nTmpLang, Sequence< PropertyValue >() ) &&
//STRIP001                 xSpell->hasLanguage( nTmpLang ))
//STRIP001          {
//STRIP001                 nLang = nTmpLang;
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001     if (nLang == LANGUAGE_NONE  &&
//STRIP001         xSpell->isValid( rWord, LANGUAGE_GERMAN, Sequence< PropertyValue >() ) &&
//STRIP001         xSpell->hasLanguage( LANGUAGE_GERMAN ))
//STRIP001     {
//STRIP001         nLang = LANGUAGE_GERMAN;
//STRIP001     }
//STRIP001     if (nLang == LANGUAGE_NONE  &&
//STRIP001         xSpell->isValid( rWord, LANGUAGE_GERMAN_SWISS, Sequence< PropertyValue >() ) &&
//STRIP001         xSpell->hasLanguage( LANGUAGE_GERMAN_SWISS ))
//STRIP001     {
//STRIP001         nLang = LANGUAGE_GERMAN_SWISS;
//STRIP001     }
//STRIP001
//STRIP001  return nLang;
//STRIP001 }


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

//STRIP001 ImpEditEngine* EditView::GetImpEditEngine() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  return pImpEditView->pEditEngine->pImpEditEngine;
//STRIP001 }

/*N*/ EditEngine* EditView::GetEditEngine() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditView, 0 );
/*N*/   DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
/*N*/   return pImpEditView->pEditEngine;
/*N*/ }

//STRIP001 void EditView::Invalidate()
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  if ( !pImpEditView->DoInvalidateMore() )
//STRIP001      pImpEditView->GetWindow()->Invalidate( pImpEditView->aOutArea );
//STRIP001  else
//STRIP001  {
//STRIP001      Rectangle aRect( pImpEditView->aOutArea );
//STRIP001      long nMore = pImpEditView->GetWindow()->PixelToLogic( Size( pImpEditView->GetInvalidateMore(), 0 ) ).Width();
//STRIP001      aRect.Left() -= nMore;
//STRIP001      aRect.Right() += nMore;
//STRIP001      aRect.Top() -= nMore;
//STRIP001      aRect.Bottom() += nMore;
//STRIP001      pImpEditView->GetWindow()->Invalidate( aRect );
//STRIP001  }
//STRIP001 }

//STRIP001 void EditView::SetReadOnly( sal_Bool bReadOnly )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  pImpEditView->bReadOnly = bReadOnly;
//STRIP001 }

/*N*/ sal_Bool EditView::IsReadOnly() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditView, 0 );
/*N*/   return pImpEditView->bReadOnly;
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
/*N*/   // Wenn nach einem KeyInput die Selection manipuliert wird:
/*N*/   PIMPEE->CheckIdleFormatter();
/*N*/
/*N*/   // Selektion darf nicht bei einem unsichtbaren Absatz Starten/Enden:
/*N*/   ParaPortion* pPortion = PIMPEE->FindParaPortion( aNewSelection.Min().GetNode() );
/*N*/   if ( !pPortion->IsVisible() )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 pPortion = PIMPEE->GetPrevVisPortion( pPortion );
//STRIP001 /*?*/        ContentNode* pNode = pPortion ? pPortion->GetNode() : PIMPEE->GetEditDoc().GetObject( 0 );
//STRIP001 /*?*/        aNewSelection.Min() = EditPaM( pNode, pNode->Len() );
/*N*/   }
/*N*/   pPortion = PIMPEE->FindParaPortion( aNewSelection.Max().GetNode() );
/*N*/   if ( !pPortion->IsVisible() )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 pPortion = PIMPEE->GetPrevVisPortion( pPortion );
//STRIP001 /*?*/        ContentNode* pNode = pPortion ? pPortion->GetNode() : PIMPEE->GetEditDoc().GetObject( 0 );
//STRIP001 /*?*/        aNewSelection.Max() = EditPaM( pNode, pNode->Len() );
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

//STRIP001 void EditView::DeleteSelected()
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001     pImpEditView->DeleteSelected();
//STRIP001 }

//STRIP001 USHORT EditView::GetSelectedScriptType() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  return PIMPEE->GetScriptType( pImpEditView->GetEditSelection() );
//STRIP001 }

//STRIP001 void EditView::Paint( const Rectangle& rRect )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  PIMPEE->Paint( pImpEditView, rRect );
//STRIP001 }

//STRIP001 void EditView::SetEditEngine( EditEngine* pEditEng )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  pImpEditView->pEditEngine = pEditEng;
//STRIP001  EditSelection aStartSel;
//STRIP001  aStartSel = PIMPEE->GetEditDoc().GetStartPaM();
//STRIP001  pImpEditView->SetEditSelection( aStartSel );
//STRIP001 }

//STRIP001 void EditView::SetWindow( Window* pWin )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  pImpEditView->pOutWin = pWin;
//STRIP001  PIMPEE->GetSelEngine().Reset();
//STRIP001 }

/*N*/ Window*   EditView::GetWindow() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditView, 0 );
/*N*/   return pImpEditView->pOutWin;
/*N*/ }

/*N*/ void EditView::SetVisArea( const Rectangle& rRec )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  pImpEditView->SetVisDocStartPos( rRec.TopLeft() );
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

//STRIP001 void EditView::SetPointer( const Pointer& rPointer )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  pImpEditView->SetPointer( rPointer );
//STRIP001 }

/*N*/ const Pointer& EditView::GetPointer() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditView, 0 );
/*N*/   return pImpEditView->GetPointer();
/*N*/ }

//STRIP001 void EditView::SetCursor( const Cursor& rCursor )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  delete pImpEditView->pCursor;
//STRIP001  pImpEditView->pCursor = new Cursor( rCursor );
//STRIP001 }

//STRIP001 Cursor* EditView::GetCursor() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  return pImpEditView->pCursor;
//STRIP001 }

//STRIP001 void EditView::InsertText( const XubString& rStr, sal_Bool bSelect )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001
//STRIP001  ImpEditEngine* pImpEE = PIMPEE;
//STRIP001  pImpEditView->DrawSelection();
//STRIP001
//STRIP001  EditPaM aPaM1;
//STRIP001  if ( bSelect )
//STRIP001  {
//STRIP001      EditSelection aTmpSel( pImpEditView->GetEditSelection() );
//STRIP001      aTmpSel.Adjust( pImpEE->GetEditDoc() );
//STRIP001      aPaM1 = aTmpSel.Min();
//STRIP001  }
//STRIP001
//STRIP001  pImpEE->UndoActionStart( EDITUNDO_INSERT );
//STRIP001  EditPaM aPaM2( pImpEE->InsertText( pImpEditView->GetEditSelection(), rStr ) );
//STRIP001  pImpEE->UndoActionEnd( EDITUNDO_INSERT );
//STRIP001
//STRIP001  if ( bSelect )
//STRIP001  {
//STRIP001      DBG_ASSERT( !aPaM1.DbgIsBuggy( pImpEE->GetEditDoc() ), "Insert: PaM kaputt" );
//STRIP001      pImpEditView->SetEditSelection( EditSelection( aPaM1, aPaM2 ) );
//STRIP001  }
//STRIP001  else
//STRIP001      pImpEditView->SetEditSelection( EditSelection( aPaM2, aPaM2 ) );
//STRIP001
//STRIP001  pImpEE->FormatAndUpdate( this );
//STRIP001 }

/*N*/ sal_Bool EditView::PostKeyEvent( const KeyEvent& rKeyEvent )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditView, 0 );
/*N*/   DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
/*N*/   return pImpEditView->PostKeyEvent( rKeyEvent );
/*N*/ }

//STRIP001 sal_Bool EditView::MouseButtonUp( const MouseEvent& rMouseEvent )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  return pImpEditView->MouseButtonUp( rMouseEvent );
//STRIP001 }

//STRIP001 sal_Bool EditView::MouseButtonDown( const MouseEvent& rMouseEvent )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  return pImpEditView->MouseButtonDown( rMouseEvent );
//STRIP001 }

//STRIP001 sal_Bool EditView::MouseMove( const MouseEvent& rMouseEvent )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  return pImpEditView->MouseMove( rMouseEvent );
//STRIP001 }

//STRIP001 void EditView::Command( const CommandEvent& rCEvt )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  pImpEditView->Command( rCEvt );
//STRIP001 }

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

//STRIP001 Pair EditView::Scroll( long ndX, long ndY, BYTE nRangeCheck )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  return pImpEditView->Scroll( ndX, ndY, nRangeCheck );
//STRIP001 }

//STRIP001 const SfxItemSet& EditView::GetEmptyItemSet()
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  return PIMPEE->GetEmptyItemSet();
//STRIP001 }

//STRIP001 void EditView::SetAttribs( const SfxItemSet& rSet )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  DBG_ASSERT( !pImpEditView->aEditSelection.IsInvalid(), "Blinde Selection in ...." );
//STRIP001
//STRIP001  // Kein Undo-Kappseln noetig...
//STRIP001  pImpEditView->DrawSelection();
//STRIP001  PIMPEE->SetAttribs( pImpEditView->GetEditSelection(), rSet, ATTRSPECIAL_WHOLEWORD );
//STRIP001  PIMPEE->FormatAndUpdate( this );
//STRIP001 }

//STRIP001 void EditView::SetParaAttribs( const SfxItemSet& rSet, sal_uInt16 nPara )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  // Kein Undo-Kappseln noetig...
//STRIP001  PIMPEE->SetParaAttribs( nPara, rSet );
//STRIP001  // Beim Aendern von Absatzattributen muss immer formatiert werden...
//STRIP001  PIMPEE->FormatAndUpdate( this );
//STRIP001 }

//STRIP001 void EditView::RemoveAttribs( sal_Bool bRemoveParaAttribs, sal_uInt16 nWhich )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001
//STRIP001  pImpEditView->DrawSelection();
//STRIP001  PIMPEE->UndoActionStart( EDITUNDO_RESETATTRIBS );
//STRIP001  PIMPEE->RemoveCharAttribs( pImpEditView->GetEditSelection(), bRemoveParaAttribs, nWhich  );
//STRIP001  PIMPEE->UndoActionEnd( EDITUNDO_RESETATTRIBS );
//STRIP001  PIMPEE->FormatAndUpdate( this );
//STRIP001 }

//STRIP001 void EditView::RemoveCharAttribs( sal_uInt16 nPara, sal_uInt16 nWhich )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  PIMPEE->UndoActionStart( EDITUNDO_RESETATTRIBS );
//STRIP001  PIMPEE->RemoveCharAttribs( nPara, nWhich );
//STRIP001  PIMPEE->UndoActionEnd( EDITUNDO_RESETATTRIBS );
//STRIP001  PIMPEE->FormatAndUpdate( this );
//STRIP001 }

//STRIP001 SfxItemSet EditView::GetAttribs()
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  DBG_ASSERT( !pImpEditView->aEditSelection.IsInvalid(), "Blinde Selection in ...." );
//STRIP001  return PIMPEE->GetAttribs( pImpEditView->GetEditSelection() );
//STRIP001 }

//STRIP001 void EditView::Undo()
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  PIMPEE->Undo( this );
//STRIP001 }

//STRIP001 void EditView::Redo()
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  PIMPEE->Redo( this );
//STRIP001 }

//STRIP001 sal_uInt32 EditView::Read( SvStream& rInput, EETextFormat eFormat, sal_Bool bSelect, SvKeyValueIterator* pHTTPHeaderAttrs )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  EditSelection aOldSel( pImpEditView->GetEditSelection() );
//STRIP001  pImpEditView->DrawSelection();
//STRIP001  PIMPEE->UndoActionStart( EDITUNDO_READ );
//STRIP001  EditPaM aEndPaM = PIMPEE->Read( rInput, eFormat, aOldSel, pHTTPHeaderAttrs );
//STRIP001  PIMPEE->UndoActionEnd( EDITUNDO_READ );
//STRIP001  EditSelection aNewSel( aEndPaM, aEndPaM );
//STRIP001  if ( bSelect )
//STRIP001  {
//STRIP001      aOldSel.Adjust( PIMPEE->GetEditDoc() );
//STRIP001      aNewSel.Min() = aOldSel.Min();
//STRIP001  }
//STRIP001
//STRIP001  pImpEditView->SetEditSelection( aNewSel );
//STRIP001  sal_Bool bGotoCursor = pImpEditView->DoAutoScroll();
//STRIP001  ShowCursor( bGotoCursor );
//STRIP001
//STRIP001  return rInput.GetError();
//STRIP001 }

#ifndef SVX_LIGHT
//STRIP001 sal_uInt32 EditView::Write( SvStream& rOutput, EETextFormat eFormat )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  PIMPEE->Write( rOutput, eFormat, pImpEditView->GetEditSelection() );
//STRIP001  ShowCursor();
//STRIP001  return rOutput.GetError();
//STRIP001 }
#endif

/*N*/ void EditView::Cut()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001     Reference< ::com::sun::star::datatransfer::clipboard::XClipboard> aClipBoard(GetWindow()->GetClipboard());
//STRIP001  pImpEditView->CutCopy( aClipBoard, sal_True );
/*N*/ }

/*N*/ void EditView::Copy()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001     Reference< ::com::sun::star::datatransfer::clipboard::XClipboard> aClipBoard(GetWindow()->GetClipboard());
//STRIP001  pImpEditView->CutCopy( aClipBoard, sal_False );
/*N*/ }

/*N*/ void EditView::Paste()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001     Reference< ::com::sun::star::datatransfer::clipboard::XClipboard> aClipBoard(GetWindow()->GetClipboard());
//STRIP001  pImpEditView->Paste( aClipBoard, sal_False );
/*N*/ }

//STRIP001 void EditView::PasteSpecial()
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001     Reference< ::com::sun::star::datatransfer::clipboard::XClipboard> aClipBoard(GetWindow()->GetClipboard());
//STRIP001  pImpEditView->Paste(aClipBoard, sal_True );
//STRIP001 }

//STRIP001 void EditView::EnablePaste( sal_Bool bEnable )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  pImpEditView->EnablePaste( bEnable );
//STRIP001 }

//STRIP001 sal_Bool EditView::IsPasteEnabled() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  return pImpEditView->IsPasteEnabled();
//STRIP001 }

//STRIP001 Point EditView::GetWindowPosTopLeft( sal_uInt16 nParagraph )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  Point aDocPos( pImpEditView->pEditEngine->GetDocPosTopLeft( nParagraph ) );
//STRIP001  return pImpEditView->GetWindowPos( aDocPos );
//STRIP001 }

//STRIP001 sal_uInt16 EditView::GetParagraph( const Point& rMousePosPixel )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  Point aMousePos( rMousePosPixel );
//STRIP001  aMousePos = GetWindow()->PixelToLogic( aMousePos );
//STRIP001  Point aDocPos( pImpEditView->GetDocPos( aMousePos ) );
//STRIP001  sal_uInt16 nParagraph = PIMPEE->GetParaPortions().FindParagraph( aDocPos.Y() );
//STRIP001  return nParagraph;
//STRIP001 }

//STRIP001 void EditView::IndentBlock()
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001
//STRIP001  PIMPEE->IndentBlock( this, sal_True );
//STRIP001 }

//STRIP001 void EditView::UnindentBlock()
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001
//STRIP001  PIMPEE->IndentBlock( this, sal_False );
//STRIP001 }

//STRIP001 EESelectionMode  EditView::GetSelectionMode() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  return pImpEditView->GetSelectionMode();
//STRIP001 }

/*N*/ void EditView::SetSelectionMode( EESelectionMode eMode )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditView, 0 );
/*N*/   pImpEditView->SetSelectionMode( eMode );
/*N*/ }

//STRIP001 XubString EditView::GetSelected()
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  return PIMPEE->GetSelected( pImpEditView->GetEditSelection() );
//STRIP001 }

//STRIP001 void EditView::MoveParagraphs( Range aParagraphs, sal_uInt16 nNewPos )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  PIMPEE->UndoActionStart( EDITUNDO_MOVEPARAS );
//STRIP001  PIMPEE->MoveParagraphs( aParagraphs, nNewPos, this );
//STRIP001  PIMPEE->UndoActionEnd( EDITUNDO_MOVEPARAS );
//STRIP001 }

//STRIP001 void EditView::MoveParagraphs( long nDiff )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001     ESelection aSel = GetSelection();
//STRIP001     long nDest = aSel.nStartPara + nDiff;
//STRIP001     if ( nDiff > 0 )
//STRIP001         nDest++;
//STRIP001     DBG_ASSERT( ( nDest >= 0 ) && ( nDest <= pImpEditView->pEditEngine->GetParagraphCount() ), "MoveParagraphs - wrong Parameters!" );
//STRIP001     MoveParagraphs( Range( aSel.nStartPara, aSel.nEndPara ), nDest );
//STRIP001 }

//STRIP001 void EditView::SetBackgroundColor( const Color& rColor )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  pImpEditView->SetBackgroundColor( rColor );
//STRIP001 }

//STRIP001 Color EditView::GetBackgroundColor() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  return pImpEditView->GetBackgroundColor();
//STRIP001 }

//STRIP001 void EditView::SetControlWord( sal_uInt32 nWord )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  pImpEditView->nControl = nWord;
//STRIP001 }

//STRIP001 sal_uInt32 EditView::GetControlWord() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  return pImpEditView->nControl;
//STRIP001 }

//STRIP001 EditTextObject*  EditView::CreateTextObject()
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  return PIMPEE->CreateTextObject( pImpEditView->GetEditSelection() );
//STRIP001 }

//STRIP001 void EditView::InsertText( const EditTextObject& rTextObject )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  pImpEditView->DrawSelection();
//STRIP001
//STRIP001  PIMPEE->UndoActionStart( EDITUNDO_INSERT );
//STRIP001  EditSelection aTextSel( PIMPEE->InsertText( rTextObject, pImpEditView->GetEditSelection() ) );
//STRIP001  PIMPEE->UndoActionEnd( EDITUNDO_INSERT );
//STRIP001
//STRIP001  aTextSel.Min() = aTextSel.Max();    // Selektion nicht behalten.
//STRIP001  pImpEditView->SetEditSelection( aTextSel );
//STRIP001  PIMPEE->FormatAndUpdate( this );
//STRIP001 }

//STRIP001 void EditView::InsertText( ::com::sun::star::uno::Reference< ::com::sun::star::datatransfer::XTransferable > xDataObj, BOOL bUseSpecial )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001
//STRIP001  PIMPEE->UndoActionStart( EDITUNDO_INSERT );
//STRIP001     pImpEditView->DeleteSelected();
//STRIP001  EditSelection aTextSel( PIMPEE->InsertText( xDataObj, pImpEditView->GetEditSelection().Max(), bUseSpecial ) );
//STRIP001  PIMPEE->UndoActionEnd( EDITUNDO_INSERT );
//STRIP001
//STRIP001  aTextSel.Min() = aTextSel.Max();    // Selektion nicht behalten.
//STRIP001  pImpEditView->SetEditSelection( aTextSel );
//STRIP001  PIMPEE->FormatAndUpdate( this );
//STRIP001 }

//STRIP001 sal_Bool EditView::Drop( const DropEvent& rEvt )
//STRIP001 {
//STRIP001     return FALSE;
//STRIP001 }

//STRIP001 ESelection EditView::GetDropPos()
//STRIP001 {
//STRIP001     DBG_ERROR( "GetDropPos - Why?!" );
//STRIP001     return ESelection();
//STRIP001 }

//STRIP001 sal_Bool EditView::QueryDrop( DropEvent& rEvt )
//STRIP001 {
//STRIP001     return FALSE;
//STRIP001 }

//STRIP001 void EditView::SetEditEngineUpdateMode( sal_Bool bUpdate )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  PIMPEE->SetUpdateMode( bUpdate, this );
//STRIP001 }

//STRIP001 void EditView::ForceUpdate()
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  PIMPEE->SetUpdateMode( sal_True, this, sal_True );
//STRIP001 }

/*N*/ void EditView::SetStyleSheet( SfxStyleSheet* pStyle )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001
//STRIP001  EditSelection aSel( pImpEditView->GetEditSelection() );
//STRIP001  PIMPEE->UndoActionStart( EDITUNDO_STYLESHEET );
//STRIP001  PIMPEE->SetStyleSheet( aSel, pStyle );
//STRIP001  PIMPEE->UndoActionEnd( EDITUNDO_STYLESHEET );
/*N*/ }

//STRIP001 SfxStyleSheet* EditView::GetStyleSheet() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001
//STRIP001
//STRIP001  EditSelection aSel( pImpEditView->GetEditSelection() );
//STRIP001  aSel.Adjust( PIMPEE->GetEditDoc() );
//STRIP001  sal_uInt16 nStartPara = PIMPEE->GetEditDoc().GetPos( aSel.Min().GetNode() );
//STRIP001  sal_uInt16 nEndPara = PIMPEE->GetEditDoc().GetPos( aSel.Max().GetNode() );
//STRIP001
//STRIP001  SfxStyleSheet* pStyle = NULL;
//STRIP001  for ( sal_uInt16 n = nStartPara; n <= nEndPara; n++ )
//STRIP001  {
//STRIP001      SfxStyleSheet* pTmpStyle = PIMPEE->GetStyleSheet( n );
//STRIP001      if ( ( n != nStartPara ) && ( pStyle != pTmpStyle ) )
//STRIP001          return NULL;    // Nicht eindeutig.
//STRIP001      pStyle = pTmpStyle;
//STRIP001  }
//STRIP001  return pStyle;
//STRIP001 }

/*N*/ sal_Bool EditView::IsInsertMode() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditView, 0 );
/*N*/   return pImpEditView->IsInsertMode();
/*N*/ }

//STRIP001 void EditView::SetInsertMode( sal_Bool bInsert )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  pImpEditView->SetInsertMode( bInsert );
//STRIP001 }

//STRIP001 void EditView::SetAnchorMode( EVAnchorMode eMode )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  pImpEditView->SetAnchorMode( eMode );
//STRIP001 }

//STRIP001 EVAnchorMode EditView::GetAnchorMode() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  return pImpEditView->GetAnchorMode();
//STRIP001 }

//STRIP001 void EditView::TransliterateText( sal_Int32 nTransliterationMode )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001     EditSelection aOldSel( pImpEditView->GetEditSelection() );
//STRIP001  EditSelection aNewSel = PIMPEE->TransliterateText( pImpEditView->GetEditSelection(), nTransliterationMode );
//STRIP001     if ( aNewSel != aOldSel )
//STRIP001     {
//STRIP001      pImpEditView->DrawSelection();  // alte Selektion 'weg-zeichnen'
//STRIP001      pImpEditView->SetEditSelection( aNewSel );
//STRIP001      pImpEditView->DrawSelection();
//STRIP001     }
//STRIP001 }


//STRIP001 sal_Bool EditView::MatchGroup()
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  EditSelection aNewSel( PIMPEE->MatchGroup( pImpEditView->GetEditSelection() ) );
//STRIP001  if ( aNewSel.HasRange() )
//STRIP001  {
//STRIP001      pImpEditView->DrawSelection();
//STRIP001      pImpEditView->SetEditSelection( aNewSel );
//STRIP001      pImpEditView->DrawSelection();
//STRIP001      ShowCursor();
//STRIP001      return sal_True;
//STRIP001  }
//STRIP001  return sal_False;
//STRIP001 }

//STRIP001 void EditView::CompleteAutoCorrect()
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  if ( !pImpEditView->HasSelection() && PIMPEE->GetStatus().DoAutoCorrect() )
//STRIP001  {
//STRIP001      pImpEditView->DrawSelection();
//STRIP001      EditSelection aSel = pImpEditView->GetEditSelection();
//STRIP001      aSel = PIMPEE->EndOfWord( aSel.Max() );
//STRIP001      // MT 06/00: Why pass EditSelection to AutoCorrect, not EditPaM?!
//STRIP001      aSel = PIMPEE->AutoCorrect( aSel, 0, !IsInsertMode() );
//STRIP001      pImpEditView->SetEditSelection( aSel );
//STRIP001      if ( PIMPEE->IsModified() )
//STRIP001          PIMPEE->FormatAndUpdate( this );
//STRIP001  }
//STRIP001 }

//STRIP001 EESpellState EditView::StartSpeller( LanguageType eLang, sal_Bool bMultipleDoc )
//STRIP001 {
//STRIP001 #if SUPD >= 615
//STRIP001  DBG_ERROR( "DefaultLanguage not longer supported" );
//STRIP001 #endif
//STRIP001  return StartSpeller( bMultipleDoc );
//STRIP001 }

//STRIP001 EESpellState EditView::StartSpeller( sal_Bool bMultipleDoc )
//STRIP001 {
//STRIP001 #ifdef SVX_LIGHT
//STRIP001  return EE_SPELL_NOSPELLER;
//STRIP001 #else
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  if ( !PIMPEE->GetSpeller().is() )
//STRIP001      return EE_SPELL_NOSPELLER;
//STRIP001  SvxSpellWrapper::CheckSpellLang( PIMPEE->GetSpeller(), PIMPEE->GetLanguage( EditPaM( PIMPEE->GetEditDoc().SaveGetObject( 0 ), 0 ) ) );
//STRIP001  return PIMPEE->Spell( this, bMultipleDoc );
//STRIP001 #endif
//STRIP001 }

//STRIP001 EESpellState EditView::StartThesaurus( LanguageType eLang )
//STRIP001 {
//STRIP001 #if SUPD >= 615
//STRIP001  DBG_ERROR( "DefaultLanguage not longer supported" );
//STRIP001 #endif
//STRIP001  return StartThesaurus();
//STRIP001 }

//STRIP001 EESpellState EditView::StartThesaurus()
//STRIP001 {
//STRIP001 #ifdef SVX_LIGHT
//STRIP001  return EE_SPELL_NOSPELLER;
//STRIP001 #else
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  if ( !PIMPEE->GetSpeller().is() )
//STRIP001      return EE_SPELL_NOSPELLER;
//STRIP001
//STRIP001  return PIMPEE->StartThesaurus( this );
//STRIP001 #endif
//STRIP001 }

//STRIP001 sal_uInt16 EditView::StartSearchAndReplace( const SvxSearchItem& rSearchItem )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  return PIMPEE->StartSearchAndReplace( this, rSearchItem );
//STRIP001 }

//STRIP001 sal_Bool EditView::IsCursorAtWrongSpelledWord( sal_Bool bMarkIfWrong )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  sal_Bool bIsWrong = sal_False;
//STRIP001  if ( !HasSelection() )
//STRIP001  {
//STRIP001      EditPaM aPaM = pImpEditView->GetEditSelection().Max();
//STRIP001      bIsWrong = pImpEditView->IsWrongSpelledWord( aPaM, bMarkIfWrong );
//STRIP001  }
//STRIP001  return bIsWrong;
//STRIP001 }

//STRIP001 sal_Bool EditView::IsWrongSpelledWordAtPos( const Point& rPosPixel, sal_Bool bMarkIfWrong )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  Point aPos ( pImpEditView->GetWindow()->PixelToLogic( rPosPixel ) );
//STRIP001  aPos = pImpEditView->GetDocPos( aPos );
//STRIP001  EditPaM aPaM = pImpEditView->pEditEngine->pImpEditEngine->GetPaM( aPos, sal_False );
//STRIP001  return pImpEditView->IsWrongSpelledWord( aPaM , bMarkIfWrong );
//STRIP001 }

//STRIP001 void EditView::ExecuteSpellPopup( const Point& rPosPixel, Link* pCallBack )
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001
//STRIP001  Point aPos ( pImpEditView->GetWindow()->PixelToLogic( rPosPixel ) );
//STRIP001  aPos = pImpEditView->GetDocPos( aPos );
//STRIP001  EditPaM aPaM = pImpEditView->pEditEngine->pImpEditEngine->GetPaM( aPos, sal_False );
//STRIP001  Reference< XSpellChecker1 >  xSpeller( PIMPEE->GetSpeller() );
//STRIP001     ESelection aOldSel = GetSelection();
//STRIP001  if ( xSpeller.is() && pImpEditView->IsWrongSpelledWord( aPaM, sal_True ) )
//STRIP001  {
//STRIP001      PopupMenu aPopupMenu( EditResId( RID_MENU_SPELL ) );
//STRIP001      PopupMenu *pAutoMenu = aPopupMenu.GetPopupMenu( MN_AUTOCORR );
//STRIP001      PopupMenu *pInsertMenu = aPopupMenu.GetPopupMenu( MN_INSERT );
//STRIP001
//STRIP001      EditPaM aPaM2( aPaM );
//STRIP001      aPaM2.GetIndex()++;
//STRIP001
//STRIP001      // Gibt es Replace-Vorschlaege?
//STRIP001      String aSelected( GetSelected() );
//STRIP001      Reference< XSpellAlternatives >  xSpellAlt =
//STRIP001              xSpeller->spell( aSelected, PIMPEE->GetLanguage( aPaM2 ), Sequence< PropertyValue >() );
//STRIP001
//STRIP001         // Other language???
//STRIP001         LanguageType nCorrLang = LANGUAGE_NONE;
//STRIP001      if (xSpellAlt.is())
//STRIP001          nCorrLang = lcl_CheckLanguage( xSpellAlt->getWord(), PIMPEE->GetSpeller() );
//STRIP001
//STRIP001         if( nCorrLang != LANGUAGE_NONE )
//STRIP001      {
//STRIP001          aPopupMenu.InsertSeparator();
//STRIP001          String aTmp( ::GetLanguageString( nCorrLang ) );
//STRIP001             String aWordStr( EditResId( RID_STR_WORD ) );
//STRIP001             aWordStr.SearchAndReplace( String( RTL_CONSTASCII_USTRINGPARAM( "%x" ) ), aTmp );
//STRIP001             String aParaStr( EditResId( RID_STR_PARAGRAPH ) );
//STRIP001             aParaStr.SearchAndReplace( String( RTL_CONSTASCII_USTRINGPARAM( "%x" ) ), aTmp );
//STRIP001          aPopupMenu.InsertItem( MN_WORDLANGUAGE, aWordStr );
//STRIP001          aPopupMenu.SetHelpId( MN_WORDLANGUAGE, HID_EDITENG_SPELLER_WORDLANGUAGE );
//STRIP001          aPopupMenu.InsertItem( MN_PARALANGUAGE, aParaStr );
//STRIP001          aPopupMenu.SetHelpId( MN_PARALANGUAGE, HID_EDITENG_SPELLER_PARALANGUAGE );
//STRIP001      }
//STRIP001
//STRIP001         // ## Create mnemonics here
//STRIP001         if ( Application::IsAutoMnemonicEnabled() )
//STRIP001         {
//STRIP001             aPopupMenu.CreateAutoMnemonics();
//STRIP001             aPopupMenu.SetMenuFlags( aPopupMenu.GetMenuFlags() | MENU_FLAG_NOAUTOMNEMONICS );
//STRIP001         }
//STRIP001
//STRIP001         // Replace suggestions...
//STRIP001         Sequence< OUString > aAlt;
//STRIP001      if (xSpellAlt.is())
//STRIP001          aAlt = xSpellAlt->getAlternatives();
//STRIP001      const OUString *pAlt = aAlt.getConstArray();
//STRIP001      sal_uInt16 nWords = (USHORT) aAlt.getLength();
//STRIP001      if ( nWords )
//STRIP001      {
//STRIP001          for ( sal_uInt16 nW = 0; nW < nWords; nW++ )
//STRIP001          {
//STRIP001              String aAlternate( pAlt[nW] );
//STRIP001              aPopupMenu.InsertItem( MN_ALTSTART+nW, aAlternate, 0, nW );
//STRIP001              pAutoMenu->InsertItem( MN_AUTOSTART+nW, aAlternate, 0, nW );
//STRIP001          }
//STRIP001          aPopupMenu.InsertSeparator( nWords );
//STRIP001      }
//STRIP001      else
//STRIP001          aPopupMenu.RemoveItem( MN_AUTOCORR );   // Loeschen?
//STRIP001
//STRIP001      Reference< XDictionaryList >  xDicList( SvxGetDictionaryList() );
//STRIP001
//STRIP001      Sequence< Reference< XDictionary >  > aDics;
//STRIP001      if (xDicList.is())
//STRIP001          aDics = xDicList->getDictionaries();
//STRIP001      const Reference< XDictionary >  *pDic = aDics.getConstArray();
//STRIP001      sal_uInt16 nLanguage = PIMPEE->GetLanguage( aPaM2 );
//STRIP001      sal_uInt16 nDicCount = (USHORT)aDics.getLength();
//STRIP001      for ( sal_uInt16 i = 0; i < nDicCount; i++ )
//STRIP001      {
//STRIP001          Reference< XDictionary1 >  xDic( pDic[i], UNO_QUERY );
//STRIP001          if (xDic.is())
//STRIP001          {
//STRIP001              sal_uInt16 nActLanguage = xDic->getLanguage();
//STRIP001              if( xDic->isActive() &&
//STRIP001                  xDic->getDictionaryType() == DictionaryType_POSITIVE &&
//STRIP001                  (nLanguage == nActLanguage || LANGUAGE_NONE == nActLanguage ) )
//STRIP001              {
//STRIP001                  pInsertMenu->InsertItem( MN_DICTSTART + i, xDic->getName() );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if ( !pInsertMenu->GetItemCount() )
//STRIP001          aPopupMenu.EnableItem( MN_INSERT, sal_False );
//STRIP001
//STRIP001      aPopupMenu.RemoveDisabledEntries( sal_True, sal_True );
//STRIP001
//STRIP001      sal_uInt16 nId = aPopupMenu.Execute( pImpEditView->GetWindow(), rPosPixel );
//STRIP001      if ( nId == MN_IGNORE )
//STRIP001      {
//STRIP001          String aWord = pImpEditView->SpellIgnoreOrAddWord( sal_False );
//STRIP001          if ( pCallBack )
//STRIP001          {
//STRIP001              SpellCallbackInfo aInf( SPELLCMD_IGNOREWORD, aWord );
//STRIP001              pCallBack->Call( &aInf );
//STRIP001          }
//STRIP001             SetSelection( aOldSel );
//STRIP001      }
//STRIP001      else if ( ( nId == MN_WORDLANGUAGE ) || ( nId == MN_PARALANGUAGE ) )
//STRIP001      {
//STRIP001             SfxItemSet aAttrs = GetEditEngine()->GetEmptyItemSet();
//STRIP001             aAttrs.Put( SvxLanguageItem( nCorrLang, EE_CHAR_LANGUAGE ) );
//STRIP001             aAttrs.Put( SvxLanguageItem( nCorrLang, EE_CHAR_LANGUAGE_CTL ) );
//STRIP001             aAttrs.Put( SvxLanguageItem( nCorrLang, EE_CHAR_LANGUAGE_CJK ) );
//STRIP001             if ( nId == MN_PARALANGUAGE )
//STRIP001             {
//STRIP001                 ESelection aSel = GetSelection();
//STRIP001                 aSel.nStartPos = 0;
//STRIP001                 aSel.nEndPos = 0xFFFF;
//STRIP001                 SetSelection( aSel );
//STRIP001             }
//STRIP001          SetAttribs( aAttrs );
//STRIP001          PIMPEE->StartOnlineSpellTimer();
//STRIP001
//STRIP001             if ( pCallBack )
//STRIP001          {
//STRIP001                 SpellCallbackInfo aInf( ( nId == MN_WORDLANGUAGE ) ? SPELLCMD_WORDLANGUAGE : SPELLCMD_PARALANGUAGE, nCorrLang );
//STRIP001              pCallBack->Call( &aInf );
//STRIP001          }
//STRIP001             SetSelection( aOldSel );
//STRIP001      }
//STRIP001      else if ( nId == MN_SPELLING )
//STRIP001      {
//STRIP001          if ( !pCallBack )
//STRIP001          {
//STRIP001              // Cursor vor das Wort setzen...
//STRIP001              EditPaM aCursor = pImpEditView->GetEditSelection().Min();
//STRIP001              pImpEditView->DrawSelection();  // alte Selektion 'weg-zeichnen'
//STRIP001              pImpEditView->SetEditSelection( EditSelection( aCursor, aCursor ) );
//STRIP001              pImpEditView->DrawSelection();
//STRIP001              // Stuerzt ab, wenn keine SfxApp
//STRIP001              PIMPEE->Spell( this, sal_False );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              SpellCallbackInfo aInf( SPELLCMD_STARTSPELLDLG, String() );
//STRIP001              pCallBack->Call( &aInf );
//STRIP001          }
//STRIP001      }
//STRIP001      else if ( nId >= MN_DICTSTART )
//STRIP001      {
//STRIP001          Reference< XDictionary1 >  xDic( pDic[nId - MN_DICTSTART], UNO_QUERY );
//STRIP001          if (xDic.is())
//STRIP001              xDic->add( aSelected, sal_False, String() );
//STRIP001          aPaM.GetNode()->GetWrongList()->GetInvalidStart() = 0;
//STRIP001          aPaM.GetNode()->GetWrongList()->GetInvalidEnd() = aPaM.GetNode()->Len();
//STRIP001          PIMPEE->StartOnlineSpellTimer();
//STRIP001
//STRIP001             if ( pCallBack )
//STRIP001          {
//STRIP001              SpellCallbackInfo aInf( SPELLCMD_ADDTODICTIONARY, aSelected );
//STRIP001              pCallBack->Call( &aInf );
//STRIP001          }
//STRIP001             SetSelection( aOldSel );
//STRIP001      }
//STRIP001      else if ( nId >= MN_AUTOSTART )
//STRIP001      {
//STRIP001          DBG_ASSERT(nId - MN_AUTOSTART < aAlt.getLength(), "index out of range");
//STRIP001          String aWord = pAlt[nId - MN_AUTOSTART];
//STRIP001          SvxAutoCorrect* pAutoCorrect = EE_DLL()->GetGlobalData()->GetAutoCorrect();
//STRIP001          if ( pAutoCorrect )
//STRIP001              pAutoCorrect->PutText( aSelected, aWord, PIMPEE->GetLanguage( aPaM2 ) );
//STRIP001          InsertText( aWord );
//STRIP001      }
//STRIP001      else if ( nId >= MN_ALTSTART )  // Replace
//STRIP001      {
//STRIP001          DBG_ASSERT(nId - MN_ALTSTART < aAlt.getLength(), "index out of range");
//STRIP001          String aWord = pAlt[nId - MN_ALTSTART];
//STRIP001          InsertText( aWord );
//STRIP001      }
//STRIP001         else
//STRIP001         {
//STRIP001             SetSelection( aOldSel );
//STRIP001         }
//STRIP001  }
//STRIP001 #endif
//STRIP001 }

//STRIP001 void EditView::SpellIgnoreWord()
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  pImpEditView->SpellIgnoreOrAddWord( sal_False );
//STRIP001 }

//STRIP001 sal_Bool EditView::SelectCurrentWord()
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  EditSelection aCurSel( pImpEditView->GetEditSelection() );
//STRIP001  pImpEditView->DrawSelection();
//STRIP001  aCurSel = PIMPEE->SelectWord( aCurSel.Max() );
//STRIP001  pImpEditView->SetEditSelection( aCurSel );
//STRIP001  pImpEditView->DrawSelection();
//STRIP001  ShowCursor( sal_True, sal_False );
//STRIP001  return aCurSel.HasRange() ? sal_True : sal_False;
//STRIP001 }

//STRIP001 void EditView::InsertField( const SvxFieldItem& rFld )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001
//STRIP001  ImpEditEngine* pImpEE = PIMPEE;
//STRIP001  pImpEditView->DrawSelection();
//STRIP001  pImpEE->UndoActionStart( EDITUNDO_INSERT );
//STRIP001  EditPaM aPaM( pImpEE->InsertField( pImpEditView->GetEditSelection(), rFld ) );
//STRIP001  pImpEE->UndoActionEnd( EDITUNDO_INSERT );
//STRIP001  pImpEditView->SetEditSelection( EditSelection( aPaM, aPaM ) );
//STRIP001  pImpEE->UpdateFields();
//STRIP001  pImpEE->FormatAndUpdate( this );
//STRIP001 }

//STRIP001 const SvxFieldItem* EditView::GetFieldUnderMousePointer() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  sal_uInt16 nPara, nPos;
//STRIP001  return GetFieldUnderMousePointer( nPara, nPos );
//STRIP001 }

/*N*/ const SvxFieldItem* EditView::GetField( const Point& rPos, sal_uInt16* pPara, sal_uInt16* pPos ) const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditView, 0 );
/*N*/   DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
/*N*/   return pImpEditView->GetField( rPos, pPara, pPos );
/*N*/ }

//STRIP001 const SvxFieldItem* EditView::GetFieldUnderMousePointer( sal_uInt16& nPara, sal_uInt16& nPos ) const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001  Point aPos = pImpEditView->GetWindow()->GetPointerPosPixel();
//STRIP001  aPos = pImpEditView->GetWindow()->PixelToLogic( aPos );
//STRIP001  return GetField( aPos, &nPara, &nPos );
//STRIP001 }

//STRIP001 const SvxFieldItem* EditView::GetFieldAtSelection() const
//STRIP001 {
//STRIP001  EditSelection aSel( pImpEditView->GetEditSelection() );
//STRIP001  aSel.Adjust( pImpEditView->pEditEngine->pImpEditEngine->GetEditDoc() );
//STRIP001  // Nur wenn Cursor vor Feld, keine Selektion, oder nur Feld selektiert
//STRIP001  if ( ( aSel.Min().GetNode() == aSel.Max().GetNode() ) &&
//STRIP001       ( ( aSel.Max().GetIndex() == aSel.Min().GetIndex() ) ||
//STRIP001         ( aSel.Max().GetIndex() == aSel.Min().GetIndex()+1 ) ) )
//STRIP001  {
//STRIP001      EditPaM aPaM = aSel.Min();
//STRIP001      const CharAttribArray& rAttrs = aPaM.GetNode()->GetCharAttribs().GetAttribs();
//STRIP001      sal_uInt16 nXPos = aPaM.GetIndex();
//STRIP001      for ( sal_uInt16 nAttr = rAttrs.Count(); nAttr; )
//STRIP001      {
//STRIP001          EditCharAttrib* pAttr = rAttrs[--nAttr];
//STRIP001          if ( pAttr->GetStart() == nXPos )
//STRIP001              if ( pAttr->Which() == EE_FEATURE_FIELD )
//STRIP001              {
//STRIP001                  DBG_ASSERT( pAttr->GetItem()->ISA( SvxFieldItem ), "Kein FeldItem..." );
//STRIP001                  return (const SvxFieldItem*)pAttr->GetItem();
//STRIP001              }
//STRIP001      }
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }

//STRIP001 XubString EditView::GetWordUnderMousePointer() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001
//STRIP001  Rectangle aRect;
//STRIP001  return GetWordUnderMousePointer( aRect );
//STRIP001 }

//STRIP001 XubString EditView::GetWordUnderMousePointer( Rectangle& rWordRect ) const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  DBG_CHKOBJ( pImpEditView->pEditEngine, EditEngine, 0 );
//STRIP001
//STRIP001  Point aPos = pImpEditView->GetWindow()->GetPointerPosPixel();
//STRIP001  aPos = pImpEditView->GetWindow()->PixelToLogic( aPos );
//STRIP001
//STRIP001  XubString aWord;
//STRIP001
//STRIP001  if( GetOutputArea().IsInside( aPos ) )
//STRIP001  {
//STRIP001      ImpEditEngine* pImpEE = pImpEditView->pEditEngine->pImpEditEngine;
//STRIP001      Point aDocPos( pImpEditView->GetDocPos( aPos ) );
//STRIP001      EditPaM aPaM = pImpEE->GetPaM( aDocPos, sal_False );
//STRIP001      EditSelection aWordSel = pImpEE->SelectWord( aPaM );
//STRIP001
//STRIP001      Rectangle aTopLeftRec( pImpEE->PaMtoEditCursor( aWordSel.Min() ) );
//STRIP001      Rectangle aBottomRightRec( pImpEE->PaMtoEditCursor( aWordSel.Max() ) );
//STRIP001
//STRIP001 #if OSL_DEBUG_LEVEL > 1
//STRIP001      DBG_ASSERT( aTopLeftRec.Top() == aBottomRightRec.Top(), "Top() in einer Zeile unterschiedlich?" );
//STRIP001 #endif
//STRIP001
//STRIP001      Point aPnt1( pImpEditView->GetWindowPos( aTopLeftRec.TopLeft() ) );
//STRIP001      Point aPnt2( pImpEditView->GetWindowPos( aBottomRightRec.BottomRight()) );
//STRIP001      rWordRect = Rectangle( aPnt1, aPnt2 );
//STRIP001      aWord = pImpEE->GetSelected( aWordSel );
//STRIP001  }
//STRIP001
//STRIP001  return aWord;
//STRIP001 }

//STRIP001 void EditView::SetInvalidateMore( sal_uInt16 nPixel )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  pImpEditView->SetInvalidateMore( nPixel );
//STRIP001 }

//STRIP001 sal_uInt16 EditView::GetInvalidateMore() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  return (sal_uInt16)pImpEditView->GetInvalidateMore();
//STRIP001 }


}
