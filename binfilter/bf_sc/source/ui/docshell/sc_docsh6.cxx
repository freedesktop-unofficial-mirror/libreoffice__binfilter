/*************************************************************************
 *
 *  $RCSfile: sc_docsh6.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 11:47:32 $
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

// System - Includes -----------------------------------------------------

//#define _BASEDLGS_HXX ***
#define _BIGINT_HXX
#define _CACHESTR_HXX
//#define _CLIP_HXX
#define _CONFIG_HXX
#define _CURSOR_HXX
//#define _COLOR_HXX
//#define _CTRLBOX_HXX
//#define _CTRLTOOL_HXX
#define _DIALOGS_HXX
#define _DLGCFG_HXX
#define _DYNARR_HXX
#define _EXTATTR_HXX
//#define _FIELD_HXX
#define _FILDLG_HXX
//#define _FILTER_HXX
#define _FONTDLG_HXX
#define _FRM3D_HXX
//#define _GRAPH_HXX
//#define _GDIMTF_HXX
#define _INTRO_HXX
#define _ISETBWR_HXX
#define _NO_SVRTF_PARSER_HXX
//#define _MDIFRM_HXX
#define _MACRODLG_HXX
#define _MODALDLG_HXX
#define _MOREBUTTON_HXX
//#define _MAPMOD_HXX
#define _OUTLINER_HXX
//#define _PAL_HXX
#define _PASSWD_HXX
//#define _PRNDLG_HXX   //
#define _POLY_HXX
#define _PVRWIN_HXX
#define _QUEUE_HXX
#define _RULER_HXX
#define _SCRWIN_HXX
//#define _SELENG_HXX
#define _SETBRW_HXX
//#define _SOUND_HXX
#define _STACK_HXX
//#define _STATUS_HXX ***
#define _STDMENU_HXX
//#define _STDCTRL_HXX
//#define _SYSDLG_HXX
//#define _TAB_HXX
#define _TABBAR_HXX
//#define _TREELIST_HXX
//#define _VALUESET_HXX
#define _VCBRW_HXX
#define _VCTRLS_HXX
//#define _VCATTR_HXX
#define _VCSBX_HXX
#define _VCONT_HXX
#define _VDRWOBJ_HXX
//#define _VIEWFAC_HXX


#define _SFX_PRNMON_HXX
#define _SFX_RESMGR_HXX
//#define _SFX_SAVEOPT_HXX
#define _SFX_TEMPLDLG_HXX
//#define _SFXAPP_HXX
#define _SFXBASIC_HXX
//#define _SFXCTRLITEM_HXX
#define _SFXDISPATCH_HXX
#define _SFXFILEDLG_HXX
#define _SFXIMGMGR_HXX
#define _SFXMNUMGR_HXX
//#define _SFXMSG_HXX
#define _SFXMSGDESCR_HXX
#define _SFXMSGPOOL_HXX
//#define _SFXOBJFACE_HXX
//#define _SFXREQUEST_HXX
#define _SFXSTBITEM_HXX
#define _SFXSTBMGR_HXX
#define _SFXTBXCTRL_HXX
#define _SFXTBXMGR_HXX
#define _SFX_TEMPLDLG_HXX

#define _SI_DLL_HXX
#define _SIDLL_HXX
#define _SI_NOITEMS
#define _SI_NOOTHERFORMS
#define _SI_NOSBXCONTROLS
#define _SINOSBXCONTROLS
#define _SI_NODRW
#define _SI_NOCONTROL

#define _SV_NOXSOUND
#define _SVDATTR_HXX
#define _SVDETC_HXX
#define _SVDIO_HXX
#define _SVDRAG_HXX
#define _SVDLAYER_HXX
#define _SVDXOUT_HXX

#define _SVX_DAILDLL_HXX
#define _SVX_HYPHEN_HXX
#define _SVX_IMPGRF_HXX
#define _SVX_OPTITEMS_HXX
#define _SVX_OPTGERL_HXX
#define _SVX_OPTSAVE_HXX
#define _SVX_OPTSPELL_HXX
#define _SVX_OPTPATH_HXX
#define _SVX_OPTLINGU_HXX
#define _SVX_RULER_HXX
#define _SVX_RULRITEM_HXX
#define _SVX_SPLWRAP_HXX
#define _SVX_SPLDLG_HXX
#define _SVX_THESDLG_HXX


#ifdef PCH
// auto strip #include "ui_pch.hxx"
#endif

#pragma hdrstop

#ifndef PCH
// auto strip #include <so3/ipenv.hxx>
// auto strip #include "scitems.hxx"

#include <so3/ipenv.hxx>

// auto strip #ifndef _SFXPOOLITEM_HXX
// auto strip #include <svtools/poolitem.hxx>
// auto strip #endif

// auto strip #include <bf_svx/pageitem.hxx>
// auto strip #include <vcl/virdev.hxx>
#include <bf_svx/linkmgr.hxx>
#endif

// INCLUDE ---------------------------------------------------------------

//#include <svxlink.hxx>

#include "docsh.hxx"

// auto strip #include "stlsheet.hxx"
#include "stlpool.hxx"
// auto strip #include "global.hxx"
// auto strip #include "viewdata.hxx"
#include "tabvwsh.hxx"
#include "tablink.hxx"
#include "collect.hxx"

#ifndef _SFXITEMSET_HXX
#include <svtools/itemset.hxx>
#endif

namespace binfilter {

/*N*/ struct ScStylePair
/*N*/ {
/*N*/   SfxStyleSheetBase *pSource;
/*N*/   SfxStyleSheetBase *pDest;
/*N*/ };


