/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: starmath_smdll.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 19:57:27 $
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

#ifndef _SVX_SVXIDS_HRC //autogen
#include <bf_svx/svxids.hrc>
#endif
#ifndef _SVX_MODCTRL_HXX //autogen
#include <bf_svx/modctrl.hxx>
#endif
#ifndef _SVX_ZOOMCTRL_HXX //autogen
#include <bf_svx/zoomctrl.hxx>
#endif
#ifndef _SVX_LBOXCTRL_HXX_
#include <bf_svx/lboxctrl.hxx>
#endif

#ifndef DOCUMENT_HXX
#include <document.hxx>
#endif
#ifndef VIEW_HXX
#include <view.hxx>
#endif

#ifndef _STARMATH_HRC
#include <starmath.hrc>
#endif
namespace binfilter {

BOOL SmDLL::bInitialized = FALSE;

/*************************************************************************
|*
|* Initialisierung
|*
\************************************************************************/
/*N*/ void SmDLL::Init()
/*N*/ {
/*N*/     if ( bInitialized )
/*N*/         return;
/*N*/
/*N*/     bInitialized = TRUE;
/*N*/
/*N*/   // called directly after loading the DLL
/*N*/   // do whatever you want, you may use Sd-DLL too
/*N*/
/*N*/   // the SdModule must be created
/*N*/ #if 0
/*N*/   SmDocShell::RegisterFactory(SDT_SMA_DOCFACTPRIO);
/*N*/ #endif
/*N*/
/*N*/   SmModuleDummy** ppShlPtr = (SmModuleDummy**) GetAppData(BF_SHL_SM);
/*N*/
/*N*/ #if 1
/*N*/     SvFactory* pFact = PTR_CAST(SvFactory,(*ppShlPtr)->pSmDocShellFactory);
/*N*/     delete (*ppShlPtr);
/*N*/     (*ppShlPtr) = new SmModule(pFact);
/*N*/     (*ppShlPtr)->pSmDocShellFactory = pFact;
/*N*/ #else
/*N*/     (*ppShlPtr) = new SmModule( &SmDocShell::Factory() );
/*N*/ #endif
/*N*/
/*N*/   String aResDll(C2S("sm"));
/*N*/   aResDll += String::CreateFromInt32( SOLARUPD );
/*N*/
/*N*/   SfxModule *p = SM_MOD1();
/*N*/   SmModule *pp = (SmModule *) p;
/*N*/
/*N*/   SmModule::RegisterInterface(pp);
/*N*/
/*N*/   SmDocShell::RegisterInterface(pp);
/*N*/
/*N*/   SmViewShell::RegisterFactory(1);
/*N*/   SmViewShell::RegisterInterface(pp);
/*N*/
/*N*/   SvxZoomStatusBarControl::RegisterControl( SID_ATTR_ZOOM, pp );
/*N*/   SvxModifyControl::RegisterControl( SID_TEXTSTATUS, pp );
/*N*/   SvxUndoRedoControl::RegisterControl( SID_UNDO, pp );
/*N*/   SvxUndoRedoControl::RegisterControl( SID_REDO, pp );
/*N*/
/*N*/ }

/*************************************************************************
|*
|* Deinitialisierung
|*
\************************************************************************/
/*N*/ void SmDLL::Exit()
/*N*/ {
/*N*/   // the SdModule must be destroyed
/*N*/   SmModuleDummy** ppShlPtr = (SmModuleDummy**) GetAppData(BF_SHL_SM);
/*N*/   delete (*ppShlPtr);
/*N*/   (*ppShlPtr) = NULL;
/*N*/
/*N*/   *GetAppData(BF_SHL_SM) = 0;
/*N*/ }


}
