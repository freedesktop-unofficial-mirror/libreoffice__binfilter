/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sd_drawdoc3.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 09:57:16 $
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

#include <utility>
#include <algorithm>

#ifndef _SFXDOCFILE_HXX //autogen
#include <bf_sfx2/docfile.hxx>
#endif



#include <set>

#include "glob.hrc"
#include "drawdoc.hxx"
#include "sdpage.hxx"
#include "strmname.h"

#ifdef MAC
#include "::ui:inc:strings.hrc"
#else
#ifdef UNX
#include "../ui/inc/grdocsh.hxx"
#include "../ui/inc/sdview.hxx"
#include "../ui/inc/strings.hrc"
#else
#include "..\ui\inc\docshell.hxx"
#include "..\ui\inc\sdview.hxx"
#include "..\ui\inc\strings.hrc"
#endif
#endif
namespace binfilter {

using namespace ::com::sun::star;

#define POOL_BUFFER_SIZE        (USHORT)32768
#define BASIC_BUFFER_SIZE       (USHORT)8192
#define DOCUMENT_BUFFER_SIZE    (USHORT)32768

/*************************************************************************
|*
|* Oeffnet ein Bookmark-Dokument
|*
\************************************************************************/


/*************************************************************************
|*
|* Oeffnet ein Bookmark-Dokument
|*
\************************************************************************/


/*************************************************************************
|*
|* Fuegt ein Bookmark (Seite oder Objekt) ein
|*
\************************************************************************/


/*************************************************************************
|*
|* Fuegt ein Bookmark als Seite ein
|*
\************************************************************************/

/** Concrete incarnations get called by IterateBookmarkPages, for
    every page in the bookmark document/list
 */

/*************************************************************************
|*
|* Fuegt ein Bookmark als Objekt ein
|*
\************************************************************************/


/*************************************************************************
|*
|* Beendet das Einfuegen von Bookmarks
|*
\************************************************************************/

/*N*/ void SdDrawDocument::CloseBookmarkDoc()
/*N*/ {
/*N*/   if (xBookmarkDocShRef.Is())
/*?*/   {
/*?*/       xBookmarkDocShRef->DoClose();
/*?*/   }

/*N*/   xBookmarkDocShRef.Clear();
/*N*/   aBookmarkFile = String();
/*N*/ }

/*************************************************************************
|*
|* Dokument laden (fuer gelinkte Objekte)
|*
\************************************************************************/


/*************************************************************************
|*
|* Dokument schliessen (fuer gelinkte Objekte)
|*
\************************************************************************/

/*N*/ void SdDrawDocument::DisposeLoadedModels()
/*N*/ {
/*N*/   CloseBookmarkDoc();
/*N*/ }

/*************************************************************************
|*
|* Ist das Dokument read-only?
|*
\************************************************************************/



/*************************************************************************
|*
|* In anschliessendem AllocModel() wird eine DocShell erzeugt
|* (xAllocedDocShRef). Eine bereits bestehende DocShell wird ggf. geloescht
|*
\************************************************************************/

/*N*/ void SdDrawDocument::SetAllocDocSh(BOOL bAlloc)
/*N*/ {
/*N*/   bAllocDocSh = bAlloc;

/*N*/   if (xAllocedDocShRef.Is())
/*?*/   {
/*?*/       xAllocedDocShRef->DoClose();
/*?*/   }

/*N*/   xAllocedDocShRef.Clear();
/*N*/ }

/*************************************************************************
|*
|* Liste der CustomShows zurueckgeben (ggf. zuerst erzeugen)
|*
\************************************************************************/

/*N*/ List* SdDrawDocument::GetCustomShowList(BOOL bCreate)
/*N*/ {
/*N*/   if (!pCustomShowList && bCreate)
/*N*/   {
/*N*/       // Liste erzeugen
/*N*/       pCustomShowList = new List();
/*N*/   }
/*N*/
/*N*/   return(pCustomShowList);
/*N*/ }

/*************************************************************************
|*
|* Document-Stream herausgeben (fuer load-on-demand Graphiken)
|*
\************************************************************************/

/*N*/ SvStream* SdDrawDocument::GetDocumentStream(SdrDocumentStreamInfo& rStreamInfo) const
/*N*/ {
/*N*/   SotStorage* pStor = pDocSh ? pDocSh->GetMedium()->GetStorage() : NULL;
/*N*/   SvStream*   pRet = NULL;
/*N*/
/*N*/   if( pStor )
/*N*/   {
/*N*/       if( rStreamInfo.maUserData.Len() &&
/*N*/           ( rStreamInfo.maUserData.GetToken( 0, ':' ) ==
/*N*/             String( RTL_CONSTASCII_USTRINGPARAM( "vnd.sun.star.Package" ) ) ) )
/*N*/       {
/*N*/           const String aPicturePath( rStreamInfo.maUserData.GetToken( 1, ':' ) );
/*N*/
/*N*/           // graphic from picture stream in picture storage in XML package
/*N*/           if( aPicturePath.GetTokenCount( '/' ) == 2 )
/*N*/           {
/*N*/               const String aPictureStreamName( aPicturePath.GetToken( 1, '/' ) );
/*N*/
/*N*/               if( !xPictureStorage.Is() )
/*N*/               {
/*N*/                   const String aPictureStorageName( aPicturePath.GetToken( 0, '/' ) );
/*N*/
/*N*/                   if( pStor->IsContained( aPictureStorageName ) &&
/*N*/                       pStor->IsStorage( aPictureStorageName )  )
/*N*/                   {
/*N*/                       // cast away const
/*N*/                       ((SdDrawDocument*)this)->xPictureStorage = pStor->OpenUCBStorage( aPictureStorageName, STREAM_READ );
/*N*/                   }
/*N*/               }
/*N*/
/*N*/               if( xPictureStorage.Is() &&
/*N*/                   xPictureStorage->IsContained( aPictureStreamName ) &&
/*N*/                   xPictureStorage->IsStream( aPictureStreamName ) )
/*N*/               {
/*N*/                   pRet = xPictureStorage->OpenSotStream( aPictureStreamName, STREAM_READ );
/*N*/
/*N*/                   if( pRet )
/*N*/                   {
/*N*/                       pRet->SetVersion( xPictureStorage->GetVersion() );
/*N*/                       pRet->SetKey( xPictureStorage->GetKey() );
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/
/*N*/           rStreamInfo.mbDeleteAfterUse = ( pRet != NULL );
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           // graphic from plain binary document stream
/*N*/           if( !pDocStor )
/*N*/           {
/*N*/               if( pStor->IsStream( pStarDrawDoc ) )
/*N*/               {
/*N*/                   BOOL bOK = pStor->Rename(pStarDrawDoc, pStarDrawDoc3);
/*N*/                   DBG_ASSERT(bOK, "Umbenennung des Streams gescheitert");
/*N*/               }
/*N*/
/*N*/               SotStorageStreamRef docStream = pStor->OpenSotStream( pStarDrawDoc3, STREAM_READ );
/*N*/               docStream->SetVersion( pStor->GetVersion() );
/*N*/               docStream->SetKey( pStor->GetKey() );
/*N*/
/*N*/               // cast away const (should be regarded logical constness)
/*N*/               ((SdDrawDocument*)this)->xDocStream = docStream;
/*N*/               ((SdDrawDocument*)this)->pDocStor = pStor;
/*N*/           }
/*N*/
/*N*/           pRet = xDocStream;
/*N*/           rStreamInfo.mbDeleteAfterUse = FALSE;
/*N*/       }
/*N*/   }
/*N*/
/*N*/ #if OSL_DEBUG_LEVEL > 1
/*N*/   if( pRet )
/*N*/   {
/*N*/       // try to get some information from stream
/*N*/       const ULONG nStartPos = pRet->Tell();
/*N*/       const ULONG nEndPos = pRet->Seek( STREAM_SEEK_TO_END );
/*N*/       const ULONG nStmLen = nEndPos - nStartPos;
/*N*/       sal_uChar   aTestByte;
/*N*/
/*N*/       // try to read one byte
/*N*/       if( nStmLen )
/*N*/           *pRet >> aTestByte;
/*N*/
/*N*/       pRet->Seek( nStartPos );
/*N*/   }
/*N*/ #endif
/*N*/
/*N*/   return pRet;
/*N*/ }


/*************************************************************************
|*
|* Release doc stream, if no longer valid
|*
\************************************************************************/

/*N*/ void SdDrawDocument::HandsOff()
/*N*/ {
/*N*/   xPictureStorage = SotStorageRef();
/*N*/   pDocStor = NULL;
/*N*/ }


/*************************************************************************
|*
|* Nicht benutzte MasterPages und Layouts entfernen
|*
\************************************************************************/

/*N*/ void SdDrawDocument::RemoveUnnessesaryMasterPages(SdPage* pMasterPage, BOOL bOnlyDuplicatePages, BOOL bUndo)
/*N*/ {
/*N*/   SdView* pView = NULL;
/*N*/
    /***********************************************************
    * Alle MasterPages pruefen
    ***********************************************************/
/*N*/   USHORT nSdMasterPageCount = GetMasterSdPageCount( PK_STANDARD );
/*N*/   for (sal_Int32 nMPage = nSdMasterPageCount - 1; nMPage >= 0; nMPage--)
/*N*/   {
/*N*/       SdPage* pMaster = pMasterPage;
/*N*/       SdPage* pNotesMaster = NULL;
/*N*/
/*N*/       if (!pMaster)
/*N*/       {
/*N*/           pMaster = (SdPage*) GetMasterSdPage( (USHORT) nMPage, PK_STANDARD );
/*N*/           pNotesMaster = (SdPage*) GetMasterSdPage( (USHORT) nMPage, PK_NOTES );
/*N*/       }
/*N*/       else
/*N*/       {
/*?*/           for ( USHORT nMPg = 0; nMPg < GetMasterPageCount(); nMPg++ )
/*?*/           {
/*?*/               if ( pMaster == GetMasterPage( nMPg ) )
/*?*/               {
/*?*/                   pNotesMaster = (SdPage*) GetMasterPage( ++nMPg );
/*?*/                   break;
/*?*/               }
/*?*/           }
/*N*/       }
/*N*/
/*N*/       DBG_ASSERT( pMaster->GetPageKind() == PK_STANDARD, "wrong page kind" );
/*N*/
/*N*/       if ( pMaster->GetPageKind() == PK_STANDARD &&
/*N*/            GetMasterPageUserCount( pMaster ) == 0 &&
/*N*/            pNotesMaster )
/*N*/       {
/*N*/           BOOL bDeleteMaster = TRUE;
/*N*/           String aLayoutName = pMaster->GetLayoutName();
/*N*/
/*N*/           if( bOnlyDuplicatePages )
/*N*/           {
/*N*/               // remove only duplicate pages
/*N*/               bDeleteMaster = FALSE;
/*N*/               for (USHORT i = 0; i < GetMasterSdPageCount( PK_STANDARD ); i++)
/*N*/               {
/*N*/                   SdPage* pMPg = (SdPage*) GetMasterSdPage( i, PK_STANDARD );
/*N*/                   if( pMPg != pMaster &&
/*N*/                       pMPg->GetLayoutName() == aLayoutName )
/*N*/                   {
/*N*/                       // duplicate page found -> remove it
/*N*/                       bDeleteMaster = TRUE;
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/
/*N*/           if( bDeleteMaster )
/*N*/           {
/*N*/               if (pView)
/*N*/               {
/*?*/                   // falls MasterPage sichtbar: erst PageView abmelden, dann loeschen
/*?*/                   SdrPageView* pPgView = pView->GetPageView(pNotesMaster);
/*?*/                   if (pPgView)
/*?*/                       pView->HidePage(pPgView);
/*?*/
/*?*/                   pPgView = pView->GetPageView(pMaster);
/*?*/                   if (pPgView)
/*?*/                       pView->HidePage(pPgView);
/*N*/               }
/*N*/
/*N*/               RemoveMasterPage( pNotesMaster->GetPageNum() );
/*N*/
/*N*/
/*N*/               RemoveMasterPage( pMaster->GetPageNum() );
/*N*/
/*N*/
/*N*/               // alte Layoutvorlagen loeschen, wenn sie nicht mehr benoetigt werden
/*N*/               BOOL bDeleteOldStyleSheets = TRUE;
/*N*/               for ( USHORT nMPg = 0;
/*N*/                         nMPg < GetMasterPageCount() && bDeleteOldStyleSheets;
/*N*/                     nMPg++ )
/*N*/               {
/*N*/                   SdPage* pMPg = (SdPage*) GetMasterPage(nMPg);
/*N*/                   if (pMPg->GetLayoutName() == aLayoutName)
/*N*/                   {
/*N*/                       bDeleteOldStyleSheets = FALSE;
/*N*/                   }
/*N*/               }
/*N*/
/*N*/               if (bDeleteOldStyleSheets)
/*?*/               {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/
/*N*/       if (pMasterPage)
/*N*/           break;                      // Nur diese eine MasterPage!
/*N*/   }
/*N*/ }


/*************************************************************************
|*
|* MasterPage austauschen
|*
|* Entweder erhaelt nSdPageNum eine neue, eigene MasterPage, oder die MasterPage
|* wird komplett ausgetauscht (gilt dann fuer alle Seiten).
|*
|* nSdPageNum   : Nummer der Seite, welche die neue MasterPage erhalten soll
|* rLayoutName  : LayoutName der neuen MasterPage
|* pSourceDoc   : Dokument (Vorlage) aus dem die MasterPage geholt wird
|* bMaster      : Die MasterPage von nSdPageNum soll ausgetauscht werden
|* bCheckMasters: Nicht benutzte MasterPages sollen entfernt werden
|*
|* Ist pSourceDoc == NULL, so wird eine leere MasterPage zugewiesen.
|* Ist rLayoutName leer, so wird die erste MasterPage genommen
\************************************************************************/




}
