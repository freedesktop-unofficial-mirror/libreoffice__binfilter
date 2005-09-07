/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_documen9.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 16:44:39 $
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

#ifdef PCH
// auto strip #include "core_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------

#include "scitems.hxx"
#include <bf_svx/eeitem.hxx>
#define ITEMID_FIELD EE_FEATURE_FIELD

#include <bf_svx/fontitem.hxx>
#include <bf_svx/forbiddencharacterstable.hxx>
#include <bf_svx/langitem.hxx>
// auto strip #include <bf_svx/svdetc.hxx>
#include <bf_svx/svditer.hxx>
#include <bf_svx/svdocapt.hxx>
// auto strip #include <bf_svx/svdograf.hxx>
#include <bf_svx/svdoole2.hxx>
#include <bf_svx/svdouno.hxx>
#include <bf_svx/svdpage.hxx>
// auto strip #include <bf_svx/svdundo.hxx>
#include <bf_svx/xtable.hxx>
#include <bf_sfx2/objsh.hxx>
#include <bf_sfx2/printer.hxx>
#include <svtools/saveopt.hxx>
#include <svtools/pathoptions.hxx>
// auto strip #include <so3/ipobj.hxx>
#include <bf_sch/schdll.hxx>
#include <bf_sch/schdll0.hxx>
// auto strip #include <bf_sch/memchrt.hxx>

