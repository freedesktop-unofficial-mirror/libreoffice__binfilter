/*************************************************************************
 *
 *  $RCSfile: sw_feshview.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 17:28:53 $
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

#define ITEMID_BOXINFO      SID_ATTR_BORDER_INNER
#include "hintids.hxx"

#ifdef WIN
#define NEEDED_BY_FESHVIEW
#define _FESHVIEW_ONLY_INLINE_NEEDED
#endif

// auto strip #ifndef _SVDOUNO_HXX //autogen
// auto strip #include <bf_svx/svdouno.hxx>
// auto strip #endif
// auto strip #ifndef _SVDOOLE2_HXX //autogen
// auto strip #include <bf_svx/svdoole2.hxx>
// auto strip #endif
// auto strip #ifndef _SVDOGRP_HXX //autogen
// auto strip #include <bf_svx/svdogrp.hxx>
// auto strip #endif
// auto strip #ifndef _SVDOCIRC_HXX
// auto strip #include <bf_svx/svdocirc.hxx>
// auto strip #endif
#ifndef _SVDOPATH_HXX
#include <bf_svx/svdopath.hxx>
#endif
// auto strip #ifndef _SXCIAITM_HXX
// auto strip #include <bf_svx/sxciaitm.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_FILLITEM_HXX //autogen
// auto strip #include <bf_svx/xfillit.hxx>
// auto strip #endif
#ifndef _SVDVMARK_HXX //autogen
#include <bf_svx/svdvmark.hxx>
#endif
// auto strip #ifndef _XPOLY_HXX //autogen
// auto strip #include <bf_svx/xpoly.hxx>
// auto strip #endif
// auto strip #ifndef _SVDCAPT_HXX //autogen
// auto strip #include <bf_svx/svdocapt.hxx>
// auto strip #endif
// auto strip #ifndef _SFXAPP_HXX //autogen
// auto strip #include <bf_sfx2/app.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_BOXITEM_HXX //autogen
// auto strip #include <bf_svx/boxitem.hxx>
// auto strip #endif
// auto strip #ifndef _SVX_OPAQITEM_HXX //autogen
// auto strip #include <bf_svx/opaqitem.hxx>
// auto strip #endif
#ifndef _SVX_PROTITEM_HXX //autogen
#include <bf_svx/protitem.hxx>
#endif
// auto strip #ifndef _SVDPAGE_HXX //autogen
// auto strip #include <bf_svx/svdpage.hxx>
// auto strip #endif
// auto strip #ifndef _SVDPAGV_HXX //autogen wg. SdrPageView
// auto strip #include <bf_svx/svdpagv.hxx>
// auto strip #endif
#ifndef _IPOBJ_HXX //autogen
#include <so3/ipobj.hxx>
#endif

#ifndef _POOLFMT_HRC
#include <poolfmt.hrc>      // fuer InitFldTypes
#endif
#ifndef _FRMFMT_HXX //autogen
#include <frmfmt.hxx>
#endif
#ifndef _FRMATR_HXX
#include <frmatr.hxx>
#endif
// auto strip #ifndef _FMTFSIZE_HXX //autogen
// auto strip #include <fmtfsize.hxx>
// auto strip #endif
// auto strip #ifndef _FMTANCHR_HXX //autogen
// auto strip #include <fmtanchr.hxx>
// auto strip #endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

// auto strip #ifndef _FMTORNT_HXX //autogen
// auto strip #include <fmtornt.hxx>
// auto strip #endif
// auto strip #ifndef _FMTSRND_HXX //autogen
// auto strip #include <fmtsrnd.hxx>
// auto strip #endif
// auto strip #ifndef _FMTCNTNT_HXX //autogen
// auto strip #include <fmtcntnt.hxx>
// auto strip #endif
// auto strip #ifndef _FMTFLCNT_HXX //autogen
// auto strip #include <fmtflcnt.hxx>
// auto strip #endif
// auto strip #ifndef _FMTCNCT_HXX //autogen
// auto strip #include <fmtcnct.hxx>
// auto strip #endif
// auto strip #ifndef _DOCARY_HXX
// auto strip #include <docary.hxx>
// auto strip #endif
// auto strip #ifndef _TBLSEL_HXX //autogen
// auto strip #include <tblsel.hxx>
// auto strip #endif
// auto strip #ifndef _SWTABLE_HXX //autogen
// auto strip #include <swtable.hxx>
// auto strip #endif
// auto strip #ifndef _FLYFRMS_HXX
// auto strip #include <flyfrms.hxx>
// auto strip #endif
#include "fesh.hxx"
// auto strip #include "rootfrm.hxx"
// auto strip #include "pagefrm.hxx"
// auto strip #include "sectfrm.hxx"
#include "doc.hxx"
#include "dview.hxx"
#include "dflyobj.hxx"
#include "dcontact.hxx"
#include "viewimp.hxx"
#include "flyfrm.hxx"
// auto strip #include "pam.hxx"
#include "ndole.hxx"
// auto strip #include "ndgrf.hxx"
// auto strip #include "ndtxt.hxx"
// auto strip #include "viewopt.hxx"                    // fuer GetHTMLMode
// auto strip #include "swundo.hxx"
// auto strip #include "notxtfrm.hxx"
#include "txtfrm.hxx"
// auto strip #include "txatbase.hxx"
// auto strip #include "mdiexp.hxx"                 // fuer Update der Statuszeile bei drag
namespace binfilter {

#define SCROLLVAL 75

//Tattergrenze fuer Drawing-SS
#define MINMOVE ((USHORT)GetOut()->PixelToLogic(Size(Imp()->GetDrawView()->GetMarkHdlSizePixel()/2,0)).Width())

/*N*/ SwFlyFrm *GetFlyFromMarked( const SdrMarkList *pLst, ViewShell *pSh )
/*N*/ {
/*N*/   if ( !pLst )
/*?*/       pLst = pSh->HasDrawView() ? &pSh->Imp()->GetDrawView()->GetMarkList():0;
/*N*/
/*N*/   if ( pLst && pLst->GetMarkCount() == 1 )
/*N*/   {
/*?*/       SdrObject *pO = pLst->GetMark( 0 )->GetObj();
/*?*/       if ( pO->IsWriterFlyFrame() )
/*?*/           return ((SwVirtFlyDrawObj*)pO)->GetFlyFrm();
/*N*/   }
/*N*/   return 0;
/*N*/ }

//STRIP001 void lcl_GrabCursor( SwFEShell* pSh, SwFlyFrm* pOldSelFly)
//STRIP001 {
//STRIP001  const SwFrmFmt *pFlyFmt = pSh->SelFlyGrabCrsr();
//STRIP001  if( pFlyFmt && !pSh->ActionPend() &&
//STRIP001                      (!pOldSelFly || pOldSelFly->GetFmt() != pFlyFmt) )
//STRIP001  {
//STRIP001      // dann das evt. gesetzte Macro rufen
//STRIP001      pSh->GetFlyMacroLnk().Call( (void*)pFlyFmt );
//STRIP001 extern BOOL bNoInterrupt;        // in swapp.cxx
//STRIP001      // wir in dem Makro ein Dialog gestartet, dann kommt das
//STRIP001      // MouseButtonUp zu diesem und nicht zu uns. Dadurch ist
//STRIP001      // Flag bei uns immer gesetzt und schaltet nie die auf die
//STRIP001      // entsp. Shell um !!!!!!!
//STRIP001      bNoInterrupt = FALSE;
//STRIP001  }
//STRIP001  else if( !pFlyFmt || RES_DRAWFRMFMT == pFlyFmt->Which() )
//STRIP001      pSh->SetCrsr( pSh->Imp()->GetDrawView()->GetAllMarkedRect().TopLeft(), TRUE);
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::SelectObj()
|*
|*  Ersterstellung      MA 16. Nov. 92
|*  Letzte Aenderung    MA 22. Oct. 96
|*
*************************************************************************/

/*N*/ BOOL SwFEShell::SelectObj( const Point& rPt, BYTE nFlag, SdrObject *pObj )
/*N*/ {
DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 //STRIP001   SET_CURR_SHELL( this );
//STRIP001  StartAction();          //Aktion ist Notwendig, damit nicht mehrere
//STRIP001                          //AttrChgdNotify (etwa durch Unmark->MarkListHasChgd)
//STRIP001                          //durchkommen
//STRIP001
//STRIP001  ASSERT( Imp()->HasDrawView(), "SelectObj without DrawView?" );
//STRIP001  SwDrawView *pDView = Imp()->GetDrawView();
//STRIP001  const SdrMarkList &rMrkList = pDView->GetMarkList();
//STRIP001  const BOOL bHadSelection = rMrkList.GetMarkCount() ? TRUE : FALSE;
//STRIP001     const BOOL bAddSelect = 0 != (SW_ADD_SELECT & nFlag);
//STRIP001     const BOOL bEnterGroup = 0 != (SW_ENTER_GROUP & nFlag);
//STRIP001  SwFlyFrm* pOldSelFly = 0;
//STRIP001  const Point aOldPos( pDView->GetAllMarkedRect().TopLeft() );
//STRIP001
//STRIP001  if( bHadSelection )
//STRIP001  {
//STRIP001      //Unmark rufen wenn !bAddSelect oder wenn ein Fly selektiert ist.
//STRIP001         BOOL bUnmark = !bAddSelect;
//STRIP001
//STRIP001      if ( rMrkList.GetMarkCount() == 1 )
//STRIP001      {
//STRIP001          //Wenn ein Fly selektiert ist, so muss er erst deselektiert werden.
//STRIP001          pOldSelFly = ::GetFlyFromMarked( &rMrkList, this );
//STRIP001          if ( pOldSelFly )
//STRIP001          {
//STRIP001              const USHORT nType = GetCntType();
//STRIP001                 if( nType != CNT_TXT || (SW_LEAVE_FRAME & nFlag) ||
//STRIP001                  ( pOldSelFly->GetFmt()->GetProtect().IsCntntProtected()
//STRIP001                   && !IsReadOnlyAvailable() ))
//STRIP001              {
//STRIP001                  //Wenn ein Fly deselektiert wird, der Grafik, Ole o.ae.
//STRIP001                  //enthaelt, so muss der Crsr aus diesem entfernt werden.
//STRIP001                  //Desgleichen wenn ein Fly mit geschuetztem Inhalt deselektiert
//STRIP001                  //wird. Der Einfachheit halber wire der Crsr 'grad so neben die
//STRIP001                  //linke obere Ecke gesetzt.
//STRIP001                  Point aPt( pOldSelFly->Frm().Pos() );
//STRIP001                  aPt.X() -= 1;
//STRIP001                  BOOL bUnLockView = !IsViewLocked();
//STRIP001                  LockView( TRUE );
//STRIP001                  SetCrsr( aPt, TRUE );
//STRIP001                  if( bUnLockView )
//STRIP001                      LockView( FALSE );
//STRIP001              }
//STRIP001              if ( nType & CNT_GRF &&
//STRIP001                   ((SwNoTxtFrm*)pOldSelFly->Lower())->HasAnimation() )
//STRIP001              {
//STRIP001                  GetWin()->Invalidate( pOldSelFly->Frm().SVRect() );
//STRIP001              }
//STRIP001              bUnmark = TRUE;
//STRIP001          }
//STRIP001 #ifdef USED
//STRIP001          else
//STRIP001          {
//STRIP001              SdrObject *pObj = rMrkList.GetMark( 0 )->GetObj();
//STRIP001              SwFrmFmt *pFrmFmt = FindFrmFmt( pObj );
//STRIP001              if( pFrmFmt &&
//STRIP001                  FLY_IN_CNTNT == pFrmFmt->GetAnchor().GetAnchorId() )
//STRIP001                  bUnmark = TRUE;
//STRIP001          }
//STRIP001 #endif
//STRIP001      }
//STRIP001      if ( bUnmark )
//STRIP001          pDView->UnmarkAll();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      KillPams();
//STRIP001      ClearMark();
//STRIP001  }
//STRIP001
//STRIP001  if ( pObj )
//STRIP001  {
//STRIP001      ASSERT( !bEnterGroup, "SW_ENTER_GROUP is not supported" );
//STRIP001      pDView->MarkObj( pObj, Imp()->GetPageView() );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pDView->MarkObj( rPt, MINMOVE, bAddSelect, bEnterGroup );
//STRIP001  }
//STRIP001
//STRIP001  const FASTBOOL bRet = 0 != rMrkList.GetMarkCount();
//STRIP001
//STRIP001  if ( rMrkList.GetMarkCount() > 1 )
//STRIP001  {
//STRIP001      //Ganz dumm ist es, wenn Zeichenobjekte Selektiert waren und
//STRIP001      //nun ein Fly hinzuselektiert wird.
//STRIP001      for ( USHORT i = 0; i < rMrkList.GetMarkCount(); ++i )
//STRIP001      {
//STRIP001          SdrObject *pObj = rMrkList.GetMark( i )->GetObj();
//STRIP001          BOOL bForget = pObj->IsWriterFlyFrame();
//STRIP001          if( bForget )
//STRIP001          {
//STRIP001              pDView->UnmarkAll();
//STRIP001              if ( pObj )
//STRIP001                  pDView->MarkObj( pObj, Imp()->GetPageView(), bAddSelect, bEnterGroup );
//STRIP001              else
//STRIP001                  pDView->MarkObj( rPt, MINMOVE );
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if ( bRet )
//STRIP001  {
//STRIP001      ::lcl_GrabCursor(this, pOldSelFly);
//STRIP001      if ( GetCntType() & CNT_GRF )
//STRIP001      {
//STRIP001          const SwFlyFrm *pTmp = GetFlyFromMarked( &rMrkList, this );
//STRIP001          ASSERT( pTmp, "Graphic without Fly" );
//STRIP001          if ( ((SwNoTxtFrm*)pTmp->Lower())->HasAnimation() )
//STRIP001              ((SwNoTxtFrm*)pTmp->Lower())->StopAnimation( GetOut() );
//STRIP001      }
//STRIP001  }
//STRIP001  else if ( !pOldSelFly && bHadSelection )
//STRIP001      SetCrsr( aOldPos, TRUE);
//STRIP001
//STRIP001  if( bRet || !bHadSelection )
//STRIP001      CallChgLnk();
//STRIP001
//STRIP001  // update der Statuszeile
//STRIP001  ::FrameNotify( this, bRet ? FLY_DRAG_START : FLY_DRAG_END );
//STRIP001
//STRIP001  EndAction();
//STRIP001  return bRet;
/*N*/ }

/*************************************************************************
|*
|*  sal_Bool SwFEShell::MoveAnchor( USHORT nDir )
|*
|*  Created        AMA 05/28/2002
|*  Last modify    AMA 05/30/2002
|*
|*  Description: MoveAnchor( nDir ) looked for an another Anchor for
|*  the selected drawing object (or fly frame) in the given direction.
|*  An object "as character" doesn't moves anyway.
|*  A page bounded object could move to the previous/next page with up/down,
|*  an object bounded "at paragraph" moves to the previous/next paragraph, too.
|*  An object bounded "at character" moves to the previous/next paragraph
|*  with up/down and to the previous/next character with left/right.
|*  If the anchor for at paragraph/character bounded objects has vertical or
|*  right_to_left text direction, the directions for up/down/left/right will
|*  interpreted accordingly.
|*  An object bounded "at fly" takes the center of the actual anchor and looks
|*  for the nearest fly frame in the given direction.
|*
*************************************************************************/

//STRIP001 #define LESS_X( aPt1, aPt2, bOld ) ( aPt1.X() < aPt2.X() || \
//STRIP001         ( aPt1.X() == aPt2.X() && ( aPt1.Y() < aPt2.Y() || \
//STRIP001         ( aPt1.Y() == aPt2.Y() && bOld ) ) ) )
//STRIP001 #define LESS_Y( aPt1, aPt2, bOld ) ( aPt1.Y() < aPt2.Y() || \
//STRIP001         ( aPt1.Y() == aPt2.Y() && ( aPt1.X() < aPt2.X() || \
//STRIP001         ( aPt1.X() == aPt2.X() && bOld ) ) ) )

