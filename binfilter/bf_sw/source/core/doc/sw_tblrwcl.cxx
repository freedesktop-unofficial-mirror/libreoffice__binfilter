/*************************************************************************
 *
 *  $RCSfile: sw_tblrwcl.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:14:25 $
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

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#define _ZFORLIST_DECLARE_TABLE
#define ITEMID_BOXINFO      SID_ATTR_BORDER_INNER

// auto strip #ifndef _SVX_BRSHITEM_HXX //autogen
// auto strip #include <bf_svx/brshitem.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_LRSPITEM_HXX //autogen
// auto strip #include <bf_svx/lrspitem.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_PROTITEM_HXX //autogen
// auto strip #include <bf_svx/protitem.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_BOXITEM_HXX //autogen
// auto strip #include <bf_svx/boxitem.hxx>
// auto strip #endif
// auto strip #ifndef _FRACT_HXX
// auto strip #include <tools/fract.hxx>
// auto strip #endif

// auto strip #ifndef _FMTFSIZE_HXX //autogen
// auto strip #include <fmtfsize.hxx>
// auto strip #endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif
// auto strip #ifndef _ERRHDL_HXX
// auto strip #include <errhdl.hxx>
// auto strip #endif

// auto strip #ifndef _FMTORNT_HXX //autogen
// auto strip #include <fmtornt.hxx>
// auto strip #endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
// auto strip #ifndef _CNTFRM_HXX
// auto strip #include <cntfrm.hxx>
// auto strip #endif
// auto strip #ifndef _TABFRM_HXX //autogen
// auto strip #include <tabfrm.hxx>
// auto strip #endif
#ifndef _FRMTOOL_HXX
#include <frmtool.hxx>
#endif
// auto strip #ifndef _PAM_HXX
// auto strip #include <pam.hxx>
// auto strip #endif
// auto strip #ifndef _SWTABLE_HXX
// auto strip #include <swtable.hxx>
// auto strip #endif
// auto strip #ifndef _NDTXT_HXX
// auto strip #include <ndtxt.hxx>
// auto strip #endif
// auto strip #ifndef _TBLSEL_HXX
// auto strip #include <tblsel.hxx>
// auto strip #endif
// auto strip #ifndef _FLDBAS_HXX
// auto strip #include <fldbas.hxx>
// auto strip #endif
// auto strip #ifndef _HINTS_HXX
// auto strip #include <hints.hxx>
// auto strip #endif
// auto strip #ifndef _SWUNDO_HXX
// auto strip #include <swundo.hxx>
// auto strip #endif
// auto strip #ifndef _TABFRM_HXX
// auto strip #include <tabfrm.hxx>
// auto strip #endif
// auto strip #ifndef _ROWFRM_HXX
// auto strip #include <rowfrm.hxx>
// auto strip #endif
// auto strip #ifndef _DDEFLD_HXX
// auto strip #include <ddefld.hxx>
// auto strip #endif
// auto strip #ifndef _UNDOBJ_HXX
// auto strip #include <undobj.hxx>
// auto strip #endif
// auto strip #ifndef _TABFRM_HXX
// auto strip #include <tabfrm.hxx>
// auto strip #endif
// auto strip #ifndef _CELLATR_HXX
// auto strip #include <cellatr.hxx>
// auto strip #endif
// auto strip #ifndef _MVSAVE_HXX
// auto strip #include <mvsave.hxx>
// auto strip #endif
// auto strip #ifndef _SWTBLFMT_HXX
// auto strip #include <swtblfmt.hxx>
// auto strip #endif
// auto strip #ifndef _SWDDETBL_HXX
// auto strip #include <swddetbl.hxx>
// auto strip #endif
// auto strip #ifndef _POOLFMT_HXX
// auto strip #include <poolfmt.hxx>
// auto strip #endif
#ifndef _TBLRWCL_HXX
#include <tblrwcl.hxx>
#endif
namespace binfilter {

#define COLFUZZY 20
#define ROWFUZZY 10

typedef SwTableLine* SwTableLinePtr;
//STRIP001 SV_DECL_PTRARR_SORT( SwSortTableLines, SwTableLinePtr, 16, 16 )//STRIP008 ;
//STRIP001 SV_IMPL_PTRARR_SORT( SwSortTableLines, SwTableLinePtr );

/*N*/ SV_IMPL_PTRARR( _SwShareBoxFmts, SwShareBoxFmt* )

// fuers setzen der Frame-Formate an den Boxen reicht es, das aktuelle
// im Array zu suchen. Ist es vorhanden, so gebe das neue zurueck
//STRIP001 struct _CpyTabFrm
//STRIP001 {
//STRIP001  union {
//STRIP001      SwTableBoxFmt *pFrmFmt;     // fuer CopyCol
//STRIP001      SwTwips nSize;              // fuer DelCol
//STRIP001  } Value;
//STRIP001  SwTableBoxFmt *pNewFrmFmt;
//STRIP001
//STRIP001  _CpyTabFrm( SwTableBoxFmt* pAktFrmFmt ) : pNewFrmFmt( 0 )
//STRIP001  {   Value.pFrmFmt = pAktFrmFmt; }
//STRIP001
//STRIP001  _CpyTabFrm& operator=( const _CpyTabFrm& );
//STRIP001
//STRIP001  BOOL operator==( const _CpyTabFrm& rCpyTabFrm )
//STRIP001      { return  (ULONG)Value.nSize == (ULONG)rCpyTabFrm.Value.nSize; }
//STRIP001  BOOL operator<( const _CpyTabFrm& rCpyTabFrm )
//STRIP001      { return  (ULONG)Value.nSize < (ULONG)rCpyTabFrm.Value.nSize; }
//STRIP001 };

//STRIP001 struct CR_SetBoxWidth
//STRIP001 {
//STRIP001  SwSelBoxes aBoxes;
//STRIP001  SwSortTableLines aLines;
//STRIP001  SvUShorts aLinesWidth;
//STRIP001  SwShareBoxFmts aShareFmts;
//STRIP001  SwTableNode* pTblNd;
//STRIP001  SwUndoTblNdsChg* pUndo;
//STRIP001  SwTwips nDiff, nSide, nMaxSize, nLowerDiff;
//STRIP001  USHORT nMode, nTblWidth, nRemainWidth, nBoxWidth;
//STRIP001  BOOL bBigger, bLeft, bSplittBox, bAnyBoxFnd;
//STRIP001
//STRIP001  CR_SetBoxWidth( USHORT eType, SwTwips nDif, SwTwips nSid, SwTwips nTblW,
//STRIP001                  SwTwips nMax, SwTableNode* pTNd )
//STRIP001      : nDiff( nDif ), nSide( nSid ), nMaxSize( nMax ),
//STRIP001      nTblWidth( (USHORT)nTblW ), nRemainWidth( 0 ),
//STRIP001      nLowerDiff( 0 ), bAnyBoxFnd( FALSE ),
//STRIP001      pTblNd( pTNd ), bSplittBox( FALSE ), nBoxWidth( 0 )
//STRIP001  {
//STRIP001      bLeft = WH_COL_LEFT == ( eType & 0xff ) ||
//STRIP001              WH_CELL_LEFT == ( eType & 0xff );
//STRIP001      bBigger = 0 != (eType & WH_FLAG_BIGGER );
//STRIP001      nMode = pTblNd->GetTable().GetTblChgMode();
//STRIP001  }
//STRIP001  CR_SetBoxWidth( const CR_SetBoxWidth& rCpy )
//STRIP001      : nDiff( rCpy.nDiff ), nMode( rCpy.nMode ),
//STRIP001      nSide( rCpy.nSide ), bBigger( rCpy.bBigger ), bLeft( rCpy.bLeft ),
//STRIP001      bSplittBox( rCpy.bSplittBox ), bAnyBoxFnd( rCpy.bAnyBoxFnd ),
//STRIP001      nTblWidth( rCpy.nTblWidth ), nRemainWidth( rCpy.nRemainWidth ),
//STRIP001      pTblNd( rCpy.pTblNd ), nMaxSize( rCpy.nMaxSize ), nLowerDiff( 0 ),
//STRIP001      pUndo( rCpy.pUndo ), nBoxWidth( nBoxWidth )
//STRIP001  {
//STRIP001      aLines.Insert( &rCpy.aLines );
//STRIP001      aLinesWidth.Insert( &rCpy.aLinesWidth, 0 );
//STRIP001  }
//STRIP001
//STRIP001  SwUndoTblNdsChg* CreateUndo( USHORT nUndoType )
//STRIP001  {
//STRIP001      return pUndo = new SwUndoTblNdsChg( nUndoType, aBoxes, *pTblNd );
//STRIP001  }
//STRIP001
//STRIP001  void LoopClear()
//STRIP001  {
//STRIP001      nLowerDiff = 0; nRemainWidth = 0;
//STRIP001  }
//STRIP001
//STRIP001  void AddBoxWidth( const SwTableBox& rBox, USHORT nWidth )
//STRIP001  {
//STRIP001      SwTableLinePtr p = (SwTableLine*)rBox.GetUpper();
//STRIP001      USHORT nFndPos;
//STRIP001      if( aLines.Insert( p, nFndPos ))
//STRIP001          aLinesWidth.Insert( nWidth, nFndPos );
//STRIP001      else
//STRIP001          aLinesWidth[ nFndPos ] += nWidth;
//STRIP001  }
//STRIP001
//STRIP001  USHORT GetBoxWidth( const SwTableLine& rLn ) const
//STRIP001  {
//STRIP001      SwTableLinePtr p = (SwTableLine*)&rLn;
//STRIP001      USHORT nFndPos;
//STRIP001      if( aLines.Seek_Entry( p, &nFndPos ) )
//STRIP001          nFndPos = aLinesWidth[ nFndPos ];
//STRIP001      else
//STRIP001          nFndPos = 0;
//STRIP001      return nFndPos;
//STRIP001  }
//STRIP001 };

//STRIP001 BOOL lcl_SetSelBoxWidth( SwTableLine* pLine, CR_SetBoxWidth& rParam,
//STRIP001                       SwTwips nDist, BOOL bCheck );
//STRIP001 BOOL lcl_SetOtherBoxWidth( SwTableLine* pLine, CR_SetBoxWidth& rParam,
//STRIP001                              SwTwips nDist, BOOL bCheck );
//STRIP001 BOOL lcl_InsSelBox( SwTableLine* pLine, CR_SetBoxWidth& rParam,
//STRIP001                              SwTwips nDist, BOOL bCheck );
//STRIP001 BOOL lcl_InsOtherBox( SwTableLine* pLine, CR_SetBoxWidth& rParam,
//STRIP001                              SwTwips nDist, BOOL bCheck );
//STRIP001 BOOL lcl_DelSelBox( SwTableLine* pLine, CR_SetBoxWidth& rParam,
//STRIP001                              SwTwips nDist, BOOL bCheck );
//STRIP001 BOOL lcl_DelOtherBox( SwTableLine* pLine, CR_SetBoxWidth& rParam,
//STRIP001                              SwTwips nDist, BOOL bCheck );

//STRIP001 typedef BOOL (*FN_lcl_SetBoxWidth)(SwTableLine*, CR_SetBoxWidth&, SwTwips, BOOL );

#if !defined( PRODUCT ) || defined( JP_DEBUG )

//STRIP001 void _CheckBoxWidth( const SwTableLine& rLine, SwTwips nSize );

//STRIP001 #define CHECKBOXWIDTH                                            \
//STRIP001  {                                                           \
//STRIP001      SwTwips nSize = GetFrmFmt()->GetFrmSize().GetWidth();   \
//STRIP001      for( USHORT n = 0; n < aLines.Count(); ++n  )           \
//STRIP001          ::_CheckBoxWidth( *aLines[ n ], nSize );            \
//STRIP001  }

//STRIP001 #define CHECKTABLELAYOUT                                            \
//STRIP001     {                                                               \
//STRIP001         for ( int i = 0; i < GetTabLines().Count(); ++i )    \
//STRIP001         {                                                           \
//STRIP001             SwFrmFmt* pFmt = GetTabLines()[i]->GetFrmFmt();  \
//STRIP001             SwClientIter aIter( *pFmt );                            \
//STRIP001             SwClient* pLast = aIter.GoStart();                      \
//STRIP001             if( pLast )                                             \
//STRIP001             {                                                       \
//STRIP001                 do                                                  \
//STRIP001                 {                                                   \
//STRIP001                     SwFrm *pFrm = PTR_CAST( SwFrm, pLast );         \
//STRIP001                     if ( pFrm &&                                    \
//STRIP001                          ((SwRowFrm*)pFrm)->GetTabLine() == GetTabLines()[i] ) \
//STRIP001                     {                                               \
//STRIP001                         ASSERT( pFrm->GetUpper()->IsTabFrm(),       \
//STRIP001                                 "Table layout does not match table structure" )       \
//STRIP001                     }                                               \
//STRIP001                 } while ( 0 != ( pLast = aIter++ ) );               \
//STRIP001             }                                                       \
//STRIP001         }                                                           \
//STRIP001     }

#else

#define CHECKBOXWIDTH
#define CHECKTABLELAYOUT

#endif


//STRIP001 struct CR_SetLineHeight
//STRIP001 {
//STRIP001  SwSelBoxes aBoxes;
//STRIP001  SwShareBoxFmts aShareFmts;
//STRIP001  SwTableNode* pTblNd;
//STRIP001  SwUndoTblNdsChg* pUndo;
//STRIP001  SwTwips nMaxSpace, nMaxHeight;
//STRIP001  USHORT nMode, nLines;
//STRIP001  BOOL bBigger, bTop, bSplittBox, bAnyBoxFnd;
//STRIP001
//STRIP001  CR_SetLineHeight( USHORT eType, SwTableNode* pTNd )
//STRIP001      : nMaxSpace( 0 ), nLines( 0 ), nMaxHeight( 0 ),
//STRIP001      bAnyBoxFnd( FALSE ), bSplittBox( FALSE ) ,
//STRIP001      pTblNd( pTNd ), pUndo( 0 )
//STRIP001  {
//STRIP001      bTop = WH_ROW_TOP == ( eType & 0xff ) || WH_CELL_TOP == ( eType & 0xff );
//STRIP001      bBigger = 0 != (eType & WH_FLAG_BIGGER );
//STRIP001      if( eType & WH_FLAG_INSDEL )
//STRIP001          bBigger = !bBigger;
//STRIP001      BOOL bTst = (0 != (eType & WH_FLAG_BIGGER )) ^ (0 != ( eType & WH_FLAG_INSDEL ));
//STRIP001      nMode = pTblNd->GetTable().GetTblChgMode();
//STRIP001  }
//STRIP001  CR_SetLineHeight( const CR_SetLineHeight& rCpy )
//STRIP001      : nMode( rCpy.nMode ), nMaxSpace( rCpy.nMaxSpace ),
//STRIP001      bBigger( rCpy.bBigger ), bTop( rCpy.bTop ),
//STRIP001      bSplittBox( rCpy.bSplittBox ), bAnyBoxFnd( rCpy.bAnyBoxFnd ),
//STRIP001      pTblNd( rCpy.pTblNd ), nLines( rCpy.nLines ),
//STRIP001      nMaxHeight( rCpy.nMaxHeight ),
//STRIP001      pUndo( rCpy.pUndo )
//STRIP001  {}
//STRIP001
//STRIP001  SwUndoTblNdsChg* CreateUndo( USHORT nUndoType )
//STRIP001  {
//STRIP001      return pUndo = new SwUndoTblNdsChg( nUndoType, aBoxes, *pTblNd );
//STRIP001  }
//STRIP001 };

//STRIP001 BOOL lcl_SetSelLineHeight( SwTableLine* pLine, CR_SetLineHeight& rParam,
//STRIP001                       SwTwips nDist, BOOL bCheck );
//STRIP001 BOOL lcl_SetOtherLineHeight( SwTableLine* pLine, CR_SetLineHeight& rParam,
//STRIP001                              SwTwips nDist, BOOL bCheck );
//STRIP001 BOOL lcl_InsDelSelLine( SwTableLine* pLine, CR_SetLineHeight& rParam,
//STRIP001                              SwTwips nDist, BOOL bCheck );

//STRIP001 typedef BOOL (*FN_lcl_SetLineHeight)(SwTableLine*, CR_SetLineHeight&, SwTwips, BOOL );

//STRIP001 _CpyTabFrm& _CpyTabFrm::operator=( const _CpyTabFrm& rCpyTabFrm )
//STRIP001 {
//STRIP001  pNewFrmFmt = rCpyTabFrm.pNewFrmFmt;
//STRIP001  Value = rCpyTabFrm.Value;
//STRIP001  return *this;
//STRIP001 }

//STRIP001 SV_DECL_VARARR_SORT( _CpyTabFrms, _CpyTabFrm, 0, 50 )
//STRIP001 SV_IMPL_VARARR_SORT( _CpyTabFrms, _CpyTabFrm )

//STRIP001 void lcl_DelCpyTabFrmFmts( _CpyTabFrm& rArr );

// ---------------------------------------------------------------

//STRIP001 struct _CpyPara
//STRIP001 {
//STRIP001  SwDoc* pDoc;
//STRIP001  SwTableNode* pTblNd;
//STRIP001  _CpyTabFrms& rTabFrmArr;
//STRIP001  SwTableLine* pInsLine;
//STRIP001  SwTableBox* pInsBox;
//STRIP001  ULONG nOldSize, nNewSize;           // zum Korrigieren der Size-Attribute
//STRIP001  USHORT nCpyCnt, nInsPos;
//STRIP001  BYTE nDelBorderFlag;
//STRIP001  BOOL bCpyCntnt;
//STRIP001
//STRIP001  _CpyPara( SwTableNode* pNd, USHORT nCopies, _CpyTabFrms& rFrmArr,
//STRIP001              BOOL bCopyContent = TRUE )
//STRIP001      : pDoc( pNd->GetDoc() ), pTblNd( pNd ), nCpyCnt(nCopies), rTabFrmArr(rFrmArr),
//STRIP001      pInsLine(0), pInsBox(0), nInsPos(0), nNewSize(0), nOldSize(0),
//STRIP001      bCpyCntnt( bCopyContent ), nDelBorderFlag( 0 )
//STRIP001      {}
//STRIP001  _CpyPara( const _CpyPara& rPara, SwTableLine* pLine )
//STRIP001      : pDoc(rPara.pDoc), pTblNd(rPara.pTblNd), nCpyCnt(rPara.nCpyCnt),
//STRIP001      rTabFrmArr(rPara.rTabFrmArr), pInsLine(pLine), pInsBox(rPara.pInsBox),
//STRIP001      nInsPos(0), nNewSize(rPara.nNewSize), nOldSize(0),
//STRIP001      bCpyCntnt( rPara.bCpyCntnt ), nDelBorderFlag( rPara.nDelBorderFlag )
//STRIP001      {}
//STRIP001  _CpyPara( const _CpyPara& rPara, SwTableBox* pBox )
//STRIP001      : pDoc(rPara.pDoc), pTblNd(rPara.pTblNd), nCpyCnt(rPara.nCpyCnt),
//STRIP001      rTabFrmArr(rPara.rTabFrmArr), pInsLine(rPara.pInsLine), pInsBox(pBox),
//STRIP001      nInsPos(0), nNewSize(rPara.nNewSize),nOldSize(rPara.nOldSize),
//STRIP001      bCpyCntnt( rPara.bCpyCntnt ), nDelBorderFlag( rPara.nDelBorderFlag )
//STRIP001      {}
//STRIP001  void SetBoxWidth( SwTableBox* pBox );
//STRIP001 };


