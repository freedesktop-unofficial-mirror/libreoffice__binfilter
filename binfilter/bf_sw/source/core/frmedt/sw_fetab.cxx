/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_fetab.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 22:40:20 $
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

#define ITEMID_BOXINFO SID_ATTR_BORDER_INNER
#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _SVX_SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif


#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _FESH_HXX
#include <fesh.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
#ifndef _TABFRM_HXX
#include <tabfrm.hxx>
#endif
#ifndef _CELLFRM_HXX
#include <cellfrm.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _TABCOL_HXX
#include <tabcol.hxx>
#endif
#ifndef _VISCRS_HXX
#include <viscrs.hxx>
#endif

#ifndef _SWSWERROR_H
#include <swerror.h>
#endif
namespace binfilter {

//siehe auch swtable.cxx
#define COLFUZZY 20L


/*N*/ SwTabCols *pLastCols   = 0;



/*N*/ inline const SwCursor& GetShellCursor( const SwCrsrShell& rShell )
/*N*/ {
/*N*/   const SwShellCrsr *pCrsr = rShell.GetTableCrsr();
/*N*/   if( !pCrsr )
/*N*/       pCrsr = (SwShellCrsr*)*rShell.GetSwCrsr( FALSE );
/*N*/   return *pCrsr;
/*N*/ }


/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  GetStartEndCell
#*  Datum      :  MA 03. May. 93
#*  Update     :  MA 23. May. 95
#***********************************************************************/

/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  InsertRow(), InsertCol
#*  Datum      :  MA 03. May. 93
#*  Update     :  MA 19. Apr. 95
#***********************************************************************/


/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  DeleteRow(), DeleteCol()
#*  Datum      :  MA 03. May. 93
#*  Update     :  MA 19. Apr. 95
#***********************************************************************/

/**
   Determines if the current cursor is in the last row of the table.
*/



/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  MergeTab(), SplitTab()
#*  Datum      :  MA 03. May. 93
#*  Update     :  MA 19. Apr. 95
#***********************************************************************/




/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  _GetTabCols
#*  Datum      :  MA 30. Nov. 95
#*  Update     :  MA 08. Jan. 97
#***********************************************************************/

/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  SetTabCols(), GetTabCols()
#*  Datum      :  MA 03. May. 93
#*  Update     :  MA 18. May. 93
#***********************************************************************/


/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  SetRowHeight(), GetRowHeight()
#*  Datum      :  MA 17. May. 93
#*  Update     :  JP 29.04.98
#***********************************************************************/


/******************************************************************************
 *               SwTwips SwFEShell::GetRowHeight() const
 ******************************************************************************/

/*N*/ BOOL SwFEShell::BalanceRowHeight( BOOL bTstOnly )
/*N*/ {
/*N*/   SET_CURR_SHELL( this );
/*N*/   if( !bTstOnly )
/*?*/       StartAllAction();
/*N*/   BOOL bRet = GetDoc()->BalanceRowHeight( GetShellCursor( *this ), bTstOnly );
/*N*/   if( !bTstOnly )
/*?*/   {DBG_BF_ASSERT(0, "STRIP");} //STRIP001     EndAllActionAndCall();
/*N*/   return bRet;
/*N*/ }

/******************************************************************************
 *              void SwFEShell::SetRowBackground()
 ******************************************************************************/

/******************************************************************************
 *               SwTwips SwFEShell::GetRowBackground() const
 ******************************************************************************/

/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  SetTabBorders(), GetTabBorders()
#*  Datum      :  MA 18. May. 93
#*  Update     :  JP 29.04.98
#***********************************************************************/



/*N*/ void SwFEShell::GetTabBorders( SfxItemSet& rSet ) const
/*N*/ {
/*N*/   GetDoc()->GetTabBorders( GetShellCursor( *this ), rSet );
/*N*/ }


/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  SetBoxBackground(), GetBoxBackground()
#*  Datum      :  MA 01. Jun. 93
#*  Update     :  MA 03. Jul. 96
#***********************************************************************/


/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  SetBoxAlign, SetBoxAlign
#*  Datum      :  MA 18. Dec. 96
#*  Update     :  JP 29.04.98
#***********************************************************************/

/*N*/ USHORT SwFEShell::GetBoxAlign() const
/*N*/ {
/*N*/   return GetDoc()->GetBoxAlign( GetShellCursor( *this ) );
/*N*/ }

/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  SetTabBackground(), GetTabBackground()
#*  Datum      :  MA 08. Jul. 96
#*  Update     :  MA 08. Jul. 96
#***********************************************************************/



/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  HasWholeTabSelection()
#*  Datum      :  MA 18. May. 93
#*  Update     :  MA 20. Jul. 93
#***********************************************************************/


/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  ProtectCells(), UnProtectCells()
#*  Datum      :  MA 20. Jul. 93
#*  Update     :  JP 25. Sep. 93
#***********************************************************************/


// die Tabellenselektion aufheben




/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  IsHeadlineRepeat(), SetHeadlineRepeat()
#*  Datum      :  MA 02. Feb. 94
#*  Update     :  MA 27. Jul. 95
#***********************************************************************/



/*N*/ BOOL SwFEShell::IsInRepeatedHeadline() const
/*N*/ {
/*N*/   BOOL bRet = FALSE;
/*N*/   if ( !IsTableMode() )
/*N*/   {
/*N*/       SwFrm *pFrm = GetCurrFrm();
/*N*/       if ( pFrm->IsInTab() )
/*N*/       {
/*N*/           SwTabFrm *pTab = pFrm->FindTabFrm();
/*N*/           if ( pTab->IsFollow() && pTab->GetTable()->IsHeadlineRepeat() &&
/*N*/                ((SwLayoutFrm*)pTab->Lower())->IsAnLower( pFrm ) )
/*N*/           {
/*?*/               bRet = TRUE;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }

/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  AdjustCellWidth()
#*  Datum      :  MA 20. Feb. 95
#*  Update     :  MA 27. Jul. 95
#***********************************************************************/


/*N*/ BOOL SwFEShell::IsAdjustCellWidthAllowed( BOOL bBalance ) const
/*N*/ {
/*N*/   //Es muss mindestens eine Zelle mit Inhalt in der Selektion enthalten
/*N*/   //sein.
/*N*/
/*N*/   SwFrm *pFrm = GetCurrFrm();
/*N*/   if( !pFrm->IsInTab() )
/*?*/       return FALSE;
/*N*/
/*N*/   SwSelBoxes aBoxes;
/*N*/   ::binfilter::GetTblSelCrs( *this, aBoxes );
/*N*/
/*N*/   if ( bBalance )
/*N*/       return aBoxes.Count() > 1;
/*N*/
/*N*/   if ( !aBoxes.Count() )
/*N*/   {
/*N*/       do
/*N*/       {   pFrm = pFrm->GetUpper();
/*N*/       } while ( !pFrm->IsCellFrm() );
/*N*/       SwTableBox *pBox = (SwTableBox*)((SwCellFrm*)pFrm)->GetTabBox();
/*N*/       aBoxes.Insert( pBox );
/*N*/   }
/*N*/
/*N*/   for ( USHORT i = 0; i < aBoxes.Count(); ++i )
/*N*/   {
/*N*/       SwTableBox *pBox = aBoxes[i];
/*N*/       if ( pBox->GetSttNd() )
/*N*/       {
/*N*/           SwNodeIndex aIdx( *pBox->GetSttNd(), 1 );
/*N*/           SwTxtNode* pCNd = aIdx.GetNode().GetTxtNode();
/*N*/           if( !pCNd )
/*?*/               pCNd = (SwTxtNode*)GetDoc()->GetNodes().GoNext( &aIdx );
/*N*/
/*N*/           while ( pCNd )
/*N*/           {
/*N*/               if ( pCNd->GetTxt().Len() )
/*N*/                   return TRUE;
/*N*/               ++aIdx;
/*N*/               pCNd = GetDoc()->GetNodes()[ aIdx ]->GetTxtNode();
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return FALSE;
/*N*/ }

    // AutoFormat fuer die Tabelle/TabellenSelection


/***********************************************************************
#*  Class      :  SwFEShell
#*  Methoden   :  DeleteTblSel()
#*  Datum      :  MA 03. May. 93
#*  Update     :  MA 19. Apr. 95
#***********************************************************************/

/*************************************************************************
|*
|*  SwFEShell::GetCurTabColNum()
|*
|*  Ersterstellung      MA 03. Feb. 95
|*  Letzte Aenderung    MA 21. May. 95
|
|*************************************************************************/

/*************************************************************************
|*
|*  SwFEShell::GetBox()
|*
|*  Ersterstellung      MA 22. Jun. 95
|*  Letzte Aenderung    MA 21. Nov. 96
|*
|*************************************************************************/





/*************************************************************************
|*
|*  SwFEShell::WhichMouseTabCol()
|*
|*  Ersterstellung      MA 22. Jun. 95
|*  Last change         AMA 12. Jun. 02
|
|*************************************************************************/

/*************************************************************************
|*
|*  SwFEShell::GetMouseTabCols()
|*
|*  Ersterstellung      MA 22. Jun. 95
|*  Letzte Aenderung    MA 27. Aug. 96
|
|*************************************************************************/


/*************************************************************************
|*
|*  SwFEShell::GetMouseColNum(), GetMouseTabColNum()
|*
|*  Ersterstellung      MA 04. Jul. 95
|*  Letzte Aenderung    MA 04. Jul. 95
|
|*************************************************************************/


/*N*/ void ClearFEShellTabCols()
/*N*/ {
/*N*/   DELETEZ( pLastCols );
/*N*/ }

/*************************************************************************
|*
|*  SwFEShell::GetTblAttr(), SetTblAttr()
|*
|*  Ersterstellung      MA 09. Dec. 96
|*  Letzte Aenderung    MA 09. Dec. 96
|
|*************************************************************************/


/** move cursor within a table into previous/next row (same column)
 * @param pShell cursor shell whose cursor is to be moved
 * @param bUp true: move up, false: move down
 * @returns true if successful
 */

    // aender eine  Zellenbreite/-Hoehe/Spaltenbreite/Zeilenhoehe


    // erfrage die Formel fuer die Autosumme
/* -----------------------------22.08.2002 12:50------------------------------

 ---------------------------------------------------------------------------*/
/*M*/ BOOL SwFEShell::IsTableRightToLeft() const
/*M*/ {
/*M*/   SwFrm *pFrm = GetCurrFrm();
/*M*/   if( !pFrm->IsInTab() )
/*M*/       return FALSE;
/*M*/
/*M*/     return pFrm->ImplFindTabFrm()->IsRightToLeft();
/*M*/ }
/* -----------------------------22.08.2002 12:50------------------------------

 ---------------------------------------------------------------------------*/
/*M*/ BOOL SwFEShell::IsMouseTableRightToLeft(const Point &rPt) const
/*M*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
/*M*/ }

}
