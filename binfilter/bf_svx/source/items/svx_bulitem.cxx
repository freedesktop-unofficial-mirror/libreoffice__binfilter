/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <vcl/outdev.hxx>

#define _SVX_BULITEM_CXX

#include "bulitem.hxx"

// #90477#
#include <tools/tenccvt.hxx>
#include <bf_tools/string.hxx>
namespace binfilter {

#define BULITEM_VERSION     ((USHORT)2)

// -----------------------------------------------------------------------

/*N*/ TYPEINIT1(SvxBulletItem,SfxPoolItem);

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
/*N*/   nTemp = (sal_uInt16)GetSOLoadTextEncoding((rtl_TextEncoding)nTemp);
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
/*N*/   String aName = rStream.ReadUniOrByteString(rStream.GetStreamCharSet());
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


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


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
/*?*/             pGraphicObject = new BfGraphicObject( aBmp );
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
/*N*/   aPrevText = rStrm.ReadUniOrByteString(rStrm.GetStreamCharSet());
/*N*/
/*N*/   // UNICODE: rStrm >> aFollowText;
/*N*/   aFollowText = rStrm.ReadUniOrByteString(rStrm.GetStreamCharSet());
/*N*/
/*N*/   nValidMask = 0xFFFF;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxBulletItem::SvxBulletItem( const SvxBulletItem& rItem) : SfxPoolItem( rItem )
/*N*/ {
/*N*/   aFont           = rItem.aFont;
/*N*/     pGraphicObject    = ( rItem.pGraphicObject ? new BfGraphicObject( *rItem.pGraphicObject ) : NULL );
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

/*N*/ SfxPoolItem* SvxBulletItem::Clone( SfxItemPool* /*pPool*/ ) const
/*N*/ {
/*N*/   return new SvxBulletItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxBulletItem::Create( SvStream& rStrm, USHORT /*nVersion*/ ) const
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

/*N*/ USHORT SvxBulletItem::GetVersion( USHORT /*nVersion*/ ) const
/*N*/ {
/*N*/   return BULITEM_VERSION;
/*N*/ }

// -----------------------------------------------------------------------



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
/*?*/             ( ( !(*pGraphicObject == *rBullet.pGraphicObject) ) ||
/*?*/               ( pGraphicObject->GetPrefSize() != rBullet.pGraphicObject->GetPrefSize() ) ) )
/*?*/         {
/*?*/             return 0;
/*N*/         }
/*N*/     }
/*N*/
/*N*/   return 1;
/*N*/ }


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
