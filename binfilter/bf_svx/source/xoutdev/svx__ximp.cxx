/*************************************************************************
 *
 *  $RCSfile: svx__ximp.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:45 $
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

#include <algorithm>

#include <stdlib.h>
#include <math.h>
#include <vcl/svapp.hxx>
#include <tools/poly.hxx>
#include <vcl/gradient.hxx>
#include <vcl/virdev.hxx>
#include <vcl/gdimtf.hxx>
#include <vcl/metaact.hxx>
#include <vcl/salbtype.hxx>
#include <vcl/wrkwin.hxx>
#include <goodies/grfmgr.hxx>
#include "xpoly.hxx"
#include "xattr.hxx"
#include "xoutbmp.hxx"
#include "xoutx.hxx"
#include "svdoimp.hxx"
namespace binfilter {

// -----------
// - Statics -
// -----------

#ifdef MAC
    const BOOL XIMP_bDrawRasterOps = FALSE;
#else
    const BOOL XIMP_bDrawRasterOps = TRUE;
#endif

// -----------
// - Defines -
// -----------

#define FILL_TILE 200

// ----------------
// - XOuputDevice -
// ----------------

/*N*/ void XOutputDevice::DrawFillPolyPolygon( const PolyPolygon& rPolyPoly, BOOL bRect )
/*N*/ {
/*N*/   if( ( eFillStyle != XFILL_NONE ) && iRotTransGradient() &&
/*N*/       ( eFillStyle != XFILL_SOLID || iRotTransGradient()->GetStartColor() != iRotTransGradient()->GetEndColor() ) )
/*N*/   {
/*?*/       XGradient&      rTransGradient = *iRotTransGradient();
/*?*/       Gradient        aVCLGradient;
/*?*/       GDIMetaFile     aMtf;
/*?*/       VirtualDevice   aVDev;
/*?*/       OutputDevice*   pOldOut = pOut;
/*?*/       const Rectangle aBound( rPolyPoly.GetBoundRect() );
/*?*/       MapMode         aMap( pOldOut->GetMapMode() );
/*?*/
/*?*/       pOut = &aVDev;
/*?*/       aVDev.EnableOutput( FALSE );
/*?*/       aVDev.SetMapMode( pOldOut->GetMapMode() );
/*?*/       aMtf.Record( &aVDev );
/*?*/       aVDev.SetLineColor( pOldOut->GetLineColor() );
/*?*/       aVDev.SetFillColor( pOldOut->GetFillColor() );
/*?*/       aVDev.SetFont( pOldOut->GetFont() );
/*?*/       aVDev.SetDrawMode( pOldOut->GetDrawMode() );
/*?*/       aVDev.SetRefPoint( pOldOut->GetRefPoint() );
/*?*/       ImpDrawFillPolyPolygon( rPolyPoly, bRect, pOldOut->GetOutDevType() == OUTDEV_PRINTER );
/*?*/       aMtf.Stop();
/*?*/       aMtf.WindStart();
/*?*/       aMap.SetOrigin( aBound.TopLeft() );
/*?*/       aMtf.SetPrefMapMode( aMap );
/*?*/       aMtf.SetPrefSize( aBound.GetSize() );
/*?*/       pOut = pOldOut;
/*?*/
/*?*/       aVCLGradient.SetStyle((GradientStyle)rTransGradient.GetGradientStyle());
/*?*/       aVCLGradient.SetStartColor(rTransGradient.GetStartColor());
/*?*/       aVCLGradient.SetEndColor(rTransGradient.GetEndColor());
/*?*/       aVCLGradient.SetAngle((USHORT)rTransGradient.GetAngle());
/*?*/       aVCLGradient.SetBorder(rTransGradient.GetBorder());
/*?*/       aVCLGradient.SetOfsX(rTransGradient.GetXOffset());
/*?*/       aVCLGradient.SetOfsY(rTransGradient.GetYOffset());
/*?*/       aVCLGradient.SetStartIntensity(rTransGradient.GetStartIntens());
/*?*/       aVCLGradient.SetEndIntensity(rTransGradient.GetEndIntens());
/*?*/       aVCLGradient.SetSteps(rTransGradient.GetSteps());
/*?*/
/*?*/       pOut->DrawTransparent( aMtf, aBound.TopLeft(), aBound.GetSize(), aVCLGradient );
/*N*/   }
/*N*/   else
/*N*/       ImpDrawFillPolyPolygon( rPolyPoly, bRect, pOut->GetOutDevType() == OUTDEV_PRINTER );
/*N*/ }

