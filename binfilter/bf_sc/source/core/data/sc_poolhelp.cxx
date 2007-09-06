/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_poolhelp.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 10:38:45 $
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

#ifdef _MSC_VER
#pragma hdrstop
#endif

// INCLUDE ---------------------------------------------------------------

#include <svtools/zforlist.hxx>
#include <bf_svx/editeng.hxx>

#include "poolhelp.hxx"
#include "document.hxx"
#include "docpool.hxx"
#include "stlpool.hxx"
namespace binfilter {

// -----------------------------------------------------------------------

/*N*/ ScPoolHelper::ScPoolHelper( ScDocument* pSourceDoc )
/*N*/ {
/*N*/   DBG_ASSERT( pSourceDoc, "ScPoolHelper: no document" );
/*N*/
/*N*/   pDocPool = new ScDocumentPool;
/*N*/   pDocPool->FreezeIdRanges();
/*N*/
/*N*/   pStylePool = new ScStyleSheetPool( *pDocPool, pSourceDoc );
/*N*/
/*N*/   pFormTable = new SvNumberFormatter( pSourceDoc->GetServiceManager(), ScGlobal::eLnge );
/*N*/     pFormTable->SetColorLink( LINK( pSourceDoc, ScDocument, GetUserDefinedColor ) );
/*N*/   pFormTable->SetEvalDateFormat( NF_EVALDATEFORMAT_INTL_FORMAT );
/*N*/
/*N*/   pEditPool = EditEngine::CreatePool();
/*N*/   pEditPool->SetDefaultMetric( SFX_MAPUNIT_100TH_MM );
/*N*/   pEditPool->FreezeIdRanges();
/*N*/   pEditPool->SetFileFormatVersion( SOFFICE_FILEFORMAT_50 );   // used in ScGlobal::EETextObjEqual
/*N*/
/*N*/   pEnginePool = EditEngine::CreatePool();
/*N*/   pEnginePool->SetDefaultMetric( SFX_MAPUNIT_100TH_MM );
/*N*/   pEnginePool->FreezeIdRanges();
/*N*/ }

/*N*/ ScPoolHelper::~ScPoolHelper()
/*N*/ {
/*N*/   delete pEnginePool;
/*N*/   delete pEditPool;
/*N*/   delete pFormTable;
/*N*/   delete pStylePool;
/*N*/   delete pDocPool;
/*N*/ }

/*N*/ void ScPoolHelper::SourceDocumentGone()
/*N*/ {
/*N*/   //  reset all pointers to the source document
/*N*/   pStylePool->SetDocument( NULL );
/*N*/     pFormTable->SetColorLink( Link() );
/*N*/ }

// -----------------------------------------------------------------------


}
