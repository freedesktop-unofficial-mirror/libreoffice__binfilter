/*************************************************************************
 *
 *  $RCSfile: sd_drawdoc3.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: kz $ $Date: 2004-10-07 10:25:44 $
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

#include <utility>
#include <algorithm>

// auto strip #ifndef _SV_WRKWIN_HXX
// auto strip #include <vcl/wrkwin.hxx>
// auto strip #endif
#ifndef _SFXDOCFILE_HXX //autogen
#include <bf_sfx2/docfile.hxx>
#endif
// auto strip #ifndef _SVSTOR_HXX //autogen
// auto strip #include <so3/svstor.hxx>
// auto strip #endif
// auto strip #ifndef _SFXAPP_HXX //autogen
// auto strip #include <bf_sfx2/app.hxx>
// auto strip #endif

// auto strip #ifndef _SFXITEMSET_HXX
// auto strip #include <svtools/itemset.hxx>
// auto strip #endif

// auto strip #ifndef _SVDOPATH_HXX
// auto strip #include <bf_svx/svdopath.hxx>
// auto strip #endif
// auto strip #ifndef _SVDITER_HXX
// auto strip #include <bf_svx/svditer.hxx>
// auto strip #endif
// auto strip #include <svtools/style.hxx>
// auto strip #include <bf_svx/linkmgr.hxx>
// auto strip #ifndef _SVDPAGV_HXX //autogen
// auto strip #include <bf_svx/svdpagv.hxx>
// auto strip #endif
// auto strip #ifndef _SVDOGRP_HXX //autogen
// auto strip #include <bf_svx/svdogrp.hxx>
// auto strip #endif
// auto strip #ifndef _SVDUNDO_HXX //autogen
// auto strip #include <bf_svx/svdundo.hxx>
// auto strip #endif
// auto strip #ifndef _SV_MSGBOX_HXX //autogen
// auto strip #include <vcl/msgbox.hxx>
// auto strip #endif
// auto strip #ifndef _SOT_FORMATS_HXX //autogen
// auto strip #include <sot/formats.hxx>
// auto strip #endif

#include <set>

#include "glob.hrc"
#include "drawdoc.hxx"
#include "sdpage.hxx"
// auto strip #include "stlpool.hxx"
// auto strip #include "sdresid.hxx"
// auto strip #include "sdiocmpt.hxx"
#include "strmname.h"
// auto strip #include "anminfo.hxx"

#ifdef MAC
// auto strip #include "::ui:inc:unmovss.hxx"
// auto strip #include "::ui:inc:unchss.hxx"
// auto strip #include "::ui:inc:unprlout.hxx"
// auto strip #include "::ui:inc:docshell.hxx"
// auto strip #include "::ui:inc:grdocsh.hxx"
// auto strip #include "::ui:inc:viewshel.hxx"
// auto strip #include "::ui:inc:sdview.hxx"
// auto strip #include "::ui:inc:cfgids.hxx"
#include "::ui:inc:strings.hrc"
#else
#ifdef UNX
// auto strip #include "../ui/inc/unmovss.hxx"
// auto strip #include "../ui/inc/unchss.hxx"
// auto strip #include "../ui/inc/unprlout.hxx"
// auto strip #include "../ui/inc/docshell.hxx"
#include "../ui/inc/grdocsh.hxx"
#include "../ui/inc/viewshel.hxx"
#include "../ui/inc/sdview.hxx"
// auto strip #include "../ui/inc/cfgids.hxx"
#include "../ui/inc/strings.hrc"
#else
// auto strip #include "..\ui\inc\unmovss.hxx"
// auto strip #include "..\ui\inc\unchss.hxx"
// auto strip #include "..\ui\inc\unprlout.hxx"
#include "..\ui\inc\docshell.hxx"
// auto strip #include "..\ui\inc\grdocsh.hxx"
#include "..\ui\inc\viewshel.hxx"
#include "..\ui\inc\sdview.hxx"
// auto strip #include "..\ui\inc\cfgids.hxx"
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

//STRIP001 SdDrawDocument* SdDrawDocument::OpenBookmarkDoc(SfxMedium& rMedium)
//STRIP001 {
//STRIP001  BOOL bOK = TRUE;
//STRIP001  SdDrawDocument* pBookmarkDoc = NULL;
//STRIP001  String aBookmarkName = rMedium.GetName();
//STRIP001
//STRIP001  if (aBookmarkFile != aBookmarkName && aBookmarkName.Len() && rMedium.IsStorage())
//STRIP001  {
//STRIP001      DBG_ASSERT( rMedium.IsStorage(), "Kein Storage, keine Banane!" );
//STRIP001
//STRIP001      SvStorage* pStorage = rMedium.GetStorage();
//STRIP001
//STRIP001      if( !pStorage->IsStream( pStarDrawDoc ) &&
//STRIP001          !pStorage->IsStream( pStarDrawDoc3 ) &&
//STRIP001          !pStorage->IsStream( pStarDrawXMLContent ) &&
//STRIP001          !pStorage->IsStream( pStarDrawOldXMLContent ))
//STRIP001      {
//STRIP001          // Es ist nicht unser Storage
//STRIP001          DBG_ASSERT(bOK, "Nicht unser Storage");
//STRIP001          bOK = FALSE;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          CloseBookmarkDoc();
//STRIP001
//STRIP001          aBookmarkFile = aBookmarkName;
//STRIP001
//STRIP001          // Es wird eine DocShell erzeugt, da in dem Dokument OLE-Objekte
//STRIP001          // enthalten sein koennten (Persist)
//STRIP001          // Wenn dem nicht so waere, so koennte man auch das Model
//STRIP001          // direkt laden
//STRIP001
//STRIP001          if ( pStorage->GetFormat() == SOT_FORMATSTR_ID_STARDRAW_50 )
//STRIP001              // Draw
//STRIP001              xBookmarkDocShRef = new SdGraphicDocShell(SFX_CREATE_MODE_STANDARD, TRUE);
//STRIP001          else
//STRIP001              // Impress
//STRIP001              xBookmarkDocShRef = new SdDrawDocShell(SFX_CREATE_MODE_STANDARD, TRUE);
//STRIP001
//STRIP001          if ( bOK = xBookmarkDocShRef->DoLoad(pStorage) )
//STRIP001              pBookmarkDoc = xBookmarkDocShRef->GetDoc();
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // Kein Storage
//STRIP001      bOK = FALSE;
//STRIP001      DBG_ASSERT(bOK, "Kein Storage");
//STRIP001  }
//STRIP001
//STRIP001  if (!bOK)
//STRIP001  {
//STRIP001      ErrorBox aErrorBox( NULL, (WinBits)WB_OK, String(SdResId(STR_READ_DATA_ERROR)));
//STRIP001      aErrorBox.Execute();
//STRIP001
//STRIP001      CloseBookmarkDoc();
//STRIP001      pBookmarkDoc = NULL;
//STRIP001  }
//STRIP001  else if (xBookmarkDocShRef.Is())
//STRIP001  {
//STRIP001      pBookmarkDoc = xBookmarkDocShRef->GetDoc();
//STRIP001  }
//STRIP001
//STRIP001  return(pBookmarkDoc);
//STRIP001 }

/*************************************************************************
|*
|* Oeffnet ein Bookmark-Dokument
|*
\************************************************************************/

//STRIP001 SdDrawDocument* SdDrawDocument::OpenBookmarkDoc(const String& rBookmarkFile)
//STRIP001 {
//STRIP001  SdDrawDocument* pBookmarkDoc = NULL;
//STRIP001
//STRIP001  if (aBookmarkFile != rBookmarkFile && rBookmarkFile.Len())
//STRIP001  {
//STRIP001      // Das Medium muss als read/write geoeffnet werden, da ev.
//STRIP001      // OLE-Objekte geclont werden muessen (innerhalb des Mediums)
//STRIP001
//STRIP001      // #70116#: OpenMode is set only to STREAM_READ
//STRIP001      SfxMedium* pMedium = new SfxMedium(rBookmarkFile,
//STRIP001                                         STREAM_READ /*WRITE | STREAM_SHARE_DENYWRITE
//STRIP001                                         | STREAM_NOCREATE */,
//STRIP001                                         FALSE );  // direkt
//STRIP001
//STRIP001      if (pMedium->IsStorage())
//STRIP001      {
//STRIP001          if (!pMedium->GetStorage())
//STRIP001          {
//STRIP001              // READ/WRITE hat nicht geklappt, also wieder READ
//STRIP001              pMedium->Close();
//STRIP001              pMedium->SetOpenMode(STREAM_READ | STREAM_NOCREATE,
//STRIP001                                   FALSE);
//STRIP001
//STRIP001              // Nun wird eine Kopie angelegt. In diese Kopie darf
//STRIP001              // geschrieben werden
//STRIP001              SfxMedium* pTempMedium = new SfxMedium(*pMedium, TRUE);
//STRIP001              pBookmarkDoc = OpenBookmarkDoc(*pTempMedium);
//STRIP001              delete pTempMedium;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              pBookmarkDoc = OpenBookmarkDoc(*pMedium);
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      delete pMedium;
//STRIP001  }
//STRIP001  else if (xBookmarkDocShRef.Is())
//STRIP001  {
//STRIP001      pBookmarkDoc = xBookmarkDocShRef->GetDoc();
//STRIP001  }
//STRIP001
//STRIP001  return(pBookmarkDoc);
//STRIP001 }

/*************************************************************************
|*
|* Fuegt ein Bookmark (Seite oder Objekt) ein
|*
\************************************************************************/

