/*************************************************************************
 *
 *  $RCSfile: sw_wrtswtbl.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:53:10 $
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
#include "filt_pch.hxx"
#endif

#pragma hdrstop

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _SVX_BOXITEM_HXX //autogen
#include <bf_svx/boxitem.hxx>
#endif
#ifndef _SVX_BRSHITEM_HXX //autogen
#include <bf_svx/brshitem.hxx>
#endif
#ifndef _FRACT_HXX
#include <tools/fract.hxx>
#endif

#ifndef _WRTSWTBL_HXX
#include <wrtswtbl.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _FRMFMT_HXX
#include <frmfmt.hxx>
#endif
#ifndef _FMTFSIZE_HXX
#include <fmtfsize.hxx>
#endif
#ifndef _FMTORNT_HXX
#include <fmtornt.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
#ifndef _HTMLTBL_HXX
#include <htmltbl.hxx>
#endif
namespace binfilter {


//STRIP001 SV_IMPL_PTRARR( SwWriteTableCells, SwWriteTableCellPtr )
//STRIP001 SV_IMPL_OP_PTRARR_SORT( SwWriteTableRows, SwWriteTableRowPtr )
//STRIP001 SV_IMPL_OP_PTRARR_SORT( SwWriteTableCols, SwWriteTableColPtr )

//-----------------------------------------------------------------------

//STRIP001 SwVertOrient SwWriteTableCell::GetVertOri() const
//STRIP001 {
//STRIP001  SwVertOrient eCellVertOri = VERT_TOP;
//STRIP001  if( pBox->GetSttNd() )
//STRIP001  {
//STRIP001      const SfxItemSet& rItemSet = pBox->GetFrmFmt()->GetAttrSet();
//STRIP001      const SfxPoolItem *pItem;
//STRIP001      if( SFX_ITEM_SET == rItemSet.GetItemState( RES_VERT_ORIENT, FALSE, &pItem ) )
//STRIP001      {
//STRIP001          SwVertOrient eBoxVertOri =
//STRIP001              ((const SwFmtVertOrient *)pItem)->GetVertOrient();
//STRIP001          if( VERT_CENTER==eBoxVertOri || VERT_BOTTOM==eBoxVertOri)
//STRIP001              eCellVertOri = eBoxVertOri;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return eCellVertOri;
//STRIP001 }

//-----------------------------------------------------------------------

//STRIP001 SwWriteTableRow::SwWriteTableRow( long nPosition, BOOL bUseLayoutHeights )
//STRIP001  : nPos(nPosition), mbUseLayoutHeights(bUseLayoutHeights), pBackground( 0 ),
//STRIP001  bTopBorder(TRUE), bBottomBorder(TRUE),
//STRIP001  nTopBorder(USHRT_MAX), nBottomBorder(USHRT_MAX)
//STRIP001 {
//STRIP001 }


//STRIP001 SwWriteTableCell *SwWriteTableRow::AddCell( const SwTableBox *pBox,
//STRIP001                              USHORT nRow, USHORT nCol,
//STRIP001                              USHORT nRowSpan, USHORT nColSpan,
//STRIP001                              long nHeight,
//STRIP001                              const SvxBrushItem *pBackground )
//STRIP001 {
//STRIP001  SwWriteTableCell *pCell =
//STRIP001      new SwWriteTableCell( pBox, nRow, nCol, nRowSpan, nColSpan,
//STRIP001                              nHeight, pBackground );
//STRIP001  aCells.Insert( pCell, aCells.Count() );
//STRIP001
//STRIP001  return pCell;
//STRIP001 }

//-----------------------------------------------------------------------

/*N*/ SwWriteTableCol::SwWriteTableCol( USHORT nPosition )
/*N*/   : nPos(nPosition),
/*N*/   bLeftBorder(TRUE), bRightBorder(TRUE),
/*N*/   nWidthOpt( 0 ), bRelWidthOpt( FALSE ),
/*N*/   bOutWidth( TRUE )
/*N*/ {
/*N*/ }

//-----------------------------------------------------------------------

/*N*/ long SwWriteTable::GetBoxWidth( const SwTableBox *pBox )
/*N*/ {
/*N*/   const SwFrmFmt *pFmt = pBox->GetFrmFmt();
/*N*/   const SwFmtFrmSize& aFrmSize=
/*N*/       (const SwFmtFrmSize&)pFmt->GetAttr( RES_FRM_SIZE );
/*N*/
/*N*/   return aFrmSize.GetSize().Width();
/*N*/ }

