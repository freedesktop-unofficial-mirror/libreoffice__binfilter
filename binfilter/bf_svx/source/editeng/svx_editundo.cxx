/*************************************************************************
 *
 *  $RCSfile: svx_editundo.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:43:07 $
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
#include <editundo.hxx>
#include <editview.hxx>
#include <editeng.hxx>
namespace binfilter {

DBG_NAME( EditUndo );

#define MAX_UNDOS   100     // ab dieser Menge darf geloescht werden....
#define MIN_UNDOS   50      // soviel muss stehen bleiben...

#define NO_UNDO         0xFFFF
#define GROUP_NOTFOUND  0xFFFF

//STRIP001 TYPEINIT1( EditUndo, SfxUndoAction );
//STRIP001 TYPEINIT1( EditUndoDelContent, EditUndo );
//STRIP001 TYPEINIT1( EditUndoConnectParas, EditUndo );
//STRIP001 TYPEINIT1( EditUndoSplitPara, EditUndo );
/*N*/ TYPEINIT1( EditUndoInsertChars, EditUndo );
//STRIP001 TYPEINIT1( EditUndoRemoveChars, EditUndo );
//STRIP001 TYPEINIT1( EditUndoInsertFeature, EditUndo );
//STRIP001 TYPEINIT1( EditUndoMoveParagraphs, EditUndo );
//STRIP001 TYPEINIT1( EditUndoSetStyleSheet, EditUndo );
//STRIP001 TYPEINIT1( EditUndoSetParaAttribs, EditUndo );
//STRIP001 TYPEINIT1( EditUndoSetAttribs, EditUndo );
//STRIP001 TYPEINIT1( EditUndoTransliteration, EditUndo );
//STRIP001 TYPEINIT1( EditUndoMarkSelection, EditUndo );

//STRIP001 void lcl_DoSetSelection( EditView* pView, USHORT nPara )
//STRIP001 {
//STRIP001  EPaM aEPaM( nPara, 0 );
//STRIP001  EditPaM aPaM( pView->GetImpEditEngine()->CreateEditPaM( aEPaM ) );
//STRIP001  aPaM.SetIndex( aPaM.GetNode()->Len() );
//STRIP001  EditSelection aSel( aPaM, aPaM );
//STRIP001  pView->GetImpEditView()->SetEditSelection( aSel );
//STRIP001 }

// -----------------------------------------------------------------------
// EditUndoManager
// ------------------------------------------------------------------------
/*N*/ EditUndoManager::EditUndoManager( ImpEditEngine* p )
/*N*/ {
/*N*/   pImpEE = p;
/*N*/ }

//STRIP001 BOOL __EXPORT EditUndoManager::Undo( USHORT nCount )
//STRIP001 {
//STRIP001  if ( GetUndoActionCount() == 0 )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  DBG_ASSERT( pImpEE->GetActiveView(), "Active View?" );
//STRIP001
//STRIP001  if ( !pImpEE->GetActiveView() )
//STRIP001  {
//STRIP001      if ( pImpEE->GetEditViews().Count() )
//STRIP001          pImpEE->SetActiveView( pImpEE->GetEditViews().GetObject(0) );
//STRIP001      else
//STRIP001      {
//STRIP001          DBG_ERROR( "Undo in Engine ohne View nicht moeglich!" );
//STRIP001          return FALSE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  pImpEE->GetActiveView()->GetImpEditView()->DrawSelection(); // alte Selektion entfernen
//STRIP001
//STRIP001  pImpEE->SetUndoMode( TRUE );
//STRIP001  BOOL bDone = SfxUndoManager::Undo( nCount );
//STRIP001  pImpEE->SetUndoMode( FALSE );
//STRIP001
//STRIP001  EditSelection aNewSel( pImpEE->GetActiveView()->GetImpEditView()->GetEditSelection() );
//STRIP001  DBG_ASSERT( !aNewSel.IsInvalid(), "Ungueltige Selektion nach Undo()" );
//STRIP001  DBG_ASSERT( !aNewSel.DbgIsBuggy( pImpEE->GetEditDoc() ), "Kaputte Selektion nach Undo()" );
//STRIP001
//STRIP001  aNewSel.Min() = aNewSel.Max();
//STRIP001  pImpEE->GetActiveView()->GetImpEditView()->SetEditSelection( aNewSel );
//STRIP001  pImpEE->FormatAndUpdate( pImpEE->GetActiveView() );
//STRIP001
//STRIP001  return bDone;
//STRIP001 }

//STRIP001 BOOL __EXPORT EditUndoManager::Redo( USHORT nCount )
//STRIP001 {
//STRIP001  if ( GetRedoActionCount() == 0 )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  DBG_ASSERT( pImpEE->GetActiveView(), "Active View?" );
//STRIP001
//STRIP001  if ( !pImpEE->GetActiveView() )
//STRIP001  {
//STRIP001      if ( pImpEE->GetEditViews().Count() )
//STRIP001          pImpEE->SetActiveView( pImpEE->GetEditViews().GetObject(0) );
//STRIP001      else
//STRIP001      {
//STRIP001          DBG_ERROR( "Redo in Engine ohne View nicht moeglich!" );
//STRIP001          return FALSE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  pImpEE->GetActiveView()->GetImpEditView()->DrawSelection(); // alte Selektion entfernen
//STRIP001
//STRIP001  pImpEE->SetUndoMode( TRUE );
//STRIP001  BOOL bDone = SfxUndoManager::Redo( nCount );
//STRIP001  pImpEE->SetUndoMode( FALSE );
//STRIP001
//STRIP001  EditSelection aNewSel( pImpEE->GetActiveView()->GetImpEditView()->GetEditSelection() );
//STRIP001  DBG_ASSERT( !aNewSel.IsInvalid(), "Ungueltige Selektion nach Undo()" );
//STRIP001  DBG_ASSERT( !aNewSel.DbgIsBuggy( pImpEE->GetEditDoc() ), "Kaputte Selektion nach Redo()" );
//STRIP001
//STRIP001  aNewSel.Min() = aNewSel.Max();
//STRIP001  pImpEE->GetActiveView()->GetImpEditView()->SetEditSelection( aNewSel );
//STRIP001  pImpEE->FormatAndUpdate( pImpEE->GetActiveView() );
//STRIP001
//STRIP001  return bDone;
//STRIP001 }

