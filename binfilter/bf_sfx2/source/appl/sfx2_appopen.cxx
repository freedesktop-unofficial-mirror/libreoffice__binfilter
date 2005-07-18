/*************************************************************************
 *
 *  $RCSfile: sfx2_appopen.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: obo $ $Date: 2005-07-18 11:48:34 $
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

#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
#include <com/sun/star/uno/Reference.h>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_FRAMESEARCHFLAG_HPP_
#include <com/sun/star/frame/FrameSearchFlag.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XCOMPONENTLOADER_HPP_
#include <com/sun/star/frame/XComponentLoader.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XNOTIFYINGDISPATCH_HPP_
#include <com/sun/star/frame/XNotifyingDispatch.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XDISPATCHPROVIDER_HPP_
#include <com/sun/star/frame/XDispatchProvider.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XFRAME_HPP_
#include <com/sun/star/frame/XFrame.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_DISPATCHRESULTSTATE_HPP_
#include <com/sun/star/frame/DispatchResultState.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XDISPATCHRESULTLISTENER_HPP_
#include <com/sun/star/frame/XDispatchResultListener.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_URL_HPP_
#include <com/sun/star/util/URL.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XURLTRANSFORMER_HPP_
#include <com/sun/star/util/XURLTransformer.hpp>
#endif
#ifndef _COM_SUN_STAR_SYSTEM_XSYSTEMSHELLEXECUTE_HPP_
#include <com/sun/star/system/XSystemShellExecute.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_XTYPEDETECTION_HPP_
#include <com/sun/star/document/XTypeDetection.hpp>
#endif
#ifndef _COM_SUN_STAR_SYSTEM_SYSTEMSHELLEXECUTEFLAGS_HPP_
#include <com/sun/star/system/SystemShellExecuteFlags.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_MACROEXECMODE_HPP_
#include <com/sun/star/document/MacroExecMode.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_UPDATEDOCMODE_HPP_
#include <com/sun/star/document/UpdateDocMode.hpp>
#endif
#ifndef _COM_SUN_STAR_TASK_XINTERACTIONREQUEST_HPP_
#include <com/sun/star/task/XInteractionRequest.hpp>
#endif

#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif
#ifndef _CPPUHELPER_IMPLBASE1_HXX_
#include <cppuhelper/implbase1.hxx>
#endif

#ifndef _SV_WRKWIN_HXX
#include <vcl/wrkwin.hxx>
#endif
#ifndef _SFXINTITEM_HXX //autogen
#include <svtools/intitem.hxx>
#endif
#ifndef _SV_MSGBOX_HXX
#include <vcl/msgbox.hxx>
#endif
#ifndef _SFXSTRITEM_HXX //autogen
#include <svtools/stritem.hxx>
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#ifndef _SVSTOR_HXX //autogen
#include <so3/svstor.hxx>
#endif
#ifndef _SFXDOCTEMPL_HXX //autogen
#include <doctempl.hxx>
#endif
// STRIP001 #ifndef _EXTATTR_HXX
// STRIP001 #include <svtools/extattr.hxx>
// STRIP001 #endif
#ifndef _SFXECODE_HXX
#include <svtools/sfxecode.hxx>
#endif

#include <svtools/ehdl.hxx>
#include <basic/sbxobj.hxx>
#include <svtools/urihelper.hxx>
#include <unotools/localfilehelper.hxx>

#ifndef INCLUDED_SVTOOLS_PATHOPTIONS_HXX
#include <svtools/pathoptions.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_MODULEOPTIONS_HXX
#include <svtools/moduleoptions.hxx>
#endif
#ifndef _SVTOOLS_TEMPLDLG_HXX
#include <svtools/templdlg.hxx>
#endif
#ifndef _OSL_FILE_HXX_
#include <osl/file.hxx>
#endif
#include <svtools/extendedsecurityoptions.hxx>
#include <svtools/docpasswdrequest.hxx>

#pragma hdrstop

#include "app.hxx"
#include "appdata.hxx"
#include "bindings.hxx"
#include "cfgmgr.hxx"
#include "dispatch.hxx"
#include "docfile.hxx"
#include "docinf.hxx"
#include "fcontnr.hxx"
#include "fsetobsh.hxx"
#include "loadenv.hxx"
#include "new.hxx"
#include "objitem.hxx"
#include "objsh.hxx"
#include "objshimp.hxx"
#include "openflag.hxx"
#include "passwd.hxx"
#include "referers.hxx"
#include "request.hxx"
#include "sfxresid.hxx"
#include "viewsh.hxx"
#include "app.hrc"
#include "topfrm.hxx"
#include "appimp.hxx"
#include "sfxuno.hxx"
#include "objface.hxx"
#include "filedlghelper.hxx"

#define _SVSTDARR_STRINGSDTOR
#include <svtools/svstdarr.hxx>

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {

using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::system;
using namespace ::com::sun::star::task;
using namespace ::cppu;
using namespace sfx2;

//=========================================================================

//STRIP001 class SfxOpenDocStatusListener_Impl : public WeakImplHelper1< XDispatchResultListener >
//STRIP001 {
//STRIP001 public:
//STRIP001     BOOL    bFinished;
//STRIP001     BOOL    bSuccess;
//STRIP001     virtual void SAL_CALL   dispatchFinished( const DispatchResultEvent& Event ) throw(RuntimeException);
//STRIP001     virtual void SAL_CALL   disposing( const EventObject& Source ) throw(RuntimeException);
//STRIP001                             SfxOpenDocStatusListener_Impl()
//STRIP001                                 : bFinished( FALSE )
//STRIP001                                 , bSuccess( FALSE )
//STRIP001                             {}
//STRIP001 };

//STRIP001 void SAL_CALL SfxOpenDocStatusListener_Impl::dispatchFinished( const DispatchResultEvent& aEvent ) throw(RuntimeException)
//STRIP001 {
//STRIP001     bSuccess = ( aEvent.State == DispatchResultState::SUCCESS );
//STRIP001     bFinished = TRUE;
//STRIP001 }

//STRIP001 void SAL_CALL SfxOpenDocStatusListener_Impl::disposing( const EventObject& Source ) throw(RuntimeException)
//STRIP001 {
//STRIP001 }

//STRIP001 SfxObjectShellRef SfxApplication::DocAlreadyLoaded
//STRIP001 (
//STRIP001     const String&   rName,      // Name des Dokuments mit Pfad
//STRIP001     BOOL            bSilent,    // TRUE: nicht nach neuer Sicht fragen
//STRIP001     BOOL            bActivate,   // soll bestehende Sicht aktiviert werden
//STRIP001     BOOL            bForbidVisible,
//STRIP001  const String*   pPostStr
//STRIP001 )
//STRIP001
//STRIP001 /*  [Beschreibung]
//STRIP001
//STRIP001     Stellt fest, ob ein Dokument mit dem Namen 'rName' bereits geladen
//STRIP001     ist und liefert einen Pointer darauf zu"uck.
//STRIP001
//STRIP001     Ist das Dokument noch nicht geladen, wird ein 0-Pointer zur"uckgeliefert.
//STRIP001 */
//STRIP001
//STRIP001 {
//STRIP001     // zu suchenden Namen als URL aufbereiten
//STRIP001     INetURLObject aUrlToFind( rName );
//STRIP001     DBG_ASSERT( aUrlToFind.GetProtocol() != INET_PROT_NOT_VALID, "Invalid URL" );
//STRIP001  String aPostString;
//STRIP001  if (  pPostStr )
//STRIP001      aPostString = *pPostStr;
//STRIP001
//STRIP001     // noch offen?
//STRIP001     SfxObjectShellRef xDoc;
//STRIP001
//STRIP001     if ( !aUrlToFind.HasError() )
//STRIP001     {
//STRIP001      // dann bei den normal geoeffneten Docs
//STRIP001      if ( !xDoc.Is() )
//STRIP001      {
//STRIP001          xDoc = SfxObjectShell::GetFirst( 0, FALSE ); // auch hidden Docs
//STRIP001          while( xDoc.Is() )
//STRIP001          {
//STRIP001              if ( xDoc->GetMedium() &&
//STRIP001                   xDoc->GetCreateMode() == SFX_CREATE_MODE_STANDARD &&
//STRIP001                   !xDoc->IsAbortingImport() && !xDoc->IsLoading() )
//STRIP001              {
//STRIP001                  // Vergleiche anhand der URLs
//STRIP001                     INetURLObject aUrl( xDoc->GetMedium()->GetName() );
//STRIP001                  if ( !aUrl.HasError() && aUrl == aUrlToFind &&
//STRIP001                          (!bForbidVisible || !SfxViewFrame::GetFirst( xDoc, 0, TRUE )) &&
//STRIP001                       !xDoc->IsLoading())
//STRIP001                  {
//STRIP001                          break;
//STRIP001                  }
//STRIP001              }
//STRIP001              xDoc = SfxObjectShell::GetNext( *xDoc, 0, FALSE );
//STRIP001          }
//STRIP001      }
//STRIP001     }
//STRIP001
//STRIP001     // gefunden?
//STRIP001     if ( xDoc.Is() && bActivate )
//STRIP001     {
//STRIP001         DBG_ASSERT(
//STRIP001             !bForbidVisible, "Unsichtbares kann nicht aktiviert werden" );
//STRIP001
//STRIP001      SfxTopViewFrame *pFrame;
//STRIP001         for( pFrame = (SfxTopViewFrame*)
//STRIP001                  SfxViewFrame::GetFirst( xDoc, TYPE(SfxTopViewFrame) );
//STRIP001              pFrame && !pFrame->IsVisible();
//STRIP001              pFrame = (SfxTopViewFrame*)
//STRIP001                  SfxViewFrame::GetNext( *pFrame, xDoc, TYPE(SfxTopViewFrame) ) );
//STRIP001      if ( pFrame )
//STRIP001      {
//STRIP001          SfxViewFrame *pCur = SfxViewFrame::Current();
//STRIP001          if ( !bSilent && pFrame == pCur )
//STRIP001              InfoBox( 0, SfxResId(RID_DOCALREADYLOADED_DLG)).Execute();
//STRIP001          if ( bActivate )
//STRIP001             {
//STRIP001                 pFrame->MakeActive_Impl( TRUE );
//STRIP001             }
//STRIP001      }
//STRIP001     }
//STRIP001     return xDoc;
//STRIP001 }

//====================================================================

