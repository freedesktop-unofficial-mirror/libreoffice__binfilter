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

#include <bf_svtools/undoopt.hxx>

#include "rtl/instance.hxx"
#include <unotools/configmgr.hxx>
#include <unotools/configitem.hxx>
#include <tools/debug.hxx>
#include <com/sun/star/uno/Any.hxx>
#include <com/sun/star/uno/Sequence.hxx>

#include <osl/mutex.hxx>
#include <bf_svtools/smplhint.hxx>
#include <vcl/svapp.hxx>
#include <osl/mutex.hxx>
#include <rtl/logfile.hxx>
#include "itemholder2.hxx"

using namespace utl;
using namespace com::sun::star::uno;

using ::rtl::OUString;

namespace binfilter
{

static SvtUndoOptions_Impl* pOptions = NULL;
static sal_Int32           nRefCount = 0;

#define STEPS 0

class SvtUndoOptions_Impl : public utl::ConfigItem, public SfxBroadcaster
{
    sal_Int32               nUndoCount;
    Sequence< rtl::OUString > m_aPropertyNames;

public:
                            SvtUndoOptions_Impl();

    virtual void            Notify( const com::sun::star::uno::Sequence< rtl::OUString >& aPropertyNames );
    virtual void            Commit();
    void                    Load();

    void                    SetUndoCount( sal_Int32 n ) { nUndoCount = n; SetModified();  }
    sal_Int32               GetUndoCount() const        { return nUndoCount; }
};

// -----------------------------------------------------------------------

SvtUndoOptions_Impl::SvtUndoOptions_Impl()
    : ConfigItem( OUString( RTL_CONSTASCII_USTRINGPARAM( "Office.Common/Undo" )) )
    , nUndoCount( 20 )
{
    Load();
}

void SvtUndoOptions_Impl::Commit()
{
    Sequence< Any > aValues( m_aPropertyNames.getLength() );
    Any* pValues = aValues.getArray();
    for ( int nProp = 0; nProp < m_aPropertyNames.getLength(); nProp++ )
    {
        switch ( nProp )
        {
            case STEPS :
                pValues[nProp] <<= nUndoCount;
                break;
            default:
                DBG_ERRORFILE( "invalid index to save a path" );
        }
    }

    PutProperties( m_aPropertyNames, aValues );
    //broadcast changes
    Broadcast(SfxSimpleHint(SFX_HINT_UNDO_OPTIONS_CHANGED));
}

// -----------------------------------------------------------------------
void SvtUndoOptions_Impl::Load()
{
    if(!m_aPropertyNames.getLength())
    {
        static const char* aPropNames[] =
        {
            "Steps",
        };

        const int nCount = sizeof( aPropNames ) / sizeof( const char* );
        m_aPropertyNames.realloc(nCount);
        OUString* pNames = m_aPropertyNames.getArray();
        for ( int i = 0; i < nCount; i++ )
            pNames[i] = OUString::createFromAscii( aPropNames[i] );
        EnableNotification( m_aPropertyNames );
    }

    Sequence< Any > aValues = GetProperties( m_aPropertyNames );
    const Any* pValues = aValues.getConstArray();
    DBG_ASSERT( aValues.getLength() == m_aPropertyNames.getLength(), "GetProperties failed" );
    if ( aValues.getLength() == m_aPropertyNames.getLength() )
    {
        for ( int nProp = 0; nProp < m_aPropertyNames.getLength(); nProp++ )
        {
            DBG_ASSERT( pValues[nProp].hasValue(), "property value missing" );
            if ( pValues[nProp].hasValue() )
            {
                switch ( nProp )
                {
                    case STEPS :
                    {
                        sal_Int32 nTemp = 0;
                        if ( pValues[nProp] >>= nTemp )
                            nUndoCount = nTemp;
                        else
                        {
                            OSL_FAIL( "Wrong Type!" );
                        }
                        break;
                    }

                    default:
                        OSL_FAIL( "Wrong Type!" );
                        break;
                }
            }
        }
    }
}
// -----------------------------------------------------------------------
void SvtUndoOptions_Impl::Notify( const Sequence<rtl::OUString>& )
{
    Load();
    //broadcast changes
    Broadcast(SfxSimpleHint(SFX_HINT_UNDO_OPTIONS_CHANGED));
}

// -----------------------------------------------------------------------
namespace
{
    class LocalSingleton : public rtl::Static< osl::Mutex, LocalSingleton >
    {
    };
}

// -----------------------------------------------------------------------
SvtUndoOptions::SvtUndoOptions()
{
    // Global access, must be guarded (multithreading)
    ::osl::MutexGuard aGuard( LocalSingleton::get() );
    if ( !pOptions )
    {
        RTL_LOGFILE_CONTEXT(aLog, "svtools ( ??? ) ::SvtUndoOptions_Impl::ctor()");
        pOptions = new SvtUndoOptions_Impl;

        ItemHolder2::holdConfigItem(E_UNDOOPTIONS);
    }
    ++nRefCount;
    pImp = pOptions;
    StartListening(*pImp);
}

// -----------------------------------------------------------------------

SvtUndoOptions::~SvtUndoOptions()
{
    // Global access, must be guarded (multithreading)
    ::osl::MutexGuard aGuard( LocalSingleton::get() );
    EndListening(*pImp);
    if ( !--nRefCount )
    {
        if ( pOptions->IsModified() )
            pOptions->Commit();
        DELETEZ( pOptions );
    }
}

void SvtUndoOptions::Notify( SfxBroadcaster&, const SfxHint& rHint )
{
    SolarMutexGuard aVclGuard;
    Broadcast( rHint );
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
