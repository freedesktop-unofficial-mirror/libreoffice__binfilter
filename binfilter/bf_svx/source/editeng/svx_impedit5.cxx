/*************************************************************************
 *
 *  $RCSfile: svx_impedit5.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:21:42 $
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
#include <editdbg.hxx>

#include <svtools/smplhint.hxx>


#ifndef _SVX_LRSPITEM_HXX
#include <lrspitem.hxx>
#endif

/*N*/ void ImpEditEngine::SetStyleSheetPool( SfxStyleSheetPool* pSPool )
/*N*/ {
/*N*/   if ( pStylePool != pSPool )
/*N*/   {
/*N*/ //        if ( pStylePool )
/*N*/ //            EndListening( *pStylePool, TRUE );
/*N*/
/*N*/       pStylePool = pSPool;
/*N*/
/*N*/ //        if ( pStylePool )
/*N*/ //            StartListening( *pStylePool, TRUE );
/*N*/   }
/*N*/ }

/*N*/ SfxStyleSheet* ImpEditEngine::GetStyleSheet( USHORT nPara ) const
/*N*/ {
/*N*/   ContentNode* pNode = aEditDoc.SaveGetObject( nPara );
/*N*/   return pNode ? pNode->GetContentAttribs().GetStyleSheet() : NULL;
/*N*/ }

/*N*/ void ImpEditEngine::SetStyleSheet( EditSelection aSel, SfxStyleSheet* pStyle )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  aSel.Adjust( aEditDoc );
//STRIP001
//STRIP001  USHORT nStartPara = aEditDoc.GetPos( aSel.Min().GetNode() );
//STRIP001  USHORT nEndPara = aEditDoc.GetPos( aSel.Max().GetNode() );
//STRIP001
//STRIP001  BOOL bUpdate = GetUpdateMode();
//STRIP001  SetUpdateMode( FALSE );
//STRIP001
//STRIP001  for ( USHORT n = nStartPara; n <= nEndPara; n++ )
//STRIP001      SetStyleSheet( n, pStyle );
//STRIP001
//STRIP001  SetUpdateMode( bUpdate, 0 );
/*N*/ }

/*N*/ void ImpEditEngine::SetStyleSheet( USHORT nPara, SfxStyleSheet* pStyle )
/*N*/ {
/*N*/   DBG_ASSERT( GetStyleSheetPool() || !pStyle, "SetStyleSheet: No StyleSheetPool registered!" );
/*N*/   ContentNode* pNode = aEditDoc.SaveGetObject( nPara );
/*N*/   SfxStyleSheet* pCurStyle = pNode->GetStyleSheet();
/*N*/   if ( pStyle != pCurStyle )
/*N*/   {
/*N*/ #ifndef SVX_LIGHT
/*N*/       if ( IsUndoEnabled() && !IsInUndo() && aStatus.DoUndoAttribs() )
/*N*/       {
/*N*/           XubString aPrevStyleName;
/*N*/           if ( pCurStyle )
/*N*/               aPrevStyleName = pCurStyle->GetName();
/*N*/
/*N*/             XubString aNewStyleName;
/*N*/           if ( pStyle )
/*N*/               aNewStyleName = pStyle->GetName();
/*N*/
/*N*/           InsertUndo(
/*N*/               new EditUndoSetStyleSheet( this, aEditDoc.GetPos( pNode ),
/*N*/                       aPrevStyleName, pCurStyle ? pCurStyle->GetFamily() : SFX_STYLE_FAMILY_PARA,
/*N*/                         aNewStyleName, pStyle ? pStyle->GetFamily() : SFX_STYLE_FAMILY_PARA,
/*N*/                       pNode->GetContentAttribs().GetItems() ) );
/*N*/       }
/*N*/ #endif
/*N*/       if ( pCurStyle )
/*N*/           EndListening( *pCurStyle, FALSE );
/*N*/       pNode->SetStyleSheet( pStyle, aStatus.UseCharAttribs() );
/*N*/       if ( pStyle )
/*N*/           StartListening( *pStyle, FALSE );
/*N*/       ParaAttribsChanged( pNode );
/*N*/   }
/*N*/   FormatAndUpdate();
/*N*/ }

//STRIP001 void ImpEditEngine::UpdateParagraphsWithStyleSheet( SfxStyleSheet* pStyle )
//STRIP001 {
//STRIP001  SvxFont aFontFromStyle;
//STRIP001  CreateFont( aFontFromStyle, pStyle->GetItemSet() );
//STRIP001
//STRIP001  BOOL bUsed = FALSE;
//STRIP001  for ( USHORT nNode = 0; nNode < aEditDoc.Count(); nNode++ )
//STRIP001  {
//STRIP001      ContentNode* pNode = aEditDoc.GetObject( nNode );
//STRIP001      if ( pNode->GetStyleSheet() == pStyle )
//STRIP001      {
//STRIP001          bUsed = TRUE;
//STRIP001          if ( aStatus.UseCharAttribs() )
//STRIP001              pNode->SetStyleSheet( pStyle, aFontFromStyle );
//STRIP001          else
//STRIP001              pNode->SetStyleSheet( pStyle, FALSE );
//STRIP001
//STRIP001          ParaAttribsChanged( pNode );
//STRIP001      }
//STRIP001  }
//STRIP001  if ( bUsed )
//STRIP001  {
//STRIP001      GetEditEnginePtr()->StyleSheetChanged( pStyle );
//STRIP001      FormatAndUpdate();
//STRIP001  }
//STRIP001 }

//STRIP001 void ImpEditEngine::RemoveStyleFromParagraphs( SfxStyleSheet* pStyle )
//STRIP001 {
//STRIP001  for ( USHORT nNode = 0; nNode < aEditDoc.Count(); nNode++ )
//STRIP001  {
//STRIP001      ContentNode* pNode = aEditDoc.GetObject(nNode);
//STRIP001      if ( pNode->GetStyleSheet() == pStyle )
//STRIP001      {
//STRIP001          pNode->SetStyleSheet( NULL );
//STRIP001          ParaAttribsChanged( pNode );
//STRIP001      }
//STRIP001  }
//STRIP001  FormatAndUpdate();
//STRIP001 }

