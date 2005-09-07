/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_pivot2.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 16:51:33 $
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

#pragma optimize("",off)
#pragma optimize("q",off) // p-code off

// INCLUDE ---------------------------------------------------------------

#include "scitems.hxx"
// auto strip #include <bf_svx/boxitem.hxx>
// auto strip #include <bf_svx/wghtitem.hxx>
// auto strip #include <bf_svx/algitem.hxx>
#ifndef _UNOTOOLS_TRANSLITERATIONWRAPPER_HXX
#include <unotools/transliterationwrapper.hxx>
#endif

#include "globstr.hrc"
// auto strip #include "subtotal.hxx"
#include "rangeutl.hxx"
// auto strip #include "attrib.hxx"
// auto strip #include "patattr.hxx"
// auto strip #include "docpool.hxx"
// auto strip #include "document.hxx"
// auto strip #include "userlist.hxx"
#include "pivot.hxx"
#include "rechead.hxx"
// auto strip #include "compiler.hxx"                           // fuer errNoValue
#include "refupdat.hxx"
// auto strip #include "stlpool.hxx"
#include "stlsheet.hxx"
namespace binfilter {


// STATIC DATA -----------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Hilfsmethoden von ScPivot
//--------------------------------------------------------------------------------------------------

//STRIP001 void ScPivot::SetFrame(USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2, USHORT nWidth)
//STRIP001 {
//STRIP001  if (pDoc->pTab[nDestTab])
//STRIP001  {
//STRIP001      SvxBorderLine aLine;
//STRIP001      aLine.SetOutWidth(nWidth);
//STRIP001      SvxBoxItem aBox;
//STRIP001      aBox.SetLine(&aLine, BOX_LINE_LEFT);
//STRIP001      aBox.SetLine(&aLine, BOX_LINE_TOP);
//STRIP001      aBox.SetLine(&aLine, BOX_LINE_RIGHT);
//STRIP001      aBox.SetLine(&aLine, BOX_LINE_BOTTOM);
//STRIP001      SvxBoxInfoItem aBoxInfo;
//STRIP001      aBoxInfo.SetValid(VALID_HORI,FALSE);
//STRIP001      aBoxInfo.SetValid(VALID_VERT,FALSE);
//STRIP001      aBoxInfo.SetValid(VALID_DISTANCE,FALSE);
//STRIP001      pDoc->pTab[nDestTab]->ApplyBlockFrame(&aBox, &aBoxInfo, nCol1, nRow1, nCol2, nRow2);
//STRIP001  }
//STRIP001 }

//STRIP001 void ScPivot::SetFrameHor(USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2)
//STRIP001 {
//STRIP001  if (pDoc->pTab[nDestTab])
//STRIP001  {
//STRIP001      SvxBorderLine aLine;
//STRIP001      aLine.SetOutWidth(20);
//STRIP001      SvxBoxItem aBox;
//STRIP001      aBox.SetLine(&aLine, BOX_LINE_LEFT);
//STRIP001      aBox.SetLine(&aLine, BOX_LINE_TOP);
//STRIP001      aBox.SetLine(&aLine, BOX_LINE_RIGHT);
//STRIP001      aBox.SetLine(&aLine, BOX_LINE_BOTTOM);
//STRIP001      SvxBoxInfoItem aBoxInfo;
//STRIP001      aBoxInfo.SetValid(VALID_VERT,FALSE);
//STRIP001      aBoxInfo.SetValid(VALID_DISTANCE,FALSE);
//STRIP001      aBoxInfo.SetLine(&aLine, BOXINFO_LINE_HORI);
//STRIP001      pDoc->pTab[nDestTab]->ApplyBlockFrame(&aBox, &aBoxInfo, nCol1, nRow1, nCol2, nRow2);
//STRIP001  }
//STRIP001 }

//STRIP001 void ScPivot::SetFrameVer(USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2)
//STRIP001 {
//STRIP001  if (pDoc->pTab[nDestTab])
//STRIP001  {
//STRIP001      SvxBorderLine aLine;
//STRIP001      aLine.SetOutWidth(20);
//STRIP001      SvxBoxItem aBox;
//STRIP001      aBox.SetLine(&aLine, BOX_LINE_LEFT);
//STRIP001      aBox.SetLine(&aLine, BOX_LINE_TOP);
//STRIP001      aBox.SetLine(&aLine, BOX_LINE_RIGHT);
//STRIP001      aBox.SetLine(&aLine, BOX_LINE_BOTTOM);
//STRIP001      SvxBoxInfoItem aBoxInfo;
//STRIP001      aBoxInfo.SetValid(VALID_HORI,FALSE);
//STRIP001      aBoxInfo.SetValid(VALID_DISTANCE,FALSE);
//STRIP001      aBoxInfo.SetLine(&aLine, BOXINFO_LINE_VERT);
//STRIP001      pDoc->pTab[nDestTab]->ApplyBlockFrame(&aBox, &aBoxInfo, nCol1, nRow1, nCol2, nRow2);
//STRIP001  }
//STRIP001 }

//STRIP001 void ScPivot::SetFontBold(USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2)
//STRIP001 {
//STRIP001  if (pDoc->pTab[nDestTab])
//STRIP001  {
//STRIP001      ScPatternAttr aPattern( pDoc->GetPool() );
//STRIP001      aPattern.GetItemSet().Put( SvxWeightItem( WEIGHT_BOLD ) );
//STRIP001      pDoc->pTab[nDestTab]->ApplyPatternArea(nCol1, nRow1, nCol2, nRow2, aPattern);
//STRIP001  }
//STRIP001 }

//STRIP001 void ScPivot::SetJustifyLeft(USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2)
//STRIP001 {
//STRIP001  if (pDoc->pTab[nDestTab])
//STRIP001  {
//STRIP001      ScPatternAttr aPattern( pDoc->GetPool() );
//STRIP001      aPattern.GetItemSet().Put( SvxHorJustifyItem( SVX_HOR_JUSTIFY_LEFT ) );
//STRIP001      pDoc->pTab[nDestTab]->ApplyPatternArea(nCol1, nRow1, nCol2, nRow2, aPattern);
//STRIP001  }
//STRIP001 }

//STRIP001 void ScPivot::SetJustifyRight(USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2)
//STRIP001 {
//STRIP001  if (pDoc->pTab[nDestTab])
//STRIP001  {
//STRIP001      ScPatternAttr aPattern( pDoc->GetPool() );
//STRIP001      aPattern.GetItemSet().Put( SvxHorJustifyItem( SVX_HOR_JUSTIFY_RIGHT ) );
//STRIP001      pDoc->pTab[nDestTab]->ApplyPatternArea(nCol1, nRow1, nCol2, nRow2, aPattern);
//STRIP001  }
//STRIP001 }

//STRIP001 void ScPivot::SetButton(USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2)
//STRIP001 {
//STRIP001  if (pDoc->pTab[nDestTab])
//STRIP001  {
//STRIP001      ScPatternAttr aPattern( pDoc->GetPool() );
//STRIP001      aPattern.GetItemSet().Put( ScMergeFlagAttr(SC_MF_BUTTON) );
//STRIP001      pDoc->pTab[nDestTab]->ApplyPatternArea(nCol1, nRow1, nCol2, nRow2, aPattern);
//STRIP001  }
//STRIP001 }

//STRIP001 void ScPivot::SetStyle(USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2, USHORT nId)
//STRIP001 {
//STRIP001  if ( nCol1 > nCol2 || nRow1 > nRow2 )
//STRIP001      return;                                 //  Falls Bereiche leer sind
//STRIP001
//STRIP001  USHORT nStringId = 0;
//STRIP001  switch (nId)
//STRIP001  {
//STRIP001      case PIVOT_STYLE_INNER:     nStringId = STR_PIVOT_STYLE_INNER;      break;
//STRIP001      case PIVOT_STYLE_RESULT:    nStringId = STR_PIVOT_STYLE_RESULT;     break;
//STRIP001      case PIVOT_STYLE_CATEGORY:  nStringId = STR_PIVOT_STYLE_CATEGORY;   break;
//STRIP001      case PIVOT_STYLE_TITLE:     nStringId = STR_PIVOT_STYLE_TITLE;      break;
//STRIP001      case PIVOT_STYLE_FIELDNAME: nStringId = STR_PIVOT_STYLE_FIELDNAME;  break;
//STRIP001      case PIVOT_STYLE_TOP:       nStringId = STR_PIVOT_STYLE_TOP;        break;
//STRIP001      default:
//STRIP001          DBG_ERROR("falsche ID bei ScPivot::SetStyle");
//STRIP001          return;
//STRIP001  }
//STRIP001  String aStyleName = ScGlobal::GetRscString(nStringId);
//STRIP001
//STRIP001  ScStyleSheetPool* pStlPool = pDoc->GetStyleSheetPool();
//STRIP001  ScStyleSheet* pStyle = (ScStyleSheet*) pStlPool->Find( aStyleName, SFX_STYLE_FAMILY_PARA );
//STRIP001  if (!pStyle)
//STRIP001  {
//STRIP001      //  neu anlegen
//STRIP001
//STRIP001      pStyle = (ScStyleSheet*) &pStlPool->Make( aStyleName, SFX_STYLE_FAMILY_PARA,
//STRIP001                                                  SFXSTYLEBIT_USERDEF );
//STRIP001      pStyle->SetParent( ScGlobal::GetRscString(STR_STYLENAME_STANDARD) );
//STRIP001      SfxItemSet& rSet = pStyle->GetItemSet();
//STRIP001      if ( nId==PIVOT_STYLE_RESULT || nId==PIVOT_STYLE_TITLE )
//STRIP001          rSet.Put( SvxWeightItem( WEIGHT_BOLD ) );
//STRIP001      if ( nId==PIVOT_STYLE_CATEGORY || nId==PIVOT_STYLE_TITLE )
//STRIP001          rSet.Put( SvxHorJustifyItem( SVX_HOR_JUSTIFY_LEFT ) );
//STRIP001  }
//STRIP001
//STRIP001  pDoc->pTab[nDestTab]->ApplyStyleArea( nCol1, nRow1, nCol2, nRow2, *pStyle );
//STRIP001 }

//STRIP001 void ScPivot::SetValue(USHORT nCol, USHORT nRow, const SubTotal& rTotal, USHORT nFunc)
//STRIP001 {
//STRIP001  if ( rTotal.Valid( nFunc ) == 1)
//STRIP001      pDoc->SetValue(nCol, nRow, nDestTab, rTotal.Result( nFunc ));
//STRIP001  else if ( rTotal.Valid( nFunc ) == 0)
//STRIP001      pDoc->SetError(nCol, nRow, nDestTab, errNoValue);
//STRIP001 }

//--------------------------------------------------------------------------------------------------

/*N*/ void ScPivot::GetParam( ScPivotParam& rParam, ScQueryParam& rQuery, ScArea& rSrcArea ) const
/*N*/ {
/*N*/   short nCount;
/*N*/   USHORT nDummy;
/*N*/   GetDestArea( rParam.nCol,rParam.nRow, nDummy,nDummy, rParam.nTab );
/*N*/
/*N*/   // Row und Col in der Bedeutung vertauscht:
/*N*/   GetRowFields( rParam.aColArr, nCount );
/*N*/   rParam.nColCount = (USHORT) nCount;
/*N*/   GetColFields( rParam.aRowArr, nCount );
/*N*/   rParam.nRowCount = (USHORT) nCount;
/*N*/   GetDataFields( rParam.aDataArr, nCount );
/*N*/   rParam.nDataCount = (USHORT) nCount;
/*N*/
/*N*/   rParam.bIgnoreEmptyRows  = GetIgnoreEmpty();
/*N*/   rParam.bDetectCategories = GetDetectCat();
/*N*/   rParam.bMakeTotalCol     = GetMakeTotalCol();
/*N*/   rParam.bMakeTotalRow     = GetMakeTotalRow();
/*N*/
/*N*/   GetQuery(rQuery);
/*N*/   GetSrcArea( rSrcArea.nColStart, rSrcArea.nRowStart,
/*N*/                       rSrcArea.nColEnd, rSrcArea.nRowEnd, rSrcArea.nTab );
/*N*/ }

/*N*/ void ScPivot::SetParam( const ScPivotParam& rParam, const ScQueryParam& rQuery,
/*N*/                           const ScArea& rSrcArea )
/*N*/ {
/*N*/   SetQuery( rQuery );
/*N*/   SetHeader( TRUE );
/*N*/   SetSrcArea( rSrcArea.nColStart, rSrcArea.nRowStart,
/*N*/                         rSrcArea.nColEnd, rSrcArea.nRowEnd, rSrcArea.nTab );
/*N*/   SetDestPos( rParam.nCol, rParam.nRow, rParam.nTab );
/*N*/   SetIgnoreEmpty( rParam.bIgnoreEmptyRows );
/*N*/   SetDetectCat( rParam.bDetectCategories );
/*N*/   SetMakeTotalCol( rParam.bMakeTotalCol );
/*N*/   SetMakeTotalRow( rParam.bMakeTotalRow );
/*N*/
/*N*/   // Row und Col in der Bedeutung vertauscht:
/*N*/   SetRowFields( rParam.aColArr, rParam.nColCount );
/*N*/   SetColFields( rParam.aRowArr, rParam.nRowCount );
/*N*/   SetDataFields( rParam.aDataArr, rParam.nDataCount );
/*N*/ }

/*N*/ DataObject*   ScPivot::Clone() const
/*N*/ {
/*N*/   return new ScPivot(*this);
/*N*/ }

//--------------------------------------------------------------------------------------------------
// PivotStrCollection
//--------------------------------------------------------------------------------------------------

//STRIP001 DataObject*  PivotStrCollection::Clone() const
//STRIP001 {
//STRIP001  return new PivotStrCollection(*this);
//STRIP001 }

/*N*/ short PivotStrCollection::Compare(DataObject* pKey1, DataObject* pKey2) const
/*N*/ {
/*N*/   DBG_ASSERT(pKey1&&pKey2,"0-Zeiger bei PivotStrCollection::Compare");
/*N*/
/*N*/   short nResult = 0;
/*N*/
/*N*/   TypedStrData& rData1 = (TypedStrData&)*pKey1;
/*N*/   TypedStrData& rData2 = (TypedStrData&)*pKey2;
/*N*/
/*N*/   if ( rData1.nStrType > rData2.nStrType )
/*N*/       nResult = 1;
/*N*/   else if ( rData1.nStrType < rData2.nStrType )
/*N*/       nResult = -1;
/*N*/   else if ( !rData1.nStrType /* && !rData2.nStrType */ )
/*N*/   {
/*?*/       // Zahlen vergleichen:
/*?*/
/*?*/       if ( rData1.nValue == rData2.nValue )
/*?*/           nResult = 0;
/*?*/       else if ( rData1.nValue < rData2.nValue )
/*?*/           nResult = -1;
/*?*/       else
/*?*/           nResult = 1;
/*N*/   }
/*N*/   else /* if ( rData1.nStrType && rData2.nStrType ) */
/*N*/   {
/*N*/       // Strings vergleichen:
/*N*/
/*N*/       if (pUserData)
/*?*/       {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     nResult = pUserData->ICompare(rData1.aStrValue, rData2.aStrValue);
/*N*/       else
/*N*/       {
/*N*/             nResult = (short) ScGlobal::pTransliteration->compareString(
/*N*/               rData1.aStrValue, rData2.aStrValue );
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return nResult;
/*N*/ }

/*N*/ short PivotStrCollection::GetIndex(TypedStrData* pData) const
/*N*/ {
/*N*/   USHORT nIndex = 0;
/*N*/   if (!Search(pData, nIndex))
/*N*/       nIndex = 0;
/*N*/   return (short)nIndex;
/*N*/ }

//--------------------------------------------------------------------------------------------------
// PivotCollection
//--------------------------------------------------------------------------------------------------

/*N*/ String ScPivotCollection::CreateNewName( USHORT nMin ) const
/*N*/ {
/*N*/     String aBase( RTL_CONSTASCII_USTRINGPARAM("DataPilot") );
/*N*/   //! from Resource?
/*N*/
/*N*/   for (USHORT nAdd=0; nAdd<=nCount; nAdd++)   //  nCount+1 Versuche
/*N*/   {
/*N*/       String aNewName = aBase;
/*N*/       aNewName += String::CreateFromInt32( nMin + nAdd );
/*N*/       BOOL bFound = FALSE;
/*N*/       for (USHORT i=0; i<nCount && !bFound; i++)
/*N*/           if (((ScPivot*)pItems[i])->GetName() == aNewName)
/*N*/               bFound = TRUE;
/*N*/       if (!bFound)
/*N*/           return aNewName;            // freien Namen gefunden
/*N*/   }
/*N*/   return String();                    // sollte nicht vorkommen
/*N*/ }

//STRIP001 ScPivot* ScPivotCollection::GetPivotAtCursor(USHORT nCol, USHORT nRow, USHORT nTab) const
//STRIP001 {
//STRIP001  if (pItems)
//STRIP001  {
//STRIP001      for (USHORT i = 0; i < nCount; i++)
//STRIP001          if (((ScPivot*)pItems[i])->IsPivotAtCursor(nCol, nRow, nTab))
//STRIP001          {
//STRIP001              return (ScPivot*)pItems[i];
//STRIP001          }
//STRIP001  }
//STRIP001  return NULL;
//STRIP001 }

/*N*/ BOOL ScPivotCollection::Load(SvStream& rStream)
/*N*/ {
/*N*/   BOOL bSuccess = TRUE;
/*N*/   USHORT nNewCount, i;
/*N*/   FreeAll();
/*N*/
/*N*/   ScMultipleReadHeader aHdr( rStream );
/*N*/
/*N*/   rStream >> nNewCount;
/*N*/   for (i=0; i<nNewCount && bSuccess; i++)
/*N*/   {
/*N*/       ScPivot* pPivot = new ScPivot( pDoc );
/*N*/       if (pPivot)
/*N*/       {
/*N*/           bSuccess = pPivot->Load(rStream, aHdr);
/*N*/           Insert( pPivot );
/*N*/       }
/*N*/       else
/*N*/           bSuccess = FALSE;
/*N*/   }
/*N*/
/*N*/   //  fuer alte Dateien: eindeutige Namen vergeben
/*N*/
/*N*/   if (bSuccess)
/*N*/       for (i=0; i<nCount; i++)
/*N*/           if (!((const ScPivot*)At(i))->GetName().Len())
/*N*/               ((ScPivot*)At(i))->SetName( CreateNewName() );
/*N*/
/*N*/   return bSuccess;
/*N*/ }

/*N*/ BOOL ScPivotCollection::Store(SvStream& rStream) const
/*N*/ {
/*N*/   BOOL bSuccess = TRUE;
/*N*/
/*N*/   ScMultipleWriteHeader aHdr( rStream );
/*N*/
/*N*/   rStream << nCount;
/*N*/
/*N*/   for (USHORT i=0; i<nCount && bSuccess; i++)
/*?*/       bSuccess = ((const ScPivot*)At(i))->Store( rStream, aHdr );
/*N*/
/*N*/   return bSuccess;
/*N*/ }

/*N*/ void ScPivotCollection::UpdateReference(UpdateRefMode eUpdateRefMode,
/*N*/                               USHORT nCol1, USHORT nRow1, USHORT nTab1,
/*N*/                               USHORT nCol2, USHORT nRow2, USHORT nTab2,
/*N*/                               short nDx, short nDy, short nDz )
/*N*/ {
/*N*/   for (USHORT i=0; i<nCount; i++)
/*N*/   {
/*?*/       USHORT theCol1;
/*?*/       USHORT theRow1;
/*?*/       USHORT theTab1;
/*?*/       USHORT theCol2;
/*?*/       USHORT theRow2;
/*?*/       USHORT theTab2;
/*?*/       ScRefUpdateRes eRes;
/*?*/       ScPivot* pPivot = (ScPivot*)pItems[i];
/*?*/
/*?*/       //  Source
/*?*/
/*?*/       pPivot->GetSrcArea( theCol1, theRow1, theCol2, theRow2, theTab1 );
/*?*/       theTab2 = theTab1;
/*?*/
/*?*/       eRes = ScRefUpdate::Update( pDoc, eUpdateRefMode,
/*?*/                                               nCol1,nRow1,nTab1, nCol2,nRow2,nTab2, nDx,nDy,nDz,
/*?*/                                               theCol1,theRow1,theTab1, theCol2,theRow2,theTab2 );
/*?*/
/*?*/       if (eRes != UR_NOTHING)
/*?*/           pPivot->MoveSrcArea( theCol1, theRow1, theTab1 );
/*?*/
/*?*/       //  Dest
/*?*/
/*?*/       pPivot->GetDestArea( theCol1, theRow1, theCol2, theRow2, theTab1 );
/*?*/       theTab2 = theTab1;
/*?*/
/*?*/       eRes = ScRefUpdate::Update( pDoc, eUpdateRefMode,
/*?*/                                               nCol1,nRow1,nTab1, nCol2,nRow2,nTab2, nDx,nDy,nDz,
/*?*/                                               theCol1,theRow1,theTab1, theCol2,theRow2,theTab2 );
/*?*/
/*?*/       if (eRes != UR_NOTHING)
/*?*/           pPivot->MoveDestArea( theCol1, theRow1, theTab1 );
/*N*/   }
/*N*/ }

//STRIP001 void ScPivotCollection::UpdateGrow( const ScRange& rArea, USHORT nGrowX, USHORT nGrowY )
//STRIP001 {
//STRIP001  //  nur Quell-Bereich
//STRIP001
//STRIP001  for (USHORT i=0; i<nCount; i++)
//STRIP001  {
//STRIP001      ScPivot* pPivot = (ScPivot*)pItems[i];
//STRIP001      ScRange aSrc = pPivot->GetSrcArea();
//STRIP001      ScRefUpdateRes eRes = ScRefUpdate::DoGrow( rArea, nGrowX, nGrowY, aSrc );
//STRIP001      if (eRes != UR_NOTHING)
//STRIP001          pPivot->ExtendSrcArea( aSrc.aEnd.Col(), aSrc.aEnd.Row() );
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL ScPivotCollection::operator==(const ScPivotCollection& rCmp) const
//STRIP001 {
//STRIP001  if (nCount != rCmp.nCount)
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if (!nCount)
//STRIP001      return TRUE;            // beide leer - nicht erst die Param's anlegen!
//STRIP001
//STRIP001  ScPivotParam aMyParam, aCmpParam;
//STRIP001  ScQueryParam aMyQuery, aCmpQuery;
//STRIP001  ScArea aMyArea, aCmpArea;
//STRIP001
//STRIP001  for (USHORT i=0; i<nCount; i++)
//STRIP001  {
//STRIP001      ScPivot* pMyPivot = (ScPivot*)pItems[i];
//STRIP001      pMyPivot->GetParam( aMyParam, aMyQuery, aMyArea );
//STRIP001      ScPivot* pCmpPivot = (ScPivot*)rCmp.pItems[i];
//STRIP001      pCmpPivot->GetParam( aCmpParam, aCmpQuery, aCmpArea );
//STRIP001      if (!( aMyArea==aCmpArea && aMyParam==aCmpParam && aMyQuery==aCmpQuery ))
//STRIP001          return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 DataObject*  ScPivotCollection::Clone() const
//STRIP001 {
//STRIP001  return new ScPivotCollection(*this);
//STRIP001 }




}
