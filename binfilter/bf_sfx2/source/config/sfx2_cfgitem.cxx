/*************************************************************************
 *
 *  $RCSfile: sfx2_cfgitem.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:09 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#pragma hdrstop

#include "cfgitem.hxx"
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
//STRIP001     if ( m_pCfgMgr )
//STRIP001     {
//STRIP001         if ( m_bModified )
//STRIP001             m_pCfgMgr->StoreConfigItem( *this );
//STRIP001         m_pCfgMgr->RemoveConfigItem( *this );
//STRIP001     }
//STRIP001
//STRIP001     m_pCfgMgr = pMgr;
//STRIP001     if ( m_pCfgMgr )
//STRIP001     {
//STRIP001         m_pCfgMgr->AddConfigItem( *this );
//STRIP001         ReInitialize();
//STRIP001     }
/*?*/ }

/*?*/ BOOL SfxConfigItem::ReInitialize()
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE; //STRIP001
//STRIP001     m_bInitialized = FALSE;
//STRIP001     return Initialize();
/*?*/ }

/*?*/ String SfxConfigItem::GetStreamName( USHORT nType )
/*?*/ {
/*?*/     return SfxConfigManagerImExport_Impl::GetStreamName( nType );
/*?*/ }

/*N*/ void SfxConfigItem::Connect( SfxConfigManager* pMgr )
/*N*/ {
/*N*/   m_pCfgMgr = pMgr; pMgr->AddConfigItem(*this);
/*N*/ }
}