//STRIP001 BOOL lcl_CopyCol( const _FndBox*& rpFndBox, void* pPara )
//STRIP001 {
//STRIP001  _CpyPara* pCpyPara = (_CpyPara*)pPara;
//STRIP001
//STRIP001  // suche das FrmFmt im Array aller Frame-Formate
//STRIP001  SwTableBox* pBox = (SwTableBox*)rpFndBox->GetBox();
//STRIP001  _CpyTabFrm aFindFrm( (SwTableBoxFmt*)pBox->GetFrmFmt() );
//STRIP001
//STRIP001  USHORT nFndPos;
//STRIP001  if( pCpyPara->nCpyCnt )
//STRIP001  {
//STRIP001      if( !pCpyPara->rTabFrmArr.Seek_Entry( aFindFrm, &nFndPos ))
//STRIP001      {
//STRIP001          // fuer das verschachtelte Kopieren sicher auch das neue Format
//STRIP001          // als alt.
//STRIP001          SwTableBoxFmt* pNewFmt = (SwTableBoxFmt*)pBox->ClaimFrmFmt();
//STRIP001
//STRIP001          // suche die selektierten Boxen in der Line:
//STRIP001          _FndLine* pCmpLine;
//STRIP001          SwFmtFrmSize aFrmSz( pNewFmt->GetFrmSize() );
//STRIP001          if( pBox->GetTabLines().Count() &&
//STRIP001              ( pCmpLine = rpFndBox->GetLines()[ 0 ])->GetBoxes().Count()
//STRIP001                  != pCmpLine->GetLine()->GetTabBoxes().Count() )
//STRIP001          {
//STRIP001              // die erste Line sollte reichen
//STRIP001              _FndBoxes& rFndBoxes = pCmpLine->GetBoxes();
//STRIP001              long nSz = 0;
//STRIP001              for( USHORT n = rFndBoxes.Count(); n; )
//STRIP001                  nSz += rFndBoxes[ --n ]->GetBox()->GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001              aFrmSz.SetWidth( aFrmSz.GetWidth() -
//STRIP001                                          nSz / ( pCpyPara->nCpyCnt + 1 ) );
//STRIP001              pNewFmt->SetAttr( aFrmSz );
//STRIP001              aFrmSz.SetWidth( nSz / ( pCpyPara->nCpyCnt + 1 ) );
//STRIP001
//STRIP001              // fuer die neue Box ein neues Format mit der Groesse anlegen!
//STRIP001              aFindFrm.pNewFrmFmt = (SwTableBoxFmt*)pNewFmt->GetDoc()->
//STRIP001                                          MakeTableLineFmt();
//STRIP001              *aFindFrm.pNewFrmFmt = *pNewFmt;
//STRIP001              aFindFrm.pNewFrmFmt->SetAttr( aFrmSz );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              aFrmSz.SetWidth( aFrmSz.GetWidth() / ( pCpyPara->nCpyCnt + 1 ) );
//STRIP001              pNewFmt->SetAttr( aFrmSz );
//STRIP001
//STRIP001              aFindFrm.pNewFrmFmt = pNewFmt;
//STRIP001              pCpyPara->rTabFrmArr.Insert( aFindFrm );
//STRIP001              aFindFrm.Value.pFrmFmt = pNewFmt;
//STRIP001              pCpyPara->rTabFrmArr.Insert( aFindFrm );
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          aFindFrm = pCpyPara->rTabFrmArr[ nFndPos ];
//STRIP001 //           aFindFrm.pNewFrmFmt->Add( pBox );
//STRIP001          pBox->ChgFrmFmt( (SwTableBoxFmt*)aFindFrm.pNewFrmFmt );
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if( pCpyPara->nDelBorderFlag &&
//STRIP001          pCpyPara->rTabFrmArr.Seek_Entry( aFindFrm, &nFndPos ))
//STRIP001          aFindFrm = pCpyPara->rTabFrmArr[ nFndPos ];
//STRIP001      else
//STRIP001          aFindFrm.pNewFrmFmt = (SwTableBoxFmt*)pBox->GetFrmFmt();
//STRIP001  }
//STRIP001
//STRIP001  if( rpFndBox->GetLines().Count() )
//STRIP001  {
//STRIP001      pBox = new SwTableBox( aFindFrm.pNewFrmFmt,
//STRIP001                  rpFndBox->GetLines().Count(), pCpyPara->pInsLine );
//STRIP001      pCpyPara->pInsLine->GetTabBoxes().C40_INSERT( SwTableBox, pBox, pCpyPara->nInsPos++);
//STRIP001      _CpyPara aPara( *pCpyPara, pBox );
//STRIP001      aPara.nDelBorderFlag &= 7;
//STRIP001
//STRIP001      ((_FndBox*)rpFndBox)->GetLines().ForEach( &lcl_CopyRow, &aPara );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      ::_InsTblBox( pCpyPara->pDoc, pCpyPara->pTblNd, pCpyPara->pInsLine,
//STRIP001                  aFindFrm.pNewFrmFmt, pBox, pCpyPara->nInsPos++ );
//STRIP001
//STRIP001      const _FndBoxes& rFndBxs = rpFndBox->GetUpper()->GetBoxes();
//STRIP001      if( 8 > pCpyPara->nDelBorderFlag
//STRIP001              ? pCpyPara->nDelBorderFlag
//STRIP001              : rpFndBox == rFndBxs[ rFndBxs.Count() - 1 ] )
//STRIP001      {
//STRIP001          const SvxBoxItem& rBoxItem = pBox->GetFrmFmt()->GetBox();
//STRIP001          if( 8 > pCpyPara->nDelBorderFlag
//STRIP001                  ? rBoxItem.GetTop()
//STRIP001                  : rBoxItem.GetRight() )
//STRIP001          {
//STRIP001              aFindFrm.Value.pFrmFmt = (SwTableBoxFmt*)pBox->GetFrmFmt();
//STRIP001
//STRIP001              SvxBoxItem aNew( rBoxItem );
//STRIP001              if( 8 > pCpyPara->nDelBorderFlag )
//STRIP001                  aNew.SetLine( 0, BOX_LINE_TOP );
//STRIP001              else
//STRIP001                  aNew.SetLine( 0, BOX_LINE_RIGHT );
//STRIP001
//STRIP001              if( 1 == pCpyPara->nDelBorderFlag ||
//STRIP001                  8 == pCpyPara->nDelBorderFlag )
//STRIP001              {
//STRIP001                  // es wird dahinter kopiert, bei allen Boxen die
//STRIP001                  // TopBorderLine loeschen
//STRIP001                  pBox = pCpyPara->pInsLine->GetTabBoxes()[
//STRIP001                                          pCpyPara->nInsPos - 1 ];
//STRIP001              }
//STRIP001
//STRIP001              aFindFrm.pNewFrmFmt = (SwTableBoxFmt*)pBox->GetFrmFmt();
//STRIP001
//STRIP001              // ansonsten wird davor kopiert und die erste Line behaelt
//STRIP001              // die TopLine und an der originalen wird sie entfernt
//STRIP001              pBox->ClaimFrmFmt()->SetAttr( aNew );
//STRIP001
//STRIP001              if( !pCpyPara->nCpyCnt )
//STRIP001                  pCpyPara->rTabFrmArr.Insert( aFindFrm );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL lcl_CopyRow( const _FndLine*& rpFndLine, void* pPara )
//STRIP001 {
//STRIP001  _CpyPara* pCpyPara = (_CpyPara*)pPara;
//STRIP001  SwTableLine* pNewLine = new SwTableLine(
//STRIP001                          (SwTableLineFmt*)rpFndLine->GetLine()->GetFrmFmt(),
//STRIP001                      rpFndLine->GetBoxes().Count(), pCpyPara->pInsBox );
//STRIP001  if( pCpyPara->pInsBox )
//STRIP001  {
//STRIP001      pCpyPara->pInsBox->GetTabLines().C40_INSERT( SwTableLine, pNewLine, pCpyPara->nInsPos++ );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pCpyPara->pTblNd->GetTable().GetTabLines().C40_INSERT( SwTableLine, pNewLine,
//STRIP001                                              pCpyPara->nInsPos++ );
//STRIP001  }
//STRIP001
//STRIP001  _CpyPara aPara( *pCpyPara, pNewLine );
//STRIP001  ((_FndLine*)rpFndLine)->GetBoxes().ForEach( &lcl_CopyCol, &aPara );
//STRIP001
//STRIP001  pCpyPara->nDelBorderFlag &= 0xf8;
//STRIP001  return TRUE;
//STRIP001 }

//-----------------------------------------------------------

//STRIP001 void lcl_InsCol( _FndLine* pFndLn, _CpyPara& rCpyPara, USHORT nCpyCnt,
//STRIP001              BOOL bBehind )
//STRIP001 {
//STRIP001  // Bug 29124: nicht nur in den Grundlines kopieren. Wenns geht, so weit
//STRIP001  //              runter wie moeglich.
//STRIP001  _FndBox* pFBox;
//STRIP001  if( 1 == pFndLn->GetBoxes().Count() &&
//STRIP001      !( pFBox = pFndLn->GetBoxes()[ 0 ] )->GetBox()->GetSttNd() )
//STRIP001  {
//STRIP001      // eine Box mit mehreren Lines, also in diese Lines einfuegen
//STRIP001      for( USHORT n = 0; n < pFBox->GetLines().Count(); ++n )
//STRIP001          lcl_InsCol( pFBox->GetLines()[ n ], rCpyPara, nCpyCnt, bBehind );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      rCpyPara.pInsLine = pFndLn->GetLine();
//STRIP001      SwTableBox* pBox = pFndLn->GetBoxes()[ bBehind ?
//STRIP001                  pFndLn->GetBoxes().Count()-1 : 0 ]->GetBox();
//STRIP001      rCpyPara.nInsPos = pFndLn->GetLine()->GetTabBoxes().C40_GETPOS( SwTableBox, pBox );
//STRIP001      USHORT nBoxPos = rCpyPara.nInsPos;
//STRIP001      if( bBehind )
//STRIP001          ++rCpyPara.nInsPos;
//STRIP001
//STRIP001      for( USHORT n = 0; n < nCpyCnt; ++n )
//STRIP001      {
//STRIP001          if( n + 1 == nCpyCnt && bBehind )
//STRIP001              rCpyPara.nDelBorderFlag = 9;
//STRIP001          else
//STRIP001              rCpyPara.nDelBorderFlag = 8;
//STRIP001          pFndLn->GetBoxes().ForEach( &lcl_CopyCol, &rCpyPara );
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 SwRowFrm* GetRowFrm( SwTableLine& rLine )
//STRIP001 {
//STRIP001     SwClientIter aIter( *rLine.GetFrmFmt() );
//STRIP001     for( SwClient* pFrm = aIter.First( TYPE( SwRowFrm )); pFrm;
//STRIP001             pFrm = aIter.Next() )
//STRIP001         if( ((SwRowFrm*)pFrm)->GetTabLine() == &rLine )
//STRIP001             return (SwRowFrm*)pFrm;
//STRIP001     return 0;
//STRIP001 }


//STRIP001 BOOL SwTable::InsertCol( SwDoc* pDoc, const SwSelBoxes& rBoxes,
//STRIP001                      USHORT nCnt, BOOL bBehind )
//STRIP001 {
//STRIP001  ASSERT( pDoc && rBoxes.Count() && nCnt, "keine gueltige Box-Liste" );
//STRIP001  SwTableNode* pTblNd = (SwTableNode*)rBoxes[0]->GetSttNd()->FindTableNode();
//STRIP001  if( !pTblNd )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // suche alle Boxen / Lines
//STRIP001  _FndBox aFndBox( 0, 0 );
//STRIP001  {
//STRIP001      _FndPara aPara( rBoxes, &aFndBox );
//STRIP001      GetTabLines().ForEach( &_FndLineCopyCol, &aPara );
//STRIP001  }
//STRIP001  if( !aFndBox.GetLines().Count() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SetHTMLTableLayout( 0 );    // MIB 9.7.97: HTML-Layout loeschen
//STRIP001
//STRIP001  //Lines fuer das Layout-Update herausuchen.
//STRIP001  aFndBox.SetTableLines( *this );
//STRIP001  aFndBox.DelFrms( *this );
//STRIP001  aFndBox.SaveChartData( *this );
//STRIP001
//STRIP001  _CpyTabFrms aTabFrmArr;
//STRIP001  _CpyPara aCpyPara( pTblNd, nCnt, aTabFrmArr );
//STRIP001
//STRIP001  for( USHORT n = 0; n < aFndBox.GetLines().Count(); ++n )
//STRIP001      lcl_InsCol( aFndBox.GetLines()[ n ], aCpyPara, nCnt, bBehind );
//STRIP001
//STRIP001  // dann raeume die Struktur dieser Line noch mal auf, generell alle
//STRIP001  GCLines();
//STRIP001
//STRIP001  //Layout updaten
//STRIP001  aFndBox.MakeFrms( *this );
//STRIP001  aFndBox.RestoreChartData( *this );
//STRIP001  CHECKBOXWIDTH
//STRIP001     CHECKTABLELAYOUT
//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 BOOL SwTable::InsertRow( SwDoc* pDoc, const SwSelBoxes& rBoxes,
//STRIP001                      USHORT nCnt, BOOL bBehind )
//STRIP001 {
//STRIP001  ASSERT( pDoc && rBoxes.Count() && nCnt, "keine gueltige Box-Liste" );
//STRIP001  SwTableNode* pTblNd = (SwTableNode*)rBoxes[0]->GetSttNd()->FindTableNode();
//STRIP001  if( !pTblNd )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // suche alle Boxen / Lines
//STRIP001  _FndBox aFndBox( 0, 0 );
//STRIP001  {
//STRIP001      _FndPara aPara( rBoxes, &aFndBox );
//STRIP001      GetTabLines().ForEach( &_FndLineCopyCol, &aPara );
//STRIP001  }
//STRIP001  if( !aFndBox.GetLines().Count() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SetHTMLTableLayout( 0 );    // MIB 9.7.97: HTML-Layout loeschen
//STRIP001
//STRIP001  _FndBox* pFndBox = &aFndBox;
//STRIP001  {
//STRIP001      _FndLine* pFndLine;
//STRIP001      while( 1 == pFndBox->GetLines().Count() &&
//STRIP001              1 == ( pFndLine = pFndBox->GetLines()[ 0 ])->GetBoxes().Count() )
//STRIP001      {
//STRIP001          // nicht zu weit runter, eine Line mit Boxen muss nachbleiben!!
//STRIP001          _FndBox* pTmpBox = pFndLine->GetBoxes()[ 0 ];
//STRIP001          if( pTmpBox->GetLines().Count() )
//STRIP001              pFndBox = pTmpBox;
//STRIP001          else
//STRIP001              break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  //Lines fuer das Layout-Update herausuchen.
//STRIP001  const FASTBOOL bLayout = 0 != SwClientIter( *GetFrmFmt() ).First( TYPE(SwTabFrm) );
//STRIP001  if ( bLayout )
//STRIP001  {
//STRIP001      aFndBox.SetTableLines( *this );
//STRIP001      if( pFndBox != &aFndBox )
//STRIP001          aFndBox.DelFrms( *this );
//STRIP001      aFndBox.SaveChartData( *this );
//STRIP001  }
//STRIP001
//STRIP001  _CpyTabFrms aTabFrmArr;
//STRIP001  _CpyPara aCpyPara( pTblNd, 0, aTabFrmArr );
//STRIP001
//STRIP001  SwTableLine* pLine = pFndBox->GetLines()[ bBehind ?
//STRIP001                  pFndBox->GetLines().Count()-1 : 0 ]->GetLine();
//STRIP001  if( &aFndBox == pFndBox )
//STRIP001      aCpyPara.nInsPos = GetTabLines().C40_GETPOS( SwTableLine, pLine );
//STRIP001  else
//STRIP001  {
//STRIP001      aCpyPara.pInsBox = pFndBox->GetBox();
//STRIP001      aCpyPara.nInsPos = pFndBox->GetBox()->GetTabLines().C40_GETPOS( SwTableLine, pLine );
//STRIP001  }
//STRIP001
//STRIP001  USHORT nLinePos = aCpyPara.nInsPos;
//STRIP001  if( bBehind )
//STRIP001  {
//STRIP001      ++aCpyPara.nInsPos;
//STRIP001      aCpyPara.nDelBorderFlag = 1;
//STRIP001  }
//STRIP001  else
//STRIP001      aCpyPara.nDelBorderFlag = 2;
//STRIP001
//STRIP001  for( USHORT nCpyCnt = 0; nCpyCnt < nCnt; ++nCpyCnt )
//STRIP001  {
//STRIP001      if( bBehind )
//STRIP001          aCpyPara.nDelBorderFlag = 1;
//STRIP001      pFndBox->GetLines().ForEach( &lcl_CopyRow, &aCpyPara );
//STRIP001  }
//STRIP001
//STRIP001  // dann raeume die Struktur dieser Line noch mal auf, generell alle
//STRIP001  if( !pDoc->IsInReading() )
//STRIP001      GCLines();
//STRIP001
//STRIP001  //Layout updaten
//STRIP001  if ( bLayout )
//STRIP001  {
//STRIP001      if( pFndBox != &aFndBox )
//STRIP001          aFndBox.MakeFrms( *this );
//STRIP001      else
//STRIP001          aFndBox.MakeNewFrms( *this, nCnt, bBehind );
//STRIP001      aFndBox.RestoreChartData( *this );
//STRIP001  }
//STRIP001  CHECKBOXWIDTH
//STRIP001     CHECKTABLELAYOUT

//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL _FndBoxAppendRowLine( const SwTableLine*& rpLine, void* pPara );

//STRIP001 BOOL _FndBoxAppendRowBox( const SwTableBox*& rpBox, void* pPara )
//STRIP001 {
//STRIP001  _FndPara* pFndPara = (_FndPara*)pPara;
//STRIP001  _FndBox* pFndBox = new _FndBox( (SwTableBox*)rpBox, pFndPara->pFndLine );
//STRIP001  if( rpBox->GetTabLines().Count() )
//STRIP001  {
//STRIP001      _FndPara aPara( *pFndPara, pFndBox );
//STRIP001      pFndBox->GetBox()->GetTabLines().ForEach( &_FndBoxAppendRowLine, &aPara );
//STRIP001      if( !pFndBox->GetLines().Count() )
//STRIP001          delete pFndBox;
//STRIP001  }
//STRIP001  else
//STRIP001      pFndPara->pFndLine->GetBoxes().C40_INSERT( _FndBox, pFndBox,
//STRIP001                      pFndPara->pFndLine->GetBoxes().Count() );
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL _FndBoxAppendRowLine( const SwTableLine*& rpLine, void* pPara )
//STRIP001 {
//STRIP001  _FndPara* pFndPara = (_FndPara*)pPara;
//STRIP001  _FndLine* pFndLine = new _FndLine( (SwTableLine*)rpLine, pFndPara->pFndBox );
//STRIP001  _FndPara aPara( *pFndPara, pFndLine );
//STRIP001  pFndLine->GetLine()->GetTabBoxes().ForEach( &_FndBoxAppendRowBox, &aPara );
//STRIP001  if( pFndLine->GetBoxes().Count() )
//STRIP001  {
//STRIP001      pFndPara->pFndBox->GetLines().C40_INSERT( _FndLine, pFndLine,
//STRIP001              pFndPara->pFndBox->GetLines().Count() );
//STRIP001  }
//STRIP001  else
//STRIP001      delete pFndLine;
//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 BOOL SwTable::AppendRow( SwDoc* pDoc, USHORT nCnt )
//STRIP001 {
//STRIP001  SwTableNode* pTblNd = (SwTableNode*)aSortCntBoxes[0]->GetSttNd()->FindTableNode();
//STRIP001  if( !pTblNd )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // suche alle Boxen / Lines
//STRIP001  _FndBox aFndBox( 0, 0 );
//STRIP001  {
//STRIP001      const SwTableLine* pLLine = GetTabLines()[ GetTabLines().Count()-1 ];
//STRIP001
//STRIP001      const SwSelBoxes* pBxs = 0;     // Dummy !!!
//STRIP001      _FndPara aPara( *pBxs, &aFndBox );
//STRIP001
//STRIP001      _FndBoxAppendRowLine( pLLine, &aPara );
//STRIP001  }
//STRIP001  if( !aFndBox.GetLines().Count() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SetHTMLTableLayout( 0 );    // MIB 9.7.97: HTML-Layout loeschen
//STRIP001
//STRIP001  //Lines fuer das Layout-Update herausuchen.
//STRIP001  const FASTBOOL bLayout = 0 != SwClientIter( *GetFrmFmt() ).First( TYPE(SwTabFrm) );
//STRIP001  if( bLayout )
//STRIP001  {
//STRIP001      aFndBox.SetTableLines( *this );
//STRIP001      aFndBox.SaveChartData( *this );
//STRIP001  }
//STRIP001
//STRIP001  _CpyTabFrms aTabFrmArr;
//STRIP001  _CpyPara aCpyPara( pTblNd, 0, aTabFrmArr );
//STRIP001  aCpyPara.nInsPos = GetTabLines().Count();
//STRIP001  aCpyPara.nDelBorderFlag = 1;
//STRIP001
//STRIP001  for( USHORT nCpyCnt = 0; nCpyCnt < nCnt; ++nCpyCnt )
//STRIP001  {
//STRIP001      aCpyPara.nDelBorderFlag = 1;
//STRIP001      aFndBox.GetLines().ForEach( &lcl_CopyRow, &aCpyPara );
//STRIP001  }
//STRIP001
//STRIP001  // dann raeume die Struktur dieser Line noch mal auf, generell alle
//STRIP001  if( !pDoc->IsInReading() )
//STRIP001      GCLines();
//STRIP001
//STRIP001  //Layout updaten
//STRIP001  if ( bLayout )
//STRIP001  {
//STRIP001      aFndBox.MakeNewFrms( *this, nCnt, TRUE );
//STRIP001      aFndBox.RestoreChartData( *this );
//STRIP001  }
//STRIP001  CHECKBOXWIDTH
//STRIP001     CHECKTABLELAYOUT

//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 void lcl_LastBoxSetWidth( SwTableBoxes &rBoxes, const long nOffset,
//STRIP001                          BOOL bFirst, SwShareBoxFmts& rShareFmts );

//STRIP001 void lcl_LastBoxSetWidthLine( SwTableLines &rLines, const long nOffset,
//STRIP001                              BOOL bFirst, SwShareBoxFmts& rShareFmts )
//STRIP001 {
//STRIP001  for ( USHORT i = 0; i < rLines.Count(); ++i )
//STRIP001      ::lcl_LastBoxSetWidth( rLines[i]->GetTabBoxes(), nOffset, bFirst,
//STRIP001                              rShareFmts );
//STRIP001 }

//STRIP001 void lcl_LastBoxSetWidth( SwTableBoxes &rBoxes, const long nOffset,
//STRIP001                          BOOL bFirst, SwShareBoxFmts& rShareFmts )
//STRIP001 {
//STRIP001  SwTableBox& rBox = *rBoxes[ bFirst ? 0 : rBoxes.Count() - 1 ];
//STRIP001  if( !rBox.GetSttNd() )
//STRIP001      ::lcl_LastBoxSetWidthLine( rBox.GetTabLines(), nOffset,
//STRIP001                                  bFirst, rShareFmts );
//STRIP001
//STRIP001  //Die Box anpassen
//STRIP001  SwFrmFmt *pBoxFmt = rBox.GetFrmFmt();
//STRIP001  SwFmtFrmSize aNew( pBoxFmt->GetFrmSize() );
//STRIP001  aNew.SetWidth( aNew.GetWidth() + nOffset );
//STRIP001  SwFrmFmt *pFmt = rShareFmts.GetFormat( *pBoxFmt, aNew );
//STRIP001  if( pFmt )
//STRIP001      rBox.ChgFrmFmt( (SwTableBoxFmt*)pFmt );
//STRIP001  else
//STRIP001  {
//STRIP001      pFmt = rBox.ClaimFrmFmt();
//STRIP001
//STRIP001      pFmt->LockModify();
//STRIP001      pFmt->SetAttr( aNew );
//STRIP001      pFmt->UnlockModify();
//STRIP001
//STRIP001      rShareFmts.AddFormat( *pBoxFmt, *pFmt );
//STRIP001  }
//STRIP001 }

//STRIP001 void _DeleteBox( SwTable& rTbl, SwTableBox* pBox, SwUndo* pUndo,
//STRIP001              BOOL bCalcNewSize, const BOOL bCorrBorder,
//STRIP001              SwShareBoxFmts* pShareFmts )
//STRIP001 {
//STRIP001  do {
//STRIP001      SwTwips nBoxSz = bCalcNewSize ?
//STRIP001              pBox->GetFrmFmt()->GetFrmSize().GetWidth() : 0;
//STRIP001      SwTableLine* pLine = pBox->GetUpper();
//STRIP001      SwTableBoxes& rTblBoxes = pLine->GetTabBoxes();
//STRIP001      USHORT nDelPos = rTblBoxes.C40_GETPOS( SwTableBox, pBox );
//STRIP001      SwTableBox* pUpperBox = pBox->GetUpper()->GetUpper();
//STRIP001
//STRIP001      // Sonderbehandlung fuer Umrandung:
//STRIP001      if( bCorrBorder && 1 < rTblBoxes.Count() )
//STRIP001      {
//STRIP001          BOOL bChgd = FALSE;
//STRIP001          const SvxBoxItem& rBoxItem = pBox->GetFrmFmt()->GetBox();
//STRIP001
//STRIP001          if( rBoxItem.GetLeft() || rBoxItem.GetRight() )
//STRIP001          {
//STRIP001              //JP 02.04.97:  1.Teil fuer Bug 36271
//STRIP001              // zuerst die linken/rechten Kanten
//STRIP001              if( nDelPos + 1 < rTblBoxes.Count() )
//STRIP001              {
//STRIP001                  SwTableBox* pNxtBox = rTblBoxes[ nDelPos + 1 ];
//STRIP001                  const SvxBoxItem& rNxtBoxItem = pNxtBox->GetFrmFmt()->GetBox();
//STRIP001
//STRIP001                  SwTableBox* pPrvBox = nDelPos ? rTblBoxes[ nDelPos - 1 ] : 0;
//STRIP001
//STRIP001                  if( pNxtBox->GetSttNd() && !rNxtBoxItem.GetLeft() &&
//STRIP001                      ( !pPrvBox || !pPrvBox->GetFrmFmt()->GetBox().GetRight()) )
//STRIP001                  {
//STRIP001                      SvxBoxItem aTmp( rNxtBoxItem );
//STRIP001                      aTmp.SetLine( rBoxItem.GetLeft() ? rBoxItem.GetLeft()
//STRIP001                                                       : rBoxItem.GetRight(),
//STRIP001                                                          BOX_LINE_LEFT );
//STRIP001                      if( pShareFmts )
//STRIP001                          pShareFmts->SetAttr( *pNxtBox, aTmp );
//STRIP001                      else
//STRIP001                          pNxtBox->ClaimFrmFmt()->SetAttr( aTmp );
//STRIP001                      bChgd = TRUE;
//STRIP001                  }
//STRIP001              }
//STRIP001              if( !bChgd && nDelPos )
//STRIP001              {
//STRIP001                  SwTableBox* pPrvBox = rTblBoxes[ nDelPos - 1 ];
//STRIP001                  const SvxBoxItem& rPrvBoxItem = pPrvBox->GetFrmFmt()->GetBox();
//STRIP001
//STRIP001                  SwTableBox* pNxtBox = nDelPos + 1 < rTblBoxes.Count()
//STRIP001                                          ? rTblBoxes[ nDelPos + 1 ] : 0;
//STRIP001
//STRIP001                  if( pPrvBox->GetSttNd() && !rPrvBoxItem.GetRight() &&
//STRIP001                      ( !pNxtBox || !pNxtBox->GetFrmFmt()->GetBox().GetLeft()) )
//STRIP001                  {
//STRIP001                      SvxBoxItem aTmp( rPrvBoxItem );
//STRIP001                      aTmp.SetLine( rBoxItem.GetLeft() ? rBoxItem.GetLeft()
//STRIP001                                                       : rBoxItem.GetRight(),
//STRIP001                                                          BOX_LINE_RIGHT );
//STRIP001                      if( pShareFmts )
//STRIP001                          pShareFmts->SetAttr( *pPrvBox, aTmp );
//STRIP001                      else
//STRIP001                          pPrvBox->ClaimFrmFmt()->SetAttr( aTmp );
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001      }
//STRIP001
//STRIP001      // erst die Box, dann die Nodes loeschen!!
//STRIP001      SwStartNode* pSttNd = (SwStartNode*)pBox->GetSttNd();
//STRIP001      if( pShareFmts )
//STRIP001          pShareFmts->RemoveFormat( *rTblBoxes[ nDelPos ]->GetFrmFmt() );
//STRIP001      rTblBoxes.DeleteAndDestroy( nDelPos );
//STRIP001
//STRIP001      if( pSttNd )
//STRIP001      {
//STRIP001          // ist das UndoObject zum speichern der Section vorbereitet?
//STRIP001          if( pUndo && UNDO_TABLE_DELBOX == pUndo->GetId() )
//STRIP001              ((SwUndoTblNdsChg*)pUndo)->SaveSection( pSttNd );
//STRIP001          else
//STRIP001              pSttNd->GetDoc()->DeleteSection( pSttNd );
//STRIP001      }
//STRIP001
//STRIP001      // auch die Zeile noch loeschen ??
//STRIP001      if( rTblBoxes.Count() )
//STRIP001      {
//STRIP001          // dann passe noch die Frame-SSize an
//STRIP001          BOOL bLastBox = nDelPos == rTblBoxes.Count();
//STRIP001          if( bLastBox )
//STRIP001              --nDelPos;
//STRIP001          pBox = rTblBoxes[nDelPos];
//STRIP001          if( bCalcNewSize )
//STRIP001          {
//STRIP001              SwFmtFrmSize aNew( pBox->GetFrmFmt()->GetFrmSize() );
//STRIP001              aNew.SetWidth( aNew.GetWidth() + nBoxSz );
//STRIP001              if( pShareFmts )
//STRIP001                  pShareFmts->SetSize( *pBox, aNew );
//STRIP001              else
//STRIP001                  pBox->ClaimFrmFmt()->SetAttr( aNew );
//STRIP001
//STRIP001              if( !pBox->GetSttNd() )
//STRIP001              {
//STRIP001                  // dann muss es auch rekursiv in allen Zeilen, in allen
//STRIP001                  // Zellen erfolgen!
//STRIP001                  SwShareBoxFmts aShareFmts;
//STRIP001                  ::lcl_LastBoxSetWidthLine( pBox->GetTabLines(), nBoxSz,
//STRIP001                                              !bLastBox,
//STRIP001                                              pShareFmts ? *pShareFmts
//STRIP001                                                         : aShareFmts );
//STRIP001              }
//STRIP001          }
//STRIP001          break;      // nichts mehr loeschen
//STRIP001      }
//STRIP001      // loesche die Line aus Tabelle/Box
//STRIP001      if( !pUpperBox )
//STRIP001      {
//STRIP001          // dann loesche auch noch die Line aus der Tabelle
//STRIP001          nDelPos = rTbl.GetTabLines().C40_GETPOS( SwTableLine, pLine );
//STRIP001          if( pShareFmts )
//STRIP001              pShareFmts->RemoveFormat( *rTbl.GetTabLines()[ nDelPos ]->GetFrmFmt() );
//STRIP001          rTbl.GetTabLines().DeleteAndDestroy( nDelPos );
//STRIP001          break;      // mehr kann nicht geloescht werden
//STRIP001      }
//STRIP001
//STRIP001      // dann loesche auch noch die Line
//STRIP001      pBox = pUpperBox;
//STRIP001      nDelPos = pBox->GetTabLines().C40_GETPOS( SwTableLine, pLine );
//STRIP001      if( pShareFmts )
//STRIP001          pShareFmts->RemoveFormat( *pBox->GetTabLines()[ nDelPos ]->GetFrmFmt() );
//STRIP001      pBox->GetTabLines().DeleteAndDestroy( nDelPos );
//STRIP001  } while( !pBox->GetTabLines().Count() );
//STRIP001 }

//STRIP001 SwTableBox* lcl_FndNxtPrvDelBox( const SwTableLines& rTblLns,
//STRIP001                              SwTwips nBoxStt, SwTwips nBoxWidth,
//STRIP001                              USHORT nLinePos, BOOL bNxt,
//STRIP001                              SwSelBoxes* pAllDelBoxes, USHORT* pCurPos )
//STRIP001 {
//STRIP001  SwTableBox* pFndBox = 0;
//STRIP001  do {
//STRIP001      if( bNxt )
//STRIP001          ++nLinePos;
//STRIP001      else
//STRIP001          --nLinePos;
//STRIP001      SwTableLine* pLine = rTblLns[ nLinePos ];
//STRIP001      SwTwips nFndBoxWidth, nFndWidth = nBoxStt + nBoxWidth;
//STRIP001      USHORT nBoxCnt = pLine->GetTabBoxes().Count();
//STRIP001
//STRIP001      for( USHORT n = 0; 0 < nFndWidth && n < nBoxCnt; ++n )
//STRIP001      {
//STRIP001          pFndBox = pLine->GetTabBoxes()[ n ];
//STRIP001          nFndWidth -= (nFndBoxWidth = pFndBox->GetFrmFmt()->
//STRIP001                                      GetFrmSize().GetWidth());
//STRIP001      }
//STRIP001
//STRIP001      // suche die erste ContentBox
//STRIP001      while( !pFndBox->GetSttNd() )
//STRIP001      {
//STRIP001          const SwTableLines& rLowLns = pFndBox->GetTabLines();
//STRIP001          if( bNxt )
//STRIP001              pFndBox = rLowLns[ 0 ]->GetTabBoxes()[ 0 ];
//STRIP001          else
//STRIP001              pFndBox = rLowLns[ rLowLns.Count() - 1 ]->GetTabBoxes()[ 0 ];
//STRIP001      }
//STRIP001
//STRIP001      if( Abs( nFndWidth ) > COLFUZZY ||
//STRIP001          Abs( nBoxWidth - nFndBoxWidth ) > COLFUZZY )
//STRIP001          pFndBox = 0;
//STRIP001      else if( pAllDelBoxes )
//STRIP001      {
//STRIP001          // falls der Vorganger auch geloscht wird, ist nicht zu tun
//STRIP001          USHORT nFndPos;
//STRIP001          if( !pAllDelBoxes->Seek_Entry( pFndBox, &nFndPos ) )
//STRIP001              break;
//STRIP001
//STRIP001          // sonst noch mal weitersuchen
//STRIP001          // Die Box muessen wir aber nicht nochmal abpruefen
//STRIP001          pFndBox = 0;
//STRIP001          if( nFndPos <= *pCurPos )
//STRIP001              --*pCurPos;
//STRIP001          pAllDelBoxes->Remove( nFndPos );
//STRIP001      }
//STRIP001  } while( bNxt ? ( nLinePos + 1 < rTblLns.Count() ) : nLinePos );
//STRIP001  return pFndBox;
//STRIP001 }

//STRIP001 void lcl_SaveUpperLowerBorder( SwTable& rTbl, const SwTableBox& rBox,
//STRIP001                              SwShareBoxFmts& rShareFmts,
//STRIP001                              SwSelBoxes* pAllDelBoxes = 0,
//STRIP001                              USHORT* pCurPos = 0 )
//STRIP001 {
//STRIP001 //JP 16.04.97:  2.Teil fuer Bug 36271
//STRIP001  BOOL bChgd = FALSE;
//STRIP001  const SwTableLine* pLine = rBox.GetUpper();
//STRIP001  const SwTableBoxes& rTblBoxes = pLine->GetTabBoxes();
//STRIP001  const SwTableBox* pUpperBox = &rBox;
//STRIP001  USHORT nDelPos = rTblBoxes.C40_GETPOS( SwTableBox, pUpperBox );
//STRIP001  pUpperBox = rBox.GetUpper()->GetUpper();
//STRIP001  const SvxBoxItem& rBoxItem = rBox.GetFrmFmt()->GetBox();
//STRIP001
//STRIP001  // dann die unteren/oberen Kanten
//STRIP001  if( rBoxItem.GetTop() || rBoxItem.GetBottom() )
//STRIP001  {
//STRIP001      bChgd = FALSE;
//STRIP001      const SwTableLines* pTblLns;
//STRIP001      if( pUpperBox )
//STRIP001          pTblLns = &pUpperBox->GetTabLines();
//STRIP001      else
//STRIP001          pTblLns = &rTbl.GetTabLines();
//STRIP001
//STRIP001      USHORT nLnPos = pTblLns->GetPos( pLine );
//STRIP001
//STRIP001      // bestimme die Attr.Position der akt. zu loeschenden Box
//STRIP001      // und suche dann in der unteren / oberen Line die entspr.
//STRIP001      // Gegenstuecke
//STRIP001      SwTwips nBoxStt = 0;
//STRIP001      for( USHORT n = 0; n < nDelPos; ++n )
//STRIP001          nBoxStt += rTblBoxes[ n ]->GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001      SwTwips nBoxWidth = rBox.GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001
//STRIP001      SwTableBox *pPrvBox = 0, *pNxtBox = 0;
//STRIP001      if( nLnPos )        // Vorgaenger?
//STRIP001          pPrvBox = ::lcl_FndNxtPrvDelBox( *pTblLns, nBoxStt, nBoxWidth,
//STRIP001                              nLnPos, FALSE, pAllDelBoxes, pCurPos );
//STRIP001
//STRIP001      if( nLnPos + 1 < pTblLns->Count() )     // Nachfolger?
//STRIP001          pNxtBox = ::lcl_FndNxtPrvDelBox( *pTblLns, nBoxStt, nBoxWidth,
//STRIP001                              nLnPos, TRUE, pAllDelBoxes, pCurPos );
//STRIP001
//STRIP001      if( pNxtBox && pNxtBox->GetSttNd() )
//STRIP001      {
//STRIP001          const SvxBoxItem& rNxtBoxItem = pNxtBox->GetFrmFmt()->GetBox();
//STRIP001          if( !rNxtBoxItem.GetTop() && ( !pPrvBox ||
//STRIP001              !pPrvBox->GetFrmFmt()->GetBox().GetBottom()) )
//STRIP001          {
//STRIP001              SvxBoxItem aTmp( rNxtBoxItem );
//STRIP001              aTmp.SetLine( rBoxItem.GetTop() ? rBoxItem.GetTop()
//STRIP001                                              : rBoxItem.GetBottom(),
//STRIP001                                              BOX_LINE_TOP );
//STRIP001              rShareFmts.SetAttr( *pNxtBox, aTmp );
//STRIP001              bChgd = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001      if( !bChgd && pPrvBox && pPrvBox->GetSttNd() )
//STRIP001      {
//STRIP001          const SvxBoxItem& rPrvBoxItem = pPrvBox->GetFrmFmt()->GetBox();
//STRIP001          if( !rPrvBoxItem.GetTop() && ( !pNxtBox ||
//STRIP001              !pNxtBox->GetFrmFmt()->GetBox().GetTop()) )
//STRIP001          {
//STRIP001              SvxBoxItem aTmp( rPrvBoxItem );
//STRIP001              aTmp.SetLine( rBoxItem.GetTop() ? rBoxItem.GetTop()
//STRIP001                                              : rBoxItem.GetBottom(),
//STRIP001                                              BOX_LINE_BOTTOM );
//STRIP001              rShareFmts.SetAttr( *pPrvBox, aTmp );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001  }
//STRIP001 }