//STRIP001 void SetTemplate_Impl( SvStorage *pStorage,
//STRIP001                        const String &rFileName,
//STRIP001                        const String &rLongName,
//STRIP001                        SfxObjectShell *pDoc)
//STRIP001 {
//STRIP001     // DocInfo von pDoc 'plattmachen'
//STRIP001     SfxDocumentInfo &rInfo = pDoc->GetDocInfo();
//STRIP001     rInfo.Clear();
//STRIP001
//STRIP001     // DocInfo vom Template laden
//STRIP001     SvStorageRef xTemplStor = new SvStorage( rFileName, STREAM_STD_READ );
//STRIP001     SfxDocumentInfo aTemplInfo;
//STRIP001
//STRIP001  if ( aTemplInfo.Load( xTemplStor ) )
//STRIP001      rInfo.SetTemplateDate( aTemplInfo.GetChanged().GetTime() );
//STRIP001
//STRIP001     // Template in DocInfo von pDoc eintragen
//STRIP001     INetURLObject aObj( rFileName );
//STRIP001     DBG_ASSERT( aObj.GetProtocol() != INET_PROT_NOT_VALID, "Invalid URL" );
//STRIP001
//STRIP001     if( ::utl::LocalFileHelper::IsLocalFile( rFileName ) )
//STRIP001  {
//STRIP001         String aFoundName;
//STRIP001         if( SFX_APP()->Get_Impl()->GetDocumentTemplates()->GetFull( String(), rLongName, aFoundName ) )
//STRIP001         {
//STRIP001             rInfo.SetTemplateFileName( aObj.GetMainURL(INetURLObject::DECODE_TO_IURI) );
//STRIP001             rInfo.SetTemplateName( rLongName );
//STRIP001
//STRIP001             // wenn schon eine Config da ist, mu\s sie aus dem Template sein
//STRIP001             BOOL bHasConfig = (pDoc->GetConfigManager() != 0);
//STRIP001             rInfo.SetTemplateConfig( bHasConfig );
//STRIP001             pDoc->SetTemplateConfig( bHasConfig );
//STRIP001         }
//STRIP001  }
//STRIP001
//STRIP001     // DocInfo in Stream schreiben
//STRIP001     pDoc->FlushDocInfo();
//STRIP001 }

//--------------------------------------------------------------------

/*N*/ ULONG CheckPasswd_Impl
/*N*/ (
/*N*/     //Window *pWin,       // Parent des Dialogs
/*N*/     SfxObjectShell* pDoc,
/*N*/   SfxItemPool &rPool, // Pool, falls ein Set erzeugt werden mus
/*N*/   SfxMedium *pFile    // das Medium, dessen Passwort gfs. erfragt werden soll
/*N*/ )

/*  [Beschreibung]

    Zu einem Medium das Passwort erfragen; funktioniert nur, wenn es sich
    um einen Storage handelt.
    Wenn in der Documentinfo das Passwort-Flag gesetzt ist, wird
    das Passwort vom Benutzer per Dialog erfragt und an dem Set
    des Mediums gesetzt; das Set wird, wenn nicht vorhanden, erzeugt.

*/

/*N*/ {
/*N*/     ULONG nRet=0;
/*N*/     if( ( !pFile->GetFilter() || pFile->GetFilter()->UsesStorage() ) )
/*N*/     {
/*N*/         SvStorageRef aRef = pFile->GetStorage();
/*N*/         if(aRef.Is())
/*N*/         {
/*N*/             sal_Bool bIsEncrypted = sal_False;
/*N*/             ::com::sun::star::uno::Any aAny;
/*N*/             if ( aRef->GetProperty( ::rtl::OUString::createFromAscii("HasEncryptedEntries"), aAny ) )
/*N*/                 aAny >>= bIsEncrypted;
/*N*/             else
/*N*/             {
/*N*/                 SfxDocumentInfo aInfo;
/*N*/                 bIsEncrypted = ( aInfo.Load(aRef) && aInfo.IsPasswd() );
/*N*/             }
/*N*/
/*N*/             if ( bIsEncrypted )
/*N*/             {
                nRet = ERRCODE_SFX_CANTGETPASSWD;
                SfxItemSet *pSet = pFile->GetItemSet();
                if( pSet )
                {
                    Reference< ::com::sun::star::task::XInteractionHandler > xInteractionHandler;

                    SFX_ITEMSET_ARG( pSet, pxInteractionItem, SfxUnoAnyItem, SID_INTERACTIONHANDLER, sal_False );
                    if( pxInteractionItem && ( pxInteractionItem->GetValue() >>= xInteractionHandler )
                     && xInteractionHandler.is() )
                    {
                        RequestDocumentPassword* pPasswordRequest = new RequestDocumentPassword(
                            ::com::sun::star::task::PasswordRequestMode_PASSWORD_ENTER,
                            INetURLObject( pFile->GetOrigURL() ).GetName( INetURLObject::DECODE_WITH_CHARSET ) );

                        Reference< XInteractionRequest > rRequest( pPasswordRequest );
                        xInteractionHandler->handle( rRequest );

                        if ( pPasswordRequest->isPassword() )
                        {
                            pSet->Put( SfxStringItem( SID_PASSWORD, pPasswordRequest->getPassword() ) );
                            nRet = ERRCODE_NONE;
                        }
                        else
                            nRet = ERRCODE_IO_ABORT;
                    }
                }
/*?*/             }
/*N*/         }
/*N*/     }
/*N*/     return nRet;
/*N*/ }

//--------------------------------------------------------------------


