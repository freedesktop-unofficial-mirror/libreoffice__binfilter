/*************************************************************************
 *
 *  $RCSfile: sw_fews.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:29:20 $
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

// auto strip #ifndef _LIST_HXX //autogen
// auto strip #include <tools/list.hxx>
// auto strip #endif
#ifndef _SVDVMARK_HXX //autogen
#include <bf_svx/svdvmark.hxx>
#endif
// auto strip #ifndef _SVDOBJ_HXX //autogen
// auto strip #include <bf_svx/svdobj.hxx>
// auto strip #endif

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
// auto strip #ifndef _CNTFRM_HXX
// auto strip #include <cntfrm.hxx>
// auto strip #endif
// auto strip #ifndef _DOC_HXX
// auto strip #include <doc.hxx>
// auto strip #endif
#ifndef _FRMTOOL_HXX
#include <frmtool.hxx>
#endif
// auto strip #ifndef _SWTABLE_HXX
// auto strip #include <swtable.hxx>
// auto strip #endif
#ifndef _VIEWIMP_HXX
#include <viewimp.hxx>
#endif
#ifndef _DVIEW_HXX
#include <dview.hxx>
#endif
// auto strip #ifndef _FLYFRM_HXX
// auto strip #include <flyfrm.hxx>
// auto strip #endif
// auto strip #ifndef _NODE_HXX
// auto strip #include <node.hxx>
// auto strip #endif
#ifndef _PAM_HXX
#include <pam.hxx>
#endif
#ifndef _SECTFRM_HXX
#include <sectfrm.hxx>
#endif
// auto strip #ifndef _FMTPDSC_HXX //autogen
// auto strip #include <fmtpdsc.hxx>
// auto strip #endif
// auto strip #ifndef _FMTSRND_HXX //autogen
// auto strip #include <fmtsrnd.hxx>
// auto strip #endif
// auto strip #ifndef _FMTCNTNT_HXX //autogen
// auto strip #include <fmtcntnt.hxx>
// auto strip #endif
#ifndef _TABFRM_HXX
#include <tabfrm.hxx>
#endif
// auto strip #ifndef _CELLFRM_HXX
// auto strip #include <cellfrm.hxx>
// auto strip #endif
#ifndef _FLYFRMS_HXX
#include <flyfrms.hxx>
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>       // SwTxtFrm
#endif
#ifndef _MDIEXP_HXX
#include <mdiexp.hxx>
#endif
// auto strip #ifndef _EDIMP_HXX
// auto strip #include <edimp.hxx>
// auto strip #endif
// auto strip #ifndef _TBLSEL_HXX
// auto strip #include <tblsel.hxx>
// auto strip #endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif
// auto strip #ifndef _FMTANCHR_HXX
// auto strip #include <fmtanchr.hxx>
// auto strip #endif
namespace binfilter {

/*N*/ TYPEINIT1(SwFEShell,SwEditShell)

/***********************************************************************
#*  Class      :  SwFEShell
#*  Methode    :  EndAllActionAndCall()
#*
#*  Datum      :  MA 03. May. 93
#*  Update     :  MA 31. Oct. 95
#***********************************************************************/

//STRIP001 void SwFEShell::EndAllActionAndCall()
//STRIP001 {
//STRIP001  ViewShell *pTmp = this;
//STRIP001  do {
//STRIP001      if( pTmp->IsA( TYPE(SwCrsrShell) ) )
//STRIP001      {
//STRIP001          ((SwFEShell*)pTmp)->EndAction();
//STRIP001          ((SwFEShell*)pTmp)->CallChgLnk();
//STRIP001      }
//STRIP001      else
//STRIP001          pTmp->EndAction();
//STRIP001  } while( this != ( pTmp = (ViewShell*)pTmp->GetNext() ));
//STRIP001 }


/***********************************************************************
#*  Class       :  SwFEShell
#*  Methode     :  GetCntntPos
#*  Beschreibung:  Ermitteln des Cntnt's der dem Punkt am naechsten liegt
#*  Datum       :  MA 02. Jun. 92
#*  Update      :  MA 02. May. 95
#***********************************************************************/

//STRIP001 Point SwFEShell::GetCntntPos( const Point& rPoint, BOOL bNext ) const
//STRIP001 {
//STRIP001  SET_CURR_SHELL( (ViewShell*)this );
//STRIP001  return GetLayout()->GetNextPrevCntntPos( rPoint, bNext );
//STRIP001 }


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


