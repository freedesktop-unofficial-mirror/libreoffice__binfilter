/*************************************************************************
 *
 *  $RCSfile: sw_htmltbl.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:11:22 $
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

// auto strip #include "hintids.hxx"

//#define TEST_DELAYED_RESIZE

#ifdef TEST_DELAYED_RESIZE
// auto strip #ifndef _SV_SOUND_HXX //autogen
// auto strip #include <vcl/sound.hxx>
// auto strip #endif
#endif
// auto strip #ifndef _WRKWIN_HXX //autogen
// auto strip #include <vcl/wrkwin.hxx>
// auto strip #endif
// auto strip #ifndef _APP_HXX //autogen
// auto strip #include <vcl/svapp.hxx>
// auto strip #endif
// auto strip #ifndef _SOT_STORAGE_HXX //autogen
// auto strip #include <sot/storage.hxx>
// auto strip #endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif
#ifndef _ERRHDL_HXX
#include <errhdl.hxx>
#endif

// auto strip #ifndef _FMTORNT_HXX //autogen
// auto strip #include <fmtornt.hxx>
// auto strip #endif
// auto strip #ifndef _FMTFSIZE_HXX //autogen
// auto strip #include <fmtfsize.hxx>
// auto strip #endif
// auto strip #ifndef _FRMFMT_HXX //autogen
// auto strip #include <frmfmt.hxx>
// auto strip #endif
// auto strip #ifndef _DOCARY_HXX
// auto strip #include <docary.hxx>
// auto strip #endif
// auto strip #include "ndtxt.hxx"
// auto strip #include "doc.hxx"
// auto strip #include "swtable.hxx"
// auto strip #include "rootfrm.hxx"
// auto strip #include "docsh.hxx"
// auto strip #include "flyfrm.hxx"
// auto strip #include "poolfmt.hxx"
// auto strip #include "viewsh.hxx"
// auto strip #include "tabfrm.hxx"

#include "htmltbl.hxx"
// auto strip #include "ndindex.hxx"
namespace binfilter {

#define COLFUZZY 20
#define MAX_TABWIDTH (USHRT_MAX - 2001)


/*  */

//STRIP001 class SwHTMLTableLayoutConstraints
//STRIP001 {
//STRIP001  USHORT nRow;                    // Start-Zeile
//STRIP001  USHORT nCol;                    // Start-Spalte
//STRIP001  USHORT nColSpan;                // COLSPAN der Zelle
//STRIP001
//STRIP001  SwHTMLTableLayoutConstraints *pNext;        // die naechste Bedingung
//STRIP001
//STRIP001  ULONG nMinNoAlign, nMaxNoAlign; // Zwischenergebnisse AL-Pass 1
//STRIP001
//STRIP001 public:
//STRIP001
//STRIP001  SwHTMLTableLayoutConstraints( ULONG nMin, ULONG nMax, USHORT nRow,
//STRIP001                              USHORT nCol, USHORT nColSp );
//STRIP001  ~SwHTMLTableLayoutConstraints();
//STRIP001
//STRIP001  ULONG GetMinNoAlign() const { return nMinNoAlign; }
//STRIP001  ULONG GetMaxNoAlign() const { return nMaxNoAlign; }
//STRIP001
//STRIP001  SwHTMLTableLayoutConstraints *InsertNext( SwHTMLTableLayoutConstraints *pNxt );
//STRIP001  SwHTMLTableLayoutConstraints* GetNext() const { return pNext; }
//STRIP001
//STRIP001  USHORT GetRow() const { return nRow; }
//STRIP001
//STRIP001  USHORT GetColSpan() const { return nColSpan; }
//STRIP001  USHORT GetColumn() const { return nCol; }
//STRIP001 };

/*  */

//STRIP001 SwHTMLTableLayoutCnts::SwHTMLTableLayoutCnts( const SwStartNode *pSttNd,
//STRIP001                                        SwHTMLTableLayout* pTab,
//STRIP001                                        BOOL bNoBrTag,
//STRIP001                                        SwHTMLTableLayoutCnts* pNxt ) :
//STRIP001  pNext( pNxt ), pBox( 0 ), pTable( pTab ), pStartNode( pSttNd ),
//STRIP001  nWidthSet( 0 ), nPass1Done( 0 ), bNoBreakTag( bNoBrTag )
//STRIP001 {}

//STRIP001 SwHTMLTableLayoutCnts::~SwHTMLTableLayoutCnts()
//STRIP001 {
//STRIP001  delete pNext;
//STRIP001  delete pTable;
//STRIP001 }

//STRIP001 const SwStartNode *SwHTMLTableLayoutCnts::GetStartNode() const
//STRIP001 {
//STRIP001  return pBox ? pBox->GetSttNd() : pStartNode;
//STRIP001 }


/*  */

//STRIP001 SwHTMLTableLayoutCell::SwHTMLTableLayoutCell( SwHTMLTableLayoutCnts *pCnts,
//STRIP001                                        USHORT nRSpan, USHORT nCSpan,
//STRIP001                                        USHORT nWidth, BOOL bPrcWidth,
//STRIP001                                        BOOL bNWrapOpt ) :
//STRIP001  pContents( pCnts ),
//STRIP001  nRowSpan( nRSpan ), nColSpan( nCSpan ),
//STRIP001  nWidthOption( nWidth ), bPrcWidthOption( bPrcWidth ),
//STRIP001  bNoWrapOption( bNWrapOpt )
//STRIP001 {}

//STRIP001 SwHTMLTableLayoutCell::~SwHTMLTableLayoutCell()
//STRIP001 {
//STRIP001  if( nRowSpan==1 && nColSpan==1 )
//STRIP001  {
//STRIP001      delete pContents;
//STRIP001  }
//STRIP001 }

/*  */

//STRIP001 SwHTMLTableLayoutColumn::SwHTMLTableLayoutColumn( USHORT nWidth,
//STRIP001                                                BOOL bRelWidth,
//STRIP001                                                BOOL bLBorder ) :
//STRIP001  nMinNoAlign(MINLAY), nMaxNoAlign(MINLAY), nAbsMinNoAlign(MINLAY),
//STRIP001  nMin(0), nMax(0),
//STRIP001  nAbsColWidth(0), nRelColWidth(0),
//STRIP001  nWidthOption( nWidth ), bRelWidthOption( bRelWidth ),
//STRIP001  bLeftBorder( bLBorder )
//STRIP001 {}


/*  */

//STRIP001 SwHTMLTableLayoutConstraints::SwHTMLTableLayoutConstraints(
//STRIP001  ULONG nMin, ULONG nMax, USHORT nRw, USHORT nColumn, USHORT nColSp ):
//STRIP001  nMinNoAlign( nMin ), nMaxNoAlign( nMax ),
//STRIP001  nRow( nRw ), nCol( nColumn ), nColSpan( nColSp ),
//STRIP001  pNext( 0 )
//STRIP001 {}

//STRIP001 SwHTMLTableLayoutConstraints::~SwHTMLTableLayoutConstraints()
//STRIP001 {
//STRIP001  delete pNext;
//STRIP001 }

//STRIP001 SwHTMLTableLayoutConstraints *SwHTMLTableLayoutConstraints::InsertNext(
//STRIP001  SwHTMLTableLayoutConstraints *pNxt )
//STRIP001 {
//STRIP001  SwHTMLTableLayoutConstraints *pPrev = 0;
//STRIP001  SwHTMLTableLayoutConstraints *pConstr = this;
//STRIP001  while( pConstr )
//STRIP001  {
//STRIP001      if( pConstr->GetRow() > pNxt->GetRow() ||
//STRIP001          pConstr->GetColumn() > pNxt->GetColumn() )
//STRIP001          break;
//STRIP001      pPrev = pConstr;
//STRIP001      pConstr = pConstr->GetNext();
//STRIP001  }
//STRIP001
//STRIP001  if( pPrev )
//STRIP001  {
//STRIP001      pNxt->pNext = pPrev->GetNext();
//STRIP001      pPrev->pNext = pNxt;
//STRIP001      pConstr = this;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pNxt->pNext = this;
//STRIP001      pConstr = pNxt;
//STRIP001  }
//STRIP001
//STRIP001  return pConstr;
//STRIP001 }

/*  */

//STRIP001 typedef SwHTMLTableLayoutColumn *SwHTMLTableLayoutColumnPtr;
//STRIP001 typedef SwHTMLTableLayoutCell *SwHTMLTableLayoutCellPtr;

/*N*/ SwHTMLTableLayout::SwHTMLTableLayout(
/*N*/                       const SwTable * pSwTbl,
/*N*/                       USHORT nRws, USHORT nCls, BOOL bColsOpt, BOOL bColTgs,
/*N*/                       USHORT nWdth, BOOL bPrcWdth, USHORT nBorderOpt,
/*N*/                       USHORT nCellPad, USHORT nCellSp, SvxAdjust eAdjust,
/*N*/                       USHORT nLMargin, USHORT nRMargin,
/*N*/                       USHORT nBWidth, USHORT nLeftBWidth,
/*N*/                       USHORT nRightBWidth,
/*N*/                       USHORT nInhLeftBWidth, USHORT nInhRightBWidth ) //STRIP001 :
//STRIP001  aColumns( new SwHTMLTableLayoutColumnPtr[nCls] ),
//STRIP001  aCells( new SwHTMLTableLayoutCellPtr[nRws*nCls] ),
//STRIP001  pSwTable( pSwTbl ), pLeftFillerBox( 0 ), pRightFillerBox( 0 ),
//STRIP001  nMin( 0 ), nMax( 0 ),
//STRIP001  nRows( nRws ), nCols( nCls ),
//STRIP001  nLeftMargin( nLMargin ), nRightMargin( nRMargin ),
//STRIP001  nCellPadding( nCellPad ), nCellSpacing( nCellSp ), nBorder( nBorderOpt ),
//STRIP001  nBorderWidth( nBWidth ),
//STRIP001  nLeftBorderWidth( nLeftBWidth ), nRightBorderWidth( nRightBWidth ),
//STRIP001  nInhLeftBorderWidth( nInhLeftBWidth ),
//STRIP001  nInhRightBorderWidth( nInhRightBWidth ),
//STRIP001  nRelLeftFill( 0 ), nRelRightFill( 0 ),
//STRIP001  nInhAbsLeftSpace( 0 ), nInhAbsRightSpace( 0 ),
//STRIP001  nRelTabWidth( 0 ), nWidthOption( nWdth ),
//STRIP001  nDelayedResizeAbsAvail( 0 ), nLastResizeAbsAvail( 0 ),
//STRIP001  nPass1Done( 0 ), nWidthSet( 0 ), eTableAdjust( eAdjust ),
//STRIP001  bColsOption( bColsOpt ), bColTags( bColTgs ),
//STRIP001  bPrcWidthOption( bPrcWdth ), bUseRelWidth( FALSE ),
//STRIP001  bMustResize( TRUE ), bExportable( TRUE ), bBordersChanged( FALSE ),
//STRIP001  bMustNotResize( FALSE ), bMustNotRecalc( FALSE )
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  aResizeTimer.SetTimeoutHdl( STATIC_LINK( this, SwHTMLTableLayout,
//STRIP001                                           DelayedResize_Impl ) );
/*N*/ }

/*N*/ SwHTMLTableLayout::~SwHTMLTableLayout()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  for( USHORT i=0; i<nCols; i++ )
//STRIP001      delete aColumns[i];
//STRIP001  delete[] aColumns;
//STRIP001
//STRIP001  USHORT nCount = nRows*nCols;
//STRIP001  for( i=0; i<nCount; i++ )
//STRIP001      delete aCells[i];
//STRIP001  delete[] aCells;
/*N*/ }

#ifdef USED
//STRIP001 USHORT SwHTMLTableLayout::GetLeftBorderWidth( USHORT nCol ) const
//STRIP001 {
//STRIP001  SwHTMLTableLayoutColumn *pColumn = GetColumn( nCol );
//STRIP001
//STRIP001  USHORT nBWidth = 0;
//STRIP001  if( pColumn->HasLeftBorder() )
//STRIP001  {
//STRIP001      nBWidth = nCol==0 ? nLeftBorderWidth : nBorderWidth;
//STRIP001  }
//STRIP001  if( nCol==0 && nInhLeftBorderWidth > nBWidth )
//STRIP001  {
//STRIP001      nBWidth = nInhLeftBorderWidth;
//STRIP001  }
//STRIP001
//STRIP001  return nBWidth;
//STRIP001 }

//STRIP001 USHORT SwHTMLTableLayout::GetRightBorderWidth( USHORT nCol, USHORT nColSpan ) const
//STRIP001 {
//STRIP001  USHORT nBWidth = 0;
//STRIP001
//STRIP001  if( nCol+nColSpan==nCols )
//STRIP001  {
//STRIP001      nBWidth = nInhRightBorderWidth > nRightBorderWidth
//STRIP001          ? nInhRightBorderWidth
//STRIP001          : nRightBorderWidth;
//STRIP001  }
//STRIP001
//STRIP001  return nBWidth;
//STRIP001 }
#endif

