/*************************************************************************
 *
 *  $RCSfile: sfx2_docfile.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: obo $ $Date: 2004-05-13 10:18:16 $
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

#include "docfile.hxx"

#include <uno/mapping.hxx>
#include <com/sun/star/task/XInteractionHandler.hpp>
#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/ucb/XContent.hpp>

#ifndef _COM_SUN_STAR_UCB_INTERACTIVEIOEXCEPTION_HPP_
#include <com/sun/star/ucb/InteractiveIOException.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_UNSUPPORTEDDATASINKEXCEPTION_HPP_
#include <com/sun/star/ucb/UnsupportedDataSinkException.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_COMMANDFAILEDEXCEPTION_HPP_
#include <com/sun/star/ucb/CommandFailedException.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_COMMANDABORTEDEXCEPTION_HPP_
#include <com/sun/star/ucb/CommandAbortedException.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_XCOMMANDENVIRONMENT_HPP_
#include <com/sun/star/ucb/XCommandEnvironment.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_XPROGRESSHANDLER_HPP_
#include <com/sun/star/ucb/XProgressHandler.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_XCOMMANDINFO_HPP_
#include <com/sun/star/ucb/XCommandInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XARCHIVER_HPP_
#include <com/sun/star/util/XArchiver.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XOUTPUTSTREAM_HPP_
#include <com/sun/star/io/XOutputStream.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XINPUTSTREAM_HPP_
#include <com/sun/star/io/XInputStream.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XSTREAMLISTENER_HPP_
#include <com/sun/star/io/XStreamListener.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XSEEKABLE_HPP_
#include <com/sun/star/io/XSeekable.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_XSIMPLEFILEACCESS_HPP_
#include <com/sun/star/ucb/XSimpleFileAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XINITIALIZATION_HPP_
#include <com/sun/star/lang/XInitialization.hpp>
#endif
#ifndef  _COM_SUN_STAR_UCB_INSERTCOMMANDARGUMENT_HPP_
#include <com/sun/star/ucb/InsertCommandArgument.hpp>
#endif
#ifndef  _COM_SUN_STAR_UCB_NAMECLASH_HPP_
#include <com/sun/star/ucb/NameClash.hpp>
#endif
#ifndef  _COM_SUN_STAR_UCB_TRANSFERINFO_HPP_
#include <com/sun/star/ucb/TransferInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_OPENCOMMANDARGUMENT2_HPP_
#include <com/sun/star/ucb/OpenCommandArgument2.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_OPENMODE_HPP_
#include <com/sun/star/ucb/OpenMode.hpp>
#endif
#ifndef _CPPUHELPER_IMPLBASE1_HXX_
#include <cppuhelper/implbase1.hxx>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
#ifndef _ZCODEC_HXX
#include <tools/zcodec.hxx>
#endif
#ifndef _CACHESTR_HXX //autogen
#include <tools/cachestr.hxx>
#endif
#ifndef _URLOBJ_HXX //autogen
#include <tools/urlobj.hxx>
#endif
#ifndef _UNOTOOLS_TEMPFILE_HXX
#include <unotools/tempfile.hxx>
#endif
#ifndef _UNOTOOLS_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif
#ifndef  _UNOTOOLS_STREAMHELPER_HXX_
#include <unotools/streamhelper.hxx>
#endif
#ifndef _UNOTOOLS_LOCALEDATAWRAPPER_HXX
#include <unotools/localedatawrapper.hxx>
#endif
#ifndef _MSGBOX_HXX //autogen
#include <vcl/msgbox.hxx>
#endif
#ifndef _SVSTOR_HXX //autogen
#include <so3/svstor.hxx>
#endif
#ifndef _EXTATTR_HXX
#include <svtools/extattr.hxx>
#endif
#ifndef _SFXSTRITEM_HXX //autogen
#include <svtools/stritem.hxx>
#endif
#ifndef _SFXENUMITEM_HXX //autogen
#include <svtools/eitem.hxx>
#endif
#include <svtools/lckbitem.hxx>
#ifndef _SFXECODE_HXX
#include <svtools/sfxecode.hxx>
#endif
#ifndef _SFXITEMSET_HXX
#include <svtools/itemset.hxx>
#endif
#ifndef _SFXINTITEM_HXX
#include <svtools/intitem.hxx>
#endif
#ifndef _CPPUHELPER_WEAKREF_HXX_
#include <cppuhelper/weakref.hxx>
#endif
#ifndef _CPPUHELPER_IMPLBASE1_HXX_
#include <cppuhelper/implbase1.hxx>
#endif

#define _SVSTDARR_ULONGS
#define _SVSTDARR_STRINGSDTOR
#include <svtools/svstdarr.hxx>

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::ucb;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::io;

#pragma hdrstop

#include <comphelper/processfactory.hxx>
#include <so3/transbnd.hxx> // SvKeyValueIterator
#include <tools/urlobj.hxx>
#include <tools/inetmime.hxx>
#include <unotools/ucblockbytes.hxx>
#include <svtools/pathoptions.hxx>
#include <svtools/asynclink.hxx>
#include <svtools/inettype.hxx>
#include <ucbhelper/contentbroker.hxx>
#include <ucbhelper/commandenvironment.hxx>
#include <unotools/localfilehelper.hxx>
#include <unotools/ucbstreamhelper.hxx>
#include <unotools/ucbhelper.hxx>
#include <unotools/progresshandlerwrap.hxx>
#include <ucbhelper/content.hxx>
#include <sot/stg.hxx>

#include "helper.hxx"
#include "request.hxx"      // SFX_ITEMSET_SET
#include "app.hxx"          // GetFilterMatcher
#include "frame.hxx"        // LoadTargetFrame
#include "fltfnc.hxx"       // SfxFilterMatcher
#include "docfilt.hxx"      // SfxFilter
#include "objsh.hxx"        // CheckOpenMode
#include "docfac.hxx"       // GetFilterContainer
#include "doc.hrc"          // MSG_WARNING_BACKUP, MSG_OPEN_READONLY
#include "openflag.hxx"     // SFX_STREAM_READONLY etc.
#include "sfxresid.hxx"

#include "xmlversion.hxx"

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {

#define MAX_REDIRECT 5

/*N*/ class SfxLockBytesHandler_Impl : public ::utl::UcbLockBytesHandler
/*N*/ {
/*N*/     ULONG           m_nAcquireCount;
/*N*/     SfxMedium*      m_pMedium;
/*N*/     ::vos::OMutex   m_aMutex;
/*N*/ public:
/*N*/                     SfxLockBytesHandler_Impl( SfxMedium* pMedium )
/*N*/                         : m_pMedium( pMedium )
/*N*/                         , m_nAcquireCount( 0 )
/*N*/                     {}
/*N*/
/*N*/     virtual void    Handle( ::utl::UcbLockBytesHandler::LoadHandlerItem nWhich, ::utl::UcbLockBytesRef xLockBytes );
/*N*/     ::vos::OMutex&  GetMutex()
/*N*/                     { return m_aMutex; }
/*N*/     void            ReleaseMedium()
/*N*/                     { m_pMedium = NULL; }
/*N*/ };

/*?*/ SV_DECL_IMPL_REF( SfxLockBytesHandler_Impl );

/*N*/ void SfxLockBytesHandler_Impl::Handle( ::utl::UcbLockBytesHandler::LoadHandlerItem nWhich, ::utl::UcbLockBytesRef xLockBytes )
/*N*/ {
/*N*/     ::vos::OGuard aGuard( m_aMutex );
/*N*/     if ( IsActive() && xLockBytes.Is()&& m_pMedium )
/*N*/     {
/*N*/         switch( nWhich )
/*N*/         {
/*N*/                 break;
/*N*/             case DATA_AVAILABLE :
/*?*/                 m_pMedium->DataAvailable_Impl();
/*N*/                 break;
/*N*/             case DONE :
/*N*/                 m_pMedium->Done_Impl( xLockBytes->GetError() );
/*N*/                 break;
/*N*/             case CANCEL :
/*?*/                 m_pMedium->Cancel_Impl();
/*N*/                 break;
/*N*/             default:
/*N*/                 break;
/*N*/         }
/*N*/     }
/*N*/ }

/*N*/ class UcbLockBytesCancellable_Impl : public SfxCancellable
/*N*/ {
/*N*/     ::utl::UcbLockBytesRef         xLockBytes;
/*N*/
/*N*/ public:
/*N*/                             UcbLockBytesCancellable_Impl( const ::utl::UcbLockBytesRef& rLockBytes, SfxCancelManager* pManager, const String& rTitle )
/*N*/                                 : SfxCancellable( pManager, rTitle )
/*N*/                                 , xLockBytes( rLockBytes )
/*N*/                             {}

/*N*/     virtual void            Cancel();
/*N*/ };

/*N*/ void UcbLockBytesCancellable_Impl::Cancel()
/*N*/ {
/*N*/     xLockBytes->Cancel();
/*N*/ }

/*N*/ class SfxMediumHandler_Impl : public ::cppu::WeakImplHelper1< ::com::sun::star::task::XInteractionHandler >
/*N*/ {
/*N*/     ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionHandler > m_xInter;
/*N*/
/*N*/ public:
/*N*/     virtual void SAL_CALL handle( const ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionRequest >& xRequest )
/*N*/             throw( ::com::sun::star::uno::RuntimeException );
/*N*/
/*N*/     SfxMediumHandler_Impl( ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionHandler > xInteraction )
/*N*/         : m_xInter( xInteraction )
/*N*/         {}
/*N*/
/*N*/     ~SfxMediumHandler_Impl();
/*N*/ };

/*N*/ SfxMediumHandler_Impl::~SfxMediumHandler_Impl()
/*N*/ {
/*N*/ }

/*N*/ void SAL_CALL SfxMediumHandler_Impl::handle( const ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionRequest >& xRequest )
/*N*/         throw( ::com::sun::star::uno::RuntimeException )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if( !m_xInter.is() )
//STRIP001      return;
//STRIP001
//STRIP001     ::com::sun::star::uno::Any aRequest = xRequest->getRequest();
//STRIP001     ::com::sun::star::ucb::InteractiveIOException aIoException;
//STRIP001     ::com::sun::star::ucb::UnsupportedDataSinkException aSinkException;
//STRIP001     if ( (aRequest >>= aIoException) && ( aIoException.Code == IOErrorCode_ACCESS_DENIED || aIoException.Code == IOErrorCode_LOCKING_VIOLATION ) )
//STRIP001         return;
//STRIP001     else
//STRIP001     if ( aRequest >>= aSinkException )
//STRIP001         return;
//STRIP001     else
//STRIP001         m_xInter->handle( xRequest );
/*N*/ }

/*?*/ String ConvertDateTime_Impl(const SfxStamp &rTime, const LocaleDataWrapper& rWrapper);

//----------------------------------------------------------------
/*N*/ SfxPoolCancelManager::SfxPoolCancelManager( SfxCancelManager* pParent, const String& rName )
/*N*/     : SfxCancelManager( pParent ),
/*N*/       SfxCancellable( pParent ? pParent : this, rName ),
/*N*/       wParent( pParent )
/*N*/ {
/*N*/     if( pParent )
/*N*/     {
/*N*/         StartListening( *this );
/*N*/         SetManager( 0 );
/*N*/     }
/*N*/ }

//----------------------------------------------------------------
/*N*/ SfxPoolCancelManager::~SfxPoolCancelManager()
/*N*/ {
/*N*/     for( sal_uInt16 nPos = GetCancellableCount(); nPos--; )
/*N*/     {
/*N*/         // nicht an Parent uebernehmen!
/*?*/         SfxCancellable* pCbl = GetCancellable( nPos );
/*?*/         if ( pCbl )
/*?*/             pCbl->SetManager( 0 );
/*N*/     }
/*N*/ }


//----------------------------------------------------------------
/*N*/ void SfxPoolCancelManager::Notify( SfxBroadcaster& rBC, const SfxHint& rHint )
/*N*/ {
/*N*/     if( !GetCancellableCount() ) SetManager( 0 );
/*N*/     else if( !GetManager() )
/*N*/     {
/*N*/         if( !wParent.Is() ) wParent = SFX_APP()->GetCancelManager();
/*N*/         SetManager( wParent );
/*N*/     }
/*N*/ }

//----------------------------------------------------------------
/*N*/ void SfxPoolCancelManager::Cancel()
/*N*/ {
/*N*/     SfxPoolCancelManagerRef xThis = this;
/*N*/     for( sal_uInt16 nPos = GetCancellableCount(); nPos--; )
/*N*/     {
/*?*/         SfxCancellable* pCbl = GetCancellable( nPos );
/*?*/         // Wenn wir nicht im Button stehen
/*?*/         if( pCbl && pCbl != this )
/*?*/             pCbl->Cancel();
/*?*/         if( GetCancellableCount() < nPos )
/*?*/             nPos = GetCancellableCount();
/*N*/     }
/*N*/ }

//----------------------------------------------------------------
/*?*/ class SfxMedium_Impl : public SvCompatWeakBase
/*?*/ {
/*?*/ public:
/*?*/     ::ucb::Content aContent;
/*?*/   String aBaseURL;
/*?*/     sal_Bool bUpdatePickList : 1;
/*?*/     sal_Bool bIsTemp        : 1;
/*?*/     sal_Bool bUsesCache     : 1;
/*?*/     sal_Bool bForceSynchron : 1;
/*?*/     sal_Bool bDontCreateCancellable : 1;
/*?*/     sal_Bool bDownloadDone          : 1;
/*?*/     sal_Bool bDontCallDoneLinkOnSharingError : 1;
/*?*/     sal_Bool bStreamReady: 1;
/*?*/     sal_Bool bIsStorage: 1;
/*?*/     sal_Bool bUseInteractionHandler: 1;
/*?*/     sal_Bool bAllowDefaultIntHdl: 1;
/*?*/     sal_Bool bIsDiskSpannedJAR: 1;
/*?*/     sal_Bool bIsCharsetInitialized: 1;
/*?*/
/*?*/     sal_uInt16       nPrio;
/*?*/
/*?*/     SfxPoolCancelManagerRef xCancelManager;
/*?*/     UcbLockBytesCancellable_Impl* pCancellable;
/*?*/     SfxMedium*       pAntiImpl;
/*?*/     SvEaMgr*         pEaMgr;
/*?*/
/*?*/     long             nFileVersion;
/*?*/
/*?*/     const SfxFilter* pOrigFilter;
/*?*/     String           aOrigURL;
/*?*/     String           aPreRedirectionURL;
/*?*/     String           aReferer;
/*?*/     DateTime         aExpireTime;
/*?*/     SfxFrameWeak     wLoadTargetFrame;
/*?*/     LoadEnvironment_Impl* pLoadEnv;
/*?*/     SvKeyValueIteratorRef xAttributes;
/*?*/     SvRefBaseRef    xLoadRef;
/*?*/
/*?*/     svtools::AsynchronLink  aDoneLink;
/*?*/     svtools::AsynchronLink  aAvailableLink;
/*?*/     SfxLockBytesHandler_ImplRef  aHandler;
/*?*/
/*?*/     SfxVersionTableDtor*    pVersions;
/*?*/     ::utl::TempFile*           pTempDir;
/*?*/     ::utl::TempFile*           pTempFile;
/*?*/
/*?*/     Reference < XInputStream > xInputStream;
/*?*/     ::utl::UcbLockBytesRef     xLockBytes;
/*?*/
/*?*/   sal_uInt32                  nLastStorageError;
/*?*/   ::rtl::OUString             aCharset;
/*?*/
/*?*/     ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionHandler > xInteraction;
/*?*/
/*?*/   sal_Bool        m_bRemoveBackup;
/*?*/   ::rtl::OUString m_aBackupURL;
/*?*/
/*?*/     SfxPoolCancelManager* GetCancelManager();
/*?*/
/*?*/     SfxMedium_Impl( SfxMedium* pAntiImplP );
/*?*/     ~SfxMedium_Impl();
/*?*/ };

/*N*/ void SfxMedium::Done_Impl( ErrCode nError )
/*N*/ {
/*N*/     DELETEZ( pImp->pCancellable );
/*N*/     pImp->bDownloadDone = sal_True;
/*N*/     SetError( nError );
/*N*/     if ( pImp->xLockBytes.Is() )
/*N*/         pImp->xInputStream = pImp->xLockBytes->getInputStream();
/*N*/
/*N*/     if ( ( !nError || !pImp->bDontCallDoneLinkOnSharingError ) && ( pImp->bStreamReady || !pInStream ) )
/*N*/     {
/*N*/         pImp->aDoneLink.ClearPendingCall();
/*N*/         pImp->aDoneLink.Call( (void*) nError );
/*N*/     }
/*N*/ }

/*N*/ void SfxMedium::DataAvailable_Impl()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     pImp->aAvailableLink.ClearPendingCall();
//STRIP001     pImp->aAvailableLink.Call( NULL );
/*N*/ }

/*N*/ void SfxMedium::Cancel_Impl()
/*N*/ {
/*N*/     SetError( ERRCODE_IO_GENERAL );
/*N*/ }