//STRIP001 USHORT SwFEShell::GetPageNumber( const Point &rPoint ) const
//STRIP001 {
//STRIP001  const SwFrm *pPage = GetLayout()->Lower();
//STRIP001  while ( pPage && !pPage->Frm().IsInside( rPoint ) )
//STRIP001      pPage = pPage->GetNext();
//STRIP001  if ( pPage )
//STRIP001      return ((const SwPageFrm*)pPage)->GetPhyPageNum();
//STRIP001  else
//STRIP001      return 0;
//STRIP001 }


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

//STRIP001 #ifdef USED
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

//STRIP001 long SwFEShell::GetHeadFootFrmRect( SwRect &rToFill ) const
//STRIP001 {
//STRIP001  ASSERT( GetCurrFrm(), "Crsr geparkt?" );
//STRIP001
//STRIP001  long nRet = 0;
//STRIP001  const SwFrm *pFrm = GetCurrFrm();
//STRIP001  while ( pFrm && !pFrm->IsHeaderFrm() && !pFrm->IsFooterFrm() )
//STRIP001      pFrm = pFrm->GetUpper();
//STRIP001
//STRIP001  if ( pFrm )
//STRIP001  {
//STRIP001      const SwPageFrm *pPage = pFrm->FindPageFrm();
//STRIP001      rToFill = pFrm->Frm();
//STRIP001      rToFill.Pos() -= pPage->Frm().Pos();
//STRIP001
//STRIP001      //Wenn Kopf-/Fusszeilen vergroessert werden, sollte die Resthoehe der
//STRIP001      //PrtArea der Seite wenigstens 2cm (lMinBorder) betragen.
//STRIP001      const SwFrm *pBody = pPage->FindBodyCont();
//STRIP001      nRet = pBody->Frm().Top();
//STRIP001      if ( pFrm->IsHeaderFrm() )
//STRIP001      {
//STRIP001          nRet += pBody->Prt().Bottom();
//STRIP001          nRet -= lMinBorder;
//STRIP001          nRet -= pBody->Prt().Top();
//STRIP001      }
//STRIP001      else if ( pFrm->IsFooterFrm() )
//STRIP001      {
//STRIP001          nRet += pBody->Prt().Top();
//STRIP001          nRet += lMinBorder;
//STRIP001          nRet += pBody->Frm().Height() -
//STRIP001                  (pBody->Prt().Height() + pBody->Prt().Top());
//STRIP001      }
//STRIP001      nRet -= pPage->Frm().Top();
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }
//STRIP001 #endif

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
/*?*/           FrameNotify( this, FLY_DRAG_START );
/*N*/   }
/*N*/ }

//STRIP001 void SwFEShell::ShLooseFcs()
//STRIP001 {
//STRIP001  SwCrsrShell::ShLooseFcs();
//STRIP001
//STRIP001  if ( HasDrawView() && Imp()->GetDrawView()->HasMarkedObj() )
//STRIP001  {
//STRIP001      Imp()->GetDrawView()->SetMarkHdlHidden( TRUE );
//STRIP001      FrameNotify( this, FLY_DRAG_END );
//STRIP001  }
//STRIP001 //   ::ResetShell();
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::GetPhyPageNum()
|*  SwFEShell::GetVirtPageNum()
|*
|*  Ersterstellung      OK 07.07.93 08:20
|*  Letzte Aenderung    MA 03. Jan. 94
|*
*************************************************************************/

//STRIP001 USHORT SwFEShell::GetPhyPageNum()
//STRIP001 {
//STRIP001  SwFrm *pFrm = GetCurrFrm();
//STRIP001  if ( pFrm )
//STRIP001      return pFrm->GetPhyPageNum();
//STRIP001  return 0;
//STRIP001 }

//STRIP001 USHORT SwFEShell::GetVirtPageNum( const BOOL bCalcFrm )
//STRIP001 {
//STRIP001  SwFrm *pFrm = GetCurrFrm( bCalcFrm );
//STRIP001  if ( pFrm )
//STRIP001      return pFrm->GetVirtPageNum();
//STRIP001  return 0;
//STRIP001 }

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