//STRIP001 BOOL SwTable::DeleteSel( SwDoc* pDoc, const SwSelBoxes& rBoxes, SwUndo* pUndo,
//STRIP001                       const BOOL bDelMakeFrms, const BOOL bCorrBorder )
//STRIP001 {
//STRIP001  ASSERT( pDoc && rBoxes.Count(), "keine gueltigen Werte" );
//STRIP001  SwTableNode* pTblNd = (SwTableNode*)rBoxes[0]->GetSttNd()->FindTableNode();
//STRIP001  if( !pTblNd )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // es darf nie die gesamte Tabelle geloescht werden
//STRIP001  SwNodes& rNds = pDoc->GetNodes();
//STRIP001  if( rBoxes[0]->GetSttIdx()-1 == pTblNd->GetIndex() &&
//STRIP001      rBoxes[rBoxes.Count()-1]->GetSttNd()->EndOfSectionIndex()+1
//STRIP001      == pTblNd->EndOfSectionIndex() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SetHTMLTableLayout( 0 );    // MIB 9.7.97: HTML-Layout loeschen
//STRIP001
//STRIP001  //Lines fuer das Layout-Update herausuchen.
//STRIP001  _FndBox aFndBox( 0, 0 );
//STRIP001  if ( bDelMakeFrms )
//STRIP001  {
//STRIP001      aFndBox.SetTableLines( rBoxes, *this );
//STRIP001      aFndBox.DelFrms( *this );
//STRIP001  }
//STRIP001  aFndBox.SaveChartData( *this );
//STRIP001
//STRIP001  SwShareBoxFmts aShareFmts;
//STRIP001
//STRIP001  // erst die Umrandung umsetzen, dann loeschen
//STRIP001  if( bCorrBorder )
//STRIP001  {
//STRIP001      SwSelBoxes aBoxes;
//STRIP001      aBoxes.Insert( &rBoxes );
//STRIP001      for( USHORT n = 0; n < aBoxes.Count(); ++n )
//STRIP001          ::lcl_SaveUpperLowerBorder( *this, *rBoxes[ n ], aShareFmts,
//STRIP001                                      &aBoxes, &n );
//STRIP001  }
//STRIP001
//STRIP001  for( USHORT n = 0; n < rBoxes.Count(); ++n )
//STRIP001      _DeleteBox( *this, rBoxes[n], pUndo, TRUE, bCorrBorder, &aShareFmts );
//STRIP001
//STRIP001  // dann raeume die Struktur aller Lines auf
//STRIP001  GCLines();
//STRIP001
//STRIP001  if( bDelMakeFrms && aFndBox.AreLinesToRestore( *this ) )
//STRIP001      aFndBox.MakeFrms( *this );
//STRIP001  aFndBox.RestoreChartData( *this );
//STRIP001
//STRIP001     CHECKTABLELAYOUT
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }


// ---------------------------------------------------------------

//STRIP001 BOOL SwTable::SplitRow( SwDoc* pDoc, const SwSelBoxes& rBoxes, USHORT nCnt,
//STRIP001                         BOOL bSameHeight )
//STRIP001 {
//STRIP001  ASSERT( pDoc && rBoxes.Count() && nCnt, "keine gueltigen Werte" );
//STRIP001  SwTableNode* pTblNd = (SwTableNode*)rBoxes[0]->GetSttNd()->FindTableNode();
//STRIP001  if( !pTblNd )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SetHTMLTableLayout( 0 );    // MIB 9.7.97: HTML-Layout loeschen
//STRIP001
//STRIP001     // If the rows should get the same (min) height, we first have
//STRIP001     // to store the old row heights before deleting the frames
//STRIP001     long* pRowHeights = 0;
//STRIP001     if ( bSameHeight )
//STRIP001     {
//STRIP001         pRowHeights = new long[ rBoxes.Count() ];
//STRIP001         for( USHORT n = 0; n < rBoxes.Count(); ++n )
//STRIP001         {
//STRIP001             SwTableBox* pSelBox = *( rBoxes.GetData() + n );
//STRIP001             const SwRowFrm* pRow = GetRowFrm( *pSelBox->GetUpper() );
//STRIP001             ASSERT( pRow, "wo ist der Frm von der SwTableLine?" )
//STRIP001             SWRECTFN( pRow )
//STRIP001             pRowHeights[ n ] = (pRow->Frm().*fnRect->fnGetHeight)();
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001  //Lines fuer das Layout-Update herausuchen.
//STRIP001  _FndBox aFndBox( 0, 0 );
//STRIP001  aFndBox.SetTableLines( rBoxes, *this );
//STRIP001  aFndBox.DelFrms( *this );
//STRIP001  aFndBox.SaveChartData( *this );
//STRIP001
//STRIP001     for( USHORT n = 0; n < rBoxes.Count(); ++n )
//STRIP001  {
//STRIP001      SwTableBox* pSelBox = *( rBoxes.GetData() + n );
//STRIP001      ASSERT( pSelBox, "Box steht nicht in der Tabelle" );
//STRIP001
//STRIP001      // dann fuege in die Box nCnt neue Zeilen ein
//STRIP001      SwTableLine* pInsLine = pSelBox->GetUpper();
//STRIP001      SwTableBoxFmt* pFrmFmt = (SwTableBoxFmt*)pSelBox->GetFrmFmt();
//STRIP001
//STRIP001      // Hoehe der Line beachten, gegebenenfalls neu setzen
//STRIP001         SwFmtFrmSize aFSz( pInsLine->GetFrmFmt()->GetFrmSize() );
//STRIP001         if ( bSameHeight && ATT_VAR_SIZE == aFSz.GetSizeType() )
//STRIP001             aFSz.SetSizeType( ATT_MIN_SIZE );
//STRIP001
//STRIP001         BOOL bChgLineSz = 0 != aFSz.GetHeight() || bSameHeight;
//STRIP001         if ( bChgLineSz )
//STRIP001             aFSz.SetHeight( ( bSameHeight ? pRowHeights[ n ] : aFSz.GetHeight() ) /
//STRIP001                              (nCnt + 1) );
//STRIP001
//STRIP001      SwTableBox* pNewBox = new SwTableBox( pFrmFmt, nCnt, pInsLine );
//STRIP001      USHORT nBoxPos = pInsLine->GetTabBoxes().C40_GETPOS( SwTableBox, pSelBox );
//STRIP001      pInsLine->GetTabBoxes().Remove( nBoxPos );  // alte loeschen
//STRIP001      pInsLine->GetTabBoxes().C40_INSERT( SwTableBox, pNewBox, nBoxPos );
//STRIP001
//STRIP001      // Hintergrund- / Rand Attribut loeschen
//STRIP001      SwTableBox* pLastBox = pSelBox;         // zum verteilen der TextNodes !!
//STRIP001      // sollte Bereiche in der Box stehen, dann bleibt sie so bestehen
//STRIP001      // !! FALLS DAS GEAENDERT WIRD MUSS DAS UNDO ANGEPASST WERDEN !!!
//STRIP001      BOOL bMoveNodes = TRUE;
//STRIP001      {
//STRIP001          ULONG nSttNd = pLastBox->GetSttIdx() + 1,
//STRIP001                  nEndNd = pLastBox->GetSttNd()->EndOfSectionIndex();
//STRIP001          while( nSttNd < nEndNd )
//STRIP001              if( !pDoc->GetNodes()[ nSttNd++ ]->IsTxtNode() )
//STRIP001              {
//STRIP001                  bMoveNodes = FALSE;
//STRIP001                  break;
//STRIP001              }
//STRIP001      }
//STRIP001
//STRIP001      SwTableBoxFmt* pCpyBoxFrmFmt = (SwTableBoxFmt*)pSelBox->GetFrmFmt();
//STRIP001      BOOL bChkBorder = 0 != pCpyBoxFrmFmt->GetBox().GetTop();
//STRIP001      if( bChkBorder )
//STRIP001          pCpyBoxFrmFmt = (SwTableBoxFmt*)pSelBox->ClaimFrmFmt();
//STRIP001
//STRIP001      for( USHORT i = 0; i <= nCnt; ++i )
//STRIP001      {
//STRIP001          // also erstmal eine neue Linie in der neuen Box
//STRIP001          SwTableLine* pNewLine = new SwTableLine(
//STRIP001                  (SwTableLineFmt*)pInsLine->GetFrmFmt(), 1, pNewBox );
//STRIP001          if( bChgLineSz )
//STRIP001          {
//STRIP001              pNewLine->ClaimFrmFmt()->SetAttr( aFSz );
//STRIP001          }
//STRIP001
//STRIP001          pNewBox->GetTabLines().C40_INSERT( SwTableLine, pNewLine, i );
//STRIP001          // dann eine neue Box in der Line
//STRIP001          if( !i )        // haenge die originale Box ein
//STRIP001          {
//STRIP001              pSelBox->SetUpper( pNewLine );
//STRIP001              pNewLine->GetTabBoxes().C40_INSERT( SwTableBox, pSelBox, 0 );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              ::_InsTblBox( pDoc, pTblNd, pNewLine, pCpyBoxFrmFmt,
//STRIP001                              pLastBox, 0 );
//STRIP001
//STRIP001              if( bChkBorder )
//STRIP001              {
//STRIP001                  pCpyBoxFrmFmt = (SwTableBoxFmt*)pNewLine->GetTabBoxes()[ 0 ]->ClaimFrmFmt();
//STRIP001                  SvxBoxItem aTmp( pCpyBoxFrmFmt->GetBox() );
//STRIP001                  aTmp.SetLine( 0, BOX_LINE_TOP );
//STRIP001                  pCpyBoxFrmFmt->SetAttr( aTmp );
//STRIP001                  bChkBorder = FALSE;
//STRIP001              }
//STRIP001
//STRIP001              if( bMoveNodes )
//STRIP001              {
//STRIP001                  const SwNode* pEndNd = pLastBox->GetSttNd()->EndOfSectionNode();
//STRIP001                  if( pLastBox->GetSttIdx()+2 != pEndNd->GetIndex() )
//STRIP001                  {
//STRIP001                      // TextNodes verschieben
//STRIP001                      SwNodeRange aRg( *pLastBox->GetSttNd(), +2, *pEndNd );
//STRIP001                      pLastBox = pNewLine->GetTabBoxes()[0];  // neu setzen
//STRIP001                      SwNodeIndex aInsPos( *pLastBox->GetSttNd(), 1 );
//STRIP001                      pDoc->GetNodes()._MoveNodes(aRg, pDoc->GetNodes(), aInsPos, FALSE);
//STRIP001                      pDoc->GetNodes().Delete( aInsPos, 1 ); // den leeren noch loeschen
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      // in Boxen mit Lines darf es nur noch Size/Fillorder geben
//STRIP001      pFrmFmt = (SwTableBoxFmt*)pNewBox->ClaimFrmFmt();
//STRIP001      pFrmFmt->ResetAttr( RES_LR_SPACE, RES_FRMATR_END - 1 );
//STRIP001      pFrmFmt->ResetAttr( RES_BOXATR_BEGIN, RES_BOXATR_END - 1 );
//STRIP001  }
//STRIP001
//STRIP001     delete[] pRowHeights;
//STRIP001
//STRIP001  GCLines();
//STRIP001
//STRIP001     aFndBox.MakeFrms( *this );
//STRIP001  aFndBox.RestoreChartData( *this );
//STRIP001  CHECKBOXWIDTH
//STRIP001     CHECKTABLELAYOUT
//STRIP001     return TRUE;
//STRIP001 }

//STRIP001 BOOL SwTable::SplitCol( SwDoc* pDoc, const SwSelBoxes& rBoxes, USHORT nCnt )
//STRIP001 {
//STRIP001  ASSERT( pDoc && rBoxes.Count() && nCnt, "keine gueltigen Werte" );
//STRIP001  SwTableNode* pTblNd = (SwTableNode*)rBoxes[0]->GetSttNd()->FindTableNode();
//STRIP001  if( !pTblNd )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SetHTMLTableLayout( 0 );    // MIB 9.7.97: HTML-Layout loeschen
//STRIP001
//STRIP001  //Lines fuer das Layout-Update herausuchen.
//STRIP001  _FndBox aFndBox( 0, 0 );
//STRIP001  aFndBox.SetTableLines( rBoxes, *this );
//STRIP001  aFndBox.DelFrms( *this );
//STRIP001  aFndBox.SaveChartData( *this );
//STRIP001
//STRIP001  _CpyTabFrms aFrmArr;
//STRIP001  SvPtrarr aLastBoxArr;
//STRIP001  USHORT nFndPos;
//STRIP001  for( USHORT n = 0; n < rBoxes.Count(); ++n )
//STRIP001  {
//STRIP001      SwTableBox* pSelBox = *( rBoxes.GetData() + n );
//STRIP001      ASSERT( pSelBox, "Box steht nicht in der Tabelle" );
//STRIP001
//STRIP001      // dann teile die Box nCnt in nCnt Boxen
//STRIP001      SwTableLine* pInsLine = pSelBox->GetUpper();
//STRIP001      USHORT nBoxPos = pInsLine->GetTabBoxes().C40_GETPOS( SwTableBox, pSelBox );
//STRIP001
//STRIP001      // suche das FrmFmt im Array aller Frame-Formate
//STRIP001      SwTableBoxFmt* pLastBoxFmt;
//STRIP001      _CpyTabFrm aFindFrm( (SwTableBoxFmt*)pSelBox->GetFrmFmt() );
//STRIP001      if( !aFrmArr.Seek_Entry( aFindFrm, &nFndPos ))
//STRIP001      {
//STRIP001          // aender das FrmFmt
//STRIP001          aFindFrm.pNewFrmFmt = (SwTableBoxFmt*)pSelBox->ClaimFrmFmt();
//STRIP001          SwTwips nBoxSz = aFindFrm.pNewFrmFmt->GetFrmSize().GetWidth();
//STRIP001          SwTwips nNewBoxSz = nBoxSz / ( nCnt + 1 );
//STRIP001          aFindFrm.pNewFrmFmt->SetAttr( SwFmtFrmSize( ATT_VAR_SIZE,
//STRIP001                                                      nNewBoxSz, 0 ) );
//STRIP001          aFrmArr.Insert( aFindFrm );
//STRIP001
//STRIP001          pLastBoxFmt = aFindFrm.pNewFrmFmt;
//STRIP001          if( nBoxSz != ( nNewBoxSz * (nCnt + 1)))
//STRIP001          {
//STRIP001              // es bleibt ein Rest, also muss fuer die letzte Box ein
//STRIP001              // eigenes Format definiert werden
//STRIP001              pLastBoxFmt = new SwTableBoxFmt( *aFindFrm.pNewFrmFmt );
//STRIP001              pLastBoxFmt->SetAttr( SwFmtFrmSize( ATT_VAR_SIZE,
//STRIP001                              nBoxSz - ( nNewBoxSz * nCnt ), 0 ) );
//STRIP001          }
//STRIP001          void* p = pLastBoxFmt;
//STRIP001          aLastBoxArr.Insert( p, nFndPos );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          aFindFrm = aFrmArr[ nFndPos ];
//STRIP001          pSelBox->ChgFrmFmt( (SwTableBoxFmt*)aFindFrm.pNewFrmFmt );
//STRIP001          pLastBoxFmt = (SwTableBoxFmt*)aLastBoxArr[ nFndPos ];
//STRIP001      }
//STRIP001
//STRIP001      // dann fuege mal an der Position die neuen Boxen ein
//STRIP001      for( USHORT i = 1; i < nCnt; ++i )
//STRIP001          ::_InsTblBox( pDoc, pTblNd, pInsLine, aFindFrm.pNewFrmFmt,
//STRIP001                      pSelBox, nBoxPos + i ); // dahinter einfuegen
//STRIP001
//STRIP001      ::_InsTblBox( pDoc, pTblNd, pInsLine, pLastBoxFmt,
//STRIP001                  pSelBox, nBoxPos + nCnt );  // dahinter einfuegen
//STRIP001
//STRIP001      // Sonderbehandlung fuer die Umrandung:
//STRIP001      const SvxBoxItem& rBoxItem = aFindFrm.pNewFrmFmt->GetBox();
//STRIP001      if( rBoxItem.GetRight() )
//STRIP001      {
//STRIP001          pInsLine->GetTabBoxes()[ nBoxPos + nCnt ]->ClaimFrmFmt();
//STRIP001
//STRIP001          SvxBoxItem aTmp( rBoxItem );
//STRIP001          aTmp.SetLine( 0, BOX_LINE_RIGHT );
//STRIP001          aFindFrm.pNewFrmFmt->SetAttr( aTmp );
//STRIP001
//STRIP001          // und dann das Format aus dem "cache" entfernen
//STRIP001          for( USHORT i = aFrmArr.Count(); i; )
//STRIP001          {
//STRIP001              const _CpyTabFrm& rCTF = aFrmArr[ --i ];
//STRIP001              if( rCTF.pNewFrmFmt == aFindFrm.pNewFrmFmt ||
//STRIP001                  rCTF.Value.pFrmFmt == aFindFrm.pNewFrmFmt )
//STRIP001              {
//STRIP001                  aFrmArr.Remove( i );
//STRIP001                  aLastBoxArr.Remove( i );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  //Layout updaten
//STRIP001  aFndBox.MakeFrms( *this );
//STRIP001  aFndBox.RestoreChartData( *this );
//STRIP001  CHECKBOXWIDTH
//STRIP001     CHECKTABLELAYOUT
//STRIP001  return TRUE;
//STRIP001 }

// ---------------------------------------------------------------

/*
    ----------------------- >> MERGE << ------------------------
     Algorythmus:
        ist in der _FndBox nur eine Line angegeben, nehme die Line
        und teste die Anzahl der Boxen
        - ist mehr als 1 Box angegeben, so wird auf Boxenebene zusammen-
            gefasst, d.H. die neue Box wird so Breit wie die alten.
            - Alle Lines die ueber/unter dem Bereich liegen werden in die
            Box als Line + Box mit Lines eingefuegt
            - Alle Lines die vor/hinter dem Bereich liegen werden in
            die Boxen Left/Right eingetragen

    ----------------------- >> MERGE << ------------------------
*/

//STRIP001 void lcl_CpyLines( USHORT nStt, USHORT nEnd,
//STRIP001                              SwTableLines& rLines,
//STRIP001                              SwTableBox* pInsBox,
//STRIP001                              USHORT nPos = USHRT_MAX )
//STRIP001 {
//STRIP001  for( USHORT n = nStt; n < nEnd; ++n )
//STRIP001      rLines[n]->SetUpper( pInsBox );
//STRIP001  if( USHRT_MAX == nPos )
//STRIP001      nPos = pInsBox->GetTabLines().Count();
//STRIP001  pInsBox->GetTabLines().Insert( &rLines, nPos, nStt, nEnd );
//STRIP001  rLines.Remove( nStt, nEnd - nStt );
//STRIP001 }

//STRIP001 void lcl_CpyBoxes( USHORT nStt, USHORT nEnd,
//STRIP001                              SwTableBoxes& rBoxes,
//STRIP001                              SwTableLine* pInsLine,
//STRIP001                              USHORT nPos = USHRT_MAX )
//STRIP001 {
//STRIP001  for( USHORT n = nStt; n < nEnd; ++n )
//STRIP001      rBoxes[n]->SetUpper( pInsLine );
//STRIP001  if( USHRT_MAX == nPos )
//STRIP001      nPos = pInsLine->GetTabBoxes().Count();
//STRIP001  pInsLine->GetTabBoxes().Insert( &rBoxes, nPos, nStt, nEnd );
//STRIP001  rBoxes.Remove( nStt, nEnd - nStt );
//STRIP001 }

//STRIP001 void lcl_CalcWidth( SwTableBox* pBox )
//STRIP001 {
//STRIP001  // Annahme: jede Line in der Box ist gleich gross
//STRIP001  SwFrmFmt* pFmt = pBox->ClaimFrmFmt();
//STRIP001  ASSERT( pBox->GetTabLines().Count(), "Box hat keine Lines" );
//STRIP001
//STRIP001  SwTableLine* pLine = pBox->GetTabLines()[0];
//STRIP001  ASSERT( pLine, "Box steht in keiner Line" );
//STRIP001
//STRIP001  long nWidth = 0;
//STRIP001  for( USHORT n = 0; n < pLine->GetTabBoxes().Count(); ++n )
//STRIP001      nWidth += pLine->GetTabBoxes()[n]->GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001
//STRIP001  pFmt->SetAttr( SwFmtFrmSize( ATT_VAR_SIZE, nWidth, 0 ));
//STRIP001
//STRIP001  // in Boxen mit Lines darf es nur noch Size/Fillorder geben
//STRIP001  pFmt->ResetAttr( RES_LR_SPACE, RES_FRMATR_END - 1 );
//STRIP001  pFmt->ResetAttr( RES_BOXATR_BEGIN, RES_BOXATR_END - 1 );
//STRIP001 }



//STRIP001 struct _InsULPara
//STRIP001 {
//STRIP001  SwTableNode* pTblNd;
//STRIP001  SwTableLine* pInsLine;
//STRIP001  SwTableBox* pInsBox;
//STRIP001  BOOL bUL_LR : 1;        // Upper-Lower(TRUE) oder Left-Right(FALSE) ?
//STRIP001  BOOL bUL : 1;           // Upper-Left(TRUE) oder Lower-Right(FALSE) ?
//STRIP001
//STRIP001  SwTableBox* pLeftBox;
//STRIP001  SwTableBox* pRightBox;
//STRIP001  SwTableBox* pMergeBox;
//STRIP001
//STRIP001  _InsULPara( SwTableNode* pTNd, BOOL bUpperLower, BOOL bUpper,
//STRIP001              SwTableBox* pLeft, SwTableBox* pMerge, SwTableBox* pRight,
//STRIP001              SwTableLine* pLine=0, SwTableBox* pBox=0 )
//STRIP001      : pTblNd( pTNd ), pInsLine( pLine ), pInsBox( pBox ),
//STRIP001      pLeftBox( pLeft ), pMergeBox( pMerge ), pRightBox( pRight )
//STRIP001      {   bUL_LR = bUpperLower; bUL = bUpper; }
//STRIP001
//STRIP001  void SetLeft( SwTableBox* pBox=0 )
//STRIP001      { bUL_LR = FALSE;   bUL = TRUE; if( pBox ) pInsBox = pBox; }
//STRIP001  void SetRight( SwTableBox* pBox=0 )
//STRIP001      { bUL_LR = FALSE;   bUL = FALSE; if( pBox ) pInsBox = pBox; }
//STRIP001  void SetUpper( SwTableLine* pLine=0 )
//STRIP001      { bUL_LR = TRUE;    bUL = TRUE;  if( pLine ) pInsLine = pLine; }
//STRIP001  void SetLower( SwTableLine* pLine=0 )
//STRIP001      { bUL_LR = TRUE;    bUL = FALSE; if( pLine ) pInsLine = pLine; }
//STRIP001 };


//STRIP001 BOOL lcl_Merge_MoveBox( const _FndBox*& rpFndBox, void* pPara )
//STRIP001 {
//STRIP001  _InsULPara* pULPara = (_InsULPara*)pPara;
//STRIP001  SwTableBoxes* pBoxes;
//STRIP001
//STRIP001  USHORT nStt = 0, nEnd = rpFndBox->GetLines().Count();
//STRIP001  USHORT nInsPos = USHRT_MAX;
//STRIP001  if( !pULPara->bUL_LR )  // Left/Right
//STRIP001  {
//STRIP001      USHORT nPos;
//STRIP001      SwTableBox* pFndBox = (SwTableBox*)rpFndBox->GetBox();
//STRIP001      pBoxes = &pFndBox->GetUpper()->GetTabBoxes();
//STRIP001      if( pULPara->bUL )  // Left ?
//STRIP001      {
//STRIP001          // gibt es noch davor Boxen, dann move sie
//STRIP001          if( 0 != ( nPos = pBoxes->C40_GETPOS( SwTableBox, pFndBox )) )
//STRIP001              lcl_CpyBoxes( 0, nPos, *pBoxes, pULPara->pInsLine );
//STRIP001      }
//STRIP001      else                // Right
//STRIP001          // gibt es noch dahinter Boxen, dann move sie
//STRIP001          if( (nPos = pBoxes->C40_GETPOS( SwTableBox, pFndBox )) +1 < pBoxes->Count() )
//STRIP001          {
//STRIP001              nInsPos = pULPara->pInsLine->GetTabBoxes().Count();
//STRIP001              lcl_CpyBoxes( nPos+1, pBoxes->Count(),
//STRIP001                                  *pBoxes, pULPara->pInsLine );
//STRIP001          }
//STRIP001  }
//STRIP001  // Upper/Lower und gehts noch tiefer ??
//STRIP001  else if( rpFndBox->GetLines().Count() )
//STRIP001  {
//STRIP001      // suche nur die Line, ab der Verschoben werden muss
//STRIP001      nStt = pULPara->bUL ? 0 : rpFndBox->GetLines().Count()-1;
//STRIP001      nEnd = nStt+1;
//STRIP001  }
//STRIP001
//STRIP001  pBoxes = &pULPara->pInsLine->GetTabBoxes();
//STRIP001
//STRIP001  // geht es noch eine weitere Stufe runter?
//STRIP001  if( rpFndBox->GetBox()->GetTabLines().Count() )
//STRIP001  {
//STRIP001      SwTableBox* pBox = new SwTableBox(
//STRIP001              (SwTableBoxFmt*)rpFndBox->GetBox()->GetFrmFmt(), 0, pULPara->pInsLine );
//STRIP001      _InsULPara aPara( *pULPara );
//STRIP001      aPara.pInsBox = pBox;
//STRIP001      ((_FndBox*)rpFndBox)->GetLines().ForEach( nStt, nEnd,
//STRIP001                                              &lcl_Merge_MoveLine, &aPara );
//STRIP001      if( pBox->GetTabLines().Count() )
//STRIP001      {
//STRIP001          if( USHRT_MAX == nInsPos )
//STRIP001              nInsPos = pBoxes->Count();
//STRIP001          pBoxes->C40_INSERT( SwTableBox, pBox, nInsPos );
//STRIP001          lcl_CalcWidth( pBox );      // bereche die Breite der Box
//STRIP001      }
//STRIP001      else
//STRIP001          delete pBox;
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL lcl_Merge_MoveLine( const _FndLine*& rpFndLine, void* pPara )
//STRIP001 {
//STRIP001  _InsULPara* pULPara = (_InsULPara*)pPara;
//STRIP001  SwTableLines* pLines;
//STRIP001
//STRIP001  USHORT nStt = 0, nEnd = rpFndLine->GetBoxes().Count();
//STRIP001  USHORT nInsPos = USHRT_MAX;
//STRIP001  if( pULPara->bUL_LR )   // UpperLower ?
//STRIP001  {
//STRIP001      USHORT nPos;
//STRIP001      SwTableLine* pFndLn = (SwTableLine*)rpFndLine->GetLine();
//STRIP001      pLines = pFndLn->GetUpper() ?
//STRIP001                      &pFndLn->GetUpper()->GetTabLines() :
//STRIP001                      &pULPara->pTblNd->GetTable().GetTabLines();
//STRIP001
//STRIP001      SwTableBox* pLBx = rpFndLine->GetBoxes()[0]->GetBox();
//STRIP001      SwTableBox* pRBx = rpFndLine->GetBoxes()[
//STRIP001                          rpFndLine->GetBoxes().Count()-1]->GetBox();
//STRIP001      USHORT nLeft = pFndLn->GetTabBoxes().C40_GETPOS( SwTableBox, pLBx );
//STRIP001      USHORT nRight = pFndLn->GetTabBoxes().C40_GETPOS( SwTableBox, pRBx );
//STRIP001
//STRIP001 //       if( ( nLeft && nRight+1 < pFndLn->GetTabBoxes().Count() ) ||
//STRIP001 //           ( !nLeft && nRight+1 >= pFndLn->GetTabBoxes().Count() ) )
//STRIP001      if( !nLeft || nRight == pFndLn->GetTabBoxes().Count() )
//STRIP001      {
//STRIP001          if( pULPara->bUL )  // Upper ?
//STRIP001          {
//STRIP001              // gibt es noch davor Zeilen, dann move sie
//STRIP001              if( 0 != ( nPos = pLines->C40_GETPOS( SwTableLine, pFndLn )) )
//STRIP001                  lcl_CpyLines( 0, nPos, *pLines, pULPara->pInsBox );
//STRIP001          }
//STRIP001          else
//STRIP001              // gibt es noch dahinter Zeilen, dann move sie
//STRIP001              if( (nPos = pLines->C40_GETPOS( SwTableLine, pFndLn )) +1 < pLines->Count() )
//STRIP001              {
//STRIP001                  nInsPos = pULPara->pInsBox->GetTabLines().Count();
//STRIP001                  lcl_CpyLines( nPos+1, pLines->Count(), *pLines,
//STRIP001                                      pULPara->pInsBox );
//STRIP001              }
//STRIP001      }
//STRIP001      else if( nLeft )
//STRIP001      {
//STRIP001          // es gibt links noch weitere Boxen, also setze Left-
//STRIP001          // und Merge-Box in eine Box und Line, fuege davor/dahinter
//STRIP001          // eine Line mit Box ein, in die die oberen/unteren Lines
//STRIP001          // eingefuegt werden
//STRIP001          SwTableLine* pInsLine = pULPara->pLeftBox->GetUpper();
//STRIP001          SwTableBox* pLMBox = new SwTableBox(
//STRIP001              (SwTableBoxFmt*)pULPara->pLeftBox->GetFrmFmt(), 0, pInsLine );
//STRIP001          SwTableLine* pLMLn = new SwTableLine(
//STRIP001                      (SwTableLineFmt*)pInsLine->GetFrmFmt(), 2, pLMBox );
//STRIP001          pLMLn->ClaimFrmFmt()->ResetAttr( RES_FRM_SIZE );
//STRIP001
//STRIP001          pLMBox->GetTabLines().C40_INSERT( SwTableLine, pLMLn, 0 );
//STRIP001
//STRIP001          lcl_CpyBoxes( 0, 2, pInsLine->GetTabBoxes(), pLMLn );
//STRIP001
//STRIP001          pInsLine->GetTabBoxes().C40_INSERT( SwTableBox, pLMBox, 0 );
//STRIP001
//STRIP001          if( pULPara->bUL )  // Upper ?
//STRIP001          {
//STRIP001              // gibt es noch davor Zeilen, dann move sie
//STRIP001              if( 0 != ( nPos = pLines->C40_GETPOS( SwTableLine, pFndLn )) )
//STRIP001                  lcl_CpyLines( 0, nPos, *pLines, pLMBox, 0 );
//STRIP001          }
//STRIP001          else
//STRIP001              // gibt es noch dahinter Zeilen, dann move sie
//STRIP001              if( (nPos = pLines->C40_GETPOS( SwTableLine, pFndLn )) +1 < pLines->Count() )
//STRIP001                  lcl_CpyLines( nPos+1, pLines->Count(), *pLines,
//STRIP001                                      pLMBox );
//STRIP001          lcl_CalcWidth( pLMBox );        // bereche die Breite der Box
//STRIP001      }
//STRIP001      else if( nRight+1 < pFndLn->GetTabBoxes().Count() )
//STRIP001      {
//STRIP001          // es gibt rechts noch weitere Boxen, also setze Right-
//STRIP001          // und Merge-Box in eine Box und Line, fuege davor/dahinter
//STRIP001          // eine Line mit Box ein, in die die oberen/unteren Lines
//STRIP001          // eingefuegt werden
//STRIP001          SwTableLine* pInsLine = pULPara->pRightBox->GetUpper();
//STRIP001          SwTableBox* pRMBox;
//STRIP001          if( pULPara->pLeftBox->GetUpper() == pInsLine )
//STRIP001          {
//STRIP001              pRMBox = new SwTableBox(
//STRIP001                  (SwTableBoxFmt*)pULPara->pRightBox->GetFrmFmt(), 0, pInsLine );
//STRIP001              SwTableLine* pRMLn = new SwTableLine(
//STRIP001                  (SwTableLineFmt*)pInsLine->GetFrmFmt(), 2, pRMBox );
//STRIP001              pRMLn->ClaimFrmFmt()->ResetAttr( RES_FRM_SIZE );
//STRIP001              pRMBox->GetTabLines().C40_INSERT( SwTableLine, pRMLn, 0 );
//STRIP001
//STRIP001              lcl_CpyBoxes( 1, 3, pInsLine->GetTabBoxes(), pRMLn );
//STRIP001
//STRIP001              pInsLine->GetTabBoxes().C40_INSERT( SwTableBox, pRMBox, 0 );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              // Left und Merge wurden schon zusammengefuegt, also move
//STRIP001              // Right auch mit in die Line
//STRIP001
//STRIP001              pInsLine = pULPara->pLeftBox->GetUpper();
//STRIP001              USHORT nMvPos = pULPara->pRightBox->GetUpper()->GetTabBoxes().
//STRIP001                                  C40_GETPOS( SwTableBox, pULPara->pRightBox );
//STRIP001              lcl_CpyBoxes( nMvPos, nMvPos+1,
//STRIP001                          pULPara->pRightBox->GetUpper()->GetTabBoxes(),
//STRIP001                          pInsLine );
//STRIP001              pRMBox = pInsLine->GetUpper();
//STRIP001
//STRIP001              // sind schon Lines vorhanden, dann muessen diese in eine
//STRIP001              // neue Line und Box
//STRIP001              nMvPos = pRMBox->GetTabLines().C40_GETPOS( SwTableLine, pInsLine );
//STRIP001              if( pULPara->bUL ? nMvPos
//STRIP001                              : nMvPos+1 < pRMBox->GetTabLines().Count() )
//STRIP001              {
//STRIP001                  // alle Lines zu einer neuen Line und Box zusammenfassen
//STRIP001                  SwTableLine* pNewLn = new SwTableLine(
//STRIP001                      (SwTableLineFmt*)pInsLine->GetFrmFmt(), 1, pRMBox );
//STRIP001                  pNewLn->ClaimFrmFmt()->ResetAttr( RES_FRM_SIZE );
//STRIP001                  pRMBox->GetTabLines().C40_INSERT( SwTableLine, pNewLn,
//STRIP001                          pULPara->bUL ? nMvPos : nMvPos+1 );
//STRIP001                  pRMBox = new SwTableBox( (SwTableBoxFmt*)pRMBox->GetFrmFmt(), 0, pNewLn );
//STRIP001                  pNewLn->GetTabBoxes().C40_INSERT( SwTableBox, pRMBox, 0 );
//STRIP001
//STRIP001                  USHORT nPos1, nPos2;
//STRIP001                  if( pULPara->bUL )
//STRIP001                      nPos1 = 0,
//STRIP001                      nPos2 = nMvPos;
//STRIP001                  else
//STRIP001                      nPos1 = nMvPos+2,
//STRIP001                      nPos2 = pNewLn->GetUpper()->GetTabLines().Count();
//STRIP001
//STRIP001                  lcl_CpyLines( nPos1, nPos2,
//STRIP001                              pNewLn->GetUpper()->GetTabLines(), pRMBox );
//STRIP001                  lcl_CalcWidth( pRMBox );        // bereche die Breite der Box
//STRIP001
//STRIP001                  pRMBox = new SwTableBox( (SwTableBoxFmt*)pRMBox->GetFrmFmt(), 0, pNewLn );
//STRIP001                  pNewLn->GetTabBoxes().C40_INSERT( SwTableBox, pRMBox,
//STRIP001                                  pNewLn->GetTabBoxes().Count() );
//STRIP001              }
//STRIP001          }
//STRIP001          if( pULPara->bUL )  // Upper ?
//STRIP001          {
//STRIP001              // gibt es noch davor Zeilen, dann move sie
//STRIP001              if( 0 != ( nPos = pLines->C40_GETPOS( SwTableLine, pFndLn )) )
//STRIP001                  lcl_CpyLines( 0, nPos, *pLines, pRMBox, 0 );
//STRIP001          }
//STRIP001          else
//STRIP001              // gibt es noch dahinter Zeilen, dann move sie
//STRIP001              if( (nPos = pLines->C40_GETPOS( SwTableLine, pFndLn )) +1 < pLines->Count() )
//STRIP001                  lcl_CpyLines( nPos+1, pLines->Count(), *pLines,
//STRIP001                                      pRMBox );
//STRIP001          lcl_CalcWidth( pRMBox );        // bereche die Breite der Box
//STRIP001      }
//STRIP001      else
//STRIP001          ASSERT( FALSE , "Was denn nun" );
//STRIP001  }
//STRIP001  // Left/Right
//STRIP001  else
//STRIP001  {
//STRIP001      // suche nur die Line, ab der Verschoben werden muss
//STRIP001      nStt = pULPara->bUL ? 0 : rpFndLine->GetBoxes().Count()-1;
//STRIP001      nEnd = nStt+1;
//STRIP001  }
//STRIP001  pLines = &pULPara->pInsBox->GetTabLines();
//STRIP001
//STRIP001  SwTableLine* pNewLine = new SwTableLine(
//STRIP001      (SwTableLineFmt*)rpFndLine->GetLine()->GetFrmFmt(), 0, pULPara->pInsBox );
//STRIP001  _InsULPara aPara( *pULPara );       // kopieren
//STRIP001  aPara.pInsLine = pNewLine;
//STRIP001  ((_FndLine*)rpFndLine)->GetBoxes().ForEach( nStt, nEnd,
//STRIP001                                              &lcl_Merge_MoveBox, &aPara );
//STRIP001  if( pNewLine->GetTabBoxes().Count() )
//STRIP001  {
//STRIP001      if( USHRT_MAX == nInsPos )
//STRIP001          nInsPos = pLines->Count();
//STRIP001      pLines->C40_INSERT( SwTableLine, pNewLine, nInsPos );
//STRIP001  }
//STRIP001  else
//STRIP001      delete pNewLine;
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }


//STRIP001 BOOL SwTable::Merge( SwDoc* pDoc, const SwSelBoxes& rBoxes,
//STRIP001                  SwTableBox* pMergeBox, SwUndoTblMerge* pUndo )
//STRIP001 {
//STRIP001  ASSERT( pDoc && rBoxes.Count() && pMergeBox, "keine gueltigen Werte" );
//STRIP001  SwTableNode* pTblNd = (SwTableNode*)rBoxes[0]->GetSttNd()->FindTableNode();
//STRIP001  if( !pTblNd )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // suche alle Boxen / Lines
//STRIP001  _FndBox aFndBox( 0, 0 );
//STRIP001  {
//STRIP001      _FndPara aPara( rBoxes, &aFndBox );
//STRIP001      GetTabLines().ForEach( &_FndLineCopyCol, &aPara );
//STRIP001  }
//STRIP001  if( !aFndBox.GetLines().Count() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SetHTMLTableLayout( 0 );    // MIB 9.7.97: HTML-Layout loeschen
//STRIP001
//STRIP001  if( pUndo )
//STRIP001      pUndo->SetSelBoxes( rBoxes );
//STRIP001
//STRIP001  //Lines fuer das Layout-Update herausuchen.
//STRIP001  aFndBox.SetTableLines( *this );
//STRIP001  aFndBox.DelFrms( *this );
//STRIP001  aFndBox.SaveChartData( *this );
//STRIP001
//STRIP001  _FndBox* pFndBox = &aFndBox;
//STRIP001  while( 1 == pFndBox->GetLines().Count() &&
//STRIP001          1 == pFndBox->GetLines()[0]->GetBoxes().Count() )
//STRIP001      pFndBox = pFndBox->GetLines()[0]->GetBoxes()[0];
//STRIP001
//STRIP001  SwTableLine* pInsLine = new SwTableLine(
//STRIP001              (SwTableLineFmt*)pFndBox->GetLines()[0]->GetLine()->GetFrmFmt(), 0,
//STRIP001              !pFndBox->GetUpper() ? 0 : pFndBox->GetBox() );
//STRIP001  pInsLine->ClaimFrmFmt()->ResetAttr( RES_FRM_SIZE );
//STRIP001
//STRIP001  // trage die neue Line ein
//STRIP001  SwTableLines* pLines =  pFndBox->GetUpper() ?
//STRIP001                &pFndBox->GetBox()->GetTabLines() :  &GetTabLines();
//STRIP001
//STRIP001  SwTableLine* pNewLine = pFndBox->GetLines()[0]->GetLine();
//STRIP001  USHORT nInsPos = pLines->C40_GETPOS( SwTableLine, pNewLine );
//STRIP001  pLines->C40_INSERT( SwTableLine, pInsLine, nInsPos );
//STRIP001
//STRIP001  SwTableBox* pLeft = new SwTableBox( (SwTableBoxFmt*)pMergeBox->GetFrmFmt(), 0, pInsLine );
//STRIP001  SwTableBox* pRight = new SwTableBox( (SwTableBoxFmt*)pMergeBox->GetFrmFmt(), 0, pInsLine );
//STRIP001  pMergeBox->SetUpper( pInsLine );
//STRIP001  pInsLine->GetTabBoxes().C40_INSERT( SwTableBox, pLeft, 0 );
//STRIP001  pLeft->ClaimFrmFmt();
//STRIP001  pInsLine->GetTabBoxes().C40_INSERT( SwTableBox, pMergeBox, 1 );
//STRIP001  pInsLine->GetTabBoxes().C40_INSERT( SwTableBox, pRight, 2 );
//STRIP001  pRight->ClaimFrmFmt();
//STRIP001
//STRIP001  // in diese kommen alle Lines, die ueber dem selektierten Bereich stehen
//STRIP001  // Sie bilden also eine Upper/Lower Line
//STRIP001  _InsULPara aPara( pTblNd, TRUE, TRUE, pLeft, pMergeBox, pRight, pInsLine );
//STRIP001
//STRIP001  // move die oben/unten ueberhaengenden Lines vom selektierten Bereich
//STRIP001  pFndBox->GetLines()[0]->GetBoxes().ForEach( &lcl_Merge_MoveBox,
//STRIP001                                              &aPara );
//STRIP001  aPara.SetLower( pInsLine );
//STRIP001  USHORT nEnd = pFndBox->GetLines().Count()-1;
//STRIP001  pFndBox->GetLines()[nEnd]->GetBoxes().ForEach( &lcl_Merge_MoveBox,
//STRIP001                                                  &aPara );
//STRIP001
//STRIP001  // move die links/rechts hereinreichenden Boxen vom selektierten Bereich
//STRIP001  aPara.SetLeft( pLeft );
//STRIP001  pFndBox->GetLines().ForEach( &lcl_Merge_MoveLine, &aPara );
//STRIP001
//STRIP001  aPara.SetRight( pRight );
//STRIP001  pFndBox->GetLines().ForEach( &lcl_Merge_MoveLine, &aPara );
//STRIP001
//STRIP001  if( !pLeft->GetTabLines().Count() )
//STRIP001      _DeleteBox( *this, pLeft, 0, FALSE, FALSE );
//STRIP001  else
//STRIP001  {
//STRIP001      lcl_CalcWidth( pLeft );     // bereche die Breite der Box
//STRIP001      if( pUndo && pLeft->GetSttNd() )
//STRIP001          pUndo->AddNewBox( pLeft->GetSttIdx() );
//STRIP001  }
//STRIP001  if( !pRight->GetTabLines().Count() )
//STRIP001      _DeleteBox( *this, pRight, 0, FALSE, FALSE );
//STRIP001  else
//STRIP001  {
//STRIP001      lcl_CalcWidth( pRight );        // bereche die Breite der Box
//STRIP001      if( pUndo && pRight->GetSttNd() )
//STRIP001          pUndo->AddNewBox( pRight->GetSttIdx() );
//STRIP001  }
//STRIP001
//STRIP001  DeleteSel( pDoc, rBoxes, 0, FALSE, FALSE );
//STRIP001
//STRIP001  // dann raeume die Struktur dieser Line noch mal auf:
//STRIP001  // generell alle Aufraeumen
//STRIP001  GCLines();
//STRIP001
//STRIP001  GetTabLines()[0]->GetTabBoxes().ForEach( &lcl_BoxSetHeadCondColl, 0 );
//STRIP001
//STRIP001  aFndBox.MakeFrms( *this );
//STRIP001  aFndBox.RestoreChartData( *this );
//STRIP001  CHECKBOXWIDTH
//STRIP001     CHECKTABLELAYOUT
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }

// ---------------------------------------------------------------

//STRIP001 USHORT lcl_GetBoxOffset( const _FndBox& rBox )
//STRIP001 {
//STRIP001  // suche die erste Box
//STRIP001  const _FndBox* pFirstBox = &rBox;
//STRIP001  while( pFirstBox->GetLines().Count() )
//STRIP001      pFirstBox = pFirstBox->GetLines()[ 0 ]->GetBoxes()[ 0 ];
//STRIP001
//STRIP001  USHORT nRet = 0;
//STRIP001  // dann ueber die Lines nach oben die Position bestimmen
//STRIP001  const SwTableBox* pBox = pFirstBox->GetBox();
//STRIP001  do {
//STRIP001      const SwTableBoxes& rBoxes = pBox->GetUpper()->GetTabBoxes();
//STRIP001      const SwTableBox* pCmp;
//STRIP001      for( USHORT n = 0; pBox != ( pCmp = rBoxes[ n ] ); ++n )
//STRIP001          nRet += (USHORT) pCmp->GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001      pBox = pBox->GetUpper()->GetUpper();
//STRIP001  } while( pBox );
//STRIP001  return nRet;
//STRIP001 }

//STRIP001 USHORT lcl_GetLineWidth( const _FndLine& rLine )
//STRIP001 {
//STRIP001  USHORT nRet = 0;
//STRIP001  for( USHORT n = rLine.GetBoxes().Count(); n; )
//STRIP001      nRet += (USHORT)rLine.GetBoxes()[ --n ]->GetBox()->GetFrmFmt()
//STRIP001                      ->GetFrmSize().GetWidth();
//STRIP001  return nRet;
//STRIP001 }

