/*************************************************************************
 *
 *  $RCSfile: sw_viscrs.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:08:50 $
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


#pragma hdrstop

#ifndef _SVSTDARR_HXX
#define _SVSTDARR_USHORTS
#include <svtools/svstdarr.hxx>
#endif

#ifndef _DIALOG_HXX //autogen
#include <vcl/dialog.hxx>
#endif
#ifndef _MSGBOX_HXX //autogen
#include <vcl/msgbox.hxx>
#endif
#ifndef _WRKWIN_HXX //autogen
#include <vcl/wrkwin.hxx>
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
#ifndef _CRSRSH_HXX
#include <crsrsh.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _NODE_HXX
#include <node.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _VIEWIMP_HXX
#include <viewimp.hxx>
#endif
#ifndef _DVIEW_HXX
#include <dview.hxx>
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>   // SwTxtFrm
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _EXTINPUT_HXX
#include <extinput.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _DRAWFONT_HXX
#include <drawfont.hxx>
#endif

#ifndef _MDIEXP_HXX
#include <mdiexp.hxx>           // GetSearchDialog
#endif
#ifndef _COMCORE_HRC
#include <comcore.hrc>          // ResId fuer Abfrage wenn zu Search & Replaces
#endif


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
//STRIP001
//STRIP001 #ifndef _BOOKMRK_HXX
//STRIP001 #include <bookmrk.hxx>
//STRIP001 #endif

//STRIP001 class SwBookmarkRects : public SwSelPaintRects
//STRIP001 {
//STRIP001  virtual void Paint( const Rectangle& rRect );
//STRIP001  virtual void FillRects();
//STRIP001
//STRIP001 public:
//STRIP001  SwBookmarkRects( const SwCrsrShell& rSh ) : SwSelPaintRects( rSh ) {}
//STRIP001 };

//STRIP001 void SwBookmarkRects::Paint( const Rectangle& rRect )
//STRIP001 {
//STRIP001  Window* pWin = GetShell()->GetWin();
//STRIP001
//STRIP001  RasterOp eOld( pWin->GetRasterOp() );
//STRIP001  BOOL bLCol = pWin->IsLineColor();
//STRIP001  Color aLCol( pWin->GetLineColor() );
//STRIP001  BOOL bFCol = pWin->IsFillColor();
//STRIP001  Color aFCol( pWin->GetFillColor() );
//STRIP001
//STRIP001  pWin->SetRasterOp( ROP_XOR );
//STRIP001  Color aCol( RGB_COLORDATA( 0xF0, 0xC8, 0xF0 ) ^ COL_WHITE );
//STRIP001  pWin->SetFillColor( aCol );
//STRIP001  pWin->SetLineColor( aCol );
//STRIP001
//STRIP001  pWin->DrawRect( rRect );
//STRIP001
//STRIP001  if( bLCol ) pWin->SetLineColor( aLCol ); else pWin->SetLineColor();
//STRIP001  if( bFCol ) pWin->SetFillColor( aFCol ); else pWin->SetFillColor();
//STRIP001  pWin->SetRasterOp( eOld );
//STRIP001 }

//STRIP001 void SwBookmarkRects::FillRects()
//STRIP001 {
//STRIP001  SwRegionRects aReg( GetShell()->VisArea() );
//STRIP001
//STRIP001  const SwBookmarks& rBkmkTbl = GetShell()->GetDoc()->GetBookmarks();
//STRIP001  SwShellCrsr* pCrsr = 0;
//STRIP001  for( USHORT n = 0; n < rBkmkTbl.Count(); ++n )
//STRIP001  {
//STRIP001      const SwBookmark& rBkmk = *rBkmkTbl[ n ];
//STRIP001      if( rBkmk.IsBookMark() && rBkmk.GetOtherPos() )
//STRIP001      {
//STRIP001          if( !pCrsr )
//STRIP001          {
//STRIP001              pCrsr = new SwShellCrsr( *GetShell(), rBkmk.GetPos() );
//STRIP001              pCrsr->SetMark();
//STRIP001          }
//STRIP001          else
//STRIP001              *pCrsr->GetPoint() = rBkmk.GetPos();
//STRIP001          *pCrsr->GetMark() = *rBkmk.GetOtherPos();
//STRIP001          pCrsr->FillRects();
//STRIP001          for( USHORT i = 0; i < pCrsr->Count(); ++i )
//STRIP001              aReg -= (*pCrsr)[ i ];
//STRIP001
//STRIP001          pCrsr->Remove( 0, i );
//STRIP001      }
//STRIP001  }
//STRIP001  if( pCrsr ) delete pCrsr;
//STRIP001
//STRIP001  aReg.Invert();
//STRIP001  SwRects::Insert( &aReg, 0 );
//STRIP001 }

//STRIP001 SwBookmarkRects* pBookMarkRects = 0;

//STRIP001 void ShowBookmarks( const SwCrsrShell* pSh, int nAction, const SwRect* pRect = 0 )
//STRIP001 {
//STRIP001  if( !pBookMarkRects && pSh->GetDoc()->GetBookmarks().Count() )
//STRIP001      pBookMarkRects = new SwBookmarkRects( *pSh );
//STRIP001
//STRIP001  if( pBookMarkRects )
//STRIP001  {
//STRIP001      switch( nAction )
//STRIP001      {
//STRIP001      case 1: pBookMarkRects->Show(); break;
//STRIP001      case 2: pBookMarkRects->Hide(); break;
//STRIP001      case 3: pBookMarkRects->Invalidate( *pRect ); break;
//STRIP001      }
//STRIP001
//STRIP001      if( !pBookMarkRects->Count() )
//STRIP001          delete pBookMarkRects, pBookMarkRects = 0;
//STRIP001  }
//STRIP001 }

#define SHOWBOOKMARKS1( nAct )          ShowBookmarks( GetShell(),nAct );
//STRIP001 #define SHOWBOOKMARKS2( nAct, pRect )    ShowBookmarks( GetShell(),nAct, pRect );

#else

#define SHOWBOOKMARKS1( nAct )
//STRIP001 #define SHOWBOOKMARKS2( nAct, pRect )
//STRIP001
#endif
//STRIP001
#ifdef SHOW_REDLINES
//STRIP001
#ifndef _REDLINE_HXX
#include <redline.hxx>
#endif

//STRIP001 class SwRedlineRects : public SwSelPaintRects
//STRIP001 {
//STRIP001  USHORT nMode;
//STRIP001  USHORT nNm;
//STRIP001
//STRIP001  virtual void Paint( const Rectangle& rRect );
//STRIP001  virtual void FillRects();
//STRIP001
//STRIP001 public:
//STRIP001  SwRedlineRects( const SwCrsrShell& rSh, USHORT nName, USHORT n )
//STRIP001      : SwSelPaintRects( rSh ), nMode( n ), nNm( nName )
//STRIP001  {}
//STRIP001 };

//STRIP001 void SwRedlineRects::Paint( const Rectangle& rRect )
//STRIP001 {
//STRIP001  Window* pWin = GetShell()->GetWin();
//STRIP001
//STRIP001  RasterOp eOld( pWin->GetRasterOp() );
//STRIP001  BOOL bLCol = pWin->IsLineColor();
//STRIP001  Color aLCol( pWin->GetLineColor() );
//STRIP001  BOOL bFCol = pWin->IsFillColor();
//STRIP001  Color aFCol( pWin->GetFillColor() );
//STRIP001
//STRIP001  pWin->SetRasterOp( ROP_XOR );
//STRIP001  Color aCol;
//STRIP001
//STRIP001  UINT8 nVal = 0xc8 - ( (nMode / 4) * 16 );
//STRIP001  switch( nMode % 4 )
//STRIP001  {
//STRIP001  case 0: aCol = RGB_COLORDATA( nVal, nVal, 0xFF );   break;
//STRIP001  case 1: aCol = RGB_COLORDATA( 0xFF, 0xc8, nVal );   break;
//STRIP001  case 2: aCol = RGB_COLORDATA( nVal, 0xFF, nVal );   break;
//STRIP001  case 3: aCol = RGB_COLORDATA( 0xFF, nVal, nVal );   break;
//STRIP001  }
//STRIP001  aCol = aCol.GetColor() ^ COL_WHITE;
//STRIP001
//STRIP001  pWin->SetFillColor( aCol );
//STRIP001  pWin->SetLineColor( aCol );
//STRIP001
//STRIP001  pWin->DrawRect( rRect );
//STRIP001
//STRIP001  if( bLCol ) pWin->SetLineColor( aLCol ); else pWin->SetLineColor();
//STRIP001  if( bFCol ) pWin->SetFillColor( aFCol ); else pWin->SetFillColor();
//STRIP001  pWin->SetRasterOp( eOld );
//STRIP001 }

//STRIP001 void SwRedlineRects::FillRects()
//STRIP001 {
//STRIP001  SwRegionRects aReg( GetShell()->VisArea() );
//STRIP001
//STRIP001  const SwRedlineTbl& rTbl = GetShell()->GetDoc()->GetRedlineTbl();
//STRIP001  SwShellCrsr* pCrsr = 0;
//STRIP001  for( USHORT n = 0; n < rTbl.Count(); ++n )
//STRIP001  {
//STRIP001      const SwRedline& rRed = *rTbl[ n ];
//STRIP001      if( rRed.HasMark() && (nMode % 4 ) == rRed.GetType() &&
//STRIP001          nNm == rRed.GetAuthor() )
//STRIP001      {
//STRIP001          if( !pCrsr )
//STRIP001          {
//STRIP001              pCrsr = new SwShellCrsr( *GetShell(), *rRed.GetPoint() );
//STRIP001              pCrsr->SetMark();
//STRIP001          }
//STRIP001          else
//STRIP001              *pCrsr->GetPoint() = *rRed.GetPoint();
//STRIP001          *pCrsr->GetMark() = *rRed.GetMark();
//STRIP001          pCrsr->FillRects();
//STRIP001          for( USHORT i = 0; i < pCrsr->Count(); ++i )
//STRIP001              aReg -= (*pCrsr)[ i ];
//STRIP001
//STRIP001          pCrsr->Remove( 0, i );
//STRIP001      }
//STRIP001  }
//STRIP001  if( pCrsr ) delete pCrsr;
//STRIP001
//STRIP001  aReg.Invert();
//STRIP001  SwRects::Insert( &aReg, 0 );
//STRIP001 }

//STRIP001 SwRedlineRects* aRedlines[ 10 * 4 ];
//STRIP001 static int bFirstCall = TRUE;

//STRIP001 void ShowRedlines( const SwCrsrShell* pSh, int nAction, const SwRect* pRect = 0 )
//STRIP001 {
//STRIP001  if( bFirstCall )
//STRIP001  {
//STRIP001      memset( aRedlines, 0, sizeof(aRedlines));
//STRIP001      bFirstCall = FALSE;
//STRIP001  }
//STRIP001
//STRIP001  const SwRedlineTbl& rTbl = pSh->GetDoc()->GetRedlineTbl();
//STRIP001  const SwRedlineAuthorTbl& rAuthorTbl = pSh->GetDoc()->GetRedlineAuthorTbl();
//STRIP001
//STRIP001  for( USHORT n = 0; n < rAuthorTbl.Count(); ++n )
//STRIP001  {
//STRIP001      for( int i = 0; i < 4; ++i  )
//STRIP001      {
//STRIP001          SwRedlineRects** ppRedRect = &aRedlines[ n * 4 + i ];
//STRIP001          if( rTbl.Count() && !*ppRedRect )
//STRIP001              *ppRedRect = new SwRedlineRects( *pSh, n, n * 4 + i );
//STRIP001
//STRIP001          if( *ppRedRect )
//STRIP001          {
//STRIP001              switch( nAction )
//STRIP001              {
//STRIP001              case 1: (*ppRedRect)->Show(); break;
//STRIP001              case 2: (*ppRedRect)->Hide(); break;
//STRIP001              case 3: (*ppRedRect)->Invalidate( *pRect ); break;
//STRIP001              }
//STRIP001
//STRIP001              if( !(*ppRedRect)->Count() )
//STRIP001                  delete *ppRedRect, *ppRedRect = 0;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

#define SHOWREDLINES1( nAct )           ShowRedlines( GetShell(),nAct );
//STRIP001 #define SHOWREDLINES2( nAct, pRect ) ShowRedlines( GetShell(),nAct, pRect );
//STRIP001
#else
//STRIP001
#define SHOWREDLINES1( nAct )
//STRIP001 #define SHOWREDLINES2( nAct, pRect )
//STRIP001
#endif
//STRIP001
//STRIP001 #ifdef JP_REDLINE
//STRIP001  if( GetDoc()->GetRedlineTbl().Count() )
//STRIP001  {
//STRIP001      SwRedlineTbl& rRedlineTbl = (SwRedlineTbl&)GetDoc()->GetRedlineTbl();
//STRIP001      for( USHORT i = 0; i < rRedlineTbl.Count(); ++i )
//STRIP001          rRedlineTbl[ i ]->HideRects( *GetShell() );
//STRIP001  }
//STRIP001 #endif

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
//STRIP001
//STRIP001 void __EXPORT SwVisCrsr::Timeout()
//STRIP001 {
//STRIP001  ASSERT( !bIsDragCrsr, "Timer vorher abschalten" );
//STRIP001  if( bIsVisible )
//STRIP001  {
//STRIP001      if ( !pCrsrShell->GetWin() ) //SwFrmFmt::GetGraphic setzt das Win temp aus!
//STRIP001          Start();
//STRIP001      else
//STRIP001          _SetPosAndShow();
//STRIP001  }
//STRIP001 }

//STRIP001 FASTBOOL SwCrsrShell::ChgCrsrTimerFlag( BOOL bTimerOn )
//STRIP001 {
//STRIP001  return pVisCrsr->ChgTimerFlag( bTimerOn );
//STRIP001 }


//STRIP001 FASTBOOL SwVisCrsr::ChgTimerFlag( BOOL bFlag )
//STRIP001 {
//STRIP001  register bOld = bTimerOn;
//STRIP001  if( !bFlag && bIsVisible && IsActive() )
//STRIP001  {
//STRIP001      Stop();         // Timer Stoppen
//STRIP001      _SetPosAndShow();
//STRIP001  }
//STRIP001  bTimerOn = bFlag;
//STRIP001  return bOld;
//STRIP001 }

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
/*N*/     {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/         ::SwCalcPixStatics( pCrsrShell->GetOut() );
//STRIP001 /*?*/         ::SwAlignRect( aRect, (ViewShell*)pCrsrShell );
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
/*?*/   {DBG_ASSERT(0, "STRIP"); }//STRIP001    Paint( (*this)[n] );
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
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001  SwRegionRects aReg( pCShell->VisArea() );
//STRIP001 /*?*/
//STRIP001 /*?*/        // suche die neu selektierten Rechtecke heraus
//STRIP001 /*?*/        aReg.Remove( 0, aReg.Count() );
//STRIP001 /*?*/        aReg.Insert( this, 0 );
//STRIP001 /*?*/
//STRIP001 /*?*/        for( USHORT n = 0; n < aTmp.Count(); ++n )
//STRIP001 /*?*/            aReg -= aTmp[n];
//STRIP001 /*?*/
//STRIP001 /*?*/        // jetzt sollten in aReg nur noch die neuen Rechtecke vorliegen
//STRIP001 /*?*/        for( n = 0; n < aReg.Count(); ++n )
//STRIP001 /*?*/            Paint( aReg[n] );
//STRIP001 /*?*/
//STRIP001 /*?*/        // suche die nicht mehr selektierten Rechtecke heraus
//STRIP001 /*?*/        if( aTmp.Count() )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            aReg.Remove( 0, aReg.Count() );
//STRIP001 /*?*/            aReg.Insert( &aTmp, 0 );
//STRIP001 /*?*/
//STRIP001 /*?*/            for( n = 0; n < Count(); ++n )
//STRIP001 /*?*/                aReg -= (*this)[n];
//STRIP001 /*?*/            // jetzt sollten in aReg nur noch die alten Rechtecke vorliegen
//STRIP001 /*?*/            for( n = 0; n < aReg.Count(); ++n )
//STRIP001 /*?*/                Paint( aReg[n] );
//STRIP001 /*?*/        }
/*N*/   }
/*N*/ }

