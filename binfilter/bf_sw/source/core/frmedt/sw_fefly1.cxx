/*************************************************************************
 *
 *  $RCSfile: sw_fefly1.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:57 $
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

#ifndef _SFXITEMITER_HXX //autogen
#include <svtools/itemiter.hxx>
#endif
#ifndef _GOODIES_IMAPOBJ_HXX
#include <svtools/imapobj.hxx>
#endif
#ifndef _SOERR_HXX //autogen
#include <so3/soerr.hxx>
#endif
#ifndef _SVX_PROTITEM_HXX //autogen
#include <bf_svx/protitem.hxx>
#endif
#ifndef _SVDOGRP_HXX //autogen
#include <bf_svx/svdogrp.hxx>
#endif
#ifndef _SVDOUNO_HXX //autogen
#include <bf_svx/svdouno.hxx>
#endif
#ifndef _SVX_FMGLOB_HXX
#include <bf_svx/fmglob.hxx>
#endif
#ifndef _SFX_INTERNO_HXX //autogen
#include <bf_sfx2/interno.hxx>
#endif
#ifndef _COM_SUN_STAR_FORM_FORMBUTTONTYPE_HPP_
#include <com/sun/star/form/FormButtonType.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif

#ifndef _FMTANCHR_HXX //autogen
#include <fmtanchr.hxx>
#endif
#ifndef _TXTFLCNT_HXX //autogen
#include <txtflcnt.hxx>
#endif
#ifndef _FMTCNTNT_HXX //autogen
#include <fmtcntnt.hxx>
#endif
#ifndef _FMTORNT_HXX //autogen
#include <fmtornt.hxx>
#endif
#ifndef _FMTFLCNT_HXX //autogen
#include <fmtflcnt.hxx>
#endif
#ifndef _FMTURL_HXX //autogen
#include <fmturl.hxx>
#endif
#ifndef _FMTCLDS_HXX //autogen
#include <fmtclds.hxx>
#endif
#ifndef _FMTFSIZE_HXX //autogen
#include <fmtfsize.hxx>
#endif
#ifndef _DOCARY_HXX
#include <docary.hxx>
#endif
#ifndef _FESH_HXX
#include <fesh.hxx>
#endif
#ifndef _ROOTFRM_HXX
#include <rootfrm.hxx>
#endif
#ifndef _PAGEFRM_HXX
#include <pagefrm.hxx>
#endif
#ifndef _CNTFRM_HXX
#include <cntfrm.hxx>
#endif
#ifndef _TXTFRM_HXX
#include <txtfrm.hxx>
#endif
#ifndef _VIEWIMP_HXX
#include <viewimp.hxx>
#endif
#ifndef _VISCRS_HXX
#include <viscrs.hxx>
#endif
#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _DVIEW_HXX
#include <dview.hxx>
#endif
#ifndef _DFLYOBJ_HXX
#include <dflyobj.hxx>
#endif
#ifndef _DCONTACT_HXX
#include <dcontact.hxx>
#endif
#ifndef _FRMFMT_HXX
#include <frmfmt.hxx>
#endif
#ifndef _FLYFRM_HXX
#include <flyfrm.hxx>
#endif
#ifndef _NDTXT_HXX
#include <ndtxt.hxx>
#endif
#ifndef _EDIMP_HXX
#include <edimp.hxx>
#endif
#ifndef _TBLSEL_HXX
#include <tblsel.hxx>
#endif
#ifndef _SWTABLE_HXX
#include <swtable.hxx>
#endif
#ifndef _MVSAVE_HXX
#include <mvsave.hxx>       // Strukturen zum Sichern beim Move/Delete
#endif
#ifndef _NDGRF_HXX
#include <ndgrf.hxx>
#endif
#ifndef _FLYFRMS_HXX
#include <flyfrms.hxx>
#endif
#ifndef _FLYPOS_HXX
#include <flypos.hxx>
#endif
#ifndef _FLDBAS_HXX
#include <fldbas.hxx>
#endif
#ifndef _FMTFLD_HXX
#include <fmtfld.hxx>
#endif
#ifndef _SWUNDO_HXX
#include <swundo.hxx>
#endif
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;

//Zum anmelden von Flys in Flys in ...
//definiert in layout/frmtool.cxx
//STRIP001 void RegistFlys( SwPageFrm*, const SwLayoutFrm* );

/***********************************************************************
#*  Class       :  SwDoc
#*  Methode     :  UseSpzLayoutFmt
#*  Beschreibung:  Anhand des Request werden zu dem Format entsprechende
#*      Aenderungen an den Spezifischen Layouts vorgenommen.
#*  Datum       :  MA 23. Sep. 92
#*  Update      :  JP 09.03.98
#***********************************************************************/

//STRIP001 sal_Bool lcl_SetNewFlyPos( const SwNode& rNode, SwFmtAnchor& rAnchor,
//STRIP001                      const Point& rPt )
//STRIP001 {
//STRIP001  sal_Bool bRet = sal_False;
//STRIP001  const SwStartNode* pStNode = rNode.FindFlyStartNode();
//STRIP001  if( pStNode )
//STRIP001  {
//STRIP001      SwPosition aPos( *pStNode );
//STRIP001      rAnchor.SetAnchor( &aPos );
//STRIP001      bRet = sal_True;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      const SwCntntFrm* pCFrm = rNode.GetCntntNode()->GetFrm( &rPt, 0, sal_False );
//STRIP001      const SwPageFrm *pPg = pCFrm ? pCFrm->FindPageFrm() : 0;
//STRIP001
//STRIP001      rAnchor.SetPageNum( pPg ? pPg->GetPhyPageNum() : 1 );
//STRIP001      rAnchor.SetType( FLY_PAGE );
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*N*/ BOOL lcl_FindAnchorPos( SwDoc& rDoc, const Point& rPt, const SwFrm& rFrm,
/*N*/                       SfxItemSet& rSet )
/*N*/ {
/*N*/   BOOL bRet = TRUE;
/*N*/   SwFmtAnchor aNewAnch( (SwFmtAnchor&)rSet.Get( RES_ANCHOR ) );
/*N*/   RndStdIds nNew = aNewAnch.GetAnchorId();
/*N*/   const SwFrm *pNewAnch;
/*N*/
/*N*/   //Neuen Anker ermitteln
/*N*/   Point aTmpPnt( rPt );
/*N*/   switch( nNew )
/*N*/   {
/*N*/   case FLY_IN_CNTNT:  // sollte der nicht auch mit hinein?
/*N*/   case FLY_AT_CNTNT:
/*N*/   case FLY_AUTO_CNTNT: // LAYER_IMPL
/*N*/       {
/*N*/           //Ausgehend von der linken oberen Ecke des Fly den
/*N*/           //dichtesten CntntFrm suchen.
/*N*/           const SwFrm* pFrm = rFrm.IsFlyFrm() ? ((SwFlyFrm&)rFrm).GetAnchor()
/*N*/                                               : &rFrm;
/*N*/           pNewAnch = ::binfilter::FindAnchor( pFrm, aTmpPnt );
/*N*/           if( pNewAnch->IsProtected() )
/*N*/           {
/*N*/               bRet = FALSE;
/*N*/               break;
/*N*/           }
/*N*/
/*N*/           SwPosition aPos( *((SwCntntFrm*)pNewAnch)->GetNode() );
/*N*/           if( FLY_AUTO_CNTNT == nNew || FLY_IN_CNTNT == nNew )
/*N*/           {
/*N*/               // es muss ein TextNode gefunden werden, denn nur in diesen
/*N*/               // ist ein Inhaltsgebundene Frames zu verankern
/*N*/               SwCrsrMoveState aState( MV_SETONLYTEXT );
/*N*/               aTmpPnt.X() -= 1;                   //nicht im Fly landen!!
/*N*/               if( !pNewAnch->GetCrsrOfst( &aPos, aTmpPnt, &aState ) )
/*N*/               {
/*N*/                   SwCntntNode* pCNd = ((SwCntntFrm*)pNewAnch)->GetNode();
/*N*/                   if( pNewAnch->Frm().Bottom() < aTmpPnt.Y() )
/*N*/                       pCNd->MakeStartIndex( &aPos.nContent );
/*N*/                   else
/*N*/                       pCNd->MakeEndIndex( &aPos.nContent );
/*N*/               }
/*N*/           }
/*N*/           aNewAnch.SetAnchor( &aPos );
/*N*/       }
/*N*/       break;
/*N*/
/*N*/   case FLY_AT_FLY: // LAYER_IMPL
/*N*/       {
/*N*/           //Ausgehend von der linken oberen Ecke des Fly den
/*N*/           //dichtesten SwFlyFrm suchen.
/*N*/           SwCrsrMoveState aState( MV_SETONLYTEXT );
/*N*/           SwPosition aPos( rDoc.GetNodes() );
/*N*/           aTmpPnt.X() -= 1;                   //nicht im Fly landen!!
/*N*/           rDoc.GetRootFrm()->GetCrsrOfst( &aPos, aTmpPnt, &aState );
/*N*/           pNewAnch = ::binfilter::FindAnchor(
/*N*/               aPos.nNode.GetNode().GetCntntNode()->GetFrm( 0, 0, sal_False ),
/*N*/               aTmpPnt )->FindFlyFrm();
/*N*/
/*N*/           if( pNewAnch && &rFrm != pNewAnch && !pNewAnch->IsProtected() )
/*N*/           {
/*N*/               aPos.nNode = *((SwFlyFrm*)pNewAnch)->GetFmt()->GetCntnt().
/*N*/                               GetCntntIdx();
/*N*/               aNewAnch.SetAnchor( &aPos );
/*N*/               break;
/*N*/           }
/*N*/       }
/*N*/
/*N*/       aNewAnch.SetType( nNew = FLY_PAGE );
/*N*/       // no break
/*N*/
/*N*/   case FLY_PAGE:
/*N*/       pNewAnch = rFrm.FindPageFrm();
/*N*/       aNewAnch.SetPageNum( pNewAnch->GetPhyPageNum() );
/*N*/       break;
/*N*/
/*N*/   default:
/*N*/       ASSERT( !&rDoc, "Falsche ID fuer neuen Anker." );
/*N*/   }
/*N*/
/*N*/   rSet.Put( aNewAnch );
/*N*/   return bRet;
/*N*/ }

//
//! also used in unoframe.cxx
//
/*N*/ sal_Bool lcl_ChkAndSetNewAnchor( const SwFlyFrm& rFly, SfxItemSet& rSet )
/*N*/ {
/*N*/   const SwFrmFmt& rFmt = *rFly.GetFmt();
/*N*/   const SwFmtAnchor &rOldAnch = rFmt.GetAnchor();
/*N*/   const RndStdIds nOld = rOldAnch.GetAnchorId();
/*N*/
/*N*/   RndStdIds nNew = ((SwFmtAnchor&)rSet.Get( RES_ANCHOR )).GetAnchorId();
/*N*/
/*N*/   if( nOld == nNew )
/*N*/       return sal_False;
/*N*/
/*N*/   SwDoc* pDoc = (SwDoc*)rFmt.GetDoc();
/*N*/
/*N*/ #ifndef PRODUCT
/*N*/   ASSERT( !(nNew == FLY_PAGE &&
/*N*/       (FLY_AT_CNTNT==nOld || FLY_AUTO_CNTNT==nOld || FLY_IN_CNTNT==nOld ) &&
/*N*/       pDoc->IsInHeaderFooter( rOldAnch.GetCntntAnchor()->nNode )),
/*N*/           "Unerlaubter Ankerwechsel in Head/Foot." );
/*N*/ #endif
/*N*/
/*N*/   return ::binfilter::lcl_FindAnchorPos( *pDoc, rFly.Frm().Pos(), rFly, rSet );
/*N*/ }

