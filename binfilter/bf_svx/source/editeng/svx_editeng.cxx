/*************************************************************************
 *
 *  $RCSfile: svx_editeng.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:25 $
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

// #define _SOLAR__PRIVATE 1
#pragma hdrstop

#define USE_SVXFONT

#define _SVSTDARR_USHORTS
#include <svtools/svstdarr.hxx>

#include <svxfont.hxx>
#include <impedit.hxx>
#include <editeng.hxx>
#include <editview.hxx>
#include <editstat.hxx>
#include <editdbg.hxx>
#include <eerdll2.hxx>
#include <eerdll.hxx>
#include <editeng.hrc>
#include <flditem.hxx>
#include <txtrange.hxx>
#include <vcl/graph.hxx>

#include "akrnitem.hxx"
#include "cntritem.hxx"
#include "colritem.hxx"
#include "crsditem.hxx"
#include "escpitem.hxx"
#include "fhgtitem.hxx"
#include "fontitem.hxx"
#include "kernitem.hxx"
#include "lrspitem.hxx"
#include "postitem.hxx"
#include "shdditem.hxx"
#include "udlnitem.hxx"
#include "wghtitem.hxx"
#include "wrlmitem.hxx"
#include "brshitem.hxx"
#include "cscoitem.hxx"
#include "langitem.hxx"
#include <emphitem.hxx>
#include <charscaleitem.hxx>
#include <charreliefitem.hxx>

#include <sot/exchange.hxx>
#include <sot/formats.hxx>

//#ifndef _SV_SYSTEM_HXX
//#include <vcl/system.hxx>
//#endif

#include <numitem.hxx>
#include <bulitem.hxx>

#ifndef _UNO_LINGU_HXX
#include <unolingu.hxx>
#endif
#ifndef _LINGUISTIC_LNGPROPS_HHX_
#include <bf_linguistic/lngprops.hxx>
#endif
#ifndef _SFX_SFXUNO_HXX
#include <bf_sfx2/sfxuno.hxx>
#endif

#ifndef _SV_HELP_HXX //autogen
#include <vcl/help.hxx>
#endif

#ifndef _XPOLY_HXX //autogen
#include <xpoly.hxx>
#endif

#ifndef _COM_SUN_STAR_DATATRANSFER_CLIPBOARD_XCLIPBOARD_HPP_
#include <com/sun/star/datatransfer/clipboard/XClipboard.hpp>
#endif

#ifndef SVX_LIGHT
#include <srchdlg.hxx>
#endif

#if OSL_DEBUG_LEVEL > 1
#include <frmdiritem.hxx>
#endif
namespace binfilter {

// Spaeter -> TOOLS\STRING.H (fuer Grep: WS_TARGET)

//using namespace ::rtl;
//using namespace ::utl;
using namespace ::com::sun::star;
//using namespace ::com::sun::star::util;
using namespace ::com::sun::star::uno;
//using namespace ::com::sun::star::lang;
//using namespace ::com::sun::star::beans;
//using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::linguistic2;



/*N*/ DBG_NAME( EditEngine )
/*N*/ DBG_NAMEEX( EditView )//STRIP008 ;

#if (OSL_DEBUG_LEVEL > 1) || defined ( DBG_UTIL )
/*N*/ static sal_Bool bDebugPaint = sal_False;
#endif

SV_IMPL_VARARR( EECharAttribArray, EECharAttrib );


// ----------------------------------------------------------------------
// EditEngine
// ----------------------------------------------------------------------
/*N*/ EditEngine::EditEngine( SfxItemPool* pItemPool )
/*N*/ {
/*N*/   DBG_CTOR( EditEngine, 0 );
/*N*/   pImpEditEngine = new ImpEditEngine( this, pItemPool );
/*N*/ }

/*N*/ EditEngine::~EditEngine()
/*N*/ {
/*N*/   DBG_DTOR( EditEngine, 0 );
/*N*/   delete pImpEditEngine;
/*N*/ }

/*N*/ void EditEngine::EnableUndo( sal_Bool bEnable )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->EnableUndo( bEnable );
/*N*/ }

/*N*/ sal_Bool EditEngine::IsUndoEnabled()
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return pImpEditEngine->IsUndoEnabled();
/*N*/ }

/*N*/ sal_Bool EditEngine::IsInUndo()
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return pImpEditEngine->IsInUndo();
/*N*/ }

#ifndef SVX_LIGHT
/*N*/ SfxUndoManager& EditEngine::GetUndoManager()
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return pImpEditEngine->GetUndoManager();
/*N*/ }
#endif

/*N*/ void EditEngine::UndoActionStart( sal_uInt16 nId )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   DBG_ASSERT( !pImpEditEngine->IsInUndo(), "Aufruf von UndoActionStart im Undomodus!" );
/*N*/   if ( !pImpEditEngine->IsInUndo() )
/*N*/       pImpEditEngine->UndoActionStart( nId );
/*N*/ }

/*N*/ void EditEngine::UndoActionEnd( sal_uInt16 nId )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   DBG_ASSERT( !pImpEditEngine->IsInUndo(), "Aufruf von UndoActionEnd im Undomodus!" );
/*N*/   if ( !pImpEditEngine->IsInUndo() )
/*N*/       pImpEditEngine->UndoActionEnd( nId );
/*N*/ }

/*N*/ void EditEngine::SetRefDevice( OutputDevice* pRefDev )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->SetRefDevice( pRefDev );
/*N*/ }

/*N*/ OutputDevice* EditEngine::GetRefDevice() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return pImpEditEngine->GetRefDevice();
/*N*/ }

/*N*/ void EditEngine::SetRefMapMode( const MapMode& rMapMode )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->SetRefMapMode( rMapMode );
/*N*/ }

/*N*/ MapMode EditEngine::GetRefMapMode()
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return pImpEditEngine->GetRefMapMode();
/*N*/ }

/*N*/ void EditEngine::SetBackgroundColor( const Color& rColor )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->SetBackgroundColor( rColor );
/*N*/ }

//STRIP001 Color EditEngine::GetBackgroundColor() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  return pImpEditEngine->GetBackgroundColor();
//STRIP001 }

/*N*/ Color EditEngine::GetAutoColor() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return pImpEditEngine->GetAutoColor();
/*N*/ }

/*N*/ void EditEngine::EnableAutoColor( BOOL b )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->EnableAutoColor( b );
/*N*/ }

//STRIP001 BOOL EditEngine::IsAutoColorEnabled() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  return pImpEditEngine->IsAutoColorEnabled();
//STRIP001 }

//STRIP001 void EditEngine::ForceAutoColor( BOOL b )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  pImpEditEngine->ForceAutoColor( b );
//STRIP001 }

/*N*/ BOOL EditEngine::IsForceAutoColor() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return pImpEditEngine->IsForceAutoColor();
/*N*/ }

/*N*/ const SfxItemSet& EditEngine::GetEmptyItemSet()
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return pImpEditEngine->GetEmptyItemSet();
/*N*/ }

//STRIP001 void EditEngine::Draw( OutputDevice* pOutDev, const Rectangle& rOutRect )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  Draw( pOutDev, rOutRect, Point( 0, 0 ) );
//STRIP001 }

//STRIP001 void EditEngine::Draw( OutputDevice* pOutDev, const Point& rStartPos, short nOrientation )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  // Mit 2 Punkten erzeugen, da bei Positivem Punkt, LONGMAX als Size
//STRIP001  // Bottom und Right im Bereich > LONGMAX landen.
//STRIP001  Rectangle aBigRec( -0x3FFFFFFF, -0x3FFFFFFF, 0x3FFFFFFF, 0x3FFFFFFF );
//STRIP001  if( pOutDev->GetConnectMetaFile() )
//STRIP001      pOutDev->Push();
//STRIP001  Point aStartPos( rStartPos );
//STRIP001  if ( IsVertical() )
//STRIP001  {
//STRIP001      aStartPos.X() += GetPaperSize().Width();
//STRIP001      aStartPos = Rotate( aStartPos, nOrientation, rStartPos );
//STRIP001  }
//STRIP001  pImpEditEngine->Paint( pOutDev, aBigRec, aStartPos, sal_False, nOrientation );
//STRIP001  if( pOutDev->GetConnectMetaFile() )
//STRIP001      pOutDev->Pop();
//STRIP001 }

//STRIP001 void EditEngine::Draw( OutputDevice* pOutDev, const Rectangle& rOutRect, const Point& rStartDocPos )
//STRIP001 {
//STRIP001  Draw( pOutDev, rOutRect, rStartDocPos, sal_True );
//STRIP001 }

//STRIP001 void EditEngine::Draw( OutputDevice* pOutDev, const Rectangle& rOutRect, const Point& rStartDocPos, sal_Bool bClip )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001
//STRIP001 #if defined( DBG_UTIL ) || (OSL_DEBUG_LEVEL > 1)
//STRIP001  if ( bDebugPaint )
//STRIP001      EditDbg::ShowEditEngineData( this, sal_False );
//STRIP001 #endif
//STRIP001
//STRIP001  // Auf Pixelgrenze ausrichten, damit genau das gleiche
//STRIP001  // wie bei Paint().
//STRIP001  Rectangle aOutRect( pOutDev->LogicToPixel( rOutRect ) );
//STRIP001  aOutRect = pOutDev->PixelToLogic( aOutRect );
//STRIP001
//STRIP001  Point aStartPos;
//STRIP001  if ( !IsVertical() )
//STRIP001  {
//STRIP001      aStartPos.X() = aOutRect.Left() - rStartDocPos.X();
//STRIP001      aStartPos.Y() = aOutRect.Top() - rStartDocPos.Y();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      aStartPos.X() = aOutRect.Right() + rStartDocPos.Y();
//STRIP001      aStartPos.Y() = aOutRect.Top() - rStartDocPos.X();
//STRIP001  }
//STRIP001
//STRIP001  sal_Bool bClipRegion = pOutDev->IsClipRegion();
//STRIP001  sal_Bool bMetafile = pOutDev->GetConnectMetaFile() ? sal_True : sal_False;
//STRIP001  Region aOldRegion = pOutDev->GetClipRegion();
//STRIP001
//STRIP001 #ifdef EDIT_PRINTER_LOG
//STRIP001  if ( pOutDev->GetOutDevType() == OUTDEV_PRINTER )
//STRIP001  {
//STRIP001      SvFileStream aLog( "d:\\editprn.log", STREAM_WRITE );
//STRIP001      aLog.Seek( STREAM_SEEK_TO_END );
//STRIP001      aLog << '' << endl << "Printing: ";
//STRIP001      aLog << GetText( "\n\r" ).GetStr();
//STRIP001      aLog << endl << endl;
//STRIP001          aLog << "Ref-Device: " << String( (sal_uInt32)GetRefDevice() ).GetStr() << " Type=" << String( (sal_uInt16)GetRefDevice()->GetOutDevType() ).GetStr() << ", MapX=" << String( GetRefDevice()->GetMapMode().GetScaleX().GetNumerator() ).GetStr() << "/" << String( GetRefDevice()->GetMapMode().GetScaleX().GetDenominator() ).GetStr() <<endl;
//STRIP001      aLog << "Paper-Width: " << String( GetPaperSize().Width() ).GetStr() << ",\tOut-Width: " << String( rOutRect.GetWidth() ).GetStr() << ",\tCalculated: " << String( CalcTextWidth() ).GetStr() << endl;
//STRIP001      aLog << "Paper-Height: " << String( GetPaperSize().Height() ).GetStr() << ",\tOut-Height: " << String( rOutRect.GetHeight() ).GetStr() << ",\tCalculated: " << String( GetTextHeight() ).GetStr() << endl;
//STRIP001
//STRIP001      aLog << endl;
//STRIP001  }
//STRIP001 #endif
//STRIP001
//STRIP001  // Wenn es eine gab => Schnittmenge !
//STRIP001  // Bei der Metafileaufzeichnung Push/Pop verwenden.
//STRIP001  if ( bMetafile )
//STRIP001      pOutDev->Push();
//STRIP001
//STRIP001  // Immer die Intersect-Methode, weil beim Metafile ein Muss!
//STRIP001  if ( bClip )
//STRIP001  {
//STRIP001      // Clip only if neccesary...
//STRIP001      if ( !rStartDocPos.X() && !rStartDocPos.Y() &&
//STRIP001           ( rOutRect.GetHeight() >= (long)GetTextHeight() ) &&
//STRIP001           ( rOutRect.GetWidth() >= (long)CalcTextWidth() ) )
//STRIP001      {
//STRIP001          bClip = FALSE;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // Einige Druckertreiber bereiten Probleme, wenn Buchstaben die
//STRIP001          // ClipRegion streifen, deshalb lieber ein Pixel mehr...
//STRIP001          Rectangle aClipRect( aOutRect );
//STRIP001          if ( pOutDev->GetOutDevType() == OUTDEV_PRINTER )
//STRIP001          {
//STRIP001              Size aPixSz( 1, 0 );
//STRIP001              aPixSz = pOutDev->PixelToLogic( aPixSz );
//STRIP001              aClipRect.Right() += aPixSz.Width();
//STRIP001              aClipRect.Bottom() += aPixSz.Width();
//STRIP001          }
//STRIP001          pOutDev->IntersectClipRegion( aClipRect );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  pImpEditEngine->Paint( pOutDev, aOutRect, aStartPos );
//STRIP001
//STRIP001  if ( bMetafile )
//STRIP001      pOutDev->Pop();
//STRIP001  else if ( bClipRegion )
//STRIP001      pOutDev->SetClipRegion( aOldRegion );
//STRIP001  else
//STRIP001      pOutDev->SetClipRegion();
//STRIP001 }

/*N*/ void EditEngine::InsertView( EditView* pEditView, sal_uInt16 nIndex )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   DBG_CHKOBJ( pEditView, EditView, 0 );
/*N*/
/*N*/   if ( nIndex > pImpEditEngine->GetEditViews().Count() )
/*N*/       nIndex = pImpEditEngine->GetEditViews().Count();
/*N*/
/*N*/   pImpEditEngine->GetEditViews().Insert( pEditView, nIndex );
/*N*/   EditSelection aStartSel;
/*N*/   aStartSel = pImpEditEngine->GetEditDoc().GetStartPaM();
/*N*/   pEditView->pImpEditView->SetEditSelection( aStartSel );
/*N*/   if ( !pImpEditEngine->GetActiveView() )
/*N*/       pImpEditEngine->SetActiveView( pEditView );
/*N*/
/*N*/     pEditView->pImpEditView->AddDragAndDropListeners();
/*N*/ }

/*N*/ EditView* EditEngine::RemoveView( EditView* pView )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   DBG_CHKOBJ( pView, EditView, 0 );
/*N*/
/*N*/   pView->HideCursor();
/*N*/   EditView* pRemoved = 0;
/*N*/   sal_uInt16 nPos = pImpEditEngine->GetEditViews().GetPos( pView );
/*N*/   DBG_ASSERT( nPos != USHRT_MAX, "RemoveView mit ungueltigem Index" );
/*N*/   if ( nPos != USHRT_MAX )
/*N*/   {
/*N*/       pRemoved = pImpEditEngine->GetEditViews().GetObject( nPos );
/*N*/       pImpEditEngine->GetEditViews().Remove( nPos );
/*N*/       if ( pImpEditEngine->GetActiveView() == pView )
/*N*/       {
/*N*/           pImpEditEngine->SetActiveView( 0 );
/*N*/           pImpEditEngine->GetSelEngine().SetCurView( 0 );
/*N*/       }
/*N*/         pView->pImpEditView->RemoveDragAndDropListeners();
/*N*/
/*N*/   }
/*N*/   return pRemoved;
/*N*/ }

//STRIP001 EditView* EditEngine::RemoveView( sal_uInt16 nIndex )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  EditView* pView = pImpEditEngine->GetEditViews().GetObject( nIndex );
//STRIP001  if ( pView )
//STRIP001      return RemoveView( pView );
//STRIP001  return NULL;
//STRIP001 }

//STRIP001 EditView* EditEngine::GetView( sal_uInt16 nIndex ) const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  return pImpEditEngine->GetEditViews().GetObject( nIndex );
//STRIP001 }