//STRIP001 long SwWriteTable::GetLineHeight( const SwTableLine *pLine )
//STRIP001 {
//STRIP001 #ifndef PRODUCT
//STRIP001  BOOL bOldGetLineHeightCalled = bGetLineHeightCalled;
//STRIP001  bGetLineHeightCalled = TRUE;
//STRIP001 #endif
//STRIP001
//STRIP001  long nHeight = 0;
//STRIP001  if( bUseLayoutHeights )
//STRIP001  {
//STRIP001      // Erstmal versuchen wir die Hoehe ueber das Layout zu bekommen
//STRIP001      long nHeight = pLine->GetLineRect( FALSE ).Height();
//STRIP001      if( nHeight > 0 )
//STRIP001          return nHeight;
//STRIP001
//STRIP001      // Wenn kein Layout gefunden wurde, gehen wir von festen Hoehen aus.
//STRIP001      bUseLayoutHeights = FALSE;
//STRIP001
//STRIP001 #ifndef PRODUCT
//STRIP001      ASSERT( !bOldGetLineHeightCalled, "Layout ungueltig?" );
//STRIP001 #endif
//STRIP001  }
//STRIP001
//STRIP001  const SwTableBoxes& rBoxes = pLine->GetTabBoxes();
//STRIP001  USHORT nBoxes = rBoxes.Count();
//STRIP001
//STRIP001  for( USHORT nBox=0; nBox<nBoxes; nBox++ )
//STRIP001  {
//STRIP001      const SwTableBox* pBox = rBoxes[nBox];
//STRIP001      if( pBox->GetSttNd() )
//STRIP001      {
//STRIP001          if( nHeight < ROW_DFLT_HEIGHT )
//STRIP001              nHeight = ROW_DFLT_HEIGHT;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          long nTmp = 0;
//STRIP001          const SwTableLines &rLines = pBox->GetTabLines();
//STRIP001          for( USHORT nLine=0; nLine<rLines.Count(); nLine++ )
//STRIP001          {
//STRIP001              nTmp += GetLineHeight( rLines[nLine] );
//STRIP001          }
//STRIP001          if( nHeight < nTmp )
//STRIP001              nHeight = nTmp;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return nHeight;
//STRIP001 }

//STRIP001 long SwWriteTable::GetLineHeight( const SwTableBox *pBox ) const
//STRIP001 {
//STRIP001  const SwTableLine *pLine = pBox->GetUpper();
//STRIP001
//STRIP001  if( !pLine )
//STRIP001      return 0;
//STRIP001
//STRIP001  const SwFrmFmt *pLineFrmFmt = pLine->GetFrmFmt();
//STRIP001  const SfxPoolItem* pItem;
//STRIP001  const SfxItemSet& rItemSet = pLineFrmFmt->GetAttrSet();
//STRIP001
//STRIP001  long nHeight = 0;
//STRIP001  if( SFX_ITEM_SET == rItemSet.GetItemState( RES_FRM_SIZE, TRUE, &pItem ))
//STRIP001      nHeight = ((SwFmtFrmSize*)pItem)->GetHeight();
//STRIP001
//STRIP001  return nHeight;
//STRIP001 }

//STRIP001 const SvxBrushItem *SwWriteTable::GetLineBrush( const SwTableBox *pBox,
//STRIP001                                                SwWriteTableRow *pRow )
//STRIP001 {
//STRIP001  const SwTableLine *pLine = pBox->GetUpper();
//STRIP001
//STRIP001  while( pLine )
//STRIP001  {
//STRIP001      const SwFrmFmt *pLineFrmFmt = pLine->GetFrmFmt();
//STRIP001      const SfxPoolItem* pItem;
//STRIP001      const SfxItemSet& rItemSet = pLineFrmFmt->GetAttrSet();
//STRIP001
//STRIP001      const SvxBrushItem *pBrushItem = 0;
//STRIP001      if( SFX_ITEM_SET == rItemSet.GetItemState( RES_BACKGROUND, FALSE,
//STRIP001                                                 &pItem ) )
//STRIP001      {
//STRIP001          if( !pLine->GetUpper() )
//STRIP001          {
//STRIP001              if( !pRow->GetBackground() )
//STRIP001                  pRow->SetBackground( (const SvxBrushItem *)pItem );
//STRIP001              pItem = 0;
//STRIP001          }
//STRIP001
//STRIP001          return (const SvxBrushItem *)pItem;
//STRIP001      }
//STRIP001
//STRIP001      pBox = pLine->GetUpper();
//STRIP001      pLine = pBox ? pBox->GetUpper() : 0;
//STRIP001  }
//STRIP001
//STRIP001  return 0;
//STRIP001 }


//STRIP001 void SwWriteTable::MergeBorders( const SvxBorderLine* pBorderLine,
//STRIP001                                 BOOL bTable )
//STRIP001 {
//STRIP001  if( (UINT32)-1 == nBorderColor )
//STRIP001  {
//STRIP001      Color aGrayColor( COL_GRAY );
//STRIP001      if( !pBorderLine->GetColor().IsRGBEqual( aGrayColor ) )
//STRIP001          nBorderColor = pBorderLine->GetColor().GetColor();
//STRIP001  }
//STRIP001
//STRIP001  if( !bCollectBorderWidth )
//STRIP001      return;
//STRIP001
//STRIP001  USHORT nOutWidth = pBorderLine->GetOutWidth();
//STRIP001  if( bTable )
//STRIP001  {
//STRIP001      if( nOutWidth && (!nBorder || nOutWidth < nBorder) )
//STRIP001          nBorder = nOutWidth;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( nOutWidth && (!nInnerBorder || nOutWidth < nInnerBorder) )
//STRIP001          nInnerBorder = nOutWidth;
//STRIP001  }
//STRIP001
//STRIP001  USHORT nDist = pBorderLine->GetInWidth() ? pBorderLine->GetDistance()
//STRIP001                                              : 0;
//STRIP001  if( nDist && (!nCellSpacing || nDist < nCellSpacing) )
//STRIP001      nCellSpacing = nDist;
//STRIP001 }