//STRIP001 void SwFEShell::SelectFlyFrm( SwFlyFrm& rFrm, sal_Bool bNew )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001
//STRIP001  //  Wenn es ein neuer Rahmen ist, so soll er selektiert sein.
//STRIP001  //  !!Rahmen immer selektieren, wenn sie nicht selektiert sind.
//STRIP001  //  - Es kann ein neuer 'alter' sein weil der Anker gewechselt wurde.
//STRIP001  //  - 'alte' Rahmen sind vorher immer selektiert denn sonst wird nix
//STRIP001  //    an ihnen veraendert.
//STRIP001  //  Der Rahmen darf nicht per Dokumentposition selektiert werden, weil er
//STRIP001  //  auf jedenfall selektiert sein muss!
//STRIP001  SwViewImp *pImp = Imp();
//STRIP001  if( GetWin() && (bNew || !pImp->GetDrawView()->HasMarkedObj()) )
//STRIP001  {
//STRIP001      ASSERT( rFrm.IsFlyFrm(), "SelectFlyFrm will einen Fly" );
//STRIP001
//STRIP001      //Wenn der Fly bereits selektiert ist gibt es hier ja wohl nichts
//STRIP001      //zu tun.
//STRIP001      if ( FindFlyFrm() == &rFrm )
//STRIP001          return;
//STRIP001
//STRIP001      //Damit der Anker ueberhaupt noch gepaintet wird.
//STRIP001      if( rFrm.IsFlyInCntFrm() && rFrm.GetAnchor() )
//STRIP001           rFrm.GetAnchor()->SetCompletePaint();
//STRIP001
//STRIP001      //Hier wurde immer kalkuliert. Leider ist der Sonderfall Fly in Fly mit
//STRIP001      //Spalten u.U. sehr kritisch wenn der innenliegende zuerst formatiert
//STRIP001      //wird. Um kein Risiko einzugehen entschaerfen wir nur diesen Sonderfall.
//STRIP001      if( !rFrm.GetAnchor()->IsInFly() )
//STRIP001          rFrm.Calc();
//STRIP001
//STRIP001      if( pImp->GetDrawView()->HasMarkedObj() )
//STRIP001          pImp->GetDrawView()->UnmarkAll();
//STRIP001
//STRIP001      pImp->GetDrawView()->MarkObj( rFrm.GetVirtDrawObj(),
//STRIP001                                    pImp->GetPageView(), sal_False, sal_False );
//STRIP001      KillPams();
//STRIP001      ClearMark();
//STRIP001      SelFlyGrabCrsr();
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::FindFlyFrm()
|*
|*  Beschreibung        Liefert den Fly wenn einer Selektiert ist.
|*  Ersterstellung      MA 03. Nov. 92
|*  Letzte Aenderung    MA 05. Mar. 96
|*
*************************************************************************/

/*N*/ SwFlyFrm *SwFEShell::FindFlyFrm() const
/*N*/ {
/*N*/   if ( Imp()->HasDrawView() )
/*N*/   {
/*N*/       // Ein Fly ist genau dann erreichbar, wenn er selektiert ist.
/*N*/       const SdrMarkList &rMrkList = Imp()->GetDrawView()->GetMarkList();
/*N*/       if( rMrkList.GetMarkCount() != 1 )
/*N*/           return 0;
/*N*/
/*?*/       SdrObject *pO = rMrkList.GetMark( 0 )->GetObj();
/*?*/       return pO->IsWriterFlyFrame() ? ((SwVirtFlyDrawObj*)pO)->GetFlyFrm() : 0;
/*N*/   }
/*N*/   return 0;
/*N*/ }

/*************************************************************************
|*
|*  SwFEShell::IsFlyInFly()
|*
|*  Beschreibung        Liefert sal_True, wenn der aktuelle Fly an einem anderen
|*                      verankert werden koennte (also innerhalb ist)
|*  Ersterstellung      AMA 11. Sep. 97
|*  Letzte Aenderung    AMA 14. Jan. 98
|*
*************************************************************************/

//STRIP001 const SwFrmFmt* SwFEShell::IsFlyInFly()
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001
//STRIP001  if ( !Imp()->HasDrawView() )
//STRIP001      return NULL;
//STRIP001
//STRIP001  const SdrMarkList &rMrkList = Imp()->GetDrawView()->GetMarkList();
//STRIP001  if ( !rMrkList.GetMarkCount() )
//STRIP001  {
//STRIP001      SwCntntFrm *pCntnt = GetCurrFrm( sal_False );
//STRIP001      if( !pCntnt )
//STRIP001          return NULL;
//STRIP001      SwFlyFrm *pFly = pCntnt->FindFlyFrm();
//STRIP001      if ( !pFly )
//STRIP001          return NULL;
//STRIP001      return pFly->GetFmt();
//STRIP001  }
//STRIP001  else if ( rMrkList.GetMarkCount() != 1 ||
//STRIP001       !GetUserCall(rMrkList.GetMark( 0 )->GetObj()) )
//STRIP001      return NULL;
//STRIP001
//STRIP001  SdrObject *pObj = rMrkList.GetMark( 0 )->GetObj();
//STRIP001
//STRIP001  SwFrmFmt *pFmt = FindFrmFmt( pObj );
//STRIP001  if( pFmt && FLY_AT_FLY == pFmt->GetAnchor().GetAnchorId() )
//STRIP001  {
//STRIP001      SwFrm* pFly = pObj->IsWriterFlyFrame() ?
//STRIP001          ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm()->GetAnchor() :
//STRIP001          ((SwDrawContact*)GetUserCall(pObj))->GetAnchor();
//STRIP001      ASSERT( pFly, "IsFlyInFly: Where's my anchor?" );
//STRIP001      ASSERT( pFly->IsFlyFrm(), "IsFlyInFly: Funny anchor!" );
//STRIP001      return ((SwFlyFrm*)pFly)->GetFmt();
//STRIP001  }
//STRIP001
//STRIP001  Point aTmpPos = pObj->GetBoundRect().TopLeft();
//STRIP001
//STRIP001  SwFrm *pTxtFrm;
//STRIP001  {
//STRIP001      SwCrsrMoveState aState( MV_SETONLYTEXT );
//STRIP001      SwNodeIndex aSwNodeIndex( GetDoc()->GetNodes() );
//STRIP001      SwPosition aPos( aSwNodeIndex );
//STRIP001      Point aPoint( aTmpPos );
//STRIP001      aPoint.X() -= 1;                    //nicht im Fly landen!!
//STRIP001      GetLayout()->GetCrsrOfst( &aPos, aPoint, &aState );
//STRIP001         // OD 01.07.2003 #108784# - determine text frame by left-top-corner
//STRIP001         // of object
//STRIP001         //pTxtFrm = aPos.nNode.GetNode().GetCntntNode()->GetFrm( 0, 0, sal_False );
//STRIP001         pTxtFrm = aPos.nNode.GetNode().GetCntntNode()->GetFrm( &aTmpPos, 0, sal_False );
//STRIP001  }
//STRIP001  const SwFrm *pTmp = ::FindAnchor( pTxtFrm, aTmpPos );
//STRIP001  const SwFlyFrm *pFly = pTmp->FindFlyFrm();
//STRIP001  if( pFly )
//STRIP001      return pFly->GetFmt();
//STRIP001  return NULL;
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::SetFlyPos
|*
|*  Ersterstellung      MA 14. Jan. 93
|*  Letzte Aenderung    MA 14. Feb. 95
|*
*************************************************************************/

//STRIP001 void SwFEShell::SetFlyPos( const Point& rAbsPos )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001
//STRIP001  //Bezugspunkt in Dokumentkoordinaten bestimmen
//STRIP001  SwCntntFrm *pCntnt = GetCurrFrm( sal_False );
//STRIP001  if( !pCntnt )
//STRIP001      return;
//STRIP001  SwFlyFrm *pFly = pCntnt->FindFlyFrm();
//STRIP001  if ( !pFly )
//STRIP001      return;
//STRIP001
//STRIP001  SwSaveHdl aSaveX( Imp() );
//STRIP001
//STRIP001  //Bei Absatzgebundenen Flys muss ausgehend von der absoluten
//STRIP001  //Position ein neuer Anker gesetzt werden. Anker und neue RelPos werden
//STRIP001  //vom Fly selbst berechnet und gesetzt.
//STRIP001  if ( pFly->IsFlyAtCntFrm() )
//STRIP001      ((SwFlyAtCntFrm*)pFly)->SetAbsPos( rAbsPos );
//STRIP001  else
//STRIP001  {
//STRIP001      const SwFrm *pAnch = pFly->GetAnchor();
//STRIP001      pAnch->Calc();
//STRIP001      Point aOrient( pAnch->Frm().Pos() );
//STRIP001
//STRIP001      if ( pFly->IsFlyInCntFrm() )
//STRIP001          aOrient.X() = rAbsPos.X();
//STRIP001
//STRIP001      //RelPos errechnen.
//STRIP001      aOrient.X() = rAbsPos.X() - aOrient.X();
//STRIP001      aOrient.Y() = rAbsPos.Y() - aOrient.Y();
//STRIP001      pFly->ChgRelPos( aOrient );
//STRIP001  }
//STRIP001  pFly->Calc();
//STRIP001  CallChgLnk();       // rufe das AttrChangeNotify auf der UI-Seite.
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::FindAnchorPos
|*
|*  Ersterstellung      AMA 24. Sep. 97
|*  Letzte Aenderung    AMA 24. Sep. 97
|*
*************************************************************************/

//STRIP001 Point SwFEShell::FindAnchorPos( const Point& rAbsPos, sal_Bool bMoveIt )
//STRIP001 {
//STRIP001     Point aRet;
//STRIP001
//STRIP001  SET_CURR_SHELL( this );
//STRIP001
//STRIP001  if ( !Imp()->HasDrawView() )
//STRIP001      return aRet;
//STRIP001
//STRIP001  const SdrMarkList &rMrkList = Imp()->GetDrawView()->GetMarkList();
//STRIP001  if ( rMrkList.GetMarkCount() != 1 ||
//STRIP001       !GetUserCall(rMrkList.GetMark( 0 )->GetObj()) )
//STRIP001      return aRet;
//STRIP001
//STRIP001     SdrObject* pObj = rMrkList.GetMark( 0 )->GetObj();
//STRIP001     SwFmt* pFmt = ::FindFrmFmt( pObj );
//STRIP001  SwFmtAnchor aAnch( pFmt->GetAnchor() );
//STRIP001  RndStdIds nAnchorId = aAnch.GetAnchorId();
//STRIP001
//STRIP001  if ( FLY_IN_CNTNT == nAnchorId )
//STRIP001      return aRet;
//STRIP001
//STRIP001  sal_Bool bFlyFrame = pObj->IsWriterFlyFrame();
//STRIP001
//STRIP001     SwFlyFrm* pFly;
//STRIP001     const SwFrm* pOldAnch;
//STRIP001  const SwFrm* pFooterOrHeader = NULL;
//STRIP001
//STRIP001  if( bFlyFrame )
//STRIP001  {
//STRIP001      //Bezugspunkt in Dokumentkoordinaten bestimmen
//STRIP001      SwCntntFrm *pCntnt = GetCurrFrm( sal_False );
//STRIP001      if( !pCntnt )
//STRIP001          return aRet;
//STRIP001      pFly = pCntnt->FindFlyFrm();
//STRIP001      if ( !pFly )
//STRIP001          return aRet;
//STRIP001      pOldAnch = pFly->GetAnchor();
//STRIP001      if( !pOldAnch )
//STRIP001          return aRet;
//STRIP001      if( FLY_PAGE != nAnchorId )
//STRIP001          pFooterOrHeader = pCntnt->FindFooterOrHeader();
//STRIP001  }
//STRIP001     // OD 26.06.2003 #108784# - set <pFooterOrHeader> also for drawing
//STRIP001     // objects, but not for control objects.
//STRIP001     // Necessary for moving 'anchor symbol' at the user interface inside header/footer.
//STRIP001     else if ( !::CheckControlLayer( pObj ) )
//STRIP001     {
//STRIP001         SwCntntFrm *pCntnt = GetCurrFrm( sal_False );
//STRIP001         if( !pCntnt )
//STRIP001             return aRet;
//STRIP001         pFooterOrHeader = pCntnt->FindFooterOrHeader();
//STRIP001     }
//STRIP001
//STRIP001  //Ausgehend von der linken oberen Ecke des Fly den
//STRIP001  //dichtesten SwFlyFrm suchen.
//STRIP001  SwCntntFrm *pTxtFrm;
//STRIP001  {
//STRIP001      SwCrsrMoveState aState( MV_SETONLYTEXT );
//STRIP001      SwPosition aPos( GetDoc()->GetNodes().GetEndOfExtras() );
//STRIP001      Point aTmpPnt( rAbsPos );
//STRIP001      GetLayout()->GetCrsrOfst( &aPos, aTmpPnt, &aState );
//STRIP001      pTxtFrm = aPos.nNode.GetNode().GetCntntNode()->GetFrm(0,&aPos,FALSE );
//STRIP001  }
//STRIP001  const SwFrm *pNewAnch;
//STRIP001  if( pTxtFrm )
//STRIP001  {
//STRIP001      if( FLY_PAGE == nAnchorId )
//STRIP001          pNewAnch = pTxtFrm->FindPageFrm();
//STRIP001      else
//STRIP001      {
//STRIP001          pNewAnch = ::FindAnchor( pTxtFrm, rAbsPos );
//STRIP001
//STRIP001          if( FLY_AT_FLY == nAnchorId ) // LAYER_IMPL
//STRIP001              pNewAnch = pNewAnch->FindFlyFrm();
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      pNewAnch = 0;
//STRIP001
//STRIP001  if( pNewAnch && !pNewAnch->IsProtected() )
//STRIP001  {
//STRIP001      const SwFlyFrm* pCheck = bFlyFrame ? pNewAnch->FindFlyFrm() : 0;
//STRIP001      // Falls wir innerhalb eines Rahmens landen, muss sichergestellt werden,
//STRIP001      // dass der Rahmen nicht in seinem eigenen Inhalt landet!
//STRIP001      while( pCheck )
//STRIP001      {
//STRIP001          if( pCheck == pFly )
//STRIP001              break;
//STRIP001          const SwFrm *pTmp = pCheck->GetAnchor();
//STRIP001          pCheck = pTmp ? pTmp->FindFlyFrm() : NULL;
//STRIP001      }
//STRIP001      // Es darf nicht aus einer Kopf-/Fusszeile in einen anderen Bereich
//STRIP001      // gewechselt werden, es darf nicht in eine Kopf-/Fusszeile hinein-
//STRIP001      // gewechselt werden.
//STRIP001      if( !pCheck &&
//STRIP001          pFooterOrHeader == pNewAnch->FindFooterOrHeader() )
//STRIP001      {
//STRIP001             aRet = pNewAnch->GetFrmAnchorPos( ::HasWrap( pObj ) );
//STRIP001
//STRIP001             if( bMoveIt || nAnchorId == FLY_AUTO_CNTNT )
//STRIP001          {
//STRIP001              SwFmtAnchor aAnch( pFmt->GetAnchor() );
//STRIP001              switch ( nAnchorId )
//STRIP001              {
//STRIP001                  case FLY_AT_CNTNT:
//STRIP001                  {
//STRIP001                      SwPosition *pPos = (SwPosition*)aAnch.GetCntntAnchor();
//STRIP001                      pPos->nNode = *pTxtFrm->GetNode();
//STRIP001                      pPos->nContent.Assign(0,0);
//STRIP001                      break;
//STRIP001                  }
//STRIP001                  case FLY_PAGE:
//STRIP001                  {
//STRIP001                      aAnch.SetPageNum( ((const SwPageFrm*)pNewAnch)->
//STRIP001                                        GetPhyPageNum() );
//STRIP001                      break;
//STRIP001                  }
//STRIP001                  case FLY_AT_FLY:
//STRIP001                  {
//STRIP001                      SwPosition aPos( *((SwFlyFrm*)pNewAnch)->GetFmt()->
//STRIP001                                                GetCntnt().GetCntntIdx() );
//STRIP001                      aAnch.SetAnchor( &aPos );
//STRIP001                      break;
//STRIP001                  }
//STRIP001                  case FLY_AUTO_CNTNT:
//STRIP001                  {
//STRIP001                      SwPosition *pPos = (SwPosition*)aAnch.GetCntntAnchor();
//STRIP001                      Point aTmpPnt( rAbsPos );
//STRIP001                      if( pTxtFrm->GetCrsrOfst( pPos, aTmpPnt, NULL ) )
//STRIP001                      {
//STRIP001                          SwRect aTmpRect;
//STRIP001                          pTxtFrm->GetCharRect( aTmpRect, *pPos );
//STRIP001                          aRet = aTmpRect.Pos();
//STRIP001                      }
//STRIP001                      else
//STRIP001                      {
//STRIP001                          pPos->nNode = *pTxtFrm->GetNode();
//STRIP001                          pPos->nContent.Assign(0,0);
//STRIP001                      }
//STRIP001                      break;
//STRIP001                  }
//STRIP001              }
//STRIP001              if( bMoveIt )
//STRIP001              {
//STRIP001                  StartAllAction();
//STRIP001                  pFmt->GetDoc()->SetAttr( aAnch, *pFmt );
//STRIP001                  if( nAnchorId == FLY_AUTO_CNTNT && bFlyFrame &&
//STRIP001                      pFly->IsFlyAtCntFrm() )
//STRIP001                      ((SwFlyAtCntFrm*)pFly)->CheckCharRect();
//STRIP001                  EndAllAction();
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          SwRect aTmpRect( aRet, rAbsPos );
//STRIP001          if( aTmpRect.HasArea() )
//STRIP001              MakeVisible( aTmpRect );
//STRIP001 #ifndef PRODUCT
//STRIP001          //TODO: That doesn't seem to be intended
//STRIP001          if( Color(COL_TRANSPARENT) != GetOut()->GetLineColor() )
//STRIP001          {
//STRIP001              ASSERT( FALSE, "Hey, Joe: Where's my Null Pen?" );
//STRIP001              GetOut()->SetLineColor( Color(COL_TRANSPARENT) );
//STRIP001          }
//STRIP001 /*           if( PEN_NULL != GetOut()->GetPen().GetStyle() )
//STRIP001          {
//STRIP001              ASSERT( FALSE, "Hey, Joe: Where's my Null Pen?" );
//STRIP001              Pen aPen( PEN_NULL );
//STRIP001              GetOut()->SetPen( aPen );
//STRIP001          }
//STRIP001 */#endif
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return aRet;
//STRIP001 }

