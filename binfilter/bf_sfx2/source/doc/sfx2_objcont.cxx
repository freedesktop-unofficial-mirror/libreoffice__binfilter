/*************************************************************************
 *
 *  $RCSfile: sfx2_objcont.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:15 $
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
#include "basmgr.hxx"
#include "doctempl.hxx"
#include "doc.hrc"
#include "appdata.hxx"
#include "sfxbasemodel.hxx"
#include "accmgr.hxx"
#include "mnumgr.hxx"
#include "imgmgr.hxx"
#include "tbxconf.hxx"
#include "docfile.hxx"
#include "objuno.hxx"
#include "request.hxx"

#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {

using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;

//====================================================================

#define SFX_WINDOWS_STREAM "SfxWindows"
#define SFX_PREVIEW_STREAM "SfxPreview"

//====================================================================

/*?*/ GDIMetaFile* SfxObjectShell::GetPreviewMetaFile( sal_Bool bFullContent ) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001
//STRIP001  // Nur wenn gerade nicht gedruckt wird, darf DoDraw aufgerufen
//STRIP001  // werden, sonst wird u.U. der Printer abgeschossen !
//STRIP001  SfxViewFrame *pFrame = SfxViewFrame::GetFirst( this );
//STRIP001  if ( pFrame && pFrame->GetViewShell() &&
//STRIP001       pFrame->GetViewShell()->GetPrinter() &&
//STRIP001       pFrame->GetViewShell()->GetPrinter()->IsPrinting() )
//STRIP001       return 0;
//STRIP001
//STRIP001  GDIMetaFile* pFile = new GDIMetaFile;
//STRIP001
//STRIP001  VirtualDevice aDevice;
//STRIP001  aDevice.EnableOutput( FALSE );
//STRIP001
//STRIP001  SfxInPlaceObject* pInPlaceObj = GetInPlaceObject();
//STRIP001  DBG_ASSERT( pInPlaceObj, "Ohne Inplace Objekt keine Grafik" );
//STRIP001  if (pInPlaceObj)
//STRIP001  {
//STRIP001      MapMode aMode( pInPlaceObj->GetMapUnit() );
//STRIP001      aDevice.SetMapMode( aMode );
//STRIP001      pFile->SetPrefMapMode( aMode );
//STRIP001
//STRIP001      Size aTmpSize;
//STRIP001      sal_Int8 nAspect;
//STRIP001      if ( bFullContent )
//STRIP001      {
//STRIP001          nAspect = ASPECT_CONTENT;
//STRIP001          aTmpSize = pInPlaceObj->GetVisArea( nAspect ).GetSize();
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          nAspect = ASPECT_THUMBNAIL;
//STRIP001          aTmpSize = ((SfxObjectShell*)this)->GetFirstPageSize();
//STRIP001      }
//STRIP001
//STRIP001      pFile->SetPrefSize( aTmpSize );
//STRIP001      DBG_ASSERT( aTmpSize.Height()*aTmpSize.Width(),
//STRIP001                  "size of first page is 0, overload GetFirstPageSize or set vis-area!" );
//STRIP001
//STRIP001      pFile->Record( &aDevice );
//STRIP001      pInPlaceObj->DoDraw(
//STRIP001              &aDevice, Point(0,0), aTmpSize,
//STRIP001              JobSetup(), nAspect );
//STRIP001      pFile->Stop();
//STRIP001  }
//STRIP001
//STRIP001  return pFile;
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
//STRIP001 /*?*/        GDIMetaFile* pFile = GetPreviewMetaFile();
//STRIP001 /*?*/        if ( pFile )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            SvCacheStream aStream;
//STRIP001 /*?*/            long nVer = pNewStg->GetVersion();
//STRIP001 /*?*/            aStream.SetVersion( nVer );
//STRIP001 /*?*/            aStream << *pFile;
//STRIP001 /*?*/            if( aStream.Tell() < nMaxSize )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                SvStorageStreamRef xStream = pNewStg->OpenStream(
//STRIP001 /*?*/                    DEFINE_CONST_UNICODE( SFX_PREVIEW_STREAM ),
//STRIP001 /*?*/                    STREAM_TRUNC | STREAM_STD_READWRITE);
//STRIP001 /*?*/                if( xStream.Is() && !xStream->GetError() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    long nVer = pNewStg->GetVersion();
//STRIP001 /*?*/                    xStream->SetVersion( nVer );
//STRIP001 /*?*/                    aStream.Seek( 0L );
//STRIP001 /*?*/                    *xStream << aStream;
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
//STRIP001 /*?*/            delete pFile;
//STRIP001 /*?*/        }
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
/*?*/                 pImp->pBasicMgr->Store( *pNewStg );
/*N*/           else
/*N*/           {
/*N*/               String aURL;
/*N*/               if( HasName() )
/*N*/                   aURL = GetMedium()->GetName();
/*N*/               else
/*?*/               {
/*?*/                   aURL = GetDocInfo().GetTemplateFileName();
/*?*/                   // Bei Templates keine URL...
/*?*/                   aURL = URIHelper::SmartRelToAbs( aURL );
/*N*/               }
/*N*/ #ifndef TFPLUGCOMM
/*N*/                 BasicManager::CopyBasicData( GetStorage(), aURL, pNewStg );
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
/*N*/             pImp->pBasicMgr->Store( *pNewStg );
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
/*?*/               aURL = URIHelper::SmartRelToAbs( aURL );
/*?*/           }
/*?*/ #ifndef TFPLUGCOMM
/*?*/             BasicManager::CopyBasicData( GetStorage(), aURL, pNewStg );
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

