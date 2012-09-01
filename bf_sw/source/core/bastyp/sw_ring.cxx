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

#include "ring.hxx"
namespace binfilter {


/*************************************************************************
|*
|*    Ring::Ring()
|*
*************************************************************************/

/*N*/ Ring::Ring( Ring *pObj )
/*N*/ {
/*N*/   if( !pObj )
/*N*/       pNext = this, pPrev = this;
/*N*/   else
/*N*/   {
/*?*/       pNext = pObj;
/*?*/       pPrev = pObj->pPrev;
/*?*/       pObj->pPrev = this;
/*?*/       pPrev->pNext = this;
/*N*/   }
}

/*************************************************************************
|*
|*    Ring::~Ring()
|*
*************************************************************************/

/*N*/ Ring::~Ring()
/*N*/ {
/*N*/   pNext->pPrev = pPrev;
/*N*/   pPrev->pNext = pNext;
/*N*/ }

/*************************************************************************
|*
|*    Ring::MoveTo
|*
*************************************************************************/

/*N*/ void Ring::MoveTo(Ring *pDestRing)
/*N*/ {
/*N*/   // loeschen aus dem alten
/*N*/   pNext->pPrev = pPrev;
/*N*/   pPrev->pNext = pNext;
/*N*/
/*N*/   // im neuen einfuegen
/*N*/   if( pDestRing )
/*N*/   {
/*N*/       pNext = pDestRing;
/*N*/       pPrev = pDestRing->pPrev;
/*N*/       pDestRing->pPrev = this;
/*N*/       pPrev->pNext = this;
/*N*/   }
/*N*/   else
/*N*/       pNext = pPrev = this;
/*N*/
/*N*/ }



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
