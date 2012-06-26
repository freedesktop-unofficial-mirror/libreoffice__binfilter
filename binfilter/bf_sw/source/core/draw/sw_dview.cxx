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

#include "hintids.hxx"




#include <horiornt.hxx>

#include "frmfmt.hxx"
#include "dcontact.hxx"
#include "viewsh.hxx"
#include "viewimp.hxx"
#include "dview.hxx"

#include <fmtanchr.hxx>

// #i7672#

#include <vector>
namespace binfilter {

class SwSdrHdl : public SdrHdl
{
public:
    SwSdrHdl(const Point& rPnt, bool bTopRight ) :
        SdrHdl( rPnt, bTopRight ? HDL_ANCHOR_TR : HDL_ANCHOR ) {}
};



/*************************************************************************
|*
|*  SwDrawView::Ctor
|*
*************************************************************************/



/*N*/ SwDrawView::SwDrawView( SwViewImp &rI, SdrModel *pMd, OutputDevice *pOutDev) :
/*N*/   FmFormView( (FmFormModel*)pMd, pOutDev ),
/*N*/   rImp( rI )
/*N*/ {
/*N*/   SetPageVisible( FALSE );
/*N*/   SetBordVisible( FALSE );
/*N*/   SetGridVisible( FALSE );
/*N*/   SetHlplVisible( FALSE );
/*N*/   SetGlueVisible( FALSE );
/*N*/   SetFrameDragSingles( TRUE );
/*N*/   SetVirtualObjectBundling( TRUE );
/*N*/   SetSwapAsynchron( TRUE );
/*N*/
/*N*/   EnableExtendedKeyInputDispatcher( FALSE );
/*N*/   EnableExtendedMouseEventDispatcher( FALSE );
/*N*/   EnableExtendedCommandEventDispatcher( FALSE );
/*N*/
/*N*/   SetHitTolerancePixel( GetMarkHdlSizePixel()/2 );
/*N*/
/*N*/   SetPrintPreview( rI.GetShell()->IsPreView() );
/*N*/ }

/*************************************************************************
|*
|*  SwDrawView::AddCustomHdl()
|*
|*  Gets called every time the handles need to be build
|*
*************************************************************************/

/*M*/ void SwDrawView::AddCustomHdl()
/*M*/ {
/*M*/   const SdrMarkList &rMrkList = GetMarkList();
/*M*/
/*M*/   if(rMrkList.GetMarkCount() != 1 || !GetUserCall(rMrkList.GetMark( 0 )->GetObj()))
/*M*/       return;
/*M*/
/*?*/   SdrObject *pObj = rMrkList.GetMark(0)->GetObj();
/*?*/   const SwFmtAnchor &rAnchor = ::binfilter::FindFrmFmt(pObj)->GetAnchor();
/*?*/
/*?*/   if(FLY_IN_CNTNT == rAnchor.GetAnchorId())
/*?*/       return;
/*M*/ }


/*************************************************************************
|*
|*  SwDrawView::MarkListHasChanged()
|*
*************************************************************************/

/*N*/ void SwDrawView::MarkListHasChanged()
/*N*/ {
/*N*/   Imp().GetShell()->DrawSelChanged(this);
/*N*/   FmFormView::MarkListHasChanged();
/*N*/ }

// #i7672#
/*N*/ void SwDrawView::ModelHasChanged()
/*N*/ {
    // The ModelHasChanged() call in DrawingLayer also updates
    // a eventually active text edit view (OutlinerView). This also leads
    // to newly setting the background color for that edit view. Thus,
    // this method rescues the current background color if a OutlinerView
    // exists and re-establishes it then. To be more safe, the OutlinerView
    // will be fetched again (maybe textedit has ended).
/*N*/
/*N*/   // call parent
/*N*/   FmFormView::ModelHasChanged();
/*N*/
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
