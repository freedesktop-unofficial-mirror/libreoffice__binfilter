/*************************************************************************
 *
 *  $RCSfile: sc_documen5.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 11:05:00 $
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
// auto strip #include "core_pch.hxx"
#endif

#pragma hdrstop

#pragma optimize("",off)
#pragma optimize("q",off) // p-code off

// INCLUDE ---------------------------------------------------------------

#include <bf_sfx2/objsh.hxx>
#include <bf_svx/svditer.hxx>
#include <bf_svx/svdoole2.hxx>
#include <bf_svx/svdpage.hxx>
#include <bf_sch/schdll.hxx>
#include <bf_sch/memchrt.hxx>
#include <bf_sch/schdll0.hxx>
// auto strip #include <so3/ipobj.hxx>

#ifndef SO2_DECL_SVINPLACEOBJECT_DEFINED
#define SO2_DECL_SVINPLACEOBJECT_DEFINED
SO2_DECL_REF(SvInPlaceObject)
#endif

#include "document.hxx"
#include "drwlayer.hxx"
#include "chartarr.hxx"
#include "chartlis.hxx"
#include "refupdat.hxx"
// auto strip #ifndef _GLOBNAME_HXX
// auto strip #include <tools/globname.hxx>
// auto strip #endif
namespace binfilter {

// -----------------------------------------------------------------------

        // Charts aus altem Dokument updaten

/*N*/ void ScDocument::UpdateAllCharts(BOOL bDoUpdate)
/*N*/ {
/*N*/   if (!pDrawLayer)
/*N*/       return;
/*N*/
/*N*/   USHORT nDataCount = pChartCollection->GetCount();
/*N*/   if ( !nDataCount )
/*N*/       return ;        // nothing to do
/*?*/
/*?*/   USHORT nPos;
/*?*/
/*?*/   for (USHORT nTab=0; nTab<=MAXTAB; nTab++)
/*?*/   {
/*?*/       if (pTab[nTab])
/*?*/       {
/*?*/           SdrPage* pPage = pDrawLayer->GetPage(nTab);
/*?*/           DBG_ASSERT(pPage,"Page ?");
/*?*/
/*?*/           ScRange aRange;
/*?*/           SdrObjListIter aIter( *pPage, IM_DEEPNOGROUPS );
/*?*/           SdrObject* pObject = aIter.Next();
/*?*/           while (pObject)
/*?*/           {
/*?*/               if ( pObject->GetObjIdentifier() == OBJ_OLE2 )
/*?*/               {
/*?*/                   SvInPlaceObjectRef aIPObj = ((SdrOle2Obj*)pObject)->GetObjRef();
/*?*/                   if (aIPObj.Is())
/*?*/                   {
/*?*/                       // String aIPName = aIPObj->GetName()->GetName();
/*?*/
/*?*/                       SvInfoObject* pInfoObj = pShell->Find( aIPObj );
/*?*/                       String aIPName;
/*?*/
/*?*/                       if ( pInfoObj )
/*?*/                           aIPName = pInfoObj->GetObjName();
/*?*/
/*?*/                       for (nPos=0; nPos<nDataCount; nPos++)
/*?*/                       {
/*?*/                           ScChartArray* pChartObj = (*pChartCollection)[nPos];
/*?*/                           if (pChartObj->GetName() == aIPName)
/*?*/                           {
/*?*/                               if (bDoUpdate)
/*?*/                               {
/*?*/                                   SchMemChart* pMemChart = pChartObj->CreateMemChart();
/*?*/                                   SchDLL::Update( aIPObj, pMemChart );
/*?*/                                   delete pMemChart;
/*?*/                               }
/*?*/                               else        // nur Position uebernehmen
/*?*/                               {
/*?*/                                   SchMemChart* pChartData = SchDLL::GetChartData(aIPObj);
/*?*/                                   if (pChartData)
/*?*/                                   {
/*?*/                                       pChartObj->SetExtraStrings(*pChartData);
/*?*/ //                                        aIPObj->SetModified( TRUE );
/*?*/                                   }
/*?*/                               }
/*?*/                               ScChartListener* pCL = new ScChartListener(
/*?*/                                   aIPName, this, pChartObj->GetRangeList() );
/*?*/                               pChartListenerCollection->Insert( pCL );
/*?*/                               pCL->StartListeningTo();
/*?*/                           }
/*?*/                       }
/*?*/                   }
/*?*/               }
/*?*/               pObject = aIter.Next();
/*?*/           }
/*?*/       }
/*?*/   }
/*?*/
/*?*/   pChartCollection->FreeAll();
/*N*/ }

