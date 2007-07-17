/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_module.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 10:38:12 $
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

#include <stdio.h>
#include <tools/rcid.h>

#include <cstdarg>
#include "app.hxx"
#include "arrdecl.hxx"
#include "docfac.hxx"
#include "module.hxx"

namespace binfilter {

static SfxModuleArr_Impl* pModules=0;

/*N*/ TYPEINIT1(SfxModule, SfxShell);

/*?*/ BOOL SfxModule::QueryUnload()
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
/*?*/ }

/*?*/ SfxModule* SfxModule::Load()
/*?*/ {
/*?*/   return 0;
/*?*/ }

/*?*/ void SfxModule::Free()
/*?*/ {
/*?*/ }


/*N*/ ResMgr* SfxModule::GetResMgr()
/*N*/ {
/*N*/   return pResMgr;
/*N*/ }

//====================================================================
/*N*/ SfxModule::SfxModule( ResMgr* pMgrP, BOOL bDummyP,
/*N*/                     SfxObjectFactory* pFactoryP, ... )
/*N*/   : pResMgr( pMgrP ), bDummy( bDummyP )
/*N*/ {
/*N*/   if( !bDummy )
/*N*/   {
/*N*/       SfxApplication *pApp = SFX_APP();
/*N*/       SfxModuleArr_Impl& rArr = GetModules_Impl();
/*N*/       SfxModule* pPtr = (SfxModule*)this;
/*N*/       rArr.C40_INSERT( SfxModule, pPtr, rArr.Count() );
/*N*/       SetPool( &pApp->GetPool() );
/*N*/   }
/*N*/   va_list pVarArgs;
/*N*/   va_start( pVarArgs, pFactoryP );
/*N*/   for ( SfxObjectFactory *pArg = pFactoryP; pArg;
/*N*/        pArg = va_arg( pVarArgs, SfxObjectFactory* ) )
/*N*/       pArg->SetModule_Impl( this );
/*N*/   va_end(pVarArgs);
/*N*/ }

/*N*/ SfxModule::~SfxModule()
/*N*/ {
/*N*/   if( !bDummy )
/*N*/   {
/*N*/       if ( SFX_APP()->Get_Impl() )
/*N*/       {
/*N*/           // Das Modul wird noch vor dem DeInitialize zerst"ort, also auis dem Array entfernen
/*N*/           SfxModuleArr_Impl& rArr = GetModules_Impl();
/*N*/           for( USHORT nPos = rArr.Count(); nPos--; )
/*N*/           {
/*N*/               if( rArr[ nPos ] == this )
/*N*/               {
/*N*/                   rArr.Remove( nPos );
/*N*/                   break;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/
/*N*/       delete pResMgr;
/*N*/   }
/*N*/ }

/*N*/ SfxModuleArr_Impl& SfxModule::GetModules_Impl()
/*N*/ {
/*N*/     if( !pModules )
/*N*/         pModules = new SfxModuleArr_Impl;
/*N*/     return *pModules;
/*N*/ };
}