//STRIP001 BOOL lcl_CopyBoxToDoc( const _FndBox*& rpFndBox, void* pPara )
//STRIP001 {
//STRIP001  _CpyPara* pCpyPara = (_CpyPara*)pPara;
//STRIP001
//STRIP001  // Berechne die neue Size
//STRIP001  ULONG nSize = pCpyPara->nNewSize;
//STRIP001  nSize *= rpFndBox->GetBox()->GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001  nSize /= pCpyPara->nOldSize;
//STRIP001
//STRIP001  // suche das Frame-Format in der Liste aller Frame-Formate
//STRIP001  _CpyTabFrm aFindFrm( (SwTableBoxFmt*)rpFndBox->GetBox()->GetFrmFmt() );
//STRIP001
//STRIP001  SwFmtFrmSize aFrmSz;
//STRIP001  USHORT nFndPos;
//STRIP001  if( !pCpyPara->rTabFrmArr.Seek_Entry( aFindFrm, &nFndPos ) ||
//STRIP001      ( aFrmSz = ( aFindFrm = pCpyPara->rTabFrmArr[ nFndPos ]).pNewFrmFmt->
//STRIP001          GetFrmSize()).GetWidth() != (SwTwips)nSize )
//STRIP001  {
//STRIP001      // es ist noch nicht vorhanden, also kopiere es
//STRIP001      aFindFrm.pNewFrmFmt = pCpyPara->pDoc->MakeTableBoxFmt();
//STRIP001      aFindFrm.pNewFrmFmt->CopyAttrs( *rpFndBox->GetBox()->GetFrmFmt() );
//STRIP001      if( !pCpyPara->bCpyCntnt )
//STRIP001          aFindFrm.pNewFrmFmt->ResetAttr(  RES_BOXATR_FORMULA, RES_BOXATR_VALUE );
//STRIP001      aFrmSz.SetWidth( nSize );
//STRIP001      aFindFrm.pNewFrmFmt->SetAttr( aFrmSz );
//STRIP001      pCpyPara->rTabFrmArr.Insert( aFindFrm );
//STRIP001  }
//STRIP001
//STRIP001  SwTableBox* pBox;
//STRIP001  if( rpFndBox->GetLines().Count() )
//STRIP001  {
//STRIP001      pBox = new SwTableBox( aFindFrm.pNewFrmFmt,
//STRIP001                  rpFndBox->GetLines().Count(), pCpyPara->pInsLine );
//STRIP001      pCpyPara->pInsLine->GetTabBoxes().C40_INSERT( SwTableBox, pBox, pCpyPara->nInsPos++ );
//STRIP001      _CpyPara aPara( *pCpyPara, pBox );
//STRIP001      aPara.nNewSize = nSize;     // hole die Groesse
//STRIP001      ((_FndBox*)rpFndBox)->GetLines().ForEach( &lcl_CopyLineToDoc, &aPara );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // erzeuge eine leere Box
//STRIP001      pCpyPara->pDoc->GetNodes().InsBoxen( pCpyPara->pTblNd, pCpyPara->pInsLine,
//STRIP001                      aFindFrm.pNewFrmFmt,
//STRIP001                      (SwTxtFmtColl*)pCpyPara->pDoc->GetDfltTxtFmtColl(),
//STRIP001                      0, pCpyPara->nInsPos );
//STRIP001
//STRIP001      if( pCpyPara->bCpyCntnt )
//STRIP001      {
//STRIP001          // dann kopiere mal den Inhalt in diese leere Box
//STRIP001          pBox = pCpyPara->pInsLine->GetTabBoxes()[ pCpyPara->nInsPos ];
//STRIP001
//STRIP001          // der Inhalt kopiert wird, dann koennen auch Formeln&Values
//STRIP001          // kopiert werden.
//STRIP001          {
//STRIP001              SfxItemSet aBoxAttrSet( pCpyPara->pDoc->GetAttrPool(),
//STRIP001                                      RES_BOXATR_FORMAT, RES_BOXATR_VALUE );
//STRIP001              aBoxAttrSet.Put( rpFndBox->GetBox()->GetFrmFmt()->GetAttrSet() );
//STRIP001              if( aBoxAttrSet.Count() )
//STRIP001              {
//STRIP001                  const SfxPoolItem* pItem;
//STRIP001                  SvNumberFormatter* pN = pCpyPara->pDoc->GetNumberFormatter( FALSE );
//STRIP001                  if( pN && pN->HasMergeFmtTbl() && SFX_ITEM_SET == aBoxAttrSet.
//STRIP001                      GetItemState( RES_BOXATR_FORMAT, FALSE, &pItem ) )
//STRIP001                  {
//STRIP001                      ULONG nOldIdx = ((SwTblBoxNumFormat*)pItem)->GetValue();
//STRIP001                      ULONG nNewIdx = pN->GetMergeFmtIndex( nOldIdx );
//STRIP001                      if( nNewIdx != nOldIdx )
//STRIP001                          aBoxAttrSet.Put( SwTblBoxNumFormat( nNewIdx ));
//STRIP001                  }
//STRIP001                  pBox->ClaimFrmFmt()->SetAttr( aBoxAttrSet );
//STRIP001              }
//STRIP001          }
//STRIP001          SwDoc* pFromDoc = rpFndBox->GetBox()->GetFrmFmt()->GetDoc();
//STRIP001          SwNodeRange aCpyRg( *rpFndBox->GetBox()->GetSttNd(), 1,
//STRIP001                      *rpFndBox->GetBox()->GetSttNd()->EndOfSectionNode() );
//STRIP001          SwNodeIndex aInsIdx( *pBox->GetSttNd(), 1 );
//STRIP001
//STRIP001          pFromDoc->CopyWithFlyInFly( aCpyRg, aInsIdx, FALSE );
//STRIP001          // den initialen TextNode loeschen
//STRIP001          pCpyPara->pDoc->GetNodes().Delete( aInsIdx, 1 );
//STRIP001      }
//STRIP001      ++pCpyPara->nInsPos;
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL lcl_CopyLineToDoc( const _FndLine*& rpFndLine, void* pPara )
//STRIP001 {
//STRIP001  _CpyPara* pCpyPara = (_CpyPara*)pPara;
//STRIP001
//STRIP001  // suche das Format in der Liste aller Formate
//STRIP001  _CpyTabFrm aFindFrm( (SwTableBoxFmt*)rpFndLine->GetLine()->GetFrmFmt() );
//STRIP001  USHORT nFndPos;
//STRIP001  if( !pCpyPara->rTabFrmArr.Seek_Entry( aFindFrm, &nFndPos ))
//STRIP001  {
//STRIP001      // es ist noch nicht vorhanden, also kopiere es
//STRIP001      aFindFrm.pNewFrmFmt = (SwTableBoxFmt*)pCpyPara->pDoc->MakeTableLineFmt();
//STRIP001      aFindFrm.pNewFrmFmt->CopyAttrs( *rpFndLine->GetLine()->GetFrmFmt() );
//STRIP001      pCpyPara->rTabFrmArr.Insert( aFindFrm );
//STRIP001  }
//STRIP001  else
//STRIP001      aFindFrm = pCpyPara->rTabFrmArr[ nFndPos ];
//STRIP001
//STRIP001  SwTableLine* pNewLine = new SwTableLine( (SwTableLineFmt*)aFindFrm.pNewFrmFmt,
//STRIP001                      rpFndLine->GetBoxes().Count(), pCpyPara->pInsBox );
//STRIP001  if( pCpyPara->pInsBox )
//STRIP001  {
//STRIP001      pCpyPara->pInsBox->GetTabLines().C40_INSERT( SwTableLine, pNewLine, pCpyPara->nInsPos++ );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pCpyPara->pTblNd->GetTable().GetTabLines().C40_INSERT( SwTableLine, pNewLine,
//STRIP001                          pCpyPara->nInsPos++ );
//STRIP001  }
//STRIP001
//STRIP001  _CpyPara aPara( *pCpyPara, pNewLine );
//STRIP001
//STRIP001  // berechne die neue Size der Boxen einer Line
//STRIP001  if( rpFndLine->GetBoxes().Count() ==
//STRIP001                  rpFndLine->GetLine()->GetTabBoxes().Count() )
//STRIP001  {
//STRIP001      // hole die Size vom Parent
//STRIP001      const SwFrmFmt* pFmt;
//STRIP001
//STRIP001      if( rpFndLine->GetLine()->GetUpper() )
//STRIP001          pFmt = rpFndLine->GetLine()->GetUpper()->GetFrmFmt();
//STRIP001      else
//STRIP001          pFmt = pCpyPara->pTblNd->GetTable().GetFrmFmt();
//STRIP001      aPara.nOldSize = pFmt->GetFrmSize().GetWidth();
//STRIP001  }
//STRIP001  else
//STRIP001      // errechne sie
//STRIP001      for( USHORT n = 0; n < rpFndLine->GetBoxes().Count(); ++n )
//STRIP001          aPara.nOldSize += rpFndLine->GetBoxes()[n]
//STRIP001                      ->GetBox()->GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001
//STRIP001  ((_FndLine*)rpFndLine)->GetBoxes().ForEach( &lcl_CopyBoxToDoc, &aPara );
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL SwTable::CopyHeadlineIntoTable( SwTableNode& rTblNd )
//STRIP001 {
//STRIP001  // suche alle Boxen / Lines
//STRIP001  SwSelBoxes aSelBoxes;
//STRIP001  SwTableBox* pBox = GetTabSortBoxes()[ 0 ];
//STRIP001  pBox = GetTblBox( pBox->GetSttNd()->FindStartNode()->GetIndex() + 1 );
//STRIP001  SelLineFromBox( pBox, aSelBoxes, TRUE );
//STRIP001
//STRIP001  _FndBox aFndBox( 0, 0 );
//STRIP001  {
//STRIP001      _FndPara aPara( aSelBoxes, &aFndBox );
//STRIP001      ((SwTableLines&)GetTabLines()).ForEach( &_FndLineCopyCol, &aPara );
//STRIP001  }
//STRIP001  if( !aFndBox.GetLines().Count() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  {
//STRIP001      // Tabellen-Formeln in die relative Darstellung umwandeln
//STRIP001      SwTableFmlUpdate aMsgHnt( this );
//STRIP001      aMsgHnt.eFlags = TBL_RELBOXNAME;
//STRIP001      GetFrmFmt()->GetDoc()->UpdateTblFlds( &aMsgHnt );
//STRIP001  }
//STRIP001
//STRIP001  _CpyTabFrms aCpyFmt;
//STRIP001  _CpyPara aPara( &rTblNd, 1, aCpyFmt, TRUE );
//STRIP001  aPara.nNewSize = aPara.nOldSize = rTblNd.GetTable().GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001  // dann kopiere mal
//STRIP001  aFndBox.GetLines().ForEach( &lcl_CopyLineToDoc, &aPara );
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL SwTable::MakeCopy( SwDoc* pInsDoc, const SwPosition& rPos,
//STRIP001                      const SwSelBoxes& rSelBoxes, BOOL bCpyNds,
//STRIP001                      BOOL bCpyName ) const
//STRIP001 {
//STRIP001  // suche alle Boxen / Lines
//STRIP001  _FndBox aFndBox( 0, 0 );
//STRIP001  {
//STRIP001      _FndPara aPara( rSelBoxes, &aFndBox );
//STRIP001      ((SwTableLines&)GetTabLines()).ForEach( &_FndLineCopyCol, &aPara );
//STRIP001  }
//STRIP001  if( !aFndBox.GetLines().Count() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  // erst die Poolvorlagen fuer die Tabelle kopieren, damit die dann
//STRIP001  // wirklich kopiert und damit die gueltigen Werte haben.
//STRIP001  SwDoc* pSrcDoc = GetFrmFmt()->GetDoc();
//STRIP001  if( pSrcDoc != pInsDoc )
//STRIP001  {
//STRIP001      pInsDoc->CopyTxtColl( *pSrcDoc->GetTxtCollFromPool( RES_POOLCOLL_TABLE ) );
//STRIP001      pInsDoc->CopyTxtColl( *pSrcDoc->GetTxtCollFromPool( RES_POOLCOLL_TABLE_HDLN ) );
//STRIP001  }
//STRIP001
//STRIP001  SwTable* pNewTbl = (SwTable*)pInsDoc->InsertTable( rPos, 1, 1,
//STRIP001                  GetFrmFmt()->GetHoriOrient().GetHoriOrient() );
//STRIP001  if( !pNewTbl )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SwNodeIndex aIdx( rPos.nNode, -1 );
//STRIP001  SwTableNode* pTblNd = aIdx.GetNode().FindTableNode();
//STRIP001  aIdx++;
//STRIP001  ASSERT( pTblNd, "wo ist denn nun der TableNode?" );
//STRIP001
//STRIP001  pTblNd->GetTable().SetHeadlineRepeat( IsHeadlineRepeat() );
//STRIP001
//STRIP001  if( IS_TYPE( SwDDETable, this ))
//STRIP001  {
//STRIP001      // es wird eine DDE-Tabelle kopiert
//STRIP001      // ist im neuen Dokument ueberhaupt der FeldTyp vorhanden ?
//STRIP001      SwFieldType* pFldType = pInsDoc->InsertFldType(
//STRIP001                                  *((SwDDETable*)this)->GetDDEFldType() );
//STRIP001      ASSERT( pFldType, "unbekannter FieldType" );
//STRIP001
//STRIP001      // tauschen am Node den Tabellen-Pointer aus
//STRIP001      pNewTbl = new SwDDETable( *pNewTbl,
//STRIP001                               (SwDDEFieldType*)pFldType );
//STRIP001      pTblNd->SetNewTable( pNewTbl, FALSE );
//STRIP001  }
//STRIP001
//STRIP001  pNewTbl->GetFrmFmt()->CopyAttrs( *GetFrmFmt() );
//STRIP001  pNewTbl->SetTblChgMode( GetTblChgMode() );
//STRIP001
//STRIP001  //Vernichten der Frms die bereits angelegt wurden.
//STRIP001  pTblNd->DelFrms();
//STRIP001
//STRIP001  {
//STRIP001      // Tabellen-Formeln in die relative Darstellung umwandeln
//STRIP001      SwTableFmlUpdate aMsgHnt( this );
//STRIP001      aMsgHnt.eFlags = TBL_RELBOXNAME;
//STRIP001      pSrcDoc->UpdateTblFlds( &aMsgHnt );
//STRIP001  }
//STRIP001
//STRIP001  SwTblNumFmtMerge aTNFM( *pSrcDoc, *pInsDoc );
//STRIP001
//STRIP001  // Namen auch kopieren oder neuen eindeutigen erzeugen
//STRIP001  if( bCpyName )
//STRIP001      pNewTbl->GetFrmFmt()->SetName( GetFrmFmt()->GetName() );
//STRIP001
//STRIP001  _CpyTabFrms aCpyFmt;
//STRIP001  _CpyPara aPara( pTblNd, 1, aCpyFmt, bCpyNds );
//STRIP001  aPara.nNewSize = aPara.nOldSize = GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001  // dann kopiere mal
//STRIP001  aFndBox.GetLines().ForEach( &lcl_CopyLineToDoc, &aPara );
//STRIP001
//STRIP001  // dann setze oben und unten noch die "richtigen" Raender:
//STRIP001  {
//STRIP001      _FndLine* pFndLn = aFndBox.GetLines()[ 0 ];
//STRIP001      SwTableLine* pLn = pFndLn->GetLine();
//STRIP001      const SwTableLine* pTmp = pLn;
//STRIP001      USHORT nLnPos = GetTabLines().GetPos( pTmp );
//STRIP001      if( USHRT_MAX != nLnPos && nLnPos )
//STRIP001      {
//STRIP001          // es gibt eine Line davor
//STRIP001          SwCollectTblLineBoxes aLnPara( FALSE, HEADLINE_BORDERCOPY );
//STRIP001
//STRIP001          pLn = GetTabLines()[ nLnPos - 1 ];
//STRIP001          pLn->GetTabBoxes().ForEach( &lcl_Box_CollectBox, &aLnPara );
//STRIP001
//STRIP001          if( aLnPara.Resize( lcl_GetBoxOffset( aFndBox ),
//STRIP001                              lcl_GetLineWidth( *pFndLn )) )
//STRIP001          {
//STRIP001              aLnPara.SetValues( TRUE );
//STRIP001              pLn = pNewTbl->GetTabLines()[ 0 ];
//STRIP001              pLn->GetTabBoxes().ForEach( &lcl_BoxSetSplitBoxFmts, &aLnPara );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      pFndLn = aFndBox.GetLines()[ aFndBox.GetLines().Count() -1 ];
//STRIP001      pLn = pFndLn->GetLine();
//STRIP001      pTmp = pLn;
//STRIP001      nLnPos = GetTabLines().GetPos( pTmp );
//STRIP001      if( nLnPos < GetTabLines().Count() - 1 )
//STRIP001      {
//STRIP001          // es gibt eine Line dahinter
//STRIP001          SwCollectTblLineBoxes aLnPara( TRUE, HEADLINE_BORDERCOPY );
//STRIP001
//STRIP001          pLn = GetTabLines()[ nLnPos + 1 ];
//STRIP001          pLn->GetTabBoxes().ForEach( &lcl_Box_CollectBox, &aLnPara );
//STRIP001
//STRIP001          if( aLnPara.Resize( lcl_GetBoxOffset( aFndBox ),
//STRIP001                              lcl_GetLineWidth( *pFndLn )) )
//STRIP001          {
//STRIP001              aLnPara.SetValues( FALSE );
//STRIP001              pLn = pNewTbl->GetTabLines()[ pNewTbl->GetTabLines().Count()-1 ];
//STRIP001              pLn->GetTabBoxes().ForEach( &lcl_BoxSetSplitBoxFmts, &aLnPara );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // die initiale Box muss noch geloescht werden
//STRIP001  _DeleteBox( *pNewTbl, pNewTbl->GetTabLines()[
//STRIP001              pNewTbl->GetTabLines().Count() - 1 ]->GetTabBoxes()[0],
//STRIP001              0, FALSE, FALSE );
//STRIP001
//STRIP001  // Mal kurz aufraeumen:
//STRIP001  pNewTbl->GCLines();
//STRIP001
//STRIP001  pTblNd->MakeFrms( &aIdx );  // erzeuge die Frames neu
//STRIP001
//STRIP001     CHECKTABLELAYOUT
//STRIP001
//STRIP001  return TRUE;
//STRIP001 }



// ---------------------------------------------------------------

// suche ab dieser Line nach der naechsten Box mit Inhalt
//STRIP001 SwTableBox* SwTableLine::FindNextBox( const SwTable& rTbl,
//STRIP001                   const SwTableBox* pSrchBox, BOOL bOvrTblLns ) const
//STRIP001 {
//STRIP001  const SwTableLine* pLine = this;            // fuer M800
//STRIP001  SwTableBox* pBox;
//STRIP001  USHORT nFndPos;
//STRIP001  if( GetTabBoxes().Count() && pSrchBox &&
//STRIP001      USHRT_MAX != ( nFndPos = GetTabBoxes().GetPos( pSrchBox )) &&
//STRIP001      nFndPos + 1 != GetTabBoxes().Count() )
//STRIP001  {
//STRIP001      pBox = GetTabBoxes()[ nFndPos + 1 ];
//STRIP001      while( pBox->GetTabLines().Count() )
//STRIP001          pBox = pBox->GetTabLines()[0]->GetTabBoxes()[0];
//STRIP001      return pBox;
//STRIP001  }
//STRIP001
//STRIP001  if( GetUpper() )
//STRIP001  {
//STRIP001      nFndPos = GetUpper()->GetTabLines().GetPos( pLine );
//STRIP001      ASSERT( USHRT_MAX != nFndPos, "Line nicht in der Tabelle" );
//STRIP001      // gibts eine weitere Line
//STRIP001      if( nFndPos+1 >= GetUpper()->GetTabLines().Count() )
//STRIP001          return GetUpper()->GetUpper()->FindNextBox( rTbl, GetUpper(), bOvrTblLns );
//STRIP001      pLine = GetUpper()->GetTabLines()[nFndPos+1];
//STRIP001  }
//STRIP001  else if( bOvrTblLns )       // ueber die "GrundLines" einer Tabelle ?
//STRIP001  {
//STRIP001      // suche in der Tabelle nach der naechsten Line
//STRIP001      nFndPos = rTbl.GetTabLines().GetPos( pLine );
//STRIP001      if( nFndPos + 1 >= rTbl.GetTabLines().Count() )
//STRIP001          return 0;           // es gibt keine weitere Box mehr
//STRIP001
//STRIP001      pLine = rTbl.GetTabLines()[ nFndPos+1 ];
//STRIP001  }
//STRIP001  else
//STRIP001      return 0;
//STRIP001
//STRIP001  if( pLine->GetTabBoxes().Count() )
//STRIP001  {
//STRIP001      pBox = pLine->GetTabBoxes()[0];
//STRIP001      while( pBox->GetTabLines().Count() )
//STRIP001          pBox = pBox->GetTabLines()[0]->GetTabBoxes()[0];
//STRIP001      return pBox;
//STRIP001  }
//STRIP001  return pLine->FindNextBox( rTbl, 0, bOvrTblLns );
//STRIP001 }

// suche ab dieser Line nach der vorherigen Box
//STRIP001 SwTableBox* SwTableLine::FindPreviousBox( const SwTable& rTbl,
//STRIP001                       const SwTableBox* pSrchBox, BOOL bOvrTblLns ) const
//STRIP001 {
//STRIP001  const SwTableLine* pLine = this;            // fuer M800
//STRIP001  SwTableBox* pBox;
//STRIP001  USHORT nFndPos;
//STRIP001  if( GetTabBoxes().Count() && pSrchBox &&
//STRIP001      USHRT_MAX != ( nFndPos = GetTabBoxes().GetPos( pSrchBox )) &&
//STRIP001      nFndPos )
//STRIP001  {
//STRIP001      pBox = GetTabBoxes()[ nFndPos - 1 ];
//STRIP001      while( pBox->GetTabLines().Count() )
//STRIP001      {
//STRIP001          pLine = pBox->GetTabLines()[pBox->GetTabLines().Count()-1];
//STRIP001          pBox = pLine->GetTabBoxes()[pLine->GetTabBoxes().Count()-1];
//STRIP001      }
//STRIP001      return pBox;
//STRIP001  }
//STRIP001
//STRIP001  if( GetUpper() )
//STRIP001  {
//STRIP001      nFndPos = GetUpper()->GetTabLines().GetPos( pLine );
//STRIP001      ASSERT( USHRT_MAX != nFndPos, "Line nicht in der Tabelle" );
//STRIP001      // gibts eine weitere Line
//STRIP001      if( !nFndPos )
//STRIP001          return GetUpper()->GetUpper()->FindPreviousBox( rTbl, GetUpper(), bOvrTblLns );
//STRIP001      pLine = GetUpper()->GetTabLines()[nFndPos-1];
//STRIP001  }
//STRIP001  else if( bOvrTblLns )       // ueber die "GrundLines" einer Tabelle ?
//STRIP001  {
//STRIP001      // suche in der Tabelle nach der naechsten Line
//STRIP001      nFndPos = rTbl.GetTabLines().GetPos( pLine );
//STRIP001      if( !nFndPos )
//STRIP001          return 0;           // es gibt keine weitere Box mehr
//STRIP001
//STRIP001      pLine = rTbl.GetTabLines()[ nFndPos-1 ];
//STRIP001  }
//STRIP001  else
//STRIP001      return 0;
//STRIP001
//STRIP001  if( pLine->GetTabBoxes().Count() )
//STRIP001  {
//STRIP001      pBox = pLine->GetTabBoxes()[pLine->GetTabBoxes().Count()-1];
//STRIP001      while( pBox->GetTabLines().Count() )
//STRIP001      {
//STRIP001          pLine = pBox->GetTabLines()[pBox->GetTabLines().Count()-1];
//STRIP001          pBox = pLine->GetTabBoxes()[pLine->GetTabBoxes().Count()-1];
//STRIP001      }
//STRIP001      return pBox;
//STRIP001  }
//STRIP001  return pLine->FindPreviousBox( rTbl, 0, bOvrTblLns );
//STRIP001 }

// suche ab dieser Line nach der naechsten Box mit Inhalt
//STRIP001 SwTableBox* SwTableBox::FindNextBox( const SwTable& rTbl,
//STRIP001                       const SwTableBox* pSrchBox, BOOL bOvrTblLns ) const
//STRIP001 {
//STRIP001  if( !pSrchBox  && !GetTabLines().Count() )
//STRIP001      return (SwTableBox*)this;
//STRIP001  return GetUpper()->FindNextBox( rTbl, pSrchBox ? pSrchBox : this,
//STRIP001                                      bOvrTblLns );
//STRIP001
//STRIP001 }

// suche ab dieser Line nach der naechsten Box mit Inhalt
//STRIP001 SwTableBox* SwTableBox::FindPreviousBox( const SwTable& rTbl,
//STRIP001                       const SwTableBox* pSrchBox, BOOL bOvrTblLns ) const
//STRIP001 {
//STRIP001  if( !pSrchBox && !GetTabLines().Count() )
//STRIP001      return (SwTableBox*)this;
//STRIP001  return GetUpper()->FindPreviousBox( rTbl, pSrchBox ? pSrchBox : this,
//STRIP001                                      bOvrTblLns );
//STRIP001 }


//STRIP001 BOOL lcl_BoxSetHeadCondColl( const SwTableBox*& rpBox, void* pPara )
//STRIP001 {
//STRIP001  // in der HeadLine sind die Absaetze mit BedingtenVorlage anzupassen
//STRIP001  const SwStartNode* pSttNd = rpBox->GetSttNd();
//STRIP001  if( pSttNd )
//STRIP001      pSttNd->CheckSectionCondColl();
//STRIP001  else
//STRIP001      ((SwTableBox*)rpBox)->GetTabLines().ForEach( &lcl_LineSetHeadCondColl, 0 );
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL lcl_LineSetHeadCondColl( const SwTableLine*& rpLine, void* pPara )
//STRIP001 {
//STRIP001  ((SwTableLine*)rpLine)->GetTabBoxes().ForEach( &lcl_BoxSetHeadCondColl, 0 );
//STRIP001  return TRUE;
//STRIP001 }

/*  */

#pragma optimize( "", off )

//STRIP001 SwTwips lcl_GetDistance( SwTableBox* pBox, BOOL bLeft )
//STRIP001 {
//STRIP001  BOOL bFirst = TRUE;
//STRIP001  SwTwips nRet = 0;
//STRIP001  SwTableLine* pLine;
//STRIP001  while( pBox && 0 != ( pLine = pBox->GetUpper() ) )
//STRIP001  {
//STRIP001      USHORT nStt = 0, nPos = pLine->GetTabBoxes().C40_GETPOS( SwTableBox, pBox );
//STRIP001
//STRIP001      if( bFirst && !bLeft )
//STRIP001          ++nPos;
//STRIP001      bFirst = FALSE;
//STRIP001
//STRIP001      while( nStt < nPos )
//STRIP001          nRet += pLine->GetTabBoxes()[ nStt++ ]->GetFrmFmt()
//STRIP001                          ->GetFrmSize().GetWidth();
//STRIP001      pBox = pLine->GetUpper();
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

//#pragma optimize( "", on )

//STRIP001 BOOL lcl_SetSelBoxWidth( SwTableLine* pLine, CR_SetBoxWidth& rParam,
//STRIP001                       SwTwips nDist, BOOL bCheck )
//STRIP001 {
//STRIP001  SwTableBoxes& rBoxes = pLine->GetTabBoxes();
//STRIP001  for( USHORT n = 0; n < rBoxes.Count(); ++n )
//STRIP001  {
//STRIP001      SwTableBox* pBox = rBoxes[ n ];
//STRIP001      SwFrmFmt* pFmt = pBox->GetFrmFmt();
//STRIP001      const SwFmtFrmSize& rSz = pFmt->GetFrmSize();
//STRIP001      SwTwips nWidth = rSz.GetWidth();
//STRIP001      BOOL bGreaterBox;
//STRIP001
//STRIP001      if( bCheck )
//STRIP001      {
//STRIP001          for( USHORT i = 0; i < pBox->GetTabLines().Count(); ++i )
//STRIP001              if( !::lcl_SetSelBoxWidth( pBox->GetTabLines()[ i ], rParam,
//STRIP001                                          nDist, TRUE ))
//STRIP001                  return FALSE;
//STRIP001
//STRIP001
//STRIP001          // dann noch mal alle "ContentBoxen" sammeln
//STRIP001          if( !rParam.bBigger &&
//STRIP001              ( Abs( nDist + (( rParam.nMode && rParam.bLeft ) ? 0 : nWidth )
//STRIP001                  - rParam.nSide ) < COLFUZZY ) ||
//STRIP001               ( 0 != ( bGreaterBox = TBLFIX_CHGABS != rParam.nMode &&
//STRIP001                  ( nDist + ( rParam.bLeft ? 0 : nWidth ) ) >= rParam.nSide)) )
//STRIP001          {
//STRIP001              rParam.bAnyBoxFnd = TRUE;
//STRIP001              SwTwips nLowerDiff;
//STRIP001              if( bGreaterBox && TBLFIX_CHGPROP == rParam.nMode )
//STRIP001              {
//STRIP001                  // die "anderen Boxen" wurden angepasst,
//STRIP001                  // also sich um diesen Betrag aendern
//STRIP001                  nLowerDiff = (nDist + ( rParam.bLeft ? 0 : nWidth ) ) - rParam.nSide;
//STRIP001                  nLowerDiff *= rParam.nDiff;
//STRIP001                  nLowerDiff /= rParam.nMaxSize;
//STRIP001                  nLowerDiff = rParam.nDiff - nLowerDiff;
//STRIP001              }
//STRIP001              else
//STRIP001                  nLowerDiff = rParam.nDiff;
//STRIP001
//STRIP001              if( nWidth < nLowerDiff || nWidth - nLowerDiff < MINLAY )
//STRIP001                  return FALSE;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          SwTwips nLowerDiff = 0, nOldLower = rParam.nLowerDiff;
//STRIP001          for( USHORT i = 0; i < pBox->GetTabLines().Count(); ++i )
//STRIP001          {
//STRIP001              rParam.nLowerDiff = 0;
//STRIP001              lcl_SetSelBoxWidth( pBox->GetTabLines()[ i ], rParam, nDist, FALSE );
//STRIP001
//STRIP001              if( nLowerDiff < rParam.nLowerDiff )
//STRIP001                  nLowerDiff = rParam.nLowerDiff;
//STRIP001          }
//STRIP001          rParam.nLowerDiff = nOldLower;
//STRIP001
//STRIP001
//STRIP001          if( nLowerDiff ||
//STRIP001              ( Abs( nDist + ( (rParam.nMode && rParam.bLeft) ? 0 : nWidth )
//STRIP001                          - rParam.nSide ) < COLFUZZY ) ||
//STRIP001               ( 0 != ( bGreaterBox = !nOldLower && TBLFIX_CHGABS != rParam.nMode &&
//STRIP001                  ( nDist + ( rParam.bLeft ? 0 : nWidth ) ) >= rParam.nSide)) )
//STRIP001          {
//STRIP001              // in dieser Spalte ist der Cursor - also verkleinern / vergroessern
//STRIP001              SwFmtFrmSize aNew( rSz );
//STRIP001
//STRIP001              if( !nLowerDiff )
//STRIP001              {
//STRIP001                  if( bGreaterBox && TBLFIX_CHGPROP == rParam.nMode )
//STRIP001                  {
//STRIP001                      // die "anderen Boxen" wurden angepasst,
//STRIP001                      // also sich um diesen Betrag aendern
//STRIP001                      nLowerDiff = (nDist + ( rParam.bLeft ? 0 : nWidth ) ) - rParam.nSide;
//STRIP001                      nLowerDiff *= rParam.nDiff;
//STRIP001                      nLowerDiff /= rParam.nMaxSize;
//STRIP001                      nLowerDiff = rParam.nDiff - nLowerDiff;
//STRIP001                  }
//STRIP001                  else
//STRIP001                      nLowerDiff = rParam.nDiff;
//STRIP001              }
//STRIP001
//STRIP001              rParam.nLowerDiff += nLowerDiff;
//STRIP001
//STRIP001              if( rParam.bBigger )
//STRIP001                  aNew.SetWidth( nWidth + nLowerDiff );
//STRIP001              else
//STRIP001                  aNew.SetWidth( nWidth - nLowerDiff );
//STRIP001              rParam.aShareFmts.SetSize( *pBox, aNew );
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if( rParam.bLeft && rParam.nMode && nDist >= rParam.nSide )
//STRIP001          break;
//STRIP001
//STRIP001      nDist += nWidth;
//STRIP001
//STRIP001      // wenns groesser wird, dann wars das
//STRIP001      if( ( TBLFIX_CHGABS == rParam.nMode || !rParam.bLeft ) &&
//STRIP001              nDist >= rParam.nSide )
//STRIP001          break;
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL lcl_SetOtherBoxWidth( SwTableLine* pLine, CR_SetBoxWidth& rParam,
//STRIP001                              SwTwips nDist, BOOL bCheck )
//STRIP001 {
//STRIP001  SwTableBoxes& rBoxes = pLine->GetTabBoxes();
//STRIP001  for( USHORT n = 0; n < rBoxes.Count(); ++n )
//STRIP001  {
//STRIP001      SwTableBox* pBox = rBoxes[ n ];
//STRIP001      SwFrmFmt* pFmt = pBox->GetFrmFmt();
//STRIP001      const SwFmtFrmSize& rSz = pFmt->GetFrmSize();
//STRIP001      SwTwips nWidth = rSz.GetWidth();
//STRIP001
//STRIP001      if( bCheck )
//STRIP001      {
//STRIP001          for( USHORT i = 0; i < pBox->GetTabLines().Count(); ++i )
//STRIP001              if( !::lcl_SetOtherBoxWidth( pBox->GetTabLines()[ i ],
//STRIP001                                                  rParam, nDist, TRUE ))
//STRIP001                  return FALSE;
//STRIP001
//STRIP001          if( rParam.bBigger && ( TBLFIX_CHGABS == rParam.nMode
//STRIP001                  ? Abs( nDist - rParam.nSide ) < COLFUZZY
//STRIP001                  : ( rParam.bLeft ? nDist < rParam.nSide - COLFUZZY
//STRIP001                                   : nDist >= rParam.nSide - COLFUZZY )) )
//STRIP001          {
//STRIP001              rParam.bAnyBoxFnd = TRUE;
//STRIP001              SwTwips nDiff;
//STRIP001              if( TBLFIX_CHGPROP == rParam.nMode )        // Tabelle fix, proport.
//STRIP001              {
//STRIP001                  // relativ berechnen
//STRIP001                  nDiff = nWidth;
//STRIP001                  nDiff *= rParam.nDiff;
//STRIP001                  nDiff /= rParam.nMaxSize;
//STRIP001              }
//STRIP001              else
//STRIP001                  nDiff = rParam.nDiff;
//STRIP001
//STRIP001              if( nWidth < nDiff || nWidth - nDiff < MINLAY )
//STRIP001                  return FALSE;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          SwTwips nLowerDiff = 0, nOldLower = rParam.nLowerDiff;
//STRIP001          for( USHORT i = 0; i < pBox->GetTabLines().Count(); ++i )
//STRIP001          {
//STRIP001              rParam.nLowerDiff = 0;
//STRIP001              lcl_SetOtherBoxWidth( pBox->GetTabLines()[ i ], rParam,
//STRIP001                                          nDist, FALSE );
//STRIP001
//STRIP001              if( nLowerDiff < rParam.nLowerDiff )
//STRIP001                  nLowerDiff = rParam.nLowerDiff;
//STRIP001          }
//STRIP001          rParam.nLowerDiff = nOldLower;
//STRIP001
//STRIP001          if( nLowerDiff ||
//STRIP001              ( TBLFIX_CHGABS == rParam.nMode
//STRIP001                      ? Abs( nDist - rParam.nSide ) < COLFUZZY
//STRIP001                      : ( rParam.bLeft ? nDist < rParam.nSide - COLFUZZY
//STRIP001                                       : nDist >= rParam.nSide - COLFUZZY)
//STRIP001               ) )
//STRIP001          {
//STRIP001              SwFmtFrmSize aNew( rSz );
//STRIP001
//STRIP001              if( !nLowerDiff )
//STRIP001              {
//STRIP001                  if( TBLFIX_CHGPROP == rParam.nMode )        // Tabelle fix, proport.
//STRIP001                  {
//STRIP001                      // relativ berechnen
//STRIP001                      nLowerDiff = nWidth;
//STRIP001                      nLowerDiff *= rParam.nDiff;
//STRIP001                      nLowerDiff /= rParam.nMaxSize;
//STRIP001                  }
//STRIP001                  else
//STRIP001                      nLowerDiff = rParam.nDiff;
//STRIP001              }
//STRIP001
//STRIP001              rParam.nLowerDiff += nLowerDiff;
//STRIP001
//STRIP001              if( rParam.bBigger )
//STRIP001                  aNew.SetWidth( nWidth - nLowerDiff );
//STRIP001              else
//STRIP001                  aNew.SetWidth( nWidth + nLowerDiff );
//STRIP001
//STRIP001              rParam.aShareFmts.SetSize( *pBox, aNew );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      nDist += nWidth;
//STRIP001      if( ( TBLFIX_CHGABS == rParam.nMode || rParam.bLeft ) &&
//STRIP001          nDist > rParam.nSide )
//STRIP001          break;
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

/**/

//#pragma optimize( "", off )

//STRIP001 BOOL lcl_InsSelBox( SwTableLine* pLine, CR_SetBoxWidth& rParam,
//STRIP001                          SwTwips nDist, BOOL bCheck )
//STRIP001 {
//STRIP001  SwTableBoxes& rBoxes = pLine->GetTabBoxes();
//STRIP001  USHORT n, nCmp;
//STRIP001  for( n = 0; n < rBoxes.Count(); ++n )
//STRIP001  {
//STRIP001      SwTableBox* pBox = rBoxes[ n ];
//STRIP001      SwTableBoxFmt* pFmt = (SwTableBoxFmt*)pBox->GetFrmFmt();
//STRIP001      const SwFmtFrmSize& rSz = pFmt->GetFrmSize();
//STRIP001      SwTwips nWidth = rSz.GetWidth();
//STRIP001
//STRIP001      if( bCheck )
//STRIP001      {
//STRIP001          for( USHORT i = 0; i < pBox->GetTabLines().Count(); ++i )
//STRIP001              if( !::lcl_InsSelBox( pBox->GetTabLines()[ i ], rParam,
//STRIP001                                          nDist, TRUE ))
//STRIP001                  return FALSE;
//STRIP001
//STRIP001          // dann noch mal alle "ContentBoxen" sammeln
//STRIP001          if( Abs( nDist + ( rParam.bLeft ? 0 : nWidth )
//STRIP001                  - rParam.nSide ) < COLFUZZY )
//STRIP001              nCmp = 1;
//STRIP001          else if( nDist + ( rParam.bLeft ? 0 : nWidth/2 ) > rParam.nSide )
//STRIP001              nCmp = 2;
//STRIP001          else
//STRIP001              nCmp = 0;
//STRIP001
//STRIP001          if( nCmp )
//STRIP001          {
//STRIP001              rParam.bAnyBoxFnd = TRUE;
//STRIP001              if( pFmt->GetProtect().IsCntntProtected() )
//STRIP001                  return FALSE;
//STRIP001
//STRIP001              if( rParam.bSplittBox &&
//STRIP001                  nWidth - rParam.nDiff <= COLFUZZY +
//STRIP001                      ( 567 / 2 /* min. 0,5 cm Platz lassen*/) )
//STRIP001                  return FALSE;
//STRIP001
//STRIP001              if( pBox->GetSttNd() )
//STRIP001                  rParam.aBoxes.Insert( pBox );
//STRIP001
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          SwTwips nLowerDiff = 0, nOldLower = rParam.nLowerDiff;
//STRIP001          for( USHORT i = 0; i < pBox->GetTabLines().Count(); ++i )
//STRIP001          {
//STRIP001              rParam.nLowerDiff = 0;
//STRIP001              lcl_InsSelBox( pBox->GetTabLines()[ i ], rParam, nDist, FALSE );
//STRIP001
//STRIP001              if( nLowerDiff < rParam.nLowerDiff )
//STRIP001                  nLowerDiff = rParam.nLowerDiff;
//STRIP001          }
//STRIP001          rParam.nLowerDiff = nOldLower;
//STRIP001
//STRIP001          if( nLowerDiff )
//STRIP001              nCmp = 1;
//STRIP001          else if( Abs( nDist + ( rParam.bLeft ? 0 : nWidth )
//STRIP001                              - rParam.nSide ) < COLFUZZY )
//STRIP001              nCmp = 2;
//STRIP001          else if( nDist + nWidth / 2 > rParam.nSide )
//STRIP001              nCmp = 3;
//STRIP001          else
//STRIP001              nCmp = 0;
//STRIP001
//STRIP001          if( nCmp )
//STRIP001          {
//STRIP001              // in dieser Spalte ist der Cursor - also verkleinern / vergroessern
//STRIP001              if( 1 == nCmp )
//STRIP001              {
//STRIP001                  if( !rParam.bSplittBox )
//STRIP001                  {
//STRIP001                      // die akt. Box auf
//STRIP001                      SwFmtFrmSize aNew( rSz );
//STRIP001                      aNew.SetWidth( nWidth + rParam.nDiff );
//STRIP001                      rParam.aShareFmts.SetSize( *pBox, aNew );
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  ASSERT( pBox->GetSttNd(), "Das muss eine EndBox sein!");
//STRIP001
//STRIP001                  if( !rParam.bLeft && 3 != nCmp )
//STRIP001                      ++n;
//STRIP001
//STRIP001                  ::_InsTblBox( pFmt->GetDoc(), rParam.pTblNd,
//STRIP001                                      pLine, pFmt, pBox, n );
//STRIP001
//STRIP001                  SwTableBox* pNewBox = rBoxes[ n ];
//STRIP001                  SwFmtFrmSize aNew( rSz );
//STRIP001                  aNew.SetWidth( rParam.nDiff );
//STRIP001                  rParam.aShareFmts.SetSize( *pNewBox, aNew );
//STRIP001
//STRIP001                  // Sonderfall: kein Platz in den anderen Boxen
//STRIP001                  //              aber in der Zelle
//STRIP001                  if( rParam.bSplittBox )
//STRIP001                  {
//STRIP001                      // die akt. Box auf
//STRIP001                      SwFmtFrmSize aNew( rSz );
//STRIP001                      aNew.SetWidth( nWidth - rParam.nDiff );
//STRIP001                      rParam.aShareFmts.SetSize( *pBox, aNew );
//STRIP001                  }
//STRIP001
//STRIP001                  // Sonderbehandlung fuer Umrandung die Rechte muss
//STRIP001                  // entfernt werden
//STRIP001                  {
//STRIP001                      const SvxBoxItem& rBoxItem = pBox->GetFrmFmt()->GetBox();
//STRIP001                      if( rBoxItem.GetRight() )
//STRIP001                      {
//STRIP001                          SvxBoxItem aTmp( rBoxItem );
//STRIP001                          aTmp.SetLine( 0, BOX_LINE_RIGHT );
//STRIP001                          rParam.aShareFmts.SetAttr( rParam.bLeft
//STRIP001                                                          ? *pNewBox
//STRIP001                                                          : *pBox, aTmp );
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              rParam.nLowerDiff = rParam.nDiff;
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if( rParam.bLeft && rParam.nMode && nDist >= rParam.nSide )
//STRIP001          break;
//STRIP001
//STRIP001      nDist += nWidth;
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }
//#pragma optimize( "", on )

//STRIP001 BOOL lcl_InsOtherBox( SwTableLine* pLine, CR_SetBoxWidth& rParam,
//STRIP001                              SwTwips nDist, BOOL bCheck )
//STRIP001 {
//STRIP001  // Sonderfall: kein Platz in den anderen Boxen aber in der Zelle
//STRIP001  if( rParam.bSplittBox )
//STRIP001      return TRUE;
//STRIP001
//STRIP001  SwTableBoxes& rBoxes = pLine->GetTabBoxes();
//STRIP001  USHORT n;
//STRIP001
//STRIP001  // Tabelle fix, proport.
//STRIP001  if( !rParam.nRemainWidth && TBLFIX_CHGPROP == rParam.nMode )
//STRIP001  {
//STRIP001      // dann die richtige Breite suchen, auf die sich die relative
//STRIP001      // Breitenanpassung bezieht.
//STRIP001      SwTwips nTmpDist = nDist;
//STRIP001      for( n = 0; n < rBoxes.Count(); ++n )
//STRIP001      {
//STRIP001          SwTwips nWidth = rBoxes[ n ]->GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001          if( (nTmpDist + nWidth / 2 ) > rParam.nSide )
//STRIP001          {
//STRIP001              rParam.nRemainWidth = rParam.bLeft
//STRIP001                                      ? USHORT(nTmpDist)
//STRIP001                                      : USHORT(rParam.nTblWidth - nTmpDist);
//STRIP001              break;
//STRIP001          }
//STRIP001          nTmpDist += nWidth;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  for( n = 0; n < rBoxes.Count(); ++n )
//STRIP001  {
//STRIP001      SwTableBox* pBox = rBoxes[ n ];
//STRIP001      SwFrmFmt* pFmt = pBox->GetFrmFmt();
//STRIP001      const SwFmtFrmSize& rSz = pFmt->GetFrmSize();
//STRIP001      SwTwips nWidth = rSz.GetWidth();
//STRIP001
//STRIP001      if( bCheck )
//STRIP001      {
//STRIP001          for( USHORT i = 0; i < pBox->GetTabLines().Count(); ++i )
//STRIP001              if( !::lcl_InsOtherBox( pBox->GetTabLines()[ i ],
//STRIP001                                                  rParam, nDist, TRUE ))
//STRIP001                  return FALSE;
//STRIP001
//STRIP001          if(
//STRIP001              rParam.bLeft ? ((nDist + nWidth / 2 ) <= rParam.nSide &&
//STRIP001                              (TBLFIX_CHGABS != rParam.nMode ||
//STRIP001                              n < rBoxes.Count() &&
//STRIP001                              (nDist + nWidth + rBoxes[ n+1 ]->
//STRIP001                                  GetFrmFmt()->GetFrmSize().GetWidth() / 2)
//STRIP001                                > rParam.nSide ))
//STRIP001                           : (nDist + nWidth / 2 ) > rParam.nSide
//STRIP001              )
//STRIP001          {
//STRIP001              rParam.bAnyBoxFnd = TRUE;
//STRIP001              SwTwips nDiff;
//STRIP001              if( TBLFIX_CHGPROP == rParam.nMode )        // Tabelle fix, proport.
//STRIP001              {
//STRIP001                  // relativ berechnen
//STRIP001                  nDiff = nWidth;
//STRIP001                  nDiff *= rParam.nDiff;
//STRIP001                  nDiff /= rParam.nRemainWidth;
//STRIP001
//STRIP001                  if( nWidth < nDiff || nWidth - nDiff < MINLAY )
//STRIP001                      return FALSE;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  nDiff = rParam.nDiff;
//STRIP001
//STRIP001                  // teste ob die linke oder rechte Box gross genug
//STRIP001                  // ist, um den Platz abzugeben!
//STRIP001                  // es wird davor oder dahinter eine Box eingefuegt!
//STRIP001                  SwTwips nTmpWidth = nWidth;
//STRIP001                  if( rParam.bLeft && pBox->GetUpper()->GetUpper() )
//STRIP001                  {
//STRIP001                      const SwTableBox* pTmpBox = pBox;
//STRIP001                      USHORT nBoxPos = n;
//STRIP001                      while( !nBoxPos && pTmpBox->GetUpper()->GetUpper() )
//STRIP001                      {
//STRIP001                          pTmpBox = pTmpBox->GetUpper()->GetUpper();
//STRIP001                          nBoxPos = pTmpBox->GetUpper()->GetTabBoxes().GetPos( pTmpBox );
//STRIP001                      }
//STRIP001 //                       if( nBoxPos )
//STRIP001                          nTmpWidth = pTmpBox->GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001 //                       else
//STRIP001 //                           nTmpWidth = 0;
//STRIP001                  }
//STRIP001
//STRIP001                  if( nTmpWidth < nDiff || nTmpWidth - nDiff < MINLAY )
//STRIP001                      return FALSE;
//STRIP001                  break;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          SwTwips nLowerDiff = 0, nOldLower = rParam.nLowerDiff;
//STRIP001          for( USHORT i = 0; i < pBox->GetTabLines().Count(); ++i )
//STRIP001          {
//STRIP001              rParam.nLowerDiff = 0;
//STRIP001              lcl_InsOtherBox( pBox->GetTabLines()[ i ], rParam,
//STRIP001                                      nDist, FALSE );
//STRIP001
//STRIP001              if( nLowerDiff < rParam.nLowerDiff )
//STRIP001                  nLowerDiff = rParam.nLowerDiff;
//STRIP001          }
//STRIP001          rParam.nLowerDiff = nOldLower;
//STRIP001
//STRIP001          if( nLowerDiff ||
//STRIP001              (rParam.bLeft ? ((nDist + nWidth / 2 ) <= rParam.nSide &&
//STRIP001                              (TBLFIX_CHGABS != rParam.nMode ||
//STRIP001                              n < rBoxes.Count() &&
//STRIP001                              (nDist + nWidth + rBoxes[ n+1 ]->
//STRIP001                                  GetFrmFmt()->GetFrmSize().GetWidth() / 2)
//STRIP001                                > rParam.nSide ))
//STRIP001                            : (nDist + nWidth / 2 ) > rParam.nSide ))
//STRIP001          {
//STRIP001              if( !nLowerDiff )
//STRIP001              {
//STRIP001                  if( TBLFIX_CHGPROP == rParam.nMode )        // Tabelle fix, proport.
//STRIP001                  {
//STRIP001                      // relativ berechnen
//STRIP001                      nLowerDiff = nWidth;
//STRIP001                      nLowerDiff *= rParam.nDiff;
//STRIP001                      nLowerDiff /= rParam.nRemainWidth;
//STRIP001                  }
//STRIP001                  else
//STRIP001                      nLowerDiff = rParam.nDiff;
//STRIP001              }
//STRIP001
//STRIP001              SwFmtFrmSize aNew( rSz );
//STRIP001              rParam.nLowerDiff += nLowerDiff;
//STRIP001
//STRIP001              if( rParam.bBigger )
//STRIP001                  aNew.SetWidth( nWidth - nLowerDiff );
//STRIP001              else
//STRIP001                  aNew.SetWidth( nWidth + nLowerDiff );
//STRIP001              rParam.aShareFmts.SetSize( *pBox, aNew );
//STRIP001
//STRIP001              if( TBLFIX_CHGABS == rParam.nMode )
//STRIP001                  break;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      nDist += nWidth;
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }


// das Ergebnis des Positions Vergleiches
//  POS_BEFORE,             // Box liegt davor
//  POS_BEHIND,             // Box liegt dahinter
//  POS_INSIDE,             // Box liegt vollstaendig in Start/End
//  POS_OUTSIDE,            // Box ueberlappt Start/End vollstaendig
//  POS_EQUAL,              // Box und Start/End sind gleich
//  POS_OVERLAP_BEFORE,     // Box ueberlappt den Start
//  POS_OVERLAP_BEHIND      // Box ueberlappt das Ende

//STRIP001 SwComparePosition _CheckBoxInRange( USHORT nStt, USHORT nEnd,
//STRIP001                                  USHORT nBoxStt, USHORT nBoxEnd )
//STRIP001 {
//STRIP001 // COLFUZZY noch beachten!!
//STRIP001  SwComparePosition nRet;
//STRIP001  if( nBoxStt + COLFUZZY < nStt )
//STRIP001  {
//STRIP001      if( nBoxEnd > nStt + COLFUZZY )
//STRIP001      {
//STRIP001          if( nBoxEnd >= nEnd + COLFUZZY )
//STRIP001              nRet = POS_OUTSIDE;
//STRIP001          else
//STRIP001              nRet = POS_OVERLAP_BEFORE;
//STRIP001      }
//STRIP001      else
//STRIP001          nRet = POS_BEFORE;
//STRIP001  }
//STRIP001  else if( nEnd > nBoxStt + COLFUZZY )
//STRIP001  {
//STRIP001      if( nEnd + COLFUZZY >= nBoxEnd )
//STRIP001      {
//STRIP001          if( COLFUZZY > Abs( long(nEnd) - long(nBoxEnd) ) &&
//STRIP001              COLFUZZY > Abs( long(nStt) - long(nBoxStt) ) )
//STRIP001              nRet = POS_EQUAL;
//STRIP001          else
//STRIP001              nRet = POS_INSIDE;
//STRIP001      }
//STRIP001      else
//STRIP001          nRet = POS_OVERLAP_BEHIND;
//STRIP001  }
//STRIP001  else
//STRIP001      nRet = POS_BEHIND;
//STRIP001
//STRIP001  return nRet;
//STRIP001 }

