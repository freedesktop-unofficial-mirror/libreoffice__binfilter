/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_module.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: rt $ $Date: 2007-04-26 07:12:28 $
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
#include "sfxresid.hxx"
#include "msgpool.hxx"
#include "tbxctrl.hxx"
#include "stbitem.hxx"
#include "mnuitem.hxx"
#include "childwin.hxx"
#include "mnumgr.hxx"
#include "docfac.hxx"
#include "objface.hxx"
#include "viewfrm.hxx"

#define SfxModule
namespace binfilter {
#include "sfxslots.hxx"

static SfxModuleArr_Impl* pModules=0;

class SfxModule_Impl
{
public:

    SfxSlotPool*                pSlotPool;
    SfxTbxCtrlFactArr_Impl*     pTbxCtrlFac;
    SfxStbCtrlFactArr_Impl*     pStbCtrlFac;
    SfxMenuCtrlFactArr_Impl*    pMenuCtrlFac;
    SfxChildWinFactArr_Impl*    pFactArr;
    ImageList*                  pImgListSmall;
    ImageList*                  pImgListBig;
    ImageList*                  pImgListHiSmall;
    ImageList*                  pImgListHiBig;

                                SfxModule_Impl();
                                ~SfxModule_Impl();
    ImageList*                  GetImageList( ResMgr*, BOOL, BOOL bHiContrast = FALSE );
};

/*N*/ SfxModule_Impl::SfxModule_Impl()
/*N*/  : pSlotPool(0)
/*N*/ {
/*N*/ }

/*N*/ SfxModule_Impl::~SfxModule_Impl()
/*N*/ {
/*N*/   delete pSlotPool;
/*N*/   delete pTbxCtrlFac;
/*N*/   delete pStbCtrlFac;
/*N*/   delete pMenuCtrlFac;
/*N*/   delete pFactArr;
/*N*/     delete pImgListSmall;
/*N*/     delete pImgListBig;
/*N*/     delete pImgListHiSmall;
/*N*/     delete pImgListHiBig;
/*N*/ }

/*N*/ ImageList* SfxModule_Impl::GetImageList( ResMgr* pResMgr, BOOL bBig, BOOL bHiContrast )
/*N*/ {
/*N*/     ImageList*& rpList = bBig ? ( bHiContrast ? pImgListHiBig: pImgListBig ) :
/*N*/                               ( bHiContrast ? pImgListHiSmall : pImgListSmall );
/*N*/     if ( !rpList )
/*N*/     {
/*N*/         ResId aResId( bBig ? ( bHiContrast ? RID_DEFAULTIMAGELIST_LCH : RID_DEFAULTIMAGELIST_LC ) :
/*N*/                            ( bHiContrast ? RID_DEFAULTIMAGELIST_SCH : RID_DEFAULTIMAGELIST_SC ), *pResMgr );
/*N*/         aResId.SetRT( RSC_IMAGELIST );
/*N*/
/*N*/         DBG_ASSERT( pResMgr->IsAvailable(aResId), "No default ImageList!" );
/*N*/
/*N*/         if ( pResMgr->IsAvailable(aResId) )
/*N*/             rpList = new ImageList( aResId );
/*N*/         else
/*?*/             rpList = new ImageList();
/*N*/     }
/*N*/
/*N*/     return rpList;
/*N*/ }

/*N*/ TYPEINIT1(SfxModule, SfxShell);

//=========================================================================

/*N*/ SFX_IMPL_INTERFACE(SfxModule,SfxShell,SfxResId(0))
/*N*/ {
/*N*/ }

//====================================================================

/*?*/ ModalDialog* SfxModule::CreateAboutDialog()
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001
/*?*/ }

//====================================================================

/*?*/ BOOL SfxModule::QueryUnload()
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
/*?*/ }

//====================================================================

/*?*/ SfxModule* SfxModule::Load()

/*  [Description]

    This methode must be overrided in subclasses to load the real module.
    In your dummy subclass you implement it as follows ('...' is the name
    of your library, e.g. 'Sd'):

        SfxModule* ...ModuleDummy::Load()
        {
            return LoadLib...() ? ..._MOD() : 0;
        }

    In your real subclass you implement it as follows:

        SfxModule* ...Module::Load()
        {
            return this;
        }

    The code must be behind the invocation of SFX_...OBJECTFACTORY_LIB,
    which defines the function LoadLib...().
*/
/*?*/ {
/*?*/   return 0;
/*?*/ }

//====================================================================

/*?*/ void SfxModule::Free()

/*  [Description]

    This methode must be overrided in subclasses to free the real module.
    In your real subclass you implement it as follows ('...' is the name
    of your library, e.g. 'Sd'):

        void ...Module::Free()
        {
            FreeLib...();
        }

    The code must be behind the invocation of SFX_...OBJECTFACTORY_LIB,
    which defines the function LoadLib...().
*/

