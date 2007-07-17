/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_objserv.cxx,v $
 *
 *  $Revision: 1.11 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 10:58:23 $
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

#include <com/sun/star/document/XExporter.hpp>
#include <tools/urlobj.hxx>
#include <svtools/whiter.hxx>
#include <svtools/eitem.hxx>
#include <svtools/itemset.hxx>

#pragma hdrstop

#include "request.hxx"
#include "docfile.hxx"
#include "app.hxx"
#include "docinf.hxx"
#include "objshimp.hxx"
#include "interno.hxx"
#include "docfac.hxx"
#include "fcontnr.hxx"

#include "so3/staticbaseurl.hxx"

namespace binfilter {

using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::awt;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::document;
using namespace ::com::sun::star::task;

//====================================================================

/*N*/ class SfxSaveAsContext_Impl
/*N*/ {
/*N*/   String&     _rNewNameVar;
/*N*/   String      _aNewName;
/*N*/
/*N*/ public:
/*N*/               SfxSaveAsContext_Impl( String &rNewNameVar,
/*N*/                                      const String &rNewName )
/*N*/               :   _rNewNameVar( rNewNameVar ),
/*N*/                   _aNewName( rNewName )
/*N*/               { rNewNameVar = rNewName; }
/*N*/               ~SfxSaveAsContext_Impl()
/*N*/               { _rNewNameVar.Erase(); }
/*N*/ };

//====================================================================

/*N*/ BOOL ShallSetBaseURL_Impl( SfxMedium &rMed );

svtools::AsynchronLink* pPendingCloser = 0;

//=========================================================================



/*N*/ long SfxObjectShellClose_Impl( void* pObj, void* pArg )
/*N*/ {
/*N*/   SfxObjectShell *pObjSh = (SfxObjectShell*) pArg;
/*N*/   if ( pObjSh->Get_Impl()->bHiddenLockedByAPI )
/*N*/   {
/*N*/       pObjSh->Get_Impl()->bHiddenLockedByAPI = FALSE;
/*N*/       pObjSh->OwnerLock(FALSE);
/*N*/   }
/*N*/   else if ( !pObjSh->Get_Impl()->bClosing )
/*N*/       // GCC stuerzt ab, wenn schon im dtor, also vorher Flag abfragen
/*?*/       pObjSh->DoClose();
/*N*/   return 0;
/*N*/ }

/*N*/ sal_Bool SfxObjectShell::APISaveAs_Impl
/*N*/ (
/*N*/   const String& aFileName,
/*N*/   SfxItemSet*   aParams
/*N*/ )
/*N*/ {
/*N*/     BOOL bOk = sal_False;
/*N*/
/*N*/   {DBG_CHKTHIS(SfxObjectShell, 0);}
/*N*/
/*N*/   pImp->bSetStandardName=FALSE;
/*N*/   if ( GetMedium() )
/*N*/   {
/*N*/       SFX_ITEMSET_ARG( aParams, pSaveToItem, SfxBoolItem, SID_SAVETO, sal_False );
/*N*/       sal_Bool bSaveTo = pSaveToItem && pSaveToItem->GetValue();
/*N*/
/*N*/       String aFilterName;
/*N*/       SFX_ITEMSET_ARG( aParams, pFilterNameItem, SfxStringItem, SID_FILTER_NAME, sal_False );
/*N*/       if( pFilterNameItem )
/*N*/           aFilterName = pFilterNameItem->GetValue();
/*N*/
/*N*/       // in case no filter defined use default one
/*N*/       if( !aFilterName.Len() )
/*N*/       {
/*N*/           sal_uInt16 nActFilt = 0;
/*N*/           const SfxFilter* pFilt = GetFactory().GetFilter( 0 ); for( ;
/*N*/                pFilt && ( !pFilt->CanExport()
/*N*/                 || !bSaveTo && !pFilt->CanImport() // SaveAs case
/*N*/                 || pFilt->IsInternal() );
/*N*/                pFilt = GetFactory().GetFilter( ++nActFilt ) );
/*N*/
/*N*/           DBG_ASSERT( pFilt, "No default filter!\n" );
/*N*/
/*N*/           if( pFilt )
/*N*/               aFilterName = pFilt->GetFilterName();
/*N*/
/*N*/           aParams->Put(SfxStringItem( SID_FILTER_NAME, aFilterName));
/*N*/       }
/*N*/
/*N*/
/*N*/       {
/*N*/           SfxObjectShellRef xLock( this ); // ???
/*N*/
/*N*/           // since saving a document modified its DocumentInfo, the current DocumentInfo must be saved on "SaveTo", because
/*N*/           // it must be restored after saving
/*N*/           SfxDocumentInfo aSavedInfo;
/*N*/           sal_Bool bCopyTo =  bSaveTo || GetCreateMode() == SFX_CREATE_MODE_EMBEDDED;
/*N*/           if ( bCopyTo )
/*N*/               aSavedInfo = GetDocInfo();
/*N*/
/*N*/           bOk = CommonSaveAs_Impl( INetURLObject(aFileName), aFilterName,
/*N*/               aParams );
/*N*/
/*N*/           if ( bCopyTo )
/*N*/           {
/*N*/               // restore DocumentInfo if only a copy was created
/*N*/               SfxDocumentInfo &rDocInfo = GetDocInfo();
/*N*/               rDocInfo = aSavedInfo;
/*N*/           }
/*N*/       }
/*N*/
/*N*/       // Picklisten-Eintrag verhindern
/*N*/       GetMedium()->SetUpdatePickList( FALSE );
/*N*/   }
/*N*/
/*N*/   return bOk;
/*N*/ }
}
