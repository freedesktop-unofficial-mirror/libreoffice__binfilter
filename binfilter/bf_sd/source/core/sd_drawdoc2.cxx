/*************************************************************************
 *
 *  $RCSfile: sd_drawdoc2.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 14:58:18 $
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

#pragma hdrstop

#ifndef _SV_WRKWIN_HXX
#include <vcl/wrkwin.hxx>
#endif

#ifndef SVX_LIGHT
#include <so3/iface.hxx>
#ifndef _SFX_PRINTER_HXX
#include <bf_sfx2/printer.hxx>
#endif
#ifndef _SFXAPP_HXX //autogen
#include <bf_sfx2/app.hxx>
#endif
#include "sdoutl.hxx"
#else   // SVX_LIGHT
#ifndef _OUTLINER_HXX //autogen wg. Outliner
#include <bf_svx/outliner.hxx>
#endif
#ifndef _SVDOUTL_HXX //autogen wg. Outliner
#include <bf_svx/svdoutl.hxx>
#endif
#define SfxPrinter Printer
#endif // !SVX_LIGHT

#ifndef _SVX_PAPERINF_HXX
#include <bf_svx/paperinf.hxx>
#endif
#ifndef _SVDOPAGE_HXX //autogen
#include <bf_svx/svdopage.hxx>
#endif
#ifndef _SVDOOLE2_HXX //autogen
#include <bf_svx/svdoole2.hxx>
#endif
#ifndef _SVDOTEXT_HXX //autogen
#include <bf_svx/svdotext.hxx>
#endif
#ifndef _SVDOGRAF_HXX //autogen
#include <bf_svx/svdograf.hxx>
#endif
#ifndef _SVDUNDO_HXX //autogen
#include <bf_svx/svdundo.hxx>
#endif
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif
#ifndef _EEITEM_HXX //autogen
#include <bf_svx/eeitem.hxx>
#endif
#ifndef _EEITEMID_HXX //autogen
#include <bf_svx/eeitemid.hxx>
#endif
#ifndef _SVX_LANGITEM_HXX
#include <bf_svx/langitem.hxx>
#endif
#ifndef _SFXITEMPOOL_HXX
#include <svtools/itempool.hxx>
#endif


#include <bf_svx/linkmgr.hxx>
#include <bf_svx/editdata.hxx>
#include <bf_svx/dialogs.hrc>
#include <bf_svx/dialmgr.hxx>                   // SVX_RESSTR

#include "eetext.hxx"

#ifndef _SVDITER_HXX //autogen
#include <bf_svx/svditer.hxx>
#endif
#ifndef _GOODIES_IMAPOBJ_HXX //autogen
#include <svtools/imapobj.hxx>
#endif


#include "sdresid.hxx"
#include "drawdoc.hxx"
#include "sdpage.hxx"
#include "pglink.hxx"
#include "glob.hrc"
#include "glob.hxx"
#include "stlpool.hxx"
#include "sdiocmpt.hxx"
#include "anminfo.hxx"
#include "imapinfo.hxx"
#include "cusshow.hxx"

#ifndef SVX_LIGHT
#ifdef MAC
#include "::ui:inc:docshell.hxx"
#include "::ui:inc:frmview.hxx"
#include "::ui:inc:cfgids.hxx"
#include "::ui:inc:strings.hrc"
#else
#ifdef UNX
#include "../ui/inc/docshell.hxx"
#include "../ui/inc/frmview.hxx"
#include "../ui/inc/cfgids.hxx"
#include "../ui/inc/strings.hrc"
#else
#include "..\ui\inc\docshell.hxx"
#include "..\ui\inc\frmview.hxx"
#include "..\ui\inc\cfgids.hxx"
#include "..\ui\inc\strings.hrc"
#endif
#endif

#endif // !SVX_LIGHT

/*N*/ const long PRINT_OFFSET = 30;     // siehe \svx\source\dialog\page.cxx (PB)


/*************************************************************************
|*
|* Sucht ein Objekt per Name
|*
\************************************************************************/

//STRIP001 SdrObject* SdDrawDocument::GetObj(const String& rObjName) const
//STRIP001 {
//STRIP001  SdrObject* pObj = NULL;
//STRIP001  SdrObject* pObjFound = NULL;
//STRIP001  SdPage* pPage = NULL;
//STRIP001
//STRIP001  /**************************************************************************
//STRIP001  * Zuerst alle Pages durchsuchen
//STRIP001  **************************************************************************/
//STRIP001  USHORT nPage = 0;
//STRIP001  const USHORT nMaxPages = GetPageCount();
//STRIP001
//STRIP001  while (nPage < nMaxPages && !pObjFound)
//STRIP001  {
//STRIP001      pPage = (SdPage*) GetPage(nPage);
//STRIP001      SdrObjListIter aIter(*pPage, IM_DEEPWITHGROUPS);
//STRIP001
//STRIP001      while (aIter.IsMore() && !pObjFound)
//STRIP001      {
//STRIP001          pObj = aIter.Next();
//STRIP001
//STRIP001          if( ( rObjName == pObj->GetName() ) ||
//STRIP001                 ( SdrInventor == pObj->GetObjInventor() &&
//STRIP001                   OBJ_OLE2 == pObj->GetObjIdentifier() &&
//STRIP001                   rObjName == static_cast< SdrOle2Obj* >( pObj )->GetPersistName() ) )
//STRIP001          {
//STRIP001              pObjFound = pObj;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      nPage++;
//STRIP001  }
//STRIP001
//STRIP001  /**************************************************************************
//STRIP001  * Wenn nicht gefunden, dann alle MasterPages durchsuchen
//STRIP001  **************************************************************************/
//STRIP001  nPage = 0;
//STRIP001  const USHORT nMaxMasterPages = GetMasterPageCount();
//STRIP001
//STRIP001  while (nPage < nMaxMasterPages && !pObjFound)
//STRIP001  {
//STRIP001      pPage = (SdPage*) GetMasterPage(nPage);
//STRIP001      SdrObjListIter aIter(*pPage, IM_DEEPWITHGROUPS);
//STRIP001
//STRIP001      while (aIter.IsMore() && !pObjFound)
//STRIP001      {
//STRIP001          pObj = aIter.Next();
//STRIP001
//STRIP001          if( ( rObjName == pObj->GetName() ) ||
//STRIP001                 ( SdrInventor == pObj->GetObjInventor() &&
//STRIP001                   OBJ_OLE2 == pObj->GetObjIdentifier() &&
//STRIP001                   rObjName == static_cast< SdrOle2Obj* >( pObj )->GetPersistName() ) )
//STRIP001          {
//STRIP001              pObjFound = pObj;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      nPage++;
//STRIP001  }
//STRIP001
//STRIP001  return (pObjFound);
//STRIP001 }


/*************************************************************************
|*
|* Sucht die SdPage per Name
|*
\************************************************************************/

USHORT SdDrawDocument::GetPageByName(const String& rPgName, BOOL& rbIsMasterPage) const
{
/*?*/ {DBG_ASSERT(0, "STRIP");} return 0;//STRIP001     SdPage* pPage = NULL;
//STRIP001  SdPage* pPageFound = NULL;
//STRIP001  USHORT nPage = 0;
//STRIP001  const USHORT nMaxPages = GetPageCount();
//STRIP001  USHORT nPageNum = SDRPAGE_NOTFOUND;
//STRIP001
//STRIP001     rbIsMasterPage = FALSE;
//STRIP001
//STRIP001  /**************************************************************************
//STRIP001  * Zuerst alle Pages durchsuchen
//STRIP001  **************************************************************************/
//STRIP001  while (nPage < nMaxPages && nPageNum == SDRPAGE_NOTFOUND)
//STRIP001  {
//STRIP001      pPage = (SdPage*) GetPage(nPage);
//STRIP001
//STRIP001      if (pPage && pPage->GetName() == rPgName)
//STRIP001      {
//STRIP001          nPageNum = nPage;
//STRIP001      }
//STRIP001
//STRIP001      nPage++;
//STRIP001  }
//STRIP001
//STRIP001  /**************************************************************************
//STRIP001  * Wenn nicht gefunden, dann alle MasterPages durchsuchen
//STRIP001  **************************************************************************/
//STRIP001  const USHORT nMaxMasterPages = GetMasterPageCount();
//STRIP001  nPage = 0;
//STRIP001
//STRIP001  while (nPage < nMaxMasterPages && nPageNum == SDRPAGE_NOTFOUND)
//STRIP001  {
//STRIP001      pPage = (SdPage*) GetMasterPage(nPage);
//STRIP001
//STRIP001      if (pPage && pPage->GetName() == rPgName)
//STRIP001      {
//STRIP001          nPageNum = nPage;
//STRIP001             rbIsMasterPage = TRUE;
//STRIP001      }
//STRIP001
//STRIP001      nPage++;
//STRIP001  }
//STRIP001
//STRIP001  return (nPageNum);
/*?*/ }


/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ SdPage* SdDrawDocument::GetSdPage(USHORT nPgNum, PageKind ePgKind) const
/*N*/ {
/*N*/   SdPage* pPage = NULL;
/*N*/   SdPage* pPageFound = NULL;
/*N*/
/*N*/   USHORT nPage = 0;
/*N*/   const USHORT nMaxPages = GetPageCount();
/*N*/   USHORT nPageNum = 0;
/*N*/
/*N*/   while (nPage < nMaxPages && !pPageFound)
/*N*/   {
/*N*/       pPage = (SdPage*) GetPage(nPage);
/*N*/
/*N*/       if (pPage && pPage->GetPageKind() == ePgKind)
/*N*/       {
/*N*/           if (nPageNum == nPgNum)
/*N*/           {
/*N*/               pPageFound = pPage;
/*N*/           }
/*N*/
/*N*/           nPageNum++;
/*N*/       }
/*N*/
/*N*/       nPage++;
/*N*/   }
/*N*/
/*N*/   return (pPageFound);
/*N*/ }