//STRIP001 USHORT SwWriteTable::MergeBoxBorders( const SwTableBox *pBox,
//STRIP001                                      USHORT nRow, USHORT nCol,
//STRIP001                                      USHORT nRowSpan, USHORT nColSpan,
//STRIP001                                      USHORT& rTopBorder,
//STRIP001                                      USHORT &rBottomBorder )
//STRIP001 {
//STRIP001  USHORT nBorderMask = 0;
//STRIP001
//STRIP001  const SwFrmFmt *pFrmFmt = pBox->GetFrmFmt();
//STRIP001  const SvxBoxItem& rBoxItem = (const SvxBoxItem&)pFrmFmt->GetAttr( RES_BOX );
//STRIP001
//STRIP001  USHORT nWidth = 0;
//STRIP001
//STRIP001  if( rBoxItem.GetTop() )
//STRIP001  {
//STRIP001      nBorderMask |= 1;
//STRIP001      MergeBorders( rBoxItem.GetTop(), nRow==0 );
//STRIP001      rTopBorder = rBoxItem.GetTop()->GetOutWidth();
//STRIP001  }
//STRIP001
//STRIP001  if( rBoxItem.GetLeft() )
//STRIP001  {
//STRIP001      nBorderMask |= 4;
//STRIP001      MergeBorders( rBoxItem.GetLeft(), nCol==0 );
//STRIP001  }
//STRIP001
//STRIP001  if( rBoxItem.GetBottom() )
//STRIP001  {
//STRIP001      nBorderMask |= 2;
//STRIP001      MergeBorders( rBoxItem.GetBottom(), nRow+nRowSpan==aRows.Count() );
//STRIP001      rBottomBorder = rBoxItem.GetBottom()->GetOutWidth();
//STRIP001  }
//STRIP001
//STRIP001  if( rBoxItem.GetRight() )
//STRIP001  {
//STRIP001      nBorderMask |= 8;
//STRIP001      MergeBorders( rBoxItem.GetRight(), nCol+nColSpan==aCols.Count() );
//STRIP001  }
//STRIP001
//STRIP001  // If any distance is set, the smallest one is used. This holds for
//STRIP001  // the four distance of a box as well as for the distances of different
//STRIP001  // boxes.
//STRIP001  if( bCollectBorderWidth )
//STRIP001  {
//STRIP001      USHORT nDist = rBoxItem.GetDistance( BOX_LINE_TOP );
//STRIP001      if( nDist && (!nCellPadding || nDist < nCellPadding) )
//STRIP001          nCellPadding = nDist;
//STRIP001      nDist = rBoxItem.GetDistance( BOX_LINE_BOTTOM );
//STRIP001      if( nDist && (!nCellPadding || nDist < nCellPadding) )
//STRIP001          nCellPadding = nDist;
//STRIP001      nDist = rBoxItem.GetDistance( BOX_LINE_LEFT );
//STRIP001      if( nDist && (!nCellPadding || nDist < nCellPadding) )
//STRIP001          nCellPadding = nDist;
//STRIP001      nDist = rBoxItem.GetDistance( BOX_LINE_RIGHT );
//STRIP001      if( nDist && (!nCellPadding || nDist < nCellPadding) )
//STRIP001          nCellPadding = nDist;
//STRIP001  }
//STRIP001
//STRIP001  return nBorderMask;
//STRIP001 }


//STRIP001 USHORT SwWriteTable::GetRawWidth( USHORT nCol, USHORT nColSpan ) const
//STRIP001 {
//STRIP001  USHORT nWidth = aCols[nCol+nColSpan-1]->GetPos();
//STRIP001  if( nCol > 0 )
//STRIP001      nWidth -= aCols[nCol-1]->GetPos();
//STRIP001
//STRIP001  return nWidth;
//STRIP001 }

//STRIP001 USHORT SwWriteTable::GetLeftSpace( USHORT nCol ) const
//STRIP001 {
//STRIP001  USHORT nSpace = nCellPadding + nCellSpacing;
//STRIP001
//STRIP001  // In der ersten Spalte auch noch die Liniendicke abziehen
//STRIP001  if( nCol==0 )
//STRIP001  {
//STRIP001      nSpace += nLeftSub;
//STRIP001
//STRIP001      const SwWriteTableCol *pCol = aCols[nCol];
//STRIP001      if( pCol->HasLeftBorder() )
//STRIP001          nSpace += nBorder;
//STRIP001  }
//STRIP001
//STRIP001  return nSpace;
//STRIP001 }

//STRIP001 USHORT SwWriteTable::GetRightSpace( USHORT nCol, USHORT nColSpan ) const
//STRIP001 {
//STRIP001  USHORT nSpace = nCellPadding;
//STRIP001
//STRIP001  // In der letzten Spalte noch einmal zusaetzlich CELLSPACING und
//STRIP001  // und die Liniendicke abziehen
//STRIP001  if( nCol+nColSpan==aCols.Count() )
//STRIP001  {
//STRIP001      nSpace += (nCellSpacing + nRightSub);
//STRIP001
//STRIP001      const SwWriteTableCol *pCol = aCols[nCol+nColSpan-1];
//STRIP001      if( pCol->HasRightBorder() )
//STRIP001          nSpace += nBorder;
//STRIP001  }
//STRIP001
//STRIP001  return nSpace;
//STRIP001 }

//STRIP001 USHORT SwWriteTable::GetAbsWidth( USHORT nCol, USHORT nColSpan ) const
//STRIP001 {
//STRIP001  long nWidth = GetRawWidth( nCol, nColSpan );
//STRIP001  if( nBaseWidth != nTabWidth )
//STRIP001  {
//STRIP001      nWidth *= nTabWidth;
//STRIP001      nWidth /= nBaseWidth;
//STRIP001  }
//STRIP001
//STRIP001  nWidth -= GetLeftSpace( nCol ) + GetRightSpace( nCol, nColSpan );
//STRIP001
//STRIP001  ASSERT( nWidth > 0, "Spaltenbreite <= 0. OK?" );
//STRIP001  return nWidth > 0 ? (USHORT)nWidth : 0;
//STRIP001 }

