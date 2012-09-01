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


#include <vcl/splitwin.hxx>
#include <bf_svtools/itemset.hxx>
#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "frmdescr.hxx"
#include "app.hxx"
#include "bf_so3/staticbaseurl.hxx"
namespace binfilter {

/*N*/ DBG_NAME(SfxFrameDescriptor)

#define VERSION (USHORT) 3

/*N*/ struct SfxFrameSetDescriptor_Impl
/*N*/ {
/*N*/   Wallpaper*  pWallpaper;
/*N*/   Bitmap*     pBitmap;
/*N*/   BOOL        bNetscapeCompat;
/*N*/ };

/*N*/ struct SfxFrameDescriptor_Impl
/*N*/ {
/*N*/   Wallpaper*  pWallpaper;
/*N*/   SfxItemSet* pArgs;
/*N*/   BOOL        bEditable;
/*N*/
/*N*/   SfxFrameDescriptor_Impl() : pWallpaper( NULL ), pArgs( NULL ), bEditable( TRUE ) {}
/*N*/   ~SfxFrameDescriptor_Impl()
/*N*/   {
/*N*/       delete pWallpaper;
/*N*/       delete pArgs;
/*N*/   }
/*N*/ };

/*N*/ SfxFrameDescriptor::SfxFrameDescriptor( SfxFrameSetDescriptor *pParSet ) :
/*N*/   pParentFrameSet( pParSet ),
/*N*/   pFrameSet( 0L ),
/*N*/   aMargin( -1, -1 ),
/*N*/   nWidth( 0L ),
/*N*/   eScroll( ScrollingAuto ),
/*N*/   eSizeSelector( SIZE_ABS ),
/*N*/   nHasBorder( BORDER_YES ),
/*N*/   nItemId( 0 ),
/*N*/   bResizeHorizontal( TRUE ),
/*N*/   bResizeVertical( TRUE ),
/*N*/   bHasUI( TRUE ),
/*N*/   bReadOnly( FALSE )
/*N*/ {
/*N*/   DBG_CTOR(SfxFrameDescriptor, 0);
/*N*/
/*N*/   pImp = new SfxFrameDescriptor_Impl;
/*N*/ }

/*N*/ SfxFrameDescriptor::~SfxFrameDescriptor()
/*N*/ {
/*N*/   DBG_DTOR(SfxFrameDescriptor, 0);
/*N*/
/*N*/   if ( pFrameSet )
/*N*/       delete pFrameSet;
/*N*/   delete pImp;
/*N*/ }

/*N*/ SfxFrameProperties&   SfxFrameProperties::operator =(
/*N*/   const SfxFrameProperties &rProp )
/*N*/ {
/*N*/   aURL = rProp.aURL;
/*N*/   aName = rProp.aName;
/*N*/   lMarginWidth = rProp.lMarginWidth;
/*N*/   lMarginHeight = rProp.lMarginHeight;
/*N*/   lSize = rProp.lSize;
/*N*/   lSetSize = rProp.lSetSize;
/*N*/   lFrameSpacing = rProp.lFrameSpacing;
/*N*/   lInheritedFrameSpacing = rProp.lInheritedFrameSpacing;
/*N*/   eScroll = rProp.eScroll;
/*N*/   eSizeSelector = rProp.eSizeSelector;
/*N*/   eSetSizeSelector = rProp.eSetSizeSelector;
/*N*/   bHasBorder = rProp.bHasBorder;
/*N*/   bBorderSet = rProp.bBorderSet;
/*N*/   bResizable = rProp.bResizable;
/*N*/   bSetResizable = rProp.bSetResizable;
/*N*/   bIsRootSet = rProp.bIsRootSet;
/*N*/   bIsInColSet = rProp.bIsInColSet;
/*N*/   bHasBorderInherited = rProp.bHasBorderInherited;
/*N*/   pFrame = NULL;
/*N*/   return *this;
/*N*/ }

/*N*/ int SfxFrameProperties::operator ==( const SfxFrameProperties& rProp ) const
/*N*/ {
/*N*/   return aURL == rProp.aURL && aName == rProp.aName && lMarginWidth == rProp.lMarginWidth && lMarginHeight == rProp.lMarginHeight &&
/*N*/           lSize == rProp.lSize && eScroll == rProp.eScroll && eSizeSelector == rProp.eSizeSelector &&
/*N*/           lSetSize == rProp.lSetSize && lFrameSpacing == rProp.lFrameSpacing && eSetSizeSelector == rProp.eSetSizeSelector &&
/*N*/           bHasBorder == rProp.bHasBorder && bBorderSet == rProp.bBorderSet &&
/*N*/           bResizable == rProp.bResizable && bSetResizable == rProp.bSetResizable;
/*N*/ }

/*?*/ TYPEINIT1(SfxFrameDescriptorItem, SfxPoolItem);

/*?*/ SfxFrameDescriptorItem::~SfxFrameDescriptorItem()
/*?*/ {}

/*?*/ int SfxFrameDescriptorItem::operator==( const SfxPoolItem& rAttr ) const
/*?*/ {
/*?*/   DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );
/*?*/
/*?*/   return aProperties == ((SfxFrameDescriptorItem&)rAttr).aProperties;
/*?*/ }

// -----------------------------------------------------------------------

/*?*/ SfxPoolItem* SfxFrameDescriptorItem::Clone( SfxItemPool* ) const
/*?*/ {
/*?*/   return new SfxFrameDescriptorItem( *this );
/*?*/ }

//------------------------------------------------------------------------

/*?*/ SfxItemPresentation SfxFrameDescriptorItem::GetPresentation
/*?*/ (
/*?*/   SfxItemPresentation /*ePres*/,
/*?*/   SfxMapUnit          /*eCoreUnit*/,
/*?*/   SfxMapUnit          /*ePresUnit*/,
/*?*/   XubString&          rText,
/*?*/     const ::IntlWrapper *
/*?*/ ) const
/*?*/ {
/*?*/   rText.Erase();
/*?*/   return SFX_ITEM_PRESENTATION_NONE;
/*?*/ }


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
