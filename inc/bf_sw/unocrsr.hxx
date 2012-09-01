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
#ifndef _UNOCRSR_HXX
#define _UNOCRSR_HXX

#include <bf_svtools/bf_solar.h>

#include <swcrsr.hxx>
#include <calbck.hxx>
namespace binfilter {


class SwUnoCrsr : public virtual SwCursor, public SwModify
{
    BOOL bRemainInSection : 1;
    BOOL bSkipOverHiddenSections : 1;
    BOOL bSkipOverProtectSections : 1;

public:
    SwUnoCrsr( const SwPosition &rPos, SwPaM* pRing = 0 );
    virtual ~SwUnoCrsr();

    virtual operator SwUnoCrsr* ();

    // gibt es eine Selection vom Content in die Tabelle
    // Return Wert gibt an, ob der Crsr auf der alten Position verbleibt
    virtual bool IsSelOvr( int eFlags =
                                ( SELOVER_CHECKNODESSECTION |
                                  SELOVER_TOGGLE | SELOVER_CHANGEPOS ));

    BOOL IsRemainInSection() const          { return bRemainInSection; }
    void SetRemainInSection( BOOL bFlag )   { bRemainInSection = bFlag; }

    BOOL IsSkipOverProtectSections() const
                                    { return bSkipOverProtectSections; }
    void SetSkipOverProtectSections( BOOL bFlag )
                                    { bSkipOverProtectSections = bFlag; }

    BOOL IsSkipOverHiddenSections() const
                                    { return bSkipOverHiddenSections; }
    void SetSkipOverHiddenSections( BOOL bFlag )
                                    { bSkipOverHiddenSections = bFlag; }

    DECL_FIXEDMEMPOOL_NEWDEL( SwUnoCrsr )
};



class SwUnoTableCrsr : public virtual SwUnoCrsr, public virtual SwTableCursor
{
    // die Selection hat die gleiche Reihenfolge wie die
    // TabellenBoxen. D.h., wird aus dem einen Array an einer Position
    // etwas geloescht, dann muss es auch im anderen erfolgen!!
    SwCursor aTblSel;

public:
    SwUnoTableCrsr( const SwPosition& rPos );
    virtual ~SwUnoTableCrsr() {}

    virtual operator SwUnoCrsr* ()          { return this; }
    virtual operator SwUnoTableCrsr* ()     { return this; }
    virtual operator SwTableCursor* ()      { return this; }

    // gibt es eine Selection vom Content in die Tabelle
    // Return Wert gibt an, ob der Crsr auf der alten Position verbleibt
    virtual bool IsSelOvr( int )    { return false; }

    SwCursor& GetSelRing()              { return aTblSel; }
    const SwCursor& GetSelRing() const  { return aTblSel; }
};



} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
