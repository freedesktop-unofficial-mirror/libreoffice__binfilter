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

#include <osl/diagnose.h>

#include <pamtyp.hxx>
namespace binfilter {


/*N*/ static SwMoveFnCollection aFwrd = {
/*N*/   /* fnNd         */  &GoNext,
/*N*/   /* fnNds        */  &GoNextNds,
/*N*/   /* fnDoc        */  &GoEndDoc,
/*N*/   /* fnSection    */  &SwNodes::GoStartOfSection
/*N*/ };

/*N*/ static SwMoveFnCollection aBwrd = {
/*N*/   /* fnNd         */  &GoPrevious,
/*N*/   /* fnNds        */  &GoPreviousNds,
/*N*/   /* fnDoc        */  &GoStartDoc,
/*N*/   /* fnSection    */  &SwNodes::GoEndOfSection
/*N*/ };

/*N*/ SwGoInDoc fnGoDoc         = &GoInDoc;
/*N*/ SwGoInDoc fnGoNode        = &GoInNode;
/*N*/ SwGoInDoc fnGoCntnt       = &GoInCntnt;
/*N*/ SwGoInDoc fnGoCntntCells  = &GoInCntntCells;

/*N*/ SwWhichPara fnParaPrev    = &GoPrevPara;
/*N*/ SwWhichPara fnParaCurr    = &GoCurrPara;
/*N*/ SwWhichPara fnParaNext    = &GoNextPara;
/*N*/ SwPosPara fnParaStart     = &aFwrd;
/*N*/ SwPosPara fnParaEnd       = &aBwrd;

/*N*/ SwWhichSection fnSectionCurr  = &GoCurrSection;
/*N*/ SwPosSection fnSectionStart   = &aFwrd;
/*N*/ SwPosSection fnSectionEnd     = &aBwrd;

// Travelling in Tabellen
/*N*/ bool GotoCurrTable( SwPaM&, SwPosTable, bool bInReadOnly );

/*N*/ SwWhichTable fnTableCurr  = &GotoCurrTable;
/*N*/ SwPosTable fnTableStart   = &aFwrd;
/*N*/ SwPosTable fnTableEnd     = &aBwrd;

// Travelling in Bereichen
/*N*/ SwMoveFn fnMoveBackward   = &aBwrd;
/*N*/ SwMoveFn fnMoveForward    = &aFwrd;

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