//STRIP001 void lcl_SetAPageOffset( USHORT nOffset, SwPageFrm* pPage, SwFEShell* pThis )
//STRIP001 {
//STRIP001  pThis->StartAllAction();
//STRIP001  ASSERT( pPage->FindFirstBodyCntnt(),
//STRIP001          "SwFEShell _SetAPageOffset() ohne CntntFrm" );
//STRIP001
//STRIP001  SwFmtPageDesc aDesc( pPage->GetPageDesc() );
//STRIP001  aDesc.SetNumOffset( nOffset );
//STRIP001
//STRIP001  SwFrm *pFrm = pThis->GetCurrFrm( FALSE );
//STRIP001  if ( pFrm->IsInTab() )
//STRIP001      pThis->GetDoc()->SetAttr( aDesc, *pFrm->FindTabFrm()->GetFmt() );
//STRIP001  else
//STRIP001      pThis->GetDoc()->Insert( *pThis->GetCrsr(), aDesc );
//STRIP001
//STRIP001  pThis->EndAllAction();
//STRIP001 }

//STRIP001 void SwFEShell::SetNewPageOffset( USHORT nOffset )
//STRIP001 {
//STRIP001  GetLayout()->SetVirtPageNum( TRUE );
//STRIP001  const SwPageFrm *pPage = GetCurrFrm( FALSE )->FindPageFrm();
//STRIP001  lcl_SetAPageOffset( nOffset, (SwPageFrm*)pPage, this );
//STRIP001 }

//STRIP001 void SwFEShell::SetPageOffset( USHORT nOffset )
//STRIP001 {
//STRIP001  const SwPageFrm *pPage = GetCurrFrm( FALSE )->FindPageFrm();
//STRIP001  const SwRootFrm* pLayout = GetLayout();
//STRIP001  while ( pPage )
//STRIP001  {
//STRIP001      const SwFrm *pFlow = pPage->FindFirstBodyCntnt();
//STRIP001      if ( pFlow )
//STRIP001      {
//STRIP001          if ( pFlow->IsInTab() )
//STRIP001              pFlow = pFlow->FindTabFrm();
//STRIP001          const SwFmtPageDesc& rPgDesc = pFlow->GetAttrSet()->GetPageDesc();
//STRIP001          if ( rPgDesc.GetNumOffset() )
//STRIP001          {
//STRIP001              pLayout->SetVirtPageNum( TRUE );
//STRIP001              lcl_SetAPageOffset( nOffset, (SwPageFrm*)pPage, this );
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001      pPage = (SwPageFrm*)pPage->GetPrev();
//STRIP001  }
//STRIP001 }

//STRIP001 USHORT SwFEShell::GetPageOffset() const
//STRIP001 {
//STRIP001  const SwPageFrm *pPage = GetCurrFrm()->FindPageFrm();
//STRIP001  while ( pPage )
//STRIP001  {
//STRIP001      const SwFrm *pFlow = pPage->FindFirstBodyCntnt();
//STRIP001      if ( pFlow )
//STRIP001      {
//STRIP001          if ( pFlow->IsInTab() )
//STRIP001              pFlow = pFlow->FindTabFrm();
//STRIP001          const USHORT nOffset = pFlow->GetAttrSet()->GetPageDesc().GetNumOffset();
//STRIP001          if ( nOffset )
//STRIP001              return nOffset;
//STRIP001      }
//STRIP001      pPage = (SwPageFrm*)pPage->GetPrev();
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::InsertLabel()
|*
|*  Ersterstellung      MA 10. Feb. 94
|*  Letzte Aenderung    MA 10. Feb. 94
|*
*************************************************************************/