//STRIP001 void SwSelPaintRects::Invalidate( const SwRect& rRect )
//STRIP001 {
//STRIP001  register USHORT nSz = Count();
//STRIP001  if( !nSz )
//STRIP001      return;
//STRIP001
//STRIP001  SwRegionRects aReg( GetShell()->VisArea() );
//STRIP001  aReg.Remove( 0, aReg.Count() );
//STRIP001  aReg.Insert( this, 0 );
//STRIP001  aReg -= rRect;
//STRIP001  SwRects::Remove( 0, nSz );
//STRIP001  SwRects::Insert( &aReg, 0 );
//STRIP001
//STRIP001  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//STRIP001  // Liegt die Selection rechts oder unten ausserhalb des sichtbaren
//STRIP001  // Bereiches, so ist diese nie auf eine Pixel rechts/unten aligned.
//STRIP001  // Das muss hier erkannt und ggf. das Rechteckt erweitert werden.
//STRIP001  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//STRIP001  if( GetShell()->bVisPortChgd && 0 != ( nSz = Count()) )
//STRIP001  {
//STRIP001      SwSelPaintRects::Get1PixelInLogic( *GetShell() );
//STRIP001      register SwRect* pRect = (SwRect*)GetData();
//STRIP001      for( ; nSz--; ++pRect )
//STRIP001      {
//STRIP001          if( pRect->Right() == GetShell()->aOldRBPos.X() )
//STRIP001              pRect->Right( pRect->Right() + nPixPtX );
//STRIP001          if( pRect->Bottom() == GetShell()->aOldRBPos.Y() )
//STRIP001              pRect->Bottom( pRect->Bottom() + nPixPtY );
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SwSelPaintRects::Paint( const Rectangle& rRect )
//STRIP001 {
//STRIP001  GetShell()->GetWin()->Invert( rRect );
//STRIP001 }