// Die Breiten der Umrandung werden zunaechst wie in Netscape berechnet:
// Aussere Umrandung: BORDER + CELLSPACING + CELLPADDING
// Innere Umrandung: CELLSPACING + CELLPADDING
// Allerdings wird die Breite der Umrandung im SW trotzdem beachtet, wenn
// bSwBorders gesetzt ist, damit nicht faellschlich umgebrochen wird.
// MIB 27.6.97: Dabei muss auch der Abstand zum Inhalt berueckichtigt werden,
// und zwar auch dann, wenn wenn nur die gegenueberliegende Seite
// eine Umrandung hat.
//STRIP001 USHORT SwHTMLTableLayout::GetLeftCellSpace( USHORT nCol, USHORT nColSpan,
//STRIP001                                          BOOL bSwBorders ) const
//STRIP001 {
//STRIP001  USHORT nSpace = nCellSpacing + nCellPadding;
//STRIP001
//STRIP001  if( nCol == 0 )
//STRIP001  {
//STRIP001      nSpace += nBorder;
//STRIP001
//STRIP001      if( bSwBorders && nSpace < nLeftBorderWidth )
//STRIP001          nSpace = nLeftBorderWidth;
//STRIP001  }
//STRIP001  else if( bSwBorders )
//STRIP001  {
//STRIP001      if( GetColumn(nCol)->HasLeftBorder() )
//STRIP001      {
//STRIP001          if( nSpace < nBorderWidth )
//STRIP001              nSpace = nBorderWidth;
//STRIP001      }
//STRIP001      else if( nCol+nColSpan == nCols && nRightBorderWidth &&
//STRIP001               nSpace < MIN_BORDER_DIST )
//STRIP001      {
//STRIP001          ASSERT( !nCellPadding, "GetLeftCellSpace: CELLPADDING!=0" );
//STRIP001          // Wenn die Gegenueberliegende Seite umrandet ist muessen
//STRIP001          // wir zumindest den minimalen Abstand zum Inhalt
//STRIP001          // beruecksichtigen. (Koennte man zusaetzlich auch an
//STRIP001          // nCellPadding festmachen.)
//STRIP001          nSpace = MIN_BORDER_DIST;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return nSpace;
//STRIP001 }

//STRIP001 USHORT SwHTMLTableLayout::GetRightCellSpace( USHORT nCol, USHORT nColSpan,
//STRIP001                                           BOOL bSwBorders ) const
//STRIP001 {
//STRIP001  USHORT nSpace = nCellPadding;
//STRIP001
//STRIP001  if( nCol+nColSpan == nCols )
//STRIP001  {
//STRIP001      nSpace += nBorder + nCellSpacing;
//STRIP001      if( bSwBorders && nSpace < nRightBorderWidth )
//STRIP001          nSpace = nRightBorderWidth;
//STRIP001  }
//STRIP001  else if( bSwBorders && GetColumn(nCol)->HasLeftBorder() &&
//STRIP001           nSpace < MIN_BORDER_DIST )
//STRIP001  {
//STRIP001      ASSERT( !nCellPadding, "GetRightCellSpace: CELLPADDING!=0" );
//STRIP001      // Wenn die Gegenueberliegende Seite umrandet ist muessen
//STRIP001      // wir zumindest den minimalen Abstand zum Inhalt
//STRIP001      // beruecksichtigen. (Koennte man zusaetzlich auch an
//STRIP001      // nCellPadding festmachen.)
//STRIP001      nSpace = MIN_BORDER_DIST;
//STRIP001  }
//STRIP001
//STRIP001  return nSpace;
//STRIP001 }

//STRIP001 void SwHTMLTableLayout::AddBorderWidth( ULONG &rMin, ULONG &rMax,
//STRIP001                                      ULONG &rAbsMin,
//STRIP001                                      USHORT nCol, USHORT nColSpan,
//STRIP001                                      BOOL bSwBorders ) const
//STRIP001 {
//STRIP001  ULONG nAdd = GetLeftCellSpace( nCol, nColSpan, bSwBorders ) +
//STRIP001               GetRightCellSpace( nCol, nColSpan, bSwBorders );
//STRIP001
//STRIP001  rMin += nAdd;
//STRIP001  rMax += nAdd;
//STRIP001  rAbsMin += nAdd;
//STRIP001
//STRIP001 #if 0
//STRIP001  // Diese Breiten-Berchnung orientiert sich an den SW-Umrandungen!!!
//STRIP001  USHORT nBDist = nCellPadding;
//STRIP001
//STRIP001  // linke Umrandung beruecksichtigen
//STRIP001  USHORT nBorderWidth = GetLeftBorderWidth( nCol );
//STRIP001  if( nBorderWidth )
//STRIP001  {
//STRIP001      rMin += nBorderWidth;
//STRIP001      rMax += nBorderWidth;
//STRIP001      rAbsMin += nBorderWidth;
//STRIP001      if( !nBDist )
//STRIP001          nBDist = MIN_BORDER_DIST;
//STRIP001  }
//STRIP001
//STRIP001  // rechte Umrandung beruecksichtigen
//STRIP001  nBorderWidth = GetRightBorderWidth( nCol, nColSpan );
//STRIP001  if( nBorderWidth )
//STRIP001  {
//STRIP001      rMin += nBorderWidth;
//STRIP001      rMax += nBorderWidth;
//STRIP001      rAbsMin += nBorderWidth;
//STRIP001      if( !nBDist )
//STRIP001          nBDist = MIN_BORDER_DIST;
//STRIP001  }
//STRIP001
//STRIP001  // Abstand zum Inhalt beruecksichtigen
//STRIP001  rMin += 2*nBDist;
//STRIP001  rMax += 2*nBDist;
//STRIP001  rAbsMin += 2*nBDist;
//STRIP001 #endif
//STRIP001 }

//STRIP001 void SwHTMLTableLayout::SetBoxWidth( SwTableBox *pBox, USHORT nCol,
//STRIP001                           USHORT nColSpan ) const
//STRIP001 {
//STRIP001  SwFrmFmt *pFrmFmt = pBox->GetFrmFmt();
//STRIP001
//STRIP001  // die Breite der Box berechnen
//STRIP001  SwTwips nFrmWidth = 0;
//STRIP001  while( nColSpan-- )
//STRIP001      nFrmWidth += GetColumn( nCol++ )->GetRelColWidth();
//STRIP001
//STRIP001  // und neu setzen
//STRIP001
//STRIP001  pFrmFmt->SetAttr( SwFmtFrmSize( ATT_VAR_SIZE, nFrmWidth, 0 ));
//STRIP001 }

//STRIP001 void SwHTMLTableLayout::GetAvail( USHORT nCol, USHORT nColSpan,
//STRIP001                                USHORT& rAbsAvail, USHORT& rRelAvail ) const
//STRIP001 {
//STRIP001  rAbsAvail = 0;
//STRIP001  rRelAvail = 0;
//STRIP001  for( USHORT i=nCol; i<nCol+nColSpan;i++ )
//STRIP001  {
//STRIP001      const SwHTMLTableLayoutColumn *pColumn = GetColumn(i);
//STRIP001      rAbsAvail += pColumn->GetAbsColWidth();
//STRIP001      rRelAvail += pColumn->GetRelColWidth();
//STRIP001  }
//STRIP001
//STRIP001 #if 0
//STRIP001  rAbsSpace = GetLeftBorderWidth( nCol ) +
//STRIP001              GetRightBorderWidth( nCol, nColSpan ) +
//STRIP001              2*nCellPadding;
//STRIP001 #endif
//STRIP001 }

//STRIP001 USHORT SwHTMLTableLayout::GetBrowseWidthByVisArea( const SwDoc& rDoc )
//STRIP001 {
//STRIP001  ViewShell *pVSh = 0;
//STRIP001  rDoc.GetEditShell( &pVSh );
//STRIP001  if( pVSh )
//STRIP001  {
//STRIP001      return (USHORT)( pVSh->VisArea().Width() -
//STRIP001         2*pVSh->GetOut()->PixelToLogic( pVSh->GetBrowseBorder() ).Width() );
//STRIP001  }
//STRIP001
//STRIP001  return 0;
//STRIP001 }

//STRIP001 USHORT SwHTMLTableLayout::GetBrowseWidth( const SwDoc& rDoc )
//STRIP001 {
//STRIP001  // Wenn ein Layout da ist, koennen wir die Breite dort herholen.
//STRIP001  const SwRootFrm *pRootFrm = rDoc.GetRootFrm();
//STRIP001  if( pRootFrm )
//STRIP001  {
//STRIP001      const SwFrm *pPageFrm = pRootFrm->GetLower();
//STRIP001      if( pPageFrm )
//STRIP001          return (USHORT)pPageFrm->Prt().Width();
//STRIP001  }
//STRIP001
//STRIP001  // Sonst versuchen wir es ueber die ViewShell
//STRIP001  USHORT nWidth = GetBrowseWidthByVisArea( rDoc );
//STRIP001  if( !nWidth )
//STRIP001  {
//STRIP001      // Und wenn das auch nicht geht, gibt es noch die ActualSize an der
//STRIP001      // DocShell.
//STRIP001      if( rDoc.GetDocShell() && GetpApp() && GetpApp()->GetDefaultDevice() )
//STRIP001      {
//STRIP001          nWidth = (USHORT)Application::GetDefaultDevice()
//STRIP001                  ->PixelToLogic( rDoc.GetDocShell()->GetActualSize(),
//STRIP001                                  MapMode( MAP_TWIP ) ).Width();
//STRIP001
//STRIP001          ASSERT( nWidth, "GetActualSize liefert 0" );
//STRIP001      }
//STRIP001 #ifndef PRODUCT
//STRIP001      else
//STRIP001      {
//STRIP001          // und wenn das auch nicht klappt, gibt es zur Zeit keine Breite
//STRIP001          ASSERT( nWidth, "Nix da um eine Browse-Breite zu berechnen" );
//STRIP001      }
//STRIP001 #endif
//STRIP001  }
//STRIP001  return nWidth;
//STRIP001 }

//STRIP001 USHORT SwHTMLTableLayout::GetBrowseWidthByTabFrm(
//STRIP001  const SwTabFrm& rTabFrm ) const
//STRIP001 {
//STRIP001  SwTwips nWidth = 0;
//STRIP001
//STRIP001  const SwFrm *pUpper = rTabFrm.GetUpper();
//STRIP001  if( MayBeInFlyFrame() && pUpper->IsFlyFrm() &&
//STRIP001      ((const SwFlyFrm *)pUpper)->GetAnchor() )
//STRIP001  {
//STRIP001      // Wenn die Tabelle in einem selbst angelegten Rahmen steht, dann ist
//STRIP001      // die Breite Ankers und nicht die Breite Rahmens von Bedeutung.
//STRIP001      // Bei Absatz-gebundenen Rahmen werden Absatz-Einzuege nicht beachtet.
//STRIP001      const SwFrm *pAnchor = ((const SwFlyFrm *)pUpper)->GetAnchor();
//STRIP001      if( pAnchor->IsTxtFrm() )
//STRIP001          nWidth = pAnchor->Frm().Width();
//STRIP001      else
//STRIP001          nWidth = pAnchor->Prt().Width();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      nWidth = pUpper->Prt().Width();
//STRIP001  }
//STRIP001
//STRIP001  SwTwips nUpperDummy = 0;
//STRIP001  long nRightOffset = 0,
//STRIP001       nLeftOffset  = 0;
//STRIP001  rTabFrm.CalcFlyOffsets( nUpperDummy, nLeftOffset, nRightOffset );
//STRIP001  nWidth -= (nLeftOffset + nRightOffset);
//STRIP001
//STRIP001  return nWidth < USHRT_MAX ? nWidth : USHRT_MAX;
//STRIP001 }

//STRIP001 USHORT SwHTMLTableLayout::GetBrowseWidthByTable( const SwDoc& rDoc ) const
//STRIP001 {
//STRIP001  USHORT nBrowseWidth = 0;
//STRIP001  SwClientIter aIter( *(SwModify*)pSwTable->GetFrmFmt() );
//STRIP001  SwClient* pCli = aIter.First( TYPE( SwTabFrm ));
//STRIP001  if( pCli )
//STRIP001  {
//STRIP001      nBrowseWidth = GetBrowseWidthByTabFrm( *(SwTabFrm*)pCli );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      nBrowseWidth = SwHTMLTableLayout::GetBrowseWidth( rDoc );
//STRIP001  }
//STRIP001
//STRIP001  return nBrowseWidth;
//STRIP001 }

//STRIP001 const SwStartNode *SwHTMLTableLayout::GetAnyBoxStartNode() const
//STRIP001 {
//STRIP001  const SwStartNode *pBoxSttNd;
//STRIP001
//STRIP001  const SwTableBox* pBox = pSwTable->GetTabLines()[0]->GetTabBoxes()[0];
//STRIP001  while( 0 == (pBoxSttNd = pBox->GetSttNd()) )
//STRIP001  {
//STRIP001      ASSERT( pBox->GetTabLines().Count() > 0,
//STRIP001              "Box ohne Start-Node und Lines" );
//STRIP001      ASSERT( pBox->GetTabLines()[0]->GetTabBoxes().Count() > 0,
//STRIP001              "Line ohne Boxen" );
//STRIP001      pBox = pBox->GetTabLines()[0]->GetTabBoxes()[0];
//STRIP001  }
//STRIP001
//STRIP001  return pBoxSttNd;
//STRIP001 }

