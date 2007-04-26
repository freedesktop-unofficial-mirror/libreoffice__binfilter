/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sch_schmod.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: rt $ $Date: 2007-04-26 07:11:21 $
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

#define ITEMID_SEARCH           SID_SEARCH_ITEM

#pragma hdrstop


#include <bf_svx/svxids.hrc>


#ifndef _SFXOBJFACE_HXX //autogen
#include <bf_sfx2/objface.hxx>
#endif

#ifndef _SFXDISPATCH_HXX //autogen
#include <bf_sfx2/dispatch.hxx>
#endif
#ifndef _SV_STATUS_HXX //autogen
#include <vcl/status.hxx>
#endif
#ifndef _SVDOBJ_HXX //autogen
#include <bf_svx/svdobj.hxx>
#endif

#define _SCH_DLL                 // fuer SD_MOD()
#include "schmod.hxx"
#include "schresid.hxx"

#include "app.hrc"
#include "glob.hrc"
#include "strings.hrc"
#include "res_bmp.hrc"

//STRIP008 /*N*/ TYPEINIT1( SchModuleDummy, SfxModule );
//STRIP008 /*N*/ TYPEINIT1( SchModule, SchModuleDummy );


#define SchModule
//STRIP008 #include "schslots.hxx"

#ifndef _SVX_MODCTRL_HXX //autogen
#include <bf_svx/modctrl.hxx>
#endif
namespace binfilter {
#include "schslots.hxx"
/*N*/ TYPEINIT1( SchModuleDummy, SfxModule );
/*N*/ TYPEINIT1( SchModule, SchModuleDummy );

/*N*/ SFX_IMPL_INTERFACE( SchModule, SfxModule, SchResId( STR_APPLICATIONOBJECTBAR ) )
/*N*/ // from macro: void SchModule::InitInterface_Impl()
/*N*/ {
/*N*/   SFX_STATUSBAR_REGISTRATION( SchResId( RID_STATUSBAR ) );
/*N*/ }

/*************************************************************************
|*
|* Ctor
|*
\************************************************************************/

/*N*/ SchModule::SchModule(SvFactory* pObjFact) :
/*N*/   SchModuleDummy(SFX_APP()->CreateResManager("bf_sch"), FALSE, pObjFact), //STRIP005
/*N*/   pXOutDevPool( NULL ),
/*N*/   pDragData( NULL ),
/*N*/   pClipboardData( NULL ),
/*N*/   mpTransferDragDrop( NULL ),
/*N*/   mpTransferClipboard( NULL ),
/*N*/   mpTransferSelectionClipbd( NULL ),
/*N*/   pChartOptions( NULL )
/*N*/ {
/*N*/   pSchObjFactory = new SchObjFactory();
/*N*/
/*N*/   if (!pSchObjFactory->GetInserted())
/*N*/   {
/*N*/       SdrObjFactory::InsertMakeObjectHdl(LINK(pSchObjFactory, SchObjFactory, MakeObject));
/*N*/       SdrObjFactory::InsertMakeUserDataHdl(LINK(pSchObjFactory, SchObjFactory, MakeUserData));
/*N*/
/*N*/       pSchObjFactory->SetInserted(TRUE);
/*N*/   }
/*N*/
/*N*/   // #62493# this factory exists already
/*N*/   //pE3dFactory = new E3dObjFactory();
/*N*/   //SdrObjFactory::InsertMakeObjectHdl(LINK(pE3dFactory, E3dObjFactory, MakeObject));
/*N*/
/*N*/   SetName( String( RTL_CONSTASCII_USTRINGPARAM( "StarChart" )) );
/*N*/
/*N*/   // establish listener, so that the module is informed
/*N*/   // right before the application is going to be shut down
/*N*/   StartListening( *SFX_APP() );
/*N*/ }

/*************************************************************************
|*
|* Dtor
|*
\************************************************************************/

/*N*/ SchModule::~SchModule()
/*N*/ {
/*N*/   if (pSchObjFactory)
/*N*/   {
/*N*/       if (pSchObjFactory->GetInserted())
/*N*/       {
/*N*/           SdrObjFactory::RemoveMakeObjectHdl(LINK(pSchObjFactory, SchObjFactory, MakeObject));
/*N*/           SdrObjFactory::RemoveMakeUserDataHdl(LINK(pSchObjFactory, SchObjFactory, MakeUserData));
/*N*/       }
/*N*/
/*N*/       delete pSchObjFactory;
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* SfxRequests bearbeiten
|*
\************************************************************************/

void SchModule::Execute(SfxRequest& rReq)
{
    DBG_BF_ASSERT(0, "STRIP");//STRIP001    switch (rReq.GetSlot())
}

/*************************************************************************
|*
|*
|*
\************************************************************************/

/*?*/ void SchModule::GetState(SfxItemSet& rItemSet)
/*?*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001   rItemSet.DisableItem(SID_CONFIGEVENT);
/*?*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/


/*************************************************************************
|*
|* Statusbar erzeugen; virtuell, wird vom SFX gerufen
|*
\************************************************************************/

/*N*/ void SchModule::FillStatusBar(StatusBar &rBar)
/*N*/ {
/*N*/   String aDummy;
/*N*/   aDummy.Fill( 20, (sal_Unicode)('x') );
/*N*/   long nWidth = rBar.GetTextWidth( aDummy );
/*N*/
/*N*/   rBar.InsertItem(SID_CONTEXT, nWidth, SIB_IN | SIB_AUTOSIZE | SIB_LEFT);
/*N*/   rBar.InsertItem(SID_CONTEXT_TYPE, nWidth, SIB_IN | SIB_AUTOSIZE | SIB_LEFT);
/*N*/   rBar.InsertItem(SID_DOC_MODIFIED, SvxModifyControl::GetDefItemWidth(rBar));
/*N*/   rBar.SetHelpId( SID_DOC_MODIFIED, SID_DOC_MODIFIED );
/*N*/
/*N*/   aDummy.Fill( 30, (sal_Unicode)('x') );
/*N*/   nWidth = rBar.GetTextWidth( aDummy );
/*N*/
/*N*/   rBar.InsertItem(SID_ATTR_SIZE, nWidth, SIB_IN | SIB_USERDRAW);
/*N*/ }

/*************************************************************************
|*
|* Lade Module von aussen
|*
\************************************************************************/

/*?*/ SfxModule *SchModuleDummy::Load()
/*?*/ {
/*?*/   return NULL;
/*?*/ }

/*************************************************************************
|*
|* Lade Module von aussen
|*
\************************************************************************/


/*************************************************************************
|*
|* Loesche Module
|*
\************************************************************************/


/*N*/ SchOptions* SchModule::GetSchOptions()
/*N*/ {
/*N*/   if( ! pChartOptions )
/*N*/       pChartOptions = new SchOptions();
/*N*/
/*N*/   return pChartOptions;
/*N*/ }

/*************************************************************************
|*
|* get notifications
|*
\************************************************************************/

/*N*/ void SchModule::Notify( SfxBroadcaster& rBC, const SfxHint& rHint )
/*N*/ {
/*N*/   if( rHint.ISA( SfxSimpleHint ) &&
/*N*/       ( (SfxSimpleHint&) rHint ).GetId() == SFX_HINT_DEINITIALIZING )
/*N*/   {
/*N*/       delete pChartOptions, pChartOptions = NULL;
/*N*/   }
/*N*/ }
}