/***********************************************************************
#*  Class       :  SwFEShell
#*  Methode     :  NewFlyFrm
#*  Beschreibung:
#*  Datum       :  MA 03. Nov. 92
#*  Update      :  JP 11. Aug. 93
#***********************************************************************/

//STRIP001 const SwFrmFmt *SwFEShell::NewFlyFrm( const SfxItemSet& rSet, sal_Bool bAnchValid,
//STRIP001                         SwFrmFmt *pParent )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001
//STRIP001  SwPaM* pCrsr = GetCrsr();
//STRIP001  const SwPosition& rPos = *pCrsr->Start();
//STRIP001  const Point aPt( GetCrsrDocPos() );
//STRIP001
//STRIP001  SwSelBoxes aBoxes;
//STRIP001  sal_Bool bMoveCntnt = sal_True;
//STRIP001  if( IsTableMode() )
//STRIP001  {
//STRIP001      GetTblSel( *this, aBoxes );
//STRIP001      if( aBoxes.Count() )
//STRIP001      {
//STRIP001          // die Crsr muessen noch aus dem Loeschbereich entfernt
//STRIP001          // werden. Setze sie immer hinter/auf die Tabelle; ueber die
//STRIP001          // Dokument-Position werden sie dann immer an die alte
//STRIP001          // Position gesetzt.
//STRIP001          ParkCrsr( SwNodeIndex( *aBoxes[0]->GetSttNd() ));
//STRIP001 //           KillPams();
//STRIP001      }
//STRIP001      else
//STRIP001          bMoveCntnt = sal_False;
//STRIP001  }
//STRIP001  else if( !pCrsr->HasMark() && pCrsr->GetNext() == pCrsr )
//STRIP001      bMoveCntnt = sal_False;
//STRIP001
//STRIP001  SwFmtAnchor& rAnch = (SwFmtAnchor&)rSet.Get( RES_ANCHOR );
//STRIP001  RndStdIds eRndId = rAnch.GetAnchorId();
//STRIP001  switch( eRndId )
//STRIP001  {
//STRIP001  case FLY_PAGE:
//STRIP001      if( !rAnch.GetPageNum() )       //HotFix: Bug in UpdateByExample
//STRIP001          rAnch.SetPageNum( 1 );
//STRIP001      break;
//STRIP001
//STRIP001  case FLY_AT_FLY:
//STRIP001  case FLY_AT_CNTNT:
//STRIP001  case FLY_AUTO_CNTNT:
//STRIP001  case FLY_IN_CNTNT:
//STRIP001      if( !bAnchValid )
//STRIP001      {
//STRIP001          if( FLY_AT_FLY != eRndId )
//STRIP001              rAnch.SetAnchor( &rPos );
//STRIP001          else if( lcl_SetNewFlyPos( rPos.nNode.GetNode(), rAnch, aPt ) )
//STRIP001              eRndId = FLY_PAGE;
//STRIP001      }
//STRIP001      break;
//STRIP001
//STRIP001 #ifndef PRODUCT
//STRIP001  default:
//STRIP001          ASSERT( !this, "Was sollte das fuer ein Fly werden?" );
//STRIP001 #endif
//STRIP001  }
//STRIP001
//STRIP001  SwFlyFrmFmt *pRet;
//STRIP001  if( bMoveCntnt )
//STRIP001  {
//STRIP001      GetDoc()->StartUndo( UNDO_INSLAYFMT );
//STRIP001      SwFmtAnchor* pOldAnchor = 0;
//STRIP001      sal_Bool bHOriChgd = sal_False, bVOriChgd = sal_False;
//STRIP001      SwFmtVertOrient aOldV;
//STRIP001      SwFmtHoriOrient aOldH;
//STRIP001
//STRIP001      if( FLY_PAGE != eRndId )
//STRIP001      {
//STRIP001          // erstmal als mit Seitenbindung, Absatz/Zeichenbindung erst wenn
//STRIP001          // alles verschoben ist. Dann ist die Position gueltig!
//STRIP001          // JP 13.05.98: ggfs. auch noch die Hori/Vert-Orientierung
//STRIP001          //              umsetzen, damit diese beim Umanker NICHT
//STRIP001          //              korrigiert wird
//STRIP001          pOldAnchor = new SwFmtAnchor( rAnch );
//STRIP001          ((SfxItemSet&)rSet).Put( SwFmtAnchor( FLY_PAGE, 1 ) );
//STRIP001
//STRIP001          const SfxPoolItem* pItem;
//STRIP001          if( SFX_ITEM_SET == rSet.GetItemState( RES_HORI_ORIENT, sal_False, &pItem )
//STRIP001              && HORI_NONE == ((SwFmtHoriOrient*)pItem)->GetHoriOrient() )
//STRIP001          {
//STRIP001              bHOriChgd = sal_True;
//STRIP001              aOldH = *((SwFmtHoriOrient*)pItem);
//STRIP001              ((SfxItemSet&)rSet).Put( SwFmtHoriOrient( 0, HORI_LEFT ) );
//STRIP001          }
//STRIP001          if( SFX_ITEM_SET == rSet.GetItemState( RES_VERT_ORIENT, sal_False, &pItem )
//STRIP001              && VERT_NONE == ((SwFmtVertOrient*)pItem)->GetVertOrient() )
//STRIP001          {
//STRIP001              bVOriChgd = sal_True;
//STRIP001              aOldV = *((SwFmtVertOrient*)pItem);
//STRIP001              ((SfxItemSet&)rSet).Put( SwFmtVertOrient( 0, VERT_TOP ) );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      pRet = GetDoc()->MakeFlyAndMove( *pCrsr, rSet, &aBoxes, pParent );
//STRIP001
//STRIP001      KillPams();
//STRIP001
//STRIP001      if( pOldAnchor )
//STRIP001      {
//STRIP001          if( pRet )
//STRIP001          {
//STRIP001              // neue Position bestimmen
//STRIP001              //JP 24.03.97: immer ueber die Seitenbindung gehen - der
//STRIP001              //           chaos::Anchor darf nie im verschobenen Bereich
//STRIP001              //              liegen
//STRIP001              pRet->DelFrms();
//STRIP001
//STRIP001              const SwFrm* pAnch = ::FindAnchor( GetLayout(), aPt, sal_False );
//STRIP001              SwPosition aPos( *((SwCntntFrm*)pAnch)->GetNode() );
//STRIP001              if( FLY_IN_CNTNT == eRndId )
//STRIP001                  aPos.nContent.Assign( ((SwCntntFrm*)pAnch)->GetNode(), 0 );
//STRIP001              pOldAnchor->SetAnchor( &aPos );
//STRIP001
//STRIP001              // das verschieben von TabelleSelektion ist noch nicht
//STRIP001              // Undofaehig - also darf das UmAnkern auch nicht
//STRIP001              // aufgezeichnet werden.
//STRIP001              sal_Bool bDoesUndo = GetDoc()->DoesUndo();
//STRIP001              if( bDoesUndo && UNDO_INSLAYFMT == GetDoc()->GetUndoIds() )
//STRIP001                  GetDoc()->DoUndo( sal_False );
//STRIP001
//STRIP001              ((SfxItemSet&)rSet).Put( *pOldAnchor );
//STRIP001
//STRIP001              if( bHOriChgd )
//STRIP001                  ((SfxItemSet&)rSet).Put( aOldH );
//STRIP001              if( bVOriChgd )
//STRIP001                  ((SfxItemSet&)rSet).Put( aOldV );
//STRIP001
//STRIP001              GetDoc()->SetFlyFrmAttr( *pRet, (SfxItemSet&)rSet );
//STRIP001              GetDoc()->DoUndo( bDoesUndo );
//STRIP001          }
//STRIP001          delete pOldAnchor;
//STRIP001      }
//STRIP001      GetDoc()->EndUndo( UNDO_INSLAYFMT );
//STRIP001  }
//STRIP001  else
//STRIP001         /* #109161# If called from a shell try to propagate an
//STRIP001             existing adjust item from rPos to the content node of the
//STRIP001             new frame. */
//STRIP001      pRet = GetDoc()->MakeFlySection( eRndId, &rPos, &rSet, pParent, TRUE );
//STRIP001
//STRIP001  if( pRet )
//STRIP001  {
//STRIP001      SwFlyFrm* pFrm = pRet->GetFrm( &aPt );
//STRIP001      if( pFrm )
//STRIP001          SelectFlyFrm( *pFrm, sal_True );
//STRIP001      else
//STRIP001      {
//STRIP001          GetLayout()->SetAssertFlyPages();
//STRIP001          pRet = 0;
//STRIP001      }
//STRIP001  }
//STRIP001  EndAllActionAndCall();
//STRIP001
//STRIP001  return pRet;
//STRIP001 }

