/*************************************************************************
 *
 *  $RCSfile: sw_viewopt.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:54:13 $
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

#ifndef _OFF_APP_HXX //autogen
#include <bf_offmgr/app.hxx>
#endif
#ifndef _SVX_HTMLMODE_HXX //autogen
#include <bf_svx/htmlmode.hxx>
#endif
#ifndef _OFA_HTMLCFG_HXX //autogen
#include <bf_offmgr/htmlcfg.hxx>
#endif
#ifndef _SVX_SVXIDS_HRC //autogen
#include <bf_svx/svxids.hrc>
#endif
#ifndef _SVX_SVXENUM_HXX //autogen
#include <bf_svx/svxenum.hxx>
#endif
#ifndef _MySVXACORR_HXX //autogen
#include <bf_svx/svxacorr.hxx>
#endif
#ifndef _UNOTOOLS_LOCALEDATAWRAPPER_HXX
#include <unotools/localedatawrapper.hxx>
#endif
#ifndef _REGION_HXX //autogen
#include <vcl/region.hxx>
#endif
#ifndef _OUTDEV_HXX //autogen
#include <vcl/outdev.hxx>
#endif
#ifndef _WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif
#ifndef _SWMODULE_HXX //autogen
#include <swmodule.hxx>
#endif
#ifndef _SWTYPES_HXX
#include <swtypes.hxx>
#endif
#ifndef _VIEWOPT_HXX
#include <viewopt.hxx>
#endif
#ifndef _WDOCSH_HXX
#include <wdocsh.hxx>
#endif
#ifndef _SWRECT_HXX
#include <swrect.hxx>
#endif
#ifndef _CRSTATE_HXX
#include <crstate.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_COLORCFG_HXX
#include <svtools/colorcfg.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_ACCESSIBILITYOPTIONS_HXX
#include <svtools/accessibilityoptions.hxx>
#endif
namespace binfilter {


/*N*/ #ifndef PRODUCT
/*N*/ BOOL   SwViewOption::bTest9 = FALSE;      //DrawingLayerNotLoading
/*N*/ #endif
/*N*/ Color SwViewOption::aDocBoundColor(COL_LIGHTGRAY);
/*N*/ Color SwViewOption::aObjectBoundColor(COL_LIGHTGRAY);
/*N*/ Color SwViewOption::aDocColor(COL_LIGHTGRAY);
/*N*/ Color SwViewOption::aAppBackgroundColor(COL_LIGHTGRAY);
/*N*/ Color SwViewOption::aTableBoundColor(COL_LIGHTGRAY);
/*N*/ Color SwViewOption::aIndexShadingsColor(COL_LIGHTGRAY);
/*N*/ Color SwViewOption::aLinksColor(COL_BLUE);
/*N*/ Color SwViewOption::aVisitedLinksColor(COL_RED);
/*N*/ Color SwViewOption::aDirectCursorColor(COL_BLUE);
/*N*/ Color SwViewOption::aTextGridColor(COL_LIGHTGRAY);
/*N*/ Color SwViewOption::aSpellColor(COL_LIGHTRED);
/*N*/ Color SwViewOption::aFontColor(COL_BLACK);
/*N*/ Color SwViewOption::aFieldShadingsColor(COL_LIGHTGRAY);
/*N*/ Color SwViewOption::aSectionBoundColor(COL_LIGHTGRAY);
/*M*/ Color SwViewOption::aPageBreakColor(COL_BLUE);
/*N*/ Color SwViewOption::aNotesIndicatorColor(COL_YELLOW);
/*N*/ Color SwViewOption::aScriptIndicatorColor(COL_GREEN);
/*N*/
/*N*/ sal_Int32 SwViewOption::nAppearanceFlags = VIEWOPT_DOC_BOUNDARIES|VIEWOPT_OBJECT_BOUNDARIES;
/*N*/ USHORT SwViewOption::nPixelTwips = 0;   //ein Pixel auf dem Bildschirm
/*N*/

#define LINEBREAK_SIZE 12, 8
#define TAB_SIZE 12, 6

#define MIN_BLANKWIDTH       40
#define MIN_BLANKHEIGHT      40
#define MIN_TABWIDTH        120
#define MIN_TABHEIGHT       200

static const char __FAR_DATA aPostItStr[] = "  ";

/*************************************************************************
 *                    SwViewOption::IsEqualFlags()
 *************************************************************************/

//STRIP001 BOOL SwViewOption::IsEqualFlags( const SwViewOption &rOpt ) const
//STRIP001 {
//STRIP001  return  nCoreOptions == rOpt.nCoreOptions
//STRIP001          && nCore2Options == rOpt.nCore2Options
//STRIP001          && aSnapSize    == rOpt.aSnapSize
//STRIP001          && nDivisionX   == rOpt.GetDivisionX()
//STRIP001          && nDivisionY   == rOpt.GetDivisionY()
//STRIP001          && nPagePrevRow == rOpt.GetPagePrevRow()
//STRIP001          && nPagePrevCol == rOpt.GetPagePrevCol()
//STRIP001          && aRetoucheColor == rOpt.GetRetoucheColor()
//STRIP001 #ifndef PRODUCT
//STRIP001          // korrespondieren zu den Angaben in ui/config/cfgvw.src
//STRIP001          && bTest1 == rOpt.IsTest1()
//STRIP001          && bTest2 == rOpt.IsTest2()
//STRIP001          && bTest3 == rOpt.IsTest3()
//STRIP001          && bTest4 == rOpt.IsTest4()
//STRIP001          && bTest5 == rOpt.IsTest5()
//STRIP001          && bTest6 == rOpt.IsTest6()
//STRIP001          && bTest7 == rOpt.IsTest7()
//STRIP001          && bTest8 == rOpt.IsTest8()
//STRIP001          && bTest10 == rOpt.IsTest10()
//STRIP001 #endif
//STRIP001          ;
//STRIP001 }

