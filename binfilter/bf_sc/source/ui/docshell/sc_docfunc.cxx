/*************************************************************************
 *
 *  $RCSfile: sc_docfunc.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:29:05 $
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
#include "ui_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------

#include "scitems.hxx"
#include <bf_svx/eeitem.hxx>
#define ITEMID_FIELD EE_FEATURE_FIELD

#include <bf_svx/editobj.hxx>
#include <bf_svx/linkmgr.hxx>
#include <bf_svx/svdundo.hxx>
#include <bf_sfx2/bindings.hxx>
#include <bf_sfx2/printer.hxx>
#include <vcl/msgbox.hxx>
#include <vcl/sound.hxx>
#include <vcl/virdev.hxx>
#include <vcl/waitobj.hxx>
#include <svtools/zforlist.hxx>
#ifndef _SVTOOLS_PASSWORDHELPER_HXX
#include <svtools/PasswordHelper.hxx>
#endif

#include <list>

#include "docfunc.hxx"

#include "bf_sc.hrc"

#include "arealink.hxx"
#include "attrib.hxx"
#include "autoform.hxx"
#include "cell.hxx"
#include "detdata.hxx"
#include "detfunc.hxx"
#include "docpool.hxx"
#include "docsh.hxx"
#include "drwlayer.hxx"
#include "editutil.hxx"
#include "globstr.hrc"
#include "namecrea.hxx"     // NAME_TOP etc.
#include "olinetab.hxx"
#include "patattr.hxx"
#include "rangenam.hxx"
#include "rangeutl.hxx"
#include "refundo.hxx"
#include "scresid.hxx"
#include "stlpool.hxx"
#include "stlsheet.hxx"
#include "tablink.hxx"
#include "tabvwsh.hxx"
#include "uiitems.hxx"
#include "undoblk.hxx"
#include "undocell.hxx"
#include "undodraw.hxx"
#include "undotab.hxx"
#include "waitoff.hxx"
#include "sizedev.hxx"
#include "scmod.hxx"
#include "inputhdl.hxx"
#include "inputwin.hxx"
#include "editable.hxx"
namespace binfilter {

using namespace ::com::sun::star;

// STATIC DATA -----------------------------------------------------------

//========================================================================

/*N*/ IMPL_LINK( ScDocFunc, NotifyDrawUndo, SfxUndoAction*, pUndoAction )
/*N*/ {
    DBG_ASSERT(0, "STRIP"); //STRIP001 rDocShell.GetUndoManager()->AddUndoAction( new ScUndoDraw( pUndoAction, &rDocShell ) );
//STRIP001  rDocShell.SetDrawModified();
/*N*/   return 0;
/*N*/ }

//------------------------------------------------------------------------

//  Zeile ueber dem Range painten (fuer Linien nach AdjustRowHeight)

/*N*/ void lcl_PaintAbove( ScDocShell& rDocShell, const ScRange& rRange )
/*N*/ {
/*N*/   USHORT nRow = rRange.aStart.Row();
/*N*/   if ( nRow > 0 )
/*N*/   {
/*N*/       USHORT nTab = rRange.aStart.Tab();  //! alle?
/*N*/       --nRow;
/*N*/       rDocShell.PostPaint( ScRange(0,nRow,nTab, MAXCOL,nRow,nTab), PAINT_GRID );
/*N*/   }
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL ScDocFunc::AdjustRowHeight( const ScRange& rRange, BOOL bPaint )
/*N*/ {
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   if ( pDoc->IsImportingXML() )
/*N*/   {
/*N*/       //  for XML import, all row heights are updated together after importing
/*N*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   USHORT nTab      = rRange.aStart.Tab();
/*N*/   USHORT nStartRow = rRange.aStart.Row();
/*N*/   USHORT nEndRow   = rRange.aEnd.Row();
/*N*/
/*N*/   ScSizeDeviceProvider aProv( &rDocShell );
/*N*/   Fraction aOne(1,1);
/*N*/
/*N*/   BOOL bChanged = pDoc->SetOptimalHeight( nStartRow, nEndRow, nTab, 0, aProv.GetDevice(),
/*N*/                                           aProv.GetPPTX(), aProv.GetPPTY(), aOne, aOne, FALSE );
/*N*/
/*N*/   if ( bPaint && bChanged )
/*N*/       rDocShell.PostPaint( 0, nStartRow, nTab, MAXCOL, MAXROW, nTab,
/*N*/                                           PAINT_GRID | PAINT_LEFT );
/*N*/
/*N*/   return bChanged;
/*N*/ }


//------------------------------------------------------------------------

/*N*/ BOOL ScDocFunc::DetectiveAddPred(const ScAddress& rPos)
/*N*/ {
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   rDocShell.MakeDrawLayer();
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   BOOL bUndo (pDoc->IsUndoEnabled());
/*N*/   ScDrawLayer* pModel = pDoc->GetDrawLayer();
/*N*/   USHORT nCol = rPos.Col();
/*N*/   USHORT nRow = rPos.Row();
/*N*/   USHORT nTab = rPos.Tab();
/*N*/
/*N*/   if (bUndo)
/*N*/       pModel->BeginCalcUndo();
/*N*/   BOOL bDone = ScDetectiveFunc( pDoc,nTab ).ShowPred( nCol, nRow );
/*N*/   SdrUndoGroup* pUndo = NULL;
/*N*/   if (bUndo)
/*N*/       pUndo = pModel->GetCalcUndo();
/*N*/   if (bDone)
/*N*/   {
/*N*/       ScDetOpData aOperation( ScAddress(nCol,nRow,nTab), SCDETOP_ADDPRED );
/*N*/       pDoc->AddDetectiveOperation( aOperation );
/*N*/       if (bUndo)
/*N*/       {
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                        new ScUndoDetective( &rDocShell, pUndo, &aOperation ) );
/*N*/       }
/*N*/       aModificator.SetDocumentModified();
/*N*/       SfxBindings* pBindings = rDocShell.GetViewBindings();
/*N*/       if (pBindings)
/*N*/           pBindings->Invalidate( SID_DETECTIVE_REFRESH );
/*N*/   }
/*N*/   else
/*N*/       delete pUndo;
/*N*/
/*N*/   return bDone;
/*N*/ }

/*N*/ BOOL ScDocFunc::DetectiveDelPred(const ScAddress& rPos)
/*N*/ {
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/
/*N*/   BOOL bUndo(pDoc->IsUndoEnabled());
/*N*/   ScDrawLayer* pModel = pDoc->GetDrawLayer();
/*N*/   if (!pModel)
/*N*/       return FALSE;
/*N*/
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   USHORT nCol = rPos.Col();
/*N*/   USHORT nRow = rPos.Row();
/*N*/   USHORT nTab = rPos.Tab();
/*N*/
/*N*/   if (bUndo)
/*N*/       pModel->BeginCalcUndo();
/*N*/   BOOL bDone = ScDetectiveFunc( pDoc,nTab ).DeletePred( nCol, nRow );
/*N*/   SdrUndoGroup* pUndo = NULL;
/*N*/   if (bUndo)
/*N*/       pUndo = pModel->GetCalcUndo();
/*N*/   if (bDone)
/*N*/   {
/*N*/       ScDetOpData aOperation( ScAddress(nCol,nRow,nTab), SCDETOP_DELPRED );
/*N*/       pDoc->AddDetectiveOperation( aOperation );
/*N*/       if (bUndo)
/*N*/       {
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                        new ScUndoDetective( &rDocShell, pUndo, &aOperation ) );
/*N*/       }
/*N*/       aModificator.SetDocumentModified();
/*N*/       SfxBindings* pBindings = rDocShell.GetViewBindings();
/*N*/       if (pBindings)
/*N*/           pBindings->Invalidate( SID_DETECTIVE_REFRESH );
/*N*/   }
/*N*/   else
/*N*/       delete pUndo;
/*N*/
/*N*/   return bDone;
/*N*/ }

/*N*/ BOOL ScDocFunc::DetectiveAddSucc(const ScAddress& rPos)
/*N*/ {
    DBG_ASSERT(0, "STRIP"); return 0; //STRIP001 ScDocShellModificator aModificator( rDocShell );
//STRIP001
//STRIP001  rDocShell.MakeDrawLayer();
//STRIP001  ScDocument* pDoc = rDocShell.GetDocument();
//STRIP001
//STRIP001  BOOL bUndo(pDoc->IsUndoEnabled());
//STRIP001  ScDrawLayer* pModel = pDoc->GetDrawLayer();
//STRIP001  USHORT nCol = rPos.Col();
//STRIP001  USHORT nRow = rPos.Row();
//STRIP001  USHORT nTab = rPos.Tab();
//STRIP001
//STRIP001  if (bUndo)
//STRIP001      pModel->BeginCalcUndo();
//STRIP001  BOOL bDone = ScDetectiveFunc( pDoc,nTab ).ShowSucc( nCol, nRow );
//STRIP001  SdrUndoGroup* pUndo = NULL;
//STRIP001  if (bUndo)
//STRIP001      pUndo = pModel->GetCalcUndo();
//STRIP001  if (bDone)
//STRIP001  {
//STRIP001      ScDetOpData aOperation( ScAddress(nCol,nRow,nTab), SCDETOP_ADDSUCC );
//STRIP001      pDoc->AddDetectiveOperation( aOperation );
//STRIP001      if (bUndo)
//STRIP001      {
//STRIP001          rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001                      new ScUndoDetective( &rDocShell, pUndo, &aOperation ) );
//STRIP001      }
//STRIP001      aModificator.SetDocumentModified();
//STRIP001      SfxBindings* pBindings = rDocShell.GetViewBindings();
//STRIP001      if (pBindings)
//STRIP001          pBindings->Invalidate( SID_DETECTIVE_REFRESH );
//STRIP001  }
//STRIP001  else
//STRIP001      delete pUndo;
//STRIP001
//STRIP001  return bDone;
/*N*/ }

/*N*/ BOOL ScDocFunc::DetectiveDelSucc(const ScAddress& rPos)
/*N*/ {
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/
/*N*/   BOOL bUndo (pDoc->IsUndoEnabled());
/*N*/   ScDrawLayer* pModel = pDoc->GetDrawLayer();
/*N*/   if (!pModel)
/*N*/       return FALSE;
/*N*/
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   USHORT nCol = rPos.Col();
/*N*/   USHORT nRow = rPos.Row();
/*N*/   USHORT nTab = rPos.Tab();
/*N*/
/*N*/   if (bUndo)
/*N*/       pModel->BeginCalcUndo();
/*N*/   BOOL bDone = ScDetectiveFunc( pDoc,nTab ).DeleteSucc( nCol, nRow );
/*N*/   SdrUndoGroup* pUndo = NULL;
/*N*/   if (bUndo)
/*N*/       pUndo = pModel->GetCalcUndo();
/*N*/   if (bDone)
/*N*/   {
/*N*/       ScDetOpData aOperation( ScAddress(nCol,nRow,nTab), SCDETOP_DELSUCC );
/*N*/       pDoc->AddDetectiveOperation( aOperation );
/*N*/       if (bUndo)
/*N*/       {
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                        new ScUndoDetective( &rDocShell, pUndo, &aOperation ) );
/*N*/       }
/*N*/       aModificator.SetDocumentModified();
/*N*/       SfxBindings* pBindings = rDocShell.GetViewBindings();
/*N*/       if (pBindings)
/*N*/           pBindings->Invalidate( SID_DETECTIVE_REFRESH );
/*N*/   }
/*N*/   else
/*N*/       delete pUndo;
/*N*/
/*N*/   return bDone;
/*N*/ }

/*N*/ BOOL ScDocFunc::DetectiveAddError(const ScAddress& rPos)
/*N*/ {
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   rDocShell.MakeDrawLayer();
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/
/*N*/   BOOL bUndo (pDoc->IsUndoEnabled());
/*N*/   ScDrawLayer* pModel = pDoc->GetDrawLayer();
/*N*/   USHORT nCol = rPos.Col();
/*N*/   USHORT nRow = rPos.Row();
/*N*/   USHORT nTab = rPos.Tab();
/*N*/
/*N*/   if (bUndo)
/*N*/       pModel->BeginCalcUndo();
/*N*/   BOOL bDone = ScDetectiveFunc( pDoc,nTab ).ShowError( nCol, nRow );
/*N*/   SdrUndoGroup* pUndo = NULL;
/*N*/   if (bUndo)
/*N*/       pUndo = pModel->GetCalcUndo();
/*N*/   if (bDone)
/*N*/   {
/*N*/       ScDetOpData aOperation( ScAddress(nCol,nRow,nTab), SCDETOP_ADDERROR );
/*N*/       pDoc->AddDetectiveOperation( aOperation );
/*N*/       if (bUndo)
/*N*/       {
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                        new ScUndoDetective( &rDocShell, pUndo, &aOperation ) );
/*N*/       }
/*N*/       aModificator.SetDocumentModified();
/*N*/       SfxBindings* pBindings = rDocShell.GetViewBindings();
/*N*/       if (pBindings)
/*N*/           pBindings->Invalidate( SID_DETECTIVE_REFRESH );
/*N*/   }
/*N*/   else
/*N*/       delete pUndo;
/*N*/
/*N*/   return bDone;
/*N*/ }