// ------------------------------------------------------------------------

/*N*/ void XOutputDevice::ImpDrawFillPolyPolygon( const PolyPolygon& rPolyPoly, BOOL bRect, BOOL bPrinter )
/*N*/ {
/*N*/   if( eFillStyle != XFILL_NONE )
/*N*/   {
/*?*/       const Color aOldLineColor( pOut->GetLineColor() );
/*?*/       const ULONG nDrawMode = pOut->GetDrawMode();
/*?*/
/*?*/       pOut->SetLineColor();
/*?*/
/*?*/       if( eFillStyle == XFILL_SOLID )
/*?*/       {
/*?*/           if( nFillTransparence )
/*?*/               pOut->DrawTransparent( rPolyPoly, nFillTransparence );
/*?*/           else
/*?*/               pOut->DrawPolyPolygon( rPolyPoly );
/*?*/       }
/*?*/       else if( eFillStyle == XFILL_HATCH )
/*?*/       {
/*?*/           long        nAngle10 = aHatch.GetAngle() % 3600;
/*?*/           HatchStyle  eStyle;
/*?*/
/*?*/           if( nAngle10 < 0 )
/*?*/               nAngle10 += 3600;
/*?*/
/*?*/           switch( aHatch.GetHatchStyle() )
/*?*/           {
/*?*/               case( XHATCH_TRIPLE ): eStyle = HATCH_TRIPLE; break;
/*?*/               case( XHATCH_DOUBLE ): eStyle = HATCH_DOUBLE; break;
/*?*/
/*?*/               default:
/*?*/                   eStyle = HATCH_SINGLE;
/*?*/               break;
/*?*/           }
/*?*/
/*?*/           if( iSolidHatch() )
/*?*/               pOut->DrawPolyPolygon( rPolyPoly );
/*?*/
/*?*/           pOut->DrawHatch( rPolyPoly, Hatch( eStyle, aHatch.GetColor(), aHatch.GetDistance(), (USHORT) nAngle10 ) );
/*?*/       }
/*?*/       else if( eFillStyle == XFILL_GRADIENT )
/*?*/       {
/*?*/           GDIMetaFile*    pMtf = pOut->GetConnectMetaFile();
/*?*/           Gradient        aVCLGradient;
/*?*/
/*?*/
/*?*/           aVCLGradient.SetStyle((GradientStyle)aGradient.GetGradientStyle());
/*?*/           aVCLGradient.SetStartColor(aGradient.GetStartColor());
/*?*/           aVCLGradient.SetEndColor(aGradient.GetEndColor());
/*?*/           aVCLGradient.SetAngle((USHORT)aGradient.GetAngle());
/*?*/           aVCLGradient.SetBorder(aGradient.GetBorder());
/*?*/           aVCLGradient.SetOfsX(aGradient.GetXOffset());
/*?*/           aVCLGradient.SetOfsY(aGradient.GetYOffset());
/*?*/           aVCLGradient.SetStartIntensity(aGradient.GetStartIntens());
/*?*/           aVCLGradient.SetEndIntensity(aGradient.GetEndIntens());
/*?*/           aVCLGradient.SetSteps(aGradient.GetSteps());
/*?*/
/*?*/           if( bRect )
/*?*/               pOut->DrawGradient( rPolyPoly.GetBoundRect(), aVCLGradient );
/*?*/           else
/*?*/               pOut->DrawGradient( rPolyPoly, aVCLGradient );
/*?*/       }
/*?*/       else if( eFillStyle == XFILL_BITMAP )
/*?*/       {
/*?*/           if( nDrawMode & DRAWMODE_WHITEFILL )
/*?*/           {
/*?*/               const Color aOldFillColor( pOut->GetFillColor() );
/*?*/
/*?*/               pOut->SetFillColor( COL_WHITE );
/*?*/               pOut->DrawPolyPolygon( rPolyPoly );
/*?*/               pOut->SetFillColor( aOldFillColor );
/*?*/           }
/*?*/           else
/*?*/           {
/*?*/               Rectangle       aPolyRect( rPolyPoly.GetBoundRect() );
/*?*/               GDIMetaFile*    pMtf = pOut->GetConnectMetaFile();
/*?*/
/*?*/               pOut->Push();
/*?*/               pOut->SetRasterOp( ROP_OVERPAINT );
/*?*/
/*?*/               if( pMtf && !bPrinter )
/*?*/               {
/*?*/                   if( !pOut->GetPDFWriter() && XIMP_bDrawRasterOps )
/*?*/                   {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/                        pOut->SetRasterOp( ROP_XOR );
//STRIP001 /*?*/                        ImpDrawBitmapFill( aPolyRect, bPrinter );
//STRIP001 /*?*/
//STRIP001 /*?*/                        pOut->Push( PUSH_FILLCOLOR );
//STRIP001 /*?*/                        pOut->SetFillColor( COL_BLACK );
//STRIP001 /*?*/                        pOut->SetRasterOp( ROP_0 );
//STRIP001 /*?*/                        pOut->DrawPolyPolygon( rPolyPoly );
//STRIP001 /*?*/                        pOut->Pop();
//STRIP001 /*?*/
//STRIP001 /*?*/                        pOut->SetRasterOp( ROP_XOR );
//STRIP001 /*?*/                        ImpDrawBitmapFill( aPolyRect, bPrinter );
/*?*/                   }
/*?*/                   else
/*?*/                   {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/                        pOut->IntersectClipRegion( rPolyPoly );
//STRIP001 /*?*/                        ImpDrawBitmapFill( aPolyRect, bPrinter );
/*?*/                   }
/*?*/               }
/*?*/               else if( bRect || bPrinter )
/*?*/               {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/                    pOut->IntersectClipRegion( rPolyPoly );
//STRIP001 /*?*/                    ImpDrawBitmapFill( aPolyRect, bPrinter );
/*?*/               }
/*?*/               else
/*?*/               {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/                    VirtualDevice   aMemDev;
//STRIP001 /*?*/                    PolyPolygon     aPolyPoly( pOut->LogicToPixel( rPolyPoly ) );
//STRIP001 /*?*/                     Rectangle      aPolyRectPix( pOut->LogicToPixel( aPolyRect ) );
//STRIP001 /*?*/                    Point           aPoint;
//STRIP001 /*?*/                    Rectangle       aOutputRectPix( aPoint, pOut->GetOutputSizePixel() );
//STRIP001 /*?*/                     const BOOL      bOldMap = pOut->IsMapModeEnabled();
//STRIP001 /*?*/
//STRIP001 /*?*/                     pOut->EnableMapMode( FALSE );
//STRIP001 /*?*/
//STRIP001 /*?*/                     aOutputRectPix.Intersection( aPolyPoly.GetBoundRect() );
//STRIP001 /*?*/
//STRIP001 /*?*/                    // add one pixel to avoid mapping differences
//STRIP001 /*?*/                    aOutputRectPix.Right() += 2, aOutputRectPix.Bottom() += 2;
//STRIP001 /*?*/                    const Size aVDevSizePix( aOutputRectPix.GetSize() );
//STRIP001 /*?*/
//STRIP001 /*?*/                    pOut->IntersectClipRegion( aPolyRectPix );
//STRIP001 /*?*/                    aMemDev.SetOutputSizePixel( aVDevSizePix );
//STRIP001 /*?*/                    aMemDev.DrawOutDev( Point(), aVDevSizePix, aOutputRectPix.TopLeft(), aVDevSizePix, *pOut );
//STRIP001 /*?*/
//STRIP001 /*?*/                     pOut->EnableMapMode( bOldMap );
//STRIP001 /*?*/                    ImpDrawBitmapFill( aPolyRect, bPrinter );
//STRIP001 /*?*/                     pOut->EnableMapMode( FALSE );
//STRIP001 /*?*/
//STRIP001 /*?*/                     aMemDev.SetRasterOp( ROP_XOR );
//STRIP001 /*?*/                    aMemDev.DrawOutDev( Point(), aVDevSizePix, aOutputRectPix.TopLeft(), aVDevSizePix, *pOut );
//STRIP001 /*?*/
//STRIP001 /*?*/                    aMemDev.Push( PUSH_FILLCOLOR );
//STRIP001 /*?*/                    aMemDev.SetFillColor( COL_BLACK );
//STRIP001 /*?*/                    aMemDev.SetRasterOp( ROP_0 );
//STRIP001 /*?*/                    aPolyPoly.Move( -aOutputRectPix.Left(), -aOutputRectPix.Top() );
//STRIP001 /*?*/                    aMemDev.DrawPolyPolygon( aPolyPoly );
//STRIP001 /*?*/                    aMemDev.Pop();
//STRIP001 /*?*/
//STRIP001 /*?*/                    pOut->SetRasterOp( ROP_XOR );
//STRIP001 /*?*/                    pOut->DrawOutDev( aOutputRectPix.TopLeft(), aVDevSizePix, Point(), aVDevSizePix, aMemDev );
//STRIP001 /*?*/
//STRIP001 /*?*/                     pOut->EnableMapMode( bOldMap );
/*?*/               }
/*?*/
/*?*/               pOut->Pop();
/*?*/           }
/*?*/       }
/*?*/
/*?*/       pOut->SetLineColor( aOldLineColor );
/*N*/   }
/*N*/ }

