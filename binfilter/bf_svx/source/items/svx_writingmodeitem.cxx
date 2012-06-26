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

#include <bf_svx/xdef.hxx>

#include "writingmodeitem.hxx"


#include "svxitems.hrc"
namespace binfilter {

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::text;

// class SvxWritingModeItem -------------------------------------------------

/*N*/ TYPEINIT1_AUTOFACTORY(SvxWritingModeItem, SfxUInt16Item);

/*N*/ SvxWritingModeItem::SvxWritingModeItem( WritingMode eValue, USHORT nWhich )
/*N*/   : SfxUInt16Item( nWhich, (sal_uInt16)eValue )
/*N*/ {
/*N*/ }

/*N*/ SvxWritingModeItem::~SvxWritingModeItem()
/*N*/ {
/*N*/ }

/*N*/ int SvxWritingModeItem::operator==( const SfxPoolItem& rCmp ) const
/*N*/ {
/*N*/   DBG_ASSERT( SfxPoolItem::operator==(rCmp), "unequal types" );
/*N*/
/*N*/   return GetValue() == ((SvxWritingModeItem&)rCmp).GetValue();
/*N*/ }

/*N*/ SfxPoolItem* SvxWritingModeItem::Clone( SfxItemPool * ) const
/*N*/ {
/*N*/   return new SvxWritingModeItem( *this );
/*N*/ }



/*N*/ USHORT SvxWritingModeItem::GetVersion( USHORT /*nFVer*/ ) const
/*N*/ {
/*N*/   return USHRT_MAX;
/*N*/ }



/*N*/ bool SvxWritingModeItem::QueryValue( ::com::sun::star::uno::Any& rVal,
/*N*/                                           BYTE ) const
/*N*/ {
/*N*/   rVal <<= (WritingMode)GetValue();
/*N*/   return true;
/*N*/ }

/*N*/ SvxWritingModeItem& SvxWritingModeItem::operator=( const SvxWritingModeItem& rItem )
/*N*/ {
/*N*/   SetValue( rItem.GetValue() );
/*N*/   return *this;
/*N*/ }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
