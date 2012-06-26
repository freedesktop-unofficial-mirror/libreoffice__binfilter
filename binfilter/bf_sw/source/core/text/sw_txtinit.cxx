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

#include "fntcache.hxx"     // pFntCache  ( SwFont/ScrFont-PrtFont Cache )
#include "swfntcch.hxx"     // pSwFontCache  ( SwAttrSet/SwFont Cache )
#include "txtfrm.hxx"
#include "txtcache.hxx"
#include "porrst.hxx"

#include <horiornt.hxx>

#include "pordrop.hxx"
#include "txtfly.hxx"   // SwContourCache
namespace binfilter {

/*N*/ SwCache *SwTxtFrm::pTxtCache = 0;
/*N*/ long SwTxtFrm::nMinPrtLine = 0;
/*N*/ SwContourCache *pContourCache = 0;

#ifndef PROFILE
// Code zum Initialisieren von Statics im eigenen Code-Segment
#ifdef _MSC_VER
#pragma code_seg( "SWSTATICS" )
#endif
#endif

/*N*/ IMPL_FIXEDMEMPOOL_NEWDEL( SwTxtLine )
/*N*/ IMPL_FIXEDMEMPOOL_NEWDEL( SwParaPortion )   //Absaetze
/*N*/ IMPL_FIXEDMEMPOOL_NEWDEL( SwLineLayout )   //Zeilen
/*N*/ IMPL_FIXEDMEMPOOL_NEWDEL( SwHolePortion )   //z.B. Blanks am Zeilenende
/*N*/ IMPL_FIXEDMEMPOOL_NEWDEL( SwTxtPortion )   //Attributwechsel

#ifndef PROFILE
#ifdef _MSC_VER
#pragma code_seg()
#endif
#endif

/*************************************************************************
 *                  _TextInit(), _TextFinit()
 *************************************************************************/

// Werden _nur_ in init.cxx verwendet, dort stehen extern void _TextFinit()
// und extern void _TextInit(...)

/*N*/ void _TextInit()
/*N*/ {
/*N*/   pFntCache = new SwFntCache;
/*N*/   pSwFontCache = new SwFontCache;
/*N*/   pWaveCol = new Color( COL_GRAY );
/*N*/
/*N*/   //Pauschale groesse 250, plus 100 pro Shell
/*N*/   SwCache *pTxtCache = new SwCache( 250, 100
/*N*/ #ifdef DBG_UTIL
/*N*/   , "static SwTxtFrm::pTxtCache"
/*N*/ #endif
/*N*/   );
/*N*/   SwTxtFrm::SetTxtCache( pTxtCache );
/*N*/ }

/*N*/ void _TextFinit()
/*N*/ {
/*N*/   delete SwTxtFrm::GetTxtCache();
/*N*/   delete pSwFontCache;
/*N*/   delete pFntCache;
/*N*/   delete pWaveCol;
/*N*/   delete pContourCache;
/*N*/ }



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
