/*************************************************************************
 *
 *  $RCSfile: sw_docchart.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:11:04 $
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

#include <float.h>

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _IPOBJ_HXX
#include <so3/ipobj.hxx>
#endif
#ifndef _SCH_DLL_HXX
#include <bf_sch/schdll.hxx>
#endif
#ifndef _SCH_MEMCHRT_HXX
#include <bf_sch/memchrt.hxx>
#endif
#ifndef _WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _NDINDEX_HXX
#include <ndindex.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _CALC_HXX
#include <calc.hxx>
#endif
#ifndef _FRMFMT_HXX
#include <frmfmt.hxx>
#endif
#ifndef _CELLFML_HXX
#include <cellfml.hxx>
#endif
#ifndef _VIEWSH_HXX
#include <viewsh.hxx>
#endif
#ifndef _NDOLE_HXX
#include <ndole.hxx>
#endif
#ifndef _CALBCK_HXX
#include <calbck.hxx>
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
#ifndef _SWTBLFMT_HXX
#include <swtblfmt.hxx>
#endif
#ifndef _TBLSEL_HXX
#include <tblsel.hxx>
#endif
#ifndef _CELLATR_HXX
#include <cellatr.hxx>
#endif


/*N*/ SchMemChart *SwTable::UpdateData( SchMemChart* pData,
/*N*/                               const String* pSelection ) const
/*N*/ {
/*N*/   SwCalc aCalc( *GetFrmFmt()->GetDoc() );
/*N*/   SwTblCalcPara aCalcPara( aCalc, *this );
/*N*/   String sSelection, sRowColInfo;
/*N*/   BOOL bSetChartRange = TRUE;
/*N*/
/*N*/   // worauf bezieht sich das Chart?
/*N*/   if( pData && pData->SomeData1().Len() )
/*N*/   {
/*?*/       sSelection = pData->SomeData1();
/*?*/       sRowColInfo = pData->SomeData2();
/*N*/   }
/*N*/   else if( pData && pData->GetChartRange().maRanges.size() )
/*N*/   {
/*?*/       SchDLL::ConvertChartRangeForWriter( *pData, FALSE );
/*?*/       sSelection = pData->SomeData1();
/*?*/       sRowColInfo = pData->SomeData2();
/*?*/       bSetChartRange = FALSE;
/*N*/   }
/*N*/   else if( pSelection )
/*N*/   {
/*?*/       sSelection = *pSelection;
/*?*/       sRowColInfo.AssignAscii( RTL_CONSTASCII_STRINGPARAM("11") );
/*N*/   }
/*N*/
/*N*/   SwChartLines aLines;
/*N*/   if( !IsTblComplexForChart( sSelection, &aLines ))
/*N*/   {
/*N*/       USHORT nLines = aLines.Count(), nBoxes = aLines[0]->Count();
/*N*/
/*N*/       if( !pData )
/*N*/       {
/*N*/           //JP 08.02.99: als default wird mit Spalten/Zeilenueberschrift
/*N*/           //              eingefuegt, deshalb das -1
/*?*/           pData = SchDLL::NewMemChart( nBoxes-1, nLines-1 );
/*?*/           pData->SetSubTitle( aEmptyStr );
/*?*/           pData->SetXAxisTitle( aEmptyStr );
/*?*/           pData->SetYAxisTitle( aEmptyStr );
/*?*/           pData->SetZAxisTitle( aEmptyStr );
/*N*/       }
/*N*/
/*N*/       USHORT nRowStt = 0, nColStt = 0;
/*N*/       if( sRowColInfo.Len() )
/*N*/       {
/*?*/           if( '1' == sRowColInfo.GetChar( 0 ))
/*?*/               ++nRowStt;
/*?*/           if( '1' == sRowColInfo.GetChar( 1 ))
/*?*/               ++nColStt;
/*N*/       }
/*N*/
/*N*/       if( (nBoxes - nColStt) > pData->GetColCount() )
/*N*/           SchDLL::MemChartInsertCols( *pData, 0, (nBoxes - nColStt) - pData->GetColCount() );
/*N*/       else if( (nBoxes - nColStt) < pData->GetColCount() )
/*?*/           SchDLL::MemChartRemoveCols( *pData, 0, pData->GetColCount() - (nBoxes - nColStt) );
/*N*/
/*N*/       if( (nLines - nRowStt) > pData->GetRowCount() )
/*N*/           SchDLL::MemChartInsertRows( *pData, 0, (nLines - nRowStt) - pData->GetRowCount() );
/*N*/       else if( (nLines - nRowStt) < pData->GetRowCount() )
/*?*/           SchDLL::MemChartRemoveRows( *pData, 0, pData->GetRowCount() - (nLines - nRowStt) );
/*N*/
/*N*/
/*N*/       ASSERT( pData->GetRowCount() >= (nLines - nRowStt ) &&
/*N*/               pData->GetColCount() >= (nBoxes - nColStt ),
/*N*/                   "Die Struktur fuers Chart ist zu klein,\n"
/*N*/                   "es wird irgendwo in den Speicher geschrieben!" );
/*N*/
/*N*/       // Row-Texte setzen
/*N*/       USHORT n;
/*N*/       if( nRowStt )
/*?*/           for( n = nColStt; n < nBoxes; ++n )
/*?*/           {
/*?*/               const SwTableBox *pBox = (*aLines[ 0 ])[ n ];
/*?*/               ASSERT( pBox->GetSttNd(), "Box without SttIdx" );
/*?*/               SwNodeIndex aIdx( *pBox->GetSttNd(), 1 );
/*?*/               const SwTxtNode* pTNd = aIdx.GetNode().GetTxtNode();
/*?*/               if( !pTNd )
/*?*/                   pTNd = aIdx.GetNodes().GoNextSection( &aIdx, TRUE, FALSE )
/*?*/                               ->GetTxtNode();
/*?*/
/*?*/               pData->SetColText( n - nColStt, pTNd->GetExpandTxt() );
/*?*/           }
/*N*/       else
/*N*/       {
/*N*/           String aText;
/*N*/           for( n = nColStt; n < nBoxes; ++n )
/*N*/           {
/*N*/               SchDLL::GetDefaultForColumnText( *pData, n - nColStt, aText );
/*N*/               pData->SetColText( n - nColStt, aText );
/*N*/           }
/*N*/       }
/*N*/
/*N*/       // Col-Texte setzen
/*N*/       if( nColStt )
/*N*/           for( n = nRowStt; n < nLines; ++n )
/*N*/           {
/*N*/               const SwTableBox *pBox = (*aLines[ n ])[ 0 ];
/*N*/               ASSERT( pBox->GetSttNd(), "Box without SttIdx" );
/*N*/               SwNodeIndex aIdx( *pBox->GetSttNd(), 1 );
/*N*/               const SwTxtNode* pTNd = aIdx.GetNode().GetTxtNode();
/*N*/               if( !pTNd )
/*N*/                   pTNd = aIdx.GetNodes().GoNextSection( &aIdx, TRUE, FALSE )
/*N*/                               ->GetTxtNode();
/*N*/
/*N*/               pData->SetRowText( n - nRowStt, pTNd->GetExpandTxt() );
/*N*/           }
/*N*/       else
/*N*/       {
/*N*/           String aText;
/*N*/           for( n = nRowStt; n < nLines; ++n )
/*N*/           {
/*N*/               SchDLL::GetDefaultForRowText( *pData, n - nRowStt, aText );
/*N*/               pData->SetRowText( n - nRowStt, aText );
/*N*/           }
/*N*/       }
/*N*/
/*N*/       // und dann fehlen nur noch die Daten
/*N*/       const SwTblBoxNumFormat& rDfltNumFmt = *(SwTblBoxNumFormat*)
/*N*/                                       GetDfltAttr( RES_BOXATR_FORMAT );
/*N*/       pData->SetNumberFormatter( GetFrmFmt()->GetDoc()->GetNumberFormatter());
/*N*/
/*N*/       int bFirstRow = TRUE;
/*N*/       for( n = nRowStt; n < nLines; ++n )
/*N*/       {
/*N*/           for( USHORT i = nColStt; i < nBoxes; ++i )
/*N*/           {
/*N*/               const SwTableBox* pBox = (*aLines[ n ])[ i ];
/*N*/               ASSERT( pBox->GetSttNd(), "Box without SttIdx" );
/*N*/               SwNodeIndex aIdx( *pBox->GetSttNd(), 1 );
/*N*/               const SwTxtNode* pTNd = aIdx.GetNode().GetTxtNode();
/*N*/               if( !pTNd )
/*?*/                   pTNd = aIdx.GetNodes().GoNextSection( &aIdx, TRUE, FALSE )
/*?*/                               ->GetTxtNode();
/*N*/
/*N*/               pData->SetData( short( i - nColStt ),
/*N*/                               short( n - nRowStt ),
/*N*/                               pTNd->GetTxt().Len()
/*N*/                                       ? pBox->GetValue( aCalcPara )
/*N*/                                       : DBL_MIN );
/*N*/
/*N*/               if( i == nColStt || bFirstRow )
/*N*/               {
/*N*/                   // first box of row set the numberformat
/*N*/                   const SwTblBoxNumFormat& rNumFmt = pBox->GetFrmFmt()->
/*N*/                                                       GetTblBoxNumFmt();
/*N*/                   if( rNumFmt != rDfltNumFmt )
/*N*/                   {
/*?*/                       pData->SetNumFormatIdCol( i, rNumFmt.GetValue() );
/*?*/                       if( bFirstRow )
/*?*/                           pData->SetNumFormatIdRow( n, rNumFmt.GetValue() );
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/           bFirstRow = FALSE;
/*N*/       }
/*N*/   }
/*N*/   else if( pData )
/*N*/   {
/*?*/       if( pData->GetColCount() )
/*?*/           SchDLL::MemChartRemoveCols( *pData, 0, pData->GetColCount() );
/*?*/       if( pData->GetRowCount() )
/*?*/           SchDLL::MemChartRemoveRows( *pData, 0, pData->GetRowCount() );
/*N*/   }
/*N*/   else
/*?*/       bSetChartRange = FALSE;
/*N*/
/*N*/   if( bSetChartRange )
/*N*/   {
/*N*/       // convert the selection string to the SchartRanges
/*N*/       pData->SomeData1() = sSelection;
/*N*/       pData->SomeData2() = sRowColInfo;
/*N*/       SchDLL::ConvertChartRangeForWriter( *pData, TRUE );
/*N*/   }
/*N*/
/*N*/   return pData;
/*N*/ }

/*N*/ BOOL SwTable::IsTblComplexForChart( const String& rSelection,
/*N*/                                   SwChartLines* pGetCLines ) const
/*N*/ {
/*N*/   const SwTableBox* pSttBox, *pEndBox;
/*N*/   if( 2 < rSelection.Len() )
/*N*/   {
/*N*/       // spitze Klammern am Anfang & Ende enfernen
/*?*/       String sBox( rSelection );
/*?*/       if( '<' == sBox.GetChar( 0  ) ) sBox.Erase( 0, 1 );
/*?*/       if( '>' == sBox.GetChar( sBox.Len()-1  ) ) sBox.Erase( sBox.Len()-1 );
/*?*/
/*?*/       xub_StrLen nTrenner = sBox.Search( ':' );
/*?*/       ASSERT( STRING_NOTFOUND != nTrenner, "keine gueltige Selektion" );
/*?*/
/*?*/       pSttBox = GetTblBox( sBox.Copy( 0, nTrenner ));
/*?*/       pEndBox = GetTblBox( sBox.Copy( nTrenner+1 ));
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       const SwTableLines* pLns = &GetTabLines();
/*N*/       pSttBox = (*pLns)[ 0 ]->GetTabBoxes()[ 0 ];
/*N*/       while( !pSttBox->GetSttNd() )
/*N*/           // bis zur Content Box!
/*?*/           pSttBox = pSttBox->GetTabLines()[ 0 ]->GetTabBoxes()[ 0 ];
/*N*/
/*N*/       const SwTableBoxes* pBoxes = &(*pLns)[ pLns->Count()-1 ]->GetTabBoxes();
/*N*/       pEndBox = (*pBoxes)[ pBoxes->Count()-1 ];
/*N*/       while( !pEndBox->GetSttNd() )
/*N*/       {
/*N*/           // bis zur Content Box!
/*?*/           pLns = &pEndBox->GetTabLines();
/*?*/           pBoxes = &(*pLns)[ pLns->Count()-1 ]->GetTabBoxes();
/*?*/           pEndBox = (*pBoxes)[ pBoxes->Count()-1 ];
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return !pSttBox || !pEndBox || !::ChkChartSel( *pSttBox->GetSttNd(),
/*N*/                                       *pEndBox->GetSttNd(), pGetCLines );
/*N*/ }



/*N*/ IMPL_LINK( SwDoc, DoUpdateAllCharts, Timer *, pTimer )
/*N*/ {
/*N*/   ViewShell* pVSh;
/*N*/   GetEditShell( &pVSh );
/*N*/   if( pVSh )
/*N*/   {
/*N*/       const SwFrmFmts& rTblFmts = *GetTblFrmFmts();
/*N*/       for( USHORT n = 0; n < rTblFmts.Count(); ++n )
/*N*/       {
/*N*/           SwTable* pTmpTbl;
/*N*/           const SwTableNode* pTblNd;
/*N*/           SwFrmFmt* pFmt = rTblFmts[ n ];
/*N*/
/*N*/           if( 0 != ( pTmpTbl = SwTable::FindTable( pFmt ) ) &&
/*N*/               0 != ( pTblNd = pTmpTbl->GetTableNode() ) &&
/*N*/               pTblNd->GetNodes().IsDocNodes() )
/*N*/           {
/*N*/               _UpdateCharts( *pTmpTbl, *pVSh );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return 0;
/*N*/ }

/*N*/ void SwDoc::_UpdateCharts( const SwTable& rTbl, ViewShell& rVSh ) const
/*N*/ {
/*N*/   String aName( rTbl.GetFrmFmt()->GetName() );
/*N*/   SwOLENode *pONd;
/*N*/   SwStartNode *pStNd;
/*N*/   SwNodeIndex aIdx( *GetNodes().GetEndOfAutotext().StartOfSectionNode(), 1 );
/*N*/   while( 0 != (pStNd = aIdx.GetNode().GetStartNode()) )
/*N*/   {
/*N*/       aIdx++;
/*N*/       SwFrm* pFrm;
/*N*/       if( 0 != ( pONd = aIdx.GetNode().GetOLENode() ) &&
/*N*/           aName.Equals( pONd->GetChartTblName() ) &&
/*N*/           0 != ( pFrm = pONd->GetFrm() ) )
/*N*/       {
/*N*/           SwOLEObj& rOObj = pONd->GetOLEObj();
/*N*/
/*N*/           SchMemChart *pData = SchDLL::GetChartData( rOObj.GetOleRef() );
/*N*/           FASTBOOL bDelData = 0 == pData;
/*N*/
/*N*/           ASSERT( pData, "UpdateChart ohne irgendwelche Daten?" );
/*N*/           pData = rTbl.UpdateData( pData );
/*N*/
/*N*/           if( pData->GetColCount() && pData->GetRowCount() )
/*N*/           {
/*N*/               SchDLL::Update( rOObj.GetOleRef(), pData, rVSh.GetWin() );
/*N*/
/*N*/               SwClientIter aIter( *pONd );
/*N*/               for( pFrm = (SwFrm*)aIter.First( TYPE(SwFrm) ); pFrm;
/*N*/                       pFrm = (SwFrm*)aIter.Next() )
/*N*/               {
/*N*/                   if( pFrm->Frm().HasArea() )
/*N*/                       rVSh.InvalidateWindows( pFrm->Frm() );
/*N*/               }
/*N*/           }
/*N*/
/*N*/           if ( bDelData )
/*?*/               delete pData;
/*N*/       }
/*N*/       aIdx.Assign( *pStNd->EndOfSectionNode(), + 1 );
/*N*/   }
/*N*/ }

//STRIP001 void SwDoc::UpdateCharts( const String &rName ) const
//STRIP001 {
//STRIP001  SwTable* pTmpTbl = SwTable::FindTable( FindTblFmtByName( rName ) );
//STRIP001  if( pTmpTbl )
//STRIP001  {
//STRIP001      ViewShell* pVSh;
//STRIP001      GetEditShell( &pVSh );
//STRIP001
//STRIP001      if( pVSh )
//STRIP001          _UpdateCharts( *pTmpTbl, *pVSh );
//STRIP001  }
//STRIP001 }

/*N*/ void SwDoc::SetTableName( SwFrmFmt& rTblFmt, const String &rNewName )
/*N*/ {
DBG_ASSERT(0, "STRIP"); //STRIP001  const String aOldName( rTblFmt.GetName() );
//STRIP001
//STRIP001  BOOL bNameFound = 0 == rNewName.Len();
//STRIP001  if( !bNameFound )
//STRIP001  {
//STRIP001      SwFrmFmt* pFmt;
//STRIP001      const SwFrmFmts& rTbl = *GetTblFrmFmts();
//STRIP001      for( USHORT i = rTbl.Count(); i; )
//STRIP001          if( !( pFmt = rTbl[ --i ] )->IsDefault() &&
//STRIP001              pFmt->GetName() == rNewName && IsUsed( *pFmt ) )
//STRIP001          {
//STRIP001              bNameFound = TRUE;
//STRIP001              break;
//STRIP001          }
//STRIP001  }
//STRIP001
//STRIP001  if( !bNameFound )
//STRIP001      rTblFmt.SetName( rNewName, sal_True );
//STRIP001  else
//STRIP001      rTblFmt.SetName( GetUniqueTblName(), sal_True );
//STRIP001
//STRIP001  SwStartNode *pStNd;
//STRIP001  SwNodeIndex aIdx( *GetNodes().GetEndOfAutotext().StartOfSectionNode(), 1 );
//STRIP001  while ( 0 != (pStNd = aIdx.GetNode().GetStartNode()) )
//STRIP001  {
//STRIP001      aIdx++;
//STRIP001      SwOLENode *pNd = aIdx.GetNode().GetOLENode();
//STRIP001      if( pNd && aOldName == pNd->GetChartTblName() )
//STRIP001      {
//STRIP001          pNd->SetChartTblName( rNewName );
//STRIP001
//STRIP001          SwOLEObj& rOObj = pNd->GetOLEObj();
//STRIP001          SchMemChart *pData = SchDLL::GetChartData( rOObj.GetOleRef() );
//STRIP001          if( pData )
//STRIP001          {
//STRIP001              ViewShell* pVSh;
//STRIP001              GetEditShell( &pVSh );
//STRIP001
//STRIP001              if( aOldName == pData->GetMainTitle() )
//STRIP001              {
//STRIP001                  pData->SetMainTitle( rNewName );
//STRIP001                  if( pVSh )
//STRIP001                      SchDLL::Update( rOObj.GetOleRef(), pData, pVSh->GetWin() );
//STRIP001              }
//STRIP001
//STRIP001              if( pVSh )
//STRIP001              {
//STRIP001                  SwFrm *pFrm;
//STRIP001                  SwClientIter aIter( *pNd );
//STRIP001                  for( pFrm = (SwFrm*)aIter.First( TYPE(SwFrm) ); pFrm;
//STRIP001                          pFrm = (SwFrm*)aIter.Next() )
//STRIP001                  {
//STRIP001                      if( pFrm->Frm().HasArea() )
//STRIP001                          pVSh->InvalidateWindows( pFrm->Frm() );
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      aIdx.Assign( *pStNd->EndOfSectionNode(), + 1 );
//STRIP001  }
//STRIP001  SetModified();
/*N*/ }


