/*************************************************************************
 *
 *  $RCSfile: sfx2_objserv.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2004-04-19 10:22:48 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/
#include <so3/svstor.hxx>

#ifndef  _COM_SUN_STAR_UI_DIALOGS_EXTENDEDFILEPICKERELEMENTIDS_HPP_
#include <com/sun/star/ui/dialogs/ExtendedFilePickerElementIds.hpp>
#endif

#ifndef  _COM_SUN_STAR_UI_DIALOGS_XFILEPICKERCONTROLACCESS_HPP_
#include <com/sun/star/ui/dialogs/XFilePickerControlAccess.hpp>
#endif

#ifndef  _COM_SUN_STAR_UI_DIALOGS_COMMONFILEPICKERELEMENTIDS_HPP_
#include <com/sun/star/ui/dialogs/CommonFilePickerElementIds.hpp>
#endif

#ifndef _COM_SUN_STAR_UI_DIALOGS_XCONTROLACCESS_HPP_
#include <com/sun/star/ui/dialogs/XControlAccess.hpp>
#endif

#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif

#ifndef _COM_SUN_STAR_BEANS_XPROPERTYACCESS_HPP_
#include <com/sun/star/beans/XPropertyAccess.hpp>
#endif

#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif

#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
#include <com/sun/star/container/XNameAccess.hpp>
#endif

#ifndef _COM_SUN_STAR_DOCUMENT_XEXPORTER_HPP_
#include <com/sun/star/document/XExporter.hpp>
#endif

#ifndef _COM_SUN_STAR_TASK_XINTERACTIONHANDLER_HPP_
#include <com/sun/star/task/XInteractionHandler.hpp>
#endif

#ifndef _UNOTOOLS_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif

#ifndef _URLOBJ_HXX //autogen
#include <tools/urlobj.hxx>
#endif
#if SUPD<613//MUSTINI
    #ifndef _SFX_INIMGR_HXX //autogen
    #include <inimgr.hxx>
    #endif
#endif
#ifndef _SFX_WHITER_HXX //autogen
#include <svtools/whiter.hxx>
#endif
#if SUPD<613//MUSTINI
    #ifndef _SFXINIMGR_HXX //autogen
    #include <svtools/iniman.hxx>
    #endif
#endif
#ifndef _MSGBOX_HXX //autogen
#include <vcl/msgbox.hxx>
#endif
#ifndef _SFXINTITEM_HXX //autogen
#include <svtools/intitem.hxx>
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#include <vcl/wrkwin.hxx>
#ifndef _SFXECODE_HXX
#include <svtools/sfxecode.hxx>
#endif
#ifndef _EHDL_HXX
#include <svtools/ehdl.hxx>
#endif

#include <svtools/sbx.hxx>
#include <svtools/pathoptions.hxx>
#include <svtools/useroptions.hxx>
#include <svtools/asynclink.hxx>
#include <svtools/saveopt.hxx>

#pragma hdrstop

#include "sfxresid.hxx"
#include "event.hxx"
#include "request.hxx"
#include "printer.hxx"
#include "viewsh.hxx"
#include "doctdlg.hxx"
#include "docfilt.hxx"
#include "docfile.hxx"
#include "docinf.hxx"
#include "dispatch.hxx"
#include "dinfdlg.hxx"
#include "objitem.hxx"
#include "objsh.hxx"
#include "objshimp.hxx"
#include "sfxtypes.hxx"
#include "interno.hxx"
#include "module.hxx"
#include "topfrm.hxx"
#include "versdlg.hxx"
#include "doc.hrc"
#include "docfac.hxx"
#include "fcontnr.hxx"
#include "filedlghelper.hxx"
#include "sfxhelp.hxx"

#ifndef _SFX_HELPID_HRC
#include "helpid.hrc"
#endif

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {

using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::ui::dialogs;
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
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  SfxViewFrame *pFrame = SfxViewFrame::GetFirst(this);
//STRIP001  if ( pFrame )
//STRIP001  {
//STRIP001      rReq.SetSlot( SID_PRINTDOC );
//STRIP001      pFrame->GetViewShell()->ExecuteSlot(rReq);
//STRIP001  }
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectShell::PrintState_Impl(SfxItemSet &rSet)
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  FASTBOOL bPrinting = FALSE;
//STRIP001  SfxViewFrame *pFrame = SfxViewFrame::GetFirst(this, TYPE(SfxTopViewFrame));
//STRIP001  if ( pFrame )
//STRIP001  {
//STRIP001      SfxPrinter *pPrinter = pFrame->GetViewShell()->GetPrinter();
//STRIP001      bPrinting = pPrinter && pPrinter->IsPrinting();
//STRIP001  }
//STRIP001  rSet.Put( SfxBoolItem( SID_PRINTOUT, bPrinting ) );
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
/*N*/           bOk = CommonSaveAs_Impl( aFileName, aFilterName, aParams );
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

//-------------------------------------------------------------------------