//STRIP001 ULONG SfxApplication::LoadTemplate( SfxObjectShellLock& xDoc, const String &rFileName, BOOL bCopy, SfxItemSet* pSet )
//STRIP001 {
//STRIP001     const SfxFilter* pFilter = NULL;
//STRIP001     SfxMedium aMedium( rFileName,  ( STREAM_READ | STREAM_SHARE_DENYNONE ), FALSE );
//STRIP001
//STRIP001     if ( !aMedium.GetStorage() )
//STRIP001         aMedium.GetInStream();
//STRIP001
//STRIP001     if ( aMedium.GetError() )
//STRIP001  {
//STRIP001      delete pSet;
//STRIP001         return aMedium.GetErrorCode();
//STRIP001  }
//STRIP001
//STRIP001     ULONG nErr = GetFilterMatcher().GuessFilter( aMedium,&pFilter,SFX_FILTER_TEMPLATE, 0 );
//STRIP001     if ( 0 != nErr)
//STRIP001     {
//STRIP001      delete pSet;
//STRIP001         return ERRCODE_SFX_NOTATEMPLATE;
//STRIP001     }
//STRIP001
//STRIP001     if( !pFilter || !pFilter->IsAllowedAsTemplate() )
//STRIP001     {
//STRIP001      delete pSet;
//STRIP001         return ERRCODE_SFX_NOTATEMPLATE;
//STRIP001     }
//STRIP001
//STRIP001  if ( pFilter->GetFilterFlags() & SFX_FILTER_STARONEFILTER )
//STRIP001  {
//STRIP001      DBG_ASSERT( !xDoc.Is(), "Sorry, not implemented!" );
//STRIP001      delete pSet;
//STRIP001      SfxStringItem aName( SID_FILE_NAME, rFileName );
//STRIP001      SfxStringItem aReferer( SID_REFERER, String::CreateFromAscii("private:user") );
//STRIP001      SfxStringItem aFlags( SID_OPTIONS, String::CreateFromAscii("T") );
//STRIP001      SfxBoolItem aHidden( SID_HIDDEN, TRUE );
//STRIP001      const SfxPoolItem *pRet = GetDispatcher_Impl()->Execute( SID_OPENDOC, SFX_CALLMODE_SYNCHRON, &aName, &aHidden, &aReferer, &aFlags, 0L );
//STRIP001      const SfxObjectItem *pObj = PTR_CAST( SfxObjectItem, pRet );
//STRIP001      xDoc = PTR_CAST( SfxObjectShell, pObj->GetShell() );
//STRIP001      if ( !xDoc.Is() )
//STRIP001          return ERRCODE_SFX_DOLOADFAILED;
//STRIP001      xDoc->OwnerLock( FALSE );   // lock was set by hidden load
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if ( !xDoc.Is() )
//STRIP001          xDoc = ((SfxFactoryFilterContainer*)pFilter->GetFilterContainer())->GetFactory().CreateObject();
//STRIP001
//STRIP001      SfxMedium *pMedium = new SfxMedium( rFileName, STREAM_STD_READ, FALSE, pFilter, pSet );
//STRIP001      if(!xDoc->DoLoad(pMedium))
//STRIP001      {
//STRIP001          ErrCode nErr = xDoc->GetErrorCode();
//STRIP001          xDoc->DoClose();
//STRIP001          xDoc.Clear();
//STRIP001          return nErr;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001     if( bCopy )
//STRIP001     {
//STRIP001         SvStorageRef aTmpStor = new SvStorage( (xDoc->GetStorage()->GetVersion() >= SOFFICE_FILEFORMAT_60) ,String() );
//STRIP001         if( 0 != aTmpStor->GetError())
//STRIP001         {
//STRIP001          xDoc->DoClose();
//STRIP001          xDoc.Clear();
//STRIP001             return aTmpStor->GetErrorCode();
//STRIP001         }
//STRIP001         xDoc->GetStorage()->CopyTo( &aTmpStor );
//STRIP001         xDoc->DoHandsOff();
//STRIP001         if ( !xDoc->DoSaveCompleted( aTmpStor ) )
//STRIP001         {
//STRIP001          xDoc->DoClose();
//STRIP001          xDoc.Clear();
//STRIP001          return aTmpStor->GetErrorCode();
//STRIP001         }
//STRIP001
//STRIP001         SetTemplate_Impl( aTmpStor, rFileName, String(), xDoc );
//STRIP001     }
//STRIP001     else
//STRIP001         SetTemplate_Impl( xDoc->GetStorage(), rFileName, String(), xDoc );
//STRIP001
//STRIP001     xDoc->Broadcast( SfxDocumentInfoHint( &xDoc->GetDocInfo() ) );
//STRIP001     xDoc->SetNoName();
//STRIP001     xDoc->InvalidateName();
//STRIP001     xDoc->SetModified(FALSE);
//STRIP001     xDoc->ResetError();
//STRIP001
//STRIP001     ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel >  xModel ( xDoc->GetModel(), ::com::sun::star::uno::UNO_QUERY );
//STRIP001     if ( xModel.is() )
//STRIP001     {
//STRIP001         SfxItemSet* pNew = xDoc->GetMedium()->GetItemSet()->Clone();
//STRIP001         pNew->ClearItem( SID_PROGRESS_STATUSBAR_CONTROL );
//STRIP001         pNew->Put( SfxStringItem( SID_FILTER_NAME, xDoc->GetFactory().GetFilter(0)->GetFilterName() ) );
//STRIP001         ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > aArgs;
//STRIP001         TransformItems( SID_OPENDOC, *pNew, aArgs );
//STRIP001         sal_Int32 nLength = aArgs.getLength();
//STRIP001         aArgs.realloc( nLength + 1 );
//STRIP001         aArgs[nLength].Name = DEFINE_CONST_UNICODE("Title");
//STRIP001         aArgs[nLength].Value <<= ::rtl::OUString( xDoc->GetTitle( SFX_TITLE_DETECT ) );
//STRIP001         xModel->attachResource( ::rtl::OUString(), aArgs );
//STRIP001         delete pNew;
//STRIP001     }
//STRIP001
//STRIP001     return xDoc->GetErrorCode();
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 void SfxApplication::LoadEa_Impl(SfxMedium &rMedium, SfxObjectShell& rObj)
//STRIP001 {
//STRIP001     if ( !rMedium.GetStorage() )
//STRIP001         return;
//STRIP001     const SfxFilter *pFilter = rMedium.GetFilter();
//STRIP001     if ( !pFilter || !pFilter->IsOwnFormat() )
//STRIP001         return;
//STRIP001     SvStorage *pStor = rMedium.GetStorage();
//STRIP001     if ( !pStor )
//STRIP001         return;
//STRIP001     SvStream *pStream = pStor->GetTargetSvStream();
//STRIP001     if ( pStream && pStream->IsA() == ID_FILESTREAM )
//STRIP001     {
//STRIP001         SvEaMgr aEaMgr(*(SvFileStream *)pStream);
//STRIP001         String aBuffer;
//STRIP001         // Langnamen merken f"ur Titel und erneutes Setzen
//STRIP001         // beim Speichern
//STRIP001         if ( aEaMgr.GetLongName(aBuffer) )
//STRIP001             rMedium.SetLongName(aBuffer);
//STRIP001         if ( aEaMgr.GetComment(aBuffer) )
//STRIP001         {
//STRIP001             SfxDocumentInfo *pInfo = &rObj.GetDocInfo();
//STRIP001             // Kommentar aus der WPS mit DocInfo abgleichen
//STRIP001             pInfo->SetComment(aBuffer);
//STRIP001         }
//STRIP001     }
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 SfxMedium* SfxApplication::InsertDocumentDialog
//STRIP001 (
//STRIP001     ULONG                   nFlags,
//STRIP001     const SfxObjectFactory& rFact
//STRIP001 )
//STRIP001 {
//STRIP001     return InsertDocumentDialog( nFlags, rFact, 0 );
//STRIP001 }
//STRIP001
//STRIP001 //--------------------------------------------------------------------
//STRIP001
//STRIP001 SfxMedium* SfxApplication::InsertDocumentDialog
//STRIP001 (
//STRIP001     ULONG                   nFlags,
//STRIP001     const SfxObjectFactory& rFact,
//STRIP001     ULONG                   nHelpId
//STRIP001 )
//STRIP001 {
//STRIP001     SfxMedium *pMedium=0;
//STRIP001  SvStringsDtor* pURLList = NULL;
//STRIP001     String aFilter;
//STRIP001     SfxItemSet* pSet=0;
//STRIP001     ErrCode nErr = sfx2::FileOpenDialog_Impl( nFlags | SFXWB_INSERT | WB_3DLOOK, rFact, pURLList, aFilter, pSet, String(), nHelpId );
//STRIP001     if( pURLList && !nErr )
//STRIP001     {
//STRIP001      DBG_ASSERT( pURLList->Count() == 1, "invalid URLList count" );
//STRIP001      String aURL = *(pURLList->GetObject(0));
//STRIP001         pMedium = new SfxMedium(
//STRIP001              aURL, SFX_STREAM_READONLY, FALSE,
//STRIP001              GetFilterMatcher().GetFilter( aFilter ), pSet );
//STRIP001
//STRIP001      pMedium->UseInteractionHandler(TRUE);
//STRIP001      LoadEnvironment_ImplRef xLoader = new LoadEnvironment_Impl( pMedium );
//STRIP001      SfxFilterMatcher aMatcher( rFact.GetFilterContainer() );
//STRIP001      xLoader->SetFilterMatcher( &aMatcher );
//STRIP001         xLoader->Start();
//STRIP001         while( xLoader->GetState() != LoadEnvironment_Impl::DONE  )
//STRIP001             Application::Yield();
//STRIP001      pMedium = xLoader->GetMedium();
//STRIP001         if( pMedium && CheckPasswd_Impl( 0, SFX_APP()->GetPool(), pMedium ) == ERRCODE_ABORT )
//STRIP001             pMedium = NULL;
//STRIP001     }
//STRIP001
//STRIP001  delete pURLList;
//STRIP001     return pMedium;
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 SfxMediumList* SfxApplication::InsertDocumentsDialog
//STRIP001 (
//STRIP001     ULONG                   nFlags,
//STRIP001     const SfxObjectFactory& rFact,
//STRIP001     ULONG                   nHelpId
//STRIP001 )
//STRIP001 {
//STRIP001     SfxMediumList *pMediumList=new SfxMediumList;
//STRIP001  SvStringsDtor* pURLList = NULL;
//STRIP001     String aFilter;
//STRIP001     SfxItemSet* pSet=0;
//STRIP001     ErrCode nErr = sfx2::FileOpenDialog_Impl( nFlags | SFXWB_INSERT | SFXWB_MULTISELECTION | WB_3DLOOK, rFact, pURLList, aFilter, pSet, String(), nHelpId );
//STRIP001  DBG_ASSERT( pURLList, "invalid URLList" );
//STRIP001     if( pURLList && !nErr )
//STRIP001     {
//STRIP001      for ( USHORT n=0; n<pURLList->Count(); n++ )
//STRIP001      {
//STRIP001          String aURL = *(pURLList->GetObject(n));
//STRIP001          SfxMedium* pMedium = new SfxMedium(
//STRIP001                  aURL, SFX_STREAM_READONLY, FALSE,
//STRIP001                  GetFilterMatcher().GetFilter( aFilter ), pSet );
//STRIP001
//STRIP001          pMedium->UseInteractionHandler(TRUE);
//STRIP001          LoadEnvironment_ImplRef xLoader = new LoadEnvironment_Impl( pMedium );
//STRIP001          SfxFilterMatcher aMatcher( rFact.GetFilterContainer() );
//STRIP001          xLoader->SetFilterMatcher( &aMatcher );
//STRIP001          xLoader->Start();
//STRIP001          while( xLoader->GetState() != LoadEnvironment_Impl::DONE  )
//STRIP001              Application::Yield();
//STRIP001          pMedium = xLoader->GetMedium();
//STRIP001          if( pMedium && CheckPasswd_Impl( 0, GetPool(), pMedium ) != ERRCODE_ABORT )
//STRIP001          {
//STRIP001              pMediumList->Insert( pMedium );
//STRIP001          }
//STRIP001          else
//STRIP001              delete pMedium;
//STRIP001      }
//STRIP001     }
//STRIP001
//STRIP001  delete pURLList;
//STRIP001     return pMediumList;
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 SfxMediumList* SfxApplication::InsertDocumentsDialog
//STRIP001 (
//STRIP001     ULONG                   nFlags,
//STRIP001     const SfxObjectFactory& rFact
//STRIP001 )
//STRIP001 {
//STRIP001     return InsertDocumentsDialog( nFlags, rFact, 0 );
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 void SfxApplication::NewFramesetExec_Impl( SfxRequest& rReq )
//STRIP001 {
//STRIP001     DBG_MEMTEST();
//STRIP001 /*
//STRIP001     // Factory-RegNo kann per Parameter angegeben sein
//STRIP001     SfxErrorContext aEc(ERRCTX_SFX_NEWDOCDIRECT);
//STRIP001
//STRIP001  SfxFrameSetObjectShell *pDoc =
//STRIP001              new SfxFrameSetObjectShell( SFX_CREATE_MODE_STANDARD );
//STRIP001     SfxObjectShellRef xDoc(pDoc);
//STRIP001  pDoc->Initialize( String() );
//STRIP001     xDoc->SetActivateEvent_Impl( SFX_EVENT_CREATEDOC );
//STRIP001
//STRIP001  SFX_REQUEST_ARG(rReq, pFrameItem, SfxFrameItem,
//STRIP001                  SID_DOCFRAME, FALSE);
//STRIP001  if ( pFrameItem && pFrameItem->GetFrame() )
//STRIP001      pFrameItem->GetFrame()->InsertDocument( pDoc );
//STRIP001  else
//STRIP001      CreateView_Impl( rReq, pDoc, TRUE );
//STRIP001
//STRIP001     GetAppDispatcher_Impl()->Execute( SID_EDIT_FRAMESET );
//STRIP001  */
//STRIP001 }

//--------------------------------------------------------------------
/*N*/ SfxObjectShellLock SfxApplication::NewDoc_Impl( const String& rFact, const SfxItemSet *pSet )
/*N*/ {
/*N*/     SfxObjectShellLock xDoc;
/*N*/   const SfxObjectFactory* pFactory = 0;
/*N*/   String aFact( rFact );
/*N*/   String aPrefix = String::CreateFromAscii( "private:factory/" );
/*N*/   if ( aPrefix.Len() == aFact.Match( aPrefix ) )
/*?*/       aFact.Erase( 0, aPrefix.Len() );
/*N*/   USHORT nPos = aFact.Search( '?' );
/*N*/   String aParam;
/*N*/   if ( nPos != STRING_NOTFOUND )
/*N*/   {
/*N*/       aParam = aFact.Copy( nPos, aFact.Len() );
/*N*/       aFact.Erase( nPos, aFact.Len() );
/*N*/       aParam.Erase(0,1);
/*N*/   }
/*N*/
/*N*/   WildCard aSearchedFac( aFact.EraseAllChars('4').ToUpperAscii() );
/*N*/     for( USHORT n = SfxObjectFactory::GetObjectFactoryCount_Impl(); !pFactory && n--; )
/*N*/   {
/*?*/         pFactory = &SfxObjectFactory::GetObjectFactory_Impl( n );
/*?*/       if( !aSearchedFac.Matches( String::CreateFromAscii( pFactory->GetShortName() ).ToUpperAscii() ) )
/*?*/           pFactory = 0;
/*?*/   }
/*N*/
/*N*/   if( !pFactory )
/*N*/   {
/*?*/       DBG_ERROR("Unknown factory!");
/*?*/       pFactory = &SfxObjectFactory::GetDefaultFactory();
/*N*/   }
/*N*/
/*N*/     xDoc = pFactory->CreateObject();
/*N*/     aParam = INetURLObject::decode( aParam, '%', INetURLObject::DECODE_WITH_CHARSET );
/*N*/   if( xDoc.Is() )
/*N*/       xDoc->DoInitNew_Impl( aParam );
/*N*/
/*N*/     if ( xDoc.Is() )
/*N*/     {
/*N*/       if ( pSet )
/*N*/       {
/*N*/           SFX_ITEMSET_ARG( pSet, pTitleItem, SfxStringItem, SID_DOCINFO_TITLE, FALSE );
/*N*/           if ( pTitleItem )
/*?*/               xDoc->GetMedium()->GetItemSet()->Put( *pTitleItem );
/*N*/       }
/*N*/
/*N*/         ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel >  xModel ( xDoc->GetModel(), ::com::sun::star::uno::UNO_QUERY );
/*N*/       if ( xModel.is() )
/*N*/       {
/*N*/             SfxItemSet* pNew = xDoc->GetMedium()->GetItemSet()->Clone();
/*N*/             pNew->ClearItem( SID_PROGRESS_STATUSBAR_CONTROL );
/*N*/           ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > aArgs;
/*N*/             TransformItems( SID_OPENDOC, *pNew, aArgs );
/*N*/
/*N*/             sal_Int32 nLength = aArgs.getLength();
/*N*/             aArgs.realloc( nLength + 1 );
/*N*/
/*N*/             aArgs[nLength].Name = DEFINE_CONST_UNICODE("Title");
/*N*/             aArgs[nLength].Value <<= ::rtl::OUString( xDoc->GetTitle( SFX_TITLE_DETECT ) );
/*N*/
/*N*/             xModel->attachResource( ::rtl::OUString(), aArgs );
/*N*/             delete pNew;
/*N*/       }
/*N*/     }
/*N*/
/*N*/   return xDoc;
/*N*/ }

