/*************************************************************************
 *
 *  $RCSfile: sw_swtable.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:13:09 $
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

#ifdef WTC
#define private public
#endif

#include <ctype.h>
#include <float.h>

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif
#ifndef _HINTS_HXX
#include <hints.hxx>    // fuer SwAttrSetChg
#endif

// auto strip #ifndef _SVX_LRSPITEM_HXX //autogen
// auto strip #include <bf_svx/lrspitem.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_SHADITEM_HXX //autogen
// auto strip #include <bf_svx/shaditem.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_ADJITEM_HXX //autogen
// auto strip #include <bf_svx/adjitem.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_COLRITEM_HXX //autogen
// auto strip #include <bf_svx/colritem.hxx>
// auto strip #endif
#ifndef _SVXLINKMGR_HXX
#include <bf_svx/linkmgr.hxx>
#endif
// auto strip #ifndef _SVX_BOXITEM_HXX //autogen
// auto strip #include <bf_svx/boxitem.hxx>
// auto strip #endif


#ifndef _FMTFSIZE_HXX //autogen
#include <fmtfsize.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif
// auto strip #ifndef _ERRHDL_HXX
// auto strip #include <errhdl.hxx>
// auto strip #endif

// auto strip #ifndef _FMTORNT_HXX //autogen
// auto strip #include <fmtornt.hxx>
// auto strip #endif
// auto strip #ifndef _FMTPDSC_HXX //autogen
// auto strip #include <fmtpdsc.hxx>
// auto strip #endif
// auto strip #ifndef _FRMATR_HXX
// auto strip #include <frmatr.hxx>
// auto strip #endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
// auto strip #ifndef _DOCARY_HXX
// auto strip #include <docary.hxx>     // fuer RedlineTbl()
// auto strip #endif
#ifndef _FRAME_HXX
#include <frame.hxx>
#endif
// auto strip #ifndef _SWTABLE_HXX
// auto strip #include <swtable.hxx>
// auto strip #endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
// auto strip #ifndef _TABCOL_HXX
// auto strip #include <tabcol.hxx>
// auto strip #endif
// auto strip #ifndef _TABFRM_HXX
// auto strip #include <tabfrm.hxx>
// auto strip #endif
#ifndef _CELLFRM_HXX
#include <cellfrm.hxx>
#endif
#ifndef _ROWFRM_HXX
#include <rowfrm.hxx>
#endif
#ifndef _SWSERV_HXX
#include <swserv.hxx>
#endif
// auto strip #ifndef _EXPFLD_HXX
// auto strip #include <expfld.hxx>
// auto strip #endif
#ifndef _MDIEXP_HXX
#include <mdiexp.hxx>
#endif
#ifndef _CELLATR_HXX
#include <cellatr.hxx>
#endif
#ifndef _TXATBASE_HXX
#include <txatbase.hxx>
#endif
#ifndef _HTMLTBL_HXX
#include <htmltbl.hxx>
#endif
#ifndef _SWTBLFMT_HXX
#include <swtblfmt.hxx>
#endif
// auto strip #ifndef _NDINDEX_HXX
// auto strip #include <ndindex.hxx>
// auto strip #endif
#ifndef _TBLRWCL_HXX
#include <tblrwcl.hxx>
#endif
// auto strip #ifndef _SHELLRES_HXX
// auto strip #include <shellres.hxx>
// auto strip #endif
// auto strip #ifndef _VIEWSH_HXX
// auto strip #include <viewsh.hxx>
// auto strip #endif
#ifndef _REDLINE_HXX
#include <redline.hxx>
#endif
namespace binfilter {

/*N*/ TYPEINIT1( SwTable, SwClient );
/*N*/ TYPEINIT1( SwTableBox, SwClient );
/*N*/ TYPEINIT1( SwTableLine, SwClient );
/*N*/ TYPEINIT1( SwTableFmt, SwFrmFmt );
/*N*/ TYPEINIT1( SwTableBoxFmt, SwFrmFmt );
/*N*/ TYPEINIT1( SwTableLineFmt, SwFrmFmt );

/*N*/ SV_IMPL_PTRARR(SwTableLines,SwTableLine*);
/*N*/ SV_IMPL_PTRARR(SwTableBoxes,SwTableBox*);
/*N*/ SV_IMPL_PTRARR_SORT(SwTableSortBoxes,SwTableBoxPtr);

/*N*/ SV_IMPL_REF( SwServerObject )

#define COLFUZZY 20

//----------------------------------

/*N*/ class SwTableBox_Impl
/*N*/ {
/*N*/   Color *pUserColor, *pNumFmtColor;
/*N*/
/*N*/   void SetNewCol( Color** ppCol, const Color* pNewCol );
/*N*/ public:
/*N*/   SwTableBox_Impl() : pUserColor(0), pNumFmtColor(0) {}
/*N*/   ~SwTableBox_Impl() { delete pUserColor; delete pNumFmtColor; }
/*N*/
/*N*/   const Color* GetSaveUserColor() const       { return pUserColor; }
/*N*/   const Color* GetSaveNumFmtColor() const     { return pNumFmtColor; }
/*N*/   void SetSaveUserColor(const Color* p )      { SetNewCol( &pUserColor, p ); }
/*N*/   void SetSaveNumFmtColor( const Color* p )   { SetNewCol( &pNumFmtColor, p ); }
/*N*/ };

// ----------- Inlines -----------------------------

//STRIP001 inline const Color* SwTableBox::GetSaveUserColor() const
//STRIP001 {
//STRIP001  return pImpl ? pImpl->GetSaveUserColor() : 0;
//STRIP001 }

//STRIP001 inline const Color* SwTableBox::GetSaveNumFmtColor() const
//STRIP001 {
//STRIP001  return pImpl ? pImpl->GetSaveNumFmtColor() : 0;
//STRIP001 }

//STRIP001 inline void SwTableBox::SetSaveUserColor(const Color* p )
//STRIP001 {
//STRIP001  if( pImpl )
//STRIP001      pImpl->SetSaveUserColor( p );
//STRIP001  else if( p )
//STRIP001      ( pImpl = new SwTableBox_Impl ) ->SetSaveUserColor( p );
//STRIP001 }

//STRIP001 inline void SwTableBox::SetSaveNumFmtColor( const Color* p )
//STRIP001 {
//STRIP001  if( pImpl )
//STRIP001      pImpl->SetSaveNumFmtColor( p );
//STRIP001  else if( p )
//STRIP001      ( pImpl = new SwTableBox_Impl )->SetSaveNumFmtColor( p );
//STRIP001 }

//JP 15.09.98: Bug 55741 - Tabs beibehalten (vorne und hinten)
//STRIP001 String& lcl_TabToBlankAtSttEnd( String& rTxt )
//STRIP001 {
//STRIP001  sal_Unicode c;
//STRIP001  for( xub_StrLen n = 0; n < rTxt.Len() && ' ' >= ( c = rTxt.GetChar( n )); ++n )
//STRIP001      if( '\x9' == c )
//STRIP001          rTxt.SetChar( n, ' ' );
//STRIP001  for( n = rTxt.Len(); n && ' ' >= ( c = rTxt.GetChar( --n )); )
//STRIP001      if( '\x9' == c )
//STRIP001          rTxt.SetChar( n, ' ' );
//STRIP001  return rTxt;
//STRIP001 }

//STRIP001 String& lcl_DelTabsAtSttEnd( String& rTxt )
//STRIP001 {
//STRIP001  sal_Unicode c;
//STRIP001  for( xub_StrLen n = 0; n < rTxt.Len() && ' ' >= ( c = rTxt.GetChar( n )); ++n )
//STRIP001      if( '\x9' == c )
//STRIP001          rTxt.Erase( n--, 1 );
//STRIP001  for( n = rTxt.Len(); n && ' ' >= ( c = rTxt.GetChar( --n )); )
//STRIP001      if( '\x9' == c )
//STRIP001          rTxt.Erase( n, 1 );
//STRIP001  return rTxt;
//STRIP001 }

//STRIP001 void _InsTblBox( SwDoc* pDoc, SwTableNode* pTblNd,
//STRIP001                      SwTableLine* pLine, SwTableBoxFmt* pBoxFrmFmt,
//STRIP001                      SwTableBox* pBox,
//STRIP001                      USHORT nInsPos, USHORT nCnt )
//STRIP001 {
//STRIP001  ASSERT( pBox->GetSttNd(), "Box ohne Start-Node" );
//STRIP001  SwNodeIndex aIdx( *pBox->GetSttNd(), +1 );
//STRIP001  SwCntntNode* pCNd = aIdx.GetNode().GetCntntNode();
//STRIP001  if( !pCNd )
//STRIP001      pCNd = pDoc->GetNodes().GoNext( &aIdx );
//STRIP001  ASSERT( pCNd, "Box ohne ContentNode" );
//STRIP001
//STRIP001  if( pCNd->IsTxtNode() )
//STRIP001  {
//STRIP001      if( pBox->GetSaveNumFmtColor() && pCNd->GetpSwAttrSet() )
//STRIP001      {
//STRIP001          SwAttrSet aAttrSet( *pCNd->GetpSwAttrSet() );
//STRIP001          if( pBox->GetSaveUserColor() )
//STRIP001              aAttrSet.Put( SvxColorItem( *pBox->GetSaveUserColor() ));
//STRIP001          else
//STRIP001              aAttrSet.ClearItem( RES_CHRATR_COLOR );
//STRIP001          pDoc->GetNodes().InsBoxen( pTblNd, pLine, pBoxFrmFmt,
//STRIP001                                  ((SwTxtNode*)pCNd)->GetTxtColl(),
//STRIP001                                  &aAttrSet, nInsPos, nCnt );
//STRIP001      }
//STRIP001      else
//STRIP001          pDoc->GetNodes().InsBoxen( pTblNd, pLine, pBoxFrmFmt,
//STRIP001                                  ((SwTxtNode*)pCNd)->GetTxtColl(),
//STRIP001                                  pCNd->GetpSwAttrSet(),
//STRIP001                                  nInsPos, nCnt );
//STRIP001  }
//STRIP001  else
//STRIP001      pDoc->GetNodes().InsBoxen( pTblNd, pLine, pBoxFrmFmt,
//STRIP001              (SwTxtFmtColl*)pDoc->GetDfltTxtFmtColl(), 0,
//STRIP001              nInsPos, nCnt );
//STRIP001 }

/*************************************************************************
|*
|*  SwTable::SwTable()
|*
|*  Ersterstellung      MA 09. Mar. 93
|*  Letzte Aenderung    MA 05. May. 93
|*
|*************************************************************************/
/*N*/ SwTable::SwTable( SwTableFmt* pFmt )
/*N*/   : SwClient( pFmt ),
/*N*/   pHTMLLayout( 0 ),
/*N*/   nGrfsThatResize( 0 )
/*N*/ {
/*N*/   bModifyLocked = FALSE;
/*N*/   bHeadlineRepeat = TRUE;
/*N*/
/*N*/   // default Wert aus den Optionen setzen
/*N*/   eTblChgMode = (TblChgMode)GetTblChgDefaultMode();
/*N*/ }

/*N*/ SwTable::SwTable( const SwTable& rTable )
/*N*/   : SwClient( rTable.GetFrmFmt() ),
/*N*/   pHTMLLayout( 0 ),
/*N*/   nGrfsThatResize( 0 )
/*N*/ {
/*N*/   bHeadlineRepeat = rTable.IsHeadlineRepeat();
/*N*/   bModifyLocked = FALSE;
/*N*/   eTblChgMode = rTable.eTblChgMode;
/*N*/ }

/*N*/ void DelBoxNode( SwTableSortBoxes& rSortCntBoxes )
/*N*/ {
/*N*/   for( USHORT n = 0; n < rSortCntBoxes.Count(); ++n )
/*N*/       rSortCntBoxes[ n ]->pSttNd = 0;
/*N*/ }

/*N*/ SwTable::~SwTable()
/*N*/ {
/*N*/   if( refObj.Is() )
/*N*/   {
/*?*/       SwDoc* pDoc = GetFrmFmt()->GetDoc();
/*?*/       if( !pDoc->IsInDtor() )         // dann aus der Liste entfernen
/*?*/           pDoc->GetLinkManager().RemoveServer( &refObj );
/*?*/
/*?*/       refObj->Closed();
/*N*/   }
/*N*/
/*N*/   // ist die Tabelle der letzte Client im FrameFormat, kann dieses
/*N*/   // geloescht werden
/*N*/   SwTableFmt* pFmt = (SwTableFmt*)GetFrmFmt();
/*N*/   pFmt->Remove( this );               // austragen,
/*N*/
/*N*/   if( !pFmt->GetDepends() )
/*N*/       pFmt->GetDoc()->DelTblFrmFmt( pFmt );   // und loeschen
/*N*/
/*N*/   // Loesche die Pointer aus dem SortArray der Boxen, die
/*N*/   // Objecte bleiben erhalten und werden vom DTOR der Lines/Boxes
/*N*/   // Arrays geloescht.
/*N*/   //JP: reicht leider nicht, es muessen die Pointer auf den StartNode
/*N*/   //  der Section geloescht werden
/*N*/   DelBoxNode( aSortCntBoxes );
/*N*/   aSortCntBoxes.Remove( (USHORT)0, aSortCntBoxes.Count() );
/*N*/   delete pHTMLLayout;
/*N*/ }

/*************************************************************************
|*
|*  SwTable::Modify()
|*
|*  Ersterstellung      JP ??
|*  Letzte Aenderung    MA 06. May. 93
|*
|*************************************************************************/
/*?*/ inline BOOL FmtInArr( SvPtrarr& rFmtArr, SwFmt* pBoxFmt )
/*?*/ {
/*?*/   BOOL bRet = USHRT_MAX != rFmtArr.GetPos( (VoidPtr)pBoxFmt );
/*?*/   if( !bRet )
/*?*/       rFmtArr.Insert( (VoidPtr)pBoxFmt, rFmtArr.Count() );
/*?*/   return bRet;
/*?*/ }

