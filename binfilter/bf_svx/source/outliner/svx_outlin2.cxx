/*************************************************************************
 *
 *  $RCSfile: svx_outlin2.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:16 $
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

#include <tools/list.hxx>

#ifndef _SFXSTYLE_HXX //autogen
#include <svtools/style.hxx>
#endif

#ifndef _SV_MAPMOD_HXX
#include <vcl/mapmod.hxx>
#endif

#include <forbiddencharacterstable.hxx>

#define _OUTLINER_CXX

#include <outliner.hxx>
#include <paralist.hxx>
#include <outlobj.hxx>
#include <outleeng.hxx>
#include <outlundo.hxx>
#include <eeitem.hxx>
#include <editstat.hxx>

DBG_NAMEEX(Outliner);

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::linguistic2;

// =====================================================================
// ======================   Einfache Durchreicher =======================
// ======================================================================

/*N*/ void Outliner::SetUpdateMode( BOOL bUpdate )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->SetUpdateMode( bUpdate );
/*N*/ }


/*N*/ BOOL Outliner::GetUpdateMode() const
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pEditEngine->GetUpdateMode();
/*N*/ }

/*N*/ const SfxItemSet& Outliner::GetEmptyItemSet() const
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pEditEngine->GetEmptyItemSet();
/*N*/ }

/*N*/ void Outliner::EnableUndo( BOOL bEnable )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->EnableUndo( bEnable );
/*N*/ }

/*N*/ BOOL Outliner::IsUndoEnabled() const
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pEditEngine->IsUndoEnabled();
/*N*/ }

/*N*/ MapMode   Outliner::GetRefMapMode() const
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pEditEngine->GetRefMapMode();
/*N*/ }

/*N*/ void Outliner::SetRefMapMode( const MapMode& rMMode )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->SetRefMapMode( rMMode );
/*N*/ }

/*N*/ void Outliner::SetBackgroundColor( const Color& rColor )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->SetBackgroundColor( rColor );
/*N*/ }

//STRIP001 Color Outliner::GetBackgroundColor() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pEditEngine->GetBackgroundColor();
//STRIP001 }


//STRIP001 void Outliner::ClearModifyFlag()
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  pEditEngine->ClearModifyFlag();
//STRIP001 }

//STRIP001 BOOL Outliner::IsModified() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pEditEngine->IsModified();
//STRIP001 }

/*N*/ ULONG Outliner::GetTextHeight() const
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pEditEngine->GetTextHeight();
/*N*/ }

//STRIP001 void Outliner::SetModifyHdl( const Link& rLink )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001     pEditEngine->SetModifyHdl( rLink );
//STRIP001 }

//STRIP001 Link Outliner::GetModifyHdl() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pEditEngine->GetModifyHdl();
//STRIP001 }

/*N*/ void Outliner::SetNotifyHdl( const Link& rLink )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/     pEditEngine->aOutlinerNotifyHdl = rLink;
/*N*/
/*N*/     if ( rLink.IsSet() )
/*?*/       {DBG_ASSERT(0, "STRIP");} //STRIP001 pEditEngine->SetNotifyHdl( LINK( this, Outliner, EditEngineNotifyHdl ) );
/*N*/     else
/*N*/       pEditEngine->SetNotifyHdl( Link() );
/*N*/
/*N*/ }

//STRIP001 Link Outliner::GetNotifyHdl() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pEditEngine->aOutlinerNotifyHdl;
//STRIP001 }

//STRIP001 void Outliner::SetStatusEventHdl( const Link& rLink )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  pEditEngine->SetStatusEventHdl( rLink );
//STRIP001 }

//STRIP001 Link Outliner::GetStatusEventHdl() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pEditEngine->GetStatusEventHdl();
//STRIP001 }

/*N*/ void Outliner::SetDefTab( USHORT nTab )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->SetDefTab( nTab );
/*N*/ }

//STRIP001 USHORT Outliner::GetDefTab() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pEditEngine->GetDefTab();
//STRIP001 }

//STRIP001 BOOL Outliner::IsFlatMode() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pEditEngine->IsFlatMode();
//STRIP001 }