/*?*/ {
/*?*/ }


//====================================================================

/*N*/ ResMgr* SfxModule::GetResMgr()
/*N*/ {
/*N*/   return pResMgr;
/*N*/ }

//====================================================================
/*
SfxModule::SfxModule( ResMgr* pMgrP, BOOL bDummyP,
                      SfxObjectFactory* pFactoryP )
    : pResMgr( pMgrP ), bDummy( bDummyP ), pImpl(0L)
{
    Construct_Impl();
    if ( pFactoryP )
        pFactoryP->SetModule_Impl( this );
}
*/
/*N*/ SfxModule::SfxModule( ResMgr* pMgrP, BOOL bDummyP,
/*N*/                     SfxObjectFactory* pFactoryP, ... )
/*N*/   : pResMgr( pMgrP ), bDummy( bDummyP ), pImpl(0L)
/*N*/ {
/*N*/   Construct_Impl();
/*N*/   va_list pVarArgs;
/*N*/   va_start( pVarArgs, pFactoryP );
/*N*/   for ( SfxObjectFactory *pArg = pFactoryP; pArg;
/*N*/        pArg = va_arg( pVarArgs, SfxObjectFactory* ) )
/*N*/       pArg->SetModule_Impl( this );
/*N*/   va_end(pVarArgs);
/*N*/ }

/*N*/ void SfxModule::Construct_Impl()
/*N*/ {
/*N*/   if( !bDummy )
/*N*/   {
/*N*/       SfxApplication *pApp = SFX_APP();
/*N*/         SfxModuleArr_Impl& rArr = GetModules_Impl();
/*N*/       SfxModule* pPtr = (SfxModule*)this;
/*N*/       rArr.C40_INSERT( SfxModule, pPtr, rArr.Count() );
/*N*/       pImpl = new SfxModule_Impl;
/*N*/       pImpl->pSlotPool = new SfxSlotPool( &pApp->GetAppSlotPool_Impl(), pResMgr );
/*N*/
/*N*/       pImpl->pTbxCtrlFac=0;
/*N*/       pImpl->pStbCtrlFac=0;
/*N*/       pImpl->pMenuCtrlFac=0;
/*N*/       pImpl->pFactArr=0;
/*N*/         pImpl->pImgListSmall=0;
/*N*/         pImpl->pImgListBig=0;
/*N*/         pImpl->pImgListHiSmall=0;
/*N*/         pImpl->pImgListHiBig=0;
/*N*/
/*N*/       SetPool( &pApp->GetPool() );
/*N*/   }
/*N*/ }

//====================================================================