//STRIP001 BOOL ScDocument::HasChartAtPoint( USHORT nTab, const Point& rPos, String* pName )
//STRIP001 {
//STRIP001  if (pDrawLayer && pTab[nTab])
//STRIP001  {
//STRIP001      SdrPage* pPage = pDrawLayer->GetPage(nTab);
//STRIP001      DBG_ASSERT(pPage,"Page ?");
//STRIP001
//STRIP001      SdrObjListIter aIter( *pPage, IM_DEEPNOGROUPS );
//STRIP001      SdrObject* pObject = aIter.Next();
//STRIP001      while (pObject)
//STRIP001      {
//STRIP001          if ( pObject->GetObjIdentifier() == OBJ_OLE2 &&
//STRIP001               pObject->GetBoundRect().IsInside(rPos) )
//STRIP001          {
//STRIP001                      // auch Chart-Objekte die nicht in der Collection sind
//STRIP001
//STRIP001              if (IsChart(pObject))
//STRIP001              {
//STRIP001                  if (pName)
//STRIP001                      *pName = ((SdrOle2Obj*)pObject)->GetPersistName();
//STRIP001                  return TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001          pObject = aIter.Next();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if (pName)
//STRIP001      pName->Erase();
//STRIP001  return FALSE;                   // nix gefunden
//STRIP001 }

