/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sd_sddll.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 23:41:51 $
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

// auto strip #ifndef _EEITEM_HXX //autogen
// auto strip #include <bf_svx/eeitem.hxx>
// auto strip #endif

// auto strip #include <bf_svx/editeng.hxx>
#ifndef _SVDOBJ_HXX //autogen
#include <bf_svx/svdobj.hxx>
#endif
// auto strip #ifndef _SFXAPP_HXX //autogen
// auto strip #include <bf_sfx2/app.hxx>
// auto strip #endif
#ifndef INCLUDED_SVTOOLS_MODULEOPTIONS_HXX
#include <svtools/moduleoptions.hxx>
#endif

#pragma hdrstop

// auto strip #include "sddll.hxx"
// auto strip #include "docshell.hxx"
#include "grdocsh.hxx"
#include "sdresid.hxx"
#include "sdobjfac.hxx"
#include "cfgids.hxx"

#ifndef _SVX_ACCESSIBILITY_CHILDREN_MANAGER_HXX
#include <bf_svx/ChildrenManager.hxx>
#endif

// auto strip #include "SdShapeTypes.hxx"
// auto strip #include <bf_svx/SvxShapeTypes.hxx>
namespace binfilter {

/*************************************************************************
|*
|* Init
|*
\************************************************************************/

/*N*/ void SdDLL::Init()
/*N*/ {
/*N*/   // called directly after loading the DLL
/*N*/   // do whatever you want, you may use Sd-DLL too
/*N*/
/*N*/   // the SdModule must be created
/*N*/   SdModuleDummy** ppShlPtr = (SdModuleDummy**) GetAppData(BF_SHL_DRAW);
/*N*/   SvFactory* pDrawFact    = (SvFactory*)(*ppShlPtr)->pSdDrawDocShellFactory;
/*N*/   SvFactory* pGraphicFact = (SvFactory*)(*ppShlPtr)->pSdGraphicDocShellFactory;
/*N*/   delete (*ppShlPtr);
/*N*/   (*ppShlPtr) = new SdModule(pDrawFact, pGraphicFact);
/*N*/   (*ppShlPtr)->pSdDrawDocShellFactory    = pDrawFact;
/*N*/   (*ppShlPtr)->pSdGraphicDocShellFactory = pGraphicFact;
/*N*/
/*N*/   if (SvtModuleOptions().IsImpress())
/*N*/   {
/*N*/       SdDrawDocShell::Factory().RegisterMenuBar( SdResId( RID_DRAW_DEFAULTMENU ) );
/*N*/       SdDrawDocShell::Factory().RegisterPluginMenuBar( SdResId( RID_DRAW_PORTALMENU ) );
/*N*/       SdDrawDocShell::Factory().RegisterAccel( SdResId( RID_DRAW_DEFAULTACCEL ) );
/*N*/
/*N*/         // Register the Impress shape types in order to make the shapes
/*N*/         // accessible.
//STRIP001 /*?*/         accessibility::RegisterImpressShapeTypes ();
/*N*/   }

/*N*/   if (SvtModuleOptions().IsDraw())
/*N*/   {
/*N*/       SdGraphicDocShell::Factory().RegisterMenuBar( SdResId( RID_GRAPHIC_DEFAULTMENU ) );
/*N*/       SdGraphicDocShell::Factory().RegisterPluginMenuBar( SdResId( RID_GRAPHIC_PORTALMENU ) );
/*N*/       SdGraphicDocShell::Factory().RegisterAccel( SdResId( RID_GRAPHIC_DEFAULTACCEL ) );
/*N*/   }
/*N*/
/*N*/   // register your view-factories here
/*N*/   RegisterFactorys();
/*N*/
/*N*/   // register your shell-interfaces here
/*N*/   RegisterInterfaces();
/*N*/
/*N*/   // register your controllers here
/*N*/   RegisterControllers();
/*N*/
/*N*/   // Objekt-Factory eintragen
/*N*/   SdrObjFactory::InsertMakeUserDataHdl(LINK(&aSdObjectFactory, SdObjectFactory, MakeUserData));
/*N*/ }



/*************************************************************************
|*
|* Exit
|*
\************************************************************************/

/*N*/ void SdDLL::Exit()
/*N*/ {
/*N*/   // called directly befor unloading the DLL
/*N*/   // do whatever you want, Sd-DLL is accessible
/*N*/
/*N*/   // Objekt-Factory austragen
/*N*/   SdrObjFactory::RemoveMakeUserDataHdl(LINK(&aSdObjectFactory, SdObjectFactory, MakeUserData));
/*N*/
/*N*/   // the SdModule must be destroyed
/*N*/   SdModuleDummy** ppShlPtr = (SdModuleDummy**) GetAppData(BF_SHL_DRAW);
/*N*/   delete (*ppShlPtr);
/*N*/   (*ppShlPtr) = NULL;
/*N*/ }





}
