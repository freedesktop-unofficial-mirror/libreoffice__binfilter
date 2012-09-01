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

#include <bf_svtools/itempool.hxx>
#include <bf_svtools/itemset.hxx>

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "request.hxx"

namespace binfilter {

/*N*/ const SfxPoolItem* SfxRequest::GetItem
/*N*/ (
/*N*/   const SfxItemSet* pArgs,
/*N*/   USHORT          nSlotId,    // Slot-Id oder Which-Id des Parameters
/*N*/   bool        bDeep,      // FALSE: nicht in Parent-ItemSets suchen
/*N*/   TypeId          aType       // != 0:  RTTI Pruefung mit Assertion
/*N*/ )
/*N*/ {
/*N*/   if ( pArgs )
/*N*/   {
/*N*/       // ggf. in Which-Id umrechnen
/*N*/       USHORT nWhich = pArgs->GetPool()->GetWhich(nSlotId);
/*N*/
/*N*/       // ist das Item gesetzt oder bei bDeep==TRUE verf"ugbar?
/*N*/       const SfxPoolItem *pItem = 0;
/*N*/       if ( ( bDeep ? SFX_ITEM_AVAILABLE : SFX_ITEM_SET )
/*N*/            <= pArgs->GetItemState( nWhich, bDeep, &pItem ) )
/*N*/       {
/*N*/           // stimmt der Typ "uberein?
/*N*/           if ( !pItem || pItem->IsA(aType) )
/*N*/               return pItem;
/*N*/
/*N*/           // Item da aber falsch => Programmierfehler
/*N*/           OSL_FAIL(  "invalid argument type" );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // keine Parameter, nicht gefunden oder falschen Typ gefunden
/*N*/   return 0;
/*N*/ }
}
/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