//STRIP001 void SfxObjectShell::DocInfoDlg_Impl( SfxDocumentInfo &rDocInfo )
//STRIP001 {
//STRIP001  // anzuzeigenden Dokumentnamen ermitteln
//STRIP001  String aURL, aTitle;
//STRIP001  if ( HasName() && !pImp->aNewName.Len() )
//STRIP001  {
//STRIP001      aURL = GetMedium()->GetName();
//STRIP001      aTitle = GetTitle();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if ( !pImp->aNewName.Len() )
//STRIP001      {
//STRIP001          aURL = DEFINE_CONST_UNICODE( "private:factory/" );
//STRIP001          aURL += String::CreateFromAscii( GetFactory().GetShortName() );
//STRIP001          // aTitle = String( SfxResId( STR_NONAME ) );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          aURL = DEFINE_CONST_UNICODE( "[private:factory/" );
//STRIP001          aURL += String::CreateFromAscii( GetFactory().GetShortName() );
//STRIP001          aURL += DEFINE_CONST_UNICODE( "]" );
//STRIP001          INetURLObject aURLObj( pImp->aNewName );
//STRIP001          aURL += aURLObj.GetMainURL( INetURLObject::DECODE_TO_IURI );
//STRIP001          // aTitle = aURLObj.GetBase();
//STRIP001      }
//STRIP001      aTitle = GetTitle();
//STRIP001  }
//STRIP001
//STRIP001  // Itemset f"ur Dialog aufbereiten
//STRIP001  SfxDocumentInfoItem aDocInfoItem( aURL, rDocInfo );
//STRIP001  if ( !GetSlotState( SID_DOCTEMPLATE ) )
//STRIP001      aDocInfoItem.SetTemplate(FALSE);
//STRIP001  SfxItemSet aSet(GetPool(), SID_DOCINFO, SID_DOCINFO,
//STRIP001                  SID_EXPLORER_PROPS_START, SID_EXPLORER_PROPS_START,
//STRIP001                  0L );
//STRIP001  aSet.Put( aDocInfoItem );
//STRIP001  aSet.Put( SfxStringItem( SID_EXPLORER_PROPS_START, aTitle ) );
//STRIP001
//STRIP001  // Dialog via Factory erzeugen und ausf"uhren
//STRIP001  SfxDocumentInfoDialog *pDlg = CreateDocumentInfoDialog(0, aSet);
//STRIP001  if ( RET_OK == pDlg->Execute() )
//STRIP001  {
//STRIP001      // neue DocInfo aus Dialog holen
//STRIP001      const SfxPoolItem *pItem = 0;
//STRIP001      if ( SFX_ITEM_SET ==
//STRIP001           pDlg->GetOutputItemSet()->GetItemState( SID_DOCINFO, TRUE, &pItem ) )
//STRIP001      {
//STRIP001          rDocInfo = (*(const SfxDocumentInfoItem *)pItem)();
//STRIP001
//STRIP001          // ggf. den Titel des Dokuments neu setzen
//STRIP001          String aNewTitle = rDocInfo.GetTitle();
//STRIP001          aNewTitle.EraseLeadingChars();
//STRIP001          aNewTitle.EraseTrailingChars();
//STRIP001          if ( aTitle != aNewTitle && aNewTitle.Len() )
//STRIP001              SetTitle( aNewTitle );
//STRIP001      }
//STRIP001  }
//STRIP001  delete pDlg;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SfxDocumentInfoDialog* SfxObjectShell::CreateDocumentInfoDialog
//STRIP001 (
//STRIP001  Window*             pParent,
//STRIP001  const SfxItemSet&   rSet
//STRIP001 )
//STRIP001 {
//STRIP001  return new SfxDocumentInfoDialog(pParent, rSet);
//STRIP001 }

//--------------------------------------------------------------------

/*?*/ SvEmbeddedInfoObject* SfxObjectShell::InsertObject
/*?*/ (
/*?*/   SvEmbeddedObject*   pObj,
/*?*/   const String&       rName
/*?*/ )

/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001
//STRIP001  // Objekt erzeugen ist fehlgeschlagen?
//STRIP001  if ( !pObj )
//STRIP001      HACK(Fehlermeldung fehlt)
//STRIP001      return 0;
//STRIP001
//STRIP001  String aName( rName );
//STRIP001  if( !aName.Len() )
//STRIP001  {
//STRIP001         aName = DEFINE_CONST_UNICODE("Object ");
//STRIP001      String aStr;
//STRIP001      USHORT i = 1;
//STRIP001      HACK(Wegen Storage Bug 46033)
//STRIP001      // for-Schleife wegen Storage Bug 46033
//STRIP001      for( USHORT n = 0; n < 100; n++ )
//STRIP001      {
//STRIP001          do
//STRIP001          {
//STRIP001              aStr = aName;
//STRIP001              aStr += String::CreateFromInt32( i );
//STRIP001              i++;
//STRIP001          } while ( Find( aStr ) );
//STRIP001
//STRIP001          SvInfoObjectRef xSub = new SvEmbeddedInfoObject( pObj, aStr );
//STRIP001          if ( Move( xSub, aStr ) ) // Eigentuemer Uebergang
//STRIP001              return (SvEmbeddedInfoObject*) &xSub;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SvInfoObjectRef xSub = new SvEmbeddedInfoObject( pObj, aName );
//STRIP001      if ( Move( xSub, aName ) ) // Eigentuemer Uebergang
//STRIP001          return (SvEmbeddedInfoObject*) &xSub;
//STRIP001  }
//STRIP001  return 0;
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

//STRIP001 void SfxObjectShell::SetTemplateConfig(BOOL bTplConf)
//STRIP001 {
//STRIP001 //    pImp->bTemplateConfig = bTplConf;
//STRIP001 //    DBG_ASSERT(pImp->pCfgMgr || !bTplConf,"Keine Konfiguration in der Vorlage!");
//STRIP001 }

//-------------------------------------------------------------------------

/*N*/ BOOL SfxObjectShell::HasTemplateConfig() const
/*N*/ {
/*N*/ //!MBA    return pImp->bTemplateConfig;
/*N*/     return FALSE;
/*N*/ }

//-------------------------------------------------------------------------
/*
void SfxObjectShell::TransferConfig(SfxObjectShell& rObjSh)
{
    SfxConfigManager *pNewCfgMgr=0, *pOldCfgMgr=0;
    pOldCfgMgr = pImp->pCfgMgr;
    pImp->pCfgMgr = 0;

    pNewCfgMgr = rObjSh.pImp->pCfgMgr;
    rObjSh.pImp->pCfgMgr=0;

    SetConfigManager(pNewCfgMgr);
    rObjSh.SetConfigManager(pOldCfgMgr);
}
*/

//--------------------------------------------------------------------

/*N*/ SfxStyleSheetBasePool* SfxObjectShell::GetStyleSheetPool()
/*N*/ {
/*N*/   return 0;
/*N*/ }

//STRIP001 void SfxObjectShell::SetOrganizerSearchMask(
//STRIP001  SfxStyleSheetBasePool* pPool) const
//STRIP001 {
//STRIP001  pPool->SetSearchMask(SFX_STYLE_FAMILY_ALL,
//STRIP001                       SFXSTYLEBIT_USERDEF | SFXSTYLEBIT_USED);
//STRIP001 }

//--------------------------------------------------------------------

/*N*/ USHORT SfxObjectShell::GetContentCount(USHORT nIdx1,
/*N*/                                        USHORT nIdx2)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001  switch(nIdx1)
//STRIP001  {
//STRIP001      case INDEX_IGNORE:
//STRIP001          return DEF_CONTENT_COUNT;
//STRIP001      case CONTENT_STYLE:
//STRIP001      {
//STRIP001          SfxStyleSheetBasePool *pPool = GetStyleSheetPool();
//STRIP001          if(!pPool)
//STRIP001              return 0;
//STRIP001          SetOrganizerSearchMask(pPool);
//STRIP001          return pPool->Count();
//STRIP001      }
//STRIP001      case CONTENT_MACRO:
//STRIP001          break;
//STRIP001 /*
//STRIP001      case CONTENT_CONFIG:
//STRIP001          return (GetConfigManager() && !HasTemplateConfig()) ?
//STRIP001                      GetConfigManager()->GetItemCount() : 0;
//STRIP001          break;
//STRIP001  */
//STRIP001  }
//STRIP001  return 0;
/*N*/ }


