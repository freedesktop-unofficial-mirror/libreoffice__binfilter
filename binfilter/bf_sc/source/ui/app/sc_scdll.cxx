/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_scdll.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 09:15:11 $
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

#ifdef PCH
#endif

#pragma hdrstop

#include <bf_svx/eeitem.hxx>
#define ITEMID_FIELD EE_FEATURE_FIELD

#include "scitems.hxx"      // fuer tbxctrls etc.
#include "scmod.hxx"
#include "scresid.hxx"
#include "bf_sc.hrc"
#include "cfgids.hxx"

//! die Registrierung wird wegen CLOOKs in ein eigenes File wandern muessen...

// Interface-Registrierung
#include "docsh.hxx"
#include "docpool.hxx"
#include "appoptio.hxx"

#ifndef _SVX_ITEMDATA_HXX
#include <bf_svx/itemdata.hxx>
#endif


#ifndef _SVTOOLS_IMGDEF_HXX
#include <svtools/imgdef.hxx>
#endif

#include <bf_svx/svdfield.hxx>      //  SdrRegisterFieldClasses
#include <rtl/logfile.hxx>

namespace binfilter {

//------------------------------------------------------------------

/*N*/ ScResId::ScResId( USHORT nId ) :
/*N*/   ResId( nId, *SC_MOD()->GetResMgr() )
/*N*/ {
/*N*/ }

//------------------------------------------------------------------

/*N*/ void ScDLL::Init()
/*N*/ {
/*N*/   RTL_LOGFILE_CONTEXT_AUTHOR ( aLog, "sc", "nn93723", "ScDLL::Init" );
/*N*/
/*N*/   // called directly after loading the DLL
/*N*/   // do whatever you want, you may use Sxx-DLL too
/*N*/
/*N*/   ScDocumentPool::InitVersionMaps();  // wird im ScModule ctor gebraucht
/*N*/
/*N*/   // the ScModule must be created
/*N*/   ScModuleDummy **ppShlPtr = (ScModuleDummy**) GetAppData(BF_SHL_CALC);
/*N*/   SvFactory *pFact = (SvFactory*)(*ppShlPtr)->pScDocShellFactory;
/*N*/   delete (*ppShlPtr);
/*N*/   ScModule* pMod = new ScModule((SfxObjectFactory*)pFact);
/*N*/   (*ppShlPtr) = pMod;
/*N*/   (*ppShlPtr)->pScDocShellFactory = pFact;
/*N*/
/*N*/   ScGlobal::Init();       // erst wenn der ResManager initialisiert ist
/*N*/                           //  erst nach ScGlobal::Init duerfen die App-Optionen
/*N*/                           //  initialisiert werden
/*N*/
/*N*/   //  Edit-Engine-Felder, soweit nicht schon in OfficeApplication::Init
/*N*/
/*N*/   SvClassManager& rClassManager = SvxFieldItem::GetClassManager();
/*N*/ //    rClassManager.SV_CLASS_REGISTER( SvxURLField );
/*N*/ //    rClassManager.SV_CLASS_REGISTER( SvxDateField );
/*N*/ //    rClassManager.SV_CLASS_REGISTER( SvxPageField );
/*N*/   rClassManager.SV_CLASS_REGISTER( SvxPagesField );
/*N*/ //    rClassManager.SV_CLASS_REGISTER( SvxTimeField );
/*N*/   rClassManager.SV_CLASS_REGISTER( SvxFileField );
/*N*/ //    rClassManager.SV_CLASS_REGISTER( SvxExtFileField );
/*N*/   rClassManager.SV_CLASS_REGISTER( SvxTableField );
/*N*/
/*N*/   SdrRegisterFieldClasses();      // SvDraw-Felder registrieren
/*N*/
/*N*/   pMod->PutItem( SfxUInt16Item( SID_ATTR_METRIC, pMod->GetAppOptions().GetAppMetric() ) );
/*N*/
/*N*/   //  StarOne Services are now handled in the registry
/*N*/ }

/*N*/ void ScDLL::Exit()
/*N*/ {
/*N*/   // called directly befor unloading the DLL
/*N*/   // do whatever you want, Sxx-DLL is accessible
/*N*/
/*N*/   // the SxxModule must be destroyed
/*N*/   ScModuleDummy **ppShlPtr = (ScModuleDummy**) GetAppData(BF_SHL_CALC);
/*N*/   delete (*ppShlPtr);
/*N*/   (*ppShlPtr) = NULL;
/*N*/
/*N*/   //  auf keinen Fall ein neues ScModuleDummy anlegen, weil dessen vtable sonst
/*N*/   //  in der DLL waere und das Loeschen im LibExit schiefgehen wuerde
/*N*/
/*N*/   //  ScGlobal::Clear ist schon im Module-dtor
/*N*/ }

//------------------------------------------------------------------
//  Statusbar
//------------------------------------------------------------------

#define TEXT_WIDTH(s)   rStatusBar.GetTextWidth((s))


#undef TEXT_WIDTH


}
