/*************************************************************************
 *
 *  $RCSfile: sc_drwlayer.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:26:04 $
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
#include "core_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------


#include "scitems.hxx"
#include <bf_svx/eeitem.hxx>
#define ITEMID_FIELD EE_FEATURE_FIELD

#ifndef _SVX_FRMDIRITEM_HXX
#include <bf_svx/frmdiritem.hxx>
#endif
#include <bf_svx/objfac3d.hxx>
#include <bf_svx/svdoutl.hxx>
#include <bf_svx/svditer.hxx>
#include <bf_svx/svdocapt.hxx>
#include <bf_svx/svdocirc.hxx>
#include <bf_svx/svdoedge.hxx>
#include <bf_svx/svdograf.hxx>
#include <bf_svx/svdoole2.hxx>
#include <bf_svx/svdundo.hxx>
#include <bf_svx/unolingu.hxx>
#include <bf_svx/drawitem.hxx>
#ifndef _SVX_FHGTITEM_HXX
#include <bf_svx/fhgtitem.hxx>
#endif
#include <bf_sfx2/viewsh.hxx>
#include <bf_sfx2/docinf.hxx>
#include <bf_sfx2/docfile.hxx>
#include <so3/ipobj.hxx>
#include <so3/svstor.hxx>
#include <svtools/pathoptions.hxx>
#include <svtools/itempool.hxx>
#include <vcl/virdev.hxx>
#include <bf_offmgr/app.hxx>
#include <bf_sch/schdll.hxx>
#include <bf_sch/schdll0.hxx>
#include <bf_sch/memchrt.hxx>

#include "drwlayer.hxx"
#include "drawpage.hxx"
#include "global.hxx"
#include "document.hxx"
#include "rechead.hxx"
#include "userdat.hxx"
#include "markdata.hxx"
#include "globstr.hrc"
#include "scmod.hxx"
#include "chartarr.hxx"
namespace binfilter {

#define DET_ARROW_OFFSET    1000

//  Abstand zur naechsten Zelle beim Loeschen (bShrink), damit der Anker
//  immer an der richtigen Zelle angezeigt wird
//#define SHRINK_DIST       3
//  und noch etwas mehr, damit das Objekt auch sichtbar in der Zelle liegt
#define SHRINK_DIST     25

#define SHRINK_DIST_TWIPS   15

// -----------------------------------------------------------------------
//
//  Das Anpassen der Detektiv-UserData muss zusammen mit den Draw-Undo's
//  in der SdrUndoGroup liegen, darum von SdrUndoAction abgeleitet:

//STRIP001 class ScUndoObjData : public SdrUndoObj
//STRIP001 {
//STRIP001 private:
//STRIP001  ScTripel    aOldStt;
//STRIP001  ScTripel    aOldEnd;
//STRIP001  ScTripel    aNewStt;
//STRIP001  ScTripel    aNewEnd;
//STRIP001  BOOL        bHasNew;
//STRIP001 public:
//STRIP001              ScUndoObjData( SdrObject* pObj, const ScTripel& rOS, const ScTripel& rOE,
//STRIP001                                              const ScTripel& rNS, const ScTripel& rNE );
//STRIP001              ~ScUndoObjData();
//STRIP001
//STRIP001  virtual void     Undo();
//STRIP001  virtual void     Redo();
//STRIP001 };

// -----------------------------------------------------------------------

// STATIC DATA -----------------------------------------------------------

/*N*/ TYPEINIT1(ScTabDeletedHint, SfxHint);
/*N*/ TYPEINIT1(ScTabSizeChangedHint, SfxHint);

static ScDrawObjFactory* pFac = NULL;
static E3dObjFactory* pF3d = NULL;
static USHORT nInst = 0;

SvPersist* ScDrawLayer::pGlobalDrawPersist = NULL;

BOOL bDrawIsInUndo = FALSE;         //! Member

// -----------------------------------------------------------------------

//STRIP001 ScUndoObjData::ScUndoObjData( SdrObject* pObj, const ScTripel& rOS, const ScTripel& rOE,
//STRIP001                                             const ScTripel& rNS, const ScTripel& rNE ) :
//STRIP001  SdrUndoObj( *pObj ),
//STRIP001  aOldStt( rOS ),
//STRIP001  aOldEnd( rOE ),
//STRIP001  aNewStt( rNS ),
//STRIP001  aNewEnd( rNE )
//STRIP001 {
//STRIP001 }

//STRIP001 __EXPORT ScUndoObjData::~ScUndoObjData()
//STRIP001 {
//STRIP001 }

//STRIP001 void __EXPORT ScUndoObjData::Undo()
//STRIP001 {
//STRIP001  ScDrawObjData* pData = ((ScDrawLayer&)rMod).GetObjData( pObj );
//STRIP001  DBG_ASSERT(pData,"ScUndoObjData: Daten nicht da");
//STRIP001  if (pData)
//STRIP001  {
//STRIP001      pData->aStt = aOldStt;
//STRIP001      pData->aEnd = aOldEnd;
//STRIP001  }
//STRIP001 }

//STRIP001 void __EXPORT ScUndoObjData::Redo()
//STRIP001 {
//STRIP001  ScDrawObjData* pData = ((ScDrawLayer&)rMod).GetObjData( pObj );
//STRIP001  DBG_ASSERT(pData,"ScUndoObjData: Daten nicht da");
//STRIP001  if (pData)
//STRIP001  {
//STRIP001      pData->aStt = aNewStt;
//STRIP001      pData->aEnd = aNewEnd;
//STRIP001  }
//STRIP001 }

// -----------------------------------------------------------------------

/*N*/ ScTabDeletedHint::ScTabDeletedHint( USHORT nTabNo ) :
/*N*/   nTab( nTabNo )
/*N*/ {
/*N*/ }

/*N*/ __EXPORT ScTabDeletedHint::~ScTabDeletedHint()
/*N*/ {
/*N*/ }

/*N*/ ScTabSizeChangedHint::ScTabSizeChangedHint( USHORT nTabNo ) :
/*N*/   nTab( nTabNo )
/*N*/ {
/*N*/ }

/*N*/ __EXPORT ScTabSizeChangedHint::~ScTabSizeChangedHint()
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------

#define MAXMM   10000000

/*N*/ inline void TwipsToMM( long& nVal )
/*N*/ {
/*N*/   nVal = (long) ( nVal * HMM_PER_TWIPS );
/*N*/ }

/*N*/ inline void ReverseTwipsToMM( long& nVal )
/*N*/ {
/*N*/   //  reverse the effect of TwipsToMM - round up here (add 1)
/*N*/
/*N*/   nVal = ((long) ( nVal / HMM_PER_TWIPS )) + 1;
/*N*/ }

/*N*/ void lcl_TwipsToMM( Point& rPoint )
/*N*/ {
/*N*/   TwipsToMM( rPoint.X() );
/*N*/   TwipsToMM( rPoint.Y() );
/*N*/ }

/*N*/ void lcl_ReverseTwipsToMM( Point& rPoint )
/*N*/ {
/*N*/   ReverseTwipsToMM( rPoint.X() );
/*N*/   ReverseTwipsToMM( rPoint.Y() );
/*N*/ }

/*N*/ void lcl_ReverseTwipsToMM( Rectangle& rRect )
/*N*/ {
/*N*/   ReverseTwipsToMM( rRect.Left() );
/*N*/   ReverseTwipsToMM( rRect.Right() );
/*N*/   ReverseTwipsToMM( rRect.Top() );
/*N*/   ReverseTwipsToMM( rRect.Bottom() );
/*N*/ }

// -----------------------------------------------------------------------


/*N*/ ScDrawLayer::ScDrawLayer( ScDocument* pDocument, const String& rName ) :
/*N*/   FmFormModel( SvtPathOptions().GetPalettePath(),
/*N*/                NULL,                          // SfxItemPool* Pool
/*N*/                pGlobalDrawPersist ?
/*N*/                   pGlobalDrawPersist :
/*N*/                   ( pDocument ? pDocument->GetDocumentShell() : NULL ),
/*N*/                TRUE ),        // bUseExtColorTable (is set below)
/*N*/   aName( rName ),
/*N*/   pDoc( pDocument ),
/*N*/   pUndoGroup( NULL ),
/*N*/   bRecording( FALSE ),
/*N*/   bAdjustEnabled( TRUE ),
/*N*/   bHyphenatorSet( FALSE )
/*N*/ {
/*N*/   pGlobalDrawPersist = NULL;          // nur einmal benutzen
/*N*/
/*N*/   SfxObjectShell* pObjSh = pDocument ? pDocument->GetDocumentShell() : NULL;
/*N*/   if ( pObjSh )
/*N*/   {
/*N*/       SetObjectShell( pObjSh );
/*N*/
/*N*/       // set color table
/*N*/       SvxColorTableItem* pColItem = (SvxColorTableItem*) pObjSh->GetItem( ITEMID_COLOR_TABLE );
/*N*/       XColorTable* pXCol = pColItem ? pColItem->GetColorTable() : OFF_APP()->GetStdColorTable();
/*N*/       SetColorTable( pXCol );
/*N*/   }
/*N*/   else
/*?*/       SetColorTable( OFF_APP()->GetStdColorTable() );
/*N*/
/*N*/   SetSwapGraphics(TRUE);
/*N*/ //    SetSwapAsynchron(TRUE);     // an der View
/*N*/
/*N*/   SetScaleUnit(MAP_100TH_MM);
/*N*/   SfxItemPool& rPool = GetItemPool();
/*N*/   rPool.SetDefaultMetric(SFX_MAPUNIT_100TH_MM);
/*N*/   SvxFrameDirectionItem aModeItem( FRMDIR_ENVIRONMENT, EE_PARA_WRITINGDIR );
/*N*/   rPool.SetPoolDefaultItem( aModeItem );
/*N*/   rPool.FreezeIdRanges();                         // der Pool wird auch direkt verwendet
/*N*/
/*N*/   SdrLayerAdmin& rAdmin = GetLayerAdmin();
/*N*/   rAdmin.NewLayer(String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("vorne")),    SC_LAYER_FRONT);
/*N*/   rAdmin.NewLayer(String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("hinten")),   SC_LAYER_BACK);
/*N*/   rAdmin.NewLayer(String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("intern")),   SC_LAYER_INTERN);
/*N*/   rAdmin.NewLayer(String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("Controls")), SC_LAYER_CONTROLS);
/*N*/   // "Controls" is new - must also be created when loading
/*N*/
/*N*/   //  Link fuer URL-Fields setzen
/*N*/   ScModule* pScMod = SC_MOD();
/*N*/   Outliner& rOutliner = GetDrawOutliner();
/*N*/   rOutliner.SetCalcFieldValueHdl( LINK( pScMod, ScModule, CalcFieldValueHdl ) );
/*N*/
/*N*/   Outliner& rHitOutliner = GetHitTestOutliner();
/*N*/   rHitOutliner.SetCalcFieldValueHdl( LINK( pScMod, ScModule, CalcFieldValueHdl ) );
/*N*/
/*N*/     // #95129# SJ: set FontHeight pool defaults without changing static SdrEngineDefaults
/*N*/     SfxItemPool* pOutlinerPool = rOutliner.GetEditTextObjectPool();
/*N*/     if ( pOutlinerPool )
/*N*/       pItemPool->SetPoolDefaultItem(SvxFontHeightItem( 423, 100, EE_CHAR_FONTHEIGHT ));           // 12Pt
/*N*/     SfxItemPool* pHitOutlinerPool = rHitOutliner.GetEditTextObjectPool();
/*N*/     if ( pHitOutlinerPool )
/*N*/       pHitOutlinerPool->SetPoolDefaultItem(SvxFontHeightItem( 423, 100, EE_CHAR_FONTHEIGHT ));    // 12Pt
/*N*/
/*N*/   //  URL-Buttons haben keinen Handler mehr, machen alles selber
/*N*/
/*N*/   if( !nInst++ )
/*N*/   {
/*N*/       pFac = new ScDrawObjFactory;
/*N*/       pF3d = new E3dObjFactory;
/*N*/   }
/*N*/ }