//STRIP001 sal_Bool SwFEShell::MoveAnchor( USHORT nDir )
//STRIP001 {
//STRIP001  const SdrMarkList* pMrkList;
//STRIP001  if( !Imp()->GetDrawView() ||
//STRIP001      0 == (pMrkList = &Imp()->GetDrawView()->GetMarkList()) ||
//STRIP001         1 != pMrkList->GetMarkCount())
//STRIP001         return sal_False;
//STRIP001     SwFrm* pOld;
//STRIP001     SwFlyFrm* pFly = NULL;
//STRIP001     SdrObject *pObj = pMrkList->GetMark( 0 )->GetObj();
//STRIP001     if( pObj->IsWriterFlyFrame() )
//STRIP001     {
//STRIP001         pFly = ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm();
//STRIP001         pOld = pFly->GetAnchor();
//STRIP001     }
//STRIP001     else
//STRIP001         pOld = ((SwDrawContact*)GetUserCall(pObj))->GetAnchor();
//STRIP001     sal_Bool bRet = sal_False;
//STRIP001     if( pOld )
//STRIP001     {
//STRIP001         SwFrm* pNew = pOld;
//STRIP001         SwFmt *pFmt = ::FindFrmFmt( pObj );
//STRIP001         SwFmtAnchor aAnch( pFmt->GetAnchor() );
//STRIP001         RndStdIds nAnchorId = aAnch.GetAnchorId();
//STRIP001         if ( FLY_IN_CNTNT == nAnchorId )
//STRIP001             return sal_False;
//STRIP001 #ifdef VERTICAL_LAYOUT
//STRIP001         if( pOld->IsVertical() )
//STRIP001         {
//STRIP001             if( pOld->IsTxtFrm() )
//STRIP001             {
//STRIP001                 switch( nDir ) {
//STRIP001                     case SW_MOVE_UP: nDir = SW_MOVE_LEFT; break;
//STRIP001                     case SW_MOVE_DOWN: nDir = SW_MOVE_RIGHT; break;
//STRIP001                     case SW_MOVE_LEFT: nDir = SW_MOVE_DOWN; break;
//STRIP001                     case SW_MOVE_RIGHT: nDir = SW_MOVE_UP; break;
//STRIP001                 }
//STRIP001                 if( pOld->IsRightToLeft() )
//STRIP001                 {
//STRIP001                     if( nDir == SW_MOVE_LEFT )
//STRIP001                         nDir = SW_MOVE_RIGHT;
//STRIP001                     else if( nDir == SW_MOVE_RIGHT )
//STRIP001                         nDir = SW_MOVE_LEFT;
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001 #endif
//STRIP001         switch ( nAnchorId ) {
//STRIP001             case FLY_PAGE:
//STRIP001             {
//STRIP001                 ASSERT( pOld->IsPageFrm(), "Wrong anchor, page exspected." );
//STRIP001                 if( SW_MOVE_UP == nDir )
//STRIP001                     pNew = pOld->GetPrev();
//STRIP001                 else if( SW_MOVE_DOWN == nDir )
//STRIP001                     pNew = pOld->GetNext();
//STRIP001                 if( pNew && pNew != pOld )
//STRIP001                 {
//STRIP001                     aAnch.SetPageNum( ((SwPageFrm*)pNew)->GetPhyPageNum() );
//STRIP001                     bRet = sal_True;
//STRIP001                 }
//STRIP001                 break;
//STRIP001             }
//STRIP001             case FLY_AUTO_CNTNT:
//STRIP001             {
//STRIP001                 ASSERT( pOld->IsCntntFrm(), "Wrong anchor, page exspected." );
//STRIP001                 if( SW_MOVE_LEFT == nDir || SW_MOVE_RIGHT == nDir )
//STRIP001                 {
//STRIP001                     SwPosition *pPos = (SwPosition*)aAnch.GetCntntAnchor();
//STRIP001                     SwTxtNode* pTxtNd = ((SwTxtFrm*)pOld)->GetTxtNode();
//STRIP001                     xub_StrLen nAct = pPos->nContent.GetIndex();
//STRIP001                     if( SW_MOVE_LEFT == nDir )
//STRIP001                     {
//STRIP001                         bRet = sal_True;
//STRIP001                         if( nAct )
//STRIP001                         {
//STRIP001                             --nAct;
//STRIP001                             pPos->nContent.Assign( pTxtNd, nAct );
//STRIP001                         }
//STRIP001                         else
//STRIP001                             nDir = SW_MOVE_UP;
//STRIP001                     }
//STRIP001                     else
//STRIP001                     {
//STRIP001                         xub_StrLen nMax =
//STRIP001                             ((SwTxtFrm*)pOld)->GetTxtNode()->GetTxt().Len();
//STRIP001                         if( nAct < nMax )
//STRIP001                         {
//STRIP001                             ++nAct;
//STRIP001                             bRet = sal_True;
//STRIP001                             pPos->nContent.Assign( pTxtNd, nAct );
//STRIP001                         }
//STRIP001                         else
//STRIP001                             nDir = SW_MOVE_DOWN;
//STRIP001                     }
//STRIP001                 }
//STRIP001             } // no break!
//STRIP001             case FLY_AT_CNTNT:
//STRIP001             {
//STRIP001                 ASSERT( pOld->IsCntntFrm(), "Wrong anchor, page exspected." );
//STRIP001                 if( SW_MOVE_UP == nDir )
//STRIP001                     pNew = pOld->FindPrev();
//STRIP001                 else if( SW_MOVE_DOWN == nDir )
//STRIP001                     pNew = pOld->FindNext();
//STRIP001                 if( pNew && pNew != pOld && pNew->IsCntntFrm() )
//STRIP001                 {
//STRIP001                     SwPosition *pPos = (SwPosition*)aAnch.GetCntntAnchor();
//STRIP001                     SwTxtNode* pTxtNd = ((SwTxtFrm*)pNew)->GetTxtNode();
//STRIP001                     pPos->nNode = *pTxtNd;
//STRIP001                     xub_StrLen nTmp = 0;
//STRIP001                     if( bRet )
//STRIP001                     {
//STRIP001                         nTmp = ((SwTxtFrm*)pNew)->GetTxtNode()->GetTxt().Len();
//STRIP001                         if( nTmp )
//STRIP001                             --nTmp;
//STRIP001                     }
//STRIP001                     pPos->nContent.Assign( pTxtNd, nTmp );
//STRIP001                     bRet = sal_True;
//STRIP001                 }
//STRIP001                 else if( SW_MOVE_UP == nDir || SW_MOVE_DOWN == nDir )
//STRIP001                     bRet = sal_False;
//STRIP001                 break;
//STRIP001             }
//STRIP001             case FLY_AT_FLY:
//STRIP001             {
//STRIP001                 ASSERT( pOld->IsFlyFrm(), "Wrong anchor, fly frame exspected.");
//STRIP001                 SwPageFrm* pPage = pOld->FindPageFrm();
//STRIP001                 ASSERT( pPage, "Where's my page?" );
//STRIP001                 SwFlyFrm* pNewFly = NULL;
//STRIP001                 if( pPage->GetSortedObjs() )
//STRIP001                 {
//STRIP001                     int i;
//STRIP001                     sal_Bool bOld = sal_False;
//STRIP001                     Point aCenter( pOld->Frm().Left() + pOld->Frm().Width()/2,
//STRIP001                                    pOld->Frm().Top() + pOld->Frm().Height()/2 );
//STRIP001                     Point aBest;
//STRIP001                     for( i = 0; (USHORT)i<pPage->GetSortedObjs()->Count(); ++i )
//STRIP001                     {
//STRIP001                         SdrObject *pO = (*pPage->GetSortedObjs())[i];
//STRIP001                         if( pO->IsWriterFlyFrame() )
//STRIP001                         {
//STRIP001                             SwFlyFrm* pTmp=((SwVirtFlyDrawObj*)pO)->GetFlyFrm();
//STRIP001                             if( pTmp == pOld )
//STRIP001                                 bOld = sal_True;
//STRIP001                             else
//STRIP001                             {
//STRIP001                                 const SwFlyFrm* pCheck = pFly ? pTmp : 0;
//STRIP001                                 while( pCheck )
//STRIP001                                 {
//STRIP001                                     if( pCheck == pFly )
//STRIP001                                         break;
//STRIP001                                     const SwFrm *pNxt = pCheck->GetAnchor();
//STRIP001                                     pCheck = pNxt ? pNxt->FindFlyFrm() : NULL;
//STRIP001                                 }
//STRIP001                                 if( pCheck || pTmp->IsProtected() )
//STRIP001                                     continue;
//STRIP001                                 Point aNew( pTmp->Frm().Left() +
//STRIP001                                             pTmp->Frm().Width()/2,
//STRIP001                                             pTmp->Frm().Top() +
//STRIP001                                             pTmp->Frm().Height()/2 );
//STRIP001                                 sal_Bool bAccept = sal_False;
//STRIP001                                 switch( nDir ) {
//STRIP001                                     case SW_MOVE_RIGHT:
//STRIP001                                     {
//STRIP001                                         bAccept = LESS_X( aCenter, aNew, bOld )
//STRIP001                                              && ( !pNewFly ||
//STRIP001                                              LESS_X( aNew, aBest, sal_False ) );
//STRIP001                                         break;
//STRIP001                                     }
//STRIP001                                     case SW_MOVE_LEFT:
//STRIP001                                     {
//STRIP001                                         bAccept = LESS_X( aNew, aCenter, !bOld )
//STRIP001                                              && ( !pNewFly ||
//STRIP001                                              LESS_X( aBest, aNew, sal_True ) );
//STRIP001                                         break;
//STRIP001                                     }
//STRIP001                                     case SW_MOVE_UP:
//STRIP001                                     {
//STRIP001                                         bAccept = LESS_Y( aNew, aCenter, !bOld )
//STRIP001                                              && ( !pNewFly ||
//STRIP001                                              LESS_Y( aBest, aNew, sal_True ) );
//STRIP001                                         break;
//STRIP001                                     }
//STRIP001                                     case SW_MOVE_DOWN:
//STRIP001                                     {
//STRIP001                                         bAccept = LESS_Y( aCenter, aNew, bOld )
//STRIP001                                              && ( !pNewFly ||
//STRIP001                                              LESS_Y( aNew, aBest, sal_False ) );
//STRIP001                                         break;
//STRIP001                                     }
//STRIP001                                 }
//STRIP001                                 if( bAccept )
//STRIP001                                 {
//STRIP001                                     pNewFly = pTmp;
//STRIP001                                     aBest = aNew;
//STRIP001                                 }
//STRIP001                             }
//STRIP001                         }
//STRIP001                     }
//STRIP001                 }
//STRIP001
//STRIP001                 if( pNewFly )
//STRIP001                 {
//STRIP001                     SwPosition aPos( *pNewFly->GetFmt()->
//STRIP001                                         GetCntnt().GetCntntIdx());
//STRIP001                     aAnch.SetAnchor( &aPos );
//STRIP001                     bRet = sal_True;
//STRIP001                 }
//STRIP001                 break;
//STRIP001             }
//STRIP001         }
//STRIP001         if( bRet )
//STRIP001         {
//STRIP001             StartAllAction();
//STRIP001             pFmt->GetDoc()->SetAttr( aAnch, *pFmt );
//STRIP001             if( nAnchorId == FLY_AUTO_CNTNT && pFly && pFly->IsFlyAtCntFrm() )
//STRIP001                 ((SwFlyAtCntFrm*)pFly)->CheckCharRect();
//STRIP001             EndAllAction();
//STRIP001         }
//STRIP001     }
//STRIP001     return bRet;
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::GetSelFrmType()
|*
|*  Ersterstellung      MA 12. Jan. 93
|*  Letzte Aenderung    JP 19.03.96
|*
*************************************************************************/

const SdrMarkList* SwFEShell::_GetMarkList() const
{
    const SdrMarkList* pMarkList = NULL;
    if( Imp()->GetDrawView() != NULL )
        pMarkList = &Imp()->GetDrawView()->GetMarkList();
    return pMarkList;
}

USHORT SwFEShell::GetSelFrmType() const
{
    enum FrmType eType;

    // get marked frame list, and check if anything is selected
    const SdrMarkList* pMarkList = _GetMarkList();
    if( pMarkList == NULL  ||  pMarkList->GetMarkCount() == 0 )
        eType = FRMTYPE_NONE;
    else
    {
        // obtain marked item as fly frame; if no fly frame, it must
        // be a draw object
        const SwFlyFrm* pFly = ::binfilter::GetFlyFromMarked(pMarkList, (ViewShell*)this);
        if ( pFly != NULL )
        {
            if( pFly->IsFlyLayFrm() )
                eType = FRMTYPE_FLY_FREE;
            else if( pFly->IsFlyAtCntFrm() )
                eType = FRMTYPE_FLY_ATCNT;
            else
            {
                ASSERT( pFly->IsFlyInCntFrm(), "Neuer Rahmentyp?" );
                eType = FRMTYPE_FLY_INCNT;
            }
        }
        else
            eType = FRMTYPE_DRAWOBJ;
    }

    return eType;
}

// #108784# does the draw selection contain a control?
bool SwFEShell::IsSelContainsControl() const
{
    bool bRet = false;

    // basically, copy the mechanism from GetSelFrmType(), but call
    // CheckControl... if you get a drawing object
    const SdrMarkList* pMarkList = _GetMarkList();
    if( pMarkList != NULL  &&  pMarkList->GetMarkCount() == 1 )
    {
        // if we have one marked object, get the SdrObject and check
        // whether it contains a control
        const SdrObject* pSdrObject = pMarkList->GetMark( 0 )->GetObj();
        bRet = CheckControlLayer( pSdrObject );
    }
    return bRet;
}

/*************************************************************************
|*
|*  SwFEShell::Scroll()
|*
|*  Ersterstellung      MA 20. Dec. 94
|*  Letzte Aenderung    MA 27. Jul. 95
|*
*************************************************************************/

//STRIP001 void SwFEShell::Scroll( const Point &rPt )
//STRIP001 {
//STRIP001  const SwRect aRect( rPt, rPt );
//STRIP001  if ( IsScrollMDI( this, aRect ) &&
//STRIP001       (!Imp()->GetDrawView()->GetMarkList().GetMarkCount() ||
//STRIP001        Imp()->IsDragPossible( rPt )) )
//STRIP001  {
//STRIP001      SwSaveHdl aSave( Imp() );
//STRIP001      ScrollMDI( this, aRect, SCROLLVAL, SCROLLVAL );
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::SetDragMode()
|*
|*  Ersterstellung      MA 30. Jan. 95
|*  Letzte Aenderung    MA 30. Jan. 95
|*
*************************************************************************/

//STRIP001 void SwFEShell::SetDragMode( UINT16 eDragMode )
//STRIP001 {
//STRIP001  if ( Imp()->HasDrawView() )
//STRIP001      Imp()->GetDrawView()->SetDragMode( (SdrDragMode)eDragMode );
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::BeginDrag()
|*
|*  Ersterstellung      MS 10.06.92
|*  Letzte Aenderung    MA 13. Mar. 96
|*
*************************************************************************/

//STRIP001 long SwFEShell::BeginDrag( const Point* pPt, BOOL )
//STRIP001 {
//STRIP001  SdrView *pView = Imp()->GetDrawView();
//STRIP001  if ( pView && pView->HasMarkedObj() )
//STRIP001  {
//STRIP001      delete pChainFrom; delete pChainTo; pChainFrom = pChainTo = 0;
//STRIP001      SdrHdl* pHdl = pView->HitHandle( *pPt, *GetWin() );
//STRIP001      pView->BegDragObj( *pPt, GetWin(), pHdl );
//STRIP001      ::FrameNotify( this, FLY_DRAG );
//STRIP001      return 1;
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }
/*************************************************************************
|*
|*  SwFEShell::Drag()
|*
|*  Ersterstellung      MS 10.06.92
|*  Letzte Aenderung    MA 13. Mar. 96
|*
*************************************************************************/

//STRIP001 long SwFEShell::Drag( const Point *pPt, BOOL )
//STRIP001 {
//STRIP001  ASSERT( Imp()->HasDrawView(), "Drag without DrawView?" );
//STRIP001  if ( Imp()->GetDrawView()->IsDragObj() )
//STRIP001  {
//STRIP001      Scroll( *pPt );
//STRIP001
//STRIP001 #ifdef USED
//STRIP001 JP 31.01.96: der Wunsch ist, das Orthogonale Resizen nur vom Benutzer
//STRIP001           vorgegeben werden kann.  (beschlossen und verkuendet: ST/WP/..)
//STRIP001      //OLE wird immer proportional resized.
//STRIP001      if ( !Imp()->GetDrawView()->IsMoveOnlyDragObj( TRUE ) &&
//STRIP001           GetCntType() == CNT_OLE )
//STRIP001          Imp()->GetDrawView()->SetOrtho( TRUE );
//STRIP001 #endif
//STRIP001
//STRIP001      Imp()->GetDrawView()->MovDragObj( *pPt );
//STRIP001      Imp()->GetDrawView()->ShowDragAnchor();
//STRIP001      ::FrameNotify( this, FLY_DRAG );
//STRIP001      return 1;
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::EndDrag()
|*
|*  Ersterstellung      MS 10.06.92
|*  Letzte Aenderung    MA 13. Mar. 96
|*
*************************************************************************/

//STRIP001 long SwFEShell::EndDrag( const Point *, BOOL )
//STRIP001 {
//STRIP001  ASSERT( Imp()->HasDrawView(), "EndDrag without DrawView?" );
//STRIP001  SdrView *pView = Imp()->GetDrawView();
//STRIP001  if ( pView->IsDragObj() )
//STRIP001  {
//STRIP001      //Start-/EndActions nur an der ViewShell aufsetzen
//STRIP001      ViewShell *pSh = this;
//STRIP001      do {
//STRIP001          pSh->StartAction();
//STRIP001      } while ( this != (pSh = (ViewShell*)pSh->GetNext()) );
//STRIP001
//STRIP001      StartUndo( UNDO_START );
//STRIP001
//STRIP001      //#50778# Bug im Draging: Im StartAction wird ein HideShowXor gerufen.
//STRIP001      //Im EndDragObj() wird dies unsinniger und faelschlicherweise wieder
//STRIP001      //Rueckgaengig gemacht. Um Konsistenz herzustellen muessen wir das
//STRIP001      //Xor also wieder zur Anzeige bringen.
//STRIP001
//STRIP001         // Reanimation from the hack #50778 to fix bug #97057
//STRIP001         // May be not the best solution, but the one with lowest risc at the moment.
//STRIP001         pView->ShowShownXor( GetOut() );
//STRIP001
//STRIP001      pView->EndDragObj();
//STRIP001      // JP 18.08.95: DrawUndo-Action auf FlyFrames werden nicht gespeichert
//STRIP001      //              Die Fly aendern das Flag
//STRIP001      GetDoc()->SetNoDrawUndoObj( FALSE );
//STRIP001      ChgAnchor( 0, TRUE );
//STRIP001
//STRIP001      EndUndo( UNDO_END );
//STRIP001
//STRIP001      do {
//STRIP001          pSh->EndAction();
//STRIP001          if( pSh->IsA( TYPE( SwCrsrShell ) ) )
//STRIP001              ((SwCrsrShell*)pSh)->CallChgLnk();
//STRIP001      } while ( this != (pSh = (ViewShell*)pSh->GetNext()) );
//STRIP001
//STRIP001      GetDoc()->SetModified();
//STRIP001      ::FrameNotify( this, FLY_DRAG );
//STRIP001      return 1;
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::BreakDrag()
|*
|*  Ersterstellung      OM 02. Okt. 95
|*  Letzte Aenderung    OM 02. Okt. 95
|*
*************************************************************************/

//STRIP001 void SwFEShell::BreakDrag()
//STRIP001 {
//STRIP001  ASSERT( Imp()->HasDrawView(), "BreakDrag without DrawView?" );
//STRIP001  if ( Imp()->GetDrawView()->IsDragObj() )
//STRIP001      Imp()->GetDrawView()->BrkDragObj();
//STRIP001  SetChainMarker();
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::SelFlyGrabCrsr()
|*
|*  Beschreibung        Wenn ein Fly selektiert ist, zieht er den Crsr in
|*                      den ersten CntntFrm
|*  Ersterstellung      MA 11. Dec. 92
|*  Letzte Aenderung    MA 07. Oct. 96
|*
*************************************************************************/

//STRIP001 const SwFrmFmt* SwFEShell::SelFlyGrabCrsr()
//STRIP001 {
//STRIP001  if ( Imp()->HasDrawView() )
//STRIP001  {
//STRIP001      const SdrMarkList &rMrkList = Imp()->GetDrawView()->GetMarkList();
//STRIP001      SwFlyFrm *pFly = ::GetFlyFromMarked( &rMrkList, this );
//STRIP001
//STRIP001      if( pFly )
//STRIP001      {
//STRIP001          pFly->GetAnchor()->Calc();
//STRIP001          SwCntntFrm *pCFrm = pFly->ContainsCntnt();
//STRIP001          if ( pCFrm )
//STRIP001          {
//STRIP001              SwCntntNode *pCNode = pCFrm->GetNode();
//STRIP001              SwPaM       *pCrsr  = GetCrsr();
//STRIP001
//STRIP001              pCrsr->GetPoint()->nNode = *pCNode;
//STRIP001              pCrsr->GetPoint()->nContent.Assign( pCNode, 0 );
//STRIP001
//STRIP001              SwRect& rChrRect = (SwRect&)GetCharRect();
//STRIP001              rChrRect = pFly->Prt();
//STRIP001              rChrRect.Pos() += pFly->Frm().Pos();
//STRIP001              GetCrsrDocPos() = rChrRect.Pos();
//STRIP001          }
//STRIP001          return pFly->GetFmt();
//STRIP001      }
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }


/*************************************************************************
|*
|*  SwFEShell::SelectionToTop(), SelectionToBottom()
|*
|*  Beschreibung        Selektion nach oben/unten (Z-Order)
|*
|*  Ersterstellung      MA 05. Nov. 92
|*  Letzte Aenderung    MA 03. Jun. 96
|*
*************************************************************************/

//STRIP001 void lcl_NotifyNeighbours( const SdrMarkList *pLst )
//STRIP001 {
//STRIP001  //Die Regeln fuer die Ausweichmanoever haben sich veraendert.
//STRIP001  //1. Die Umgebung des Fly und aller innenliegenden muss benachrichtigt
//STRIP001  //   werden.
//STRIP001  //2. Der Inhalt des Rahmen selbst muss benachrichtigt werden.
//STRIP001  //3. Rahmen die dem Rahmen ausweichen bzw. wichen muessen benachrichtigt werden.
//STRIP001  //4. Auch Zeichenobjekte koennen Rahmen verdraengen
//STRIP001
//STRIP001  for( USHORT j = 0; j < pLst->GetMarkCount(); ++j )
//STRIP001  {
//STRIP001      SwPageFrm *pPage;
//STRIP001      BOOL bCheckNeighbours = FALSE;
//STRIP001      SwHoriOrient aHori;
//STRIP001      SwRect aRect;
//STRIP001      SdrObject *pO = pLst->GetMark( 0 )->GetObj();
//STRIP001      if ( pO->IsWriterFlyFrame() )
//STRIP001      {
//STRIP001          SwFlyFrm *pFly = ((SwVirtFlyDrawObj*)pO)->GetFlyFrm();
//STRIP001
//STRIP001          const SwFmtHoriOrient &rHori = pFly->GetFmt()->GetHoriOrient();
//STRIP001          aHori = rHori.GetHoriOrient();
//STRIP001          if( HORI_NONE != aHori && HORI_CENTER != aHori &&
//STRIP001              pFly->IsFlyAtCntFrm() )
//STRIP001          {
//STRIP001              bCheckNeighbours = TRUE;
//STRIP001              pFly->InvalidatePos();
//STRIP001              pFly->Frm().Pos().Y() += 1;
//STRIP001          }
//STRIP001
//STRIP001          pPage = pFly->FindPageFrm();
//STRIP001          aRect = pFly->Frm();
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          SwFrm *pAnch = ( (SwDrawContact*)GetUserCall(pO) )->GetAnchor();
//STRIP001          if( !pAnch )
//STRIP001              continue;
//STRIP001          pPage = pAnch->FindPageFrm();
//STRIP001          aRect = GetBoundRect( pO );
//STRIP001      }
//STRIP001
//STRIP001      USHORT nCount = pPage->GetSortedObjs() ? pPage->GetSortedObjs()->Count() : 0;
//STRIP001      for ( USHORT i = 0; i < nCount; ++i )
//STRIP001      {
//STRIP001          SdrObject *pO = (*pPage->GetSortedObjs())[i];
//STRIP001          if ( !pO->IsWriterFlyFrame() )
//STRIP001              continue;
//STRIP001
//STRIP001          SwVirtFlyDrawObj *pObj = (SwVirtFlyDrawObj*)pO;
//STRIP001
//STRIP001          SwFlyFrm *pAct = pObj->GetFlyFrm();
//STRIP001          SwRect aTmpCalcPnt( pAct->Prt() );
//STRIP001          aTmpCalcPnt += pAct->Frm().Pos();
//STRIP001          if ( aRect.IsOver( aTmpCalcPnt ) )
//STRIP001          {
//STRIP001              SwCntntFrm *pCnt = pAct->ContainsCntnt();
//STRIP001              while ( pCnt )
//STRIP001              {
//STRIP001                  aTmpCalcPnt = pCnt->Prt();
//STRIP001                  aTmpCalcPnt += pCnt->Frm().Pos();
//STRIP001                  if ( aRect.IsOver( aTmpCalcPnt ) )
//STRIP001                      ((SwFrm*)pCnt)->Prepare( PREP_FLY_ATTR_CHG );
//STRIP001                  pCnt = pCnt->GetNextCntntFrm();
//STRIP001              }
//STRIP001          }
//STRIP001          if ( bCheckNeighbours && pAct->IsFlyAtCntFrm() )
//STRIP001          {
//STRIP001              const SwFmtHoriOrient &rH = pAct->GetFmt()->GetHoriOrient();
//STRIP001              if ( rH.GetHoriOrient() == aHori &&
//STRIP001                   pAct->Frm().Top()    <= aRect.Bottom() &&
//STRIP001                   pAct->Frm().Bottom() >= aRect.Top() )
//STRIP001              {
//STRIP001                  pAct->InvalidatePos();
//STRIP001                  pAct->Frm().Pos().Y() += 1;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SwFEShell::SelectionToTop( BOOL bTop )
//STRIP001 {
//STRIP001  ASSERT( Imp()->HasDrawView(), "SelectionToTop without DrawView?" );
//STRIP001  const SdrMarkList &rMrkList = Imp()->GetDrawView()->GetMarkList();
//STRIP001  ASSERT( rMrkList.GetMarkCount(), "Kein Object Selektiert." );
//STRIP001
//STRIP001  SwFlyFrm *pFly = ::GetFlyFromMarked( &rMrkList, this );
//STRIP001  if ( pFly && pFly->IsFlyInCntFrm() )
//STRIP001      return;
//STRIP001
//STRIP001  StartAllAction();
//STRIP001  if ( bTop )
//STRIP001      Imp()->GetDrawView()->PutMarkedToTop();
//STRIP001  else
//STRIP001      Imp()->GetDrawView()->MovMarkedToTop();
//STRIP001  ::lcl_NotifyNeighbours( &rMrkList );
//STRIP001  GetDoc()->SetModified();
//STRIP001  EndAllAction();
//STRIP001 }

//STRIP001 void SwFEShell::SelectionToBottom( BOOL bBottom )
//STRIP001 {
//STRIP001  ASSERT( Imp()->HasDrawView(), "SelectionToBottom without DrawView?" );
//STRIP001  const SdrMarkList &rMrkList = Imp()->GetDrawView()->GetMarkList();
//STRIP001  ASSERT( rMrkList.GetMarkCount(), "Kein Object Selektiert." );
//STRIP001
//STRIP001  SwFlyFrm *pFly = ::GetFlyFromMarked( &rMrkList, this );
//STRIP001  if ( pFly && pFly->IsFlyInCntFrm() )
//STRIP001      return;
//STRIP001
//STRIP001  StartAllAction();
//STRIP001  if ( bBottom )
//STRIP001      Imp()->GetDrawView()->PutMarkedToBtm();
//STRIP001  else
//STRIP001      Imp()->GetDrawView()->MovMarkedToBtm();
//STRIP001  ::lcl_NotifyNeighbours( &rMrkList );
//STRIP001  GetDoc()->SetModified();
//STRIP001  EndAllAction();
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::GetLayerId()
|*
|*  Beschreibung        Objekt ueber/unter dem Dokument?
|*                      2 Controls, 1 Heaven, 0 Hell, -1 Uneindeutig
|*  Ersterstellung      MA 20. Dec. 94
|*  Letzte Aenderung    MA 20. Dec. 94
|*
*************************************************************************/

//STRIP001 short SwFEShell::GetLayerId() const
//STRIP001 {
//STRIP001  short nRet = SHRT_MAX;
//STRIP001  if ( Imp()->HasDrawView() )
//STRIP001  {
//STRIP001      const SdrMarkList &rMrkList = Imp()->GetDrawView()->GetMarkList();
//STRIP001      for ( USHORT i = 0; i < rMrkList.GetMarkCount(); ++i )
//STRIP001      {
//STRIP001          const SdrObject *pObj = rMrkList.GetMark( i )->GetObj();
//STRIP001          if ( nRet == SHRT_MAX )
//STRIP001              nRet = pObj->GetLayer();
//STRIP001          else if ( nRet != pObj->GetLayer() )
//STRIP001          {
//STRIP001              nRet = -1;
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if ( nRet == SHRT_MAX )
//STRIP001      nRet = -1;
//STRIP001  return nRet;
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::SelectionToHeaven(), SelectionToHell()
|*
|*  Beschreibung        Objekt ueber/unter dem Dokument
|*  Ersterstellung      MA 20. Dec. 94
|*  Letzte Aenderung    AMA 04. Jun. 98
|*
*************************************************************************/
// OD 25.06.2003 #108784#
// Note: only visible objects can be marked. Thus, objects with invisible
//       layer IDs have not to be considered.
//       If <SwFEShell> exists, layout exists!!
//STRIP001 void SwFEShell::ChangeOpaque( SdrLayerID nLayerId )
//STRIP001 {
//STRIP001  if ( Imp()->HasDrawView() )
//STRIP001  {
//STRIP001      const SdrMarkList &rMrkList = Imp()->GetDrawView()->GetMarkList();
//STRIP001         // OD 25.06.2003 #108784# - correct type of <nControls>
//STRIP001         const SdrLayerID nControls = GetDoc()->GetControlsId();
//STRIP001      for ( USHORT i = 0; i < rMrkList.GetMarkCount(); ++i )
//STRIP001      {
//STRIP001          SdrObject *pObj = rMrkList.GetMark( i )->GetObj();
//STRIP001          if ( pObj->GetLayer() != nLayerId && pObj->GetLayer() != nControls )
//STRIP001          {
//STRIP001              pObj->SetLayer( nLayerId );
//STRIP001              InvalidateWindows( SwRect( pObj->GetBoundRect() ) );
//STRIP001              if ( pObj->IsWriterFlyFrame() )
//STRIP001              {
//STRIP001                  SwFmt *pFmt = ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm()->GetFmt();
//STRIP001                  SvxOpaqueItem aOpa( pFmt->GetOpaque() );
//STRIP001                  aOpa.SetValue(  nLayerId == GetDoc()->GetHellId() );
//STRIP001                  pFmt->SetAttr( aOpa );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      GetDoc()->SetModified();
//STRIP001  }
//STRIP001 }

//STRIP001 void SwFEShell::SelectionToHeaven()
//STRIP001 {
//STRIP001  ChangeOpaque( GetDoc()->GetHeavenId() );
//STRIP001 }

//STRIP001 void SwFEShell::SelectionToHell()
//STRIP001 {
//STRIP001  ChangeOpaque( GetDoc()->GetHellId() );
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::IsObjSelected(), IsFrmSelected()
|*
|*  Ersterstellung      MA 16. Nov. 92
|*  Letzte Aenderung    MA 17. Jan. 95
|*
*************************************************************************/

/*N*/ USHORT SwFEShell::IsObjSelected() const
/*N*/ {
/*N*/   if ( IsFrmSelected() || !Imp()->HasDrawView() )
/*N*/       return 0;
/*N*/   else
/*N*/       return USHORT( Imp()->GetDrawView()->GetMarkList().GetMarkCount() );
/*N*/ }

/*N*/ BOOL SwFEShell::IsFrmSelected() const
/*N*/ {
/*N*/   if ( !Imp()->HasDrawView() )
/*N*/       return FALSE;
/*N*/   else
/*N*/       return 0 != ::binfilter::GetFlyFromMarked( &Imp()->GetDrawView()->GetMarkList(),
/*N*/                                       (ViewShell*)this );
/*N*/ }

//STRIP001 #ifdef ACCESSIBLE_LAYOUT
//STRIP001 sal_Bool SwFEShell::IsObjSelected( const SdrObject& rObj ) const
//STRIP001 {
//STRIP001  if ( IsFrmSelected() || !Imp()->HasDrawView() )
//STRIP001      return sal_False;
//STRIP001  else
//STRIP001      return Imp()->GetDrawView()
//STRIP001                  ->IsObjMarked( const_cast< SdrObject * >( &rObj ) );
//STRIP001 }
//STRIP001 #endif

//STRIP001 Rectangle *SwFEShell::IsAnchorAtPos( const Point &rPt ) const
//STRIP001 {
//STRIP001  if ( !Imp()->HasDrawView() )
//STRIP001      return 0;
//STRIP001  else
//STRIP001      return Imp()->GetDrawView()->IsAnchorAtPos( rPt );
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::EndTextEdit()
|*
|*  Ersterstellung      MA 19. Feb. 96
|*  Letzte Aenderung    MA 19. Feb. 96
|*
*************************************************************************/

//STRIP001 void SwFEShell::EndTextEdit()
//STRIP001 {
//STRIP001  //Beenden des TextEditModus. Wenn gewuenscht (default wenn das Objekt
//STRIP001  //keinen Text mehr enthaelt und keine Attribute traegt) wird das
//STRIP001  //Objekt gel”scht. Alle anderen markierten Objekte bleiben erhalten.
//STRIP001
//STRIP001  ASSERT( Imp()->HasDrawView() && Imp()->GetDrawView()->IsTextEdit(),
//STRIP001          "EndTextEdit an no Object" );
//STRIP001
//STRIP001  StartAllAction();
//STRIP001  SdrView *pView = Imp()->GetDrawView();
//STRIP001  SdrObject *pObj = pView->GetTextEditObject();
//STRIP001  SdrObjUserCall* pUserCall;
//STRIP001  if( 0 != ( pUserCall = GetUserCall(pObj) ) )
//STRIP001  {
//STRIP001         SdrObject *pTmp = ((SwContact*)pUserCall)->GetMaster();
//STRIP001         if( !pTmp )
//STRIP001             pTmp = pObj;
//STRIP001         pUserCall->Changed( *pTmp, SDRUSERCALL_RESIZE, pTmp->GetBoundRect() );
//STRIP001  }
//STRIP001  if ( !pObj->GetUpGroup() )
//STRIP001  {
//STRIP001      if ( SDRENDTEXTEDIT_SHOULDBEDELETED == pView->EndTextEdit( TRUE ) )
//STRIP001      {
//STRIP001          if ( pView->GetMarkList().GetMarkCount() > 1 )
//STRIP001          {
//STRIP001              {
//STRIP001                  SdrMarkList aSave( pView->GetMarkList() );
//STRIP001                  aSave.DeleteMark( aSave.FindObject( pObj ) );
//STRIP001                  if ( aSave.GetMarkCount() )
//STRIP001                  {
//STRIP001                      pView->UnmarkAll();
//STRIP001                      pView->MarkObj( pObj, Imp()->GetPageView() );
//STRIP001                  }
//STRIP001                  DelSelectedObj();
//STRIP001                  if ( aSave.GetMarkCount() )
//STRIP001                  {
//STRIP001                      for ( USHORT i = 0; i < aSave.GetMarkCount(); ++i )
//STRIP001                          pView->MarkObj( aSave.GetMark( i )->GetObj(),
//STRIP001                                          Imp()->GetPageView() );
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001              DelSelectedObj();
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001      pView->EndTextEdit();
//STRIP001  EndAllAction();
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::IsInsideSelectedObj()
|*
|*  Ersterstellung      MA 16. Nov. 92
|*  Letzte Aenderung    MA 08. Nov. 96
|*
*************************************************************************/

//STRIP001 int SwFEShell::IsInsideSelectedObj( const Point &rPt )
//STRIP001 {
//STRIP001  if( Imp()->HasDrawView() )
//STRIP001  {
//STRIP001      SwDrawView *pDView = Imp()->GetDrawView();
//STRIP001
//STRIP001      if( pDView->GetMarkList().GetMarkCount() &&
//STRIP001          pDView->IsMarkedObjHit( rPt ) )
//STRIP001      {
//STRIP001          return SDRHIT_OBJECT;
//STRIP001      }
//STRIP001  }
//STRIP001  return SDRHIT_NONE;
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::IsObjSelectable()
|*
|*  Ersterstellung      MA 16. Nov. 92
|*  Letzte Aenderung    MA 02. Feb. 95
|*
*************************************************************************/

//STRIP001 int SwFEShell::IsObjSelectable( const Point& rPt )
//STRIP001 {
//STRIP001  SET_CURR_SHELL(this);
//STRIP001 #ifdef OLD
//STRIP001  if( Imp()->HasDrawView() )
//STRIP001      return Imp()->GetDrawView()->PickSomething( rPt, MINMOVE );
//STRIP001  return 0;
//STRIP001 #else
//STRIP001  SwDrawView *pDView = Imp()->GetDrawView();
//STRIP001  BOOL bRet = FALSE;
//STRIP001  if( pDView )
//STRIP001  {
//STRIP001      SdrObject* pObj;
//STRIP001      SdrPageView* pPV;
//STRIP001      USHORT nOld = pDView->GetHitTolerancePixel();
//STRIP001      pDView->SetHitTolerancePixel( pDView->GetMarkHdlSizePixel()/2 );
//STRIP001
//STRIP001      bRet = pDView->PickObj( rPt, pObj, pPV, SDRSEARCH_PICKMARKABLE );
//STRIP001      pDView->SetHitTolerancePixel( nOld );
//STRIP001  }
//STRIP001  return bRet ? 1 : 0;
//STRIP001 #endif
//STRIP001 }

