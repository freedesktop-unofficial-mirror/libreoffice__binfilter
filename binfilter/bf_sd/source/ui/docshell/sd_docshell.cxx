/*************************************************************************
 *
 *  $RCSfile: sd_docshell.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 13:44:21 $
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

#define ITEMID_FONTLIST                 SID_ATTR_CHAR_FONTLIST
#define ITEMID_COLOR_TABLE              SID_COLOR_TABLE
#define ITEMID_GRADIENT_LIST            SID_GRADIENT_LIST
#define ITEMID_HATCH_LIST               SID_HATCH_LIST
#define ITEMID_BITMAP_LIST              SID_BITMAP_LIST
#define ITEMID_DASH_LIST                SID_DASH_LIST
#define ITEMID_LINEEND_LIST             SID_LINEEND_LIST
#define ITEMID_SEARCH                   SID_SEARCH_ITEM

// auto strip #ifndef _PSTM_HXX
// auto strip #include <tools/pstm.hxx>
// auto strip #endif
// auto strip #ifndef _SV_SVAPP_HXX
// auto strip #include <vcl/svapp.hxx>
// auto strip #endif

// auto strip #include <bf_sfx2/docfac.hxx>

#ifndef _SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif
// auto strip #ifndef _SVX_SRCHITEM_HXX
// auto strip #include <bf_svx/srchitem.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_SRCHDLG_HXX
// auto strip #include <bf_svx/srchdlg.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_SVXIFACT_HXX
// auto strip #include <bf_svx/svxifact.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_FLSTITEM_HXX
// auto strip #include <bf_svx/flstitem.hxx>
// auto strip #endif
// auto strip #ifndef _SFXENUMITEM_HXX
// auto strip #include <svtools/eitem.hxx>
// auto strip #endif
#ifndef _SFXINTITEM_HXX
#include <svtools/intitem.hxx>
#endif
#ifndef _SFX_PRINTER_HXX //autogen
#include <bf_sfx2/printer.hxx>
#endif
// auto strip #ifndef _SFX_DOCFILE_HXX //autogen
// auto strip #include <bf_sfx2/docfile.hxx>
// auto strip #endif
// auto strip #ifndef _B3D_BASE3D_HXX
// auto strip #include "goodies/base3d.hxx"
// auto strip #endif
// auto strip #ifndef _SVX_DRAWITEM_HXX //autogen
// auto strip #include <bf_svx/drawitem.hxx>
// auto strip #endif
#ifndef _SVX_FLSTITEM_HXX //autogen
#include <bf_svx/flstitem.hxx>
#endif
#ifndef _SVX_DRAWITEM_HXX //autogen
#include <bf_svx/drawitem.hxx>
#endif
#ifndef _SFXDISPATCH_HXX //autogen
#include <bf_sfx2/dispatch.hxx>
#endif
// auto strip #ifndef _SFX_WHITER_HXX //autogen
// auto strip #include <svtools/whiter.hxx>
// auto strip #endif
// auto strip #ifndef _SFXITEMPOOL_HXX //autogen
// auto strip #include <svtools/itempool.hxx>
// auto strip #endif
#ifndef _CTRLTOOL_HXX //autogen
#include <svtools/ctrltool.hxx>
#endif
#ifndef _FILTER_HXX //autogen
#include <svtools/filter.hxx>
#endif
#ifndef _SO_CLSIDS_HXX
#include <so3/clsids.hxx>
#endif
// auto strip #ifndef _SFX_TOPFRM_HXX
// auto strip #include <bf_sfx2/topfrm.hxx>
// auto strip #endif

#include "app.hrc"
// auto strip #include "app.hxx"
#include "strmname.h"
// auto strip #include "stlpool.hxx"
#include "strings.hrc"
#include "docshell.hxx"
// auto strip #include "sdview.hxx"
#include "drawdoc.hxx"
// auto strip #include "sdpage.hxx"
#include "glob.hrc"
#include "res_bmp.hrc"
// auto strip #include "fupoor.hxx"
// auto strip #include "fusearch.hxx"
#include "viewshel.hxx"
#include "sdresid.hxx"
#include "fuslshow.hxx"
//STRIP001 #include "preview.hxx"
// auto strip #include "drawview.hxx"
#include "frmview.hxx"
#include "unomodel.hxx"

#define POOL_BUFFER_SIZE                (USHORT)32768
#define BASIC_BUFFER_SIZE               (USHORT)8192
#define DOCUMENT_BUFFER_SIZE            (USHORT)32768

namespace binfilter {
GraphicFilter* GetGrfFilter();

SfxProgress* SdDrawDocShell::mpSpecialProgress = NULL;
Link*        SdDrawDocShell::mpSpecialProgressHdl = NULL;

/*************************************************************************
|*
|* SFX-Slotmaps und -Definitionen
|*
\************************************************************************/
/*N*/ TYPEINIT1( SdDrawDocShell, SfxObjectShell );
}//namespace binfilter


