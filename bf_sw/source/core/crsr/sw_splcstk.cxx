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

#include "crsrsh.hxx"

#include "splcstk.hxx"
#include "viscrs.hxx"
namespace binfilter {



SwSpellCrsrStk::SwSpellCrsrStk( SwCrsrShell& rShell )
    : rCrsrShell( rShell ), pErrorPos( 0 )
{
    pCurCrsr =
    pCrsrStk = new SwIntrnlCrsr( rCrsrShell,
                                 *rCrsrShell.GetCrsr()->GetPoint() );
    if( rCrsrShell.GetCrsr()->HasMark() )
    {
        pCurCrsr->SetMark();
        *pCurCrsr->GetMark() = *rCrsrShell.GetCrsr()->GetMark();
    }
        // gibt es mehr als einen Cursor ??
    if( rCrsrShell.GetCrsr()->GetNext() != rCrsrShell.GetCrsr() )
    {
        rCrsrShell.HideCrsr(); // alle Cursor erstmal verstecken

        // dann verschiebe den gesamten Ring hierher, in dem aus der Shell
        // alle ausgekettet und hier eingekettet werden. Bis auf den akt. !
        Ring* pCrsr = rCrsrShell.GetCrsr();
        pCrsr->MoveRingTo( pCurCrsr );
        pCrsr->MoveTo( pCrsr );
    }
}


SwSpellCrsrStk::~SwSpellCrsrStk()
{
    register Ring* p = pCrsrStk;
    while( p->GetNext() != pCrsrStk )
        delete p->GetNext();

    delete pCrsrStk;
    delete pErrorPos;
}


    // akt. Cursor in der CrsrShell mit akt. setzen
void SwSpellCrsrStk::SetCurCrsr()
{
    *rCrsrShell.GetCrsr()->GetPoint() = *pCurCrsr->Start();
    if( pCurCrsr->HasMark() )
    {
        rCrsrShell.GetCrsr()->SetMark();
        *rCrsrShell.GetCrsr()->GetMark() = *pCurCrsr->End();
    }
    else
        rCrsrShell.GetCrsr()->DeleteMark();
}

    // gehe zum naechsten Cursor im Ring (falls am Ende returne FALSE;


BOOL SwSpellCrsrStk::SetNextCrsr()
{
    if( pCurCrsr->GetNext() == pCrsrStk )
        return FALSE;

    pCurCrsr = (SwIntrnlCrsr*)pCurCrsr->GetNext();
    SetCurCrsr();
    return TRUE;
}


    // alle Cursor aus dem CursorStack wieder in der Shell setzen
void SwSpellCrsrStk::RestoreCrsrs()
{
    // verschiebe den gesamten Ring in die Shell, in dem hier
    // alle ausgekettet und dort eingekettet werden. Bis auf den Stack !
    if( pCrsrStk->GetNext() != pCrsrStk )
    {
        // sich selbst "ausketten"
        pCrsrStk->MoveRingTo( rCrsrShell.GetCrsr() );
        pCrsrStk->MoveTo( pCrsrStk );
    }

    pCurCrsr = pCrsrStk;

    SetCurCrsr();

    rCrsrShell.ShowCrsr();              // Cursor wieder anzeigen
}


    // speicher die akt. Start-Position als Error. An dieser wird spaeter
    // wieder aufgesetzt
void SwSpellCrsrStk::StoreErrPos()
{
    if( !pErrorPos )
        pErrorPos = new SwPosition( *rCrsrShell.GetCrsr()->Start() );
    else
        *pErrorPos = *rCrsrShell.GetCrsr()->Start();
}


    // akt. Cursor auf die Error-Position setzen
void SwSpellCrsrStk::SetErrPos()
{
    if( !pErrorPos )
        return;

    *rCrsrShell.GetCrsr()->GetPoint() = *pErrorPos;
    if( pCurCrsr->HasMark() )
    {
        rCrsrShell.GetCrsr()->SetMark();
        *rCrsrShell.GetCrsr()->GetMark() = *pCurCrsr->End();
    }
    else
        rCrsrShell.GetCrsr()->DeleteMark();
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