/*
 * Rectangle ist in Dokument-Koordianten !!
 * pWin != 0 ->  auch wirklich malen
 *      == 0 ->  nur testen, ob es gemalt werden kann
 */

//STRIP001 void SwSelPaintRects::Paint( const SwRect& rRect )
//STRIP001 {
//STRIP001  Window* pWin = GetShell()->GetWin();
//STRIP001  const SwRect& rVisArea = GetShell()->VisArea();
//STRIP001
//STRIP001  if( !pWin || rRect.IsEmpty() || !rVisArea.IsOver( rRect ) )
//STRIP001      return;
//STRIP001
//STRIP001  Rectangle aPntRect( rRect.SVRect() );
//STRIP001  Rectangle aCalcRect( aPntRect );
//STRIP001
//STRIP001  aPntRect = pWin->LogicToPixel( aPntRect );
//STRIP001
//STRIP001  // falls nach der "Normalisierung" kein Rectangle besteht -> Ende
//STRIP001  if( aPntRect.Left() == aPntRect.Right() ||
//STRIP001      aPntRect.Top() == aPntRect.Bottom() )
//STRIP001      return;
//STRIP001
//STRIP001  // damit Linien nicht doppelt invertiert werden, muss jeweis von
//STRIP001  // der rechten und unteren Seite ein PIXEL abgezogen werden !
//STRIP001  // Pixel heisst, gleichgueltig, welcher MapMode heute zaehlt !
//STRIP001
//STRIP001  FASTBOOL bChg = FALSE;
//STRIP001  FASTBOOL bTstRight  = rRect.Right() < rVisArea.Right();
//STRIP001  FASTBOOL bTstBottom = rRect.Bottom() < rVisArea.Bottom();
//STRIP001
//STRIP001  if( bTstBottom || bTstRight )
//STRIP001  {
//STRIP001      ++aCalcRect.Bottom();
//STRIP001      ++aCalcRect.Right();
//STRIP001      aCalcRect = pWin->LogicToPixel( aCalcRect );
//STRIP001
//STRIP001      if( bTstBottom && aPntRect.Bottom() == aCalcRect.Bottom() )
//STRIP001      {
//STRIP001          --aPntRect.Bottom();
//STRIP001          bChg = TRUE;
//STRIP001      }
//STRIP001      if( bTstRight && aPntRect.Right() == aCalcRect.Right() )
//STRIP001      {
//STRIP001          --aPntRect.Right();
//STRIP001          bChg = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( bChg )
//STRIP001      Paint( pWin->PixelToLogic( aPntRect ));
//STRIP001  else
//STRIP001      Paint( rRect.SVRect() );
//STRIP001 }