/*N*/ BOOL Outliner::UpdateFields()
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pEditEngine->UpdateFields();
/*N*/ }

//STRIP001 void Outliner::RemoveFields( BOOL bKeepFieldText, TypeId aType )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  pEditEngine->RemoveFields( bKeepFieldText, aType );
//STRIP001 }

//STRIP001 void Outliner::SetWordDelimiters( const String& rDelimiters )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  pEditEngine->SetWordDelimiters( rDelimiters );
//STRIP001 }

//STRIP001 String Outliner::GetWordDelimiters() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pEditEngine->GetWordDelimiters();
//STRIP001 }

//STRIP001 String Outliner::GetWord( USHORT nPara, USHORT nIndex )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pEditEngine->GetWord( nPara, nIndex );
//STRIP001 }

//STRIP001 void Outliner::Draw( OutputDevice* pOutDev, const Rectangle& rOutRect )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  pEditEngine->Draw( pOutDev, rOutRect );
//STRIP001 }

//STRIP001 void Outliner::Draw( OutputDevice* pOutDev, const Rectangle& rOutRect, const Point& rStartDocPos )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  pEditEngine->Draw( pOutDev, rOutRect, rStartDocPos );
//STRIP001 }


//STRIP001 void Outliner::Draw( OutputDevice* pOutDev, const Point& rStartPos, short nOrientation )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  pEditEngine->Draw( pOutDev, rStartPos, nOrientation );
//STRIP001 }

/*N*/ void Outliner::SetPaperSize( const Size& rSize )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->SetPaperSize( rSize );
/*N*/ }

/*N*/ const Size& Outliner::GetPaperSize() const
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pEditEngine->GetPaperSize();
/*N*/ }

//STRIP001 void Outliner::SetPolygon( const XPolyPolygon& rPoly )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( Outliner, 0 );
//STRIP001  pEditEngine->SetPolygon( rPoly );
//STRIP001 }

//STRIP001 void Outliner::SetPolygon( const XPolyPolygon& rPoly, const XPolyPolygon* pXorPoly )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( Outliner, 0 );
//STRIP001  pEditEngine->SetPolygon( rPoly, pXorPoly );
//STRIP001 }

/*N*/ void Outliner::ClearPolygon()
/*N*/ {
/*N*/   DBG_CHKTHIS( Outliner, 0 );
/*N*/   pEditEngine->ClearPolygon();
/*N*/ }

//STRIP001 const PolyPolygon* Outliner::GetPolygon()
//STRIP001 {
//STRIP001  DBG_CHKTHIS( Outliner, 0 );
//STRIP001  return pEditEngine->GetPolygon();
//STRIP001 }

//STRIP001 const Size& Outliner::GetMinAutoPaperSize() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pEditEngine->GetMinAutoPaperSize();
//STRIP001 }

/*N*/ void Outliner::SetMinAutoPaperSize( const Size& rSz )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->SetMinAutoPaperSize( rSz );
/*N*/ }

//STRIP001 const Size& Outliner::GetMaxAutoPaperSize() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pEditEngine->GetMaxAutoPaperSize();
//STRIP001 }

/*N*/ void Outliner::SetMaxAutoPaperSize( const Size& rSz )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->SetMaxAutoPaperSize( rSz );
/*N*/ }

//STRIP001 BOOL Outliner::IsExpanded( Paragraph* pPara ) const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pParaList->HasVisibleChilds( pPara );
//STRIP001 }

//STRIP001 Paragraph* Outliner::GetParent( Paragraph* pParagraph ) const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  USHORT nRelPos;
//STRIP001  return pParaList->GetParent( pParagraph, nRelPos );
//STRIP001 }

//STRIP001 ULONG Outliner::GetChildCount( Paragraph* pParent ) const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pParaList->GetChildCount( pParent );
//STRIP001 }

/*N*/ Size Outliner::CalcTextSize()
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return Size(pEditEngine->CalcTextWidth(),pEditEngine->GetTextHeight());
/*N*/ }

//STRIP001 Point Outliner::GetDocPos( Paragraph* pPara )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pEditEngine->GetDocPosTopLeft( (USHORT)pParaList->GetAbsPos( pPara ) );
//STRIP001 }