/*N*/ SfxPoolCancelManager* SfxMedium_Impl::GetCancelManager()
/*N*/ {
/*N*/     if( !xCancelManager.Is() )
/*N*/     {
/*N*/         if( !bDontCreateCancellable )
/*N*/             xCancelManager = new SfxPoolCancelManager(
/*N*/                 wLoadTargetFrame ? wLoadTargetFrame->GetCancelManager() :
/*N*/                 SFX_APP()->GetCancelManager(),
/*N*/                 pAntiImpl->GetURLObject().GetURLNoPass() );
/*N*/         else
/*?*/             xCancelManager = new SfxPoolCancelManager(
/*?*/                 0, pAntiImpl->GetURLObject().GetURLNoPass() );
/*N*/     }
/*N*/     return xCancelManager;
/*N*/ }

//------------------------------------------------------------------
/*N*/ SfxMedium_Impl::SfxMedium_Impl( SfxMedium* pAntiImplP )
/*N*/  :
/*N*/     SvCompatWeakBase( pAntiImplP ),
/*N*/     bUpdatePickList(sal_True), bIsTemp( sal_False ), pOrigFilter( 0 ),
/*N*/     bUsesCache(sal_True), pCancellable( 0 ),
/*N*/     nPrio( 99 ), aExpireTime( Date() + 10, Time() ),
/*N*/     bForceSynchron( sal_False ), bStreamReady( sal_False ), bIsStorage( sal_False ),
/*N*/     pLoadEnv( 0 ), pAntiImpl( pAntiImplP ),
/*N*/     bDontCreateCancellable( sal_False ), pTempDir( NULL ), bIsDiskSpannedJAR( sal_False ),
/*N*/     bDownloadDone( sal_True ), bDontCallDoneLinkOnSharingError( sal_False ),nFileVersion( 0 ), pEaMgr( NULL ), pTempFile( NULL ),
/*N*/   nLastStorageError( 0 ),
/*N*/   bIsCharsetInitialized( sal_False ),
/*N*/   bUseInteractionHandler( sal_True ),
/*N*/   bAllowDefaultIntHdl( sal_False ),
/*N*/   m_bRemoveBackup( sal_False )
/*N*/ {
/*N*/     aHandler = new SfxLockBytesHandler_Impl( pAntiImpl );
/*N*/     aDoneLink.CreateMutex();
/*N*/ }

//------------------------------------------------------------------
/*N*/ SfxMedium_Impl::~SfxMedium_Impl()
/*N*/ {
/*N*/     delete pCancellable;
/*N*/
/*N*/     if ( aHandler.Is() )
/*N*/         aHandler->Activate( sal_False );
/*N*/
/*N*/     aDoneLink.ClearPendingCall();
/*N*/     aAvailableLink.ClearPendingCall();
/*N*/
/*N*/     delete pEaMgr;
/*N*/     delete pVersions;
/*N*/
/*N*/     if ( pTempFile )
/*N*/         delete pTempFile;
/*N*/
/*N*/     if ( pTempDir )
/*?*/         delete pTempDir;
/*N*/ }

//================================================================

/*?*/ #define IMPL_CTOR()                         \
/*?*/      eError( SVSTREAM_OK ),                 \
/*?*/                                             \
/*?*/      bDirect( sal_False ),                  \
/*?*/      bTriedStorage( sal_False ),            \
/*?*/      bSetFilter( sal_False ),               \
/*?*/                                             \
/*?*/      nStorOpenMode( SFX_STREAM_READWRITE ), \
/*?*/      pInStream(0),                          \
/*?*/      pOutStream( 0 )

//------------------------------------------------------------------
/*N*/ const SvGlobalName&  SfxMedium::GetClassFilter()
/*N*/ {
/*N*/     GetMedium_Impl();
/*N*/     if( GetError() )
/*N*/         return aFilterClass;
/*N*/     if( !bSetFilter && GetStorage() )
/*N*/         SetClassFilter( GetStorage()->GetClassName() );
/*N*/     return aFilterClass;
/*N*/ }

//------------------------------------------------------------------
/*N*/ void SfxMedium::ResetError()
/*N*/ {
/*N*/     eError = SVSTREAM_OK;
/*N*/     if( aStorage.Is() )
/*N*/         aStorage->ResetError();
/*N*/     if( pInStream )
/*N*/         pInStream->ResetError();
/*N*/     if( pOutStream )
/*?*/         pOutStream->ResetError();
/*N*/ }

//------------------------------------------------------------------
/*N*/ sal_uInt32 SfxMedium::GetLastStorageCreationState()
/*N*/ {
/*N*/   return pImp->nLastStorageError;
/*N*/ }

//------------------------------------------------------------------
/*N*/ sal_uInt32 SfxMedium::GetErrorCode() const
/*N*/ {
/*N*/     sal_uInt32 lError=eError;
/*N*/     if(!lError && pInStream)
/*N*/         lError=pInStream->GetErrorCode();
/*N*/     if(!lError && pOutStream)
/*?*/         lError=pOutStream->GetErrorCode();
/*N*/     if(!lError && aStorage.Is())
/*N*/         lError=aStorage->GetErrorCode();
/*N*/     return lError;
/*N*/ }

//------------------------------------------------------------------
/*N*/ long SfxMedium::GetFileVersion() const
/*N*/ {
/*N*/     if ( !pImp->nFileVersion && pFilter )
/*N*/         return pFilter->GetVersion();
/*N*/     else
/*?*/         return pImp->nFileVersion;
/*N*/ }

//------------------------------------------------------------------
/*N*/ Reference < XContent > SfxMedium::GetContent() const
/*N*/ {
/*N*/     if ( !pImp->aContent.get().is() )
/*N*/     {
/*N*/       Reference < ::com::sun::star::ucb::XContent > xContent;
/*N*/       Reference < ::com::sun::star::ucb::XCommandEnvironment > xEnv;
/*N*/         SFX_ITEMSET_ARG( pSet, pItem, SfxUnoAnyItem, SID_CONTENT, sal_False);
/*N*/         if ( pItem )
/*?*/             pItem->GetValue() >>= xContent;
/*N*/
/*N*/       if ( xContent.is() )
/*N*/       {
/*N*/           try
/*N*/           {
/*?*/               pImp->aContent = ::ucb::Content( xContent, xEnv );
/*N*/           }
/*N*/           catch ( Exception& )
/*N*/           {
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           String aURL;
/*N*/           if ( aName.Len() )
/*N*/               ::utl::LocalFileHelper::ConvertPhysicalNameToURL( aName, aURL );
/*N*/           else if ( aLogicName.Len() )
/*N*/               aURL = GetURLObject().GetMainURL( INetURLObject::NO_DECODE );
/*N*/           if ( aURL.Len() )
/*N*/               ::ucb::Content::create( aURL, xEnv, pImp->aContent );
/*N*/       }
/*N*/     }
/*N*/
/*N*/     return pImp->aContent.get();
/*N*/ }

/*N*/ const String& SfxMedium::GetBaseURL()
/*N*/ {
/*N*/     if ( !pImp->aBaseURL.Len() && GetContent().is() )
/*N*/     {
/*N*/         try
/*N*/         {
/*N*/             Any aAny = pImp->aContent.getPropertyValue( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("BaseURI" )) );
/*N*/             ::rtl::OUString aStr;
/*N*/             if ( ( aAny >>= aStr ) && aStr.getLength() )
/*N*/               pImp->aBaseURL = aStr;
/*N*/         }
/*N*/         catch ( ::com::sun::star::uno::Exception& )
/*N*/         {
/*N*/         }
/*N*/     }
/*N*/
/*N*/   if ( !pImp->aBaseURL.Len() )
/*N*/       pImp->aBaseURL = GetURLObject().GetMainURL( INetURLObject::NO_DECODE );
/*N*/   return pImp->aBaseURL;
/*N*/ }

//------------------------------------------------------------------
/*N*/ SvStream* SfxMedium::GetInStream()
/*N*/ {
/*N*/     if ( pInStream )
/*N*/         return pInStream;
/*N*/
/*N*/     if ( pImp->pTempFile || pImp->pTempDir )
/*N*/     {
/*?*/         pInStream = new SvFileStream( aName, nStorOpenMode );
/*?*/
/*?*/         eError = pInStream->GetError();
/*?*/
/*?*/         if( !eError && (nStorOpenMode & STREAM_WRITE)
/*?*/                     && ! pInStream->IsWritable() )
/*?*/         {
/*?*/             eError = ERRCODE_IO_ACCESSDENIED;
/*?*/             delete pInStream;
/*?*/             pInStream = NULL;
/*?*/         }
/*?*/         else
/*?*/             return pInStream;
/*N*/     }
/*N*/
/*N*/     GetMedium_Impl();
/*N*/
/*N*/     if ( !pInStream && eError == ERRCODE_IO_PENDING )
/*?*/         eError = SVSTREAM_OK;
/*N*/
/*N*/     return pInStream;
/*N*/ }

//------------------------------------------------------------------
/*N*/ void SfxMedium::CloseInStream()
/*N*/ {
/*N*/     CloseInStream_Impl();
/*N*/ }

/*N*/ void SfxMedium::CloseInStream_Impl()
/*N*/ {
/*N*/     // if there is a storage based on the InStream, we have to
/*N*/     // close the storage, too, because otherwise the storage
/*N*/     // would use an invalid ( deleted ) stream.
/*N*/     if ( pInStream && aStorage.Is() )
/*N*/     {
/*?*/         const SvStream *pStorage = aStorage->GetSvStream();
/*?*/         if ( pStorage == pInStream )
/*?*/         {
/*?*/             CloseStorage();
/*?*/         }
/*?*/     }
/*N*/
/*N*/     DELETEZ( pInStream );
/*N*/     pImp->xInputStream = Reference < XInputStream >();
/*N*/     pImp->xLockBytes.Clear();
/*N*/     if ( pSet )
/*N*/         pSet->ClearItem( SID_INPUTSTREAM );
/*N*/
/*N*/     DELETEZ( pImp->pCancellable );
/*N*/ }

//------------------------------------------------------------------
/*N*/ SvStream* SfxMedium::GetOutStream()
/*N*/ {
/*N*/     if ( !pOutStream )
/*N*/     {
/*N*/         // Create a temp. file if there is none because we always
/*N*/         // need one.
/*N*/         if ( !pImp->pTempFile )
/*?*/             CreateTempFile();
/*N*/
/*N*/         if ( pImp->pTempFile )
/*N*/         {
/*N*/             pOutStream = new SvFileStream( aName, STREAM_STD_READWRITE );
/*N*/             CloseStorage();
/*N*/         }
/*N*/     }
/*N*/
/*N*/     return pOutStream;
/*N*/ }

//------------------------------------------------------------------
/*N*/ sal_Bool SfxMedium::CloseOutStream()
/*N*/ {
/*N*/     CloseOutStream_Impl();
/*N*/     return sal_True;
/*N*/ }

/*N*/ sal_Bool SfxMedium::CloseOutStream_Impl()
/*N*/ {
/*N*/     if ( pOutStream )
/*N*/     {
/*N*/         // if there is a storage based on the OutStream, we have to
/*N*/         // close the storage, too, because otherwise the storage
/*N*/         // would use an invalid ( deleted ) stream.
/*N*/         if ( aStorage.Is() )
/*N*/         {
/*?*/             const SvStream *pStorage = aStorage->GetSvStream();
/*?*/             if ( pStorage == pOutStream )
/*?*/                 CloseStorage();
/*N*/         }
/*N*/
/*N*/         delete pOutStream;
/*N*/         pOutStream = NULL;
/*N*/     }
/*N*/
/*N*/     return sal_True;
/*N*/ }

//------------------------------------------------------------------
/*N*/ const String& SfxMedium::GetPhysicalName() const
/*N*/ {
/*N*/     if ( !aName.Len() && aLogicName.Len() )
/*N*/         (( SfxMedium*)this)->CreateFileStream();
/*N*/
/*N*/     // return the name then
/*N*/     return aName;
/*N*/ }

//------------------------------------------------------------------
/*N*/ void SfxMedium::CreateFileStream()
/*N*/ {
/*N*/     ForceSynchronStream_Impl( TRUE );
/*N*/     GetInStream();
/*N*/     if( pInStream )
/*N*/     {
/*N*/         if ( !pImp->pTempFile )
/*N*/             CreateTempFile();
/*N*/         pImp->bIsTemp = sal_True;
/*N*/         CloseInStream_Impl();
/*N*/     }
/*N*/ }

//------------------------------------------------------------------
/*N*/ sal_Bool SfxMedium::Commit()
/*N*/ {
/*N*/     if( aStorage.Is() )
/*N*/     {
/*N*/         // StorageStream immer direkt
/*N*/         if( !aStorage->Commit() )
/*?*/             eError = aStorage->GetError();
/*N*/     }
/*N*/     else if( pOutStream  )
/*?*/         pOutStream->Flush();
/*N*/     else if( pInStream  )
/*?*/         pInStream->Flush();
/*N*/
/*N*/     if ( ( GetError() == SVSTREAM_OK ) && pImp->pTempFile )
/*N*/         Transfer_Impl();
/*N*/
/*N*/   ClearBackup_Impl();
/*N*/
/*N*/     return GetError() == SVSTREAM_OK;
/*N*/ }

//------------------------------------------------------------------
/*N*/ sal_Bool SfxMedium::IsStorage()
/*N*/ {
/*N*/     if ( aStorage.Is() )
/*?*/         return TRUE;
/*N*/
/*N*/     if ( bTriedStorage )
/*?*/         return pImp->bIsStorage;
/*N*/
/*N*/     if ( pImp->pTempFile )
/*N*/     {
/*?*/       String aURL;
#ifdef DBG_UTIL
/*?*/       if ( !::utl::LocalFileHelper::ConvertPhysicalNameToURL( aName, aURL ) )
/*?*/           DBG_ERROR("Physical name not convertable!");
#endif
/*?*/         pImp->bIsStorage = SotStorage::IsStorageFile( aURL );
/*?*/         if ( !pImp->bIsStorage )
/*?*/             bTriedStorage = TRUE;
/*N*/     }
/*N*/     else if ( GetInStream() )
/*N*/     {
/*?*/         pImp->bIsStorage = SotStorage::IsStorageFile( pInStream );
/*?*/         if ( !pInStream->GetError() && !pImp->bIsStorage )
/*?*/             bTriedStorage = TRUE;
/*N*/     }
/*N*/
/*N*/     return pImp->bIsStorage;
/*N*/ }

//------------------------------------------------------------------
/*N*/ Link SfxMedium::GetDataAvailableLink() const
/*N*/ {
/*N*/     return pImp->aAvailableLink.GetLink();
/*N*/ }

//------------------------------------------------------------------
/*N*/ Link SfxMedium::GetDoneLink() const
/*N*/ {
/*N*/     return pImp->aDoneLink.GetLink();
/*N*/ }

//------------------------------------------------------------------
//STRIP001 sal_Bool SfxMedium::IsPreview_Impl()
//STRIP001 {
//STRIP001     sal_Bool bPreview = sal_False;
//STRIP001     SFX_ITEMSET_ARG( GetItemSet(), pPreview, SfxBoolItem, SID_PREVIEW, sal_False);
//STRIP001     if ( pPreview )
//STRIP001         bPreview = pPreview->GetValue();
//STRIP001     else
//STRIP001     {
//STRIP001         SFX_ITEMSET_ARG( GetItemSet(), pFlags, SfxStringItem, SID_OPTIONS, sal_False);
//STRIP001         if ( pFlags )
//STRIP001         {
//STRIP001             String aFileFlags = pFlags->GetValue();
//STRIP001             aFileFlags.ToUpperAscii();
//STRIP001             if ( STRING_NOTFOUND != aFileFlags.Search( 'B' ) )
//STRIP001                 bPreview = sal_True;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     return bPreview;
//STRIP001 }