/*N*/ void lcl_ModifyBoxes( SwTableBoxes &rBoxes, const long nOld,
/*N*/                        const long nNew, SvPtrarr& rFmtArr );
/*N*/
/*N*/ void lcl_ModifyLines( SwTableLines &rLines, const long nOld,
/*N*/                        const long nNew, SvPtrarr& rFmtArr )
/*N*/ {
/*N*/   for ( USHORT i = 0; i < rLines.Count(); ++i )
/*N*/       ::binfilter::lcl_ModifyBoxes( rLines[i]->GetTabBoxes(), nOld, nNew, rFmtArr );
/*N*/ }

/*N*/ void lcl_ModifyBoxes( SwTableBoxes &rBoxes, const long nOld,
/*N*/                        const long nNew, SvPtrarr& rFmtArr )
/*N*/ {
/*N*/   for ( USHORT i = 0; i < rBoxes.Count(); ++i )
/*N*/   {
/*N*/       SwTableBox &rBox = *rBoxes[i];
/*N*/       if ( rBox.GetTabLines().Count() )
/*?*/           ::binfilter::lcl_ModifyLines( rBox.GetTabLines(), nOld, nNew, rFmtArr );
/*N*/       //Die Box anpassen
/*N*/       SwFrmFmt *pFmt = rBox.GetFrmFmt();
/*N*/       if ( !FmtInArr( rFmtArr, pFmt ) )
/*N*/       {
/*N*/           long nBox = pFmt->GetFrmSize().GetWidth();
/*N*/           nBox *= nNew;
/*N*/           nBox /= nOld;
/*N*/           SwFmtFrmSize aNewBox( ATT_VAR_SIZE, nBox, 0 );
/*N*/           pFmt->LockModify();
/*N*/           pFmt->SetAttr( aNewBox );
/*N*/           pFmt->UnlockModify();
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void SwTable::Modify( SfxPoolItem *pOld, SfxPoolItem *pNew )
/*N*/ {
/*N*/   // fange SSize Aenderungen ab, um die Lines/Boxen anzupassen
/*N*/   USHORT nWhich = pOld ? pOld->Which() : pNew ? pNew->Which() : 0 ;
/*N*/   const SwFmtFrmSize* pNewSize = 0, *pOldSize = 0;
/*N*/
/*N*/   if( RES_ATTRSET_CHG == nWhich )
/*N*/   {
/*N*/       if( SFX_ITEM_SET == ((SwAttrSetChg*)pNew)->GetChgSet()->GetItemState(
/*N*/           RES_FRM_SIZE, FALSE, (const SfxPoolItem**)&pNewSize ))
/*N*/           pOldSize = &((SwAttrSetChg*)pOld)->GetChgSet()->GetFrmSize();
/*N*/   }
/*N*/   else if( RES_FRM_SIZE == nWhich )
/*N*/   {
/*?*/       pOldSize = (const SwFmtFrmSize*)pOld;
/*?*/       pNewSize = (const SwFmtFrmSize*)pNew;
/*N*/   }

/*N*/   if( pOldSize || pNewSize )
/*N*/   {
/*N*/       if ( !IsModifyLocked() )
/*N*/       {
/*N*/           ASSERT( pOldSize && pOldSize->Which() == RES_FRM_SIZE &&
/*N*/                   pNewSize && pNewSize->Which() == RES_FRM_SIZE,
/*N*/                   "Kein Old oder New fuer FmtFrmSize-Modify der SwTable." );
/*N*/
/*N*/           // Array zum Vergleichen der Box-Formatpointer; um zu verhindern,
/*N*/           // das das gleiche Attribut immer wieder im selben Format
/*N*/           // gesetzt wird. (+1 fuer das Ende-Kennzeichen)
/*N*/           SvPtrarr aFmtArr( (BYTE)aLines[0]->GetTabBoxes().Count(), 1 );
/*N*/
/*N*/           ::binfilter::lcl_ModifyLines( aLines, pOldSize->GetWidth(), pNewSize->GetWidth(),
/*N*/                          aFmtArr );
/*N*/       }
/*N*/   }
/*N*/   else
/*N*/       SwClient::Modify( pOld, pNew );         // fuers ObjectDying
/*N*/ }

/*************************************************************************
|*
|*  SwTable::GetTabCols()
|*
|*  Ersterstellung      MA 04. May. 93
|*  Letzte Aenderung    MA 30. Nov. 95
|*
|*************************************************************************/
//STRIP001 void lcl_RefreshHidden( SwTabCols &rToFill, USHORT nPos )
//STRIP001 {
//STRIP001  for ( USHORT i = 0; i < rToFill.Count(); ++i )
//STRIP001  {
//STRIP001      if ( Abs((long)(nPos - rToFill[i])) <= COLFUZZY )
//STRIP001      {
//STRIP001          rToFill.GetHidden()[i] = FALSE;
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void lcl_SortedTabColInsert( SwTabCols &rToFill, const SwTableBox *pBox,
//STRIP001                 const SwFrmFmt *pTabFmt, const FASTBOOL bHidden,
//STRIP001                 const FASTBOOL bRefreshHidden )
//STRIP001 {
//STRIP001  const long nWish = pTabFmt->GetFrmSize().GetWidth();
//STRIP001  const long nAct  = rToFill.GetRight() - rToFill.GetLeft() + 1;
//STRIP001
//STRIP001  //Der Wert fuer die linke Kante der Box errechnet sich aus den
//STRIP001  //Breiten der vorhergehenden Boxen.
//STRIP001  USHORT nPos = 0;
//STRIP001  const SwTableBox  *pCur  = pBox;
//STRIP001  const SwTableLine *pLine = pBox->GetUpper();
//STRIP001  while ( pLine )
//STRIP001  {   const SwTableBoxes &rBoxes = pLine->GetTabBoxes();
//STRIP001      for ( USHORT i = 0; (i < rBoxes.Count()) && (rBoxes[i] != pCur); ++i)
//STRIP001      {
//STRIP001          long nWidth = rBoxes[i]->GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001          nWidth *= nAct;
//STRIP001          nWidth /= nWish;
//STRIP001          nPos += (USHORT)nWidth;
//STRIP001      }
//STRIP001      pCur  = pLine->GetUpper();
//STRIP001      pLine = pCur ? pCur->GetUpper() : 0;
//STRIP001  }
//STRIP001
//STRIP001  FASTBOOL bInsert = !bRefreshHidden;
//STRIP001  for ( USHORT j = 0; bInsert && (j < rToFill.Count()); ++j )
//STRIP001  {
//STRIP001      USHORT nCmp = rToFill[j];
//STRIP001      if ( (nPos >= ((nCmp >= COLFUZZY) ? nCmp - COLFUZZY : nCmp)) &&
//STRIP001           (nPos <= (nCmp + COLFUZZY)) )
//STRIP001      {
//STRIP001          bInsert = FALSE;        //Hat ihn schon.
//STRIP001      }
//STRIP001      else if ( nPos < nCmp )
//STRIP001      {
//STRIP001          if ( bRefreshHidden )
//STRIP001              ::lcl_RefreshHidden( rToFill, nPos );
//STRIP001          else
//STRIP001          {
//STRIP001              bInsert = FALSE;
//STRIP001              rToFill.Insert( nPos, j );
//STRIP001              rToFill.InsertHidden( j, bHidden );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if ( bInsert )
//STRIP001  {
//STRIP001      if ( bRefreshHidden )
//STRIP001          ::lcl_RefreshHidden( rToFill, nPos );
//STRIP001      rToFill.Insert( nPos, rToFill.Count() );
//STRIP001      rToFill.InsertHidden( rToFill.GetHidden().Count(), bHidden );
//STRIP001  }
//STRIP001  else if ( bRefreshHidden )
//STRIP001      ::lcl_RefreshHidden( rToFill, nPos );
//STRIP001 }

//STRIP001 void lcl_ProcessBoxGet( const SwTableBox *pBox, SwTabCols &rToFill,
//STRIP001                      const SwFrmFmt *pTabFmt, FASTBOOL bRefreshHidden )
//STRIP001 {
//STRIP001  if ( pBox->GetTabLines().Count() )
//STRIP001  {
//STRIP001      const SwTableLines &rLines = pBox->GetTabLines();
//STRIP001      for ( USHORT i = 0; i < rLines.Count(); ++i )
//STRIP001      {   const SwTableBoxes &rBoxes = rLines[i]->GetTabBoxes();
//STRIP001          for ( USHORT j = 0; j < rBoxes.Count(); ++j )
//STRIP001              ::lcl_ProcessBoxGet( rBoxes[j], rToFill, pTabFmt, bRefreshHidden);
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      ::lcl_SortedTabColInsert( rToFill, pBox, pTabFmt, FALSE, bRefreshHidden );
//STRIP001 }

//STRIP001 void lcl_ProcessLineGet( const SwTableLine *pLine, SwTabCols &rToFill,
//STRIP001                       const SwFrmFmt *pTabFmt )
//STRIP001 {
//STRIP001  for ( USHORT i = 0; i < pLine->GetTabBoxes().Count(); ++i )
//STRIP001  {
//STRIP001      const SwTableBox *pBox = pLine->GetTabBoxes()[i];
//STRIP001      if ( pBox->GetSttNd() )
//STRIP001          ::lcl_SortedTabColInsert( rToFill, pBox, pTabFmt, TRUE, FALSE );
//STRIP001      else
//STRIP001          for ( USHORT j = 0; j < pBox->GetTabLines().Count(); ++j )
//STRIP001              ::lcl_ProcessLineGet( pBox->GetTabLines()[j], rToFill, pTabFmt );
//STRIP001  }
//STRIP001 }

// MS: Sonst Absturz auf der DEC-Kiste
//
#if defined(ALPHA) && defined(WNT)
#pragma optimize("", off)
#endif


/*N*/ void SwTable::GetTabCols( SwTabCols &rToFill, const SwTableBox *pStart,
/*N*/                         FASTBOOL bRefreshHidden, BOOL bCurRowOnly ) const
/*N*/ {
/*N*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 //MA 30. Nov. 95: Opt: wenn bHidden gesetzt ist, wird neu das Hidden
//STRIP001  //Array aktualisiert.
//STRIP001  if ( bRefreshHidden )
//STRIP001  {
//STRIP001      //Korrekturen entfernen
//STRIP001      for ( USHORT i = 0; i < rToFill.Count(); ++i )
//STRIP001          rToFill[i] -= rToFill.GetLeft();
//STRIP001
//STRIP001      //Alle sind hidden, dann die sichtbaren eintragen.
//STRIP001      for ( i = 0; i < rToFill.GetHidden().Count(); ++i )
//STRIP001          rToFill.GetHidden()[i] = TRUE;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      rToFill.Remove( 0, rToFill.Count() );
//STRIP001      rToFill.DeleteHidden( 0, rToFill.GetHidden().Count() );
//STRIP001  }
//STRIP001
//STRIP001  //Eingetragen werden:
//STRIP001  //1. Alle Boxen unterhalb der dem Start uebergeordneten Line sowie
//STRIP001  //   deren untergeordnete Boxen falls vorhanden.
//STRIP001  //2. Ausgehend von der Line die uebergeordnete Box sowie deren Nachbarn;
//STRIP001  //   nicht aber deren untergeordnete.
//STRIP001  //3. Mit der der Boxenkette uebergeordneten Line wieder wie 2. bis einer
//STRIP001  //   Line keine Box (sondern die Table) uebergeordnet ist.
//STRIP001  //Es werden nur diejenigen Boxen eingetragen, die keine weiteren Zeilen
//STRIP001  //enhalten. Die eintragende Funktion sorgt dafuer, dass keine doppelten
//STRIP001  //eingetragen werden. Um dies zu gewaehrleisten wird mit einer gewissen
//STRIP001  //Unschaerfe gearbeitet (um Rundungsfehler auszuschalten).
//STRIP001  //Es werden nur die linken Kanten der Boxen eingetragen.
//STRIP001  //Am Schluss wird der Erste wieder ausgetragen denn er ist bereits vom
//STRIP001  //Rand abgedeckt.
//STRIP001
//STRIP001  //4. Nochmalige abscannen der Tabelle und eintragen _aller_ Boxen,
//STRIP001  //   jetzt aber als Hidden.
//STRIP001
//STRIP001  const SwFrmFmt *pTabFmt = GetFrmFmt();
//STRIP001
//STRIP001  //1.
//STRIP001  const SwTableBoxes &rBoxes = pStart->GetUpper()->GetTabBoxes();
//STRIP001  for ( USHORT i = 0; i < rBoxes.Count(); ++i )
//STRIP001      ::lcl_ProcessBoxGet( rBoxes[i], rToFill, pTabFmt, bRefreshHidden );
//STRIP001
//STRIP001  //2. und 3.
//STRIP001  const SwTableLine *pLine = pStart->GetUpper()->GetUpper() ?
//STRIP001                              pStart->GetUpper()->GetUpper()->GetUpper() : 0;
//STRIP001  while ( pLine )
//STRIP001  {
//STRIP001      const SwTableBoxes &rBoxes = pLine->GetTabBoxes();
//STRIP001      for ( USHORT i = 0; i < rBoxes.Count(); ++i )
//STRIP001          ::lcl_SortedTabColInsert( rToFill, rBoxes[i],
//STRIP001                                    pTabFmt, FALSE, bRefreshHidden );
//STRIP001      pLine = pLine->GetUpper() ? pLine->GetUpper()->GetUpper() : 0;
//STRIP001  }
//STRIP001
//STRIP001  if ( !bRefreshHidden )
//STRIP001  {
//STRIP001      //4.
//STRIP001      if ( !bCurRowOnly )
//STRIP001      {
//STRIP001          for ( i = 0; i < aLines.Count(); ++i )
//STRIP001              ::lcl_ProcessLineGet( aLines[i], rToFill, pTabFmt );
//STRIP001      }
//STRIP001
//STRIP001      rToFill.Remove( 0, 1 );
//STRIP001      rToFill.DeleteHidden( 0, 1 );
//STRIP001  }
//STRIP001
//STRIP001  //Die Koordinaten sind jetzt relativ zum linken Rand der Tabelle - also
//STRIP001  //relativ zum nLeft vom SwTabCols. Die Werte werden aber relativ zum
//STRIP001  //linken Rand - also nLeftMin vom SwTabCols - erwartet.
//STRIP001  //Alle Werte muessen also um nLeft erweitert werden.
//STRIP001  for ( i = 0; i < rToFill.Count(); ++i )
//STRIP001      rToFill[i] += rToFill.GetLeft();
/*N*/ }

#if defined(ALPHA) && defined(WNT)
#pragma optimize("", on)
#endif

/*************************************************************************
|*
|*  SwTable::SetTabCols()
|*
|*  Ersterstellung      MA 04. May. 93
|*  Letzte Aenderung    MA 26. Aug. 98
|*
|*************************************************************************/
//Struktur zur Parameteruebergabe
//STRIP001 struct Parm
//STRIP001 {
//STRIP001  const SwTabCols &rNew;
//STRIP001  const SwTabCols &rOld;
//STRIP001  long nNewWish,
//STRIP001       nOldWish;
//STRIP001  SvPtrarr aBoxArr;
//STRIP001  SwShareBoxFmts aShareFmts;
//STRIP001
//STRIP001  Parm( const SwTabCols &rN, const SwTabCols &rO ) :
//STRIP001      rNew( rN ),
//STRIP001      rOld( rO ),
//STRIP001      aBoxArr( 10, 1 ) {}
//STRIP001 };
//STRIP001 inline BOOL BoxInArr( SvPtrarr& rArr, SwTableBox* pBox )
//STRIP001 {
//STRIP001  BOOL bRet = USHRT_MAX != rArr.GetPos( (VoidPtr)pBox );
//STRIP001  if( !bRet )
//STRIP001      rArr.Insert( (VoidPtr)pBox, rArr.Count() );
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 void lcl_ProcessBoxSet( SwTableBox *pBox, Parm &rParm );

//STRIP001 void lcl_ProcessLine( SwTableLine *pLine, Parm &rParm )
//STRIP001 {
//STRIP001  SwTableBoxes &rBoxes = pLine->GetTabBoxes();
//STRIP001  for ( int i = rBoxes.Count()-1; i >= 0; --i )
//STRIP001      ::lcl_ProcessBoxSet( rBoxes[i], rParm );
//STRIP001 }

//STRIP001 void lcl_ProcessBoxSet( SwTableBox *pBox, Parm &rParm )
//STRIP001 {
//STRIP001  if ( pBox->GetTabLines().Count() )
//STRIP001  {   SwTableLines &rLines = pBox->GetTabLines();
//STRIP001      for ( int i = rLines.Count()-1; i >= 0; --i )
//STRIP001          lcl_ProcessLine( rLines[i], rParm );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      //Aktuelle Position (linke und rechte Kante berechnen) und im
//STRIP001      //alten TabCols suchen. Im neuen TabCols die Werte vergleichen und
//STRIP001      //wenn es Unterschiede gibt die Box entsprechend anpassen.
//STRIP001      //Wenn an der veraenderten Kante kein Nachbar existiert werden auch
//STRIP001      //alle uebergeordneten Boxen angepasst.
//STRIP001
//STRIP001      const long nOldAct = rParm.rOld.GetRight() -
//STRIP001                           rParm.rOld.GetLeft() + 1;
//STRIP001
//STRIP001      //Der Wert fuer die linke Kante der Box errechnet sich aus den
//STRIP001      //Breiten der vorhergehenden Boxen plus dem linken Rand
//STRIP001      long nLeft = rParm.rOld.GetLeft();
//STRIP001      const  SwTableBox  *pCur  = pBox;
//STRIP001      const  SwTableLine *pLine = pBox->GetUpper();
//STRIP001
//STRIP001      while ( pLine )
//STRIP001      {   const SwTableBoxes &rBoxes = pLine->GetTabBoxes();
//STRIP001          for ( USHORT i = 0; (i < rBoxes.Count()) && (rBoxes[i] != pCur); ++i)
//STRIP001          {
//STRIP001              long nWidth = rBoxes[i]->GetFrmFmt()->
//STRIP001                                      GetFrmSize().GetWidth();
//STRIP001              nWidth *= nOldAct;
//STRIP001              nWidth /= rParm.nOldWish;
//STRIP001              nLeft += (USHORT)nWidth;
//STRIP001          }
//STRIP001          pCur  = pLine->GetUpper();
//STRIP001          pLine = pCur ? pCur->GetUpper() : 0;
//STRIP001      }
//STRIP001      long nLeftDiff;
//STRIP001      long nRightDiff = 0;
//STRIP001      if ( nLeft != rParm.rOld.GetLeft() ) //Es gibt noch Boxen davor.
//STRIP001      {
//STRIP001          //Rechte Kante ist linke Kante plus Breite.
//STRIP001          long nWidth = pBox->GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001          nWidth *= nOldAct;
//STRIP001          nWidth /= rParm.nOldWish;
//STRIP001          long nRight = nLeft + nWidth;
//STRIP001          USHORT nLeftPos  = USHRT_MAX,
//STRIP001                 nRightPos = USHRT_MAX;
//STRIP001          for ( USHORT i = 0; i < rParm.rOld.Count(); ++i )
//STRIP001          {
//STRIP001              if ( nLeft >= (rParm.rOld[i] - COLFUZZY) &&
//STRIP001                   nLeft <= (rParm.rOld[i] + COLFUZZY) )
//STRIP001                  nLeftPos = i;
//STRIP001              else if ( nRight >= (rParm.rOld[i] - COLFUZZY) &&
//STRIP001                        nRight <= (rParm.rOld[i] + COLFUZZY) )
//STRIP001                  nRightPos = i;
//STRIP001          }
//STRIP001          nLeftDiff = nLeftPos != USHRT_MAX ?
//STRIP001                  (int)rParm.rOld[nLeftPos] - (int)rParm.rNew[nLeftPos] : 0;
//STRIP001          nRightDiff= nRightPos!= USHRT_MAX ?
//STRIP001                  (int)rParm.rNew[nRightPos] - (int)rParm.rOld[nRightPos] : 0;
//STRIP001      }
//STRIP001      else    //Die erste Box.
//STRIP001      {
//STRIP001          nLeftDiff = (long)rParm.rOld.GetLeft() - (long)rParm.rNew.GetLeft();
//STRIP001          if ( rParm.rOld.Count() )
//STRIP001          {
//STRIP001              //Differnz zu der Kante berechnen, von der die erste Box
//STRIP001              //beruehrt wird.
//STRIP001              long nWidth = pBox->GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001              nWidth *= nOldAct;
//STRIP001              nWidth /= rParm.nOldWish;
//STRIP001              long nTmp = nWidth;
//STRIP001              nTmp += rParm.rOld.GetLeft();
//STRIP001              USHORT nLeftPos = USHRT_MAX;
//STRIP001              for ( USHORT i = 0; i < rParm.rOld.Count() &&
//STRIP001                                  nLeftPos == USHRT_MAX; ++i )
//STRIP001              {
//STRIP001                  if ( nTmp >= (rParm.rOld[i] - COLFUZZY) &&
//STRIP001                       nTmp <= (rParm.rOld[i] + COLFUZZY) )
//STRIP001                      nLeftPos = i;
//STRIP001              }
//STRIP001              if ( nLeftPos != USHRT_MAX )
//STRIP001                  nRightDiff = (long)rParm.rNew[nLeftPos] -
//STRIP001                               (long)rParm.rOld[nLeftPos];
//STRIP001          }
//STRIP001 //MA 11. Feb. 99: #61577# 0 sollte doch gerade richtig sein, weil die
//STRIP001 //Kante doch schon in SetTabCols() korrigiert wurde.
//STRIP001 //           else
//STRIP001 //               nRightDiff = (long)rParm.rNew.GetRight() -
//STRIP001 //                            (long)rParm.rOld.GetRight();
//STRIP001      }
//STRIP001
//STRIP001      if ( nLeftDiff || nRightDiff )
//STRIP001      {
//STRIP001          //Die Differenz ist der tatsaechliche Differenzbetrag; die
//STRIP001          //Attribute der Boxen um diesen Betrag anzupassen macht keinen
//STRIP001          //Sinn wenn die Tabelle gestrecht ist. Der Differenzbetrag muss
//STRIP001          //entsprechend umgerechnet werden.
//STRIP001          long nTmp = rParm.rNew.GetRight() - rParm.rNew.GetLeft() + 1;
//STRIP001          nLeftDiff *= rParm.nNewWish;
//STRIP001          nLeftDiff /= nTmp;
//STRIP001          nRightDiff *= rParm.nNewWish;
//STRIP001          nRightDiff /= nTmp;
//STRIP001          long nDiff = nLeftDiff + nRightDiff;
//STRIP001
//STRIP001          //Box und alle uebergeordneten um den Differenzbetrag anpassen.
//STRIP001          BOOL bUp = FALSE;
//STRIP001          while ( pBox )
//STRIP001          {
//STRIP001              if ( !bUp || (bUp && !::BoxInArr( rParm.aBoxArr, pBox )) )
//STRIP001              {
//STRIP001                  SwFmtFrmSize aFmtFrmSize( pBox->GetFrmFmt()->GetFrmSize() );
//STRIP001                  aFmtFrmSize.SetWidth( aFmtFrmSize.GetWidth() + nDiff );
//STRIP001                  if ( aFmtFrmSize.GetWidth() < 0 )
//STRIP001                      aFmtFrmSize.SetWidth( -aFmtFrmSize.GetWidth() );
//STRIP001                  rParm.aShareFmts.SetSize( *pBox, aFmtFrmSize );
//STRIP001                  bUp = TRUE;
//STRIP001              }
//STRIP001
//STRIP001              //Wenn es links noch Boxen gibt, die LeftDiff nicht auf den Upper
//STRIP001              if ( pBox != pBox->GetUpper()->GetTabBoxes()[0] )
//STRIP001                  nDiff = nRightDiff;
//STRIP001              //Wenn es rechts noch Boxen gibt, den RightDiff nicht auf den Upper
//STRIP001              if ( pBox != pBox->GetUpper()->GetTabBoxes()
//STRIP001                              [pBox->GetUpper()->GetTabBoxes().Count()-1] )
//STRIP001                  nDiff -= nRightDiff;
//STRIP001              pBox = nDiff ? pBox->GetUpper()->GetUpper() : 0;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void lcl_ProcessBoxPtr( SwTableBox *pBox, SvPtrarr &rBoxArr,
//STRIP001                         BOOL bBefore )
//STRIP001 {
//STRIP001  if ( pBox->GetTabLines().Count() )
//STRIP001  {
//STRIP001      const SwTableLines &rLines = pBox->GetTabLines();
//STRIP001      for ( USHORT i = 0; i < rLines.Count(); ++i )
//STRIP001      {
//STRIP001          const SwTableBoxes &rBoxes = rLines[i]->GetTabBoxes();
//STRIP001          for ( USHORT j = 0; j < rBoxes.Count(); ++j )
//STRIP001              ::lcl_ProcessBoxPtr( rBoxes[j], rBoxArr, bBefore );
//STRIP001      }
//STRIP001  }
//STRIP001  else if ( bBefore )
//STRIP001      rBoxArr.Insert( (VoidPtr)pBox, 0 );
//STRIP001  else
//STRIP001      rBoxArr.Insert( (VoidPtr)pBox, rBoxArr.Count() );
//STRIP001 }

//STRIP001 void lcl_AdjustBox( SwTableBox *pBox, const long nDiff, Parm &rParm );

//STRIP001 void lcl_AdjustLines( SwTableLines &rLines, const long nDiff, Parm &rParm )
//STRIP001 {
//STRIP001  for ( USHORT i = 0; i < rLines.Count(); ++i )
//STRIP001  {
//STRIP001      SwTableBox *pBox = rLines[i]->GetTabBoxes()
//STRIP001                              [rLines[i]->GetTabBoxes().Count()-1];
//STRIP001      lcl_AdjustBox( pBox, nDiff, rParm );
//STRIP001  }
//STRIP001 }

//STRIP001 void lcl_AdjustBox( SwTableBox *pBox, const long nDiff, Parm &rParm )
//STRIP001 {
//STRIP001  if ( pBox->GetTabLines().Count() )
//STRIP001      ::lcl_AdjustLines( pBox->GetTabLines(), nDiff, rParm );
//STRIP001
//STRIP001  //Groesse der Box anpassen.
//STRIP001  SwFmtFrmSize aFmtFrmSize( pBox->GetFrmFmt()->GetFrmSize() );
//STRIP001  aFmtFrmSize.SetWidth( aFmtFrmSize.GetWidth() + nDiff );
//STRIP001 //#30009#        if ( aFmtFrmSize.GetWidth() < 0 )
//STRIP001 //           aFmtFrmSize.SetWidth( -aFmtFrmSize.GetWidth() );
//STRIP001
//STRIP001  rParm.aShareFmts.SetSize( *pBox, aFmtFrmSize );
//STRIP001 }

//STRIP001 void SwTable::SetTabCols( const SwTabCols &rNew, SwTabCols &rOld,
//STRIP001                        const SwTableBox *pStart, BOOL bCurRowOnly )
//STRIP001 {
//STRIP001  SetHTMLTableLayout( 0 );    // MIB 9.7.97: HTML-Layout loeschen
//STRIP001
//STRIP001  GetTabCols( rOld, pStart );
//STRIP001
//STRIP001  Parm aParm( rNew, rOld );
//STRIP001
//STRIP001  ASSERT( rOld.Count() == rNew.Count(), "Columnanzahl veraendert.");
//STRIP001
//STRIP001  //Raender verarbeiten. Groesse der Tabelle und ein paar Boxen mussen
//STRIP001  //angepasst werden. Bei der Groesseneinstellung darf allerdings das
//STRIP001  //Modify nicht verarbeitet werden - dieses wuerde alle Boxen anpassen
//STRIP001  //und das koennen wir ueberhaupt nicht gebrauchen.
//STRIP001  SwFrmFmt *pFmt = GetFrmFmt();
//STRIP001  aParm.nOldWish = aParm.nNewWish = pFmt->GetFrmSize().GetWidth();
//STRIP001  if ( (rOld.GetLeft() != rNew.GetLeft()) ||
//STRIP001       (rOld.GetRight()!= rNew.GetRight()) )
//STRIP001  {
//STRIP001      LockModify();
//STRIP001      {
//STRIP001          SvxLRSpaceItem aLR( pFmt->GetLRSpace() );
//STRIP001             SvxShadowItem aSh( pFmt->GetShadow() );
//STRIP001
//STRIP001             SwTwips nShRight = aSh.CalcShadowSpace( SHADOW_RIGHT );
//STRIP001             SwTwips nShLeft = aSh.CalcShadowSpace( SHADOW_LEFT );
//STRIP001
//STRIP001          aLR.SetLeft ( rNew.GetLeft() - nShLeft );
//STRIP001             aLR.SetRight( rNew.GetRightMax() - rNew.GetRight() - nShRight );
//STRIP001          pFmt->SetAttr( aLR );
//STRIP001
//STRIP001          //Die Ausrichtung der Tabelle muss entsprechend angepasst werden,
//STRIP001          //das geschieht so, dass die Tabelle genauso stehenbleibt wie der
//STRIP001          //Anwender sie gerade hingezuppelt hat.
//STRIP001          SwFmtHoriOrient aOri( pFmt->GetHoriOrient() );
//STRIP001          if(HORI_NONE != aOri.GetHoriOrient())
//STRIP001          {
//STRIP001              BOOL bLeftDist = rNew.GetLeft() != nShLeft;
//STRIP001              BOOL bRightDist = rNew.GetRight() + nShRight != rNew.GetRightMax();
//STRIP001              if(!bLeftDist && !bRightDist)
//STRIP001                  aOri.SetHoriOrient( HORI_FULL );
//STRIP001              else if(!bRightDist && rNew.GetLeft() > nShLeft )
//STRIP001                  aOri.SetHoriOrient( HORI_RIGHT );
//STRIP001              else if(!bLeftDist && rNew.GetRight() + nShRight < rNew.GetRightMax())
//STRIP001                  aOri.SetHoriOrient( HORI_LEFT );
//STRIP001              else
//STRIP001                  aOri.SetHoriOrient( HORI_NONE );
//STRIP001          }
//STRIP001          pFmt->SetAttr( aOri );
//STRIP001      }
//STRIP001      const long nAct = rOld.GetRight() - rOld.GetLeft() + 1;
//STRIP001      long nTabDiff = 0;
//STRIP001
//STRIP001      if ( rOld.GetLeft() != rNew.GetLeft() )
//STRIP001      {
//STRIP001          nTabDiff = rOld.GetLeft() - rNew.GetLeft();
//STRIP001          nTabDiff *= aParm.nOldWish;
//STRIP001          nTabDiff /= nAct;
//STRIP001      }
//STRIP001      if ( rOld.GetRight() != rNew.GetRight() )
//STRIP001      {
//STRIP001          long nDiff = rNew.GetRight() - rOld.GetRight();
//STRIP001          nDiff *= aParm.nOldWish;
//STRIP001          nDiff /= nAct;
//STRIP001          nTabDiff += nDiff;
//STRIP001          ::lcl_AdjustLines( GetTabLines(), nDiff, aParm );
//STRIP001      }
//STRIP001
//STRIP001      //Groesse der Tabelle anpassen. Es muss beachtet werden, das die
//STRIP001      //Tabelle gestrecht sein kann.
//STRIP001      if ( nTabDiff )
//STRIP001      {
//STRIP001          aParm.nNewWish += nTabDiff;
//STRIP001          if ( aParm.nNewWish < 0 )
//STRIP001              aParm.nNewWish = USHRT_MAX; //Uuups! Eine Rolle rueckwaerts.
//STRIP001          SwFmtFrmSize aSz( pFmt->GetFrmSize() );
//STRIP001          if ( aSz.GetWidth() != aParm.nNewWish )
//STRIP001          {
//STRIP001              aSz.SetWidth( aParm.nNewWish );
//STRIP001              aSz.SetWidthPercent( 0 );
//STRIP001              pFmt->SetAttr( aSz );
//STRIP001          }
//STRIP001      }
//STRIP001      UnlockModify();
//STRIP001  }
//STRIP001
//STRIP001 //MA 26. Aug. 98: #55469# Wozu das wohl mal gut war.
//STRIP001 //   if( rNew.Count() )
//STRIP001  {
//STRIP001      if ( bCurRowOnly )
//STRIP001      {
//STRIP001          //Um die aktuelle Zeile anzupassen muessen wir analog zu dem
//STRIP001          //Verfahren zum fuellen der TabCols (siehe GetTabCols()) die
//STRIP001          //Boxen der aktuellen Zeile abklappern.
//STRIP001          //Leider muessen wir auch hier dafuer sorgen, dass die Boxen von
//STRIP001          //hinten nach vorne bzw. von innen nach aussen veraendert werden.
//STRIP001          //Der beste Weg hierzu scheint mir darin zu liegen die
//STRIP001          //entsprechenden Boxen in einem PtrArray vorzumerken.
//STRIP001
//STRIP001          const SwTableBoxes &rBoxes = pStart->GetUpper()->GetTabBoxes();
//STRIP001          for ( USHORT i = 0; i < rBoxes.Count(); ++i )
//STRIP001              ::lcl_ProcessBoxPtr( rBoxes[i], aParm.aBoxArr, FALSE );
//STRIP001
//STRIP001          const SwTableLine *pLine = pStart->GetUpper()->GetUpper() ?
//STRIP001                                  pStart->GetUpper()->GetUpper()->GetUpper() : 0;
//STRIP001          const SwTableBox  *pExcl = pStart->GetUpper()->GetUpper();
//STRIP001          while ( pLine )
//STRIP001          {
//STRIP001              const SwTableBoxes &rBoxes = pLine->GetTabBoxes();
//STRIP001              BOOL bBefore = TRUE;
//STRIP001              for ( USHORT i = 0; i < rBoxes.Count(); ++i )
//STRIP001              {
//STRIP001                  if ( rBoxes[i] != pExcl )
//STRIP001                      ::lcl_ProcessBoxPtr( rBoxes[i], aParm.aBoxArr, bBefore );
//STRIP001                  else
//STRIP001                      bBefore = FALSE;
//STRIP001              }
//STRIP001              pExcl = pLine->GetUpper();
//STRIP001              pLine = pLine->GetUpper() ? pLine->GetUpper()->GetUpper() : 0;
//STRIP001          }
//STRIP001          //Nachdem wir haufenweise Boxen (hoffentlich alle und in der richtigen
//STRIP001          //Reihenfolge) eingetragen haben, brauchen diese nur noch rueckwaerts
//STRIP001          //verarbeitet zu werden.
//STRIP001          for ( int j = aParm.aBoxArr.Count()-1; j >= 0; --j )
//STRIP001          {
//STRIP001              SwTableBox *pBox = (SwTableBox*)aParm.aBoxArr[j];
//STRIP001              ::lcl_ProcessBoxSet( pBox, aParm );
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {   //Die gesamte Tabelle anzupassen ist 'einfach'.
//STRIP001          //Es werden alle Boxen, die keine Lines mehr enthalten angepasst.
//STRIP001          //Diese Boxen passen alle uebergeordneten Boxen entsprechend mit an.
//STRIP001          //Um uns nicht selbst hereinzulegen muss natuerlich rueckwaerst
//STRIP001          //gearbeitet werden!
//STRIP001          SwTableLines &rLines = GetTabLines();
//STRIP001          for ( int i = rLines.Count()-1; i >= 0; --i )
//STRIP001              ::lcl_ProcessLine( rLines[i], aParm );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001 #ifndef PRODUCT
//STRIP001  {
//STRIP001 // steht im tblrwcl.cxx
//STRIP001 extern void _CheckBoxWidth( const SwTableLine&, SwTwips );
//STRIP001      // checke doch mal ob die Tabellen korrekte Breiten haben
//STRIP001      SwTwips nSize = GetFrmFmt()->GetFrmSize().GetWidth();
//STRIP001      for( USHORT n = 0; n < aLines.Count(); ++n  )
//STRIP001          _CheckBoxWidth( *aLines[ n ], nSize );
//STRIP001  }
//STRIP001 #endif
//STRIP001 }

/*************************************************************************
|*
|*  const SwTableBox* SwTable::GetTblBox( const Strn¡ng& rName ) const
|*      gebe den Pointer auf die benannte Box zurueck.
|*
|*  Ersterstellung      JP 30. Jun. 93
|*  Letzte Aenderung    JP 30. Jun. 93
|*
|*************************************************************************/
/*N*/ USHORT SwTable::_GetBoxNum( String& rStr, BOOL bFirst )
/*N*/ {
/*N*/   USHORT nRet = 0;
/*N*/   xub_StrLen nPos = 0;
/*N*/   if( bFirst )
/*N*/   {
/*N*/       // die 1. ist mit Buchstaben addressiert!
/*N*/       sal_Unicode cChar;
/*N*/       BOOL bFirst = TRUE;
/*N*/       while( 0 != ( cChar = rStr.GetChar( nPos )) &&
/*N*/              ( (cChar >= 'A' && cChar <= 'Z') ||
/*N*/                (cChar >= 'a' && cChar <= 'z') ) )
/*N*/       {
/*N*/           if( (cChar -= 'A') >= 26 )
/*?*/               cChar -= 'a' - '[';
/*N*/           if( bFirst )
/*N*/               bFirst = FALSE;
/*N*/           else
/*?*/               ++nRet;
/*N*/           nRet = nRet * 52 + cChar;
/*N*/           ++nPos;
/*N*/       }
/*N*/       rStr.Erase( 0, nPos );      // Zeichen aus dem String loeschen
/*N*/   }
/*N*/   else if( STRING_NOTFOUND == ( nPos = rStr.Search( aDotStr ) ))
/*N*/   {
/*N*/       nRet = rStr.ToInt32();
/*N*/       rStr.Erase();
/*N*/   }
/*N*/   else
/*N*/   {
/*?*/       nRet = rStr.Copy( 0, nPos ).ToInt32();
/*?*/       rStr.Erase( 0, nPos+1 );
/*N*/   }
/*N*/   return nRet;
/*N*/ }

/*N*/ const SwTableBox* SwTable::GetTblBox( const String& rName ) const
/*N*/ {
/*N*/   const SwTableBox* pBox = 0;
/*N*/   const SwTableLine* pLine;
/*N*/   const SwTableLines* pLines;
/*N*/   const SwTableBoxes* pBoxes;
/*N*/
/*N*/   USHORT nLine, nBox;
/*N*/   String aNm( rName );
/*N*/   while( aNm.Len() )
/*N*/   {
/*N*/       nBox = SwTable::_GetBoxNum( aNm, 0 == pBox );
/*N*/       // erste Box ?
/*N*/       if( !pBox )
/*N*/           pLines = &GetTabLines();
/*N*/       else
/*N*/       {
/*?*/           pLines = &pBox->GetTabLines();
/*?*/           if( nBox )
/*?*/               --nBox;
/*N*/       }

/*N*/       nLine = SwTable::_GetBoxNum( aNm );
/*N*/
/*N*/       // bestimme die Line
/*N*/       if( !nLine || nLine > pLines->Count() )
/*N*/           return 0;
/*N*/       pLine = (*pLines)[ nLine-1 ];
/*N*/
/*N*/       // bestimme die Box
/*N*/       pBoxes = &pLine->GetTabBoxes();
/*N*/       if( nBox >= pBoxes->Count() )
/*N*/           return 0;
/*N*/       pBox = (*pBoxes)[ nBox ];
/*N*/   }

    // abpruefen, ob die gefundene Box auch wirklich eine Inhaltstragende
    // Box ist ??
/*N*/   if( pBox && !pBox->GetSttNd() )
/*N*/   {
/*?*/       ASSERT( FALSE, "Box ohne Inhalt, suche die naechste !!" );
/*?*/       // "herunterfallen lassen" bis zur ersten Box
/*?*/       while( pBox->GetTabLines().Count() )
/*?*/           pBox = pBox->GetTabLines()[0]->GetTabBoxes()[0];
/*N*/   }
/*N*/   return pBox;
/*N*/ }

/*M*/ SwTableBox* SwTable::GetTblBox( ULONG nSttIdx )
/*M*/ {
/*M*/   //MA: Zur Optimierung nicht immer umstaendlich das ganze SortArray abhuenern.
/*M*/     //OS: #102675# converting text to table tries und certain conditions
/*M*/     // to ask for a table box of a table that is not yet having a format
/*M*/     if(!GetFrmFmt())
/*M*/         return 0;
/*M*/     SwTableBox *pRet = 0;
/*M*/     SwNodes &rNds = GetFrmFmt()->GetDoc()->GetNodes();
/*M*/   ULONG nIndex;
/*M*/   SwCntntNode *pCNd = 0;
/*M*/
/*M*/   for ( nIndex = nSttIdx + 1; nIndex < rNds.Count() &&
/*M*/                               0 == (pCNd = rNds[nIndex]->GetCntntNode());
/*M*/                               ++nIndex )
/*M*/       /* do nothing */;
/*M*/
/*M*/   if ( pCNd )
/*M*/   {
/*M*/       SwClientIter aIter( *pCNd );
/*M*/       SwFrm *pFrm = (SwFrm*)aIter.First( TYPE(SwFrm) );
/*M*/       while ( pFrm && !pFrm->IsCellFrm() )
/*M*/           pFrm = pFrm->GetUpper();
/*M*/       if ( pFrm )
/*M*/           pRet = (SwTableBox*)((SwCellFrm*)pFrm)->GetTabBox();
/*M*/   }
/*M*/
/*M*/   //Falls es das Layout noch nicht gibt oder sonstwie etwas schieft geht.
/*M*/   if ( !pRet )
/*M*/   {
/*M*/       for( USHORT n = aSortCntBoxes.Count(); n; )
/*M*/           if( aSortCntBoxes[ --n ]->GetSttIdx() == nSttIdx )
/*M*/               return aSortCntBoxes[ n ];
/*M*/   }
/*M*/   return pRet;
/*M*/ }

/*N*/ BOOL SwTable::IsTblComplex() const
/*N*/ {
/*N*/   // returnt TRUE wenn sich in der Tabelle Verschachtelungen befinden
/*N*/   // steht eine Box nicht in der obersten Line, da wurde gesplittet/
/*N*/   // gemergt und die Struktur ist komplexer.
/*N*/   for( USHORT n = 0; n < aSortCntBoxes.Count(); ++n )
/*N*/       if( aSortCntBoxes[ n ]->GetUpper()->GetUpper() )
/*N*/           return TRUE;
/*N*/   return FALSE;
/*N*/ }



/*************************************************************************
|*
|*  SwTableLine::SwTableLine()
|*
|*  Ersterstellung      MA 09. Mar. 93
|*  Letzte Aenderung    MA 09. Mar. 93
|*
|*************************************************************************/
/*N*/ SwTableLine::SwTableLine( SwTableLineFmt *pFmt, USHORT nBoxes,
/*N*/                           SwTableBox *pUp )
/*N*/   : SwClient( pFmt ),
/*N*/   aBoxes( (BYTE)nBoxes, 1 ),
/*N*/   pUpper( pUp )
/*N*/ {
/*N*/ }

/*N*/ SwTableLine::~SwTableLine()
/*N*/ {
/*N*/   // ist die TabelleLine der letzte Client im FrameFormat, kann dieses
/*N*/   // geloescht werden
/*N*/   SwModify* pMod = GetFrmFmt();
/*N*/   pMod->Remove( this );               // austragen,
/*N*/   if( !pMod->GetDepends() )
/*N*/       delete pMod;    // und loeschen
/*N*/ }

/*************************************************************************
|*
|*  SwTableLine::ClaimFrmFmt(), ChgFrmFmt()
|*
|*  Ersterstellung      MA 03. May. 93
|*  Letzte Aenderung    MA 07. Feb. 96
|*
|*************************************************************************/
/*N*/ SwFrmFmt* SwTableLine::ClaimFrmFmt()
/*N*/ {
/*N*/   //Wenn noch andere TableLines ausser mir selbst an dem FrmFmt haengen,
/*N*/   //sehe ich mich leider gezwungen mir ein eingenes zu machen und mich
/*N*/   //bei diesem anzumelden.
/*N*/   SwTableLineFmt *pOld = (SwTableLineFmt*)GetFrmFmt();
/*N*/   SwClientIter aIter( *pOld );
/*N*/
/*N*/   SwClient* pLast;
/*N*/
/*N*/   for( pLast = aIter.First( TYPE( SwTableLine )); pLast && pLast == this;
/*N*/       pLast = aIter.Next() )
/*N*/       ;
/*N*/
/*N*/   if( pLast )
/*N*/   {
/*N*/       SwTableLineFmt *pNewFmt = pOld->GetDoc()->MakeTableLineFmt();
/*N*/       *pNewFmt = *pOld;
/*N*/
/*N*/       //Erstmal die Frms ummelden.
/*N*/       for( pLast = aIter.First( TYPE( SwFrm ) ); pLast; pLast = aIter.Next() )
/*N*/           if( ((SwRowFrm*)pLast)->GetTabLine() == this )
/*?*/               pNewFmt->Add( pLast );
/*N*/
/*N*/       //Jetzt noch mich selbst ummelden.
/*N*/       pNewFmt->Add( this );
/*N*/       pOld = pNewFmt;
/*N*/   }
/*N*/
/*N*/   return pOld;
/*N*/ }

//STRIP001 void SwTableLine::ChgFrmFmt( SwTableLineFmt *pNewFmt )
//STRIP001 {
//STRIP001  SwFrmFmt *pOld = GetFrmFmt();
//STRIP001  SwClientIter aIter( *pOld );
//STRIP001  SwClient* pLast;
//STRIP001
//STRIP001  //Erstmal die Frms ummelden.
//STRIP001  for( pLast = aIter.First( TYPE( SwFrm ) ); pLast; pLast = aIter.Next() )
//STRIP001  {
//STRIP001      SwRowFrm *pRow = (SwRowFrm*)pLast;
//STRIP001      if( pRow->GetTabLine() == this )
//STRIP001      {
//STRIP001          pNewFmt->Add( pLast );
//STRIP001          pRow->InvalidateSize();
//STRIP001          pRow->_InvalidatePrt();
//STRIP001          pRow->SetCompletePaint();
//STRIP001          pRow->ReinitializeFrmSizeAttrFlags();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  //Jetzt noch mich selbst ummelden.
//STRIP001  pNewFmt->Add( this );
//STRIP001
//STRIP001  if ( !aIter.GoStart() )
//STRIP001      delete pOld;
//STRIP001 }

//STRIP001 SwRect SwTableLine::GetLineRect( const BOOL bPrtArea ) const
//STRIP001 {
//STRIP001  SwRect aRect;
//STRIP001  SwClientIter aIter( *GetFrmFmt() );
//STRIP001  for( SwClient* pLast = aIter.First( TYPE( SwFrm ) ); pLast;
//STRIP001          pLast = aIter.Next() )
//STRIP001      if( ((SwRowFrm*)pLast)->GetTabLine() == this )
//STRIP001      {
//STRIP001          aRect = bPrtArea ? ((SwRowFrm*)pLast)->Prt()
//STRIP001                           : ((SwRowFrm*)pLast)->Frm();
//STRIP001          break;
//STRIP001      }
//STRIP001  return aRect;
//STRIP001 }

/*************************************************************************
|*
|*  SwTableBox::SwTableBox()
|*
|*  Ersterstellung      MA 04. May. 93
|*  Letzte Aenderung    MA 04. May. 93
|*
|*************************************************************************/
/*N*/ SwTableBox::SwTableBox( SwTableBoxFmt* pFmt, USHORT nLines, SwTableLine *pUp )
/*N*/   : SwClient( 0 ),
/*N*/   aLines( (BYTE)nLines, 1 ),
/*N*/   pSttNd( 0 ),
/*N*/   pUpper( pUp ),
/*N*/   pImpl( 0 )
/*N*/ {
/*N*/   CheckBoxFmt( pFmt )->Add( this );
/*N*/ }

/*N*/ SwTableBox::SwTableBox( SwTableBoxFmt* pFmt, const SwNodeIndex &rIdx,
/*N*/                       SwTableLine *pUp )
/*N*/   : SwClient( 0 ),
/*N*/   aLines( 0, 0 ),
/*N*/   pUpper( pUp ),
/*N*/   pImpl( 0 )
/*N*/ {
/*N*/   SwDoc* pDoc = pFmt->GetDoc();
/*N*/   CheckBoxFmt( pFmt )->Add( this );
/*N*/
/*N*/   pSttNd = pDoc->GetNodes()[ rIdx ]->GetStartNode();
/*N*/
/*N*/   // an der Table eintragen
/*N*/   const SwTableNode* pTblNd = pSttNd->FindTableNode();
/*N*/   ASSERT( pTblNd, "in welcher Tabelle steht denn die Box?" );
/*N*/   SwTableSortBoxes& rSrtArr = (SwTableSortBoxes&)pTblNd->GetTable().
/*N*/                               GetTabSortBoxes();
/*N*/   SwTableBox* p = this;   // error: &this
/*N*/   rSrtArr.Insert( p );        // eintragen
/*N*/ }

/*N*/ SwTableBox::SwTableBox( SwTableBoxFmt* pFmt, const SwStartNode& rSttNd, SwTableLine *pUp ) :
/*N*/   SwClient( 0 ),
/*N*/   aLines( 0, 0 ),
/*N*/   pUpper( pUp ),
/*N*/   pImpl( 0 ),
/*N*/   pSttNd( &rSttNd )
/*N*/ {
/*N*/   SwDoc* pDoc = pFmt->GetDoc();
/*N*/   CheckBoxFmt( pFmt )->Add( this );
/*N*/
/*N*/   // an der Table eintragen
/*N*/   const SwTableNode* pTblNd = pSttNd->FindTableNode();
/*N*/   ASSERT( pTblNd, "in welcher Tabelle steht denn die Box?" );
/*N*/   SwTableSortBoxes& rSrtArr = (SwTableSortBoxes&)pTblNd->GetTable().
/*N*/                               GetTabSortBoxes();
/*N*/   SwTableBox* p = this;   // error: &this
/*N*/   rSrtArr.Insert( p );        // eintragen
/*N*/ }

/*N*/ SwTableBox::~SwTableBox()
/*N*/ {
/*N*/   // Inhaltstragende Box ?
/*N*/   if( !GetFrmFmt()->GetDoc()->IsInDtor() && pSttNd )
/*N*/   {
/*N*/       // an der Table austragen
/*?*/       const SwTableNode* pTblNd = pSttNd->FindTableNode();
/*?*/       ASSERT( pTblNd, "in welcher Tabelle steht denn die Box?" );
/*?*/       SwTableSortBoxes& rSrtArr = (SwTableSortBoxes&)pTblNd->GetTable().
/*?*/                                   GetTabSortBoxes();
/*?*/       SwTableBox *p = this;   // error: &this
/*?*/       rSrtArr.Remove( p );        // austragen
/*N*/   }
/*N*/
/*N*/   // ist die TabelleBox der letzte Client im FrameFormat, kann dieses
/*N*/   // geloescht werden
/*N*/   SwModify* pMod = GetFrmFmt();
/*N*/   pMod->Remove( this );               // austragen,
/*N*/   if( !pMod->GetDepends() )
/*N*/       delete pMod;    // und loeschen
/*N*/
/*N*/   delete pImpl;
/*N*/ }

/*N*/ SwTableBoxFmt* SwTableBox::CheckBoxFmt( SwTableBoxFmt* pFmt )
/*N*/ {
    // sollte das Format eine Formel oder einen Value tragen, dann muss die
    // Box alleine am Format haengen. Ggfs. muss ein neues angelegt werden.
/*N*/   if( SFX_ITEM_SET == pFmt->GetItemState( RES_BOXATR_VALUE, FALSE ) ||
/*N*/       SFX_ITEM_SET == pFmt->GetItemState( RES_BOXATR_FORMULA, FALSE ) )
/*N*/   {
/*N*/       SwClient* pOther = SwClientIter( *pFmt ).First( TYPE( SwTableBox ));
/*N*/       if( pOther )
/*N*/       {
/*?*/           SwTableBoxFmt* pNewFmt = pFmt->GetDoc()->MakeTableBoxFmt();
/*?*/           pNewFmt->LockModify();
/*?*/           *pNewFmt = *pFmt;
/*?*/
/*?*/           // Values und Formeln entfernen
/*?*/           pNewFmt->ResetAttr( RES_BOXATR_FORMULA, RES_BOXATR_VALUE );
/*?*/           pNewFmt->UnlockModify();
/*?*/
/*?*/           pFmt = pNewFmt;
/*N*/       }
/*N*/   }
/*N*/   return pFmt;
/*N*/ }

/*************************************************************************
|*
|*  SwTableBox::ClaimFrmFmt(), ChgFrmFmt()
|*
|*  Ersterstellung      MA 04. May. 93
|*  Letzte Aenderung    MA 07. Feb. 96
|*
|*************************************************************************/
/*N*/ SwFrmFmt* SwTableBox::ClaimFrmFmt()
/*N*/ {
/*N*/   //Wenn noch andere TableBoxen ausser mir selbst an dem FrmFmt haengen,
/*N*/   //sehe ich mich leider gezwungen mir ein eingenes zu machen und mich
/*N*/   //bei diesem anzumelden.
/*N*/   SwTableBoxFmt *pOld = (SwTableBoxFmt*)GetFrmFmt();
/*N*/   SwClientIter aIter( *pOld );
/*N*/   SwClient* pLast;
/*N*/
/*N*/   for( pLast = aIter.First( TYPE( SwTableBox )); pLast && pLast == this;
/*N*/       pLast = aIter.Next() )
/*N*/       ;
/*N*/
/*N*/   if( pLast )
/*N*/   {
/*N*/       SwTableBoxFmt* pNewFmt = pOld->GetDoc()->MakeTableBoxFmt();
/*N*/
/*N*/       pNewFmt->LockModify();
/*N*/       *pNewFmt = *pOld;
/*N*/
/*N*/       // Values und Formeln nie kopieren
/*N*/       pNewFmt->ResetAttr( RES_BOXATR_FORMULA, RES_BOXATR_VALUE );
/*N*/       pNewFmt->UnlockModify();
/*N*/
/*N*/       //Erstmal die Frms ummelden.
/*N*/       for( pLast = aIter.First( TYPE( SwFrm ) ); pLast; pLast = aIter.Next() )
/*N*/           if( ((SwCellFrm*)pLast)->GetTabBox() == this )
/*N*/               pNewFmt->Add( pLast );
/*N*/
/*N*/       //Jetzt noch mich selbst ummelden.
/*N*/       pNewFmt->Add( this );
/*N*/       pOld = pNewFmt;
/*N*/   }
/*N*/   return pOld;
/*N*/ }

/*N*/ void SwTableBox::ChgFrmFmt( SwTableBoxFmt* pNewFmt )
/*N*/ {
/*N*/   SwFrmFmt *pOld = GetFrmFmt();
/*N*/   SwClientIter aIter( *pOld );
/*N*/   SwClient* pLast;
/*N*/
/*N*/   //Erstmal die Frms ummelden.
/*N*/   for( pLast = aIter.First( TYPE( SwFrm ) ); pLast; pLast = aIter.Next() )
/*N*/   {
/*N*/       SwCellFrm *pCell = (SwCellFrm*)pLast;
/*N*/       if( pCell->GetTabBox() == this )
/*N*/       {
/*?*/           pNewFmt->Add( pLast );
/*?*/           pCell->InvalidateSize();
/*?*/           pCell->_InvalidatePrt();
/*?*/           pCell->SetCompletePaint();
/*N*/       }
/*N*/   }
/*N*/
/*N*/   //Jetzt noch mich selbst ummelden.
/*N*/   pNewFmt->Add( this );
/*N*/
/*N*/   if( !aIter.GoStart() )
/*?*/       delete pOld;
/*N*/ }

/*************************************************************************
|*
|*  String SwTableBox::GetName() const
|*      gebe den Namen dieser Box zurueck. Dieser wird dynamisch bestimmt
|*      und ergibt sich aus der Position in den Lines/Boxen/Tabelle
|*
|*  Ersterstellung      JP 30. Jun. 93
|*  Letzte Aenderung    JP 30. Jun. 93
|*
|*************************************************************************/
/*N*/ void lcl_GetTblBoxColStr( USHORT nCol, String& rNm )
/*N*/ {
/*N*/   const USHORT coDiff = 52;   // 'A'-'Z' 'a' - 'z'
/*N*/   register USHORT nCalc;
/*N*/
/*N*/   do {
/*N*/       nCalc = nCol % coDiff;
/*N*/       if( nCalc >= 26 )
/*N*/           rNm.Insert( sal_Unicode('a' - 26 + nCalc ), 0 );
/*N*/       else
/*N*/           rNm.Insert( sal_Unicode('A' + nCalc ), 0 );
/*N*/
/*N*/       if( !(nCol -= nCalc) )
/*N*/           break;
/*N*/       nCol /= coDiff;
/*N*/       --nCol;
/*N*/   } while( 1 );
/*N*/ }

/*N*/ String SwTableBox::GetName() const
/*N*/ {
/*N*/   if( !pSttNd )       // keine Content Box ??
/*N*/   {
/*N*/       // die naechste erste Box suchen ??
/*?*/       return aEmptyStr;
/*N*/   }

/*N*/   const SwTable& rTbl = pSttNd->FindTableNode()->GetTable();
/*N*/   register USHORT nPos;
/*N*/   String sNm, sTmp;
/*N*/   const SwTableBox* pBox = this;
/*N*/   do {
/*N*/       const SwTableBoxes* pBoxes = &pBox->GetUpper()->GetTabBoxes();
/*N*/       const SwTableLine* pLine = pBox->GetUpper();
/*N*/       // auf oberstere Ebene ?
/*N*/       const SwTableLines* pLines = pLine->GetUpper()
/*N*/               ? &pLine->GetUpper()->GetTabLines() : &rTbl.GetTabLines();
/*N*/
/*N*/       sTmp = String::CreateFromInt32( nPos = pLines->GetPos( pLine ) + 1 );
/*N*/       if( sNm.Len() )
/*N*/           sNm.Insert( aDotStr, 0 ).Insert( sTmp, 0 );
/*N*/       else
/*N*/           sNm = sTmp;
/*N*/
/*N*/       sTmp = String::CreateFromInt32(( nPos = pBoxes->GetPos( pBox )) + 1 );
/*N*/       if( 0 != ( pBox = pLine->GetUpper()) )
/*N*/           sNm.Insert( aDotStr, 0 ).Insert( sTmp, 0 );
/*N*/       else
/*N*/           ::binfilter::lcl_GetTblBoxColStr( nPos, sNm );
/*N*/
/*N*/   } while( pBox );
/*N*/   return sNm;
/*N*/ }

        // gebe den Zellnamen zu der angebenen Row/Col zurueck. Das ist
        // nur fuer ausgeglichene Tabellen interessant, weil diese keine
        // "Sub"Boxen kennen. Es wird z.B. aus (0,0) ein "A1".
//STRIP001 String SwTable::GetBoxName( USHORT nRow, USHORT nCol )
//STRIP001 {
//STRIP001  String sNm;
//STRIP001  ::lcl_GetTblBoxColStr( nCol, sNm );
//STRIP001  sNm += String::CreateFromInt32( nRow + 1 );
//STRIP001  return sNm;
//STRIP001 }

/*N*/ BOOL SwTableBox::IsInHeadline( const SwTable* pTbl ) const
/*N*/ {
/*N*/   if( !GetUpper() )           // sollte nur beim Merge vorkommen.
/*N*/       return FALSE;
/*N*/
/*N*/   if( !pTbl )
/*?*/       pTbl = &pSttNd->FindTableNode()->GetTable();
/*N*/
/*N*/   const SwTableLine* pLine = GetUpper();
/*N*/   while( pLine->GetUpper() )
/*?*/       pLine = pLine->GetUpper()->GetUpper();

    // Headerline?
/*N*/   return pTbl->GetTabLines()[ 0 ] == pLine;
/*N*/ }

#ifndef PRODUCT

/*N*/ ULONG SwTableBox::GetSttIdx() const
/*N*/ {
/*N*/   return pSttNd ? pSttNd->GetIndex() : 0;
/*N*/ }
#endif

    // erfrage vom Client Informationen
/*N*/ BOOL SwTable::GetInfo( SfxPoolItem& rInfo ) const
/*N*/ {
/*N*/   switch( rInfo.Which() )
/*N*/   {
/*N*/   case RES_AUTOFMT_DOCNODE:
/*N*/       if( aSortCntBoxes.Count() &&
/*N*/           &aSortCntBoxes[ 0 ]->GetSttNd()->GetNodes() ==
/*N*/           ((SwAutoFmtGetDocNode&)rInfo).pNodes )
/*N*/       {
/*N*/           SwNodeIndex aIdx( *aSortCntBoxes[ 0 ]->GetSttNd() );
/*N*/           ((SwAutoFmtGetDocNode&)rInfo).pCntntNode =
/*N*/                           GetFrmFmt()->GetDoc()->GetNodes().GoNext( &aIdx );
/*N*/           return FALSE;
/*N*/       }
/*N*/       break;
/*N*/
/*N*/   case RES_FINDNEARESTNODE:
/*?*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001   if( GetFrmFmt() && ((SwFmtPageDesc&)GetFrmFmt()->GetAttr(
//STRIP001 /*?*/            RES_PAGEDESC )).GetPageDesc() &&
//STRIP001 /*?*/            aSortCntBoxes.Count() &&
//STRIP001 /*?*/            aSortCntBoxes[ 0 ]->GetSttNd()->GetNodes().IsDocNodes() )
//STRIP001 /*?*/            ((SwFindNearestNode&)rInfo).CheckNode( *
//STRIP001 /*?*/                aSortCntBoxes[ 0 ]->GetSttNd()->FindTableNode() );
/*?*/       break;
/*?*/
/*?*/   case RES_CONTENT_VISIBLE:
/*?*/       {
/*?*/           ((SwPtrMsgPoolItem&)rInfo).pObject =
/*?*/               SwClientIter( *GetFrmFmt() ).First( TYPE(SwFrm) );
/*?*/       }
/*?*/       return FALSE;
/*?*/   }
/*?*/   return TRUE;
/*N*/ }

/*N*/ SwTable* SwTable::FindTable( SwFrmFmt* pFmt )
/*N*/ {
/*N*/   return pFmt ? (SwTable*)SwClientIter( *pFmt ).First( TYPE(SwTable) ) : 0;
/*N*/ }

/*N*/ SwTableNode* SwTable::GetTableNode() const
/*N*/ {
/*N*/   return GetTabSortBoxes().Count()
/*N*/       ? (SwTableNode*)GetTabSortBoxes()[ 0 ]->GetSttNd()->FindTableNode()
/*N*/       : 0;
/*N*/ }

/*N*/ void SwTable::SetRefObject( SwServerObject* pObj )
/*N*/ {
/*N*/   if( refObj.Is() )
/*N*/       refObj->Closed();
/*N*/
/*N*/   refObj = pObj;
/*N*/ }


//STRIP001 void SwTable::SetHTMLTableLayout( SwHTMLTableLayout *p )
//STRIP001 {
//STRIP001  delete pHTMLLayout;
//STRIP001  pHTMLLayout = p;
//STRIP001 }


//STRIP001 void ChgTextToNum( SwTableBox& rBox, const String& rTxt, const Color* pCol,
//STRIP001                  BOOL bChgAlign )
//STRIP001 {
//STRIP001  ULONG nNdPos = rBox.IsValidNumTxtNd( TRUE );
//STRIP001  if( ULONG_MAX != nNdPos )
//STRIP001  {
//STRIP001      SwDoc* pDoc = rBox.GetFrmFmt()->GetDoc();
//STRIP001      SwTxtNode* pTNd = pDoc->GetNodes()[ nNdPos ]->GetTxtNode();
//STRIP001      const SfxPoolItem* pItem;
//STRIP001
//STRIP001      // Ausrichtung umsetzen
//STRIP001      if( bChgAlign )
//STRIP001      {
//STRIP001          pItem = &pTNd->SwCntntNode::GetAttr( RES_PARATR_ADJUST );
//STRIP001          SvxAdjust eAdjust = ((SvxAdjustItem*)pItem)->GetAdjust();
//STRIP001          if( SVX_ADJUST_LEFT == eAdjust || SVX_ADJUST_BLOCK == eAdjust )
//STRIP001          {
//STRIP001              SvxAdjustItem aAdjust( *(SvxAdjustItem*)pItem );
//STRIP001              aAdjust.SetAdjust( SVX_ADJUST_RIGHT );
//STRIP001              pTNd->SwCntntNode::SetAttr( aAdjust );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      // Farbe umsetzen oder "Benutzer Farbe" sichern
//STRIP001      if( !pTNd->GetpSwAttrSet() || SFX_ITEM_SET != pTNd->GetpSwAttrSet()->
//STRIP001          GetItemState( RES_CHRATR_COLOR, FALSE, &pItem ))
//STRIP001          pItem = 0;
//STRIP001
//STRIP001      const Color* pOldNumFmtColor = rBox.GetSaveNumFmtColor();
//STRIP001      const Color* pNewUserColor = pItem ? &((SvxColorItem*)pItem)->GetValue() : 0;
//STRIP001
//STRIP001      if( ( pNewUserColor && pOldNumFmtColor &&
//STRIP001              *pNewUserColor == *pOldNumFmtColor ) ||
//STRIP001          ( !pNewUserColor && !pOldNumFmtColor ))
//STRIP001      {
//STRIP001          // User Color nicht veraendern aktuellen Werte setzen
//STRIP001          // ggfs. die alte NumFmtColor loeschen
//STRIP001          if( pCol )
//STRIP001              // ggfs. die Farbe setzen
//STRIP001              pTNd->SwCntntNode::SetAttr( SvxColorItem( *pCol ));
//STRIP001          else if( pItem )
//STRIP001          {
//STRIP001              pNewUserColor = rBox.GetSaveUserColor();
//STRIP001              if( pNewUserColor )
//STRIP001                  pTNd->SwCntntNode::SetAttr( SvxColorItem( *pNewUserColor ));
//STRIP001              else
//STRIP001                  pTNd->SwCntntNode::ResetAttr( RES_CHRATR_COLOR );
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // User Color merken, ggfs. die NumFormat Color setzen, aber
//STRIP001          // nie die Farbe zurueck setzen
//STRIP001          rBox.SetSaveUserColor( pNewUserColor );
//STRIP001
//STRIP001          if( pCol )
//STRIP001              // ggfs. die Farbe setzen
//STRIP001              pTNd->SwCntntNode::SetAttr( SvxColorItem( *pCol ));
//STRIP001
//STRIP001      }
//STRIP001      rBox.SetSaveNumFmtColor( pCol );
//STRIP001
//STRIP001      if( pTNd->GetTxt() != rTxt )
//STRIP001      {
//STRIP001          // Text austauschen
//STRIP001          //JP 15.09.98: Bug 55741 - Tabs beibehalten (vorne und hinten!)
//STRIP001          const String& rOrig = pTNd->GetTxt();
//STRIP001          for( xub_StrLen n = 0; n < rOrig.Len() &&
//STRIP001                              '\x9' == rOrig.GetChar( n ); ++n )
//STRIP001              ;
//STRIP001          SwIndex aIdx( pTNd, n );
//STRIP001          for( n = rOrig.Len(); n && '\x9' == rOrig.GetChar( --n ); )
//STRIP001              ;
//STRIP001          n -= aIdx.GetIndex() - 1;
//STRIP001
//STRIP001          //JP 06.04.99: Bug 64321 - DontExpand-Flags vorm Austauschen
//STRIP001          //             zuruecksetzen, damit sie wieder aufgespannt werden
//STRIP001          {
//STRIP001              SwIndex aResetIdx( aIdx, n );
//STRIP001              pTNd->DontExpandFmt( aResetIdx, FALSE, FALSE );
//STRIP001          }
//STRIP001
//STRIP001             if( !pDoc->IsIgnoreRedline() && pDoc->GetRedlineTbl().Count() )
//STRIP001             {
//STRIP001                 pDoc->DeleteRedline( SwPaM( *pTNd, 0, *pTNd, rOrig.Len() ),
//STRIP001                                      sal_True );
//STRIP001             }
//STRIP001
//STRIP001          pTNd->Erase( aIdx, n, INS_EMPTYEXPAND );
//STRIP001          pTNd->Insert( rTxt, aIdx, INS_EMPTYEXPAND );
//STRIP001
//STRIP001             if( pDoc->IsRedlineOn() )
//STRIP001             {
//STRIP001                 pDoc->AppendRedline(
//STRIP001                     new SwRedline( REDLINE_INSERT,
//STRIP001                                    SwPaM( *pTNd, 0, *pTNd, rTxt.Len() ) ) );
//STRIP001             }
//STRIP001      }
//STRIP001
//STRIP001      // vertikale Ausrichtung umsetzen
//STRIP001      if( bChgAlign &&
//STRIP001          ( SFX_ITEM_SET != rBox.GetFrmFmt()->GetItemState(
//STRIP001              RES_VERT_ORIENT, TRUE, &pItem ) ||
//STRIP001              VERT_TOP == ((SwFmtVertOrient*)pItem)->GetVertOrient() ))
//STRIP001      {
//STRIP001          rBox.GetFrmFmt()->SetAttr( SwFmtVertOrient( 0, VERT_BOTTOM ));
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void ChgNumToText( SwTableBox& rBox, ULONG nFmt )
//STRIP001 {
//STRIP001  ULONG nNdPos = rBox.IsValidNumTxtNd( FALSE );
//STRIP001  if( ULONG_MAX != nNdPos )
//STRIP001  {
//STRIP001      SwDoc* pDoc = rBox.GetFrmFmt()->GetDoc();
//STRIP001      SwTxtNode* pTNd = pDoc->GetNodes()[ nNdPos ]->GetTxtNode();
//STRIP001      BOOL bChgAlign = pDoc->IsInsTblAlignNum();
//STRIP001      const SfxPoolItem* pItem;
//STRIP001
//STRIP001      Color* pCol = 0;
//STRIP001      if( NUMBERFORMAT_TEXT != nFmt )
//STRIP001      {
//STRIP001          // speziellen Textformat:
//STRIP001          String sTmp, sTxt( pTNd->GetTxt() );
//STRIP001          pDoc->GetNumberFormatter()->GetOutputString( sTxt, nFmt, sTmp, &pCol );
//STRIP001          if( sTxt != sTmp )
//STRIP001          {
//STRIP001              // Text austauschen
//STRIP001              SwIndex aIdx( pTNd, sTxt.Len() );
//STRIP001              //JP 06.04.99: Bug 64321 - DontExpand-Flags vorm Austauschen
//STRIP001              //             zuruecksetzen, damit sie wieder aufgespannt werden
//STRIP001              pTNd->DontExpandFmt( aIdx, FALSE, FALSE );
//STRIP001              aIdx = 0;
//STRIP001              pTNd->Erase( aIdx, STRING_LEN, INS_EMPTYEXPAND );
//STRIP001              pTNd->Insert( sTmp, aIdx, INS_EMPTYEXPAND );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      SwAttrSet* pAttrSet = pTNd->GetpSwAttrSet();
//STRIP001
//STRIP001      // Ausrichtung umsetzen
//STRIP001      if( bChgAlign && pAttrSet && SFX_ITEM_SET == pAttrSet->GetItemState(
//STRIP001          RES_PARATR_ADJUST, FALSE, &pItem ) &&
//STRIP001              SVX_ADJUST_RIGHT == ((SvxAdjustItem*)pItem)->GetAdjust() )
//STRIP001      {
//STRIP001          pTNd->SwCntntNode::SetAttr( SvxAdjustItem( SVX_ADJUST_LEFT ) );
//STRIP001      }
//STRIP001
//STRIP001      // Farbe umsetzen oder "Benutzer Farbe" sichern
//STRIP001      if( !pAttrSet || SFX_ITEM_SET != pAttrSet->
//STRIP001          GetItemState( RES_CHRATR_COLOR, FALSE, &pItem ))
//STRIP001          pItem = 0;
//STRIP001
//STRIP001      const Color* pOldNumFmtColor = rBox.GetSaveNumFmtColor();
//STRIP001      const Color* pNewUserColor = pItem ? &((SvxColorItem*)pItem)->GetValue() : 0;
//STRIP001
//STRIP001      if( ( pNewUserColor && pOldNumFmtColor &&
//STRIP001              *pNewUserColor == *pOldNumFmtColor ) ||
//STRIP001          ( !pNewUserColor && !pOldNumFmtColor ))
//STRIP001      {
//STRIP001          // User Color nicht veraendern aktuellen Werte setzen
//STRIP001          // ggfs. die alte NumFmtColor loeschen
//STRIP001          if( pCol )
//STRIP001              // ggfs. die Farbe setzen
//STRIP001              pTNd->SwCntntNode::SetAttr( SvxColorItem( *pCol ));
//STRIP001          else if( pItem )
//STRIP001          {
//STRIP001              pNewUserColor = rBox.GetSaveUserColor();
//STRIP001              if( pNewUserColor )
//STRIP001                  pTNd->SwCntntNode::SetAttr( SvxColorItem( *pNewUserColor ));
//STRIP001              else
//STRIP001                  pTNd->SwCntntNode::ResetAttr( RES_CHRATR_COLOR );
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          // User Color merken, ggfs. die NumFormat Color setzen, aber
//STRIP001          // nie die Farbe zurueck setzen
//STRIP001          rBox.SetSaveUserColor( pNewUserColor );
//STRIP001
//STRIP001          if( pCol )
//STRIP001              // ggfs. die Farbe setzen
//STRIP001              pTNd->SwCntntNode::SetAttr( SvxColorItem( *pCol ));
//STRIP001
//STRIP001      }
//STRIP001      rBox.SetSaveNumFmtColor( pCol );
//STRIP001
//STRIP001
//STRIP001      // vertikale Ausrichtung umsetzen
//STRIP001      if( bChgAlign &&
//STRIP001          SFX_ITEM_SET == rBox.GetFrmFmt()->GetItemState(
//STRIP001          RES_VERT_ORIENT, FALSE, &pItem ) &&
//STRIP001          VERT_BOTTOM == ((SwFmtVertOrient*)pItem)->GetVertOrient() )
//STRIP001      {
//STRIP001          rBox.GetFrmFmt()->SetAttr( SwFmtVertOrient( 0, VERT_TOP ));
//STRIP001      }
//STRIP001  }
//STRIP001 }

// zum Erkennen von Veraenderungen (haupts. TableBoxAttribute)
/*N*/ void SwTableBoxFmt::Modify( SfxPoolItem* pOld, SfxPoolItem* pNew )
/*N*/ {
/*N*/   if( !IsModifyLocked() && !IsInDocDTOR() )
/*N*/   {
/*N*/       const SwTblBoxNumFormat *pNewFmt = 0, *pOldFmt = 0;
/*N*/       const SwTblBoxFormula *pNewFml = 0, *pOldFml = 0;
/*N*/       const SwTblBoxValue *pNewVal = 0, *pOldVal = 0;
/*N*/       double aOldValue = 0;
/*N*/       ULONG nOldFmt = NUMBERFORMAT_TEXT;
/*N*/
/*N*/       SwAttrSetChg *pNewChgSet = 0,  *pOldChgSet = 0;
/*N*/
/*N*/       switch( pNew ? pNew->Which() : 0 )
/*N*/       {
/*N*/       case RES_ATTRSET_CHG:
/*N*/           {
/*N*/               const SfxItemSet& rSet = *((SwAttrSetChg*)pNew)->GetChgSet();
/*N*/               if( SFX_ITEM_SET == rSet.GetItemState( RES_BOXATR_FORMAT,
/*N*/                                   FALSE, (const SfxPoolItem**)&pNewFmt ) )
/*N*/                   nOldFmt = ((SwTblBoxNumFormat&)((SwAttrSetChg*)pOld)->
/*N*/                           GetChgSet()->Get( RES_BOXATR_FORMAT )).GetValue();
/*N*/               rSet.GetItemState( RES_BOXATR_FORMULA, FALSE,
/*N*/                                   (const SfxPoolItem**)&pNewFml );
/*N*/               if( SFX_ITEM_SET == rSet.GetItemState( RES_BOXATR_VALUE,
/*N*/                                   FALSE, (const SfxPoolItem**)&pNewVal ) )
/*N*/                   aOldValue = ((SwTblBoxValue&)((SwAttrSetChg*)pOld)->
/*N*/                           GetChgSet()->Get( RES_BOXATR_VALUE )).GetValue();
/*N*/           }
/*N*/           break;
/*N*/
/*N*/       case RES_BOXATR_FORMAT:
/*N*/           pNewFmt = (SwTblBoxNumFormat*)pNew;
/*N*/           nOldFmt = ((SwTblBoxNumFormat*)pOld)->GetValue();
/*N*/           break;
/*N*/       case RES_BOXATR_FORMULA:
/*N*/           pNewFml = (SwTblBoxFormula*)pNew;
/*N*/           break;
/*N*/       case RES_BOXATR_VALUE:
/*N*/           pNewVal = (SwTblBoxValue*)pNew;
/*N*/           aOldValue = ((SwTblBoxValue*)pOld)->GetValue();
/*N*/           break;
/*N*/       }
/*N*/
/*N*/       // es hat sich etwas getan und im Set ist noch irgendein BoxAttribut
/*N*/       // vorhanden!
/*N*/       if( pNewFmt || pNewFml || pNewVal )
/*N*/       {
/*N*/           GetDoc()->SetFieldsDirty( TRUE );
/*N*/
/*N*/           if( SFX_ITEM_SET == GetItemState( RES_BOXATR_FORMAT, FALSE ) ||
/*N*/               SFX_ITEM_SET == GetItemState( RES_BOXATR_VALUE, FALSE ) ||
/*N*/               SFX_ITEM_SET == GetItemState( RES_BOXATR_FORMULA, FALSE ) )
/*N*/           {
/*N*/               // die Box holen
/*N*/               SwClientIter aIter( *this );
/*N*/               SwTableBox* pBox = (SwTableBox*)aIter.First( TYPE( SwTableBox ) );
/*N*/               if( pBox )
/*N*/               {
/*?*/                   ASSERT( !aIter.Next(), "keine Box oder mehrere am Format" );
/*?*/
/*?*/                   ULONG nNewFmt;
/*?*/                   if( pNewFmt )
/*?*/                   {
/*?*/                       nNewFmt = pNewFmt->GetValue();
/*?*/                       // neu Formatieren
/*?*/                       // ist es neuer oder wurde der akt. entfernt?
/*?*/                       if( SFX_ITEM_SET != GetItemState( RES_BOXATR_VALUE, FALSE ))
/*?*/                           pNewFmt = 0;
/*?*/                   }
/*?*/                   else
/*?*/                   {
/*?*/                       // das akt. Item besorgen
/*?*/                       GetItemState( RES_BOXATR_FORMAT, FALSE,
/*?*/                                           (const SfxPoolItem**)&pNewFmt );
/*?*/                       nOldFmt = GetTblBoxNumFmt().GetValue();
/*?*/                       nNewFmt = pNewFmt ? pNewFmt->GetValue() : nOldFmt;
/*?*/                   }
/*?*/
/*?*/                   // ist es neuer oder wurde der akt. entfernt?
/*?*/                   if( pNewVal )
/*?*/                   {
/*?*/                       if( NUMBERFORMAT_TEXT != nNewFmt )
/*?*/                       {
/*?*/                           if( SFX_ITEM_SET == GetItemState(
/*?*/                                               RES_BOXATR_VALUE, FALSE ))
/*?*/                               nOldFmt = NUMBERFORMAT_TEXT;
/*?*/                           else
/*?*/                               nNewFmt = NUMBERFORMAT_TEXT;
/*?*/                       }
/*?*/                       else if( NUMBERFORMAT_TEXT == nNewFmt )
/*?*/                           nOldFmt = 0;
/*?*/                   }
/*?*/
/*?*/                   // Logik:
/*?*/                   // ValueAenderung:  -> "simuliere" eine FormatAenderung!
/*?*/                   // FormatAenderung:
/*?*/                   // Text -> !Text oder FormatAenderung:
/*?*/                   //          - Ausrichtung auf RECHTS, wenn LINKS oder Blocksatz
/*?*/                   //          - vertikale Ausrichtung auf UNTEN wenn OBEN oder nicht
/*?*/                   //              gesetzt ist.
/*?*/                   //          - Text ersetzen (Farbe?? neg. Zahlen ROT??)
/*?*/                   // !Text -> Text:
/*?*/                   //          - Ausrichtung auf LINKS, wenn RECHTS
/*?*/                   //          - vertikale Ausrichtung auf OEBN, wenn UNTEN gesetzt ist
/*?*/
/*?*/                   SvNumberFormatter* pNumFmtr = GetDoc()->GetNumberFormatter();
/*?*/                   BOOL bNewIsTxtFmt = pNumFmtr->IsTextFormat( nNewFmt ) ||
/*?*/                                       NUMBERFORMAT_TEXT == nNewFmt;
/*?*/
/*?*/                   if( !bNewIsTxtFmt && nOldFmt != nNewFmt || pNewFml )
/*?*/                   {
/*?*/               DBG_BF_ASSERT(0, "STRIP"); //STRIP001       BOOL bChgTxt = TRUE;
//STRIP001 /*?*/                        double fVal = 0;
//STRIP001 /*?*/                        if( !pNewVal && SFX_ITEM_SET != GetItemState(
//STRIP001 /*?*/                            RES_BOXATR_VALUE, FALSE, (const SfxPoolItem**)&pNewVal ))
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            // es wurde noch nie ein Wert gesetzt, dann versuche
//STRIP001 /*?*/                            DBG_BF_ASSERT(0, "STRIP"); //STRIP001 // doch mal den Inhalt auszuwerten
//STRIP001 /*?*/                            ULONG nNdPos = pBox->IsValidNumTxtNd( TRUE );
//STRIP001 /*?*/                            if( ULONG_MAX != nNdPos )
//STRIP001 /*?*/                            {
//STRIP001 /*?*/                                ULONG nTmpFmtIdx = nNewFmt;
//STRIP001 /*?*/                                String aTxt( GetDoc()->GetNodes()[ nNdPos ]
//STRIP001 /*?*/                                                ->GetTxtNode()->GetRedlineTxt());
//STRIP001 /*?*/                                if( !aTxt.Len() )
//STRIP001 /*?*/                                    bChgTxt = FALSE;
//STRIP001 /*?*/                                else
//STRIP001 /*?*/                                {
//STRIP001 /*?*/                                    //JP 15.09.98: Bug 55741 - Tabs beibehalten
//STRIP001 /*?*/                                    lcl_TabToBlankAtSttEnd( aTxt );
//STRIP001 /*?*/
//STRIP001 /*?*/                                    // JP 22.04.98: Bug 49659 -
//STRIP001 /*?*/                                    //          Sonderbehandlung fuer Prozent
//STRIP001 /*?*/                                    BOOL bIsNumFmt = FALSE;
//STRIP001 /*?*/                                    if( NUMBERFORMAT_PERCENT ==
//STRIP001 /*?*/                                        pNumFmtr->GetType( nNewFmt ))
//STRIP001 /*?*/                                    {
//STRIP001 /*?*/                                        ULONG nTmpFmt = 0;
//STRIP001 /*?*/                                        if( pNumFmtr->IsNumberFormat(
//STRIP001 /*?*/                                                    aTxt, nTmpFmt, fVal ))
//STRIP001 /*?*/                                        {
//STRIP001 /*?*/                                            if( NUMBERFORMAT_NUMBER ==
//STRIP001 /*?*/                                                pNumFmtr->GetType( nTmpFmt ))
//STRIP001 /*?*/                                                aTxt += '%';
//STRIP001 /*?*/
//STRIP001 /*?*/                                            bIsNumFmt = pNumFmtr->IsNumberFormat(
//STRIP001 /*?*/                                                        aTxt, nTmpFmtIdx, fVal );
//STRIP001 /*?*/                                        }
//STRIP001 /*?*/                                    }
//STRIP001 /*?*/                                    else
//STRIP001 /*?*/                                        bIsNumFmt = pNumFmtr->IsNumberFormat(
//STRIP001 /*?*/                                                        aTxt, nTmpFmtIdx, fVal );
//STRIP001 /*?*/
//STRIP001 /*?*/                                    if( bIsNumFmt )
//STRIP001 /*?*/                                    {
//STRIP001 /*?*/                                        // dann setze den Value direkt in den Set -
//STRIP001 /*?*/                                        // ohne Modify
//STRIP001 /*?*/                                        int bIsLockMod = IsModifyLocked();
//STRIP001 /*?*/                                        LockModify();
//STRIP001 /*?*/                                        SetAttr( SwTblBoxValue( fVal ));
//STRIP001 /*?*/                                        if( !bIsLockMod )
//STRIP001 /*?*/                                            UnlockModify();
//STRIP001 /*?*/                                    }
//STRIP001 /*?*/                                }
//STRIP001 /*?*/                            }
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                        else
//STRIP001 /*?*/                            fVal = pNewVal->GetValue();
//STRIP001 /*?*/
//STRIP001 /*?*/                        // den Inhalt mit dem neuen Wert Formtieren und in den Absatz
//STRIP001 /*?*/                        // schbreiben
//STRIP001 /*?*/                        Color* pCol = 0;
//STRIP001 /*?*/                        String sNewTxt;
//STRIP001 /*?*/                        if( DBL_MAX == fVal )
//STRIP001 /*?*/                            sNewTxt = ViewShell::GetShellRes()->aCalc_Error;
//STRIP001 /*?*/                        else
//STRIP001 /*?*/                        {
//STRIP001 /*?*/                            pNumFmtr->GetOutputString( fVal, nNewFmt, sNewTxt, &pCol );
//STRIP001 /*?*/
//STRIP001 /*?*/                            if( !bChgTxt )
//STRIP001 /*?*/                                sNewTxt.Erase();
//STRIP001 /*?*/                        }
//STRIP001 /*?*/
//STRIP001 /*?*/                        // ueber alle Boxen
//STRIP001 /*?*/                        ChgTextToNum( *pBox, sNewTxt, pCol,
//STRIP001 /*?*/                                        GetDoc()->IsInsTblAlignNum() );
//STRIP001 /*?*/
/*?*/                   }
/*?*/                   else if( bNewIsTxtFmt && nOldFmt != nNewFmt )
/*?*/                   {
/*?*/                       // auf jedenfall muessen jetzt die Formeln/Values
/*?*/                       // geloescht werden!
/*?*/   //                  LockModify();
/*?*/   //                  ResetAttr( RES_BOXATR_FORMULA, RES_BOXATR_VALUE );
/*?*/   //                  UnlockModify();
/*?*/
/*?*/
/*?*/                   DBG_BF_ASSERT(0, "STRIP"); //STRIP001   ChgNumToText( *pBox, nNewFmt );
/*?*/                   }
/*?*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   // Und die Basis-Klasse rufen
/*N*/   SwFrmFmt::Modify( pOld, pNew );
/*N*/ }

//STRIP001 BOOL SwTableBox::HasNumCntnt( double& rNum, ULONG& rFmtIndex,
//STRIP001                          BOOL& rIsEmptyTxtNd ) const
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  ULONG nNdPos = IsValidNumTxtNd( TRUE );
//STRIP001  if( ULONG_MAX != nNdPos )
//STRIP001  {
//STRIP001      String aTxt( pSttNd->GetNodes()[ nNdPos ]->GetTxtNode()->
//STRIP001                          GetRedlineTxt() );
//STRIP001      //JP 15.09.98: Bug 55741 - Tabs beibehalten
//STRIP001      lcl_TabToBlankAtSttEnd( aTxt );
//STRIP001      rIsEmptyTxtNd = 0 == aTxt.Len();
//STRIP001      SvNumberFormatter* pNumFmtr = GetFrmFmt()->GetDoc()->GetNumberFormatter();
//STRIP001
//STRIP001      const SfxPoolItem* pItem;
//STRIP001      if( SFX_ITEM_SET == GetFrmFmt()->GetItemState( RES_BOXATR_FORMAT,
//STRIP001              FALSE, &pItem ))
//STRIP001      {
//STRIP001          rFmtIndex = ((SwTblBoxNumFormat*)pItem)->GetValue();
//STRIP001          // JP 22.04.98: Bug 49659 - Sonderbehandlung fuer Prozent
//STRIP001          if( !rIsEmptyTxtNd &&
//STRIP001              NUMBERFORMAT_PERCENT == pNumFmtr->GetType( rFmtIndex ))
//STRIP001          {
//STRIP001              ULONG nTmpFmt = 0;
//STRIP001              if( pNumFmtr->IsNumberFormat( aTxt, nTmpFmt, rNum ) &&
//STRIP001                  NUMBERFORMAT_NUMBER == pNumFmtr->GetType( nTmpFmt ))
//STRIP001                  aTxt += '%';
//STRIP001          }
//STRIP001      }
//STRIP001      else
//STRIP001          rFmtIndex = 0;
//STRIP001
//STRIP001      bRet = pNumFmtr->IsNumberFormat( aTxt, rFmtIndex, rNum );
//STRIP001
//STRIP001 /*
//STRIP001 // wie bekommt man aus dem neuen String den neuen Wert?
//STRIP001 // denn der Numberformater erkennt aus "123.--DM" kein Zahlenformat!
//STRIP001      if( !bRet && rFmtIndex && !pNumFmtr->IsTextFormat( rFmtIndex ) &&
//STRIP001          SFX_ITEM_SET == GetFrmFmt()->GetItemState( RES_BOXATR_VALUE,
//STRIP001          FALSE, &pItem ))
//STRIP001      {
//STRIP001          Color* pCol;
//STRIP001          String sNewTxt;
//STRIP001          pNumFmtr->GetOutputString( ((SwTblBoxValue*)pItem)->GetValue(),
//STRIP001                                      rFmtIndex, sNewTxt, &pCol );
//STRIP001          bRet = aTxt == sNewTxt;
//STRIP001      }
//STRIP001 */
//STRIP001  }
//STRIP001  else
//STRIP001      rIsEmptyTxtNd = FALSE;
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SwTableBox::IsNumberChanged() const
//STRIP001 {
//STRIP001  BOOL bRet = TRUE;
//STRIP001
//STRIP001  if( SFX_ITEM_SET == GetFrmFmt()->GetItemState( RES_BOXATR_FORMULA, FALSE ))
//STRIP001  {
//STRIP001      const SwTblBoxNumFormat *pNumFmt;
//STRIP001      const SwTblBoxValue *pValue;
//STRIP001
//STRIP001      if( SFX_ITEM_SET != GetFrmFmt()->GetItemState( RES_BOXATR_VALUE, FALSE,
//STRIP001          (const SfxPoolItem**)&pValue ))
//STRIP001          pValue = 0;
//STRIP001      if( SFX_ITEM_SET != GetFrmFmt()->GetItemState( RES_BOXATR_FORMAT, FALSE,
//STRIP001          (const SfxPoolItem**)&pNumFmt ))
//STRIP001          pNumFmt = 0;
//STRIP001
//STRIP001      ULONG nNdPos;
//STRIP001      if( pNumFmt && pValue &&
//STRIP001          ULONG_MAX != ( nNdPos = IsValidNumTxtNd( TRUE ) ) )
//STRIP001      {
//STRIP001          String sNewTxt, sOldTxt( pSttNd->GetNodes()[ nNdPos ]->
//STRIP001                                  GetTxtNode()->GetRedlineTxt() );
//STRIP001          lcl_DelTabsAtSttEnd( sOldTxt );
//STRIP001
//STRIP001          Color* pCol = 0;
//STRIP001          GetFrmFmt()->GetDoc()->GetNumberFormatter()->GetOutputString(
//STRIP001              pValue->GetValue(), pNumFmt->GetValue(), sNewTxt, &pCol );
//STRIP001
//STRIP001          bRet = sNewTxt != sOldTxt ||
//STRIP001                  !( ( !pCol && !GetSaveNumFmtColor() ) ||
//STRIP001                     ( pCol && GetSaveNumFmtColor() &&
//STRIP001                      *pCol == *GetSaveNumFmtColor() ));
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*N*/ ULONG SwTableBox::IsValidNumTxtNd( BOOL bCheckAttr ) const
/*N*/ {
/*N*/   ULONG nPos = ULONG_MAX;
/*N*/   if( pSttNd )
/*N*/   {
/*N*/       SwNodeIndex aIdx( *pSttNd );
/*N*/       const SwCntntNode* pCNd = pSttNd->GetNodes().GoNext( &aIdx );
/*N*/       if( pCNd && pCNd->IsTxtNode() &&
/*N*/           pSttNd->GetNodes()[ aIdx.GetIndex() + 1 ]->IsEndNode() )
/*N*/       {
/*N*/           if( bCheckAttr )
/*N*/           {
/*N*/               const SwpHints* pHts = ((SwTxtNode*)pCNd)->GetpSwpHints();
/*N*/               const String& rTxt = ((SwTxtNode*)pCNd)->GetTxt();
/*N*/ //                if( rTxt.Len() )
/*N*/               {
/*N*/                   nPos = aIdx.GetIndex();
/*N*/
/*N*/                   // dann teste doch mal, ob das wirklich nur Text im Node steht!
/*N*/                   // Flys/Felder/..
/*N*/                   if( pHts )
/*N*/                   {
/*?*/                       for( USHORT n = 0; n < pHts->Count(); ++n )
/*?*/                       {
/*?*/                           const SwTxtAttr* pAttr = (*pHts)[ n ];
/*?*/                           if( RES_TXTATR_NOEND_BEGIN <= pAttr->Which() ||
/*?*/                               *pAttr->GetStart() ||
/*?*/                               *pAttr->GetAnyEnd() < rTxt.Len() )
/*?*/                           {
/*?*/                               nPos = ULONG_MAX;
/*?*/                               break;
/*?*/                           }
/*?*/                       }
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/           else
/*N*/               nPos = aIdx.GetIndex();
/*N*/       }
/*N*/   }
/*N*/   return nPos;
/*N*/ }

// ist das eine FormelBox oder eine Box mit numerischen Inhalt (AutoSum)
//STRIP001 USHORT SwTableBox::IsFormulaOrValueBox() const
//STRIP001 {
//STRIP001  USHORT nWhich = 0;
//STRIP001  const SwTxtNode* pTNd;
//STRIP001  SwFrmFmt* pFmt = GetFrmFmt();
//STRIP001  if( SFX_ITEM_SET == pFmt->GetItemState( RES_BOXATR_FORMULA, FALSE ))
//STRIP001      nWhich = RES_BOXATR_FORMULA;
//STRIP001  else if( SFX_ITEM_SET == pFmt->GetItemState( RES_BOXATR_VALUE, FALSE ) &&
//STRIP001          !pFmt->GetDoc()->GetNumberFormatter()->IsTextFormat(
//STRIP001              pFmt->GetTblBoxNumFmt().GetValue() ))
//STRIP001      nWhich = RES_BOXATR_VALUE;
//STRIP001  else if( pSttNd && pSttNd->GetIndex() + 2 == pSttNd->EndOfSectionIndex()
//STRIP001          && 0 != ( pTNd = pSttNd->GetNodes()[ pSttNd->GetIndex() + 1 ]
//STRIP001          ->GetTxtNode() ) && !pTNd->GetTxt().Len() )
//STRIP001      nWhich = USHRT_MAX;
//STRIP001
//STRIP001  return nWhich;
//STRIP001 }

// JP 12.09.97 - Bug 41223:
// falls an der International Einstellung gedreht wurde, so muss beim Laden
// eine entsprechende Aktualisierung erfolgen.
/*N*/ void SwTableBox::ChgByLanguageSystem()
/*N*/ {
/*N*/   const SfxPoolItem *pFmtItem, *pValItem;
/*N*/   SwFrmFmt* pFmt = GetFrmFmt();
/*N*/   ULONG nFmtId;
/*N*/   if( SFX_ITEM_SET == pFmt->GetItemState( RES_BOXATR_FORMAT, TRUE, &pFmtItem )
/*N*/       && ( nFmtId = ((SwTblBoxNumFormat*)pFmtItem)->GetValue()) < SV_COUNTRY_LANGUAGE_OFFSET
/*N*/       && SFX_ITEM_SET == pFmt->GetItemState( RES_BOXATR_VALUE, TRUE, &pValItem ))
/*N*/   {
/*N*/       ULONG nNdPos;
/*N*/       SvNumberFormatter* pNumFmtr = pFmt->GetDoc()->GetNumberFormatter();
/*N*/
/*N*/       if( !pNumFmtr->IsTextFormat( nFmtId ) &&
/*N*/           ULONG_MAX != (nNdPos = IsValidNumTxtNd( TRUE )) )
/*N*/       {
/*N*/           double fVal = ((SwTblBoxValue*)pValItem)->GetValue();
/*N*/           Color* pCol = 0;
/*N*/           String sNewTxt;
/*N*/           pNumFmtr->GetOutputString( fVal, nFmtId, sNewTxt, &pCol );
/*N*/
/*N*/           const String& rTxt = pSttNd->GetNodes()[ nNdPos ]->GetTxtNode()->GetTxt();
/*N*/           if( rTxt != sNewTxt )
/*?*/               {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 ChgTextToNum( *this, sNewTxt, pCol, FALSE );
/*N*/       }
/*N*/   }
/*N*/ }
/*N*/
//STRIP001 void SwTableBox_Impl::SetNewCol( Color** ppCol, const Color* pNewCol )
//STRIP001 {
//STRIP001  if( *ppCol != pNewCol )
//STRIP001  {
//STRIP001      delete *ppCol;
//STRIP001      if( pNewCol )
//STRIP001          *ppCol = new Color( *pNewCol );
//STRIP001      else
//STRIP001          *ppCol = 0;
//STRIP001  }
//STRIP001 }


}