//STRIP001 sal_uInt16 EditEngine::GetViewCount() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  return pImpEditEngine->GetEditViews().Count();
//STRIP001 }

/*N*/ sal_Bool EditEngine::HasView( EditView* pView ) const
/*N*/ {
/*N*/   return pImpEditEngine->GetEditViews().GetPos( pView ) != USHRT_MAX;
/*N*/ }

//STRIP001 EditView* EditEngine::GetActiveView() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  return pImpEditEngine->GetActiveView();
//STRIP001 }

//STRIP001 void EditEngine::SetActiveView( EditView* pView )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  if ( pView )
//STRIP001      DBG_CHKOBJ( pView, EditView, 0 );
//STRIP001  pImpEditEngine->SetActiveView( pView );
//STRIP001 }

/*N*/ void EditEngine::SetDefTab( sal_uInt16 nDefTab )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->GetEditDoc().SetDefTab( nDefTab );
/*N*/   if ( pImpEditEngine->IsFormatted() )
/*N*/   {
/*N*/       pImpEditEngine->FormatFullDoc();
/*N*/       pImpEditEngine->UpdateViews( (EditView*) 0 );
/*N*/   }
/*N*/ }

//STRIP001 sal_uInt16 EditEngine::GetDefTab() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  return pImpEditEngine->GetEditDoc().GetDefTab();
//STRIP001 }

/*N*/ void EditEngine::SetPaperSize( const Size& rNewSize )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/
/*N*/   Size aOldSize( pImpEditEngine->GetPaperSize() );
/*N*/   pImpEditEngine->SetValidPaperSize( rNewSize );
/*N*/   Size aNewSize( pImpEditEngine->GetPaperSize() );
/*N*/
/*N*/   sal_Bool bAutoPageSize = pImpEditEngine->GetStatus().AutoPageSize();
/*N*/   if ( bAutoPageSize || ( aNewSize.Width() != aOldSize.Width() ) )
/*N*/   {
/*N*/       for ( sal_uInt16 nView = 0; nView < pImpEditEngine->aEditViews.Count(); nView++ )
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 EditView* pView = pImpEditEngine->aEditViews[nView];
//STRIP001 /*?*/            DBG_CHKOBJ( pView, EditView, 0 );
//STRIP001 /*?*/            if ( bAutoPageSize )
//STRIP001 /*?*/                pView->pImpEditView->RecalcOutputArea();
//STRIP001 /*?*/            else if ( pView->pImpEditView->DoAutoSize() )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                pView->pImpEditView->ResetOutputArea( Rectangle(
//STRIP001 /*?*/                    pView->pImpEditView->GetOutputArea().TopLeft(), aNewSize ) );
//STRIP001 /*?*/            }
/*N*/       }
/*N*/
/*N*/       if ( bAutoPageSize || pImpEditEngine->IsFormatted() )
/*N*/       {
/*N*/           // Aendern der Breite hat bei AutoPageSize keine Wirkung, da durch
/*N*/           // Textbreite bestimmt.
/*N*/           // Optimierung erst nach Vobis-Auslieferung aktivieren...
/*N*/ //            if ( !bAutoPageSize )
/*N*/               pImpEditEngine->FormatFullDoc();
/*N*/ //            else
/*N*/ //            {
/*N*/ //                pImpEditEngine->FormatDoc();            // PageSize, falls Aenderung
/*N*/ //                pImpEditEngine->CheckAutoPageSize();    // Falls nichts formatiert wurde
/*N*/ //            }
/*N*/
/*N*/           pImpEditEngine->UpdateViews( pImpEditEngine->GetActiveView() );
/*N*/
/*N*/           if ( pImpEditEngine->GetUpdateMode() && pImpEditEngine->GetActiveView() )
/*?*/               pImpEditEngine->pActiveView->ShowCursor( sal_False, sal_False );
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ const Size& EditEngine::GetPaperSize() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return pImpEditEngine->GetPaperSize();
/*N*/ }

/*N*/ void EditEngine::SetVertical( BOOL bVertical )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->SetVertical( bVertical );
/*N*/ }

/*N*/ BOOL EditEngine::IsVertical() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return pImpEditEngine->IsVertical();
/*N*/ }

//STRIP001 void EditEngine::SetDefaultHorizontalTextDirection( EEHorizontalTextDirection eHTextDir )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  pImpEditEngine->SetDefaultHorizontalTextDirection( eHTextDir );
//STRIP001 }

//STRIP001 EEHorizontalTextDirection EditEngine::GetDefaultHorizontalTextDirection() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  return pImpEditEngine->GetDefaultHorizontalTextDirection();
//STRIP001 }

/*N*/ USHORT EditEngine::GetScriptType( const ESelection& rSelection ) const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   EditSelection aSel( pImpEditEngine->CreateSel( rSelection ) );
/*N*/   return pImpEditEngine->GetScriptType( aSel );
/*N*/ }

/*N*/ LanguageType EditEngine::GetLanguage( USHORT nPara, USHORT nPos ) const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/     ContentNode* pNode = pImpEditEngine->GetEditDoc().SaveGetObject( nPara );
/*N*/     DBG_ASSERT( pNode, "GetLanguage - nPara is invalid!" );
/*N*/     return pNode ? pImpEditEngine->GetLanguage( EditPaM( pNode, nPos ) ) : LANGUAGE_DONTKNOW;
/*N*/ }


//STRIP001 void EditEngine::TransliterateText( const ESelection& rSelection, sal_Int32 nTransliterationMode )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  pImpEditEngine->TransliterateText( pImpEditEngine->CreateSel( rSelection ), nTransliterationMode );
//STRIP001 }

/*N*/ void EditEngine::SetAsianCompressionMode( USHORT n )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditView, 0 );
/*N*/   pImpEditEngine->SetAsianCompressionMode( n );
/*N*/ }

//STRIP001 USHORT EditEngine::GetAsianCompressionMode() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  return pImpEditEngine->GetAsianCompressionMode();
//STRIP001 }

/*N*/ void EditEngine::SetKernAsianPunctuation( BOOL b )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditView, 0 );
/*N*/   pImpEditEngine->SetKernAsianPunctuation( b );
/*N*/ }

//STRIP001 BOOL EditEngine::IsKernAsianPunctuation() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditView, 0 );
//STRIP001  return pImpEditEngine->IsKernAsianPunctuation();
//STRIP001 }

//STRIP001 void EditEngine::SetPolygon( const XPolyPolygon& rPoly )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  SetPolygon( rPoly, NULL );
//STRIP001 }

//STRIP001 void EditEngine::SetPolygon( const XPolyPolygon& rPoly, const XPolyPolygon* pXorPoly )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001
//STRIP001  sal_Bool bSimple = sal_False;
//STRIP001  if( pXorPoly && rPoly.Count() == 1 )
//STRIP001  {
//STRIP001      // Handelt es sich um eine offene Kurve?
//STRIP001      const XPolygon& rP = rPoly[0];
//STRIP001      USHORT nCnt = rP.GetPointCount();
//STRIP001
//STRIP001      if( ( nCnt == 0 ) || ( rP[0] != rP[nCnt - 1] ) )
//STRIP001          // Offene Kurve
//STRIP001          bSimple = sal_True;
//STRIP001  }
//STRIP001
//STRIP001  TextRanger* pRanger = new TextRanger( rPoly, pXorPoly, 30, 2, 2, bSimple, sal_True );
//STRIP001  pImpEditEngine->SetTextRanger( pRanger );
//STRIP001  pImpEditEngine->SetPaperSize( pRanger->GetBoundRect().GetSize() );
//STRIP001 }

/*N*/ void EditEngine::ClearPolygon()
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->SetTextRanger( 0 );
/*N*/ }

//STRIP001 const PolyPolygon* EditEngine::GetPolygon()
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  return pImpEditEngine->GetTextRanger() ?
//STRIP001      &pImpEditEngine->GetTextRanger()->GetPolyPolygon() : NULL;
//STRIP001 }

//STRIP001 const Size& EditEngine::GetMinAutoPaperSize() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  return pImpEditEngine->GetMinAutoPaperSize();
//STRIP001 }

/*N*/ void EditEngine::SetMinAutoPaperSize( const Size& rSz )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->SetMinAutoPaperSize( rSz );
/*N*/ }

//STRIP001 const Size& EditEngine::GetMaxAutoPaperSize() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  return pImpEditEngine->GetMaxAutoPaperSize();
//STRIP001 }

/*N*/ void EditEngine::SetMaxAutoPaperSize( const Size& rSz )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->SetMaxAutoPaperSize( rSz );
/*N*/ }

/*N*/ XubString EditEngine::GetText( LineEnd eEnd ) const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return pImpEditEngine->GetEditDoc().GetText( eEnd );
/*N*/ }

/*N*/ XubString EditEngine::GetText( const ESelection& rESelection, const LineEnd eEnd ) const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   EditSelection aSel( pImpEditEngine->CreateSel( rESelection ) );
/*N*/   return pImpEditEngine->GetSelected( aSel, eEnd );
/*N*/ }

/*N*/ sal_uInt32 EditEngine::GetTextLen() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return pImpEditEngine->GetEditDoc().GetTextLen();
/*N*/ }

/*N*/ sal_uInt16 EditEngine::GetParagraphCount() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return pImpEditEngine->aEditDoc.Count();
/*N*/ }

/*N*/ sal_uInt16 EditEngine::GetLineCount( sal_uInt16 nParagraph ) const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return pImpEditEngine->GetLineCount( nParagraph );
/*N*/ }

/*N*/ sal_uInt16 EditEngine::GetLineLen( sal_uInt16 nParagraph, sal_uInt16 nLine ) const
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return 0; //STRIP001
//STRIP001 /*?*/    DBG_CHKTHIS( EditEngine, 0 );
//STRIP001 /*?*/    return pImpEditEngine->GetLineLen( nParagraph, nLine );
/*N*/ }

/*?*/ sal_uInt32 EditEngine::GetLineHeight( sal_uInt16 nParagraph, sal_uInt16 nLine )
/*?*/ {{DBG_BF_ASSERT(0, "STRIP");} return 0;//STRIP001
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  // Falls jemand mit einer leeren Engine ein GetLineHeight() macht.
//STRIP001  if ( !pImpEditEngine->IsFormatted() )
//STRIP001      pImpEditEngine->FormatDoc();
//STRIP001  return pImpEditEngine->GetLineHeight( nParagraph, nLine );
/*?*/ }

/*N*/ sal_uInt16 EditEngine::GetFirstLineOffset( sal_uInt16 nParagraph )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   if ( !pImpEditEngine->IsFormatted() )
/*?*/       pImpEditEngine->FormatDoc();
/*N*/   ParaPortion* pPortion = pImpEditEngine->GetParaPortions().SaveGetObject( nParagraph );
/*N*/   return ( pPortion ? pPortion->GetFirstLineOffset() : 0 );
/*N*/ }

/*N*/ sal_uInt32 EditEngine::GetTextHeight( sal_uInt16 nParagraph ) const
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return 0; //STRIP001
//STRIP001 /*?*/    DBG_CHKTHIS( EditEngine, 0 );
//STRIP001 /*?*/
//STRIP001 /*?*/    if ( !pImpEditEngine->IsFormatted() )
//STRIP001 /*?*/        pImpEditEngine->FormatDoc();
//STRIP001 /*?*/
//STRIP001 /*?*/    sal_uInt32 nHeight = pImpEditEngine->GetParaHeight( nParagraph );
//STRIP001 /*?*/    return nHeight;
/*N*/ }

//STRIP001 XubString EditEngine::GetWord( sal_uInt16 nPara, sal_uInt16 nIndex )
//STRIP001 {
//STRIP001  ESelection aESel( nPara, nIndex, nPara, nIndex );
//STRIP001  EditSelection aSel( pImpEditEngine->CreateSel( aESel ) );
//STRIP001  aSel = pImpEditEngine->SelectWord( aSel );
//STRIP001  return pImpEditEngine->GetSelected( aSel );
//STRIP001 }

/*N*/ ESelection EditEngine::GetWord( const ESelection& rSelection, USHORT nWordType  ) const
/*N*/ {
/*N*/     // ImpEditEngine-Iteration-Methods should be const!
/*N*/     EditEngine* pE = (EditEngine*)this;
/*N*/
/*N*/   EditSelection aSel( pE->pImpEditEngine->CreateSel( rSelection ) );
/*N*/   aSel = pE->pImpEditEngine->SelectWord( aSel, nWordType );
/*N*/   return pE->pImpEditEngine->CreateESel( aSel );
/*N*/ }

//STRIP001 ESelection EditEngine::WordLeft( const ESelection& rSelection, USHORT nWordType  ) const
//STRIP001 {
//STRIP001     // ImpEditEngine-Iteration-Methods should be const!
//STRIP001     EditEngine* pE = (EditEngine*)this;
//STRIP001
//STRIP001  EditSelection aSel( pE->pImpEditEngine->CreateSel( rSelection ) );
//STRIP001  aSel = pE->pImpEditEngine->WordLeft( aSel.Min(), nWordType );
//STRIP001  return pE->pImpEditEngine->CreateESel( aSel );
//STRIP001 }

//STRIP001 ESelection EditEngine::WordRight( const ESelection& rSelection, USHORT nWordType  ) const
//STRIP001 {
//STRIP001     // ImpEditEngine-Iteration-Methods should be const!
//STRIP001     EditEngine* pE = (EditEngine*)this;
//STRIP001
//STRIP001  EditSelection aSel( pE->pImpEditEngine->CreateSel( rSelection ) );
//STRIP001  aSel = pE->pImpEditEngine->WordRight( aSel.Max(), nWordType );
//STRIP001  return pE->pImpEditEngine->CreateESel( aSel );
//STRIP001 }

//STRIP001 ESelection EditEngine::CursorLeft( const ESelection& rSelection, USHORT nCharacterIteratorMode ) const
//STRIP001 {
//STRIP001     // ImpEditEngine-Iteration-Methods should be const!
//STRIP001     EditEngine* pE = (EditEngine*)this;
//STRIP001
//STRIP001  EditSelection aSel( pE->pImpEditEngine->CreateSel( rSelection ) );
//STRIP001  aSel = pE->pImpEditEngine->CursorLeft( aSel.Min(), nCharacterIteratorMode );
//STRIP001  return pE->pImpEditEngine->CreateESel( aSel );
//STRIP001 }

//STRIP001 ESelection EditEngine::CursorRight( const ESelection& rSelection, USHORT nCharacterIteratorMode ) const
//STRIP001 {
//STRIP001     // ImpEditEngine-Iteration-Methods should be const!
//STRIP001     EditEngine* pE = (EditEngine*)this;
//STRIP001
//STRIP001  EditSelection aSel( pE->pImpEditEngine->CreateSel( rSelection ) );
//STRIP001  aSel = pE->pImpEditEngine->CursorRight( aSel.Max(), nCharacterIteratorMode );
//STRIP001  return pE->pImpEditEngine->CreateESel( aSel );
//STRIP001 }

