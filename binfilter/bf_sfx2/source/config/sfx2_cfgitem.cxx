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

#include "cfgmgr.hxx"
#include "sfx.hrc"
#include "cfgimpl.hxx"
#include <tools/debug.hxx>
namespace binfilter {
// class SfxConfigItem ---------------------------------------------------

/*N*/ SfxConfigItem::SfxConfigItem( USHORT nType, SfxConfigManager* pCfgMgr )
/*N*/   : m_pCfgMgr( pCfgMgr )
/*N*/   , m_nType( nType )
/*N*/   , m_bDefault( TRUE )
/*N*/     , m_bModified( FALSE )
/*N*/     , m_bInitialized( FALSE )
/*N*/ {
/*N*/     if ( pCfgMgr )
/*N*/         pCfgMgr->AddConfigItem( *this );
/*N*/ }

/*N*/ SfxConfigItem::~SfxConfigItem()
/*N*/ {
/*N*/     if ( m_pCfgMgr )
/*N*/         m_pCfgMgr->RemoveConfigItem( *this );
/*N*/ }

// ----------------------------------------------------------------------
/*N*/ BOOL SfxConfigItem::Initialize()
/*N*/ {
/*N*/   BOOL bRet = TRUE;
/*N*/   if ( !m_pCfgMgr )
/*N*/       UseDefault();
/*N*/   else
/*N*/         bRet = m_pCfgMgr->LoadConfigItem( *this );
/*N*/     m_bModified = FALSE;
/*N*/     m_bInitialized = TRUE;
/*N*/   return bRet;
/*N*/ }

// ----------------------------------------------------------------------
BOOL SfxConfigItem::StoreConfig()
{
    m_bModified = FALSE;
    return FALSE;;
}

// ------------------------------------------------------------------------
/*N*/ void SfxConfigItem::SetDefault( BOOL bOn )
/*N*/ {
/*N*/     if ( m_bInitialized && (!bOn || !m_bDefault) )
/*?*/       SetModified( TRUE );
/*N*/   m_bDefault = bOn;
/*N*/ }

//-------------------------------------------------------------------------
/*N*/ void SfxConfigItem::SetModified( BOOL bMod )
/*N*/ {
/*N*/     if ( m_bInitialized )
/*N*/         m_bModified = bMod;
/*N*/ }

/*?*/ String SfxConfigItem::GetStreamName( USHORT /*nType*/ )
/*?*/ {
/*?*/     return String();
/*?*/ }

/*N*/ void SfxConfigItem::Connect( SfxConfigManager* pMgr )
/*N*/ {
/*N*/   m_pCfgMgr = pMgr; pMgr->AddConfigItem(*this);
/*N*/ }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