// -----------------------------------------------------------------------
// EditUndo
// ------------------------------------------------------------------------
/*N*/ EditUndo::EditUndo( USHORT nI, ImpEditEngine* p )
/*N*/ {
/*N*/   DBG_CTOR( EditUndo, 0 );
/*N*/   nId = nI;
/*N*/   pImpEE = p;
/*N*/ }

/*N*/ EditUndo::~EditUndo()
/*N*/ {
/*N*/   DBG_DTOR( EditUndo, 0 );
/*N*/ }

/*N*/ USHORT __EXPORT EditUndo::GetId() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditUndo, 0 );
/*N*/   return nId;
/*N*/ }

//STRIP001 BOOL __EXPORT EditUndo::CanRepeat(SfxRepeatTarget&) const
//STRIP001 {
//STRIP001  return FALSE;
//STRIP001 }

/*N*/ XubString __EXPORT EditUndo::GetComment() const
/*N*/ {
/*N*/   XubString aComment;
/*N*/   if ( pImpEE )
/*N*/   {
/*N*/       EditEngine* pEditEng = pImpEE->GetEditEnginePtr();
/*N*/       aComment = pEditEng->GetUndoComment( GetId() );
/*N*/   }
/*N*/   return aComment;
/*N*/ }

// -----------------------------------------------------------------------
// EditUndoDelContent
// ------------------------------------------------------------------------
//STRIP001 EditUndoDelContent::EditUndoDelContent( ImpEditEngine* pImpEE, ContentNode* pNode, USHORT n )
//STRIP001                  : EditUndo( EDITUNDO_DELCONTENT, pImpEE )
//STRIP001 {
//STRIP001  pContentNode = pNode;
//STRIP001  nNode = n;
//STRIP001  bDelObject = TRUE;
//STRIP001 }

//STRIP001 EditUndoDelContent::~EditUndoDelContent()
//STRIP001 {
//STRIP001  if ( bDelObject )
//STRIP001      delete pContentNode;
//STRIP001 }

//STRIP001 void __EXPORT EditUndoDelContent::Undo()
//STRIP001 {
//STRIP001  DBG_ASSERT( GetImpEditEngine()->GetActiveView(), "Undo/Redo: Keine Active View!" );
//STRIP001  GetImpEditEngine()->InsertContent( pContentNode, nNode );
//STRIP001  bDelObject = FALSE; // gehoert wieder der Engine
//STRIP001  EditSelection aSel( EditPaM( pContentNode, 0 ), EditPaM( pContentNode, pContentNode->Len() ) );
//STRIP001  GetImpEditEngine()->GetActiveView()->GetImpEditView()->SetEditSelection( aSel );
//STRIP001 }

//STRIP001 void __EXPORT EditUndoDelContent::Redo()
//STRIP001 {
//STRIP001  DBG_ASSERT( GetImpEditEngine()->GetActiveView(), "Undo/Redo: Keine Active View!" );
//STRIP001
//STRIP001  ImpEditEngine* pImpEE = GetImpEditEngine();
//STRIP001
//STRIP001  // pNode stimmt nicht mehr, falls zwischendurch Undos, in denen
//STRIP001  // Absaetze verschmolzen sind.
//STRIP001  pContentNode = pImpEE->GetEditDoc().SaveGetObject( nNode );
//STRIP001  DBG_ASSERT( pContentNode, "EditUndoDelContent::Redo(): Node?!" );
//STRIP001
//STRIP001  delete pImpEE->GetParaPortions()[nNode];
//STRIP001  pImpEE->GetParaPortions().Remove( nNode );
//STRIP001
//STRIP001  // Node nicht loeschen, haengt im Undo!
//STRIP001  pImpEE->GetEditDoc().Remove( nNode );
//STRIP001  if( pImpEE->IsCallParaInsertedOrDeleted() )
//STRIP001      pImpEE->GetEditEnginePtr()->ParagraphDeleted( nNode );
//STRIP001
//STRIP001  DeletedNodeInfo* pInf = new DeletedNodeInfo( (ULONG)pContentNode, nNode );
//STRIP001  pImpEE->aDeletedNodes.Insert( pInf, pImpEE->aDeletedNodes.Count() );
//STRIP001  pImpEE->UpdateSelections();
//STRIP001
//STRIP001  ContentNode* pN = ( nNode < pImpEE->GetEditDoc().Count() )
//STRIP001      ? pImpEE->GetEditDoc().SaveGetObject( nNode )
//STRIP001      : pImpEE->GetEditDoc().SaveGetObject( nNode-1 );
//STRIP001  DBG_ASSERT( pN && ( pN != pContentNode ), "?! RemoveContent !? " );
//STRIP001  EditPaM aPaM( pN, pN->Len() );
//STRIP001
//STRIP001  bDelObject = TRUE;  // gehoert wieder dem Undo
//STRIP001
//STRIP001  pImpEE->GetActiveView()->GetImpEditView()->SetEditSelection( EditSelection( aPaM, aPaM ) );
//STRIP001 }

