/*************************************************************************
 *
 *  $RCSfile: htmltbl.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:52 $
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

#ifndef _HTMLTBL_HXX
#define _HTMLTBL_HXX


#ifndef _TIMER_HXX //autogen
#include <vcl/timer.hxx>
#endif

#ifndef _SVX_SVXENUM_HXX //autogen
#include <bf_svx/svxenum.hxx>
#endif

#include "swtypes.hxx"
#include "node.hxx"     // Fuer SwStartNode


class SwTableBox;
class SwTable;
class SwHTMLTableLayout;
class SwDoc;
class SwFrmFmt;

#define HTMLTABLE_RESIZE_NOW (ULONG_MAX)

//STRIP001 class SwHTMLTableLayoutCnts
//STRIP001 {
//STRIP001  SwHTMLTableLayoutCnts *pNext;   // der naechste Inhalt
//STRIP001
//STRIP001  // von den beiden naechsten Pointern darf nur einer gesetzt sein!
//STRIP001  SwTableBox *pBox;           // ein Box
//STRIP001  SwHTMLTableLayout *pTable;  // eine "Tabelle in der Tabelle"
//STRIP001
//STRIP001  // Beim ersten Durchlauf gibt es noch keine Boxen. Es wird dann
//STRIP001  // pStartNode anstelle von pBox verwendet.
//STRIP001  const SwStartNode *pStartNode;
//STRIP001
//STRIP001  // Die folgenden Zahler geben an, wie oft ein Pass bereits fuer diesen
//STRIP001  // Inhalt durchgefuehrt wurde. Dazu werden sie mit einer Soll-Vorgabe
//STRIP001  // verglichen. Wird 255 erreicht laufen sie bei 0 weiter. So wird
//STRIP001  // eine Reinitialisierung bei jedem Resize vermieden.
//STRIP001  BYTE nPass1Done;            // Wieoft wurde Pass 1 aufgerufen?
//STRIP001  BYTE nWidthSet;             // Wieoft wurde die Breite gesetzt?
//STRIP001
//STRIP001  BOOL bNoBreakTag;       // <NOBR>-Tag ueber gesamten Inhalt
//STRIP001
//STRIP001 public:
//STRIP001
//STRIP001  SwHTMLTableLayoutCnts( const SwStartNode* pSttNd, SwHTMLTableLayout* pTab,
//STRIP001                         BOOL bNoBreakTag, SwHTMLTableLayoutCnts* pNxt );
//STRIP001
//STRIP001  ~SwHTMLTableLayoutCnts();
//STRIP001
//STRIP001  void SetTableBox( SwTableBox *pBx ) { pBox = pBx; }
//STRIP001  SwTableBox *GetTableBox() const { return pBox; }
//STRIP001
//STRIP001  SwHTMLTableLayout *GetTable() const { return pTable; }
//STRIP001
//STRIP001  const SwStartNode *GetStartNode() const;
//STRIP001
//STRIP001  // Ermitteln des naechsten Knotens
//STRIP001  SwHTMLTableLayoutCnts *GetNext() const { return pNext; }
//STRIP001
//STRIP001  void SetWidthSet( BYTE nRef ) { nWidthSet = nRef; }
//STRIP001  BOOL IsWidthSet( BYTE nRef ) const { return nRef==nWidthSet; }
//STRIP001
//STRIP001  void SetPass1Done( BYTE nRef ) { nPass1Done = nRef; }
//STRIP001  BOOL IsPass1Done( BYTE nRef ) const { return nRef==nPass1Done; }
//STRIP001
//STRIP001  BOOL HasNoBreakTag() const { return bNoBreakTag; }
//STRIP001 };

/*  */