//STRIP001 SwFrmFmt *SwHTMLTableLayout::FindFlyFrmFmt() const
//STRIP001 {
//STRIP001  const SwTableNode *pTblNd = GetAnyBoxStartNode()->FindTableNode();
//STRIP001  ASSERT( pTblNd, "Kein Table-Node?" );
//STRIP001  return pTblNd->GetFlyFmt();
//STRIP001 }

//STRIP001 void lcl_GetMinMaxSize( ULONG& rMinNoAlignCnts, ULONG& rMaxNoAlignCnts,
//STRIP001                      ULONG& rAbsMinNoAlignCnts,
//STRIP001 #ifdef FIX41370
//STRIP001                      BOOL& rHR,
//STRIP001 #endif
//STRIP001                      SwTxtNode *pTxtNd, ULONG nIdx, BOOL bNoBreak )
//STRIP001 {
//STRIP001  pTxtNd->GetMinMaxSize( nIdx, rMinNoAlignCnts, rMaxNoAlignCnts,
//STRIP001                         rAbsMinNoAlignCnts );
//STRIP001  ASSERT( rAbsMinNoAlignCnts <= rMinNoAlignCnts,
//STRIP001          "GetMinMaxSize: absmin > min" );
//STRIP001  ASSERT( rMinNoAlignCnts <= rMaxNoAlignCnts,
//STRIP001          "GetMinMaxSize: max > min" );
//STRIP001
//STRIP001  //Bei einen <PRE>-Absatz entspricht die maximale Breite der
//STRIP001  // minimalen breite
//STRIP001  const SwFmtColl *pColl = &pTxtNd->GetAnyFmtColl();
//STRIP001  while( pColl && !pColl->IsDefault() &&
//STRIP001          (USER_FMT & pColl->GetPoolFmtId()) )
//STRIP001  {
//STRIP001      pColl = (const SwFmtColl *)pColl->DerivedFrom();
//STRIP001  }
//STRIP001
//STRIP001  // <NOBR> in der gesamten Zelle bezieht sich auf Text, aber nicht
//STRIP001  // auf Tabellen. Netscape beruecksichtigt dies nur fuer Grafiken.
//STRIP001  if( (pColl && RES_POOLCOLL_HTML_PRE==pColl->GetPoolFmtId()) || bNoBreak )
//STRIP001  {
//STRIP001      rMinNoAlignCnts = rMaxNoAlignCnts;
//STRIP001      rAbsMinNoAlignCnts = rMaxNoAlignCnts;
//STRIP001  }
//STRIP001 #ifdef FIX41370
//STRIP001  else if( pColl && RES_POOLCOLL_HTML_HR==pColl->GetPoolFmtId() )
//STRIP001  {
//STRIP001      rHR |= !pTxtNd->GetpSwAttrSet() ||
//STRIP001              SFX_ITEM_SET != pTxtNd->GetpSwAttrSet()
//STRIP001                                    ->GetItemState( RES_LR_SPACE, FALSE );
//STRIP001  }
//STRIP001 #endif
//STRIP001 }