//--------------------------------------------------------------------

//STRIP001 void  SfxObjectShell::TriggerHelpPI(USHORT nIdx1, USHORT nIdx2, USHORT nIdx3)
//STRIP001 {
//STRIP001  if(nIdx1==CONTENT_STYLE && nIdx2 != INDEX_IGNORE) //StyleSheets
//STRIP001  {
//STRIP001      SfxStyleSheetBasePool *pPool = GetStyleSheetPool();
//STRIP001      SetOrganizerSearchMask(pPool);
//STRIP001      SfxStyleSheetBase *pStyle = (*pPool)[nIdx2];
//STRIP001 #ifdef WIR_KOENNEN_WIEDER_HILFE_FUER_STYLESHEETS
//STRIP001      if(pStyle)
//STRIP001      {
//STRIP001          String aHelpFile;
//STRIP001          ULONG nHelpId=pStyle->GetHelpId(aHelpFile);
//STRIP001          SfxHelpPI* pHelpPI = SFX_APP()->GetHelpPI();
//STRIP001          if ( pHelpPI && nHelpId )
//STRIP001              pHelpPI->LoadTopic( nHelpId );
//STRIP001      }
//STRIP001 #endif
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL   SfxObjectShell::CanHaveChilds(USHORT nIdx1,
//STRIP001                                     USHORT nIdx2)
//STRIP001 {
//STRIP001  switch(nIdx1) {
//STRIP001  case INDEX_IGNORE:
//STRIP001      return TRUE;
//STRIP001  case CONTENT_STYLE:
//STRIP001      return INDEX_IGNORE == nIdx2 || !GetStyleSheetPool()? FALSE: TRUE;
//STRIP001  case CONTENT_MACRO:
//STRIP001 //!!    return INDEX_IGNORE == nIdx2? FALSE: TRUE;
//STRIP001      return FALSE;
//STRIP001 /*
//STRIP001  case CONTENT_CONFIG:
//STRIP001      return INDEX_IGNORE == nIdx2 ? FALSE : TRUE;
//STRIP001  */
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

//--------------------------------------------------------------------

/*N*/ void SfxObjectShell::GetContent(String &rText,
/*N*/                               Bitmap &rClosedBitmap,
/*N*/                               Bitmap &rOpenedBitmap,
/*N*/                               BOOL &bCanDel,
/*N*/                               USHORT i,
/*N*/                               USHORT nIdx1,
/*N*/                               USHORT nIdx2 )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  DBG_ERRORFILE( "Non high contrast method called. Please update calling code!" );
//STRIP001  SfxObjectShell::GetContent( rText, rClosedBitmap, rOpenedBitmap, BMP_COLOR_NORMAL, bCanDel, i, nIdx1, nIdx2 );
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
//STRIP001  bCanDel=TRUE;
//STRIP001
//STRIP001  switch(nIdx1)
//STRIP001  {
//STRIP001      case INDEX_IGNORE:
//STRIP001      {
//STRIP001          USHORT nTextResId = 0;
//STRIP001          USHORT nClosedBitmapResId; // evtl. sp"ater mal unterschiedliche
//STRIP001          USHORT nOpenedBitmapResId; // "     "       "   "
//STRIP001          switch(i)
//STRIP001          {
//STRIP001              case CONTENT_STYLE:
//STRIP001                  nTextResId = STR_STYLES;
//STRIP001                  if ( eColorMode == BMP_COLOR_NORMAL )
//STRIP001                  {
//STRIP001                      nClosedBitmapResId= BMP_STYLES_CLOSED;
//STRIP001                      nOpenedBitmapResId= BMP_STYLES_OPENED;
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      nClosedBitmapResId= BMP_STYLES_CLOSED_HC;
//STRIP001                      nOpenedBitmapResId= BMP_STYLES_OPENED_HC;
//STRIP001                  }
//STRIP001                  break;
//STRIP001              case CONTENT_MACRO:
//STRIP001                  nTextResId = STR_MACROS;
//STRIP001                  if ( eColorMode == BMP_COLOR_NORMAL )
//STRIP001                  {
//STRIP001                      nClosedBitmapResId= BMP_STYLES_CLOSED;
//STRIP001                      nOpenedBitmapResId= BMP_STYLES_OPENED;
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      nClosedBitmapResId= BMP_STYLES_CLOSED_HC;
//STRIP001                      nOpenedBitmapResId= BMP_STYLES_OPENED_HC;
//STRIP001                  }
//STRIP001                  break;
//STRIP001 /*
//STRIP001              case CONTENT_CONFIG:
//STRIP001                  nTextResId = STR_CONFIG;
//STRIP001                  nClosedBitmapResId= BMP_STYLES_CLOSED;
//STRIP001                  nOpenedBitmapResId= BMP_STYLES_OPENED;
//STRIP001                  break;
//STRIP001  */
//STRIP001          }
//STRIP001
//STRIP001          if ( nTextResId )
//STRIP001          {
//STRIP001              rText  = String(SfxResId(nTextResId));
//STRIP001              rClosedBitmap = Bitmap(SfxResId(nClosedBitmapResId));
//STRIP001              rOpenedBitmap = Bitmap(SfxResId(nOpenedBitmapResId));
//STRIP001          }
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      case CONTENT_STYLE:
//STRIP001      {
//STRIP001          SfxStyleSheetBasePool *pPool = GetStyleSheetPool();
//STRIP001          SetOrganizerSearchMask(pPool);
//STRIP001          SfxStyleSheetBase *pStyle = (*pPool)[i];
//STRIP001          rText = pStyle->GetName();
//STRIP001          bCanDel=((pStyle->GetMask() & SFXSTYLEBIT_USERDEF)
//STRIP001                   == SFXSTYLEBIT_USERDEF);
//STRIP001          rClosedBitmap = rOpenedBitmap =
//STRIP001              GetStyleFamilyBitmap(pStyle->GetFamily(), eColorMode );
//STRIP001      }
//STRIP001          break;
//STRIP001      case CONTENT_MACRO:
//STRIP001          break;
//STRIP001 /*
//STRIP001      case CONTENT_CONFIG:
//STRIP001          if ( GetConfigManager() && !HasTemplateConfig())
//STRIP001          {
//STRIP001              rText = GetConfigManager()->GetItem(i);
//STRIP001              bCanDel = GetConfigManager()->CanDelete(i);
//STRIP001          }
//STRIP001          else
//STRIP001              rText = String();
//STRIP001          rClosedBitmap = Bitmap(SfxResId(BMP_STYLES_CLOSED));
//STRIP001          rOpenedBitmap = Bitmap(SfxResId(BMP_STYLES_OPENED));
//STRIP001          break;
//STRIP001 */
//STRIP001  }
/*N*/ }

