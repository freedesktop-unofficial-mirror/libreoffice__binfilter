/*************************************************************************
 *
 *  $RCSfile: svx_impgrfll.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:22 $
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

#ifndef _SFXITEMSET_HXX
#include <svtools/itemset.hxx>
#endif

#ifndef _SV_SALBTYPE_HXX
#include <vcl/salbtype.hxx>     // FRound
#endif

#ifndef _SV_VIRDEV_HXX
#include <vcl/virdev.hxx>
#endif

#ifndef _SV_GDIMTF_HXX
#include <vcl/gdimtf.hxx>
#endif

#ifndef _SV_METAACT_HXX
#include <vcl/metaact.hxx>
#endif

#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif

#ifndef _SVTOOLS_GRAPHICTOOLS_HXX_
#include <svtools/graphictools.hxx>
#endif

#include "svdobj.hxx"
#include "xpoly.hxx"
#include "xattr.hxx"
#include "xoutbmp.hxx"
#include "xoutx.hxx"

#include "xenum.hxx"
#include "xgrad.hxx"
#include "xhatch.hxx"
#include "xflhtit.hxx"
#include "xbtmpit.hxx"
#include "svdoimp.hxx"
#include "svdattr.hxx"


///////////////////////////////////////////////////////////////////////////////

#define ITEMVALUE(ItemSet,Id,Cast)  ((const Cast&)(ItemSet).Get(Id)).GetValue()

////////////////////////////////////////////////////////////////////////////////////////////////////

// #100127# Bracket filled output with a comment, if recording a Mtf
/*N*/ ImpGraphicFill::ImpGraphicFill( const SdrObject&      rObj,
/*N*/                                 const ExtOutputDevice&    rXOut,
/*N*/                                 const SfxItemSet&         rFillItemSet,
/*N*/                                 bool                  bIsShadow       ) :
/*N*/     mrObj( rObj ),
/*N*/     mrXOut( rXOut ),
/*N*/     mbCommentWritten( false )
/*N*/ {
/*N*/   const SfxItemSet& rSet = rObj.GetItemSet();
/*N*/     XFillStyle eFillStyle( ITEMVALUE( rFillItemSet, XATTR_FILLSTYLE, XFillStyleItem ) );
/*N*/     XGradient aGradient( ITEMVALUE( rFillItemSet, XATTR_FILLGRADIENT, XFillGradientItem ) );
/*N*/     XHatch aHatch( ITEMVALUE( rFillItemSet, XATTR_FILLHATCH, XFillHatchItem ) );
/*N*/
/*N*/   sal_Int32 nDX( ((SdrShadowXDistItem&)(rSet.Get(SDRATTR_SHADOWXDIST))).GetValue() );
/*N*/   sal_Int32 nDY( ((SdrShadowYDistItem&)(rSet.Get(SDRATTR_SHADOWYDIST))).GetValue() );
/*N*/
/*N*/     GDIMetaFile* pMtf=NULL;
/*N*/     if( eFillStyle != XFILL_NONE &&
/*N*/         (pMtf=mrXOut.GetOutDev()->GetConnectMetaFile()) )
/*?*/     {DBG_ASSERT(0, "STRIP");//STRIP001
//STRIP001 /*?*/         XPolyPolygon aGeometry;
//STRIP001 /*?*/         mrObj.TakeXorPoly(aGeometry, TRUE);
//STRIP001 /*?*/
//STRIP001 /*?*/         // #104686# Prune non-closed polygons from geometry
//STRIP001 /*?*/         XPolyPolygon aPolyPoly;
//STRIP001 /*?*/         int i;
//STRIP001 /*?*/         for( i=0; i<aGeometry.Count(); ++i )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             const XPolygon& rPoly = aGeometry.GetObject(i);
//STRIP001 /*?*/             if( rPoly[0] == rPoly[ rPoly.GetPointCount()-1 ] )
//STRIP001 /*?*/             {
//STRIP001 /*?*/                 // polygon is closed - use for fillings
//STRIP001 /*?*/                 aPolyPoly.Insert( rPoly );
//STRIP001 /*?*/             }
//STRIP001 /*?*/         }
//STRIP001 /*?*/
//STRIP001 /*?*/         // #103692# Offset original geometry for shadows
//STRIP001 /*?*/         if( bIsShadow && (nDX || nDY) )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             // transformation necessary
//STRIP001 /*?*/             aPolyPoly.Move( nDX, nDY );
//STRIP001 /*?*/         }
//STRIP001 /*?*/
//STRIP001 /*?*/         SvtGraphicFill::FillType eType;
//STRIP001 /*?*/         switch( eFillStyle )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             case XFILL_NONE:
//STRIP001 /*?*/             case XFILL_SOLID:
//STRIP001 /*?*/                 eType = SvtGraphicFill::fillSolid;
//STRIP001 /*?*/                 break;
//STRIP001 /*?*/
//STRIP001 /*?*/             case XFILL_GRADIENT:
//STRIP001 /*?*/                 eType = SvtGraphicFill::fillGradient;
//STRIP001 /*?*/                 break;
//STRIP001 /*?*/
//STRIP001 /*?*/             case XFILL_HATCH:
//STRIP001 /*?*/                 eType = SvtGraphicFill::fillHatch;
//STRIP001 /*?*/                 break;
//STRIP001 /*?*/
//STRIP001 /*?*/             case XFILL_BITMAP:
//STRIP001 /*?*/                 eType = SvtGraphicFill::fillTexture;
//STRIP001 /*?*/                 break;
//STRIP001 /*?*/
//STRIP001 /*?*/             default:
//STRIP001 /*?*/                 DBG_ERROR( "ImpGraphicFill::ImpGraphicFill invalid fill type");
//STRIP001 /*?*/                 break;
//STRIP001 /*?*/         }
//STRIP001 /*?*/
//STRIP001 /*?*/         SvtGraphicFill::Transform aTransform;
//STRIP001 /*?*/         SvtGraphicFill::HatchType eHatch;
//STRIP001 /*?*/         // TODO: Set hatch background color. Do that via multi-texturing
//STRIP001 /*?*/         switch( aHatch.GetHatchStyle() )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             case XHATCH_SINGLE:
//STRIP001 /*?*/                 eHatch = SvtGraphicFill::hatchSingle;
//STRIP001 /*?*/                 break;
//STRIP001 /*?*/
//STRIP001 /*?*/             case XHATCH_DOUBLE:
//STRIP001 /*?*/                 eHatch = SvtGraphicFill::hatchDouble;
//STRIP001 /*?*/                 break;
//STRIP001 /*?*/
//STRIP001 /*?*/             case XHATCH_TRIPLE:
//STRIP001 /*?*/                 eHatch = SvtGraphicFill::hatchTriple;
//STRIP001 /*?*/                 break;
//STRIP001 /*?*/
//STRIP001 /*?*/             default:
//STRIP001 /*?*/                 DBG_ERROR( "ImpGraphicFill::ImpGraphicFill invalid hatch type");
//STRIP001 /*?*/                 break;
//STRIP001 /*?*/         }
//STRIP001 /*?*/
//STRIP001 /*?*/         if( SvtGraphicFill::fillHatch == eType )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             // scale
//STRIP001 /*?*/             aTransform.matrix[0] *= aHatch.GetDistance();
//STRIP001 /*?*/             aTransform.matrix[4] *= aHatch.GetDistance();
//STRIP001 /*?*/
//STRIP001 /*?*/             // rotate
//STRIP001 /*?*/             aTransform.matrix[0] *= cos( aHatch.GetAngle() );
//STRIP001 /*?*/             aTransform.matrix[1] *= -sin( aHatch.GetAngle() );
//STRIP001 /*?*/             aTransform.matrix[3] *= sin( aHatch.GetAngle() );
//STRIP001 /*?*/             aTransform.matrix[4] *= cos( aHatch.GetAngle() );
//STRIP001 /*?*/         }
//STRIP001 /*?*/
//STRIP001 /*?*/         SvtGraphicFill::GradientType eGrad;
//STRIP001 /*?*/         switch( aGradient.GetGradientStyle() )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             case XGRAD_LINEAR:
//STRIP001 /*?*/             case XGRAD_AXIAL:
//STRIP001 /*?*/                 // TODO: setup transformation
//STRIP001 /*?*/                 eGrad = SvtGraphicFill::gradientLinear;
//STRIP001 /*?*/                 break;
//STRIP001 /*?*/
//STRIP001 /*?*/             case XGRAD_RADIAL:
//STRIP001 /*?*/             case XGRAD_ELLIPTICAL:
//STRIP001 /*?*/                 // TODO: setup transformation
//STRIP001 /*?*/                 eGrad = SvtGraphicFill::gradientRadial;
//STRIP001 /*?*/                 break;
//STRIP001 /*?*/
//STRIP001 /*?*/             case XGRAD_SQUARE:
//STRIP001 /*?*/             case XGRAD_RECT:
//STRIP001 /*?*/                 // TODO: setup transformation
//STRIP001 /*?*/                 eGrad = SvtGraphicFill::gradientRectangular;
//STRIP001 /*?*/                 break;
//STRIP001 /*?*/
//STRIP001 /*?*/             default:
//STRIP001 /*?*/                 DBG_ERROR( "ImpGraphicFill::ImpGraphicFill invalid gradient type");
//STRIP001 /*?*/                 break;
//STRIP001 /*?*/         }
//STRIP001 /*?*/
//STRIP001 /*?*/         Graphic aFillGraphic;
//STRIP001 /*?*/         bool bTile( ITEMVALUE( rFillItemSet, XATTR_FILLBMP_TILE, SfxBoolItem ) );
//STRIP001 /*?*/         if( SvtGraphicFill::fillTexture == eType )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             OutputDevice* pOut = rXOut.GetOutDev();
//STRIP001 /*?*/
//STRIP001 /*?*/             if( pOut )
//STRIP001 /*?*/             {
//STRIP001 /*?*/                 Bitmap             aBitmap( ITEMVALUE( rSet, XATTR_FILLBITMAP, XFillBitmapItem ).GetBitmap() );
//STRIP001 /*?*/                 Rectangle       aPolyRect( aPolyPoly.GetBoundRect() );
//STRIP001 /*?*/                 MapMode            aMap( pOut->GetMapMode().GetMapUnit() );
//STRIP001 /*?*/                 Size           aStartOffset;
//STRIP001 /*?*/                 Size           aBmpOutputSize;
//STRIP001 /*?*/
//STRIP001 /*?*/                 // #104609# Call extracted method from XOutputDevice to
//STRIP001 /*?*/                 // determine bitmap size and offset
//STRIP001 /*?*/                 RECT_POINT     eRectPoint = (RECT_POINT) ITEMVALUE( rSet, XATTR_FILLBMP_POS, SfxEnumItem );
//STRIP001 /*?*/                 USHORT         nOffX = ITEMVALUE( rSet, XATTR_FILLBMP_TILEOFFSETX, SfxUInt16Item );
//STRIP001 /*?*/                 USHORT         nOffY = ITEMVALUE( rSet, XATTR_FILLBMP_TILEOFFSETY, SfxUInt16Item );
//STRIP001 /*?*/                 Size           aPosOffset( ITEMVALUE( rSet, XATTR_FILLBMP_POSOFFSETX, SfxUInt16Item ),
//STRIP001 /*?*/                                             ITEMVALUE( rSet, XATTR_FILLBMP_POSOFFSETY, SfxUInt16Item ) );
//STRIP001 /*?*/                 BOOL           bStretch = ITEMVALUE( rSet, XATTR_FILLBMP_STRETCH, SfxBoolItem );
//STRIP001 /*?*/                 BOOL           bLogSize = ITEMVALUE( rSet, XATTR_FILLBMP_SIZELOG, SfxBoolItem );
//STRIP001 /*?*/                 Size           aSize( labs( ITEMVALUE( rSet, XATTR_FILLBMP_SIZEX, SfxMetricItem ) ),
//STRIP001 /*?*/                                        labs( ITEMVALUE( rSet, XATTR_FILLBMP_SIZEY, SfxMetricItem ) ) );
//STRIP001 /*?*/
//STRIP001 /*?*/                 Size           aBmpRenderSize;
//STRIP001 /*?*/                 Size           aBmpPerCentSize;
//STRIP001 /*?*/                 Size           aBmpSizePixel( aBitmap.GetSizePixel() );
//STRIP001 /*?*/
//STRIP001 /*?*/                 if( bLogSize )
//STRIP001 /*?*/                     aBmpRenderSize = aSize;
//STRIP001 /*?*/                 else
//STRIP001 /*?*/                     aBmpPerCentSize = aSize;
//STRIP001 /*?*/
//STRIP001 /*?*/                 ImpCalcBmpFillSizes( aStartOffset, aBmpOutputSize, aPolyRect,
//STRIP001 /*?*/                                      aMap, aBitmap, aBmpRenderSize, aBmpPerCentSize,
//STRIP001 /*?*/                                      aPosOffset, bLogSize, bTile, bStretch, eRectPoint );
//STRIP001 /*?*/
//STRIP001 /*?*/                 // avoid reimplementation of tiling and offset calculation
//STRIP001 /*?*/                 // -- simply render our texture into a VDev
//STRIP001 /*?*/                 if( bTile && (nOffX || nOffY) )
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     // paint texture to VDev, then extract first 2x2
//STRIP001 /*?*/                     // tiles (to cope with the offset variations)
//STRIP001 /*?*/
//STRIP001 /*?*/                     // setup VDev
//STRIP001 /*?*/                     VirtualDevice  aVDev;
//STRIP001 /*?*/
//STRIP001 /*?*/                     aVDev.SetOutputSizePixel( pOut->LogicToPixel( aPolyRect, aMap ).GetSize() );
//STRIP001 /*?*/                     aVDev.SetMapMode( aMap );
//STRIP001 /*?*/
//STRIP001 /*?*/                     // setup XOutDev
//STRIP001 /*?*/                     ExtOutputDevice aXOut( &aVDev );
//STRIP001 /*?*/                     aXOut.SetFillAttr( rFillItemSet );
//STRIP001 /*?*/
//STRIP001 /*?*/                     // prepare ItemSet to avoid line drawing
//STRIP001 /*?*/                     SfxItemSet aEmptySet( *rFillItemSet.GetPool() );
//STRIP001 /*?*/                     aEmptySet.Put(XLineStyleItem(XLINE_NONE));
//STRIP001 /*?*/                     aXOut.SetLineAttr( aEmptySet );
//STRIP001 /*?*/
//STRIP001 /*?*/                     // render into VDev (note: cannot paint smaller
//STRIP001 /*?*/                     // area here, because bitmap size might be
//STRIP001 /*?*/                     // relative to draw rect)
//STRIP001 /*?*/                     Rectangle aOutRect( aPolyRect );
//STRIP001 /*?*/                     aOutRect.SetPos( Point(0,0) );
//STRIP001 /*?*/                     aXOut.DrawRect( aOutRect );
//STRIP001 /*?*/
//STRIP001 /*?*/                     // extract first 2x2 tiles
//STRIP001 /*?*/                     Size aTileBmpSize( aBmpOutputSize );
//STRIP001 /*?*/                     aTileBmpSize.Width() *= 2;
//STRIP001 /*?*/                     aTileBmpSize.Height() *= 2;
//STRIP001 /*?*/                     Size aTileBmpSizePixel( pOut->LogicToPixel( aTileBmpSize ) );
//STRIP001 /*?*/                     aFillGraphic = Graphic( aVDev.GetBitmap( Point(), aTileBmpSize ) );
//STRIP001 /*?*/                     aFillGraphic.SetPrefMapMode( MapMode(MAP_PIXEL) );
//STRIP001 /*?*/                     aFillGraphic.SetPrefSize( aTileBmpSizePixel );
//STRIP001 /*?*/
//STRIP001 /*?*/                     if( aTileBmpSizePixel.Width() == 0 )
//STRIP001 /*?*/                         aTileBmpSizePixel.Width() = 1;
//STRIP001 /*?*/                     if( aTileBmpSizePixel.Height() == 0 )
//STRIP001 /*?*/                         aTileBmpSizePixel.Height() = 1;
//STRIP001 /*?*/
//STRIP001 /*?*/                     // setup transformation (scale to logical coordinate system. no need for translation)
//STRIP001 /*?*/                     aTransform.matrix[0] *= (double)2*aBmpOutputSize.Width() / aTileBmpSizePixel.Width();
//STRIP001 /*?*/                     aTransform.matrix[4] *= (double)2*aBmpOutputSize.Height() / aTileBmpSizePixel.Height();
//STRIP001 /*?*/                 }
//STRIP001 /*?*/                 else
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     // setup fill graphic
//STRIP001 /*?*/                     aFillGraphic = Graphic( aBitmap );
//STRIP001 /*?*/                     aFillGraphic.SetPrefMapMode( MapMode(MAP_PIXEL) );
//STRIP001 /*?*/                     aFillGraphic.SetPrefSize( aBmpSizePixel );
//STRIP001 /*?*/
//STRIP001 /*?*/                     if( aBmpSizePixel.Width() == 0 )
//STRIP001 /*?*/                         aBmpSizePixel.Width() = 1;
//STRIP001 /*?*/                     if( aBmpSizePixel.Height() == 0 )
//STRIP001 /*?*/                         aBmpSizePixel.Height() = 1;
//STRIP001 /*?*/
//STRIP001 /*?*/                     // setup transformation from size and offset values (scale to logical coordinate system)
//STRIP001 /*?*/                     aTransform.matrix[0] *= (double)aBmpOutputSize.Width() / aBmpSizePixel.Width();
//STRIP001 /*?*/                     aTransform.matrix[4] *= (double)aBmpOutputSize.Height() / aBmpSizePixel.Height();
//STRIP001 /*?*/
//STRIP001 /*?*/                     // translate
//STRIP001 /*?*/                     aTransform.matrix[2] += aStartOffset.Width();
//STRIP001 /*?*/                     aTransform.matrix[5] += aStartOffset.Height();
//STRIP001 /*?*/                 }
//STRIP001 /*?*/             }
//STRIP001 /*?*/         }
//STRIP001 /*?*/
//STRIP001 /*?*/         SvtGraphicFill aFill( XOutCreatePolyPolygonBezier( aPolyPoly, rXOut.GetOutDev() ),
//STRIP001 /*?*/                               ITEMVALUE( rFillItemSet, XATTR_FILLCOLOR, XFillColorItem ),
//STRIP001 /*?*/                               ITEMVALUE( rFillItemSet, XATTR_FILLTRANSPARENCE, XFillTransparenceItem ) / 100.0,
//STRIP001 /*?*/                               SvtGraphicFill::fillEvenOdd,
//STRIP001 /*?*/                               eType,
//STRIP001 /*?*/                               aTransform,
//STRIP001 /*?*/                               SvtGraphicFill::fillTexture == eType ? bTile : false,
//STRIP001 /*?*/                               eHatch,
//STRIP001 /*?*/                               aHatch.GetColor(),
//STRIP001 /*?*/                               eGrad,
//STRIP001 /*?*/                               aGradient.GetStartColor(),
//STRIP001 /*?*/                               aGradient.GetEndColor(),
//STRIP001 /*?*/                               0 == aGradient.GetSteps() ? SvtGraphicFill::gradientStepsInfinite : aGradient.GetSteps(), // 0 means adaptive/infinite step count
//STRIP001 /*?*/                               aFillGraphic );
//STRIP001 /*?*/
//STRIP001 /*?*/ #ifdef DBG_UTIL
//STRIP001 /*?*/         ::rtl::OString aStr( aFill.toString() );
//STRIP001 /*?*/ #endif
//STRIP001 /*?*/
//STRIP001 /*?*/         SvMemoryStream aMemStm;
//STRIP001 /*?*/
//STRIP001 /*?*/         aMemStm << aFill;
//STRIP001 /*?*/
//STRIP001 /*?*/         pMtf->AddAction( new MetaCommentAction( "XPATHFILL_SEQ_BEGIN", 0,
//STRIP001 /*?*/                                                 static_cast<const BYTE*>(aMemStm.GetData()),
//STRIP001 /*?*/
//STRIP001 /*?*/                                                 aMemStm.Seek( STREAM_SEEK_TO_END ) ) );
//STRIP001 /*?*/         mbCommentWritten = true;
/*?*/     }
/*N*/ }