//------------------------------------------------------------------
/*N*/ sal_Bool SfxMedium::TryStorage()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001     GetStorage();
//STRIP001
//STRIP001     if ( aStorage.Is() )
//STRIP001         return sal_True;
//STRIP001
//STRIP001     ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >  xSMgr( ::legacy_binfilters::getLegacyProcessServiceFactory() );
//STRIP001     ::com::sun::star::uno::Reference< ::com::sun::star::util::XArchiver >
//STRIP001             xPacker( xSMgr->createInstance( DEFINE_CONST_UNICODE( "com.sun.star.util.Archiver" ) ), ::com::sun::star::uno::UNO_QUERY );
//STRIP001
//STRIP001     if( !xPacker.is() )
//STRIP001         return sal_False;
//STRIP001
//STRIP001     // extract extra data
//STRIP001     ::rtl::OUString aPath = GetURLObject().PathToFileName();
//STRIP001     ::rtl::OUString aExtraData = xPacker->getExtraData( aPath );
//STRIP001     const ::rtl::OUString aSig1( DEFINE_CONST_UNICODE( "private:" ) );
//STRIP001     String aTmp( '?' );
//STRIP001     aTmp += pFilter->GetFilterContainer()->GetName();
//STRIP001     const ::rtl::OUString aSig2( aTmp );
//STRIP001     sal_Int32 nIndex1 = aExtraData.indexOf( aSig1 );
//STRIP001     sal_Int32 nIndex2 = aExtraData.indexOf( aSig2 );
//STRIP001
//STRIP001     if( nIndex1 != 0 || nIndex2 == -1 )
//STRIP001         return sal_False;
//STRIP001
//STRIP001     nIndex1 += aSig1.getLength();
//STRIP001     ::rtl::OUString aTempDoku = aExtraData.copy( nIndex1, nIndex2 - nIndex1 );
//STRIP001
//STRIP001     // create a temp dir to unpack to
//STRIP001     pImp->pTempDir = new ::utl::TempFile( NULL, sal_True );
//STRIP001     pImp->pTempDir->EnableKillingFile( sal_True );
//STRIP001
//STRIP001     // unpack all files to temp dir
//STRIP001     ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > aArgs;
//STRIP001     ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionHandler > xInteractionHandler = GetInteractionHandler();
//STRIP001     if (xInteractionHandler.is())
//STRIP001     {
//STRIP001         aArgs.realloc(1);
//STRIP001         aArgs.getArray()[0].Name = DEFINE_CONST_UNICODE( "InteractionHandler" );
//STRIP001         aArgs.getArray()[0].Value <<= xInteractionHandler ;
//STRIP001     }
//STRIP001     ::com::sun::star::uno::Sequence< ::rtl::OUString > files(0);
//STRIP001
//STRIP001     if( !xPacker->unpack( pImp->pTempDir->GetURL(), aPath, files, aArgs ) )
//STRIP001         return sal_False;
//STRIP001
//STRIP001     String aNewName = pImp->pTempDir->GetURL();
//STRIP001     aNewName += '/';
//STRIP001     aNewName += String( aTempDoku );
//STRIP001     CloseInStream_Impl();
//STRIP001     String aTemp;
//STRIP001     ::utl::LocalFileHelper::ConvertURLToPhysicalName( aNewName, aTemp );
//STRIP001     SetPhysicalName_Impl( aTemp );
//STRIP001     GetStorage();
//STRIP001
//STRIP001     if ( aStorage.Is() )
//STRIP001     {
//STRIP001         const SfxFilter *pRealFilter = SFX_APP()->GetFilterMatcher().GetFilter4ClipBoardId( aStorage->GetFormat() );
//STRIP001         if ( pRealFilter )
//STRIP001         {
//STRIP001             pImp->nFileVersion = pRealFilter->GetVersion();
//STRIP001             aStorage->SetVersion( pImp->nFileVersion );
//STRIP001         }
//STRIP001
//STRIP001         DBG_ASSERT( pRealFilter, "Unknown storage format!" );
//STRIP001     }
//STRIP001
//STRIP001     return aStorage.Is();
/*N*/ }

//STRIP001 ErrCode SfxMedium::Unpack_Impl( const String& rDest )
//STRIP001 {
//STRIP001     ErrCode nRet = ERRCODE_NONE;
//STRIP001     if ( pImp->pTempDir )
//STRIP001     {
//STRIP001 /*
//STRIP001         DirEntry aDestEntry( rDest );
//STRIP001         Dir aDir( pImp->pTempDir->GetName(), FSYS_KIND_FILE );
//STRIP001         sal_uInt16 nCount = aDir.Count();
//STRIP001         for ( sal_uInt16 n=0; n<nCount; n++ )
//STRIP001         {
//STRIP001             DirEntry aDest( aDestEntry.GetPath() );
//STRIP001             DirEntry aTmp = aDir[n];
//STRIP001             aDest += aTmp.GetName();
//STRIP001             if ( aDir[n] == DirEntry( GetPhysicalName() ) )
//STRIP001                 continue;
//STRIP001
//STRIP001             nRet = aTmp.CopyTo( aDest, FSYS_ACTION_COPYFILE );
//STRIP001             if ( nRet != ERRCODE_NONE )
//STRIP001                 break;
//STRIP001         }
//STRIP001  */
//STRIP001     }
//STRIP001
//STRIP001     return nRet;
//STRIP001 }

//------------------------------------------------------------------
/*N*/ SvStorage* SfxMedium::GetOutputStorage( BOOL bUCBStorage )
/*N*/ {
/*N*/     // if the medium was constructed with a SvStorage: use this one, not a temp. storage
/*N*/     if ( aStorage.Is() && !aLogicName.Len() )
/*N*/         return aStorage;
/*N*/
/*N*/     if ( !pImp->pTempFile )
/*N*/         CreateTempFile();
/*N*/     return GetStorage_Impl( bUCBStorage );
/*N*/ }

/*N*/ SvStorage* SfxMedium::GetStorage()
/*N*/ {
/*N*/     return GetStorage_Impl( pFilter && SOFFICE_FILEFORMAT_60 <= pFilter->GetVersion() );
/*N*/ }

/*N*/ SvStorage* SfxMedium::GetStorage_Impl( BOOL bUCBStorage )
/*N*/ {
/*N*/     if ( aStorage.Is() || bTriedStorage )
/*N*/         return aStorage;
/*N*/
/*N*/     String aStorageName;
/*N*/     if ( pImp->pTempFile || pImp->pTempDir )
/*N*/     {
/*N*/         // open storage with the URL of the tempfile
/*N*/       if ( !::utl::LocalFileHelper::ConvertPhysicalNameToURL( aName, aStorageName ) )
/*N*/       {
/*?*/           DBG_ERROR("Physical name not convertable!");
/*N*/       }
/*N*/         CloseOutStream();
/*N*/         aStorage = new SvStorage( bUCBStorage, aStorageName, nStorOpenMode, bDirect ? 0 : STORAGE_TRANSACTED );
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         if ( aName.Len() )
/*N*/         {
/*N*/             if ( !::utl::LocalFileHelper::ConvertPhysicalNameToURL( aName, aStorageName ) )
/*N*/           {
/*?*/                 DBG_ERROR("Physical name not convertable!");
/*N*/           }
/*N*/         }
/*N*/         else
/*N*/             aStorageName = GetURLObject().GetMainURL( INetURLObject::NO_DECODE );
/*N*/
/*N*/         GetInStream();
/*N*/         if ( pInStream )
/*N*/         {
/*?*/             pInStream->GetLockBytes()->SetSynchronMode( sal_True );
/*?*/             if( UCBStorage::IsDiskSpannedFile( pInStream ) )
/*?*/             {
/*?*/                 // packed remote files can't be opened outside the storage, so they must be reopened
/*?*/                 // inside the storage even if it is expensive
/*?*/                 pImp->bIsDiskSpannedJAR = TRUE;
/*?*/                 CloseInStream();
/*?*/                 aStorage = new SvStorage( TRUE, aStorageName, nStorOpenMode, bDirect ? 0 : STORAGE_TRANSACTED );
/*?*/                 SfxFilterFlags nMust = SFX_FILTER_IMPORT, nDont = SFX_FILTER_NOTINSTALLED | SFX_FILTER_STARONEFILTER;
/*?*/                 SetFilter( SFX_APP()->GetFilterMatcher().GetFilter4ClipBoardId( aStorage->GetFormat(), nMust, nDont ) );
/*N*/             }
/*N*/             else
/*N*/             {
/*N*/                 // download the stream ( or at least start the download )
/*N*/                 if ( !pImp->aDoneLink.IsSet() )
/*N*/                     DownLoad();
/*N*/
/*N*/                   SFX_ITEMSET_ARG( GetItemSet(), pItem, SfxBoolItem, SID_REPAIRPACKAGE, sal_False);
/*N*/                   if ( pItem && pItem->GetValue() )
/*N*/               {
/*N*/                   // CreateTempFile();
/*?*/                   Reference< ::com::sun::star::ucb::XProgressHandler > xProgressHandler;
/*?*/                   Reference< ::com::sun::star::task::XStatusIndicator > xStatusIndicator;
/*?*/                   SFX_ITEMSET_ARG( GetItemSet(), pxProgressItem, SfxUnoAnyItem, SID_PROGRESS_STATUSBAR_CONTROL, sal_False );
/*?*/                   if( pxProgressItem && ( pxProgressItem->GetValue() >>= xStatusIndicator ) )
/*?*/                       xProgressHandler = Reference< ::com::sun::star::ucb::XProgressHandler >(
/*?*/                                               new ::utl::ProgressHandlerWrap( xStatusIndicator ) );
/*?*/
/*?*/                       INetURLObject aObj( aName );
/*?*/                       if ( aObj.GetProtocol() == INET_PROT_NOT_VALID )
/*?*/                       {
/*?*/                           String aURL;
/*?*/                           ::utl::LocalFileHelper::ConvertPhysicalNameToURL( aName, aURL );
/*?*/                           aObj.SetURL( aURL );
/*?*/                       }
/*?*/
/*?*/                   UCBStorage* pUCBStorage = new UCBStorage( aObj.GetMainURL( INetURLObject::NO_DECODE ),
/*?*/                                                             nStorOpenMode,
/*?*/                                                             bDirect ? 0 : STORAGE_TRANSACTED,
/*?*/                                                             sal_True,
/*?*/                                                             sal_True,
/*?*/                                                             xProgressHandler );
/*?*/
/*?*/                   aStorage = new SvStorage( pUCBStorage );
/*N*/               }
/*N*/               else
/*N*/               {
/*N*/                   if( SotStorage::IsStorageFile( pInStream ) )
/*N*/                   {
/*N*/                       if ( IsReadOnly() && ::utl::LocalFileHelper::IsLocalFile( aLogicName ) )
/*N*/                       {
/*N*/                           CreateTempFile();
/*N*/                           aStorage = new SvStorage( bUCBStorage, aName, nStorOpenMode, bDirect ? 0 : STORAGE_TRANSACTED );
/*N*/                       }
/*N*/                       else
/*N*/                       {
/*N*/                           if ( bUCBStorage && !UCBStorage::IsStorageFile( pInStream ) )
/*N*/                               return NULL;
/*N*/
/*N*/                           // create a storage on the stream
/*N*/                           aStorage = new SvStorage( pInStream, sal_False );
/*N*/                           if ( !aStorage->GetName().Len() )
/*N*/                                   aStorage->SetName( aStorageName );
/*N*/                       }
/*N*/                   }
/*N*/                   else
/*N*/                       return NULL;
/*N*/               }
/*N*/             }
/*N*/         }
/*N*/         else
/*N*/             return NULL;
/*N*/     }
/*N*/
/*N*/     if( ( pImp->nLastStorageError = GetError() ) != SVSTREAM_OK )
/*N*/     {
/*N*/         aStorage.Clear();
/*N*/         if ( pInStream )
/*N*/             pInStream->Seek(0);
/*N*/         return NULL;
/*N*/     }
/*N*/
/*N*/     bTriedStorage = sal_True;
/*N*/
/*N*/     if ( aStorage->GetError() == SVSTREAM_OK )
/*N*/         GetVersionList();
/*N*/
/*N*/     // ???? wird das noch gebraucht?
/*N*/ //  GetMedium_Impl();
/*N*/ //  if ( !aStorage.Is() )
/*N*/ //      CreateFileStream();
/*N*/
/*N*/     SFX_ITEMSET_ARG( pSet, pVersion, SfxInt16Item, SID_VERSION, sal_False);
/*N*/
/*N*/     BOOL bResetStorage = FALSE;
/*N*/     if ( pVersion && pVersion->GetValue() )
/*N*/     {
/*N*/         // Alle verf"ugbaren Versionen einlesen
/*N*/         if ( pImp->pVersions )
/*N*/         {
/*?*/             // Die zum Kommentar passende Version suchen
/*?*/             // Die Versionen sind von 1 an durchnumeriert, mit negativen
/*?*/             // Versionsnummern werden die Versionen von der aktuellen aus
/*?*/             // r"uckw"arts gez"ahlt
/*?*/             short nVersion = pVersion ? pVersion->GetValue() : 0;
/*?*/             if ( nVersion<0 )
/*?*/                 nVersion = ( (short) pImp->pVersions->Count() ) + nVersion;
/*?*/             else if ( nVersion )
/*?*/                 nVersion--;
/*?*/
/*?*/             SfxVersionInfo* pInfo = nVersion>=0 ? pImp->pVersions->GetObject( nVersion ) : NULL;
/*?*/             if ( pInfo )
/*?*/             {
/*?*/                 String aVersionStream = pInfo->aName;
/*?*/
/*?*/                 // SubStorage f"ur alle Versionen "offnen
/*?*/                 SvStorageRef aSub =
/*?*/                     aStorage->OpenStorage( DEFINE_CONST_UNICODE( "Versions" ), SFX_STREAM_READONLY | STREAM_NOCREATE );
/*?*/
/*?*/                 DBG_ASSERT( aSub.Is() && !aSub->GetError(), "Versionsliste, aber keine Versionen!" );
/*?*/
/*?*/                 // Dort ist die Version als gepackter Stream gespeichert
/*?*/                 SvStorageStreamRef aStream =
/*?*/                     aSub->OpenStream( aVersionStream, SFX_STREAM_READONLY );
/*?*/
/*?*/                 if ( aStream.Is() && aStream->GetError() == SVSTREAM_OK )
/*?*/                 {
/*?*/                     // Stream ins TempDir auspacken
/*?*/                     ::utl::TempFile aTempFile;
/*?*/                     String          aTmpName = aTempFile.GetURL();
/*?*/                     SvFileStream    aTmpStream( aTmpName, SFX_STREAM_READWRITE );
/*?*/
/*?*/                     // The new file format uses UCB storages instead of OLE storages.
/*?*/                     // These storages aren't compressed.
/*?*/                     if ( !aSub->IsOLEStorage() )
/*?*/                     {
/*?*/                         *aStream >> aTmpStream;
/*?*/                     }
/*?*/                     else
/*?*/                     {
/*?*/                         ZCodec aCodec;
/*?*/                         aCodec.BeginCompression();
/*?*/                         aCodec.Decompress( *aStream, aTmpStream );
/*?*/                         aCodec.EndCompression();
/*?*/                     }
/*?*/                     aTmpStream.Close();
/*?*/
/*?*/                     // Datei als Storage "offnen
/*?*/                     nStorOpenMode = SFX_STREAM_READONLY;
/*?*/                     aStorage = new SvStorage( aTmpName, nStorOpenMode );
/*?*/
/*?*/                     String aTemp;
/*?*/                     ::utl::LocalFileHelper::ConvertURLToPhysicalName( aTmpName, aTemp );
/*?*/                     SetPhysicalName_Impl( aTemp );
/*?*/
/*?*/                     pImp->bIsTemp = sal_True;
/*?*/                     GetItemSet()->Put( SfxBoolItem( SID_DOC_READONLY, sal_True ) );
/*?*/                     DELETEZ( pImp->pVersions );
/*?*/                 }
/*?*/                 else
/*?*/                     bResetStorage = TRUE;
/*?*/             }
/*?*/             else
/*?*/                 bResetStorage = TRUE;
/*?*/         }
/*?*/         else
/*?*/             bResetStorage = TRUE;
/*N*/     }
/*N*/
/*N*/     if ( aStorage.Is() )
/*N*/     {
/*N*/         if( ( pImp->nLastStorageError = aStorage->GetError() ) != SVSTREAM_OK )
/*N*/             bResetStorage = TRUE;
/*N*/         else if ( GetFilter() )
/*N*/             aStorage->SetVersion( GetFilter()->GetVersion() );
/*N*/     }
/*N*/
/*N*/     if ( bResetStorage )
/*N*/     {
/*?*/         aStorage.Clear();
/*?*/         if ( pInStream )
/*?*/             pInStream->Seek( 0L );
/*N*/     }
/*N*/
/*N*/     pImp->bIsStorage = aStorage.Is();
/*N*/     return aStorage;
/*N*/ }

//------------------------------------------------------------------
/*N*/ void SfxMedium::CloseStorage()
/*N*/ {
/*N*/     aStorage.Clear();
/*N*/     bTriedStorage = sal_False;
/*N*/     pImp->bIsStorage = sal_False;
/*N*/ }

//------------------------------------------------------------------
/*?*/ void SfxMedium::SetOpenMode( StreamMode nStorOpen,
/*?*/                              sal_Bool bDirectP,
/*?*/                              sal_Bool bDontClose )
/*?*/ {
/*?*/     if ( nStorOpenMode != nStorOpen )
/*?*/     {
/*?*/         nStorOpenMode = nStorOpen;
/*?*/
/*?*/         if( !bDontClose )
/*?*/             Close();
/*?*/     }
/*?*/
/*?*/     bDirect     = bDirectP;
/*?*/     bSetFilter  = sal_False;
/*?*/ }

