/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_olinefun.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 09:21:04 $
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

#ifdef PCH
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------


#include "olinefun.hxx"

#include "docsh.hxx"
#include "globstr.hrc"
#include "bf_sc.hrc"
namespace binfilter {


//========================================================================

/*N*/ BOOL ScOutlineDocFunc::MakeOutline( const ScRange& rRange, BOOL bColumns, BOOL bRecord, BOOL bApi )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE; //STRIP001 BOOL bSuccess = FALSE;
/*N*/ }

/*N*/ BOOL ScOutlineDocFunc::RemoveOutline( const ScRange& rRange, BOOL bColumns, BOOL bRecord, BOOL bApi )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE; //STRIP001 BOOL bDone = FALSE;
/*N*/ }

/*N*/ BOOL ScOutlineDocFunc::RemoveAllOutlines( USHORT nTab, BOOL bRecord, BOOL bApi )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE; //STRIP001 BOOL bSuccess = FALSE;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL ScOutlineDocFunc::AutoOutline( const ScRange& rRange, BOOL bRecord, BOOL bApi )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 USHORT nStartCol = rRange.aStart.Col();
/*N*/   return TRUE;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL ScOutlineDocFunc::SelectLevel( USHORT nTab, BOOL bColumns, USHORT nLevel,
/*N*/                                   BOOL bRecord, BOOL bPaint, BOOL bApi )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   return TRUE;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL ScOutlineDocFunc::ShowMarkedOutlines( const ScRange& rRange, BOOL bRecord, BOOL bApi )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 BOOL bDone = FALSE;
/*N*/ }

/*N*/ BOOL ScOutlineDocFunc::HideMarkedOutlines( const ScRange& rRange, BOOL bRecord, BOOL bApi )
/*N*/ {
/*?*/   DBG_BF_ASSERT(0, "STRIP"); return FALSE; //STRIP001 BOOL bDone = FALSE;
/*N*/ }
}