//STRIP001 void SwFEShell::InsertLabel( const SwLabelType eType, const String &rTxt,
//STRIP001                           const BOOL bBefore, const USHORT nId,
//STRIP001                           const BOOL bCpyBrd )
//STRIP001 {
//STRIP001  //NodeIndex der CrsrPosition besorgen, den Rest kann das Dokument
//STRIP001  //selbst erledigen.
//STRIP001  SwCntntFrm *pCnt = LTYPE_DRAW==eType ? 0 : GetCurrFrm( FALSE );
//STRIP001  if( LTYPE_DRAW==eType || pCnt )
//STRIP001  {
//STRIP001      StartAllAction();
//STRIP001
//STRIP001      ULONG nIdx = 0;
//STRIP001      SwFlyFrmFmt* pFlyFmt = 0;
//STRIP001      switch( eType )
//STRIP001      {
//STRIP001      case LTYPE_OBJECT:
//STRIP001      case LTYPE_FLY:
//STRIP001          if( pCnt->IsInFly() )
//STRIP001          {
//STRIP001              //Bei Flys den Index auf den StartNode herunterreichen.
//STRIP001              nIdx = pCnt->FindFlyFrm()->
//STRIP001                          GetFmt()->GetCntnt().GetCntntIdx()->GetIndex();
//STRIP001 //warum?? Bug 61913      ParkCrsr( GetCrsr()->GetPoint()->nNode );
//STRIP001          }
//STRIP001          break;
//STRIP001      case LTYPE_TABLE:
//STRIP001          if( pCnt->IsInTab() )
//STRIP001          {
//STRIP001              //Bei Tabellen den Index auf den TblNode herunterreichen.
//STRIP001              const SwTable& rTbl = *pCnt->FindTabFrm()->GetTable();
//STRIP001              nIdx = rTbl.GetTabSortBoxes()[ 0 ]
//STRIP001                          ->GetSttNd()->FindTableNode()->GetIndex();
//STRIP001          }
//STRIP001          break;
//STRIP001      case LTYPE_DRAW:
//STRIP001          if( Imp()->GetDrawView() )
//STRIP001          {
//STRIP001              SwDrawView *pDView = Imp()->GetDrawView();
//STRIP001              const SdrMarkList& rMrkList = pDView->GetMarkList();
//STRIP001              StartUndo();
//STRIP001
//STRIP001              ULONG nCount = rMrkList.GetMarkCount();
//STRIP001              for( ULONG i=0; i < nCount; i++ )
//STRIP001              {
//STRIP001                  SdrObject *pObj = rMrkList.GetMark(i)->GetObj();
//STRIP001                  if( !pObj->IsWriterFlyFrame() )
//STRIP001                  {
//STRIP001                      SwFlyFrmFmt *pFmt =
//STRIP001                          GetDoc()->InsertDrawLabel( rTxt, nId, *pObj );
//STRIP001                      if( !pFlyFmt )
//STRIP001                          pFlyFmt = pFmt;
//STRIP001                  }
//STRIP001              }
//STRIP001              EndUndo();
//STRIP001          }
//STRIP001          break;
//STRIP001      default:
//STRIP001          ASSERT( !this, "Crsr weder in Tabelle noch in Fly." );
//STRIP001      }
//STRIP001
//STRIP001      if( nIdx )
//STRIP001          pFlyFmt = GetDoc()->InsertLabel( eType, rTxt, bBefore, nId,
//STRIP001                                           nIdx, bCpyBrd );
//STRIP001
//STRIP001      SwFlyFrm* pFrm;
//STRIP001      const Point aPt( GetCrsrDocPos() );
//STRIP001      if( pFlyFmt && 0 != ( pFrm = pFlyFmt->GetFrm( &aPt )))
//STRIP001          SelectFlyFrm( *pFrm, TRUE );
//STRIP001
//STRIP001      EndAllActionAndCall();
//STRIP001  }
//STRIP001 }


/***********************************************************************
#*  Class       :  SwFEShell
#*  Methoden    :  Sort
#*  Datum       :  ??
#*  Update      :  ??
#***********************************************************************/

//STRIP001 BOOL SwFEShell::Sort(const SwSortOptions& rOpt)
//STRIP001 {
//STRIP001  if( !HasSelection() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  BOOL bRet;
//STRIP001  StartAllAction();
//STRIP001  if(IsTableMode())
//STRIP001  {
//STRIP001      // Tabelle sortieren
//STRIP001      // pruefe ob vom aktuellen Crsr der SPoint/Mark in einer Tabelle stehen
//STRIP001      SwFrm *pFrm = GetCurrFrm( FALSE );
//STRIP001      ASSERT( pFrm->FindTabFrm(), "Crsr nicht in Tabelle." );
//STRIP001
//STRIP001      // lasse ueber das Layout die Boxen suchen
//STRIP001      SwSelBoxes  aBoxes;
//STRIP001      GetTblSel(*this, aBoxes);
//STRIP001
//STRIP001      // die Crsr muessen noch aus dem Loesch Bereich entfernt
//STRIP001      // werden. Setze sie immer hinter/auf die Tabelle; ueber die
//STRIP001      // Dokument-Position werden sie dann immer an die alte Position gesetzt.
//STRIP001      while( !pFrm->IsCellFrm() )
//STRIP001          pFrm = pFrm->GetUpper();
//STRIP001      {
//STRIP001             /* #107993# ParkCursor->ParkCursorTab */
//STRIP001          ParkCursorInTab();
//STRIP001      }
//STRIP001
//STRIP001      // Sorting am Dokument aufrufen
//STRIP001      bRet = pDoc->SortTbl(aBoxes, rOpt);
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // Text sortieren und nichts anderes
//STRIP001      FOREACHPAM_START(this)
//STRIP001
//STRIP001          SwPaM* pPam = PCURCRSR;
//STRIP001
//STRIP001          SwPosition* pStart = pPam->Start();
//STRIP001          SwPosition* pEnd   = pPam->End();
//STRIP001
//STRIP001          SwNodeIndex aPrevIdx( pStart->nNode, -1 );
//STRIP001          ULONG nOffset = pEnd->nNode.GetIndex() - pStart->nNode.GetIndex();
//STRIP001          xub_StrLen nCntStt  = pStart->nContent.GetIndex();
//STRIP001
//STRIP001          // Das Sortieren
//STRIP001          bRet = pDoc->SortText(*pPam, rOpt);
//STRIP001
//STRIP001          // Selektion wieder setzen
//STRIP001          pPam->DeleteMark();
//STRIP001          pPam->GetPoint()->nNode.Assign( aPrevIdx.GetNode(), +1 );
//STRIP001          SwCntntNode* pCNd = pPam->GetCntntNode();
//STRIP001          xub_StrLen nLen = pCNd->Len();
//STRIP001          if( nLen > nCntStt )
//STRIP001              nLen = nCntStt;
//STRIP001          pPam->GetPoint()->nContent.Assign(pCNd, nLen );
//STRIP001          pPam->SetMark();
//STRIP001
//STRIP001          pPam->GetPoint()->nNode += nOffset;
//STRIP001          pCNd = pPam->GetCntntNode();
//STRIP001          pPam->GetPoint()->nContent.Assign( pCNd, pCNd->Len() );
//STRIP001
//STRIP001      FOREACHPAM_END()
//STRIP001  }
//STRIP001
//STRIP001  EndAllAction();
//STRIP001  return bRet;
//STRIP001 }

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