//STRIP001 void __EXPORT EditUndoDelContent::Repeat()
//STRIP001 {
//STRIP001  DBG_ERROR( "EditUndoDelContent::Repeat nicht implementiert!" );
//STRIP001 }

// -----------------------------------------------------------------------
// EditUndoConnectParas
// ------------------------------------------------------------------------
//STRIP001 EditUndoConnectParas::EditUndoConnectParas( ImpEditEngine* pImpEE, USHORT nN, USHORT nSP,
//STRIP001                                          const SfxItemSet& rLeftParaAttribs, const SfxItemSet& rRightParaAttribs,
//STRIP001                                          const SfxStyleSheet* pLeftStyle, const SfxStyleSheet* pRightStyle, BOOL bBkwrd )
//STRIP001                  :   EditUndo( EDITUNDO_CONNECTPARAS, pImpEE ),
//STRIP001                      aLeftParaAttribs( rLeftParaAttribs ),
//STRIP001                      aRightParaAttribs( rRightParaAttribs )
//STRIP001 {
//STRIP001  nNode   = nN;
//STRIP001  nSepPos = nSP;
//STRIP001
//STRIP001  if ( pLeftStyle )
//STRIP001  {
//STRIP001      aLeftStyleName = pLeftStyle->GetName();
//STRIP001      eLeftStyleFamily = pLeftStyle->GetFamily();
//STRIP001  }
//STRIP001  if ( pRightStyle )
//STRIP001  {
//STRIP001      aRightStyleName = pRightStyle->GetName();
//STRIP001      eRightStyleFamily = pRightStyle->GetFamily();
//STRIP001  }
//STRIP001
//STRIP001  bBackward = bBkwrd;
//STRIP001 }

//STRIP001 EditUndoConnectParas::~EditUndoConnectParas()
//STRIP001 {
//STRIP001 }

//STRIP001 void __EXPORT EditUndoConnectParas::Undo()
//STRIP001 {
//STRIP001  DBG_ASSERT( GetImpEditEngine()->GetActiveView(), "Undo/Redo: Keine Active View!" );
//STRIP001
//STRIP001  // Bei SplitContent darf noch kein ParagraphInserted gerufen werden,
//STRIP001  // weil der Outliner sich auf die Attribute verlaesst um die Tiefe
//STRIP001  // des Absatzes zu initialisieren
//STRIP001
//STRIP001  BOOL bCall = GetImpEditEngine()->IsCallParaInsertedOrDeleted();
//STRIP001  GetImpEditEngine()->SetCallParaInsertedOrDeleted( FALSE );
//STRIP001
//STRIP001  EditPaM aPaM = GetImpEditEngine()->SplitContent( nNode, nSepPos );
//STRIP001  GetImpEditEngine()->SetParaAttribs( nNode, aLeftParaAttribs );
//STRIP001  GetImpEditEngine()->SetParaAttribs( nNode+1, aRightParaAttribs );
//STRIP001
//STRIP001  GetImpEditEngine()->SetCallParaInsertedOrDeleted( bCall );
//STRIP001  if ( GetImpEditEngine()->IsCallParaInsertedOrDeleted() )
//STRIP001      GetImpEditEngine()->GetEditEnginePtr()->ParagraphInserted( nNode+1 );
//STRIP001
//STRIP001  if ( GetImpEditEngine()->GetStyleSheetPool() )
//STRIP001  {
//STRIP001      if ( aLeftStyleName.Len() )
//STRIP001          GetImpEditEngine()->SetStyleSheet( (USHORT)nNode, (SfxStyleSheet*)GetImpEditEngine()->GetStyleSheetPool()->Find( aLeftStyleName, eLeftStyleFamily ) );
//STRIP001      if ( aRightStyleName.Len() )
//STRIP001          GetImpEditEngine()->SetStyleSheet( nNode+1, (SfxStyleSheet*)GetImpEditEngine()->GetStyleSheetPool()->Find( aRightStyleName, eRightStyleFamily ) );
//STRIP001  }
//STRIP001
//STRIP001  GetImpEditEngine()->GetActiveView()->GetImpEditView()->SetEditSelection( EditSelection( aPaM, aPaM ) );
//STRIP001 }

//STRIP001 void __EXPORT EditUndoConnectParas::Redo()
//STRIP001 {
//STRIP001  DBG_ASSERT( GetImpEditEngine()->GetActiveView(), "Undo/Redo: Keine Active View!" );
//STRIP001  EditPaM aPaM = GetImpEditEngine()->ConnectContents( nNode, bBackward );
//STRIP001
//STRIP001  GetImpEditEngine()->GetActiveView()->GetImpEditView()->SetEditSelection( EditSelection( aPaM, aPaM ) );
//STRIP001 }

//STRIP001 void __EXPORT EditUndoConnectParas::Repeat()
//STRIP001 {
//STRIP001  DBG_ERROR( "EditUndoConnectParas::Repeat nicht implementiert!" );
//STRIP001 }

// -----------------------------------------------------------------------
// EditUndoSplitPara
// ------------------------------------------------------------------------
/*N*/ EditUndoSplitPara::EditUndoSplitPara( ImpEditEngine* pImpEE, USHORT nN, USHORT nSP )
/*N*/                   : EditUndo( EDITUNDO_SPLITPARA, pImpEE )
/*N*/ {
/*N*/   nNode   = nN;
/*N*/   nSepPos = nSP;
/*N*/ }