/*N*/ __EXPORT ScDrawLayer::~ScDrawLayer()
/*N*/ {
/*N*/   Broadcast(SdrHint(HINT_MODELCLEARED));
/*N*/
/*N*/   Clear();
/*N*/
/*N*/   delete pUndoGroup;
/*N*/   if( !--nInst )
/*N*/   {
/*N*/       delete pFac, pFac = NULL;
/*N*/       delete pF3d, pF3d = NULL;
/*N*/   }
/*N*/ }

//STRIP001 void ScDrawLayer::UseHyphenator()
//STRIP001 {
//STRIP001  if (!bHyphenatorSet)
//STRIP001  {
//STRIP001      ::com::sun::star::uno::Reference< ::com::sun::star::linguistic2::XHyphenator >
//STRIP001                                  xHyphenator = LinguMgr::GetHyphenator();
//STRIP001
//STRIP001      GetDrawOutliner().SetHyphenator( xHyphenator );
//STRIP001      GetHitTestOutliner().SetHyphenator( xHyphenator );
//STRIP001
//STRIP001      bHyphenatorSet = TRUE;
//STRIP001  }
//STRIP001 }

/*N*/ SdrPage* __EXPORT ScDrawLayer::AllocPage(FASTBOOL bMasterPage)
/*N*/ {
/*N*/   //  don't create basic until it is needed
/*N*/   StarBASIC* pBasic = NULL;
/*N*/   ScDrawPage* pPage = new ScDrawPage( *this, pBasic, bMasterPage );
/*N*/   return pPage;
/*N*/ }

//STRIP001 BOOL ScDrawLayer::HasObjects() const
//STRIP001 {
//STRIP001  BOOL bFound = FALSE;
//STRIP001
//STRIP001  USHORT nCount = GetPageCount();
//STRIP001  for (USHORT i=0; i<nCount && !bFound; i++)
//STRIP001      if (GetPage(i)->GetObjCount())
//STRIP001          bFound = TRUE;
//STRIP001
//STRIP001  return bFound;
//STRIP001 }

/*N*/ void ScDrawLayer::UpdateBasic()
/*N*/ {
/*N*/   //  don't create basic until it is needed
/*N*/   //! remove this method?
/*N*/ }

//STRIP001 SdrModel* __EXPORT ScDrawLayer::AllocModel() const
//STRIP001 {
//STRIP001  //  #103849# Allocated model (for clipboard etc) must not have a pointer
//STRIP001  //  to the original model's document, pass NULL as document:
//STRIP001
//STRIP001  return new ScDrawLayer( NULL, aName );
//STRIP001 }

//STRIP001 Window* __EXPORT ScDrawLayer::GetCurDocViewWin()
//STRIP001 {
//STRIP001  DBG_ASSERT( pDoc, "ScDrawLayer::GetCurDocViewWin without document" );
//STRIP001  if ( !pDoc )
//STRIP001      return NULL;
//STRIP001
//STRIP001  SfxViewShell* pViewSh = SfxViewShell::Current();
//STRIP001  SfxObjectShell* pObjSh = pDoc->GetDocumentShell();
//STRIP001
//STRIP001  if (pViewSh && pViewSh->GetObjectShell() == pObjSh)
//STRIP001      return pViewSh->GetWindow();
//STRIP001
//STRIP001  return NULL;
//STRIP001 }

/*N*/ void ScDrawLayer::ScAddPage( USHORT nTab )
/*N*/ {
/*N*/   if (bDrawIsInUndo)
/*N*/       return;
/*N*/
/*N*/   ScDrawPage* pPage = (ScDrawPage*)AllocPage( FALSE );
/*N*/   InsertPage(pPage, nTab);
/*N*/   if (bRecording)
/*N*/       AddCalcUndo(new SdrUndoNewPage(*pPage));
/*N*/ }

//STRIP001 void ScDrawLayer::ScRemovePage( USHORT nTab )
//STRIP001 {
//STRIP001  if (bDrawIsInUndo)
//STRIP001      return;
//STRIP001
//STRIP001  Broadcast( ScTabDeletedHint( nTab ) );
//STRIP001  if (bRecording)
//STRIP001  {
//STRIP001      SdrPage* pPage = GetPage(nTab);
//STRIP001      AddCalcUndo(new SdrUndoDelPage(*pPage));        // Undo-Action wird Owner der Page
//STRIP001      RemovePage( nTab );                         // nur austragen, nicht loeschen
//STRIP001  }
//STRIP001  else
//STRIP001      DeletePage( nTab );                         // einfach weg damit
//STRIP001 }

/*N*/ void ScDrawLayer::ScRenamePage( USHORT nTab, const String& rNewName )
/*N*/ {
/*N*/   ScDrawPage* pPage = (ScDrawPage*) GetPage(nTab);
/*N*/   if (pPage)
/*N*/       pPage->SetName(rNewName);
/*N*/ }

//STRIP001 void ScDrawLayer::ScMovePage( USHORT nOldPos, USHORT nNewPos )
//STRIP001 {
//STRIP001  MovePage( nOldPos, nNewPos );
//STRIP001 }

//STRIP001 void ScDrawLayer::ScCopyPage( USHORT nOldPos, USHORT nNewPos, BOOL bAlloc )
//STRIP001 {
//STRIP001  //! remove argument bAlloc (always FALSE)
//STRIP001
//STRIP001  if (bDrawIsInUndo)
//STRIP001      return;
//STRIP001
//STRIP001  SdrPage* pOldPage = GetPage(nOldPos);
//STRIP001  SdrPage* pNewPage = bAlloc ? AllocPage(FALSE) : GetPage(nNewPos);
//STRIP001
//STRIP001  // kopieren
//STRIP001
//STRIP001  if (pOldPage && pNewPage)
//STRIP001  {
//STRIP001      SdrObjListIter aIter( *pOldPage, IM_FLAT );
//STRIP001      SdrObject* pOldObject = aIter.Next();
//STRIP001      while (pOldObject)
//STRIP001      {
//STRIP001          SdrObject* pNewObject = pOldObject->Clone( pNewPage, this );
//STRIP001          pNewObject->NbcMove(Size(0,0));
//STRIP001          pNewPage->InsertObject( pNewObject );
//STRIP001          if (bRecording)
//STRIP001              AddCalcUndo( new SdrUndoInsertObj( *pNewObject ) );
//STRIP001
//STRIP001          pOldObject = aIter.Next();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if (bAlloc)
//STRIP001      InsertPage(pNewPage, nNewPos);
//STRIP001 }

//STRIP001 inline BOOL IsInBlock( const ScTripel& rPos, USHORT nCol1,USHORT nRow1, USHORT nCol2,USHORT nRow2 )
//STRIP001 {
//STRIP001  return rPos.nCol >= nCol1 && rPos.nCol <= nCol2 &&
//STRIP001         rPos.nRow >= nRow1 && rPos.nRow <= nRow2;
//STRIP001 }

//STRIP001 void ScDrawLayer::MoveCells( USHORT nTab, USHORT nCol1,USHORT nRow1, USHORT nCol2,USHORT nRow2,
//STRIP001                              short nDx,short nDy )
//STRIP001 {
//STRIP001  SdrPage* pPage = GetPage(nTab);
//STRIP001  DBG_ASSERT(pPage,"Page nicht gefunden");
//STRIP001  if (!pPage)
//STRIP001      return;
//STRIP001
//STRIP001  ULONG nCount = pPage->GetObjCount();
//STRIP001  for ( ULONG i = 0; i < nCount; i++ )
//STRIP001  {
//STRIP001      SdrObject* pObj = pPage->GetObj( i );
//STRIP001      ScDrawObjData* pData = GetObjData( pObj );
//STRIP001      if( pData )
//STRIP001      {
//STRIP001          ScTripel aOldStt = pData->aStt;
//STRIP001          ScTripel aOldEnd = pData->aEnd;
//STRIP001          BOOL bChange = FALSE;
//STRIP001          if ( pData->bValidStart && IsInBlock( pData->aStt, nCol1,nRow1, nCol2,nRow2 ) )
//STRIP001          {
//STRIP001              pData->aStt.nCol += nDx;
//STRIP001              pData->aStt.nRow += nDy;
//STRIP001              bChange = TRUE;
//STRIP001          }
//STRIP001          if ( pData->bValidEnd && IsInBlock( pData->aEnd, nCol1,nRow1, nCol2,nRow2 ) )
//STRIP001          {
//STRIP001              pData->aEnd.nCol += nDx;
//STRIP001              pData->aEnd.nRow += nDy;
//STRIP001              bChange = TRUE;
//STRIP001          }
//STRIP001          if (bChange)
//STRIP001          {
//STRIP001              if ( pObj->ISA(SdrRectObj) && pData->bValidStart && pData->bValidEnd )
//STRIP001              {
//STRIP001                  PutInOrder( pData->aStt.nCol, pData->aEnd.nCol );
//STRIP001                  PutInOrder( pData->aStt.nRow, pData->aEnd.nRow );
//STRIP001              }
//STRIP001              AddCalcUndo( new ScUndoObjData( pObj, aOldStt, aOldEnd, pData->aStt, pData->aEnd ) );
//STRIP001              RecalcPos( pObj, pData );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*N*/ void ScDrawLayer::SetPageSize( USHORT nPageNo, const Size& rSize )
/*N*/ {
/*N*/   SdrPage* pPage = GetPage(nPageNo);
/*N*/   if (pPage)
/*N*/   {
/*N*/       if ( rSize != pPage->GetSize() )
/*N*/       {
/*N*/           pPage->SetSize( rSize );
/*N*/           Broadcast( ScTabSizeChangedHint( nPageNo ) );   // SetWorkArea() an den Views
/*N*/       }
/*N*/
/*N*/       // Detektivlinien umsetzen (an neue Hoehen/Breiten anpassen)
/*N*/       //  auch wenn Groesse gleich geblieben ist
/*N*/       //  (einzelne Zeilen/Spalten koennen geaendert sein)
/*N*/
/*N*/       ULONG nCount = pPage->GetObjCount();
/*N*/       for ( ULONG i = 0; i < nCount; i++ )
/*N*/       {
/*N*/           SdrObject* pObj = pPage->GetObj( i );
/*N*/           ScDrawObjData* pData = GetObjData( pObj );
/*N*/           if( pData )
DBG_ASSERT(0, "STRIP"); //STRIP001 /*?*/                RecalcPos( pObj, pData );
/*N*/       }
/*N*/   }
/*N*/ }

