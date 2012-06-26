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

#include <shellio.hxx>
#include <horiornt.hxx>
#include <doc.hxx>
#include <osl/diagnose.h>
#include <cmdid.h>

namespace binfilter {

/******************************************************************************
 *  Methode     :   SwDocFac::SwDocFac( SwDoc *pDoc )
 ******************************************************************************/

/*N*/ SwDocFac::SwDocFac( SwDoc *pDc )
/*N*/   : pDoc( pDc )
/*N*/ {
/*N*/   if( pDoc )
/*N*/       pDoc->AddLink();
/*N*/ }

/******************************************************************************
 *  Methode     :   SwDocFac::~SwDocFac()
 ******************************************************************************/

/*N*/ SwDocFac::~SwDocFac()
/*N*/ {
/*N*/   if( pDoc && !pDoc->RemoveLink() )
/*?*/       delete pDoc;
/*N*/ }

/******************************************************************************
 *  Methode     :   SwDoc *SwDocFac::GetDoc()
 *  Beschreibung:   Diese Methode legt immer einen Drucker an.
 ******************************************************************************/

/*N*/ SwDoc *SwDocFac::GetDoc()
/*N*/ {
/*N*/   if( !pDoc )
/*N*/   {
/*N*/       pDoc = new SwDoc;
/*N*/       pDoc->AddLink();
/*N*/   }
/*N*/   return pDoc;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