/*N*/ EditUndoSplitPara::~EditUndoSplitPara()
/*N*/ {
/*N*/ }

/*N*/ void __EXPORT EditUndoSplitPara::Undo()
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_ASSERT( GetImpEditEngine()->GetActiveView(), "Undo/Redo: Keine Active View!" );
//STRIP001  EditPaM aPaM = GetImpEditEngine()->ConnectContents( nNode, FALSE );
//STRIP001  GetImpEditEngine()->GetActiveView()->GetImpEditView()->SetEditSelection( EditSelection( aPaM, aPaM ) );
/*N*/ }

/*N*/ void __EXPORT EditUndoSplitPara::Redo()
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_ASSERT( GetImpEditEngine()->GetActiveView(), "Undo/Redo: Keine Active View!" );
//STRIP001  EditPaM aPaM = GetImpEditEngine()->SplitContent( nNode, nSepPos );
//STRIP001  GetImpEditEngine()->GetActiveView()->GetImpEditView()->SetEditSelection( EditSelection( aPaM, aPaM ) );
/*N*/ }

/*N*/ void __EXPORT EditUndoSplitPara::Repeat()
/*N*/ {
/*N*/   DBG_ERROR( "EditUndoSplitPara::Repeat nicht implementiert!" );
/*N*/ }

// -----------------------------------------------------------------------
// EditUndoInsertChars
// ------------------------------------------------------------------------
/*N*/ EditUndoInsertChars::EditUndoInsertChars( ImpEditEngine* pImpEE, const EPaM& rEPaM, const XubString& rStr )
/*N*/                   : EditUndo( EDITUNDO_INSERTCHARS, pImpEE ),
/*N*/                       aEPaM( rEPaM ), aText( rStr )
/*N*/ {
/*N*/ }

/*N*/ void __EXPORT EditUndoInsertChars::Undo()
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_ASSERT( GetImpEditEngine()->GetActiveView(), "Undo/Redo: Keine Active View!" );
//STRIP001  EditPaM aPaM( GetImpEditEngine()->CreateEditPaM( aEPaM ) );
//STRIP001  EditSelection aSel( aPaM, aPaM );
//STRIP001  aSel.Max().GetIndex() += aText.Len();
//STRIP001  EditPaM aNewPaM( GetImpEditEngine()->ImpDeleteSelection( aSel ) );
//STRIP001  GetImpEditEngine()->GetActiveView()->GetImpEditView()->SetEditSelection( EditSelection( aNewPaM, aNewPaM ) );
/*N*/ }

/*N*/ void __EXPORT EditUndoInsertChars::Redo()
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_ASSERT( GetImpEditEngine()->GetActiveView(), "Undo/Redo: Keine Active View!" );
//STRIP001  EditPaM aPaM( GetImpEditEngine()->CreateEditPaM( aEPaM ) );
//STRIP001  GetImpEditEngine()->ImpInsertText( EditSelection( aPaM, aPaM ), aText );
//STRIP001  EditPaM aNewPaM( aPaM );
//STRIP001  aNewPaM.GetIndex() += aText.Len();
//STRIP001  GetImpEditEngine()->GetActiveView()->GetImpEditView()->SetEditSelection( EditSelection( aPaM, aNewPaM ) );
/*N*/ }

/*N*/ BOOL __EXPORT EditUndoInsertChars::Merge( SfxUndoAction* pNextAction )
/*N*/ {
/*N*/   if ( !pNextAction->ISA( EditUndoInsertChars ) )
/*N*/       return FALSE;
/*N*/
/*N*/   EditUndoInsertChars* pNext = (EditUndoInsertChars*)pNextAction;
/*N*/
/*N*/   if ( aEPaM.nPara != pNext->aEPaM.nPara )
/*N*/       return FALSE;
/*N*/
/*N*/   if ( ( aEPaM.nIndex + aText.Len() ) == pNext->aEPaM.nIndex )
/*N*/   {
/*N*/       aText += pNext->aText;
/*N*/       return TRUE;
/*N*/   }
/*N*/   return FALSE;
/*N*/ }

/*N*/ void __EXPORT EditUndoInsertChars::Repeat()
/*N*/ {
/*N*/   DBG_ERROR( "EditUndoInsertChars::Repeat nicht implementiert!" );
/*N*/ }

// -----------------------------------------------------------------------
// EditUndoRemoveChars
// ------------------------------------------------------------------------
//STRIP001 EditUndoRemoveChars::EditUndoRemoveChars( ImpEditEngine* pImpEE, const EPaM& rEPaM, const XubString& rStr )
//STRIP001                  : EditUndo( EDITUNDO_REMOVECHARS, pImpEE ),
//STRIP001                      aEPaM( rEPaM ), aText( rStr )
//STRIP001 {
//STRIP001 }

//STRIP001 void __EXPORT EditUndoRemoveChars::Undo()
//STRIP001 {
//STRIP001  DBG_ASSERT( GetImpEditEngine()->GetActiveView(), "Undo/Redo: Keine Active View!" );
//STRIP001  EditPaM aPaM( GetImpEditEngine()->CreateEditPaM( aEPaM ) );
//STRIP001  EditSelection aSel( aPaM, aPaM );
//STRIP001  GetImpEditEngine()->ImpInsertText( aSel, aText );
//STRIP001  aSel.Max().GetIndex() += aText.Len();
//STRIP001  GetImpEditEngine()->GetActiveView()->GetImpEditView()->SetEditSelection( aSel );
//STRIP001 }

