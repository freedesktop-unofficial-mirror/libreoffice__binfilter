/*************************************************************************
 *
 *  $RCSfile: svx_impedit2.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:43:10 $
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

#include <lspcitem.hxx>
#include <flditem.hxx>
#include <impedit.hxx>
#include <editeng.hxx>
#include <editview.hxx>
#include <editdbg.hxx>
#include <eerdll2.hxx>
#include <eerdll.hxx>
#include <edtspell.hxx>
#include <eeobj.hxx>
#include <txtrange.hxx>
#include <svtools/urlbmk.hxx>
#include <svtools/colorcfg.hxx>
#include <svtools/ctloptions.hxx>

#include <fhgtitem.hxx>
#include <lrspitem.hxx>
#include <ulspitem.hxx>
#include <wghtitem.hxx>
#include <postitem.hxx>
#include <udlnitem.hxx>
#include <adjitem.hxx>
#include <scripttypeitem.hxx>
#include <frmdiritem.hxx>
#include <fontitem.hxx>

#ifndef _SFXVIEWFRM_HXX //autogen
#include <bf_sfx2/viewfrm.hxx>
#endif

#ifndef _SFX_FCONTNR_HXX //autogen
#include <bf_sfx2/fcontnr.hxx>
#endif

#ifndef _SFXDISPATCH_HXX //autogen
#include <bf_sfx2/dispatch.hxx>
#endif

#ifndef _VCL_CMDEVT_H
#include <vcl/cmdevt.h>
#endif

#ifndef SVX_LIGHT
#ifndef _SFXFRAME_HXX //autogen
#include <bf_sfx2/frame.hxx>
#endif
#endif

#ifndef _COM_SUN_STAR_I18N_CHARACTERITERATORMODE_HPP_
#include <com/sun/star/i18n/CharacterIteratorMode.hpp>
#endif

#ifndef _COM_SUN_STAR_I18N_WORDTYPE_HPP_
#include <com/sun/star/i18n/WordType.hpp>
#endif

#ifndef _COM_SUN_STAR_I18N_SCRIPTTYPE_HPP_
#include <com/sun/star/i18n/ScriptType.hpp>
#endif

#ifndef _COM_SUN_STAR_TEXT_CHARACTERCOMPRESSIONTYPE_HPP_
#include <com/sun/star/text/CharacterCompressionType.hpp>
#endif

#include <comphelper/processfactory.hxx>

#include <sot/formats.hxx>

#include <unicode/ubidi.h>
namespace binfilter {

#if defined(MACOSX) && ( __GNUC__ < 3 )
// moved from editundo.hxx
const EPaM& EditUndoRemoveChars::GetEPaM() { return aEPaM; }
String& EditUndoRemoveChars::GetStr() { return aText; }
#endif

using namespace ::com::sun::star;

/*N*/ USHORT lcl_CalcExtraSpace( ParaPortion* pPortion, const SvxLineSpacingItem& rLSItem )
/*N*/ {
/*N*/   USHORT nExtra = 0;
    /* if ( ( rLSItem.GetInterLineSpaceRule() == SVX_INTER_LINE_SPACE_PROP )
            && ( rLSItem.GetPropLineSpace() != 100 ) )
    {
        // ULONG nH = pPortion->GetNode()->GetCharAttribs().GetDefFont().GetSize().Height();
        ULONG nH = pPortion->GetLines().GetObject( 0 )->GetHeight();
        long n = nH * rLSItem.GetPropLineSpace();
        n /= 100;
        n -= nH;    // nur den Abstand
        if ( n > 0 )
            nExtra = (USHORT)n;
    }
    else */
/*N*/   if ( rLSItem.GetInterLineSpaceRule() == SVX_INTER_LINE_SPACE_FIX )
/*N*/   {
/*?*/       nExtra = rLSItem.GetInterLineSpace();
/*N*/   }
/*N*/
/*N*/   return nExtra;
/*N*/ }

// ----------------------------------------------------------------------
//  class ImpEditEngine
//  ----------------------------------------------------------------------

/*N*/ ImpEditEngine::ImpEditEngine( EditEngine* pEE, SfxItemPool* pItemPool ) :
/*N*/   aEditDoc( pItemPool ),
/*N*/   aPaperSize( 0x7FFFFFFF, 0x7FFFFFFF ),
/*N*/   aMaxAutoPaperSize( 0x7FFFFFFF, 0x7FFFFFFF ),
/*N*/   aMinAutoPaperSize( 0x0, 0x0 ),
/*N*/   aGroupChars( RTL_CONSTASCII_USTRINGPARAM( "{}()[]" ) ),
/*N*/   aWordDelimiters( RTL_CONSTASCII_USTRINGPARAM( "  .,;:-'`'?!_=\"{}()[]\0xFF" ) )
/*N*/ {
/*N*/   pEditEngine         = pEE;
/*N*/   pRefDev             = NULL;
/*N*/   pVirtDev            = NULL;
/*N*/   pEmptyItemSet       = NULL;
/*N*/   pActiveView         = NULL;
//STRIP001  pSpellInfo          = NULL;
/*N*/   pTextObjectPool     = NULL;
/*N*/   mpIMEInfos          = NULL;
/*N*/   pStylePool          = NULL;
/*N*/   pUndoManager        = NULL;
/*N*/   pUndoMarkSelection  = NULL;
/*N*/   pTextRanger         = NULL;
/*N*/     pColorConfig        = NULL;
/*N*/     pCTLOptions         = NULL;
/*N*/
/*N*/   nCurTextHeight      = 0;
/*N*/     nBlockNotifications = 0;
/*N*/   nBigTextObjectStart = 20;
/*N*/
/*N*/   nStretchX           = 100;
/*N*/   nStretchY           = 100;
/*N*/
/*N*/   bInSelection        = FALSE;
/*N*/   bOwnerOfRefDev      = FALSE;
/*N*/   bDowning            = FALSE;
/*N*/   bIsInUndo           = FALSE;
/*N*/   bIsFormatting       = FALSE;
/*N*/   bFormatted          = FALSE;
/*N*/   bUpdate             = TRUE;
/*N*/     bUseAutoColor       = TRUE;
/*N*/     bForceAutoColor     = FALSE;
/*N*/ #ifndef SVX_LIGHT
/*N*/   bUndoEnabled        = TRUE;
/*N*/ #else
/*N*/   bUndoEnabled        = FALSE;
/*N*/ #endif
/*N*/   bCallParaInsertedOrDeleted = FALSE;
/*N*/
/*N*/   eDefLanguage        = LANGUAGE_DONTKNOW;
/*N*/   maBackgroundColor   = COL_AUTO;
/*N*/
/*N*/     nAsianCompressionMode = text::CharacterCompressionType::NONE;
/*N*/   bKernAsianPunctuation = FALSE;
/*N*/
/*N*/     eDefaultHorizontalTextDirection = EE_HTEXTDIR_DEFAULT;
/*N*/
/*N*/
/*N*/   aStatus.GetControlWord() =  EE_CNTRL_USECHARATTRIBS | EE_CNTRL_DOIDLEFORMAT |
/*N*/                               EE_CNTRL_PASTESPECIAL | EE_CNTRL_UNDOATTRIBS |
/*N*/                               EE_CNTRL_ALLOWBIGOBJS | EE_CNTRL_RTFSTYLESHEETS |
/*N*/                               EE_CNTRL_FORMAT100;
/*N*/
/*N*/   aSelEngine.SetFunctionSet( &aSelFuncSet );
/*N*/
/*N*/   aStatusTimer.SetTimeout( 200 );
/*N*/   aStatusTimer.SetTimeoutHdl( LINK( this, ImpEditEngine, StatusTimerHdl ) );
/*N*/
/*N*/   aIdleFormatter.SetTimeout( 5 );
/*N*/   aIdleFormatter.SetTimeoutHdl( LINK( this, ImpEditEngine, IdleFormatHdl ) );
/*N*/
/*N*/   aOnlineSpellTimer.SetTimeout( 100 );
/*N*/   aOnlineSpellTimer.SetTimeoutHdl( LINK( this, ImpEditEngine, OnlineSpellHdl ) );
/*N*/
/*N*/   pRefDev             = EE_DLL()->GetGlobalData()->GetStdRefDevice();
/*N*/
/*N*/   // Ab hier wird schon auf Daten zugegriffen!
/*N*/   SetRefDevice( pRefDev );
/*N*/   InitDoc( FALSE );
/*N*/
/*N*/   bCallParaInsertedOrDeleted = TRUE;
/*N*/
/*N*/     aEditDoc.SetModifyHdl( LINK( this, ImpEditEngine, DocModified ) );
/*N*/ }

/*N*/ ImpEditEngine::~ImpEditEngine()
/*N*/ {
/*N*/   aStatusTimer.Stop();
/*N*/   aOnlineSpellTimer.Stop();
/*N*/   aIdleFormatter.Stop();
/*N*/
/*N*/   // das Zerstoeren von Vorlagen kann sonst unnoetiges Formatieren ausloesen,
/*N*/   // wenn eine Parent-Vorlage zerstoert wird.
/*N*/   // Und das nach dem Zerstoeren der Daten!
/*N*/   bDowning = TRUE;
/*N*/   SetUpdateMode( FALSE );
/*N*/
/*N*/   delete pVirtDev;
/*N*/   delete pEmptyItemSet;
/*N*/   delete pUndoManager;
/*N*/   delete pTextRanger;
/*N*/   delete mpIMEInfos;
/*N*/     delete pColorConfig;
/*N*/     delete pCTLOptions;
/*N*/   if ( bOwnerOfRefDev )
/*N*/       delete pRefDev;
/*N*/ }

/*N*/ void ImpEditEngine::SetRefDevice( OutputDevice* pRef )
/*N*/ {
/*N*/   if ( bOwnerOfRefDev )
/*N*/       delete pRefDev;
/*N*/
/*N*/   pRefDev = pRef;
/*N*/   bOwnerOfRefDev = FALSE;
/*N*/
/*N*/   if ( !pRef )
/*N*/       pRefDev = EE_DLL()->GetGlobalData()->GetStdRefDevice();
/*N*/
/*N*/   nOnePixelInRef = (USHORT)pRefDev->PixelToLogic( Size( 1, 0 ) ).Width();
/*N*/
/*N*/   if ( IsFormatted() )
/*N*/   {
/*N*/       FormatFullDoc();
/*N*/       UpdateViews( (EditView*) 0);
/*N*/   }
/*N*/ }

/*N*/ void ImpEditEngine::SetRefMapMode( const MapMode& rMapMode )
/*N*/ {
/*N*/   if ( GetRefDevice()->GetMapMode() == rMapMode )
/*N*/       return;
/*N*/
/*N*/   // Wenn RefDev == GlobalRefDev => eigenes anlegen!
/*N*/   if ( !bOwnerOfRefDev && ( pRefDev == EE_DLL()->GetGlobalData()->GetStdRefDevice() ) )
/*N*/   {
/*N*/       pRefDev = new VirtualDevice;
/*N*/       pRefDev->SetMapMode( MAP_TWIP );
/*N*/       SetRefDevice( pRefDev );
/*N*/       bOwnerOfRefDev = TRUE;
/*N*/   }
/*N*/   pRefDev->SetMapMode( rMapMode );
/*N*/   nOnePixelInRef = (USHORT)pRefDev->PixelToLogic( Size( 1, 0 ) ).Width();
/*N*/   if ( IsFormatted() )
/*N*/   {
/*N*/       FormatFullDoc();
/*N*/       UpdateViews( (EditView*) 0);
/*N*/   }
/*N*/ }

/*N*/ void ImpEditEngine::InitDoc( BOOL bKeepParaAttribs )
/*N*/ {
/*N*/   USHORT nParas = aEditDoc.Count();
/*N*/   for ( USHORT n = bKeepParaAttribs ? 1 : 0; n < nParas; n++ )
/*N*/   {
/*N*/       if ( aEditDoc[n]->GetStyleSheet() )
/*N*/           EndListening( *aEditDoc[n]->GetStyleSheet(), FALSE );
/*N*/   }
/*N*/
/*N*/   if ( bKeepParaAttribs )
/*N*/       aEditDoc.RemoveText();
/*N*/   else
/*N*/       aEditDoc.Clear();
/*N*/
/*N*/   GetParaPortions().Reset();
/*N*/
/*N*/   ParaPortion* pIniPortion = new ParaPortion( aEditDoc[0] );
/*N*/   GetParaPortions().Insert( pIniPortion, 0 );
/*N*/
/*N*/   bFormatted = FALSE;
/*N*/
/*N*/   if ( IsCallParaInsertedOrDeleted() )
/*N*/   {
/*N*/       GetEditEnginePtr()->ParagraphDeleted( EE_PARA_ALL );
/*N*/       GetEditEnginePtr()->ParagraphInserted( 0 );
/*N*/   }
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/   if ( GetStatus().DoOnlineSpelling() )
/*?*/       aEditDoc.GetObject( 0 )->CreateWrongList();
/*N*/ #endif // !SVX_LIGHT
/*N*/ }

//STRIP001 EditPaM ImpEditEngine::DeleteSelected( EditSelection aSel )
//STRIP001 {
//STRIP001  EditPaM aPaM ( ImpDeleteSelection( aSel ) );
//STRIP001  return aPaM;
//STRIP001 }

/*N*/ XubString ImpEditEngine::GetSelected( const EditSelection& rSel, const LineEnd eEnd  ) const
/*N*/ {
/*N*/   XubString aText;
/*N*/   if ( !rSel.HasRange() )
/*N*/       return aText;
/*N*/
/*N*/   String aSep = EditDoc::GetSepStr( eEnd );
/*N*/
/*N*/   EditSelection aSel( rSel );
/*N*/   aSel.Adjust( aEditDoc );
/*N*/
/*N*/   ContentNode* pStartNode = aSel.Min().GetNode();
/*N*/   ContentNode* pEndNode = aSel.Max().GetNode();
/*N*/   USHORT nStartNode = aEditDoc.GetPos( pStartNode );
/*N*/   USHORT nEndNode = aEditDoc.GetPos( pEndNode );
/*N*/
/*N*/   DBG_ASSERT( nStartNode <= nEndNode, "Selektion nicht sortiert ?" );
/*N*/
/*N*/   // ueber die Absaetze iterieren...
/*N*/   for ( USHORT nNode = nStartNode; nNode <= nEndNode; nNode++ )
/*N*/   {
/*N*/       DBG_ASSERT( aEditDoc.SaveGetObject( nNode ), "Node nicht gefunden: GetSelected" );
/*N*/       ContentNode* pNode = aEditDoc.GetObject( nNode );
/*N*/
/*N*/       xub_StrLen nStartPos = 0;
/*N*/       xub_StrLen nEndPos = pNode->Len();
/*N*/       if ( nNode == nStartNode )
/*N*/           nStartPos = aSel.Min().GetIndex();
/*N*/       if ( nNode == nEndNode ) // kann auch == nStart sein!
/*N*/           nEndPos = aSel.Max().GetIndex();
/*N*/
/*N*/       aText += aEditDoc.GetParaAsString( pNode, nStartPos, nEndPos );
/*N*/       if ( nNode < nEndNode )
/*N*/           aText += aSep;
/*N*/   }
/*N*/   return aText;
/*N*/ }

//STRIP001 BOOL ImpEditEngine::MouseButtonDown( const MouseEvent& rMEvt, EditView* pView )
//STRIP001 {
//STRIP001  GetSelEngine().SetCurView( pView );
//STRIP001  SetActiveView( pView );
//STRIP001
//STRIP001  if ( GetAutoCompleteText().Len() )
//STRIP001      SetAutoCompleteText( String(), TRUE );
//STRIP001
//STRIP001  GetSelEngine().SelMouseButtonDown( rMEvt );
//STRIP001  // Sonderbehandlungen
//STRIP001  EditSelection aCurSel( pView->pImpEditView->GetEditSelection() );
//STRIP001  if ( !rMEvt.IsShift() )
//STRIP001  {
//STRIP001      if ( rMEvt.GetClicks() == 2 )
//STRIP001      {
//STRIP001          // damit die SelectionEngine weiss, dass Anker.
//STRIP001          aSelEngine.CursorPosChanging( TRUE, FALSE );
//STRIP001
//STRIP001          EditSelection aNewSelection( SelectWord( aCurSel ) );
//STRIP001          pView->pImpEditView->DrawSelection();
//STRIP001          pView->pImpEditView->SetEditSelection( aNewSelection );
//STRIP001          pView->pImpEditView->DrawSelection();
//STRIP001          pView->ShowCursor( TRUE, TRUE );
//STRIP001      }
//STRIP001      else if ( rMEvt.GetClicks() == 3 )
//STRIP001      {
//STRIP001          // damit die SelectionEngine weiss, dass Anker.
//STRIP001          aSelEngine.CursorPosChanging( TRUE, FALSE );
//STRIP001
//STRIP001          EditSelection aNewSelection( aCurSel );
//STRIP001          aNewSelection.Min().SetIndex( 0 );
//STRIP001          aNewSelection.Max().SetIndex( aCurSel.Min().GetNode()->Len() );
//STRIP001          pView->pImpEditView->DrawSelection();
//STRIP001          pView->pImpEditView->SetEditSelection( aNewSelection );
//STRIP001          pView->pImpEditView->DrawSelection();
//STRIP001          pView->ShowCursor( TRUE, TRUE );
//STRIP001      }
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 void ImpEditEngine::Command( const CommandEvent& rCEvt, EditView* pView )
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  GetSelEngine().SetCurView( pView );
//STRIP001  SetActiveView( pView );
//STRIP001     if ( rCEvt.GetCommand() == COMMAND_VOICE )
//STRIP001  {
//STRIP001      const CommandVoiceData* pData = rCEvt.GetVoiceData();
//STRIP001      if ( pData->GetType() == VOICECOMMANDTYPE_DICTATION )
//STRIP001      {
//STRIP001          // Funktionen auf KeyEvents umbiegen, wenn keine entsprechende
//STRIP001          // Methode an EditView/EditEngine, damit Undo konsistent bleibt.
//STRIP001
//STRIP001          SfxPoolItem* pNewAttr = NULL;
//STRIP001
//STRIP001          switch ( pData->GetCommand() )
//STRIP001          {
//STRIP001              case DICTATIONCOMMAND_UNKNOWN:
//STRIP001              {
//STRIP001                  pView->InsertText( pData->GetText() );
//STRIP001              }
//STRIP001              break;
//STRIP001              case DICTATIONCOMMAND_NEWPARAGRAPH:
//STRIP001              {
//STRIP001                  pView->PostKeyEvent( KeyEvent( 0, KeyCode( KEY_RETURN, 0 ) ) );
//STRIP001              }
//STRIP001              break;
//STRIP001              case DICTATIONCOMMAND_NEWLINE:
//STRIP001              {
//STRIP001                  pView->PostKeyEvent( KeyEvent( 0, KeyCode( KEY_RETURN, KEY_SHIFT ) ) );
//STRIP001              }
//STRIP001              break;
//STRIP001              case DICTATIONCOMMAND_TAB:
//STRIP001              {
//STRIP001                  pView->PostKeyEvent( KeyEvent( 0, KeyCode( KEY_TAB, 0 ) ) );
//STRIP001              }
//STRIP001              break;
//STRIP001              case DICTATIONCOMMAND_LEFT:
//STRIP001              {
//STRIP001                  pView->PostKeyEvent( KeyEvent( 0, KeyCode( KEY_LEFT, KEY_MOD1  ) ) );
//STRIP001              }
//STRIP001              break;
//STRIP001              case DICTATIONCOMMAND_RIGHT:
//STRIP001              {
//STRIP001                  pView->PostKeyEvent( KeyEvent( 0, KeyCode( KEY_RIGHT, KEY_MOD1  ) ) );
//STRIP001              }
//STRIP001              break;
//STRIP001              case DICTATIONCOMMAND_UP:
//STRIP001              {
//STRIP001                  pView->PostKeyEvent( KeyEvent( 0, KeyCode( KEY_UP, 0 ) ) );
//STRIP001              }
//STRIP001              break;
//STRIP001              case DICTATIONCOMMAND_DOWN:
//STRIP001              {
//STRIP001                  pView->PostKeyEvent( KeyEvent( 0, KeyCode( KEY_UP, 0 ) ) );
//STRIP001              }
//STRIP001              break;
//STRIP001              case DICTATIONCOMMAND_UNDO:
//STRIP001              {
//STRIP001                  pView->Undo();
//STRIP001              }
//STRIP001              break;
//STRIP001              case DICTATIONCOMMAND_DEL:
//STRIP001              {
//STRIP001                  pView->PostKeyEvent( KeyEvent( 0, KeyCode( KEY_LEFT, KEY_MOD1|KEY_SHIFT  ) ) );
//STRIP001                  pView->DeleteSelected();
//STRIP001              }
//STRIP001              break;
//STRIP001              case DICTATIONCOMMAND_BOLD_ON:
//STRIP001              {
//STRIP001                  pNewAttr = new SvxWeightItem( WEIGHT_BOLD, EE_CHAR_WEIGHT );
//STRIP001              }
//STRIP001              break;
//STRIP001              case DICTATIONCOMMAND_BOLD_OFF:
//STRIP001              {
//STRIP001                  pNewAttr = new SvxWeightItem( WEIGHT_NORMAL, EE_CHAR_WEIGHT );
//STRIP001              }
//STRIP001              break;
//STRIP001              case DICTATIONCOMMAND_ITALIC_ON:
//STRIP001              {
//STRIP001                  pNewAttr = new SvxPostureItem( ITALIC_NORMAL, EE_CHAR_ITALIC );
//STRIP001              }
//STRIP001              break;
//STRIP001              case DICTATIONCOMMAND_ITALIC_OFF:
//STRIP001              {
//STRIP001                  pNewAttr = new SvxPostureItem( ITALIC_NORMAL, EE_CHAR_ITALIC );
//STRIP001              }
//STRIP001              break;
//STRIP001              case DICTATIONCOMMAND_UNDERLINE_ON:
//STRIP001              {
//STRIP001                  pNewAttr = new SvxUnderlineItem( UNDERLINE_SINGLE, EE_CHAR_UNDERLINE );
//STRIP001              }
//STRIP001              break;
//STRIP001              case DICTATIONCOMMAND_UNDERLINE_OFF:
//STRIP001              {
//STRIP001                  pNewAttr = new SvxUnderlineItem( UNDERLINE_NONE, EE_CHAR_UNDERLINE );
//STRIP001              }
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001          if ( pNewAttr )
//STRIP001          {
//STRIP001              SfxItemSet aSet( GetEmptyItemSet() );
//STRIP001              aSet.Put( *pNewAttr );
//STRIP001              pView->SetAttribs( aSet );
//STRIP001              delete pNewAttr;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else if ( rCEvt.GetCommand() == COMMAND_STARTEXTTEXTINPUT )
//STRIP001  {
//STRIP001      pView->DeleteSelected();
//STRIP001      delete mpIMEInfos;
//STRIP001         EditPaM aPaM = pView->GetImpEditView()->GetEditSelection().Max();
//STRIP001         String aOldTextAfterStartPos = aPaM.GetNode()->Copy( aPaM.GetIndex() );
//STRIP001         USHORT nMax = aOldTextAfterStartPos.Search( CH_FEATURE );
//STRIP001         if ( nMax != STRING_NOTFOUND )  // don't overwrite features!
//STRIP001             aOldTextAfterStartPos.Erase( nMax );
//STRIP001      mpIMEInfos = new ImplIMEInfos( aPaM, aOldTextAfterStartPos );
//STRIP001      mpIMEInfos->bWasCursorOverwrite = !pView->IsInsertMode();
//STRIP001         UndoActionStart( EDITUNDO_INSERT );
//STRIP001  }
//STRIP001  else if ( rCEvt.GetCommand() == COMMAND_ENDEXTTEXTINPUT )
//STRIP001  {
//STRIP001      DBG_ASSERT( mpIMEInfos, "COMMAND_ENDEXTTEXTINPUT => Kein Start ?" );
//STRIP001      if( mpIMEInfos )
//STRIP001      {
//STRIP001          // #102812# convert quotes in IME text
//STRIP001          // works on the last input character, this is escpecially in Korean text often done
//STRIP001          // quotes that are inside of the string are not replaced!
//STRIP001          // Borrowed from sw: edtwin.cxx
//STRIP001          if ( mpIMEInfos->nLen )
//STRIP001          {
//STRIP001              EditSelection aSel( mpIMEInfos->aPos );
//STRIP001              aSel.Min().GetIndex() += mpIMEInfos->nLen-1;
//STRIP001              aSel.Max().GetIndex() += mpIMEInfos->nLen;
//STRIP001              // #102812# convert quotes in IME text
//STRIP001              // works on the last input character, this is escpecially in Korean text often done
//STRIP001              // quotes that are inside of the string are not replaced!
//STRIP001              const sal_Unicode nCharCode = aSel.Min().GetNode()->GetChar( aSel.Min().GetIndex() );
//STRIP001              if ( ( GetStatus().DoAutoCorrect() ) && ( ( nCharCode == '\"' ) || ( nCharCode == '\'' ) ) )
//STRIP001              {
//STRIP001                  aSel = DeleteSelected( aSel );
//STRIP001                  aSel = AutoCorrect( aSel, nCharCode, mpIMEInfos->bWasCursorOverwrite );
//STRIP001                  pView->pImpEditView->SetEditSelection( aSel );
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          ParaPortion* pPortion = FindParaPortion( mpIMEInfos->aPos.GetNode() );
//STRIP001          pPortion->MarkSelectionInvalid( mpIMEInfos->aPos.GetIndex(), 0 );
//STRIP001
//STRIP001          BOOL bWasCursorOverwrite = mpIMEInfos->bWasCursorOverwrite;
//STRIP001
//STRIP001          delete mpIMEInfos;
//STRIP001          mpIMEInfos = NULL;
//STRIP001
//STRIP001          FormatAndUpdate( pView );
//STRIP001
//STRIP001          pView->SetInsertMode( !bWasCursorOverwrite );
//STRIP001      }
//STRIP001         UndoActionEnd( EDITUNDO_INSERT );
//STRIP001  }
//STRIP001  else if ( rCEvt.GetCommand() == COMMAND_EXTTEXTINPUT )
//STRIP001  {
//STRIP001      DBG_ASSERT( mpIMEInfos, "COMMAND_EXTTEXTINPUT => Kein Start ?" );
//STRIP001      if( mpIMEInfos )
//STRIP001      {
//STRIP001          const CommandExtTextInputData* pData = rCEvt.GetExtTextInputData();
//STRIP001
//STRIP001          if ( !pData->IsOnlyCursorChanged() )
//STRIP001          {
//STRIP001              EditSelection aSel( mpIMEInfos->aPos );
//STRIP001              aSel.Max().GetIndex() += mpIMEInfos->nLen;
//STRIP001              aSel = DeleteSelected( aSel );
//STRIP001              aSel = ImpInsertText( aSel, pData->GetText() );
//STRIP001
//STRIP001                 if ( mpIMEInfos->bWasCursorOverwrite )
//STRIP001                 {
//STRIP001                     USHORT nOldIMETextLen = mpIMEInfos->nLen;
//STRIP001                     USHORT nNewIMETextLen = pData->GetText().Len();
//STRIP001
//STRIP001                     if ( ( nOldIMETextLen > nNewIMETextLen ) &&
//STRIP001                          ( nNewIMETextLen < mpIMEInfos->aOldTextAfterStartPos.Len() ) )
//STRIP001                     {
//STRIP001                         // restore old characters
//STRIP001                         USHORT nRestore = nOldIMETextLen - nNewIMETextLen;
//STRIP001                         EditPaM aPaM( mpIMEInfos->aPos );
//STRIP001                         aPaM.GetIndex() += nNewIMETextLen;
//STRIP001                         ImpInsertText( aPaM, mpIMEInfos->aOldTextAfterStartPos.Copy( nNewIMETextLen, nRestore ) );
//STRIP001                     }
//STRIP001                     else if ( ( nOldIMETextLen < nNewIMETextLen ) &&
//STRIP001                               ( nOldIMETextLen < mpIMEInfos->aOldTextAfterStartPos.Len() ) )
//STRIP001                     {
//STRIP001                         // overwrite
//STRIP001                         USHORT nOverwrite = nNewIMETextLen - nOldIMETextLen;
//STRIP001                         if ( ( nOldIMETextLen + nOverwrite ) > mpIMEInfos->aOldTextAfterStartPos.Len() )
//STRIP001                             nOverwrite = mpIMEInfos->aOldTextAfterStartPos.Len() - nOldIMETextLen;
//STRIP001                         DBG_ASSERT( nOverwrite && (nOverwrite < 0xFF00), "IME Overwrite?!" );
//STRIP001                         EditPaM aPaM( mpIMEInfos->aPos );
//STRIP001                         aPaM.GetIndex() += nNewIMETextLen;
//STRIP001                         EditSelection aSel( aPaM );
//STRIP001                         aSel.Max().GetIndex() += nOverwrite;
//STRIP001                         DeleteSelected( aSel );
//STRIP001                     }
//STRIP001                 }
//STRIP001              if ( pData->GetTextAttr() )
//STRIP001              {
//STRIP001                  mpIMEInfos->CopyAttribs( pData->GetTextAttr(), pData->GetText().Len() );
//STRIP001                  mpIMEInfos->bCursor = pData->IsCursorVisible();
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  mpIMEInfos->DestroyAttribs();
//STRIP001                  mpIMEInfos->nLen = pData->GetText().Len();
//STRIP001              }
//STRIP001
//STRIP001              ParaPortion* pPortion = FindParaPortion( mpIMEInfos->aPos.GetNode() );
//STRIP001              pPortion->MarkSelectionInvalid( mpIMEInfos->aPos.GetIndex(), 0 );
//STRIP001              FormatAndUpdate( pView );
//STRIP001          }
//STRIP001
//STRIP001          EditSelection aNewSel = EditPaM( mpIMEInfos->aPos.GetNode(), mpIMEInfos->aPos.GetIndex()+pData->GetCursorPos() );
//STRIP001          pView->SetSelection( CreateESel( aNewSel ) );
//STRIP001          pView->SetInsertMode( !pData->IsCursorOverwrite() );
//STRIP001
//STRIP001          if ( pData->IsCursorVisible() )
//STRIP001              pView->ShowCursor();
//STRIP001          else
//STRIP001              pView->HideCursor();
//STRIP001      }
//STRIP001  }
//STRIP001  else if ( rCEvt.GetCommand() == COMMAND_INPUTCONTEXTCHANGE )
//STRIP001  {
//STRIP001  }
//STRIP001  else if ( rCEvt.GetCommand() == COMMAND_CURSORPOS )
//STRIP001  {
//STRIP001      if ( mpIMEInfos && mpIMEInfos->nLen )
//STRIP001      {
//STRIP001          EditPaM aPaM( pView->pImpEditView->GetEditSelection().Max() );
//STRIP001          Rectangle aR1 = PaMtoEditCursor( aPaM, 0 );
//STRIP001
//STRIP001          USHORT nInputEnd = mpIMEInfos->aPos.GetIndex() + mpIMEInfos->nLen;
//STRIP001
//STRIP001          if ( !IsFormatted() )
//STRIP001              FormatDoc();
//STRIP001
//STRIP001          ParaPortion* pParaPortion = GetParaPortions().SaveGetObject( GetEditDoc().GetPos( aPaM.GetNode() ) );
//STRIP001          USHORT nLine = pParaPortion->GetLines().FindLine( aPaM.GetIndex(), sal_True );
//STRIP001          EditLine* pLine = pParaPortion->GetLines().GetObject( nLine );
//STRIP001          if ( pLine && ( nInputEnd > pLine->GetEnd() ) )
//STRIP001              nInputEnd = pLine->GetEnd();
//STRIP001          Rectangle aR2 = PaMtoEditCursor( EditPaM( aPaM.GetNode(), nInputEnd ), GETCRSR_ENDOFLINE );
//STRIP001          Rectangle aRect = pView->GetImpEditView()->GetWindowPos( aR1 );
//STRIP001          pView->GetWindow()->SetCursorRect( &aRect, aR2.Left()-aR1.Right() );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pView->GetWindow()->SetCursorRect();
//STRIP001      }
//STRIP001  }
//STRIP001 #endif // !SVX_LIGHT
//STRIP001
//STRIP001  GetSelEngine().Command( rCEvt );
//STRIP001 }