//STRIP001 sal_Bool SfxMedium::TransactedTransferForFS_Impl( const INetURLObject& aSource,
//STRIP001                                              const INetURLObject& aDest,
//STRIP001                                              const Reference< ::com::sun::star::ucb::XCommandEnvironment >& xComEnv )
//STRIP001 {
//STRIP001  sal_Bool bResult = sal_False;
//STRIP001  Reference< ::com::sun::star::ucb::XCommandEnvironment > xDummyEnv;
//STRIP001  Reference< XOutputStream > aDestStream;
//STRIP001  Reference< XSimpleFileAccess > aSimpleAccess;
//STRIP001  ::ucb::Content aOriginalContent;
//STRIP001
//STRIP001  DBG_ASSERT( ::utl::LocalFileHelper::IsLocalFile( aDest.GetMainURL( INetURLObject::NO_DECODE ) ),
//STRIP001              "SfxMedium::TransactedTransferForFS() should be used only for local contents!" );
//STRIP001
//STRIP001  if( ::ucb::Content::create( aDest.GetMainURL( INetURLObject::NO_DECODE ), xComEnv, aOriginalContent ) )
//STRIP001  {
//STRIP001      Close();
//STRIP001      ::ucb::Content aTempCont;
//STRIP001      if( ::ucb::Content::create( aSource.GetMainURL( INetURLObject::NO_DECODE ), xDummyEnv, aTempCont ) )
//STRIP001      {
//STRIP001          sal_Bool bTransactStarted = sal_False;
//STRIP001          SFX_ITEMSET_ARG( GetItemSet(), pOverWrite, SfxBoolItem, SID_OVERWRITE, sal_False );
//STRIP001              SFX_ITEMSET_ARG( GetItemSet(), pRename, SfxBoolItem, SID_RENAME, sal_False );
//STRIP001          sal_Bool bRename = pRename ? pRename->GetValue() : FALSE;
//STRIP001          sal_Bool bOverWrite = pOverWrite ? pOverWrite->GetValue() : !bRename;
//STRIP001
//STRIP001          try
//STRIP001          {
//STRIP001              if( bOverWrite && ::utl::UCBContentHelper::IsDocument( aDest.GetMainURL( INetURLObject::NO_DECODE ) ) )
//STRIP001              {
//STRIP001                  if( ! pImp->m_aBackupURL.getLength() )
//STRIP001                      DoInternalBackup_Impl( aOriginalContent );
//STRIP001
//STRIP001                  if( pImp->m_aBackupURL.getLength() )
//STRIP001                  {
//STRIP001                      Reference< XInputStream > aTempInput = aTempCont.openStream();
//STRIP001                      bTransactStarted = sal_True;
//STRIP001                      aOriginalContent.writeStream( aTempInput, bOverWrite );
//STRIP001                      bResult = sal_True;
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      WarningBox( NULL, SfxResId( MSG_WARNING_BACKUP ) ).Execute();
//STRIP001                      eError = ERRCODE_ABORT;
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  Reference< XInputStream > aTempInput = aTempCont.openStream();
//STRIP001                  aOriginalContent.writeStream( aTempInput, bOverWrite );
//STRIP001                  bResult = sal_True;
//STRIP001              }
//STRIP001          }
//STRIP001          catch ( ::com::sun::star::ucb::CommandAbortedException& )
//STRIP001          {
//STRIP001              eError = ERRCODE_ABORT;
//STRIP001          }
//STRIP001          catch ( ::com::sun::star::ucb::CommandFailedException& )
//STRIP001          {
//STRIP001              eError = ERRCODE_ABORT;
//STRIP001          }
//STRIP001          catch ( ::com::sun::star::ucb::InteractiveIOException& r )
//STRIP001          {
//STRIP001              if ( r.Code == IOErrorCode_ACCESS_DENIED )
//STRIP001                  eError = ERRCODE_IO_ACCESSDENIED;
//STRIP001              else if ( r.Code == IOErrorCode_NOT_EXISTING )
//STRIP001                  eError = ERRCODE_IO_NOTEXISTS;
//STRIP001              else if ( r.Code == IOErrorCode_CANT_READ )
//STRIP001                  eError = ERRCODE_IO_CANTREAD;
//STRIP001              else
//STRIP001                  eError = ERRCODE_IO_GENERAL;
//STRIP001          }
//STRIP001          catch ( ::com::sun::star::uno::Exception& e )
//STRIP001          {
//STRIP001              eError = ERRCODE_IO_GENERAL;
//STRIP001          }
//STRIP001
//STRIP001              if ( bResult )
//STRIP001              {
//STRIP001              pImp->pTempFile->EnableKillingFile( sal_True );
//STRIP001                  delete pImp->pTempFile;
//STRIP001                  pImp->pTempFile = NULL;
//STRIP001
//STRIP001              // without a TempFile the physical and logical name should be the same
//STRIP001                  ::utl::LocalFileHelper::ConvertURLToPhysicalName( GetURLObject().GetMainURL( INetURLObject::NO_DECODE ),
//STRIP001                                                                aName );
//STRIP001              }
//STRIP001          else if ( bTransactStarted )
//STRIP001          {
//STRIP001              try
//STRIP001              {
//STRIP001                  ::ucb::Content aTransactCont;
//STRIP001                  if( ::ucb::Content::create( pImp->m_aBackupURL, xDummyEnv, aTransactCont ) )
//STRIP001                  {
//STRIP001                      Reference< XInputStream > aOrigInput = aTransactCont.openStream();
//STRIP001                      aOriginalContent.writeStream( aOrigInput, sal_True );
//STRIP001                  }
//STRIP001              }
//STRIP001              catch( Exception& )
//STRIP001              {
//STRIP001                  // in case of failure here the backup file should not be removed
//STRIP001                  pImp->m_bRemoveBackup = sal_False;
//STRIP001                  eError = ERRCODE_IO_GENERAL;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001          eError = ERRCODE_IO_CANTREAD;
//STRIP001  }
//STRIP001
//STRIP001  return bResult;
//STRIP001 }


//------------------------------------------------------------------
/*N*/ void SfxMedium::Transfer_Impl()
/*N*/ {
/*N*/     if( pImp->pTempFile && ( !eError || eError & ERRCODE_WARNING_MASK ) )
/*N*/     {
/*N*/         Reference < ::com::sun::star::ucb::XCommandEnvironment > xEnv;
/*N*/       Reference< XOutputStream > rOutStream;
/*N*/
/*N*/       // in case an output stream is provided from outside and the URL is correct
/*N*/       // commit to the stream
/*N*/         if( aLogicName.CompareToAscii( "private:stream", 14 ) == COMPARE_EQUAL )
/*N*/       {
/*N*/           SFX_ITEMSET_ARG( pSet, pOutStreamItem, SfxUnoAnyItem, SID_OUTPUTSTREAM, sal_False);
/*N*/           if( pOutStreamItem && ( pOutStreamItem->GetValue() >>= rOutStream ) )
/*N*/           {
/*N*/               // write directly to the stream
/*N*/               Close();
/*N*/
/*N*/               INetURLObject aSource( pImp->pTempFile->GetURL() );
/*N*/               ::ucb::Content aTempCont;
/*N*/               if( ::ucb::Content::create( aSource.GetMainURL( INetURLObject::NO_DECODE ), xEnv, aTempCont ) )
/*N*/               {
/*N*/                   try
/*N*/                   {
/*N*/                       sal_Int32 nRead;
/*N*/                       sal_Int32 nBufferSize = 32767;
/*N*/                       Sequence < sal_Int8 > aSequence ( nBufferSize );
/*N*/                       Reference< XInputStream > aTempInput = aTempCont.openStream();
/*N*/
/*N*/                       do
/*N*/                       {
/*N*/                           nRead = aTempInput->readBytes ( aSequence, nBufferSize );
/*N*/                           if ( nRead < nBufferSize )
/*N*/                           {
/*N*/                               Sequence < sal_Int8 > aTempBuf ( aSequence.getConstArray(), nRead );
/*N*/                               rOutStream->writeBytes ( aTempBuf );
/*N*/                           }
/*N*/                           else
/*N*/                               rOutStream->writeBytes ( aSequence );
/*N*/                       }
/*N*/                       while ( nRead == nBufferSize );
/*N*/
/*N*/                       // remove temporary file
/*N*/                       pImp->pTempFile->EnableKillingFile( sal_True );
/*N*/                       delete pImp->pTempFile;
/*N*/                       pImp->pTempFile = NULL;
/*N*/                   }
/*N*/                   catch( Exception& )
/*N*/                   {}
/*N*/               }
/*N*/               }
/*N*/           else
/*N*/           {
/*N*/               DBG_ERROR( "Illegal Output stream parameter!\n" );
/*N*/               SetError( ERRCODE_IO_GENERAL );
/*N*/           }
/*N*/
/*N*/           // free the reference
/*N*/           pSet->ClearItem( SID_OUTPUTSTREAM );
/*N*/
/*N*/           return;
/*N*/       }
/*N*/ DBG_BF_ASSERT(0, "STRIP"); return;//STRIP001
//STRIP001 /*?*/         GetContent();
//STRIP001 /*?*/         if ( !pImp->aContent.get().is() )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             eError = ERRCODE_IO_NOTEXISTS;
//STRIP001 /*?*/             return;
//STRIP001 /*?*/         }
//STRIP001 /*?*/
//STRIP001 /*?*/         SFX_ITEMSET_ARG( GetItemSet(), pSegmentSize, SfxInt32Item, SID_SEGMENTSIZE, sal_False);
//STRIP001 /*?*/         if ( pSegmentSize )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             // this file must be stored into a disk spanned package
//STRIP001 /*?*/             SotStorageRef xStor = new SotStorage( TRUE, GetName(), STREAM_STD_READWRITE | STREAM_TRUNC, STORAGE_TRANSACTED );
//STRIP001 /*?*/             if ( xStor->GetError() == ERRCODE_NONE )
//STRIP001 /*?*/             {
//STRIP001 /*?*/                // set segment size property; package will automatically be divided in pieces fitting
//STRIP001 /*?*/                // into this size
//STRIP001 /*?*/                 ::com::sun::star::uno::Any aAny;
//STRIP001 /*?*/                 aAny <<= pSegmentSize->GetValue();
//STRIP001 /*?*/                 xStor->SetProperty( String::CreateFromAscii("SegmentSize"), aAny );
//STRIP001 /*?*/
//STRIP001 /*?*/                // copy the temporary storage into the disk spanned package
//STRIP001 /*?*/                 GetStorage()->CopyTo( xStor );
//STRIP001 /*?*/                 xStor->Commit();
//STRIP001 /*?*/             }
//STRIP001 /*?*/
//STRIP001 /*?*/            if ( !GetError() )
//STRIP001 /*?*/                SetError( xStor->GetError() );
//STRIP001 /*?*/             return;
//STRIP001 /*?*/         }
//STRIP001 /*?*/
//STRIP001 /*?*/         if ( pFilter && SOFFICE_FILEFORMAT_60 <= pFilter->GetVersion() )
//STRIP001 /*?*/        {
//STRIP001 /*?*/             SFX_ITEMSET_ARG( GetItemSet(), pItem, SfxBoolItem, SID_UNPACK, sal_False);
//STRIP001 /*?*/             if ( pItem && pItem->GetValue() )
//STRIP001 /*?*/             {
//STRIP001 /*?*/                // this file must be stored without packing into a JAR file
//STRIP001 /*?*/                // check for an existing unpacked storage
//STRIP001 /*?*/                SvStream* pStream = ::utl::UcbStreamHelper::CreateStream( GetName(), STREAM_STD_READ );
//STRIP001 /*?*/                 if ( !pStream->GetError() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    String aURL = UCBStorage::GetLinkedFile( *pStream );
//STRIP001 /*?*/                    if ( aURL.Len() )
//STRIP001 /*?*/                        // remove a possibly existing old folder
//STRIP001 /*?*/                        ::utl::UCBContentHelper::Kill( aURL );
//STRIP001 /*?*/
//STRIP001 /*?*/                     DELETEZ( pStream );
//STRIP001 /*?*/                 }
//STRIP001 /*?*/
//STRIP001 /*?*/                 // create a new folder based storage
//STRIP001 /*?*/                 SvStorageRef xStor = new SvStorage( TRUE, GetName(), STREAM_STD_READWRITE, STORAGE_CREATE_UNPACKED );
//STRIP001 /*?*/
//STRIP001 /*?*/                 // copy package into unpacked storage
//STRIP001 /*?*/                 if ( xStor->GetError() == ERRCODE_NONE && GetStorage()->CopyTo( xStor ) )
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     // commit changes, writing will happen now
//STRIP001 /*?*/                     xStor->Commit();
//STRIP001 /*?*/
//STRIP001 /*?*/                     // take new unpacked storage as own storage
//STRIP001 /*?*/                     Close();
//STRIP001 /*?*/                     DELETEZ( pImp->pTempFile );
//STRIP001 /*?*/                     ::utl::LocalFileHelper::ConvertURLToPhysicalName( GetURLObject().GetMainURL( INetURLObject::NO_DECODE ), aName );
//STRIP001 /*?*/                     SetStorage_Impl( xStor );
//STRIP001 /*?*/                 }
//STRIP001 /*?*/                 else if ( !GetError() )
//STRIP001 /*?*/                     SetError( xStor->GetError() );
//STRIP001 /*?*/                 return;
//STRIP001 /*?*/             }
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/         sal_Bool bSuccess = sal_False;
//STRIP001 /*?*/         INetURLObject aDest( GetURLObject() );
//STRIP001 /*?*/
//STRIP001 /*?*/         // source is the temp file written so far
//STRIP001 /*?*/         INetURLObject aSource( pImp->pTempFile->GetURL() );
//STRIP001 /*?*/
//STRIP001 /*?*/        // a special case, an interaction handler should be used for
//STRIP001 /*?*/        // authentication in case it is available
//STRIP001 /*?*/        Reference< ::com::sun::star::ucb::XCommandEnvironment > xComEnv;
//STRIP001 /*?*/            Reference< ::com::sun::star::task::XInteractionHandler > xInteractionHandler = GetInteractionHandler();
//STRIP001 /*?*/         if (xInteractionHandler.is())
//STRIP001 /*?*/            xComEnv = new ::ucb::CommandEnvironment( xInteractionHandler,
//STRIP001 /*?*/                                                      Reference< ::com::sun::star::ucb::XProgressHandler >() );
//STRIP001 /*?*/
//STRIP001 /*?*/         if ( ::utl::LocalFileHelper::IsLocalFile( aDest.GetMainURL( INetURLObject::NO_DECODE ) ) )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            TransactedTransferForFS_Impl( aSource, aDest, xComEnv );
//STRIP001 /*?*/            return;
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/         if ( aDest.removeSegment() )
//STRIP001 /*?*/         {
//STRIP001 /*?*/             // create content for the parent folder and call transfer on that content with the source content
//STRIP001 /*?*/             // and the destination file name as parameters
//STRIP001 /*?*/             ::ucb::Content aSourceContent;
//STRIP001 /*?*/             ::ucb::Content aTransferContent;
//STRIP001 /*?*/
//STRIP001 /*?*/             String aFileName = GetLongName();
//STRIP001 /*?*/             if ( !aFileName.Len() )
//STRIP001 /*?*/                 aFileName = GetURLObject().getName( INetURLObject::LAST_SEGMENT, true, INetURLObject::DECODE_WITH_CHARSET );
//STRIP001 /*?*/
//STRIP001 /*?*/             if ( ::ucb::Content::create( aDest.GetMainURL( INetURLObject::NO_DECODE ), xComEnv, aTransferContent ) )
//STRIP001 /*?*/             {
//STRIP001 /*?*/                 // free resources, otherwise the transfer may fail
//STRIP001 /*?*/                 Close();
//STRIP001 /*?*/                 // don't create content before Close(), because if the storage was opened in direct mode, it will be flushed
//STRIP001 /*?*/                 // in Close() and this leads to a transfer command executed in the package, which currently is implemented as
//STRIP001 /*?*/                 // remove+move in the file FCP. The "remove" is notified to the ::ucb::Content, that clears its URL and its
//STRIP001 /*?*/                 // content reference in this notification and thus will never get back any URL, so my transfer will fail!
//STRIP001 /*?*/                 ::ucb::Content::create( aSource.GetMainURL( INetURLObject::NO_DECODE ), xEnv, aSourceContent );
//STRIP001 /*?*/
//STRIP001 /*?*/                 // check for external parameters that may customize the handling of NameClash situations
//STRIP001 /*?*/                 SFX_ITEMSET_ARG( GetItemSet(), pRename, SfxBoolItem, SID_RENAME, sal_False );
//STRIP001 /*?*/                 SFX_ITEMSET_ARG( GetItemSet(), pOverWrite, SfxBoolItem, SID_OVERWRITE, sal_False );
//STRIP001 /*?*/                 sal_Int32 nNameClash;
//STRIP001 /*?*/                 if ( pOverWrite && !pOverWrite->GetValue() )
//STRIP001 /*?*/                     // argument says: never overwrite
//STRIP001 /*?*/                     nNameClash = NameClash::ERROR;
//STRIP001 /*?*/                 else if ( pRename && pRename->GetValue() )
//STRIP001 /*?*/                     // argument says: rename file
//STRIP001 /*?*/                     nNameClash = NameClash::RENAME;
//STRIP001 /*?*/                 else
//STRIP001 /*?*/                     // default is overwrite existing files
//STRIP001 /*?*/                     nNameClash = NameClash::OVERWRITE;
//STRIP001 /*?*/
//STRIP001 /*?*/                 try
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     bSuccess = aTransferContent.transferContent( aSourceContent, ::ucb::InsertOperation_COPY, aFileName, nNameClash );
//STRIP001 /*?*/                 }
//STRIP001 /*?*/                 catch ( ::com::sun::star::ucb::CommandAbortedException& )
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     eError = ERRCODE_ABORT;
//STRIP001 /*?*/                 }
//STRIP001 /*?*/                 catch ( ::com::sun::star::ucb::CommandFailedException& )
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     eError = ERRCODE_ABORT;
//STRIP001 /*?*/                 }
//STRIP001 /*?*/                 catch ( ::com::sun::star::ucb::InteractiveIOException& r )
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     if ( r.Code == IOErrorCode_ACCESS_DENIED )
//STRIP001 /*?*/                         eError = ERRCODE_IO_ACCESSDENIED;
//STRIP001 /*?*/                     else if ( r.Code == IOErrorCode_NOT_EXISTING )
//STRIP001 /*?*/                         eError = ERRCODE_IO_NOTEXISTS;
//STRIP001 /*?*/                     else if ( r.Code == IOErrorCode_CANT_READ )
//STRIP001 /*?*/                         eError = ERRCODE_IO_CANTREAD;
//STRIP001 /*?*/                     else
//STRIP001 /*?*/                         eError = ERRCODE_IO_GENERAL;
//STRIP001 /*?*/                 }
//STRIP001 /*?*/                 catch ( ::com::sun::star::uno::Exception& e )
//STRIP001 /*?*/                 {
//STRIP001 /*?*/                     eError = ERRCODE_IO_GENERAL;
//STRIP001 /*?*/                 }
//STRIP001 /*?*/
//STRIP001 /*?*/                // do not switch from temporary file in case of nonfile protocol
//STRIP001 /*?*/            }
//STRIP001 /*?*/        }
/*?*/     }
/*N*/ }

