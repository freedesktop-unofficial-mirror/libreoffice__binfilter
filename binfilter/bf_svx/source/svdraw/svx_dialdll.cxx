/*************************************************************************
 *
 *  $RCSfile: svx_dialdll.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:17 $
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

// include ---------------------------------------------------------------

#include <svtools/solar.hrc>
#include <tools/stream.hxx>
#include "dialdll.hxx"
#include "dialmgr.hxx"
#define ITEMID_BRUSH 1
#include "brshitem.hxx"
#include "chardlg.hxx"

#ifndef _SHL_HXX //autogen
#include <tools/shl.hxx>
#endif

#ifndef _SV_SVAPP_HXX //autogen
#include <vcl/svapp.hxx>
#endif

#ifndef _TOOLS_DEBUG_HXX //autogen
#include <tools/debug.hxx>
#endif

#ifndef _TOOLS_RESMGR_HXX //autogen
#include <tools/resmgr.hxx>
#endif

#ifndef _FILTER_HXX //autogen
#include <svtools/filter.hxx>
#endif

#ifndef _WALLITEM_HXX
#include <svtools/wallitem.hxx>
#endif

// struct DialogsResMgr --------------------------------------------------
/*N*/ DialogsResMgr::DialogsResMgr()
/*N*/ : pResMgr(0),
/*N*/   pGrapicFilter(0)
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   ByteString aName( "bf_svx" );       //STRIP005
/*N*/ #else
/*N*/   ByteString aName( "bf_svl" );       //STRIP005
/*N*/ #endif
/*N*/   INT32 nSolarUpd(SOLARUPD);
/*N*/   aName += ByteString::CreateFromInt32( nSolarUpd );
/*N*/     pResMgr = ResMgr::CreateResMgr( aName.GetBuffer(), Application::GetSettings().GetUILanguage() );
/*N*/ }

// -----------------------------------------------------------------------
/*N*/ DialogsResMgr::~DialogsResMgr()
/*N*/ {
/*N*/   delete pGrapicFilter;
/*N*/   delete pResMgr;
/*N*/ }

// class SvxDialogDll ----------------------------------------------------
/*N*/ SvxDialogDll::SvxDialogDll()
/*N*/ {
/*N*/   DBG_ASSERT( !(*GetAppData(BF_SHL_SVX)), "Ctor, but pointer not null" );
/*N*/
/*N*/   (*(DialogsResMgr**)GetAppData(BF_SHL_SVX)) = new DialogsResMgr;
/*N*/   SvxBrushItem::InitSfxLink();  //  OV,30.06.1998
/*N*/ }

// -----------------------------------------------------------------------
/*N*/ SvxDialogDll::~SvxDialogDll()
/*N*/ {
/*N*/   DBG_ASSERT( (*GetAppData(BF_SHL_SVX)), "Dtor, pointer == null" );
/*N*/
/*N*/   delete (*(DialogsResMgr**)GetAppData(BF_SHL_SVX));
/*N*/   (*(DialogsResMgr**)GetAppData(BF_SHL_SVX)) = 0;
/*N*/   delete SfxBrushItemLink::Get();
/*N*/   (*(SfxBrushItemLink**)GetAppData(SHL_BRUSHITEM)) = 0;
/*N*/ }

// -----------------------------------------------------------------------
//STRIP001 void SvxDialogDll::ResetResMgr()
//STRIP001 {
//STRIP001  DialogsResMgr* pResMgr = (*(DialogsResMgr**)GetAppData(BF_SHL_SVX));
//STRIP001  DBG_ASSERT( pResMgr, "SvxDialogDll::ResetResMgr - no ResMgr" );
//STRIP001  if ( pResMgr )
//STRIP001  {
//STRIP001      delete pResMgr;
//STRIP001      (*(DialogsResMgr**)GetAppData(BF_SHL_SVX)) = new DialogsResMgr;
//STRIP001  }
//STRIP001 }