// ------------------------------------------------------------------------

//STRIP001 void XOutputDevice::ImpDrawBitmapFill( const Rectangle& rRect, BOOL bPrinter )
//STRIP001 {
//STRIP001  // Ausgabe-Position und -Groesse bestimmen
//STRIP001  ImpCalcBmpFillStartValues( rRect, bPrinter );
//STRIP001
//STRIP001  if( ( mbBmpTile || !mbBmpStretch ) && ( !maFillBitmapSize.Width() || !maFillBitmapSize.Height() ) )
//STRIP001      return;
//STRIP001
//STRIP001  if( ( !pOut->GetConnectMetaFile() || bPrinter ) || pOut->GetPDFWriter() )
//STRIP001  {
//STRIP001      if ( mbBmpTile )
//STRIP001         {
//STRIP001             Point aOffset( rRect.TopLeft() - maStartPoint );
//STRIP001
//STRIP001             // #105229# Delegating tile draw to graphic object
//STRIP001             mpFillGraphicObject->DrawTiled( pOut, rRect, maFillBitmapSize,
//STRIP001                                             Size( aOffset.X(), aOffset.Y() ), NULL, GRFMGR_DRAW_CACHED, 128 );
//STRIP001         }
//STRIP001      else
//STRIP001      {
//STRIP001             // #104846# ImpCalcBmpFillStartValues now also calc non-tiled sizes correctly
//STRIP001             mpFillGraphicObject->Draw( pOut, maStartPoint, maFillBitmapSize, NULL, GRFMGR_DRAW_CACHED );
//STRIP001      }
//STRIP001  }
//STRIP001  // Mtf-Aufzeichnung
//STRIP001  else
//STRIP001  {
//STRIP001      pOut->Push();
//STRIP001
//STRIP001      if( mbBmpTile )
//STRIP001      {
//STRIP001          VirtualDevice   aVDev;
//STRIP001          MapMode         aMap( pOut->GetMapMode().GetMapUnit() );
//STRIP001
//STRIP001          aVDev.SetOutputSizePixel( pOut->LogicToPixel( rRect, aMap ).GetSize() );
//STRIP001          aMap.SetOrigin( Point( -rRect.Left(), -rRect.Top() ) );
//STRIP001          aVDev.SetMapMode( aMap );
//STRIP001
//STRIP001             // #105229# Delegating tile draw to graphic object
//STRIP001             // #94014#
//STRIP001             Point aOffset( rRect.TopLeft() - maStartPoint );
//STRIP001
//STRIP001             mpFillGraphicObject->DrawTiled( &aVDev, rRect, maFillBitmapSize,
//STRIP001                                             Size( aOffset.X(), aOffset.Y() ), NULL, GRFMGR_DRAW_CACHED, 128 );
//STRIP001             GraphicObject aTmpGraphic( aVDev.GetBitmap( rRect.TopLeft(), aVDev.GetOutputSize() ) );
//STRIP001             aTmpGraphic.Draw( pOut, rRect.TopLeft(), rRect.GetSize(), NULL, GRFMGR_DRAW_CACHED );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if( !mbBmpStretch )
//STRIP001          {
//STRIP001              // in MetaFiles machen wir den Hintergrund weiss
//STRIP001              // das Poppen macht das Selektieren der Brush
//STRIP001              // wieder rueckgaengig
//STRIP001              PolyPolygon aPolyPoly( 2 );
//STRIP001              aPolyPoly.Insert( Polygon( rRect ) );
//STRIP001              aPolyPoly.Insert( Polygon( Rectangle( maStartPoint, maFillBitmapSize ) ) );
//STRIP001
//STRIP001              pOut->SetFillColor( Color( COL_WHITE ) );
//STRIP001              pOut->SetLineColor();
//STRIP001              pOut->DrawPolyPolygon( aPolyPoly );
//STRIP001             }
//STRIP001
//STRIP001             // #104846# ImpCalcBmpFillStartValues now also calc non-tiled sizes correctly
//STRIP001             mpFillGraphicObject->Draw( pOut, maStartPoint, maFillBitmapSize, NULL, GRFMGR_DRAW_CACHED );
//STRIP001      }
//STRIP001
//STRIP001      pOut->Pop();
//STRIP001  }
//STRIP001 }