// #100127# Bracket filled output with a comment, if recording a Mtf
/*N*/ ImpGraphicFill::~ImpGraphicFill()
/*N*/ {
/*N*/     GDIMetaFile* pMtf=NULL;
/*N*/     if( mbCommentWritten &&
/*N*/         (pMtf=mrXOut.GetOutDev()->GetConnectMetaFile()) )
/*N*/     {
/*?*/         pMtf->AddAction( new MetaCommentAction( "XPATHFILL_SEQ_END" ) );
/*N*/     }
/*N*/ }

///////////////////////////////////////////////////////////////////////////////

// #104609# Extracted from XOutputDevice::ImpCalcBmpFillStartValues
//STRIP001 void ImpCalcBmpFillSizes( Size&             rStartOffset,
//STRIP001                           Size&             rBmpOutputSize,
//STRIP001                           const Rectangle& rOutputRect,
//STRIP001                           const MapMode&   rOutputMapMode,
//STRIP001                           const Bitmap&    rFillBitmap,
//STRIP001                           const Size&      rBmpSize,
//STRIP001                           const Size&      rBmpPerCent,
//STRIP001                           const Size&       rBmpOffPerCent,
//STRIP001                           BOOL             bBmpLogSize,
//STRIP001                           BOOL             bBmpTile,
//STRIP001                           BOOL             bBmpStretch,
//STRIP001                           RECT_POINT       eBmpRectPoint )
//STRIP001 {
//STRIP001  BOOL    bOriginalSize = FALSE, bScaleSize = FALSE;
//STRIP001
//STRIP001  // Falls keine Groessen gegeben sind ( z.B. alte Dokumente )
//STRIP001  // berechnen wir uns die Groesse selber aus der Bitmap
//STRIP001  // ==> altes Verhalten;
//STRIP001  // wenn nur eine Groesse gegeben ist, wird die andere
//STRIP001  // Groesse angepasst berechnet
//STRIP001  if( bBmpLogSize )
//STRIP001  {
//STRIP001      if( !rBmpSize.Width() && !rBmpSize.Height() )
//STRIP001          bOriginalSize = TRUE;
//STRIP001      else if( !rBmpSize.Width() || !rBmpSize.Height() )
//STRIP001          bScaleSize = TRUE;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( !rBmpPerCent.Width() && !rBmpPerCent.Height() )
//STRIP001          bOriginalSize = TRUE;
//STRIP001      else if( !rBmpPerCent.Width() || !rBmpPerCent.Height() )
//STRIP001          bScaleSize = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  // entweder Originalgroesse oder angepasste Groesse
//STRIP001  if( bOriginalSize || bScaleSize )
//STRIP001  {
//STRIP001      MapMode aBmpPrefMapMode( rFillBitmap.GetPrefMapMode() );
//STRIP001      Size    aBmpPrefSize( rFillBitmap.GetPrefSize() );
//STRIP001
//STRIP001      // Falls keine gesetzt ist, nehmen wir Pixel
//STRIP001      if( !aBmpPrefSize.Width() || !aBmpPrefSize.Height() )
//STRIP001         {
//STRIP001          aBmpPrefSize = rFillBitmap.GetSizePixel();
//STRIP001             aBmpPrefMapMode = MAP_PIXEL;
//STRIP001         }
//STRIP001
//STRIP001      if( bOriginalSize )
//STRIP001      {
//STRIP001          if( MAP_PIXEL == aBmpPrefMapMode.GetMapUnit() )
//STRIP001              rBmpOutputSize = Application::GetDefaultDevice()->PixelToLogic( aBmpPrefSize, rOutputMapMode );
//STRIP001          else
//STRIP001              rBmpOutputSize = OutputDevice::LogicToLogic( aBmpPrefSize, aBmpPrefMapMode, rOutputMapMode );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if( bBmpLogSize )
//STRIP001          {
//STRIP001              rBmpOutputSize = rBmpSize;
//STRIP001
//STRIP001              if( !rBmpSize.Width() )
//STRIP001                  rBmpOutputSize.Width() = FRound( (double) rBmpSize.Height() * aBmpPrefSize.Width() / aBmpPrefSize.Height() );
//STRIP001              else
//STRIP001                  rBmpOutputSize.Height() = FRound( (double) rBmpSize.Width() * aBmpPrefSize.Height() / aBmpPrefSize.Width() );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              if( !rBmpPerCent.Width() )
//STRIP001              {
//STRIP001                  rBmpOutputSize.Height() = FRound( (double) rOutputRect.GetHeight() * rBmpPerCent.Height() / 100. );
//STRIP001                  rBmpOutputSize.Width() = FRound( (double) rBmpOutputSize.Height() * aBmpPrefSize.Width() / aBmpPrefSize.Height() );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  rBmpOutputSize.Width() = FRound( (double) rOutputRect.GetWidth() * rBmpPerCent.Width() / 100. );
//STRIP001                  rBmpOutputSize.Height() = FRound( (double) rBmpOutputSize.Width() * aBmpPrefSize.Height() / aBmpPrefSize.Width() );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  // ansonsten koennen wir die Groesse leicht selber berechnen
//STRIP001  else
//STRIP001  {
//STRIP001      if( bBmpLogSize )
//STRIP001          rBmpOutputSize = rBmpSize;
//STRIP001      else
//STRIP001      {
//STRIP001          rBmpOutputSize.Width() = FRound( (double) rOutputRect.GetWidth() * rBmpPerCent.Width() / 100. );
//STRIP001          rBmpOutputSize.Height() = FRound( (double) rOutputRect.GetHeight() * rBmpPerCent.Height() / 100. );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // nur bei Kachelung die anderen Positionen berechnen
//STRIP001  if( bBmpTile )
//STRIP001  {
//STRIP001         Point aStartPoint;
//STRIP001
//STRIP001      // Grundposition der ersten Kachel berechen;
//STRIP001      // Diese Position wird spaeter zur Berechnung der absoluten
//STRIP001      // Startposition links oberhalb des Objektes benutzt
//STRIP001      switch( eBmpRectPoint )
//STRIP001      {
//STRIP001          case( RP_MT ):
//STRIP001          {
//STRIP001              aStartPoint.X() = rOutputRect.Left() + ( ( rOutputRect.GetWidth() - rBmpOutputSize.Width() ) >> 1 );
//STRIP001              aStartPoint.Y() = rOutputRect.Top();
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001          case( RP_RT ):
//STRIP001          {
//STRIP001              aStartPoint.X() = rOutputRect.Right() - rBmpOutputSize.Width();
//STRIP001              aStartPoint.Y() = rOutputRect.Top();
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001          case( RP_LM ):
//STRIP001          {
//STRIP001              aStartPoint.X() = rOutputRect.Left();
//STRIP001              aStartPoint.Y() = rOutputRect.Top() + ( ( rOutputRect.GetHeight() - rBmpOutputSize.Height() ) >> 1  );
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001          case( RP_MM ):
//STRIP001          {
//STRIP001              aStartPoint.X() = rOutputRect.Left() + ( ( rOutputRect.GetWidth() - rBmpOutputSize.Width() ) >> 1 );
//STRIP001              aStartPoint.Y() = rOutputRect.Top() + ( ( rOutputRect.GetHeight() - rBmpOutputSize.Height() ) >> 1 );
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001          case( RP_RM ):
//STRIP001          {
//STRIP001              aStartPoint.X() = rOutputRect.Right() - rBmpOutputSize.Width();
//STRIP001              aStartPoint.Y() = rOutputRect.Top() + ( ( rOutputRect.GetHeight() - rBmpOutputSize.Height() ) >> 1 );
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001          case( RP_LB ):
//STRIP001          {
//STRIP001              aStartPoint.X() = rOutputRect.Left();
//STRIP001              aStartPoint.Y() = rOutputRect.Bottom() - rBmpOutputSize.Height();
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001          case( RP_MB ):
//STRIP001          {
//STRIP001              aStartPoint.X() = rOutputRect.Left() + ( ( rOutputRect.GetWidth() - rBmpOutputSize.Width() ) >> 1 );
//STRIP001              aStartPoint.Y() = rOutputRect.Bottom() - rBmpOutputSize.Height();
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001          case( RP_RB ):
//STRIP001          {
//STRIP001              aStartPoint.X() = rOutputRect.Right() - rBmpOutputSize.Width();
//STRIP001              aStartPoint.Y() = rOutputRect.Bottom() - rBmpOutputSize.Height();
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001          // default linke obere Ecke
//STRIP001          default:
//STRIP001              aStartPoint = rOutputRect.TopLeft();
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      // X- oder Y-Positionsoffset beruecksichtigen
//STRIP001      if( rBmpOffPerCent.Width() )
//STRIP001          aStartPoint.X() += ( rBmpOutputSize.Width() * rBmpOffPerCent.Width() / 100 );
//STRIP001
//STRIP001         if( rBmpOffPerCent.Height() )
//STRIP001          aStartPoint.Y() += ( rBmpOutputSize.Height() * rBmpOffPerCent.Height() / 100 );
//STRIP001
//STRIP001      // echten Startpunkt berechnen ( links oben )
//STRIP001      if( rBmpOutputSize.Width() && rBmpOutputSize.Height() )
//STRIP001      {
//STRIP001          const long nDiffX = aStartPoint.X() - rOutputRect.Left();
//STRIP001          const long nDiffY = aStartPoint.Y() - rOutputRect.Top();
//STRIP001
//STRIP001          if ( nDiffX )
//STRIP001          {
//STRIP001              long nCount = nDiffX / rBmpOutputSize.Width() + 1;
//STRIP001
//STRIP001              if ( rBmpOffPerCent.Height() && ( nCount & 1L ) )
//STRIP001                  nCount++;
//STRIP001
//STRIP001              aStartPoint.X() -= ( nCount * rBmpOutputSize.Width() );
//STRIP001          }
//STRIP001
//STRIP001          if ( nDiffY )
//STRIP001          {
//STRIP001              long nCount = nDiffY / rBmpOutputSize.Height() + 1;
//STRIP001
//STRIP001              if ( rBmpOffPerCent.Width() && ( nCount & 1L ) )
//STRIP001                  nCount++;
//STRIP001
//STRIP001              aStartPoint.Y() -= ( nCount * rBmpOutputSize.Height() );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001         rStartOffset = Size( aStartPoint.X() - rOutputRect.Left(),
//STRIP001                              aStartPoint.Y() - rOutputRect.Top() );
//STRIP001  }
//STRIP001     else
//STRIP001     {
//STRIP001         if( bBmpStretch )
//STRIP001         {
//STRIP001             rStartOffset = Size(0, 0);
//STRIP001             rBmpOutputSize = rOutputRect.GetSize();
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             rStartOffset = Size( ( rOutputRect.GetWidth() - rBmpOutputSize.Width() ) >> 1,
//STRIP001                                  ( rOutputRect.GetHeight() - rBmpOutputSize.Height() ) >> 1 );
//STRIP001         }
//STRIP001     }
//STRIP001 }