/*N*/ BOOL ScDocFunc::DetectiveMarkInvalid(USHORT nTab)
/*N*/ {
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   rDocShell.MakeDrawLayer();
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/
/*N*/   BOOL bUndo (pDoc->IsUndoEnabled());
/*N*/   ScDrawLayer* pModel = pDoc->GetDrawLayer();
/*N*/
/*N*/   Window* pWaitWin = rDocShell.GetDialogParent();
/*N*/   if (pWaitWin)
/*N*/       pWaitWin->EnterWait();
/*N*/   if (bUndo)
/*N*/       pModel->BeginCalcUndo();
/*N*/   BOOL bOverflow;
/*N*/   BOOL bDone = ScDetectiveFunc( pDoc,nTab ).MarkInvalid( bOverflow );
/*N*/   SdrUndoGroup* pUndo = NULL;
/*N*/   if (bUndo)
/*N*/       pUndo = pModel->GetCalcUndo();
/*N*/   if (pWaitWin)
/*N*/       pWaitWin->LeaveWait();
/*N*/   if (bDone)
/*N*/   {
/*N*/       if (pUndo && bUndo)
/*N*/       {
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 pUndo->SetComment( ScGlobal::GetRscString( STR_UNDO_DETINVALID ) );
//STRIP001 /*N*/            rDocShell.GetUndoManager()->AddUndoAction( pUndo );
/*N*/       }
/*N*/       aModificator.SetDocumentModified();
/*N*/       if ( bOverflow )
/*N*/       {
/*N*/           InfoBox( NULL,
/*N*/                   ScGlobal::GetRscString( STR_DETINVALID_OVERFLOW ) ).Execute();
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/       delete pUndo;
/*N*/
/*N*/   return bDone;
/*N*/ }

/*N*/ BOOL ScDocFunc::DetectiveDelAll(USHORT nTab)
/*N*/ {
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/
/*N*/   BOOL bUndo (pDoc->IsUndoEnabled());
/*N*/   ScDrawLayer* pModel = pDoc->GetDrawLayer();
/*N*/   if (!pModel)
/*N*/       return FALSE;
/*N*/
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   if (bUndo)
/*N*/       pModel->BeginCalcUndo();
/*N*/   BOOL bDone = ScDetectiveFunc( pDoc,nTab ).DeleteAll( SC_DET_DETECTIVE );
/*N*/   SdrUndoGroup* pUndo = NULL;
/*N*/   if (bUndo)
/*N*/       pUndo = pModel->GetCalcUndo();
/*N*/   if (bDone)
/*N*/   {
/*N*/       ScDetOpList* pOldList = pDoc->GetDetOpList();
/*N*/       ScDetOpList* pUndoList = NULL;
/*N*/       if (bUndo)
/*N*/           pUndoList = pOldList ? new ScDetOpList(*pOldList) : NULL;
/*N*/
/*N*/       pDoc->ClearDetectiveOperations();
/*N*/
/*N*/       if (bUndo)
/*N*/       {
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                        new ScUndoDetective( &rDocShell, pUndo, NULL, pUndoList ) );
/*N*/       }
/*N*/       aModificator.SetDocumentModified();
/*N*/       SfxBindings* pBindings = rDocShell.GetViewBindings();
/*N*/       if (pBindings)
/*N*/           pBindings->Invalidate( SID_DETECTIVE_REFRESH );
/*N*/   }
/*N*/   else
/*N*/       delete pUndo;
/*N*/
/*N*/   return bDone;
/*N*/ }

/*N*/ BOOL ScDocFunc::DetectiveRefresh( BOOL bAutomatic )
/*N*/ {
/*N*/   BOOL bDone = FALSE;
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/
/*N*/   BOOL bUndo (pDoc->IsUndoEnabled());
/*N*/   ScDetOpList* pList = pDoc->GetDetOpList();
/*N*/   if ( pList && pList->Count() )
/*N*/   {
/*N*/       rDocShell.MakeDrawLayer();
/*N*/       ScDrawLayer* pModel = pDoc->GetDrawLayer();
/*N*/       if (bUndo)
/*N*/           pModel->BeginCalcUndo();
/*N*/
/*N*/       //  Loeschen auf allen Tabellen
/*N*/
/*N*/       USHORT nTabCount = pDoc->GetTableCount();
/*N*/       for (USHORT nTab=0; nTab<nTabCount; nTab++)
/*N*/           ScDetectiveFunc( pDoc,nTab ).DeleteAll( SC_DET_ARROWS );    // don't remove circles
/*N*/
/*N*/       //  Wiederholen
/*N*/
/*N*/       USHORT nCount = pList->Count();
/*N*/       for (USHORT i=0; i<nCount; i++)
/*N*/       {
/*N*/           ScDetOpData* pData = (*pList)[i];
/*N*/           if (pData)
/*N*/           {
/*N*/               ScAddress aPos = pData->GetPos();
/*N*/               ScDetectiveFunc aFunc( pDoc, aPos.Tab() );
/*N*/               USHORT nCol = aPos.Col();
/*N*/               USHORT nRow = aPos.Row();
/*N*/               switch (pData->GetOperation())
/*N*/               {
/*N*/                   case SCDETOP_ADDSUCC:
/*N*/                       aFunc.ShowSucc( nCol, nRow );
/*N*/                       break;
/*N*/                   case SCDETOP_DELSUCC:
/*N*/                       aFunc.DeleteSucc( nCol, nRow );
/*N*/                       break;
/*N*/                   case SCDETOP_ADDPRED:
/*N*/                       aFunc.ShowPred( nCol, nRow );
/*N*/                       break;
/*N*/                   case SCDETOP_DELPRED:
/*N*/                       aFunc.DeletePred( nCol, nRow );
/*N*/                       break;
/*N*/                   case SCDETOP_ADDERROR:
/*N*/                       aFunc.ShowError( nCol, nRow );
/*N*/                       break;
/*N*/                   default:
/*N*/                       DBG_ERROR("falsche Op bei DetectiveRefresh");
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/
/*N*/       if (bUndo)
/*N*/       {
/*N*/           SdrUndoGroup* pUndo = pModel->GetCalcUndo();
/*N*/           if (pUndo)
/*N*/           {
/*N*/               pUndo->SetComment( ScGlobal::GetRscString( STR_UNDO_DETREFRESH ) );
/*N*/               //  wenn automatisch, an letzte Aktion anhaengen
/*N*/               rDocShell.GetUndoManager()->AddUndoAction(
/*N*/                                               new ScUndoDraw( pUndo, &rDocShell ),
/*N*/                                               bAutomatic );
/*N*/           }
/*N*/       }
/*N*/       rDocShell.SetDrawModified();
/*N*/       bDone = TRUE;
/*N*/   }
/*N*/   return bDone;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL ScDocFunc::DeleteContents( const ScMarkData& rMark, USHORT nFlags,
/*N*/                                   BOOL bRecord, BOOL bApi )
/*N*/ {
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   if ( !rMark.IsMarked() && !rMark.IsMultiMarked() )
/*N*/   {
/*N*/       DBG_ERROR("ScDocFunc::DeleteContents ohne Markierung");
/*N*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/
/*N*/   if (bRecord && !pDoc->IsUndoEnabled())
/*N*/       bRecord = FALSE;
/*N*/
/*N*/   ScEditableTester aTester( pDoc, rMark );
/*N*/   if (!aTester.IsEditable())
/*N*/   {
/*N*/       if (!bApi)
/*N*/           rDocShell.ErrorMessage(aTester.GetMessageId());
/*N*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   ScRange aMarkRange;
/*N*/   BOOL bSimple = FALSE;
/*N*/
/*N*/   ScMarkData aMultiMark = rMark;
/*N*/   aMultiMark.SetMarking(FALSE);       // fuer MarkToMulti
/*N*/
/*N*/   ScDocument* pUndoDoc = NULL;
/*N*/   BOOL bMulti = !bSimple && aMultiMark.IsMultiMarked();
/*N*/   if (!bSimple)
/*N*/   {
/*N*/       aMultiMark.MarkToMulti();
/*N*/       aMultiMark.GetMultiMarkArea( aMarkRange );
/*N*/   }
/*N*/   ScRange aExtendedRange(aMarkRange);
/*N*/   if (!bSimple)
/*N*/   {
/*N*/       if ( pDoc->ExtendMerge( aExtendedRange, TRUE ) )
/*N*/           bMulti = FALSE;
/*N*/   }
/*N*/
/*N*/   // keine Objekte auf geschuetzten Tabellen
/*N*/   BOOL bObjects = FALSE;
/*N*/   if ( nFlags & IDF_OBJECTS )
/*N*/   {
/*N*/       bObjects = TRUE;
/*N*/       USHORT nTabCount = pDoc->GetTableCount();
/*N*/       for (USHORT nTab=0; nTab<nTabCount; nTab++)
/*N*/           if (aMultiMark.GetTableSelect(nTab) && pDoc->IsTabProtected(nTab))
/*N*/               bObjects = FALSE;
/*N*/   }
/*N*/
/*N*/   USHORT nExtFlags = 0;                       // Linien interessieren nur, wenn Attribute
/*N*/   if ( nFlags & IDF_ATTRIB )                  // geloescht werden
/*N*/       if (pDoc->HasAttrib( aMarkRange, HASATTR_PAINTEXT ))
/*N*/           nExtFlags |= SC_PF_LINES;
/*N*/
/*N*/   //  Reihenfolge:
/*N*/   //  1) BeginDrawUndo
/*N*/   //  2) Objekte loeschen (DrawUndo wird gefuellt)
/*N*/   //  3) Inhalte fuer Undo kopieren und Undo-Aktion anlegen
/*N*/   //  4) Inhalte loeschen
/*N*/
/*N*/   if (bObjects)
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 if (bRecord)
//STRIP001 /*?*/            pDoc->BeginDrawUndo();
//STRIP001 /*?*/
//STRIP001 /*?*/        if (bMulti)
//STRIP001 /*?*/            pDoc->DeleteObjectsInSelection( aMultiMark );
//STRIP001 /*?*/        else
//STRIP001 /*?*/            pDoc->DeleteObjectsInArea( aMarkRange.aStart.Col(), aMarkRange.aStart.Row(),
//STRIP001 /*?*/                                       aMarkRange.aEnd.Col(),   aMarkRange.aEnd.Row(),
//STRIP001 /*?*/                                       aMultiMark );
/*N*/   }
/*N*/
/*N*/   if ( bRecord )
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 /*?*/        pUndoDoc->InitUndo( pDoc, aMarkRange.aStart.Tab(), aMarkRange.aEnd.Tab() );
//STRIP001 /*?*/
//STRIP001 /*?*/        //  bei "Format/Standard" alle Attribute kopieren, weil CopyToDocument
//STRIP001 /*?*/        //  nur mit IDF_HARDATTR zu langsam ist:
//STRIP001 /*?*/        USHORT nUndoDocFlags = nFlags;
//STRIP001 /*?*/        if (nFlags & IDF_ATTRIB)
//STRIP001 /*?*/            nUndoDocFlags |= IDF_ATTRIB;
//STRIP001 /*?*/        if (nFlags & IDF_EDITATTR)          // Edit-Engine-Attribute
//STRIP001 /*?*/            nUndoDocFlags |= IDF_STRING;    // -> Zellen werden geaendert
//STRIP001 /*?*/        if (nFlags & IDF_NOTE)
//STRIP001 /*?*/            nUndoDocFlags |= IDF_CONTENTS;  // #68795# copy all cells with their notes
//STRIP001 /*?*/        pDoc->CopyToDocument( aExtendedRange, nUndoDocFlags, bMulti, pUndoDoc, &aMultiMark );
//STRIP001 /*?*/        rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/            new ScUndoDeleteContents( &rDocShell, aMultiMark, aExtendedRange,
//STRIP001 /*?*/                                      pUndoDoc, bMulti, nFlags, bObjects ) );
/*N*/   }
/*N*/
/*N*/ //!   HideAllCursors();   // falls Zusammenfassung aufgehoben wird
/*N*/   if (bSimple)
/*N*/       pDoc->DeleteArea( aMarkRange.aStart.Col(), aMarkRange.aStart.Row(),
/*N*/                         aMarkRange.aEnd.Col(),   aMarkRange.aEnd.Row(),
/*N*/                         aMultiMark, nFlags );
/*N*/   else
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 pDoc->DeleteSelection( nFlags, aMultiMark );
//STRIP001 /*?*/        aMultiMark.MarkToSimple();
/*N*/   }
/*N*/
/*N*/   if (!AdjustRowHeight( aExtendedRange ))
/*N*/       rDocShell.PostPaint( aExtendedRange, PAINT_GRID, nExtFlags );
/*N*/   else if (nExtFlags & SC_PF_LINES)
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 lcl_PaintAbove( rDocShell, aExtendedRange ); // fuer Linien ueber dem Bereich
/*N*/
/*N*/ //    rDocShell.UpdateOle(GetViewData());     //! an der View?
/*N*/   aModificator.SetDocumentModified();
/*N*/ //!   CellContentChanged();
/*N*/ //!   ShowAllCursors();
/*N*/
/*N*/ #if 0
/*N*/   //! muss an der View bleiben !!!!
/*N*/   if ( nFlags & IDF_ATTRIB )
/*N*/   {
/*N*/       if ( nFlags & IDF_CONTENTS )
/*N*/           ForgetFormatArea();
/*N*/       else
/*N*/           StartFormatArea();              // Attribute loeschen ist auch Attributierung
/*N*/   }
/*N*/ #endif
/*N*/
/*N*/   return TRUE;
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 BOOL ScDocFunc::TransliterateText( const ScMarkData& rMark, sal_Int32 nType,
//STRIP001                                  BOOL bRecord, BOOL bApi )
//STRIP001 {
//STRIP001  ScDocShellModificator aModificator( rDocShell );
//STRIP001
//STRIP001  ScDocument* pDoc = rDocShell.GetDocument();
//STRIP001  if (bRecord && !pDoc->IsUndoEnabled())
//STRIP001      bRecord = FALSE;
//STRIP001
//STRIP001  ScEditableTester aTester( pDoc, rMark );
//STRIP001  if (!aTester.IsEditable())
//STRIP001  {
//STRIP001      if (!bApi)
//STRIP001          rDocShell.ErrorMessage(aTester.GetMessageId());
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  ScRange aMarkRange;
//STRIP001  ScMarkData aMultiMark = rMark;
//STRIP001  aMultiMark.SetMarking(FALSE);       // for MarkToMulti
//STRIP001  aMultiMark.MarkToMulti();
//STRIP001  aMultiMark.GetMultiMarkArea( aMarkRange );
//STRIP001
//STRIP001  if (bRecord)
//STRIP001  {
//STRIP001      USHORT nStartTab = aMarkRange.aStart.Tab();
//STRIP001      USHORT nTabCount = pDoc->GetTableCount();
//STRIP001
//STRIP001      ScDocument* pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001      pUndoDoc->InitUndo( pDoc, nStartTab, nStartTab );
//STRIP001      for (USHORT i=0; i<nTabCount; i++)
//STRIP001          if (i != nStartTab && rMark.GetTableSelect(i))
//STRIP001              pUndoDoc->AddUndoTab( i, i );
//STRIP001
//STRIP001      ScRange aCopyRange = aMarkRange;
//STRIP001      aCopyRange.aStart.SetTab(0);
//STRIP001      aCopyRange.aEnd.SetTab(nTabCount-1);
//STRIP001      pDoc->CopyToDocument( aCopyRange, IDF_CONTENTS, TRUE, pUndoDoc, &aMultiMark );
//STRIP001
//STRIP001      rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001          new ScUndoTransliterate( &rDocShell, aMultiMark, pUndoDoc, nType ) );
//STRIP001  }
//STRIP001
//STRIP001  pDoc->TransliterateText( aMultiMark, nType );
//STRIP001
//STRIP001  if (!AdjustRowHeight( aMarkRange ))
//STRIP001      rDocShell.PostPaint( aMarkRange, PAINT_GRID );
//STRIP001
//STRIP001  aModificator.SetDocumentModified();
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ BOOL ScDocFunc::SetNormalString( const ScAddress& rPos, const String& rText, BOOL bApi )
/*N*/ {
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/
/*N*/   BOOL bUndo(pDoc->IsUndoEnabled());
/*N*/   ScEditableTester aTester( pDoc, rPos.Tab(), rPos.Col(),rPos.Row(), rPos.Col(),rPos.Row() );
/*N*/   if (!aTester.IsEditable())
/*N*/   {
/*N*/       if (!bApi)
/*N*/           rDocShell.ErrorMessage(aTester.GetMessageId());
/*N*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   USHORT* pTabs = NULL;
/*N*/   ScBaseCell** ppOldCells = NULL;
/*N*/   BOOL* pHasFormat = NULL;
/*N*/   ULONG* pOldFormats = NULL;
/*N*/   ScBaseCell* pDocCell = pDoc->GetCell( rPos );
/*N*/   BOOL bEditDeleted = (pDocCell && pDocCell->GetCellType() == CELLTYPE_EDIT);
/*N*/   if (bUndo)
/*N*/   {
/*N*/       pTabs = new USHORT[1];
/*N*/       pTabs[0] = rPos.Tab();
/*N*/       ppOldCells  = new ScBaseCell*[1];
/*N*/       ppOldCells[0] = pDocCell ? pDocCell->Clone(pDoc) : NULL;
/*N*/
/*N*/       pHasFormat = new BOOL[1];
/*N*/       pOldFormats = new ULONG[1];
/*N*/       const SfxPoolItem* pItem;
/*N*/       const ScPatternAttr* pPattern = pDoc->GetPattern( rPos.Col(),rPos.Row(),rPos.Tab() );
/*N*/       if ( SFX_ITEM_SET == pPattern->GetItemSet().GetItemState(
/*N*/                               ATTR_VALUE_FORMAT,FALSE,&pItem) )
/*N*/       {
/*N*/           pHasFormat[0] = TRUE;
/*N*/           pOldFormats[0] = ((const SfxUInt32Item*)pItem)->GetValue();
/*N*/       }
/*N*/       else
/*N*/           pHasFormat[0] = FALSE;
/*N*/   }
/*N*/
/*N*/   pDoc->SetString( rPos.Col(), rPos.Row(), rPos.Tab(), rText );
/*N*/
/*N*/   if (bUndo)
/*N*/   {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001  //  wegen ChangeTracking darf UndoAction erst nach SetString angelegt werden
//STRIP001 /*?*/        rDocShell.GetUndoManager()->AddUndoAction(new ScUndoEnterData( &rDocShell, rPos.Col(),rPos.Row(),rPos.Tab(), 1,pTabs,
//STRIP001 /*?*/                                     ppOldCells, pHasFormat, pOldFormats, rText, NULL ) );
/*N*/   }
/*N*/
/*N*/   if ( bEditDeleted || pDoc->HasAttrib( ScRange(rPos), HASATTR_NEEDHEIGHT ) )
/*N*/       AdjustRowHeight( ScRange(rPos) );
/*N*/
/*N*/   rDocShell.PostPaintCell( rPos.Col(), rPos.Row(), rPos.Tab() );
/*N*/   aModificator.SetDocumentModified();
/*N*/
/*N*/     // #107160# notify input handler here the same way as in PutCell
/*N*/     if (bApi)
/*?*/         NotifyInputHandler( rPos );
/*N*/
/*N*/   return TRUE;
/*N*/ }

/*N*/ BOOL ScDocFunc::PutCell( const ScAddress& rPos, ScBaseCell* pNewCell, BOOL bApi )
/*N*/ {
/*N*/
/*N*/     ScDocShellModificator aModificator( rDocShell );
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   BOOL bUndo (pDoc->IsUndoEnabled());
/*N*/     BOOL bXMLLoading(pDoc->IsImportingXML());
/*N*/
/*N*/     // #i925#; it is not neccessary to test whether the cell is editable on loading a XML document
/*N*/     if (!bXMLLoading)
/*N*/     {
/*N*/       ScEditableTester aTester( pDoc, rPos.Tab(), rPos.Col(),rPos.Row(), rPos.Col(),rPos.Row() );
/*N*/       if (!aTester.IsEditable())
/*N*/       {
/*N*/           if (!bApi)
/*?*/               rDocShell.ErrorMessage(aTester.GetMessageId());
/*N*/           pNewCell->Delete();
/*N*/           return FALSE;
/*N*/       }
/*N*/     }
/*N*/
/*N*/   BOOL bEditCell(FALSE);
/*N*/   BOOL bEditDeleted(FALSE);
/*N*/   BOOL bHeight;
/*N*/   ScBaseCell* pUndoCell = NULL;
/*N*/   ScBaseCell* pRedoCell = NULL;
/*N*/   if (bUndo)
/*N*/   {
/*N*/       bEditCell = ( pNewCell->GetCellType() == CELLTYPE_EDIT );
/*N*/       ScBaseCell* pDocCell = pDoc->GetCell( rPos );
/*N*/       bEditDeleted = (pDocCell && pDocCell->GetCellType() == CELLTYPE_EDIT);
/*N*/       bHeight = ( bEditDeleted || bEditCell ||
/*N*/                   pDoc->HasAttrib( ScRange(rPos), HASATTR_NEEDHEIGHT ) );
/*N*/       pUndoCell = pDocCell ? pDocCell->Clone(pDoc) : NULL;
/*N*/       pRedoCell = pNewCell ? pNewCell->Clone(pDoc) : NULL;
/*N*/   }
/*N*/
/*N*/   pDoc->PutCell( rPos, pNewCell );
/*N*/
/*N*/   //  wegen ChangeTracking darf UndoAction erst nach PutCell angelegt werden
/*N*/   if (bUndo)
/*N*/   {
/*N*/       rDocShell.GetUndoManager()->AddUndoAction(
/*N*/               new ScUndoPutCell( &rDocShell, rPos, pUndoCell, pRedoCell, bHeight ) );
/*N*/   }
/*N*/
/*N*/   if (bHeight)
/*N*/       AdjustRowHeight( ScRange(rPos) );
/*N*/
/*N*/     if (!bXMLLoading)
/*N*/       rDocShell.PostPaintCell( rPos.Col(), rPos.Row(), rPos.Tab() );
/*N*/
/*N*/     aModificator.SetDocumentModified();
/*N*/
/*N*/     // #i925#; it is not neccessary to notify on loading a XML document
/*N*/     // #103934#; notify editline and cell in edit mode
/*N*/     if (bApi && !bXMLLoading)
/*N*/         NotifyInputHandler( rPos );
/*N*/
/*N*/   return TRUE;
/*N*/ }

/*N*/ void ScDocFunc::NotifyInputHandler( const ScAddress& rPos )
/*N*/ {
/*N*/     ScTabViewShell* pViewSh = ScTabViewShell::GetActiveViewShell();
/*N*/     if ( pViewSh && pViewSh->GetViewData()->GetDocShell() == &rDocShell )
/*N*/     {
/*?*/         ScInputHandler* pInputHdl = SC_MOD()->GetInputHdl();
/*?*/         if ( pInputHdl )
/*?*/         {
/*?*/             sal_Bool bIsEditMode(pInputHdl->IsEditMode());
/*?*/
/*?*/             // set modified if in editmode, because so the string is not set in the InputWindow like in the cell
/*?*/             // (the cell shows the same like the InputWindow)
/*?*/             if (bIsEditMode)
/*?*/                 pInputHdl->SetModified();
/*?*/             pViewSh->UpdateInputHandler(FALSE, !bIsEditMode);
/*?*/         }
/*N*/     }
/*N*/ }

/*N*/       struct ScMyRememberItem
/*N*/       {
/*N*/           USHORT      nIndex;
/*N*/           SfxItemSet  aItemSet;
/*N*/
/*N*/           ScMyRememberItem(const SfxItemSet& rItemSet, USHORT nTempIndex) :
/*N*/               aItemSet(rItemSet), nIndex(nTempIndex) {}
/*N*/       };

/*N*/       typedef ::std::list<ScMyRememberItem*> ScMyRememberItemList;

/*N*/ BOOL ScDocFunc::PutData( const ScAddress& rPos, EditEngine& rEngine, BOOL bInterpret, BOOL bApi )
/*N*/ {
/*N*/   //  PutData ruft PutCell oder SetNormalString
/*N*/
/*N*/   BOOL bRet = FALSE;
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   ScEditAttrTester aTester( &rEngine );
/*N*/   BOOL bEditCell = aTester.NeedsObject();
/*N*/   if ( bEditCell )
/*N*/   {
/*N*/       sal_Bool bUpdateMode(rEngine.GetUpdateMode());
/*N*/       if (bUpdateMode)
/*N*/           rEngine.SetUpdateMode(sal_False);
/*N*/
/*N*/       ScMyRememberItemList aRememberItems;
/*N*/       ScMyRememberItem* pRememberItem = NULL;
/*N*/
/*N*/       //  All paragraph attributes must be removed before calling CreateTextObject,
/*N*/       //  not only alignment, so the object doesn't contain the cell attributes as
/*N*/       //  paragraph attributes. Before remove the attributes store they in a list to
/*N*/       //  set they back to the EditEngine.
/*N*/       USHORT nCount = rEngine.GetParagraphCount();
/*N*/       for (USHORT i=0; i<nCount; i++)
/*N*/       {
/*N*/           const SfxItemSet& rOld = rEngine.GetParaAttribs( i );
/*N*/           if ( rOld.Count() )
/*N*/           {
/*N*/               pRememberItem = new ScMyRememberItem(rEngine.GetParaAttribs(i), i);
/*N*/               aRememberItems.push_back(pRememberItem);
/*N*/               rEngine.SetParaAttribs( i, SfxItemSet( *rOld.GetPool(), rOld.GetRanges() ) );
/*N*/           }
/*N*/       }
/*N*/
/*N*/       EditTextObject* pNewData = rEngine.CreateTextObject();
/*N*/       bRet = PutCell( rPos,
/*N*/                       new ScEditCell( pNewData, pDoc, rEngine.GetEditTextObjectPool() ),
/*N*/                       bApi );
/*N*/       delete pNewData;
/*N*/
/*N*/       // Set the paragraph attributes back to the EditEngine.
/*N*/       if (!aRememberItems.empty())
/*N*/       {
/*N*/           ScMyRememberItem* pRememberItem = NULL;
/*N*/           ScMyRememberItemList::iterator aItr = aRememberItems.begin();
/*N*/           while (aItr != aRememberItems.end())
/*N*/           {
/*N*/               pRememberItem = *aItr;
/*N*/               rEngine.SetParaAttribs(pRememberItem->nIndex, pRememberItem->aItemSet);
/*N*/               delete pRememberItem;
/*N*/               aItr = aRememberItems.erase(aItr);
/*N*/           }
/*N*/       }
/*N*/
/*N*/       if (bUpdateMode)
/*N*/           rEngine.SetUpdateMode(sal_True);
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/        String aText = rEngine.GetText();
/*N*/       if ( bInterpret || !aText.Len() )
/*N*/           bRet = SetNormalString( rPos, aText, bApi );
/*N*/       else
/*N*/           bRet = PutCell( rPos, new ScStringCell( aText ), bApi );
/*N*/   }
/*N*/
/*N*/   if ( bRet && aTester.NeedsCellAttr() )
/*N*/   {
/*N*/       const SfxItemSet& rEditAttr = aTester.GetAttribs();
/*N*/       ScPatternAttr aPattern( pDoc->GetPool() );
/*N*/       aPattern.GetFromEditItemSet( &rEditAttr );
/*N*/       aPattern.DeleteUnchanged( pDoc->GetPattern( rPos.Col(), rPos.Row(), rPos.Tab() ) );
/*N*/       aPattern.GetItemSet().ClearItem( ATTR_HOR_JUSTIFY );    // wasn't removed above if no edit object
/*N*/       if ( aPattern.GetItemSet().Count() > 0 )
/*N*/       {
/*?*/           ScMarkData aMark;
/*?*/           aMark.SelectTable( rPos.Tab(), TRUE );
/*?*/           aMark.SetMarkArea( ScRange( rPos ) );
/*?*/           ApplyAttributes( aMark, aPattern, TRUE, bApi );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return bRet;
/*N*/ }


/*N*/  ScTokenArray* lcl_ScDocFunc_CreateTokenArrayXML( const String& rText )
/*N*/  {
/*N*/   ScTokenArray* pCode = new ScTokenArray;
/*N*/      pCode->AddString( rText );
/*N*/   return pCode;
/*N*/  }


/*N*/ ScBaseCell* ScDocFunc::InterpretEnglishString( const ScAddress& rPos, const String& rText )
/*N*/ {
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   ScBaseCell* pNewCell = NULL;
/*N*/
/*N*/   if ( rText.Len() > 1 && rText.GetChar(0) == '=' )
/*N*/   {
/*N*/       ScTokenArray* pCode;
/*N*/       if ( pDoc->IsImportingXML() )
/*N*/       {   // temporary formula string as string tokens
/*N*/           pCode = lcl_ScDocFunc_CreateTokenArrayXML( rText );
/*N*/             pDoc->IncXMLImportedFormulaCount( rText.Len() );
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           ScCompiler aComp( pDoc, rPos );
/*N*/           aComp.SetCompileEnglish( TRUE );
/*N*/           pCode = aComp.CompileString( rText );
/*N*/       }
/*N*/       pNewCell = new ScFormulaCell( pDoc, rPos, pCode, 0 );
/*N*/       delete pCode;   // Zell-ctor hat das TokenArray kopiert
/*N*/   }
/*N*/   else if ( rText.Len() > 1 && rText.GetChar(0) == '\'' )
/*N*/   {
/*N*/       //  for bEnglish, "'" at the beginning is always interpreted as text
/*N*/       //  marker and stripped
/*?*/       pNewCell = ScBaseCell::CreateTextCell( rText.Copy( 1 ), pDoc );
/*N*/   }
/*N*/   else        // (nur) auf englisches Zahlformat testen
/*N*/   {
/*?*/       SvNumberFormatter* pFormatter = pDoc->GetFormatTable();
/*?*/       ULONG nEnglish = pFormatter->GetStandardIndex(LANGUAGE_ENGLISH_US);
/*?*/       double fVal;
/*?*/       if ( pFormatter->IsNumberFormat( rText, nEnglish, fVal ) )
/*?*/           pNewCell = new ScValueCell( fVal );
/*?*/       else if ( rText.Len() )
/*?*/           pNewCell = ScBaseCell::CreateTextCell( rText, pDoc );
/*?*/
/*?*/       //  das (englische) Zahlformat wird nicht gesetzt
/*?*/       //! passendes lokales Format suchen und setzen???
/*N*/   }
/*N*/
/*N*/   return pNewCell;
/*N*/ }


/*N*/ BOOL ScDocFunc::SetCellText( const ScAddress& rPos, const String& rText,
/*N*/                               BOOL bInterpret, BOOL bEnglish, BOOL bApi )
/*N*/ {
/*N*/   //  SetCellText ruft PutCell oder SetNormalString
/*N*/
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   ScBaseCell* pNewCell = NULL;
/*N*/   if ( bInterpret )
/*N*/   {
/*N*/       if ( bEnglish )
/*N*/       {
/*N*/           //  code moved to own method InterpretEnglishString because it is also used in
/*N*/           //  ScCellRangeObj::setFormulaArray
/*N*/
/*N*/           pNewCell = InterpretEnglishString( rPos, rText );
/*N*/       }
/*N*/       // sonst Null behalten -> SetString mit lokalen Formeln/Zahlformat
/*N*/   }
/*N*/   else if ( rText.Len() )
/*N*/       pNewCell = ScBaseCell::CreateTextCell( rText, pDoc );   // immer Text
/*N*/
/*N*/   if (pNewCell)
/*N*/       return PutCell( rPos, pNewCell, bApi );
/*N*/   else
/*?*/       return SetNormalString( rPos, rText, bApi );
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL ScDocFunc::SetNoteText( const ScAddress& rPos, const String& rText, BOOL bApi )
/*N*/ {
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   ScEditableTester aTester( pDoc, rPos.Tab(), rPos.Col(),rPos.Row(), rPos.Col(),rPos.Row() );
/*N*/   if (!aTester.IsEditable())
/*N*/   {
/*?*/       if (!bApi)
/*?*/           rDocShell.ErrorMessage(aTester.GetMessageId());
/*?*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   String aNewText = rText;
/*N*/   aNewText.ConvertLineEnd();      //! ist das noetig ???
/*N*/
/*N*/   ScPostIt aNote;
/*N*/   pDoc->GetNote( rPos.Col(), rPos.Row(), rPos.Tab(), aNote );
/*N*/   aNote.AutoSetText( aNewText );      // setzt auch Author und Date
/*N*/   pDoc->SetNote( rPos.Col(), rPos.Row(), rPos.Tab(), aNote );
/*N*/
/*N*/   if ( aNote.IsShown() )
/*N*/   {
/*N*/       //  Zeichenobjekt updaten
/*N*/       //! bei gelocktem Paint auch erst spaeter !!!
/*N*/
/*N*/       ScDetectiveFunc aDetFunc( pDoc, rPos.Tab() );
/*N*/       aDetFunc.HideComment( rPos.Col(), rPos.Row() );
/*N*/       aDetFunc.ShowComment( rPos.Col(), rPos.Row(), FALSE );  // FALSE: nur wenn gefunden
/*N*/   }
/*N*/
/*N*/   //! Undo !!!
/*N*/
/*N*/   rDocShell.PostPaintCell( rPos.Col(), rPos.Row(), rPos.Tab() );
/*N*/   aModificator.SetDocumentModified();
/*N*/
/*N*/   return TRUE;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL ScDocFunc::ApplyAttributes( const ScMarkData& rMark, const ScPatternAttr& rPattern,
/*N*/                                   BOOL bRecord, BOOL bApi )
/*N*/ {
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   if ( bRecord && !pDoc->IsUndoEnabled() )
/*N*/       bRecord = FALSE;
/*N*/
/*N*/   // nur wegen Matrix nicht editierbar? Attribute trotzdem ok
/*N*/   BOOL bOnlyNotBecauseOfMatrix;
/*N*/   if ( !pDoc->IsSelectionEditable( rMark, &bOnlyNotBecauseOfMatrix )
/*N*/           && !bOnlyNotBecauseOfMatrix )
/*N*/   {
/*?*/       if (!bApi)
/*?*/           rDocShell.ErrorMessage(STR_PROTECTIONERR);
/*?*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   //! Umrandung
/*N*/
/*N*/   ScRange aMultiRange;
/*N*/   BOOL bMulti = rMark.IsMultiMarked();
/*N*/   if ( bMulti )
/*N*/       rMark.GetMultiMarkArea( aMultiRange );
/*N*/   else
/*N*/       rMark.GetMarkArea( aMultiRange );
/*N*/
/*N*/   if ( bRecord )
/*N*/   {
/*N*/       ScDocument* pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
/*N*/       pUndoDoc->InitUndo( pDoc, aMultiRange.aStart.Tab(), aMultiRange.aEnd.Tab() );
/*N*/       pDoc->CopyToDocument( aMultiRange, IDF_ATTRIB, bMulti, pUndoDoc, &rMark );
/*N*/
/*N*/       rDocShell.GetUndoManager()->AddUndoAction(
/*N*/           new ScUndoSelectionAttr(
/*N*/                   &rDocShell, rMark,
/*N*/                   aMultiRange.aStart.Col(), aMultiRange.aStart.Row(), aMultiRange.aStart.Tab(),
/*N*/                   aMultiRange.aEnd.Col(), aMultiRange.aEnd.Row(), aMultiRange.aEnd.Tab(),
/*N*/                   pUndoDoc, bMulti, &rPattern ) );
/*N*/   }
/*N*/
/*N*/   // While loading XML it is not neccessary to ask HasAttrib. It needs too much time.
/*N*/   BOOL bPaintExt = pDoc->IsImportingXML() || pDoc->HasAttrib( aMultiRange, HASATTR_PAINTEXT );
/*N*/   pDoc->ApplySelectionPattern( rPattern, rMark );
/*N*/
/*N*/   if (!bPaintExt)
/*N*/       bPaintExt = pDoc->HasAttrib( aMultiRange, HASATTR_PAINTEXT );
/*N*/   USHORT nExtFlags = bPaintExt ? SC_PF_LINES : 0;
/*N*/   if (!AdjustRowHeight( aMultiRange ))
/*N*/       rDocShell.PostPaint( aMultiRange, PAINT_GRID, nExtFlags );
/*N*/   else if (nExtFlags & SC_PF_LINES)
/*N*/   lcl_PaintAbove( rDocShell, aMultiRange );   // fuer Linien ueber dem Bereich
/*N*/
/*N*/   aModificator.SetDocumentModified();
/*N*/
/*N*/   return TRUE;
/*N*/ }


/*N*/ BOOL ScDocFunc::ApplyStyle( const ScMarkData& rMark, const String& rStyleName,
/*N*/                                   BOOL bRecord, BOOL bApi )
/*N*/ {
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   if ( bRecord && !pDoc->IsUndoEnabled() )
/*N*/       bRecord = FALSE;
/*N*/
/*N*/   // nur wegen Matrix nicht editierbar? Attribute trotzdem ok
/*N*/   BOOL bOnlyNotBecauseOfMatrix;
/*N*/   if ( !pDoc->IsSelectionEditable( rMark, &bOnlyNotBecauseOfMatrix )
/*N*/           && !bOnlyNotBecauseOfMatrix )
/*N*/   {
/*?*/       if (!bApi)
/*?*/           rDocShell.ErrorMessage(STR_PROTECTIONERR);
/*?*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   ScStyleSheet* pStyleSheet = (ScStyleSheet*) pDoc->GetStyleSheetPool()->Find(
/*N*/                                               rStyleName, SFX_STYLE_FAMILY_PARA );
/*N*/   if (!pStyleSheet)
/*N*/       return FALSE;
/*N*/
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   ScRange aMultiRange;
/*N*/   BOOL bMulti = rMark.IsMultiMarked();
/*N*/   if ( bMulti )
/*N*/       rMark.GetMultiMarkArea( aMultiRange );
/*N*/   else
/*N*/       rMark.GetMarkArea( aMultiRange );
/*N*/
/*N*/   if ( bRecord )
/*N*/   {
/*N*/       ScDocument* pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
/*N*/       USHORT nStartTab = aMultiRange.aStart.Tab();
/*N*/       USHORT nTabCount = pDoc->GetTableCount();
/*N*/       pUndoDoc->InitUndo( pDoc, nStartTab, nStartTab );
/*N*/       for (USHORT i=0; i<nTabCount; i++)
/*N*/           if (i != nStartTab && rMark.GetTableSelect(i))
/*?*/               pUndoDoc->AddUndoTab( i, i );
/*N*/
/*N*/       ScRange aCopyRange = aMultiRange;
/*N*/       aCopyRange.aStart.SetTab(0);
/*N*/       aCopyRange.aEnd.SetTab(nTabCount-1);
/*N*/       pDoc->CopyToDocument( aCopyRange, IDF_ATTRIB, bMulti, pUndoDoc, &rMark );
/*N*/
/*N*/       rDocShell.GetUndoManager()->AddUndoAction(
/*N*/           new ScUndoSelectionStyle(
/*N*/                   &rDocShell, rMark, aMultiRange, rStyleName, pUndoDoc ) );
/*N*/
/*N*/   }
/*N*/
/*N*/ //    BOOL bPaintExt = pDoc->HasAttrib( aMultiRange, HASATTR_PAINTEXT );
/*N*/ //    pDoc->ApplySelectionPattern( rPattern, rMark );
/*N*/
/*N*/   pDoc->ApplySelectionStyle( (ScStyleSheet&)*pStyleSheet, rMark );
/*N*/
/*N*/ //    if (!bPaintExt)
/*N*/ //        bPaintExt = pDoc->HasAttrib( aMultiRange, HASATTR_PAINTEXT );
/*N*/ //    USHORT nExtFlags = bPaintExt ? SC_PF_LINES : 0;
/*N*/   USHORT nExtFlags = 0;
/*N*/   if (!AdjustRowHeight( aMultiRange ))
/*N*/       rDocShell.PostPaint( aMultiRange, PAINT_GRID, nExtFlags );
/*N*/   else if (nExtFlags & SC_PF_LINES)
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 lcl_PaintAbove( rDocShell, aMultiRange );    // fuer Linien ueber dem Bereich
/*N*/
/*N*/   aModificator.SetDocumentModified();
/*N*/
/*N*/   return TRUE;
/*N*/ }

//------------------------------------------------------------------------

/*M*/ BOOL ScDocFunc::InsertCells( const ScRange& rRange, InsCellCmd eCmd,
/*N*/                               BOOL bRecord, BOOL bApi, BOOL bPartOfPaste )
/*M*/ {
/*M*/   DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001 ScDocShellModificator aModificator( rDocShell );
//STRIP001
//STRIP001  USHORT nStartCol = rRange.aStart.Col();
//STRIP001  USHORT nStartRow = rRange.aStart.Row();
//STRIP001  USHORT nStartTab = rRange.aStart.Tab();
//STRIP001  USHORT nEndCol = rRange.aEnd.Col();
//STRIP001  USHORT nEndRow = rRange.aEnd.Row();
//STRIP001  USHORT nEndTab = rRange.aEnd.Tab();
//STRIP001
//STRIP001  if ( nStartRow > MAXROW || nEndRow > MAXROW )
//STRIP001  {
//STRIP001      DBG_ERROR("invalid row in InsertCells");
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  USHORT nTab = nStartTab;
//STRIP001  ScDocument* pDoc = rDocShell.GetDocument();
//STRIP001  USHORT nTabCount = pDoc->GetTableCount();
//STRIP001  USHORT nPaintStartX = nStartCol;
//STRIP001  USHORT nPaintStartY = nStartRow;
//STRIP001  USHORT nPaintEndX = nEndCol;
//STRIP001  USHORT nPaintEndY = nEndRow;
//STRIP001  USHORT nPaintFlags = PAINT_GRID;
//STRIP001  BOOL bSuccess;
//STRIP001
//STRIP001  if (bRecord && !pDoc->IsUndoEnabled())
//STRIP001      bRecord = FALSE;
//STRIP001
//STRIP001  //  zugehoerige Szenarien auch anpassen
//STRIP001  if ( !pDoc->IsScenario(nEndTab) )
//STRIP001      while ( nEndTab+1 < nTabCount && pDoc->IsScenario(nEndTab+1) )
//STRIP001          ++nEndTab;
//STRIP001
//STRIP001                  // Test zusammengefasste
//STRIP001
//STRIP001  USHORT nMergeTestStartX = nStartCol;
//STRIP001  USHORT nMergeTestStartY = nStartRow;
//STRIP001  USHORT nMergeTestEndX = nEndCol;
//STRIP001  USHORT nMergeTestEndY = nEndRow;
//STRIP001
//STRIP001  if (eCmd==INS_INSROWS)
//STRIP001  {
//STRIP001      nMergeTestStartX = 0;
//STRIP001      nMergeTestEndX = MAXCOL;
//STRIP001  }
//STRIP001  if (eCmd==INS_INSCOLS)
//STRIP001  {
//STRIP001      nMergeTestStartY = 0;
//STRIP001      nMergeTestEndY = MAXROW;
//STRIP001  }
//STRIP001  if (eCmd==INS_CELLSDOWN)
//STRIP001      nMergeTestEndY = MAXROW;
//STRIP001  if (eCmd==INS_CELLSRIGHT)
//STRIP001      nMergeTestEndX = MAXCOL;
//STRIP001
//STRIP001  BOOL bCanDo = TRUE;
//STRIP001  BOOL bNeedRefresh = FALSE;
//STRIP001
//STRIP001  USHORT nEditTestEndX = (eCmd==INS_INSCOLS) ? MAXCOL : nMergeTestEndX;
//STRIP001  USHORT nEditTestEndY = (eCmd==INS_INSROWS) ? MAXROW : nMergeTestEndY;
//STRIP001  ScEditableTester aTester( pDoc, nTab, nMergeTestStartX,nMergeTestStartY, nEditTestEndX,nEditTestEndY );
//STRIP001  if (!aTester.IsEditable())
//STRIP001  {
//STRIP001      if (!bApi)
//STRIP001          rDocShell.ErrorMessage(aTester.GetMessageId());
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  if (pDoc->HasAttrib( nMergeTestStartX,nMergeTestStartY,nTab,
//STRIP001                          nMergeTestEndX,nMergeTestEndY,nTab,
//STRIP001                          HASATTR_MERGED | HASATTR_OVERLAPPED ))
//STRIP001  {
//STRIP001      if (eCmd==INS_CELLSRIGHT)
//STRIP001          bNeedRefresh = TRUE;
//STRIP001
//STRIP001      USHORT nMergeStartX = nMergeTestStartX;
//STRIP001      USHORT nMergeStartY = nMergeTestStartY;
//STRIP001      USHORT nMergeEndX   = nMergeTestEndX;
//STRIP001      USHORT nMergeEndY   = nMergeTestEndY;
//STRIP001
//STRIP001      pDoc->ExtendMerge( nMergeStartX, nMergeStartY, nMergeEndX, nMergeEndY, nTab );
//STRIP001      pDoc->ExtendOverlapped( nMergeStartX, nMergeStartY, nMergeEndX, nMergeEndY, nTab );
//STRIP001      if ( nMergeStartX != nMergeTestStartX || nMergeStartY != nMergeTestStartY ||
//STRIP001           nMergeEndX   != nMergeTestEndX   || nMergeEndY   != nMergeTestEndY )
//STRIP001          bCanDo = FALSE;
//STRIP001
//STRIP001      //!     ? nur Start testen ?
//STRIP001
//STRIP001      if (!bCanDo)
//STRIP001          if ( eCmd==INS_INSCOLS || eCmd==INS_INSROWS )
//STRIP001              if ( nMergeStartX == nMergeTestStartX && nMergeStartY == nMergeTestStartY )
//STRIP001              {
//STRIP001                  bCanDo = TRUE;
//STRIP001 //                   bNeedRefresh = TRUE;
//STRIP001              }
//STRIP001  }
//STRIP001
//STRIP001  if (!bCanDo)
//STRIP001  {
//STRIP001      //!         auf Verschieben (Drag&Drop) zurueckfuehren !!!
//STRIP001      //  "Kann nicht in zusammengefasste Bereiche einfuegen"
//STRIP001      if (!bApi)
//STRIP001          rDocShell.ErrorMessage(STR_MSSG_INSERTCELLS_0);
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  //
//STRIP001  //      ausfuehren
//STRIP001  //
//STRIP001
//STRIP001  WaitObject aWait( rDocShell.GetDialogParent() );        // wichtig wegen TrackFormulas bei UpdateReference
//STRIP001
//STRIP001  ScDocument* pRefUndoDoc = NULL;
//STRIP001  ScRefUndoData* pUndoData = NULL;
//STRIP001  if ( bRecord )
//STRIP001  {
//STRIP001      pRefUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001      pRefUndoDoc->InitUndo( pDoc, 0, nTabCount-1, FALSE, FALSE );
//STRIP001
//STRIP001      // pRefUndoDoc is filled in InsertCol / InsertRow
//STRIP001
//STRIP001      pUndoData = new ScRefUndoData( pDoc );
//STRIP001
//STRIP001      pDoc->BeginDrawUndo();
//STRIP001  }
//STRIP001
//STRIP001  switch (eCmd)
//STRIP001  {
//STRIP001      case INS_CELLSDOWN:
//STRIP001          bSuccess = pDoc->InsertRow( nStartCol,nStartTab, nEndCol,nEndTab,
//STRIP001                                      nStartRow, nEndRow-nStartRow+1, pRefUndoDoc );
//STRIP001          nPaintEndY = MAXROW;
//STRIP001          break;
//STRIP001      case INS_INSROWS:
//STRIP001          bSuccess = pDoc->InsertRow( 0,nStartTab, MAXCOL,nEndTab,
//STRIP001                                      nStartRow, nEndRow-nStartRow+1, pRefUndoDoc );
//STRIP001          nPaintStartX = 0;
//STRIP001          nPaintEndX = MAXCOL;
//STRIP001          nPaintEndY = MAXROW;
//STRIP001          nPaintFlags |= PAINT_LEFT;
//STRIP001          break;
//STRIP001      case INS_CELLSRIGHT:
//STRIP001          bSuccess = pDoc->InsertCol( nStartRow,nStartTab, nEndRow,nEndTab,
//STRIP001                                      nStartCol, nEndCol-nStartCol+1, pRefUndoDoc );
//STRIP001          nPaintEndX = MAXCOL;
//STRIP001          break;
//STRIP001      case INS_INSCOLS:
//STRIP001          bSuccess = pDoc->InsertCol( 0,nStartTab, MAXROW,nEndTab,
//STRIP001                                      nStartCol, nEndCol-nStartCol+1, pRefUndoDoc );
//STRIP001          nPaintStartY = 0;
//STRIP001          nPaintEndY = MAXROW;
//STRIP001          nPaintEndX = MAXCOL;
//STRIP001          nPaintFlags |= PAINT_TOP;
//STRIP001          break;
//STRIP001      default:
//STRIP001          DBG_ERROR("Falscher Code beim Einfuegen");
//STRIP001          bSuccess = FALSE;
//STRIP001          break;
//STRIP001  }
//STRIP001
//STRIP001  if ( bSuccess )
//STRIP001  {
//STRIP001      if ( bRecord )
//STRIP001      {
//STRIP001          rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001              new ScUndoInsertCells( &rDocShell, ScRange(
//STRIP001                                              nStartCol,nStartRow,nStartTab,
//STRIP001                                              nEndCol,nEndRow,nEndTab ),
//STRIP001                                      eCmd, pRefUndoDoc, pUndoData, bPartOfPaste ) );
//STRIP001      }
//STRIP001
//STRIP001      if (bNeedRefresh)
//STRIP001          pDoc->ExtendMerge( nMergeTestStartX,nMergeTestStartY,
//STRIP001                              nMergeTestEndX,nMergeTestEndY, nTab, TRUE );
//STRIP001      else
//STRIP001          pDoc->RefreshAutoFilter( nMergeTestStartX,nMergeTestStartY,
//STRIP001                                      nMergeTestEndX,nMergeTestEndY, nTab);
//STRIP001
//STRIP001      if ( eCmd == INS_INSROWS || eCmd == INS_INSCOLS )
//STRIP001          pDoc->UpdatePageBreaks( nTab );
//STRIP001
//STRIP001      USHORT nExtFlags = 0;
//STRIP001      if (pDoc->HasAttrib( nPaintStartX,nPaintStartY,nTab,
//STRIP001                              nPaintEndX,nPaintEndY,nTab, HASATTR_PAINTEXT ))
//STRIP001          nExtFlags |= SC_PF_LINES;
//STRIP001
//STRIP001      //  ganze Zeilen einfuegen: nur neue Zeilen anpassen
//STRIP001      BOOL bAdjusted = ( eCmd == INS_INSROWS ) ?
//STRIP001              AdjustRowHeight(ScRange(0,nStartRow,nStartTab, MAXCOL,nEndRow,nEndTab)) :
//STRIP001              AdjustRowHeight(ScRange(0,nPaintStartY,nStartTab, MAXCOL,nPaintEndY,nEndTab));
//STRIP001      if (bAdjusted)
//STRIP001      {
//STRIP001          //  paint only what is not done by AdjustRowHeight
//STRIP001          if (nPaintFlags & PAINT_TOP)
//STRIP001              rDocShell.PostPaint( nPaintStartX, nPaintStartY, nStartTab,
//STRIP001                                   nPaintEndX,   nPaintEndY,   nEndTab,   PAINT_TOP );
//STRIP001      }
//STRIP001      else
//STRIP001          rDocShell.PostPaint( nPaintStartX, nPaintStartY, nStartTab,
//STRIP001                               nPaintEndX,   nPaintEndY,   nEndTab,
//STRIP001                               nPaintFlags,  nExtFlags);
//STRIP001      aModificator.SetDocumentModified();
//STRIP001
//STRIP001 //!      pDocSh->UpdateOle(GetViewData());   // muss an der View bleiben
//STRIP001 //!      CellContentChanged();               // muss an der View bleiben
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      delete pRefUndoDoc;
//STRIP001      delete pUndoData;
//STRIP001      if (!bApi)
//STRIP001          rDocShell.ErrorMessage(STR_INSERT_FULL);        // Spalte/Zeile voll
//STRIP001  }
//STRIP001  return bSuccess;
/*M*/ }

/*N*/ BOOL ScDocFunc::DeleteCells( const ScRange& rRange, DelCellCmd eCmd, BOOL bRecord, BOOL bApi )
/*N*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001 ScDocShellModificator aModificator( rDocShell );
//STRIP001 /*?*/
//STRIP001 /*?*/    USHORT nStartCol = rRange.aStart.Col();
//STRIP001 /*?*/    USHORT nStartRow = rRange.aStart.Row();
//STRIP001 /*?*/    USHORT nStartTab = rRange.aStart.Tab();
//STRIP001 /*?*/    USHORT nEndCol = rRange.aEnd.Col();
//STRIP001 /*?*/    USHORT nEndRow = rRange.aEnd.Row();
//STRIP001 /*?*/    USHORT nEndTab = rRange.aEnd.Tab();
//STRIP001 /*?*/
//STRIP001 /*?*/    if ( nStartRow > MAXROW || nEndRow > MAXROW )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        DBG_ERROR("invalid row in DeleteCells");
//STRIP001 /*?*/        return FALSE;
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    USHORT nTab = nStartTab;
//STRIP001 /*?*/    ScDocument* pDoc = rDocShell.GetDocument();
//STRIP001 /*?*/    USHORT nTabCount = pDoc->GetTableCount();
//STRIP001 /*?*/    USHORT nPaintStartX = nStartCol;
//STRIP001 /*?*/    USHORT nPaintStartY = nStartRow;
//STRIP001 /*?*/    USHORT nPaintEndX = nEndCol;
//STRIP001 /*?*/    USHORT nPaintEndY = nEndRow;
//STRIP001 /*?*/    USHORT nPaintFlags = PAINT_GRID;
//STRIP001 /*?*/
//STRIP001 /*?*/    if (bRecord && !pDoc->IsUndoEnabled())
//STRIP001 /*?*/        bRecord = FALSE;
//STRIP001 /*?*/
//STRIP001 /*?*/    //  zugehoerige Szenarien auch anpassen
//STRIP001 /*?*/    if ( !pDoc->IsScenario(nEndTab) )
//STRIP001 /*?*/        while ( nEndTab+1 < nTabCount && pDoc->IsScenario(nEndTab+1) )
//STRIP001 /*?*/            ++nEndTab;
//STRIP001 /*?*/
//STRIP001 /*?*/    USHORT nUndoStartX = nStartCol;
//STRIP001 /*?*/    USHORT nUndoStartY = nStartRow;
//STRIP001 /*?*/    USHORT nUndoEndX = nEndCol;
//STRIP001 /*?*/    USHORT nUndoEndY = nEndRow;
//STRIP001 /*?*/
//STRIP001 /*?*/    if (eCmd==DEL_DELROWS)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        nUndoStartX = 0;
//STRIP001 /*?*/        nUndoEndX = MAXCOL;
//STRIP001 /*?*/    }
//STRIP001 /*?*/    if (eCmd==DEL_DELCOLS)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        nUndoStartY = 0;
//STRIP001 /*?*/        nUndoEndY = MAXROW;
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    USHORT nDelEndX = nUndoEndX;
//STRIP001 /*?*/    if (eCmd==DEL_CELLSLEFT||eCmd==DEL_DELCOLS) nDelEndX = MAXCOL;
//STRIP001 /*?*/    USHORT nDelEndY = nUndoEndY;
//STRIP001 /*?*/    if (eCmd==DEL_CELLSUP||eCmd==DEL_DELROWS) nDelEndY = MAXROW;
//STRIP001 /*?*/
//STRIP001 /*?*/                    // Test Zellschutz
//STRIP001 /*?*/
//STRIP001 /*?*/    USHORT nEditTestEndX = nUndoEndX;
//STRIP001 /*?*/    if ( eCmd==DEL_DELCOLS || eCmd==DEL_CELLSLEFT ) nEditTestEndX = MAXCOL;
//STRIP001 /*?*/    USHORT nEditTestEndY = nUndoEndY;
//STRIP001 /*?*/    if ( eCmd==DEL_DELROWS || eCmd==DEL_CELLSUP ) nEditTestEndY = MAXROW;
//STRIP001 /*?*/    ScEditableTester aTester( pDoc, nTab, nUndoStartX,nUndoStartY,nEditTestEndX,nEditTestEndY );
//STRIP001 /*?*/    if (!aTester.IsEditable())
//STRIP001 /*?*/    {
//STRIP001 /*?*/        if (!bApi)
//STRIP001 /*?*/            rDocShell.ErrorMessage(aTester.GetMessageId());
//STRIP001 /*?*/        return FALSE;
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/                    // Test zusammengefasste
//STRIP001 /*?*/
//STRIP001 /*?*/    USHORT nMergeTestEndX = (eCmd==DEL_CELLSLEFT) ? MAXCOL : nUndoEndX;
//STRIP001 /*?*/    USHORT nMergeTestEndY = (eCmd==DEL_CELLSUP)   ? MAXROW : nUndoEndY;
//STRIP001 /*?*/    BOOL bCanDo = TRUE;
//STRIP001 /*?*/    BOOL bNeedRefresh = FALSE;
//STRIP001 /*?*/
//STRIP001 /*?*/    if (pDoc->HasAttrib( nUndoStartX,nUndoStartY,nTab, nMergeTestEndX,nMergeTestEndY,nTab,
//STRIP001 /*?*/                            HASATTR_MERGED | HASATTR_OVERLAPPED ))
//STRIP001 /*?*/    {
//STRIP001 /*?*/        if (eCmd==DEL_CELLSLEFT)
//STRIP001 /*?*/            bNeedRefresh = TRUE;
//STRIP001 /*?*/
//STRIP001 /*?*/        USHORT nMergeStartX = nUndoStartX;
//STRIP001 /*?*/        USHORT nMergeStartY = nUndoStartY;
//STRIP001 /*?*/        USHORT nMergeEndX   = nMergeTestEndX;
//STRIP001 /*?*/        USHORT nMergeEndY   = nMergeTestEndY;
//STRIP001 /*?*/
//STRIP001 /*?*/        pDoc->ExtendMerge( nMergeStartX, nMergeStartY, nMergeEndX, nMergeEndY, nTab );
//STRIP001 /*?*/        pDoc->ExtendOverlapped( nMergeStartX, nMergeStartY, nMergeEndX, nMergeEndY, nTab );
//STRIP001 /*?*/        if ( nMergeStartX != nUndoStartX  || nMergeStartY != nUndoStartY ||
//STRIP001 /*?*/             nMergeEndX != nMergeTestEndX || nMergeEndY != nMergeTestEndY )
//STRIP001 /*?*/            bCanDo = FALSE;
//STRIP001 /*?*/
//STRIP001 /*?*/        //      ganze Zeilen/Spalten: Testen, ob Merge komplett geloescht werden kann
//STRIP001 /*?*/
//STRIP001 /*?*/        if (!bCanDo)
//STRIP001 /*?*/            if ( eCmd==DEL_DELCOLS || eCmd==DEL_DELROWS )
//STRIP001 /*?*/                if ( nMergeStartX == nUndoStartX && nMergeStartY == nUndoStartY )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    bCanDo = TRUE;
//STRIP001 /*?*/                    bNeedRefresh = TRUE;
//STRIP001 /*?*/                }
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    if (!bCanDo)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        //!         auf Verschieben (Drag&Drop) zurueckfuehren !!!
//STRIP001 /*?*/        //  "Kann nicht aus zusammengefassten Bereichen loeschen"
//STRIP001 /*?*/        if (!bApi)
//STRIP001 /*?*/            rDocShell.ErrorMessage(STR_MSSG_DELETECELLS_0);
//STRIP001 /*?*/        return FALSE;
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    //
//STRIP001 /*?*/    //      ausfuehren
//STRIP001 /*?*/    //
//STRIP001 /*?*/
//STRIP001 /*?*/    WaitObject aWait( rDocShell.GetDialogParent() );        // wichtig wegen TrackFormulas bei UpdateReference
//STRIP001 /*?*/
//STRIP001 /*?*/    ScDocument* pUndoDoc = NULL;
//STRIP001 /*?*/    ScDocument* pRefUndoDoc = NULL;
//STRIP001 /*?*/    ScRefUndoData* pUndoData = NULL;
//STRIP001 /*?*/    if ( bRecord )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 /*?*/        pUndoDoc->InitUndo( pDoc, nStartTab, nEndTab,
//STRIP001 /*?*/                                (eCmd==DEL_DELCOLS), (eCmd==DEL_DELROWS) );
//STRIP001 /*?*/        pDoc->CopyToDocument( nUndoStartX, nUndoStartY, nStartTab, nDelEndX, nDelEndY, nEndTab,
//STRIP001 /*?*/                                IDF_ALL, FALSE, pUndoDoc );
//STRIP001 /*?*/        pRefUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 /*?*/        pRefUndoDoc->InitUndo( pDoc, 0, nTabCount-1, FALSE, FALSE );
//STRIP001 /*?*/
//STRIP001 /*?*/        pUndoData = new ScRefUndoData( pDoc );
//STRIP001 /*?*/
//STRIP001 /*?*/        pDoc->BeginDrawUndo();
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    USHORT nExtFlags = 0;
//STRIP001 /*?*/    if (pDoc->HasAttrib( nStartCol,nStartRow,nTab, nEndCol,nEndRow,nTab, HASATTR_PAINTEXT ))
//STRIP001 /*?*/        nExtFlags |= SC_PF_LINES;
//STRIP001 /*?*/
//STRIP001 /*?*/    BOOL bUndoOutline = FALSE;
//STRIP001 /*?*/    switch (eCmd)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        case DEL_CELLSUP:
//STRIP001 /*?*/            pDoc->DeleteRow( nStartCol, nStartTab, nEndCol, nEndTab,
//STRIP001 /*?*/                                nStartRow, nEndRow-nStartRow+1, pRefUndoDoc );
//STRIP001 /*?*/            nPaintEndY = MAXROW;
//STRIP001 /*?*/            break;
//STRIP001 /*?*/        case DEL_DELROWS:
//STRIP001 /*?*/            pDoc->DeleteRow( 0, nStartTab, MAXCOL, nEndTab,
//STRIP001 /*?*/                                nStartRow, nEndRow-nStartRow+1, pRefUndoDoc, &bUndoOutline );
//STRIP001 /*?*/            nPaintStartX = 0;
//STRIP001 /*?*/            nPaintEndX = MAXCOL;
//STRIP001 /*?*/            nPaintEndY = MAXROW;
//STRIP001 /*?*/            nPaintFlags |= PAINT_LEFT;
//STRIP001 /*?*/            break;
//STRIP001 /*?*/        case DEL_CELLSLEFT:
//STRIP001 /*?*/            pDoc->DeleteCol( nStartRow, nStartTab, nEndRow, nEndTab,
//STRIP001 /*?*/                                nStartCol, nEndCol-nStartCol+1, pRefUndoDoc );
//STRIP001 /*?*/            nPaintEndX = MAXCOL;
//STRIP001 /*?*/            break;
//STRIP001 /*?*/        case DEL_DELCOLS:
//STRIP001 /*?*/            pDoc->DeleteCol( 0, nStartTab, MAXROW, nEndTab,
//STRIP001 /*?*/                                nStartCol, nEndCol-nStartCol+1, pRefUndoDoc, &bUndoOutline );
//STRIP001 /*?*/            nPaintStartY = 0;
//STRIP001 /*?*/            nPaintEndY = MAXROW;
//STRIP001 /*?*/            nPaintEndX = MAXCOL;
//STRIP001 /*?*/            nPaintFlags |= PAINT_TOP;
//STRIP001 /*?*/            break;
//STRIP001 /*?*/        default:
//STRIP001 /*?*/            DBG_ERROR("Falscher Code beim Loeschen");
//STRIP001 /*?*/            break;
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    //! Test, ob Outline in Groesse geaendert
//STRIP001 /*?*/
//STRIP001 /*?*/    if ( bRecord )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        for (USHORT i=nStartTab; i<=nEndTab; i++)
//STRIP001 /*?*/            pRefUndoDoc->DeleteAreaTab(nUndoStartX,nUndoStartY,nDelEndX,nDelEndY,i,
//STRIP001 /*?*/                                        IDF_ALL);
//STRIP001 /*?*/
//STRIP001 /*?*/            //  alle Tabellen anlegen, damit Formeln kopiert werden koennen:
//STRIP001 /*?*/        pUndoDoc->AddUndoTab( 0, nTabCount-1, FALSE, FALSE );
//STRIP001 /*?*/
//STRIP001 /*?*/            //  kopieren mit bColRowFlags=FALSE (#54194#)
//STRIP001 /*?*/        pRefUndoDoc->CopyToDocument(0,0,0,MAXCOL,MAXROW,MAXTAB,IDF_FORMULA,FALSE,pUndoDoc,NULL,FALSE);
//STRIP001 /*?*/        delete pRefUndoDoc;
//STRIP001 /*?*/        rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/            new ScUndoDeleteCells( &rDocShell, ScRange(
//STRIP001 /*?*/                                            nStartCol,nStartRow,nStartTab,
//STRIP001 /*?*/                                            nEndCol,nEndRow,nEndTab ),
//STRIP001 /*?*/                                    eCmd, pUndoDoc, pUndoData ) );
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    if (bNeedRefresh)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        if ( eCmd==DEL_DELCOLS || eCmd==DEL_DELROWS )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            if (eCmd==DEL_DELCOLS) nMergeTestEndX = MAXCOL;
//STRIP001 /*?*/            if (eCmd==DEL_DELROWS) nMergeTestEndY = MAXROW;
//STRIP001 /*?*/            ScPatternAttr aPattern( pDoc->GetPool() );
//STRIP001 /*?*/            aPattern.GetItemSet().Put( ScMergeFlagAttr() );
//STRIP001 /*?*/
//STRIP001 /*?*/            ScMarkData aMark;                           // nur fuer Tabellen
//STRIP001 /*?*/            for (USHORT i=nStartTab; i<=nEndTab; i++)
//STRIP001 /*?*/                aMark.SelectTable( i, TRUE );
//STRIP001 /*?*/            pDoc->ApplyPatternArea( nUndoStartX, nUndoStartY, nMergeTestEndX, nMergeTestEndY,
//STRIP001 /*?*/                                        aMark, aPattern );
//STRIP001 /*?*/        }
//STRIP001 /*?*/        pDoc->ExtendMerge( nUndoStartX, nUndoStartY, nMergeTestEndX, nMergeTestEndY, nTab, TRUE );
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    if ( eCmd == DEL_DELCOLS || eCmd == DEL_DELROWS )
//STRIP001 /*?*/        pDoc->UpdatePageBreaks( nTab );
//STRIP001 /*?*/
//STRIP001 /*?*/    if (pDoc->HasAttrib( nPaintStartX,nPaintStartY,nTab,
//STRIP001 /*?*/                            nPaintEndX,nPaintEndY,nTab, HASATTR_PAINTEXT ))
//STRIP001 /*?*/        nExtFlags |= SC_PF_LINES;
//STRIP001 /*?*/
//STRIP001 /*?*/    //  ganze Zeilen loeschen: nichts anpassen
//STRIP001 /*?*/    if ( eCmd == DEL_DELROWS ||
//STRIP001 /*?*/            !AdjustRowHeight(ScRange(0,nPaintStartY,nStartTab, MAXCOL,nPaintEndY,nEndTab)) )
//STRIP001 /*?*/        rDocShell.PostPaint( nPaintStartX, nPaintStartY, nStartTab,
//STRIP001 /*?*/                             nPaintEndX,   nPaintEndY,   nEndTab,
//STRIP001 /*?*/                             nPaintFlags,  nExtFlags );
//STRIP001 /*?*/    else
//STRIP001 /*?*/    {
//STRIP001 /*?*/        //  paint only what is not done by AdjustRowHeight
//STRIP001 /*?*/        if (nExtFlags & SC_PF_LINES)
//STRIP001 /*?*/            lcl_PaintAbove( rDocShell, ScRange( nPaintStartX, nPaintStartY, nStartTab,
//STRIP001 /*?*/                                                nPaintEndX,   nPaintEndY,   nEndTab) );
//STRIP001 /*?*/        if (nPaintFlags & PAINT_TOP)
//STRIP001 /*?*/            rDocShell.PostPaint( nPaintStartX, nPaintStartY, nStartTab,
//STRIP001 /*?*/                                 nPaintEndX,   nPaintEndY,   nEndTab,   PAINT_TOP );
//STRIP001 /*?*/    }
//STRIP001 /*?*/    aModificator.SetDocumentModified();
//STRIP001 /*?*/
//STRIP001 /*?*/ //!    pDocSh->UpdateOle(GetViewData());   // muss an der View bleiben
//STRIP001 /*?*/ //!    CellContentChanged();               // muss an der View bleiben
//STRIP001 /*?*/
/*N*/   return TRUE;
/*N*/ }

/*N*/ BOOL ScDocFunc::MoveBlock( const ScRange& rSource, const ScAddress& rDestPos,
/*N*/                               BOOL bCut, BOOL bRecord, BOOL bPaint, BOOL bApi )
/*N*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001 ScDocShellModificator aModificator( rDocShell );
//STRIP001 /*?*/
//STRIP001 /*?*/    USHORT nStartCol = rSource.aStart.Col();
//STRIP001 /*?*/    USHORT nStartRow = rSource.aStart.Row();
//STRIP001 /*?*/    USHORT nStartTab = rSource.aStart.Tab();
//STRIP001 /*?*/    USHORT nEndCol = rSource.aEnd.Col();
//STRIP001 /*?*/    USHORT nEndRow = rSource.aEnd.Row();
//STRIP001 /*?*/    USHORT nEndTab = rSource.aEnd.Tab();
//STRIP001 /*?*/    USHORT nDestCol = rDestPos.Col();
//STRIP001 /*?*/    USHORT nDestRow = rDestPos.Row();
//STRIP001 /*?*/    USHORT nDestTab = rDestPos.Tab();
//STRIP001 /*?*/
//STRIP001 /*?*/    if ( nStartRow > MAXROW || nEndRow > MAXROW || nDestRow > MAXROW )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        DBG_ERROR("invalid row in MoveBlock");
//STRIP001 /*?*/        return FALSE;
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    //  zugehoerige Szenarien auch anpassen - nur wenn innerhalb einer Tabelle verschoben wird!
//STRIP001 /*?*/    BOOL bScenariosAdded = FALSE;
//STRIP001 /*?*/    ScDocument* pDoc = rDocShell.GetDocument();
//STRIP001 /*?*/    if (bRecord && !pDoc->IsUndoEnabled())
//STRIP001 /*?*/        bRecord = FALSE;
//STRIP001 /*?*/
//STRIP001 /*?*/    USHORT nTabCount = pDoc->GetTableCount();
//STRIP001 /*?*/    if ( nDestTab == nStartTab && !pDoc->IsScenario(nEndTab) )
//STRIP001 /*?*/        while ( nEndTab+1 < nTabCount && pDoc->IsScenario(nEndTab+1) )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            ++nEndTab;
//STRIP001 /*?*/            bScenariosAdded = TRUE;
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/    USHORT nSrcTabCount = nEndTab-nStartTab+1;
//STRIP001 /*?*/    USHORT nDestEndTab = nDestTab+nSrcTabCount-1;
//STRIP001 /*?*/    USHORT nTab;
//STRIP001 /*?*/
//STRIP001 /*?*/    ScDocument* pClipDoc = new ScDocument( SCDOCMODE_CLIP );
//STRIP001 /*?*/
//STRIP001 /*?*/    ScMarkData aSourceMark;
//STRIP001 /*?*/    for (nTab=nStartTab; nTab<=nEndTab; nTab++)
//STRIP001 /*?*/        aSourceMark.SelectTable( nTab, TRUE );      // Source selektieren
//STRIP001 /*?*/    aSourceMark.SetMarkArea( rSource );
//STRIP001 /*?*/
//STRIP001 /*?*/    ScDocShellRef aDragShellRef;
//STRIP001 /*?*/    if ( pDoc->HasOLEObjectsInArea( rSource ) )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        aDragShellRef = new ScDocShell;     // DocShell needs a Ref immediately
//STRIP001 /*?*/        aDragShellRef->DoInitNew(NULL);
//STRIP001 /*?*/    }
//STRIP001 /*?*/    ScDrawLayer::SetGlobalDrawPersist(aDragShellRef);
//STRIP001 /*?*/
//STRIP001 /*?*/    pDoc->CopyToClip( nStartCol, nStartRow, nEndCol, nEndRow, bCut, pClipDoc,
//STRIP001 /*?*/                        FALSE, &aSourceMark, bScenariosAdded, TRUE );
//STRIP001 /*?*/
//STRIP001 /*?*/    ScDrawLayer::SetGlobalDrawPersist(NULL);
//STRIP001 /*?*/
//STRIP001 /*?*/    USHORT nOldEndCol = nEndCol;
//STRIP001 /*?*/    USHORT nOldEndRow = nEndRow;
//STRIP001 /*?*/    BOOL bClipOver = FALSE;
//STRIP001 /*?*/    for (nTab=nStartTab; nTab<=nEndTab; nTab++)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        USHORT nTmpEndCol = nOldEndCol;
//STRIP001 /*?*/        USHORT nTmpEndRow = nOldEndRow;
//STRIP001 /*?*/        if (pDoc->ExtendMerge( nStartCol, nStartRow, nTmpEndCol, nTmpEndRow, nTab ))
//STRIP001 /*?*/            bClipOver = TRUE;
//STRIP001 /*?*/        if ( nTmpEndCol > nEndCol ) nEndCol = nTmpEndCol;
//STRIP001 /*?*/        if ( nTmpEndRow > nEndRow ) nEndRow = nTmpEndRow;
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    USHORT nDestEndCol = nDestCol + ( nOldEndCol-nStartCol );
//STRIP001 /*?*/    USHORT nDestEndRow = nDestRow + ( nOldEndRow-nStartRow );
//STRIP001 /*?*/
//STRIP001 /*?*/    USHORT nUndoEndCol = nDestCol + ( nEndCol-nStartCol );      // erweitert im Zielblock
//STRIP001 /*?*/    USHORT nUndoEndRow = nDestRow + ( nEndRow-nStartRow );
//STRIP001 /*?*/
//STRIP001 /*?*/    BOOL bIncludeFiltered = bCut;
//STRIP001 /*?*/    if ( !bIncludeFiltered )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        //  adjust sizes to include only non-filtered rows
//STRIP001 /*?*/
//STRIP001 /*?*/        USHORT nClipX, nClipY;
//STRIP001 /*?*/        pClipDoc->GetClipArea( nClipX, nClipY, FALSE );
//STRIP001 /*?*/        USHORT nUndoAdd = nUndoEndRow - nDestEndRow;
//STRIP001 /*?*/        nDestEndRow = nDestRow + nClipY;
//STRIP001 /*?*/        nUndoEndRow = nDestEndRow + nUndoAdd;
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    if (nUndoEndCol>MAXCOL || nUndoEndRow>MAXROW)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        if (!bApi)
//STRIP001 /*?*/            rDocShell.ErrorMessage(STR_PASTE_FULL);
//STRIP001 /*?*/        delete pClipDoc;
//STRIP001 /*?*/        return FALSE;
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    //  Test auf Zellschutz
//STRIP001 /*?*/
//STRIP001 /*?*/    ScEditableTester aTester;
//STRIP001 /*?*/    for (nTab=nDestTab; nTab<=nDestEndTab; nTab++)
//STRIP001 /*?*/        aTester.TestBlock( pDoc, nTab, nDestCol,nDestRow, nUndoEndCol,nUndoEndRow );
//STRIP001 /*?*/    if (bCut)
//STRIP001 /*?*/        for (nTab=nStartTab; nTab<=nEndTab; nTab++)
//STRIP001 /*?*/            aTester.TestBlock( pDoc, nTab, nStartCol,nStartRow, nEndCol,nEndRow );
//STRIP001 /*?*/
//STRIP001 /*?*/    if (!aTester.IsEditable())
//STRIP001 /*?*/    {
//STRIP001 /*?*/        if (!bApi)
//STRIP001 /*?*/            rDocShell.ErrorMessage(aTester.GetMessageId());
//STRIP001 /*?*/        delete pClipDoc;
//STRIP001 /*?*/        return FALSE;
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    //  Test auf zusammengefasste - beim Verschieben erst nach dem Loeschen
//STRIP001 /*?*/
//STRIP001 /*?*/    if (bClipOver && !bCut)
//STRIP001 /*?*/        if (pDoc->HasAttrib( nDestCol,nDestRow,nDestTab, nUndoEndCol,nUndoEndRow,nDestEndTab,
//STRIP001 /*?*/                                HASATTR_MERGED | HASATTR_OVERLAPPED ))
//STRIP001 /*?*/        {       // "Zusammenfassen nicht verschachteln !"
//STRIP001 /*?*/            if (!bApi)
//STRIP001 /*?*/                rDocShell.ErrorMessage(STR_MSSG_MOVEBLOCKTO_0);
//STRIP001 /*?*/            delete pClipDoc;
//STRIP001 /*?*/            return FALSE;
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/    //  Linien drin? (fuer Paint)
//STRIP001 /*?*/
//STRIP001 /*?*/    BOOL bSourceLines = pDoc->HasAttrib( nStartCol,nStartRow,nStartTab,
//STRIP001 /*?*/                                nEndCol,nEndRow,nEndTab, HASATTR_PAINTEXT );
//STRIP001 /*?*/    BOOL bDestLines = pDoc->HasAttrib( nDestCol,nDestRow,nDestTab,
//STRIP001 /*?*/                                nDestEndCol,nDestEndRow,nDestEndTab, HASATTR_PAINTEXT );
//STRIP001 /*?*/
//STRIP001 /*?*/    //
//STRIP001 /*?*/    //  ausfuehren
//STRIP001 /*?*/    //
//STRIP001 /*?*/
//STRIP001 /*?*/    ScDocument* pUndoDoc = NULL;
//STRIP001 /*?*/    ScDocument* pRefUndoDoc = NULL;
//STRIP001 /*?*/    ScRefUndoData* pUndoData = NULL;
//STRIP001 /*?*/    if (bRecord)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        BOOL bWholeCols = ( nStartRow == 0 && nEndRow == MAXROW );
//STRIP001 /*?*/        BOOL bWholeRows = ( nStartCol == 0 && nEndCol == MAXCOL );
//STRIP001 /*?*/
//STRIP001 /*?*/        pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 /*?*/        pUndoDoc->InitUndo( pDoc, nStartTab, nEndTab, bWholeCols, bWholeRows );
//STRIP001 /*?*/
//STRIP001 /*?*/        if (bCut)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pDoc->CopyToDocument( nStartCol, nStartRow, nStartTab, nEndCol, nEndRow, nEndTab,
//STRIP001 /*?*/                                    IDF_ALL, FALSE, pUndoDoc );
//STRIP001 /*?*/            pRefUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 /*?*/            pRefUndoDoc->InitUndo( pDoc, 0, nTabCount-1, FALSE, FALSE );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        if ( nDestTab != nStartTab )
//STRIP001 /*?*/            pUndoDoc->AddUndoTab( nDestTab, nDestEndTab, bWholeCols, bWholeRows );
//STRIP001 /*?*/        pDoc->CopyToDocument( nDestCol, nDestRow, nDestTab,
//STRIP001 /*?*/                                    nDestEndCol, nDestEndRow, nDestEndTab,
//STRIP001 /*?*/                                    IDF_ALL, FALSE, pUndoDoc );
//STRIP001 /*?*/
//STRIP001 /*?*/        pUndoData = new ScRefUndoData( pDoc );
//STRIP001 /*?*/
//STRIP001 /*?*/        pDoc->BeginDrawUndo();
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    BOOL bSourceHeight = FALSE;     // Hoehen angepasst?
//STRIP001 /*?*/    if (bCut)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        ScMarkData aDelMark;    // only for tables
//STRIP001 /*?*/        for (nTab=nStartTab; nTab<=nEndTab; nTab++)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pDoc->DeleteAreaTab( nStartCol,nStartRow, nOldEndCol,nOldEndRow, nTab, IDF_ALL );
//STRIP001 /*?*/            aDelMark.SelectTable( nTab, TRUE );
//STRIP001 /*?*/        }
//STRIP001 /*?*/        pDoc->DeleteObjectsInArea( nStartCol,nStartRow, nOldEndCol,nOldEndRow, aDelMark );
//STRIP001 /*?*/
//STRIP001 /*?*/        //  Test auf zusammengefasste
//STRIP001 /*?*/
//STRIP001 /*?*/        if (bClipOver)
//STRIP001 /*?*/            if (pDoc->HasAttrib( nDestCol,nDestRow,nDestTab,
//STRIP001 /*?*/                                    nUndoEndCol,nUndoEndRow,nDestEndTab,
//STRIP001 /*?*/                                    HASATTR_MERGED | HASATTR_OVERLAPPED ))
//STRIP001 /*?*/            {
//STRIP001 /*?*/                pDoc->CopyFromClip( rSource, aSourceMark, IDF_ALL, pRefUndoDoc, pClipDoc );
//STRIP001 /*?*/                for (nTab=nStartTab; nTab<=nEndTab; nTab++)
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    USHORT nTmpEndCol = nEndCol;
//STRIP001 /*?*/                    USHORT nTmpEndRow = nEndRow;
//STRIP001 /*?*/                    pDoc->ExtendMerge( nStartCol, nStartRow, nTmpEndCol, nTmpEndRow, nTab, TRUE );
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/                //  Fehlermeldung erst nach dem Wiederherstellen des Inhalts
//STRIP001 /*?*/                if (!bApi)      // "Zusammenfassen nicht verschachteln !"
//STRIP001 /*?*/                    rDocShell.ErrorMessage(STR_MSSG_MOVEBLOCKTO_0);
//STRIP001 /*?*/
//STRIP001 /*?*/                delete pUndoDoc;
//STRIP001 /*?*/                delete pRefUndoDoc;
//STRIP001 /*?*/                delete pUndoData;
//STRIP001 /*?*/                delete pClipDoc;
//STRIP001 /*?*/                return FALSE;
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/        bSourceHeight = AdjustRowHeight( rSource, FALSE );
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    ScRange aPasteDest( nDestCol, nDestRow, nDestTab, nDestEndCol, nDestEndRow, nDestEndTab );
//STRIP001 /*?*/
//STRIP001 /*?*/    ScMarkData aDestMark;
//STRIP001 /*?*/    for (nTab=nDestTab; nTab<=nDestEndTab; nTab++)
//STRIP001 /*?*/        aDestMark.SelectTable( nTab, TRUE );        // Destination selektieren
//STRIP001 /*?*/    aDestMark.SetMarkArea( aPasteDest );
//STRIP001 /*?*/
//STRIP001 /*?*/    pDoc->CopyFromClip( aPasteDest, aDestMark, IDF_ALL & ~IDF_OBJECTS,
//STRIP001 /*?*/                        pRefUndoDoc, pClipDoc, TRUE, FALSE, bIncludeFiltered );
//STRIP001 /*?*/
//STRIP001 /*?*/    // skipped rows and merged cells don't mix
//STRIP001 /*?*/    if ( !bIncludeFiltered && pClipDoc->HasClipFilteredRows() )
//STRIP001 /*?*/        UnmergeCells( aPasteDest, FALSE, TRUE );
//STRIP001 /*?*/
//STRIP001 /*?*/    VirtualDevice aVirtDev;
//STRIP001 /*?*/    BOOL bDestHeight = AdjustRowHeight(
//STRIP001 /*?*/                            ScRange( 0,nDestRow,nDestTab, MAXCOL,nDestEndRow,nDestEndTab ),
//STRIP001 /*?*/                            FALSE );
//STRIP001 /*?*/
//STRIP001 /*?*/    //  paste drawing objects after adjusting row heights
//STRIP001 /*?*/    if ( pClipDoc->GetDrawLayer() )
//STRIP001 /*?*/        pDoc->CopyFromClip( aPasteDest, aDestMark, IDF_OBJECTS,
//STRIP001 /*?*/                            pRefUndoDoc, pClipDoc, TRUE, FALSE, bIncludeFiltered );
//STRIP001 /*?*/
//STRIP001 /*?*/    if (bRecord)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        if (pRefUndoDoc)
//STRIP001 /*?*/        {
//STRIP001 /*?*/                //  alle Tabellen anlegen, damit Formeln kopiert werden koennen:
//STRIP001 /*?*/            pUndoDoc->AddUndoTab( 0, nTabCount-1, FALSE, FALSE );
//STRIP001 /*?*/
//STRIP001 /*?*/            pRefUndoDoc->DeleteArea( nDestCol, nDestRow, nDestEndCol, nDestEndRow, aSourceMark, IDF_ALL );
//STRIP001 /*?*/            //  kopieren mit bColRowFlags=FALSE (#54194#)
//STRIP001 /*?*/            pRefUndoDoc->CopyToDocument( 0, 0, 0, MAXCOL, MAXROW, MAXTAB,
//STRIP001 /*?*/                                            IDF_FORMULA, FALSE, pUndoDoc, NULL, FALSE );
//STRIP001 /*?*/            delete pRefUndoDoc;
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/            new ScUndoDragDrop( &rDocShell, ScRange(
//STRIP001 /*?*/                                    nStartCol, nStartRow, nStartTab,
//STRIP001 /*?*/                                    nOldEndCol, nOldEndRow, nEndTab ),
//STRIP001 /*?*/                                ScAddress( nDestCol, nDestRow, nDestTab ),
//STRIP001 /*?*/                                bCut, pUndoDoc, pUndoData, bScenariosAdded ) );
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    USHORT nDestPaintEndCol = nDestEndCol;
//STRIP001 /*?*/    USHORT nDestPaintEndRow = nDestEndRow;
//STRIP001 /*?*/    for (nTab=nDestTab; nTab<=nDestEndTab; nTab++)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        USHORT nTmpEndCol = nDestEndCol;
//STRIP001 /*?*/        USHORT nTmpEndRow = nDestEndRow;
//STRIP001 /*?*/        pDoc->ExtendMerge( nDestCol, nDestRow, nTmpEndCol, nTmpEndRow, nTab, TRUE );
//STRIP001 /*?*/        if (nTmpEndCol > nDestPaintEndCol) nDestPaintEndCol = nTmpEndCol;
//STRIP001 /*?*/        if (nTmpEndRow > nDestPaintEndRow) nDestPaintEndRow = nTmpEndRow;
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    if (bCut)
//STRIP001 /*?*/        for (nTab=nStartTab; nTab<=nEndTab; nTab++)
//STRIP001 /*?*/            pDoc->RefreshAutoFilter( nStartCol, nStartRow, nEndCol, nEndRow, nTab );
//STRIP001 /*?*/
//STRIP001 /*?*/    if (bPaint)
//STRIP001 /*?*/    {
//STRIP001 /*?*/            //  Zielbereich:
//STRIP001 /*?*/
//STRIP001 /*?*/        USHORT nPaintStartX = nDestCol;
//STRIP001 /*?*/        USHORT nPaintStartY = nDestRow;
//STRIP001 /*?*/        USHORT nPaintEndX = nDestPaintEndCol;
//STRIP001 /*?*/        USHORT nPaintEndY = nDestPaintEndRow;
//STRIP001 /*?*/        USHORT nFlags = PAINT_GRID;
//STRIP001 /*?*/        USHORT nExt = 0;
//STRIP001 /*?*/        if ( bSourceLines || bDestLines )
//STRIP001 /*?*/            nExt |= SC_PF_LINES;
//STRIP001 /*?*/
//STRIP001 /*?*/        if ( nStartRow==0 && nEndRow==MAXROW )      // Breiten mitkopiert?
//STRIP001 /*?*/        {
//STRIP001 /*?*/            nPaintEndX = MAXCOL;
//STRIP001 /*?*/            nPaintStartY = 0;
//STRIP001 /*?*/            nPaintEndY = MAXROW;
//STRIP001 /*?*/            nFlags |= PAINT_TOP;
//STRIP001 /*?*/        }
//STRIP001 /*?*/        if ( bDestHeight || ( nStartCol == 0 && nEndCol == MAXCOL ) )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            nPaintEndY = MAXROW;
//STRIP001 /*?*/            nPaintStartX = 0;
//STRIP001 /*?*/            nPaintEndX = MAXCOL;
//STRIP001 /*?*/            nFlags |= PAINT_LEFT;
//STRIP001 /*?*/        }
//STRIP001 /*?*/        if ( bScenariosAdded )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            nPaintStartX = nPaintStartY = 0;
//STRIP001 /*?*/            nPaintEndX = MAXCOL;
//STRIP001 /*?*/            nPaintEndY = MAXROW;
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        rDocShell.PostPaint( nPaintStartX,nPaintStartY,nDestTab,
//STRIP001 /*?*/                            nPaintEndX,nPaintEndY,nDestEndTab, nFlags, nExt );
//STRIP001 /*?*/
//STRIP001 /*?*/        if ( bCut )
//STRIP001 /*?*/        {
//STRIP001 /*?*/                //  Quellbereich:
//STRIP001 /*?*/
//STRIP001 /*?*/            nPaintStartX = nStartCol;
//STRIP001 /*?*/            nPaintStartY = nStartRow;
//STRIP001 /*?*/            nPaintEndX = nEndCol;
//STRIP001 /*?*/            nPaintEndY = nEndRow;
//STRIP001 /*?*/            nFlags = PAINT_GRID;
//STRIP001 /*?*/            nExt = 0;
//STRIP001 /*?*/            if ( bSourceLines )
//STRIP001 /*?*/                nExt |= SC_PF_LINES;
//STRIP001 /*?*/
//STRIP001 /*?*/            if ( bSourceHeight )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                nPaintEndY = MAXROW;
//STRIP001 /*?*/                nPaintStartX = 0;
//STRIP001 /*?*/                nPaintEndX = MAXCOL;
//STRIP001 /*?*/                nFlags |= PAINT_LEFT;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            if ( bScenariosAdded )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                nPaintStartX = nPaintStartY = 0;
//STRIP001 /*?*/                nPaintEndX = MAXCOL;
//STRIP001 /*?*/                nPaintEndY = MAXROW;
//STRIP001 /*?*/            }
//STRIP001 /*?*/
//STRIP001 /*?*/            rDocShell.PostPaint( nPaintStartX,nPaintStartY,nStartTab,
//STRIP001 /*?*/                                nPaintEndX,nPaintEndY,nEndTab, nFlags, nExt );
//STRIP001 /*?*/        }
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    aModificator.SetDocumentModified();
//STRIP001 /*?*/
//STRIP001 /*?*/    delete pClipDoc;
/*N*/   return TRUE;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL ScDocFunc::InsertTable( USHORT nTab, const String& rName, BOOL bRecord, BOOL bApi )
/*N*/ {
/*N*/   BOOL bSuccess = FALSE;
/*N*/   WaitObject aWait( rDocShell.GetDialogParent() );
/*N*/
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   if (bRecord && !pDoc->IsUndoEnabled())
/*N*/       bRecord = FALSE;
/*N*/   if (bRecord)
/*N*/       pDoc->BeginDrawUndo();                          //  InsertTab erzeugt ein SdrUndoNewPage
/*N*/
/*N*/   USHORT nTabCount = pDoc->GetTableCount();
/*N*/   BOOL bAppend = ( nTab >= nTabCount );
/*N*/   if ( bAppend )
/*N*/       nTab = nTabCount;       // wichtig fuer Undo
/*N*/
/*N*/   if (pDoc->InsertTab( nTab, rName ))
/*N*/   {
/*N*/       if (bRecord)
/*N*/           rDocShell.GetUndoManager()->AddUndoAction(
/*N*/                       new ScUndoInsertTab( &rDocShell, nTab, bAppend, rName));
/*N*/       //  Views updaten:
/*N*/       rDocShell.Broadcast( ScTablesHint( SC_TAB_INSERTED, nTab ) );
/*N*/
/*N*/       rDocShell.PostPaintExtras();
/*N*/       aModificator.SetDocumentModified();
/*N*/       SFX_APP()->Broadcast( SfxSimpleHint( SC_HINT_TABLES_CHANGED ) );
/*N*/       bSuccess = TRUE;
/*N*/   }
/*N*/   else if (!bApi)
/*?*/       rDocShell.ErrorMessage(STR_TABINSERT_ERROR);
/*N*/
/*N*/   return bSuccess;
/*N*/ }

/*N*/ BOOL ScDocFunc::DeleteTable( USHORT nTab, BOOL bRecord, BOOL bApi )
/*N*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); return FALSE; //STRIP001 WaitObject aWait( rDocShell.GetDialogParent() );
//STRIP001 /*?*/
//STRIP001 /*?*/    ScDocShellModificator aModificator( rDocShell );
//STRIP001 /*?*/
//STRIP001 /*?*/    BOOL bSuccess = FALSE;
//STRIP001 /*?*/    ScDocument* pDoc = rDocShell.GetDocument();
//STRIP001 /*?*/    if (bRecord && !pDoc->IsUndoEnabled())
//STRIP001 /*?*/        bRecord = FALSE;
//STRIP001 /*?*/    BOOL bWasLinked = pDoc->IsLinked(nTab);
//STRIP001 /*?*/    ScDocument* pUndoDoc = NULL;
//STRIP001 /*?*/    ScRefUndoData* pUndoData = NULL;
//STRIP001 /*?*/    if (bRecord)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 /*?*/        USHORT nCount = pDoc->GetTableCount();
//STRIP001 /*?*/
//STRIP001 /*?*/        pUndoDoc->InitUndo( pDoc, nTab, nTab, TRUE, TRUE );     // nur nTab mit Flags
//STRIP001 /*?*/        pUndoDoc->AddUndoTab( 0, nCount-1 );                    // alle Tabs fuer Referenzen
//STRIP001 /*?*/
//STRIP001 /*?*/        pDoc->CopyToDocument(0,0,nTab, MAXCOL,MAXROW,nTab, IDF_ALL,FALSE, pUndoDoc );
//STRIP001 /*?*/        String aOldName;
//STRIP001 /*?*/        pDoc->GetName( nTab, aOldName );
//STRIP001 /*?*/        pUndoDoc->RenameTab( nTab, aOldName, FALSE );
//STRIP001 /*?*/        if (bWasLinked)
//STRIP001 /*?*/            pUndoDoc->SetLink( nTab, pDoc->GetLinkMode(nTab), pDoc->GetLinkDoc(nTab),
//STRIP001 /*?*/                                pDoc->GetLinkFlt(nTab), pDoc->GetLinkOpt(nTab),
//STRIP001 /*?*/                                pDoc->GetLinkTab(nTab),
//STRIP001 /*?*/                                pDoc->GetLinkRefreshDelay(nTab) );
//STRIP001 /*?*/
//STRIP001 /*?*/        if ( pDoc->IsScenario(nTab) )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pUndoDoc->SetScenario( nTab, TRUE );
//STRIP001 /*?*/            String aComment;
//STRIP001 /*?*/            Color  aColor;
//STRIP001 /*?*/            USHORT nScenFlags;
//STRIP001 /*?*/            pDoc->GetScenarioData( nTab, aComment, aColor, nScenFlags );
//STRIP001 /*?*/            pUndoDoc->SetScenarioData( nTab, aComment, aColor, nScenFlags );
//STRIP001 /*?*/            BOOL bActive = pDoc->IsActiveScenario( nTab );
//STRIP001 /*?*/            pUndoDoc->SetActiveScenario( nTab, bActive );
//STRIP001 /*?*/        }
//STRIP001 /*?*/        pUndoDoc->SetVisible( nTab, pDoc->IsVisible( nTab ) );
//STRIP001 /*?*/
//STRIP001 /*?*/        //  Drawing-Layer muss sein Undo selbst in der Hand behalten !!!
//STRIP001 /*?*/        pDoc->BeginDrawUndo();                          //  DeleteTab erzeugt ein SdrUndoDelPage
//STRIP001 /*?*/
//STRIP001 /*?*/        pUndoData = new ScRefUndoData( pDoc );
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    if (pDoc->DeleteTab( nTab, pUndoDoc ))
//STRIP001 /*?*/    {
//STRIP001 /*?*/        if (bRecord)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            SvUShorts theTabs;
//STRIP001 /*?*/            theTabs.Insert(nTab,theTabs.Count());
//STRIP001 /*?*/            rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                        new ScUndoDeleteTab( &rDocShell, theTabs, pUndoDoc, pUndoData ));
//STRIP001 /*?*/        }
//STRIP001 /*?*/        //  Views updaten:
//STRIP001 /*?*/        rDocShell.Broadcast( ScTablesHint( SC_TAB_DELETED, nTab ) );
//STRIP001 /*?*/
//STRIP001 /*?*/        if (bWasLinked)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            rDocShell.UpdateLinks();                // Link-Manager updaten
//STRIP001 /*?*/            SfxBindings* pBindings = rDocShell.GetViewBindings();
//STRIP001 /*?*/            if (pBindings)
//STRIP001 /*?*/                pBindings->Invalidate(SID_LINKS);
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        rDocShell.PostPaintExtras();
//STRIP001 /*?*/        aModificator.SetDocumentModified();
//STRIP001 /*?*/        SFX_APP()->Broadcast( SfxSimpleHint( SC_HINT_TABLES_CHANGED ) );
//STRIP001 /*?*/        bSuccess = TRUE;
//STRIP001 /*?*/    }
//STRIP001 /*?*/    else
//STRIP001 /*?*/    {
//STRIP001 /*?*/        delete pUndoDoc;
//STRIP001 /*?*/        delete pUndoData;
//STRIP001 /*?*/    }
//STRIP001 /*?*/    return bSuccess;
/*N*/ }

/*N*/ BOOL ScDocFunc::SetTableVisible( USHORT nTab, BOOL bVisible, BOOL bApi )
/*N*/ {
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   BOOL bUndo(pDoc->IsUndoEnabled());
/*N*/   if ( pDoc->IsVisible( nTab ) == bVisible )
/*N*/       return TRUE;                                // nichts zu tun - ok
/*N*/
/*N*/   if ( !pDoc->IsDocEditable() )
/*N*/   {
/*N*/       if (!bApi)
/*N*/           rDocShell.ErrorMessage(STR_PROTECTIONERR);
/*N*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   if ( !bVisible )
/*N*/   {
/*N*/       //  nicht alle Tabellen ausblenden
/*N*/
/*N*/       USHORT nVisCount = 0;
/*N*/       USHORT nCount = pDoc->GetTableCount();
/*N*/       for (USHORT i=0; i<nCount; i++)
/*N*/           if (pDoc->IsVisible(i))
/*N*/               ++nVisCount;
/*N*/
/*N*/       if (nVisCount <= 1)
/*N*/       {
/*N*/           if (!bApi)
/*N*/               rDocShell.ErrorMessage(STR_PROTECTIONERR);  //! eigene Meldung?
/*N*/           return FALSE;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   pDoc->SetVisible( nTab, bVisible );
/*N*/   if (bUndo)
/*N*/       rDocShell.GetUndoManager()->AddUndoAction( new ScUndoShowHideTab( &rDocShell, nTab, bVisible ) );
/*N*/
/*N*/   //  Views updaten:
/*N*/   if (!bVisible)
/*N*/       rDocShell.Broadcast( ScTablesHint( SC_TAB_HIDDEN, nTab ) );
/*N*/
/*N*/   SFX_APP()->Broadcast( SfxSimpleHint( SC_HINT_TABLES_CHANGED ) );
/*N*/   rDocShell.PostPaint(0,0,0,MAXCOL,MAXROW,MAXTAB, PAINT_EXTRAS);
/*N*/   aModificator.SetDocumentModified();
/*N*/
/*N*/   return TRUE;
/*N*/ }

/*N*/ BOOL ScDocFunc::RenameTable( USHORT nTab, const String& rName, BOOL bRecord, BOOL bApi )
/*N*/ {
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   if (bRecord && !pDoc->IsUndoEnabled())
/*N*/       bRecord = FALSE;
/*N*/   if ( !pDoc->IsDocEditable() )
/*N*/   {
/*?*/       if (!bApi)
/*?*/           rDocShell.ErrorMessage(STR_PROTECTIONERR);
/*?*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   BOOL bSuccess = FALSE;
/*N*/   String sOldName;
/*N*/   pDoc->GetName(nTab, sOldName);
/*N*/   if (pDoc->RenameTab( nTab, rName ))
/*N*/   {
/*N*/       if (bRecord)
/*N*/       {
/*N*/           rDocShell.GetUndoManager()->AddUndoAction(
/*N*/                           new ScUndoRenameTab( &rDocShell, nTab, sOldName, rName));
/*N*/       }
/*N*/       rDocShell.PostPaintExtras();
/*N*/       aModificator.SetDocumentModified();
/*N*/       SFX_APP()->Broadcast( SfxSimpleHint( SC_HINT_TABLES_CHANGED ) );
/*N*/
/*N*/       bSuccess = TRUE;
/*N*/   }
/*N*/   return bSuccess;
/*N*/ }

//------------------------------------------------------------------------

//! SetWidthOrHeight - noch doppelt zu ViewFunc !!!!!!
//! Probleme:
//! - Optimale Hoehe fuer Edit-Zellen ist unterschiedlich zwischen Drucker und Bildschirm
//! - Optimale Breite braucht Selektion, um evtl. nur selektierte Zellen zu beruecksichtigen

/*N*/ USHORT lcl_GetOptimalColWidth( ScDocShell& rDocShell, USHORT nCol, USHORT nTab, BOOL bFormula )
/*N*/ {
/*N*/   USHORT nTwips = 0;
/*N*/
/*N*/   ScSizeDeviceProvider aProv(&rDocShell);
/*N*/   OutputDevice* pDev = aProv.GetDevice();         // has pixel MapMode
/*N*/   double nPPTX = aProv.GetPPTX();
/*N*/   double nPPTY = aProv.GetPPTY();
/*N*/
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   Fraction aOne(1,1);
/*N*/   nTwips = pDoc->GetOptimalColWidth( nCol, nTab, pDev, nPPTX, nPPTY, aOne, aOne,
/*N*/                                       bFormula, NULL );
/*N*/
/*N*/   return nTwips;
/*N*/ }

/*N*/ BOOL ScDocFunc::SetWidthOrHeight( BOOL bWidth, USHORT nRangeCnt, USHORT* pRanges, USHORT nTab,
/*N*/                                       ScSizeMode eMode, USHORT nSizeTwips,
/*N*/                                       BOOL bRecord, BOOL bApi )
/*N*/ {
/*N*/   if (!nRangeCnt)
/*N*/       return TRUE;
/*N*/
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   if ( bRecord && !pDoc->IsUndoEnabled() )
/*N*/       bRecord = FALSE;
/*N*/
/*N*/   if ( !rDocShell.IsEditable() )
/*N*/   {
/*?*/       if (!bApi)
/*?*/           rDocShell.ErrorMessage(STR_PROTECTIONERR);      //! eigene Meldung?
/*?*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   BOOL bSuccess = FALSE;
/*N*/   USHORT nStart = pRanges[0];
/*N*/   USHORT nEnd = pRanges[2*nRangeCnt-1];
/*N*/
/*N*/   BOOL bFormula = FALSE;
/*N*/   if ( eMode == SC_SIZE_OPTIMAL )
/*N*/   {
/*N*/       //! Option "Formeln anzeigen" - woher nehmen?
/*N*/   }
/*N*/
/*N*/   ScDocument*     pUndoDoc = NULL;
/*N*/   ScOutlineTable* pUndoTab = NULL;
/*N*/   USHORT*         pUndoRanges = NULL;
/*N*/
/*N*/   if ( bRecord )
/*N*/   {
/*N*/       pDoc->BeginDrawUndo();                          // Drawing Updates
/*N*/
/*N*/       pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
/*N*/       if (bWidth)
/*N*/       {
/*N*/           pUndoDoc->InitUndo( pDoc, nTab, nTab, TRUE, FALSE );
/*N*/           pDoc->CopyToDocument( nStart, 0, nTab, nEnd, MAXROW, nTab, IDF_NONE, FALSE, pUndoDoc );
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           pUndoDoc->InitUndo( pDoc, nTab, nTab, FALSE, TRUE );
/*N*/           pDoc->CopyToDocument( 0, nStart, nTab, MAXCOL, nEnd, nTab, IDF_NONE, FALSE, pUndoDoc );
/*N*/       }
/*N*/
/*N*/       pUndoRanges = new USHORT[ 2*nRangeCnt ];
/*N*/       memmove( pUndoRanges, pRanges, 2*nRangeCnt*sizeof(USHORT) );
/*N*/
/*N*/       ScOutlineTable* pTable = pDoc->GetOutlineTable( nTab );
/*N*/       if (pTable)
/*N*/           pUndoTab = new ScOutlineTable( *pTable );
/*N*/   }
/*N*/
/*N*/   BOOL bShow = nSizeTwips > 0 || eMode != SC_SIZE_DIRECT;
/*N*/   BOOL bOutline = FALSE;
/*N*/
/*N*/   pDoc->IncSizeRecalcLevel( nTab );       // nicht fuer jede Spalte einzeln
/*N*/   for (USHORT nRangeNo=0; nRangeNo<nRangeCnt; nRangeNo++)
/*N*/   {
/*N*/       USHORT nStartNo = *(pRanges++);
/*N*/       USHORT nEndNo = *(pRanges++);
/*N*/
/*N*/       if ( !bWidth )                      // Hoehen immer blockweise
/*N*/       {
/*N*/           if ( eMode==SC_SIZE_OPTIMAL || eMode==SC_SIZE_VISOPT )
/*N*/           {
/*?*/               BOOL bAll = ( eMode==SC_SIZE_OPTIMAL );
/*?*/               if (!bAll)
/*?*/               {
/*?*/                   //  fuer alle eingeblendeten CR_MANUALSIZE loeschen,
/*?*/                   //  dann SetOptimalHeight mit bShrink = FALSE
/*?*/                   for (USHORT nRow=nStartNo; nRow<=nEndNo; nRow++)
/*?*/                   {
/*?*/                       BYTE nOld = pDoc->GetRowFlags(nRow,nTab);
/*?*/                       if ( (nOld & CR_HIDDEN) == 0 && ( nOld & CR_MANUALSIZE ) )
/*?*/                           pDoc->SetRowFlags( nRow, nTab, nOld & ~CR_MANUALSIZE );
/*?*/                   }
/*?*/               }
/*?*/
/*?*/               ScSizeDeviceProvider aProv( &rDocShell );
/*?*/               Fraction aOne(1,1);
/*?*/               pDoc->SetOptimalHeight( nStartNo, nEndNo, nTab, 0, aProv.GetDevice(),
/*?*/                                       aProv.GetPPTX(), aProv.GetPPTY(), aOne, aOne, bAll );
/*?*/
/*?*/               if (bAll)
/*?*/                   pDoc->ShowRows( nStartNo, nEndNo, nTab, TRUE );
/*?*/
/*?*/               //  Manual-Flag wird bei bAll=TRUE schon in SetOptimalHeight gesetzt
/*?*/               //  (an bei Extra-Height, sonst aus).
/*N*/           }
/*N*/           else if ( eMode==SC_SIZE_DIRECT || eMode==SC_SIZE_ORIGINAL )
/*N*/           {
/*N*/               if (nSizeTwips)
/*N*/               {
/*N*/                   pDoc->SetRowHeightRange( nStartNo, nEndNo, nTab, nSizeTwips );
/*N*/                   pDoc->SetManualHeight( nStartNo, nEndNo, nTab, TRUE );          // height was set manually
/*N*/               }
/*N*/               if ( eMode != SC_SIZE_ORIGINAL )
/*N*/                   pDoc->ShowRows( nStartNo, nEndNo, nTab, nSizeTwips != 0 );
/*N*/           }
/*N*/           else if ( eMode==SC_SIZE_SHOW )
/*N*/           {
/*?*/               pDoc->ShowRows( nStartNo, nEndNo, nTab, TRUE );
/*N*/           }
/*N*/       }
/*N*/       else                                // Spaltenbreiten
/*N*/       {
/*N*/           for (USHORT nCol=nStartNo; nCol<=nEndNo; nCol++)
/*N*/           {
/*N*/               if ( eMode != SC_SIZE_VISOPT ||
/*N*/                    (pDoc->GetColFlags( nCol, nTab ) & CR_HIDDEN) == 0 )
/*N*/               {
/*N*/                   USHORT nThisSize = nSizeTwips;
/*N*/
/*N*/                   if ( eMode==SC_SIZE_OPTIMAL || eMode==SC_SIZE_VISOPT )
/*N*/                    nThisSize = nSizeTwips +
/*N*/                                   lcl_GetOptimalColWidth( rDocShell, nCol, nTab, bFormula );
/*N*/                   if ( nThisSize )
/*N*/                       pDoc->SetColWidth( nCol, nTab, nThisSize );
/*N*/
/*N*/                   if ( eMode != SC_SIZE_ORIGINAL )
/*N*/                       pDoc->ShowCol( nCol, nTab, bShow );
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/
/*N*/                           //  adjust outlines
/*N*/
/*N*/       if ( eMode != SC_SIZE_ORIGINAL )
/*N*/       {
/*N*/           if (bWidth)
/*N*/               bOutline = bOutline || pDoc->UpdateOutlineCol( nStartNo, nEndNo, nTab, bShow );
/*N*/           else
/*N*/               bOutline = bOutline || pDoc->UpdateOutlineRow( nStartNo, nEndNo, nTab, bShow );
/*N*/       }
/*N*/   }
/*N*/   pDoc->DecSizeRecalcLevel( nTab );       // nicht fuer jede Spalte einzeln
/*N*/
/*N*/   if (!bOutline)
/*N*/       DELETEZ(pUndoTab);
/*N*/
/*N*/   if (bRecord)
/*N*/   {
/*N*/       ScMarkData aMark;
/*N*/       aMark.SelectOneTable( nTab );
/*N*/       rDocShell.GetUndoManager()->AddUndoAction(
/*N*/           new ScUndoWidthOrHeight( &rDocShell, aMark,
/*N*/                                    nStart, nTab, nEnd, nTab,
/*N*/                                    pUndoDoc, nRangeCnt, pUndoRanges,
/*N*/                                    pUndoTab, eMode, nSizeTwips, bWidth ) );
/*N*/   }
/*N*/
/*N*/   pDoc->UpdatePageBreaks( nTab );
/*N*/
/*N*/   rDocShell.PostPaint(0,0,nTab,MAXCOL,MAXROW,nTab,PAINT_ALL);
/*N*/
/*N*/   return bSuccess;
/*N*/ }


/*N*/ BOOL ScDocFunc::InsertPageBreak( BOOL bColumn, const ScAddress& rPos,
/*N*/                               BOOL bRecord, BOOL bSetModified, BOOL bApi )
/*N*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001 ScDocShellModificator aModificator( rDocShell );
//STRIP001 /*?*/
//STRIP001 /*?*/    ScDocument* pDoc = rDocShell.GetDocument();
//STRIP001 /*?*/    if (bRecord && !pDoc->IsUndoEnabled())
//STRIP001 /*?*/        bRecord = FALSE;
//STRIP001 /*?*/    USHORT nTab = rPos.Tab();
//STRIP001 /*?*/    SfxBindings* pBindings = rDocShell.GetViewBindings();
//STRIP001 /*?*/
//STRIP001 /*?*/    USHORT nPos = bColumn ? rPos.Col() : rPos.Row();
//STRIP001 /*?*/    if (nPos == 0)
//STRIP001 /*?*/        return FALSE;                   // erste Spalte / Zeile
//STRIP001 /*?*/
//STRIP001 /*?*/    BYTE nFlags = bColumn ? pDoc->GetColFlags( nPos, nTab ) : pDoc->GetRowFlags( nPos, nTab );
//STRIP001 /*?*/    if (nFlags & CR_MANUALBREAK)
//STRIP001 /*?*/        return TRUE;                    // Umbruch schon gesetzt
//STRIP001 /*?*/
//STRIP001 /*?*/    if (bRecord)
//STRIP001 /*?*/        rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/            new ScUndoPageBreak( &rDocShell, rPos.Col(), rPos.Row(), nTab, bColumn, TRUE ) );
//STRIP001 /*?*/
//STRIP001 /*?*/    nFlags |= CR_MANUALBREAK;
//STRIP001 /*?*/    if (bColumn)
//STRIP001 /*?*/        pDoc->SetColFlags( nPos, nTab, nFlags );
//STRIP001 /*?*/    else
//STRIP001 /*?*/        pDoc->SetRowFlags( nPos, nTab, nFlags );
//STRIP001 /*?*/    pDoc->UpdatePageBreaks( nTab );
//STRIP001 /*?*/
//STRIP001 /*?*/    if (bColumn)
//STRIP001 /*?*/    {
//STRIP001 /*?*/        rDocShell.PostPaint( nPos-1, 0, nTab, MAXCOL, MAXROW, nTab, PAINT_GRID );
//STRIP001 /*?*/        if (pBindings)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pBindings->Invalidate( FID_INS_COLBRK );
//STRIP001 /*?*/            pBindings->Invalidate( FID_DEL_COLBRK );
//STRIP001 /*?*/        }
//STRIP001 /*?*/    }
//STRIP001 /*?*/    else
//STRIP001 /*?*/    {
//STRIP001 /*?*/        rDocShell.PostPaint( 0, nPos-1, nTab, MAXCOL, MAXROW, nTab, PAINT_GRID );
//STRIP001 /*?*/        if (pBindings)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            pBindings->Invalidate( FID_INS_ROWBRK );
//STRIP001 /*?*/            pBindings->Invalidate( FID_DEL_ROWBRK );
//STRIP001 /*?*/        }
//STRIP001 /*?*/    }
//STRIP001 /*?*/    if (pBindings)
//STRIP001 /*?*/        pBindings->Invalidate( FID_DEL_MANUALBREAKS );
//STRIP001 /*?*/
//STRIP001 /*?*/    if (bSetModified)
//STRIP001 /*?*/        aModificator.SetDocumentModified();
//STRIP001 /*?*/
/*N*/   return TRUE;
/*N*/ }

/*N*/ BOOL ScDocFunc::RemovePageBreak( BOOL bColumn, const ScAddress& rPos,
/*N*/                               BOOL bRecord, BOOL bSetModified, BOOL bApi )
/*N*/ {
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   if (bRecord && !pDoc->IsUndoEnabled())
/*N*/       bRecord = FALSE;
/*N*/   USHORT nTab = rPos.Tab();
/*N*/   SfxBindings* pBindings = rDocShell.GetViewBindings();
/*N*/
/*N*/   USHORT nPos = bColumn ? rPos.Col() : rPos.Row();
/*N*/   BYTE nFlags = bColumn ? pDoc->GetColFlags( nPos, nTab ) : pDoc->GetRowFlags( nPos, nTab );
/*N*/   if ((nFlags & CR_MANUALBREAK)==0)
/*N*/       return FALSE;                           // kein Umbruch gesetzt
/*N*/
/*?*/   if (bRecord)
/*?*/       {DBG_ASSERT(0, "STRIP"); }//STRIP001 rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/            new ScUndoPageBreak( &rDocShell, rPos.Col(), rPos.Row(), nTab, bColumn, FALSE ) );
/*?*/
/*?*/   nFlags &= ~CR_MANUALBREAK;
/*?*/   if (bColumn)
/*?*/       {DBG_ASSERT(0, "STRIP"); }//STRIP001 pDoc->SetColFlags( nPos, nTab, nFlags );
/*?*/   else
/*?*/       pDoc->SetRowFlags( nPos, nTab, nFlags );
/*?*/   pDoc->UpdatePageBreaks( nTab );
/*?*/
/*?*/   if (bColumn)
/*?*/   {
/*?*/       rDocShell.PostPaint( nPos-1, 0, nTab, MAXCOL, MAXROW, nTab, PAINT_GRID );
/*?*/       if (pBindings)
/*?*/       {
/*?*/           pBindings->Invalidate( FID_INS_COLBRK );
/*?*/           pBindings->Invalidate( FID_DEL_COLBRK );
/*?*/       }
/*?*/   }
/*?*/   else
/*?*/   {
/*?*/       rDocShell.PostPaint( 0, nPos-1, nTab, MAXCOL, MAXROW, nTab, PAINT_GRID );
/*?*/       if (pBindings)
/*?*/       {
/*?*/           pBindings->Invalidate( FID_INS_ROWBRK );
/*?*/           pBindings->Invalidate( FID_DEL_ROWBRK );
/*?*/       }
/*?*/   }
/*?*/   if (pBindings)
/*?*/       pBindings->Invalidate( FID_DEL_MANUALBREAKS );
/*?*/
/*?*/   if (bSetModified)
/*?*/       aModificator.SetDocumentModified();
/*?*/
/*?*/   return TRUE;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL lcl_ValidPassword( ScDocument* pDoc, USHORT nTab,
/*N*/                       const String& rPassword,
/*N*/                       uno::Sequence<sal_Int8>* pReturnOld = NULL )
/*N*/ {
/*N*/   uno::Sequence<sal_Int8> aOldPassword;
/*N*/   if ( nTab == TABLEID_DOC )
/*N*/   {
/*N*/       if (pDoc->IsDocProtected())
/*N*/           aOldPassword = pDoc->GetDocPassword();
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       if (pDoc->IsTabProtected(nTab))
/*N*/           aOldPassword = pDoc->GetTabPassword(nTab);
/*N*/   }
/*N*/
/*N*/   if (pReturnOld)
/*N*/       *pReturnOld = aOldPassword;
/*N*/
/*N*/   return ((aOldPassword.getLength() == 0) || SvPasswordHelper::CompareHashPassword(aOldPassword, rPassword));
/*N*/ }

/*N*/ BOOL ScDocFunc::Protect( USHORT nTab, const String& rPassword, BOOL bApi )
/*N*/ {
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   BOOL bUndo(pDoc->IsUndoEnabled());
/*N*/   BOOL bOk = lcl_ValidPassword( pDoc, nTab, rPassword);
/*N*/   if ( bOk )
/*N*/   {
/*N*/       uno::Sequence<sal_Int8> aPass;
/*N*/       if (rPassword.Len())
/*N*/           SvPasswordHelper::GetHashPassword(aPass, rPassword);
/*N*/
/*N*/       if (bUndo)
/*N*/       {
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                        new ScUndoProtect( &rDocShell, nTab, TRUE, aPass ) );
/*N*/       }
/*N*/
/*N*/       if ( nTab == TABLEID_DOC )
/*N*/           pDoc->SetDocProtection( TRUE, aPass );
/*N*/       else
/*N*/           pDoc->SetTabProtection( nTab, TRUE, aPass );
/*N*/
/*N*/       rDocShell.PostPaintGridAll();
/*N*/       aModificator.SetDocumentModified();
/*N*/   }
/*N*/   else if (!bApi)
/*N*/   {
/*N*/       //  different password was set before
/*N*/
/*N*/ //!       rDocShell.ErrorMessage(...);
/*N*/
/*N*/       InfoBox aBox( rDocShell.GetDialogParent(), String( ScResId( SCSTR_WRONGPASSWORD ) ) );
/*N*/       aBox.Execute();
/*N*/   }
/*N*/
/*N*/   return bOk;
/*N*/ }

/*N*/ BOOL ScDocFunc::Unprotect( USHORT nTab, const String& rPassword, BOOL bApi )
/*N*/ {
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   BOOL bUndo(pDoc->IsUndoEnabled());
/*N*/   uno::Sequence<sal_Int8> aOldPassword;
/*N*/   uno::Sequence<sal_Int8> aPass;
/*N*/   BOOL bOk = lcl_ValidPassword( pDoc, nTab, rPassword, &aOldPassword );
/*N*/   if ( bOk )
/*N*/   {
/*N*/       uno::Sequence<sal_Int8> aEmptyPass;
/*N*/       if ( nTab == TABLEID_DOC )
/*N*/           pDoc->SetDocProtection( FALSE, aEmptyPass );
/*N*/       else
/*N*/           pDoc->SetTabProtection( nTab, FALSE, aEmptyPass );
/*N*/
/*N*/       if (bUndo)
/*N*/       {
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                        new ScUndoProtect( &rDocShell, nTab, FALSE, aOldPassword ) );
/*N*/       }
/*N*/
/*N*/       rDocShell.PostPaintGridAll();
/*N*/       aModificator.SetDocumentModified();
/*N*/   }
/*N*/   else if (!bApi)
/*N*/   {
/*N*/ //!       rDocShell.ErrorMessage(...);
/*N*/
/*N*/       InfoBox aBox( rDocShell.GetDialogParent(), String( ScResId( SCSTR_WRONGPASSWORD ) ) );
/*N*/       aBox.Execute();
/*N*/   }
/*N*/
/*N*/   return bOk;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL ScDocFunc::ClearItems( const ScMarkData& rMark, const USHORT* pWhich, BOOL bApi )
/*N*/ {
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   BOOL bUndo (pDoc->IsUndoEnabled());
/*N*/   ScEditableTester aTester( pDoc, rMark );
/*N*/   if (!aTester.IsEditable())
/*N*/   {
/*?*/       if (!bApi)
/*?*/           rDocShell.ErrorMessage(aTester.GetMessageId());
/*?*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   //  #i12940# ClearItems is called (from setPropertyToDefault) directly with uno object's cached
/*N*/   //  MarkData (GetMarkData), so rMark must be changed to multi selection for ClearSelectionItems
/*N*/   //  here.
/*N*/
/*N*/   ScRange aMarkRange;
/*N*/   ScMarkData aMultiMark = rMark;
/*N*/   aMultiMark.SetMarking(FALSE);       // for MarkToMulti
/*N*/   aMultiMark.MarkToMulti();
/*N*/   aMultiMark.GetMultiMarkArea( aMarkRange );
/*N*/
/*N*/ //    if (bRecord)
/*N*/   if (bUndo)
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 USHORT nStartTab = aMarkRange.aStart.Tab();
//STRIP001 /*?*/        USHORT nEndTab = aMarkRange.aEnd.Tab();
//STRIP001 /*?*/
//STRIP001 /*?*/        ScDocument* pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 /*?*/        pUndoDoc->InitUndo( pDoc, nStartTab, nEndTab );
//STRIP001 /*?*/        pDoc->CopyToDocument( aMarkRange, IDF_ATTRIB, TRUE, pUndoDoc, (ScMarkData*)&aMultiMark );
//STRIP001 /*?*/
//STRIP001 /*?*/        rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/            new ScUndoClearItems( &rDocShell, aMultiMark, pUndoDoc, pWhich ) );
/*N*/   }
/*N*/
/*N*/   pDoc->ClearSelectionItems( pWhich, aMultiMark );
/*N*/
/*N*/   rDocShell.PostPaint( aMarkRange, PAINT_GRID, SC_PF_LINES | SC_PF_TESTMERGE );
/*N*/   aModificator.SetDocumentModified();
/*N*/
/*N*/   //! Bindings-Invalidate etc.?
/*N*/
/*N*/   return TRUE;
/*N*/ }

/*N*/ BOOL ScDocFunc::ChangeIndent( const ScMarkData& rMark, BOOL bIncrement, BOOL bApi )
/*N*/ {
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   BOOL bUndo(pDoc->IsUndoEnabled());
/*N*/   ScEditableTester aTester( pDoc, rMark );
/*N*/   if (!aTester.IsEditable())
/*N*/   {
/*N*/       if (!bApi)
/*N*/           rDocShell.ErrorMessage(aTester.GetMessageId());
/*N*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   ScRange aMarkRange;
/*N*/   rMark.GetMultiMarkArea( aMarkRange );
/*N*/
/*N*/ //    if (bRecord)
/*N*/   if (bUndo)
/*N*/   {
/*?*/       DBG_ASSERT(0, "STRIP"); //STRIP001 USHORT nStartTab = aMarkRange.aStart.Tab();
//STRIP001 /*?*/        USHORT nTabCount = pDoc->GetTableCount();
//STRIP001 /*?*/
//STRIP001 /*?*/        ScDocument* pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 /*?*/        pUndoDoc->InitUndo( pDoc, nStartTab, nStartTab );
//STRIP001 /*?*/        for (USHORT i=0; i<nTabCount; i++)
//STRIP001 /*?*/            if (i != nStartTab && rMark.GetTableSelect(i))
//STRIP001 /*?*/                pUndoDoc->AddUndoTab( i, i );
//STRIP001 /*?*/
//STRIP001 /*?*/        ScRange aCopyRange = aMarkRange;
//STRIP001 /*?*/        aCopyRange.aStart.SetTab(0);
//STRIP001 /*?*/        aCopyRange.aEnd.SetTab(nTabCount-1);
//STRIP001 /*?*/        pDoc->CopyToDocument( aCopyRange, IDF_ATTRIB, TRUE, pUndoDoc, (ScMarkData*)&rMark );
//STRIP001 /*?*/
//STRIP001 /*?*/        rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/            new ScUndoIndent( &rDocShell, rMark, pUndoDoc, bIncrement ) );
/*N*/   }
/*N*/
/*N*/   pDoc->ChangeSelectionIndent( bIncrement, rMark );
/*N*/
/*N*/   rDocShell.PostPaint( aMarkRange, PAINT_GRID, SC_PF_LINES | SC_PF_TESTMERGE );
/*N*/   aModificator.SetDocumentModified();
/*N*/
/*N*/   SfxBindings* pBindings = rDocShell.GetViewBindings();
/*N*/   if (pBindings)
/*N*/   {
/*N*/       pBindings->Invalidate( SID_ALIGNLEFT );         // ChangeIndent setzt auf links
/*N*/       pBindings->Invalidate( SID_ALIGNRIGHT );
/*N*/       pBindings->Invalidate( SID_ALIGNBLOCK );
/*N*/       pBindings->Invalidate( SID_ALIGNCENTERHOR );
/*N*/   }
/*N*/
/*N*/   return TRUE;
/*N*/ }

/*N*/ BOOL ScDocFunc::AutoFormat( const ScRange& rRange, const ScMarkData* pTabMark,
/*N*/                           USHORT nFormatNo, BOOL bRecord, BOOL bApi )
/*N*/ {
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   BOOL bSuccess = FALSE;
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   USHORT nStartCol = rRange.aStart.Col();
/*N*/   USHORT nStartRow = rRange.aStart.Row();
/*N*/   USHORT nStartTab = rRange.aStart.Tab();
/*N*/   USHORT nEndCol = rRange.aEnd.Col();
/*N*/   USHORT nEndRow = rRange.aEnd.Row();
/*N*/   USHORT nEndTab = rRange.aEnd.Tab();
/*N*/
/*N*/   if (bRecord && !pDoc->IsUndoEnabled())
/*N*/       bRecord = FALSE;
/*N*/   ScMarkData aMark;
/*N*/   if (pTabMark)
/*N*/       aMark = *pTabMark;
/*N*/   else
/*N*/   {
/*N*/       for (USHORT nTab=nStartTab; nTab<=nEndTab; nTab++)
/*N*/           aMark.SelectTable( nTab, TRUE );
/*N*/   }
/*N*/
/*N*/   ScAutoFormat* pAutoFormat = ScGlobal::GetAutoFormat();
/*N*/   ScEditableTester aTester( pDoc, nStartCol,nStartRow, nEndCol,nEndRow, aMark );
/*N*/   if ( pAutoFormat && nFormatNo < pAutoFormat->GetCount() && aTester.IsEditable() )
/*N*/   {
/*N*/       WaitObject aWait( rDocShell.GetDialogParent() );
/*N*/
/*N*/       BOOL bSize = (*pAutoFormat)[nFormatNo]->GetIncludeWidthHeight();
/*N*/
/*N*/       USHORT nTabCount = pDoc->GetTableCount();
/*N*/       ScDocument* pUndoDoc = NULL;
/*N*/       if ( bRecord )
/*N*/       {
/*N*/           pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
/*N*/           pUndoDoc->InitUndo( pDoc, nStartTab, nStartTab, bSize, bSize );
/*N*/           for (USHORT i=0; i<nTabCount; i++)
/*N*/               if (i != nStartTab && aMark.GetTableSelect(i))
/*N*/                   pUndoDoc->AddUndoTab( i, i, bSize, bSize );
/*N*/
/*N*/           ScRange aCopyRange = rRange;
/*N*/           aCopyRange.aStart.SetTab(0);
/*N*/           aCopyRange.aStart.SetTab(nTabCount-1);
/*N*/           pDoc->CopyToDocument( aCopyRange, IDF_ATTRIB, FALSE, pUndoDoc, &aMark );
/*N*/           if (bSize)
/*N*/           {
/*N*/               pDoc->CopyToDocument( nStartCol,0,0, nEndCol,MAXROW,nTabCount-1,
/*N*/                                                           IDF_NONE, FALSE, pUndoDoc, &aMark );
/*N*/               pDoc->CopyToDocument( 0,nStartRow,0, MAXCOL,nEndRow,nTabCount-1,
/*N*/                                                           IDF_NONE, FALSE, pUndoDoc, &aMark );
/*N*/           }
/*N*/           pDoc->BeginDrawUndo();
/*N*/       }
/*N*/
/*N*/       pDoc->AutoFormat( nStartCol, nStartRow, nEndCol, nEndRow, nFormatNo, aMark );
/*N*/
/*N*/       if (bSize)
/*N*/       {
/*          USHORT nCols[2];
            nCols[0] = nStartCol;
            nCols[1] = nEndCol;
            USHORT nRows[2];
            nRows[0] = nStartRow;
            nRows[1] = nEndRow;
*/
/*N*/           USHORT nCols[2] = { nStartCol, nEndCol };
/*N*/           USHORT nRows[2] = { nStartRow, nEndRow };
/*N*/
/*N*/           for (USHORT nTab=0; nTab<nTabCount; nTab++)
/*N*/               if (aMark.GetTableSelect(nTab))
/*N*/               {
/*N*/                   SetWidthOrHeight( TRUE, 1,nCols, nTab, SC_SIZE_VISOPT, STD_EXTRA_WIDTH, FALSE, TRUE );
/*N*/                   SetWidthOrHeight( FALSE,1,nRows, nTab, SC_SIZE_VISOPT, 0, FALSE, FALSE );
/*N*/                   rDocShell.PostPaint( 0,0,nTab, MAXCOL,MAXROW,nTab,
/*N*/                                   PAINT_GRID | PAINT_LEFT | PAINT_TOP );
/*N*/               }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           for (USHORT nTab=0; nTab<nTabCount; nTab++)
/*N*/               if (aMark.GetTableSelect(nTab))
/*N*/               {
/*N*/                   BOOL bAdj = AdjustRowHeight( ScRange(nStartCol, nStartRow, nTab,
/*N*/                                                       nEndCol, nEndRow, nTab), FALSE );
/*N*/                   if (bAdj)
/*N*/                       rDocShell.PostPaint( 0,nStartRow,nTab, MAXCOL,MAXROW,nTab,
/*N*/                                           PAINT_GRID | PAINT_LEFT );
/*N*/                   else
/*N*/                       rDocShell.PostPaint( nStartCol, nStartRow, nTab,
/*N*/                                           nEndCol, nEndRow, nTab, PAINT_GRID );
/*N*/               }
/*N*/       }
/*N*/
/*N*/       if ( bRecord )      // Draw-Undo erst jetzt verfuegbar
/*N*/       {
/*?*/           DBG_ASSERT(0, "STRIP"); //STRIP001 rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                new ScUndoAutoFormat( &rDocShell, rRange, pUndoDoc, aMark, bSize, nFormatNo ) );
/*N*/       }
/*N*/
/*N*/       aModificator.SetDocumentModified();
/*N*/   }
/*N*/   else if (!bApi)
/*N*/       rDocShell.ErrorMessage(aTester.GetMessageId());
/*N*/
/*N*/   return bSuccess;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL ScDocFunc::EnterMatrix( const ScRange& rRange, const ScMarkData* pTabMark,
/*N*/                               const String& rString, BOOL bApi, BOOL bEnglish )
/*N*/ {
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   BOOL bSuccess = FALSE;
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   USHORT nStartCol = rRange.aStart.Col();
/*N*/   USHORT nStartRow = rRange.aStart.Row();
/*N*/   USHORT nStartTab = rRange.aStart.Tab();
/*N*/   USHORT nEndCol = rRange.aEnd.Col();
/*N*/   USHORT nEndRow = rRange.aEnd.Row();
/*N*/   USHORT nEndTab = rRange.aEnd.Tab();
/*N*/
/*N*/   BOOL bUndo(pDoc->IsUndoEnabled());
/*N*/
/*N*/   ScMarkData aMark;
/*N*/   if (pTabMark)
/*N*/       aMark = *pTabMark;
/*N*/   else
/*N*/   {
/*N*/       for (USHORT nTab=nStartTab; nTab<=nEndTab; nTab++)
/*N*/           aMark.SelectTable( nTab, TRUE );
/*N*/   }
/*N*/
/*N*/   ScEditableTester aTester( pDoc, nStartCol,nStartRow, nEndCol,nEndRow, aMark );
/*N*/   if ( aTester.IsEditable() )
/*N*/   {
/*N*/       WaitObject aWait( rDocShell.GetDialogParent() );
/*N*/
/*N*/       ScDocument* pUndoDoc;
/*N*/ //        if (bRecord)    // immer
/*N*/       if (bUndo)
/*N*/       {
/*N*/           //! auch bei Undo selektierte Tabellen beruecksichtigen
/*N*/           pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
/*N*/           pUndoDoc->InitUndo( pDoc, nStartTab, nEndTab );
/*N*/           pDoc->CopyToDocument( rRange, IDF_ALL, FALSE, pUndoDoc );
/*N*/       }
/*N*/
/*N*/       if ( pDoc->IsImportingXML() )
/*N*/       {
/*N*/           ScTokenArray* pCode = lcl_ScDocFunc_CreateTokenArrayXML( rString );
/*N*/           pDoc->InsertMatrixFormula(nStartCol,nStartRow,nEndCol,nEndRow,aMark,EMPTY_STRING,pCode);
/*N*/           delete pCode;
/*N*/             pDoc->IncXMLImportedFormulaCount( rString.Len() );
/*N*/       }
/*N*/       else if (bEnglish)
/*N*/         {
/*N*/           ScCompiler aComp( pDoc, rRange.aStart );
/*N*/           aComp.SetCompileEnglish( TRUE );
/*N*/           ScTokenArray* pCode = aComp.CompileString( rString );
/*N*/           pDoc->InsertMatrixFormula(nStartCol,nStartRow,nEndCol,nEndRow,aMark,EMPTY_STRING,pCode);
/*N*/           delete pCode;
/*N*/         }
/*N*/         else
/*N*/           pDoc->InsertMatrixFormula(nStartCol,nStartRow,nEndCol,nEndRow,aMark,rString);
/*N*/
/*N*/ //        if (bRecord)    // immer
/*N*/       if (bUndo)
/*N*/       {
/*N*/           //! auch bei Undo selektierte Tabellen beruecksichtigen
/*N*/           rDocShell.GetUndoManager()->AddUndoAction(
/*N*/               new ScUndoEnterMatrix( &rDocShell, rRange, pUndoDoc, rString ) );
/*N*/       }
/*N*/
/*N*/       //  Err522 beim Paint von DDE-Formeln werden jetzt beim Interpretieren abgefangen
/*N*/       rDocShell.PostPaint( nStartCol,nStartRow,nStartTab,nEndCol,nEndRow,nEndTab, PAINT_GRID );
/*N*/       aModificator.SetDocumentModified();
/*N*/
/*N*/       bSuccess = TRUE;
/*N*/   }
/*N*/   else if (!bApi)
/*N*/       rDocShell.ErrorMessage(aTester.GetMessageId());
/*N*/
/*N*/   return bSuccess;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL ScDocFunc::TabOp( const ScRange& rRange, const ScMarkData* pTabMark,
/*N*/                           const ScTabOpParam& rParam, BOOL bRecord, BOOL bApi )
/*N*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); return FALSE; //STRIP001 ScDocShellModificator aModificator( rDocShell );
//STRIP001 /*?*/
//STRIP001 /*?*/    BOOL bSuccess = FALSE;
//STRIP001 /*?*/    ScDocument* pDoc = rDocShell.GetDocument();
//STRIP001 /*?*/    USHORT nStartCol = rRange.aStart.Col();
//STRIP001 /*?*/    USHORT nStartRow = rRange.aStart.Row();
//STRIP001 /*?*/    USHORT nStartTab = rRange.aStart.Tab();
//STRIP001 /*?*/    USHORT nEndCol = rRange.aEnd.Col();
//STRIP001 /*?*/    USHORT nEndRow = rRange.aEnd.Row();
//STRIP001 /*?*/    USHORT nEndTab = rRange.aEnd.Tab();
//STRIP001 /*?*/
//STRIP001 /*?*/    if (bRecord && !pDoc->IsUndoEnabled())
//STRIP001 /*?*/        bRecord = FALSE;
//STRIP001 /*?*/
//STRIP001 /*?*/    ScMarkData aMark;
//STRIP001 /*?*/    if (pTabMark)
//STRIP001 /*?*/        aMark = *pTabMark;
//STRIP001 /*?*/    else
//STRIP001 /*?*/    {
//STRIP001 /*?*/        for (USHORT nTab=nStartTab; nTab<=nEndTab; nTab++)
//STRIP001 /*?*/            aMark.SelectTable( nTab, TRUE );
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    ScEditableTester aTester( pDoc, nStartCol,nStartRow, nEndCol,nEndRow, aMark );
//STRIP001 /*?*/    if ( aTester.IsEditable() )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        WaitObject aWait( rDocShell.GetDialogParent() );
//STRIP001 /*?*/        pDoc->SetDirty( rRange );
//STRIP001 /*?*/        if ( bRecord )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            //! auch bei Undo selektierte Tabellen beruecksichtigen
//STRIP001 /*?*/            ScDocument* pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 /*?*/            pUndoDoc->InitUndo( pDoc, nStartTab, nEndTab );
//STRIP001 /*?*/            pDoc->CopyToDocument( rRange, IDF_ALL, FALSE, pUndoDoc );
//STRIP001 /*?*/
//STRIP001 /*?*/            rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                    new ScUndoTabOp( &rDocShell,
//STRIP001 /*?*/                                     nStartCol, nStartRow, nStartTab,
//STRIP001 /*?*/                                     nEndCol, nEndRow, nEndTab, pUndoDoc,
//STRIP001 /*?*/                                     rParam.aRefFormulaCell,
//STRIP001 /*?*/                                     rParam.aRefFormulaEnd,
//STRIP001 /*?*/                                     rParam.aRefRowCell,
//STRIP001 /*?*/                                     rParam.aRefColCell,
//STRIP001 /*?*/                                     rParam.nMode) );
//STRIP001 /*?*/        }
//STRIP001 /*?*/        pDoc->InsertTableOp(rParam, nStartCol, nStartRow, nEndCol, nEndRow, aMark);
//STRIP001 /*?*/        rDocShell.PostPaintGridAll();
//STRIP001 /*?*/        aModificator.SetDocumentModified();
//STRIP001 /*?*/        bSuccess = TRUE;
//STRIP001 /*?*/    }
//STRIP001 /*?*/    else if (!bApi)
//STRIP001 /*?*/        rDocShell.ErrorMessage(aTester.GetMessageId());
//STRIP001 /*?*/
//STRIP001 /*?*/    return bSuccess;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ inline ScDirection DirFromFillDir( FillDir eDir )
/*N*/ {
/*N*/   if (eDir==FILL_TO_BOTTOM)
/*N*/       return DIR_BOTTOM;
/*N*/   else if (eDir==FILL_TO_RIGHT)
/*N*/       return DIR_RIGHT;
/*N*/   else if (eDir==FILL_TO_TOP)
/*N*/       return DIR_TOP;
/*N*/   else // if (eDir==FILL_TO_LEFT)
/*N*/       return DIR_LEFT;
/*N*/ }

//STRIP001 BOOL ScDocFunc::FillSimple( const ScRange& rRange, const ScMarkData* pTabMark,
//STRIP001                          FillDir eDir, BOOL bRecord, BOOL bApi )
//STRIP001 {
//STRIP001  ScDocShellModificator aModificator( rDocShell );
//STRIP001
//STRIP001  BOOL bSuccess = FALSE;
//STRIP001  ScDocument* pDoc = rDocShell.GetDocument();
//STRIP001  USHORT nStartCol = rRange.aStart.Col();
//STRIP001  USHORT nStartRow = rRange.aStart.Row();
//STRIP001  USHORT nStartTab = rRange.aStart.Tab();
//STRIP001  USHORT nEndCol = rRange.aEnd.Col();
//STRIP001  USHORT nEndRow = rRange.aEnd.Row();
//STRIP001  USHORT nEndTab = rRange.aEnd.Tab();
//STRIP001
//STRIP001  if (bRecord && !pDoc->IsUndoEnabled())
//STRIP001      bRecord = FALSE;
//STRIP001
//STRIP001  ScMarkData aMark;
//STRIP001  if (pTabMark)
//STRIP001      aMark = *pTabMark;
//STRIP001  else
//STRIP001  {
//STRIP001      for (USHORT nTab=nStartTab; nTab<=nEndTab; nTab++)
//STRIP001          aMark.SelectTable( nTab, TRUE );
//STRIP001  }
//STRIP001
//STRIP001  ScEditableTester aTester( pDoc, nStartCol,nStartRow, nEndCol,nEndRow, aMark );
//STRIP001  if ( aTester.IsEditable() )
//STRIP001  {
//STRIP001      WaitObject aWait( rDocShell.GetDialogParent() );
//STRIP001
//STRIP001      ScRange aSourceArea = rRange;
//STRIP001      ScRange aDestArea   = rRange;
//STRIP001
//STRIP001      USHORT nCount;
//STRIP001      switch (eDir)
//STRIP001      {
//STRIP001          case FILL_TO_BOTTOM:
//STRIP001              nCount = aSourceArea.aEnd.Row()-aSourceArea.aStart.Row();
//STRIP001              aSourceArea.aEnd.SetRow( aSourceArea.aStart.Row() );
//STRIP001              break;
//STRIP001          case FILL_TO_RIGHT:
//STRIP001              nCount = aSourceArea.aEnd.Col()-aSourceArea.aStart.Col();
//STRIP001              aSourceArea.aEnd.SetCol( aSourceArea.aStart.Col() );
//STRIP001              break;
//STRIP001          case FILL_TO_TOP:
//STRIP001              nCount = aSourceArea.aEnd.Row()-aSourceArea.aStart.Row();
//STRIP001              aSourceArea.aStart.SetRow( aSourceArea.aEnd.Row() );
//STRIP001              break;
//STRIP001          case FILL_TO_LEFT:
//STRIP001              nCount = aSourceArea.aEnd.Col()-aSourceArea.aStart.Col();
//STRIP001              aSourceArea.aStart.SetCol( aSourceArea.aEnd.Col() );
//STRIP001              break;
//STRIP001      }
//STRIP001
//STRIP001      ScDocument* pUndoDoc = NULL;
//STRIP001      if ( bRecord )
//STRIP001      {
//STRIP001          USHORT nTabCount = pDoc->GetTableCount();
//STRIP001          USHORT nStartTab = aDestArea.aStart.Tab();
//STRIP001
//STRIP001          pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001          pUndoDoc->InitUndo( pDoc, nStartTab, nStartTab );
//STRIP001          for (USHORT i=0; i<nTabCount; i++)
//STRIP001              if (i != nStartTab && aMark.GetTableSelect(i))
//STRIP001                  pUndoDoc->AddUndoTab( i, i );
//STRIP001
//STRIP001          ScRange aCopyRange = aDestArea;
//STRIP001          aCopyRange.aStart.SetTab(0);
//STRIP001          aCopyRange.aEnd.SetTab(nTabCount-1);
//STRIP001          pDoc->CopyToDocument( aCopyRange, IDF_ALL, FALSE, pUndoDoc, &aMark );
//STRIP001          pDoc->BeginDrawUndo();
//STRIP001      }
//STRIP001
//STRIP001      pDoc->Fill( aSourceArea.aStart.Col(), aSourceArea.aStart.Row(),
//STRIP001                  aSourceArea.aEnd.Col(), aSourceArea.aEnd.Row(), aMark,
//STRIP001                  nCount, eDir, FILL_SIMPLE );
//STRIP001      AdjustRowHeight(rRange);
//STRIP001
//STRIP001      if ( bRecord )      // Draw-Undo erst jetzt verfuegbar
//STRIP001      {
//STRIP001          rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001              new ScUndoAutoFill( &rDocShell, aDestArea, aSourceArea, pUndoDoc, aMark,
//STRIP001                                  eDir, FILL_SIMPLE, FILL_DAY, MAXDOUBLE, 1.0, 1e307,
//STRIP001                                  pDoc->GetRangeName()->GetSharedMaxIndex()+1 ) );
//STRIP001      }
//STRIP001
//STRIP001      rDocShell.PostPaintGridAll();
//STRIP001 //       rDocShell.PostPaintDataChanged();
//STRIP001      aModificator.SetDocumentModified();
//STRIP001
//STRIP001      bSuccess = TRUE;
//STRIP001  }
//STRIP001  else if (!bApi)
//STRIP001      rDocShell.ErrorMessage(aTester.GetMessageId());
//STRIP001
//STRIP001  return bSuccess;
//STRIP001 }

/*N*/ BOOL ScDocFunc::FillSeries( const ScRange& rRange, const ScMarkData* pTabMark,
/*N*/                           FillDir eDir, FillCmd eCmd, FillDateCmd eDateCmd,
/*N*/                           double fStart, double fStep, double fMax,
/*N*/                           BOOL bRecord, BOOL bApi )
/*N*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001 ScDocShellModificator aModificator( rDocShell );
//STRIP001 /*?*/
//STRIP001 /*?*/    BOOL bSuccess = FALSE;
//STRIP001 /*?*/    ScDocument* pDoc = rDocShell.GetDocument();
//STRIP001 /*?*/    USHORT nStartCol = rRange.aStart.Col();
//STRIP001 /*?*/    USHORT nStartRow = rRange.aStart.Row();
//STRIP001 /*?*/    USHORT nStartTab = rRange.aStart.Tab();
//STRIP001 /*?*/    USHORT nEndCol = rRange.aEnd.Col();
//STRIP001 /*?*/    USHORT nEndRow = rRange.aEnd.Row();
//STRIP001 /*?*/    USHORT nEndTab = rRange.aEnd.Tab();
//STRIP001 /*?*/
//STRIP001 /*?*/    if (bRecord && !pDoc->IsUndoEnabled())
//STRIP001 /*?*/        bRecord = FALSE;
//STRIP001 /*?*/
//STRIP001 /*?*/    ScMarkData aMark;
//STRIP001 /*?*/    if (pTabMark)
//STRIP001 /*?*/        aMark = *pTabMark;
//STRIP001 /*?*/    else
//STRIP001 /*?*/    {
//STRIP001 /*?*/        for (USHORT nTab=nStartTab; nTab<=nEndTab; nTab++)
//STRIP001 /*?*/            aMark.SelectTable( nTab, TRUE );
//STRIP001 /*?*/    }
//STRIP001 /*?*/
//STRIP001 /*?*/    ScEditableTester aTester( pDoc, nStartCol,nStartRow, nEndCol,nEndRow, aMark );
//STRIP001 /*?*/    if ( aTester.IsEditable() )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        WaitObject aWait( rDocShell.GetDialogParent() );
//STRIP001 /*?*/
//STRIP001 /*?*/        ScRange aSourceArea = rRange;
//STRIP001 /*?*/        ScRange aDestArea   = rRange;
//STRIP001 /*?*/
//STRIP001 /*?*/        USHORT nCount = pDoc->GetEmptyLinesInBlock(
//STRIP001 /*?*/                aSourceArea.aStart.Col(), aSourceArea.aStart.Row(), aSourceArea.aStart.Tab(),
//STRIP001 /*?*/                aSourceArea.aEnd.Col(), aSourceArea.aEnd.Row(), aSourceArea.aEnd.Tab(),
//STRIP001 /*?*/                DirFromFillDir(eDir) );
//STRIP001 /*?*/
//STRIP001 /*?*/        //  #27665# mindestens eine Zeile/Spalte als Quellbereich behalten:
//STRIP001 /*?*/        USHORT nTotLines = ( eDir == FILL_TO_BOTTOM || eDir == FILL_TO_TOP ) ?
//STRIP001 /*?*/                            ( aSourceArea.aEnd.Row() - aSourceArea.aStart.Row() + 1 ) :
//STRIP001 /*?*/                            ( aSourceArea.aEnd.Col() - aSourceArea.aStart.Col() + 1 );
//STRIP001 /*?*/        if ( nCount >= nTotLines )
//STRIP001 /*?*/            nCount = nTotLines - 1;
//STRIP001 /*?*/
//STRIP001 /*?*/        switch (eDir)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            case FILL_TO_BOTTOM:
//STRIP001 /*?*/                aSourceArea.aEnd.SetRow( aSourceArea.aEnd.Row() - nCount );
//STRIP001 /*?*/                break;
//STRIP001 /*?*/            case FILL_TO_RIGHT:
//STRIP001 /*?*/                aSourceArea.aEnd.SetCol( aSourceArea.aEnd.Col() - nCount );
//STRIP001 /*?*/                break;
//STRIP001 /*?*/            case FILL_TO_TOP:
//STRIP001 /*?*/                aSourceArea.aStart.SetRow( aSourceArea.aStart.Row() + nCount );
//STRIP001 /*?*/                break;
//STRIP001 /*?*/            case FILL_TO_LEFT:
//STRIP001 /*?*/                aSourceArea.aStart.SetCol( aSourceArea.aStart.Col() + nCount );
//STRIP001 /*?*/                break;
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        ScDocument* pUndoDoc = NULL;
//STRIP001 /*?*/        if ( bRecord )
//STRIP001 /*?*/        {
//STRIP001 /*?*/            USHORT nTabCount = pDoc->GetTableCount();
//STRIP001 /*?*/            USHORT nStartTab = aDestArea.aStart.Tab();
//STRIP001 /*?*/
//STRIP001 /*?*/            pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 /*?*/            pUndoDoc->InitUndo( pDoc, nStartTab, nStartTab );
//STRIP001 /*?*/            for (USHORT i=0; i<nTabCount; i++)
//STRIP001 /*?*/                if (i != nStartTab && aMark.GetTableSelect(i))
//STRIP001 /*?*/                    pUndoDoc->AddUndoTab( i, i );
//STRIP001 /*?*/
//STRIP001 /*?*/            pDoc->CopyToDocument(
//STRIP001 /*?*/                aDestArea.aStart.Col(), aDestArea.aStart.Row(), 0,
//STRIP001 /*?*/                aDestArea.aEnd.Col(), aDestArea.aEnd.Row(), nTabCount-1,
//STRIP001 /*?*/                IDF_ALL, FALSE, pUndoDoc, &aMark );
//STRIP001 /*?*/            pDoc->BeginDrawUndo();
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        if (aDestArea.aStart.Col() <= aDestArea.aEnd.Col() &&
//STRIP001 /*?*/            aDestArea.aStart.Row() <= aDestArea.aEnd.Row())
//STRIP001 /*?*/        {
//STRIP001 /*?*/            if ( fStart != MAXDOUBLE )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                USHORT nValX = (eDir == FILL_TO_LEFT) ? aDestArea.aEnd.Col() : aDestArea.aStart.Col();
//STRIP001 /*?*/                USHORT nValY = (eDir == FILL_TO_TOP ) ? aDestArea.aEnd.Row() : aDestArea.aStart.Row();
//STRIP001 /*?*/                USHORT nTab = aDestArea.aStart.Tab();
//STRIP001 /*?*/                pDoc->SetValue( nValX, nValY, nTab, fStart );
//STRIP001 /*?*/            }
//STRIP001 /*?*/            pDoc->Fill( aSourceArea.aStart.Col(), aSourceArea.aStart.Row(),
//STRIP001 /*?*/                        aSourceArea.aEnd.Col(), aSourceArea.aEnd.Row(), aMark,
//STRIP001 /*?*/                        nCount, eDir, eCmd, eDateCmd, fStep, fMax );
//STRIP001 /*?*/            AdjustRowHeight(rRange);
//STRIP001 /*?*/
//STRIP001 /*?*/            rDocShell.PostPaintGridAll();
//STRIP001 /*?*/ //         rDocShell.PostPaintDataChanged();
//STRIP001 /*?*/            aModificator.SetDocumentModified();
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        if ( bRecord )      // Draw-Undo erst jetzt verfuegbar
//STRIP001 /*?*/        {
//STRIP001 /*?*/            rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                new ScUndoAutoFill( &rDocShell, aDestArea, aSourceArea, pUndoDoc, aMark,
//STRIP001 /*?*/                                    eDir, eCmd, eDateCmd, fStart, fStep, fMax,
//STRIP001 /*?*/                                    pDoc->GetRangeName()->GetSharedMaxIndex()+1 ) );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        bSuccess = TRUE;
//STRIP001 /*?*/    }
//STRIP001 /*?*/    else if (!bApi)
//STRIP001 /*?*/        rDocShell.ErrorMessage(aTester.GetMessageId());
//STRIP001 /*?*/
//STRIP001 /*?*/    return bSuccess;
/*N*/ }

/*N*/ BOOL ScDocFunc::FillAuto( ScRange& rRange, const ScMarkData* pTabMark,
/*N*/                           FillDir eDir, USHORT nCount, BOOL bRecord, BOOL bApi )
/*N*/ {
    DBG_ASSERT(0, "STRIP"); //STRIP001 ScDocShellModificator aModificator( rDocShell );
//STRIP001
//STRIP001  ScDocument* pDoc = rDocShell.GetDocument();
//STRIP001  USHORT nStartCol = rRange.aStart.Col();
//STRIP001  USHORT nStartRow = rRange.aStart.Row();
//STRIP001  USHORT nStartTab = rRange.aStart.Tab();
//STRIP001  USHORT nEndCol = rRange.aEnd.Col();
//STRIP001  USHORT nEndRow = rRange.aEnd.Row();
//STRIP001  USHORT nEndTab = rRange.aEnd.Tab();
//STRIP001
//STRIP001  if (bRecord && !pDoc->IsUndoEnabled())
//STRIP001      bRecord = FALSE;
//STRIP001
//STRIP001  ScMarkData aMark;
//STRIP001  if (pTabMark)
//STRIP001      aMark = *pTabMark;
//STRIP001  else
//STRIP001  {
//STRIP001      for (USHORT nTab=nStartTab; nTab<=nEndTab; nTab++)
//STRIP001          aMark.SelectTable( nTab, TRUE );
//STRIP001  }
//STRIP001
//STRIP001  ScRange aSourceArea = rRange;
//STRIP001  ScRange aDestArea   = rRange;
//STRIP001
//STRIP001  FillCmd     eCmd = FILL_AUTO;
//STRIP001  FillDateCmd eDateCmd = FILL_DAY;
//STRIP001  double      fStep = 1.0;
//STRIP001  double      fMax = MAXDOUBLE;
//STRIP001
//STRIP001  switch (eDir)
//STRIP001  {
//STRIP001      case FILL_TO_BOTTOM:
//STRIP001          aDestArea.aEnd.SetRow( aSourceArea.aEnd.Row() + nCount );
//STRIP001          break;
//STRIP001      case FILL_TO_TOP:
//STRIP001          if (nCount > aSourceArea.aStart.Row())
//STRIP001          {
//STRIP001              DBG_ERROR("FillAuto: Row < 0");
//STRIP001              nCount = aSourceArea.aStart.Row();
//STRIP001          }
//STRIP001          aDestArea.aStart.SetRow( aSourceArea.aStart.Row() - nCount );
//STRIP001          break;
//STRIP001      case FILL_TO_RIGHT:
//STRIP001          aDestArea.aEnd.SetCol( aSourceArea.aEnd.Col() + nCount );
//STRIP001          break;
//STRIP001      case FILL_TO_LEFT:
//STRIP001          if (nCount > aSourceArea.aStart.Col())
//STRIP001          {
//STRIP001              DBG_ERROR("FillAuto: Col < 0");
//STRIP001              nCount = aSourceArea.aStart.Col();
//STRIP001          }
//STRIP001          aDestArea.aStart.SetCol( aSourceArea.aStart.Col() - nCount );
//STRIP001          break;
//STRIP001      default:
//STRIP001          DBG_ERROR("Falsche Richtung bei FillAuto");
//STRIP001          break;
//STRIP001  }
//STRIP001
//STRIP001  //      Zellschutz testen
//STRIP001  //!     Quellbereich darf geschuetzt sein !!!
//STRIP001  //!     aber kein Matrixfragment enthalten !!!
//STRIP001
//STRIP001  ScEditableTester aTester( pDoc, aDestArea );
//STRIP001  if ( !aTester.IsEditable() )
//STRIP001  {
//STRIP001      if (!bApi)
//STRIP001          rDocShell.ErrorMessage(aTester.GetMessageId());
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  if ( pDoc->HasSelectedBlockMatrixFragment( nStartCol, nStartRow,
//STRIP001          nEndCol, nEndRow, aMark ) )
//STRIP001  {
//STRIP001      if (!bApi)
//STRIP001          rDocShell.ErrorMessage(STR_MATRIXFRAGMENTERR);
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  WaitObject aWait( rDocShell.GetDialogParent() );
//STRIP001
//STRIP001  ScDocument* pUndoDoc = NULL;
//STRIP001  if ( bRecord )
//STRIP001  {
//STRIP001      USHORT nTabCount = pDoc->GetTableCount();
//STRIP001      USHORT nStartTab = aDestArea.aStart.Tab();
//STRIP001
//STRIP001      pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001      pUndoDoc->InitUndo( pDoc, nStartTab, nStartTab );
//STRIP001      for (USHORT i=0; i<nTabCount; i++)
//STRIP001          if (i != nStartTab && aMark.GetTableSelect(i))
//STRIP001              pUndoDoc->AddUndoTab( i, i );
//STRIP001
//STRIP001      pDoc->CopyToDocument(
//STRIP001          aDestArea.aStart.Col(), aDestArea.aStart.Row(), 0,
//STRIP001          aDestArea.aEnd.Col(), aDestArea.aEnd.Row(), nTabCount-1,
//STRIP001          IDF_ALL, FALSE, pUndoDoc, &aMark );
//STRIP001      pDoc->BeginDrawUndo();
//STRIP001  }
//STRIP001
//STRIP001  pDoc->Fill( aSourceArea.aStart.Col(), aSourceArea.aStart.Row(),
//STRIP001              aSourceArea.aEnd.Col(), aSourceArea.aEnd.Row(), aMark,
//STRIP001              nCount, eDir, eCmd, eDateCmd, fStep, fMax );
//STRIP001
//STRIP001  AdjustRowHeight(aDestArea);
//STRIP001
//STRIP001  if ( bRecord )      // Draw-Undo erst jetzt verfuegbar
//STRIP001  {
//STRIP001      rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001          new ScUndoAutoFill( &rDocShell, aDestArea, aSourceArea, pUndoDoc, aMark,
//STRIP001                              eDir, eCmd, eDateCmd, MAXDOUBLE, fStep, fMax,
//STRIP001                              pDoc->GetRangeName()->GetSharedMaxIndex()+1 ) );
//STRIP001  }
//STRIP001
//STRIP001  rDocShell.PostPaintGridAll();
//STRIP001 //   rDocShell.PostPaintDataChanged();
//STRIP001  aModificator.SetDocumentModified();
//STRIP001
//STRIP001  rRange = aDestArea;         // Zielbereich zurueckgeben (zum Markieren)
/*N*/   return TRUE;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL ScDocFunc::MergeCells( const ScRange& rRange, BOOL bContents, BOOL bRecord, BOOL bApi )
/*N*/ {
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   USHORT nStartCol = rRange.aStart.Col();
/*N*/   USHORT nStartRow = rRange.aStart.Row();
/*N*/   USHORT nEndCol = rRange.aEnd.Col();
/*N*/   USHORT nEndRow = rRange.aEnd.Row();
/*N*/   USHORT nTab = rRange.aStart.Tab();
/*N*/
/*N*/   if (bRecord && !pDoc->IsUndoEnabled())
/*N*/       bRecord = FALSE;
/*N*/
/*N*/   ScEditableTester aTester( pDoc, nTab, nStartCol, nStartRow, nEndCol, nEndRow );
/*N*/   if (!aTester.IsEditable())
/*N*/   {
/*?*/       if (!bApi)
/*?*/           rDocShell.ErrorMessage(aTester.GetMessageId());
/*?*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   if ( nStartCol == nEndCol && nStartRow == nEndRow )
/*N*/   {
/*N*/       // nichts zu tun
/*N*/       return TRUE;
/*N*/   }
/*N*/
/*N*/   if ( pDoc->HasAttrib( nStartCol, nStartRow, nTab, nEndCol, nEndRow, nTab,
/*N*/                           HASATTR_MERGED | HASATTR_OVERLAPPED ) )
/*N*/   {
/*?*/       // "Zusammenfassen nicht verschachteln !"
/*?*/       if (!bApi)
/*?*/           rDocShell.ErrorMessage(STR_MSSG_MERGECELLS_0);
/*?*/       return FALSE;
/*N*/   }
/*N*/
/*N*/   BOOL bNeedContents = bContents &&
/*N*/           ( !pDoc->IsBlockEmpty( nTab, nStartCol,nStartRow+1, nStartCol,nEndRow ) ||
/*N*/             !pDoc->IsBlockEmpty( nTab, nStartCol+1,nStartRow, nEndCol,nEndRow ) );
/*N*/
/*N*/   if (bRecord)
/*N*/   {
/*N*/       ScDocument* pUndoDoc = NULL;
/*N*/       if (bNeedContents && bContents)
/*N*/       {
/*?*/           pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
/*?*/           pUndoDoc->InitUndo( pDoc, nTab, nTab );
/*?*/           pDoc->CopyToDocument( nStartCol, nStartRow, nTab, nEndCol, nEndRow, nTab,
/*?*/                                   IDF_ALL, FALSE, pUndoDoc );
/*N*/       }
/*N*/       rDocShell.GetUndoManager()->AddUndoAction(
/*N*/           new ScUndoMerge( &rDocShell,
/*N*/                           nStartCol, nStartRow, nTab,
/*N*/                           nEndCol, nEndRow, nTab, TRUE, pUndoDoc ) );
/*N*/   }
/*N*/
/*N*/   if (bNeedContents && bContents)
/*?*/   {   DBG_ASSERT(0, "STRIP");} //STRIP001 pDoc->DoMergeContents( nTab, nStartCol,nStartRow, nEndCol,nEndRow );
/*N*/   pDoc->DoMerge( nTab, nStartCol,nStartRow, nEndCol,nEndRow );
/*N*/
/*N*/   if ( !AdjustRowHeight( ScRange( 0,nStartRow,nTab, MAXCOL,nEndRow,nTab ) ) )
/*N*/       rDocShell.PostPaint( nStartCol, nStartRow, nTab,
/*N*/                                           nEndCol, nEndRow, nTab, PAINT_GRID );
/*N*/   if (bNeedContents && bContents)
/*?*/       pDoc->SetDirty( rRange );
/*N*/   aModificator.SetDocumentModified();
/*N*/
/*N*/   SfxBindings* pBindings = rDocShell.GetViewBindings();
/*N*/   if (pBindings)
/*N*/   {
/*N*/       pBindings->Invalidate( FID_MERGE_ON );
/*N*/       pBindings->Invalidate( FID_MERGE_OFF );
/*N*/   }
/*N*/
/*N*/   return TRUE;
/*N*/ }

/*N*/ BOOL ScDocFunc::UnmergeCells( const ScRange& rRange, BOOL bRecord, BOOL bApi )
/*N*/ {
/*?*/   DBG_ASSERT(0, "STRIP"); //STRIP001 ScDocShellModificator aModificator( rDocShell );
//STRIP001 /*?*/
//STRIP001 /*?*/    ScDocument* pDoc = rDocShell.GetDocument();
//STRIP001 /*?*/    USHORT nTab = rRange.aStart.Tab();
//STRIP001 /*?*/
//STRIP001 /*?*/    if (bRecord && !pDoc->IsUndoEnabled())
//STRIP001 /*?*/        bRecord = FALSE;
//STRIP001 /*?*/
//STRIP001 /*?*/    if ( pDoc->HasAttrib( rRange, HASATTR_MERGED ) )
//STRIP001 /*?*/    {
//STRIP001 /*?*/        ScRange aExtended = rRange;
//STRIP001 /*?*/        pDoc->ExtendMerge( aExtended );
//STRIP001 /*?*/        ScRange aRefresh = aExtended;
//STRIP001 /*?*/        pDoc->ExtendOverlapped( aRefresh );
//STRIP001 /*?*/
//STRIP001 /*?*/        if (bRecord)
//STRIP001 /*?*/        {
//STRIP001 /*?*/            ScDocument* pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 /*?*/            pUndoDoc->InitUndo( pDoc, nTab, nTab );
//STRIP001 /*?*/            pDoc->CopyToDocument( aExtended, IDF_ATTRIB, FALSE, pUndoDoc );
//STRIP001 /*?*/            rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                new ScUndoRemoveMerge( &rDocShell, rRange, pUndoDoc ) );
//STRIP001 /*?*/        }
//STRIP001 /*?*/
//STRIP001 /*?*/        const SfxPoolItem& rDefAttr = pDoc->GetPool()->GetDefaultItem( ATTR_MERGE );
//STRIP001 /*?*/        ScPatternAttr aPattern( pDoc->GetPool() );
//STRIP001 /*?*/        aPattern.GetItemSet().Put( rDefAttr );
//STRIP001 /*?*/        pDoc->ApplyPatternAreaTab( rRange.aStart.Col(), rRange.aStart.Row(),
//STRIP001 /*?*/                                    rRange.aEnd.Col(), rRange.aEnd.Row(), nTab,
//STRIP001 /*?*/                                    aPattern );
//STRIP001 /*?*/
//STRIP001 /*?*/        pDoc->RemoveFlagsTab( aExtended.aStart.Col(), aExtended.aStart.Row(),
//STRIP001 /*?*/                                aExtended.aEnd.Col(), aExtended.aEnd.Row(), nTab,
//STRIP001 /*?*/                                SC_MF_HOR | SC_MF_VER );
//STRIP001 /*?*/
//STRIP001 /*?*/        pDoc->ExtendMerge( aRefresh, TRUE, FALSE );
//STRIP001 /*?*/
//STRIP001 /*?*/        if ( !AdjustRowHeight( aExtended ) )
//STRIP001 /*?*/            rDocShell.PostPaint( aExtended, PAINT_GRID );
//STRIP001 /*?*/        aModificator.SetDocumentModified();
//STRIP001 /*?*/    }
//STRIP001 /*?*/    else if (!bApi)
//STRIP001 /*?*/        Sound::Beep();      //! FALSE zurueck???
//STRIP001 /*?*/
/*N*/   return TRUE;
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 BOOL ScDocFunc::SetNote( const ScAddress& rPos, const ScPostIt& rNote, BOOL bApi )
//STRIP001 {
//STRIP001  ScDocShellModificator aModificator( rDocShell );
//STRIP001
//STRIP001  BOOL bDone = FALSE;
//STRIP001  USHORT nCol = rPos.Col();
//STRIP001  USHORT nRow = rPos.Row();
//STRIP001  USHORT nTab = rPos.Tab();
//STRIP001
//STRIP001  ScDocument* pDoc = rDocShell.GetDocument();
//STRIP001  BOOL bUndo (pDoc->IsUndoEnabled());
//STRIP001  ScEditableTester aTester( pDoc, nTab, nCol,nRow, nCol,nRow );
//STRIP001  if (aTester.IsEditable())
//STRIP001  {
//STRIP001      pDoc->SetNote( nCol, nRow, nTab, rNote );
//STRIP001
//STRIP001      if (bUndo)
//STRIP001      {
//STRIP001          ScPostIt aOld;
//STRIP001          pDoc->GetNote( nCol, nRow, nTab, aOld );
//STRIP001          rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001              new ScUndoEditNote( &rDocShell, rPos, aOld, rNote ) );
//STRIP001      }
//STRIP001
//STRIP001      rDocShell.PostPaintCell( nCol, nRow, nTab );
//STRIP001      aModificator.SetDocumentModified();
//STRIP001      bDone = TRUE;
//STRIP001  }
//STRIP001  else if (!bApi)
//STRIP001      rDocShell.ErrorMessage(aTester.GetMessageId());
//STRIP001
//STRIP001  return bDone;
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ BOOL ScDocFunc::ModifyRangeNames( const ScRangeName& rNewRanges, BOOL bApi )
/*N*/ {
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   BOOL bUndo(pDoc->IsUndoEnabled());
/*N*/
/*N*/   if (bUndo)
/*N*/   {
/*N*/       ScRangeName* pOld = pDoc->GetRangeName();
/*N*/       ScRangeName* pUndoRanges = new ScRangeName(*pOld);
/*N*/       ScRangeName* pRedoRanges = new ScRangeName(rNewRanges);
/*N*/       rDocShell.GetUndoManager()->AddUndoAction(
/*N*/           new ScUndoRangeNames( &rDocShell, pUndoRanges, pRedoRanges ) );
/*N*/   }
/*N*/
/*N*/   pDoc->CompileNameFormula( TRUE );   // CreateFormulaString
/*N*/   pDoc->SetRangeName( new ScRangeName( rNewRanges ) );
/*N*/   pDoc->CompileNameFormula( FALSE );  // CompileFormulaString
/*N*/
/*N*/   aModificator.SetDocumentModified();
/*N*/   SFX_APP()->Broadcast( SfxSimpleHint( SC_HINT_AREAS_CHANGED ) );
/*N*/
/*N*/   return TRUE;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void ScDocFunc::CreateOneName( ScRangeName& rList,
/*N*/                               USHORT nPosX, USHORT nPosY, USHORT nTab,
/*N*/                               USHORT nX1, USHORT nY1, USHORT nX2, USHORT nY2,
/*N*/                               BOOL& rCancel, BOOL bApi )
/*N*/ {
/*N*/   if (rCancel)
/*N*/       return;
/*N*/
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   if (!pDoc->HasValueData( nPosX, nPosY, nTab ))
/*N*/   {
/*N*/       String aName;
/*N*/       pDoc->GetString( nPosX, nPosY, nTab, aName );
/*N*/       ScRangeData::MakeValidName(aName);
/*N*/       if (aName.Len())
/*N*/       {
/*N*/           String aContent;
/*N*/             ScRange( nX1, nY1, nTab, nX2, nY2, nTab ).Format( aContent, SCR_ABS_3D, pDoc );
/*N*/
/*N*/           ScRangeName* pList = pDoc->GetRangeName();
/*N*/
/*N*/           BOOL bInsert = FALSE;
/*N*/           USHORT nOldPos;
/*N*/           if (rList.SearchName( aName, nOldPos ))         // vorhanden ?
/*N*/           {
/*N*/               ScRangeData* pOld = rList[nOldPos];
/*N*/               String aOldStr;
/*N*/               pOld->GetSymbol( aOldStr );
/*N*/               if (aOldStr != aContent)
/*N*/               {
/*N*/                   if (bApi)
/*N*/                       bInsert = TRUE;     // per API nicht nachfragen
/*N*/                   else
/*N*/                   {
/*N*/                       String aTemplate = ScGlobal::GetRscString( STR_CREATENAME_REPLACE );
/*N*/
/*N*/                       String aMessage = aTemplate.GetToken( 0, '#' );
/*N*/                       aMessage += aName;
/*N*/                       aMessage += aTemplate.GetToken( 1, '#' );
/*N*/
/*N*/                       short nResult = QueryBox( rDocShell.GetDialogParent(),
/*N*/                                                   WinBits(WB_YES_NO_CANCEL | WB_DEF_YES),
/*N*/                                                   aMessage ).Execute();
/*N*/                       if ( nResult == RET_YES )
/*N*/                       {
/*N*/                           rList.AtFree(nOldPos);
/*N*/                           bInsert = TRUE;
/*N*/                       }
/*N*/                       else if ( nResult == RET_CANCEL )
/*N*/                           rCancel = TRUE;
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/           else
/*N*/               bInsert = TRUE;
/*N*/
/*N*/           if (bInsert)
/*N*/           {
/*N*/               ScRangeData* pData = new ScRangeData( pDoc, aName, aContent, nPosX, nPosY, nTab );
/*N*/               if (!rList.Insert(pData))
/*N*/               {
/*N*/                   DBG_ERROR("nanu?");
/*N*/                   delete pData;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ BOOL ScDocFunc::CreateNames( const ScRange& rRange, USHORT nFlags, BOOL bApi )
/*N*/ {
/*N*/   if (!nFlags)
/*N*/       return FALSE;       // war nix
/*N*/
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/   BOOL bDone = FALSE;
/*N*/   USHORT nStartCol = rRange.aStart.Col();
/*N*/   USHORT nStartRow = rRange.aStart.Row();
/*N*/   USHORT nEndCol = rRange.aEnd.Col();
/*N*/   USHORT nEndRow = rRange.aEnd.Row();
/*N*/   USHORT nTab = rRange.aStart.Tab();
/*N*/   DBG_ASSERT(rRange.aEnd.Tab() == nTab, "CreateNames: mehrere Tabellen geht nicht");
/*N*/
/*N*/   BOOL bValid = TRUE;
/*N*/   if ( nFlags & ( NAME_TOP | NAME_BOTTOM ) )
/*N*/       if ( nStartRow == nEndRow )
/*N*/           bValid = FALSE;
/*N*/   if ( nFlags & ( NAME_LEFT | NAME_RIGHT ) )
/*N*/       if ( nStartCol == nEndCol )
/*N*/           bValid = FALSE;
/*N*/
/*N*/   if (bValid)
/*N*/   {
/*N*/       ScDocument* pDoc = rDocShell.GetDocument();
/*N*/       ScRangeName* pNames = pDoc->GetRangeName();
/*N*/       if (!pNames)
/*N*/           return FALSE;   // soll nicht sein
/*N*/       ScRangeName aNewRanges( *pNames );
/*N*/
/*N*/       BOOL bTop    = ( ( nFlags & NAME_TOP ) != 0 );
/*N*/       BOOL bLeft   = ( ( nFlags & NAME_LEFT ) != 0 );
/*N*/       BOOL bBottom = ( ( nFlags & NAME_BOTTOM ) != 0 );
/*N*/       BOOL bRight  = ( ( nFlags & NAME_RIGHT ) != 0 );
/*N*/
/*N*/       USHORT nContX1 = nStartCol;
/*N*/       USHORT nContY1 = nStartRow;
/*N*/       USHORT nContX2 = nEndCol;
/*N*/       USHORT nContY2 = nEndRow;
/*N*/
/*N*/       if ( bTop )
/*N*/           ++nContY1;
/*N*/       if ( bLeft )
/*N*/           ++nContX1;
/*N*/       if ( bBottom )
/*N*/           --nContY2;
/*N*/       if ( bRight )
/*N*/           --nContX2;
/*N*/
/*N*/       BOOL bCancel = FALSE;
/*N*/       USHORT i;
/*N*/
/*N*/       if ( bTop )
/*N*/           for (i=nContX1; i<=nContX2; i++)
/*N*/               CreateOneName( aNewRanges, i,nStartRow,nTab, i,nContY1,i,nContY2, bCancel, bApi );
/*N*/       if ( bLeft )
/*N*/           for (i=nContY1; i<=nContY2; i++)
/*N*/               CreateOneName( aNewRanges, nStartCol,i,nTab, nContX1,i,nContX2,i, bCancel, bApi );
/*N*/       if ( bBottom )
/*N*/           for (i=nContX1; i<=nContX2; i++)
/*N*/               CreateOneName( aNewRanges, i,nEndRow,nTab, i,nContY1,i,nContY2, bCancel, bApi );
/*N*/       if ( bRight )
/*N*/           for (i=nContY1; i<=nContY2; i++)
/*N*/               CreateOneName( aNewRanges, nEndCol,i,nTab, nContX1,i,nContX2,i, bCancel, bApi );
/*N*/
/*N*/       if ( bTop && bLeft )
/*N*/           CreateOneName( aNewRanges, nStartCol,nStartRow,nTab, nContX1,nContY1,nContX2,nContY2, bCancel, bApi );
/*N*/       if ( bTop && bRight )
/*N*/           CreateOneName( aNewRanges, nEndCol,nStartRow,nTab, nContX1,nContY1,nContX2,nContY2, bCancel, bApi );
/*N*/       if ( bBottom && bLeft )
/*N*/           CreateOneName( aNewRanges, nStartCol,nEndRow,nTab, nContX1,nContY1,nContX2,nContY2, bCancel, bApi );
/*N*/       if ( bBottom && bRight )
/*N*/           CreateOneName( aNewRanges, nEndCol,nEndRow,nTab, nContX1,nContY1,nContX2,nContY2, bCancel, bApi );
/*N*/
/*N*/       bDone = ModifyRangeNames( aNewRanges, bApi );
/*N*/
/*N*/       aModificator.SetDocumentModified();
/*N*/       SFX_APP()->Broadcast( SfxSimpleHint( SC_HINT_AREAS_CHANGED ) );
/*N*/   }
/*N*/
/*N*/   return bDone;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ BOOL ScDocFunc::InsertNameList( const ScAddress& rStartPos, BOOL bApi )
/*N*/ {
/*N*/   ScDocShellModificator aModificator( rDocShell );
/*N*/
/*N*/
/*N*/   BOOL bDone = FALSE;
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   const BOOL bRecord = pDoc->IsUndoEnabled();
/*N*/   USHORT nTab = rStartPos.Tab();
/*N*/   ScDocument* pUndoDoc = NULL;
/*N*/
/*N*/   ScRangeName* pList = pDoc->GetRangeName();
/*N*/   USHORT nCount = pList->GetCount();
/*N*/   USHORT nValidCount = 0;
/*N*/   USHORT i;
/*N*/   for (i=0; i<nCount; i++)
/*N*/   {
/*N*/       ScRangeData* pData = (*pList)[i];
/*N*/       if ( !pData->HasType( RT_DATABASE ) && !pData->HasType( RT_SHARED ) )
/*N*/           ++nValidCount;
/*N*/   }
/*N*/
/*N*/   if (nValidCount)
/*N*/   {
/*N*/       USHORT nStartCol = rStartPos.Col();
/*N*/       USHORT nStartRow = rStartPos.Row();
/*N*/       USHORT nEndCol = nStartCol + 1;
/*N*/       USHORT nEndRow = nStartRow + nValidCount - 1;
/*N*/
/*N*/       ScEditableTester aTester( pDoc, nTab, nStartCol,nStartRow, nEndCol,nEndRow );
/*N*/       if (aTester.IsEditable())
/*N*/       {
/*N*/           if (bRecord)
/*N*/           {
/*N*/               pUndoDoc = new ScDocument( SCDOCMODE_UNDO );
/*N*/               pUndoDoc->InitUndo( pDoc, nTab, nTab );
/*N*/               pDoc->CopyToDocument( nStartCol,nStartRow,nTab, nEndCol,nEndRow,nTab,
/*N*/                                       IDF_ALL, FALSE, pUndoDoc );
/*N*/
/*N*/               pDoc->BeginDrawUndo();      // wegen Hoehenanpassung
/*N*/           }
/*N*/
/*N*/           ScRangeData** ppSortArray = new ScRangeData* [ nValidCount ];
/*N*/           USHORT j = 0;
/*N*/           for (i=0; i<nCount; i++)
/*N*/           {
/*N*/               ScRangeData* pData = (*pList)[i];
/*N*/               if ( !pData->HasType( RT_DATABASE ) && !pData->HasType( RT_SHARED ) )
/*N*/                   ppSortArray[j++] = pData;
/*N*/           }
/*N*/ #ifndef ICC
/*N*/           qsort( (void*)ppSortArray, nValidCount, sizeof(ScRangeData*),
/*N*/               &ScRangeData::QsortNameCompare );
/*N*/ #else
/*N*/           qsort( (void*)ppSortArray, nValidCount, sizeof(ScRangeData*),
/*N*/               ICCQsortNameCompare );
/*N*/ #endif
/*N*/           String aName;
/*N*/           String aContent;
/*N*/           String aFormula;
/*N*/           USHORT nOutRow = nStartRow;
/*N*/           for (j=0; j<nValidCount; j++)
/*N*/           {
/*N*/               ScRangeData* pData = ppSortArray[j];
/*N*/               pData->GetName(aName);
/*N*/               // relative Referenzen Excel-konform auf die linke Spalte anpassen:
/*N*/               pData->UpdateSymbol(aContent, ScAddress( nStartCol, nOutRow, nTab ));
/*N*/               aFormula = '=';
/*N*/               aFormula += aContent;
/*N*/               pDoc->PutCell( nStartCol,nOutRow,nTab, new ScStringCell( aName ) );
/*N*/               pDoc->PutCell( nEndCol  ,nOutRow,nTab, new ScStringCell( aFormula ) );
/*N*/               ++nOutRow;
/*N*/           }
/*N*/
/*N*/           delete [] ppSortArray;
/*N*/
/*N*/           if (bRecord)
/*N*/           {
/*?*/               DBG_ASSERT(0, "STRIP"); //STRIP001 ScDocument* pRedoDoc = new ScDocument( SCDOCMODE_UNDO );
//STRIP001 /*?*/                pRedoDoc->InitUndo( pDoc, nTab, nTab );
//STRIP001 /*?*/                pDoc->CopyToDocument( nStartCol,nStartRow,nTab, nEndCol,nEndRow,nTab,
//STRIP001 /*?*/                                        IDF_ALL, FALSE, pRedoDoc );
//STRIP001 /*?*/
//STRIP001 /*?*/                rDocShell.GetUndoManager()->AddUndoAction(
//STRIP001 /*?*/                    new ScUndoListNames( &rDocShell,
//STRIP001 /*?*/                                ScRange( nStartCol,nStartRow,nTab, nEndCol,nEndRow,nTab ),
//STRIP001 /*?*/                                pUndoDoc, pRedoDoc ) );
/*N*/           }
/*N*/
/*N*/           if (!AdjustRowHeight(ScRange(0,nStartRow,nTab,MAXCOL,nEndRow,nTab)))
/*N*/               rDocShell.PostPaint( nStartCol,nStartRow,nTab, nEndCol,nEndRow,nTab, PAINT_GRID );
/*N*/ //!           rDocShell.UpdateOle(GetViewData());
/*N*/           aModificator.SetDocumentModified();
/*N*/           bDone = TRUE;
/*N*/       }
/*N*/       else if (!bApi)
/*?*/           rDocShell.ErrorMessage(aTester.GetMessageId());
/*N*/   }
/*N*/   return bDone;
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 BOOL ScDocFunc::ResizeMatrix( const ScRange& rOldRange, const ScAddress& rNewEnd, BOOL bApi )
//STRIP001 {
//STRIP001  ScDocument* pDoc = rDocShell.GetDocument();
//STRIP001  USHORT nStartCol = rOldRange.aStart.Col();
//STRIP001  USHORT nStartRow = rOldRange.aStart.Row();
//STRIP001  USHORT nNewEndCol = rNewEnd.Col();
//STRIP001  USHORT nNewEndRow = rNewEnd.Row();
//STRIP001  USHORT nTab = rOldRange.aStart.Tab();
//STRIP001
//STRIP001  BOOL bUndo(pDoc->IsUndoEnabled());
//STRIP001
//STRIP001  BOOL bRet = FALSE;
//STRIP001
//STRIP001  String aFormula;
//STRIP001  pDoc->GetFormula( nStartCol, nStartRow, nTab, aFormula );
//STRIP001  if ( aFormula.GetChar(0) == '{' && aFormula.GetChar(aFormula.Len()-1) == '}' )
//STRIP001  {
//STRIP001      String aUndo = ScGlobal::GetRscString( STR_UNDO_RESIZEMATRIX );
//STRIP001      if (bUndo)
//STRIP001          rDocShell.GetUndoManager()->EnterListAction( aUndo, aUndo );
//STRIP001
//STRIP001      aFormula.Erase(0,1);
//STRIP001      aFormula.Erase(aFormula.Len()-1,1);
//STRIP001
//STRIP001      ScMarkData aMark;
//STRIP001      aMark.SetMarkArea( rOldRange );
//STRIP001      aMark.SelectTable( nTab, TRUE );
//STRIP001      ScRange aNewRange( rOldRange.aStart, rNewEnd );
//STRIP001
//STRIP001      if ( DeleteContents( aMark, IDF_CONTENTS, TRUE, bApi ) )
//STRIP001      {
//STRIP001          bRet = EnterMatrix( aNewRange, &aMark, aFormula, bApi, FALSE );
//STRIP001          if (!bRet)
//STRIP001          {
//STRIP001              //  versuchen, alten Zustand wiederherzustellen
//STRIP001              EnterMatrix( rOldRange, &aMark, aFormula, bApi, FALSE );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if (bUndo)
//STRIP001          rDocShell.GetUndoManager()->LeaveListAction();
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

//------------------------------------------------------------------------

/*N*/ BOOL ScDocFunc::InsertAreaLink( const String& rFile, const String& rFilter,
/*N*/                               const String& rOptions, const String& rSource,
/*N*/                               const ScRange& rDestRange, ULONG nRefresh,
/*N*/                               BOOL bFitBlock, BOOL bApi )
/*N*/ {
/*N*/   //! auch fuer ScViewFunc::InsertAreaLink benutzen!
/*N*/
/*N*/   ScDocument* pDoc = rDocShell.GetDocument();
/*N*/   BOOL bUndo (pDoc->IsUndoEnabled());
/*N*/
/*N*/   String aFilterName = rFilter;
/*N*/   String aNewOptions = rOptions;
/*N*/   if (!aFilterName.Len())
/*N*/       ScDocumentLoader::GetFilterName( rFile, aFilterName, aNewOptions );
/*N*/
/*N*/   //  remove application prefix from filter name here, so the filter options
/*N*/   //  aren't reset when the filter name is changed in ScAreaLink::DataChanged
/*N*/   ScDocumentLoader::RemoveAppPrefix( aFilterName );
/*N*/
/*N*/   SvxLinkManager* pLinkManager = pDoc->GetLinkManager();
/*N*/
/*N*/   ScAreaLink* pLink = new ScAreaLink( &rDocShell, rFile, aFilterName,
/*N*/                                       aNewOptions, rSource, rDestRange, nRefresh );
/*N*/   pLinkManager->InsertFileLink( *pLink, OBJECT_CLIENT_FILE, rFile, &aFilterName, &rSource );
/*N*/
/*N*/   //  Undo fuer den leeren Link
/*N*/
/*N*/   if (bUndo)
/*?*/       {DBG_ASSERT(0, "STRIP");} //STRIP001 rDocShell.GetUndoManager()->AddUndoAction( new ScUndoInsertAreaLink( &rDocShell,
//STRIP001 /*?*/                                                    rFile, aFilterName, aNewOptions,
//STRIP001 /*?*/                                                    rSource, rDestRange, nRefresh ) );
/*N*/
/*N*/   //  Update hat sein eigenes Undo
/*N*/
/*N*/   pLink->SetDoInsert(bFitBlock);  // beim ersten Update ggf. nichts einfuegen
/*N*/   pLink->Update();                // kein SetInCreate -> Update ausfuehren
/*N*/   pLink->SetDoInsert(TRUE);       // Default = TRUE
/*N*/
/*N*/   SfxBindings* pBindings = rDocShell.GetViewBindings();
/*N*/   if (pBindings)
/*N*/       pBindings->Invalidate( SID_LINKS );
/*N*/
/*N*/   SFX_APP()->Broadcast( SfxSimpleHint( SC_HINT_AREALINKS_CHANGED ) );     // Navigator
/*N*/
/*N*/   return TRUE;
/*N*/ }




}
