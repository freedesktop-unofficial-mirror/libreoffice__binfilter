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

#include <viewsh.hxx>
#include "swfntcch.hxx"
#include "fmtcol.hxx"
namespace binfilter {

// aus atrstck.cxx
extern const BYTE StackPos[];

// globale Variablen, werden in SwFntCch.Hxx bekanntgegeben
// Der FontCache wird in TxtInit.Cxx _TXTINIT erzeugt und in _TXTEXIT geloescht
SwFontCache *pSwFontCache = NULL;

/*************************************************************************
|*
|*  SwFontObj::SwFontObj(), ~SwFontObj()
|*
|*************************************************************************/

/*N*/ SwFontObj::SwFontObj( const void *pOwner2, ViewShell *pSh ) :
/*N*/   SwCacheObj( (void*)pOwner2 ),
/*N*/   aSwFont( &((SwTxtFmtColl *)pOwner2)->GetAttrSet(), pSh ? pSh->GetDoc() : 0 )
/*N*/ {
/*N*/   aSwFont.GoMagic( pSh, aSwFont.GetActual() );
/*N*/     const SwAttrSet& rAttrSet = ((SwTxtFmtColl *)pOwner2)->GetAttrSet();
/*N*/     for (USHORT i = RES_CHRATR_BEGIN; i < RES_CHRATR_END; i++)
/*N*/         pDefaultArray[ StackPos[ i ] ] = &rAttrSet.Get( i, TRUE );
/*N*/ }

/*N*/ SwFontObj::~SwFontObj()
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|*  SwFontAccess::SwFontAccess()
|*
|*************************************************************************/

/*N*/ SwFontAccess::SwFontAccess( const void *pOwner3, ViewShell *pSh ) :
/*N*/   SwCacheAccess( *pSwFontCache, pOwner3,
/*N*/           (BOOL) ((SwTxtFmtColl*)pOwner3)->IsInSwFntCache() ),
/*N*/   pShell( pSh )
/*N*/ {
/*N*/ }

/*N*/ SwFontObj *SwFontAccess::Get( )
/*N*/ {
/*N*/   return (SwFontObj *) SwCacheAccess::Get( );
/*N*/ }

/*N*/ SwCacheObj *SwFontAccess::NewObj( )
/*N*/ {
/*N*/   ((SwTxtFmtColl*)pOwner)->SetInSwFntCache( TRUE );
/*N*/   return new SwFontObj( pOwner, pShell );
/*N*/ }


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
