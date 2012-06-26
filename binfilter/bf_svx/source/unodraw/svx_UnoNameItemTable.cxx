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

#include <set>

#include <bf_svtools/itempool.hxx>

#include <bf_svtools/itemset.hxx>


#include <comphelper/stl_types.hxx>

#include "svdmodel.hxx"

#include "UnoNameItemTable.hxx"

#include <osl/mutex.hxx>
#include <vcl/svapp.hxx>

#include "unoapi.hxx"
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::rtl;
using namespace ::cppu;

SvxUnoNameItemTable::SvxUnoNameItemTable( SdrModel* pModel, USHORT nWhich, BYTE nMemberId ) throw()
: mpModel( pModel ),
  mpModelPool( pModel ? &pModel->GetItemPool() : NULL ),
  mnWhich( nWhich ), mnMemberId( nMemberId )
{
    if( pModel )
        StartListening( *pModel );
}

SvxUnoNameItemTable::~SvxUnoNameItemTable() throw()
{
    if( mpModel )
        EndListening( *mpModel );
    dispose();
}

void SvxUnoNameItemTable::dispose()
{
    ItemPoolVector::iterator aIter = maItemSetVector.begin();
    const ItemPoolVector::iterator aEnd = maItemSetVector.end();

    while( aIter != aEnd )
    {
        delete (*aIter++);
    }

    maItemSetVector.clear();
}

void SvxUnoNameItemTable::Notify( SfxBroadcaster& /*rBC*/, const SfxHint& rHint ) throw()
{
    const SdrHint* pSdrHint = PTR_CAST( SdrHint, &rHint );

    if( pSdrHint && HINT_MODELCLEARED == pSdrHint->GetKind() )
        dispose();
}

sal_Bool SAL_CALL SvxUnoNameItemTable::supportsService( const  OUString& ServiceName ) throw(uno::RuntimeException)
{
    uno::Sequence< OUString > aSNL( getSupportedServiceNames() );
    const OUString * pArray = aSNL.getConstArray();

    for( INT32 i = 0; i < aSNL.getLength(); i++ )
        if( pArray[i] == ServiceName )
            return TRUE;

    return FALSE;
}

void SAL_CALL SvxUnoNameItemTable::ImplInsertByName( const OUString& aName, const uno::Any& aElement )
{
    SfxItemSet* mpInSet = new SfxItemSet( *mpModelPool, mnWhich, mnWhich );
    maItemSetVector.push_back( mpInSet );

    NameOrIndex* pNewItem = createItem();
    pNewItem->SetName( String( aName ) );
    pNewItem->PutValue( aElement, mnMemberId );
    mpInSet->Put( *pNewItem, mnWhich );
    delete pNewItem;
}

// XNameContainer
void SAL_CALL SvxUnoNameItemTable::insertByName( const OUString& aApiName, const uno::Any& aElement )
    throw( lang::IllegalArgumentException, container::ElementExistException, lang::WrappedTargetException, uno::RuntimeException )
{
    SolarMutexGuard aGuard;

    if( hasByName( aApiName ) )
        throw container::ElementExistException();

    String aName;
    SvxUnogetInternalNameForItem( mnWhich, aApiName, aName );

    ImplInsertByName( aName, aElement );
}



void SAL_CALL SvxUnoNameItemTable::removeByName( const OUString& aApiName )
    throw( container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException)
{
    SolarMutexGuard aGuard;

    String Name;
    SvxUnogetInternalNameForItem( mnWhich, aApiName, Name );

    ItemPoolVector::iterator aIter = maItemSetVector.begin();
    const ItemPoolVector::iterator aEnd = maItemSetVector.end();

    NameOrIndex *pItem;
    const String aSearchName( Name );

    while( aIter != aEnd )
    {
        pItem = (NameOrIndex *)&((*aIter)->Get( mnWhich ) );
        if( pItem->GetName() == aSearchName )
        {
            delete (*aIter);
            maItemSetVector.erase( aIter );
            return;
        }
        ++aIter;
    }

    if( !hasByName( Name ) )
        throw container::NoSuchElementException();
}