//--------------------------------------------------------------------
//STRIP001 Bitmap SfxObjectShell::GetStyleFamilyBitmap( SfxStyleFamily eFamily )
//STRIP001 {
//STRIP001  DBG_ERRORFILE( "Non high contrast method called. Please update calling code!" );
//STRIP001  return SfxObjectShell::GetStyleFamilyBitmap( eFamily, BMP_COLOR_NORMAL );
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 Bitmap SfxObjectShell::GetStyleFamilyBitmap(SfxStyleFamily eFamily, BmpColorMode eColorMode )
//STRIP001 {
//STRIP001  USHORT nResId = 0;
//STRIP001  switch(eFamily)
//STRIP001  {
//STRIP001      case SFX_STYLE_FAMILY_CHAR:
//STRIP001          nResId = ( eColorMode == BMP_COLOR_NORMAL ) ? BMP_STYLES_FAMILY1 : BMP_STYLES_FAMILY1_HC;
//STRIP001          break;
//STRIP001      case SFX_STYLE_FAMILY_PARA:
//STRIP001          nResId = ( eColorMode == BMP_COLOR_NORMAL ) ? BMP_STYLES_FAMILY2 : BMP_STYLES_FAMILY2_HC;
//STRIP001          break;
//STRIP001      case SFX_STYLE_FAMILY_FRAME:
//STRIP001          nResId = ( eColorMode == BMP_COLOR_NORMAL ) ? BMP_STYLES_FAMILY3 : BMP_STYLES_FAMILY3_HC;
//STRIP001          break;
//STRIP001      case SFX_STYLE_FAMILY_PAGE :
//STRIP001          nResId = ( eColorMode == BMP_COLOR_NORMAL ) ? BMP_STYLES_FAMILY4 : BMP_STYLES_FAMILY4_HC;
//STRIP001          break;
//STRIP001  }
//STRIP001
//STRIP001  if ( nResId )
//STRIP001      return Bitmap(SfxResId(nResId));
//STRIP001  else
//STRIP001      return Bitmap();
//STRIP001 }


//--------------------------------------------------------------------

