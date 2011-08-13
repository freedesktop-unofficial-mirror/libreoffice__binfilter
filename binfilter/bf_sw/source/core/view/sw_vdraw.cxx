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

#include <bf_svx/svdpage.hxx>

#include <bf_svx/svdpagv.hxx>

#include <fmtanchr.hxx>
#include <frmfmt.hxx>

/// OD 29.08.2002 #102450#
/// include <bf_svx/svdoutl.hxx>

#ifdef DBG_UTIL
#endif

#include <horiornt.hxx>

#include "fesh.hxx"
#include "doc.hxx"
#include "viewimp.hxx"
#include "dcontact.hxx"
#include "dview.hxx"
#include "flyfrm.hxx"
namespace binfilter {

/*************************************************************************
|*
|*  SwViewImp::StartAction(), EndAction()
|*
|*************************************************************************/


/*N*/ void SwViewImp::StartAction()
/*N*/ {
/*N*/   if ( HasDrawView() )
/*N*/   {
/*N*/       SET_CURR_SHELL( GetShell() );
/*N*/       if ( pSh->ISA(SwFEShell) )
/*N*/           ((SwFEShell*)pSh)->HideChainMarker();   //Kann sich geaendert haben
/*N*/       bResetXorVisibility = GetDrawView()->IsShownXorVisible( GetShell()->GetOut());
/*N*/       GetDrawView()->HideShownXor( GetShell()->GetOut() );
/*N*/   }
/*N*/ }



/*N*/ void SwViewImp::EndAction()
/*N*/ {
/*N*/   if ( HasDrawView() )
/*N*/   {
/*N*/       SET_CURR_SHELL( GetShell() );
/*N*/       if ( bResetXorVisibility )
/*?*/           GetDrawView()->ShowShownXor( GetShell()->GetOut() );
/*N*/       if ( pSh->ISA(SwFEShell) )
/*N*/           ((SwFEShell*)pSh)->SetChainMarker();    //Kann sich geaendert haben
/*N*/   }
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
