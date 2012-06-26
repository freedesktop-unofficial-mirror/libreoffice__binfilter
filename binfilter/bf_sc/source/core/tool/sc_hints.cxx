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

#include "hints.hxx"
namespace binfilter {

// -----------------------------------------------------------------------

/*N*/ TYPEINIT1(ScPaintHint, SfxHint);
/*N*/ TYPEINIT1(ScUpdateRefHint, SfxHint);
/*N*/ TYPEINIT1(ScPointerChangedHint, SfxHint);
/*N*/ TYPEINIT1(ScLinkRefreshedHint, SfxHint);
/*N*/ TYPEINIT1(ScAutoStyleHint, SfxHint);

// -----------------------------------------------------------------------
//      ScPaintHint - Angabe, was neu gezeichnet werden muss
// -----------------------------------------------------------------------

/*N*/ ScPaintHint::ScPaintHint( const ScRange& rRng, USHORT nPaint ) :
/*N*/   aRange( rRng ),
/*N*/   nParts( nPaint ),
/*N*/   bPrint( TRUE )
/*N*/ {
/*N*/ }

/*N*/ ScPaintHint::~ScPaintHint()
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------
//      ScUpdateRefHint - Referenz-Updaterei
// -----------------------------------------------------------------------

/*N*/ ScUpdateRefHint::ScUpdateRefHint( UpdateRefMode eMode, const ScRange& rR,
/*N*/                                   short nX, short nY, short nZ ) :
/*N*/   eUpdateRefMode( eMode ),
/*N*/   aRange( rR ),
/*N*/   nDx( nX ),
/*N*/   nDy( nY ),
/*N*/   nDz( nZ )
/*N*/ {
/*N*/ }

/*N*/ ScUpdateRefHint::~ScUpdateRefHint()
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------
//      ScPointerChangedHint - Pointer ist ungueltig geworden
// -----------------------------------------------------------------------

/*N*/ ScPointerChangedHint::ScPointerChangedHint( USHORT nF ) :
/*N*/   nFlags( nF )
/*N*/ {
/*N*/ }

/*N*/ ScPointerChangedHint::~ScPointerChangedHint()
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------
//      ScLinkRefreshedHint - a link has been refreshed
// -----------------------------------------------------------------------

/*N*/ ScLinkRefreshedHint::ScLinkRefreshedHint() :
/*N*/   nLinkType( SC_LINKREFTYPE_NONE ),
/*N*/   nDdeMode( 0 )
/*N*/ {
/*N*/ }

/*N*/ ScLinkRefreshedHint::~ScLinkRefreshedHint()
/*N*/ {
/*N*/ }

/*N*/ void ScLinkRefreshedHint::SetSheetLink( const String& rSourceUrl )
/*N*/ {
/*N*/   nLinkType = SC_LINKREFTYPE_SHEET;
/*N*/   aUrl = rSourceUrl;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