//STRIP001 void __EXPORT EditUndoRemoveChars::Redo()
//STRIP001 {
//STRIP001  DBG_ASSERT( GetImpEditEngine()->GetActiveView(), "Undo/Redo: Keine Active View!" );
//STRIP001  EditPaM aPaM( GetImpEditEngine()->CreateEditPaM( aEPaM ) );
//STRIP001  EditSelection aSel( aPaM, aPaM );
//STRIP001  aSel.Max().GetIndex() += aText.Len();
//STRIP001  EditPaM aNewPaM = GetImpEditEngine()->ImpDeleteSelection( aSel );
//STRIP001  GetImpEditEngine()->GetActiveView()->GetImpEditView()->SetEditSelection( aNewPaM );
//STRIP001 }

//STRIP001 void __EXPORT EditUndoRemoveChars::Repeat()
//STRIP001 {
//STRIP001  DBG_ERROR( "EditUndoRemoveChars::Repeat nicht implementiert!" );
//STRIP001 }

// -----------------------------------------------------------------------
// EditUndoInsertFeature
// ------------------------------------------------------------------------
/*N*/ EditUndoInsertFeature::EditUndoInsertFeature( ImpEditEngine* pImpEE, const EPaM& rEPaM, const SfxPoolItem& rFeature)
/*N*/                   : EditUndo( EDITUNDO_INSERTFEATURE, pImpEE ), aEPaM( rEPaM )
/*N*/ {
/*N*/   pFeature = rFeature.Clone();
/*N*/   DBG_ASSERT( pFeature, "Feature konnte nicht dupliziert werden: EditUndoInsertFeature" );
/*N*/ }

/*N*/ EditUndoInsertFeature::~EditUndoInsertFeature()
/*N*/ {
/*N*/   delete pFeature;
/*N*/ }

/*N*/ void __EXPORT EditUndoInsertFeature::Undo()
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_ASSERT( GetImpEditEngine()->GetActiveView(), "Undo/Redo: Keine Active View!" );
//STRIP001  EditPaM aPaM( GetImpEditEngine()->CreateEditPaM( aEPaM ) );
//STRIP001  EditSelection aSel( aPaM, aPaM );
//STRIP001  // Attribute werden dort implizit vom Dokument korrigiert...
//STRIP001  aSel.Max().GetIndex()++;
//STRIP001  EditPaM aNewPaM = GetImpEditEngine()->ImpDeleteSelection( aSel );
//STRIP001  aSel.Max().GetIndex()--;    // Fuer Selektion
//STRIP001  GetImpEditEngine()->GetActiveView()->GetImpEditView()->SetEditSelection( aSel );
/*N*/ }

/*N*/ void __EXPORT EditUndoInsertFeature::Redo()
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_ASSERT( GetImpEditEngine()->GetActiveView(), "Undo/Redo: Keine Active View!" );
//STRIP001  EditPaM aPaM( GetImpEditEngine()->CreateEditPaM( aEPaM ) );
//STRIP001  EditSelection aSel( aPaM, aPaM );
//STRIP001  GetImpEditEngine()->ImpInsertFeature( aSel, *pFeature );
//STRIP001  if ( pFeature->Which() == EE_FEATURE_FIELD )
//STRIP001      GetImpEditEngine()->UpdateFields();
//STRIP001  aSel.Max().GetIndex()++;
//STRIP001  GetImpEditEngine()->GetActiveView()->GetImpEditView()->SetEditSelection( aSel );
/*N*/ }

/*N*/ void __EXPORT EditUndoInsertFeature::Repeat()
/*N*/ {
/*N*/   DBG_ERROR( "EditUndoInsertFeature::Repeat nicht implementiert!" );
/*N*/ }

// -----------------------------------------------------------------------
// EditUndoMoveParagraphs
// ------------------------------------------------------------------------
//STRIP001 EditUndoMoveParagraphs::EditUndoMoveParagraphs
//STRIP001                          ( ImpEditEngine* pImpEE, const Range& rParas, USHORT n )
//STRIP001                          :   EditUndo( EDITUNDO_MOVEPARAGRAPHS, pImpEE ),
//STRIP001                              nParagraphs( rParas )
//STRIP001 {
//STRIP001  nDest = n;
//STRIP001 }

//STRIP001 EditUndoMoveParagraphs::~EditUndoMoveParagraphs()
//STRIP001 {
//STRIP001 }

//STRIP001 void __EXPORT EditUndoMoveParagraphs::Undo()
//STRIP001 {
//STRIP001  DBG_ASSERT( GetImpEditEngine()->GetActiveView(), "Undo/Redo: Keine Active View!" );
//STRIP001  Range aTmpRange( nParagraphs );
//STRIP001  long nTmpDest = aTmpRange.Min();
//STRIP001
//STRIP001  long nDiff = ( nDest - aTmpRange.Min() );
//STRIP001  aTmpRange.Min() += nDiff;
//STRIP001  aTmpRange.Max() += nDiff;
//STRIP001
//STRIP001  if ( nParagraphs.Min() < (long)nDest )
//STRIP001  {
//STRIP001      long nLen = aTmpRange.Len();
//STRIP001      aTmpRange.Min() -= nLen;
//STRIP001      aTmpRange.Max() -= nLen;
//STRIP001  }
//STRIP001  else
//STRIP001      nTmpDest += aTmpRange.Len();
//STRIP001
//STRIP001  EditSelection aNewSel( GetImpEditEngine()->MoveParagraphs( aTmpRange, (USHORT)nTmpDest, 0 ) );
//STRIP001  GetImpEditEngine()->GetActiveView()->GetImpEditView()->SetEditSelection( aNewSel );
//STRIP001 }

