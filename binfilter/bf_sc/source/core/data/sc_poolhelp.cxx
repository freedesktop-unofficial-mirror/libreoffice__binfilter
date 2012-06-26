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


#include <bf_svtools/zforlist.hxx>
#include <bf_svx/editeng.hxx>

#include "poolhelp.hxx"
#include "document.hxx"
#include "docpool.hxx"
#include "stlpool.hxx"

namespace binfilter {

// -----------------------------------------------------------------------

/*N*/ ScPoolHelper::ScPoolHelper( ScDocument* pSourceDoc )
/*N*/ {
/*N*/   DBG_ASSERT( pSourceDoc, "ScPoolHelper: no document" );
/*N*/
/*N*/   pDocPool = new ScDocumentPool;
/*N*/   pDocPool->FreezeIdRanges();
/*N*/
/*N*/   pStylePool = new ScStyleSheetPool( *pDocPool, pSourceDoc );
/*N*/
/*N*/   pFormTable = new SvNumberFormatter( pSourceDoc->GetServiceManager(), ScGlobal::eLnge );
/*N*/     pFormTable->SetColorLink( LINK( pSourceDoc, ScDocument, GetUserDefinedColor ) );
/*N*/   pFormTable->SetEvalDateFormat( NF_EVALDATEFORMAT_INTL_FORMAT );
/*N*/
/*N*/   pEditPool = EditEngine::CreatePool();
/*N*/   pEditPool->SetDefaultMetric( SFX_MAPUNIT_100TH_MM );
/*N*/   pEditPool->FreezeIdRanges();
/*N*/   pEditPool->SetFileFormatVersion( SOFFICE_FILEFORMAT_50 );   // used in ScGlobal::EETextObjEqual
/*N*/
/*N*/   pEnginePool = EditEngine::CreatePool();
/*N*/   pEnginePool->SetDefaultMetric( SFX_MAPUNIT_100TH_MM );
/*N*/   pEnginePool->FreezeIdRanges();
/*N*/ }

/*N*/ ScPoolHelper::~ScPoolHelper()
/*N*/ {
/*N*/   delete pEnginePool;
/*N*/   delete pEditPool;
/*N*/   delete pFormTable;
/*N*/   delete pStylePool;
/*N*/   delete pDocPool;
/*N*/ }

/*N*/ void ScPoolHelper::SourceDocumentGone()
/*N*/ {
/*N*/   //  reset all pointers to the source document
/*N*/   pStylePool->SetDocument( NULL );
/*N*/     pFormTable->SetColorLink( Link() );
/*N*/ }

// -----------------------------------------------------------------------


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