// STATIC DATA -----------------------------------------------------------

//----------------------------------------------------------------------

//
//  Ole
//

//STRIP001 String ScDocShell::CreateObjectName( const String& rPrefix )
//STRIP001 {
//STRIP001  String aStr( rPrefix );
//STRIP001  USHORT i = 1;
//STRIP001  aStr += String::CreateFromInt32( i );
//STRIP001  while( Find( aStr ) )
//STRIP001  {
//STRIP001      i++;
//STRIP001      aStr = rPrefix;
//STRIP001      aStr += String::CreateFromInt32( i );
//STRIP001  }
//STRIP001  return aStr;
//STRIP001 }

/*N*/ void __EXPORT ScDocShell::SetVisArea( const Rectangle & rVisArea )
/*N*/ {
/*N*/   //  with the SnapVisArea call in SetVisAreaOrSize, it's safe to always
/*N*/   //  use both the size and position of the VisArea
/*N*/   SetVisAreaOrSize( rVisArea, TRUE );
/*N*/ }

/*N*/ void ScDocShell::SetVisAreaOrSize( const Rectangle& rVisArea, BOOL bModifyStart )
/*N*/ {
/*N*/   Rectangle aArea = rVisArea;
/*N*/   if (bModifyStart)
/*N*/   {
/*N*/       if ( aArea.Left() < 0 || aArea.Top() < 0 )
/*N*/       {
/*?*/           //  VisArea start position can't be negative.
/*?*/           //  Move the VisArea, otherwise only the upper left position would
/*?*/           //  be changed in SnapVisArea, and the size would be wrong.
/*?*/
/*?*/           Point aNewPos( Max( aArea.Left(), (long) 0 ),
/*?*/                          Max( aArea.Top(), (long) 0 ) );
/*?*/           aArea.SetPos( aNewPos );
/*N*/       }
/*N*/   }
/*N*/   else
/*?*/       aArea.SetPos( SfxInPlaceObject::GetVisArea().TopLeft() );
/*N*/
/*N*/   //      hier Position anpassen!
/*N*/
/*N*/   //  #92248# when loading an ole object, the VisArea is set from the document's
/*N*/   //  view settings and must be used as-is (document content may not be complete yet).
/*N*/   if ( !aDocument.IsImportingXML() )
/*N*/       aDocument.SnapVisArea( aArea );
/*N*/
/*N*/   SvInPlaceEnvironment* pEnv = GetIPEnv();
/*N*/   if (pEnv)
/*N*/   {
/*?*/       Window* pWin = pEnv->GetEditWin();
/*?*/       pEnv->MakeScale( aArea.GetSize(), MAP_100TH_MM,
/*?*/                           pWin->LogicToPixel( aArea.GetSize() ) );
/*N*/   }
/*N*/
/*N*/   SvInPlaceObject::SetVisArea( aArea );
/*N*/
/*N*/   if (bIsInplace)                     // Zoom in der InPlace View einstellen
/*N*/   {
/*?*/       ScTabViewShell* pViewSh = ScTabViewShell::GetActiveViewShell();
/*?*/       if (pViewSh)
/*?*/       {
/*?*/           if (pViewSh->GetViewData()->GetDocShell() == this)
/*?*/           {   DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 pViewSh->UpdateOleZoom();
/*?*/       }
/*?*/       //else
/*?*/       //  DataChanged( SvDataType() );            // fuer Zuppeln wenn nicht IP-aktiv
/*N*/   }
/*N*/
/*N*/   if (aDocument.IsEmbedded())
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ScTripel aOldStart,aOldEnd;
//STRIP001 /*?*/        aDocument.GetEmbedded(aOldStart,aOldEnd);
//STRIP001 /*?*/        aDocument.SetEmbedded( aArea );
//STRIP001 /*?*/        ScTripel aNewStart,aNewEnd;
//STRIP001 /*?*/        aDocument.GetEmbedded(aNewStart,aNewEnd);
//STRIP001 /*?*/        if (aNewStart!=aOldStart || aNewEnd!=aOldEnd)
//STRIP001 /*?*/            PostPaint(0,0,0,MAXCOL,MAXROW,MAXTAB,PAINT_GRID);
//STRIP001 /*?*/
//STRIP001 /*?*/        ViewChanged( ASPECT_CONTENT );          // auch im Container anzeigen
/*N*/   }
/*N*/ }