//STRIP001 void ScDrawLayer::RecalcPos( SdrObject* pObj, ScDrawObjData* pData )
//STRIP001 {
//STRIP001  DBG_ASSERT( pDoc, "ScDrawLayer::RecalcPos without document" );
//STRIP001  if ( !pDoc )
//STRIP001      return;
//STRIP001
//STRIP001  BOOL bArrow = ( pObj->IsPolyObj() && pObj->GetPointCount()==2 );    // Pfeil ?
//STRIP001  BOOL bCircle = ( pObj->ISA(SdrCircObj) );                           // Kreis (Gueltigkeit)
//STRIP001  BOOL bCaption = ( pObj->ISA(SdrCaptionObj) );                       // Notiz
//STRIP001
//STRIP001  if (bCaption)
//STRIP001  {
//STRIP001      SdrCaptionObj* pCaptObj = (SdrCaptionObj*) pObj;
//STRIP001
//STRIP001      USHORT nCol = pData->aStt.nCol;
//STRIP001      USHORT nRow = pData->aStt.nRow;
//STRIP001      USHORT nTab = pData->aStt.nTab;
//STRIP001      Point aPos( pDoc->GetColOffset( nCol+1, nTab ),
//STRIP001                  pDoc->GetRowOffset( nRow, nTab ) );
//STRIP001      TwipsToMM( aPos.X() );
//STRIP001      TwipsToMM( aPos.Y() );
//STRIP001      aPos.X() -= 10;
//STRIP001
//STRIP001      Point aOldTail = pCaptObj->GetTailPos();
//STRIP001      if ( aOldTail != aPos )
//STRIP001      {
//STRIP001          pCaptObj->SetTailPos(aPos);
//STRIP001
//STRIP001          //  Rest in gleichem Abstand mitverschieben
//STRIP001
//STRIP001          Rectangle aOldLogic = pObj->GetLogicRect();
//STRIP001          long nDiffX = aOldLogic.Left() - aOldTail.X();
//STRIP001          long nDiffY = aOldLogic.Top() - aOldTail.Y();
//STRIP001          Point aNewStart( aPos.X() + nDiffX, aPos.Y() + nDiffY );
//STRIP001          if ( aNewStart.X() < 0 ) aNewStart.X() = 0;
//STRIP001          if ( aNewStart.Y() < 0 ) aNewStart.Y() = 0;
//STRIP001          Rectangle aNewLogic( aNewStart, aOldLogic.GetSize() );
//STRIP001
//STRIP001          if ( aNewLogic != aOldLogic )
//STRIP001          {
//STRIP001              if (bRecording)
//STRIP001                  AddCalcUndo( new SdrUndoGeoObj( *pObj ) );
//STRIP001              pObj->SetLogicRect(aNewLogic);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else if (bCircle)                   // Kreis (Gueltigkeit)
//STRIP001  {
//STRIP001      USHORT nCol = pData->aStt.nCol;
//STRIP001      USHORT nRow = pData->aStt.nRow;
//STRIP001      USHORT nTab = pData->aStt.nTab;
//STRIP001      Point aPos( pDoc->GetColOffset( nCol, nTab ), pDoc->GetRowOffset( nRow, nTab ) );
//STRIP001      TwipsToMM( aPos.X() );
//STRIP001      TwipsToMM( aPos.Y() );
//STRIP001
//STRIP001      //  Berechnung und Werte wie in detfunc.cxx
//STRIP001
//STRIP001      Size aSize( (long) ( pDoc->GetColWidth(nCol, nTab) * HMM_PER_TWIPS ),
//STRIP001                  (long) ( pDoc->GetRowHeight(nRow, nTab) * HMM_PER_TWIPS ) );
//STRIP001      Rectangle aRect( aPos, aSize );
//STRIP001      aRect.Left()    -= 250;
//STRIP001      aRect.Right()   += 250;
//STRIP001      aRect.Top()     -= 70;
//STRIP001      aRect.Bottom()  += 70;
//STRIP001
//STRIP001      if ( pObj->GetLogicRect() != aRect )
//STRIP001      {
//STRIP001          if (bRecording)
//STRIP001              AddCalcUndo( new SdrUndoGeoObj( *pObj ) );
//STRIP001          pObj->SetLogicRect(aRect);
//STRIP001      }
//STRIP001  }
//STRIP001  else if (bArrow)                    // Pfeil
//STRIP001  {
//STRIP001      //! nicht mehrere Undos fuer ein Objekt erzeugen (hinteres kann dann weggelassen werden)
//STRIP001
//STRIP001      if( pData->bValidStart )
//STRIP001      {
//STRIP001          Point aPos(
//STRIP001              pDoc->GetColOffset( pData->aStt.nCol, pData->aStt.nTab ),
//STRIP001              pDoc->GetRowOffset( pData->aStt.nRow, pData->aStt.nTab ) );
//STRIP001          if( !( pDoc->GetColFlags( pData->aStt.nCol, pData->aStt.nTab )
//STRIP001               & CR_HIDDEN ) )
//STRIP001              aPos.X() += pDoc->GetColWidth( pData->aStt.nCol, pData->aStt.nTab ) / 4;
//STRIP001          if( !( pDoc->GetRowFlags( pData->aStt.nRow, pData->aStt.nTab )
//STRIP001               & CR_HIDDEN ) )
//STRIP001              aPos.Y() += pDoc->GetRowHeight( pData->aStt.nRow, pData->aStt.nTab ) / 2;
//STRIP001          TwipsToMM( aPos.X() );
//STRIP001          TwipsToMM( aPos.Y() );
//STRIP001          if ( pObj->GetPoint(0) != aPos )
//STRIP001          {
//STRIP001              if (bRecording)
//STRIP001                  AddCalcUndo( new SdrUndoGeoObj( *pObj ) );
//STRIP001              pObj->SetPoint( aPos, 0 );
//STRIP001          }
//STRIP001
//STRIP001          if( !pData->bValidEnd )
//STRIP001          {
//STRIP001              Point aEndPos( aPos.X() + DET_ARROW_OFFSET, aPos.Y() - DET_ARROW_OFFSET );
//STRIP001              if (aEndPos.Y() < 0)
//STRIP001                  aEndPos.Y() += 2*DET_ARROW_OFFSET;
//STRIP001              if ( pObj->GetPoint(1) != aEndPos )
//STRIP001              {
//STRIP001                  if (bRecording)
//STRIP001                      AddCalcUndo( new SdrUndoGeoObj( *pObj ) );
//STRIP001                  pObj->SetPoint( aEndPos, 1 );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      if( pData->bValidEnd )
//STRIP001      {
//STRIP001          Point aPos(
//STRIP001              pDoc->GetColOffset( pData->aEnd.nCol, pData->aEnd.nTab ),
//STRIP001              pDoc->GetRowOffset( pData->aEnd.nRow, pData->aEnd.nTab ) );
//STRIP001          if( !( pDoc->GetColFlags( pData->aEnd.nCol, pData->aEnd.nTab )
//STRIP001               & CR_HIDDEN ) )
//STRIP001              aPos.X() += pDoc->GetColWidth( pData->aEnd.nCol, pData->aEnd.nTab ) / 4;
//STRIP001          if( !( pDoc->GetRowFlags( pData->aEnd.nRow, pData->aEnd.nTab )
//STRIP001               & CR_HIDDEN ) )
//STRIP001              aPos.Y() += pDoc->GetRowHeight( pData->aEnd.nRow, pData->aEnd.nTab ) / 2;
//STRIP001          TwipsToMM( aPos.X() );
//STRIP001          TwipsToMM( aPos.Y() );
//STRIP001          if ( pObj->GetPoint(1) != aPos )
//STRIP001          {
//STRIP001              if (bRecording)
//STRIP001                  AddCalcUndo( new SdrUndoGeoObj( *pObj ) );
//STRIP001              pObj->SetPoint( aPos, 1 );
//STRIP001          }
//STRIP001
//STRIP001          if( !pData->bValidStart )
//STRIP001          {
//STRIP001              Point aStartPos( aPos.X() - DET_ARROW_OFFSET, aPos.Y() - DET_ARROW_OFFSET );
//STRIP001              if (aStartPos.X() < 0)
//STRIP001                  aStartPos.X() += 2*DET_ARROW_OFFSET;
//STRIP001              if (aStartPos.Y() < 0)
//STRIP001                  aStartPos.Y() += 2*DET_ARROW_OFFSET;
//STRIP001              if ( pObj->GetPoint(0) != aStartPos )
//STRIP001              {
//STRIP001                  if (bRecording)
//STRIP001                      AddCalcUndo( new SdrUndoGeoObj( *pObj ) );
//STRIP001                  pObj->SetPoint( aStartPos, 0 );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else                                // Referenz-Rahmen
//STRIP001  {
//STRIP001      DBG_ASSERT( pData->bValidStart, "RecalcPos: kein Start" );
//STRIP001      Point aPos(
//STRIP001          pDoc->GetColOffset( pData->aStt.nCol, pData->aStt.nTab ),
//STRIP001          pDoc->GetRowOffset( pData->aStt.nRow, pData->aStt.nTab ) );
//STRIP001      TwipsToMM( aPos.X() );
//STRIP001      TwipsToMM( aPos.Y() );
//STRIP001
//STRIP001      if( pData->bValidEnd )
//STRIP001      {
//STRIP001          Point aEnd(
//STRIP001              pDoc->GetColOffset( pData->aEnd.nCol+1, pData->aEnd.nTab ),
//STRIP001              pDoc->GetRowOffset( pData->aEnd.nRow+1, pData->aEnd.nTab ) );
//STRIP001          TwipsToMM( aEnd.X() );
//STRIP001          TwipsToMM( aEnd.Y() );
//STRIP001
//STRIP001          Rectangle aNew( aPos, aEnd );
//STRIP001          if ( pObj->GetLogicRect() != aNew )
//STRIP001          {
//STRIP001              if (bRecording)
//STRIP001                  AddCalcUndo( new SdrUndoGeoObj( *pObj ) );
//STRIP001              pObj->SetLogicRect(aNew);
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001          if ( pObj->GetRelativePos() != aPos )
//STRIP001          {
//STRIP001              if (bRecording)
//STRIP001                  AddCalcUndo( new SdrUndoGeoObj( *pObj ) );
//STRIP001              pObj->SetRelativePos( aPos );
//STRIP001          }
//STRIP001  }
//STRIP001
//STRIP001 }