/*N*/ void SfxApplication::NewDocDirectExec_Impl( SfxRequest& rReq )
/*N*/ {
/*N*/     DBG_MEMTEST();
/*N*/
/*N*/   SFX_REQUEST_ARG(rReq, pHidden, SfxBoolItem, SID_HIDDEN, FALSE);
//(mba)/task
/*
    if ( !pHidden || !pHidden->GetValue() )
        Application::GetAppWindow()->EnterWait();
*/
/*N*/     SfxObjectShellLock xDoc;
/*N*/     BOOL bNewView = TRUE;
/*N*/
/*N*/     // Factory-RegNo kann per Parameter angegeben sein
/*N*/     SfxErrorContext aEc(ERRCTX_SFX_NEWDOCDIRECT);
/*N*/     const SfxItemSet *pArgs = rReq.GetArgs();
/*N*/   const SfxObjectFactory* pFactory = 0;
/*N*/   String aFactory;
/*N*/   rReq.AppendItem( SfxBoolItem( SID_TEMPLATE, TRUE ) );
/*N*/   SFX_REQUEST_ARG( rReq, pFactoryName, SfxStringItem, SID_NEWDOCDIRECT, FALSE );
/*N*/   if( pFactoryName )
/*N*/       aFactory = pFactoryName->GetValue();
/*N*/     else
/*N*/     {
/*?*/         SvtModuleOptions aOpt;
/*?*/
/*?*/         if (aOpt.IsModuleInstalled(SvtModuleOptions::E_SWRITER))
/*?*/             aFactory = aOpt.GetFactoryShortName(SvtModuleOptions::E_WRITER);
/*?*/         else
/*?*/         if (aOpt.IsModuleInstalled(SvtModuleOptions::E_SCALC))
/*?*/             aFactory = aOpt.GetFactoryShortName(SvtModuleOptions::E_CALC);
/*?*/         else
/*?*/         if (aOpt.IsModuleInstalled(SvtModuleOptions::E_SDRAW))
/*?*/             aFactory = aOpt.GetFactoryShortName(SvtModuleOptions::E_DRAW);
/*?*/         else
/*?*/         if (aOpt.IsModuleInstalled(SvtModuleOptions::E_SIMPRESS))
/*?*/             aFactory = aOpt.GetFactoryShortName(SvtModuleOptions::E_IMPRESS);
/*?*/         else
/*?*/         if (aOpt.IsModuleInstalled(SvtModuleOptions::E_SMATH))
/*?*/             aFactory = aOpt.GetFactoryShortName(SvtModuleOptions::E_MATH);
/*?*/         else
/*?*/         if (aOpt.IsModuleInstalled(SvtModuleOptions::E_SWRITER))
/*?*/             aFactory = aOpt.GetFactoryShortName(SvtModuleOptions::E_WRITERGLOBAL);
/*?*/         else
/*?*/         if (aOpt.IsModuleInstalled(SvtModuleOptions::E_SWRITER))
/*?*/             aFactory = aOpt.GetFactoryShortName(SvtModuleOptions::E_WRITERWEB);
/*N*/     }
/*N*/
/*N*/     SFX_REQUEST_ARG( rReq, pFileFlagsItem, SfxStringItem, SID_OPTIONS, FALSE);
/*N*/     if ( pFileFlagsItem )
/*N*/     {
/*N*/         // Werte auf einzelne Items verteilen
/*?*/         String aFileFlags = pFileFlagsItem->GetValue();
/*?*/         aFileFlags.ToUpperAscii();
/*?*/         if ( STRING_NOTFOUND != aFileFlags.Search( 0x0054 ) )               // T = 54h
/*?*/             rReq.AppendItem( SfxBoolItem( SID_TEMPLATE, TRUE ) );
/*?*/         if ( STRING_NOTFOUND != aFileFlags.Search( 0x0048 ) )               // H = 48h
/*?*/             rReq.AppendItem( SfxBoolItem( SID_HIDDEN, TRUE ) );
/*?*/         if ( STRING_NOTFOUND != aFileFlags.Search( 0x0052 ) )               // R = 52h
/*?*/             rReq.AppendItem( SfxBoolItem( SID_DOC_READONLY, TRUE ) );
/*?*/         if ( STRING_NOTFOUND != aFileFlags.Search( 0x0042 ) )               // B = 42h
/*?*/             rReq.AppendItem( SfxBoolItem( SID_PREVIEW, TRUE ) );
/*?*/         if ( STRING_NOTFOUND != aFileFlags.Search( 0x0053 ) )               // S = 53h
/*?*/             rReq.AppendItem( SfxBoolItem( SID_SILENT, TRUE ) );
/*N*/     }
/*N*/
/*N*/   xDoc = NewDoc_Impl( aFactory, rReq.GetArgs() );
/*N*/   if ( xDoc.Is() )
/*N*/   {
/*N*/       SFX_REQUEST_ARG(rReq, pReadonly, SfxBoolItem, SID_DOC_READONLY, FALSE);
/*N*/       if ( pReadonly )
/*?*/           xDoc->GetMedium()->GetItemSet()->Put( *pReadonly );
/*N*/
/*N*/       SFX_REQUEST_ARG(rReq, pPreview, SfxBoolItem, SID_PREVIEW, FALSE);
/*N*/       if ( pPreview )
/*?*/           xDoc->GetMedium()->GetItemSet()->Put( *pPreview );
/*N*/
/*N*/         SFX_REQUEST_ARG(rReq, pSilent, SfxBoolItem, SID_SILENT, FALSE);
/*N*/         if ( pSilent )
/*?*/             xDoc->GetMedium()->GetItemSet()->Put( *pSilent );
/*N*/
/*N*/         SFX_REQUEST_ARG(rReq, pFlags, SfxStringItem, SID_OPTIONS, FALSE);
/*N*/         if ( pFlags )
/*?*/             xDoc->GetMedium()->GetItemSet()->Put( *pFlags );
/*N*/   }
/*N*/
/*N*/     // View erzeugen
/*N*/   SfxViewFrame* pViewFrame = 0;
/*N*/     if ( xDoc.Is() )
/*N*/     {
/*N*/       SFX_REQUEST_ARG(rReq, pHidden, SfxBoolItem, SID_HIDDEN, FALSE);
/*N*/         BOOL bHidden = FALSE;
/*N*/       if ( pHidden )
/*N*/         {
/*N*/           xDoc->GetMedium()->GetItemSet()->Put( *pHidden, SID_HIDDEN );
/*N*/             bHidden = pHidden->GetValue();
/*N*/         }
/*N*/
/*N*/       SFX_REQUEST_ARG(rReq, pViewId, SfxUInt16Item, SID_VIEW_ID, FALSE);
/*N*/         USHORT nViewId = 0;
/*N*/       if ( pViewId )
/*N*/         {
/*?*/           xDoc->GetMedium()->GetItemSet()->Put( *pViewId, SID_VIEW_ID );
/*?*/             nViewId = pViewId->GetValue();
/*N*/         }
/*N*/
/*N*/       xDoc->SetActivateEvent_Impl( SFX_EVENT_CREATEDOC );
/*N*/ //        xDoc->Get_Impl()->nLoadedFlags = SFX_LOADED_ALL;
/*N*/       const SfxItemSet* pInternalArgs = rReq.GetInternalArgs_Impl();
/*N*/       if( pInternalArgs )
/*?*/           xDoc->GetMedium()->GetItemSet()->Put( *pInternalArgs );
/*N*/       BOOL bOwnsFrame = FALSE;
/*N*/         SFX_REQUEST_ARG(rReq, pFrameItem, SfxFrameItem, SID_DOCFRAME, FALSE);
/*N*/
/*N*/         SfxFrame* pFrame = NULL;
/*N*/         if (pFrameItem)
/*N*/             pFrame = pFrameItem->GetFrame();
/*N*/         else
/*?*/             {DBG_BF_ASSERT(0, "STRIP");}//STRIP001 pFrame = (SfxFrame*)SfxTopFrame::Create(xDoc, nViewId, bHidden, pInternalArgs);
/*N*/         if ( pFrame )
/*N*/         {
/*N*/             if ( pFrame->GetCurrentDocument() == xDoc || pFrame->PrepareClose_Impl( TRUE, TRUE ) == TRUE )
/*N*/             {
/*N*/                 if (bHidden)
/*N*/                 {
/*N*/                     xDoc->RestoreNoDelete();
/*N*/                     xDoc->OwnerLock( TRUE );
/*N*/                     xDoc->Get_Impl()->bHiddenLockedByAPI = TRUE;
/*N*/                 }
/*N*/
/*N*/                 if ( pFrame->GetCurrentDocument() != xDoc )
/*N*/                     pFrame->InsertDocument( xDoc );
/*N*/                 pViewFrame = pFrame->GetCurrentViewFrame();
/*N*/             }
/*N*/             else
/*?*/                 xDoc.Clear();
/*N*/         }
/*N*/
/*N*/         rReq.SetReturnValue( SfxFrameItem( 0, pFrame ) );
/*N*/     }
/*N*/
//(mba)/task
/*
    if ( !pHidden || !pHidden->GetValue() )
        Application::GetAppWindow()->LeaveWait();
 */
/*N*/ }

//--------------------------------------------------------------------

