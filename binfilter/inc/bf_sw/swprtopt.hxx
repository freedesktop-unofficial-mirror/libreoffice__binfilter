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

#ifndef _SWPRTOPT_HXX
#define _SWPRTOPT_HXX

#include <bf_svtools/bf_solar.h>

#include <tools/multisel.hxx>
#include <printdata.hxx>
namespace binfilter {

#define POSTITS_NONE    0
#define POSTITS_ONLY    1
#define POSTITS_ENDDOC  2
#define POSTITS_ENDPAGE 3

class SwPrtOptions : public SwPrintData
{
    USHORT nJobNo;
    String sJobName;

public:
    SwPrtOptions( const String& rJobName )
        : nJobNo( 1 )
        , sJobName( rJobName )
        , aOffset( Point(0,0) )
        , nMergeCnt( 0 )
        , nMergeAct( 0 )
        , bCollate(FALSE)
        , bPrintSelection (FALSE)
        , bJobStartet(FALSE)
    {}

    const String& GetJobName() const    { return sJobName; }

    MultiSelection  aMulti;
    Point  aOffset;
    ULONG  nMergeCnt;           // Anzahl der Serienbriefe
    ULONG  nMergeAct;           // Aktueller Serienbriefnr.
    USHORT nCopyCount;

    BOOL   bCollate,
           bPrintSelection,     // Markierung drucken
           bJobStartet;

        SwPrtOptions& operator=(const SwPrintData& rData)
            {
                SwPrintData::operator=(rData);
                return *this;
            }
};


} //namespace binfilter
#endif //_SWPRTOPT_HXX















/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