/***********************************************************************
#*  Class       :  SwFEShell
#*  Methode     :  Insert
#*  Datum       :  ??
#*  Update      :  MA 12. Sep. 94
#***********************************************************************/

//STRIP001 void SwFEShell::Insert( const String& rGrfName, const String& rFltName,
//STRIP001                      const Graphic* pGraphic,
//STRIP001                      const SfxItemSet* pFlyAttrSet,
//STRIP001                      const SfxItemSet* pGrfAttrSet,
//STRIP001                      SwFrmFmt* pFrmFmt )
//STRIP001 {
//STRIP001  SwFlyFrmFmt* pFmt = 0;
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001  FOREACHCURSOR_START( this )
//STRIP001
//STRIP001      // Anker noch nicht oder unvollstaendig gesetzt ?
//STRIP001      if( pFlyAttrSet )
//STRIP001      {
//STRIP001          const SfxPoolItem* pItem;
//STRIP001          if( SFX_ITEM_SET == pFlyAttrSet->GetItemState( RES_ANCHOR, sal_False,
//STRIP001                  &pItem ) )
//STRIP001          {
//STRIP001              SwFmtAnchor* pAnchor = (SwFmtAnchor*)pItem;
//STRIP001              switch( pAnchor->GetAnchorId())
//STRIP001              {
//STRIP001              case FLY_AT_CNTNT:
//STRIP001              case FLY_AUTO_CNTNT: // LAYER_IMPL
//STRIP001              case FLY_IN_CNTNT:
//STRIP001                  if( !pAnchor->GetCntntAnchor() )
//STRIP001                      pAnchor->SetAnchor( PCURCRSR->GetPoint() );
//STRIP001                  break;
//STRIP001              case FLY_AT_FLY:
//STRIP001                  if( !pAnchor->GetCntntAnchor() )
//STRIP001                      lcl_SetNewFlyPos( *PCURCRSR->GetNode(),
//STRIP001                                          *pAnchor, GetCrsrDocPos() );
//STRIP001                  break;
//STRIP001              case FLY_PAGE:
//STRIP001                  if( !pAnchor->GetPageNum() )
//STRIP001                  {
//STRIP001                      pAnchor->SetPageNum( PCURCRSR->GetPageNum(
//STRIP001                                  sal_True, &PCURCRSR->GetPtPos() ) );
//STRIP001                  }
//STRIP001                  break;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      pFmt = GetDoc()->Insert(*PCURCRSR, rGrfName,
//STRIP001                              rFltName, pGraphic,
//STRIP001                              pFlyAttrSet,
//STRIP001                              pGrfAttrSet, pFrmFmt );
//STRIP001      ASSERT( pFmt, "Doc->Insert(notxt) failed." );
//STRIP001
//STRIP001  FOREACHCURSOR_END()
//STRIP001  EndAllAction();
//STRIP001
//STRIP001  if( pFmt )
//STRIP001  {
//STRIP001      const Point aPt( GetCrsrDocPos() );
//STRIP001      SwFlyFrm* pFrm = pFmt->GetFrm( &aPt );
//STRIP001
//STRIP001      if( pFrm )
//STRIP001          SelectFlyFrm( *pFrm, sal_True );
//STRIP001      else
//STRIP001          GetLayout()->SetAssertFlyPages();
//STRIP001  }
//STRIP001 }

//STRIP001 void SwFEShell::Insert( SvInPlaceObject *pObj,
//STRIP001                      const SfxItemSet* pFlyAttrSet,
//STRIP001                      const SfxItemSet* pGrfAttrSet,
//STRIP001                      SwFrmFmt* pFrmFmt )
//STRIP001 {
//STRIP001  SwFlyFrmFmt* pFmt = 0;
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  StartAllAction();
//STRIP001      FOREACHPAM_START( this )
//STRIP001          pFmt = GetDoc()->Insert(*PCURCRSR, pObj,
//STRIP001                                  pFlyAttrSet, pGrfAttrSet, pFrmFmt );
//STRIP001          ASSERT( pFmt, "Doc->Insert(notxt) failed." );
//STRIP001
//STRIP001      FOREACHPAM_END()
//STRIP001  EndAllAction();
//STRIP001
//STRIP001  if( pFmt )
//STRIP001  {
//STRIP001      const Point aPt( GetCrsrDocPos() );
//STRIP001      SwFlyFrm* pFrm = pFmt->GetFrm( &aPt );
//STRIP001
//STRIP001      if( pFrm )
//STRIP001          SelectFlyFrm( *pFrm, sal_True );
//STRIP001      else
//STRIP001          GetLayout()->SetAssertFlyPages();
//STRIP001  }
//STRIP001 }


//STRIP001 void SwFEShell::Insert(  SdrObject& rDrawObj,
//STRIP001                       const SfxItemSet* pFlyAttrSet,
//STRIP001                       SwFrmFmt* pFrmFmt, const Point* pPt )
//STRIP001 {
//STRIP001  SwDrawFrmFmt* pFmt = 0;
//STRIP001  SET_CURR_SHELL( this );
//STRIP001
//STRIP001  if( pPt )
//STRIP001  {
//STRIP001      SfxItemSet* pSet = 0;
//STRIP001      const SfxPoolItem* pItem;
//STRIP001      if( !pFlyAttrSet ||
//STRIP001          !pFlyAttrSet->GetItemState( RES_ANCHOR, sal_False, &pItem ) ||
//STRIP001          FLY_PAGE != ((SwFmtAnchor*)pItem)->GetAnchorId() )
//STRIP001      {
//STRIP001          pSet = new SfxItemSet( GetDoc()->GetAttrPool(), aFrmFmtSetRange );
//STRIP001          pSet->Put( SwFmtAnchor( FLY_AT_CNTNT ));
//STRIP001          pFlyAttrSet = pSet;
//STRIP001      }
//STRIP001
//STRIP001      SwCrsrMoveState aState( MV_SETONLYTEXT );
//STRIP001      SwPaM aPam( pDoc->GetNodes() );
//STRIP001      Point aTmpPt( *pPt );
//STRIP001      GetDoc()->GetRootFrm()->GetCrsrOfst( aPam.GetPoint(), aTmpPt, &aState );
//STRIP001      SwFrm* pFrm = aPam.GetCntntNode()->GetFrm( 0, 0, sal_False );
//STRIP001      const Point aRelPos( pPt->X() - pFrm->Frm().Left(),
//STRIP001                           pPt->Y() - pFrm->Frm().Top() );
//STRIP001      rDrawObj.SetRelativePos( aRelPos );
//STRIP001      ::lcl_FindAnchorPos( *GetDoc(), *pPt, *pFrm, *(SfxItemSet*)pFlyAttrSet );
//STRIP001      pFmt = GetDoc()->Insert( aPam, rDrawObj, pFlyAttrSet, pFrmFmt );
//STRIP001      if( pSet )
//STRIP001          delete pSet;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      StartAllAction();
//STRIP001          FOREACHPAM_START( this )
//STRIP001              pFmt = GetDoc()->Insert(*PCURCRSR, rDrawObj,
//STRIP001                                      pFlyAttrSet, pFrmFmt );
//STRIP001              ASSERT( pFmt, "Doc->Insert(sdrobj) failed." );
//STRIP001
//STRIP001          FOREACHPAM_END()
//STRIP001      EndAllAction();
//STRIP001  }
//STRIP001
//STRIP001  if( pFmt )
//STRIP001      // das DrawObject selektieren
//STRIP001      Imp()->GetDrawView()->MarkObj( &rDrawObj, Imp()->GetPageView(),
//STRIP001                                          sal_False, sal_False );
//STRIP001  else
//STRIP001      GetLayout()->SetAssertFlyPages();
//STRIP001 }

/***********************************************************************
#*  Class       :  SwFEShell
#*  Methode     :  GetPageObjs
#*  Datum       :  ??
#*  Update      :  MA 11. Jan. 95
#***********************************************************************/

//STRIP001 void SwFEShell::GetPageObjs( SvPtrarr& rFillArr )
//STRIP001 {
//STRIP001  if( rFillArr.Count() )
//STRIP001      rFillArr.Remove( 0, rFillArr.Count() );
//STRIP001
//STRIP001  const SwFrmFmt* pFmt;
//STRIP001  for( sal_uInt16 n = 0; n < pDoc->GetSpzFrmFmts()->Count(); ++n )
//STRIP001  {
//STRIP001      pFmt = (const SwFrmFmt*)(*pDoc->GetSpzFrmFmts())[n];
//STRIP001      if( FLY_PAGE == pFmt->GetAnchor().GetAnchorId() )
//STRIP001          rFillArr.Insert( (VoidPtr)pFmt, rFillArr.Count() );
//STRIP001  }
//STRIP001 }

/***********************************************************************
#*  Class       :  SwFEShell
#*  Methode     :  SetPageFlysNewPage
#*  Datum       :  ??
#*  Update      :  MA 14. Feb. 95
#***********************************************************************/

//STRIP001 void SwFEShell::SetPageObjsNewPage( SvPtrarr& rFillArr, int nOffset )
//STRIP001 {
//STRIP001  if( !rFillArr.Count() || !nOffset )
//STRIP001      return;
//STRIP001
//STRIP001  StartAllAction();
//STRIP001  StartUndo();
//STRIP001
//STRIP001  SwFrmFmt* pFmt;
//STRIP001  long nNewPage;
//STRIP001  sal_uInt16 nMaxPage = GetDoc()->GetRootFrm()->GetPageNum();
//STRIP001  sal_Bool bAssert = sal_False;
//STRIP001  for( sal_uInt16 n = 0; n < rFillArr.Count(); ++n )
//STRIP001  {
//STRIP001      pFmt = (SwFrmFmt*)rFillArr[n];
//STRIP001      if( USHRT_MAX != pDoc->GetSpzFrmFmts()->GetPos( pFmt ))
//STRIP001      {
//STRIP001          // FlyFmt ist noch gueltig, also behandeln
//STRIP001          SwFmtAnchor aNewAnchor( pFmt->GetAnchor() );
//STRIP001          if( FLY_PAGE != aNewAnchor.GetAnchorId() ||
//STRIP001              0 >= ( nNewPage = aNewAnchor.GetPageNum() + nOffset ) )
//STRIP001              // chaos::Anchor wurde veraendert oder ungueltige SeitenNummer,
//STRIP001              // also nicht veraendern !!
//STRIP001              continue;
//STRIP001
//STRIP001          if( sal_uInt16(nNewPage) > nMaxPage )
//STRIP001          {
//STRIP001              if ( RES_DRAWFRMFMT == pFmt->Which() )
//STRIP001              {
//STRIP001                  SwContact *pCon = pFmt->FindContactObj();
//STRIP001                  if( pCon )
//STRIP001                      ((SwDrawContact*)pCon)->DisconnectFromLayout();
//STRIP001              }
//STRIP001              else
//STRIP001                  pFmt->DelFrms();
//STRIP001              bAssert = sal_True;
//STRIP001          }
//STRIP001          aNewAnchor.SetPageNum( sal_uInt16(nNewPage) );
//STRIP001          pDoc->SetAttr( aNewAnchor, *pFmt );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( bAssert )
//STRIP001      GetDoc()->GetRootFrm()->SetAssertFlyPages();
//STRIP001
//STRIP001  EndUndo();
//STRIP001  EndAllAction();
//STRIP001 }

/***********************************************************************
#*  Class       :  SwFEShell
#*  Methode     :  GetFlyFrmAttr
#*  Beschreibung:  Alle Attribute in dem 'Koerbchen' werden mit den
#*                 Attributen des aktuellen FlyFrms gefuellt.
#*                 Sind Attribute nicht zu fuellen weil fehl am Platz oder
#*                 uneindeutig (Mehrfachtselektionen) so werden sie entfernt.
#*  Datum       :  MA 03. Nov. 92
#*  Update      :  MA 03. Feb. 94
#***********************************************************************/