// ------------------------------------------------------------------------

//STRIP001 void XOutputDevice::ImpCalcBmpFillStartValues( const Rectangle& rRect, BOOL bPrinter )
//STRIP001 {
//STRIP001     GDIMetaFile*    pMtf = pOut->GetConnectMetaFile();
//STRIP001  const MapMode   aDstMapMode( pOut->GetMapMode().GetMapUnit() );
//STRIP001     Size         aStartOffset;
//STRIP001
//STRIP001     // #104609# Extracted to ImpCalcBmpFillSizes
//STRIP001     ImpCalcBmpFillSizes( aStartOffset, maBmpOutputSize, rRect,
//STRIP001                          aDstMapMode, maFillBitmap, maBmpSize,
//STRIP001                          Size( mnBmpPerCentX, mnBmpPerCentY ),
//STRIP001                          Size( mnBmpOffPosX, mnBmpOffPosY ),
//STRIP001                          mbBmpLogSize, mbBmpTile, mbBmpStretch, meBmpRectPoint );
//STRIP001
//STRIP001     maStartPoint.X() = rRect.Left() + aStartOffset.Width();
//STRIP001     maStartPoint.Y() = rRect.Top() + aStartOffset.Height();
//STRIP001
//STRIP001     if( mbRecalc )
//STRIP001     {
//STRIP001         mpFillGraphicObject->SetGraphic( maFillBitmap );
//STRIP001
//STRIP001         const Size aBmpSizePix( maFillBitmap.GetSizePixel() );
//STRIP001
//STRIP001         // create intermediate bitmap if neccessary
//STRIP001         // #105229# Condition changed: intermediate necessary only for
//STRIP001         // tiling plus phase offsets, mnBmpOff is only evaluated for tilings
//STRIP001         if( mbBmpTile && ( mnBmpOffX != 0 ||
//STRIP001                            mnBmpOffY != 0 ||
//STRIP001                            mnBmpOffPosX != 0 ||
//STRIP001                            mnBmpOffPosY != 0 ) && !maFillBitmap.IsEmpty() )
//STRIP001         {
//STRIP001             VirtualDevice   aVDev;
//STRIP001             const Point     aPt;
//STRIP001          const Size      aNewSize( 2 * aBmpSizePix.Width(), 2 * aBmpSizePix.Height() );
//STRIP001             const Rectangle aIntermediateRect( aPt, aNewSize );
//STRIP001
//STRIP001             aVDev.SetOutputSizePixel( aNewSize );
//STRIP001             maBmpOutputSize.Width() *= 2;
//STRIP001             maBmpOutputSize.Height() *= 2;
//STRIP001             maFillBitmapSize = aBmpSizePix;
//STRIP001             ImpDrawTiledBitmap( &aVDev, aIntermediateRect, aPt, aIntermediateRect, FALSE );
//STRIP001             mpFillGraphicObject->SetGraphic( aVDev.GetBitmap( aPt, aNewSize ) );
//STRIP001         }
//STRIP001
//STRIP001         maFillBitmapSize = maBmpOutputSize;
//STRIP001     }
//STRIP001
//STRIP001  if( !pMtf )
//STRIP001      mbRecalc = FALSE;
//STRIP001 }

