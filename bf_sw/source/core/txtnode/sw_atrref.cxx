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

#include <txtrfmrk.hxx>
#include <fmtrfmrk.hxx>
namespace binfilter {


/****************************************************************************
 *
 *  class SwFmtRefMark
 *
 ****************************************************************************/

/*N*/ SwFmtRefMark::~SwFmtRefMark( )
/*N*/ {
/*N*/ }

/*N*/ SwFmtRefMark::SwFmtRefMark( const XubString& rName )
/*N*/   : SfxPoolItem( RES_TXTATR_REFMARK )
/*N*/   , pTxtAttr( 0 )
/*N*/   , aRefName( rName )
/*N*/ {
/*N*/ }

/*N*/ SwFmtRefMark::SwFmtRefMark( const SwFmtRefMark& rAttr )
/*N*/   : SfxPoolItem( RES_TXTATR_REFMARK )
/*N*/   , pTxtAttr( 0 )
/*N*/   , aRefName( rAttr.aRefName )
/*N*/ {
/*N*/ }

/*N*/ SfxPoolItem* SwFmtRefMark::Clone( SfxItemPool* ) const
/*N*/ {
/*N*/   return new SwFmtRefMark( *this );
/*N*/ }

/*************************************************************************
 *                      class SwTxtRefMark
 *************************************************************************/

// Attribut fuer Inhalts-/Positions-Referenzen im Text

/*N*/ SwTxtRefMark::SwTxtRefMark( const SwFmtRefMark& rAttr,
/*N*/                   xub_StrLen nStart2, xub_StrLen* pEnde )
/*N*/   : SwTxtAttrEnd( rAttr, nStart2, nStart2 )
/*N*/   , pMyTxtNd( 0 )
/*N*/   , pEnd( 0 )
/*N*/ {
/*N*/   ((SwFmtRefMark&)rAttr).pTxtAttr = this;
/*N*/   if( pEnde )
/*N*/   {
/*N*/       nEnd = *pEnde;
/*N*/       pEnd = &nEnd;
/*N*/   }
/*N*/   SetDontMergeAttr( TRUE );
/*N*/   SetDontMoveAttr( TRUE );
/*N*/   SetOverlapAllowedAttr( TRUE );
/*N*/ }

/*N*/ xub_StrLen* SwTxtRefMark::GetEnd()
/*N*/ {
/*N*/   return pEnd;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