// #107513#
// Test if there is a draw object at that position and if it should be selected.
// The 'should' is aimed at Writer text fly frames which may be in front of
// the draw object.
//STRIP001 sal_Bool SwFEShell::ShouldObjectBeSelected(const Point& rPt)
//STRIP001 {
//STRIP001  SET_CURR_SHELL(this);
//STRIP001  SwDrawView *pDrawView = Imp()->GetDrawView();
//STRIP001  sal_Bool bRet(sal_False);
//STRIP001
//STRIP001  if(pDrawView)
//STRIP001  {
//STRIP001      SdrObject* pObj;
//STRIP001      SdrPageView* pPV;
//STRIP001      sal_uInt16 nOld(pDrawView->GetHitTolerancePixel());
//STRIP001
//STRIP001      pDrawView->SetHitTolerancePixel(pDrawView->GetMarkHdlSizePixel()/2);
//STRIP001      bRet = pDrawView->PickObj(rPt, pObj, pPV, SDRSEARCH_PICKMARKABLE);
//STRIP001      pDrawView->SetHitTolerancePixel(nOld);
//STRIP001
//STRIP001      if(bRet && pObj)
//STRIP001      {
//STRIP001          SdrPage* pPage = GetDoc()->GetDrawModel()->GetPage(0);
//STRIP001
//STRIP001          for(sal_uInt32 a(pObj->GetOrdNumDirect() + 1); bRet && a < pPage->GetObjCount(); a++)
//STRIP001          {
//STRIP001              SdrObject *pCandidate = pPage->GetObj(a);
//STRIP001
//STRIP001              if(pCandidate->IsWriterFlyFrame() && ((SwVirtFlyDrawObj*)pCandidate)->GetBoundRect().IsInside(rPt))
//STRIP001              {
//STRIP001                  bRet = sal_False;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::GotoObj()
|*
|*  Beschreibung        Wenn ein Obj selektiert ist, gehen wir von dessen
|*      TopLeft aus, andernfalls von der Mitte des aktuellen CharRects.
|*  Ersterstellung      MA 01. Jun. 95
|*  Letzte Aenderung    MA 30. Apr. 96
|*
*************************************************************************/
/* -----------------23.09.98 10:29-------------------
 * Beinhaltet das Objekt ein Control oder Gruppen,
 * die nur aus Controls bestehen
 * --------------------------------------------------*/
//STRIP001 FASTBOOL lcl_IsControlGroup( const SdrObject *pObj )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  if(pObj->ISA(SdrUnoObj))
//STRIP001      bRet = TRUE;
//STRIP001  else if( pObj->ISA( SdrObjGroup ) )
//STRIP001  {
//STRIP001      bRet = TRUE;
//STRIP001      const SdrObjList *pLst = ((SdrObjGroup*)pObj)->GetSubList();
//STRIP001      for ( USHORT i = 0; i < pLst->GetObjCount(); ++i )
//STRIP001          if( !::lcl_IsControlGroup( pLst->GetObj( i ) ) )
//STRIP001              return FALSE;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SwFEShell::GotoObj( BOOL bNext, GotoObjType eType )
//STRIP001 {
//STRIP001  if( !Imp()->HasDrawView() )
//STRIP001      return FALSE;
//STRIP001  else
//STRIP001  {
//STRIP001      const SdrObject *pBest  = 0,
//STRIP001                      *pTop   = 0;
//STRIP001
//STRIP001      const long nTmp = bNext ? LONG_MAX : 0;
//STRIP001      Point aBestPos( nTmp, nTmp );
//STRIP001      Point aTopPos(  nTmp, nTmp );
//STRIP001      Point aCurPos;
//STRIP001      Point aPos;
//STRIP001      BOOL  bRet = FALSE;
//STRIP001         BOOL bNoDraw = 0 == (DRAW_ANY & eType);
//STRIP001         BOOL bNoFly = 0 == (FLY_ANY & eType);
//STRIP001
//STRIP001         if( !bNoFly && bNoDraw )
//STRIP001         {
//STRIP001             SwFlyFrm *pFly = GetCurrFrm( FALSE )->FindFlyFrm();
//STRIP001             if( pFly )
//STRIP001                 pBest = pFly->GetVirtDrawObj();
//STRIP001         }
//STRIP001      const SdrMarkList &rMrkList = Imp()->GetDrawView()->GetMarkList();
//STRIP001         SdrPageView* pPV = Imp()->GetDrawView()->GetPageViewPvNum( 0 );
//STRIP001
//STRIP001         if( !pBest || rMrkList.GetMarkCount() == 1 )
//STRIP001         {
//STRIP001             // Ausgangspunkt bestimmen.
//STRIP001             SdrObjList* pList = NULL;
//STRIP001             if ( rMrkList.GetMarkCount() )
//STRIP001             {
//STRIP001                 const SdrObject* pStartObj = rMrkList.GetMark(0)->GetObj();
//STRIP001                 if( pStartObj->IsWriterFlyFrame() )
//STRIP001                     aPos = ((SwVirtFlyDrawObj*)pStartObj)->GetFlyFrm()->Frm().Pos();
//STRIP001                 else
//STRIP001                     aPos = pStartObj->GetSnapRect().TopLeft();
//STRIP001
//STRIP001                 // If an object inside a group is selected, we want to
//STRIP001                 // iterate over the group members.
//STRIP001                 if ( ! pStartObj->GetUserCall() )
//STRIP001                     pList = pStartObj->GetObjList();
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 // If no object is selected, we check if we just entered a group.
//STRIP001                 // In this case we want to iterate over the group members.
//STRIP001                 aPos = GetCharRect().Center();
//STRIP001                 const SdrObject* pStartObj = pPV ? pPV->GetAktGroup() : 0;
//STRIP001                 if ( pStartObj && pStartObj->ISA( SdrObjGroup ) )
//STRIP001                     pList = pStartObj->GetSubList();
//STRIP001             }
//STRIP001
//STRIP001             if ( ! pList )
//STRIP001             {
//STRIP001                 // Here we are if
//STRIP001                 // A  No object has been selected and no group has been entered or
//STRIP001                 // B  An object has been selected and it is not inside a group
//STRIP001                 pList = GetDoc()->GetDrawModel()->GetPage( 0 );
//STRIP001             }
//STRIP001
//STRIP001
//STRIP001             ASSERT( pList, "No object list to iterate" )
//STRIP001
//STRIP001             const ULONG nObjs = pList->GetObjCount();
//STRIP001             for( ULONG nObj = 0; nObj < nObjs; ++nObj )
//STRIP001             {
//STRIP001                 SdrObject* pObj = pList->GetObj( nObj );
//STRIP001                 BOOL bFlyFrm = pObj->IsWriterFlyFrame();
//STRIP001                 if( ( bNoFly && bFlyFrm ) ||
//STRIP001                     ( bNoDraw && !bFlyFrm ) ||
//STRIP001                     ( eType == DRAW_SIMPLE && lcl_IsControlGroup( pObj ) ) ||
//STRIP001                     ( eType == DRAW_CONTROL && !lcl_IsControlGroup( pObj ) ) ||
//STRIP001                     ( pPV && ! pPV->GetView().IsObjMarkable( pObj, pPV ) ) )
//STRIP001                     continue;
//STRIP001                 if( bFlyFrm )
//STRIP001                 {
//STRIP001                     SwVirtFlyDrawObj *pO = (SwVirtFlyDrawObj*)pObj;
//STRIP001                     SwFlyFrm *pFly = pO->GetFlyFrm();
//STRIP001                     if( FLY_ANY != ( FLY_ANY & eType ) )
//STRIP001                     {
//STRIP001                         switch ( eType )
//STRIP001                         {
//STRIP001                             case FLY_FRM:
//STRIP001                                 if ( pFly->Lower() && pFly->Lower()->IsNoTxtFrm() )
//STRIP001                                     continue;
//STRIP001                             break;
//STRIP001                             case FLY_GRF:
//STRIP001                                 if ( pFly->Lower() &&
//STRIP001                                     (pFly->Lower()->IsLayoutFrm() ||
//STRIP001                                     !((SwCntntFrm*)pFly->Lower())->GetNode()->GetGrfNode()))
//STRIP001                                     continue;
//STRIP001                             break;
//STRIP001                             case FLY_OLE:
//STRIP001                                 if ( pFly->Lower() &&
//STRIP001                                     (pFly->Lower()->IsLayoutFrm() ||
//STRIP001                                     !((SwCntntFrm*)pFly->Lower())->GetNode()->GetOLENode()))
//STRIP001                                     continue;
//STRIP001                             break;
//STRIP001                         }
//STRIP001                     }
//STRIP001                     aCurPos = pFly->Frm().Pos();
//STRIP001                 }
//STRIP001                 else
//STRIP001                     aCurPos = pObj->GetBoundRect().TopLeft();
//STRIP001
//STRIP001                 // Sonderfall wenn ein anderes Obj auf selber Y steht.
//STRIP001                 if( aCurPos != aPos &&          // nur wenn ich es nicht selber bin
//STRIP001                     aCurPos.Y() == aPos.Y() &&  // ist die Y Position gleich
//STRIP001                     (bNext? (aCurPos.X() > aPos.X()) :  // liegt neben mir
//STRIP001                             (aCurPos.X() < aPos.X())) ) // " reverse
//STRIP001                 {
//STRIP001                     aBestPos = Point( nTmp, nTmp );
//STRIP001                     for( ULONG i = 0; i < nObjs; ++i )
//STRIP001                     {
//STRIP001                         SdrObject *pObj = pList->GetObj( i );
//STRIP001                         bFlyFrm = pObj->IsWriterFlyFrame();
//STRIP001                         if( ( bNoFly && bFlyFrm ) || ( bNoDraw && !bFlyFrm ) )
//STRIP001                             continue;
//STRIP001                         if( bFlyFrm )
//STRIP001                         {
//STRIP001                             SwVirtFlyDrawObj *pO = (SwVirtFlyDrawObj*)pObj;
//STRIP001                             aCurPos = pO->GetFlyFrm()->Frm().Pos();
//STRIP001                         }
//STRIP001                         else
//STRIP001                             aCurPos = pObj->GetBoundRect().TopLeft();
//STRIP001
//STRIP001                         if( aCurPos != aPos && aCurPos.Y() == aPos.Y() &&
//STRIP001                             (bNext? (aCurPos.X() > aPos.X()) :  // liegt neben mir
//STRIP001                                     (aCurPos.X() < aPos.X())) &&    // " reverse
//STRIP001                             (bNext? (aCurPos.X() < aBestPos.X()) :  // besser als Beste
//STRIP001                                     (aCurPos.X() > aBestPos.X())) ) // " reverse
//STRIP001                         {
//STRIP001                             aBestPos = aCurPos;
//STRIP001                             pBest = pObj;
//STRIP001                         }
//STRIP001                     }
//STRIP001                     break;
//STRIP001                 }
//STRIP001
//STRIP001                 if( (bNext? (aPos.Y() < aCurPos.Y()) :          // nur unter mir
//STRIP001                             (aPos.Y() > aCurPos.Y())) &&        // " reverse
//STRIP001                     (bNext? (aBestPos.Y() > aCurPos.Y()) :      // naeher drunter
//STRIP001                             (aBestPos.Y() < aCurPos.Y())) ||    // " reverse
//STRIP001                             (aBestPos.Y() == aCurPos.Y() &&
//STRIP001                     (bNext? (aBestPos.X() > aCurPos.X()) :      // weiter links
//STRIP001                             (aBestPos.X() < aCurPos.X()))))     // " reverse
//STRIP001
//STRIP001                 {
//STRIP001                     aBestPos = aCurPos;
//STRIP001                     pBest = pObj;
//STRIP001                 }
//STRIP001
//STRIP001                 if( (bNext? (aTopPos.Y() > aCurPos.Y()) :       // hoeher als Beste
//STRIP001                             (aTopPos.Y() < aCurPos.Y())) ||     // " reverse
//STRIP001                             (aTopPos.Y() == aCurPos.Y() &&
//STRIP001                     (bNext? (aTopPos.X() > aCurPos.X()) :       // weiter links
//STRIP001                             (aTopPos.X() < aCurPos.X()))))      // " reverse
//STRIP001                 {
//STRIP001                     aTopPos = aCurPos;
//STRIP001                     pTop = pObj;
//STRIP001                 }
//STRIP001             }
//STRIP001             // leider nichts gefunden
//STRIP001             if( (bNext? (aBestPos.X() == LONG_MAX) : (aBestPos.X() == 0)) )
//STRIP001                 pBest = pTop;
//STRIP001         }
//STRIP001
//STRIP001      if( pBest )
//STRIP001      {
//STRIP001             BOOL bFlyFrm = pBest->IsWriterFlyFrame();
//STRIP001             if( bFlyFrm )
//STRIP001             {
//STRIP001                 SwVirtFlyDrawObj *pO = (SwVirtFlyDrawObj*)pBest;
//STRIP001                 const SwRect& rFrm = pO->GetFlyFrm()->Frm();
//STRIP001                 SelectObj( rFrm.Pos(), 0, (SdrObject*)pBest );
//STRIP001                 if( !ActionPend() )
//STRIP001                     MakeVisible( rFrm );
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 SelectObj( Point(), 0, (SdrObject*)pBest );
//STRIP001                 if( !ActionPend() )
//STRIP001                     MakeVisible( pBest->GetBoundRect() );
//STRIP001             }
//STRIP001          CallChgLnk();
//STRIP001          bRet = TRUE;
//STRIP001      }
//STRIP001      return bRet;
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::ControlCount(), GotoControl()
|*
|*  Ersterstellung      MA 22. Jul. 96
|*  Letzte Aenderung    MA 22. Jul. 96
|*
*************************************************************************/

//STRIP001 ULONG SwFEShell::ControlCount() const
//STRIP001 {
//STRIP001  INT32 nRet = 0;
//STRIP001  if ( Imp()->HasDrawView() )
//STRIP001  {
//STRIP001      SdrPage* pPage = GetDoc()->GetDrawModel()->GetPage( 0 );
//STRIP001      const ULONG nObjs = pPage->GetObjCount();
//STRIP001      for( ULONG nObj = 0; nObj < nObjs; ++nObj )
//STRIP001      {
//STRIP001          if ( pPage->GetObj( nObj )->ISA( SdrUnoObj ) )
//STRIP001              ++nRet;
//STRIP001      }
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

//STRIP001 BOOL SwFEShell::GotoControl( ULONG nIndex )
//STRIP001 {
//STRIP001  if ( Imp()->HasDrawView() )
//STRIP001  {
//STRIP001      ULONG nIdx = 0;
//STRIP001      SdrPage* pPage = GetDoc()->GetDrawModel()->GetPage( 0 );
//STRIP001      const ULONG nObjs = pPage->GetObjCount();
//STRIP001      for( ULONG nObj = 0; nObj < nObjs; ++nObj )
//STRIP001      {
//STRIP001          SdrObject *pObj = pPage->GetObj( nObj );
//STRIP001          if ( pObj->ISA( SdrUnoObj ) )
//STRIP001          {
//STRIP001              if ( nIdx == nIndex )
//STRIP001              {
//STRIP001                     SelectObj( Point(), 0, pObj );
//STRIP001                  if( !ActionPend() )
//STRIP001                      MakeVisible( pObj->GetBoundRect() );
//STRIP001                  CallChgLnk();
//STRIP001                  return TRUE;
//STRIP001              }
//STRIP001              ++nIdx;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::BeginCreate()
|*
|*  Ersterstellung      MA 20. Dec. 94
|*  Letzte Aenderung    MA 21. Mar. 95
|*
*************************************************************************/

