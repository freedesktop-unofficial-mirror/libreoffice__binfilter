/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_fmobjfac.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 20:55:55 $
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





#ifndef _FM_FMOBJFAC_HXX
#include "fmobjfac.hxx"
#endif

#ifndef _FM_FMGLOB_HXX
#include "fmglob.hxx"
#endif

#ifndef _FM_FMOBJ_HXX
#include "fmobj.hxx"
#endif

#ifndef _COM_SUN_STAR_SDBC_XROWSETLISTENER_HPP_
#include <com/sun/star/sdbc/XRowSetListener.hpp>
#endif

#ifndef _COM_SUN_STAR_SDB_XSQLQUERYCOMPOSERFACTORY_HPP_
#include <com/sun/star/sdb/XSQLQueryComposerFactory.hpp>
#endif

#ifndef _COM_SUN_STAR_FRAME_XFRAME_HPP_
#include <com/sun/star/frame/XFrame.hpp>
#endif

#ifndef _SVX_FMSHIMP_HXX
#include "fmshimp.hxx"
#endif

#ifndef _FM_FMSHELL_HXX
#include "fmshell.hxx"
#endif

#ifndef _SVX_SVXIDS_HRC
#include "svxids.hrc"
#endif

#ifndef _SVX_TBXFORM_HXX
#include "tbxform.hxx"
#endif


#ifndef _SVX_FMRESIDS_HRC
#include "fmresids.hrc"
#endif



#ifndef _SVX_FMSERVS_HXX
#include "fmservs.hxx"
#endif

#ifndef _SVX_TABWIN_HXX
#include "tabwin.hxx"
#endif

#ifndef _SVX_FMEXPL_HXX
#include "fmexpl.hxx"
#endif

#ifndef _SVX_FILTNAV_HXX
#include "filtnav.hxx"
#endif

#ifndef _SVX_FMPROP_HRC
#include "fmprop.hrc"
#endif
#ifndef SVX_FMPROPBRW_HXX
#include "fmPropBrw.hxx"
#endif
namespace binfilter {

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::binfilter::svxform;//STRIP008 using namespace ::svxform;

/*************************************************************************
|*
|* Ctor
|*
\************************************************************************/
/*N*/ FmFormObjFactory::FmFormObjFactory()
/*N*/ {
/*N*/   SdrObjFactory::InsertMakeObjectHdl(LINK(this, FmFormObjFactory, MakeObject));
/*N*/
/*N*/   //////////////////////////////////////////////////////////////////////
/*N*/   // Konfigurations-::com::sun::star::frame::Controller und NavigationBar registrieren
/*N*/   SvxFmTbxCtlConfig::RegisterControl( SID_FM_CONFIG );
/*N*/   SvxFmTbxCtlAbsRec::RegisterControl( SID_FM_RECORD_ABSOLUTE );
/*N*/   SvxFmTbxCtlRecText::RegisterControl( SID_FM_RECORD_TEXT );
/*N*/   SvxFmTbxCtlRecFromText::RegisterControl( SID_FM_RECORD_FROM_TEXT );
/*N*/   SvxFmTbxCtlRecTotal::RegisterControl( SID_FM_RECORD_TOTAL );
/*N*/   SvxFmTbxPrevRec::RegisterControl( SID_FM_RECORD_PREV );
/*N*/   SvxFmTbxNextRec::RegisterControl( SID_FM_RECORD_NEXT );
/*N*/   ControlConversionMenuController::RegisterControl(SID_FM_CHANGECONTROLTYPE);
/*N*/
/*N*/   // Registrieung von globalen fenstern
/*N*/   FmFieldWinMgr::RegisterChildWindow();
/*N*/   FmPropBrwMgr::RegisterChildWindow();
/*N*/   NavigatorFrameManager::RegisterChildWindow();
/*N*/   FmFilterNavigatorWinMgr::RegisterChildWindow();
/*N*/
/*N*/   //////////////////////////////////////////////////////////////////////
/*N*/   // Interface fuer die Formshell registrieren
/*N*/   FmFormShell::RegisterInterface(0);
/*N*/
/*N*/   ImplSmartRegisterUnoServices();
/*N*/
/*N*/ }


/*************************************************************************
|*
|* Dtor
|*
\************************************************************************/
/*N*/ FmFormObjFactory::~FmFormObjFactory()
/*N*/ {
/*N*/ }


/*************************************************************************
|*
|* ::com::sun::star::form::Form-Objekte erzeugen
|*
\************************************************************************/

/*N*/ IMPL_LINK(FmFormObjFactory, MakeObject, SdrObjFactory*, pObjFactory)
/*N*/ {
/*N*/   if (pObjFactory->nInventor == FmFormInventor)
/*N*/   {
/*N*/       switch (pObjFactory->nIdentifier)
/*N*/       {
/*N*/           case OBJ_FM_CONTROL:    // allgemeines Object
/*N*/           {
/*N*/               pObjFactory->pNewObj = new FmFormObj(pObjFactory->nIdentifier);
/*N*/           }   break;
/*?*/           default:
/*?*/               {DBG_BF_ASSERT(0, "STRIP");}//STRIP001 return 0;
/*?*/       }
/*?*/   }
/*N*/
/*N*/   return 0;
/*N*/ }



}
