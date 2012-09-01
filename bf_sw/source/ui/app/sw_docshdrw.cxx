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


#include <bf_svx/svxids.hrc>

#define ITEMID_COLOR_TABLE      SID_COLOR_TABLE
#define ITEMID_GRADIENT_LIST    SID_GRADIENT_LIST
#define ITEMID_HATCH_LIST       SID_HATCH_LIST
#define ITEMID_BITMAP_LIST      SID_BITMAP_LIST
#define ITEMID_DASH_LIST        SID_DASH_LIST
#define ITEMID_LINEEND_LIST     SID_LINEEND_LIST


#include <bf_offmgr/app.hxx>
#include <bf_svx/drawitem.hxx>
#include <bf_svx/svdmodel.hxx>
#include <bf_svx/svdoutl.hxx>

#include <docsh.hxx>

#include <horiornt.hxx>

#include <doc.hxx>
namespace binfilter {

/*--------------------------------------------------------------------
    Beschreibung: Document laden
 --------------------------------------------------------------------*/


/*N*/ void  SwDocShell::InitDraw()
/*N*/ {
/*N*/   SdrModel *pDrDoc = pDoc->GetDrawModel();
/*N*/   if( pDrDoc )
/*N*/   {
/*N*/       // Listen, bzw. Tables im ItemSet der DocShell anlegen
/*N*/       PutItem( SvxGradientListItem( pDrDoc->GetGradientList() ) );
/*N*/       PutItem( SvxHatchListItem( pDrDoc->GetHatchList() ) );
/*N*/       PutItem( SvxBitmapListItem( pDrDoc->GetBitmapList() ) );
/*N*/       PutItem( SvxDashListItem( pDrDoc->GetDashList() ) );
/*N*/       PutItem( SvxLineEndListItem( pDrDoc->GetLineEndList() ) );
/*N*/
/*N*/       pDrDoc->GetDrawOutliner();
/*N*/   }
/*N*/   else
/*N*/       PutItem( SvxColorTableItem( OFF_APP()->GetStdColorTable() ));
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