/*N*/ BOOL ScDocShell::IsOle()
/*N*/ {
/*N*/   return (GetCreateMode() == SFX_CREATE_MODE_EMBEDDED);
/*N*/ }

//STRIP001 void ScDocShell::UpdateOle( const ScViewData* pViewData, BOOL bSnapSize )
//STRIP001 {
//STRIP001  //  wenn's gar nicht Ole ist, kann man sich die Berechnungen sparen
//STRIP001  //  (VisArea wird dann beim Save wieder zurueckgesetzt)
//STRIP001
//STRIP001  if (GetCreateMode() == SFX_CREATE_MODE_STANDARD)
//STRIP001      return;
//STRIP001
//STRIP001  DBG_ASSERT(pViewData,"pViewData==0 bei ScDocShell::UpdateOle");
//STRIP001
//STRIP001  Rectangle aOldArea = SfxInPlaceObject::GetVisArea();
//STRIP001  Rectangle aNewArea = aOldArea;
//STRIP001
//STRIP001  BOOL bChange = FALSE;
//STRIP001  BOOL bEmbedded = aDocument.IsEmbedded();
//STRIP001  if (bEmbedded)
//STRIP001      aNewArea = aDocument.GetEmbeddedRect();
//STRIP001  else
//STRIP001  {
//STRIP001      USHORT nX = pViewData->GetPosX(SC_SPLIT_LEFT);
//STRIP001      USHORT nY = pViewData->GetPosY(SC_SPLIT_BOTTOM);
//STRIP001      Point aStart = aDocument.GetMMRect( nX,nY, nX,nY, 0 ).TopLeft();
//STRIP001      aNewArea.SetPos(aStart);
//STRIP001      if (bSnapSize)
//STRIP001          aDocument.SnapVisArea(aNewArea);
//STRIP001
//STRIP001      if ( pViewData->GetTabNo() != aDocument.GetVisibleTab() )
//STRIP001      {
//STRIP001          aDocument.SetVisibleTab( pViewData->GetTabNo() );
//STRIP001          bChange = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if (aNewArea != aOldArea)
//STRIP001  {
//STRIP001      SetVisAreaOrSize( aNewArea, TRUE ); // hier muss auch der Start angepasst werden
//STRIP001      bChange = TRUE;
//STRIP001  }
//STRIP001
//STRIP001 //   if (bChange)
//STRIP001 //       DataChanged( SvDataType() );        //! passiert auch bei SetModified
//STRIP001 }

//
//  Style-Krempel fuer Organizer etc.
//

/*N*/ SfxStyleSheetBasePool* __EXPORT ScDocShell::GetStyleSheetPool()
/*N*/ {
/*N*/   return (SfxStyleSheetBasePool*)aDocument.GetStyleSheetPool();
/*N*/ }