/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ USHORT SdDrawDocument::GetSdPageCount(PageKind ePgKind) const
/*N*/ {
/*N*/   SdPage* pPage = NULL;
/*N*/
/*N*/   USHORT nPage;
/*N*/   const USHORT nMaxPages = GetPageCount();
/*N*/   USHORT nPageNum = 0;
/*N*/
/*N*/   for (nPage = 0; nPage < nMaxPages; nPage++)
/*N*/   {
/*N*/       pPage = (SdPage*) GetPage(nPage);
/*N*/
/*N*/       if (pPage && pPage->GetPageKind() == ePgKind)
/*N*/       {
/*N*/           nPageNum++;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return (nPageNum);
/*N*/ }


/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ SdPage* SdDrawDocument::GetMasterSdPage(USHORT nPgNum, PageKind ePgKind)
/*N*/ {
/*N*/   SdPage* pPage = NULL;
/*N*/   SdPage* pPageFound = NULL;
/*N*/
/*N*/   USHORT nPage = 0;
/*N*/   const USHORT nMaxPages = GetMasterPageCount();
/*N*/   USHORT nPageNum = 0;
/*N*/
/*N*/   while (nPage < nMaxPages && !pPageFound)
/*N*/   {
/*N*/       pPage = (SdPage*) GetMasterPage(nPage);
/*N*/
/*N*/       if (pPage && pPage->GetPageKind() == ePgKind)
/*N*/       {
/*N*/           if (nPageNum == nPgNum)
/*N*/           {
/*N*/               pPageFound = pPage;
/*N*/           }
/*N*/
/*N*/           nPageNum++;
/*N*/       }
/*N*/
/*N*/       nPage++;
/*N*/   }
/*N*/
/*N*/    return (pPageFound);
/*N*/ }


/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ USHORT SdDrawDocument::GetMasterSdPageCount(PageKind ePgKind) const
/*N*/ {
/*N*/   SdPage* pPage = NULL;
/*N*/
/*N*/   USHORT nPage;
/*N*/   const USHORT nMaxPages = GetMasterPageCount();
/*N*/   USHORT nPageNum = 0;
/*N*/
/*N*/   for (nPage = 0; nPage < nMaxPages; nPage++)
/*N*/   {
/*N*/       pPage = (SdPage*) GetMasterPage(nPage);
/*N*/
/*N*/       if (pPage && pPage->GetPageKind() == ePgKind)
/*N*/       {
/*N*/           nPageNum++;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return (nPageNum);
/*N*/ }

/*************************************************************************
|*
|*  die in den Seitenobjekten der Notizseiten eingetragenen
|*  Seitennummern anpassen
|*
\************************************************************************/

/*N*/ void SdDrawDocument::UpdatePageObjectsInNotes(USHORT nStartPos)
/*N*/ {
/*N*/   USHORT  nPageCount  = GetPageCount();
/*N*/   SdPage* pPage       = NULL;
/*N*/
/*N*/   for (USHORT nPage = nStartPos; nPage < nPageCount; nPage++)
/*N*/   {
/*N*/       pPage = (SdPage*)GetPage(nPage);
/*N*/
/*N*/       // wenn es eine Notizseite ist, Seitenobjekt suchen
/*N*/       // und Nummer korrigieren
/*N*/       if (pPage && pPage->GetPageKind() == PK_NOTES)
/*N*/       {
/*N*/           ULONG nObjCount = pPage->GetObjCount();
/*N*/           SdrObject* pObj = NULL;
/*N*/           for (ULONG nObj = 0; nObj < nObjCount; nObj++)
/*N*/           {
/*?*/               pObj = pPage->GetObj(nObj);
/*?*/               if (pObj->GetObjIdentifier() == OBJ_PAGE &&
/*?*/                   pObj->GetObjInventor() == SdrInventor)
/*?*/               {
                    // das Seitenobjekt stellt die vorhergende Seite (also
                    // die Zeichenseite) dar
/*?*/                   DBG_ASSERTWARNING(nStartPos, "Notizseitenpos. darf nicht 0 sein");

/*?*/                   DBG_ASSERTWARNING(nPage > 1, "Seitenobjekt darf nicht Handzettel darstellen");

/*?*/                   if (nStartPos > 0 && nPage > 1)
/*?*/                       ((SdrPageObj*)pObj)->SetPageNum(nPage - 1);
/*?*/               }
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|*  Seite verschieben
|*
\************************************************************************/

//STRIP001 void SdDrawDocument::MovePage(USHORT nPgNum, USHORT nNewPos)
//STRIP001 {
//STRIP001  // Seite verschieben
//STRIP001  FmFormModel::MovePage(nPgNum, nNewPos);
//STRIP001
//STRIP001  USHORT nMin = Min(nPgNum, nNewPos);
//STRIP001
//STRIP001  UpdatePageObjectsInNotes(nMin);
//STRIP001 }

/*************************************************************************
|*
|*  Seite einfuegen
|*
\************************************************************************/

/*N*/ void SdDrawDocument::InsertPage(SdrPage* pPage, USHORT nPos)
/*N*/ {
/*N*/   FmFormModel::InsertPage(pPage, nPos);

/*N*/ #ifndef SVX_LIGHT
/*N*/   ((SdPage*)pPage)->ConnectLink();
/*N*/ #endif
/*N*/
/*N*/   UpdatePageObjectsInNotes(nPos);
/*N*/ }

/*************************************************************************
|*
|*  Seite loeschen
|*
\************************************************************************/

/*N*/ void SdDrawDocument::DeletePage(USHORT nPgNum)
/*N*/ {
/*N*/   FmFormModel::DeletePage(nPgNum);
/*N*/
/*N*/   UpdatePageObjectsInNotes(nPgNum);
/*N*/ }

/*************************************************************************
|*
|*  Seite entfernen
|*
\************************************************************************/

/*N*/ SdrPage* SdDrawDocument::RemovePage(USHORT nPgNum)
/*N*/ {
/*N*/   SdrPage* pPage = FmFormModel::RemovePage(nPgNum);
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/   ((SdPage*)pPage)->DisconnectLink();
/*N*/ #endif
/*N*/
/*N*/   if (pCustomShowList)
/*?*/   {
/*?*/       for (ULONG i = 0; i < pCustomShowList->Count(); i++)
/*?*/       {
            // Ggf. Seite aus der CustomShows ausfuegen
/*?*/           SdCustomShow* pCustomShow = (SdCustomShow*) pCustomShowList->GetObject(i);
/*?*/           pCustomShow->Remove(pPage);
/*?*/       }
/*?*/   }
/*N*/
/*N*/   UpdatePageObjectsInNotes(nPgNum);
/*N*/
/*N*/   return pPage;
/*N*/ }

//////////////////////////////////////////////////////////////////////////////
// #107844#
// An undo class which is able to set/unset user calls is needed to handle
// the undo/redo of PresObjs correctly. It can also add/remove the object
// from the PresObjList of that page.

//STRIP001 SdrUndoUserCallObj::SdrUndoUserCallObj(SdrObject& rNewObj, SdPage* pNew)
//STRIP001 :    SdrUndoObj(rNewObj),
//STRIP001  mpOld((SdPage*)rNewObj.GetUserCall()),
//STRIP001  mpNew(pNew)
//STRIP001 {
//STRIP001 }

//STRIP001 void SdrUndoUserCallObj::Undo()
//STRIP001 {
//STRIP001  if(mpNew)
//STRIP001  {
//STRIP001      List* pPresObjList = mpNew->GetPresObjList();
//STRIP001      pPresObjList->Remove(pObj);
//STRIP001  }
//STRIP001
//STRIP001  pObj->SetUserCall(mpOld);
//STRIP001
//STRIP001  if(mpOld)
//STRIP001  {
//STRIP001      List* pPresObjList = mpOld->GetPresObjList();
//STRIP001      pPresObjList->Insert(pObj, LIST_APPEND);
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrUndoUserCallObj::Redo()
//STRIP001 {
//STRIP001  if(mpOld)
//STRIP001  {
//STRIP001      List* pPresObjList = mpOld->GetPresObjList();
//STRIP001      pPresObjList->Remove(pObj);
//STRIP001  }
//STRIP001
//STRIP001  pObj->SetUserCall(mpNew);
//STRIP001
//STRIP001  if(mpNew)
//STRIP001  {
//STRIP001      List* pPresObjList = mpNew->GetPresObjList();
//STRIP001      pPresObjList->Insert(pObj, LIST_APPEND);
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* anfallenden Undo-Aktionen des SdrModels verwalten
|*
\************************************************************************/

// #107844#
// Inline has no advantages at such big code.
IMPL_LINK( SdDrawDocument, NotifyUndoActionHdl, SfxUndoAction *, pUndoAction )
{
        DBG_ASSERT(0, "STRIP"); //STRIP001 //STRIP001 #ifndef SVX_LIGHT
//STRIP001  if (pUndoAction)
//STRIP001  {
//STRIP001      if ( pDeletedPresObjList )
//STRIP001      {
//STRIP001          if( pDeletedPresObjList->Count() )
//STRIP001          {
//STRIP001              // Praesentationsobjekte sollen geloescht werden
//STRIP001              ULONG nCount = pDeletedPresObjList->Count();
//STRIP001
//STRIP001              // #107844#
//STRIP001              // SfxUndoAction::Merge() is empty implemented and does
//STRIP001              // nothing. To really add the action here without getting
//STRIP001              // a recursive call to this link the RTTI needs to be used.
//STRIP001              // So, pUndoGroup is filled and used if this worked well.
//STRIP001              SdrUndoGroup* pUndoGroup;
//STRIP001
//STRIP001              if(pUndoAction->ISA(SdrUndoGroup))
//STRIP001              {
//STRIP001                  pUndoGroup = (SdrUndoGroup*)pUndoAction;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  DBG_ASSERT(sal_False, "SdDrawDocument::NotifyUndoActionHdl: Could not add undo action (!)");
//STRIP001              }
//STRIP001
//STRIP001              for (ULONG i=0; i < nCount; i++)
//STRIP001              {
//STRIP001                  // #107844# Take the other direction here to create the new placeholders
//STRIP001                  // in the correct order since they were deleted reversely. Else, travelling
//STRIP001                  // over the text objects using CTRL+RETURN was in wrong order.
//STRIP001                  SdrObject* pObj = (SdrObject*) pDeletedPresObjList->GetObject((nCount - 1) - i);
//STRIP001
//STRIP001                  // #107844#
//STRIP001                  // Decide between empty and not-empty PresObj later
//STRIP001                  if (pObj)
//STRIP001                  {
//STRIP001                      if (pObj->ISA(SdrTextObj))
//STRIP001                      {
//STRIP001                          SdrTextObj* pTextObj = (SdrTextObj*) pObj;
//STRIP001
//STRIP001                          if (pTextObj)
//STRIP001                          {
//STRIP001                              String aString;
//STRIP001                              SdPage* pPage = (SdPage*) pTextObj->GetUserCall();
//STRIP001
//STRIP001                              if (pPage)
//STRIP001                              {
//STRIP001                                  PresObjKind ePresObjKind = pPage->GetPresObjKind(pTextObj);
//STRIP001                                  PageKind ePageKind = pPage->GetPageKind();
//STRIP001
//STRIP001                                  if(pUndoGroup)
//STRIP001                                  {
//STRIP001                                      // #107844#
//STRIP001                                      // Add new Undo-Action here
//STRIP001                                      pUndoGroup->AddAction(new SdrUndoUserCallObj(*pTextObj, NULL));
//STRIP001                                  }
//STRIP001
//STRIP001                                  List* pPresObjList = pPage->GetPresObjList();
//STRIP001                                  pPresObjList->Remove((void*) pTextObj);
//STRIP001                                  pTextObj->SetUserCall(NULL);
//STRIP001
//STRIP001                                  if(!pObj->IsEmptyPresObj())
//STRIP001                                  {
//STRIP001                                      // #107844#
//STRIP001                                      // create empty new presobj
//STRIP001                                      if (ePresObjKind == PRESOBJ_TITLE)
//STRIP001                                      {
//STRIP001                                          if ( pPage->IsMasterPage() )
//STRIP001                                          {
//STRIP001                                              if (ePageKind != PK_NOTES)
//STRIP001                                              {
//STRIP001                                                  aString = String ( SdResId( STR_PRESOBJ_MPTITLE ) );
//STRIP001                                              }
//STRIP001                                              else
//STRIP001                                              {
//STRIP001                                                  aString = String ( SdResId( STR_PRESOBJ_MPNOTESTITLE ) );
//STRIP001                                              }
//STRIP001                                          }
//STRIP001                                          else
//STRIP001                                          {
//STRIP001                                              aString = String (SdResId(STR_PRESOBJ_TITLE));
//STRIP001                                          }
//STRIP001                                      }
//STRIP001                                      else if (ePresObjKind == PRESOBJ_OUTLINE)
//STRIP001                                      {
//STRIP001                                          ePresObjKind = PRESOBJ_OUTLINE;
//STRIP001
//STRIP001                                          if ( pPage->IsMasterPage() )
//STRIP001                                          {
//STRIP001                                              aString = String (SdResId(STR_PRESOBJ_MPOUTLINE));
//STRIP001                                          }
//STRIP001                                          else
//STRIP001                                          {
//STRIP001                                              aString = String (SdResId(STR_PRESOBJ_OUTLINE));
//STRIP001                                          }
//STRIP001                                      }
//STRIP001                                      else if (ePresObjKind == PRESOBJ_NOTES)
//STRIP001                                      {
//STRIP001                                          if ( pPage->IsMasterPage() )
//STRIP001                                          {
//STRIP001                                              aString = String ( SdResId( STR_PRESOBJ_MPNOTESTEXT ) );
//STRIP001                                          }
//STRIP001                                          else
//STRIP001                                          {
//STRIP001                                              aString = String ( SdResId( STR_PRESOBJ_NOTESTEXT ) );
//STRIP001                                          }
//STRIP001                                      }
//STRIP001                                      else if (ePresObjKind == PRESOBJ_TEXT)
//STRIP001                                      {
//STRIP001                                          aString = String ( SdResId( STR_PRESOBJ_TEXT ) );
//STRIP001                                      }
//STRIP001
//STRIP001                                      if ( aString.Len() )
//STRIP001                                      {
//STRIP001                                          GetInternalOutliner(TRUE);
//STRIP001                                          pInternalOutliner->SetMinDepth(0);
//STRIP001
//STRIP001                                          SdrTextObj* pNewTextObj = (SdrTextObj*)pTextObj->Clone();
//STRIP001                                          pPage->InsertObject(pNewTextObj);
//STRIP001
//STRIP001                                          pPage->SetObjText(pNewTextObj, pInternalOutliner, ePresObjKind, aString);
//STRIP001                                          pNewTextObj->NbcSetStyleSheet(pPage->GetStyleSheetForPresObj(ePresObjKind), TRUE);
//STRIP001                                          pNewTextObj->SetEmptyPresObj(TRUE);
//STRIP001
//STRIP001                                          if(pUndoGroup)
//STRIP001                                          {
//STRIP001                                              // #107844#
//STRIP001                                              // Add new Undo-Action here
//STRIP001                                              pUndoGroup->AddAction(new SdrUndoUserCallObj(*pNewTextObj, pPage));
//STRIP001                                          }
//STRIP001
//STRIP001                                          pNewTextObj->SetUserCall(pPage);
//STRIP001                                          List* pPresObjList = pPage->GetPresObjList();
//STRIP001                                          pPresObjList->Insert(pNewTextObj, LIST_APPEND);
//STRIP001
//STRIP001                                          if(pUndoGroup)
//STRIP001                                          {
//STRIP001                                              // #107844#
//STRIP001                                              // Add new Undo-Action here
//STRIP001                                              pUndoGroup->AddAction(new SdrUndoNewObj(*pNewTextObj));
//STRIP001                                          }
//STRIP001
//STRIP001                                          pInternalOutliner->Clear();
//STRIP001                                          pInternalOutliner->SetMinDepth(0);
//STRIP001                                      }
//STRIP001                                  }
//STRIP001                              }
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          delete pDeletedPresObjList;
//STRIP001          pDeletedPresObjList = NULL;
//STRIP001      }
//STRIP001
//STRIP001      if (pDocSh)
//STRIP001      {
//STRIP001          pDocSh->GetUndoManager()->AddUndoAction(pUndoAction);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001 #endif // !SVX_LIGHT
    return 0;
}

/*************************************************************************
|*
|* Seiten selektieren
|*
\************************************************************************/

/*N*/ void SdDrawDocument::SetSelected(SdPage* pPage, BOOL bSelect)
/*N*/ {
/*N*/   PageKind ePageKind = pPage->GetPageKind();
/*N*/
/*N*/   if (ePageKind == PK_STANDARD)
/*N*/   {
/*N*/       pPage->SetSelected(bSelect);
/*N*/       SdPage* pNotesPage = (SdPage*) GetPage( pPage->GetPageNum() + 1 );
/*N*/
/*N*/       if (pNotesPage && pNotesPage->GetPageKind() == PK_NOTES)
/*N*/           pNotesPage->SetSelected(bSelect);
/*N*/   }
/*N*/   else if (ePageKind == PK_NOTES)
/*?*/   {
/*?*/       pPage->SetSelected(bSelect);
/*?*/       SdPage* pStandardPage = (SdPage*) GetPage( pPage->GetPageNum() - 1 );

/*?*/       if (pStandardPage && pStandardPage->GetPageKind() == PK_STANDARD)
/*?*/           pStandardPage->SetSelected(bSelect);
/*?*/   }
/*N*/ }

/*************************************************************************
|*
|* Sofern noch keine Seiten vorhanden sind, werden nun Seiten erzeugt
|*
\************************************************************************/

/*N*/ void SdDrawDocument::CreateFirstPages()
/*N*/ {
    /**************************************************************************
    * Wenn noch keine Seite im Model vorhanden ist (Datei-Neu), wird
    * eine neue Seite eingefuegt
    **************************************************************************/
/*N*/   USHORT nPageCount = GetPageCount();
/*N*/
/*N*/   if (nPageCount <= 1)
/*N*/   {
         /**********************************************************************
         * Default-Papiergroesse vom Drucker holen
         **********************************************************************/
/*N*/       SfxPrinter* pPrinter = NULL;
/*N*/       Size aDefSize(21000, 29700);   // A4-Hochformat
/*N*/
/*N*/       if (pDocSh)
/*N*/       {
/*N*/           pPrinter = pDocSh->GetPrinter(TRUE);
/*N*/
/*N*/           if (pPrinter->IsValid())
/*N*/           {
/*N*/               // Der Printer gibt leider kein exaktes Format (z.B. A4) zurueck
/*N*/               aDefSize = pPrinter->GetPaperSize();
/*N*/               SvxPaper ePaper = SvxPaperInfo::GetSvxPaper(aDefSize, MAP_100TH_MM, TRUE);
/*N*/
/*N*/               if (ePaper != SVX_PAPER_USER)
/*N*/               {
/*N*/                   // Korrekte Size holen
/*N*/                   aDefSize = SvxPaperInfo::GetPaperSize(ePaper, MAP_100TH_MM);
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/
        /**********************************************************************
        * Handzettel-Seite einfuegen
        **********************************************************************/
/*N*/       BOOL bMasterPage;
/*N*/       SdPage* pHandoutPage = (SdPage*) AllocPage(bMasterPage=FALSE);
/*N*/
/*N*/       // Stets Querformat
/*N*/       if (aDefSize.Height() <= aDefSize.Width())
/*N*/       {
/*N*/           pHandoutPage->SetSize(aDefSize);
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           pHandoutPage->SetSize( Size(aDefSize.Height(), aDefSize.Width()) );
/*N*/       }
/*N*/
/*N*/       pHandoutPage->SetBorder(2000, 2000, 2000, 2000);
/*N*/       pHandoutPage->SetPageKind(PK_HANDOUT);
/*N*/       pHandoutPage->SetName( String (SdResId(STR_HANDOUT) ) );
/*N*/       InsertPage(pHandoutPage, 0);
/*N*/
        /**********************************************************************
        * MasterPage einfuegen und an der Handzettel-Seite vermerken
        **********************************************************************/
/*N*/       SdPage* pHandoutMPage = (SdPage*) AllocPage(bMasterPage=TRUE);
/*N*/       pHandoutMPage->SetSize( pHandoutPage->GetSize() );
/*N*/       pHandoutMPage->SetPageKind(PK_HANDOUT);
/*N*/       pHandoutMPage->SetBorder( pHandoutPage->GetLftBorder(),
/*N*/                                 pHandoutPage->GetUppBorder(),
/*N*/                                 pHandoutPage->GetRgtBorder(),
/*N*/                                 pHandoutPage->GetLwrBorder() );
/*N*/       InsertMasterPage(pHandoutMPage, 0);
/*N*/       pHandoutPage->InsertMasterPage( pHandoutMPage->GetPageNum() );

        /**********************************************************************
        * Seite einfuegen
        * Sofern nPageCount==1 ist, wurde das Model fuers Clipboad erzeugt.
        * Eine Standard-Seite ist daher schon vorhanden.
        **********************************************************************/
/*N*/       SdPage* pPage;
/*N*/       BOOL bClipboard = FALSE;
/*N*/
/*N*/       if (nPageCount == 0)
/*N*/       {
/*N*/           pPage = (SdPage*) AllocPage(bMasterPage=FALSE);
/*N*/
/*N*/           if (eDocType == DOCUMENT_TYPE_DRAW)
/*N*/           {
/*N*/               // Draw: stets Default-Groesse mit Raendern
/*N*/               pPage->SetSize(aDefSize);

/*N*/               if (pPrinter->IsValid())
/*N*/               {
/*N*/                   Size aOutSize(pPrinter->GetOutputSize());
/*N*/                   Point aPageOffset(pPrinter->GetPageOffset());
/*N*/                   aPageOffset -= pPrinter->PixelToLogic( Point() );
/*N*/                   long nOffset = !aPageOffset.X() && !aPageOffset.X() ? 0 : PRINT_OFFSET;
/*N*/
/*N*/                   ULONG nTop    = aPageOffset.Y();
/*N*/                   ULONG nLeft   = aPageOffset.X();
/*N*/                   ULONG nBottom = Max((long)(aDefSize.Height() - aOutSize.Height() - nTop + nOffset), 0L);
/*N*/                   ULONG nRight  = Max((long)(aDefSize.Width() - aOutSize.Width() - nLeft + nOffset), 0L);
/*N*/
/*N*/                   pPage->SetBorder(nLeft, nTop, nRight, nBottom);
/*N*/               }
/*?*/               else
/*?*/               {
/*?*/                   pPage->SetBorder(0, 0, 0, 0);
/*?*/               }
/*?*/           }
/*N*/           else
/*N*/           {
/*N*/               // Impress: stets Bildschirmformat
/*N*/               pPage->SetSize( Size(28000, 21000) );   // Bildschirmformat
/*N*/               pPage->SetBorder(0, 0, 0, 0);
/*N*/           }
/*N*/
/*N*/           InsertPage(pPage, 1);
/*N*/       }
/*?*/       else
/*?*/       {
/*?*/           bClipboard = TRUE;
/*?*/           pPage = (SdPage*) GetPage(1);
/*?*/       }

        /**********************************************************************
        * MasterPage einfuegen und an der Seite vermerken
        **********************************************************************/
/*N*/       SdPage* pMPage = (SdPage*) AllocPage(bMasterPage=TRUE);
/*N*/       pMPage->SetSize( pPage->GetSize() );
/*N*/       pMPage->SetBorder( pPage->GetLftBorder(),
/*N*/                          pPage->GetUppBorder(),
/*N*/                          pPage->GetRgtBorder(),
/*N*/                          pPage->GetLwrBorder() );
/*N*/       InsertMasterPage(pMPage, 1);
/*N*/       pPage->InsertMasterPage( pMPage->GetPageNum() );
/*N*/       if( bClipboard )
/*?*/           pMPage->SetLayoutName( pPage->GetLayoutName() );

        /**********************************************************************
        * Notizen-Seite einfuegen
        **********************************************************************/
/*N*/       SdPage* pNotesPage = (SdPage*) AllocPage(bMasterPage=FALSE);
/*N*/
/*N*/       // Stets Hochformat
/*N*/       if (aDefSize.Height() >= aDefSize.Width())
/*N*/       {
/*N*/           pNotesPage->SetSize(aDefSize);
/*N*/       }
/*?*/       else
/*?*/       {
/*?*/           pNotesPage->SetSize( Size(aDefSize.Height(), aDefSize.Width()) );
/*?*/       }

/*N*/       pNotesPage->SetBorder(2000, 2000, 2000, 2000);
/*N*/       pNotesPage->SetPageKind(PK_NOTES);
/*N*/       InsertPage(pNotesPage, 2);
/*N*/       if( bClipboard )
/*?*/           pNotesPage->SetLayoutName( pPage->GetLayoutName() );

        /**********************************************************************
        * MasterPage einfuegen und an der Notizen-Seite vermerken
        **********************************************************************/
/*N*/       SdPage* pNotesMPage = (SdPage*) AllocPage(bMasterPage=TRUE);
/*N*/       pNotesMPage->SetSize( pNotesPage->GetSize() );
/*N*/       pNotesMPage->SetPageKind(PK_NOTES);
/*N*/       pNotesMPage->SetBorder( pNotesPage->GetLftBorder(),
/*N*/                               pNotesPage->GetUppBorder(),
/*N*/                               pNotesPage->GetRgtBorder(),
/*N*/                               pNotesPage->GetLwrBorder() );
/*N*/       InsertMasterPage(pNotesMPage, 2);
/*N*/       pNotesPage->InsertMasterPage( pNotesMPage->GetPageNum() );
/*N*/       if( bClipboard )
/*?*/           pNotesMPage->SetLayoutName( pPage->GetLayoutName() );

/*N*/       pWorkStartupTimer = new Timer();
/*N*/       pWorkStartupTimer->SetTimeoutHdl( LINK(this, SdDrawDocument, WorkStartupHdl) );
/*N*/       pWorkStartupTimer->SetTimeout(2000);
/*N*/       pWorkStartupTimer->Start();
/*N*/
/*N*/       SetChanged(FALSE);
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Erzeugt fehlende Notiz und Handzettelseiten (nach PowerPoint-Import)
|* Es wird davon ausgegangen, dass mindestens eine Standard-Seite und
|* eine Standard-MasterPage vorhanden sind.
|*
\************************************************************************/

//STRIP001 BOOL SdDrawDocument::CreateMissingNotesAndHandoutPages()
//STRIP001 {
//STRIP001  BOOL bOK = FALSE;
//STRIP001  USHORT nPageCount = GetPageCount();
//STRIP001
//STRIP001  if (nPageCount != 0)
//STRIP001  {
//STRIP001      /**********************************************************************
//STRIP001      * PageKind setzen
//STRIP001      **********************************************************************/
//STRIP001      SdPage* pHandoutMPage = (SdPage*) GetMasterPage(0);
//STRIP001      pHandoutMPage->SetPageKind(PK_HANDOUT);
//STRIP001
//STRIP001      SdPage* pHandoutPage = (SdPage*) GetPage(0);
//STRIP001      pHandoutPage->SetPageKind(PK_HANDOUT);
//STRIP001      pHandoutPage->InsertMasterPage(pHandoutMPage->GetPageNum());
//STRIP001
//STRIP001      for (USHORT i = 1; i < nPageCount; i = i + 2)
//STRIP001      {
//STRIP001          SdPage* pPage = (SdPage*) GetPage(i);
//STRIP001
//STRIP001          if (pPage->GetMasterPageCount() == 0)
//STRIP001          {
//STRIP001              // Keine MasterPage gesetzt -> erste Standard-MasterPage nehmen
//STRIP001              // (Wenn bei PPT keine Standard-Seite vorhanden war)
//STRIP001              pPage->InsertMasterPage(1);
//STRIP001          }
//STRIP001
//STRIP001          SdPage* pNotesPage = (SdPage*) GetPage(i+1);
//STRIP001          pNotesPage->SetPageKind(PK_NOTES);
//STRIP001
//STRIP001          // Notiz-MasterPages setzen
//STRIP001          pNotesPage->RemoveMasterPage(0);
//STRIP001          USHORT nNum = pPage->GetMasterPageNum(0) + 1;
//STRIP001          pNotesPage->InsertMasterPage(nNum);
//STRIP001      }
//STRIP001
//STRIP001      bOK = TRUE;
//STRIP001      StopWorkStartupDelay();
//STRIP001      SetChanged(FALSE);
//STRIP001  }
//STRIP001
//STRIP001  return(bOK);
//STRIP001 }

/*************************************************************************
|*
|* - selektierte Seiten hinter genannte Seite schieben
|*   (nTargetPage = (USHORT)-1  --> vor erste Seite schieben)
|* - ergibt TRUE, wenn Seiten verschoben wurden
|*
\************************************************************************/

//STRIP001 BOOL SdDrawDocument::MovePages(USHORT nTargetPage)
//STRIP001 {
//STRIP001  SdPage* pTargetPage        = NULL;
//STRIP001  SdPage* pPage              = NULL;
//STRIP001  USHORT  nPage;
//STRIP001  USHORT  nNoOfPages         = GetSdPageCount(PK_STANDARD);
//STRIP001  BOOL    bSomethingHappened = FALSE;
//STRIP001
//STRIP001  BegUndo(String(SdResId(STR_UNDO_MOVEPAGES)));
//STRIP001
//STRIP001  // Liste mit selektierten Seiten
//STRIP001  List    aPageList;
//STRIP001  for (nPage = 0; nPage < nNoOfPages; nPage++)
//STRIP001  {
//STRIP001      pPage = GetSdPage(nPage, PK_STANDARD);
//STRIP001      if (pPage->IsSelected())
//STRIP001      {
//STRIP001          aPageList.Insert(pPage, LIST_APPEND);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // falls noetig, nach vorne hangeln, bis nicht selektierte Seite gefunden
//STRIP001  nPage = nTargetPage;
//STRIP001  if (nPage != (USHORT)-1)
//STRIP001  {
//STRIP001      pPage = GetSdPage(nPage, PK_STANDARD);
//STRIP001      while (nPage > 0 && pPage->IsSelected())
//STRIP001      {
//STRIP001          nPage--;
//STRIP001          pPage = GetSdPage(nPage, PK_STANDARD);
//STRIP001      }
//STRIP001
//STRIP001      if (pPage->IsSelected())
//STRIP001      {
//STRIP001          nPage = (USHORT)-1;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // vor der ersten Seite einfuegen
//STRIP001  if (nPage == (USHORT)-1)
//STRIP001  {
//STRIP001      while (aPageList.Count() > 0)
//STRIP001      {
//STRIP001          aPageList.Last();
//STRIP001
//STRIP001          nPage = ( (SdPage*) aPageList.GetCurObject() )->GetPageNum();
//STRIP001          if (nPage != 0)
//STRIP001          {
//STRIP001              SdrPage* pPg = GetPage(nPage);
//STRIP001              AddUndo(new SdrUndoSetPageNum(*pPg, nPage, 1));
//STRIP001              MovePage(nPage, 1);
//STRIP001              pPg = GetPage(nPage+1);
//STRIP001              AddUndo(new SdrUndoSetPageNum(*pPg, nPage+1, 2));
//STRIP001              MovePage(nPage+1, 2);
//STRIP001              bSomethingHappened = TRUE;
//STRIP001          }
//STRIP001          aPageList.Remove();
//STRIP001      }
//STRIP001  }
//STRIP001  // hinter <nPage> einfuegen
//STRIP001  else
//STRIP001  {
//STRIP001      pTargetPage = GetSdPage(nPage, PK_STANDARD);
//STRIP001      nTargetPage = nPage;
//STRIP001      nTargetPage = 2 * nTargetPage + 1;    // PK_STANDARD --> absolut
//STRIP001      while (aPageList.Count() > 0)
//STRIP001      {
//STRIP001          pPage = (SdPage*)aPageList.GetObject(0);
//STRIP001          nPage = pPage->GetPageNum();
//STRIP001          if (nPage > nTargetPage)
//STRIP001          {
//STRIP001              nTargetPage += 2;        // hinter (!) der Seite einfuegen
//STRIP001
//STRIP001              if (nPage != nTargetPage)
//STRIP001              {
//STRIP001                  SdrPage* pPg = GetPage(nPage);
//STRIP001                  AddUndo(new SdrUndoSetPageNum(*pPg, nPage, nTargetPage));
//STRIP001                  MovePage(nPage, nTargetPage);
//STRIP001                  pPg = GetPage(nPage+1);
//STRIP001                  AddUndo(new SdrUndoSetPageNum(*pPg, nPage+1, nTargetPage+1));
//STRIP001                  MovePage(nPage+1, nTargetPage+1);
//STRIP001                  bSomethingHappened = TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              if (nPage != nTargetPage)
//STRIP001              {
//STRIP001                  SdrPage* pPg = GetPage(nPage+1);
//STRIP001                  AddUndo(new SdrUndoSetPageNum(*pPg, nPage+1, nTargetPage+1));
//STRIP001                  MovePage(nPage+1, nTargetPage+1);
//STRIP001                  pPg = GetPage(nPage);
//STRIP001                  AddUndo(new SdrUndoSetPageNum(*pPg, nPage, nTargetPage));
//STRIP001                  MovePage(nPage, nTargetPage);
//STRIP001                  bSomethingHappened = TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001          aPageList.Remove((ULONG)0);
//STRIP001          nTargetPage = pPage->GetPageNum();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  EndUndo();
//STRIP001
//STRIP001  return bSomethingHappened;
//STRIP001 }


/*************************************************************************
|*
|* Anzahl der Links im LinkManager zurueckgeben
|*
\************************************************************************/

//STRIP001 ULONG SdDrawDocument::GetLinkCount()
//STRIP001 {
//STRIP001  return ( pLinkManager->GetLinks().Count() );
//STRIP001 }

/*************************************************************************
|*
|* Language setzen
|*
\************************************************************************/

/*N*/ void SdDrawDocument::SetLanguage( const LanguageType eLang, const USHORT nId )
/*N*/ {
/*N*/   BOOL bChanged = FALSE;
/*N*/
/*N*/   if( nId == EE_CHAR_LANGUAGE && eLanguage != eLang )
/*N*/   {
/*N*/       eLanguage = eLang;
/*N*/       bChanged = TRUE;
/*N*/   }
/*N*/   else if( nId == EE_CHAR_LANGUAGE_CJK && eLanguageCJK != eLang )
/*N*/   {
/*N*/       eLanguageCJK = eLang;
/*N*/       bChanged = TRUE;
/*N*/   }
/*N*/   else if( nId == EE_CHAR_LANGUAGE_CTL && eLanguageCTL != eLang )
/*N*/   {
/*N*/       eLanguageCTL = eLang;
/*N*/       bChanged = TRUE;
/*N*/   }
/*N*/
/*N*/   if( bChanged )
/*N*/   {
/*N*/       GetDrawOutliner().SetDefaultLanguage( Application::GetSettings().GetLanguage() );
/*N*/       pHitTestOutliner->SetDefaultLanguage( Application::GetSettings().GetLanguage() );
/*N*/       pItemPool->SetPoolDefaultItem( SvxLanguageItem( eLang, nId ) );
/*N*/       SetChanged( bChanged );
/*N*/   }
/*N*/ }


/*************************************************************************
|*
|* Return language
|*
\************************************************************************/

/*N*/ LanguageType SdDrawDocument::GetLanguage( const USHORT nId ) const
/*N*/ {
/*N*/   LanguageType eLangType = eLanguage;
/*N*/
/*N*/   if( nId == EE_CHAR_LANGUAGE_CJK )
/*N*/       eLangType = eLanguageCJK;
/*N*/   else if( nId == EE_CHAR_LANGUAGE_CTL )
/*N*/       eLangType = eLanguageCTL;
/*N*/
/*N*/   return eLangType;
/*N*/ }


/*************************************************************************
|*
|* WorkStartup einleiten
|*
\************************************************************************/

/*N*/ IMPL_LINK( SdDrawDocument, WorkStartupHdl, Timer *, pTimer )
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   if( pDocSh )
/*N*/       pDocSh->SetWaitCursor( TRUE );
/*N*/ #endif
/*N*/
/*N*/   BOOL bChanged = IsChanged();        // merken
/*N*/
/*N*/   // Autolayouts initialisieren
/*N*/   SdPage* pHandoutMPage = GetMasterSdPage(0, PK_HANDOUT);
/*N*/
/*N*/   if (pHandoutMPage->GetAutoLayout() == AUTOLAYOUT_NONE)
/*N*/   {
/*N*/       // AutoLayout wurde noch nicht umgesetzt -> Initialisieren
/*N*/       pHandoutMPage->SetAutoLayout(AUTOLAYOUT_HANDOUT4, TRUE);
/*N*/   }
/*N*/
/*N*/   SdPage* pPage = GetSdPage(0, PK_STANDARD);
/*N*/
/*N*/   if (pPage->GetAutoLayout() == AUTOLAYOUT_NONE)
/*N*/   {
/*N*/       // AutoLayout wurde noch nicht umgesetzt -> Initialisieren
/*N*/       pPage->SetAutoLayout(AUTOLAYOUT_NONE, TRUE);
/*N*/   }
/*N*/
/*N*/   SdPage* pNotesPage = GetSdPage(0, PK_NOTES);
/*N*/
/*N*/   if (pNotesPage->GetAutoLayout() == AUTOLAYOUT_NONE)
/*N*/   {
/*N*/       // AutoLayout wurde noch nicht umgesetzt -> Initialisieren
/*N*/       pNotesPage->SetAutoLayout(AUTOLAYOUT_NOTES, TRUE);
/*N*/   }
/*N*/
/*N*/   SetChanged(bChanged || FALSE);
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/   if( pDocSh )
/*N*/       pDocSh->SetWaitCursor( FALSE );
/*N*/ #endif
/*N*/   return 0;
/*N*/ }


/*************************************************************************
|*
|* Wenn der WorkStartupTimer erzeugt worden ist (das erfolgt ausschliesslich
|* in SdDrawViewShell::Consruct() ), so wird der Timer ggf. gestoppt und
|* das WorkStartup eingeleitet
|*
\************************************************************************/

/*N*/ void SdDrawDocument::StopWorkStartupDelay()
/*N*/ {
/*N*/   if (pWorkStartupTimer)
/*N*/   {
/*N*/       if ( pWorkStartupTimer->IsActive() )
/*N*/       {
/*N*/           // Timer war noch nicht abgelaufen -> WorkStartup wird eingeleitet
/*N*/           pWorkStartupTimer->Stop();
/*N*/           WorkStartupHdl(NULL);
/*N*/       }
/*N*/
/*N*/       delete pWorkStartupTimer;
/*N*/       pWorkStartupTimer = NULL;
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|* Wenn der WorkStartupTimer erzeugt worden ist (das erfolgt ausschliesslich
|* in SdDrawViewShell::Consruct() ), so wird der Timer ggf. gestoppt und
|* das WorkStartup eingeleitet
|*
\************************************************************************/

/*N*/ SdAnimationInfo* SdDrawDocument::GetAnimationInfo(SdrObject* pObject) const
/*N*/ {
/*N*/   DBG_ASSERT(pObject, "ohne Objekt keine AnimationsInfo");
/*N*/   USHORT nUD          = 0;
/*N*/   USHORT nUDCount     = pObject->GetUserDataCount();
/*N*/   SdrObjUserData* pUD = NULL;
/*N*/
/*N*/   // gibt es in den User-Daten eine Animationsinformation?
/*N*/   for (nUD = 0; nUD < nUDCount; nUD++)
/*N*/   {
/*N*/       pUD = pObject->GetUserData(nUD);
/*N*/       if (pUD->GetInventor() == SdUDInventor   &&
/*N*/           pUD->GetId() == SD_ANIMATIONINFO_ID)
/*N*/       {
/*N*/           return (SdAnimationInfo*)pUD;
/*N*/       }
/*N*/   }
/*N*/   return NULL;
/*N*/ }


/*************************************************************************
|*
|*
|*
\************************************************************************/

/*N*/ SdIMapInfo* SdDrawDocument::GetIMapInfo( SdrObject* pObject ) const
/*N*/ {
/*N*/   DBG_ASSERT(pObject, "ohne Objekt keine IMapInfo");
/*N*/
/*N*/   SdrObjUserData* pUserData = NULL;
/*N*/   SdIMapInfo*     pIMapInfo = NULL;
/*N*/   USHORT          nCount = pObject->GetUserDataCount();
/*N*/
/*N*/   // gibt es in den User-Daten eine IMap-Information?
/*N*/   for ( USHORT i = 0; i < nCount; i++ )
/*N*/   {
/*N*/       pUserData = pObject->GetUserData( i );
/*N*/
/*N*/       if ( ( pUserData->GetInventor() == SdUDInventor ) && ( pUserData->GetId() == SD_IMAPINFO_ID ) )
/*N*/           pIMapInfo = (SdIMapInfo*) pUserData;
/*N*/   }
/*N*/
/*N*/   return pIMapInfo;
/*N*/ }


/*************************************************************************
|*
|*
|*
\************************************************************************/

//STRIP001 IMapObject* SdDrawDocument::GetHitIMapObject( SdrObject* pObj,
//STRIP001                                            const Point& rWinPoint,
//STRIP001                                            const Window& rCmpWnd )
//STRIP001 {
//STRIP001  SdIMapInfo* pIMapInfo = GetIMapInfo( pObj );
//STRIP001  IMapObject* pIMapObj = NULL;
//STRIP001
//STRIP001  if ( pIMapInfo )
//STRIP001  {
//STRIP001      const MapMode       aMap100( MAP_100TH_MM );
//STRIP001      Size                aGraphSize;
//STRIP001      Point               aRelPoint( rWinPoint );
//STRIP001      ImageMap&           rImageMap = (ImageMap&) pIMapInfo->GetImageMap();
//STRIP001      const Rectangle&    rRect = pObj->GetLogicRect();
//STRIP001      BOOL                bObjSupported = FALSE;
//STRIP001
//STRIP001      // HitTest ausfuehren
//STRIP001      if ( pObj->ISA( SdrGrafObj )  ) // einfaches Grafik-Objekt
//STRIP001      {
//STRIP001          const SdrGrafObj*   pGrafObj = (const SdrGrafObj*) pObj;
//STRIP001          const GeoStat&      rGeo = pGrafObj->GetGeoStat();
//STRIP001          SdrGrafObjGeoData*  pGeoData = (SdrGrafObjGeoData*) pGrafObj->GetGeoData();
//STRIP001
//STRIP001          // Drehung rueckgaengig
//STRIP001          if ( rGeo.nDrehWink )
//STRIP001              RotatePoint( aRelPoint, rRect.TopLeft(), -rGeo.nSin, rGeo.nCos );
//STRIP001
//STRIP001          // Spiegelung rueckgaengig
//STRIP001          if ( pGeoData->bMirrored )
//STRIP001              aRelPoint.X() = rRect.Right() + rRect.Left() - aRelPoint.X();
//STRIP001
//STRIP001          // ggf. Unshear:
//STRIP001          if ( rGeo.nShearWink )
//STRIP001              ShearPoint( aRelPoint, rRect.TopLeft(), -rGeo.nTan );
//STRIP001
//STRIP001          if ( pGrafObj->GetGrafPrefMapMode().GetMapUnit() == MAP_PIXEL )
//STRIP001              aGraphSize = Application::GetDefaultDevice()->PixelToLogic( pGrafObj->GetGrafPrefSize(), aMap100 );
//STRIP001          else
//STRIP001              aGraphSize = OutputDevice::LogicToLogic( pGrafObj->GetGrafPrefSize(),
//STRIP001                                                       pGrafObj->GetGrafPrefMapMode(), aMap100 );
//STRIP001
//STRIP001          delete pGeoData;
//STRIP001          bObjSupported = TRUE;
//STRIP001      }
//STRIP001      else if ( pObj->ISA( SdrOle2Obj ) ) // OLE-Objekt
//STRIP001      {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001          SvInPlaceObjectRef aIPObjRef = ( (SdrOle2Obj*) pObj )->GetObjRef();
//STRIP001
//STRIP001          if ( aIPObjRef.Is() )
//STRIP001          {
//STRIP001              aGraphSize = aIPObjRef->GetVisArea().GetSize();
//STRIP001              bObjSupported = TRUE;
//STRIP001          }
//STRIP001 #endif // !SVX_LIGHT
//STRIP001      }
//STRIP001
//STRIP001      // hat alles geklappt, dann HitTest ausfuehren
//STRIP001      if ( bObjSupported )
//STRIP001      {
//STRIP001          // relativen Mauspunkt berechnen
//STRIP001          aRelPoint -= rRect.TopLeft();
//STRIP001          pIMapObj = rImageMap.GetHitIMapObject( aGraphSize, rRect.GetSize(), aRelPoint );
//STRIP001
//STRIP001          // Deaktivierte Objekte wollen wir nicht
//STRIP001          if ( pIMapObj && !pIMapObj->IsActive() )
//STRIP001              pIMapObj = NULL;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return pIMapObj;
//STRIP001 }


/*************************************************************************
|*
|*
|*
\************************************************************************/

//STRIP001 Graphic SdDrawDocument::GetGraphicFromOle2Obj( const SdrOle2Obj* pOle2Obj )
//STRIP001 {
//STRIP001  Graphic             aGraphic;
//STRIP001
//STRIP001 #ifndef SVX_LIGHT
//STRIP001  SvInPlaceObjectRef  aIPObjRef = pOle2Obj->GetObjRef();
//STRIP001
//STRIP001  if ( aIPObjRef.Is() )
//STRIP001  {
//STRIP001      VirtualDevice   aVDev;
//STRIP001      GDIMetaFile     aGDIMtf;
//STRIP001      const MapMode   aMap100( MAP_100TH_MM );
//STRIP001      const Size&     rSize = aIPObjRef->GetVisArea().GetSize();
//STRIP001
//STRIP001      aVDev.SetMapMode( aMap100 );
//STRIP001      aGDIMtf.Record( &aVDev );
//STRIP001
//STRIP001      aIPObjRef->DoDraw( &aVDev, Point(), rSize, JobSetup() );
//STRIP001
//STRIP001      aGDIMtf.Stop();
//STRIP001      aGDIMtf.WindStart();
//STRIP001      aGDIMtf.SetPrefMapMode( aMap100 );
//STRIP001      aGDIMtf.SetPrefSize( rSize );
//STRIP001      aGraphic = Graphic( aGDIMtf );
//STRIP001  }
//STRIP001 #endif // !SVX_LIGHT
//STRIP001
//STRIP001  return aGraphic;
//STRIP001 }


/*************************************************************************
|*
|* Liste fuer zu loeschende Praesentationobjekte (fuer die Seite herausgeben)
|*
\************************************************************************/

//STRIP001 List* SdDrawDocument::GetDeletedPresObjList()
//STRIP001 {
//STRIP001  if (!pDeletedPresObjList)
//STRIP001  {
//STRIP001      pDeletedPresObjList = new List();
//STRIP001  }
//STRIP001
//STRIP001  return pDeletedPresObjList;
//STRIP001 }

/** this method enforces that the masterpages are in the currect order,
    that is at position 1 is a PK_STANDARD masterpage followed by a
    PK_NOTES masterpage and so on. #
*/
/*N*/ void SdDrawDocument::CheckMasterPages()
/*N*/ {
/*N*/ //    RemoveMasterPage(2); // code to test the creation of notes pages
/*N*/
/*N*/   USHORT nMaxPages = GetMasterPageCount();
/*N*/
/*N*/   // we need at least a handout master and one master page
/*N*/   if( nMaxPages < 2 )
/*N*/   {
/*N*/       return;
/*N*/   }
/*N*/
/*N*/   SdPage* pPage = NULL;
/*N*/   SdPage* pNotesPage = NULL;
/*N*/
/*N*/   USHORT nPage;
/*N*/
/*N*/   // first see if the page order is correct
/*N*/   for( nPage = 1; nPage < nMaxPages; nPage++ )
/*N*/   {
/*N*/       pPage = static_cast<SdPage*> (GetMasterPage( nPage ));
/*N*/       // if an odd page is not a standard page or an even page is not a notes page
/*N*/       if( ((1 == (nPage & 1)) && (pPage->GetPageKind() != PK_STANDARD) ) ||
/*N*/           ((0 == (nPage & 1)) && (pPage->GetPageKind() != PK_NOTES) ) )
/*N*/           break; // then we have a fatal error
/*N*/   }
/*N*/
/*N*/   if( nPage < nMaxPages )
/*N*/   {
/*N*/       // there is a fatal error in the master page order,
/*N*/       // we need to repair the document
/*N*/       sal_Bool bChanged = sal_False;
/*N*/
/*N*/       nPage = 1;
/*N*/       while( nPage < nMaxPages )
/*N*/       {
/*N*/           pPage = static_cast<SdPage*> (GetMasterPage( nPage ));
/*N*/           if( pPage->GetPageKind() != PK_STANDARD )
/*N*/           {
/*N*/               bChanged = sal_True;
/*N*/               USHORT nFound = nPage + 1;
/*N*/               while( nFound < nMaxPages )
/*N*/               {
/*N*/                   pPage = static_cast<SdPage*>(GetMasterPage( nFound ));
/*N*/                   if( PK_STANDARD == pPage->GetPageKind() )
/*N*/                   {
/*N*/                       MoveMasterPage( nFound, nPage );
/*N*/                       pPage->SetInserted(sal_True);
/*N*/                       break;
/*N*/
/*N*/                   }
/*N*/
/*N*/                   nFound++;
/*N*/               }
/*N*/
/*N*/               // if we don't have any more standard pages, were done
/*N*/               if( nMaxPages == nFound )
/*N*/                   break;
/*N*/           }
/*N*/
/*N*/           nPage++;
/*N*/
/*N*/           if( nPage < nMaxPages )
/*N*/               pNotesPage = static_cast<SdPage*>(GetMasterPage( nPage ));
/*N*/           else
/*N*/               pNotesPage = NULL;
/*N*/
/*N*/           if( (NULL == pNotesPage) || (pNotesPage->GetPageKind() != PK_NOTES) || ( pPage->GetLayoutName() != pNotesPage->GetLayoutName() ) )
/*N*/           {
/*N*/               bChanged = sal_True;
/*N*/
/*N*/               USHORT nFound = nPage + 1;
/*N*/               while( nFound < nMaxPages )
/*N*/               {
/*N*/                   pNotesPage = static_cast<SdPage*>(GetMasterPage( nFound ));
/*N*/                   if( (PK_NOTES == pNotesPage->GetPageKind()) && ( pPage->GetLayoutName() == pNotesPage->GetLayoutName() ) )
/*N*/                   {
/*N*/                       MoveMasterPage( nFound, nPage );
/*N*/                       pNotesPage->SetInserted(sal_True);
/*N*/                       break;
/*N*/                   }
/*N*/
/*N*/                   nFound++;
/*N*/               }
/*N*/
/*N*/               // looks like we lost a notes page
/*N*/               if( nMaxPages == nFound )
/*N*/               {
/*N*/                   // so create one
/*N*/
/*N*/                   // first find a reference notes page for size
/*N*/                   SdPage* pRefNotesPage = NULL;
/*N*/                   nFound = 0;
/*N*/                   while( nFound < nMaxPages )
/*N*/                   {
/*N*/                       pRefNotesPage = static_cast<SdPage*>(GetMasterPage( nFound ));
/*N*/                       if( PK_NOTES == pRefNotesPage->GetPageKind() )
/*N*/                           break;
/*N*/                       nFound++;
/*N*/                   }
/*N*/                   if( nFound == nMaxPages )
/*N*/                       pRefNotesPage = NULL;
/*N*/
/*N*/                   SdPage* pNotesPage = static_cast<SdPage*>(AllocPage(sal_True));
/*N*/                   pNotesPage->SetPageKind(PK_NOTES);
/*N*/                   if( pRefNotesPage )
/*N*/                   {
/*N*/                       pNotesPage->SetSize( pRefNotesPage->GetSize() );
/*N*/                       pNotesPage->SetBorder( pRefNotesPage->GetLftBorder(),
/*N*/                                               pRefNotesPage->GetUppBorder(),
/*N*/                                               pRefNotesPage->GetRgtBorder(),
/*N*/                                               pRefNotesPage->GetLwrBorder() );
/*N*/                   }
/*N*/                   InsertMasterPage(pNotesPage,  nPage );
/*N*/                   pNotesPage->SetLayoutName( pPage->GetLayoutName() );
/*N*/                   pNotesPage->SetAutoLayout(AUTOLAYOUT_NOTES, sal_True, sal_True);
/*N*/                   nMaxPages++;
/*N*/               }
/*N*/           }
/*N*/
/*N*/           nPage++;
/*N*/       }
/*N*/
/*N*/       // now remove all remaining and unused non PK_STANDARD slides
/*N*/       while( nPage < nMaxPages )
/*N*/       {
/*N*/           bChanged = sal_True;
/*N*/
/*N*/           RemoveMasterPage( nPage );
/*N*/           nMaxPages--;
/*N*/       }
/*N*/
/*N*/       if( bChanged )
/*N*/       {
/*N*/           DBG_ERROR( "master pages where in a wrong order" );
/*N*/           RecalcPageNums( sal_True);
/*N*/       }
/*N*/   }
/*N*/ }




//STRIP001 USHORT SdDrawDocument::CreatePage (USHORT nPageNum)
//STRIP001 {
//STRIP001     PageKind ePageKind = PK_STANDARD;
//STRIP001
//STRIP001     // Get current page.
//STRIP001     SdPage* pActualPage = GetSdPage(nPageNum, ePageKind);
//STRIP001
//STRIP001     // Get background flags.
//STRIP001     SdrLayerAdmin& rLayerAdmin = GetLayerAdmin();
//STRIP001     BYTE aBckgrnd = rLayerAdmin.GetLayerID(String(SdResId(STR_LAYER_BCKGRND)), FALSE);
//STRIP001     BYTE aBckgrndObj = rLayerAdmin.GetLayerID(String(SdResId(STR_LAYER_BCKGRNDOBJ)), FALSE);
//STRIP001     SetOfByte aVisibleLayers = pActualPage->GetMasterPageVisibleLayers(0);
//STRIP001
//STRIP001     // Get layout from current page.
//STRIP001     AutoLayout eAutoLayout = pActualPage->GetAutoLayout();
//STRIP001
//STRIP001     return CreatePage (
//STRIP001         pActualPage, ePageKind,
//STRIP001         // No names for the new slides.
//STRIP001         String(), String(),
//STRIP001         eAutoLayout, eAutoLayout,
//STRIP001         aVisibleLayers.IsSet(aBckgrnd),
//STRIP001         aVisibleLayers.IsSet(aBckgrndObj));
//STRIP001 }




//STRIP001 USHORT SdDrawDocument::CreatePage (
//STRIP001     SdPage* pActualPage,
//STRIP001     PageKind ePageKind,
//STRIP001     const String& sStandardPageName,
//STRIP001     const String& sNotesPageName,
//STRIP001     AutoLayout eStandardLayout,
//STRIP001     AutoLayout eNotesLayout,
//STRIP001     BOOL bIsPageBack,
//STRIP001     BOOL bIsPageObj)
//STRIP001 {
//STRIP001     SdPage* pPreviousStandardPage;
//STRIP001     SdPage* pPreviousNotesPage;
//STRIP001     SdPage* pStandardPage;
//STRIP001     SdPage* pNotesPage;
//STRIP001     USHORT nPgNum;
//STRIP001
//STRIP001     // From the given page determine the standard page and notes page of which
//STRIP001     // to take the layout and the position where to insert the new pages.
//STRIP001     if (ePageKind == PK_NOTES)
//STRIP001     {
//STRIP001         pPreviousNotesPage = pActualPage;
//STRIP001         USHORT nNotesPageNum = pPreviousNotesPage->GetPageNum() + 2;
//STRIP001         pPreviousStandardPage = (SdPage*) GetPage(nNotesPageNum - 3);
//STRIP001         eStandardLayout = pPreviousStandardPage->GetAutoLayout();
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         pPreviousStandardPage = pActualPage;
//STRIP001         USHORT nStandardPageNum = pPreviousStandardPage->GetPageNum() + 2;
//STRIP001         pPreviousNotesPage = (SdPage*) GetPage(nStandardPageNum - 1);
//STRIP001         eNotesLayout = pPreviousNotesPage->GetAutoLayout();
//STRIP001     }
//STRIP001
//STRIP001     // Create new standard page and set it up.
//STRIP001     pStandardPage = (SdPage*) AllocPage(FALSE);
//STRIP001
//STRIP001  // #108658#
//STRIP001  // Set the size here since else the presobj autolayout
//STRIP001  // will be wrong.
//STRIP001  pStandardPage->SetSize( pPreviousStandardPage->GetSize() );
//STRIP001  pStandardPage->SetBorder( pPreviousStandardPage->GetLftBorder(),
//STRIP001                            pPreviousStandardPage->GetUppBorder(),
//STRIP001                            pPreviousStandardPage->GetRgtBorder(),
//STRIP001                            pPreviousStandardPage->GetLwrBorder() );
//STRIP001
//STRIP001     // Use master page of current page.
//STRIP001     nPgNum = pPreviousStandardPage->GetMasterPageNum(0);
//STRIP001     pStandardPage->InsertMasterPage(nPgNum);
//STRIP001     // User layout of current standard page.
//STRIP001     pStandardPage->SetLayoutName( pPreviousStandardPage->GetLayoutName() );
//STRIP001     pStandardPage->SetAutoLayout(eStandardLayout, TRUE);
//STRIP001
//STRIP001     // Create new notes page and set it up.
//STRIP001     pNotesPage = (SdPage*) AllocPage(FALSE);
//STRIP001  pNotesPage->SetPageKind(PK_NOTES);
//STRIP001     // Use master page of current page.
//STRIP001     nPgNum = pPreviousNotesPage->GetMasterPageNum(0);
//STRIP001     pNotesPage->InsertMasterPage(nPgNum);
//STRIP001     // Use layout of current notes page.
//STRIP001     pNotesPage->SetLayoutName( pPreviousNotesPage->GetLayoutName() );
//STRIP001     pNotesPage->SetAutoLayout(eNotesLayout, TRUE);
//STRIP001
//STRIP001     return InsertPageSet (
//STRIP001         pActualPage, ePageKind,
//STRIP001         sStandardPageName,
//STRIP001         sNotesPageName,
//STRIP001         eStandardLayout,
//STRIP001         eNotesLayout,
//STRIP001         bIsPageBack,
//STRIP001         bIsPageObj,
//STRIP001
//STRIP001         pStandardPage,
//STRIP001         pNotesPage);
//STRIP001 }




//STRIP001 USHORT SdDrawDocument::DuplicatePage (USHORT nPageNum)
//STRIP001 {
//STRIP001     PageKind ePageKind = PK_STANDARD;
//STRIP001
//STRIP001     // Get current page.
//STRIP001     SdPage* pActualPage = GetSdPage(nPageNum, ePageKind);
//STRIP001
//STRIP001     // Get background flags.
//STRIP001     SdrLayerAdmin& rLayerAdmin = GetLayerAdmin();
//STRIP001     BYTE aBckgrnd = rLayerAdmin.GetLayerID(String(SdResId(STR_LAYER_BCKGRND)), FALSE);
//STRIP001     BYTE aBckgrndObj = rLayerAdmin.GetLayerID(String(SdResId(STR_LAYER_BCKGRNDOBJ)), FALSE);
//STRIP001     SetOfByte aVisibleLayers = pActualPage->GetMasterPageVisibleLayers(0);
//STRIP001
//STRIP001     // Get layout from current page.
//STRIP001     AutoLayout eAutoLayout = pActualPage->GetAutoLayout();
//STRIP001
//STRIP001     return DuplicatePage (
//STRIP001         pActualPage, ePageKind,
//STRIP001         // No names for the new slides.
//STRIP001         String(), String(),
//STRIP001         eAutoLayout, eAutoLayout,
//STRIP001         aVisibleLayers.IsSet(aBckgrnd),
//STRIP001         aVisibleLayers.IsSet(aBckgrndObj));
//STRIP001 }




//STRIP001 USHORT SdDrawDocument::DuplicatePage (
//STRIP001     SdPage* pActualPage,
//STRIP001     PageKind ePageKind,
//STRIP001     const String& sStandardPageName,
//STRIP001     const String& sNotesPageName,
//STRIP001     AutoLayout eStandardLayout,
//STRIP001     AutoLayout eNotesLayout,
//STRIP001     BOOL bIsPageBack,
//STRIP001     BOOL bIsPageObj)
//STRIP001 {
//STRIP001     SdPage* pPreviousStandardPage;
//STRIP001     SdPage* pPreviousNotesPage;
//STRIP001     SdPage* pStandardPage;
//STRIP001     SdPage* pNotesPage;
//STRIP001
//STRIP001     // From the given page determine the standard page and the notes page
//STRIP001     // of which to make copies.
//STRIP001     if (ePageKind == PK_NOTES)
//STRIP001     {
//STRIP001         pPreviousNotesPage = pActualPage;
//STRIP001         USHORT nNotesPageNum = pPreviousNotesPage->GetPageNum() + 2;
//STRIP001         pPreviousStandardPage = (SdPage*) GetPage(nNotesPageNum - 3);
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         pPreviousStandardPage = pActualPage;
//STRIP001         USHORT nStandardPageNum = pPreviousStandardPage->GetPageNum() + 2;
//STRIP001         pPreviousNotesPage = (SdPage*) GetPage(nStandardPageNum - 1);
//STRIP001     }
//STRIP001
//STRIP001     // Create duplicates of a standard page and the associated notes page.
//STRIP001     pStandardPage = (SdPage*) pPreviousStandardPage->Clone();
//STRIP001     pNotesPage = (SdPage*) pPreviousNotesPage->Clone();
//STRIP001
//STRIP001     return InsertPageSet (
//STRIP001         pActualPage, ePageKind,
//STRIP001         sStandardPageName,
//STRIP001         sNotesPageName,
//STRIP001         eStandardLayout,
//STRIP001         eNotesLayout,
//STRIP001         bIsPageBack,
//STRIP001         bIsPageObj,
//STRIP001
//STRIP001         pStandardPage,
//STRIP001         pNotesPage);
//STRIP001 }




//STRIP001 USHORT SdDrawDocument::InsertPageSet (
//STRIP001     SdPage* pActualPage,
//STRIP001     PageKind ePageKind,
//STRIP001     const String& sStandardPageName,
//STRIP001     const String& sNotesPageName,
//STRIP001     AutoLayout eStandardLayout,
//STRIP001     AutoLayout eNotesLayout,
//STRIP001     BOOL bIsPageBack,
//STRIP001     BOOL bIsPageObj,
//STRIP001
//STRIP001     SdPage* pStandardPage,
//STRIP001     SdPage* pNotesPage)
//STRIP001 {
//STRIP001     SdPage* pPreviousStandardPage;
//STRIP001     SdPage* pPreviousNotesPage;
//STRIP001     USHORT nStandardPageNum;
//STRIP001     USHORT nNotesPageNum;
//STRIP001     String aStandardPageName = sStandardPageName;
//STRIP001     String aNotesPageName = sNotesPageName;
//STRIP001
//STRIP001     // Gather some information about the standard page and the notes page
//STRIP001     // that are to be inserted.  This makes sure that there is allways one
//STRIP001     // standard page followed by one notes page.
//STRIP001     if (ePageKind == PK_NOTES)
//STRIP001     {
//STRIP001         pPreviousNotesPage = pActualPage;
//STRIP001         nNotesPageNum = pPreviousNotesPage->GetPageNum() + 2;
//STRIP001         pPreviousStandardPage = (SdPage*) GetPage(nNotesPageNum - 3);
//STRIP001         nStandardPageNum = nNotesPageNum - 1;
//STRIP001         eStandardLayout = pPreviousStandardPage->GetAutoLayout();
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         pPreviousStandardPage = pActualPage;
//STRIP001         nStandardPageNum = pPreviousStandardPage->GetPageNum() + 2;
//STRIP001         pPreviousNotesPage = (SdPage*) GetPage(nStandardPageNum - 1);
//STRIP001         nNotesPageNum = nStandardPageNum + 1;
//STRIP001         aNotesPageName = aStandardPageName;
//STRIP001         eNotesLayout = pPreviousNotesPage->GetAutoLayout();
//STRIP001     }
//STRIP001
//STRIP001
//STRIP001     // Set up and insert the standard page.
//STRIP001     SetupNewPage (
//STRIP001         pPreviousStandardPage,
//STRIP001         pStandardPage,
//STRIP001         aStandardPageName,
//STRIP001         nStandardPageNum,
//STRIP001         bIsPageBack,
//STRIP001         bIsPageObj);
//STRIP001
//STRIP001     // Set up and insert the notes page.
//STRIP001     pNotesPage->SetPageKind(PK_NOTES);
//STRIP001     SetupNewPage (
//STRIP001         pPreviousNotesPage,
//STRIP001         pNotesPage,
//STRIP001         aNotesPageName,
//STRIP001         nNotesPageNum,
//STRIP001         bIsPageBack,
//STRIP001         bIsPageObj);
//STRIP001
//STRIP001     // Return an index that allows the caller to access the newly inserted
//STRIP001     // pages by using GetSdPage().
//STRIP001     return pStandardPage->GetPageNum() / 2;
//STRIP001 }




//STRIP001 void SdDrawDocument::SetupNewPage (
//STRIP001     SdPage* pPreviousPage,
//STRIP001     SdPage* pPage,
//STRIP001     const String& sPageName,
//STRIP001     USHORT nInsertionPoint,
//STRIP001     BOOL bIsPageBack,
//STRIP001     BOOL bIsPageObj)
//STRIP001 {
//STRIP001     if (pPreviousPage != NULL)
//STRIP001     {
//STRIP001         pPage->SetSize( pPreviousPage->GetSize() );
//STRIP001         pPage->SetBorder( pPreviousPage->GetLftBorder(),
//STRIP001             pPreviousPage->GetUppBorder(),
//STRIP001             pPreviousPage->GetRgtBorder(),
//STRIP001             pPreviousPage->GetLwrBorder() );
//STRIP001     }
//STRIP001     pPage->SetName(sPageName);
//STRIP001
//STRIP001     InsertPage(pPage, nInsertionPoint);
//STRIP001
//STRIP001     if (pPreviousPage != NULL)
//STRIP001     {
//STRIP001         SdrLayerAdmin& rLayerAdmin = GetLayerAdmin();
//STRIP001         BYTE aBckgrnd = rLayerAdmin.GetLayerID(String(SdResId(STR_LAYER_BCKGRND)), FALSE);
//STRIP001         BYTE aBckgrndObj = rLayerAdmin.GetLayerID(String(SdResId(STR_LAYER_BCKGRNDOBJ)), FALSE);
//STRIP001         SetOfByte aVisibleLayers = pPreviousPage->GetMasterPageVisibleLayers(0);
//STRIP001         aVisibleLayers.Set(aBckgrnd, bIsPageBack);
//STRIP001         aVisibleLayers.Set(aBckgrndObj, bIsPageObj);
//STRIP001         pPage->SetMasterPageVisibleLayers(aVisibleLayers, 0);
//STRIP001     }
//STRIP001 }
