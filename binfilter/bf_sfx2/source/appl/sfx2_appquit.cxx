/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_appquit.cxx,v $
 *
 *  $Revision: 1.13 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 08:01:40 $
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
#ifndef _BASMGR_HXX //autogen
#include "bf_basic/basmgr.hxx"
#endif

#ifdef WIN
#define _TL_LANG_SPECIAL
#endif

#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef _COM_SUN_STAR_LANG_XTYPEPROVIDER_HPP_
#include <com/sun/star/lang/XTypeProvider.hpp>
#endif

#include "appdata.hxx"
#include "plugobj.hxx"
#include "arrdecl.hxx"
#include "macrconf.hxx"

#include <bf_svtools/imgdef.hxx>

#include "frameobj.hxx"
#include "docfile.hxx"
#include "sfxtypes.hxx"
#include "appimp.hxx"
#include "fcontnr.hxx"
#include "nochaos.hxx"
#include "doctempl.hxx"
#include "dlgcont.hxx"
#include "scriptcont.hxx"
#include "misccfg.hxx"
#include "docfac.hxx"

namespace binfilter {

DECLARE_LIST( SfxFrameWindowFactoryArray_Impl, SfxFrameWindowFactory* )
SV_DECL_PTRARR(SfxInitLinkList, Link*, 2, 2)//STRIP008 ;

//-------------------------------------------------------------------------

/*?*/ void SfxApplication::Deinitialize()
/*?*/ {
/*?*/     if ( bDowning )
/*?*/         return;
/*?*/
/*?*/   StarBASIC::Stop();
/*?*/
/*?*/   bDowning = TRUE; // wegen Timer aus DecAliveCount und QueryExit
/*?*/
/*?*/   bDowning = FALSE;
/*?*/   DBG_ASSERT( !SfxObjectShell::GetFirst(),
/*?*/               "existing SfxObjectShell after Execute" );
/*?*/   bDowning = TRUE;
/*?*/
/*?*/   // call derived application-exit
/*?*/   bInExit = TRUE;
/*?*/   Exit();
/*?*/
/*?*/     // Controller u."a. freigeben
/*?*/     // dabei sollten auch restliche Komponenten ( Beamer! ) verschwinden
/*?*/   SfxObjectFactory::ClearAll_Impl();
//      pBasMgr = NULL;
/*?*/   if( pImp->pBasicLibContainer )
/*?*/       pImp->pBasicLibContainer->release();
/*?*/   if( pImp->pDialogLibContainer )
/*?*/       pImp->pDialogLibContainer->release();
/*?*/
/*?*/   bInExit = FALSE;
/*?*/
/*?*/   // ab hier d"urfen keine SvObjects mehr existieren
/*?*/   DELETEX(pAppData_Impl->pMatcher);
/*?*/   DELETEX(pAppData_Impl->pSfxFrameObjectFactoryPtr);
/*?*/
/*?*/   DELETEX(pAppData_Impl->pEventConfig);
/*?*/   DELETEX(pAppData_Impl->pMiscConfig);
/*?*/   SfxMacroConfig::Release_Impl();
/*?*/   DELETEX(pAppData_Impl->pInitLinkList);
/*?*/
/*?*/     DELETEX(pImp->pEventHdl);
/*?*/     DELETEX(pImp->pObjShells);
/*?*/
/*?*/   NoChaos::ReleaseItemPool();
/*?*/   pAppData_Impl->pPool = NULL;
/*?*/ }
}
