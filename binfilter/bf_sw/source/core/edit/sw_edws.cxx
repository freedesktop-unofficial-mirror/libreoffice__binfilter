/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_edws.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:11:24 $
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


#ifdef _MSC_VER
#pragma hdrstop
#endif


#ifndef _WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _EDITSH_HXX
#include <editsh.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
namespace binfilter {

/********************************************************
 * Ctor/Dtor
 ********************************************************/

// ctor/dtor


/*N*/ SwEditShell::SwEditShell( SwDoc& rDoc, Window *pWin, SwRootFrm *pRootFrm,
/*N*/                           const SwViewOption *pOpt )
/*N*/   : SwCrsrShell( rDoc, pWin, pRootFrm, pOpt)
/*N*/ {
/*N*/   GetDoc()->DoUndo();
/*N*/ }


/*N*/ SwEditShell::~SwEditShell() // USED
/*N*/ {
/*N*/ }

/******************************************************************************
 *                 void SwEditShell::StartAllAction()
 ******************************************************************************/


/*N*/ void SwEditShell::StartAllAction()
/*N*/ {
/*N*/   ViewShell *pSh = this;
/*N*/   do {
/*N*/       if( pSh->IsA( TYPE( SwEditShell ) ) )
/*N*/           ((SwEditShell*)pSh)->StartAction();
/*N*/       else
/*?*/           pSh->StartAction();
/*N*/       pSh = (ViewShell *)pSh->GetNext();
/*N*/   } while(pSh != this);
/*N*/ }
/******************************************************************************
 *                  void SwEditShell::EndAllAction()
 ******************************************************************************/


/*N*/ void SwEditShell::EndAllAction()
/*N*/ {
/*N*/   ViewShell *pSh = this;
/*N*/   do {
/*N*/       if( pSh->IsA( TYPE( SwEditShell ) ) )
/*N*/           ((SwEditShell*)pSh)->EndAction();
/*N*/       else
/*?*/           pSh->EndAction();
/*N*/       pSh = (ViewShell *)pSh->GetNext();
/*N*/   } while(pSh != this);
/*N*/ }

/******************************************************************************
 *                  void SwEditShell::CalcLayout()
 ******************************************************************************/


/*N*/ void SwEditShell::CalcLayout()
/*N*/ {
/*N*/   StartAllAction();
/*N*/   ViewShell::CalcLayout();
/*N*/
/*N*/   ViewShell *pSh = this;
/*N*/   do
/*N*/   {
/*N*/       if ( pSh->GetWin() )
/*N*/           pSh->GetWin()->Invalidate();
/*N*/       pSh = (ViewShell*)pSh->GetNext();
/*N*/
/*N*/   } while ( pSh != this );
/*N*/
/*N*/   EndAllAction();
/*N*/ }

}
