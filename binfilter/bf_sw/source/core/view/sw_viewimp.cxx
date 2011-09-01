/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "scrrect.hxx"

#include <horiornt.hxx>

#include "doc.hxx"
#include "crsrsh.hxx"
#include "rootfrm.hxx"
#include "pagefrm.hxx"
#include "viewimp.hxx"
#include "viewopt.hxx"
#include "layact.hxx"
#include "swregion.hxx"
#include "dview.hxx"
#include <bf_svx/svdpage.hxx>
#ifdef ACCESSIBLE_LAYOUT
#endif

namespace binfilter {

/*N*/ SwViewImp::~SwViewImp() { }

/*N*/ BOOL SwViewImp::AddPaintRect( const SwRect &rRect )
/*N*/ {
/*N*/   if ( rRect.IsOver( pSh->VisArea() ) )
/*N*/   {
/*?*/       if ( !pRegion )
/*?*/           pRegion = new SwRegionRects( pSh->VisArea() );
/*?*/       (*pRegion) -= rRect;
/*?*/       return TRUE;
/*N*/   }
/*N*/   return FALSE;
/*N*/ }


/******************************************************************************
|*
|*  ViewImp::CheckWaitCrsr()
|*
******************************************************************************/

/*N*/ void SwViewImp::CheckWaitCrsr()
/*N*/ {
/*N*/   if ( pLayAct )
/*N*/       pLayAct->CheckWaitCrsr();
/*N*/ }

/******************************************************************************
|*
|*  ViewImp::IsCalcLayoutProgress()
|*
******************************************************************************/

/*N*/ BOOL SwViewImp::IsCalcLayoutProgress() const
/*N*/ {
/*N*/   if ( pLayAct )
/*N*/       return pLayAct->IsCalcLayout();
/*N*/   return FALSE;
/*N*/ }

/******************************************************************************
|*
|*  ViewImp::IsUpdateExpFlds()
|*
******************************************************************************/

/*N*/ BOOL SwViewImp::IsUpdateExpFlds()
/*N*/ {
/*N*/   if ( pLayAct && pLayAct->IsCalcLayout() )
/*N*/   {
/*?*/       pLayAct->SetUpdateExpFlds();
/*?*/       return TRUE;
/*N*/   }
/*N*/   return FALSE;
/*N*/ }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
