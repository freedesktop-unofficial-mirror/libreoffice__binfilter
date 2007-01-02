/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_viscrs.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 17:44:11 $
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


#pragma hdrstop

#ifndef _SVSTDARR_HXX
#define _SVSTDARR_USHORTS
#endif


#ifndef _VIEWOPT_HXX //autogen
#include <viewopt.hxx>
#endif
#ifndef _FRMTOOL_HXX
#include <frmtool.hxx>
#endif
#ifndef _VISCRS_HXX
#include <viscrs.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _CRSRSH_HXX
#include <crsrsh.hxx>
#endif
#ifndef _DVIEW_HXX
#include <dview.hxx>
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>   // SwTxtFrm
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _DRAWFONT_HXX
#include <drawfont.hxx>
#endif

#ifndef _COMCORE_HRC
#include <comcore.hrc>          // ResId fuer Abfrage wenn zu Search & Replaces
#endif
namespace binfilter {


// OD 24.01.2003 #106593# - no longer needed, included in <frmtool.hxx>
//extern void MA_FASTCALL SwAlignRect( SwRect &rRect, ViewShell *pSh );
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

// --------  Ab hier Klassen / Methoden fuer den nicht Text-Cursor ------

/*N*/ SwVisCrsr::SwVisCrsr( const SwCrsrShell * pCShell )
/*N*/   : pCrsrShell( pCShell )
/*N*/ {
/*N*/   pCShell->GetWin()->SetCursor( &aTxtCrsr );
/*N*/   bIsVisible = aTxtCrsr.IsVisible();
/*N*/   bIsDragCrsr = FALSE;
/*N*/   aTxtCrsr.SetWidth( 0 );
/*N*/
/*N*/ #ifdef SW_CRSR_TIMER
/*N*/   bTimerOn = TRUE;
/*N*/   SetTimeout( 50 );       // 50msec Verzoegerung
/*N*/ #endif
/*N*/ }



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




/*N*/ void SwVisCrsr::Show()
/*N*/ {
/*N*/   if( !bIsVisible )
/*N*/   {
/*N*/       bIsVisible = TRUE;
/*N*/
/*N*/       // muss ueberhaupt angezeigt werden ?
/*N*/       if( pCrsrShell->VisArea().IsOver( pCrsrShell->aCharRect ) )
/*N*/ #ifdef SW_CRSR_TIMER
/*N*/       {
/*N*/           if( bTimerOn )
/*N*/               Start();            // Timer aufsetzen
/*N*/           else
/*N*/           {
/*N*/               if( IsActive() )
/*N*/                   Stop();         // Timer Stoppen
/*N*/
/*N*/               _SetPosAndShow();
/*N*/           }
/*N*/       }
/*N*/ #else
/*N*/           _SetPosAndShow();
/*N*/ #endif
/*N*/   }
/*N*/ }



/*N*/ void SwVisCrsr::Hide()
/*N*/ {
/*N*/   if( bIsVisible )
/*N*/   {
/*N*/       bIsVisible = FALSE;
/*N*/
/*N*/ #ifdef SW_CRSR_TIMER
/*N*/       if( IsActive() )
/*N*/           Stop();         // Timer Stoppen
/*N*/ #endif
/*N*/
/*N*/       if( aTxtCrsr.IsVisible() )      // sollten die Flags nicht gueltig sein?
/*?*/           aTxtCrsr.Hide();
/*N*/   }
/*N*/ }

#ifdef SW_CRSR_TIMER




#endif


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
/*N*/     {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
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


/*  */
// ------ Ab hier Klassen / Methoden fuer die Selectionen -------

/*N*/ SwSelPaintRects::SwSelPaintRects( const SwCrsrShell& rCSh )
/*N*/       : SwRects( 0 ), pCShell( &rCSh )
/*N*/ {
/*N*/ }

/*N*/ SwSelPaintRects::~SwSelPaintRects()
/*N*/ {
/*N*/   Hide();
/*N*/ }

/*N*/ void SwSelPaintRects::Hide()
/*N*/ {
/*N*/   for( USHORT n = 0; n < Count(); ++n )
/*?*/   {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001     Paint( (*this)[n] );
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
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001   SwRegionRects aReg( pCShell->VisArea() );
/*N*/   }
/*N*/ }

// check current MapMode of the shell and set possibly the static members.
// Optional set the parameters pX, pY
/*N*/ void SwSelPaintRects::Get1PixelInLogic( const ViewShell& rSh,
/*N*/                                       long* pX, long* pY )
/*N*/ {
/*N*/   const OutputDevice* pOut = rSh.GetWin();
/*N*/   if ( ! pOut )
/*N*/       pOut = rSh.GetOut();
/*N*/
/*N*/   const MapMode& rMM = pOut->GetMapMode();
/*N*/   if( pMapMode->GetMapUnit() != rMM.GetMapUnit() ||
/*N*/       pMapMode->GetScaleX() != rMM.GetScaleX() ||
/*N*/       pMapMode->GetScaleY() != rMM.GetScaleY() )
/*N*/   {
/*N*/       *pMapMode = rMM;
/*N*/       Size aTmp( 1, 1 );
/*N*/       aTmp = pOut->PixelToLogic( aTmp );
/*N*/       nPixPtX = aTmp.Width();
/*N*/       nPixPtY = aTmp.Height();
/*N*/   }
/*N*/   if( pX )
/*N*/       *pX = nPixPtX;
/*N*/   if( pY )
/*N*/       *pY = nPixPtY;
/*N*/ }


/*  */

/*N*/ SwShellCrsr::SwShellCrsr( const SwCrsrShell& rCShell, const SwPosition &rPos )
/*N*/   : SwCursor( rPos ), SwSelPaintRects( rCShell ),
/*N*/   pPt( SwPaM::GetPoint() )
/*N*/ {}





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
/*?*/   {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001     GetDoc()->GetRootFrm()->CalcFrmRects( *this, GetShell()->IsTableMode() );
/*N*/ }


/*N*/ void SwShellCrsr::Show()
/*N*/ {
/*N*/   SwShellCrsr * pTmp = this;
/*N*/   do {
/*N*/       pTmp->SwSelPaintRects::Show();
/*N*/   } while( this != ( pTmp = (SwShellCrsr*)*(SwCursor*)(pTmp->GetNext() )));
/*N*/
/*N*/   SHOWBOOKMARKS1( 1 )
/*N*/   SHOWREDLINES1( 1 )
/*N*/ }


    // Dieses Rechteck wird neu gepaintet, also ist die SSelection in
    // dem Bereich ungueltig








#ifndef PRODUCT

// JP 05.03.98: zum Testen des UNO-Crsr Verhaltens hier die Implementierung
//              am sichtbaren Cursor


#endif

// TRUE: an die Position kann der Cursor gesetzt werden

/*  */

/*N*/ SwShellTableCrsr::SwShellTableCrsr( const SwCrsrShell& rCrsrSh,
/*N*/                                   const SwPosition& rPos )
/*N*/   : SwTableCursor( rPos ), SwShellCrsr( rCrsrSh, rPos ),
/*N*/       SwCursor( rPos )
/*N*/ {
/*N*/ }

/*N*/ SwShellTableCrsr::~SwShellTableCrsr() {}

/*N*/ void SwShellTableCrsr::SetMark()              { SwShellCrsr::SetMark(); }
/*N*/ SwShellTableCrsr::operator SwShellCrsr* ()        { return this; }
/*N*/ SwShellTableCrsr::operator SwTableCursor* ()  { return this; }
/*N*/ SwShellTableCrsr::operator SwShellTableCrsr* ()   { return this; }





// Pruefe, ob sich der SPoint innerhalb der Tabellen-SSelection befindet

#ifndef PRODUCT

// JP 05.03.98: zum Testen des UNO-Crsr Verhaltens hier die Implementierung
//              am sichtbaren Cursor

#endif


}