/*N*/ void Outliner::SetStyleSheetPool( SfxStyleSheetPool* pSPool )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->SetStyleSheetPool( pSPool );
/*N*/ }

/*N*/ SfxStyleSheetPool* Outliner::GetStyleSheetPool()
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pEditEngine->GetStyleSheetPool();
/*N*/ }

/*N*/ SfxStyleSheet* Outliner::GetStyleSheet( ULONG nPara )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pEditEngine->GetStyleSheet( (USHORT)nPara );
/*N*/ }

/*N*/ BOOL Outliner::IsInSelectionMode() const
/*N*/ {DBG_ASSERT(0, "STRIP"); return FALSE; //STRIP001
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pEditEngine->IsInSelectionMode();
/*N*/ }

/*N*/ void Outliner::SetControlWord( ULONG nWord )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->SetControlWord( nWord );
/*N*/ }

/*N*/ ULONG Outliner::GetControlWord() const
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pEditEngine->GetControlWord();
/*N*/ }

/*N*/ void Outliner::SetAsianCompressionMode( USHORT n )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->SetAsianCompressionMode( n );
/*N*/ }

//STRIP001 USHORT Outliner::GetAsianCompressionMode() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pEditEngine->GetAsianCompressionMode();
//STRIP001 }

/*N*/ void Outliner::SetKernAsianPunctuation( BOOL b )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->SetKernAsianPunctuation( b );
/*N*/ }

//STRIP001 BOOL Outliner::IsKernAsianPunctuation() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pEditEngine->IsKernAsianPunctuation();
//STRIP001 }

/*N*/ void Outliner::UndoActionStart( USHORT nId )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->UndoActionStart( nId );
/*N*/ }

/*N*/ void Outliner::UndoActionEnd( USHORT nId )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->UndoActionEnd( nId );
/*N*/ }

//STRIP001 void Outliner::InsertUndo( EditUndo* pUndo )
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  pEditEngine->GetUndoManager().AddUndoAction( pUndo, FALSE );
//STRIP001 #endif
//STRIP001 }

/*N*/ BOOL Outliner::IsInUndo()
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pEditEngine->IsInUndo();
/*N*/ }

/*N*/ ULONG Outliner::GetLineCount( ULONG nParagraph ) const
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pEditEngine->GetLineCount( (USHORT)nParagraph );
/*N*/ }

/*N*/ USHORT Outliner::GetLineLen( ULONG nParagraph, USHORT nLine ) const
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pEditEngine->GetLineLen( (USHORT)nParagraph, nLine );
/*N*/ }

/*?*/ ULONG Outliner::GetLineHeight( ULONG nParagraph, ULONG nLine )
/*?*/ {
/*?*/   DBG_CHKTHIS(Outliner,0);
/*?*/   return pEditEngine->GetLineHeight( (USHORT)nParagraph, (USHORT)nLine );
/*?*/ }

/*N*/ void Outliner::QuickRemoveCharAttribs( USHORT nPara, USHORT nWhich )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->QuickRemoveCharAttribs( nPara, nWhich );
/*N*/ }

//STRIP001 EESpellState Outliner::HasSpellErrors( LanguageType eLang )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pEditEngine->HasSpellErrors( eLang );
//STRIP001 }

//STRIP001 EESpellState Outliner::HasSpellErrors()
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pEditEngine->HasSpellErrors();
//STRIP001 }

/*N*/ void Outliner::SetDefaultLanguage( LanguageType eLang )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->SetDefaultLanguage( eLang );
/*N*/ }

//STRIP001 LanguageType Outliner::GetDefaultLanguage() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pEditEngine->GetDefaultLanguage();
//STRIP001 }

//STRIP001 BOOL Outliner::HasOnlineSpellErrors() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pEditEngine->HasOnlineSpellErrors();
//STRIP001 }

//STRIP001 void Outliner::CompleteOnlineSpelling()
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  pEditEngine->CompleteOnlineSpelling();
//STRIP001 }

//STRIP001 BOOL Outliner::HasText( const SvxSearchItem& rSearchItem )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pEditEngine->HasText( rSearchItem );
//STRIP001 }

