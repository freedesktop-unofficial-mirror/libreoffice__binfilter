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

#include <ctype.h>
#include <stdio.h>
#include <bf_svtools/bf_solar.h>
#include <bf_tools/string.hxx>
#include <com/sun/star/beans/PropertyValues.hpp>
#include <bf_svtools/ownlist.hxx>

using namespace com::sun::star;

namespace binfilter
{

//=========================================================================
//============== SvCommandList ============================================
//=========================================================================
PRV_SV_IMPL_OWNER_LIST(SvCommandList,SvCommand)

//=========================================================================
SvCommand & SvCommandList::Append
(
    const String & rCommand,    /* das Kommando */
    const String & rArg         /* dasArgument des Kommandos */
)
/*  [Beschreibung]

    Es wird eine Objekt vom Typ SvCommand erzeugt und an die Liste
    angeh"angt.

    [R"uckgabewert]

    SvCommand &     Das erteugte Objekt wird zur"uckgegeben.
*/
{
    SvCommand * pCmd = new SvCommand( rCommand, rArg );
    aTypes.Insert( pCmd, LIST_APPEND );
    return *pCmd;
}

//=========================================================================
SvStream & operator >>
(
    SvStream & rStm,        /* Stream aus dem gelesen wird */
    SvCommandList & rThis   /* Die zu f"ullende Liste */
)
/*  [Beschreibung]

    Die Liste mit ihren Elementen wird gelesen. Das Format ist:
    1. Anzahl der Elemente
    2. Alle Elemente

    [R"uckgabewert]

    SvStream &      Der "ubergebene Stream.
*/
{
    UINT32 nCount = 0;
    rStm >> nCount;
    if( !rStm.GetError() )
    {
        while( nCount-- )
        {
            SvCommand * pCmd = new SvCommand();
            rStm >> *pCmd;
            rThis.aTypes.Insert( pCmd, LIST_APPEND );
        }
    }
    return rStm;
}

//=========================================================================
SvStream & operator <<
(
    SvStream & rStm,            /* Stream in den geschrieben wird */
    const SvCommandList & rThis /* Die zu schreibende Liste */
)
/*  [Beschreibung]

    Die Liste mit ihren Elementen wir geschrieben. Das Format ist:
    1. Anzahl der Elemente
    2. Alle Elemente

    [R"uckgabewert]

    SvStream &      Der "ubergebene Stream.
*/
{
    UINT32 nCount = rThis.aTypes.Count();
    rStm << nCount;

    for( UINT32 i = 0; i < nCount; i++ )
    {
        SvCommand * pCmd = (SvCommand *)rThis.aTypes.GetObject( i );
        rStm << *pCmd;
    }
    return rStm;
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
