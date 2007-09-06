/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sd_drawdoc2.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:20:20 $
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

#ifdef _MSC_VER
#pragma hdrstop
#endif


#ifndef SVX_LIGHT
#ifndef _SFX_PRINTER_HXX
#include <bf_sfx2/printer.hxx>
#endif
#include "sdoutl.hxx"
#else   // SVX_LIGHT
#define SfxPrinter Printer
#endif // !SVX_LIGHT

#ifndef _SVX_PAPERINF_HXX
#include <bf_svx/paperinf.hxx>
#endif
#ifndef _SVDOPAGE_HXX //autogen
#include <bf_svx/svdopage.hxx>
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


#include <bf_svx/dialogs.hrc>




#include "sdresid.hxx"
#include "drawdoc.hxx"
#include "sdpage.hxx"
#include "glob.hrc"
#include "cusshow.hxx"

#ifndef SVX_LIGHT
#ifdef MAC
#include "::ui:inc:strings.hrc"
#else
#ifdef UNX
#include "../ui/inc/docshell.hxx"
#include "../ui/inc/frmview.hxx"
#include "../ui/inc/strings.hrc"
#else
#include "..\ui\inc\docshell.hxx"
#include "..\ui\inc\strings.hrc"
#endif
#endif

namespace binfilter {

#endif // !SVX_LIGHT

/*N*/ const long PRINT_OFFSET = 30;     // siehe \svx\source\dialog\page.cxx (PB)


/*************************************************************************
|*
|* Sucht ein Objekt per Name
|*
\************************************************************************/



/*************************************************************************
|*
|* Sucht die SdPage per Name
|*
\************************************************************************/

USHORT SdDrawDocument::GetPageByName(const String& rPgName, BOOL& rbIsMasterPage) const
{
/*?*/ {DBG_BF_ASSERT(0, "STRIP");} return 0;//STRIP001  SdPage* pPage = NULL;
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




/*************************************************************************
|*
|* anfallenden Undo-Aktionen des SdrModels verwalten
|*
\************************************************************************/

// #107844#
// Inline has no advantages at such big code.
IMPL_LINK( SdDrawDocument, NotifyUndoActionHdl, SfxUndoAction *, pUndoAction )
{
        DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //STRIP001 #ifndef SVX_LIGHT
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


/*************************************************************************
|*
|* - selektierte Seiten hinter genannte Seite schieben
|*   (nTargetPage = (USHORT)-1  --> vor erste Seite schieben)
|* - ergibt TRUE, wenn Seiten verschoben wurden
|*
\************************************************************************/



/*************************************************************************
|*
|* Anzahl der Links im LinkManager zurueckgeben
|*
\************************************************************************/


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



/*************************************************************************
|*
|*
|*
\************************************************************************/



/*************************************************************************
|*
|* Liste fuer zu loeschende Praesentationobjekte (fuer die Seite herausgeben)
|*
\************************************************************************/


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
























}