//STRIP001 sal_Bool SfxObjectShell::GUISaveAs_Impl(sal_Bool bUrl, SfxRequest *pRequest)
//STRIP001 {
//STRIP001  INetURLObject aURL;
//STRIP001
//STRIP001     SFX_REQUEST_ARG( (*pRequest), pSaveToItem, SfxBoolItem, SID_SAVETO, sal_False );
//STRIP001
//STRIP001  sal_Bool bSaveTo = pSaveToItem ? pSaveToItem->GetValue() : sal_False;
//STRIP001  sal_Bool bIsPDFExport = (( pRequest->GetSlot() == SID_EXPORTDOCASPDF ) ||
//STRIP001                          ( pRequest->GetSlot() == SID_DIRECTEXPORTDOCASPDF ));
//STRIP001  sal_Bool bIsExport = ( pRequest->GetSlot() == SID_EXPORTDOC ) || bIsPDFExport;
//STRIP001  sal_Bool bSuppressFilterOptionsDialog = sal_False;
//STRIP001
//STRIP001  // Parameter to return if user cancelled a optional configuration dialog and
//STRIP001  // there for cancelled the whole save procedure.
//STRIP001  DBG_ASSERT( !bIsExport || bSaveTo, "Export mode should use SaveTo mechanics!\n" );
//STRIP001
//STRIP001  const SfxFilter* pFilt = NULL;
//STRIP001  if ( pRequest->GetSlot() == SID_EXPORTDOCASPDF ||
//STRIP001       pRequest->GetSlot() == SID_DIRECTEXPORTDOCASPDF )
//STRIP001  {
//STRIP001      // Preselect PDF-Filter for EXPORT
//STRIP001      pFilt = GetFactory().GetFilterContainer()->GetFilter4Extension( String::CreateFromAscii( ".pdf" ), SFX_FILTER_EXPORT );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      sal_uInt16 nActFilt = 0;
//STRIP001      for( pFilt = GetFactory().GetFilter( 0 );
//STRIP001          pFilt && ( !pFilt->CanExport()
//STRIP001                  || bIsExport && pFilt->CanImport() // Export case ( only for GUI )
//STRIP001                  || !bSaveTo && !pFilt->CanImport() // SaveAs case
//STRIP001                  || pFilt->IsInternal() );
//STRIP001          pFilt = GetFactory().GetFilter( ++nActFilt ) );
//STRIP001  }
//STRIP001
//STRIP001  DBG_ASSERT( pFilt, "Kein Filter zum Speichern" );
//STRIP001  if ( !pFilt )
//STRIP001      return sal_False;
//STRIP001
//STRIP001  String aFilterName;
//STRIP001  if( pFilt )
//STRIP001         aFilterName = pFilt->GetFilterName();
//STRIP001
//STRIP001  SfxItemSet *pParams = new SfxAllItemSet( SFX_APP()->GetPool() );
//STRIP001     SFX_REQUEST_ARG( (*pRequest), pFileNameItem, SfxStringItem, SID_FILE_NAME, sal_False );
//STRIP001     if ( pRequest->GetArgs() )
//STRIP001         pParams->Put( *pRequest->GetArgs() );
//STRIP001
//STRIP001  SfxItemSet* pMedSet = pMedium->GetItemSet();
//STRIP001  SFX_ITEMSET_ARG( pMedSet, pOptionsItem, SfxStringItem, SID_FILE_FILTEROPTIONS, sal_False );
//STRIP001  if ( pOptionsItem && pParams->GetItemState(SID_FILE_FILTEROPTIONS) != SFX_ITEM_SET )
//STRIP001      pParams->Put( *pOptionsItem );
//STRIP001
//STRIP001     SFX_ITEMSET_ARG( pMedSet, pDataItem, SfxUsrAnyItem, SID_FILTER_DATA, sal_False );
//STRIP001  if ( pDataItem && pParams->GetItemState(SID_FILTER_DATA) != SFX_ITEM_SET )
//STRIP001      pParams->Put( *pDataItem );
//STRIP001
//STRIP001     sal_Bool bDialogUsed = sal_False;
//STRIP001  sal_Bool bUseFilterOptions = sal_False;
//STRIP001
//STRIP001  Reference< XMultiServiceFactory > xServiceManager = ::legacy_binfilters::getLegacyProcessServiceFactory();
//STRIP001  Reference< XNameAccess > xFilterCFG;
//STRIP001  if( xServiceManager.is() )
//STRIP001  {
//STRIP001      xFilterCFG = Reference< XNameAccess >(
//STRIP001          xServiceManager->createInstance( ::rtl::OUString::createFromAscii( "com.sun.star.document.FilterFactory" ) ),
//STRIP001          UNO_QUERY );
//STRIP001  }
//STRIP001
//STRIP001     if ( !pFileNameItem )
//STRIP001  {
//STRIP001         // we need to show the file dialog
//STRIP001         bDialogUsed = sal_True;
//STRIP001      if(! bUrl )
//STRIP001      {
//STRIP001             // check if we have a filter which allows for filter options, so we need a corresponding checkbox in the dialog
//STRIP001          sal_Bool bAllowOptions = sal_False;
//STRIP001          const SfxFilter* pFilter;
//STRIP001          SfxFilterFlags nMust = SFX_FILTER_EXPORT | ( bSaveTo ? 0 : SFX_FILTER_IMPORT );
//STRIP001          SfxFilterFlags nDont = SFX_FILTER_INTERNAL | SFX_FILTER_NOTINFILEDLG | ( bIsExport ? SFX_FILTER_IMPORT : 0 );
//STRIP001
//STRIP001          SfxFilterMatcher aMatcher( GetFactory().GetFilterContainer() );
//STRIP001          SfxFilterMatcherIter aIter( &aMatcher, nMust, nDont );
//STRIP001
//STRIP001          if( !bIsExport )
//STRIP001          {
//STRIP001              // in case of Export, filter options dialog is used if available
//STRIP001              for ( pFilter = aIter.First(); pFilter && !bAllowOptions; pFilter = aIter.Next() )
//STRIP001              {
//STRIP001                  if( xFilterCFG.is() )
//STRIP001                  {
//STRIP001                      try {
//STRIP001                          Sequence < PropertyValue > aProps;
//STRIP001                          Any aAny = xFilterCFG->getByName( pFilter->GetName() );
//STRIP001                          if ( aAny >>= aProps )
//STRIP001                          {
//STRIP001                              ::rtl::OUString aServiceName;
//STRIP001                              sal_Int32 nPropertyCount = aProps.getLength();
//STRIP001                              for( sal_Int32 nProperty=0; nProperty < nPropertyCount; ++nProperty )
//STRIP001                                  if( aProps[nProperty].Name.equals( ::rtl::OUString::createFromAscii("UIComponent")) )
//STRIP001                                  {
//STRIP001                                      ::rtl::OUString aServiceName;
//STRIP001                                      aProps[nProperty].Value >>= aServiceName;
//STRIP001                                      if( aServiceName.getLength() )
//STRIP001                                          bAllowOptions = sal_True;
//STRIP001                                  }
//STRIP001                          }
//STRIP001                      }
//STRIP001                      catch( Exception& )
//STRIP001                      {
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001             // get the filename by dialog ...
//STRIP001          // create the file dialog
//STRIP001          sal_Int16  aDialogMode = bAllowOptions ?
//STRIP001                                      ::sfx2::FILESAVE_AUTOEXTENSION_PASSWORD_FILTEROPTIONS :
//STRIP001                                      ::sfx2::FILESAVE_AUTOEXTENSION_PASSWORD;
//STRIP001          sal_uInt32 aDialogFlags = 0;
//STRIP001
//STRIP001          if( bIsExport )
//STRIP001          {
//STRIP001              aDialogMode  = ::sfx2::FILESAVE_AUTOEXTENSION_SELECTION;
//STRIP001              aDialogFlags = SFXWB_EXPORT;
//STRIP001          }
//STRIP001
//STRIP001             sfx2::FileDialogHelper* pFileDlg = NULL;
//STRIP001
//STRIP001          if ( bIsExport || bIsPDFExport )
//STRIP001          {
//STRIP001              // This is the normal dialog
//STRIP001              SfxObjectFactory& rFact = GetFactory();
//STRIP001              pFileDlg = new sfx2::FileDialogHelper( aDialogMode, aDialogFlags, rFact, nMust, nDont );
//STRIP001
//STRIP001              if( strcmp( rFact.GetShortName(), "sdraw" ) != 0 )
//STRIP001                  pFileDlg->SetContext( sfx2::FileDialogHelper::SD_EXPORT );
//STRIP001              else if( strcmp( rFact.GetShortName(), "simpress" ) != 0 )
//STRIP001                  pFileDlg->SetContext( sfx2::FileDialogHelper::SI_EXPORT );
//STRIP001
//STRIP001              pFileDlg->CreateMatcher( rFact );
//STRIP001              Reference< ::com::sun::star::ui::dialogs::XFilePicker > xFilePicker = pFileDlg->GetFilePicker();
//STRIP001              Reference< ::com::sun::star::ui::dialogs::XFilePickerControlAccess > xControlAccess =
//STRIP001                  Reference< ::com::sun::star::ui::dialogs::XFilePickerControlAccess >( xFilePicker, UNO_QUERY );
//STRIP001
//STRIP001              if ( xControlAccess.is() )
//STRIP001              {
//STRIP001                  String aResStr = String( SfxResId( STR_EXPORTBUTTON ));
//STRIP001                  ::rtl::OUString aCtrlText = aResStr;
//STRIP001                  xControlAccess->setLabel( ::com::sun::star::ui::dialogs::CommonFilePickerElementIds::PUSHBUTTON_OK, aCtrlText );
//STRIP001                  aResStr = String( SfxResId( STR_LABEL_FILEFORMAT ));
//STRIP001                  aCtrlText = aResStr;
//STRIP001                  xControlAccess->setLabel( ::com::sun::star::ui::dialogs::CommonFilePickerElementIds::LISTBOX_FILTER_LABEL, aCtrlText );
//STRIP001              }
//STRIP001
//STRIP001              if ( bIsPDFExport && pFilt )
//STRIP001                  pFileDlg->SetCurrentFilter( pFilt->GetUIName() );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              // This is the normal dialog
//STRIP001              pFileDlg = new sfx2::FileDialogHelper( aDialogMode, aDialogFlags, GetFactory(), nMust, nDont );
//STRIP001              pFileDlg->CreateMatcher( GetFactory() );
//STRIP001          }
//STRIP001
//STRIP001          SFX_ITEMSET_ARG( pMedSet, pRepairItem, SfxBoolItem, SID_REPAIRPACKAGE, sal_False );
//STRIP001          if ( HasName() && !( pRepairItem && pRepairItem->GetValue() ) )
//STRIP001          {
//STRIP001              String aLastName = QueryTitle( SFX_TITLE_QUERY_SAVE_NAME_PROPOSAL );
//STRIP001              const SfxFilter* pMedFilter = GetMedium()->GetFilter();
//STRIP001              if( pImp->bSetStandardName && !IsTemplate()
//STRIP001                  || !pMedFilter
//STRIP001                  || !pMedFilter->CanExport()
//STRIP001                  || bIsExport && pMedFilter->CanImport() // Export case ( only for GUI )
//STRIP001                  || !bSaveTo && !pMedFilter->CanImport() // SaveAs case
//STRIP001                  /*!!!|| pMedFilter->GetVersion() != SOFFICE_FILEFORMAT_CURRENT*/ )
//STRIP001              {
//STRIP001                  if( aLastName.Len() )
//STRIP001                  {
//STRIP001                      String aPath( aLastName );
//STRIP001                         bool bWasAbsolute = sal_False;
//STRIP001                         INetURLObject aObj( SvtPathOptions().GetWorkPath() );
//STRIP001                         aObj.setFinalSlash();
//STRIP001                         aObj = INetURLObject( aObj.RelToAbs( aPath, bWasAbsolute ) );
//STRIP001                         aObj.SetExtension( pFilt->GetDefaultExtension().Copy(2) );
//STRIP001                         pFileDlg->SetDisplayDirectory( aObj.GetMainURL( INetURLObject::NO_DECODE ) );
//STRIP001                  }
//STRIP001
//STRIP001                     pFileDlg->SetCurrentFilter( pFilt->GetUIName() );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  if( aLastName.Len() )
//STRIP001                      pFileDlg->SetDisplayDirectory( aLastName );
//STRIP001                     pFileDlg->SetCurrentFilter( pMedFilter->GetUIName() );
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001                 pFileDlg->SetDisplayDirectory( SvtPathOptions().GetWorkPath() );
//STRIP001          }
//STRIP001
//STRIP001          SFX_ITEMSET_ARG( GetMedium()->GetItemSet(), pPassItem, SfxStringItem, SID_PASSWORD, FALSE );
//STRIP001          if ( pPassItem != NULL )
//STRIP001              pParams->Put( SfxStringItem( SID_PASSWORD, ::rtl::OUString() ) );
//STRIP001
//STRIP001          Reference < ::com::sun::star::view::XSelectionSupplier > xSel( GetModel()->getCurrentController(), UNO_QUERY );
//STRIP001          if ( xSel.is() && xSel->getSelection().hasValue() )
//STRIP001              pParams->Put( SfxBoolItem( SID_SELECTION, TRUE ) );
//STRIP001
//STRIP001             if ( pFileDlg->Execute( pParams, aFilterName ) != ERRCODE_NONE )
//STRIP001          {
//STRIP001              SetError(ERRCODE_IO_ABORT);
//STRIP001              delete pFileDlg;
//STRIP001              return sal_False;
//STRIP001          }
//STRIP001
//STRIP001             // get the path from the dialog
//STRIP001          aURL.SetURL( pFileDlg->GetPath() );
//STRIP001
//STRIP001          // gibt es schon ein Doc mit dem Namen?
//STRIP001             if ( aURL.GetProtocol() != INET_PROT_NOT_VALID )
//STRIP001             {
//STRIP001                 SfxObjectShell* pDoc = 0;
//STRIP001                 for ( SfxObjectShell* pTmp = SfxObjectShell::GetFirst();
//STRIP001                       pTmp && !pDoc;
//STRIP001                       pTmp = SfxObjectShell::GetNext(*pTmp) )
//STRIP001                 {
//STRIP001                     if( ( pTmp != this ) && pTmp->GetMedium() )
//STRIP001                     {
//STRIP001                         INetURLObject aCompare( pTmp->GetMedium()->GetName() );
//STRIP001                         if ( aCompare == aURL )
//STRIP001                             pDoc = pTmp;
//STRIP001                     }
//STRIP001                 }
//STRIP001                 if ( pDoc )
//STRIP001                 {
//STRIP001                     // dann Fehlermeldeung: "schon offen"
//STRIP001                     SetError(ERRCODE_SFX_ALREADYOPEN);
//STRIP001                  delete pFileDlg;
//STRIP001                     return sal_False;
//STRIP001                 }
//STRIP001             }
//STRIP001
//STRIP001          // old filter options should be cleared in case different filter is used
//STRIP001          SFX_ITEMSET_ARG( pMedSet, pOldFilterNameItem, SfxStringItem, SID_FILTER_NAME, sal_False );
//STRIP001          if ( !pOldFilterNameItem || pOldFilterNameItem->GetValue().CompareTo( aFilterName ) != COMPARE_EQUAL )
//STRIP001          {
//STRIP001              pParams->ClearItem( SID_FILTER_DATA );
//STRIP001              pParams->ClearItem( SID_FILE_FILTEROPTIONS );
//STRIP001          }
//STRIP001
//STRIP001          // --**-- pParams->Put( *pDlg->GetItemSet() );
//STRIP001          Reference< XFilePickerControlAccess > xExtFileDlg( pFileDlg->GetFilePicker(), UNO_QUERY );
//STRIP001          if ( xExtFileDlg.is() )
//STRIP001          {
//STRIP001              try
//STRIP001              {
//STRIP001                  if( xFilterCFG.is() )
//STRIP001                  {
//STRIP001                      try {
//STRIP001                          Sequence < PropertyValue > aProps;
//STRIP001                             Any aAny = xFilterCFG->getByName( aFilterName );
//STRIP001                          if ( aAny >>= aProps )
//STRIP001                          {
//STRIP001                              ::rtl::OUString aServiceName;
//STRIP001                              sal_Int32 nPropertyCount = aProps.getLength();
//STRIP001                              for( sal_Int32 nProperty=0; nProperty < nPropertyCount; ++nProperty )
//STRIP001                                  if( aProps[nProperty].Name.equals( ::rtl::OUString::createFromAscii("UIComponent")) )
//STRIP001                                  {
//STRIP001                                      ::rtl::OUString aServiceName;
//STRIP001                                      aProps[nProperty].Value >>= aServiceName;
//STRIP001                                      if( aServiceName.getLength() )
//STRIP001                                             bUseFilterOptions = sal_True;
//STRIP001                                  }
//STRIP001                          }
//STRIP001                      }
//STRIP001                      catch( Exception& )
//STRIP001                      {
//STRIP001                      }
//STRIP001                  }
//STRIP001
//STRIP001                     if ( !bIsExport && bUseFilterOptions )
//STRIP001                     {
//STRIP001                         // for exporters: always show dialog if format uses options
//STRIP001                         // for save: show dialog if format uses options and no options given or if forced by user
//STRIP001                         Any aValue = xExtFileDlg->getValue( ExtendedFilePickerElementIds::CHECKBOX_FILTEROPTIONS, 0 );
//STRIP001                         aValue >>= bUseFilterOptions;
//STRIP001                         if ( !bUseFilterOptions )
//STRIP001                             bUseFilterOptions = pParams->GetItemState( SID_FILTER_DATA ) != SFX_ITEM_SET &&
//STRIP001                                                 pParams->GetItemState( SID_FILE_FILTEROPTIONS ) != SFX_ITEM_SET;
//STRIP001                     }
//STRIP001
//STRIP001                     //pParams->Put( SfxBoolItem( SID_USE_FILTEROPTIONS, bUseFilterOptions ) );
//STRIP001              }
//STRIP001              catch( IllegalArgumentException ){}
//STRIP001          }
//STRIP001
//STRIP001          delete pFileDlg;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          SfxUrlDialog aDlg( 0 );
//STRIP001          if( aDlg.Execute() == RET_OK )
//STRIP001              aURL.SetURL( aDlg.GetUrl() );
//STRIP001          else
//STRIP001          {
//STRIP001              SetError(ERRCODE_IO_ABORT);
//STRIP001              return sal_False;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // merge in results of the dialog execution
//STRIP001      pParams->Put( SfxStringItem( SID_FILE_NAME, aURL.GetMainURL( INetURLObject::NO_DECODE )) );
//STRIP001      pParams->Put( SfxStringItem( SID_FILTER_NAME, aFilterName) );
//STRIP001      // Request mit Dateiname und Filter vervollst"andigen
//STRIP001         pRequest->AppendItem(SfxStringItem( SID_FILE_NAME, aURL.GetMainURL( INetURLObject::NO_DECODE )) );
//STRIP001         pRequest->AppendItem(SfxStringItem( SID_FILTER_NAME, aFilterName));
//STRIP001         const SfxPoolItem* pItem=0;
//STRIP001         pRequest->GetArgs()->GetItemState( SID_FILE_NAME, sal_False, &pItem );
//STRIP001         pFileNameItem = PTR_CAST( SfxStringItem, pItem );
//STRIP001  }
//STRIP001
//STRIP001  // neuen Namen an der Object-Shell merken
//STRIP001  SfxSaveAsContext_Impl aSaveAsCtx( pImp->aNewName, aURL.GetMainURL( INetURLObject::NO_DECODE ) );
//STRIP001
//STRIP001  // now we can get the filename from the SfxRequest
//STRIP001     DBG_ASSERT( pRequest->GetArgs() != 0, "fehlerhafte Parameter");
//STRIP001
//STRIP001     if ( !pFileNameItem && bSaveTo )
//STRIP001     {
//STRIP001         bDialogUsed = sal_True;
//STRIP001
//STRIP001      // get the filename by dialog ...
//STRIP001      // create the file dialog
//STRIP001         sfx2::FileDialogHelper aFileDlg( ::sfx2::FILESAVE_AUTOEXTENSION_PASSWORD,
//STRIP001                                          0L, GetFactory() );
//STRIP001
//STRIP001      SfxItemSet* pTempSet = NULL;
//STRIP001      if ( aFileDlg.Execute( pParams, aFilterName ) != ERRCODE_NONE )
//STRIP001      {
//STRIP001          SetError(ERRCODE_IO_ABORT);
//STRIP001          return sal_False;
//STRIP001      }
//STRIP001
//STRIP001         // get the path from the dialog
//STRIP001      aURL.SetURL( aFileDlg.GetPath() );
//STRIP001
//STRIP001      // merge in results of the dialog execution
//STRIP001      if( pTempSet )
//STRIP001          pParams->Put( *pTempSet );
//STRIP001
//STRIP001      // old filter options should be cleared in case different filter is used
//STRIP001      SFX_ITEMSET_ARG( pMedSet, pOldFilterNameItem, SfxStringItem, SID_FILTER_NAME, sal_False );
//STRIP001      if ( !pOldFilterNameItem || pOldFilterNameItem->GetValue().CompareTo( aFilterName ) != COMPARE_EQUAL )
//STRIP001      {
//STRIP001          pParams->ClearItem( SID_FILTER_DATA );
//STRIP001          pParams->ClearItem( SID_FILE_FILTEROPTIONS );
//STRIP001      }
//STRIP001
//STRIP001      pParams->Put( SfxStringItem( SID_FILE_NAME, aURL.GetMainURL( INetURLObject::NO_DECODE )) );
//STRIP001      pParams->Put( SfxStringItem( SID_FILTER_NAME, aFilterName) );
//STRIP001         pRequest->AppendItem(SfxStringItem( SID_FILE_NAME, aURL.GetMainURL( INetURLObject::NO_DECODE )) );
//STRIP001         pRequest->AppendItem(SfxStringItem( SID_FILTER_NAME, aFilterName));
//STRIP001     }
//STRIP001     else if ( pFileNameItem )
//STRIP001     {
//STRIP001         aURL.SetURL(((const SfxStringItem *)pFileNameItem)->GetValue() );
//STRIP001         DBG_ASSERT( aURL.GetProtocol() != INET_PROT_NOT_VALID, "Illegal URL!" );
//STRIP001
//STRIP001         const SfxPoolItem* pFilterNameItem=0;
//STRIP001         const SfxItemState eState = pRequest->GetArgs()->GetItemState(SID_FILTER_NAME, sal_True, &pFilterNameItem);
//STRIP001         if ( SFX_ITEM_SET == eState )
//STRIP001         {
//STRIP001             DBG_ASSERT(pFilterNameItem->IsA( TYPE(SfxStringItem) ), "Fehler Parameter");
//STRIP001             aFilterName = ((const SfxStringItem *)pFilterNameItem)->GetValue();
//STRIP001         }
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         SetError( ERRCODE_IO_INVALIDPARAMETER );
//STRIP001         return sal_False;
//STRIP001     }
//STRIP001
//STRIP001  SfxErrorContext aEc(ERRCTX_SFX_SAVEASDOC,GetTitle());
//STRIP001
//STRIP001     // check if a "SaveTo" is wanted, no "SaveAs"
//STRIP001     sal_Bool bCopyTo = GetCreateMode() == SFX_CREATE_MODE_EMBEDDED || bSaveTo;
//STRIP001
//STRIP001     // because saving a document modified its DocumentInfo, the current DocumentInfo must be saved on "SaveTo", because
//STRIP001     // it must be restored after saving
//STRIP001  SfxDocumentInfo aSavedInfo;
//STRIP001  if ( bCopyTo )
//STRIP001      aSavedInfo = GetDocInfo();
//STRIP001
//STRIP001  // if it is defenitly SaveAs then update doc info
//STRIP001  SfxBoolResetter aDocInfoReset( pImp->bDoNotTouchDocInfo );
//STRIP001  SfxMedium *pActMed = GetMedium();
//STRIP001  const INetURLObject aActName(pActMed->GetName());
//STRIP001
//STRIP001  // Don't show filter options dialog
//STRIP001  if ( pRequest->GetSlot() == SID_DIRECTEXPORTDOCASPDF )
//STRIP001      bSuppressFilterOptionsDialog = sal_True;
//STRIP001
//STRIP001  if( !bSuppressFilterOptionsDialog &&
//STRIP001      ( bSaveTo || bUseFilterOptions ))
//STRIP001  {
//STRIP001      // call filter dialog
//STRIP001      if( xFilterCFG.is() )
//STRIP001      {
//STRIP001          try {
//STRIP001                  Sequence < PropertyValue > aProps;
//STRIP001                  Any aAny = xFilterCFG->getByName( aFilterName );
//STRIP001                  if ( aAny >>= aProps )
//STRIP001                  {
//STRIP001                      ::rtl::OUString aServiceName;
//STRIP001                      sal_Int32 nPropertyCount = aProps.getLength();
//STRIP001                      for( sal_Int32 nProperty=0; nProperty < nPropertyCount; ++nProperty )
//STRIP001                          if( aProps[nProperty].Name.equals( ::rtl::OUString::createFromAscii("UIComponent")) )
//STRIP001                          {
//STRIP001                          ::rtl::OUString aServiceName;
//STRIP001                              aProps[nProperty].Value >>= aServiceName;
//STRIP001                          if( aServiceName.getLength() )
//STRIP001                          {
//STRIP001                              Reference< XExecutableDialog > xFilterDialog( xServiceManager->createInstance( aServiceName ), UNO_QUERY );
//STRIP001                              Reference< XPropertyAccess > xFilterProperties( xFilterDialog, UNO_QUERY );
//STRIP001
//STRIP001                              if( xFilterDialog.is() && xFilterProperties.is() )
//STRIP001                              {
//STRIP001                                  bDialogUsed = sal_True;
//STRIP001
//STRIP001                                  Reference< XExporter > xExporter( xFilterDialog, UNO_QUERY );
//STRIP001                                  if( xExporter.is() )
//STRIP001                                      xExporter->setSourceDocument( Reference< XComponent >( GetModel(), UNO_QUERY ) );
//STRIP001
//STRIP001                                  Sequence< PropertyValue > aPropsForDialog;
//STRIP001                                  TransformItems( pRequest->GetSlot(), *pParams, aPropsForDialog, NULL );
//STRIP001                                  xFilterProperties->setPropertyValues( aPropsForDialog );
//STRIP001
//STRIP001                                  if( xFilterDialog->execute() )
//STRIP001                                  {
//STRIP001                                      SfxAllItemSet aNewParams( GetPool() );
//STRIP001                                      TransformParameters( pRequest->GetSlot(),
//STRIP001                                                           xFilterProperties->getPropertyValues(),
//STRIP001                                                           aNewParams,
//STRIP001                                                           NULL );
//STRIP001                                      pParams->Put( aNewParams );
//STRIP001                                  }
//STRIP001                                  else
//STRIP001                                  {
//STRIP001                                      SetError(ERRCODE_IO_ABORT);
//STRIP001                                      return sal_False; // cancel
//STRIP001                                  }
//STRIP001                              }
//STRIP001                          }
//STRIP001
//STRIP001                          break;
//STRIP001                      }
//STRIP001              }
//STRIP001          }
//STRIP001          catch( NoSuchElementException& )
//STRIP001          {
//STRIP001              // the filter name is unknown
//STRIP001                  SetError( ERRCODE_IO_INVALIDPARAMETER );
//STRIP001              return sal_False;
//STRIP001          }
//STRIP001          catch( Exception& )
//STRIP001          {
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if ( aURL != aActName )
//STRIP001  {
//STRIP001      // this is defenitly not a Save
//STRIP001      pImp->bIsSaving = sal_False; // here it's already clear
//STRIP001
//STRIP001      // ggf. DocInfo Dialog
//STRIP001      if( bCopyTo && IsEnableSetModified() )
//STRIP001      {
//STRIP001          EnableSetModified( sal_False );
//STRIP001          UpdateDocInfoForSave();
//STRIP001          EnableSetModified( sal_True );
//STRIP001      }
//STRIP001      else
//STRIP001          UpdateDocInfoForSave();
//STRIP001
//STRIP001         if (  eCreateMode == SFX_CREATE_MODE_STANDARD && 0 == ( pImp->eFlags & SFXOBJECTSHELL_NODOCINFO ) )
//STRIP001      {
//STRIP001             SvtSaveOptions aOptions;
//STRIP001             if ( aOptions.IsDocInfoSave() )
//STRIP001          {
//STRIP001                 DocInfoDlg_Impl( GetDocInfo() );
//STRIP001              pImp->bDoNotTouchDocInfo = sal_True;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  sal_Bool bOk = CommonSaveAs_Impl( aURL, aFilterName, pParams );
//STRIP001
//STRIP001  if ( bCopyTo )
//STRIP001  {
//STRIP001         // restore DocumentInfo if only a copy was created
//STRIP001      SfxDocumentInfo &rDocInfo = GetDocInfo();
//STRIP001      rDocInfo = aSavedInfo;
//STRIP001  }
//STRIP001
//STRIP001  if( bOk )
//STRIP001  {
//STRIP001         if  (   bDialogUsed
//STRIP001             &&  pFilt->IsOwnFormat()
//STRIP001             &&  pFilt->UsesStorage()
//STRIP001             &&  pFilt->GetVersion() >= SOFFICE_FILEFORMAT_60
//STRIP001             )
//STRIP001         {
//STRIP001             SfxViewFrame* pDocViewFrame = SfxViewFrame::GetFirst( this );
//STRIP001             SfxFrame* pDocFrame = pDocViewFrame ? pDocViewFrame->GetFrame() : NULL;
//STRIP001             if ( pDocFrame )
//STRIP001                 SfxHelp::OpenHelpAgent( pDocFrame, HID_DID_SAVE_PACKED_XML );
//STRIP001         }
//STRIP001
//STRIP001      return sal_True;
//STRIP001  }
//STRIP001  else
//STRIP001      return sal_False;
//STRIP001 }