//STRIP001 BOOL SfxObjectShell::Insert(SfxObjectShell &rSource,
//STRIP001                            USHORT nSourceIdx1,
//STRIP001                            USHORT nSourceIdx2,
//STRIP001                            USHORT nSourceIdx3,
//STRIP001                            USHORT &nIdx1,
//STRIP001                            USHORT &nIdx2,
//STRIP001                            USHORT &nIdx3,
//STRIP001                            USHORT &nDeleted)
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001
//STRIP001  if (INDEX_IGNORE == nIdx1 && CONTENT_STYLE == nSourceIdx1)
//STRIP001      nIdx1 = CONTENT_STYLE;
//STRIP001
//STRIP001  if (CONTENT_STYLE == nSourceIdx1 && CONTENT_STYLE == nIdx1)
//STRIP001  {
//STRIP001      SfxStyleSheetBasePool* pHisPool  = rSource.GetStyleSheetPool();
//STRIP001      SfxStyleSheetBasePool* pMyPool   = GetStyleSheetPool();
//STRIP001      SetOrganizerSearchMask(pHisPool);
//STRIP001      SetOrganizerSearchMask(pMyPool);
//STRIP001
//STRIP001      SfxStyleSheetBase* pHisSheet = (*pHisPool)[nSourceIdx2];
//STRIP001
//STRIP001      // Einfuegen ist nur dann noetig, wenn ein StyleSheet
//STRIP001      // zwischen unterschiedlichen(!) Pools bewegt wird
//STRIP001
//STRIP001      if (pMyPool != pHisPool)
//STRIP001      {
//STRIP001          if (INDEX_IGNORE == nIdx2)
//STRIP001          {
//STRIP001              nIdx2 = pMyPool->Count();
//STRIP001          }
//STRIP001
//STRIP001          // wenn so eine Vorlage schon existiert: loeschen!
//STRIP001          String aOldName(pHisSheet->GetName());
//STRIP001          SfxStyleFamily eOldFamily = pHisSheet->GetFamily();
//STRIP001
//STRIP001          SfxStyleSheetBase* pExist = pMyPool->Find(aOldName, eOldFamily);
//STRIP001          // USHORT nOldHelpId = pExist->GetHelpId(??? VB ueberlegt sich was);
//STRIP001          BOOL bUsedOrUserDefined;
//STRIP001          if( pExist )
//STRIP001          {
//STRIP001              bUsedOrUserDefined =
//STRIP001                  pExist->IsUsed() || pExist->IsUserDefined();
//STRIP001              if( ErrorHandler::HandleError(
//STRIP001                  *new MessageInfo( ERRCODE_SFXMSG_STYLEREPLACE, aOldName ) )
//STRIP001                  != ERRCODE_BUTTON_OK )
//STRIP001                  return FALSE;
//STRIP001              else
//STRIP001              {
//STRIP001                  pMyPool->Replace( *pHisSheet, *pExist );
//STRIP001                  SetModified( TRUE );
//STRIP001                  nIdx2 = nIdx1 = INDEX_IGNORE;
//STRIP001                  return TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          SfxStyleSheetBase& rNewSheet = pMyPool->Make(
//STRIP001              aOldName, eOldFamily,
//STRIP001              pHisSheet->GetMask(), nIdx2);
//STRIP001
//STRIP001          // ItemSet der neuen Vorlage fuellen
//STRIP001          rNewSheet.GetItemSet().Set(pHisSheet->GetItemSet());
//STRIP001
//STRIP001          // wer bekommt den Neuen als Parent? wer benutzt den Neuen als Follow?
//STRIP001          SfxStyleSheetBase* pTestSheet = pMyPool->First();
//STRIP001          while (pTestSheet)
//STRIP001          {
//STRIP001              if (pTestSheet->GetFamily() == eOldFamily &&
//STRIP001                  pTestSheet->HasParentSupport() &&
//STRIP001                  pTestSheet->GetParent() == aOldName)
//STRIP001              {
//STRIP001                  pTestSheet->SetParent(aOldName);
//STRIP001                  // Verknuepfung neu aufbauen
//STRIP001              }
//STRIP001
//STRIP001              if (pTestSheet->GetFamily() == eOldFamily &&
//STRIP001                  pTestSheet->HasFollowSupport() &&
//STRIP001                  pTestSheet->GetFollow() == aOldName)
//STRIP001              {
//STRIP001                  pTestSheet->SetFollow(aOldName);
//STRIP001                  // Verknuepfung neu aufbauen
//STRIP001              }
//STRIP001
//STRIP001              pTestSheet = pMyPool->Next();
//STRIP001          }
//STRIP001          bUsedOrUserDefined =
//STRIP001              rNewSheet.IsUsed() || rNewSheet.IsUserDefined();
//STRIP001
//STRIP001
//STRIP001          // hat der Neue einen Parent? wenn ja, mit gleichem Namen bei uns suchen
//STRIP001          if (pHisSheet->HasParentSupport())
//STRIP001          {
//STRIP001              const String& rParentName = pHisSheet->GetParent();
//STRIP001              if (0 != rParentName.Len())
//STRIP001              {
//STRIP001                  SfxStyleSheetBase* pParentOfNew =
//STRIP001                      pMyPool->Find(rParentName, eOldFamily);
//STRIP001                  if (pParentOfNew)
//STRIP001                      rNewSheet.SetParent(rParentName);
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          // hat der Neue einen Follow? wenn ja, mit gleichem
//STRIP001          // Namen bei uns suchen
//STRIP001          if (pHisSheet->HasFollowSupport())
//STRIP001          {
//STRIP001              const String& rFollowName = pHisSheet->GetFollow();
//STRIP001              if (0 != rFollowName.Len())
//STRIP001              {
//STRIP001                  SfxStyleSheetBase* pFollowOfNew =
//STRIP001                      pMyPool->Find(rFollowName, eOldFamily);
//STRIP001                  if (pFollowOfNew)
//STRIP001                      rNewSheet.SetFollow(rFollowName);
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          SetModified( TRUE );
//STRIP001          if( !bUsedOrUserDefined ) nIdx2 = nIdx1 = INDEX_IGNORE;
//STRIP001
//STRIP001          bRet = TRUE;
//STRIP001      }
//STRIP001      else
//STRIP001          bRet = FALSE;
//STRIP001  }
//STRIP001 /*
//STRIP001  else if (nSourceIdx1 == CONTENT_CONFIG)
//STRIP001  {
//STRIP001      nIdx1 = CONTENT_CONFIG;
//STRIP001
//STRIP001      SfxConfigManager *pCfgMgr = SFX_CFGMANAGER();
//STRIP001      if (!GetConfigManager() || HasTemplateConfig())
//STRIP001      {
//STRIP001          SetConfigManager(new SfxConfigManager(0, pCfgMgr));
//STRIP001          SetTemplateConfig(FALSE);
//STRIP001          if (this == Current())
//STRIP001              GetConfigManager()->Activate(pCfgMgr);
//STRIP001      }
//STRIP001
//STRIP001      if (GetConfigManager()->CopyItem(
//STRIP001          nSourceIdx2, nIdx2, rSource.GetConfigManager()))
//STRIP001      {
//STRIP001          SetModified(TRUE);
//STRIP001          bRet = TRUE;
//STRIP001             SFX_APP()->GetDispatcher_Impl()->Update_Impl(TRUE);
//STRIP001      }
//STRIP001  }
//STRIP001 */
//STRIP001  return bRet;
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 BOOL SfxObjectShell::Remove
//STRIP001 (
//STRIP001  USHORT nIdx1,
//STRIP001  USHORT nIdx2,
//STRIP001  USHORT nIdx3
//STRIP001 )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001
//STRIP001  if (CONTENT_STYLE == nIdx1)
//STRIP001  {
//STRIP001      SfxStyleSheetBasePool* pMyPool  = GetStyleSheetPool();
//STRIP001
//STRIP001      SetOrganizerSearchMask(pMyPool);
//STRIP001
//STRIP001      SfxStyleSheetBase* pMySheet =  (*pMyPool)[nIdx2];
//STRIP001      String aName(pMySheet->GetName());
//STRIP001      String aEmpty;
//STRIP001      SfxStyleFamily  eFamily = pMySheet->GetFamily();
//STRIP001      if (pMySheet)
//STRIP001      {
//STRIP001          pMyPool->Erase(pMySheet);
//STRIP001          bRet = TRUE;
//STRIP001      }
//STRIP001
//STRIP001      SfxStyleSheetBase* pTestSheet = pMyPool->First();
//STRIP001      while (pTestSheet)
//STRIP001      {
//STRIP001          if (pTestSheet->GetFamily() == eFamily &&
//STRIP001              pTestSheet->HasParentSupport() &&
//STRIP001              pTestSheet->GetParent() == aName)
//STRIP001          {
//STRIP001              pTestSheet->SetParent(aEmpty); // Verknuepfung aufloesen
//STRIP001          }
//STRIP001
//STRIP001          if (pTestSheet->GetFamily() == eFamily &&
//STRIP001              pTestSheet->HasFollowSupport() &&
//STRIP001              pTestSheet->GetFollow() == aName)
//STRIP001          {
//STRIP001              pTestSheet->SetFollow(aEmpty); // Verknuepfung aufloesen
//STRIP001          }
//STRIP001
//STRIP001          pTestSheet = pMyPool->Next();
//STRIP001      }
//STRIP001      if(bRet)
//STRIP001          SetModified( TRUE );
//STRIP001  }
//STRIP001 /*
//STRIP001  else if (nIdx1 == CONTENT_CONFIG)
//STRIP001  {
//STRIP001      if (GetConfigManager()->RemoveItem(nIdx2))
//STRIP001      {
//STRIP001          SetModified(TRUE);
//STRIP001          bRet = TRUE;
//STRIP001             SFX_APP()->GetDispatcher_Impl()->Update_Impl(TRUE);
//STRIP001      }
//STRIP001  }
//STRIP001 */
//STRIP001  return bRet;
//STRIP001 }

//--------------------------------------------------------------------

//STRIP001 BOOL SfxObjectShell::Print
//STRIP001 (
//STRIP001  Printer&        rPrt,
//STRIP001  USHORT          nIdx1,
//STRIP001  USHORT          nIdx2,
//STRIP001  USHORT          nIdx3,
//STRIP001  const String*   pObjectName
//STRIP001 )

/*  [Beschreibung]
*/

