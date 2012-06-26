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

//------------------------------------------------------------------------

#include <bf_sfx2/app.hxx>
#include <bf_sfx2/objsh.hxx>
#include <bf_sfx2/sfxsids.hrc>

#define SC_PROGRESS_CXX
#include "progress.hxx"
#include "globstr.hrc"
namespace binfilter {



static ScProgress theDummyInterpretProgress;
SfxProgress*    ScProgress::pGlobalProgress = NULL;
ULONG           ScProgress::nGlobalRange = 0;
ULONG           ScProgress::nGlobalPercent = 0;
BOOL            ScProgress::bGlobalNoUserBreak = TRUE;
ScProgress*     ScProgress::pInterpretProgress = &theDummyInterpretProgress;
ScProgress*     ScProgress::pOldInterpretProgress = NULL;
ULONG           ScProgress::nInterpretProgress = 0;
BOOL            ScProgress::bAllowInterpretProgress = TRUE;
ScDocument*     ScProgress::pInterpretDoc;
BOOL            ScProgress::bIdleWasDisabled = FALSE;



/*N*/ ScProgress::ScProgress( SfxObjectShell* pObjSh, const String& rText,
/*N*/                       ULONG nRange, BOOL bAllDocs, BOOL bWait )
/*N*/ {
/*N*/
/*N*/   if ( !(pGlobalProgress || SfxProgress::GetActiveProgress( NULL ) ) )
/*N*/   {
/*N*/       if ( SFX_APP()->IsDowning() )
/*N*/       {
/*N*/           //  kommt vor z.B. beim Speichern des Clipboard-Inhalts als OLE beim Beenden
/*N*/           //  Dann wuerde ein SfxProgress wild im Speicher rummuellen
/*N*/           //! Soll das so sein ???
/*N*/
/*N*/           pProgress = NULL;
/*N*/       }
/*N*/       else if (  pObjSh
                    && (  pObjSh->GetCreateMode() == SFX_CREATE_MODE_EMBEDDED
                       || pObjSh->GetProgress()
                       )
                    )
/*N*/       {
/*N*/           //  #62808# no own progress for embedded objects,
/*N*/           //  #73633# no second progress if the document already has one
/*N*/
/*N*/           pProgress = NULL;
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           pProgress = new SfxProgress( pObjSh, rText, nRange, bAllDocs, bWait );
/*N*/           pGlobalProgress = pProgress;
/*N*/           nGlobalRange = nRange;
/*N*/           nGlobalPercent = 0;
/*N*/           bGlobalNoUserBreak = TRUE;
            }
/*N*/   }
/*N*/ }


/*N*/ ScProgress::ScProgress() :
/*N*/       pProgress( NULL )
/*N*/ { // DummyInterpret
/*N*/ }


/*N*/ ScProgress::~ScProgress()
/*N*/ {
/*N*/   if ( pProgress )
/*N*/   {
/*N*/       delete pProgress;
/*N*/       pGlobalProgress = NULL;
/*N*/       nGlobalRange = 0;
/*N*/       nGlobalPercent = 0;
/*N*/       bGlobalNoUserBreak = TRUE;
/*N*/   }
/*N*/ }


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
