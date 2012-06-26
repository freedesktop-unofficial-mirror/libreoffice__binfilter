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


#include <horiornt.hxx>


#include <osl/diagnose.h>

#include <pam.hxx>
#include <bookmrk.hxx>
#include <swserv.hxx>

namespace binfilter {

/*N*/ SV_IMPL_REF( SwServerObject )

/*N*/ SwBookmark::SwBookmark(const SwPosition& aPos, const KeyCode& rCode,
/*N*/                       const String& rName, const String& rShortName )
/*N*/   : SwModify( 0 )
/*N*/   , pPos2( 0 )
/*N*/   , aStartMacro( aEmptyStr, aEmptyStr )
/*N*/   , aEndMacro  ( aEmptyStr, aEmptyStr )
/*N*/   , aName(rName)
/*N*/   , aShortName(rShortName)
/*N*/   , aCode(rCode)
/*N*/   , eMarkType( BOOKMARK )
/*N*/ {
/*N*/   pPos1 = new SwPosition(aPos);
/*N*/ }

// Beim Loeschen von Text werden Bookmarks mitgeloescht!


/*N*/ SwBookmark::~SwBookmark()
/*N*/ {
/*N*/   delete pPos1;
/*N*/   if( pPos2 )
/*N*/       delete pPos2;
/*N*/ }

// Vergleiche auf Basis der Dokumentposition

/*N*/ BOOL SwBookmark::operator<(const SwBookmark &rBM) const
/*N*/ {
/*N*/   const SwPosition* pThisPos = ( !pPos2 || *pPos1 <= *pPos2 ) ? pPos1 : pPos2;
/*N*/   const SwPosition* pBMPos = ( !rBM.pPos2 || *rBM.pPos1 <= *rBM.pPos2 )
/*N*/                                       ? rBM.pPos1 : rBM.pPos2;
/*N*/
/*N*/   return *pThisPos < *pBMPos;
/*N*/ }

/*N*/ BOOL SwBookmark::operator==(const SwBookmark &rBM) const
/*N*/ {
/*N*/   return (this == &rBM);
/*N*/ }

/*N*/ SwUNOMark::SwUNOMark( const SwPosition& aPos,
/*N*/               const KeyCode& rCode,
/*N*/               const String& rName,
/*N*/               const String& rShortName )
/*N*/   : SwBookmark( aPos, rCode, rName, rShortName )
/*N*/ {
/*N*/   eMarkType = UNO_BOOKMARK;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