//STRIP001 void ImpEditEngine::Notify( SfxBroadcaster& rBC, const SfxHint& rHint )
//STRIP001 {
//STRIP001  // Damit nicht beim Destruieren unnoetig formatiert wird:
//STRIP001  if ( !bDowning )
//STRIP001  {
//STRIP001      DBG_CHKOBJ( GetEditEnginePtr(), EditEngine, 0 );
//STRIP001
//STRIP001      SfxStyleSheet* pStyle = NULL;
//STRIP001      ULONG nId = 0;
//STRIP001
//STRIP001      if ( rHint.ISA( SfxStyleSheetHint ) )
//STRIP001      {
//STRIP001          const SfxStyleSheetHint& rH = (const SfxStyleSheetHint&) rHint;
//STRIP001          DBG_ASSERT( rH.GetStyleSheet()->ISA( SfxStyleSheet ), "Kein SfxStyleSheet!" );
//STRIP001          pStyle = (SfxStyleSheet*) rH.GetStyleSheet();
//STRIP001          nId = rH.GetHint();
//STRIP001      }
//STRIP001      else if ( ( rHint.Type() == TYPE(SfxSimpleHint ) ) && ( rBC.ISA( SfxStyleSheet ) ) )
//STRIP001      {
//STRIP001          pStyle = (SfxStyleSheet*)&rBC;
//STRIP001          nId = ((SfxSimpleHint&)rHint).GetId();
//STRIP001      }
//STRIP001
//STRIP001      if ( pStyle )
//STRIP001      {
//STRIP001          if ( ( nId == SFX_HINT_DYING ) ||
//STRIP001               ( nId == SFX_STYLESHEET_INDESTRUCTION ) ||
//STRIP001               ( nId == SFX_STYLESHEET_ERASED ) )
//STRIP001          {
//STRIP001              RemoveStyleFromParagraphs( pStyle );
//STRIP001          }
//STRIP001          else if ( ( nId == SFX_HINT_DATACHANGED ) ||
//STRIP001                    ( nId == SFX_STYLESHEET_MODIFIED ) )
//STRIP001          {
//STRIP001              UpdateParagraphsWithStyleSheet( pStyle );
//STRIP001
//STRIP001              // Alle Absaetze mit EditStyles, die das geaenderte Style
//STRIP001              // irgendwie als Parent haben, muessen formatiert werden.
//STRIP001              // ULONG nStyles = pMyStylePool->GetStyles().Count();
//STRIP001              // for ( ULONG nStyle = 0; nStyle < nStyles; nStyle++ )
//STRIP001              // {
//STRIP001              //  EditStyleSheet* pES = (EditStyleSheet*)pMyStylePool->GetStyles().GetObject( nStyle );
//STRIP001              //  DBG_ASSERT( pES, "NULL-Pointer im StyleSheetPool!" );
//STRIP001              //  if ( pES->IsUsed() && pES->HasStyleAsAnyParent( *pStyle ) )
//STRIP001              //      UpdateParagraphsWithStyleSheet( pES );
//STRIP001              // }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 EditUndoSetAttribs* ImpEditEngine::CreateAttribUndo( EditSelection aSel, const SfxItemSet& rSet )
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  DBG_ASSERT( !aSel.DbgIsBuggy( aEditDoc ), "CreateAttribUndo: Fehlerhafte Selektion" );
//STRIP001  aSel.Adjust( aEditDoc );
//STRIP001
//STRIP001  ESelection aESel( CreateESel( aSel ) );
//STRIP001
//STRIP001  USHORT nStartNode = aEditDoc.GetPos( aSel.Min().GetNode() );
//STRIP001  USHORT nEndNode = aEditDoc.GetPos( aSel.Max().GetNode() );
//STRIP001
//STRIP001  DBG_ASSERT( nStartNode <= nEndNode, "CreateAttribUndo: Start > End ?!" );
//STRIP001
//STRIP001  EditUndoSetAttribs* pUndo = NULL;
//STRIP001  if ( rSet.GetPool() != &aEditDoc.GetItemPool() )
//STRIP001  {
//STRIP001      SfxItemSet aTmpSet( GetEmptyItemSet() );
//STRIP001      aTmpSet.Put( rSet );
//STRIP001      pUndo = new EditUndoSetAttribs( this, aESel, aTmpSet );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pUndo = new EditUndoSetAttribs( this, aESel, rSet );
//STRIP001  }
//STRIP001
//STRIP001  SfxItemPool* pPool = pUndo->GetNewAttribs().GetPool();
//STRIP001
//STRIP001  for ( USHORT nPara = nStartNode; nPara <= nEndNode; nPara++ )
//STRIP001  {
//STRIP001      ContentNode* pNode = aEditDoc.GetObject( nPara );
//STRIP001      DBG_ASSERT( aEditDoc.SaveGetObject( nPara ), "Node nicht gefunden: CreateAttribUndo" );
//STRIP001      ContentAttribsInfo* pInf = new ContentAttribsInfo( pNode->GetContentAttribs().GetItems() );
//STRIP001      pUndo->GetContentInfos().Insert( pInf, pUndo->GetContentInfos().Count() );
//STRIP001
//STRIP001      for ( USHORT nAttr = 0; nAttr < pNode->GetCharAttribs().Count(); nAttr++ )
//STRIP001      {
//STRIP001          EditCharAttribPtr pAttr = pNode->GetCharAttribs().GetAttribs()[ nAttr ];
//STRIP001          if ( pAttr->GetLen() )
//STRIP001          {
//STRIP001              EditCharAttribPtr pNew = MakeCharAttrib( *pPool, *pAttr->GetItem(), pAttr->GetStart(), pAttr->GetEnd() );
//STRIP001              pInf->GetPrevCharAttribs().Insert( pNew, pInf->GetPrevCharAttribs().Count() );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return pUndo;
//STRIP001 #else
//STRIP001  return 0;
//STRIP001 #endif
//STRIP001 }