// ------------------------------------------------------------------------

//STRIP001 void XOutputDevice::ImpDrawTiledBitmap( OutputDevice* pOutDev, const Rectangle& rRect,
//STRIP001                                      const Point& rStartPoint, const Rectangle& rClipRect,
//STRIP001                                         BOOL bPrinter )
//STRIP001 {
//STRIP001     // #105229# Removed everything except plain painting; cached tile
//STRIP001     // draw is now done via GraphicObject. This method's solely
//STRIP001     // purpose is to render tiles with phase shifts (currently, 2x2 tiles)
//STRIP001     Point            aPixOrg;
//STRIP001     Point           aOrg;
//STRIP001     const Rectangle aPixRect( pOutDev->LogicToPixel( rRect ) ) ;
//STRIP001     const Rectangle aPixClipRect( pOutDev->LogicToPixel( rClipRect ) ) ;
//STRIP001     const Point     aPixPos( pOutDev->LogicToPixel( rStartPoint ) );
//STRIP001     const Size      aPixSize( pOutDev->LogicToPixel( maFillBitmapSize ) );
//STRIP001     const long       nOffX = aPixSize.Width() - aPixSize.Width() * mnBmpOffX / 100;
//STRIP001     const long       nOffY = aPixSize.Height() - aPixSize.Height() * mnBmpOffY / 100;
//STRIP001     // #106767# Prevent division by zero
//STRIP001     long         nCountX = ( aPixRect.Right() - aPixPos.X() ) / ::std::max( aPixSize.Width(), 1L ) + 1;
//STRIP001     long         nCountY = ( aPixRect.Bottom() - aPixPos.Y() ) / ::std::max( aPixSize.Height(), 1L ) + 1;
//STRIP001     BOOL         bDraw;
//STRIP001
//STRIP001     // Falls Kacheln untereinander verschoben,
//STRIP001     // muessen wir noch eine zusaetzliche Zeile
//STRIP001     // oder Spalte ausgeben
//STRIP001     if( mnBmpOffX )
//STRIP001         nCountX++;
//STRIP001     else if( mnBmpOffY )
//STRIP001         nCountY++;
//STRIP001
//STRIP001     long nCountX1 = nCountX - 1;
//STRIP001     long nCountY1 = nCountY - 1;
//STRIP001
//STRIP001     aPixOrg = aPixPos;
//STRIP001
//STRIP001     // Kachelung ausgeben
//STRIP001     for ( long nY = 0; nY < nCountY; nY++ )
//STRIP001     {
//STRIP001         for ( long nX = 0; nX < nCountX; nX++ )
//STRIP001         {
//STRIP001             bDraw = FALSE;
//STRIP001
//STRIP001             if( mnBmpOffX && ( nY & 1 ) )
//STRIP001             {
//STRIP001                 bDraw = TRUE;
//STRIP001                 aOrg = Point( aPixOrg.X() - nOffX, aPixOrg.Y() );
//STRIP001             }
//STRIP001             else if( mnBmpOffY && ( nX & 1 ) )
//STRIP001             {
//STRIP001                 bDraw = TRUE;
//STRIP001                 aOrg = Point( aPixOrg.X(), aPixOrg.Y() - nOffY );
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 if( mnBmpOffX )
//STRIP001                 {
//STRIP001                     // Nicht-Offset-Tiles ausser in der letzten Spalte immer zeichnen
//STRIP001                     if( nX < nCountX1 )
//STRIP001                         bDraw = TRUE;
//STRIP001                 }
//STRIP001                 else if( mnBmpOffY )
//STRIP001                 {
//STRIP001                     // Nicht-Offset-Tiles ausser in der letzten Zeile immer zeichnen
//STRIP001                     if( nY < nCountY1 )
//STRIP001                         bDraw = TRUE;
//STRIP001                 }
//STRIP001                 else
//STRIP001                     bDraw = TRUE;
//STRIP001
//STRIP001                 aOrg = aPixOrg;
//STRIP001             }
//STRIP001
//STRIP001             // ausgeben, wenn innerhalb des Objektes und innerhalb
//STRIP001             // des gueltigen Clipping-Bereiches
//STRIP001             if ( bDraw && !Rectangle( aOrg, aPixSize ).Intersection( aPixClipRect ).IsEmpty() )
//STRIP001                 mpFillGraphicObject->Draw( pOutDev, pOutDev->PixelToLogic( aOrg ), maFillBitmapSize, NULL, GRFMGR_DRAW_CACHED );
//STRIP001
//STRIP001             aPixOrg.X() += aPixSize.Width();
//STRIP001         }
//STRIP001
//STRIP001         aPixOrg.X() = aPixPos.X();
//STRIP001         aPixOrg.Y() += aPixSize.Height();
//STRIP001     }
//STRIP001 }
} //namespace binfilter
