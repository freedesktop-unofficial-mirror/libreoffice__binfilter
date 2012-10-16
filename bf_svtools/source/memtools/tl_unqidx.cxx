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

#include <bf_tools/impcont.hxx>
#include <bf_tools/unqidx.hxx>
#include <bf_tools/unqid.hxx>

namespace binfilter
{

/*************************************************************************
|*
|*    UniqueIndex::UniqueIndex()
|*
*************************************************************************/

UniqueIndex::UniqueIndex( sal_uIntPtr _nStartIndex,
                          sal_uIntPtr _nInitSize, sal_uIntPtr _nReSize ) :
                 Container( _nInitSize )
{
    nReSize         = _nReSize;
    nStartIndex     = _nStartIndex;
    nUniqIndex      = 0;
    nCount          = 0;
}

/*************************************************************************
|*
|*    UniqueIndex::UniqueIndex()
|*
*************************************************************************/

UniqueIndex::UniqueIndex( const UniqueIndex& rIdx ) :
                 Container( rIdx )
{
    nReSize     = rIdx.nReSize;
    nStartIndex = rIdx.nStartIndex;
    nUniqIndex  = rIdx.nUniqIndex;
    nCount      = rIdx.nCount;
}

/*************************************************************************
|*
|*    UniqueIndex::Insert()
|*
*************************************************************************/

sal_uIntPtr UniqueIndex::Insert( void* p )
{
    // NULL-Pointer ist nicht erlaubt
    if ( !p )
        return UNIQUEINDEX_ENTRY_NOTFOUND;

    // Ist Array voll, dann expandieren
    if ( nCount == Container::GetSize() )
        SetSize( nCount + nReSize );

    // Damit UniqIndex nicht ueberlaeuft, wenn Items geloescht wurden
    nUniqIndex = nUniqIndex % Container::GetSize();

    // Leeren Eintrag suchen
    while ( Container::ImpGetObject( nUniqIndex ) != NULL )
        nUniqIndex = (nUniqIndex+1) % Container::GetSize();

    // Object im Array speichern
    Container::Replace( p, nUniqIndex );

    // Anzahl der Eintraege erhoehen und Index zurueckgeben
    nCount++;
    nUniqIndex++;
    return ( nUniqIndex + nStartIndex - 1 );
}

/*************************************************************************
|*
|*    UniqueIndex::Remove()
|*
*************************************************************************/

void* UniqueIndex::Remove( sal_uIntPtr nIndex )
{
    // Ist Index zulaessig
    if ( (nIndex >= nStartIndex) &&
         (nIndex < (Container::GetSize()+nStartIndex)) )
    {
        // Index-Eintrag als leeren Eintrag setzen und Anzahl der
        // gespeicherten Indexe erniedriegen, wenn Eintrag belegt war
        void* p = Container::Replace( NULL, nIndex-nStartIndex );
        if ( p )
            nCount--;
        return p;
    }
    else
        return NULL;
}

/*************************************************************************
|*
|*    UniqueIndex::GetCurIndex()
|*
*************************************************************************/

sal_uIntPtr UniqueIndex::GetCurIndex() const
{
    sal_uIntPtr nPos = Container::GetCurPos();

    // Ist der Current-Index nicht belegt, dann gibt es keinen Current-Index
    if ( !Container::ImpGetObject( nPos ) )
        return UNIQUEINDEX_ENTRY_NOTFOUND;
    else
        return nPos+nStartIndex;
}

/*************************************************************************
|*
|*    UniqueIndex::IsIndexValid()
|*
*************************************************************************/

sal_Bool UniqueIndex::IsIndexValid( sal_uIntPtr nIndex ) const
{
    // Ist Index zulaessig
    if ( (nIndex >= nStartIndex) &&
         (nIndex < (Container::GetSize()+nStartIndex)) )
    {
        // Index ist nur zulaessig, wenn Eintrag auch belegt ist
        if ( Container::ImpGetObject( nIndex-nStartIndex ) )
            return sal_True;
        else
            return sal_False;
    }
    else
        return sal_False;
}

/*************************************************************************
|*
|*    UniqueIndex::Seek()
|*
*************************************************************************/

void* UniqueIndex::Seek( sal_uIntPtr nIndex )
{
    // Index-Eintrag als aktuellen setzten, wenn er gueltig ist
    if ( IsIndexValid( nIndex ) )
        return Container::Seek( nIndex-nStartIndex );
    else
        return NULL;
}

/*************************************************************************
|*
|*    UniqueIndex::First()
|*
*************************************************************************/

void* UniqueIndex::First()
{
    void* p = Container::First();

    while ( !p && (Container::GetCurPos() < (Container::GetSize()-1)) )
        p = Container::Next();

    return p;
}

/*************************************************************************
|*
|*    UniqueIndex::Last()
|*
*************************************************************************/

void* UniqueIndex::Last()
{
    void* p = Container::Last();

    while ( !p && Container::GetCurPos() )
        p = Container::Prev();

    return p;
}

/*************************************************************************
|*
|*    UniqueIndex::Next()
|*
*************************************************************************/

void* UniqueIndex::Next()
{
    void* p = NULL;

    while ( !p && (Container::GetCurPos() < (Container::GetSize()-1)) )
        p = Container::Next();

    return p;
}

/*************************************************************************
|*
|*    UniqueIndex::Prev()
|*
*************************************************************************/

void* UniqueIndex::Prev()
{
    void* p = NULL;

    while ( !p && Container::GetCurPos() )
        p = Container::Prev();

    return p;
}

/*************************************************************************
|*
|*    UniqueIndex::operator =()
|*
*************************************************************************/

UniqueIndex& UniqueIndex::operator =( const UniqueIndex& rIdx )
{
    // Neue Werte zuweisen
    Container::operator =( rIdx );
    nReSize     = rIdx.nReSize;
    nStartIndex = rIdx.nStartIndex;
    nUniqIndex  = rIdx.nUniqIndex;
    nCount      = rIdx.nCount;
    return *this;
}

/*************************************************************************
|*
|*    UniqueIndex::operator ==()
|*
*************************************************************************/

sal_Bool UniqueIndex::operator ==( const UniqueIndex& rIdx ) const
{
    // Neue Werte zuweisen
    if ( (nStartIndex == rIdx.nStartIndex) &&
         (nCount      == rIdx.nCount)      &&
         (Container::operator ==( rIdx )) )
        return sal_True;
    else
        return sal_False;
}
/*************************************************************************
|*
|*    UniqueIdContainer::UniqueIdContainer ()
|*
*************************************************************************/

UniqueIdContainer::UniqueIdContainer( const UniqueIdContainer& rObj )
    : UniqueIndex( rObj )
    , nCollectCount( rObj.nCollectCount )
{
    sal_uIntPtr nCur = GetCurIndex();

    ImpUniqueId * pEle = (ImpUniqueId *)First();
    while( pEle )
    {
        pEle->nRefCount++;
        pEle = (ImpUniqueId *)Next();
    }
    Seek( nCur );
}

/*************************************************************************
|*
|*    UniqueIdContainer::operator = ()
|*
*************************************************************************/

UniqueIdContainer& UniqueIdContainer::operator = ( const UniqueIdContainer & rObj )
{
    UniqueIndex::operator = ( rObj );
    nCollectCount = rObj.nCollectCount;

    sal_uIntPtr nCur = GetCurIndex();

    ImpUniqueId * pEle = (ImpUniqueId *)First();
    while( pEle )
    {
        pEle->nRefCount++;
        pEle = (ImpUniqueId *)Next();
    }
    Seek( nCur );
    return *this;
}

/*************************************************************************
|*
|*    UniqueIdContainer::Clear()
|*
*************************************************************************/

void UniqueIdContainer::Clear( sal_Bool bAll )
{
    sal_uInt16 nFree = bAll ? 0xFFFF : 1;

    ImpUniqueId* pId = (ImpUniqueId*)Last();
    sal_Bool bLast = sal_True;
    while ( pId )
    {
        if ( pId->nRefCount <= nFree )
        {
            ((ImpUniqueId *)Remove( pId->nId ))->Release();
            if( bLast )
                pId = (ImpUniqueId *)Last();
            else
                pId = (ImpUniqueId *)Prev();
        }
        else
        {
            pId = (ImpUniqueId *)Prev();
            bLast = sal_False;
        }
    }
}

/*************************************************************************
|*
|*    UniqueIdContainer::CreateId()
|*
*************************************************************************/

UniqueItemId UniqueIdContainer::CreateId()
{
    if( nCollectCount > 50 )
    { // aufraeumen
        Clear( sal_False );
        nCollectCount = 0;
    }
    nCollectCount++;

    ImpUniqueId * pId = new ImpUniqueId;
    pId->nRefCount = 1;
    pId->nId = Insert( pId );
    return UniqueItemId( pId );
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
