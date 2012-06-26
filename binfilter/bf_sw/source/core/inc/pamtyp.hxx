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

#ifndef _PAMTYP_HXX
#define _PAMTYP_HXX

#include <bf_svtools/bf_solar.h>
#include <unotools/textsearch.hxx>
#include <pam.hxx>
#include <node.hxx>
#include <bf_tools/string.hxx>

namespace binfilter {

struct SwPosition;
class SwPaM;

// Funktions-Deklarationen fuer die Move/Find-Methoden vom SwPaM

void GoStartDoc( SwPosition*);
void GoEndDoc( SwPosition*);
bool GoInDoc( SwPaM&, SwMoveFn);
bool GoInNode( SwPaM&, SwMoveFn);
bool GoInCntnt( SwPaM&, SwMoveFn);
bool GoInCntntCells( SwPaM&, SwMoveFn);

bool GoNext(SwNode* pNd, SwIndex * pIdx, USHORT nMode );
bool GoPrevious(SwNode* pNd, SwIndex * pIdx, USHORT nMode );
SwCntntNode* GoNextNds( SwNodeIndex * pIdx, bool );
SwCntntNode* GoPreviousNds( SwNodeIndex * pIdx, bool );

// --------- Funktionsdefinitionen fuer die SwCrsrShell --------------

bool GoPrevPara( SwPaM&, SwPosPara);
bool GoCurrPara( SwPaM&, SwPosPara);
bool GoNextPara( SwPaM&, SwPosPara);
bool GoCurrSection( SwPaM&, SwPosSection);


// ------------ Typedefiniton fuer Funktionen ----------------------

typedef bool (*GoNd)( SwNode*, SwIndex*, USHORT );
typedef SwCntntNode* (*GoNds)( SwNodeIndex*, bool );
typedef void (*GoDoc)( SwPosition* );
typedef void (SwNodes:: *MvSection)( SwNodeIndex * ) const;


struct SwMoveFnCollection
{
    GoNd      fnNd;
    GoNds     fnNds;
    GoDoc     fnDoc;
    MvSection fnSection;
};

// --------- Funktionsdefinitionen fuers Suchen --------------
SwCntntNode* GetNode( SwPaM&, bool&, SwMoveFn, bool bInReadOnly = FALSE );



} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
