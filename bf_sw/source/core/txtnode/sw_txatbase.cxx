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

#include <bf_svtools/itempool.hxx>
#include <txatbase.hxx>
namespace binfilter {

/*N*/ SwTxtAttr::SwTxtAttr( const SfxPoolItem& rAttr, xub_StrLen nStt )
/*N*/   : pAttr( &rAttr ), nStart( nStt )
/*N*/ {
/*N*/   bDontExpand = bLockExpandFlag = bDontMergeAttr = bDontMoveAttr =
/*N*/         bCharFmtAttr = bOverlapAllowedAttr = bPriorityAttr =
/*N*/       bDontExpandStart = FALSE;
/*N*/ }

/*N*/ SwTxtAttr::~SwTxtAttr( )
/*N*/ {
/*N*/ }

/*N*/ xub_StrLen* SwTxtAttr::GetEnd()
/*N*/ {
/*N*/   return 0;
/*N*/ }

    // RemoveFromPool muss immer vorm DTOR Aufruf erfolgen!!
    // Meldet sein Attribut beim Pool ab
/*N*/ void SwTxtAttr::RemoveFromPool( SfxItemPool& rPool )
/*N*/ {
/*N*/   rPool.Remove( GetAttr() );
/*N*/   pAttr = 0;
/*N*/ }


/*N*/ SwTxtAttrEnd::SwTxtAttrEnd( const SfxPoolItem& rAttr, xub_StrLen nS,
/*N*/                           xub_StrLen nE )
/*N*/   : SwTxtAttr( rAttr, nS ), nEnd( nE )
/*N*/ {
/*N*/ }

/*N*/ xub_StrLen* SwTxtAttrEnd::GetEnd()
/*N*/ {
/*N*/   return &nEnd;
/*N*/ }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