//STRIP001 USHORT SwFEShell::GetCurOutColNum( SwGetCurColNumPara* pPara ) const
//STRIP001 {
//STRIP001  USHORT nRet = 0;
//STRIP001  SwFrm* pFrm = GetCurrFrm();
//STRIP001  ASSERT( pFrm, "Crsr geparkt?" );
//STRIP001  if( pFrm )
//STRIP001  {
//STRIP001      pFrm = pFrm->IsInTab() ? (SwFrm*)pFrm->FindTabFrm()
//STRIP001                             : (SwFrm*)pFrm->FindSctFrm();
//STRIP001      ASSERT( pFrm, "No Tab, no Sect" );
//STRIP001      if( pFrm )
//STRIP001          nRet = _GetCurColNum( pFrm, pPara );
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

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

//STRIP001 void SwFEShell::CalcBoundRect( SwRect &rRect, RndStdIds nAnchorId,
//STRIP001  SwRelationOrient eRelOrient, BOOL bMirror, Point* pRef, Size* pPercent ) const
//STRIP001 {
//STRIP001  SwFrm *pFrm;
//STRIP001  SwFlyFrm *pFly;
//STRIP001  if( pRef )
//STRIP001  {
//STRIP001      pFrm = GetCurrFrm();
//STRIP001      if( 0 != ( pFly = pFrm->FindFlyFrm() ) )
//STRIP001          pFrm = pFly->GetAnchor();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pFly = FindFlyFrm();
//STRIP001      pFrm = pFly ? pFly->GetAnchor() : GetCurrFrm();
//STRIP001  }
//STRIP001
//STRIP001     sal_Bool bWrapThrough = sal_False;
//STRIP001     if ( pFly )
//STRIP001     {
//STRIP001         SwFlyFrmFmt* pFmt = (SwFlyFrmFmt*)pFly->GetFmt();
//STRIP001         const SwFmtSurround& rSurround = pFmt->GetSurround();
//STRIP001         bWrapThrough = rSurround.GetSurround() == SURROUND_THROUGHT;
//STRIP001     }
//STRIP001
//STRIP001  SwPageFrm* pPage = pFrm->FindPageFrm();
//STRIP001  bMirror = bMirror && !pPage->OnRightPage();
//STRIP001
//STRIP001  Point aPos;
//STRIP001     BOOL bVertic = FALSE;
//STRIP001     BOOL bRTL = FALSE;
//STRIP001
//STRIP001  if( FLY_PAGE == nAnchorId || FLY_AT_FLY == nAnchorId ) // LAYER_IMPL
//STRIP001  {
//STRIP001 #ifdef AMA_OUT_OF_FLY
//STRIP001      // Falls wir uns auch ausserhalb des Rahmens aufhalten duerfen
//STRIP001      SwFrm *pTmp = pFrm->FindPageFrm();
//STRIP001      rRect = pTmp->Frm();
//STRIP001      if( FLY_PAGE == nAnchorId )
//STRIP001          pFrm = pTmp;
//STRIP001 #else
//STRIP001      SwFrm *pTmp = pFrm;
//STRIP001      if( FLY_PAGE == nAnchorId )
//STRIP001          pFrm = pPage;
//STRIP001      else
//STRIP001          pFrm = pFrm->FindFlyFrm();
//STRIP001      if( !pFrm )
//STRIP001          pFrm = pTmp;
//STRIP001      rRect = pFrm->Frm();
//STRIP001         SWRECTFN( pFrm )
//STRIP001         bRTL = pFrm->IsRightToLeft();
//STRIP001      if ( bRTL )
//STRIP001          aPos = pFrm->Frm().TopRight();
//STRIP001      else
//STRIP001          aPos = (pFrm->Frm().*fnRect->fnGetPos)();
//STRIP001
//STRIP001         if( bVert )
//STRIP001      {
//STRIP001             bVertic = TRUE;
//STRIP001             bMirror = FALSE; // no mirroring in vertical environment
//STRIP001          switch ( eRelOrient )
//STRIP001          {
//STRIP001              case REL_PG_RIGHT:
//STRIP001                 case REL_FRM_RIGHT: aPos.Y() += pFrm->Prt().Height();
//STRIP001                 // no break!
//STRIP001              case PRTAREA:
//STRIP001                 case REL_PG_PRTAREA: aPos.Y() += pFrm->Prt().Top(); break;
//STRIP001          }
//STRIP001      }
//STRIP001         else if( bMirror )
//STRIP001      {
//STRIP001          switch ( eRelOrient )
//STRIP001          {
//STRIP001              case PRTAREA:
//STRIP001              case REL_PG_PRTAREA: aPos.X() += pFrm->Prt().Width();
//STRIP001              // kein break
//STRIP001              case REL_PG_RIGHT:
//STRIP001              case REL_FRM_RIGHT: aPos.X() += pFrm->Prt().Left(); break;
//STRIP001              default: aPos.X() += pFrm->Frm().Width();
//STRIP001          }
//STRIP001      }
//STRIP001         else if ( bRTL )
//STRIP001         {
//STRIP001             switch ( eRelOrient )
//STRIP001             {
//STRIP001                 case PRTAREA:
//STRIP001                 case REL_PG_PRTAREA: aPos.X() += pFrm->Prt().Width();
//STRIP001                 // kein break!
//STRIP001                 case REL_PG_LEFT:
//STRIP001                 case REL_FRM_LEFT: aPos.X() += pFrm->Prt().Left() -
//STRIP001                                             pFrm->Frm().Width(); break;
//STRIP001             }
//STRIP001         }
//STRIP001         else
//STRIP001         {
//STRIP001          switch ( eRelOrient )
//STRIP001          {
//STRIP001              case REL_PG_RIGHT:
//STRIP001              case REL_FRM_RIGHT: aPos.X() += pFrm->Prt().Width();
//STRIP001              // kein break!
//STRIP001              case PRTAREA:
//STRIP001              case REL_PG_PRTAREA: aPos.X() += pFrm->Prt().Left(); break;
//STRIP001          }
//STRIP001      }
//STRIP001 #endif
//STRIP001      if( pPercent )
//STRIP001          *pPercent = pFrm->Prt().SSize();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      BOOL bAtCntnt = FLY_AT_CNTNT == nAnchorId ||
//STRIP001                      FLY_AUTO_CNTNT == nAnchorId;  // LAYER_IMPL
//STRIP001      if( pRef && !bAtCntnt && pFly && pFly->IsFlyInCntFrm() )
//STRIP001          *pRef = ( (SwFlyInCntFrm*)pFly )->GetRefPoint();
//STRIP001
//STRIP001      SwFrm *pUpper = ( pFrm->IsPageFrm() || pFrm->IsFlyFrm() ) ?
//STRIP001                      pFrm : pFrm->GetUpper();
//STRIP001      rRect = pUpper->Frm();
//STRIP001         SWRECTFN( pUpper );
//STRIP001      if( pPercent )
//STRIP001          *pPercent = pUpper->Prt().SSize();
//STRIP001      if( bAtCntnt )
//STRIP001      {
//STRIP001          while( pUpper->IsColumnFrm() || pUpper->IsSctFrm() ||
//STRIP001                 pUpper->IsColBodyFrm() ) // auch ein Rahmen innerhalb einer Spalte darf
//STRIP001                                          // ueber die ganze Seite gehen
//STRIP001              pUpper = pUpper->GetUpper();
//STRIP001      }
//STRIP001      if( !pUpper->IsBodyFrm() )
//STRIP001      {
//STRIP001          rRect += pUpper->Prt().Pos();
//STRIP001          rRect.SSize( pUpper->Prt().SSize() );
//STRIP001          if ( pUpper->IsCellFrm() )//MA_FLY_HEIGHT
//STRIP001          {
//STRIP001              SwFrm *pTab = pUpper->FindTabFrm();
//STRIP001                 long nBottom = (pTab->GetUpper()->*fnRect->fnGetPrtBottom)();
//STRIP001                 (rRect.*fnRect->fnSetBottom)( nBottom );
//STRIP001          }
//STRIP001      }
//STRIP001      if( bAtCntnt )
//STRIP001      {
//STRIP001             (rRect.*fnRect->fnSetTop)( (pFrm->Frm().*fnRect->fnGetTop)() );
//STRIP001             // OD 26.03.2003 #105559# - determine frame, which gives the
//STRIP001             // environment for the fly frame, and use this environment frame
//STRIP001             // for setting top and height respectively left and width.
//STRIP001             SwFrm* pEnvironmentFrm = 0;
//STRIP001             if ( pFrm->IsInFly() )
//STRIP001             {
//STRIP001                 pEnvironmentFrm = pUpper;
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 pEnvironmentFrm = pPage;
//STRIP001             }
//STRIP001             if( bVert )
//STRIP001             {
//STRIP001                 rRect.Top( pEnvironmentFrm->Frm().Top() );
//STRIP001                 rRect.Height( pEnvironmentFrm->Frm().Height() );
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 rRect.Left( pEnvironmentFrm->Frm().Left() );
//STRIP001                 rRect.Width( pEnvironmentFrm->Frm().Width() );
//STRIP001             }
//STRIP001      }
//STRIP001      else  // bei zeichengebundenen lieber nur 90% der Hoehe ausnutzen
//STRIP001         {
//STRIP001             if( bVert )
//STRIP001                 rRect.Width( (rRect.Width()*9)/10 );
//STRIP001             else
//STRIP001                 rRect.Height( (rRect.Height()*9)/10 );
//STRIP001         }
//STRIP001
//STRIP001         bRTL = pFrm->IsRightToLeft();
//STRIP001      if ( bRTL )
//STRIP001          aPos = pFrm->Frm().TopRight();
//STRIP001      else
//STRIP001          aPos = (pFrm->Frm().*fnRect->fnGetPos)();
//STRIP001
//STRIP001         const SwTwips nBaseOfstForFly = ( pFrm->IsTxtFrm() && pFly ) ?
//STRIP001                                         ((SwTxtFrm*)pFrm)->GetBaseOfstForFly( !bWrapThrough ) :
//STRIP001                                          0;
//STRIP001         if( bVert )
//STRIP001      {
//STRIP001             bVertic = TRUE;
//STRIP001             bMirror = FALSE;
//STRIP001
//STRIP001          switch ( eRelOrient )
//STRIP001          {
//STRIP001                 case REL_FRM_RIGHT: aPos.Y() += pFrm->Prt().Height();
//STRIP001                                     aPos += (pFrm->Prt().*fnRect->fnGetPos)();
//STRIP001                                     break;
//STRIP001                 case PRTAREA: aPos += (pFrm->Prt().*fnRect->fnGetPos)();
//STRIP001                               aPos.Y() += nBaseOfstForFly;
//STRIP001                               break;
//STRIP001                 case REL_PG_RIGHT: aPos.Y() = pPage->Frm().Top()
//STRIP001                                             + pPage->Prt().Bottom(); break;
//STRIP001                 case REL_PG_PRTAREA: aPos.Y() = pPage->Frm().Top()
//STRIP001                                               + pPage->Prt().Top(); break;
//STRIP001              case REL_PG_LEFT:
//STRIP001                 case REL_PG_FRAME: aPos.Y() = pPage->Frm().Top(); break;
//STRIP001                 case FRAME: aPos.Y() += nBaseOfstForFly; break;
//STRIP001          }
//STRIP001      }
//STRIP001         else if( bMirror )
//STRIP001      {
//STRIP001          switch ( eRelOrient )
//STRIP001          {
//STRIP001              case REL_FRM_RIGHT: aPos.X() += pFrm->Prt().Left(); break;
//STRIP001              case FRAME:
//STRIP001              case REL_FRM_LEFT: aPos.X() += pFrm->Frm().Width(); break;
//STRIP001              case PRTAREA: aPos.X() += pFrm->Prt().Right(); break;
//STRIP001              case REL_PG_LEFT:
//STRIP001              case REL_PG_FRAME: aPos.X() = pPage->Frm().Right(); break;
//STRIP001              case REL_PG_PRTAREA: aPos.X() = pPage->Frm().Left()
//STRIP001                                            + pPage->Prt().Left(); break;
//STRIP001          }
//STRIP001      }
//STRIP001         else if ( bRTL )
//STRIP001         {
//STRIP001             switch ( eRelOrient )
//STRIP001             {
//STRIP001                 case REL_FRM_LEFT:
//STRIP001                     aPos.X() = pFrm->Frm().Left() +
//STRIP001                                pFrm->Prt().Left();
//STRIP001                     break;
//STRIP001
//STRIP001                 case PRTAREA:
//STRIP001                     aPos.X() = pFrm->Frm().Left() + pFrm->Prt().Left() +
//STRIP001                                pFrm->Prt().Width();
//STRIP001                     aPos.X() += nBaseOfstForFly;
//STRIP001                     break;
//STRIP001
//STRIP001                 case REL_PG_LEFT:
//STRIP001                     aPos.X() = pPage->Frm().Left() + pPage->Prt().Left();
//STRIP001                     break;
//STRIP001
//STRIP001                 case REL_PG_PRTAREA:
//STRIP001                     aPos.X() = pPage->Frm().Left() + pPage->Prt().Left() +
//STRIP001                                pPage->Prt().Width() ;
//STRIP001                     break;
//STRIP001
//STRIP001              case REL_PG_RIGHT:
//STRIP001                 case REL_PG_FRAME:
//STRIP001                     aPos.X() = pPage->Frm().Right();
//STRIP001                     break;
//STRIP001
//STRIP001              case FRAME:
//STRIP001                     aPos.X() += nBaseOfstForFly;
//STRIP001                     break;
//STRIP001             }
//STRIP001         }
//STRIP001      else
//STRIP001      {
//STRIP001          switch ( eRelOrient )
//STRIP001          {
//STRIP001              case REL_FRM_RIGHT: aPos.X() += pFrm->Prt().Width();
//STRIP001                                     aPos += pFrm->Prt().Pos();
//STRIP001                                     break;
//STRIP001              case PRTAREA: aPos += pFrm->Prt().Pos();
//STRIP001                               aPos.X() += nBaseOfstForFly;
//STRIP001                               break;
//STRIP001              case REL_PG_RIGHT: aPos.X() = pPage->Frm().Left()
//STRIP001                                          + pPage->Prt().Right(); break;
//STRIP001              case REL_PG_PRTAREA: aPos.X() = pPage->Frm().Left()
//STRIP001                                            + pPage->Prt().Left(); break;
//STRIP001              case REL_PG_LEFT:
//STRIP001              case REL_PG_FRAME: aPos.X() = pPage->Frm().Left(); break;
//STRIP001                 case FRAME: aPos.X() += nBaseOfstForFly; break;
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001  }
//STRIP001  if( !pRef )
//STRIP001  {
//STRIP001         if( bVertic )
//STRIP001             rRect.Pos( aPos.X() - rRect.Width() - rRect.Left(), rRect.Top() - aPos.Y() );
//STRIP001         else if ( bRTL )
//STRIP001             rRect.Pos( - ( rRect.Right() - aPos.X() ), rRect.Top() - aPos.Y() );
//STRIP001      else
//STRIP001             rRect.Pos( rRect.Left() - aPos.X(), rRect.Top() - aPos.Y() );
//STRIP001      if( bMirror )
//STRIP001          rRect.Pos( -rRect.Right(), rRect.Top() );
//STRIP001  }
//STRIP001 }

//STRIP001 Size SwFEShell::GetGraphicDefaultSize() const
//STRIP001 {
//STRIP001  Size aRet;
//STRIP001  SwFlyFrm *pFly = FindFlyFrm();
//STRIP001  if ( pFly )
//STRIP001  {
//STRIP001      aRet = pFly->GetAnchor()->Prt().SSize();
//STRIP001
//STRIP001      SwRect aBound;
//STRIP001      CalcBoundRect( aBound, pFly->GetFmt()->GetAnchor().GetAnchorId());
//STRIP001      if ( pFly->GetAnchor()->IsVertical() )
//STRIP001          aRet.Width() = aBound.Width();
//STRIP001      else
//STRIP001          aRet.Height() = aBound.Height();
//STRIP001  }
//STRIP001  return aRet;
//STRIP001 }
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
