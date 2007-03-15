/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_objcont.cxx,v $
 *
 *  $Revision: 1.10 $
 *
 *  last change: $Author: obo $ $Date: 2007-03-15 15:24:26 $
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

#include <com/sun/star/uno/Reference.hxx>

#ifndef _COM_SUN_STAR_DOCUMENT_UPDATEDOCMODE_HPP_
#include <com/sun/star/document/UpdateDocMode.hpp>
#endif

#ifndef _CACHESTR_HXX //autogen
#include <tools/cachestr.hxx>
#endif
#ifndef _SV_MSGBOX_HXX //autogen wg. QueryBox
#include <vcl/msgbox.hxx>
#endif
#ifndef _SFXSTYLE_HXX //autogen
#include <svtools/style.hxx>
#endif
#ifndef _SV_WRKWIN_HXX //autogen
#include <vcl/wrkwin.hxx>
#endif

#pragma hdrstop

#include <svtools/stritem.hxx>
#include <svtools/intitem.hxx>
#include <svtools/rectitem.hxx>
#include <svtools/urihelper.hxx>
#include <comphelper/processfactory.hxx>

#ifndef _SFXECODE_HXX
#include <svtools/sfxecode.hxx>
#endif
#ifndef _EHDL_HXX
#include <svtools/ehdl.hxx>
#endif
#ifndef _DATETIME_HXX
#include <tools/datetime.hxx>
#endif
#include <math.h>

#include <svtools/saveopt.hxx>
#include <svtools/useroptions.hxx>
#include <unotools/localfilehelper.hxx>

#include "sfxresid.hxx"
#include "stbmgr.hxx"
#include "dinfdlg.hxx"
#include "fltfnc.hxx"
#include "docfac.hxx"
#include "cfgmgr.hxx"
#include "viewsh.hxx"
#include "objsh.hxx"
#include "objshimp.hxx"
#include "cfgitem.hxx"
#include "evntconf.hxx"
#include "interno.hxx"
#include "sfxhelp.hxx"
#include "dispatch.hxx"
#include "urlframe.hxx"
#include "printer.hxx"
#include "topfrm.hxx"
#include "doctempl.hxx"
#include "doc.hrc"
#include "appdata.hxx"
#include "sfxbasemodel.hxx"
#include "accmgr.hxx"
#include "mnumgr.hxx"
#include "imgmgr.hxx"

#ifndef _SVTOOLS_IMGDEF_HXX
#include <svtools/imgdef.hxx>
#endif

#include "tbxconf.hxx"
#include "docfile.hxx"
#include "objuno.hxx"
#include "request.hxx"

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif

#ifndef _BASMGR_HXX
#include "bf_basic/basmgr.hxx"
#endif

#include "so3/staticbaseurl.hxx"
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;

//====================================================================

#define SFX_WINDOWS_STREAM "SfxWindows"
#define SFX_PREVIEW_STREAM "SfxPreview"

//====================================================================

/*?*/ GDIMetaFile* SfxObjectShell::GetPreviewMetaFile( sal_Bool bFullContent ) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001
/*?*/ }

/*N*/ FASTBOOL SfxObjectShell::SaveWindows_Impl( SvStorage &rStor ) const
/*N*/ {
/*N*/   SvStorageStreamRef xStream = rStor.OpenStream( DEFINE_CONST_UNICODE( SFX_WINDOWS_STREAM ),
/*N*/                                   STREAM_TRUNC | STREAM_STD_READWRITE);
/*N*/   if ( !xStream )
/*N*/       return FALSE;
/*N*/
/*N*/   xStream->SetBufferSize(1024);
/*N*/     xStream->SetVersion( rStor.GetVersion() );
/*N*/
/*N*/     // "uber alle Fenster iterieren (aber aktives Window zuletzt)
/*N*/     SfxViewFrame *pActFrame = SfxViewFrame::Current();
/*N*/     if ( !pActFrame || pActFrame->GetObjectShell() != this )
/*N*/         pActFrame = SfxViewFrame::GetFirst(this);
/*N*/
/*N*/     String aActWinData;
/*N*/     for ( SfxViewFrame *pFrame = SfxViewFrame::GetFirst(this, TYPE(SfxTopViewFrame) ); pFrame;
/*N*/             pFrame = SfxViewFrame::GetNext(*pFrame, this, TYPE(SfxTopViewFrame) ) )
/*N*/     {
/*N*/         // Bei Dokumenten, die Outplace aktiv sind, kann beim Speichern auch schon die View weg sein!
/*N*/         if ( pFrame->GetViewShell() )
/*N*/         {
/*N*/             SfxTopFrame* pTop = (SfxTopFrame*) pFrame->GetFrame();
/*N*/             Window* pWin = pTop->GetTopWindow_Impl();
/*N*/
/*N*/ #if SUPD<613//MUSTINI
/*N*/           char cToken = SfxIniManager::GetToken();
/*N*/ #else
/*N*/           char cToken = ',';
/*N*/ #endif
/*N*/             const BOOL bActWin = pActFrame == pFrame;
/*N*/             String aUserData;
/*N*/             pFrame->GetViewShell()->WriteUserData(aUserData);
/*N*/
/*N*/             // assemble ini-data
/*N*/             String aWinData;
/*N*/             aWinData += String::CreateFromInt32( pFrame->GetCurViewId() );
/*N*/             aWinData += cToken;
/*
            if ( !pWin || pWin->IsMaximized() )
                aWinData += SFX_WINSIZE_MAX;
            else if ( pWin->IsMinimized() )
                aWinData += SFX_WINSIZE_MIN;
            else
*/
/*N*/ #if SUPD<613//MUSTINI
/*N*/             aWinData += SfxIniManager::GetString( pWin->GetPosPixel(), pWin->GetSizePixel() );
/*N*/ #endif
/*N*/             aWinData += cToken;
/*N*/             aWinData += aUserData;
/*N*/
/*N*/             // aktives kennzeichnen
/*N*/             aWinData += cToken;
/*N*/             aWinData += bActWin ? '1' : '0';
/*N*/
/*N*/             // je nachdem merken oder abspeichern
/*N*/             if ( bActWin  )
/*N*/                 aActWinData = aWinData;
/*N*/             else
/*N*/                 xStream->WriteByteString( aWinData );
/*N*/         }
/*N*/     }
/*N*/
/*N*/     // aktives Window hinterher
/*N*/     xStream->WriteByteString( aActWinData );
/*N*/   return !xStream->GetError();
/*N*/ }

