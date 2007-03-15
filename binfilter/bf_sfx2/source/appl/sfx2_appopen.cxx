/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_appopen.cxx,v $
 *
 *  $Revision: 1.13 $
 *
 *  last change: $Author: obo $ $Date: 2007-03-15 15:21:31 $
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
#ifndef _SFXECODE_HXX
#include <svtools/sfxecode.hxx>
#endif

#include <svtools/ehdl.hxx>
#include "bf_basic/sbxobj.hxx"
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
#include "objitem.hxx"
#include "objsh.hxx"
#include "objshimp.hxx"
#include "openflag.hxx"
#include "referers.hxx"
#include "request.hxx"
#include "sfxresid.hxx"
#include "viewsh.hxx"
#include "app.hrc"
#include "topfrm.hxx"
#include "appimp.hxx"
#include "appuno.hxx"
#include "objface.hxx"

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
//using namespace sfx2;

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
/*?*/ }

//---------------------------------------------------------------------------

/*?*/ void SfxApplication::OpenDocExec_Impl( SfxRequest& rReq )
/*?*/ {DBG_BF_ASSERT(0, "STRIP");//STRIP001
    /* Attention!
            There exist two possibilities to open hyperlinks:
            a) using SID_OPENHYPERLINK (new)
            b) using SID_BROWSE        (old)
     */
/*?*/ }
}
