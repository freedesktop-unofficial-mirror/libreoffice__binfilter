/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_dialdll.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 06:50:34 $
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

// include ---------------------------------------------------------------

#include <svtools/solar.hrc>
// auto strip #include <tools/stream.hxx>
#include "dialdll.hxx"
#include "dialmgr.hxx"
#define ITEMID_BRUSH 1
#include "brshitem.hxx"
// auto strip #include "chardlg.hxx"

// auto strip #ifndef _SHL_HXX //autogen
// auto strip #include <tools/shl.hxx>
// auto strip #endif

#ifndef _SV_SVAPP_HXX //autogen
#include <vcl/svapp.hxx>
#endif

// auto strip #ifndef _TOOLS_DEBUG_HXX //autogen
// auto strip #include <tools/debug.hxx>
// auto strip #endif

// auto strip #ifndef _TOOLS_RESMGR_HXX //autogen
// auto strip #include <tools/resmgr.hxx>
// auto strip #endif

#ifndef _FILTER_HXX //autogen
#include <svtools/filter.hxx>
#endif

#ifndef _WALLITEM_HXX
#include <svtools/wallitem.hxx>
#endif
namespace binfilter {

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
/*N*/     pResMgr = ResMgr::CreateResMgr( aName.GetBuffer(), Application::GetSettings().GetUILocale() );
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


}