//STRIP001 class SwHTMLTableLayoutCell
//STRIP001 {
//STRIP001  SwHTMLTableLayoutCnts *pContents;       // der Inhalt der Zelle
//STRIP001
//STRIP001  USHORT nRowSpan;    // ROWSPAN der Zelle
//STRIP001  USHORT nColSpan;    // COLSPAN der Zelle
//STRIP001  USHORT nWidthOption;// angegebene Breite der Zelle in Twip oder %
//STRIP001
//STRIP001  BOOL bPrcWidthOption : 1;// nWidth ist %-Angabe
//STRIP001  BOOL bNoWrapOption : 1; // NOWRAP-Option
//STRIP001
//STRIP001 public:
//STRIP001
//STRIP001  SwHTMLTableLayoutCell( SwHTMLTableLayoutCnts *pCnts,
//STRIP001                       USHORT nRSpan, USHORT nCSpan,
//STRIP001                       USHORT nWidthOpt, BOOL bPrcWdthOpt,
//STRIP001                       BOOL nNWrapOpt );
//STRIP001
//STRIP001  ~SwHTMLTableLayoutCell();
//STRIP001
//STRIP001  // Setzen/Ermitteln des Inhalts einer Zelle
//STRIP001  void SetContents( SwHTMLTableLayoutCnts *pCnts ) { pContents = pCnts; }
//STRIP001  SwHTMLTableLayoutCnts *GetContents() const { return pContents; }
//STRIP001
//STRIP001  inline void SetProtected();
//STRIP001
//STRIP001  // ROWSPAN/COLSPAN der Zelle Setzen/Ermitteln
//STRIP001  void SetRowSpan( USHORT nRSpan ) { nRowSpan = nRSpan; }
//STRIP001  USHORT GetRowSpan() const { return nRowSpan; }
//STRIP001  USHORT GetColSpan() const { return nColSpan; }
//STRIP001
//STRIP001  USHORT GetWidthOption() const { return nWidthOption; }
//STRIP001  BOOL IsPrcWidthOption() const { return bPrcWidthOption; }
//STRIP001
//STRIP001  BOOL HasNoWrapOption() const { return bNoWrapOption; }
//STRIP001 };

/*  */

//STRIP001 class SwHTMLTableLayoutColumn
//STRIP001 {
//STRIP001  // Zwischenwerte von AutoLayoutPass1
//STRIP001  ULONG nMinNoAlign, nMaxNoAlign, nAbsMinNoAlign;
//STRIP001
//STRIP001  // Ergebnisse von AutoLayoutPass1
//STRIP001  ULONG nMin, nMax;
//STRIP001
//STRIP001  // Ergibnisse von Pass 2
//STRIP001  USHORT nAbsColWidth;                // in Twips
//STRIP001  USHORT nRelColWidth;                // in Twips bzw. relativ zu USHRT_MAX
//STRIP001
//STRIP001  USHORT nWidthOption;                // Optionen von <COL> oder <TD>/<TH>
//STRIP001
//STRIP001  BOOL bRelWidthOption : 1;
//STRIP001  BOOL bLeftBorder : 1;
//STRIP001
//STRIP001 public:
//STRIP001
//STRIP001  SwHTMLTableLayoutColumn( USHORT nColWidthOpt, BOOL bRelColWidthOpt,
//STRIP001                           BOOL bLBorder );
//STRIP001
//STRIP001  ~SwHTMLTableLayoutColumn() {}
//STRIP001
//STRIP001  inline void MergeCellWidthOption( USHORT nWidth, BOOL bPrc );
//STRIP001  inline void SetWidthOption( USHORT nWidth, BOOL bRelWidth, BOOL bTest );
//STRIP001
//STRIP001  USHORT GetWidthOption() const { return nWidthOption; }
//STRIP001  BOOL IsRelWidthOption() const { return bRelWidthOption; }
//STRIP001
//STRIP001  inline void MergeMinMaxNoAlign( ULONG nMin, ULONG nMax, ULONG nAbsMin );
//STRIP001  ULONG GetMinNoAlign() const { return nMinNoAlign; }
//STRIP001  ULONG GetMaxNoAlign() const { return nMaxNoAlign; }
//STRIP001  ULONG GetAbsMinNoAlign() const { return nAbsMinNoAlign; }
//STRIP001  inline void ClearPass1Info( BOOL bWidthOpt );
//STRIP001
//STRIP001  inline void SetMinMax( ULONG nMin, ULONG nMax );
//STRIP001  void SetMax( ULONG nVal ) { nMax = nVal; }
//STRIP001  void AddToMin( ULONG nVal ) { nMin += nVal; }
//STRIP001  void AddToMax( ULONG nVal ) { nMax += nVal; }
//STRIP001  ULONG GetMin() const { return nMin; }
//STRIP001  ULONG GetMax() const { return nMax; }
//STRIP001
//STRIP001  void SetAbsColWidth( USHORT nWidth ) { nAbsColWidth = nWidth; }
//STRIP001  USHORT GetAbsColWidth() const { return nAbsColWidth; }
//STRIP001
//STRIP001  void SetRelColWidth( USHORT nWidth ) { nRelColWidth = nWidth; }
//STRIP001  USHORT GetRelColWidth() const { return nRelColWidth; }
//STRIP001
//STRIP001  BOOL HasLeftBorder() const { return bLeftBorder; }
//STRIP001 };