/*?*/ void SfxApplication::NewDocExec_Impl( SfxRequest& rReq )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     DBG_MEMTEST();
//STRIP001
//STRIP001     // keine Parameter vom BASIC nur Factory angegeben?
//STRIP001     SFX_REQUEST_ARG(rReq, pTemplNameItem, SfxStringItem, SID_TEMPLATE_NAME, FALSE);
//STRIP001     SFX_REQUEST_ARG(rReq, pTemplFileNameItem, SfxStringItem, SID_FILE_NAME, FALSE);
//STRIP001     SFX_REQUEST_ARG(rReq, pTemplRegionNameItem, SfxStringItem, SID_TEMPLATE_REGIONNAME, FALSE);
//STRIP001
//STRIP001     SfxObjectShellLock xDoc;
//STRIP001     BOOL bNewView = TRUE;
//STRIP001
//STRIP001     String  aTemplateRegion, aTemplateName, aTemplateFileName;
//STRIP001     BOOL    bDirect = FALSE; // "uber FileName anstelle Region/Template
//STRIP001     SfxErrorContext aEc(ERRCTX_SFX_NEWDOC);
//STRIP001     if ( !pTemplNameItem && !pTemplFileNameItem )
//STRIP001     {
//STRIP001      Window* pTopWin = GetTopWindow();
//STRIP001      SvtDocumentTemplateDialog* pDocTemplDlg = new SvtDocumentTemplateDialog( pTopWin );
//STRIP001         int nRet = pDocTemplDlg->Execute();
//STRIP001      sal_Bool bNewWin = sal_False;
//STRIP001         if ( nRet == RET_OK )
//STRIP001      {
//STRIP001             rReq.Done();
//STRIP001             if ( pTopWin != GetTopWindow() )
//STRIP001             {
//STRIP001                 // the dialogue opens a document -> a new TopWindow appears
//STRIP001                 pTopWin = GetTopWindow();
//STRIP001                 bNewWin = sal_True;
//STRIP001             }
//STRIP001      }
//STRIP001
//STRIP001      delete pDocTemplDlg;
//STRIP001      if ( bNewWin )
//STRIP001          // after the destruction of the dialogue its parent comes to top,
//STRIP001          // but we want that the new document is on top
//STRIP001          pTopWin->ToTop();
//STRIP001
//STRIP001      return;
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         // Template-Name
//STRIP001         if ( pTemplNameItem )
//STRIP001             aTemplateName = pTemplNameItem->GetValue();
//STRIP001
//STRIP001         // Template-Region
//STRIP001         if ( pTemplRegionNameItem )
//STRIP001             aTemplateRegion = pTemplRegionNameItem->GetValue();
//STRIP001
//STRIP001         // Template-File-Name
//STRIP001         if ( pTemplFileNameItem )
//STRIP001         {
//STRIP001             aTemplateFileName = pTemplFileNameItem->GetValue();
//STRIP001             bDirect = TRUE;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001  ULONG lErr = 0;
//STRIP001  SfxItemSet* pSet = new SfxAllItemSet( GetPool() );
//STRIP001  pSet->Put( SfxBoolItem( SID_TEMPLATE, TRUE ) );
//STRIP001     if ( !bDirect )
//STRIP001  {
//STRIP001      SfxDocumentTemplates aTmpFac;
//STRIP001      if( !aTemplateFileName.Len() )
//STRIP001          aTmpFac.GetFull( aTemplateRegion, aTemplateName, aTemplateFileName );
//STRIP001
//STRIP001         if( !aTemplateFileName.Len() )
//STRIP001          lErr = ERRCODE_SFX_TEMPLATENOTFOUND;
//STRIP001  }
//STRIP001
//STRIP001     INetURLObject aObj( aTemplateFileName );
//STRIP001  SfxErrorContext aEC( ERRCTX_SFX_LOADTEMPLATE, aObj.PathToFileName() );
//STRIP001
//STRIP001     if ( lErr != ERRCODE_NONE )
//STRIP001     {
//STRIP001         ULONG lFatalErr = ERRCODE_TOERROR(lErr);
//STRIP001         if ( lFatalErr )
//STRIP001             ErrorHandler::HandleError(lErr);
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         SfxCallMode eMode = SFX_CALLMODE_SYNCHRON;
//STRIP001         if ( IsPlugin() )
//STRIP001             eMode = SFX_CALLMODE_ASYNCHRON;
//STRIP001
//STRIP001         const SfxPoolItem *pRet=0;
//STRIP001         SfxStringItem aReferer( SID_REFERER, DEFINE_CONST_UNICODE("private:user") );
//STRIP001         SfxStringItem aTarget( SID_TARGETNAME, DEFINE_CONST_UNICODE("_default") );
//STRIP001         if ( aTemplateFileName.Len() )
//STRIP001         {
//STRIP001             INetURLObject aObj( aTemplateFileName );
//STRIP001             DBG_ASSERT( aObj.GetProtocol() != INET_PROT_NOT_VALID, "Illegal URL!" );
//STRIP001
//STRIP001             SfxStringItem aName( SID_FILE_NAME, aObj.GetMainURL( INetURLObject::NO_DECODE ) );
//STRIP001             SfxStringItem aTemplName( SID_TEMPLATE_NAME, aTemplateName );
//STRIP001             SfxStringItem aTemplRegionName( SID_TEMPLATE_REGIONNAME, aTemplateRegion );
//STRIP001             pRet = GetDispatcher_Impl()->Execute( SID_OPENDOC, eMode, &aName, &aTarget, &aReferer, &aTemplName, &aTemplRegionName, 0L );
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             SfxStringItem aName( SID_FILE_NAME, DEFINE_CONST_UNICODE("private:factory") );
//STRIP001             pRet = GetDispatcher_Impl()->Execute( SID_OPENDOC, eMode, &aName, &aTarget, &aReferer, 0L );
//STRIP001         }
//STRIP001
//STRIP001         if ( pRet )
//STRIP001             rReq.SetReturnValue( *pRet );
//STRIP001     }
/*?*/ }

//---------------------------------------------------------------------------