//====================================================================

/*N*/ SfxViewFrame* SfxObjectShell::LoadWindows_Impl( SfxTopFrame *pPreferedFrame )
/*N*/ {
/*N*/     DBG_ASSERT( pPreferedFrame, "Can't be implemented in StarPortal!" );
/*N*/     if ( pImp->bLoadingWindows || !pPreferedFrame )
/*N*/       return NULL;
/*N*/
/*N*/     DBG_ASSERT( GetMedium(), "A Medium should exist here!");
/*N*/     if( !GetMedium() )
/*N*/       return 0;
/*N*/
/*N*/   // get correct mode
/*N*/   SfxApplication *pSfxApp = SFX_APP();
/*N*/   SfxViewFrame *pPrefered = pPreferedFrame ? pPreferedFrame->GetCurrentViewFrame() : 0;
/*N*/     SvtSaveOptions aOpt;
/*N*/     BOOL bLoadDocWins = aOpt.IsSaveDocWins() && !pPrefered;
/*N*/     BOOL bLoadDocView = aOpt.IsSaveDocView();
/*N*/
/*N*/     // In a StarPortal not possible at the moment
/*N*/   if ( !bLoadDocView )
/*N*/       return 0;
/*N*/
/*N*/   // try to get viewdata information for XML format
/*N*/   REFERENCE < XVIEWDATASUPPLIER > xViewDataSupplier( GetModel(), ::com::sun::star::uno::UNO_QUERY );
/*N*/   REFERENCE < XINDEXACCESS > xViewData;
/*N*/   SvStorageStreamRef xStream;
/*N*/
/*N*/   // get viewdata information for binary format
/*N*/     SvStorage *pStor = HasName() ? GetStorage() : NULL;
/*N*/     xStream = pStor ? pStor->OpenStream( DEFINE_CONST_UNICODE( SFX_WINDOWS_STREAM ), STREAM_STD_READ ) : 0;
/*N*/   if ( xStream.Is() && xStream->GetError() == ERRCODE_NONE )
/*N*/   {
/*?*/       xStream->SetVersion( pStor->GetVersion() );
/*?*/       xStream->SetBufferSize(1024);
/*N*/   }
/*N*/   else if ( xViewDataSupplier.is() )
/*N*/   {
/*N*/       xViewData = xViewDataSupplier->getViewData();
/*N*/       if ( !xViewData.is() )
/*N*/           return NULL;
/*N*/   }
/*N*/   else
/*N*/       return NULL;
/*N*/
/*?*/     BOOL bOldFormat = TRUE;             // old format : not in StarDesktop 5.x
/*?*/   SfxViewFrame *pActiveFrame = 0;
/*?*/   String aWinData;
/*?*/   char cToken =',';
/*?*/   SfxItemSet *pSet = GetMedium()->GetItemSet();
/*?*/
/*?*/   pImp->bLoadingWindows = TRUE;
/*?*/   BOOL bLoaded = FALSE;
/*?*/   sal_Int32 nView = 0;
/*?*/
/*?*/   // get saved information for all views
/*?*/   while ( TRUE )
/*?*/   {
/*?*/       USHORT nViewId = 0;
/*?*/         FASTBOOL bActive=FALSE, bMaximized=FALSE;
/*?*/       String aPosSize;
/*?*/       String aUserData;                   // used in the binary format
/*?*/       SEQUENCE < PROPERTYVALUE > aSeq;    // used in the XML format
/*?*/       if ( xViewData.is() )
/*?*/       {
/*?*/           // XML format
/*?*/           // active view is the first view in the container
/*?*/           bActive = ( nView == 0 );
/*?*/
/*?*/           if ( nView == xViewData->getCount() )
/*?*/               // finished
/*?*/               break;
/*?*/
/*?*/           // get viewdata and look for the stored ViewId
/*?*/           ::com::sun::star::uno::Any aAny = xViewData->getByIndex( nView++ );
/*?*/           if ( aAny >>= aSeq )
/*?*/           {
/*?*/               for ( sal_Int32 n=0; n<aSeq.getLength(); n++ )
/*?*/               {
/*?*/                   const PROPERTYVALUE& rProp = aSeq[n];
/*?*/                   if ( rProp.Name.compareToAscii("ViewId") == COMPARE_EQUAL )
/*?*/                   {
/*?*/                       ::rtl::OUString aId;
/*?*/                       rProp.Value >>= aId;
/*?*/                       String aTmp( aId );
/*?*/                       aTmp.Erase( 0, 4 );  // format is like in "view3"
/*?*/                       nViewId = (USHORT) aTmp.ToInt32();
/*?*/                       break;
/*?*/                   }
/*?*/               }
/*?*/           }
/*?*/       }
/*?*/       else
/*?*/       {
/*?*/           // binary format
/*?*/           xStream->ReadByteString( aWinData );
/*?*/           if ( !aWinData.Len() )
/*?*/               // reading finished
/*?*/               break;
/*?*/
/*?*/           if ( aWinData.GetToken( 0, cToken ).EqualsAscii( "TASK" ) )
/*?*/           {
/*?*/               // doesn't make any sense with the new task handling using system tasks or browser windows
/*?*/               bOldFormat = FALSE;
/*?*/               continue;
/*?*/           }
/*?*/
/*?*/           nViewId = (USHORT) aWinData.GetToken( 0, cToken ).ToInt32();
/*?*/             if ( bOldFormat )
/*?*/           {
/*?*/                 // Old format
/*?*/               aPosSize = aWinData.GetToken( 1, cToken );
/*?*/               aPosSize.ToLowerAscii();
/*?*/               aUserData = aWinData.GetToken( 2, cToken );
/*?*/               bActive = aWinData.GetToken( 3, cToken ).ToInt32();
/*?*/           }
/*?*/           else
/*?*/           {
/*?*/                 // 5.0-Format, get activity state and UserData
/*?*/               USHORT nPos=0;
/*?*/               bActive = aWinData.GetToken( 3, cToken, nPos ).ToInt32();
/*?*/               aUserData = aWinData.Copy( nPos );
/*?*/           }
/*?*/       }
/*?*/
/*?*/       // load only active view, but current item is not the active one ?
/*?*/       if ( !bLoadDocWins && !bActive )
/*?*/       {
/*?*/           if ( xViewData.is() )
/*?*/               // in XML format the active view is the first one
/*?*/               break;
/*?*/           else
/*?*/               continue;
/*?*/       }
/*?*/
/*?*/       // check for minimized/maximized/size
/*?*/       if ( aPosSize.EqualsAscii( "min" ) )
/*?*/             bMaximized = TRUE;
/*?*/       else if ( aPosSize.EqualsAscii( "min" ) )
/*?*/       {
/*?*/             bMaximized = TRUE;
/*?*/           bActive = FALSE;
/*?*/       }
/*?*/       else
/*?*/             bMaximized = FALSE;
/*?*/
/*?*/       Point aPt;
/*?*/       Size aSz;
/*?*/ #if SUPD<613//MUSTINI
/*?*/         if ( !bMaximized )
/*?*/           SfxIniManager::GetPosSize( aPosSize, aPt, aSz );
/*?*/ #endif
/*?*/
/*?*/       pSet->ClearItem( SID_USER_DATA );
/*?*/       SfxViewFrame *pFrame = 0;
/*?*/       if ( pPrefered )
/*?*/       {
/*?*/           // use the frame from the arguments, but don't set a window size
/*?*/           pFrame = pPrefered;
/*?*/           if ( pFrame->GetViewShell() || !pFrame->GetObjectShell() )
/*?*/           {
/*?*/               pSet->ClearItem( SID_VIEW_POS_SIZE );
/*?*/               pSet->ClearItem( SID_WIN_POSSIZE );
/*?*/               pSet->Put( SfxUInt16Item( SID_VIEW_ID, nViewId ) );
/*?*/
/*?*/               // avoid flickering controllers
/*?*/                 SfxBindings &rBind = pFrame->GetBindings();
/*?*/               rBind.ENTERREGISTRATIONS();
/*?*/
/*?*/               // set document into frame
/*?*/               pPreferedFrame->InsertDocument( this );
/*?*/
/*?*/               // restart controller updating
/*?*/               rBind.LEAVEREGISTRATIONS();
/*?*/           }
/*?*/           else
/*?*/           {
/*?*/               // create new view
/*?*/               DBG_BF_ASSERT(0, "STRIP"); //STRIP001 pFrame->CreateView_Impl( nViewId );
/*?*/           }
/*?*/       }
/*?*/       else
/*?*/       {
/*?*/           if ( bLoadDocWins )
/*?*/           {
/*?*/               // open in the background
/*?*/               pSet->Put( SfxUInt16Item( SID_VIEW_ZOOM_MODE, 0 ) );
/*?*/                 if ( !bMaximized )
/*?*/                   pSet->Put( SfxRectangleItem( SID_VIEW_POS_SIZE, Rectangle( aPt, aSz ) ) );
/*?*/           }
/*?*/
/*?*/           pSet->Put( SfxUInt16Item( SID_VIEW_ID, nViewId ) );
/*?*/
/*?*/           if ( pPreferedFrame )
/*?*/           {
/*?*/               // Frame "ubergeben, allerdings ist der noch leer
/*?*/               pPreferedFrame->InsertDocument( this );
/*?*/               pFrame = pPreferedFrame->GetCurrentViewFrame();
/*?*/           }
/*?*/           else
/*?*/           {
/*?*/               DBG_BF_ASSERT(0, "STRIP"); //STRIP001 pFrame = SfxTopFrame::Create( this, nViewId, FALSE, pSet )->GetCurrentViewFrame();
/*?*/           }
/*?*/
/*?*/           // only temporary data, don't hold it in the itemset
/*?*/           pSet->ClearItem( SID_VIEW_POS_SIZE );
/*?*/           pSet->ClearItem( SID_WIN_POSSIZE );
/*?*/           pSet->ClearItem( SID_VIEW_ZOOM_MODE );
/*?*/       }
/*?*/
/*?*/       bLoaded = TRUE;
/*?*/
/*?*/       // UserData hier einlesen, da es ansonsten immer mit bBrowse=TRUE
/*?*/       // aufgerufen wird, beim Abspeichern wurde aber bBrowse=FALSE verwendet
/*?*/       if ( pFrame && pFrame->GetViewShell() )
/*?*/       {
/*?*/           if ( aUserData.Len() )
/*?*/               pFrame->GetViewShell()->ReadUserData( aUserData, !bLoadDocWins );
/*?*/           else if ( aSeq.getLength() )
/*?*/               pFrame->GetViewShell()->ReadUserDataSequence( aSeq, !bLoadDocWins );
/*?*/       }
/*?*/
/*?*/       // perhaps there are more windows to load
/*?*/       pPreferedFrame = NULL;
/*?*/
/*?*/       if ( bActive )
/*?*/           pActiveFrame = pFrame;
/*?*/
/*?*/       if( pPrefered || !bLoadDocWins )
/*?*/           // load only active window
/*?*/           break;
/*?*/   }
/*?*/
/*?*/   if ( pActiveFrame )
/*?*/   {
/*?*/       if ( !pPrefered )
/*?*/           // activate frame
/*?*/             pActiveFrame->MakeActive_Impl( TRUE );
/*?*/   }
/*?*/
/*?*/   pImp->bLoadingWindows = FALSE;
/*?*/   return pPrefered && bLoaded ? pPrefered : pActiveFrame;
/*N*/ }

