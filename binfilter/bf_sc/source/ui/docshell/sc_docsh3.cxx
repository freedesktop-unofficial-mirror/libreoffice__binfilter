/*************************************************************************
 *
 *  $RCSfile: sc_docsh3.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 11:46:55 $
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

#ifdef PCH
// auto strip #include "ui_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------

#include "scitems.hxx"
// auto strip #include "rangelst.hxx"
#include <bf_svx/flstitem.hxx>
// auto strip #include <bf_svx/pageitem.hxx>
#include <bf_svx/paperinf.hxx>

#ifndef _SFXSTRITEM_HXX
#include <svtools/stritem.hxx>
#endif

// auto strip #include <bf_svx/postattr.hxx>
//#include <bf_svx/postdlg.hxx>
#include <bf_svx/sizeitem.hxx>
#include <bf_offmgr/app.hxx>

// auto strip #include <bf_sfx2/docfile.hxx>
// auto strip #include <bf_sfx2/docinf.hxx>
#include <bf_sfx2/misccfg.hxx>
#include <bf_sfx2/printer.hxx>
#include <svtools/ctrltool.hxx>
#include <vcl/virdev.hxx>
// auto strip #include <vcl/svapp.hxx>
// auto strip #include <vcl/msgbox.hxx>

// auto strip #ifndef _UNOTOOLS_LOCALEDATAWRAPPER_HXX
// auto strip #include <unotools/localedatawrapper.hxx>
// auto strip #endif

#include "docsh.hxx"
#include "scmod.hxx"
#include "tabvwsh.hxx"
// auto strip #include "viewdata.hxx"
#include "docpool.hxx"
#include "stlpool.hxx"
#include "patattr.hxx"
// auto strip #include "uiitems.hxx"
#include "hints.hxx"
#include "docoptio.hxx"
// auto strip #include "viewopti.hxx"
#include "pntlock.hxx"
// auto strip #include "chgtrack.hxx"
// auto strip #include "docfunc.hxx"
// auto strip #include "cell.hxx"
// auto strip #include "chgviset.hxx"
// auto strip #include "progress.hxx"
// auto strip #include "redcom.hxx"
#include "bf_sc.hrc"
#include "inputopt.hxx"
#include "drwlayer.hxx"
#include "inputhdl.hxx"
namespace binfilter {

//------------------------------------------------------------------

//
//          Redraw - Benachrichtigungen
//


//STRIP001 void ScDocShell::PostEditView( ScEditEngineDefaulter* pEditEngine, const ScAddress& rCursorPos )
//STRIP001 {
//STRIP001 //   Broadcast( ScEditViewHint( pEditEngine, rCursorPos ) );
//STRIP001
//STRIP001      //  Test: nur aktive ViewShell
//STRIP001
//STRIP001  ScTabViewShell* pViewSh = ScTabViewShell::GetActiveViewShell();
//STRIP001  if (pViewSh && pViewSh->GetViewData()->GetDocShell() == this)
//STRIP001  {
//STRIP001      ScEditViewHint aHint( pEditEngine, rCursorPos );
//STRIP001      pViewSh->Notify( *this, aHint );
//STRIP001  }
//STRIP001 }

/*N*/ void ScDocShell::PostDataChanged()
/*N*/ {
/*N*/   Broadcast( SfxSimpleHint( FID_DATACHANGED ) );
/*N*/   aDocument.ResetChanged( ScRange(0,0,0,MAXCOL,MAXROW,MAXTAB) );
/*N*/
/*N*/   SFX_APP()->Broadcast(SfxSimpleHint( FID_ANYDATACHANGED ));      // Navigator
/*N*/   //! Navigator direkt benachrichtigen!
/*N*/ }

/*N*/ void ScDocShell::PostPaint( USHORT nStartCol, USHORT nStartRow, USHORT nStartTab,
/*N*/                           USHORT nEndCol, USHORT nEndRow, USHORT nEndTab, USHORT nPart,
/*N*/                           USHORT nExtFlags )
/*N*/ {
/*N*/   if (nStartCol > MAXCOL) nStartCol = MAXCOL;
/*N*/   if (nStartRow > MAXROW) nStartRow = MAXROW;
/*N*/   if (nEndCol > MAXCOL) nEndCol = MAXCOL;
/*N*/   if (nEndRow > MAXROW) nEndRow = MAXROW;
/*N*/
/*N*/   if ( pPaintLockData )
/*N*/   {
/*N*/       //! nExtFlags ???
/*N*/       pPaintLockData->AddRange( ScRange( nStartCol, nStartRow, nStartTab,
/*N*/                                           nEndCol, nEndRow, nEndTab ), nPart );
/*N*/       return;
/*N*/   }
/*N*/
/*N*/
/*N*/   if (nExtFlags & SC_PF_LINES)            // Platz fuer Linien berücksichtigen
/*N*/   {
/*N*/                                           //! Abfrage auf versteckte Spalten/Zeilen!
/*N*/       if (nStartCol>0) --nStartCol;
/*N*/       if (nEndCol<MAXCOL) ++nEndCol;
/*N*/       if (nStartRow>0) --nStartRow;
/*N*/       if (nEndRow<MAXROW) ++nEndRow;
/*N*/   }
/*N*/
/*N*/                                           // um zusammengefasste erweitern
/*N*/   if (nExtFlags & SC_PF_TESTMERGE)
/*?*/       aDocument.ExtendMerge( nStartCol, nStartRow, nEndCol, nEndRow, nStartTab );
/*N*/
/*N*/   if ( nStartCol != 0 || nEndCol != MAXCOL )
/*N*/   {
/*?*/       //  If rotated text is involved, repaint the entire rows.
/*?*/       //  #i9731# If there's right-to-left text to the left of the area,
/*?*/       //  the displacement for clipping of that text may change.
/*?*/       if ( aDocument.HasAttrib( 0,nStartRow,nStartTab,
/*?*/                                   MAXCOL,nEndRow,nEndTab, HASATTR_ROTATE | HASATTR_RTL ) )
/*?*/       {
/*?*/           nStartCol = 0;
/*?*/           nEndCol = MAXCOL;
/*?*/       }
/*N*/   }
/*N*/
/*N*/   Broadcast( ScPaintHint( ScRange( nStartCol, nStartRow, nStartTab,
/*N*/                                    nEndCol, nEndRow, nEndTab ), nPart ) );
/*N*/
/*N*/   if ( nPart & PAINT_GRID )
/*N*/       aDocument.ResetChanged( ScRange(nStartCol,nStartRow,nStartTab,nEndCol,nEndRow,nEndTab) );
/*N*/ }