//STRIP001 sal_Bool SwFEShell::GetFlyFrmAttr( SfxItemSet &rSet ) const
//STRIP001 {
//STRIP001  SwFlyFrm *pFly = FindFlyFrm();
//STRIP001  if ( !pFly )
//STRIP001  {
//STRIP001      ASSERT( GetCurrFrm(), "Crsr in parking zone" );
//STRIP001      pFly = GetCurrFrm()->FindFlyFrm();
//STRIP001      if ( !pFly )
//STRIP001      {
//STRIP001          ASSERT( !this, "GetFlyFrmAttr, no Fly selected." );
//STRIP001          return sal_False;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  SET_CURR_SHELL( (ViewShell*)this );
//STRIP001
//STRIP001  if( !rSet.Set( pFly->GetFmt()->GetAttrSet(), sal_True ) )
//STRIP001      return sal_False;
//STRIP001
//STRIP001  //Und die Attribute durchschaufeln. Unerlaubte Attribute entfernen, dann
//STRIP001  //alle restlichen Attribute besorgen und eintragen.
//STRIP001  const SfxPoolItem* pItem;
//STRIP001  if( SFX_ITEM_SET == rSet.GetItemState( RES_ANCHOR, sal_False, &pItem ) )
//STRIP001  {
//STRIP001      SwFmtAnchor* pAnchor = (SwFmtAnchor*)pItem;
//STRIP001      RndStdIds eType = pAnchor->GetAnchorId();
//STRIP001
//STRIP001      if( FLY_PAGE != eType )
//STRIP001      {
//STRIP001          rSet.Put( SwFmtAnchor( eType ));
//STRIP001          if( FLY_IN_CNTNT == eType )
//STRIP001          {
//STRIP001              rSet.ClearItem( RES_OPAQUE );
//STRIP001              rSet.ClearItem( RES_SURROUND );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  rSet.SetParent( pFly->GetFmt()->GetAttrSet().GetParent() );
//STRIP001  //JP 11.02.97: Bug #35894#: die Attribute MUESSEN entfern werden!
//STRIP001  rSet.ClearItem( RES_FILL_ORDER );
//STRIP001  rSet.ClearItem( RES_CNTNT );
//STRIP001  //MA: Ersteinmal entfernen (Template by example usw.)
//STRIP001  rSet.ClearItem( RES_CHAIN );
//STRIP001  return sal_True;
//STRIP001 }
/***********************************************************************
#*  Class       :  SwFEShell
#*  Methode     :  SetFlyFrmAttr
#*  Beschreibung:  Die Attribute des aktuellen Flys aendern sich.
#*  Datum       :  MA 03. Nov. 92
#*  Update      :  MA 01. Aug. 95
#***********************************************************************/

//STRIP001 sal_Bool SwFEShell::SetFlyFrmAttr( SfxItemSet& rSet )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001  sal_Bool bRet = sal_False;
//STRIP001
//STRIP001  if( rSet.Count() )
//STRIP001  {
//STRIP001      SwFlyFrm *pFly = FindFlyFrm();
//STRIP001      if( !pFly )
//STRIP001      {
//STRIP001          ASSERT( GetCurrFrm(), "Crsr in parking zone" );
//STRIP001          pFly = GetCurrFrm()->FindFlyFrm();
//STRIP001          ASSERT( pFly, "SetFlyFrmAttr, no Fly selected." );
//STRIP001      }
//STRIP001      if( pFly )
//STRIP001      {
//STRIP001          StartAllAction();
//STRIP001          const Point aPt( pFly->Frm().Pos() );
//STRIP001
//STRIP001          if( SFX_ITEM_SET == rSet.GetItemState( RES_ANCHOR, sal_False ))
//STRIP001              ::lcl_ChkAndSetNewAnchor( *pFly, rSet );
//STRIP001          SwFlyFrmFmt* pFlyFmt = (SwFlyFrmFmt*)pFly->GetFmt();
//STRIP001
//STRIP001          if( GetDoc()->SetFlyFrmAttr( *pFlyFmt, rSet ))
//STRIP001          {
//STRIP001              bRet = sal_True;
//STRIP001              SwFlyFrm* pFrm = pFlyFmt->GetFrm( &aPt );
//STRIP001              if( pFrm )
//STRIP001                  SelectFlyFrm( *pFrm, sal_True );
//STRIP001              else
//STRIP001                  GetLayout()->SetAssertFlyPages();
//STRIP001          }
//STRIP001
//STRIP001          EndAllActionAndCall();
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/***********************************************************************
#*  Class       :  SwFEShell
#*  Methode     :  ResetFlyFrmAttr
#*  Beschreibung:  Das gewuenschte Attribut oder die im Set befindlichen
#*                  werden zurueckgesetzt.
#*  Datum       :  MA 14. Mar. 97
#*  Update      :  MA 14. Mar. 97
#***********************************************************************/

//STRIP001 sal_Bool SwFEShell::ResetFlyFrmAttr( sal_uInt16 nWhich, const SfxItemSet* pSet )
//STRIP001 {
//STRIP001  sal_Bool bRet = sal_False;
//STRIP001
//STRIP001  if( RES_ANCHOR != nWhich && RES_CHAIN != nWhich && RES_CNTNT != nWhich )
//STRIP001  {
//STRIP001      SET_CURR_SHELL( this );
//STRIP001
//STRIP001      SwFlyFrm *pFly = FindFlyFrm();
//STRIP001      if( !pFly )
//STRIP001      {
//STRIP001          ASSERT( GetCurrFrm(), "Crsr in parking zone" );
//STRIP001          pFly = GetCurrFrm()->FindFlyFrm();
//STRIP001          ASSERT( pFly, "SetFlyFrmAttr, no Fly selected." );
//STRIP001      }
//STRIP001
//STRIP001      if( pFly )
//STRIP001      {
//STRIP001          StartAllAction();
//STRIP001
//STRIP001          if( pSet )
//STRIP001          {
//STRIP001              SfxItemIter aIter( *pSet );
//STRIP001              const SfxPoolItem* pItem = aIter.FirstItem();
//STRIP001              while( pItem )
//STRIP001              {
//STRIP001                  if( !IsInvalidItem( pItem ) &&
//STRIP001                      RES_ANCHOR != ( nWhich = pItem->Which() ) &&
//STRIP001                      RES_CHAIN != nWhich && RES_CNTNT != nWhich )
//STRIP001                      pFly->GetFmt()->ResetAttr( nWhich );
//STRIP001                  pItem = aIter.NextItem();
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001              pFly->GetFmt()->ResetAttr( nWhich );
//STRIP001
//STRIP001          bRet = sal_True;
//STRIP001          EndAllActionAndCall();
//STRIP001          GetDoc()->SetModified();
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/***********************************************************************
#*  Class       :  SwFEShell
#*  Methode     :  GetCurFrmFmt
#*  Beschreibung:  liefert wenn Rahmen, dann Rahmenvorlage, sonst 0
#*  Datum       :  ST 04. Jun. 93
#*  Update      :
#***********************************************************************/

/*N*/ SwFrmFmt* SwFEShell::GetCurFrmFmt() const
/*N*/ {
/*N*/   SwFrmFmt* pRet = 0;
/*N*/   SwLayoutFrm *pFly = FindFlyFrm();
/*N*/   if( pFly && ( pRet = (SwFrmFmt*)pFly->GetFmt()->DerivedFrom() ) ==
/*N*/                                           GetDoc()->GetDfltFrmFmt() )
/*?*/       pRet = 0;
/*N*/   return pRet;
/*N*/ }

/******************************************************************************
 *  Methode     :   void SwFEShell::SetFrmFmt(SwFrmFmt *pNewFmt)
 *  Beschreibung:
 *  Erstellt    :   OK 14.04.94 15:40
 *  Aenderung   :   MA 23. Apr. 97
 ******************************************************************************/

//STRIP001 void SwFEShell::SetFrmFmt( SwFrmFmt *pNewFmt, sal_Bool bKeepOrient, Point* pDocPos )
//STRIP001 {
//STRIP001  SwFlyFrm *pFly = 0;
//STRIP001  if(pDocPos)
//STRIP001  {
//STRIP001      const SwFrmFmt* pFmt = GetFmtFromObj( *pDocPos );
//STRIP001
//STRIP001      if(PTR_CAST(SwFlyFrmFmt, pFmt))
//STRIP001          pFly = ((SwFlyFrmFmt*)pFmt)->GetFrm();
//STRIP001  }
//STRIP001  else
//STRIP001      pFly = FindFlyFrm();
//STRIP001  ASSERT( pFly, "SetFrmFmt: kein Frame" );
//STRIP001  if( pFly )
//STRIP001  {
//STRIP001      StartAllAction();
//STRIP001      SET_CURR_SHELL( this );
//STRIP001
//STRIP001      SwFlyFrmFmt* pFlyFmt = (SwFlyFrmFmt*)pFly->GetFmt();
//STRIP001      const Point aPt( pFly->Frm().Pos() );
//STRIP001
//STRIP001      SfxItemSet* pSet = 0;
//STRIP001      const SfxPoolItem* pItem;
//STRIP001      if( SFX_ITEM_SET == pNewFmt->GetItemState( RES_ANCHOR, sal_False, &pItem ))
//STRIP001      {
//STRIP001          pSet = new SfxItemSet( GetDoc()->GetAttrPool(), aFrmFmtSetRange );
//STRIP001          pSet->Put( *pItem );
//STRIP001          if( !::lcl_ChkAndSetNewAnchor( *pFly, *pSet ))
//STRIP001              delete pSet, pSet = 0;
//STRIP001      }
//STRIP001
//STRIP001      if( GetDoc()->SetFrmFmtToFly( *pFlyFmt, *pNewFmt, pSet, bKeepOrient ))
//STRIP001      {
//STRIP001          SwFlyFrm* pFrm = pFlyFmt->GetFrm( &aPt );
//STRIP001          if( pFrm )
//STRIP001              SelectFlyFrm( *pFrm, sal_True );
//STRIP001          else
//STRIP001              GetLayout()->SetAssertFlyPages();
//STRIP001      }
//STRIP001      if( pSet )
//STRIP001          delete pSet;
//STRIP001
//STRIP001      EndAllActionAndCall();
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::GetFlyFrmFmt()
|*
|*  Ersterstellung      OK 23.06.93 13:15
|*  Letzte Aenderung    OK 23.06.93 13:15
|*
*************************************************************************/

/*N*/ const SwFrmFmt* SwFEShell::GetFlyFrmFmt() const
/*N*/ {
/*N*/   const SwFlyFrm* pFly = FindFlyFrm();
/*N*/   if ( !pFly )
/*N*/       pFly = GetCurrFrm()->FindFlyFrm();
/*N*/   if( pFly )
/*N*/       return pFly->GetFmt();
/*N*/   return 0;
/*N*/ }

/*M*/ SwFrmFmt* SwFEShell::GetFlyFrmFmt()
/*M*/ {
/*M*/   SwFlyFrm* pFly = FindFlyFrm();
/*M*/   if ( !pFly )
/*M*/       pFly = GetCurrFrm()->FindFlyFrm();
/*M*/   if( pFly )
/*M*/       return pFly->GetFmt();
/*M*/   return 0;
/*M*/ }

/*************************************************************************
|*
|*  SwFEShell::GetFlyRect()
|*
|*  Ersterstellung      AMA 6. Mae. 97
|*  Letzte Aenderung    AMA 6. Mae. 97
|*
*************************************************************************/

//STRIP001 SwRect SwFEShell::GetFlyRect() const
//STRIP001 {
//STRIP001  SwCntntFrm *pCntnt = GetCurrFrm( sal_False );
//STRIP001  SwFlyFrm *pFly = pCntnt->FindFlyFrm();
//STRIP001  if ( !pFly )
//STRIP001  {
//STRIP001      SwRect aRect;
//STRIP001      return aRect;
//STRIP001  }
//STRIP001  else
//STRIP001      return pFly->Frm();
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::GetObjRect()
|*
|*  Ersterstellung      MA 22. Aug. 93
|*  Letzte Aenderung    MA 11. Jan. 95
|*
*************************************************************************/

//STRIP001 SwRect SwFEShell::GetObjRect() const
//STRIP001 {
//STRIP001 /*   const SdrMarkList &rMrkList = Imp()->GetDrawView()->GetMarkList();
//STRIP001      Rectangle aRect;
//STRIP001  for ( sal_uInt16 i = 0; i < rMrkList.GetMarkCount(); ++i )
//STRIP001      aRect.Union( rMrkList.GetMark( i )->GetObj()->GetBoundRect() );
//STRIP001  return SwRect( aRect );*/
//STRIP001  if( Imp()->HasDrawView() )
//STRIP001      return Imp()->GetDrawView()->GetAllMarkedRect();
//STRIP001  else
//STRIP001  {
//STRIP001      SwRect aRect;
//STRIP001      return aRect;
//STRIP001  }
//STRIP001 }

//STRIP001 void SwFEShell::SetObjRect( const SwRect& rRect )
//STRIP001 {
//STRIP001  if ( Imp()->HasDrawView() )
//STRIP001  {
//STRIP001      Imp()->GetDrawView()->SetAllMarkedRect( rRect.SVRect() );
//STRIP001      CallChgLnk();   // rufe das AttrChangeNotify auf der UI-Seite.
//STRIP001  }
//STRIP001 }

/***********************************************************************
#*  Class       :  SwFEShell
#*  Methode     :  RequestObjectResize()
#*  Datum       :  MA 10. Feb. 95
#*  Update      :  MA 13. Jul. 95
#***********************************************************************/

