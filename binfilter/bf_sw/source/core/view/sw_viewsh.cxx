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

#define _SVX_PARAITEM_HXX
#define _SVX_TEXTITEM_HXX

#include <bf_sfx2/progress.hxx>
#include <swwait.hxx>

#include <horiornt.hxx>

#include <fesh.hxx>
#include <doc.hxx>
#include <rootfrm.hxx>
#include <pagefrm.hxx>
#include <viewimp.hxx>
#include <frmtool.hxx>
#include <viewopt.hxx>
#include <dview.hxx>
#include <swregion.hxx>
#include <hints.hxx>
#include <txtfrm.hxx>
#include <mdiexp.hxx>
#include <fntcache.hxx>
#include <docsh.hxx>
#include <pagedesc.hxx>
#include <accessibilityoptions.hxx>
#include <statstr.hrc>
#include <shellres.hxx>
namespace binfilter {

ShellResource *ViewShell::pShellRes = 0;
Window *ViewShell::pCareWindow = 0;

bool bInSizeNotify = FALSE;

/*N*/ TYPEINIT0(ViewShell);

/******************************************************************************
|*
|*  ViewShell::InvalidateWindows()
|*
******************************************************************************/

/*N*/ void ViewShell::InvalidateWindows( const SwRect &rRect )
/*N*/ {
/*N*/     ViewShell *pSh = this;
/*N*/     do
/*N*/     {
/*N*/         if ( pSh->GetWin() )
/*N*/         {
/*N*/             if ( pSh->IsPreView() )
/*?*/                 DBG_BF_ASSERT(0, "STRIP");
/*N*/             else if ( pSh->VisArea().IsOver( rRect ) )
/*N*/                 pSh->GetWin()->Invalidate( rRect.SVRect() );
/*N*/         }
/*N*/         pSh = (ViewShell*)pSh->GetNext();
/*N*/
/*N*/     } while ( pSh != this );
/*N*/ }

/******************************************************************************
|*
|*  ViewShell::SetFirstVisPageInvalid()
|*
******************************************************************************/

/*N*/ void ViewShell::SetFirstVisPageInvalid()
/*N*/ {
/*N*/   ViewShell *pSh = this;
/*N*/   do
/*N*/   {   pSh->Imp()->SetFirstVisPageInvalid();
/*N*/       pSh = (ViewShell*)pSh->GetNext();
/*N*/
/*N*/   } while ( pSh != this );
/*N*/ }

/*N*/ OutputDevice& ViewShell::GetRefDev() const
/*N*/ {
/*N*/     OutputDevice* pTmpOut = 0;
/*N*/     if ( GetWin() && IsBrowseMode() &&
/*N*/          ! GetViewOptions()->IsPrtFormat() )
/*N*/         pTmpOut = GetWin();
/*N*/     else if ( 0 != mpTmpRef )
/*N*/         pTmpOut = mpTmpRef;
/*N*/     else
/*N*/         pTmpOut = &GetDoc()->GetRefDev();
/*N*/
/*N*/     return *pTmpOut;
/*N*/ }

/*N*/ void ViewShell::DrawSelChanged(SdrView*)
/*N*/ {
/*N*/ }

/*N*/ BOOL ViewShell::IsBrowseMode() const
/*N*/ {
/*N*/   return GetDoc()->IsBrowseMode();
/*N*/ }

ShellResource* ViewShell::GetShellRes()
{
    if ( !pShellRes )
        pShellRes = new ShellResource();
    return pShellRes;
}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
