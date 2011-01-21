/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/
#include "ParseContext.hxx"
#include <tools/debug.hxx>
#include "fmresids.hrc"
#include "dialmgr.hxx"
#include <vcl/svapp.hxx>
#include <osl/mutex.hxx>

#include <tools/shl.hxx>

namespace binfilter {


using namespace svxform;
using namespace ::connectivity;
//==========================================================================
//= OSystemParseContext
//==========================================================================
/*N*/ DBG_NAME(OSystemParseContext)
//-----------------------------------------------------------------------------
/*N*/ OSystemParseContext::OSystemParseContext() : IParseContext()
/*N*/ {
/*N*/   DBG_CTOR(OSystemParseContext,NULL);
/*N*/   SolarMutexGuard aGuard;
/*N*/   m_aSQLInternationals = ByteString(SVX_RES(RID_STR_SVT_SQL_INTERNATIONAL),RTL_TEXTENCODING_ASCII_US);
/*N*/ }

//-----------------------------------------------------------------------------
/*?*/ OSystemParseContext::~OSystemParseContext()
/*?*/ {
/*?*/   DBG_DTOR(OSystemParseContext,NULL);
/*?*/ }

//-----------------------------------------------------------------------------
/*?*/ ::com::sun::star::lang::Locale OSystemParseContext::getPreferredLocale( ) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); ::com::sun::star::lang::Locale alocal; return alocal;
/*?*/ }

//-----------------------------------------------------------------------------
/*?*/ ::rtl::OUString OSystemParseContext::getErrorMessage(ErrorCode) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); String astring; return astring;
/*?*/ }

//-----------------------------------------------------------------------------
/*?*/ ::rtl::OString OSystemParseContext::getIntlKeywordAscii(InternationalKeyCode) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); ByteString aKeyword; return aKeyword;
/*?*/ }

// -----------------------------------------------------------------------------
/*?*/ IParseContext::InternationalKeyCode OSystemParseContext::getIntlKeyCode(const ::rtl::OString&) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return KEY_NONE;
/*?*/ }


// =============================================================================
namespace
{
    // -----------------------------------------------------------------------------
/*N*/   ::osl::Mutex& getSafteyMutex()
/*N*/   {
/*N*/       static ::osl::Mutex s_aSafety;
/*N*/       return s_aSafety;
/*N*/   }
    // -----------------------------------------------------------------------------
/*N*/   oslInterlockedCount& getCounter()
/*N*/   {
/*N*/       static oslInterlockedCount s_nCounter;
/*N*/       return s_nCounter;
/*N*/   }
    // -----------------------------------------------------------------------------
/*N*/   OSystemParseContext* getSharedContext(OSystemParseContext* _pContext = NULL,sal_Bool _bSet = sal_False)
/*N*/   {
/*N*/       static OSystemParseContext* s_pSharedContext = NULL;
/*N*/       if ( _pContext && !s_pSharedContext )
/*N*/       {
/*N*/           s_pSharedContext = _pContext;
/*N*/           return s_pSharedContext;
/*N*/       }
/*N*/       if ( _bSet )
/*N*/       {
/*N*/               OSystemParseContext* pReturn = _pContext ? _pContext : s_pSharedContext;
/*N*/           s_pSharedContext = _pContext;
/*N*/           return pReturn;
/*N*/       }
/*N*/       return s_pSharedContext;
    }
    // -----------------------------------------------------------------------------
}
// -----------------------------------------------------------------------------
/*N*/ OParseContextClient::OParseContextClient()
/*N*/ {
/*N*/   ::osl::MutexGuard aGuard( getSafteyMutex() );
/*N*/   if ( 1 == osl_incrementInterlockedCount( &getCounter() ) )
/*N*/   {   // first instance
/*N*/       getSharedContext( new OSystemParseContext );
/*N*/   }
/*N*/ }

// -----------------------------------------------------------------------------
/*N*/ OParseContextClient::~OParseContextClient()
/*N*/ {
/*N*/   {
/*N*/       ::osl::MutexGuard aGuard( getSafteyMutex() );
/*N*/       if ( 0 == osl_decrementInterlockedCount( &getCounter() ) )
/*N*/           delete getSharedContext(NULL,sal_True);
/*N*/   }
/*N*/ }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
