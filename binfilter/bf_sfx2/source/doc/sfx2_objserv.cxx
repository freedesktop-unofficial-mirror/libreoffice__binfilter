/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_objserv.cxx,v $
 *
 *  $Revision: 1.10 $
 *
 *  last change: $Author: vg $ $Date: 2006-11-22 10:18:24 $
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









#ifndef _COM_SUN_STAR_DOCUMENT_XEXPORTER_HPP_
#include <com/sun/star/document/XExporter.hpp>
#endif



#ifndef _URLOBJ_HXX //autogen
#include <tools/urlobj.hxx>
#endif
#if SUPD<613//MUSTINI
#endif
#ifndef _SFX_WHITER_HXX //autogen
#include <svtools/whiter.hxx>
#endif
#if SUPD<613//MUSTINI
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif


#pragma hdrstop

#include "sfxresid.hxx"
#include "request.hxx"
#include "docfile.hxx"
#include "dispatch.hxx"
#include "dinfdlg.hxx"
#include "objshimp.hxx"
#include "interno.hxx"
#include "doc.hrc"
#include "docfac.hxx"
#include "fcontnr.hxx"

#ifndef _SFX_HELPID_HRC
#include "helpid.hrc"
#endif

#include "so3/staticbaseurl.hxx"
namespace binfilter {

using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::uno;
//using namespace ::com::sun::star::ui::dialogs;
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

#define SfxObjectShell
#include "sfxslots.hxx"

svtools::AsynchronLink* pPendingCloser = 0;

//=========================================================================



/*N*/ SFX_IMPL_INTERFACE(SfxObjectShell,SfxShell,SfxResId(0))
/*N*/ {
/*N*/ }

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

//=========================================================================

/*N*/ void SfxObjectShell::PrintExec_Impl(SfxRequest &rReq)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectShell::PrintState_Impl(SfxItemSet &rSet)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

//--------------------------------------------------------------------

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

//--------------------------------------------------------------------

/*N*/ void SfxObjectShell::ExecFile_Impl(SfxRequest &rReq)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectShell::GetState_Impl(SfxItemSet &rSet)
/*N*/ {
/*N*/   DBG_CHKTHIS(SfxObjectShell, 0);
/*N*/   SfxWhichIter aIter( rSet );
/*N*/   SfxInPlaceObject *pObj=GetInPlaceObject();
/*N*/   for ( USHORT nWhich = aIter.FirstWhich(); nWhich; nWhich = aIter.NextWhich() )
/*N*/   {
/*N*/       switch ( nWhich )
/*N*/       {
/*N*/             case SID_SAVE_VERSION_ON_CLOSE:
/*N*/             {
/*N*/                 rSet.Put( SfxBoolItem( nWhich, GetDocInfo().IsSaveVersionOnClose() ) );
/*N*/                 break;
/*N*/             }
/*N*/
/*N*/           case SID_DOCTEMPLATE :
/*N*/           {
/*N*/               if ( !GetFactory().GetTemplateFilter() )
/*N*/                   rSet.DisableItem( nWhich );
/*N*/               break;
/*N*/           }
/*N*/
/*N*/           case SID_VERSION:
/*N*/               {
/*N*/                   SfxObjectShell *pDoc = this;
/*N*/                   SfxViewFrame* pFrame = GetFrame();
/*N*/                   if ( !pFrame )
/*N*/                       pFrame = SfxViewFrame::GetFirst( this );
/*N*/                     if ( pFrame  )
/*N*/                   {
/*N*/                       if ( pFrame->GetFrame()->GetParentFrame() )
/*N*/                       {
/*N*/                           pFrame = pFrame->GetTopViewFrame();
/*N*/                           pDoc = pFrame->GetObjectShell();
/*N*/                       }
/*N*/                   }
/*N*/
/*N*/                   if ( !pFrame || !pDoc->HasName() ||
/*N*/                       !IsOwnStorageFormat_Impl( *pDoc->GetMedium() ) ||
/*N*/                       pDoc->GetMedium()->GetStorage()->GetVersion() < SOFFICE_FILEFORMAT_50 )
/*N*/                       rSet.DisableItem( nWhich );
/*N*/                   break;
/*N*/               }
/*N*/           case SID_SAVEDOC:
/*N*/           case SID_UPDATEDOC:
/*N*/               if (pObj && (
/*N*/                   pObj->GetProtocol().IsEmbed() ||
/*N*/                   GetCreateMode() == SFX_CREATE_MODE_EMBEDDED ))
/*N*/               {
/*N*/                   String aEntry (SfxResId(STR_UPDATEDOC));
/*N*/                   aEntry += ' ';
/*N*/                   aEntry += GetInPlaceObject()->GetDocumentName();
/*N*/                   rSet.Put(SfxStringItem(nWhich, aEntry));
/*N*/               }
/*N*/               else
/*N*/               {
/*N*/                   BOOL bMediumRO = IsReadOnlyMedium();
/*N*/                   if ( !bMediumRO && GetMedium() && IsModified() )
/*N*/                       rSet.Put(SfxStringItem(
/*N*/                           nWhich, String(SfxResId(STR_SAVEDOC))));
/*N*/                   else
/*N*/                       rSet.DisableItem(nWhich);
/*N*/               }
/*N*/               break;
/*N*/
/*N*/           case SID_DOCINFO:
/*N*/               if ( 0 != ( pImp->eFlags & SFXOBJECTSHELL_NODOCINFO ) )
/*N*/                   rSet.DisableItem( nWhich );
/*N*/               break;
/*N*/
/*N*/           case SID_CLOSEDOC:
/*N*/           {
/*N*/               SfxObjectShell *pDoc = this;
/*N*/               SfxViewFrame *pFrame = GetFrame();
/*N*/               if ( pFrame && pFrame->GetFrame()->GetParentFrame() )
/*N*/               {
/*N*/                   // Wenn SID_CLOSEDOC "uber Menue etc. ausgef"uhrt wird, das
/*N*/                   // aktuelle Dokument aber in einem Frame liegt, soll eigentlich
/*N*/                   // das FrameSetDocument geclosed werden
/*N*/                   pDoc = pFrame->GetTopViewFrame()->GetObjectShell();
/*N*/               }
/*N*/
/*N*/               if ( pDoc->GetFlags() & SFXOBJECTSHELL_DONTCLOSE )
/*N*/                   rSet.DisableItem(nWhich);
/*N*/               else if ( pObj && (
/*N*/                   pObj->GetProtocol().IsEmbed() ||
/*N*/                   GetCreateMode() == SFX_CREATE_MODE_EMBEDDED ))
/*N*/               {
/*N*/                   String aEntry (SfxResId(STR_CLOSEDOC_ANDRETURN));
/*N*/                   aEntry += pObj->GetDocumentName();
/*N*/                   rSet.Put( SfxStringItem(nWhich, aEntry) );
/*N*/               }
/*N*/               else
/*N*/                   rSet.Put(SfxStringItem(nWhich, String(SfxResId(STR_CLOSEDOC))));
/*N*/               break;
/*N*/           }
/*N*/
/*N*/           case SID_SAVEASDOC:
/*N*/           {
/*N*/               if( ( pImp->nLoadedFlags & SFX_LOADED_MAINDOCUMENT ) != SFX_LOADED_MAINDOCUMENT )
/*N*/               {
/*N*/                   rSet.DisableItem( nWhich );
/*N*/                   break;
/*N*/               }
/*N*/
/*N*/               const SfxFilter* pCombinedFilters = NULL;
/*N*/               SfxFactoryFilterContainer* pFilterContainer = GetFactory().GetFilterContainer();
/*N*/
/*N*/               if ( pFilterContainer )
/*N*/               {
/*N*/                   SfxFilterFlags    nMust    = SFX_FILTER_IMPORT | SFX_FILTER_EXPORT;
/*N*/                   SfxFilterFlags    nDont    = SFX_FILTER_NOTINSTALLED;
/*N*/
/*N*/                   pCombinedFilters = pFilterContainer->GetAnyFilter( nMust, nDont );
/*N*/               }
/*N*/
/*N*/               if ( !pCombinedFilters || !GetMedium() )
/*N*/                   rSet.DisableItem( nWhich );
/*N*/               else if ( pObj && (
/*N*/                   pObj->GetProtocol().IsEmbed() ||
/*N*/                   GetCreateMode() == SFX_CREATE_MODE_EMBEDDED ))
/*N*/                   rSet.Put( SfxStringItem( nWhich, String( SfxResId( STR_SAVECOPYDOC ) ) ) );
/*N*/               else
/*N*/                   rSet.Put( SfxStringItem( nWhich, String( SfxResId( STR_SAVEASDOC ) ) ) );
/*N*/
/*N*/               break;
/*N*/           }
/*N*/
/*N*/           case SID_EXPORTDOCASPDF:
/*N*/           case SID_DIRECTEXPORTDOCASPDF:
/*N*/           {
/*N*/               SfxFactoryFilterContainer* pFilterContainer = GetFactory().GetFilterContainer();
/*N*/               if ( pFilterContainer )
/*N*/               {
/*N*/                   String aPDFExtension = String::CreateFromAscii( ".pdf" );
/*N*/                   const SfxFilter* pFilter = pFilterContainer->GetFilter4Extension( aPDFExtension, SFX_FILTER_EXPORT );
/*N*/                   if ( pFilter != NULL )
/*N*/                       break;
/*N*/               }
/*N*/
/*N*/               rSet.DisableItem( nWhich );
/*N*/               break;
/*N*/           }
/*N*/
/*N*/           case SID_DOC_MODIFIED:
/*N*/           {
/*N*/               rSet.Put( SfxStringItem( SID_DOC_MODIFIED, IsModified() ? '*' : ' ' ) );
/*N*/               break;
/*N*/           }
/*N*/
/*N*/           case SID_MODIFIED:
/*N*/           {
/*N*/               rSet.Put( SfxBoolItem( SID_MODIFIED, IsModified() ) );
/*N*/               break;
/*N*/           }
/*N*/
/*N*/           case SID_DOCINFO_TITLE:
/*N*/           {
/*N*/               rSet.Put( SfxStringItem(
/*N*/                   SID_DOCINFO_TITLE, GetDocInfo().GetTitle() ) );
/*N*/               break;
/*N*/           }
/*N*/           case SID_FILE_NAME:
/*N*/           {
/*N*/               if( GetMedium() && HasName() )
/*N*/                   rSet.Put( SfxStringItem(
/*N*/                       SID_FILE_NAME, GetMedium()->GetName() ) );
/*N*/               break;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectShell::ExecProps_Impl(SfxRequest &rReq)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectShell::StateProps_Impl(SfxItemSet &rSet)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectShell::ExecView_Impl(SfxRequest &rReq)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectShell::StateView_Impl(SfxItemSet &rSet)
/*N*/ {
/*N*/ }

}