//------------------------------------------------------------------
//STRIP001 void SfxMedium::DoInternalBackup_Impl( const ::ucb::Content& aOriginalContent,
//STRIP001                                     const String& aPrefix,
//STRIP001                                     const String& aExtension,
//STRIP001                                     const String& aDestDir )
//STRIP001 {
//STRIP001  if ( pImp->m_aBackupURL.getLength() )
//STRIP001      return; // the backup was done already
//STRIP001
//STRIP001  ::utl::TempFile aTransactTemp( aPrefix, &aExtension, &aDestDir );
//STRIP001  aTransactTemp.EnableKillingFile( sal_False );
//STRIP001
//STRIP001  INetURLObject aBackObj( aTransactTemp.GetURL() );
//STRIP001  ::rtl::OUString aBackupName = aBackObj.getName( INetURLObject::LAST_SEGMENT, true, INetURLObject::DECODE_WITH_CHARSET );
//STRIP001
//STRIP001  Reference < ::com::sun::star::ucb::XCommandEnvironment > xDummyEnv;
//STRIP001  ::ucb::Content aBackupCont;
//STRIP001  if( ::ucb::Content::create( aDestDir, xDummyEnv, aBackupCont ) )
//STRIP001  {
//STRIP001      try
//STRIP001      {
//STRIP001          if( aBackupCont.transferContent( aOriginalContent,
//STRIP001                                          ::ucb::InsertOperation_COPY,
//STRIP001                                          aBackupName,
//STRIP001                                          NameClash::OVERWRITE ) )
//STRIP001          {
//STRIP001              pImp->m_aBackupURL = aBackObj.GetMainURL( INetURLObject::NO_DECODE );
//STRIP001              pImp->m_bRemoveBackup = sal_True;
//STRIP001          }
//STRIP001      }
//STRIP001      catch( Exception& )
//STRIP001      {}
//STRIP001  }
//STRIP001
//STRIP001  if ( !pImp->m_aBackupURL.getLength() )
//STRIP001      aTransactTemp.EnableKillingFile( sal_True );
//STRIP001 }

//------------------------------------------------------------------
/*?*/ void SfxMedium::DoInternalBackup_Impl( const ::ucb::Content& aOriginalContent )
/*?*/ {{DBG_BF_ASSERT(0, "STRIP");}//STRIP001
//STRIP001  if ( pImp->m_aBackupURL.getLength() )
//STRIP001      return; // the backup was done already
//STRIP001
//STRIP001  ::rtl::OUString aFileName =  GetURLObject().getName( INetURLObject::LAST_SEGMENT,
//STRIP001                                                      true,
//STRIP001                                                      INetURLObject::NO_DECODE );
//STRIP001
//STRIP001  sal_Int32 nPrefixLen = aFileName.lastIndexOf( '.' );
//STRIP001  String aPrefix = ( nPrefixLen == -1 ) ? aFileName : aFileName.copy( 0, nPrefixLen );
//STRIP001  String aExtension = ( nPrefixLen == -1 ) ? String() : String(aFileName.copy( nPrefixLen ));
//STRIP001      String aBakDir = SvtPathOptions().GetBackupPath();
//STRIP001
//STRIP001  DoInternalBackup_Impl( aOriginalContent, aPrefix, aExtension, aBakDir );
//STRIP001
//STRIP001  if ( !pImp->m_aBackupURL.getLength() )
//STRIP001  {
//STRIP001      // the copiing to the backup catalog failed ( for example because
//STRIP001      // of using an encrypted partition as target catalog )
//STRIP001      // since the user did not specify to make backup explicitly
//STRIP001      // office should try to make backup in another place,
//STRIP001      // target catalog does not look bad for this case ( and looks
//STRIP001      // to be the only way for encrypted partitions )
//STRIP001
//STRIP001      INetURLObject aDest = GetURLObject();
//STRIP001      if ( aDest.removeSegment() )
//STRIP001          DoInternalBackup_Impl( aOriginalContent, aPrefix, aExtension, aDest.GetMainURL( INetURLObject::NO_DECODE ) );
//STRIP001  }
/*?*/ }


//------------------------------------------------------------------
//STRIP001 void SfxMedium::DoBackup_Impl()
//STRIP001 {
//STRIP001      // source file name is the logical name of this medium
//STRIP001     INetURLObject aSource( GetURLObject() );
//STRIP001
//STRIP001  // there is nothing to backup in case source file does not exist
//STRIP001  if ( !::utl::UCBContentHelper::IsDocument( aSource.GetMainURL( INetURLObject::NO_DECODE ) ) )
//STRIP001      return;
//STRIP001
//STRIP001     sal_Bool        bSuccess = sal_False;
//STRIP001
//STRIP001     // get path for backups
//STRIP001     String aBakDir = SvtPathOptions().GetBackupPath();
//STRIP001     if( aBakDir.Len() )
//STRIP001     {
//STRIP001         // create content for the parent folder ( = backup folder )
//STRIP001         ::ucb::Content  aContent;
//STRIP001         Reference < ::com::sun::star::ucb::XCommandEnvironment > xEnv;
//STRIP001         if( ::ucb::Content::create( aBakDir, xEnv, aContent ) )
//STRIP001      {
//STRIP001          // save as ".bak" file
//STRIP001          INetURLObject aDest( aBakDir );
//STRIP001          aDest.insertName( aSource.getName() );
//STRIP001          aDest.setExtension( DEFINE_CONST_UNICODE( "bak" ) );
//STRIP001          String aFileName = aDest.getName( INetURLObject::LAST_SEGMENT, true, INetURLObject::DECODE_WITH_CHARSET );
//STRIP001
//STRIP001          // create a content for the source file
//STRIP001          ::ucb::Content aSourceContent;
//STRIP001          if ( ::ucb::Content::create( aSource.GetMainURL( INetURLObject::NO_DECODE ), xEnv, aSourceContent ) )
//STRIP001          {
//STRIP001              try
//STRIP001              {
//STRIP001                  // do the transfer ( copy source file to backup dir )
//STRIP001                  bSuccess = aContent.transferContent( aSourceContent,
//STRIP001                                                      ::ucb::InsertOperation_COPY,
//STRIP001                                                      aFileName,
//STRIP001                                                      NameClash::OVERWRITE );
//STRIP001                  if( bSuccess )
//STRIP001                  {
//STRIP001                      pImp->m_aBackupURL = aDest.GetMainURL( INetURLObject::NO_DECODE );
//STRIP001                      pImp->m_bRemoveBackup = sal_False;
//STRIP001                  }
//STRIP001              }
//STRIP001              catch ( ::com::sun::star::uno::Exception& )
//STRIP001              {
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001     if ( !bSuccess )
//STRIP001  {
//STRIP001      eError = ERRCODE_ABORT;
//STRIP001         WarningBox( NULL, SfxResId( MSG_WARNING_BACKUP ) ).Execute();
//STRIP001  }
//STRIP001 }

//------------------------------------------------------------------
/*N*/ void SfxMedium::ClearBackup_Impl()
/*N*/ {
/*N*/   if( pImp->m_bRemoveBackup )
/*N*/   {
#ifdef DBG_UTIL
/*?*/       if ( pImp->m_aBackupURL.getLength() )
/*?*/           if ( !::utl::UCBContentHelper::Kill( pImp->m_aBackupURL ) )
/*?*/               DBG_ERROR("Couldn't remove backup file!");
#endif
/*?*/       pImp->m_bRemoveBackup = sal_False;
/*N*/   }
/*N*/
/*N*/   pImp->m_aBackupURL = ::rtl::OUString();
/*N*/ }

//----------------------------------------------------------------
/*N*/ void SfxMedium::GetMedium_Impl()
/*N*/ {
/*N*/     if ( !pInStream )
/*N*/     {
/*N*/         pImp->bDownloadDone = sal_False;
/*N*/         pImp->bStreamReady = sal_False;
/*N*/         Reference< ::com::sun::star::task::XInteractionHandler > xInteractionHandler = GetInteractionHandler();
/*N*/
/*N*/         ::utl::UcbLockBytesHandler* pHandler = pImp->aHandler;
/*N*/         INetProtocol eProt = GetURLObject().GetProtocol();
/*N*/         if ( eProt != INET_PROT_HTTP && eProt != INET_PROT_FTP || aName.Len() )
/*N*/             pHandler = NULL;
/*N*/         BOOL bSynchron = pImp->bForceSynchron || ! pImp->aDoneLink.IsSet();
/*N*/         SFX_ITEMSET_ARG( pSet, pStreamItem, SfxUnoAnyItem, SID_INPUTSTREAM, sal_False);
/*N*/         if ( pStreamItem )
/*N*/         {
/*N*/             if ( GetContent().is() && !IsReadOnly() )
/*N*/             {
/*?*/                 try
/*?*/                 {
/*?*/                     Any aAny = pImp->aContent.getPropertyValue( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("IsReadOnly" )) );
/*?*/                     BOOL bReadonly;
/*?*/                     if ( ( aAny >>= bReadonly ) && bReadonly )
/*?*/                     {
/*?*/                         GetItemSet()->Put( SfxBoolItem(SID_DOC_READONLY, sal_True));
/*?*/                         SetOpenMode(SFX_STREAM_READONLY, sal_False);
/*?*/                     }
/*?*/                 }
/*?*/                 catch ( ::com::sun::star::uno::Exception& )
/*?*/                 {
/*?*/                 }
/*N*/             }
/*N*/
/*N*/             Reference < ::com::sun::star::io::XInputStream > xStream;
/*N*/             if ( ( pStreamItem->GetValue() >>= xStream ) && xStream.is() )
/*N*/                 pImp->xLockBytes = ::utl::UcbLockBytes::CreateInputLockBytes( xStream );
/*N*/             Done_Impl( pImp->xLockBytes.Is() ? pImp->xLockBytes->GetError() : ERRCODE_IO_NOTSUPPORTED );
/*N*/         }
/*N*/         else
/*N*/         {
/*N*/             SFX_ITEMSET_ARG( GetItemSet(), pItem, SfxBoolItem, SID_DOC_READONLY, sal_False);
/*N*/             BOOL bAllowReadOnlyMode = pItem ? pItem->GetValue() : TRUE;
/*N*/             BOOL bIsWritable = ( nStorOpenMode & STREAM_WRITE );
/*N*/
/*N*/             SFX_ITEMSET_ARG( GetItemSet(), pPostDataItem, SfxUnoAnyItem, SID_POSTDATA, sal_False);
/*N*/             SFX_ITEMSET_ARG( GetItemSet(), pContentTypeItem, SfxStringItem, SID_CONTENT_TYPE, sal_False);
/*N*/             SFX_ITEMSET_ARG( GetItemSet(), pRefererItem, SfxStringItem, SID_REFERER, sal_False);
/*N*/
/*N*/           ::rtl::OUString aReferer;
/*N*/           if ( pRefererItem )
/*N*/               aReferer = pRefererItem->GetValue();
/*N*/
/*N*/             if ( pPostDataItem )
/*N*/           {
/*?*/                 DBG_ASSERT( bAllowReadOnlyMode, "Strange open mode!" );
/*?*/               bIsWritable = FALSE;
/*?*/                 GetItemSet()->Put( SfxBoolItem(SID_DOC_READONLY, sal_True));
/*?*/                 SetOpenMode(SFX_STREAM_READONLY, sal_False);
/*?*/
/*?*/               ::rtl::OUString aMimeType;
/*?*/               if ( pContentTypeItem )
/*?*/                   aMimeType = pContentTypeItem->GetValue();
/*?*/               else
/*?*/                   aMimeType = ::rtl::OUString::createFromAscii( "application/x-www-form-urlencoded" );
/*?*/
/*?*/               Reference < XInputStream > xPostData;
/*?*/               if ( pPostDataItem )
/*?*/               {
/*?*/                     Any aAny = pPostDataItem->GetValue();
/*?*/                     aAny >>= xPostData;
/*?*/               }
/*?*/
/*?*/                 pImp->xLockBytes = ::utl::UcbLockBytes::CreateLockBytes(
/*?*/                         GetContent(), aReferer, aMimeType, xPostData, xInteractionHandler, pHandler );
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               // no callbacks for opening read/write because we might try readonly later
/*N*/                 pImp->bDontCallDoneLinkOnSharingError = ( bIsWritable && bAllowReadOnlyMode );
/*N*/               if ( pImp->bDontCallDoneLinkOnSharingError )
/*N*/               {
/*N*/                   ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionHandler > aTempHandler =
/*N*/                           new SfxMediumHandler_Impl( xInteractionHandler );
/*N*/                   pImp->xLockBytes = ::utl::UcbLockBytes::CreateLockBytes(
/*N*/                         GetContent(), Sequence < PropertyValue >(), nStorOpenMode, aTempHandler );
/*N*/               }
/*N*/               else
/*N*/                   pImp->xLockBytes = ::utl::UcbLockBytes::CreateLockBytes(
/*N*/                       GetContent(), Sequence < PropertyValue >(), nStorOpenMode, xInteractionHandler, bIsWritable ? NULL : pHandler );
/*N*/           }
/*N*/
/*N*/             if ( !pImp->xLockBytes.Is() )
/*N*/             {
/*N*/                 pImp->bDontCallDoneLinkOnSharingError = sal_False;
/*N*/                 Done_Impl( ERRCODE_IO_NOTEXISTS );
/*N*/             }
/*N*/             else if ( pImp->xLockBytes->GetError() == ERRCODE_IO_ACCESSDENIED && bIsWritable && bAllowReadOnlyMode ||
/*N*/                     pImp->xLockBytes->GetError() == ERRCODE_IO_NOTSUPPORTED && bIsWritable )
/*N*/             {
/*?*/                 if ( pImp->xLockBytes->GetError() == ERRCODE_IO_ACCESSDENIED )
/*?*/                 {
/*?*/                     GetItemSet()->Put( SfxBoolItem(SID_DOC_READONLY, sal_True));
/*?*/                     SetOpenMode(SFX_STREAM_READONLY, sal_False);
/*?*/                 }
/*?*/
/*?*/                 ResetError();
/*?*/                 pImp->bDownloadDone = sal_False;
/*?*/                 pImp->bDontCallDoneLinkOnSharingError = sal_False;
/*?*/                 pImp->xLockBytes = ::utl::UcbLockBytes::CreateLockBytes(
/*?*/                         GetContent(), Sequence < PropertyValue >(), SFX_STREAM_READONLY, xInteractionHandler, pHandler );
/*?*/
/*?*/               if ( !pHandler && !pImp->bDownloadDone )
/*?*/                     Done_Impl( pImp->xLockBytes->GetError() );
/*?*/             }
/*?*/             else if ( !pHandler && !pImp->bDownloadDone )
/*?*/                 // opening readwrite is always done synchronously
/*?*/                 Done_Impl( pImp->xLockBytes->GetError() );
/*N*/         }
/*N*/
/*N*/         if ( pImp->xLockBytes.Is() && !GetError() )
/*N*/         {
/*N*/             if ( bSynchron )
/*N*/                 pImp->xLockBytes->SetSynchronMode( sal_True );
/*N*/             if ( !pImp->bDownloadDone )
/*?*/                 pImp->pCancellable = new UcbLockBytesCancellable_Impl( pImp->xLockBytes, pImp->GetCancelManager(),
/*?*/                                       GetURLObject().GetMainURL( INetURLObject::NO_DECODE ) );
/*N*/             pInStream = new SvStream( pImp->xLockBytes );
/*N*/             pInStream->SetBufferSize( 4096 );
/*N*/             pImp->bStreamReady = sal_True;
/*N*/         }
/*N*/     }

/*N*/     // Download completion happened while pInStream was constructed
/*N*/     if ( pImp->bDownloadDone )
/*N*/         Done_Impl( GetError() );
/*N*/
/*N*/ }

//------------------------------------------------------------------
/*N*/ SfxPoolCancelManager* SfxMedium::GetCancelManager_Impl() const
/*N*/ {
/*N*/     return pImp->GetCancelManager();
/*N*/ }

