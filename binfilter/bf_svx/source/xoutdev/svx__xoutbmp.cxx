/*************************************************************************
 *
 *  $RCSfile: svx__xoutbmp.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:21:09 $
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

#include <sot/factory.hxx>
#include <tools/urlobj.hxx>
#include <unotools/ucbstreamhelper.hxx>
#include <vcl/bmpacc.hxx>
#include <vcl/poly.hxx>
#include <vcl/virdev.hxx>
#include <vcl/wrkwin.hxx>
#include <svtools/solar.hrc>
#include <bf_sfx2/docfile.hxx>
#include <bf_sfx2/app.hxx>
#include "impgrf.hxx"
#include "xoutbmp.hxx"
#include <svtools/FilterConfigItem.hxx>

// -----------
// - Defines -
// -----------

#define FORMAT_BMP  String(RTL_CONSTASCII_USTRINGPARAM("bmp"))
#define FORMAT_GIF  String(RTL_CONSTASCII_USTRINGPARAM("gif"))
#define FORMAT_JPG  String(RTL_CONSTASCII_USTRINGPARAM("jpg"))
#define FORMAT_PNG  String(RTL_CONSTASCII_USTRINGPARAM("png"))

// --------------
// - XOutBitmap -
// --------------

GraphicFilter* XOutBitmap::pGrfFilter = NULL;

// -----------------------------------------------------------------------------

//STRIP001 BitmapEx XOutBitmap::CreateQuickDrawBitmapEx( const Graphic& rGraphic, const OutputDevice& rCompDev,
//STRIP001                                            const MapMode& rMapMode, const Size& rLogSize,
//STRIP001                                            const Point& rPoint, const Size& rSize )
//STRIP001 {
//STRIP001  BitmapEx aRetBmp;
//STRIP001
//STRIP001  if( rGraphic.IsAlpha() )
//STRIP001      aRetBmp = rGraphic.GetBitmapEx();
//STRIP001  else
//STRIP001  {
//STRIP001      VirtualDevice   aVDev( rCompDev );
//STRIP001      MapMode         aMap( rMapMode );
//STRIP001
//STRIP001      aMap.SetOrigin( Point() );
//STRIP001      aVDev.SetMapMode( aMap );
//STRIP001
//STRIP001      Point   aPoint( aVDev.LogicToPixel( rPoint ) );
//STRIP001      Size    aOldSize( aVDev.LogicToPixel( rSize ) );
//STRIP001      Size    aAbsSize( aOldSize );
//STRIP001      Size    aQSizePix( aVDev.LogicToPixel( rLogSize ) );
//STRIP001
//STRIP001      aVDev.SetMapMode( MapMode() );
//STRIP001
//STRIP001      if( aOldSize.Width() < 0 )
//STRIP001          aAbsSize.Width() = -aAbsSize.Width();
//STRIP001
//STRIP001      if( aOldSize.Height() < 0 )
//STRIP001          aAbsSize.Height() = -aAbsSize.Height();
//STRIP001
//STRIP001      if( aVDev.SetOutputSizePixel( aAbsSize ) )
//STRIP001      {
//STRIP001          Point       aNewOrg( -aPoint.X(), -aPoint.Y() );
//STRIP001          const Point aNullPoint;
//STRIP001
//STRIP001          // horizontale Spiegelung ggf. beruecksichtigen
//STRIP001          if( aOldSize.Width() < 0 )
//STRIP001          {
//STRIP001              aNewOrg.X() -= aOldSize.Width();
//STRIP001
//STRIP001              // und jetzt noch einen abziehen
//STRIP001              aNewOrg.X()--;
//STRIP001          }
//STRIP001
//STRIP001          // vertikale Spiegelung ggf. beruecksichtigen
//STRIP001          if( rSize.Height() < 0 )
//STRIP001          {
//STRIP001              aNewOrg.Y() -= aOldSize.Height();
//STRIP001
//STRIP001              // und jetzt noch einen abziehen
//STRIP001              aNewOrg.Y()--;
//STRIP001          }
//STRIP001
//STRIP001          if( rGraphic.GetType() != GRAPHIC_BITMAP )
//STRIP001          {
//STRIP001              rGraphic.Draw( &aVDev, aNewOrg, aQSizePix );
//STRIP001
//STRIP001              const Bitmap    aBmp( aVDev.GetBitmap( aNullPoint, aAbsSize ) );
//STRIP001              Bitmap          aMask;
//STRIP001
//STRIP001              Graphic( rGraphic.GetGDIMetaFile().GetMonochromeMtf( COL_BLACK ) ).Draw( &aVDev, aNewOrg, aQSizePix );
//STRIP001              aMask = aVDev.GetBitmap( aNullPoint, aAbsSize );
//STRIP001              aRetBmp = BitmapEx( aBmp, aMask );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              Bitmap  aBmp( rGraphic.GetBitmap() );
//STRIP001
//STRIP001 // UNX has got problems with 1x1 bitmaps which are transparent (KA 02.11.1998)
//STRIP001 #ifdef UNX
//STRIP001              const Size  aBmpSize( aBmp.GetSizePixel() );
//STRIP001              BOOL        bFullTrans = FALSE;
//STRIP001
//STRIP001              if( aBmpSize.Width() == 1 && aBmpSize.Height() == 1 && rGraphic.IsTransparent() )
//STRIP001              {
//STRIP001                  Bitmap              aTrans( rGraphic.GetBitmapEx().GetMask() );
//STRIP001                  BitmapReadAccess*   pMAcc = aBmp.AcquireReadAccess();
//STRIP001
//STRIP001                  if( pMAcc )
//STRIP001                  {
//STRIP001                      if( pMAcc->GetColor( 0, 0 ) == BitmapColor( Color( COL_WHITE ) ) )
//STRIP001                          bFullTrans = TRUE;
//STRIP001
//STRIP001                      aTrans.ReleaseAccess( pMAcc );
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              if( !bFullTrans )
//STRIP001 #endif // UNX
//STRIP001
//STRIP001              {
//STRIP001                  DitherBitmap( aBmp );
//STRIP001                  aVDev.DrawBitmap( aNewOrg, aQSizePix, aBmp );
//STRIP001                  aBmp = aVDev.GetBitmap( aNullPoint, aAbsSize );
//STRIP001
//STRIP001                  if( !rGraphic.IsTransparent() )
//STRIP001                      aRetBmp = BitmapEx( aBmp );
//STRIP001                  else
//STRIP001                  {
//STRIP001                      Bitmap  aTrans( rGraphic.GetBitmapEx().GetMask() );
//STRIP001
//STRIP001                      if( !aTrans )
//STRIP001                          aRetBmp = BitmapEx( aBmp, rGraphic.GetBitmapEx().GetTransparentColor() );
//STRIP001                      else
//STRIP001                      {
//STRIP001                          aVDev.DrawBitmap( aNewOrg, aQSizePix, aTrans );
//STRIP001                          aRetBmp = BitmapEx( aBmp, aVDev.GetBitmap( Point(), aAbsSize ) );
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return aRetBmp;
//STRIP001 }
//STRIP001
//STRIP001 // ------------------------------------------------------------------------
//STRIP001
//STRIP001 void XOutBitmap::DrawQuickDrawBitmapEx( OutputDevice* pOutDev, const Point& rPt,
//STRIP001                                      const Size& rSize, const BitmapEx& rBmpEx )
//STRIP001 {
//STRIP001  const Size      aBmpSizePix( rBmpEx.GetSizePixel() );
//STRIP001  const Size      aSizePix( pOutDev->LogicToPixel( rSize ) );
//STRIP001
//STRIP001  if ( ( aSizePix.Width() - aBmpSizePix.Width() ) || ( aSizePix.Height() - aBmpSizePix.Height() ) )
//STRIP001      rBmpEx.Draw( pOutDev, rPt, rSize );
//STRIP001  else
//STRIP001      rBmpEx.Draw( pOutDev, rPt );
//STRIP001 }
//STRIP001
//STRIP001 // ------------------------------------------------------------------------
//STRIP001
//STRIP001 void XOutBitmap::DrawTiledBitmapEx( OutputDevice* pOutDev,
//STRIP001                                  const Point& rStartPt, const Size& rGrfSize,
//STRIP001                                  const Rectangle& rTileRect, const BitmapEx& rBmpEx )
//STRIP001 {
//STRIP001  Rectangle       aClipRect( pOutDev->LogicToPixel( pOutDev->GetClipRegion().GetBoundRect() ) );
//STRIP001  Rectangle       aPixRect( pOutDev->LogicToPixel( rTileRect ) );
//STRIP001  const Size      aPixSize( pOutDev->LogicToPixel( rGrfSize ) );
//STRIP001  const Point     aPixPoint( pOutDev->LogicToPixel( rStartPt ) );
//STRIP001  Point           aOrg;
//STRIP001  const long      nWidth = aPixSize.Width();
//STRIP001  const long      nHeight = aPixSize.Height();
//STRIP001  long            nXPos = aPixPoint.X() + ( ( aPixRect.Left() - aPixPoint.X() ) / nWidth ) * nWidth;
//STRIP001  long            nYPos = aPixPoint.Y() + ( ( aPixRect.Top() - aPixPoint.Y() ) / nHeight ) * nHeight;
//STRIP001  const long      nBottom = aPixRect.Bottom();
//STRIP001  const long      nRight = aPixRect.Right();
//STRIP001  const long      nLeft = nXPos;
//STRIP001  const BOOL      bNoSize = ( aPixSize == rBmpEx.GetSizePixel() );
//STRIP001
//STRIP001  pOutDev->Push();
//STRIP001  pOutDev->SetMapMode( MapMode() );
//STRIP001
//STRIP001  // ggf. neue ClipRegion berechnen und setzen
//STRIP001  if ( pOutDev->IsClipRegion() )
//STRIP001      aPixRect.Intersection( aClipRect );
//STRIP001
//STRIP001  pOutDev->SetClipRegion( aPixRect );
//STRIP001
//STRIP001  while( nYPos <= nBottom )
//STRIP001  {
//STRIP001      while( nXPos <= nRight )
//STRIP001      {
//STRIP001          if ( bNoSize )
//STRIP001              rBmpEx.Draw( pOutDev, Point( nXPos, nYPos ) );
//STRIP001          else
//STRIP001              rBmpEx.Draw( pOutDev, Point( nXPos, nYPos ), aPixSize );
//STRIP001
//STRIP001          nXPos += nWidth;
//STRIP001      }
//STRIP001
//STRIP001      nXPos = nLeft;
//STRIP001      nYPos += nHeight;
//STRIP001  }
//STRIP001
//STRIP001  pOutDev->Pop();
//STRIP001 }
//STRIP001
//STRIP001 // ------------------------------------------------------------------------
//STRIP001
//STRIP001 Animation XOutBitmap::MirrorAnimation( const Animation& rAnimation, BOOL bHMirr, BOOL bVMirr )
//STRIP001 {
//STRIP001  Animation aNewAnim( rAnimation );
//STRIP001
//STRIP001  if( bHMirr || bVMirr )
//STRIP001  {
//STRIP001      const Size& rGlobalSize = aNewAnim.GetDisplaySizePixel();
//STRIP001      ULONG       nMirrorFlags = 0L;
//STRIP001
//STRIP001      if( bHMirr )
//STRIP001          nMirrorFlags |= BMP_MIRROR_HORZ;
//STRIP001
//STRIP001      if( bVMirr )
//STRIP001          nMirrorFlags |= BMP_MIRROR_VERT;
//STRIP001
//STRIP001      for( USHORT i = 0, nCount = aNewAnim.Count(); i < nCount; i++ )
//STRIP001      {
//STRIP001          AnimationBitmap aAnimBmp( aNewAnim.Get( i ) );
//STRIP001
//STRIP001          // BitmapEx spiegeln
//STRIP001          aAnimBmp.aBmpEx.Mirror( nMirrorFlags );
//STRIP001
//STRIP001          // Die Positionen innerhalb der Gesamtbitmap
//STRIP001          // muessen natuerlich auch angepasst werden
//STRIP001          if( bHMirr )
//STRIP001              aAnimBmp.aPosPix.X() = rGlobalSize.Width() - aAnimBmp.aPosPix.X() -
//STRIP001                                     aAnimBmp.aSizePix.Width();
//STRIP001
//STRIP001          if( bVMirr )
//STRIP001              aAnimBmp.aPosPix.Y() = rGlobalSize.Height() - aAnimBmp.aPosPix.Y() -
//STRIP001                                     aAnimBmp.aSizePix.Height();
//STRIP001
//STRIP001          aNewAnim.Replace( aAnimBmp, i );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return aNewAnim;
//STRIP001 }
//STRIP001
//STRIP001 // ------------------------------------------------------------------------
//STRIP001
//STRIP001 Graphic XOutBitmap::MirrorGraphic( const Graphic& rGraphic, const ULONG nMirrorFlags )
//STRIP001 {
//STRIP001  Graphic aRetGraphic;
//STRIP001
//STRIP001  if( nMirrorFlags )
//STRIP001  {
//STRIP001      if( rGraphic.IsAnimated() )
//STRIP001      {
//STRIP001          aRetGraphic = MirrorAnimation( rGraphic.GetAnimation(),
//STRIP001                                         ( nMirrorFlags & BMP_MIRROR_HORZ ) == BMP_MIRROR_HORZ,
//STRIP001                                         ( nMirrorFlags & BMP_MIRROR_VERT ) == BMP_MIRROR_VERT );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if( rGraphic.IsTransparent() )
//STRIP001          {
//STRIP001              BitmapEx aBmpEx( rGraphic.GetBitmapEx() );
//STRIP001
//STRIP001              aBmpEx.Mirror( nMirrorFlags );
//STRIP001              aRetGraphic = aBmpEx;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              Bitmap aBmp( rGraphic.GetBitmap() );
//STRIP001
//STRIP001              aBmp.Mirror( nMirrorFlags );
//STRIP001              aRetGraphic = aBmp;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      aRetGraphic = rGraphic;
//STRIP001
//STRIP001  return aRetGraphic;
//STRIP001 }
//STRIP001
//STRIP001 // ------------------------------------------------------------------------
//STRIP001
//STRIP001 USHORT XOutBitmap::WriteGraphic( const Graphic& rGraphic, String& rFileName,
//STRIP001                               const String& rFilterName, const ULONG nFlags,
//STRIP001                               const Size* pMtfSize_100TH_MM )
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  if( rGraphic.GetType() != GRAPHIC_NONE )
//STRIP001  {
//STRIP001      INetURLObject   aURL( rFileName );
//STRIP001      Graphic         aGraphic;
//STRIP001      String          aExt;
//STRIP001      GraphicFilter*  pFilter = GetGrfFilter();
//STRIP001      USHORT          nErr = GRFILTER_FILTERERROR, nFilter = GRFILTER_FORMAT_NOTFOUND;
//STRIP001      BOOL            bTransparent = rGraphic.IsTransparent(), bAnimated = rGraphic.IsAnimated();
//STRIP001
//STRIP001      DBG_ASSERT( aURL.GetProtocol() != INET_PROT_NOT_VALID, "XOutBitmap::WriteGraphic(...): invalid URL" );
//STRIP001
//STRIP001      // calculate correct file name
//STRIP001      if( !( nFlags & XOUTBMP_DONT_EXPAND_FILENAME ) )
//STRIP001      {
//STRIP001             String aName( aURL.getBase() );
//STRIP001             aName += '_';
//STRIP001             aName += aURL.getExtension();
//STRIP001             aName += '_';
//STRIP001             String aStr( String::CreateFromInt32( rGraphic.GetChecksum(), 16 ) );
//STRIP001             if ( aStr.GetChar(0) == '-' )
//STRIP001                 aStr.SetChar(0,'m');
//STRIP001             aName += aStr;
//STRIP001             aURL.setBase( aName );
//STRIP001      }
//STRIP001
//STRIP001      if( ( nFlags & XOUTBMP_USE_NATIVE_IF_POSSIBLE ) &&
//STRIP001          !( nFlags & XOUTBMP_MIRROR_HORZ ) &&
//STRIP001          !( nFlags & XOUTBMP_MIRROR_VERT ) &&
//STRIP001          ( rGraphic.GetType() != GRAPHIC_GDIMETAFILE ) && rGraphic.IsLink() )
//STRIP001      {
//STRIP001          // try to write native link
//STRIP001          const GfxLink aGfxLink( ( (Graphic&) rGraphic ).GetLink() );
//STRIP001
//STRIP001          switch( aGfxLink.GetType() )
//STRIP001          {
//STRIP001              case( GFX_LINK_TYPE_NATIVE_GIF ): aExt = FORMAT_GIF; break;
//STRIP001              case( GFX_LINK_TYPE_NATIVE_JPG ): aExt = FORMAT_JPG; break;
//STRIP001              case( GFX_LINK_TYPE_NATIVE_PNG ): aExt = FORMAT_PNG; break;
//STRIP001
//STRIP001              default:
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001          if( aExt.Len() )
//STRIP001          {
//STRIP001              aURL.setExtension( aExt );
//STRIP001              rFileName = aURL.GetMainURL( INetURLObject::NO_DECODE );
//STRIP001
//STRIP001              SfxMedium   aMedium( aURL.GetMainURL( INetURLObject::NO_DECODE ), STREAM_WRITE | STREAM_SHARE_DENYNONE | STREAM_TRUNC, TRUE );
//STRIP001              SvStream*   pOStm = aMedium.GetOutStream();
//STRIP001
//STRIP001              if( pOStm && aGfxLink.GetDataSize() )
//STRIP001              {
//STRIP001                  pOStm->Write( aGfxLink.GetData(), aGfxLink.GetDataSize() );
//STRIP001                  aMedium.Commit();
//STRIP001
//STRIP001                  if( !aMedium.GetError() )
//STRIP001                      nErr = GRFILTER_OK;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if( GRFILTER_OK != nErr )
//STRIP001      {
//STRIP001          String  aFilter( rFilterName );
//STRIP001          BOOL    bWriteTransGrf = ( aFilter.EqualsIgnoreCaseAscii( "transgrf" ) ) ||
//STRIP001                                   ( aFilter.EqualsIgnoreCaseAscii( "gif" ) ) ||
//STRIP001                                   ( nFlags & XOUTBMP_USE_GIF_IF_POSSIBLE ) ||
//STRIP001                                   ( ( nFlags & XOUTBMP_USE_GIF_IF_SENSIBLE ) && ( bAnimated || bTransparent ) );
//STRIP001
//STRIP001          // get filter and extension
//STRIP001          if( bWriteTransGrf )
//STRIP001              aFilter = FORMAT_GIF;
//STRIP001
//STRIP001          nFilter = pFilter->GetExportFormatNumberForShortName( aFilter );
//STRIP001
//STRIP001          if( GRFILTER_FORMAT_NOTFOUND == nFilter )
//STRIP001          {
//STRIP001              nFilter = pFilter->GetExportFormatNumberForShortName( FORMAT_JPG );
//STRIP001
//STRIP001              if( GRFILTER_FORMAT_NOTFOUND == nFilter )
//STRIP001                  nFilter = pFilter->GetExportFormatNumberForShortName( FORMAT_BMP );
//STRIP001          }
//STRIP001
//STRIP001          if( GRFILTER_FORMAT_NOTFOUND != nFilter )
//STRIP001          {
//STRIP001              aExt = pFilter->GetExportFormatShortName( nFilter ).ToLowerAscii();
//STRIP001
//STRIP001              if( bWriteTransGrf )
//STRIP001              {
//STRIP001                  if( bAnimated  )
//STRIP001                      aGraphic = rGraphic;
//STRIP001                  else
//STRIP001                  {
//STRIP001                      if( pMtfSize_100TH_MM && ( rGraphic.GetType() != GRAPHIC_BITMAP ) )
//STRIP001                      {
//STRIP001                          VirtualDevice aVDev;
//STRIP001                          const Size    aSize( aVDev.LogicToPixel( *pMtfSize_100TH_MM, MAP_100TH_MM ) );
//STRIP001
//STRIP001                          if( aVDev.SetOutputSizePixel( aSize ) )
//STRIP001                          {
//STRIP001                              const Wallpaper aWallpaper( aVDev.GetBackground() );
//STRIP001                              const Point     aPt;
//STRIP001
//STRIP001                              aVDev.SetBackground( Wallpaper( Color( COL_BLACK ) ) );
//STRIP001                              aVDev.Erase();
//STRIP001                              rGraphic.Draw( &aVDev, aPt, aSize );
//STRIP001
//STRIP001                              const Bitmap aBitmap( aVDev.GetBitmap( aPt, aSize ) );
//STRIP001
//STRIP001                              aVDev.SetBackground( aWallpaper );
//STRIP001                              aVDev.Erase();
//STRIP001                              rGraphic.Draw( &aVDev, aPt, aSize );
//STRIP001
//STRIP001                              aVDev.SetRasterOp( ROP_XOR );
//STRIP001                              aVDev.DrawBitmap( aPt, aSize, aBitmap );
//STRIP001                              aGraphic = BitmapEx( aBitmap, aVDev.GetBitmap( aPt, aSize ) );
//STRIP001                          }
//STRIP001                          else
//STRIP001                              aGraphic = rGraphic.GetBitmapEx();
//STRIP001                      }
//STRIP001                      else
//STRIP001                          aGraphic = rGraphic.GetBitmapEx();
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  if( pMtfSize_100TH_MM && ( rGraphic.GetType() != GRAPHIC_BITMAP ) )
//STRIP001                  {
//STRIP001                      VirtualDevice   aVDev;
//STRIP001                      const Size      aSize( aVDev.LogicToPixel( *pMtfSize_100TH_MM, MAP_100TH_MM ) );
//STRIP001
//STRIP001                      if( aVDev.SetOutputSizePixel( aSize ) )
//STRIP001                      {
//STRIP001                          rGraphic.Draw( &aVDev, Point(), aSize );
//STRIP001                          aGraphic =  aVDev.GetBitmap( Point(), aSize );
//STRIP001                      }
//STRIP001                      else
//STRIP001                          aGraphic = rGraphic.GetBitmap();
//STRIP001                  }
//STRIP001                  else
//STRIP001                      aGraphic = rGraphic.GetBitmap();
//STRIP001              }
//STRIP001
//STRIP001              // mirror?
//STRIP001              if( ( nFlags & XOUTBMP_MIRROR_HORZ ) || ( nFlags & XOUTBMP_MIRROR_VERT ) )
//STRIP001                  aGraphic = MirrorGraphic( aGraphic, nFlags );
//STRIP001
//STRIP001              if( ( GRFILTER_FORMAT_NOTFOUND != nFilter ) && ( aGraphic.GetType() != GRAPHIC_NONE ) )
//STRIP001              {
//STRIP001                  aURL.setExtension( aExt );
//STRIP001                  rFileName = aURL.GetMainURL( INetURLObject::NO_DECODE );
//STRIP001                  nErr = ExportGraphic( aGraphic, aURL, *pFilter, nFilter, TRUE, NULL );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      return nErr;
//STRIP001  }
//STRIP001  else
//STRIP001 #endif
//STRIP001      return GRFILTER_OK;
//STRIP001 }
//STRIP001
//STRIP001 // ------------------------------------------------------------------------
//STRIP001
/*N*/ #ifdef WNT
/*N*/ #pragma optimize ( "", off )
/*N*/ #endif
/*N*/
/*N*/ // SJ: bIgnoreOptions is not used anymore
/*N*/
/*N*/ USHORT XOutBitmap::ExportGraphic( const Graphic& rGraphic, const INetURLObject& rURL,
/*N*/                                 GraphicFilter& rFilter, const USHORT nFormat,
/*N*/                                 BOOL bIgnoreOptions,
/*N*/                                 const com::sun::star::uno::Sequence< com::sun::star::beans::PropertyValue >* pFilterData )
/*N*/ {DBG_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  DBG_ASSERT( rURL.GetProtocol() != INET_PROT_NOT_VALID, "XOutBitmap::ExportGraphic(...): invalid URL" );
//STRIP001
//STRIP001  SfxMedium   aMedium( rURL.GetMainURL( INetURLObject::NO_DECODE ), STREAM_WRITE | STREAM_SHARE_DENYNONE | STREAM_TRUNC, TRUE );
//STRIP001  SvStream*   pOStm = aMedium.GetOutStream();
//STRIP001  USHORT      nRet = 1;
//STRIP001
//STRIP001  if( pOStm )
//STRIP001  {
//STRIP001      pGrfFilter = &rFilter;
//STRIP001
//STRIP001      nRet = rFilter.ExportGraphic( rGraphic, rURL.GetMainURL( INetURLObject::NO_DECODE ),
//STRIP001                  *pOStm, nFormat, sal_True, pFilterData );
//STRIP001
//STRIP001      pGrfFilter = NULL;
//STRIP001      aMedium.Commit();
//STRIP001
//STRIP001      if( aMedium.GetError() && ( GRFILTER_OK == nRet  ) )
//STRIP001          nRet = 1;
//STRIP001  }
//STRIP001
//STRIP001  return nRet;
//STRIP001 #else
//STRIP001  return 1;
//STRIP001 #endif
/*N*/ }
//STRIP001
//STRIP001 #ifdef WNT
//STRIP001 #pragma optimize ( "", on )
//STRIP001 #endif
//STRIP001
//STRIP001 // ------------------------------------------------------------------------
//STRIP001
//STRIP001 Bitmap XOutBitmap::DetectEdges( const Bitmap& rBmp, const BYTE cThreshold )
//STRIP001 {
//STRIP001  const Size  aSize( rBmp.GetSizePixel() );
//STRIP001  Bitmap      aRetBmp;
//STRIP001  BOOL        bRet = FALSE;
//STRIP001
//STRIP001  if( ( aSize.Width() > 2L ) && ( aSize.Height() > 2L ) )
//STRIP001  {
//STRIP001      Bitmap aWorkBmp( rBmp );
//STRIP001
//STRIP001      if( aWorkBmp.Convert( BMP_CONVERSION_8BIT_GREYS ) )
//STRIP001      {
//STRIP001          Bitmap              aDstBmp( aSize, 1 );
//STRIP001          BitmapReadAccess*   pReadAcc = aWorkBmp.AcquireReadAccess();
//STRIP001          BitmapWriteAccess*  pWriteAcc = aDstBmp.AcquireWriteAccess();
//STRIP001
//STRIP001          if( pReadAcc && pWriteAcc )
//STRIP001          {
//STRIP001              const long          nWidth = aSize.Width();
//STRIP001              const long          nWidth2 = nWidth - 2L;
//STRIP001              const long          nHeight = aSize.Height();
//STRIP001              const long          nHeight2 = nHeight - 2L;
//STRIP001              const long          lThres2 = (long) cThreshold * cThreshold;
//STRIP001              const BitmapColor   aWhite = (BYTE) pWriteAcc->GetBestMatchingColor( Color( COL_WHITE ) );
//STRIP001              const BitmapColor   aBlack = (BYTE) pWriteAcc->GetBestMatchingColor( Color( COL_BLACK ) );
//STRIP001              long                nSum1;
//STRIP001              long                nSum2;
//STRIP001              long                lGray;
//STRIP001
//STRIP001              // Rand mit Weiss init.
//STRIP001              pWriteAcc->SetLineColor( Color( COL_WHITE) );
//STRIP001              pWriteAcc->DrawLine( Point(), Point( nWidth - 1L, 0L ) );
//STRIP001              pWriteAcc->DrawLine( Point( nWidth - 1L, 0L ), Point( nWidth - 1L, nHeight - 1L ) );
//STRIP001              pWriteAcc->DrawLine( Point( nWidth - 1L, nHeight - 1L ), Point( 0L, nHeight - 1L ) );
//STRIP001              pWriteAcc->DrawLine( Point( 0, nHeight - 1L ), Point() );
//STRIP001
//STRIP001              for( long nY = 0L, nY1 = 1L, nY2 = 2; nY < nHeight2; nY++, nY1++, nY2++ )
//STRIP001              {
//STRIP001                  for( long nX = 0L, nXDst = 1L, nXTmp; nX < nWidth2; nX++, nXDst++ )
//STRIP001                  {
//STRIP001                      nXTmp = nX;
//STRIP001
//STRIP001                      nSum1 = -( nSum2 = lGray = (BYTE) pReadAcc->GetPixel( nY, nXTmp++ ) );
//STRIP001                      nSum2 += ( (long) (BYTE) pReadAcc->GetPixel( nY, nXTmp++ ) ) << 1;
//STRIP001                      nSum1 += ( lGray = pReadAcc->GetPixel( nY, nXTmp ) );
//STRIP001                      nSum2 += lGray;
//STRIP001
//STRIP001                      nSum1 += ( (long) (BYTE) pReadAcc->GetPixel( nY1, nXTmp ) ) << 1;
//STRIP001                      nSum1 -= ( (long) (BYTE) pReadAcc->GetPixel( nY1, nXTmp -= 2 ) ) << 1;
//STRIP001
//STRIP001                      nSum1 += ( lGray = -(long) (BYTE) pReadAcc->GetPixel( nY2, nXTmp++ ) );
//STRIP001                      nSum2 += lGray;
//STRIP001                      nSum2 -= ( (long) (BYTE) pReadAcc->GetPixel( nY2, nXTmp++ ) ) << 1;
//STRIP001                      nSum1 += ( lGray = (long) (BYTE) pReadAcc->GetPixel( nY2, nXTmp ) );
//STRIP001                      nSum2 -= lGray;
//STRIP001
//STRIP001                      if( ( nSum1 * nSum1 + nSum2 * nSum2 ) < lThres2 )
//STRIP001                          pWriteAcc->SetPixel( nY1, nXDst, aWhite );
//STRIP001                      else
//STRIP001                          pWriteAcc->SetPixel( nY1, nXDst, aBlack );
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              bRet = TRUE;
//STRIP001          }
//STRIP001
//STRIP001          aWorkBmp.ReleaseAccess( pReadAcc );
//STRIP001          aDstBmp.ReleaseAccess( pWriteAcc );
//STRIP001
//STRIP001          if( bRet )
//STRIP001              aRetBmp = aDstBmp;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( !aRetBmp )
//STRIP001      aRetBmp = rBmp;
//STRIP001  else
//STRIP001  {
//STRIP001      aRetBmp.SetPrefMapMode( rBmp.GetPrefMapMode() );
//STRIP001      aRetBmp.SetPrefSize( rBmp.GetPrefSize() );
//STRIP001  }
//STRIP001
//STRIP001  return aRetBmp;
//STRIP001 };
//STRIP001
//STRIP001 // ------------------------------------------------------------------------
//STRIP001
//STRIP001 Polygon XOutBitmap::GetCountour( const Bitmap& rBmp, const ULONG nFlags,
//STRIP001                               const BYTE cEdgeDetectThreshold, const Rectangle* pWorkRectPixel )
//STRIP001 {
//STRIP001  Bitmap      aWorkBmp;
//STRIP001  Polygon     aRetPoly;
//STRIP001  Point       aTmpPoint;
//STRIP001  Rectangle   aWorkRect( aTmpPoint, rBmp.GetSizePixel() );
//STRIP001
//STRIP001  if( pWorkRectPixel )
//STRIP001      aWorkRect.Intersection( *pWorkRectPixel );
//STRIP001
//STRIP001  aWorkRect.Justify();
//STRIP001
//STRIP001  if( ( aWorkRect.GetWidth() > 4 ) && ( aWorkRect.GetHeight() > 4 ) )
//STRIP001  {
//STRIP001      // falls Flag gesetzt, muessen wir Kanten detektieren
//STRIP001      if( nFlags & XOUTBMP_CONTOUR_EDGEDETECT )
//STRIP001          aWorkBmp = DetectEdges( rBmp, cEdgeDetectThreshold );
//STRIP001      else
//STRIP001          aWorkBmp = rBmp;
//STRIP001
//STRIP001      BitmapReadAccess* pAcc = aWorkBmp.AcquireReadAccess();
//STRIP001
//STRIP001      if( pAcc )
//STRIP001      {
//STRIP001          const Size&         rPrefSize = aWorkBmp.GetPrefSize();
//STRIP001          const long          nWidth = pAcc->Width();
//STRIP001          const long          nHeight = pAcc->Height();
//STRIP001          const double        fFactorX = (double) rPrefSize.Width() / nWidth;
//STRIP001          const double        fFactorY = (double) rPrefSize.Height() / nHeight;
//STRIP001          const long          nStartX1 = aWorkRect.Left() + 1L;
//STRIP001          const long          nEndX1 = aWorkRect.Right();
//STRIP001          const long          nStartX2 = nEndX1 - 1L;
//STRIP001          const long          nEndX2 = nStartX1 - 1L;
//STRIP001          const long          nStartY1 = aWorkRect.Top() + 1L;
//STRIP001          const long          nEndY1 = aWorkRect.Bottom();
//STRIP001          const long          nStartY2 = nEndY1 - 1L;
//STRIP001          const long          nEndY2 = nStartY1 - 1L;
//STRIP001          Point*              pPoints1 = NULL;
//STRIP001          Point*              pPoints2 = NULL;
//STRIP001          long                nX, nY;
//STRIP001          USHORT              nPolyPos = 0;
//STRIP001          const BitmapColor   aBlack = pAcc->GetBestMatchingColor( Color( COL_BLACK ) );
//STRIP001
//STRIP001          if( nFlags & XOUTBMP_CONTOUR_VERT )
//STRIP001          {
//STRIP001              pPoints1 = new Point[ nWidth ];
//STRIP001              pPoints2 = new Point[ nWidth ];
//STRIP001
//STRIP001              for( nX = nStartX1; nX < nEndX1; nX++ )
//STRIP001              {
//STRIP001                  nY = nStartY1;
//STRIP001
//STRIP001                  // zunaechst Zeile von Links nach Rechts durchlaufen
//STRIP001                  while( nY < nEndY1 )
//STRIP001                  {
//STRIP001                      if( aBlack == pAcc->GetPixel( nY, nX ) )
//STRIP001                      {
//STRIP001                          pPoints1[ nPolyPos ] = Point( nX, nY );
//STRIP001                          nY = nStartY2;
//STRIP001
//STRIP001                          // diese Schleife wird immer gebreaked da hier ja min. ein Pixel ist
//STRIP001                          while( TRUE )
//STRIP001                          {
//STRIP001                              if( aBlack == pAcc->GetPixel( nY, nX ) )
//STRIP001                              {
//STRIP001                                  pPoints2[ nPolyPos ] = Point( nX, nY );
//STRIP001                                  break;
//STRIP001                              }
//STRIP001
//STRIP001                              nY--;
//STRIP001                          }
//STRIP001
//STRIP001                          nPolyPos++;
//STRIP001                          break;
//STRIP001                      }
//STRIP001
//STRIP001                      nY++;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              pPoints1 = new Point[ nHeight ];
//STRIP001              pPoints2 = new Point[ nHeight ];
//STRIP001
//STRIP001              for ( nY = nStartY1; nY < nEndY1; nY++ )
//STRIP001              {
//STRIP001                  nX = nStartX1;
//STRIP001
//STRIP001                  // zunaechst Zeile von Links nach Rechts durchlaufen
//STRIP001                  while( nX < nEndX1 )
//STRIP001                  {
//STRIP001                      if( aBlack == pAcc->GetPixel( nY, nX ) )
//STRIP001                      {
//STRIP001                          pPoints1[ nPolyPos ] = Point( nX, nY );
//STRIP001                          nX = nStartX2;
//STRIP001
//STRIP001                          // diese Schleife wird immer gebreaked da hier ja min. ein Pixel ist
//STRIP001                          while( TRUE )
//STRIP001                          {
//STRIP001                              if( aBlack == pAcc->GetPixel( nY, nX ) )
//STRIP001                              {
//STRIP001                                  pPoints2[ nPolyPos ] = Point( nX, nY );
//STRIP001                                  break;
//STRIP001                              }
//STRIP001
//STRIP001                              nX--;
//STRIP001                          }
//STRIP001
//STRIP001                          nPolyPos++;
//STRIP001                          break;
//STRIP001                      }
//STRIP001
//STRIP001                      nX++;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          const USHORT nNewSize1 = nPolyPos << 1;
//STRIP001
//STRIP001          aRetPoly = Polygon( nPolyPos, pPoints1 );
//STRIP001          aRetPoly.SetSize( nNewSize1 + 1 );
//STRIP001          aRetPoly[ nNewSize1 ] = aRetPoly[ 0 ];
//STRIP001
//STRIP001          for( USHORT j = nPolyPos; nPolyPos < nNewSize1; )
//STRIP001              aRetPoly[ nPolyPos++ ] = pPoints2[ --j ];
//STRIP001
//STRIP001          if( ( fFactorX != 0. ) && ( fFactorY != 0. ) )
//STRIP001              aRetPoly.Scale( fFactorX, fFactorY );
//STRIP001
//STRIP001          delete[] pPoints1;
//STRIP001          delete[] pPoints2;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return aRetPoly;
//STRIP001 };
//STRIP001
//STRIP001 // ----------------
//STRIP001 // - DitherBitmap -
//STRIP001 // ----------------
//STRIP001
//STRIP001 BOOL DitherBitmap( Bitmap& rBitmap )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001
//STRIP001  if( ( rBitmap.GetBitCount() >= 8 ) && ( Application::GetDefaultDevice()->GetColorCount() < 257 ) )
//STRIP001      bRet = rBitmap.Dither( BMP_DITHER_FLOYD );
//STRIP001  else
//STRIP001      bRet = FALSE;
//STRIP001
//STRIP001  return bRet;
//STRIP001 }