//STRIP001 void SwHTMLTableLayout::AutoLayoutPass1()
//STRIP001 {
//STRIP001  nPass1Done++;
//STRIP001
//STRIP001  ClearPass1Info();
//STRIP001
//STRIP001  BOOL bFixRelWidths = FALSE;
//STRIP001  USHORT i;
//STRIP001
//STRIP001  SwHTMLTableLayoutConstraints *pConstraints = 0;
//STRIP001
//STRIP001  for( i=0; i<nCols; i++ )
//STRIP001  {
//STRIP001      SwHTMLTableLayoutColumn *pColumn = GetColumn( i );
//STRIP001      pColumn->ClearPass1Info( !HasColTags() );
//STRIP001      USHORT nMinColSpan = USHRT_MAX; // Spaltenzahl, auf die sich dir
//STRIP001                                      // berechnete Breite bezieht
//STRIP001      USHORT nColSkip = USHRT_MAX;    // Wie viele Spalten muessen
//STRIP001                                      // uebersprungen werden
//STRIP001
//STRIP001      for( USHORT j=0; j<nRows; j++ )
//STRIP001      {
//STRIP001          SwHTMLTableLayoutCell *pCell = GetCell(j,i);
//STRIP001          SwHTMLTableLayoutCnts *pCnts = pCell->GetContents();
//STRIP001
//STRIP001          // fix #31488#: Zum Ermitteln der naechsten zu berechnenden
//STRIP001          // Spalte muessen alle Zeilen herangezogen werden
//STRIP001          USHORT nColSpan = pCell->GetColSpan();
//STRIP001          if( nColSpan < nColSkip )
//STRIP001              nColSkip = nColSpan;
//STRIP001
//STRIP001          if( !pCnts || (pCnts && !pCnts->IsPass1Done(nPass1Done)) )
//STRIP001          {
//STRIP001              // die Zelle ist leer oder ihr Inhalt wurde nich nicht
//STRIP001              // bearbeitet
//STRIP001              if( nColSpan < nMinColSpan )
//STRIP001                  nMinColSpan = nColSpan;
//STRIP001
//STRIP001              ULONG nMinNoAlignCell = 0;
//STRIP001              ULONG nMaxNoAlignCell = 0;
//STRIP001              ULONG nAbsMinNoAlignCell = 0;
//STRIP001              ULONG nMaxTableCell = 0;
//STRIP001              ULONG nAbsMinTableCell = 0;
//STRIP001 #ifdef FIX41370
//STRIP001              BOOL bHR = FALSE;
//STRIP001 #endif
//STRIP001
//STRIP001              while( pCnts )
//STRIP001              {
//STRIP001                  const SwStartNode *pSttNd = pCnts->GetStartNode();
//STRIP001                  if( pSttNd )
//STRIP001                  {
//STRIP001                      const SwDoc *pDoc = pSttNd->GetDoc();
//STRIP001                      ULONG nIdx = pSttNd->GetIndex();
//STRIP001                      while( !(pDoc->GetNodes()[nIdx])->IsEndNode() )
//STRIP001                      {
//STRIP001                          SwTxtNode *pTxtNd = (pDoc->GetNodes()[nIdx])->GetTxtNode();
//STRIP001                          if( pTxtNd )
//STRIP001                          {
//STRIP001                              ULONG nMinNoAlignCnts;
//STRIP001                              ULONG nMaxNoAlignCnts;
//STRIP001                              ULONG nAbsMinNoAlignCnts;
//STRIP001
//STRIP001                              lcl_GetMinMaxSize( nMinNoAlignCnts,
//STRIP001                                                 nMaxNoAlignCnts,
//STRIP001                                                 nAbsMinNoAlignCnts,
//STRIP001 #ifdef FIX41370
//STRIP001                                                 bHR,
//STRIP001 #endif
//STRIP001                                                 pTxtNd, nIdx,
//STRIP001                                                 pCnts->HasNoBreakTag() );
//STRIP001
//STRIP001                              if( nMinNoAlignCnts > nMinNoAlignCell )
//STRIP001                                  nMinNoAlignCell = nMinNoAlignCnts;
//STRIP001                              if( nMaxNoAlignCnts > nMaxNoAlignCell )
//STRIP001                                  nMaxNoAlignCell = nMaxNoAlignCnts;
//STRIP001                              if( nAbsMinNoAlignCnts > nAbsMinNoAlignCell )
//STRIP001                                  nAbsMinNoAlignCell = nAbsMinNoAlignCnts;
//STRIP001                          }
//STRIP001                          nIdx++;
//STRIP001                      }
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      SwHTMLTableLayout *pChild = pCnts->GetTable();
//STRIP001                      pChild->AutoLayoutPass1();
//STRIP001                      ULONG nMaxTableCnts = pChild->nMax;
//STRIP001                      ULONG nAbsMinTableCnts = pChild->nMin;
//STRIP001
//STRIP001                      // Eine feste Tabellen-Breite wird als Minimum
//STRIP001                      // und Maximum gleichzeitig uebernommen
//STRIP001                      if( !pChild->bPrcWidthOption && pChild->nWidthOption )
//STRIP001                      {
//STRIP001                          ULONG nTabWidth = pChild->nWidthOption;
//STRIP001                          if( nTabWidth >= nAbsMinTableCnts  )
//STRIP001                          {
//STRIP001                              nMaxTableCnts = nTabWidth;
//STRIP001                              nAbsMinTableCnts = nTabWidth;
//STRIP001                          }
//STRIP001                          else
//STRIP001                          {
//STRIP001                              nMaxTableCnts = nAbsMinTableCnts;
//STRIP001                          }
//STRIP001                      }
//STRIP001
//STRIP001                      if( nMaxTableCnts > nMaxTableCell )
//STRIP001                          nMaxTableCell = nMaxTableCnts;
//STRIP001                      if( nAbsMinTableCnts > nAbsMinTableCell )
//STRIP001                          nAbsMinTableCell = nAbsMinTableCnts;
//STRIP001                  }
//STRIP001                  pCnts->SetPass1Done( nPass1Done );
//STRIP001                  pCnts = pCnts->GetNext();
//STRIP001              }
//STRIP001
//STRIP001 // War frueher hinter AddBorderWidth
//STRIP001              // Wenn die Breite einer Tabelle in der Zelle breiter ist als
//STRIP001              // das, was wir fuer sonstigen Inhalt berechnet haben, mussen
//STRIP001              // wir die Breite der Tabelle nutzen
//STRIP001              if( nMaxTableCell > nMaxNoAlignCell )
//STRIP001                  nMaxNoAlignCell = nMaxTableCell;
//STRIP001              if( nAbsMinTableCell > nAbsMinNoAlignCell )
//STRIP001              {
//STRIP001                  nAbsMinNoAlignCell = nAbsMinTableCell;
//STRIP001                  if( nMinNoAlignCell < nAbsMinNoAlignCell )
//STRIP001                      nMinNoAlignCell = nAbsMinNoAlignCell;
//STRIP001                  if( nMaxNoAlignCell < nMinNoAlignCell )
//STRIP001                      nMaxNoAlignCell = nMinNoAlignCell;
//STRIP001              }
//STRIP001 // War frueher hinter AddBorderWidth
//STRIP001
//STRIP001              BOOL bRelWidth = pCell->IsPrcWidthOption();
//STRIP001              USHORT nWidth = pCell->GetWidthOption();
//STRIP001
//STRIP001              // Eine NOWRAP-Option bezieht sich auf Text und auf
//STRIP001              // Tabellen, wird aber bei fester Zellenbreite
//STRIP001              // nicht uebernommen. Stattdessen wirkt die angegebene
//STRIP001              // Zellenbreite wie eine Mindestbreite.
//STRIP001              if( pCell->HasNoWrapOption() )
//STRIP001              {
//STRIP001                  if( nWidth==0 || bRelWidth )
//STRIP001                  {
//STRIP001                      nMinNoAlignCell = nMaxNoAlignCell;
//STRIP001                      nAbsMinNoAlignCell = nMaxNoAlignCell;
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      if( nWidth>nMinNoAlignCell )
//STRIP001                          nMinNoAlignCell = nWidth;
//STRIP001                      if( nWidth>nAbsMinNoAlignCell )
//STRIP001                          nAbsMinNoAlignCell = nWidth;
//STRIP001                  }
//STRIP001              }
//STRIP001 #ifdef FIX41370
//STRIP001              else if( bHR && nWidth>0 && !bRelWidth )
//STRIP001              {
//STRIP001                  // Ein kleiner Hack, um einen Bug in Netscape 4.0
//STRIP001                  // nachzubilden (siehe #41370#). Wenn eine Zelle eine
//STRIP001                  // fixe Breite besitzt und gleichzeitig ein HR, wird
//STRIP001                  // sie nie schmaler als die angegebene Breite.
//STRIP001                  // (Genaugenomen scheint die Zelle nie schmaler zu werden
//STRIP001                  // als die HR-Linie, denn wenn man fuer die Linie eine
//STRIP001                  // Breite angibt, die breiter ist als die der Zelle, dann
//STRIP001                  // wird die Zelle so breit wie die Linie. Das bekommen wir
//STRIP001                  // natuerlich nicht hin.)
//STRIP001                  if( nWidth>nMinNoAlignCell )
//STRIP001                      nMinNoAlignCell = nWidth;
//STRIP001                  if( nWidth>nAbsMinNoAlignCell )
//STRIP001                      nAbsMinNoAlignCell = nWidth;
//STRIP001              }
//STRIP001 #endif
//STRIP001
//STRIP001              // Mindestbreite fuer Inhalt einhalten
//STRIP001              if( nMinNoAlignCell < MINLAY )
//STRIP001                  nMinNoAlignCell = MINLAY;
//STRIP001              if( nMaxNoAlignCell < MINLAY )
//STRIP001                  nMaxNoAlignCell = MINLAY;
//STRIP001              if( nAbsMinNoAlignCell < MINLAY )
//STRIP001                  nAbsMinNoAlignCell = MINLAY;
//STRIP001
//STRIP001              // Umrandung und Abstand zum Inhalt beachten.
//STRIP001              AddBorderWidth( nMinNoAlignCell, nMaxNoAlignCell,
//STRIP001                              nAbsMinNoAlignCell, i, nColSpan );
//STRIP001
//STRIP001              if( 1==nColSpan )
//STRIP001              {
//STRIP001                  // die Werte direkt uebernehmen
//STRIP001                  pColumn->MergeMinMaxNoAlign( nMinNoAlignCell,
//STRIP001                                               nMaxNoAlignCell,
//STRIP001                                               nAbsMinNoAlignCell );
//STRIP001
//STRIP001                  // bei den WIDTH angaben gewinnt die breiteste
//STRIP001                  if( !HasColTags() )
//STRIP001                      pColumn->MergeCellWidthOption( nWidth, bRelWidth );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  // die Angaben erst am Ende, und zwar zeilenweise von
//STRIP001                  // links nach rechts bearbeiten
//STRIP001
//STRIP001                  // Wann welche Werte wie uebernommen werden ist weiter
//STRIP001                  // unten erklaert.
//STRIP001                  if( !HasColTags() && nWidth && !bRelWidth )
//STRIP001                  {
//STRIP001                      ULONG nAbsWidth = nWidth, nDummy = 0, nDummy2 = 0;
//STRIP001                      AddBorderWidth( nAbsWidth, nDummy, nDummy2,
//STRIP001                                      i, nColSpan, FALSE );
//STRIP001
//STRIP001                      if( nAbsWidth >= nMinNoAlignCell )
//STRIP001                      {
//STRIP001                          nMaxNoAlignCell = nAbsWidth;
//STRIP001                          if( HasColsOption() )
//STRIP001                              nMinNoAlignCell = nAbsWidth;
//STRIP001                      }
//STRIP001                      else if( nAbsWidth >= nAbsMinNoAlignCell )
//STRIP001                      {
//STRIP001                          nMaxNoAlignCell = nAbsWidth;
//STRIP001                          nMinNoAlignCell = nAbsWidth;
//STRIP001                      }
//STRIP001                      else
//STRIP001                      {
//STRIP001                          nMaxNoAlignCell = nAbsMinNoAlignCell;
//STRIP001                          nMinNoAlignCell = nAbsMinNoAlignCell;
//STRIP001                      }
//STRIP001                  }
//STRIP001                  else if( HasColsOption() || HasColTags() )
//STRIP001                      nMinNoAlignCell = nAbsMinNoAlignCell;
//STRIP001
//STRIP001                  SwHTMLTableLayoutConstraints *pConstr =
//STRIP001                      new SwHTMLTableLayoutConstraints( nMinNoAlignCell,
//STRIP001                          nMaxNoAlignCell, j, i, nColSpan );
//STRIP001                  if( pConstraints )
//STRIP001                      pConstraints = pConstraints->InsertNext( pConstr );
//STRIP001                  else
//STRIP001                      pConstraints = pConstr;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      ASSERT( nMinColSpan>0 && nColSkip>0 && nColSkip <= nMinColSpan,
//STRIP001              "Layout Pass 1: Da werden Spalten vergessen!" );
//STRIP001      ASSERT( nMinColSpan!=USHRT_MAX,
//STRIP001              "Layout Pass 1: unnoetiger Schleifendurchlauf oder Bug" );
//STRIP001
//STRIP001      if( 1==nMinColSpan )
//STRIP001      {
//STRIP001          // es gibt Zellen mit COLSPAN 1 und demnach auch sinnvolle
//STRIP001          // Werte in pColumn
//STRIP001
//STRIP001          // Werte anhand folgender Tabelle (Netscape 4.0 pv 3) uebernehmen:
//STRIP001          //
//STRIP001          // WIDTH:           kein COLS       COLS
//STRIP001          //
//STRIP001          // keine            min = min       min = absmin
//STRIP001          //                  max = max       max = max
//STRIP001          //
//STRIP001          // >= min           min = min       min = width
//STRIP001          //                  max = width     max = width
//STRIP001          //
//STRIP001          // >= absmin        min = wdith(*)  min = width
//STRIP001          //                  max = width     max = width
//STRIP001          //
//STRIP001          // < absmin         min = absmin    min = absmin
//STRIP001          //                  max = absmin    max = absmin
//STRIP001          //
//STRIP001          // (*) Netscape benutzt hier die Mindestbreite ohne einen
//STRIP001          //     Umbruch vor der letzten Grafik. Haben wir (noch?) nicht,
//STRIP001          //     also belassen wir es bei width.^
//STRIP001
//STRIP001          if( pColumn->GetWidthOption() && !pColumn->IsRelWidthOption() )
//STRIP001          {
//STRIP001              // absolute Breiten als Minimal- und Maximalbreite
//STRIP001              // uebernehmen.
//STRIP001              ULONG nAbsWidth = pColumn->GetWidthOption();
//STRIP001              ULONG nDummy = 0, nDummy2 = 0;
//STRIP001              AddBorderWidth( nAbsWidth, nDummy, nDummy2, i, 1, FALSE );
//STRIP001
//STRIP001              if( nAbsWidth >= pColumn->GetMinNoAlign() )
//STRIP001              {
//STRIP001                  pColumn->SetMinMax( HasColsOption() ? nAbsWidth
//STRIP001                                                 : pColumn->GetMinNoAlign(),
//STRIP001                                      nAbsWidth );
//STRIP001              }
//STRIP001              else if( nAbsWidth >= pColumn->GetAbsMinNoAlign() )
//STRIP001              {
//STRIP001                  pColumn->SetMinMax( nAbsWidth, nAbsWidth );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  pColumn->SetMinMax( pColumn->GetAbsMinNoAlign(),
//STRIP001                                      pColumn->GetAbsMinNoAlign() );
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              pColumn->SetMinMax( HasColsOption() ? pColumn->GetAbsMinNoAlign()
//STRIP001                                             : pColumn->GetMinNoAlign(),
//STRIP001                                  pColumn->GetMaxNoAlign() );
//STRIP001          }
//STRIP001      }
//STRIP001      else if( USHRT_MAX!=nMinColSpan )
//STRIP001      {
//STRIP001          // kann irgendwas !=0 sein, weil es durch die Constraints
//STRIP001          // angepasst wird.
//STRIP001          pColumn->SetMinMax( MINLAY, MINLAY );
//STRIP001
//STRIP001          // die naechsten Spalten muessen nicht bearbeitet werden
//STRIP001          i += (nColSkip-1);
//STRIP001      }
//STRIP001
//STRIP001      nMin += pColumn->GetMin();
//STRIP001      nMax += pColumn->GetMax();
//STRIP001      bFixRelWidths |= pColumn->IsRelWidthOption();
//STRIP001  }
//STRIP001
//STRIP001  // jetzt noch die Constrains verarbeiten
//STRIP001  SwHTMLTableLayoutConstraints *pConstr = pConstraints;
//STRIP001  while( pConstr )
//STRIP001  {
//STRIP001      // Erstmal muss die Breite analog zu den den Spaltenbreiten
//STRIP001      // aufbereitet werden
//STRIP001      USHORT nCol = pConstr->GetColumn();
//STRIP001      USHORT nColSpan = pConstr->GetColSpan();
//STRIP001      ULONG nConstrMin = pConstr->GetMinNoAlign();
//STRIP001      ULONG nConstrMax = pConstr->GetMaxNoAlign();
//STRIP001
//STRIP001      // jetzt holen wir uns die bisherige Breite der ueberspannten
//STRIP001      // Spalten
//STRIP001      ULONG nColsMin = 0;
//STRIP001      ULONG nColsMax = 0;
//STRIP001      for( USHORT i=nCol; i<nCol+nColSpan; i++ )
//STRIP001      {
//STRIP001          SwHTMLTableLayoutColumn *pColumn = GetColumn( i );
//STRIP001          nColsMin += pColumn->GetMin();
//STRIP001          nColsMax += pColumn->GetMax();
//STRIP001      }
//STRIP001
//STRIP001      if( nColsMin<nConstrMin )
//STRIP001      {
//STRIP001          // den Minimalwert anteilig auf die Spalten verteilen
//STRIP001          ULONG nMinD = nConstrMin-nColsMin;
//STRIP001
//STRIP001          if( nConstrMin > nColsMax )
//STRIP001          {
//STRIP001              // Anteilig anhand der Mindestbreiten
//STRIP001              USHORT nEndCol = nCol+nColSpan;
//STRIP001              ULONG nDiff = nMinD;
//STRIP001              for( USHORT i=nCol; i<nEndCol; i++ )
//STRIP001              {
//STRIP001                  SwHTMLTableLayoutColumn *pColumn = GetColumn( i );
//STRIP001
//STRIP001                  ULONG nColMin = pColumn->GetMin();
//STRIP001                  ULONG nColMax = pColumn->GetMax();
//STRIP001
//STRIP001                  nMin -= nColMin;
//STRIP001                  ULONG nAdd = i<nEndCol-1 ? (nColMin * nMinD) / nColsMin
//STRIP001                                           : nDiff;
//STRIP001                  nColMin += nAdd;
//STRIP001                  nMin += nColMin;
//STRIP001                  ASSERT( nDiff >= nAdd, "Ooops: nDiff stimmt nicht mehr" );
//STRIP001                  nDiff -= nAdd;
//STRIP001
//STRIP001                  if( nColMax < nColMin )
//STRIP001                  {
//STRIP001                      nMax -= nColMax;
//STRIP001                      nColsMax -= nColMax;
//STRIP001                      nColMax = nColMin;
//STRIP001                      nMax += nColMax;
//STRIP001                      nColsMax += nColMax;
//STRIP001                  }
//STRIP001
//STRIP001                  pColumn->SetMinMax( nColMin, nColMax );
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              // Anteilig anhand der Differenz zwischen Max und Min
//STRIP001              for( USHORT i=nCol; i<nCol+nColSpan; i++ )
//STRIP001              {
//STRIP001                  SwHTMLTableLayoutColumn *pColumn = GetColumn( i );
//STRIP001
//STRIP001                  ULONG nDiff = pColumn->GetMax()-pColumn->GetMin();
//STRIP001                  if( nMinD < nDiff )
//STRIP001                      nDiff = nMinD;
//STRIP001
//STRIP001                  pColumn->AddToMin( nDiff );
//STRIP001
//STRIP001                  ASSERT( pColumn->GetMax() >= pColumn->GetMin(),
//STRIP001                          "Wieso ist die SPalte auf einmal zu schmal?" )
//STRIP001
//STRIP001                  nMin += nDiff;
//STRIP001                  nMinD -= nDiff;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if( !HasColTags() && nColsMax<nConstrMax )
//STRIP001      {
//STRIP001          ULONG nMaxD = nConstrMax-nColsMax;
//STRIP001
//STRIP001          for( USHORT i=nCol; i<nCol+nColSpan; i++ )
//STRIP001          {
//STRIP001              SwHTMLTableLayoutColumn *pColumn = GetColumn( i );
//STRIP001
//STRIP001              nMax -= pColumn->GetMax();
//STRIP001
//STRIP001              pColumn->AddToMax( (pColumn->GetMax() * nMaxD) / nColsMax );
//STRIP001
//STRIP001              nMax += pColumn->GetMax();
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      pConstr = pConstr->GetNext();
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001  if( bFixRelWidths )
//STRIP001  {
//STRIP001      if( HasColTags() )
//STRIP001      {
//STRIP001          // Zum Anpassen der relativen Breiten werden im 1. Schritt die
//STRIP001          // Minmalbreiten aller anzupassenden Zellen jeweils mit der
//STRIP001          // relativen Breite einer Spalte multipliziert. Dadurch stimmen
//STRIP001          // dann die Breitenverhaeltnisse der Spalten untereinander.
//STRIP001          // Ausserdem wird der Faktor berechnet, um den die Zelle dadurch
//STRIP001          // breiter gworden ist als die Minmalbreite.
//STRIP001          // Im 2. Schritt werden dann die berechneten Breiten durch diesen
//STRIP001          // Faktor geteilt. Dadurch bleibt die Breite (nimd.) einer Zelle
//STRIP001          // erhalten und dient als Ausgangsbasis fuer die andern Breiten.
//STRIP001          // Es werden auch hier nur die Maximalbreiten beeinflusst!
//STRIP001
//STRIP001          ULONG nAbsMin = 0;  // absolte Min-Breite alter Spalten mit
//STRIP001                              // relativer Breite
//STRIP001          ULONG nRel = 0;     // Summe der relativen Breiten aller Spalten
//STRIP001          for( i=0; i<nCols; i++ )
//STRIP001          {
//STRIP001              SwHTMLTableLayoutColumn *pColumn = GetColumn( i );
//STRIP001              if( pColumn->IsRelWidthOption() && pColumn->GetWidthOption() )
//STRIP001              {
//STRIP001                  nAbsMin += pColumn->GetMin();
//STRIP001                  nRel += pColumn->GetWidthOption();
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          ULONG nQuot = ULONG_MAX;
//STRIP001          for( i=0; i<nCols; i++ )
//STRIP001          {
//STRIP001              SwHTMLTableLayoutColumn *pColumn = GetColumn( i );
//STRIP001              if( pColumn->IsRelWidthOption() )
//STRIP001              {
//STRIP001                  nMax -= pColumn->GetMax();
//STRIP001                  if( pColumn->GetWidthOption() && pColumn->GetMin() )
//STRIP001                  {
//STRIP001                      pColumn->SetMax( nAbsMin * pColumn->GetWidthOption() );
//STRIP001                      ULONG nColQuot = pColumn->GetMax() / pColumn->GetMin();
//STRIP001                      if( nColQuot<nQuot )
//STRIP001                          nQuot = nColQuot;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          ASSERT( 0==nRel || nQuot!=ULONG_MAX,
//STRIP001                  "Wo sind die relativen Spalten geblieben?" );
//STRIP001          for( i=0; i<nCols; i++ )
//STRIP001          {
//STRIP001              SwHTMLTableLayoutColumn *pColumn = GetColumn( i );
//STRIP001              if( pColumn->IsRelWidthOption() )
//STRIP001              {
//STRIP001                  if( pColumn->GetWidthOption() )
//STRIP001                      pColumn->SetMax( pColumn->GetMax() / nQuot );
//STRIP001                  else
//STRIP001                      pColumn->SetMax( pColumn->GetMin() );
//STRIP001                  ASSERT( pColumn->GetMax() >= pColumn->GetMin(),
//STRIP001                          "Maximale Spaltenbreite kleiner als Minimale" );
//STRIP001                  nMax += pColumn->GetMax();
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          USHORT nRel = 0;        // Summe der relativen Breiten aller Spalten
//STRIP001          USHORT nRelCols = 0;    // Anzahl Spalten mit relativer Angabe
//STRIP001          ULONG nRelMax = 0;      // Anteil am Maximum dieser Spalten
//STRIP001          for( i=0; i<nCols; i++ )
//STRIP001          {
//STRIP001              ASSERT( nRel<=100, "relative Breite aller Spalten>100%" );
//STRIP001              SwHTMLTableLayoutColumn *pColumn = GetColumn( i );
//STRIP001              if( pColumn->IsRelWidthOption() && pColumn->GetWidthOption() )
//STRIP001              {
//STRIP001                  // Sicherstellen, dass die relativen breiten nicht
//STRIP001                  // ueber 100% landen
//STRIP001                  USHORT nColWidth = pColumn->GetWidthOption();
//STRIP001                  if( nRel+nColWidth > 100 )
//STRIP001                  {
//STRIP001                      nColWidth = 100 - nRel;
//STRIP001                      pColumn->SetWidthOption( nColWidth, TRUE, FALSE );
//STRIP001                  }
//STRIP001                  nRelMax += pColumn->GetMax();
//STRIP001                  nRel += nColWidth;
//STRIP001                  nRelCols++;
//STRIP001              }
//STRIP001              else if( !pColumn->GetMin() )
//STRIP001              {
//STRIP001                  // Die Spalte ist leer (wurde also auschliesslich
//STRIP001                  // durch COLSPAN erzeugt) und darf deshalb auch
//STRIP001                  // keine %-Breite zugewiesen bekommen.
//STRIP001                  nRelCols++;
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          // Eventuell noch vorhandene Prozente werden auf die Spalten ohne
//STRIP001          // eine Breiten-Angabe verteilt. Wie in Netscape werden die
//STRIP001          // verbleibenden Prozente enstprechend der Verhaeltnisse
//STRIP001          // der Maximalbreiten der in Frage kommenden Spalten
//STRIP001          // untereinander verteilt.
//STRIP001          // ??? Wie beruecksichtigen bei den Maximalbreiten auch Spalten
//STRIP001          // mit fester Breite. Ist das richtig???
//STRIP001          if( nRel < 100 && nRelCols < nCols )
//STRIP001          {
//STRIP001              USHORT nRelLeft = 100 - nRel;
//STRIP001              ULONG nFixMax = nMax - nRelMax;
//STRIP001              for( i=0; i<nCols; i++ )
//STRIP001              {
//STRIP001                  SwHTMLTableLayoutColumn *pColumn = GetColumn( i );
//STRIP001                  if( !pColumn->IsRelWidthOption() &&
//STRIP001                      !pColumn->GetWidthOption() &&
//STRIP001                      pColumn->GetMin() )
//STRIP001                  {
//STRIP001                      // den Rest bekommt die naechste Spalte
//STRIP001                      USHORT nColWidth =
//STRIP001                          (USHORT)((pColumn->GetMax() * nRelLeft) / nFixMax);
//STRIP001                      pColumn->SetWidthOption( nColWidth, TRUE, FALSE );
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          // nun die Maximalbreiten entsprechend anpassen
//STRIP001          ULONG nQuotMax = ULONG_MAX;
//STRIP001          ULONG nOldMax = nMax;
//STRIP001          nMax = 0;
//STRIP001          for( i=0; i<nCols; i++ )
//STRIP001          {
//STRIP001              // Spalten mit %-Angaben werden enstprechend angepasst.
//STRIP001              // Spalten, die
//STRIP001              // - keine %-Angabe besitzen und in einer Tabelle mit COLS
//STRIP001              //   oder WIDTH vorkommen, oder
//STRIP001              // - als Breite 0% angegeben haben erhalten die Minimalbreite
//STRIP001              SwHTMLTableLayoutColumn *pColumn = GetColumn( i );
//STRIP001              if( pColumn->IsRelWidthOption() && pColumn->GetWidthOption() )
//STRIP001              {
//STRIP001                  ULONG nNewMax;
//STRIP001                  ULONG nColQuotMax;
//STRIP001                  if( !nWidthOption )
//STRIP001                  {
//STRIP001                      nNewMax = nOldMax * pColumn->GetWidthOption();
//STRIP001                      nColQuotMax = nNewMax / pColumn->GetMax();
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      nNewMax = nMin * pColumn->GetWidthOption();
//STRIP001                      nColQuotMax = nNewMax / pColumn->GetMin();
//STRIP001                  }
//STRIP001                  pColumn->SetMax( nNewMax );
//STRIP001                  if( nColQuotMax < nQuotMax )
//STRIP001                      nQuotMax = nColQuotMax;
//STRIP001              }
//STRIP001              else if( HasColsOption() || nWidthOption ||
//STRIP001                       (pColumn->IsRelWidthOption() &&
//STRIP001                        !pColumn->GetWidthOption()) )
//STRIP001                  pColumn->SetMax( pColumn->GetMin() );
//STRIP001          }
//STRIP001          // und durch den Quotienten teilen
//STRIP001          ASSERT( nQuotMax!=ULONG_MAX, "Wo sind die relativen Spalten geblieben?" );
//STRIP001          for( i=0; i<nCols; i++ )
//STRIP001          {
//STRIP001              SwHTMLTableLayoutColumn *pColumn = GetColumn( i );
//STRIP001              if( pColumn->IsRelWidthOption() && pColumn->GetWidthOption() )
//STRIP001              {
//STRIP001                  if( pColumn->GetWidthOption() )
//STRIP001                  {
//STRIP001                      pColumn->SetMax( pColumn->GetMax() / nQuotMax );
//STRIP001                      ASSERT( pColumn->GetMax() >= pColumn->GetMin(),
//STRIP001                              "Minimalbreite ein Spalte Groesser Maximum" );
//STRIP001                      if( pColumn->GetMax() < pColumn->GetMin() )
//STRIP001                          pColumn->SetMax( pColumn->GetMin() );
//STRIP001                  }
//STRIP001              }
//STRIP001              nMax += pColumn->GetMax();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  delete pConstraints;
//STRIP001 }

// nAbsAvail ist der verfuegbare Platz in TWIPS.
// nRelAvail ist der auf USHRT_MAX bezogene verfuegbare Platz oder 0
// nAbsSpace ist der Anteil von nAbsAvail, der durch der umgebende Zelle
//           fur die Umrandung und den Abstand zum Inhalt reserviert ist.
//STRIP001 void SwHTMLTableLayout::AutoLayoutPass2( USHORT nAbsAvail, USHORT nRelAvail,
//STRIP001                                       USHORT nAbsLeftSpace,
//STRIP001                                       USHORT nAbsRightSpace,
//STRIP001                                       USHORT nParentInhAbsSpace )
//STRIP001 {
//STRIP001  // Erstmal fuehren wie jede Menge Plausibilaets-Test durch
//STRIP001
//STRIP001  // Eine abolute zur Verfuegung stehende Breite muss immer uebergeben
//STRIP001  // werden.
//STRIP001  ASSERT( nAbsAvail, "AutoLayout Pass 2: Keine absolute Breite gegeben" );
//STRIP001
//STRIP001  // Eine realtive zur Verfuegung stehende Breite darf nur und muss fuer
//STRIP001  // Tabellen in Tabellen uebergeben
//STRIP001  ASSERT( IsTopTable() == (nRelAvail==0),
//STRIP001          "AutoLayout Pass 2: Rel. Breite bei Tab in Tab oder umgekehrt" );
//STRIP001
//STRIP001  // Die Minimalbreite der Tabelle darf natuerlich nie groesser sein
//STRIP001  // als das die Maximalbreite.
//STRIP001  ASSERT( nMin<=nMax, "AutoLayout Pass2: nMin > nMax" );
//STRIP001
//STRIP001  // Die verfuegbare Breite, fuer die die Tabelle berechnet wurde, merken.
//STRIP001  // (Dies ist ein guter Ort, denn hier kommer wir bei der Erstberechnung
//STRIP001  // der Tabelle aus dem Parser und bei jedem _Resize-Aufruf vorbei.)
//STRIP001  nLastResizeAbsAvail = nAbsAvail;
//STRIP001
//STRIP001  // Schritt 1: Der verfuegbar Platz wird an linke/rechte Raender,
//STRIP001  // vorhandene Filler-Zellen und Abstande angepasst
//STRIP001
//STRIP001  // Abstand zum Inhalt und Unrandung
//STRIP001  USHORT nAbsLeftFill = 0, nAbsRightFill = 0;
//STRIP001  if( !IsTopTable() &&
//STRIP001      GetMin() + nAbsLeftSpace + nAbsRightSpace <= nAbsAvail )
//STRIP001  {
//STRIP001      nAbsLeftFill = nAbsLeftSpace;
//STRIP001      nAbsRightFill = nAbsRightSpace;
//STRIP001  }
//STRIP001
//STRIP001  // Linker und rechter Abstand
//STRIP001  if( nLeftMargin || nRightMargin )
//STRIP001  {
//STRIP001      if( IsTopTable() )
//STRIP001      {
//STRIP001          // fuer die Top-Table beruecksichtigen wir die Raender immer,
//STRIP001          // den die Minimalbreite der Tabelle wird hier nie unterschritten
//STRIP001          nAbsAvail -= (nLeftMargin + nRightMargin);
//STRIP001      }
//STRIP001      else if( GetMin() + nLeftMargin + nRightMargin <= nAbsAvail )
//STRIP001      {
//STRIP001          // sonst beruecksichtigen wir die Raender nur, wenn auch Platz
//STRIP001          // fuer sie da ist (nMin ist hier bereits berechnet!)
//STRIP001          nAbsLeftFill += nLeftMargin;
//STRIP001          nAbsRightFill += nRightMargin;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Filler-Zellen
//STRIP001  if( !IsTopTable() )
//STRIP001  {
//STRIP001      if( pLeftFillerBox && nAbsLeftFill<MINLAY+nInhLeftBorderWidth )
//STRIP001          nAbsLeftFill = MINLAY+nInhLeftBorderWidth;
//STRIP001      if( pRightFillerBox && nAbsRightFill<MINLAY+nInhRightBorderWidth )
//STRIP001          nAbsRightFill = MINLAY+nInhRightBorderWidth;
//STRIP001  }
//STRIP001
//STRIP001  // Anpassen des verfuegbaren Platzes.
//STRIP001  nRelLeftFill = 0;
//STRIP001  nRelRightFill = 0;
//STRIP001  if( !IsTopTable() && (nAbsLeftFill>0 || nAbsRightFill) )
//STRIP001  {
//STRIP001      ULONG nAbsLeftFillL = nAbsLeftFill, nAbsRightFillL = nAbsRightFill;
//STRIP001
//STRIP001      nRelLeftFill = (USHORT)((nAbsLeftFillL * nRelAvail) / nAbsAvail);
//STRIP001      nRelRightFill = (USHORT)((nAbsRightFillL * nRelAvail) / nAbsAvail);
//STRIP001
//STRIP001      nAbsAvail -= (nAbsLeftFill + nAbsRightFill);
//STRIP001      if( nRelAvail )
//STRIP001          nRelAvail -= (nRelLeftFill + nRelRightFill);
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001  // Schritt 2: Die absolute Tabellenbreite wird berechnet.
//STRIP001  USHORT nAbsTabWidth = 0;
//STRIP001  bUseRelWidth = FALSE;
//STRIP001  if( nWidthOption )
//STRIP001  {
//STRIP001      if( bPrcWidthOption )
//STRIP001      {
//STRIP001          ASSERT( nWidthOption<=100, "Prozentangabe zu gross" );
//STRIP001          if( nWidthOption > 100 )
//STRIP001              nWidthOption = 100;
//STRIP001
//STRIP001          // Die absolute Breite entspricht den angegeben Prozent der
//STRIP001          // zur Verfuegung stehenden Breite.
//STRIP001          // Top-Tabellen bekommen nur eine relative Breite, wenn der
//STRIP001          // verfuegbare Platz *echt groesser* ist als die Minimalbreite.
//STRIP001          // ACHTUNG: Das "echte groesser" ist noetig, weil der Wechsel
//STRIP001          // von einer relativen Breite zu einer absoluten Breite durch
//STRIP001          // Resize sonst zu einer Endlosschleife fuehrt.
//STRIP001          // Weil bei Tabellen in Rahmen kein Resize aufgerufen wird,
//STRIP001          // wenn der Rahmen eine nicht-relative Breite besitzt, koennen
//STRIP001          // wir da solche Spielchen nicht spielen
//STRIP001          // MIB 19.2.98: Wegen fix #47394# spielen wir solche Spielchen
//STRIP001          // jetzt doch. Dort war eine Grafik in einer 1%-breiten
//STRIP001          // Tabelle und hat da natuerlich nicht hineingepasst.
//STRIP001          nAbsTabWidth = (USHORT)( ((ULONG)nAbsAvail * nWidthOption) / 100 );
//STRIP001          if( IsTopTable() &&
//STRIP001              ( /*MayBeInFlyFrame() ||*/ (ULONG)nAbsTabWidth > nMin ) )
//STRIP001          {
//STRIP001              nRelAvail = USHRT_MAX;
//STRIP001              bUseRelWidth = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          nAbsTabWidth = nWidthOption;
//STRIP001          if( nAbsTabWidth > MAX_TABWIDTH )
//STRIP001              nAbsTabWidth = MAX_TABWIDTH;
//STRIP001
//STRIP001          // Tabellen in Tabellen duerfen niemals breiter werden als der
//STRIP001          // verfuegbare Platz.
//STRIP001          if( !IsTopTable() && nAbsTabWidth > nAbsAvail )
//STRIP001              nAbsTabWidth = nAbsAvail;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  ASSERT( IsTopTable() || nAbsTabWidth<=nAbsAvail,
//STRIP001          "AutoLayout Pass2: nAbsTabWidth > nAbsAvail fuer Tab in Tab" );
//STRIP001  ASSERT( !nRelAvail || nAbsTabWidth<=nAbsAvail,
//STRIP001          "AutoLayout Pass2: nAbsTabWidth > nAbsAvail fuer relative Breite" );
//STRIP001
//STRIP001  // Catch fuer die beiden Asserts von oben (man weiss ja nie!)
//STRIP001  if( (!IsTopTable() || nRelAvail>0) && nAbsTabWidth>nAbsAvail )
//STRIP001      nAbsTabWidth = nAbsAvail;
//STRIP001
//STRIP001
//STRIP001  // Schritt 3: Bestimmen der Spaltenbreiten und ggf. auch der
//STRIP001  // absoluten und relativen Tabellenbreiten.
//STRIP001  if( (!IsTopTable() && nMin > (ULONG)nAbsAvail) ||
//STRIP001      nMin > MAX_TABWIDTH )
//STRIP001  {
//STRIP001      // Wenn
//STRIP001      // - das Minumum einer inneren Tabelle groesser ist als der
//STRIP001      //   verfuegbare Platz, oder
//STRIP001      // - das Minumum einer Top-Table groesser ist als USHRT_MAX
//STRIP001      // muss die Tabelle an den verfuegbaren Platz bzw. USHRT_MAX
//STRIP001      // abgepasst werden. Dabei bleiben die Verhaeltnisse der Breiten
//STRIP001      // untereinander erhalten.
//STRIP001
//STRIP001      nAbsTabWidth = IsTopTable() ? MAX_TABWIDTH : nAbsAvail;
//STRIP001      nRelTabWidth = (nRelAvail ? nRelAvail : nAbsTabWidth );
//STRIP001
//STRIP001      // First of all, we check wether we can fit the layout constrains,
//STRIP001      // that are: Every cell's width excluding the borders must be at least
//STRIP001      // MINLAY:
//STRIP001
//STRIP001      ULONG nRealMin = 0;
//STRIP001      for( USHORT i=0; i<nCols; i++ )
//STRIP001      {
//STRIP001          ULONG nRealColMin = MINLAY, nDummy1, nDummy2;
//STRIP001          AddBorderWidth( nRealColMin, nDummy1, nDummy2, i, 1 );
//STRIP001          nRealMin += nRealColMin;
//STRIP001      }
//STRIP001      if( (nRealMin >= nAbsTabWidth) || (nRealMin >= nMin) )
//STRIP001      {
//STRIP001          // "Nichts geht mehr". We cannot get the minimum column widths
//STRIP001          // the layout wants to have.
//STRIP001
//STRIP001          USHORT nAbs = 0, nRel = 0;
//STRIP001          SwHTMLTableLayoutColumn *pColumn;
//STRIP001          for( USHORT i=0; i<nCols-1; i++ )
//STRIP001          {
//STRIP001              pColumn = GetColumn( i );
//STRIP001              ULONG nColMin = pColumn->GetMin();
//STRIP001              if( nColMin <= USHRT_MAX )
//STRIP001              {
//STRIP001                  pColumn->SetAbsColWidth(
//STRIP001                      (USHORT)((nColMin * nAbsTabWidth) / nMin) );
//STRIP001                  pColumn->SetRelColWidth(
//STRIP001                      (USHORT)((nColMin * nRelTabWidth) / nMin) );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  double nColMinD = nColMin;
//STRIP001                  pColumn->SetAbsColWidth(
//STRIP001                      (USHORT)((nColMinD * nAbsTabWidth) / nMin) );
//STRIP001                  pColumn->SetRelColWidth(
//STRIP001                      (USHORT)((nColMinD * nRelTabWidth) / nMin) );
//STRIP001              }
//STRIP001
//STRIP001              nAbs += (USHORT)pColumn->GetAbsColWidth();
//STRIP001              nRel += (USHORT)pColumn->GetRelColWidth();
//STRIP001          }
//STRIP001          pColumn = GetColumn( nCols-1 );
//STRIP001          pColumn->SetAbsColWidth( nAbsTabWidth - nAbs );
//STRIP001          pColumn->SetRelColWidth( nRelTabWidth - nRel );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          ULONG nDistAbs = nAbsTabWidth - nRealMin;
//STRIP001          ULONG nDistRel = nRelTabWidth - nRealMin;
//STRIP001          ULONG nDistMin = nMin - nRealMin;
//STRIP001          USHORT nAbs = 0, nRel = 0;
//STRIP001          SwHTMLTableLayoutColumn *pColumn;
//STRIP001          for( USHORT i=0; i<nCols-1; i++ )
//STRIP001          {
//STRIP001              pColumn = GetColumn( i );
//STRIP001              ULONG nColMin = pColumn->GetMin();
//STRIP001              ULONG nRealColMin = MINLAY, nDummy1, nDummy2;
//STRIP001              AddBorderWidth( nRealColMin, nDummy1, nDummy2, i, 1 );
//STRIP001
//STRIP001              if( nColMin <= USHRT_MAX )
//STRIP001              {
//STRIP001                  pColumn->SetAbsColWidth(
//STRIP001                      (USHORT)((((nColMin-nRealColMin) * nDistAbs) / nDistMin) + nRealColMin) );
//STRIP001                  pColumn->SetRelColWidth(
//STRIP001                      (USHORT)((((nColMin-nRealColMin) * nDistRel) / nDistMin) + nRealColMin) );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  double nColMinD = nColMin;
//STRIP001                  pColumn->SetAbsColWidth(
//STRIP001                      (USHORT)((((nColMinD-nRealColMin) * nDistAbs) / nDistMin) + nRealColMin) );
//STRIP001                  pColumn->SetRelColWidth(
//STRIP001                      (USHORT)((((nColMinD-nRealColMin) * nDistRel) / nDistMin) + nRealColMin) );
//STRIP001              }
//STRIP001
//STRIP001              nAbs += (USHORT)pColumn->GetAbsColWidth();
//STRIP001              nRel += (USHORT)pColumn->GetRelColWidth();
//STRIP001          }
//STRIP001          pColumn = GetColumn( nCols-1 );
//STRIP001          pColumn->SetAbsColWidth( nAbsTabWidth - nAbs );
//STRIP001          pColumn->SetRelColWidth( nRelTabWidth - nRel );
//STRIP001      }
//STRIP001  }
//STRIP001  else if( nMax <= (ULONG)(nAbsTabWidth ? nAbsTabWidth : nAbsAvail) )
//STRIP001  {
//STRIP001      // Wenn
//STRIP001      // - die Tabelle eine fixe Breite besitzt und das Maximum der
//STRIP001      //   Tabelle kleiner ist, oder
//STRIP001      // - das Maximum kleiner ist als der verfuegbare Platz
//STRIP001      // kann das Maximum direkt uebernommen werden bzw. die Tabelle nur
//STRIP001      // unter Beruecksichtigung des Maxumums an die fixe Breite
//STRIP001      // angepasst werden.
//STRIP001
//STRIP001      // Keine fixe Breite, dann das Maximum nehmen.
//STRIP001      if( !nAbsTabWidth )
//STRIP001          nAbsTabWidth = (USHORT)nMax;
//STRIP001
//STRIP001      // Eine Top-Table darf auch beriter werden als der verfuegbare Platz.
//STRIP001      if( nAbsTabWidth > nAbsAvail )
//STRIP001      {
//STRIP001          ASSERT( IsTopTable(),
//STRIP001                  "Tabelle in Tabelle soll breiter werden als umgebende Zelle" );
//STRIP001          nAbsAvail = nAbsTabWidth;
//STRIP001      }
//STRIP001
//STRIP001      // Nur den Anteil der relativen Breite verwenden, der auch fuer
//STRIP001      // die absolute Breite verwendet wuerde.
//STRIP001      ULONG nAbsTabWidthL = nAbsTabWidth;
//STRIP001      nRelTabWidth =
//STRIP001          ( nRelAvail ? (USHORT)((nAbsTabWidthL * nRelAvail) / nAbsAvail)
//STRIP001                      : nAbsTabWidth );
//STRIP001
//STRIP001      // Gibt es Spalten mit und Spalten ohne %-Angabe?
//STRIP001      ULONG nFixMax = nMax;
//STRIP001      for( USHORT i=0; i<nCols; i++ )
//STRIP001      {
//STRIP001          const SwHTMLTableLayoutColumn *pColumn = GetColumn( i );
//STRIP001          if( pColumn->IsRelWidthOption() && pColumn->GetWidthOption()>0 )
//STRIP001              nFixMax -= pColumn->GetMax();
//STRIP001      }
//STRIP001
//STRIP001      if( nFixMax > 0 && nFixMax < nMax )
//STRIP001      {
//STRIP001          // ja, dann den zu verteilenden Platz nur auf die Spalten
//STRIP001          // mit %-Angabe verteilen.
//STRIP001
//STRIP001          // In diesem (und nur in diesem) Fall gibt es Spalten,
//STRIP001          // die ihre Maximalbreite genau einhalten, also weder
//STRIP001          // schmaler noch breiter werden. Beim zurueckrechnen der
//STRIP001          // absoluten Breite aus der relativen Breite kann es
//STRIP001          // zu Rundungsfehlern kommen (bug #45598#). Um die auszugeleichen
//STRIP001          // werden zuerst die fixen Breiten entsprechend korrigiert
//STRIP001          // eingestellt und erst danach die relativen.
//STRIP001
//STRIP001          USHORT nAbs = 0, nRel = 0;
//STRIP001          USHORT nFixedCols = 0;
//STRIP001          for( USHORT i=0; i<nCols; i++ )
//STRIP001          {
//STRIP001              SwHTMLTableLayoutColumn *pColumn = GetColumn( i );
//STRIP001              if( !pColumn->IsRelWidthOption() || !pColumn->GetWidthOption() )
//STRIP001              {
//STRIP001                  // Die Spalte behaelt ihre Breite bei.
//STRIP001                  nFixedCols++;
//STRIP001                  ULONG nColMax = pColumn->GetMax();
//STRIP001                  pColumn->SetAbsColWidth( (USHORT)nColMax );
//STRIP001
//STRIP001                  ULONG nRelColWidth =
//STRIP001                      (nColMax * nRelTabWidth) / nAbsTabWidth;
//STRIP001                  ULONG nChkWidth =
//STRIP001                      (nRelColWidth * nAbsTabWidth) / nRelTabWidth;
//STRIP001                  if( nChkWidth < nColMax )
//STRIP001                      nRelColWidth++;
//STRIP001                  else if( nChkWidth > nColMax )
//STRIP001                      nRelColWidth--;
//STRIP001                  pColumn->SetRelColWidth( (USHORT)nRelColWidth );
//STRIP001
//STRIP001                  nAbs += (USHORT)nColMax;
//STRIP001                  nRel += (USHORT)nRelColWidth;
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          // Zu verteilende Anteile des Maximums und der relativen und
//STRIP001          // absoluten Breiten. nFixMax entspricht an dieser Stelle
//STRIP001          // nAbs, so dass man gleich nFixMax haette nehmen koennen.
//STRIP001          // Der Code ist so aber verstaendlicher.
//STRIP001          ASSERT( nFixMax == nAbs, "Zwei Schleifen, zwei Summen?" )
//STRIP001          ULONG nDistMax = nMax - nFixMax;
//STRIP001          USHORT nDistAbsTabWidth = nAbsTabWidth - nAbs;
//STRIP001          USHORT nDistRelTabWidth = nRelTabWidth - nRel;
//STRIP001
//STRIP001          for( i=0; i<nCols; i++ )
//STRIP001          {
//STRIP001              SwHTMLTableLayoutColumn *pColumn = GetColumn( i );
//STRIP001              if( pColumn->IsRelWidthOption() && pColumn->GetWidthOption() > 0 )
//STRIP001              {
//STRIP001                  // Die Spalte wird anteilig breiter.
//STRIP001                  nFixedCols++;
//STRIP001                  if( nFixedCols == nCols )
//STRIP001                  {
//STRIP001                      pColumn->SetAbsColWidth( nAbsTabWidth-nAbs );
//STRIP001                      pColumn->SetRelColWidth( nRelTabWidth-nRel );
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      ULONG nColMax = pColumn->GetMax();
//STRIP001                      pColumn->SetAbsColWidth(
//STRIP001                          (USHORT)((nColMax * nDistAbsTabWidth) / nDistMax) );
//STRIP001                      pColumn->SetRelColWidth(
//STRIP001                          (USHORT)((nColMax * nDistRelTabWidth) / nDistMax) );
//STRIP001                  }
//STRIP001                  nAbs += pColumn->GetAbsColWidth();
//STRIP001                  nRel += pColumn->GetRelColWidth();
//STRIP001              }
//STRIP001          }
//STRIP001          ASSERT( nCols==nFixedCols, "Spalte vergessen!" );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // nein, dann den zu verteilenden Platz auf alle Spalten
//STRIP001          // gleichmaessig vertilen.
//STRIP001          for( USHORT i=0; i<nCols; i++ )
//STRIP001          {
//STRIP001              ULONG nColMax = GetColumn( i )->GetMax();
//STRIP001              GetColumn( i )->SetAbsColWidth(
//STRIP001                  (USHORT)((nColMax * nAbsTabWidth) / nMax) );
//STRIP001              GetColumn( i )->SetRelColWidth(
//STRIP001                  (USHORT)((nColMax * nRelTabWidth) / nMax) );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // den ueber die Minimalbreite herausgehenden Platz entsprechend
//STRIP001      // den einzelnen Spalten anteilig zuschlagen
//STRIP001      if( !nAbsTabWidth )
//STRIP001          nAbsTabWidth = nAbsAvail;
//STRIP001      if( nAbsTabWidth < nMin )
//STRIP001          nAbsTabWidth = (USHORT)nMin;
//STRIP001
//STRIP001      if( nAbsTabWidth > nAbsAvail )
//STRIP001      {
//STRIP001          ASSERT( IsTopTable(),
//STRIP001                  "Tabelle in Tabelle soll breiter werden als Platz da ist" );
//STRIP001          nAbsAvail = nAbsTabWidth;
//STRIP001      }
//STRIP001
//STRIP001      ULONG nAbsTabWidthL = nAbsTabWidth;
//STRIP001      nRelTabWidth =
//STRIP001          ( nRelAvail ? (USHORT)((nAbsTabWidthL * nRelAvail) / nAbsAvail)
//STRIP001                      : nAbsTabWidth );
//STRIP001      double nW = nAbsTabWidth - nMin;
//STRIP001      double nD = (nMax==nMin ? 1 : nMax-nMin);
//STRIP001      USHORT nAbs = 0, nRel = 0;
//STRIP001      for( USHORT i=0; i<nCols-1; i++ )
//STRIP001      {
//STRIP001          double nd = GetColumn( i )->GetMax() - GetColumn( i )->GetMin();
//STRIP001          ULONG nAbsColWidth = GetColumn( i )->GetMin() + (ULONG)((nd*nW)/nD);
//STRIP001          ULONG nRelColWidth = nRelAvail
//STRIP001                                  ? (nAbsColWidth * nRelTabWidth) / nAbsTabWidth
//STRIP001                                  : nAbsColWidth;
//STRIP001
//STRIP001          GetColumn( i )->SetAbsColWidth( (USHORT)nAbsColWidth );
//STRIP001          GetColumn( i )->SetRelColWidth( (USHORT)nRelColWidth );
//STRIP001          nAbs += (USHORT)nAbsColWidth;
//STRIP001          nRel += (USHORT)nRelColWidth;
//STRIP001      }
//STRIP001      GetColumn( nCols-1 )->SetAbsColWidth( nAbsTabWidth - nAbs );
//STRIP001      GetColumn( nCols-1 )->SetRelColWidth( nRelTabWidth - nRel );
//STRIP001
//STRIP001  }
//STRIP001
//STRIP001  // Schritt 4: Fuer Tabellen in Tabellen kann es links und/oder rechts
//STRIP001  // noch Ausgleichzellen geben. Deren Breite wird jetzt berechnet.
//STRIP001  nInhAbsLeftSpace = 0;
//STRIP001  nInhAbsRightSpace = 0;
//STRIP001  if( !IsTopTable() && (nRelLeftFill>0 || nRelRightFill>0 ||
//STRIP001                        nAbsTabWidth<nAbsAvail) )
//STRIP001  {
//STRIP001      // Die Breite von zusaetzlichen Zellen zur Ausrichtung der
//STRIP001      // inneren Tabelle bestimmen
//STRIP001      USHORT nAbsDist = (USHORT)(nAbsAvail-nAbsTabWidth);
//STRIP001      USHORT nRelDist = (USHORT)(nRelAvail-nRelTabWidth);
//STRIP001      USHORT nParentInhAbsLeftSpace = 0, nParentInhAbsRightSpace = 0;
//STRIP001
//STRIP001      // Groesse und Position der zusaetzlichen Zellen bestimmen
//STRIP001      switch( eTableAdjust )
//STRIP001      {
//STRIP001      case SVX_ADJUST_RIGHT:
//STRIP001          nAbsLeftFill += nAbsDist;
//STRIP001          nRelLeftFill += nRelDist;
//STRIP001          nParentInhAbsLeftSpace = nParentInhAbsSpace;
//STRIP001          break;
//STRIP001      case SVX_ADJUST_CENTER:
//STRIP001          {
//STRIP001              USHORT nAbsLeftDist = nAbsDist / 2;
//STRIP001              nAbsLeftFill += nAbsLeftDist;
//STRIP001              nAbsRightFill += nAbsDist - nAbsLeftDist;
//STRIP001              USHORT nRelLeftDist = nRelDist / 2;
//STRIP001              nRelLeftFill += nRelLeftDist;
//STRIP001              nRelRightFill += nRelDist - nRelLeftDist;
//STRIP001              nParentInhAbsLeftSpace = nParentInhAbsSpace / 2;
//STRIP001              nParentInhAbsRightSpace = nParentInhAbsSpace -
//STRIP001                                        nParentInhAbsLeftSpace;
//STRIP001          }
//STRIP001          break;
//STRIP001      case SVX_ADJUST_LEFT:
//STRIP001      default:
//STRIP001          nAbsRightFill += nAbsDist;
//STRIP001          nRelRightFill += nRelDist;
//STRIP001          nParentInhAbsRightSpace = nParentInhAbsSpace;
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      ASSERT( !pLeftFillerBox || nRelLeftFill>0,
//STRIP001              "Fuer linke Filler-Box ist keine Breite da!" );
//STRIP001      ASSERT( !pRightFillerBox || nRelRightFill>0,
//STRIP001              "Fuer rechte Filler-Box ist keine Breite da!" );
//STRIP001
//STRIP001      // Filler-Breiten werden auf die ausseren Spalten geschlagen, wenn
//STRIP001      // es nach dem ersten Durchlauf keine Boxen fuer sie gibt (nWidth>0)
//STRIP001      // oder ihre Breite zu klein wuerde oder wenn es COL-Tags gibt und
//STRIP001      // die Filler-Breite der Umrandung-Breite entspricht (dann haben wir
//STRIP001      // die Tabelle wahrscheinlich selbst exportiert)
//STRIP001      if( nRelLeftFill && !pLeftFillerBox &&
//STRIP001          ( nWidthSet>0 || nAbsLeftFill<MINLAY+nInhLeftBorderWidth ||
//STRIP001            (HasColTags() && nAbsLeftFill < nAbsLeftSpace+nParentInhAbsLeftSpace+20) ) )
//STRIP001 //           (nAbsLeftFill<MINLAY || nAbsLeftFill<=nAbsLeftSpace) )
//STRIP001      {
//STRIP001          SwHTMLTableLayoutColumn *pColumn = GetColumn( 0 );
//STRIP001          pColumn->SetAbsColWidth( pColumn->GetAbsColWidth()+nAbsLeftFill );
//STRIP001          pColumn->SetRelColWidth( pColumn->GetRelColWidth()+nRelLeftFill );
//STRIP001          nRelLeftFill = 0;
//STRIP001          nInhAbsLeftSpace = nAbsLeftSpace + nParentInhAbsLeftSpace;
//STRIP001      }
//STRIP001      if( nRelRightFill && !pRightFillerBox &&
//STRIP001          ( nWidthSet>0 || nAbsRightFill<MINLAY+nInhRightBorderWidth ||
//STRIP001            (HasColTags() && nAbsRightFill < nAbsRightSpace+nParentInhAbsRightSpace+20) ) )
//STRIP001 //           (nAbsRightFill<MINLAY || nAbsRightFill<=nAbsRightSpace) )
//STRIP001      {
//STRIP001          SwHTMLTableLayoutColumn *pColumn = GetColumn( nCols-1 );
//STRIP001          pColumn->SetAbsColWidth( pColumn->GetAbsColWidth()+nAbsRightFill );
//STRIP001          pColumn->SetRelColWidth( pColumn->GetRelColWidth()+nRelRightFill );
//STRIP001          nRelRightFill = 0;
//STRIP001          nInhAbsRightSpace = nAbsRightSpace + nParentInhAbsRightSpace;
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL lcl_ResizeLine( const SwTableLine*& rpLine, void* pPara );

//STRIP001 BOOL lcl_ResizeBox( const SwTableBox*& rpBox, void* pPara )
//STRIP001 {
//STRIP001  USHORT *pWidth = (USHORT *)pPara;
//STRIP001
//STRIP001  if( !rpBox->GetSttNd() )
//STRIP001  {
//STRIP001      USHORT nWidth = 0;
//STRIP001      ((SwTableBox *)rpBox)->GetTabLines().ForEach( &lcl_ResizeLine, &nWidth );
//STRIP001      rpBox->GetFrmFmt()->SetAttr( SwFmtFrmSize( ATT_VAR_SIZE, nWidth, 0 ));
//STRIP001      *pWidth += nWidth;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      *pWidth += (USHORT)rpBox->GetFrmFmt()->GetFrmSize().GetSize().Width();
//STRIP001  }
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL lcl_ResizeLine( const SwTableLine*& rpLine, void* pPara )
//STRIP001 {
//STRIP001  USHORT *pWidth = (USHORT *)pPara;
//STRIP001 #ifndef PRODUCT
//STRIP001  USHORT nOldWidth = *pWidth;
//STRIP001 #endif;
//STRIP001  *pWidth = 0;
//STRIP001  ((SwTableLine *)rpLine)->GetTabBoxes().ForEach( &lcl_ResizeBox, pWidth );
//STRIP001
//STRIP001 #ifndef PRODUCT
//STRIP001  ASSERT( !nOldWidth || Abs(*pWidth-nOldWidth) < COLFUZZY,
//STRIP001          "Zeilen einer Box sind unterschiedlich lang" );
//STRIP001 #endif;
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 void SwHTMLTableLayout::SetWidths( BOOL bCallPass2, USHORT nAbsAvail,
//STRIP001                                 USHORT nRelAvail, USHORT nAbsLeftSpace,
//STRIP001                                 USHORT nAbsRightSpace,
//STRIP001                                 USHORT nParentInhAbsSpace )
//STRIP001 {
//STRIP001  // SetWidth muss am Ende einmal mehr fuer jede Zelle durchlaufen
//STRIP001  // worden sein.
//STRIP001  nWidthSet++;
//STRIP001
//STRIP001  // Schritt 0: Wenn noetig, wird hier noch der Pass2 des Layout-Alogithmus
//STRIP001  // aufgerufen.
//STRIP001  if( bCallPass2 )
//STRIP001      AutoLayoutPass2( nAbsAvail, nRelAvail, nAbsLeftSpace, nAbsRightSpace,
//STRIP001                       nParentInhAbsSpace );
//STRIP001
//STRIP001  // Schritt 1: Setzten der neuen Breite an allen Content-Boxen.
//STRIP001  // Da die Boxen nichts von der HTML-Tabellen-Struktur wissen, wird
//STRIP001  // ueber die HTML-Tabellen-Struktur iteriert. Fuer Tabellen in Tabellen
//STRIP001  // in Tabellen wird rekursiv SetWidth aufgerufen.
//STRIP001  for( USHORT i=0; i<nRows; i++ )
//STRIP001  {
//STRIP001      for( USHORT j=0; j<nCols; j++ )
//STRIP001      {
//STRIP001          SwHTMLTableLayoutCell *pCell = GetCell( i, j );
//STRIP001
//STRIP001          SwHTMLTableLayoutCnts* pCntnts = pCell->GetContents();
//STRIP001          while( pCntnts && !pCntnts->IsWidthSet(nWidthSet) )
//STRIP001          {
//STRIP001              SwTableBox *pBox = pCntnts->GetTableBox();
//STRIP001              if( pBox )
//STRIP001              {
//STRIP001                  SetBoxWidth( pBox, j, pCell->GetColSpan() );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  USHORT nAbs = 0, nRel = 0, nLSpace = 0, nRSpace = 0,
//STRIP001                         nInhSpace = 0;
//STRIP001                  if( bCallPass2 )
//STRIP001                  {
//STRIP001                      USHORT nColSpan = pCell->GetColSpan();
//STRIP001                      GetAvail( j, nColSpan, nAbs, nRel );
//STRIP001                      nLSpace = GetLeftCellSpace( j, nColSpan );
//STRIP001                      nRSpace = GetRightCellSpace( j, nColSpan );
//STRIP001                      nInhSpace = GetInhCellSpace( j, nColSpan );
//STRIP001                  }
//STRIP001                  pCntnts->GetTable()->SetWidths( bCallPass2, nAbs, nRel,
//STRIP001                                                  nLSpace, nRSpace,
//STRIP001                                                  nInhSpace );
//STRIP001              }
//STRIP001
//STRIP001              pCntnts->SetWidthSet( nWidthSet );
//STRIP001              pCntnts = pCntnts->GetNext();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // Schritt 2: Wenn eine Top-Tabelle vorliegt, werden jetzt die Formate
//STRIP001  // der Nicht-Content-Boxen angepasst. Da diese aufgrund der
//STRIP001  // Garbage-Collection in der HTML-Tabelle nicht bekannt sind, muessen
//STRIP001  // wir hier ueber die Tabelle iterieren. Bei der Gelegenheit wird auch
//STRIP001  // das Tabellen-Frameformat angepasst. Fuer Tabellen in Tabellen werden
//STRIP001  // stattdessen die Breiten der Filler-Zellen gesetzt.
//STRIP001  if( IsTopTable() )
//STRIP001  {
//STRIP001      USHORT nCalcTabWidth = 0;
//STRIP001      ((SwTable *)pSwTable)->GetTabLines().ForEach( &lcl_ResizeLine,
//STRIP001                                                    &nCalcTabWidth );
//STRIP001      ASSERT( Abs( nRelTabWidth-nCalcTabWidth ) < COLFUZZY,
//STRIP001              "Tabellebreite stimmt nicht mit Zeilenbreite ueberein." );
//STRIP001
//STRIP001      // Beim Anpassen des Tabellen-Formats dieses locken, weil sonst
//STRIP001      // die Boxformate erneut angepasst werden. Ausserdem muss eine
//STRIP001      // evtl. vorhandene %-Angabe in jedem Fall erhalten bleiben.
//STRIP001      SwFrmFmt *pFrmFmt = pSwTable->GetFrmFmt();
//STRIP001      ((SwTable *)pSwTable)->LockModify();
//STRIP001      SwFmtFrmSize aFrmSize( pFrmFmt->GetFrmSize() );
//STRIP001      aFrmSize.SetWidth( nRelTabWidth );
//STRIP001      BOOL bRel = bUseRelWidth &&
//STRIP001                  HORI_FULL!=pFrmFmt->GetHoriOrient().GetHoriOrient();
//STRIP001      aFrmSize.SetWidthPercent( (BYTE)(bRel ? nWidthOption : 0) );
//STRIP001      pFrmFmt->SetAttr( aFrmSize );
//STRIP001      ((SwTable *)pSwTable)->UnlockModify();
//STRIP001
//STRIP001      // Wenn die Tabelle in einem Rahmen steht, muss auch noch dessen
//STRIP001      // breite angepasst werden.
//STRIP001      if( MayBeInFlyFrame() )
//STRIP001      {
//STRIP001          SwFrmFmt *pFlyFrmFmt = FindFlyFrmFmt();
//STRIP001          if( pFlyFrmFmt )
//STRIP001          {
//STRIP001              SwFmtFrmSize aFlyFrmSize( ATT_VAR_SIZE, nRelTabWidth, MINLAY );
//STRIP001
//STRIP001              if( bUseRelWidth )
//STRIP001              {
//STRIP001                  // Bei %-Angaben wird die Breite auf das Minimum gesetzt.
//STRIP001                  aFlyFrmSize.SetWidth(  nMin > USHRT_MAX ? USHRT_MAX
//STRIP001                                                          : nMin );
//STRIP001                  aFlyFrmSize.SetWidthPercent( (BYTE)nWidthOption );
//STRIP001              }
//STRIP001              pFlyFrmFmt->SetAttr( aFlyFrmSize );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001 #ifndef PRODUCT
//STRIP001      {
//STRIP001          // steht im tblrwcl.cxx
//STRIP001          extern void _CheckBoxWidth( const SwTableLine&, SwTwips );
//STRIP001
//STRIP001          // checke doch mal ob die Tabellen korrekte Breiten haben
//STRIP001          SwTwips nSize = pSwTable->GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001          const SwTableLines& rLines = pSwTable->GetTabLines();
//STRIP001          for( USHORT n = 0; n < rLines.Count(); ++n  )
//STRIP001              _CheckBoxWidth( *rLines[ n ], nSize );
//STRIP001      }
//STRIP001 #endif
//STRIP001
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( pLeftFillerBox )
//STRIP001      {
//STRIP001          pLeftFillerBox->GetFrmFmt()->SetAttr(
//STRIP001              SwFmtFrmSize( ATT_VAR_SIZE, nRelLeftFill, 0 ));
//STRIP001      }
//STRIP001      if( pRightFillerBox )
//STRIP001      {
//STRIP001          pRightFillerBox->GetFrmFmt()->SetAttr(
//STRIP001              SwFmtFrmSize( ATT_VAR_SIZE, nRelRightFill, 0 ));
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SwHTMLTableLayout::_Resize( USHORT nAbsAvail, BOOL bRecalc )
//STRIP001 {
//STRIP001  // Wenn bRecalc gestzt ist, hat sich am Inhalt der Tabelle etwas
//STRIP001  // geaendert. Es muss dann der erste Pass noch einmal durchgefuehrt
//STRIP001  // werden.
//STRIP001  if( bRecalc )
//STRIP001      AutoLayoutPass1();
//STRIP001
//STRIP001  SwRootFrm *pRoot = (SwRootFrm*)GetDoc()->GetRootFrm();
//STRIP001  if ( pRoot && pRoot->IsCallbackActionEnabled() )
//STRIP001      pRoot->StartAllAction();
//STRIP001
//STRIP001  // Sonst koennen die Breiten gesetzt werden, wobei zuvor aber jewils
//STRIP001  // noch der Pass 2 laufen muss.
//STRIP001  SetWidths( TRUE, nAbsAvail );
//STRIP001
//STRIP001  if ( pRoot && pRoot->IsCallbackActionEnabled() )
//STRIP001      pRoot->EndAllAction( TRUE );    //True per VirDev (Browsen ruhiger)
//STRIP001 }

//STRIP001 IMPL_STATIC_LINK( SwHTMLTableLayout, DelayedResize_Impl, void*, EMPTYARG )
//STRIP001 {
//STRIP001 #ifdef TEST_DELAYED_RESIZE
//STRIP001  Sound::Beep( SOUND_WARNING );
//STRIP001 #endif
//STRIP001  pThis->aResizeTimer.Stop();
//STRIP001  pThis->_Resize( pThis->nDelayedResizeAbsAvail,
//STRIP001                  pThis->bDelayedResizeRecalc );
//STRIP001
//STRIP001  return 0;
//STRIP001 }


//STRIP001 BOOL SwHTMLTableLayout::Resize( USHORT nAbsAvail, BOOL bRecalc,
//STRIP001                              BOOL bForce, ULONG nDelay )
//STRIP001 {
//STRIP001  ASSERT( IsTopTable(), "Resize darf nur an Top-Tabellen aufgerufen werden" );
//STRIP001
//STRIP001  // Darf die Tabelle uberhaupt Resized werden oder soll sie es trotzdem?
//STRIP001  if( bMustNotResize && !bForce )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // Darf ein Recalc der Tabelle durchgefuehrt werden?
//STRIP001  if( bMustNotRecalc && !bForce )
//STRIP001      bRecalc = FALSE;
//STRIP001
//STRIP001  const SwDoc *pDoc = GetDoc();
//STRIP001
//STRIP001  // Wenn es ein Layout gibt, wurde evtl. die Groesse der Root-Frames
//STRIP001  // und nicht die der VisArea uebergeben. Wenn wir nicht in einem Rahmen
//STRIP001  // stehen, muss die Tabelle allerdings fuer die VisArea berechnet werden,
//STRIP001  // weil sond die Umschaltung von relativ nach absolut nicht funktioniert.
//STRIP001  if( pDoc->GetRootFrm() && pDoc->IsBrowseMode() )
//STRIP001  {
//STRIP001      USHORT nVisAreaWidth = GetBrowseWidthByVisArea( *pDoc );
//STRIP001      if( nVisAreaWidth < nAbsAvail && !FindFlyFrmFmt() )
//STRIP001          nAbsAvail = nVisAreaWidth;
//STRIP001  }
//STRIP001
//STRIP001  if( nDelay==0 && aResizeTimer.IsActive() )
//STRIP001  {
//STRIP001      // Wenn beim Aufruf eines synchronen Resize noch ein asynchrones
//STRIP001      // Resize aussteht, dann werden nur die neuen Werte uebernommen.
//STRIP001
//STRIP001      bRecalc |= bDelayedResizeRecalc;
//STRIP001      nDelayedResizeAbsAvail = nAbsAvail;
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  // Optimierung:
//STRIP001  // Wenn die Minima/Maxima nicht neu berechnet werden sollen und
//STRIP001  // - die Breite der Tabelle nie neu berechnet werden muss, oder
//STRIP001  // - die Tabelle schon fuer die uebergebene Breite berechnet wurde, oder
//STRIP001  // - der verfuegbare Platz kleiner oder gleich der Minimalbreite ist
//STRIP001  //   und die Tabelle bereits die Minimalbreite besitzt, oder
//STRIP001  // - der verfuegbare Platz groesser ist als die Maximalbreite und
//STRIP001  //   die Tabelle bereits die Maximalbreite besitzt
//STRIP001  // wird sich an der Tabelle nichts aendern.
//STRIP001  if( !bRecalc && ( !bMustResize ||
//STRIP001                    (nLastResizeAbsAvail==nAbsAvail) ||
//STRIP001                    (nAbsAvail<=nMin && nRelTabWidth==nMin) ||
//STRIP001                    (!bPrcWidthOption && nAbsAvail>=nMax && nRelTabWidth==nMax) ) )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if( nDelay==HTMLTABLE_RESIZE_NOW )
//STRIP001  {
//STRIP001      if( aResizeTimer.IsActive() )
//STRIP001          aResizeTimer.Stop();
//STRIP001      _Resize( nAbsAvail, bRecalc );
//STRIP001  }
//STRIP001  else if( nDelay > 0 )
//STRIP001  {
//STRIP001      nDelayedResizeAbsAvail = nAbsAvail;
//STRIP001      bDelayedResizeRecalc = bRecalc;
//STRIP001      aResizeTimer.SetTimeout( nDelay );
//STRIP001      aResizeTimer.Start();
//STRIP001 #ifdef TEST_DELAYED_RESIZE
//STRIP001      Sound::Beep( SOUND_DEFAULT );
//STRIP001 #endif
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      _Resize( nAbsAvail, bRecalc );
//STRIP001  }
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 void SwHTMLTableLayout::BordersChanged( USHORT nAbsAvail, BOOL bRecalc )
//STRIP001 {
//STRIP001  bBordersChanged = TRUE;
//STRIP001
//STRIP001  Resize( nAbsAvail, bRecalc );
//STRIP001 }


}