/*?*/ sal_Bool EditEngine::PostKeyEvent( const KeyEvent& rKeyEvent, EditView* pEditView )
/*?*/ {{DBG_BF_ASSERT(0, "STRIP"); } return sal_False;//STRIP001
//STRIP001 /*?*/    DBG_CHKTHIS( EditEngine, 0 );
//STRIP001 /*?*/    DBG_CHKOBJ( pEditView, EditView, 0 );
//STRIP001 /*?*/    DBG_ASSERT( pEditView, "Keine View - keine Kekse !" );
//STRIP001 /*?*/
//STRIP001 /*?*/     sal_Bool bDone = sal_True;
//STRIP001 /*?*/
//STRIP001 /*?*/ #ifndef SVX_LIGHT
//STRIP001 /*?*/
//STRIP001 /*?*/    sal_Bool bModified  = sal_False;
//STRIP001 /*?*/    sal_Bool bMoved     = sal_False;
//STRIP001 /*?*/    sal_Bool bAllowIdle = sal_True;
//STRIP001 /*?*/    sal_Bool bReadOnly  = pEditView->IsReadOnly();
//STRIP001 /*?*/
//STRIP001 /*?*/     USHORT nNewCursorFlags = 0;
//STRIP001 /*?*/     BOOL bSetCursorFlags = TRUE;
//STRIP001 /*?*/
//STRIP001 /*?*/    EditSelection aCurSel( pEditView->pImpEditView->GetEditSelection() );
//STRIP001 /*?*/    DBG_ASSERT( !aCurSel.IsInvalid(), "Blinde Selection in EditEngine::PostKeyEvent" );
//STRIP001 /*?*/
//STRIP001 /*?*/    String aAutoText( pImpEditEngine->GetAutoCompleteText() );
//STRIP001 /*?*/    if ( pImpEditEngine->GetAutoCompleteText().Len() )
//STRIP001 /*?*/    {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     pImpEditEngine->SetAutoCompleteText( String(), sal_True );
//STRIP001 /*?*/
//STRIP001 /*?*/    sal_uInt16 nCode = rKeyEvent.GetKeyCode().GetCode();
//STRIP001 /*?*/    KeyFuncType eFunc = rKeyEvent.GetKeyCode().GetFunction();
//STRIP001 /*?*/    if ( eFunc != KEYFUNC_DONTKNOW )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        switch ( eFunc )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            case KEYFUNC_UNDO:
//STRIP001 /*?*/            {
//STRIP001 /*?*/                if ( !bReadOnly )
//STRIP001 /*?*/                {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     pEditView->Undo();
//STRIP001 /*?*/                return sal_True;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            // break;
//STRIP001 /*?*/            case KEYFUNC_REDO:
//STRIP001 /*?*/            {
//STRIP001 /*?*/                if ( !bReadOnly )
//STRIP001 /*?*/                {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     pEditView->Redo();
//STRIP001 /*?*/                return sal_True;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            // break;
//STRIP001 /*?*/
//STRIP001 /*?*/            default:    // wird dann evtl. unten bearbeitet.
//STRIP001 /*?*/                        eFunc = KEYFUNC_DONTKNOW;
//STRIP001 /*?*/        }
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/     pImpEditEngine->EnterBlockNotifications();
//STRIP001 /*?*/
//STRIP001 /*?*/     if ( GetNotifyHdl().IsSet() )
//STRIP001 /*?*/     {
//STRIP001 /*?*/         EENotify aNotify( EE_NOTIFY_INPUT_START );
//STRIP001 /*?*/         aNotify.pEditEngine = this;
//STRIP001 /*?*/         pImpEditEngine->CallNotify( aNotify );
//STRIP001 /*?*/     }
//STRIP001 /*?*/
//STRIP001 /*?*/     if ( eFunc == KEYFUNC_DONTKNOW )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        switch ( nCode )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            #if defined( DBG_UTIL ) || (OSL_DEBUG_LEVEL > 1)
//STRIP001 /*?*/            case KEY_F1:
//STRIP001 /*?*/            {
//STRIP001 /*?*/                if ( rKeyEvent.GetKeyCode().IsMod1() && rKeyEvent.GetKeyCode().IsMod2() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                     USHORT nParas = GetParagraphCount();
//STRIP001 /*?*/                     Point aPos;
//STRIP001 /*?*/                     Point aViewStart( pEditView->GetOutputArea().TopLeft() );
//STRIP001 /*?*/                     long n20 = 40 * pImpEditEngine->nOnePixelInRef;
//STRIP001 /*?*/                     for ( USHORT n = 0; n < nParas; n++ )
//STRIP001 /*?*/                     {
//STRIP001 /*?*/                         long nH = GetTextHeight( n );
//STRIP001 /*?*/                         Point P1( aViewStart.X() + n20 + n20*(n%2), aViewStart.Y() + aPos.Y() );
//STRIP001 /*?*/                         Point P2( P1 );
//STRIP001 /*?*/                         P2.X() += n20;
//STRIP001 /*?*/                         P2.Y() += nH;
//STRIP001 /*?*/                         pEditView->GetWindow()->SetLineColor();
//STRIP001 /*?*/                         pEditView->GetWindow()->SetFillColor( Color( (n%2) ? COL_YELLOW : COL_LIGHTGREEN ) );
//STRIP001 /*?*/                         pEditView->GetWindow()->DrawRect( Rectangle( P1, P2 ) );
//STRIP001 /*?*/                         aPos.Y() += nH;
//STRIP001 /*?*/                     }
//STRIP001 /*?*/                }
//STRIP001 /*?*/                bDone = FALSE;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            break;
//STRIP001 /*?*/            case KEY_F11:
//STRIP001 /*?*/            {
//STRIP001 /*?*/                if ( rKeyEvent.GetKeyCode().IsMod1() && rKeyEvent.GetKeyCode().IsMod2() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    bDebugPaint = !bDebugPaint;
//STRIP001 /*?*/                    ByteString aInfo( "DebugPaint: " );
//STRIP001 /*?*/                    aInfo += bDebugPaint ? "On" : "Off";
//STRIP001 /*?*/                    InfoBox( NULL, String( aInfo, RTL_TEXTENCODING_ASCII_US ) ).Execute();
//STRIP001 /*?*/                }
//STRIP001 /*?*/                bDone = FALSE;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            break;
//STRIP001 /*?*/            case KEY_F12:
//STRIP001 /*?*/            {
//STRIP001 /*?*/                if ( rKeyEvent.GetKeyCode().IsMod1() && rKeyEvent.GetKeyCode().IsMod2() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    EditDbg::ShowEditEngineData( this );
//STRIP001 /*?*/                    #ifdef EDIT_PRINTER_LOG
//STRIP001 /*?*/                        SvFileStream aLog( "d:\\editprn.log", STREAM_WRITE );
//STRIP001 /*?*/                        aLog.Seek( STREAM_SEEK_TO_END );
//STRIP001 /*?*/                        aLog << '' << endl << "Debug: ";
//STRIP001 /*?*/                        aLog << GetText( "\n\r" ).GetStr();
//STRIP001 /*?*/                        aLog << endl << endl;
//STRIP001 /*?*/                        aLog << "Ref-Device: " << String( (sal_uInt32)GetRefDevice() ).GetStr() << " Type=" << String( (sal_uInt16)GetRefDevice()->GetOutDevType() ).GetStr() << ", MapX=" << String( GetRefDevice()->GetMapMode().GetScaleX().GetNumerator() ).GetStr() << "/" << String( GetRefDevice()->GetMapMode().GetScaleX().GetDenominator() ).GetStr() <<endl;
//STRIP001 /*?*/                        aLog << "Paper-Width: " << String( GetPaperSize().Width() ).GetStr() << ",\tCalculated: " << String( CalcTextWidth() ).GetStr() << endl;
//STRIP001 /*?*/                        aLog << "Paper-Height: " << String( GetPaperSize().Height() ).GetStr() << ",\tCalculated: " << String( GetTextHeight() ).GetStr() << endl;
//STRIP001 /*?*/                        aLog << endl;
//STRIP001 /*?*/                    #endif
//STRIP001 /*?*/                }
//STRIP001 /*?*/                bDone = FALSE;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            break;
//STRIP001 /*?*/           #endif
//STRIP001 /*?*/            case KEY_UP:
//STRIP001 /*?*/            case KEY_DOWN:
//STRIP001 /*?*/            case KEY_LEFT:
//STRIP001 /*?*/            case KEY_RIGHT:
//STRIP001 /*?*/            case KEY_HOME:
//STRIP001 /*?*/            case KEY_END:
//STRIP001 /*?*/            case KEY_PAGEUP:
//STRIP001 /*?*/            case KEY_PAGEDOWN:
//STRIP001 /*?*/            {
//STRIP001 /*?*/                 if ( !rKeyEvent.GetKeyCode().IsMod2() || ( nCode == KEY_LEFT ) || ( nCode == KEY_RIGHT ) )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                     if ( pImpEditEngine->DoVisualCursorTraveling( aCurSel.Max().GetNode() ) && ( ( nCode == KEY_LEFT ) || ( nCode == KEY_RIGHT ) /* || ( nCode == KEY_HOME ) || ( nCode == KEY_END ) */ ) )
//STRIP001 /*?*/                         bSetCursorFlags = FALSE;    // Will be manipulated within visual cursor move
//STRIP001 /*?*/
//STRIP001 /*?*/                    aCurSel = pImpEditEngine->MoveCursor( rKeyEvent, pEditView );
//STRIP001 /*?*/
//STRIP001 /*?*/                     if ( aCurSel.HasRange() ) {
//STRIP001 /*?*/                         Reference< ::com::sun::star::datatransfer::clipboard::XClipboard> aSelection(pEditView->GetWindow()->GetSelection());
//STRIP001 /*?*/                         pEditView->pImpEditView->CutCopy( aSelection, FALSE );
//STRIP001 /*?*/                     }
//STRIP001 /*?*/
//STRIP001 /*?*/                    bMoved = sal_True;
//STRIP001 /*?*/                    if ( nCode == KEY_HOME )
//STRIP001 /*?*/                        nNewCursorFlags |= GETCRSR_STARTOFLINE;
//STRIP001 /*?*/                    else if ( nCode == KEY_END )
//STRIP001 /*?*/                        nNewCursorFlags |= GETCRSR_ENDOFLINE;
//STRIP001 /*?*/
//STRIP001 /*?*/                }
//STRIP001 /*?*/ #if OSL_DEBUG_LEVEL > 1
//STRIP001 /*?*/                 GetLanguage( pImpEditEngine->GetEditDoc().GetPos( aCurSel.Max().GetNode() ), aCurSel.Max().GetIndex() );
//STRIP001 /*?*/ #endif
//STRIP001 /*?*/            }
//STRIP001 /*?*/            break;
//STRIP001 /*?*/            case KEY_BACKSPACE:
//STRIP001 /*?*/            case KEY_DELETE:
//STRIP001 /*?*/            {
//STRIP001 /*?*/                if ( !bReadOnly && !rKeyEvent.GetKeyCode().IsMod2() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    BYTE nDel = ( nCode == KEY_DELETE ) ? DEL_RIGHT : DEL_LEFT;
//STRIP001 /*?*/                    BYTE nMode = rKeyEvent.GetKeyCode().IsMod1() ? DELMODE_RESTOFWORD : DELMODE_SIMPLE;
//STRIP001 /*?*/                    if ( ( nMode == DELMODE_RESTOFWORD ) && rKeyEvent.GetKeyCode().IsShift() )
//STRIP001 /*?*/                        nMode = DELMODE_RESTOFCONTENT;
//STRIP001 /*?*/                    pEditView->pImpEditView->DrawSelection();
//STRIP001 /*?*/                    pImpEditEngine->UndoActionStart( EDITUNDO_DELETE );
//STRIP001 /*?*/                    aCurSel = pImpEditEngine->DeleteLeftOrRight( aCurSel, nDel, nMode );
//STRIP001 /*?*/                    pImpEditEngine->UndoActionEnd( EDITUNDO_DELETE );
//STRIP001 /*?*/                    bModified = sal_True;
//STRIP001 /*?*/                    bAllowIdle = sal_False;
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/            break;
//STRIP001 /*?*/            case KEY_TAB:
//STRIP001 /*?*/            {
//STRIP001 /*?*/                if ( !bReadOnly && !rKeyEvent.GetKeyCode().IsMod1() && !rKeyEvent.GetKeyCode().IsMod2() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    sal_Bool bShift = rKeyEvent.GetKeyCode().IsShift();
//STRIP001 /*?*/                    if ( pImpEditEngine->GetStatus().DoTabIndenting() &&
//STRIP001 /*?*/                        ( aCurSel.Min().GetNode() != aCurSel.Max().GetNode() ) )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        pImpEditEngine->IndentBlock( pEditView, !bShift );
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    else if ( !bShift )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        sal_Bool bSel = pEditView->HasSelection();
//STRIP001 /*?*/                        if ( bSel )
//STRIP001 /*?*/                            pImpEditEngine->UndoActionStart( EDITUNDO_INSERT );
//STRIP001 /*?*/                        if ( pImpEditEngine->GetStatus().DoAutoCorrect() )
//STRIP001 /*?*/                            aCurSel = pImpEditEngine->AutoCorrect( aCurSel, 0, !pEditView->IsInsertMode() );
//STRIP001 /*?*/                        aCurSel = pImpEditEngine->InsertTab( aCurSel );
//STRIP001 /*?*/                        if ( bSel )
//STRIP001 /*?*/                            pImpEditEngine->UndoActionEnd( EDITUNDO_INSERT );
//STRIP001 /*?*/                        bModified = sal_True;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else
//STRIP001 /*?*/                    bDone = sal_False;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            break;
//STRIP001 /*?*/            case KEY_RETURN:
//STRIP001 /*?*/            {
//STRIP001 /*?*/                if ( !bReadOnly )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    pEditView->pImpEditView->DrawSelection();
//STRIP001 /*?*/                    if ( !rKeyEvent.GetKeyCode().IsMod1() && !rKeyEvent.GetKeyCode().IsMod2() )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        pImpEditEngine->UndoActionStart( EDITUNDO_INSERT );
//STRIP001 /*?*/                        if ( rKeyEvent.GetKeyCode().IsShift() )
//STRIP001 /*?*/                            aCurSel = pImpEditEngine->InsertLineBreak( aCurSel );
//STRIP001 /*?*/                        else
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            if ( !aAutoText.Len() )
//STRIP001 /*?*/                            {
//STRIP001 /*?*/                                if ( pImpEditEngine->GetStatus().DoAutoCorrect() )
//STRIP001 /*?*/                                    aCurSel = pImpEditEngine->AutoCorrect( aCurSel, 0, !pEditView->IsInsertMode() );
//STRIP001 /*?*/                                aCurSel = pImpEditEngine->InsertParaBreak( aCurSel );
//STRIP001 /*?*/                            }
//STRIP001 /*?*/                            else
//STRIP001 /*?*/                            {
//STRIP001 /*?*/                                DBG_ASSERT( !aCurSel.HasRange(), "Selektion bei Complete?!" );
//STRIP001 /*?*/                                EditPaM aStart( pImpEditEngine->WordLeft( aCurSel.Max() ) );
//STRIP001 /*?*/                                aCurSel = pImpEditEngine->InsertText(
//STRIP001 /*?*/                                                EditSelection( aStart, aCurSel.Max() ), aAutoText );
//STRIP001 /*?*/                                pImpEditEngine->SetAutoCompleteText( String(), sal_True );
//STRIP001 /*?*/                            }
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                        pImpEditEngine->UndoActionEnd( EDITUNDO_INSERT );
//STRIP001 /*?*/                        bModified = sal_True;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/            break;
//STRIP001 /*?*/            case KEY_INSERT:
//STRIP001 /*?*/            {
//STRIP001 /*?*/                if ( !rKeyEvent.GetKeyCode().IsMod1() && !rKeyEvent.GetKeyCode().IsMod2() )
//STRIP001 /*?*/                    pEditView->SetInsertMode( !pEditView->IsInsertMode() );
//STRIP001 /*?*/            }
//STRIP001 /*?*/            break;
//STRIP001 /*?*/            default:
//STRIP001 /*?*/            {
//STRIP001 /*?*/                 #if (OSL_DEBUG_LEVEL > 1) && !defined( PRODUCT )
//STRIP001 /*?*/                     if ( ( nCode == KEY_W ) && rKeyEvent.GetKeyCode().IsMod1() && rKeyEvent.GetKeyCode().IsMod2() )
//STRIP001 /*?*/                     {
//STRIP001 /*?*/                         SfxItemSet aAttribs = pEditView->GetAttribs();
//STRIP001 /*?*/                         const SvxFrameDirectionItem& rCurrentWritingMode = (const SvxFrameDirectionItem&)aAttribs.Get( EE_PARA_WRITINGDIR );
//STRIP001 /*?*/                         SvxFrameDirectionItem aNewItem( FRMDIR_HORI_LEFT_TOP, EE_PARA_WRITINGDIR );
//STRIP001 /*?*/                         if ( rCurrentWritingMode.GetValue() != FRMDIR_HORI_RIGHT_TOP )
//STRIP001 /*?*/                             aNewItem.SetValue( FRMDIR_HORI_RIGHT_TOP );
//STRIP001 /*?*/                         aAttribs.Put( aNewItem );
//STRIP001 /*?*/                         pEditView->SetAttribs( aAttribs );
//STRIP001 /*?*/                     }
//STRIP001 /*?*/                 #endif
//STRIP001 /*?*/                if ( !bReadOnly && IsSimpleCharInput( rKeyEvent ) )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    xub_Unicode nCharCode = rKeyEvent.GetCharCode();
//STRIP001 /*?*/                    pEditView->pImpEditView->DrawSelection();
//STRIP001 /*?*/                    // Autokorrektur ?
//STRIP001 /*?*/                    if ( ( pImpEditEngine->GetStatus().DoAutoCorrect() ) &&
//STRIP001 /*?*/                         (  ( nCharCode == ' ' ) || ( nCharCode == '*' ) ||
//STRIP001 /*?*/                            ( nCharCode == '\"' ) || ( nCharCode == '\'' ) ||
//STRIP001 /*?*/                            ( nCharCode == '_' )  ) )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        aCurSel = pImpEditEngine->AutoCorrect( aCurSel, nCharCode, !pEditView->IsInsertMode() );
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    else
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        aCurSel = pImpEditEngine->InsertText( (const EditSelection&)aCurSel, nCharCode, !pEditView->IsInsertMode() );
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    // AutoComplete ???
//STRIP001 /*?*/                    if ( pImpEditEngine->GetStatus().DoAutoComplete() && ( nCharCode != ' ' ) )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        // Aber nur wenn Wort-Ende...
//STRIP001 /*?*/                        sal_uInt16 nIndex = aCurSel.Max().GetIndex();
//STRIP001 /*?*/                        if ( ( nIndex >= aCurSel.Max().GetNode()->Len() ) ||
//STRIP001 /*?*/                             ( pImpEditEngine->aWordDelimiters.Search( aCurSel.Max().GetNode()->GetChar( nIndex ) ) != STRING_NOTFOUND ) )
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            EditPaM aStart( pImpEditEngine->WordLeft( aCurSel.Max() ) );
//STRIP001 /*?*/                            String aWord = pImpEditEngine->GetSelected( EditSelection( aStart, aCurSel.Max() ) );
//STRIP001 /*?*/                            if ( aWord.Len() >= 3 )
//STRIP001 /*?*/                            {
//STRIP001 /*?*/                                String aComplete;
//STRIP001 /*?*/
//STRIP001 /*?*/                                International aInt = International( pImpEditEngine->GetLanguage( EditPaM( aStart.GetNode(), aStart.GetIndex()+1 ) ) );
//STRIP001 /*?*/                                for( int n = MONDAY; n <= SUNDAY; ++n )
//STRIP001 /*?*/                                {
//STRIP001 /*?*/                                    const String& rDay = aInt.GetDayText( (DayOfWeek)n );
//STRIP001 /*?*/                                    // MT: Auf International umstellen, wenn Compare mit Laengenangabe moeglich!
//STRIP001 /*?*/                                    if( aWord.CompareIgnoreCaseToAscii( rDay, aWord.Len() ) == COMPARE_EQUAL )
//STRIP001 /*?*/                                    {
//STRIP001 /*?*/                                        aComplete = rDay;
//STRIP001 /*?*/                                        break;
//STRIP001 /*?*/                                    }
//STRIP001 /*?*/                                }
//STRIP001 /*?*/
//STRIP001 /*?*/                                if ( !aComplete.Len() )
//STRIP001 /*?*/                                {
//STRIP001 /*?*/                                    for( int n = 1; n <= 12; ++n )
//STRIP001 /*?*/                                    {
//STRIP001 /*?*/                                        const String& rMon = aInt.GetMonthText( n );
//STRIP001 /*?*/                                        // MT: Auf International umstellen, wenn Compare mit Laengenangabe moeglich!
//STRIP001 /*?*/                                        if( aWord.CompareIgnoreCaseToAscii( rMon, aWord.Len() ) == COMPARE_EQUAL )
//STRIP001 /*?*/                                        {
//STRIP001 /*?*/                                            aComplete = rMon;
//STRIP001 /*?*/                                            break;
//STRIP001 /*?*/                                        }
//STRIP001 /*?*/                                    }
//STRIP001 /*?*/                                }
//STRIP001 /*?*/
//STRIP001 /*?*/                                if( aComplete.Len() && ( ( aWord.Len() + 1 ) < aComplete.Len() ) )
//STRIP001 /*?*/                                {
//STRIP001 /*?*/                                    pImpEditEngine->SetAutoCompleteText( aComplete, sal_False );
//STRIP001 /*?*/                                    Point aPos = pImpEditEngine->PaMtoEditCursor( aCurSel.Max() ).TopLeft();
//STRIP001 /*?*/                                    aPos = pEditView->pImpEditView->GetWindowPos( aPos );
//STRIP001 /*?*/                                    aPos = pEditView->pImpEditView->GetWindow()->LogicToPixel( aPos );
//STRIP001 /*?*/                                    aPos = pEditView->GetWindow()->OutputToScreenPixel( aPos );
//STRIP001 /*?*/                                    aPos.Y() -= 3;
//STRIP001 /*?*/                                    Help::ShowQuickHelp( pEditView->GetWindow(), Rectangle( aPos, Size( 1, 1 ) ), aComplete, QUICKHELP_BOTTOM|QUICKHELP_LEFT );
//STRIP001 /*?*/                                }
//STRIP001 /*?*/                            }
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    bModified = sal_True;
//STRIP001 /*?*/                }
//STRIP001 /*?*/                else
//STRIP001 /*?*/                    bDone = sal_False;
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    pEditView->pImpEditView->SetEditSelection( aCurSel );
//STRIP001 /*?*/    pImpEditEngine->UpdateSelections();
//STRIP001 /*?*/
//STRIP001 /*?*/    if ( ( !IsVertical() && ( nCode != KEY_UP ) && ( nCode != KEY_DOWN ) ) ||
//STRIP001 /*?*/         ( IsVertical() && ( nCode != KEY_LEFT ) && ( nCode != KEY_RIGHT ) ))
//STRIP001 /*?*/     {
//STRIP001 /*?*/        pEditView->pImpEditView->nTravelXPos = TRAVEL_X_DONTKNOW;
//STRIP001 /*?*/     }
//STRIP001 /*?*/
//STRIP001 /*?*/     if ( /* ( nCode != KEY_HOME ) && ( nCode != KEY_END ) && */
//STRIP001 /*?*/         ( !IsVertical() && ( nCode != KEY_LEFT ) && ( nCode != KEY_RIGHT ) ) ||
//STRIP001 /*?*/         ( IsVertical() && ( nCode != KEY_UP ) && ( nCode != KEY_DOWN ) ))
//STRIP001 /*?*/     {
//STRIP001 /*?*/        pEditView->pImpEditView->SetCursorBidiLevel( 0xFFFF );
//STRIP001 /*?*/     }
//STRIP001 /*?*/
//STRIP001 /*?*/     if ( bSetCursorFlags )
//STRIP001 /*?*/         pEditView->pImpEditView->nExtraCursorFlags = nNewCursorFlags;
//STRIP001 /*?*/
//STRIP001 /*?*/    if ( bModified )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        DBG_ASSERT( !bReadOnly, "ReadOnly but modified???" );
//STRIP001 /*?*/        // Idle-Formatter nur, wenn AnyInput.
//STRIP001 /*?*/        if ( bAllowIdle && pImpEditEngine->GetStatus().UseIdleFormatter()
//STRIP001 /*?*/                && Application::AnyInput( INPUT_KEYBOARD) )
//STRIP001 /*?*/            pImpEditEngine->IdleFormatAndUpdate( pEditView );
//STRIP001 /*?*/        else
//STRIP001 /*?*/            pImpEditEngine->FormatAndUpdate( pEditView );
//STRIP001 /*?*/    }
//STRIP001 /*?*/    else if ( bMoved )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        sal_Bool bGotoCursor = pEditView->pImpEditView->DoAutoScroll();
//STRIP001 /*?*/        pEditView->pImpEditView->ShowCursor( bGotoCursor, sal_True );
//STRIP001 /*?*/        pImpEditEngine->CallStatusHdl();
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/ #endif
//STRIP001 /*?*/
//STRIP001 /*?*/     if ( GetNotifyHdl().IsSet() )
//STRIP001 /*?*/     {
//STRIP001 /*?*/         EENotify aNotify( EE_NOTIFY_INPUT_END );
//STRIP001 /*?*/         aNotify.pEditEngine = this;
//STRIP001 /*?*/         pImpEditEngine->CallNotify( aNotify );
//STRIP001 /*?*/     }
//STRIP001 /*?*/
//STRIP001 /*?*/     pImpEditEngine->LeaveBlockNotifications();
//STRIP001 /*?*/
//STRIP001 /*?*/     return bDone;
/*?*/ }