/*N*/void SwSelPaintRects::FillRects()
/*N*/{
/*N*/}

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


//STRIP001 SwShellCrsr::SwShellCrsr( const SwCrsrShell& rCShell, const SwPosition &rPos,
//STRIP001                          const Point& rPtPos, SwPaM* pRing )
//STRIP001  : SwCursor( rPos, pRing ), SwSelPaintRects( rCShell ),
//STRIP001  pPt( SwPaM::GetPoint() ), aPtPt( rPtPos ), aMkPt( rPtPos )
//STRIP001 {}


//STRIP001 SwShellCrsr::SwShellCrsr( SwShellCrsr& rICrsr )
//STRIP001  : SwCursor( rICrsr ), SwSelPaintRects( *rICrsr.GetShell() ),
//STRIP001  pPt( SwPaM::GetPoint() ),
//STRIP001  aPtPt( rICrsr.GetPtPos() ),
//STRIP001  aMkPt( rICrsr.GetMkPos() )
//STRIP001 {}

/*N*/ SwShellCrsr::~SwShellCrsr() {}

/*N*/ SwShellCrsr::operator SwShellCrsr* () { return this; }

//STRIP001 void SwShellCrsr::SetMark()
//STRIP001 {
//STRIP001  if( SwPaM::GetPoint() == pPt )
//STRIP001      aMkPt = aPtPt;
//STRIP001  else
//STRIP001      aPtPt = aMkPt;
//STRIP001  SwPaM::SetMark();
//STRIP001 }

