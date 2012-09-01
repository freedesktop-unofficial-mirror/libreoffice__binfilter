/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <vcl/window.hxx>
#include <vcl/graph.hxx>
#include <bf_offmgr/app.hxx>

#include <comphelper/processfactory.hxx>
#include <bf_svx/unolingu.hxx>

#include <pagefrm.hxx>
#include <frmtool.hxx>
#include <ndtxt.hxx>
#include <viscrs.hxx>
#include <fntcache.hxx>
#include <swfntcch.hxx>
#include <hffrm.hxx>
#include <colfrm.hxx>
#include <bodyfrm.hxx>
#include <tabfrm.hxx>
#include <txtfrm.hxx>
#include <swtblfmt.hxx>
#include <rowfrm.hxx>
#include <cellfrm.hxx>
#include <sectfrm.hxx>
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::linguistic2;
using namespace ::comphelper;

#ifndef PROFILE
// Code zum Initialisieren von Statics im eigenen Code-Segment
#ifdef _MSC_VER
#pragma code_seg( "SWSTATICS" )
#endif
#endif

String aEmptyStr;               // Konstante Strings
String aDotStr('.');            // Konstante Strings

IMPL_FIXEDMEMPOOL_NEWDEL( SwAttrSet )
IMPL_FIXEDMEMPOOL_NEWDEL( SwStartNode )
IMPL_FIXEDMEMPOOL_NEWDEL( SwEndNode )
IMPL_FIXEDMEMPOOL_NEWDEL( SwTableBox )
IMPL_FIXEDMEMPOOL_NEWDEL( SwPaM )
IMPL_FIXEDMEMPOOL_NEWDEL( SwCursor )
IMPL_FIXEDMEMPOOL_NEWDEL( SwShellCrsr )
IMPL_FIXEDMEMPOOL_NEWDEL( SwTxtNode )
IMPL_FIXEDMEMPOOL_NEWDEL( SwpHints )
IMPL_FIXEDMEMPOOL_NEWDEL( SwFntObj )
IMPL_FIXEDMEMPOOL_NEWDEL( SwFontObj )
IMPL_FIXEDMEMPOOL_NEWDEL( SwFrmFmt )
IMPL_FIXEDMEMPOOL_NEWDEL( SwFlyFrmFmt )
IMPL_FIXEDMEMPOOL_NEWDEL( SwDrawFrmFmt )
IMPL_FIXEDMEMPOOL_NEWDEL( SwBorderAttrs )
IMPL_FIXEDMEMPOOL_NEWDEL( SwCellFrm )
IMPL_FIXEDMEMPOOL_NEWDEL( SwRowFrm )
IMPL_FIXEDMEMPOOL_NEWDEL( SwColumnFrm )
IMPL_FIXEDMEMPOOL_NEWDEL( SwSectionFrm )
IMPL_FIXEDMEMPOOL_NEWDEL( SwTabFrm )
IMPL_FIXEDMEMPOOL_NEWDEL( SwPageFrm )
IMPL_FIXEDMEMPOOL_NEWDEL( SwBodyFrm )
IMPL_FIXEDMEMPOOL_NEWDEL( SwHeaderFrm )
IMPL_FIXEDMEMPOOL_NEWDEL( SwFooterFrm )
IMPL_FIXEDMEMPOOL_NEWDEL( SwTxtFrm )
IMPL_FIXEDMEMPOOL_NEWDEL( SwTableFmt )
IMPL_FIXEDMEMPOOL_NEWDEL( SwTableLineFmt )
IMPL_FIXEDMEMPOOL_NEWDEL( SwTableBoxFmt )
IMPL_FIXEDMEMPOOL_NEWDEL( _SwCursor_SavePos )


#ifndef PROFILE
#ifdef _MSC_VER
#pragma code_seg()
#endif
#endif

/*N*/ Size GetGraphicSizeTwip( const Graphic& rGraphic, OutputDevice* pOutDev )
/*N*/ {
/*N*/   const MapMode aMapTwip( MAP_TWIP );
/*N*/   Size aSize( rGraphic.GetPrefSize() );
/*N*/   if( MAP_PIXEL == rGraphic.GetPrefMapMode().GetMapUnit() )
/*N*/   {
/*N*/       if( !pOutDev )
/*N*/           pOutDev = Application::GetDefaultDevice();
/*N*/       aSize = pOutDev->PixelToLogic( aSize, aMapTwip );
/*N*/   }
/*N*/   else
/*N*/       aSize = OutputDevice::LogicToLogic( aSize,
/*N*/                                       rGraphic.GetPrefMapMode(), aMapTwip );
/*N*/   return aSize;
/*N*/ }


/*N*/ Reference< XHyphenator >  GetHyphenator()
/*N*/ {
/*N*/   return LinguMgr::GetHyphenator();
/*N*/ }


/*N*/ Reference< XDictionaryList >  GetDictionaryList()
/*N*/ {
/*N*/   return LinguMgr::GetDictionaryList();
/*N*/ }




}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
