/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_ndtbl1.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 22:29:47 $
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


#pragma hdrstop

#define ITEMID_BOXINFO      SID_ATTR_BORDER_INNER
#ifdef WTC
#define private public
#endif

#include "hintids.hxx"

#ifndef _SVX_BOXITEM_HXX //autogen
#include <bf_svx/boxitem.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _FMTORNT_HXX //autogen
#include <fmtornt.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _CELLFRM_HXX //autogen
#include <cellfrm.hxx>
#endif
#ifndef _TABFRM_HXX //autogen
#include <tabfrm.hxx>
#endif
#ifndef _TXTFRM_HXX //autogen
#include <txtfrm.hxx>
#endif

#include "doc.hxx"
#include "viscrs.hxx"
#include "swtblfmt.hxx"
namespace binfilter {


extern void ClearFEShellTabCols();

//siehe auch swtable.cxx
#define COLFUZZY 20L







/*N*/ void lcl_GetStartEndCell( const SwCursor& rCrsr,
/*N*/                       SwLayoutFrm *&prStart, SwLayoutFrm *&prEnd )
/*N*/ {
/*N*/   ASSERT( rCrsr.GetCntntNode() && rCrsr.GetCntntNode( FALSE ),
/*N*/           "Tabselection nicht auf Cnt." );
/*N*/
/*N*/   Point aPtPos, aMkPos;
/*N*/   const SwShellCrsr* pShCrsr = rCrsr;
/*N*/   if( pShCrsr )
/*N*/   {
/*N*/       aPtPos = pShCrsr->GetPtPos();
/*N*/       aMkPos = pShCrsr->GetMkPos();
/*N*/   }
/*N*/
/*N*/   prStart = rCrsr.GetCntntNode()->GetFrm( &aPtPos )->GetUpper();
/*N*/   prEnd   = rCrsr.GetCntntNode(FALSE)->GetFrm( &aMkPos )->GetUpper();
/*N*/ }

/*N*/ BOOL lcl_GetBoxSel( const SwCursor& rCursor, SwSelBoxes& rBoxes,
/*N*/                   BOOL bAllCrsr = FALSE )
/*N*/ {
/*N*/   const SwTableCursor* pTblCrsr = rCursor;
/*N*/   if( pTblCrsr )
/*?*/       ::binfilter::GetTblSelCrs( *pTblCrsr, rBoxes );
/*N*/   else
/*N*/   {
/*N*/       const SwPaM *pCurPam = &rCursor, *pSttPam = pCurPam;
/*N*/       do {
/*N*/           const SwNode* pNd = pCurPam->GetNode()->FindTableBoxStartNode();
/*N*/           if( pNd )
/*N*/           {
/*N*/               SwTableBox* pBox = (SwTableBox*)pNd->FindTableNode()->GetTable().
/*N*/                                           GetTblBox( pNd->GetIndex() );
/*N*/               rBoxes.Insert( pBox );
/*N*/           }
/*N*/       } while( bAllCrsr &&
/*N*/               pSttPam != ( pCurPam = (SwPaM*)pCurPam->GetNext()) );
/*N*/   }
/*N*/   return 0 != rBoxes.Count();
/*N*/ }

/***********************************************************************
#*  Class      :  SwDoc
#*  Methoden   :  SetRowHeight(), GetRowHeight()
#*  Datum      :  MA 17. May. 93
#*  Update     :  JP 28.04.98
#***********************************************************************/
//Die Zeilenhoehe wird ausgehend von der Selektion ermittelt/gesetzt.
//Ausgehend von jeder Zelle innerhalb der Selektion werden nach oben alle
//Zeilen abgeklappert, die oberste Zeile erhaelt den gewuenschten Wert alle
//tieferliegenden Zeilen einen entsprechenden Wert der sich aus der
//Relation der alten und neuen Groesse der obersten Zeile und ihrer
//eigenen Groesse ergiebt.
//Alle veraenderten Zeilen erhalten ggf. ein eigenes FrmFmt.
//Natuerlich darf jede Zeile nur einmal angefasst werden.

/*N*/ inline void InsertLine( SvPtrarr& rLineArr, SwTableLine* pLine )
/*N*/ {
/*N*/   if( USHRT_MAX == rLineArr.GetPos( (void*&)pLine ) )
/*N*/       rLineArr.Insert( (void*&)pLine, rLineArr.Count() );
/*N*/ }

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

/*N*/ struct LinesAndTable
/*N*/ {
/*N*/         SvPtrarr &rLines;
/*N*/   const SwTable  &rTable;
/*N*/         BOOL      bInsertLines;
/*N*/
/*N*/   LinesAndTable( SvPtrarr &rL, const SwTable &rTbl ) :
/*N*/         rLines( rL ), rTable( rTbl ), bInsertLines( TRUE ) {}
/*N*/ };


/*N*/ BOOL _FindLine( const _FndLine*& rpLine, void* pPara );

/*N*/ BOOL _FindBox( const _FndBox*& rpBox, void* pPara )
/*N*/ {
/*N*/   if ( rpBox->GetLines().Count() )
/*N*/   {
/*N*/       ((LinesAndTable*)pPara)->bInsertLines = TRUE;
/*N*/       ((_FndBox*)rpBox)->GetLines().ForEach( _FindLine, pPara );
/*N*/       if ( ((LinesAndTable*)pPara)->bInsertLines )
/*N*/       {
/*N*/           const SwTableLines &rLines = rpBox->GetBox()
/*N*/                                   ? rpBox->GetBox()->GetTabLines()
/*N*/                                   : ((LinesAndTable*)pPara)->rTable.GetTabLines();
/*N*/           if ( rpBox->GetLines().Count() == rLines.Count() )
/*N*/           {
/*N*/               for ( USHORT i = 0; i < rLines.Count(); ++i )
/*N*/                   ::binfilter::InsertLine( ((LinesAndTable*)pPara)->rLines,
/*N*/                                 (SwTableLine*)rLines[i] );
/*N*/           }
/*N*/           else
/*N*/               ((LinesAndTable*)pPara)->bInsertLines = FALSE;
/*N*/       }
/*N*/   }
/*N*/   else if ( rpBox->GetBox() )
/*N*/       ::binfilter::InsertLine( ((LinesAndTable*)pPara)->rLines,
/*N*/                     (SwTableLine*)rpBox->GetBox()->GetUpper() );
/*N*/   return TRUE;
/*N*/ }

/*N*/ BOOL _FindLine( const _FndLine*& rpLine, void* pPara )
/*N*/ {
/*N*/   ((_FndLine*)rpLine)->GetBoxes().ForEach( _FindBox, pPara );
/*N*/   return TRUE;
/*N*/ }

/*N*/ void lcl_CollectLines( SvPtrarr &rArr, const SwCursor& rCursor )
/*N*/ {
/*N*/   //Zuerst die selektierten Boxen einsammeln.
/*N*/   SwSelBoxes aBoxes;
/*N*/   if( !::binfilter::lcl_GetBoxSel( rCursor, aBoxes ))
/*?*/       return ;
/*N*/
/*N*/   //Die selektierte Struktur kopieren.
/*N*/   const SwTable &rTable = aBoxes[0]->GetSttNd()->FindTableNode()->GetTable();
/*N*/   LinesAndTable aPara( rArr, rTable );
/*N*/   _FndBox aFndBox( 0, 0 );
/*N*/   {
/*N*/       _FndPara aPara( aBoxes, &aFndBox );
/*N*/       ((SwTableLines&)rTable.GetTabLines()).ForEach( &_FndLineCopyCol, &aPara );
/*N*/   }
/*N*/
/*N*/   //Diejenigen Lines einsammeln, die nur selektierte Boxen enthalten.
/*N*/   const _FndBox *pTmp = &aFndBox;
/*N*/   ::binfilter::_FindBox( pTmp, &aPara );
/*N*/
/*N*/   //Jetzt die Lines entfernen, die von einer gemeinsamen uebergeordneten Line
/*N*/   //erfasst werden.
/*N*/   for ( USHORT i = 0; i < rArr.Count(); ++i )
/*N*/   {
/*N*/       SwTableLine *pUpLine = (SwTableLine*)rArr[i];
/*N*/       for ( USHORT k = 0; k < rArr.Count(); ++k )
/*N*/       {
/*N*/           if ( k != i && 1) //STRIP001 ::lcl_IsAnLower( pUpLine, (SwTableLine*)rArr[k] ) )
/*N*/           {
/*?*/               DBG_BF_ASSERT(0, "STRIP"); //STRIP001 rArr.Remove( k );
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------


/******************************************************************************
 *              void SwDoc::SetRowHeight( SwTwips nNew )
 ******************************************************************************/


/******************************************************************************
 *               SwTwips SwDoc::GetRowHeight() const
 ******************************************************************************/

/*N*/ BOOL SwDoc::BalanceRowHeight( const SwCursor& rCursor, BOOL bTstOnly )
/*N*/ {
/*N*/   BOOL bRet = FALSE;
/*N*/   SwTableNode* pTblNd = rCursor.GetPoint()->nNode.GetNode().FindTableNode();
/*N*/   if( pTblNd )
/*N*/   {
/*N*/       SvPtrarr aRowArr( 25, 50 ); //Zum sammeln der Lines.
/*N*/       ::binfilter::lcl_CollectLines( aRowArr, rCursor );
/*N*/
/*N*/       if( 1 < aRowArr.Count() )
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 if( !bTstOnly )
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }

/******************************************************************************
 *              void SwDoc::SetRowBackground()
 ******************************************************************************/

/******************************************************************************
 *               SwTwips SwDoc::GetRowBackground() const
 ******************************************************************************/

/***********************************************************************
#*  Class      :  SwDoc
#*  Methoden   :  SetTabBorders(), GetTabBorders()
#*  Datum      :  MA 18. May. 93
#*  Update     :  JP 29.04.98
#***********************************************************************/
/*N*/ inline void InsertCell( SvPtrarr& rCellArr, SwCellFrm* pCellFrm )
/*N*/ {
/*N*/   if( USHRT_MAX == rCellArr.GetPos( (void*&)pCellFrm ) )
/*N*/       rCellArr.Insert( (void*&)pCellFrm, rCellArr.Count() );
/*N*/ }

//-----------------------------------------------------------------------------
/*N*/ void lcl_CollectCells( SvPtrarr &rArr, const SwRect &rUnion,
/*N*/                         SwTabFrm *pTab )
/*N*/ {
/*N*/   SwLayoutFrm *pCell = pTab->FirstCell();
/*N*/   do
/*N*/   {
/*N*/       // Wenn in der Zelle ein spaltiger Bereich sitzt, muessen wir
/*N*/       // uns erst wieder zur Zelle hochhangeln
/*N*/       while ( !pCell->IsCellFrm() )
/*?*/           pCell = pCell->GetUpper();
/*N*/       ASSERT( pCell, "Frame ist keine Zelle." );
/*N*/       if ( rUnion.IsOver( pCell->Frm() ) )
/*N*/           ::binfilter::InsertCell( rArr, (SwCellFrm*)pCell );
/*N*/       //Dafuer sorgen, dass die Zelle auch verlassen wird (Bereiche)
/*N*/       SwLayoutFrm *pTmp = pCell;
/*N*/       do
/*N*/       {   pTmp = pTmp->GetNextLayoutLeaf();
/*N*/       } while ( pCell->IsAnLower( pTmp ) );
/*N*/       pCell = pTmp;
/*N*/   } while( pCell && pTab->IsAnLower( pCell ) );
/*N*/ }




/*N*/ void SwDoc::GetTabBorders( const SwCursor& rCursor, SfxItemSet& rSet ) const
/*N*/ {
/*N*/   SwTableNode* pTblNd = rCursor.GetPoint()->nNode.GetNode().FindTableNode();
/*N*/   if( !pTblNd )
/*?*/       return ;
/*N*/
/*N*/   SwLayoutFrm *pStart, *pEnd;
/*N*/   ::binfilter::lcl_GetStartEndCell( rCursor, pStart, pEnd );
/*N*/
/*N*/   SwSelUnions aUnions;
/*N*/   ::binfilter::MakeSelUnions( aUnions, pStart, pEnd );
/*N*/
/*N*/   if( aUnions.Count() )
/*N*/   {
/*N*/       SvxBoxItem     aSetBox    ((const SvxBoxItem    &) rSet.Get(RES_BOX    ));
/*N*/       SvxBoxInfoItem aSetBoxInfo((const SvxBoxInfoItem&) rSet.Get(SID_ATTR_BORDER_INNER));
/*N*/
/*N*/       BOOL bTopSet      = FALSE,
/*N*/            bBottomSet   = FALSE,
/*N*/            bLeftSet     = FALSE,
/*N*/            bRightSet    = FALSE,
/*N*/            bHoriSet     = FALSE,
/*N*/            bVertSet     = FALSE,
/*N*/            bDistanceSet = FALSE;
/*N*/
/*N*/       aSetBoxInfo.ResetFlags();
/*N*/
/*N*/       for ( USHORT i = 0; i < aUnions.Count(); ++i )
/*N*/       {
/*N*/           SwSelUnion *pUnion = aUnions[i];
/*N*/           const SwTabFrm *pTab = pUnion->GetTable();
/*N*/           const SwRect &rUnion = pUnion->GetUnion();
/*N*/           const BOOL bFirst = i == 0 ? TRUE : FALSE;
/*N*/           const BOOL bLast  = i == aUnions.Count() - 1 ? TRUE : FALSE;
/*N*/
/*N*/           SvPtrarr aCellArr( 255, 255 );
/*N*/           ::binfilter::lcl_CollectCells( aCellArr, rUnion, (SwTabFrm*)pTab );
/*N*/
/*N*/           for ( USHORT j = 0; j < aCellArr.Count(); ++j )
/*N*/           {
/*N*/               const SwCellFrm *pCell = (const SwCellFrm*)aCellArr[j];
/*N*/                 const sal_Bool bVert = pCell->IsVertical();
/*N*/                 const sal_Bool bRTL = pCell->IsRightToLeft();
/*N*/                 sal_Bool bTopOver, bLeftOver, bRightOver, bBottomOver;
/*N*/                 if ( bVert )
/*N*/                 {
/*N*/                     bTopOver = pCell->Frm().Right() >= rUnion.Right();
/*N*/                     bLeftOver = pCell->Frm().Top() <= rUnion.Top();
/*N*/                     bRightOver = pCell->Frm().Bottom() >= rUnion.Bottom();
/*N*/                     bBottomOver = pCell->Frm().Left() <= rUnion.Left();
/*N*/                 }
/*N*/                 else
/*N*/                 {
/*N*/                     bTopOver = pCell->Frm().Top() <= rUnion.Top();
/*N*/                     bLeftOver = pCell->Frm().Left() <= rUnion.Left();
/*N*/                     bRightOver = pCell->Frm().Right() >= rUnion.Right();
/*N*/                     bBottomOver = pCell->Frm().Bottom() >= rUnion.Bottom();
/*N*/                 }
/*N*/
/*N*/                 if ( bRTL )
/*N*/                 {
/*N*/                     sal_Bool bTmp = bRightOver;
/*N*/                     bRightOver = bLeftOver;
/*N*/                     bLeftOver = bTmp;
/*N*/                 }
/*N*/
/*N*/               const SwFrmFmt  *pFmt  = pCell->GetFmt();
/*N*/               const SvxBoxItem  &rBox  = pFmt->GetBox();
/*N*/
/*N*/               //Obere Kante
/*N*/               if ( bFirst && bTopOver )
/*N*/               {
/*N*/                   if (aSetBoxInfo.IsValid(VALID_TOP))
/*N*/                   {
/*N*/                       if ( !bTopSet )
/*N*/                       {   bTopSet = TRUE;
/*N*/                           aSetBox.SetLine( rBox.GetTop(), BOX_LINE_TOP );
/*N*/                       }
/*?*/                       else if ((aSetBox.GetTop() && rBox.GetTop() &&
/*?*/                                !(*aSetBox.GetTop() == *rBox.GetTop())) ||
/*?*/                                ((!aSetBox.GetTop()) ^ (!rBox.GetTop()))) // XOR-Ausdruck ist TRUE, wenn genau einer der beiden Pointer 0 ist
/*?*/                       {
/*?*/                           aSetBoxInfo.SetValid(VALID_TOP, FALSE );
/*?*/                           aSetBox.SetLine( 0, BOX_LINE_TOP );
/*?*/                       }
/*N*/                   }
/*N*/               }
/*N*/
/*N*/               //Linke Kante
/*N*/               if ( bLeftOver )
/*N*/               {
/*N*/                   if (aSetBoxInfo.IsValid(VALID_LEFT))
/*N*/                   {
/*N*/                       if ( !bLeftSet )
/*N*/                       {   bLeftSet = TRUE;
/*N*/                           aSetBox.SetLine( rBox.GetLeft(), BOX_LINE_LEFT );
/*N*/                       }
/*N*/                       else if ((aSetBox.GetLeft() && rBox.GetLeft() &&
/*?*/                                !(*aSetBox.GetLeft() == *rBox.GetLeft())) ||
/*?*/                                ((!aSetBox.GetLeft()) ^ (!rBox.GetLeft())))
/*?*/                       {
/*?*/                           aSetBoxInfo.SetValid(VALID_LEFT, FALSE );
/*?*/                           aSetBox.SetLine( 0, BOX_LINE_LEFT );
/*?*/                       }
/*N*/                   }
/*N*/               }
/*N*/               else
/*N*/               {
/*?*/                   if (aSetBoxInfo.IsValid(VALID_VERT))
/*?*/                   {
/*?*/                       if ( !bVertSet )
/*?*/                       {   bVertSet = TRUE;
/*?*/                           aSetBoxInfo.SetLine( rBox.GetLeft(), BOXINFO_LINE_VERT );
/*?*/                       }
/*?*/                       else if ((aSetBoxInfo.GetVert() && rBox.GetLeft() &&
/*?*/                                !(*aSetBoxInfo.GetVert() == *rBox.GetLeft())) ||
/*?*/                                ((!aSetBoxInfo.GetVert()) ^ (!rBox.GetLeft())))
/*?*/                       {   aSetBoxInfo.SetValid( VALID_VERT, FALSE );
/*?*/                           aSetBoxInfo.SetLine( 0, BOXINFO_LINE_VERT );
/*?*/                       }
/*?*/                   }
/*N*/               }
/*N*/
/*N*/               //Rechte Kante
/*N*/               if ( aSetBoxInfo.IsValid(VALID_RIGHT) && bRightOver )
/*N*/               {
/*N*/                   if ( !bRightSet )
/*N*/                   {   bRightSet = TRUE;
/*N*/                       aSetBox.SetLine( rBox.GetRight(), BOX_LINE_RIGHT );
/*N*/                   }
/*N*/                   else if ((aSetBox.GetRight() && rBox.GetRight() &&
/*?*/                            !(*aSetBox.GetRight() == *rBox.GetRight())) ||
/*?*/                            (!aSetBox.GetRight() ^ !rBox.GetRight()))
/*?*/                   {   aSetBoxInfo.SetValid( VALID_RIGHT, FALSE );
/*?*/                       aSetBox.SetLine( 0, BOX_LINE_RIGHT );
/*?*/                   }
/*N*/               }
/*N*/
/*N*/               //Untere Kante
/*N*/               if ( bLast && bBottomOver )
/*N*/               {
/*N*/                   if ( aSetBoxInfo.IsValid(VALID_BOTTOM) )
/*N*/                   {
/*N*/                       if ( !bBottomSet )
/*N*/                       {   bBottomSet = TRUE;
/*N*/                           aSetBox.SetLine( rBox.GetBottom(), BOX_LINE_BOTTOM );
/*N*/                       }
/*N*/                       else if ((aSetBox.GetBottom() && rBox.GetBottom() &&
/*?*/                                !(*aSetBox.GetBottom() == *rBox.GetBottom())) ||
/*?*/                                (!aSetBox.GetBottom() ^ !rBox.GetBottom()))
/*?*/                       {   aSetBoxInfo.SetValid( VALID_BOTTOM, FALSE );
/*?*/                           aSetBox.SetLine( 0, BOX_LINE_BOTTOM );
/*?*/                       }
/*N*/                   }
/*N*/               }
/*N*/               //in allen Zeilen ausser der letzten werden die
/*N*/               // horiz. Linien aus der Bottom-Linie entnommen
/*N*/               else
/*N*/               {
/*?*/                   if (aSetBoxInfo.IsValid(VALID_HORI))
/*?*/                   {
/*?*/                       if ( !bHoriSet )
/*?*/                       {   bHoriSet = TRUE;
/*?*/                           aSetBoxInfo.SetLine( rBox.GetBottom(), BOXINFO_LINE_HORI );
/*?*/                       }
/*?*/                       else if ((aSetBoxInfo.GetHori() && rBox.GetBottom() &&
/*?*/                                !(*aSetBoxInfo.GetHori() == *rBox.GetBottom())) ||
/*?*/                                ((!aSetBoxInfo.GetHori()) ^ (!rBox.GetBottom())))
/*?*/                       {
/*?*/                           aSetBoxInfo.SetValid( VALID_HORI, FALSE );
/*?*/                           aSetBoxInfo.SetLine( 0, BOXINFO_LINE_HORI );
/*?*/                       }
/*?*/                   }
/*N*/               }
/*N*/
/*N*/               // Abstand zum Text
/*N*/               if (aSetBoxInfo.IsValid(VALID_DISTANCE))
/*N*/               {
/*N*/                   static USHORT __READONLY_DATA aBorders[] = {
/*N*/                       BOX_LINE_BOTTOM, BOX_LINE_TOP,
/*N*/                       BOX_LINE_RIGHT, BOX_LINE_LEFT };
/*N*/                   const USHORT* pBrd = aBorders;
/*N*/
/*N*/                   if( !bDistanceSet )     // bei 1. Durchlauf erstmal setzen
/*N*/                   {
/*N*/                       bDistanceSet = TRUE;
/*N*/                       for( int i = 0; i < 4; ++i, ++pBrd )
/*N*/                           aSetBox.SetDistance( rBox.GetDistance( *pBrd ),
/*N*/                                               *pBrd );
/*N*/                   }
/*N*/                   else
/*N*/                   {
/*?*/                       for( int i = 0; i < 4; ++i, ++pBrd )
/*?*/                           if( aSetBox.GetDistance( *pBrd ) !=
/*?*/                               rBox.GetDistance( *pBrd ) )
/*?*/                           {
/*?*/                               aSetBoxInfo.SetValid( VALID_DISTANCE, FALSE );
/*?*/                               aSetBox.SetDistance( (USHORT) 0 );
/*?*/                               break;
/*?*/                           }
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/       rSet.Put( aSetBox );
/*N*/       rSet.Put( aSetBoxInfo );
/*N*/   }
/*N*/ }

/***********************************************************************
#*  Class      :  SwDoc
#*  Methoden   :  SetBoxAttr
#*  Datum      :  MA 18. Dec. 96
#*  Update     :  JP 29.04.98
#***********************************************************************/

/***********************************************************************
#*  Class      :  SwDoc
#*  Methoden   :  GetBoxBackground()
#*  Datum      :  MA 01. Jun. 93
#*  Update     :  JP 29.04.98
#***********************************************************************/


/***********************************************************************
#*  Class      :  SwDoc
#*  Methoden   :  SetBoxAlign, SetBoxAlign
#*  Datum      :  MA 18. Dec. 96
#*  Update     :  JP 29.04.98
#***********************************************************************/

/*N*/ USHORT SwDoc::GetBoxAlign( const SwCursor& rCursor ) const
/*N*/ {
/*N*/   USHORT nAlign = USHRT_MAX;
/*N*/   SwTableNode* pTblNd = rCursor.GetPoint()->nNode.GetNode().FindTableNode();
/*N*/   SwSelBoxes aBoxes;
/*N*/   if( pTblNd && ::binfilter::lcl_GetBoxSel( rCursor, aBoxes ))
/*N*/       for( USHORT i = 0; i < aBoxes.Count(); ++i )
/*N*/       {
/*N*/           const SwFmtVertOrient &rOri =
/*N*/                           aBoxes[i]->GetFrmFmt()->GetVertOrient();
/*N*/           if( USHRT_MAX == nAlign )
/*N*/               nAlign = rOri.GetVertOrient();
/*N*/           else if( rOri.GetVertOrient() != nAlign )
/*N*/           {
/*?*/               nAlign = USHRT_MAX;
/*?*/               break;
/*N*/           }
/*N*/       }
/*N*/   return nAlign;
/*N*/ }


/***********************************************************************
#*  Class      :  SwDoc
#*  Methoden   :  AdjustCellWidth()
#*  Datum      :  MA 20. Feb. 95
#*  Update     :  JP 29.04.98
#***********************************************************************/

/*Die Zelle ist in der Selektion, wird aber nicht von den TabCols beschrieben.
 *Das bedeutet, dass die Zelle aufgrund der zweidimensionalen Darstellung von
 *anderen Zellen "geteilt" wurde. Wir muessen also den Wunsch- bzw. Minimalwert
 *der Zelle auf die Spalten, durch die sie geteilt wurde verteilen.
 *
 *Dazu sammeln wir zuerst die Spalten - nicht die Spaltentrenner! - ein, die
 *sich mit der Zelle ueberschneiden. Den Wunschwert der Zelle verteilen wir
 *dann anhand des Betrages der Ueberschneidung auf die Zellen.
 *Wenn eine Zelle bereits einen groesseren Wunschwert angemeldet hat, so bleibt
 *dieser erhalten, kleinere Wuensche werden ueberschrieben.
 */


/*Besorgt neue Werte zu Einstellung der TabCols.
 *Es wird nicht ueber die Eintrage in den TabCols itereriert, sondern
 *quasi ueber die Zwischenraeume, die ja die Zellen beschreiben.
 *
 *bWishValues == TRUE:  Es werden zur aktuellen Selektion bzw. zur aktuellen
 *                      Zelle die Wunschwerte aller betroffen Zellen ermittelt.
 *                      Sind mehrere Zellen in einer Spalte, so wird der
 *                      groesste Wunschwert als Ergebnis geliefert.
 *                      Fuer die TabCol-Eintraege, zu denen keine Zellen
 *                      ermittelt wurden, werden 0-en eingetragen.
 *
 *bWishValues == FALSE: Die Selektion wird senkrecht ausgedehnt. Zu jeder
 *                      Spalte in den TabCols, die sich mit der Selektion
 *                      schneidet wird der Minimalwert ermittelt.
 */




}