/*************************************************************************
 *                    class SwPxlToTwips
 *************************************************************************/

//STRIP001 class SwPxlToTwips
//STRIP001 {
//STRIP001  OutputDevice *pOut;
//STRIP001  Color   aLineColor;
//STRIP001  BOOL   bClip;
//STRIP001  Region aClip;
//STRIP001  Point aStart;
//STRIP001  SwRect aRect;
//STRIP001 public:
//STRIP001  SwPxlToTwips( OutputDevice *pOut, const SwRect &rRect, const Size &rSize );
//STRIP001  ~SwPxlToTwips();
//STRIP001  inline const Point &GetStartPoint() const { return aStart; }
//STRIP001  inline BOOL  IsTooSmall() const {return 0 == pOut;}
//STRIP001  inline const SwRect &GetRect() const { return aRect; }
//STRIP001  void DrawLine( const Point &rStart, const Point &rEnd );
//STRIP001 };

/*************************************************************************
 *                    SwPxlToTwips::CTOR
 *************************************************************************/

//STRIP001 SwPxlToTwips::SwPxlToTwips( OutputDevice *pOutDev,
//STRIP001                          const SwRect &rRect, const Size &rSize )
//STRIP001  : pOut( pOutDev )
//STRIP001 {
//STRIP001  aRect = pOut->LogicToPixel( rRect.SVRect() );
//STRIP001
//STRIP001  // Wenn der Tab nicht mehr darstellbar ist, geben wir auf.
//STRIP001  if( 3 > aRect.Width() )
//STRIP001  {
//STRIP001      pOut = NULL;
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  if( rSize.Height() - 1 > aRect.Height() )
//STRIP001  {
//STRIP001      pOut = NULL;
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  aStart = aRect.Pos();
//STRIP001  aStart.X() += (aRect.Width()  / 2) - (rSize.Width() / 2);
//STRIP001  aStart.Y() += (aRect.Height() / 2) - (rSize.Height() / 2);
//STRIP001  if ( aStart.X() < aRect.Left() )
//STRIP001      aStart.X() = aRect.Left();
//STRIP001
//STRIP001  if ( pOut->GetConnectMetaFile() )
//STRIP001      pOut->Push();
//STRIP001
//STRIP001  bClip = pOut->IsClipRegion();
//STRIP001  if ( bClip )
//STRIP001  {
//STRIP001      aClip = pOut->GetClipRegion();
//STRIP001      pOut->SetClipRegion();
//STRIP001  }
//STRIP001
//STRIP001  aLineColor = pOut->GetLineColor( );
//STRIP001  pOut->SetLineColor( Color(COL_BLACK) );
//STRIP001 }

/*************************************************************************
 *                    SwPxlToTwips::DTOR
 *************************************************************************/

//STRIP001 SwPxlToTwips::~SwPxlToTwips()
//STRIP001 {
//STRIP001  if( pOut )
//STRIP001  {
//STRIP001      if ( pOut->GetConnectMetaFile() )
//STRIP001          pOut->Pop();
//STRIP001      else
//STRIP001      {
//STRIP001          pOut->SetLineColor( aLineColor );
//STRIP001          if( bClip )
//STRIP001              pOut->SetClipRegion( aClip );
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
 *                    SwPxlToTwips::DrawLine
 *************************************************************************/

//STRIP001 void SwPxlToTwips::DrawLine( const Point &rStart, const Point &rEnd )
//STRIP001 {
//STRIP001  if( pOut )
//STRIP001  {
//STRIP001      const Point aStart( pOut->PixelToLogic( rStart ) );
//STRIP001      const Point aEnd( pOut->PixelToLogic( rEnd ) );
//STRIP001      pOut->DrawLine( aStart, aEnd );
//STRIP001  }
//STRIP001 }

/*************************************************************************
 *                    SwViewOption::DrawRect()
 *************************************************************************/

//STRIP001 void SwViewOption::DrawRect( OutputDevice *pOut,
//STRIP001                           const SwRect &rRect, long nCol ) const
//STRIP001 {
//STRIP001  if ( pOut->GetOutDevType() != OUTDEV_PRINTER )
//STRIP001  {
//STRIP001      const Color aCol( nCol );
//STRIP001      const Color aOldColor( pOut->GetFillColor() );
//STRIP001      pOut->SetFillColor( aCol );
//STRIP001      pOut->DrawRect( rRect.SVRect() );
//STRIP001      pOut->SetFillColor( aOldColor );
//STRIP001  }
//STRIP001  else
//STRIP001      DrawRectPrinter( pOut, rRect );
//STRIP001 }