//STRIP001 USHORT SwWriteTable::GetRelWidth( USHORT nCol, USHORT nColSpan ) const
//STRIP001 {
//STRIP001  long nWidth = GetRawWidth( nCol, nColSpan );
//STRIP001
//STRIP001  return (USHORT)(long)Fraction( nWidth*256 + GetBaseWidth()/2,
//STRIP001                                 GetBaseWidth() );
//STRIP001 }

//STRIP001 USHORT SwWriteTable::GetPrcWidth( USHORT nCol, USHORT nColSpan ) const
//STRIP001 {
//STRIP001  long nWidth = GetRawWidth( nCol, nColSpan );
//STRIP001
//STRIP001  // sieht komisch aus, ist aber nichts anderes als
//STRIP001  //  [(100 * nWidth) + .5] ohne Rundungsfehler
//STRIP001  return (USHORT)(long)Fraction( nWidth*100 + GetBaseWidth()/2,
//STRIP001                                 GetBaseWidth() );
//STRIP001 }

//STRIP001 long SwWriteTable::GetAbsHeight( long nRawHeight, USHORT nRow,
//STRIP001                                 USHORT nRowSpan ) const
//STRIP001 {
//STRIP001  nRawHeight -= (2*nCellPadding + nCellSpacing);
//STRIP001
//STRIP001  // In der ersten Zeile noch einmal zusaetzlich CELLSPACING und
//STRIP001  // und die Liniendicke abziehen
//STRIP001  const SwWriteTableRow *pRow = 0;
//STRIP001  if( nRow==0 )
//STRIP001  {
//STRIP001      nRawHeight -= nCellSpacing;
//STRIP001      pRow = aRows[nRow];
//STRIP001      if( pRow->HasTopBorder() )
//STRIP001          nRawHeight -= nBorder;
//STRIP001  }
//STRIP001
//STRIP001  // In der letzten Zeile noch die Liniendicke abziehen
//STRIP001  if( nRow+nRowSpan==aRows.Count() )
//STRIP001  {
//STRIP001      if( !pRow || nRowSpan > 1 )
//STRIP001          pRow = aRows[nRow+nRowSpan-1];
//STRIP001      if( pRow->HasBottomBorder() )
//STRIP001          nRawHeight -= nBorder;
//STRIP001  }
//STRIP001
//STRIP001  ASSERT( nRawHeight > 0, "Zeilenheohe <= 0. OK?" );
//STRIP001  return nRawHeight > 0 ? nRawHeight : 0;
//STRIP001 }



//STRIP001 BOOL SwWriteTable::ShouldExpandSub( const SwTableBox *pBox,
//STRIP001                                    BOOL bExpandedBefore,
//STRIP001                                    USHORT nDepth ) const
//STRIP001 {
//STRIP001  return !pBox->GetSttNd() && nDepth > 0;
//STRIP001 }

