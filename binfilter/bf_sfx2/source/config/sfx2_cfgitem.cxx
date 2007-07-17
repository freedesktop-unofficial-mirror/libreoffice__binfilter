/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_cfgitem.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 10:42:43 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#pragma hdrstop

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
/*N*/ BOOL SfxConfigItem::StoreConfig()
/*N*/ {
/*N*/   BOOL bRet = FALSE;
/*N*/     if ( m_pCfgMgr && m_bModified )
/*?*/         bRet = m_pCfgMgr->StoreConfigItem( *this );
/*N*/   m_bModified = FALSE;
/*N*/   return bRet;
/*N*/ }

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
/*N*/     {
/*N*/         m_bModified = bMod;
/*N*/         if ( bMod && m_pCfgMgr )
/*?*/             m_pCfgMgr->SetModified( bMod );
/*N*/     }
/*N*/ }

/*?*/ void SfxConfigItem::ReConnect( SfxConfigManager* pMgr )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }

/*?*/ BOOL SfxConfigItem::ReInitialize()
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE; //STRIP001
/*?*/ }

/*?*/ String SfxConfigItem::GetStreamName( USHORT nType )
/*?*/ {
/*?*/     return String();
/*?*/ }

/*N*/ void SfxConfigItem::Connect( SfxConfigManager* pMgr )
/*N*/ {
/*N*/   m_pCfgMgr = pMgr; pMgr->AddConfigItem(*this);
/*N*/ }
}