/*N*/ void SwFEShell::RequestObjectResize( const SwRect &rRect, SvEmbeddedObject *pIPObj )
/*N*/ {
/*N*/   SwFlyFrm *pFly = FindFlyFrm( pIPObj );
/*N*/   if ( !pFly )
/*?*/       return;
/*N*/
/*N*/   StartAllAction();
/*N*/
/*N*/   //MA wir lassen den Fly nicht Clippen, damit die Ole-Server mit
/*N*/   //beliebigen Wuenschen kommen koennen. Die Formatierung uebernimmt das
/*N*/   //Clippen. Die richtige Darstellung wird per Scalierung erledigt.
/*N*/   //Die Scalierung wird von SwNoTxtFrm::Format durch einen Aufruf von
/*N*/   //SwWrtShell::CalcAndSetScale() erledigt.
/*N*/
/*N*/   if ( rRect.SSize() != pFly->Prt().SSize() )
/*N*/   {
/*N*/       Size aSz( rRect.SSize() );
/*N*/
/*N*/       //JP 28.02.2001: Task 74707 - ask for fly in fly with automatic size
/*N*/       //
/*N*/       const SwFrm* pAnchor;
/*N*/       const SwTxtNode* pTNd;
/*N*/       const SwpHints* pHts;
/*N*/       const SwFmtFrmSize& rFrmSz = pFly->GetFmt()->GetFrmSize();
/*N*/       if( bCheckForOLEInCaption &&
/*N*/           0 != rFrmSz.GetWidthPercent() &&
/*N*/           0 != (pAnchor = pFly->GetAnchor()) &&
/*N*/           pAnchor->IsTxtFrm() &&
/*N*/           !pAnchor->GetNext() && !pAnchor->GetPrev() &&
/*N*/           pAnchor->GetUpper()->IsFlyFrm() &&
/*?*/           0 != ( pTNd = ((SwTxtFrm*)pAnchor)->GetNode()->GetTxtNode()) &&
/*N*/           0 != ( pHts = pTNd->GetpSwpHints() ))
/*N*/       {
/*?*/           // search for a sequence field:
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 const SfxPoolItem* pItem;
//STRIP001 /*?*/            for( USHORT n = 0, nEnd = pHts->Count(); n < nEnd; ++n )
//STRIP001 /*?*/                if( RES_TXTATR_FIELD == ( pItem =
//STRIP001 /*?*/                            &(*pHts)[ n ]->GetAttr())->Which() &&
//STRIP001 /*?*/                    TYP_SEQFLD == ((SwFmtFld*)pItem)->GetFld()->GetTypeId() )
//STRIP001 /*?*/                {
//STRIP001 /*?*/                    // sequence field found
//STRIP001 /*?*/                    SwFlyFrm* pChgFly = (SwFlyFrm*)pAnchor->GetUpper();
//STRIP001 /*?*/                    // calculate the changed size:
//STRIP001 /*?*/                    // width must change, height can change
//STRIP001 /*?*/                    Size aNewSz( aSz.Width() + pChgFly->Frm().Width() -
//STRIP001 /*?*/                                   pFly->Prt().Width(), aSz.Height() );
//STRIP001 /*?*/
//STRIP001 /*?*/                    SwFrmFmt *pFmt = pChgFly->GetFmt();
//STRIP001 /*?*/                    SwFmtFrmSize aFrmSz( pFmt->GetFrmSize() );
//STRIP001 /*?*/                    aFrmSz.SetWidth( aNewSz.Width() );
//STRIP001 /*?*/                    if( ATT_MIN_SIZE != aFrmSz.GetSizeType() )
//STRIP001 /*?*/                    {
//STRIP001 /*?*/                        aNewSz.Height() += pChgFly->Frm().Height() -
//STRIP001 /*?*/                                            pFly->Prt().Height();
//STRIP001 /*?*/                        if( Abs( aNewSz.Height() - pChgFly->Frm().Height()) > 1 )
//STRIP001 /*?*/                            aFrmSz.SetHeight( aNewSz.Height() );
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    // uebers Doc fuers Undo!
//STRIP001 /*?*/                    pFmt->GetDoc()->SetAttr( aFrmSz, *pFmt );
//STRIP001 /*?*/                    break;
//STRIP001 /*?*/                }
/*N*/       }
/*N*/
/*N*/       // set the new Size at the fly themself
/*N*/       if ( pFly->Prt().Height() > 0 && pFly->Prt().Width() > 0 )
/*N*/       {
/*N*/       aSz.Width() += pFly->Frm().Width() - pFly->Prt().Width();
/*N*/       aSz.Height()+= pFly->Frm().Height()- pFly->Prt().Height();
/*N*/       }
/*N*/       pFly->ChgSize( aSz );
/*N*/
/*N*/       //Wenn sich das Objekt aendert ist die Kontur hoechstwahrscheinlich daneben.
/*N*/       ASSERT( pFly->Lower()->IsNoTxtFrm(), "Request ohne NoTxt" );
/*N*/       SwNoTxtNode *pNd = ((SwCntntFrm*)pFly->Lower())->GetNode()->GetNoTxtNode();
/*N*/       ASSERT( pNd, "Request ohne Node" );
/*N*/       pNd->SetContour( 0 );
/*N*/       ClrContourCache();
/*N*/   }
/*N*/
/*N*/   //Wenn nur die Size angepasst werden soll, so wird eine Pos mit
/*N*/   //ausgezeichneten Werten transportiert.
/*N*/   Point aPt( pFly->Prt().Pos() );
/*N*/   aPt += pFly->Frm().Pos();
/*N*/   if ( rRect.Top() != LONG_MIN && rRect.Pos() != aPt )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 aPt = rRect.Pos();
//STRIP001 /*?*/        aPt.X() -= pFly->Prt().Left();
//STRIP001 /*?*/        aPt.Y() -= pFly->Prt().Top();
//STRIP001 /*?*/        //Bei Absatzgebundenen Flys muss ausgehend von der neuen Position ein
//STRIP001 /*?*/        //neuer Anker gesetzt werden. Anker und neue RelPos werden vom Fly
//STRIP001 /*?*/        //selbst berechnet und gesetzt.
//STRIP001 /*?*/        if( pFly->IsFlyAtCntFrm() )
//STRIP001 /*?*/            ((SwFlyAtCntFrm*)pFly)->SetAbsPos( aPt );
//STRIP001 /*?*/        else
//STRIP001 /*?*/        {
//STRIP001 /*?*/            const SwFrmFmt *pFmt = pFly->GetFmt();
//STRIP001 /*?*/            const SwFmtVertOrient &rVert = pFmt->GetVertOrient();
//STRIP001 /*?*/            const SwFmtHoriOrient &rHori = pFmt->GetHoriOrient();
//STRIP001 /*?*/            const long lXDiff = aPt.X() - pFly->Frm().Left();
//STRIP001 /*?*/            const long lYDiff = aPt.Y() - pFly->Frm().Top();
//STRIP001 /*?*/            const Point aTmp( rHori.GetPos() + lXDiff,
//STRIP001 /*?*/                              rVert.GetPos() + lYDiff );
//STRIP001 /*?*/            pFly->ChgRelPos( aTmp );
//STRIP001 /*?*/        }
/*N*/   }
/*N*/   EndAllAction();
/*N*/ }

/***********************************************************************
#*  Class       :  SwFEShell
#*  Methode     :  DeleteCurrFrmFmt
#*  Datum       :  JP 28.07.95
#*  Update      :  JP 28.07.95
#***********************************************************************/

//STRIP001 sal_Bool SwFEShell::WizzardDelFly()
//STRIP001 {
//STRIP001  // mal nicht uebers Layout den Fly suchen. Dann kann auch ohne gueltiges
//STRIP001  // Layout ein Rahmen geloescht werden. ( z.B.: fuer die Wizard's )
//STRIP001  SwFrmFmt* pDelFmt = WizzardGetFly();
//STRIP001  if( pDelFmt )
//STRIP001  {
//STRIP001      // gefunden: dann also loeschen
//STRIP001      // bei Zeichen/Absatz gebundenen Flys den Crsr auf den Anker umsetzen,
//STRIP001      // dadurch bleibt der Crsr auf einer "definierten" Position
//STRIP001      // (Im Wizzard wird das Layout nicht aktualisiert!)
//STRIP001      SwPosition* pCrsrPos = GetCrsr()->GetPoint(), *pNewPos = 0;
//STRIP001      const SwFmtAnchor& rAnch = pDelFmt->GetAnchor();
//STRIP001      if( rAnch.GetCntntAnchor() &&
//STRIP001          ( FLY_AT_CNTNT == rAnch.GetAnchorId() ||
//STRIP001            FLY_AUTO_CNTNT == rAnch.GetAnchorId() ||
//STRIP001              FLY_IN_CNTNT == rAnch.GetAnchorId() ))
//STRIP001      {
//STRIP001          pNewPos = new SwPosition( *rAnch.GetCntntAnchor() );
//STRIP001          if( FLY_IN_CNTNT != rAnch.GetAnchorId() )
//STRIP001              pNewPos->nContent.Assign( GetDoc()->GetNodes()[ pNewPos->nNode ]
//STRIP001                                                  ->GetCntntNode(), 0 );
//STRIP001      }
//STRIP001
//STRIP001      GetDoc()->DelLayoutFmt( pDelFmt );
//STRIP001
//STRIP001      if( pNewPos )
//STRIP001      {
//STRIP001          *pCrsrPos = *pNewPos;
//STRIP001          delete pNewPos;
//STRIP001      }
//STRIP001      return sal_True;
//STRIP001  }
//STRIP001  return sal_False;
//STRIP001 }

/***********************************************************************
#*  Class       :  SwFEShell
#*  Methode     :  WizzardFindCurFrmFmt
#*  Datum       :  JP 31.07.95
#*  Update      :  JP 31.07.95
#***********************************************************************/

//STRIP001 SwFrmFmt* SwFEShell::WizzardGetFly()
//STRIP001 {
//STRIP001  // mal nicht uebers Layout den Fly suchen. Dann kann auch ohne gueltiges
//STRIP001  // Layout ein Rahmen geloescht werden. ( z.B.: fuer die Wizard's )
//STRIP001  SwSpzFrmFmts& rSpzArr = *pDoc->GetSpzFrmFmts();
//STRIP001  sal_uInt16 nCnt = rSpzArr.Count();
//STRIP001  if( nCnt )
//STRIP001  {
//STRIP001      SwNodeIndex& rCrsrNd = GetCrsr()->GetPoint()->nNode;
//STRIP001      if( rCrsrNd.GetIndex() > pDoc->GetNodes().GetEndOfExtras().GetIndex() )
//STRIP001          // Cusor steht im Body-Bereich!
//STRIP001          return 0;
//STRIP001
//STRIP001      for( sal_uInt16 n = 0; n < nCnt; ++n )
//STRIP001      {
//STRIP001          SwFrmFmt* pFmt = rSpzArr[ n ];
//STRIP001          const SwNodeIndex* pIdx = pFmt->GetCntnt( sal_False ).GetCntntIdx();
//STRIP001          SwStartNode* pSttNd;
//STRIP001          if( pIdx &&
//STRIP001              0 != ( pSttNd = pIdx->GetNode().GetStartNode() ) &&
//STRIP001              pSttNd->GetIndex() < rCrsrNd.GetIndex() &&
//STRIP001              rCrsrNd.GetIndex() < pSttNd->EndOfSectionIndex() )
//STRIP001          {
//STRIP001              // gefunden: also raus damit
//STRIP001              return pFmt;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }

//STRIP001 void SwFEShell::SetFlyName( const String& rName )
//STRIP001 {
//STRIP001  SwLayoutFrm *pFly = FindFlyFrm();
//STRIP001  if( pFly )
//STRIP001      GetDoc()->SetFlyName( *(SwFlyFrmFmt*)pFly->GetFmt(), rName );
//STRIP001  else
//STRIP001      ASSERT( !this, "kein FlyFrame selektiert" )
//STRIP001 }

//STRIP001 const String& SwFEShell::GetFlyName() const
//STRIP001 {
//STRIP001  SwLayoutFrm *pFly = FindFlyFrm();
//STRIP001  if( pFly )
//STRIP001      return pFly->GetFmt()->GetName();
//STRIP001
//STRIP001  ASSERT( !this, "kein FlyFrame selektiert" )
//STRIP001  return aEmptyStr;
//STRIP001 }


//STRIP001 String SwFEShell::GetUniqueGrfName() const
//STRIP001 {
//STRIP001  return GetDoc()->GetUniqueGrfName();
//STRIP001 }