/*************************************************************************
 *                    SwViewOption::DrawRectPrinter()
 *************************************************************************/

//STRIP001 void SwViewOption::DrawRectPrinter( OutputDevice *pOut,
//STRIP001                                  const SwRect &rRect ) const
//STRIP001 {
//STRIP001  Color aOldColor(pOut->GetLineColor());
//STRIP001  Color aOldFillColor( pOut->GetFillColor() );
//STRIP001  pOut->SetLineColor( Color(COL_BLACK) );
//STRIP001  pOut->SetFillColor( Color(COL_TRANSPARENT ));
//STRIP001  pOut->DrawRect( rRect.SVRect() );
//STRIP001  pOut->SetFillColor( aOldFillColor );
//STRIP001  pOut->SetLineColor( aOldColor );
//STRIP001 }

/*************************************************************************
 *                    SwViewOption::PaintTab()
 *************************************************************************/
//STRIP001 #ifdef VERTICAL_LAYOUT
//STRIP001 #else
//STRIP001 void SwViewOption::PaintTab( OutputDevice *pOut, const SwRect &rRect ) const
//STRIP001 {
//STRIP001  SwPxlToTwips aSave( pOut, rRect, Size( TAB_SIZE ) );
//STRIP001
//STRIP001  if( aSave.IsTooSmall() )
//STRIP001      return;
//STRIP001
//STRIP001  Point aStart( aSave.GetStartPoint() );
//STRIP001  const SwRect &rPaintRect = aSave.GetRect();
//STRIP001
//STRIP001  // horizontale
//STRIP001  aStart.Y() += 2;
//STRIP001  aStart.X() += 1;
//STRIP001  Point aEnd( aStart );
//STRIP001  aEnd.X() += 10;
//STRIP001  if( aEnd.X() >= rPaintRect.Right() )
//STRIP001      aEnd.X() = rPaintRect.Right() - 1;
//STRIP001  long nDiff = aEnd.X() - aStart.X();
//STRIP001  aSave.DrawLine( aStart, aEnd );
//STRIP001
//STRIP001  // Pfeil
//STRIP001  aEnd.X() -= 1;
//STRIP001  aStart.X() = aEnd.X();
//STRIP001  aStart.Y() -= 1;
//STRIP001  aEnd.Y() += 1;
//STRIP001  aSave.DrawLine( aStart, aEnd );
//STRIP001
//STRIP001  if( nDiff > 1 && rPaintRect.Height() > 8 )
//STRIP001  {
//STRIP001      aStart.X() -= 1;
//STRIP001      aStart.Y() -= 1;
//STRIP001      aEnd.X() = aStart.X();
//STRIP001      aEnd.Y() += 1;
//STRIP001      aSave.DrawLine( aStart, aEnd );
//STRIP001      if( nDiff > 2 && rPaintRect.Height() > 12 )
//STRIP001      {
//STRIP001          aStart.X() -= 1;
//STRIP001          aEnd.X() -= 1;
//STRIP001          aSave.DrawLine( aStart, aEnd );
//STRIP001      }
//STRIP001  }
//STRIP001 }
//STRIP001 #endif
/*************************************************************************
 *                    SwViewOption::GetLineBreakWidth()
 *************************************************************************/

//STRIP001 USHORT SwViewOption::GetLineBreakWidth( const OutputDevice *pOut ) const
//STRIP001 {
//STRIP001  ASSERT( pOut, "no Outdev" );
//STRIP001  const Size aSz( LINEBREAK_SIZE );
//STRIP001  return USHORT(pOut->PixelToLogic( aSz ).Width());
//STRIP001 }

/*************************************************************************
 *                    SwViewOption::PaintLineBreak()
 *************************************************************************/
//STRIP001 #ifdef VERTICAL_LAYOUT
//STRIP001 #else
//STRIP001 void SwViewOption::PaintLineBreak( OutputDevice *pOut, const SwRect &rRect ) const
//STRIP001 {
//STRIP001  const Size aSz( LINEBREAK_SIZE );
//STRIP001  SwPxlToTwips aSave( pOut, rRect, aSz );
//STRIP001  if( aSave.IsTooSmall() )
//STRIP001      return;
//STRIP001  Point aStart( aSave.GetStartPoint() );
//STRIP001  const SwRect &rPaintRect = aSave.GetRect();
//STRIP001
//STRIP001  // horizontale
//STRIP001  aStart.Y() += 4;
//STRIP001  aStart.X() += 1;
//STRIP001  Point aEnd( aStart );
//STRIP001  aEnd.X() += 8;
//STRIP001  if( aEnd.X() >= rPaintRect.Right() - 1 )
//STRIP001      aEnd.X() = rPaintRect.Right() - 2;
//STRIP001  aSave.DrawLine( aStart, aEnd );
//STRIP001
//STRIP001  // Pfeil
//STRIP001  aStart.Y() -= 1;
//STRIP001  aStart.X() += 1;
//STRIP001  aEnd.Y()   = aStart.Y() + 2;
//STRIP001  aEnd.X()   = aStart.X();
//STRIP001  aSave.DrawLine( aStart, aEnd );
//STRIP001
//STRIP001  // Pfeil
//STRIP001  aStart.Y() -= 1;
//STRIP001  aStart.X() += 1;
//STRIP001  aEnd.Y()   += 1;
//STRIP001  aEnd.X()   += 1;
//STRIP001  aSave.DrawLine( aStart, aEnd );
//STRIP001
//STRIP001  // Pfeil
//STRIP001  aStart.X() += 1;
//STRIP001  aEnd.X()   += 1;
//STRIP001  aSave.DrawLine( aStart, aEnd );
//STRIP001
//STRIP001  // vertikale
//STRIP001  aStart.Y() -= 2;
//STRIP001  aStart.X() += 6;
//STRIP001  if( aStart.X() >= rPaintRect.Right() )
//STRIP001      aStart.X() = rPaintRect.Right() - 1;
//STRIP001  aEnd.X() = aStart.X();
//STRIP001  aEnd.Y() = aStart.Y() + 3;
//STRIP001  aSave.DrawLine( aStart, aEnd );
//STRIP001 }
//STRIP001 #endif
/*************************************************************************
 *                    SwViewOption::GetPostItsWidth()
 *************************************************************************/