/*N*/ void ScDocument::UpdateChartArea( const String& rChartName,
/*N*/           const ScRange& rNewArea, BOOL bColHeaders, BOOL bRowHeaders,
/*N*/           BOOL bAdd, Window* pWindow )
/*N*/ {
/*N*/   ScRangeListRef aRLR( new ScRangeList );
/*N*/   aRLR->Append( rNewArea );
/*N*/   UpdateChartArea( rChartName, aRLR, bColHeaders, bRowHeaders, bAdd, pWindow );
/*N*/ }
/*N*/
/*N*/ void ScDocument::UpdateChartArea( const String& rChartName,
/*N*/           const ScRangeListRef& rNewList, BOOL bColHeaders, BOOL bRowHeaders,
/*N*/           BOOL bAdd, Window* pWindow )
/*N*/ {
/*N*/   if (!pDrawLayer)
/*N*/       return;
/*N*/
/*N*/   for (USHORT nTab=0; nTab<=MAXTAB && pTab[nTab]; nTab++)
/*N*/   {
/*N*/       SdrPage* pPage = pDrawLayer->GetPage(nTab);
/*N*/       DBG_ASSERT(pPage,"Page ?");
/*N*/
/*N*/       SdrObjListIter aIter( *pPage, IM_DEEPNOGROUPS );
/*N*/       SdrObject* pObject = aIter.Next();
/*N*/       while (pObject)
/*N*/       {
/*N*/           if ( pObject->GetObjIdentifier() == OBJ_OLE2 &&
/*N*/                   ((SdrOle2Obj*)pObject)->GetPersistName() == rChartName )
/*N*/           {
/*N*/               SvInPlaceObjectRef aIPObj = ((SdrOle2Obj*)pObject)->GetObjRef();
/*N*/               if (aIPObj.Is())
/*N*/               {
/*N*/                   const SchMemChart* pChartData = SchDLL::GetChartData(aIPObj);
/*N*/                   if ( pChartData )
/*N*/                   {
/*N*/                       ScChartArray aArray( this, *pChartData );
/*N*/                       if ( bAdd )
/*N*/                       {
/*N*/                           // bei bAdd werden Header-Angaben ignoriert
/*N*/                           aArray.AddToRangeList( rNewList );
/*N*/                       }
/*N*/                       else
/*N*/                       {
/*N*/                           aArray.SetRangeList( rNewList );
/*N*/                           aArray.SetHeaders( bColHeaders, bRowHeaders );
/*N*/                       }
/*N*/                       pChartListenerCollection->ChangeListening(
/*N*/                           rChartName, aArray.GetRangeList() );
/*N*/
/*N*/
/*N*/                       SchMemChart* pMemChart = aArray.CreateMemChart();
/*N*/                       ScChartArray::CopySettings( *pMemChart, *pChartData );
/*N*/
/*N*/                       SchDLL::Update( aIPObj, pMemChart, pWindow );
/*N*/                       delete pMemChart;
/*N*/
/*N*/                       // Dies veranlaesst Chart zum sofortigen Update
/*N*/                       //SvData aEmpty;
/*N*/                       //aIPObj->SendDataChanged( aEmpty );
/*N*/                       aIPObj->SendViewChanged();
/*N*/                       pObject->SendRepaintBroadcast();
/*N*/
/*N*/                       return;         // nicht weitersuchen
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/           pObject = aIter.Next();
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void ScDocument::UpdateChart( const String& rChartName, Window* pWindow )
/*N*/ {
/*N*/   if (!pDrawLayer || bInDtorClear)
/*N*/       return;
/*N*/
/*N*/   for (USHORT nTab=0; nTab<=MAXTAB && pTab[nTab]; nTab++)
/*N*/   {
/*N*/       SdrPage* pPage = pDrawLayer->GetPage(nTab);
/*N*/       DBG_ASSERT(pPage,"Page ?");
/*N*/
/*N*/       SdrObjListIter aIter( *pPage, IM_DEEPNOGROUPS );
/*N*/       SdrObject* pObject = aIter.Next();
/*N*/       while (pObject)
/*N*/       {
/*N*/           if ( pObject->GetObjIdentifier() == OBJ_OLE2 &&
/*N*/                   ((SdrOle2Obj*)pObject)->GetPersistName() == rChartName )
/*N*/           {
/*N*/               SvInPlaceObjectRef aIPObj = ((SdrOle2Obj*)pObject)->GetObjRef();
/*N*/               if (aIPObj.Is())
/*N*/               {
/*N*/                   const SchMemChart* pChartData = SchDLL::GetChartData(aIPObj);
/*N*/                   if ( pChartData )
/*N*/                   {
/*N*/                       ScChartArray aArray( this, *pChartData );
/*N*/
/*N*/                       SchMemChart* pMemChart = aArray.CreateMemChart();
/*N*/                       ScChartArray::CopySettings( *pMemChart, *pChartData );
/*N*/
/*N*/                       //  #57655# Chart-Update ohne geaenderte Einstellungen (MemChart)
/*N*/                       //  soll das Dokument nicht auf modified setzen (z.B. in frisch
/*N*/                       //  geladenem Dokument durch initiales Recalc)
/*N*/
/*N*/                       //  #72576# disable SetModified for readonly documents only
/*N*/
/*N*/                       BOOL bEnabled = ( ((pShell && pShell->IsReadOnly()) ||
/*N*/                                           IsImportingXML()) &&
/*N*/                                           aIPObj->IsEnableSetModified() );
/*N*/                       if (bEnabled)
/*N*/                           aIPObj->EnableSetModified(FALSE);
/*N*/
/*N*/                       SchDLL::Update( aIPObj, pMemChart, pWindow );
/*N*/                       delete pMemChart;
/*N*/
/*N*/                       // Dies veranlaesst Chart zum sofortigen Update
/*N*/                       //SvData aEmpty;
/*N*/                       //aIPObj->SendDataChanged( aEmpty );
/*N*/                       aIPObj->SendViewChanged();
/*N*/                       pObject->SendRepaintBroadcast();
/*N*/
/*N*/                       if (bEnabled)
/*N*/                           aIPObj->EnableSetModified(TRUE);
/*N*/
/*N*/                       return;         // nicht weitersuchen
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/           pObject = aIter.Next();
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void ScDocument::UpdateChartRef( UpdateRefMode eUpdateRefMode,
/*N*/                                   USHORT nCol1, USHORT nRow1, USHORT nTab1,
/*N*/                                   USHORT nCol2, USHORT nRow2, USHORT nTab2,
/*N*/                                   short nDx, short nDy, short nDz )
/*N*/ {
/*N*/   if (!pDrawLayer)
/*N*/       return;
/*N*/
/*N*/   USHORT nChartCount = pChartListenerCollection->GetCount();
/*N*/   for ( USHORT nIndex = 0; nIndex < nChartCount; nIndex++ )
/*N*/   {
/*?*/       ScChartListener* pChartListener =
/*?*/           (ScChartListener*) (pChartListenerCollection->At(nIndex));
/*?*/       ScRangeListRef aRLR( pChartListener->GetRangeList() );
/*?*/       ScRangeListRef aNewRLR( new ScRangeList );
/*?*/       BOOL bChanged = FALSE;
/*?*/       BOOL bDataChanged = FALSE;
/*?*/       for ( ScRangePtr pR = aRLR->First(); pR; pR = aRLR->Next() )
/*?*/       {
/*?*/           USHORT theCol1 = pR->aStart.Col();
/*?*/           USHORT theRow1 = pR->aStart.Row();
/*?*/           USHORT theTab1 = pR->aStart.Tab();
/*?*/           USHORT theCol2 = pR->aEnd.Col();
/*?*/           USHORT theRow2 = pR->aEnd.Row();
/*?*/           USHORT theTab2 = pR->aEnd.Tab();
/*?*/           ScRefUpdateRes eRes = ScRefUpdate::Update(
/*?*/               this, eUpdateRefMode,
/*?*/               nCol1,nRow1,nTab1, nCol2,nRow2,nTab2,
/*?*/               nDx,nDy,nDz,
/*?*/               theCol1,theRow1,theTab1,
/*?*/               theCol2,theRow2,theTab2 );
/*?*/           if ( eRes != UR_NOTHING )
/*?*/           {
/*?*/               bChanged = TRUE;
/*?*/               aNewRLR->Append( ScRange(
/*?*/                   theCol1, theRow1, theTab1,
/*?*/                   theCol2, theRow2, theTab2 ));
/*?*/               if ( eUpdateRefMode == URM_INSDEL
/*?*/                   && !bDataChanged
/*?*/                   && (eRes == UR_INVALID ||
/*?*/                       ((pR->aEnd.Col() - pR->aStart.Col()
/*?*/                       != theCol2 - theCol1)
/*?*/                   || (pR->aEnd.Row() - pR->aStart.Row()
/*?*/                       != theRow2 - theRow1)
/*?*/                   || (pR->aEnd.Tab() - pR->aStart.Tab()
/*?*/                       != theTab2 - theTab1))) )
/*?*/               {
/*?*/                   bDataChanged = TRUE;
/*?*/               }
/*?*/           }
/*?*/           else
/*?*/               aNewRLR->Append( *pR );
/*?*/       }
/*?*/       if ( bChanged )
/*?*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if ( nDz != 0 )
//STRIP001 /*?*/            {   // #81844# sheet to be deleted or inserted or moved
//STRIP001 /*?*/                // => no valid sheet names for references right now
//STRIP001 /*?*/                pChartListener->ChangeListening( aNewRLR, bDataChanged );
//STRIP001 /*?*/                pChartListener->ScheduleSeriesRanges();
//STRIP001 /*?*/            }
//STRIP001 /*?*/            else
//STRIP001 /*?*/            {
//STRIP001 /*?*/                SetChartRangeList( pChartListener->GetString(), aNewRLR );
//STRIP001 /*?*/                pChartListener->ChangeListening( aNewRLR, bDataChanged );
//STRIP001 /*?*/            }
/*?*/       }
/*N*/   }
/*N*/ }


//STRIP001 void ScDocument::SetChartRangeList( const String& rChartName,
//STRIP001          const ScRangeListRef& rNewRangeListRef )
//STRIP001 {
//STRIP001  SchMemChart* pChartData = FindChartData( rChartName, TRUE );
//STRIP001  if ( pChartData )
//STRIP001  {
//STRIP001      ScChartArray aArray( this, *pChartData );
//STRIP001      aArray.SetRangeList( rNewRangeListRef );
//STRIP001      aArray.SetExtraStrings( *pChartData );
//STRIP001  }
//STRIP001 }


/*N*/ BOOL ScDocument::HasData( USHORT nCol, USHORT nRow, USHORT nTab )
/*N*/ {
/*N*/   if (pTab[nTab])
/*N*/       return pTab[nTab]->HasData( nCol, nRow );
/*N*/   else
/*N*/       return FALSE;
/*N*/ }

/*N*/ SchMemChart* ScDocument::FindChartData(const String& rName, BOOL bForModify)
/*N*/ {
/*N*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if (!pDrawLayer)
//STRIP001      return NULL;
//STRIP001
//STRIP001  //  die Seiten hier vom Draw-Layer nehmen,
//STRIP001  //  weil sie evtl. nicht mit den Tabellen uebereinstimmen
//STRIP001  //  (z.B. Redo von Tabelle loeschen, Draw-Redo passiert vor DeleteTab).
//STRIP001
//STRIP001  USHORT nCount = pDrawLayer->GetPageCount();
//STRIP001  for (USHORT nTab=0; nTab<nCount; nTab++)
//STRIP001  {
//STRIP001      SdrPage* pPage = pDrawLayer->GetPage(nTab);
//STRIP001      DBG_ASSERT(pPage,"Page ?");
//STRIP001
//STRIP001      SdrObjListIter aIter( *pPage, IM_DEEPNOGROUPS );
//STRIP001      SdrObject* pObject = aIter.Next();
//STRIP001      while (pObject)
//STRIP001      {
//STRIP001          if ( pObject->GetObjIdentifier() == OBJ_OLE2 &&
//STRIP001                  ((SdrOle2Obj*)pObject)->GetPersistName() == rName )
//STRIP001          {
//STRIP001              SvInPlaceObjectRef aIPObj = ((SdrOle2Obj*)pObject)->GetObjRef();
//STRIP001              if ( aIPObj.Is() )
//STRIP001              {
//STRIP001                  if (bForModify)
//STRIP001                      aIPObj->SetModified( TRUE );
//STRIP001                  return SchDLL::GetChartData( aIPObj );
//STRIP001              }
//STRIP001          }
//STRIP001          pObject = aIter.Next();
//STRIP001      }
//STRIP001  }
//STRIP001
/*N*/   return NULL;                            // nix
/*N*/ }


/*N*/ BOOL lcl_StringInCollection( const StrCollection* pColl, const String& rStr )
/*N*/ {
/*N*/   if ( !pColl )
/*N*/       return FALSE;
/*N*/
/*N*/   StrData aData( rStr );
/*N*/   USHORT nDummy;
/*N*/   return pColl->Search( &aData, nDummy );
/*N*/ }

/*N*/ void ScDocument::UpdateChartListenerCollection()
/*N*/ {
/*N*/   bChartListenerCollectionNeedsUpdate = FALSE;
/*N*/   if (!pDrawLayer)
/*N*/       return;
/*N*/   else
/*N*/   {
/*N*/       ScRange aRange;
/*N*/       // Range fuer Suche unwichtig
/*N*/       ScChartListener aCLSearcher( EMPTY_STRING, this, aRange );
/*N*/       for (USHORT nTab=0; nTab<=MAXTAB; nTab++)
/*N*/       {
/*N*/           if (pTab[nTab])
/*N*/           {
/*N*/               SdrPage* pPage = pDrawLayer->GetPage(nTab);
/*N*/               DBG_ASSERT(pPage,"Page ?");
/*N*/
/*N*/               SdrObjListIter aIter( *pPage, IM_DEEPNOGROUPS );
/*N*/               SdrObject* pObject = aIter.Next();
/*N*/               while (pObject)
/*N*/               {
/*N*/                   if ( pObject->GetObjIdentifier() == OBJ_OLE2 )
/*N*/                   {
/*N*/                       String aObjName = ((SdrOle2Obj*)pObject)->GetPersistName();
/*N*/                       aCLSearcher.SetString( aObjName );
/*N*/                       USHORT nIndex;
/*N*/                       if ( pChartListenerCollection->Search( &aCLSearcher, nIndex ) )
/*N*/                       {
/*N*/                           ((ScChartListener*) (pChartListenerCollection->
/*N*/                               At( nIndex )))->SetUsed( TRUE );
/*N*/                       }
/*N*/                       else if ( lcl_StringInCollection( pOtherObjects, aObjName ) )
/*N*/                       {
/*N*/                           // non-chart OLE object -> don't touch
/*N*/                       }
/*N*/                       else
/*N*/                       {
/*N*/                           //  SchDLL::GetChartData always loads the chart dll,
/*N*/                           //  so SchModuleDummy::HasID must be tested before
/*N*/
/*N*/                           BOOL bIsChart = FALSE;
/*N*/                           USHORT nId;
/*N*/
/*N*/                             //  Ask the SvPersist for the InfoObject to find out
/*N*/                             //  whether it is a Chart. The old way with GetObjRef
/*N*/                             //  loads the object which takes too much unnecessary
/*N*/                             //  time
/*N*/                             SvInfoObject* pInfoObj = pShell->Find(aObjName);
/*N*/                             DBG_ASSERT(pInfoObj, "Why isn't here a SvInfoObject?");
/*N*/                           if ( pInfoObj &&
/*N*/                                ((nId = SchModuleDummy::HasID(pInfoObj->GetClassName()) ) != 0) )
/*N*/                           {
/*N*/                                 SvInPlaceObjectRef aIPObj = ((SdrOle2Obj*)pObject)->GetObjRef();
/*N*/                                 DBG_ASSERT(aIPObj.Is(), "no SvInPlaceObject given");
/*N*/                                 if (aIPObj.Is())
/*N*/                                 {
/*N*/                                   BOOL bSO6 = (nId >= SOFFICE_FILEFORMAT_60);
/*N*/                                   SchMemChart* pChartData = SchDLL::GetChartData(aIPObj);
/*N*/                                   // #84359# manually inserted OLE object
/*N*/                                   // => no listener at ScAddress(0,0,0)
/*N*/                                   // >=SO6: if no series set
/*N*/                                   // < SO6: if no SomeData set
/*N*/                                   if ( pChartData &&
/*N*/                                       ((!bSO6 && pChartData->SomeData1().Len()) ||
/*N*/                                         (bSO6 && pChartData->GetChartRange().maRanges.size())) )
/*N*/                                   {
/*N*/                                         if ( PastingDrawFromOtherDoc() )
/*N*/                                         {
/*?*/                                             // #89247# Remove series ranges from
/*?*/                                             // charts not originating from the
/*?*/                                             // same document, they become true OLE
/*?*/                                             // objects.
/*?*/                                             pChartData->SomeData1().Erase();
/*?*/                                             pChartData->SomeData2().Erase();
/*?*/                                             pChartData->SomeData3().Erase();
/*?*/                                             pChartData->SomeData4().Erase();
/*?*/                                             SchChartRange aChartRange;
/*?*/                                             pChartData->SetChartRange( aChartRange );
/*?*/                                             pChartData->SetReadOnly( FALSE );
/*?*/                                             SchDLL::Update( aIPObj, pChartData );
/*N*/                                         }
/*N*/                                         else
/*N*/                                         {
/*N*/                                             bIsChart = TRUE;
/*N*/
/*N*/                                             ScChartArray aArray( this, *pChartData );
/*N*/                                             ScChartListener* pCL = new ScChartListener(
/*N*/                                                 aObjName,
/*N*/                                                 this, aArray.GetRangeList() );
/*N*/                                             pChartListenerCollection->Insert( pCL );
/*N*/                                             pCL->StartListeningTo();
/*N*/                                             pCL->SetUsed( TRUE );
/*N*/
/*N*/                                             BOOL bForceSave = FALSE;
/*N*/
/*N*/                                             //  Set ReadOnly flag at MemChart, so Chart knows
/*N*/                                             //  about the external data in a freshly loaded document.
/*N*/                                             //  #73642# only if the chart really has external data
/*N*/                                             if ( aArray.IsValid() )
/*N*/                                             {
/*N*/                                                 pChartData->SetReadOnly( TRUE );
/*N*/
/*N*/                                                 //  #81525# re-create series ranges from old extra string
/*N*/                                                 //  if not set (after loading)
/*N*/                                                 if ( !bSO6 )
/*N*/                                                 {
/*N*/                                                     String aOldData3 = pChartData->SomeData3();
/*N*/                                                     aArray.SetExtraStrings( *pChartData );
/*N*/                                                     if ( aOldData3 != pChartData->SomeData3() )
/*N*/                                                     {
/*N*/                                                         //  #96148# ChartRange isn't saved in binary format anyway,
/*N*/                                                         //  but SomeData3 (sheet names) has to survive swapping out,
/*N*/                                                         //  or the chart can't be saved to 6.0 format.
/*N*/
/*N*/                                                         bForceSave = TRUE;
/*N*/                                                     }
/*N*/                                                 }
/*N*/                                             }
/*N*/
/*N*/     #if 1
/*N*/     // #74046# initially loaded charts need the number formatter standard precision
/*N*/                                             BOOL bEnabled = aIPObj->IsEnableSetModified();
/*N*/                                             if (bEnabled)
/*N*/                                                 aIPObj->EnableSetModified(FALSE);
/*N*/                                             pChartData->SetNumberFormatter( GetFormatTable() );
/*N*/                                             SchDLL::Update( aIPObj, pChartData );
/*N*/                                             //! pChartData got deleted, don't use it anymore
/*N*/                                             if (bEnabled)
/*N*/                                                 aIPObj->EnableSetModified(TRUE);
/*N*/     #ifndef PRODUCT
/*N*/     //                                          static BOOL bShown74046 = 0;
/*N*/     //                                          if ( !bShown74046 && SOFFICE_FILEFORMAT_NOW > SOFFICE_FILEFORMAT_50 )
/*N*/     //                                          {
/*N*/     //                                              bShown74046 = 1;
/*N*/     //                                              DBG_ERRORFILE( "on incompatible file format save number formatter standard precision in chart" );
/*N*/     //                                          }
/*N*/     #endif
/*N*/     #endif
/*N*/                                             if ( bForceSave )
/*N*/                                             {
/*N*/                                                 //  #96148# after adjusting the data that wasn't in the MemChart
/*N*/                                                 //  in a binary file (ChartRange etc.), the chart object has to be
/*N*/                                                 //  saved (within the open document, in transacted mode, so the
/*N*/                                                 //  original file isn't changed yet), so the changes are still
/*N*/                                                 //  there after the chart is swapped out and loaded again.
/*N*/                                                 //  The chart can't get the modified flag set, because then it
/*N*/                                                 //  wouldn't be swapped out at all. So it has to be saved manually
/*N*/                                                 //  here (which is unnecessary if the chart is modified before it
/*N*/                                                 //  it swapped out). At this point, we don't have to care about
/*N*/                                                 //  contents being lost when saving in old binary format, because
/*N*/                                                 //  the chart was just loaded from that format.
/*N*/
/*N*/                                                 aIPObj->DoSave();
/*N*/                                                 aIPObj->DoSaveCompleted();
/*N*/                                             }
/*N*/                                         }
/*N*/                                   }
/*N*/                                 }
/*N*/                           }
/*N*/                           if (!bIsChart)
/*N*/                           {
/*N*/                               //  put into list of other ole objects, so the object doesn't have to
/*N*/                               //  be swapped in the next time UpdateChartListenerCollection is called
/*N*/                               //! remove names when objects are no longer there?
/*N*/                               //  (object names aren't used again before reloading the document)
/*N*/
/*N*/                               if (!pOtherObjects)
/*N*/                                   pOtherObjects = new StrCollection;
/*N*/                               pOtherObjects->Insert( new StrData( aObjName ) );
/*N*/                           }
/*N*/                       }
/*N*/                   }
/*N*/                   pObject = aIter.Next();
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/       // alle nicht auf SetUsed gesetzten loeschen
/*N*/       pChartListenerCollection->FreeUnused();
/*N*/   }
/*N*/ }

/*N*/ void ScDocument::AddOLEObjectToCollection(const String& rName)
/*N*/ {
/*N*/   if (!pOtherObjects)
/*N*/       pOtherObjects = new StrCollection;
/*N*/   pOtherObjects->Insert( new StrData( rName ) );
/*N*/ }



}