/*N*/ SfxModule::~SfxModule()
/*N*/ {
/*N*/   if( !bDummy )
/*N*/   {
/*N*/       if ( SFX_APP()->Get_Impl() )
/*N*/       {
/*N*/           // Das Modul wird noch vor dem DeInitialize zerst"ort, also auis dem Array entfernen
/*N*/             SfxModuleArr_Impl& rArr = GetModules_Impl();
/*N*/           for( USHORT nPos = rArr.Count(); nPos--; )
/*N*/           {
/*N*/               if( rArr[ nPos ] == this )
/*N*/               {
/*N*/                   rArr.Remove( nPos );
/*N*/                   break;
/*N*/               }
/*N*/           }
/*N*/
/*N*/           delete pImpl;
/*N*/       }
/*N*/
/*N*/       delete pResMgr;
/*N*/   }
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ SfxSlotPool* SfxModule::GetSlotPool() const
/*N*/ {
/*N*/   return pImpl->pSlotPool;
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ void SfxModule::RegisterChildWindow(SfxChildWinFactory *pFact)
/*N*/ {
/*N*/   DBG_ASSERT( pImpl, "Kein echtes Modul!" );
/*N*/
/*N*/   if (!pImpl->pFactArr)
/*N*/       pImpl->pFactArr = new SfxChildWinFactArr_Impl;
/*N*/
/*N*/ //#ifdef DBG_UTIL
/*N*/   for (USHORT nFactory=0; nFactory<pImpl->pFactArr->Count(); ++nFactory)
/*N*/   {
/*N*/       if (pFact->nId ==  (*pImpl->pFactArr)[nFactory]->nId)
/*N*/       {
/*?*/           pImpl->pFactArr->Remove( nFactory );
/*?*/           DBG_ERROR("ChildWindow mehrfach registriert!");
/*?*/           return;
/*N*/       }
/*N*/   }
/*N*/ //#endif
/*N*/
/*N*/   pImpl->pFactArr->C40_INSERT(
/*N*/       SfxChildWinFactory, pFact, pImpl->pFactArr->Count() );
/*N*/ }

//-------------------------------------------------------------------------


//-------------------------------------------------------------------------

/*N*/ void SfxModule::RegisterToolBoxControl( SfxTbxCtrlFactory *pFact )
/*N*/ {
/*N*/   if (!pImpl->pTbxCtrlFac)
/*N*/       pImpl->pTbxCtrlFac = new SfxTbxCtrlFactArr_Impl;
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/   for ( USHORT n=0; n<pImpl->pTbxCtrlFac->Count(); n++ )
/*N*/   {
/*N*/       SfxTbxCtrlFactory *pF = (*pImpl->pTbxCtrlFac)[n];
/*N*/       if ( pF->nTypeId && pF->nTypeId == pFact->nTypeId &&
/*N*/           (pF->nSlotId == pFact->nSlotId || pF->nSlotId == 0) )
/*N*/       {
/*N*/           DBG_WARNING("TbxController-Registrierung ist nicht eindeutig!");
/*N*/       }
/*N*/   }
/*N*/ #endif
/*N*/
/*N*/   pImpl->pTbxCtrlFac->C40_INSERT( SfxTbxCtrlFactory, pFact, pImpl->pTbxCtrlFac->Count() );
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ void SfxModule::RegisterStatusBarControl( SfxStbCtrlFactory *pFact )
/*N*/ {
/*N*/   if (!pImpl->pStbCtrlFac)
/*N*/       pImpl->pStbCtrlFac = new SfxStbCtrlFactArr_Impl;
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/   for ( USHORT n=0; n<pImpl->pStbCtrlFac->Count(); n++ )
/*N*/   {
/*N*/       SfxStbCtrlFactory *pF = (*pImpl->pStbCtrlFac)[n];
/*N*/       if ( pF->nTypeId && pF->nTypeId == pFact->nTypeId &&
/*N*/           (pF->nSlotId == pFact->nSlotId || pF->nSlotId == 0) )
/*N*/       {
/*N*/           DBG_WARNING("StbController-Registrierung ist nicht eindeutig!");
/*N*/       }
/*N*/   }
/*N*/ #endif
/*N*/
/*N*/   pImpl->pStbCtrlFac->C40_INSERT( SfxStbCtrlFactory, pFact, pImpl->pStbCtrlFac->Count() );
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ void SfxModule::RegisterMenuControl( SfxMenuCtrlFactory *pFact )
/*N*/ {
/*N*/   if (!pImpl->pMenuCtrlFac)
/*N*/       pImpl->pMenuCtrlFac = new SfxMenuCtrlFactArr_Impl;
/*N*/
/*N*/ #ifdef DBG_UTIL
/*N*/   for ( USHORT n=0; n<pImpl->pMenuCtrlFac->Count(); n++ )
/*N*/   {
/*N*/       SfxMenuCtrlFactory *pF = (*pImpl->pMenuCtrlFac)[n];
/*N*/       if ( pF->nTypeId && pF->nTypeId == pFact->nTypeId &&
/*N*/           (pF->nSlotId == pFact->nSlotId || pF->nSlotId == 0) )
/*N*/       {
/*N*/           DBG_WARNING("MenuController-Registrierung ist nicht eindeutig!");
/*N*/       }
/*N*/   }
/*N*/ #endif
/*N*/
/*N*/   pImpl->pMenuCtrlFac->C40_INSERT( SfxMenuCtrlFactory, pFact, pImpl->pMenuCtrlFac->Count() );
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ SfxTbxCtrlFactArr_Impl*  SfxModule::GetTbxCtrlFactories_Impl() const
/*N*/ {
/*N*/   return pImpl->pTbxCtrlFac;
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ SfxStbCtrlFactArr_Impl*  SfxModule::GetStbCtrlFactories_Impl() const
/*N*/ {
/*N*/   return pImpl->pStbCtrlFac;
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ SfxMenuCtrlFactArr_Impl* SfxModule::GetMenuCtrlFactories_Impl() const
/*N*/ {
/*N*/   return pImpl->pMenuCtrlFac;
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ SfxChildWinFactArr_Impl* SfxModule::GetChildWinFactories_Impl() const
/*N*/ {
/*N*/   return pImpl->pFactArr;
/*N*/ }


/*N*/ ImageList* SfxModule::GetImageList_Impl( BOOL bBig, BOOL bHiContrast )
/*N*/ {
/*N*/     return pImpl->GetImageList( pResMgr, bBig, bHiContrast );
/*N*/ }

/*N*/ SfxTabPage*   SfxModule::CreateTabPage( USHORT nId, Window* pParent, const SfxItemSet& rSet )
/*N*/ {
/*N*/   return NULL;
/*N*/ }

/*N*/ SfxModuleArr_Impl& SfxModule::GetModules_Impl()
/*N*/ {
/*N*/     if( !pModules )
/*N*/         pModules = new SfxModuleArr_Impl;
/*N*/     return *pModules;
/*N*/ };

/*?*/ void SfxModule::Invalidate( USHORT nId )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*?*/ }

}