//STRIP001 USHORT SwViewOption::GetPostItsWidth( const OutputDevice *pOut ) const
//STRIP001 {
//STRIP001  ASSERT( pOut, "no Outdev" );
//STRIP001  return USHORT(pOut->GetTextWidth( String::CreateFromAscii(aPostItStr )));
//STRIP001 }

/*************************************************************************
 *                    SwViewOption::PaintPostIts()
 *************************************************************************/

//STRIP001 void SwViewOption::PaintPostIts( OutputDevice *pOut, const SwRect &rRect,
//STRIP001                                  sal_Bool bIsScript ) const
//STRIP001 {
//STRIP001  if( pOut )
//STRIP001  {
//STRIP001         Color aOldLineColor( pOut->GetLineColor() );
//STRIP001      pOut->SetLineColor( Color(COL_GRAY ) );
//STRIP001      // Wir ziehen ueberall zwei Pixel ab, damit es schick aussieht
//STRIP001      USHORT nPix = GetPixelTwips() * 2;
//STRIP001      if( rRect.Width() <= 2 * nPix || rRect.Height() <= 2 * nPix )
//STRIP001          nPix = 0;
//STRIP001      const Point aTopLeft(  rRect.Left()  + nPix, rRect.Top()    + nPix );
//STRIP001      const Point aBotRight( rRect.Right() - nPix, rRect.Bottom() - nPix );
//STRIP001      const SwRect aRect( aTopLeft, aBotRight );
//STRIP001         sal_Int32 nColor = bIsScript ? aScriptIndicatorColor.GetColor() : aNotesIndicatorColor.GetColor();
//STRIP001         DrawRect( pOut, aRect, nColor );
//STRIP001      pOut->SetLineColor( aOldLineColor );
//STRIP001  }
//STRIP001 }


/*************************************************************************
|*
|*  ViewOption::ViewOption()
|*
|*  Letzte Aenderung    MA 04. Aug. 93
|*
|*************************************************************************/

/*M*/ SwViewOption::SwViewOption() :
/*M*/   nZoom( 100 ),
/*M*/   nPagePrevRow( 1 ),
/*M*/   nPagePrevCol( 2 ),
/*M*/   eZoom( 0 ),
/*M*/   nTblDest(TBL_DEST_CELL),
/*M*/   bReadonly(FALSE),
/*M*/     bSelectionInReadonly(FALSE),
/*M*/   aRetoucheColor( COL_TRANSPARENT ),
/*M*/   nShdwCrsrFillMode( FILL_TAB ),
/*M*/     bStarOneSetting(FALSE),
/*M*/     bIsPagePreview(FALSE)
/*M*/ {
/*M*/   // Initialisierung ist jetzt etwas einfacher
/*M*/   // alle Bits auf 0
/*M*/   nCoreOptions =  VIEWOPT_1_IDLE | VIEWOPT_1_HARDBLANK | VIEWOPT_1_SOFTHYPH |
/*M*/                     VIEWOPT_1_REF |
/*M*/                     VIEWOPT_1_GRAPHIC |
/*M*/                   VIEWOPT_1_TABLE    | VIEWOPT_1_DRAW | VIEWOPT_1_CONTROL |
/*M*/                     VIEWOPT_1_PAGEBACK |
/*M*/                   VIEWOPT_1_SOLIDMARKHDL | VIEWOPT_1_POSTITS;
/*M*/     nCore2Options = VIEWOPT_CORE2_BLACKFONT | VIEWOPT_CORE2_HIDDENPARA;
/*M*/     nUIOptions    = VIEWOPT_2_MODIFIED | VIEWOPT_2_EXECHYPERLINKS | VIEWOPT_2_GRFKEEPZOOM |VIEWOPT_2_ANY_RULER;
/*M*/
/*M*/   if(MEASURE_METRIC != GetAppLocaleData().getMeasurementSystemEnum())
/*M*/       aSnapSize.Width() = aSnapSize.Height() = 720;   // 1/2"
/*M*/   else
/*M*/       aSnapSize.Width() = aSnapSize.Height() = 567;   // 1 cm
/*M*/   nDivisionX = nDivisionY = 1;
/*M*/
/*M*/     bSelectionInReadonly = SW_MOD()->GetAccessibilityOptions().IsSelectionInReadonly();
/*M*/
/*M*/ #ifndef PRODUCT
/*M*/   // korrespondieren zu den Angaben in ui/config/cfgvw.src
/*M*/   bTest1 = bTest2 = bTest3 = bTest4 =
/*M*/            bTest5 = bTest6 = bTest7 = bTest8 = bTest10 = FALSE;
/*M*/ #endif
/*M*/ }