//------------------------------------------------------------------
/*N*/ void SfxMedium::SetCancelManager_Impl( SfxPoolCancelManager* pMgr )
/*N*/ {
/*N*/     pImp->xCancelManager = pMgr;
/*N*/ }

//----------------------------------------------------------------
/*N*/ void SfxMedium::CancelTransfers()
/*N*/ {
/*N*/     if( pImp->xCancelManager.Is() )
/*N*/         pImp->xCancelManager->Cancel();
/*N*/ }

//----------------------------------------------------------------
/*
String SfxMedium::GetStatusString( const SvProgressArg* pArg )
{
    String aString;
    StringList_Impl aSL( SfxResId( RID_DLSTATUS2 ), (USHORT)pArg->eStatus );
    USHORT nTotal = 0;

    if ( pArg->eStatus == SVBINDSTATUS_ENDDOWNLOADDATA && nTotal <= 1 )
        return aString;

    if( aSL )
    {
        INetURLObject aObj( pArg->rStatus );
        aString = aSL.GetString();
        aString.SearchAndReplaceAscii( "$(HOST)", aObj.GetHost() );
        String aTarget = aObj.GetFull();
        if( aTarget.Len() <= 1 && pArg->eStatus != SVBINDSTATUS_CONNECTING )
            aTarget = aObj.GetHost();
        if( pArg->nMax )
        {
            aTarget += DEFINE_CONST_UNICODE( " (" );
            AddNumber_Impl( aTarget, pArg->nMax );
            aTarget += ')';
        }

        aString.SearchAndReplaceAscii( "$(TARGET)",aTarget );
        String aNumber;
        AddNumber_Impl( aNumber, pArg->nProgress );
        if( pArg->nRate )
        {
            aNumber+= DEFINE_CONST_UNICODE( " (" );
            AddNumber_Impl( aNumber, (ULONG)pArg->nRate );
            aNumber+= DEFINE_CONST_UNICODE( "/s)" );
        }
        if( pArg->nMax && pArg->nProgress && pArg->nMax != pArg->nProgress )
        {
            aNumber += DEFINE_CONST_UNICODE( " [" );
            float aPerc = pArg->nProgress / (float)pArg->nMax;
            aNumber += String::CreateFromInt32( (USHORT)(aPerc * 100) );
            aNumber += DEFINE_CONST_UNICODE( "%]" );
        }
        aString.SearchAndReplaceAscii( "$(BYTE)", aNumber );
    }
    return aString;
}
*/

/*N*/ sal_Bool SfxMedium::IsRemote()
/*N*/ {
/*N*/     return bRemote;
/*N*/ }

//------------------------------------------------------------------

/*N*/ void SfxMedium::SetUpdatePickList(sal_Bool bVal)
/*N*/ {
/*N*/     if(!pImp)
/*?*/         pImp = new SfxMedium_Impl( this );
/*N*/     pImp->bUpdatePickList = bVal;
/*N*/ }
//------------------------------------------------------------------

/*N*/ sal_Bool SfxMedium::IsUpdatePickList() const
/*N*/ {
/*N*/     return pImp? pImp->bUpdatePickList: sal_True;
/*N*/ }
//----------------------------------------------------------------

/*N*/ void SfxMedium::SetDoneLink( const Link& rLink )
/*N*/ {
/*N*/     pImp->aDoneLink = rLink;
/*N*/ }

//----------------------------------------------------------------

/*N*/ void SfxMedium::SetDataAvailableLink( const Link& rLink )
/*N*/ {
/*N*/     pImp->aAvailableLink = rLink;
/*N*/ }

//----------------------------------------------------------------
/*N*/ void SfxMedium::StartDownload()
/*N*/ {
/*N*/     GetInStream();
/*N*/ }

/*N*/ void SfxMedium::DownLoad( const Link& aLink )
/*N*/ {
/*N*/     SetDoneLink( aLink );
/*N*/     GetInStream();
/*N*/     if ( pInStream && !aLink.IsSet() )
/*N*/     {
/*N*/         while( !pImp->bDownloadDone )
/*?*/             Application::Yield();
/*N*/     }
/*N*/ }

//------------------------------------------------------------------
/*N*/ void SfxMedium::Init_Impl()
/*  [Beschreibung]
    Setzt in den Logischen Namen eine gueltige ::com::sun::star::util::URL (Falls zuvor ein Filename
    drin war) und setzt den physikalschen Namen auf den Filenamen, falls
    vorhanden.
 */

/*N*/ {
/*N*/   Reference< XOutputStream > rOutStream;
/*N*/     pImp->pVersions = NULL;
/*N*/
/*N*/     SFX_ITEMSET_ARG( pSet, pSalvageItem, SfxStringItem, SID_DOC_SALVAGE, sal_False);
/*N*/     if( aLogicName.Len() )
/*N*/     {
/*N*/         INetURLObject aUrl( aLogicName );
/*N*/         INetProtocol eProt = aUrl.GetProtocol();
/*N*/         if ( eProt == INET_PROT_NOT_VALID )
/*N*/         {
/*?*/             DBG_ERROR ( "Unknown protocol!" );
/*N*/         }
/*N*/         else
/*N*/         {
/*N*/             // try to convert the URL into a physical name - but never change a physical name
/*N*/             // physical name may be set if the logical name is changed after construction
/*N*/             if ( !aName.Len() )
/*N*/                 ::utl::LocalFileHelper::ConvertURLToPhysicalName( GetURLObject().GetMainURL( INetURLObject::NO_DECODE ), aName );
/*N*/             else
/*?*/                 DBG_ASSERT( pSalvageItem, "Suspicious change of logical name!" );
/*N*/         }
/*N*/     }
/*N*/
/*N*/     if ( pSalvageItem && pSalvageItem->GetValue().Len() )
/*N*/         aLogicName = pSalvageItem->GetValue();
/*N*/
/*N*/   // in case output stream is by mistake here
/*N*/   // clear the reference
/*N*/     SFX_ITEMSET_ARG( pSet, pOutStreamItem, SfxUnoAnyItem, SID_OUTPUTSTREAM, sal_False);
/*N*/   if( pOutStreamItem
/*N*/    && ( !( pOutStreamItem->GetValue() >>= rOutStream )
/*N*/           || !aLogicName.CompareToAscii( "private:stream", 14 ) == COMPARE_EQUAL ) )
/*N*/   {
/*?*/       pSet->ClearItem( SID_OUTPUTSTREAM );
/*?*/       DBG_ERROR( "Unexpected Output stream parameter!\n" );
/*N*/   }
/*N*/
/*N*/     SetIsRemote_Impl();
/*N*/ }

//------------------------------------------------------------------
/*N*/ SfxMedium::SfxMedium()
/*N*/ :   IMPL_CTOR(),
/*N*/     bRoot( sal_False ),
/*N*/     pURLObj(0),
/*N*/
/*N*/     pSet(0),
/*N*/     pImp(new SfxMedium_Impl( this )),
/*N*/     pFilter(0)
/*N*/ {
/*N*/     Init_Impl();
/*N*/ }
//------------------------------------------------------------------

/*?*/ SfxMedium::SfxMedium( const SfxMedium& rMedium, sal_Bool bTemporary )
/*?*/ :   IMPL_CTOR(),
/*?*/     bRoot(sal_True),
/*?*/     pURLObj( rMedium.pURLObj ? new INetURLObject(*rMedium.pURLObj) : 0 ),
/*?*/     pImp(new SfxMedium_Impl( this ))
/*?*/ {
/*?*/     bDirect       = rMedium.IsDirect();
/*?*/     nStorOpenMode = rMedium.GetOpenMode();
/*?*/     if ( !bTemporary )
/*?*/         aName = rMedium.aName;
/*?*/
/*?*/     pImp->bIsTemp = bTemporary;
/*?*/     DBG_ASSERT( ! rMedium.pImp->bIsTemp, "Temporaeres Medium darf nicht kopiert werden" );
/*?*/     aLogicName = rMedium.aLogicName;
/*?*/     pSet =  rMedium.GetItemSet() ? new SfxItemSet(*rMedium.GetItemSet()) : 0;
/*?*/     pFilter = rMedium.pFilter;
/*?*/     Init_Impl();
/*?*/     if( bTemporary )
/*?*/         CreateTempFile();
/*?*/
/*?*/     if ( rMedium.pImp->pEaMgr )
/*?*/         GetEaMgr();
/*?*/ }

//------------------------------------------------------------------

/*N*/ void SfxMedium::UseInteractionHandler( BOOL bUse )
/*N*/ {
/*N*/     pImp->bAllowDefaultIntHdl = bUse;
/*N*/ }

//------------------------------------------------------------------

/*N*/ ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionHandler >
/*N*/ SfxMedium::GetInteractionHandler()
/*N*/ {
/*N*/     // if interaction isnt allowed explicitly ... return empty reference!
/*N*/     if ( !pImp->bUseInteractionHandler )
/*?*/         return ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionHandler >();
/*N*/
/*N*/     // search a possible existing handler inside cached item set
/*N*/     if ( pSet )
/*N*/     {
/*N*/         ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionHandler > xHandler;
/*N*/         SFX_ITEMSET_ARG( pSet, pHandler, SfxUnoAnyItem, SID_INTERACTIONHANDLER, sal_False);
/*N*/         if ( pHandler && (pHandler->GetValue() >>= xHandler) && xHandler.is() )
/*N*/             return xHandler;
/*N*/     }
/*N*/
/*N*/     // if default interaction isnt allowed explicitly ... return empty reference!
/*N*/     if ( !pImp->bAllowDefaultIntHdl )
/*N*/         return ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionHandler >();
/*N*/
/*N*/     // otherwhise return cached default handler ... if it exist.
/*?*/     if ( pImp->xInteraction.is() )
/*?*/         return pImp->xInteraction;
/*?*/
/*?*/     // create default handler and cache it!
/*?*/     ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xFactory = ::legacy_binfilters::getLegacyProcessServiceFactory();
/*?*/     if ( xFactory.is() )
/*?*/     {
/*?*/         pImp->xInteraction = ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionHandler >( xFactory->createInstance( DEFINE_CONST_UNICODE("com.sun.star.task.InteractionHandler") ), ::com::sun::star::uno::UNO_QUERY );
/*?*/         return pImp->xInteraction;
/*?*/     }
/*?*/
/*?*/   return ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionHandler >();
/*N*/ }

//------------------------------------------------------------------

/*N*/ void SfxMedium::SetFilter( const SfxObjectFactory& rFact, const String & rFilter )
/*N*/ {
/*N*/     SetFilter(  rFact.GetFilterContainer()->GetFilter(rFilter) );
/*N*/ }
//----------------------------------------------------------------

/*N*/ void SfxMedium::SetFilter( const SfxFilter* pFilterP, sal_Bool bResetOrig )
/*N*/ {
/*N*/     pFilter = pFilterP;
/*N*/     pImp->nFileVersion = 0;
/*N*/ }
//----------------------------------------------------------------

/*N*/ const SfxFilter* SfxMedium::GetOrigFilter( sal_Bool bNotCurrent ) const
/*N*/ {
/*N*/     return ( pImp->pOrigFilter || bNotCurrent ) ? pImp->pOrigFilter : pFilter;
/*N*/ }
//----------------------------------------------------------------

/*?*/ void SfxMedium::SetOrigFilter_Impl( const SfxFilter* pFilter )
/*?*/ {
/*?*/     pImp->pOrigFilter = pFilter;
/*?*/ }
//------------------------------------------------------------------

/*N*/ void SfxMedium::Close()
/*N*/ {
/*N*/     if ( aStorage.Is() )
/*N*/     {
/*N*/         // don't close the streams if they belong to the
/*N*/         // storage
/*N*/
/*N*/         const SvStream *pStream = aStorage->GetSvStream();
/*N*/         if ( pStream && pStream == pInStream )
/*N*/         {
/*N*/             pInStream = NULL;
/*N*/             pImp->xInputStream = Reference < XInputStream >();
/*N*/             pImp->xLockBytes.Clear();
/*N*/             if ( pSet )
/*N*/                 pSet->ClearItem( SID_INPUTSTREAM );
/*N*/             aStorage->SetDeleteStream( TRUE );
/*N*/         }
/*N*/         else if ( pStream && pStream == pOutStream )
/*N*/         {
/*?*/             pOutStream = NULL;
/*?*/             aStorage->SetDeleteStream( TRUE );
/*N*/         }
/*N*/
/*N*/         CloseStorage();
/*N*/     }
/*N*/
/*N*/     if ( pInStream )
/*N*/         CloseInStream_Impl();
/*N*/
/*N*/     if ( pOutStream )
/*?*/         CloseOutStream_Impl();
/*N*/
/*N*/     if ( pSet )
/*N*/         pSet->ClearItem( SID_CONTENT );
/*N*/
/*N*/     pImp->aContent = ::ucb::Content();
/*N*/ }

//------------------------------------------------------------------

//STRIP001 void SfxMedium::RefreshName_Impl()
//STRIP001 {
//STRIP001 #if 0   //(dv)
//STRIP001     if ( pImp->aContent.get().is() )
//STRIP001     {
//STRIP001         String aNameP = pImp->xAnchor->GetViewURL();
//STRIP001         pImp->aOrigURL = aNameP;
//STRIP001         aLogicName = aNameP;
//STRIP001         DELETEZ( pURLObj );
//STRIP001         if (aLogicName.Len())
//STRIP001             aLogicName = GetURLObject().GetMainURL( INetURLObject::NO_DECODE );
//STRIP001         SetIsRemote_Impl();
//STRIP001     }
//STRIP001 #endif  //(dv)
//STRIP001 }

/*N*/ void SfxMedium::SetIsRemote_Impl()
/*N*/ {
/*N*/     INetURLObject aObj( GetName() );
/*N*/     switch( aObj.GetProtocol() )
/*N*/     {
/*N*/         case INET_PROT_FTP:
/*N*/         case INET_PROT_HTTP:
/*N*/         case INET_PROT_HTTPS:
/*N*/         case INET_PROT_POP3:
/*N*/         case INET_PROT_NEWS:
/*N*/         case INET_PROT_IMAP:
/*N*/ //        case INET_PROT_OUT:
/*N*/         case INET_PROT_VIM:
/*N*/             bRemote = TRUE; break;
/*N*/         default:
/*N*/             bRemote = ( GetName().CompareToAscii( "private:msgid", 13 ) == COMPARE_EQUAL );
/*N*/             break;
/*N*/     }
/*N*/
/*N*/     // Da Dateien, die Remote geschrieben werden zur Uebertragung auch
/*N*/     // gelesen werden koennen muessen
/*N*/     if( bRemote )
/*N*/         nStorOpenMode |= STREAM_READ;
/*N*/ }



//STRIP001 void SfxMedium::SetName( const String& aNameP, sal_Bool bSetOrigURL )
//STRIP001 {
//STRIP001     if( !pImp->aOrigURL.Len() )
//STRIP001         pImp->aOrigURL = aLogicName;
//STRIP001     if( bSetOrigURL )
//STRIP001         pImp->aOrigURL = aNameP;
//STRIP001     aLogicName = aNameP;
//STRIP001     DELETEZ( pURLObj );
//STRIP001     pImp->aContent = ::ucb::Content();
//STRIP001     Init_Impl();
//STRIP001 }

//----------------------------------------------------------------
/*N*/ const String& SfxMedium::GetOrigURL() const
/*N*/ {
/*N*/     return !pImp->aOrigURL.Len() ? (String &)aLogicName : pImp->aOrigURL;
/*N*/ }

//----------------------------------------------------------------

/*N*/ void SfxMedium::SetPhysicalName_Impl( const String& rNameP )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001     if ( rNameP != aName )
//STRIP001     {
//STRIP001         if( pImp->pTempFile )
//STRIP001         {
//STRIP001             delete pImp->pTempFile;
//STRIP001             pImp->pTempFile = NULL;
//STRIP001         }
//STRIP001
//STRIP001         if ( aName.Len() || rNameP.Len() )
//STRIP001             pImp->aContent = ::ucb::Content();
//STRIP001
//STRIP001         aName = rNameP;
//STRIP001         bTriedStorage = sal_False;
//STRIP001         pImp->bIsStorage = sal_False;
//STRIP001     }
/*N*/ }

//----------------------------------------------------------------
//STRIP001 void SfxMedium::MoveTempTo_Impl( SfxMedium* pMedium )
//STRIP001 {
//STRIP001     if ( pMedium && pMedium != this && pImp->pTempFile )
//STRIP001     {
//STRIP001         if( pMedium->pImp->pTempFile )
//STRIP001             delete pMedium->pImp->pTempFile;
//STRIP001         pMedium->pImp->pTempFile = pImp->pTempFile;
//STRIP001
//STRIP001      pImp->pTempFile->EnableKillingFile( sal_True );
//STRIP001      pImp->pTempFile = NULL;
//STRIP001
//STRIP001      pMedium->aName = pMedium->pImp->pTempFile->GetFileName();
//STRIP001
//STRIP001         pMedium->CloseInStream();
//STRIP001      pMedium->CloseStorage();
//STRIP001         pMedium->pImp->aContent = ::ucb::Content();
//STRIP001     }
//STRIP001 }