// XNameReplace
void SAL_CALL SvxUnoNameItemTable::replaceByName( const OUString& aApiName, const uno::Any& aElement )
    throw( lang::IllegalArgumentException, container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException )
{
    SolarMutexGuard aGuard;

    String aName;
    SvxUnogetInternalNameForItem( mnWhich, aApiName, aName );

    ItemPoolVector::iterator aIter = maItemSetVector.begin();
    const ItemPoolVector::iterator aEnd = maItemSetVector.end();

    NameOrIndex *pItem;
    const String aSearchName( aName );

    while( aIter != aEnd )
    {
        pItem = (NameOrIndex *)&((*aIter)->Get( mnWhich ) );
        if( pItem->GetName() == aSearchName )
        {
            NameOrIndex* pNewItem = createItem();
            pNewItem->SetName( aSearchName );
            if( !pNewItem->PutValue( aElement, mnMemberId ) )
                throw lang::IllegalArgumentException();

            (*aIter)->Put( *pNewItem );
            return;
        }
        ++aIter;
    }

    // if it is not in our own sets, modify the pool!
    sal_Bool bFound = sal_False;

    USHORT nSurrogate;
    USHORT nCount = mpModelPool ? mpModelPool->GetItemCount( mnWhich ) : 0;
    for( nSurrogate = 0; nSurrogate < nCount; nSurrogate++ )
    {
        pItem = (NameOrIndex*)mpModelPool->GetItem( mnWhich, nSurrogate);
        if( pItem && pItem->GetName() == aSearchName )
        {
            pItem->PutValue( aElement, mnMemberId );
            bFound = sal_True;
            break;
        }
    }

    if( bFound )
        ImplInsertByName( aName, aElement );
    else
        throw container::NoSuchElementException();

    if( !hasByName( aName ) )
        throw container::NoSuchElementException();
}

// XNameAccess
uno::Any SAL_CALL SvxUnoNameItemTable::getByName( const OUString& aApiName )
    throw( container::NoSuchElementException,  lang::WrappedTargetException, uno::RuntimeException)
{
    SolarMutexGuard aGuard;

    String aName;
    SvxUnogetInternalNameForItem( mnWhich, aApiName, aName );

    uno::Any aAny;

    if( mpModelPool && aName.Len() != 0 )
    {
        const String aSearchName( aName );
        NameOrIndex *pItem;
        sal_Int32 nSurrogate;

        sal_Int32 nSurrogateCount = mpModelPool ? (sal_Int32)mpModelPool->GetItemCount( mnWhich ) : 0;
        for( nSurrogate = 0; nSurrogate < nSurrogateCount; nSurrogate++ )
        {
            pItem = (NameOrIndex*)mpModelPool->GetItem( mnWhich, (USHORT)nSurrogate );

            if( pItem && pItem->GetName() == aSearchName )
            {
                pItem->QueryValue( aAny, mnMemberId );
                return aAny;
            }
        }
    }

    throw container::NoSuchElementException();
    return aAny;
}

uno::Sequence< OUString > SAL_CALL SvxUnoNameItemTable::getElementNames(  )
    throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;

    std::set< OUString, comphelper::UStringLess > aNameSet;

    NameOrIndex *pItem;
    OUString aApiName;

    const sal_Int32 nSurrogateCount = mpModelPool ? (sal_Int32)mpModelPool->GetItemCount( mnWhich ) : 0;
    sal_Int32 nSurrogate;
    for( nSurrogate = 0; nSurrogate < nSurrogateCount; nSurrogate++ )
    {
        pItem = (NameOrIndex*)mpModelPool->GetItem( mnWhich, (USHORT)nSurrogate );

        if( pItem == NULL || pItem->GetName().Len() == 0 )
            continue;

        SvxUnogetApiNameForItem( mnWhich, pItem->GetName(), aApiName );
        aNameSet.insert( aApiName );
    }

    uno::Sequence< OUString > aSeq( aNameSet.size() );
    OUString* pNames = aSeq.getArray();

    std::set< OUString, comphelper::UStringLess >::iterator aIter( aNameSet.begin() );
    const std::set< OUString, comphelper::UStringLess >::iterator aEnd( aNameSet.end() );

    while( aIter != aEnd )
    {
        *pNames++ = *aIter++;
    }

    return aSeq;
}

sal_Bool SAL_CALL SvxUnoNameItemTable::hasByName( const OUString& aApiName )
    throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;

    String aName;
    SvxUnogetInternalNameForItem( mnWhich, aApiName, aName );

    if( aName.Len() == 0 )
        return sal_False;

    const String aSearchName( aName );
    USHORT nSurrogate;

    const NameOrIndex *pItem;

    USHORT nCount = mpModelPool ? mpModelPool->GetItemCount( mnWhich ) : 0;
    for( nSurrogate = 0; nSurrogate < nCount; nSurrogate++ )
    {
        pItem = (NameOrIndex*)mpModelPool->GetItem( mnWhich, nSurrogate );
        if( pItem && pItem->GetName() == aSearchName )
            return sal_True;
    }

    return sal_False;
}

sal_Bool SAL_CALL SvxUnoNameItemTable::hasElements(  )
    throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;

    const NameOrIndex *pItem;

    sal_Int32 nSurrogate;
    const sal_Int32 nSurrogateCount = mpModelPool ? (sal_Int32)mpModelPool->GetItemCount( mnWhich ) : 0;
    for( nSurrogate = 0; nSurrogate < nSurrogateCount; nSurrogate++ )
    {
        pItem = (NameOrIndex*)mpModelPool->GetItem( mnWhich, (USHORT)nSurrogate );

        if( pItem && pItem->GetName().Len() != 0 )
            return sal_True;
    }

    return sal_False;
}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