#include "document.hxx"
#include "docoptio.hxx"
// auto strip #include "table.hxx"
#include "drwlayer.hxx"
// auto strip #include "markdata.hxx"
#include "userdat.hxx"
#include "patattr.hxx"
#include "rechead.hxx"
#include "poolhelp.hxx"
#include "docpool.hxx"
// auto strip #include "chartarr.hxx"
#include "detfunc.hxx"      // for UpdateAllComments
#include "editutil.hxx"
namespace binfilter {


// -----------------------------------------------------------------------


//STRIP001 void ScDocument::SetLinkManager( SvxLinkManager* pNew )
//STRIP001 {
//STRIP001  pLinkManager = pNew;
//STRIP001  if (pDrawLayer)
//STRIP001      pDrawLayer->SetLinkManager( pNew );
//STRIP001 }

//STRIP001 SfxBroadcaster* ScDocument::GetDrawBroadcaster()
//STRIP001 {
//STRIP001  return pDrawLayer;
//STRIP001 }

/*N*/ void ScDocument::BeginDrawUndo()
/*N*/ {
/*N*/   if (pDrawLayer)
/*N*/       pDrawLayer->BeginCalcUndo();
/*N*/ }

/*N*/ XColorTable* ScDocument::GetColorTable()
/*N*/ {
/*N*/   if (pDrawLayer)
/*N*/       return pDrawLayer->GetColorTable();
/*N*/   else
/*N*/   {
/*N*/       if (!pColorTable)
/*N*/       {
/*N*/           SvtPathOptions aPathOpt;
/*N*/           pColorTable = new XColorTable( aPathOpt.GetPalettePath() );
/*N*/       }
/*N*/
/*N*/       return pColorTable;
/*N*/   }
/*N*/ }

BOOL lcl_AdjustRanges( ScRangeList& rRanges, USHORT nSource, USHORT nDest, USHORT nTabCount )
{
    //! if multiple sheets are copied, update references into the other copied sheets?

    BOOL bChanged = FALSE;

    DBG_BF_ASSERT(0, "STRIP"); //STRIP001 ULONG nCount = rRanges.Count();
//STRIP001  for (ULONG i=0; i<nCount; i++)
//STRIP001  {
//STRIP001      ScRange* pRange = rRanges.GetObject(i);
//STRIP001      if ( pRange->aStart.Tab() == nSource && pRange->aEnd.Tab() == nSource )
//STRIP001      {
//STRIP001          pRange->aStart.SetTab( nDest );
//STRIP001          pRange->aEnd.SetTab( nDest );
//STRIP001          bChanged = TRUE;
//STRIP001      }
//STRIP001      if ( pRange->aStart.Tab() >= nTabCount )
//STRIP001      {
//STRIP001          pRange->aStart.SetTab( nTabCount ? ( nTabCount - 1 ) : 0 );
//STRIP001          bChanged = TRUE;
//STRIP001      }
//STRIP001      if ( pRange->aEnd.Tab() >= nTabCount )
//STRIP001      {
//STRIP001          pRange->aEnd.SetTab( nTabCount ? ( nTabCount - 1 ) : 0 );
//STRIP001          bChanged = TRUE;
//STRIP001      }
//STRIP001  }

    return bChanged;
}

/*N*/ void ScDocument::TransferDrawPage(ScDocument* pSrcDoc, USHORT nSrcPos, USHORT nDestPos)
/*N*/ {
/*N*/   if (pDrawLayer && pSrcDoc->pDrawLayer)
/*N*/   {
/*?*/       SdrPage* pOldPage = pSrcDoc->pDrawLayer->GetPage(nSrcPos);
/*?*/       SdrPage* pNewPage = pDrawLayer->GetPage(nDestPos);
/*?*/
/*?*/       if (pOldPage && pNewPage)
/*?*/       {
/*?*/           SdrObjListIter aIter( *pOldPage, IM_FLAT );
/*?*/           SdrObject* pOldObject = aIter.Next();
/*?*/           while (pOldObject)
/*?*/           {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/                SdrObject* pNewObject = pOldObject->Clone( pNewPage, pDrawLayer );
//STRIP001 /*?*/                pNewObject->NbcMove(Size(0,0));
//STRIP001 /*?*/                pNewPage->InsertObject( pNewObject );
//STRIP001 /*?*/
//STRIP001 /*?*/                if (pDrawLayer->IsRecording())
//STRIP001 /*?*/                    pDrawLayer->AddCalcUndo( new SdrUndoInsertObj( *pNewObject ) );
//STRIP001 /*?*/
//STRIP001 /*?*/                //  #71726# if it's a chart, make sure the data references are valid
//STRIP001 /*?*/                //  (this must be after InsertObject!)
//STRIP001 /*?*/
//STRIP001 /*?*/                if ( pNewObject->GetObjIdentifier() == OBJ_OLE2 )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    //  test if it's a chart with HasID, because GetChartData always loads the DLL
//STRIP001 /*?*/                    SvInPlaceObjectRef aIPObj = ((SdrOle2Obj*)pNewObject)->GetObjRef();
//STRIP001 /*?*/                    if ( aIPObj.Is() && SchModuleDummy::HasID( *aIPObj->GetSvFactory() ) )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        SchMemChart* pChartData = SchDLL::GetChartData(aIPObj);
//STRIP001 /*?*/                        if ( pChartData )
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            ScChartArray aArray( this, *pChartData );   // parses range description
//STRIP001 /*?*/                            ScRangeListRef xRanges = aArray.GetRangeList();
//STRIP001 /*?*/                            if ( xRanges.Is() )
//STRIP001 /*?*/                            {
//STRIP001 /*?*/                                ScRangeListRef xNewRanges = new ScRangeList( *xRanges );
//STRIP001 /*?*/                                if ( lcl_AdjustRanges( *xNewRanges,
//STRIP001 /*?*/                                                        nSrcPos, nDestPos, GetTableCount() ) )
//STRIP001 /*?*/                                {
//STRIP001 /*?*/                                    aArray.SetRangeList( xNewRanges );
//STRIP001 /*?*/                                }
//STRIP001 /*?*/
//STRIP001 /*?*/                                // update all charts, even if the ranges were not changed
//STRIP001 /*?*/
//STRIP001 /*?*/                                SchMemChart* pMemChart = aArray.CreateMemChart();
//STRIP001 /*?*/                                ScChartArray::CopySettings( *pMemChart, *pChartData );
//STRIP001 /*?*/                                SchDLL::Update( aIPObj, pMemChart );
//STRIP001 /*?*/                                delete pMemChart;
//STRIP001 /*?*/                            }
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                }
//STRIP001 /*?*/
//STRIP001 /*?*/                pOldObject = aIter.Next();
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/ }

//STRIP001 void ScDocument::ClearDrawPage(USHORT nTab)
//STRIP001 {
//STRIP001  if (pDrawLayer)
//STRIP001  {
//STRIP001      SdrPage* pPage = pDrawLayer->GetPage(nTab);
//STRIP001      if (pPage)
//STRIP001          pPage->Clear();
//STRIP001      else
//STRIP001          DBG_ERROR("ScDocument::DeleteDrawObjects: pPage ???");
//STRIP001  }
//STRIP001 }

/*N*/ void ScDocument::InitDrawLayer( SfxObjectShell* pDocShell )
/*N*/ {
/*N*/   if (pDocShell && !pShell)
/*N*/       pShell = pDocShell;
/*N*/
/*N*/ //    DBG_ASSERT(pShell,"InitDrawLayer ohne Shell");
/*N*/
/*N*/   if (!pDrawLayer)
/*N*/   {
/*N*/       String aName;
/*N*/       if ( pShell && !pShell->IsLoading() )       // #88438# don't call GetTitle while loading
/*N*/           aName = pShell->GetTitle();
/*N*/       pDrawLayer = new ScDrawLayer( this, aName );
/*N*/       if (pLinkManager)
/*N*/           pDrawLayer->SetLinkManager( pLinkManager );
/*N*/
/*N*/       //  Drawing pages are accessed by table number, so they must also be present
/*N*/       //  for preceding table numbers, even if the tables aren't allocated
/*N*/       //  (important for clipboard documents).
/*N*/
/*N*/       USHORT nDrawPages = 0;
/*N*/       USHORT nTab;
/*N*/       for (nTab=0; nTab<=MAXTAB; nTab++)
/*N*/           if (pTab[nTab])
/*N*/               nDrawPages = nTab + 1;          // needed number of pages
/*N*/
/*N*/       for (nTab=0; nTab<nDrawPages; nTab++)
/*N*/       {
/*N*/           pDrawLayer->ScAddPage( nTab );      // always add page, with or without the table
/*N*/           if (pTab[nTab])
/*N*/           {
/*N*/               String aName;
/*N*/               pTab[nTab]->GetName(aName);
/*N*/               pDrawLayer->ScRenamePage( nTab, aName );
/*N*/
/*N*/               pTab[nTab]->SetDrawPageSize();  // #54782# sofort die richtige Groesse
/*N*/ #if 0
/*N*/               ULONG nx = (ULONG) ((double) (MAXCOL+1) * STD_COL_WIDTH           * HMM_PER_TWIPS );
/*N*/               ULONG ny = (ULONG) ((double) (MAXROW+1) * ScGlobal::nStdRowHeight * HMM_PER_TWIPS );
/*N*/               pDrawLayer->SetPageSize( nTab, Size( nx, ny ) );
/*N*/ #endif
/*N*/           }
/*N*/       }
/*N*/
/*N*/       pDrawLayer->SetDefaultTabulator( GetDocOptions().GetTabDistance() );
/*N*/
/*N*/       UpdateDrawPrinter();
/*N*/       UpdateDrawLanguages();
/*N*/       if (bImportingXML)
/*?*/           pDrawLayer->EnableAdjust(FALSE);
/*N*/
/*N*/       pDrawLayer->SetForbiddenCharsTable( xForbiddenCharacters );
/*N*/       pDrawLayer->SetCharCompressType( GetAsianCompression() );
/*N*/       pDrawLayer->SetKernAsianPunctuation( GetAsianKerning() );
/*N*/   }
/*N*/ }

/*N*/ void ScDocument::UpdateDrawLanguages()
/*N*/ {
/*N*/   if (pDrawLayer)
/*N*/   {
/*N*/       SfxItemPool& rDrawPool = pDrawLayer->GetItemPool();
/*N*/       rDrawPool.SetPoolDefaultItem( SvxLanguageItem( eLanguage, EE_CHAR_LANGUAGE ) );
/*N*/       rDrawPool.SetPoolDefaultItem( SvxLanguageItem( eCjkLanguage, EE_CHAR_LANGUAGE_CJK ) );
/*N*/       rDrawPool.SetPoolDefaultItem( SvxLanguageItem( eCtlLanguage, EE_CHAR_LANGUAGE_CTL ) );
/*N*/   }
/*N*/ }

/*N*/ void ScDocument::UpdateDrawPrinter()
/*N*/ {
/*N*/   if (pDrawLayer)
/*N*/   {
/*N*/       // use the printer even if IsValid is false
/*N*/       // Application::GetDefaultDevice causes trouble with changing MapModes
/*N*/
/*N*/       OutputDevice* pRefDev = GetPrinter();
/*N*/       pRefDev->SetMapMode( MAP_100TH_MM );
/*N*/       pDrawLayer->SetRefDevice(pRefDev);
/*N*/   }
/*N*/ }

/*N*/ BOOL ScDocument::IsChart( SdrObject* pObject )
/*N*/ {
/*N*/   if ( pObject->GetObjIdentifier() == OBJ_OLE2 )
/*N*/   {
/*N*/       SvInPlaceObjectRef aIPObj = ((SdrOle2Obj*)pObject)->GetObjRef();
/*N*/       if (aIPObj.Is())
/*N*/       {
/*N*/           SvGlobalName aObjClsId = *aIPObj->GetSvFactory();
/*N*/           if (SchModuleDummy::HasID( aObjClsId ))
/*N*/               return TRUE;
/*N*/       }
/*N*/   }
/*N*/   return FALSE;
/*N*/ }

/*N*/ IMPL_LINK_INLINE_START( ScDocument, GetUserDefinedColor, USHORT *, pColorIndex )
/*N*/ {
/*N*/   return (long) &((GetColorTable()->Get(*pColorIndex))->GetColor());
/*N*/ }
/*N*/ IMPL_LINK_INLINE_END( ScDocument, GetUserDefinedColor, USHORT *, pColorIndex )

/*N*/ void ScDocument::DeleteDrawLayer()
/*N*/ {
/*N*/   delete pDrawLayer;
/*N*/ }

/*N*/ void ScDocument::DeleteColorTable()
/*N*/ {
/*N*/   delete pColorTable;
/*N*/ }

/*N*/ void ScDocument::LoadDrawLayer(SvStream& rStream)
/*N*/ {
/*N*/   InitDrawLayer();                        // anlegen
/*N*/   pDrawLayer->Load(rStream);
/*N*/
/*N*/   //  nMaxTableNumber ist noch nicht initialisiert
/*N*/
/*N*/   USHORT nTableCount = 0;
/*N*/   while ( nTableCount <= MAXTAB && pTab[nTableCount] )
/*N*/       ++nTableCount;
/*N*/
/*N*/   USHORT nPageCount = pDrawLayer->GetPageCount();
/*N*/   if ( nPageCount > nTableCount && nTableCount != 0 )
/*N*/   {
/*?*/       //  Manchmal sind beim Kopieren/Verschieben/Undo von Tabellen zuviele
/*?*/       //  (leere) Pages in der Tabelle stehengeblieben. Weg damit!
/*?*/
/*?*/       DBG_ERROR("zuviele Draw-Pages in der Datei");
/*?*/
/*?*/       for (USHORT i=nTableCount; i<nPageCount; i++)
/*?*/           pDrawLayer->DeletePage(nTableCount);
/*N*/   }
/*N*/
/*N*/   //  Controls auf richtigen Layer setzen
/*N*/   //  (zumindest in Dateien aus der 502 koennen sie falsch sein,
/*N*/   //   wegen des fehlenden Layers in alten Dateien)
/*N*/
/*N*/   nPageCount = pDrawLayer->GetPageCount();
/*N*/   for (USHORT i=0; i<nPageCount; i++)
/*N*/   {
/*N*/       SdrPage* pPage = pDrawLayer->GetPage(i);
/*N*/       SdrObjListIter aIter( *pPage, IM_DEEPNOGROUPS );
/*N*/       SdrObject* pObject = aIter.Next();
/*N*/       while (pObject)
/*N*/       {
/*N*/           if ( pObject->ISA(SdrUnoObj) && pObject->GetLayer() != SC_LAYER_CONTROLS )
/*N*/           {
/*?*/               pObject->NbcSetLayer(SC_LAYER_CONTROLS);
/*?*/               DBG_ERROR("Control war auf falschem Layer");
/*N*/           }
/*N*/           pObject = aIter.Next();
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void ScDocument::StoreDrawLayer(SvStream& rStream) const
/*N*/ {
/*N*/   if (pDrawLayer)
/*N*/   {
/*N*/       //  SetSavePortable wird mit VCL nicht mehr gebraucht
/*N*/       //BOOL bIndep = SFX_APP()->GetOptions().IsIndepGrfFmt();
/*N*/       //pDrawLayer->SetSavePortable( bIndep );
/*N*/
/*N*/       SvtSaveOptions aSaveOpt;
/*N*/       SvtSaveOptions::SaveGraphicsMode eMode = aSaveOpt.GetSaveGraphicsMode();
/*N*/
/*N*/       BOOL bNative = ( eMode == SvtSaveOptions::SaveGraphicsOriginal );
/*N*/       BOOL bCompr = bNative || ( eMode == SvtSaveOptions::SaveGraphicsCompressed );
/*N*/
/*N*/       pDrawLayer->SetSaveCompressed( bCompr );
/*N*/       pDrawLayer->SetSaveNative( bNative );
/*N*/
/*N*/       pDrawLayer->GetItemPool().SetFileFormatVersion( (USHORT)rStream.GetVersion() );
/*N*/       pDrawLayer->Store(rStream);
/*N*/   }
/*N*/ }

/*N*/ BOOL ScDocument::DrawGetPrintArea( ScRange& rRange, BOOL bSetHor, BOOL bSetVer ) const
/*N*/ {
/*N*/   return pDrawLayer->GetPrintArea( rRange, bSetHor, bSetVer );
/*N*/ }

//STRIP001 void ScDocument::DrawMovePage( USHORT nOldPos, USHORT nNewPos )
//STRIP001 {
//STRIP001  pDrawLayer->ScMovePage(nOldPos,nNewPos);
//STRIP001 }

//STRIP001 void ScDocument::DrawCopyPage( USHORT nOldPos, USHORT nNewPos )
//STRIP001 {
//STRIP001  // angelegt wird die Page schon im ScTable ctor
//STRIP001  pDrawLayer->ScCopyPage( nOldPos, nNewPos, FALSE );
//STRIP001 }

//STRIP001 void ScDocument::DeleteObjectsInArea( USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2,
//STRIP001                      const ScMarkData& rMark )
//STRIP001 {
//STRIP001  if (!pDrawLayer)
//STRIP001      return;
//STRIP001
//STRIP001  USHORT nTabCount = GetTableCount();
//STRIP001  for (USHORT nTab=0; nTab<=nTabCount; nTab++)
//STRIP001      if (pTab[nTab] && rMark.GetTableSelect(nTab))
//STRIP001          pDrawLayer->DeleteObjectsInArea( nTab, nCol1, nRow1, nCol2, nRow2 );
//STRIP001 }

//STRIP001 void ScDocument::DeleteObjects( USHORT nTab )
//STRIP001 {
//STRIP001  if (!pDrawLayer)
//STRIP001      return;
//STRIP001
//STRIP001  if ( nTab<=MAXTAB && pTab[nTab] )
//STRIP001      pDrawLayer->DeleteObjects( nTab );
//STRIP001  else
//STRIP001      DBG_ERROR("DeleteObjects: falsche Tabelle");
//STRIP001 }

//STRIP001 void ScDocument::DeleteObjectsInSelection( const ScMarkData& rMark )
//STRIP001 {
//STRIP001  if (!pDrawLayer)
//STRIP001      return;
//STRIP001
//STRIP001  pDrawLayer->DeleteObjectsInSelection( rMark );
//STRIP001 }

//STRIP001 BOOL ScDocument::HasOLEObjectsInArea( const ScRange& rRange, const ScMarkData* pTabMark )
//STRIP001 {
//STRIP001  //  pTabMark is used only for selected tables. If pTabMark is 0, all tables of rRange are used.
//STRIP001
//STRIP001  if (!pDrawLayer)
//STRIP001      return FALSE;
//STRIP001
//STRIP001  USHORT nStartTab = 0;
//STRIP001  USHORT nEndTab = MAXTAB;
//STRIP001  if ( !pTabMark )
//STRIP001  {
//STRIP001      nStartTab = rRange.aStart.Tab();
//STRIP001      nEndTab = rRange.aEnd.Tab();
//STRIP001  }
//STRIP001
//STRIP001  for (USHORT nTab = nStartTab; nTab <= nEndTab; nTab++)
//STRIP001  {
//STRIP001      if ( !pTabMark || pTabMark->GetTableSelect(nTab) )
//STRIP001      {
//STRIP001          Rectangle aMMRect = GetMMRect( rRange.aStart.Col(), rRange.aStart.Row(),
//STRIP001                                          rRange.aEnd.Col(), rRange.aEnd.Row(), nTab );
//STRIP001
//STRIP001          SdrPage* pPage = pDrawLayer->GetPage(nTab);
//STRIP001          DBG_ASSERT(pPage,"Page ?");
//STRIP001          if (pPage)
//STRIP001          {
//STRIP001              SdrObjListIter aIter( *pPage, IM_FLAT );
//STRIP001              SdrObject* pObject = aIter.Next();
//STRIP001              while (pObject)
//STRIP001              {
//STRIP001                  if ( pObject->GetObjIdentifier() == OBJ_OLE2 &&
//STRIP001                          aMMRect.IsInside( pObject->GetBoundRect() ) )
//STRIP001                      return TRUE;
//STRIP001
//STRIP001                  pObject = aIter.Next();
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return FALSE;
//STRIP001 }


//STRIP001 void ScDocument::StopAnimations( USHORT nTab, Window* pWin )
//STRIP001 {
//STRIP001  if (!pDrawLayer)
//STRIP001      return;
//STRIP001  SdrPage* pPage = pDrawLayer->GetPage(nTab);
//STRIP001  DBG_ASSERT(pPage,"Page ?");
//STRIP001  if (!pPage)
//STRIP001      return;
//STRIP001
//STRIP001  SdrObjListIter aIter( *pPage, IM_FLAT );
//STRIP001  SdrObject* pObject = aIter.Next();
//STRIP001  while (pObject)
//STRIP001  {
//STRIP001      if (pObject->ISA(SdrGrafObj))
//STRIP001      {
//STRIP001          SdrGrafObj* pGrafObj = (SdrGrafObj*)pObject;
//STRIP001          if ( pGrafObj->IsAnimated() )
//STRIP001 //!              pGrafObj->StopAnimation( pWin );
//STRIP001              pGrafObj->StopAnimation();
//STRIP001      }
//STRIP001      pObject = aIter.Next();
//STRIP001  }
//STRIP001 }

//STRIP001 void ScDocument::StartAnimations( USHORT nTab, Window* pWin )
//STRIP001 {
//STRIP001  if (!pDrawLayer)
//STRIP001      return;
//STRIP001  SdrPage* pPage = pDrawLayer->GetPage(nTab);
//STRIP001  DBG_ASSERT(pPage,"Page ?");
//STRIP001  if (!pPage)
//STRIP001      return;
//STRIP001
//STRIP001  SdrObjListIter aIter( *pPage, IM_FLAT );
//STRIP001  SdrObject* pObject = aIter.Next();
//STRIP001  while (pObject)
//STRIP001  {
//STRIP001      if (pObject->ISA(SdrGrafObj))
//STRIP001      {
//STRIP001          SdrGrafObj* pGrafObj = (SdrGrafObj*)pObject;
//STRIP001          if ( pGrafObj->IsAnimated() )
//STRIP001          {
//STRIP001              const Rectangle& rRect = pGrafObj->GetBoundRect();
//STRIP001              pGrafObj->StartAnimation( pWin, rRect.TopLeft(), rRect.GetSize() );
//STRIP001          }
//STRIP001      }
//STRIP001      pObject = aIter.Next();
//STRIP001  }
//STRIP001 }

/*N*/ BOOL ScDocument::HasNoteObject( USHORT nCol, USHORT nRow, USHORT nTab ) const
/*N*/ {
/*N*/   if (!pDrawLayer)
/*N*/       return FALSE;
/*N*/   SdrPage* pPage = pDrawLayer->GetPage(nTab);
/*N*/   DBG_ASSERT(pPage,"Page ?");
/*N*/   if (!pPage)
/*N*/       return FALSE;
/*N*/
/*N*/   BOOL bFound = FALSE;
/*N*/
/*N*/   SdrObjListIter aIter( *pPage, IM_FLAT );
/*N*/   SdrObject* pObject = aIter.Next();
/*N*/   while (pObject && !bFound)
/*N*/   {
/*N*/       if ( pObject->GetLayer() == SC_LAYER_INTERN && pObject->ISA( SdrCaptionObj ) )
/*N*/       {
/*N*/           ScDrawObjData* pData = ScDrawLayer::GetObjData( pObject );
/*N*/           if ( pData && nCol == pData->aStt.nCol && nRow == pData->aStt.nRow )
/*N*/               bFound = TRUE;
/*N*/       }
/*N*/       pObject = aIter.Next();
/*N*/   }
/*N*/
/*N*/   return bFound;
/*N*/ }

/*N*/ void ScDocument::RefreshNoteFlags()
/*N*/ {
/*N*/   if (!pDrawLayer)
/*N*/       return;
/*N*/
/*N*/   BOOL bAnyIntObj = FALSE;
/*N*/   USHORT nTab;
/*N*/   ScPostIt aNote;
/*N*/   for (nTab=0; nTab<=MAXTAB && pTab[nTab]; nTab++)
/*N*/   {
/*N*/       SdrPage* pPage = pDrawLayer->GetPage(nTab);
/*N*/       DBG_ASSERT(pPage,"Page ?");
/*N*/       if (pPage)
/*N*/       {
/*N*/           SdrObjListIter aIter( *pPage, IM_FLAT );
/*N*/           SdrObject* pObject = aIter.Next();
/*N*/           while (pObject)
/*N*/           {
/*N*/               if ( pObject->GetLayer() == SC_LAYER_INTERN )
/*N*/               {
/*?*/                   bAnyIntObj = TRUE;  // for all internal objects, including detective
/*?*/
/*?*/                   if ( pObject->ISA( SdrCaptionObj ) )
/*?*/                   {
/*?*/                       ScDrawObjData* pData = ScDrawLayer::GetObjData( pObject );
/*?*/                       if ( pData )
/*?*/                       {
/*?*/                           if ( GetNote( pData->aStt.nCol, pData->aStt.nRow, nTab, aNote ) )
/*?*/                               if ( !aNote.IsShown() )
/*?*/                               {
/*?*/                                   aNote.SetShown(TRUE);
/*?*/                                   SetNote( pData->aStt.nCol, pData->aStt.nRow, nTab, aNote );
/*?*/                               }
/*?*/                       }
/*?*/                   }
/*N*/               }
/*N*/               pObject = aIter.Next();
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (bAnyIntObj)
/*N*/   {
/*?*/       //  update attributes for all note objects and the colors of detective objects
/*?*/       //  (we don't know with which settings the file was created)
/*?*/
/*N*/   ScDetectiveFunc aFunc( this, 0 ); // detective.sdc
/*N*/ /*?*/         aFunc.UpdateAllComments();
/*N*/ /*?*/         aFunc.UpdateAllArrowColors();
/*N*/   }
/*N*/ }

/*N*/ BOOL ScDocument::HasBackgroundDraw( USHORT nTab, const Rectangle& rMMRect )
/*N*/ {
/*N*/   //  Gibt es Objekte auf dem Hintergrund-Layer, die (teilweise) von rMMRect
/*N*/   //  betroffen sind?
/*N*/   //  (fuer Drawing-Optimierung, vor dem Hintergrund braucht dann nicht geloescht
/*N*/   //   zu werden)
/*N*/
/*N*/   if (!pDrawLayer)
/*N*/       return FALSE;
/*N*/   SdrPage* pPage = pDrawLayer->GetPage(nTab);
/*N*/   DBG_ASSERT(pPage,"Page ?");
/*N*/   if (!pPage)
/*N*/       return FALSE;
/*N*/
/*N*/   BOOL bFound = FALSE;
/*N*/
/*N*/   SdrObjListIter aIter( *pPage, IM_FLAT );
/*N*/   SdrObject* pObject = aIter.Next();
/*N*/   while (pObject && !bFound)
/*N*/   {
/*N*/       if ( pObject->GetLayer() == SC_LAYER_BACK && pObject->GetBoundRect().IsOver( rMMRect ) )
/*N*/           bFound = TRUE;
/*N*/       pObject = aIter.Next();
/*N*/   }
/*N*/
/*N*/   return bFound;
/*N*/ }

//STRIP001 BOOL ScDocument::HasAnyDraw( USHORT nTab, const Rectangle& rMMRect )
//STRIP001 {
//STRIP001  //  Gibt es ueberhaupt Objekte, die (teilweise) von rMMRect
//STRIP001  //  betroffen sind?
//STRIP001  //  (um leere Seiten beim Drucken zu erkennen)
//STRIP001
//STRIP001  if (!pDrawLayer)
//STRIP001      return FALSE;
//STRIP001  SdrPage* pPage = pDrawLayer->GetPage(nTab);
//STRIP001  DBG_ASSERT(pPage,"Page ?");
//STRIP001  if (!pPage)
//STRIP001      return FALSE;
//STRIP001
//STRIP001  BOOL bFound = FALSE;
//STRIP001
//STRIP001  SdrObjListIter aIter( *pPage, IM_FLAT );
//STRIP001  SdrObject* pObject = aIter.Next();
//STRIP001  while (pObject && !bFound)
//STRIP001  {
//STRIP001      if ( pObject->GetBoundRect().IsOver( rMMRect ) )
//STRIP001          bFound = TRUE;
//STRIP001      pObject = aIter.Next();
//STRIP001  }
//STRIP001
//STRIP001  return bFound;
//STRIP001 }

//STRIP001 void ScDocument::EnsureGraphicNames()
//STRIP001 {
//STRIP001  if (pDrawLayer)
//STRIP001      pDrawLayer->EnsureGraphicNames();
//STRIP001 }

//STRIP001 SdrObject* ScDocument::GetObjectAtPoint( USHORT nTab, const Point& rPos )
//STRIP001 {
//STRIP001  //  fuer Drag&Drop auf Zeichenobjekt
//STRIP001
//STRIP001  SdrObject* pFound = NULL;
//STRIP001  if (pDrawLayer && pTab[nTab])
//STRIP001  {
//STRIP001      SdrPage* pPage = pDrawLayer->GetPage(nTab);
//STRIP001      DBG_ASSERT(pPage,"Page ?");
//STRIP001      if (pPage)
//STRIP001      {
//STRIP001          SdrObjListIter aIter( *pPage, IM_FLAT );
//STRIP001          SdrObject* pObject = aIter.Next();
//STRIP001          while (pObject)
//STRIP001          {
//STRIP001              if ( pObject->GetBoundRect().IsInside(rPos) )
//STRIP001              {
//STRIP001                  //  Intern interessiert gar nicht
//STRIP001                  //  Objekt vom Back-Layer nur, wenn kein Objekt von anderem Layer getroffen
//STRIP001
//STRIP001                  SdrLayerID nLayer = pObject->GetLayer();
//STRIP001                  if ( nLayer != SC_LAYER_INTERN )
//STRIP001                  {
//STRIP001                      if ( nLayer != SC_LAYER_BACK ||
//STRIP001                              !pFound || pFound->GetLayer() == SC_LAYER_BACK )
//STRIP001                      {
//STRIP001                          pFound = pObject;
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001              //  weitersuchen -> letztes (oberstes) getroffenes Objekt nehmen
//STRIP001
//STRIP001              pObject = aIter.Next();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return pFound;
//STRIP001 }

/*N*/ BOOL ScDocument::IsPrintEmpty( USHORT nTab, USHORT nStartCol, USHORT nStartRow,
/*N*/                               USHORT nEndCol, USHORT nEndRow, BOOL bLeftIsEmpty,
/*N*/                               ScRange* pLastRange, Rectangle* pLastMM ) const
/*N*/ {
    DBG_BF_ASSERT(0, "STRIP"); //STRIP001   if (!IsBlockEmpty( nTab, nStartCol, nStartRow, nEndCol, nEndRow ))
//STRIP001      return FALSE;
//STRIP001
//STRIP001  ScDocument* pThis = (ScDocument*)this;  //! GetMMRect / HasAnyDraw etc. const !!!
//STRIP001
//STRIP001  Rectangle aMMRect;
//STRIP001  if ( pLastRange && pLastMM && nTab == pLastRange->aStart.Tab() &&
//STRIP001          nStartRow == pLastRange->aStart.Row() && nEndRow == pLastRange->aEnd.Row() )
//STRIP001  {
//STRIP001      //  keep vertical part of aMMRect, only update horizontal position
//STRIP001      aMMRect = *pLastMM;
//STRIP001
//STRIP001      long nLeft = 0;
//STRIP001      USHORT i;
//STRIP001      for (i=0; i<nStartCol; i++)
//STRIP001          nLeft += GetColWidth(i,nTab);
//STRIP001      long nRight = nLeft;
//STRIP001      for (i=nStartCol; i<=nEndCol; i++)
//STRIP001          nRight += GetColWidth(i,nTab);
//STRIP001
//STRIP001      aMMRect.Left()  = (long)(nLeft  * HMM_PER_TWIPS);
//STRIP001      aMMRect.Right() = (long)(nRight * HMM_PER_TWIPS);
//STRIP001  }
//STRIP001  else
//STRIP001      aMMRect = pThis->GetMMRect( nStartCol, nStartRow, nEndCol, nEndRow, nTab );
//STRIP001
//STRIP001  if ( pLastRange && pLastMM )
//STRIP001  {
//STRIP001      *pLastRange = ScRange( nStartCol, nStartRow, nTab, nEndCol, nEndRow, nTab );
//STRIP001      *pLastMM = aMMRect;
//STRIP001  }
//STRIP001
//STRIP001  if ( pThis->HasAnyDraw( nTab, aMMRect ))
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if ( nStartCol > 0 && !bLeftIsEmpty )
//STRIP001  {
//STRIP001      //  aehnlich wie in ScPrintFunc::AdjustPrintArea
//STRIP001      //! ExtendPrintArea erst ab Start-Spalte des Druckbereichs
//STRIP001
//STRIP001      USHORT nExtendCol = nStartCol - 1;
//STRIP001      USHORT nTmpRow = nEndRow;
//STRIP001
//STRIP001      pThis->ExtendMerge( 0,nStartRow, nExtendCol,nTmpRow, nTab,
//STRIP001                          FALSE, TRUE );      // kein Refresh, incl. Attrs
//STRIP001
//STRIP001      OutputDevice* pDev = pThis->GetPrinter();
//STRIP001      pDev->SetMapMode( MAP_PIXEL );              // wichtig fuer GetNeededSize
//STRIP001      pThis->ExtendPrintArea( pDev, nTab, 0, nStartRow, nExtendCol, nEndRow );
//STRIP001      if ( nExtendCol >= nStartCol )
//STRIP001          return FALSE;
//STRIP001  }
//STRIP001
/*N*/   return TRUE;
/*N*/ }

/*N*/ void ScDocument::Clear()
/*N*/ {
/*N*/   for (USHORT i=0; i<=MAXTAB; i++)
/*N*/       if (pTab[i])
/*N*/       {
/*N*/           delete pTab[i];
/*N*/           pTab[i]=NULL;
/*N*/       }
/*N*/   delete pSelectionAttr;
/*N*/   pSelectionAttr = NULL;
/*N*/
/*N*/   if (pDrawLayer)
/*N*/       pDrawLayer->Clear();
/*N*/ }

/*N*/ BOOL ScDocument::HasControl( USHORT nTab, const Rectangle& rMMRect )
/*N*/ {
/*N*/   BOOL bFound = FALSE;
/*N*/
/*N*/   if (pDrawLayer)
/*N*/   {
/*N*/       SdrPage* pPage = pDrawLayer->GetPage(nTab);
/*N*/       DBG_ASSERT(pPage,"Page ?");
/*N*/       if (pPage)
/*N*/       {
/*N*/           SdrObjListIter aIter( *pPage, IM_DEEPNOGROUPS );
/*N*/           SdrObject* pObject = aIter.Next();
/*N*/           while (pObject && !bFound)
/*N*/           {
/*N*/               if (pObject->ISA(SdrUnoObj))
/*N*/               {
/*N*/                   Rectangle aObjRect = pObject->GetLogicRect();
/*N*/                   if ( aObjRect.IsOver( rMMRect ) )
/*N*/                       bFound = TRUE;
/*N*/               }
/*N*/
/*N*/               pObject = aIter.Next();
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return bFound;
/*N*/ }

//STRIP001 void ScDocument::InvalidateControls( Window* pWin, USHORT nTab, const Rectangle& rMMRect )
//STRIP001 {
//STRIP001  if (pDrawLayer)
//STRIP001  {
//STRIP001      SdrPage* pPage = pDrawLayer->GetPage(nTab);
//STRIP001      DBG_ASSERT(pPage,"Page ?");
//STRIP001      if (pPage)
//STRIP001      {
//STRIP001          SdrObjListIter aIter( *pPage, IM_DEEPNOGROUPS );
//STRIP001          SdrObject* pObject = aIter.Next();
//STRIP001          while (pObject)
//STRIP001          {
//STRIP001              if (pObject->ISA(SdrUnoObj))
//STRIP001              {
//STRIP001                  Rectangle aObjRect = pObject->GetLogicRect();
//STRIP001                  if ( aObjRect.IsOver( rMMRect ) )
//STRIP001                  {
//STRIP001                      //  Uno-Controls zeichnen sich immer komplett, ohne Ruecksicht
//STRIP001                      //  auf ClippingRegions. Darum muss das ganze Objekt neu gepainted
//STRIP001                      //  werden, damit die Selektion auf der Tabelle nicht uebermalt wird.
//STRIP001
//STRIP001                      //pWin->Invalidate( aObjRect.GetIntersection( rMMRect ) );
//STRIP001                      pWin->Invalidate( aObjRect );
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              pObject = aIter.Next();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*N*/ BOOL ScDocument::HasDetectiveObjects(USHORT nTab) const
/*N*/ {
/*N*/   //  looks for detective objects, annotations don't count
/*N*/   //  (used to adjust scale so detective objects hit their cells better)
/*N*/
/*N*/   BOOL bFound = FALSE;
/*N*/
/*N*/   if (pDrawLayer)
/*N*/   {
/*N*/       SdrPage* pPage = pDrawLayer->GetPage(nTab);
/*N*/       DBG_ASSERT(pPage,"Page ?");
/*N*/       if (pPage)
/*N*/       {
/*N*/           SdrObjListIter aIter( *pPage, IM_DEEPNOGROUPS );
/*N*/           SdrObject* pObject = aIter.Next();
/*N*/           while (pObject && !bFound)
/*N*/           {
/*N*/               // anything on the internal layer except captions (annotations)
/*N*/               if ( pObject->GetLayer() == SC_LAYER_INTERN && !pObject->ISA( SdrCaptionObj ) )
/*N*/                   bFound = TRUE;
/*N*/
/*N*/               pObject = aIter.Next();
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return bFound;
/*N*/ }

/*N*/ void ScDocument::UpdateFontCharSet()
/*N*/ {
/*N*/   //  In alten Versionen (bis incl. 4.0 ohne SP) wurden beim Austausch zwischen
/*N*/   //  Systemen die CharSets in den Font-Attributen nicht angepasst.
/*N*/   //  Das muss fuer Dokumente bis incl SP2 nun nachgeholt werden:
/*N*/   //  Alles, was nicht SYMBOL ist, wird auf den System-CharSet umgesetzt.
/*N*/   //  Bei neuen Dokumenten (Version SC_FONTCHARSET) sollte der CharSet stimmen.
/*N*/
/*N*/   BOOL bUpdateOld = ( nSrcVer < SC_FONTCHARSET );
/*N*/
/*N*/   CharSet eSysSet = gsl_getSystemTextEncoding();
/*N*/   if ( eSrcSet != eSysSet || bUpdateOld )
/*N*/   {
/*N*/       USHORT nCount,i;
/*N*/       SvxFontItem* pItem;
/*N*/
/*N*/       ScDocumentPool* pPool = xPoolHelper->GetDocPool();
/*N*/       nCount = pPool->GetItemCount(ATTR_FONT);
/*N*/       for (i=0; i<nCount; i++)
/*N*/       {
/*N*/           pItem = (SvxFontItem*)pPool->GetItem(ATTR_FONT, i);
/*N*/           if ( pItem && ( pItem->GetCharSet() == eSrcSet ||
/*N*/                           ( bUpdateOld && pItem->GetCharSet() != RTL_TEXTENCODING_SYMBOL ) ) )
/*N*/               pItem->GetCharSet() = eSysSet;
/*N*/       }
/*N*/
/*N*/       if ( pDrawLayer )
/*N*/       {
/*N*/           SfxItemPool& rDrawPool = pDrawLayer->GetItemPool();
/*N*/           nCount = rDrawPool.GetItemCount(EE_CHAR_FONTINFO);
/*N*/           for (i=0; i<nCount; i++)
/*N*/           {
/*N*/               pItem = (SvxFontItem*)rDrawPool.GetItem(EE_CHAR_FONTINFO, i);
/*N*/               if ( pItem && ( pItem->GetCharSet() == eSrcSet ||
/*N*/                               ( bUpdateOld && pItem->GetCharSet() != RTL_TEXTENCODING_SYMBOL ) ) )
/*?*/                   pItem->GetCharSet() = eSysSet;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void ScDocument::SetImportingXML( BOOL bVal )
/*N*/ {
/*N*/   bImportingXML = bVal;
/*N*/   if (pDrawLayer)
/*N*/       pDrawLayer->EnableAdjust(!bImportingXML);
/*N*/ }

/*N*/ vos::ORef<SvxForbiddenCharactersTable> ScDocument::GetForbiddenCharacters()
/*N*/ {
/*N*/   return xForbiddenCharacters;
/*N*/ }

/*N*/ void ScDocument::SetForbiddenCharacters( const vos::ORef<SvxForbiddenCharactersTable> xNew )
/*N*/ {
/*N*/   xForbiddenCharacters = xNew;
/*N*/   if ( pEditEngine )
/*?*/       pEditEngine->SetForbiddenCharsTable( xForbiddenCharacters );
/*N*/   if ( pDrawLayer )
/*N*/       pDrawLayer->SetForbiddenCharsTable( xForbiddenCharacters );
/*N*/ }

/*N*/ BOOL ScDocument::IsValidAsianCompression() const
/*N*/ {
/*N*/   return ( nAsianCompression != SC_ASIANCOMPRESSION_INVALID );
/*N*/ }

/*N*/ BYTE ScDocument::GetAsianCompression() const
/*N*/ {
/*N*/   if ( nAsianCompression == SC_ASIANCOMPRESSION_INVALID )
/*N*/       return 0;
/*N*/   else
/*N*/       return nAsianCompression;
/*N*/ }

/*N*/ void ScDocument::SetAsianCompression(BYTE nNew)
/*N*/ {
/*N*/   nAsianCompression = nNew;
/*N*/   if ( pEditEngine )
/*?*/       pEditEngine->SetAsianCompressionMode( nAsianCompression );
/*N*/   if ( pDrawLayer )
/*N*/       pDrawLayer->SetCharCompressType( nAsianCompression );
/*N*/ }

/*N*/ BOOL ScDocument::IsValidAsianKerning() const
/*N*/ {
/*N*/   return ( nAsianKerning != SC_ASIANKERNING_INVALID );
/*N*/ }

/*N*/ BOOL ScDocument::GetAsianKerning() const
/*N*/ {
/*N*/   if ( nAsianKerning == SC_ASIANKERNING_INVALID )
/*N*/       return FALSE;
/*N*/   else
/*N*/       return (BOOL)nAsianKerning;
/*N*/ }

/*N*/ void ScDocument::SetAsianKerning(BOOL bNew)
/*N*/ {
/*N*/   nAsianKerning = (BYTE)bNew;
/*N*/   if ( pEditEngine )
/*?*/       pEditEngine->SetKernAsianPunctuation( (BOOL)nAsianKerning );
/*N*/   if ( pDrawLayer )
/*N*/       pDrawLayer->SetKernAsianPunctuation( (BOOL)nAsianKerning );
/*N*/ }

}