/*N*/ void ScDocShell::PostPaint( const ScRange& rRange, USHORT nPart, USHORT nExtFlags )
/*N*/ {
/*N*/   PostPaint( rRange.aStart.Col(), rRange.aStart.Row(), rRange.aStart.Tab(),
/*N*/              rRange.aEnd.Col(),   rRange.aEnd.Row(),   rRange.aEnd.Tab(),
/*N*/              nPart, nExtFlags );
/*N*/ }

/*N*/ void ScDocShell::PostPaintGridAll()
/*N*/ {
/*N*/   PostPaint( 0,0,0, MAXCOL,MAXROW,MAXTAB, PAINT_GRID );
/*N*/ }

/*N*/ void ScDocShell::PostPaintCell( USHORT nCol, USHORT nRow, USHORT nTab )
/*N*/ {
/*N*/   PostPaint( nCol,nRow,nTab, nCol,nRow,nTab, PAINT_GRID, SC_PF_TESTMERGE );
/*N*/ }

/*N*/ void ScDocShell::PostPaintExtras()
/*N*/ {
/*N*/   PostPaint( 0,0,0, MAXCOL,MAXROW,MAXTAB, PAINT_EXTRAS );
/*N*/ }

//------------------------------------------------------------------

/*N*/ void ScDocShell::LockPaint_Impl(BOOL bDoc)
/*N*/ {
/*N*/   if ( pPaintLockData )
/*N*/       pPaintLockData->IncLevel(bDoc);
/*N*/   else
/*N*/       pPaintLockData = new ScPaintLockData(0);    //! Modus...
/*N*/ }