//STRIP001 {
//STRIP001  switch(nIdx1)
//STRIP001  {
//STRIP001    case CONTENT_STYLE:
//STRIP001      {
//STRIP001          SfxStyleSheetBasePool *pPool = GetStyleSheetPool();
//STRIP001          SetOrganizerSearchMask(pPool);
//STRIP001          SfxStyleSheetIterator* pIter = pPool->CreateIterator(
//STRIP001              pPool->GetSearchFamily(), pPool->GetSearchMask() );
//STRIP001          USHORT nStyles = pIter->Count();
//STRIP001          SfxStyleSheetBase *pStyle = pIter->First();
//STRIP001          if ( !pStyle )
//STRIP001              return TRUE;
//STRIP001
//STRIP001          if ( !rPrt.StartJob(String(SfxResId(STR_STYLES))) )
//STRIP001          {
//STRIP001              delete pIter;
//STRIP001              return FALSE;
//STRIP001          }
//STRIP001          if ( !rPrt.StartPage() )
//STRIP001          {
//STRIP001              delete pIter;
//STRIP001              return FALSE;
//STRIP001          }
//STRIP001          SfxStatusBarManager* pStbMgr = SFX_APP()->GetStatusBarManager();
//STRIP001          if ( pStbMgr )
//STRIP001              pStbMgr->StartProgressMode(String(SfxResId(STR_PRINT_STYLES)), nStyles);
//STRIP001          rPrt.SetMapMode(MapMode(MAP_10TH_MM));
//STRIP001          Font aFont( DEFINE_CONST_UNICODE( "Arial" ), Size(0, 64));   // 18pt
//STRIP001          aFont.SetWeight(WEIGHT_BOLD);
//STRIP001          rPrt.SetFont(aFont);
//STRIP001          const Size aPageSize(rPrt.GetOutputSize());
//STRIP001          const USHORT nXIndent = 200;
//STRIP001          USHORT nYIndent = 200;
//STRIP001          Point aOutPos(nXIndent, nYIndent);
//STRIP001          String aHeader(SfxResId(STR_PRINT_STYLES_HEADER));
//STRIP001          if ( pObjectName )
//STRIP001              aHeader += *pObjectName;
//STRIP001          else
//STRIP001              aHeader += GetTitle();
//STRIP001             long nTextHeight( rPrt.GetTextHeight() );
//STRIP001          rPrt.DrawText(aOutPos, aHeader);
//STRIP001          aOutPos.Y() += nTextHeight;
//STRIP001          aOutPos.Y() += nTextHeight/2;
//STRIP001          aFont.SetSize(Size(0, 35)); // 10pt
//STRIP001          nStyles = 1;
//STRIP001          while(pStyle)
//STRIP001          {
//STRIP001              if(pStbMgr)
//STRIP001                  pStbMgr->SetProgressState(nStyles++);
//STRIP001              // Ausgabe des Vorlagennamens
//STRIP001              String aStr(pStyle->GetName());
//STRIP001              aFont.SetWeight(WEIGHT_BOLD);
//STRIP001              rPrt.SetFont(aFont);
//STRIP001              nTextHeight = rPrt.GetTextHeight();
//STRIP001              // Seitenwechsel
//STRIP001              if ( aOutPos.Y() + nTextHeight*2 >
//STRIP001                     aPageSize.Height() - (long) nYIndent )
//STRIP001              {
//STRIP001                  rPrt.EndPage();
//STRIP001                  rPrt.StartPage();
//STRIP001                  aOutPos.Y() = nYIndent;
//STRIP001              }
//STRIP001              rPrt.DrawText(aOutPos, aStr);
//STRIP001              aOutPos.Y() += nTextHeight;
//STRIP001
//STRIP001              // Ausgabe der Vorlagenbeschreibung
//STRIP001              aFont.SetWeight(WEIGHT_NORMAL);
//STRIP001              rPrt.SetFont(aFont);
//STRIP001              aStr = pStyle->GetDescription();
//STRIP001              const char cDelim = ' ';
//STRIP001              USHORT nStart = 0, nIdx = 0;
//STRIP001
//STRIP001              nTextHeight = rPrt.GetTextHeight();
//STRIP001              // wie viele Worte passen auf eine Zeile
//STRIP001              while(nIdx < aStr.Len())
//STRIP001              {
//STRIP001                  USHORT  nOld = nIdx;
//STRIP001                     long nTextWidth;
//STRIP001                  nIdx = aStr.Search(cDelim, nStart);
//STRIP001                  nTextWidth = rPrt.GetTextWidth(aStr, nStart, nIdx-nStart);
//STRIP001                  while(nIdx != STRING_NOTFOUND &&
//STRIP001                        aOutPos.X() + nTextWidth <
//STRIP001                           aPageSize.Width() - (long) nXIndent)
//STRIP001                  {
//STRIP001                      nOld = nIdx;
//STRIP001                      nIdx = aStr.Search(cDelim, nIdx+1);
//STRIP001                      nTextWidth = rPrt.GetTextWidth(aStr, nStart, nIdx-nStart);
//STRIP001                  }
//STRIP001                  String aTmp(aStr, nStart, nIdx == STRING_NOTFOUND?
//STRIP001                              STRING_LEN :
//STRIP001                              nOld-nStart);
//STRIP001                  if ( aTmp.Len() )
//STRIP001                  {
//STRIP001                      nStart = nOld+1;    // wegen trailing space
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      USHORT nChar = 1;
//STRIP001                      while(
//STRIP001                          nStart + nChar < aStr.Len() &&
//STRIP001                          aOutPos.X() + rPrt.GetTextWidth(
//STRIP001                              aStr, nStart, nChar) <
//STRIP001                          aPageSize.Width() - nXIndent)
//STRIP001                          ++nChar;
//STRIP001                      aTmp = String(aStr, nStart, nChar-1);
//STRIP001                      nIdx = nStart + nChar;
//STRIP001                      nStart = nIdx;
//STRIP001                  }
//STRIP001                  if ( aOutPos.Y() + nTextHeight*2 >
//STRIP001                      aPageSize.Height() - nYIndent )
//STRIP001                  {
//STRIP001                      rPrt.EndPage();
//STRIP001                      rPrt.StartPage();
//STRIP001                      aOutPos.Y() = nYIndent;
//STRIP001                  }
//STRIP001                  rPrt.DrawText(aOutPos, aTmp);
//STRIP001                  aOutPos.Y() += rPrt.GetTextHeight();
//STRIP001              }
//STRIP001              pStyle = pIter->Next();
//STRIP001          }
//STRIP001          rPrt.EndPage();
//STRIP001          rPrt.EndJob();
//STRIP001          if ( pStbMgr )
//STRIP001              pStbMgr->EndProgressMode();
//STRIP001          delete pIter;
//STRIP001          break;
//STRIP001      }
//STRIP001    default:
//STRIP001        return FALSE;
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

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
//STRIP001  struct Styles_Impl
//STRIP001  {
//STRIP001      SfxStyleSheetBase *pSource;
//STRIP001      SfxStyleSheetBase *pDest;
//STRIP001 //      Styles_Impl () : pSource(0), pDest(0) {}
//STRIP001  };
//STRIP001
//STRIP001  SfxStyleSheetBasePool *pSourcePool = rSource.GetStyleSheetPool();
//STRIP001  DBG_ASSERT(pSourcePool, "Source-DocumentShell ohne StyleSheetPool");
//STRIP001  SfxStyleSheetBasePool *pMyPool = GetStyleSheetPool();
//STRIP001  DBG_ASSERT(pMyPool, "Dest-DocumentShell ohne StyleSheetPool");
//STRIP001  pSourcePool->SetSearchMask(SFX_STYLE_FAMILY_ALL, 0xffff);
//STRIP001  Styles_Impl *pFound = new Styles_Impl[pSourcePool->Count()];
//STRIP001  USHORT nFound = 0;
//STRIP001
//STRIP001  SfxStyleSheetBase *pSource = pSourcePool->First();
//STRIP001  while ( pSource )
//STRIP001  {
//STRIP001      SfxStyleSheetBase *pDest =
//STRIP001          pMyPool->Find( pSource->GetName(), pSource->GetFamily() );
//STRIP001      if ( !pDest )
//STRIP001      {
//STRIP001          pDest = &pMyPool->Make( pSource->GetName(),
//STRIP001                  pSource->GetFamily(), pSource->GetMask());
//STRIP001          // Setzen des Parents, der Folgevorlage
//STRIP001      }
//STRIP001      pFound[nFound].pSource = pSource;
//STRIP001      pFound[nFound].pDest = pDest;
//STRIP001      ++nFound;
//STRIP001      pSource = pSourcePool->Next();
//STRIP001  }
//STRIP001
//STRIP001  for ( USHORT i = 0; i < nFound; ++i )
//STRIP001  {
//STRIP001      pFound[i].pDest->GetItemSet().PutExtended(pFound[i].pSource->GetItemSet(), SFX_ITEM_DONTCARE, SFX_ITEM_DEFAULT);
//STRIP001 //      pFound[i].pDest->SetHelpId(pFound[i].pSource->GetHelpId());
//STRIP001      if(pFound[i].pSource->HasParentSupport())
//STRIP001          pFound[i].pDest->SetParent(pFound[i].pSource->GetParent());
//STRIP001      if(pFound[i].pSource->HasFollowSupport())
//STRIP001          pFound[i].pDest->SetFollow(pFound[i].pSource->GetParent());
//STRIP001  }
//STRIP001  delete pFound;
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
//STRIP001  // Storage-medium?
//STRIP001  SfxMedium *pFile = GetMedium();
//STRIP001  DBG_ASSERT( pFile, "cannot UpdateFromTemplate without medium" );
//STRIP001
//STRIP001     // only for own storage formats
//STRIP001     SvStorageRef xDocStor = pFile ? pFile->GetStorage() : 0;
//STRIP001     if ( !xDocStor.Is() || !pFile->GetFilter() || !pFile->GetFilter()->IsOwnFormat() )
//STRIP001      return;
//STRIP001
//STRIP001  SFX_ITEMSET_ARG( pFile->GetItemSet(), pUpdateDocItem, SfxUInt16Item, SID_UPDATEDOCMODE, sal_False);
//STRIP001  sal_Int16 bCanUpdateFromTemplate = pUpdateDocItem ? pUpdateDocItem->GetValue() : document::UpdateDocMode::NO_UPDATE;
//STRIP001
//STRIP001     // created from template?
//STRIP001  SfxDocumentInfo *pInfo = &GetDocInfo();
//STRIP001  String aTemplName( pInfo->GetTemplateName() );
//STRIP001  String aTemplFileName( pInfo->GetTemplateFileName() );
//STRIP001     String aFoundName;
//STRIP001     SvStorageRef aTemplStor;
//STRIP001     if ( aTemplName.Len() || aTemplFileName.Len() && !IsReadOnly() )
//STRIP001  {
//STRIP001         // try to locate template, first using filename
//STRIP001         // this must be done because writer global document uses this "great" idea to manage the templates of all parts
//STRIP001         // in the master document
//STRIP001         // but it is NOT an error if the template filename points not to a valid file
//STRIP001         SfxDocumentTemplates aTempl;
//STRIP001         aTempl.Construct();
//STRIP001         if ( aTemplFileName.Len() )
//STRIP001         {
//STRIP001             String aURL;
//STRIP001             if( ::utl::LocalFileHelper::ConvertSystemPathToURL( aTemplFileName, GetMedium()->GetName(), aURL ) )
//STRIP001             {
//STRIP001                 aTemplStor = new SvStorage( aURL, STREAM_READ|STREAM_NOCREATE|STREAM_SHARE_DENYWRITE, STORAGE_TRANSACTED );
//STRIP001                 if ( aTemplStor->GetError() )
//STRIP001                     aTemplStor.Clear();
//STRIP001                 else
//STRIP001                     aFoundName = aURL;
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         if( !aFoundName.Len() && aTemplName.Len() )
//STRIP001             // if the template filename did not lead to success, try to get a file name for the logical template name
//STRIP001             aTempl.GetFull( String(), aTemplName, aFoundName );
//STRIP001  }
//STRIP001
//STRIP001     if ( aFoundName.Len() )
//STRIP001  {
//STRIP001         // check existence of template storage
//STRIP001         aTemplFileName = aFoundName;
//STRIP001      BOOL bLoad = FALSE;
//STRIP001         if ( !aTemplStor.Is() )
//STRIP001             aTemplStor = new SvStorage( aTemplFileName,
//STRIP001                             STREAM_READ | STREAM_NOCREATE | STREAM_SHARE_DENYWRITE, STORAGE_TRANSACTED );
//STRIP001
//STRIP001         // should the document checked against changes in the template ?
//STRIP001         if ( !aTemplStor->GetError() && pInfo->IsQueryLoadTemplate() )
//STRIP001      {
//STRIP001             // load document info of template
//STRIP001             BOOL bOK = FALSE;
//STRIP001          DateTime aTemplDate;
//STRIP001             Reference < document::XStandaloneDocumentInfo > xDocInfo (
//STRIP001                     ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(
//STRIP001                         ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.document.StandaloneDocumentInfo") ) ), UNO_QUERY );
//STRIP001             Reference < beans::XFastPropertySet > xSet( xDocInfo, UNO_QUERY );
//STRIP001             if ( xDocInfo.is() && xSet.is() )
//STRIP001             {
//STRIP001                 try
//STRIP001                 {
//STRIP001                     xDocInfo->loadFromURL( aTemplFileName );
//STRIP001                     Any aAny = xSet->getFastPropertyValue( WID_DATE_MODIFIED );
//STRIP001                     ::com::sun::star::util::DateTime aTmp;
//STRIP001                     if ( aAny >>= aTmp )
//STRIP001                     {
//STRIP001                         // get modify date from document info
//STRIP001                         aTemplDate = SfxDocumentInfoObject::impl_DateTime_Struct2Object( aTmp );
//STRIP001                         bOK = TRUE;
//STRIP001                     }
//STRIP001                 }
//STRIP001                 catch ( Exception& )
//STRIP001                 {
//STRIP001                 }
//STRIP001             }
//STRIP001
//STRIP001             // if modify date was read successfully
//STRIP001             if ( bOK )
//STRIP001          {
//STRIP001                 // compare modify data of template with the last check date of the document
//STRIP001                 const DateTime aInfoDate( pInfo->GetTemplateDate(), pInfo->GetTemplateDate() );
//STRIP001              if ( aTemplDate > aInfoDate )
//STRIP001              {
//STRIP001                     // ask user
//STRIP001                  if( bCanUpdateFromTemplate == document::UpdateDocMode::QUIET_UPDATE
//STRIP001                   || bCanUpdateFromTemplate == document::UpdateDocMode::FULL_UPDATE )
//STRIP001                      bLoad = TRUE;
//STRIP001                  else if ( bCanUpdateFromTemplate == document::UpdateDocMode::ACCORDING_TO_CONFIG )
//STRIP001                  {
//STRIP001                      QueryBox aBox( GetDialogParent(), SfxResId(MSG_QUERY_LOAD_TEMPLATE) );
//STRIP001                      if ( RET_YES == aBox.Execute() )
//STRIP001                          bLoad = TRUE;
//STRIP001                  }
//STRIP001
//STRIP001                  if( !bLoad )
//STRIP001                  {
//STRIP001                         // user refuses, so don't ask again for this document
//STRIP001                      pInfo->SetQueryLoadTemplate(FALSE);
//STRIP001
//STRIP001                      if ( xDocStor->IsOLEStorage() )
//STRIP001                          pInfo->Save(xDocStor);
//STRIP001                      else
//STRIP001                          SetModified( TRUE );
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          if ( bLoad )
//STRIP001          {
//STRIP001                 // styles should be updated, create document in organizer mode to read in the styles
//STRIP001                 SfxObjectShellLock xTemplDoc = GetFactory().CreateObject( SFX_CREATE_MODE_ORGANIZER );
//STRIP001              xTemplDoc->DoInitNew(0);
//STRIP001              String aOldBaseURL = INetURLObject::GetBaseURL();
//STRIP001                 INetURLObject::SetBaseURL( INetURLObject( aTemplFileName ).GetMainURL( INetURLObject::NO_DECODE ) );
//STRIP001              if ( xTemplDoc->LoadFrom(aTemplStor) )
//STRIP001              {
//STRIP001                     // transfer styles from xTemplDoc to this document
//STRIP001                  LoadStyles(*xTemplDoc);
//STRIP001
//STRIP001                     // remember date/time of check
//STRIP001                  pInfo->SetTemplateDate(aTemplDate);
//STRIP001                  pInfo->Save(xDocStor);
//STRIP001              }
//STRIP001
//STRIP001              INetURLObject::SetBaseURL( aOldBaseURL );
//STRIP001          }
//STRIP001 /*
//STRIP001          SfxConfigManager *pCfgMgr = SFX_CFGMANAGER();
//STRIP001          BOOL bConfig = pInfo->HasTemplateConfig();
//STRIP001          {
//STRIP001              SfxConfigManager *pTemplCfg = new SfxConfigManager(aTemplStor, pCfgMgr);
//STRIP001              SetConfigManager(pTemplCfg);
//STRIP001              SetTemplateConfig(TRUE);
//STRIP001
//STRIP001              // Falls der gerade zerst"orte CfgMgr des Dokuments der
//STRIP001              // aktive war, pCfgMgr lieber neu holen
//STRIP001              pCfgMgr = SFX_CFGMANAGER();
//STRIP001
//STRIP001              // ggf. den neuen ConfigManager aktivieren
//STRIP001              if ( this == SfxObjectShell::Current() )
//STRIP001                  pTemplCfg->Activate(pCfgMgr);
//STRIP001          }
//STRIP001 */
//STRIP001          // Template und Template-DocInfo werden nicht mehr gebraucht
//STRIP001 //            delete pTemplInfo;
//STRIP001      }
//STRIP001  }
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
//STRIP001  // configuration storage shall be opened in own storage or a new storage, if the
//STRIP001  // document is getting stored into this storage
//STRIP001  if ( !pStor )
//STRIP001      pStor = GetStorage();
//STRIP001
//STRIP001  if ( pStor->IsOLEStorage() )
//STRIP001                 return (SvStorageRef) SotStorageRef();
//STRIP001
//STRIP001  // storage is always opened in transacted mode, so changes must be commited
//STRIP001  SotStorageRef xStorage = pStor->OpenSotStorage( DEFINE_CONST_UNICODE("Configurations"),
//STRIP001              IsReadOnly() ? STREAM_STD_READ : STREAM_STD_READWRITE );
//STRIP001  if ( xStorage.Is() && xStorage->GetError() )
//STRIP001      xStorage.Clear();
//STRIP001         return (SvStorageRef) xStorage;
/*N*/ }