//STRIP001 BOOL ImpEditEngine::MouseButtonUp( const MouseEvent& rMEvt, EditView* pView )
//STRIP001 {
//STRIP001  GetSelEngine().SetCurView( pView );
//STRIP001  GetSelEngine().SelMouseButtonUp( rMEvt );
//STRIP001  bInSelection = FALSE;
//STRIP001  // Sonderbehandlungen
//STRIP001  EditSelection aCurSel( pView->pImpEditView->GetEditSelection() );
//STRIP001  if ( !aCurSel.HasRange() )
//STRIP001  {
//STRIP001      if ( ( rMEvt.GetClicks() == 1 ) && rMEvt.IsLeft() && !rMEvt.IsMod2() )
//STRIP001      {
//STRIP001          const SvxFieldItem* pFld = pView->GetFieldUnderMousePointer();
//STRIP001          if ( pFld )
//STRIP001          {
//STRIP001              EditPaM aPaM( aCurSel.Max() );
//STRIP001              USHORT nPara = GetEditDoc().GetPos( aPaM.GetNode() );
//STRIP001              GetEditEnginePtr()->FieldClicked( *pFld, nPara, aPaM.GetIndex() );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL ImpEditEngine::MouseMove( const MouseEvent& rMEvt, EditView* pView )
//STRIP001 {
//STRIP001  // MouseMove wird sofort nach ShowQuickHelp() gerufen!
//STRIP001 //   if ( GetAutoCompleteText().Len() )
//STRIP001 //       SetAutoCompleteText( String(), TRUE );
//STRIP001  GetSelEngine().SetCurView( pView );
//STRIP001  GetSelEngine().SelMouseMove( rMEvt );
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 EditPaM ImpEditEngine::InsertText( EditSelection aSel, const XubString& rStr )
//STRIP001 {
//STRIP001  EditPaM aPaM = ImpInsertText( aSel, rStr );
//STRIP001  return aPaM;
//STRIP001 }

/*N*/ EditPaM ImpEditEngine::Clear()
/*N*/ {
/*N*/   InitDoc( FALSE );
/*N*/
/*N*/   EditPaM aPaM = aEditDoc.GetStartPaM();
/*N*/   EditSelection aSel( aPaM );
/*N*/
/*N*/   nCurTextHeight = 0;
/*N*/
/*N*/   ResetUndoManager();
/*N*/
/*N*/   for ( USHORT nView = aEditViews.Count(); nView; )
/*N*/   {
/*?*/       EditView* pView = aEditViews[--nView];
/*?*/       DBG_CHKOBJ( pView, EditView, 0 );
/*?*/       pView->pImpEditView->SetEditSelection( aSel );
/*N*/   }
/*N*/
/*N*/   return aPaM;
/*N*/ }

/*N*/ EditPaM ImpEditEngine::RemoveText()
/*N*/ {
/*N*/   InitDoc( TRUE );
/*N*/
/*N*/   EditPaM aStartPaM = aEditDoc.GetStartPaM();
/*N*/   EditSelection aEmptySel( aStartPaM, aStartPaM );
/*N*/   for ( USHORT nView = 0; nView < aEditViews.Count(); nView++ )
/*N*/   {
/*N*/       EditView* pView = aEditViews.GetObject(nView);
/*N*/       DBG_CHKOBJ( pView, EditView, 0 );
/*N*/       pView->pImpEditView->SetEditSelection( aEmptySel );
/*N*/   }
/*N*/   ResetUndoManager();
/*N*/   return aEditDoc.GetStartPaM();
/*N*/ }


/*N*/ void ImpEditEngine::SetText( const XubString& rText )
/*N*/ {
/*N*/   // RemoveText loescht die Undo-Liste!
/*N*/   EditPaM aStartPaM = RemoveText();
/*N*/   BOOL bUndoCurrentlyEnabled = IsUndoEnabled();
/*N*/   // Der von Hand reingesteckte Text kann nicht vom Anwender rueckgaengig gemacht werden.
/*N*/   EnableUndo( FALSE );
/*N*/
/*N*/   EditSelection aEmptySel( aStartPaM, aStartPaM );
/*N*/   EditPaM aPaM = aStartPaM;
/*N*/   if ( rText.Len() )
/*N*/       aPaM = ImpInsertText( aEmptySel, rText );
/*N*/
/*N*/   for ( USHORT nView = 0; nView < aEditViews.Count(); nView++ )
/*N*/   {
/*N*/       EditView* pView = aEditViews[nView];
/*N*/       DBG_CHKOBJ( pView, EditView, 0 );
/*N*/       pView->pImpEditView->SetEditSelection( EditSelection( aPaM, aPaM ) );
/*N*/       // Wenn kein Text, dann auch Kein Format&Update
/*N*/       // => Der Text bleibt stehen.
/*N*/       if ( !rText.Len() && GetUpdateMode() )
/*N*/       {
/*?*/           Rectangle aTmpRec( pView->GetOutputArea().TopLeft(),
/*?*/                               Size( aPaperSize.Width(), nCurTextHeight ) );
/*?*/           aTmpRec.Intersection( pView->GetOutputArea() );
/*?*/           pView->GetWindow()->Invalidate( aTmpRec );
/*N*/       }
/*N*/   }
/*N*/   if( !rText.Len() )  // sonst muss spaeter noch invalidiert werden, !bFormatted reicht.
/*N*/       nCurTextHeight = 0;
/*N*/   EnableUndo( bUndoCurrentlyEnabled );
/*N*/ #ifndef SVX_LIGHT
/*N*/   DBG_ASSERT( !HasUndoManager() || !GetUndoManager().GetUndoActionCount(), "Undo nach SetText?" );
/*N*/ #endif
/*N*/ }


/*N*/ const SfxItemSet& ImpEditEngine::GetEmptyItemSet()
/*N*/ {
/*N*/   if ( !pEmptyItemSet )
/*N*/   {
/*N*/       pEmptyItemSet = new SfxItemSet( aEditDoc.GetItemPool(), EE_ITEMS_START, EE_ITEMS_END );
/*N*/       for ( USHORT nWhich = EE_ITEMS_START; nWhich <= EE_CHAR_END; nWhich++)
/*N*/       {
/*N*/           pEmptyItemSet->ClearItem( nWhich );
/*N*/       }
/*N*/   }
/*N*/   return *pEmptyItemSet;
/*N*/ }

//  ----------------------------------------------------------------------
//  MISC
//  ----------------------------------------------------------------------
/*N*/ void ImpEditEngine::CursorMoved( ContentNode* pPrevNode )
/*N*/ {
/*N*/   // Leere Attribute loeschen, aber nur, wenn Absatz nicht leer!
/*N*/   if ( pPrevNode->GetCharAttribs().HasEmptyAttribs() && pPrevNode->Len() )
/*?*/   {DBG_ASSERT(0, "STRIP");} //STRIP001    pPrevNode->GetCharAttribs().DeleteEmptyAttribs( aEditDoc.GetItemPool() );
/*N*/ }

/*N*/ void ImpEditEngine::TextModified()
/*N*/ {
/*N*/   bFormatted = FALSE;
/*N*/
/*N*/     if ( GetNotifyHdl().IsSet() )
/*N*/     {
/*?*/         DBG_ASSERT(0, "STRIP"); //STRIP001 EENotify aNotify( EE_NOTIFY_TEXTMODIFIED );
//STRIP001 /*?*/         aNotify.pEditEngine = GetEditEnginePtr();
//STRIP001 /*?*/         CallNotify( aNotify );
/*N*/     }
/*N*/ }


/*N*/ void ImpEditEngine::ParaAttribsChanged( ContentNode* pNode )
/*N*/ {
/*N*/   DBG_ASSERT( pNode, "ParaAttribsChanged: Welcher?" );
/*N*/
/*N*/   aEditDoc.SetModified( TRUE );
/*N*/   bFormatted = FALSE;
/*N*/
/*N*/   ParaPortion* pPortion = FindParaPortion( pNode );
/*N*/   DBG_ASSERT( pPortion, "ParaAttribsChanged: Portion?" );
/*N*/   pPortion->MarkSelectionInvalid( 0, pNode->Len() );
/*N*/
/*N*/   USHORT nPara = aEditDoc.GetPos( pNode );
/*N*/   pEditEngine->ParaAttribsChanged( nPara );
/*N*/
/*N*/   ParaPortion* pNextPortion = GetParaPortions().SaveGetObject( nPara+1 );
/*N*/   // => wird sowieso noch formatiert, wenn Invalid.
/*N*/   if ( pNextPortion && !pNextPortion->IsInvalid() )
/*?*/       CalcHeight( pNextPortion );
/*N*/ }

//  ----------------------------------------------------------------------
//  Cursorbewegungen
//  ----------------------------------------------------------------------

//STRIP001 EditSelection ImpEditEngine::MoveCursor( const KeyEvent& rKeyEvent, EditView* pEditView )
//STRIP001 {
//STRIP001  // Eigentlich nur bei Up/Down noetig, aber was solls.
//STRIP001  CheckIdleFormatter();
//STRIP001
//STRIP001  EditPaM aPaM( pEditView->pImpEditView->GetEditSelection().Max() );
//STRIP001
//STRIP001  EditPaM aOldPaM( aPaM );
//STRIP001
//STRIP001     TextDirectionality eTextDirection = TextDirectionality_LeftToRight_TopToBottom;
//STRIP001  if ( IsVertical() )
//STRIP001         eTextDirection = TextDirectionality_TopToBottom_RightToLeft;
//STRIP001     else if ( IsRightToLeft( GetEditDoc().GetPos( aPaM.GetNode() ) ) )
//STRIP001         eTextDirection = TextDirectionality_RightToLeft_TopToBottom;
//STRIP001
//STRIP001     KeyEvent aTranslatedKeyEvent = rKeyEvent.LogicalTextDirectionality( eTextDirection );
//STRIP001
//STRIP001     BOOL bCtrl = aTranslatedKeyEvent.GetKeyCode().IsMod1() ? TRUE : FALSE;
//STRIP001  USHORT nCode = aTranslatedKeyEvent.GetKeyCode().GetCode();
//STRIP001
//STRIP001     if ( DoVisualCursorTraveling( aPaM.GetNode() ) )
//STRIP001     {
//STRIP001         // Only for simple cursor movement...
//STRIP001         if ( !bCtrl && ( ( nCode == KEY_LEFT ) || ( nCode == KEY_RIGHT ) ) )
//STRIP001         {
//STRIP001             aPaM = CursorVisualLeftRight( pEditView, aPaM, rKeyEvent.GetKeyCode().IsMod2() ? i18n::CharacterIteratorMode::SKIPCHARACTER : i18n::CharacterIteratorMode::SKIPCELL, rKeyEvent.GetKeyCode().GetCode() == KEY_LEFT );
//STRIP001          nCode = 0;  // skip switch statement
//STRIP001         }
//STRIP001         /*
//STRIP001         else if ( !bCtrl && ( ( nCode == KEY_HOME ) || ( nCode == KEY_END ) ) )
//STRIP001         {
//STRIP001             aPaM = CursorVisualStartEnd( pEditView, aPaM, nCode == KEY_HOME );
//STRIP001          nCode = 0;  // skip switch statement
//STRIP001         }
//STRIP001         */
//STRIP001     }
//STRIP001
//STRIP001  switch ( nCode )
//STRIP001  {
//STRIP001      case KEY_UP:        aPaM = CursorUp( aPaM, pEditView );
//STRIP001                          break;
//STRIP001      case KEY_DOWN:      aPaM = CursorDown( aPaM, pEditView );
//STRIP001                          break;
//STRIP001         case KEY_LEFT:       aPaM = bCtrl ? WordLeft( aPaM ) : CursorLeft( aPaM, aTranslatedKeyEvent.GetKeyCode().IsMod2() ? i18n::CharacterIteratorMode::SKIPCHARACTER : i18n::CharacterIteratorMode::SKIPCELL );
//STRIP001                          break;
//STRIP001      case KEY_RIGHT:     aPaM = bCtrl ? WordRight( aPaM ) : CursorRight( aPaM, aTranslatedKeyEvent.GetKeyCode().IsMod2() ? i18n::CharacterIteratorMode::SKIPCHARACTER : i18n::CharacterIteratorMode::SKIPCELL );
//STRIP001                          break;
//STRIP001      case KEY_HOME:      aPaM = bCtrl ? CursorStartOfDoc() : CursorStartOfLine( aPaM );
//STRIP001                          break;
//STRIP001      case KEY_END:       aPaM = bCtrl ? CursorEndOfDoc() : CursorEndOfLine( aPaM );
//STRIP001                          break;
//STRIP001      case KEY_PAGEUP:    aPaM = bCtrl ? CursorStartOfDoc() : PageUp( aPaM, pEditView );
//STRIP001                          break;
//STRIP001      case KEY_PAGEDOWN:  aPaM = bCtrl ? CursorEndOfDoc() : PageDown( aPaM, pEditView );
//STRIP001                          break;
//STRIP001  }
//STRIP001
//STRIP001  if ( aOldPaM != aPaM )
//STRIP001  {
//STRIP001      CursorMoved( aOldPaM.GetNode() );
//STRIP001      if ( aStatus.NotifyCursorMovements() && ( aOldPaM.GetNode() != aPaM.GetNode() ) )
//STRIP001      {
//STRIP001          aStatus.GetStatusWord() = aStatus.GetStatusWord() | EE_STAT_CRSRLEFTPARA;
//STRIP001          aStatus.GetPrevParagraph() = aEditDoc.GetPos( aOldPaM.GetNode() );
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      aStatus.GetStatusWord() = aStatus.GetStatusWord() | EE_STAT_CRSRMOVEFAIL;
//STRIP001
//STRIP001  // Bewirkt evtl. ein CreateAnchor oder Deselection all
//STRIP001  aSelEngine.SetCurView( pEditView );
//STRIP001  aSelEngine.CursorPosChanging( aTranslatedKeyEvent.GetKeyCode().IsShift(), aTranslatedKeyEvent.GetKeyCode().IsMod1() );
//STRIP001  EditPaM aOldEnd( pEditView->pImpEditView->GetEditSelection().Max() );
//STRIP001  pEditView->pImpEditView->GetEditSelection().Max() = aPaM;
//STRIP001  if ( aTranslatedKeyEvent.GetKeyCode().IsShift() )
//STRIP001  {
//STRIP001      // Dann wird die Selektion erweitert...
//STRIP001      EditSelection aTmpNewSel( aOldEnd, aPaM );
//STRIP001      pEditView->pImpEditView->DrawSelection( aTmpNewSel );
//STRIP001  }
//STRIP001  else
//STRIP001      pEditView->pImpEditView->GetEditSelection().Min() = aPaM;
//STRIP001
//STRIP001  return pEditView->pImpEditView->GetEditSelection();
//STRIP001 }

//STRIP001 EditPaM ImpEditEngine::CursorVisualStartEnd( EditView* pEditView, const EditPaM& rPaM, BOOL bStart )
//STRIP001 {
//STRIP001     EditPaM aPaM( rPaM );
//STRIP001
//STRIP001     USHORT nPara = GetEditDoc().GetPos( aPaM.GetNode() );
//STRIP001     ParaPortion* pParaPortion = GetParaPortions().SaveGetObject( nPara );
//STRIP001
//STRIP001     USHORT nLine = pParaPortion->GetLines().FindLine( aPaM.GetIndex(), sal_False );
//STRIP001     EditLine* pLine = pParaPortion->GetLines().GetObject( nLine );
//STRIP001     BOOL bEmptyLine = pLine->GetStart() == pLine->GetEnd();
//STRIP001
//STRIP001     pEditView->pImpEditView->nExtraCursorFlags = 0;
//STRIP001
//STRIP001     if ( !bEmptyLine )
//STRIP001     {
//STRIP001         String aLine( *aPaM.GetNode(), pLine->GetStart(), pLine->GetEnd() - pLine->GetStart() );
//STRIP001         USHORT nPosInLine = aPaM.GetIndex() - pLine->GetStart();
//STRIP001
//STRIP001         const sal_Unicode* pLineString = aLine.GetBuffer();
//STRIP001
//STRIP001         UErrorCode nError = U_ZERO_ERROR;
//STRIP001         UBiDi* pBidi = ubidi_openSized( aLine.Len(), 0, &nError );
//STRIP001
//STRIP001         const BYTE nDefaultDir = IsRightToLeft( nPara ) ? UBIDI_RTL : UBIDI_LTR;
//STRIP001         ubidi_setPara( pBidi, pLineString, aLine.Len(), nDefaultDir, NULL, &nError );
//STRIP001
//STRIP001         USHORT nVisPos = bStart ? 0 : aLine.Len()-1;
//STRIP001         USHORT nLogPos = (USHORT)ubidi_getLogicalIndex( pBidi, nVisPos, &nError );
//STRIP001
//STRIP001         ubidi_close( pBidi );
//STRIP001
//STRIP001         aPaM.GetIndex() = nLogPos + pLine->GetStart();
//STRIP001
//STRIP001         USHORT nTmp;
//STRIP001         USHORT nTextPortion = pParaPortion->GetTextPortions().FindPortion( aPaM.GetIndex(), nTmp, TRUE );
//STRIP001         TextPortion* pTextPortion = pParaPortion->GetTextPortions().GetObject( nTextPortion );
//STRIP001         USHORT nRTLLevel = pTextPortion->GetRightToLeft();
//STRIP001         BOOL bParaRTL = IsRightToLeft( nPara );
//STRIP001         BOOL bPortionRTL = nRTLLevel%2 ? TRUE : FALSE;
//STRIP001
//STRIP001         if ( bStart )
//STRIP001         {
//STRIP001             pEditView->pImpEditView->SetCursorBidiLevel( bPortionRTL ? 0 : 1 );
//STRIP001             // Maybe we must be *behind* the character
//STRIP001             if ( bPortionRTL && pEditView->IsInsertMode() )
//STRIP001                 aPaM.GetIndex()++;
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             pEditView->pImpEditView->SetCursorBidiLevel( bPortionRTL ? 1 : 0 );
//STRIP001             if ( !bPortionRTL && pEditView->IsInsertMode() )
//STRIP001                 aPaM.GetIndex()++;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     return aPaM;
//STRIP001 }

//STRIP001 EditPaM ImpEditEngine::CursorVisualLeftRight( EditView* pEditView, const EditPaM& rPaM, USHORT nCharacterIteratorMode, BOOL bVisualToLeft )
//STRIP001 {
//STRIP001     EditPaM aPaM( rPaM );
//STRIP001
//STRIP001     USHORT nPara = GetEditDoc().GetPos( aPaM.GetNode() );
//STRIP001     ParaPortion* pParaPortion = GetParaPortions().SaveGetObject( nPara );
//STRIP001
//STRIP001     USHORT nLine = pParaPortion->GetLines().FindLine( aPaM.GetIndex(), sal_False );
//STRIP001     EditLine* pLine = pParaPortion->GetLines().GetObject( nLine );
//STRIP001     BOOL bEmptyLine = pLine->GetStart() == pLine->GetEnd();
//STRIP001
//STRIP001     USHORT nCurrentCursorFlags = pEditView->pImpEditView->nExtraCursorFlags;
//STRIP001     pEditView->pImpEditView->nExtraCursorFlags = 0;
//STRIP001
//STRIP001     BOOL bParaRTL = IsRightToLeft( nPara );
//STRIP001
//STRIP001     BOOL bDone = FALSE;
//STRIP001
//STRIP001     if ( bEmptyLine )
//STRIP001     {
//STRIP001         if ( bVisualToLeft )
//STRIP001         {
//STRIP001             aPaM = CursorUp( aPaM, pEditView );
//STRIP001             if ( aPaM != rPaM )
//STRIP001                 aPaM = CursorVisualStartEnd( pEditView, aPaM, FALSE );
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             aPaM = CursorDown( aPaM, pEditView );
//STRIP001             if ( aPaM != rPaM )
//STRIP001                 aPaM = CursorVisualStartEnd( pEditView, aPaM, TRUE );
//STRIP001         }
//STRIP001
//STRIP001         bDone = TRUE;
//STRIP001     }
//STRIP001
//STRIP001     BOOL bLogicalBackward = bParaRTL ? !bVisualToLeft : bVisualToLeft;
//STRIP001
//STRIP001     if ( !bDone && pEditView->IsInsertMode() )
//STRIP001     {
//STRIP001         // Check if we are within a portion and don't have overwrite mode, then it's easy...
//STRIP001         USHORT nPortionStart;
//STRIP001         USHORT nTextPortion = pParaPortion->GetTextPortions().FindPortion( aPaM.GetIndex(), nPortionStart, FALSE );
//STRIP001         TextPortion* pTextPortion = pParaPortion->GetTextPortions().GetObject( nTextPortion );
//STRIP001
//STRIP001         BOOL bPortionBoundary = ( aPaM.GetIndex() == nPortionStart ) || ( aPaM.GetIndex() == (nPortionStart+pTextPortion->GetLen()) );
//STRIP001         USHORT nRTLLevel = pTextPortion->GetRightToLeft();
//STRIP001
//STRIP001         // Portion boundary doesn't matter if both have same RTL level
//STRIP001         USHORT nRTLLevelNextPortion = 0xFFFF;
//STRIP001         if ( bPortionBoundary && aPaM.GetIndex() && ( aPaM.GetIndex() < aPaM.GetNode()->Len() ) )
//STRIP001         {
//STRIP001             USHORT nTmp;
//STRIP001             USHORT nNextTextPortion = pParaPortion->GetTextPortions().FindPortion( aPaM.GetIndex()+1, nTmp, bLogicalBackward ? FALSE : TRUE );
//STRIP001             TextPortion* pNextTextPortion = pParaPortion->GetTextPortions().GetObject( nNextTextPortion );
//STRIP001             nRTLLevelNextPortion = pNextTextPortion->GetRightToLeft();
//STRIP001         }
//STRIP001
//STRIP001         if ( !bPortionBoundary || ( nRTLLevel == nRTLLevelNextPortion ) )
//STRIP001         {
//STRIP001             if ( ( bVisualToLeft && !(nRTLLevel%2) ) || ( !bVisualToLeft && (nRTLLevel%2) ) )
//STRIP001             {
//STRIP001                 aPaM = CursorLeft( aPaM, nCharacterIteratorMode );
//STRIP001                 pEditView->pImpEditView->SetCursorBidiLevel( 1 );
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 aPaM = CursorRight( aPaM, nCharacterIteratorMode );
//STRIP001                 pEditView->pImpEditView->SetCursorBidiLevel( 0 );
//STRIP001             }
//STRIP001             bDone = TRUE;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     if ( !bDone )
//STRIP001     {
//STRIP001         BOOL bGotoStartOfNextLine = FALSE;
//STRIP001         BOOL bGotoEndOfPrevLine = FALSE;
//STRIP001
//STRIP001         String aLine( *aPaM.GetNode(), pLine->GetStart(), pLine->GetEnd() - pLine->GetStart() );
//STRIP001         USHORT nPosInLine = aPaM.GetIndex() - pLine->GetStart();
//STRIP001
//STRIP001         const sal_Unicode* pLineString = aLine.GetBuffer();
//STRIP001
//STRIP001         UErrorCode nError = U_ZERO_ERROR;
//STRIP001         UBiDi* pBidi = ubidi_openSized( aLine.Len(), 0, &nError );
//STRIP001
//STRIP001         const BYTE nDefaultDir = IsRightToLeft( nPara ) ? UBIDI_RTL : UBIDI_LTR;
//STRIP001         ubidi_setPara( pBidi, pLineString, aLine.Len(), nDefaultDir, NULL, &nError );
//STRIP001
//STRIP001         if ( !pEditView->IsInsertMode() )
//STRIP001         {
//STRIP001             BOOL bEndOfLine = nPosInLine == aLine.Len();
//STRIP001             USHORT nVisPos = (USHORT)ubidi_getVisualIndex( pBidi, !bEndOfLine ? nPosInLine : nPosInLine-1, &nError );
//STRIP001             if ( bVisualToLeft )
//STRIP001             {
//STRIP001                 bGotoEndOfPrevLine = nVisPos == 0;
//STRIP001                 if ( !bEndOfLine )
//STRIP001                     nVisPos--;
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 bGotoStartOfNextLine = nVisPos == (aLine.Len() - 1);
//STRIP001                 if ( !bEndOfLine )
//STRIP001                     nVisPos++;
//STRIP001             }
//STRIP001
//STRIP001             if ( !bGotoEndOfPrevLine && !bGotoStartOfNextLine )
//STRIP001             {
//STRIP001                 USHORT nLogPos = (USHORT)ubidi_getLogicalIndex( pBidi, nVisPos, &nError );
//STRIP001                 aPaM.GetIndex() = pLine->GetStart() + nLogPos;
//STRIP001                 pEditView->pImpEditView->SetCursorBidiLevel( 0 );
//STRIP001             }
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             BOOL bWasBehind = FALSE;
//STRIP001             BOOL bBeforePortion = !nPosInLine || pEditView->pImpEditView->GetCursorBidiLevel() == 1;
//STRIP001             if ( nPosInLine && ( !bBeforePortion ) ) // before the next portion
//STRIP001                 bWasBehind = TRUE;  // step one back, otherwise visual will be unusable when rtl portion follows.
//STRIP001
//STRIP001             USHORT nPortionStart;
//STRIP001             USHORT nTextPortion = pParaPortion->GetTextPortions().FindPortion( aPaM.GetIndex(), nPortionStart, bBeforePortion );
//STRIP001             TextPortion* pTextPortion = pParaPortion->GetTextPortions().GetObject( nTextPortion );
//STRIP001             BOOL bRTLPortion = (pTextPortion->GetRightToLeft() % 2) != 0;
//STRIP001
//STRIP001             // -1: We are 'behind' the character
//STRIP001             long nVisPos = (long)ubidi_getVisualIndex( pBidi, bWasBehind ? nPosInLine-1 : nPosInLine, &nError );
//STRIP001             if ( bVisualToLeft )
//STRIP001             {
//STRIP001                 if ( !bWasBehind || bRTLPortion )
//STRIP001                     nVisPos--;
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 if ( bWasBehind || bRTLPortion || bBeforePortion )
//STRIP001                     nVisPos++;
//STRIP001 //                if ( bWasBehind && bRTLPortion )
//STRIP001 //                    nVisPos++;
//STRIP001             }
//STRIP001
//STRIP001             bGotoEndOfPrevLine = nVisPos < 0;
//STRIP001             bGotoStartOfNextLine = nVisPos >= aLine.Len();
//STRIP001
//STRIP001             if ( !bGotoEndOfPrevLine && !bGotoStartOfNextLine )
//STRIP001             {
//STRIP001                 USHORT nLogPos = (USHORT)ubidi_getLogicalIndex( pBidi, nVisPos, &nError );
//STRIP001
//STRIP001 /*
//STRIP001                 if ( nLogPos == aPaM.GetIndex() )
//STRIP001                 {
//STRIP001                     if ( bVisualToLeft )
//STRIP001                         bGotoEndOfPrevLine = TRUE;
//STRIP001                     else
//STRIP001                         bGotoStartOfNextLine = TRUE;
//STRIP001                 }
//STRIP001                 else
//STRIP001 */
//STRIP001                 {
//STRIP001                     aPaM.GetIndex() = pLine->GetStart() + nLogPos;
//STRIP001
//STRIP001                     // RTL portion, stay visually on the left side.
//STRIP001                     USHORT nPortionStart;
//STRIP001                     // USHORT nTextPortion = pParaPortion->GetTextPortions().FindPortion( aPaM.GetIndex(), nPortionStart, !bRTLPortion );
//STRIP001                     USHORT nTextPortion = pParaPortion->GetTextPortions().FindPortion( aPaM.GetIndex(), nPortionStart, TRUE );
//STRIP001                     TextPortion* pTextPortion = pParaPortion->GetTextPortions().GetObject( nTextPortion );
//STRIP001                     if ( bVisualToLeft && !bRTLPortion && ( pTextPortion->GetRightToLeft() % 2 ) )
//STRIP001                         aPaM.GetIndex()++;
//STRIP001                     else if ( !bVisualToLeft && bRTLPortion && ( bWasBehind || !(pTextPortion->GetRightToLeft() % 2 )) )
//STRIP001                         aPaM.GetIndex()++;
//STRIP001
//STRIP001                     pEditView->pImpEditView->SetCursorBidiLevel( nPortionStart );
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         ubidi_close( pBidi );
//STRIP001
//STRIP001         if ( bGotoEndOfPrevLine )
//STRIP001         {
//STRIP001             aPaM = CursorUp( aPaM, pEditView );
//STRIP001             if ( aPaM != rPaM )
//STRIP001                 aPaM = CursorVisualStartEnd( pEditView, aPaM, FALSE );
//STRIP001         }
//STRIP001         else if ( bGotoStartOfNextLine )
//STRIP001         {
//STRIP001             aPaM = CursorDown( aPaM, pEditView );
//STRIP001             if ( aPaM != rPaM )
//STRIP001                 aPaM = CursorVisualStartEnd( pEditView, aPaM, TRUE );
//STRIP001         }
//STRIP001     }
//STRIP001     return aPaM;
//STRIP001 }