/*?*/ void SfxApplication::OpenDocExec_Impl( SfxRequest& rReq )
/*?*/ {DBG_BF_ASSERT(0, "STRIP");//STRIP001
//STRIP001 /*?*/     DBG_MEMTEST();
//STRIP001 /*?*/
//STRIP001 /*?*/    USHORT nSID = rReq.GetSlot();
//STRIP001 /*?*/     SFX_REQUEST_ARG( rReq, pFileNameItem, SfxStringItem, SID_FILE_NAME, FALSE );
//STRIP001 /*?*/     if ( pFileNameItem )
//STRIP001 /*?*/     {
//STRIP001 /*?*/         String aCommand( pFileNameItem->GetValue() );
//STRIP001 /*?*/         const SfxSlot* pSlot = GetInterface()->GetSlot( aCommand );
//STRIP001 /*?*/         if ( pSlot )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             pFileNameItem = NULL;
//STRIP001 /*?*/         }
//STRIP001 /*?*/         else
//STRIP001 /*?*/         {
//STRIP001 /*?*/                 USHORT nSlotId = (USHORT) String( aCommand, 5, aCommand.Len()-5 ).ToInt32();
//STRIP001 /*?*/             if ( !nIndex )
//STRIP001 /*?*/             {
//STRIP001 /*?*/                 USHORT nSlotId = (USHORT) String( aCommand, 5, aCommand.Len()-5 ).ToInt32();
//STRIP001 /*?*/                 if ( nSlotId == SID_OPENDOC )
//STRIP001 /*?*/                     pFileNameItem = NULL;
//STRIP001 /*?*/             }
//STRIP001 /*?*/         }
//STRIP001 /*?*/     }
//STRIP001 /*?*/
//STRIP001 /*?*/     if ( !pFileNameItem )
//STRIP001 /*?*/     {
//STRIP001 /*?*/         // FileDialog ausf"uhren
//STRIP001 /*?*/         SvStringsDtor* pURLList = NULL;
//STRIP001 /*?*/         String aFilter;
//STRIP001 /*?*/         void* pDummy = 0; // wegen GCC und C272
//STRIP001 /*?*/         SfxItemSet* pSet = NULL;
//STRIP001 /*?*/         String aPath;
//STRIP001 /*?*/         if ( nSID == SID_OPENTEMPLATE )
//STRIP001 /*?*/         {
//STRIP001 /*?*/            aPath = SvtPathOptions().GetTemplatePath();
//STRIP001 /*?*/             aPath = aPath.GetToken(0,';');
//STRIP001 /*?*/         }
//STRIP001 /*?*/
//STRIP001 /*?*/         ULONG nErr = sfx2::FileOpenDialog_Impl(
//STRIP001 /*?*/                 WB_OPEN | SFXWB_MULTISELECTION | SFXWB_SHOWVERSIONS, *(SfxObjectFactory*)pDummy, pURLList, aFilter, pSet, aPath );
//STRIP001 /*?*/
//STRIP001 /*?*/         if ( nErr == ERRCODE_ABORT )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             delete pURLList;
//STRIP001 /*?*/             return;
//STRIP001 /*?*/         }
//STRIP001 /*?*/
//STRIP001 /*?*/         rReq.SetArgs( *(SfxAllItemSet*)pSet );
//STRIP001 /*?*/         if (aFilter.Len() >0 )
//STRIP001 /*?*/             rReq.AppendItem( SfxStringItem( SID_FILTER_NAME, aFilter ) );
//STRIP001 /*?*/         rReq.AppendItem( SfxStringItem( SID_TARGETNAME, String::CreateFromAscii("_default") ) );
//STRIP001 /*?*/         rReq.AppendItem( SfxStringItem( SID_REFERER, String::CreateFromAscii(SFX_REFERER_USER) ) );
//STRIP001 /*?*/         delete pSet;
//STRIP001 /*?*/
//STRIP001 /*?*/         if ( pURLList->Count() > 1 )
//STRIP001 /*?*/         {
//STRIP001 /*?*/            if ( nSID == SID_OPENTEMPLATE )
//STRIP001 /*?*/                rReq.AppendItem( SfxBoolItem( SID_TEMPLATE, FALSE ) );
//STRIP001 /*?*/
//STRIP001 /*?*/             for ( USHORT i = 0; i < pURLList->Count(); ++i )
//STRIP001 /*?*/             {
//STRIP001 /*?*/                 String aURL = *(pURLList->GetObject(i));
//STRIP001 /*?*/                 rReq.RemoveItem( SID_FILE_NAME );
//STRIP001 /*?*/                 rReq.AppendItem( SfxStringItem( SID_FILE_NAME, aURL ) );
//STRIP001 /*?*/
//STRIP001 /*?*/                 // synchron ausf"uhren, damit beim Reschedulen nicht schon das n"achste Dokument
//STRIP001 /*?*/                 // geladen wird
//STRIP001 /*?*/                 GetDispatcher_Impl()->Execute( SID_OPENDOC, SFX_CALLMODE_SYNCHRON, *rReq.GetArgs() );
//STRIP001 /*?*/             }
//STRIP001 /*?*/             delete pURLList;
//STRIP001 /*?*/             return;
//STRIP001 /*?*/         }
//STRIP001 /*?*/         else
//STRIP001 /*?*/         {
//STRIP001 /*?*/             String aURL;
//STRIP001 /*?*/             if ( pURLList->Count() == 1 )
//STRIP001 /*?*/                 aURL = *(pURLList->GetObject(0));
//STRIP001 /*?*/             rReq.AppendItem( SfxStringItem( SID_FILE_NAME, aURL ) );
//STRIP001 /*?*/             delete pURLList;
//STRIP001 /*?*/         }
//STRIP001 /*?*/     }
//STRIP001 /*?*/
//STRIP001 /*?*/     BOOL bHyperlinkUsed = FALSE;
//STRIP001 /*?*/
//STRIP001 /*?*/    if ( SID_OPENURL == nSID )
//STRIP001 /*?*/    {
//STRIP001 /*?*/         // SID_OPENURL does the same as SID_OPENDOC!
//STRIP001 /*?*/        rReq.SetSlot( SID_OPENDOC );
//STRIP001 /*?*/        nSID = SID_OPENDOC;
//STRIP001 /*?*/    }
//STRIP001 /*?*/     else if ( nSID == SID_OPENTEMPLATE )
//STRIP001 /*?*/     {
//STRIP001 /*?*/         rReq.AppendItem( SfxBoolItem( SID_TEMPLATE, FALSE ) );
//STRIP001 /*?*/     }
//STRIP001 /*?*/     // pass URL to OS by using ShellExecuter or open it internal
//STRIP001 /*?*/     // if it seams to be an own format.
    /* Attention!
            There exist two possibilities to open hyperlinks:
            a) using SID_OPENHYPERLINK (new)
            b) using SID_BROWSE        (old)
     */
//STRIP001 /*?*/     else if ( nSID == SID_OPENHYPERLINK )
//STRIP001 /*?*/     {
//STRIP001 /*?*/         rReq.SetSlot( SID_OPENDOC );
//STRIP001 /*?*/         nSID = SID_OPENDOC;
//STRIP001 /*?*/         bHyperlinkUsed = TRUE;
//STRIP001 /*?*/     }
//STRIP001 /*?*/
//STRIP001 /*?*/     // no else here! It's optional ...
//STRIP001 /*?*/     if (!bHyperlinkUsed)
//STRIP001 /*?*/     {
//STRIP001 /*?*/         SFX_REQUEST_ARG(rReq, pHyperLinkUsedItem, SfxBoolItem, SID_BROWSE, FALSE);
//STRIP001 /*?*/         if ( pHyperLinkUsedItem )
//STRIP001 /*?*/             bHyperlinkUsed = pHyperLinkUsedItem->GetValue();
//STRIP001 /*?*/         // no "official" item, so remove it from ItemSet before using UNO-API
//STRIP001 /*?*/         rReq.RemoveItem( SID_BROWSE );
//STRIP001 /*?*/     }
//STRIP001 /*?*/
//STRIP001 /*?*/    SFX_REQUEST_ARG( rReq, pFileName, SfxStringItem, SID_FILE_NAME, FALSE );
//STRIP001 /*?*/    String aFileName = pFileName->GetValue();
//STRIP001 /*?*/
//STRIP001 /*?*/     String aReferer;
//STRIP001 /*?*/     SFX_REQUEST_ARG( rReq, pRefererItem, SfxStringItem, SID_REFERER, FALSE );
//STRIP001 /*?*/     if ( pRefererItem )
//STRIP001 /*?*/         aReferer = pRefererItem->GetValue();
//STRIP001 /*?*/
//STRIP001 /*?*/     SFX_REQUEST_ARG( rReq, pFileFlagsItem, SfxStringItem, SID_OPTIONS, FALSE);
//STRIP001 /*?*/     if ( pFileFlagsItem )
//STRIP001 /*?*/     {
//STRIP001 /*?*/         String aFileFlags = pFileFlagsItem->GetValue();
//STRIP001 /*?*/         aFileFlags.ToUpperAscii();
//STRIP001 /*?*/         if ( STRING_NOTFOUND != aFileFlags.Search( 0x0054 ) )               // T = 54h
//STRIP001 /*?*/        {
//STRIP001 /*?*/            rReq.RemoveItem( SID_TEMPLATE );
//STRIP001 /*?*/             rReq.AppendItem( SfxBoolItem( SID_TEMPLATE, TRUE ) );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/         if ( STRING_NOTFOUND != aFileFlags.Search( 0x0048 ) )               // H = 48h
//STRIP001 /*?*/        {
//STRIP001 /*?*/            rReq.RemoveItem( SID_HIDDEN );
//STRIP001 /*?*/             rReq.AppendItem( SfxBoolItem( SID_HIDDEN, TRUE ) );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/         if ( STRING_NOTFOUND != aFileFlags.Search( 0x0052 ) )               // R = 52h
//STRIP001 /*?*/        {
//STRIP001 /*?*/            rReq.RemoveItem( SID_DOC_READONLY );
//STRIP001 /*?*/             rReq.AppendItem( SfxBoolItem( SID_DOC_READONLY, TRUE ) );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/         if ( STRING_NOTFOUND != aFileFlags.Search( 0x0042 ) )               // B = 42h
//STRIP001 /*?*/        {
//STRIP001 /*?*/            rReq.RemoveItem( SID_PREVIEW );
//STRIP001 /*?*/             rReq.AppendItem( SfxBoolItem( SID_PREVIEW, TRUE ) );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/         if ( STRING_NOTFOUND != aFileFlags.Search( 0x0053 ) )               // S = 53h
//STRIP001 /*?*/        {
//STRIP001 /*?*/            // not supported anymore
//STRIP001 /*?*/            //rReq.RemoveItem( SID_SILENT );
//STRIP001 /*?*/             //rReq.AppendItem( SfxBoolItem( SID_SILENT, TRUE ) );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        rReq.RemoveItem( SID_OPTIONS );
//STRIP001 /*?*/     }
//STRIP001 /*?*/
//STRIP001 /*?*/    // Mark without URL cannot be handled by hyperlink code
//STRIP001 /*?*/    if ( bHyperlinkUsed && aFileName.Len() && aFileName.GetChar(0) != '#' )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        Reference< ::com::sun::star::document::XTypeDetection > xTypeDetection(
//STRIP001 /*?*/                                                                    ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(
//STRIP001 /*?*/                                                                    ::rtl::OUString::createFromAscii( "com.sun.star.comp.framework.TypeDetection" )),
//STRIP001 /*?*/                                                                    UNO_QUERY );
//STRIP001 /*?*/        if ( xTypeDetection.is() )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            URL             aURL;
//STRIP001 /*?*/            ::rtl::OUString aTypeName;
//STRIP001 /*?*/
//STRIP001 /*?*/            aURL.Complete = aFileName;
//STRIP001 /*?*/            Reference < XURLTransformer > xTrans( ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(
//STRIP001 /*?*/                                                    ::rtl::OUString::createFromAscii("com.sun.star.util.URLTransformer" )), UNO_QUERY );
//STRIP001 /*?*/            xTrans->parseStrict( aURL );
//STRIP001 /*?*/
//STRIP001 /*?*/            INetProtocol aINetProtocol = INetURLObject( aURL.Complete ).GetProtocol();
//STRIP001 /*?*/            SvtExtendedSecurityOptions aExtendedSecurityOptions;
//STRIP001 /*?*/            SvtExtendedSecurityOptions::OpenHyperlinkMode eMode = aExtendedSecurityOptions.GetOpenHyperlinkMode();
//STRIP001 /*?*/            if ( eMode == SvtExtendedSecurityOptions::OPEN_WITHSECURITYCHECK )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                if ( aINetProtocol == INET_PROT_FILE )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    // Check if file URL is a directory. This is not insecure!
//STRIP001 /*?*/                    osl::Directory aDir( aURL.Main );
//STRIP001 /*?*/                    sal_Bool bIsDir = ( aDir.open() == osl::Directory::E_None );
//STRIP001 /*?*/
//STRIP001 /*?*/                    if ( !bIsDir && !aExtendedSecurityOptions.IsSecureHyperlink( aURL.Complete ))
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        // Security check for local files depending on the extension
//STRIP001 /*?*/                        vos::OGuard aGuard( Application::GetSolarMutex() );
//STRIP001 /*?*/                        Window *pWindow = SFX_APP()->GetTopWindow();
//STRIP001 /*?*/
//STRIP001 /*?*/                        String aSecurityWarningBoxTitle( SfxResId( RID_SECURITY_WARNING_TITLE ));
//STRIP001 /*?*/                        WarningBox  aSecurityWarningBox( pWindow, SfxResId( RID_SECURITY_WARNING_HYPERLINK ));
//STRIP001 /*?*/                        aSecurityWarningBox.SetText( aSecurityWarningBoxTitle );
//STRIP001 /*?*/
//STRIP001 /*?*/                        // Replace %s with the real file name
//STRIP001 /*?*/                        String aMsgText = aSecurityWarningBox.GetMessText();
//STRIP001 /*?*/                        String aMainURL( aURL.Main );
//STRIP001 /*?*/                        String aFileName;
//STRIP001 /*?*/
//STRIP001 /*?*/                        utl::LocalFileHelper::ConvertURLToPhysicalName( aMainURL, aFileName );
//STRIP001 /*?*/                        aMsgText.SearchAndReplaceAscii( "%s", aFileName );
//STRIP001 /*?*/                        aSecurityWarningBox.SetMessText( aMsgText );
//STRIP001 /*?*/
//STRIP001 /*?*/                        if( aSecurityWarningBox.Execute() == RET_NO )
//STRIP001 /*?*/                            return;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/            else if ( eMode == SvtExtendedSecurityOptions::OPEN_NEVER )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                return;
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            aTypeName = xTypeDetection->queryTypeByURL( aURL.Main );
//STRIP001 /*?*/            SfxFilterMatcher& rMatcher = SFX_APP()->GetFilterMatcher();
//STRIP001 /*?*/            const SfxFilter* pFilter = rMatcher.GetFilter4EA( aTypeName );
//STRIP001 /*?*/            if ( !pFilter || !( pFilter->IsOwnFormat() ))
//STRIP001 /*?*/            {
//STRIP001 /*?*/                // hyperlink does not link to known type => special handling (http, ftp) browser and (file) OS
//STRIP001 /*?*/                Reference< XSystemShellExecute > xSystemShellExecute( ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(
//STRIP001 /*?*/                                                    ::rtl::OUString::createFromAscii( "com.sun.star.system.SystemShellExecute" )), UNO_QUERY );
//STRIP001 /*?*/                if ( xSystemShellExecute.is() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    if ( aINetProtocol == INET_PROT_FTP ||
//STRIP001 /*?*/                         aINetProtocol == INET_PROT_HTTP ||
//STRIP001 /*?*/                         aINetProtocol == INET_PROT_HTTPS )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        try
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            // start browser
//STRIP001 /*?*/                            ::rtl::OUString aURLString( aURL.Complete );
//STRIP001 /*?*/                            xSystemShellExecute->execute( aURLString, ::rtl::OUString(), SystemShellExecuteFlags::DEFAULTS );
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                        catch ( ::com::sun::star::lang::IllegalArgumentException& )
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            vos::OGuard aGuard( Application::GetSolarMutex() );
//STRIP001 /*?*/                             Window *pWindow = SFX_APP()->GetTopWindow();
//STRIP001 /*?*/                            ErrorBox( pWindow, SfxResId( MSG_ERR_WEBBROWSER_NOT_STARTED )).Execute();
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                        catch ( ::com::sun::star::system::SystemShellExecuteException& )
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            vos::OGuard aGuard( Application::GetSolarMutex() );
//STRIP001 /*?*/                             Window *pWindow = SFX_APP()->GetTopWindow();
//STRIP001 /*?*/                            ErrorBox( pWindow, SfxResId( MSG_ERR_WEBBROWSER_NOT_STARTED )).Execute();
//STRIP001 /*?*/                        }
//STRIP001 /*?*/
//STRIP001 /*?*/                        return;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    else if ( aINetProtocol == INET_PROT_FILE )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        BOOL bLoadInternal = FALSE;
//STRIP001 /*?*/
//STRIP001 /*?*/                         // security reservation: => we have to check the referer before executing
//STRIP001 /*?*/                         if ( SFX_APP()->IsSecureURL( String(), &aReferer ) )
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            ::rtl::OUString aSysPathFileName;
//STRIP001 /*?*/                            ::osl::FileBase::RC nError = ::osl::FileBase::getSystemPathFromFileURL( aURL.Complete, aSysPathFileName );
//STRIP001 /*?*/                            if ( nError == ::osl::FileBase::E_None )
//STRIP001 /*?*/                            {
//STRIP001 /*?*/                                try
//STRIP001 /*?*/                                {
//STRIP001 /*?*/                                    // give os this file
//STRIP001 /*?*/                                    xSystemShellExecute->execute( aSysPathFileName, ::rtl::OUString(), SystemShellExecuteFlags::DEFAULTS );
//STRIP001 /*?*/                                }
//STRIP001 /*?*/                                catch ( ::com::sun::star::lang::IllegalArgumentException& )
//STRIP001 /*?*/                                {
//STRIP001 /*?*/                                    vos::OGuard aGuard( Application::GetSolarMutex() );
//STRIP001 /*?*/                                     Window *pWindow = SFX_APP()->GetTopWindow();
//STRIP001 /*?*/                                    ErrorBox( pWindow, SfxResId( MSG_ERR_EXTERNAL_APP_NOT_FOUND )).Execute();
//STRIP001 /*?*/                                }
//STRIP001 /*?*/                                catch ( ::com::sun::star::system::SystemShellExecuteException& )
//STRIP001 /*?*/                                {
//STRIP001 /*?*/                                    if ( !pFilter )
//STRIP001 /*?*/                                    {
//STRIP001 /*?*/                                        vos::OGuard aGuard( Application::GetSolarMutex() );
//STRIP001 /*?*/                                        Window *pWindow = SFX_APP()->GetTopWindow();
//STRIP001 /*?*/                                        ErrorBox( pWindow, SfxResId( MSG_ERR_EXTERNAL_APP_NOT_FOUND )).Execute();
//STRIP001 /*?*/                                    }
//STRIP001 /*?*/                                    else
//STRIP001 /*?*/                                    {
//STRIP001 /*?*/                                        rReq.RemoveItem( SID_TARGETNAME );
//STRIP001 /*?*/                                        rReq.AppendItem( SfxStringItem( SID_TARGETNAME, String::CreateFromAscii("_default") ) );
//STRIP001 /*?*/                                        bLoadInternal = TRUE;
//STRIP001 /*?*/                                    }
//STRIP001 /*?*/                                }
//STRIP001 /*?*/                            }
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                        else
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            SfxErrorContext aCtx( ERRCTX_SFX_OPENDOC, aURL.Complete );
//STRIP001 /*?*/                            ErrorHandler::HandleError( ERRCODE_IO_ACCESSDENIED );
//STRIP001 /*?*/                        }
//STRIP001 /*?*/
//STRIP001 /*?*/                        if ( !bLoadInternal )
//STRIP001 /*?*/                            return;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    else if ( aINetProtocol == INET_PROT_MAILTO )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        // don't dispatch mailto hyperlink to desktop dispatcher
//STRIP001 /*?*/                        rReq.RemoveItem( SID_TARGETNAME );
//STRIP001 /*?*/                        rReq.AppendItem( SfxStringItem( SID_TARGETNAME, String::CreateFromAscii("_self") ) );
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/            else
//STRIP001 /*?*/            {
//STRIP001 /*?*/                 // hyperlink document must be loaded into a new frame
//STRIP001 /*?*/                rReq.RemoveItem( SID_TARGETNAME );
//STRIP001 /*?*/                 rReq.AppendItem( SfxStringItem( SID_TARGETNAME, String::CreateFromAscii("_default") ) );
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/     if ( !SFX_APP()->IsSecureURL( aFileName, &aReferer ) )
//STRIP001 /*?*/     {
//STRIP001 /*?*/         SfxErrorContext aCtx( ERRCTX_SFX_OPENDOC, aFileName );
//STRIP001 /*?*/         ErrorHandler::HandleError( ERRCODE_IO_ACCESSDENIED );
//STRIP001 /*?*/         return;
//STRIP001 /*?*/     }
//STRIP001 /*?*/
//STRIP001 /*?*/     SFX_REQUEST_ARG(rReq, pFrmItem, SfxFrameItem, SID_DOCFRAME, FALSE);
//STRIP001 /*?*/    SfxFrame *pFrame = NULL;
//STRIP001 /*?*/    if ( pFrmItem )
//STRIP001 /*?*/        pFrame = pFrmItem->GetFrame();
//STRIP001 /*?*/     else if ( SfxViewFrame::Current() )
//STRIP001 /*?*/         pFrame = SfxViewFrame::Current()->GetFrame();
//STRIP001 /*?*/
//STRIP001 /*?*/     // check if caller has set a callback
//STRIP001 /*?*/     SFX_REQUEST_ARG(rReq, pLinkItem, SfxLinkItem, SID_DONELINK, FALSE );
//STRIP001 /*?*/
//STRIP001 /*?*/    // remove from Itemset, because it confuses the parameter transformation
//STRIP001 /*?*/    if ( pLinkItem )
//STRIP001 /*?*/        pLinkItem = (SfxLinkItem*) pLinkItem->Clone();
//STRIP001 /*?*/
//STRIP001 /*?*/    rReq.RemoveItem( SID_DONELINK );
//STRIP001 /*?*/
//STRIP001 /*?*/     // check if caller wants to create a view
//STRIP001 /*?*/    BOOL bCreateView = TRUE;
//STRIP001 /*?*/    SFX_REQUEST_ARG( rReq, pCreateViewItem, SfxBoolItem, SID_VIEW, FALSE );
//STRIP001 /*?*/    if ( pCreateViewItem && !pCreateViewItem->GetValue() )
//STRIP001 /*?*/        bCreateView = FALSE;
//STRIP001 /*?*/
//STRIP001 /*?*/     // we can't load without a view - switch to hidden view
//STRIP001 /*?*/     if ( !bCreateView )
//STRIP001 /*?*/         rReq.AppendItem( SfxBoolItem( SID_HIDDEN, TRUE ) );
//STRIP001 /*?*/
//STRIP001 /*?*/     // check if the view must be hidden
//STRIP001 /*?*/     BOOL bHidden = FALSE;
//STRIP001 /*?*/     SFX_REQUEST_ARG(rReq, pHidItem, SfxBoolItem, SID_HIDDEN, FALSE);
//STRIP001 /*?*/     if ( pHidItem )
//STRIP001 /*?*/         bHidden = pHidItem->GetValue();
//STRIP001 /*?*/
//STRIP001 /*?*/     // This request is a UI call. We have to set the right values inside the MediaDescriptor
//STRIP001 /*?*/     // for: InteractionHandler, StatusIndicator, MacroExecutionMode and DocTemplate.
//STRIP001 /*?*/     // But we have to look for already existing values or for real hidden requests.
//STRIP001 /*?*/     SFX_REQUEST_ARG(rReq, pPreviewItem, SfxBoolItem, SID_PREVIEW, FALSE);
//STRIP001 /*?*/     if (!bHidden && ( !pPreviewItem || !pPreviewItem->GetValue() ) )
//STRIP001 /*?*/     {
//STRIP001 /*?*/         SFX_REQUEST_ARG(rReq, pInteractionItem, SfxUnoAnyItem, SID_INTERACTIONHANDLER, FALSE);
//STRIP001 /*?*/         SFX_REQUEST_ARG(rReq, pMacroExecItem  , SfxUInt16Item, SID_MACROEXECMODE     , FALSE);
//STRIP001 /*?*/         SFX_REQUEST_ARG(rReq, pDocTemplateItem, SfxUInt16Item, SID_UPDATEDOCMODE     , FALSE);
//STRIP001 /*?*/
//STRIP001 /*?*/         if (!pInteractionItem)
//STRIP001 /*?*/         {
//STRIP001 /*?*/             Reference < ::com::sun::star::task::XInteractionHandler > xHdl( ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(::rtl::OUString::createFromAscii("com.sun.star.comp.uui.UUIInteractionHandler")), UNO_QUERY );
//STRIP001 /*?*/             if (xHdl.is())
//STRIP001 /*?*/                 rReq.AppendItem( SfxUnoAnyItem(SID_INTERACTIONHANDLER,::com::sun::star::uno::makeAny(xHdl)) );
//STRIP001 /*?*/         }
//STRIP001 /*?*/         if (!pMacroExecItem)
//STRIP001 /*?*/             rReq.AppendItem( SfxUInt16Item(SID_MACROEXECMODE,::com::sun::star::document::MacroExecMode::USE_CONFIG) );
//STRIP001 /*?*/         if (!pDocTemplateItem)
//STRIP001 /*?*/             rReq.AppendItem( SfxUInt16Item(SID_UPDATEDOCMODE,::com::sun::star::document::UpdateDocMode::ACCORDING_TO_CONFIG) );
//STRIP001 /*?*/     }
//STRIP001 /*?*/
//STRIP001 /*?*/     // convert items to properties for framework API calls
//STRIP001 /*?*/     Sequence < PropertyValue > aArgs;
//STRIP001 /*?*/     TransformItems( SID_OPENDOC, *rReq.GetArgs(), aArgs );
//STRIP001 /*?*/
//STRIP001 /*?*/     // extract target name
//STRIP001 /*?*/     ::rtl::OUString aTarget;
//STRIP001 /*?*/     SFX_REQUEST_ARG(rReq, pTargetItem, SfxStringItem, SID_TARGETNAME, FALSE);
//STRIP001 /*?*/     if ( pTargetItem )
//STRIP001 /*?*/         aTarget = pTargetItem->GetValue();
//STRIP001 /*?*/     else
//STRIP001 /*?*/     {
//STRIP001 /*?*/         SFX_REQUEST_ARG( rReq, pNewViewItem, SfxBoolItem, SID_OPEN_NEW_VIEW, FALSE );
//STRIP001 /*?*/         if ( pNewViewItem && pNewViewItem->GetValue() )
//STRIP001 /*?*/             aTarget = String::CreateFromAscii("_blank" );
//STRIP001 /*?*/     }
//STRIP001 /*?*/
//STRIP001 /*?*/     if ( bHidden )
//STRIP001 /*?*/         aTarget = String::CreateFromAscii("_blank");
//STRIP001 /*?*/
//STRIP001 /*?*/     BOOL bIsBlankTarget = ( aTarget.compareToAscii( "_blank" ) == COMPARE_EQUAL || aTarget.compareToAscii( "_default" ) == COMPARE_EQUAL );
//STRIP001 /*?*/     Reference < XController > xController;
//STRIP001 /*?*/     if ( ( !bIsBlankTarget && pFrame ) || pLinkItem || !rReq.IsSynchronCall() )
//STRIP001 /*?*/     {
//STRIP001 /*?*/         // if a frame is given, it must be used for the starting point of the targetting mechanism
//STRIP001 /*?*/         // this code is also used if asynchron loading is possible, because loadComponent always is synchron
//STRIP001 /*?*/         Reference < XFrame > xFrame;
//STRIP001 /*?*/         if ( pFrame )
//STRIP001 /*?*/             xFrame = pFrame->GetFrameInterface();
//STRIP001 /*?*/         else
//STRIP001 /*?*/             xFrame = Reference < XFrame >( ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(::rtl::OUString::createFromAscii("com.sun.star.frame.Desktop")), UNO_QUERY );
//STRIP001 /*?*/
//STRIP001 /*?*/         // make URL ready
//STRIP001 /*?*/         URL aURL;
//STRIP001 /*?*/         SFX_REQUEST_ARG( rReq, pFileNameItem, SfxStringItem, SID_FILE_NAME, FALSE );
//STRIP001 /*?*/         String aFileName = pFileNameItem->GetValue();
//STRIP001 /*?*/
//STRIP001 /*?*/         INetURLObject aObj;
//STRIP001 /*?*/         SfxObjectShell* pCur = pFrame ? pFrame->GetCurrentDocument() : 0;
//STRIP001 /*?*/         if ( !pCur )
//STRIP001 /*?*/             pCur = SfxObjectShell::Current();
//STRIP001 /*?*/         if( aFileName.Len() && aFileName.GetChar(0) == '#' ) // Mark without URL
//STRIP001 /*?*/         {
//STRIP001 /*?*/             SfxViewFrame *pView = pFrame ? pFrame->GetCurrentViewFrame() : 0;
//STRIP001 /*?*/             if ( !pView )
//STRIP001 /*?*/                 pView = SfxViewFrame::Current();
//STRIP001 /*?*/             pView->GetViewShell()->JumpToMark( aFileName.Copy(1) );
//STRIP001 /*?*/             rReq.SetReturnValue( SfxViewFrameItem( 0, pView ) );
//STRIP001 /*?*/             return;
//STRIP001 /*?*/         }
//STRIP001 /*?*/
//STRIP001 /*?*/         aURL.Complete = aFileName;
//STRIP001 /*?*/         Reference < XURLTransformer > xTrans( ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance( ::rtl::OUString::createFromAscii("com.sun.star.util.URLTransformer" )), UNO_QUERY );
//STRIP001 /*?*/         xTrans->parseStrict( aURL );
//STRIP001 /*?*/
//STRIP001 /*?*/         // load document using dispatch framework
//STRIP001 /*?*/         if( pLinkItem || rReq.IsSynchronCall() )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             // if loading must be done synchron, we must wait for completion to get a return value
//STRIP001 /*?*/             // find frame by myself; I must konw the exact frame to get the controller for the return value from it
//STRIP001 /*?*/             if( aTarget.getLength() )
//STRIP001 /*?*/                 xFrame = xFrame->findFrame( aTarget, FrameSearchFlag::ALL );
//STRIP001 /*?*/
//STRIP001 /*?*/             // targeting has been resolved, so target name must not be used in queryDispatch
//STRIP001 /*?*/             Reference < XDispatchProvider > xProv( xFrame, UNO_QUERY );
//STRIP001 /*?*/             Reference < XDispatch > xDisp = xProv.is() ? xProv->queryDispatch( aURL, ::rtl::OUString(), 0 ) : Reference < XDispatch >();
//STRIP001 /*?*/             if ( xDisp.is() )
//STRIP001 /*?*/             {
//STRIP001 /*?*/                 Reference < XNotifyingDispatch > xNot( xDisp, UNO_QUERY );
//STRIP001 /*?*/                 if ( xNot.is() )
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     // create listener for notification of load success or fail
//STRIP001 /*?*/                     SfxOpenDocStatusListener_Impl* pListener = new SfxOpenDocStatusListener_Impl();
//STRIP001 /*?*/                     pListener->acquire();
//STRIP001 /*?*/                     xNot->dispatchWithNotification( aURL, aArgs, pListener );
//STRIP001 /*?*/
//STRIP001 /*?*/                     // stay on the stack until result has been notified
//STRIP001 /*?*/                     while ( !pListener->bFinished )
//STRIP001 /*?*/                         Application::Yield();
//STRIP001 /*?*/
//STRIP001 /*?*/                     if ( pListener->bSuccess )
//STRIP001 /*?*/                         // successful loading, get loaded controller
//STRIP001 /*?*/                         xController = xFrame->getController();
//STRIP001 /*?*/
//STRIP001 /*?*/                     pListener->release();
//STRIP001 /*?*/                 }
//STRIP001 /*?*/             }
//STRIP001 /*?*/
//STRIP001 /*?*/             if ( !xController.is() && bIsBlankTarget )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                 // a blank frame would have been created in findFrame; in this case I am the owner and I must delete it
//STRIP001 /*?*/                Reference < XCloseable > xClose( xFrame, UNO_QUERY );
//STRIP001 /*?*/                if ( xClose.is() )
//STRIP001 /*?*/                    xClose->close(sal_True);
//STRIP001 /*?*/                else
//STRIP001 /*?*/                    xFrame->dispose();
//STRIP001 /*?*/            }
//STRIP001 /*?*/         }
//STRIP001 /*?*/         else
//STRIP001 /*?*/         {
//STRIP001 /*?*/             // otherwise we just dispatch and that's it
//STRIP001 /*?*/             Reference < XDispatchProvider > xProv( xFrame, UNO_QUERY );
//STRIP001 /*?*/             Reference < XDispatch > xDisp = xProv.is() ? xProv->queryDispatch( aURL, aTarget, FrameSearchFlag::ALL ) : Reference < XDispatch >();;
//STRIP001 /*?*/             if ( xDisp.is() )
//STRIP001 /*?*/                 xDisp->dispatch( aURL, aArgs );
//STRIP001 /*?*/         }
//STRIP001 /*?*/     }
//STRIP001 /*?*/     else
//STRIP001 /*?*/     {
//STRIP001 /*?*/         // synchron loading without a given frame or as blank frame
//STRIP001 /*?*/         SFX_REQUEST_ARG( rReq, pFileNameItem, SfxStringItem, SID_FILE_NAME, FALSE );
//STRIP001 /*?*/         Reference < XComponentLoader > xDesktop( ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(::rtl::OUString::createFromAscii("com.sun.star.frame.Desktop")), UNO_QUERY ); //STRIP002 ::comphelper::getProcessServiceFactory()->createInstance(::rtl::OUString::createFromAscii("com.sun.star.frame.Desktop")), UNO_QUERY );
//STRIP001 /*?*/         Reference < XComponent > xComp = xDesktop->loadComponentFromURL( pFileNameItem->GetValue(), aTarget, 0, aArgs );
//STRIP001 /*?*/        Reference < XModel > xModel( xComp, UNO_QUERY );
//STRIP001 /*?*/         if ( xModel.is() )
//STRIP001 /*?*/             xController = xModel->getCurrentController();
//STRIP001 /*?*/        else
//STRIP001 /*?*/            xController = Reference < XController >( xComp, UNO_QUERY );
//STRIP001 /*?*/     }
//STRIP001 /*?*/ /*
//STRIP001 /*?*/    if ( bHidden )
//STRIP001 /*?*/         aTarget = String::CreateFromAscii("_blank");
//STRIP001 /*?*/
//STRIP001 /*?*/     // if a frame is given, it must be used for the starting point of the targeting mechanism
//STRIP001 /*?*/     Reference < XFrame > xFrame;
//STRIP001 /*?*/     if ( pFrame )
//STRIP001 /*?*/         xFrame = pFrame->GetFrameInterface();
//STRIP001 /*?*/     else
//STRIP001 /*?*/         xFrame = Reference < XFrame >( ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(::rtl::OUString::createFromAscii("com.sun.star.frame.Desktop")), UNO_QUERY ); //STRIP002 ::comphelper::getProcessServiceFactory()->createInstance(::rtl::OUString::createFromAscii("com.sun.star.frame.Desktop")), UNO_QUERY );
//STRIP001 /*?*/
//STRIP001 /*?*/     if( aFileName.Len() && aFileName.GetChar(0) == '#' )
//STRIP001 /*?*/     {
//STRIP001 /*?*/        // Mark without URL
//STRIP001 /*?*/         SfxViewFrame *pView = pFrame ? pFrame->GetCurrentViewFrame() : 0;
//STRIP001 /*?*/         if ( !pView )
//STRIP001 /*?*/             pView = SfxViewFrame::Current();
//STRIP001 /*?*/         pView->GetViewShell()->JumpToMark( aFileName.Copy(1) );
//STRIP001 /*?*/         rReq.SetReturnValue( SfxViewFrameItem( 0, pView ) );
//STRIP001 /*?*/     }
//STRIP001 /*?*/    else
//STRIP001 /*?*/    {
//STRIP001 /*?*/        // evaluate target name
//STRIP001 /*?*/        try
//STRIP001 /*?*/        {
//STRIP001 /*?*/            Reference < XComponentLoader > xLoader( xFrame, UNO_QUERY );
//STRIP001 /*?*/            Reference < XModel > xModel( xLoader->loadComponentFromURL( aFileName, aTarget, FrameSearchFlag::GLOBAL|FrameSearchFlag::CREATE, aArgs ), UNO_QUERY );
//STRIP001 /*?*/            Reference < XController > xController;
//STRIP001 /*?*/            if ( xModel.is() )
//STRIP001 /*?*/                xController = xModel->getCurrentController();
//STRIP001 /*?*/    */
//STRIP001 /*?*/    if ( xController.is() )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        // try to find the SfxFrame for the controller
//STRIP001 /*?*/        SfxFrame* pFrame = NULL;
//STRIP001 /*?*/        for ( SfxViewShell* pShell = SfxViewShell::GetFirst( 0, FALSE ); pShell; pShell = SfxViewShell::GetNext( *pShell, 0, FALSE ) )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            if ( pShell->GetController() == xController )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                pFrame = pShell->GetViewFrame()->GetFrame();
//STRIP001 /*?*/                break;
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        if ( pFrame )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            SfxObjectShell* pSh = pFrame->GetCurrentDocument();
//STRIP001 /*?*/            DBG_ASSERT( pSh, "Controller without ObjectShell ?!" );
//STRIP001 /*?*/
//STRIP001 /*?*/            if ( bCreateView )
//STRIP001 /*?*/                rReq.SetReturnValue( SfxViewFrameItem( 0, pFrame->GetCurrentViewFrame() ) );
//STRIP001 /*?*/            else
//STRIP001 /*?*/                rReq.SetReturnValue( SfxObjectItem( 0, pSh ) );
//STRIP001 /*?*/
//STRIP001 /*?*/            if( ( bHidden || !bCreateView ) )
//STRIP001 /*?*/                pSh->RestoreNoDelete();
//STRIP001 /*?*/        }
//STRIP001 /*?*/    }
//STRIP001 /*?*/ /*
//STRIP001 /*?*/        }
//STRIP001 /*?*/        catch (::com::sun::star::uno::Exception&)
//STRIP001 /*?*/        {
//STRIP001 /*?*/        }
//STRIP001 /*?*/    }
//STRIP001 /*?*/ */
//STRIP001 /*?*/    if ( pLinkItem )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        SfxPoolItem* pRet = rReq.GetReturnValue()->Clone();
//STRIP001 /*?*/        pLinkItem->GetValue().Call(pRet);
//STRIP001 /*?*/        delete pLinkItem;
//STRIP001 /*?*/    }
/*?*/ }