/*N*/ void ScDocShell::UnlockPaint_Impl(BOOL bDoc)
/*N*/ {
/*N*/   if ( pPaintLockData )
/*N*/   {
/*N*/       if ( pPaintLockData->GetLevel(bDoc) )
/*N*/           pPaintLockData->DecLevel(bDoc);
/*N*/       else if (!pPaintLockData->GetLevel(!bDoc))
/*N*/       {
/*N*/           //      Paint jetzt ausfuehren
/*N*/
/*N*/           ScPaintLockData* pPaint = pPaintLockData;
/*N*/           pPaintLockData = NULL;                      // nicht weitersammeln
/*N*/
/*N*/           ScRangeListRef xRangeList = pPaint->GetRangeList();
/*N*/           if (xRangeList)
/*N*/           {
/*N*/               USHORT nParts = pPaint->GetParts();
/*N*/               ULONG nCount = xRangeList->Count();
/*N*/               for ( ULONG i=0; i<nCount; i++ )
/*N*/               {
/*N*/                   //! nExtFlags ???
/*N*/                   ScRange aRange = *xRangeList->GetObject(i);
/*N*/                   PostPaint( aRange.aStart.Col(), aRange.aStart.Row(), aRange.aStart.Tab(),
/*N*/                               aRange.aEnd.Col(), aRange.aEnd.Row(), aRange.aEnd.Tab(),
/*N*/                               nParts );
/*N*/               }
/*N*/           }
/*N*/
/*N*/           if ( pPaint->GetModified() )
/*N*/               SetDocumentModified();
/*N*/
/*N*/           delete pPaint;
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/       DBG_ERROR("UnlockPaint ohne LockPaint");
/*N*/ }

/*N*/ void ScDocShell::LockDocument_Impl(USHORT nNew)
/*N*/ {
/*N*/   if (!nDocumentLock)
/*N*/   {
/*N*/       ScDrawLayer* pDrawLayer = aDocument.GetDrawLayer();
/*N*/       if (pDrawLayer)
/*N*/           pDrawLayer->setLock(TRUE);
/*N*/   }
/*N*/   nDocumentLock = nNew;
/*N*/ }

/*N*/ void ScDocShell::UnlockDocument_Impl(USHORT nNew)
/*N*/ {
/*N*/   nDocumentLock = nNew;
/*N*/   if (!nDocumentLock)
/*N*/   {
/*N*/       ScDrawLayer* pDrawLayer = aDocument.GetDrawLayer();
/*N*/       if (pDrawLayer)
/*N*/           pDrawLayer->setLock(FALSE);
/*N*/   }
/*N*/ }

/*N*/ USHORT ScDocShell::GetLockCount() const
/*N*/ {
/*N*/   return nDocumentLock;
/*N*/ }

/*N*/ void ScDocShell::SetLockCount(USHORT nNew)
/*N*/ {
/*N*/   if (nNew)                   // setzen
/*N*/   {
/*N*/       if ( !pPaintLockData )
/*N*/           pPaintLockData = new ScPaintLockData(0);    //! Modus...
/*N*/       pPaintLockData->SetLevel(nNew-1, TRUE);
/*N*/       LockDocument_Impl(nNew);
/*N*/   }
/*N*/   else if (pPaintLockData)    // loeschen
/*N*/   {
/*N*/       pPaintLockData->SetLevel(0, TRUE);  // bei Unlock sofort ausfuehren
/*N*/       UnlockPaint_Impl(TRUE);                 // jetzt
/*N*/       UnlockDocument_Impl(0);
/*N*/   }
/*N*/ }

/*N*/ void ScDocShell::LockPaint()
/*N*/ {
/*N*/   LockPaint_Impl(FALSE);
/*N*/ }

/*N*/ void ScDocShell::UnlockPaint()
/*N*/ {
/*N*/   UnlockPaint_Impl(FALSE);
/*N*/ }

/*N*/ void ScDocShell::LockDocument()
/*N*/ {
/*N*/   LockPaint_Impl(TRUE);
/*N*/   LockDocument_Impl(nDocumentLock + 1);
/*N*/ }

/*N*/ void ScDocShell::UnlockDocument()
/*N*/ {
/*N*/   if (nDocumentLock)
/*N*/   {
/*N*/       UnlockPaint_Impl(TRUE);
/*N*/       UnlockDocument_Impl(nDocumentLock - 1);
/*N*/   }
/*N*/   else
/*N*/       DBG_ERROR("UnlockDocument without LockDocument");
/*N*/ }

//------------------------------------------------------------------

//STRIP001 void ScDocShell::SetInplace( BOOL bInplace )
//STRIP001 {
//STRIP001  if (bIsInplace != bInplace)
//STRIP001  {
//STRIP001      bIsInplace = bInplace;
//STRIP001      CalcOutputFactor();
//STRIP001  }
//STRIP001 }

/*N*/ void ScDocShell::CalcOutputFactor()
/*N*/ {
/*N*/   if (bIsInplace)
/*N*/   {
/*N*/       nPrtToScreenFactor = 1.0;           // passt sonst nicht zur inaktiven Darstellung
/*N*/       return;
/*N*/   }
/*N*/
/*N*/   BOOL bTextWysiwyg = SC_MOD()->GetInputOptions().GetTextWysiwyg();
/*N*/   if (bTextWysiwyg)
/*N*/   {
/*N*/       nPrtToScreenFactor = 1.0;
/*N*/       return;
/*N*/   }
/*N*/
/*N*/   String aTestString = String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM(
/*N*/           "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz01234567890123456789" ));
/*N*/   long nPrinterWidth = 0;
/*N*/   long nWindowWidth = 0;
/*N*/   const ScPatternAttr* pPattern = (const ScPatternAttr*)&aDocument.GetPool()->
/*N*/                                           GetDefaultItem(ATTR_PATTERN);
/*N*/
/*N*/   Font aDefFont;
/*N*/   Printer* pPrinter = GetPrinter();
/*N*/   if (pPrinter)
/*N*/   {
/*N*/       MapMode aOldMode = pPrinter->GetMapMode();
/*N*/       Font    aOldFont = pPrinter->GetFont();
/*N*/
/*N*/       pPrinter->SetMapMode(MAP_PIXEL);
/*N*/       pPattern->GetFont(aDefFont, SC_AUTOCOL_BLACK, pPrinter);    // font color doesn't matter here
/*N*/       pPrinter->SetFont(aDefFont);
/*N*/       nPrinterWidth = pPrinter->PixelToLogic( Size( pPrinter->GetTextWidth(aTestString), 0 ),
/*N*/                                                   MAP_100TH_MM ).Width();
/*N*/       pPrinter->SetFont(aOldFont);
/*N*/       pPrinter->SetMapMode(aOldMode);
/*N*/   }
/*N*/   else
/*N*/       DBG_ERROR("kein Drucker ?!?!?");
/*N*/
/*N*/   VirtualDevice aVirtWindow( *Application::GetDefaultDevice() );
/*N*/   aVirtWindow.SetMapMode(MAP_PIXEL);
/*N*/   pPattern->GetFont(aDefFont, SC_AUTOCOL_BLACK, &aVirtWindow);    // font color doesn't matter here
/*N*/   aVirtWindow.SetFont(aDefFont);
/*N*/   nWindowWidth = aVirtWindow.GetTextWidth(aTestString);
/*N*/   nWindowWidth = (long) ( nWindowWidth / ScGlobal::nScreenPPTX * HMM_PER_TWIPS );
/*N*/
/*N*/   if (nPrinterWidth && nWindowWidth)
/*N*/       nPrtToScreenFactor = nPrinterWidth / (double) nWindowWidth;
/*N*/   else
/*N*/   {
/*N*/       DBG_ERROR("GetTextSize gibt 0 ??");
/*N*/       nPrtToScreenFactor = 1.0;
/*N*/   }
/*N*/ }

/*N*/ double ScDocShell::GetOutputFactor() const
/*N*/ {
/*N*/   return nPrtToScreenFactor;
/*N*/ }

//---------------------------------------------------------------------

/*N*/ void ScDocShell::InitOptions()            // Fortsetzung von InitNew (CLOOKs)
/*N*/ {
/*N*/   //  Einstellungen aus dem SpellCheckCfg kommen in Doc- und ViewOptions
/*N*/
/*N*/   USHORT nDefLang, nCjkLang, nCtlLang;
/*N*/   BOOL bAutoSpell, bHideAuto;
/*N*/   ScModule::GetSpellSettings( nDefLang, nCjkLang, nCtlLang, bAutoSpell, bHideAuto );
/*N*/   ScModule* pScMod = SC_MOD();
/*N*/
/*N*/   ScDocOptions  aDocOpt  = pScMod->GetDocOptions();
/*N*/   ScViewOptions aViewOpt = pScMod->GetViewOptions();
/*N*/   aDocOpt.SetAutoSpell( bAutoSpell );
/*N*/   aViewOpt.SetHideAutoSpell( bHideAuto );
/*N*/
/*N*/   // zweistellige Jahreszahleneingabe aus Extras->Optionen->Allgemein->Sonstiges
/*N*/   aDocOpt.SetYear2000( SFX_APP()->GetMiscConfig()->GetYear2000() );
/*N*/
/*N*/   aDocument.SetDocOptions( aDocOpt );
/*N*/   aDocument.SetViewOptions( aViewOpt );
/*N*/
/*N*/   //  Druck-Optionen werden jetzt direkt vor dem Drucken gesetzt
/*N*/
/*N*/   aDocument.SetLanguage( (LanguageType) nDefLang, (LanguageType) nCjkLang, (LanguageType) nCtlLang );
/*N*/ }

//---------------------------------------------------------------------

/*N*/ Printer* ScDocShell::GetDocumentPrinter()     // fuer OLE
/*N*/ {
/*N*/   return aDocument.GetPrinter();
/*N*/ }

/*N*/ SfxPrinter* ScDocShell::GetPrinter()
/*N*/ {
/*N*/   return aDocument.GetPrinter();
/*N*/ }

//STRIP001 void ScDocShell::UpdateFontList()
//STRIP001 {
//STRIP001  delete pFontList;
//STRIP001  pFontList = new FontList( GetPrinter(), Application::GetDefaultDevice() );
//STRIP001  SvxFontListItem aFontListItem( pFontList, SID_ATTR_CHAR_FONTLIST );
//STRIP001  PutItem( aFontListItem );
//STRIP001
//STRIP001  CalcOutputFactor();
//STRIP001 }

/*N*/ USHORT ScDocShell::SetPrinter( SfxPrinter* pNewPrinter, USHORT nDiffFlags )
/*N*/ {
/*N*/   if (nDiffFlags & SFX_PRINTER_PRINTER)
/*N*/   {
/*N*/       if ( aDocument.GetPrinter() != pNewPrinter )
/*N*/       {
/*N*/           aDocument.SetPrinter( pNewPrinter );
/*N*/           aDocument.SetPrintOptions();
/*N*/
/*N*/           delete pFontList;
/*N*/           pFontList = new FontList( pNewPrinter, Application::GetDefaultDevice() );
/*N*/           SvxFontListItem aFontListItem( pFontList, SID_ATTR_CHAR_FONTLIST );
/*N*/           PutItem( aFontListItem );
/*N*/
/*N*/           CalcOutputFactor();
/*N*/
/*N*/           ScModule* pScMod = SC_MOD();
/*N*/           SfxViewFrame *pFrame = SfxViewFrame::GetFirst( this );
/*N*/           while (pFrame)
/*N*/           {
/*N*/               SfxViewShell* pSh = pFrame->GetViewShell();
/*N*/               if (pSh && pSh->ISA(ScTabViewShell))
/*N*/               {
/*N*/                   ScTabViewShell* pViewSh = (ScTabViewShell*)pSh;
/*N*/                   ScInputHandler* pInputHdl = pScMod->GetInputHdl(pViewSh);
/*N*/                   if (pInputHdl)
/*N*/                       pInputHdl->UpdateRefDevice();
/*N*/               }
/*N*/               pFrame = SfxViewFrame::GetNext( *pFrame, this );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   else if (nDiffFlags & SFX_PRINTER_JOBSETUP)
/*N*/   {
/*?*/       SfxPrinter* pOldPrinter = aDocument.GetPrinter();
/*?*/       if (pOldPrinter)
/*?*/       {
/*?*/           pOldPrinter->SetJobSetup( pNewPrinter->GetJobSetup() );
/*?*/
/*?*/           //  #i6706# Call SetPrinter with the old printer again, so the drawing layer
/*?*/           //  RefDevice is set (calling ReformatAllTextObjects and rebuilding charts),
/*?*/           //  because the JobSetup (printer device settings) may affect text layout.
/*?*/           aDocument.SetPrinter( pOldPrinter );
/*?*/           CalcOutputFactor();                         // also with the new settings
/*?*/       }
/*N*/   }
/*N*/
/*N*/   if (nDiffFlags & SFX_PRINTER_OPTIONS)
/*N*/   {
/*N*/       aDocument.SetPrintOptions();        //! aus neuem Printer ???
/*N*/   }
/*N*/
/*N*/   if (nDiffFlags & (SFX_PRINTER_CHG_ORIENTATION | SFX_PRINTER_CHG_SIZE))
/*N*/   {
/*N*/       String aStyle = aDocument.GetPageStyle( GetCurTab() );
/*N*/       ScStyleSheetPool* pStPl = aDocument.GetStyleSheetPool();
/*N*/       SfxStyleSheet* pStyleSheet = (SfxStyleSheet*)pStPl->Find(aStyle, SFX_STYLE_FAMILY_PAGE);
/*N*/       if (pStyleSheet)
/*N*/       {
/*N*/           SfxItemSet& rSet = pStyleSheet->GetItemSet();
/*N*/
/*N*/           if (nDiffFlags & SFX_PRINTER_CHG_ORIENTATION)
/*N*/           {
/*N*/               const SvxPageItem& rOldItem = (const SvxPageItem&)rSet.Get(ATTR_PAGE);
/*N*/               BOOL bWasLand = rOldItem.IsLandscape();
/*N*/               BOOL bNewLand = ( pNewPrinter->GetOrientation() == ORIENTATION_LANDSCAPE );
/*N*/               if (bNewLand != bWasLand)
/*N*/               {
/*?*/                   SvxPageItem aNewItem( rOldItem );
/*?*/                   aNewItem.SetLandscape( bNewLand );
/*?*/                   rSet.Put( aNewItem );
/*?*/
/*?*/                   //  Groesse umdrehen
/*?*/                   Size aOldSize = ((const SvxSizeItem&)rSet.Get(ATTR_PAGE_SIZE)).GetSize();
/*?*/                   Size aNewSize(aOldSize.Height(),aOldSize.Width());
/*?*/                   SvxSizeItem aNewSItem(ATTR_PAGE_SIZE,aNewSize);
/*?*/                   rSet.Put( aNewSItem );
/*N*/               }
/*N*/           }
/*N*/           if (nDiffFlags & SFX_PRINTER_CHG_SIZE)
/*N*/           {
/*N*/               SvxSizeItem aPaperSizeItem( ATTR_PAGE_SIZE, SvxPaperInfo::GetPaperSize(pNewPrinter) );
/*N*/               rSet.Put( aPaperSizeItem );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   PostPaint(0,0,0,MAXCOL,MAXROW,MAXTAB,PAINT_ALL);
/*N*/
/*N*/   return 0;
/*N*/ }

//---------------------------------------------------------------------

//STRIP001 ScChangeAction* ScDocShell::GetChangeAction( const ScAddress& rPos )
//STRIP001 {
//STRIP001  ScChangeTrack* pTrack = GetDocument()->GetChangeTrack();
//STRIP001  if (!pTrack)
//STRIP001      return NULL;
//STRIP001
//STRIP001  USHORT nTab = rPos.Tab();
//STRIP001
//STRIP001  const ScChangeAction* pFound = NULL;
//STRIP001  const ScChangeAction* pFoundContent = NULL;
//STRIP001  const ScChangeAction* pFoundMove = NULL;
//STRIP001  long nModified = 0;
//STRIP001  const ScChangeAction* pAction = pTrack->GetFirst();
//STRIP001  while (pAction)
//STRIP001  {
//STRIP001      ScChangeActionType eType = pAction->GetType();
//STRIP001      //! ScViewUtil::IsActionShown( *pAction, *pSettings, *pDoc )...
//STRIP001      if ( pAction->IsVisible() && eType != SC_CAT_DELETE_TABS )
//STRIP001      {
//STRIP001          const ScBigRange& rBig = pAction->GetBigRange();
//STRIP001          if ( rBig.aStart.Tab() == nTab )
//STRIP001          {
//STRIP001              ScRange aRange = rBig.MakeRange();
//STRIP001
//STRIP001              if ( eType == SC_CAT_DELETE_ROWS )
//STRIP001                  aRange.aEnd.SetRow( aRange.aStart.Row() );
//STRIP001              else if ( eType == SC_CAT_DELETE_COLS )
//STRIP001                  aRange.aEnd.SetCol( aRange.aStart.Col() );
//STRIP001
//STRIP001              if ( aRange.In( rPos ) )
//STRIP001              {
//STRIP001                  pFound = pAction;       // der letzte gewinnt
//STRIP001                  switch ( pAction->GetType() )
//STRIP001                  {
//STRIP001                      case SC_CAT_CONTENT :
//STRIP001                          pFoundContent = pAction;
//STRIP001                      break;
//STRIP001                      case SC_CAT_MOVE :
//STRIP001                          pFoundMove = pAction;
//STRIP001                      break;
//STRIP001                  }
//STRIP001                  ++nModified;
//STRIP001              }
//STRIP001          }
//STRIP001          if ( pAction->GetType() == SC_CAT_MOVE )
//STRIP001          {
//STRIP001              ScRange aRange =
//STRIP001                  ((const ScChangeActionMove*)pAction)->
//STRIP001                  GetFromRange().MakeRange();
//STRIP001              if ( aRange.In( rPos ) )
//STRIP001              {
//STRIP001                  pFound = pAction;
//STRIP001                  ++nModified;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      pAction = pAction->GetNext();
//STRIP001  }
//STRIP001
//STRIP001  return (ScChangeAction*)pFound;
//STRIP001 }

//STRIP001 void ScDocShell::SetChangeComment( ScChangeAction* pAction, const String& rComment )
//STRIP001 {
//STRIP001  if (pAction)
//STRIP001  {
//STRIP001      pAction->SetComment( rComment );
//STRIP001      //! Undo ???
//STRIP001      SetDocumentModified();
//STRIP001
//STRIP001      //  Dialog-Notify
//STRIP001      ScChangeTrack* pTrack = GetDocument()->GetChangeTrack();
//STRIP001      if (pTrack)
//STRIP001      {
//STRIP001          ULONG nNumber = pAction->GetActionNumber();
//STRIP001          pTrack->NotifyModified( SC_CTM_CHANGE, nNumber, nNumber );
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void ScDocShell::ExecuteChangeCommentDialog( ScChangeAction* pAction, Window* pParent,BOOL bPrevNext)
//STRIP001 {
//STRIP001  if (!pAction) return;           // ohne Aktion ist nichts..
//STRIP001
//STRIP001  String aComment = pAction->GetComment();
//STRIP001  String aAuthor = pAction->GetUser();
//STRIP001
//STRIP001  DateTime aDT = pAction->GetDateTime();
//STRIP001     String aDate = ScGlobal::pLocaleData->getDate( aDT );
//STRIP001  aDate += ' ';
//STRIP001     aDate += ScGlobal::pLocaleData->getTime( aDT, FALSE, FALSE );
//STRIP001
//STRIP001  SfxItemSet aSet( GetPool(),
//STRIP001                    SID_ATTR_POSTIT_AUTHOR, SID_ATTR_POSTIT_AUTHOR,
//STRIP001                    SID_ATTR_POSTIT_DATE,   SID_ATTR_POSTIT_DATE,
//STRIP001                    SID_ATTR_POSTIT_TEXT,   SID_ATTR_POSTIT_TEXT,
//STRIP001                    0 );
//STRIP001
//STRIP001  aSet.Put( SvxPostItTextItem  ( aComment, SID_ATTR_POSTIT_TEXT ) );
//STRIP001  aSet.Put( SvxPostItAuthorItem( aAuthor,  SID_ATTR_POSTIT_AUTHOR ) );
//STRIP001  aSet.Put( SvxPostItDateItem  ( aDate,    SID_ATTR_POSTIT_DATE ) );
//STRIP001
//STRIP001  ScRedComDialog* pDlg = new ScRedComDialog( pParent, aSet,this,pAction,bPrevNext);
//STRIP001
//STRIP001  pDlg->Execute();
//STRIP001
//STRIP001  delete pDlg;
//STRIP001 }

//---------------------------------------------------------------------

//STRIP001 void ScDocShell::CompareDocument( ScDocument& rOtherDoc )
//STRIP001 {
//STRIP001  ScChangeTrack* pTrack = aDocument.GetChangeTrack();
//STRIP001  if ( pTrack && pTrack->GetFirst() )
//STRIP001  {
//STRIP001      //! Changes vorhanden -> Nachfrage ob geloescht werden soll
//STRIP001  }
//STRIP001
//STRIP001  aDocument.EndChangeTracking();
//STRIP001  aDocument.StartChangeTracking();
//STRIP001
//STRIP001  String aOldUser;
//STRIP001  pTrack = aDocument.GetChangeTrack();
//STRIP001  if ( pTrack )
//STRIP001  {
//STRIP001      aOldUser = pTrack->GetUser();
//STRIP001
//STRIP001      //  check if comparing to same document
//STRIP001
//STRIP001      String aThisFile;
//STRIP001      const SfxMedium* pThisMed = GetMedium();
//STRIP001      if (pThisMed)
//STRIP001          aThisFile = pThisMed->GetName();
//STRIP001      String aOtherFile;
//STRIP001      SfxObjectShell* pOtherSh = rOtherDoc.GetDocumentShell();
//STRIP001      if (pOtherSh)
//STRIP001      {
//STRIP001          const SfxMedium* pOtherMed = pOtherSh->GetMedium();
//STRIP001          if (pOtherMed)
//STRIP001              aOtherFile = pOtherMed->GetName();
//STRIP001      }
//STRIP001      BOOL bSameDoc = ( aThisFile == aOtherFile && aThisFile.Len() );
//STRIP001      if ( !bSameDoc )
//STRIP001      {
//STRIP001          //  create change actions from comparing with the name of the user
//STRIP001          //  who last saved the document
//STRIP001          //  (only if comparing different documents)
//STRIP001
//STRIP001          String aDocUser = GetDocInfo().GetChanged().GetName();
//STRIP001          if ( aDocUser.Len() )
//STRIP001              pTrack->SetUser( aDocUser );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  aDocument.CompareDocument( rOtherDoc );
//STRIP001
//STRIP001  pTrack = aDocument.GetChangeTrack();
//STRIP001  if ( pTrack )
//STRIP001      pTrack->SetUser( aOldUser );
//STRIP001
//STRIP001  PostPaintGridAll();
//STRIP001  SetDocumentModified();
//STRIP001 }

//---------------------------------------------------------------------
//
//              Merge (Aenderungen zusammenfuehren)
//
//---------------------------------------------------------------------

//STRIP001 inline BOOL lcl_Equal( const ScChangeAction* pA, const ScChangeAction* pB, BOOL bIgnore100Sec )
//STRIP001 {
//STRIP001  return pA && pB &&
//STRIP001         pA->GetActionNumber() == pB->GetActionNumber() &&
//STRIP001         pA->GetType()          == pB->GetType() &&
//STRIP001         pA->GetUser()          == pB->GetUser() &&
//STRIP001         (bIgnore100Sec ?
//STRIP001          pA->GetDateTimeUTC().IsEqualIgnore100Sec( pB->GetDateTimeUTC() ) :
//STRIP001          pA->GetDateTimeUTC() == pB->GetDateTimeUTC());
//STRIP001  //  State nicht vergleichen, falls eine alte Aenderung akzeptiert wurde
//STRIP001 }

//STRIP001 void ScDocShell::MergeDocument( ScDocument& rOtherDoc )
//STRIP001 {
//STRIP001  ScTabViewShell* pViewSh = GetBestViewShell();   //! Funktionen an die DocShell
//STRIP001  if (!pViewSh)
//STRIP001      return;
//STRIP001
//STRIP001  ScChangeTrack* pSourceTrack = rOtherDoc.GetChangeTrack();
//STRIP001  if (!pSourceTrack)
//STRIP001      return;             //! nichts zu tun - Fehlermeldung?
//STRIP001
//STRIP001  ScChangeTrack* pThisTrack = aDocument.GetChangeTrack();
//STRIP001  if ( !pThisTrack )
//STRIP001  {   // anschalten
//STRIP001      aDocument.StartChangeTracking();
//STRIP001      pThisTrack = aDocument.GetChangeTrack();
//STRIP001      DBG_ASSERT(pThisTrack,"ChangeTracking nicht angeschaltet?");
//STRIP001      // #51138# visuelles RedLining einschalten
//STRIP001      ScChangeViewSettings aChangeViewSet;
//STRIP001      aChangeViewSet.SetShowChanges(TRUE);
//STRIP001      aDocument.SetChangeViewSettings(aChangeViewSet);
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001     // #97286# include 100th seconds in compare?
//STRIP001     BOOL bIgnore100Sec = !pSourceTrack->IsTime100thSeconds() ||
//STRIP001             !pThisTrack->IsTime100thSeconds();
//STRIP001
//STRIP001  //  gemeinsame Ausgangsposition suchen
//STRIP001  ULONG nFirstNewNumber = 0;
//STRIP001  const ScChangeAction* pSourceAction = pSourceTrack->GetFirst();
//STRIP001  const ScChangeAction* pThisAction = pThisTrack->GetFirst();
//STRIP001     // skip identical actions
//STRIP001     while ( lcl_Equal( pSourceAction, pThisAction, bIgnore100Sec ) )
//STRIP001  {
//STRIP001      nFirstNewNumber = pSourceAction->GetActionNumber() + 1;
//STRIP001      pSourceAction = pSourceAction->GetNext();
//STRIP001      pThisAction = pThisAction->GetNext();
//STRIP001  }
//STRIP001  //  pSourceAction und pThisAction zeigen jetzt auf die ersten "eigenen" Aktionen
//STRIP001  //  Die gemeinsamen Aktionen davor interessieren ueberhaupt nicht
//STRIP001
//STRIP001  //! Abfrage, ob die Dokumente vor dem Change-Tracking gleich waren !!!
//STRIP001
//STRIP001
//STRIP001  const ScChangeAction* pFirstMergeAction = pSourceAction;
//STRIP001  //  MergeChangeData aus den folgenden Aktionen erzeugen
//STRIP001  ULONG nNewActionCount = 0;
//STRIP001  const ScChangeAction* pCount = pSourceAction;
//STRIP001  while ( pCount )
//STRIP001  {
//STRIP001      if ( !ScChangeTrack::MergeIgnore( *pCount, nFirstNewNumber ) )
//STRIP001          ++nNewActionCount;
//STRIP001      pCount = pCount->GetNext();
//STRIP001  }
//STRIP001  if (!nNewActionCount)
//STRIP001      return;             //! nichts zu tun - Fehlermeldung?
//STRIP001                          //  ab hier kein return mehr
//STRIP001
//STRIP001  ScProgress aProgress( this,
//STRIP001                  String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("...")),
//STRIP001                  nNewActionCount );
//STRIP001
//STRIP001  ULONG nLastMergeAction = pSourceTrack->GetLast()->GetActionNumber();
//STRIP001  // UpdateReference-Undo, gueltige Referenzen fuer den letzten gemeinsamen Zustand
//STRIP001  pSourceTrack->MergePrepare( (ScChangeAction*) pFirstMergeAction );
//STRIP001
//STRIP001  //  MergeChangeData an alle noch folgenden Aktionen in diesem Dokument anpassen
//STRIP001  //  -> Referenzen gueltig fuer dieses Dokument
//STRIP001  while ( pThisAction )
//STRIP001  {
//STRIP001      ScChangeActionType eType = pThisAction->GetType();
//STRIP001      switch ( eType )
//STRIP001      {
//STRIP001          case SC_CAT_INSERT_COLS :
//STRIP001          case SC_CAT_INSERT_ROWS :
//STRIP001          case SC_CAT_INSERT_TABS :
//STRIP001              pSourceTrack->AppendInsert( pThisAction->GetBigRange().MakeRange() );
//STRIP001          break;
//STRIP001          case SC_CAT_DELETE_COLS :
//STRIP001          case SC_CAT_DELETE_ROWS :
//STRIP001          case SC_CAT_DELETE_TABS :
//STRIP001          {
//STRIP001              const ScChangeActionDel* pDel = (const ScChangeActionDel*) pThisAction;
//STRIP001              if ( pDel->IsTopDelete() && !pDel->IsTabDeleteCol() )
//STRIP001              {   // deleted Table enthaelt deleted Cols, die nicht
//STRIP001                  ULONG nStart, nEnd;
//STRIP001                  pSourceTrack->AppendDeleteRange(
//STRIP001                      pDel->GetOverAllRange().MakeRange(), NULL, nStart, nEnd );
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001          case SC_CAT_MOVE :
//STRIP001          {
//STRIP001              const ScChangeActionMove* pMove = (const ScChangeActionMove*) pThisAction;
//STRIP001              pSourceTrack->AppendMove( pMove->GetFromRange().MakeRange(),
//STRIP001                  pMove->GetBigRange().MakeRange(), NULL );
//STRIP001          }
//STRIP001          break;
//STRIP001      }
//STRIP001      pThisAction = pThisAction->GetNext();
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001  //  MergeChangeData in das aktuelle Dokument uebernehmen
//STRIP001  BOOL bHasRejected = FALSE;
//STRIP001  String aOldUser = pThisTrack->GetUser();
//STRIP001  pThisTrack->SetUseFixDateTime( TRUE );
//STRIP001  ScMarkData& rMarkData = pViewSh->GetViewData()->GetMarkData();
//STRIP001  ScMarkData aOldMarkData( rMarkData );
//STRIP001  pSourceAction = pFirstMergeAction;
//STRIP001  while ( pSourceAction && pSourceAction->GetActionNumber() <= nLastMergeAction )
//STRIP001  {
//STRIP001      if ( !ScChangeTrack::MergeIgnore( *pSourceAction, nFirstNewNumber ) )
//STRIP001      {
//STRIP001          ScChangeActionType eSourceType = pSourceAction->GetType();
//STRIP001          if ( pSourceAction->IsDeletedIn() )
//STRIP001          {
//STRIP001              //! muss hier noch festgestellt werden, ob wirklich in
//STRIP001              //! _diesem_ Dokument geloescht?
//STRIP001
//STRIP001              //  liegt in einem Bereich, der in diesem Dokument geloescht wurde
//STRIP001              //  -> wird weggelassen
//STRIP001              //! ??? Loesch-Aktion rueckgaengig machen ???
//STRIP001              //! ??? Aktion irgendwo anders speichern  ???
//STRIP001 #ifndef PRODUCT
//STRIP001              String aValue;
//STRIP001              if ( eSourceType == SC_CAT_CONTENT )
//STRIP001                  ((const ScChangeActionContent*)pSourceAction)->GetNewString( aValue );
//STRIP001              ByteString aError( aValue, gsl_getSystemTextEncoding() );
//STRIP001              aError += " weggelassen";
//STRIP001              DBG_ERROR( aError.GetBuffer() );
//STRIP001 #endif
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              //! Datum/Autor/Kommentar der Source-Aktion uebernehmen!
//STRIP001
//STRIP001              pThisTrack->SetUser( pSourceAction->GetUser() );
//STRIP001              pThisTrack->SetFixDateTimeUTC( pSourceAction->GetDateTimeUTC() );
//STRIP001              ULONG nNextAction = pThisTrack->GetActionMax() + 1;
//STRIP001
//STRIP001              ULONG nReject = pSourceAction->GetRejectAction();
//STRIP001              if (nReject)
//STRIP001              {
//STRIP001                  //  alte Aktion (aus den gemeinsamen) ablehnen
//STRIP001                  ScChangeAction* pOldAction = pThisTrack->GetAction( nReject );
//STRIP001                  if (pOldAction && pOldAction->GetState() == SC_CAS_VIRGIN)
//STRIP001                  {
//STRIP001                      //! was passiert bei Aktionen, die in diesem Dokument accepted worden sind???
//STRIP001                      //! Fehlermeldung oder was???
//STRIP001                      //! oder Reject-Aenderung normal ausfuehren
//STRIP001
//STRIP001                      pThisTrack->Reject(pOldAction);
//STRIP001                      bHasRejected = TRUE;                // fuer Paint
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  //  normal ausfuehren
//STRIP001                  ScRange aSourceRange = pSourceAction->GetBigRange().MakeRange();
//STRIP001                  rMarkData.SelectOneTable( aSourceRange.aStart.Tab() );
//STRIP001                  switch ( eSourceType )
//STRIP001                  {
//STRIP001                      case SC_CAT_CONTENT:
//STRIP001                      {
//STRIP001                          //! Test, ob es ganz unten im Dokument war, dann automatisches
//STRIP001                          //! Zeilen-Einfuegen ???
//STRIP001
//STRIP001                          DBG_ASSERT( aSourceRange.aStart == aSourceRange.aEnd, "huch?" );
//STRIP001                          ScAddress aPos = aSourceRange.aStart;
//STRIP001                          String aValue;
//STRIP001                          ((const ScChangeActionContent*)pSourceAction)->GetNewString( aValue );
//STRIP001                          BYTE eMatrix = MM_NONE;
//STRIP001                          const ScBaseCell* pCell = ((const ScChangeActionContent*)pSourceAction)->GetNewCell();
//STRIP001                             if ( pCell && pCell->GetCellType() == CELLTYPE_FORMULA )
//STRIP001                              eMatrix = ((const ScFormulaCell*)pCell)->GetMatrixFlag();
//STRIP001                          switch ( eMatrix )
//STRIP001                          {
//STRIP001                              case MM_NONE :
//STRIP001                                  pViewSh->EnterData( aPos.Col(), aPos.Row(), aPos.Tab(), aValue );
//STRIP001                              break;
//STRIP001                              case MM_FORMULA :
//STRIP001                              {
//STRIP001                                  USHORT nCols, nRows;
//STRIP001                                  ((const ScFormulaCell*)pCell)->GetMatColsRows( nCols, nRows );
//STRIP001                                  aSourceRange.aEnd.SetCol( aPos.Col() + nCols - 1 );
//STRIP001                                  aSourceRange.aEnd.SetRow( aPos.Row() + nRows - 1 );
//STRIP001                                  aValue.Erase( 0, 1 );
//STRIP001                                  aValue.Erase( aValue.Len()-1, 1 );
//STRIP001                                  GetDocFunc().EnterMatrix( aSourceRange, NULL, aValue, FALSE, FALSE );
//STRIP001                              }
//STRIP001                              break;
//STRIP001                              case MM_REFERENCE :     // do nothing
//STRIP001                              break;
//STRIP001                              case MM_FAKE :
//STRIP001                                  DBG_WARNING( "MergeDocument: MatrixFlag MM_FAKE" );
//STRIP001                                  pViewSh->EnterData( aPos.Col(), aPos.Row(), aPos.Tab(), aValue );
//STRIP001                              break;
//STRIP001                              default:
//STRIP001                                  DBG_ERROR( "MergeDocument: unknown MatrixFlag" );
//STRIP001                          }
//STRIP001                      }
//STRIP001                      break;
//STRIP001                      case SC_CAT_INSERT_TABS :
//STRIP001                      {
//STRIP001                          String aName;
//STRIP001                          aDocument.CreateValidTabName( aName );
//STRIP001                          GetDocFunc().InsertTable( aSourceRange.aStart.Tab(), aName, TRUE, FALSE );
//STRIP001                      }
//STRIP001                      break;
//STRIP001                      case SC_CAT_INSERT_ROWS:
//STRIP001                          GetDocFunc().InsertCells( aSourceRange, INS_INSROWS, TRUE, FALSE );
//STRIP001                      break;
//STRIP001                      case SC_CAT_INSERT_COLS:
//STRIP001                          GetDocFunc().InsertCells( aSourceRange, INS_INSCOLS, TRUE, FALSE );
//STRIP001                      break;
//STRIP001                      case SC_CAT_DELETE_TABS :
//STRIP001                          GetDocFunc().DeleteTable( aSourceRange.aStart.Tab(), TRUE, FALSE );
//STRIP001                      break;
//STRIP001                      case SC_CAT_DELETE_ROWS:
//STRIP001                      {
//STRIP001                          const ScChangeActionDel* pDel = (const ScChangeActionDel*) pSourceAction;
//STRIP001                          if ( pDel->IsTopDelete() )
//STRIP001                          {
//STRIP001                              aSourceRange = pDel->GetOverAllRange().MakeRange();
//STRIP001                              GetDocFunc().DeleteCells( aSourceRange, DEL_DELROWS, TRUE, FALSE );
//STRIP001                          }
//STRIP001                      }
//STRIP001                      break;
//STRIP001                      case SC_CAT_DELETE_COLS:
//STRIP001                      {
//STRIP001                          const ScChangeActionDel* pDel = (const ScChangeActionDel*) pSourceAction;
//STRIP001                          if ( pDel->IsTopDelete() && !pDel->IsTabDeleteCol() )
//STRIP001                          {   // deleted Table enthaelt deleted Cols, die nicht
//STRIP001                              aSourceRange = pDel->GetOverAllRange().MakeRange();
//STRIP001                              GetDocFunc().DeleteCells( aSourceRange, DEL_DELCOLS, TRUE, FALSE );
//STRIP001                          }
//STRIP001                      }
//STRIP001                      break;
//STRIP001                      case SC_CAT_MOVE :
//STRIP001                      {
//STRIP001                          const ScChangeActionMove* pMove = (const ScChangeActionMove*) pSourceAction;
//STRIP001                          ScRange aFromRange( pMove->GetFromRange().MakeRange() );
//STRIP001                          GetDocFunc().MoveBlock( aFromRange,
//STRIP001                              aSourceRange.aStart, TRUE, TRUE, FALSE, FALSE );
//STRIP001                      }
//STRIP001                      break;
//STRIP001                  }
//STRIP001              }
//STRIP001              const String& rComment = pSourceAction->GetComment();
//STRIP001              if ( rComment.Len() )
//STRIP001              {
//STRIP001                  ScChangeAction* pAct = pThisTrack->GetLast();
//STRIP001                  if ( pAct && pAct->GetActionNumber() >= nNextAction )
//STRIP001                      pAct->SetComment( rComment );
//STRIP001 #ifndef PRODUCT
//STRIP001                  else
//STRIP001                      DBG_ERROR( "MergeDocument: wohin mit dem Kommentar?!?" );
//STRIP001 #endif
//STRIP001              }
//STRIP001
//STRIP001              // Referenzen anpassen
//STRIP001              pSourceTrack->MergeOwn( (ScChangeAction*) pSourceAction, nFirstNewNumber );
//STRIP001          }
//STRIP001          aProgress.SetStateCountDown( --nNewActionCount );
//STRIP001      }
//STRIP001      pSourceAction = pSourceAction->GetNext();
//STRIP001  }
//STRIP001  rMarkData = aOldMarkData;
//STRIP001  pThisTrack->SetUser(aOldUser);
//STRIP001  pThisTrack->SetUseFixDateTime( FALSE );
//STRIP001
//STRIP001  pSourceTrack->Clear();      //! der ist jetzt verhunzt
//STRIP001
//STRIP001  if (bHasRejected)
//STRIP001      PostPaintGridAll();         // Reject() paintet nicht selber
//STRIP001 }





}