//STRIP001 EditPaM ImpEditEngine::CursorLeft( const EditPaM& rPaM, USHORT nCharacterIteratorMode )
//STRIP001 {
//STRIP001     EditPaM aCurPaM( rPaM );
//STRIP001  EditPaM aNewPaM( aCurPaM );
//STRIP001
//STRIP001  if ( aCurPaM.GetIndex() )
//STRIP001  {
//STRIP001      sal_Int32 nCount = 1;
//STRIP001      uno::Reference < i18n::XBreakIterator > xBI = ImplGetBreakIterator();
//STRIP001          aNewPaM.SetIndex( (USHORT)xBI->previousCharacters( *aNewPaM.GetNode(), aNewPaM.GetIndex(), GetLocale( aNewPaM ), nCharacterIteratorMode, nCount, nCount ) );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      ContentNode* pNode = aCurPaM.GetNode();
//STRIP001      pNode = GetPrevVisNode( pNode );
//STRIP001      if ( pNode )
//STRIP001      {
//STRIP001          aNewPaM.SetNode( pNode );
//STRIP001          aNewPaM.SetIndex( pNode->Len() );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return aNewPaM;
//STRIP001 }

//STRIP001 EditPaM ImpEditEngine::CursorRight( const EditPaM& rPaM, USHORT nCharacterIteratorMode )
//STRIP001 {
//STRIP001     EditPaM aCurPaM( rPaM );
//STRIP001  EditPaM aNewPaM( aCurPaM );
//STRIP001
//STRIP001     if ( aCurPaM.GetIndex() < aCurPaM.GetNode()->Len() )
//STRIP001  {
//STRIP001      uno::Reference < i18n::XBreakIterator > xBI = ImplGetBreakIterator();
//STRIP001      sal_Int32 nCount = 1;
//STRIP001      aNewPaM.SetIndex( (USHORT)xBI->nextCharacters( *aNewPaM.GetNode(), aNewPaM.GetIndex(), GetLocale( aNewPaM ), nCharacterIteratorMode, nCount, nCount ) );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      ContentNode* pNode = aCurPaM.GetNode();
//STRIP001      pNode = GetNextVisNode( pNode );
//STRIP001      if ( pNode )
//STRIP001      {
//STRIP001          aNewPaM.SetNode( pNode );
//STRIP001          aNewPaM.SetIndex( 0 );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return aNewPaM;
//STRIP001 }

//STRIP001 EditPaM ImpEditEngine::CursorUp( const EditPaM& rPaM, EditView* pView )
//STRIP001 {
//STRIP001  DBG_ASSERT( pView, "Keine View - Keine Cursorbewegung!" );
//STRIP001
//STRIP001  ParaPortion* pPPortion = FindParaPortion( rPaM.GetNode() );
//STRIP001  DBG_ASSERT( pPPortion, "Keine passende Portion gefunden: CursorUp" );
//STRIP001  USHORT nLine = pPPortion->GetLineNumber( rPaM.GetIndex() );
//STRIP001  EditLine* pLine = pPPortion->GetLines().GetObject( nLine );
//STRIP001
//STRIP001  long nX;
//STRIP001  if ( pView->pImpEditView->nTravelXPos == TRAVEL_X_DONTKNOW )
//STRIP001  {
//STRIP001      nX = GetXPos( pPPortion, pLine, rPaM.GetIndex() );
//STRIP001      pView->pImpEditView->nTravelXPos = nX+nOnePixelInRef;
//STRIP001  }
//STRIP001  else
//STRIP001      nX = pView->pImpEditView->nTravelXPos;
//STRIP001
//STRIP001  EditPaM aNewPaM( rPaM );
//STRIP001  if ( nLine )    // gleicher Absatz
//STRIP001  {
//STRIP001      EditLine* pPrevLine = pPPortion->GetLines().GetObject(nLine-1);
//STRIP001      aNewPaM.SetIndex( GetChar( pPPortion, pPrevLine, nX ) );
//STRIP001      // Wenn davor eine autom.Umgebrochene Zeile, und ich muss genau an das
//STRIP001      // Ende dieser Zeile, landet der Cursor in der aktuellen Zeile am Anfang
//STRIP001      // Siehe Problem: Letztes Zeichen einer autom.umgebr. Zeile = Cursor
//STRIP001      if ( aNewPaM.GetIndex() && ( aNewPaM.GetIndex() == pLine->GetStart() ) )
//STRIP001          aNewPaM = CursorLeft( aNewPaM );
//STRIP001  }
//STRIP001  else    // vorheriger Absatz
//STRIP001  {
//STRIP001      ParaPortion* pPrevPortion = GetPrevVisPortion( pPPortion );
//STRIP001      if ( pPrevPortion )
//STRIP001      {
//STRIP001          pLine = pPrevPortion->GetLines().GetObject( pPrevPortion->GetLines().Count()-1 );
//STRIP001          DBG_ASSERT( pLine, "Zeile davor nicht gefunden: CursorUp" );
//STRIP001          aNewPaM.SetNode( pPrevPortion->GetNode() );
//STRIP001          aNewPaM.SetIndex( GetChar( pPrevPortion, pLine, nX+nOnePixelInRef ) );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return aNewPaM;
//STRIP001 }

//STRIP001 EditPaM ImpEditEngine::CursorDown( const EditPaM& rPaM, EditView* pView )
//STRIP001 {
//STRIP001  DBG_ASSERT( pView, "Keine View - Keine Cursorbewegung!" );
//STRIP001
//STRIP001  ParaPortion* pPPortion = FindParaPortion( rPaM.GetNode() );
//STRIP001  DBG_ASSERT( pPPortion, "Keine passende Portion gefunden: CursorDown" );
//STRIP001  USHORT nLine = pPPortion->GetLineNumber( rPaM.GetIndex() );
//STRIP001
//STRIP001  long nX;
//STRIP001  if ( pView->pImpEditView->nTravelXPos == TRAVEL_X_DONTKNOW )
//STRIP001  {
//STRIP001      EditLine* pLine = pPPortion->GetLines().GetObject(nLine);
//STRIP001      nX = GetXPos( pPPortion, pLine, rPaM.GetIndex() );
//STRIP001      pView->pImpEditView->nTravelXPos = nX+nOnePixelInRef;
//STRIP001  }
//STRIP001  else
//STRIP001      nX = pView->pImpEditView->nTravelXPos;
//STRIP001
//STRIP001  EditPaM aNewPaM( rPaM );
//STRIP001  if ( nLine < pPPortion->GetLines().Count()-1 )
//STRIP001  {
//STRIP001      EditLine* pNextLine = pPPortion->GetLines().GetObject(nLine+1);
//STRIP001      aNewPaM.SetIndex( GetChar( pPPortion, pNextLine, nX ) );
//STRIP001      // Sonderbehandlung siehe CursorUp...
//STRIP001      if ( ( aNewPaM.GetIndex() == pNextLine->GetEnd() ) && ( aNewPaM.GetIndex() > pNextLine->GetStart() ) && ( aNewPaM.GetIndex() < pPPortion->GetNode()->Len() ) )
//STRIP001          aNewPaM = CursorLeft( aNewPaM );
//STRIP001  }
//STRIP001  else    // naechster Absatz
//STRIP001  {
//STRIP001      ParaPortion* pNextPortion = GetNextVisPortion( pPPortion );
//STRIP001      if ( pNextPortion )
//STRIP001      {
//STRIP001          EditLine* pLine = pNextPortion->GetLines().GetObject(0);
//STRIP001          DBG_ASSERT( pLine, "Zeile davor nicht gefunden: CursorUp" );
//STRIP001          aNewPaM.SetNode( pNextPortion->GetNode() );
//STRIP001          // Nie ganz ans Ende wenn mehrere Zeilen, da dann eine
//STRIP001          // Zeile darunter der Cursor angezeigt wird.
//STRIP001          aNewPaM.SetIndex( GetChar( pNextPortion, pLine, nX+nOnePixelInRef ) );
//STRIP001          if ( ( aNewPaM.GetIndex() == pLine->GetEnd() ) && ( aNewPaM.GetIndex() > pLine->GetStart() ) && ( pNextPortion->GetLines().Count() > 1 ) )
//STRIP001              aNewPaM = CursorLeft( aNewPaM );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return aNewPaM;
//STRIP001 }

//STRIP001 EditPaM ImpEditEngine::CursorStartOfLine( const EditPaM& rPaM )
//STRIP001 {
//STRIP001  ParaPortion* pCurPortion = FindParaPortion( rPaM.GetNode() );
//STRIP001  DBG_ASSERT( pCurPortion, "Keine Portion fuer den PaM ?" );
//STRIP001  USHORT nLine = pCurPortion->GetLineNumber( rPaM.GetIndex() );
//STRIP001  EditLine* pLine = pCurPortion->GetLines().GetObject(nLine);
//STRIP001  DBG_ASSERT( pLine, "Aktuelle Zeile nicht gefunden ?!" );
//STRIP001
//STRIP001  EditPaM aNewPaM( rPaM );
//STRIP001  aNewPaM.SetIndex( pLine->GetStart() );
//STRIP001  return aNewPaM;
//STRIP001 }

//STRIP001 EditPaM ImpEditEngine::CursorEndOfLine( const EditPaM& rPaM )
//STRIP001 {
//STRIP001  ParaPortion* pCurPortion = FindParaPortion( rPaM.GetNode() );
//STRIP001  DBG_ASSERT( pCurPortion, "Keine Portion fuer den PaM ?" );
//STRIP001  USHORT nLine = pCurPortion->GetLineNumber( rPaM.GetIndex() );
//STRIP001  EditLine* pLine = pCurPortion->GetLines().GetObject(nLine);
//STRIP001  DBG_ASSERT( pLine, "Aktuelle Zeile nicht gefunden ?!" );
//STRIP001
//STRIP001  EditPaM aNewPaM( rPaM );
//STRIP001  aNewPaM.SetIndex( pLine->GetEnd() );
//STRIP001  if ( pLine->GetEnd() > pLine->GetStart() )
//STRIP001  {
//STRIP001      xub_Unicode cLastChar = aNewPaM.GetNode()->GetChar( aNewPaM.GetIndex()-1 );
//STRIP001      if ( aNewPaM.GetNode()->IsFeature( aNewPaM.GetIndex() - 1 ) )
//STRIP001      {
//STRIP001          // Bei einem weichen Umbruch muss ich davor stehen!
//STRIP001          EditCharAttrib* pNextFeature = aNewPaM.GetNode()->GetCharAttribs().FindFeature( aNewPaM.GetIndex()-1 );
//STRIP001          if ( pNextFeature && ( pNextFeature->GetItem()->Which() == EE_FEATURE_LINEBR ) )
//STRIP001              aNewPaM = CursorLeft( aNewPaM );
//STRIP001      }
//STRIP001      else if ( ( aNewPaM.GetNode()->GetChar( aNewPaM.GetIndex() - 1 ) == ' ' ) && ( aNewPaM.GetIndex() != aNewPaM.GetNode()->Len() ) )
//STRIP001      {
//STRIP001          // Bei einem Blank in einer autom. umgebrochenen Zeile macht es Sinn,
//STRIP001          // davor zu stehen, da der Anwender hinter das Wort will.
//STRIP001          // Wenn diese geaendert wird, Sonderbehandlung fuer Pos1 nach End!
//STRIP001          aNewPaM = CursorLeft( aNewPaM );
//STRIP001      }
//STRIP001  }
//STRIP001  return aNewPaM;
//STRIP001 }

//STRIP001 EditPaM ImpEditEngine::CursorStartOfParagraph( const EditPaM& rPaM )
//STRIP001 {
//STRIP001  EditPaM aPaM( rPaM.GetNode(), 0 );
//STRIP001  return aPaM;
//STRIP001 }

//STRIP001 EditPaM ImpEditEngine::CursorEndOfParagraph( const EditPaM& rPaM )
//STRIP001 {
//STRIP001  EditPaM aPaM( rPaM.GetNode(), rPaM.GetNode()->Len() );
//STRIP001  return aPaM;
//STRIP001 }

//STRIP001 EditPaM ImpEditEngine::CursorStartOfDoc()
//STRIP001 {
//STRIP001  EditPaM aPaM( aEditDoc.SaveGetObject( 0 ), 0 );
//STRIP001  return aPaM;
//STRIP001 }

//STRIP001 EditPaM ImpEditEngine::CursorEndOfDoc()
//STRIP001 {
//STRIP001  ContentNode* pLastNode = aEditDoc.SaveGetObject( aEditDoc.Count()-1 );
//STRIP001  ParaPortion* pLastPortion = GetParaPortions().SaveGetObject( aEditDoc.Count()-1 );
//STRIP001  DBG_ASSERT( pLastNode && pLastPortion, "CursorEndOfDoc: Node oder Portion nicht gefunden" );
//STRIP001
//STRIP001  if ( !pLastPortion->IsVisible() )
//STRIP001  {
//STRIP001      pLastNode = GetPrevVisNode( pLastPortion->GetNode() );
//STRIP001      DBG_ASSERT( pLastNode, "Kein sichtbarer Absatz?" );
//STRIP001      if ( !pLastNode )
//STRIP001          pLastNode = aEditDoc.SaveGetObject( aEditDoc.Count()-1 );
//STRIP001  }
//STRIP001
//STRIP001  EditPaM aPaM( pLastNode, pLastNode->Len() );
//STRIP001  return aPaM;
//STRIP001 }

//STRIP001 EditPaM ImpEditEngine::PageUp( const EditPaM& rPaM, EditView* pView )
//STRIP001 {
//STRIP001  Rectangle aRec = PaMtoEditCursor( rPaM );
//STRIP001  Point aTopLeft = aRec.TopLeft();
//STRIP001  aTopLeft.Y() -= pView->GetVisArea().GetHeight() *9/10;
//STRIP001  aTopLeft.X() += nOnePixelInRef;
//STRIP001  if ( aTopLeft.Y() < 0 )
//STRIP001  {
//STRIP001      aTopLeft.Y() = 0;
//STRIP001  }
//STRIP001  return GetPaM( aTopLeft );
//STRIP001 }

//STRIP001 EditPaM ImpEditEngine::PageDown( const EditPaM& rPaM, EditView* pView )
//STRIP001 {
//STRIP001  Rectangle aRec = PaMtoEditCursor( rPaM );
//STRIP001  Point aBottomRight = aRec.BottomRight();
//STRIP001  aBottomRight.Y() += pView->GetVisArea().GetHeight() *9/10;
//STRIP001  aBottomRight.X() += nOnePixelInRef;
//STRIP001  long nHeight = GetTextHeight();
//STRIP001  if ( aBottomRight.Y() > nHeight )
//STRIP001  {
//STRIP001      aBottomRight.Y() = nHeight-2;
//STRIP001  }
//STRIP001  return GetPaM( aBottomRight );
//STRIP001 }

//STRIP001 EditPaM ImpEditEngine::WordLeft( const EditPaM& rPaM, sal_Int16 nWordType )
//STRIP001 {
//STRIP001  USHORT nCurrentPos = rPaM.GetIndex();
//STRIP001  EditPaM aNewPaM( rPaM );
//STRIP001  if ( nCurrentPos == 0 )
//STRIP001  {
//STRIP001      // Vorheriger Absatz...
//STRIP001      USHORT nCurPara = aEditDoc.GetPos( aNewPaM.GetNode() );
//STRIP001      ContentNode* pPrevNode = aEditDoc.SaveGetObject( --nCurPara );
//STRIP001      if ( pPrevNode )
//STRIP001      {
//STRIP001          aNewPaM.SetNode( pPrevNode );
//STRIP001          aNewPaM.SetIndex( pPrevNode->Len() );
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      uno::Reference < i18n::XBreakIterator > xBI = ImplGetBreakIterator();
//STRIP001      i18n::Boundary aBoundary = xBI->getWordBoundary( *aNewPaM.GetNode(), nCurrentPos, GetLocale( EditPaM( aNewPaM.GetNode(), nCurrentPos ) ), nWordType, sal_True );
//STRIP001      if ( aBoundary.startPos >= nCurrentPos )
//STRIP001          aBoundary = xBI->previousWord( *aNewPaM.GetNode(), nCurrentPos, GetLocale( EditPaM( aNewPaM.GetNode(), nCurrentPos ) ), nWordType );
//STRIP001         aNewPaM.SetIndex( ( aBoundary.startPos != (-1) ) ? (USHORT)aBoundary.startPos : 0 );
//STRIP001  }
//STRIP001
//STRIP001  return aNewPaM;
//STRIP001 }

/*N*/ EditPaM ImpEditEngine::WordRight( const EditPaM& rPaM, sal_Int16 nWordType )
/*N*/ {
/*N*/   xub_StrLen nMax = rPaM.GetNode()->Len();
/*N*/   EditPaM aNewPaM( rPaM );
/*N*/   if ( aNewPaM.GetIndex() < nMax )
/*N*/   {
/*N*/       uno::Reference < i18n::XBreakIterator > xBI = ImplGetBreakIterator();
/*N*/       i18n::Boundary aBoundary = xBI->nextWord( *aNewPaM.GetNode(), aNewPaM.GetIndex(), GetLocale( aNewPaM ), nWordType );
/*N*/       aNewPaM.SetIndex( (USHORT)aBoundary.startPos );
/*N*/   }
/*N*/   // not 'else', maybe the index reached nMax now...
/*N*/   if ( aNewPaM.GetIndex() >= nMax )
/*N*/   {
/*?*/       // Naechster Absatz...
/*?*/       USHORT nCurPara = aEditDoc.GetPos( aNewPaM.GetNode() );
/*?*/       ContentNode* pNextNode = aEditDoc.SaveGetObject( ++nCurPara );
/*?*/       if ( pNextNode )
/*?*/       {
/*?*/           aNewPaM.SetNode( pNextNode );
/*?*/           aNewPaM.SetIndex( 0 );
/*?*/       }
/*N*/   }
/*N*/   return aNewPaM;
/*N*/ }

//STRIP001 EditPaM ImpEditEngine::StartOfWord( const EditPaM& rPaM, sal_Int16 nWordType )
//STRIP001 {
//STRIP001  EditPaM aNewPaM( rPaM );
//STRIP001  uno::Reference < i18n::XBreakIterator > xBI = ImplGetBreakIterator();
//STRIP001  i18n::Boundary aBoundary = xBI->getWordBoundary( *rPaM.GetNode(), rPaM.GetIndex(), GetLocale( rPaM ), nWordType, sal_True );
//STRIP001  aNewPaM.SetIndex( (USHORT)aBoundary.startPos );
//STRIP001  return aNewPaM;
//STRIP001 }

//STRIP001 EditPaM ImpEditEngine::EndOfWord( const EditPaM& rPaM, sal_Int16 nWordType )
//STRIP001 {
//STRIP001  EditPaM aNewPaM( rPaM );
//STRIP001  uno::Reference < i18n::XBreakIterator > xBI = ImplGetBreakIterator();
//STRIP001  i18n::Boundary aBoundary = xBI->getWordBoundary( *rPaM.GetNode(), rPaM.GetIndex(), GetLocale( rPaM ), nWordType, sal_True );
//STRIP001  aNewPaM.SetIndex( (USHORT)aBoundary.endPos );
//STRIP001  return aNewPaM;
//STRIP001 }