/*N*/ void ScDrawLayer::Load( SvStream& rStream )
/*N*/ {
/*N*/   bRecording = FALSE;
/*N*/   DELETEZ(pUndoGroup);
/*N*/
/*N*/   ScReadHeader aHdr( rStream );
/*N*/   while (aHdr.BytesLeft())
/*N*/   {
/*N*/       USHORT nID;
/*N*/       rStream >> nID;
/*N*/       switch (nID)
/*N*/       {
/*N*/           case SCID_DRAWPOOL:
/*N*/               {
/*N*/                   ScReadHeader aPoolHdr( rStream );
/*N*/                   GetItemPool().Load( rStream );              //! in Pool-Stream ?
/*N*/               }
/*N*/               break;
/*N*/           case SCID_DRAWMODEL:
/*N*/               {
/*N*/                   ScReadHeader aDrawHdr( rStream );
/*N*/                   rStream >> *this;
/*N*/
/*N*/                   //  Control-Layer ist nicht in alten Dateien
/*N*/                   SdrLayerAdmin& rAdmin = GetLayerAdmin();
/*N*/                   const SdrLayer* pLayer = rAdmin.GetLayerPerID(SC_LAYER_CONTROLS);
/*N*/                   if (!pLayer)
/*N*/                       rAdmin.NewLayer(
/*N*/                           String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM("Controls")),
/*N*/                           SC_LAYER_CONTROLS);
/*N*/               }
/*N*/               break;
/*N*/           default:
/*N*/               {
/*N*/                   DBG_ERROR("unbekannter Sub-Record in ScDrawLayer::Load");
/*N*/                   ScReadHeader aDummyHdr( rStream );
/*N*/               }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   GetItemPool().LoadCompleted();
/*N*/ }

/*N*/ void ScDrawLayer::Store( SvStream& rStream ) const
/*N*/ {
/*N*/   ScWriteHeader aHdr( rStream );
/*N*/
/*N*/ //-/  const_cast<ScDrawLayer*>(this)->PrepareStore();     // non-const
/*N*/   const_cast<ScDrawLayer*>(this)->PreSave();      // non-const
/*N*/
/*N*/   {
/*N*/       rStream << (USHORT) SCID_DRAWPOOL;
/*N*/       ScWriteHeader aPoolHdr( rStream );
/*N*/       GetItemPool().Store( rStream );             //! in Pool-Stream ?
/*N*/   }
/*N*/
/*N*/   {
/*N*/       rStream << (USHORT) SCID_DRAWMODEL;
/*N*/       ScWriteHeader aDrawHdr( rStream );
/*N*/       rStream << *this;
/*N*/   }
/*N*/
/*N*/   const_cast<ScDrawLayer*>(this)->PostSave();     // non-const
/*N*/ }

/*N*/ BOOL ScDrawLayer::GetPrintArea( ScRange& rRange, BOOL bSetHor, BOOL bSetVer ) const
/*N*/ {
/*N*/   DBG_ASSERT( pDoc, "ScDrawLayer::GetPrintArea without document" );
/*N*/   if ( !pDoc )
/*N*/       return FALSE;
/*N*/
/*N*/   USHORT nTab = rRange.aStart.Tab();
/*N*/   DBG_ASSERT( rRange.aEnd.Tab() == nTab, "GetPrintArea: Tab unterschiedlich" );
/*N*/
/*N*/   BOOL bAny = FALSE;
/*N*/   long nEndX = 0;
/*N*/   long nEndY = 0;
/*N*/   long nStartX = LONG_MAX;
/*N*/   long nStartY = LONG_MAX;
/*N*/   USHORT i;
/*N*/
/*N*/   // Grenzen ausrechnen
/*N*/
/*N*/   if (!bSetHor)
/*N*/   {
/*?*/       nStartX = 0;
/*?*/       USHORT nStartCol = rRange.aStart.Col();
/*?*/       for (i=0; i<nStartCol; i++)
/*?*/           nStartX +=pDoc->GetColWidth(i,nTab);
/*?*/       nEndX = nStartX;
/*?*/       USHORT nEndCol = rRange.aEnd.Col();
/*?*/       for (i=nStartCol; i<=nEndCol; i++)
/*?*/           nEndX += pDoc->GetColWidth(i,nTab);
/*?*/       nStartX = (long)(nStartX * HMM_PER_TWIPS);
/*?*/       nEndX   = (long)(nEndX   * HMM_PER_TWIPS);
/*N*/   }
/*N*/   if (!bSetVer)
/*N*/   {
/*?*/       nStartY = 0;
/*?*/       USHORT nStartRow = rRange.aStart.Row();
/*?*/       for (i=0; i<nStartRow; i++)
/*?*/           nStartY +=pDoc->FastGetRowHeight(i,nTab);
/*?*/       nEndY = nStartY;
/*?*/       USHORT nEndRow = rRange.aEnd.Row();
/*?*/       for (i=nStartRow; i<=nEndRow; i++)
/*?*/           nEndY += pDoc->FastGetRowHeight(i,nTab);
/*?*/       nStartY = (long)(nStartY * HMM_PER_TWIPS);
/*?*/       nEndY   = (long)(nEndY   * HMM_PER_TWIPS);
/*N*/   }
/*N*/
/*N*/   const SdrPage* pPage = GetPage(nTab);
/*N*/   DBG_ASSERT(pPage,"Page nicht gefunden");
/*N*/   if (pPage)
/*N*/   {
/*N*/       SdrObjListIter aIter( *pPage, IM_FLAT );
/*N*/       SdrObject* pObject = aIter.Next();
/*N*/       while (pObject)
/*N*/       {
/*N*/                           //! Flags (ausgeblendet?) testen
/*N*/
/*N*/           Rectangle aObjRect = pObject->GetBoundRect();
/*N*/           BOOL bFit = TRUE;
/*N*/           if ( !bSetHor && ( aObjRect.Right() < nStartX || aObjRect.Left() > nEndX ) )
/*N*/               bFit = FALSE;
/*N*/           if ( !bSetVer && ( aObjRect.Bottom() < nStartY || aObjRect.Top() > nEndY ) )
/*N*/               bFit = FALSE;
/*N*/           if ( bFit )
/*N*/           {
/*N*/               if (bSetHor)
/*N*/               {
/*N*/                   if (aObjRect.Left() < nStartX) nStartX = aObjRect.Left();
/*N*/                   if (aObjRect.Right()  > nEndX) nEndX = aObjRect.Right();
/*N*/               }
/*N*/               if (bSetVer)
/*N*/               {
/*N*/                   if (aObjRect.Top()  < nStartY) nStartY = aObjRect.Top();
/*N*/                   if (aObjRect.Bottom() > nEndY) nEndY = aObjRect.Bottom();
/*N*/               }
/*N*/               bAny = TRUE;
/*N*/           }
/*N*/
/*N*/           pObject = aIter.Next();
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (bAny)
/*N*/   {
/*N*/       DBG_ASSERT( nStartX<=nEndX && nStartY<=nEndY, "Start/End falsch in ScDrawLayer::GetPrintArea" );
/*N*/
/*N*/       if (bSetHor)
/*N*/       {
/*N*/           nStartX = (long) (nStartX / HMM_PER_TWIPS);
/*N*/           nEndX = (long) (nEndX / HMM_PER_TWIPS);
/*N*/           long nWidth;
/*N*/
/*N*/           nWidth = 0;
/*N*/           for (i=0; i<MAXCOL && nWidth<=nStartX; i++)
/*N*/               nWidth += pDoc->GetColWidth(i,nTab);
/*N*/           rRange.aStart.SetCol( i ? (i-1) : 0 );
/*N*/
/*N*/           nWidth = 0;
/*N*/           for (i=0; i<MAXCOL && nWidth<=nEndX; i++)           //! bei Start anfangen
/*N*/               nWidth += pDoc->GetColWidth(i,nTab);
/*N*/           rRange.aEnd.SetCol( i ? (i-1) : 0 );
/*N*/       }
/*N*/
/*N*/       if (bSetVer)
/*N*/       {
/*N*/           nStartY = (long) (nStartY / HMM_PER_TWIPS);
/*N*/           nEndY = (long) (nEndY / HMM_PER_TWIPS);
/*N*/           long nHeight;
/*N*/
/*N*/           nHeight = 0;
/*N*/           for (i=0; i<MAXROW && nHeight<=nStartY; i++)
/*N*/               nHeight += pDoc->FastGetRowHeight(i,nTab);
/*N*/           rRange.aStart.SetRow( i ? (i-1) : 0 );
/*N*/
/*N*/           nHeight = 0;
/*N*/           for (i=0; i<MAXROW && nHeight<=nEndY; i++)
/*N*/               nHeight += pDoc->FastGetRowHeight(i,nTab);
/*N*/           rRange.aEnd.SetRow( i ? (i-1) : 0 );
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       if (bSetHor)
/*N*/       {
/*N*/           rRange.aStart.SetCol(0);
/*N*/           rRange.aEnd.SetCol(0);
/*N*/       }
/*N*/       if (bSetVer)
/*N*/       {
/*N*/           rRange.aStart.SetRow(0);
/*N*/           rRange.aEnd.SetRow(0);
/*N*/       }
/*N*/   }
/*N*/   return bAny;
/*N*/ }

/*N*/ void ScDrawLayer::AddCalcUndo( SdrUndoAction* pUndo )
/*N*/ {
/*N*/   if (bRecording)
/*N*/   {
/*N*/       if (!pUndoGroup)
/*N*/           pUndoGroup = new SdrUndoGroup(*this);
/*N*/
/*N*/       pUndoGroup->AddAction( pUndo );
/*N*/   }
/*N*/   else
/*N*/       delete pUndo;
/*N*/ }

/*N*/ void ScDrawLayer::BeginCalcUndo()
/*N*/ {
/*N*/ //! DBG_ASSERT( !bRecording, "BeginCalcUndo ohne GetCalcUndo" );
/*N*/
/*N*/   DELETEZ(pUndoGroup);
/*N*/   bRecording = TRUE;
/*N*/ }

/*N*/ SdrUndoGroup* ScDrawLayer::GetCalcUndo()
/*N*/ {
/*N*/ //! DBG_ASSERT( bRecording, "GetCalcUndo ohne BeginCalcUndo" );
/*N*/
/*N*/   SdrUndoGroup* pRet = pUndoGroup;
/*N*/   pUndoGroup = NULL;
/*N*/   bRecording = FALSE;
/*N*/   return pRet;
/*N*/ }

//  MoveAreaTwips: all measures are kept in twips
/*N*/ void ScDrawLayer::MoveAreaTwips( USHORT nTab, const Rectangle& rArea,
/*N*/       const Point& rMove, const Point& rTopLeft )
/*N*/ {
/*N*/   if (!rMove.X() && !rMove.Y())
/*N*/       return;                                     // nix
/*N*/
/*N*/   SdrPage* pPage = GetPage(nTab);
/*N*/   DBG_ASSERT(pPage,"Page nicht gefunden");
/*N*/   if (!pPage)
/*N*/       return;
/*N*/
/*N*/   // fuer Shrinking!
/*N*/   Rectangle aNew( rArea );
/*N*/   BOOL bShrink = FALSE;
/*N*/   if ( rMove.X() < 0 || rMove.Y() < 0 )       // verkleinern
/*N*/   {
/*N*/       if ( rTopLeft != rArea.TopLeft() )      // sind gleich beim Verschieben von Zellen
/*N*/       {
/*N*/           bShrink = TRUE;
/*N*/           aNew.Left() = rTopLeft.X();
/*N*/           aNew.Top() = rTopLeft.Y();
/*N*/       }
/*N*/   }
/*N*/   SdrObjListIter aIter( *pPage, IM_FLAT );
/*N*/   SdrObject* pObject = aIter.Next();
/*N*/   while (pObject)
/*N*/   {
/*N*/       if( GetAnchor( pObject ) == SCA_CELL )
/*N*/       {
/*N*/           if ( GetObjData( pObject ) )                    // Detektiv-Pfeil ?
/*N*/           {
/*N*/               // hier nichts
/*N*/           }
/*N*/           else if ( pObject->ISA( SdrEdgeObj ) )          // Verbinder?
/*N*/           {
/*N*/               //  hier auch nichts
/*N*/               //! nicht verbundene Enden wie bei Linien (s.u.) behandeln?
/*N*/           }
/*N*/           else if ( pObject->IsPolyObj() && pObject->GetPointCount()==2 )
/*N*/           {
/*N*/               for (USHORT i=0; i<2; i++)
/*N*/               {
/*N*/                   BOOL bMoved = FALSE;
/*N*/                   Point aPoint = pObject->GetPoint(i);
/*N*/                   lcl_ReverseTwipsToMM( aPoint );
/*N*/                   if (rArea.IsInside(aPoint))
/*N*/                   {
/*N*/                       aPoint += rMove; bMoved = TRUE;
/*N*/                   }
/*N*/                   else if (bShrink && aNew.IsInside(aPoint))
/*N*/                   {
/*?*/                       //  Punkt ist in betroffener Zelle - Test auf geloeschten Bereich
/*?*/                       if ( rMove.X() && aPoint.X() >= rArea.Left() + rMove.X() )
/*?*/                       {
/*?*/                           aPoint.X() = rArea.Left() + rMove.X() - SHRINK_DIST_TWIPS;
/*?*/                           if ( aPoint.X() < 0 ) aPoint.X() = 0;
/*?*/                           bMoved = TRUE;
/*?*/                       }
/*?*/                       if ( rMove.Y() && aPoint.Y() >= rArea.Top() + rMove.Y() )
/*?*/                       {
/*?*/                           aPoint.Y() = rArea.Top() + rMove.Y() - SHRINK_DIST_TWIPS;
/*?*/                           if ( aPoint.Y() < 0 ) aPoint.Y() = 0;
/*?*/                           bMoved = TRUE;
/*?*/                       }
/*N*/                   }
/*N*/                   if( bMoved )
/*N*/                   {
/*N*/                       AddCalcUndo( new SdrUndoGeoObj( *pObject ) );
/*N*/                       lcl_TwipsToMM( aPoint );
/*N*/                       pObject->SetPoint( aPoint, i );
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               Rectangle aObjRect = pObject->GetLogicRect();
/*N*/               Point aOldMMPos = aObjRect.TopLeft();           // not converted, millimeters
/*N*/               lcl_ReverseTwipsToMM( aObjRect );
/*N*/               Point aTopLeft = aObjRect.TopLeft();
/*N*/               Size aMoveSize;
/*N*/               BOOL bDoMove = FALSE;
/*N*/               if (rArea.IsInside(aTopLeft))
/*N*/               {
/*N*/                   aMoveSize = Size(rMove.X(),rMove.Y());
/*N*/                   bDoMove = TRUE;
/*N*/               }
/*N*/               else if (bShrink && aNew.IsInside(aTopLeft))
/*N*/               {
/*?*/                   //  Position ist in betroffener Zelle - Test auf geloeschten Bereich
/*?*/                   if ( rMove.X() && aTopLeft.X() >= rArea.Left() + rMove.X() )
/*?*/                   {
/*?*/                       aMoveSize.Width() = rArea.Left() + rMove.X() - SHRINK_DIST - aTopLeft.X();
/*?*/                       bDoMove = TRUE;
/*?*/                   }
/*?*/                   if ( rMove.Y() && aTopLeft.Y() >= rArea.Top() + rMove.Y() )
/*?*/                   {
/*?*/                       aMoveSize.Height() = rArea.Top() + rMove.Y() - SHRINK_DIST - aTopLeft.Y();
/*?*/                       bDoMove = TRUE;
/*?*/                   }
/*N*/               }
/*N*/               if ( bDoMove )
/*N*/               {
/*N*/                   if ( aTopLeft.X() + aMoveSize.Width() < 0 )
/*?*/                       aMoveSize.Width() = -aTopLeft.X();
/*N*/                   if ( aTopLeft.Y() + aMoveSize.Height() < 0 )
/*?*/                       aMoveSize.Height() = -aTopLeft.Y();
/*N*/
/*N*/                   //  get corresponding move size in millimeters:
/*N*/                   Point aNewPos( aTopLeft.X() + aMoveSize.Width(), aTopLeft.Y() + aMoveSize.Height() );
/*N*/                   lcl_TwipsToMM( aNewPos );
/*N*/                   aMoveSize = Size( aNewPos.X() - aOldMMPos.X(), aNewPos.Y() - aOldMMPos.Y() );   // millimeters
/*N*/
/*N*/                   AddCalcUndo( new SdrUndoMoveObj( *pObject, aMoveSize ) );
/*N*/                   pObject->Move( aMoveSize );
/*N*/               }
/*N*/               else if ( rArea.IsInside(aObjRect.BottomRight()) &&
/*N*/                           !pObject->IsResizeProtect() )
/*N*/               {
/*N*/                   //  geschuetzte Groessen werden nicht veraendert
/*N*/                   //  (Positionen schon, weil sie ja an der Zelle "verankert" sind)
/*N*/                   AddCalcUndo( new SdrUndoGeoObj( *pObject ) );
/*N*/                   long nOldSizeX = aObjRect.Right() - aObjRect.Left() + 1;
/*N*/                   long nOldSizeY = aObjRect.Bottom() - aObjRect.Top() + 1;
/*N*/                   pObject->Resize( aOldMMPos, Fraction( nOldSizeX+rMove.X(), nOldSizeX ),
/*N*/                                               Fraction( nOldSizeY+rMove.Y(), nOldSizeY ) );
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/       pObject = aIter.Next();
/*N*/   }
/*N*/ }

//STRIP001 void ScDrawLayer::MoveArea( USHORT nTab, USHORT nCol1,USHORT nRow1, USHORT nCol2,USHORT nRow2,
//STRIP001                          short nDx,short nDy, BOOL bInsDel )
//STRIP001 {
//STRIP001  DBG_ASSERT( pDoc, "ScDrawLayer::MoveArea without document" );
//STRIP001  if ( !pDoc )
//STRIP001      return;
//STRIP001
//STRIP001  if (!bAdjustEnabled)
//STRIP001      return;
//STRIP001
//STRIP001  Rectangle aRect = pDoc->GetMMRect( nCol1, nRow1, nCol2, nRow2, nTab );
//STRIP001  lcl_ReverseTwipsToMM( aRect );
//STRIP001  //! use twips directly?
//STRIP001
//STRIP001  short s;
//STRIP001  Point aMove;
//STRIP001
//STRIP001  if (nDx > 0)
//STRIP001      for (s=0; s<nDx; s++)
//STRIP001          aMove.X() += pDoc->GetColWidth(s+(short)nCol1,nTab);
//STRIP001  else
//STRIP001      for (s=-1; s>=nDx; s--)
//STRIP001          aMove.X() -= pDoc->GetColWidth(s+(short)nCol1,nTab);
//STRIP001  if (nDy > 0)
//STRIP001      for (s=0; s<nDy; s++)
//STRIP001          aMove.Y() += pDoc->FastGetRowHeight(s+(short)nRow1,nTab);
//STRIP001  else
//STRIP001      for (s=-1; s>=nDy; s--)
//STRIP001          aMove.Y() -= pDoc->FastGetRowHeight(s+(short)nRow1,nTab);
//STRIP001
//STRIP001  Point aTopLeft = aRect.TopLeft();       // Anfang beim Verkleinern
//STRIP001  if (bInsDel)
//STRIP001  {
//STRIP001      if ( aMove.X() < 0 )
//STRIP001          aTopLeft.X() += aMove.X();
//STRIP001      if ( aMove.Y() < 0 )
//STRIP001          aTopLeft.Y() += aMove.Y();
//STRIP001  }
//STRIP001
//STRIP001  //  drawing objects are now directly included in cut&paste
//STRIP001  //  -> only update references when inserting/deleting (or changing widths or heights)
//STRIP001  if ( bInsDel )
//STRIP001      MoveAreaTwips( nTab, aRect, aMove, aTopLeft );
//STRIP001
//STRIP001      //
//STRIP001      //      Detektiv-Pfeile: Zellpositionen anpassen
//STRIP001      //
//STRIP001
//STRIP001  MoveCells( nTab, nCol1,nRow1, nCol2,nRow2, nDx,nDy );
//STRIP001 }

/*N*/ void ScDrawLayer::WidthChanged( USHORT nTab, USHORT nCol, long nDifTwips )
/*N*/ {
/*N*/   DBG_ASSERT( pDoc, "ScDrawLayer::WidthChanged without document" );
/*N*/   if ( !pDoc )
/*N*/       return;
/*N*/
/*N*/   if (!bAdjustEnabled)
/*N*/       return;
/*N*/
/*N*/   USHORT i;
/*N*/   Rectangle aRect;
/*N*/   Point aTopLeft;
/*N*/
/*N*/   for (i=0; i<nCol; i++)
/*N*/       aRect.Left() += pDoc->GetColWidth(i,nTab);
/*N*/   aTopLeft.X() = aRect.Left();
/*N*/   aRect.Left() += pDoc->GetColWidth(nCol,nTab);
/*N*/
/*N*/   aRect.Right() = MAXMM;
/*N*/   aRect.Top() = 0;
/*N*/   aRect.Bottom() = MAXMM;
/*N*/
/*N*/   //! aTopLeft ist falsch, wenn mehrere Spalten auf einmal ausgeblendet werden
/*N*/
/*N*/   MoveAreaTwips( nTab, aRect, Point( nDifTwips,0 ), aTopLeft );
/*N*/ }

/*N*/ void ScDrawLayer::HeightChanged( USHORT nTab, USHORT nRow, long nDifTwips )
/*N*/ {
/*N*/   DBG_ASSERT( pDoc, "ScDrawLayer::HeightChanged without document" );
/*N*/   if ( !pDoc )
/*N*/       return;
/*N*/
/*N*/   if (!bAdjustEnabled)
/*N*/       return;
/*N*/
/*N*/   USHORT i;
/*N*/   Rectangle aRect;
/*N*/   Point aTopLeft;
/*N*/
/*N*/   for (i=0; i<nRow; i++)
/*N*/       aRect.Top() += pDoc->FastGetRowHeight(i,nTab);
/*N*/   aTopLeft.Y() = aRect.Top();
/*N*/   aRect.Top() += pDoc->FastGetRowHeight(nRow,nTab);
/*N*/
/*N*/   aRect.Bottom() = MAXMM;
/*N*/   aRect.Left() = 0;
/*N*/   aRect.Right() = MAXMM;
/*N*/
/*N*/   //! aTopLeft ist falsch, wenn mehrere Zeilen auf einmal ausgeblendet werden
/*N*/
/*N*/   MoveAreaTwips( nTab, aRect, Point( 0,nDifTwips ), aTopLeft );
/*N*/ }

/*N*/ BOOL ScDrawLayer::HasObjectsInRows( USHORT nTab, USHORT nStartRow, USHORT nEndRow )
/*N*/ {
/*N*/   DBG_ASSERT( pDoc, "ScDrawLayer::HasObjectsInRows without document" );
/*N*/   if ( !pDoc )
/*N*/       return FALSE;
/*N*/
/*N*/   Rectangle aTestRect;
/*N*/
/*N*/   USHORT i;
/*N*/   for (i=0; i<nStartRow; i++)
/*N*/       aTestRect.Top() += pDoc->FastGetRowHeight(i,nTab);
/*N*/
/*N*/   if (nEndRow==MAXROW)
/*N*/       aTestRect.Bottom() = MAXMM;
/*N*/   else
/*N*/   {
/*N*/       aTestRect.Bottom() = aTestRect.Top();
/*N*/       for (i=nStartRow; i<=nEndRow; i++)
/*N*/       {
/*N*/           aTestRect.Bottom() += pDoc->FastGetRowHeight(i,nTab);
/*N*/       }
/*N*/       TwipsToMM( aTestRect.Bottom() );
/*N*/   }
/*N*/
/*N*/   TwipsToMM( aTestRect.Top() );
/*N*/
/*N*/   aTestRect.Left()  = 0;
/*N*/   aTestRect.Right() = MAXMM;
/*N*/
/*N*/   SdrPage* pPage = GetPage(nTab);
/*N*/   DBG_ASSERT(pPage,"Page nicht gefunden");
/*N*/   if (!pPage)
/*N*/       return FALSE;
/*N*/
/*N*/   BOOL bFound = FALSE;
/*N*/
/*N*/   Rectangle aObjRect;
/*N*/   SdrObjListIter aIter( *pPage );
/*N*/   SdrObject* pObject = aIter.Next();
/*N*/   while ( pObject && !bFound )
/*N*/   {
/*N*/       aObjRect = pObject->GetSnapRect();  //! GetLogicRect ?
/*N*/       if (aTestRect.IsInside(aObjRect.TopLeft()) || aTestRect.IsInside(aObjRect.BottomLeft()))
/*N*/           bFound = TRUE;
/*N*/
/*N*/       pObject = aIter.Next();
/*N*/   }
/*N*/
/*N*/   return bFound;
/*N*/ }

//STRIP001 void ScDrawLayer::DeleteObjects( USHORT nTab )
//STRIP001 {
//STRIP001  SdrPage* pPage = GetPage(nTab);
//STRIP001  DBG_ASSERT(pPage,"Page ?");
//STRIP001  if (!pPage)
//STRIP001      return;
//STRIP001
//STRIP001  pPage->RecalcObjOrdNums();
//STRIP001
//STRIP001  long    nDelCount = 0;
//STRIP001  ULONG   nObjCount = pPage->GetObjCount();
//STRIP001  if (nObjCount)
//STRIP001  {
//STRIP001      SdrObject** ppObj = new SdrObject*[nObjCount];
//STRIP001
//STRIP001      SdrObjListIter aIter( *pPage, IM_FLAT );
//STRIP001      SdrObject* pObject = aIter.Next();
//STRIP001      while (pObject)
//STRIP001      {
//STRIP001          //  alle loeschen
//STRIP001          ppObj[nDelCount++] = pObject;
//STRIP001          pObject = aIter.Next();
//STRIP001      }
//STRIP001
//STRIP001      long i;
//STRIP001      if (bRecording)
//STRIP001          for (i=1; i<=nDelCount; i++)
//STRIP001              AddCalcUndo( new SdrUndoRemoveObj( *ppObj[nDelCount-i] ) );
//STRIP001
//STRIP001      for (i=1; i<=nDelCount; i++)
//STRIP001          pPage->RemoveObject( ppObj[nDelCount-i]->GetOrdNum() );
//STRIP001
//STRIP001      delete[] ppObj;
//STRIP001  }
//STRIP001 }

//STRIP001 void ScDrawLayer::DeleteObjectsInArea( USHORT nTab, USHORT nCol1,USHORT nRow1,
//STRIP001                                          USHORT nCol2,USHORT nRow2 )
//STRIP001 {
//STRIP001  DBG_ASSERT( pDoc, "ScDrawLayer::DeleteObjectsInArea without document" );
//STRIP001  if ( !pDoc )
//STRIP001      return;
//STRIP001
//STRIP001  SdrPage* pPage = GetPage(nTab);
//STRIP001  DBG_ASSERT(pPage,"Page ?");
//STRIP001  if (!pPage)
//STRIP001      return;
//STRIP001
//STRIP001  pPage->RecalcObjOrdNums();
//STRIP001
//STRIP001  long    nDelCount = 0;
//STRIP001  ULONG   nObjCount = pPage->GetObjCount();
//STRIP001  if (nObjCount)
//STRIP001  {
//STRIP001      Rectangle aDelRect = pDoc->GetMMRect( nCol1, nRow1, nCol2, nRow2, nTab );
//STRIP001
//STRIP001      SdrObject** ppObj = new SdrObject*[nObjCount];
//STRIP001
//STRIP001      SdrObjListIter aIter( *pPage, IM_FLAT );
//STRIP001      SdrObject* pObject = aIter.Next();
//STRIP001      while (pObject)
//STRIP001      {
//STRIP001          Rectangle aObjRect = pObject->GetBoundRect();
//STRIP001          if ( aDelRect.IsInside( aObjRect ) )
//STRIP001              ppObj[nDelCount++] = pObject;
//STRIP001
//STRIP001          pObject = aIter.Next();
//STRIP001      }
//STRIP001
//STRIP001      long i;
//STRIP001      if (bRecording)
//STRIP001          for (i=1; i<=nDelCount; i++)
//STRIP001              AddCalcUndo( new SdrUndoRemoveObj( *ppObj[nDelCount-i] ) );
//STRIP001
//STRIP001      for (i=1; i<=nDelCount; i++)
//STRIP001          pPage->RemoveObject( ppObj[nDelCount-i]->GetOrdNum() );
//STRIP001
//STRIP001      delete[] ppObj;
//STRIP001  }
//STRIP001 }

//STRIP001 void ScDrawLayer::DeleteObjectsInSelection( const ScMarkData& rMark )
//STRIP001 {
//STRIP001  DBG_ASSERT( pDoc, "ScDrawLayer::DeleteObjectsInSelection without document" );
//STRIP001  if ( !pDoc )
//STRIP001      return;
//STRIP001
//STRIP001  if ( !rMark.IsMultiMarked() )
//STRIP001      return;
//STRIP001
//STRIP001  ScRange aMarkRange;
//STRIP001  rMark.GetMultiMarkArea( aMarkRange );
//STRIP001
//STRIP001  USHORT nTabCount = pDoc->GetTableCount();
//STRIP001  for (USHORT nTab=0; nTab<=nTabCount; nTab++)
//STRIP001      if ( rMark.GetTableSelect( nTab ) )
//STRIP001      {
//STRIP001          SdrPage* pPage = GetPage(nTab);
//STRIP001          if (pPage)
//STRIP001          {
//STRIP001              pPage->RecalcObjOrdNums();
//STRIP001              long    nDelCount = 0;
//STRIP001              ULONG   nObjCount = pPage->GetObjCount();
//STRIP001              if (nObjCount)
//STRIP001              {
//STRIP001                  //  Rechteck um die ganze Selektion
//STRIP001                  Rectangle aMarkBound = pDoc->GetMMRect(
//STRIP001                              aMarkRange.aStart.Col(), aMarkRange.aStart.Row(),
//STRIP001                              aMarkRange.aEnd.Col(), aMarkRange.aEnd.Row(), nTab );
//STRIP001
//STRIP001                  SdrObject** ppObj = new SdrObject*[nObjCount];
//STRIP001
//STRIP001                  SdrObjListIter aIter( *pPage, IM_FLAT );
//STRIP001                  SdrObject* pObject = aIter.Next();
//STRIP001                  while (pObject)
//STRIP001                  {
//STRIP001                      Rectangle aObjRect = pObject->GetBoundRect();
//STRIP001                      if ( aMarkBound.IsInside( aObjRect ) )
//STRIP001                      {
//STRIP001                          ScRange aRange = pDoc->GetRange( nTab, aObjRect );
//STRIP001                          if (rMark.IsAllMarked(aRange))
//STRIP001                              ppObj[nDelCount++] = pObject;
//STRIP001                      }
//STRIP001
//STRIP001                      pObject = aIter.Next();
//STRIP001                  }
//STRIP001
//STRIP001                  //  Objekte loeschen (rueckwaerts)
//STRIP001
//STRIP001                  long i;
//STRIP001                  if (bRecording)
//STRIP001                      for (i=1; i<=nDelCount; i++)
//STRIP001                          AddCalcUndo( new SdrUndoRemoveObj( *ppObj[nDelCount-i] ) );
//STRIP001
//STRIP001                  for (i=1; i<=nDelCount; i++)
//STRIP001                      pPage->RemoveObject( ppObj[nDelCount-i]->GetOrdNum() );
//STRIP001
//STRIP001                  delete[] ppObj;
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001              DBG_ERROR("pPage?");
//STRIP001      }
//STRIP001 }

//STRIP001 void ScDrawLayer::CopyToClip( ScDocument* pClipDoc, USHORT nTab, const Rectangle& rRange )
//STRIP001 {
//STRIP001  //  copy everything in the specified range into the same page (sheet) in the clipboard doc
//STRIP001
//STRIP001  SdrPage* pSrcPage = GetPage(nTab);
//STRIP001  if (pSrcPage)
//STRIP001  {
//STRIP001      ScDrawLayer* pDestModel = NULL;
//STRIP001      SdrPage* pDestPage = NULL;
//STRIP001
//STRIP001      SdrObjListIter aIter( *pSrcPage, IM_FLAT );
//STRIP001      SdrObject* pOldObject = aIter.Next();
//STRIP001      while (pOldObject)
//STRIP001      {
//STRIP001          Rectangle aObjRect = pOldObject->GetBoundRect();
//STRIP001          if ( rRange.IsInside( aObjRect ) && pOldObject->GetLayer() != SC_LAYER_INTERN )
//STRIP001          {
//STRIP001              if ( !pDestModel )
//STRIP001              {
//STRIP001                  pDestModel = pClipDoc->GetDrawLayer();      // does the document already have a drawing layer?
//STRIP001                  if ( !pDestModel )
//STRIP001                  {
//STRIP001                      //  allocate drawing layer in clipboard document only if there are objects to copy
//STRIP001
//STRIP001                      pClipDoc->InitDrawLayer();                  //! create contiguous pages
//STRIP001                      pDestModel = pClipDoc->GetDrawLayer();
//STRIP001                  }
//STRIP001                  if (pDestModel)
//STRIP001                      pDestPage = pDestModel->GetPage( nTab );
//STRIP001              }
//STRIP001
//STRIP001              DBG_ASSERT( pDestPage, "no page" );
//STRIP001              if (pDestPage)
//STRIP001              {
//STRIP001                  SdrObject* pNewObject = pOldObject->Clone( pDestPage, pDestModel );
//STRIP001                  pNewObject->NbcMove(Size(0,0));
//STRIP001                  pDestPage->InsertObject( pNewObject );
//STRIP001
//STRIP001                  //  no undo needed in clipboard document
//STRIP001                  //  charts are not updated
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          pOldObject = aIter.Next();
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL lcl_IsAllInRange( const ScRangeList& rRanges, const ScRange& rClipRange )
//STRIP001 {
//STRIP001  //  check if every range of rRanges is completely in rClipRange
//STRIP001
//STRIP001  ULONG nCount = rRanges.Count();
//STRIP001  for (ULONG i=0; i<nCount; i++)
//STRIP001  {
//STRIP001      ScRange aRange = *rRanges.GetObject(i);
//STRIP001      if ( !rClipRange.In( aRange ) )
//STRIP001      {
//STRIP001          return FALSE;   // at least one range is not valid
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return TRUE;            // everything is fine
//STRIP001 }

//STRIP001 BOOL lcl_MoveRanges( ScRangeList& rRanges, const ScRange& rSourceRange, const ScAddress& rDestPos )
//STRIP001 {
//STRIP001  BOOL bChanged = FALSE;
//STRIP001
//STRIP001  ULONG nCount = rRanges.Count();
//STRIP001  for (ULONG i=0; i<nCount; i++)
//STRIP001  {
//STRIP001      ScRange* pRange = rRanges.GetObject(i);
//STRIP001      if ( rSourceRange.In( *pRange ) )
//STRIP001      {
//STRIP001          short nDiffX = rDestPos.Col() - (short)rSourceRange.aStart.Col();
//STRIP001          short nDiffY = rDestPos.Row() - (short)rSourceRange.aStart.Row();
//STRIP001          short nDiffZ = rDestPos.Tab() - (short)rSourceRange.aStart.Tab();
//STRIP001          pRange->Move( nDiffX, nDiffY, nDiffZ );
//STRIP001          bChanged = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return bChanged;
//STRIP001 }

//STRIP001 void ScDrawLayer::CopyFromClip( ScDrawLayer* pClipModel, USHORT nSourceTab, const Rectangle& rSourceRange,
//STRIP001                                  const ScAddress& rDestPos, const Rectangle& rDestRange )
//STRIP001 {
//STRIP001  DBG_ASSERT( pDoc, "ScDrawLayer::CopyFromClip without document" );
//STRIP001  if ( !pDoc )
//STRIP001      return;
//STRIP001
//STRIP001  if (!pClipModel)
//STRIP001      return;
//STRIP001
//STRIP001  if (bDrawIsInUndo)      //! can this happen?
//STRIP001  {
//STRIP001      DBG_ERROR("CopyFromClip, bDrawIsInUndo");
//STRIP001      return;
//STRIP001  }
//STRIP001
//STRIP001  USHORT nDestTab = rDestPos.Tab();
//STRIP001
//STRIP001  SdrPage* pSrcPage = pClipModel->GetPage(nSourceTab);
//STRIP001  SdrPage* pDestPage = GetPage(nDestTab);
//STRIP001  DBG_ASSERT( pSrcPage && pDestPage, "draw page missing" );
//STRIP001  if ( !pSrcPage || !pDestPage )
//STRIP001      return;
//STRIP001
//STRIP001  Size aMove( rDestRange.Left() - rSourceRange.Left(), rDestRange.Top() - rSourceRange.Top() );
//STRIP001
//STRIP001  long nDestWidth = rDestRange.GetWidth();
//STRIP001  long nDestHeight = rDestRange.GetHeight();
//STRIP001  long nSourceWidth = rSourceRange.GetWidth();
//STRIP001  long nSourceHeight = rSourceRange.GetHeight();
//STRIP001
//STRIP001  long nWidthDiff = nDestWidth - nSourceWidth;
//STRIP001  long nHeightDiff = nDestHeight - nSourceHeight;
//STRIP001
//STRIP001  Fraction aHorFract(1,1);
//STRIP001  Fraction aVerFract(1,1);
//STRIP001  BOOL bResize = FALSE;
//STRIP001  // sizes can differ by 1 from twips->1/100mm conversion for equal cell sizes,
//STRIP001  // don't resize to empty size when pasting into hidden columns or rows
//STRIP001  if ( Abs(nWidthDiff) > 1 && nDestWidth > 1 && nSourceWidth > 1 )
//STRIP001  {
//STRIP001      aHorFract = Fraction( nDestWidth, nSourceWidth );
//STRIP001      bResize = TRUE;
//STRIP001  }
//STRIP001  if ( Abs(nHeightDiff) > 1 && nDestHeight > 1 && nSourceHeight > 1 )
//STRIP001  {
//STRIP001      aVerFract = Fraction( nDestHeight, nSourceHeight );
//STRIP001      bResize = TRUE;
//STRIP001  }
//STRIP001  Point aRefPos = rDestRange.TopLeft();       // for resizing (after moving)
//STRIP001
//STRIP001  SdrObjListIter aIter( *pSrcPage, IM_FLAT );
//STRIP001  SdrObject* pOldObject = aIter.Next();
//STRIP001  while (pOldObject)
//STRIP001  {
//STRIP001      Rectangle aObjRect = pOldObject->GetBoundRect();
//STRIP001      if ( rSourceRange.IsInside( aObjRect ) )
//STRIP001      {
//STRIP001          SdrObject* pNewObject = pOldObject->Clone( pDestPage, this );
//STRIP001
//STRIP001          pNewObject->NbcMove( aMove );
//STRIP001          if ( bResize )
//STRIP001              pNewObject->NbcResize( aRefPos, aHorFract, aVerFract );
//STRIP001
//STRIP001          pDestPage->InsertObject( pNewObject );
//STRIP001          if (bRecording)
//STRIP001              AddCalcUndo( new SdrUndoInsertObj( *pNewObject ) );
//STRIP001
//STRIP001          //  handle chart data references (after InsertObject)
//STRIP001
//STRIP001          if ( pNewObject->GetObjIdentifier() == OBJ_OLE2 )
//STRIP001          {
//STRIP001              SvInPlaceObjectRef aIPObj = ((SdrOle2Obj*)pNewObject)->GetObjRef();
//STRIP001              if ( aIPObj.Is() && SchModuleDummy::HasID( *aIPObj->GetSvFactory() ) )
//STRIP001              {
//STRIP001                  SchMemChart* pChartData = SchDLL::GetChartData(aIPObj);
//STRIP001                  if ( pChartData )
//STRIP001                  {
//STRIP001                      ScChartArray aArray( pDoc, *pChartData );   // parses range description
//STRIP001                      ScRangeListRef xRanges = aArray.GetRangeList();
//STRIP001                      if ( aArray.IsValid() && xRanges.Is() )
//STRIP001                      {
//STRIP001                          ScDocument* pClipDoc = pClipModel->GetDocument();
//STRIP001
//STRIP001                          //  a clipboard document and its source share the same document item pool,
//STRIP001                          //  so the pointers can be compared to see if this is copy&paste within
//STRIP001                          //  the same document
//STRIP001                          BOOL bSameDoc = pDoc && pClipDoc && pDoc->GetPool() == pClipDoc->GetPool();
//STRIP001
//STRIP001                          BOOL bDestClip = pDoc && pDoc->IsClipboard();
//STRIP001
//STRIP001                          BOOL bInSourceRange = FALSE;
//STRIP001                          ScRange aClipRange;
//STRIP001                          if ( pClipDoc )
//STRIP001                          {
//STRIP001                              USHORT nClipStartX, nClipStartY, nClipEndX, nClipEndY;
//STRIP001                              pClipDoc->GetClipStart( nClipStartX, nClipStartY );
//STRIP001                              pClipDoc->GetClipArea( nClipEndX, nClipEndY, TRUE );
//STRIP001                              nClipEndX += nClipStartX;
//STRIP001                              nClipEndY += nClipStartY;   // GetClipArea returns the difference
//STRIP001
//STRIP001                              aClipRange = ScRange( nClipStartX, nClipStartY, nSourceTab,
//STRIP001                                                      nClipEndX, nClipEndY, nSourceTab );
//STRIP001
//STRIP001                              bInSourceRange = lcl_IsAllInRange( *xRanges, aClipRange );
//STRIP001                          }
//STRIP001
//STRIP001                          // always lose references when pasting into a clipboard document (transpose)
//STRIP001                          if ( ( bInSourceRange || bSameDoc ) && !bDestClip )
//STRIP001                          {
//STRIP001                              if ( bInSourceRange )
//STRIP001                              {
//STRIP001                                  if ( rDestPos != aClipRange.aStart )
//STRIP001                                  {
//STRIP001                                      //  update the data ranges to the new (copied) position
//STRIP001                                      ScRangeListRef xNewRanges = new ScRangeList( *xRanges );
//STRIP001                                      if ( lcl_MoveRanges( *xNewRanges, aClipRange, rDestPos ) )
//STRIP001                                      {
//STRIP001                                          aArray.SetRangeList( xNewRanges );
//STRIP001                                      }
//STRIP001                                  }
//STRIP001                              }
//STRIP001                              else
//STRIP001                              {
//STRIP001                                  //  leave the ranges unchanged
//STRIP001                                  //  Update has to be called anyway because parts of the data may have changed
//STRIP001                              }
//STRIP001
//STRIP001                              SchMemChart* pMemChart = aArray.CreateMemChart();
//STRIP001                              ScChartArray::CopySettings( *pMemChart, *pChartData );
//STRIP001                              SchDLL::Update( aIPObj, pMemChart );
//STRIP001                              delete pMemChart;
//STRIP001                          }
//STRIP001                          else
//STRIP001                          {
//STRIP001                              //  pasting into a new document without the complete source data
//STRIP001                              //  -> break connection to source data
//STRIP001
//STRIP001                              //  (see ScDocument::UpdateChartListenerCollection, PastingDrawFromOtherDoc)
//STRIP001
//STRIP001                                 pChartData->SomeData1().Erase();
//STRIP001                                 pChartData->SomeData2().Erase();
//STRIP001                                 pChartData->SomeData3().Erase();
//STRIP001                                 pChartData->SomeData4().Erase();
//STRIP001                                 SchChartRange aChartRange;
//STRIP001                                 pChartData->SetChartRange( aChartRange );
//STRIP001                                 pChartData->SetReadOnly( FALSE );
//STRIP001                                 SchDLL::Update( aIPObj, pChartData );
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001      }
//STRIP001
//STRIP001      pOldObject = aIter.Next();
//STRIP001  }
//STRIP001 }

// static
//STRIP001 String ScDrawLayer::GetVisibleName( SdrObject* pObj )
//STRIP001 {
//STRIP001  String aName = pObj->GetName();
//STRIP001  if ( pObj->GetObjIdentifier() == OBJ_OLE2 )
//STRIP001  {
//STRIP001      //  #95575# For OLE, the user defined name (GetName) is used
//STRIP001      //  if it's not empty (accepting possibly duplicate names),
//STRIP001      //  otherwise the persist name is used so every object appears
//STRIP001      //  in the Navigator at all.
//STRIP001
//STRIP001      if ( !aName.Len() )
//STRIP001          aName = static_cast<SdrOle2Obj*>(pObj)->GetPersistName();
//STRIP001  }
//STRIP001  return aName;
//STRIP001 }

/*N*/ inline IsNamedObject( SdrObject* pObj, const String& rName )
/*N*/ {
/*N*/   //  TRUE if rName is the object's Name or PersistName
/*N*/   //  (used to find a named object)
/*N*/
/*N*/   return ( pObj->GetName() == rName ||
/*N*/           ( pObj->GetObjIdentifier() == OBJ_OLE2 &&
/*N*/             static_cast<SdrOle2Obj*>(pObj)->GetPersistName() == rName ) );
/*N*/ }

/*N*/ SdrObject* ScDrawLayer::GetNamedObject( const String& rName, USHORT nId, USHORT& rFoundTab ) const
/*N*/ {
/*N*/   USHORT nTabCount = GetPageCount();
/*N*/   for (USHORT nTab=0; nTab<nTabCount; nTab++)
/*N*/   {
/*N*/       const SdrPage* pPage = GetPage(nTab);
/*N*/       DBG_ASSERT(pPage,"Page ?");
/*N*/       if (pPage)
/*N*/       {
/*N*/           SdrObjListIter aIter( *pPage, IM_DEEPWITHGROUPS );
/*N*/           SdrObject* pObject = aIter.Next();
/*N*/           while (pObject)
/*N*/           {
/*N*/               if ( nId == 0 || pObject->GetObjIdentifier() == nId )
/*N*/                   if ( IsNamedObject( pObject, rName ) )
/*N*/                   {
/*N*/                       rFoundTab = nTab;
/*N*/                       return pObject;
/*N*/                   }
/*N*/
/*N*/               pObject = aIter.Next();
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return NULL;
/*N*/ }

//STRIP001 String ScDrawLayer::GetNewGraphicName( long* pnCounter ) const
//STRIP001 {
//STRIP001  String aBase = ScGlobal::GetRscString(STR_GRAPHICNAME);
//STRIP001  aBase += ' ';
//STRIP001
//STRIP001  BOOL bThere = TRUE;
//STRIP001  String aName;
//STRIP001  USHORT nDummy;
//STRIP001     long nId = pnCounter ? *pnCounter : 0;
//STRIP001  while (bThere)
//STRIP001  {
//STRIP001      ++nId;
//STRIP001      aName = aBase;
//STRIP001      aName += String::CreateFromInt32( nId );
//STRIP001      bThere = ( GetNamedObject( aName, 0, nDummy ) != NULL );
//STRIP001  }
//STRIP001
//STRIP001     if ( pnCounter )
//STRIP001         *pnCounter = nId;
//STRIP001
//STRIP001  return aName;
//STRIP001 }

//STRIP001 void ScDrawLayer::EnsureGraphicNames()
//STRIP001 {
//STRIP001  //  make sure all graphic objects have names (after Excel import etc.)
//STRIP001
//STRIP001  USHORT nTabCount = GetPageCount();
//STRIP001  for (USHORT nTab=0; nTab<nTabCount; nTab++)
//STRIP001  {
//STRIP001      SdrPage* pPage = GetPage(nTab);
//STRIP001      DBG_ASSERT(pPage,"Page ?");
//STRIP001      if (pPage)
//STRIP001      {
//STRIP001          SdrObjListIter aIter( *pPage, IM_DEEPWITHGROUPS );
//STRIP001          SdrObject* pObject = aIter.Next();
//STRIP001
//STRIP001             /* #101799# The index passed to GetNewGraphicName() will be set to
//STRIP001                 the used index in each call. This prevents the repeated search
//STRIP001                 for all names from 1 to current index. */
//STRIP001             long nCounter = 0;
//STRIP001
//STRIP001          while (pObject)
//STRIP001          {
//STRIP001              if ( pObject->GetObjIdentifier() == OBJ_GRAF && pObject->GetName().Len() == 0 )
//STRIP001                     pObject->SetName( GetNewGraphicName( &nCounter ) );
//STRIP001
//STRIP001              pObject = aIter.Next();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 ULONG ScDrawLayer::GetDefTextHeight() const
//STRIP001 {
//STRIP001  return nDefTextHgt;     // protected in SdrModel
//STRIP001 }

/*N*/ void ScDrawLayer::SetAnchor( SdrObject* pObj, ScAnchorType eType )
/*N*/ {
/*N*/   // Ein an der Seite verankertes Objekt zeichnet sich durch eine Anker-Pos
/*N*/   // von (0,1) aus. Das ist ein shabby Trick, der aber funktioniert!
/*N*/   Point aAnchor( 0, eType == SCA_PAGE ? 1 : 0 );
/*N*/   pObj->SetAnchorPos( aAnchor );
/*N*/ }

/*N*/ ScAnchorType ScDrawLayer::GetAnchor( const SdrObject* pObj )
/*N*/ {
/*N*/   Point aAnchor( pObj->GetAnchorPos() );
/*N*/   return ( aAnchor.Y() != 0 ) ? SCA_PAGE : SCA_CELL;
/*N*/ }

/*N*/ ScDrawObjData* ScDrawLayer::GetObjData( SdrObject* pObj, BOOL bCreate )       // static
/*N*/ {
/*N*/   USHORT nCount = pObj->GetUserDataCount();
/*N*/   for( USHORT i = 0; i < nCount; i++ )
/*N*/   {
/*?*/       SdrObjUserData* pData = pObj->GetUserData( i );
/*?*/       if( pData && pData->GetInventor() == SC_DRAWLAYER
/*?*/                   && pData->GetId() == SC_UD_OBJDATA )
/*?*/           return (ScDrawObjData*) pData;
/*N*/   }
/*N*/   if( bCreate )
/*N*/   {
/*N*/       ScDrawObjData* pData = new ScDrawObjData;
/*N*/       pObj->InsertUserData( pData, 0 );
/*N*/       return pData;
/*N*/   }
/*N*/   return NULL;
/*N*/ }

/*N*/ ScIMapInfo* ScDrawLayer::GetIMapInfo( SdrObject* pObj )               // static
/*N*/ {
/*N*/   USHORT nCount = pObj->GetUserDataCount();
/*N*/   for( USHORT i = 0; i < nCount; i++ )
/*N*/   {
/*?*/       SdrObjUserData* pData = pObj->GetUserData( i );
/*?*/       if( pData && pData->GetInventor() == SC_DRAWLAYER
/*?*/                   && pData->GetId() == SC_UD_IMAPDATA )
/*?*/           return (ScIMapInfo*) pData;
/*N*/   }
/*N*/   return NULL;
/*N*/ }

//STRIP001 Graphic ScDrawLayer::GetGraphicFromOle2Obj( const SdrOle2Obj* pOle2Obj ) // static
//STRIP001 {
//STRIP001  SvInPlaceObjectRef  aIPObjRef = pOle2Obj->GetObjRef();
//STRIP001  Graphic             aGraphic;
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
//STRIP001
//STRIP001  return aGraphic;
//STRIP001 }

// static:
//STRIP001 IMapObject*  ScDrawLayer::GetHitIMapObject( SdrObject* pObj,
//STRIP001                                        const Point& rWinPoint, const Window& rCmpWnd )
//STRIP001 {
//STRIP001  const MapMode       aMap100( MAP_100TH_MM );
//STRIP001  MapMode             aWndMode = rCmpWnd.GetMapMode();
//STRIP001  Point               aRelPoint( rCmpWnd.LogicToLogic( rWinPoint, &aWndMode, &aMap100 ) );
//STRIP001  Rectangle           aLogRect = rCmpWnd.LogicToLogic( pObj->GetLogicRect(), &aWndMode, &aMap100 );
//STRIP001  ScIMapInfo*         pIMapInfo = GetIMapInfo( pObj );
//STRIP001  IMapObject*         pIMapObj = NULL;
//STRIP001
//STRIP001  if ( pIMapInfo )
//STRIP001  {
//STRIP001      Size        aGraphSize;
//STRIP001      ImageMap&   rImageMap = (ImageMap&) pIMapInfo->GetImageMap();
//STRIP001      Graphic     aGraphic;
//STRIP001      BOOL        bObjSupported = FALSE;
//STRIP001
//STRIP001      if ( pObj->ISA( SdrGrafObj )  ) // einfaches Grafik-Objekt
//STRIP001      {
//STRIP001          const SdrGrafObj*   pGrafObj = (const SdrGrafObj*) pObj;
//STRIP001          const GeoStat&      rGeo = pGrafObj->GetGeoStat();
//STRIP001          const Graphic&      rGraphic = pGrafObj->GetGraphic();
//STRIP001
//STRIP001          // Drehung rueckgaengig
//STRIP001          if ( rGeo.nDrehWink )
//STRIP001              RotatePoint( aRelPoint, aLogRect.TopLeft(), -rGeo.nSin, rGeo.nCos );
//STRIP001
//STRIP001          // Spiegelung rueckgaengig
//STRIP001          if ( ( (const SdrGrafObjGeoData*) pGrafObj->GetGeoData() )->bMirrored )
//STRIP001              aRelPoint.X() = aLogRect.Right() + aLogRect.Left() - aRelPoint.X();
//STRIP001
//STRIP001          // ggf. Unshear:
//STRIP001          if ( rGeo.nShearWink )
//STRIP001              ShearPoint( aRelPoint, aLogRect.TopLeft(), -rGeo.nTan );
//STRIP001
//STRIP001
//STRIP001          if ( rGraphic.GetPrefMapMode().GetMapUnit() == MAP_PIXEL )
//STRIP001              aGraphSize = rCmpWnd.PixelToLogic( rGraphic.GetPrefSize(),
//STRIP001                                                       aMap100 );
//STRIP001          else
//STRIP001              aGraphSize = OutputDevice::LogicToLogic( rGraphic.GetPrefSize(),
//STRIP001                                                       rGraphic.GetPrefMapMode(),
//STRIP001                                                       aMap100 );
//STRIP001
//STRIP001          bObjSupported = TRUE;
//STRIP001      }
//STRIP001      else if ( pObj->ISA( SdrOle2Obj ) ) // OLE-Objekt
//STRIP001      {
//STRIP001          SvInPlaceObjectRef aIPObjRef = ( (SdrOle2Obj*) pObj )->GetObjRef();
//STRIP001
//STRIP001          if ( aIPObjRef.Is() )
//STRIP001          {
//STRIP001              aGraphSize = aIPObjRef->GetVisArea().GetSize();
//STRIP001              bObjSupported = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // hat alles geklappt, dann HitTest ausfuehren
//STRIP001      if ( bObjSupported )
//STRIP001      {
//STRIP001          // relativen Mauspunkt berechnen
//STRIP001          aRelPoint -= aLogRect.TopLeft();
//STRIP001          pIMapObj = rImageMap.GetHitIMapObject( aGraphSize, aLogRect.GetSize(), aRelPoint );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return pIMapObj;
//STRIP001 }

//STRIP001 void ScDrawLayer::SetGlobalDrawPersist(SvPersist* pPersist)          // static
//STRIP001 {
//STRIP001  DBG_ASSERT(!pGlobalDrawPersist,"SetGlobalDrawPersist mehrfach");
//STRIP001  pGlobalDrawPersist = pPersist;
//STRIP001 }

/*N*/ void __EXPORT ScDrawLayer::SetChanged( FASTBOOL bFlg /* =TRUE */ )
/*N*/ {
/*N*/   if ( bFlg && pDoc )
/*N*/       pDoc->SetChartListenerCollectionNeedsUpdate( TRUE );
/*N*/   FmFormModel::SetChanged( bFlg );
/*N*/ }

/*N*/ SvStream* __EXPORT ScDrawLayer::GetDocumentStream(SdrDocumentStreamInfo& rStreamInfo) const
/*N*/ {
/*N*/   DBG_ASSERT( pDoc, "ScDrawLayer::GetDocumentStream without document" );
/*N*/   if ( !pDoc )
/*N*/       return NULL;
/*N*/
/*N*/   SvStorage*  pStor = pDoc->GetDocumentShell() ? pDoc->GetDocumentShell()->GetMedium()->GetStorage() : NULL;
/*N*/   SvStream*   pRet = NULL;
/*N*/
/*N*/   if( pStor )
/*N*/   {
/*N*/       if( rStreamInfo.maUserData.Len() &&
/*N*/           ( rStreamInfo.maUserData.GetToken( 0, ':' ) ==
/*N*/             String( RTL_CONSTASCII_USTRINGPARAM( "vnd.sun.star.Package" ) ) ) )
/*N*/       {
/*?*/           const String aPicturePath( rStreamInfo.maUserData.GetToken( 1, ':' ) );
/*?*/
/*?*/           // graphic from picture stream in picture storage in XML package
/*?*/           if( aPicturePath.GetTokenCount( '/' ) == 2 )
/*?*/           {
/*?*/               const String aPictureStreamName( aPicturePath.GetToken( 1, '/' ) );
/*?*/
/*?*/               if( !xPictureStorage.Is() )
/*?*/               {
/*?*/                   const String aPictureStorageName( aPicturePath.GetToken( 0, '/' ) );
/*?*/
/*?*/                   if( pStor->IsContained( aPictureStorageName ) &&
/*?*/                       pStor->IsStorage( aPictureStorageName )  )
/*?*/                   {
/*?*/                       ( (ScDrawLayer*) this )->xPictureStorage = pStor->OpenUCBStorage( aPictureStorageName, STREAM_READ | STREAM_WRITE );
/*?*/                   }
/*?*/               }
/*?*/
/*?*/               if( xPictureStorage.Is() &&
/*?*/                   xPictureStorage->IsContained( aPictureStreamName ) &&
/*?*/                   xPictureStorage->IsStream( aPictureStreamName ) )
/*?*/               {
/*?*/                   pRet = xPictureStorage->OpenStream( aPictureStreamName );
/*?*/               }
/*?*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           pRet = pStor->OpenStream( String::CreateFromAscii(RTL_CONSTASCII_STRINGPARAM(STRING_SCSTREAM)),
/*N*/                                     STREAM_READ | STREAM_WRITE | STREAM_TRUNC );
/*N*/
/*N*/           if( pRet )
/*N*/           {
/*N*/               pRet->SetVersion( pStor->GetVersion() );
/*N*/               pRet->SetKey( pStor->GetKey() );
/*N*/           }
/*N*/       }
/*N*/
/*N*/       rStreamInfo.mbDeleteAfterUse = ( pRet != NULL );
/*N*/   }
/*N*/
/*N*/   return pRet;
/*N*/ }

/*N*/ void ScDrawLayer::ReleasePictureStorage()
/*N*/ {
/*N*/   xPictureStorage.Clear();
/*N*/ }

//STRIP001 SdrLayerID __EXPORT ScDrawLayer::GetControlExportLayerId( const SdrObject & ) const
//STRIP001 {
//STRIP001  //  Layer fuer Export von Form-Controls in Versionen vor 5.0 - immer SC_LAYER_FRONT
//STRIP001  return SC_LAYER_FRONT;
//STRIP001 }



}