/*N*/ void Outliner::SetEditTextObjectPool( SfxItemPool* pPool )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->SetEditTextObjectPool( pPool );
/*N*/ }

/*N*/ SfxItemPool* Outliner::GetEditTextObjectPool() const
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pEditEngine->GetEditTextObjectPool();
/*N*/ }

//STRIP001 BOOL Outliner::SpellNextDocument()
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return FALSE;
//STRIP001 }


/*N*/ void Outliner::SetSpeller( Reference< XSpellChecker1 > &xSpeller )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->SetSpeller( xSpeller );
/*N*/ }
//STRIP001 Reference< XSpellChecker1 > Outliner::GetSpeller()
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pEditEngine->GetSpeller();
//STRIP001 }

/*N*/ void Outliner::SetForbiddenCharsTable( vos::ORef<SvxForbiddenCharactersTable> xForbiddenChars )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->SetForbiddenCharsTable( xForbiddenChars );
/*N*/ }

//STRIP001 vos::ORef<SvxForbiddenCharactersTable> Outliner::GetForbiddenCharsTable() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pEditEngine->GetForbiddenCharsTable();
//STRIP001 }


//STRIP001 Reference< XHyphenator > Outliner::GetHyphenator() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pEditEngine->GetHyphenator();
//STRIP001 }

/*N*/ void Outliner::SetHyphenator( Reference< XHyphenator >& xHyph )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->SetHyphenator( xHyph );
/*N*/ }

/*N*/ OutputDevice* Outliner::GetRefDevice() const
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pEditEngine->GetRefDevice();
/*N*/ }

//STRIP001 USHORT Outliner::GetFirstLineOffset( ULONG nParagraph )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pEditEngine->GetFirstLineOffset( (USHORT)nParagraph );
//STRIP001 }

/*N*/ ULONG Outliner::GetTextHeight( ULONG nParagraph ) const
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pEditEngine->GetTextHeight((USHORT)nParagraph );
/*N*/ }

/*N*/ Point Outliner::GetDocPos( const Point& rPaperPos ) const
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pEditEngine->GetDocPos( rPaperPos );
/*N*/ }

/*N*/ Point Outliner::GetDocPosTopLeft( ULONG nParagraph )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pEditEngine->GetDocPosTopLeft( (USHORT)nParagraph );
/*N*/ }

/*N*/ BOOL Outliner::IsTextPos( const Point& rPaperPos, USHORT nBorder )
/*N*/ {
/*N*/     return IsTextPos( rPaperPos, nBorder, NULL );
/*N*/ }

/*N*/ BOOL Outliner::IsTextPos( const Point& rPaperPos, USHORT nBorder, BOOL* pbBullet )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/     if ( pbBullet)
/*N*/         *pbBullet = FALSE;
/*N*/   BOOL bTextPos = pEditEngine->IsTextPos( rPaperPos, nBorder );
/*N*/   if ( !bTextPos )
/*N*/   {
/*N*/       Point aDocPos = GetDocPos( rPaperPos );
/*N*/       USHORT nPara = pEditEngine->FindParagraph( aDocPos.Y() );
/*N*/       if ( ( nPara != EE_PARA_NOT_FOUND ) && ImplHasBullet( nPara ) )
/*N*/       {
/*?*/           Rectangle aBulArea = ImpCalcBulletArea( nPara, TRUE, TRUE );
/*?*/           if ( aBulArea.IsInside( rPaperPos ) )
/*?*/           {
/*?*/               bTextPos = TRUE;
/*?*/                 if ( pbBullet)
/*?*/                     *pbBullet = TRUE;
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return bTextPos;
/*N*/ }

/*N*/ void Outliner::QuickSetAttribs( const SfxItemSet& rSet, const ESelection& rSel )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->QuickSetAttribs( rSet, rSel );
/*N*/ }

/*N*/ void Outliner::QuickInsertText( const XubString& rText, const ESelection& rSel )
/*N*/ {
/*N*/   bFirstParaIsEmpty = FALSE;
/*N*/   pEditEngine->QuickInsertText( rText, rSel );
/*N*/ }

/*N*/ void Outliner::QuickDelete( const ESelection& rSel )
/*N*/ {
/*N*/   bFirstParaIsEmpty = FALSE;
/*N*/   pEditEngine->QuickDelete( rSel );
/*N*/ }

/*N*/ void Outliner::QuickInsertField( const SvxFieldItem& rFld, const ESelection& rSel )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   bFirstParaIsEmpty = FALSE;
/*N*/   pEditEngine->QuickInsertField( rFld, rSel );
/*N*/ }

