/*************************************************************************
 *
 *  $RCSfile: sw_scrrect.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:44:39 $
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

#ifndef _VIEWIMP_HXX
#include <viewimp.hxx>
#endif
#ifndef _VIEWSH_HXX
#include <viewsh.hxx>
#endif
#ifndef _VIEWOPT_HXX
#include <viewopt.hxx>
#endif
#ifndef _SV_WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif
#ifndef _SCRRECT_HXX
#include <scrrect.hxx>      // SwScrollRect, SwScrollRects
#endif
// OD 18.02.2003 #107562# - <SwAlignRect> for <ViewShell::Scroll()>
#ifndef _FRMTOOL_HXX
#include <frmtool.hxx>
#endif
#ifndef _TOOLS_DEBUG_HXX //autogen
#include <tools/debug.hxx>
#endif
#ifndef _CURSOR_HXX //autogen
#include <vcl/cursor.hxx>
#endif
#ifndef _SV_VIRDEV_HXX //autogen
#include <vcl/virdev.hxx>
#endif
#ifndef _APP_HXX //autogen
#include <vcl/svapp.hxx>
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>
#endif
#include "crsrsh.hxx"
#include "rootfrm.hxx"
#include "pagefrm.hxx"
#include "doc.hxx"
// OD 12.11.2002 #96272# - include declaration for <SetMappingForVirtDev>
#include "setmapvirtdev.hxx"

//STRIP001 DBG_NAME(RefreshTimer);
//STRIP001
//STRIP001 SV_IMPL_VARARR(SwStripeArr,SwStripe);
//STRIP001 SV_IMPL_OP_PTRARR_SORT(SwScrollStripes, SwStripesPtr);
//STRIP001 SV_IMPL_OP_PTRARR_SORT(SScrAreas, SwScrollAreaPtr);

/*****************************************************************************
|*
|*  ViewShell::AddScrollRect()
|*
|*  Creation            MA 07. Mar. 94
|*  Last change         AMA 20. July 00
|*
|*  Description
|*  ViewShell::AddScrollRect(..) passes a registration from a scrolling frame or
|*  rectangle to all ViewShells and SwViewImps respectively.
|*
******************************************************************************/

/*N*/ void ViewShell::AddScrollRect( const SwFrm *pFrm, const SwRect &rRect,
/*N*/   long nOfs )
/*N*/ {
/*N*/   ASSERT( pFrm, "Where is my friend, the frame?" );
/*N*/   BOOL bScrollOn = TRUE;
/*N*/
/*N*/ #ifdef NOSCROLL
/*N*/   //Auch im Product per speziellem Compilat abschaltbar.
/*N*/   bScrollOn = FALSE;
/*N*/ #endif
/*N*/
/*N*/   if( bScrollOn && Imp()->IsScroll() && nOfs <= SHRT_MAX && nOfs >= SHRT_MIN )
/*N*/   {
/*N*/       ViewShell *pSh = this;
/*N*/       do
/*N*/       {
/*N*/           pSh->Imp()->AddScrollRect( pFrm, rRect, nOfs );
/*N*/           pSh = (ViewShell*)pSh->GetNext();
/*N*/       } while ( pSh != this );
/*N*/   }
/*N*/   else
/*N*/       AddPaintRect( rRect );
/*N*/ }

/******************************************************************************
|*
|*  ViewShell::Scroll()
|*
|*  Ersterstellung      MA 07. Mar. 94
|*  Last change         AMA 21. July 00
|*
|*  Description
|*  ViewShell::Scroll() scrolls all rectangles in the pScrollRects-list and
|*  transfers the critical lines by calling SwViewImp::MoveScrollArea(..).
|*
******************************************************************************/

/*N*/ void ViewShell::Scroll()
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  SwScrollAreas *pScrollRects = Imp()->GetScrollRects();
//STRIP001  if ( pScrollRects )
//STRIP001  {
//STRIP001      bPaintWorks = FALSE;
//STRIP001      ASSERT( pScrollRects->Count(), "ScrollRects ohne ScrollRects." );
//STRIP001
//STRIP001      //Abgleichen der Region mit den Scroll-Bereichen!!!
//STRIP001      //Wenn eines der Scroll-Rechtecke ungueltig wird, so muss
//STRIP001      //der PaintMode wahrscheinlich auf PAINT_BACKGROUND umgeschaltet
//STRIP001      //werden.
//STRIP001
//STRIP001      //Auf die Richtung kommt es an:
//STRIP001      //- Bei einem pos. Ofst muss von hinten nach vorn gescrollt werden.
//STRIP001      //- Bei einem neg. Ofst muss von vorn nach hinten gescrollt werden.
//STRIP001         BOOL bPositive = (*pScrollRects)[0]->GetOffs() > 0;
//STRIP001         if( (*pScrollRects)[0]->IsVertical() )
//STRIP001             bPositive = !bPositive;
//STRIP001      int i = bPositive ? pScrollRects->Count()-1 : 0;
//STRIP001
//STRIP001      for ( ; bPositive ? i >= 0 : i < (int)pScrollRects->Count();
//STRIP001              bPositive ? --i : ++i )
//STRIP001      {
//STRIP001          const SwScrollArea &rScroll = *(*pScrollRects)[i];
//STRIP001          if( rScroll.Count() )
//STRIP001          {
//STRIP001              int j = bPositive ? rScroll.Count()-1 : 0;
//STRIP001              for ( ; bPositive ? j >= 0 : j < (int)rScroll.Count();
//STRIP001                  bPositive ? --j : ++j )
//STRIP001              {
//STRIP001                  const SwStripes& rStripes = *rScroll[j];
//STRIP001                     if( rScroll.IsVertical() )
//STRIP001                     {
//STRIP001                         Rectangle aRectangle( rStripes.GetY() -
//STRIP001                             rStripes.GetHeight() + rScroll.GetOffs(),
//STRIP001                             rStripes.GetMin(),
//STRIP001                             rStripes.GetY() + rScroll.GetOffs(),
//STRIP001                             rStripes.GetMax() );
//STRIP001                         // OD 18.02.2003 #107562# - align rectangle for scrolling
//STRIP001                         SwRect aAlignedScrollRect( aRectangle );
//STRIP001                         ::SwAlignRect( aAlignedScrollRect, this );
//STRIP001                         GetWin()->Scroll( -rScroll.GetOffs(), 0,
//STRIP001                                           aAlignedScrollRect.SVRect(),
//STRIP001                                           SCROLL_CHILDREN );
//STRIP001                         SwRect aRect( aRectangle );
//STRIP001                         Imp()->ScrolledRect( aRect, -rScroll.GetOffs() );
//STRIP001                         if ( bPositive )
//STRIP001                             aRect.Right( aRect.Left() + rScroll.GetOffs()-1 );
//STRIP001                         else
//STRIP001                             aRect.Left( aRect.Right() - rScroll.GetOffs() );
//STRIP001                         Imp()->AddPaintRect( aRect );
//STRIP001                     }
//STRIP001                     else
//STRIP001                     {
//STRIP001                         Rectangle aRectangle( rStripes.GetMin(),
//STRIP001                             rStripes.GetY() - rScroll.GetOffs(),
//STRIP001                             rStripes.GetRight(),
//STRIP001                             rStripes.GetBottom() - rScroll.GetOffs() );
//STRIP001                         // OD 18.02.2003 #107562# - use aligned rectangle for scrolling
//STRIP001                         SwRect aAlignedScrollRect( aRectangle );
//STRIP001                         ::SwAlignRect( aAlignedScrollRect, this );
//STRIP001                         GetWin()->Scroll( 0, rScroll.GetOffs(),
//STRIP001                                           aAlignedScrollRect.SVRect(),
//STRIP001                                           SCROLL_CHILDREN );
//STRIP001                         SwRect aRect( aRectangle );
//STRIP001                         Imp()->ScrolledRect( aRect, rScroll.GetOffs() );
//STRIP001                         if ( bPositive )
//STRIP001                             aRect.Bottom( aRect.Top() + rScroll.GetOffs()-1 );
//STRIP001                         else
//STRIP001                             aRect.Top( aRect.Bottom() + rScroll.GetOffs() );
//STRIP001                         Imp()->AddPaintRect( aRect );
//STRIP001                     }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      if ( !Imp()->IsScrolled() )
//STRIP001          Imp()->SetScrolled();
//STRIP001
//STRIP001      Imp()->MoveScrollArea();
//STRIP001      bPaintWorks = TRUE;
//STRIP001  }
/*N*/ }