//STRIP001 void __EXPORT EditUndoMoveParagraphs::Redo()
//STRIP001 {
//STRIP001  DBG_ASSERT( GetImpEditEngine()->GetActiveView(), "Undo/Redo: Keine Active View!" );
//STRIP001  EditSelection aNewSel( GetImpEditEngine()->MoveParagraphs( nParagraphs, nDest, 0 ) );
//STRIP001  GetImpEditEngine()->GetActiveView()->GetImpEditView()->SetEditSelection( aNewSel );
//STRIP001 }

//STRIP001 void __EXPORT EditUndoMoveParagraphs::Repeat()
//STRIP001 {
//STRIP001  DBG_ERROR( "EditUndoMoveParagraphs::Repeat nicht implementiert!" );
//STRIP001 }

// -----------------------------------------------------------------------
// EditUndoSetStyleSheet
// ------------------------------------------------------------------------
/*N*/ EditUndoSetStyleSheet::EditUndoSetStyleSheet( ImpEditEngine* pImpEE, USHORT nP,
/*N*/                       const XubString& rPrevName, SfxStyleFamily ePrevFam,
/*N*/                       const XubString& rNewName, SfxStyleFamily eNewFam,
/*N*/                       const SfxItemSet& rPrevParaAttribs )
/*N*/   : EditUndo( EDITUNDO_STYLESHEET, pImpEE ), aPrevName( rPrevName ), aNewName( rNewName ),
/*N*/     aPrevParaAttribs( rPrevParaAttribs )
/*N*/ {
/*N*/   ePrevFamily = ePrevFam;
/*N*/   eNewFamily = eNewFam;
/*N*/   nPara = nP;
/*N*/ }

/*N*/ EditUndoSetStyleSheet::~EditUndoSetStyleSheet()
/*N*/ {
/*N*/ }

/*N*/ void __EXPORT EditUndoSetStyleSheet::Undo()
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_ASSERT( GetImpEditEngine()->GetActiveView(), "Undo/Redo: Keine Active View!" );
//STRIP001  GetImpEditEngine()->SetStyleSheet( nPara, (SfxStyleSheet*)GetImpEditEngine()->GetStyleSheetPool()->Find( aPrevName, ePrevFamily ) );
//STRIP001  GetImpEditEngine()->SetParaAttribs( nPara, aPrevParaAttribs );
//STRIP001  lcl_DoSetSelection( GetImpEditEngine()->GetActiveView(), nPara );
/*N*/ }

/*N*/ void __EXPORT EditUndoSetStyleSheet::Redo()
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_ASSERT( GetImpEditEngine()->GetActiveView(), "Undo/Redo: Keine Active View!" );
//STRIP001  GetImpEditEngine()->SetStyleSheet( nPara, (SfxStyleSheet*)GetImpEditEngine()->GetStyleSheetPool()->Find( aNewName, eNewFamily ) );
//STRIP001  lcl_DoSetSelection( GetImpEditEngine()->GetActiveView(), nPara );
/*N*/ }

/*N*/ void __EXPORT EditUndoSetStyleSheet::Repeat()
/*N*/ {
/*N*/   DBG_ERROR( "EditUndoSetStyleSheet::Repeat nicht implementiert!" );
/*N*/ }

// -----------------------------------------------------------------------
// EditUndoSetParaAttribs
// ------------------------------------------------------------------------
/*N*/ EditUndoSetParaAttribs::EditUndoSetParaAttribs( ImpEditEngine* pImpEE, USHORT nP, const SfxItemSet& rPrevItems, const SfxItemSet& rNewItems )
/*N*/   : EditUndo( EDITUNDO_PARAATTRIBS, pImpEE ),
/*N*/     aPrevItems( rPrevItems ),
/*N*/     aNewItems(rNewItems )
/*N*/ {
/*N*/   nPara = nP;
/*N*/ }

/*N*/ EditUndoSetParaAttribs::~EditUndoSetParaAttribs()
/*N*/ {
/*N*/ }

/*N*/ void __EXPORT EditUndoSetParaAttribs::Undo()
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_ASSERT( GetImpEditEngine()->GetActiveView(), "Undo/Redo: Keine Active View!" );
//STRIP001  GetImpEditEngine()->SetParaAttribs( nPara, aPrevItems );
//STRIP001  lcl_DoSetSelection( GetImpEditEngine()->GetActiveView(), nPara );
/*N*/ }

/*N*/ void __EXPORT EditUndoSetParaAttribs::Redo()
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_ASSERT( GetImpEditEngine()->GetActiveView(), "Undo/Redo: Keine Active View!" );
//STRIP001  GetImpEditEngine()->SetParaAttribs( nPara, aNewItems );
//STRIP001  lcl_DoSetSelection( GetImpEditEngine()->GetActiveView(), nPara );
/*N*/ }

/*N*/ void __EXPORT EditUndoSetParaAttribs::Repeat()
/*N*/ {
/*N*/   DBG_ERROR( "EditUndoSetParaAttribs::Repeat nicht implementiert!" );
/*N*/ }

// -----------------------------------------------------------------------
// EditUndoSetAttribs
// ------------------------------------------------------------------------
//STRIP001 EditUndoSetAttribs::EditUndoSetAttribs( ImpEditEngine* pImpEE, const ESelection& rESel, const SfxItemSet& rNewItems )
//STRIP001  : EditUndo( EDITUNDO_ATTRIBS, pImpEE ),
//STRIP001    aNewAttribs( rNewItems ),
//STRIP001    aESel( rESel )
//STRIP001 {
//STRIP001  // Wenn das EditUndoSetAttribs eigentlich ein RemoveAttribs ist, koennte
//STRIP001  // man das eigentlich an einem leeren ItemSet erkennen, aber dann muesste
//STRIP001  // an einigen Stellen abgefangen werden, das ggf. ein SetAttribs mit einem
//STRIP001  // leeren ItemSet gemacht wird.
//STRIP001  // => Ich habe lieber diesen Member spendiert...
//STRIP001  bSetIsRemove = FALSE;
//STRIP001  bRemoveParaAttribs = FALSE;
//STRIP001  nRemoveWhich = 0;
//STRIP001  nSpecial = 0;
//STRIP001 }