/*N*/ sal_uInt32 EditEngine::GetTextHeight() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/
/*N*/   if ( !pImpEditEngine->IsFormatted() )
/*?*/       pImpEditEngine->FormatDoc();
/*N*/
/*N*/   sal_uInt32 nHeight = !IsVertical() ? pImpEditEngine->GetTextHeight() : pImpEditEngine->CalcTextWidth( TRUE );
/*N*/   return nHeight;
/*N*/ }

/*N*/ sal_uInt32 EditEngine::CalcTextWidth()
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/
/*N*/   if ( !pImpEditEngine->IsFormatted() )
/*?*/       pImpEditEngine->FormatDoc();
/*N*/
/*N*/   sal_uInt32 nWidth = !IsVertical() ? pImpEditEngine->CalcTextWidth( TRUE ) : pImpEditEngine->GetTextHeight();
/*N*/   return nWidth;
/*N*/ }

/*N*/ void EditEngine::SetUpdateMode( sal_Bool bUpdate )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->SetUpdateMode( bUpdate );
/*N*/   if ( pImpEditEngine->pActiveView )
/*?*/       pImpEditEngine->pActiveView->ShowCursor( sal_False, sal_False );
/*N*/ }

/*N*/ sal_Bool EditEngine::GetUpdateMode() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return pImpEditEngine->GetUpdateMode();
/*N*/ }

/*N*/ void EditEngine::Clear()
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->Clear();
/*N*/ }

/*N*/ void EditEngine::SetText( const XubString& rText )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->SetText( rText );
/*N*/   if ( rText.Len() )
/*N*/       pImpEditEngine->FormatAndUpdate();
/*N*/ }

/*N*/ sal_uInt32 EditEngine::Read( SvStream& rInput, EETextFormat eFormat, SvKeyValueIterator* pHTTPHeaderAttrs /* = NULL */ )
/*N*/ {DBG_BF_ASSERT(0, "STRIP");return 0; //STRIP001
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  sal_Bool bUndoEnabled = pImpEditEngine->IsUndoEnabled();
//STRIP001  pImpEditEngine->EnableUndo( sal_False );
//STRIP001  pImpEditEngine->SetText( XubString() );
//STRIP001  EditPaM aPaM( pImpEditEngine->GetEditDoc().GetStartPaM() );
//STRIP001  pImpEditEngine->Read( rInput, eFormat, EditSelection( aPaM, aPaM ), pHTTPHeaderAttrs );
//STRIP001  pImpEditEngine->EnableUndo( bUndoEnabled );
//STRIP001  return rInput.GetError();
/*N*/ }

#ifndef SVX_LIGHT
/*N*/ sal_uInt32 EditEngine::Write( SvStream& rOutput, EETextFormat eFormat )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  EditPaM aStartPaM( pImpEditEngine->GetEditDoc().GetStartPaM() );
//STRIP001  EditPaM aEndPaM( pImpEditEngine->GetEditDoc().GetEndPaM() );
//STRIP001  pImpEditEngine->Write( rOutput, eFormat, EditSelection( aStartPaM, aEndPaM ) );
//STRIP001  return rOutput.GetError();
/*N*/ }
#endif

/*N*/ EditTextObject*   EditEngine::CreateTextObject()
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return pImpEditEngine->CreateTextObject();
/*N*/ }

//STRIP001 EditTextObject*  EditEngine::CreateTextObject( const ESelection& rESelection )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  EditSelection aSel( pImpEditEngine->CreateSel( rESelection ) );
//STRIP001  return pImpEditEngine->CreateTextObject( aSel );
//STRIP001 }

/*N*/ void EditEngine::SetText( const EditTextObject& rTextObject )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/     pImpEditEngine->EnterBlockNotifications();
/*N*/   pImpEditEngine->SetText( rTextObject );
/*N*/   pImpEditEngine->FormatAndUpdate();
/*N*/     pImpEditEngine->LeaveBlockNotifications();
/*N*/ }

//STRIP001 void EditEngine::ShowParagraph( sal_uInt16 nParagraph, sal_Bool bShow )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  pImpEditEngine->ShowParagraph( nParagraph, bShow );
//STRIP001 }

//STRIP001 sal_Bool EditEngine::IsParagraphVisible( sal_uInt16 nParagraph )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  return pImpEditEngine->IsParagraphVisible( nParagraph );
//STRIP001 }

/*N*/ void EditEngine::SetNotifyHdl( const Link& rLink )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->SetNotifyHdl( rLink );
/*N*/ }

/*N*/ Link EditEngine::GetNotifyHdl() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return pImpEditEngine->GetNotifyHdl();
/*N*/ }

/*N*/ void EditEngine::SetStatusEventHdl( const Link& rLink )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->SetStatusEventHdl( rLink );
/*N*/ }

//STRIP001 Link EditEngine::GetStatusEventHdl() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  return pImpEditEngine->GetStatusEventHdl();
//STRIP001 }

//STRIP001 void EditEngine::SetImportHdl( const Link& rLink )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  pImpEditEngine->aImportHdl = rLink;
//STRIP001 }

//STRIP001 Link EditEngine::GetImportHdl() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  return pImpEditEngine->aImportHdl;
//STRIP001 }

/*N*/ void EditEngine::SetBeginMovingParagraphsHdl( const Link& rLink )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->aBeginMovingParagraphsHdl = rLink;
/*N*/ }

/*N*/ void EditEngine::SetEndMovingParagraphsHdl( const Link& rLink )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->aEndMovingParagraphsHdl = rLink;
/*N*/ }

/*N*/ void EditEngine::SetBeginPasteOrDropHdl( const Link& rLink )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->aBeginPasteOrDropHdl = rLink;
/*N*/ }

/*N*/ void EditEngine::SetEndPasteOrDropHdl( const Link& rLink )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->aEndPasteOrDropHdl = rLink;
/*N*/ }

/*N*/ EditTextObject*   EditEngine::CreateTextObject( sal_uInt16 nPara, sal_uInt16 nParas )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   DBG_ASSERT( nPara < pImpEditEngine->GetEditDoc().Count(), "CreateTextObject: Startpara out of Range" );
/*N*/   DBG_ASSERT( nPara+nParas-1 < pImpEditEngine->GetEditDoc().Count(), "CreateTextObject: Endpara out of Range" );
/*N*/
/*N*/   ContentNode* pStartNode = pImpEditEngine->GetEditDoc().SaveGetObject( nPara );
/*N*/   ContentNode* pEndNode = pImpEditEngine->GetEditDoc().SaveGetObject( nPara+nParas-1 );
/*N*/   DBG_ASSERT( pStartNode, "Start-Absatz existiert nicht: CreateTextObject" );
/*N*/   DBG_ASSERT( pEndNode, "End-Absatz existiert nicht: CreateTextObject" );
/*N*/
/*N*/   if ( pStartNode && pEndNode )
/*N*/   {
/*N*/       EditSelection aTmpSel;
/*N*/       aTmpSel.Min() = EditPaM( pStartNode, 0 );
/*N*/       aTmpSel.Max() = EditPaM( pEndNode, pEndNode->Len() );
/*N*/       return pImpEditEngine->CreateTextObject( aTmpSel );
/*N*/   }
/*N*/   return 0;
/*N*/ }