/******************************************************************************
|*
|*  ViewShell::SetNoNextScroll()
|*
|*  Ersterstellung      MA 08. Mar. 94
|*  Letzte Aenderung    MA 08. Mar. 94
|*
******************************************************************************/

/*N*/ void ViewShell::SetNoNextScroll()
/*N*/ {
/*N*/   ViewShell *pSh = this;
/*N*/   do
/*N*/   {   pSh->Imp()->ResetNextScroll();
/*N*/       pSh = (ViewShell*)pSh->GetNext();
/*N*/
/*N*/   } while ( pSh != this );
/*N*/ }

/******************************************************************************
|*
|*  SwViewImp::AddScrollRect()
|*
|*  Ersterstellung      MA 07. Mar. 94
|*  Last change         AMA 21. July 00
|*
|*  Adds a scrollable rectangle and his critical lines to the list.
|*
******************************************************************************/

/*N*/ void SwViewImp::AddScrollRect( const SwFrm *pFrm, const SwRect &rRect,
/*N*/   long nOffs )
/*N*/ {
/*N*/   ASSERT( nOffs != 0, "Scrollen ohne Ofst." );
/*N*/   SwRect aRect( rRect );
/*N*/     BOOL bVert = pFrm->IsVertical();
/*N*/     if( bVert )
/*?*/         aRect.Pos().X() += nOffs;
/*N*/     else
/*N*/   aRect.Pos().Y() -= nOffs;
/*N*/   if( aRect.IsOver( pSh->VisArea() ) )
/*N*/   {
            DBG_ASSERT(0, "STRIP"); //STRIP001 /*?*/        ASSERT( pSh->GetWin(), "Scrolling without outputdevice" );
//STRIP001 /*?*/        aRect._Intersection( pSh->VisArea() );
//STRIP001 /*?*/         SwStripes *pStr;
//STRIP001 /*?*/         if ( !pScrollRects )
//STRIP001 /*?*/             pScrollRects = new SwScrollAreas;
//STRIP001 /*?*/         if( bVert )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             aRect.Pos().X() -= nOffs;
//STRIP001 /*?*/             pStr = new SwStripes( aRect.Right(), aRect.Width(),
//STRIP001 /*?*/                                   aRect.Top(), aRect.Bottom() );
//STRIP001 /*?*/             if( pFrm->IsTxtFrm() )
//STRIP001 /*?*/                 ((SwTxtFrm*)pFrm)->CriticalLines(*pSh->GetWin(), *pStr, nOffs );
//STRIP001 /*?*/             else
//STRIP001 /*?*/                 pStr->Insert( SwStripe( aRect.Right(), aRect.Width() ), 0 );
//STRIP001 /*?*/             pScrollRects->InsertCol( SwScrollColumn( pFrm->Frm().Top(),
//STRIP001 /*?*/                                     pFrm->Frm().Height(), nOffs, bVert ), pStr);
//STRIP001 /*?*/         }
//STRIP001 /*?*/         else
//STRIP001 /*?*/         {
//STRIP001 /*?*/             aRect.Pos().Y() += nOffs;
//STRIP001 /*?*/             pStr = new SwStripes( aRect.Top(), aRect.Height(),
//STRIP001 /*?*/                                   aRect.Left(), aRect.Right() );
//STRIP001 /*?*/             if( pFrm->IsTxtFrm() )
//STRIP001 /*?*/                 ((SwTxtFrm*)pFrm)->CriticalLines(*pSh->GetWin(), *pStr, nOffs );
//STRIP001 /*?*/             else
//STRIP001 /*?*/                 pStr->Insert( SwStripe( aRect.Top(), aRect.Height() ), 0 );
//STRIP001 /*?*/             pScrollRects->InsertCol( SwScrollColumn( pFrm->Frm().Left(),
//STRIP001 /*?*/                                     pFrm->Frm().Width(), nOffs, bVert ), pStr );
//STRIP001 /*?*/         }
/*N*/   }
/*N*/   else
/*N*/       AddPaintRect( rRect );
/*N*/ }