/*N*/ SotStorageStreamRef SfxObjectShell::GetConfigurationStream( const String& rName, BOOL bCreate )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return SotStorageStreamRef();//STRIP001
//STRIP001  SotStorageStreamRef xStream;
//STRIP001  SvStorageRef xStorage = GetConfigurationStorage();
//STRIP001  if ( xStorage.Is() )
//STRIP001  {
//STRIP001      xStream = xStorage->OpenSotStream( rName,
//STRIP001          bCreate ? STREAM_STD_READWRITE|STREAM_TRUNC : STREAM_STD_READ );
//STRIP001      if ( xStream.Is() && xStream->GetError() )
//STRIP001          xStream.Clear();
//STRIP001  }
//STRIP001
//STRIP001  return xStream;
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
//STRIP001  // check for own format
//STRIP001  SfxObjectShellRef xDoc;
//STRIP001  SfxMedium *pMed = new SfxMedium( aTargetURL, STREAM_STD_READ, FALSE, 0 );
//STRIP001  const SfxFilter* pFilter = NULL;
//STRIP001     if( SFX_APP()->GetFilterMatcher().GuessFilter( *pMed, &pFilter ) == ERRCODE_NONE && pFilter && pFilter->IsOwnFormat() )
//STRIP001  {
//STRIP001         delete pMed;
//STRIP001         StreamMode nMode = bForWriting ? STREAM_STD_READWRITE : STREAM_STD_READ;
//STRIP001         SvStorageRef xStor = new SvStorage( aTargetURL, nMode, STORAGE_TRANSACTED );
//STRIP001         xStor->SetVersion( pFilter->GetVersion() );
//STRIP001         if ( SVSTREAM_OK == xStor->GetError() )
//STRIP001         {
//STRIP001          // create document
//STRIP001          const SfxObjectFactory &rFactory =
//STRIP001              ((SfxFactoryFilterContainer*)pFilter->GetFilterContainer())->GetFactory();
//STRIP001
//STRIP001             xDoc = (SfxObjectShell *) rFactory.CreateObject( SFX_CREATE_MODE_ORGANIZER );
//STRIP001             if ( xDoc.Is() )
//STRIP001             {
//STRIP001              // partially load, so don't use DoLoad!
//STRIP001                 xDoc->DoInitNew(0);
//STRIP001                 if( !xDoc->LoadFrom( xStor ) )
//STRIP001                     xDoc.Clear();
//STRIP001                 else
//STRIP001                 {
//STRIP001                  // connect to storage, abandon temp. storage
//STRIP001                     xDoc->DoHandsOff();
//STRIP001                     xDoc->DoSaveCompleted( xStor );
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001  }
//STRIP001  else
//STRIP001      delete pMed;
//STRIP001
//STRIP001     return xDoc;
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