/*N*/ SwViewOption::SwViewOption(const SwViewOption& rVOpt)
/*N*/ {
/*N*/   bReadonly = FALSE;
/*M*/     bSelectionInReadonly = FALSE;
/*N*/   nZoom           = rVOpt.nZoom       ;
/*N*/   aSnapSize       = rVOpt.aSnapSize   ;
/*N*/   nDivisionX      = rVOpt.nDivisionX  ;
/*N*/   nDivisionY      = rVOpt.nDivisionY  ;
/*N*/   nPagePrevRow    = rVOpt.nPagePrevRow;
/*N*/   nPagePrevCol    = rVOpt.nPagePrevCol;
/*N*/     bIsPagePreview  = rVOpt.bIsPagePreview;
/*N*/   eZoom           = rVOpt.eZoom       ;
/*N*/   nTblDest        = rVOpt.nTblDest    ;
/*N*/   nUIOptions      = rVOpt.nUIOptions  ;
/*N*/   nCoreOptions    = rVOpt.nCoreOptions  ;
/*N*/   nCore2Options   = rVOpt.nCore2Options  ;
/*N*/   aRetoucheColor  = rVOpt.GetRetoucheColor();
/*N*/   sSymbolFont     = rVOpt.sSymbolFont;
/*N*/   nShdwCrsrFillMode = rVOpt.nShdwCrsrFillMode;
/*N*/   bStarOneSetting = rVOpt.bStarOneSetting;
/*N*/
/*N*/ #ifndef PRODUCT
/*N*/   bTest1          = rVOpt.bTest1      ;
/*N*/   bTest2          = rVOpt.bTest2      ;
/*N*/   bTest3          = rVOpt.bTest3      ;
/*N*/   bTest4          = rVOpt.bTest4      ;
/*N*/   bTest5          = rVOpt.bTest5      ;
/*N*/   bTest6          = rVOpt.bTest6      ;
/*N*/   bTest7          = rVOpt.bTest7      ;
/*N*/   bTest8          = rVOpt.bTest8      ;
/*N*/   bTest10         = rVOpt.bTest10     ;
/*N*/ #endif
/*N*/ }


/*N*/ SwViewOption& SwViewOption::operator=( const SwViewOption &rVOpt )
/*N*/ {
/*N*/   nZoom           = rVOpt.nZoom       ;
/*N*/   aSnapSize       = rVOpt.aSnapSize   ;
/*N*/   nDivisionX      = rVOpt.nDivisionX  ;
/*N*/   nDivisionY      = rVOpt.nDivisionY  ;
/*N*/   nPagePrevRow    = rVOpt.nPagePrevRow;
/*N*/   nPagePrevCol    = rVOpt.nPagePrevCol;
/*N*/     bIsPagePreview  = rVOpt.bIsPagePreview;
/*N*/   eZoom           = rVOpt.eZoom       ;
/*N*/   nTblDest        = rVOpt.nTblDest    ;
/*N*/   nUIOptions      = rVOpt.nUIOptions  ;
/*N*/   nCoreOptions    = rVOpt.nCoreOptions;
/*N*/   nCore2Options   = rVOpt.nCore2Options;
/*N*/   aRetoucheColor  = rVOpt.GetRetoucheColor();
/*N*/   sSymbolFont     = rVOpt.sSymbolFont;
/*N*/   nShdwCrsrFillMode = rVOpt.nShdwCrsrFillMode;
/*N*/   bStarOneSetting = rVOpt.bStarOneSetting;
/*N*/
/*N*/ #ifndef PRODUCT
/*N*/   bTest1          = rVOpt.bTest1      ;
/*N*/   bTest2          = rVOpt.bTest2      ;
/*N*/   bTest3          = rVOpt.bTest3      ;
/*N*/   bTest4          = rVOpt.bTest4      ;
/*N*/   bTest5          = rVOpt.bTest5      ;
/*N*/   bTest6          = rVOpt.bTest6      ;
/*N*/   bTest7          = rVOpt.bTest7      ;
/*N*/   bTest8          = rVOpt.bTest8      ;
/*N*/   bTest10         = rVOpt.bTest10     ;
/*N*/ #endif
/*N*/   return *this;
/*N*/ }


/*N*/ SwViewOption::~SwViewOption()
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|*  ViewOption::Init()
|*
|*  Letzte Aenderung    MA 04. Aug. 93
|*
|*************************************************************************/

/*N*/ void SwViewOption::Init( Window *pWin )
/*N*/ {
/*N*/   if( !nPixelTwips && pWin )
/*N*/   {
/*N*/       nPixelTwips = (USHORT)pWin->PixelToLogic( Size(1,1) ).Height();
/*N*/   }
/*N*/ }