/******************************************************************************
|*
|*  SwViewImp::MoveScrollArea()
|*
|*  Creation            AMA 10. July 00
|*  Last change         AMA 21. July 00
|*
|*  Transfers the areas after scrolling to the scrolled list, but only those
|*  parts with critical lines.
|*
******************************************************************************/

//STRIP001 void SwViewImp::MoveScrollArea()
//STRIP001 {
//STRIP001  if( !pScrolledArea )
//STRIP001      pScrolledArea = new SwScrollAreas;
//STRIP001     for( USHORT nIdx = 0; nIdx < pScrollRects->Count(); ++nIdx )
//STRIP001  {
//STRIP001      SwScrollArea *pScr = (*pScrollRects)[ nIdx ];
//STRIP001      if( pScr->Compress() )
//STRIP001          delete pScr;
//STRIP001      else
//STRIP001      {
//STRIP001          USHORT nIdx;
//STRIP001          if( pScrolledArea->Seek_Entry( pScr, &nIdx ) )
//STRIP001              pScrolledArea->GetObject(nIdx)->Add( pScr );
//STRIP001          else
//STRIP001              pScrolledArea->Insert( pScr );
//STRIP001      }
//STRIP001  }
//STRIP001  delete pScrollRects;
//STRIP001  pScrollRects = NULL;
//STRIP001 }

/******************************************************************************
|*
|*  SwViewImp::FlushScrolledArea()
|*
|*  Creation            AMA 10. July 00
|*  Last change         AMA 21. July 00
|*
|*  Flushes the scrolled critical lines, that is transfer them to AddPaintRect()
|*  and remove them from the list.
|*
******************************************************************************/

//STRIP001 void SwViewImp::FlushScrolledArea()
//STRIP001 {
//STRIP001     USHORT nCount = pScrolledArea->Count();
//STRIP001  while( nCount )
//STRIP001  {
//STRIP001      SwScrollArea* pScroll = (*pScrolledArea)[--nCount];
//STRIP001         USHORT nCnt = pScroll->Count();
//STRIP001      while( nCnt )
//STRIP001      {
//STRIP001          SwStripes* pStripes = (*pScroll)[--nCnt];
//STRIP001             if( pScroll->IsVertical() )
//STRIP001             {
//STRIP001                 SwRect aRect( 0, pStripes->GetMin(), 0, pStripes->GetWidth() );
//STRIP001                 for( USHORT i = 0; i < pStripes->Count(); ++i )
//STRIP001                 {
//STRIP001                     long nWidth = (*pStripes)[i].GetHeight();
//STRIP001                     aRect.Left( (*pStripes)[i].GetY() - nWidth + 1 );
//STRIP001                     aRect.Width( nWidth );
//STRIP001                     AddPaintRect( aRect );
//STRIP001                 }
//STRIP001             }
//STRIP001             {
//STRIP001                 SwRect aRect( pStripes->GetMin(), 0, pStripes->GetWidth(), 0 );
//STRIP001                 for( USHORT i = 0; i < pStripes->Count(); ++i )
//STRIP001                 {
//STRIP001                     aRect.Top( (*pStripes)[i].GetY() );
//STRIP001                     aRect.Height( (*pStripes)[i].GetHeight() );
//STRIP001                     AddPaintRect( aRect );
//STRIP001                 }
//STRIP001             }
//STRIP001          pScroll->Remove( nCnt );
//STRIP001          delete pStripes;
//STRIP001      }
//STRIP001      pScrolledArea->Remove( nCount );
//STRIP001      delete pScroll;
//STRIP001  }
//STRIP001  delete pScrolledArea;
//STRIP001  pScrolledArea = NULL;
//STRIP001 }

/******************************************************************************
|*
|*  SwViewImp::_FlushScrolledArea(..)
|*
|*  Creation            AMA 10. July 00
|*  Last change         AMA 21. July 00
|*
|*  The critical lines, which overlaps with the given rectangle, will be united
|*  with the rectangle and removed from the list.
|*
******************************************************************************/