//STRIP001 BOOL SdDrawDocument::InsertBookmark(
//STRIP001  List* pBookmarkList,            // Liste der Namen der einzufuegenden Bookmarks
//STRIP001  List* pExchangeList,            // Liste der zu verwendenen Namen
//STRIP001  BOOL bLink,                     // Bookmarks sollen als Verknuepfung eingefuegt werden
//STRIP001  BOOL bReplace,                  // Aktuellen Seiten (Standard&Notiz) werden ersetzt
//STRIP001  USHORT nInsertPos,              // Einfuegeposition fuer Seiten
//STRIP001  BOOL bNoDialogs,                // Keine Dialoge anzeigen
//STRIP001  SdDrawDocShell* pBookmarkDocSh, // Wenn gesetzt, so ist dieses das Source-Dokument
//STRIP001  BOOL bCopy,                     // Seiten werden kopiert
//STRIP001  Point* pObjPos)                 // Einfuegeposition fuer Objekte
//STRIP001 {
//STRIP001  BOOL bOK = TRUE;
//STRIP001  BOOL bInsertPages = FALSE;
//STRIP001
//STRIP001  if (!pBookmarkList)
//STRIP001  {
//STRIP001      /**********************************************************************
//STRIP001      * Alle Seiten werden eingefuegt
//STRIP001      **********************************************************************/
//STRIP001      bInsertPages = TRUE;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SdDrawDocument* pBookmarkDoc = NULL;
//STRIP001      String aBookmarkName;
//STRIP001
//STRIP001      if (pBookmarkDocSh)
//STRIP001      {
//STRIP001          pBookmarkDoc = pBookmarkDocSh->GetDoc();
//STRIP001          aBookmarkName = pBookmarkDocSh->GetMedium()->GetName();
//STRIP001      }
//STRIP001      else if ( xBookmarkDocShRef.Is() )
//STRIP001      {
//STRIP001          pBookmarkDoc = xBookmarkDocShRef->GetDoc();
//STRIP001          aBookmarkName = aBookmarkFile;
//STRIP001      }
//STRIP001      else
//STRIP001          bOK = FALSE;
//STRIP001
//STRIP001      for (USHORT nPos = 0; bOK && ( nPos < pBookmarkList->Count() ) && !bInsertPages; nPos++)
//STRIP001      {
//STRIP001          /******************************************************************
//STRIP001          * Gibt es in der Bookmark-Liste einen Seitennamen?
//STRIP001          ******************************************************************/
//STRIP001          String  aBMPgName (*(String*) pBookmarkList->GetObject(nPos));
//STRIP001             BOOL    bIsMasterPage;
//STRIP001
//STRIP001          if( pBookmarkDoc->GetPageByName( aBMPgName, bIsMasterPage ) != SDRPAGE_NOTFOUND )
//STRIP001          {
//STRIP001              // Seite gefunden
//STRIP001              bInsertPages = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if ( bOK && bInsertPages )
//STRIP001  {
//STRIP001      // Zuerst werden alle Seiten-Bookmarks eingefuegt
//STRIP001      bOK = InsertBookmarkAsPage(pBookmarkList, pExchangeList, bLink, bReplace,
//STRIP001                                 nInsertPos, bNoDialogs, pBookmarkDocSh, bCopy, TRUE, FALSE);
//STRIP001  }
//STRIP001
//STRIP001  if ( bOK && pBookmarkList )
//STRIP001  {
//STRIP001      // Es werden alle Objekt-Bookmarks eingefuegt
//STRIP001      bOK = InsertBookmarkAsObject(pBookmarkList, pExchangeList, bLink,
//STRIP001                                   pBookmarkDocSh, pObjPos);
//STRIP001  }
//STRIP001
//STRIP001  return bOK;
//STRIP001 }

/*************************************************************************
|*
|* Fuegt ein Bookmark als Seite ein
|*
\************************************************************************/

/** Concrete incarnations get called by IterateBookmarkPages, for
    every page in the bookmark document/list
 */