/*N*/ BOOL SwViewOption::IsAutoCompleteWords() const
/*N*/ {
/*N*/   const SvxSwAutoFmtFlags& rFlags = OFF_APP()->GetAutoCorrect()->GetSwFlags();
/*N*/   return /*rFlags.bAutoCompleteWords &&*/ rFlags.bAutoCmpltCollectWords;
/*N*/ }

/*************************************************************************/
/*
/*************************************************************************/

/*N*/ AuthorCharAttr::AuthorCharAttr() :
/*N*/   nItemId (SID_ATTR_CHAR_UNDERLINE),
/*N*/   nAttr   (UNDERLINE_SINGLE),
/*N*/   nColor  (COL_TRANSPARENT)
/*N*/ {
/*N*/ }

/*-----------------07.01.97 13.50-------------------

--------------------------------------------------*/

/*N*/ USHORT        GetHtmlMode(const SwDocShell* pShell)
/*N*/ {
/*N*/   USHORT nRet = 0;
/*N*/   if(!pShell || PTR_CAST(SwWebDocShell, pShell))
/*N*/   {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/        nRet = HTMLMODE_ON;
//STRIP001 /*?*/        OfaHtmlOptions* pHtmlOpt = OFF_APP()->GetHtmlOptions();
//STRIP001 /*?*/        switch ( pHtmlOpt->GetExportMode() )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            case HTML_CFG_MSIE_40:
//STRIP001 /*?*/                nRet |= HTMLMODE_PARA_BORDER|HTMLMODE_SMALL_CAPS|
//STRIP001 /*?*/                        HTMLMODE_SOME_STYLES|
//STRIP001 /*?*/                        HTMLMODE_FULL_STYLES|HTMLMODE_GRAPH_POS|
//STRIP001 /*?*/                        HTMLMODE_FULL_ABS_POS|HTMLMODE_SOME_ABS_POS;
//STRIP001 /*?*/            break;
//STRIP001 /*?*/            case HTML_CFG_NS40:
//STRIP001 /*?*/                nRet |= HTMLMODE_PARA_BORDER|HTMLMODE_SOME_STYLES|
//STRIP001 /*?*/                        HTMLMODE_FRM_COLUMNS|HTMLMODE_BLINK|HTMLMODE_GRAPH_POS|
//STRIP001 /*?*/                        HTMLMODE_SOME_ABS_POS;
//STRIP001 /*?*/            break;
//STRIP001 /*?*/            case HTML_CFG_WRITER:
//STRIP001 /*?*/                nRet |= HTMLMODE_PARA_BORDER|HTMLMODE_SMALL_CAPS|
//STRIP001 /*?*/                        HTMLMODE_SOME_STYLES|
//STRIP001 /*?*/                        HTMLMODE_FRM_COLUMNS|HTMLMODE_FULL_STYLES|
//STRIP001 /*?*/                        HTMLMODE_BLINK|HTMLMODE_DROPCAPS|HTMLMODE_GRAPH_POS|
//STRIP001 /*?*/                        HTMLMODE_FULL_ABS_POS|HTMLMODE_SOME_ABS_POS;
//STRIP001 /*?*/            break;
//STRIP001 /*?*/            case HTML_CFG_HTML32:
//STRIP001 /*?*/            break;
//STRIP001 /*?*/        }
/*N*/   }
/*N*/   return nRet;
/*N*/ }
/* -----------------------------24.04.2002 10:20------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 Color&   SwViewOption::GetDocColor()
//STRIP001 {
//STRIP001     return aDocColor;
//STRIP001 }
/* -----------------------------23.04.2002 17:18------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 Color&   SwViewOption::GetDocBoundariesColor()
//STRIP001 {
//STRIP001     return aDocBoundColor;
//STRIP001 }
/* -----------------------------23.04.2002 17:53------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 Color&   SwViewOption::GetObjectBoundariesColor()
//STRIP001 {
//STRIP001     return aObjectBoundColor;
//STRIP001 }
/* -----------------------------24.04.2002 10:41------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 Color& SwViewOption::GetAppBackgroundColor()
//STRIP001 {
//STRIP001     return aAppBackgroundColor;
//STRIP001 }
/*-- 24.04.2002 10:50:11---------------------------------------------------

  -----------------------------------------------------------------------*/
//STRIP001 Color&   SwViewOption::GetTableBoundariesColor()
//STRIP001 {
//STRIP001     return aTableBoundColor;
//STRIP001 }
/*-- 24.04.2002 10:50:12---------------------------------------------------

  -----------------------------------------------------------------------*/
//STRIP001 Color&   SwViewOption::GetIndexShadingsColor()
//STRIP001 {
//STRIP001     return aIndexShadingsColor;
//STRIP001 }
/*-- 24.04.2002 10:50:12---------------------------------------------------

  -----------------------------------------------------------------------*/
//STRIP001 Color&   SwViewOption::GetLinksColor()
//STRIP001 {
//STRIP001     return aLinksColor;
//STRIP001 }
/*-- 24.04.2002 10:50:13---------------------------------------------------

  -----------------------------------------------------------------------*/
