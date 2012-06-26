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

#include <com/sun/star/drawing/Direction3D.hpp>
#include <tools/stream.hxx>
#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "e3ditem.hxx"
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;

// STATIC DATA -----------------------------------------------------------

/*N*/ DBG_NAME(SvxVector3DItem)

// -----------------------------------------------------------------------

/*N*/ TYPEINIT1_AUTOFACTORY(SvxVector3DItem, SfxPoolItem);

// -----------------------------------------------------------------------

/*N*/ SvxVector3DItem::SvxVector3DItem( USHORT nWhich, const Vector3D& rVal ) :
/*N*/   SfxPoolItem( nWhich ),
/*N*/   aVal( rVal )
/*N*/ {
/*N*/   DBG_CTOR(SvxVector3DItem, 0);
/*N*/ }

// -----------------------------------------------------------------------


// -----------------------------------------------------------------------

/*N*/ SvxVector3DItem::SvxVector3DItem( const SvxVector3DItem& rItem ) :
/*N*/   SfxPoolItem( rItem ),
/*N*/   aVal( rItem.aVal )
/*N*/ {
/*N*/   DBG_CTOR(SvxVector3DItem, 0);
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ int SvxVector3DItem::operator==( const SfxPoolItem &rItem ) const
/*N*/ {
/*N*/   DBG_CHKTHIS(SvxVector3DItem, 0);
/*N*/   DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal type" );
/*N*/   return ((SvxVector3DItem&)rItem).aVal == aVal;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxVector3DItem::Clone( SfxItemPool* /*pPool*/ ) const
/*N*/ {
/*N*/   DBG_CHKTHIS(SvxVector3DItem, 0);
/*N*/   return new SvxVector3DItem( *this );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ SfxPoolItem* SvxVector3DItem::Create(SvStream &rStream, USHORT /*nVersion*/) const
/*N*/ {
/*N*/   DBG_CHKTHIS(SvxVector3DItem, 0);
/*N*/   Vector3D aStr;
/*N*/   rStream >> aStr;
/*N*/   return new SvxVector3DItem(Which(), aStr);
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ bool SvxVector3DItem::QueryValue( uno::Any& rVal, BYTE /*nMemberId*/ ) const
/*N*/ {
/*N*/   drawing::Direction3D aDirection;
/*N*/
/*N*/   // Werte eintragen
/*N*/   aDirection.DirectionX = aVal.X();
/*N*/   aDirection.DirectionY = aVal.Y();
/*N*/   aDirection.DirectionZ = aVal.Z();
/*N*/
/*N*/   rVal <<= aDirection;
/*N*/   return( sal_True );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ bool SvxVector3DItem::PutValue( const uno::Any& rVal, BYTE /*nMemberId*/ )
/*N*/ {
/*N*/   drawing::Direction3D aDirection;
/*N*/   if(!(rVal >>= aDirection))
/*N*/       return sal_False;
/*N*/
/*N*/   aVal.X() = aDirection.DirectionX;
/*N*/   aVal.Y() = aDirection.DirectionY;
/*N*/   aVal.Z() = aDirection.DirectionZ;
/*N*/   return sal_True;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ USHORT SvxVector3DItem::GetVersion (USHORT nFileFormatVersion) const
/*N*/ {
/*N*/   return (nFileFormatVersion == SOFFICE_FILEFORMAT_31) ? USHRT_MAX : 0;
/*N*/ }


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