//STRIP001 const SwFrmFmt* SwFEShell::IsURLGrfAtPos( const Point& rPt, String* pURL,
//STRIP001                                      String *pTargetFrameName,
//STRIP001                                      String *pDescription ) const
//STRIP001 {
//STRIP001  if( !Imp()->HasDrawView() )
//STRIP001      return 0;
//STRIP001
//STRIP001  SdrObject* pObj;
//STRIP001  SdrPageView* pPV;
//STRIP001  const SwFrmFmt* pRet = 0;
//STRIP001  SwDrawView *pDView = (SwDrawView*)Imp()->GetDrawView();
//STRIP001
//STRIP001  sal_uInt16 nOld = pDView->GetHitTolerancePixel();
//STRIP001  pDView->SetHitTolerancePixel( 2 );
//STRIP001
//STRIP001  if( pDView->PickObj( rPt, pObj, pPV,SDRSEARCH_PICKMACRO ) &&
//STRIP001      pObj->IsWriterFlyFrame() )
//STRIP001  {
//STRIP001      SwFlyFrm *pFly = ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm();
//STRIP001      const SwFmtURL &rURL = pFly->GetFmt()->GetURL();
//STRIP001      if( rURL.GetURL().Len() || rURL.GetMap() )
//STRIP001      {
//STRIP001          FASTBOOL bSetTargetFrameName = pTargetFrameName != 0;
//STRIP001          FASTBOOL bSetDescription = pDescription != 0;
//STRIP001          if ( rURL.GetMap() )
//STRIP001          {
//STRIP001              IMapObject *pObj = pFly->GetFmt()->GetIMapObject( rPt, pFly );
//STRIP001              if ( pObj && pObj->GetURL().Len() )
//STRIP001              {
//STRIP001                  if( pURL )
//STRIP001                      *pURL = pObj->GetURL();
//STRIP001                  if ( bSetTargetFrameName && pObj->GetTarget().Len() )
//STRIP001                  {
//STRIP001                      bSetTargetFrameName = sal_False;
//STRIP001                      *pTargetFrameName = pObj->GetTarget();
//STRIP001                  }
//STRIP001                  if ( bSetDescription )
//STRIP001                  {
//STRIP001                      bSetDescription = sal_False;
//STRIP001                      *pDescription = pObj->GetDescription();
//STRIP001                  }
//STRIP001                  pRet = pFly->GetFmt();
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              if( pURL )
//STRIP001              {
//STRIP001                  *pURL = rURL.GetURL();
//STRIP001                  if( rURL.IsServerMap() )
//STRIP001                  {
//STRIP001                      // dann die rel. Pixel Position anhaengen !!
//STRIP001                      Point aPt( rPt );
//STRIP001                      aPt -= pFly->Frm().Pos();
//STRIP001                      // ohne MapMode-Offset, ohne Offset, o ... !!!!!
//STRIP001                      aPt = (Point&)(Size&)GetOut()->LogicToPixel(
//STRIP001                              (Size&)aPt, MapMode( MAP_TWIP ) );
//STRIP001                      ((( *pURL += '?' ) += String::CreateFromInt32( aPt.X() ))
//STRIP001                                += ',' ) += String::CreateFromInt32(aPt.Y() );
//STRIP001                  }
//STRIP001              }
//STRIP001              pRet = pFly->GetFmt();
//STRIP001          }
//STRIP001          if ( bSetTargetFrameName )
//STRIP001              *pTargetFrameName = rURL.GetTargetFrameName();
//STRIP001          if ( bSetDescription )
//STRIP001              *pDescription = pFly->GetFmt()->GetName();
//STRIP001      }
//STRIP001  }
//STRIP001  pDView->SetHitTolerancePixel( nOld );
//STRIP001  return pRet;
//STRIP001 }

//STRIP001 const Graphic *SwFEShell::GetGrfAtPos( const Point &rPt,
//STRIP001                                     String &rName, sal_Bool &rbLink ) const
//STRIP001 {
//STRIP001  if( !Imp()->HasDrawView() )
//STRIP001      return 0;
//STRIP001
//STRIP001  SdrObject* pObj;
//STRIP001  SdrPageView* pPV;
//STRIP001  SwDrawView *pDView = (SwDrawView*)Imp()->GetDrawView();
//STRIP001
//STRIP001  if( pDView->PickObj( rPt, pObj, pPV ) && pObj->IsWriterFlyFrame() )
//STRIP001  {
//STRIP001      SwFlyFrm *pFly = ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm();
//STRIP001      if ( pFly->Lower() && pFly->Lower()->IsNoTxtFrm() )
//STRIP001      {
//STRIP001          SwGrfNode *pNd = ((SwCntntFrm*)pFly->Lower())->GetNode()->GetGrfNode();
//STRIP001          if ( pNd )
//STRIP001          {
//STRIP001              if ( pNd->IsGrfLink() )
//STRIP001              {
//STRIP001                  //Halbfertige Grafik?
//STRIP001                  ::so3::SvLinkSource* pLnkObj = pNd->GetLink()->GetObj();
//STRIP001                  if( pLnkObj && pLnkObj->IsPending() )
//STRIP001                      return 0;
//STRIP001                  rbLink = sal_True;
//STRIP001              }
//STRIP001
//STRIP001              pNd->GetFileFilterNms( &rName, 0 );
//STRIP001              if ( !rName.Len() )
//STRIP001                  rName = pFly->GetFmt()->GetName();
//STRIP001              pNd->SwapIn( sal_True );
//STRIP001              return &pNd->GetGrf();
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }


//STRIP001 const SwFrmFmt* SwFEShell::GetFmtFromObj( const Point& rPt, SwRect** pRectToFill ) const
//STRIP001 {
//STRIP001  SwFrmFmt* pRet = 0;
//STRIP001
//STRIP001  if( Imp()->HasDrawView() )
//STRIP001  {
//STRIP001      SdrObject* pObj;
//STRIP001      SdrPageView* pPView;
//STRIP001
//STRIP001      SwDrawView *pDView = (SwDrawView*)Imp()->GetDrawView();
//STRIP001
//STRIP001      sal_uInt16 nOld = pDView->GetHitTolerancePixel();
//STRIP001      // Tattergrenze fuer Drawing-SS
//STRIP001      pDView->SetHitTolerancePixel( pDView->GetMarkHdlSizePixel()/2 );
//STRIP001
//STRIP001      if( pDView->PickObj( rPt, pObj, pPView, SDRSEARCH_PICKMARKABLE ) )
//STRIP001      {
//STRIP001          // dann teste mal was es ist:
//STRIP001          if ( pObj->IsWriterFlyFrame() )
//STRIP001              pRet = ((SwVirtFlyDrawObj*)pObj)->GetFmt();
//STRIP001          else if ( pObj->GetUserCall() ) //nicht fuer Gruppenobjekte
//STRIP001              pRet = ((SwDrawContact*)pObj->GetUserCall())->GetFmt();
//STRIP001          if(pRet && pRectToFill)
//STRIP001              **pRectToFill = pObj->GetBoundRect();
//STRIP001      }
//STRIP001      pDView->SetHitTolerancePixel( nOld );
//STRIP001  }
//STRIP001  return pRet;
//STRIP001 }

// returns a format too, if the point is over the text of any fly
//STRIP001 const SwFrmFmt* SwFEShell::GetFmtFromAnyObj( const Point& rPt ) const
//STRIP001 {
//STRIP001  const SwFrmFmt* pRet = GetFmtFromObj( rPt );
//STRIP001  if( !pRet || RES_FLYFRMFMT == pRet->Which() )
//STRIP001  {
//STRIP001      SwPosition aPos( *GetCrsr()->GetPoint() );
//STRIP001      Point aPt( rPt );
//STRIP001      GetLayout()->GetCrsrOfst( &aPos, aPt );
//STRIP001      SwCntntNode *pNd = aPos.nNode.GetNode().GetCntntNode();
//STRIP001      SwFrm* pFrm = pNd->GetFrm( &rPt )->FindFlyFrm();
//STRIP001      pRet = pFrm ? ((SwLayoutFrm*)pFrm)->GetFmt() : 0;
//STRIP001  }
//STRIP001  return pRet;
//STRIP001 }

//STRIP001 ObjCntType SwFEShell::GetObjCntType( const SdrObject& rObj ) const
//STRIP001 {
//STRIP001  ObjCntType eType;
//STRIP001
//STRIP001     // OD 23.06.2003 #108784# - investigate 'master' drawing object, if method
//STRIP001     // is called for a 'virtual' drawing object.
//STRIP001     const SdrObject* pInvestigatedObj;
//STRIP001     if ( rObj.ISA(SwDrawVirtObj) )
//STRIP001     {
//STRIP001         const SwDrawVirtObj* pDrawVirtObj = static_cast<const SwDrawVirtObj*>(&rObj);
//STRIP001         pInvestigatedObj = &(pDrawVirtObj->GetReferencedObj());
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         pInvestigatedObj = &rObj;
//STRIP001     }
//STRIP001
//STRIP001     if( FmFormInventor == pInvestigatedObj->GetObjInventor() )
//STRIP001  {
//STRIP001      eType = OBJCNT_CONTROL;
//STRIP001         uno::Reference< awt::XControlModel >  xModel =
//STRIP001                 ((SdrUnoObj&)(*pInvestigatedObj)).GetUnoControlModel();
//STRIP001      if( xModel.is() )
//STRIP001      {
//STRIP001          uno::Any aVal;
//STRIP001          OUString sName = OUString::createFromAscii("ButtonType");
//STRIP001          uno::Reference< beans::XPropertySet >  xSet(xModel, uno::UNO_QUERY);
//STRIP001
//STRIP001          uno::Reference< beans::XPropertySetInfo >  xInfo = xSet->getPropertySetInfo();
//STRIP001          if(xInfo->hasPropertyByName( sName ))
//STRIP001          {
//STRIP001              beans::Property xProperty = xInfo->getPropertyByName( sName );
//STRIP001              aVal = xSet->getPropertyValue( sName );
//STRIP001              if( aVal.getValue() && form::FormButtonType_URL == *((form::FormButtonType*)aVal.getValue()) )
//STRIP001                  eType = OBJCNT_URLBUTTON;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001     else if( pInvestigatedObj->IsWriterFlyFrame() )
//STRIP001  {
//STRIP001         SwFlyFrm *pFly = ((SwVirtFlyDrawObj&)(*pInvestigatedObj)).GetFlyFrm();
//STRIP001      if ( pFly->Lower() && pFly->Lower()->IsNoTxtFrm() )
//STRIP001      {
//STRIP001          if ( ((SwCntntFrm*)pFly->Lower())->GetNode()->GetGrfNode() )
//STRIP001              eType = OBJCNT_GRF;
//STRIP001          else
//STRIP001              eType = OBJCNT_OLE;
//STRIP001      }
//STRIP001      else
//STRIP001          eType = OBJCNT_FLY;
//STRIP001  }
//STRIP001     else if( pInvestigatedObj->ISA( SdrObjGroup ) &&
//STRIP001              FLY_IN_CNTNT !=
//STRIP001                 ((SwDrawContact*)GetUserCall(pInvestigatedObj))->GetFmt()->GetAnchor().GetAnchorId() )
//STRIP001      eType = OBJCNT_GROUPOBJ;
//STRIP001  else
//STRIP001      eType = OBJCNT_SIMPLE;
//STRIP001  return eType;
//STRIP001 }

//STRIP001 ObjCntType SwFEShell::GetObjCntType( const Point &rPt, SdrObject *&rpObj ) const
//STRIP001 {
//STRIP001  ObjCntType eType = OBJCNT_NONE;
//STRIP001
//STRIP001  if( Imp()->HasDrawView() )
//STRIP001  {
//STRIP001      SdrObject* pObj;
//STRIP001      SdrPageView* pPView;
//STRIP001
//STRIP001      SwDrawView *pDView = (SwDrawView*)Imp()->GetDrawView();
//STRIP001
//STRIP001      sal_uInt16 nOld = pDView->GetHitTolerancePixel();
//STRIP001      // Tattergrenze fuer Drawing-SS
//STRIP001      pDView->SetHitTolerancePixel( pDView->GetMarkHdlSizePixel()/2 );
//STRIP001
//STRIP001      if( pDView->PickObj( rPt, pObj, pPView, SDRSEARCH_PICKMARKABLE ) )
//STRIP001          eType = GetObjCntType( *(rpObj = pObj) );
//STRIP001
//STRIP001      pDView->SetHitTolerancePixel( nOld );
//STRIP001  }
//STRIP001  return eType;
//STRIP001 }

/*N*/ ObjCntType SwFEShell::GetObjCntTypeOfSelection( SdrObject** ppObj ) const
/*N*/ {
/*N*/   ObjCntType eType = OBJCNT_NONE;
/*N*/
/*N*/   if( Imp()->HasDrawView() )
/*N*/   {
/*N*/       const SdrMarkList &rMrkList = Imp()->GetDrawView()->GetMarkList();
/*N*/       for( sal_uInt32 i = 0, nE = rMrkList.GetMarkCount(); i < nE; ++i )
/*N*/       {
/*?*/           DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SdrObject* pObj = rMrkList.GetMark( i )->GetObj();
//STRIP001 /*?*/            ObjCntType eTmp = GetObjCntType( *pObj );
//STRIP001 /*?*/            if( !i )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                eType = eTmp;
//STRIP001 /*?*/                if( ppObj ) *ppObj = pObj;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            else if( eTmp != eType )
//STRIP001 /*?*/            {
//STRIP001 /*?*/                eType = OBJCNT_DONTCARE;
//STRIP001 /*?*/                // einmal DontCare, immer DontCare!
//STRIP001 /*?*/                break;
//STRIP001 /*?*/            }
/*N*/       }
/*N*/   }
/*N*/   return eType;
/*N*/ }