//STRIP001 BOOL SwViewImp::_FlushScrolledArea( SwRect& rRect )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001     for( USHORT i = pScrolledArea->Count(); i; )
//STRIP001  {
//STRIP001      SwScrollArea* pScroll = (*pScrolledArea)[--i];
//STRIP001         for( USHORT j = pScroll->Count(); j; )
//STRIP001      {
//STRIP001          SwStripes* pStripes = (*pScroll)[--j];
//STRIP001          if( pStripes->Count() )
//STRIP001          {
//STRIP001                 if( pScroll->IsVertical() )
//STRIP001                 {
//STRIP001                     SwRect aRect( pStripes->GetY() - pStripes->GetHeight(),
//STRIP001                         pStripes->GetMin(), pStripes->GetHeight(),
//STRIP001                         pStripes->GetWidth() );
//STRIP001                     if( rRect.IsOver( aRect ) )
//STRIP001                     {
//STRIP001                         for( USHORT nI = pStripes->Count(); nI; )
//STRIP001                         {
//STRIP001                             long nWidth = (*pStripes)[--nI].GetHeight();
//STRIP001                             aRect.Left( (*pStripes)[nI].GetY() - nWidth + 1 );
//STRIP001                             aRect.Width( nWidth );
//STRIP001                             if( rRect.IsOver( aRect ) )
//STRIP001                             {
//STRIP001                                 rRect.Union( aRect );
//STRIP001                                 bRet = TRUE;
//STRIP001                                 pStripes->Remove( nI );
//STRIP001                                 nI = pStripes->Count();
//STRIP001                             }
//STRIP001                         }
//STRIP001                     }
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     SwRect aRect( pStripes->GetMin(), pStripes->GetY(),
//STRIP001                         pStripes->GetWidth(), pStripes->GetHeight() );
//STRIP001                     if( rRect.IsOver( aRect ) )
//STRIP001                     {
//STRIP001                         for( USHORT nI = pStripes->Count(); nI; )
//STRIP001                         {
//STRIP001                             aRect.Top( (*pStripes)[--nI].GetY() );
//STRIP001                             aRect.Height( (*pStripes)[nI].GetHeight() );
//STRIP001                             if( rRect.IsOver( aRect ) )
//STRIP001                             {
//STRIP001                                 rRect.Union( aRect );
//STRIP001                                 bRet = TRUE;
//STRIP001                                 pStripes->Remove( nI );
//STRIP001                                 nI = pStripes->Count();
//STRIP001                             }
//STRIP001                         }
//STRIP001                     }
//STRIP001                 }
//STRIP001             }
//STRIP001          if( !pStripes->Count() )
//STRIP001          {
//STRIP001              pScroll->Remove( j );
//STRIP001              delete pStripes;
//STRIP001          }
//STRIP001      }
//STRIP001      if( !pScroll->Count() )
//STRIP001      {
//STRIP001          pScrolledArea->Remove( pScroll );
//STRIP001          delete pScroll;
//STRIP001      }
//STRIP001  }
//STRIP001  if( !pScrolledArea->Count() )
//STRIP001  {
//STRIP001      DELETEZ( pScrolledArea );
//STRIP001      SetNextScroll();
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/******************************************************************************
|*
|*  SwViewImp::RefreshScrolledHdl(..)
|*
|*  Creation            MA 06. Oct. 94
|*  Last change         AMA 21. July 00
|*
|*  Every timerstop one of the critical lines will be painted.
|*
******************************************************************************/

/*N*/ IMPL_LINK( SwViewImp, RefreshScrolledHdl, Timer *, EMPTYARG )
/*N*/ {
        {DBG_ASSERT(0, "STRIP");} return 0;//STRIP001   DBG_PROFSTART( RefreshTimer );
//STRIP001
//STRIP001  if ( !IsScrolled() )
//STRIP001  {   DBG_PROFSTOP( RefreshTimer );
//STRIP001      return 0;
//STRIP001  }
//STRIP001
//STRIP001  SET_CURR_SHELL( GetShell() );
//STRIP001
//STRIP001  //Kein Refresh wenn eine Selektion besteht.
//STRIP001  if ( GetShell()->IsA( TYPE(SwCrsrShell) ) &&
//STRIP001       (((SwCrsrShell*)GetShell())->HasSelection() ||
//STRIP001        ((SwCrsrShell*)GetShell())->GetCrsrCnt() > 1))
//STRIP001  {
//STRIP001      DBG_PROFSTOP( RefreshTimer );
//STRIP001      return 0;
//STRIP001  }
//STRIP001
//STRIP001  if( pScrolledArea )
//STRIP001  {
//STRIP001      BOOL bFound = FALSE;
//STRIP001      const SwRect aRect( GetShell()->VisArea() );
//STRIP001      BOOL bNoRefresh = GetShell()->IsA( TYPE(SwCrsrShell) ) &&
//STRIP001          ( ((SwCrsrShell*)GetShell())->HasSelection() ||
//STRIP001          ((SwCrsrShell*)GetShell())->GetCrsrCnt() > 1 );
//STRIP001      if( pScrolledArea->Count() )
//STRIP001      {
//STRIP001          SwScrollArea* pScroll = pScrolledArea->GetObject(0);
//STRIP001          ASSERT( pScroll->Count(), "Empty scrollarea" );
//STRIP001          SwStripes* pStripes = pScroll->GetObject(0);
//STRIP001          ASSERT( pStripes->Count() > 1, "Empty scrollstripes" );
//STRIP001          const SwStripe &rStripe = pStripes->GetObject(1);
//STRIP001             SwRect aTmpRect = pScroll->IsVertical() ?
//STRIP001                 SwRect( rStripe.GetY() - rStripe.GetHeight(), pScroll->GetX(),
//STRIP001                           rStripe.GetHeight(), pScroll->GetWidth() ) :
//STRIP001                 SwRect( pScroll->GetX(), rStripe.GetY(),
//STRIP001                         pScroll->GetWidth(), rStripe.GetHeight() );
//STRIP001          if( aTmpRect.IsOver( aRect ) )
//STRIP001          {
//STRIP001              SwSaveHdl aSaveHdl( this );
//STRIP001              if( !bNoRefresh )
//STRIP001                  _RefreshScrolledArea( aTmpRect );
//STRIP001          }
//STRIP001          pStripes->Remove( 1 );
//STRIP001          if( pStripes->Count() < 2 )
//STRIP001          {
//STRIP001              pScroll->Remove( USHORT(0) );
//STRIP001              delete pStripes;
//STRIP001          }
//STRIP001          if( !pScroll->Count() )
//STRIP001          {
//STRIP001              pScrolledArea->Remove( pScroll );
//STRIP001              delete pScroll;
//STRIP001          }
//STRIP001      }
//STRIP001      if( !pScrolledArea->Count() )
//STRIP001      {
//STRIP001          delete pScrolledArea;
//STRIP001          pScrolledArea = 0;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  //All done?
//STRIP001  if( !pScrolledArea || !pScrolledArea->Count()
//STRIP001      )
//STRIP001  {
//STRIP001      ResetScrolled();
//STRIP001      SetNextScroll();
//STRIP001      aScrollTimer.Stop();
//STRIP001  }
//STRIP001
//STRIP001  DBG_PROFSTOP( RefreshTimer );
//STRIP001     return 0;
/*N*/ }

/******************************************************************************
|*
|*  SwViewImp::_ScrolledRect(..)
|*
|*  Creation            AMA 20. July 00
|*  Last change         AMA 21. July 00
|*
|*  handles the problem of scrolled criticals lines, when they are a part of
|*  a scrolling area again. In this case, their rectangle has to move to the
|*  right position.
|*
******************************************************************************/

//STRIP001 void SwViewImp::_ScrolledRect( const SwRect& rRect, long nOffs )
//STRIP001 {
//STRIP001     for( USHORT i = pScrolledArea->Count(); i; )
//STRIP001  {
//STRIP001      SwScrollArea* pScroll = (*pScrolledArea)[--i];
//STRIP001      ASSERT( pScroll->Count() == 1, "Missing scrollarea compression 1" );
//STRIP001      SwStripes* pStripes = (*pScroll)[0];
//STRIP001      if( pStripes->Count() )
//STRIP001      {
//STRIP001             SwRect aRect = pScroll->IsVertical() ?
//STRIP001                 SwRect( pStripes->GetY() - pStripes->GetHeight(),
//STRIP001                         pStripes->GetMin(), pStripes->GetHeight(),
//STRIP001                         pStripes->GetWidth() ) :
//STRIP001                 SwRect( pStripes->GetMin(), pStripes->GetY(),
//STRIP001                         pStripes->GetWidth(), pStripes->GetHeight() );
//STRIP001
//STRIP001          if( rRect.IsOver( aRect ) )
//STRIP001          {
//STRIP001              BOOL bRecalc = FALSE;
//STRIP001                 for( USHORT nI = pStripes->Count(); nI; )
//STRIP001              {
//STRIP001                     if( pScroll->IsVertical() )
//STRIP001                     {
//STRIP001                         long nWidth = (*pStripes)[--nI].GetHeight();
//STRIP001                         aRect.Left( (*pStripes)[nI].GetY() - nWidth + 1 );
//STRIP001                         aRect.Width( nWidth );
//STRIP001                     }
//STRIP001                     else
//STRIP001                     {
//STRIP001                         aRect.Top( (*pStripes)[--nI].GetY() );
//STRIP001                         aRect.Height( (*pStripes)[nI].GetHeight() );
//STRIP001                     }
//STRIP001                  if( rRect.IsInside( aRect ) )
//STRIP001                  {
//STRIP001                      (*pStripes)[nI].Y() += nOffs;
//STRIP001                      bRecalc = TRUE;
//STRIP001                  }
//STRIP001              }
//STRIP001              if( bRecalc )
//STRIP001                     pStripes->Recalc( pScroll->IsVertical() );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/******************************************************************************
|*
|*  SwViewImp::_RefreshScrolledArea()
|*
******************************************************************************/

//Berechnen der Hoehe fuer das virtuelle Device, Breite und maximaler
//Speicherbedarf sind vorgegeben.
#define MAXKB 180L

//STRIP001 void lcl_CalcVirtHeight( OutputDevice *pOut, Size &rSz )
//STRIP001 {
//STRIP001  char nBytes;
//STRIP001  const ULONG nColorCount = pOut->GetColorCount();
//STRIP001  if( 256 >= nColorCount )                // 2^8
//STRIP001      nBytes = 1;
//STRIP001  else
//STRIP001      if( USHRT_MAX >= nColorCount )      // 2^16
//STRIP001          nBytes = 2;
//STRIP001      else
//STRIP001          if( 16777216 >= nColorCount )   // 2^24
//STRIP001              nBytes = 3;
//STRIP001          else
//STRIP001              nBytes = 4;                 // 2^n
//STRIP001
//STRIP001  rSz = pOut->LogicToPixel( rSz );
//STRIP001
//STRIP001  long nKB = MAXKB * 1000;
//STRIP001  nKB /= nBytes;
//STRIP001  if ( rSz.Width() > 0 )
//STRIP001      rSz.Height() = nKB / rSz.Width();
//STRIP001  else
//STRIP001      rSz.Height() = nKB;
//STRIP001
//STRIP001  rSz = pOut->PixelToLogic( rSz );
//STRIP001 }

//STRIP001 void SwViewImp::_RefreshScrolledArea( const SwRect &rRect )
//STRIP001 {
//STRIP001  SwRect aScRect( rRect );
//STRIP001  aScRect.Intersection( GetShell()->VisArea() );
//STRIP001
//STRIP001  if( aScRect.IsEmpty() )
//STRIP001      return;
//STRIP001
//STRIP001  BOOL bShowCrsr = FALSE;
//STRIP001  Window *pWin = GetShell()->GetWin();
//STRIP001  if ( pWin && pWin->GetCursor() && pWin->GetCursor()->IsVisible() )
//STRIP001  {
//STRIP001      bShowCrsr = TRUE;
//STRIP001      pWin->GetCursor()->Hide();
//STRIP001  }
//STRIP001
//STRIP001  //Virtuelles Device erzeugen und einstellen.
//STRIP001  OutputDevice *pOld = GetShell()->GetOut();
//STRIP001  VirtualDevice *pVout = new VirtualDevice( *pOld );
//STRIP001  MapMode aMapMode( pOld->GetMapMode() );
//STRIP001  pVout->SetMapMode( aMapMode );
//STRIP001  Size aSize( aScRect.Width(), 0 );
//STRIP001  lcl_CalcVirtHeight( pOld, aSize );
//STRIP001  if ( aSize.Height() > aScRect.Height() )
//STRIP001      aSize.Height() = aScRect.Height() + 50;
//STRIP001
//STRIP001  //unten in der Schleife lassen wir die Rechtecke ein wenig ueberlappen,
//STRIP001  //das muss auch bei der Groesse beruecksichtigt werden.
//STRIP001  aSize = pOld->LogicToPixel( aSize );
//STRIP001     aSize.Width() += 4; aSize.Height() += 4;
//STRIP001  aSize = pOld->PixelToLogic( aSize );
//STRIP001
//STRIP001  const SwRootFrm* pLayout = GetShell()->GetLayout();
//STRIP001
//STRIP001  if( pVout->SetOutputSize( aSize ) )
//STRIP001  {
//STRIP001      pVout->SetLineColor( pOld->GetLineColor() );
//STRIP001      pVout->SetFillColor( pOld->GetFillColor() );
//STRIP001
//STRIP001      //Virtuelles Device in die ViewShell 'selektieren'
//STRIP001      GetShell()->pOut = pVout;
//STRIP001
//STRIP001      const SwFrm *pPg = GetFirstVisPage();
//STRIP001      do
//STRIP001      {
//STRIP001          SwRect aRect( pPg->Frm() );
//STRIP001          if ( aRect.IsOver( aScRect ) )
//STRIP001          {
//STRIP001              aRect._Intersection( aScRect );
//STRIP001              do
//STRIP001              {   Rectangle aTmp( aRect.SVRect() );
//STRIP001                  long nTmp = aTmp.Top() + aSize.Height();
//STRIP001                  if ( aTmp.Bottom() > nTmp )
//STRIP001                      aTmp.Bottom() = nTmp;
//STRIP001
//STRIP001                  aTmp = pOld->LogicToPixel( aTmp );
//STRIP001                     if( aRect.Top() > pPg->Frm().Top() )
//STRIP001                         aTmp.Top()  -= 2;
//STRIP001                     if( aRect.Top() + aRect.Height() < pPg->Frm().Top()
//STRIP001                                                      + pPg->Frm().Height() )
//STRIP001                         aTmp.Bottom() += 2;
//STRIP001                     if( aRect.Left() > pPg->Frm().Left() )
//STRIP001                         aTmp.Left() -= 2;
//STRIP001                     if( aRect.Left() + aRect.Width() < pPg->Frm().Left()
//STRIP001                                                      + pPg->Frm().Width() )
//STRIP001                         aTmp.Right() += 2;
//STRIP001                  aTmp = pOld->PixelToLogic( aTmp );
//STRIP001                     SwRect aTmp2( aTmp );
//STRIP001
//STRIP001                     // OD 12.11.2002 #96272# - use method to set mapping
//STRIP001                     //Point aOrigin( aTmp2.Pos() );
//STRIP001                     //aOrigin.X() = -aOrigin.X(); aOrigin.Y() = -aOrigin.Y();
//STRIP001                     //aMapMode.SetOrigin( aOrigin );
//STRIP001                     ::SetMappingForVirtDev( aTmp2.Pos(), &aMapMode, pOld, pVout );
//STRIP001                  pVout->SetMapMode( aMapMode );
//STRIP001
//STRIP001                  pLayout->Paint( aTmp2 );
//STRIP001                  pOld->DrawOutDev( aTmp2.Pos(), aTmp2.SSize(),
//STRIP001                                    aTmp2.Pos(), aTmp2.SSize(), *pVout );
//STRIP001
//STRIP001                  aRect.Top( aRect.Top() + aSize.Height() );
//STRIP001                  aScRect.Top( aRect.Top() );
//STRIP001
//STRIP001              } while ( aRect.Height() > 0 );
//STRIP001          }
//STRIP001          pPg = pPg->GetNext();
//STRIP001
//STRIP001      } while ( pPg && pPg->Frm().IsOver( GetShell()->VisArea() ) );
//STRIP001
//STRIP001      GetShell()->pOut = pOld;
//STRIP001      delete pVout;
//STRIP001      if( GetShell()->GetViewOptions()->IsControl() && HasDrawView() )
//STRIP001          PaintLayer( GetShell()->GetDoc()->GetControlsId(), aScRect );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      delete pVout;
//STRIP001      pLayout->Paint( aScRect );
//STRIP001  }
//STRIP001
//STRIP001  if ( bShowCrsr )
//STRIP001      pWin->GetCursor()->Show();
//STRIP001 }

/******************************************************************************
|*
|*  SwViewImp::RefreshScrolledArea()
|*
|*  Ersterstellung      MA 06. Oct. 94
|*  Letzte Aenderung    MA 19. Apr. 95
|*
******************************************************************************/

//STRIP001 void SwViewImp::RefreshScrolledArea( SwRect &rRect )
//STRIP001 {
//STRIP001  //1. Wird auch von der CrsrShell gerufen, um ggf. den Bereich, in den der
//STRIP001  //Crsr gesetzt wird (Absatz, ganze Zeile bei einer Tabelle) aufzufrischen.
//STRIP001  //Allerdings kann es dann natuerlich sein, dass das Rechteck ueberhaupt
//STRIP001  //nicht mit aufzufrischenden Bereichen ueberlappt.
//STRIP001  //2. Kein Refresh wenn eine Selektion besteht.
//STRIP001  if( (GetShell()->IsA( TYPE(SwCrsrShell) ) &&
//STRIP001        (((SwCrsrShell*)GetShell())->HasSelection() ||
//STRIP001         ((SwCrsrShell*)GetShell())->GetCrsrCnt() > 1)))
//STRIP001  {
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  if( pScrolledArea && pScrolledArea->Count() &&
//STRIP001      !( ( GetShell()->IsA( TYPE(SwCrsrShell) ) &&
//STRIP001      ( ((SwCrsrShell*)GetShell())->HasSelection() ||
//STRIP001        ((SwCrsrShell*)GetShell())->GetCrsrCnt() > 1) ) ) )
//STRIP001  {
//STRIP001         for( USHORT i = pScrolledArea->Count(); i; )
//STRIP001      {
//STRIP001          SwScrollArea* pScroll = (*pScrolledArea)[--i];
//STRIP001             for( USHORT j = pScroll->Count(); j; )
//STRIP001          {
//STRIP001              SwStripes* pStripes = (*pScroll)[--j];
//STRIP001              if( pStripes->Count() )
//STRIP001              {
//STRIP001                     SwRect aRect = pScroll->IsVertical() ?
//STRIP001                         SwRect( pStripes->GetY() - pStripes->GetHeight(),
//STRIP001                                 pStripes->GetMin(), pStripes->GetHeight(),
//STRIP001                                 pStripes->GetWidth() ) :
//STRIP001                         SwRect( pStripes->GetMin(), pStripes->GetY(),
//STRIP001                                 pStripes->GetWidth(), pStripes->GetHeight() );
//STRIP001                  if( rRect.IsOver( aRect ) )
//STRIP001                  {
//STRIP001                         for( USHORT nI = pStripes->Count(); nI; )
//STRIP001                      {
//STRIP001                             if( pScroll->IsVertical() )
//STRIP001                             {
//STRIP001                                 long nWidth = (*pStripes)[--nI].GetHeight();
//STRIP001                                 aRect.Left( (*pStripes)[nI].GetY() -nWidth +1 );
//STRIP001                                 aRect.Width( nWidth );
//STRIP001                             }
//STRIP001                             else
//STRIP001                             {
//STRIP001                                 aRect.Top( (*pStripes)[--nI].GetY() );
//STRIP001                                 aRect.Height( (*pStripes)[nI].GetHeight() );
//STRIP001                             }
//STRIP001                          if( rRect.IsOver( aRect ) )
//STRIP001                          {
//STRIP001                              pStripes->Remove( nI );
//STRIP001                              _RefreshScrolledArea( aRect );
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001              if( !pStripes->Count() )
//STRIP001              {
//STRIP001                  pScroll->Remove( j );
//STRIP001                  delete pStripes;
//STRIP001              }
//STRIP001          }
//STRIP001          if( !pScroll->Count() )
//STRIP001          {
//STRIP001              pScrolledArea->Remove( pScroll );
//STRIP001              delete pScroll;
//STRIP001          }
//STRIP001          //Ist da jemand ungeduldig?
//STRIP001          //Nur Mouse und Keyboard, weil wir sonst von jeder billigen
//STRIP001          //Uhr unterbrochen werden.
//STRIP001          if( GetpApp()->AnyInput( INPUT_MOUSEANDKEYBOARD ) )
//STRIP001              break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  //All done?
//STRIP001  if( !pScrolledArea || !pScrolledArea->Count() )
//STRIP001  {
//STRIP001      ResetScrolled();
//STRIP001      SetNextScroll();
//STRIP001      aScrollTimer.Stop();
//STRIP001  }
//STRIP001 }

//STRIP001 SwStripes& SwStripes::Plus( const SwStripes& rOther, BOOL bVert )
//STRIP001 {
//STRIP001  if( !Count() )
//STRIP001  {
//STRIP001      Insert( &rOther, 0 );
//STRIP001      SetMin( rOther.GetMin() );
//STRIP001      SetMax( rOther.GetMax() );
//STRIP001      return *this;
//STRIP001  }
//STRIP001
//STRIP001  long nCnt = rOther.Count();
//STRIP001  if( nCnt )
//STRIP001  {
//STRIP001      ChkMin( rOther.GetMin() );
//STRIP001      ChkMax( rOther.GetMax() );
//STRIP001      USHORT nStart = 0;
//STRIP001         if( bVert )
//STRIP001         for( USHORT nIdx = 0; nIdx < nCnt; ++nIdx )
//STRIP001      {
//STRIP001          const SwStripe& rAdd = rOther[ nIdx ];
//STRIP001             long nBottom = rAdd.GetY() - rAdd.GetHeight();
//STRIP001          USHORT nCount = Count();
//STRIP001          USHORT nY = nStart;
//STRIP001          while( nY < nCount )
//STRIP001          {
//STRIP001              SwStripe& rChk = GetObject( nY );
//STRIP001                 if( rChk.GetY() - rChk.GetHeight() < rAdd.GetY() )
//STRIP001                  break;
//STRIP001              else
//STRIP001                  ++nY;
//STRIP001          }
//STRIP001          USHORT nB = nY;
//STRIP001          while( nB < nCount )
//STRIP001          {
//STRIP001              const SwStripe& rChk = GetObject( nB );
//STRIP001                 if( rChk.GetY() <= nBottom )
//STRIP001                  break;
//STRIP001              else
//STRIP001                  ++nB;
//STRIP001          }
//STRIP001          nStart = nY;
//STRIP001          if( nY == nB )
//STRIP001              Insert( rAdd, nY );
//STRIP001          else
//STRIP001          {
//STRIP001                 long nChkBottom = rAdd.GetY() - rAdd.GetHeight();;
//STRIP001              const SwStripe& rChkB = GetObject( nB - 1 );
//STRIP001                 long nTmp = rChkB.GetY() - rChkB.GetHeight();
//STRIP001                 if( nTmp < nChkBottom )
//STRIP001                  nChkBottom = nTmp;
//STRIP001              SwStripe& rChk = GetObject( nY );
//STRIP001                 if( rAdd.GetY() > rChk.GetY() )
//STRIP001                  rChk.Y() = rAdd.GetY();
//STRIP001                 rChk.Height() = rChk.GetY() - nChkBottom;
//STRIP001              nChkBottom = nB - nY - 1;
//STRIP001              if( nChkBottom )
//STRIP001                     Remove( nY + 1, (USHORT)nChkBottom );
//STRIP001          }
//STRIP001      }
//STRIP001         else
//STRIP001         for( USHORT nIdx = 0; nIdx < nCnt; ++nIdx )
//STRIP001      {
//STRIP001          const SwStripe& rAdd = rOther[ nIdx ];
//STRIP001          long nBottom = rAdd.GetY() + rAdd.GetHeight();
//STRIP001          USHORT nCount = Count();
//STRIP001          USHORT nY = nStart;
//STRIP001          while( nY < nCount )
//STRIP001          {
//STRIP001              SwStripe& rChk = GetObject( nY );
//STRIP001              if( rChk.GetY() + rChk.GetHeight() > rAdd.GetY() )
//STRIP001                  break;
//STRIP001              else
//STRIP001                  ++nY;
//STRIP001          }
//STRIP001          USHORT nB = nY;
//STRIP001          while( nB < nCount )
//STRIP001          {
//STRIP001              const SwStripe& rChk = GetObject( nB );
//STRIP001              if( rChk.GetY() >= nBottom )
//STRIP001                  break;
//STRIP001              else
//STRIP001                  ++nB;
//STRIP001          }
//STRIP001          nStart = nY;
//STRIP001          if( nY == nB )
//STRIP001              Insert( rAdd, nY );
//STRIP001          else
//STRIP001          {
//STRIP001              long nChkBottom = rAdd.GetY() + rAdd.GetHeight();;
//STRIP001              const SwStripe& rChkB = GetObject( nB - 1 );
//STRIP001              long nTmp = rChkB.GetY() + rChkB.GetHeight();
//STRIP001              if( nTmp > nChkBottom )
//STRIP001                  nChkBottom = nTmp;
//STRIP001              SwStripe& rChk = GetObject( nY );
//STRIP001              if( rAdd.GetY() < rChk.GetY() )
//STRIP001                  rChk.Y() = rAdd.GetY();
//STRIP001              rChk.Height() = nChkBottom - rChk.GetY();
//STRIP001              nChkBottom = nB - nY - 1;
//STRIP001              if( nChkBottom )
//STRIP001                     Remove( nY + 1, (USHORT)nChkBottom );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return *this;
//STRIP001 }

//STRIP001 BOOL SwStripes::Recalc( BOOL bVert )
//STRIP001 {
//STRIP001  if( !Count() )
//STRIP001      return TRUE;
//STRIP001  Y() = GetObject(0).GetY();
//STRIP001     if( bVert )
//STRIP001     {
//STRIP001         long nTmpMin = GetObject(0).GetY() - GetObject(0).Height();
//STRIP001         for( USHORT nIdx = 1; nIdx < Count(); )
//STRIP001         {
//STRIP001             const SwStripe& rStr = GetObject(nIdx++);
//STRIP001             if( GetY() < rStr.GetY() )
//STRIP001                 Y() = rStr.GetY();
//STRIP001             if( nTmpMin > rStr.GetY() - rStr.GetHeight() )
//STRIP001                 nTmpMin = rStr.GetY() - rStr.GetHeight();
//STRIP001         }
//STRIP001         Height() = GetY() - nTmpMin;
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         long nTmpMax = GetObject(0).GetY() + GetObject(0).Height();
//STRIP001         for( USHORT nIdx = 1; nIdx < Count(); )
//STRIP001         {
//STRIP001             const SwStripe& rStr = GetObject(nIdx++);
//STRIP001             if( GetY() > rStr.GetY() )
//STRIP001                 Y() = rStr.GetY();
//STRIP001             if( nTmpMax < rStr.GetY() + rStr.GetHeight() )
//STRIP001                 nTmpMax = rStr.GetY() + rStr.GetHeight();
//STRIP001         }
//STRIP001         Height() = nTmpMax - GetY();
//STRIP001     }
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 BOOL SwScrollArea::Compress()
//STRIP001 {
//STRIP001  if( !Count() )
//STRIP001      return TRUE;
//STRIP001     for( USHORT nIdx = Count() - 1; nIdx > 0; --nIdx )
//STRIP001  {
//STRIP001         GetObject(0)->Plus( *GetObject(nIdx), IsVertical() );
//STRIP001      delete GetObject( nIdx );
//STRIP001      Remove( nIdx, 1 );
//STRIP001  }
//STRIP001  ClrOffs();
//STRIP001     return GetObject(0)->Recalc( IsVertical() );
//STRIP001 }

//STRIP001 void SwScrollArea::Add( SwScrollArea *pScroll )
//STRIP001 {
//STRIP001  ASSERT( pScroll->Count() == 1, "Missing scrollarea compression 2" );
//STRIP001  ASSERT( Count() == 1, "Missing scrollarea compression 3" );
//STRIP001     GetObject(0)->Plus( *pScroll->GetObject(0), IsVertical() );
//STRIP001     GetObject(0)->Recalc( IsVertical() );
//STRIP001  delete pScroll->GetObject( 0 );
//STRIP001  pScroll->Remove( (USHORT)0, 1 );
//STRIP001  delete pScroll;
//STRIP001 }

/******************************************************************************
|*
|*  SwScrollAreas::Insert(..)
|*
******************************************************************************/

//STRIP001 void SwScrollAreas::InsertCol( const SwScrollColumn &rCol,
//STRIP001                          SwStripes *pStripes )
//STRIP001 {
//STRIP001  SwScrollArea *pTmp = new SwScrollArea( rCol, pStripes );
//STRIP001  USHORT nIdx;
//STRIP001  if( Seek_Entry( pTmp, &nIdx ) )
//STRIP001  {
//STRIP001      GetObject( nIdx )->SmartInsert( pStripes );
//STRIP001      delete pTmp;
//STRIP001  }
//STRIP001  else
//STRIP001      Insert( pTmp );
//STRIP001 }


//STRIP001 void SwScrollArea::SmartInsert( SwStripes* pStripes )
//STRIP001 {
//STRIP001  ASSERT( pStripes, "Insert empty scrollstripe?" );
//STRIP001  BOOL bNotInserted = TRUE;
//STRIP001     if( IsVertical() )
//STRIP001         for( USHORT nIdx = 0; nIdx < Count() && bNotInserted; )
//STRIP001         {
//STRIP001             SwStripes* pTmp = GetObject( nIdx++ );
//STRIP001             if( pTmp->GetY() - pTmp->GetHeight() == pStripes->GetY() )
//STRIP001             {
//STRIP001                 pTmp->Height() += pStripes->GetHeight();
//STRIP001                 pTmp->ChkMin( pStripes->GetMin() );
//STRIP001                 pTmp->ChkMax( pStripes->GetMax() );
//STRIP001                 if( pStripes->Count() )
//STRIP001                     pTmp->Insert( (SwStripeArr*)pStripes, pTmp->Count(), 0 );
//STRIP001                 bNotInserted = FALSE;
//STRIP001             }
//STRIP001             else if( pTmp->GetY() == pStripes->GetY() - pStripes->GetHeight() )
//STRIP001             {
//STRIP001                 pTmp->Height() += pStripes->GetHeight();
//STRIP001                 pTmp->Y() = pStripes->GetY();
//STRIP001                 pTmp->ChkMin( pStripes->GetMin() );
//STRIP001                 pTmp->ChkMax( pStripes->GetMax() );
//STRIP001                 if( pStripes->Count() )
//STRIP001                     pTmp->Insert( (SwStripeArr*)pStripes, 0, 0 );
//STRIP001                 bNotInserted = FALSE;
//STRIP001             }
//STRIP001         }
//STRIP001     else
//STRIP001     for( USHORT nIdx = 0; nIdx < Count() && bNotInserted; )
//STRIP001  {
//STRIP001      SwStripes* pTmp = GetObject( nIdx++ );
//STRIP001      if( pTmp->GetY() + pTmp->GetHeight() == pStripes->GetY() )
//STRIP001      {
//STRIP001          pTmp->Height() += pStripes->GetHeight();
//STRIP001          pTmp->ChkMin( pStripes->GetMin() );
//STRIP001          pTmp->ChkMax( pStripes->GetMax() );
//STRIP001          if( pStripes->Count() )
//STRIP001              pTmp->Insert( (SwStripeArr*)pStripes, pTmp->Count(), 0 );
//STRIP001          bNotInserted = FALSE;
//STRIP001      }
//STRIP001      else if( pTmp->GetY() == pStripes->GetY() + pStripes->GetHeight() )
//STRIP001      {
//STRIP001          pTmp->Height() += pStripes->GetHeight();
//STRIP001          pTmp->Y() = pStripes->GetY();
//STRIP001          pTmp->ChkMin( pStripes->GetMin() );
//STRIP001          pTmp->ChkMax( pStripes->GetMax() );
//STRIP001          if( pStripes->Count() )
//STRIP001              pTmp->Insert( (SwStripeArr*)pStripes, 0, 0 );
//STRIP001          bNotInserted = FALSE;
//STRIP001      }
//STRIP001  }
//STRIP001  if( !bNotInserted || !Insert( pStripes ) )
//STRIP001      delete pStripes;
//STRIP001 }

