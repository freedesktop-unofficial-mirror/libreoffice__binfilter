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

#include <docstat.hxx>
namespace binfilter {


/************************************************************************
 *                         SwDocStat::SwDocStat()
 ************************************************************************/

/*N*/ SwDocStat::SwDocStat() :
/*N*/   nTbl(0),
/*N*/   nGrf(0),
/*N*/   nOLE(0),
/*N*/   nPage(1),
/*N*/   nPara(1),
/*N*/   nWord(0),
/*N*/   nChar(0),
/*N*/   bModified(TRUE),
/*N*/   pInternStat(0)
/*N*/ {}

/************************************************************************
 *                         void SwDocStat::Reset()
 ************************************************************************/

/*N*/ void SwDocStat::Reset()
/*N*/ {
/*N*/   nTbl    = 0;
/*N*/   nGrf    = 0;
/*N*/   nOLE    = 0;
/*N*/   nPage   = 1;
/*N*/   nPara   = 1;
/*N*/   nWord   = 0;
/*N*/   nChar   = 0;
/*N*/   bModified = TRUE;
/*N*/   pInternStat = 0;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