//STRIP001 void ImpEditEngine::UndoActionStart( USHORT nId, const ESelection& aSel )
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  if ( IsUndoEnabled() && !IsInUndo() )
//STRIP001  {
//STRIP001      GetUndoManager().EnterListAction( GetEditEnginePtr()->GetUndoComment( nId ), XubString(), nId );
//STRIP001      DBG_ASSERT( !pUndoMarkSelection, "UndoAction SelectionMarker?" );
//STRIP001      pUndoMarkSelection = new ESelection( aSel );
//STRIP001  }
//STRIP001 #endif
//STRIP001 }

/*N*/ void ImpEditEngine::UndoActionStart( USHORT nId )
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   if ( IsUndoEnabled() && !IsInUndo() )
/*N*/   {
/*N*/       GetUndoManager().EnterListAction( GetEditEnginePtr()->GetUndoComment( nId ), XubString(), nId );
/*N*/       DBG_ASSERT( !pUndoMarkSelection, "UndoAction SelectionMarker?" );
/*N*/   }
/*N*/ #endif
/*N*/ }

/*N*/ void ImpEditEngine::UndoActionEnd( USHORT nId )
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   if ( IsUndoEnabled() && !IsInUndo() )
/*N*/   {
/*N*/       GetUndoManager().LeaveListAction();
/*N*/       delete pUndoMarkSelection;
/*N*/       pUndoMarkSelection = NULL;
/*N*/   }
/*N*/ #endif
/*N*/ }

/*N*/ void ImpEditEngine::InsertUndo( EditUndo* pUndo, BOOL bTryMerge )
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   DBG_ASSERT( !IsInUndo(), "InsertUndo im Undomodus!" );
/*N*/   if ( pUndoMarkSelection )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 EditUndoMarkSelection* pU = new EditUndoMarkSelection( this, *pUndoMarkSelection );
//STRIP001 /*?*/        GetUndoManager().AddUndoAction( pU, FALSE );
//STRIP001 /*?*/        delete pUndoMarkSelection;
//STRIP001 /*?*/        pUndoMarkSelection = NULL;
/*N*/   }
/*N*/   GetUndoManager().AddUndoAction( pUndo, bTryMerge );
/*N*/ #endif
/*N*/ }

/*N*/ void ImpEditEngine::ResetUndoManager()
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   if ( HasUndoManager() )
/*N*/       GetUndoManager().Clear();
/*N*/ #endif
/*N*/ }

/*N*/ void ImpEditEngine::EnableUndo( BOOL bEnable )
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   // Beim Umschalten des Modus Liste loeschen:
/*N*/   if ( bEnable != IsUndoEnabled() )
/*N*/       ResetUndoManager();
/*N*/
/*N*/   bUndoEnabled = bEnable;
/*N*/ #endif
/*N*/ }

//STRIP001 BOOL ImpEditEngine::Undo( EditView* pView )
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  if ( HasUndoManager() && GetUndoManager().GetUndoActionCount() )
//STRIP001  {
//STRIP001      SetActiveView( pView );
//STRIP001      GetUndoManager().Undo( 1 );
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001 #endif
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 BOOL ImpEditEngine::Redo( EditView* pView )
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  if ( HasUndoManager() && GetUndoManager().GetRedoActionCount() )
//STRIP001  {
//STRIP001      SetActiveView( pView );
//STRIP001      GetUndoManager().Redo( 0 );
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001 #endif
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 BOOL ImpEditEngine::Repeat( EditView* /* pView */ )
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  if ( HasUndoManager() && GetUndoManager().GetRepeatActionCount() )
//STRIP001  {
//STRIP001      DBG_WARNING( "Repeat nicht implementiert!" );
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001 #endif
//STRIP001  return FALSE;
//STRIP001 }

