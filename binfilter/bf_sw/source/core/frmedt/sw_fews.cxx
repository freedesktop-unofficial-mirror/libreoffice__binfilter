/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_fews.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2006-11-08 12:30:48 $
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

#ifndef _SVDVMARK_HXX //autogen
#include <bf_svx/svdvmark.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _FESH_HXX
#include <fesh.hxx>
#endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>
#endif
#ifndef _FRMTOOL_HXX
#include <frmtool.hxx>
#endif
#ifndef _VIEWIMP_HXX
#include <viewimp.hxx>
#endif
#ifndef _DVIEW_HXX
#include <dview.hxx>
#endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _SECTFRM_HXX
#include <sectfrm.hxx>
#endif
#ifndef _TABFRM_HXX
#include <tabfrm.hxx>
#endif
#ifndef _FLYFRMS_HXX
#include <flyfrms.hxx>
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>       // SwTxtFrm
#endif
#ifndef _MDIEXP_HXX
#include <mdiexp.hxx>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif
namespace binfilter {

/*N*/ TYPEINIT1(SwFEShell,SwEditShell)

/***********************************************************************
#*  Class      :  SwFEShell
#*  Methode    :  EndAllActionAndCall()
#*
#*  Datum      :  MA 03. May. 93
#*  Update     :  MA 31. Oct. 95
#***********************************************************************/



/***********************************************************************
#*  Class       :  SwFEShell
#*  Methode     :  GetCntntPos
#*  Beschreibung:  Ermitteln des Cntnt's der dem Punkt am naechsten liegt
#*  Datum       :  MA 02. Jun. 92
#*  Update      :  MA 02. May. 95
#***********************************************************************/



/*N*/ const SwRect& SwFEShell::GetAnyCurRect( CurRectType eType, const Point* pPt,
/*N*/                                       const SvEmbeddedObject *pObj ) const
/*N*/ {
/*N*/   const SwFrm *pFrm = Imp()->HasDrawView()
    /*N*/               ? ::binfilter::GetFlyFromMarked( &Imp()->GetDrawView()->GetMarkList(),
/*N*/                                     (ViewShell*)this)
/*N*/               : 0;
/*N*/
/*N*/   if( !pFrm )
/*N*/   {
/*N*/       if( pPt )
/*N*/       {
/*?*/           SwPosition aPos( *GetCrsr()->GetPoint() );
/*?*/           Point aPt( *pPt );
/*?*/           GetLayout()->GetCrsrOfst( &aPos, aPt );
/*?*/           SwCntntNode *pNd = aPos.nNode.GetNode().GetCntntNode();
/*?*/           pFrm = pNd->GetFrm( pPt );
/*N*/       }
/*N*/       else
/*N*/           pFrm = GetCurrFrm();
/*N*/   }
/*N*/
/*N*/   if( !pFrm )
/*?*/       return GetLayout()->Frm();
/*N*/
/*N*/   FASTBOOL  bFrm  = TRUE;
/*N*/   switch ( eType )
/*N*/   {
/*N*/       case RECT_PAGE_PRT:         bFrm = FALSE; /* no break */
/*N*/       case RECT_PAGE :            pFrm = pFrm->FindPageFrm();
/*N*/                                   break;
/*N*/
/*?*/       case RECT_PAGE_CALC:        pFrm->Calc();
/*?*/                                   pFrm = pFrm->FindPageFrm();
/*?*/                                   pFrm->Calc();
/*?*/                                   break;
/*N*/
/*N*/       case RECT_FLY_PRT_EMBEDDED: bFrm = FALSE; /* no break */
/*N*/       case RECT_FLY_EMBEDDED:     pFrm = pObj ? FindFlyFrm( pObj )
/*N*/                                               : pFrm->IsFlyFrm()
/*N*/                                                   ? pFrm
/*N*/                                                   : pFrm->FindFlyFrm();
/*N*/                                   break;
/*N*/
/*N*/       case RECT_OUTTABSECTION_PRT:
/*?*/       case RECT_OUTTABSECTION :   if( pFrm->IsInTab() )
/*?*/                                       pFrm = pFrm->FindTabFrm();
/*?*/                                   else
/*?*/                                       ASSERT( FALSE, "Missing Table" );
/*?*/                                   /* KEIN BREAK */
/*?*/       case RECT_SECTION_PRT:
/*?*/       case RECT_SECTION:          if( pFrm->IsInSct() )
/*?*/                                       pFrm = pFrm->FindSctFrm();
/*?*/                                   else
/*?*/                                       ASSERT( FALSE, "Missing section" );
/*?*/
/*?*/                                   if( RECT_OUTTABSECTION_PRT == eType ||
/*?*/                                       RECT_SECTION_PRT == eType )
/*?*/                                       bFrm = FALSE;
/*?*/                                   break;
/*?*/
/*?*/       case RECT_HEADERFOOTER_PRT: bFrm = FALSE; /* no break */
/*?*/       case RECT_HEADERFOOTER:     if( 0 == (pFrm = pFrm->FindFooterOrHeader()) )
/*?*/                                       return GetLayout()->Frm();
/*?*/                                   break;
/*N*/
/*N*/ //JP 20.08.98: wo zu diese Statements? unnoetiger Code
/*N*/ //        case RECT_FRM:
/*N*/ //        default:                    break;
/*N*/   }
/*N*/   return bFrm ? pFrm->Frm() : pFrm->Prt();
/*N*/ }




/*N*/ BOOL SwFEShell::GetPageNumber( long nYPos, BOOL bAtCrsrPos, USHORT& rPhyNum, USHORT& rVirtNum, String &rDisplay) const
/*N*/ {
/*N*/   const SwFrm *pPage;
/*N*/
/*N*/   if ( bAtCrsrPos )                   //Seite vom Crsr besorgen
/*N*/   {
/*N*/       pPage = GetCurrFrm( FALSE );
/*N*/       if ( pPage )
/*N*/           pPage = pPage->FindPageFrm();
/*N*/   }
/*N*/   else if ( nYPos > -1 )              //Seite ueber die Positon ermitteln
/*N*/   {
/*?*/       pPage = GetLayout()->Lower();
/*?*/       while( pPage &&  (pPage->Frm().Bottom() < nYPos ||
/*?*/                           nYPos < pPage->Frm().Top() ) )
/*?*/           pPage = pPage->GetNext();
/*N*/   }
/*N*/   else                                //Die erste sichtbare Seite
/*N*/   {
/*N*/       pPage = Imp()->GetFirstVisPage();
/*N*/       if ( pPage && ((SwPageFrm*)pPage)->IsEmptyPage() )
/*N*/           pPage = pPage->GetNext();
/*N*/   }
/*N*/
/*N*/   if( pPage )
/*N*/   {
/*N*/       rPhyNum  = ((const SwPageFrm*)pPage)->GetPhyPageNum();
/*N*/       rVirtNum = ((const SwPageFrm*)pPage)->GetVirtPageNum();
/*N*/       const SvxNumberType& rNum = ((const SwPageFrm*)pPage)->GetPageDesc()->GetNumType();
/*N*/       rDisplay = rNum.GetNumStr( rVirtNum );
/*N*/   }
/*N*/
/*N*/   return 0 != pPage;
/*N*/ }

/*************************************************************************
|*
|*  SwFEShell::GetHeadFootFrmRect()
|*
|*  Ersterstellung      MA 08. Feb. 95
|*  Letzte Aenderung    MA 08. Feb. 95
|
|*************************************************************************/

//Das FrmRect von Header bzw. Footer wird relativ zur Seite ermittelt.
//Der long ist 0 wenn der Crsr nicht in Header oder Footer steht.
//Andernfalls markiert der long den maximalen bzw. minimalen Spielraum
//fuer die Hoehe von Header bzw. Footer.


/*************************************************************************
|*
|*  SwFEShell::IsDirectlyInSection()
|*
|*  Hack for OS:
|*
*************************************************************************/

bool SwFEShell::IsDirectlyInSection() const
{
    SwFrm* pFrm = GetCurrFrm( FALSE );
    return pFrm && pFrm->GetUpper() && pFrm->GetUpper()->IsSctFrm();
}

/*************************************************************************
|*
|*  SwFEShell::GetFrmType()
|*
|*  Ersterstellung      MA 12. Jan. 93
|*  Letzte Aenderung    AMA 25. Nov. 98
|*
*************************************************************************/

/*N*/ USHORT SwFEShell::GetFrmType( const Point *pPt, BOOL bStopAtFly ) const
/*N*/ {
/*N*/   USHORT nReturn = FRMTYPE_NONE;
/*N*/   SwFrm *pFrm;
/*N*/   if ( pPt )
/*N*/   {
/*?*/       SwPosition aPos( *GetCrsr()->GetPoint() );
/*?*/       Point aPt( *pPt );
/*?*/       GetLayout()->GetCrsrOfst( &aPos, aPt );
/*?*/       SwCntntNode *pNd = aPos.nNode.GetNode().GetCntntNode();
/*?*/       pFrm = pNd->GetFrm( pPt );
/*N*/   }
/*N*/   else
/*N*/       pFrm = GetCurrFrm( FALSE );
/*N*/   while ( pFrm )
/*N*/   {
/*N*/       switch ( pFrm->GetType() )
/*N*/       {
/*N*/           case FRM_COLUMN:    if( pFrm->GetUpper()->IsSctFrm() )
/*N*/                               {
/*?*/                                   // Check, if isn't not only a single column
/*?*/                                   // from a section with footnotes at the end.
/*?*/                                   if( pFrm->GetNext() || pFrm->GetPrev() )
/*?*/                                       // Sectioncolumns
/*?*/                                       nReturn |= ( nReturn & FRMTYPE_TABLE ) ?
/*?*/                                           FRMTYPE_COLSECTOUTTAB : FRMTYPE_COLSECT;
/*N*/                               }
/*N*/                               else // nur Seiten und Rahmenspalten
/*N*/                                   nReturn |= FRMTYPE_COLUMN;
/*N*/                               break;
/*N*/           case FRM_PAGE:      nReturn |= FRMTYPE_PAGE;
/*N*/                               if( ((SwPageFrm*)pFrm)->IsFtnPage() )
/*?*/                                   nReturn |= FRMTYPE_FTNPAGE;
/*N*/                               break;
/*?*/           case FRM_HEADER:    nReturn |= FRMTYPE_HEADER;      break;
/*?*/           case FRM_FOOTER:    nReturn |= FRMTYPE_FOOTER;      break;
/*N*/           case FRM_BODY:      if( pFrm->GetUpper()->IsPageFrm() ) // nicht bei ColumnFrms
/*N*/                                   nReturn |= FRMTYPE_BODY;
/*N*/                               break;
/*?*/           case FRM_FTN:       nReturn |= FRMTYPE_FOOTNOTE;    break;
/*?*/           case FRM_FLY:       if( ((SwFlyFrm*)pFrm)->IsFlyLayFrm() )
/*?*/                                   nReturn |= FRMTYPE_FLY_FREE;
/*?*/                               else if ( ((SwFlyFrm*)pFrm)->IsFlyAtCntFrm() )
/*?*/                                   nReturn |= FRMTYPE_FLY_ATCNT;
/*?*/                               else
/*?*/                               {
/*?*/                                   ASSERT( ((SwFlyFrm*)pFrm)->IsFlyInCntFrm(),
/*?*/                                           "Neuer Rahmentyp?" );
/*?*/                                   nReturn |= FRMTYPE_FLY_INCNT;
/*?*/                               }
/*?*/                               nReturn |= FRMTYPE_FLY_ANY;
/*?*/                               if( bStopAtFly )
/*?*/                                   return nReturn;
/*?*/                               break;
/*N*/           case FRM_TAB:
/*N*/           case FRM_ROW:
/*N*/           case FRM_CELL:      nReturn |= FRMTYPE_TABLE;       break;
/*N*/           default:            /* do nothing */                break;
/*N*/       }
/*N*/       if ( pFrm->IsFlyFrm() )
/*?*/           pFrm = ((SwFlyFrm*)pFrm)->GetAnchor();
/*N*/       else
/*N*/           pFrm = pFrm->GetUpper();
/*N*/   }
/*N*/   return nReturn;
/*N*/ }

/*************************************************************************
|*
|*  SwFEShell::ShLooseFcs(), ShGetFcs()
|*
|*  Ersterstellung      MA 10. May. 93
|*  Letzte Aenderung    MA 09. Sep. 98
|*
*************************************************************************/

/*N*/ void SwFEShell::ShGetFcs( BOOL bUpdate )
/*N*/ {
/*N*/   ::binfilter::SetShell( this );
/*N*/   SwCrsrShell::ShGetFcs( bUpdate );
/*N*/
/*N*/   if ( HasDrawView() )
/*N*/   {
/*N*/       Imp()->GetDrawView()->SetMarkHdlHidden( FALSE );
/*N*/       if ( Imp()->GetDrawView()->HasMarkedObj() )
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 FrameNotify( this, FLY_DRAG_START );
/*N*/   }
/*N*/ }


/*************************************************************************
|*
|*  SwFEShell::GetPhyPageNum()
|*  SwFEShell::GetVirtPageNum()
|*
|*  Ersterstellung      OK 07.07.93 08:20
|*  Letzte Aenderung    MA 03. Jan. 94
|*
*************************************************************************/



/*************************************************************************
|*
|*  void lcl_SetAPageOffset()
|*  void SwFEShell::SetNewPageOffset()
|*  void SwFEShell::SetPageOffset()
|*  USHORT SwFEShell::GetPageOffset() const
|*
|*  Ersterstellung      OK 07.07.93 08:20
|*  Letzte Aenderung    MA 30. Mar. 95
|*
*************************************************************************/





/*************************************************************************
|*
|*  SwFEShell::InsertLabel()
|*
|*  Ersterstellung      MA 10. Feb. 94
|*  Letzte Aenderung    MA 10. Feb. 94
|*
*************************************************************************/



/***********************************************************************
#*  Class       :  SwFEShell
#*  Methoden    :  Sort
#*  Datum       :  ??
#*  Update      :  ??
#***********************************************************************/


/*************************************************************************
|*
|*  SwFEShell::GetCurColNum(), _GetColNum()
|*
|*  Ersterstellung      MA 03. Feb. 95
|*  Letzte Aenderung    MA 20. Apr. 95
|
|*************************************************************************/

/*N*/ USHORT SwFEShell::_GetCurColNum( const SwFrm *pFrm,
/*N*/                               SwGetCurColNumPara* pPara ) const
/*N*/ {
/*N*/   USHORT nRet = 0;
/*N*/   while ( pFrm )
/*N*/   {
/*N*/       pFrm = pFrm->GetUpper();
/*N*/       if( pFrm && pFrm->IsColumnFrm() )
/*N*/       {
/*N*/           const SwFrm *pCurFrm = pFrm;
/*N*/           do {
/*N*/               ++nRet;
/*N*/               pFrm = pFrm->GetPrev();
/*N*/           } while ( pFrm );
/*N*/
/*N*/           if( pPara )
/*N*/           {
/*N*/               // dann suche mal das Format, was diese Spaltigkeit bestimmt
/*N*/               pFrm = pCurFrm->GetUpper();
/*N*/               while( pFrm )
/*N*/               {
/*N*/                   if( ( FRM_PAGE | FRM_FLY | FRM_SECTION ) & pFrm->GetType() )
/*N*/                   {
/*N*/                       pPara->pFrmFmt = ((SwLayoutFrm*)pFrm)->GetFmt();
/*N*/                       pPara->pPrtRect = &pFrm->Prt();
/*N*/                       pPara->pFrmRect = &pFrm->Frm();
/*N*/                       break;
/*N*/                   }
/*N*/                   pFrm = pFrm->GetUpper();
/*N*/               }
/*N*/               if( !pFrm )
/*N*/               {
/*N*/                   pPara->pFrmFmt = 0;
/*N*/                   pPara->pPrtRect = 0;
/*N*/                   pPara->pFrmRect = 0;
/*N*/               }
/*N*/           }
/*N*/           break;
/*N*/       }
/*N*/   }
/*N*/   return nRet;
/*N*/ }

/*N*/ USHORT SwFEShell::GetCurColNum( SwGetCurColNumPara* pPara ) const
/*N*/ {
/*N*/   ASSERT( GetCurrFrm(), "Crsr geparkt?" );
/*N*/   return _GetCurColNum( GetCurrFrm(), pPara );
/*N*/ }


/*N*/ SwFEShell::SwFEShell( SwDoc& rDoc, Window *pWin,
/*N*/                    SwRootFrm *pMaster, const SwViewOption *pOpt )
/*N*/   : SwEditShell( rDoc, pWin, pMaster, pOpt ),
/*N*/   pChainFrom( 0 ), pChainTo( 0 ), bCheckForOLEInCaption( FALSE )
/*N*/ {
/*N*/ }

/*N*/ SwFEShell::SwFEShell( SwEditShell& rShell, Window *pWin )
/*N*/   : SwEditShell( rShell, pWin ),
/*N*/   pChainFrom( 0 ), pChainTo( 0 ), bCheckForOLEInCaption( FALSE )
/*N*/ {
/*N*/ }

/*N*/ SwFEShell::~SwFEShell()
/*N*/ {
/*N*/   delete pChainFrom;
/*N*/   delete pChainTo;
/*N*/ }


/* -----------------------------12.08.2002 12:51------------------------------

 ---------------------------------------------------------------------------*/
/*M*/ BOOL SwFEShell::IsFrmVertical(BOOL bEnvironment, BOOL& bRTL) const
/*M*/ {
/*M*/     SwFlyFrm *pFly = FindFlyFrm();
/*M*/     BOOL bVert = FALSE;
/*M*/     if ( pFly )
/*M*/     {
/*M*/         const SwFrm *pFrm = pFly->GetAnchor();
/*M*/         bVert = bEnvironment ? pFrm->IsVertical() : pFly->IsVertical();
/*M*/         bRTL = bEnvironment ? pFrm->IsRightToLeft() : pFly->IsRightToLeft();
/*M*/     }
/*M*/     else
/*M*/         bRTL = FALSE;
/*M*/     return bVert;
/*M*/ }

}