/*N*/ void Outliner::QuickInsertLineBreak( const ESelection& rSel )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   bFirstParaIsEmpty = FALSE;
/*N*/   pEditEngine->QuickInsertLineBreak( rSel );
/*N*/ }

/*N*/ void Outliner::QuickFormatDoc( BOOL bFull )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->QuickFormatDoc( bFull );
/*N*/ }

/*N*/ void Outliner::SetGlobalCharStretching( USHORT nX, USHORT nY )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->SetGlobalCharStretching( nX, nY );
/*N*/ }

//STRIP001 void Outliner::GetGlobalCharStretching( USHORT& rX, USHORT& rY )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  pEditEngine->GetGlobalCharStretching( rX, rY );
//STRIP001 }


/*N*/ void Outliner::DoStretchChars( USHORT nX, USHORT nY )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->DoStretchChars( nX, nY );
/*N*/ }

/*N*/ void Outliner::EraseVirtualDevice()
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->EraseVirtualDevice();
/*N*/ }

//STRIP001 void Outliner::SetBigTextObjectStart( USHORT nStartAtPortionCount )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  pEditEngine->SetBigTextObjectStart( nStartAtPortionCount );
//STRIP001 }

//STRIP001 USHORT Outliner::GetBigTextObjectStart() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pEditEngine->GetBigTextObjectStart();
//STRIP001 }

/*N*/ BOOL Outliner::ShouldCreateBigTextObject() const
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pEditEngine->ShouldCreateBigTextObject();
/*N*/ }

/*N*/ void Outliner::SetVertical( BOOL b )
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   pEditEngine->SetVertical( b );
/*N*/ }

/*N*/ BOOL Outliner::IsVertical() const
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pEditEngine->IsVertical();
/*N*/ }

//STRIP001 void Outliner::SetDefaultHorizontalTextDirection( EEHorizontalTextDirection eHTextDir )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  pEditEngine->SetDefaultHorizontalTextDirection( eHTextDir );
//STRIP001 }

//STRIP001 EEHorizontalTextDirection Outliner::GetDefaultHorizontalTextDirection() const
//STRIP001 {
//STRIP001  return pEditEngine->GetDefaultHorizontalTextDirection();
//STRIP001 }

/*N*/ USHORT Outliner::GetScriptType( const ESelection& rSelection ) const
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pEditEngine->GetScriptType( rSelection );
/*N*/ }

/*N*/ LanguageType Outliner::GetLanguage( USHORT nPara, USHORT nPos ) const
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pEditEngine->GetLanguage( nPara, nPos );
/*N*/ }

//STRIP001 void Outliner::RemoveAttribs( const ESelection& rSelection, sal_Bool bRemoveParaAttribs, sal_uInt16 nWhich )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  pEditEngine->RemoveAttribs( rSelection, bRemoveParaAttribs, nWhich );
//STRIP001 }

//STRIP001 void Outliner::EnableAutoColor( BOOL b )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  pEditEngine->EnableAutoColor( b );
//STRIP001 }

//STRIP001 BOOL Outliner::IsAutoColorEnabled() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  return pEditEngine->IsAutoColorEnabled();
//STRIP001 }

//STRIP001 void Outliner::ForceAutoColor( BOOL b )
//STRIP001 {
//STRIP001  DBG_CHKTHIS(Outliner,0);
//STRIP001  pEditEngine->ForceAutoColor( b );
//STRIP001 }

/*N*/ BOOL Outliner::IsForceAutoColor() const
/*N*/ {
/*N*/   DBG_CHKTHIS(Outliner,0);
/*N*/   return pEditEngine->IsForceAutoColor();
/*N*/ }