//  nach dem Laden von Vorlagen aus einem anderen Dokment (LoadStyles, Insert)
//  muessen die SetItems (ATTR_PAGE_HEADERSET, ATTR_PAGE_FOOTERSET) auf den richtigen
//  Pool umgesetzt werden, bevor der Quell-Pool geloescht wird.

/*N*/ void lcl_AdjustPool( SfxStyleSheetBasePool* pStylePool )
/*N*/ {
/*N*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 pStylePool->SetSearchMask(SFX_STYLE_FAMILY_PAGE, 0xffff);
//STRIP001 /*N*/    SfxStyleSheetBase *pStyle = pStylePool->First();
//STRIP001 /*N*/    while ( pStyle )
//STRIP001 /*N*/    {
//STRIP001 /*N*/        SfxItemSet& rStyleSet = pStyle->GetItemSet();
//STRIP001 /*N*/
//STRIP001 /*N*/        const SfxPoolItem* pItem;
//STRIP001 /*N*/        if (rStyleSet.GetItemState(ATTR_PAGE_HEADERSET,FALSE,&pItem) == SFX_ITEM_SET)
//STRIP001 /*N*/        {
//STRIP001 /*N*/            SfxItemSet& rSrcSet = ((SvxSetItem*)pItem)->GetItemSet();
//STRIP001 /*N*/            SfxItemSet* pDestSet = new SfxItemSet(*rStyleSet.GetPool(),rSrcSet.GetRanges());
//STRIP001 /*N*/            pDestSet->Put(rSrcSet);
//STRIP001 /*N*/            rStyleSet.Put(SvxSetItem(ATTR_PAGE_HEADERSET,pDestSet));
//STRIP001 /*N*/        }
//STRIP001 /*N*/        if (rStyleSet.GetItemState(ATTR_PAGE_FOOTERSET,FALSE,&pItem) == SFX_ITEM_SET)
//STRIP001 /*N*/        {
//STRIP001 /*N*/            SfxItemSet& rSrcSet = ((SvxSetItem*)pItem)->GetItemSet();
//STRIP001 /*N*/            SfxItemSet* pDestSet = new SfxItemSet(*rStyleSet.GetPool(),rSrcSet.GetRanges());
//STRIP001 /*N*/            pDestSet->Put(rSrcSet);
//STRIP001 /*N*/            rStyleSet.Put(SvxSetItem(ATTR_PAGE_FOOTERSET,pDestSet));
//STRIP001 /*N*/        }
//STRIP001 /*N*/
//STRIP001 /*N*/        pStyle = pStylePool->Next();
//STRIP001 /*N*/    }
/*N*/ }

//STRIP001 void __EXPORT ScDocShell::LoadStyles( SfxObjectShell &rSource )
//STRIP001 {
//STRIP001  aDocument.StylesToNames();
//STRIP001
//STRIP001  SfxObjectShell::LoadStyles(rSource);
//STRIP001  lcl_AdjustPool( GetStyleSheetPool() );      // SetItems anpassen
//STRIP001
//STRIP001  aDocument.UpdStlShtPtrsFrmNms();
//STRIP001
//STRIP001  UpdateAllRowHeights();
//STRIP001
//STRIP001      //  Paint
//STRIP001
//STRIP001  PostPaint( 0,0,0, MAXCOL,MAXROW,MAXTAB, PAINT_GRID | PAINT_LEFT );
//STRIP001 }

