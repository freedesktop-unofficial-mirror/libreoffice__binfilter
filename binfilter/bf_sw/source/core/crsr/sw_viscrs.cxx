/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/


#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef _SVSTDARR_HXX
#define _SVSTDARR_USHORTS
#endif


#include <viewopt.hxx>
#include <frmtool.hxx>
#include <viscrs.hxx>

#include <horiornt.hxx>

#include <crsrsh.hxx>
#include <dview.hxx>
#include <txtfrm.hxx>   // SwTxtFrm
#include <ndtxt.hxx>
#include <drawfont.hxx>

#include <comcore.hrc>          // ResId fuer Abfrage wenn zu Search & Replaces
namespace binfilter {

extern void SwCalcPixStatics( OutputDevice *pOut );


//Damit beim ShowCrsr nicht immer wieder die gleiche Size teuer ermittelt
//werden muss, hier statische Member, die beim Wechsel des MapModes
// angepasst werden

long SwSelPaintRects::nPixPtX = 0;
long SwSelPaintRects::nPixPtY = 0;
MapMode* SwSelPaintRects::pMapMode = 0;



//#define SHOW_BOOKMARKS
//#define SHOW_REDLINES

#ifdef SHOW_BOOKMARKS






#define SHOWBOOKMARKS1( nAct )          ShowBookmarks( GetShell(),nAct );

#else

#define SHOWBOOKMARKS1( nAct )
#endif
#ifdef SHOW_REDLINES






#define SHOWREDLINES1( nAct )           ShowRedlines( GetShell(),nAct );
#else
#define SHOWREDLINES1( nAct )
#endif

/*N*/ SwVisCrsr::~SwVisCrsr()
/*N*/ {
/*N*/ #ifdef SW_CRSR_TIMER
/*N*/   if( bTimerOn )
/*N*/       Stop();     // Timer stoppen
/*N*/ #endif
/*N*/
/*N*/   if( bIsVisible && aTxtCrsr.IsVisible() )
/*?*/       aTxtCrsr.Hide();
/*N*/
/*N*/   pCrsrShell->GetWin()->SetCursor( 0 );
/*N*/ }

/*N*/ void SwVisCrsr::_SetPosAndShow()
/*N*/ {
/*N*/   SwRect aRect;
/*N*/     long nTmpY = pCrsrShell->aCrsrHeight.Y();
/*N*/     if( 0 > nTmpY )
/*N*/   {
/*?*/         nTmpY = -nTmpY;
/*?*/         aTxtCrsr.SetOrientation( 900 );
/*?*/       aRect = SwRect( pCrsrShell->aCharRect.Pos(),
/*?*/            Size( pCrsrShell->aCharRect.Height(), nTmpY ) );
/*?*/       aRect.Pos().X() += pCrsrShell->aCrsrHeight.X();
/*?*/         if( pCrsrShell->IsOverwriteCrsr() )
/*?*/             aRect.Pos().Y() += aRect.Width();
/*N*/   }
/*N*/   else
/*N*/     {
/*N*/         aTxtCrsr.SetOrientation( 0 );
/*N*/       aRect = SwRect( pCrsrShell->aCharRect.Pos(),
/*N*/            Size( pCrsrShell->aCharRect.Width(), nTmpY ) );
/*N*/       aRect.Pos().Y() += pCrsrShell->aCrsrHeight.X();
/*N*/     }
/*N*/
/*N*/     // check if cursor should show the current cursor bidi level
/*N*/     aTxtCrsr.SetDirection( CURSOR_DIRECTION_NONE );
/*N*/     const SwCursor* pTmpCrsr = pCrsrShell->_GetCrsr();
/*N*/
/*N*/     if ( pTmpCrsr && !pCrsrShell->IsOverwriteCrsr() )
/*N*/     {
/*N*/         SwNode& rNode = pTmpCrsr->GetPoint()->nNode.GetNode();
/*N*/         if( rNode.IsTxtNode() )
/*N*/         {
/*N*/             const SwTxtNode& rTNd = *rNode.GetTxtNode();
/*N*/             Point aPt( aRect.Pos() );
/*N*/             SwFrm* pFrm = rTNd.GetFrm( &aPt );
/*N*/             if ( pFrm )
/*N*/             {
/*N*/                 const SwScriptInfo* pSI = ((SwTxtFrm*)pFrm)->GetScriptInfo();
/*N*/                  // cursor level has to be shown
/*N*/                 if ( pSI && pSI->CountDirChg() > 1 )
/*N*/                 {
/*N*/                     aTxtCrsr.SetDirection(
/*N*/                         ( pTmpCrsr->GetCrsrBidiLevel() % 2 ) ?
/*N*/                           CURSOR_DIRECTION_RTL :
/*N*/                           CURSOR_DIRECTION_LTR );
/*N*/                 }
/*N*/
/*N*/                 if ( pFrm->IsRightToLeft() )
/*N*/                 {
/*N*/                     const OutputDevice *pOut = pCrsrShell->GetOut();
/*N*/                     if ( pOut )
/*N*/                     {
/*N*/                         USHORT nSize = pOut->GetSettings().GetStyleSettings().GetCursorSize();
/*N*/                         Size aSize( nSize, nSize );
/*N*/                         aSize = pOut->PixelToLogic( aSize );
/*N*/                         aRect.Left( aRect.Left() - aSize.Width() );
/*N*/                     }
/*N*/                 }
/*N*/             }
/*N*/         }
/*N*/     }
/*N*/
/*N*/     if( aRect.Height() )
/*N*/     {DBG_BF_ASSERT(0, "STRIP");
/*N*/     }
/*N*/     if( !pCrsrShell->IsOverwriteCrsr() || bIsDragCrsr ||
/*N*/         pCrsrShell->IsSelection() )
/*N*/         aRect.Width( 0 );
/*N*/
/*N*/   aTxtCrsr.SetSize( aRect.SSize() );
/*N*/
/*N*/   aTxtCrsr.SetPos( aRect.Pos() );
/*N*/     if ( !pCrsrShell->IsCrsrReadonly()  || pCrsrShell->GetViewOptions()->IsSelectionInReadonly() )
/*N*/   {
/*N*/       if ( pCrsrShell->GetDrawView() )
/*N*/           ((SwDrawView*)pCrsrShell->GetDrawView())->SetAnimationEnabled(
/*N*/                   !pCrsrShell->IsSelection() );
/*N*/
/*N*/       USHORT nStyle = bIsDragCrsr ? CURSOR_SHADOW : 0;
/*N*/       if( nStyle != aTxtCrsr.GetStyle() )
/*N*/       {
/*?*/           aTxtCrsr.SetStyle( nStyle );
/*?*/           aTxtCrsr.SetWindow( bIsDragCrsr ? pCrsrShell->GetWin() : 0 );
/*N*/       }
/*N*/
/*N*/       aTxtCrsr.Show();
/*N*/   }
/*N*/ }


// ------ Ab hier Klassen / Methoden fuer die Selectionen -------

/*N*/ SwSelPaintRects::~SwSelPaintRects()
/*N*/ {
/*N*/   Hide();
/*N*/ }

/*N*/ void SwSelPaintRects::Hide()
/*N*/ {
/*N*/   for( USHORT n = 0; n < Count(); ++n )
/*?*/   {DBG_BF_ASSERT(0, "STRIP"); }
/*N*/   SwRects::Remove( 0, Count() );
/*N*/ }

/*N*/ void SwSelPaintRects::Show()
/*N*/ {
/*N*/   if( pCShell->GetDrawView() )
/*N*/   {
/*N*/       SdrView* pView = (SdrView*)pCShell->GetDrawView();
/*N*/       pView->SetAnimationEnabled( !pCShell->IsSelection() );
/*N*/   }
/*N*/
/*N*/   SwRects aTmp;
/*N*/   aTmp.Insert( this, 0 );     // Kopie vom Array
/*N*/
/*N*/   SwRects::Remove( 0, SwRects::Count() );
/*N*/   FillRects();
/*N*/
/*N*/   if( Count() || aTmp.Count() )
/*N*/   {
/*?*/   DBG_BF_ASSERT(0, "STRIP");
/*N*/   }
/*N*/ }


/*N*/ SwShellCrsr::~SwShellCrsr() {}

/*N*/ SwShellCrsr::operator SwShellCrsr* () { return this; }


/*N*/ void SwShellCrsr::FillRects()
/*N*/ {
/*N*/   // die neuen Rechtecke berechnen
/*N*/   if( HasMark() &&
/*N*/       GetPoint()->nNode.GetNode().IsCntntNode() &&
/*N*/       GetPoint()->nNode.GetNode().GetCntntNode()->GetFrm() &&
/*N*/       (GetMark()->nNode == GetPoint()->nNode ||
/*N*/       (GetMark()->nNode.GetNode().IsCntntNode() &&
/*N*/        GetMark()->nNode.GetNode().GetCntntNode()->GetFrm() )  ))
/*?*/   {DBG_BF_ASSERT(0, "STRIP"); }
/*N*/ }

// TRUE: an die Position kann der Cursor gesetzt werden

/*N*/ SwShellTableCrsr::~SwShellTableCrsr() {}

/*N*/ void SwShellTableCrsr::SetMark()              { SwShellCrsr::SetMark(); }
/*N*/ SwShellTableCrsr::operator SwShellCrsr* ()        { return this; }
/*N*/ SwShellTableCrsr::operator SwTableCursor* ()  { return this; }
/*N*/ SwShellTableCrsr::operator SwShellTableCrsr* ()   { return this; }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