//------------------------------------------------------------------
//STRIP001 void SfxMedium::SetTemporary( sal_Bool bTemp )
//STRIP001 {
//STRIP001     pImp->bIsTemp = bTemp;
//STRIP001 }

//------------------------------------------------------------------
/*N*/ sal_Bool SfxMedium::IsTemporary() const
/*N*/ {
/*N*/     return pImp->bIsTemp;
/*N*/ }

//------------------------------------------------------------------

/*?*/ sal_Bool SfxMedium::Exists( sal_Bool bForceSession )
/*?*/ {
/*?*/     DBG_ERROR( "Not implemented!" );
/*?*/     return sal_True;
/*?*/ }

//------------------------------------------------------------------

/*N*/ void SfxMedium::ReOpen()
/*N*/ {
/*N*/     BOOL bUseInteractionHandler = pImp->bUseInteractionHandler;
/*N*/     pImp->bUseInteractionHandler = FALSE;
/*N*/     DBG_ASSERT( pFilter, "Kein Filter, aber ReOpen!" );
/*N*/     if( pFilter )
/*N*/     {
/*N*/         if( pFilter->UsesStorage() )
/*N*/             GetStorage();
/*N*/         else
/*N*/             GetInStream();
/*N*/     }
/*N*/
/*N*/     pImp->bUseInteractionHandler = bUseInteractionHandler;
/*N*/ }
//------------------------------------------------------------------
/*N*/ SfxMedium::SfxMedium
/*N*/ (
/*N*/     const String &rName, StreamMode nOpenMode,  sal_Bool bDirectP,
/*N*/     const SfxFilter *pFlt, SfxItemSet *pInSet
/*N*/ )
/*N*/ :   IMPL_CTOR(),
/*N*/     bRoot( sal_False ),
/*N*/     pFilter(pFlt),
/*N*/     pURLObj(0),
/*N*/     pImp(new SfxMedium_Impl( this )),
/*N*/     pSet( pInSet )
/*N*/ {
/*N*/     aLogicName = rName;
/*N*/     nStorOpenMode = nOpenMode;
/*N*/     bDirect = bDirectP;
/*N*/     Init_Impl();
/*N*/ }
//------------------------------------------------------------------

/*N*/ SfxMedium::SfxMedium( SvStorage *pStorage, sal_Bool bRootP )
/*N*/ :   IMPL_CTOR(),
/*N*/     bRoot( bRootP ),
/*N*/     aStorage(pStorage),
/*N*/     pURLObj(0),
/*N*/     pImp( new SfxMedium_Impl( this )),
/*N*/     pSet(0)
/*N*/ {
/*N*/     SfxApplication* pApp = SFX_APP();
/*N*/     sal_uInt32 nFormat = pStorage->GetFormat();
/*N*/     if( !nFormat )
/*N*/     {
/*N*/ #ifdef DBG_UTIL
/*N*/         if( aLogicName.Len() )
/*N*/             DBG_ERROR( "Unbekanntes StorageFormat, versuche eigenes Format" );
/*N*/ #endif
/*N*/         pFilter = SfxObjectFactory::GetDefaultFactory().GetFilterContainer()->
/*N*/             GetFilter( 0 );
/*N*/     }
/*N*/     else
/*N*/         pFilter = pApp->GetFilterMatcher().GetFilter4ClipBoardId( nFormat, 0, 0 );
/*N*/
/*N*/     Init_Impl();
/*N*/
/*N*/     if( !pFilter && nFormat )
/*N*/     {
/*STRIP003*/ pApp->GetFilterMatcher().GetFilter4Content( *this, &pFilter );  // #91292# PowerPoint does not support an OleComp stream,
/*STRIP003*/ if ( !pFilter )                                                 // so GetFilter4ClipBoardId is not able to detect the format,
/*STRIP003*/ {                                                               // for such cases we try to get the filter by GetFilter4Content
/*STRIP003*/    DBG_ERROR( "No Filter for storage found!" );
/*STRIP003*/    pFilter = SfxObjectFactory::GetDefaultFactory().GetFilterContainer()->GetFilter( 0 );
/*STRIP003*/ }
/*N*/     }
/*N*/ }

//------------------------------------------------------------------

/*N*/ SfxMedium::~SfxMedium()
/*N*/ {
/*N*/     /* Attention
        Don't enable CancelTransfers() till you know that the writer/web has changed his asynchronous load
        behaviour. Otherwhise may StyleSheets inside a html file will be loaded at the right time.
        => further the help will be empty then ... #100490#
     */
/*N*/     //CancelTransfers();
/*N*/     ::vos::OClearableGuard aGuard( pImp->aHandler->GetMutex() );
/*N*/     pImp->aHandler->ReleaseMedium();
/*N*/     aGuard.clear();
/*N*/
/*N*/     Close();
/*N*/
/*N*/     delete pSet;
/*N*/
/*N*/     #ifdef  DBG_UTIL
/*N*/     if( pImp->bIsTemp && aName.Len() )
/*N*/     {
/*N*/         String aTemp;
/*N*/         if ( !::utl::LocalFileHelper::ConvertPhysicalNameToURL( aName, aTemp ))
/*N*/           DBG_ERROR("Physical name not convertable!");
/*N*/
/*N*/         if ( !::utl::UCBContentHelper::Kill( aTemp ) )
/*N*/           DBG_ERROR("Couldn't remove temporary file!");
/*N*/     }
/*N*/     #endif
/*N*/
/*N*/     pFilter = 0;
/*N*/
/*N*/     delete pURLObj;
/*N*/     delete pImp;
/*N*/ }
//------------------------------------------------------------------

//STRIP001 void SfxMedium::SetItemSet(SfxItemSet *pNewSet)
//STRIP001 {
//STRIP001     delete pSet;
//STRIP001     pSet = pNewSet;
//STRIP001 }
//------------------------------------------------------------------

/*N*/ void SfxMedium::SetClassFilter( const SvGlobalName & rFilterClass )
/*N*/ {
/*N*/     bSetFilter = sal_True;
/*N*/     aFilterClass = rFilterClass;
/*N*/ }
//----------------------------------------------------------------

/*N*/ const INetURLObject& SfxMedium::GetURLObject() const
/*N*/ {
/*N*/     if( !pURLObj )
/*N*/     {
/*N*/         SfxMedium* pThis = const_cast < SfxMedium* > (this);
/*N*/         pThis->pURLObj = new INetURLObject( aLogicName );
/*N*/       if ( pThis->pURLObj->HasMark() )
/*N*/           (*pThis->pURLObj) = INetURLObject( aLogicName ).GetURLNoMark();
/*N*/     }
/*N*/
/*N*/     return *pURLObj;
/*N*/ }

//----------------------------------------------------------------

//STRIP001 const String& SfxMedium::GetPreRedirectedURL() const
//STRIP001 {
//STRIP001     return pImp->aPreRedirectionURL;
//STRIP001 }
//----------------------------------------------------------------

/*N*/ sal_uInt32 SfxMedium::GetMIMEAndRedirect( String &rName )
/*N*/ {
/* dv !!!! not needed any longer ?
    INetProtocol eProt = GetURLObject().GetProtocol();
    if( eProt == INET_PROT_FTP && SvBinding::ShouldUseFtpProxy( GetURLObject().GetMainURL( INetURLObject::NO_DECODE ) ) )
    {
        Any aAny( UCB_Helper::GetProperty( GetContent(), WID_FLAG_IS_FOLDER ) );
        sal_Bool bIsFolder = FALSE;
        if ( ( aAny >>= bIsFolder ) && bIsFolder )
            return ERRCODE_NONE;
    }

    GetMedium_Impl();
    if( !eError && pImp->xBinding.Is() )
    {
        eError = pImp->xBinding->GetMimeType( rName );

        // Wir koennen keine Parameter wie CharSets usw.
        rName = rName.GetToken( 0, ';' );
        if( !eError )
        {
            if( !pImp->aPreRedirectionURL.Len() )
                pImp->aPreRedirectionURL = aLogicName;
            SetName( pImp->xBinding->GetRedirectedURL() );
        }
        pImp->aExpireTime = pImp->xBinding->GetExpireDateTime();
    }
    return eError;
*/
/*N*/     return 0;
/*N*/ }

//----------------------------------------------------------------

/*N*/ void SfxMedium::SetUsesCache( sal_Bool bUse )
/*N*/ {
/*N*/     pImp->bUsesCache = bUse;
/*N*/ }
//----------------------------------------------------------------

/*N*/ sal_Bool SfxMedium::UsesCache() const
/*N*/ {
/*N*/     return pImp->bUsesCache;
/*N*/ }
//----------------------------------------------------------------

//----------------------------------------------------------------

/*N*/ void SfxMedium::SetReferer( const String& rRefer )
/*N*/ {
/*N*/     pImp->aReferer = rRefer;
/*N*/ }
//----------------------------------------------------------------

//STRIP001 const String& SfxMedium::GetReferer( ) const
//STRIP001 {
//STRIP001     return pImp->aReferer;
//STRIP001 }
//----------------------------------------------------------------

/*N*/ void SfxMedium::SetTransferPriority( sal_uInt16 nPrio )
/*N*/ {
/*N*/     pImp->nPrio = nPrio;
/*N*/ }
//----------------------------------------------------------------

//STRIP001 sal_uInt16 SfxMedium::GetTransferPriority( ) const
//STRIP001 {
//STRIP001     return pImp->nPrio;
//STRIP001 }
//----------------------------------------------------------------

//STRIP001 void SfxMedium::SetExpired_Impl( const DateTime& rDateTime )
//STRIP001 {
//STRIP001     pImp->aExpireTime = rDateTime;
//STRIP001 }
//----------------------------------------------------------------

//STRIP001 sal_Bool SfxMedium::IsExpired() const
//STRIP001 {
//STRIP001     return pImp->aExpireTime.IsValid() && pImp->aExpireTime < DateTime();
//STRIP001 }
//----------------------------------------------------------------

/*N*/ void SfxMedium::ForceSynchronStream_Impl( sal_Bool bForce )
/*N*/ {
/*N*/     if( pInStream )
/*N*/     {
/*N*/         SvLockBytes* pBytes = pInStream->GetLockBytes();
/*N*/         if( pBytes )
/*N*/             pBytes->SetSynchronMode( bForce );
/*N*/     }
/*N*/     pImp->bForceSynchron = bForce;
/*N*/ }
//----------------------------------------------------------------
/* Kann der URL ein MIME Type zugeordnent werden? */
/*N*/ sal_Bool SfxMedium::SupportsMIME_Impl() const
/*N*/ {
/*N*/     INetProtocol eProt = GetURLObject().GetProtocol();
/*N*/     if( eProt == INET_PROT_HTTPS || eProt == INET_PROT_HTTP  )
/*N*/         return sal_True;
/*N*/
/*N*/     if( eProt == INET_PROT_NOT_VALID )
/*N*/         return sal_False;
/*N*/
/*N*/     if( eProt == INET_PROT_FTP )
/*N*/     {
/*N*/         try
/*N*/         {
/*?*/             Any aAny = pImp->aContent.getPropertyValue( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("IsFolder")) );
/*?*/             sal_Bool bIsFolder = FALSE;
/*?*/             if ( ( aAny >>= bIsFolder ) && bIsFolder )
/*?*/                 return SvBinding::ShouldUseFtpProxy( GetURLObject().GetMainURL( INetURLObject::NO_DECODE ) );
/*?*/         }
/*?*/         catch ( ::com::sun::star::uno::Exception& )
/*?*/         {
/*?*/         }
/*N*/     }
/*N*/
/*N*/     return sal_False;
/*N*/ }

//----------------------------------------------------------------
/*N*/ SfxFrame* SfxMedium::GetLoadTargetFrame() const
/*N*/ {
/*N*/     return pImp->wLoadTargetFrame;
/*N*/ }
//----------------------------------------------------------------

/*N*/ void SfxMedium::SetLoadTargetFrame(SfxFrame* pFrame )
/*N*/ {
/*N*/     pImp->wLoadTargetFrame = pFrame;
/*N*/ }
//----------------------------------------------------------------

/*?*/ void SfxMedium::SetStorage_Impl( SvStorage* pStor )
/*?*/ {
/*?*/     aStorage = pStor;
/*?*/ }
//----------------------------------------------------------------

/*N*/ SfxItemSet* SfxMedium::GetItemSet() const
/*N*/ {
/*N*/     if( !pSet ) ((SfxMedium*)this)->pSet =
/*N*/                     new SfxAllItemSet( SFX_APP()->GetPool() );
/*N*/     return pSet;
/*N*/ }
//----------------------------------------------------------------

/*N*/ void SfxMedium::SetLoadEnvironment_Impl( LoadEnvironment_Impl* pEnv )
/*N*/ {
/*N*/     pImp->pLoadEnv = pEnv;
/*N*/ }
//----------------------------------------------------------------

/*?*/ LoadEnvironment_Impl* SfxMedium::GetLoadEnvironment_Impl() const
/*?*/ {
/*?*/     return pImp->pLoadEnv;
/*?*/ }
//----------------------------------------------------------------