//STRIP001 EditUndoSetAttribs::~EditUndoSetAttribs()
//STRIP001 {
//STRIP001  // Items aus Pool holen...
//STRIP001  SfxItemPool* pPool = aNewAttribs.GetPool();
//STRIP001  USHORT nContents = aPrevAttribs.Count();
//STRIP001  for ( USHORT n = 0; n < nContents; n++ )
//STRIP001  {
//STRIP001      ContentAttribsInfo* pInf = aPrevAttribs[n];
//STRIP001      DBG_ASSERT( pInf, "Undo_DTOR (SetAttribs): pInf = NULL!" );
//STRIP001      for ( USHORT nAttr = 0; nAttr < pInf->GetPrevCharAttribs().Count(); nAttr++ )
//STRIP001      {
//STRIP001          EditCharAttrib* pX = pInf->GetPrevCharAttribs()[nAttr];
//STRIP001          DBG_ASSERT( pX, "Undo_DTOR (SetAttribs): pX = NULL!" );
//STRIP001          pPool->Remove( *pX->GetItem() );
//STRIP001          delete pX;
//STRIP001      }
//STRIP001      delete pInf;
//STRIP001  }
//STRIP001 }

//STRIP001 void __EXPORT EditUndoSetAttribs::Undo()
//STRIP001 {
//STRIP001  DBG_ASSERT( GetImpEditEngine()->GetActiveView(), "Undo/Redo: Keine Active View!" );
//STRIP001  ImpEditEngine* pImpEE = GetImpEditEngine();
//STRIP001  BOOL bFields = FALSE;
//STRIP001  for ( USHORT nPara = aESel.nStartPara; nPara <= aESel.nEndPara; nPara++ )
//STRIP001  {
//STRIP001      ContentAttribsInfo* pInf = aPrevAttribs[ (USHORT)(nPara-aESel.nStartPara) ];
//STRIP001      DBG_ASSERT( pInf, "Undo (SetAttribs): pInf = NULL!" );
//STRIP001
//STRIP001      // erstmal die Absatzattribute...
//STRIP001      pImpEE->SetParaAttribs( nPara, pInf->GetPrevParaAttribs() );
//STRIP001
//STRIP001      // Dann die Zeichenattribute...
//STRIP001      // Alle Attribute inkl. Features entfernen, werden wieder neu eingestellt.
//STRIP001      pImpEE->RemoveCharAttribs( nPara, 0, TRUE );
//STRIP001      DBG_ASSERT( pImpEE->GetEditDoc().SaveGetObject( nPara ), "Undo (SetAttribs): pNode = NULL!" );
//STRIP001      ContentNode* pNode = pImpEE->GetEditDoc().GetObject( nPara );
//STRIP001      for ( USHORT nAttr = 0; nAttr < pInf->GetPrevCharAttribs().Count(); nAttr++ )
//STRIP001      {
//STRIP001          EditCharAttrib* pX = pInf->GetPrevCharAttribs()[nAttr];
//STRIP001          DBG_ASSERT( pX, "Redo (SetAttribs): pX = NULL!" );
//STRIP001          // wird autom. 'eingepoolt'.
//STRIP001          pImpEE->GetEditDoc().InsertAttrib( pNode, pX->GetStart(), pX->GetEnd(), *pX->GetItem() );
//STRIP001          if ( pX->Which() == EE_FEATURE_FIELD )
//STRIP001              bFields = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  if ( bFields )
//STRIP001      pImpEE->UpdateFields();
//STRIP001  ImpSetSelection( GetImpEditEngine()->GetActiveView() );
//STRIP001 }

//STRIP001 void __EXPORT EditUndoSetAttribs::Redo()
//STRIP001 {
//STRIP001  DBG_ASSERT( GetImpEditEngine()->GetActiveView(), "Undo/Redo: Keine Active View!" );
//STRIP001  ImpEditEngine* pImpEE = GetImpEditEngine();
//STRIP001
//STRIP001  EditSelection aSel( pImpEE->CreateSel( aESel ) );
//STRIP001  if ( !bSetIsRemove )
//STRIP001      pImpEE->SetAttribs( aSel, aNewAttribs, nSpecial );
//STRIP001  else
//STRIP001      pImpEE->RemoveCharAttribs( aSel, bRemoveParaAttribs, nRemoveWhich );
//STRIP001
//STRIP001  ImpSetSelection( GetImpEditEngine()->GetActiveView() );
//STRIP001 }

//STRIP001 void __EXPORT EditUndoSetAttribs::Repeat()
//STRIP001 {
//STRIP001  DBG_ERROR( "EditUndoSetAttribs::Repeat nicht implementiert!" );
//STRIP001 }

//STRIP001 void EditUndoSetAttribs::ImpSetSelection( EditView* pView )
//STRIP001 {
//STRIP001  ImpEditEngine* pImpEE = GetImpEditEngine();
//STRIP001  EditSelection aSel( pImpEE->CreateSel( aESel ) );
//STRIP001  GetImpEditEngine()->GetActiveView()->GetImpEditView()->SetEditSelection( aSel );
//STRIP001 }