/*  */

class SwHTMLTableLayout
{
//STRIP001  Timer aResizeTimer;             // Timer fuer DelayedResize
//STRIP001
//STRIP001  SwHTMLTableLayoutColumn **aColumns;
//STRIP001  SwHTMLTableLayoutCell **aCells;
//STRIP001
//STRIP001  const SwTable *pSwTable;        // die SwTable (nur Top-Table)
//STRIP001  SwTableBox *pLeftFillerBox;     // linke Filler-Zelle (nur Tab in Tab)
//STRIP001  SwTableBox *pRightFillerBox;    // rechte Filler-Zelle (nur Tab-in Tab)
//STRIP001
//STRIP001  ULONG nMin;                     // minimale Breite der Tabelle (Twips)
//STRIP001  ULONG nMax;                     // maximale Breite der Tabelle (Twips)
//STRIP001
//STRIP001  USHORT nRows;                   // Anzahl Zeilen
//STRIP001  USHORT nCols;                   // Anzahl Spalten
//STRIP001
//STRIP001  USHORT nLeftMargin;             // Abstand zum linken Rand (aus Absatz)
//STRIP001  USHORT nRightMargin;            // Abstand zum rechten Rand (aus Absatz)
//STRIP001
//STRIP001  USHORT nInhAbsLeftSpace;        // von umgebender Zelle geerbter Abstand,
//STRIP001  USHORT nInhAbsRightSpace;       // der Zellen zugeschlagen wurde
//STRIP001
//STRIP001  USHORT nRelLeftFill;            // relative Breiten der Zellen zur
//STRIP001  USHORT nRelRightFill;           // Ausrichtung von Tabellen in Tabellen
//STRIP001
//STRIP001  USHORT nRelTabWidth;            // Die relative Breite der Tabelle
//STRIP001
//STRIP001  USHORT nWidthOption;            // die Breite der Tabelle (in Twip oder %)
//STRIP001  USHORT nCellPadding;            // Abstand zum Inhalt (in Twip)
//STRIP001  USHORT nCellSpacing;            // Absatnd zwischen Zellen (in Twip)
//STRIP001  USHORT nBorder;                 // Dicke der ausseren Umrandung bzw.
//STRIP001                                  // Platz, den Netscape hierfuer einrechnet.
//STRIP001
//STRIP001  USHORT nLeftBorderWidth;
//STRIP001  USHORT nRightBorderWidth;
//STRIP001  USHORT nInhLeftBorderWidth;
//STRIP001  USHORT nInhRightBorderWidth;
//STRIP001  USHORT nBorderWidth;
//STRIP001
//STRIP001  USHORT nDelayedResizeAbsAvail;  // Param fuer's verzoegerte Resize
//STRIP001  USHORT nLastResizeAbsAvail;
//STRIP001
//STRIP001  BYTE nPass1Done;                // Vorgabe-Werte fuer die einzelen
//STRIP001  BYTE nWidthSet;                 // Schleifen-Durchlauefe
//STRIP001
//STRIP001  SvxAdjust eTableAdjust;         // Die Ausrichtung der Tabelle
//STRIP001
//STRIP001  BOOL bColsOption : 1;           // Tabelle besitzt eine COLS-Option
//STRIP001  BOOL bColTags : 1;              // Tabelle besitzt COL/COLGRP-Tags
//STRIP001  BOOL bPrcWidthOption : 1;       // Breite ist eine %-Angabe
//STRIP001  BOOL bUseRelWidth : 1;          // SwTable bekommt relative Breite
//STRIP001
//STRIP001  BOOL bMustResize : 1;           // Tabelle muss in der Breite ang. werden
//STRIP001  BOOL bExportable : 1;           // Layout kann zum Export genutzt werden
//STRIP001  BOOL bBordersChanged : 1;       // Umrandung wurde geaendert
//STRIP001  BOOL bMayBeInFlyFrame : 1;      // Die Tabelle koennte im Rahmen sein
//STRIP001
//STRIP001  BOOL bDelayedResizeRecalc : 1;  // Param fuer's verzoegerte Resize
//STRIP001  BOOL bMustNotResize : 1;        // Die Tabelle darf nicht reseized werden
//STRIP001  BOOL bMustNotRecalc : 1;        // Tabelle darf nicht an Inhalt angepasst
//STRIP001                                  // werden
//STRIP001
//STRIP001 //   USHORT GetLeftBorderWidth( USHORT nCol ) const;
//STRIP001 //   USHORT GetRightBorderWidth( USHORT nCol, USHORT nColSpan ) const;
//STRIP001
//STRIP001  void AddBorderWidth( ULONG &rMin, ULONG &rMax, ULONG& rAbsMin,
//STRIP001                       USHORT nCol, USHORT nColSpan,
//STRIP001                       BOOL bSwBorders=TRUE ) const;
//STRIP001  void SetBoxWidth( SwTableBox *pBox, USHORT nCol, USHORT nColSpan ) const;
//STRIP001
//STRIP001  const SwStartNode *GetAnyBoxStartNode() const;
//STRIP001  SwFrmFmt *FindFlyFrmFmt() const;
//STRIP001  const SwDoc *GetDoc() const { return GetAnyBoxStartNode()->GetDoc(); }
//STRIP001
//STRIP001  void ClearPass1Info() { nMin = nMax = 0; }
//STRIP001
//STRIP001  void _Resize( USHORT nAbsAvail, BOOL bRecalc=FALSE );
//STRIP001
//STRIP001  DECL_STATIC_LINK( SwHTMLTableLayout, DelayedResize_Impl, void* );

public:

    SwHTMLTableLayout( const SwTable *pSwTbl,
                       USHORT nRows, USHORT nCols, BOOL bColsOpt, BOOL ColTgs,
                       USHORT nWidth, BOOL bPrcWidth, USHORT nBorderOpt,
                       USHORT nCellPad, USHORT nCellSp, SvxAdjust eAdjust,
                       USHORT nLMargin, USHORT nRMargin, USHORT nBWidth,
                       USHORT nLeftBWidth, USHORT nRightBWidth,
                       USHORT nInhLeftBWidth, USHORT nInhRightBWidth );

    ~SwHTMLTableLayout();

//STRIP001  USHORT GetLeftCellSpace( USHORT nCol, USHORT nColSpan,
//STRIP001                           BOOL bSwBorders=TRUE ) const;
//STRIP001  USHORT GetRightCellSpace( USHORT nCol, USHORT nColSpan,
//STRIP001                            BOOL bSwBorders=TRUE ) const;
//STRIP001  inline USHORT GetInhCellSpace( USHORT nCol, USHORT nColSpan ) const;
//STRIP001
//STRIP001  inline void SetInhBorderWidths( USHORT nLeft, USHORT nRight );
//STRIP001
//STRIP001
//STRIP001  void GetAvail( USHORT nCol, USHORT nColSpan, USHORT& rAbsAvail,
//STRIP001                 USHORT& rRelAvail ) const;
//STRIP001
//STRIP001  void AutoLayoutPass1();
//STRIP001  void AutoLayoutPass2( USHORT nAbsAvail, USHORT nRelAvail,
//STRIP001                        USHORT nAbsLeftSpace, USHORT nAbsRightSpace,
//STRIP001                        USHORT nParentInhSpace );
//STRIP001  void SetWidths( BOOL bCallPass2=FALSE, USHORT nAbsAvail=0,
//STRIP001                  USHORT nRelAvail=0, USHORT nAbsLeftSpace=0,
//STRIP001                  USHORT nAbsRightSpace=0,
//STRIP001                  USHORT nParentInhSpace=0 );
//STRIP001
//STRIP001  inline SwHTMLTableLayoutColumn *GetColumn( USHORT nCol ) const;
//STRIP001  inline void SetColumn( SwHTMLTableLayoutColumn *pCol, USHORT nCol );
//STRIP001
//STRIP001  inline SwHTMLTableLayoutCell *GetCell( USHORT nRow, USHORT nCol ) const;
//STRIP001  inline void SetCell( SwHTMLTableLayoutCell *pCell, USHORT nRow, USHORT nCol );
//STRIP001
//STRIP001  void SetLeftFillerBox( SwTableBox *pBox ) { pLeftFillerBox = pBox; }
//STRIP001  void SetRightFillerBox( SwTableBox *pBox ) { pRightFillerBox = pBox; }
//STRIP001
//STRIP001  ULONG GetMin() const { return nMin; }
//STRIP001  ULONG GetMax() const { return nMax; }
//STRIP001  USHORT GetRelLeftFill() const { return nRelLeftFill; }
//STRIP001  USHORT GetRelRightFill() const { return nRelRightFill; }
//STRIP001
//STRIP001  inline long GetBrowseWidthMin() const;
//STRIP001
//STRIP001  BOOL HasColsOption() const { return bColsOption; }
//STRIP001  BOOL HasColTags() const { return bColTags; }
//STRIP001
//STRIP001  BOOL IsTopTable() const  { return pSwTable != 0; }
//STRIP001
//STRIP001  void SetMustResize( BOOL bSet ) { bMustResize = bSet; }
//STRIP001  void SetMustNotResize( BOOL bSet ) { bMustNotResize = bSet; }
//STRIP001  void SetMustNotRecalc( BOOL bSet ) { bMustNotRecalc = bSet; }
//STRIP001
//STRIP001  // Neueberechnung der Tabellenbreiten fuer die uebergebene verfuegbare
//STRIP001  // Breite.
//STRIP001  // - Wenn bRecalc gesetzt ist, werden auch der Inhalt der Boxen
//STRIP001  //   zur Berechnung herangezogen.
//STRIP001  //   neu berechnet.
//STRIP001  // - Wenn bForce gesetzt ist, wird die Tabelle auch neu berechnet, wenn
//STRIP001  //   dies mit SetMustNotResize unterdrueckt werden soll.
//STRIP001  // - Wenn nDelay>0 wird die Berechnung entsprechend verzoegert.
//STRIP001  //   Innerhalb der Verzeoegerung auftretende Resize-Aufrufe werden
//STRIP001  //   ignoriert, die Verzeogerung wird aber ggf. uebernommen.
//STRIP001  // - Wenn nDelay==HTMLTABLE_RESIZE_NOW ist, wird sofort Resized und
//STRIP001  //   eventuell noch asstehende Resize-Aufrufe werden nicht mehr
//STRIP001  //   ausgefuehrt.
//STRIP001  // - Der Rueckgabewert gibt an, ob sich die Tabelle geaendert hat.
//STRIP001  BOOL Resize( USHORT nAbsAvail, BOOL bRecalc=FALSE, BOOL bForce=FALSE,
//STRIP001               ULONG nDelay=0 );
//STRIP001
//STRIP001  void BordersChanged( USHORT nAbsAvail, BOOL bRecalc=FALSE );
//STRIP001
//STRIP001  // Ermitteln der verfuegbaren Breite. Das geht nur, wenn ein Layout
//STRIP001  // oder eine ViewShell vorhanden ist. Sonst wird 0 zurueckgegeben.
//STRIP001  // (Wird vom HTML-Filter benoetigt, da der nicht an das Layout kommt.)
//STRIP001  static USHORT GetBrowseWidth( const SwDoc& rDoc );
//STRIP001  static USHORT GetBrowseWidthByVisArea( const SwDoc& rDoc );
//STRIP001
//STRIP001  // Ermitteln der verfuegbaren Breite uber den Tabellen-Frame
//STRIP001  USHORT GetBrowseWidthByTabFrm( const SwTabFrm& rTabFrm ) const;
//STRIP001
//STRIP001  // Ermitteln der verfuegbaren Breite uber den Tabellen-Frame oder
//STRIP001  // das statische GetBrowseWidth, wenn kein Layout existiert.
//STRIP001  USHORT GetBrowseWidthByTable( const SwDoc& rDoc ) const;
//STRIP001
//STRIP001  // Fuer Export
//STRIP001  USHORT GetWidthOption() const { return nWidthOption; }
//STRIP001  BOOL   HasPrcWidthOption() const { return bPrcWidthOption; }
//STRIP001
//STRIP001  USHORT GetCellPadding() const { return nCellPadding; }
//STRIP001  USHORT GetCellSpacing() const { return nCellSpacing; }
//STRIP001  USHORT GetBorder() const { return nBorder; }
//STRIP001
//STRIP001  USHORT GetRowCount() const { return nRows; }
//STRIP001  USHORT GetColCount() const { return nCols; }
//STRIP001
//STRIP001  void SetExportable( BOOL bSet ) { bExportable = bSet; }
//STRIP001  BOOL IsExportable() const { return bExportable; }
//STRIP001
//STRIP001  BOOL HaveBordersChanged() const { return bBordersChanged; }
//STRIP001
//STRIP001  void SetMayBeInFlyFrame( BOOL bSet ) { bMayBeInFlyFrame = bSet; }
//STRIP001  BOOL MayBeInFlyFrame() const { return bMayBeInFlyFrame; }
};

