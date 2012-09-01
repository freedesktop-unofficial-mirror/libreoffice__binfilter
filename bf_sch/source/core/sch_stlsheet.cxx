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

#include <bf_svx/eeitem.hxx>

#include <bf_svx/xdef.hxx>


#include <bf_svtools/itemset.hxx>

#include <bf_svtools/smplhint.hxx>

#include "stlsheet.hxx"
namespace binfilter {

/*N*/ TYPEINIT1(SchStyleSheet, SfxStyleSheet);


/*************************************************************************
|*
|* Ctor
|*
\************************************************************************/

/*N*/ SchStyleSheet::SchStyleSheet(const String& rName, SfxStyleSheetBasePool& rInPool,
/*N*/                            SfxStyleFamily eFamily, USHORT nInMask) :
/*N*/   SfxStyleSheet(rName, rInPool, eFamily, nInMask)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Dtor
|*
\************************************************************************/

/*N*/ SchStyleSheet::~SchStyleSheet()
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Load
|*
\************************************************************************/

/*N*/ void SchStyleSheet::Load (SvStream&, USHORT)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Parent setzen
|*
\************************************************************************/

/*N*/ BOOL SchStyleSheet::SetParent(const String& rParentName)
/*N*/ {
/*N*/   if (SfxStyleSheet::SetParent(rParentName))
/*N*/   {
/*N*/       SfxStyleSheetBase* pStyle = rPool.Find(rParentName, nFamily);
/*N*/
/*N*/       if (pStyle)
/*N*/       {
/*?*/           SfxItemSet& rParentSet = pStyle->GetItemSet();
/*?*/           GetItemSet().SetParent(&rParentSet);
/*?*/           Broadcast(SfxSimpleHint(SFX_HINT_DATACHANGED));
/*?*/
/*?*/           return TRUE;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return FALSE;
/*N*/ }

/*************************************************************************
|*
|* ItemSet ggfs. erzeugen und herausreichen
|*
\************************************************************************/

/*N*/ SfxItemSet& SchStyleSheet::GetItemSet()
/*N*/ {
/*N*/   if (!pSet)
/*N*/   {
/*N*/       USHORT nWhichPairTable[] = { XATTR_LINE_FIRST, XATTR_LINE_LAST,
/*N*/                                    XATTR_FILL_FIRST, XATTR_FILL_LAST,
/*N*/                                    EE_PARA_START, EE_CHAR_END,
/*N*/                                    (USHORT)0 };
/*N*/
/*N*/       pSet = new SfxItemSet(GetPool().GetPool(), nWhichPairTable);
/*N*/       bMySet = TRUE; //Eigentum erklaeren, damit der DTor der Basisklasse den
/*N*/                      //Set wieder abraeumt.
/*N*/   }
/*N*/
/*N*/   return *pSet;
/*N*/ }

/*************************************************************************
|*
|* IsUsed(), wird an Listeners erkannt
|*
\************************************************************************/

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