/*N*/ SfxItemSet ImpEditEngine::GetAttribs( EditSelection aSel, BOOL bOnlyHardAttrib )
/*N*/ {
/*N*/   DBG_CHKOBJ( GetEditEnginePtr(), EditEngine, 0 );
/*N*/
/*N*/   aSel.Adjust( aEditDoc );
/*N*/
/*N*/ #if OSL_DEBUG_LEVEL > 1
/*N*/ //    if ( ( aSel.Min().GetNode() == aSel.Max().GetNode() ) && ( bOnlyHardAttrib == EditEngineAttribs_All ) )
/*N*/ //        return GetAttribs( aEditDoc.GetPos( aSel.Min().GetNode() ), aSel.Min().GetIndex(), aSel.Max().GetIndex(), GETATTRIBS_ALL );
/*N*/ #endif
/*N*/
/*N*/
/*N*/   SfxItemSet aCurSet( GetEmptyItemSet() );
/*N*/
/*N*/   USHORT nStartNode = aEditDoc.GetPos( aSel.Min().GetNode() );
/*N*/   USHORT nEndNode = aEditDoc.GetPos( aSel.Max().GetNode() );
/*N*/
/*N*/   // ueber die Absaetze iterieren...
/*N*/   for ( USHORT nNode = nStartNode; nNode <= nEndNode; nNode++ )
/*N*/   {
/*N*/       ContentNode* pNode = aEditDoc.GetObject( nNode );
/*N*/       DBG_ASSERT( aEditDoc.SaveGetObject( nNode ), "Node nicht gefunden: GetAttrib" );
/*N*/
/*N*/       xub_StrLen nStartPos = 0;
/*N*/       xub_StrLen nEndPos = pNode->Len();
/*N*/       if ( nNode == nStartNode )
/*N*/           nStartPos = aSel.Min().GetIndex();
/*N*/       if ( nNode == nEndNode ) // kann auch == nStart sein!
/*N*/           nEndPos = aSel.Max().GetIndex();
/*N*/
/*N*/       // Problem: Vorlagen....
/*N*/       // => Andersrum:
/*N*/       // 1) Harte Zeichenattribute, wie gehabt...
/*N*/       // 2) Nur wenn OFF, Style and Absatzattr. pruefen...
/*N*/
/*N*/       // Erst die ganz harte Formatierung...
/*N*/       aEditDoc.FindAttribs( pNode, nStartPos, nEndPos, aCurSet );
/*N*/
/*N*/       if( bOnlyHardAttrib != EditEngineAttribs_OnlyHard )
/*N*/       {
/*N*/           // Und dann Absatzformatierung und Vorlage...
/*N*/           // SfxStyleSheet* pStyle = pNode->GetStyleSheet();
/*N*/           for ( USHORT nWhich = EE_ITEMS_START; nWhich <= EE_CHAR_END; nWhich++)
/*N*/           {
/*N*/               if ( aCurSet.GetItemState( nWhich ) == SFX_ITEM_OFF )
/*N*/               {
/*N*/                   if ( bOnlyHardAttrib == EditEngineAttribs_All )
/*N*/                   {
/*N*/                       const SfxPoolItem& rItem = pNode->GetContentAttribs().GetItem( nWhich );
/*N*/                       aCurSet.Put( rItem );
/*N*/                   }
/*N*/                   else if ( pNode->GetContentAttribs().GetItems().GetItemState( nWhich ) == SFX_ITEM_ON )
/*N*/                   {
/*?*/                       const SfxPoolItem& rItem = pNode->GetContentAttribs().GetItems().Get( nWhich );
/*?*/                       aCurSet.Put( rItem );
/*N*/                   }
/*N*/               }
/*N*/               else if ( aCurSet.GetItemState( nWhich ) == SFX_ITEM_ON )
/*N*/               {
/*N*/                   const SfxPoolItem* pItem = NULL;
/*N*/                   if ( bOnlyHardAttrib == EditEngineAttribs_All )
/*N*/                   {
/*N*/                       pItem = &pNode->GetContentAttribs().GetItem( nWhich );
/*N*/                   }
/*N*/                   else if ( pNode->GetContentAttribs().GetItems().GetItemState( nWhich ) == SFX_ITEM_ON )
/*N*/                   {
/*?*/                       pItem = &pNode->GetContentAttribs().GetItems().Get( nWhich );
/*N*/                   }
/*N*/                   // pItem can only be NULL when bOnlyHardAttrib...
/*N*/                   if ( !pItem || ( *pItem != aCurSet.Get( nWhich ) ) )
/*N*/                   {
/*N*/                       // Problem: Wenn Absatzvorlage mit z.B. Font,
/*N*/                       // aber Font hart und anders und komplett in Selektion
/*N*/                       // Falsch, wenn invalidiert....
/*N*/                       // => Lieber nicht invalidieren, UMSTELLEN!
/*N*/                       // Besser waere, Absatzweise ein ItemSet zu fuellen
/*N*/                       // und dieses mit dem gesmten vergleichen.
/*N*/   //                      aCurSet.InvalidateItem( nWhich );
/*N*/                       if ( nWhich <= EE_PARA_END )
/*?*/                           aCurSet.InvalidateItem( nWhich );
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // Leere Slots mit Defaults fuellen...
/*N*/     if ( bOnlyHardAttrib == EditEngineAttribs_All )
/*N*/     {
/*N*/       for ( USHORT nWhich = EE_ITEMS_START; nWhich <= EE_CHAR_END; nWhich++ )
/*N*/       {
/*N*/           if ( aCurSet.GetItemState( nWhich ) == SFX_ITEM_OFF )
/*N*/           {
/*?*/               aCurSet.Put( aEditDoc.GetItemPool().GetDefaultItem( nWhich ) );
/*N*/           }
/*N*/       }
/*N*/     }
/*N*/
/*N*/ #ifdef EDITDEBUG
/*N*/ /*
/*N*/ #ifdef MAC
/*N*/       FILE* fp = fopen( "debug.log", "a" );
/*N*/ #elif defined UNX
/*N*/       FILE* fp = fopen( "/tmp/debug.log", "a" );
/*N*/ #else
/*N*/       FILE* fp = fopen( "d:\\debug.log", "a" );
/*N*/ #endif
/*N*/       if ( fp )
/*N*/       {
/*N*/           fprintf( fp, "\n\n<= Attribute: Absatz %i\n", nNode );
/*N*/           DbgOutItemSet( fp, aCurSet, TRUE, FALSE );
/*N*/           fclose( fp );
/*N*/       }
/*N*/ */
/*N*/ #endif
/*N*/
/*N*/   return aCurSet;
/*N*/ }


/*N*/ SfxItemSet ImpEditEngine::GetAttribs( USHORT nPara, USHORT nStart, USHORT nEnd, sal_uInt8 nFlags ) const
/*N*/ {
/*N*/     // MT: #94002# Optimized function with less Puts(), which cause unnecessary cloning from default items.
/*N*/     // If this works, change GetAttribs( EditSelection ) to use this for each paragraph and merge the results!
/*N*/
/*N*/     DBG_CHKOBJ( GetEditEnginePtr(), EditEngine, 0 );
/*N*/
/*N*/     ContentNode* pNode = aEditDoc.SaveGetObject( nPara );
/*N*/     DBG_ASSERT( pNode, "GetAttribs - unknown paragraph!" );
/*N*/     DBG_ASSERT( nStart <= nEnd, "getAttribs: Start > End not supported!" );
/*N*/
/*N*/     SfxItemSet aAttribs( ((ImpEditEngine*)this)->GetEmptyItemSet() );
/*N*/
/*N*/     if ( pNode )
/*N*/     {
/*N*/         if ( nEnd > pNode->Len() )
/*N*/             nEnd = pNode->Len();
/*?*/
/*N*/         if ( nStart > nEnd )
/*?*/             nStart = nEnd;
/*N*/
/*N*/         // StyleSheet / Parattribs...
/*N*/
/*N*/         if ( pNode->GetStyleSheet() && ( nFlags & GETATTRIBS_STYLESHEET ) )
/*N*/             aAttribs.Set( pNode->GetStyleSheet()->GetItemSet(), TRUE );
/*N*/
/*N*/         if ( nFlags & GETATTRIBS_PARAATTRIBS )
/*N*/             aAttribs.Put( pNode->GetContentAttribs().GetItems() );
/*N*/
/*N*/         // CharAttribs...
/*N*/
/*N*/         if ( nFlags & GETATTRIBS_CHARATTRIBS )
/*N*/         {
/*N*/             // Make testing easier...
/*N*/             pNode->GetCharAttribs().OptimizeRanges( ((ImpEditEngine*)this)->GetEditDoc().GetItemPool() );
/*N*/
/*N*/             const CharAttribArray& rAttrs = pNode->GetCharAttribs().GetAttribs();
/*N*/             for ( USHORT nAttr = 0; nAttr < rAttrs.Count(); nAttr++ )
/*N*/             {
/*N*/                 EditCharAttrib* pAttr = rAttrs.GetObject( nAttr );
/*N*/
/*N*/                 if ( nStart == nEnd )
/*N*/                 {
/*N*/                     USHORT nCursorPos = nStart;
/*N*/                     if ( ( pAttr->GetStart() <= nCursorPos ) && ( pAttr->GetEnd() >= nCursorPos ) )
/*N*/                     {
/*N*/                         // To be used the attribute has to start BEFORE the position, or it must be a
/*N*/                         // new empty attr AT the position, or we are on position 0.
/*N*/                         if ( ( pAttr->GetStart() < nCursorPos ) || pAttr->IsEmpty() || !nCursorPos )
/*N*/                         {
/*N*/                             // maybe this attrib ends here and a new attrib with 0 Len may follow and be valid here,
/*N*/                             // but that s no problem, the empty item will come later and win.
/*N*/                             aAttribs.Put( *pAttr->GetItem() );
/*N*/                         }
/*N*/                     }
/*N*/                 }
/*N*/                 else
/*N*/                 {
/*N*/                     // Check every attribute covering the area, partial or full.
/*N*/                     if ( ( pAttr->GetStart() < nEnd ) && ( pAttr->GetEnd() > nStart ) )
/*N*/                     {
/*N*/                         if ( ( pAttr->GetStart() <= nStart ) && ( pAttr->GetEnd() >= nEnd ) )
/*N*/                         {
/*N*/                             // full coverage
/*N*/                             aAttribs.Put( *pAttr->GetItem() );
/*N*/                         }
/*N*/                         else
/*N*/                         {
/*N*/                             // OptimizeRagnge() assures that not the same attr can follow for full coverage
/*N*/                             // only partial, check with current, when using para/styhe, otherwise invalid.
/*N*/                             if ( !( nFlags & (GETATTRIBS_PARAATTRIBS|GETATTRIBS_STYLESHEET) ) ||
/*N*/                                 ( *pAttr->GetItem() != aAttribs.Get( pAttr->Which() ) ) )
/*N*/                             {
/*N*/                                 aAttribs.InvalidateItem( pAttr->Which() );
/*N*/                             }
/*N*/                         }
/*N*/                     }
/*N*/                 }
/*N*/
/*N*/                 if ( pAttr->GetStart() > nEnd )
/*N*/                 {
/*N*/                     break;
/*N*/                 }
/*N*/             }
/*N*/         }
/*N*/   }
/*N*/
/*N*/   return aAttribs;
/*N*/ }


/*N*/ void ImpEditEngine::SetAttribs( EditSelection aSel, const SfxItemSet& rSet, BYTE nSpecial )
/*N*/ {
/*N*/   aSel.Adjust( aEditDoc );
/*N*/
/*N*/   // Wenn keine Selektion => die Attribute aufs Wort anwenden.
/*N*/   // ( Der RTF-Perser sollte die Methode eigentlich nie ohne Range rufen )
/*N*/   if ( ( nSpecial == ATTRSPECIAL_WHOLEWORD ) && !aSel.HasRange() )
/*?*/       aSel = SelectWord( aSel, ::com::sun::star::i18n::WordType::ANYWORD_IGNOREWHITESPACES, FALSE );
/*N*/
/*N*/   USHORT nStartNode = aEditDoc.GetPos( aSel.Min().GetNode() );
/*N*/   USHORT nEndNode = aEditDoc.GetPos( aSel.Max().GetNode() );
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/   if ( IsUndoEnabled() && !IsInUndo() && aStatus.DoUndoAttribs() )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 EditUndoSetAttribs* pUndo = CreateAttribUndo( aSel, rSet );
//STRIP001 /*?*/        pUndo->SetSpecial( nSpecial );
//STRIP001 /*?*/        InsertUndo( pUndo );
/*N*/   }
/*N*/ #endif
/*N*/
/*N*/   BOOL bCheckLanguage = FALSE;
/*N*/   if ( GetStatus().DoOnlineSpelling() )
/*N*/   {
/*?*/       bCheckLanguage = ( rSet.GetItemState( EE_CHAR_LANGUAGE ) == SFX_ITEM_ON ) ||
/*?*/                        ( rSet.GetItemState( EE_CHAR_LANGUAGE_CJK ) == SFX_ITEM_ON ) ||
/*?*/                        ( rSet.GetItemState( EE_CHAR_LANGUAGE_CTL ) == SFX_ITEM_ON );
/*N*/   }
/*N*/
/*N*/   // ueber die Absaetze iterieren...
/*N*/   for ( USHORT nNode = nStartNode; nNode <= nEndNode; nNode++ )
/*N*/   {
/*N*/       BOOL bParaAttribFound = FALSE;
/*N*/       BOOL bCharAttribFound = FALSE;
/*N*/
/*N*/       ContentNode* pNode = aEditDoc.GetObject( nNode );
/*N*/       ParaPortion* pPortion = GetParaPortions().GetObject( nNode );
/*N*/
/*N*/       DBG_ASSERT( aEditDoc.SaveGetObject( nNode ), "Node nicht gefunden: SetAttribs" );
/*N*/       DBG_ASSERT( GetParaPortions().GetObject( nNode ), "Portion nicht gefunden: SetAttribs" );
/*N*/
/*N*/       xub_StrLen nStartPos = 0;
/*N*/       xub_StrLen nEndPos = pNode->Len();
/*N*/       if ( nNode == nStartNode )
/*N*/           nStartPos = aSel.Min().GetIndex();
/*N*/       if ( nNode == nEndNode ) // kann auch == nStart sein!
/*N*/           nEndPos = aSel.Max().GetIndex();
/*N*/
/*N*/       // ueber die Items iterieren...
/*N*/ #ifdef EDITDEBUG
/*N*/ //        FILE* fp = fopen( "d:\\debug.log", "a" );
/*N*/ //        if ( fp )
/*N*/ //        {
/*N*/ //            fprintf( fp, "\n\n=> Zeichen-Attribute: Absatz %i, %i-%i\n", nNode, nStartPos, nEndPos );
/*N*/ //            DbgOutItemSet( fp, rSet, TRUE, FALSE );
/*N*/ //            fclose( fp );
/*N*/ //        }
/*N*/ #endif
/*N*/
/*N*/       for ( USHORT nWhich = EE_ITEMS_START; nWhich <= EE_CHAR_END; nWhich++)
/*N*/       {
/*N*/           if ( rSet.GetItemState( nWhich ) == SFX_ITEM_ON )
/*N*/           {
/*N*/               const SfxPoolItem& rItem = rSet.Get( nWhich );
/*N*/               if ( nWhich <= EE_PARA_END )
/*N*/               {
/*?*/                   pNode->GetContentAttribs().GetItems().Put( rItem );
/*?*/                   bParaAttribFound = TRUE;
/*N*/               }
/*N*/               else
/*N*/               {
/*N*/                   aEditDoc.InsertAttrib( pNode, nStartPos, nEndPos, rItem );
/*N*/                   bCharAttribFound = TRUE;
/*N*/                   if ( nSpecial == ATTRSPECIAL_EDGE )
/*N*/                   {
/*?*/                       CharAttribArray& rAttribs = pNode->GetCharAttribs().GetAttribs();
/*?*/                       USHORT nAttrs = rAttribs.Count();
/*?*/                       for ( USHORT n = 0; n < nAttrs; n++ )
/*?*/                       {
/*?*/                           EditCharAttrib* pAttr = rAttribs.GetObject( n );
/*?*/                           if ( pAttr->GetStart() > nEndPos )
/*?*/                               break;
/*?*/
/*?*/                           if ( ( pAttr->GetEnd() == nEndPos ) && ( pAttr->Which() == nWhich ) )
/*?*/                           {
/*?*/                               pAttr->SetEdge( TRUE );
/*?*/                               break;
/*?*/                           }
/*?*/                       }
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/
/*N*/       if ( bParaAttribFound )
/*N*/       {
/*?*/           ParaAttribsChanged( pPortion->GetNode() );
/*N*/       }
/*N*/       else if ( bCharAttribFound )
/*N*/       {
/*N*/           bFormatted = FALSE;
/*N*/           if ( !pNode->Len() || ( nStartPos != nEndPos  ) )
/*N*/           {
/*N*/               pPortion->MarkSelectionInvalid( nStartPos, nEndPos-nStartPos );
/*N*/               if ( bCheckLanguage )
/*?*/               {DBG_ASSERT(0, "STRIP");} //STRIP001    pNode->GetWrongList()->MarkInvalid( nStartPos, nEndPos );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

//STRIP001 void ImpEditEngine::RemoveCharAttribs( EditSelection aSel, BOOL bRemoveParaAttribs, USHORT nWhich )
//STRIP001 {
//STRIP001  aSel.Adjust( aEditDoc );
//STRIP001
//STRIP001  USHORT nStartNode = aEditDoc.GetPos( aSel.Min().GetNode() );
//STRIP001  USHORT nEndNode = aEditDoc.GetPos( aSel.Max().GetNode() );
//STRIP001
//STRIP001  const SfxItemSet* pEmptyItemSet = bRemoveParaAttribs ? &GetEmptyItemSet() : 0;
//STRIP001
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  if ( IsUndoEnabled() && !IsInUndo() && aStatus.DoUndoAttribs() )
//STRIP001  {
//STRIP001      // Eventuel spezielles Undo, oder ItemSet*
//STRIP001      EditUndoSetAttribs* pUndo = CreateAttribUndo( aSel, GetEmptyItemSet() );
//STRIP001      pUndo->SetRemoveAttribs( TRUE );
//STRIP001      pUndo->SetRemoveParaAttribs( bRemoveParaAttribs );
//STRIP001      pUndo->SetRemoveWhich( nWhich );
//STRIP001      InsertUndo( pUndo );
//STRIP001  }
//STRIP001 #endif
//STRIP001
//STRIP001  // ueber die Absaetze iterieren...
//STRIP001  for ( USHORT nNode = nStartNode; nNode <= nEndNode; nNode++ )
//STRIP001  {
//STRIP001      ContentNode* pNode = aEditDoc.GetObject( nNode );
//STRIP001      ParaPortion* pPortion = GetParaPortions().GetObject( nNode );
//STRIP001
//STRIP001      DBG_ASSERT( aEditDoc.SaveGetObject( nNode ), "Node nicht gefunden: SetAttribs" );
//STRIP001      DBG_ASSERT( GetParaPortions().SaveGetObject( nNode ), "Portion nicht gefunden: SetAttribs" );
//STRIP001
//STRIP001      xub_StrLen nStartPos = 0;
//STRIP001      xub_StrLen nEndPos = pNode->Len();
//STRIP001      if ( nNode == nStartNode )
//STRIP001          nStartPos = aSel.Min().GetIndex();
//STRIP001      if ( nNode == nEndNode ) // kann auch == nStart sein!
//STRIP001          nEndPos = aSel.Max().GetIndex();
//STRIP001
//STRIP001      // Optimieren: Wenn ganzer Absatz, dann RemoveCharAttribs( nPara )?!
//STRIP001      BOOL bChanged = aEditDoc.RemoveAttribs( pNode, nStartPos, nEndPos, nWhich );
//STRIP001      if ( bRemoveParaAttribs )
//STRIP001         {
//STRIP001          SetParaAttribs( nNode, *pEmptyItemSet );    // Invalidiert
//STRIP001         }
//STRIP001      else
//STRIP001      {
//STRIP001          // Bei 'Format-Standard' sollen auch die Zeichenattribute verschwinden,
//STRIP001          // die von der DrawingEngine als Absatzattribute eingestellt wurden.
//STRIP001          // Diese koennen sowieso nicht vom Anwender eingestellt worden sein.
//STRIP001
//STRIP001             // #106871# Not when nWhich
//STRIP001             // Would have been better to offer a separate method for format/standard...
//STRIP001             if ( !nWhich )
//STRIP001             {
//STRIP001              SfxItemSet aAttribs( GetParaAttribs( nNode ) );
//STRIP001              for ( USHORT nW = EE_CHAR_START; nW <= EE_CHAR_END; nW++ )
//STRIP001                  aAttribs.ClearItem( nW );
//STRIP001              SetParaAttribs( nNode, aAttribs );
//STRIP001             }
//STRIP001      }
//STRIP001
//STRIP001      if ( bChanged && !bRemoveParaAttribs )
//STRIP001      {
//STRIP001          bFormatted = FALSE;
//STRIP001          pPortion->MarkSelectionInvalid( nStartPos, nEndPos-nStartPos );
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*N*/ typedef EditCharAttrib* EditCharAttribPtr;

/*N*/ void ImpEditEngine::RemoveCharAttribs( USHORT nPara, USHORT nWhich, BOOL bRemoveFeatures )
/*N*/ {
/*N*/   ContentNode* pNode = aEditDoc.SaveGetObject( nPara );
/*N*/   ParaPortion* pPortion = GetParaPortions().SaveGetObject( nPara );
/*N*/
/*N*/   DBG_ASSERT( pNode, "Node nicht gefunden: RemoveCharAttribs" );
/*N*/   DBG_ASSERT( pPortion, "Portion nicht gefunden: RemoveCharAttribs" );
/*N*/
/*N*/   if ( !pNode )
/*N*/       return;
/*N*/
/*N*/   USHORT nAttr = 0;
/*N*/   EditCharAttribPtr pAttr = GetAttrib( pNode->GetCharAttribs().GetAttribs(), nAttr );
/*N*/   while ( pAttr )
/*N*/   {
/*N*/       if ( ( !pAttr->IsFeature() || bRemoveFeatures ) &&
/*N*/            ( !nWhich || ( pAttr->GetItem()->Which() == nWhich ) ) )
/*N*/       {
/*?*/           pNode->GetCharAttribs().GetAttribs().Remove( nAttr );
/*?*/           delete pAttr;
/*?*/           nAttr--;
/*N*/       }
/*N*/       nAttr++;
/*N*/       pAttr = GetAttrib( pNode->GetCharAttribs().GetAttribs(), nAttr );
/*N*/   }
/*N*/
/*N*/   pPortion->MarkSelectionInvalid( 0, pNode->Len() );
/*N*/ }

/*N*/ void ImpEditEngine::SetParaAttribs( USHORT nPara, const SfxItemSet& rSet )
/*N*/ {
/*N*/   ContentNode* pNode = aEditDoc.SaveGetObject( nPara );
/*N*/
/*N*/   if ( !pNode )
/*N*/       return;
/*N*/
/*N*/ #ifdef EDITDEBUG
/*N*/ //        FILE* fp = fopen( "d:\\debug.log", "a" );
/*N*/ //        if ( fp )
/*N*/ //        {
/*N*/ //            fprintf( fp, "\n\n=> Absatz-Attribute: Absatz %i\n", nPara );
/*N*/ //            DbgOutItemSet( fp, rSet, TRUE, FALSE );
/*N*/ //            fclose( fp );
/*N*/ //        }
/*N*/ #endif
/*N*/
/*N*/   if ( !( pNode->GetContentAttribs().GetItems() == rSet ) )
/*N*/   {
/*N*/ #ifndef SVX_LIGHT
/*N*/       if ( IsUndoEnabled() && !IsInUndo() && aStatus.DoUndoAttribs() )
/*N*/       {
/*N*/           if ( rSet.GetPool() != &aEditDoc.GetItemPool() )
/*N*/           {
/*?*/               SfxItemSet aTmpSet( GetEmptyItemSet() );
/*?*/               aTmpSet.Put( rSet );
/*?*/               InsertUndo( new EditUndoSetParaAttribs( this, nPara, pNode->GetContentAttribs().GetItems(), aTmpSet ) );
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               InsertUndo( new EditUndoSetParaAttribs( this, nPara, pNode->GetContentAttribs().GetItems(), rSet ) );
/*N*/           }
/*N*/       }
/*N*/ #endif
/*N*/       pNode->GetContentAttribs().GetItems().Set( rSet );
/*N*/       if ( aStatus.UseCharAttribs() )
/*N*/           pNode->CreateDefFont();
/*N*/
/*N*/       ParaAttribsChanged( pNode );
/*N*/   }
/*N*/ }

/*N*/ const SfxItemSet& ImpEditEngine::GetParaAttribs( USHORT nPara ) const
/*N*/ {
/*N*/   ContentNode* pNode = aEditDoc.GetObject( nPara );
/*N*/   DBG_ASSERT( pNode, "Node nicht gefunden: GetParaAttribs" );
/*N*/   return pNode->GetContentAttribs().GetItems();
/*N*/ }

/*N*/ BOOL ImpEditEngine::HasParaAttrib( USHORT nPara, USHORT nWhich ) const
/*N*/ {
/*N*/   ContentNode* pNode = aEditDoc.GetObject( nPara );
/*N*/   DBG_ASSERT( pNode, "Node nicht gefunden: HasParaAttrib" );
/*N*/
/*N*/   return pNode->GetContentAttribs().HasItem( nWhich );
/*N*/ }

/*N*/ const SfxPoolItem& ImpEditEngine::GetParaAttrib( USHORT nPara, USHORT nWhich ) const
/*N*/ {
/*N*/   ContentNode* pNode = aEditDoc.GetObject( nPara );
/*N*/   DBG_ASSERT( pNode, "Node nicht gefunden: GetParaAttrib" );
/*N*/
/*N*/     return pNode->GetContentAttribs().GetItem( nWhich );
/*N*/ }

//STRIP001 void ImpEditEngine::GetCharAttribs( USHORT nPara, EECharAttribArray& rLst ) const
//STRIP001 {
//STRIP001  rLst.Remove( 0, rLst.Count() );
//STRIP001  ContentNode* pNode = aEditDoc.GetObject( nPara );
//STRIP001  if ( pNode )
//STRIP001  {
//STRIP001      for ( USHORT nAttr = 0; nAttr < pNode->GetCharAttribs().Count(); nAttr++ )
//STRIP001      {
//STRIP001          EditCharAttribPtr pAttr = pNode->GetCharAttribs().GetAttribs()[ nAttr ];
//STRIP001          EECharAttrib aEEAttr;
//STRIP001          aEEAttr.pAttr = pAttr->GetItem();
//STRIP001          aEEAttr.nPara = nPara;
//STRIP001          aEEAttr.nStart = pAttr->GetStart();
//STRIP001          aEEAttr.nEnd = pAttr->GetEnd();
//STRIP001          rLst.Insert( aEEAttr, rLst.Count() );
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void ImpEditEngine::ParaAttribsToCharAttribs( ContentNode* pNode )
//STRIP001 {
//STRIP001  pNode->GetCharAttribs().DeleteEmptyAttribs( GetEditDoc().GetItemPool() );
//STRIP001  xub_StrLen nEndPos = pNode->Len();
//STRIP001  for ( USHORT nWhich = EE_CHAR_START; nWhich <= EE_CHAR_END; nWhich++ )
//STRIP001  {
//STRIP001      if ( pNode->GetContentAttribs().HasItem( nWhich ) )
//STRIP001      {
//STRIP001          const SfxPoolItem& rItem = pNode->GetContentAttribs().GetItem( nWhich );
//STRIP001          // Die Luecken auffuellen:
//STRIP001          USHORT nLastEnd = 0;
//STRIP001          EditCharAttrib* pAttr = pNode->GetCharAttribs().FindNextAttrib( nWhich, nLastEnd );
//STRIP001          while ( pAttr )
//STRIP001          {
//STRIP001              if ( pAttr->GetStart() > nLastEnd )
//STRIP001                  aEditDoc.InsertAttrib( pNode, nLastEnd, pAttr->GetStart(), rItem );
//STRIP001              nLastEnd = pAttr->GetEnd();
//STRIP001              pAttr = pNode->GetCharAttribs().FindNextAttrib( nWhich, nLastEnd );
//STRIP001          }
//STRIP001
//STRIP001          // Und den Rest:
//STRIP001          if ( nLastEnd < nEndPos )
//STRIP001              aEditDoc.InsertAttrib( pNode, nLastEnd, nEndPos, rItem );
//STRIP001      }
//STRIP001  }
//STRIP001  bFormatted = FALSE;
//STRIP001  // Portion braucht hier nicht invalidiert werden, geschieht woanders.
//STRIP001 }

/*N*/ IdleFormattter::IdleFormattter()
/*N*/ {
/*N*/   pView = 0;
/*N*/   nRestarts = 0;
/*N*/ }

/*N*/ IdleFormattter::~IdleFormattter()
/*N*/ {
/*N*/   pView = 0;
/*N*/ }

/*N*/ void IdleFormattter::DoIdleFormat( EditView* pV )
/*N*/ {
/*N*/   pView = pV;
/*N*/
/*N*/   if ( IsActive() )
/*N*/       nRestarts++;
/*N*/
/*N*/   if ( nRestarts > 4 )
/*?*/       ForceTimeout();
/*N*/   else
/*N*/       Start();
/*N*/ }

/*N*/ void IdleFormattter::ForceTimeout()
/*N*/ {
/*N*/   if ( IsActive() )
/*N*/   {
/*?*/       Stop();
/*?*/       ((Link&)GetTimeoutHdl()).Call( this );
/*N*/   }
/*N*/ }

/*N*/ ImplIMEInfos::ImplIMEInfos( const EditPaM& rPos, const String& rOldTextAfterStartPos )
/*N*/  : aOldTextAfterStartPos( rOldTextAfterStartPos )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  aPos = rPos;
//STRIP001  nLen = 0;
//STRIP001  bCursor = TRUE;
//STRIP001  pAttribs = NULL;
//STRIP001  bWasCursorOverwrite = FALSE;
/*N*/ }

/*N*/ ImplIMEInfos::~ImplIMEInfos()
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  delete[] pAttribs;
/*N*/ }

//STRIP001 void ImplIMEInfos::CopyAttribs( const USHORT* pA, USHORT nL )
//STRIP001 {
//STRIP001  nLen = nL;
//STRIP001  delete pAttribs;
//STRIP001  pAttribs = new USHORT[ nL ];
//STRIP001  memcpy( pAttribs, pA, nL*sizeof(USHORT) );
//STRIP001 }

//STRIP001 void ImplIMEInfos::DestroyAttribs()
//STRIP001 {
//STRIP001  delete[] pAttribs;
//STRIP001  pAttribs = NULL;
//STRIP001     nLen = 0;
//STRIP001 }