//STRIP001 void EditEngine::RemoveParagraph( sal_uInt16 nPara )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  DBG_ASSERT( pImpEditEngine->GetEditDoc().Count() > 1, "Der erste Absatz darf nicht geloescht werden!" );
//STRIP001  if( pImpEditEngine->GetEditDoc().Count() <= 1 )
//STRIP001      return;
//STRIP001
//STRIP001  ContentNode* pNode = pImpEditEngine->GetEditDoc().SaveGetObject( nPara );
//STRIP001  ParaPortion* pPortion = pImpEditEngine->GetParaPortions().SaveGetObject( nPara );
//STRIP001  DBG_ASSERT( pPortion && pNode, "Absatz nicht gefunden: RemoveParagraph" );
//STRIP001  if ( pNode && pPortion )
//STRIP001  {
//STRIP001      // Keine Undokappselung noetig.
//STRIP001      pImpEditEngine->ImpRemoveParagraph( nPara );
//STRIP001      pImpEditEngine->InvalidateFromParagraph( nPara );
//STRIP001      pImpEditEngine->UpdateSelections();
//STRIP001      pImpEditEngine->FormatAndUpdate();
//STRIP001  }
//STRIP001 }

/*N*/ sal_uInt16 EditEngine::GetTextLen( sal_uInt16 nPara ) const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   ContentNode* pNode = pImpEditEngine->GetEditDoc().SaveGetObject( nPara );
/*N*/   DBG_ASSERT( pNode, "Absatz nicht gefunden: GetTextLen" );
/*N*/   if ( pNode )
/*N*/       return pNode->Len();
/*N*/   return 0;
/*N*/ }

/*N*/ XubString EditEngine::GetText( sal_uInt16 nPara ) const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   XubString aStr;
/*N*/   if ( nPara < pImpEditEngine->GetEditDoc().Count() )
/*N*/       aStr = pImpEditEngine->GetEditDoc().GetParaAsString( nPara );
/*N*/   return aStr;
/*N*/ }

/*N*/ void EditEngine::SetModifyHdl( const Link& rLink )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->SetModifyHdl( rLink );
/*N*/ }

//STRIP001 Link EditEngine::GetModifyHdl() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  return pImpEditEngine->GetModifyHdl();
//STRIP001 }


/*N*/ void EditEngine::ClearModifyFlag()
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->SetModifyFlag( sal_False );
/*N*/ }

//STRIP001 void EditEngine::SetModified()
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  pImpEditEngine->SetModifyFlag( sal_True );
//STRIP001 }

/*N*/ sal_Bool EditEngine::IsModified() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return pImpEditEngine->IsModified();
/*N*/ }

//STRIP001 sal_Bool EditEngine::IsInSelectionMode() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  return ( pImpEditEngine->IsInSelectionMode() ||
//STRIP001              pImpEditEngine->GetSelEngine().IsInSelection() );
//STRIP001 }

//STRIP001 void EditEngine::StopSelectionMode()
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  pImpEditEngine->StopSelectionMode();
//STRIP001 }

//STRIP001 void EditEngine::InsertParagraph( sal_uInt16 nPara, const EditTextObject& rTxtObj )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  if ( nPara > GetParagraphCount() )
//STRIP001  {
//STRIP001      DBG_ASSERTWARNING( nPara == USHRT_MAX, "AbsatzNr zu Gro? aber nicht LIST_APPEND! " );
//STRIP001      nPara = GetParagraphCount();
//STRIP001  }
//STRIP001
//STRIP001  pImpEditEngine->UndoActionStart( EDITUNDO_INSERT );
//STRIP001
//STRIP001  // Keine Undoklammerung noetig.
//STRIP001  EditPaM aPaM( pImpEditEngine->InsertParagraph( nPara ) );
//STRIP001  // Bei einem InsertParagraph von aussen sollen keine Harten
//STRIP001  // Attribute uebernommen werden !
//STRIP001  pImpEditEngine->RemoveCharAttribs( nPara );
//STRIP001  pImpEditEngine->InsertText( rTxtObj, EditSelection( aPaM, aPaM ) );
//STRIP001
//STRIP001  pImpEditEngine->UndoActionEnd( EDITUNDO_INSERT );
//STRIP001
//STRIP001  pImpEditEngine->FormatAndUpdate();
//STRIP001 }

/*N*/ void EditEngine::InsertParagraph( sal_uInt16 nPara, const XubString& rTxt )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   if ( nPara > GetParagraphCount() )
/*N*/   {
/*?*/       DBG_ASSERTWARNING( nPara == USHRT_MAX, "AbsatzNr zu Gro? aber nicht LIST_APPEND! " );
/*?*/       nPara = GetParagraphCount();
/*N*/   }
/*N*/
/*N*/   pImpEditEngine->UndoActionStart( EDITUNDO_INSERT );
/*N*/   EditPaM aPaM( pImpEditEngine->InsertParagraph( nPara ) );
/*N*/   // Bei einem InsertParagraph von aussen sollen keine Harten
/*N*/   // Attribute uebernommen werden !
/*N*/   pImpEditEngine->RemoveCharAttribs( nPara );
/*N*/   pImpEditEngine->UndoActionEnd( EDITUNDO_INSERT );
/*N*/   pImpEditEngine->ImpInsertText( EditSelection( aPaM, aPaM ), rTxt );
/*N*/   pImpEditEngine->FormatAndUpdate();
/*N*/ }

//STRIP001 void EditEngine::SetText( sal_uInt16 nPara, const EditTextObject& rTxtObj )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  EditSelection* pSel = pImpEditEngine->SelectParagraph( nPara );
//STRIP001  if ( pSel )
//STRIP001  {
//STRIP001      pImpEditEngine->UndoActionStart( EDITUNDO_INSERT );
//STRIP001      pImpEditEngine->InsertText( rTxtObj, *pSel );
//STRIP001      pImpEditEngine->UndoActionEnd( EDITUNDO_INSERT );
//STRIP001      pImpEditEngine->FormatAndUpdate();
//STRIP001      delete pSel;
//STRIP001  }
//STRIP001 }

/*N*/ void EditEngine::SetText( sal_uInt16 nPara, const XubString& rTxt )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   EditSelection* pSel = pImpEditEngine->SelectParagraph( nPara );
/*N*/   if ( pSel )
/*N*/   {
/*N*/       pImpEditEngine->UndoActionStart( EDITUNDO_INSERT );
/*N*/       pImpEditEngine->ImpInsertText( *pSel, rTxt );
/*N*/       pImpEditEngine->UndoActionEnd( EDITUNDO_INSERT );
/*N*/       pImpEditEngine->FormatAndUpdate();
/*N*/       delete pSel;
/*N*/   }
/*N*/ }

/*N*/ void EditEngine::SetParaAttribs( sal_uInt16 nPara, const SfxItemSet& rSet )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   // Keine Undoklammerung noetig.
/*N*/   pImpEditEngine->SetParaAttribs( nPara, rSet );
/*N*/   pImpEditEngine->FormatAndUpdate();
/*N*/ }

/*N*/ const SfxItemSet& EditEngine::GetParaAttribs( sal_uInt16 nPara ) const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return pImpEditEngine->GetParaAttribs( nPara );
/*N*/ }

/*N*/ sal_Bool EditEngine::HasParaAttrib( sal_uInt16 nPara, sal_uInt16 nWhich ) const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return pImpEditEngine->HasParaAttrib( nPara, nWhich );
/*N*/ }

/*N*/ const SfxPoolItem& EditEngine::GetParaAttrib( sal_uInt16 nPara, sal_uInt16 nWhich )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/     return pImpEditEngine->GetParaAttrib( nPara, nWhich );
/*N*/ }

/*N*/ void EditEngine::GetCharAttribs( sal_uInt16 nPara, EECharAttribArray& rLst ) const
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  pImpEditEngine->GetCharAttribs( nPara, rLst );
/*N*/ }

/*N*/ SfxItemSet EditEngine::GetAttribs( const ESelection& rSel, BOOL bOnlyHardAttrib )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   EditSelection aSel( pImpEditEngine->
/*N*/       ConvertSelection( rSel.nStartPara, rSel.nStartPos, rSel.nEndPara, rSel.nEndPos ) );
/*N*/   return pImpEditEngine->GetAttribs( aSel, bOnlyHardAttrib );
/*N*/ }

/*N*/ SfxItemSet EditEngine::GetAttribs( USHORT nPara, USHORT nStart, USHORT nEnd, sal_uInt8 nFlags ) const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return pImpEditEngine->GetAttribs( nPara, nStart, nEnd, nFlags );
/*N*/ }

//STRIP001 void EditEngine::RemoveAttribs( const ESelection& rSelection, sal_Bool bRemoveParaAttribs, sal_uInt16 nWhich )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001
//STRIP001  pImpEditEngine->UndoActionStart( EDITUNDO_RESETATTRIBS );
//STRIP001  EditSelection aSel( pImpEditEngine->ConvertSelection( rSelection.nStartPara, rSelection.nStartPos, rSelection.nEndPara, rSelection.nEndPos ) );
//STRIP001  pImpEditEngine->RemoveCharAttribs( aSel, bRemoveParaAttribs, nWhich  );
//STRIP001  pImpEditEngine->UndoActionEnd( EDITUNDO_RESETATTRIBS );
//STRIP001  pImpEditEngine->FormatAndUpdate();
//STRIP001 }

// MT: Can be removed after 6.x?
//STRIP001 Font EditEngine::GetStandardFont( sal_uInt16 nPara )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  return GetStandardSvxFont( nPara );
//STRIP001 }

//STRIP001 SvxFont EditEngine::GetStandardSvxFont( sal_uInt16 nPara )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  ContentNode* pNode = pImpEditEngine->GetEditDoc().SaveGetObject( nPara );
//STRIP001  return pNode->GetCharAttribs().GetDefFont();
//STRIP001 }

/*N*/ void EditEngine::StripPortions()
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   VirtualDevice aTmpDev;
/*N*/   Rectangle aBigRec( Point( 0, 0 ), Size( 0x7FFFFFFF, 0x7FFFFFFF ) );
/*N*/   if ( IsVertical() )
/*N*/   {
/*?*/       aBigRec.Right() = 0;
/*?*/       aBigRec.Left() = -0x7FFFFFFF;
/*N*/   }
/*N*/   pImpEditEngine->Paint( &aTmpDev, aBigRec, Point(), sal_True );
/*N*/ }

/*N*/ void EditEngine::GetPortions( sal_uInt16 nPara, SvUShorts& rList )
/*N*/ {
/*N*/   if ( !pImpEditEngine->IsFormatted() )
/*N*/       pImpEditEngine->FormatFullDoc();
/*N*/
/*N*/   ParaPortion* pParaPortion = pImpEditEngine->GetParaPortions().SaveGetObject( nPara );
/*N*/   if ( pParaPortion )
/*N*/   {
/*N*/       sal_uInt16 nEnd = 0;
/*N*/       sal_uInt16 nTextPortions = pParaPortion->GetTextPortions().Count();
/*N*/       for ( sal_uInt16 n = 0; n < nTextPortions; n++ )
/*N*/       {
/*N*/           nEnd += pParaPortion->GetTextPortions()[n]->GetLen();
/*N*/           rList.Insert( nEnd, rList.Count() );
/*N*/       }
/*N*/   }
/*N*/ }

//STRIP001 void EditEngine::SetFlatMode( sal_Bool bFlat)
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  pImpEditEngine->SetFlatMode( bFlat );
//STRIP001 }

/*N*/ sal_Bool EditEngine::IsFlatMode() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return !( pImpEditEngine->aStatus.UseCharAttribs() );
/*N*/ }

/*N*/ void EditEngine::SetControlWord( sal_uInt32 nWord )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/
/*N*/   if ( nWord != pImpEditEngine->aStatus.GetControlWord() )
/*N*/   {
/*N*/       sal_uInt32 nPrev = pImpEditEngine->aStatus.GetControlWord();
/*N*/       pImpEditEngine->aStatus.GetControlWord() = nWord;
/*N*/
/*N*/       sal_uInt32 nChanges = nPrev ^ nWord;
/*N*/       if ( pImpEditEngine->IsFormatted() )
/*N*/       {
/*N*/           // ggf. neu formatieren:
/*N*/           if ( ( nChanges & EE_CNTRL_USECHARATTRIBS ) ||
/*N*/                ( nChanges & EE_CNTRL_USEPARAATTRIBS ) ||
/*N*/                ( nChanges & EE_CNTRL_ONECHARPERLINE ) ||
/*N*/                ( nChanges & EE_CNTRL_STRETCHING ) ||
/*N*/                ( nChanges & EE_CNTRL_OUTLINER ) ||
/*N*/                ( nChanges & EE_CNTRL_NOCOLORS ) ||
/*N*/                ( nChanges & EE_CNTRL_OUTLINER2 ) )
/*N*/           {
/*N*/               if ( ( nChanges & EE_CNTRL_USECHARATTRIBS ) ||
/*N*/                    ( nChanges & EE_CNTRL_USEPARAATTRIBS ) )
/*N*/               {
/*?*/                   sal_Bool bUseCharAttribs = ( nWord & EE_CNTRL_USECHARATTRIBS ) ? sal_True : sal_False;
/*?*/                   pImpEditEngine->GetEditDoc().CreateDefFont( bUseCharAttribs );
/*N*/               }
/*N*/
/*N*/               pImpEditEngine->FormatFullDoc();
/*N*/               pImpEditEngine->UpdateViews( pImpEditEngine->GetActiveView() );
/*N*/           }
/*N*/       }
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/       sal_Bool bSpellingChanged = nChanges & EE_CNTRL_ONLINESPELLING ? sal_True : sal_False;
/*N*/       sal_Bool bRedLinesChanged = nChanges & EE_CNTRL_NOREDLINES ? sal_True : sal_False;
/*N*/
/*N*/       if ( bSpellingChanged || bRedLinesChanged )
/*N*/       {
/*N*/           pImpEditEngine->StopOnlineSpellTimer();
/*N*/           if ( bSpellingChanged && ( nWord & EE_CNTRL_ONLINESPELLING ) )
/*N*/           {
/*?*/               // WrongListen anlegen, Timer starten...
/*?*/               sal_uInt16 nNodes = pImpEditEngine->GetEditDoc().Count();
/*?*/               for ( sal_uInt16 n = 0; n < nNodes; n++ )
/*?*/               {
/*?*/                   ContentNode* pNode = pImpEditEngine->GetEditDoc().GetObject( n );
/*?*/                   pNode->CreateWrongList();
/*?*/               }
/*?*/               pImpEditEngine->StartOnlineSpellTimer();
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               long nY = 0;
/*N*/               sal_uInt16 nNodes = pImpEditEngine->GetEditDoc().Count();
/*N*/               for ( sal_uInt16 n = 0; n < nNodes; n++ )
/*N*/               {
/*N*/                   ContentNode* pNode = pImpEditEngine->GetEditDoc().GetObject( n );
/*N*/                   ParaPortion* pPortion = pImpEditEngine->GetParaPortions().GetObject( n );
/*N*/                   sal_Bool bWrongs = ( bSpellingChanged || ( nWord & EE_CNTRL_ONLINESPELLING ) ) ? pNode->GetWrongList()->HasWrongs() : sal_False;
/*N*/                   if ( bSpellingChanged )         // Also aus
/*?*/                       pNode->DestroyWrongList();  // => vorm Paint weghaun.
/*N*/                   if ( bWrongs )
/*N*/                   {
/*?*/                       pImpEditEngine->aInvalidRec.Left() = 0;
/*?*/                       pImpEditEngine->aInvalidRec.Right() = pImpEditEngine->GetPaperSize().Width();
/*?*/                       pImpEditEngine->aInvalidRec.Top() = nY+1;
/*?*/                       pImpEditEngine->aInvalidRec.Bottom() = nY+pPortion->GetHeight()-1;
/*?*/                       pImpEditEngine->UpdateViews( pImpEditEngine->pActiveView );
/*N*/                   }
/*N*/                   nY += pPortion->GetHeight();
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/ #endif // !SVX_LIGHT
/*N*/   }
/*N*/ }

/*N*/ sal_uInt32 EditEngine::GetControlWord() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return pImpEditEngine->aStatus.GetControlWord();
/*N*/ }

//STRIP001 long EditEngine::GetFirstLineStartX( sal_uInt16 nParagraph )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001
//STRIP001  long nX = 0;
//STRIP001  ParaPortion* pPPortion = pImpEditEngine->GetParaPortions().SaveGetObject( nParagraph );
//STRIP001  if ( pPPortion )
//STRIP001  {
//STRIP001      DBG_ASSERT( pImpEditEngine->IsFormatted() || !pImpEditEngine->IsFormatting(), "GetFirstLineStartX: Doc not formatted - unable to format!" );
//STRIP001      if ( !pImpEditEngine->IsFormatted() )
//STRIP001          pImpEditEngine->FormatDoc();
//STRIP001      EditLine* pFirstLine = pPPortion->GetLines()[0];
//STRIP001      nX = pFirstLine->GetStartPosX();
//STRIP001  }
//STRIP001  return nX;
//STRIP001 }

/*N*/ Point EditEngine::GetDocPos( const Point& rPaperPos ) const
/*N*/ {
/*N*/   Point aDocPos( rPaperPos );
/*N*/   if ( IsVertical() )
/*N*/   {
/*?*/       aDocPos.X() = rPaperPos.Y();
/*?*/       aDocPos.Y() = GetPaperSize().Width() - rPaperPos.X();
/*N*/   }
/*N*/   return aDocPos;
/*N*/ }

/*N*/ Point EditEngine::GetDocPosTopLeft( sal_uInt16 nParagraph )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   ParaPortion* pPPortion = pImpEditEngine->GetParaPortions().SaveGetObject( nParagraph );
/*N*/   DBG_ASSERT( pPPortion, "Absatz nicht gefunden: GetWindowPosTopLeft" );
/*N*/   Point aPoint;
/*N*/   if ( pPPortion )
/*N*/   {
/*N*/       // Falls jemand mit einer leeren Engine ein GetLineHeight() macht.
/*N*/       DBG_ASSERT( pImpEditEngine->IsFormatted() || !pImpEditEngine->IsFormatting(), "GetDocPosTopLeft: Doc not formatted - unable to format!" );
/*N*/       if ( !pImpEditEngine->IsFormatted() )
/*?*/           pImpEditEngine->FormatAndUpdate();
/*N*/       if ( pPPortion->GetLines().Count() )
/*N*/       {
/*N*/           // So richtiger, falls grosses Bullet.
/*N*/           EditLine* pFirstLine = pPPortion->GetLines()[0];
/*N*/           aPoint.X() = pFirstLine->GetStartPosX();
/*N*/       }
/*N*/       else
/*N*/       {
/*?*/           const SvxLRSpaceItem& rLRItem = pImpEditEngine->GetLRSpaceItem( pPPortion->GetNode() );
/*?*/           aPoint.X() = pImpEditEngine->GetXValue( (short)(rLRItem.GetTxtLeft() + rLRItem.GetTxtFirstLineOfst()) );
/*N*/       }
/*N*/       aPoint.Y() = pImpEditEngine->GetParaPortions().GetYOffset( pPPortion );
/*N*/   }
/*N*/   return aPoint;
/*N*/ }