//STRIP001 Color&   SwViewOption::GetVisitedLinksColor()
//STRIP001 {
//STRIP001     return aVisitedLinksColor;
//STRIP001 }
/*-- 24.04.2002 10:50:13---------------------------------------------------

  -----------------------------------------------------------------------*/
//STRIP001 Color&   SwViewOption::GetDirectCursorColor()
//STRIP001 {
//STRIP001     return aDirectCursorColor;
//STRIP001 }
/*-- 24.04.2002 10:50:14---------------------------------------------------

  -----------------------------------------------------------------------*/
//STRIP001 Color&   SwViewOption::GetTextGridColor()
//STRIP001 {
//STRIP001     return aTextGridColor;
//STRIP001 }
/*-- 24.04.2002 10:50:14---------------------------------------------------

  -----------------------------------------------------------------------*/
//STRIP001 Color&   SwViewOption::GetSpellColor()
//STRIP001 {
//STRIP001     return aSpellColor;
//STRIP001 }
/*-- 06.12.2002 10:50:11---------------------------------------------------

  -----------------------------------------------------------------------*/
//STRIP001 Color&   SwViewOption::GetFontColor()
//STRIP001 {
//STRIP001     return aFontColor;
//STRIP001 }
/*-- 24.04.2002 10:50:15---------------------------------------------------

  -----------------------------------------------------------------------*/
//STRIP001 Color&   SwViewOption::GetFieldShadingsColor()
//STRIP001 {
//STRIP001     return aFieldShadingsColor;
//STRIP001 }
/*-- 24.04.2002 10:50:15---------------------------------------------------

  -----------------------------------------------------------------------*/
//STRIP001 Color&   SwViewOption::GetSectionBoundColor()
//STRIP001 {
//STRIP001     return aSectionBoundColor;
//STRIP001 }
/* -----------------------------2002/07/31 14:00------------------------------

 ---------------------------------------------------------------------------*/
/*M*/ Color& SwViewOption::GetPageBreakColor()
/*M*/ {
/*M*/     return aPageBreakColor;
/*M*/ }
/*-- 24.04.2002 10:50:15---------------------------------------------------

  -----------------------------------------------------------------------*/
//STRIP001 Color&   SwViewOption::GetNotesIndicatorColor()
//STRIP001 {
//STRIP001     return aNotesIndicatorColor;
//STRIP001 }
/*-- 24.04.2002 10:50:15---------------------------------------------------

  -----------------------------------------------------------------------*/