/*N*/ EditSelection ImpEditEngine::SelectWord( const EditSelection& rCurSel, sal_Int16 nWordType, BOOL bAcceptStartOfWord )
/*N*/ {
/*N*/   EditSelection aNewSel( rCurSel );
/*N*/   EditPaM aPaM( rCurSel.Max() );
/*N*/   uno::Reference < i18n::XBreakIterator > xBI = ImplGetBreakIterator();
/*N*/   sal_Int16 nType = xBI->getWordType( *aPaM.GetNode(), aPaM.GetIndex(), GetLocale( aPaM ) );
/*N*/   if ( nType == i18n::WordType::ANY_WORD )
/*N*/   {
/*N*/       i18n::Boundary aBoundary = xBI->getWordBoundary( *aPaM.GetNode(), aPaM.GetIndex(), GetLocale( aPaM ), nWordType, sal_True );
/*N*/       // don't select when curser at end of word
/*N*/       if ( ( aBoundary.endPos > aPaM.GetIndex() ) &&
/*N*/            ( bAcceptStartOfWord || ( aBoundary.startPos < aPaM.GetIndex() ) ) )
/*N*/       {
/*N*/           aNewSel.Min().SetIndex( (USHORT)aBoundary.startPos );
/*N*/           aNewSel.Max().SetIndex( (USHORT)aBoundary.endPos );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return aNewSel;
/*N*/ }

/*N*/ void ImpEditEngine::InitScriptTypes( USHORT nPara )
/*N*/ {
/*N*/   ParaPortion* pParaPortion = GetParaPortions().SaveGetObject( nPara );
/*N*/   ScriptTypePosInfos& rTypes = pParaPortion->aScriptInfos;
/*N*/   rTypes.Remove( 0, rTypes.Count() );
/*N*/
/*N*/
/*N*/ //    pParaPortion->aExtraCharInfos.Remove( 0, pParaPortion->aExtraCharInfos.Count() );
/*N*/
/*N*/   ContentNode* pNode = pParaPortion->GetNode();
/*N*/   if ( pNode->Len() )
/*N*/   {
/*N*/       uno::Reference < i18n::XBreakIterator > xBI = ImplGetBreakIterator();
/*N*/
/*N*/       String aText( *pNode );
/*N*/
/*N*/       // To handle fields put the character from the field in the string,
/*N*/       // because endOfScript( ... ) will skip the CH_FEATURE, because this is WEAK
/*N*/       EditCharAttrib* pField = pNode->GetCharAttribs().FindNextAttrib( EE_FEATURE_FIELD, 0 );
/*N*/       while ( pField )
/*N*/       {
/*N*/           ::rtl::OUString aFldText( ((EditCharAttribField*)pField)->GetFieldValue() );
/*N*/           if ( aFldText.getLength() )
/*N*/           {
/*N*/               aText.SetChar( pField->GetStart(), aFldText.getStr()[0] );
/*N*/               short nFldScriptType = xBI->getScriptType( aFldText, 0 );
/*N*/
/*N*/               for ( USHORT nCharInField = 1; nCharInField < aFldText.getLength(); nCharInField++ )
/*N*/               {
/*N*/                   short nTmpType = xBI->getScriptType( aFldText, nCharInField );
/*N*/
/*N*/                   // First char from field wins...
/*N*/                   if ( nFldScriptType == i18n::ScriptType::WEAK )
/*N*/                   {
/*?*/                       nFldScriptType = nTmpType;
/*?*/                       aText.SetChar( pField->GetStart(), aFldText.getStr()[nCharInField] );
/*N*/                   }
/*N*/
/*N*/                   // ...  but if the first one is LATIN, and there are CJK or CTL chars too,
/*N*/                   // we prefer that ScripType because we need an other font.
/*N*/                   if ( ( nTmpType == i18n::ScriptType::ASIAN ) || ( nTmpType == i18n::ScriptType::COMPLEX ) )
/*N*/                   {
/*?*/                       aText.SetChar( pField->GetStart(), aFldText.getStr()[nCharInField] );
/*?*/                       break;
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/           pField = pNode->GetCharAttribs().FindNextAttrib( EE_FEATURE_FIELD, pField->GetEnd() );
/*N*/       }
/*N*/
/*N*/       ::rtl::OUString aOUText( aText );
/*N*/       USHORT nTextLen = (USHORT)aOUText.getLength();
/*N*/
/*N*/       long nPos = 0;
/*N*/       short nScriptType = xBI->getScriptType( aOUText, nPos );
/*N*/       rTypes.Insert( ScriptTypePosInfo( nScriptType, (USHORT)nPos, nTextLen ), rTypes.Count() );
/*N*/       nPos = xBI->endOfScript( aOUText, nPos, nScriptType );
/*N*/       while ( ( nPos != (-1) ) && ( nPos < nTextLen ) )
/*N*/       {
/*N*/           rTypes[rTypes.Count()-1].nEndPos = (USHORT)nPos;
/*N*/
/*N*/             nScriptType = xBI->getScriptType( aOUText, nPos );
/*N*/           long nEndPos = xBI->endOfScript( aOUText, nPos, nScriptType );
/*N*/
/*N*/             // #96850# Handle blanks as weak, remove if BreakIterator returns WEAK for spaces.
/*N*/           if ( ( nScriptType == i18n::ScriptType::LATIN ) && ( aOUText.getStr()[ nPos ] == 0x20 ) )
/*N*/             {
/*?*/                 BOOL bOnlySpaces = TRUE;
/*?*/                 for ( USHORT n = nPos+1; ( n < nEndPos ) && bOnlySpaces; n++ )
/*?*/                 {
/*?*/                     if ( aOUText.getStr()[ n ] != 0x20 )
/*?*/                         bOnlySpaces = FALSE;
/*?*/                 }
/*?*/                 if ( bOnlySpaces )
/*?*/                     nScriptType = i18n::ScriptType::WEAK;
/*N*/             }
/*N*/
/*N*/             if ( ( nScriptType == i18n::ScriptType::WEAK ) || ( nScriptType == rTypes[rTypes.Count()-1].nScriptType ) )
/*N*/             {
/*?*/                 // Expand last ScriptTypePosInfo, don't create weak or unecessary portions
/*?*/                 rTypes[rTypes.Count()-1].nEndPos = (USHORT)nEndPos;
/*N*/             }
/*N*/             else
/*N*/             {
/*N*/               rTypes.Insert( ScriptTypePosInfo( nScriptType, (USHORT)nPos, nTextLen ), rTypes.Count() );
/*N*/             }
/*N*/
/*N*/           nPos = nEndPos;
/*N*/       }
/*N*/
/*N*/       if ( rTypes[0].nScriptType == i18n::ScriptType::WEAK )
/*N*/           rTypes[0].nScriptType = ( rTypes.Count() > 1 ) ? rTypes[1].nScriptType : GetI18NScriptTypeOfLanguage( GetDefaultLanguage() );
/*N*/   }
/*N*/ }

/*N*/ USHORT ImpEditEngine::GetScriptType( const EditPaM& rPaM, USHORT* pEndPos ) const
/*N*/ {
/*N*/   USHORT nScriptType = 0;
/*N*/
/*N*/   if ( pEndPos )
/*?*/       *pEndPos = rPaM.GetNode()->Len();
/*N*/
/*N*/   if ( rPaM.GetNode()->Len() )
/*N*/   {
/*N*/       USHORT nPara = GetEditDoc().GetPos( rPaM.GetNode() );
/*N*/       ParaPortion* pParaPortion = GetParaPortions().SaveGetObject( nPara );
/*N*/       if ( !pParaPortion->aScriptInfos.Count() )
/*?*/           ((ImpEditEngine*)this)->InitScriptTypes( nPara );
/*N*/
/*N*/       ScriptTypePosInfos& rTypes = pParaPortion->aScriptInfos;
/*N*/       USHORT nPos = rPaM.GetIndex();
/*N*/       for ( USHORT n = 0; n < rTypes.Count(); n++ )
/*N*/       {
/*N*/           if ( ( rTypes[n].nStartPos <= nPos ) && ( rTypes[n].nEndPos >= nPos ) )
/*N*/           {
/*N*/               nScriptType = rTypes[n].nScriptType;
/*N*/               if( pEndPos )
/*?*/                   *pEndPos = rTypes[n].nEndPos;
/*N*/               break;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return nScriptType ? nScriptType : GetI18NScriptTypeOfLanguage( GetDefaultLanguage() );
/*N*/ }

/*N*/ USHORT ImpEditEngine::GetScriptType( const EditSelection& rSel ) const
/*N*/ {
/*N*/   EditSelection aSel( rSel );
/*N*/   aSel.Adjust( aEditDoc );
/*N*/
/*N*/   short nScriptType = 0;
/*N*/
/*N*/   USHORT nStartPara = GetEditDoc().GetPos( aSel.Min().GetNode() );
/*N*/   USHORT nEndPara = GetEditDoc().GetPos( aSel.Max().GetNode() );
/*N*/
/*N*/   for ( USHORT nPara = nStartPara; nPara <= nEndPara; nPara++ )
/*N*/   {
/*N*/       ParaPortion* pParaPortion = GetParaPortions().SaveGetObject( nPara );
/*N*/       if ( !pParaPortion->aScriptInfos.Count() )
/*N*/           ((ImpEditEngine*)this)->InitScriptTypes( nPara );
/*N*/
/*N*/       ScriptTypePosInfos& rTypes = pParaPortion->aScriptInfos;
/*N*/
/*N*/       USHORT nS = ( nPara == nStartPara ) ? aSel.Min().GetIndex() : 0;
/*N*/       USHORT nE = ( nPara == nEndPara ) ? aSel.Max().GetIndex() : pParaPortion->GetNode()->Len();
/*N*/       for ( USHORT n = 0; n < rTypes.Count(); n++ )
/*N*/       {
/*N*/           if ( ( rTypes[n].nStartPos <= nE ) && ( rTypes[n].nEndPos >= nS ) )
/*N*/           {
/*N*/               if ( rTypes[n].nScriptType != i18n::ScriptType::WEAK )
/*N*/               {
/*N*/                     nScriptType |= GetItemScriptType ( rTypes[n].nScriptType );
/*N*/                 }
/*N*/                 else
/*N*/               {
/*?*/                     if ( !nScriptType && n )
/*?*/                     {
/*?*/                         // #93548# When starting with WEAK, use prev ScriptType...
/*?*/                         nScriptType = rTypes[n-1].nScriptType;
/*N*/                     }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return nScriptType ? nScriptType : GetI18NScriptTypeOfLanguage( GetDefaultLanguage() );
/*N*/ }

/*N*/ BOOL ImpEditEngine::IsScriptChange( const EditPaM& rPaM ) const
/*N*/ {
/*N*/   BOOL bScriptChange = FALSE;
/*N*/
/*N*/   if ( rPaM.GetNode()->Len() )
/*N*/   {
/*N*/       USHORT nPara = GetEditDoc().GetPos( rPaM.GetNode() );
/*N*/       ParaPortion* pParaPortion = GetParaPortions().SaveGetObject( nPara );
/*N*/       if ( !pParaPortion->aScriptInfos.Count() )
/*?*/           ((ImpEditEngine*)this)->InitScriptTypes( nPara );
/*N*/
/*N*/       ScriptTypePosInfos& rTypes = pParaPortion->aScriptInfos;
/*N*/       USHORT nPos = rPaM.GetIndex();
/*N*/       for ( USHORT n = 0; n < rTypes.Count(); n++ )
/*N*/       {
/*N*/           if ( rTypes[n].nStartPos == nPos )
/*N*/           {
/*N*/               bScriptChange = TRUE;
/*N*/               break;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return bScriptChange;
/*N*/ }

/*N*/ BOOL ImpEditEngine::HasScriptType( USHORT nPara, USHORT nType ) const
/*N*/ {
/*N*/     BOOL bTypeFound = FALSE;
/*N*/
/*N*/   ParaPortion* pParaPortion = GetParaPortions().SaveGetObject( nPara );
/*N*/   if ( !pParaPortion->aScriptInfos.Count() )
/*N*/       ((ImpEditEngine*)this)->InitScriptTypes( nPara );
/*N*/
/*N*/     ScriptTypePosInfos& rTypes = pParaPortion->aScriptInfos;
/*N*/   for ( USHORT n = rTypes.Count(); n && !bTypeFound; )
/*N*/   {
/*N*/       if ( rTypes[--n].nScriptType == nType )
/*N*/                 bTypeFound = TRUE;
/*N*/     }
/*N*/     return bTypeFound;
/*N*/ }

/*N*/ void ImpEditEngine::InitWritingDirections( USHORT nPara )
/*N*/ {
/*N*/   ParaPortion* pParaPortion = GetParaPortions().SaveGetObject( nPara );
/*N*/   WritingDirectionInfos& rInfos = pParaPortion->aWritingDirectionInfos;
/*N*/   rInfos.Remove( 0, rInfos.Count() );
/*N*/
/*N*/     BOOL bCTL = FALSE;
/*N*/   ScriptTypePosInfos& rTypes = pParaPortion->aScriptInfos;
/*N*/   for ( USHORT n = 0; n < rTypes.Count(); n++ )
/*N*/   {
/*N*/       if ( rTypes[n].nScriptType == i18n::ScriptType::COMPLEX )
/*N*/       {
/*N*/           bCTL = TRUE;
/*N*/           break;
/*N*/       }
/*N*/   }
/*N*/
/*N*/     const BYTE nDefaultDir = IsRightToLeft( nPara ) ? UBIDI_RTL : UBIDI_LTR;
/*N*/   if ( ( bCTL || ( nDefaultDir == UBIDI_RTL ) ) && pParaPortion->GetNode()->Len() )
/*N*/   {
/*?*/
/*?*/         String aText( *pParaPortion->GetNode() );
/*?*/
/*?*/         //
/*?*/         // Bidi functions from icu 2.0
/*?*/         //
/*?*/         UErrorCode nError = U_ZERO_ERROR;
/*?*/         UBiDi* pBidi = ubidi_openSized( aText.Len(), 0, &nError );
/*?*/         nError = U_ZERO_ERROR;
/*?*/
/*?*/         ubidi_setPara( pBidi, aText.GetBuffer(), aText.Len(), nDefaultDir, NULL, &nError );
/*?*/         nError = U_ZERO_ERROR;
/*?*/
/*?*/         long nCount = ubidi_countRuns( pBidi, &nError );
/*?*/
/*?*/         UTextOffset nStart = 0;
/*?*/         UTextOffset nEnd;
/*?*/         UBiDiLevel nCurrDir;
/*?*/
/*?*/         for ( USHORT nIdx = 0; nIdx < nCount; ++nIdx )
/*?*/         {
/*?*/             ubidi_getLogicalRun( pBidi, nStart, &nEnd, &nCurrDir );
/*?*/             rInfos.Insert( WritingDirectionInfo( nCurrDir, (USHORT)nStart, (USHORT)nEnd ), rInfos.Count() );
/*?*/             nStart = nEnd;
/*?*/         }
/*?*/
/*?*/         ubidi_close( pBidi );
/*N*/   }
/*N*/
/*N*/     // No infos mean no CTL and default dir is L2R...
/*N*/     if ( !rInfos.Count() )
/*N*/         rInfos.Insert( WritingDirectionInfo( 0, 0, (USHORT)pParaPortion->GetNode()->Len() ), rInfos.Count() );
/*N*/
/*N*/ }

/*N*/ BOOL ImpEditEngine::IsRightToLeft( USHORT nPara ) const
/*N*/ {
/*N*/     BOOL bR2L = FALSE;
/*N*/     const SvxFrameDirectionItem* pFrameDirItem = NULL;
/*N*/
/*N*/     if ( !IsVertical() )
/*N*/     {
/*N*/         bR2L = GetDefaultHorizontalTextDirection() == EE_HTEXTDIR_R2L;
/*N*/         pFrameDirItem = &(const SvxFrameDirectionItem&)GetParaAttrib( nPara, EE_PARA_WRITINGDIR );
/*N*/         if ( pFrameDirItem->GetValue() == FRMDIR_ENVIRONMENT )
/*N*/         {
/*N*/             // #103045# if DefaultHorizontalTextDirection is set, use that value, otherwise pool default.
/*N*/             if ( GetDefaultHorizontalTextDirection() != EE_HTEXTDIR_DEFAULT )
/*N*/             {
/*?*/                 pFrameDirItem = NULL; // bR2L allready set to default horizontal text direction
/*N*/             }
/*N*/             else
/*N*/             {
/*N*/                 // Use pool default
/*N*/                 pFrameDirItem = &(const SvxFrameDirectionItem&)((ImpEditEngine*)this)->GetEmptyItemSet().Get( EE_PARA_WRITINGDIR );
/*N*/             }
/*N*/         }
/*N*/     }
/*N*/
/*N*/     if ( pFrameDirItem )
/*N*/         bR2L = pFrameDirItem->GetValue() == FRMDIR_HORI_RIGHT_TOP;
/*N*/
/*N*/     return bR2L;
/*N*/ }

//STRIP001 BOOL ImpEditEngine::HasDifferentRTLLevels( const ContentNode* pNode )
//STRIP001 {
//STRIP001     USHORT nPara = GetEditDoc().GetPos( (ContentNode*)pNode );
//STRIP001  ParaPortion* pParaPortion = GetParaPortions().SaveGetObject( nPara );
//STRIP001
//STRIP001     BOOL bHasDifferentRTLLevels = FALSE;
//STRIP001
//STRIP001     USHORT nRTLLevel = IsRightToLeft( nPara ) ? 1 : 0;
//STRIP001  for ( USHORT n = 0; n < pParaPortion->GetTextPortions().Count(); n++ )
//STRIP001  {
//STRIP001      TextPortion* pTextPortion = pParaPortion->GetTextPortions().GetObject( n );
//STRIP001         if ( pTextPortion->GetRightToLeft() != nRTLLevel )
//STRIP001         {
//STRIP001             bHasDifferentRTLLevels = TRUE;
//STRIP001             break;
//STRIP001         }
//STRIP001  }
//STRIP001     return bHasDifferentRTLLevels;
//STRIP001 }


/*N*/ BYTE ImpEditEngine::GetRightToLeft( USHORT nPara, USHORT nPos, USHORT* pStart, USHORT* pEnd )
/*N*/ {
/*N*/ //    BYTE nRightToLeft = IsRightToLeft( nPara ) ? 1 : 0;
/*N*/     BYTE nRightToLeft = 0;
/*N*/
/*N*/     ContentNode* pNode = aEditDoc.SaveGetObject( nPara );
/*N*/     if ( pNode && pNode->Len() )
/*N*/     {
/*N*/       ParaPortion* pParaPortion = GetParaPortions().SaveGetObject( nPara );
/*N*/       if ( !pParaPortion->aWritingDirectionInfos.Count() )
/*N*/           InitWritingDirections( nPara );
/*N*/
/*N*/         BYTE nType = 0;
/*N*/       WritingDirectionInfos& rDirInfos = pParaPortion->aWritingDirectionInfos;
/*N*/       for ( USHORT n = 0; n < rDirInfos.Count(); n++ )
/*N*/       {
/*N*/           if ( ( rDirInfos[n].nStartPos <= nPos ) && ( rDirInfos[n].nEndPos >= nPos ) )
/*N*/           {
/*N*/               nRightToLeft = rDirInfos[n].nType;
/*N*/                 if ( pStart )
/*?*/                     *pStart = rDirInfos[n].nStartPos;
/*N*/                 if ( pEnd )
/*?*/                     *pEnd = rDirInfos[n].nEndPos;
/*N*/               break;
/*N*/           }
/*N*/       }
/*N*/     }
/*N*/     return nRightToLeft;
/*N*/ }

/*N*/ SvxAdjust ImpEditEngine::GetJustification( USHORT nPara ) const
/*N*/ {
/*N*/   SvxAdjust eJustification = SVX_ADJUST_LEFT;
/*N*/
/*N*/     if ( !aStatus.IsOutliner() )
/*N*/     {
/*N*/       eJustification = ((const SvxAdjustItem&) GetParaAttrib( nPara, EE_PARA_JUST )).GetAdjust();
/*N*/
/*N*/         if ( IsRightToLeft( nPara ) )
/*N*/         {
/*?*/             if ( eJustification == SVX_ADJUST_LEFT )
/*?*/                 eJustification = SVX_ADJUST_RIGHT;
/*?*/             else if ( eJustification == SVX_ADJUST_RIGHT )
/*?*/                 eJustification = SVX_ADJUST_LEFT;
/*N*/         }
/*N*/     }
/*N*/     return eJustification;
/*N*/ }


//  ----------------------------------------------------------------------
//  Textaenderung
//  ----------------------------------------------------------------------

/*N*/ void ImpEditEngine::ImpRemoveChars( const EditPaM& rPaM, USHORT nChars, EditUndoRemoveChars* pCurUndo )
/*N*/ {
/*N*/   if ( IsUndoEnabled() && !IsInUndo() )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 XubString aStr( rPaM.GetNode()->Copy( rPaM.GetIndex(), nChars ) );
//STRIP001 /*?*/
//STRIP001 /*?*/        // Pruefen, ob Attribute geloescht oder geaendert werden:
//STRIP001 /*?*/        USHORT nStart = rPaM.GetIndex();
//STRIP001 /*?*/        USHORT nEnd = nStart + nChars;
//STRIP001 /*?*/        CharAttribArray& rAttribs = rPaM.GetNode()->GetCharAttribs().GetAttribs();
//STRIP001 /*?*/        USHORT nAttrs = rAttribs.Count();
//STRIP001 /*?*/        for ( USHORT nAttr = 0; nAttr < rAttribs.Count(); nAttr++ )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            EditCharAttrib* pAttr = rAttribs[nAttr];
//STRIP001 /*?*/            if ( ( pAttr->GetEnd() >= nStart ) && ( pAttr->GetStart() < nEnd ) )
//STRIP001 /*?*/            {
//STRIP001 /*?*/ #ifndef SVX_LIGHT
//STRIP001 /*?*/                EditSelection aSel( rPaM );
//STRIP001 /*?*/                aSel.Max().GetIndex() += nChars;
//STRIP001 /*?*/                EditUndoSetAttribs* pAttrUndo = CreateAttribUndo( aSel, GetEmptyItemSet() );
//STRIP001 /*?*/                InsertUndo( pAttrUndo );
//STRIP001 /*?*/ #endif
//STRIP001 /*?*/                break;  // for
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
//STRIP001 /*?*/        if ( pCurUndo && ( CreateEditPaM( pCurUndo->GetEPaM() ) == rPaM ) )
//STRIP001 /*?*/            pCurUndo->GetStr() += aStr;
//STRIP001 /*?*/ #ifndef SVX_LIGHT
//STRIP001 /*?*/        else
//STRIP001 /*?*/            InsertUndo( new EditUndoRemoveChars( this, CreateEPaM( rPaM ), aStr ) );
//STRIP001 /*?*/ #endif
/*N*/   }
/*N*/
/*N*/   aEditDoc.RemoveChars( rPaM, nChars );
/*N*/   TextModified();
/*N*/ }

//STRIP001 EditSelection ImpEditEngine::ImpMoveParagraphs( Range aOldPositions, USHORT nNewPos )
//STRIP001 {
//STRIP001  aOldPositions.Justify();
//STRIP001  BOOL bValidAction = ( (long)nNewPos < aOldPositions.Min() ) || ( (long)nNewPos > aOldPositions.Max() );
//STRIP001  DBG_ASSERT( bValidAction, "Move in sich selbst ?" );
//STRIP001  DBG_ASSERT( aOldPositions.Max() <= (long)GetParaPortions().Count(), "Voll drueber weg: MoveParagraphs" );
//STRIP001
//STRIP001  EditSelection aSelection;
//STRIP001
//STRIP001  if ( !bValidAction )
//STRIP001  {
//STRIP001      aSelection = aEditDoc.GetStartPaM();
//STRIP001      return aSelection;
//STRIP001  }
//STRIP001
//STRIP001  ULONG nParaCount = GetParaPortions().Count();
//STRIP001
//STRIP001  if ( nNewPos >= nParaCount )
//STRIP001      nNewPos = GetParaPortions().Count();
//STRIP001
//STRIP001  // Height may change when moving first or last Paragraph
//STRIP001  ParaPortion* pRecalc1 = NULL;
//STRIP001  ParaPortion* pRecalc2 = NULL;
//STRIP001  ParaPortion* pRecalc3 = NULL;
//STRIP001  ParaPortion* pRecalc4 = NULL;
//STRIP001
//STRIP001  if ( nNewPos == 0 ) // Move to Start
//STRIP001  {
//STRIP001      pRecalc1 = GetParaPortions().GetObject( 0 );
//STRIP001      pRecalc2 = GetParaPortions().GetObject( (USHORT)aOldPositions.Min() );
//STRIP001
//STRIP001  }
//STRIP001  else if ( nNewPos == nParaCount )
//STRIP001  {
//STRIP001      pRecalc1 = GetParaPortions().GetObject( (USHORT)(nParaCount-1) );
//STRIP001      pRecalc2 = GetParaPortions().GetObject( (USHORT)aOldPositions.Max() );
//STRIP001  }
//STRIP001
//STRIP001  if ( aOldPositions.Min() == 0 ) // Move from Start
//STRIP001  {
//STRIP001      pRecalc3 = GetParaPortions().GetObject( 0 );
//STRIP001      pRecalc4 = GetParaPortions().GetObject( aOldPositions.Max()+1 );
//STRIP001  }
//STRIP001  else if ( (USHORT)aOldPositions.Max() == (nParaCount-1) )
//STRIP001  {
//STRIP001      pRecalc3 = GetParaPortions().GetObject( (USHORT)aOldPositions.Max() );
//STRIP001      pRecalc4 = GetParaPortions().GetObject( (USHORT)(aOldPositions.Min()-1) );
//STRIP001  }
//STRIP001
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  if ( IsUndoEnabled() && !IsInUndo())
//STRIP001      InsertUndo( new EditUndoMoveParagraphs( this, aOldPositions, nNewPos ) );
//STRIP001 #endif
//STRIP001
//STRIP001     MoveParagraphsInfo aMoveParagraphsInfo( aOldPositions.Min(), aOldPositions.Max(), nNewPos );
//STRIP001     aBeginMovingParagraphsHdl.Call( &aMoveParagraphsInfo );
//STRIP001
//STRIP001  // Position nicht aus dem Auge verlieren!
//STRIP001  ParaPortion* pDestPortion = GetParaPortions().SaveGetObject( nNewPos );
//STRIP001
//STRIP001  ParaPortionList aTmpPortionList;
//STRIP001  USHORT i;
//STRIP001  for ( i = (USHORT)aOldPositions.Min(); i <= (USHORT)aOldPositions.Max(); i++  )
//STRIP001  {
//STRIP001      // Immer aOldPositions.Min(), da Remove().
//STRIP001      ParaPortion* pTmpPortion = GetParaPortions().GetObject( (USHORT)aOldPositions.Min() );
//STRIP001      GetParaPortions().Remove( (USHORT)aOldPositions.Min() );
//STRIP001      aEditDoc.Remove( (USHORT)aOldPositions.Min() );
//STRIP001      aTmpPortionList.Insert( pTmpPortion, aTmpPortionList.Count() );
//STRIP001  }
//STRIP001
//STRIP001  USHORT nRealNewPos = pDestPortion ? GetParaPortions().GetPos( pDestPortion ) : GetParaPortions().Count();
//STRIP001  DBG_ASSERT( nRealNewPos != USHRT_MAX, "ImpMoveParagraphs: Ungueltige Position!" );
//STRIP001
//STRIP001  for ( i = 0; i < (USHORT)aTmpPortionList.Count(); i++  )
//STRIP001  {
//STRIP001      ParaPortion* pTmpPortion = aTmpPortionList.GetObject( i );
//STRIP001      if ( i == 0 )
//STRIP001          aSelection.Min().SetNode( pTmpPortion->GetNode() );
//STRIP001
//STRIP001      aSelection.Max().SetNode( pTmpPortion->GetNode() );
//STRIP001      aSelection.Max().SetIndex( pTmpPortion->GetNode()->Len() );
//STRIP001
//STRIP001      ContentNode* pN = pTmpPortion->GetNode();
//STRIP001      aEditDoc.Insert( pN, nRealNewPos+i );
//STRIP001
//STRIP001      GetParaPortions().Insert( pTmpPortion, nRealNewPos+i );
//STRIP001  }
//STRIP001
//STRIP001     aEndMovingParagraphsHdl.Call( &aMoveParagraphsInfo );
//STRIP001
//STRIP001     if ( GetNotifyHdl().IsSet() )
//STRIP001     {
//STRIP001         EENotify aNotify( EE_NOTIFY_PARAGRAPHSMOVED );
//STRIP001         aNotify.pEditEngine = GetEditEnginePtr();
//STRIP001         aNotify.nParagraph = nNewPos;
//STRIP001         aNotify.nParam1 = aOldPositions.Min();
//STRIP001         aNotify.nParam2 = aOldPositions.Max();
//STRIP001         CallNotify( aNotify );
//STRIP001     }
//STRIP001
//STRIP001  aEditDoc.SetModified( TRUE );
//STRIP001
//STRIP001  if ( pRecalc1 )
//STRIP001      CalcHeight( pRecalc1 );
//STRIP001  if ( pRecalc2 )
//STRIP001      CalcHeight( pRecalc2 );
//STRIP001  if ( pRecalc3 )
//STRIP001      CalcHeight( pRecalc3 );
//STRIP001  if ( pRecalc4 )
//STRIP001      CalcHeight( pRecalc4 );
//STRIP001
//STRIP001  aTmpPortionList.Remove( 0, aTmpPortionList.Count() );   // wichtig !
//STRIP001
//STRIP001 #ifdef EDITDEBUG
//STRIP001  GetParaPortions().DbgCheck(aEditDoc);
//STRIP001 #endif
//STRIP001  return aSelection;
//STRIP001 }


/*N*/ EditPaM ImpEditEngine::ImpConnectParagraphs( ContentNode* pLeft, ContentNode* pRight, BOOL bBackward )
/*N*/ {
/*N*/   DBG_ASSERT( pLeft != pRight, "Den gleichen Absatz zusammenfuegen ?" );
/*N*/   DBG_ASSERT( aEditDoc.GetPos( pLeft ) != USHRT_MAX, "Einzufuegenden Node nicht gefunden(1)" );
/*N*/   DBG_ASSERT( aEditDoc.GetPos( pRight ) != USHRT_MAX, "Einzufuegenden Node nicht gefunden(2)" );
/*N*/
/*N*/   USHORT nParagraphTobeDeleted = aEditDoc.GetPos( pRight );
/*N*/   DeletedNodeInfo* pInf = new DeletedNodeInfo( (ULONG)pRight, nParagraphTobeDeleted );
/*N*/   aDeletedNodes.Insert( pInf, aDeletedNodes.Count() );
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/   if ( IsUndoEnabled() && !IsInUndo() )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 InsertUndo( new EditUndoConnectParas( this,
//STRIP001 /*?*/            aEditDoc.GetPos( pLeft ), pLeft->Len(),
//STRIP001 /*?*/            pLeft->GetContentAttribs().GetItems(), pRight->GetContentAttribs().GetItems(),
//STRIP001 /*?*/            pLeft->GetStyleSheet(), pRight->GetStyleSheet(), bBackward ) );
/*N*/   }
/*N*/ #endif
/*N*/
/*N*/   if ( bBackward )
/*N*/   {
/*?*/       pLeft->SetStyleSheet( pRight->GetStyleSheet(), TRUE );
/*?*/       pLeft->GetContentAttribs().GetItems().Set( pRight->GetContentAttribs().GetItems() );
/*?*/       pLeft->GetCharAttribs().GetDefFont() = pRight->GetCharAttribs().GetDefFont();
/*N*/   }
/*N*/
/*N*/   ParaAttribsChanged( pLeft );
/*N*/
/*N*/   // Erstmal Portions suchen, da pRight nach ConnectParagraphs weg.
/*N*/   ParaPortion* pLeftPortion = FindParaPortion( pLeft );
/*N*/   ParaPortion* pRightPortion = FindParaPortion( pRight );
/*N*/   DBG_ASSERT( pLeftPortion, "Blinde Portion in ImpConnectParagraphs(1)" );
/*N*/   DBG_ASSERT( pRightPortion, "Blinde Portion in ImpConnectParagraphs(2)" );
/*N*/   DBG_ASSERT( nParagraphTobeDeleted == GetParaPortions().GetPos( pRightPortion ), "NodePos != PortionPos?" );
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/   if ( GetStatus().DoOnlineSpelling() )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 xub_StrLen nEnd = pLeft->Len();
//STRIP001 /*?*/        xub_StrLen nInv = nEnd ? nEnd-1 : nEnd;
//STRIP001 /*?*/        pLeft->GetWrongList()->ClearWrongs( nInv, 0xFFFF, pLeft );  // Evtl. einen wegnehmen
//STRIP001 /*?*/        pLeft->GetWrongList()->MarkInvalid( nInv, nEnd+1 );
//STRIP001 /*?*/        // Falschgeschriebene Woerter ruebernehmen:
//STRIP001 /*?*/        USHORT nRWrongs = pRight->GetWrongList()->Count();
//STRIP001 /*?*/        for ( USHORT nW = 0; nW < nRWrongs; nW++ )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            WrongRange aWrong = pRight->GetWrongList()->GetObject( nW );
//STRIP001 /*?*/            if ( aWrong.nStart != 0 )   // Nicht ein anschliessender
//STRIP001 /*?*/            {
//STRIP001 /*?*/                aWrong.nStart += nEnd;
//STRIP001 /*?*/                aWrong.nEnd += nEnd;
//STRIP001 /*?*/                pLeft->GetWrongList()->InsertWrong( aWrong, pLeft->GetWrongList()->Count() );
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
/*N*/   }
/*N*/ #endif
/*N*/
/*N*/   if ( IsCallParaInsertedOrDeleted() )
/*N*/       GetEditEnginePtr()->ParagraphDeleted( nParagraphTobeDeleted );
/*N*/
/*N*/   EditPaM aPaM = aEditDoc.ConnectParagraphs( pLeft, pRight );
/*N*/   GetParaPortions().Remove( nParagraphTobeDeleted );
/*N*/   delete pRightPortion;
/*N*/
/*N*/   pLeftPortion->MarkSelectionInvalid( aPaM.GetIndex(), pLeft->Len() );
/*N*/
/*N*/   // der rechte Node wird von EditDoc::ConnectParagraphs() geloescht.
/*N*/
/*N*/   if ( GetTextRanger() )
/*N*/   {
/*?*/       // Durch das zusammenfuegen wird der linke zwar neu formatiert, aber
/*?*/       // wenn sich dessen Hoehe nicht aendert bekommt die Formatierung die
/*?*/       // Aenderung der Gesaamthoehe des Textes zu spaet mit...
/*?*/       for ( USHORT n = nParagraphTobeDeleted; n < GetParaPortions().Count(); n++ )
/*?*/       {
/*?*/           ParaPortion* pPP = GetParaPortions().GetObject( n );
/*?*/           pPP->MarkSelectionInvalid( 0, pPP->GetNode()->Len() );
/*?*/           pPP->GetLines().Reset();
/*?*/       }
/*N*/   }
/*N*/
/*N*/   TextModified();
/*N*/
/*N*/   return aPaM;
/*N*/ }

//STRIP001 EditPaM ImpEditEngine::DeleteLeftOrRight( const EditSelection& rSel, BYTE nMode, BYTE nDelMode )
//STRIP001 {
//STRIP001  DBG_ASSERT( !EditSelection( rSel ).DbgIsBuggy( aEditDoc ), "Index im Wald in DeleteLeftOrRight" )
//STRIP001
//STRIP001  if ( rSel.HasRange() )  // dann nur Sel. loeschen
//STRIP001      return ImpDeleteSelection( rSel );
//STRIP001
//STRIP001  const EditPaM aCurPos( rSel.Max() );
//STRIP001  EditPaM aDelStart( aCurPos );
//STRIP001  EditPaM aDelEnd( aCurPos );
//STRIP001  if ( nMode == DEL_LEFT )
//STRIP001  {
//STRIP001      if ( nDelMode == DELMODE_SIMPLE )
//STRIP001      {
//STRIP001          aDelStart = CursorLeft( aCurPos, i18n::CharacterIteratorMode::SKIPCHARACTER );
//STRIP001      }
//STRIP001      else if ( nDelMode == DELMODE_RESTOFWORD )
//STRIP001      {
//STRIP001          aDelStart = StartOfWord( aCurPos );
//STRIP001          if ( aDelStart.GetIndex() == aCurPos.GetIndex() )
//STRIP001              aDelStart = WordLeft( aCurPos );
//STRIP001      }
//STRIP001      else    // DELMODE_RESTOFCONTENT
//STRIP001      {
//STRIP001          aDelStart.SetIndex( 0 );
//STRIP001          if ( aDelStart == aCurPos )
//STRIP001          {
//STRIP001              // kompletter Absatz davor
//STRIP001              ContentNode* pPrev = GetPrevVisNode( aCurPos.GetNode() );
//STRIP001              if ( pPrev )
//STRIP001                  aDelStart = EditPaM( pPrev, 0 );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if ( nDelMode == DELMODE_SIMPLE )
//STRIP001      {
//STRIP001          aDelEnd = CursorRight( aCurPos );
//STRIP001      }
//STRIP001      else if ( nDelMode == DELMODE_RESTOFWORD )
//STRIP001      {
//STRIP001          aDelEnd = EndOfWord( aCurPos );
//STRIP001          if ( aDelEnd.GetIndex() == aCurPos.GetIndex() )
//STRIP001              aDelEnd = WordLeft( aCurPos );
//STRIP001      }
//STRIP001      else    // DELMODE_RESTOFCONTENT
//STRIP001      {
//STRIP001          aDelEnd.SetIndex( aCurPos.GetNode()->Len() );
//STRIP001          if ( aDelEnd == aCurPos )
//STRIP001          {
//STRIP001              // kompletter Absatz dahinter
//STRIP001              ContentNode* pNext = GetNextVisNode( aCurPos.GetNode() );
//STRIP001              if ( pNext )
//STRIP001                  aDelEnd = EditPaM( pNext, pNext->Len() );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Bei DELMODE_RESTOFCONTENT reicht bei verschiedenen Nodes
//STRIP001  // kein ConnectParagraphs.
//STRIP001  if ( ( nDelMode == DELMODE_RESTOFCONTENT ) || ( aDelStart.GetNode() == aDelEnd.GetNode() ) )
//STRIP001      return ImpDeleteSelection( EditSelection( aDelStart, aDelEnd ) );
//STRIP001
//STRIP001  // Jetzt entscheiden, ob noch Selektion loeschen (RESTOFCONTENTS)
//STRIP001  BOOL bSpecialBackward = ( ( nMode == DEL_LEFT ) && ( nDelMode == DELMODE_SIMPLE ) )
//STRIP001                              ? TRUE : FALSE;
//STRIP001  if ( aStatus.IsAnyOutliner() )
//STRIP001      bSpecialBackward = FALSE;
//STRIP001
//STRIP001  return ImpConnectParagraphs( aDelStart.GetNode(), aDelEnd.GetNode(), bSpecialBackward );
//STRIP001 }

/*N*/ EditPaM ImpEditEngine::ImpDeleteSelection( EditSelection aSel )
/*N*/ {
/*N*/   if ( !aSel.HasRange() )
/*?*/       return aSel.Min();
/*N*/
/*N*/   aSel.Adjust( aEditDoc );
/*N*/   EditPaM aStartPaM( aSel.Min() );
/*N*/   EditPaM aEndPaM( aSel.Max() );
/*N*/
/*N*/   CursorMoved( aStartPaM.GetNode() ); // nur damit neu eingestellte Attribute verschwinden...
/*N*/   CursorMoved( aEndPaM.GetNode() );   // nur damit neu eingestellte Attribute verschwinden...
/*N*/
/*N*/   DBG_ASSERT( aStartPaM.GetIndex() <= aStartPaM.GetNode()->Len(), "Index im Wald in ImpDeleteSelection" )
/*N*/   DBG_ASSERT( aEndPaM.GetIndex() <= aEndPaM.GetNode()->Len(), "Index im Wald in ImpDeleteSelection" )
/*N*/
/*N*/   USHORT nStartNode = aEditDoc.GetPos( aStartPaM.GetNode() );
/*N*/   USHORT nEndNode = aEditDoc.GetPos( aEndPaM.GetNode() );
/*N*/
/*N*/   DBG_ASSERT( nEndNode != USHRT_MAX, "Start > End ?!" );
/*N*/   DBG_ASSERT( nStartNode <= nEndNode, "Start > End ?!" );
/*N*/
/*N*/   // Alle Nodes dazwischen entfernen....
/*N*/   for ( ULONG z = nStartNode+1; z < nEndNode; z++ )
/*N*/   {
/*?*/       // Immer nStartNode+1, wegen Remove()!
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 ImpRemoveParagraph( nStartNode+1 );
/*N*/   }
/*N*/
/*N*/   if ( aStartPaM.GetNode() != aEndPaM.GetNode() )
/*N*/   {
/*N*/       // Den Rest des StartNodes...
/*N*/       USHORT nChars;
/*N*/       nChars = aStartPaM.GetNode()->Len() - aStartPaM.GetIndex();
/*N*/       ImpRemoveChars( aStartPaM, nChars );
/*N*/       ParaPortion* pPortion = FindParaPortion( aStartPaM.GetNode() );
/*N*/       DBG_ASSERT( pPortion, "Blinde Portion in ImpDeleteSelection(3)" );
/*N*/       pPortion->MarkSelectionInvalid( aStartPaM.GetIndex(), aStartPaM.GetNode()->Len() );
/*N*/
/*N*/       // Den Anfang des EndNodes....
/*N*/       nChars = aEndPaM.GetIndex();
/*N*/       aEndPaM.SetIndex( 0 );
/*N*/       ImpRemoveChars( aEndPaM, nChars );
/*N*/       pPortion = FindParaPortion( aEndPaM.GetNode() );
/*N*/       DBG_ASSERT( pPortion, "Blinde Portion in ImpDeleteSelection(4)" );
/*N*/       pPortion->MarkSelectionInvalid( 0, aEndPaM.GetNode()->Len() );
/*N*/       // Zusammenfuegen....
/*N*/       aStartPaM = ImpConnectParagraphs( aStartPaM.GetNode(), aEndPaM.GetNode() );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       USHORT nChars;
/*N*/       nChars = aEndPaM.GetIndex() - aStartPaM.GetIndex();
/*N*/       ImpRemoveChars( aStartPaM, nChars );
/*N*/       ParaPortion* pPortion = FindParaPortion( aStartPaM.GetNode() );
/*N*/       DBG_ASSERT( pPortion, "Blinde Portion in ImpDeleteSelection(5)" );
/*N*/       pPortion->MarkInvalid( aEndPaM.GetIndex(), aStartPaM.GetIndex() - aEndPaM.GetIndex() );
/*N*/   }
/*N*/
/*N*/   UpdateSelections();
/*N*/   TextModified();
/*N*/   return aStartPaM;
/*N*/ }

//STRIP001 void ImpEditEngine::ImpRemoveParagraph( USHORT nPara )
//STRIP001 {
//STRIP001  ContentNode* pNode = aEditDoc.SaveGetObject( nPara );
//STRIP001  ContentNode* pNextNode = aEditDoc.SaveGetObject( nPara+1 );
//STRIP001  ParaPortion* pPortion = GetParaPortions().SaveGetObject( nPara );
//STRIP001
//STRIP001  DBG_ASSERT( pNode, "Blinder Node in ImpRemoveParagraph" );
//STRIP001  DBG_ASSERT( pPortion, "Blinde Portion in ImpRemoveParagraph(2)" );
//STRIP001
//STRIP001  DeletedNodeInfo* pInf = new DeletedNodeInfo( (ULONG)pNode, nPara );
//STRIP001  aDeletedNodes.Insert( pInf, aDeletedNodes.Count() );
//STRIP001
//STRIP001  // Der Node wird vom Undo verwaltet und ggf. zerstoert!
//STRIP001  /* delete */ aEditDoc.Remove( nPara );
//STRIP001  GetParaPortions().Remove( nPara );
//STRIP001  delete pPortion;
//STRIP001
//STRIP001  if ( IsCallParaInsertedOrDeleted() )
//STRIP001  {
//STRIP001      GetEditEnginePtr()->ParagraphDeleted( nPara );
//STRIP001  }
//STRIP001
//STRIP001  // Im folgenden muss ggf. Extra-Space neu ermittelt werden.
//STRIP001  // Bei ParaAttribsChanged wird leider der Absatz neu formatiert,
//STRIP001  // aber diese Methode sollte nicht Zeitkritsch sein!
//STRIP001  if ( pNextNode )
//STRIP001      ParaAttribsChanged( pNextNode );
//STRIP001
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  if ( IsUndoEnabled() && !IsInUndo() )
//STRIP001      InsertUndo( new EditUndoDelContent( this, pNode, nPara ) );
//STRIP001  else
//STRIP001 #endif
//STRIP001  {
//STRIP001      aEditDoc.RemoveItemsFromPool( pNode );
//STRIP001      if ( pNode->GetStyleSheet() )
//STRIP001          EndListening( *pNode->GetStyleSheet(), FALSE );
//STRIP001      delete pNode;
//STRIP001  }
//STRIP001 }

//STRIP001 EditPaM ImpEditEngine::AutoCorrect( const EditSelection& rCurSel, xub_Unicode c, BOOL bOverwrite )
//STRIP001 {
//STRIP001  EditSelection aSel( rCurSel );
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  SvxAutoCorrect* pAutoCorrect = EE_DLL()->GetGlobalData()->GetAutoCorrect();
//STRIP001  if ( pAutoCorrect )
//STRIP001  {
//STRIP001      if ( aSel.HasRange() )
//STRIP001          aSel = ImpDeleteSelection( rCurSel );
//STRIP001      ContentNode* pNode = aSel.Max().GetNode();
//STRIP001      USHORT nIndex = aSel.Max().GetIndex();
//STRIP001      EdtAutoCorrDoc aAuto( this, pNode, nIndex, c );
//STRIP001      pAutoCorrect->AutoCorrect( aAuto, *pNode, nIndex, c, !bOverwrite );
//STRIP001      aSel.Max().SetIndex( aAuto.GetCursor() );
//STRIP001  }
//STRIP001 #endif // !SVX_LIGHT
//STRIP001  return aSel.Max();
//STRIP001 }


/*N*/ EditPaM ImpEditEngine::InsertText( const EditSelection& rCurSel, xub_Unicode c, BOOL bOverwrite )
/*N*/ {
/*N*/   DBG_ASSERT( c != '\t', "Tab bei InsertText ?" );
/*N*/   DBG_ASSERT( c != '\n', "Zeilenumbruch bei InsertText ?" );
/*N*/
/*N*/   EditPaM aPaM( rCurSel.Min() );
/*N*/
/*N*/   BOOL bDoOverwrite = ( bOverwrite &&
/*N*/           ( aPaM.GetIndex() < aPaM.GetNode()->Len() ) ) ? TRUE : FALSE;
/*N*/
/*N*/   BOOL bUndoAction = ( rCurSel.HasRange() || bDoOverwrite );
/*N*/
/*N*/   if ( bUndoAction )
/*?*/       UndoActionStart( EDITUNDO_INSERT );
/*N*/
/*N*/   if ( rCurSel.HasRange() )
/*N*/   {
/*?*/       aPaM = ImpDeleteSelection( rCurSel );
/*N*/   }
/*N*/   else if ( bDoOverwrite )
/*N*/   {
/*?*/       // Wenn Selektion, dann nicht auch noch ein Zeichen ueberschreiben!
/*?*/       EditSelection aTmpSel( aPaM );
/*?*/       aTmpSel.Max().GetIndex()++;
/*?*/       DBG_ASSERT( !aTmpSel.DbgIsBuggy( aEditDoc ), "Overwrite: Fehlerhafte Selektion!" );
/*?*/       ImpDeleteSelection( aTmpSel );
/*N*/   }
/*N*/
/*N*/   if ( aPaM.GetNode()->Len() < MAXCHARSINPARA )
/*N*/   {
/*N*/ #ifndef SVX_LIGHT
/*N*/       if ( IsUndoEnabled() && !IsInUndo() )
/*N*/       {
/*N*/               EditUndoInsertChars* pNewUndo = new EditUndoInsertChars( this, CreateEPaM( aPaM ), c );
/*N*/               BOOL bTryMerge = ( !bDoOverwrite && ( c != ' ' ) ) ? TRUE : FALSE;
/*N*/               InsertUndo( pNewUndo, bTryMerge );
/*N*/       }
/*N*/ #endif
/*N*/
/*N*/       aEditDoc.InsertText( (const EditPaM&)aPaM, c );
/*N*/       ParaPortion* pPortion = FindParaPortion( aPaM.GetNode() );
/*N*/       DBG_ASSERT( pPortion, "Blinde Portion in InsertText" );
/*N*/       pPortion->MarkInvalid( aPaM.GetIndex(), 1 );
/*N*/       aPaM.GetIndex()++;  // macht EditDoc-Methode nicht mehr
/*N*/   }
/*N*/
/*N*/   TextModified();
/*N*/
/*N*/   if ( bUndoAction )
/*?*/       UndoActionEnd( EDITUNDO_INSERT );
/*N*/
/*N*/   return aPaM;
/*N*/ }

/*N*/ EditPaM ImpEditEngine::ImpInsertText( EditSelection aCurSel, const XubString& rStr )
/*N*/ {
/*N*/   EditPaM aPaM;
/*N*/   if ( aCurSel.HasRange() )
/*N*/       aPaM = ImpDeleteSelection( aCurSel );
/*N*/   else
/*N*/       aPaM = aCurSel.Max();
/*N*/
/*N*/   EditPaM aCurPaM( aPaM );    // fuers Invalidieren
/*N*/
/*N*/   XubString aText( rStr );
/*N*/   aText.ConvertLineEnd( LINEEND_LF );
/*N*/   SfxVoidItem aTabItem( EE_FEATURE_TAB );
/*N*/
/*N*/   // Konvertiert nach LineSep = \n
/*N*/   // Token mit LINE_SEP abfragen,
/*N*/   // da der MAC-Compiler aus \n etwas anderes macht!
/*N*/
/*N*/   USHORT nStart = 0;
/*N*/   while ( nStart < aText.Len() )
/*N*/   {
/*N*/       USHORT nEnd = aText.Search( LINE_SEP, nStart );
/*N*/       if ( nEnd == STRING_NOTFOUND )
/*N*/           nEnd = aText.Len(); // nicht dereferenzieren!
/*N*/
/*N*/       // Start == End => Leerzeile
/*N*/       if ( nEnd > nStart )
/*N*/       {
/*N*/           XubString aLine( aText, nStart, nEnd-nStart );
/*N*/           xub_StrLen nChars = aPaM.GetNode()->Len() + aLine.Len();
/*N*/           if ( nChars > MAXCHARSINPARA )
/*N*/           {
/*?*/                 USHORT nMaxNewChars = MAXCHARSINPARA-aPaM.GetNode()->Len();
/*?*/               nEnd -= ( aLine.Len() - nMaxNewChars ); // Dann landen die Zeichen im naechsten Absatz.
/*?*/               aLine.Erase( nMaxNewChars );            // Del Rest...
/*N*/           }
/*N*/ #ifndef SVX_LIGHT
/*N*/           if ( IsUndoEnabled() && !IsInUndo() )
/*N*/               InsertUndo( new EditUndoInsertChars( this, CreateEPaM( aPaM ), aLine ) );
/*N*/ #endif
/*N*/           // Tabs ?
/*N*/           if ( aLine.Search( '\t' ) == STRING_NOTFOUND )
/*N*/               aPaM = aEditDoc.InsertText( aPaM, aLine );
/*N*/           else
/*N*/           {
/*N*/               USHORT nStart2 = 0;
/*N*/               while ( nStart2 < aLine.Len() )
/*N*/               {
/*N*/                   USHORT nEnd2 = aLine.Search( '\t', nStart2 );
/*N*/                   if ( nEnd2 == STRING_NOTFOUND )
/*?*/                       nEnd2 = aLine.Len();    // nicht dereferenzieren!
/*N*/
/*N*/                   if ( nEnd2 > nStart2 )
/*?*/                       aPaM = aEditDoc.InsertText( aPaM, XubString( aLine, nStart2, nEnd2-nStart2 ) );
/*N*/                   if ( nEnd2 < aLine.Len() )
/*N*/                   {
/*N*/                       // aPaM = ImpInsertFeature( EditSelection( aPaM, aPaM ),  );
/*N*/                       aPaM = aEditDoc.InsertFeature( aPaM, aTabItem );
/*N*/                   }
/*N*/                   nStart2 = nEnd2+1;
/*N*/               }
/*N*/           }
/*N*/           ParaPortion* pPortion = FindParaPortion( aPaM.GetNode() );
/*N*/           DBG_ASSERT( pPortion, "Blinde Portion in InsertText" );
/*N*/           pPortion->MarkInvalid( aCurPaM.GetIndex(), aLine.Len() );
/*N*/       }
/*N*/       if ( nEnd < aText.Len() )
/*N*/           aPaM = ImpInsertParaBreak( aPaM );
/*N*/
/*N*/       nStart = nEnd+1;
/*N*/   }
/*N*/
/*N*/   TextModified();
/*N*/   return aPaM;
/*N*/ }

/*N*/ EditPaM ImpEditEngine::ImpFastInsertText( EditPaM aPaM, const XubString& rStr )
/*N*/ {
/*N*/   DBG_ASSERT( rStr.Search( 0x0A ) == STRING_NOTFOUND, "FastInsertText: Zeilentrenner nicht erlaubt!" );
/*N*/   DBG_ASSERT( rStr.Search( 0x0D ) == STRING_NOTFOUND, "FastInsertText: Zeilentrenner nicht erlaubt!" );
/*N*/   DBG_ASSERT( rStr.Search( '\t' ) == STRING_NOTFOUND, "FastInsertText: Features nicht erlaubt!" );
/*N*/
/*N*/   if ( ( aPaM.GetNode()->Len() + rStr.Len() ) < MAXCHARSINPARA )
/*N*/   {
/*N*/ #ifndef SVX_LIGHT
/*N*/       if ( IsUndoEnabled() && !IsInUndo() )
/*?*/           InsertUndo( new EditUndoInsertChars( this, CreateEPaM( aPaM ), rStr ) );
/*N*/ #endif
/*N*/
/*N*/       aPaM = aEditDoc.InsertText( aPaM, rStr );
/*N*/       TextModified();
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       aPaM = ImpInsertText( aPaM, rStr );
/*N*/   }
/*N*/
/*N*/   return aPaM;
/*N*/ }

/*N*/ EditPaM ImpEditEngine::ImpInsertFeature( EditSelection aCurSel, const SfxPoolItem& rItem )
/*N*/ {
/*N*/   EditPaM aPaM;
/*N*/   if ( aCurSel.HasRange() )
/*?*/       aPaM = ImpDeleteSelection( aCurSel );
/*N*/   else
/*N*/       aPaM = aCurSel.Max();
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/   if ( IsUndoEnabled() && !IsInUndo() )
/*N*/       InsertUndo( new EditUndoInsertFeature( this, CreateEPaM( aPaM ), rItem ) );
/*N*/ #endif
/*N*/   aPaM = aEditDoc.InsertFeature( aPaM, rItem );
/*N*/
/*N*/   ParaPortion* pPortion = FindParaPortion( aPaM.GetNode() );
/*N*/   DBG_ASSERT( pPortion, "Blinde Portion in InsertFeature" );
/*N*/   pPortion->MarkInvalid( aPaM.GetIndex()-1, 1 );
/*N*/
/*N*/   TextModified();
/*N*/
/*N*/   return aPaM;
/*N*/ }

/*N*/ EditPaM ImpEditEngine::ImpInsertParaBreak( const EditSelection& rCurSel, BOOL bKeepEndingAttribs )
/*N*/ {
/*N*/   EditPaM aPaM;
/*N*/   if ( rCurSel.HasRange() )
/*?*/       aPaM = ImpDeleteSelection( rCurSel );
/*N*/   else
/*N*/       aPaM = rCurSel.Max();
/*N*/
/*N*/   return ImpInsertParaBreak( aPaM, bKeepEndingAttribs );
/*N*/ }

/*N*/ EditPaM ImpEditEngine::ImpInsertParaBreak( const EditPaM& rPaM, BOOL bKeepEndingAttribs )
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   if ( IsUndoEnabled() && !IsInUndo() )
/*N*/       InsertUndo( new EditUndoSplitPara( this, aEditDoc.GetPos( rPaM.GetNode() ), rPaM.GetIndex() ) );
/*N*/ #endif
/*N*/
/*N*/   EditPaM aPaM( aEditDoc.InsertParaBreak( rPaM, bKeepEndingAttribs ) );
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/   if ( GetStatus().DoOnlineSpelling() )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 xub_StrLen nEnd = rPaM.GetNode()->Len();
//STRIP001 /*?*/        aPaM.GetNode()->CreateWrongList();
//STRIP001 /*?*/        WrongList* pLWrongs = rPaM.GetNode()->GetWrongList();
//STRIP001 /*?*/        WrongList* pRWrongs = aPaM.GetNode()->GetWrongList();
//STRIP001 /*?*/        // Falschgeschriebene Woerter ruebernehmen:
//STRIP001 /*?*/        USHORT nLWrongs = pLWrongs->Count();
//STRIP001 /*?*/        for ( USHORT nW = 0; nW < nLWrongs; nW++ )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            WrongRange& rWrong = pLWrongs->GetObject( nW );
//STRIP001 /*?*/            // Nur wenn wirklich dahinter, ein ueberlappendes wird beim Spell korrigiert
//STRIP001 /*?*/            if ( rWrong.nStart > nEnd )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                pRWrongs->InsertWrong( rWrong, pRWrongs->Count() );
//STRIP001 /*?*/                WrongRange& rRWrong = pRWrongs->GetObject( pRWrongs->Count() - 1 );
//STRIP001 /*?*/                rRWrong.nStart -= nEnd;
//STRIP001 /*?*/                rRWrong.nEnd -= nEnd;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            else if ( ( rWrong.nStart < nEnd ) && ( rWrong.nEnd > nEnd ) )
//STRIP001 /*?*/                rWrong.nEnd = nEnd;
//STRIP001 /*?*/        }
//STRIP001 /*?*/        USHORT nInv = nEnd ? nEnd-1 : nEnd;
//STRIP001 /*?*/        if ( nEnd )
//STRIP001 /*?*/            pLWrongs->MarkInvalid( nInv, nEnd );
//STRIP001 /*?*/        else
//STRIP001 /*?*/            pLWrongs->SetValid();
//STRIP001 /*?*/        pRWrongs->SetValid(); // sonst 0 - 0xFFFF
//STRIP001 /*?*/        pRWrongs->MarkInvalid( 0, 1 );  // Nur das erste Wort testen
/*N*/   }
/*N*/ #endif // !SVX_LIGHT
/*N*/
/*N*/
/*N*/   ParaPortion* pPortion = FindParaPortion( rPaM.GetNode() );
/*N*/   DBG_ASSERT( pPortion, "Blinde Portion in ImpInsertParaBreak" );
/*N*/   pPortion->MarkInvalid( rPaM.GetIndex(), 0 );
/*N*/
/*N*/   // Optimieren: Nicht unnoetig viele GetPos auf die Listen ansetzen!
/*N*/   // Hier z.B. bei Undo, aber auch in allen anderen Methoden.
/*N*/   USHORT nPos = GetParaPortions().GetPos( pPortion );
/*N*/   ParaPortion* pNewPortion = new ParaPortion( aPaM.GetNode() );
/*N*/   GetParaPortions().Insert( pNewPortion, nPos + 1 );
/*N*/   ParaAttribsChanged( pNewPortion->GetNode() );
/*N*/   if ( IsCallParaInsertedOrDeleted() )
/*N*/       GetEditEnginePtr()->ParagraphInserted( nPos+1 );
/*N*/
/*N*/   CursorMoved( rPaM.GetNode() );  // falls leeres Attribut entstanden.
/*N*/   TextModified();
/*N*/   return aPaM;
/*N*/ }

/*N*/ EditPaM ImpEditEngine::ImpFastInsertParagraph( USHORT nPara )
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   if ( IsUndoEnabled() && !IsInUndo() )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 if ( nPara )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            DBG_ASSERT( aEditDoc.SaveGetObject( nPara-1 ), "FastInsertParagraph: Prev existiert nicht" );
//STRIP001 /*?*/            InsertUndo( new EditUndoSplitPara( this, nPara-1, aEditDoc.GetObject( nPara-1 )->Len() ) );
//STRIP001 /*?*/        }
//STRIP001 /*?*/        else
//STRIP001 /*?*/            InsertUndo( new EditUndoSplitPara( this, 0, 0 ) );
/*N*/   }
/*N*/ #endif
/*N*/
/*N*/   ContentNode* pNode = new ContentNode( aEditDoc.GetItemPool() );
/*N*/   // Falls FlatMode, wird spaeter kein Font eingestellt:
/*N*/   pNode->GetCharAttribs().GetDefFont() = aEditDoc.GetDefFont();
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/   if ( GetStatus().DoOnlineSpelling() )
/*?*/       pNode->CreateWrongList();
/*N*/ #endif // !SVX_LIGHT
/*N*/
/*N*/   aEditDoc.Insert( pNode, nPara );
/*N*/
/*N*/   ParaPortion* pNewPortion = new ParaPortion( pNode );
/*N*/   GetParaPortions().Insert( pNewPortion, nPara );
/*N*/   if ( IsCallParaInsertedOrDeleted() )
/*N*/       GetEditEnginePtr()->ParagraphInserted( nPara );
/*N*/
/*N*/   return EditPaM( pNode, 0 );
/*N*/ }

/*N*/ EditPaM ImpEditEngine::InsertParaBreak( EditSelection aCurSel )
/*N*/ {
/*N*/   EditPaM aPaM( ImpInsertParaBreak( aCurSel ) );
/*N*/   if ( aStatus.DoAutoIndenting() )
/*N*/   {
/*N*/       USHORT nPara = aEditDoc.GetPos( aPaM.GetNode() );
/*N*/       DBG_ASSERT( nPara > 0, "AutoIndenting: Fehler!" );
/*N*/       XubString aPrevParaText( GetEditDoc().GetParaAsString( nPara-1 ) );
/*N*/       USHORT n = 0;
/*N*/       while ( ( n < aPrevParaText.Len() ) &&
/*N*/               ( ( aPrevParaText.GetChar(n) == ' ' ) || ( aPrevParaText.GetChar(n) == '\t' ) ) )
/*N*/       {
/*?*/           if ( aPrevParaText.GetChar(n) == '\t' )
/*?*/               aPaM = ImpInsertFeature( aPaM, SfxVoidItem( EE_FEATURE_TAB ) );
/*?*/           else
/*?*/               aPaM = ImpInsertText( aPaM, aPrevParaText.GetChar(n) );
/*?*/           n++;
/*N*/       }
/*N*/
/*N*/   }
/*N*/   return aPaM;
/*N*/ }

/*N*/ EditPaM ImpEditEngine::InsertTab( EditSelection aCurSel )
/*N*/ {
/*N*/   EditPaM aPaM( ImpInsertFeature( aCurSel, SfxVoidItem( EE_FEATURE_TAB ) ) );
/*N*/   return aPaM;
/*N*/ }

//STRIP001 EditPaM ImpEditEngine::InsertField( EditSelection aCurSel, const SvxFieldItem& rFld )
//STRIP001 {
//STRIP001  EditPaM aPaM( ImpInsertFeature( aCurSel, rFld ) );
//STRIP001  return aPaM;
//STRIP001 }

/*N*/ BOOL ImpEditEngine::UpdateFields()
/*N*/ {
/*N*/   BOOL bChanges = FALSE;
/*N*/   USHORT nParas = GetEditDoc().Count();
/*N*/   for ( USHORT nPara = 0; nPara < nParas; nPara++ )
/*N*/   {
/*N*/       BOOL bChangesInPara = FALSE;
/*N*/       ContentNode* pNode = GetEditDoc().GetObject( nPara );
/*N*/       DBG_ASSERT( pNode, "NULL-Pointer im Doc" );
/*N*/       CharAttribArray& rAttribs = pNode->GetCharAttribs().GetAttribs();
/*N*/       USHORT nAttrs = rAttribs.Count();
/*N*/       for ( USHORT nAttr = 0; nAttr < rAttribs.Count(); nAttr++ )
/*N*/       {
/*N*/           EditCharAttrib* pAttr = rAttribs[nAttr];
/*N*/           if ( pAttr->Which() == EE_FEATURE_FIELD )
/*N*/           {
/*N*/               EditCharAttribField* pField = (EditCharAttribField*)pAttr;
/*N*/               EditCharAttribField* pCurrent = new EditCharAttribField( *pField );
/*N*/               pField->Reset();
/*N*/
/*N*/                 if ( aStatus.MarkFields() )
/*N*/                     pField->GetFldColor() = new Color( GetColorConfig().GetColorValue( svtools::WRITERFIELDSHADINGS ).nColor );
/*N*/
/*N*/               XubString aFldValue = GetEditEnginePtr()->CalcFieldValue(
/*N*/                                       (const SvxFieldItem&)*pField->GetItem(),
/*N*/                                       nPara, pField->GetStart(),
/*N*/                                       pField->GetTxtColor(), pField->GetFldColor() );
/*N*/               pField->GetFieldValue() = aFldValue;
/*N*/               if ( *pField != *pCurrent )
/*N*/               {
/*N*/                   bChanges = TRUE;
/*N*/                   bChangesInPara = TRUE;
/*N*/               }
/*N*/               delete pCurrent;
/*N*/           }
/*N*/       }
/*N*/       if ( bChangesInPara )
/*N*/       {
/*N*/           // ggf. etwas genauer invalidieren.
/*N*/           ParaPortion* pPortion = GetParaPortions().GetObject( nPara );
/*N*/           DBG_ASSERT( pPortion, "NULL-Pointer im Doc" );
/*N*/           pPortion->MarkSelectionInvalid( 0, pNode->Len() );
/*N*/       }
/*N*/   }
/*N*/   return bChanges;
/*N*/ }

/*N*/ EditPaM ImpEditEngine::InsertLineBreak( EditSelection aCurSel )
/*N*/ {
/*N*/   EditPaM aPaM( ImpInsertFeature( aCurSel, SfxVoidItem( EE_FEATURE_LINEBR ) ) );
/*N*/   return aPaM;
/*N*/ }

//  ----------------------------------------------------------------------
//  Hilfsfunktionen
//  ----------------------------------------------------------------------
//STRIP001 Rectangle ImpEditEngine::PaMtoEditCursor( EditPaM aPaM, USHORT nFlags )
//STRIP001 {
//STRIP001  DBG_ASSERT( GetUpdateMode(), "Darf bei Update=FALSE nicht erreicht werden: PaMtoEditCursor" );
//STRIP001
//STRIP001  Rectangle aEditCursor;
//STRIP001  long nY = 0;
//STRIP001  for ( USHORT nPortion = 0; nPortion < GetParaPortions().Count(); nPortion++ )
//STRIP001  {
//STRIP001      ParaPortion* pPortion = GetParaPortions().GetObject(nPortion);
//STRIP001      ContentNode* pNode = pPortion->GetNode();
//STRIP001      DBG_ASSERT( pNode, "Ungueltiger Node in Portion!" );
//STRIP001      if ( pNode != aPaM.GetNode() )
//STRIP001      {
//STRIP001          nY += pPortion->GetHeight();
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          aEditCursor = GetEditCursor( pPortion, aPaM.GetIndex(), nFlags );
//STRIP001          aEditCursor.Top() += nY;
//STRIP001          aEditCursor.Bottom() += nY;
//STRIP001          return aEditCursor;
//STRIP001      }
//STRIP001  }
//STRIP001  DBG_ERROR( "Portion nicht gefunden!" );
//STRIP001  return aEditCursor;
//STRIP001 }

/*N*/ EditPaM ImpEditEngine::GetPaM( Point aDocPos, BOOL bSmart )
/*N*/ {
/*N*/   DBG_ASSERT( GetUpdateMode(), "Darf bei Update=FALSE nicht erreicht werden: GetPaM" );
/*N*/
/*N*/   long nY = 0;
/*N*/   long nTmpHeight;
/*N*/   EditPaM aPaM;
/*N*/   USHORT nPortion;
/*N*/   for ( nPortion = 0; nPortion < GetParaPortions().Count(); nPortion++ )
/*N*/   {
/*N*/       ParaPortion* pPortion = GetParaPortions().GetObject(nPortion);
/*N*/       nTmpHeight = pPortion->GetHeight();     // sollte auch bei !bVisible richtig sein!
/*N*/       nY += nTmpHeight;
/*N*/       if ( nY > aDocPos.Y() )
/*N*/       {
/*N*/           nY -= nTmpHeight;
/*N*/           aDocPos.Y() -= nY;
/*N*/           // unsichtbare Portions ueberspringen:
/*N*/           while ( pPortion && !pPortion->IsVisible() )
/*N*/           {
/*?*/               nPortion++;
/*?*/               pPortion = GetParaPortions().SaveGetObject( nPortion );
/*N*/           }
/*N*/           DBG_ASSERT( pPortion, "Keinen sichtbaren Absatz gefunden: GetPaM" );
/*N*/           aPaM = GetPaM( pPortion, aDocPos, bSmart );
/*N*/           return aPaM;
/*N*/
/*N*/       }
/*N*/   }
/*?*/   // Dann den letzten sichtbaren Suchen:
/*?*/   nPortion = GetParaPortions().Count()-1;
/*?*/   while ( nPortion && !GetParaPortions()[nPortion]->IsVisible() )
/*?*/       nPortion--;
/*?*/
/*?*/   DBG_ASSERT( GetParaPortions()[nPortion]->IsVisible(), "Keinen sichtbaren Absatz gefunden: GetPaM" );
/*?*/   aPaM.SetNode( GetParaPortions()[nPortion]->GetNode() );
/*?*/   aPaM.SetIndex( GetParaPortions()[nPortion]->GetNode()->Len() );
/*?*/   return aPaM;
/*N*/ }

/*N*/ ULONG ImpEditEngine::GetTextHeight() const
/*N*/ {
/*N*/   DBG_ASSERT( GetUpdateMode(), "Sollte bei Update=FALSE nicht verwendet werden: GetTextHeight" );
/*N*/   DBG_ASSERT( IsFormatted() || IsFormatting(), "GetTextHeight: Nicht formatiert" );
/*N*/   return nCurTextHeight;
/*N*/ }

/*N*/ ULONG ImpEditEngine::CalcTextWidth( BOOL bIgnoreExtraSpace )
/*N*/ {
/*N*/   // Wenn noch nicht formatiert und nicht gerade dabei.
/*N*/   // Wird in der Formatierung bei AutoPageSize gerufen.
/*N*/   if ( !IsFormatted() && !IsFormatting() )
/*?*/       FormatDoc();
/*N*/
/*N*/   EditLine* pLine;
/*N*/
/*N*/   long nMaxWidth = 0;
/*N*/   long nCurWidth = 0;
/*N*/
/*N*/   // --------------------------------------------------
/*N*/   // Ueber alle Absaetze...
/*N*/   // --------------------------------------------------
/*N*/   USHORT nParas = GetParaPortions().Count();
/*N*/   USHORT nBiggestPara = 0;
/*N*/   USHORT nBiggestLine = 0;
/*N*/   for ( USHORT nPara = 0; nPara < nParas; nPara++ )
/*N*/   {
/*N*/       ParaPortion* pPortion = GetParaPortions().GetObject( nPara );
/*N*/       const SvxLRSpaceItem& rLRItem = GetLRSpaceItem( pPortion->GetNode() );
/*N*/
/*N*/       if ( pPortion->IsVisible() )
/*N*/       {
/*N*/           // --------------------------------------------------
/*N*/           // Ueber die Zeilen des Absatzes...
/*N*/           // --------------------------------------------------
/*N*/           ULONG nLines = pPortion->GetLines().Count();
/*N*/           for ( USHORT nLine = 0; nLine < nLines; nLine++ )
/*N*/           {
/*N*/               pLine = pPortion->GetLines().GetObject( nLine );
/*N*/               DBG_ASSERT( pLine, "NULL-Pointer im Zeileniterator in CalcWidth" );
/*N*/               // nCurWidth = pLine->GetStartPosX();
/*N*/               // Bei Center oder Right haengt die breite von der
/*N*/               // Papierbreite ab, hier nicht erwuenscht.
/*N*/               // Am besten generell nicht auf StartPosX verlassen,
/*N*/               // es muss auch die rechte Einrueckung beruecksichtigt werden!
/*N*/               nCurWidth = GetXValue( rLRItem.GetTxtLeft() );
/*N*/               if ( nLine == 0 )
/*N*/               {
/*N*/                   long nFI = GetXValue( rLRItem.GetTxtFirstLineOfst() );
/*N*/                   nCurWidth += nFI;
/*N*/                   if ( pPortion->GetBulletX() > nCurWidth )
/*N*/                   {
/*?*/                       nCurWidth -= nFI;   // LI?
/*?*/                       if ( pPortion->GetBulletX() > nCurWidth )
/*?*/                           nCurWidth = pPortion->GetBulletX();
/*N*/                   }
/*N*/               }
/*N*/               nCurWidth += GetXValue( rLRItem.GetRight() );
/*N*/               nCurWidth += CalcLineWidth( pPortion, pLine, bIgnoreExtraSpace );
/*N*/               if ( nCurWidth > nMaxWidth )
/*N*/               {
/*N*/                   nMaxWidth = nCurWidth;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   if ( nMaxWidth < 0 )
/*?*/       nMaxWidth = 0;
/*N*/
/*N*/   nMaxWidth++; // Ein breiter, da in CreateLines bei >= umgebrochen wird.
/*N*/   return (ULONG)nMaxWidth;
/*N*/ }

/*N*/ ULONG ImpEditEngine::CalcLineWidth( ParaPortion* pPortion, EditLine* pLine, BOOL bIgnoreExtraSpace )
/*N*/ {
/*N*/   USHORT nPara = GetEditDoc().GetPos( pPortion->GetNode() );
/*N*/     ULONG nOldLayoutMode = GetRefDevice()->GetLayoutMode();
/*N*/
/*N*/     ImplInitLayoutMode( GetRefDevice(), nPara, 0xFFFF );
/*N*/
/*N*/     SvxAdjust eJustification = GetJustification( nPara );
/*N*/
/*N*/     // Berechnung der Breite ohne die Indents...
/*N*/   ULONG nWidth = 0;
/*N*/     USHORT nPos = pLine->GetStart();
/*N*/   for ( USHORT nTP = pLine->GetStartPortion(); nTP <= pLine->GetEndPortion(); nTP++ )
/*N*/   {
/*N*/       TextPortion* pTextPortion = pPortion->GetTextPortions().GetObject( nTP );
/*N*/       switch ( pTextPortion->GetKind() )
/*N*/       {
/*N*/           case PORTIONKIND_FIELD:
/*N*/           case PORTIONKIND_HYPHENATOR:
/*N*/           case PORTIONKIND_TAB:
/*N*/           {
/*N*/               nWidth += pTextPortion->GetSize().Width();
/*N*/           }
/*N*/           break;
/*N*/           case PORTIONKIND_TEXT:
/*N*/           {
/*N*/                 if ( ( eJustification != SVX_ADJUST_BLOCK ) || ( !bIgnoreExtraSpace ) )
/*N*/                 {
/*N*/                   nWidth += pTextPortion->GetSize().Width();
/*N*/                 }
/*N*/                 else
/*N*/                 {
/*?*/                   SvxFont aTmpFont( pPortion->GetNode()->GetCharAttribs().GetDefFont() );
/*?*/                   SeekCursor( pPortion->GetNode(), nPos+1, aTmpFont );
/*?*/                   aTmpFont.SetPhysFont( GetRefDevice() );
/*?*/                   nWidth += aTmpFont.QuickGetTextSize( GetRefDevice(), *pPortion->GetNode(), nPos, pTextPortion->GetLen(), NULL ).Width();
/*N*/                 }
/*N*/           }
/*N*/           break;
/*N*/       }
/*N*/         nPos += pTextPortion->GetLen();
/*N*/   }
/*N*/
/*N*/     GetRefDevice()->SetLayoutMode( nOldLayoutMode );
/*N*/
/*N*/     return nWidth;
/*N*/ }

/*N*/ ULONG ImpEditEngine::CalcTextHeight()
/*N*/ {
/*N*/   DBG_ASSERT( GetUpdateMode(), "Sollte bei Update=FALSE nicht verwendet werden: CalcTextHeight" );
/*N*/   ULONG nY = 0;
/*N*/   for ( USHORT nPortion = 0; nPortion < GetParaPortions().Count(); nPortion++ )
/*N*/       nY += GetParaPortions()[nPortion]->GetHeight();
/*N*/   return nY;
/*N*/ }

/*N*/ USHORT ImpEditEngine::GetLineCount( USHORT nParagraph ) const
/*N*/ {
/*N*/   DBG_ASSERT( nParagraph < GetParaPortions().Count(), "GetLineCount: Out of range" );
/*N*/   ParaPortion* pPPortion = GetParaPortions().SaveGetObject( nParagraph );
/*N*/   DBG_ASSERT( pPPortion, "Absatz nicht gefunden: GetLineCount" );
/*N*/   if ( pPPortion )
/*N*/       return pPPortion->GetLines().Count();
/*N*/
/*N*/   return 0xFFFF;
/*N*/ }

//STRIP001 xub_StrLen ImpEditEngine::GetLineLen( USHORT nParagraph, USHORT nLine ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( nParagraph < GetParaPortions().Count(), "GetLineCount: Out of range" );
//STRIP001  ParaPortion* pPPortion = GetParaPortions().SaveGetObject( nParagraph );
//STRIP001  DBG_ASSERT( pPPortion, "Absatz nicht gefunden: GetLineHeight" );
//STRIP001  if ( pPPortion && ( nLine < pPPortion->GetLines().Count() ) )
//STRIP001  {
//STRIP001      EditLine* pLine = pPPortion->GetLines().GetObject( nLine );
//STRIP001      DBG_ASSERT( pLine, "Zeile nicht gefunden: GetLineHeight" );
//STRIP001      return pLine->GetLen();
//STRIP001  }
//STRIP001
//STRIP001  return 0xFFFF;
//STRIP001 }

//STRIP001 USHORT ImpEditEngine::GetLineHeight( USHORT nParagraph, USHORT nLine )
//STRIP001 {
//STRIP001  DBG_ASSERT( nParagraph < GetParaPortions().Count(), "GetLineCount: Out of range" );
//STRIP001  ParaPortion* pPPortion = GetParaPortions().SaveGetObject( nParagraph );
//STRIP001  DBG_ASSERT( pPPortion, "Absatz nicht gefunden: GetLineHeight" );
//STRIP001  if ( pPPortion && ( nLine < pPPortion->GetLines().Count() ) )
//STRIP001  {
//STRIP001      EditLine* pLine = pPPortion->GetLines().GetObject( nLine );
//STRIP001      DBG_ASSERT( pLine, "Zeile nicht gefunden: GetLineHeight" );
//STRIP001      return pLine->GetHeight();
//STRIP001  }
//STRIP001
//STRIP001  return 0xFFFF;
//STRIP001 }

//STRIP001 ULONG ImpEditEngine::GetParaHeight( USHORT nParagraph )
//STRIP001 {
//STRIP001  ULONG nHeight = 0;
//STRIP001
//STRIP001  ParaPortion* pPPortion = GetParaPortions().SaveGetObject( nParagraph );
//STRIP001  DBG_ASSERT( pPPortion, "Absatz nicht gefunden: GetParaHeight" );
//STRIP001
//STRIP001  if ( pPPortion )
//STRIP001      nHeight = pPPortion->GetHeight();
//STRIP001
//STRIP001  return nHeight;
//STRIP001 }

/*N*/ void ImpEditEngine::UpdateSelections()
/*N*/ {
/*N*/   USHORT nInvNodes = aDeletedNodes.Count();
/*N*/
/*N*/   // Pruefen, ob eine der Selektionen auf einem geloeschten Node steht...
/*N*/   // Wenn der Node gueltig ist, muss noch der Index geprueft werden!
/*N*/   for ( USHORT nView = 0; nView < aEditViews.Count(); nView++ )
/*N*/   {
/*N*/       EditView* pView = aEditViews.GetObject(nView);
/*N*/       DBG_CHKOBJ( pView, EditView, 0 );
/*N*/       EditSelection aCurSel( pView->pImpEditView->GetEditSelection() );
/*N*/       BOOL bChanged = FALSE;
/*N*/       for ( USHORT n = 0; n < nInvNodes; n++ )
/*N*/       {
/*?*/           DeletedNodeInfo* pInf = aDeletedNodes.GetObject( n );
/*?*/           if ( ( ( ULONG )(aCurSel.Min().GetNode()) == pInf->GetInvalidAdress() ) ||
/*?*/                ( ( ULONG )(aCurSel.Max().GetNode()) == pInf->GetInvalidAdress() ) )
/*?*/           {
/*?*/               // ParaPortions verwenden, da jetzt auch versteckte
/*?*/               // Absaetze beruecksichtigt werden muessen!
/*?*/               USHORT nPara = pInf->GetPosition();
/*?*/               ParaPortion* pPPortion = GetParaPortions().SaveGetObject( nPara );
/*?*/               if ( !pPPortion ) // letzter Absatz
/*?*/               {
/*?*/                   nPara = GetParaPortions().Count()-1;
/*?*/                   pPPortion = GetParaPortions().GetObject( nPara );
/*?*/               }
/*?*/               DBG_ASSERT( pPPortion, "Leeres Document in UpdateSelections ?" );
/*?*/               // Nicht aus einem verstecktem Absatz landen:
/*?*/               USHORT nCurPara = nPara;
/*?*/               USHORT nLastPara = GetParaPortions().Count()-1;
/*?*/               while ( nPara <= nLastPara && !GetParaPortions()[nPara]->IsVisible() )
/*?*/                   nPara++;
/*?*/               if ( nPara > nLastPara ) // dann eben rueckwaerts...
/*?*/               {
/*?*/                   nPara = nCurPara;
/*?*/                   while ( nPara && !GetParaPortions()[nPara]->IsVisible() )
/*?*/                       nPara--;
/*?*/               }
/*?*/               DBG_ASSERT( GetParaPortions()[nPara]->IsVisible(), "Keinen sichtbaren Absatz gefunden: UpdateSelections" );
/*?*/
/*?*/               ParaPortion* pParaPortion = GetParaPortions()[nPara];
/*?*/               EditSelection aTmpSelection( EditPaM( pParaPortion->GetNode(), 0 ) );
/*?*/               pView->pImpEditView->SetEditSelection( aTmpSelection );
/*?*/               bChanged=TRUE;
/*?*/               break;  // for-Schleife
/*?*/           }
/*N*/       }
/*N*/       if ( !bChanged )
/*N*/       {
/*N*/           // Index prueffen, falls Node geschrumpft.
/*N*/           if ( aCurSel.Min().GetIndex() > aCurSel.Min().GetNode()->Len() )
/*N*/           {
/*?*/               aCurSel.Min().GetIndex() = aCurSel.Min().GetNode()->Len();
/*?*/               pView->pImpEditView->SetEditSelection( aCurSel );
/*N*/           }
/*N*/           if ( aCurSel.Max().GetIndex() > aCurSel.Max().GetNode()->Len() )
/*N*/           {
/*?*/               aCurSel.Max().GetIndex() = aCurSel.Max().GetNode()->Len();
/*?*/               pView->pImpEditView->SetEditSelection( aCurSel );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // Loeschen...
/*N*/   for ( USHORT n = 0; n < nInvNodes; n++ )
/*N*/   {
/*N*/       DeletedNodeInfo* pInf = aDeletedNodes.GetObject( n );
/*N*/       delete pInf;
/*N*/   }
/*N*/   aDeletedNodes.Remove( 0, aDeletedNodes.Count() );
/*N*/ }

/*N*/ EditSelection ImpEditEngine::ConvertSelection( USHORT nStartPara, USHORT nStartPos,
/*N*/                            USHORT nEndPara, USHORT nEndPos ) const
/*N*/ {
/*N*/   EditSelection aNewSelection;
/*N*/
/*N*/   // Start...
/*N*/   ContentNode* pNode = aEditDoc.SaveGetObject( nStartPara );
/*N*/   USHORT nIndex = nStartPos;
/*N*/   if ( !pNode )
/*N*/   {
/*?*/       pNode = aEditDoc[ aEditDoc.Count()-1 ];
/*?*/       nIndex = pNode->Len();
/*N*/   }
/*N*/   else if ( nIndex > pNode->Len() )
/*?*/       nIndex = pNode->Len();
/*N*/
/*N*/   aNewSelection.Min().SetNode( pNode );
/*N*/   aNewSelection.Min().SetIndex( nIndex );
/*N*/
/*N*/   // End...
/*N*/   pNode = aEditDoc.SaveGetObject( nEndPara );
/*N*/   nIndex = nEndPos;
/*N*/   if ( !pNode )
/*N*/   {
/*?*/       pNode = aEditDoc[ aEditDoc.Count()-1 ];
/*?*/       nIndex = pNode->Len();
/*N*/   }
/*N*/   else if ( nIndex > pNode->Len() )
/*?*/       nIndex = pNode->Len();
/*N*/
/*N*/   aNewSelection.Max().SetNode( pNode );
/*N*/   aNewSelection.Max().SetIndex( nIndex );
/*N*/
/*N*/   return aNewSelection;
/*N*/ }

//STRIP001 EditSelection ImpEditEngine::MatchGroup( const EditSelection& rSel )
//STRIP001 {
//STRIP001  EditSelection aMatchSel;
//STRIP001  EditSelection aTmpSel( rSel );
//STRIP001  aTmpSel.Adjust( GetEditDoc() );
//STRIP001  if ( (  aTmpSel.Min().GetNode() != aTmpSel.Max().GetNode() ) ||
//STRIP001       ( ( aTmpSel.Max().GetIndex() - aTmpSel.Min().GetIndex() ) > 1 ) )
//STRIP001  {
//STRIP001      return aMatchSel;
//STRIP001  }
//STRIP001
//STRIP001  USHORT nPos = aTmpSel.Min().GetIndex();
//STRIP001  ContentNode* pNode = aTmpSel.Min().GetNode();
//STRIP001  if ( nPos >= pNode->Len() )
//STRIP001      return aMatchSel;
//STRIP001
//STRIP001  USHORT nMatchChar = aGroupChars.Search( pNode->GetChar( nPos ) );
//STRIP001  if ( nMatchChar != STRING_NOTFOUND )
//STRIP001  {
//STRIP001      USHORT nNode = aEditDoc.GetPos( pNode );
//STRIP001      if ( ( nMatchChar % 2 ) == 0 )
//STRIP001      {
//STRIP001          // Vorwaerts suchen...
//STRIP001          xub_Unicode nSC = aGroupChars.GetChar( nMatchChar );
//STRIP001          DBG_ASSERT( aGroupChars.Len() > (nMatchChar+1), "Ungueltige Gruppe von MatchChars!" );
//STRIP001          xub_Unicode nEC = aGroupChars.GetChar( nMatchChar+1 );
//STRIP001
//STRIP001          USHORT nCur = aTmpSel.Min().GetIndex()+1;
//STRIP001          USHORT nLevel = 1;
//STRIP001          while ( pNode && nLevel )
//STRIP001          {
//STRIP001              XubString& rStr = *pNode;
//STRIP001              while ( nCur < rStr.Len() )
//STRIP001              {
//STRIP001                  if ( rStr.GetChar( nCur ) == nSC )
//STRIP001                      nLevel++;
//STRIP001                  else if ( rStr.GetChar( nCur ) == nEC )
//STRIP001                  {
//STRIP001                      nLevel--;
//STRIP001                      if ( !nLevel )
//STRIP001                          break;  // while nCur...
//STRIP001                  }
//STRIP001                  nCur++;
//STRIP001              }
//STRIP001
//STRIP001              if ( nLevel )
//STRIP001              {
//STRIP001                  nNode++;
//STRIP001                  pNode = nNode < aEditDoc.Count() ? aEditDoc.GetObject( nNode ) : 0;
//STRIP001                  nCur = 0;
//STRIP001              }
//STRIP001          }
//STRIP001          if ( nLevel == 0 )  // gefunden
//STRIP001          {
//STRIP001              aMatchSel.Min() = aTmpSel.Min();
//STRIP001              aMatchSel.Max() = EditPaM( pNode, nCur+1 );
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // Rueckwaerts suchen...
//STRIP001          xub_Unicode nEC = aGroupChars.GetChar( nMatchChar );
//STRIP001          xub_Unicode nSC = aGroupChars.GetChar( nMatchChar-1 );
//STRIP001
//STRIP001          USHORT nCur = aTmpSel.Min().GetIndex()-1;
//STRIP001          USHORT nLevel = 1;
//STRIP001          while ( pNode && nLevel )
//STRIP001          {
//STRIP001              if ( pNode->Len() )
//STRIP001              {
//STRIP001                  XubString& rStr = *pNode;
//STRIP001                  while ( nCur )
//STRIP001                  {
//STRIP001                      if ( rStr.GetChar( nCur ) == nSC )
//STRIP001                      {
//STRIP001                          nLevel--;
//STRIP001                          if ( !nLevel )
//STRIP001                              break;  // while nCur...
//STRIP001                      }
//STRIP001                      else if ( rStr.GetChar( nCur ) == nEC )
//STRIP001                          nLevel++;
//STRIP001
//STRIP001                      nCur--;
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              if ( nLevel )
//STRIP001              {
//STRIP001                  pNode = nNode ? aEditDoc.GetObject( --nNode ) : 0;
//STRIP001                  if ( pNode )
//STRIP001                      nCur = pNode->Len()-1;  // egal ob negativ, weil if Len()
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          if ( nLevel == 0 )  // gefunden
//STRIP001          {
//STRIP001              aMatchSel.Min() = aTmpSel.Min();
//STRIP001              aMatchSel.Min().GetIndex()++;   // hinter das Zeichen
//STRIP001              aMatchSel.Max() = EditPaM( pNode, nCur );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return aMatchSel;
//STRIP001 }

//STRIP001 void ImpEditEngine::StopSelectionMode()
//STRIP001 {
//STRIP001  if ( ( IsInSelectionMode() || aSelEngine.IsInSelection() ) && pActiveView )
//STRIP001  {
//STRIP001      pActiveView->pImpEditView->DrawSelection(); // Wegzeichnen...
//STRIP001      EditSelection aSel( pActiveView->pImpEditView->GetEditSelection() );
//STRIP001      aSel.Min() = aSel.Max();
//STRIP001      pActiveView->pImpEditView->SetEditSelection( aSel );
//STRIP001      pActiveView->ShowCursor();
//STRIP001      aSelEngine.Reset();
//STRIP001      bInSelection = FALSE;
//STRIP001  }
//STRIP001 }

/*N*/ void ImpEditEngine::SetActiveView( EditView* pView )
/*N*/ {
/*N*/   // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*N*/   // Eigentlich waere jetzt ein bHasVisSel und HideSelection notwendig !!!
/*N*/
/*N*/   if ( pView == pActiveView )
/*N*/       return;
/*N*/
/*N*/   if ( pActiveView && pActiveView->HasSelection() )
/*?*/       pActiveView->pImpEditView->DrawSelection(); // Wegzeichnen...
/*N*/
/*N*/   pActiveView = pView;
/*N*/
/*N*/   if ( pActiveView && pActiveView->HasSelection() )
/*?*/       pActiveView->pImpEditView->DrawSelection(); // Wegzeichnen...
/*N*/
/*N*/   //  NN: Quick fix for #78668#:
/*N*/   //  When editing of a cell in Calc is ended, the edit engine is not deleted,
/*N*/   //  only the edit views are removed. If mpIMEInfos is still set in that case,
/*N*/   //  mpIMEInfos->aPos points to an invalid selection.
/*N*/   //  -> reset mpIMEInfos now
/*N*/   //  (probably something like this is necessary whenever the content is modified
/*N*/   //  from the outside)
/*N*/
/*N*/   if ( !pView && mpIMEInfos )
/*N*/   {
/*?*/       delete mpIMEInfos;
/*?*/       mpIMEInfos = NULL;
/*N*/   }
/*N*/ }

//STRIP001 uno::Reference< datatransfer::XTransferable > ImpEditEngine::CreateTransferable( const EditSelection& rSelection ) const
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001     EditSelection aSelection( rSelection );
//STRIP001  aSelection.Adjust( GetEditDoc() );
//STRIP001
//STRIP001  EditDataObject* pDataObj = new EditDataObject;
//STRIP001  uno::Reference< datatransfer::XTransferable > xDataObj;
//STRIP001  xDataObj = pDataObj;
//STRIP001
//STRIP001  XubString aText( GetSelected( aSelection ) );
//STRIP001  aText.ConvertLineEnd(); // Systemspezifisch
//STRIP001  pDataObj->GetString() = aText;
//STRIP001
//STRIP001     SvxFontItem::EnableStoreUnicodeNames( TRUE );
//STRIP001  WriteBin( pDataObj->GetStream(), aSelection, TRUE );
//STRIP001  pDataObj->GetStream().Seek( 0 );
//STRIP001     SvxFontItem::EnableStoreUnicodeNames( FALSE );
//STRIP001
//STRIP001     ((ImpEditEngine*)this)->WriteRTF( pDataObj->GetRTFStream(), aSelection );
//STRIP001  pDataObj->GetRTFStream().Seek( 0 );
//STRIP001
//STRIP001  if ( ( aSelection.Min().GetNode() == aSelection.Max().GetNode() )
//STRIP001          && ( aSelection.Max().GetIndex() == (aSelection.Min().GetIndex()+1) ) )
//STRIP001  {
//STRIP001      const EditCharAttrib* pAttr = aSelection.Min().GetNode()->GetCharAttribs().
//STRIP001          FindFeature( aSelection.Min().GetIndex() );
//STRIP001      if ( pAttr &&
//STRIP001          ( pAttr->GetStart() == aSelection.Min().GetIndex() ) &&
//STRIP001          ( pAttr->Which() == EE_FEATURE_FIELD ) )
//STRIP001      {
//STRIP001          const SvxFieldItem* pField = (const SvxFieldItem*)pAttr->GetItem();
//STRIP001          const SvxFieldData* pFld = pField->GetField();
//STRIP001          if ( pFld && pFld->ISA( SvxURLField ) )
//STRIP001          {
//STRIP001              // Office-Bookmark
//STRIP001              String aURL( ((const SvxURLField*)pFld)->GetURL() );
//STRIP001              String aTxt( ((const SvxURLField*)pFld)->GetRepresentation() );
//STRIP001              pDataObj->GetURL() = aURL;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001     return xDataObj;
//STRIP001 #else
//STRIP001  return uno::Reference< datatransfer::XTransferable >();
//STRIP001 #endif
//STRIP001 }

//STRIP001 EditSelection ImpEditEngine::InsertText( uno::Reference< datatransfer::XTransferable >& rxDataObj, const EditPaM& rPaM, BOOL bUseSpecial )
//STRIP001 {
//STRIP001  EditSelection aNewSelection( rPaM );
//STRIP001
//STRIP001  if ( rxDataObj.is() )
//STRIP001  {
//STRIP001      datatransfer::DataFlavor aFlavor;
//STRIP001      BOOL bDone = FALSE;
//STRIP001
//STRIP001      if ( bUseSpecial )
//STRIP001      {
//STRIP001          // BIN
//STRIP001          SotExchange::GetFormatDataFlavor( SOT_FORMATSTR_ID_EDITENGINE, aFlavor );
//STRIP001          if ( rxDataObj->isDataFlavorSupported( aFlavor ) )
//STRIP001          {
//STRIP001              uno::Any aData = rxDataObj->getTransferData( aFlavor );
//STRIP001              uno::Sequence< sal_Int8 > aSeq;
//STRIP001              aData >>= aSeq;
//STRIP001              {
//STRIP001                  SvMemoryStream aBinStream( aSeq.getArray(), aSeq.getLength(), STREAM_READ );
//STRIP001                  aNewSelection = Read( aBinStream, EE_FORMAT_BIN, rPaM );
//STRIP001              }
//STRIP001              bDone = TRUE;
//STRIP001          }
//STRIP001
//STRIP001          if ( !bDone )
//STRIP001          {
//STRIP001              // Bookmark
//STRIP001              /*
//STRIP001              String aURL = ...;
//STRIP001              String aTxt = ...;
//STRIP001              // Feld nur einfuegen, wenn Factory vorhanden.
//STRIP001              if ( ITEMDATA() && ITEMDATA()->GetClassManager().Get( SVX_URLFIELD ) )
//STRIP001              {
//STRIP001                  SvxFieldItem aField( SvxURLField( aURL, aTxt, SVXURLFORMAT_URL ), EE_FEATURE_FIELD  );
//STRIP001                  aNewSelection = InsertField( aPaM, aField );
//STRIP001                  UpdateFields();
//STRIP001              }
//STRIP001              else
//STRIP001                  aNewSelection = ImpInsertText( aPaM, aURL );
//STRIP001              }
//STRIP001              */
//STRIP001          }
//STRIP001          if ( !bDone )
//STRIP001          {
//STRIP001              // RTF
//STRIP001              SotExchange::GetFormatDataFlavor( SOT_FORMAT_RTF, aFlavor );
//STRIP001              if ( rxDataObj->isDataFlavorSupported( aFlavor ) )
//STRIP001              {
//STRIP001                  uno::Any aData = rxDataObj->getTransferData( aFlavor );
//STRIP001                  uno::Sequence< sal_Int8 > aSeq;
//STRIP001                  aData >>= aSeq;
//STRIP001                  {
//STRIP001                      SvMemoryStream aRTFStream( aSeq.getArray(), aSeq.getLength(), STREAM_READ );
//STRIP001                      aNewSelection = Read( aRTFStream, EE_FORMAT_RTF, rPaM );
//STRIP001                  }
//STRIP001                  bDone = TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001          if ( !bDone )
//STRIP001          {
//STRIP001              // XML ?
//STRIP001                 // Currently, there is nothing like "The" XML format, StarOffice doesn't offer plain XML in Clipboard...
//STRIP001          }
//STRIP001      }
//STRIP001      if ( !bDone )
//STRIP001      {
//STRIP001          SotExchange::GetFormatDataFlavor( SOT_FORMAT_STRING, aFlavor );
//STRIP001          if ( rxDataObj->isDataFlavorSupported( aFlavor ) )
//STRIP001          {
//STRIP001              try
//STRIP001              {
//STRIP001                  uno::Any aData = rxDataObj->getTransferData( aFlavor );
//STRIP001                  ::rtl::OUString aText;
//STRIP001                  aData >>= aText;
//STRIP001                  aNewSelection = ImpInsertText( rPaM, aText );
//STRIP001                  bDone = TRUE;
//STRIP001              }
//STRIP001              catch( ... )
//STRIP001              {
//STRIP001                     ; // #i9286# can happen, even if isDataFlavorSupported returns true...
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return aNewSelection;
//STRIP001 }

/*N*/ Range ImpEditEngine::GetInvalidYOffsets( ParaPortion* pPortion )
/*N*/ {
/*N*/   Range aRange( 0, 0 );
/*N*/
/*N*/   if ( pPortion->IsVisible() )
/*N*/   {
/*N*/       const SvxULSpaceItem& rULSpace = (const SvxULSpaceItem&)pPortion->GetNode()->GetContentAttribs().GetItem( EE_PARA_ULSPACE );
/*N*/       const SvxLineSpacingItem& rLSItem = (const SvxLineSpacingItem&)pPortion->GetNode()->GetContentAttribs().GetItem( EE_PARA_SBL );
/*N*/       USHORT nSBL = ( rLSItem.GetInterLineSpaceRule() == SVX_INTER_LINE_SPACE_FIX )
/*N*/                           ? GetYValue( rLSItem.GetInterLineSpace() ) : 0;
/*N*/
/*N*/       // erst von vorne...
/*N*/       USHORT nFirstInvalid = 0xFFFF;
/*N*/       USHORT nLine;
/*N*/       for ( nLine = 0; nLine < pPortion->GetLines().Count(); nLine++ )
/*N*/       {
/*N*/           EditLine* pL = pPortion->GetLines().GetObject( nLine );
/*N*/           if ( pL->IsInvalid() )
/*N*/           {
/*N*/               nFirstInvalid = nLine;
/*N*/               break;
/*N*/           }
/*?*/           if ( nLine && !aStatus.IsOutliner() )   // nicht die erste Zeile
/*?*/               aRange.Min() += nSBL;
/*?*/           aRange.Min() += pL->GetHeight();
/*N*/       }
/*N*/       DBG_ASSERT( nFirstInvalid != 0xFFFF, "Keine ungueltige Zeile gefunden in GetInvalidYOffset(1)" );
/*N*/
/*N*/
/*N*/       // Abgleichen und weiter...
/*N*/       aRange.Max() = aRange.Min();
/*N*/       aRange.Max() += pPortion->GetFirstLineOffset();
/*N*/       if ( nFirstInvalid != 0 )   // Nur wenn nicht die erste Zeile ungueltig
/*?*/           aRange.Min() = aRange.Max();
/*N*/
/*N*/       USHORT nLastInvalid = pPortion->GetLines().Count()-1;
/*N*/       for ( nLine = nFirstInvalid; nLine < pPortion->GetLines().Count(); nLine++ )
/*N*/       {
/*N*/           EditLine* pL = pPortion->GetLines().GetObject( nLine );
/*N*/           if ( pL->IsValid() )
/*N*/           {
/*?*/               nLastInvalid = nLine;
/*?*/               break;
/*N*/           }
/*N*/
/*N*/           if ( nLine && !aStatus.IsOutliner() )
/*N*/               aRange.Max() += nSBL;
/*N*/           aRange.Max() += pL->GetHeight();
/*N*/       }
/*N*/
/*N*/       // MT 07/00 SBL kann jetzt kleiner 100% sein => ggf. die Zeile davor neu ausgeben.
/*N*/       if( ( rLSItem.GetInterLineSpaceRule() == SVX_INTER_LINE_SPACE_PROP ) && rLSItem.GetPropLineSpace() &&
/*N*/           ( rLSItem.GetPropLineSpace() < 100 ) )
/*N*/       {
/*?*/           EditLine* pL = pPortion->GetLines().GetObject( nFirstInvalid );
/*?*/           long n = pL->GetTxtHeight() * ( 100 - rLSItem.GetPropLineSpace() );
/*?*/           n /= 100;
/*?*/           aRange.Min() -= n;
/*?*/           aRange.Max() += n;
/*N*/       }
/*N*/
/*N*/       if ( ( nLastInvalid == pPortion->GetLines().Count()-1 ) && ( !aStatus.IsOutliner() ) )
/*N*/           aRange.Max() += GetYValue( rULSpace.GetLower() );
/*N*/   }
/*N*/   return aRange;
/*N*/ }

/*N*/ EditPaM ImpEditEngine::GetPaM( ParaPortion* pPortion, Point aDocPos, BOOL bSmart )
/*N*/ {
/*N*/   DBG_ASSERT( pPortion->IsVisible(), "Wozu GetPaM() bei einem unsichtbaren Absatz?" );
/*N*/   DBG_ASSERT( IsFormatted(), "GetPaM: Nicht formatiert" );
/*N*/
/*N*/   USHORT nCurIndex = 0;
/*N*/   EditPaM aPaM;
/*N*/   aPaM.SetNode( pPortion->GetNode() );
/*N*/
/*N*/   const SvxLineSpacingItem& rLSItem = (const SvxLineSpacingItem&)pPortion->GetNode()->GetContentAttribs().GetItem( EE_PARA_SBL );
/*N*/   USHORT nSBL = ( rLSItem.GetInterLineSpaceRule() == SVX_INTER_LINE_SPACE_FIX )
/*N*/                       ? GetYValue( rLSItem.GetInterLineSpace() ) : 0;
/*N*/
/*N*/   long nY = pPortion->GetFirstLineOffset();
/*N*/
/*N*/   DBG_ASSERT( pPortion->GetLines().Count(), "Leere ParaPortion in GetPaM!" );
/*N*/
/*N*/   EditLine* pLine = 0;
/*N*/   for ( USHORT nLine = 0; nLine < pPortion->GetLines().Count(); nLine++ )
/*N*/   {
/*N*/       EditLine* pTmpLine = pPortion->GetLines().GetObject( nLine );
/*N*/       nY += pTmpLine->GetHeight();
/*N*/       if ( !aStatus.IsOutliner() )
/*N*/           nY += nSBL;
/*N*/       if ( nY > aDocPos.Y() )     // das war 'se
/*N*/       {
/*N*/           pLine = pTmpLine;
/*N*/           break;                  // richtige Y-Position intressiert nicht
/*N*/       }
/*N*/
/*?*/       nCurIndex += pTmpLine->GetLen();
/*N*/   }
/*N*/
/*N*/   if ( !pLine ) // darf nur im Bereich von SA passieren!
/*N*/   {
/*?*/       #ifdef DBG_UTIL
/*?*/        const SvxULSpaceItem& rULSpace =(const SvxULSpaceItem&)pPortion->GetNode()->GetContentAttribs().GetItem( EE_PARA_ULSPACE );
/*?*/        DBG_ASSERT( nY+GetYValue( rULSpace.GetLower() ) >= aDocPos.Y() , "Index in keiner Zeile, GetPaM ?" );
/*?*/       #endif
/*?*/       aPaM.SetIndex( pPortion->GetNode()->Len() );
/*?*/       return aPaM;
/*N*/   }
/*N*/
/*N*/   // Wenn Zeile gefunden, nur noch X-Position => Index
/*N*/   nCurIndex = GetChar( pPortion, pLine, aDocPos.X(), bSmart );
/*N*/   aPaM.SetIndex( nCurIndex );
/*N*/
/*N*/   if ( nCurIndex && ( nCurIndex == pLine->GetEnd() ) &&
/*N*/        ( pLine != pPortion->GetLines().GetObject( pPortion->GetLines().Count()-1) ) )
/*N*/     {
/*?*/         DBG_ASSERT(0, "STRIP"); //STRIP001 aPaM = CursorLeft( aPaM, ::com::sun::star::i18n::CharacterIteratorMode::SKIPCELL );
/*N*/     }
/*N*/
/*N*/   return aPaM;
/*N*/ }

/*N*/ USHORT ImpEditEngine::GetChar( ParaPortion* pParaPortion, EditLine* pLine, long nXPos, BOOL bSmart )
/*N*/ {
/*N*/   DBG_ASSERT( pLine, "Keine Zeile erhalten: GetChar" );
/*N*/
/*N*/     USHORT nChar = 0xFFFF;
/*N*/     USHORT nCurIndex = pLine->GetStart();
/*N*/
/*N*/
/*N*/     // Search best matching portion with GetPortionXOffset()
/*N*/     for ( USHORT i = pLine->GetStartPortion(); i <= pLine->GetEndPortion(); i++ )
/*N*/   {
/*N*/       TextPortion* pPortion = pParaPortion->GetTextPortions().GetObject( i );
/*N*/         long nXLeft = GetPortionXOffset( pParaPortion, pLine, i );
/*N*/         long nXRight = nXLeft + pPortion->GetSize().Width();
/*N*/         if ( ( nXLeft <= nXPos ) && ( nXRight >= nXPos ) )
/*N*/         {
/*N*/              nChar = nCurIndex;
/*N*/
/*N*/             // Search within Portion...
/*N*/
/*N*/             // Don't search within special portions...
/*N*/           if ( pPortion->GetKind() != PORTIONKIND_TEXT )
/*N*/           {
/*?*/                 // ...but check on which side
/*?*/                 if ( bSmart )
/*?*/                 {
/*?*/                   long nLeftDiff = nXPos-nXLeft;
/*?*/                   long nRightDiff = nXRight-nXPos;
/*?*/                   if ( nRightDiff < nLeftDiff )
/*?*/                       nChar++;
/*?*/                 }
/*N*/           }
/*N*/             else
/*N*/             {
/*N*/               USHORT nMax = pPortion->GetLen();
/*N*/               USHORT nOffset = 0xFFFF;
/*N*/               USHORT nTmpCurIndex = nChar - pLine->GetStart();
/*N*/
/*N*/                 long nXInPortion = nXPos - nXLeft;
/*N*/                 if ( pPortion->IsRightToLeft() )
/*?*/                     nXInPortion = nXRight - nXPos;
/*N*/
/*N*/                 // Search in Array...
/*N*/               for ( USHORT x = 0; x < nMax; x++ )
/*N*/               {
/*N*/                   long nTmpPosMax = pLine->GetCharPosArray().GetObject( nTmpCurIndex+x );
/*N*/                   if ( nTmpPosMax > nXInPortion )
/*N*/                   {
/*N*/                       // pruefen, ob dieser oder der davor...
/*N*/                         long nTmpPosMin = x ? pLine->GetCharPosArray().GetObject( nTmpCurIndex+x-1 ) : 0;
/*N*/                       long nDiffLeft = nXInPortion - nTmpPosMin;
/*N*/                       long nDiffRight = nTmpPosMax - nXInPortion;
/*N*/                       DBG_ASSERT( nDiffLeft >= 0, "DiffLeft negativ" );
/*N*/                       DBG_ASSERT( nDiffRight >= 0, "DiffRight negativ" );
/*N*/                       nOffset = ( bSmart && ( nDiffRight < nDiffLeft ) ) ? x+1 : x;
/*N*/                       // I18N: If there are character position with the length of 0,
/*N*/                         // they belong to the same character, we can not use this position as an index.
/*N*/                       // Skip all 0-positions, cheaper than using XBreakIterator:
/*N*/                       if ( nOffset < nMax )
/*N*/                       {
/*N*/                           const long nX = pLine->GetCharPosArray().GetObject(nOffset);
/*N*/                           while ( ( (nOffset+1) < nMax ) && ( pLine->GetCharPosArray().GetObject(nOffset+1) == nX ) )
/*N*/                               nOffset++;
/*N*/                       }
/*N*/                       break;
/*N*/                   }
/*N*/               }
/*N*/
/*N*/               // Bei Verwendung des CharPosArray duerfte es keine Ungenauigkeiten geben!
/*N*/               // Vielleicht bei Kerning ?
/*N*/               // 0xFFF passiert z.B. bei Outline-Font, wenn ganz hinten.
/*N*/               if ( nOffset == 0xFFFF )
/*N*/                   nOffset = nMax;
/*N*/
/*N*/               DBG_ASSERT( nOffset <= nMax, "nOffset > nMax" );
/*N*/
/*N*/                 nChar += nOffset;
/*N*/
/*N*/                 // Check if index is within a cell:
/*N*/                 if ( nChar && ( nChar < pParaPortion->GetNode()->Len() ) )
/*N*/                 {
/*N*/                     EditPaM aPaM( pParaPortion->GetNode(), nChar+1 );
/*N*/                     USHORT nScriptType = GetScriptType( aPaM );
/*N*/                     if ( nScriptType == i18n::ScriptType::COMPLEX )
/*N*/                     {
/*?*/                       uno::Reference < i18n::XBreakIterator > xBI = ImplGetBreakIterator();
/*?*/                       sal_Int32 nCount = 1;
/*?*/                         lang::Locale aLocale = GetLocale( aPaM );
/*?*/                         USHORT nRight = (USHORT)xBI->nextCharacters( *pParaPortion->GetNode(), nChar, aLocale, ::com::sun::star::i18n::CharacterIteratorMode::SKIPCELL, nCount, nCount );
/*?*/                         USHORT nLeft = (USHORT)xBI->previousCharacters( *pParaPortion->GetNode(), nRight, aLocale, ::com::sun::star::i18n::CharacterIteratorMode::SKIPCELL, nCount, nCount );
/*?*/                         if ( ( nLeft != nChar ) && ( nRight != nChar ) )
/*?*/                         {
/*?*/                             nChar = ( Abs( nRight - nChar ) < Abs( nLeft - nChar ) ) ? nRight : nLeft;
/*?*/                         }
/*N*/                     }
/*N*/                 }
/*N*/             }
/*N*/         }
/*N*/
/*N*/         nCurIndex += pPortion->GetLen();
/*N*/     }
/*N*/
/*N*/     if ( nChar == 0xFFFF )
/*N*/     {
/*?*/         nChar = ( nXPos <= pLine->GetStartPosX() ) ? pLine->GetStart() : pLine->GetEnd();
/*N*/     }
/*N*/
/*N*/     return nChar;
/*N*/ }

/*N*/ Range ImpEditEngine::GetLineXPosStartEnd( ParaPortion* pParaPortion, EditLine* pLine )
/*N*/ {
/*N*/     Range aLineXPosStartEnd;
/*N*/
/*N*/     USHORT nPara = GetEditDoc().GetPos( pParaPortion->GetNode() );
/*N*/     if ( !IsRightToLeft( nPara ) )
/*N*/     {
/*N*/         aLineXPosStartEnd.Min() = pLine->GetStartPosX();
/*N*/         aLineXPosStartEnd.Max() = pLine->GetStartPosX() + pLine->GetTextWidth();
/*N*/     }
/*N*/     else
/*N*/     {
/*?*/         aLineXPosStartEnd.Min() = GetPaperSize().Width() - ( pLine->GetStartPosX() + pLine->GetTextWidth() );
/*?*/         aLineXPosStartEnd.Max() = GetPaperSize().Width() - pLine->GetStartPosX();
/*N*/     }
/*N*/
/*N*/
/*N*/     return aLineXPosStartEnd;
/*N*/ }

/*N*/ long ImpEditEngine::GetPortionXOffset( ParaPortion* pParaPortion, EditLine* pLine, USHORT nTextPortion )
/*N*/ {
/*N*/   long nX = pLine->GetStartPosX();
/*N*/
/*N*/     for ( USHORT i = pLine->GetStartPortion(); i < nTextPortion; i++ )
/*N*/   {
/*N*/       TextPortion* pPortion = pParaPortion->GetTextPortions().GetObject( i );
/*N*/       switch ( pPortion->GetKind() )
/*N*/       {
/*N*/           case PORTIONKIND_FIELD:
/*N*/           case PORTIONKIND_TEXT:
/*N*/           case PORTIONKIND_HYPHENATOR:
/*N*/           case PORTIONKIND_TAB:
/*N*/ //            case PORTIONKIND_EXTRASPACE:
/*N*/           {
/*N*/               nX += pPortion->GetSize().Width();
/*N*/           }
/*N*/           break;
/*N*/       }
/*N*/     }
/*N*/
/*N*/     USHORT nPara = GetEditDoc().GetPos( pParaPortion->GetNode() );
/*N*/     BOOL bR2LPara = IsRightToLeft( nPara );
/*N*/
/*N*/     TextPortion* pDestPortion = pParaPortion->GetTextPortions().GetObject( nTextPortion );
/*N*/     if ( pDestPortion->GetKind() != PORTIONKIND_TAB )
/*N*/     {
/*N*/         if ( !bR2LPara && pDestPortion->GetRightToLeft() )
/*N*/         {
/*?*/             // Portions behind must be added, visual before this portion
/*?*/             sal_uInt16 nTmpPortion = nTextPortion+1;
/*?*/             while ( nTmpPortion <= pLine->GetEndPortion() )
/*?*/             {
/*?*/               TextPortion* pNextTextPortion = pParaPortion->GetTextPortions().GetObject( nTmpPortion );
/*?*/                 if ( pNextTextPortion->GetRightToLeft() && ( pNextTextPortion->GetKind() != PORTIONKIND_TAB ) )
/*?*/                     nX += pNextTextPortion->GetSize().Width();
/*?*/                 else
/*?*/                     break;
/*?*/                 nTmpPortion++;
/*?*/             }
/*?*/             // Portions before must be removed, visual behind this portion
/*?*/             nTmpPortion = nTextPortion;
/*?*/             while ( nTmpPortion > pLine->GetStartPortion() )
/*?*/             {
/*?*/                 --nTmpPortion;
/*?*/               TextPortion* pPrevTextPortion = pParaPortion->GetTextPortions().GetObject( nTmpPortion );
/*?*/                 if ( pPrevTextPortion->GetRightToLeft() && ( pPrevTextPortion->GetKind() != PORTIONKIND_TAB ) )
/*?*/                     nX -= pPrevTextPortion->GetSize().Width();
/*?*/                 else
/*?*/                     break;
/*?*/             }
/*N*/         }
/*N*/         else if ( bR2LPara && !pDestPortion->IsRightToLeft() )
/*N*/         {
/*?*/             // Portions behind must be ermoved, visual behind this portion
/*?*/             sal_uInt16 nTmpPortion = nTextPortion+1;
/*?*/             while ( nTmpPortion <= pLine->GetEndPortion() )
/*?*/             {
/*?*/               TextPortion* pNextTextPortion = pParaPortion->GetTextPortions().GetObject( nTmpPortion );
/*?*/                 if ( !pNextTextPortion->IsRightToLeft() && ( pNextTextPortion->GetKind() != PORTIONKIND_TAB ) )
/*?*/                     nX += pNextTextPortion->GetSize().Width();
/*?*/                 else
/*?*/                     break;
/*?*/                 nTmpPortion++;
/*?*/             }
/*?*/             // Portions before must be added, visual before this portion
/*?*/             nTmpPortion = nTextPortion;
/*?*/             while ( nTmpPortion > pLine->GetStartPortion() )
/*?*/             {
/*?*/                 --nTmpPortion;
/*?*/               TextPortion* pPrevTextPortion = pParaPortion->GetTextPortions().GetObject( nTmpPortion );
/*?*/                 if ( !pPrevTextPortion->IsRightToLeft() && ( pPrevTextPortion->GetKind() != PORTIONKIND_TAB ) )
/*?*/                     nX -= pPrevTextPortion->GetSize().Width();
/*?*/                 else
/*?*/                     break;
/*?*/             }
/*N*/         }
/*N*/     }
/*N*/     if ( bR2LPara )
/*N*/     {
/*?*/         // Switch X postions...
/*?*/         DBG_ASSERT( GetTextRanger() || GetPaperSize().Width(), "GetPortionXOffset - paper size?!" );
/*?*/         DBG_ASSERT( GetTextRanger() || (nX <= GetPaperSize().Width()), "GetPortionXOffset - position out of paper size!" );
/*?*/         nX = GetPaperSize().Width() - nX;
/*?*/         nX -= pDestPortion->GetSize().Width();
/*N*/     }
/*N*/
/*N*/     return nX;
/*N*/ }

//STRIP001 long ImpEditEngine::GetXPos( ParaPortion* pParaPortion, EditLine* pLine, USHORT nIndex, BOOL bPreferPortionStart )
//STRIP001 {
//STRIP001  DBG_ASSERT( pLine, "Keine Zeile erhalten: GetXPos" );
//STRIP001  DBG_ASSERT( ( nIndex >= pLine->GetStart() ) && ( nIndex <= pLine->GetEnd() ) , "GetXPos muss richtig gerufen werden!" );
//STRIP001
//STRIP001     BOOL bDoPreferPortionStart = bPreferPortionStart;
//STRIP001     // Assure that the portion belongs to this line:
//STRIP001     if ( nIndex == pLine->GetStart() )
//STRIP001         bDoPreferPortionStart = TRUE;
//STRIP001     else if ( nIndex == pLine->GetEnd() )
//STRIP001         bDoPreferPortionStart = FALSE;
//STRIP001
//STRIP001     USHORT nTextPortionStart = 0;
//STRIP001     USHORT nTextPortion = pParaPortion->GetTextPortions().FindPortion( nIndex, nTextPortionStart, bDoPreferPortionStart );
//STRIP001
//STRIP001     DBG_ASSERT( ( nTextPortion >= pLine->GetStartPortion() ) && ( nTextPortion <= pLine->GetEndPortion() ), "GetXPos: Portion not in current line! " );
//STRIP001
//STRIP001     TextPortion* pPortion = pParaPortion->GetTextPortions().GetObject( nTextPortion );
//STRIP001
//STRIP001     long nX = GetPortionXOffset( pParaPortion, pLine, nTextPortion );
//STRIP001
//STRIP001     // calc text width, portion size may include CJK/CTL spacing...
//STRIP001     // But the array migh not be init yet, if using text ranger this method is called within CreateLines()...
//STRIP001     long nPortionTextWidth = pPortion->GetSize().Width();
//STRIP001     if ( ( pPortion->GetKind() == PORTIONKIND_TEXT ) && pPortion->GetLen() && !GetTextRanger() )
//STRIP001         nPortionTextWidth = pLine->GetCharPosArray().GetObject( nTextPortionStart + pPortion->GetLen() - 1 - pLine->GetStart() );
//STRIP001
//STRIP001     if ( nTextPortionStart != nIndex )
//STRIP001     {
//STRIP001         // Search within portion...
//STRIP001         if ( nIndex == ( nTextPortionStart + pPortion->GetLen() ) )
//STRIP001         {
//STRIP001             // End of Portion
//STRIP001             if ( pPortion->GetKind() == PORTIONKIND_TAB )
//STRIP001             {
//STRIP001                 if ( (nTextPortion+1) < pParaPortion->GetTextPortions().Count() )
//STRIP001                 {
//STRIP001                     TextPortion* pNextPortion = pParaPortion->GetTextPortions().GetObject( nTextPortion+1 );
//STRIP001                     if ( pNextPortion->GetKind() != PORTIONKIND_TAB )
//STRIP001                     {
//STRIP001                         // DBG_ASSERT( !bPreferPortionStart, "GetXPos - How can we this tab portion here???" );
//STRIP001                      // #109879# We loop if nIndex == pLine->GetEnd, because bPreferPortionStart will be reset
//STRIP001                      if ( !bPreferPortionStart )
//STRIP001                          nX = GetXPos( pParaPortion, pLine, nIndex, TRUE );
//STRIP001                      else if ( !IsRightToLeft( GetEditDoc().GetPos( pParaPortion->GetNode() ) ) )
//STRIP001                          nX += nPortionTextWidth;
//STRIP001                     }
//STRIP001                 }
//STRIP001                 else if ( !IsRightToLeft( GetEditDoc().GetPos( pParaPortion->GetNode() ) ) )
//STRIP001                 {
//STRIP001                  nX += nPortionTextWidth;
//STRIP001                 }
//STRIP001             }
//STRIP001             else if ( !pPortion->IsRightToLeft() )
//STRIP001             {
//STRIP001              nX += nPortionTextWidth;
//STRIP001             }
//STRIP001         }
//STRIP001         else if ( pPortion->GetKind() == PORTIONKIND_TEXT )
//STRIP001         {
//STRIP001          DBG_ASSERT( nIndex != pLine->GetStart(), "Strange behavior in new GetXPos()" );
//STRIP001
//STRIP001             long nPosInPortion = pLine->GetCharPosArray().GetObject( nIndex - 1 - pLine->GetStart() );
//STRIP001
//STRIP001             if ( !pPortion->IsRightToLeft() )
//STRIP001             {
//STRIP001              nX += nPosInPortion;
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001              nX += nPortionTextWidth - nPosInPortion;
//STRIP001             }
//STRIP001
//STRIP001             if ( pPortion->GetExtraInfos() && pPortion->GetExtraInfos()->bCompressed )
//STRIP001             {
//STRIP001                 nX += pPortion->GetExtraInfos()->nPortionOffsetX;
//STRIP001                 if ( pPortion->GetExtraInfos()->nAsianCompressionTypes & CHAR_PUNCTUATIONRIGHT )
//STRIP001                 {
//STRIP001                     BYTE nType = GetCharTypeForCompression( pParaPortion->GetNode()->GetChar( nIndex ) );
//STRIP001                     if ( nType == CHAR_PUNCTUATIONRIGHT )
//STRIP001                     {
//STRIP001                         USHORT n = nIndex - nTextPortionStart;
//STRIP001                         const long* pDXArray = pLine->GetCharPosArray().GetData()+( nTextPortionStart-pLine->GetStart() );
//STRIP001                         long nCharWidth = ( ( (n+1) < pPortion->GetLen() ) ? pDXArray[n] : pPortion->GetSize().Width() )
//STRIP001                                                         - ( n ? pDXArray[n-1] : 0 );
//STRIP001                         if ( (n+1) < pPortion->GetLen() )
//STRIP001                         {
//STRIP001                             // smaller, when char behind is CHAR_PUNCTUATIONRIGHT also
//STRIP001                             nType = GetCharTypeForCompression( pParaPortion->GetNode()->GetChar( nIndex+1 ) );
//STRIP001                             if ( nType == CHAR_PUNCTUATIONRIGHT )
//STRIP001                             {
//STRIP001                                 long nNextCharWidth = ( ( (n+2) < pPortion->GetLen() ) ? pDXArray[n+1] : pPortion->GetSize().Width() )
//STRIP001                                                                 - pDXArray[n];
//STRIP001                                 long nCompressed = nNextCharWidth/2;
//STRIP001                                 nCompressed *= pPortion->GetExtraInfos()->nMaxCompression100thPercent;
//STRIP001                                 nCompressed /= 10000;
//STRIP001                                 nCharWidth += nCompressed;
//STRIP001                             }
//STRIP001                         }
//STRIP001                         else
//STRIP001                         {
//STRIP001                             nCharWidth *= 2;    // last char pos to portion end is only compressed size
//STRIP001                         }
//STRIP001                         nX += nCharWidth/2; // 50% compression
//STRIP001                     }
//STRIP001                 }
//STRIP001             }
//STRIP001      }
//STRIP001     }
//STRIP001     else // if ( nIndex == pLine->GetStart() )
//STRIP001     {
//STRIP001         if ( pPortion->IsRightToLeft() )
//STRIP001         {
//STRIP001          nX += nPortionTextWidth;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001  return nX;
//STRIP001 }

/*N*/ void ImpEditEngine::CalcHeight( ParaPortion* pPortion )
/*N*/ {
/*N*/   pPortion->nHeight = 0;
/*N*/   pPortion->nFirstLineOffset = 0;
/*N*/
/*N*/   if ( pPortion->IsVisible() )
/*N*/   {
/*N*/       DBG_ASSERT( pPortion->GetLines().Count(), "Absatz ohne Zeilen in ParaPortion::CalcHeight" );
/*N*/       for ( USHORT nLine = 0; nLine < pPortion->GetLines().Count(); nLine++ )
/*N*/           pPortion->nHeight += pPortion->GetLines().GetObject( nLine )->GetHeight();
/*N*/
/*N*/       if ( !aStatus.IsOutliner() )
/*N*/       {
/*N*/           const SvxULSpaceItem& rULItem = (const SvxULSpaceItem&)pPortion->GetNode()->GetContentAttribs().GetItem( EE_PARA_ULSPACE );
/*N*/           const SvxLineSpacingItem& rLSItem = (const SvxLineSpacingItem&)pPortion->GetNode()->GetContentAttribs().GetItem( EE_PARA_SBL );
/*N*/           USHORT nSBL = ( rLSItem.GetInterLineSpaceRule() == SVX_INTER_LINE_SPACE_FIX ) ? GetYValue( rLSItem.GetInterLineSpace() ) : 0;
/*N*/
/*N*/           if ( nSBL )
/*N*/           {
/*?*/               if ( pPortion->GetLines().Count() > 1 )
/*?*/                   pPortion->nHeight += ( pPortion->GetLines().Count() - 1 ) * nSBL;
/*?*/               if ( aStatus.ULSpaceSummation() )
/*?*/                   pPortion->nHeight += nSBL;
/*N*/           }
/*N*/
/*N*/           USHORT nPortion = GetParaPortions().GetPos( pPortion );
/*N*/           if ( nPortion || aStatus.ULSpaceFirstParagraph() )
/*N*/           {
/*N*/               USHORT nUpper = GetYValue( rULItem.GetUpper() );
/*N*/               pPortion->nHeight += nUpper;
/*N*/               pPortion->nFirstLineOffset = nUpper;
/*N*/           }
/*N*/
/*N*/           if ( ( nPortion != (GetParaPortions().Count()-1) ) )
/*N*/           {
/*N*/               pPortion->nHeight += GetYValue( rULItem.GetLower() );   // nicht in letzter
/*N*/           }
/*N*/
/*N*/
/*N*/           if ( nPortion && !aStatus.ULSpaceSummation() )
/*N*/           {
/*N*/               ParaPortion* pPrev = GetParaPortions().SaveGetObject( nPortion-1 );
/*N*/               const SvxULSpaceItem& rPrevULItem = (const SvxULSpaceItem&)pPrev->GetNode()->GetContentAttribs().GetItem( EE_PARA_ULSPACE );
/*N*/               const SvxLineSpacingItem& rPrevLSItem = (const SvxLineSpacingItem&)pPrev->GetNode()->GetContentAttribs().GetItem( EE_PARA_SBL );
/*N*/
/*N*/               // Verhalten WinWord6/Writer3:
/*N*/               // Bei einem proportionalen Zeilenabstand wird auch der Absatzabstand
/*N*/               // manipuliert.
/*N*/               // Nur Writer3: Nicht aufaddieren, sondern Mindestabstand.
/*N*/
/*N*/               // Pruefen, ob Abstand durch LineSpacing > Upper:
/*N*/               USHORT nExtraSpace = GetYValue( lcl_CalcExtraSpace( pPortion, rLSItem ) );
/*N*/               if ( nExtraSpace > pPortion->nFirstLineOffset )
/*N*/               {
/*?*/                   // Absatz wird 'groesser':
/*?*/                   pPortion->nHeight += ( nExtraSpace - pPortion->nFirstLineOffset );
/*?*/                   pPortion->nFirstLineOffset = nExtraSpace;
/*N*/               }
/*N*/
/*N*/               // nFirstLineOffset jetzt f(pNode) => jetzt f(pNode, pPrev) ermitteln:
/*N*/               USHORT nPrevLower = GetYValue( rPrevULItem.GetLower() );
/*N*/
/*N*/               // Dieser PrevLower steckt noch in der Hoehe der PrevPortion...
/*N*/               if ( nPrevLower > pPortion->nFirstLineOffset )
/*N*/               {
/*N*/                   // Absatz wird 'kleiner':
/*N*/                   pPortion->nHeight -= pPortion->nFirstLineOffset;
/*N*/                   pPortion->nFirstLineOffset = 0;
/*N*/               }
/*N*/               else if ( nPrevLower )
/*N*/               {
/*?*/                   // Absatz wird 'etwas kleiner':
/*?*/                   pPortion->nHeight -= nPrevLower;
/*?*/                   pPortion->nFirstLineOffset -= nPrevLower;
/*N*/               }
/*N*/
/*N*/               // Finde ich zwar nicht so gut, aber Writer3-Feature:
/*N*/               // Pruefen, ob Abstand durch LineSpacing > Lower:
/*N*/               // Dieser Wert steckt nicht in der Hoehe der PrevPortion.
/*N*/               if ( !pPrev->IsInvalid() )
/*N*/               {
/*N*/                   nExtraSpace = GetYValue( lcl_CalcExtraSpace( pPrev, rPrevLSItem ) );
/*N*/                   if ( nExtraSpace > nPrevLower )
/*N*/                   {
/*?*/                       USHORT nMoreLower = nExtraSpace - nPrevLower;
/*?*/                       // Absatz wird 'groesser', 'waechst' nach unten:
/*?*/                       if ( nMoreLower > pPortion->nFirstLineOffset )
/*?*/                       {
/*?*/                           pPortion->nHeight += ( nMoreLower - pPortion->nFirstLineOffset );
/*?*/                           pPortion->nFirstLineOffset = nMoreLower;
/*?*/                       }
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

//STRIP001 Rectangle ImpEditEngine::GetEditCursor( ParaPortion* pPortion, USHORT nIndex, USHORT nFlags )
//STRIP001 {
//STRIP001  DBG_ASSERT( pPortion->IsVisible(), "Wozu GetEditCursor() bei einem unsichtbaren Absatz?" );
//STRIP001  DBG_ASSERT( IsFormatted() || GetTextRanger(), "GetEditCursor: Nicht formatiert" );
//STRIP001
//STRIP001  /*
//STRIP001   GETCRSR_ENDOFLINE: Wenn hinter dem letzten Zeichen einer umgebrochenen Zeile,
//STRIP001   am Ende der Zeile bleiben, nicht am Anfang der naechsten.
//STRIP001   Zweck:     - END => wirklich hinter das letzte Zeichen
//STRIP001              - Selektion....
//STRIP001  */
//STRIP001
//STRIP001  long nY = pPortion->GetFirstLineOffset();
//STRIP001
//STRIP001  const SvxLineSpacingItem& rLSItem = (const SvxLineSpacingItem&)pPortion->GetNode()->GetContentAttribs().GetItem( EE_PARA_SBL );
//STRIP001  USHORT nSBL = ( rLSItem.GetInterLineSpaceRule() == SVX_INTER_LINE_SPACE_FIX )
//STRIP001                      ? GetYValue( rLSItem.GetInterLineSpace() ) : 0;
//STRIP001
//STRIP001  USHORT nCurIndex = 0;
//STRIP001  DBG_ASSERT( pPortion->GetLines().Count(), "Leere ParaPortion in GetEditCursor!" );
//STRIP001  EditLine* pLine = 0;
//STRIP001  BOOL bEOL = ( nFlags & GETCRSR_ENDOFLINE ) ? TRUE : FALSE;
//STRIP001  for ( USHORT nLine = 0; nLine < pPortion->GetLines().Count(); nLine++ )
//STRIP001  {
//STRIP001      EditLine* pTmpLine = pPortion->GetLines().GetObject( nLine );
//STRIP001      if ( ( pTmpLine->GetStart() == nIndex ) || ( pTmpLine->IsIn( nIndex, bEOL ) ) )
//STRIP001      {
//STRIP001          pLine = pTmpLine;
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      nCurIndex +=  pTmpLine->GetLen();
//STRIP001      nY += pTmpLine->GetHeight();
//STRIP001      if ( !aStatus.IsOutliner() )
//STRIP001          nY += nSBL;
//STRIP001  }
//STRIP001  if ( !pLine )
//STRIP001  {
//STRIP001      // Cursor am Ende des Absatzes.
//STRIP001      DBG_ASSERT( nIndex == nCurIndex, "Index voll daneben in GetEditCursor!" );
//STRIP001
//STRIP001      pLine = pPortion->GetLines().GetObject( pPortion->GetLines().Count()-1 );
//STRIP001      nY -= pLine->GetHeight();
//STRIP001      if ( !aStatus.IsOutliner() )
//STRIP001          nY -= nSBL;
//STRIP001      nCurIndex -=  pLine->GetLen();
//STRIP001  }
//STRIP001
//STRIP001  Rectangle aEditCursor;
//STRIP001
//STRIP001  aEditCursor.Top() = nY;
//STRIP001  nY += pLine->GetHeight();
//STRIP001  aEditCursor.Bottom() = nY-1;
//STRIP001
//STRIP001  // innerhalb der Zeile suchen...
//STRIP001     long nX;
//STRIP001
//STRIP001     if ( ( nIndex == pLine->GetStart() ) && ( nFlags & GETCRSR_STARTOFLINE ) )
//STRIP001     {
//STRIP001         Range aXRange = GetLineXPosStartEnd( pPortion, pLine );
//STRIP001         nX = !IsRightToLeft( GetEditDoc().GetPos( pPortion->GetNode() ) ) ? aXRange.Min() : aXRange.Max();
//STRIP001     }
//STRIP001     else if ( ( nIndex == pLine->GetEnd() ) && ( nFlags & GETCRSR_ENDOFLINE ) )
//STRIP001     {
//STRIP001         Range aXRange = GetLineXPosStartEnd( pPortion, pLine );
//STRIP001         nX = !IsRightToLeft( GetEditDoc().GetPos( pPortion->GetNode() ) ) ? aXRange.Max() : aXRange.Min();
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         nX = GetXPos( pPortion, pLine, nIndex, ( nFlags & GETCRSR_PREFERPORTIONSTART ) ? TRUE : FALSE );
//STRIP001     }
//STRIP001
//STRIP001     aEditCursor.Left() = aEditCursor.Right() = nX;
//STRIP001
//STRIP001  if ( nFlags & GETCRSR_TXTONLY )
//STRIP001      aEditCursor.Top() = aEditCursor.Bottom() - pLine->GetTxtHeight() + 1;
//STRIP001  else
//STRIP001      aEditCursor.Top() = aEditCursor.Bottom() - Min( pLine->GetTxtHeight(), pLine->GetHeight() ) + 1;
//STRIP001
//STRIP001  return aEditCursor;
//STRIP001 }

/*N*/ void ImpEditEngine::SetValidPaperSize( const Size& rNewSz )
/*N*/ {
/*N*/   aPaperSize = rNewSz;
/*N*/
/*N*/   long nMinWidth = aStatus.AutoPageWidth() ? aMinAutoPaperSize.Width() : 0;
/*N*/   long nMaxWidth = aStatus.AutoPageWidth() ? aMaxAutoPaperSize.Width() : 0x7FFFFFFF;
/*N*/   long nMinHeight = aStatus.AutoPageHeight() ? aMinAutoPaperSize.Height() : 0;
/*N*/   long nMaxHeight = aStatus.AutoPageHeight() ? aMaxAutoPaperSize.Height() : 0x7FFFFFFF;
/*N*/
/*N*/   // Minimale/Maximale Breite:
/*N*/   if ( aPaperSize.Width() < nMinWidth )
/*N*/       aPaperSize.Width() = nMinWidth;
/*N*/   else if ( aPaperSize.Width() > nMaxWidth )
/*?*/       aPaperSize.Width() = nMaxWidth;
/*N*/
/*N*/   // Minimale/Maximale Hoehe:
/*N*/   if ( aPaperSize.Height() < nMinHeight )
/*?*/       aPaperSize.Height() = nMinHeight;
/*N*/   else if ( aPaperSize.Height() > nMaxHeight )
/*?*/       aPaperSize.Height() = nMaxHeight;
/*N*/ }

//STRIP001 void ImpEditEngine::IndentBlock( EditView* pEditView, BOOL bRight )
//STRIP001 {
//STRIP001  ESelection aESel( CreateESel( pEditView->pImpEditView->GetEditSelection() ) );
//STRIP001  aESel.Adjust();
//STRIP001
//STRIP001  // Nur wenn mehrere selektierte Absaetze...
//STRIP001  if ( aESel.nEndPara > aESel.nStartPara )
//STRIP001  {
//STRIP001      ESelection aNewSel = aESel;
//STRIP001      aNewSel.nStartPos = 0;
//STRIP001      aNewSel.nEndPos = 0xFFFF;
//STRIP001
//STRIP001      if ( aESel.nEndPos == 0 )
//STRIP001      {
//STRIP001          aESel.nEndPara--;       // dann diesen Absatz nicht...
//STRIP001          aNewSel.nEndPos = 0;
//STRIP001      }
//STRIP001
//STRIP001      pEditView->pImpEditView->DrawSelection();
//STRIP001      pEditView->pImpEditView->SetEditSelection(
//STRIP001                      pEditView->pImpEditView->GetEditSelection().Max() );
//STRIP001      UndoActionStart( bRight ? EDITUNDO_INDENTBLOCK : EDITUNDO_UNINDENTBLOCK );
//STRIP001
//STRIP001      for ( USHORT nPara = aESel.nStartPara; nPara <= aESel.nEndPara; nPara++ )
//STRIP001      {
//STRIP001          ContentNode* pNode = GetEditDoc().GetObject( nPara );
//STRIP001          if ( bRight )
//STRIP001          {
//STRIP001              // Tabs hinzufuegen
//STRIP001              EditPaM aPaM( pNode, 0 );
//STRIP001              InsertTab( aPaM );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              // Tabs entfernen
//STRIP001              EditCharAttrib* pFeature = pNode->GetCharAttribs().FindFeature( 0 );
//STRIP001              if ( pFeature && ( pFeature->GetStart() == 0 ) &&
//STRIP001                 ( pFeature->GetItem()->Which() == EE_FEATURE_TAB ) )
//STRIP001              {
//STRIP001                  EditPaM aStartPaM( pNode, 0 );
//STRIP001                  EditPaM aEndPaM( pNode, 1 );
//STRIP001                  ImpDeleteSelection( EditSelection( aStartPaM, aEndPaM ) );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      UndoActionEnd( bRight ? EDITUNDO_INDENTBLOCK : EDITUNDO_UNINDENTBLOCK );
//STRIP001      UpdateSelections();
//STRIP001      FormatAndUpdate( pEditView );
//STRIP001
//STRIP001      ContentNode* pLastNode = GetEditDoc().GetObject( aNewSel.nEndPara );
//STRIP001      if ( pLastNode->Len() < aNewSel.nEndPos )
//STRIP001          aNewSel.nEndPos = pLastNode->Len();
//STRIP001      pEditView->pImpEditView->SetEditSelection( CreateSel( aNewSel ) );
//STRIP001      pEditView->pImpEditView->DrawSelection();
//STRIP001      pEditView->pImpEditView->ShowCursor( FALSE, TRUE );
//STRIP001  }
//STRIP001 }

/*N*/ vos::ORef<SvxForbiddenCharactersTable> ImpEditEngine::GetForbiddenCharsTable( BOOL bGetInternal ) const
/*N*/ {
/*N*/   vos::ORef<SvxForbiddenCharactersTable> xF = xForbiddenCharsTable;
/*N*/   if ( !xF.isValid() && bGetInternal )
/*N*/       xF = EE_DLL()->GetGlobalData()->GetForbiddenCharsTable();
/*N*/   return xF;
/*N*/ }

/*N*/ void ImpEditEngine::SetForbiddenCharsTable( vos::ORef<SvxForbiddenCharactersTable> xForbiddenChars )
/*N*/ {
/*N*/   EE_DLL()->GetGlobalData()->SetForbiddenCharsTable( xForbiddenChars );
/*N*/ }

/*N*/ svtools::ColorConfig& ImpEditEngine::GetColorConfig()
/*N*/ {
/*N*/     if ( !pColorConfig )
/*N*/         pColorConfig = new svtools::ColorConfig;
/*N*/
/*N*/     return *pColorConfig;
/*N*/ }

//STRIP001 BOOL ImpEditEngine::IsVisualCursorTravelingEnabled()
//STRIP001 {
//STRIP001     BOOL bVisualCursorTravaling = FALSE;
//STRIP001
//STRIP001     if( !pCTLOptions )
//STRIP001         pCTLOptions = new SvtCTLOptions;
//STRIP001
//STRIP001     if ( pCTLOptions->IsCTLFontEnabled() && ( pCTLOptions->GetCTLCursorMovement() == SvtCTLOptions::MOVEMENT_VISUAL ) )
//STRIP001     {
//STRIP001         bVisualCursorTravaling = TRUE;
//STRIP001     }
//STRIP001
//STRIP001     return bVisualCursorTravaling;
//STRIP001
//STRIP001 }

//STRIP001 BOOL ImpEditEngine::DoVisualCursorTraveling( const ContentNode* pNode )
//STRIP001 {
//STRIP001     // Don't check if it's necessary, because we also need it when leaving the paragraph
//STRIP001     return IsVisualCursorTravelingEnabled();
//STRIP001 /*
//STRIP001     BOOL bDoVisualCursorTraveling = FALSE;
//STRIP001
//STRIP001     if ( IsVisualCursorTravelingEnabled() && pNode->Len() )
//STRIP001     {
//STRIP001         // Only necessary when RTL text in LTR para or LTR text in RTL para
//STRIP001         bDoVisualCursorTraveling = HasDifferentRTLLevels( pNode );
//STRIP001     }
//STRIP001
//STRIP001     return bDoVisualCursorTraveling;
//STRIP001 */
//STRIP001 }


//STRIP001 void ImpEditEngine::CallNotify( EENotify& rNotify )
//STRIP001 {
//STRIP001     if ( !nBlockNotifications )
//STRIP001     {
//STRIP001         GetNotifyHdl().Call( &rNotify );
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         EENotify* pNewNotify = new EENotify( rNotify );
//STRIP001         aNotifyCache.Insert( pNewNotify, aNotifyCache.Count() );
//STRIP001     }
//STRIP001 }

/*N*/ void ImpEditEngine::EnterBlockNotifications()
/*N*/ {
/*N*/     if( !nBlockNotifications )
/*N*/     {
/*N*/         // #109864# Send out START notification immediately, to allow
/*N*/         // external, non-queued events to be captured as well from
/*N*/         // client side
/*N*/         EENotify aNotify( EE_NOTIFY_BLOCKNOTIFICATION_START );
/*N*/         aNotify.pEditEngine = GetEditEnginePtr();
/*N*/         GetNotifyHdl().Call( &aNotify );
/*N*/     }
/*N*/
/*N*/     nBlockNotifications++;
/*N*/ }

/*N*/ void ImpEditEngine::LeaveBlockNotifications()
/*N*/ {
/*N*/     DBG_ASSERT( nBlockNotifications, "LeaveBlockNotifications - Why?" );
/*N*/
/*N*/     nBlockNotifications--;
/*N*/     if ( !nBlockNotifications )
/*N*/     {
/*N*/         // Call blocked notify events...
/*N*/         while ( aNotifyCache.Count() )
/*N*/         {
/*N*/             EENotify* pNotify = aNotifyCache[0];
/*N*/             // Remove from list before calling, maybe we enter LeaveBlockNotifications while calling the handler...
/*N*/             aNotifyCache.Remove( 0 );
/*N*/             GetNotifyHdl().Call( pNotify );
/*N*/             delete pNotify;
/*N*/         }
/*N*/
/*N*/         EENotify aNotify( EE_NOTIFY_BLOCKNOTIFICATION_END );
/*N*/         aNotify.pEditEngine = GetEditEnginePtr();
/*N*/         GetNotifyHdl().Call( &aNotify );
/*N*/     }
/*N*/ }

/*N*/ IMPL_LINK( ImpEditEngine, DocModified, void*, EMPTYARG )
/*N*/ {
/*N*/     aModifyHdl.Call( NULL /*GetEditEnginePtr()*/ ); // NULL, because also used for Outliner
/*N*/     return 0;
/*N*/ }
}