//STRIP001 BOOL EditEngine::IsRightToLeft( USHORT nPara ) const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001     return pImpEditEngine->IsRightToLeft( nPara );
//STRIP001 }

/*N*/ sal_Bool EditEngine::IsTextPos( const Point& rPaperPos, sal_uInt16 nBorder )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/
/*N*/   if ( !pImpEditEngine->IsFormatted() )
/*?*/       pImpEditEngine->FormatDoc();
/*N*/
/*N*/   sal_Bool bTextPos = sal_False;
/*N*/   // #90780# take unrotated positions for calculation here
/*N*/   Point aDocPos = GetDocPos( rPaperPos );
/*N*/
/*N*/   if ( ( aDocPos.Y() > 0  ) && ( aDocPos.Y() < (long)pImpEditEngine->GetTextHeight() ) )
/*N*/   {
/*N*/       EditPaM aPaM = pImpEditEngine->GetPaM( aDocPos, sal_False );
/*N*/       if ( aPaM.GetNode() )
/*N*/       {
/*N*/           ParaPortion* pParaPortion = pImpEditEngine->FindParaPortion( aPaM.GetNode() );
/*N*/           DBG_ASSERT( pParaPortion, "ParaPortion?" );
/*N*/
/*N*/             sal_uInt16 nLine = pParaPortion->GetLineNumber( aPaM.GetIndex() );
/*N*/             EditLine* pLine = pParaPortion->GetLines().GetObject( nLine );
/*N*/             Range aLineXPosStartEnd = pImpEditEngine->GetLineXPosStartEnd( pParaPortion, pLine );
/*N*/           if ( ( aDocPos.X() >= aLineXPosStartEnd.Min() - nBorder ) &&
/*N*/                ( aDocPos.X() <= aLineXPosStartEnd.Max() + nBorder ) )
/*N*/           {
/*N*/                bTextPos = sal_True;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return bTextPos;
/*N*/ }

/*N*/ void EditEngine::SetEditTextObjectPool( SfxItemPool* pPool )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->SetEditTextObjectPool( pPool );
/*N*/ }

/*N*/ SfxItemPool* EditEngine::GetEditTextObjectPool() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return pImpEditEngine->GetEditTextObjectPool();
/*N*/ }

/*N*/ void EditEngine::QuickSetAttribs( const SfxItemSet& rSet, const ESelection& rSel )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/
/*N*/   EditSelection aSel( pImpEditEngine->
/*N*/       ConvertSelection( rSel.nStartPara, rSel.nStartPos, rSel.nEndPara, rSel.nEndPos ) );
/*N*/
/*N*/   pImpEditEngine->SetAttribs( aSel, rSet );
/*N*/ }

//STRIP001 void EditEngine::QuickMarkInvalid( const ESelection& rSel )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  DBG_ASSERT( rSel.nStartPara < pImpEditEngine->GetEditDoc().Count(), "MarkInvalid: Start out of Range!" );
//STRIP001  DBG_ASSERT( rSel.nEndPara < pImpEditEngine->GetEditDoc().Count(), "MarkInvalid: End out of Range!" );
//STRIP001  for ( sal_uInt16 nPara = rSel.nStartPara; nPara <= rSel.nEndPara; nPara++ )
//STRIP001  {
//STRIP001      ParaPortion* pPortion = pImpEditEngine->GetParaPortions().SaveGetObject( nPara );
//STRIP001      if ( pPortion )
//STRIP001          pPortion->MarkSelectionInvalid( 0, pPortion->GetNode()->Len() );
//STRIP001  }
//STRIP001 }

/*N*/ void EditEngine::QuickInsertText( const XubString& rText, const ESelection& rSel )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/
/*N*/   EditSelection aSel( pImpEditEngine->
/*N*/       ConvertSelection( rSel.nStartPara, rSel.nStartPos, rSel.nEndPara, rSel.nEndPos ) );
/*N*/
/*N*/   pImpEditEngine->ImpInsertText( aSel, rText );
/*N*/ }

/*N*/ void EditEngine::QuickDelete( const ESelection& rSel )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/
/*N*/   EditSelection aSel( pImpEditEngine->
/*N*/       ConvertSelection( rSel.nStartPara, rSel.nStartPos, rSel.nEndPara, rSel.nEndPos ) );
/*N*/
/*N*/   pImpEditEngine->ImpDeleteSelection( aSel );
/*N*/ }

//STRIP001 void EditEngine::QuickMarkToBeRepainted( sal_uInt16 nPara )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  ParaPortion* pPortion = pImpEditEngine->GetParaPortions().SaveGetObject( nPara );
//STRIP001  if ( pPortion )
//STRIP001      pPortion->SetMustRepaint( sal_True );
//STRIP001 }

/*N*/ void EditEngine::QuickInsertLineBreak( const ESelection& rSel )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/
/*N*/   EditSelection aSel( pImpEditEngine->
/*N*/       ConvertSelection( rSel.nStartPara, rSel.nStartPos, rSel.nEndPara, rSel.nEndPos ) );
/*N*/
/*N*/   pImpEditEngine->InsertLineBreak( aSel );
/*N*/ }

/*N*/ void EditEngine::QuickInsertField( const SvxFieldItem& rFld, const ESelection& rSel )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/
/*N*/   EditSelection aSel( pImpEditEngine->
/*N*/       ConvertSelection( rSel.nStartPara, rSel.nStartPos, rSel.nEndPara, rSel.nEndPos ) );
/*N*/
/*N*/   pImpEditEngine->ImpInsertFeature( aSel, rFld );
/*N*/ }

/*N*/ void EditEngine::QuickFormatDoc( sal_Bool bFull )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   if ( bFull )
/*N*/       pImpEditEngine->FormatFullDoc();
/*N*/   else
/*N*/       pImpEditEngine->FormatDoc();
/*N*/   pImpEditEngine->UpdateViews( pImpEditEngine->GetActiveView() );
/*N*/ }

/*N*/ void EditEngine::QuickRemoveCharAttribs( sal_uInt16 nPara, sal_uInt16 nWhich )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->RemoveCharAttribs( nPara, nWhich );
/*N*/ }

/*N*/ void EditEngine::SetStyleSheet( sal_uInt16 nPara, SfxStyleSheet* pStyle )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->SetStyleSheet( nPara, pStyle );
/*N*/ }

/*N*/ SfxStyleSheet* EditEngine::GetStyleSheet( sal_uInt16 nPara ) const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return pImpEditEngine->GetStyleSheet( nPara );
/*N*/ }

/*N*/ void EditEngine::SetStyleSheetPool( SfxStyleSheetPool* pSPool )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->SetStyleSheetPool( pSPool );
/*N*/ }

/*N*/ SfxStyleSheetPool* EditEngine::GetStyleSheetPool()
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return pImpEditEngine->GetStyleSheetPool();
/*N*/ }

/*N*/ void EditEngine::SetWordDelimiters( const XubString& rDelimiters )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->aWordDelimiters = rDelimiters;
/*N*/   if ( pImpEditEngine->aWordDelimiters.Search( CH_FEATURE ) == STRING_NOTFOUND )
/*N*/       pImpEditEngine->aWordDelimiters.Insert( CH_FEATURE );
/*N*/ }

/*N*/ XubString EditEngine::GetWordDelimiters() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return pImpEditEngine->aWordDelimiters;
/*N*/ }

//STRIP001 void EditEngine::SetGroupChars( const XubString& rChars )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  DBG_ASSERT( ( rChars.Len() % 2 ) == 0, "SetGroupChars: Ungerade Anzahl!" );
//STRIP001  pImpEditEngine->aGroupChars = rChars;
//STRIP001 }

//STRIP001 XubString EditEngine::GetGroupChars() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  return pImpEditEngine->aGroupChars;
//STRIP001 }

//STRIP001 void EditEngine::EnablePasteSpecial( sal_Bool bEnable )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  if ( bEnable )
//STRIP001      pImpEditEngine->GetStatus().TurnOnFlags( EE_CNTRL_PASTESPECIAL );
//STRIP001  else
//STRIP001      pImpEditEngine->GetStatus().TurnOffFlags( EE_CNTRL_PASTESPECIAL );
//STRIP001 }

//STRIP001 sal_Bool EditEngine::IsPasteSpecialEnabled() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  return pImpEditEngine->GetStatus().AllowPasteSpecial();
//STRIP001 }

//STRIP001 void EditEngine::EnableIdleFormatter( sal_Bool bEnable )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  if ( bEnable )
//STRIP001      pImpEditEngine->GetStatus().TurnOnFlags( EE_CNTRL_DOIDLEFORMAT );
//STRIP001  else
//STRIP001      pImpEditEngine->GetStatus().TurnOffFlags( EE_CNTRL_DOIDLEFORMAT);
//STRIP001 }

//STRIP001 sal_Bool EditEngine::IsIdleFormatterEnabled() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  return pImpEditEngine->GetStatus().UseIdleFormatter();
//STRIP001 }

/*N*/ void EditEngine::EraseVirtualDevice()
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->EraseVirtualDevice();
/*N*/ }

/*N*/ void EditEngine::SetSpeller( Reference< XSpellChecker1 >  &xSpeller )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->SetSpeller( xSpeller );
/*N*/ }
//STRIP001 Reference< XSpellChecker1 >  EditEngine::GetSpeller()
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  return pImpEditEngine->GetSpeller();
//STRIP001 }
//STRIP001 Reference< XHyphenator >  EditEngine::GetHyphenator() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  return pImpEditEngine->GetHyphenator();
//STRIP001 }

/*N*/ void EditEngine::SetHyphenator( Reference< XHyphenator > & xHyph )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->SetHyphenator( xHyph );
/*N*/ }

/*N*/ void EditEngine::SetForbiddenCharsTable( vos::ORef<SvxForbiddenCharactersTable> xForbiddenChars )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->SetForbiddenCharsTable( xForbiddenChars );
/*N*/ }

//STRIP001 vos::ORef<SvxForbiddenCharactersTable> EditEngine::GetForbiddenCharsTable() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  return pImpEditEngine->GetForbiddenCharsTable( FALSE );
//STRIP001 }


/*N*/ void EditEngine::SetDefaultLanguage( LanguageType eLang )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->SetDefaultLanguage( eLang );
/*N*/ }

//STRIP001 LanguageType EditEngine::GetDefaultLanguage() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  return pImpEditEngine->GetDefaultLanguage();
//STRIP001 }

//STRIP001 sal_Bool __EXPORT EditEngine::SpellNextDocument()
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  return sal_False;
//STRIP001 }

//STRIP001 EESpellState EditEngine::HasSpellErrors( LanguageType eLang )
//STRIP001 {
//STRIP001 #if SUPD >= 630
//STRIP001 //   DBG_ERROR( "DefaultLanguage not longer supported" );
//STRIP001 #endif
//STRIP001  return HasSpellErrors();
//STRIP001 }

//STRIP001 EESpellState EditEngine::HasSpellErrors()
//STRIP001 {
//STRIP001 #ifdef SVX_LIGHT
//STRIP001  return EE_SPELL_NOSPELLER;
//STRIP001 #else
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  if ( !pImpEditEngine->GetSpeller().is()  )
//STRIP001      return EE_SPELL_NOSPELLER;
//STRIP001
//STRIP001  return pImpEditEngine->HasSpellErrors();
//STRIP001 #endif
//STRIP001 }

//STRIP001 sal_Bool EditEngine::HasText( const SvxSearchItem& rSearchItem )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  return pImpEditEngine->HasText( rSearchItem );
//STRIP001 }

/*N*/ void EditEngine::SetGlobalCharStretching( sal_uInt16 nX, sal_uInt16 nY )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->SetCharStretching( nX, nY );
/*N*/ }

//STRIP001 void EditEngine::GetGlobalCharStretching( sal_uInt16& rX, sal_uInt16& rY )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  pImpEditEngine->GetCharStretching( rX, rY );
//STRIP001 }

/*N*/ void EditEngine::DoStretchChars( sal_uInt16 nX, sal_uInt16 nY )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   pImpEditEngine->DoStretchChars( nX, nY );
/*N*/ }

//STRIP001 void EditEngine::SetBigTextObjectStart( sal_uInt16 nStartAtPortionCount )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  pImpEditEngine->SetBigTextObjectStart( nStartAtPortionCount );
//STRIP001 }

//STRIP001 sal_uInt16 EditEngine::GetBigTextObjectStart() const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  return pImpEditEngine->GetBigTextObjectStart();
//STRIP001 }

/*N*/ sal_Bool EditEngine::ShouldCreateBigTextObject() const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   sal_uInt16 nTextPortions = 0;
/*N*/   sal_uInt16 nParas = pImpEditEngine->GetEditDoc().Count();
/*N*/   for ( sal_uInt16 nPara = 0; nPara < nParas; nPara++  )
/*N*/   {
/*N*/       ParaPortion* pParaPortion = pImpEditEngine->GetParaPortions()[nPara];
/*N*/       nTextPortions += pParaPortion->GetTextPortions().Count();
/*N*/   }
/*N*/   return ( nTextPortions >= pImpEditEngine->GetBigTextObjectStart() ) ? sal_True : sal_False;
/*N*/ }