//--------------------------------------------------------------------

/*N*/ void SfxObjectShell::ExecFile_Impl(SfxRequest &rReq)
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  {DBG_CHKTHIS(SfxObjectShell, 0);}
//STRIP001
//STRIP001  pImp->bSetStandardName=FALSE;
//STRIP001  USHORT nId = rReq.GetSlot();
//STRIP001  if ( !GetMedium() && nId != SID_CLOSEDOC )
//STRIP001     {
//STRIP001         rReq.Ignore();
//STRIP001      return;
//STRIP001     }
//STRIP001
//STRIP001  if( nId == SID_SAVEDOC || nId  == SID_UPDATEDOC )
//STRIP001  {
//STRIP001      // Embedded?
//STRIP001      SfxInPlaceObject *pObj=GetInPlaceObject();
//STRIP001      if( pObj && (
//STRIP001          pObj->GetProtocol().IsEmbed() ||
//STRIP001          GetCreateMode() == SFX_CREATE_MODE_EMBEDDED ))
//STRIP001      {
//STRIP001          BOOL bRet = pObj->GetClient()->SaveObject();
//STRIP001          rReq.SetReturnValue( SfxBoolItem(0, bRet) );
//STRIP001          rReq.Done();
//STRIP001          return;
//STRIP001      }
//STRIP001
//STRIP001         SFX_REQUEST_ARG( rReq, pVersionItem, SfxStringItem, SID_DOCINFO_COMMENTS, FALSE);
//STRIP001         if ( !IsModified() && !pVersionItem )
//STRIP001      {
//STRIP001          rReq.SetReturnValue( SfxBoolItem(0, FALSE) );
//STRIP001          rReq.Done();
//STRIP001          return;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001     SFX_REQUEST_ARG( rReq, pFileNameItem, SfxStringItem, SID_FILE_NAME, FALSE);
//STRIP001     SFX_REQUEST_ARG( rReq, pFilterItem, SfxStringItem, SID_FILTER_NAME, FALSE);
//STRIP001
//STRIP001     const SfxFilter *pCurFilter = GetMedium()->GetFilter();
//STRIP001  const SfxFilter *pDefFilter = GetFactory().GetFilter(0);
//STRIP001
//STRIP001     if ( nId == SID_SAVEDOC && pCurFilter && !pCurFilter->CanExport() && pDefFilter && pDefFilter->IsInternal() )
//STRIP001      nId = SID_SAVEASDOC;
//STRIP001
//STRIP001  // in case of saving an interaction handler can be required for authentication
//STRIP001  if ( nId == SID_SAVEDOC || nId == SID_SAVEASDOC || nId == SID_SAVEASURL || nId == SID_EXPORTDOC )
//STRIP001  {
//STRIP001      Reference< XInteractionHandler > xInteract;
//STRIP001      SFX_REQUEST_ARG( rReq, pxInteractionItem, SfxUnoAnyItem, SID_INTERACTIONHANDLER, sal_False );
//STRIP001
//STRIP001      DBG_ASSERT( !pxInteractionItem || ( ( pxInteractionItem->GetValue() >>= xInteract ) && xInteract.is() ),
//STRIP001                  "Broken InteractionHandler!\n" );
//STRIP001
//STRIP001      if ( !pxInteractionItem )
//STRIP001      {
//STRIP001          Reference< XMultiServiceFactory > xServiceManager = ::legacy_binfilters::getLegacyProcessServiceFactory();
//STRIP001          if( xServiceManager.is() )
//STRIP001          {
//STRIP001              xInteract = Reference< XInteractionHandler >(
//STRIP001                          xServiceManager->createInstance( DEFINE_CONST_UNICODE("com.sun.star.task.InteractionHandler") ),
//STRIP001                          UNO_QUERY );
//STRIP001
//STRIP001              rReq.AppendItem( SfxUnoAnyItem( SID_INTERACTIONHANDLER, makeAny( xInteract ) ) );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // interaktiv speichern via (nicht-Default) Filter?
//STRIP001     if ( !pFilterItem && GetMedium()->GetFilter() && HasName() && (nId == SID_SAVEDOC || nId == SID_UPDATEDOC) )
//STRIP001  {
//STRIP001      // aktuellen und Default-Filter besorgen
//STRIP001      // Filter kann nicht exportieren und Default-Filter ist verf"ugbar?
//STRIP001         if ( !pCurFilter->CanExport() && !pDefFilter->IsInternal() )
//STRIP001      {
//STRIP001          // fragen, ob im default-Format gespeichert werden soll
//STRIP001          String aWarn(SfxResId(STR_QUERY_MUSTOWNFORMAT));
//STRIP001          aWarn = SearchAndReplace( aWarn, DEFINE_CONST_UNICODE( "$(FORMAT)" ),
//STRIP001                         GetMedium()->GetFilter()->GetUIName() );
//STRIP001          aWarn = SearchAndReplace( aWarn, DEFINE_CONST_UNICODE( "$(OWNFORMAT)" ),
//STRIP001                         GetFactory().GetFilter(0)->GetUIName() );
//STRIP001          QueryBox aWarnBox(0,WB_OK_CANCEL|WB_DEF_OK,aWarn);
//STRIP001          if ( aWarnBox.Execute() == RET_OK )
//STRIP001          {
//STRIP001              // ja: Save-As in eigenem Foramt
//STRIP001              rReq.SetSlot(nId = SID_SAVEASDOC);
//STRIP001              pImp->bSetStandardName=TRUE;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              // nein: Abbruch
//STRIP001              rReq.Ignore();
//STRIP001              return;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // fremdes Format mit m"oglichem Verlust (aber nicht per API) wenn noch nicht gewarnt und anschließend im
//STRIP001          // alien format gespeichert wurde
//STRIP001             if ( !( pCurFilter->IsOwnFormat() && pCurFilter->GetVersion() == SOFFICE_FILEFORMAT_CURRENT || ( pCurFilter->GetFilterFlags() & SFX_FILTER_SILENTEXPORT ) )
//STRIP001                  && ( !pImp->bDidWarnFormat || !pImp->bDidDangerousSave ) )
//STRIP001          {
//STRIP001              // Default-Format verf"ugbar?
//STRIP001              if ( !pDefFilter->IsInternal() && pCurFilter != pDefFilter )
//STRIP001              {
//STRIP001                  // fragen, ob im default-Format gespeichert werden soll
//STRIP001                  String aWarn(SfxResId(STR_QUERY_SAVEOWNFORMAT));
//STRIP001                  aWarn = SearchAndReplace( aWarn, DEFINE_CONST_UNICODE( "$(FORMAT)" ),
//STRIP001                                 GetMedium()->GetFilter()->GetUIName());
//STRIP001                  aWarn = SearchAndReplace( aWarn, DEFINE_CONST_UNICODE( "$(OWNFORMAT)" ),
//STRIP001                                 GetFactory().GetFilter(0)->GetUIName());
//STRIP001
//STRIP001                  SfxViewFrame *pFrame = SfxObjectShell::Current() == this ?
//STRIP001                      SfxViewFrame::Current() : SfxViewFrame::GetFirst( this );
//STRIP001                  while ( pFrame && (pFrame->GetFrameType() & SFXFRAME_SERVER ) )
//STRIP001                      pFrame = SfxViewFrame::GetNext( *pFrame, this );
//STRIP001
//STRIP001                  if ( pFrame )
//STRIP001                  {
//STRIP001                         SfxFrame* pTop = pFrame->GetTopFrame();
//STRIP001                         SFX_APP()->SetViewFrame( pTop->GetCurrentViewFrame() );
//STRIP001                         pFrame->GetFrame()->Appear();
//STRIP001
//STRIP001                      QueryBox aWarnBox(&pFrame->GetWindow(),WB_YES_NO_CANCEL|WB_DEF_YES,aWarn);
//STRIP001                      switch(aWarnBox.Execute())
//STRIP001                      {
//STRIP001                          case RET_YES:
//STRIP001                          {
//STRIP001                              // ja: in Save-As umsetzen
//STRIP001                              rReq.SetSlot(nId = SID_SAVEASDOC);
//STRIP001                              SFX_ITEMSET_ARG( GetMedium()->GetItemSet(), pPassItem, SfxStringItem, SID_PASSWORD, FALSE );
//STRIP001                              if ( pPassItem )
//STRIP001                                  rReq.AppendItem( *pPassItem );
//STRIP001                              pImp->bSetStandardName = TRUE;
//STRIP001                              break;
//STRIP001                          }
//STRIP001
//STRIP001                          case RET_CANCEL:
//STRIP001                              // nein: Abbruch
//STRIP001                              rReq.Ignore();
//STRIP001                              return;
//STRIP001                      }
//STRIP001
//STRIP001                      pImp->bDidWarnFormat=TRUE;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Speichern eines namenslosen oder readonly Dokumentes
//STRIP001  BOOL bMediumRO = IsReadOnlyMedium();
//STRIP001
//STRIP001     if ( ( nId == SID_SAVEDOC || nId == SID_UPDATEDOC ) && ( !HasName() || bMediumRO ) )
//STRIP001  {
//STRIP001         if ( pFileNameItem )
//STRIP001      {
//STRIP001          // FALSE zur"uckliefern
//STRIP001          rReq.SetReturnValue( SfxBoolItem( 0, FALSE ) );
//STRIP001          rReq.Done();
//STRIP001          return;
//STRIP001      }
//STRIP001      else
//STRIP001         {
//STRIP001          // in SaveAs umwandlen
//STRIP001          rReq.SetSlot(nId = SID_SAVEASDOC);
//STRIP001             if ( SFX_APP()->IsPlugin() && !HasName() )
//STRIP001             {
//STRIP001                 SFX_REQUEST_ARG( rReq, pWarnItem, SfxBoolItem, SID_FAIL_ON_WARNING, FALSE);
//STRIP001                 if ( pWarnItem && pWarnItem->GetValue() == TRUE )
//STRIP001                 {
//STRIP001                     // saving done from PrepareClose without UI
//STRIP001                     INetURLObject aObj( SvtPathOptions().GetWorkPath() );
//STRIP001                     aObj.insertName( GetTitle(), false, INetURLObject::LAST_SEGMENT, true, INetURLObject::ENCODE_ALL );
//STRIP001                     const SfxFilter* pFilter = GetFactory().GetFilter(0);
//STRIP001                     String aExtension( pFilter->GetDefaultExtension().Copy(2) );
//STRIP001                     aObj.setExtension( aExtension, INetURLObject::LAST_SEGMENT, true, INetURLObject::ENCODE_ALL );
//STRIP001                     rReq.AppendItem( SfxStringItem( SID_FILE_NAME, aObj.GetMainURL( INetURLObject::NO_DECODE ) ) );
//STRIP001                     rReq.AppendItem( SfxBoolItem( SID_RENAME, TRUE ) );
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001  }
//STRIP001
//STRIP001  switch(nId)
//STRIP001  {
//STRIP001      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//STRIP001
//STRIP001         case SID_SAVE_VERSION_ON_CLOSE:
//STRIP001      {
//STRIP001             BOOL bSet = GetDocInfo().IsSaveVersionOnClose();
//STRIP001             SFX_REQUEST_ARG( rReq, pItem, SfxBoolItem, nId, FALSE);
//STRIP001             if ( pItem )
//STRIP001                 bSet = pItem->GetValue();
//STRIP001             GetDocInfo().SetSaveVersionOnClose( bSet );
//STRIP001             SetModified( TRUE );
//STRIP001             if ( !pItem )
//STRIP001                 rReq.AppendItem( SfxBoolItem( nId, bSet ) );
//STRIP001             rReq.Done();
//STRIP001             return;
//STRIP001             break;
//STRIP001         }
//STRIP001      case SID_VERSION:
//STRIP001      {
//STRIP001          SfxViewFrame* pFrame = GetFrame();
//STRIP001          if ( !pFrame )
//STRIP001              pFrame = SfxViewFrame::GetFirst( this );
//STRIP001          if ( !pFrame )
//STRIP001              return;
//STRIP001
//STRIP001             if ( pFrame->GetFrame()->GetParentFrame() )
//STRIP001             {
//STRIP001                 pFrame->GetTopViewFrame()->GetObjectShell()->ExecuteSlot( rReq );
//STRIP001                 return;
//STRIP001             }
//STRIP001
//STRIP001          if ( !IsOwnStorageFormat_Impl( *GetMedium() ) )
//STRIP001              return;
//STRIP001
//STRIP001          SfxVersionDialog *pDlg = new SfxVersionDialog( pFrame, NULL );
//STRIP001          pDlg->Execute();
//STRIP001          delete pDlg;
//STRIP001             return;
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      case SID_LOAD_LIBRARY:
//STRIP001      case SID_UNLOAD_LIBRARY:
//STRIP001      case SID_REMOVE_LIBRARY:
//STRIP001      case SID_ADD_LIBRARY:
//STRIP001      {
//STRIP001          // Diese Funktionen sind nur f"ur Aufrufe aus dem Basic gedacht
//STRIP001          SfxApplication *pApp = SFX_APP();
//STRIP001          if ( pApp->IsInBasicCall() )
//STRIP001              pApp->BasicLibExec_Impl( rReq, GetBasicManager() );
//STRIP001             return;
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      case SID_SAVEDOC:
//STRIP001      {
//STRIP001          //!! detaillierte Auswertung eines Fehlercodes
//STRIP001          SfxObjectShellRef xLock( this );
//STRIP001          SfxErrorContext aEc(ERRCTX_SFX_SAVEDOC,GetTitle());
//STRIP001          SFX_APP()->NotifyEvent(SfxEventHint(SFX_EVENT_SAVEDOC,this));
//STRIP001
//STRIP001             BOOL bOk = Save_Impl( rReq.GetArgs() );
//STRIP001
//STRIP001          ULONG lErr=GetErrorCode();
//STRIP001             if( !lErr && !bOk )
//STRIP001              lErr=ERRCODE_IO_GENERAL;
//STRIP001
//STRIP001             if ( lErr && bOk )
//STRIP001             {
//STRIP001                 SFX_REQUEST_ARG( rReq, pWarnItem, SfxBoolItem, SID_FAIL_ON_WARNING, FALSE);
//STRIP001                 if ( pWarnItem && pWarnItem->GetValue() )
//STRIP001                     bOk = FALSE;
//STRIP001             }
//STRIP001
//STRIP001             if( !ErrorHandler::HandleError( lErr ) )
//STRIP001                 SFX_APP()->NotifyEvent( SfxEventHint( SFX_EVENT_SAVEFINISHED, this ) );
//STRIP001          ResetError();
//STRIP001
//STRIP001          rReq.SetReturnValue( SfxBoolItem(0, bOk) );
//STRIP001          if ( bOk )
//STRIP001              SFX_APP()->NotifyEvent(SfxEventHint(SFX_EVENT_SAVEDOCDONE,this));
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//STRIP001      case SID_UPDATEDOC:
//STRIP001      {
//STRIP001          return;
//STRIP001      }
//STRIP001
//STRIP001      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//STRIP001      case SID_DOCINFO:
//STRIP001      {
//STRIP001          SFX_REQUEST_ARG(rReq, pDocInfItem, SfxDocumentInfoItem, SID_DOCINFO, FALSE);
//STRIP001
//STRIP001          // keine Parameter vorhanden?
//STRIP001          if ( !pDocInfItem )
//STRIP001          {
//STRIP001              // Dialog ausf"uhren
//STRIP001              SfxDocumentInfo *pOldInfo = new SfxDocumentInfo;
//STRIP001              if ( pImp->pDocInfo )
//STRIP001                  // r/o-flag korrigieren falls es zu frueh gesetzt wurde
//STRIP001                  pImp->pDocInfo->SetReadOnly( IsReadOnly() );
//STRIP001                 *pOldInfo = GetDocInfo();
//STRIP001                 DocInfoDlg_Impl( GetDocInfo() );
//STRIP001
//STRIP001              // ge"andert?
//STRIP001                 if( !(*pOldInfo == GetDocInfo()) )
//STRIP001              {
//STRIP001                  // Dokument gilt als ver"andert
//STRIP001                     FlushDocInfo();
//STRIP001
//STRIP001                     // ggf. Recorden
//STRIP001                     if ( !rReq.IsRecording() )
//STRIP001                         rReq.AppendItem( SfxDocumentInfoItem( GetTitle(), GetDocInfo() ) );
//STRIP001                     rReq.Done();
//STRIP001              }
//STRIP001                 else
//STRIP001                     rReq.Ignore();
//STRIP001
//STRIP001                 delete pOldInfo;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              // DocInfo aus Parameter anwenden
//STRIP001              GetDocInfo() = (*pDocInfItem)();
//STRIP001                 FlushDocInfo();
//STRIP001          }
//STRIP001
//STRIP001          return;
//STRIP001         }
//STRIP001
//STRIP001      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//STRIP001
//STRIP001      case SID_EXPORTDOC:
//STRIP001      case SID_EXPORTDOCASPDF:
//STRIP001      case SID_DIRECTEXPORTDOCASPDF:
//STRIP001          rReq.AppendItem( SfxBoolItem( SID_SAVETO, sal_True ) );
//STRIP001          // another part is pretty the same as for SID_SAVEASDOC
//STRIP001      case SID_SAVEASURL:
//STRIP001      case SID_SAVEASDOC:
//STRIP001      {
//STRIP001          //!! detaillierte Auswertung eines Fehlercodes
//STRIP001          SfxObjectShellRef xLock( this );
//STRIP001
//STRIP001          // Bei Calls "uber StarOne OverWrite-Status checken
//STRIP001          SFX_REQUEST_ARG( rReq, pOverwriteItem, SfxBoolItem, SID_OVERWRITE, FALSE );
//STRIP001          if ( pOverwriteItem )
//STRIP001          {
//STRIP001                 // because there is no "exist" function, the overwrite handling is done in the SfxMedium
//STRIP001              SFX_REQUEST_ARG( rReq, pItem, SfxStringItem, SID_FILE_NAME, FALSE );
//STRIP001                 if ( !pItem )
//STRIP001                  // In diesem Falle mu\s ein Dateiname mitkommen
//STRIP001                  SetError( ERRCODE_IO_INVALIDPARAMETER );
//STRIP001          }
//STRIP001
//STRIP001          BOOL bOk = GUISaveAs_Impl(nId == SID_SAVEASURL, &rReq);
//STRIP001          ULONG lErr=GetErrorCode();
//STRIP001          if ( !lErr && !bOk )
//STRIP001              lErr=ERRCODE_IO_GENERAL;
//STRIP001
//STRIP001             if ( lErr && bOk )
//STRIP001             {
//STRIP001                 SFX_REQUEST_ARG( rReq, pWarnItem, SfxBoolItem, SID_FAIL_ON_WARNING, FALSE );
//STRIP001                 if ( pWarnItem && pWarnItem->GetValue() )
//STRIP001                     bOk = FALSE;
//STRIP001             }
//STRIP001
//STRIP001          if ( lErr!=ERRCODE_IO_ABORT )
//STRIP001          {
//STRIP001              SfxErrorContext aEc(ERRCTX_SFX_SAVEASDOC,GetTitle());
//STRIP001                 ErrorHandler::HandleError(lErr);
//STRIP001          }
//STRIP001
//STRIP001          if ( nId == SID_EXPORTDOCASPDF )
//STRIP001          {
//STRIP001              // This function is used by the SendMail function that needs information if a export
//STRIP001              // file was written or not. This could be due to cancellation of the export
//STRIP001              // or due to an error. So IO abort must be handled like an error!
//STRIP001              bOk = ( lErr != ERRCODE_IO_ABORT ) & bOk;
//STRIP001          }
//STRIP001
//STRIP001          rReq.SetReturnValue( SfxBoolItem(0, bOk) );
//STRIP001
//STRIP001          ResetError();
//STRIP001
//STRIP001          Invalidate();
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//STRIP001
//STRIP001      case SID_CLOSEDOC:
//STRIP001      {
//STRIP001          SfxViewFrame *pFrame = GetFrame();
//STRIP001          if ( pFrame && pFrame->GetFrame()->GetParentFrame() )
//STRIP001          {
//STRIP001              // Wenn SID_CLOSEDOC "uber Menue etc. ausgef"uhrt wird, das
//STRIP001              // aktuelle Dokument aber in einem Frame liegt, soll eigentlich
//STRIP001              // das FrameSetDocument geclosed werden
//STRIP001              pFrame->GetTopViewFrame()->GetObjectShell()->ExecuteSlot( rReq );
//STRIP001                 rReq.Done();
//STRIP001              return;
//STRIP001          }
//STRIP001
//STRIP001          BOOL bInFrameSet = FALSE;
//STRIP001          USHORT nFrames=0;
//STRIP001          pFrame = SfxViewFrame::GetFirst( this );
//STRIP001          while ( pFrame )
//STRIP001          {
//STRIP001              if ( pFrame->GetFrame()->GetParentFrame() )
//STRIP001              {
//STRIP001                  // Auf dieses Dokument existiert noch eine Sicht, die
//STRIP001                  // in einem FrameSet liegt; diese darf nat"urlich nicht
//STRIP001                  // geclosed werden
//STRIP001                  bInFrameSet = TRUE;
//STRIP001              }
//STRIP001              else
//STRIP001                  nFrames++;
//STRIP001
//STRIP001              pFrame = SfxViewFrame::GetNext( *pFrame, this );
//STRIP001          }
//STRIP001
//STRIP001          if ( bInFrameSet )
//STRIP001          {
//STRIP001              // Alle Sichten, die nicht in einem FrameSet liegen, closen
//STRIP001              pFrame = SfxViewFrame::GetFirst( this );
//STRIP001              while ( pFrame )
//STRIP001              {
//STRIP001                  if ( !pFrame->GetFrame()->GetParentFrame() )
//STRIP001                      pFrame->GetFrame()->DoClose();
//STRIP001                  pFrame = SfxViewFrame::GetNext( *pFrame, this );
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          // Parameter auswerten
//STRIP001          SFX_REQUEST_ARG(rReq, pSaveItem, SfxBoolItem, SID_CLOSEDOC_SAVE, FALSE);
//STRIP001          SFX_REQUEST_ARG(rReq, pNameItem, SfxStringItem, SID_CLOSEDOC_FILENAME, FALSE);
//STRIP001          if ( pSaveItem )
//STRIP001          {
//STRIP001              if ( pSaveItem->GetValue() )
//STRIP001              {
//STRIP001                  if ( !pNameItem )
//STRIP001                  {
//STRIP001                      SbxBase::SetError( SbxERR_WRONG_ARGS );
//STRIP001                      rReq.Ignore();
//STRIP001                      return;
//STRIP001                  }
//STRIP001                  SfxAllItemSet aArgs( GetPool() );
//STRIP001                  SfxStringItem aTmpItem( SID_FILE_NAME, pNameItem->GetValue() );
//STRIP001                  aArgs.Put( aTmpItem, aTmpItem.Which() );
//STRIP001                  SfxRequest aSaveAsReq( SID_SAVEASDOC, SFX_CALLMODE_API, aArgs );
//STRIP001                  ExecFile_Impl( aSaveAsReq );
//STRIP001                  if ( !aSaveAsReq.IsDone() )
//STRIP001                  {
//STRIP001                      rReq.Ignore();
//STRIP001                      return;
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001                  SetModified(FALSE);
//STRIP001          }
//STRIP001
//STRIP001          // Benutzer bricht ab?
//STRIP001             if ( !PrepareClose( 2 ) )
//STRIP001          {
//STRIP001              rReq.SetReturnValue( SfxBoolItem(0, FALSE) );
//STRIP001              rReq.Done();
//STRIP001              return;
//STRIP001          }
//STRIP001
//STRIP001             SetModified( FALSE );
//STRIP001             ULONG lErr = GetErrorCode();
//STRIP001          ErrorHandler::HandleError(lErr);
//STRIP001
//STRIP001          rReq.SetReturnValue( SfxBoolItem(0, TRUE) );
//STRIP001          rReq.Done();
//STRIP001          rReq.ReleaseArgs(); // da der Pool in Close zerst"ort wird
//STRIP001
//STRIP001             if ( SfxApplication::IsPlugin() )
//STRIP001             {
//STRIP001                 for ( SfxViewFrame* pFrame = SfxViewFrame::GetFirst( this ); pFrame; pFrame = SfxViewFrame::GetNext( *pFrame, this ) )
//STRIP001                 {
//STRIP001                     String aName = String::CreateFromAscii("vnd.sun.star.cmd:close");
//STRIP001                     SfxStringItem aNameItem( SID_FILE_NAME, aName );
//STRIP001                     SfxStringItem aReferer( SID_REFERER, DEFINE_CONST_UNICODE( "private/user" ) );
//STRIP001                     SfxFrameItem aFrame( SID_DOCFRAME, pFrame->GetFrame() );
//STRIP001                     SFX_APP()->GetAppDispatcher_Impl()->Execute( SID_OPENDOC, SFX_CALLMODE_SLOT, &aNameItem, &aReferer, 0L );
//STRIP001                     return;
//STRIP001                 }
//STRIP001             }
//STRIP001 /*
//STRIP001          ::com::sun::star::uno::Reference < ::com::sun::star::frame::XFramesSupplier >
//STRIP001                  xDesktop( ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.frame.Desktop")) ),
//STRIP001                  ::com::sun::star::uno::UNO_QUERY );
//STRIP001          ::com::sun::star::uno::Reference < ::com::sun::star::container::XIndexAccess > xList ( xDesktop->getFrames(), ::com::sun::star::uno::UNO_QUERY );
//STRIP001          sal_Int32 nCount = xList->getCount();
//STRIP001          if ( nCount == nFrames )
//STRIP001          {
//STRIP001                 SfxViewFrame* pFrame = SfxViewFrame::GetFirst( this );
//STRIP001              SfxViewFrame* pLastFrame = SfxViewFrame::Current();
//STRIP001              if ( pLastFrame->GetObjectShell() != this )
//STRIP001                  pLastFrame = pFrame;
//STRIP001
//STRIP001              SfxViewFrame* pNextFrame = pFrame;
//STRIP001              while ( pNextFrame )
//STRIP001              {
//STRIP001                  pNextFrame = SfxViewFrame::GetNext( *pFrame, this );
//STRIP001                  if ( pFrame != pLastFrame )
//STRIP001                      pFrame->GetFrame()->DoClose();
//STRIP001                  pFrame = pNextFrame;
//STRIP001              }
//STRIP001
//STRIP001              pLastFrame->GetFrame()->CloseDocument_Impl();
//STRIP001          }
//STRIP001          else
//STRIP001  */
//STRIP001              DoClose();
//STRIP001          return;
//STRIP001      }
//STRIP001
//STRIP001      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//STRIP001      case SID_DOCTEMPLATE:
//STRIP001      {
//STRIP001          // speichern als Dokumentvorlagen
//STRIP001          SfxDocumentTemplateDlg *pDlg = 0;
//STRIP001          SfxErrorContext aEc(ERRCTX_SFX_DOCTEMPLATE,GetTitle());
//STRIP001          SfxDocumentTemplates *pTemplates =  new SfxDocumentTemplates;
//STRIP001
//STRIP001          // Find the template filter with the highest version number
//STRIP001          const SfxFilter* pFilter=NULL;
//STRIP001          const SfxObjectFactory& rFactory = GetFactory();
//STRIP001          USHORT  nFilterCount = rFactory.GetFilterCount();
//STRIP001          ULONG   nVersion = 0;
//STRIP001          int n;
//STRIP001          for( n=0; n<nFilterCount; n++)
//STRIP001          {
//STRIP001              const SfxFilter* pTemp = rFactory.GetFilter( n );
//STRIP001              if( pTemp && pTemp->IsOwnFormat() &&
//STRIP001                  pTemp->IsOwnTemplateFormat() &&
//STRIP001                  ( pTemp->GetVersion() > nVersion ) )
//STRIP001              {
//STRIP001                  pFilter = pTemp;
//STRIP001                  nVersion = pTemp->GetVersion();
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001             DBG_ASSERT( pFilter, "Template Filter nicht gefunden" );
//STRIP001          if( !pFilter )
//STRIP001              pFilter = rFactory.GetFilter(0);
//STRIP001
//STRIP001          if ( !rReq.GetArgs() )
//STRIP001          {
//STRIP001              pDlg = new SfxDocumentTemplateDlg(0, pTemplates);
//STRIP001              if ( RET_OK == pDlg->Execute() && pDlg->GetTemplateName().Len())
//STRIP001              {
//STRIP001                  String aTargetURL = pTemplates->GetTemplatePath(
//STRIP001                          pDlg->GetRegion(),
//STRIP001                          pDlg->GetTemplateName());
//STRIP001
//STRIP001                  if ( aTargetURL.Len() )
//STRIP001                  {
//STRIP001                      INetURLObject aTargetObj( aTargetURL );
//STRIP001                      String aTplExtension( pFilter->GetDefaultExtension().Copy(2) );
//STRIP001                      aTargetObj.setExtension( aTplExtension );
//STRIP001                      aTargetURL = aTargetObj.GetMainURL( INetURLObject::NO_DECODE );
//STRIP001                  }
//STRIP001
//STRIP001                  rReq.AppendItem( SfxStringItem( SID_FILE_NAME, aTargetURL ) );
//STRIP001
//STRIP001                  rReq.AppendItem(SfxStringItem(
//STRIP001                      SID_TEMPLATE_NAME, pDlg->GetTemplateName()));
//STRIP001                  rReq.AppendItem(SfxUInt16Item(
//STRIP001                      SID_TEMPLATE_REGION, pDlg->GetRegion()));
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  delete pDlg;
//STRIP001                  rReq.Ignore();
//STRIP001                  return;
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          // Region und Name aus Parameter holen
//STRIP001          SFX_REQUEST_ARG(rReq, pRegionItem, SfxStringItem, SID_TEMPLATE_REGIONNAME, FALSE);
//STRIP001          SFX_REQUEST_ARG(rReq, pNameItem, SfxStringItem, SID_TEMPLATE_NAME, FALSE);
//STRIP001          SFX_REQUEST_ARG(rReq, pRegionNrItem, SfxUInt16Item, SID_TEMPLATE_REGION, FALSE);
//STRIP001          if ( (!pRegionItem && !pRegionNrItem ) || !pNameItem )
//STRIP001          {
//STRIP001              DBG_ASSERT( rReq.IsAPI(), "non-API call without Arguments" );
//STRIP001              SbxBase::SetError( SbxERR_WRONG_ARGS );
//STRIP001              rReq.Ignore();
//STRIP001              return;
//STRIP001          }
//STRIP001          String aTemplateName = pNameItem->GetValue();
//STRIP001
//STRIP001          // Region-Nr besorgen
//STRIP001          USHORT nRegion;
//STRIP001          if( pRegionItem )
//STRIP001          {
//STRIP001              // Region-Name finden (eigentlich nicht unbedingt eindeutig)
//STRIP001              nRegion = pTemplates->GetRegionNo( pRegionItem->GetValue() );
//STRIP001              if ( nRegion == USHRT_MAX )
//STRIP001              {
//STRIP001                  SbxBase::SetError( ERRCODE_IO_INVALIDPARAMETER );
//STRIP001                  rReq.Ignore();
//STRIP001                  return;
//STRIP001              }
//STRIP001          }
//STRIP001          if ( pRegionNrItem )
//STRIP001              nRegion = pRegionNrItem->GetValue();
//STRIP001
//STRIP001          // kein File-Name angegeben?
//STRIP001          if ( SFX_ITEM_SET != rReq.GetArgs()->GetItemState( SID_FILE_NAME ) )
//STRIP001          {
//STRIP001              // TemplatePath nicht angebgeben => aus Region+Name ermitteln
//STRIP001              // Dateiname zusammenbauen lassen
//STRIP001              String aTemplPath = pTemplates->GetTemplatePath( nRegion, aTemplateName );
//STRIP001              INetURLObject aURLObj( aTemplPath );
//STRIP001                 String aExtension( pFilter->GetDefaultExtension().Copy(2) );
//STRIP001                 aURLObj.setExtension( aExtension, INetURLObject::LAST_SEGMENT, true, INetURLObject::ENCODE_ALL );
//STRIP001
//STRIP001                 rReq.AppendItem( SfxStringItem( SID_FILE_NAME, aURLObj.GetMainURL( INetURLObject::NO_DECODE ) ) );
//STRIP001          }
//STRIP001
//STRIP001          // Dateiname
//STRIP001          SFX_REQUEST_ARG(rReq, pFileItem, SfxStringItem, SID_FILE_NAME, FALSE);
//STRIP001          const String aFileName(((const SfxStringItem *)pFileItem)->GetValue());
//STRIP001
//STRIP001          // Medium zusammenbauen
//STRIP001          SfxItemSet* pSet = new SfxAllItemSet( *rReq.GetArgs() );
//STRIP001             SfxMedium aMedium( aFileName, STREAM_STD_READWRITE, FALSE, pFilter, pSet);
//STRIP001
//STRIP001          // als Vorlage speichern
//STRIP001          BOOL bModified = IsModified();
//STRIP001          BOOL bHasTemplateConfig = HasTemplateConfig();
//STRIP001          SetTemplateConfig( FALSE );
//STRIP001          BOOL bOK = FALSE;
//STRIP001          const String aOldURL( INetURLObject::GetBaseURL() );
//STRIP001          if( ShallSetBaseURL_Impl( aMedium ) )
//STRIP001              INetURLObject::SetBaseURL( aMedium.GetBaseURL() );
//STRIP001          else
//STRIP001              INetURLObject::SetBaseURL( String() );
//STRIP001
//STRIP001             aMedium.CreateTempFileNoCopy();
//STRIP001
//STRIP001             // Because we can't save into a storage directly ( only using tempfile ), we must save the DocInfo first, then
//STRIP001             // we can call SaveTo_Impl and Commit
//STRIP001             if ( pFilter->UsesStorage() && ( pFilter->GetVersion() < SOFFICE_FILEFORMAT_60 ) )
//STRIP001             {
//STRIP001                 SfxDocumentInfo *pInfo = new SfxDocumentInfo;
//STRIP001                 pInfo->CopyUserData(GetDocInfo());
//STRIP001                 pInfo->SetTitle( aTemplateName );
//STRIP001                 pInfo->SetChanged( SfxStamp(SvtUserOptions().GetFullName()));
//STRIP001                 SvStorageRef aRef = aMedium.GetStorage();
//STRIP001                 if ( aRef.Is() )
//STRIP001                 {
//STRIP001                     pInfo->SetTime(0L);
//STRIP001                     pInfo->Save(aRef);
//STRIP001                 }
//STRIP001
//STRIP001                 delete pInfo;
//STRIP001             }
//STRIP001
//STRIP001             if ( SaveTo_Impl(aMedium,NULL,FALSE) )
//STRIP001          {
//STRIP001              bOK = TRUE;
//STRIP001              pTemplates->NewTemplate( nRegion, aTemplateName, aFileName );
//STRIP001          }
//STRIP001
//STRIP001          INetURLObject::SetBaseURL( aOldURL );
//STRIP001
//STRIP001          DELETEX(pDlg);
//STRIP001
//STRIP001          SetError(aMedium.GetErrorCode());
//STRIP001          ULONG lErr=GetErrorCode();
//STRIP001          if(!lErr && !bOK)
//STRIP001              lErr=ERRCODE_IO_GENERAL;
//STRIP001          ErrorHandler::HandleError(lErr);
//STRIP001          ResetError();
//STRIP001          delete pTemplates;
//STRIP001
//STRIP001          if ( IsHandsOff() )
//STRIP001          {
//STRIP001              if ( !DoSaveCompleted( pMedium ) )
//STRIP001                  DBG_ERROR("Case not handled - no way to get a storage!");
//STRIP001          }
//STRIP001          else
//STRIP001              DoSaveCompleted();
//STRIP001
//STRIP001          SetTemplateConfig( bHasTemplateConfig );
//STRIP001          SetModified(bModified);
//STRIP001          rReq.SetReturnValue( SfxBoolItem( 0, bOK ) );
//STRIP001          if ( !bOK )
//STRIP001              return;
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Picklisten-Eintrag verhindern
//STRIP001  if ( rReq.IsAPI() )
//STRIP001      GetMedium()->SetUpdatePickList( FALSE );
//STRIP001  else if ( rReq.GetArgs() )
//STRIP001  {
//STRIP001      SFX_ITEMSET_GET( *rReq.GetArgs(), pPicklistItem, SfxBoolItem, SID_PICKLIST, FALSE );
//STRIP001      if ( pPicklistItem )
//STRIP001          GetMedium()->SetUpdatePickList( pPicklistItem->GetValue() );
//STRIP001  }
//STRIP001
//STRIP001  // Ignore()-Zweige haben schon returnt
//STRIP001  rReq.Done();
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
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  switch ( rReq.GetSlot() )
//STRIP001  {
//STRIP001      case SID_MODIFIED:
//STRIP001      {
//STRIP001          SetModified( ( (SfxBoolItem&) rReq.GetArgs()->Get(SID_MODIFIED)).GetValue() );
//STRIP001          rReq.Done();
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      case SID_DOCTITLE:
//STRIP001          SetTitle( ( (SfxStringItem&) rReq.GetArgs()->Get(SID_DOCTITLE)).GetValue() );
//STRIP001          rReq.Done();
//STRIP001          break;
//STRIP001
//STRIP001      case SID_ON_CREATEDOC:
//STRIP001      case SID_ON_OPENDOC:
//STRIP001      case SID_ON_PREPARECLOSEDOC:
//STRIP001      case SID_ON_CLOSEDOC:
//STRIP001      case SID_ON_SAVEDOC:
//STRIP001      case SID_ON_SAVEASDOC:
//STRIP001      case SID_ON_ACTIVATEDOC:
//STRIP001      case SID_ON_DEACTIVATEDOC:
//STRIP001      case SID_ON_PRINTDOC:
//STRIP001      case SID_ON_SAVEDOCDONE:
//STRIP001      case SID_ON_SAVEASDOCDONE:
//STRIP001          SFX_APP()->EventExec_Impl( rReq, this );
//STRIP001          break;
//STRIP001
//STRIP001      // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//STRIP001      case SID_PLAYMACRO:
//STRIP001      {
//STRIP001          SFX_APP()->PlayMacro_Impl( rReq, GetBasic() );
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      case SID_DOCINFO_AUTHOR :
//STRIP001      {
//STRIP001          String aStr = ( (SfxStringItem&)rReq.GetArgs()->Get(rReq.GetSlot())).GetValue();
//STRIP001          SfxStamp aStamp( GetDocInfo().GetCreated() );
//STRIP001          aStamp.SetName( aStr );
//STRIP001          GetDocInfo().SetCreated( aStamp );
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      case SID_DOCINFO_COMMENTS :
//STRIP001      {
//STRIP001          String aStr = ( (SfxStringItem&)rReq.GetArgs()->Get(rReq.GetSlot())).GetValue();
//STRIP001          GetDocInfo().SetComment( aStr );
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      case SID_DOCINFO_KEYWORDS :
//STRIP001      {
//STRIP001          String aStr = ( (SfxStringItem&)rReq.GetArgs()->Get(rReq.GetSlot())).GetValue();
//STRIP001          GetDocInfo().SetKeywords( aStr );
//STRIP001          break;
//STRIP001      }
//STRIP001  }
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectShell::StateProps_Impl(SfxItemSet &rSet)
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  SfxWhichIter aIter(rSet);
//STRIP001  for ( USHORT nSID = aIter.FirstWhich(); nSID; nSID = aIter.NextWhich() )
//STRIP001  {
//STRIP001      switch ( nSID )
//STRIP001      {
//STRIP001          case SID_DOCINFO_AUTHOR :
//STRIP001          {
//STRIP001              String aStr = GetDocInfo().GetCreated().GetName();
//STRIP001              rSet.Put( SfxStringItem( nSID, aStr ) );
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001          case SID_DOCINFO_COMMENTS :
//STRIP001          {
//STRIP001              String aStr = GetDocInfo().GetComment();
//STRIP001              rSet.Put( SfxStringItem( nSID, aStr ) );
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001          case SID_DOCINFO_KEYWORDS :
//STRIP001          {
//STRIP001              String aStr = GetDocInfo().GetKeywords();
//STRIP001              rSet.Put( SfxStringItem( nSID, aStr ) );
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001          case SID_DOCPATH:
//STRIP001          {
//STRIP001                 DBG_ERROR( "Not supported anymore!" );
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001          case SID_DOCFULLNAME:
//STRIP001          {
//STRIP001              rSet.Put( SfxStringItem( SID_DOCFULLNAME, GetTitle(SFX_TITLE_FULLNAME) ) );
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001          case SID_DOCTITLE:
//STRIP001          {
//STRIP001              rSet.Put( SfxStringItem( SID_DOCTITLE, GetTitle() ) );
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001          case SID_DOC_READONLY:
//STRIP001          {
//STRIP001              rSet.Put( SfxBoolItem( SID_DOC_READONLY, IsReadOnly() ) );
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001          case SID_DOC_SAVED:
//STRIP001          {
//STRIP001              rSet.Put( SfxBoolItem( SID_DOC_SAVED, !IsModified() ) );
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001          case SID_CLOSING:
//STRIP001          {
//STRIP001              rSet.Put( SfxBoolItem( SID_CLOSING, Get_Impl()->bInCloseEvent ) );
//STRIP001              break;
//STRIP001          }
//STRIP001
//STRIP001          case SID_ON_CREATEDOC:
//STRIP001          case SID_ON_OPENDOC:
//STRIP001          case SID_ON_PREPARECLOSEDOC:
//STRIP001          case SID_ON_CLOSEDOC:
//STRIP001          case SID_ON_SAVEDOC:
//STRIP001          case SID_ON_SAVEASDOC:
//STRIP001          case SID_ON_ACTIVATEDOC:
//STRIP001          case SID_ON_DEACTIVATEDOC:
//STRIP001          case SID_ON_PRINTDOC:
//STRIP001          case SID_ON_SAVEDOCDONE:
//STRIP001          case SID_ON_SAVEASDOCDONE:
//STRIP001              SFX_APP()->EventState_Impl( nSID, rSet, this );
//STRIP001              break;
//STRIP001
//STRIP001          case SID_DOC_LOADING:
//STRIP001              rSet.Put( SfxBoolItem( nSID, SFX_LOADED_MAINDOCUMENT !=
//STRIP001                          ( pImp->nLoadedFlags & SFX_LOADED_MAINDOCUMENT ) ) );
//STRIP001              break;
//STRIP001
//STRIP001          case SID_IMG_LOADING:
//STRIP001              rSet.Put( SfxBoolItem( nSID, SFX_LOADED_IMAGES !=
//STRIP001                          ( pImp->nLoadedFlags & SFX_LOADED_IMAGES ) ) );
//STRIP001              break;
//STRIP001      }
//STRIP001  }
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectShell::ExecView_Impl(SfxRequest &rReq)
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  switch ( rReq.GetSlot() )
//STRIP001  {
//STRIP001      case SID_ACTIVATE:
//STRIP001      {
//STRIP001          SfxViewFrame *pFrame =
//STRIP001                  SfxViewFrame::GetFirst( this, TYPE(SfxTopViewFrame), TRUE );
//STRIP001          if ( pFrame )
//STRIP001              pFrame->GetFrame()->Appear();
//STRIP001          rReq.SetReturnValue( SfxObjectItem( 0, pFrame ) );
//STRIP001          rReq.Done();
//STRIP001          break;
//STRIP001      }
//STRIP001      case SID_NEWWINDOWFOREDIT:
//STRIP001      {
//STRIP001          SfxViewFrame* pFrame = SfxViewFrame::Current();
//STRIP001          if( pFrame->GetObjectShell() == this &&
//STRIP001              ( pFrame->GetFrameType() & SFXFRAME_HASTITLE ) )
//STRIP001              pFrame->ExecuteSlot( rReq );
//STRIP001          else
//STRIP001          {
//STRIP001              String aFileName( GetObjectShell()->GetMedium()->GetName() );
//STRIP001              if ( aFileName.Len() )
//STRIP001              {
//STRIP001                  SfxStringItem aName( SID_FILE_NAME, aFileName );
//STRIP001                  SfxBoolItem aCreateView( SID_OPEN_NEW_VIEW, TRUE );
//STRIP001                     SFX_APP()->GetAppDispatcher_Impl()->Execute(
//STRIP001                      SID_OPENDOC, SFX_CALLMODE_ASYNCHRON, &aName,
//STRIP001                      &aCreateView, 0L);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectShell::StateView_Impl(SfxItemSet &rSet)
/*N*/ {
/*N*/ }

}
