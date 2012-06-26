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

#include "zoomitem.hxx"
namespace binfilter {

// -----------------------------------------------------------------------

/*N*/ TYPEINIT1_AUTOFACTORY(SvxZoomItem,SfxUInt16Item);

// -----------------------------------------------------------------------

/*N*/ SvxZoomItem::SvxZoomItem
/*N*/ (
/*N*/   SvxZoomType eZoomType,
/*N*/   sal_uInt16      nVal,
/*N*/   sal_uInt16      nWhich
/*N*/ )
/*N*/ : SfxUInt16Item( nWhich, nVal ),
/*N*/   nValueSet( SVX_ZOOM_ENABLE_ALL ),
/*N*/   eType( eZoomType )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxZoomItem::SvxZoomItem( const SvxZoomItem& rOrig )
/*N*/ : SfxUInt16Item( rOrig.Which(), rOrig.GetValue() ),
/*N*/   nValueSet( rOrig.GetValueSet() ),
/*N*/   eType( rOrig.GetType() )
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SvxZoomItem::~SvxZoomItem()
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxZoomItem::Clone( SfxItemPool* /*pPool*/ ) const
/*N*/ {
/*N*/   return new SvxZoomItem( *this );
/*N*/ }

// -----------------------------------------------------------------------


// -----------------------------------------------------------------------


// -----------------------------------------------------------------------

/*N*/ int SvxZoomItem::operator==( const SfxPoolItem& rAttr ) const
/*N*/ {
/*N*/   DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );
/*N*/
/*N*/   SvxZoomItem& rItem = (SvxZoomItem&)rAttr;
/*N*/
/*N*/   return ( GetValue() == rItem.GetValue()     &&
/*N*/            nValueSet  == rItem.GetValueSet()  &&
/*N*/            eType      == rItem.GetType()          );
/*N*/ }


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