//STRIP001 Color&   SwViewOption::GetScriptIndicatorColor()
//STRIP001 {
//STRIP001     return aScriptIndicatorColor;
//STRIP001 }
/* -----------------------------23.04.2002 17:41------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ void SwViewOption::ApplyColorConfigValues(const svtools::ColorConfig& rConfig )
/*N*/ {
/*N*/     aDocColor.SetColor(rConfig.GetColorValue(svtools::DOCCOLOR).nColor);
/*N*/
/*N*/     svtools::ColorConfigValue aValue = rConfig.GetColorValue(svtools::DOCBOUNDARIES);
/*N*/     aDocBoundColor.SetColor(aValue.nColor);
/*N*/     nAppearanceFlags = 0;
/*N*/     if(aValue.bIsVisible)
/*N*/         nAppearanceFlags |= VIEWOPT_DOC_BOUNDARIES;
/*N*/
/*N*/     aAppBackgroundColor.SetColor(rConfig.GetColorValue(svtools::APPBACKGROUND).nColor);
/*N*/
/*N*/     aValue = rConfig.GetColorValue(svtools::OBJECTBOUNDARIES);
/*N*/     aObjectBoundColor.SetColor(aValue.nColor);
/*N*/     if(aValue.bIsVisible)
/*N*/         nAppearanceFlags |= VIEWOPT_OBJECT_BOUNDARIES;
/*N*/
/*N*/     aValue = rConfig.GetColorValue(svtools::TABLEBOUNDARIES);
/*N*/     aTableBoundColor.SetColor(aValue.nColor);
/*N*/     if(aValue.bIsVisible)
/*N*/         nAppearanceFlags |= VIEWOPT_TABLE_BOUNDARIES;
/*N*/
/*N*/     aValue = rConfig.GetColorValue(svtools::WRITERIDXSHADINGS);
/*N*/     aIndexShadingsColor.SetColor(aValue.nColor);
/*N*/     if(aValue.bIsVisible)
/*N*/         nAppearanceFlags |= VIEWOPT_INDEX_SHADINGS;
/*N*/
/*N*/     aValue = rConfig.GetColorValue(svtools::LINKS);
/*N*/     aLinksColor.SetColor(aValue.nColor);
/*N*/     if(aValue.bIsVisible)
/*N*/         nAppearanceFlags |= VIEWOPT_LINKS;
/*N*/
/*N*/     aValue = rConfig.GetColorValue(svtools::LINKSVISITED);
/*N*/     aVisitedLinksColor.SetColor(aValue.nColor);
/*N*/     if(aValue.bIsVisible)
/*N*/         nAppearanceFlags |= VIEWOPT_VISITED_LINKS;
/*N*/
/*N*/     aDirectCursorColor.SetColor(rConfig.GetColorValue(svtools::WRITERDIRECTCURSOR).nColor);
/*N*/
/*N*/     aTextGridColor.SetColor(rConfig.GetColorValue(svtools::WRITERTEXTGRID).nColor);
/*N*/
/*N*/     aSpellColor.SetColor(rConfig.GetColorValue(svtools::SPELL).nColor);
/*N*/
/*N*/     aFontColor.SetColor(rConfig.GetColorValue(svtools::FONTCOLOR).nColor);
/*N*/
/*N*/     aValue = rConfig.GetColorValue(svtools::WRITERFIELDSHADINGS);
/*N*/     aFieldShadingsColor.SetColor(aValue.nColor);
/*N*/     if(aValue.bIsVisible)
/*N*/         nAppearanceFlags |= VIEWOPT_FIELD_SHADINGS;
/*N*/
/*N*/     aValue = rConfig.GetColorValue(svtools::WRITERSECTIONBOUNDARIES);
/*N*/     aSectionBoundColor.SetColor(aValue.nColor);
/*N*/     if(aValue.bIsVisible)
/*N*/         nAppearanceFlags |= VIEWOPT_SECTION_BOUNDARIES;
/*N*/
/*N*/     aValue = rConfig.GetColorValue(svtools::WRITERPAGEBREAKS);
/*N*/     aPageBreakColor.SetColor(aValue.nColor);
/*N*/
/*N*/     aNotesIndicatorColor.SetColor(rConfig.GetColorValue(svtools::WRITERNOTESINDICATOR).nColor);
/*N*/     aScriptIndicatorColor.SetColor(rConfig.GetColorValue(svtools::WRITERSCRIPTINDICATOR).nColor);
/*N*/ }
/* -----------------------------23.04.2002 17:48------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ void SwViewOption::SetAppearanceFlag(sal_Int32 nFlag, BOOL bSet, BOOL bSaveInConfig )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/     if(bSet)
//STRIP001 /*?*/         nAppearanceFlags |= nFlag;
//STRIP001 /*?*/     else
//STRIP001 /*?*/         nAppearanceFlags &= ~nFlag;
//STRIP001 /*?*/     if(bSaveInConfig)
//STRIP001 /*?*/     {
//STRIP001 /*?*/         //create an editable svtools::ColorConfig and store the change
//STRIP001 /*?*/         svtools::EditableColorConfig aEditableConfig;
//STRIP001 /*?*/         struct FlagToConfig_Impl
//STRIP001 /*?*/         {
//STRIP001 /*?*/             sal_Int32               nFlag;
//STRIP001 /*?*/             svtools::ColorConfigEntry   eEntry;
//STRIP001 /*?*/         };
//STRIP001 /*?*/         static const FlagToConfig_Impl aFlags[] =
//STRIP001 /*?*/         {
//STRIP001 /*?*/             VIEWOPT_DOC_BOUNDARIES     ,   svtools::DOCBOUNDARIES     ,
//STRIP001 /*?*/             VIEWOPT_OBJECT_BOUNDARIES  ,   svtools::OBJECTBOUNDARIES  ,
//STRIP001 /*?*/             VIEWOPT_TABLE_BOUNDARIES   ,   svtools::TABLEBOUNDARIES   ,
//STRIP001 /*?*/             VIEWOPT_INDEX_SHADINGS     ,   svtools::WRITERIDXSHADINGS     ,
//STRIP001 /*?*/             VIEWOPT_LINKS              ,   svtools::LINKS              ,
//STRIP001 /*?*/             VIEWOPT_VISITED_LINKS      ,   svtools::LINKSVISITED      ,
//STRIP001 /*?*/             VIEWOPT_FIELD_SHADINGS     ,   svtools::WRITERFIELDSHADINGS     ,
//STRIP001 /*?*/             VIEWOPT_SECTION_BOUNDARIES ,   svtools::WRITERSECTIONBOUNDARIES ,
//STRIP001 /*?*/             0                          ,   svtools::ColorConfigEntryCount
//STRIP001 /*?*/         };
//STRIP001 /*?*/         sal_uInt16 nPos = 0;
//STRIP001 /*?*/         while(aFlags[nPos].nFlag)
//STRIP001 /*?*/         {
//STRIP001 /*?*/             if(0 != (nFlag&aFlags[nPos].nFlag))
//STRIP001 /*?*/             {
//STRIP001 /*?*/                 svtools::ColorConfigValue aValue = aEditableConfig.GetColorValue(aFlags[nPos].eEntry);
//STRIP001 /*?*/                 aValue.bIsVisible = bSet;
//STRIP001 /*?*/                 aEditableConfig.SetColorValue(aFlags[nPos].eEntry, aValue);
//STRIP001 /*?*/             }
//STRIP001 /*?*/             nPos++;
//STRIP001 /*?*/         }
//STRIP001 /*?*/     }
/*N*/ }
/* -----------------------------24.04.2002 10:42------------------------------

 ---------------------------------------------------------------------------*/
/*N*/ BOOL SwViewOption::IsAppearanceFlag(sal_Int32 nFlag)
/*N*/ {
/*N*/     return 0 != (nAppearanceFlags & nFlag);
/*N*/ }

}