//--------------------------------------------------------------------

//STRIP001 SfxViewFrame *SfxApplication::CreateView_Impl
//STRIP001 (
//STRIP001     SfxRequest&         rReq,
//STRIP001     SfxObjectShell*     pDoc,
//STRIP001     FASTBOOL            bNewView,   // neue View erzwingen
//STRIP001     FASTBOOL            bHidden
//STRIP001 )
//STRIP001 {
//STRIP001     SfxViewFrame* pFrame = CreateView_Impl( rReq.GetArgs(), pDoc, bNewView, bHidden );
//STRIP001     rReq.SetReturnValue( SfxViewFrameItem( pFrame ) );
//STRIP001     return pFrame;
//STRIP001 }

//STRIP001 SfxViewFrame *SfxApplication::CreateView_Impl
//STRIP001 (
//STRIP001     const SfxItemSet*   pSet,
//STRIP001     SfxObjectShell*     pDoc,
//STRIP001     FASTBOOL            bNewView,   // neue View erzwingen
//STRIP001     FASTBOOL            bHidden
//STRIP001 )
//STRIP001 {
//STRIP001     DBG_MEMTEST();
//STRIP001
//STRIP001     SfxFrame* pFrame = SfxTopFrame::Create( pDoc, 0, bHidden, pSet );
//STRIP001     return pFrame->GetCurrentViewFrame();
//STRIP001 }
}