//STRIP001 void SwWriteTable::CollectTableRowsCols( long nStartRPos,
//STRIP001                                         USHORT nStartCPos,
//STRIP001                                         long nParentLineHeight,
//STRIP001                                         USHORT nParentLineWidth,
//STRIP001                                         const SwTableLines& rLines,
//STRIP001                                         USHORT nDepth )
//STRIP001 {
//STRIP001  BOOL bSubExpanded = FALSE;
//STRIP001  USHORT nLines = rLines.Count();
//STRIP001
//STRIP001 #ifndef PRODUCT
//STRIP001  USHORT nEndCPos = 0;
//STRIP001 #endif
//STRIP001
//STRIP001  long nRPos = nStartRPos;
//STRIP001  for( USHORT nLine = 0; nLine < nLines; nLine++ )
//STRIP001  {
//STRIP001      /*const*/ SwTableLine *pLine = rLines[nLine];
//STRIP001
//STRIP001      long nOldRPos = nRPos;
//STRIP001
//STRIP001      if( nLine < nLines-1 || nParentLineHeight==0  )
//STRIP001      {
//STRIP001          nRPos += GetLineHeight( pLine );
//STRIP001          SwWriteTableRow *pRow = new SwWriteTableRow( nRPos, bUseLayoutHeights);
//STRIP001          USHORT nRow;
//STRIP001          if( aRows.Seek_Entry( pRow, &nRow ) )
//STRIP001              delete pRow;
//STRIP001          else
//STRIP001              aRows.Insert( pRow );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          long nCheckPos = nRPos + GetLineHeight( pLine );
//STRIP001          nRPos = nStartRPos + nParentLineHeight;
//STRIP001 #ifndef PRODUCT
//STRIP001          SwWriteTableRow aRow( nStartRPos + nParentLineHeight, bUseLayoutHeights );
//STRIP001          ASSERT( aRows.Seek_Entry(&aRow),
//STRIP001                  "Parent-Zeile nicht gefunden" );
//STRIP001          ASSERT( !bUseLayoutHeights ||
//STRIP001                  SwWriteTableRow(nCheckPos,bUseLayoutHeights) == SwWriteTableRow(nRPos,bUseLayoutHeights),
//STRIP001                  "Hoehe der Zeilen stimmt nicht mit Parent ueberein" );
//STRIP001 #endif
//STRIP001      }
//STRIP001
//STRIP001      // Fuer alle Boxen der Zeile ggf. eine Spalte einfuegen
//STRIP001      const SwTableBoxes& rBoxes = pLine->GetTabBoxes();
//STRIP001      USHORT nBoxes = rBoxes.Count();
//STRIP001
//STRIP001      USHORT nCPos = nStartCPos;
//STRIP001      for( USHORT nBox=0; nBox<nBoxes; nBox++ )
//STRIP001      {
//STRIP001          const SwTableBox *pBox = rBoxes[nBox];
//STRIP001
//STRIP001          USHORT nOldCPos = nCPos;
//STRIP001
//STRIP001          if( nBox < nBoxes-1 || (nParentLineWidth==0 && nLine==0)  )
//STRIP001          {
//STRIP001              nCPos += (USHORT)GetBoxWidth( pBox );
//STRIP001              SwWriteTableCol *pCol = new SwWriteTableCol( nCPos );
//STRIP001
//STRIP001              USHORT nCol;
//STRIP001              if( aCols.Seek_Entry( pCol, &nCol ) )
//STRIP001                  delete pCol;
//STRIP001              else
//STRIP001                  aCols.Insert( pCol );
//STRIP001
//STRIP001              if( nBox==nBoxes-1 )
//STRIP001              {
//STRIP001                  ASSERT( nLine==0 && nParentLineWidth==0,
//STRIP001                          "Jetzt wird die Parent-Breite plattgemacht!" );
//STRIP001                  nParentLineWidth = nCPos-nStartCPos;
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001 #ifndef PRODUCT
//STRIP001              USHORT nCheckPos = nCPos + (USHORT)GetBoxWidth( pBox );
//STRIP001              if( !nEndCPos )
//STRIP001              {
//STRIP001                  nEndCPos = nCheckPos;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  ASSERT( SwWriteTableCol(nCheckPos) ==
//STRIP001                                              SwWriteTableCol(nEndCPos),
//STRIP001                  "Zelle enthaelt unterschiedlich breite Zeilen" );
//STRIP001              }
//STRIP001 #endif
//STRIP001              nCPos = nStartCPos + nParentLineWidth;
//STRIP001 #ifndef PRODUCT
//STRIP001              SwWriteTableCol aCol( nStartCPos + nParentLineWidth );
//STRIP001              ASSERT( aCols.Seek_Entry(&aCol),
//STRIP001                      "Parent-Zelle nicht gefunden" );
//STRIP001              ASSERT( SwWriteTableCol(nCheckPos) ==
//STRIP001                                          SwWriteTableCol(nCPos),
//STRIP001                      "Breite der Zellen stimmt nicht mit Parent ueberein" );
//STRIP001 #endif
//STRIP001          }
//STRIP001
//STRIP001          if( ShouldExpandSub( pBox, bSubExpanded, nDepth ) )
//STRIP001          {
//STRIP001              CollectTableRowsCols( nOldRPos, nOldCPos,
//STRIP001                                      nRPos - nOldRPos,
//STRIP001                                      nCPos - nOldCPos,
//STRIP001                                      pBox->GetTabLines(),
//STRIP001                                      nDepth-1 );
//STRIP001              bSubExpanded = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }


//STRIP001 void SwWriteTable::FillTableRowsCols( long nStartRPos, USHORT nStartRow,
//STRIP001                                      USHORT nStartCPos, USHORT nStartCol,
//STRIP001                                      long nParentLineHeight,
//STRIP001                                      USHORT nParentLineWidth,
//STRIP001                                      const SwTableLines& rLines,
//STRIP001                                      const SvxBrushItem* pParentBrush,
//STRIP001                                      USHORT nDepth )
//STRIP001 {
//STRIP001  USHORT nLines = rLines.Count();
//STRIP001  BOOL bSubExpanded = FALSE;
//STRIP001
//STRIP001  // Festlegen der Umrandung
//STRIP001  long nRPos = nStartRPos;
//STRIP001  USHORT nRow = nStartRow;
//STRIP001
//STRIP001  for( USHORT nLine = 0; nLine < nLines; nLine++ )
//STRIP001  {
//STRIP001      const SwTableLine *pLine = rLines[nLine];
//STRIP001
//STRIP001      // Position der letzten ueberdeckten Zeile ermitteln
//STRIP001      long nOldRPos = nRPos;
//STRIP001      if( nLine < nLines-1 || nParentLineHeight==0 )
//STRIP001          nRPos += GetLineHeight( pLine );
//STRIP001      else
//STRIP001          nRPos = nStartRPos + nParentLineHeight;
//STRIP001
//STRIP001      // Und ihren Index
//STRIP001      USHORT nOldRow = nRow;
//STRIP001      SwWriteTableRow aRow( nRPos,bUseLayoutHeights );
//STRIP001      BOOL bFound = aRows.Seek_Entry( &aRow, &nRow );
//STRIP001      ASSERT( bFound, "Wo ist die Zeile geblieben?" );
//STRIP001
//STRIP001      SwWriteTableRow *pRow = aRows[nOldRow];
//STRIP001      SwWriteTableRow *pEndRow = aRows[nRow];
//STRIP001      if( nLine==0 && nParentLineHeight==0 )
//STRIP001          nHeadEndRow = nRow;
//STRIP001
//STRIP001      const SwTableBoxes& rBoxes = pLine->GetTabBoxes();
//STRIP001
//STRIP001      const SwFrmFmt *pLineFrmFmt = pLine->GetFrmFmt();
//STRIP001      const SfxPoolItem* pItem;
//STRIP001      const SfxItemSet& rItemSet = pLineFrmFmt->GetAttrSet();
//STRIP001
//STRIP001      long nHeight = 0;
//STRIP001      if( SFX_ITEM_SET == rItemSet.GetItemState( RES_FRM_SIZE, TRUE, &pItem ))
//STRIP001          nHeight = ((SwFmtFrmSize*)pItem)->GetHeight();
//STRIP001
//STRIP001
//STRIP001      const SvxBrushItem *pBrushItem, *pLineBrush = pParentBrush;
//STRIP001      if( SFX_ITEM_SET == rItemSet.GetItemState( RES_BACKGROUND, FALSE,
//STRIP001                                                 &pItem ) )
//STRIP001      {
//STRIP001          pLineBrush = (const SvxBrushItem *)pItem;
//STRIP001
//STRIP001          // Wenn die Zeile die gesamte Tabelle umspannt, koennen
//STRIP001          // Wir den Hintergrund an der Zeile ausgeben. Sonst muessen
//STRIP001          // wir in an den Zelle ausgeben.
//STRIP001          BOOL bOutAtRow = !nParentLineWidth;
//STRIP001          if( !bOutAtRow && nStartCPos==0 )
//STRIP001          {
//STRIP001              USHORT nEndCol;
//STRIP001              SwWriteTableCol aCol( nParentLineWidth );
//STRIP001              bOutAtRow = aCols.Seek_Entry(&aCol,&nEndCol) &&
//STRIP001                          nEndCol == aCols.Count()-1;
//STRIP001          }
//STRIP001          if( bOutAtRow )
//STRIP001          {
//STRIP001              pRow->SetBackground( pLineBrush );
//STRIP001              pBrushItem = 0;
//STRIP001          }
//STRIP001          else
//STRIP001              pBrushItem = pLineBrush;
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pRow->SetBackground( pLineBrush );
//STRIP001          pBrushItem = 0;
//STRIP001      }
//STRIP001
//STRIP001      USHORT nBoxes = rBoxes.Count();
//STRIP001      USHORT nCPos = nStartCPos;
//STRIP001      USHORT nCol = nStartCol;
//STRIP001
//STRIP001      for( USHORT nBox=0; nBox<nBoxes; nBox++ )
//STRIP001      {
//STRIP001          const SwTableBox *pBox = rBoxes[nBox];
//STRIP001
//STRIP001          // Position der letzten ueberdeckten Spalte ermitteln
//STRIP001          USHORT nOldCPos = nCPos;
//STRIP001          if( nBox < nBoxes-1 || (nParentLineWidth==0 && nLine==0) )
//STRIP001          {
//STRIP001              nCPos += (USHORT)GetBoxWidth( pBox );
//STRIP001              if( nBox==nBoxes-1 )
//STRIP001                  nParentLineWidth = nCPos - nStartCPos;
//STRIP001          }
//STRIP001          else
//STRIP001              nCPos = nStartCPos + nParentLineWidth;
//STRIP001
//STRIP001          // Und ihren Index
//STRIP001          USHORT nOldCol = nCol;
//STRIP001          SwWriteTableCol aCol( nCPos );
//STRIP001          BOOL bFound = aCols.Seek_Entry( &aCol, &nCol );
//STRIP001          ASSERT( bFound, "Wo ist die Spalte geblieben?" );
//STRIP001
//STRIP001          if( !ShouldExpandSub( pBox, bSubExpanded, nDepth ) )
//STRIP001          {
//STRIP001              USHORT nRowSpan = nRow - nOldRow + 1;
//STRIP001              USHORT nColSpan = nCol - nOldCol + 1;
//STRIP001              pRow->AddCell( pBox, nOldRow, nOldCol,
//STRIP001                             nRowSpan, nColSpan, nHeight,
//STRIP001                             pBrushItem );
//STRIP001              nHeight = 0; // Die Hoehe braucht nur einmal geschieben werden
//STRIP001
//STRIP001              if( pBox->GetSttNd() )
//STRIP001              {
//STRIP001                  // Wegen OS/2 schon hier, sonst gibt es einen
//STRIP001                  // Optimierungs-Fehler!!!!
//STRIP001                  SwWriteTableCol *pCol = aCols[nOldCol];
//STRIP001
//STRIP001                  USHORT nTopBorder = USHRT_MAX, nBottomBorder = USHRT_MAX;
//STRIP001                  USHORT nBorderMask = MergeBoxBorders( pBox, nOldRow, nOldCol,
//STRIP001                                                        nRowSpan, nColSpan,
//STRIP001                                                        nTopBorder,
//STRIP001                                                        nBottomBorder );
//STRIP001
//STRIP001                  if( !(nBorderMask & 4) )
//STRIP001                      pCol->bLeftBorder = FALSE;
//STRIP001
//STRIP001                  pCol = aCols[nCol];
//STRIP001                  if( !(nBorderMask & 8) )
//STRIP001                      pCol->bRightBorder = FALSE;
//STRIP001
//STRIP001                  if( !(nBorderMask & 1) )
//STRIP001                      pRow->bTopBorder = FALSE;
//STRIP001                  else if( !pRow->nTopBorder || nTopBorder < pRow->nTopBorder )
//STRIP001                      pRow->nTopBorder = nTopBorder;
//STRIP001
//STRIP001                  if( !(nBorderMask & 2) )
//STRIP001                      pEndRow->bBottomBorder = FALSE;
//STRIP001                  else if( !pEndRow->nBottomBorder ||
//STRIP001                           nBottomBorder < pEndRow->nBottomBorder )
//STRIP001                      pEndRow->nBottomBorder = nBottomBorder;
//STRIP001              }
//STRIP001 //               MIB: 13.12.2000: Why should a cell that contains a subtable
//STRIP001 //               not have borders? Moreover, switching them, off switches off
//STRIP001 //               the fill border lines between the columns and rows. (#74222#)
//STRIP001 //               else
//STRIP001 //               {
//STRIP001 //                   aCols[nOldCol]->bLeftBorder = FALSE;
//STRIP001 //                   aCols[nCol]->bRightBorder = FALSE;
//STRIP001 //                   pRow->bTopBorder = FALSE;
//STRIP001 //                   pEndRow->bBottomBorder = FALSE;
//STRIP001 //               }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              FillTableRowsCols( nOldRPos, nOldRow, nOldCPos, nOldCol,
//STRIP001                                  nRPos-nOldRPos, nCPos-nOldCPos,
//STRIP001                                  pBox->GetTabLines(),
//STRIP001                                  pLineBrush, nDepth-1 );
//STRIP001              bSubExpanded = TRUE;
//STRIP001          }
//STRIP001
//STRIP001          nCol++; // Die naechste Zelle faengt in der nachten Spalte an
//STRIP001      }
//STRIP001
//STRIP001      nRow++;
//STRIP001  }
//STRIP001 }