//====================================================================

/*N*/ void SfxObjectShell::UpdateDocInfoForSave()
/*N*/ {
/*N*/   if( !pImp->bDoNotTouchDocInfo )
/*N*/   {
/*N*/       SfxDocumentInfo &rDocInfo = GetDocInfo();
/*N*/       rDocInfo.SetTemplateConfig( HasTemplateConfig() );
/*N*/
/*N*/       if ( IsModified() )
/*N*/       {
/*N*/           // Keine Unterschiede mehr zwischen Save, SaveAs
/*N*/           String aUserName = SvtUserOptions().GetFullName();
/*N*/           if ( !rDocInfo.IsUseUserData() )
/*N*/           {
/*N*/               SfxStamp aCreated = rDocInfo.GetCreated();
/*N*/               if ( aUserName == aCreated.GetName() )
/*N*/               {
/*N*/                   aCreated.SetName( String() );
/*N*/                   rDocInfo.SetCreated( aCreated );
/*N*/               }
/*N*/
/*N*/               SfxStamp aPrinted = rDocInfo.GetPrinted();
/*N*/               if ( aUserName == aPrinted.GetName() )
/*N*/               {
/*N*/                   aPrinted.SetName( String() );
/*N*/                   rDocInfo.SetPrinted( aPrinted );
/*N*/               }
/*N*/
/*N*/               aUserName.Erase();
/*N*/           }
/*N*/
/*N*/           rDocInfo.SetChanged( aUserName );
/*N*/           if ( !HasName() || pImp->bIsSaving )
/*N*/               UpdateTime_Impl( rDocInfo );
/*N*/       }
/*N*/
/*N*/       if ( !pImp->bIsSaving )
/*N*/           rDocInfo.SetPasswd( pImp->bPasswd );
/*N*/
/*N*/       Broadcast( SfxDocumentInfoHint( &rDocInfo ) );
/*N*/   }
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ BOOL SfxObjectShell::SaveInfoAndConfig_Impl( SvStorageRef pNewStg )
/*N*/ {
/*N*/   //Demnaechst mal gemeinsame Teile zusammenfassen
/*N*/   UpdateDocInfoForSave();
/*N*/
/*N*/ #if !defined( SFX_KEY_MAXPREVIEWSIZE ) && defined( TFPLUGCOMM )
/*N*/ #define SFX_KEY_MAXPREVIEWSIZE SFX_KEY_ISFREE
/*N*/ #endif
/*N*/
/*N*/ #ifdef MI_doch_wieder_die_alte_preview
/*N*/   String aMaxSize = SFX_INIMANAGER()->Get( SFX_KEY_MAXPREVIEWSIZE );
/*N*/   ULONG nMaxSize = aMaxSize.Len() ? ULONG( aMaxSize ) : 50000;
/*N*/ #else
/*N*/   ULONG nMaxSize = 0L;
/*N*/ #endif
/*N*/   if( nMaxSize && !GetDocInfo().IsPasswd() &&
/*N*/       SFX_CREATE_MODE_STANDARD == eCreateMode )
/*N*/   {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/   }

/*N*/   if( pImp->bIsSaving )
/*N*/   {
/*N*/       //!! kein Aufruf der Basisklasse wegen doppeltem Aufruf in Persist
/*N*/       //if(!SfxObjectShell::Save())
/*N*/       //  return FALSE;
/*N*/       SvStorageRef aRef = GetMedium()->GetStorage();
/*N*/       if ( aRef.Is() )
/*N*/       {
/*N*/           SfxDocumentInfo& rDocInfo = GetDocInfo();
/*N*/           rDocInfo.Save(pNewStg);
/*N*/
/*N*/           // wenn es sich um ein Dokument lokales Basic handelt, dieses
/*N*/           // schreiben
/*N*/           if ( pImp->pBasicMgr )
/*?*/                 pImp->pBasicMgr->Store(
                        *pNewStg,
                        so3::StaticBaseUrl::GetBaseURL(
                            INetURLObject::NO_DECODE) );
/*N*/           else
/*N*/           {
/*N*/               String aURL;
/*N*/               if( HasName() )
/*N*/                   aURL = GetMedium()->GetName();
/*N*/               else
/*?*/               {
/*?*/                   aURL = GetDocInfo().GetTemplateFileName();
/*?*/                   // Bei Templates keine URL...
/*?*/                   aURL = so3::StaticBaseUrl::SmartRelToAbs( aURL );
/*N*/               }
/*N*/ #ifndef TFPLUGCOMM
/*N*/                 BasicManager::CopyBasicData(
                        GetStorage(), aURL,
                        so3::StaticBaseUrl::GetBaseURL(
                            INetURLObject::NO_DECODE),
                        pNewStg );
/*N*/ #endif
/*N*/           }
/*N*/
/*N*/           // Windows-merken
/*N*/           if ( TRUE ) HACK(aus config)
/*N*/               SaveWindows_Impl( *pNewStg );
/*N*/
/*N*/           // Konfiguration schreiben
/*N*/           if ( GetConfigManager() )
/*N*/           {
/* //!MBA
                if ( rDocInfo.HasTemplateConfig() )
                {
                    const String aTemplFileName( rDocInfo.GetTemplateFileName() );
                    if ( aTemplFileName.Len() )
                    {
                        INetURLObject aURL( aTemplFileName );
                        DBG_ASSERT( aURL.GetProtocol() != INET_PROT_NOT_VALID, "Illegal URL !" );

                        SvStorageRef aStor = new SvStorage( aURL.GetMainURL( INetURLObject::NO_DECODE ) );
                        if ( SVSTREAM_OK == aStor->GetError() )
                        {
                            GetConfigManager()->StoreConfiguration(aStor);
                            if (aRef->IsStream(SfxConfigManager::GetStreamName()))
                                aRef->Remove(SfxConfigManager::GetStreamName());
                        }
                    }
                }
                else
 */
/*N*/               {
//! MBA                    GetConfigManager()->SetModified( TRUE );
/*?*/                     GetConfigManager()->StoreConfiguration( pNewStg );
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/       return TRUE;
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       //!! kein Aufruf der Basisklasse wegen doppeltem Aufruf in Persist
/*N*/       //if(!SfxObjectShell::SaveAs(pNewStg))
/*N*/       //  return FALSE;
/*N*/       SfxApplication *pSfxApp = SFX_APP();
/*N*/       SfxMedium *pActMed = GetMedium();
/*N*/
/*N*/       // alte DocInfo laden
/*N*/       SfxDocumentInfo &rDocInfo = GetDocInfo();
/*N*/
/*N*/       // DocInfo speichern
/*N*/       rDocInfo.Save( pNewStg );
/*N*/
/*N*/       // wenn es sich um ein Dokument lokales Basic handelt, dieses schreiben
/*N*/       if ( pImp->pBasicMgr )
/*N*/             pImp->pBasicMgr->Store(
                    *pNewStg,
                    so3::StaticBaseUrl::GetBaseURL(INetURLObject::NO_DECODE) );
/*N*/ #ifndef MI_NONOS
/*N*/       else
/*N*/       {
/*?*/           String aURL;
/*?*/           if( HasName() )
/*?*/               aURL = GetMedium()->GetName();
/*?*/           else
/*?*/           {
/*?*/               aURL = GetDocInfo().GetTemplateFileName();
/*?*/               // Bei Templates keine URL...
/*?*/               aURL = so3::StaticBaseUrl::SmartRelToAbs( aURL );
/*?*/           }
/*?*/ #ifndef TFPLUGCOMM
/*?*/             BasicManager::CopyBasicData(
                    GetStorage(), aURL,
                    so3::StaticBaseUrl::GetBaseURL(INetURLObject::NO_DECODE),
                    pNewStg );
/*?*/ #endif
/*N*/       }
/*N*/ #endif
/*N*/       // Windows-merken
/*N*/       if ( TRUE ) HACK(aus config)
/*N*/           SaveWindows_Impl( *pNewStg );
/*N*/
/*N*/       // Konfiguration schreiben
/*N*/       if (GetConfigManager())
/*N*/       {
/* //!MBA
            if ( rDocInfo.HasTemplateConfig() )
            {
                const String aTemplFileName( rDocInfo.GetTemplateFileName() );
                if ( aTemplFileName.Len() )
                {
                    INetURLObject aURL( aTemplFileName );
                    DBG_ASSERT( aURL.GetProtocol() != INET_PROT_NOT_VALID, "Illegal URL !" );

                    SvStorageRef aStor = new SvStorage( aURL.GetMainURL( INetURLObject::NO_DECODE ) );
                    if ( SVSTREAM_OK == aStor->GetError() )
                    {
                        GetConfigManager()->StoreConfiguration(aStor);
                        if (pNewStg->IsStream(SfxConfigManager::GetStreamName()))
                            pNewStg->Remove(SfxConfigManager::GetStreamName());
                    }
                }
            }
            else
 */
/*N*/           {
//!MBA                GetConfigManager()->SetModified( TRUE );
/*?*/                 GetConfigManager()->StoreConfiguration(pNewStg);
            }
/*N*/       }
/*N*/
/*N*/       return TRUE;
/*N*/   }
/*N*/ }

//--------------------------------------------------------------------

// Bearbeitungszeit aktualisieren
/*N*/ SfxDocumentInfo& SfxObjectShell::UpdateTime_Impl(SfxDocumentInfo &rInfo)
/*N*/ {
/*N*/   // Get old time from documentinfo
/*N*/   Time aOldTime(rInfo.GetTime());
/*N*/
/*N*/   // Initialize some local member! Its neccessary for wollow operations!
/*N*/   DateTime    aNow                    ;   // Date and time at current moment
/*N*/   Time        n24Time     (24,0,0,0)  ;   // Time-value for 24 hours - see follow calculation
/*N*/   ULONG       nDays       = 0         ;   // Count of days between now and last editing
/*N*/   Time        nAddTime    (0)         ;   // Value to add on aOldTime
/*N*/
/*N*/   // Safe impossible cases!
/*N*/   // User has changed time to the past between last editing and now ... its not possible!!!
/*N*/   DBG_ASSERT( !(aNow.GetDate()<pImp->nTime.GetDate()), "Timestamp of last change is in the past ?!..." );
/*N*/
/*N*/   // Do the follow only, if user has NOT changed time to the past.
/*N*/   // Else add a time of 0 to aOldTime ... !!!
/*N*/   if (aNow.GetDate()>=pImp->nTime.GetDate())
/*N*/   {
/*N*/       // Get count of days last editing.
/*N*/       nDays = aNow.GetSecFromDateTime(pImp->nTime.GetDate())/86400 ;
/*N*/
/*N*/       if (nDays==0)
/*N*/       {
/*N*/           // If no day between now and last editing - calculate time directly.
/*N*/             nAddTime    =   (const Time&)aNow - (const Time&)pImp->nTime ;
/*N*/       }
/*N*/       else
/*N*/       // If time of working without save greater then 1 month (!) ....
/*N*/       // we add 0 to aOldTime!
/*N*/       if (nDays<=31)
/*N*/       {
/*N*/           // If 1 or up to 31 days between now and last editing - calculate time indirectly.
/*N*/           // nAddTime = (24h - nTime) + (nDays * 24h) + aNow
/*?*/           --nDays;
/*?*/           nAddTime     =  nDays*n24Time.GetTime() ;
/*?*/           nAddTime    +=  n24Time-(const Time&)pImp->nTime        ;
/*?*/           nAddTime    +=  aNow                    ;
/*N*/       }
/*N*/
/*N*/       aOldTime += nAddTime;
/*N*/   }
/*N*/
/*N*/   rInfo.SetTime(aOldTime.GetTime());
/*N*/   pImp->nTime = aNow;
/*N*/   rInfo.IncDocumentNumber();
/*N*/   //! DocumentNummer
/*N*/ #if 0
/*N*/   const String aDocNo(rInfo.GetUserKey(0).GetWord());
/*N*/   const String aTitle(rInfo.GetUserKey(0).GetTitle());
/*N*/   USHORT nNo = 1;
/*N*/   if ( aDocNo.Len() )
/*N*/   {
/*N*/       nNo = (USHORT)aDocNo;
/*N*/       if(nNo)
/*N*/           ++nNo;
/*N*/       else
/*N*/           nNo = 1;
/*N*/   }
/*N*/   rInfo.SetUserKey(SfxDocUserKey(aTitle, nNo), 0);
/*N*/ #endif
/*N*/   return rInfo;
/*N*/ }

//--------------------------------------------------------------------

/*?*/ SvEmbeddedInfoObject* SfxObjectShell::InsertObject
/*?*/ (
/*?*/   SvEmbeddedObject*   pObj,
/*?*/   const String&       rName
/*?*/ )

/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001
/*?*/ }

//-------------------------------------------------------------------------

/*N*/ SfxConfigManager* SfxObjectShell::GetConfigManager( BOOL bForceCreation )
/*N*/ {
/*N*/     if ( !pImp->pCfgMgr )
/*N*/     {
/*N*/         if ( bForceCreation || HasStorage() && SfxConfigManager::HasConfiguration( *GetStorage() ) )
/*N*/       {
/*N*/             pImp->pCfgMgr = new SfxConfigManager( *this );
/*N*/           SfxConfigItem* pItem = GetEventConfig_Impl( FALSE );
/*N*/           if ( pItem && !pItem->GetConfigManager() )
/*N*/               // imported binary format
/*N*/               pItem->Connect( pImp->pCfgMgr );
/*N*/
/*N*/       }
/*N*/     }
/*N*/
/*N*/   return pImp->pCfgMgr;
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ void SfxObjectShell::SetConfigManager(SfxConfigManager *pMgr)
/*N*/ {
/*N*/ //    if ( pImp->pCfgMgr == SFX_CFGMANAGER() && pMgr)
/*N*/ //        pMgr->Activate(pImp->pCfgMgr);
/*N*/
/*N*/     if ( pImp->pCfgMgr && pImp->pCfgMgr != pMgr )
/*?*/       delete pImp->pCfgMgr;
/*N*/
/*N*/   pImp->pCfgMgr = pMgr;
/*N*/ }

//-------------------------------------------------------------------------

/*N*/ BOOL SfxObjectShell::HasTemplateConfig() const
/*N*/ {
/*N*/ //!MBA    return pImp->bTemplateConfig;
/*N*/     return FALSE;
/*N*/ }

//--------------------------------------------------------------------

/*N*/ SfxStyleSheetBasePool* SfxObjectShell::GetStyleSheetPool()
/*N*/ {
/*N*/   return 0;
/*N*/ }


//--------------------------------------------------------------------

/*N*/ USHORT SfxObjectShell::GetContentCount(USHORT nIdx1,
/*N*/                                        USHORT nIdx2)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectShell::GetContent(String &rText,
/*N*/                               Bitmap &rClosedBitmap,
/*N*/                               Bitmap &rOpenedBitmap,
/*N*/                               BOOL &bCanDel,
/*N*/                               USHORT i,
/*N*/                               USHORT nIdx1,
/*N*/                               USHORT nIdx2 )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void   SfxObjectShell::GetContent(String &rText,
/*N*/                                 Bitmap &rClosedBitmap,
/*N*/                                 Bitmap &rOpenedBitmap,
/*N*/                                 BmpColorMode eColorMode,
/*N*/                                 BOOL &bCanDel,
/*N*/                                 USHORT i,
/*N*/                                 USHORT nIdx1,
/*N*/                                 USHORT nIdx2 )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectShell::LoadStyles
/*N*/ (
    SfxObjectShell &rSource         /*  die Dokument-Vorlage, aus der
                                            die Styles geladen werden sollen */
/*N*/ )

/*  [Beschreibung]

    Diese Methode wird vom SFx gerufen, wenn aus einer Dokument-Vorlage
    Styles nachgeladen werden sollen. Bestehende Styles soll dabei
    "uberschrieben werden. Das Dokument mu"s daher neu formatiert werden.
    Daher werden die Applikationen in der Regel diese Methode "uberladen
    und in ihrer Implementierung die Implementierung der Basisklasse
    rufen.
*/

/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

//--------------------------------------------------------------------

/*N*/ void SfxObjectShell::UpdateFromTemplate_Impl(  )

/*  [Beschreibung]

    Diese interne Methode pr"uft, ob das Dokument aus einem Template
    erzeugt wurde, und ob dieses neuer ist als das Dokument. Ist dies
    der Fall, wird der Benutzer gefragt, ob die Vorlagen (StyleSheets)
    updated werden sollen. Wird dies positiv beantwortet, werden die
    StyleSheets updated.
*/

/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

/*N*/ SfxEventConfigItem_Impl* SfxObjectShell::GetEventConfig_Impl( BOOL bForce )
/*N*/ {
/*N*/     if ( bForce && !pImp->pEventConfig )
/*N*/     {
/*N*/         pImp->pEventConfig = new SfxEventConfigItem_Impl( SFX_ITEMTYPE_DOCEVENTCONFIG,
/*N*/                     SFX_APP()->GetEventConfig(), this );
/*N*/       if (pImp->pCfgMgr)
/*N*/           pImp->pEventConfig->Connect( pImp->pCfgMgr );
/*N*/       pImp->pEventConfig->Initialize();
/*N*/   }
/*N*/
/*N*/   return pImp->pEventConfig;
/*N*/ }

/*N*/ SvStorageRef SfxObjectShell::GetConfigurationStorage( SotStorage* pStor )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return SvStorageRef();//STRIP001
/*N*/ }

/*N*/ SotStorageStreamRef SfxObjectShell::GetConfigurationStream( const String& rName, BOOL bCreate )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return SotStorageStreamRef();//STRIP001
/*N*/ }

/*N*/ SfxAcceleratorManager* SfxObjectShell::GetAccMgr_Impl()
/*N*/ {
/*N*/   // already constructed ?!
/*N*/   if ( pImp->pAccMgr )
/*N*/       return pImp->pAccMgr;
/*N*/
/*N*/   // get the typId ( = ResourceId )
/*N*/   const ResId* pResId = GetFactory().GetAccelId();
/*N*/   if ( !pResId )
/*N*/       return NULL;
/*N*/
/*N*/   if ( GetConfigManager() && pImp->pCfgMgr->HasConfigItem( pResId->GetId() ) )
/*N*/   {
/*N*/         // document has configuration
/*N*/         pImp->pAccMgr = new SfxAcceleratorManager( *pResId, pImp->pCfgMgr );
/*N*/       return pImp->pAccMgr;
/*N*/   }
/*N*/     else
/*N*/         return GetFactory().GetAccMgr_Impl();
/*N*/ }

/*N*/ SfxMenuBarManager* SfxObjectShell::CreateMenuBarManager_Impl( SfxViewFrame* pViewFrame )
/*N*/ {
/*N*/   SfxBindings& rBindings = pViewFrame->GetBindings();
/*N*/   sal_Bool bCheckPlugin = SfxApplication::IsPlugin();
/*N*/   const ResId* pId = bCheckPlugin ? GetFactory().GetPluginMenuBarId() : GetFactory().GetMenuBarId();
/*N*/   DBG_ASSERT( pId && pId->GetId(), "Component must have own window!" );
/*N*/   if ( !pId )
/*N*/       return NULL;
/*N*/
/*N*/     SfxConfigManager *pCfgMgr = SFX_APP()->GetConfigManager_Impl();
/*N*/     if ( GetConfigManager() && pImp->pCfgMgr->HasConfigItem( pId->GetId() ) )
/*N*/         pCfgMgr = pImp->pCfgMgr;
/*N*/
/*N*/     SfxMenuBarManager* pMgr = new SfxMenuBarManager( *pId, rBindings, pCfgMgr, pViewFrame->ISA( SfxInPlaceFrame ) );
/*N*/     return pMgr;
/*N*/ }

/*N*/ SfxImageManager* SfxObjectShell::GetImageManager_Impl()
/*N*/ {
/*N*/     if ( pImp->pImageManager )
/*N*/         return pImp->pImageManager;
/*N*/
/*N*/     // every document has its own ImageManager, but they may use the global configuration!
/*N*/     pImp->pImageManager = new SfxImageManager( this );
/*N*/     return pImp->pImageManager;
/*N*/ }

/*N*/ SfxObjectShellRef MakeObjectShellForOrganizer_Impl( const String& aTargetURL, BOOL bForWriting )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return SfxObjectShellRef();//STRIP001
/*N*/ }

/*N*/ SfxToolBoxConfig* SfxObjectShell::GetToolBoxConfig_Impl()
/*N*/ {
/*N*/     if ( !pImp->pTbxConfig )
/*N*/   {
/*N*/         pImp->pTbxConfig = new SfxToolBoxConfig(
/*N*/           GetConfigManager() ? pImp->pCfgMgr : SFX_APP()->GetConfigManager_Impl() );
/*N*/   }
/*N*/
/*N*/     return pImp->pTbxConfig;
/*N*/ }


/*N*/ sal_Bool SfxObjectShell::IsHelpDocument() const
/*N*/ {
/*N*/     const SfxFilter* pFilter = GetMedium()->GetFilter();
/*N*/     return ( pFilter && pFilter->GetFilterName().CompareToAscii("writer_web_HTML_help") == COMPARE_EQUAL );
/*N*/ }
}