/*  */

//STRIP001 inline void SwHTMLTableLayoutCell::SetProtected()
//STRIP001 {
//STRIP001  nRowSpan = 1;
//STRIP001  nColSpan = 1;
//STRIP001
//STRIP001  pContents = 0;
//STRIP001 }

/*  */

//STRIP001 inline void SwHTMLTableLayoutColumn::MergeMinMaxNoAlign( ULONG nMin,
//STRIP001  ULONG nMax, ULONG nAbsMin )
//STRIP001 {
//STRIP001  if( nMin > nMinNoAlign )
//STRIP001      nMinNoAlign = nMin;
//STRIP001  if( nMax > nMaxNoAlign )
//STRIP001      nMaxNoAlign = nMax;
//STRIP001  if( nAbsMin > nAbsMinNoAlign )
//STRIP001      nAbsMinNoAlign = nAbsMin;
//STRIP001 }

//STRIP001 inline void SwHTMLTableLayoutColumn::ClearPass1Info( BOOL bWidthOpt )
//STRIP001 {
//STRIP001  nMinNoAlign = nMaxNoAlign = nAbsMinNoAlign = MINLAY;
//STRIP001  nMin = nMax = 0;
//STRIP001  if( bWidthOpt )
//STRIP001  {
//STRIP001      nWidthOption = 0;
//STRIP001      bRelWidthOption = FALSE;
//STRIP001  }
//STRIP001 }