//STRIP001 SwWriteTable::SwWriteTable( const SwTableLines& rLines, long nWidth,
//STRIP001                              USHORT nBWidth, BOOL bRel, USHORT nMaxDepth,
//STRIP001                              USHORT nLSub, USHORT nRSub )
//STRIP001  : nBorderColor( (UINT32)-1 ),
//STRIP001  nBorder( 0 ),
//STRIP001  nInnerBorder( 0 ),
//STRIP001  nCellPadding( 0 ),
//STRIP001  nCellSpacing( 0 ),
//STRIP001  nTabWidth( nWidth ),
//STRIP001  nBaseWidth( nBWidth ),
//STRIP001  nLeftSub( nLSub ), nRightSub( nRSub ),
//STRIP001  bRelWidths( bRel ),
//STRIP001  bUseLayoutHeights( TRUE ),
//STRIP001 #ifndef PRODUCT
//STRIP001  bGetLineHeightCalled( FALSE ),
//STRIP001 #endif
//STRIP001  nHeadEndRow( USHRT_MAX ),
//STRIP001  bColsOption( FALSE ),
//STRIP001  bColTags( TRUE ),
//STRIP001  bLayoutExport( FALSE ),
//STRIP001  bCollectBorderWidth( TRUE )
//STRIP001 {
//STRIP001  USHORT nParentWidth = nBaseWidth + nLeftSub + nRightSub;
//STRIP001
//STRIP001  // Erstmal die Tabellen-Struktur festlegen. Hinter der Tabelle ist in
//STRIP001  // jedem Fall eine Spalte zu Ende
//STRIP001  SwWriteTableCol *pCol = new SwWriteTableCol( nParentWidth );
//STRIP001  aCols.Insert( pCol );
//STRIP001  CollectTableRowsCols( 0, 0, 0, nParentWidth, rLines, nMaxDepth - 1 );
//STRIP001
//STRIP001  // Und jetzt mit leben fuellen
//STRIP001  FillTableRowsCols( 0, 0, 0, 0, 0, nParentWidth, rLines, 0, nMaxDepth - 1 );
//STRIP001
//STRIP001  // Einige Twip-Werte an Pixel-Grenzen anpassen
//STRIP001  if( !nBorder )
//STRIP001      nBorder = nInnerBorder;
//STRIP001 }



