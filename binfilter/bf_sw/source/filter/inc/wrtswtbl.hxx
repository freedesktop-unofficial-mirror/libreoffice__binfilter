/*************************************************************************
 *
 *  $RCSfile: wrtswtbl.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:52:49 $
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

#ifndef  _WRTSWTBL_HXX
#define  _WRTSWTBL_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
#ifndef _TOOLS_COLOR_HXX
#include <tools/color.hxx>
#endif
#ifndef _SVARRAY_HXX
#include <svtools/svarray.hxx>
#endif

#ifndef _ORNTENUM_HXX
#include <orntenum.hxx>
#endif
#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif
class Color;
namespace binfilter {


class SwTableBox;
class SwTableBoxes;
class SwTableLine;
class SwTableLines;
class SwTable;
class SwFrmFmt;
class SwHTMLTableLayout;
class SvxBrushItem;
class SvxBoxItem;
class SvxBorderLine;


//---------------------------------------------------------------------------
//       Code aus dem HTML-Filter fuers schreiben von Tabellen
//---------------------------------------------------------------------------

#define COLFUZZY 20
#define ROWFUZZY 20
#define COL_DFLT_WIDTH ((2*COLFUZZY)+1)
#define ROW_DFLT_HEIGHT (2*ROWFUZZY)+1


//-----------------------------------------------------------------------

//STRIP001 class SwWriteTableCell
//STRIP001 {
//STRIP001  const SwTableBox *pBox;     // SwTableBox der Zelle
//STRIP001  const SvxBrushItem *pBackground;    // geerbter Hintergrund einer Zeile
//STRIP001
//STRIP001  long nHeight;               // fixe/Mindest-Hoehe der Zeile
//STRIP001
//STRIP001  USHORT nWidthOpt;           // Breite aus Option;
//STRIP001
//STRIP001  USHORT nRow;                // Start-Zeile
//STRIP001  USHORT nCol;                // Start-Spalte
//STRIP001
//STRIP001  USHORT nRowSpan;            // ueberspannte Zeilen
//STRIP001  USHORT nColSpan;            // ueberspannte Spalten
//STRIP001
//STRIP001
//STRIP001  BOOL bPrcWidthOpt;
//STRIP001
//STRIP001 public:
//STRIP001
//STRIP001  SwWriteTableCell(const SwTableBox *pB, USHORT nR, USHORT nC, USHORT nRSpan,
//STRIP001         USHORT nCSpan, long nHght, const SvxBrushItem *pBGround)
//STRIP001     : pBox( pB ), pBackground( pBGround ), nHeight( nHght ), nWidthOpt( 0 ),
//STRIP001     nRow( nR ), nCol( nC ), nRowSpan( nRSpan ), nColSpan( nCSpan ),
//STRIP001     bPrcWidthOpt( FALSE )
//STRIP001  {}
//STRIP001
//STRIP001  const SwTableBox *GetBox() const { return pBox; }
//STRIP001
//STRIP001  USHORT GetRow() const { return nRow; }
//STRIP001  USHORT GetCol() const { return nCol; }
//STRIP001
//STRIP001  USHORT GetRowSpan() const { return nRowSpan; }
//STRIP001  USHORT GetColSpan() const { return nColSpan; }
//STRIP001
//STRIP001  long GetHeight() const { return nHeight; }
//STRIP001  SwVertOrient GetVertOri() const;
//STRIP001
//STRIP001  const SvxBrushItem *GetBackground() const { return pBackground; }
//STRIP001
//STRIP001  void SetWidthOpt( USHORT nWidth, BOOL bPrc )
//STRIP001  {
//STRIP001      nWidthOpt = nWidth; bPrcWidthOpt = bPrc;
//STRIP001  }
//STRIP001
//STRIP001  USHORT GetWidthOpt() const { return nWidthOpt; }
//STRIP001  BOOL HasPrcWidthOpt() const { return bPrcWidthOpt; }
//STRIP001 };

//STRIP001 typedef SwWriteTableCell *SwWriteTableCellPtr;
//STRIP001 SV_DECL_PTRARR_DEL( SwWriteTableCells, SwWriteTableCellPtr, 5, 5 )


//-----------------------------------------------------------------------

//STRIP001 class SwWriteTableRow
//STRIP001 {
//STRIP001  SwWriteTableCells aCells;       // Alle Zellen der Rows
//STRIP001  const SvxBrushItem *pBackground;// Hintergrund
//STRIP001
//STRIP001  long nPos;                  // End-Position (twips) der Zeile
//STRIP001     BOOL mbUseLayoutHeights;
//STRIP001 public:
//STRIP001
//STRIP001  USHORT nTopBorder;              // Dicke der oberen/unteren Umrandugen
//STRIP001  USHORT nBottomBorder;
//STRIP001
//STRIP001  BOOL bTopBorder : 1;            // Welche Umrandungen sind da?
//STRIP001  BOOL bBottomBorder : 1;
//STRIP001
//STRIP001  SwWriteTableRow( long nPos, BOOL bUseLayoutHeights );
//STRIP001
//STRIP001  SwWriteTableCell *AddCell( const SwTableBox *pBox,
//STRIP001                               USHORT nRow, USHORT nCol,
//STRIP001                               USHORT nRowSpan, USHORT nColSpan,
//STRIP001                               long nHeight,
//STRIP001                               const SvxBrushItem *pBackground );
//STRIP001
//STRIP001  void SetBackground( const SvxBrushItem *pBGround )
//STRIP001  {
//STRIP001      pBackground = pBGround;
//STRIP001  }
//STRIP001  const SvxBrushItem *GetBackground() const { return pBackground; }
//STRIP001
//STRIP001  BOOL HasTopBorder() const                   { return bTopBorder; }
//STRIP001  BOOL HasBottomBorder() const                { return bBottomBorder; }
//STRIP001
//STRIP001  long GetPos() const                         { return nPos; }
//STRIP001  const SwWriteTableCells& GetCells() const   { return aCells; }
//STRIP001
//STRIP001  inline int operator==( const SwWriteTableRow& rRow ) const;
//STRIP001  inline int operator<( const SwWriteTableRow& rRow2 ) const;
//STRIP001 };

//STRIP001 inline int SwWriteTableRow::operator==( const SwWriteTableRow& rRow ) const
//STRIP001 {
//STRIP001  // etwas Unschaerfe zulassen
//STRIP001  return (nPos >= rRow.nPos ?  nPos - rRow.nPos : rRow.nPos - nPos ) <=
//STRIP001         (mbUseLayoutHeights ? 0 : ROWFUZZY);
//STRIP001 }

//STRIP001 inline int SwWriteTableRow::operator<( const SwWriteTableRow& rRow ) const
//STRIP001 {
//STRIP001  // Da wir hier nur die Wahrheits-Grade 0 und 1 kennen, lassen wir lieber
//STRIP001  // auch nicht zu, dass x==y und x<y gleichzeitig gilt ;-)
//STRIP001  return nPos < rRow.nPos - (mbUseLayoutHeights ? 0 : ROWFUZZY);
//STRIP001 }

//STRIP001 typedef SwWriteTableRow *SwWriteTableRowPtr;
//STRIP001 SV_DECL_PTRARR_SORT_DEL( SwWriteTableRows, SwWriteTableRowPtr, 5, 5 )


//-----------------------------------------------------------------------

class SwWriteTableCol
{
    USHORT nPos;                        // End Position der Spalte

    USHORT nWidthOpt;

    BOOL bRelWidthOpt : 1;
    BOOL bOutWidth : 1;                 // Spaltenbreite ausgeben?

public:
    BOOL bLeftBorder : 1;               // Welche Umrandungen sind da?
    BOOL bRightBorder : 1;

    SwWriteTableCol( USHORT nPosition );

    USHORT GetPos() const                       { return nPos; }

    void SetLeftBorder( BOOL bBorder )          { bLeftBorder = bBorder; }
    BOOL HasLeftBorder() const                  { return bLeftBorder; }

    void SetRightBorder( BOOL bBorder )         { bRightBorder = bBorder; }
    BOOL HasRightBorder() const                 { return bRightBorder; }

    void SetOutWidth( BOOL bSet )               { bOutWidth = bSet; }
    BOOL GetOutWidth() const                    { return bOutWidth; }

    inline int operator==( const SwWriteTableCol& rCol ) const;
    inline int operator<( const SwWriteTableCol& rCol ) const;

    void SetWidthOpt( USHORT nWidth, BOOL bRel )
    {
        nWidthOpt = nWidth; bRelWidthOpt = bRel;
    }
    USHORT GetWidthOpt() const                  { return nWidthOpt; }
    BOOL HasRelWidthOpt() const                 { return bRelWidthOpt; }
};

inline int SwWriteTableCol::operator==( const SwWriteTableCol& rCol ) const
{
    // etwas Unschaerfe zulassen
    return (nPos >= rCol.nPos ? nPos - rCol.nPos
                                     : rCol.nPos - nPos ) <= COLFUZZY;
}

inline int SwWriteTableCol::operator<( const SwWriteTableCol& rCol ) const
{
    // Da wir hier nur die Wahrheits-Grade 0 und 1 kennen, lassen wir lieber
    // auch nicht zu, dass x==y und x<y gleichzeitig gilt ;-)
    return nPos < rCol.nPos - COLFUZZY;
}


typedef SwWriteTableCol *SwWriteTableColPtr;
SV_DECL_PTRARR_SORT_DEL( SwWriteTableCols, SwWriteTableColPtr, 5, 5 )

//-----------------------------------------------------------------------

class SwWriteTable
{
//STRIP001 protected:
//STRIP001  SwWriteTableCols aCols; // alle Spalten
//STRIP001  SwWriteTableRows aRows; // alle Zellen
//STRIP001
//STRIP001  UINT32 nBorderColor;        // Umrandungsfarbe
//STRIP001
//STRIP001  USHORT nCellSpacing;        // Dicke der inneren Umrandung
//STRIP001  USHORT nCellPadding;        // Absatnd Umrandung-Inhalt
//STRIP001
//STRIP001  USHORT nBorder;             // Dicke der ausseren Umrandung
//STRIP001  USHORT nInnerBorder;        // Dicke der inneren Umrandung
//STRIP001  USHORT nBaseWidth;          // Bezugsgroesse fur Breiten SwFmtFrmSize
//STRIP001
//STRIP001  USHORT nHeadEndRow;         // letzte Zeile des Tabellen-Kopfes
//STRIP001
//STRIP001  USHORT nLeftSub;
//STRIP001  USHORT nRightSub;
//STRIP001
//STRIP001  long nTabWidth;             // Absolute/Relative Breite der Tabelle
//STRIP001
//STRIP001  BOOL bRelWidths : 1;        // Breiten relativ ausgeben?
//STRIP001  BOOL bUseLayoutHeights : 1; // Layout zur Hoehenbestimmung nehmen?
//STRIP001 #ifndef PRODUCT
//STRIP001  BOOL bGetLineHeightCalled : 1;
//STRIP001 #endif
//STRIP001
//STRIP001  BOOL bColsOption : 1;
//STRIP001  BOOL bColTags : 1;
//STRIP001  BOOL bLayoutExport : 1;
//STRIP001  BOOL bCollectBorderWidth : 1;

//STRIP001  virtual BOOL ShouldExpandSub( const SwTableBox *pBox,
//STRIP001                              BOOL bExpandedBefore, USHORT nDepth ) const;

//STRIP001  void CollectTableRowsCols( long nStartRPos, USHORT nStartCPos,
//STRIP001                             long nParentLineHeight,
//STRIP001                             USHORT nParentLineWidth,
//STRIP001                             const SwTableLines& rLines,
//STRIP001                             USHORT nDepth );

//STRIP001  void FillTableRowsCols( long nStartRPos, USHORT nStartRow,
//STRIP001                          USHORT nStartCPos, USHORT nStartCol,
//STRIP001                          long nParentLineHeight,
//STRIP001                          USHORT nParentLineWidth,
//STRIP001                          const SwTableLines& rLines,
//STRIP001                          const SvxBrushItem* pLineBrush,
//STRIP001                          USHORT nDepth );

//STRIP001  void MergeBorders( const SvxBorderLine* pBorderLine, BOOL bTable );

//STRIP001  USHORT MergeBoxBorders( const SwTableBox *pBox, USHORT nRow, USHORT nCol,
//STRIP001                          USHORT nRowSpan, USHORT nColSpan,
//STRIP001                          USHORT &rTopBorder, USHORT &rBottomBorder );

//STRIP001  USHORT GetBaseWidth() const { return nBaseWidth; }

//STRIP001  BOOL HasRelWidths() const { return bRelWidths; }

public:
    static long GetBoxWidth( const SwTableBox *pBox );
//STRIP001 protected:

//STRIP001  long GetLineHeight( const SwTableLine *pLine );
//STRIP001  long GetLineHeight( const SwTableBox *pBox ) const;
//STRIP001  const SvxBrushItem *GetLineBrush( const SwTableBox *pBox,
//STRIP001                                    SwWriteTableRow *pRow );

//STRIP001  USHORT GetLeftSpace( USHORT nCol ) const;
//STRIP001  USHORT GetRightSpace( USHORT nCol, USHORT nColSpan ) const;

//STRIP001  USHORT GetRawWidth( USHORT nCol, USHORT nColSpan ) const;
//STRIP001  USHORT GetAbsWidth( USHORT nCol, USHORT nColSpan ) const;
//STRIP001  USHORT GetRelWidth( USHORT nCol, USHORT nColSpan ) const;
//STRIP001  USHORT GetPrcWidth( USHORT nCol, USHORT nColSpan ) const;

//STRIP001  long GetAbsHeight( long nRawWidth, USHORT nRow, USHORT nRowSpan ) const;

//STRIP001 public:
//STRIP001  SwWriteTable( const SwTableLines& rLines, long nWidth, USHORT nBWidth,
//STRIP001                  BOOL bRel, USHORT nMaxDepth = USHRT_MAX,
//STRIP001                  USHORT nLeftSub=0, USHORT nRightSub=0 );
//STRIP001  SwWriteTable( const SwHTMLTableLayout *pLayoutInfo );

//STRIP001  const SwWriteTableCols& GetCols() const { return aCols; }
//STRIP001  const SwWriteTableRows& GetRows() const { return aRows; }
};




} //namespace binfilter
#endif