/*N*/ USHORT EditEngine::GetFieldCount( USHORT nPara ) const
/*N*/ {
/*N*/     USHORT nFields = 0;
/*N*/     ContentNode* pNode = pImpEditEngine->GetEditDoc().SaveGetObject( nPara );
/*N*/     if ( pNode )
/*N*/     {
/*N*/       const CharAttribArray& rAttrs = pNode->GetCharAttribs().GetAttribs();
/*N*/       for ( sal_uInt16 nAttr = 0; nAttr < rAttrs.Count(); nAttr++ )
/*N*/       {
/*N*/           EditCharAttrib* pAttr = rAttrs[nAttr];
/*N*/           if ( pAttr->Which() == EE_FEATURE_FIELD )
/*N*/                 nFields++;
/*N*/       }
/*N*/     }
/*N*/
/*N*/     return nFields;
/*N*/ }

/*N*/ EFieldInfo EditEngine::GetFieldInfo( USHORT nPara, USHORT nField ) const
/*N*/ {
/*N*/     ContentNode* pNode = pImpEditEngine->GetEditDoc().SaveGetObject( nPara );
/*N*/     if ( pNode )
/*N*/     {
/*N*/         USHORT nCurrentField = 0;
/*N*/       const CharAttribArray& rAttrs = pNode->GetCharAttribs().GetAttribs();
/*N*/       for ( sal_uInt16 nAttr = 0; nAttr < rAttrs.Count(); nAttr++ )
/*N*/       {
/*N*/           EditCharAttrib* pAttr = rAttrs[nAttr];
/*N*/           if ( pAttr->Which() == EE_FEATURE_FIELD )
/*N*/             {
/*N*/                 if ( nCurrentField == nField )
/*N*/                 {
/*N*/                     EFieldInfo aInfo( *(const SvxFieldItem*)pAttr->GetItem(), nPara, pAttr->GetStart() );
/*N*/                     aInfo.aCurrentText = ((EditCharAttribField*)pAttr)->GetFieldValue();
/*N*/                     return aInfo;
/*N*/                 }
/*N*/
/*N*/                 nCurrentField++;
/*N*/             }
/*N*/       }
/*N*/     }
/*N*/     return EFieldInfo();
/*N*/ }


/*N*/ sal_Bool EditEngine::UpdateFields()
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   sal_Bool bChanges = pImpEditEngine->UpdateFields();
/*N*/   if ( bChanges )
/*N*/       pImpEditEngine->FormatAndUpdate();
/*N*/   return bChanges;
/*N*/ }

//STRIP001 void EditEngine::RemoveFields( sal_Bool bKeepFieldText, TypeId aType )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001
//STRIP001  if ( bKeepFieldText )
//STRIP001      pImpEditEngine->UpdateFields();
//STRIP001
//STRIP001  sal_uInt16 nParas = pImpEditEngine->GetEditDoc().Count();
//STRIP001  for ( sal_uInt16 nPara = 0; nPara < nParas; nPara++  )
//STRIP001  {
//STRIP001      ContentNode* pNode = pImpEditEngine->GetEditDoc().GetObject( nPara );
//STRIP001      const CharAttribArray& rAttrs = pNode->GetCharAttribs().GetAttribs();
//STRIP001      for ( sal_uInt16 nAttr = rAttrs.Count(); nAttr; )
//STRIP001      {
//STRIP001          const EditCharAttrib* pAttr = rAttrs[--nAttr];
//STRIP001          if ( pAttr->Which() == EE_FEATURE_FIELD )
//STRIP001          {
//STRIP001              const SvxFieldData* pFldData = ((const SvxFieldItem*)pAttr->GetItem())->GetField();
//STRIP001              if ( pFldData && ( !aType || ( pFldData->IsA( aType ) ) ) )
//STRIP001              {
//STRIP001                  DBG_ASSERT( pAttr->GetItem()->ISA( SvxFieldItem ), "Kein FeldItem..." );
//STRIP001                  EditSelection aSel( EditPaM( pNode, pAttr->GetStart() ), EditPaM( pNode, pAttr->GetEnd() ) );
//STRIP001                  String aFieldText = ((EditCharAttribField*)pAttr)->GetFieldValue();
//STRIP001                  pImpEditEngine->ImpInsertText( aSel, aFieldText );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*N*/ sal_Bool EditEngine::HasOnlineSpellErrors() const
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   sal_uInt16 nNodes = pImpEditEngine->GetEditDoc().Count();
/*N*/   for ( sal_uInt16 n = 0; n < nNodes; n++ )
/*N*/   {
/*N*/       ContentNode* pNode = pImpEditEngine->GetEditDoc().GetObject( n );
/*N*/       if ( pNode->GetWrongList() && pNode->GetWrongList()->Count() )
/*N*/           return sal_True;
/*N*/   }
/*N*/ #endif // !SVX_LIGHT
/*N*/   return sal_False;
/*N*/ }

/*N*/ void EditEngine::CompleteOnlineSpelling()
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   if ( pImpEditEngine->GetStatus().DoOnlineSpelling() )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 pImpEditEngine->StopOnlineSpellTimer();
//STRIP001 /*?*/        pImpEditEngine->DoOnlineSpelling( 0, sal_True, sal_False );
/*N*/   }
/*N*/ #endif SVX_LIGHT
/*N*/ }

/*N*/ USHORT EditEngine::FindParagraph( long nDocPosY )
/*N*/ {
/*N*/   return pImpEditEngine->GetParaPortions().FindParagraph( nDocPosY );
/*N*/ }

/*N*/ EPosition EditEngine::FindDocPosition( const Point& rDocPos ) const
/*N*/ {
/*N*/     EPosition aPos;
/*N*/     // From the point of the API, this is const....
/*N*/     EditPaM aPaM = ((EditEngine*)this)->pImpEditEngine->GetPaM( rDocPos, FALSE );
/*N*/     if ( aPaM.GetNode() )
/*N*/     {
/*N*/         aPos.nPara = pImpEditEngine->aEditDoc.GetPos( aPaM.GetNode() );
/*N*/         aPos.nIndex = aPaM.GetIndex();
/*N*/     }
/*N*/     return aPos;
/*N*/ }

/*N*/ Rectangle EditEngine::GetCharacterBounds( const EPosition& rPos ) const
/*N*/ {
/*N*/     Rectangle aBounds;
/*N*/     ContentNode* pNode = pImpEditEngine->GetEditDoc().SaveGetObject( rPos.nPara );
/*N*/
/*N*/   // #109151# Check against index, not paragraph
/*N*/     if ( pNode && ( rPos.nIndex < pNode->Len() ) )
/*N*/     {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        aBounds = pImpEditEngine->PaMtoEditCursor( EditPaM( pNode, rPos.nIndex ), GETCRSR_TXTONLY );
//STRIP001 /*?*/        Rectangle aR2 = pImpEditEngine->PaMtoEditCursor( EditPaM( pNode, rPos.nIndex+1 ), GETCRSR_TXTONLY|GETCRSR_ENDOFLINE );
//STRIP001 /*?*/         if ( aR2.Right() > aBounds.Right() )
//STRIP001 /*?*/             aBounds.Right() = aR2.Right();
/*N*/     }
/*N*/     return aBounds;
/*N*/ }

/*N*/ ParagraphInfos EditEngine::GetParagraphInfos( sal_uInt16 nPara )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/
/*N*/   // Funktioniert nur, wenn nicht bereits in der Formatierung...
/*N*/   if ( !pImpEditEngine->IsFormatted() )
/*N*/       pImpEditEngine->FormatDoc();
/*N*/
/*N*/   ParagraphInfos aInfos;
/*N*/   aInfos.bValid = pImpEditEngine->IsFormatted();
/*N*/   if ( pImpEditEngine->IsFormatted() )
/*N*/   {
/*?*/       ParaPortion* pParaPortion = pImpEditEngine->GetParaPortions()[nPara];
/*?*/       EditLine* pLine = pParaPortion ? pParaPortion->GetLines().GetObject( 0 ) : NULL;
/*?*/       DBG_ASSERT( pParaPortion && pLine, "GetParagraphInfos - Paragraph out of range" );
/*?*/       if ( pParaPortion && pLine )
/*?*/       {
/*?*/           aInfos.nParaHeight = (USHORT)pParaPortion->GetHeight();
/*?*/           aInfos.nLines = pParaPortion->GetLines().Count();
/*?*/           aInfos.nFirstLineStartX = pLine->GetStartPosX();
/*?*/           aInfos.nFirstLineOffset = pParaPortion->GetFirstLineOffset();
/*?*/           aInfos.nFirstLineHeight = pLine->GetHeight();
/*?*/           aInfos.nFirstLineTextHeight = pLine->GetTxtHeight();
/*?*/           aInfos.nFirstLineMaxAscent = pLine->GetMaxAscent();
/*?*/       }
/*N*/   }
/*N*/   return aInfos;
/*N*/ }

//STRIP001 ::com::sun::star::uno::Reference< ::com::sun::star::datatransfer::XTransferable >
//STRIP001                  EditEngine::CreateTransferable( const ESelection& rSelection ) const
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001  EditSelection aSel( pImpEditEngine->CreateSel( rSelection ) );
//STRIP001  return pImpEditEngine->CreateTransferable( aSel );
//STRIP001 }

// =====================================================================
// ======================   Virtuelle Methoden   =======================
// =====================================================================
/*N*/ void __EXPORT EditEngine::DrawingText( const Point&, const XubString&, USHORT nTextStart, USHORT nTextLen, const long*, const SvxFont&, sal_uInt16 nPara, sal_uInt16 nIndex, BYTE nRightToLeft )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/ }

/*N*/ void __EXPORT EditEngine::PaintingFirstLine( sal_uInt16, const Point&, long, const Point&, short, OutputDevice* )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/ }

/*N*/ void __EXPORT EditEngine::ParagraphInserted( sal_uInt16 nPara )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/
/*N*/     if ( GetNotifyHdl().IsSet() )
/*N*/     {
/*?*/         DBG_BF_ASSERT(0, "STRIP"); //STRIP001 EENotify aNotify( EE_NOTIFY_PARAGRAPHINSERTED );
//STRIP001 /*?*/         aNotify.pEditEngine = this;
//STRIP001 /*?*/         aNotify.nParagraph = nPara;
//STRIP001 /*?*/         pImpEditEngine->CallNotify( aNotify );
/*N*/     }
/*N*/ }

/*N*/ void __EXPORT EditEngine::ParagraphDeleted( sal_uInt16 nPara )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/
/*N*/     if ( GetNotifyHdl().IsSet() )
/*N*/     {
/*?*/         DBG_BF_ASSERT(0, "STRIP"); //STRIP001 EENotify aNotify( EE_NOTIFY_PARAGRAPHREMOVED );
//STRIP001 /*?*/         aNotify.pEditEngine = this;
//STRIP001 /*?*/         aNotify.nParagraph = nPara;
//STRIP001 /*?*/         pImpEditEngine->CallNotify( aNotify );
/*N*/     }
/*N*/ }

/*N*/ sal_Bool __EXPORT EditEngine::FormattingParagraph( sal_uInt16 )
/*N*/ {
/*N*/   // return sal_True, wenn die Attribute geaendert wurden...
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return sal_False;
/*N*/ }

/*N*/ void __EXPORT EditEngine::ParaAttribsChanged( sal_uInt16 /* nParagraph */ )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/ }

//STRIP001 void __EXPORT EditEngine::StyleSheetChanged( SfxStyleSheet* /* pStyle */ )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001 }

/*N*/ void __EXPORT EditEngine::ParagraphHeightChanged( sal_uInt16 nPara )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/
/*N*/     if ( GetNotifyHdl().IsSet() )
/*N*/     {
/*?*/         DBG_BF_ASSERT(0, "STRIP"); //STRIP001 EENotify aNotify( EE_NOTIFY_TEXTHEIGHTCHANGED );
//STRIP001 /*?*/         aNotify.pEditEngine = this;
//STRIP001 /*?*/         aNotify.nParagraph = nPara;
//STRIP001 /*?*/         pImpEditEngine->CallNotify( aNotify );
/*N*/     }
/*N*/ }

/*N*/ XubString __EXPORT EditEngine::GetUndoComment( sal_uInt16 nId ) const
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   XubString aComment;
/*N*/   switch ( nId )
/*N*/   {
/*N*/       case EDITUNDO_REMOVECHARS:
/*N*/       case EDITUNDO_CONNECTPARAS:
/*N*/       case EDITUNDO_REMOVEFEATURE:
/*N*/       case EDITUNDO_DELCONTENT:
/*N*/       case EDITUNDO_DELETE:
/*N*/       case EDITUNDO_CUT:
/*?*/           aComment = XubString( EditResId( RID_EDITUNDO_DEL ) );
/*N*/       break;
/*N*/       case EDITUNDO_MOVEPARAGRAPHS:
/*N*/       case EDITUNDO_MOVEPARAS:
/*N*/       case EDITUNDO_DRAGANDDROP:
/*?*/           aComment = XubString( EditResId( RID_EDITUNDO_MOVE ) );
/*N*/       break;
/*N*/       case EDITUNDO_INSERTFEATURE:
/*N*/       case EDITUNDO_SPLITPARA:
/*N*/       case EDITUNDO_INSERTCHARS:
/*N*/       case EDITUNDO_PASTE:
/*N*/       case EDITUNDO_INSERT:
/*N*/       case EDITUNDO_READ:
/*N*/           aComment = XubString( EditResId( RID_EDITUNDO_INSERT ) );
/*N*/       break;
/*N*/       case EDITUNDO_SRCHANDREPL:
/*N*/       case EDITUNDO_REPLACEALL:
/*?*/           aComment = XubString( EditResId( RID_EDITUNDO_REPLACE ) );
/*N*/       break;
/*N*/       case EDITUNDO_ATTRIBS:
/*N*/       case EDITUNDO_PARAATTRIBS:
/*N*/       case EDITUNDO_STRETCH:
/*?*/           aComment = XubString( EditResId( RID_EDITUNDO_SETATTRIBS ) );
/*N*/       break;
/*N*/       case EDITUNDO_RESETATTRIBS:
/*?*/           aComment = XubString( EditResId( RID_EDITUNDO_RESETATTRIBS ) );
/*N*/       break;
/*N*/       case EDITUNDO_STYLESHEET:
/*?*/           aComment = XubString( EditResId( RID_EDITUNDO_SETSTYLE ) );
/*N*/       break;
/*N*/       case EDITUNDO_TRANSLITERATE:
/*?*/           aComment = XubString( EditResId( RID_EDITUNDO_TRANSLITERATE ) );
/*N*/       break;
/*N*/       case EDITUNDO_INDENTBLOCK:
/*N*/       case EDITUNDO_UNINDENTBLOCK:
/*?*/           aComment = XubString( EditResId( RID_EDITUNDO_INDENT ) );
/*N*/       break;
/*N*/   }
/*N*/   return aComment;
/*N*/ }

/*N*/ Rectangle EditEngine::GetBulletArea( sal_uInt16 nPara )
/*N*/ {
/*N*/   return Rectangle( Point(), Point() );
/*N*/ }

/*N*/ XubString __EXPORT EditEngine::CalcFieldValue( const SvxFieldItem& rField, sal_uInt16, sal_uInt16, Color*&, Color*& )
/*N*/ {
/*N*/   DBG_CHKTHIS( EditEngine, 0 );
/*N*/   return ' ';
/*N*/ }

//STRIP001 void __EXPORT EditEngine::FieldClicked( const SvxFieldItem& rField, sal_uInt16, sal_uInt16 )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001 }

//STRIP001 void __EXPORT EditEngine::FieldSelected( const SvxFieldItem& rField, sal_uInt16, sal_uInt16 )
//STRIP001 {
//STRIP001  DBG_CHKTHIS( EditEngine, 0 );
//STRIP001 }

// =====================================================================
// ======================   Statische Methoden   =======================
// =====================================================================
/*N*/ SfxItemPool* EditEngine::CreatePool( sal_Bool bPersistentRefCounts )
/*N*/ {
/*N*/   SfxItemPool* pPool = new EditEngineItemPool( bPersistentRefCounts );
/*N*/   return pPool;
/*N*/ }

