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


#define _TOOLS_TABLE_CXX

// -----------------------------------------------------------------------
#include <tools/debug.hxx>
#include <bf_tools/impcont.hxx>
#include <bf_tools/table.hxx>

namespace binfilter
{

// =======================================================================

sal_uIntPtr Table::ImplGetIndex( sal_uIntPtr nKey, sal_uIntPtr* pIndex ) const
{
    // Abpruefen, ob der erste Key groesser als der Vergleichskey ist
    if ( !nCount || (nKey < (sal_uIntPtr)Container::ImpGetObject(0)) )
        return TABLE_ENTRY_NOTFOUND;

    sal_uIntPtr nLow;
    sal_uIntPtr nHigh;
    sal_uIntPtr nMid;
    sal_uIntPtr nCompareKey;
    void**  pNodes = Container::ImpGetOnlyNodes();

    // Binaeres Suchen
    nLow  = 0;
    nHigh = nCount-1;
    if ( pNodes )
    {
        do
        {
            nMid = (nLow + nHigh) / 2;
            nCompareKey = (sal_uIntPtr)pNodes[nMid*2];
            if ( nKey < nCompareKey )
                nHigh = nMid-1;
            else
            {
                if ( nKey > nCompareKey )
                    nLow = nMid + 1;
                else
                    return nMid*2;
            }
        }
        while ( nLow <= nHigh );
    }
    else
    {
        do
        {
            nMid = (nLow + nHigh) / 2;
            nCompareKey = (sal_uIntPtr)Container::ImpGetObject( nMid*2 );
            if ( nKey < nCompareKey )
                nHigh = nMid-1;
            else
            {
                if ( nKey > nCompareKey )
                    nLow = nMid + 1;
                else
                    return nMid*2;
            }
        }
        while ( nLow <= nHigh );
    }

    if ( pIndex )
    {
        if ( nKey > nCompareKey )
            *pIndex = (nMid+1)*2;
        else
            *pIndex = nMid*2;
    }

    return TABLE_ENTRY_NOTFOUND;
}

// =======================================================================

Table::Table( sal_uInt16 _nInitSize, sal_uInt16 _nReSize ) :
           Container( CONTAINER_MAXBLOCKSIZE, _nInitSize*2, _nReSize*2 )
{
    DBG_ASSERT( _nInitSize <= 32767, "Table::Table(): InitSize > 32767" );
    DBG_ASSERT( _nReSize <= 32767, "Table::Table(): ReSize > 32767" );
    nCount = 0;
}

// -----------------------------------------------------------------------

sal_Bool Table::Insert( sal_uIntPtr nKey, void* p )
{
    // Tabellenelement einsortieren
    sal_uIntPtr i;
    if ( nCount )
    {
        if ( nCount <= 24 )
        {
            sal_uInt16 nTempCount = (sal_uInt16)nCount * 2;

            if( void** pNodes = Container::ImpGetOnlyNodes() )
            {
                sal_uInt16 n = 0;
                sal_uIntPtr  nCompareKey = (sal_uIntPtr)(*pNodes);
                while ( nKey > nCompareKey )
                {
                    n += 2;
                    pNodes += 2;
                    if ( n < nTempCount )
                        nCompareKey = (sal_uIntPtr)(*pNodes);
                    else
                    {
                        nCompareKey = 0;
                        break;
                    }
                }

                // Testen, ob sich der Key schon in der Tabelle befindet
                if ( nKey == nCompareKey )
                    return sal_False;

                i = n;
            }
            else
            {
                i = 0;
                if ( ImplGetIndex( nKey, &i ) != TABLE_ENTRY_NOTFOUND )
                    return sal_False;
            }
        }
        else
        {
            i = 0;
            if ( ImplGetIndex( nKey, &i ) != TABLE_ENTRY_NOTFOUND )
                return sal_False;
        }
    }
    else
        i = 0;

    // Eintrag einfuegen (Key vor Pointer)
    Container::Insert( (void*)nKey, i );
    Container::Insert( p, i+1 );

    // Ein neuer Eintrag
    nCount++;

    return sal_True;
}

// -----------------------------------------------------------------------

void* Table::Remove( sal_uIntPtr nKey )
{
    // Index besorgen
    sal_uIntPtr nIndex = ImplGetIndex( nKey );

    // Testen, ob sich der Key in der Tabelle befindet
    if ( nIndex == TABLE_ENTRY_NOTFOUND )
        return NULL;

    // Itemanzahl erniedrigen
    nCount--;

    // Key entfernen
    Container::Remove( nIndex );

    // Pointer entfernen und zurueckgeben
    return Container::Remove( nIndex );
}

// -----------------------------------------------------------------------

void* Table::Replace( sal_uIntPtr nKey, void* p )
{
    // Index abfragen
    sal_uIntPtr nIndex = ImplGetIndex( nKey );

    // Existiert kein Eintrag mit dem Schluessel
    if ( nIndex == TABLE_ENTRY_NOTFOUND )
        return NULL;
    else
        return Container::Replace( p, nIndex+1 );
}

// -----------------------------------------------------------------------

void* Table::Get( sal_uIntPtr nKey ) const
{
    // Index besorgen
    sal_uIntPtr nIndex = ImplGetIndex( nKey );

    // Testen, ob sich der Key in der Tabelle befindet
    if ( nIndex == TABLE_ENTRY_NOTFOUND )
        return NULL;
    else
        return Container::ImpGetObject( nIndex+1 );
}

// -----------------------------------------------------------------------

void* Table::GetCurObject() const
{
    return Container::ImpGetObject( Container::GetCurPos()+1 );
}

// -----------------------------------------------------------------------

sal_uIntPtr Table::GetKey( const void* p ) const
{
    sal_uIntPtr nIndex = 0;

    // Solange noch Eintraege Vorhanden sind
    while ( nIndex < nCount )
    {
        // Stimmt der Pointer ueberein, wird der Key zurueckgegeben
        if ( p == Container::ImpGetObject( (nIndex*2)+1 ) )
            return (sal_uIntPtr)Container::ImpGetObject( nIndex*2 );

        nIndex++;
    }

    return TABLE_ENTRY_NOTFOUND;
}

// -----------------------------------------------------------------------

sal_Bool Table::IsKeyValid( sal_uIntPtr nKey ) const
{
    return (ImplGetIndex( nKey ) != TABLE_ENTRY_NOTFOUND) ? sal_True : sal_False;
}

// -----------------------------------------------------------------------

sal_uIntPtr Table::SearchKey( sal_uIntPtr nKey, sal_uIntPtr* pPos ) const
{
    *pPos = 0;
    sal_uIntPtr nPos = ImplGetIndex( nKey, pPos );
    if ( nPos != TABLE_ENTRY_NOTFOUND )
    {
        nPos /= 2;
        *pPos = nPos;
    }
    else
        *pPos /= 2;
    return nPos;
}

// -----------------------------------------------------------------------

void* Table::Seek( sal_uIntPtr nKey )
{
    // Testen, ob ein Eintrag vorhanden ist
    if ( nCount )
    {
        sal_uIntPtr nIndex = ImplGetIndex( nKey );

        // Ist Key nicht enthalten
        if ( nIndex == TABLE_ENTRY_NOTFOUND )
            return NULL;
        else
        {
            // Index setzen
            Container::Seek( nIndex );

            // Pointer zurueckgeben
            return Container::ImpGetObject( Container::GetCurPos() + 1 );
        }
    }
    else
        return NULL;
}

void* Table::First()
{
    // Testen, ob ein Eintrag vorhanden ist
    if ( nCount )
    {
        // Auf ersten Eintag setzen
        Container::First();

        // Pointer zurueckgeben
        return Container::ImpGetObject( 1 );
    }
    else
        return NULL;
}

// -----------------------------------------------------------------------

void* Table::Last()
{
    // Testen, ob ein Eintrag vorhanden ist
    if ( nCount )
    {
        // Last auf letzten Eintrag setzen
        void* p = Container::Last();
        Container::Prev();

        // Pointer zurueckgeben
        return p;
    }
    else
        return NULL;
}

// -----------------------------------------------------------------------

void* Table::Next()
{
    // Ueber den Pointer weiterschalten
    Container::Next();

    // Nachsten Eintag
    Container::Next();

    // Pointer vom naechsten Key zurueckgeben
    return Container::ImpGetObject( Container::GetCurPos() + 1 );
}

// -----------------------------------------------------------------------

void* Table::Prev()
{
    // Ueber den Pointer weiterschalten
    void* p = Container::Prev();

    // Nachsten Eintag
    Container::Prev();

    // Pointer vom vorherigen Key zurueckgeben
    return p;
}

} // namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
