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

#include <comphelper/stl_types.hxx>

#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/container/XNameContainer.hpp>
#include <com/sun/star/drawing/PointSequence.hpp>


#include <cppuhelper/implbase2.hxx>

#include <bf_svtools/itempool.hxx>

#include <bf_svtools/itemset.hxx>

#include <bf_svtools/lstner.hxx>

#include <xlnedit.hxx>
#include <xlnstit.hxx>
#include "svdmodel.hxx"
#include "xdef.hxx"

#include <vector>

#include <osl/mutex.hxx>
#include <vcl/svapp.hxx>


#include "unoapi.hxx"
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::rtl;
using namespace ::cppu;

typedef std::vector< SfxItemSet* > ItemPoolVector;

class SvxUnoMarkerTable : public WeakImplHelper2< container::XNameContainer, lang::XServiceInfo >,
                          public SfxListener
{
private:
    SdrModel*       mpModel;
    SfxItemPool*    mpModelPool;

    ItemPoolVector maItemSetVector;

public:
    SvxUnoMarkerTable( SdrModel* pModel ) throw();
    virtual ~SvxUnoMarkerTable() throw();

    void dispose();

    // SfxListener
    virtual void Notify( SfxBroadcaster& rBC, const SfxHint& rHint ) throw ();

    void SAL_CALL ImplInsertByName( const OUString& aName, const uno::Any& aElement );

    // XServiceInfo
    virtual OUString SAL_CALL getImplementationName(  ) throw( uno::RuntimeException );
    virtual sal_Bool SAL_CALL supportsService( const  OUString& ServiceName ) throw( uno::RuntimeException);
    virtual uno::Sequence<  OUString > SAL_CALL getSupportedServiceNames(  ) throw( uno::RuntimeException);

    // XNameContainer
    virtual void SAL_CALL insertByName( const  OUString& aName, const  uno::Any& aElement ) throw( lang::IllegalArgumentException, container::ElementExistException, lang::WrappedTargetException, uno::RuntimeException);
    virtual void SAL_CALL removeByName( const  OUString& Name ) throw( container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException);

    // XNameReplace
    virtual void SAL_CALL replaceByName( const  OUString& aName, const  uno::Any& aElement ) throw( lang::IllegalArgumentException, container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException);

    // XNameAccess
    virtual uno::Any SAL_CALL getByName( const  OUString& aName ) throw( container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException);
    virtual uno::Sequence<  OUString > SAL_CALL getElementNames(  ) throw( uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasByName( const  OUString& aName ) throw( uno::RuntimeException);

    // XElementAccess
    virtual uno::Type SAL_CALL getElementType(  ) throw( uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasElements(  ) throw( uno::RuntimeException);
};

SvxUnoMarkerTable::SvxUnoMarkerTable( SdrModel* pModel ) throw()
: mpModel( pModel ),
  mpModelPool( pModel ? &pModel->GetItemPool() : (SfxItemPool*)NULL )
{
    if( pModel )
        StartListening( *pModel );
}

SvxUnoMarkerTable::~SvxUnoMarkerTable() throw()
{
    if( mpModel )
        EndListening( *mpModel );
    dispose();
}

void SvxUnoMarkerTable::dispose()
{
    ItemPoolVector::iterator aIter = maItemSetVector.begin();
    const ItemPoolVector::iterator aEnd = maItemSetVector.end();

    while( aIter != aEnd )
    {
        delete (*aIter++);
    }

    maItemSetVector.clear();
}

// SfxListener
void SvxUnoMarkerTable::Notify( SfxBroadcaster& /*rBC*/, const SfxHint& rHint ) throw()
{
    const SdrHint* pSdrHint = PTR_CAST( SdrHint, &rHint );

    if( pSdrHint && HINT_MODELCLEARED == pSdrHint->GetKind() )
        dispose();
}

sal_Bool SAL_CALL SvxUnoMarkerTable::supportsService( const  OUString& ServiceName ) throw(uno::RuntimeException)
{
    uno::Sequence< OUString > aSNL( getSupportedServiceNames() );
    const OUString * pArray = aSNL.getConstArray();

    for( INT32 i = 0; i < aSNL.getLength(); i++ )
        if( pArray[i] == ServiceName )
            return TRUE;

    return FALSE;
}

OUString SAL_CALL SvxUnoMarkerTable::getImplementationName() throw( uno::RuntimeException )
{
    return OUString( RTL_CONSTASCII_USTRINGPARAM("SvxUnoMarkerTable") );
}

uno::Sequence< OUString > SAL_CALL SvxUnoMarkerTable::getSupportedServiceNames(  )
    throw( uno::RuntimeException )
{
    uno::Sequence< OUString > aSNS( 1 );
    aSNS.getArray()[0] = OUString( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.drawing.MarkerTable" ));
    return aSNS;
}

void SAL_CALL SvxUnoMarkerTable::ImplInsertByName( const OUString& aName, const uno::Any& aElement )
{
    SfxItemSet* mpInSet = new SfxItemSet( *mpModelPool, XATTR_LINESTART, XATTR_LINEEND );
    maItemSetVector.push_back( mpInSet );

    XLineEndItem aEndMarker;
    aEndMarker.SetName( String( aName ) );
    aEndMarker.PutValue( aElement );

    mpInSet->Put( aEndMarker, XATTR_LINEEND );

    XLineStartItem aStartMarker;
    aStartMarker.SetName( String( aName ) );
    aStartMarker.PutValue( aElement );

    mpInSet->Put( aStartMarker, XATTR_LINESTART );
}

// XNameContainer
void SAL_CALL SvxUnoMarkerTable::insertByName( const OUString& aApiName, const uno::Any& aElement )
    throw( lang::IllegalArgumentException, container::ElementExistException, lang::WrappedTargetException, uno::RuntimeException )
{
    SolarMutexGuard aGuard;

    if( hasByName( aApiName ) )
        throw container::ElementExistException();

    String aName;
    SvxUnogetInternalNameForItem( XATTR_LINEEND, aApiName, aName );

    ImplInsertByName( aName, aElement );
}

void SAL_CALL SvxUnoMarkerTable::removeByName( const OUString& aApiName )
    throw( container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException)
{
    SolarMutexGuard aGuard;

    String Name;
    SvxUnogetInternalNameForItem( XATTR_LINEEND, aApiName, Name );

    ItemPoolVector::iterator aIter = maItemSetVector.begin();
    const ItemPoolVector::iterator aEnd = maItemSetVector.end();

    NameOrIndex *pItem;
    const String aSearchName( Name );

    while( aIter != aEnd )
    {
        pItem = (NameOrIndex *)&((*aIter)->Get( XATTR_LINEEND ) );
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
void SAL_CALL SvxUnoMarkerTable::replaceByName( const OUString& aApiName, const uno::Any& aElement )
    throw( lang::IllegalArgumentException, container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException )
{
    SolarMutexGuard aGuard;

    String aName;
    SvxUnogetInternalNameForItem( XATTR_LINEEND, aApiName, aName );

    ItemPoolVector::iterator aIter = maItemSetVector.begin();
    const ItemPoolVector::iterator aEnd = maItemSetVector.end();

    NameOrIndex *pItem;
    const String aSearchName( aName );

    while( aIter != aEnd )
    {
        pItem = (NameOrIndex *)&((*aIter)->Get( XATTR_LINEEND ) );
        if( pItem->GetName() == aSearchName )
        {
            XLineEndItem aEndMarker;
            aEndMarker.SetName( aSearchName );
            if( !aEndMarker.PutValue( aElement ) )
                throw lang::IllegalArgumentException();

            (*aIter)->Put( aEndMarker, XATTR_LINEEND );

            XLineStartItem aStartMarker;
            aStartMarker.SetName( aSearchName );
            aStartMarker.PutValue( aElement );

            (*aIter)->Put( aStartMarker, XATTR_LINESTART );
            return;
        }
        ++aIter;
    }

    // if it is not in our own sets, modify the pool!
    sal_Bool bFound = sal_False;

    USHORT nSurrogate;
    const USHORT nStartCount = mpModelPool ? mpModelPool->GetItemCount( XATTR_LINESTART ) : 0;
    for( nSurrogate = 0; nSurrogate < nStartCount; nSurrogate++ )
    {
        pItem = (NameOrIndex*)mpModelPool->GetItem( XATTR_LINESTART, nSurrogate);
        if( pItem && pItem->GetName() == aSearchName )
        {
            pItem->PutValue( aElement );
            bFound = sal_True;
            break;
        }
    }

    const USHORT nEndCount = mpModelPool ? mpModelPool->GetItemCount( XATTR_LINEEND ) : 0;
    for( nSurrogate = 0; nSurrogate < nEndCount; nSurrogate++ )
    {
        pItem = (NameOrIndex*)mpModelPool->GetItem( XATTR_LINEEND, nSurrogate);
        if( pItem && pItem->GetName() == aSearchName )
        {
            pItem->PutValue( aElement );
            bFound = sal_True;
            break;
        }
    }

    if( bFound )
        ImplInsertByName( aName, aElement );
    else
        throw container::NoSuchElementException();
}

static sal_Bool getByNameFromPool( const String& rSearchName, SfxItemPool* pPool, USHORT nWhich, uno::Any& rAny )
{
    NameOrIndex *pItem;
    const sal_Int32 nSurrogateCount = pPool ? (sal_Int32)pPool->GetItemCount( nWhich ) : 0;
    for( sal_Int32 nSurrogate = 0; nSurrogate < nSurrogateCount; nSurrogate++ )
    {
        pItem = (NameOrIndex*)pPool->GetItem( nWhich, (USHORT)nSurrogate );

        if( pItem && pItem->GetName() == rSearchName )
        {
            pItem->QueryValue( rAny, 0 );
            return sal_True;
        }
    }

    return sal_False;
}

// XNameAccess
uno::Any SAL_CALL SvxUnoMarkerTable::getByName( const OUString& aApiName )
    throw( container::NoSuchElementException,  lang::WrappedTargetException, uno::RuntimeException)
{
    SolarMutexGuard aGuard;

    String aName;
    SvxUnogetInternalNameForItem( XATTR_LINEEND, aApiName, aName );

    uno::Any aAny;

    if( mpModelPool && aName.Len() != 0 )
    {
        do
        {
            const String aSearchName( aName );
            if( getByNameFromPool( aSearchName, mpModelPool, XATTR_LINESTART, aAny ) )
                break;

            if( getByNameFromPool( aSearchName, mpModelPool, XATTR_LINEEND, aAny ) )
                break;

            throw container::NoSuchElementException();
        }
        while(0);
    }

    return aAny;
}

static void createNamesForPool( SfxItemPool* pPool, USHORT nWhich, std::set< OUString, comphelper::UStringLess >& rNameSet )
{
    const sal_Int32 nSuroCount = pPool->GetItemCount( nWhich );
    sal_Int32 nSurrogate;

    NameOrIndex *pItem;
    OUString aName;

    for( nSurrogate = 0; nSurrogate < nSuroCount; nSurrogate++ )
    {
        pItem = (NameOrIndex*)pPool->GetItem( nWhich, (USHORT)nSurrogate );

        if( pItem == NULL || pItem->GetName().Len() == 0 )
            continue;

        SvxUnogetApiNameForItem( XATTR_LINEEND, pItem->GetName(), aName );
        rNameSet.insert( aName );
    }
}

uno::Sequence< OUString > SAL_CALL SvxUnoMarkerTable::getElementNames()
    throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;

    std::set< OUString, comphelper::UStringLess > aNameSet;

    // search model pool for line starts
    createNamesForPool( mpModelPool, XATTR_LINESTART, aNameSet );

    // search model pool for line ends
    createNamesForPool( mpModelPool, XATTR_LINEEND, aNameSet );

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

sal_Bool SAL_CALL SvxUnoMarkerTable::hasByName( const OUString& aName )
    throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;

    if( aName.getLength() == 0 )
        return sal_False;

    String aSearchName;

    NameOrIndex *pItem;

    SvxUnogetInternalNameForItem( XATTR_LINESTART, aName, aSearchName );
    USHORT nStartCount = mpModelPool ? mpModelPool->GetItemCount( XATTR_LINESTART ) : 0;
    USHORT nSurrogate;
    for( nSurrogate = 0; nSurrogate < nStartCount; nSurrogate++ )
    {
        pItem = (NameOrIndex*)mpModelPool->GetItem( XATTR_LINESTART, nSurrogate);
        if( pItem && pItem->GetName() == aSearchName )
            return sal_True;
    }

    SvxUnogetInternalNameForItem( XATTR_LINEEND, aName, aSearchName );
    USHORT nEndCount = mpModelPool ? mpModelPool->GetItemCount( XATTR_LINEEND ) : 0;
    for( nSurrogate = 0; nSurrogate < nEndCount; nSurrogate++ )
    {
        pItem = (NameOrIndex*)mpModelPool->GetItem( XATTR_LINEEND, nSurrogate);
        if( pItem && pItem->GetName() == aSearchName )
            return sal_True;
    }

    return sal_False;
}

// XElementAccess
uno::Type SAL_CALL SvxUnoMarkerTable::getElementType(  )
    throw( uno::RuntimeException )
{
    return ::getCppuType((const drawing::PointSequence*)0);
}

sal_Bool SAL_CALL SvxUnoMarkerTable::hasElements(  )
    throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;

    NameOrIndex *pItem;

    const USHORT nStartCount = mpModelPool ? mpModelPool->GetItemCount( XATTR_LINESTART ) : 0;
    USHORT nSurrogate;
    for( nSurrogate = 0; nSurrogate < nStartCount; nSurrogate++ )
    {
        pItem = (NameOrIndex*)mpModelPool->GetItem( XATTR_LINESTART, nSurrogate);
        if( pItem && pItem->GetName().Len() != 0 )
            return sal_True;
    }

    const USHORT nEndCount = mpModelPool ? mpModelPool->GetItemCount( XATTR_LINEEND ) : 0;
    for( nSurrogate = 0; nSurrogate < nEndCount; nSurrogate++ )
    {
        pItem = (NameOrIndex*)mpModelPool->GetItem( XATTR_LINEEND, nSurrogate);
        if( pItem && pItem->GetName().Len() != 0 )
            return sal_True;
    }

    return sal_False;
}

/**
 * Create a hatchtable
 */
uno::Reference< uno::XInterface > SAL_CALL SvxUnoMarkerTable_createInstance( SdrModel* pModel )
{
    return *new SvxUnoMarkerTable(pModel);
}



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
