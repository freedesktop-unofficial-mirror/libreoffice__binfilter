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

#include "doc.hxx"
#include "lineinfo.hxx"
#include "charfmt.hxx"
#include "poolfmt.hxx"
#include "rootfrm.hxx"
#include "viewsh.hxx"
namespace binfilter {

/*N*/ void SwDoc::SetLineNumberInfo( const SwLineNumberInfo &rNew )
/*N*/ {
/*N*/   *pLineNumberInfo = rNew;
/*N*/   SetModified();
/*N*/ }

/*N*/ SwLineNumberInfo::SwLineNumberInfo() :
/*N*/   nPosFromLeft( MM50 ),
/*N*/   nCountBy( 5 ),
/*N*/   nDividerCountBy( 3 ),
/*N*/   ePos( LINENUMBER_POS_LEFT ),
/*N*/   bPaintLineNumbers( FALSE ),
/*N*/   bCountBlankLines( TRUE ),
/*N*/   bCountInFlys( FALSE ),
/*N*/   bRestartEachPage( FALSE )
/*N*/ {
/*N*/ }

/*N*/ SwLineNumberInfo::SwLineNumberInfo(const SwLineNumberInfo &rCpy ) : SwClient(),
/*N*/   aType( rCpy.GetNumType() ),
/*N*/   aDivider( rCpy.GetDivider() ),
/*N*/   nPosFromLeft( rCpy.GetPosFromLeft() ),
/*N*/   nCountBy( rCpy.GetCountBy() ),
/*N*/   nDividerCountBy( rCpy.GetDividerCountBy() ),
/*N*/   ePos( rCpy.GetPos() ),
/*N*/   bPaintLineNumbers( rCpy.IsPaintLineNumbers() ),
/*N*/   bCountBlankLines( rCpy.IsCountBlankLines() ),
/*N*/   bCountInFlys( rCpy.IsCountInFlys() ),
/*N*/   bRestartEachPage( rCpy.IsRestartEachPage() )
/*N*/ {
/*N*/   if ( rCpy.GetRegisteredIn() )
/*?*/       ((SwModify*)rCpy.GetRegisteredIn())->Add( this );
/*N*/ }

/*N*/ SwLineNumberInfo& SwLineNumberInfo::operator=(const SwLineNumberInfo &rCpy)
/*N*/ {
/*N*/   if ( rCpy.GetRegisteredIn() )
/*N*/       ((SwModify*)rCpy.GetRegisteredIn())->Add( this );
/*N*/   else if ( GetRegisteredIn() )
/*?*/       pRegisteredIn->Remove( this );
/*N*/
/*N*/   aType = rCpy.GetNumType();
/*N*/   aDivider = rCpy.GetDivider();
/*N*/   nPosFromLeft = rCpy.GetPosFromLeft();
/*N*/   nCountBy = rCpy.GetCountBy();
/*N*/   nDividerCountBy = rCpy.GetDividerCountBy();
/*N*/   ePos = rCpy.GetPos();
/*N*/   bPaintLineNumbers = rCpy.IsPaintLineNumbers();
/*N*/   bCountBlankLines = rCpy.IsCountBlankLines();
/*N*/   bCountInFlys = rCpy.IsCountInFlys();
/*N*/   bRestartEachPage = rCpy.IsRestartEachPage();
/*N*/
/*N*/   return *this;
/*N*/ }



/*N*/ SwCharFmt* SwLineNumberInfo::GetCharFmt(SwDoc &rDoc) const
/*N*/ {
/*N*/   if ( !GetRegisteredIn() )
/*?*/   {
/*?*/       SwCharFmt* pFmt = rDoc.GetCharFmtFromPool( RES_POOLCHR_LINENUM );
/*?*/       pFmt->Add( (SwClient*)this );
/*?*/   }
/*N*/   return (SwCharFmt*)GetRegisteredIn();
/*N*/ }

/*N*/ void SwLineNumberInfo::SetCharFmt( SwCharFmt *pChFmt )
/*N*/ {
/*N*/   OSL_ENSURE( pChFmt, "SetCharFmt, 0 is not a valid pointer" );
/*N*/   pChFmt->Add( this );
/*N*/ }

/*N*/ void SwLineNumberInfo::Modify( SfxPoolItem* pOld, SfxPoolItem* pNew )
/*N*/ {
/*N*/   SwClient::Modify( pOld, pNew );
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