//STRIP001 inline void SwHTMLTableLayoutColumn::MergeCellWidthOption(
//STRIP001  USHORT nWidth, BOOL bRel )
//STRIP001 {
//STRIP001  if( !nWidthOption ||
//STRIP001      (bRel==bRelWidthOption && nWidthOption < nWidth) )
//STRIP001  {
//STRIP001      nWidthOption = nWidth;
//STRIP001      bRelWidthOption = bRel;
//STRIP001  }
//STRIP001 }

//STRIP001 inline void SwHTMLTableLayoutColumn::SetMinMax( ULONG nMn, ULONG nMx )
//STRIP001 {
//STRIP001  nMin = nMn;
//STRIP001  nMax = nMx;
//STRIP001 }

/*  */

//STRIP001 inline USHORT SwHTMLTableLayout::GetInhCellSpace( USHORT nCol,
//STRIP001                                                USHORT nColSpan ) const
//STRIP001 {
//STRIP001  USHORT nSpace = 0;
//STRIP001  if( nCol==0 )
//STRIP001      nSpace += nInhAbsLeftSpace;
//STRIP001  if( nCol+nColSpan==nCols )
//STRIP001      nSpace += nInhAbsRightSpace;
//STRIP001
//STRIP001  return nSpace;
//STRIP001 }