/*N*/ void ScDocShell::LoadStylesArgs( ScDocShell& rSource, BOOL bReplace, BOOL bCellStyles, BOOL bPageStyles )
/*N*/ {
/*N*/   //  similar to LoadStyles, but with selectable behavior for XStyleLoader::loadStylesFromURL call
/*N*/
/*N*/   if ( !bCellStyles && !bPageStyles )     // nothing to do
/*N*/       return;
/*N*/
/*N*/   ScStyleSheetPool* pSourcePool = rSource.GetDocument()->GetStyleSheetPool();
/*N*/   ScStyleSheetPool* pDestPool = aDocument.GetStyleSheetPool();
/*N*/
/*N*/   SfxStyleFamily eFamily = bCellStyles ?
/*N*/           ( bPageStyles ? SFX_STYLE_FAMILY_ALL : SFX_STYLE_FAMILY_PARA ) :
/*N*/           SFX_STYLE_FAMILY_PAGE;
/*N*/   SfxStyleSheetIterator aIter( pSourcePool, eFamily );
/*N*/   USHORT nSourceCount = aIter.Count();
/*N*/   if ( nSourceCount == 0 )
/*N*/       return;                             // no source styles
/*N*/
/*N*/   ScStylePair* pStyles = new ScStylePair[ nSourceCount ];
/*N*/   USHORT nFound = 0;
/*N*/
/*N*/   //  first create all new styles
/*N*/
/*N*/   SfxStyleSheetBase* pSourceStyle = aIter.First();
/*N*/   while (pSourceStyle)
/*N*/   {
/*N*/       String aName = pSourceStyle->GetName();
/*N*/       SfxStyleSheetBase* pDestStyle = pDestPool->Find( pSourceStyle->GetName(), pSourceStyle->GetFamily() );
/*N*/       if ( pDestStyle )
/*N*/       {
/*N*/           // touch existing styles only if replace flag is set
/*N*/           if ( bReplace )
/*N*/           {
/*N*/               pStyles[nFound].pSource = pSourceStyle;
/*N*/               pStyles[nFound].pDest = pDestStyle;
/*N*/               ++nFound;
/*N*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           pStyles[nFound].pSource = pSourceStyle;
/*N*/           pStyles[nFound].pDest = &pDestPool->Make( aName, pSourceStyle->GetFamily(), pSourceStyle->GetMask() );
/*N*/           ++nFound;
/*N*/       }
/*N*/
/*N*/       pSourceStyle = aIter.Next();
/*N*/   }
/*N*/
/*N*/   //  then copy contents (after inserting all styles, for parent etc.)
/*N*/
/*N*/   for ( USHORT i = 0; i < nFound; ++i )
/*N*/   {
/*N*/       pStyles[i].pDest->GetItemSet().PutExtended(
/*N*/           pStyles[i].pSource->GetItemSet(), SFX_ITEM_DONTCARE, SFX_ITEM_DEFAULT);
/*N*/       if(pStyles[i].pSource->HasParentSupport())
/*N*/           pStyles[i].pDest->SetParent(pStyles[i].pSource->GetParent());
/*N*/       // follow is never used
/*N*/   }
/*N*/
/*N*/   lcl_AdjustPool( GetStyleSheetPool() );      // adjust SetItems
/*N*/   UpdateAllRowHeights();
/*N*/   PostPaint( 0,0,0, MAXCOL,MAXROW,MAXTAB, PAINT_GRID | PAINT_LEFT );      // Paint
/*N*/
/*N*/   delete[] pStyles;
/*N*/ }


//STRIP001 BOOL __EXPORT ScDocShell::Insert( SfxObjectShell &rSource,
//STRIP001                              USHORT nSourceIdx1, USHORT nSourceIdx2, USHORT nSourceIdx3,
//STRIP001                              USHORT &nIdx1, USHORT &nIdx2, USHORT &nIdx3, USHORT &rIdxDeleted )
//STRIP001 {
//STRIP001  BOOL bRet = SfxObjectShell::Insert( rSource, nSourceIdx1, nSourceIdx2, nSourceIdx3,
//STRIP001                                          nIdx1, nIdx2, nIdx3, rIdxDeleted );
//STRIP001  if (bRet)
//STRIP001      lcl_AdjustPool( GetStyleSheetPool() );      // SetItems anpassen
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

/*N*/ void ScDocShell::UpdateLinks()
/*N*/ {
/*N*/   SvxLinkManager* pLinkManager = aDocument.GetLinkManager();
/*N*/   USHORT nCount;
/*N*/   USHORT i;
/*N*/   StrCollection aNames;
/*N*/
/*N*/   // nicht mehr benutzte Links raus
/*N*/
/*N*/   nCount = pLinkManager->GetLinks().Count();
/*N*/   for (i=nCount; i>0; )
/*N*/   {
/*?*/       --i;
/*?*/       ::so3::SvBaseLink* pBase = *pLinkManager->GetLinks()[i];
/*?*/       if (pBase->ISA(ScTableLink))
/*?*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ScTableLink* pTabLink = (ScTableLink*)pBase;
//STRIP001 /*?*/            if (pTabLink->IsUsed())
//STRIP001 /*?*/            {
//STRIP001 /*?*/                StrData* pData = new StrData(pTabLink->GetFileName());
//STRIP001 /*?*/                if (!aNames.Insert(pData))
//STRIP001 /*?*/                    delete pData;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            else        // nicht mehr benutzt -> loeschen
//STRIP001 /*?*/            {
//STRIP001 /*?*/                pTabLink->SetAddUndo(TRUE);
//STRIP001 /*?*/                pLinkManager->Remove(i);
//STRIP001 /*?*/            }
/*?*/       }
/*N*/   }
/*N*/
/*N*/
/*N*/   // neue Links eintragen
/*N*/
/*N*/   nCount = aDocument.GetTableCount();
/*N*/   for (i=0; i<nCount; i++)
/*N*/       if (aDocument.IsLinked(i))
/*N*/       {
/*N*/           String aDocName = aDocument.GetLinkDoc(i);
/*N*/           String aFltName = aDocument.GetLinkFlt(i);
/*N*/           String aOptions = aDocument.GetLinkOpt(i);
/*N*/           ULONG nRefresh  = aDocument.GetLinkRefreshDelay(i);
/*N*/           BOOL bThere = FALSE;
/*N*/           for (USHORT j=0; j<i && !bThere; j++)               // im Dokument mehrfach?
/*N*/               if (aDocument.IsLinked(j)
/*N*/                       && aDocument.GetLinkDoc(j) == aDocName
/*N*/                       && aDocument.GetLinkFlt(j) == aFltName
/*N*/                       && aDocument.GetLinkOpt(j) == aOptions)
/*N*/                       // Ignore refresh delay in compare, it should be the
/*N*/                       // same for identical links and we don't want dupes
/*N*/                       // if it ain't.
/*N*/                   bThere = TRUE;
/*N*/
/*N*/           if (!bThere)                                        // schon als Filter eingetragen?
/*N*/           {
/*N*/               StrData* pData = new StrData(aDocName);
/*N*/               if (!aNames.Insert(pData))
/*N*/               {
/*?*/                   delete pData;
/*?*/                   bThere = TRUE;
/*N*/               }
/*N*/           }
/*N*/           if (!bThere)
/*N*/           {
/*N*/               ScTableLink* pLink = new ScTableLink( this, aDocName, aFltName, aOptions, nRefresh );
/*N*/               pLink->SetInCreate( TRUE );
/*N*/               pLinkManager->InsertFileLink( *pLink, OBJECT_CLIENT_FILE, aDocName, &aFltName );
/*N*/               pLink->Update();
/*N*/               pLink->SetInCreate( FALSE );
/*N*/           }
/*N*/       }
/*N*/ }

