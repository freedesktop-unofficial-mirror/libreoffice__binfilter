/*************************************************************************
 *
 *  $RCSfile: svx_bulitem.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 16:02:10 $
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

// include ---------------------------------------------------------------

// auto strip #ifndef _STREAM_HXX
// auto strip #include <tools/stream.hxx>
// auto strip #endif
//#ifndef _SV_SYSTEM_HXX
//#include <vcl/system.hxx>
//#endif
#pragma hdrstop

#include <vcl/outdev.hxx>

#define _SVX_BULITEM_CXX

#include "bulitem.hxx"
// auto strip #include "svxerr.hxx"

// #90477#
#ifndef _TOOLS_TENCCVT_HXX
#include <tools/tenccvt.hxx>
#endif
namespace binfilter {

#define BULITEM_VERSION     ((USHORT)2)

// -----------------------------------------------------------------------

/*N*/ TYPEINIT1(SvxBulletItem,SfxPoolItem);

// -----------------------------------------------------------------------

/*N*/ void SvxBulletItem::StoreFont( SvStream& rStream, const Font& rFont )
/*N*/ {
/*N*/   USHORT nTemp;
/*N*/
/*N*/   rStream << rFont.GetColor();
/*N*/   nTemp = (USHORT)rFont.GetFamily(); rStream << nTemp;
/*N*/
/*N*/   // #90477# nTemp = (USHORT)GetStoreCharSet( rFont.GetCharSet(), rStream.GetVersion() );
/*N*/   nTemp = (USHORT)GetSOStoreTextEncoding((rtl_TextEncoding)rFont.GetCharSet(), (sal_uInt16)rStream.GetVersion());
/*N*/   rStream << nTemp;
/*N*/
/*N*/   nTemp = (USHORT)rFont.GetPitch(); rStream << nTemp;
/*N*/   nTemp = (USHORT)rFont.GetAlign(); rStream << nTemp;
/*N*/   nTemp = (USHORT)rFont.GetWeight(); rStream << nTemp;
/*N*/   nTemp = (USHORT)rFont.GetUnderline(); rStream << nTemp;
/*N*/   nTemp = (USHORT)rFont.GetStrikeout(); rStream << nTemp;
/*N*/   nTemp = (USHORT)rFont.GetItalic(); rStream << nTemp;
/*N*/
/*N*/   // UNICODE: rStream << rFont.GetName();
/*N*/   rStream.WriteByteString(rFont.GetName());
/*N*/
/*N*/   rStream << rFont.IsOutline();
/*N*/   rStream << rFont.IsShadow();
/*N*/   rStream << rFont.IsTransparent();
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ Font SvxBulletItem::CreateFont( SvStream& rStream, USHORT nVer )
/*N*/ {
/*N*/   Font aFont;
/*N*/   Color aColor;
/*N*/   rStream >> aColor;    aFont.SetColor( aColor );
/*N*/   USHORT nTemp;
/*N*/   rStream >> nTemp; aFont.SetFamily((FontFamily)nTemp);
/*N*/
/*N*/   // #90477#
/*N*/   rStream >> nTemp;
/*N*/   nTemp = (sal_uInt16)GetSOLoadTextEncoding((rtl_TextEncoding)nTemp, (sal_uInt16)rStream.GetVersion());
/*N*/   aFont.SetCharSet((rtl_TextEncoding)nTemp);
/*N*/
/*N*/   rStream >> nTemp; aFont.SetPitch((FontPitch)nTemp);
/*N*/   rStream >> nTemp; aFont.SetAlign((FontAlign)nTemp);
/*N*/   rStream >> nTemp; aFont.SetWeight((FontWeight)nTemp);
/*N*/   rStream >> nTemp; aFont.SetUnderline((FontUnderline)nTemp);
/*N*/   rStream >> nTemp; aFont.SetStrikeout((FontStrikeout)nTemp);
/*N*/   rStream >> nTemp; aFont.SetItalic((FontItalic)nTemp);
/*N*/
/*N*/   // UNICODE: rStream >> aName; aFont.SetName( aName );
/*N*/   String aName;
/*N*/   rStream.ReadByteString(aName);
/*N*/   aFont.SetName( aName );
/*N*/
/*N*/   if( nVer == 1 )
/*N*/   {
/*N*/       long nHeight, nWidth;
/*?*/       rStream >> nHeight; rStream >> nWidth; Size aSize( nWidth, nHeight );
/*?*/       aFont.SetSize( aSize );
/*N*/   }
/*N*/
/*N*/   BOOL bTemp;
/*N*/   rStream >> bTemp; aFont.SetOutline( bTemp );
/*N*/   rStream >> bTemp; aFont.SetShadow( bTemp );
/*N*/   rStream >> bTemp; aFont.SetTransparent( bTemp );
/*N*/   return aFont;
/*N*/ }


// -----------------------------------------------------------------------

/*N*/ SvxBulletItem::SvxBulletItem( USHORT nWhich ) : SfxPoolItem( nWhich )
/*N*/ {
/*N*/   SetDefaultFont_Impl();
/*N*/   SetDefaults_Impl();
/*N*/   nValidMask = 0xFFFF;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 SvxBulletItem::SvxBulletItem( BYTE nNewStyle, const Font& rFont, USHORT nStart,  USHORT nWhich ) : SfxPoolItem( nWhich )
//STRIP001 {
//STRIP001  SetDefaults_Impl();
//STRIP001  nStyle = nNewStyle;
//STRIP001  aFont  = rFont;
//STRIP001  nValidMask = 0xFFFF;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SvxBulletItem::SvxBulletItem( const Font& rFont, xub_Unicode cSymb, USHORT nWhich ) : SfxPoolItem( nWhich )
//STRIP001 {
//STRIP001  SetDefaults_Impl();
//STRIP001  aFont   = rFont;
//STRIP001  cSymbol = cSymb;
//STRIP001  nStyle  = BS_BULLET;
//STRIP001  nValidMask = 0xFFFF;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SvxBulletItem::SvxBulletItem( const Bitmap& rBmp, USHORT nWhich ) : SfxPoolItem( nWhich )
//STRIP001 {
//STRIP001  SetDefaults_Impl();
//STRIP001
//STRIP001     if( !rBmp.IsEmpty() )
//STRIP001     {
//STRIP001         pGraphicObject = new GraphicObject( rBmp );
//STRIP001      nStyle = BS_BMP;
//STRIP001     }
//STRIP001
//STRIP001  nValidMask = 0xFFFF;
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 SvxBulletItem::SvxBulletItem( const GraphicObject& rGraphicObject, USHORT nWhich ) : SfxPoolItem( nWhich )
//STRIP001 {
//STRIP001  SetDefaults_Impl();
//STRIP001
//STRIP001     if( ( GRAPHIC_NONE != pGraphicObject->GetType() ) && ( GRAPHIC_DEFAULT != pGraphicObject->GetType() ) )
//STRIP001     {
//STRIP001         pGraphicObject = new GraphicObject( rGraphicObject );
//STRIP001         nStyle = BS_BMP;
//STRIP001     }
//STRIP001
//STRIP001     nValidMask = 0xFFFF;
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ SvxBulletItem::SvxBulletItem( SvStream& rStrm, USHORT nWhich ) :
/*N*/     SfxPoolItem( nWhich ),
/*N*/     pGraphicObject( NULL )
/*N*/ {
/*N*/   rStrm >> nStyle;
/*N*/
/*N*/   if( nStyle != BS_BMP )
/*N*/       aFont = CreateFont( rStrm, BULITEM_VERSION );
/*N*/   else
/*N*/   {
/*N*/       // Sicheres Laden mit Test auf leere Bitmap
/*?*/       Bitmap          aBmp;
/*?*/       const UINT32    nOldPos = rStrm.Tell();
/*?*/         // #69345# Errorcode beim Bitmap lesen ignorieren,
/*?*/       // siehe Kommentar #67581# in SvxBulletItem::Store()
/*?*/       BOOL bOldError = rStrm.GetError() ? TRUE : FALSE;
/*?*/       rStrm >> aBmp;
/*?*/       if ( !bOldError && rStrm.GetError() )
/*?*/       {
/*?*/           rStrm.ResetError();
/*?*/           // #71493# Keine Warnung: Das BulletItem interessiert seit 5.0 im Dateiformat nicht mehr.
/*?*/           // rStrm.SetError(ERRCODE_CLASS_READ | ERRCODE_SVX_BULLETITEM_NOBULLET | ERRCODE_WARNING_MASK);
/*?*/       }
/*?*/
/*?*/       if( aBmp.IsEmpty() )
/*?*/       {
/*?*/           rStrm.Seek( nOldPos );
/*?*/           nStyle = BS_NONE;
/*?*/       }
/*?*/       else
/*?*/             pGraphicObject = new GraphicObject( aBmp );
/*N*/   }
/*N*/
/*N*/     rStrm >> nWidth;
/*N*/   rStrm >> nStart;
/*N*/   rStrm >> nJustify;
/*N*/
/*N*/   char cTmpSymbol;
/*N*/   rStrm >> cTmpSymbol;
/*N*/   cSymbol = ByteString::ConvertToUnicode( cTmpSymbol, aFont.GetCharSet() );
/*N*/
/*N*/   rStrm >> nScale;
/*N*/
/*N*/   // UNICODE: rStrm >> aPrevText;
/*N*/   rStrm.ReadByteString(aPrevText);
/*N*/
/*N*/   // UNICODE: rStrm >> aFollowText;
/*N*/   rStrm.ReadByteString(aFollowText);
/*N*/
/*N*/   nValidMask = 0xFFFF;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxBulletItem::SvxBulletItem( const SvxBulletItem& rItem) : SfxPoolItem( rItem )
/*N*/ {
/*N*/   aFont           = rItem.aFont;
/*N*/     pGraphicObject    = ( rItem.pGraphicObject ? new GraphicObject( *rItem.pGraphicObject ) : NULL );
/*N*/   aPrevText       = rItem.aPrevText;
/*N*/   aFollowText     = rItem.aFollowText;
/*N*/   nStart          = rItem.nStart;
/*N*/   nStyle          = rItem.nStyle;
/*N*/   nWidth          = rItem.nWidth;
/*N*/   nScale          = rItem.nScale;
/*N*/   cSymbol         = rItem.cSymbol;
/*N*/   nJustify        = rItem.nJustify;
/*N*/   nValidMask      = rItem.nValidMask;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxBulletItem::~SvxBulletItem()
/*N*/ {
/*N*/     if( pGraphicObject )
/*?*/         delete pGraphicObject;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxBulletItem::Clone( SfxItemPool *pPool ) const
/*N*/ {
/*N*/   return new SvxBulletItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxBulletItem::Create( SvStream& rStrm, USHORT nVersion ) const
/*N*/ {
/*N*/   return new SvxBulletItem( rStrm, Which() );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ void SvxBulletItem::SetDefaultFont_Impl()
/*N*/ {
/*N*/   aFont = OutputDevice::GetDefaultFont( DEFAULTFONT_FIXED, LANGUAGE_SYSTEM, 0 );
/*N*/   aFont.SetAlign( ALIGN_BOTTOM);
/*N*/   aFont.SetTransparent( TRUE );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ void SvxBulletItem::SetDefaults_Impl()
/*N*/ {
/*N*/     pGraphicObject  = NULL;
/*N*/   nWidth          = 1200;  // 1.2cm
/*N*/   nStart          = 1;
/*N*/   nStyle          = BS_123;
/*N*/   nJustify        = BJ_HLEFT | BJ_VCENTER;
/*N*/   cSymbol         = sal_Unicode(' ');
/*N*/   nScale          = 75;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ USHORT SvxBulletItem::GetVersion( USHORT nVersion ) const
/*N*/ {
/*N*/   return BULITEM_VERSION;
/*N*/ }

// -----------------------------------------------------------------------

//STRIP001 void SvxBulletItem::CopyValidProperties( const SvxBulletItem& rCopyFrom )
//STRIP001 {
//STRIP001  Font aFont = GetFont();
//STRIP001  Font aNewFont = rCopyFrom.GetFont();
//STRIP001  if ( rCopyFrom.IsValid( VALID_FONTNAME ) )
//STRIP001  {
//STRIP001      aFont.SetName( aNewFont.GetName() );
//STRIP001      aFont.SetFamily( aNewFont.GetFamily() );
//STRIP001      aFont.SetStyleName( aNewFont.GetStyleName() );
//STRIP001  }
//STRIP001  if ( rCopyFrom.IsValid( VALID_FONTCOLOR ) )
//STRIP001      aFont.SetColor( aNewFont.GetColor() );
//STRIP001  if ( rCopyFrom.IsValid( VALID_SYMBOL ) )
//STRIP001      SetSymbol( rCopyFrom.GetSymbol() );
//STRIP001  if ( rCopyFrom.IsValid( VALID_BITMAP ) )
//STRIP001      SetGraphicObject( rCopyFrom.GetGraphicObject() );
//STRIP001  if ( rCopyFrom.IsValid( VALID_SCALE ) )
//STRIP001      SetScale( rCopyFrom.GetScale() );
//STRIP001  if ( rCopyFrom.IsValid( VALID_START ) )
//STRIP001      SetStart( rCopyFrom.GetStart() );
//STRIP001  if ( rCopyFrom.IsValid( VALID_STYLE ) )
//STRIP001      SetStyle( rCopyFrom.GetStyle() );
//STRIP001  if ( rCopyFrom.IsValid( VALID_PREVTEXT ) )
//STRIP001      SetPrevText( rCopyFrom.GetPrevText() );
//STRIP001  if ( rCopyFrom.IsValid( VALID_FOLLOWTEXT ) )
//STRIP001      SetFollowText( rCopyFrom.GetFollowText() );
//STRIP001
//STRIP001  SetFont( aFont );
//STRIP001 }


// -----------------------------------------------------------------------

/*N*/ int SvxBulletItem::operator==( const SfxPoolItem& rItem ) const
/*N*/ {
/*N*/   DBG_ASSERT(rItem.ISA(SvxBulletItem),"operator==Types not matching");
/*N*/   const SvxBulletItem& rBullet = (const SvxBulletItem&)rItem;
/*N*/   // ValidMask mitvergleichen, da sonst kein Putten in ein AttrSet moeglich,
/*N*/   // wenn sich das Item nur in der ValidMask von einem existierenden unterscheidet.
/*N*/   if( nValidMask != rBullet.nValidMask    ||
/*N*/       nStyle != rBullet.nStyle            ||
/*N*/       nScale != rBullet.nScale            ||
/*N*/       nJustify != rBullet.nJustify        ||
/*N*/       nWidth != rBullet.nWidth            ||
/*N*/       nStart != rBullet.nStart            ||
/*N*/       cSymbol != rBullet.cSymbol          ||
/*N*/       aPrevText != rBullet.aPrevText      ||
/*N*/       aFollowText != rBullet.aFollowText )
/*N*/           return 0;
/*N*/
/*N*/   if( ( nStyle != BS_BMP ) && ( aFont != rBullet.aFont ) )
/*N*/       return 0;
/*N*/
/*N*/     if( nStyle == BS_BMP )
/*N*/     {
/*?*/         if( ( pGraphicObject && !rBullet.pGraphicObject ) || ( !pGraphicObject && rBullet.pGraphicObject ) )
/*?*/             return 0;
/*?*/
/*?*/         if( ( pGraphicObject && rBullet.pGraphicObject ) &&
/*?*/             ( ( *pGraphicObject != *rBullet.pGraphicObject ) ||
/*?*/               ( pGraphicObject->GetPrefSize() != rBullet.pGraphicObject->GetPrefSize() ) ) )
/*?*/         {
/*?*/             return 0;
/*N*/         }
/*N*/     }
/*N*/
/*N*/   return 1;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvStream& SvxBulletItem::Store( SvStream& rStrm, USHORT nItemVersion ) const
/*N*/ {
/*N*/   // Korrektur bei leerer Bitmap
/*N*/   if( ( nStyle == BS_BMP ) &&
/*N*/         ( !pGraphicObject || ( GRAPHIC_NONE == pGraphicObject->GetType() ) || ( GRAPHIC_DEFAULT == pGraphicObject->GetType() ) ) )
/*N*/   {
/*?*/         if( pGraphicObject )
/*?*/         {
/*?*/             delete( const_cast< SvxBulletItem* >( this )->pGraphicObject );
/*?*/             const_cast< SvxBulletItem* >( this )->pGraphicObject = NULL;
/*?*/         }
/*?*/
/*?*/         const_cast< SvxBulletItem* >( this )->nStyle = BS_NONE;
/*N*/   }
/*N*/
/*N*/   rStrm << nStyle;
/*N*/
/*N*/   if( nStyle != BS_BMP )
/*N*/       StoreFont( rStrm, aFont );
/*N*/   else
/*N*/   {
/*?*/       ULONG nStart = rStrm.Tell();
/*?*/
/*?*/       // Kleine Vorab-Schaetzung der Groesse...
/*?*/       USHORT nFac = ( rStrm.GetCompressMode() != COMPRESSMODE_NONE ) ? 3 : 1;
/*?*/       const Bitmap aBmp( pGraphicObject->GetGraphic().GetBitmap() );
/*?*/       ULONG nBytes = aBmp.GetSizeBytes();
/*?*/       if ( nBytes < ULONG(0xFF00*nFac) )
/*?*/           rStrm << aBmp;
/*?*/
/*?*/       ULONG nEnd = rStrm.Tell();
/*?*/       // #67581# Item darf mit Overhead nicht mehr als 64K schreiben,
/*?*/       // sonst platzt der SfxMultiRecord
/*?*/       // Dann lieber auf die Bitmap verzichten, ist nur fuer Outliner
/*?*/       // und auch nur fuer <= 5.0 wichtig.
/*?*/       // Beim Einlesen merkt der Stream-Operator der Bitmap, dass dort keine steht.
/*?*/       // Hiermit funktioniert jetzt der Fall das die grosse Bitmap aus einem anderen
/*?*/       // Fileformat entstanden ist, welches keine 64K belegt, aber wenn eine
/*?*/       // Bitmap > 64K verwendet wird, hat das SvxNumBulletItem beim Laden ein Problem,
/*?*/       // stuerzt aber nicht ab.
/*?*/
/*?*/       if ( (nEnd-nStart) > 0xFF00 )
/*?*/           rStrm.Seek( nStart );
/*N*/   }
/*N*/   rStrm << nWidth;
/*N*/   rStrm << nStart;
/*N*/   rStrm << nJustify;
/*N*/   rStrm << (char)ByteString::ConvertFromUnicode( cSymbol, aFont.GetCharSet() );
/*N*/   rStrm << nScale;
/*N*/
/*N*/   // UNICODE: rStrm << aPrevText;
/*N*/   rStrm.WriteByteString(aPrevText);
/*N*/
/*N*/   // UNICODE: rStrm << aFollowText;
/*N*/   rStrm.WriteByteString(aFollowText);
/*N*/
/*N*/   return rStrm;
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 XubString SvxBulletItem::GetFullText() const
//STRIP001 {
//STRIP001  XubString aStr( aPrevText );
//STRIP001  aStr += cSymbol;
//STRIP001  aStr += aFollowText;
//STRIP001  return aStr;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxItemPresentation SvxBulletItem::GetPresentation
//STRIP001 (
//STRIP001  SfxItemPresentation ePres,
//STRIP001  SfxMapUnit          eCoreUnit,
//STRIP001  SfxMapUnit          ePresUnit,
//STRIP001     XubString&          rText, const IntlWrapper *
//STRIP001 )    const
//STRIP001 {
//STRIP001  SfxItemPresentation eRet = SFX_ITEM_PRESENTATION_NONE;
//STRIP001  switch ( ePres )
//STRIP001  {
//STRIP001      case SFX_ITEM_PRESENTATION_NONE:
//STRIP001          rText.Erase();
//STRIP001          eRet = SFX_ITEM_PRESENTATION_NONE;
//STRIP001          break;
//STRIP001
//STRIP001      case SFX_ITEM_PRESENTATION_NAMELESS:
//STRIP001      case SFX_ITEM_PRESENTATION_COMPLETE:
//STRIP001          rText = GetFullText();
//STRIP001          eRet = SFX_ITEM_PRESENTATION_COMPLETE;
//STRIP001          break;
//STRIP001  }
//STRIP001  return eRet;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 Bitmap SvxBulletItem::GetBitmap() const
//STRIP001 {
//STRIP001     if( pGraphicObject )
//STRIP001         return pGraphicObject->GetGraphic().GetBitmap();
//STRIP001     else
//STRIP001     {
//STRIP001         const Bitmap aDefaultBitmap;
//STRIP001         return aDefaultBitmap;
//STRIP001     }
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 void SvxBulletItem::SetBitmap( const Bitmap& rBmp )
//STRIP001 {
//STRIP001     if( rBmp.IsEmpty() )
//STRIP001     {
//STRIP001         if( pGraphicObject )
//STRIP001         {
//STRIP001             delete pGraphicObject;
//STRIP001             pGraphicObject = NULL;
//STRIP001         }
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         delete pGraphicObject;
//STRIP001         pGraphicObject = new GraphicObject( rBmp );
//STRIP001
//STRIP001     }
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 const GraphicObject& SvxBulletItem::GetGraphicObject() const
//STRIP001 {
//STRIP001     if( pGraphicObject )
//STRIP001         return *pGraphicObject;
//STRIP001     else
//STRIP001     {
//STRIP001         static const GraphicObject aDefaultObject;
//STRIP001         return aDefaultObject;
//STRIP001     }
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 void SvxBulletItem::SetGraphicObject( const GraphicObject& rGraphicObject )
//STRIP001 {
//STRIP001     if( ( GRAPHIC_NONE == rGraphicObject.GetType() ) || ( GRAPHIC_DEFAULT == rGraphicObject.GetType() ) )
//STRIP001     {
//STRIP001         if( pGraphicObject )
//STRIP001         {
//STRIP001             delete pGraphicObject;
//STRIP001             pGraphicObject = NULL;
//STRIP001         }
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         delete pGraphicObject;
//STRIP001         pGraphicObject = new GraphicObject( rGraphicObject );
//STRIP001     }
//STRIP001 }
}