//STRIP001 inline SwHTMLTableLayoutColumn *SwHTMLTableLayout::GetColumn( USHORT nCol ) const
//STRIP001 {
//STRIP001  return aColumns[nCol];
//STRIP001 }

//STRIP001 inline void SwHTMLTableLayoutColumn::SetWidthOption(
//STRIP001  USHORT nWidth, BOOL bRelWidth, BOOL bTest )
//STRIP001 {
//STRIP001  if( bTest && bRelWidthOption==bRelWidth )
//STRIP001  {
//STRIP001      if( nWidth > nWidthOption )
//STRIP001          nWidthOption = nWidth;
//STRIP001  }
//STRIP001  else
//STRIP001      nWidthOption = nWidth;
//STRIP001  bRelWidthOption = bRelWidth;
//STRIP001 }

//STRIP001 inline void SwHTMLTableLayout::SetColumn( SwHTMLTableLayoutColumn *pCol, USHORT nCol )
//STRIP001 {
//STRIP001  aColumns[nCol] = pCol;
//STRIP001 }

//STRIP001 inline SwHTMLTableLayoutCell *SwHTMLTableLayout::GetCell( USHORT nRow, USHORT nCol ) const
//STRIP001 {
//STRIP001  return aCells[nRow*nCols+nCol];
//STRIP001 }

//STRIP001 inline void SwHTMLTableLayout::SetCell( SwHTMLTableLayoutCell *pCell,
//STRIP001                             USHORT nRow, USHORT nCol )
//STRIP001 {
//STRIP001  aCells[nRow*nCols+nCol] = pCell;
//STRIP001 }

//STRIP001 inline long SwHTMLTableLayout::GetBrowseWidthMin() const
//STRIP001 {
//STRIP001  return (long)( (!nWidthOption || bPrcWidthOption) ? nMin : nRelTabWidth );
//STRIP001 }

//STRIP001 void SwHTMLTableLayout::SetInhBorderWidths( USHORT nLeft, USHORT nRight )
//STRIP001 {
//STRIP001  nInhLeftBorderWidth = nLeft;
//STRIP001  nInhRightBorderWidth = nRight;
//STRIP001 }


#endif