//STRIP001 sal_Bool SwFEShell::ReplaceSdrObj( const String& rGrfName, const String& rFltName,
//STRIP001                              const Graphic* pGrf )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001
//STRIP001  sal_Bool bRet = sal_False;
//STRIP001  const SdrMarkList *pMrkList;
//STRIP001  if( Imp()->HasDrawView() &&  1 ==
//STRIP001      ( pMrkList = &Imp()->GetDrawView()->GetMarkList())->GetMarkCount() )
//STRIP001  {
//STRIP001      SdrObject* pObj = pMrkList->GetMark( 0 )->GetObj();
//STRIP001      SwFrmFmt *pFmt = FindFrmFmt( pObj );
//STRIP001
//STRIP001      // Attribute sichern und dann an der Grafik setzen
//STRIP001      SfxItemSet aFrmSet( pDoc->GetAttrPool(),
//STRIP001                          pFmt->GetAttrSet().GetRanges() );
//STRIP001      aFrmSet.Set( pFmt->GetAttrSet() );
//STRIP001
//STRIP001      // Groesse und Position setzen ??
//STRIP001      if( !pObj->IsWriterFlyFrame() )
//STRIP001      {
//STRIP001          // dann mal los:
//STRIP001          const Rectangle &rBound = pObj->GetSnapRect();
//STRIP001          Point aRelPos( pObj->GetRelativePos() );
//STRIP001
//STRIP001          const long nWidth = rBound.Right()  - rBound.Left();
//STRIP001          const long nHeight= rBound.Bottom() - rBound.Top();
//STRIP001          aFrmSet.Put( SwFmtFrmSize( ATT_MIN_SIZE,
//STRIP001                              Max( nWidth,  long(MINFLY) ),
//STRIP001                              Max( nHeight, long(MINFLY) )));
//STRIP001
//STRIP001          if( SFX_ITEM_SET != aFrmSet.GetItemState( RES_HORI_ORIENT ))
//STRIP001              aFrmSet.Put( SwFmtHoriOrient( aRelPos.X(), HORI_NONE, FRAME ));
//STRIP001
//STRIP001          if( SFX_ITEM_SET != aFrmSet.GetItemState( RES_VERT_ORIENT ))
//STRIP001              aFrmSet.Put( SwFmtVertOrient( aRelPos.Y(), VERT_NONE, FRAME ));
//STRIP001
//STRIP001      }
//STRIP001
//STRIP001      sal_uInt32 nOrdNum = pObj->GetOrdNum();
//STRIP001
//STRIP001      StartAllAction();
//STRIP001      StartUndo();
//STRIP001
//STRIP001      // das "Sdr-Object" loeschen und dafuer die Grafik einfuegen
//STRIP001      DelSelectedObj();
//STRIP001
//STRIP001      pFmt = GetDoc()->Insert( *GetCrsr(), rGrfName, rFltName, pGrf, &aFrmSet );
//STRIP001
//STRIP001      // die Ordnungsnummer (Z-Order) noch uebertragen
//STRIP001      // JP 04.07.98: klappt aber nicht richtig!
//STRIP001      //SdrObject* pNewObj = ::FindSdrObject( pFmt );
//STRIP001      //pNewObj->SetOrdNum( nOrdNum );
//STRIP001
//STRIP001      EndUndo();
//STRIP001      EndAllAction();
//STRIP001      bRet = sal_True;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*M*/ static USHORT SwFmtGetPageNum(const SwFlyFrmFmt * pFmt)
/*M*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001
//STRIP001 /*?*/     ASSERT(pFmt != NULL, "invalid argument");
//STRIP001 /*?*/
//STRIP001 /*?*/     SwFlyFrm * pFrm = pFmt->GetFrm();
//STRIP001 /*?*/
//STRIP001 /*?*/     USHORT aResult;
//STRIP001 /*?*/
//STRIP001 /*?*/     if (pFrm != NULL)
//STRIP001 /*?*/         aResult = pFrm->GetPhyPageNum();
//STRIP001 /*?*/     else
//STRIP001 /*?*/         aResult = pFmt->GetAnchor().GetPageNum();
//STRIP001 /*?*/
//STRIP001 /*?*/     return aResult;
/*M*/ }
} //namespace binfilter
#include <fmtcnct.hxx>
#if 0
#include <algorithm>
#include <iostream>
#include <iterator>


/*M*/ static ::std::ostream & operator << (::std::ostream & aStream,
/*M*/                                      const String & aString)
/*M*/ {
/*M*/     ByteString aByteString(aString, RTL_TEXTENCODING_ASCII_US);
/*M*/     aStream << aByteString.GetBuffer();
/*M*/
/*M*/     return aStream;
/*M*/ }

/*M*/ void lcl_PrintFrameChainPrev(const SwFrmFmt * pFmt)
/*M*/ {
/*M*/     if (pFmt != NULL)
/*M*/     {
/*M*/         lcl_PrintFrameChainPrev(pFmt->GetChain().GetPrev());
/*M*/
/*M*/         ::std::clog << pFmt->GetName() << "->";
/*M*/     }
/*M*/ }

/*M*/ void lcl_PrintFrameChainNext(const SwFrmFmt * pFmt)
/*M*/ {
/*M*/     if (pFmt != NULL)
/*M*/     {
/*M*/         ::std::clog << "->" << pFmt->GetName();
/*M*/
/*M*/         lcl_PrintFrameChainPrev(pFmt->GetChain().GetNext());
/*M*/     }
/*M*/ }

/*M*/ void lcl_PrintFrameChain(const SwFrmFmt & rFmt)
/*M*/ {
/*M*/     lcl_PrintFrameChainPrev(rFmt.GetChain().GetPrev());
/*M*/     ::std::clog << "(" <<  rFmt.GetName() << ")";
/*M*/     lcl_PrintFrameChainNext(rFmt.GetChain().GetNext());
/*M*/     ::std::clog << ::std::endl;
/*M*/ }

/*M*/ String lcl_GetChainableString(int nVal)
/*M*/ {
/*M*/     switch(nVal)
/*M*/     {
/*M*/     case SW_CHAIN_OK:
/*M*/         return String::CreateFromAscii("OK");
/*M*/
/*M*/     case SW_CHAIN_SOURCE_CHAINED:
/*M*/         return String::CreateFromAscii("source chained");
/*M*/
/*M*/     case SW_CHAIN_SELF:
/*M*/         return String::CreateFromAscii("self");
/*M*/
/*M*/     case SW_CHAIN_IS_IN_CHAIN:
/*M*/         return String::CreateFromAscii("in chain");
/*M*/
/*M*/     case SW_CHAIN_NOT_FOUND:
/*M*/         return String::CreateFromAscii("not found");
/*M*/
/*M*/     case SW_CHAIN_NOT_EMPTY:
/*M*/         return String::CreateFromAscii("not empty");
/*M*/
/*M*/     case SW_CHAIN_WRONG_AREA:
/*M*/         return String::CreateFromAscii("wrong area");
/*M*/
/*M*/     default:
/*M*/         return String::CreateFromAscii("??");
/*M*/
/*M*/     }
/*M*/ }
#endif

namespace binfilter {//STRIP009
/*M*/ void SwFEShell::GetConnectableFrmFmts(SwFrmFmt & rFmt,
/*M*/                                       const String & rReference,
/*M*/                                       BOOL bSuccessors,
/*M*/                                       ::std::vector< String > & aPrevPageVec,
/*M*/                                       ::std::vector< String > & aThisPageVec,
/*M*/                                       ::std::vector< String > & aNextPageVec,
/*M*/                                       ::std::vector< String > & aRestVec)
/*M*/ {
/*M*/ #if 0
/*M*/     ::std::clog << "Connectables:" << rFmt.GetName() << ","
/*M*/                 << (bSuccessors ? "succ" : "pred") << "," << rReference
/*M*/                 << ::std::endl;
/*M*/     lcl_PrintFrameChain(rFmt);
/*M*/     ::std::vector< String > aResult;
/*M*/ #endif
/*M*/
/*M*/     StartAction();
/*M*/
/*M*/     SwFmtChain rChain = rFmt.GetChain();
/*M*/     SwFrmFmt * pOldChainNext = (SwFrmFmt *) rChain.GetNext();
/*M*/     SwFrmFmt * pOldChainPrev = (SwFrmFmt *) rChain.GetPrev();
/*M*/
/*M*/     if (pOldChainNext)
/*M*/         pDoc->Unchain(rFmt);
/*M*/
/*M*/     if (pOldChainPrev)
/*M*/         pDoc->Unchain(*pOldChainPrev);
/*M*/
/*M*/     sal_uInt16 nCnt = pDoc->GetFlyCount(FLYCNTTYPE_FRM);
/*M*/
/*M*/     /* potential successors resp. predecessors */
/*M*/     ::std::vector< const SwFrmFmt * > aTmpSpzArray;
/*M*/
/*M*/     SwFrmFmt * pNext = (SwFrmFmt *) pDoc->FindFlyByName(rReference);
/*M*/
/*M*/     for (sal_uInt16 n = 0; n < nCnt; n++)
/*M*/     {
/*M*/         const SwFrmFmt & rFmt1 = *(pDoc->GetFlyNum(n, FLYCNTTYPE_FRM));
/*M*/
        /*
           pFmt is a potential successor of rFmt if it is chainable after
           rFmt.

           pFmt is a potential predecessor of rFmt if rFmt is chainable
           after pFmt.
        */
/*M*/
/*M*/ #if 0
/*M*/         if (bSuccessors)
/*M*/             ::std::clog << rFmt.GetName() << "->" << rFmt1.GetName() << "?:";
/*M*/         else
/*M*/             ::std::clog << rFmt1.GetName() << "->" << rFmt.GetName() << "?:";
/*M*/ #endif
/*M*/
/*M*/         int nChainState;
/*M*/
/*M*/         if (bSuccessors)
/*?*/             {DBG_BF_ASSERT(0, "STRIP");nChainState=0; }//STRIP001 nChainState = pDoc->Chainable(rFmt, rFmt1);
/*M*/         else
/*?*/             {DBG_BF_ASSERT(0, "STRIP");nChainState=0; }//STRIP001 nChainState = pDoc->Chainable(rFmt1, rFmt);
/*M*/
/*M*/ #if 0
/*M*/             ::std::clog << lcl_GetChainableString(nChainState) << ::std::endl;
/*M*/ #endif
/*M*/
/*M*/         if (nChainState == SW_CHAIN_OK)
/*M*/         {
/*M*/             aTmpSpzArray.push_back(&rFmt1);
/*M*/
/*M*/         }
/*M*/
/*M*/     }
/*M*/
/*M*/     if  (aTmpSpzArray.size() > 0)
/*M*/     {
/*M*/         aPrevPageVec.clear();
/*M*/         aThisPageVec.clear();
/*M*/         aNextPageVec.clear();
/*M*/         aRestVec.clear();
/*M*/
/*M*/         /* number of page rFmt resides on */
/*M*/         USHORT nPageNum = SwFmtGetPageNum((SwFlyFrmFmt *) &rFmt);
/*M*/
/*M*/         ::std::vector< const SwFrmFmt * >::const_iterator aIt;
/*M*/
/*M*/         for (aIt = aTmpSpzArray.begin(); aIt != aTmpSpzArray.end(); aIt++)
/*M*/         {
/*M*/             String  aString = (*aIt)->GetName();
/*M*/
            /* rFmt is not a vaild successor or predecessor of
               itself */
/*M*/             if (aString != rReference && aString != rFmt.GetName())
/*M*/             {
/*M*/                 USHORT nNum1 =
/*M*/                     SwFmtGetPageNum((SwFlyFrmFmt *) *aIt);
/*M*/
/*M*/                 if (nNum1 == nPageNum -1)
/*M*/                     aPrevPageVec.push_back(aString);
/*M*/                 else if (nNum1 == nPageNum)
/*M*/                     aThisPageVec.push_back(aString);
/*M*/                 else if (nNum1 == nPageNum + 1)
/*M*/                     aNextPageVec.push_back(aString);
/*M*/                 else
/*M*/                     aRestVec.push_back(aString);
/*M*/             }
/*M*/         }
/*M*/
/*M*/     }
/*M*/
/*M*/     if (pOldChainNext)
/*M*/         pDoc->Chain(rFmt, *pOldChainNext);
/*M*/
/*M*/     if (pOldChainPrev)
/*M*/         pDoc->Chain(*pOldChainPrev, rFmt);
/*M*/
/*M*/     EndAction();
/*M*/
/*M*/ #if 0
/*M*/     ::std::copy(aPrevPageVec.begin(), aPrevPageVec.end(),
/*M*/                 ::std::ostream_iterator<String>(::std::clog, "\n"));
/*M*/     ::std::clog << "-------------------------" << ::std::endl;
/*M*/     ::std::copy(aThisPageVec.begin(), aThisPageVec.end(),
/*M*/                 ::std::ostream_iterator<String>(::std::clog, "\n"));
/*M*/     ::std::clog << "-------------------------" << ::std::endl;
/*M*/     ::std::copy(aNextPageVec.begin(), aNextPageVec.end(),
/*M*/                 ::std::ostream_iterator<String>(::std::clog, "\n"));
/*M*/     ::std::clog << "-------------------------" << ::std::endl;
/*M*/     ::std::copy(aRestVec.begin(), aRestVec.end(),
/*M*/                 ::std::ostream_iterator<String>(::std::clog, "\n"));
/*M*/     ::std::clog << "-------------------------" << ::std::endl;
/*M*/ #endif
/*M*/ }
}