//STRIP001 class SdDrawDocument::InsertBookmarkAsPage_PageFunctorBase
//STRIP001 {
//STRIP001 public:
//STRIP001     virtual ~InsertBookmarkAsPage_PageFunctorBase() = 0;
//STRIP001     virtual void operator()( SdDrawDocument&, SdPage* ) = 0;
//STRIP001 };
//STRIP001
//STRIP001 SdDrawDocument::InsertBookmarkAsPage_PageFunctorBase::~InsertBookmarkAsPage_PageFunctorBase()
//STRIP001 {
//STRIP001 }
//STRIP001
//STRIP001 void SdDrawDocument::IterateBookmarkPages( SdDrawDocument* pBookmarkDoc, List* pBookmarkList, USHORT nBMSdPageCount,
//STRIP001                                            SdDrawDocument::InsertBookmarkAsPage_PageFunctorBase& rPageIterator )
//STRIP001 {
//STRIP001     //
//STRIP001     // #96029# Refactored copy'n'pasted layout name collection from InsertBookmarkAsPage
//STRIP001     //
//STRIP001     int nPos, nEndPos;
//STRIP001
//STRIP001     if( !pBookmarkList )
//STRIP001     {
//STRIP001         // no list? whole source document
//STRIP001         nEndPos = nBMSdPageCount;
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         // bookmark list? number of entries
//STRIP001         nEndPos = pBookmarkList->Count();
//STRIP001     }
//STRIP001
//STRIP001     SdPage* pBMPage;
//STRIP001
//STRIP001     // iterate over number of pages to insert
//STRIP001     for (nPos = 0; nPos < nEndPos; ++nPos)
//STRIP001     {
//STRIP001         // the master page associated to the nPos'th page to insert
//STRIP001         SdPage* pBMMPage = NULL;
//STRIP001
//STRIP001         if( !pBookmarkList )
//STRIP001         {
//STRIP001             // simply take master page of nPos'th page in source document
//STRIP001          pBMMPage = (SdPage*) pBookmarkDoc->
//STRIP001                 GetSdPage(nPos, PK_STANDARD)->GetMasterPage(0);
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001             // fetch nPos'th entry from bookmark list, and determine master page
//STRIP001          String  aBMPgName (*(String*) pBookmarkList->GetObject(nPos));
//STRIP001             BOOL    bIsMasterPage;
//STRIP001
//STRIP001          USHORT nBMPage = pBookmarkDoc->GetPageByName( aBMPgName, bIsMasterPage );
//STRIP001
//STRIP001          if (nBMPage != SDRPAGE_NOTFOUND)
//STRIP001          {
//STRIP001              pBMPage = (SdPage*) pBookmarkDoc->GetPage(nBMPage);
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              pBMPage = NULL;
//STRIP001          }
//STRIP001
//STRIP001             // enforce that bookmarked page is a standard page and not already a master page
//STRIP001          if (pBMPage && pBMPage->GetPageKind()==PK_STANDARD && !pBMPage->IsMasterPage())
//STRIP001          {
//STRIP001              const USHORT nBMSdPage = (nBMPage - 1) / 2;
//STRIP001
//STRIP001                 pBMMPage = (SdPage*) pBookmarkDoc->
//STRIP001                     GetSdPage(nBMSdPage, PK_STANDARD)->GetMasterPage(0);
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         // successfully determined valid (bookmarked) page?
//STRIP001         if( pBMMPage )
//STRIP001         {
//STRIP001             // yes, call functor
//STRIP001             rPageIterator( *this, pBMMPage );
//STRIP001         }
//STRIP001     }
//STRIP001 }
//STRIP001
//STRIP001 class InsertBookmarkAsPage_FindDuplicateLayouts : public SdDrawDocument::InsertBookmarkAsPage_PageFunctorBase
//STRIP001 {
//STRIP001 public:
//STRIP001     InsertBookmarkAsPage_FindDuplicateLayouts( List* pLayoutsToTransfer, SdDrawDocument* pBookmarkDoc,
//STRIP001                                                List* pBookmarkList, USHORT nBMSdPageCount ) :
//STRIP001         mpLayoutsToTransfer(pLayoutsToTransfer), mpBookmarkDoc(pBookmarkDoc),
//STRIP001         mpBookmarkList(pBookmarkList), mnBMSdPageCount(nBMSdPageCount) {}
//STRIP001     virtual ~InsertBookmarkAsPage_FindDuplicateLayouts() {};
//STRIP001     virtual void operator()( SdDrawDocument&, SdPage* );
//STRIP001 private:
//STRIP001     List*            mpLayoutsToTransfer;
//STRIP001     SdDrawDocument* mpBookmarkDoc;
//STRIP001     List*            mpBookmarkList;
//STRIP001     USHORT           mnBMSdPageCount;
//STRIP001 };
//STRIP001
//STRIP001 void InsertBookmarkAsPage_FindDuplicateLayouts::operator()( SdDrawDocument& rDoc, SdPage* pBMMPage )
//STRIP001 {
//STRIP001     // now check for duplicate masterpage and layout names
//STRIP001     // ===================================================
//STRIP001
//STRIP001     String  sFullLayoutName( pBMMPage->GetLayoutName() );
//STRIP001     String* pLayout = new String(sFullLayoutName);
//STRIP001     pLayout->Erase( pLayout->SearchAscii( SD_LT_SEPARATOR ));
//STRIP001
//STRIP001     String* pTest = (String*) mpLayoutsToTransfer->First();
//STRIP001     BOOL bFound = FALSE;
//STRIP001
//STRIP001     while (pTest && !bFound) // found yet?
//STRIP001     {
//STRIP001         if (*pLayout == *pTest)
//STRIP001             bFound = TRUE;
//STRIP001         else
//STRIP001             pTest = (String*)mpLayoutsToTransfer->Next();
//STRIP001     }
//STRIP001
//STRIP001     const USHORT nMPageCount = rDoc.GetMasterPageCount();
//STRIP001     for (USHORT nMPage = 0; nMPage < nMPageCount && !bFound; nMPage++)
//STRIP001     {
//STRIP001         /**************************************************************
//STRIP001          * Gibt es die Layouts schon im Dokument?
//STRIP001          **************************************************************/
//STRIP001         SdPage* pTest = (SdPage*) rDoc.GetMasterPage(nMPage);
//STRIP001         String aTest(pTest->GetLayoutName());
//STRIP001         aTest.Erase( aTest.SearchAscii( SD_LT_SEPARATOR ));
//STRIP001
//STRIP001         if (aTest == *pLayout)
//STRIP001             bFound = TRUE;
//STRIP001     }
//STRIP001
//STRIP001     if (!bFound)
//STRIP001         mpLayoutsToTransfer->Insert(pLayout, LIST_APPEND);
//STRIP001     else
//STRIP001         delete pLayout;
//STRIP001 }
//STRIP001
//STRIP001
//STRIP001 BOOL SdDrawDocument::InsertBookmarkAsPage(
//STRIP001  List* pBookmarkList,
//STRIP001  List* pExchangeList,            // Liste der zu verwendenen Namen
//STRIP001  BOOL bLink,
//STRIP001  BOOL bReplace,
//STRIP001  USHORT nInsertPos,
//STRIP001  BOOL bNoDialogs,
//STRIP001  SdDrawDocShell* pBookmarkDocSh,
//STRIP001  BOOL bCopy,
//STRIP001  BOOL bMergeMasterPages,
//STRIP001     BOOL bPreservePageNames)
//STRIP001 {
//STRIP001  BOOL bOK = TRUE;
//STRIP001  BOOL bContinue = TRUE;
//STRIP001  BOOL bScaleObjects = FALSE;
//STRIP001  USHORT nReplacedStandardPages = 0;
//STRIP001
//STRIP001  SdDrawDocument* pBookmarkDoc = NULL;
//STRIP001  String aBookmarkName;
//STRIP001
//STRIP001  if (pBookmarkDocSh)
//STRIP001  {
//STRIP001      pBookmarkDoc = pBookmarkDocSh->GetDoc();
//STRIP001
//STRIP001      if (pBookmarkDocSh->GetMedium())
//STRIP001      {
//STRIP001          aBookmarkName = pBookmarkDocSh->GetMedium()->GetName();
//STRIP001      }
//STRIP001  }
//STRIP001  else if ( xBookmarkDocShRef.Is() )
//STRIP001  {
//STRIP001      pBookmarkDoc = xBookmarkDocShRef->GetDoc();
//STRIP001      aBookmarkName = aBookmarkFile;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  const USHORT nSdPageCount = GetSdPageCount(PK_STANDARD);
//STRIP001  const USHORT nBMSdPageCount = pBookmarkDoc->GetSdPageCount(PK_STANDARD);
//STRIP001  const USHORT nMPageCount = GetMasterPageCount();
//STRIP001
//STRIP001  if (nSdPageCount==0 || nBMSdPageCount==0 || nMPageCount==0)
//STRIP001  {
//STRIP001      bContinue = bOK = FALSE;
//STRIP001      return(bContinue);
//STRIP001  }
//STRIP001
//STRIP001  // Seitengroesse und -raender an die Werte der letzten
//STRIP001  // Seiten anpassen?
//STRIP001  SdPage* pBMPage = pBookmarkDoc->GetSdPage(0,PK_STANDARD);
//STRIP001  SdPage* pPage = GetSdPage(nSdPageCount - 1, PK_STANDARD);
//STRIP001
//STRIP001  if( bNoDialogs )
//STRIP001  {
//STRIP001         if( !pBookmarkList )
//STRIP001          bScaleObjects = pPage->IsScaleObjects();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if (pBMPage->GetSize()        != pPage->GetSize()        ||
//STRIP001          pBMPage->GetLftBorder()   != pPage->GetLftBorder()   ||
//STRIP001          pBMPage->GetRgtBorder()   != pPage->GetRgtBorder()   ||
//STRIP001          pBMPage->GetUppBorder()   != pPage->GetUppBorder()   ||
//STRIP001          pBMPage->GetLwrBorder()   != pPage->GetLwrBorder())
//STRIP001      {
//STRIP001          String aStr(SdResId(STR_SCALE_OBJECTS));
//STRIP001          USHORT nBut = QueryBox( NULL, WB_YES_NO_CANCEL, aStr).Execute();
//STRIP001
//STRIP001          bScaleObjects = nBut == RET_YES;
//STRIP001          bContinue     = nBut != RET_CANCEL;
//STRIP001
//STRIP001          if (!bContinue)
//STRIP001          {
//STRIP001              return(bContinue);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001  /**************************************************************************
//STRIP001  |* Die benoetigten Praesentations-StyleSheets ermitteln und vor
//STRIP001  |* den Seiten transferieren, sonst verlieren die Textobjekte
//STRIP001  |* beim Transfer den Bezug zur Vorlage
//STRIP001  \*************************************************************************/
//STRIP001     SfxUndoManager* pUndoMgr = NULL;
//STRIP001     if( pDocSh )
//STRIP001     {
//STRIP001         pUndoMgr = pDocSh->GetUndoManager();
//STRIP001         pUndoMgr->EnterListAction(String(SdResId(STR_UNDO_INSERTPAGES)), String());
//STRIP001     }
//STRIP001
//STRIP001  List* pLayoutsToTransfer = new List;
//STRIP001
//STRIP001     //
//STRIP001     // #96029# Refactored copy'n'pasted layout name collection into IterateBookmarkPages
//STRIP001     //
//STRIP001     InsertBookmarkAsPage_FindDuplicateLayouts aSearchFunctor( pLayoutsToTransfer, pBookmarkDoc,
//STRIP001                                                               pBookmarkList, nBMSdPageCount );
//STRIP001     IterateBookmarkPages( pBookmarkDoc, pBookmarkList, nBMSdPageCount, aSearchFunctor );
//STRIP001
//STRIP001
//STRIP001  /**************************************************************************
//STRIP001  * Die tatsaechlich benoetigten Vorlagen kopieren
//STRIP001  **************************************************************************/
//STRIP001  SdStyleSheetPool* pBookmarkStyleSheetPool =
//STRIP001  (SdStyleSheetPool*) pBookmarkDoc->GetStyleSheetPool();
//STRIP001  String* pLayout = (String*) pLayoutsToTransfer->First();
//STRIP001
//STRIP001  // Wenn Vorlagen kopiert werden muessen, dann muessen auch die
//STRIP001  // MasterPages kopiert werden!
//STRIP001  if( pLayout )
//STRIP001      bMergeMasterPages = TRUE;
//STRIP001
//STRIP001  while (pLayout)
//STRIP001  {
//STRIP001      List* pCreatedStyles = new List;
//STRIP001
//STRIP001      ((SdStyleSheetPool*) GetStyleSheetPool())->
//STRIP001      CopyLayoutSheets(*pLayout, *pBookmarkStyleSheetPool,pCreatedStyles);
//STRIP001
//STRIP001      if (pCreatedStyles->Count() > 0)
//STRIP001      {
//STRIP001             if( pUndoMgr )
//STRIP001             {
//STRIP001                 SdMoveStyleSheetsUndoAction* pMovStyles =
//STRIP001                     new SdMoveStyleSheetsUndoAction(this, pCreatedStyles, TRUE);
//STRIP001                 pUndoMgr->AddUndoAction(pMovStyles);
//STRIP001             }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          delete pCreatedStyles;
//STRIP001      }
//STRIP001
//STRIP001      delete pLayout;
//STRIP001
//STRIP001      pLayout = (String*)pLayoutsToTransfer->Next();
//STRIP001  }
//STRIP001
//STRIP001  delete pLayoutsToTransfer;
//STRIP001
//STRIP001  /**************************************************************************
//STRIP001  * Dokument einfuegen
//STRIP001  **************************************************************************/
//STRIP001  BegUndo(String(SdResId(STR_UNDO_INSERTPAGES)));
//STRIP001
//STRIP001  if (!pBookmarkList)
//STRIP001  {
//STRIP001      if (nInsertPos >= GetPageCount())
//STRIP001      {
//STRIP001          // Seiten werden hinten angefuegt
//STRIP001          nInsertPos = GetPageCount();
//STRIP001      }
//STRIP001
//STRIP001      USHORT nActualInsertPos = nInsertPos;
//STRIP001
//STRIP001      List aNameList;
//STRIP001         std::set<USHORT> aRenameSet;
//STRIP001         USHORT nBMSdPage;
//STRIP001
//STRIP001         for (nBMSdPage=0; nBMSdPage < nBMSdPageCount; nBMSdPage++)
//STRIP001         {
//STRIP001             SdPage* pBMPage = pBookmarkDoc->GetSdPage(nBMSdPage, PK_STANDARD);
//STRIP001             String  pName( pBMPage->GetName() );
//STRIP001             BOOL    bIsMasterPage;
//STRIP001
//STRIP001             if (bLink)
//STRIP001             {
//STRIP001                 // Es werden sich die Namen aller Seiten gemerkt
//STRIP001              aNameList.Insert(new String(pName), nBMSdPage);
//STRIP001             }
//STRIP001
//STRIP001             // #95677# Have to check for duplicate names here, too
//STRIP001             // #67905# don't change name if source and dest model are the same!
//STRIP001             if( pBookmarkDoc != this &&
//STRIP001                 GetPageByName(pName, bIsMasterPage ) != SDRPAGE_NOTFOUND )
//STRIP001             {
//STRIP001                 // #95991# delay renaming *after* pages are copied (might destroy source otherwise)
//STRIP001              aRenameSet.insert(nBMSdPage);
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001      Merge(*pBookmarkDoc,
//STRIP001            1,                 // Nicht die Handzettelseite
//STRIP001            0xFFFF,            // Aber alle anderen
//STRIP001            nActualInsertPos,  // An Position einfuegen
//STRIP001            bMergeMasterPages, // MasterPages mitnehmen
//STRIP001            FALSE,             // Aber nur die benoetigten MasterPages
//STRIP001            TRUE,              // Undo-Aktion erzeugen
//STRIP001            bCopy);            // Seiten kopieren (oder mergen)
//STRIP001
//STRIP001         for (nBMSdPage=0; nBMSdPage < nBMSdPageCount; nBMSdPage++)
//STRIP001         {
//STRIP001             SdPage* pPage        = (SdPage*) GetPage(nActualInsertPos);
//STRIP001             SdPage* pNotesPage  = (SdPage*) GetPage(nActualInsertPos+1);
//STRIP001             String* pName        = (String*) aNameList.GetObject(nBMSdPage);
//STRIP001
//STRIP001             // #95991# delay renaming *after* pages are copied (might destroy source otherwise)
//STRIP001             if( aRenameSet.find(nBMSdPage) != aRenameSet.end() )
//STRIP001             {
//STRIP001                 // Seitenname schon vorhanden -> Defaultname
//STRIP001                 // fuer Standard & Notizseite
//STRIP001                 pPage->SetName(String());
//STRIP001                 pNotesPage->SetName(String());
//STRIP001             }
//STRIP001
//STRIP001             if (bLink)
//STRIP001             {
//STRIP001              // Nun werden die Link-Namen zusammengestellt
//STRIP001              pPage->SetFileName(aBookmarkName);
//STRIP001              pPage->SetBookmarkName(*(pName));
//STRIP001                 delete pName;
//STRIP001              pPage->SetModel(this);
//STRIP001          }
//STRIP001
//STRIP001             nActualInsertPos += 2;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      /**********************************************************************
//STRIP001      * Ausgewaehlte Seiten einfuegen
//STRIP001      **********************************************************************/
//STRIP001      SdPage* pBMPage;
//STRIP001
//STRIP001      if (nInsertPos >= GetPageCount())
//STRIP001      {
//STRIP001          // Seiten werden hinten angefuegt
//STRIP001          bReplace = FALSE;
//STRIP001          nInsertPos = GetPageCount();
//STRIP001      }
//STRIP001
//STRIP001      USHORT nActualInsertPos = nInsertPos;
//STRIP001
//STRIP001      for (USHORT nPos = 0; nPos < pBookmarkList->Count(); nPos++)
//STRIP001      {
//STRIP001          /**************************************************************
//STRIP001          * Namen der Bookmark-Seiten aus Liste holen
//STRIP001          **************************************************************/
//STRIP001          String  aPgName(*(String*) pBookmarkList->GetObject(nPos));
//STRIP001             BOOL    bIsMasterPage;
//STRIP001          USHORT  nBMPage = pBookmarkDoc->GetPageByName( aPgName, bIsMasterPage );
//STRIP001
//STRIP001          if (nBMPage != SDRPAGE_NOTFOUND)
//STRIP001          {
//STRIP001              pBMPage = (SdPage*) pBookmarkDoc->GetPage(nBMPage);
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              pBMPage = NULL;
//STRIP001          }
//STRIP001
//STRIP001          if (pBMPage && pBMPage->GetPageKind()==PK_STANDARD && !pBMPage->IsMasterPage())
//STRIP001          {
//STRIP001              /**************************************************************
//STRIP001              * Es muss eine StandardSeite sein
//STRIP001              **************************************************************/
//STRIP001                 sal_Bool bMustRename = sal_False;
//STRIP001
//STRIP001                 // #95991# delay renaming *after* pages are copied (might destroy source otherwise)
//STRIP001                 // #67905# don't change name if source and dest model are the same!
//STRIP001                 // #96029# avoid renaming if replacing the same page
//STRIP001                 USHORT nPageSameName = GetPageByName(aPgName, bIsMasterPage);
//STRIP001                 if( pBookmarkDoc != this &&
//STRIP001                     nPageSameName != SDRPAGE_NOTFOUND &&
//STRIP001                     ( !bReplace ||
//STRIP001                       nPageSameName != nActualInsertPos ) )
//STRIP001                 {
//STRIP001                     bMustRename = sal_True;
//STRIP001                 }
//STRIP001
//STRIP001              Merge(*pBookmarkDoc,
//STRIP001                    nBMPage,           // Von Seite (Standard)
//STRIP001                    nBMPage+1,         // Bis Seite (Notizen)
//STRIP001                    nActualInsertPos,  // An Position einfuegen
//STRIP001                    bMergeMasterPages, // MasterPages mitnehmen
//STRIP001                    FALSE,             // Aber nur die benoetigten MasterPages
//STRIP001                    TRUE,              // Undo-Aktion erzeugen
//STRIP001                    bCopy);            // Seiten kopieren (oder mergen)
//STRIP001
//STRIP001                 if( bMustRename )
//STRIP001                 {
//STRIP001                  // Seitenname schon vorhanden -> Defaultname
//STRIP001                  // fuer Standard & Notizseite
//STRIP001                  SdPage* pPage = (SdPage*) GetPage(nActualInsertPos);
//STRIP001                  pPage->SetName(String());
//STRIP001                  SdPage* pNotesPage = (SdPage*) GetPage(nActualInsertPos+1);
//STRIP001                  pNotesPage->SetName(String());
//STRIP001                 }
//STRIP001
//STRIP001              if (bLink)
//STRIP001              {
//STRIP001                  SdPage* pPage = (SdPage*) GetPage(nActualInsertPos);
//STRIP001                  pPage->SetFileName(aBookmarkName);
//STRIP001                  pPage->SetBookmarkName(aPgName);
//STRIP001                  pPage->SetModel(this);
//STRIP001              }
//STRIP001
//STRIP001              if (bReplace)
//STRIP001              {
//STRIP001                  // Seite & Notizseite ausfuegen
//STRIP001                  SdPage* pStandardPage = (SdPage*) GetPage(nActualInsertPos+2);
//STRIP001
//STRIP001                  if (pStandardPage)
//STRIP001                  {
//STRIP001                         if( bPreservePageNames )
//STRIP001                         {
//STRIP001                             // #96029# Take old slide names for inserted pages
//STRIP001                             SdPage* pPage = (SdPage*) GetPage(nActualInsertPos);
//STRIP001                             pPage->SetName( pStandardPage->GetName() );
//STRIP001                         }
//STRIP001
//STRIP001                      AddUndo(new SdrUndoDelPage(*pStandardPage));
//STRIP001                      RemovePage(nActualInsertPos+2);
//STRIP001                  }
//STRIP001
//STRIP001                  SdPage* pNotesPage = (SdPage*) GetPage(nActualInsertPos+2);
//STRIP001
//STRIP001                  if (pNotesPage)
//STRIP001                  {
//STRIP001                         if( bPreservePageNames )
//STRIP001                         {
//STRIP001                             // #96029# Take old slide names for inserted pages
//STRIP001                             SdPage* pNotesPage = (SdPage*) GetPage(nActualInsertPos+1);
//STRIP001                             pNotesPage->SetName( pStandardPage->GetName() );
//STRIP001                         }
//STRIP001
//STRIP001                      AddUndo(new SdrUndoDelPage(*pNotesPage));
//STRIP001                      RemovePage(nActualInsertPos+2);
//STRIP001                  }
//STRIP001
//STRIP001                  nReplacedStandardPages++;
//STRIP001              }
//STRIP001
//STRIP001              nActualInsertPos += 2;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001  /**************************************************************************
//STRIP001  |* Dabei sind evtl. zu viele Masterpages ruebergekommen, da die
//STRIP001  |* DrawingEngine gleiche Praesentationslayouts nicht erkennen kann.
//STRIP001  |* Ueberzaehlige MasterPages entfernen.
//STRIP001  \*************************************************************************/
//STRIP001  USHORT nNewMPageCount = GetMasterPageCount();
//STRIP001
//STRIP001  // rueckwaerts, damit Nummern nicht durcheinander geraten
//STRIP001  for (USHORT nPage = nNewMPageCount - 1; nPage >= nMPageCount; nPage--)
//STRIP001  {
//STRIP001      pPage = (SdPage*) GetMasterPage(nPage);
//STRIP001      String aMPLayout(pPage->GetLayoutName());
//STRIP001      PageKind eKind = pPage->GetPageKind();
//STRIP001
//STRIP001      // gibt's den schon?
//STRIP001      for (USHORT nTest = 0; nTest < nMPageCount; nTest++)
//STRIP001      {
//STRIP001          SdPage* pTest = (SdPage*) GetMasterPage(nTest);
//STRIP001          String aTest(pTest->GetLayoutName());
//STRIP001
//STRIP001             // #96029# nInsertPos > 2 is always true when inserting into non-empty models
//STRIP001          if ( nInsertPos > 2 &&
//STRIP001               aTest == aMPLayout &&
//STRIP001               eKind == pTest->GetPageKind() )
//STRIP001          {
//STRIP001                 AddUndo(new SdrUndoDelPage(*pPage));
//STRIP001                 RemoveMasterPage(nPage);
//STRIP001                 nNewMPageCount--;
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001     // #96029# nInsertPos > 2 is always true when inserting into non-empty models
//STRIP001  if (nInsertPos > 2)
//STRIP001  {
//STRIP001      /**********************************************************************
//STRIP001      |* Nur wenn Vorgaenger-Seiten vorhanden sind:
//STRIP001      |* An allen neuen Seiten nochmal das Praesentationslayout setzen;
//STRIP001      |* dadurch werden die Seiten von den Doppelgaenger-Masterpages
//STRIP001      |* geloest und den richtigen Masterpages zugeordnet. Ausserdem
//STRIP001      |* werden Gliederungstextobjekte wieder Listener der richtigen
//STRIP001      |* StyleSheets.
//STRIP001      |* Seitengroessen und -raender und ggfs. Objekte anpassen.
//STRIP001      |*
//STRIP001      |* Undo unnoetig, da die Seiten dabei sowieso rausfliegen.
//STRIP001      \*********************************************************************/
//STRIP001      pPage = (SdPage*) GetPage(nInsertPos - 2);
//STRIP001      SdPage* pNPage = (SdPage*) GetPage(nInsertPos - 1);
//STRIP001
//STRIP001      Size  aSize(pPage->GetSize());
//STRIP001      INT32 nLeft  = pPage->GetLftBorder();
//STRIP001      INT32 nRight = pPage->GetRgtBorder();
//STRIP001      INT32 nUpper = pPage->GetUppBorder();
//STRIP001      INT32 nLower = pPage->GetLwrBorder();
//STRIP001      Orientation eOrient = pPage->GetOrientation();
//STRIP001
//STRIP001      Size  aNSize(pNPage->GetSize());
//STRIP001      INT32 nNLeft  = pNPage->GetLftBorder();
//STRIP001      INT32 nNRight = pNPage->GetRgtBorder();
//STRIP001      INT32 nNUpper = pNPage->GetUppBorder();
//STRIP001      INT32 nNLower = pNPage->GetLwrBorder();
//STRIP001      Orientation eNOrient = pPage->GetOrientation();
//STRIP001
//STRIP001      ULONG nExchangeListPos = 0;
//STRIP001      USHORT nSdPageStart = (nInsertPos - 1) / 2;
//STRIP001      USHORT nSdPageEnd = GetSdPageCount(PK_STANDARD) - nSdPageCount +
//STRIP001                          nSdPageStart - 1;
//STRIP001
//STRIP001      if( bReplace )
//STRIP001      {
//STRIP001          nSdPageEnd = nSdPageStart + nReplacedStandardPages - 1;
//STRIP001      }
//STRIP001
//STRIP001      for (USHORT nSdPage = nSdPageStart; nSdPage <= nSdPageEnd; nSdPage++)
//STRIP001      {
//STRIP001          pPage = GetSdPage(nSdPage, PK_STANDARD);
//STRIP001
//STRIP001          if (pExchangeList)
//STRIP001          {
//STRIP001              // Zuverwendener Name aus Exchange-Liste holen
//STRIP001              if (pExchangeList->GetCurObject())
//STRIP001              {
//STRIP001                  String aExchangeName (*(String*) pExchangeList->GetCurObject());
//STRIP001                  pPage->SetName(aExchangeName);
//STRIP001                  SdrHint aHint(HINT_PAGEORDERCHG);
//STRIP001                  aHint.SetPage(pPage);
//STRIP001                  Broadcast(aHint);
//STRIP001                  SdPage* pNPage = GetSdPage(nSdPage, PK_NOTES);
//STRIP001                  pNPage->SetName(aExchangeName);
//STRIP001                  aHint.SetPage(pNPage);
//STRIP001                  Broadcast(aHint);
//STRIP001              }
//STRIP001
//STRIP001              pExchangeList->Next();
//STRIP001          }
//STRIP001
//STRIP001          String aLayout(pPage->GetLayoutName());
//STRIP001          aLayout.Erase(aLayout.SearchAscii( SD_LT_SEPARATOR ));
//STRIP001
//STRIP001             // update layout and referred master page
//STRIP001          pPage->SetPresentationLayout(aLayout);
//STRIP001
//STRIP001          if (bScaleObjects)
//STRIP001          {
//STRIP001              Rectangle aBorderRect(nLeft, nUpper, nRight, nLower);
//STRIP001              pPage->ScaleObjects(aSize, aBorderRect, TRUE);
//STRIP001          }
//STRIP001          pPage->SetSize(aSize);
//STRIP001          pPage->SetBorder(nLeft, nUpper, nRight, nLower);
//STRIP001          pPage->SetOrientation( eOrient );
//STRIP001
//STRIP001          pPage = GetSdPage(nSdPage, PK_NOTES);
//STRIP001
//STRIP001             // update layout and referred master page
//STRIP001          pPage->SetPresentationLayout(aLayout);
//STRIP001
//STRIP001          if (bScaleObjects)
//STRIP001          {
//STRIP001              Rectangle aBorderRect(nNLeft, nNUpper, nNRight, nNLower);
//STRIP001              pPage->ScaleObjects(aNSize, aBorderRect, TRUE);
//STRIP001          }
//STRIP001
//STRIP001          pPage->SetSize(aNSize);
//STRIP001          pPage->SetBorder(nNLeft, nNUpper, nNRight, nNLower);
//STRIP001          pPage->SetOrientation( eNOrient );
//STRIP001      }
//STRIP001
//STRIP001      for (USHORT nPage = nMPageCount; nPage < nNewMPageCount; nPage++)
//STRIP001      {
//STRIP001          pPage = (SdPage*) GetMasterPage(nPage);
//STRIP001          if (pPage->GetPageKind() == PK_STANDARD)
//STRIP001          {
//STRIP001              if (bScaleObjects)
//STRIP001              {
//STRIP001                  Rectangle aBorderRect(nLeft, nUpper, nRight, nLower);
//STRIP001                  pPage->ScaleObjects(aSize, aBorderRect, TRUE);
//STRIP001              }
//STRIP001              pPage->SetSize(aSize);
//STRIP001              pPage->SetBorder(nLeft, nUpper, nRight, nLower);
//STRIP001              pPage->SetOrientation( eOrient );
//STRIP001          }
//STRIP001          else        // kann nur noch NOTES sein
//STRIP001          {
//STRIP001              if (bScaleObjects)
//STRIP001              {
//STRIP001                  Rectangle aBorderRect(nNLeft, nNUpper, nNRight, nNLower);
//STRIP001                  pPage->ScaleObjects(aNSize, aBorderRect, TRUE);
//STRIP001              }
//STRIP001              pPage->SetSize(aNSize);
//STRIP001              pPage->SetBorder(nNLeft, nNUpper, nNRight, nNLower);
//STRIP001              pPage->SetOrientation( eNOrient );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001     // #91146# Make absolutely sure no double masterpages are there
//STRIP001     RemoveUnnessesaryMasterPages(NULL, TRUE, TRUE);
//STRIP001
//STRIP001     EndUndo();
//STRIP001  pUndoMgr->LeaveListAction();
//STRIP001
//STRIP001  return bContinue;
//STRIP001 }

/*************************************************************************
|*
|* Fuegt ein Bookmark als Objekt ein
|*
\************************************************************************/

//STRIP001 BOOL SdDrawDocument::InsertBookmarkAsObject(
//STRIP001  List* pBookmarkList,
//STRIP001  List* pExchangeList,            // Liste der zu verwendenen Namen
//STRIP001  BOOL bLink,
//STRIP001  SdDrawDocShell* pBookmarkDocSh,
//STRIP001  Point* pObjPos)
//STRIP001 {
//STRIP001  BOOL bOK = TRUE;
//STRIP001  BOOL bOLEObjFound = FALSE;
//STRIP001  SdView* pBMView = NULL;
//STRIP001
//STRIP001  SdDrawDocument* pBookmarkDoc = NULL;
//STRIP001  String aBookmarkName;
//STRIP001
//STRIP001  if (pBookmarkDocSh)
//STRIP001  {
//STRIP001      pBookmarkDoc = pBookmarkDocSh->GetDoc();
//STRIP001
//STRIP001      if (pBookmarkDocSh->GetMedium())
//STRIP001      {
//STRIP001          aBookmarkName = pBookmarkDocSh->GetMedium()->GetName();
//STRIP001      }
//STRIP001  }
//STRIP001  else if ( xBookmarkDocShRef.Is() )
//STRIP001  {
//STRIP001      pBookmarkDoc = xBookmarkDocShRef->GetDoc();
//STRIP001      aBookmarkName = aBookmarkFile;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  if (!pBookmarkList)
//STRIP001  {
//STRIP001      pBMView = new SdView(pBookmarkDoc, (OutputDevice*) NULL);
//STRIP001      pBMView->EndListening(*pBookmarkDoc);
//STRIP001      pBMView->MarkAll();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      SdrPage* pPage;
//STRIP001      SdrPageView* pPV;
//STRIP001
//STRIP001      for (USHORT nPos = 0; nPos < pBookmarkList->Count(); nPos++)
//STRIP001      {
//STRIP001          /******************************************************************
//STRIP001          * Namen der Bookmarks aus Liste holen
//STRIP001          ******************************************************************/
//STRIP001          String aBMName (*(String*) pBookmarkList->GetObject(nPos));
//STRIP001
//STRIP001          SdrObject* pObj = pBookmarkDoc->GetObj(aBMName);
//STRIP001
//STRIP001          if (pObj)
//STRIP001          {
//STRIP001              // Objekt gefunden
//STRIP001
//STRIP001              if (pObj->GetObjInventor() == SdrInventor &&
//STRIP001                  pObj->GetObjIdentifier() == OBJ_OLE2)
//STRIP001              {
//STRIP001                  bOLEObjFound = TRUE;
//STRIP001              }
//STRIP001
//STRIP001              if (!pBMView)
//STRIP001              {
//STRIP001                  // View erstmalig erzeugen
//STRIP001                  pBMView = new SdView(pBookmarkDoc, (OutputDevice*) NULL);
//STRIP001                  pBMView->EndListening(*pBookmarkDoc);
//STRIP001              }
//STRIP001
//STRIP001              pPage = pObj->GetPage();
//STRIP001
//STRIP001              if (pPage->IsMasterPage())
//STRIP001              {
//STRIP001                  pPV = pBMView->ShowMasterPagePgNum(pPage->GetPageNum(), Point(0, 0));
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  pPV = pBMView->GetPageView( pPage );
//STRIP001                  if( !pPV )
//STRIP001                      pPV = pBMView->ShowPage(pPage, Point(0, 0));
//STRIP001              }
//STRIP001
//STRIP001              pBMView->MarkObj(pObj, pPV, FALSE);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if (pBMView)
//STRIP001  {
//STRIP001      /**********************************************************************
//STRIP001      * Selektierte Objekte einfuegen
//STRIP001      **********************************************************************/
//STRIP001      SdView* pView = new SdView(this, (OutputDevice*) NULL);
//STRIP001      pView->EndListening(*this);
//STRIP001
//STRIP001      // Seite bestimmen, auf der die Objekte eingefuegt werden sollen
//STRIP001      SdrPage* pPage = GetSdPage(0, PK_STANDARD);
//STRIP001
//STRIP001      if (pDocSh)
//STRIP001      {
//STRIP001          SdViewShell* pViewSh = pDocSh->GetViewShell();
//STRIP001
//STRIP001          if (pViewSh)
//STRIP001          {
//STRIP001              // Welche Seite wird denn aktuell angezeigt?
//STRIP001              SdrPageView* pPV = pViewSh->GetView()->GetPageViewPvNum(0);
//STRIP001
//STRIP001              if (pPV)
//STRIP001              {
//STRIP001                  pPage = pPV->GetPage();
//STRIP001              }
//STRIP001              else if (pViewSh->GetActualPage())
//STRIP001              {
//STRIP001                  pPage = pViewSh->GetActualPage();
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      Point aObjPos;
//STRIP001
//STRIP001      if (pObjPos)
//STRIP001      {
//STRIP001          aObjPos = *pObjPos;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          aObjPos = Rectangle(Point(), pPage->GetSize()).Center();
//STRIP001      }
//STRIP001
//STRIP001      ULONG nCountBefore = 0;
//STRIP001
//STRIP001      if (pExchangeList)
//STRIP001      {
//STRIP001          // OrdNums sortieren und Anzahl Objekte vor dem Einfuegen bestimmen
//STRIP001          pPage->RecalcObjOrdNums();
//STRIP001          nCountBefore = pPage->GetObjCount();
//STRIP001      }
//STRIP001
//STRIP001      if (bOLEObjFound)
//STRIP001          pBMView->GetDoc()->SetAllocDocSh(TRUE);
//STRIP001
//STRIP001      SdDrawDocument* pTmpDoc = (SdDrawDocument*) pBMView->GetAllMarkedModel();
//STRIP001      bOK = pView->Paste(*pTmpDoc, aObjPos, pPage);
//STRIP001
//STRIP001      if (bOLEObjFound)
//STRIP001          pBMView->GetDoc()->SetAllocDocSh(FALSE);
//STRIP001
//STRIP001      if (!bOLEObjFound)
//STRIP001          delete pTmpDoc;             // Wird ansonsten von der DocShell zerstoert
//STRIP001
//STRIP001      delete pView;
//STRIP001
//STRIP001      List* pList = pBookmarkList;
//STRIP001
//STRIP001      if (pExchangeList)
//STRIP001      {
//STRIP001          // Anzahl Objekte nach dem Einfuegen bestimmen
//STRIP001          ULONG nCount = pPage->GetObjCount();
//STRIP001
//STRIP001          for (ULONG nObj = nCountBefore; nObj < nCount; nObj++)
//STRIP001          {
//STRIP001              // Zuverwendener Name aus Exchange-Liste holen
//STRIP001              if (pExchangeList->GetCurObject())
//STRIP001              {
//STRIP001                  String aExchangeName (*(String*) pExchangeList->GetCurObject());
//STRIP001
//STRIP001                  if (pPage->GetObj(nObj))
//STRIP001                  {
//STRIP001                      pPage->GetObj(nObj)->SetName(aExchangeName);
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              pExchangeList->Next();
//STRIP001          }
//STRIP001
//STRIP001          pList = pExchangeList;
//STRIP001      }
//STRIP001
//STRIP001      if( pList )
//STRIP001      {
//STRIP001          for (USHORT nPos = 0; nPos < pList->Count(); nPos++)
//STRIP001          {
//STRIP001              /******************************************************************
//STRIP001              * Namen der Bookmarks aus Liste holen
//STRIP001              ******************************************************************/
//STRIP001              String aBMName (*(String*) pList->GetObject(nPos));
//STRIP001
//STRIP001              SdrObject* pObj = GetObj(aBMName);
//STRIP001
//STRIP001              if (pObj)
//STRIP001              {
//STRIP001                  // Objekt gefunden
//STRIP001                  if (bLink && pObj->ISA(SdrObjGroup))
//STRIP001                  {
//STRIP001                      ( (SdrObjGroup*) pObj)->SetGroupLink(aBookmarkName, aBMName);
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  delete pBMView;
//STRIP001
//STRIP001  return bOK;
//STRIP001 }

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

//STRIP001 const SdrModel* SdDrawDocument::LoadModel(const String& rFileName)
//STRIP001 {
//STRIP001  return ( OpenBookmarkDoc(rFileName) );
//STRIP001 }

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

//STRIP001 FASTBOOL SdDrawDocument::IsReadOnly() const
//STRIP001 {
//STRIP001  BOOL bReadOnly = FALSE;
//STRIP001
//STRIP001  if (pDocSh)
//STRIP001  {
//STRIP001      // bReadOnly = TRUE wuerde dazu fuehren, dass das Dokument nicht
//STRIP001      // bearbeitet werden kann. Dieser Effekt ist jedoch z.Z. nicht
//STRIP001      // gewuenscht, daher auskommentiert:
//STRIP001 //         bReadOnly = pDocSh->IsReadOnly();
//STRIP001  }
//STRIP001
//STRIP001  return (bReadOnly);
//STRIP001 }


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
/*N*/   SfxUndoManager* pUndoMgr = NULL;
/*N*/
/*N*/   if (pDocSh)
/*N*/   {
/*N*/       pUndoMgr = pDocSh->GetUndoManager();
/*N*/
/*N*/       if (pDocSh->GetViewShell())
/*N*/           pView = pDocSh->GetViewShell()->GetView();
/*N*/   }
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
/*N*/               if( bUndo )
/*?*/               {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/                    BegUndo();
//STRIP001 /*?*/                    AddUndo( new SdrUndoDelPage( *pNotesMaster ) );
/*N*/               }
/*N*/
/*N*/               RemoveMasterPage( pNotesMaster->GetPageNum() );
/*N*/
/*N*/               if( bUndo )
/*?*/                   {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 AddUndo(new SdrUndoDelPage(*pMaster));
/*N*/
/*N*/               RemoveMasterPage( pMaster->GetPageNum() );
/*N*/
/*N*/               if( bUndo )
/*?*/                   {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 EndUndo();  // schon hier, damit sich Joes Actions ZWISCHEN unsere eigenen schieben
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
//STRIP001 /*?*/                    List* pRemove = ((SdStyleSheetPool*) pStyleSheetPool)->CreateLayoutSheetList( aLayoutName );
//STRIP001 /*?*/
//STRIP001 /*?*/                    if( bUndo )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        // die Liste gehoert der UndoAction
//STRIP001 /*?*/                        SdMoveStyleSheetsUndoAction* pMovStyles = new SdMoveStyleSheetsUndoAction( this, pRemove, FALSE );
//STRIP001 /*?*/
//STRIP001 /*?*/                        if (pUndoMgr)
//STRIP001 /*?*/                            {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 pUndoMgr->AddUndoAction(pMovStyles);
//STRIP001 /*?*/                    }
//STRIP001 /*?*/
//STRIP001 /*?*/                    for ( SfxStyleSheet* pSheet = (SfxStyleSheet*)pRemove->First();
//STRIP001 /*?*/                          pSheet;
//STRIP001 /*?*/                          pSheet = (SfxStyleSheet*)pRemove->Next() )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        ((SdStyleSheetPool*) pStyleSheetPool)->Remove(pSheet);
//STRIP001 /*?*/                    }
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

//STRIP001 void SdDrawDocument::SetMasterPage(USHORT nSdPageNum,
//STRIP001                                 const String& rLayoutName,
//STRIP001                                 SdDrawDocument* pSourceDoc,
//STRIP001                                 BOOL bMaster,
//STRIP001                                 BOOL bCheckMasters)
//STRIP001 {
//STRIP001  if( pDocSh )
//STRIP001      pDocSh->SetWaitCursor( TRUE );
//STRIP001
//STRIP001  SfxUndoManager* pUndoMgr = pDocSh->GetUndoManager();
//STRIP001  pUndoMgr->EnterListAction(String(SdResId(STR_UNDO_SET_PRESLAYOUT)), String());
//STRIP001
//STRIP001  SdPage* pSelectedPage   = GetSdPage(nSdPageNum, PK_STANDARD);
//STRIP001  SdPage* pNotes          = (SdPage*) GetPage(pSelectedPage->GetPageNum()+1);
//STRIP001  SdPage* pOldMaster      = (SdPage*) pSelectedPage->GetMasterPage(0);
//STRIP001  SdPage* pOldNotesMaster = (SdPage*) pNotes->GetMasterPage(0);
//STRIP001  SdPage* pMaster         = NULL;
//STRIP001  SdPage* pNotesMaster    = NULL;
//STRIP001  SdPage* pPage           = NULL;
//STRIP001  String aOldPageLayoutName(pSelectedPage->GetLayoutName());
//STRIP001  String aOldLayoutName(aOldPageLayoutName);
//STRIP001  aOldLayoutName.Erase(aOldLayoutName.SearchAscii( SD_LT_SEPARATOR ));
//STRIP001
//STRIP001  String aNewLayoutName( rLayoutName );
//STRIP001
//STRIP001  if (pSourceDoc)
//STRIP001  {
//STRIP001      List* pReplList = NULL;
//STRIP001      BOOL bLayoutReloaded = FALSE;   // Wurde ex. Layout wieder geladen?
//STRIP001
//STRIP001      /*********************************************************************
//STRIP001      |* LayoutName, Page and Notespage
//STRIP001      \*********************************************************************/
//STRIP001      if (rLayoutName.Len() == 0)
//STRIP001      {
//STRIP001          // No LayoutName: take first MasterPage
//STRIP001          pMaster = (SdPage*) pSourceDoc->GetMasterSdPage(0, PK_STANDARD);
//STRIP001          pNotesMaster = (SdPage*) pSourceDoc->GetMasterSdPage(0, PK_NOTES);
//STRIP001          aNewLayoutName = pMaster->GetName();
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          String aSearchFor(rLayoutName);
//STRIP001          aSearchFor.AppendAscii( RTL_CONSTASCII_STRINGPARAM( SD_LT_SEPARATOR ));
//STRIP001          aSearchFor.Append( String(SdResId(STR_LAYOUT_OUTLINE))) ;
//STRIP001
//STRIP001          for (USHORT nMP = 0; nMP < pSourceDoc->GetMasterPageCount(); nMP++)
//STRIP001          {
//STRIP001              SdPage* pMP = (SdPage*) pSourceDoc->GetMasterPage(nMP);
//STRIP001
//STRIP001              if (pMP->GetLayoutName() == aSearchFor)
//STRIP001              {
//STRIP001                  if (pMP->GetPageKind() == PK_STANDARD)
//STRIP001                      pMaster = pMP;
//STRIP001                  if (pMP->GetPageKind() == PK_NOTES)
//STRIP001                      pNotesMaster = pMP;
//STRIP001              }
//STRIP001              if (pMaster && pNotesMaster)
//STRIP001                  break;
//STRIP001          }
//STRIP001          DBG_ASSERT(pMaster, "MasterPage (Standard page) not found");
//STRIP001          DBG_ASSERT(pNotesMaster, "MasterPage (Notes page) not found");
//STRIP001      }
//STRIP001
//STRIP001      if (pSourceDoc != this)
//STRIP001      {
//STRIP001          const USHORT nMasterPageCount = GetMasterPageCount();
//STRIP001          for ( USHORT nMPage = 0; nMPage < nMasterPageCount; nMPage++ )
//STRIP001          {
//STRIP001              SdPage* pMaster = (SdPage*)GetMasterPage(nMPage);
//STRIP001              if( pMaster->GetName() == aNewLayoutName )
//STRIP001              {
//STRIP001                  bLayoutReloaded = TRUE;
//STRIP001                  break;
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          /*****************************************************************
//STRIP001          |* Praesentationsvorlagen korrigieren bzw. neu anlegen
//STRIP001          \****************************************************************/
//STRIP001          // nur die Praesentationsvorlagen beachten
//STRIP001          String aName;
//STRIP001          SdStyleSheetPool* pSourceStyleSheetPool = (SdStyleSheetPool*) pSourceDoc->GetStyleSheetPool();
//STRIP001          pSourceStyleSheetPool->SetSearchMask(SD_LT_FAMILY);
//STRIP001          ((SdStyleSheetPool*) pStyleSheetPool)->SetSearchMask(SD_LT_FAMILY);
//STRIP001
//STRIP001          pReplList = new List;           // Liste fuer ersetzte StyleSheets
//STRIP001          List* pCreatedStyles = new List;// Liste fuer erzeugte StyleSheets
//STRIP001
//STRIP001          SfxStyleSheetBase* pHisSheet = pSourceStyleSheetPool->First();
//STRIP001
//STRIP001          while (pHisSheet)
//STRIP001          {
//STRIP001              aName = pHisSheet->GetName();
//STRIP001
//STRIP001              if( aName.Search( aNewLayoutName ) == 0 )
//STRIP001              {
//STRIP001                  SfxStyleSheet* pMySheet = (SfxStyleSheet*) pStyleSheetPool->Find(
//STRIP001                                              aName, SD_LT_FAMILY);
//STRIP001
//STRIP001                  if (pMySheet)
//STRIP001                  {
//STRIP001                      // Es ist eine gleichnamige Vorlage vorhanden ist: Inhalte ersetzen
//STRIP001                      BOOL bTest = pMySheet->SetName(pHisSheet->GetName());
//STRIP001                      DBG_ASSERT(bTest, "StyleSheet-Umbenennung fehlgeschlagen");
//STRIP001                      pMySheet->GetItemSet().ClearItem(0);  // alle loeschen
//STRIP001
//STRIP001                      StyleSheetUndoAction* pUndoChStyle = new StyleSheetUndoAction(this,
//STRIP001                                                               pMySheet, &pHisSheet->GetItemSet());
//STRIP001                      pUndoMgr->AddUndoAction(pUndoChStyle);
//STRIP001                      pMySheet->GetItemSet().Put(pHisSheet->GetItemSet());
//STRIP001                      pMySheet->Broadcast(SfxSimpleHint(SFX_HINT_DATACHANGED));
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                     // So eine Vorlage erzeugen
//STRIP001                      pMySheet = (SfxStyleSheet*)&pStyleSheetPool->Make(
//STRIP001                                          aName, SD_LT_FAMILY, pHisSheet->GetMask());
//STRIP001                      pMySheet->GetItemSet().ClearItem(0);  // alle loeschen
//STRIP001                      pMySheet->GetItemSet().Put(pHisSheet->GetItemSet());
//STRIP001                      pCreatedStyles->Insert(pMySheet, LIST_APPEND);
//STRIP001                  }
//STRIP001
//STRIP001                  StyleReplaceData* pReplData = new StyleReplaceData;
//STRIP001                  pReplData->nNewFamily = pMySheet->GetFamily();
//STRIP001                  pReplData->nFamily    = pMySheet->GetFamily();
//STRIP001                  pReplData->aNewName   = pMySheet->GetName();
//STRIP001
//STRIP001                  String aTemp(pMySheet->GetName());
//STRIP001                  USHORT nPos = aTemp.SearchAscii( SD_LT_SEPARATOR );
//STRIP001                  aTemp.Erase(0, nPos);
//STRIP001                  aTemp.Insert(aOldLayoutName, 0);
//STRIP001                  pReplData->aName = aTemp;
//STRIP001                  pReplList->Insert(pReplData, LIST_APPEND);
//STRIP001              }
//STRIP001
//STRIP001              pHisSheet = (SfxStyleSheet*) pSourceStyleSheetPool->Next();
//STRIP001          }
//STRIP001
//STRIP001          // wenn neue Vorlagen erzeugt wurden:
//STRIP001          // eventuell bestehende Parent-Verkettung der Itemsets in den
//STRIP001          // Vorlagen wieder aufbauen
//STRIP001          if (pCreatedStyles->Count())
//STRIP001          {
//STRIP001              StyleReplaceData* pRData = (StyleReplaceData*)pReplList->First();
//STRIP001
//STRIP001              while (pRData)
//STRIP001              {
//STRIP001                  SfxStyleSheetBase* pSOld = pStyleSheetPool->Find(pRData->aName);
//STRIP001                  SfxStyleSheetBase* pSNew = pStyleSheetPool->Find(pRData->aNewName);
//STRIP001
//STRIP001                  if (pSOld && pSNew)
//STRIP001                  {
//STRIP001                      const String& rParentOfOld = pSOld->GetParent();
//STRIP001                      const String& rParentOfNew = pSNew->GetParent();
//STRIP001
//STRIP001                      if (rParentOfOld.Len() > 0 && rParentOfNew.Len() == 0)
//STRIP001                      {
//STRIP001
//STRIP001                          for (ULONG i = 0; i < pReplList->Count(); i++)
//STRIP001                          {
//STRIP001                              StyleReplaceData* pRD = (StyleReplaceData*)pReplList->
//STRIP001                                                                      GetObject(i);
//STRIP001                              if ((pRD->aName == rParentOfOld) && (pRD->aName != pRD->aNewName))
//STRIP001                              {
//STRIP001                                  String aParentOfNew(pRD->aNewName);
//STRIP001                                  pSNew->SetParent(aParentOfNew);
//STRIP001                                  break;
//STRIP001                              }
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001                  pRData = (StyleReplaceData*) pReplList->Next();
//STRIP001              }
//STRIP001
//STRIP001              // ab jetzt beim Suchen alle beachten
//STRIP001              pSourceStyleSheetPool->SetSearchMask(SFX_STYLE_FAMILY_ALL);
//STRIP001              pStyleSheetPool->SetSearchMask(SFX_STYLE_FAMILY_ALL);
//STRIP001          }
//STRIP001
//STRIP001          if (pCreatedStyles->Count() > 0)
//STRIP001          {
//STRIP001              // UndoAction fuer das Erzeugen und Einfuegen vorn StyleSheets
//STRIP001              // auf den UndoManager legen
//STRIP001              SdMoveStyleSheetsUndoAction* pMovStyles = new SdMoveStyleSheetsUndoAction(
//STRIP001                                                            this, pCreatedStyles, TRUE);
//STRIP001              pUndoMgr->AddUndoAction(pMovStyles);
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              // Liste zerstoeren
//STRIP001              delete pCreatedStyles;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // Layoutnamen auf Basis des Seitenlayoutnamens der Masterpage bilden
//STRIP001      String aPageLayoutName(pMaster->GetLayoutName());
//STRIP001      String aLayoutName = aPageLayoutName;
//STRIP001      aLayoutName.Erase( aLayoutName.SearchAscii( SD_LT_SEPARATOR ));
//STRIP001
//STRIP001      if (pSourceDoc != this)
//STRIP001      {
//STRIP001          // Aus dem Source-Dokument austragen
//STRIP001          SdrPage* pTest = NULL;
//STRIP001          pTest = pSourceDoc->RemoveMasterPage(pNotesMaster->GetPageNum());
//STRIP001          pTest = pSourceDoc->RemoveMasterPage(pMaster->GetPageNum());
//STRIP001      }
//STRIP001
//STRIP001      /*********************************************************************
//STRIP001      |* Neue MasterPages ins Dokument eintragen und den Standard- und
//STRIP001      |* Notizseiten das Praesentationslayout ueberbraten
//STRIP001      \********************************************************************/
//STRIP001      if (pSourceDoc != this)
//STRIP001      {
//STRIP001          // Die Masterpages einfuegen:
//STRIP001          // Masterpages von neuen Layouts hinten anhaengen; wird ein Layout
//STRIP001          // dagegen ersetzt, so muss vor der Position der alten Masterpage
//STRIP001          // eingefuegt werden, damit ab jetzt beim Suchen (z. B. SdPage::
//STRIP001          // SetPresentationLayout) die neue Masterpage zuerst gefunden wird
//STRIP001          USHORT nInsertPos = pOldMaster->GetPageNum();
//STRIP001          BegUndo();
//STRIP001
//STRIP001          if (!bLayoutReloaded)
//STRIP001              nInsertPos = 0xFFFF;
//STRIP001          InsertMasterPage(pMaster, nInsertPos);
//STRIP001          AddUndo(new SdrUndoNewPage(*pMaster));
//STRIP001
//STRIP001          nInsertPos++;
//STRIP001          if (!bLayoutReloaded)
//STRIP001              nInsertPos = 0xFFFF;
//STRIP001          InsertMasterPage(pNotesMaster, nInsertPos);
//STRIP001          AddUndo(new SdrUndoNewPage(*pNotesMaster));
//STRIP001
//STRIP001          EndUndo(); // schon hier, damit sich Joes Actions ZWISCHEN unsere eigenen schieben
//STRIP001      }
//STRIP001
//STRIP001      // Liste mit Seiten fuellen
//STRIP001      List* pPageList = new List;
//STRIP001
//STRIP001 //      #98456, this has to be removed according to CL (KA 07/08/2002)
//STRIP001 //       #109884# but we need them again to restore the styles of the presentation objects while undo
//STRIP001      pPageList->Insert(pMaster, LIST_APPEND);
//STRIP001      pPageList->Insert(pNotesMaster, LIST_APPEND);
//STRIP001
//STRIP001      if (bMaster || bLayoutReloaded)
//STRIP001      {
//STRIP001          for (USHORT nPage = 1; nPage < GetPageCount(); nPage++)
//STRIP001          {
//STRIP001              pPage = (SdPage*) GetPage(nPage);
//STRIP001              String aTest = pPage->GetLayoutName();
//STRIP001              if (aTest == aOldPageLayoutName)
//STRIP001              {
//STRIP001                  pPageList->Insert(pPage, LIST_APPEND);
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pPageList->Insert(pSelectedPage, LIST_APPEND);
//STRIP001          pPageList->Insert(pNotes, LIST_APPEND);
//STRIP001      }
//STRIP001
//STRIP001      pPage = (SdPage*)pPageList->First();
//STRIP001      while (pPage)
//STRIP001      {
//STRIP001          AutoLayout eAutoLayout = pPage->GetAutoLayout();
//STRIP001
//STRIP001          SdPresentationLayoutUndoAction * pPLUndoAction =
//STRIP001              new SdPresentationLayoutUndoAction
//STRIP001                  (this, aOldLayoutName, aLayoutName,
//STRIP001                   eAutoLayout, eAutoLayout, FALSE, pPage);
//STRIP001          pUndoMgr->AddUndoAction(pPLUndoAction);
//STRIP001          pPage->SetPresentationLayout(aLayoutName);
//STRIP001          pPage->SetAutoLayout(eAutoLayout);
//STRIP001
//STRIP001          pPage = (SdPage*)pPageList->Next();
//STRIP001      }
//STRIP001      delete pPageList;
//STRIP001
//STRIP001      /*********************************************************************
//STRIP001      |* Neue Masterpages angleichen
//STRIP001      \********************************************************************/
//STRIP001      if (pSourceDoc != this)
//STRIP001      {
//STRIP001          // die Masterpages angleichen
//STRIP001          Size aSize(pOldMaster->GetSize());
//STRIP001          Rectangle aBorderRect(pOldMaster->GetLftBorder(),
//STRIP001                                pOldMaster->GetUppBorder(),
//STRIP001                                pOldMaster->GetRgtBorder(),
//STRIP001                                pOldMaster->GetLwrBorder());
//STRIP001          pMaster->ScaleObjects(aSize, aBorderRect, TRUE);
//STRIP001          pMaster->SetSize(aSize);
//STRIP001          pMaster->SetBorder(pOldMaster->GetLftBorder(),
//STRIP001                             pOldMaster->GetUppBorder(),
//STRIP001                             pOldMaster->GetRgtBorder(),
//STRIP001                             pOldMaster->GetLwrBorder());
//STRIP001          pMaster->SetOrientation( pOldMaster->GetOrientation() );
//STRIP001          pMaster->SetAutoLayout(pMaster->GetAutoLayout());
//STRIP001
//STRIP001          aSize = pOldNotesMaster->GetSize();
//STRIP001          Rectangle aNotesBorderRect(pOldNotesMaster->GetLftBorder(),
//STRIP001                                     pOldNotesMaster->GetUppBorder(),
//STRIP001                                     pOldNotesMaster->GetRgtBorder(),
//STRIP001                                     pOldNotesMaster->GetLwrBorder());
//STRIP001          pNotesMaster->ScaleObjects(aSize, aNotesBorderRect, TRUE);
//STRIP001          pNotesMaster->SetSize(aSize);
//STRIP001          pNotesMaster->SetBorder(pOldNotesMaster->GetLftBorder(),
//STRIP001                                  pOldNotesMaster->GetUppBorder(),
//STRIP001                                  pOldNotesMaster->GetRgtBorder(),
//STRIP001                                  pOldNotesMaster->GetLwrBorder());
//STRIP001          pNotesMaster->SetOrientation( pOldNotesMaster->GetOrientation() );
//STRIP001          pNotesMaster->SetAutoLayout(pNotesMaster->GetAutoLayout());
//STRIP001
//STRIP001          // Liste der ersetzten Vorlagen mit Inhalt loeschen
//STRIP001          StyleReplaceData* pReplData = (StyleReplaceData*)pReplList->First();
//STRIP001          while (pReplData)
//STRIP001          {
//STRIP001              delete pReplData;
//STRIP001              pReplData = (StyleReplaceData*)pReplList->Next();
//STRIP001          }
//STRIP001          delete pReplList;
//STRIP001     }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      /*********************************************************************
//STRIP001      |* Einen neuen Layoutnamen ausdenken
//STRIP001      \********************************************************************/
//STRIP001      String aName        = String(SdResId(STR_LAYOUT_DEFAULT_NAME));
//STRIP001      String aTest;
//STRIP001      BOOL   bNotANewName = TRUE;
//STRIP001      USHORT nCount       = 0;
//STRIP001      USHORT nMPgCount    = GetMasterPageCount();
//STRIP001
//STRIP001      for (nCount = 0; bNotANewName; nCount++)
//STRIP001      {
//STRIP001          // Testnamen bilden
//STRIP001          aTest = aName;              // Standard, Standard1, Standard2, ...
//STRIP001          if (nCount > 0)
//STRIP001              aTest += String::CreateFromInt32( nCount );
//STRIP001
//STRIP001          // gibt's schon eine, die so heisst?
//STRIP001          bNotANewName = FALSE;
//STRIP001          for (USHORT nMPg = 1; nMPg < nMPgCount; nMPg++)
//STRIP001          {
//STRIP001              const SdrPage* pTest = GetMasterPage(nMPg);
//STRIP001              String aPageLayoutName(pTest->GetLayoutName());
//STRIP001              aPageLayoutName.Erase( aPageLayoutName.SearchAscii( SD_LT_SEPARATOR ));
//STRIP001
//STRIP001              if (aPageLayoutName == aTest)
//STRIP001                  bNotANewName = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001      aName = aTest;
//STRIP001      String aPageLayoutName(aName);
//STRIP001      aPageLayoutName.AppendAscii( RTL_CONSTASCII_STRINGPARAM( SD_LT_SEPARATOR ));
//STRIP001      aPageLayoutName += String(SdResId(STR_LAYOUT_OUTLINE));
//STRIP001
//STRIP001      /*********************************************************************
//STRIP001      |* Neue StyleSheets erzeugen
//STRIP001      \********************************************************************/
//STRIP001      ((SdStyleSheetPool*) pStyleSheetPool)->CreateLayoutStyleSheets(aName);
//STRIP001      List* pCreatedStyles = ((SdStyleSheetPool*) pStyleSheetPool)->CreateLayoutSheetList(aName);
//STRIP001      SdMoveStyleSheetsUndoAction* pMovStyles =
//STRIP001          new SdMoveStyleSheetsUndoAction(this, pCreatedStyles, TRUE);
//STRIP001      pUndoMgr->AddUndoAction(pMovStyles);
//STRIP001
//STRIP001      /*********************************************************************
//STRIP001      |* Neue MasterPages erzeugen und ins Dokument eintragen
//STRIP001      \********************************************************************/
//STRIP001      BegUndo();
//STRIP001      pMaster = (SdPage*) AllocPage(TRUE);
//STRIP001      pMaster->SetSize(pSelectedPage->GetSize());
//STRIP001      pMaster->SetBorder(pSelectedPage->GetLftBorder(),
//STRIP001                         pSelectedPage->GetUppBorder(),
//STRIP001                         pSelectedPage->GetRgtBorder(),
//STRIP001                         pSelectedPage->GetLwrBorder() );
//STRIP001      pMaster->SetName(aName);
//STRIP001      pMaster->SetLayoutName(aPageLayoutName);
//STRIP001      InsertMasterPage(pMaster);
//STRIP001      AddUndo(new SdrUndoNewPage(*pMaster));
//STRIP001      pMaster->SetAutoLayout(AUTOLAYOUT_NONE, TRUE);
//STRIP001
//STRIP001      pNotesMaster = (SdPage*) AllocPage(TRUE);
//STRIP001      pNotesMaster->SetPageKind(PK_NOTES);
//STRIP001      pNotesMaster->SetSize(pNotes->GetSize());
//STRIP001      pNotesMaster->SetBorder(pNotes->GetLftBorder(),
//STRIP001                              pNotes->GetUppBorder(),
//STRIP001                              pNotes->GetRgtBorder(),
//STRIP001                              pNotes->GetLwrBorder() );
//STRIP001      pNotesMaster->SetName(aName);
//STRIP001      pNotesMaster->SetLayoutName(aPageLayoutName);
//STRIP001      InsertMasterPage(pNotesMaster);
//STRIP001      AddUndo(new SdrUndoNewPage(*pNotesMaster));
//STRIP001      pNotesMaster->SetAutoLayout(AUTOLAYOUT_NOTES, TRUE);
//STRIP001      EndUndo();
//STRIP001
//STRIP001      /*********************************************************************
//STRIP001      |* Liste der betroffenen Standard- und Notizseiten erstellen
//STRIP001      \********************************************************************/
//STRIP001      List* pPageList = new List;
//STRIP001      if (bMaster)
//STRIP001      {
//STRIP001          for (USHORT nPage = 1; nPage < GetPageCount(); nPage++)
//STRIP001          {
//STRIP001              pPage = (SdPage*) GetPage(nPage);
//STRIP001              String aTest = pPage->GetLayoutName();
//STRIP001              if (aTest == aOldPageLayoutName)
//STRIP001              {
//STRIP001                  pPageList->Insert(pPage, LIST_APPEND);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pPageList->Insert(pSelectedPage, LIST_APPEND);
//STRIP001          pPageList->Insert(pNotes, LIST_APPEND);
//STRIP001      }
//STRIP001
//STRIP001      /*********************************************************************
//STRIP001      |* An den betroffenen Seiten Praesentations- und Autolayout setzen
//STRIP001      \********************************************************************/
//STRIP001      pPage = (SdPage*)pPageList->First();
//STRIP001      while(pPage)
//STRIP001      {
//STRIP001          AutoLayout eOldAutoLayout = pPage->GetAutoLayout();
//STRIP001          AutoLayout eNewAutoLayout =
//STRIP001              pPage->GetPageKind() == PK_STANDARD ? AUTOLAYOUT_NONE : AUTOLAYOUT_NOTES;
//STRIP001
//STRIP001          SdPresentationLayoutUndoAction * pPLUndoAction =
//STRIP001              new SdPresentationLayoutUndoAction
//STRIP001                      (this, aOldLayoutName, aName,
//STRIP001                       eOldAutoLayout, eNewAutoLayout, TRUE,
//STRIP001                       pPage);
//STRIP001          pUndoMgr->AddUndoAction(pPLUndoAction);
//STRIP001
//STRIP001          pPage->SetPresentationLayout(aName);
//STRIP001          pPage->SetAutoLayout(eNewAutoLayout);
//STRIP001
//STRIP001          pPage = (SdPage*)pPageList->Next();
//STRIP001      }
//STRIP001
//STRIP001      // Seitenliste loeschen
//STRIP001      delete pPageList;
//STRIP001  }
//STRIP001
//STRIP001  /*********************************************************************
//STRIP001  |* falls die alten Masterpages nicht mehr benoetigt werden,
//STRIP001  |* muessen sie und die entsprechenden Praesentationsvorlagen
//STRIP001  |* entfernt werden
//STRIP001  \********************************************************************/
//STRIP001  if (bCheckMasters)
//STRIP001  {
//STRIP001      // Alle pruefen
//STRIP001      RemoveUnnessesaryMasterPages();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // Nur die ausgetauschte MasterPage pruefen
//STRIP001      RemoveUnnessesaryMasterPages(pOldMaster);
//STRIP001  }
//STRIP001
//STRIP001  pUndoMgr->LeaveListAction();
//STRIP001
//STRIP001  if( pDocSh )
//STRIP001      pDocSh->SetWaitCursor( FALSE );
//STRIP001 }



//STRIP001 void SdDrawDocument::Merge(SdrModel& rSourceModel,
//STRIP001             USHORT nFirstPageNum, USHORT nLastPageNum,
//STRIP001             USHORT nDestPos,
//STRIP001             FASTBOOL bMergeMasterPages, FASTBOOL bAllMasterPages,
//STRIP001             FASTBOOL bUndo, FASTBOOL bTreadSourceAsConst)
//STRIP001 {
//STRIP001  SdrModel::Merge( rSourceModel, nFirstPageNum, nLastPageNum, nDestPos, bMergeMasterPages, bAllMasterPages, bUndo, bTreadSourceAsConst );
//STRIP001
//STRIP001  if( &rSourceModel == this )
//STRIP001      return;
//STRIP001
//STRIP001  // #55912# fix animation at path
//STRIP001  if( nLastPageNum >= rSourceModel.GetPageCount() )
//STRIP001      nLastPageNum = rSourceModel.GetPageCount()-1;
//STRIP001
//STRIP001  USHORT nSrcPage;
//STRIP001  USHORT nDstPage;
//STRIP001  for( nSrcPage = nFirstPageNum, nDstPage = nDestPos; (nSrcPage < nLastPageNum) && (nDstPage < GetPageCount()); nSrcPage++, nDstPage++ )
//STRIP001  {
//STRIP001      const SdrPage* pSrcPage = rSourceModel.GetPage( nSrcPage );
//STRIP001      const SdrPage* pDstPage = GetPage( nDstPage );
//STRIP001
//STRIP001      if( pSrcPage && pDstPage )
//STRIP001      {
//STRIP001          SdrObjListIter  aSrcIter( *pSrcPage, IM_DEEPWITHGROUPS );
//STRIP001          SdrObjListIter  aDstIter( *pDstPage, IM_DEEPWITHGROUPS );
//STRIP001
//STRIP001          SdrObject* pSrcObj;
//STRIP001          SdrObject* pDstObj;
//STRIP001          for( pSrcObj = aSrcIter.Next(), pDstObj = aDstIter.Next();
//STRIP001               pSrcObj && pDstObj;
//STRIP001               pSrcObj = aSrcIter.Next(), pDstObj = aDstIter.Next() )
//STRIP001          {
//STRIP001              SdAnimationInfo* pInfo = static_cast< SdDrawDocument* >(&rSourceModel)->GetAnimationInfo(const_cast<SdrObject*>(pSrcObj));
//STRIP001              if( pInfo && pInfo->eEffect == presentation::AnimationEffect_PATH && pInfo->pPathObj)
//STRIP001              {
//STRIP001                  SdrObjListIter  aSrcPathIter( *pSrcPage, IM_DEEPWITHGROUPS );
//STRIP001                  SdrObjListIter  aDstPathIter( *pDstPage, IM_DEEPWITHGROUPS );
//STRIP001                  SdrObject* pSrcPathObj;
//STRIP001                  SdrObject* pDstPathObj;
//STRIP001                  for( pSrcPathObj = aSrcPathIter.Next(), pDstPathObj = aDstPathIter.Next();
//STRIP001                       pSrcPathObj && pDstPathObj;
//STRIP001                       pSrcPathObj = aSrcPathIter.Next(), pDstPathObj = aDstPathIter.Next() )
//STRIP001                  {
//STRIP001                      if( pSrcPathObj == pInfo->pPathObj )
//STRIP001                      {
//STRIP001                          if( PTR_CAST( SdrPathObj, pDstPathObj ) )
//STRIP001                          {
//STRIP001                              SdAnimationInfo* pInfo = GetAnimationInfo(pDstObj);
//STRIP001                              if( pInfo == NULL )
//STRIP001                              {
//STRIP001                                  pInfo = new SdAnimationInfo(this);
//STRIP001                                  pDstObj->InsertUserData( pInfo );
//STRIP001                              }
//STRIP001
//STRIP001                              pInfo->eEffect = presentation::AnimationEffect_PATH;
//STRIP001                              pInfo->pPathObj = PTR_CAST(SdrPathObj, pDstPathObj );
//STRIP001                          }
//STRIP001                          break;
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }
}