/*N*/ void SwShellCrsr::FillRects()
/*N*/ {
/*N*/   // die neuen Rechtecke berechnen
/*N*/   if( HasMark() &&
/*N*/       GetPoint()->nNode.GetNode().IsCntntNode() &&
/*N*/       GetPoint()->nNode.GetNode().GetCntntNode()->GetFrm() &&
/*N*/       (GetMark()->nNode == GetPoint()->nNode ||
/*N*/       (GetMark()->nNode.GetNode().IsCntntNode() &&
/*N*/        GetMark()->nNode.GetNode().GetCntntNode()->GetFrm() )  ))
/*?*/   {DBG_ASSERT(0, "STRIP"); }//STRIP001    GetDoc()->GetRootFrm()->CalcFrmRects( *this, GetShell()->IsTableMode() );
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
//STRIP001 void SwShellCrsr::Invalidate( const SwRect& rRect )
//STRIP001 {
//STRIP001  SwShellCrsr * pTmp = this;
//STRIP001  do {
//STRIP001      pTmp->SwSelPaintRects::Invalidate( rRect );
//STRIP001  } while( this != ( pTmp = (SwShellCrsr*)*(SwCursor*)(pTmp->GetNext() )));
//STRIP001
//STRIP001  SHOWBOOKMARKS2( 3, &rRect )
//STRIP001  SHOWREDLINES2( 3, &rRect )
//STRIP001 }


//STRIP001 void SwShellCrsr::Hide()
//STRIP001 {
//STRIP001  SwShellCrsr * pTmp = this;
//STRIP001  do {
//STRIP001      pTmp->SwSelPaintRects::Hide();
//STRIP001  } while( this != ( pTmp = (SwShellCrsr*)*(SwCursor*)(pTmp->GetNext() )));
//STRIP001
//STRIP001  SHOWBOOKMARKS1( 2 )
//STRIP001  SHOWREDLINES1( 2 )
//STRIP001 }

//STRIP001 SwCursor* SwShellCrsr::Create( SwPaM* pRing ) const
//STRIP001 {
//STRIP001  return new SwShellCrsr( *GetShell(), *GetPoint(), GetPtPos(), pRing );
//STRIP001 }


//STRIP001 short SwShellCrsr::MaxReplaceArived()
//STRIP001 {
//STRIP001     short nRet = RET_YES;
//STRIP001  Window* pDlg = ::GetSearchDialog();
//STRIP001  if( pDlg )
//STRIP001  {
//STRIP001      // alte Actions beenden; die Tabellen-Frames werden angelegt und
//STRIP001      // eine SSelection kann erzeugt werden
//STRIP001      SvUShorts aArr;
//STRIP001      ViewShell *pShell = GetDoc()->GetRootFrm()->GetCurrShell(),
//STRIP001                *pSh = pShell;
//STRIP001      do {
//STRIP001          for( USHORT nActCnt = 0; pSh->ActionPend(); ++nActCnt )
//STRIP001              pSh->EndAction();
//STRIP001          aArr.Insert( nActCnt, aArr.Count() );
//STRIP001      } while( pShell != ( pSh = (ViewShell*)pSh->GetNext() ) );
//STRIP001
//STRIP001      {
//STRIP001          nRet = QueryBox( pDlg, SW_RES( MSG_COMCORE_ASKSEARCH )).Execute();
//STRIP001      }
//STRIP001
//STRIP001      for( USHORT n = 0; n < aArr.Count(); ++n )
//STRIP001      {
//STRIP001          for( USHORT nActCnt = aArr[n]; nActCnt--; )
//STRIP001              pSh->StartAction();
//STRIP001          pSh = (ViewShell*)pSh->GetNext();
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      // ansonsten aus dem Basic, und dann auf RET_YES schalten
//STRIP001      nRet = RET_YES;
//STRIP001
//STRIP001     return nRet;
//STRIP001 }

//STRIP001 void SwShellCrsr::SaveTblBoxCntnt( const SwPosition* pPos )
//STRIP001 {
//STRIP001  ((SwCrsrShell*)GetShell())->SaveTblBoxCntnt( pPos );
//STRIP001 }

//STRIP001 FASTBOOL SwShellCrsr::UpDown( BOOL bUp, USHORT nCnt )
//STRIP001 {
//STRIP001  return SwCursor::UpDown( bUp, nCnt,
//STRIP001                          &GetPtPos(), GetShell()->GetUpDownX() );
//STRIP001 }

#ifndef PRODUCT

// JP 05.03.98: zum Testen des UNO-Crsr Verhaltens hier die Implementierung
//              am sichtbaren Cursor

//STRIP001 FASTBOOL SwShellCrsr::IsSelOvr( int eFlags )
//STRIP001 {
//STRIP001 #if 0
//STRIP001  SwDoc* pDoc = GetDoc();
//STRIP001  SwNodeIndex aOldIdx( *pDoc->GetNodes()[ GetSavePos()->nNode ] );
//STRIP001  SwNodeIndex& rPtIdx = GetPoint()->nNode;
//STRIP001  SwStartNode *pOldSttNd = aOldIdx.GetNode().FindStartNode(),
//STRIP001              *pNewSttNd = rPtIdx.GetNode().FindStartNode();
//STRIP001  if( pOldSttNd != pNewSttNd )
//STRIP001  {
//STRIP001      BOOL bMoveDown = GetSavePos()->nNode < rPtIdx.GetIndex();
//STRIP001      BOOL bValidPos = FALSE;
//STRIP001      if( bMoveDown )
//STRIP001      {
//STRIP001          // ist das Ende noch nicht erreicht worden?
//STRIP001          while( pOldSttNd->EndOfSectionIndex() > rPtIdx.GetIndex() )
//STRIP001          {
//STRIP001              // dann versuche auf die "Ebene" zurueck zukommen
//STRIP001              rPtIdx.Assign( *pNewSttNd->EndOfSectionNode(), 1 );
//STRIP001              while( pOldSttNd != rPtIdx.GetNode().FindStartNode() )
//STRIP001                  rPtIdx.Assign( *rPtIdx.GetNode().EndOfSectionNode(), 1 );
//STRIP001
//STRIP001              if( !rPtIdx.GetNode().IsCntntNode() &&
//STRIP001                  !pDoc->GetNodes().GoNextSection( &rPtIdx ))
//STRIP001                  break;
//STRIP001
//STRIP001              if( pOldSttNd ==
//STRIP001                  ( pNewSttNd = rPtIdx.GetNode().FindStartNode() ))
//STRIP001              {
//STRIP001                  // das ist die gesuchte Position
//STRIP001                  bValidPos = TRUE;
//STRIP001                  break;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // ist der Start noch nicht erreicht worden?
//STRIP001          while( pOldSttNd->GetIndex() < rPtIdx.GetIndex() )
//STRIP001          {
//STRIP001              // dann versuche auf die "Ebene" zurueck zukommen
//STRIP001              rPtIdx.Assign( *pNewSttNd, -1 );
//STRIP001              while( pOldSttNd != rPtIdx.GetNode().FindStartNode() )
//STRIP001                  rPtIdx.Assign( *rPtIdx.GetNode().FindStartNode(), -1 );
//STRIP001
//STRIP001              if( !rPtIdx.GetNode().IsCntntNode() &&
//STRIP001                  !pDoc->GetNodes().GoPrevSection( &rPtIdx ))
//STRIP001                  break;
//STRIP001
//STRIP001              if( pOldSttNd ==
//STRIP001                  ( pNewSttNd = rPtIdx.GetNode().FindStartNode() ))
//STRIP001              {
//STRIP001                  // das ist die gesuchte Position
//STRIP001                  bValidPos = TRUE;
//STRIP001                  break;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if( bValidPos )
//STRIP001      {
//STRIP001          SwCntntNode* pCNd = GetCntntNode();
//STRIP001          xub_StrLen nCnt = 0;
//STRIP001          if( pCNd && !bMoveDown )
//STRIP001              nCnt = pCNd->Len();
//STRIP001          GetPoint()->nContent.Assign( pCNd, nCnt );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          rPtIdx = GetSavePos()->nNode;
//STRIP001          GetPoint()->nContent.Assign( GetCntntNode(), GetSavePos()->nCntnt );
//STRIP001          return FALSE;
//STRIP001      }
//STRIP001  }
//STRIP001 #endif
//STRIP001  return SwCursor::IsSelOvr( eFlags );
//STRIP001 }

#endif

// TRUE: an die Position kann der Cursor gesetzt werden
//STRIP001 FASTBOOL SwShellCrsr::IsAtValidPos( BOOL bPoint ) const
//STRIP001 {
//STRIP001  if( GetShell() && ( GetShell()->IsAllProtect() ||
//STRIP001      GetShell()->GetViewOptions()->IsReadonly() ||
//STRIP001      ( GetShell()->Imp()->GetDrawView() &&
//STRIP001        GetShell()->Imp()->GetDrawView()->GetMarkList().GetMarkCount() )))
//STRIP001      return TRUE;
//STRIP001
//STRIP001  return SwCursor::IsAtValidPos( bPoint );
//STRIP001 }

/*  */

/*N*/ SwShellTableCrsr::SwShellTableCrsr( const SwCrsrShell& rCrsrSh,
/*N*/                                   const SwPosition& rPos )
/*N*/   : SwTableCursor( rPos ), SwShellCrsr( rCrsrSh, rPos ),
/*N*/       SwCursor( rPos )
/*N*/ {
/*N*/ }

/*N*/ SwShellTableCrsr::SwShellTableCrsr( const SwCrsrShell& rCrsrSh,
/*N*/                   const SwPosition& rMkPos, const Point& rMkPt,
/*N*/                   const SwPosition& rPtPos, const Point& rPtPt )
/*N*/   : SwTableCursor( rPtPos ), SwShellCrsr( rCrsrSh, rPtPos ),
/*N*/       SwCursor( rPtPos )
/*N*/ {
/*N*/   SetMark();
/*N*/   *GetMark() = rMkPos;
/*N*/   GetMkPos() = rMkPt;
/*N*/   GetPtPos() = rPtPt;
/*N*/ }

/*N*/ SwShellTableCrsr::~SwShellTableCrsr() {}

/*N*/ void SwShellTableCrsr::SetMark()              { SwShellCrsr::SetMark(); }
/*N*/ SwShellTableCrsr::operator SwShellCrsr* ()        { return this; }
/*N*/ SwShellTableCrsr::operator SwTableCursor* ()  { return this; }
/*N*/ SwShellTableCrsr::operator SwShellTableCrsr* ()   { return this; }

//STRIP001 SwCursor* SwShellTableCrsr::Create( SwPaM* pRing ) const
//STRIP001 {
//STRIP001  return SwShellCrsr::Create( pRing );
//STRIP001 }
//STRIP001 short SwShellTableCrsr::MaxReplaceArived()
//STRIP001 {
//STRIP001  return SwShellCrsr::MaxReplaceArived();
//STRIP001 }
//STRIP001 void SwShellTableCrsr::SaveTblBoxCntnt( const SwPosition* pPos )
//STRIP001 {
//STRIP001  SwShellCrsr::SaveTblBoxCntnt( pPos );
//STRIP001 }


//STRIP001 void SwShellTableCrsr::FillRects()
//STRIP001 {
//STRIP001  // die neuen Rechtecke berechnen
//STRIP001  // JP 16.01.98: wenn der Cursor noch "geparkt" ist nichts machen!!
//STRIP001  if( !aSelBoxes.Count() || bParked ||
//STRIP001      !GetPoint()->nNode.GetIndex() )
//STRIP001      return;
//STRIP001
//STRIP001  SwRegionRects aReg( GetShell()->VisArea() );
//STRIP001  SwNodes& rNds = GetDoc()->GetNodes();
//STRIP001  for( USHORT n = 0; n < aSelBoxes.Count(); ++n )
//STRIP001  {
//STRIP001      SwNodeIndex aIdx( *(*(aSelBoxes.GetData() + n ))->GetSttNd() );
//STRIP001      SwCntntNode* pCNd = rNds.GoNextSection( &aIdx, TRUE, FALSE );
//STRIP001      if( !pCNd )
//STRIP001          continue;
//STRIP001
//STRIP001      SwFrm* pFrm = pCNd->GetFrm( &GetSttPos() );
//STRIP001      while( pFrm && !pFrm->IsCellFrm() )
//STRIP001          pFrm = pFrm->GetUpper();
//STRIP001      ASSERT( pFrm, "Node nicht in einer Tabelle" );
//STRIP001      if( pFrm && aReg.GetOrigin().IsOver( pFrm->Frm() ) )
//STRIP001          aReg -= pFrm->Frm();
//STRIP001  }
//STRIP001  aReg.Invert();
//STRIP001  Insert( &aReg, 0 );
//STRIP001 }


// Pruefe, ob sich der SPoint innerhalb der Tabellen-SSelection befindet
//STRIP001 FASTBOOL SwShellTableCrsr::IsInside( const Point& rPt ) const
//STRIP001 {
//STRIP001  // die neuen Rechtecke berechnen
//STRIP001  // JP 16.01.98: wenn der Cursor noch "geparkt" ist nichts machen!!
//STRIP001  if( !aSelBoxes.Count() || bParked ||
//STRIP001      !GetPoint()->nNode.GetIndex()  )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SwNodes& rNds = GetDoc()->GetNodes();
//STRIP001  for( USHORT n = 0; n < aSelBoxes.Count(); ++n )
//STRIP001  {
//STRIP001      SwNodeIndex aIdx( *(*(aSelBoxes.GetData() + n ))->GetSttNd() );
//STRIP001      SwCntntNode* pCNd = rNds.GoNextSection( &aIdx, TRUE, FALSE );
//STRIP001      if( !pCNd )
//STRIP001          continue;
//STRIP001
//STRIP001      SwFrm* pFrm = pCNd->GetFrm( &GetPtPos() );
//STRIP001      while( pFrm && !pFrm->IsCellFrm() )
//STRIP001          pFrm = pFrm->GetUpper();
//STRIP001      ASSERT( pFrm, "Node nicht in einer Tabelle" );
//STRIP001      if( pFrm && pFrm->Frm().IsInside( rPt ) )
//STRIP001          return TRUE;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

#ifndef PRODUCT

// JP 05.03.98: zum Testen des UNO-Crsr Verhaltens hier die Implementierung
//              am sichtbaren Cursor
//STRIP001 FASTBOOL SwShellTableCrsr::IsSelOvr( int eFlags )
//STRIP001 {
//STRIP001  return SwShellCrsr::IsSelOvr( eFlags );
//STRIP001 }

#endif

//STRIP001 FASTBOOL SwShellTableCrsr::IsAtValidPos( BOOL bPoint ) const
//STRIP001 {
//STRIP001  return SwShellCrsr::IsAtValidPos( bPoint );
//STRIP001 }

