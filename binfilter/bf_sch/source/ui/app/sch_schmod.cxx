/*************************************************************************
 *
 *  $RCSfile: sch_schmod.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:17:46 $
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

#define ITEMID_SEARCH           SID_SEARCH_ITEM

#pragma hdrstop

#ifndef _FACTORY_HXX //autogen
#include <so3/factory.hxx>
#endif

#include <bf_svx/svxids.hrc>

#include "schdll0.hxx"

#ifndef _SFXOBJFACE_HXX //autogen
#include <bf_sfx2/objface.hxx>
#endif

#ifndef _SFXMSG_HXX //autogen
#include <bf_sfx2/msg.hxx>
#endif
#ifndef _SFXSTRITEM_HXX //autogen
#include <svtools/stritem.hxx>
#endif
#ifndef _SFXAPP_HXX //autogen
#include <bf_sfx2/app.hxx>
#endif
#ifndef _SFXDISPATCH_HXX //autogen
#include <bf_sfx2/dispatch.hxx>
#endif
#ifndef _SFXVIEWFRM_HXX
#include <bf_sfx2/viewfrm.hxx>
#endif
#ifndef _SV_STATUS_HXX //autogen
#include <vcl/status.hxx>
#endif
#ifndef _SVDOBJ_HXX //autogen
#include <bf_svx/svdobj.hxx>
#endif
#ifndef _OBJFAC3D_HXX //autogen
#include <bf_svx/objfac3d.hxx>
#endif
#ifndef _SFXREQUEST_HXX //autogen
#include <bf_sfx2/request.hxx>
#endif
#ifndef _SFXITEMSET_HXX //autogen
#include <svtools/itemset.hxx>
#endif
#ifndef _XPOOL_HXX //autogen
#include <bf_svx/xpool.hxx>
#endif

#define _SCH_DLL                 // fuer SD_MOD()
#include "schmod.hxx"
#include "schdll.hxx"
#include "schresid.hxx"
#include "objfac.hxx"

#include "app.hrc"
#include "glob.hrc"
#include "strings.hrc"
#include "res_bmp.hrc"
#include "cfgids.hxx"

/*N*/ TYPEINIT1( SchModuleDummy, SfxModule );
/*N*/ TYPEINIT1( SchModule, SchModuleDummy );


#define SchModule
#include "schslots.hxx"

#ifndef _SVX_MODCTRL_HXX //autogen
#include <bf_svx/modctrl.hxx>
#endif

/*N*/ SFX_IMPL_INTERFACE( SchModule, SfxModule, SchResId( STR_APPLICATIONOBJECTBAR ) )
/*N*/ // from macro: void SchModule::InitInterface_Impl()
/*N*/ {
/*N*/   SFX_STATUSBAR_REGISTRATION( RID_STATUSBAR );
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
    DBG_ASSERT(0, "STRIP");//STRIP001   switch (rReq.GetSlot())
//STRIP001  {
//STRIP001      case SID_START_APP:
//STRIP001          if( GetFrame())
//STRIP001              GetFrame()->GetDispatcher()->Execute( SID_NEWDOCDIRECT,
//STRIP001                                                    SFX_CALLMODE_SYNCHRON );
//STRIP001          break;
//STRIP001
//STRIP001 // deprecated, but might be reactivated for portal version
//STRIP001 //
//STRIP001 //       case SID_OPTIONS:
//STRIP001 //           ExecuteOptionsDlg(rReq);
//STRIP001 //           break;
//STRIP001  }
}

/*************************************************************************
|*
|*
|*
\************************************************************************/

/*?*/ void SchModule::GetState(SfxItemSet& rItemSet)
/*?*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001  rItemSet.DisableItem(SID_CONFIGEVENT);
/*?*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/

//STRIP001 XOutdevItemPool* SchModule::GetXOutDevPool()
//STRIP001 {
//STRIP001  if (!pXOutDevPool) pXOutDevPool = new XOutdevItemPool;
//STRIP001
//STRIP001  return pXOutDevPool;
//STRIP001 }

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

//STRIP001 SfxModule *SchModule::Load()
//STRIP001 {
//STRIP001  return this;
//STRIP001 }

/*************************************************************************
|*
|* Loesche Module
|*
\************************************************************************/

//STRIP001 void SchModule::Free()
//STRIP001 {
//STRIP001 //    FreeLibSch ();
//STRIP001 }

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