/*N*/ SvKeyValueIterator* SfxMedium::GetHeaderAttributes_Impl()
/*N*/ {
/*N*/     if( !pImp->xAttributes.Is() )
/*N*/   {
/*N*/       pImp->xAttributes = SvKeyValueIteratorRef( new SvKeyValueIterator );
/*N*/
/*N*/       if ( GetContent().is() )
/*N*/       {
/*?*/           pImp->bIsCharsetInitialized = sal_True;
/*?*/
/*?*/           try
/*?*/           {
/*?*/               Any aAny = pImp->aContent.getPropertyValue( ::rtl::OUString::createFromAscii( "MediaType" ) );
/*?*/               ::rtl::OUString aContentType;
/*?*/               aAny >>= aContentType;
/*?*/
/*?*/               pImp->xAttributes->Append( SvKeyValue( ::rtl::OUString::createFromAscii( "content-type" ), aContentType ) );
/*?*/           }
/*?*/           catch ( ::com::sun::star::uno::Exception& )
/*?*/           {
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/
/*N*/     return pImp->xAttributes;
/*N*/ }
//----------------------------------------------------------------

/*N*/ SvCompatWeakHdl* SfxMedium::GetHdl()
/*N*/ {
/*N*/     return pImp->GetHdl();
/*N*/ }

/*N*/ sal_Bool SfxMedium::IsDownloadDone_Impl()
/*N*/ {
/*N*/     return pImp->bDownloadDone;
/*N*/ }

/*N*/ SvEaMgr* SfxMedium::GetEaMgr()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001     if ( !pImp->pEaMgr && pFilter )
//STRIP001     {
//STRIP001         /* the stream in the storage is probably not a filestream ( the stream is
//STRIP001             closed anyway! ). Therefor we will always use GetPhysicalName to
//STRIP001             create the SvEaMgr. */
//STRIP001         //  SvStream *pStream = aStorage.Is() ? aStorage->GetTargetSvStream() : NULL;
//STRIP001         //  if ( pStream && pStream->IsA() == ID_FILESTREAM )
//STRIP001         //      pImp->pEaMgr = new SvEaMgr(*(SvFileStream *)pStream);
//STRIP001         //  else
//STRIP001         pImp->pEaMgr = new SvEaMgr( GetPhysicalName() );
//STRIP001     }
//STRIP001
//STRIP001     return pImp->pEaMgr;
/*N*/ }

//----------------------------------------------------------------

/*N*/ void SfxMedium::SetDontCreateCancellable( )
/*N*/ {
/*N*/     pImp->bDontCreateCancellable = sal_True;
/*N*/ }

/*N*/ ::com::sun::star::uno::Reference< ::com::sun::star::io::XInputStream >  SfxMedium::GetInputStream()
/*N*/ {
/*N*/   if ( !pImp->xInputStream.is() )
/*N*/   {
/*N*/       // if pInStream is already opened then we have problem
/*N*/       // probably GetInStream should allways open pInStream based on xInputStream
/*N*/       GetMedium_Impl();
/*N*/   }
/*N*/
/*N*/     return pImp->xInputStream;
/*N*/ }

/*N*/ const SfxVersionTableDtor* SfxMedium::GetVersionList()
/*N*/ {
/*N*/     if ( !pImp->pVersions && GetStorage() )
/*N*/     {
/*N*/         if ( pImp->bIsDiskSpannedJAR )
/*N*/             return NULL;
/*N*/
/*N*/         SvStorageStreamRef aStream =
/*N*/             GetStorage()->OpenStream( DEFINE_CONST_UNICODE( "VersionList" ), SFX_STREAM_READONLY | STREAM_NOCREATE );
/*N*/         if ( aStream.Is() && aStream->GetError() == SVSTREAM_OK )
/*N*/         {
/*?*/             pImp->pVersions = new SfxVersionTableDtor;
/*?*/             pImp->pVersions->Read( *aStream );
/*N*/         }
/*N*/         else
/*N*/         {
/*N*/           SfxVersionTableDtor *pList = new SfxVersionTableDtor;
/*N*/           if ( SfxXMLVersList_Impl::ReadInfo( GetStorage(), pList ) )
/*?*/               pImp->pVersions = pList;
/*N*/           else
/*N*/               delete pList;
/*N*/         }
/*N*/     }
/*N*/
/*N*/     return pImp->pVersions;
/*N*/ }

//STRIP001 SfxVersionTableDtor* SfxMedium::GetVersionList( SvStorage* pStor )
//STRIP001 {
//STRIP001  SfxVersionTableDtor* pVersions = NULL;
//STRIP001
//STRIP001  if( pStor )
//STRIP001  {
//STRIP001         SvStorageStreamRef aStream =
//STRIP001             pStor->OpenStream( DEFINE_CONST_UNICODE( "VersionList" ), SFX_STREAM_READONLY | STREAM_NOCREATE );
//STRIP001         if ( aStream.Is() && aStream->GetError() == SVSTREAM_OK )
//STRIP001         {
//STRIP001             pVersions = new SfxVersionTableDtor;
//STRIP001             pVersions->Read( *aStream );
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001          SfxVersionTableDtor *pList = new SfxVersionTableDtor;
//STRIP001          if ( SfxXMLVersList_Impl::ReadInfo( pStor, pList ) )
//STRIP001              pVersions = pList;
//STRIP001          else
//STRIP001              delete pList;
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     return pVersions;
//STRIP001 }


//STRIP001 sal_uInt16 SfxMedium::AddVersion_Impl( SfxVersionInfo& rInfo )
//STRIP001 {
//STRIP001     if ( GetStorage() )
//STRIP001     {
//STRIP001         if ( !pImp->pVersions )
//STRIP001             pImp->pVersions = new SfxVersionTableDtor;
//STRIP001
//STRIP001         // Einen eindeutigen Namen f"ur den Stream ermitteln
//STRIP001         SvULongs aLongs;
//STRIP001         SfxVersionInfo* pInfo = pImp->pVersions->First();
//STRIP001         while ( pInfo )
//STRIP001         {
//STRIP001             sal_uInt32 nVer = (sal_uInt32) pInfo->aName.Copy(7).ToInt32();
//STRIP001             sal_uInt16 n;
//STRIP001             for ( n=0; n<aLongs.Count(); n++ )
//STRIP001                 if ( nVer<aLongs[n] )
//STRIP001                     break;
//STRIP001
//STRIP001             aLongs.Insert( nVer, n );
//STRIP001             pInfo = pImp->pVersions->Next();
//STRIP001         }
//STRIP001
//STRIP001         sal_uInt16 nKey;
//STRIP001         for ( nKey=0; nKey<aLongs.Count(); nKey++ )
//STRIP001             if ( aLongs[nKey] > ( ULONG ) nKey+1 )
//STRIP001                 break;
//STRIP001
//STRIP001         rInfo.aName = DEFINE_CONST_UNICODE( "Version" );
//STRIP001         rInfo.aName += String::CreateFromInt32( nKey + 1 );
//STRIP001         pInfo = new SfxVersionInfo( rInfo );
//STRIP001         pImp->pVersions->Insert( pInfo, LIST_APPEND );
//STRIP001         return nKey;
//STRIP001     }
//STRIP001
//STRIP001     return 0;
//STRIP001 }

//STRIP001 sal_Bool SfxMedium::RemoveVersion_Impl( const SfxVersionInfo& rInfo )
//STRIP001 {
//STRIP001     if ( !pImp->pVersions )
//STRIP001         return sal_False;
//STRIP001
//STRIP001     SfxVersionInfo* pInfo = pImp->pVersions->First();
//STRIP001     while( pInfo )
//STRIP001     {
//STRIP001         if ( pInfo->aName == rInfo.aName )
//STRIP001         {
//STRIP001             pImp->pVersions->Remove( pInfo );
//STRIP001             delete pInfo;
//STRIP001             return sal_True;
//STRIP001         }
//STRIP001
//STRIP001         pInfo = pImp->pVersions->Next();
//STRIP001     }
//STRIP001
//STRIP001     return sal_False;
//STRIP001 }

//STRIP001 sal_Bool SfxMedium::TransferVersionList_Impl( SfxMedium& rMedium )
//STRIP001 {
//STRIP001     if ( rMedium.pImp->pVersions )
//STRIP001     {
//STRIP001         delete pImp->pVersions;
//STRIP001         pImp->pVersions = new SfxVersionTableDtor( *rMedium.pImp->pVersions );
//STRIP001         return sal_True;
//STRIP001     }
//STRIP001
//STRIP001     return sal_False;
//STRIP001 }

//STRIP001 sal_Bool SfxMedium::SaveVersionList_Impl( sal_Bool bUseXML )
//STRIP001 {
//STRIP001     if ( GetStorage() )
//STRIP001     {
//STRIP001         if ( !pImp->pVersions )
//STRIP001             return sal_True;
//STRIP001
//STRIP001         if ( bUseXML )
//STRIP001         {
//STRIP001             SfxXMLVersList_Impl::WriteInfo( aStorage, pImp->pVersions );
//STRIP001             return sal_True;
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             SvStorageStreamRef aStream =
//STRIP001                 GetStorage()->OpenStream( DEFINE_CONST_UNICODE( "VersionList" ), SFX_STREAM_READWRITE );
//STRIP001             if ( aStream.Is() && aStream->GetError() == SVSTREAM_OK )
//STRIP001             {
//STRIP001                 pImp->pVersions->Write( *aStream );
//STRIP001                 return sal_True;
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     return sal_False;
//STRIP001 }

//----------------------------------------------------------------
/*N*/ sal_Bool SfxMedium::IsReadOnly()
/*N*/ {
/*N*/     sal_Bool bReadOnly = !( GetOpenMode() & STREAM_WRITE );
/*(dv)  if ( bReadOnly && pURLObj && CntAnchor::IsViewURL( pURLObj->GetMainURL( INetURLObject::NO_DECODE ) ) )
        // Chaos-Storages sind niemals als readonly anzusehen!
        return sal_False;
*/
/*N*/     if ( !bReadOnly )
/*N*/     {
/*N*/         // logisch readonly ge"offnet
/*N*/         SFX_ITEMSET_ARG( GetItemSet(), pItem, SfxBoolItem, SID_DOC_READONLY, sal_False);
/*N*/         if ( pItem )
/*N*/             bReadOnly = pItem->GetValue();
/*N*/     }
/*N*/
/*N*/     return bReadOnly;
/*N*/ }

//----------------------------------------------------------------
//STRIP001 void SfxMedium::TryToSwitchToRepairedTemp()
//STRIP001 {
//STRIP001  // the medium should be opened in repair mode
//STRIP001     SFX_ITEMSET_ARG( GetItemSet(), pRepairItem, SfxBoolItem, SID_REPAIRPACKAGE, FALSE );
//STRIP001     if ( pRepairItem && pRepairItem->GetValue() )
//STRIP001  {
//STRIP001      DBG_ASSERT( aStorage, "Possible performance problem" );
//STRIP001      if ( GetStorage() )
//STRIP001      {
//STRIP001          ::utl::TempFile* pTmpFile = new ::utl::TempFile();
//STRIP001          pTmpFile->EnableKillingFile( sal_True );
//STRIP001          ::rtl::OUString aNewName = pTmpFile->GetFileName();
//STRIP001
//STRIP001          if( aNewName.getLength() )
//STRIP001          {
//STRIP001              SvStorageRef aNewStorage = new SvStorage( sal_True, aNewName, STREAM_WRITE | STREAM_TRUNC, STORAGE_TRANSACTED );
//STRIP001              if ( aNewStorage->GetError() == SVSTREAM_OK )
//STRIP001              {
//STRIP001                  aStorage->CopyTo( &aNewStorage );
//STRIP001                  aNewStorage->Commit();
//STRIP001
//STRIP001                  if ( aNewStorage->GetError() == SVSTREAM_OK )
//STRIP001                  {
//STRIP001                      CloseInStream();
//STRIP001                      CloseStorage();
//STRIP001                      if ( pImp->pTempFile )
//STRIP001                          DELETEZ( pImp->pTempFile );
//STRIP001
//STRIP001                      pImp->pTempFile = pTmpFile;
//STRIP001                      aName = aNewName;
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              SetError( aNewStorage->GetError() );
//STRIP001          }
//STRIP001          else
//STRIP001              SetError( ERRCODE_IO_CANTWRITE );
//STRIP001      }
//STRIP001      else
//STRIP001          SetError( ERRCODE_IO_CANTREAD );
//STRIP001  }
//STRIP001 }

//----------------------------------------------------------------
/*N*/ void SfxMedium::CreateTempFile()
/*N*/ {
/*N*/     if ( pImp->pTempFile )
/*N*/         DELETEZ( pImp->pTempFile );
/*N*/
/*N*/     StreamMode nOpenMode = nStorOpenMode;
/*N*/     GetInStream();
/*N*/     BOOL bCopy = ( nStorOpenMode == nOpenMode && ! ( nOpenMode & STREAM_TRUNC ) );
/*N*/     nStorOpenMode = nOpenMode;
/*N*/     ResetError();
/*N*/
/*N*/     pImp->pTempFile = new ::utl::TempFile();
/*N*/     pImp->pTempFile->EnableKillingFile( sal_True );
/*N*/     aName = pImp->pTempFile->GetFileName();
/*N*/     if ( !aName.Len() )
/*N*/     {
/*N*/         SetError( ERRCODE_IO_CANTWRITE );
/*N*/         return;
/*N*/     }
/*N*/
/*N*/     if ( bCopy )
/*N*/     {
/*N*/         GetOutStream();
/*N*/         if ( pInStream && pOutStream )
/*N*/         {
/*N*/             char        *pBuf = new char [8192];
/*N*/             sal_uInt32   nErr = ERRCODE_NONE;
/*N*/
/*N*/             pInStream->Seek(0);
/*N*/             pOutStream->Seek(0);
/*N*/
/*N*/             while( !pInStream->IsEof() && nErr == ERRCODE_NONE )
/*N*/             {
/*N*/                 sal_uInt32 nRead = pInStream->Read( pBuf, 8192 );
/*N*/                 nErr = pInStream->GetError();
/*N*/                 pOutStream->Write( pBuf, nRead );
/*N*/             }
/*N*/
/*N*/             delete[] pBuf;
/*N*/             CloseInStream();
/*N*/         }
/*N*/         CloseOutStream_Impl();
/*N*/     }
/*N*/     else
/*?*/         CloseInStream();
/*N*/
/*N*/     CloseStorage();
/*N*/ }

//----------------------------------------------------------------
/*N*/ void SfxMedium::CreateTempFileNoCopy()
/*N*/ {
/*N*/     if ( pImp->pTempFile )
/*N*/         delete pImp->pTempFile;
/*N*/
/*N*/     pImp->pTempFile = new ::utl::TempFile();
/*N*/     pImp->pTempFile->EnableKillingFile( sal_True );
/*N*/     aName = pImp->pTempFile->GetFileName();
/*N*/     if ( !aName.Len() )
/*N*/     {
/*?*/         SetError( ERRCODE_IO_CANTWRITE );
/*?*/         return;
/*N*/     }
/*N*/
/*N*/     CloseOutStream_Impl();
/*N*/     CloseStorage();
/*N*/ }

/*N*/ void SfxMedium::SetLoadEnvironment( SfxLoadEnvironment* pEnv )
/*N*/ {
/*N*/     pImp->xLoadRef = pEnv;
/*N*/ }

/*?*/ SfxLoadEnvironment* SfxMedium::GetLoadEnvironment() const
/*?*/ {
/*?*/     return (SfxLoadEnvironment*) &pImp->xLoadRef;
/*?*/ }

//STRIP001 ::rtl::OUString SfxMedium::GetCharset()
//STRIP001 {
//STRIP001     if( !pImp->bIsCharsetInitialized )
//STRIP001  {
//STRIP001      // Set an error in case there is no content?
//STRIP001      if ( GetContent().is() )
//STRIP001      {
//STRIP001          pImp->bIsCharsetInitialized = sal_True;
//STRIP001
//STRIP001          try
//STRIP001          {
//STRIP001              Any aAny = pImp->aContent.getPropertyValue( ::rtl::OUString::createFromAscii( "MediaType" ) );
//STRIP001              ::rtl::OUString aField;
//STRIP001              aAny >>= aField;
//STRIP001
//STRIP001              ::rtl::OString sContent = ::rtl::OUStringToOString( aField, RTL_TEXTENCODING_ASCII_US );
//STRIP001              ByteString sType, sSubType;
//STRIP001              INetContentTypeParameterList aParameters;
//STRIP001
//STRIP001              if( INetContentTypes::parse( sContent, sType, sSubType, &aParameters ) )
//STRIP001              {
//STRIP001                  const INetContentTypeParameter * pCharset = aParameters.find("charset");
//STRIP001                  if (pCharset != 0)
//STRIP001                      pImp->aCharset = pCharset->m_sValue;
//STRIP001              }
//STRIP001          }
//STRIP001          catch ( ::com::sun::star::uno::Exception& )
//STRIP001          {
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return pImp->aCharset;
//STRIP001 }

//STRIP001 void SfxMedium::SetCharset( ::rtl::OUString aChs )
//STRIP001 {
//STRIP001  pImp->bIsCharsetInitialized = sal_True;
//STRIP001  pImp->aCharset = aChs;
//STRIP001 }

//----------------------------------------------------------------
#define nActVersion 1

/*?*/ SvStream& SfxVersionTableDtor::Read( SvStream& rStrm )
/*?*/ {
/*?*/     sal_uInt16 nCount = 0, nVersion = 0;
/*?*/
/*?*/     rStrm >> nVersion;
/*?*/     rStrm >> nCount;
/*?*/
/*?*/     for( sal_uInt16 i=0; i<nCount; ++i )
/*?*/     {
/*?*/         SfxVersionInfo *pNew = new SfxVersionInfo;
/*?*/         rStrm.ReadByteString( pNew->aComment, RTL_TEXTENCODING_UTF8 );
/*?*/         rStrm.ReadByteString( pNew->aName, RTL_TEXTENCODING_UTF8 );
/*?*/         pNew->aCreateStamp.Load( rStrm );
/*?*/         Insert( pNew, LIST_APPEND );
/*?*/     }
/*?*/
/*?*/     return rStrm;
/*?*/ }

/*?*/ SvStream& SfxVersionTableDtor::Write( SvStream& rStream ) const
/*?*/ {
/*?*/     rStream << (sal_uInt16) nActVersion;
/*?*/     rStream << (sal_uInt16) Count();
/*?*/
/*?*/     SfxVersionInfo* pInfo = ((SfxVersionTableDtor*)this)->First();
/*?*/     while( pInfo && rStream.GetError() == SVSTREAM_OK )
/*?*/     {
/*?*/         rStream.WriteByteString( pInfo->aComment, RTL_TEXTENCODING_UTF8 );
/*?*/         rStream.WriteByteString( pInfo->aName, RTL_TEXTENCODING_UTF8 );
/*?*/         pInfo->aCreateStamp.Save( rStream );
/*?*/         pInfo = ((SfxVersionTableDtor*)this)->Next();
/*?*/     }
/*?*/
/*?*/     return rStream;
/*?*/ }

/*N*/ void SfxVersionTableDtor::DelDtor()
/*N*/ {
/*N*/     SfxVersionInfo* pTmp = First();
/*N*/     while( pTmp )
/*N*/     {
/*?*/         delete pTmp;
/*?*/         pTmp = Next();
/*N*/     }
/*N*/     Clear();
/*N*/ }

//STRIP001 SfxVersionTableDtor& SfxVersionTableDtor::operator=( const SfxVersionTableDtor& rTbl )
//STRIP001 {
//STRIP001     DelDtor();
//STRIP001     SfxVersionInfo* pTmp = ((SfxVersionTableDtor&)rTbl).First();
//STRIP001     while( pTmp )
//STRIP001     {
//STRIP001         SfxVersionInfo *pNew = new SfxVersionInfo( *pTmp );
//STRIP001         Insert( pNew, LIST_APPEND );
//STRIP001         pTmp = ((SfxVersionTableDtor&)rTbl).Next();
//STRIP001     }
//STRIP001     return *this;
//STRIP001 }

//----------------------------------------------------------------
//----------------------------------------------------------------
//----------------------------------------------------------------
/*?*/ SfxVersionInfo::SfxVersionInfo()
/*?*/ {
/*?*/ }

//STRIP001 SvStringsDtor* SfxVersionTableDtor::GetVersions() const
//STRIP001 {
//STRIP001     SvStringsDtor *pList = new SvStringsDtor;
//STRIP001     SfxVersionInfo* pInfo = ((SfxVersionTableDtor*) this)->First();
//STRIP001  LocaleDataWrapper aLocaleWrapper( ::legacy_binfilters::getLegacyProcessServiceFactory(), Application::GetSettings().GetLocale() );
//STRIP001     while ( pInfo )
//STRIP001     {
//STRIP001         String *pString = new String( pInfo->aComment );
//STRIP001         (*pString) += DEFINE_CONST_UNICODE( "; " );
//STRIP001         (*pString) += ConvertDateTime_Impl( pInfo->aCreateStamp, aLocaleWrapper );
//STRIP001         pList->Insert( pString, pList->Count() );
//STRIP001         pInfo = ((SfxVersionTableDtor*) this)->Next();
//STRIP001     }
//STRIP001
//STRIP001     return pList;
//STRIP001 }

}