//STRIP001 void lcl_DelSelBox_CorrLowers( SwTableLine& rLine, CR_SetBoxWidth& rParam,
//STRIP001                              SwTwips nWidth )
//STRIP001 {
//STRIP001  // 1. Schritt die eigene Breite feststellen
//STRIP001  SwTableBoxes& rBoxes = rLine.GetTabBoxes();
//STRIP001  SwTwips nBoxWidth = 0;
//STRIP001
//STRIP001  for( USHORT n = rBoxes.Count(); n; )
//STRIP001      nBoxWidth += rBoxes[ --n ]->GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001
//STRIP001  if( COLFUZZY < Abs( nWidth - nBoxWidth ))
//STRIP001  {
//STRIP001      //  sie muessen also angepasst werden
//STRIP001      for( n = rBoxes.Count(); n; )
//STRIP001      {
//STRIP001          SwTableBox* pBox = rBoxes[ --n ];
//STRIP001          SwFmtFrmSize aNew( pBox->GetFrmFmt()->GetFrmSize() );
//STRIP001          long nDiff = aNew.GetWidth();
//STRIP001          nDiff *= nWidth;
//STRIP001          nDiff /= nBoxWidth;
//STRIP001          aNew.SetWidth( nDiff );
//STRIP001
//STRIP001          rParam.aShareFmts.SetSize( *pBox, aNew );
//STRIP001
//STRIP001          if( !pBox->GetSttNd() )
//STRIP001          {
//STRIP001              // hat selbst auch Lower, also auch die anpassen
//STRIP001              for( USHORT i = pBox->GetTabLines().Count(); i; )
//STRIP001                  ::lcl_DelSelBox_CorrLowers( *pBox->GetTabLines()[ --i ],
//STRIP001                                              rParam, nDiff  );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void lcl_ChgBoxSize( SwTableBox& rBox, CR_SetBoxWidth& rParam,
//STRIP001                  const SwFmtFrmSize& rOldSz,
//STRIP001                  USHORT& rDelWidth, SwTwips nDist )
//STRIP001 {
//STRIP001  long nDiff;
//STRIP001  BOOL bSetSize = FALSE;
//STRIP001
//STRIP001  switch( rParam.nMode )
//STRIP001  {
//STRIP001  case TBLFIX_CHGABS:     // Tabelle feste Breite, den Nachbar andern
//STRIP001      nDiff = rDelWidth + rParam.nLowerDiff;
//STRIP001      bSetSize = TRUE;
//STRIP001      break;
//STRIP001
//STRIP001  case TBLFIX_CHGPROP:    // Tabelle feste Breite, alle Nachbarn aendern
//STRIP001      if( !rParam.nRemainWidth )
//STRIP001      {
//STRIP001          // dann kurz berechnen:
//STRIP001          if( rParam.bLeft )
//STRIP001              rParam.nRemainWidth = USHORT(nDist);
//STRIP001          else
//STRIP001              rParam.nRemainWidth = USHORT(rParam.nTblWidth - nDist);
//STRIP001      }
//STRIP001
//STRIP001      // relativ berechnen
//STRIP001      nDiff = rOldSz.GetWidth();
//STRIP001      nDiff *= rDelWidth + rParam.nLowerDiff;
//STRIP001      nDiff /= rParam.nRemainWidth;
//STRIP001
//STRIP001      bSetSize = TRUE;
//STRIP001      break;
//STRIP001
//STRIP001  case TBLVAR_CHGABS:     // Tabelle variable, alle Nachbarn aendern
//STRIP001      if( COLFUZZY < Abs( rParam.nBoxWidth -
//STRIP001                          ( rDelWidth + rParam.nLowerDiff )))
//STRIP001      {
//STRIP001          nDiff = rDelWidth + rParam.nLowerDiff - rParam.nBoxWidth;
//STRIP001          if( 0 < nDiff )
//STRIP001              rDelWidth -= USHORT(nDiff);
//STRIP001          else
//STRIP001              rDelWidth += USHORT(-nDiff);
//STRIP001          bSetSize = TRUE;
//STRIP001      }
//STRIP001      break;
//STRIP001  }
//STRIP001
//STRIP001  if( bSetSize )
//STRIP001  {
//STRIP001      SwFmtFrmSize aNew( rOldSz );
//STRIP001      aNew.SetWidth( aNew.GetWidth() + nDiff );
//STRIP001      rParam.aShareFmts.SetSize( rBox, aNew );
//STRIP001
//STRIP001      // dann leider nochmals die Lower anpassen
//STRIP001      for( USHORT i = rBox.GetTabLines().Count(); i; )
//STRIP001          ::lcl_DelSelBox_CorrLowers( *rBox.GetTabLines()[ --i ], rParam,
//STRIP001                                          aNew.GetWidth() );
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL lcl_DeleteBox_Rekursiv( CR_SetBoxWidth& rParam, SwTableBox& rBox,
//STRIP001                          BOOL bCheck )
//STRIP001 {
//STRIP001  BOOL bRet = TRUE;
//STRIP001  if( rBox.GetSttNd() )
//STRIP001  {
//STRIP001      if( bCheck )
//STRIP001      {
//STRIP001          rParam.bAnyBoxFnd = TRUE;
//STRIP001          if( rBox.GetFrmFmt()->GetProtect().IsCntntProtected() )
//STRIP001              bRet = FALSE;
//STRIP001          else
//STRIP001          {
//STRIP001              SwTableBox* pBox = &rBox;
//STRIP001              rParam.aBoxes.Insert( pBox );
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001          ::_DeleteBox( rParam.pTblNd->GetTable(), &rBox,
//STRIP001                          rParam.pUndo, FALSE, TRUE, &rParam.aShareFmts );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // die muessen leider alle sequentiel ueber die
//STRIP001      // Contentboxen geloescht werden
//STRIP001      for( USHORT i = rBox.GetTabLines().Count(); i; )
//STRIP001      {
//STRIP001          SwTableLine& rLine = *rBox.GetTabLines()[ --i ];
//STRIP001          for( USHORT n = rLine.GetTabBoxes().Count(); n; )
//STRIP001              if( !::lcl_DeleteBox_Rekursiv( rParam,
//STRIP001                              *rLine.GetTabBoxes()[ --n ], bCheck ))
//STRIP001                  return FALSE;
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL lcl_DelSelBox( SwTableLine* pLine, CR_SetBoxWidth& rParam,
//STRIP001                  SwTwips nDist, BOOL bCheck )
//STRIP001 {
//STRIP001  SwTableBoxes& rBoxes = pLine->GetTabBoxes();
//STRIP001  USHORT n, nCntEnd, nBoxChkStt, nBoxChkEnd, nDelWidth = 0;
//STRIP001  if( rParam.bLeft )
//STRIP001  {
//STRIP001      n = rBoxes.Count();
//STRIP001      nCntEnd = 0;
//STRIP001      nBoxChkStt = (USHORT)rParam.nSide;
//STRIP001      nBoxChkEnd = rParam.nSide + rParam.nBoxWidth;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      n = 0;
//STRIP001      nCntEnd = rBoxes.Count();
//STRIP001      nBoxChkStt = rParam.nSide - rParam.nBoxWidth;
//STRIP001      nBoxChkEnd = (USHORT)rParam.nSide;
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001  while( n != nCntEnd )
//STRIP001  {
//STRIP001      SwTableBox* pBox;
//STRIP001      if( rParam.bLeft )
//STRIP001          pBox = rBoxes[ --n ];
//STRIP001      else
//STRIP001          pBox = rBoxes[ n++ ];
//STRIP001
//STRIP001      SwFrmFmt* pFmt = pBox->GetFrmFmt();
//STRIP001      const SwFmtFrmSize& rSz = pFmt->GetFrmSize();
//STRIP001      long nWidth = rSz.GetWidth();
//STRIP001      BOOL bDelBox = FALSE, bChgLowers = FALSE;
//STRIP001
//STRIP001      // die Boxenbreite testen und entpsrechend reagieren
//STRIP001      SwComparePosition ePosType = ::_CheckBoxInRange(
//STRIP001                          nBoxChkStt, nBoxChkEnd,
//STRIP001                          USHORT(rParam.bLeft ? nDist - nWidth : nDist),
//STRIP001                          USHORT(rParam.bLeft ? nDist : nDist + nWidth));
//STRIP001
//STRIP001      switch( ePosType )
//STRIP001      {
//STRIP001      case POS_BEFORE:
//STRIP001          if( bCheck )
//STRIP001          {
//STRIP001              if( rParam.bLeft )
//STRIP001                  return TRUE;
//STRIP001          }
//STRIP001          else if( rParam.bLeft )
//STRIP001          {
//STRIP001              ::lcl_ChgBoxSize( *pBox, rParam, rSz, nDelWidth, nDist );
//STRIP001              if( TBLFIX_CHGABS == rParam.nMode )
//STRIP001                  n = nCntEnd;
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case POS_BEHIND:
//STRIP001          if( bCheck )
//STRIP001          {
//STRIP001              if( !rParam.bLeft )
//STRIP001                  return TRUE;
//STRIP001          }
//STRIP001          else if( !rParam.bLeft )
//STRIP001          {
//STRIP001              ::lcl_ChgBoxSize( *pBox, rParam, rSz, nDelWidth, nDist );
//STRIP001              if( TBLFIX_CHGABS == rParam.nMode )
//STRIP001                  n = nCntEnd;
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case POS_OUTSIDE:           // Box ueberlappt Start/End vollstaendig
//STRIP001      case POS_INSIDE:            // Box liegt vollstaendig in Start/End
//STRIP001      case POS_EQUAL:             // Box und Start/End sind gleich
//STRIP001          bDelBox = TRUE;
//STRIP001          break;
//STRIP001
//STRIP001      case POS_OVERLAP_BEFORE:     // Box ueberlappt den Start
//STRIP001          if( nBoxChkStt <= ( nDist + (rParam.bLeft ? - nWidth / 2
//STRIP001                                                    : nWidth / 2 )))
//STRIP001          {
//STRIP001              if( !pBox->GetSttNd() )
//STRIP001                  bChgLowers = TRUE;
//STRIP001              else
//STRIP001                  bDelBox = TRUE;
//STRIP001          }
//STRIP001          else if( !bCheck && rParam.bLeft )
//STRIP001          {
//STRIP001              if( !pBox->GetSttNd() )
//STRIP001                  bChgLowers = TRUE;
//STRIP001              else
//STRIP001              {
//STRIP001                  ::lcl_ChgBoxSize( *pBox, rParam, rSz, nDelWidth, nDist );
//STRIP001                  if( TBLFIX_CHGABS == rParam.nMode )
//STRIP001                      n = nCntEnd;
//STRIP001              }
//STRIP001          }
//STRIP001          break;
//STRIP001
//STRIP001      case POS_OVERLAP_BEHIND:     // Box ueberlappt das Ende
//STRIP001          // JP 10.02.99:
//STRIP001          // generell loeschen oder wie beim OVERLAP_Before nur die, die
//STRIP001          // bis zur Haelfte in die "Loesch-"Box reicht ???
//STRIP001          if( !pBox->GetSttNd() )
//STRIP001              bChgLowers = TRUE;
//STRIP001          else
//STRIP001              bDelBox = TRUE;
//STRIP001          break;
//STRIP001      }
//STRIP001
//STRIP001      if( bDelBox )
//STRIP001      {
//STRIP001          nDelWidth += USHORT(nWidth);
//STRIP001          if( bCheck )
//STRIP001          {
//STRIP001              // die letzte/erste Box kann nur bei Tbl-Var geloescht werden,
//STRIP001              // wenn diese so gross ist, wie die Aenderung an der Tabelle
//STRIP001              if( (( TBLVAR_CHGABS != rParam.nMode ||
//STRIP001                      nDelWidth != rParam.nBoxWidth ) &&
//STRIP001                   COLFUZZY > Abs( rParam.bLeft
//STRIP001                                  ? nWidth - nDist
//STRIP001                                  : (nDist + nWidth - rParam.nTblWidth )))
//STRIP001                  || !::lcl_DeleteBox_Rekursiv( rParam, *pBox, bCheck ) )
//STRIP001                  return FALSE;
//STRIP001
//STRIP001              if( pFmt->GetProtect().IsCntntProtected() )
//STRIP001                  return FALSE;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              ::lcl_DeleteBox_Rekursiv( rParam, *pBox, bCheck );
//STRIP001
//STRIP001              if( !rParam.bLeft )
//STRIP001                  --n, --nCntEnd;
//STRIP001          }
//STRIP001      }
//STRIP001      else if( bChgLowers )
//STRIP001      {
//STRIP001          BOOL bFirst = TRUE, bCorrLowers = FALSE;
//STRIP001          long nLowerDiff = 0;
//STRIP001          long nOldLower = rParam.nLowerDiff;
//STRIP001          USHORT nOldRemain = rParam.nRemainWidth;
//STRIP001
//STRIP001          for( USHORT i = pBox->GetTabLines().Count(); i; )
//STRIP001          {
//STRIP001              rParam.nLowerDiff = nDelWidth + nOldLower;
//STRIP001              rParam.nRemainWidth = nOldRemain;
//STRIP001              SwTableLine* pLine = pBox->GetTabLines()[ --i ];
//STRIP001              if( !::lcl_DelSelBox( pLine, rParam, nDist, bCheck ))
//STRIP001                  return FALSE;
//STRIP001
//STRIP001              // gibt es die Box und die darin enthaltenen Lines noch??
//STRIP001              if( n < rBoxes.Count() &&
//STRIP001                  pBox == rBoxes[ rParam.bLeft ? n : n-1 ] &&
//STRIP001                  i < pBox->GetTabLines().Count() &&
//STRIP001                  pLine == pBox->GetTabLines()[ i ] )
//STRIP001              {
//STRIP001                  if( !bFirst && !bCorrLowers &&
//STRIP001                      COLFUZZY < Abs( nLowerDiff - rParam.nLowerDiff ) )
//STRIP001                      bCorrLowers = TRUE;
//STRIP001
//STRIP001                  // die groesste "loesch" Breite entscheidet, aber nur wenn
//STRIP001                  // nicht die gesamte Line geloescht wurde
//STRIP001                  if( nLowerDiff < rParam.nLowerDiff )
//STRIP001                      nLowerDiff = rParam.nLowerDiff;
//STRIP001
//STRIP001                  bFirst = FALSE;
//STRIP001              }
//STRIP001          }
//STRIP001          rParam.nLowerDiff = nOldLower;
//STRIP001          rParam.nRemainWidth = nOldRemain;
//STRIP001
//STRIP001          // wurden alle Boxen geloescht? Dann ist die DelBreite natuerlich
//STRIP001          // die Boxenbreite
//STRIP001          if( !nLowerDiff )
//STRIP001              nLowerDiff = nWidth;
//STRIP001
//STRIP001          // DelBreite anpassen!!
//STRIP001          nDelWidth += USHORT(nLowerDiff);
//STRIP001
//STRIP001          if( !bCheck )
//STRIP001          {
//STRIP001              // wurde die Box schon entfernt?
//STRIP001              if( n > rBoxes.Count() ||
//STRIP001                  pBox != rBoxes[ ( rParam.bLeft ? n : n-1 ) ] )
//STRIP001              {
//STRIP001                  // dann beim Loeschen nach rechts die Laufvar. anpassen
//STRIP001                  if( !rParam.bLeft )
//STRIP001                      --n, --nCntEnd;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  // sonst muss die Groesse der Box angepasst werden
//STRIP001                  SwFmtFrmSize aNew( rSz );
//STRIP001                  BOOL bCorrRel = FALSE;
//STRIP001
//STRIP001                  if( TBLVAR_CHGABS != rParam.nMode )
//STRIP001                  {
//STRIP001                      switch( ePosType )
//STRIP001                      {
//STRIP001                      case POS_OVERLAP_BEFORE:    // Box ueberlappt den Start
//STRIP001                          if( TBLFIX_CHGPROP == rParam.nMode )
//STRIP001                              bCorrRel = rParam.bLeft;
//STRIP001                          else if( rParam.bLeft ) // TBLFIX_CHGABS
//STRIP001                          {
//STRIP001                              nLowerDiff = nLowerDiff - nDelWidth;
//STRIP001                              bCorrLowers = TRUE;
//STRIP001                              n = nCntEnd;
//STRIP001                          }
//STRIP001                          break;
//STRIP001
//STRIP001                      case POS_OVERLAP_BEHIND:    // Box ueberlappt das Ende
//STRIP001                          if( TBLFIX_CHGPROP == rParam.nMode )
//STRIP001                              bCorrRel = !rParam.bLeft;
//STRIP001                          else if( !rParam.bLeft )    // TBLFIX_CHGABS
//STRIP001                          {
//STRIP001                              nLowerDiff = nLowerDiff - nDelWidth;
//STRIP001                              bCorrLowers = TRUE;
//STRIP001                              n = nCntEnd;
//STRIP001                          }
//STRIP001                          break;
//STRIP001
//STRIP001                      default:
//STRIP001                          ASSERT( !pBox, "hier sollte man nie hinkommen" );
//STRIP001                          break;
//STRIP001                      }
//STRIP001                  }
//STRIP001
//STRIP001                  if( bCorrRel )
//STRIP001                  {
//STRIP001                      if( !rParam.nRemainWidth )
//STRIP001                      {
//STRIP001                          // dann kurz berechnen:
//STRIP001                          if( rParam.bLeft )
//STRIP001                              rParam.nRemainWidth = USHORT(nDist - nLowerDiff);
//STRIP001                          else
//STRIP001                              rParam.nRemainWidth = USHORT(rParam.nTblWidth - nDist
//STRIP001                                                              - nLowerDiff );
//STRIP001                      }
//STRIP001
//STRIP001                      long nDiff = aNew.GetWidth() - nLowerDiff;
//STRIP001                      nDiff *= nDelWidth + rParam.nLowerDiff;
//STRIP001                      nDiff /= rParam.nRemainWidth;
//STRIP001
//STRIP001                      aNew.SetWidth( aNew.GetWidth() - nLowerDiff + nDiff );
//STRIP001                  }
//STRIP001                  else
//STRIP001                      aNew.SetWidth( aNew.GetWidth() - nLowerDiff );
//STRIP001                  rParam.aShareFmts.SetSize( *pBox, aNew );
//STRIP001
//STRIP001                  if( bCorrLowers )
//STRIP001                  {
//STRIP001                      // dann leider nochmals die Lower anpassen
//STRIP001                      for( i = pBox->GetTabLines().Count(); i; )
//STRIP001                          ::lcl_DelSelBox_CorrLowers( *pBox->
//STRIP001                              GetTabLines()[ --i ], rParam, aNew.GetWidth() );
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if( rParam.bLeft )
//STRIP001          nDist -= nWidth;
//STRIP001      else
//STRIP001          nDist += nWidth;
//STRIP001  }
//STRIP001  rParam.nLowerDiff = nDelWidth;
//STRIP001  return TRUE;
//STRIP001 }

// Dummy Funktion fuer die Methode SetColWidth
//STRIP001 BOOL lcl_DelOtherBox( SwTableLine* , CR_SetBoxWidth& , SwTwips , BOOL )
//STRIP001 {
//STRIP001  return TRUE;
//STRIP001 }

/**/

//STRIP001 void lcl_AjustLines( SwTableLine* pLine, CR_SetBoxWidth& rParam )
//STRIP001 {
//STRIP001  SwTableBoxes& rBoxes = pLine->GetTabBoxes();
//STRIP001  for( USHORT n = 0; n < rBoxes.Count(); ++n )
//STRIP001  {
//STRIP001      SwTableBox* pBox = rBoxes[ n ];
//STRIP001
//STRIP001      SwFmtFrmSize aSz( pBox->GetFrmFmt()->GetFrmSize() );
//STRIP001      SwTwips nWidth = aSz.GetWidth();
//STRIP001      nWidth *= rParam.nDiff;
//STRIP001      nWidth /= rParam.nMaxSize;
//STRIP001      aSz.SetWidth( nWidth );
//STRIP001      rParam.aShareFmts.SetSize( *pBox, aSz );
//STRIP001
//STRIP001      for( USHORT i = 0; i < pBox->GetTabLines().Count(); ++i )
//STRIP001          ::lcl_AjustLines( pBox->GetTabLines()[ i ], rParam );
//STRIP001  }
//STRIP001 }

#if !defined( PRODUCT ) || defined( JP_DEBUG )

//STRIP001 void _CheckBoxWidth( const SwTableLine& rLine, SwTwips nSize )
//STRIP001 {
//STRIP001  const SwTableBoxes& rBoxes = rLine.GetTabBoxes();
//STRIP001
//STRIP001  SwTwips nAktSize = 0;
//STRIP001  // checke doch mal ob die Tabellen korrekte Breiten haben
//STRIP001  for( USHORT n = 0; n < rBoxes.Count(); ++n  )
//STRIP001  {
//STRIP001      const SwTableBox* pBox = rBoxes[ n ];
//STRIP001      SwTwips nBoxW = pBox->GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001      nAktSize += nBoxW;
//STRIP001
//STRIP001      for( USHORT i = 0; i < pBox->GetTabLines().Count(); ++i )
//STRIP001          _CheckBoxWidth( *pBox->GetTabLines()[ i ], nBoxW );
//STRIP001  }
//STRIP001
//STRIP001  if( Abs( nAktSize - nSize ) > ( COLFUZZY * rBoxes.Count() ) )
//STRIP001  {
//STRIP001      DBG_ERROR( "Boxen der Line zu klein/gross" );
//STRIP001 #if defined( WNT ) && defined( JP_DEBUG )
//STRIP001      __asm int 3;
//STRIP001 #endif
//STRIP001  }
//STRIP001 }

#endif

//STRIP001 _FndBox* lcl_SaveInsDelData( CR_SetBoxWidth& rParam, SwUndo** ppUndo,
//STRIP001                              SwTableSortBoxes& rTmpLst, SwTwips nDistStt )
//STRIP001 {
//STRIP001  // suche alle Boxen / Lines
//STRIP001  SwTable& rTbl = rParam.pTblNd->GetTable();
//STRIP001
//STRIP001  if( !rParam.aBoxes.Count() )
//STRIP001  {
//STRIP001      // erstmal die Boxen besorgen !
//STRIP001      if( rParam.bBigger )
//STRIP001          for( USHORT n = 0; n < rTbl.GetTabLines().Count(); ++n )
//STRIP001              ::lcl_DelSelBox( rTbl.GetTabLines()[ n ], rParam, nDistStt, TRUE );
//STRIP001      else
//STRIP001          for( USHORT n = 0; n < rTbl.GetTabLines().Count(); ++n )
//STRIP001              ::lcl_InsSelBox( rTbl.GetTabLines()[ n ], rParam, nDistStt, TRUE );
//STRIP001  }
//STRIP001
//STRIP001  // loeschen der gesamten Tabelle verhindern
//STRIP001  if( rParam.bBigger && rParam.aBoxes.Count() ==
//STRIP001      rTbl.GetTabSortBoxes().Count() )
//STRIP001      return 0;
//STRIP001
//STRIP001  _FndBox* pFndBox = new _FndBox( 0, 0 );
//STRIP001  if( rParam.bBigger )
//STRIP001      pFndBox->SetTableLines( rParam.aBoxes, rTbl );
//STRIP001  else
//STRIP001  {
//STRIP001      _FndPara aPara( rParam.aBoxes, pFndBox );
//STRIP001      rTbl.GetTabLines().ForEach( &_FndLineCopyCol, &aPara );
//STRIP001      ASSERT( pFndBox->GetLines().Count(), "Wo sind die Boxen" );
//STRIP001      pFndBox->SetTableLines( rTbl );
//STRIP001
//STRIP001      if( ppUndo )
//STRIP001          rTmpLst.Insert( &rTbl.GetTabSortBoxes(), 0, rTbl.GetTabSortBoxes().Count() );
//STRIP001  }
//STRIP001
//STRIP001  //Lines fuer das Layout-Update herausuchen.
//STRIP001  pFndBox->DelFrms( rTbl );
//STRIP001  pFndBox->SaveChartData( rTbl );
//STRIP001
//STRIP001  return pFndBox;
//STRIP001 }

//STRIP001 BOOL SwTable::SetColWidth( SwTableBox& rAktBox, USHORT eType,
//STRIP001                      SwTwips nAbsDiff, SwTwips nRelDiff, SwUndo** ppUndo )
//STRIP001 {
//STRIP001  SetHTMLTableLayout( 0 );    // MIB 9.7.97: HTML-Layout loeschen
//STRIP001
//STRIP001  const SwFmtFrmSize& rSz = GetFrmFmt()->GetFrmSize();
//STRIP001  const SvxLRSpaceItem& rLR = GetFrmFmt()->GetLRSpace();
//STRIP001
//STRIP001  _FndBox* pFndBox = 0;                   // fuers Einfuegen/Loeschen
//STRIP001  SwTableSortBoxes aTmpLst( 0, 5 );       // fuers Undo
//STRIP001  BOOL bBigger,
//STRIP001      bRet = FALSE,
//STRIP001      bLeft = WH_COL_LEFT == ( eType & 0xff ) ||
//STRIP001              WH_CELL_LEFT == ( eType & 0xff ),
//STRIP001      bInsDel = 0 != (eType & WH_FLAG_INSDEL );
//STRIP001  USHORT n;
//STRIP001  ULONG nBoxIdx = rAktBox.GetSttIdx();
//STRIP001
//STRIP001  // bestimme die akt. Kante der Box
//STRIP001  // wird nur fuer die Breitenmanipulation benoetigt!
//STRIP001  SwTwips nDist = ::lcl_GetDistance( &rAktBox, bLeft ), nDistStt = 0;
//STRIP001  CR_SetBoxWidth aParam( eType, nRelDiff, nDist, rSz.GetWidth(),
//STRIP001                          bLeft ? nDist : rSz.GetWidth() - nDist,
//STRIP001                          (SwTableNode*)rAktBox.GetSttNd()->FindTableNode() );
//STRIP001  bBigger = aParam.bBigger;
//STRIP001
//STRIP001  FN_lcl_SetBoxWidth fnSelBox, fnOtherBox;
//STRIP001  if( bInsDel )
//STRIP001  {
//STRIP001      if( bBigger )
//STRIP001      {
//STRIP001          fnSelBox = lcl_DelSelBox;
//STRIP001          fnOtherBox = lcl_DelOtherBox;
//STRIP001          aParam.nBoxWidth = (USHORT)rAktBox.GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001          if( bLeft )
//STRIP001              nDistStt = rSz.GetWidth();
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          fnSelBox = lcl_InsSelBox;
//STRIP001          fnOtherBox = lcl_InsOtherBox;
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      fnSelBox = lcl_SetSelBoxWidth;
//STRIP001      fnOtherBox = lcl_SetOtherBoxWidth;
//STRIP001  }
//STRIP001
//STRIP001
//STRIP001  switch( eType & 0xff )
//STRIP001  {
//STRIP001  case WH_COL_RIGHT:
//STRIP001  case WH_COL_LEFT:
//STRIP001      if( TBLVAR_CHGABS == eTblChgMode )
//STRIP001      {
//STRIP001          if( bInsDel )
//STRIP001              bBigger = !bBigger;
//STRIP001
//STRIP001          // erstmal testen, ob ueberhaupt Platz ist
//STRIP001          BOOL bChgLRSpace = TRUE;
//STRIP001          if( bBigger )
//STRIP001          {
//STRIP001              if( GetFrmFmt()->GetDoc()->IsBrowseMode() &&
//STRIP001                  !rSz.GetWidthPercent() )
//STRIP001              {
//STRIP001                  bRet = rSz.GetWidth() < USHRT_MAX - nRelDiff;
//STRIP001                  bChgLRSpace = bLeft ? rLR.GetLeft() >= nAbsDiff
//STRIP001                                      : rLR.GetRight() >= nAbsDiff;
//STRIP001              }
//STRIP001              else
//STRIP001                  bRet = bLeft ? rLR.GetLeft() >= nAbsDiff
//STRIP001                               : rLR.GetRight() >= nAbsDiff;
//STRIP001
//STRIP001              if( !bRet && bInsDel &&
//STRIP001                  // auf der anderen Seite Platz?
//STRIP001                  ( bLeft ? rLR.GetRight() >= nAbsDiff
//STRIP001                          : rLR.GetLeft() >= nAbsDiff ))
//STRIP001              {
//STRIP001                  bRet = TRUE; bLeft = !bLeft;
//STRIP001              }
//STRIP001
//STRIP001              if( !bRet )
//STRIP001              {
//STRIP001                  // dann sich selbst rekursiv aufrufen; nur mit
//STRIP001                  // einem anderen Mode -> proprotional
//STRIP001                  TblChgMode eOld = eTblChgMode;
//STRIP001                  eTblChgMode = TBLFIX_CHGPROP;
//STRIP001
//STRIP001                  bRet = SetColWidth( rAktBox, eType, nAbsDiff, nRelDiff,
//STRIP001                                      ppUndo );
//STRIP001                  eTblChgMode = eOld;
//STRIP001                  return bRet;
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              bRet = TRUE;
//STRIP001              for( n = 0; n < aLines.Count(); ++n )
//STRIP001              {
//STRIP001                  aParam.LoopClear();
//STRIP001                  if( !(*fnSelBox)( aLines[ n ], aParam, nDistStt, TRUE ))
//STRIP001                  {
//STRIP001                      bRet = FALSE;
//STRIP001                      break;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          if( bRet )
//STRIP001          {
//STRIP001              if( bInsDel )
//STRIP001              {
//STRIP001                  pFndBox = ::lcl_SaveInsDelData( aParam, ppUndo,
//STRIP001                                                  aTmpLst, nDistStt );
//STRIP001                  if( aParam.bBigger && aParam.aBoxes.Count() ==
//STRIP001                                  aSortCntBoxes.Count() )
//STRIP001                  {
//STRIP001                      // dies gesamte Tabelle soll geloescht werden!!
//STRIP001                      GetFrmFmt()->GetDoc()->DeleteRowCol( aParam.aBoxes );
//STRIP001                      return FALSE;
//STRIP001                  }
//STRIP001
//STRIP001                  if( ppUndo )
//STRIP001                      *ppUndo = aParam.CreateUndo(
//STRIP001                                      aParam.bBigger ? UNDO_TABLE_DELBOX
//STRIP001                                                     : UNDO_TABLE_INSCOL );
//STRIP001              }
//STRIP001              else if( ppUndo )
//STRIP001                  *ppUndo = new SwUndoAttrTbl( *aParam.pTblNd, TRUE );
//STRIP001
//STRIP001              long nFrmWidth = LONG_MAX;
//STRIP001              LockModify();
//STRIP001              SwFmtFrmSize aSz( rSz );
//STRIP001              SvxLRSpaceItem aLR( rLR );
//STRIP001              if( bBigger )
//STRIP001              {
//STRIP001                  // falls die Tabelle keinen Platz zum Wachsen hat, dann
//STRIP001                  // muessen wir welchen schaffen!
//STRIP001                  if( aSz.GetWidth() + nRelDiff > USHRT_MAX )
//STRIP001                  {
//STRIP001                      // dann mal herunterbrechen auf USHRT_MAX / 2
//STRIP001                      CR_SetBoxWidth aTmpPara( 0, aSz.GetWidth() / 2,
//STRIP001                                      0, aSz.GetWidth(), aSz.GetWidth(), aParam.pTblNd );
//STRIP001                      for( USHORT n = 0; n < aLines.Count(); ++n )
//STRIP001                          ::lcl_AjustLines( aLines[ n ], aTmpPara );
//STRIP001                      aSz.SetWidth( aSz.GetWidth() / 2 );
//STRIP001                      aParam.nDiff = nRelDiff /= 2;
//STRIP001                      aParam.nSide /= 2;
//STRIP001                      aParam.nMaxSize /= 2;
//STRIP001                  }
//STRIP001
//STRIP001                  if( bLeft )
//STRIP001                      aLR.SetLeft( USHORT( aLR.GetLeft() - nAbsDiff ) );
//STRIP001                  else
//STRIP001                      aLR.SetRight( USHORT( aLR.GetRight() - nAbsDiff ) );
//STRIP001              }
//STRIP001              else if( bLeft )
//STRIP001                  aLR.SetLeft( USHORT( aLR.GetLeft() + nAbsDiff ) );
//STRIP001              else
//STRIP001                  aLR.SetRight( USHORT( aLR.GetRight() + nAbsDiff ) );
//STRIP001
//STRIP001              if( bChgLRSpace )
//STRIP001                  GetFrmFmt()->SetAttr( aLR );
//STRIP001              const SwFmtHoriOrient& rHOri = GetFrmFmt()->GetHoriOrient();
//STRIP001              if( HORI_FULL == rHOri.GetHoriOrient() ||
//STRIP001                  (HORI_LEFT == rHOri.GetHoriOrient() && aLR.GetLeft()) ||
//STRIP001                  (HORI_RIGHT == rHOri.GetHoriOrient() && aLR.GetRight()))
//STRIP001              {
//STRIP001                  SwFmtHoriOrient aHOri( rHOri );
//STRIP001                  aHOri.SetHoriOrient( HORI_NONE );
//STRIP001                  GetFrmFmt()->SetAttr( aHOri );
//STRIP001
//STRIP001                  // sollte die Tabelle noch auf relativen Werten
//STRIP001                  // (USHRT_MAX) stehen dann muss es jetzt auf absolute
//STRIP001                  // umgerechnet werden. Bug 61494
//STRIP001                  if( GetFrmFmt()->GetDoc()->IsBrowseMode() &&
//STRIP001                      !rSz.GetWidthPercent() )
//STRIP001                  {
//STRIP001                      SwTabFrm* pTabFrm = (SwTabFrm*)SwClientIter(
//STRIP001                                  *GetFrmFmt() ).First( TYPE( SwTabFrm ));
//STRIP001                      if( pTabFrm &&
//STRIP001                          pTabFrm->Prt().Width() != rSz.GetWidth() )
//STRIP001                      {
//STRIP001                          nFrmWidth = pTabFrm->Prt().Width();
//STRIP001                          if( bBigger )
//STRIP001                              nFrmWidth += nAbsDiff;
//STRIP001                          else
//STRIP001                              nFrmWidth -= nAbsDiff;
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              if( bBigger )
//STRIP001                  aSz.SetWidth( aSz.GetWidth() + nRelDiff );
//STRIP001              else
//STRIP001                  aSz.SetWidth( aSz.GetWidth() - nRelDiff );
//STRIP001
//STRIP001              if( rSz.GetWidthPercent() )
//STRIP001                  aSz.SetWidthPercent( ( aSz.GetWidth() * 100 ) /
//STRIP001                      ( aSz.GetWidth() + aLR.GetRight() + aLR.GetLeft()));
//STRIP001
//STRIP001              GetFrmFmt()->SetAttr( aSz );
//STRIP001              aParam.nTblWidth = USHORT( aSz.GetWidth() );
//STRIP001
//STRIP001              UnlockModify();
//STRIP001
//STRIP001              for( n = aLines.Count(); n; )
//STRIP001              {
//STRIP001                  --n;
//STRIP001                  aParam.LoopClear();
//STRIP001                  (*fnSelBox)( aLines[ n ], aParam, nDistStt, FALSE );
//STRIP001              }
//STRIP001
//STRIP001              // sollte die Tabelle noch auf relativen Werten
//STRIP001              // (USHRT_MAX) stehen dann muss es jetzt auf absolute
//STRIP001              // umgerechnet werden. Bug 61494
//STRIP001              if( LONG_MAX != nFrmWidth )
//STRIP001              {
//STRIP001                  SwFmtFrmSize aAbsSz( aSz );
//STRIP001                  aAbsSz.SetWidth( nFrmWidth );
//STRIP001                  GetFrmFmt()->SetAttr( aAbsSz );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      else if( bInsDel ||
//STRIP001              ( bLeft ? nDist : Abs( rSz.GetWidth() - nDist ) > COLFUZZY ) )
//STRIP001      {
//STRIP001          bRet = TRUE;
//STRIP001          if( bLeft && TBLFIX_CHGABS == eTblChgMode && !bInsDel )
//STRIP001              aParam.bBigger = !bBigger;
//STRIP001
//STRIP001          // erstmal testen, ob ueberhaupt Platz ist
//STRIP001          if( bInsDel )
//STRIP001          {
//STRIP001              if( aParam.bBigger )
//STRIP001              {
//STRIP001                  for( n = 0; n < aLines.Count(); ++n )
//STRIP001                  {
//STRIP001                      aParam.LoopClear();
//STRIP001                      if( !(*fnSelBox)( aLines[ n ], aParam, nDistStt, TRUE ))
//STRIP001                      {
//STRIP001                          bRet = FALSE;
//STRIP001                          break;
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  if( 0 != ( bRet = bLeft ? nDist
//STRIP001                                          : ( rSz.GetWidth() - nDist )
//STRIP001                      > COLFUZZY ) )
//STRIP001                  {
//STRIP001                      for( n = 0; n < aLines.Count(); ++n )
//STRIP001                      {
//STRIP001                          aParam.LoopClear();
//STRIP001                          if( !(*fnOtherBox)( aLines[ n ], aParam, 0, TRUE ))
//STRIP001                          {
//STRIP001                              bRet = FALSE;
//STRIP001                              break;
//STRIP001                          }
//STRIP001                      }
//STRIP001                      if( bRet && !aParam.bAnyBoxFnd )
//STRIP001                          bRet = FALSE;
//STRIP001                  }
//STRIP001
//STRIP001                  if( !bRet && rAktBox.GetFrmFmt()->GetFrmSize().GetWidth()
//STRIP001                      - nRelDiff > COLFUZZY +
//STRIP001                          ( 567 / 2 /* min. 0,5 cm Platz lassen*/) )
//STRIP001                  {
//STRIP001                      // dann den Platz von der akt. Zelle nehmen
//STRIP001                      aParam.bSplittBox = TRUE;
//STRIP001                      // aber das muss auch mal getestet werden!
//STRIP001                      bRet = TRUE;
//STRIP001
//STRIP001                      for( n = 0; n < aLines.Count(); ++n )
//STRIP001                      {
//STRIP001                          aParam.LoopClear();
//STRIP001                          if( !(*fnSelBox)( aLines[ n ], aParam, nDistStt, TRUE ))
//STRIP001                          {
//STRIP001                              bRet = FALSE;
//STRIP001                              break;
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          else if( aParam.bBigger )
//STRIP001          {
//STRIP001              for( n = 0; n < aLines.Count(); ++n )
//STRIP001              {
//STRIP001                  aParam.LoopClear();
//STRIP001                  if( !(*fnOtherBox)( aLines[ n ], aParam, 0, TRUE ))
//STRIP001                  {
//STRIP001                      bRet = FALSE;
//STRIP001                      break;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              for( n = 0; n < aLines.Count(); ++n )
//STRIP001              {
//STRIP001                  aParam.LoopClear();
//STRIP001                  if( !(*fnSelBox)( aLines[ n ], aParam, nDistStt, TRUE ))
//STRIP001                  {
//STRIP001                      bRet = FALSE;
//STRIP001                      break;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          // wenn ja, dann setzen
//STRIP001          if( bRet )
//STRIP001          {
//STRIP001              CR_SetBoxWidth aParam1( aParam );
//STRIP001              if( bInsDel )
//STRIP001              {
//STRIP001                  aParam1.bBigger = !aParam.bBigger;
//STRIP001                  pFndBox = ::lcl_SaveInsDelData( aParam, ppUndo,
//STRIP001                                                  aTmpLst, nDistStt );
//STRIP001                  if( ppUndo )
//STRIP001                      *ppUndo = aParam.CreateUndo(
//STRIP001                                      aParam.bBigger ? UNDO_TABLE_DELBOX
//STRIP001                                                     : UNDO_TABLE_INSCOL );
//STRIP001              }
//STRIP001              else if( ppUndo )
//STRIP001                  *ppUndo = new SwUndoAttrTbl( *aParam.pTblNd, TRUE );
//STRIP001
//STRIP001              if( bInsDel
//STRIP001                  ? ( TBLFIX_CHGABS == eTblChgMode ? bLeft : bLeft )
//STRIP001                  : ( TBLFIX_CHGABS != eTblChgMode && bLeft ) )
//STRIP001              {
//STRIP001                  for( n = aLines.Count(); n; )
//STRIP001                  {
//STRIP001                      --n;
//STRIP001                      aParam.LoopClear();
//STRIP001                      aParam1.LoopClear();
//STRIP001                      (*fnSelBox)( aLines[ n ], aParam, nDistStt, FALSE );
//STRIP001                      (*fnOtherBox)( aLines[ n ], aParam1, nDistStt, FALSE );
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001                  for( n = aLines.Count(); n; )
//STRIP001                  {
//STRIP001                      --n;
//STRIP001                      aParam.LoopClear();
//STRIP001                      aParam1.LoopClear();
//STRIP001                      (*fnOtherBox)( aLines[ n ], aParam1, nDistStt, FALSE );
//STRIP001                      (*fnSelBox)( aLines[ n ], aParam, nDistStt, FALSE );
//STRIP001                  }
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  case WH_CELL_RIGHT:
//STRIP001  case WH_CELL_LEFT:
//STRIP001      if( TBLVAR_CHGABS == eTblChgMode )
//STRIP001      {
//STRIP001          // dann sich selbst rekursiv aufrufen; nur mit
//STRIP001          // einem anderen Mode -> Nachbarn
//STRIP001          TblChgMode eOld = eTblChgMode;
//STRIP001          eTblChgMode = TBLFIX_CHGABS;
//STRIP001
//STRIP001          bRet = SetColWidth( rAktBox, eType, nAbsDiff, nRelDiff,
//STRIP001                              ppUndo );
//STRIP001          eTblChgMode = eOld;
//STRIP001          return bRet;
//STRIP001      }
//STRIP001      else if( bInsDel || ( bLeft ? nDist
//STRIP001                                  : (rSz.GetWidth() - nDist) > COLFUZZY ))
//STRIP001      {
//STRIP001          if( bLeft && TBLFIX_CHGABS == eTblChgMode && !bInsDel )
//STRIP001              aParam.bBigger = !bBigger;
//STRIP001
//STRIP001          // erstmal testen, ob ueberhaupt Platz ist
//STRIP001          SwTableBox* pBox = &rAktBox;
//STRIP001          SwTableLine* pLine = rAktBox.GetUpper();
//STRIP001          while( pLine->GetUpper() )
//STRIP001          {
//STRIP001              USHORT nPos = pLine->GetTabBoxes().C40_GETPOS( SwTableBox, pBox );
//STRIP001              if( bLeft ? nPos : nPos + 1 != pLine->GetTabBoxes().Count() )
//STRIP001                  break;
//STRIP001
//STRIP001              pBox = pLine->GetUpper();
//STRIP001              pLine = pBox->GetUpper();
//STRIP001          }
//STRIP001
//STRIP001          if( pLine->GetUpper() )
//STRIP001          {
//STRIP001              // dann muss die Distanz wieder korriegiert werden!
//STRIP001              aParam.nSide -= ::lcl_GetDistance( pLine->GetUpper(), TRUE );
//STRIP001
//STRIP001              if( bLeft )
//STRIP001                  aParam.nMaxSize = aParam.nSide;
//STRIP001              else
//STRIP001                  aParam.nMaxSize = pLine->GetUpper()->GetFrmFmt()->
//STRIP001                                  GetFrmSize().GetWidth() - aParam.nSide;
//STRIP001          }
//STRIP001
//STRIP001          // erstmal testen, ob ueberhaupt Platz ist
//STRIP001          if( bInsDel )
//STRIP001          {
//STRIP001              if( 0 != ( bRet = bLeft ? nDist
//STRIP001                              : ( rSz.GetWidth() - nDist ) > COLFUZZY ) &&
//STRIP001                  !aParam.bBigger )
//STRIP001              {
//STRIP001                  bRet = (*fnOtherBox)( pLine, aParam, 0, TRUE );
//STRIP001                  if( bRet && !aParam.bAnyBoxFnd )
//STRIP001                      bRet = FALSE;
//STRIP001              }
//STRIP001
//STRIP001              if( !bRet && !aParam.bBigger && rAktBox.GetFrmFmt()->
//STRIP001                  GetFrmSize().GetWidth() - nRelDiff > COLFUZZY +
//STRIP001                      ( 567 / 2 /* min. 0,5 cm Platz lassen*/) )
//STRIP001              {
//STRIP001                  // dann den Platz von der akt. Zelle nehmen
//STRIP001                  aParam.bSplittBox = TRUE;
//STRIP001                  bRet = TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              FN_lcl_SetBoxWidth fnTmp = aParam.bBigger ? fnOtherBox : fnSelBox;
//STRIP001              bRet = (*fnTmp)( pLine, aParam, nDistStt, TRUE );
//STRIP001          }
//STRIP001
//STRIP001          // wenn ja, dann setzen
//STRIP001          if( bRet )
//STRIP001          {
//STRIP001              CR_SetBoxWidth aParam1( aParam );
//STRIP001              if( bInsDel )
//STRIP001              {
//STRIP001                  aParam1.bBigger = !aParam.bBigger;
//STRIP001                  pFndBox = ::lcl_SaveInsDelData( aParam, ppUndo, aTmpLst, nDistStt );
//STRIP001                  if( ppUndo )
//STRIP001                      *ppUndo = aParam.CreateUndo(
//STRIP001                                      aParam.bBigger ? UNDO_TABLE_DELBOX
//STRIP001                                                     : UNDO_TABLE_INSCOL );
//STRIP001              }
//STRIP001              else if( ppUndo )
//STRIP001                  *ppUndo = new SwUndoAttrTbl( *aParam.pTblNd, TRUE );
//STRIP001
//STRIP001              if( bInsDel
//STRIP001                  ? ( TBLFIX_CHGABS == eTblChgMode ? (bBigger && bLeft) : bLeft )
//STRIP001                  : ( TBLFIX_CHGABS != eTblChgMode && bLeft ) )
//STRIP001              {
//STRIP001                  (*fnSelBox)( pLine, aParam, nDistStt, FALSE );
//STRIP001                  (*fnOtherBox)( pLine, aParam1, nDistStt, FALSE );
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  (*fnOtherBox)( pLine, aParam1, nDistStt, FALSE );
//STRIP001                  (*fnSelBox)( pLine, aParam, nDistStt, FALSE );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001  }
//STRIP001
//STRIP001  if( pFndBox )
//STRIP001  {
//STRIP001      // dann raeume die Struktur aller Lines auf
//STRIP001      GCLines();
//STRIP001
//STRIP001      //Layout updaten
//STRIP001      if( !bBigger || pFndBox->AreLinesToRestore( *this ) )
//STRIP001          pFndBox->MakeFrms( *this );
//STRIP001      pFndBox->RestoreChartData( *this );
//STRIP001      delete pFndBox;
//STRIP001
//STRIP001      if( ppUndo && *ppUndo )
//STRIP001      {
//STRIP001          aParam.pUndo->SetColWidthParam( nBoxIdx, eTblChgMode, eType,
//STRIP001                                          nAbsDiff, nRelDiff );
//STRIP001          if( !aParam.bBigger )
//STRIP001              aParam.pUndo->SaveNewBoxes( *aParam.pTblNd, aTmpLst );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( bRet )
//STRIP001  {
//STRIP001      CHECKBOXWIDTH
//STRIP001         CHECKTABLELAYOUT
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
//STRIP001 }
#pragma optimize( "", on )

/*  */

//STRIP001 _FndBox* lcl_SaveInsDelData( CR_SetLineHeight& rParam, SwUndo** ppUndo,
//STRIP001                              SwTableSortBoxes& rTmpLst )
//STRIP001 {
//STRIP001  // suche alle Boxen / Lines
//STRIP001  SwTable& rTbl = rParam.pTblNd->GetTable();
//STRIP001
//STRIP001  ASSERT( rParam.aBoxes.Count(), "ohne Boxen ist nichts zu machen!" );
//STRIP001
//STRIP001  // loeschen der gesamten Tabelle verhindern
//STRIP001  if( !rParam.bBigger && rParam.aBoxes.Count() ==
//STRIP001      rTbl.GetTabSortBoxes().Count() )
//STRIP001      return 0;
//STRIP001
//STRIP001  _FndBox* pFndBox = new _FndBox( 0, 0 );
//STRIP001  if( !rParam.bBigger )
//STRIP001      pFndBox->SetTableLines( rParam.aBoxes, rTbl );
//STRIP001  else
//STRIP001  {
//STRIP001      _FndPara aPara( rParam.aBoxes, pFndBox );
//STRIP001      rTbl.GetTabLines().ForEach( &_FndLineCopyCol, &aPara );
//STRIP001      ASSERT( pFndBox->GetLines().Count(), "Wo sind die Boxen" );
//STRIP001      pFndBox->SetTableLines( rTbl );
//STRIP001
//STRIP001      if( ppUndo )
//STRIP001          rTmpLst.Insert( &rTbl.GetTabSortBoxes(), 0, rTbl.GetTabSortBoxes().Count() );
//STRIP001  }
//STRIP001
//STRIP001  //Lines fuer das Layout-Update heraussuchen.
//STRIP001  pFndBox->DelFrms( rTbl );
//STRIP001  pFndBox->SaveChartData( rTbl );
//STRIP001
//STRIP001  return pFndBox;
//STRIP001 }

//STRIP001 void SetLineHeight( SwTableLine& rLine, SwTwips nOldHeight, SwTwips nNewHeight,
//STRIP001                  BOOL bMinSize )
//STRIP001 {
//STRIP001  SwLayoutFrm* pLineFrm = GetRowFrm( rLine );
//STRIP001  ASSERT( pLineFrm, "wo ist der Frm von der SwTableLine?" );
//STRIP001
//STRIP001  SwFrmFmt* pFmt = rLine.ClaimFrmFmt();
//STRIP001
//STRIP001  SwTwips nMyNewH, nMyOldH = pLineFrm->Frm().Height();
//STRIP001  if( !nOldHeight )                       // die BaseLine und absolut
//STRIP001      nMyNewH = nMyOldH + nNewHeight;
//STRIP001  else
//STRIP001  {
//STRIP001      // moeglichst genau rechnen
//STRIP001      Fraction aTmp( nMyOldH );
//STRIP001      aTmp *= Fraction( nNewHeight, nOldHeight );
//STRIP001      aTmp += Fraction( 1, 2 );       // ggfs. aufrunden
//STRIP001      nMyNewH = aTmp;
//STRIP001  }
//STRIP001
//STRIP001  SwFrmSize eSize = ATT_MIN_SIZE;
//STRIP001  if( !bMinSize &&
//STRIP001      ( nMyOldH - nMyNewH ) > ( CalcRowRstHeight( pLineFrm ) + ROWFUZZY ))
//STRIP001      eSize = ATT_FIX_SIZE;
//STRIP001
//STRIP001  pFmt->SetAttr( SwFmtFrmSize( eSize, 0, nMyNewH ) );
//STRIP001
//STRIP001  // erst alle inneren anpassen
//STRIP001  SwTableBoxes& rBoxes = rLine.GetTabBoxes();
//STRIP001  for( USHORT n = 0; n < rBoxes.Count(); ++n )
//STRIP001  {
//STRIP001      SwTableBox& rBox = *rBoxes[ n ];
//STRIP001      for( USHORT i = 0; i < rBox.GetTabLines().Count(); ++i )
//STRIP001          SetLineHeight( *rBox.GetTabLines()[ i ], nMyOldH, nMyNewH, bMinSize );
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL lcl_SetSelLineHeight( SwTableLine* pLine, CR_SetLineHeight& rParam,
//STRIP001                           SwTwips nDist, BOOL bCheck )
//STRIP001 {
//STRIP001  BOOL bRet = TRUE;
//STRIP001  if( !bCheck )
//STRIP001  {
//STRIP001      // Zeilenhoehe einstellen
//STRIP001      SetLineHeight( *pLine, 0, rParam.bBigger ? nDist : -nDist,
//STRIP001                      rParam.bBigger );
//STRIP001  }
//STRIP001  else if( !rParam.bBigger )
//STRIP001  {
//STRIP001      // anhand der alten Size die neue relative errechnen
//STRIP001      SwLayoutFrm* pLineFrm = GetRowFrm( *pLine );
//STRIP001      ASSERT( pLineFrm, "wo ist der Frm von der SwTableLine?" );
//STRIP001      SwTwips nRstHeight = CalcRowRstHeight( pLineFrm );
//STRIP001      if( (nRstHeight + ROWFUZZY) < nDist )
//STRIP001          bRet = FALSE;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL lcl_SetOtherLineHeight( SwTableLine* pLine, CR_SetLineHeight& rParam,
//STRIP001                              SwTwips nDist, BOOL bCheck )
//STRIP001 {
//STRIP001  BOOL bRet = TRUE;
//STRIP001  if( bCheck )
//STRIP001  {
//STRIP001      if( rParam.bBigger )
//STRIP001      {
//STRIP001          // anhand der alten Size die neue relative errechnen
//STRIP001          SwLayoutFrm* pLineFrm = GetRowFrm( *pLine );
//STRIP001          ASSERT( pLineFrm, "wo ist der Frm von der SwTableLine?" );
//STRIP001
//STRIP001          if( TBLFIX_CHGPROP == rParam.nMode )
//STRIP001          {
//STRIP001              nDist *= pLineFrm->Frm().Height();
//STRIP001              nDist /= rParam.nMaxHeight;
//STRIP001          }
//STRIP001          bRet = nDist <= CalcRowRstHeight( pLineFrm );
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // Zeilenhoehe einstellen
//STRIP001      // pLine ist die nachfolgende / vorhergehende -> also anpassen
//STRIP001      if( TBLFIX_CHGPROP == rParam.nMode )
//STRIP001      {
//STRIP001          SwLayoutFrm* pLineFrm = GetRowFrm( *pLine );
//STRIP001          ASSERT( pLineFrm, "wo ist der Frm von der SwTableLine?" );
//STRIP001
//STRIP001          // aus der alten Size die neue relative errechnen
//STRIP001          // Wird die selektierte Box groesser ueber den MaxSpace anpassen,
//STRIP001          // sonst ueber die MaxHeight
//STRIP001          if( 1 /*!rParam.bBigger*/ )
//STRIP001          {
//STRIP001              nDist *= pLineFrm->Frm().Height();
//STRIP001              nDist /= rParam.nMaxHeight;
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              // aus der alten Size die neue relative errechnen
//STRIP001              nDist *= CalcRowRstHeight( pLineFrm );
//STRIP001              nDist /= rParam.nMaxSpace;
//STRIP001          }
//STRIP001      }
//STRIP001      SetLineHeight( *pLine, 0, rParam.bBigger ? -nDist : nDist,
//STRIP001                      !rParam.bBigger );
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL lcl_InsDelSelLine( SwTableLine* pLine, CR_SetLineHeight& rParam,
//STRIP001                          SwTwips nDist, BOOL bCheck )
//STRIP001 {
//STRIP001  BOOL bRet = TRUE;
//STRIP001  if( !bCheck )
//STRIP001  {
//STRIP001      SwTableBoxes& rBoxes = pLine->GetTabBoxes();
//STRIP001      SwDoc* pDoc = pLine->GetFrmFmt()->GetDoc();
//STRIP001      if( !rParam.bBigger )
//STRIP001      {
//STRIP001          for( USHORT n = rBoxes.Count(); n; )
//STRIP001              ::lcl_SaveUpperLowerBorder( rParam.pTblNd->GetTable(),
//STRIP001                                                  *rBoxes[ --n ],
//STRIP001                                                  rParam.aShareFmts );
//STRIP001          for( n = rBoxes.Count(); n; )
//STRIP001              ::_DeleteBox( rParam.pTblNd->GetTable(),
//STRIP001                                  rBoxes[ --n ], rParam.pUndo, FALSE,
//STRIP001                                  FALSE, &rParam.aShareFmts );
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // Zeile einfuegen
//STRIP001          SwTableLine* pNewLine = new SwTableLine( (SwTableLineFmt*)pLine->GetFrmFmt(),
//STRIP001                                      rBoxes.Count(), pLine->GetUpper() );
//STRIP001          SwTableLines* pLines;
//STRIP001          if( pLine->GetUpper() )
//STRIP001              pLines = &pLine->GetUpper()->GetTabLines();
//STRIP001          else
//STRIP001              pLines = &rParam.pTblNd->GetTable().GetTabLines();
//STRIP001          USHORT nPos = pLines->C40_GETPOS( SwTableLine, pLine );
//STRIP001          if( !rParam.bTop )
//STRIP001              ++nPos;
//STRIP001          pLines->C40_INSERT( SwTableLine, pNewLine, nPos );
//STRIP001
//STRIP001          SwFrmFmt* pNewFmt = pNewLine->ClaimFrmFmt();
//STRIP001          pNewFmt->SetAttr( SwFmtFrmSize( ATT_MIN_SIZE, 0, nDist ) );
//STRIP001
//STRIP001          // und noch mal die Anzahl Boxen erzeugen
//STRIP001          SwTableBoxes& rNewBoxes = pNewLine->GetTabBoxes();
//STRIP001          for( USHORT n = 0; n < rBoxes.Count(); ++n )
//STRIP001          {
//STRIP001              SwTwips nWidth = 0;
//STRIP001              SwTableBox* pOld = rBoxes[ n ];
//STRIP001              if( !pOld->GetSttNd() )
//STRIP001              {
//STRIP001                  // keine normale "Content"-Box also auf die 1. naechste
//STRIP001                  // Box zurueckfallen
//STRIP001                  nWidth = pOld->GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001                  while( !pOld->GetSttNd() )
//STRIP001                      pOld = pOld->GetTabLines()[ 0 ]->GetTabBoxes()[ 0 ];
//STRIP001              }
//STRIP001              ::_InsTblBox( pDoc, rParam.pTblNd, pNewLine,
//STRIP001                                  (SwTableBoxFmt*)pOld->GetFrmFmt(), pOld, n );
//STRIP001
//STRIP001              // Sonderbehandlung fuer Umrandung die Obere muss
//STRIP001              // entfernt werden
//STRIP001              const SvxBoxItem& rBoxItem = pOld->GetFrmFmt()->GetBox();
//STRIP001              if( rBoxItem.GetTop() )
//STRIP001              {
//STRIP001                  SvxBoxItem aTmp( rBoxItem );
//STRIP001                  aTmp.SetLine( 0, BOX_LINE_TOP );
//STRIP001                  rParam.aShareFmts.SetAttr( rParam.bTop
//STRIP001                                              ? *pOld
//STRIP001                                              : *rNewBoxes[ n ], aTmp );
//STRIP001              }
//STRIP001
//STRIP001              if( nWidth )
//STRIP001                  rParam.aShareFmts.SetAttr( *rNewBoxes[ n ],
//STRIP001                              SwFmtFrmSize( ATT_FIX_SIZE, nWidth, 0 ) );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // Boxen einsammeln!
//STRIP001      SwTableBoxes& rBoxes = pLine->GetTabBoxes();
//STRIP001      for( USHORT n = rBoxes.Count(); n; )
//STRIP001      {
//STRIP001          SwTableBox* pBox = rBoxes[ --n ];
//STRIP001          if( pBox->GetFrmFmt()->GetProtect().IsCntntProtected() )
//STRIP001              return FALSE;
//STRIP001
//STRIP001          if( pBox->GetSttNd() )
//STRIP001              rParam.aBoxes.Insert( pBox );
//STRIP001          else
//STRIP001          {
//STRIP001              for( USHORT i = pBox->GetTabLines().Count(); i; )
//STRIP001                  lcl_InsDelSelLine( pBox->GetTabLines()[ --i ],
//STRIP001                                      rParam, 0, TRUE );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SwTable::SetRowHeight( SwTableBox& rAktBox, USHORT eType,
//STRIP001                      SwTwips nAbsDiff, SwTwips nRelDiff,SwUndo** ppUndo )
//STRIP001 {
//STRIP001  SwTableLine* pLine = rAktBox.GetUpper();
//STRIP001
//STRIP001  SwTableLine* pBaseLine = pLine;
//STRIP001  while( pBaseLine->GetUpper() )
//STRIP001      pBaseLine = pBaseLine->GetUpper()->GetUpper();
//STRIP001
//STRIP001  _FndBox* pFndBox = 0;                   // fuers Einfuegen/Loeschen
//STRIP001  SwTableSortBoxes aTmpLst( 0, 5 );       // fuers Undo
//STRIP001  BOOL bBigger,
//STRIP001      bRet = FALSE,
//STRIP001      bTop = WH_ROW_TOP == ( eType & 0xff ) ||
//STRIP001              WH_CELL_TOP == ( eType & 0xff ),
//STRIP001      bInsDel = 0 != (eType & WH_FLAG_INSDEL );
//STRIP001  USHORT n, nBaseLinePos = GetTabLines().C40_GETPOS( SwTableLine, pBaseLine );
//STRIP001  ULONG nBoxIdx = rAktBox.GetSttIdx();
//STRIP001
//STRIP001  CR_SetLineHeight aParam( eType,
//STRIP001                      (SwTableNode*)rAktBox.GetSttNd()->FindTableNode() );
//STRIP001  bBigger = aParam.bBigger;
//STRIP001
//STRIP001  FN_lcl_SetLineHeight fnSelLine, fnOtherLine = lcl_SetOtherLineHeight;
//STRIP001  if( bInsDel )
//STRIP001      fnSelLine = lcl_InsDelSelLine;
//STRIP001  else
//STRIP001      fnSelLine = lcl_SetSelLineHeight;
//STRIP001
//STRIP001  SwTableLines* pLines = &aLines;
//STRIP001
//STRIP001  // wie kommt man an die Hoehen heran?
//STRIP001  switch( eType & 0xff )
//STRIP001  {
//STRIP001  case WH_CELL_TOP:
//STRIP001  case WH_CELL_BOTTOM:
//STRIP001      if( pLine == pBaseLine )
//STRIP001          break;  // dann geht es nicht!
//STRIP001
//STRIP001      // ist eine verschachtelte Line (Box!)
//STRIP001      pLines = &pLine->GetUpper()->GetTabLines();
//STRIP001      nBaseLinePos = pLines->C40_GETPOS( SwTableLine, pLine );
//STRIP001      pBaseLine = pLine;
//STRIP001      // kein break!
//STRIP001
//STRIP001  case WH_ROW_TOP:
//STRIP001  case WH_ROW_BOTTOM:
//STRIP001      {
//STRIP001          if( bInsDel && !bBigger )       // um wieviel wird es Hoeher?
//STRIP001          {
//STRIP001              nAbsDiff = GetRowFrm( *pBaseLine )->Frm().Height();
//STRIP001          }
//STRIP001
//STRIP001          if( TBLVAR_CHGABS == eTblChgMode )
//STRIP001          {
//STRIP001              // erstmal testen, ob ueberhaupt Platz ist
//STRIP001              if( bBigger )
//STRIP001              {
//STRIP001                  bRet = TRUE;
//STRIP001 // was ist mit Top, was ist mit Tabelle im Rahmen oder in Kopf-/Fusszeile
//STRIP001 // mit fester Hoehe ??
//STRIP001                  if( !bRet )
//STRIP001                  {
//STRIP001                      // dann sich selbst rekursiv aufrufen; nur mit
//STRIP001                      // einem anderen Mode -> proprotional
//STRIP001                      TblChgMode eOld = eTblChgMode;
//STRIP001                      eTblChgMode = TBLFIX_CHGPROP;
//STRIP001
//STRIP001                      bRet = SetRowHeight( rAktBox, eType, nAbsDiff,
//STRIP001                                          nRelDiff, ppUndo );
//STRIP001
//STRIP001                      eTblChgMode = eOld;
//STRIP001                      return bRet;
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001                  bRet = (*fnSelLine)( (*pLines)[ nBaseLinePos ], aParam,
//STRIP001                                      nAbsDiff, TRUE );
//STRIP001
//STRIP001              if( bRet )
//STRIP001              {
//STRIP001                  if( bInsDel )
//STRIP001                  {
//STRIP001                      if( !aParam.aBoxes.Count() )
//STRIP001                          ::lcl_InsDelSelLine( (*pLines)[ nBaseLinePos ],
//STRIP001                                                  aParam, 0, TRUE );
//STRIP001
//STRIP001                      pFndBox = ::lcl_SaveInsDelData( aParam, ppUndo, aTmpLst );
//STRIP001
//STRIP001                         // #110525# delete complete table when last row is
//STRIP001                         // deleted
//STRIP001                         if( !bBigger &&
//STRIP001                             aParam.aBoxes.Count() == aSortCntBoxes.Count() )
//STRIP001                         {
//STRIP001                             GetFrmFmt()->GetDoc()->DeleteRowCol( aParam.aBoxes );
//STRIP001                             return FALSE;
//STRIP001                         }
//STRIP001
//STRIP001
//STRIP001                      if( ppUndo )
//STRIP001                          *ppUndo = aParam.CreateUndo(
//STRIP001                                      bBigger ? UNDO_TABLE_INSROW
//STRIP001                                              : UNDO_TABLE_DELBOX );
//STRIP001                  }
//STRIP001                  else if( ppUndo )
//STRIP001                      *ppUndo = new SwUndoAttrTbl( *aParam.pTblNd, TRUE );
//STRIP001
//STRIP001                  (*fnSelLine)( (*pLines)[ nBaseLinePos ], aParam,
//STRIP001                                  nAbsDiff, FALSE );
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              bRet = TRUE;
//STRIP001              USHORT nStt, nEnd;
//STRIP001              if( bTop )
//STRIP001                  nStt = 0, nEnd = nBaseLinePos;
//STRIP001              else
//STRIP001                  nStt = nBaseLinePos + 1, nEnd = pLines->Count();
//STRIP001
//STRIP001              // die akt. Hoehe der Lines besorgen
//STRIP001              if( TBLFIX_CHGPROP == eTblChgMode )
//STRIP001              {
//STRIP001                  for( n = nStt; n < nEnd; ++n )
//STRIP001                  {
//STRIP001                      SwLayoutFrm* pLineFrm = GetRowFrm( *(*pLines)[ n ] );
//STRIP001                      ASSERT( pLineFrm, "wo ist der Frm von der SwTableLine?" );
//STRIP001                      aParam.nMaxSpace += CalcRowRstHeight( pLineFrm );
//STRIP001                      aParam.nMaxHeight += pLineFrm->Frm().Height();
//STRIP001                  }
//STRIP001                  if( bBigger && aParam.nMaxSpace < nAbsDiff )
//STRIP001                      bRet = FALSE;
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  if( bTop ? nEnd : nStt < nEnd  )
//STRIP001                  {
//STRIP001                      if( bTop )
//STRIP001                          nStt = nEnd - 1;
//STRIP001                      else
//STRIP001                          nEnd = nStt + 1;
//STRIP001                  }
//STRIP001                  else
//STRIP001                      bRet = FALSE;
//STRIP001              }
//STRIP001
//STRIP001              if( bRet )
//STRIP001              {
//STRIP001                  if( bBigger )
//STRIP001                  {
//STRIP001                      for( n = nStt; n < nEnd; ++n )
//STRIP001                      {
//STRIP001                          if( !(*fnOtherLine)( (*pLines)[ n ], aParam,
//STRIP001                                                  nAbsDiff, TRUE ))
//STRIP001                          {
//STRIP001                              bRet = FALSE;
//STRIP001                              break;
//STRIP001                          }
//STRIP001                      }
//STRIP001                  }
//STRIP001                  else
//STRIP001                      bRet = (*fnSelLine)( (*pLines)[ nBaseLinePos ], aParam,
//STRIP001                                              nAbsDiff, TRUE );
//STRIP001              }
//STRIP001
//STRIP001              if( bRet )
//STRIP001              {
//STRIP001                  // dann mal anpassen
//STRIP001                  if( bInsDel )
//STRIP001                  {
//STRIP001                      if( !aParam.aBoxes.Count() )
//STRIP001                          ::lcl_InsDelSelLine( (*pLines)[ nBaseLinePos ],
//STRIP001                                                  aParam, 0, TRUE );
//STRIP001                      pFndBox = ::lcl_SaveInsDelData( aParam, ppUndo, aTmpLst );
//STRIP001                      if( ppUndo )
//STRIP001                          *ppUndo = aParam.CreateUndo(
//STRIP001                                      bBigger ? UNDO_TABLE_INSROW
//STRIP001                                              : UNDO_TABLE_DELBOX );
//STRIP001                  }
//STRIP001                  else if( ppUndo )
//STRIP001                      *ppUndo = new SwUndoAttrTbl( *aParam.pTblNd, TRUE );
//STRIP001
//STRIP001                  CR_SetLineHeight aParam1( aParam );
//STRIP001                  if( TBLFIX_CHGPROP == eTblChgMode && !bBigger &&
//STRIP001                      !aParam.nMaxSpace )
//STRIP001                  {
//STRIP001                      // dann muss der gesamte Platz auf alle Lines
//STRIP001                      // gleichmaessig verteilt werden. Dafuer wird die
//STRIP001                      // Anzahl benoetigt
//STRIP001                      aParam1.nLines = nEnd - nStt;
//STRIP001                  }
//STRIP001
//STRIP001                  if( bTop )
//STRIP001                  {
//STRIP001                      (*fnSelLine)( (*pLines)[ nBaseLinePos ], aParam,
//STRIP001                                      nAbsDiff, FALSE );
//STRIP001                      for( n = nStt; n < nEnd; ++n )
//STRIP001                          (*fnOtherLine)( (*pLines)[ n ], aParam1,
//STRIP001                                          nAbsDiff, FALSE );
//STRIP001                  }
//STRIP001                  else
//STRIP001                  {
//STRIP001                      for( n = nStt; n < nEnd; ++n )
//STRIP001                          (*fnOtherLine)( (*pLines)[ n ], aParam1,
//STRIP001                                          nAbsDiff, FALSE );
//STRIP001                      (*fnSelLine)( (*pLines)[ nBaseLinePos ], aParam,
//STRIP001                                      nAbsDiff, FALSE );
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  // dann sich selbst rekursiv aufrufen; nur mit
//STRIP001                  // einem anderen Mode -> proprotional
//STRIP001                  TblChgMode eOld = eTblChgMode;
//STRIP001                  eTblChgMode = TBLVAR_CHGABS;
//STRIP001
//STRIP001                  bRet = SetRowHeight( rAktBox, eType, nAbsDiff,
//STRIP001                                      nRelDiff, ppUndo );
//STRIP001
//STRIP001                  eTblChgMode = eOld;
//STRIP001                  pFndBox = 0;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      break;
//STRIP001  }
//STRIP001
//STRIP001  if( pFndBox )
//STRIP001  {
//STRIP001      // dann raeume die Struktur aller Lines auf
//STRIP001      GCLines();
//STRIP001
//STRIP001      //Layout updaten
//STRIP001      if( bBigger || pFndBox->AreLinesToRestore( *this ) )
//STRIP001          pFndBox->MakeFrms( *this );
//STRIP001      pFndBox->RestoreChartData( *this );
//STRIP001      delete pFndBox;
//STRIP001
//STRIP001      if( ppUndo && *ppUndo )
//STRIP001      {
//STRIP001          aParam.pUndo->SetColWidthParam( nBoxIdx, eTblChgMode, eType,
//STRIP001                                          nAbsDiff, nRelDiff );
//STRIP001          if( bBigger )
//STRIP001              aParam.pUndo->SaveNewBoxes( *aParam.pTblNd, aTmpLst );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001     CHECKTABLELAYOUT
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

/*  */

//STRIP001 SwFrmFmt* SwShareBoxFmt::GetFormat( long nWidth ) const
//STRIP001 {
//STRIP001  SwFrmFmt *pRet = 0, *pTmp;
//STRIP001  for( USHORT n = aNewFmts.Count(); n; )
//STRIP001      if( ( pTmp = (SwFrmFmt*)aNewFmts[ --n ])->GetFrmSize().GetWidth()
//STRIP001              == nWidth )
//STRIP001      {
//STRIP001          pRet = pTmp;
//STRIP001          break;
//STRIP001      }
//STRIP001  return pRet;
//STRIP001 }

//STRIP001 SwFrmFmt* SwShareBoxFmt::GetFormat( const SfxPoolItem& rItem ) const
//STRIP001 {
//STRIP001  const SfxPoolItem* pItem;
//STRIP001  USHORT nWhich = rItem.Which();
//STRIP001  SwFrmFmt *pRet = 0, *pTmp;
//STRIP001  const SfxPoolItem& rFrmSz = pOldFmt->GetAttr( RES_FRM_SIZE, FALSE );
//STRIP001  for( USHORT n = aNewFmts.Count(); n; )
//STRIP001      if( SFX_ITEM_SET == ( pTmp = (SwFrmFmt*)aNewFmts[ --n ])->
//STRIP001          GetItemState( nWhich, FALSE, &pItem ) && *pItem == rItem &&
//STRIP001          pTmp->GetAttr( RES_FRM_SIZE, FALSE ) == rFrmSz )
//STRIP001      {
//STRIP001          pRet = pTmp;
//STRIP001          break;
//STRIP001      }
//STRIP001  return pRet;
//STRIP001 }

//STRIP001 void SwShareBoxFmt::AddFormat( const SwFrmFmt& rNew )
//STRIP001 {
//STRIP001  void* pFmt = (void*)&rNew;
//STRIP001  aNewFmts.Insert( pFmt, aNewFmts.Count() );
//STRIP001 }

//STRIP001 FASTBOOL SwShareBoxFmt::RemoveFormat( const SwFrmFmt& rFmt )
//STRIP001 {
//STRIP001  // returnt TRUE, wenn geloescht werden kann
//STRIP001  if( pOldFmt == &rFmt )
//STRIP001      return TRUE;
//STRIP001
//STRIP001  void* p = (void*)&rFmt;
//STRIP001  USHORT nFnd = aNewFmts.GetPos( p );
//STRIP001  if( USHRT_MAX != nFnd )
//STRIP001      aNewFmts.Remove( nFnd );
//STRIP001  return 0 == aNewFmts.Count();
//STRIP001 }

/*N*/ SwShareBoxFmts::~SwShareBoxFmts()
/*N*/ {
/*N*/ }

//STRIP001 SwFrmFmt* SwShareBoxFmts::GetFormat( const SwFrmFmt& rFmt, long nWidth ) const
//STRIP001 {
//STRIP001  USHORT nPos;
//STRIP001  return Seek_Entry( rFmt, &nPos )
//STRIP001                  ? aShareArr[ nPos ]->GetFormat( nWidth )
//STRIP001                  : 0;
//STRIP001 }
//STRIP001 SwFrmFmt* SwShareBoxFmts::GetFormat( const SwFrmFmt& rFmt,
//STRIP001                                   const SfxPoolItem& rItem ) const
//STRIP001 {
//STRIP001  USHORT nPos;
//STRIP001  return Seek_Entry( rFmt, &nPos )
//STRIP001                  ? aShareArr[ nPos ]->GetFormat( rItem )
//STRIP001                  : 0;
//STRIP001 }

//STRIP001 void SwShareBoxFmts::AddFormat( const SwFrmFmt& rOld, const SwFrmFmt& rNew )
//STRIP001 {
//STRIP001  // wenn das Format nicht geshared ist, braucht es auch nicht in die
//STRIP001  // Liste aufgenommen werden. Denn es gibt keinen 2. der es sucht.
//STRIP001 //leider werden auch die CellFrms gefunden
//STRIP001 //   if( !rOld.IsLastDepend() )
//STRIP001  {
//STRIP001      USHORT nPos;
//STRIP001      SwShareBoxFmt* pEntry;
//STRIP001      if( !Seek_Entry( rOld, &nPos ))
//STRIP001      {
//STRIP001          pEntry = new SwShareBoxFmt( rOld );
//STRIP001          aShareArr.C40_INSERT( SwShareBoxFmt, pEntry, nPos );
//STRIP001      }
//STRIP001      else
//STRIP001          pEntry = aShareArr[ nPos ];
//STRIP001
//STRIP001      pEntry->AddFormat( rNew );
//STRIP001  }
//STRIP001 }
//STRIP001 void SwShareBoxFmts::ChangeFrmFmt( SwTableBox* pBox, SwTableLine* pLn,
//STRIP001                                  SwFrmFmt& rFmt )
//STRIP001 {
//STRIP001  SwClient aCl;
//STRIP001  SwFrmFmt* pOld = 0;
//STRIP001  if( pBox )
//STRIP001  {
//STRIP001      pOld = pBox->GetFrmFmt();
//STRIP001      pOld->Add( &aCl );
//STRIP001      pBox->ChgFrmFmt( (SwTableBoxFmt*)&rFmt );
//STRIP001  }
//STRIP001  else if( pLn )
//STRIP001  {
//STRIP001      pOld = pLn->GetFrmFmt();
//STRIP001      pOld->Add( &aCl );
//STRIP001      pLn->ChgFrmFmt( (SwTableLineFmt*)&rFmt );
//STRIP001  }
//STRIP001  if( pOld && pOld->IsLastDepend() )
//STRIP001  {
//STRIP001      RemoveFormat( *pOld );
//STRIP001      delete pOld;
//STRIP001  }
//STRIP001 }

//STRIP001 void SwShareBoxFmts::SetSize( SwTableBox& rBox, const SwFmtFrmSize& rSz )
//STRIP001 {
//STRIP001  SwFrmFmt *pBoxFmt = rBox.GetFrmFmt(),
//STRIP001           *pRet = GetFormat( *pBoxFmt, rSz.GetWidth() );
//STRIP001  if( pRet )
//STRIP001      ChangeFrmFmt( &rBox, 0, *pRet );
//STRIP001  else
//STRIP001  {
//STRIP001      pRet = rBox.ClaimFrmFmt();
//STRIP001      pRet->SetAttr( rSz );
//STRIP001      AddFormat( *pBoxFmt, *pRet );
//STRIP001  }
//STRIP001 }

//STRIP001 void SwShareBoxFmts::SetAttr( SwTableBox& rBox, const SfxPoolItem& rItem )
//STRIP001 {
//STRIP001  SwFrmFmt *pBoxFmt = rBox.GetFrmFmt(),
//STRIP001           *pRet = GetFormat( *pBoxFmt, rItem );
//STRIP001  if( pRet )
//STRIP001      ChangeFrmFmt( &rBox, 0, *pRet );
//STRIP001  else
//STRIP001  {
//STRIP001      pRet = rBox.ClaimFrmFmt();
//STRIP001      pRet->SetAttr( rItem );
//STRIP001      AddFormat( *pBoxFmt, *pRet );
//STRIP001  }
//STRIP001 }

//STRIP001 void SwShareBoxFmts::SetAttr( SwTableLine& rLine, const SfxPoolItem& rItem )
//STRIP001 {
//STRIP001  SwFrmFmt *pLineFmt = rLine.GetFrmFmt(),
//STRIP001           *pRet = GetFormat( *pLineFmt, rItem );
//STRIP001  if( pRet )
//STRIP001      ChangeFrmFmt( 0, &rLine, *pRet );
//STRIP001  else
//STRIP001  {
//STRIP001      pRet = rLine.ClaimFrmFmt();
//STRIP001      pRet->SetAttr( rItem );
//STRIP001      AddFormat( *pLineFmt, *pRet );
//STRIP001  }
//STRIP001 }

//STRIP001 void SwShareBoxFmts::RemoveFormat( const SwFrmFmt& rFmt )
//STRIP001 {
//STRIP001  for( USHORT i = aShareArr.Count(); i; )
//STRIP001      if( aShareArr[ --i ]->RemoveFormat( rFmt ))
//STRIP001          aShareArr.DeleteAndDestroy( i );
//STRIP001 }

//STRIP001 BOOL SwShareBoxFmts::Seek_Entry( const SwFrmFmt& rFmt, USHORT* pPos ) const
//STRIP001 {
//STRIP001  ULONG nIdx = (ULONG)&rFmt;
//STRIP001  register USHORT nO = aShareArr.Count(), nM, nU = 0;
//STRIP001  if( nO > 0 )
//STRIP001  {
//STRIP001      nO--;
//STRIP001      while( nU <= nO )
//STRIP001      {
//STRIP001          nM = nU + ( nO - nU ) / 2;
//STRIP001          ULONG nFmt = (ULONG)&aShareArr[ nM ]->GetOldFormat();
//STRIP001          if( nFmt == nIdx )
//STRIP001          {
//STRIP001              if( pPos )
//STRIP001                  *pPos = nM;
//STRIP001              return TRUE;
//STRIP001          }
//STRIP001          else if( nFmt < nIdx )
//STRIP001              nU = nM + 1;
//STRIP001          else if( nM == 0 )
//STRIP001          {
//STRIP001              if( pPos )
//STRIP001                  *pPos = nU;
//STRIP001              return FALSE;
//STRIP001          }
//STRIP001          else
//STRIP001              nO = nM - 1;
//STRIP001      }
//STRIP001  }
//STRIP001  if( pPos )
//STRIP001      *pPos = nU;
//STRIP001  return FALSE;
//STRIP001 }


}