//STRIP001 sal_uInt32 EditEngine::RegisterClipboardFormatName()
//STRIP001 {
//STRIP001  static sal_uInt32 nFormat = 0;
//STRIP001  if ( !nFormat )
//STRIP001      nFormat = SotExchange::RegisterFormatName( String( RTL_CONSTASCII_USTRINGPARAM( "EditEngineFormat" ) ) );
//STRIP001  return nFormat;
//STRIP001 }

/*N*/ void EditEngine::SetGetAutoCorrectHdl( const Link& rHdl )
/*N*/ {
/*N*/   EE_DLL()->GetGlobalData()->SetGetAutoCorrectHdl( rHdl );
/*N*/ }

//STRIP001 sal_uInt16 EditEngine::GetAvailableSearchOptions()
//STRIP001 {
//STRIP001 #ifdef SVX_LIGHT
//STRIP001  return 0;
//STRIP001 #else
//STRIP001  return SEARCH_OPTIONS_SEARCH | SEARCH_OPTIONS_REPLACE |
//STRIP001          SEARCH_OPTIONS_REPLACE_ALL | SEARCH_OPTIONS_WHOLE_WORDS |
//STRIP001          SEARCH_OPTIONS_BACKWARDS | SEARCH_OPTIONS_REG_EXP |
//STRIP001          SEARCH_OPTIONS_EXACT | SEARCH_OPTIONS_SELECTION;
//STRIP001 #endif
//STRIP001 }

//STRIP001 void EditEngine::SetFontInfoInItemSet( SfxItemSet& rSet, const Font& rFont )
//STRIP001 {
//STRIP001  SvxFont aSvxFont( rFont );
//STRIP001  SetFontInfoInItemSet( rSet, aSvxFont );
//STRIP001
//STRIP001 }

//STRIP001 void EditEngine::SetFontInfoInItemSet( SfxItemSet& rSet, const SvxFont& rFont )
//STRIP001 {
//STRIP001  rSet.Put( SvxLanguageItem( rFont.GetLanguage(), EE_CHAR_LANGUAGE ) );
//STRIP001  rSet.Put( SvxFontItem( rFont.GetFamily(), rFont.GetName(), XubString(), rFont.GetPitch(), rFont.GetCharSet(), EE_CHAR_FONTINFO ) );
//STRIP001  rSet.Put( SvxFontHeightItem( rFont.GetSize().Height(), 100, EE_CHAR_FONTHEIGHT )  );
//STRIP001  rSet.Put( SvxCharScaleWidthItem( 100, EE_CHAR_FONTWIDTH ) );
//STRIP001  rSet.Put( SvxShadowedItem( rFont.IsShadow(), EE_CHAR_SHADOW )  );
//STRIP001  rSet.Put( SvxEscapementItem( rFont.GetEscapement(), rFont.GetPropr(), EE_CHAR_ESCAPEMENT )  );
//STRIP001  rSet.Put( SvxWeightItem( rFont.GetWeight(), EE_CHAR_WEIGHT )  );
//STRIP001  rSet.Put( SvxColorItem( rFont.GetColor(), EE_CHAR_COLOR )  );
//STRIP001  rSet.Put( SvxUnderlineItem( rFont.GetUnderline(), EE_CHAR_UNDERLINE )  );
//STRIP001  rSet.Put( SvxCrossedOutItem( rFont.GetStrikeout(), EE_CHAR_STRIKEOUT )  );
//STRIP001  rSet.Put( SvxPostureItem( rFont.GetItalic(), EE_CHAR_ITALIC )  );
//STRIP001  rSet.Put( SvxContourItem( rFont.IsOutline(), EE_CHAR_OUTLINE )  );
//STRIP001  rSet.Put( SvxAutoKernItem( rFont.IsKerning(), EE_CHAR_PAIRKERNING ) );
//STRIP001  rSet.Put( SvxKerningItem( rFont.GetFixKerning(), EE_CHAR_KERNING ) );
//STRIP001  rSet.Put( SvxWordLineModeItem( rFont.IsWordLineMode(), EE_CHAR_WLM ) );
//STRIP001  rSet.Put( SvxEmphasisMarkItem( rFont.GetEmphasisMark(), EE_CHAR_EMPHASISMARK ) );
//STRIP001  rSet.Put( SvxCharReliefItem( rFont.GetRelief(), EE_CHAR_RELIEF ) );
//STRIP001 }

/*N*/ Font EditEngine::CreateFontFromItemSet( const SfxItemSet& rItemSet, USHORT nScriptType )
/*N*/ {
/*N*/   SvxFont aFont;
/*N*/   CreateFont( aFont, rItemSet, nScriptType );
/*N*/   return aFont;
/*N*/ }

// Maybe we can remove the next two methods, check after 6.x
//STRIP001 Font EditEngine::CreateFontFromItemSet( const SfxItemSet& rItemSet )
//STRIP001 {
//STRIP001  return CreateSvxFontFromItemSet( rItemSet );
//STRIP001 }

/*N*/ SvxFont EditEngine::CreateSvxFontFromItemSet( const SfxItemSet& rItemSet )
/*N*/ {
/*N*/   SvxFont aFont;
/*N*/   CreateFont( aFont, rItemSet );
/*N*/   return aFont;
/*N*/ }

//STRIP001 sal_Bool EditEngine::DoesKeyMoveCursor( const KeyEvent& rKeyEvent )
//STRIP001 {
//STRIP001  sal_Bool bDoesMove = sal_False;
//STRIP001
//STRIP001  switch ( rKeyEvent.GetKeyCode().GetCode() )
//STRIP001  {
//STRIP001      case KEY_UP:
//STRIP001      case KEY_DOWN:
//STRIP001      case KEY_LEFT:
//STRIP001      case KEY_RIGHT:
//STRIP001      case KEY_HOME:
//STRIP001      case KEY_END:
//STRIP001      case KEY_PAGEUP:
//STRIP001      case KEY_PAGEDOWN:
//STRIP001      {
//STRIP001          if ( !rKeyEvent.GetKeyCode().IsMod2() )
//STRIP001              bDoesMove = sal_True;
//STRIP001      }
//STRIP001      break;
//STRIP001  }
//STRIP001  return bDoesMove;
//STRIP001 }

//STRIP001 sal_Bool EditEngine::DoesKeyChangeText( const KeyEvent& rKeyEvent )
//STRIP001 {
//STRIP001  sal_Bool bDoesChange = sal_False;
//STRIP001
//STRIP001  KeyFuncType eFunc = rKeyEvent.GetKeyCode().GetFunction();
//STRIP001  if ( eFunc != KEYFUNC_DONTKNOW )
//STRIP001  {
//STRIP001      switch ( eFunc )
//STRIP001      {
//STRIP001          case KEYFUNC_UNDO:
//STRIP001          case KEYFUNC_REDO:
//STRIP001          case KEYFUNC_CUT:
//STRIP001          case KEYFUNC_PASTE: bDoesChange = sal_True;
//STRIP001          break;
//STRIP001          default:    // wird dann evtl. unten bearbeitet.
//STRIP001                      eFunc = KEYFUNC_DONTKNOW;
//STRIP001      }
//STRIP001  }
//STRIP001  if ( eFunc == KEYFUNC_DONTKNOW )
//STRIP001  {
//STRIP001      switch ( rKeyEvent.GetKeyCode().GetCode() )
//STRIP001      {
//STRIP001          case KEY_DELETE:
//STRIP001          case KEY_BACKSPACE: bDoesChange = sal_True;
//STRIP001          break;
//STRIP001          case KEY_RETURN:
//STRIP001          case KEY_TAB:
//STRIP001          {
//STRIP001              if ( !rKeyEvent.GetKeyCode().IsMod1() && !rKeyEvent.GetKeyCode().IsMod2() )
//STRIP001                  bDoesChange = sal_True;
//STRIP001          }
//STRIP001          break;
//STRIP001          default:
//STRIP001          {
//STRIP001              bDoesChange = IsSimpleCharInput( rKeyEvent );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return bDoesChange;
//STRIP001 }

/*N*/ sal_Bool EditEngine::IsSimpleCharInput( const KeyEvent& rKeyEvent )
/*N*/ {
/*N*/   if( EditEngine::IsPrintable( rKeyEvent.GetCharCode() ) &&
/*N*/ #ifndef MAC
/*N*/       ( KEY_MOD2 != (rKeyEvent.GetKeyCode().GetModifier() & ~KEY_SHIFT ) ) &&
/*N*/       ( KEY_MOD1 != (rKeyEvent.GetKeyCode().GetModifier() & ~KEY_SHIFT ) ) )
/*N*/ #else
/*N*/       KEY_MOD1 != rKeyEvent.GetKeyCode().GetModifier() )
/*N*/ #endif
/*N*/   {
/*N*/       return sal_True;
/*N*/   }
/*N*/   return sal_False;
/*N*/ }

// Mal in den Outliner schieben...
/*N*/ void EditEngine::ImportBulletItem( SvxNumBulletItem& rNumBullet, sal_uInt16 nLevel,
/*N*/                                   const SvxBulletItem* pOldBullet, const SvxLRSpaceItem* pOldLRSpace )
/*N*/ {
/*N*/   if ( pOldBullet || pOldLRSpace )
/*N*/   {
/*N*/       // Numberformat dynamisch, weil Zuweisungsoperator nicht implementiert.
/*N*/
/*N*/       // Altes NumBulletItem nur uebernehmen, wenn kein altes BulletItem
/*N*/       const SvxNumberFormat* pFmt = ( !pOldBullet && ( rNumBullet.GetNumRule()->GetLevelCount() > nLevel ) ) ?
/*N*/                                       rNumBullet.GetNumRule()->Get( nLevel ) : NULL;
/*N*/       SvxNumberFormat* pNumberFormat = pFmt
/*N*/                                           ? new SvxNumberFormat( *pFmt )
/*N*/                                           : new SvxNumberFormat( SVX_NUM_NUMBER_NONE );
/*N*/       if ( pOldBullet )
/*N*/       {
/*N*/           // Style
/*N*/           SvxExtNumType eNumType;
/*N*/           switch( pOldBullet->GetStyle() )
/*N*/           {
/*N*/               case BS_BMP:            eNumType = SVX_NUM_BITMAP;              break;
/*N*/               case BS_BULLET:         eNumType = SVX_NUM_CHAR_SPECIAL;        break;
/*N*/               case BS_ROMAN_BIG:      eNumType = SVX_NUM_ROMAN_UPPER;         break;
/*N*/               case BS_ROMAN_SMALL:    eNumType = SVX_NUM_ROMAN_LOWER;         break;
/*N*/               case BS_ABC_BIG:        eNumType = SVX_NUM_CHARS_UPPER_LETTER;  break;
/*N*/               case BS_ABC_SMALL:      eNumType = SVX_NUM_CHARS_LOWER_LETTER;  break;
/*N*/               case BS_123:            eNumType = SVX_NUM_ARABIC;              break;
/*N*/               default:                eNumType = SVX_NUM_NUMBER_NONE;         break;
/*N*/           }
/*N*/ #if SUPD > 622
/*N*/           pNumberFormat->SetNumberingType( eNumType );
/*N*/ #else
/*N*/           pNumberFormat->SetNumType( eNumType );
/*N*/ #endif
/*N*/
/*N*/           // Justification
/*N*/           SvxAdjust eAdjust;
/*N*/           switch( pOldBullet->GetJustification() & (BJ_HRIGHT|BJ_HCENTER|BJ_HLEFT) )
/*N*/           {
/*?*/               case BJ_HRIGHT:     eAdjust = SVX_ADJUST_RIGHT;     break;
/*?*/               case BJ_HCENTER:    eAdjust = SVX_ADJUST_CENTER;    break;
/*N*/               default:            eAdjust = SVX_ADJUST_LEFT;      break;
/*N*/           }
/*N*/           pNumberFormat->SetNumAdjust(eAdjust);
/*N*/
/*N*/           // Prefix/Suffix
/*N*/           pNumberFormat->SetPrefix( pOldBullet->GetPrevText() );
/*N*/           pNumberFormat->SetSuffix( pOldBullet->GetFollowText() );
/*N*/
/*N*/           //Font
/*N*/           if ( eNumType != SVX_NUM_BITMAP )
/*N*/           {
/*N*/               Font aTmpFont = pOldBullet->GetFont();
/*N*/               pNumberFormat->SetBulletFont( &aTmpFont );
/*N*/           }
/*N*/
/*N*/           // Color
/*N*/           pNumberFormat->SetBulletColor( pOldBullet->GetFont().GetColor() );
/*N*/
/*N*/           // Start
/*N*/           pNumberFormat->SetStart( pOldBullet->GetStart() );
/*N*/
/*N*/           // Scale
/*N*/           pNumberFormat->SetBulletRelSize( pOldBullet->GetScale() );
/*N*/
/*N*/           // Bullet/Bitmap
/*N*/           if( eNumType == SVX_NUM_CHAR_SPECIAL )
/*N*/           {
/*N*/               pNumberFormat->SetBulletChar( pOldBullet->GetSymbol() );
/*N*/           }
/*N*/           else if( eNumType == SVX_NUM_BITMAP )
/*N*/           {
/*?*/               DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SvxBrushItem aBItem( Graphic( pOldBullet->GetBitmap() ), GPOS_NONE );
//STRIP001 /*?*/                pNumberFormat->SetGraphicBrush( &aBItem );
/*N*/           }
/*N*/       }
/*N*/
/*N*/       // Einzug und Erstzeileneinzug
/*N*/       if ( pOldLRSpace )
/*N*/       {
/*N*/           short nLSpace = (short)pOldLRSpace->GetTxtLeft();
/*N*/           pNumberFormat->SetLSpace( nLSpace );
/*N*/           pNumberFormat->SetAbsLSpace( nLSpace );
/*N*/           pNumberFormat->SetFirstLineOffset( pOldLRSpace->GetTxtFirstLineOfst() );
/*N*/       }
/*N*/
/*N*/       rNumBullet.GetNumRule()->SetLevel( nLevel, *pNumberFormat );
/*N*/       delete pNumberFormat;
/*N*/   }
/*N*/ }

//STRIP001 BOOL EditEngine::HasValidData( ::com::sun::star::uno::Reference< ::com::sun::star::datatransfer::XTransferable >& rTransferable )
//STRIP001 {
//STRIP001     BOOL bValidData = FALSE;
//STRIP001
//STRIP001  if ( rTransferable.is() )
//STRIP001  {
//STRIP001         // Every application that copies rtf or any other text format also copies plain text into the clipboard....
//STRIP001      datatransfer::DataFlavor aFlavor;
//STRIP001      SotExchange::GetFormatDataFlavor( SOT_FORMAT_STRING, aFlavor );
//STRIP001      bValidData = rTransferable->isDataFlavorSupported( aFlavor );
//STRIP001  }
//STRIP001
//STRIP001     return bValidData;
//STRIP001 }


// ---------------------------------------------------


/*N*/ EFieldInfo::EFieldInfo()
/*N*/ {
/*N*/     pFieldItem = NULL;
/*N*/ }


/*N*/ EFieldInfo::EFieldInfo( const SvxFieldItem& rFieldItem, USHORT nPara, USHORT nPos ) : aPosition( nPara, nPos )
/*N*/ {
/*N*/     pFieldItem = new SvxFieldItem( rFieldItem );
/*N*/ }

/*N*/ EFieldInfo::~EFieldInfo()
/*N*/ {
/*N*/     delete pFieldItem;
/*N*/ }

/*N*/ EFieldInfo::EFieldInfo( const EFieldInfo& rFldInfo )
/*N*/ {
/*N*/     *this = rFldInfo;
/*N*/ }

//STRIP001 EFieldInfo& EFieldInfo::operator= ( const EFieldInfo& rFldInfo )
//STRIP001 {
//STRIP001     if( this == &rFldInfo )
//STRIP001         return *this;
//STRIP001
//STRIP001     pFieldItem = rFldInfo.pFieldItem ? new SvxFieldItem( *rFldInfo.pFieldItem ) : 0;
//STRIP001     aCurrentText = rFldInfo.aCurrentText;
//STRIP001     aPosition = rFldInfo.aPosition;
//STRIP001
//STRIP001     return *this;
//STRIP001 }
}