// -----------------------------------------------------------------------
// EditUndoTransliteration
// ------------------------------------------------------------------------
//STRIP001 EditUndoTransliteration::EditUndoTransliteration( ImpEditEngine* pImpEE, const ESelection& rESel, sal_Int32 nM )
//STRIP001  : EditUndo( EDITUNDO_TRANSLITERATE, pImpEE ), aOldESel( rESel )
//STRIP001 {
//STRIP001  nMode = nM;
//STRIP001  pTxtObj = NULL;
//STRIP001 }

//STRIP001 EditUndoTransliteration::~EditUndoTransliteration()
//STRIP001 {
//STRIP001  delete pTxtObj;
//STRIP001 }

//STRIP001 void __EXPORT EditUndoTransliteration::Undo()
//STRIP001 {
//STRIP001  DBG_ASSERT( GetImpEditEngine()->GetActiveView(), "Undo/Redo: Keine Active View!" );
//STRIP001
//STRIP001  ImpEditEngine* pImpEE = GetImpEditEngine();
//STRIP001
//STRIP001  EditSelection aSel( pImpEE->CreateSel( aNewESel ) );
//STRIP001
//STRIP001  // Insert text, but don't expand Atribs at the current position:
//STRIP001  aSel = pImpEE->DeleteSelected( aSel );
//STRIP001  EditSelection aDelSel( aSel );
//STRIP001  aSel = pImpEE->InsertParaBreak( aSel );
//STRIP001  aDelSel.Max() = aSel.Min();
//STRIP001  aDelSel.Max().GetNode()->GetCharAttribs().DeleteEmptyAttribs( pImpEE->GetEditDoc().GetItemPool() );
//STRIP001     EditSelection aNewSel;
//STRIP001  if ( pTxtObj )
//STRIP001  {
//STRIP001      aNewSel = pImpEE->InsertText( *pTxtObj, aSel );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      aNewSel = pImpEE->InsertText( aSel, aText );
//STRIP001  }
//STRIP001     if ( aNewSel.Min().GetNode() == aDelSel.Max().GetNode() )
//STRIP001     {
//STRIP001         aNewSel.Min().SetNode( aDelSel.Min().GetNode() );
//STRIP001         aNewSel.Min().GetIndex() += aDelSel.Min().GetIndex();
//STRIP001     }
//STRIP001     if ( aNewSel.Max().GetNode() == aDelSel.Max().GetNode() )
//STRIP001     {
//STRIP001         aNewSel.Max().SetNode( aDelSel.Min().GetNode() );
//STRIP001         aNewSel.Max().GetIndex() += aDelSel.Min().GetIndex();
//STRIP001     }
//STRIP001  pImpEE->DeleteSelected( aDelSel );
//STRIP001
//STRIP001  GetImpEditEngine()->GetActiveView()->GetImpEditView()->SetEditSelection( aNewSel );
//STRIP001 }

//STRIP001 void __EXPORT EditUndoTransliteration::Redo()
//STRIP001 {
//STRIP001  DBG_ASSERT( GetImpEditEngine()->GetActiveView(), "Undo/Redo: Keine Active View!" );
//STRIP001  ImpEditEngine* pImpEE = GetImpEditEngine();
//STRIP001
//STRIP001  EditSelection aSel( pImpEE->CreateSel( aOldESel ) );
//STRIP001  EditSelection aNewSel = pImpEE->TransliterateText( aSel, nMode );
//STRIP001  GetImpEditEngine()->GetActiveView()->GetImpEditView()->SetEditSelection( aNewSel );
//STRIP001 }

//STRIP001 void __EXPORT EditUndoTransliteration::Repeat()
//STRIP001 {
//STRIP001  DBG_ERROR( "EditUndoTransliteration::Repeat nicht implementiert!" );
//STRIP001 }

// -----------------------------------------------------------------------
// EditUndoMarkSelection
// ------------------------------------------------------------------------
//STRIP001 EditUndoMarkSelection::EditUndoMarkSelection( ImpEditEngine* pImpEE, const ESelection& rSel )
//STRIP001  : EditUndo( EDITUNDO_MARKSELECTION, pImpEE ), aSelection( rSel )
//STRIP001 {
//STRIP001 }

//STRIP001 EditUndoMarkSelection::~EditUndoMarkSelection()
//STRIP001 {
//STRIP001 }

//STRIP001 void __EXPORT EditUndoMarkSelection::Undo()
//STRIP001 {
//STRIP001  DBG_ASSERT( GetImpEditEngine()->GetActiveView(), "Undo/Redo: Keine Active View!" );
//STRIP001  if ( GetImpEditEngine()->GetActiveView() )
//STRIP001     {
//STRIP001         if ( GetImpEditEngine()->IsFormatted() )
//STRIP001          GetImpEditEngine()->GetActiveView()->SetSelection( aSelection );
//STRIP001         else
//STRIP001          GetImpEditEngine()->GetActiveView()->GetImpEditView()->SetEditSelection( GetImpEditEngine()->CreateSel( aSelection ) );
//STRIP001     }
//STRIP001 }

//STRIP001 void __EXPORT EditUndoMarkSelection::Redo()
//STRIP001 {
//STRIP001  // Fuer Redo unwichtig, weil am Anfang der Undo-Klammerung
//STRIP001 }

//STRIP001 void __EXPORT EditUndoMarkSelection::Repeat()
//STRIP001 {
//STRIP001  DBG_ERROR( "EditUndoMarkSelection::Repeat nicht implementiert!" );
//STRIP001 }

}