namespace binfilter {
#define SdDrawDocShell
#include "sdslots.hxx"

/*N*/ SFX_IMPL_INTERFACE(SdDrawDocShell, SfxObjectShell, SdResId(0))
/*N*/ {
/*N*/   SFX_CHILDWINDOW_REGISTRATION(SID_SEARCH_DLG);
/*N*/ }

/*N*/ SFX_IMPL_OBJECTFACTORY_LOD(SdDrawDocShell, simpress,
/*N*/                          SvGlobalName(BF_SO3_SIMPRESS_CLASSID), Sd)

/*************************************************************************
|*
|* Construct
|*
\************************************************************************/

/*N*/ void SdDrawDocShell::Construct()
/*N*/ {
/*N*/   bInDestruction = FALSE;
/*N*/   SetSlotFilter();     // setzt Filter zurueck
/*N*/   SetShell(this);
/*N*/
/*N*/   pDoc = new SdDrawDocument(eDocType, this);
/*N*/   SetModel( new SdXImpressDocument( this ) );
/*N*/   SetPool( &pDoc->GetItemPool() );
/*N*/   pUndoManager = new SfxUndoManager;
/*N*/   UpdateTablePointers();
/*N*/   SetStyleFamily(5);       //CL: eigentlich SFX_STYLE_FAMILY_PSEUDO
/*N*/ }

/*************************************************************************
|*
|* Konstruktor 1
|*
\************************************************************************/

/*N*/ SdDrawDocShell::SdDrawDocShell(SfxObjectCreateMode eMode,
/*N*/                              BOOL bDataObject,
/*N*/                              DocumentType eDocumentType) :
/*N*/   SfxObjectShell(eMode),
/*N*/   pPrinter(NULL),
/*N*/   pViewShell(NULL),
/*N*/   pDoc(NULL),
/*N*/   pUndoManager(NULL),
/*N*/   pFontList(NULL),
/*N*/   pFuActual(NULL),
/*N*/   bUIActive(FALSE),
/*N*/   pProgress(NULL),
/*N*/ //    pStbMgr( NULL ),
/*N*/   bSdDataObj(bDataObject),
/*N*/   bOwnPrinter(FALSE),
/*N*/   eDocType(eDocumentType),
/*N*/     mbNewDocument( sal_True )
/*N*/ {
/*N*/ //    pDoc = new SdDrawDocument(eDocType, this);
/*N*/   Construct();
/*N*/ }

/*************************************************************************
|*
|* Konstruktor 2
|*
\************************************************************************/

SdDrawDocShell::SdDrawDocShell(SdDrawDocument* pDoc, SfxObjectCreateMode eMode,
                               BOOL bDataObject,
                               DocumentType eDocumentType) :
    SfxObjectShell(eMode),
    pPrinter(NULL),
    pViewShell(NULL),
    pDoc(pDoc),
    pUndoManager(NULL),
    pFontList(NULL),
    pFuActual(NULL),
    bUIActive(FALSE),
    pProgress(NULL),
//  pStbMgr( NULL ),
    bSdDataObj(bDataObject),
    bOwnPrinter(FALSE),
    eDocType(eDocumentType),
    mbNewDocument( sal_True )
{
    Construct();
}

/*************************************************************************
|*
|* Destruktor
|*
\************************************************************************/

/*N*/ SdDrawDocShell::~SdDrawDocShell()
/*N*/ {
/*N*/   bInDestruction = TRUE;
/*N*/   delete pFuActual;
/*N*/   pFuActual = NULL;
/*N*/
/*N*/   delete pFontList;
/*N*/   delete pUndoManager;
/*N*/
/*N*/   if (bOwnPrinter)
/*N*/       delete pPrinter;
/*N*/
/*N*/   delete pDoc;
/*N*/
/*N*/   // damit der Navigator das Verschwinden des Dokuments mitbekommt
/*N*/   SfxBoolItem     aItem(SID_NAVIGATOR_INIT, TRUE);
/*N*/   SfxViewFrame*   pFrame = pViewShell ? pViewShell->GetFrame() : GetFrame();
/*N*/
/*N*/   if( !pFrame )
/*N*/       pFrame = SfxViewFrame::GetFirst( this );
/*N*/
/*N*/   if( pFrame )
/*?*/       pFrame->GetDispatcher()->Execute(
/*?*/           SID_NAVIGATOR_INIT, SFX_CALLMODE_ASYNCHRON | SFX_CALLMODE_RECORD, &aItem, 0L);
/*N*/ }

/*************************************************************************
|*
|* Slot-Stati setzen
|*
\************************************************************************/

//STRIP001 void SdDrawDocShell::GetState(SfxItemSet &rSet)
//STRIP001 {
//STRIP001
//STRIP001  SfxWhichIter aIter( rSet );
//STRIP001  USHORT nWhich = aIter.FirstWhich();
//STRIP001
//STRIP001  while ( nWhich )
//STRIP001  {
//STRIP001      USHORT nSlotId = SfxItemPool::IsWhich(nWhich)
//STRIP001          ? GetPool().GetSlotId(nWhich)
//STRIP001          : nWhich;
//STRIP001
//STRIP001      switch ( nSlotId )
//STRIP001      {
//STRIP001          case SID_SEARCH_ITEM:
//STRIP001          {
//STRIP001              rSet.Put( *SD_MOD()->GetSearchItem() );
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001          case SID_CLOSEDOC:
//STRIP001          {
//STRIP001              BOOL bDisabled = FALSE;
//STRIP001
//STRIP001              if (pViewShell && pViewShell->GetSlideShow() &&
//STRIP001                  pViewShell->GetSlideShow()->IsInputLocked())
//STRIP001              {
//STRIP001                  // Es laeuft ein Effekt in der SlideShow
//STRIP001                  bDisabled = TRUE;
//STRIP001              }
//STRIP001              else if (pViewShell && pViewShell->GetView() && pViewShell->GetView()->ISA(SdDrawView) &&
//STRIP001                       ((SdDrawView*) pViewShell->GetView())->GetSlideShow() &&
//STRIP001                       ((SdDrawView*) pViewShell->GetView())->GetSlideShow()->IsInputLocked())
//STRIP001              {
//STRIP001                  // Es laeuft ein Effekt auf dem Zeichentisch
//STRIP001                  bDisabled = TRUE;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  SfxViewFrame* pFrame = pViewShell ? pViewShell->GetFrame() : GetFrame();
//STRIP001
//STRIP001                  if( !pFrame )
//STRIP001                      pFrame = SfxViewFrame::GetFirst( this );
//STRIP001                  DBG_ASSERT( pFrame, "kein ViewFrame" );
//STRIP001
//STRIP001                  SfxChildWindow* pPreviewChildWindow = pFrame->GetChildWindow(SdPreviewChildWindow::GetChildWindowId());
//STRIP001                  SdPreviewWin*   pPreviewWin = (SdPreviewWin*) ( pPreviewChildWindow ? pPreviewChildWindow->GetWindow() : NULL );
//STRIP001                  FuSlideShow*    pShow = pPreviewWin ? pPreviewWin->GetSlideShow() : NULL;
//STRIP001
//STRIP001                  if (pShow && pShow->IsInputLocked())
//STRIP001                  {
//STRIP001                      // Es laeuft ein Effekt in der Preview
//STRIP001                      bDisabled = TRUE;
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              if (bDisabled)
//STRIP001              {
//STRIP001                  rSet.DisableItem(SID_CLOSEDOC);
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  GetSlotState(SID_CLOSEDOC, SfxObjectShell::GetInterface(), &rSet);
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001          case SID_SEARCH_OPTIONS:
//STRIP001          {
//STRIP001              UINT16 nOpt = SEARCH_OPTIONS_SEARCH      |
//STRIP001                            SEARCH_OPTIONS_WHOLE_WORDS |
//STRIP001                            SEARCH_OPTIONS_BACKWARDS   |
//STRIP001                            SEARCH_OPTIONS_REG_EXP     |
//STRIP001                            SEARCH_OPTIONS_EXACT       |
//STRIP001                            SEARCH_OPTIONS_SIMILARITY  |
//STRIP001                            SEARCH_OPTIONS_SELECTION;
//STRIP001
//STRIP001              if (!IsReadOnly())
//STRIP001              {
//STRIP001                  nOpt |= SEARCH_OPTIONS_REPLACE;
//STRIP001                  nOpt |= SEARCH_OPTIONS_REPLACE_ALL;
//STRIP001              }
//STRIP001
//STRIP001              rSet.Put(SfxUInt16Item(nWhich, nOpt));
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001          case SID_VERSION:
//STRIP001          {
//STRIP001              GetSlotState( SID_VERSION, SfxObjectShell::GetInterface(), &rSet );
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001          default:
//STRIP001          break;
//STRIP001      }
//STRIP001      nWhich = aIter.NextWhich();
//STRIP001  }
//STRIP001
//STRIP001  SfxViewFrame* pFrame = SFX_APP()->GetViewFrame();
//STRIP001
//STRIP001  if (pFrame)
//STRIP001  {
//STRIP001      if (rSet.GetItemState(SID_RELOAD) != SFX_ITEM_UNKNOWN)
//STRIP001      {
//STRIP001          pFrame->GetSlotState(SID_RELOAD,
//STRIP001                               pFrame->GetInterface(), &rSet);
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SdDrawDocShell::InPlaceActivate( BOOL bActive )
//STRIP001 {
//STRIP001  if( !bActive )
//STRIP001  {
//STRIP001      FrameView* pFrameView = NULL;
//STRIP001      List* pFrameViewList = pDoc->GetFrameViewList();
//STRIP001
//STRIP001      DBG_ASSERT( pFrameViewList, "No FrameViewList?" );
//STRIP001      if( pFrameViewList )
//STRIP001      {
//STRIP001          sal_uInt32 i;
//STRIP001          for ( i = 0; i < pFrameViewList->Count(); i++)
//STRIP001          {
//STRIP001              // Ggf. FrameViews loeschen
//STRIP001              pFrameView = (FrameView*) pFrameViewList->GetObject(i);
//STRIP001
//STRIP001              if (pFrameView)
//STRIP001                  delete pFrameView;
//STRIP001          }
//STRIP001
//STRIP001          pFrameViewList->Clear();
//STRIP001
//STRIP001          SdViewShell* pViewSh = NULL;
//STRIP001          SfxViewShell* pSfxViewSh = NULL;
//STRIP001          SfxViewFrame* pSfxViewFrame = SfxViewFrame::GetFirst(this, 0, false);
//STRIP001
//STRIP001          while (pSfxViewFrame)
//STRIP001          {
//STRIP001              // Anzahl FrameViews ermitteln
//STRIP001              pSfxViewSh = pSfxViewFrame->GetViewShell();
//STRIP001              pViewSh = PTR_CAST( SdViewShell, pSfxViewSh );
//STRIP001
//STRIP001              if ( pViewSh && pViewSh->GetFrameView() )
//STRIP001              {
//STRIP001                  pViewSh->WriteFrameViewData();
//STRIP001                  pFrameViewList->Insert( new FrameView( pDoc, pViewSh->GetFrameView() ) );
//STRIP001              }
//STRIP001
//STRIP001              pSfxViewFrame = SfxViewFrame::GetNext(*pSfxViewFrame, this, 0, false);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  SfxInPlaceObject::InPlaceActivate( bActive );
//STRIP001
//STRIP001  if( bActive )
//STRIP001  {
//STRIP001      FrameView* pFrameView = NULL;
//STRIP001      List* pFrameViewList = pDoc->GetFrameViewList();
//STRIP001
//STRIP001      DBG_ASSERT( pFrameViewList, "No FrameViewList?" );
//STRIP001      if( pFrameViewList )
//STRIP001      {
//STRIP001          SdViewShell* pViewSh = NULL;
//STRIP001          SfxViewShell* pSfxViewSh = NULL;
//STRIP001          SfxViewFrame* pSfxViewFrame = SfxViewFrame::GetFirst(this, 0,false);
//STRIP001
//STRIP001          sal_uInt32 i;
//STRIP001          for( i = 0; pSfxViewFrame && (i < pFrameViewList->Count()); i++ )
//STRIP001          {
//STRIP001              // Anzahl FrameViews ermitteln
//STRIP001              pSfxViewSh = pSfxViewFrame->GetViewShell();
//STRIP001              pViewSh = PTR_CAST( SdViewShell, pSfxViewSh );
//STRIP001
//STRIP001              if ( pViewSh )
//STRIP001              {
//STRIP001                  pViewSh->ReadFrameViewData( (FrameView*)pFrameViewList->GetObject(i) );
//STRIP001              }
//STRIP001
//STRIP001              pSfxViewFrame = SfxViewFrame::GetNext(*pSfxViewFrame, this, 0,false);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* SFX-Aktivierung
|*
\************************************************************************/

//STRIP001 void SdDrawDocShell::Activate( BOOL bMDI)
//STRIP001 {
//STRIP001  if (bMDI)
//STRIP001  {
//STRIP001      ApplySlotFilter();
//STRIP001      pDoc->StartOnlineSpelling();
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* SFX-Deaktivierung
|*
\************************************************************************/

/*N*/ void SdDrawDocShell::Deactivate( BOOL )
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* SFX-Undomanager zurueckgeben
|*
\************************************************************************/

/*N*/ SfxUndoManager* SdDrawDocShell::GetUndoManager()
/*N*/ {
/*N*/   return pUndoManager;
/*N*/ }



/*************************************************************************
|*
|* Tabellenzeiger auffrischen
|*
\************************************************************************/

/*N*/ void SdDrawDocShell::UpdateTablePointers()
/*N*/ {
/*N*/   PutItem( SvxColorTableItem( pDoc->GetColorTable() ) );
/*N*/   PutItem( SvxGradientListItem( pDoc->GetGradientList() ) );
/*N*/   PutItem( SvxHatchListItem( pDoc->GetHatchList() ) );
/*N*/   PutItem( SvxBitmapListItem( pDoc->GetBitmapList() ) );
/*N*/   PutItem( SvxDashListItem( pDoc->GetDashList() ) );
/*N*/   PutItem( SvxLineEndListItem( pDoc->GetLineEndList() ) );
/*N*/
/*N*/   delete pFontList;
/*N*/   pFontList = new FontList( GetPrinter(TRUE), Application::GetDefaultDevice(), FALSE );
/*N*/   SvxFontListItem aFontListItem( pFontList );
/*N*/   PutItem( aFontListItem );
/*N*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/

//STRIP001 void SdDrawDocShell::CancelSearching()
//STRIP001 {
//STRIP001  if ( pFuActual && pFuActual->ISA(FuSearch) )
//STRIP001  {
//STRIP001      delete pFuActual;
//STRIP001      pFuActual = NULL;
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*  den eingestellten SlotFilter anwenden
|*
\************************************************************************/

//STRIP001 void SdDrawDocShell::ApplySlotFilter() const
//STRIP001 {
//STRIP001     SfxViewShell* pTestViewShell = SfxViewShell::GetFirst();
//STRIP001
//STRIP001     while( pTestViewShell )
//STRIP001     {
//STRIP001         if( pTestViewShell->GetObjectShell() == const_cast< SdDrawDocShell* >( this ) &&
//STRIP001             pTestViewShell->GetViewFrame() &&
//STRIP001             pTestViewShell->GetViewFrame()->GetDispatcher() )
//STRIP001         {
//STRIP001          SfxDispatcher* pDispatcher = pTestViewShell->GetViewFrame()->GetDispatcher();
//STRIP001
//STRIP001          if( pFilterSIDs )
//STRIP001              pDispatcher->SetSlotFilter( bFilterEnable, nFilterCount, pFilterSIDs );
//STRIP001          else
//STRIP001              pDispatcher->SetSlotFilter();
//STRIP001
//STRIP001             if( pDispatcher->GetBindings() )
//STRIP001                 pDispatcher->GetBindings()->InvalidateAll( TRUE );
//STRIP001         }
//STRIP001
//STRIP001         pTestViewShell = SfxViewShell::GetNext( *pTestViewShell );
//STRIP001     }
//STRIP001 }


/*N*/ void SdDrawDocShell::SetModified( BOOL bSet /* = TRUE */ )
/*N*/ {
/*N*/   SfxInPlaceObject::SetModified( bSet );
/*N*/
/*N*/     // #100237# change model state, too
/*N*/     // #103182# only set the changed state if modification is enabled
/*N*/     if( IsEnableSetModified() && pDoc )
/*N*/         pDoc->NbcSetChanged( bSet );
/*N*/
/*N*/   Broadcast( SfxSimpleHint( SFX_HINT_DOCCHANGED ) );
/*N*/ }

//STRIP001 Window*  SdDrawDocShell::GetWindow() const
//STRIP001 {
//STRIP001  SfxViewFrame* pFrame = GetFrame();
//STRIP001  if( pFrame == NULL )
//STRIP001      pFrame = SfxViewFrame::GetFirst( this );
//STRIP001
//STRIP001  if( pFrame )
//STRIP001      return &(pFrame->GetWindow());
//STRIP001  else
//STRIP001  {
//STRIP001      DBG_ASSERT( 0, "No active window for SdDrawDocShell found! (next gpf is caused by this assertion)" );
//STRIP001      return NULL;
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|* Callback fuer ExecuteSpellPopup()
|*
\************************************************************************/

// #91457# ExecuteSpellPopup now handled by SdDrawDocShell. This is necessary
// to get hands on the outliner and the text object.
//STRIP001 #ifndef SVX_LIGHT
//STRIP001 IMPL_LINK(SdDrawDocShell, OnlineSpellCallback, SpellCallbackInfo*, pInfo)
//STRIP001 {
//STRIP001  SdrObject* pObj = NULL;
//STRIP001  SdrOutliner* pOutl = NULL;
//STRIP001
//STRIP001  if(GetViewShell())
//STRIP001  {
//STRIP001      pOutl = GetViewShell()->GetView()->GetTextEditOutliner();
//STRIP001      pObj = GetViewShell()->GetView()->GetTextEditObject();
//STRIP001  }
//STRIP001
//STRIP001  pDoc->ImpOnlineSpellCallback(pInfo, pObj, pOutl);
//STRIP001  return(0);
//STRIP001 }
//STRIP001 #endif // !SVX_LIGHT

}