//STRIP001 BOOL SwFEShell::BeginCreate( UINT16 eSdrObjectKind, const Point &rPos )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001
//STRIP001  if ( !Imp()->HasDrawView() )
//STRIP001      Imp()->MakeDrawView();
//STRIP001
//STRIP001  if ( GetPageNumber( rPos ) )
//STRIP001  {
//STRIP001      Imp()->GetDrawView()->SetCurrentObj( eSdrObjectKind );
//STRIP001      if ( eSdrObjectKind == OBJ_CAPTION )
//STRIP001          bRet = Imp()->GetDrawView()->BegCreateCaptionObj(
//STRIP001                      rPos, Size( lMinBorder - MINFLY, lMinBorder - MINFLY ),
//STRIP001                      GetOut() );
//STRIP001      else
//STRIP001          bRet = Imp()->GetDrawView()->BegCreateObj( rPos, GetOut() );
//STRIP001  }
//STRIP001  if ( bRet )
//STRIP001     {
//STRIP001         ::FrameNotify( this, FLY_DRAG_START );
//STRIP001     }
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 BOOL SwFEShell::BeginCreate( UINT16 eSdrObjectKind, UINT32 eObjInventor,
//STRIP001                           const Point &rPos )
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001
//STRIP001  if ( !Imp()->HasDrawView() )
//STRIP001      Imp()->MakeDrawView();
//STRIP001
//STRIP001  if ( GetPageNumber( rPos ) )
//STRIP001  {
//STRIP001      Imp()->GetDrawView()->SetCurrentObj( eSdrObjectKind, eObjInventor );
//STRIP001      bRet = Imp()->GetDrawView()->BegCreateObj( rPos, GetOut() );
//STRIP001  }
//STRIP001  if ( bRet )
//STRIP001      ::FrameNotify( this, FLY_DRAG_START );
//STRIP001  return bRet;
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::MoveCreate()
|*
|*  Ersterstellung      MA 20. Dec. 94
|*  Letzte Aenderung    MA 24. Jan. 95
|*
*************************************************************************/

//STRIP001 void SwFEShell::MoveCreate( const Point &rPos )
//STRIP001 {
//STRIP001  ASSERT( Imp()->HasDrawView(), "MoveCreate without DrawView?" );
//STRIP001  if ( GetPageNumber( rPos ) )
//STRIP001  {
//STRIP001      Scroll( rPos );
//STRIP001      Imp()->GetDrawView()->MovCreateObj( rPos );
//STRIP001      ::FrameNotify( this, FLY_DRAG );
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::EndCreate(), ImpEndCreate()
|*
|*  Ersterstellung      MA 20. Dec. 94
|*  Letzte Aenderung    MA 14. Oct. 96
|*
*************************************************************************/

//STRIP001 BOOL SwFEShell::EndCreate( UINT16 eSdrCreateCmd )
//STRIP001 {
//STRIP001  // JP 18.08.95: Damit das Undo-Object aus der DrawEngine nicht bei uns
//STRIP001  // gespeichert wird, (wir erzeugen ein eigenes Undo-Object!) hier kurz
//STRIP001  // das Undo abschalten
//STRIP001  ASSERT( Imp()->HasDrawView(), "EndCreate without DrawView?" );
//STRIP001  if( !Imp()->GetDrawView()->IsGroupEntered() )
//STRIP001      GetDoc()->SetNoDrawUndoObj( TRUE );
//STRIP001  FASTBOOL bCreate = Imp()->GetDrawView()->EndCreateObj(
//STRIP001                                  SdrCreateCmd( eSdrCreateCmd ) );
//STRIP001  GetDoc()->SetNoDrawUndoObj( FALSE );
//STRIP001
//STRIP001  if ( !bCreate )
//STRIP001  {
//STRIP001      ::FrameNotify( this, FLY_DRAG_END );
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  if ( (SdrCreateCmd)eSdrCreateCmd == SDRCREATE_NEXTPOINT )
//STRIP001  {
//STRIP001      ::FrameNotify( this, FLY_DRAG );
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  return ImpEndCreate();
//STRIP001 }


//STRIP001 BOOL SwFEShell::ImpEndCreate()
//STRIP001 {
//STRIP001  ASSERT( Imp()->GetDrawView()->GetMarkList().GetMarkCount() == 1,
//STRIP001          "Neues Object nicht selektiert." );
//STRIP001
//STRIP001  SdrObject& rSdrObj = *Imp()->GetDrawView()->GetMarkList().GetMark(0)->GetObj();
//STRIP001
//STRIP001  if( rSdrObj.GetSnapRect().IsEmpty() )
//STRIP001  {
//STRIP001      //JP 10.04.95: das Object vergessen wir lieber, fuerht nur
//STRIP001      //              zu Problemen
//STRIP001      Imp()->GetDrawView()->DeleteMarked();
//STRIP001      Imp()->GetDrawView()->UnmarkAll();
//STRIP001      ::FrameNotify( this, FLY_DRAG_END );
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  if( rSdrObj.GetUpGroup() )
//STRIP001  {
//STRIP001      Point aTmpPos( rSdrObj.GetRelativePos() + rSdrObj.GetAnchorPos() );
//STRIP001      Point aNewAnchor( rSdrObj.GetUpGroup()->GetAnchorPos() );
//STRIP001      rSdrObj.NbcSetRelativePos( aTmpPos - aNewAnchor );
//STRIP001      rSdrObj.NbcSetAnchorPos( aNewAnchor );
//STRIP001      // Imp()->GetDrawView()->UnmarkAll();
//STRIP001      ::FrameNotify( this, FLY_DRAG );
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001
//STRIP001  StartAllAction();
//STRIP001
//STRIP001  Imp()->GetDrawView()->UnmarkAll();
//STRIP001
//STRIP001  SwPaM* pCrsr = GetCrsr();
//STRIP001
//STRIP001  const Rectangle &rBound = rSdrObj.GetSnapRect();
//STRIP001     Point aPt( rBound.TopRight() );
//STRIP001
//STRIP001  //Fremde Identifier sollen in den Default laufen.
//STRIP001  //Ueberschneidungen sind moeglich!!
//STRIP001  UINT16 nIdent = SdrInventor == rSdrObj.GetObjInventor()
//STRIP001                      ? rSdrObj.GetObjIdentifier()
//STRIP001                      : 0xFFFF;
//STRIP001
//STRIP001  //Default fuer Controls ist Zeichengebunden, Absatzgebunden sonst.
//STRIP001  SwFmtAnchor aAnch;
//STRIP001  const SwFrm *pAnch = 0;
//STRIP001  FASTBOOL bCharBound = FALSE;
//STRIP001  if( rSdrObj.ISA( SdrUnoObj ) )
//STRIP001  {
//STRIP001      SwPosition aPos( GetDoc()->GetNodes() );
//STRIP001      SwCrsrMoveState aState( MV_SETONLYTEXT );
//STRIP001      Point aPoint( aPt.X(), aPt.Y() + rBound.GetHeight()/2 );
//STRIP001      GetDoc()->GetRootFrm()->GetCrsrOfst( &aPos, aPoint, &aState );
//STRIP001
//STRIP001      //JP 22.01.99: Zeichenbindung ist im ReadnOnly-Inhalt nicht erlaubt
//STRIP001      if( !aPos.nNode.GetNode().IsProtect() )
//STRIP001      {
//STRIP001          pAnch = aPos.nNode.GetNode().GetCntntNode()->GetFrm( &aPoint, &aPos );
//STRIP001          SwRect aTmp;
//STRIP001          pAnch->GetCharRect( aTmp, aPos );
//STRIP001
//STRIP001          //Der Crsr darf nicht zu weit entfernt sein.
//STRIP001          bCharBound = TRUE;
//STRIP001          Rectangle aRect( aTmp.SVRect() );
//STRIP001          aRect.Left()  -= MM50*2;
//STRIP001          aRect.Top()   -= MM50*2;
//STRIP001          aRect.Right() += MM50*2;
//STRIP001          aRect.Bottom()+= MM50*2;
//STRIP001
//STRIP001          if( !aRect.IsOver( rBound ) && !::binfilter::GetHtmlMode( GetDoc()->GetDocShell() ))
//STRIP001              bCharBound = FALSE;
//STRIP001
//STRIP001              //Bindung in Kopf-/Fusszeilen ist ebenfalls nicht erlaubt.
//STRIP001          if( bCharBound )
//STRIP001              bCharBound = !GetDoc()->IsInHeaderFooter( aPos.nNode );
//STRIP001
//STRIP001          if( bCharBound )
//STRIP001          {
//STRIP001              aAnch.SetType( FLY_IN_CNTNT );
//STRIP001              aAnch.SetAnchor( &aPos );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( !bCharBound )
//STRIP001  {
//STRIP001         // OD 16.05.2003 #108784# - allow native drawing objects in header/footer.
//STRIP001         // Thus, set <bBodyOnly> to <false> for these objects using value
//STRIP001         // of <nIdent> - value <0xFFFF> indicates control objects, which aren't
//STRIP001         // allowed in header/footer.
//STRIP001         //bool bBodyOnly = OBJ_NONE != nIdent;
//STRIP001         bool bBodyOnly = 0xFFFF == nIdent;
//STRIP001         bool bAtPage = false;
//STRIP001         const SwFrm* pPage = 0;
//STRIP001      SwCrsrMoveState aState( MV_SETONLYTEXT );
//STRIP001      Point aPoint( aPt );
//STRIP001      SwPosition aPos( GetDoc()->GetNodes() );
//STRIP001      GetLayout()->GetCrsrOfst( &aPos, aPoint, &aState );
//STRIP001
//STRIP001      //JP 22.01.99: nicht in ReadnOnly-Inhalt setzen
//STRIP001      if( aPos.nNode.GetNode().IsProtect() )
//STRIP001          // dann darf er nur seitengebunden sein. Oder sollte man
//STRIP001          // die naechste nicht READONLY Position suchen?
//STRIP001             bAtPage = true;
//STRIP001
//STRIP001      pAnch = aPos.nNode.GetNode().GetCntntNode()->GetFrm( &aPoint, 0, FALSE );
//STRIP001
//STRIP001      if( !bAtPage )
//STRIP001      {
//STRIP001          const SwFlyFrm *pTmp = pAnch->FindFlyFrm();
//STRIP001          if( pTmp )
//STRIP001          {
//STRIP001              const SwFrm* pTmpFrm = pAnch;
//STRIP001              SwRect aBound( rBound );
//STRIP001              while( pTmp )
//STRIP001              {
//STRIP001                  if( pTmp->Frm().IsInside( aBound ) )
//STRIP001                  {
//STRIP001                      if( !bBodyOnly || !pTmp->FindFooterOrHeader() )
//STRIP001                          pPage = pTmpFrm;
//STRIP001                      break;
//STRIP001                  }
//STRIP001                  pTmp = pTmp->GetAnchor()
//STRIP001                              ? pTmp->GetAnchor()->FindFlyFrm()
//STRIP001                              : 0;
//STRIP001                  pTmpFrm = pTmp;
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          if( !pPage )
//STRIP001              pPage = pAnch->FindPageFrm();
//STRIP001
//STRIP001          // immer ueber FindAnchor gehen, damit der Frame immer an den
//STRIP001          // davorgehen gebunden wird. Beim GetCrsOfst kann man auch zum
//STRIP001          // nachfolgenden kommen. DAS IST FALSCH
//STRIP001             pAnch = ::FindAnchor( pPage, aPt, bBodyOnly );
//STRIP001          aPos.nNode = *((SwCntntFrm*)pAnch)->GetNode();
//STRIP001
//STRIP001          //JP 22.01.99: nicht in ReadnOnly-Inhalt setzen
//STRIP001          if( aPos.nNode.GetNode().IsProtect() )
//STRIP001              // dann darf er nur seitengebunden sein. Oder sollte man
//STRIP001              // die naechste nicht READONLY Position suchen?
//STRIP001                 bAtPage = true;
//STRIP001          else
//STRIP001          {
//STRIP001              aAnch.SetType( FLY_AT_CNTNT );
//STRIP001              aAnch.SetAnchor( &aPos );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      if( bAtPage )
//STRIP001      {
//STRIP001          pPage = pAnch->FindPageFrm();
//STRIP001
//STRIP001          aAnch.SetType( FLY_PAGE );
//STRIP001          aAnch.SetPageNum( pPage->GetPhyPageNum() );
//STRIP001          pAnch = pPage;      // die Page wird jetzt zum Anker
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  SfxItemSet aSet( GetDoc()->GetAttrPool(), RES_FRM_SIZE, RES_FRM_SIZE,
//STRIP001                                          RES_SURROUND, RES_ANCHOR, 0 );
//STRIP001  aSet.Put( aAnch );
//STRIP001
//STRIP001  if( OBJ_NONE == nIdent )
//STRIP001  {
//STRIP001      //Bei OBJ_NONE wird ein Fly eingefuegt.
//STRIP001      const long nWidth = rBound.Right()  - rBound.Left();
//STRIP001      const long nHeight= rBound.Bottom() - rBound.Top();
//STRIP001      aSet.Put( SwFmtFrmSize( ATT_MIN_SIZE, Max( nWidth,  long(MINFLY) ),
//STRIP001                                            Max( nHeight, long(MINFLY) )));
//STRIP001
//STRIP001         SWRECTFN( pAnch )
//STRIP001         SwTwips nXOffset;
//STRIP001      SwTwips nYOffset = rBound.Top() - pAnch->Frm().Top();
//STRIP001         if( bVert )
//STRIP001         {
//STRIP001             nXOffset = nYOffset;
//STRIP001             nYOffset = pAnch->Frm().Left()+pAnch->Frm().Width()-rBound.Right();
//STRIP001         }
//STRIP001         else if( pAnch->IsRightToLeft() )
//STRIP001             nXOffset = pAnch->Frm().Left()+pAnch->Frm().Width()-rBound.Right();
//STRIP001         else
//STRIP001             nXOffset = rBound.Left() - pAnch->Frm().Left();
//STRIP001
//STRIP001         SwFmtHoriOrient aHori( nXOffset, HORI_NONE, FRAME );
//STRIP001      if( pAnch->IsTxtFrm() && ((SwTxtFrm*)pAnch)->IsFollow() )
//STRIP001      {
//STRIP001          SwTxtFrm* pTmp = (SwTxtFrm*)pAnch;
//STRIP001          do {
//STRIP001              pTmp = pTmp->FindMaster();
//STRIP001              ASSERT( pTmp, "Where's my Master?" );
//STRIP001                 nYOffset += pTmp->IsVertical() ?
//STRIP001                             pTmp->Prt().Width() : pTmp->Prt().Height();
//STRIP001          } while ( pTmp->IsFollow() );
//STRIP001      }
//STRIP001      SwFmtVertOrient aVert( nYOffset, VERT_NONE, FRAME );
//STRIP001      aSet.Put( SwFmtSurround( SURROUND_PARALLEL ) );
//STRIP001      aSet.Put( aHori );
//STRIP001      aSet.Put( aVert );
//STRIP001
//STRIP001      //Schnell noch das Rechteck merken
//STRIP001      const SwRect aFlyRect( rBound );
//STRIP001
//STRIP001      //Erzeugtes Object wegwerfen, so kann der Fly am elegentesten
//STRIP001      //ueber vorhandene SS erzeugt werden.
//STRIP001      GetDoc()->SetNoDrawUndoObj( TRUE );         // siehe oben
//STRIP001      SdrPage *pPg = GetDoc()->MakeDrawModel()->GetPage( 0 );
//STRIP001      if( !pPg )
//STRIP001      {
//STRIP001          pPg = GetDoc()->GetDrawModel()->AllocPage( FALSE );
//STRIP001          GetDoc()->GetDrawModel()->InsertPage( pPg );
//STRIP001      }
//STRIP001      pPg->RecalcObjOrdNums();
//STRIP001      delete pPg->RemoveObject( rSdrObj.GetOrdNumDirect() );
//STRIP001      GetDoc()->SetNoDrawUndoObj( FALSE );
//STRIP001
//STRIP001      SwFlyFrm* pFlyFrm;
//STRIP001      if( NewFlyFrm( aSet, TRUE ) &&
//STRIP001          ::binfilter::GetHtmlMode( GetDoc()->GetDocShell() ) &&
//STRIP001          0 != ( pFlyFrm = FindFlyFrm() ))
//STRIP001      {
//STRIP001          SfxItemSet aHtmlSet( GetDoc()->GetAttrPool(), RES_VERT_ORIENT, RES_HORI_ORIENT );
//STRIP001          //Horizontale Ausrichtung:
//STRIP001          const FASTBOOL bLeftFrm = aFlyRect.Left() <
//STRIP001                                    pAnch->Frm().Left() + pAnch->Prt().Left(),
//STRIP001                         bLeftPrt = aFlyRect.Left() + aFlyRect.Width() <
//STRIP001                                    pAnch->Frm().Left() + pAnch->Prt().Width()/2;
//STRIP001          if( bLeftFrm || bLeftPrt )
//STRIP001          {
//STRIP001              aHori.SetHoriOrient( HORI_LEFT );
//STRIP001              aHori.SetRelationOrient( bLeftFrm ? FRAME : PRTAREA );
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              const FASTBOOL bRightFrm = aFlyRect.Left() >
//STRIP001                                         pAnch->Frm().Left() + pAnch->Prt().Width();
//STRIP001              aHori.SetHoriOrient( HORI_RIGHT );
//STRIP001              aHori.SetRelationOrient( bRightFrm ? FRAME : PRTAREA );
//STRIP001          }
//STRIP001          aHtmlSet.Put( aHori );
//STRIP001          aVert.SetVertOrient( VERT_TOP );
//STRIP001          aVert.SetRelationOrient( PRTAREA );
//STRIP001          aHtmlSet.Put( aVert );
//STRIP001
//STRIP001          GetDoc()->SetAttr( aHtmlSet, *pFlyFrm->GetFmt() );
//STRIP001      }
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      Point aRelNullPt;
//STRIP001
//STRIP001      if( OBJ_CAPTION == nIdent )
//STRIP001          aRelNullPt = ((SdrCaptionObj&)rSdrObj).GetTailPos();
//STRIP001      else
//STRIP001          aRelNullPt = rBound.TopLeft();
//STRIP001
//STRIP001      aSet.Put( aAnch );
//STRIP001      aSet.Put( SwFmtSurround( SURROUND_THROUGHT ) );
//STRIP001      SwDrawFrmFmt* pFmt = (SwDrawFrmFmt*)GetDoc()->MakeLayoutFmt( RND_DRAW_OBJECT, 0, &aSet );
//STRIP001
//STRIP001      SwDrawContact *pContact = new SwDrawContact( pFmt, &rSdrObj );
//STRIP001      if( bCharBound )
//STRIP001      {
//STRIP001          ASSERT( aAnch.GetAnchorId() == FLY_IN_CNTNT, "wrong AnchorType" );
//STRIP001          SwTxtNode *pNd = aAnch.GetCntntAnchor()->nNode.GetNode().GetTxtNode();
//STRIP001          pNd->Insert( SwFmtFlyCnt( pFmt ),
//STRIP001                          aAnch.GetCntntAnchor()->nContent.GetIndex(), 0 );
//STRIP001          SwFmtVertOrient aVert( pFmt->GetVertOrient() );
//STRIP001          aVert.SetVertOrient( VERT_LINE_CENTER );
//STRIP001          pFmt->SetAttr( aVert );
//STRIP001      }
//STRIP001      if( pAnch->IsTxtFrm() && ((SwTxtFrm*)pAnch)->IsFollow() )
//STRIP001      {
//STRIP001          SwTxtFrm* pTmp = (SwTxtFrm*)pAnch;
//STRIP001          do {
//STRIP001              pTmp = pTmp->FindMaster();
//STRIP001              ASSERT( pTmp, "Where's my Master?" );
//STRIP001          } while( pTmp->IsFollow() );
//STRIP001          pAnch = pTmp;
//STRIP001      }
//STRIP001
//STRIP001         Point aNewAnchor = pAnch->GetFrmAnchorPos( ::HasWrap( &rSdrObj ) );
//STRIP001      Point aRelPos( aRelNullPt - aNewAnchor );
//STRIP001         rSdrObj.NbcSetRelativePos( aRelPos );
//STRIP001         rSdrObj.NbcSetAnchorPos( aNewAnchor );
//STRIP001
//STRIP001      pContact->ConnectToLayout();
//STRIP001
//STRIP001         // OD 25.06.2003 #108784# - mark object at frame the object is inserted at.
//STRIP001         {
//STRIP001             SdrObject* pMarkObj = pContact->GetDrawObjectByAnchorFrm( *pAnch );
//STRIP001             if ( pMarkObj )
//STRIP001             {
//STRIP001                 Imp()->GetDrawView()->MarkObj( pMarkObj, Imp()->GetPageView(),
//STRIP001                                                 FALSE, FALSE );
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 Imp()->GetDrawView()->MarkObj( &rSdrObj, Imp()->GetPageView(),
//STRIP001                                                 FALSE, FALSE );
//STRIP001             }
//STRIP001         }
//STRIP001  }
//STRIP001
//STRIP001  GetDoc()->SetModified();
//STRIP001
//STRIP001  KillPams();
//STRIP001  EndAllActionAndCall();
//STRIP001  return TRUE;
//STRIP001 }


/*************************************************************************
|*
|*  SwFEShell::BreakCreate()
|*
|*  Ersterstellung      MA 20. Dec. 94
|*  Letzte Aenderung    MA 09. Jan. 95
|*
*************************************************************************/

//STRIP001 void SwFEShell::BreakCreate()
//STRIP001 {
//STRIP001  ASSERT( Imp()->HasDrawView(), "BreakCreate without DrawView?" );
//STRIP001  Imp()->GetDrawView()->BrkCreateObj();
//STRIP001  ::FrameNotify( this, FLY_DRAG_END );
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::IsDrawCreate()
|*
|*  Ersterstellung      OM 16. Mar. 95
|*  Letzte Aenderung    OM 16. Mar. 95
|*
*************************************************************************/

//STRIP001 BOOL SwFEShell::IsDrawCreate() const
//STRIP001 {
//STRIP001  return Imp()->HasDrawView() ? Imp()->GetDrawView()->IsCreateObj() : FALSE;
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::BeginMark()
|*
|*  Ersterstellung      OM 07. Feb. 95
|*  Letzte Aenderung    OM 07. Feb. 95
|*
*************************************************************************/

//STRIP001 BOOL SwFEShell::BeginMark( const Point &rPos )
//STRIP001 {
//STRIP001  if ( !Imp()->HasDrawView() )
//STRIP001      Imp()->MakeDrawView();
//STRIP001
//STRIP001  if ( GetPageNumber( rPos ) )
//STRIP001  {
//STRIP001      SwDrawView* pDView = Imp()->GetDrawView();
//STRIP001
//STRIP001      if (pDView->HasMarkablePoints())
//STRIP001          return pDView->BegMarkPoints( rPos, (OutputDevice*) NULL );
//STRIP001      else
//STRIP001          return pDView->BegMarkObj( rPos, (OutputDevice*) NULL );
//STRIP001  }
//STRIP001  else
//STRIP001      return FALSE;
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::MoveMark()
|*
|*  Ersterstellung      OM 07. Feb. 95
|*  Letzte Aenderung    OM 07. Feb. 95
|*
*************************************************************************/

//STRIP001 void SwFEShell::MoveMark( const Point &rPos )
//STRIP001 {
//STRIP001  ASSERT( Imp()->HasDrawView(), "MoveMark without DrawView?" );
//STRIP001
//STRIP001  if ( GetPageNumber( rPos ) )
//STRIP001  {
//STRIP001      Scroll( rPos );
//STRIP001      SwDrawView* pDView = Imp()->GetDrawView();
//STRIP001 //       Imp()->GetDrawView()->MovMarkObj( rPos );
//STRIP001
//STRIP001      if (pDView->IsInsObjPoint())
//STRIP001          pDView->MovInsObjPoint( rPos );
//STRIP001      else if (pDView->IsMarkPoints())
//STRIP001          pDView->MovMarkPoints( rPos );
//STRIP001      else
//STRIP001          pDView->MovAction( rPos );
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::EndMark()
|*
|*  Ersterstellung      OM 07. Feb. 95
|*  Letzte Aenderung    MA 08. Feb. 95
|*
*************************************************************************/

//STRIP001 BOOL SwFEShell::EndMark()
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  ASSERT( Imp()->HasDrawView(), "EndMark without DrawView?" );
//STRIP001
//STRIP001  if (Imp()->GetDrawView()->IsMarkObj())
//STRIP001  {
//STRIP001      bRet = Imp()->GetDrawView()->EndMarkObj();
//STRIP001
//STRIP001      if ( bRet )
//STRIP001      {
//STRIP001          BOOL bShowHdl = FALSE;
//STRIP001          SwDrawView* pDView = Imp()->GetDrawView();
//STRIP001          //Rahmen werden auf diese Art nicht Selektiert, es sein denn es
//STRIP001          //ist nur ein Rahmen.
//STRIP001          SdrMarkList &rMrkList = (SdrMarkList&)pDView->GetMarkList();
//STRIP001          SwFlyFrm* pOldSelFly = ::GetFlyFromMarked( &rMrkList, this );
//STRIP001
//STRIP001          if ( rMrkList.GetMarkCount() > 1 )
//STRIP001              for ( USHORT i = 0; i < rMrkList.GetMarkCount(); ++i )
//STRIP001              {
//STRIP001                  SdrObject *pObj = rMrkList.GetMark( i )->GetObj();
//STRIP001                  if( pObj->IsWriterFlyFrame() )
//STRIP001                  {
//STRIP001                      if ( !bShowHdl )
//STRIP001                      {
//STRIP001                          pDView->HideMarkHdl( GetOut() );
//STRIP001                          bShowHdl = TRUE;
//STRIP001                      }
//STRIP001                      rMrkList.DeleteMarkNum( i );
//STRIP001                      --i;    //keinen auslassen.
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001          if( bShowHdl )
//STRIP001          {
//STRIP001              pDView->MarkListHasChanged();
//STRIP001              pDView->AdjustMarkHdl();
//STRIP001              pDView->ShowMarkHdl( GetOut() );
//STRIP001          }
//STRIP001
//STRIP001          if ( rMrkList.GetMarkCount() )
//STRIP001              ::lcl_GrabCursor(this, pOldSelFly);
//STRIP001          else
//STRIP001              bRet = FALSE;
//STRIP001      }
//STRIP001      if ( bRet )
//STRIP001          ::FrameNotify( this, FLY_DRAG_START );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      if (Imp()->GetDrawView()->IsMarkPoints())
//STRIP001          bRet = Imp()->GetDrawView()->EndMarkPoints();
//STRIP001  }
//STRIP001
//STRIP001  SetChainMarker();
//STRIP001  return bRet;
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::BreakSelect()
|*
|*  Ersterstellung      OM 07. Feb. 95
|*  Letzte Aenderung    OM 07. Feb. 95
|*
*************************************************************************/

//STRIP001 void SwFEShell::BreakMark()
//STRIP001 {
//STRIP001  ASSERT( Imp()->HasDrawView(), "BreakMark without DrawView?" );
//STRIP001  Imp()->GetDrawView()->BrkMarkObj();
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::GetAnchorId()
|*
|*  Ersterstellung      MA 30. Jan. 95
|*  Letzte Aenderung    MA 30. Jan. 95
|*
*************************************************************************/

//STRIP001 short SwFEShell::GetAnchorId() const
//STRIP001 {
//STRIP001  short nRet = SHRT_MAX;
//STRIP001  if ( Imp()->HasDrawView() )
//STRIP001  {
//STRIP001      const SdrMarkList &rMrkList = Imp()->GetDrawView()->GetMarkList();
//STRIP001      for ( USHORT i = 0; i < rMrkList.GetMarkCount(); ++i )
//STRIP001      {
//STRIP001          SdrObject *pObj = rMrkList.GetMark( i )->GetObj();
//STRIP001          if ( pObj->IsWriterFlyFrame() )
//STRIP001          {
//STRIP001              nRet = -1;
//STRIP001              break;
//STRIP001          }
//STRIP001          SwDrawContact *pContact = (SwDrawContact*)GetUserCall(pObj);
//STRIP001          short nId = pContact->GetFmt()->GetAnchor().GetAnchorId();
//STRIP001          if ( nRet == SHRT_MAX )
//STRIP001              nRet = nId;
//STRIP001          else if ( nRet != nId )
//STRIP001          {
//STRIP001              nRet = -1;
//STRIP001              break;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  if ( nRet == SHRT_MAX )
//STRIP001      nRet = -1;
//STRIP001  return nRet;
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::ChgAnchor()
|*
|*  Ersterstellung      MA 10. Jan. 95
|*  Letzte Aenderung    MA 30. May. 96
|*
*************************************************************************/

//STRIP001 void SwFEShell::ChgAnchor( int eAnchorId, BOOL bSameOnly, BOOL bPosCorr )
//STRIP001 {
//STRIP001  ASSERT( Imp()->HasDrawView(), "ChgAnchor without DrawView?" );
//STRIP001  const SdrMarkList &rMrkList = Imp()->GetDrawView()->GetMarkList();
//STRIP001  if( rMrkList.GetMarkCount() &&
//STRIP001      !rMrkList.GetMark( 0 )->GetObj()->GetUpGroup() )
//STRIP001  {
//STRIP001      StartAllAction();
//STRIP001
//STRIP001      if( GetDoc()->ChgAnchor( rMrkList, eAnchorId, bSameOnly, bPosCorr ))
//STRIP001          Imp()->GetDrawView()->UnmarkAll();
//STRIP001
//STRIP001      EndAllAction();
//STRIP001
//STRIP001      ::FrameNotify( this, FLY_DRAG );
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::DelSelectedObj()
|*
|*  Ersterstellung      MA 03. Nov. 92
|*  Letzte Aenderung    MA 14. Nov. 95
|*
*************************************************************************/

//STRIP001 void SwFEShell::DelSelectedObj()
//STRIP001 {
//STRIP001  ASSERT( Imp()->HasDrawView(), "DelSelectedObj(), no DrawView available" );
//STRIP001  if ( Imp()->HasDrawView() )
//STRIP001  {
//STRIP001      StartAllAction();
//STRIP001      Imp()->GetDrawView()->DeleteMarked();
//STRIP001      EndAllAction();
//STRIP001      ::FrameNotify( this, FLY_DRAG_END );
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::GetObjSize(), GetAnchorObjDiff()
|*
|*  Beschreibung        Fuer die Statuszeile zum Erfragen der aktuellen
|*                      Verhaeltnisse
|*  Ersterstellung      MA 25. Apr. 95
|*  Letzte Aenderung    MA 25. Apr. 95
|*
*************************************************************************/

//STRIP001 Size SwFEShell::GetObjSize() const
//STRIP001 {
//STRIP001  Rectangle aRect;
//STRIP001  if ( Imp()->HasDrawView() )
//STRIP001  {
//STRIP001      if ( Imp()->GetDrawView()->IsAction() )
//STRIP001          Imp()->GetDrawView()->TakeActionRect( aRect );
//STRIP001      else
//STRIP001          aRect = Imp()->GetDrawView()->GetAllMarkedRect();
//STRIP001  }
//STRIP001  return aRect.GetSize();
//STRIP001 }

//STRIP001 Point SwFEShell::GetAnchorObjDiff() const
//STRIP001 {
//STRIP001  const SdrView *pView = Imp()->GetDrawView();
//STRIP001  ASSERT( pView, "GetAnchorObjDiff without DrawView?" );
//STRIP001
//STRIP001  Rectangle aRect;
//STRIP001  if ( Imp()->GetDrawView()->IsAction() )
//STRIP001      Imp()->GetDrawView()->TakeActionRect( aRect );
//STRIP001  else
//STRIP001      aRect = Imp()->GetDrawView()->GetAllMarkedRect();
//STRIP001
//STRIP001  Point aRet( aRect.TopLeft() );
//STRIP001
//STRIP001  if ( IsFrmSelected() )
//STRIP001  {
//STRIP001      SwFlyFrm *pFly = FindFlyFrm();
//STRIP001      aRet -= pFly->GetAnchor()->Frm().Pos();
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      const SdrObject *pObj = pView->GetMarkList().GetMarkCount() == 1 ?
//STRIP001                              pView->GetMarkList().GetMark(0)->GetObj() : 0;
//STRIP001      if ( pObj )
//STRIP001          aRet -= pObj->GetAnchorPos();
//STRIP001  }
//STRIP001
//STRIP001  return aRet;
//STRIP001 }

//STRIP001 Point SwFEShell::GetObjAbsPos() const
//STRIP001 {
//STRIP001  ASSERT( Imp()->GetDrawView(), "GetObjAbsPos() without DrawView?" );
//STRIP001  return Imp()->GetDrawView()->GetDragStat().GetActionRect().TopLeft();
//STRIP001 }



/*************************************************************************
|*
|*  SwFEShell::IsGroupSelected()
|*
|*  Ersterstellung      MA 30. Jan. 95
|*  Letzte Aenderung    MA 30. May. 96
|*
*************************************************************************/

//STRIP001 BOOL SwFEShell::IsGroupSelected()
//STRIP001 {
//STRIP001  if ( IsObjSelected() )
//STRIP001  {
//STRIP001      const SdrMarkList &rMrkList = Imp()->GetDrawView()->GetMarkList();
//STRIP001      for ( USHORT i = 0; i < rMrkList.GetMarkCount(); ++i )
//STRIP001      {
//STRIP001          SdrObject *pObj = rMrkList.GetMark( i )->GetObj();
//STRIP001             // OD 30.06.2003 #108784# - consider 'virtual' drawing objects.
//STRIP001             // Thus, use corresponding method instead of checking type.
//STRIP001             if ( pObj->IsGroupObject() &&
//STRIP001                  FLY_IN_CNTNT != ((SwDrawContact*)GetUserCall(pObj))->
//STRIP001                                       GetFmt()->GetAnchor().GetAnchorId() )
//STRIP001             {
//STRIP001              return TRUE;
//STRIP001             }
//STRIP001      }
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

// OD 27.06.2003 #108784# - change return type.
// OD 27.06.2003 #108784# - adjustments for drawing objects in header/footer:
//      allow group, only if all selected objects are in the same header/footer
//      or not in header/footer.
//STRIP001 bool SwFEShell::IsGroupAllowed() const
//STRIP001 {
//STRIP001     bool bIsGroupAllowed = false;
//STRIP001  if ( IsObjSelected() > 1 )
//STRIP001  {
//STRIP001         bIsGroupAllowed = true;
//STRIP001         const SdrObject* pUpGroup = 0L;
//STRIP001         const SwFrm* pHeaderFooterFrm = 0L;
//STRIP001      const SdrMarkList &rMrkList = Imp()->GetDrawView()->GetMarkList();
//STRIP001         for ( USHORT i = 0; bIsGroupAllowed && i < rMrkList.GetMarkCount(); ++i )
//STRIP001      {
//STRIP001             const SdrObject* pObj = rMrkList.GetMark( i )->GetObj();
//STRIP001             if ( i )
//STRIP001                 bIsGroupAllowed = pObj->GetUpGroup() == pUpGroup;
//STRIP001          else
//STRIP001              pUpGroup = pObj->GetUpGroup();
//STRIP001
//STRIP001             if ( bIsGroupAllowed &&
//STRIP001                  FLY_IN_CNTNT == ::FindFrmFmt( (SdrObject*)pObj )->GetAnchor().GetAnchorId() )
//STRIP001             {
//STRIP001                 bIsGroupAllowed = false;
//STRIP001             }
//STRIP001
//STRIP001             // OD 27.06.2003 #108784# - check, if all selected objects are in the
//STRIP001             // same header/footer or not in header/footer.
//STRIP001             if ( bIsGroupAllowed )
//STRIP001             {
//STRIP001                 const SwFrm* pAnchorFrm = 0L;
//STRIP001                 if ( pObj->IsWriterFlyFrame() )
//STRIP001                 {
//STRIP001                     const SwFlyFrm* pFlyFrm =
//STRIP001                             static_cast<const SwVirtFlyDrawObj*>(pObj)->GetFlyFrm();
//STRIP001                     if ( pFlyFrm )
//STRIP001                     {
//STRIP001                         pAnchorFrm = pFlyFrm->GetAnchor();
//STRIP001                     }
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     if ( pObj->ISA(SwDrawVirtObj) )
//STRIP001                     {
//STRIP001                         pAnchorFrm = static_cast<const SwDrawVirtObj*>(pObj)->GetAnchorFrm();
//STRIP001                     }
//STRIP001                     else
//STRIP001                     {
//STRIP001                         SwDrawContact* pDrawContact = static_cast<SwDrawContact*>(pObj->GetUserCall());
//STRIP001                         if ( pDrawContact )
//STRIP001                         {
//STRIP001                             pAnchorFrm = pDrawContact->GetAnchor();
//STRIP001                         }
//STRIP001                     }
//STRIP001                 }
//STRIP001                 if ( pAnchorFrm )
//STRIP001                 {
//STRIP001                     if ( i )
//STRIP001                     {
//STRIP001                         bIsGroupAllowed =
//STRIP001                             ( pAnchorFrm->FindFooterOrHeader() == pHeaderFooterFrm );
//STRIP001                     }
//STRIP001                     else
//STRIP001                     {
//STRIP001                         pHeaderFooterFrm = pAnchorFrm->FindFooterOrHeader();
//STRIP001                     }
//STRIP001                 }
//STRIP001             }
//STRIP001
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001     return bIsGroupAllowed;
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::GroupSelection()
|*
|*  Beschreibung        Die Gruppe bekommt den Anker und das Contactobjekt
|*                      des ersten in der Selektion
|*  Ersterstellung      MA 30. Jan. 95
|*  Letzte Aenderung    MA 23. Apr. 95
|*
*************************************************************************/

//STRIP001 void SwFEShell::GroupSelection()
//STRIP001 {
//STRIP001  if ( IsGroupAllowed() )
//STRIP001  {
//STRIP001      StartAllAction();
//STRIP001      StartUndo( UNDO_START );
//STRIP001
//STRIP001      GetDoc()->GroupSelection( *Imp()->GetDrawView() );
//STRIP001      ChgAnchor( 0, TRUE );
//STRIP001
//STRIP001      EndUndo( UNDO_END );
//STRIP001      EndAllAction();
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::UnGroupSelection()
|*
|*  Beschreibung        Die Einzelobjekte bekommen eine Kopie vom Anker und
|*                      Contactobjekt der Gruppe.
|*  Ersterstellung      MA 30. Jan. 95
|*  Letzte Aenderung    MA 01. Feb. 95
|*
*************************************************************************/

//STRIP001 void SwFEShell::UnGroupSelection()
//STRIP001 {
//STRIP001  if ( IsGroupSelected() )
//STRIP001  {
//STRIP001      StartAllAction();
//STRIP001      StartUndo( UNDO_START );
//STRIP001
//STRIP001      GetDoc()->UnGroupSelection( *Imp()->GetDrawView() );
//STRIP001      ChgAnchor( 0, TRUE );
//STRIP001
//STRIP001      EndUndo( UNDO_END );
//STRIP001      EndAllAction();
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*  SwFEShell::MirrorSelection()
|*
|*  Ersterstellung      MA 06. Aug. 95
|*  Letzte Aenderung    MA 06. Aug. 95
|*
*************************************************************************/

//STRIP001 void SwFEShell::MirrorSelection( BOOL bHorizontal )
//STRIP001 {
//STRIP001  SdrView *pView = Imp()->GetDrawView();
//STRIP001  if ( IsObjSelected() && pView->IsMirrorAllowed() )
//STRIP001  {
//STRIP001      if ( bHorizontal )
//STRIP001          pView->MirrorAllMarkedHorizontal();
//STRIP001      else
//STRIP001          pView->MirrorAllMarkedVertical();
//STRIP001  }
//STRIP001 }

// springe zum benannten Rahmen (Grafik/OLE)

/*N*/ BOOL SwFEShell::GotoFly( const String& rName, FlyCntType eType, BOOL bSelFrm )
/*N*/ {
/*N*/   BOOL bRet = FALSE;
/*N*/ static BYTE __READONLY_DATA aChkArr[ 4 ] = {
/*N*/            /* FLYCNTTYPE_ALL */   0,
/*N*/            /* FLYCNTTYPE_FRM */   ND_TEXTNODE,
/*N*/            /* FLYCNTTYPE_GRF */   ND_GRFNODE,
/*N*/            /* FLYCNTTYPE_OLE */   ND_OLENODE
/*N*/           };
/*N*/
/*N*/   const SwFlyFrmFmt* pFlyFmt = pDoc->FindFlyByName( rName, aChkArr[ eType]);
/*N*/   if( pFlyFmt )
/*N*/   {
/*N*/       SET_CURR_SHELL( this );
/*N*/
/*N*/       SwClientIter aIter( *(SwModify*)pFlyFmt );
/*N*/       SwFlyFrm* pFrm = (SwFlyFrm*)aIter.First( TYPE( SwFlyFrm ));
/*N*/       if( pFrm )
/*N*/       {
/*N*/           ASSERT( pFrm->IsFlyFrm(), "Wrong FrmType" );
/*N*/           if( bSelFrm )
/*N*/           {
/*?*/               DBG_BF_ASSERT(0, "STRIP"); //STRIP001   SelectObj( pFrm->Frm().Pos(), 0, ((SwFlyFrm*)pFrm)->GetVirtDrawObj() );
//STRIP001 /*?*/                if( !ActionPend() )
//STRIP001 /*?*/                    MakeVisible( pFrm->Frm() );
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               pFrm->GetAnchor()->Calc();
/*N*/               SwCntntFrm *pCFrm = pFrm->ContainsCntnt();
/*N*/               if ( pCFrm )
/*N*/               {
/*?*/                   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 SwCntntNode   *pCNode = pCFrm->GetNode();
//STRIP001 /*?*/                    ClearMark();
//STRIP001 /*?*/                    SwPaM* pCrsr = GetCrsr();
//STRIP001 /*?*/
//STRIP001 /*?*/                    pCrsr->GetPoint()->nNode = *pCNode;
//STRIP001 /*?*/                    pCrsr->GetPoint()->nContent.Assign( pCNode, 0 );
//STRIP001 /*?*/
//STRIP001 /*?*/                    SwRect& rChrRect = (SwRect&)GetCharRect();
//STRIP001 /*?*/                    rChrRect = pFrm->Prt();
//STRIP001 /*?*/                    rChrRect.Pos() += pFrm->Frm().Pos();
//STRIP001 /*?*/                    GetCrsrDocPos() = rChrRect.Pos();
/*N*/               }
/*N*/           }
/*N*/           bRet = TRUE;
/*N*/       }
/*N*/   }
/*N*/   return bRet;
/*N*/ }

//STRIP001 USHORT SwFEShell::GetFlyCount(FlyCntType eType ) const
//STRIP001 {
//STRIP001  return GetDoc()->GetFlyCount(eType);
//STRIP001 }


//STRIP001 const SwFrmFmt*  SwFEShell::GetFlyNum(USHORT nIdx, FlyCntType eType ) const
//STRIP001 {
//STRIP001  return GetDoc()->GetFlyNum(nIdx, eType );
//STRIP001 }

// zeige das akt. selektierte "Object" an
/*N*/ void SwFEShell::MakeSelVisible()
/*N*/ {
/*N*/   if( Imp()->HasDrawView() &&
/*N*/       Imp()->GetDrawView()->GetMarkList().GetMarkCount() )
/*N*/   {
/*?*/       DBG_BF_ASSERT(0, "STRIP"); //STRIP001 MakeVisible( Imp()->GetDrawView()->GetAllMarkedRect() );
/*N*/   }
/*N*/   else
/*N*/       SwCrsrShell::MakeSelVisible();
/*N*/ }


//Welcher Schutz ist am selektierten Objekt gesetzt?
/*N*/ BYTE SwFEShell::IsSelObjProtected( FlyProtectType eType ) const
/*N*/ {
/*N*/   int nChk = 0;
/*N*/   BOOL bParent = eType & FLYPROTECT_PARENT;
/*N*/   if( Imp()->HasDrawView() )
/*N*/   {
/*N*/       const SdrMarkList &rMrkList = Imp()->GetDrawView()->GetMarkList();
/*N*/       for( ULONG i = rMrkList.GetMarkCount(); i; )
/*N*/       {
/*?*/           SdrObject *pObj = rMrkList.GetMark( --i )->GetObj();
/*?*/           if( !bParent )
/*?*/           {
/*?*/               nChk |= ( pObj->IsMoveProtect() ? FLYPROTECT_POS : 0 ) |
/*?*/                       ( pObj->IsResizeProtect()? FLYPROTECT_SIZE : 0 );
/*?*/
/*?*/               if( FLYPROTECT_CONTENT & eType && pObj->IsWriterFlyFrame() )
/*?*/               {
/*?*/                   SwFlyFrm *pFly = ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm();
/*?*/                   if ( pFly->GetFmt()->GetProtect().IsCntntProtected() )
/*?*/                       nChk |= FLYPROTECT_CONTENT;
/*?*/
/*?*/                   if ( pFly->Lower() && pFly->Lower()->IsNoTxtFrm() )
/*?*/                   {
/*?*/                       SwOLENode *pNd = ((SwCntntFrm*)pFly->Lower())->GetNode()->GetOLENode();
/*?*/                       if ( pNd )
/*?*/                       {
/*?*/                           SvInPlaceObjectRef aRef = pNd->GetOLEObj().GetOleRef();
/*?*/                           if ( aRef.Is() &&
/*?*/                                SVOBJ_MISCSTATUS_NOTRESIZEABLE & aRef->GetMiscStatus() )
/*?*/                           {
/*?*/                               nChk |= FLYPROTECT_SIZE;
/*?*/                               nChk |= FLYPROTECT_FIXED;
/*?*/                           }
/*?*/                       }
/*?*/                   }
/*?*/               }
/*?*/               nChk &= eType;
/*?*/               if( nChk == eType )
/*?*/                   return eType;
/*?*/           }
/*?*/           SwFrm* pAnch;
/*?*/           if( pObj->IsWriterFlyFrame() )
/*?*/               pAnch = ( (SwVirtFlyDrawObj*)pObj )->GetFlyFrm()->GetAnchor();
/*?*/           else
/*?*/           {
/*?*/               SwDrawContact* pTmp = (SwDrawContact*)GetUserCall(pObj);
/*?*/               pAnch = pTmp ? pTmp->GetAnchor() : NULL;
/*?*/           }
/*?*/           if( pAnch && pAnch->IsProtected() )
/*?*/               return eType;
/*N*/       }
/*N*/   }
/*N*/   return nChk;
/*N*/ }

//STRIP001 BOOL SwFEShell::GetObjAttr( SfxItemSet &rSet ) const
//STRIP001 {
//STRIP001  if ( !IsObjSelected() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  const SdrMarkList &rMrkList = Imp()->GetDrawView()->GetMarkList();
//STRIP001  for ( USHORT i = 0; i < rMrkList.GetMarkCount(); ++i )
//STRIP001  {
//STRIP001      SdrObject *pObj = rMrkList.GetMark( i )->GetObj();
//STRIP001      SwDrawContact *pContact = (SwDrawContact*)GetUserCall(pObj);
//STRIP001      if ( i )
//STRIP001          rSet.MergeValues( pContact->GetFmt()->GetAttrSet() );
//STRIP001      else
//STRIP001          rSet.Put( pContact->GetFmt()->GetAttrSet() );
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL SwFEShell::SetObjAttr( const SfxItemSet& rSet )
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001
//STRIP001  if ( !rSet.Count() )
//STRIP001  {   ASSERT( !this, "SetObjAttr, empty set." );
//STRIP001      return FALSE;
//STRIP001  }
//STRIP001
//STRIP001  StartAllAction();
//STRIP001  StartUndo( UNDO_INSATTR );
//STRIP001
//STRIP001  const SdrMarkList &rMrkList = Imp()->GetDrawView()->GetMarkList();
//STRIP001  for ( USHORT i = 0; i < rMrkList.GetMarkCount(); ++i )
//STRIP001  {
//STRIP001      SdrObject *pObj = rMrkList.GetMark( i )->GetObj();
//STRIP001      SwDrawContact *pContact = (SwDrawContact*)GetUserCall(pObj);
//STRIP001      GetDoc()->SetAttr( rSet, *pContact->GetFmt() );
//STRIP001  }
//STRIP001
//STRIP001  EndUndo( UNDO_INSATTR );
//STRIP001  EndAllActionAndCall();
//STRIP001  GetDoc()->SetModified();
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL SwFEShell::IsAlignPossible() const
//STRIP001 {
//STRIP001  USHORT nCnt;
//STRIP001  if ( 0 < (nCnt = IsObjSelected()) )
//STRIP001  {
//STRIP001      BOOL bRet = TRUE;
//STRIP001      if ( nCnt == 1 )
//STRIP001      {
//STRIP001          SdrObject *pO = Imp()->GetDrawView()->GetMarkList().GetMark(0)->GetObj();
//STRIP001          SwDrawContact *pC = (SwDrawContact*)GetUserCall(pO);
//STRIP001             //only as character bound drawings can be aligned
//STRIP001             bRet = pC->GetFmt()->GetAnchor().GetAnchorId() == FLY_IN_CNTNT;
//STRIP001      }
//STRIP001      if ( bRet )
//STRIP001          return Imp()->GetDrawView()->IsAlignPossible();
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }


//Temporaerer Fix bis SS von JOE da ist
//STRIP001 void SwFEShell::CheckUnboundObjects()
//STRIP001 {
//STRIP001  SET_CURR_SHELL( this );
//STRIP001
//STRIP001  const SdrMarkList &rMrkList = Imp()->GetDrawView()->GetMarkList();
//STRIP001  for ( USHORT i = 0; i < rMrkList.GetMarkCount(); ++i )
//STRIP001  {
//STRIP001      SdrObject *pObj = rMrkList.GetMark( i )->GetObj();
//STRIP001      if ( !GetUserCall(pObj) )
//STRIP001      {
//STRIP001          const Rectangle &rBound = pObj->GetSnapRect();
//STRIP001          const Point aPt( rBound.TopLeft() );
//STRIP001          const SwFrm *pPage = GetLayout()->Lower();
//STRIP001          const SwFrm *pLast = pPage;
//STRIP001          while ( pPage && !pPage->Frm().IsInside( aPt ) )
//STRIP001          {
//STRIP001              if ( aPt.Y() > pPage->Frm().Bottom() )
//STRIP001                  pLast = pPage;
//STRIP001              pPage = pPage->GetNext();
//STRIP001          }
//STRIP001          if ( !pPage )
//STRIP001              pPage = pLast;
//STRIP001          ASSERT( pPage, "Page not found." );
//STRIP001
//STRIP001          //Fremde Identifier sollen in den Default laufen.
//STRIP001          //Ueberschneidungen sind moeglich!!
//STRIP001          UINT16 nIdent =
//STRIP001                  Imp()->GetDrawView()->GetCurrentObjInventor() == SdrInventor ?
//STRIP001                          Imp()->GetDrawView()->GetCurrentObjIdentifier() : 0xFFFF;
//STRIP001
//STRIP001          SwFmtAnchor aAnch;
//STRIP001          const SwFrm *pAnch = 0;
//STRIP001          {
//STRIP001          pAnch = ::FindAnchor( pPage, aPt, TRUE );
//STRIP001          SwPosition aPos( *((SwCntntFrm*)pAnch)->GetNode() );
//STRIP001          aAnch.SetType( FLY_AT_CNTNT );
//STRIP001          aAnch.SetAnchor( &aPos );
//STRIP001          ((SwRect&)GetCharRect()).Pos() = aPt;
//STRIP001          }
//STRIP001
//STRIP001          //Erst hier die Action, damit das GetCharRect aktuelle Werte liefert.
//STRIP001          StartAllAction();
//STRIP001
//STRIP001          SfxItemSet aSet( GetAttrPool(), RES_FRM_SIZE, RES_FRM_SIZE,
//STRIP001                                          RES_SURROUND, RES_ANCHOR, 0 );
//STRIP001          aSet.Put( aAnch );
//STRIP001
//STRIP001          Point aRelNullPt;
//STRIP001
//STRIP001          if( OBJ_CAPTION == nIdent )
//STRIP001              aRelNullPt = ((SdrCaptionObj*)pObj)->GetTailPos();
//STRIP001          else
//STRIP001              aRelNullPt = rBound.TopLeft();
//STRIP001
//STRIP001          aSet.Put( aAnch );
//STRIP001          aSet.Put( SwFmtSurround( SURROUND_THROUGHT ) );
//STRIP001          SwFrmFmt* pFmt = GetDoc()->MakeLayoutFmt(
//STRIP001                                          RND_DRAW_OBJECT, 0, &aSet );
//STRIP001
//STRIP001          SwDrawContact *pContact = new SwDrawContact(
//STRIP001                                          (SwDrawFrmFmt*)pFmt, pObj );
//STRIP001
//STRIP001             Point aNewAnchor = pAnch->GetFrmAnchorPos( ::HasWrap( pObj ) );
//STRIP001             pObj->NbcSetRelativePos( aRelNullPt - aNewAnchor );
//STRIP001             pObj->NbcSetAnchorPos  ( aNewAnchor );
//STRIP001
//STRIP001             pContact->ConnectToLayout();
//STRIP001
//STRIP001          EndAllAction();
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SwFEShell::SetCalcFieldValueHdl(Outliner* pOutliner)
//STRIP001 {
//STRIP001  GetDoc()->SetCalcFieldValueHdl(pOutliner);
//STRIP001 }



//STRIP001 int SwFEShell::Chainable( SwRect &rRect, const SwFrmFmt &rSource,
//STRIP001                          const Point &rPt ) const
//STRIP001 {
//STRIP001  rRect.Clear();
//STRIP001
//STRIP001  //Die Source darf noch keinen Follow haben.
//STRIP001  const SwFmtChain &rChain = rSource.GetChain();
//STRIP001  if ( rChain.GetNext() )
//STRIP001      return SW_CHAIN_SOURCE_CHAINED;
//STRIP001
//STRIP001  if( Imp()->HasDrawView() )
//STRIP001  {
//STRIP001      SdrObject* pObj;
//STRIP001      SdrPageView* pPView;
//STRIP001      SwDrawView *pDView = (SwDrawView*)Imp()->GetDrawView();
//STRIP001      const USHORT nOld = pDView->GetHitTolerancePixel();
//STRIP001      pDView->SetHitTolerancePixel( 0 );
//STRIP001      if( pDView->PickObj( rPt, pObj, pPView, SDRSEARCH_PICKMARKABLE ) &&
//STRIP001          pObj->IsWriterFlyFrame() )
//STRIP001      {
//STRIP001          SwFlyFrm *pFly = ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm();
//STRIP001          rRect = pFly->Frm();
//STRIP001
//STRIP001          //Ziel darf natuerlich nicht gleich Source sein und es
//STRIP001          //darf keine geschlossene Kette entstehen.
//STRIP001          SwFrmFmt *pFmt = pFly->GetFmt();
//STRIP001          return GetDoc()->Chainable(rSource, *pFmt);
//STRIP001      }
//STRIP001      pDView->SetHitTolerancePixel( nOld );
//STRIP001  }
//STRIP001  return SW_CHAIN_NOT_FOUND;
//STRIP001 }
/* -----------------------------09.08.2002 07:40------------------------------

 ---------------------------------------------------------------------------*/
/*M*/ int SwFEShell::Chain( SwFrmFmt &rSource, const SwFrmFmt &rDest )
/*M*/ {
/*M*/     return GetDoc()->Chain(rSource, rDest);
/*M*/ }

//STRIP001 int SwFEShell::Chain( SwFrmFmt &rSource, const Point &rPt )
//STRIP001 {
//STRIP001  SwRect aDummy;
//STRIP001  int nErr = Chainable( aDummy, rSource, rPt );
//STRIP001  if ( !nErr )
//STRIP001  {
//STRIP001      StartAllAction();
//STRIP001      SdrObject* pObj;
//STRIP001      SdrPageView* pPView;
//STRIP001      SwDrawView *pDView = (SwDrawView*)Imp()->GetDrawView();
//STRIP001      const USHORT nOld = pDView->GetHitTolerancePixel();
//STRIP001      pDView->SetHitTolerancePixel( 0 );
//STRIP001      pDView->PickObj( rPt, pObj, pPView, SDRSEARCH_PICKMARKABLE );
//STRIP001      pDView->SetHitTolerancePixel( nOld );
//STRIP001      SwFlyFrm *pFly = ((SwVirtFlyDrawObj*)pObj)->GetFlyFrm();
//STRIP001
//STRIP001      SwFlyFrmFmt *pFmt = (SwFlyFrmFmt*)pFly->GetFmt();
//STRIP001      GetDoc()->Chain(rSource, *pFmt);
//STRIP001      EndAllAction();
//STRIP001      SetChainMarker();
//STRIP001  }
//STRIP001  return nErr;
//STRIP001 }

//STRIP001 void SwFEShell::Unchain( SwFrmFmt &rFmt )
//STRIP001 {
//STRIP001  StartAllAction();
//STRIP001  GetDoc()->Unchain(rFmt);
//STRIP001  EndAllAction();
//STRIP001 }


/*N*/ void SwFEShell::HideChainMarker()
/*N*/ {
/*N*/   if ( pChainFrom )
/*?*/       {DBG_BF_ASSERT(0, "STRIP"); }//STRIP001 pChainFrom->Hide();
/*N*/   if ( pChainTo )
/*?*/       {DBG_BF_ASSERT(0, "STRIP");} //STRIP001 pChainTo->Hide();
/*N*/ }

/*N*/ void SwFEShell::SetChainMarker()
/*N*/ {
/*N*/   FASTBOOL bDelFrom = TRUE,
/*N*/            bDelTo   = TRUE;
/*N*/   if ( IsFrmSelected() )
/*N*/   {
/*?*/       SwFlyFrm *pFly = FindFlyFrm();
/*?*/
/*?*/       XPolygon aPoly(3);
/*?*/       if ( pFly->GetPrevLink() )
/*?*/       {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            bDelFrom = FALSE;
//STRIP001 /*?*/            const SwFrm *pPre = pFly->GetPrevLink();
//STRIP001 /*?*/            aPoly[0] = Point( pPre->Frm().Right(), pPre->Frm().Bottom());
//STRIP001 /*?*/            aPoly[1] = pFly->Frm().Pos();
//STRIP001 /*?*/            if ( !pChainFrom )
//STRIP001 /*?*/                pChainFrom = new SdrViewUserMarker( GetDrawView() );
//STRIP001 /*?*/            pChainFrom->SetPolyLine( TRUE );
//STRIP001 /*?*/            pChainFrom->SetXPolygon( aPoly );
//STRIP001 /*?*/            pChainFrom->Show();
/*?*/       }
/*?*/       if ( pFly->GetNextLink() )
/*?*/       {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            bDelTo = FALSE;
//STRIP001 /*?*/            const SwFlyFrm *pNxt = pFly->GetNextLink();
//STRIP001 /*?*/            aPoly[0] = Point( pFly->Frm().Right(), pFly->Frm().Bottom());
//STRIP001 /*?*/            aPoly[1] = pNxt->Frm().Pos();
//STRIP001 /*?*/            if ( !pChainTo )
//STRIP001 /*?*/                pChainTo = new SdrViewUserMarker( GetDrawView() );
//STRIP001 /*?*/            pChainTo->SetXPolygon( aPoly );
//STRIP001 /*?*/            pChainTo->SetPolyLine( TRUE );
//STRIP001 /*?*/            pChainTo->Show();
/*?*/       }
/*N*/   }
/*N*/   if ( bDelFrom )
/*N*/       delete pChainFrom, pChainFrom = 0;
/*N*/   if ( bDelTo )
/*N*/       delete pChainTo,   pChainTo = 0;
/*N*/ }

//STRIP001 long SwFEShell::GetSectionWidth( SwFmt& rFmt ) const
//STRIP001 {
//STRIP001  SwFrm *pFrm = GetCurrFrm();
//STRIP001  // Steht der Cursor z.Z. in einem SectionFrm?
//STRIP001  if( pFrm && pFrm->IsInSct() )
//STRIP001  {
//STRIP001      SwSectionFrm* pSect = pFrm->FindSctFrm();
//STRIP001      do
//STRIP001      {
//STRIP001          // Ist es der Gewuenschte?
//STRIP001          if( pSect->GetRegisteredIn() == &rFmt )
//STRIP001              return pSect->Frm().Width();
//STRIP001          // fuer geschachtelte Bereiche
//STRIP001          pSect = pSect->GetUpper()->FindSctFrm();
//STRIP001      }
//STRIP001      while( pSect );
//STRIP001  }
//STRIP001  SwClientIter aIter( rFmt );
//STRIP001  SwClient *pLast = aIter.GoStart();
//STRIP001  while ( pLast )
//STRIP001  {
//STRIP001      if ( pLast->IsA( TYPE(SwFrm) ) )
//STRIP001      {
//STRIP001          SwSectionFrm* pSct = (SwSectionFrm*)pLast;
//STRIP001          if( !pSct->IsFollow() )
//STRIP001              return pSct->Frm().Width();
//STRIP001      }
//STRIP001      pLast = aIter++;
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }
/* -----------------------------2002/06/24 15:07------------------------------

 ---------------------------------------------------------------------------*/
//STRIP001 void SwFEShell::CreateDefaultShape(UINT16 eSdrObjectKind, const Rectangle& rRect,
//STRIP001                 USHORT nSlotId)
//STRIP001 {
//STRIP001     SdrView* pDrawView = GetDrawView();
//STRIP001     SdrModel* pDrawModel = pDrawView->GetModel();
//STRIP001     SdrObject* pObj = SdrObjFactory::MakeNewObject(
//STRIP001         SdrInventor, eSdrObjectKind,
//STRIP001         0L, pDrawModel);
//STRIP001
//STRIP001  if(pObj)
//STRIP001  {
//STRIP001         Rectangle aRect(rRect);
//STRIP001         if(OBJ_CARC == eSdrObjectKind || OBJ_CCUT == eSdrObjectKind)
//STRIP001         {
//STRIP001             // force quadratic
//STRIP001             if(aRect.GetWidth() > aRect.GetHeight())
//STRIP001             {
//STRIP001                 aRect = Rectangle(
//STRIP001                     Point(aRect.Left() + ((aRect.GetWidth() - aRect.GetHeight()) / 2), aRect.Top()),
//STRIP001                     Size(aRect.GetHeight(), aRect.GetHeight()));
//STRIP001             }
//STRIP001             else
//STRIP001             {
//STRIP001                 aRect = Rectangle(
//STRIP001                     Point(aRect.Left(), aRect.Top() + ((aRect.GetHeight() - aRect.GetWidth()) / 2)),
//STRIP001                     Size(aRect.GetWidth(), aRect.GetWidth()));
//STRIP001             }
//STRIP001         }
//STRIP001         pObj->SetLogicRect(aRect);
//STRIP001
//STRIP001         if(pObj->ISA(SdrCircObj))
//STRIP001      {
//STRIP001             SfxItemSet aAttr(pDrawModel->GetItemPool());
//STRIP001          aAttr.Put(SdrCircStartAngleItem(9000));
//STRIP001          aAttr.Put(SdrCircEndAngleItem(0));
//STRIP001          pObj->SetItemSet(aAttr);
//STRIP001         }
//STRIP001         else if(pObj->ISA(SdrPathObj))
//STRIP001      {
//STRIP001          XPolyPolygon aPoly;
//STRIP001
//STRIP001             switch(eSdrObjectKind)
//STRIP001          {
//STRIP001                 case OBJ_PATHLINE:
//STRIP001              {
//STRIP001                  XPolygon aInnerPoly;
//STRIP001                     aInnerPoly[0] = aRect.BottomLeft();
//STRIP001                     aInnerPoly[1] = aRect.BottomCenter();
//STRIP001                     aInnerPoly[2] = aRect.BottomCenter();
//STRIP001                     aInnerPoly[3] = aRect.Center();
//STRIP001                     aInnerPoly[4] = aRect.TopCenter();
//STRIP001                     aInnerPoly[5] = aRect.TopCenter();
//STRIP001                     aInnerPoly[6] = aRect.TopRight();
//STRIP001
//STRIP001                  aInnerPoly.SetFlags(1, XPOLY_CONTROL);
//STRIP001                  aInnerPoly.SetFlags(2, XPOLY_CONTROL);
//STRIP001                  aInnerPoly.SetFlags(3, XPOLY_SYMMTR);
//STRIP001                  aInnerPoly.SetFlags(4, XPOLY_CONTROL);
//STRIP001                  aInnerPoly.SetFlags(5, XPOLY_CONTROL);
//STRIP001
//STRIP001                  aPoly.Insert(aInnerPoly);
//STRIP001                 }
//STRIP001                 break;
//STRIP001                 case OBJ_FREELINE:
//STRIP001              {
//STRIP001                  XPolygon aInnerPoly;
//STRIP001                     aInnerPoly[0] = aRect.BottomLeft();
//STRIP001                     aInnerPoly[1] = aRect.TopLeft();
//STRIP001                     aInnerPoly[2] = aRect.TopCenter();
//STRIP001                     aInnerPoly[3] = aRect.Center();
//STRIP001                     aInnerPoly[4] = aRect.BottomCenter();
//STRIP001                     aInnerPoly[5] = aRect.BottomRight();
//STRIP001                     aInnerPoly[6] = aRect.TopRight();
//STRIP001
//STRIP001                  aInnerPoly.SetFlags(1, XPOLY_CONTROL);
//STRIP001                  aInnerPoly.SetFlags(2, XPOLY_CONTROL);
//STRIP001                  aInnerPoly.SetFlags(3, XPOLY_SMOOTH);
//STRIP001                  aInnerPoly.SetFlags(4, XPOLY_CONTROL);
//STRIP001                  aInnerPoly.SetFlags(5, XPOLY_CONTROL);
//STRIP001
//STRIP001                     aInnerPoly[7] = aRect.BottomRight();
//STRIP001
//STRIP001                  aPoly.Insert(aInnerPoly);
//STRIP001                 }
//STRIP001                 break;
//STRIP001                 case OBJ_POLY:
//STRIP001                 case OBJ_PLIN:
//STRIP001              {
//STRIP001                  XPolygon aInnerPoly;
//STRIP001                     sal_Int32 nWdt(aRect.GetWidth());
//STRIP001                     sal_Int32 nHgt(aRect.GetHeight());
//STRIP001
//STRIP001                     aInnerPoly[0] = aRect.BottomLeft();
//STRIP001                     aInnerPoly[1] = aRect.TopLeft() + Point((nWdt * 30) / 100, (nHgt * 70) / 100);
//STRIP001                     aInnerPoly[2] = aRect.TopLeft() + Point(0, (nHgt * 15) / 100);
//STRIP001                     aInnerPoly[3] = aRect.TopLeft() + Point((nWdt * 65) / 100, 0);
//STRIP001                     aInnerPoly[4] = aRect.TopLeft() + Point(nWdt, (nHgt * 30) / 100);
//STRIP001                     aInnerPoly[5] = aRect.TopLeft() + Point((nWdt * 80) / 100, (nHgt * 50) / 100);
//STRIP001                     aInnerPoly[6] = aRect.TopLeft() + Point((nWdt * 80) / 100, (nHgt * 75) / 100);
//STRIP001                     aInnerPoly[7] = aRect.BottomRight();
//STRIP001
//STRIP001                     if(OBJ_PLIN == eSdrObjectKind)
//STRIP001                  {
//STRIP001                         aInnerPoly[8] = aRect.BottomCenter();
//STRIP001                  }
//STRIP001
//STRIP001                  aPoly.Insert(aInnerPoly);
//STRIP001                 }
//STRIP001                 break;
//STRIP001                 case OBJ_LINE :
//STRIP001                 {
//STRIP001                  aPoly.Insert(XPolygon(2));
//STRIP001                  sal_Int32 nYMiddle((aRect.Top() + aRect.Bottom()) / 2);
//STRIP001                     aPoly[0][0] = Point(aRect.TopLeft().X(), nYMiddle);
//STRIP001                     aPoly[0][1] = Point(aRect.BottomRight().X(), nYMiddle);
//STRIP001                 }
//STRIP001                 break;
//STRIP001          }
//STRIP001
//STRIP001          ((SdrPathObj*)pObj)->SetPathPoly(aPoly);
//STRIP001      }
//STRIP001         else if(pObj->ISA(SdrCaptionObj))
//STRIP001         {
//STRIP001             BOOL bVerticalText = ( SID_DRAW_TEXT_VERTICAL == nSlotId ||
//STRIP001                                             SID_DRAW_CAPTION_VERTICAL == nSlotId );
//STRIP001             ((SdrTextObj*)pObj)->SetVerticalWriting(bVerticalText);
//STRIP001             if(bVerticalText)
//STRIP001             {
//STRIP001                 SfxItemSet aSet(pObj->GetItemSet());
//STRIP001                 aSet.Put(SdrTextVertAdjustItem(SDRTEXTVERTADJUST_CENTER));
//STRIP001                 aSet.Put(SdrTextHorzAdjustItem(SDRTEXTHORZADJUST_RIGHT));
//STRIP001                 pObj->SetItemSet(aSet);
//STRIP001             }
//STRIP001
//STRIP001             ((SdrCaptionObj*)pObj)->SetLogicRect(aRect);
//STRIP001             ((SdrCaptionObj*)pObj)->SetTailPos(
//STRIP001                 aRect.TopLeft() - Point(aRect.GetWidth() / 2, aRect.GetHeight() / 2));
//STRIP001         }
//STRIP001         else if(pObj->ISA(SdrTextObj))
//STRIP001         {
//STRIP001             SdrTextObj* pText = (SdrTextObj*)pObj;
//STRIP001             pText->SetLogicRect(aRect);
//STRIP001
//STRIP001             sal_Bool bVertical = (SID_DRAW_TEXT_VERTICAL == nSlotId);
//STRIP001             sal_Bool bMarquee = (SID_DRAW_TEXT_MARQUEE == nSlotId);
//STRIP001
//STRIP001          pText->SetVerticalWriting(bVertical);
//STRIP001
//STRIP001          if(bVertical)
//STRIP001          {
//STRIP001                 SfxItemSet aSet(pDrawModel->GetItemPool());
//STRIP001              aSet.Put(SdrTextAutoGrowWidthItem(TRUE));
//STRIP001              aSet.Put(SdrTextAutoGrowHeightItem(FALSE));
//STRIP001              aSet.Put(SdrTextVertAdjustItem(SDRTEXTVERTADJUST_TOP));
//STRIP001              aSet.Put(SdrTextHorzAdjustItem(SDRTEXTHORZADJUST_RIGHT));
//STRIP001              pText->SetItemSet(aSet);
//STRIP001          }
//STRIP001
//STRIP001          if(bMarquee)
//STRIP001          {
//STRIP001                 SfxItemSet aSet(pDrawModel->GetItemPool(), SDRATTR_MISC_FIRST, SDRATTR_MISC_LAST);
//STRIP001              aSet.Put( SdrTextAutoGrowWidthItem( FALSE ) );
//STRIP001              aSet.Put( SdrTextAutoGrowHeightItem( FALSE ) );
//STRIP001              aSet.Put( SdrTextAniKindItem( SDRTEXTANI_SLIDE ) );
//STRIP001              aSet.Put( SdrTextAniDirectionItem( SDRTEXTANI_LEFT ) );
//STRIP001              aSet.Put( SdrTextAniCountItem( 1 ) );
//STRIP001                 aSet.Put( SdrTextAniAmountItem( (INT16)GetWin()->PixelToLogic(Size(2,1)).Width()) );
//STRIP001              pObj->SetItemSetAndBroadcast(aSet);
//STRIP001          }
//STRIP001         }
//STRIP001         SdrPageView* pPageView = pDrawView->GetPageViewPvNum(0);
//STRIP001         pDrawView->InsertObject(pObj, *pPageView, pDrawView->IsSolidDraggingNow() ? SDRINSERT_NOBROADCAST : 0);
//STRIP001     }
//STRIP001     ImpEndCreate();
//STRIP001 }

/** SwFEShell::GetShapeBackgrd

    OD 02.09.2002 for #102450#:
    method determines background color of the page the selected drawing
    object is on and returns this color.
    If no color is found, because no drawing object is selected or ...,
    color COL_BLACK (default color on constructing object of class Color)
    is returned.

    @author OD

    @returns an object of class Color
*/
/*?*/ const Color SwFEShell::GetShapeBackgrd() const
/*?*/ {
/*?*/     Color aRetColor;
/*?*/
/*?*/     // check, if a draw view exists
/*?*/     ASSERT( Imp()->GetDrawView(), "wrong usage of SwFEShell::GetShapeBackgrd - no draw view!");
/*?*/     if( Imp()->GetDrawView() )
/*?*/     {
/*?*/         // determine list of selected objects
/*?*/         const SdrMarkList* pMrkList = &Imp()->GetDrawView()->GetMarkList();
/*?*/         // check, if exactly one object is selected.
/*?*/         ASSERT( pMrkList->GetMarkCount() == 1, "wrong usage of SwFEShell::GetShapeBackgrd - no selected object!");
/*?*/         if ( pMrkList->GetMarkCount() == 1)
/*?*/         {
/*?*/             // get selected object
/*?*/             const SdrObject *pSdrObj = pMrkList->GetMark( 0 )->GetObj();
/*?*/             // check, if selected object is a shape (drawing object)
/*?*/             ASSERT( !pSdrObj->IsWriterFlyFrame(), "wrong usage of SwFEShell::GetShapeBackgrd - selected object is not a drawing object!");
/*?*/             if ( !pSdrObj->IsWriterFlyFrame() )
/*?*/             {
/*?*/                 // determine page frame of the frame the shape is anchored.
/*?*/                 const SwFrm* pAnchorFrm =
/*?*/                         static_cast<SwDrawContact*>(GetUserCall(pSdrObj))->GetAnchor();
/*?*/                 ASSERT( pAnchorFrm, "inconsistent modell - no anchor at shape!");
/*?*/                 if ( pAnchorFrm )
/*?*/                 {
/*?*/                     const SwPageFrm* pPageFrm = pAnchorFrm->FindPageFrm();
/*?*/                     ASSERT( pPageFrm, "inconsistent modell - no page!");
/*?*/                     if ( pPageFrm )
/*?*/                     {
/*?*/                        DBG_BF_ASSERT(0, "STRIP"); //STRIP001  aRetColor = pPageFrm->GetDrawBackgrdColor();
/*?*/                     }
/*?*/                 }
/*?*/             }
/*?*/         }
/*?*/     }
/*?*/
/*?*/     return aRetColor;
/*?*/ }

/** Is default horizontal text direction for selected drawing object right-to-left

    OD 09.12.2002 #103045#
    Because drawing objects only painted for each page only, the default
    horizontal text direction of a drawing object is given by the corresponding
    page property.

    @author OD

    @returns boolean, indicating, if the horizontal text direction of the
    page, the selected drawing object is on, is right-to-left.
*/
//STRIP001 const bool SwFEShell::IsShapeDefaultHoriTextDirR2L() const
//STRIP001 {
//STRIP001     bool bRet = false;
//STRIP001
//STRIP001     // check, if a draw view exists
//STRIP001     ASSERT( Imp()->GetDrawView(), "wrong usage of SwFEShell::GetShapeBackgrd - no draw view!");
//STRIP001     if( Imp()->GetDrawView() )
//STRIP001     {
//STRIP001         // determine list of selected objects
//STRIP001         const SdrMarkList* pMrkList = &Imp()->GetDrawView()->GetMarkList();
//STRIP001         // check, if exactly one object is selected.
//STRIP001         ASSERT( pMrkList->GetMarkCount() == 1, "wrong usage of SwFEShell::GetShapeBackgrd - no selected object!");
//STRIP001         if ( pMrkList->GetMarkCount() == 1)
//STRIP001         {
//STRIP001             // get selected object
//STRIP001             const SdrObject *pSdrObj = pMrkList->GetMark( 0 )->GetObj();
//STRIP001             // check, if selected object is a shape (drawing object)
//STRIP001             ASSERT( !pSdrObj->IsWriterFlyFrame(), "wrong usage of SwFEShell::GetShapeBackgrd - selected object is not a drawing object!");
//STRIP001             if ( !pSdrObj->IsWriterFlyFrame() )
//STRIP001             {
//STRIP001                 // determine page frame of the frame the shape is anchored.
//STRIP001                 const SwFrm* pAnchorFrm =
//STRIP001                         static_cast<SwDrawContact*>(GetUserCall(pSdrObj))->GetAnchor();
//STRIP001                 ASSERT( pAnchorFrm, "inconsistent modell - no anchor at shape!");
//STRIP001                 if ( pAnchorFrm )
//STRIP001                 {
//STRIP001                     const SwPageFrm* pPageFrm = pAnchorFrm->FindPageFrm();
//STRIP001                     ASSERT( pPageFrm, "inconsistent modell - no page!");
//STRIP001                     if ( pPageFrm )
//STRIP001                     {
//STRIP001                         bRet = pPageFrm->IsRightToLeft() ? true : false;
//STRIP001                     }
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001     }
//STRIP001
//STRIP001     return bRet;
//STRIP001 }
/* -----------------20.03.2003 14:35-----------------

 --------------------------------------------------*/
//STRIP001 Point SwFEShell::GetRelativePagePosition(const Point& rDocPos)
//STRIP001 {
//STRIP001     Point aRet(-1, -1);
//STRIP001     const SwFrm *pPage = GetLayout()->Lower();
//STRIP001     while ( pPage && !pPage->Frm().IsInside( rDocPos ) )
//STRIP001     {
//STRIP001         pPage = pPage->GetNext();
//STRIP001     }
//STRIP001     if(pPage)
//STRIP001     {
//STRIP001         aRet = rDocPos - pPage->Frm().TopLeft();
//STRIP001     }
//STRIP001     return aRet;
//STRIP001 }

}