/*N*/ BOOL ScDocShell::ReloadTabLinks()
/*N*/ {
/*N*/   SvxLinkManager* pLinkManager = aDocument.GetLinkManager();
/*N*/
/*N*/   BOOL bAny = FALSE;
/*N*/   USHORT nCount = pLinkManager->GetLinks().Count();
/*N*/   for (USHORT i=0; i<nCount; i++ )
/*N*/   {
/*N*/       ::so3::SvBaseLink* pBase = *pLinkManager->GetLinks()[i];
/*N*/       if (pBase->ISA(ScTableLink))
/*N*/       {
/*N*/           ScTableLink* pTabLink = (ScTableLink*)pBase;
/*N*/ //            pTabLink->SetAddUndo(FALSE);        //! Undo's zusammenfassen
/*N*/           pTabLink->SetPaint(FALSE);          //  Paint nur einmal am Ende
/*N*/           pTabLink->Update();
/*N*/           pTabLink->SetPaint(TRUE);
/*N*/ //            pTabLink->SetAddUndo(TRUE);
/*N*/           bAny = TRUE;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if ( bAny )
/*N*/   {
/*N*/       //  Paint nur einmal
/*N*/       PostPaint( ScRange(0,0,0,MAXCOL,MAXROW,MAXTAB),
/*N*/                                   PAINT_GRID | PAINT_TOP | PAINT_LEFT );
/*N*/
/*N*/       SetDocumentModified();
/*N*/   }
/*N*/
/*N*/   return TRUE;        //! Fehler erkennen
/*N*/ }


}