//STRIP001 SwWriteTable::SwWriteTable( const SwHTMLTableLayout *pLayoutInfo )
//STRIP001  : nBorderColor( (UINT32)-1 ),
//STRIP001  nBorder( 0 ),
//STRIP001  nInnerBorder( 0 ),
//STRIP001  nCellPadding( 0 ),
//STRIP001  nCellSpacing( 0 ),
//STRIP001  nTabWidth( pLayoutInfo->GetWidthOption() ),
//STRIP001  nBaseWidth( pLayoutInfo->GetWidthOption() ),
//STRIP001  nLeftSub( 0 ), nRightSub( 0 ),
//STRIP001  bRelWidths( pLayoutInfo->HasPrcWidthOption() ),
//STRIP001  bUseLayoutHeights( FALSE ),
//STRIP001 #ifndef PRODUCT
//STRIP001  bGetLineHeightCalled( FALSE ),
//STRIP001 #endif
//STRIP001  nHeadEndRow( 0 ),
//STRIP001  bColsOption( pLayoutInfo->HasColsOption() ),
//STRIP001  bColTags( pLayoutInfo->HasColTags() ),
//STRIP001  bLayoutExport( TRUE ),
//STRIP001  bCollectBorderWidth( pLayoutInfo->HaveBordersChanged() )
//STRIP001 {
//STRIP001  if( !bCollectBorderWidth )
//STRIP001  {
//STRIP001      nBorder = pLayoutInfo->GetBorder();
//STRIP001      nCellPadding = pLayoutInfo->GetCellPadding();
//STRIP001      nCellSpacing = pLayoutInfo->GetCellSpacing();
//STRIP001  }
//STRIP001
//STRIP001  USHORT nRow, nCol;
//STRIP001  USHORT nCols = pLayoutInfo->GetColCount();
//STRIP001  USHORT nRows = pLayoutInfo->GetRowCount();
//STRIP001
//STRIP001  // Erstmal die Tabellen-Struktur festlegen.
//STRIP001  for( nCol=0; nCol<nCols; nCol++ )
//STRIP001  {
//STRIP001      SwWriteTableCol *pCol =
//STRIP001          new SwWriteTableCol( (nCol+1)*COL_DFLT_WIDTH );
//STRIP001
//STRIP001      if( bColTags )
//STRIP001      {
//STRIP001          const SwHTMLTableLayoutColumn *pLayoutCol =
//STRIP001              pLayoutInfo->GetColumn( nCol );
//STRIP001          pCol->SetWidthOpt( pLayoutCol->GetWidthOption(),
//STRIP001                             pLayoutCol->IsRelWidthOption() );
//STRIP001      }
//STRIP001
//STRIP001      aCols.Insert( pCol );
//STRIP001  }
//STRIP001
//STRIP001  for( nRow=0; nRow<nRows; nRow++ )
//STRIP001  {
//STRIP001      SwWriteTableRow *pRow =
//STRIP001          new SwWriteTableRow( (nRow+1)*ROW_DFLT_HEIGHT, bUseLayoutHeights );
//STRIP001      pRow->nTopBorder = 0;
//STRIP001      pRow->nBottomBorder = 0;
//STRIP001      aRows.Insert( pRow );
//STRIP001  }
//STRIP001
//STRIP001  // Und jetzt mit leben fuellen
//STRIP001  for( nRow=0; nRow<nRows; nRow++ )
//STRIP001  {
//STRIP001      SwWriteTableRow *pRow = aRows[nRow];
//STRIP001
//STRIP001      BOOL bHeightExported = FALSE;
//STRIP001      for( nCol=0; nCol<nCols; nCol++ )
//STRIP001      {
//STRIP001          const SwHTMLTableLayoutCell *pLayoutCell =
//STRIP001              pLayoutInfo->GetCell( nRow, nCol );
//STRIP001
//STRIP001          const SwHTMLTableLayoutCnts *pLayoutCnts =
//STRIP001              pLayoutCell->GetContents();
//STRIP001
//STRIP001          // Beginnt die Zelle eigentlich eine Zeile weiter oben oder
//STRIP001          // weiter vorne?
//STRIP001          if( ( nRow>0 && pLayoutCnts == pLayoutInfo->GetCell(nRow-1,nCol)
//STRIP001                                                    ->GetContents() ) ||
//STRIP001              ( nCol>0 && pLayoutCnts == pLayoutInfo->GetCell(nRow,nCol-1)
//STRIP001                                                    ->GetContents() ) )
//STRIP001          {
//STRIP001              continue;
//STRIP001          }
//STRIP001
//STRIP001          USHORT nRowSpan = pLayoutCell->GetRowSpan();
//STRIP001          USHORT nColSpan = pLayoutCell->GetColSpan();
//STRIP001          const SwTableBox *pBox = pLayoutCnts->GetTableBox();
//STRIP001          ASSERT( pBox,
//STRIP001                  "Tabelle in Tabelle kann nicht ueber Layout exportiert werden" );
//STRIP001
//STRIP001          long nHeight = bHeightExported ? 0 : GetLineHeight( pBox );
//STRIP001          const SvxBrushItem *pBrushItem = GetLineBrush( pBox, pRow );
//STRIP001
//STRIP001          SwWriteTableCell *pCell =
//STRIP001              pRow->AddCell( pBox, nRow, nCol, nRowSpan, nColSpan,
//STRIP001                             nHeight, pBrushItem );
//STRIP001          pCell->SetWidthOpt( pLayoutCell->GetWidthOption(),
//STRIP001                              pLayoutCell->IsPrcWidthOption() );
//STRIP001
//STRIP001          USHORT nTopBorder = USHRT_MAX, nBottomBorder = USHRT_MAX;
//STRIP001          USHORT nBorderMask =
//STRIP001          MergeBoxBorders( pBox, nRow, nCol, nRowSpan, nColSpan,
//STRIP001                              nTopBorder, nBottomBorder );
//STRIP001
//STRIP001          SwWriteTableCol *pCol = aCols[nCol];
//STRIP001          if( !(nBorderMask & 4) )
//STRIP001              pCol->bLeftBorder = FALSE;
//STRIP001
//STRIP001          pCol = aCols[nCol+nColSpan-1];
//STRIP001          if( !(nBorderMask & 8) )
//STRIP001              pCol->bRightBorder = FALSE;
//STRIP001
//STRIP001          if( !(nBorderMask & 1) )
//STRIP001              pRow->bTopBorder = FALSE;
//STRIP001
//STRIP001          SwWriteTableRow *pEndRow = aRows[nRow+nRowSpan-1];
//STRIP001          if( !(nBorderMask & 2) )
//STRIP001              pEndRow->bBottomBorder = FALSE;
//STRIP001
//STRIP001          // Die Hoehe braucht nur einmal geschieben werden
//STRIP001          if( nHeight )
//STRIP001              bHeightExported = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Einige Twip-Werte an Pixel-Grenzen anpassen
//STRIP001  if( bCollectBorderWidth && !nBorder )
//STRIP001      nBorder = nInnerBorder;
//STRIP001 }

}
