/*************************************************************************
 *
 *  $RCSfile: sw_trvlfrm.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:50:35 $
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

#ifndef _BIGINT_HXX //autogen
#include <tools/bigint.hxx>
#endif
#ifndef _SVX_PROTITEM_HXX //autogen
#include <bf_svx/protitem.hxx>
#endif
#ifndef _SV_SETTINGS_HXX //autogen
#include <vcl/settings.hxx>
#endif
#ifndef _SV_OUTDEV_HXX //autogen
#include <vcl/outdev.hxx>
#endif
#ifndef _FMTPDSC_HXX //autogen
#include <fmtpdsc.hxx>
#endif
#ifndef _FMTSRND_HXX //autogen
#include <fmtsrnd.hxx>
#endif
#ifndef _PAGEDESC_HXX
#include <pagedesc.hxx>
#endif

#ifndef _PAGEFRM_HXX //autogen
#include <pagefrm.hxx>
#endif
#ifndef _ROOTFRM_HXX //autogen
#include <rootfrm.hxx>
#endif
#ifndef _CNTFRM_HXX //autogen
#include <cntfrm.hxx>
#endif
#ifndef _FTNFRM_HXX //autogen
#include <ftnfrm.hxx>
#endif
#ifndef _FLYFRM_HXX //autogen
#include <flyfrm.hxx>
#endif
#ifndef _TABFRM_HXX //autogen
#include <tabfrm.hxx>
#endif
#ifndef _CELLFRM_HXX //autogen
#include <cellfrm.hxx>
#endif
#ifndef _TXTFRM_HXX //autogen
#include <txtfrm.hxx>
#endif
#ifndef _VIEWSH_HXX //autogen
#include <viewsh.hxx>
#endif
#ifndef _DOC_HXX //autogen
#include <doc.hxx>
#endif
#ifndef _VISCRS_HXX //autogen
#include <viscrs.hxx>
#endif
#ifndef _PAM_HXX //autogen
#include <pam.hxx>
#endif
#ifndef _NODE_HXX //autogen
#include <node.hxx>
#endif
#ifndef _FRMFMT_HXX //autogen
#include <frmfmt.hxx>
#endif
#ifndef _SWTABLE_HXX //autogen
#include <swtable.hxx>
#endif
#ifndef _DFLYOBJ_HXX //autogen
#include <dflyobj.hxx>
#endif
#ifndef _CRSTATE_HXX //autogen
#include <crstate.hxx>
#endif
#ifndef _FRMTOOL_HXX //autogen
#include <frmtool.hxx>
#endif
#ifndef _HINTS_HXX //autogen
#include <hints.hxx>
#endif
#ifndef _FRMSH_HXX
#include <frmsh.hxx>
#endif
namespace binfilter {


//Fuer SwFlyFrm::GetCrsrOfst
//STRIP001 class SwCrsrOszControl
//STRIP001 {
//STRIP001 public:
//STRIP001  // damit schon der Compiler die Klasse initialisieren kann, keinen
//STRIP001  // DTOR und member als publics:
//STRIP001  const SwFlyFrm *pEntry;
//STRIP001  const SwFlyFrm *pStk1;
//STRIP001  const SwFlyFrm *pStk2;
//STRIP001
//STRIP001 //public:
//STRIP001 //    SwCrsrOszControl() : pStk1( 0 ), pStk2( 0 ) {}; // ; <- ????
//STRIP001
//STRIP001  BOOL ChkOsz( const SwFlyFrm *pFly )
//STRIP001      {
//STRIP001          BOOL bRet = TRUE;
//STRIP001          if ( pFly != pStk1 && pFly != pStk2 )
//STRIP001          {
//STRIP001              pStk1 = pStk2;
//STRIP001              pStk2 = pFly;
//STRIP001              bRet  = FALSE;
//STRIP001          }
//STRIP001          return bRet;
//STRIP001      }
//STRIP001  void Entry( const SwFlyFrm *pFly )
//STRIP001      {
//STRIP001          if ( !pEntry )
//STRIP001              pEntry = pStk1 = pFly;
//STRIP001      }
//STRIP001  void Exit( const SwFlyFrm *pFly )
//STRIP001      {
//STRIP001          if ( pFly == pEntry )
//STRIP001              pEntry = pStk1 = pStk2 = 0;
//STRIP001      }
//STRIP001 };

//STRIP001 static SwCrsrOszControl aOszCtrl = { 0, 0, 0 };

/*************************************************************************
|*
|*  SwLayoutFrm::GetCrsrOfst()
|*
|*  Beschreibung:       Sucht denjenigen CntntFrm, innerhalb dessen
|*                      PrtArea der Point liegt.
|*  Ersterstellung      MA 20. Jul. 92
|*  Letzte Aenderung    MA 23. May. 95
|*
|*************************************************************************/
//STRIP001 BOOL SwLayoutFrm::GetCrsrOfst( SwPosition *pPos, Point &rPoint,
//STRIP001                          const SwCrsrMoveState* pCMS ) const
//STRIP001 {
//STRIP001  BOOL bRet = FALSE;
//STRIP001  const SwFrm *pFrm = Lower();
//STRIP001  while ( !bRet && pFrm )
//STRIP001  {   pFrm->Calc();
//STRIP001      SwRect aPaintRect( pFrm->PaintArea() );
//STRIP001      if ( aPaintRect.IsInside( rPoint ) &&
//STRIP001          pFrm->GetCrsrOfst( pPos, rPoint, pCMS ) )
//STRIP001          bRet = TRUE;
//STRIP001      else
//STRIP001          pFrm = pFrm->GetNext();
//STRIP001      if ( pCMS && pCMS->bStop )
//STRIP001          return FALSE;
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }

/*************************************************************************
|*
|*  SwPageFrm::GetCrsrOfst()
|*
|*  Beschreibung:       Sucht die Seite, innerhalb der der gesuchte Point
|*                      liegt.
|*  Ersterstellung      MA 20. Jul. 92
|*  Letzte Aenderung    MA 18. Jul. 96
|*
|*************************************************************************/
//STRIP001 #pragma optimize("e",off)

//STRIP001 BOOL SwPageFrm::GetCrsrOfst( SwPosition *pPos, Point &rPoint,
//STRIP001                          const SwCrsrMoveState* pCMS ) const
//STRIP001 {
//STRIP001  BOOL bRet     = FALSE;
//STRIP001  const SwPageFrm *pPage = this;
//STRIP001  Point aStPoint( rPoint );
//STRIP001  Point aPoint;
//STRIP001  while ( !bRet && pPage )
//STRIP001  {
//STRIP001      aPoint = aStPoint;
//STRIP001         SwTwips nTmp = pPage->Frm().Top();
//STRIP001      if ( pPage->GetPrev() )
//STRIP001      {
//STRIP001             const SwTwips nPreTmp = pPage->GetPrev()->Frm().Bottom();
//STRIP001             if ( (aPoint.Y() > nPreTmp) &&
//STRIP001                  (aPoint.Y() < nTmp)    &&
//STRIP001                  ((aPoint.Y() - nPreTmp) >= (nTmp - aPoint.Y())) )
//STRIP001                 aPoint.Y() = nTmp;
//STRIP001      }
//STRIP001         else if ( aPoint.Y() < nTmp )
//STRIP001             aPoint.Y() = nTmp;
//STRIP001
//STRIP001         nTmp = pPage->Frm().Bottom();
//STRIP001      if ( pPage->GetNext() )
//STRIP001      {
//STRIP001             const SwTwips nNxtTmp = pPage->GetNext()->Frm().Top();
//STRIP001             if ( (aPoint.Y() > nTmp) &&
//STRIP001                  (aPoint.Y() < nNxtTmp) &&
//STRIP001                  ((nNxtTmp - aPoint.Y()) >= (aPoint.Y() - nTmp)) )
//STRIP001                 aPoint.Y() = nTmp;
//STRIP001      }
//STRIP001         else if ( aPoint.Y() > nTmp )
//STRIP001             aPoint.Y() = nTmp;
//STRIP001
//STRIP001      //Wenn der Punkt in der Fix-Richtung neben der Seite liegt wird er
//STRIP001      //hineingezogen.
//STRIP001         const SwTwips nVarA = pPage->Frm().Pos().X();
//STRIP001         const SwTwips nVarB = pPage->Frm().Right();
//STRIP001         if ( nVarA > aPoint.X() )
//STRIP001             aPoint.X() = nVarA;
//STRIP001         else if ( nVarB < aPoint.X() )
//STRIP001             aPoint.X() = nVarB;
//STRIP001
//STRIP001      //Weitere versuche mit der aktuellen Seite nur dann, wenn sich der
//STRIP001      //Point innerhalb der Seite befindet.
//STRIP001      const BOOL bInside = pPage->Frm().IsInside( aPoint );
//STRIP001
//STRIP001      //Koennte ein Freifliegender gemeint sein?
//STRIP001      //Wenn sein Inhalt geschuetzt werden soll, so ist nix mit Crsr
//STRIP001      //hineinsetzen, dadurch sollten alle Aenderungen unmoeglich sein.
//STRIP001      if ( bInside && pPage->GetSortedObjs() )
//STRIP001      {
//STRIP001          SwOrderIter aIter( pPage );
//STRIP001          aIter.Top();
//STRIP001          while ( aIter() )
//STRIP001          {
//STRIP001              SwVirtFlyDrawObj *pObj = (SwVirtFlyDrawObj*)aIter();
//STRIP001              SwFlyFrm *pFly = pObj ? pObj->GetFlyFrm() : 0;
//STRIP001              if ( pFly &&
//STRIP001                   ((pCMS?pCMS->bSetInReadOnly:FALSE) ||
//STRIP001                    !pFly->IsProtected())
//STRIP001                   && pFly->GetCrsrOfst( pPos, aPoint, pCMS ) )
//STRIP001              {
//STRIP001                  bRet = TRUE;
//STRIP001                  break;
//STRIP001              }
//STRIP001              if ( pCMS && pCMS->bStop )
//STRIP001                  return FALSE;
//STRIP001              aIter.Prev();
//STRIP001          }
//STRIP001      }
//STRIP001      if ( !bRet && bInside )
//STRIP001      {
//STRIP001          //Wenn kein Cntnt unterhalb der Seite 'antwortet', so korrigieren
//STRIP001          //wir den StartPoint und fangen nochmal eine Seite vor der
//STRIP001          //aktuellen an. Mit Flys ist es dann allerdings vorbei.
//STRIP001          if ( pPage->SwLayoutFrm::GetCrsrOfst( pPos, aPoint, pCMS ) )
//STRIP001              bRet = TRUE;
//STRIP001          else
//STRIP001          {
//STRIP001              if ( pCMS && (pCMS->bStop || pCMS->bExactOnly) )
//STRIP001              {
//STRIP001                  ((SwCrsrMoveState*)pCMS)->bStop = TRUE;
//STRIP001                  return FALSE;
//STRIP001              }
//STRIP001              const SwCntntFrm *pCnt = pPage->GetCntntPos(
//STRIP001                                  aPoint, FALSE, FALSE, FALSE, pCMS, FALSE );
//STRIP001              if ( pCMS && pCMS->bStop )
//STRIP001                  return FALSE;
//STRIP001              ASSERT( pCnt, "Crsr is gone to a Black hole" );
//STRIP001              if( pCMS && pCMS->pFill && pCnt->IsTxtFrm() )
//STRIP001                  pCnt->GetCrsrOfst( pPos, rPoint, pCMS );
//STRIP001              else
//STRIP001                  pCnt->GetCrsrOfst( pPos, aPoint, pCMS );
//STRIP001              bRet = TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001      pPage = (const SwPageFrm*)pPage->GetNext();
//STRIP001  }
//STRIP001  if ( bRet )
//STRIP001      rPoint = aPoint;
//STRIP001  return bRet;
//STRIP001 }
//STRIP001
//STRIP001 #pragma optimize("",on)

/*************************************************************************
|*
|*  SwRootFrm::GetCrsrOfst()
|*
|*  Beschreibung:       Reicht Primaer den Aufruf an die erste Seite weiter.
|*                      Wenn der 'reingereichte Point veraendert wird,
|*                      so wird FALSE zurueckgegeben.
|*  Ersterstellung      MA 01. Jun. 92
|*  Letzte Aenderung    MA 30. Nov. 94
|*
|*************************************************************************/
//STRIP001 BOOL SwRootFrm::GetCrsrOfst( SwPosition *pPos, Point &rPoint,
//STRIP001                          const SwCrsrMoveState* pCMS ) const
//STRIP001 {
//STRIP001  sal_Bool bOldAction = IsCallbackActionEnabled();
//STRIP001  ((SwRootFrm*)this)->SetCallbackActionEnabled( FALSE );
//STRIP001  ASSERT( (Lower() && Lower()->IsPageFrm()), "Keinen PageFrm gefunden." );
//STRIP001  if( pCMS && pCMS->pFill )
//STRIP001      ((SwCrsrMoveState*)pCMS)->bFillRet = FALSE;
//STRIP001  Point aOldPoint = rPoint;
//STRIP001  const SwPageFrm *pPage = (SwPageFrm*)Lower();
//STRIP001  pPage->SwPageFrm::GetCrsrOfst( pPos, rPoint, pCMS );
//STRIP001  ((SwRootFrm*)this)->SetCallbackActionEnabled( bOldAction );
//STRIP001  if( pCMS )
//STRIP001  {
//STRIP001      if( pCMS->bStop )
//STRIP001          return FALSE;
//STRIP001      if( pCMS->pFill )
//STRIP001          return pCMS->bFillRet;
//STRIP001  }
//STRIP001  return aOldPoint == rPoint;
//STRIP001 }

/*************************************************************************
|*
|*  SwCellFrm::GetCrsrOfst()
|*
|*  Beschreibung        Wenn es sich um eine Cntnt-tragende Cell handelt wird
|*                      der Crsr notfalls mit Gewalt in einen der CntntFrms
|*                      gesetzt.
|*                      In geschuetzte Zellen gibt es hier keinen Eingang.
|*  Ersterstellung      MA 04. Jun. 93
|*  Letzte Aenderung    MA 23. May. 95
|*
|*************************************************************************/
//STRIP001 BOOL SwCellFrm::GetCrsrOfst( SwPosition *pPos, Point &rPoint,
//STRIP001                          const SwCrsrMoveState* pCMS ) const
//STRIP001 {
//STRIP001  ASSERT( Lower(), "Zelle ohne Inhalt." );
//STRIP001
//STRIP001  if ( !(pCMS?pCMS->bSetInReadOnly:FALSE) &&
//STRIP001       GetFmt()->GetProtect().IsCntntProtected() )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  if ( pCMS && pCMS->eState == MV_TBLSEL )
//STRIP001  {
//STRIP001      const SwTabFrm *pTab = FindTabFrm();
//STRIP001      if ( pTab->IsFollow() && pTab->GetTable()->IsHeadlineRepeat() &&
//STRIP001           ((SwLayoutFrm*)pTab->Lower())->IsAnLower( this ) )
//STRIP001      {
//STRIP001          ((SwCrsrMoveState*)pCMS)->bStop = TRUE;
//STRIP001          return FALSE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if ( Lower()->IsLayoutFrm() )
//STRIP001      return SwLayoutFrm::GetCrsrOfst( pPos, rPoint, pCMS );
//STRIP001  else
//STRIP001  {
//STRIP001      Calc();
//STRIP001      BOOL bRet = FALSE;
//STRIP001
//STRIP001      const SwFrm *pFrm = Lower();
//STRIP001      while ( pFrm && !bRet )
//STRIP001      {
//STRIP001          pFrm->Calc();
//STRIP001          if ( pFrm->Frm().IsInside( rPoint ) )
//STRIP001          {
//STRIP001              bRet = pFrm->GetCrsrOfst( pPos, rPoint, pCMS );
//STRIP001              if ( pCMS && pCMS->bStop )
//STRIP001                  return FALSE;
//STRIP001          }
//STRIP001          pFrm = pFrm->GetNext();
//STRIP001      }
//STRIP001      if ( !bRet )
//STRIP001      {
//STRIP001          Point *pPoint = pCMS && pCMS->pFill ? new Point( rPoint ) : NULL;
//STRIP001          const SwCntntFrm *pCnt = GetCntntPos( rPoint, TRUE );
//STRIP001          if( pPoint && pCnt->IsTxtFrm() )
//STRIP001          {
//STRIP001              pCnt->GetCrsrOfst( pPos, *pPoint, pCMS );
//STRIP001              rPoint = *pPoint;
//STRIP001          }
//STRIP001          else
//STRIP001              pCnt->GetCrsrOfst( pPos, rPoint, pCMS );
//STRIP001          delete pPoint;
//STRIP001      }
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*  SwFlyFrm::GetCrsrOfst()
|*
|*  Ersterstellung      MA 15. Dec. 92
|*  Letzte Aenderung    MA 23. May. 95
|*
|*************************************************************************/
//Problem: Wenn zwei Flys genau gleich gross sind und auf derselben
//Position stehen, so liegt jeder innerhalb des anderen.
//Da jeweils geprueft wird, ob der Point nicht zufaellig innerhalb eines
//anderen Flys liegt, der sich vollstaendig innerhalb des aktuellen befindet
//und ggf. ein rekursiver Aufruf erfolgt wuerde o.g. Situation zu einer
//endlosen Rekursion fuehren.
//Mit der Hilfsklasse SwCrsrOszControl unterbinden wir die Rekursion. Das
//GetCrsrOfst entscheidet sich bei einer Rekursion fuer denjenigen der
//am weitesten oben liegt.

//STRIP001 BOOL SwFlyFrm::GetCrsrOfst( SwPosition *pPos, Point &rPoint,
//STRIP001                          const SwCrsrMoveState* pCMS ) const
//STRIP001 {
//STRIP001  aOszCtrl.Entry( this );
//STRIP001
//STRIP001  //Wenn der Point innerhalb des Fly sitzt wollen wir energisch
//STRIP001  //versuchen den Crsr hineinzusetzen.
//STRIP001  //Wenn der Point allerdings in einem Flys sitzt, der sich vollstaendig
//STRIP001  //innerhalb des aktuellen befindet, so wird fuer diesen das
//STRIP001  //GetCrsrOfst gerufen.
//STRIP001  Calc();
//STRIP001  BOOL bInside = Frm().IsInside( rPoint ) && Lower(),
//STRIP001       bRet = FALSE;
//STRIP001
//STRIP001  //Wenn der Frm eine Grafik enthaelt, aber nur Text gewuenscht ist, so
//STRIP001  //nimmt er den Crsr grundsaetzlich nicht an.
//STRIP001  if ( bInside && pCMS && pCMS->eState == MV_SETONLYTEXT &&
//STRIP001       (!Lower() || Lower()->IsNoTxtFrm()) )
//STRIP001      bInside = FALSE;
//STRIP001
//STRIP001  const SwPageFrm *pPage = FindPageFrm();
//STRIP001  if ( bInside && pPage && pPage->GetSortedObjs() )
//STRIP001  {
//STRIP001      SwOrderIter aIter( pPage );
//STRIP001      aIter.Top();
//STRIP001      while ( aIter() && !bRet )
//STRIP001      {
//STRIP001          SwVirtFlyDrawObj *pObj = (SwVirtFlyDrawObj*)aIter();
//STRIP001          SwFlyFrm *pFly = pObj ? pObj->GetFlyFrm() : 0;
//STRIP001          if ( pFly && pFly->Frm().IsInside( rPoint ) &&
//STRIP001               Frm().IsInside( pFly->Frm() ) )
//STRIP001          {
//STRIP001              if ( aOszCtrl.ChkOsz( pFly ) ||
//STRIP001                   TRUE == (bRet = pFly->GetCrsrOfst( pPos, rPoint, pCMS )))
//STRIP001                  break;
//STRIP001              if ( pCMS && pCMS->bStop )
//STRIP001                  return FALSE;
//STRIP001          }
//STRIP001          aIter.Next();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  while ( bInside && !bRet )
//STRIP001  {
//STRIP001      const SwFrm *pFrm = Lower();
//STRIP001      while ( pFrm && !bRet )
//STRIP001      {
//STRIP001          pFrm->Calc();
//STRIP001          if ( pFrm->Frm().IsInside( rPoint ) )
//STRIP001          {
//STRIP001              bRet = pFrm->GetCrsrOfst( pPos, rPoint, pCMS );
//STRIP001              if ( pCMS && pCMS->bStop )
//STRIP001                  return FALSE;
//STRIP001          }
//STRIP001          pFrm = pFrm->GetNext();
//STRIP001      }
//STRIP001      if ( !bRet )
//STRIP001      {
//STRIP001          Point *pPoint = pCMS && pCMS->pFill ? new Point( rPoint ) : NULL;
//STRIP001          const SwCntntFrm *pCnt = GetCntntPos(
//STRIP001                                          rPoint, TRUE, FALSE, FALSE, pCMS );
//STRIP001          if ( pCMS && pCMS->bStop )
//STRIP001              return FALSE;
//STRIP001          if( pPoint && pCnt->IsTxtFrm() )
//STRIP001          {
//STRIP001              pCnt->GetCrsrOfst( pPos, *pPoint, pCMS );
//STRIP001              rPoint = *pPoint;
//STRIP001          }
//STRIP001          else
//STRIP001              pCnt->GetCrsrOfst( pPos, rPoint, pCMS );
//STRIP001          delete pPoint;
//STRIP001          bRet = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  aOszCtrl.Exit( this );
//STRIP001  return bRet;
//STRIP001 }

/*************************************************************************
|*
|*    Beschreibung      Layoutabhaengiges Cursortravelling
|*    Ersterstellung    MA 23. Jul. 92
|*    Letzte Aenderung  MA 06. Sep. 93
|*
|*************************************************************************/
//STRIP001 BOOL SwCntntFrm::LeftMargin(SwPaM *pPam) const
//STRIP001 {
//STRIP001  if( pPam->GetNode() != (SwCntntNode*)GetNode() )
//STRIP001      return FALSE;
//STRIP001  ((SwCntntNode*)GetNode())->
//STRIP001      MakeStartIndex((SwIndex *) &pPam->GetPoint()->nContent);
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 BOOL SwCntntFrm::RightMargin(SwPaM *pPam, BOOL) const
//STRIP001 {
//STRIP001  if( pPam->GetNode() != (SwCntntNode*)GetNode() )
//STRIP001      return FALSE;
//STRIP001  ((SwCntntNode*)GetNode())->
//STRIP001      MakeEndIndex((SwIndex *) &pPam->GetPoint()->nContent);
//STRIP001  return TRUE;
//STRIP001 }

/*N*/ const SwCntntFrm *lcl_GetNxtCnt( const SwCntntFrm* pCnt )
/*N*/ {
/*N*/   return pCnt->GetNextCntntFrm();
/*N*/ }

//STRIP001 const SwCntntFrm *lcl_GetPrvCnt( const SwCntntFrm* pCnt )
//STRIP001 {
//STRIP001  return pCnt->GetPrevCntntFrm();
//STRIP001 }

/*N*/ typedef const SwCntntFrm *(*GetNxtPrvCnt)( const SwCntntFrm* );

//Frame in wiederholter Headline?
/*N*/ FASTBOOL lcl_IsInRepeatedHeadline( const SwFrm *pFrm,
/*N*/                                   const SwTabFrm** ppTFrm = 0 )
/*N*/ {DBG_ASSERT(0, "STRIP"); return FALSE;//STRIP001
//STRIP001  const SwTabFrm *pTab = pFrm->FindTabFrm();
//STRIP001  if( ppTFrm )
//STRIP001      *ppTFrm = pTab;
//STRIP001  return pTab && pTab->IsFollow() &&
//STRIP001         pTab->GetTable()->IsHeadlineRepeat() &&
//STRIP001         ((SwLayoutFrm*)pTab->Lower())->IsAnLower( pFrm );
/*N*/ }


//Ueberspringen geschuetzter Tabellenzellen. Optional auch
//Ueberspringen von wiederholten Headlines.
//MA 26. Jan. 98: Chg auch andere Geschuetzte Bereiche ueberspringen.
/*N*/ const SwCntntFrm * MA_FASTCALL lcl_MissProtectedFrames( const SwCntntFrm *pCnt,
/*N*/                                                      GetNxtPrvCnt fnNxtPrv,
/*N*/                                                      FASTBOOL bMissHeadline,
/*N*/                                                      FASTBOOL bInReadOnly )
/*N*/ {
/*N*/   if ( pCnt && pCnt->IsInTab() )
/*N*/   {
/*N*/       BOOL bProtect = TRUE;
/*N*/       while ( pCnt && bProtect )
/*N*/       {
/*N*/           const SwLayoutFrm *pCell = pCnt->GetUpper();
/*N*/           while ( pCell && !pCell->IsCellFrm() )
/*?*/               pCell = pCell->GetUpper();
/*N*/           if ( !pCell ||
/*N*/                   ((bInReadOnly || !pCell->GetFmt()->GetProtect().IsCntntProtected()) &&
/*N*/                    (!bMissHeadline || !lcl_IsInRepeatedHeadline( pCell ) )))
/*N*/               bProtect = FALSE;
/*N*/           else
/*?*/               pCnt = (*fnNxtPrv)( pCnt );
/*N*/       }
/*N*/   }
/*N*/   else if ( !bInReadOnly )
/*N*/       while ( pCnt && pCnt->IsProtected() )
/*N*/           pCnt = (*fnNxtPrv)( pCnt );
/*N*/
/*N*/   return pCnt;
/*N*/ }

//STRIP001 BOOL MA_FASTCALL lcl_UpDown( SwPaM *pPam, const SwCntntFrm *pStart,
//STRIP001                  GetNxtPrvCnt fnNxtPrv, BOOL bInReadOnly )
//STRIP001 {
//STRIP001  ASSERT( pPam->GetNode() == (SwCntntNode*)pStart->GetNode(),
//STRIP001          "lcl_UpDown arbeitet nicht fuer andere." );
//STRIP001
//STRIP001  const SwCntntFrm *pCnt = 0;
//STRIP001
//STRIP001  //Wenn gerade eine Tabellenselection laeuft muss ein bischen getricktst
//STRIP001  //werden: Beim hochlaufen an den Anfang der Zelle gehen, beim runterlaufen
//STRIP001  //an das Ende der Zelle gehen.
//STRIP001  if ( pStart->IsInTab() &&
//STRIP001      pPam->GetNode( TRUE )->StartOfSectionNode() !=
//STRIP001      pPam->GetNode( FALSE )->StartOfSectionNode() )
//STRIP001  {
//STRIP001      const SwLayoutFrm  *pCell = pStart->GetUpper();
//STRIP001      while ( !pCell->IsCellFrm() )
//STRIP001          pCell = pCell->GetUpper();
//STRIP001      const SwCntntFrm *pNxt = pCnt = pStart;
//STRIP001      while ( pCell->IsAnLower( pNxt ) )
//STRIP001      {   pCnt = pNxt;
//STRIP001          pNxt = (*fnNxtPrv)( pNxt );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  pCnt = (*fnNxtPrv)( pCnt ? pCnt : pStart );
//STRIP001  pCnt = ::lcl_MissProtectedFrames( pCnt, fnNxtPrv, TRUE, bInReadOnly );
//STRIP001
//STRIP001
//STRIP001  const SwTabFrm *pStTab = pStart->FindTabFrm();
//STRIP001  const SwTabFrm *pTable;
//STRIP001  const BOOL bTab = pStTab || (pCnt && pCnt->IsInTab()) ? TRUE : FALSE;
//STRIP001  BOOL bEnd = bTab ? FALSE : TRUE;
//STRIP001
//STRIP001     SWRECTFN( pStart )
//STRIP001
//STRIP001  SwTwips nX;
//STRIP001  if ( bTab )
//STRIP001  {
//STRIP001      SwRect aRect( pStart->Frm() );
//STRIP001      pStart->GetCharRect( aRect, *pPam->GetPoint() );
//STRIP001         Point aCenter = aRect.Center();
//STRIP001         nX = bVert ? aCenter.Y() : aCenter.X();
//STRIP001
//STRIP001      const SwTabFrm *pTab = pCnt ? pCnt->FindTabFrm() : 0;
//STRIP001      if ( !pTab )
//STRIP001          pTab = pStTab;
//STRIP001      pTable = pTab;
//STRIP001
//STRIP001 #ifdef BIDI
//STRIP001      const sal_Bool bRTL = pTable->IsRightToLeft();
//STRIP001 #endif
//STRIP001
//STRIP001      if ( pStTab )
//STRIP001      {
//STRIP001          //Der Fluss fuehrt von einer Tabelle in die nachste. Der X-Wert
//STRIP001          //muss ausgehend von der Mitte der Startzelle um die Verschiebung
//STRIP001          //der Tabellen korrigiert werden.
//STRIP001          const SwFrm *pCell = pStart->GetUpper();
//STRIP001          while ( pCell && !pCell->IsCellFrm() )
//STRIP001              pCell = pCell->GetUpper();
//STRIP001          ASSERT( pCell, "Zelle nicht gefunden." );
//STRIP001          nX =  (pCell->Frm().*fnRect->fnGetLeft)() +
//STRIP001                (pCell->Frm().*fnRect->fnGetWidth)() / 2;
//STRIP001          nX += (pTab->Frm().*fnRect->fnGetLeft)() -
//STRIP001                   (pStTab->Frm().*fnRect->fnGetLeft)();
//STRIP001      }
//STRIP001
//STRIP001      const SwCntntFrm *pTmp = pTab->ContainsCntnt();
//STRIP001 #ifdef BIDI
//STRIP001      const long nPrtLeft = bRTL ?
//STRIP001                               (pTmp->*fnRect->fnGetPrtRight)() :
//STRIP001                            (pTmp->*fnRect->fnGetPrtLeft)();
//STRIP001      if ( bRTL != nX < nPrtLeft )
//STRIP001          nX = nPrtLeft;
//STRIP001      else
//STRIP001      {
//STRIP001          pTmp = pTab->FindLastCntnt();
//STRIP001          const long nPrtRight = bRTL ?
//STRIP001                                    (pTmp->*fnRect->fnGetPrtLeft)() :
//STRIP001                                    (pTmp->*fnRect->fnGetPrtRight)();
//STRIP001             if ( bRTL != nX > nPrtRight )
//STRIP001              nX = nPrtRight;
//STRIP001      }
//STRIP001 #else
//STRIP001         const long nPrtLeft = (pTmp->*fnRect->fnGetPrtLeft)();
//STRIP001         if ( nX < nPrtLeft )
//STRIP001             nX = nPrtLeft;
//STRIP001         else
//STRIP001         {
//STRIP001             pTmp = pTab->FindLastCntnt();
//STRIP001             const long nPrtRight = (pTmp->*fnRect->fnGetPrtRight)();
//STRIP001             if ( nX > nPrtRight )
//STRIP001                 nX = nPrtRight;
//STRIP001         }
//STRIP001 #endif
//STRIP001  }
//STRIP001  do
//STRIP001  {
//STRIP001      //Wenn ich im DokumentBody bin, so will ich da auch bleiben
//STRIP001      if ( pStart->IsInDocBody() )
//STRIP001          while ( pCnt && (!pCnt->IsInDocBody() ||
//STRIP001                           (pCnt->IsTxtFrm() && ((SwTxtFrm*)pCnt)->IsHiddenNow())))
//STRIP001          {
//STRIP001              pCnt = (*fnNxtPrv)( pCnt );
//STRIP001              pCnt = ::lcl_MissProtectedFrames( pCnt, fnNxtPrv, TRUE, bInReadOnly );
//STRIP001          }
//STRIP001
//STRIP001      //Wenn ich im Fussnotenbereich bin, so versuche ich notfalls den naechsten
//STRIP001      //Fussnotenbereich zu erreichen.
//STRIP001      else if ( pStart->IsInFtn() )
//STRIP001          while ( pCnt && !pCnt->IsInFtn() )
//STRIP001          {
//STRIP001              pCnt = (*fnNxtPrv)( pCnt );
//STRIP001              pCnt = ::lcl_MissProtectedFrames( pCnt, fnNxtPrv, TRUE, bInReadOnly );
//STRIP001          }
//STRIP001
//STRIP001      //In Flys kann es Blind weitergehen solange ein Cntnt
//STRIP001      //gefunden wird.
//STRIP001      else if ( pStart->IsInFly() )
//STRIP001      {
//STRIP001          if ( pCnt && pCnt->IsTxtFrm() && ((SwTxtFrm*)pCnt)->IsHiddenNow() )
//STRIP001          {
//STRIP001              pCnt = (*fnNxtPrv)( pCnt );
//STRIP001              pCnt = ::lcl_MissProtectedFrames( pCnt, fnNxtPrv, TRUE, bInReadOnly );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      //Andernfalls weigere ich mich einfach den derzeitigen Bereich zu
//STRIP001      //verlassen.
//STRIP001      else if ( pCnt )
//STRIP001      {
//STRIP001          const SwFrm *pUp = pStart->GetUpper();               //Head/Foot
//STRIP001          while ( pUp && pUp->GetUpper() && !(pUp->GetType() & 0x0018 ) )
//STRIP001              pUp = pUp->GetUpper();
//STRIP001          BOOL bSame = FALSE;
//STRIP001          const SwFrm *pCntUp = pCnt->GetUpper();
//STRIP001          while ( pCntUp && !bSame )
//STRIP001          {   if ( pUp == pCntUp )
//STRIP001                  bSame = TRUE;
//STRIP001              else
//STRIP001                  pCntUp = pCntUp->GetUpper();
//STRIP001          }
//STRIP001          if ( !bSame )
//STRIP001              pCnt = 0;
//STRIP001      }
//STRIP001
//STRIP001      if ( bTab )
//STRIP001      {
//STRIP001          if ( !pCnt )
//STRIP001              bEnd = TRUE;
//STRIP001          else
//STRIP001          {   const SwTabFrm *pTab = pCnt->FindTabFrm();
//STRIP001              if( !pTab )
//STRIP001                  bEnd = TRUE;
//STRIP001              else
//STRIP001              {
//STRIP001                  if ( pTab != pTable )
//STRIP001                  {   //Der Fluss fuehrt von einer Tabelle in die nachste. Der
//STRIP001                      //X-Wert muss um die Verschiebung der Tabellen korrigiert
//STRIP001                      //werden.
//STRIP001                      if ( pTable )
//STRIP001                          nX += pTab->Frm().Left() - pTable->Frm().Left();
//STRIP001                      pTable = pTab;
//STRIP001                  }
//STRIP001                  const SwLayoutFrm *pCell = pTab ? pCnt->GetUpper() : 0;
//STRIP001                  while ( pCell && !pCell->IsCellFrm() )
//STRIP001                      pCell = pCell->GetUpper();
//STRIP001
//STRIP001                     Point aInsideCell;
//STRIP001                     Point aInsideCnt;
//STRIP001                     if ( pCell )
//STRIP001                     {
//STRIP001                         long nTmpTop = (pCell->Frm().*fnRect->fnGetTop)();
//STRIP001                         if ( bVert )
//STRIP001                         {
//STRIP001                             if ( nTmpTop )
//STRIP001                                 --nTmpTop;
//STRIP001
//STRIP001                             aInsideCell = Point( nTmpTop, nX );
//STRIP001                         }
//STRIP001                         else
//STRIP001                             aInsideCell = Point( nX, nTmpTop );
//STRIP001                     }
//STRIP001
//STRIP001                     long nTmpTop = (pCnt->Frm().*fnRect->fnGetTop)();
//STRIP001                     if ( bVert )
//STRIP001                     {
//STRIP001                         if ( nTmpTop )
//STRIP001                             --nTmpTop;
//STRIP001
//STRIP001                         aInsideCnt = Point( nTmpTop, nX );
//STRIP001                     }
//STRIP001                     else
//STRIP001                         aInsideCnt = Point( nX, nTmpTop );
//STRIP001
//STRIP001                  if ( pCell && pCell->Frm().IsInside( aInsideCell ) )
//STRIP001                  {
//STRIP001                      bEnd = TRUE;
//STRIP001                      //Jetzt noch schnell den richtigen Cntnt in der Zelle
//STRIP001                      //greifen.
//STRIP001                      if ( ! pCnt->Frm().IsInside( aInsideCnt ) )
//STRIP001                      {
//STRIP001                          pCnt = pCell->ContainsCntnt();
//STRIP001                          if ( fnNxtPrv == lcl_GetPrvCnt )
//STRIP001                              while ( pCell->IsAnLower(pCnt->GetNextCntntFrm()) )
//STRIP001                                  pCnt = pCnt->GetNextCntntFrm();
//STRIP001                      }
//STRIP001                  }
//STRIP001                  else if ( pCnt->Frm().IsInside( aInsideCnt ) )
//STRIP001                      bEnd = TRUE;
//STRIP001              }
//STRIP001          }
//STRIP001          if ( !bEnd )
//STRIP001          {
//STRIP001              pCnt = (*fnNxtPrv)( pCnt );
//STRIP001              pCnt = ::lcl_MissProtectedFrames( pCnt, fnNxtPrv, TRUE, bInReadOnly );
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001  } while ( !bEnd ||
//STRIP001            (pCnt && pCnt->IsTxtFrm() && ((SwTxtFrm*)pCnt)->IsHiddenNow()));
//STRIP001
//STRIP001  if( pCnt )
//STRIP001  {   // setze den Point auf den Content-Node
//STRIP001      SwCntntNode *pCNd = (SwCntntNode*)pCnt->GetNode();
//STRIP001      pPam->GetPoint()->nNode = *pCNd;
//STRIP001      if ( fnNxtPrv == lcl_GetPrvCnt )
//STRIP001          pCNd->MakeEndIndex( (SwIndex*)&pPam->GetPoint()->nContent );
//STRIP001      else
//STRIP001          pCNd->MakeStartIndex( (SwIndex*)&pPam->GetPoint()->nContent );
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001  return FALSE;
//STRIP001 }

//STRIP001 BOOL SwCntntFrm::UnitUp( SwPaM* pPam, const SwTwips, BOOL bInReadOnly ) const
//STRIP001 {
//STRIP001  return ::lcl_UpDown( pPam, this, lcl_GetPrvCnt, bInReadOnly );
//STRIP001 }

//STRIP001 BOOL SwCntntFrm::UnitDown( SwPaM* pPam, const SwTwips, BOOL bInReadOnly ) const
//STRIP001 {
//STRIP001  return ::lcl_UpDown( pPam, this, lcl_GetNxtCnt, bInReadOnly );
//STRIP001 }

/*************************************************************************
|*
|*  SwRootFrm::GetCurrPage()
|*
|*  Beschreibung:       Liefert die Nummer der aktuellen Seite.
|*          Wenn die Methode einen PaM bekommt, so ist die aktuelle Seite
|*          diejenige in der der PaM sitzt. Anderfalls ist die aktuelle
|*          Seite die erste Seite innerhalb der VisibleArea.
|*          Es wird nur auf den vorhandenen Seiten gearbeitet!
|*  Ersterstellung      MA 20. May. 92
|*  Letzte Aenderung    MA 09. Oct. 97
|*
|*************************************************************************/
//STRIP001 USHORT SwRootFrm::GetCurrPage( const SwPaM *pActualCrsr ) const
//STRIP001 {
//STRIP001  ASSERT( pActualCrsr, "Welche Seite soll's denn sein?" );
//STRIP001  const SwFrm *pActFrm = GetFmt()->GetDoc()->GetNodes()[pActualCrsr->GetPoint()->nNode]->
//STRIP001                                  GetCntntNode()->GetFrm( 0,
//STRIP001                                                  pActualCrsr->GetPoint(),
//STRIP001                                                  FALSE );
//STRIP001  return pActFrm->FindPageFrm()->GetPhyPageNum();
//STRIP001 }

/*************************************************************************
|*
|*  SwRootFrm::SetCurrPage()
|*
|*  Beschreibung:       Liefert einen PaM der am Anfang der gewuenschten
|*          Seite sitzt.
|*          Formatiert wird soweit notwendig
|*          Liefert Null, wenn die Operation nicht moeglich ist.
|*          Der PaM sitzt in der letzten Seite, wenn die Seitenzahl zu gross
|*          gewaehlt wurde.
|*  Ersterstellung      MA 20. May. 92
|*  Letzte Aenderung    MA 09. Oct. 97
|*
|*************************************************************************/
//STRIP001 USHORT SwRootFrm::SetCurrPage( SwCursor* pToSet, USHORT nPageNum )
//STRIP001 {
//STRIP001  ASSERT( Lower() && Lower()->IsPageFrm(), "Keine Seite vorhanden." );
//STRIP001
//STRIP001  SwPageFrm *pPage = (SwPageFrm*)Lower();
//STRIP001  BOOL bEnd =FALSE;
//STRIP001  while ( !bEnd && pPage->GetPhyPageNum() != nPageNum )
//STRIP001  {   if ( pPage->GetNext() )
//STRIP001          pPage = (SwPageFrm*)pPage->GetNext();
//STRIP001      else
//STRIP001      {   //Ersten CntntFrm Suchen, und solange Formatieren bis
//STRIP001          //eine neue Seite angefangen wird oder bis die CntntFrm's alle
//STRIP001          //sind.
//STRIP001          const SwCntntFrm *pCntnt = pPage->ContainsCntnt();
//STRIP001          while ( pCntnt && pPage->IsAnLower( pCntnt ) )
//STRIP001          {   pCntnt->Calc();
//STRIP001              pCntnt = pCntnt->GetNextCntntFrm();
//STRIP001          }
//STRIP001          //Jetzt ist entweder eine neue Seite da, oder die letzte Seite
//STRIP001          //ist gefunden.
//STRIP001          if ( pPage->GetNext() )
//STRIP001              pPage = (SwPageFrm*)pPage->GetNext();
//STRIP001          else
//STRIP001              bEnd = TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  //pPage zeigt jetzt auf die 'gewuenschte' Seite. Jetzt muss noch der
//STRIP001  //PaM auf den Anfang des ersten CntntFrm im Body-Text erzeugt werden.
//STRIP001  //Wenn es sich um eine Fussnotenseite handelt, wird der PaM in die erste
//STRIP001  //Fussnote gesetzt.
//STRIP001  const SwCntntFrm *pCntnt = pPage->ContainsCntnt();
//STRIP001  if ( pPage->IsFtnPage() )
//STRIP001      while ( pCntnt && !pCntnt->IsInFtn() )
//STRIP001          pCntnt = pCntnt->GetNextCntntFrm();
//STRIP001  else
//STRIP001      while ( pCntnt && !pCntnt->IsInDocBody() )
//STRIP001          pCntnt = pCntnt->GetNextCntntFrm();
//STRIP001  if ( pCntnt )
//STRIP001  {
//STRIP001      SwCntntNode* pCNd = (SwCntntNode*)pCntnt->GetNode();
//STRIP001      pToSet->GetPoint()->nNode = *pCNd;
//STRIP001      pCNd->MakeStartIndex( (SwIndex*)&pToSet->GetPoint()->nContent );
//STRIP001      pToSet->GetPoint()->nContent = ((SwTxtFrm*)pCntnt)->GetOfst();
//STRIP001
//STRIP001      SwShellCrsr* pSCrsr = (SwShellCrsr*)*pToSet;
//STRIP001      if( pSCrsr )
//STRIP001      {
//STRIP001          Point &rPt = pSCrsr->GetPtPos();
//STRIP001          rPt = pCntnt->Frm().Pos();
//STRIP001          rPt += pCntnt->Prt().Pos();
//STRIP001      }
//STRIP001      return pPage->GetPhyPageNum();
//STRIP001  }
//STRIP001  return 0;
//STRIP001 }

/*************************************************************************
|*
|*    SwCntntFrm::StartxxPage(), EndxxPage()
|*
|*    Beschreibung      Cursor an Anfang/Ende der aktuellen/vorherigen/
|*      naechsten Seite. Alle sechs Methoden rufen GetFrmInPage() mit der
|*      entsprechenden Parametrisierung.
|*      Zwei Parameter steuern die Richtung: einer bestimmt die Seite, der
|*      andere Anfang/Ende.
|*      Fuer die Bestimmung der Seite und des Cntnt (Anfang/Ende) werden
|*      die im folgenden definierten Funktionen benutzt.
|*    Ersterstellung    MA 15. Oct. 92
|*    Letzte Aenderung  MA 28. Feb. 93
|*
|*************************************************************************/
//STRIP001 SwCntntFrm *GetFirstSub( const SwLayoutFrm *pLayout )
//STRIP001 {
//STRIP001  return ((SwPageFrm*)pLayout)->FindFirstBodyCntnt();
//STRIP001 }

//STRIP001 SwCntntFrm *GetLastSub( const SwLayoutFrm *pLayout )
//STRIP001 {
//STRIP001  return ((SwPageFrm*)pLayout)->FindLastBodyCntnt();
//STRIP001 }

//STRIP001 SwLayoutFrm *GetNextFrm( const SwLayoutFrm *pFrm )
//STRIP001 {
//STRIP001  return (pFrm->GetNext() && pFrm->GetNext()->IsLayoutFrm()) ?
//STRIP001                                          (SwLayoutFrm*)pFrm->GetNext() : 0;
//STRIP001 }

//STRIP001 SwLayoutFrm *GetThisFrm( const SwLayoutFrm *pFrm )
//STRIP001 {
//STRIP001  return (SwLayoutFrm*)pFrm;
//STRIP001 }

//STRIP001 SwLayoutFrm *GetPrevFrm( const SwLayoutFrm *pFrm )
//STRIP001 {
//STRIP001  return (pFrm->GetPrev() && pFrm->GetPrev()->IsLayoutFrm()) ?
//STRIP001                                          (SwLayoutFrm*)pFrm->GetPrev() : 0;
//STRIP001 }

//Jetzt koennen auch die Funktionspointer initalisiert werden;
//sie sind in cshtyp.hxx declariert.
//STRIP001 SwPosPage fnPageStart = GetFirstSub;
//STRIP001 SwPosPage fnPageEnd = GetLastSub;
//STRIP001 SwWhichPage fnPagePrev = GetPrevFrm;
//STRIP001 SwWhichPage fnPageCurr = GetThisFrm;
//STRIP001 SwWhichPage fnPageNext = GetNextFrm;

//Liefert den ersten/den letzten Contentframe (gesteuert ueber
//den Parameter fnPosPage) in der
//aktuellen/vorhergehenden/folgenden Seite (gesteuert durch den
//Parameter fnWhichPage).
//STRIP001 BOOL GetFrmInPage( const SwCntntFrm *pCnt, SwWhichPage fnWhichPage,
//STRIP001                 SwPosPage fnPosPage, SwPaM *pPam )
//STRIP001 {
//STRIP001  //Erstmal die gewuenschte Seite besorgen, anfangs die aktuelle, dann
//STRIP001  //die die per fnWichPage gewuenscht wurde
//STRIP001  const SwLayoutFrm *pLayoutFrm = pCnt->FindPageFrm();
//STRIP001  if ( !pLayoutFrm || (0 == (pLayoutFrm = (*fnWhichPage)(pLayoutFrm))) )
//STRIP001      return FALSE;
//STRIP001
//STRIP001  //Jetzt den gewuenschen CntntFrm unterhalb der Seite
//STRIP001  if( 0 == (pCnt = (*fnPosPage)(pLayoutFrm)) )
//STRIP001      return FALSE;
//STRIP001  else
//STRIP001  {
//STRIP001         // repeated headlines in tables
//STRIP001         if ( pCnt->IsInTab() && fnPosPage == GetFirstSub )
//STRIP001         {
//STRIP001             const SwTabFrm* pTab = pCnt->FindTabFrm();
//STRIP001             if ( pTab->IsFollow() && pTab->GetTable()->IsHeadlineRepeat() )
//STRIP001             {
//STRIP001                 const SwFrm* pTmpFrm = pCnt;
//STRIP001                 while( !pTmpFrm->IsRowFrm() || !pTmpFrm->GetUpper()->IsTabFrm() )
//STRIP001                     pTmpFrm = pTmpFrm->GetUpper();
//STRIP001
//STRIP001                 ASSERT( pTmpFrm && pTmpFrm->IsRowFrm(), "No RowFrm available" )
//STRIP001
//STRIP001                 if ( ! pTmpFrm->GetPrev() && pTmpFrm->GetNext() )
//STRIP001                 {
//STRIP001                     // We are in the first line of a follow table
//STRIP001                     // with repeated headings.
//STRIP001                     // To actually make a "real" move we take the first content
//STRIP001                     // of the next row
//STRIP001                     pCnt = ((SwLayoutFrm*)pTmpFrm->GetNext())->ContainsCntnt();
//STRIP001                     if ( ! pCnt )
//STRIP001                         return FALSE;
//STRIP001                 }
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001      SwCntntNode *pCNd = (SwCntntNode*)pCnt->GetNode();
//STRIP001      pPam->GetPoint()->nNode = *pCNd;
//STRIP001      xub_StrLen nIdx;
//STRIP001      if( fnPosPage == GetFirstSub )
//STRIP001          nIdx = ((SwTxtFrm*)pCnt)->GetOfst();
//STRIP001      else
//STRIP001          nIdx = pCnt->GetFollow() ?
//STRIP001                  ((SwTxtFrm*)pCnt)->GetFollow()->GetOfst()-1 : pCNd->Len();
//STRIP001      pPam->GetPoint()->nContent.Assign( pCNd, nIdx );
//STRIP001      return TRUE;
//STRIP001  }
//STRIP001 }

/*************************************************************************
|*
|*  SwLayoutFrm::GetCntntPos()
|*
|*  Beschreibung        Es wird der nachstliegende Cntnt zum uebergebenen
|*                      gesucht. Betrachtet werden die vorhergehende, die
|*                      aktuelle und die folgende Seite.
|*                      Wenn kein Inhalt gefunden wird, so wird der Bereich
 *                      erweitert bis einer gefunden wird.
|*                      Zurueckgegeben wird die 'Semantisch richtige' Position
|*                      innerhalb der PrtArea des gefundenen CntntFrm
|*  Ersterstellung      MA 15. Jul. 92
|*  Letzte Aenderung    MA 09. Jan. 97
|*
|*************************************************************************/
/*N*/ ULONG CalcDiff( const Point &rPt1, const Point &rPt2 )
/*N*/ {
/*N*/   //Jetzt die Entfernung zwischen den beiden Punkten berechnen.
/*N*/   //'Delta' X^2 + 'Delta'Y^2 = 'Entfernung'^2
/*N*/   ULONG dX = Max( rPt1.X(), rPt2.X() ) -
/*N*/              Min( rPt1.X(), rPt2.X() ),
/*N*/         dY = Max( rPt1.Y(), rPt2.Y() ) -
/*N*/              Min( rPt1.Y(), rPt2.Y() );
/*N*/   BigInt dX1( dX ), dY1( dY );
/*N*/   dX1 *= dX1; dY1 *= dY1;
/*N*/   return ::binfilter::SqRt( dX1 + dY1 );
/*N*/ }

// lcl_Inside ueberprueft, ob der Punkt innerhalb des Seitenteils liegt, in dem
// auch der CntntFrame liegt. Als Seitenteile gelten in diesem Zusammenhang
// Kopfzeile, Seitenbody, Fusszeile und FussnotenContainer.
// Dies dient dazu, dass ein CntntFrm, der im "richtigen" Seitenteil liegt,
// eher akzeptiert wird als ein anderer, der nicht dort liegt, auch wenn
// dessen Abstand zum Punkt geringer ist.

/*N*/ const SwLayoutFrm* lcl_Inside( const SwCntntFrm *pCnt, Point& rPt )
/*N*/ {
/*N*/   const SwLayoutFrm* pUp = pCnt->GetUpper();
/*N*/   while( pUp )
/*N*/   {
/*N*/       if( pUp->IsPageBodyFrm() || pUp->IsFooterFrm() || pUp->IsHeaderFrm() )
/*N*/       {
/*N*/           if( rPt.Y() >= pUp->Frm().Top() && rPt.Y() <= pUp->Frm().Bottom() )
/*?*/               return pUp;
/*N*/           return NULL;
/*N*/       }
/*N*/       if( pUp->IsFtnContFrm() )
/*?*/           return pUp->Frm().IsInside( rPt ) ? pUp : NULL;
/*N*/       pUp = pUp->GetUpper();
/*N*/   }
/*?*/   return NULL;
/*N*/ }

//Fuer MSC keine Optimierung mit e (enable register...) hier, sonst gibts
//einen Bug (ID: 2857)
/*N*/ #pragma optimize("e",off)

/*N*/ const SwCntntFrm *SwLayoutFrm::GetCntntPos( Point& rPoint,
/*N*/                                           const BOOL bDontLeave,
/*N*/                                           const BOOL bBodyOnly,
/*N*/                                           const BOOL bCalc,
/*N*/                                           const SwCrsrMoveState *pCMS,
/*N*/                                           const BOOL bDefaultExpand ) const
/*N*/ {
/*N*/   //Ersten CntntFrm ermitteln.
/*N*/   const SwLayoutFrm *pStart = (!bDontLeave && bDefaultExpand && GetPrev()) ?
/*N*/                                   (SwLayoutFrm*)GetPrev() : this;
/*N*/   const SwCntntFrm *pCntnt = pStart->ContainsCntnt();
/*N*/
/*N*/   if ( !pCntnt && (GetPrev() && !bDontLeave) )
/*N*/       pCntnt = ContainsCntnt();
/*N*/
/*N*/   if ( bBodyOnly && pCntnt && !pCntnt->IsInDocBody() )
/*N*/       while ( pCntnt && !pCntnt->IsInDocBody() )
/*N*/           pCntnt = pCntnt->GetNextCntntFrm();
/*N*/
/*N*/   const SwCntntFrm *pActual= pCntnt;
/*N*/   const SwLayoutFrm *pInside = NULL;
/*N*/   USHORT nMaxPage = GetPhyPageNum() + (bDefaultExpand ? 1 : 0);
/*N*/   Point aPoint = rPoint;
/*N*/   ULONG nDistance = ULONG_MAX;
/*N*/
/*N*/   while ( TRUE )  //Sicherheitsschleifchen, damit immer einer gefunden wird.
/*N*/   {
/*N*/       while ( pCntnt &&
/*N*/               ((!bDontLeave || IsAnLower( pCntnt )) &&
/*N*/               (pCntnt->GetPhyPageNum() <= nMaxPage)) )
/*N*/       {
/*N*/           if ( ( bCalc || pCntnt->Frm().Width() ) &&
/*N*/                ( !bBodyOnly || pCntnt->IsInDocBody() ) )
/*N*/           {
/*N*/               //Wenn der Cntnt in einem geschuetzen Bereich (Zelle, Ftn, Section)
/*N*/               //liegt, wird der nachste Cntnt der nicht geschuetzt ist gesucht.
/*N*/               const SwCntntFrm *pComp = pCntnt;
/*N*/               pCntnt = ::binfilter::lcl_MissProtectedFrames( pCntnt, lcl_GetNxtCnt, FALSE,
/*N*/                                       pCMS ? pCMS->bSetInReadOnly : FALSE );
/*N*/               if ( pComp != pCntnt )
/*N*/                   continue;
/*N*/
/*N*/               if ( !pCntnt->IsTxtFrm() || !((SwTxtFrm*)pCntnt)->IsHiddenNow() )
/*N*/               {
/*N*/                   if ( bCalc )
/*N*/                       pCntnt->Calc();
/*N*/
/*N*/                   SwRect aCntFrm( pCntnt->UnionFrm() );
/*N*/                   if ( aCntFrm.IsInside( rPoint ) )
/*N*/                   {
/*N*/                       pActual = pCntnt;
/*N*/                       aPoint = rPoint;
/*N*/                       break;
/*N*/                   }
/*N*/                   //Die Strecke von rPoint zum dichtesten Punkt von pCntnt wird
/*N*/                   //jetzt berechnet.
/*N*/                   Point aCntntPoint( rPoint );
/*N*/
/*N*/                   //Erst die Vertikale Position einstellen
/*N*/                   if ( aCntFrm.Top() > aCntntPoint.Y() )
/*N*/                       aCntntPoint.Y() = aCntFrm.Top();
/*N*/                   else if ( aCntFrm.Bottom() < aCntntPoint.Y() )
/*N*/                       aCntntPoint.Y() = aCntFrm.Bottom();
/*N*/
/*N*/                   //Jetzt die Horizontale Position
/*N*/                   if ( aCntFrm.Left() > aCntntPoint.X() )
/*N*/                       aCntntPoint.X() = aCntFrm.Left();
/*N*/                   else if ( aCntFrm.Right() < aCntntPoint.X() )
/*N*/                       aCntntPoint.X() = aCntFrm.Right();
/*N*/
/*N*/                   // pInside ist ein Seitenbereich, in dem der Punkt liegt,
/*N*/                   // sobald pInside!=0 ist, werden nur noch Frames akzeptiert,
/*N*/                   // die innerhalb liegen.
/*N*/                   if( !pInside || ( pInside->IsAnLower( pCntnt ) &&
/*N*/                       ( !pCntnt->IsInFtn() || pInside->IsFtnContFrm() ) ) )
/*N*/                   {
/*N*/                       const ULONG nDiff = ::binfilter::CalcDiff( aCntntPoint, rPoint );
/*N*/                       BOOL bBetter = nDiff < nDistance;  // Dichter dran
/*N*/                       if( !pInside )
/*N*/                       {
/*N*/                           pInside = lcl_Inside( pCntnt, rPoint );
/*N*/                           if( pInside )  // Im "richtigen" Seitenteil
/*N*/                               bBetter = TRUE;
/*N*/                       }
/*N*/                       if( bBetter )
/*N*/                       {
/*N*/                           aPoint = aCntntPoint;
/*N*/                           nDistance = nDiff;
/*N*/                           pActual = pCntnt;
/*N*/                       }
/*N*/                   }
/*N*/               }
/*N*/           }
/*N*/           pCntnt = pCntnt->GetNextCntntFrm();
/*N*/           if ( bBodyOnly )
/*N*/               while ( pCntnt && !pCntnt->IsInDocBody() )
/*N*/                   pCntnt = pCntnt->GetNextCntntFrm();
/*N*/       }
/*N*/       if ( !pActual )
/*N*/       {   //Wenn noch keiner gefunden wurde muss der Suchbereich erweitert
/*N*/           //werden, irgenwann muessen wir einen Finden!
/*N*/           //MA 09. Jan. 97: Opt fuer viele leere Seiten, wenn wir nur im
/*N*/           //Body suchen, koennen wir den Suchbereich gleich in einem
/*N*/           //Schritt hinreichend erweitern.
/*N*/           if ( bBodyOnly )
/*N*/           {
/*N*/               while ( !pCntnt && pStart->GetPrev() )
/*N*/               {
/*N*/                   ++nMaxPage;
/*N*/                   if( !pStart->GetPrev()->IsLayoutFrm() )
/*N*/                       return 0;
/*N*/                   pStart = (SwLayoutFrm*)pStart->GetPrev();
/*N*/                   pCntnt = pStart->IsInDocBody()
/*N*/                               ? pStart->ContainsCntnt()
/*N*/                               : pStart->FindPageFrm()->FindFirstBodyCntnt();
/*N*/               }
/*N*/               if ( !pCntnt )  //irgendwann muessen wir mit irgendeinem Anfangen!
/*N*/               {
/*N*/                   pCntnt = pStart->FindPageFrm()->GetUpper()->ContainsCntnt();
/*N*/                   while ( pCntnt && !pCntnt->IsInDocBody() )
/*N*/                       pCntnt = pCntnt->GetNextCntntFrm();
/*N*/                   if ( !pCntnt )
/*N*/                       return 0;   //Es gibt noch keine Dokumentinhalt!
/*N*/               }
/*N*/           }
/*N*/           else
/*N*/           {
/*N*/               ++nMaxPage;
/*N*/               if ( pStart->GetPrev() )
/*N*/               {
/*N*/                   if( !pStart->GetPrev()->IsLayoutFrm() )
/*N*/                       return 0;
/*N*/                   pStart = (SwLayoutFrm*)pStart->GetPrev();
/*N*/                   pCntnt = pStart->ContainsCntnt();
/*N*/               }
/*N*/               else //irgendwann muessen wir mit irgendeinem Anfangen!
/*N*/                   pCntnt = pStart->FindPageFrm()->GetUpper()->ContainsCntnt();
/*N*/           }
/*N*/           pActual = pCntnt;
/*N*/       }
/*N*/       else
/*N*/           break;
/*N*/   }
/*N*/
/*N*/ #ifndef PRODUCT
/*N*/   ASSERT( pActual, "Keinen Cntnt gefunden." );
/*N*/   if ( bBodyOnly )
/*N*/       ASSERT( pActual->IsInDocBody(), "Cnt nicht im Body." );
/*N*/ #endif
/*N*/
/*N*/   //Spezialfall fuer das selektieren von Tabellen, nicht in wiederholte
/*N*/   //TblHedlines.
/*N*/   if ( pActual->IsInTab() && pCMS && pCMS->eState == MV_TBLSEL )
/*N*/   {
/*N*/       const SwTabFrm *pTab = pActual->FindTabFrm();
/*N*/       if ( pTab->IsFollow() && pTab->GetTable()->IsHeadlineRepeat() &&
/*N*/            ((SwLayoutFrm*)pTab->Lower())->IsAnLower( pActual ) )
/*N*/       {
/*N*/           ((SwCrsrMoveState*)pCMS)->bStop = TRUE;
/*N*/           return 0;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   //Jetzt noch eine kleine Korrektur beim ersten/letzten
/*N*/   Size aActualSize( pActual->Prt().SSize() );
/*N*/   if ( aActualSize.Height() > pActual->GetUpper()->Prt().Height() )
/*N*/       aActualSize.Height() = pActual->GetUpper()->Prt().Height();
/*N*/
/*N*/     SWRECTFN( pActual )
/*N*/   if ( !pActual->GetPrev() &&
/*N*/        (*fnRect->fnYDiff)( (pActual->*fnRect->fnGetPrtTop)(),
/*N*/                               bVert ? rPoint.X() : rPoint.Y() ) > 0 )
/*N*/     {
/*N*/         aPoint.Y() = pActual->Frm().Top() + pActual->Prt().Top();
/*N*/         aPoint.X() = pActual->Frm().Left() +
/*N*/                         ( pActual->IsRightToLeft() || bVert ?
/*N*/                           pActual->Prt().Right() :
/*N*/                           pActual->Prt().Left() );
/*N*/     }
/*N*/   else if ( !pActual->GetNext() &&
/*N*/               (*fnRect->fnYDiff)( (pActual->*fnRect->fnGetPrtBottom)(),
/*N*/                                    bVert ? rPoint.X() : rPoint.Y() ) < 0 )
/*N*/     {
/*N*/         aPoint.Y() = pActual->Frm().Top() + pActual->Prt().Bottom();
/*N*/         aPoint.X() = pActual->Frm().Left() +
/*N*/                         ( pActual->IsRightToLeft() || bVert ?
/*N*/                           pActual->Prt().Left() :
/*N*/                           pActual->Prt().Right() );
/*N*/   }
/*N*/
/*N*/   //Und den Point in die PrtArea bringen
/*N*/   if ( bCalc )
/*N*/       pActual->Calc();
/*N*/   const SwRect aRect( pActual->Frm().Pos() + pActual->Prt().Pos(),
/*N*/                       aActualSize );
/*N*/   if ( aPoint.Y() < aRect.Top() )
/*N*/       aPoint.Y() = aRect.Top();
/*N*/   else if ( aPoint.Y() > aRect.Bottom() )
/*N*/       aPoint.Y() = aRect.Bottom();
/*N*/   if ( aPoint.X() < aRect.Left() )
/*N*/       aPoint.X() = aRect.Left();
/*N*/   else if ( aPoint.X() > aRect.Right() )
/*N*/       aPoint.X() = aRect.Right();
/*N*/   rPoint = aPoint;
/*N*/   return pActual;
/*N*/ }

/*N*/ #pragma optimize("",on)

/*************************************************************************
|*
|*  SwPageFrm::GetCntntPosition()
|*
|*  Beschreibung        Analog zu SwLayoutFrm::GetCntntPos().
|*                      Spezialisiert fuer Felder in Rahmen.
|*
|*  Ersterstellung      MA 22. Mar. 95
|*  Letzte Aenderung    MA 07. Nov. 95
|*
|*************************************************************************/
/*N*/ void SwPageFrm::GetCntntPosition( const Point &rPt, SwPosition &rPos ) const
/*N*/ {
/*N*/   //Ersten CntntFrm ermitteln.
/*N*/   const SwCntntFrm *pCntnt = ContainsCntnt();
/*N*/   if ( pCntnt )
/*N*/   {
/*N*/       //Einen weiter zurueck schauen (falls moeglich).
/*N*/       const SwCntntFrm *pTmp = pCntnt->GetPrevCntntFrm();
/*N*/       while ( pTmp && !pTmp->IsInDocBody() )
/*?*/           pTmp = pTmp->GetPrevCntntFrm();
/*N*/       if ( pTmp )
/*?*/           pCntnt = pTmp;
/*N*/   }
/*N*/   else
/*?*/       pCntnt = GetUpper()->ContainsCntnt();
/*N*/
/*N*/   const SwCntntFrm *pAct = pCntnt;
/*N*/   Point aAct       = rPt;
/*N*/   ULONG nDist      = ULONG_MAX;
/*N*/
/*N*/   while ( pCntnt )
/*N*/   {
/*N*/       SwRect aCntFrm( pCntnt->UnionFrm() );
/*N*/       if ( aCntFrm.IsInside( rPt ) )
/*N*/       {
/*N*/           //dichter gehts nimmer.
/*?*/           pAct = pCntnt;
/*?*/           break;
/*N*/       }
/*N*/
/*N*/       //Die Strecke von rPt zum dichtesten Punkt von pCntnt berechnen.
/*N*/       Point aPoint( rPt );
/*N*/
/*N*/       //Erst die vertikale Position einstellen
/*N*/       if ( aCntFrm.Top() > rPt.Y() )
/*N*/           aPoint.Y() = aCntFrm.Top();
/*N*/       else if ( aCntFrm.Bottom() < rPt.Y() )
/*N*/           aPoint.Y() = aCntFrm.Bottom();
/*N*/
/*N*/       //Jetzt die horizontale Position
/*N*/       if ( aCntFrm.Left() > rPt.X() )
/*N*/           aPoint.X() = aCntFrm.Left();
/*N*/       else if ( aCntFrm.Right() < rPt.X() )
/*N*/           aPoint.X() = aCntFrm.Right();
/*N*/
/*N*/       const ULONG nDiff = ::binfilter::CalcDiff( aPoint, rPt );
/*N*/       if ( nDiff < nDist )
/*N*/       {
/*N*/           aAct    = aPoint;
/*N*/           nDist   = nDiff;
/*N*/           pAct    = pCntnt;
/*N*/       }
/*N*/       else if ( aCntFrm.Top() > Frm().Bottom() )
/*N*/           //Dichter wirds im Sinne der Felder nicht mehr!
/*N*/           break;
/*N*/
/*N*/       pCntnt = pCntnt->GetNextCntntFrm();
/*N*/       while ( pCntnt && !pCntnt->IsInDocBody() )
/*N*/           pCntnt = pCntnt->GetNextCntntFrm();
/*N*/   }
/*N*/
/*N*/   //Und den Point in die PrtArea bringen
/*N*/   const SwRect aRect( pAct->Frm().Pos() + pAct->Prt().Pos(), pAct->Prt().SSize() );
/*N*/   if ( aAct.Y() < aRect.Top() )
/*N*/       aAct.Y() = aRect.Top();
/*N*/   else if ( aAct.Y() > aRect.Bottom() )
/*N*/       aAct.Y() = aRect.Bottom();
/*N*/   if ( aAct.X() < aRect.Left() )
/*?*/       aAct.X() = aRect.Left();
/*N*/   else if ( aAct.X() > aRect.Right() )
/*N*/       aAct.X() = aRect.Right();
/*N*/
/*N*/   if( !pAct->IsValid() )
/*N*/   {
/*N*/       // CntntFrm nicht formatiert -> immer auf Node-Anfang
/*?*/       SwCntntNode* pCNd = (SwCntntNode*)pAct->GetNode();
/*?*/       ASSERT( pCNd, "Wo ist mein CntntNode?" );
/*?*/       rPos.nNode = *pCNd;
/*?*/       rPos.nContent.Assign( pCNd, 0 );
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       SwCrsrMoveState aTmpState( MV_SETONLYTEXT );
/*N*/       pAct->GetCrsrOfst( &rPos, aAct, &aTmpState );
/*N*/   }
/*N*/ }

/*************************************************************************
|*
|*  SwRootFrm::GetNextPrevCntntPos()
|*
|*  Beschreibung        Es wird der naechstliegende Cntnt zum uebergebenen
|*                      Point gesucht. Es wird nur im BodyText gesucht.
|*  Ersterstellung      MA 15. Jul. 92
|*  Letzte Aenderung    JP 11.10.2001
|*
|*************************************************************************/

//!!!!! Es wird nur der vertikal naechstliegende gesucht.
//JP 11.10.2001: only in tables we try to find the right column - Bug 72294
//STRIP001 Point SwRootFrm::GetNextPrevCntntPos( const Point& rPoint, BOOL bNext ) const
//STRIP001 {
//STRIP001  //Ersten CntntFrm und seinen Nachfolger im Body-Bereich suchen
//STRIP001  //Damit wir uns nicht tot suchen (und vor allem nicht zuviel formatieren)
//STRIP001  //gehen wir schon mal von der richtigen Seite aus.
//STRIP001  SwLayoutFrm *pPage = (SwLayoutFrm*)Lower();
//STRIP001     if( pPage )
//STRIP001         while( pPage->GetNext() && pPage->Frm().Bottom() < rPoint.Y() )
//STRIP001             pPage = (SwLayoutFrm*)pPage->GetNext();
//STRIP001
//STRIP001  const SwCntntFrm *pCnt = pPage ? pPage->ContainsCntnt() : ContainsCntnt();
//STRIP001  while ( pCnt && !pCnt->IsInDocBody() )
//STRIP001      pCnt = pCnt->GetNextCntntFrm();
//STRIP001
//STRIP001  if ( !pCnt )
//STRIP001      return Point( 0, 0 );
//STRIP001
//STRIP001  pCnt->Calc();
//STRIP001  if( !bNext )
//STRIP001  {
//STRIP001      // Solange der Point vor dem ersten CntntFrm liegt und es noch
//STRIP001      // vorhergehende Seiten gibt gehe ich jeweils eine Seite nach vorn.
//STRIP001      while ( rPoint.Y() < pCnt->Frm().Top() && pPage->GetPrev() )
//STRIP001      {
//STRIP001          pPage = (SwLayoutFrm*)pPage->GetPrev();
//STRIP001          pCnt = pPage->ContainsCntnt();
//STRIP001          while ( !pCnt )
//STRIP001          {
//STRIP001              pPage = (SwLayoutFrm*)pPage->GetPrev();
//STRIP001              if ( pPage )
//STRIP001                  pCnt = pPage->ContainsCntnt();
//STRIP001              else
//STRIP001                  return ContainsCntnt()->UnionFrm().Pos();
//STRIP001          }
//STRIP001          pCnt->Calc();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  //Liegt der Point ueber dem ersten CntntFrm?
//STRIP001  if ( rPoint.Y() < pCnt->Frm().Top() && !lcl_IsInRepeatedHeadline( pCnt ) )
//STRIP001      return pCnt->UnionFrm().Pos();
//STRIP001
//STRIP001  while ( pCnt )
//STRIP001  {
//STRIP001      //Liegt der Point im aktuellen CntntFrm?
//STRIP001      SwRect aCntFrm( pCnt->UnionFrm() );
//STRIP001      if ( aCntFrm.IsInside( rPoint ) && !lcl_IsInRepeatedHeadline( pCnt ))
//STRIP001          return rPoint;
//STRIP001
//STRIP001      //Ist der aktuelle der letzte CntntFrm? ||
//STRIP001      //Wenn der naechste CntntFrm hinter dem Point liegt, ist der
//STRIP001      //aktuelle der gesuchte.
//STRIP001      const SwCntntFrm *pNxt = pCnt->GetNextCntntFrm();
//STRIP001      while ( pNxt && !pNxt->IsInDocBody() )
//STRIP001          pNxt = pNxt->GetNextCntntFrm();
//STRIP001
//STRIP001      //Liegt der Point hinter dem letzten CntntFrm?
//STRIP001      if ( !pNxt )
//STRIP001          return Point( aCntFrm.Right(), aCntFrm.Bottom() );
//STRIP001
//STRIP001      //Wenn der naechste CntntFrm hinter dem Point liegt ist er der
//STRIP001      //gesuchte.
//STRIP001      const SwTabFrm* pTFrm;
//STRIP001      pNxt->Calc();
//STRIP001      if( pNxt->Frm().Top() > rPoint.Y() &&
//STRIP001          !lcl_IsInRepeatedHeadline( pCnt, &pTFrm ) &&
//STRIP001          ( !pTFrm || pNxt->Frm().Left() > rPoint.X() ))
//STRIP001      {
//STRIP001          if( bNext )
//STRIP001              return pNxt->Frm().Pos();
//STRIP001          return Point( aCntFrm.Right(), aCntFrm.Bottom() );
//STRIP001      }
//STRIP001      pCnt = pNxt;
//STRIP001  }
//STRIP001  return Point( 0, 0 );
//STRIP001 }

/*************************************************************************
|*
|*  SwRootFrm::GetPagePos()
|*
|*  Beschreibung:   Liefert die absolute Dokumentpositon der gewuenschten
|*          Seite.
|*          Formatiert wird nur soweit notwendig und nur dann wenn bFormat=TRUE
|*          Liefert Null, wenn die Operation nicht moeglich ist.
|*          Die Pos ist die der letzten Seite, wenn die Seitenzahl zu gross
|*          gewaehlt wurde.
|*  Ersterstellung      MA 01. Jun. 92
|*  Letzte Aenderung    MA 09. Oct. 97
|*
|*************************************************************************/
//STRIP001 Point SwRootFrm::GetPagePos( USHORT nPageNum ) const
//STRIP001 {
//STRIP001  ASSERT( Lower() && Lower()->IsPageFrm(), "Keine Seite vorhanden." );
//STRIP001
//STRIP001  const SwPageFrm *pPage = (const SwPageFrm*)Lower();
//STRIP001  while ( TRUE )
//STRIP001  {
//STRIP001      if ( pPage->GetPhyPageNum() >= nPageNum || !pPage->GetNext() )
//STRIP001          break;
//STRIP001      pPage = (const SwPageFrm*)pPage->GetNext();
//STRIP001  }
//STRIP001  return pPage->Frm().Pos();
//STRIP001 }

/** get page frame by phyiscal page number

    OD 14.01.2003 #103492#

    @return pointer to the page frame with the given physical page number
*/
//STRIP001 SwPageFrm* SwRootFrm::GetPageByPageNum( sal_uInt16 _nPageNum ) const
//STRIP001 {
//STRIP001     for ( const SwPageFrm* pPageFrm = static_cast<const SwPageFrm*>( Lower() );
//STRIP001           pPageFrm && pPageFrm->GetPhyPageNum() < _nPageNum;
//STRIP001           pPageFrm = static_cast<const SwPageFrm*>( pPageFrm->GetNext() ) )
//STRIP001     {
//STRIP001         // empty body of for-loop
//STRIP001     }
//STRIP001
//STRIP001     if ( pPageFrm && pPageFrm->GetPhyPageNum() == _nPageNum )
//STRIP001     {
//STRIP001         return const_cast<SwPageFrm*>( pPageFrm );
//STRIP001     }
//STRIP001     else
//STRIP001     {
//STRIP001         return 0;
//STRIP001     }
//STRIP001 }

/*************************************************************************
|*
|*  SwRootFrm::IsDummyPage(USHORT)
|*
|*  Description: Returns TRUE, when the given physical pagenumber does't exist
|*               or this page is an empty page.
|*************************************************************************/
//STRIP001 BOOL SwRootFrm::IsDummyPage( USHORT nPageNum ) const
//STRIP001 {
//STRIP001     if( !Lower() || !nPageNum || nPageNum > GetPageNum() )
//STRIP001         return TRUE;
//STRIP001
//STRIP001  const SwPageFrm *pPage = (const SwPageFrm*)Lower();
//STRIP001     while( pPage && nPageNum < pPage->GetPhyPageNum() )
//STRIP001      pPage = (const SwPageFrm*)pPage->GetNext();
//STRIP001     return pPage ? pPage->IsEmptyPage() : TRUE;
//STRIP001 }


/*************************************************************************
|*
|*    SwFrm::IsProtected()
|*
|*    Beschreibung      Ist der Frm bzw. die Section in der er steht
|*                      geschuetzt?
|*                      Auch Fly in Fly in ... und Fussnoten
|*
|*    Ersterstellung    MA 28. Jul. 93
|*    Letzte Aenderung  MA 06. Nov. 97
|*
|*************************************************************************/
/*N*/ BOOL SwFrm::IsProtected() const
/*N*/ {
/*N*/   //Der Frm kann in Rahmen, Zellen oder Bereichen geschuetzt sein.
/*N*/   //Geht auch FlyFrms rekursiv hoch. Geht auch von Fussnoten zum Anker.
/*N*/   const SwFrm *pFrm = this;
/*N*/   do
/*N*/   {
/*N*/       if ( pFrm->IsCntntFrm() )
/*N*/       {
/*N*/           if ( ((SwCntntFrm*)pFrm)->GetNode() &&
/*N*/                  ((SwCntntFrm*)pFrm)->GetNode()->IsInProtectSect() )
/*N*/               return TRUE;
/*N*/       }
/*N*/       else
/*N*/         {
/*N*/             if ( ((SwLayoutFrm*)pFrm)->GetFmt() &&
/*N*/                  ((SwLayoutFrm*)pFrm)->GetFmt()->
/*N*/                  GetProtect().IsCntntProtected() )
/*N*/           return TRUE;
/*N*/         }
/*N*/       if ( pFrm->IsFlyFrm() )
/*N*/       {
/*N*/           //Der Schutz des Inhaltes kann bei Verkettung vom Master der Kette
/*N*/           //vorgegeben werden.
/*N*/           if ( ((SwFlyFrm*)pFrm)->GetPrevLink() )
/*N*/           {
/*N*/               SwFlyFrm *pMaster = (SwFlyFrm*)pFrm;
/*N*/               do
/*N*/               {   pMaster = pMaster->GetPrevLink();
/*N*/               } while ( pMaster->GetPrevLink() );
/*N*/               if ( pMaster->IsProtected() )
/*N*/                   return TRUE;
/*N*/           }
/*N*/           pFrm = ((SwFlyFrm*)pFrm)->GetAnchor();
/*N*/       }
/*N*/       else if ( pFrm->IsFtnFrm() )
/*N*/           pFrm = ((SwFtnFrm*)pFrm)->GetRef();
/*N*/       else
/*N*/           pFrm = pFrm->GetUpper();
/*N*/
/*N*/   } while ( pFrm );
/*N*/
/*N*/   return FALSE;
/*N*/ }

/*************************************************************************
|*
|*    SwFrm::GetPhyPageNum()
|*    Beschreibung:     Liefert die physikalische Seitennummer
|*
|*    Ersterstellung    OK 06.07.93 08:35
|*    Letzte Aenderung  MA 30. Nov. 94
|*
|*************************************************************************/
/*N*/ USHORT SwFrm::GetPhyPageNum() const
/*N*/ {
/*N*/   const SwPageFrm *pPage = FindPageFrm();
/*N*/   return pPage ? pPage->GetPhyPageNum() : 0;
/*N*/ }

/*-----------------26.02.01 11:25-------------------
 * SwFrm::WannaRightPage()
 * decides if the page want to be a rightpage or not.
 * If the first content of the page has a page descriptor,
 * we take the follow of the page descriptor of the last not empty page.
 * If this descriptor allows only right(left) pages and the page
 * isn't an empty page then it wanna be such right(left) page.
 * If the descriptor allows right and left pages, we look for a number offset
 * in the first content. If there is one, odd number results right pages,
 * even number results left pages.
 * If there is no number offset, we take the physical page number instead,
 * but a previous empty page don't count.
 * --------------------------------------------------*/

/*N*/ BOOL SwFrm::WannaRightPage() const
/*N*/ {
/*N*/   const SwPageFrm *pPage = FindPageFrm();
/*N*/   if ( !pPage || !pPage->GetUpper() )
/*?*/       return TRUE;
/*N*/
/*N*/   const SwFrm *pFlow = pPage->FindFirstBodyCntnt();
/*N*/   SwPageDesc *pDesc = 0;
/*N*/   USHORT nPgNum = 0;
/*N*/   if ( pFlow )
/*N*/   {
/*N*/       if ( pFlow->IsInTab() )
/*N*/           pFlow = pFlow->FindTabFrm();
/*N*/       const SwFlowFrm *pTmp = SwFlowFrm::CastFlowFrm( pFlow );
/*N*/       if ( !pTmp->IsFollow() )
/*N*/       {
/*N*/           const SwFmtPageDesc& rPgDesc = pFlow->GetAttrSet()->GetPageDesc();
/*N*/           pDesc = (SwPageDesc*)rPgDesc.GetPageDesc();
/*N*/           nPgNum = rPgDesc.GetNumOffset();
/*N*/       }
/*N*/   }
/*N*/   if ( !pDesc )
/*N*/   {
/*N*/       SwPageFrm *pPrv = (SwPageFrm*)pPage->GetPrev();
/*N*/       if( pPrv && pPrv->IsEmptyPage() )
/*N*/           pPrv = (SwPageFrm*)pPrv->GetPrev();
/*N*/       if( pPrv )
/*N*/           pDesc = pPrv->GetPageDesc()->GetFollow();
/*N*/       else
/*N*/       {
/*N*/           const SwDoc* pDoc = pPage->GetFmt()->GetDoc();
/*N*/           pDesc = (SwPageDesc*)&pDoc->GetPageDesc( 0 );
/*N*/       }
/*N*/   }
/*N*/   ASSERT( pDesc, "No pagedescriptor" );
/*N*/   BOOL bOdd;
/*N*/   if( nPgNum )
/*N*/       bOdd = nPgNum % 2 ? TRUE : FALSE;
/*N*/   else
/*N*/   {
/*N*/       bOdd = pPage->OnRightPage();
/*N*/       if( pPage->GetPrev() && ((SwPageFrm*)pPage->GetPrev())->IsEmptyPage() )
/*N*/           bOdd = !bOdd;
/*N*/   }
/*N*/   if( !pPage->IsEmptyPage() )
/*N*/   {
/*N*/       if( !pDesc->GetRightFmt() )
/*N*/           bOdd = FALSE;
/*N*/       else if( !pDesc->GetLeftFmt() )
/*N*/           bOdd = TRUE;
/*N*/   }
/*N*/   return bOdd;
/*N*/ }

/*************************************************************************
|*
|*    SwFrm::GetVirtPageNum()
|*    Beschreibung:     Liefert die virtuelle Seitennummer mit Offset
|*
|*    Ersterstellung    OK 06.07.93 08:35
|*    Letzte Aenderung  MA 30. Nov. 94
|*
|*************************************************************************/
/*N*/ USHORT SwFrm::GetVirtPageNum() const
/*N*/ {
/*N*/   const SwPageFrm *pPage = FindPageFrm();
/*N*/   if ( !pPage || !pPage->GetUpper() )
/*?*/       return 0;
/*N*/
/*N*/   USHORT nPhyPage = pPage->GetPhyPageNum();
/*N*/   if ( !((SwRootFrm*)pPage->GetUpper())->IsVirtPageNum() )
/*N*/       return nPhyPage;
/*N*/
/*N*/   //Den am naechsten stehenden Absatz mit virtueller Seitennummer suchen.
/*N*/   //Da das rueckwaertsuchen insgesamt sehr viel Zeit verschlingt suchen
/*N*/   //wir jetzt gezielt ueber die Abhaengigkeiten.
/*N*/   //von den PageDescs bekommen wir die Attribute, von den Attributen
/*N*/   //wiederum bekommen wir die Absaetze.
/*N*/   const SwPageFrm *pVirtPage = 0;
/*N*/   const SwFrm *pFrm = 0;
/*N*/   const SfxItemPool &rPool = pPage->GetFmt()->GetDoc()->GetAttrPool();
/*N*/   const SfxPoolItem* pItem;
/*N*/   USHORT nMaxItems = rPool.GetItemCount( RES_PAGEDESC );
/*N*/   for( USHORT n = 0; n < nMaxItems; ++n )
/*N*/   {
/*N*/       if( 0 == (pItem = rPool.GetItem( RES_PAGEDESC, n ) ))
/*N*/           continue;
/*N*/
/*N*/       const SwFmtPageDesc *pDesc = (SwFmtPageDesc*)pItem;
/*N*/       if ( pDesc->GetNumOffset() && pDesc->GetDefinedIn() )
/*N*/       {
/*N*/           const SwModify *pMod = pDesc->GetDefinedIn();
/*N*/           SwVirtPageNumInfo aInfo( pPage );
/*N*/           pMod->GetInfo( aInfo );
/*N*/           if ( aInfo.GetPage() )
/*N*/           {
/*N*/               if( !pVirtPage || ( pVirtPage && aInfo.GetPage()->
/*N*/                   GetPhyPageNum() > pVirtPage->GetPhyPageNum() ) )
/*N*/               {
/*N*/                   pVirtPage = aInfo.GetPage();
/*N*/                   pFrm = aInfo.GetFrm();
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   if ( pFrm )
/*N*/       return nPhyPage - pFrm->GetPhyPageNum() +
/*N*/              pFrm->GetAttrSet()->GetPageDesc().GetNumOffset();
/*N*/   return nPhyPage;
/*N*/ }

/*************************************************************************
|*
|*  SwRootFrm::MakeTblCrsrs()
|*
|*  Ersterstellung      MA 14. May. 93
|*  Letzte Aenderung    MA 02. Feb. 94
|*
|*************************************************************************/
//Ermitteln und einstellen derjenigen Zellen die von der Selektion
//eingeschlossen sind.

//STRIP001 bool SwRootFrm::MakeTblCrsrs( SwTableCursor& rTblCrsr )
//STRIP001 {
//STRIP001     //Union-Rects und Tabellen (Follows) der Selektion besorgen.
//STRIP001  ASSERT( rTblCrsr.GetCntntNode() && rTblCrsr.GetCntntNode( FALSE ),
//STRIP001          "Tabselection nicht auf Cnt." );
//STRIP001
//STRIP001     bool bRet = false;
//STRIP001
//STRIP001  Point aPtPt, aMkPt;
//STRIP001  {
//STRIP001      SwShellCrsr* pShCrsr =  rTblCrsr.operator SwShellCrsr*();
//STRIP001      // Aufgrund eines CompilerBugs von Linux muss
//STRIP001      // der Zeigeroperator explizit gerufen werden
//STRIP001
//STRIP001      if( pShCrsr )
//STRIP001      {
//STRIP001          aPtPt = pShCrsr->GetPtPos();
//STRIP001          aMkPt = pShCrsr->GetMkPos();
//STRIP001      }
//STRIP001  }
//STRIP001  const SwLayoutFrm *pStart = rTblCrsr.GetCntntNode()->GetFrm(
//STRIP001                                          &aPtPt, 0, FALSE )->GetUpper(),
//STRIP001                    *pEnd   = rTblCrsr.GetCntntNode(FALSE)->GetFrm(
//STRIP001                                          &aMkPt, 0, FALSE )->GetUpper();
//STRIP001
//STRIP001     /* #109590# Only change table boxes if the frames are
//STRIP001         valid. Needed because otherwise the table cursor after moving
//STRIP001         table cells by dnd resulted in an empty tables cursor.  */
//STRIP001     if (pStart->IsValid() && pEnd->IsValid())
//STRIP001     {
//STRIP001         SwSelUnions aUnions;
//STRIP001         ::MakeSelUnions( aUnions, pStart, pEnd );
//STRIP001
//STRIP001         SwSelBoxes aNew;
//STRIP001
//STRIP001         const FASTBOOL bReadOnlyAvailable = rTblCrsr.IsReadOnlyAvailable();
//STRIP001
//STRIP001         for ( USHORT i = 0; i < aUnions.Count(); ++i )
//STRIP001         {
//STRIP001             SwSelUnion *pUnion = aUnions[i];
//STRIP001             const SwTabFrm *pTable = pUnion->GetTable();
//STRIP001
//STRIP001             SwLayoutFrm *pRow = (SwLayoutFrm*)pTable->Lower();
//STRIP001             if ( pRow && pTable->IsFollow() &&
//STRIP001                  pTable->GetTable()->IsHeadlineRepeat() )
//STRIP001                 pRow = (SwLayoutFrm*)pRow->GetNext();
//STRIP001             while ( pRow )
//STRIP001             {
//STRIP001                 if ( pRow->Frm().IsOver( pUnion->GetUnion() ) )
//STRIP001                 {
//STRIP001                     const SwLayoutFrm *pCell = pRow->FirstCell();
//STRIP001
//STRIP001                     while ( pCell && pRow->IsAnLower( pCell ) )
//STRIP001                     {
//STRIP001                         ASSERT( pCell->IsCellFrm(), "Frame ohne Celle" );
//STRIP001                         if( IsFrmInTblSel( pUnion->GetUnion(), pCell ) &&
//STRIP001                             (bReadOnlyAvailable ||
//STRIP001                              !pCell->GetFmt()->GetProtect().IsCntntProtected()))
//STRIP001                         {
//STRIP001                             SwTableBox* pInsBox = (SwTableBox*)
//STRIP001                                 ((SwCellFrm*)pCell)->GetTabBox();
//STRIP001                             aNew.Insert( pInsBox );
//STRIP001                         }
//STRIP001                         if ( pCell->GetNext() )
//STRIP001                         {
//STRIP001                             pCell = (const SwLayoutFrm*)pCell->GetNext();
//STRIP001                             if ( pCell->Lower()->IsRowFrm() )
//STRIP001                                 pCell = pCell->FirstCell();
//STRIP001                         }
//STRIP001                         else
//STRIP001                         {
//STRIP001                             const SwLayoutFrm* pLastCell = pCell;
//STRIP001                             do
//STRIP001                             {
//STRIP001                                 pCell = pCell->GetNextLayoutLeaf();
//STRIP001                             } while ( pCell && pLastCell->IsAnLower( pCell ) );
//STRIP001                             // Fuer (spaltige) Bereiche...
//STRIP001                             if( pCell && pCell->IsInTab() )
//STRIP001                             {
//STRIP001                                 while( !pCell->IsCellFrm() )
//STRIP001                                 {
//STRIP001                                     pCell = pCell->GetUpper();
//STRIP001                                     ASSERT( pCell, "Where's my cell?" );
//STRIP001                                 }
//STRIP001                             }
//STRIP001                         }
//STRIP001                     }
//STRIP001                 }
//STRIP001                 pRow = (SwLayoutFrm*)pRow->GetNext();
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         SwSelBoxes& rOld = (SwSelBoxes&)rTblCrsr.GetBoxes();
//STRIP001         USHORT nOld = 0, nNew = 0;
//STRIP001         while ( nOld < rOld.Count() && nNew < aNew.Count() )
//STRIP001         {
//STRIP001             const SwTableBox* pPOld = *( rOld.GetData() + nOld );
//STRIP001             const SwTableBox* pPNew = *( aNew.GetData() + nNew );
//STRIP001             if( pPOld == pPNew )
//STRIP001             {
//STRIP001                 // diese Box bleibt erhalten
//STRIP001                 ++nOld;
//STRIP001                 aNew.Remove( nNew );
//STRIP001             }
//STRIP001             else if( pPOld->GetSttIdx() < pPNew->GetSttIdx() )
//STRIP001                 rTblCrsr.DeleteBox( nOld );
//STRIP001             else
//STRIP001             {
//STRIP001                 rTblCrsr.InsertBox( *pPNew );
//STRIP001                 ++nOld;
//STRIP001                 ++nNew;
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001         while( nOld < rOld.Count() )
//STRIP001             rTblCrsr.DeleteBox( nOld );
//STRIP001
//STRIP001         for( ; nNew < aNew.Count(); ++nNew )
//STRIP001             rTblCrsr.InsertBox( **( aNew.GetData() + nNew ) );
//STRIP001
//STRIP001         bRet = true;
//STRIP001     }
//STRIP001
//STRIP001     return bRet;
//STRIP001 }


/*************************************************************************
|*
|*  SwRootFrm::CalcFrmRects
|*
|*  Ersterstellung      MA 24. Aug. 92
|*  Letzte Aenderung    MA 24. Aug. 93
|*
|*************************************************************************/

/*
 * nun koennen folgende Situationen auftreten:
 *  1. Start und Ende liegen in einer Bildschirm - Zeile und im
 *     gleichen Node
 *      -> aus Start und End ein Rectangle, dann Ok
 *  2. Start und Ende liegen in einem Frame (dadurch im gleichen Node!)
 *      -> Start nach rechts, End nach links erweitern,
 *         und bei mehr als 2 Bildschirm - Zeilen, das dazwischen
 *         liegende berechnen
 *  3. Start und Ende liegen in verschiedenen Frames
 *      -> Start nach rechts erweitern, bis Frame-Ende Rect berechnen
 *         Ende nach links erweitern, bis Frame-Start Rect berechnen
 *         und bei mehr als 2 Frames von allen dazwischen liegenden
 *         Frames die PrtArea dazu.
 *  4. Wenn es sich um eine Tabellenselektion handelt wird fuer jeden
 *     PaM im Ring der CellFrm besorgt, dessen PrtArea wird zu den
 *     Rechtecken addiert.
 *
 * Grosser Umbau wg. der FlyFrm; denn diese muessen ausgespart werden.
 * Ausnahmen: - Der Fly in dem die Selektion stattfindet (wenn sie in einem Fly
 *              stattfindet).
 *            - Die Flys, die vom Text unterlaufen werden.
 * Arbeitsweise: Zuerst wird eine SwRegion mit der Root initialisiert.
 *               Aus der Region werden die zu invertierenden Bereiche
 *               ausgestantzt. Die Region wird Komprimiert und letztlich
 *               invertiert. Damit liegen dann die zu invertierenden
 *               Rechtecke vor.
 *               Am Ende werden die Flys aus der Region ausgestanzt.
 */

//STRIP001 inline void Sub( SwRegionRects& rRegion, const SwRect& rRect )
//STRIP001 {
//STRIP001  if( rRect.Width() > 1 && rRect.Height() > 1 &&
//STRIP001      rRect.IsOver( rRegion.GetOrigin() ))
//STRIP001      rRegion -= rRect;
//STRIP001 }

//STRIP001 void SwRootFrm::CalcFrmRects( SwShellCrsr &rCrsr, BOOL bIsTblMode )
//STRIP001 {
//STRIP001  ViewShell *pSh = GetShell();
//STRIP001  SwRegionRects aRegion( pSh ? pSh->VisArea() : Frm() );
//STRIP001  const SwNodes &rNds = GetFmt()->GetDoc()->GetNodes();
//STRIP001
//STRIP001  //Erstmal die CntntFrms zum Start und End besorgen, die brauch ich auf
//STRIP001  //jedenfall.
//STRIP001  SwPosition *pStartPos = rCrsr.Start(),
//STRIP001             *pEndPos   = rCrsr.GetPoint() == pStartPos ?
//STRIP001                              rCrsr.GetMark() : rCrsr.GetPoint();
//STRIP001  const SwCntntFrm *pStartFrm = rNds[ pStartPos->nNode ]->
//STRIP001      GetCntntNode()->GetFrm( &rCrsr.GetSttPos(), pStartPos );
//STRIP001
//STRIP001  const SwCntntFrm *pEndFrm   = rNds[ pEndPos->nNode ]->
//STRIP001      GetCntntNode()->GetFrm( &rCrsr.GetEndPos(), pEndPos );
//STRIP001
//STRIP001  ASSERT( (pStartFrm && pEndFrm), "Keine CntntFrms gefunden." );
//STRIP001
//STRIP001  //Damit die FlyFrms, in denen selektierte Frames stecken, nicht
//STRIP001  //abgezogen werden
//STRIP001  SwSortDrawObjs aSortObjs;
//STRIP001  if ( pStartFrm->IsInFly() )
//STRIP001  {
//STRIP001      const SdrObjectPtr pObj = (SdrObject*)pStartFrm->FindFlyFrm()->GetVirtDrawObj();
//STRIP001      aSortObjs.Insert( pObj );
//STRIP001      const SdrObjectPtr pObj2 = (SdrObject*)pEndFrm->FindFlyFrm()->GetVirtDrawObj();
//STRIP001      aSortObjs.Insert( pObj2 );
//STRIP001  }
//STRIP001
//STRIP001  //Fall 4: Tabellenselection
//STRIP001  if( bIsTblMode )
//STRIP001  {
//STRIP001      const SwFrm *pCell = pStartFrm->GetUpper();
//STRIP001      while ( !pCell->IsCellFrm() )
//STRIP001          pCell = pCell->GetUpper();
//STRIP001      SwRect aTmp( pCell->Prt() );
//STRIP001      aTmp.Pos() += pCell->Frm().Pos();
//STRIP001      aRegion.ChangeOrigin( aTmp );
//STRIP001      aRegion.Remove( 0, aRegion.Count() );
//STRIP001      aRegion.Insert( aTmp, 0 );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      // falls eine nicht erlaubte Selection besteht, dann korrigiere das
//STRIP001      // nicht erlaubt ist Header/Footer/TableHeadline ueber 2 Seiten
//STRIP001      do {    // middle check loop
//STRIP001          const SwLayoutFrm* pSttLFrm = pStartFrm->GetUpper();
//STRIP001          const USHORT cHdFtTblHd = FRM_HEADER | FRM_FOOTER | FRM_TAB;
//STRIP001          while( pSttLFrm &&
//STRIP001              ! (cHdFtTblHd & pSttLFrm->GetType() ))
//STRIP001              pSttLFrm = pSttLFrm->GetUpper();
//STRIP001          if( !pSttLFrm )
//STRIP001              break;
//STRIP001          const SwLayoutFrm* pEndLFrm = pEndFrm->GetUpper();
//STRIP001          while( pEndLFrm &&
//STRIP001              ! (cHdFtTblHd & pEndLFrm->GetType() ))
//STRIP001              pEndLFrm = pEndLFrm->GetUpper();
//STRIP001          if( !pEndLFrm )
//STRIP001              break;
//STRIP001
//STRIP001          ASSERT( pEndLFrm->GetType() == pSttLFrm->GetType(),
//STRIP001                  "Selection ueber unterschiedliche Inhalte" );
//STRIP001          switch( pSttLFrm->GetType() )
//STRIP001          {
//STRIP001          case FRM_HEADER:
//STRIP001          case FRM_FOOTER:
//STRIP001              // auf unterschiedlichen Seiten ??
//STRIP001              // dann immer auf die Start-Seite
//STRIP001              if( pEndLFrm->FindPageFrm() != pSttLFrm->FindPageFrm() )
//STRIP001              {
//STRIP001                  // End- auf den Start-CntntFrame setzen
//STRIP001                  if( pStartPos == rCrsr.GetPoint() )
//STRIP001                      pEndFrm = pStartFrm;
//STRIP001                  else
//STRIP001                      pStartFrm = pEndFrm;
//STRIP001              }
//STRIP001              break;
//STRIP001          case FRM_TAB:
//STRIP001              // auf unterschiedlichen Seiten ??
//STRIP001              // existiert
//STRIP001              // dann teste auf Tabelle-Headline
//STRIP001              {
//STRIP001                  const SwTabFrm* pTabFrm = (SwTabFrm*)pSttLFrm;
//STRIP001                  if( ( pTabFrm->GetFollow() ||
//STRIP001                      ((SwTabFrm*)pEndLFrm)->GetFollow() ) &&
//STRIP001                      pTabFrm->GetTable()->IsHeadlineRepeat() &&
//STRIP001                      pTabFrm->GetLower() !=
//STRIP001                          ((SwTabFrm*)pEndLFrm)->GetLower() )
//STRIP001                  {
//STRIP001                      // End- auf den Start-CntntFrame setzen
//STRIP001                      if( pStartPos == rCrsr.GetPoint() )
//STRIP001                          pEndFrm = pStartFrm;
//STRIP001                      else
//STRIP001                          pStartFrm = pEndFrm;
//STRIP001                  }
//STRIP001              }
//STRIP001              break;
//STRIP001          }
//STRIP001      } while( FALSE );
//STRIP001
//STRIP001      SwCrsrMoveState aTmpState( MV_NONE );
//STRIP001      aTmpState.b2Lines = sal_True;
//STRIP001         aTmpState.bNoScroll = sal_True;
//STRIP001         aTmpState.nCursorBidiLevel = pStartFrm->IsRightToLeft() ? 1 : 0;
//STRIP001
//STRIP001         //CntntRects zu Start- und EndFrms.
//STRIP001      SwRect aStRect, aEndRect;
//STRIP001      pStartFrm->GetCharRect( aStRect, *pStartPos, &aTmpState );
//STRIP001      Sw2LinesPos *pSt2Pos = aTmpState.p2Lines;
//STRIP001      aTmpState.p2Lines = NULL;
//STRIP001         aTmpState.nCursorBidiLevel = pEndFrm->IsRightToLeft() ? 1 : 0;
//STRIP001
//STRIP001         pEndFrm->GetCharRect  ( aEndRect, *pEndPos, &aTmpState );
//STRIP001      Sw2LinesPos *pEnd2Pos = aTmpState.p2Lines;
//STRIP001
//STRIP001      SwRect aStFrm ( pStartFrm->UnionFrm( sal_True ) );
//STRIP001      aStFrm.Intersection( pStartFrm->PaintArea() );
//STRIP001      SwRect aEndFrm( pStartFrm == pEndFrm ? aStFrm :
//STRIP001                                             pEndFrm->UnionFrm( sal_True ) );
//STRIP001      if( pStartFrm != pEndFrm )
//STRIP001          aEndFrm.Intersection( pEndFrm->PaintArea() );
//STRIP001         SWRECTFN( pStartFrm )
//STRIP001         const BOOL bR2L = pStartFrm->IsRightToLeft();
//STRIP001         const BOOL bEndR2L = pEndFrm->IsRightToLeft();
//STRIP001
//STRIP001         // If there's no doubleline portion involved or start and end are both
//STRIP001      // in the same doubleline portion, all works fine, but otherwise
//STRIP001      // we need the following...
//STRIP001      if( pSt2Pos != pEnd2Pos && ( !pSt2Pos || !pEnd2Pos ||
//STRIP001             pSt2Pos->aPortion != pEnd2Pos->aPortion ) )
//STRIP001      {
//STRIP001          // If we have a start(end) position inside a doubleline portion
//STRIP001          // the surrounded part of the doubleline portion is subtracted
//STRIP001          // from the region and the aStRect(aEndRect) is set to the
//STRIP001          // end(start) of the doubleline portion.
//STRIP001             if( pSt2Pos )
//STRIP001          {
//STRIP001                 SwRect aTmp( aStRect );
//STRIP001
//STRIP001                 // BiDi-Portions are swimming against the current.
//STRIP001                 const sal_Bool bPorR2L = ( MT_BIDI == pSt2Pos->nMultiType ) ?
//STRIP001                                            ! bR2L :
//STRIP001                                              bR2L;
//STRIP001
//STRIP001                 if( MT_BIDI == pSt2Pos->nMultiType &&
//STRIP001                     (pSt2Pos->aPortion2.*fnRect->fnGetWidth)() )
//STRIP001                 {
//STRIP001                     // nested bidi portion
//STRIP001                     long nRightAbs = (pSt2Pos->aPortion.*fnRect->fnGetRight)();
//STRIP001                     nRightAbs -= (pSt2Pos->aPortion2.*fnRect->fnGetLeft)();
//STRIP001                     long nLeftAbs = nRightAbs - (pSt2Pos->aPortion2.*fnRect->fnGetWidth)();
//STRIP001
//STRIP001                     (aTmp.*fnRect->fnSetRight)( nRightAbs );
//STRIP001
//STRIP001                     if ( ! pEnd2Pos || pEnd2Pos->aPortion != pSt2Pos->aPortion )
//STRIP001                     {
//STRIP001                         SwRect aTmp2( pSt2Pos->aPortion );
//STRIP001                         (aTmp2.*fnRect->fnSetRight)( nLeftAbs );
//STRIP001                         aTmp2.Intersection( aEndFrm );
//STRIP001                         Sub( aRegion, aTmp2 );
//STRIP001                     }
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     if( bPorR2L )
//STRIP001                         (aTmp.*fnRect->fnSetLeft)(
//STRIP001                             (pSt2Pos->aPortion.*fnRect->fnGetLeft)() );
//STRIP001                     else
//STRIP001                         (aTmp.*fnRect->fnSetRight)(
//STRIP001                             (pSt2Pos->aPortion.*fnRect->fnGetRight)() );
//STRIP001                 }
//STRIP001
//STRIP001                 if( MT_ROT_90 == pSt2Pos->nMultiType ||
//STRIP001                     (pSt2Pos->aPortion.*fnRect->fnGetTop)() ==
//STRIP001                     (aTmp.*fnRect->fnGetTop)() )
//STRIP001                 {
//STRIP001                     (aTmp.*fnRect->fnSetTop)(
//STRIP001                         (pSt2Pos->aLine.*fnRect->fnGetTop)() );
//STRIP001                 }
//STRIP001
//STRIP001                 aTmp.Intersection( aStFrm );
//STRIP001              Sub( aRegion, aTmp );
//STRIP001
//STRIP001                 SwTwips nTmp = (pSt2Pos->aLine.*fnRect->fnGetBottom)();
//STRIP001                 if( MT_ROT_90 != pSt2Pos->nMultiType &&
//STRIP001                     (aStRect.*fnRect->fnBottomDist)( nTmp ) > 0 )
//STRIP001                 {
//STRIP001                     (aTmp.*fnRect->fnSetTop)( (aTmp.*fnRect->fnGetBottom)() );
//STRIP001                     (aTmp.*fnRect->fnSetBottom)( nTmp );
//STRIP001                     if( (aStRect.*fnRect->fnBottomDist)(
//STRIP001                         (pSt2Pos->aPortion.*fnRect->fnGetBottom)() ) > 0 )
//STRIP001                     {
//STRIP001                         if( bPorR2L )
//STRIP001                             (aTmp.*fnRect->fnSetRight)(
//STRIP001                                 (pSt2Pos->aPortion.*fnRect->fnGetRight)() );
//STRIP001                         else
//STRIP001                             (aTmp.*fnRect->fnSetLeft)(
//STRIP001                                 (pSt2Pos->aPortion.*fnRect->fnGetLeft)() );
//STRIP001                     }
//STRIP001                     aTmp.Intersection( aStFrm );
//STRIP001                     Sub( aRegion, aTmp );
//STRIP001                 }
//STRIP001
//STRIP001                 aStRect = pSt2Pos->aLine;
//STRIP001                 (aStRect.*fnRect->fnSetLeft)( bR2L ?
//STRIP001                         (pSt2Pos->aPortion.*fnRect->fnGetLeft)() :
//STRIP001                         (pSt2Pos->aPortion.*fnRect->fnGetRight)() );
//STRIP001                 (aStRect.*fnRect->fnSetWidth)( 1 );
//STRIP001          }
//STRIP001
//STRIP001             if( pEnd2Pos )
//STRIP001          {
//STRIP001                 SWRECTFN( pEndFrm )
//STRIP001                 SwRect aTmp( aEndRect );
//STRIP001
//STRIP001                 // BiDi-Portions are swimming against the current.
//STRIP001                 const sal_Bool bPorR2L = ( MT_BIDI == pEnd2Pos->nMultiType ) ?
//STRIP001                                            ! bEndR2L :
//STRIP001                                              bEndR2L;
//STRIP001
//STRIP001                 if( MT_BIDI == pEnd2Pos->nMultiType &&
//STRIP001                     (pEnd2Pos->aPortion2.*fnRect->fnGetWidth)() )
//STRIP001                 {
//STRIP001                     // nested bidi portion
//STRIP001                     long nRightAbs = (pEnd2Pos->aPortion.*fnRect->fnGetRight)();
//STRIP001                     nRightAbs = nRightAbs - (pEnd2Pos->aPortion2.*fnRect->fnGetLeft)();
//STRIP001                     long nLeftAbs = nRightAbs - (pEnd2Pos->aPortion2.*fnRect->fnGetWidth)();
//STRIP001
//STRIP001                     (aTmp.*fnRect->fnSetLeft)( nLeftAbs );
//STRIP001
//STRIP001                     if ( ! pSt2Pos || pSt2Pos->aPortion != pEnd2Pos->aPortion )
//STRIP001                     {
//STRIP001                         SwRect aTmp2( pEnd2Pos->aPortion );
//STRIP001                         (aTmp2.*fnRect->fnSetLeft)( nRightAbs );
//STRIP001                         aTmp2.Intersection( aEndFrm );
//STRIP001                         Sub( aRegion, aTmp2 );
//STRIP001                     }
//STRIP001                 }
//STRIP001                 else
//STRIP001                 {
//STRIP001                     if ( bPorR2L )
//STRIP001                         (aTmp.*fnRect->fnSetRight)(
//STRIP001                             (pEnd2Pos->aPortion.*fnRect->fnGetRight)() );
//STRIP001                     else
//STRIP001                         (aTmp.*fnRect->fnSetLeft)(
//STRIP001                             (pEnd2Pos->aPortion.*fnRect->fnGetLeft)() );
//STRIP001                 }
//STRIP001
//STRIP001                 if( MT_ROT_90 == pEnd2Pos->nMultiType ||
//STRIP001                     (pEnd2Pos->aPortion.*fnRect->fnGetBottom)() ==
//STRIP001                     (aEndRect.*fnRect->fnGetBottom)() )
//STRIP001                 {
//STRIP001                     (aTmp.*fnRect->fnSetBottom)(
//STRIP001                         (pEnd2Pos->aLine.*fnRect->fnGetBottom)() );
//STRIP001                 }
//STRIP001
//STRIP001                 aTmp.Intersection( aEndFrm );
//STRIP001              Sub( aRegion, aTmp );
//STRIP001
//STRIP001                 // The next statement means neither ruby nor rotate(90):
//STRIP001                 if( !( MT_RUBY & pEnd2Pos->nMultiType ) )
//STRIP001                 {
//STRIP001                     SwTwips nTmp = (pEnd2Pos->aLine.*fnRect->fnGetTop)();
//STRIP001                     if( (aEndRect.*fnRect->fnGetTop)() != nTmp )
//STRIP001                     {
//STRIP001                         (aTmp.*fnRect->fnSetBottom)(
//STRIP001                             (aTmp.*fnRect->fnGetTop)() );
//STRIP001                         (aTmp.*fnRect->fnSetTop)( nTmp );
//STRIP001                         if( (aEndRect.*fnRect->fnGetTop)() !=
//STRIP001                             (pEnd2Pos->aPortion.*fnRect->fnGetTop)() )
//STRIP001                         if( bPorR2L )
//STRIP001                             (aTmp.*fnRect->fnSetLeft)(
//STRIP001                                 (pEnd2Pos->aPortion.*fnRect->fnGetLeft)() );
//STRIP001                         else
//STRIP001                             (aTmp.*fnRect->fnSetRight)(
//STRIP001                                 (pEnd2Pos->aPortion.*fnRect->fnGetRight)() );
//STRIP001                         aTmp.Intersection( aEndFrm );
//STRIP001                         Sub( aRegion, aTmp );
//STRIP001                     }
//STRIP001                 }
//STRIP001
//STRIP001                 aEndRect = pEnd2Pos->aLine;
//STRIP001                 (aEndRect.*fnRect->fnSetLeft)( bEndR2L ?
//STRIP001                         (pEnd2Pos->aPortion.*fnRect->fnGetRight)() :
//STRIP001                         (pEnd2Pos->aPortion.*fnRect->fnGetLeft)() );
//STRIP001                 (aEndRect.*fnRect->fnSetWidth)( 1 );
//STRIP001          }
//STRIP001      }
//STRIP001         else if( pSt2Pos && pEnd2Pos &&
//STRIP001                  MT_BIDI == pSt2Pos->nMultiType &&
//STRIP001                  MT_BIDI == pEnd2Pos->nMultiType &&
//STRIP001                  pSt2Pos->aPortion == pEnd2Pos->aPortion &&
//STRIP001                  pSt2Pos->aPortion2 != pEnd2Pos->aPortion2 )
//STRIP001         {
//STRIP001             // This is the ugly special case, where the selection starts and
//STRIP001             // ends in the same bidi portion but one start or end is inside a
//STRIP001             // nested bidi portion.
//STRIP001
//STRIP001             if ( (pSt2Pos->aPortion2.*fnRect->fnGetWidth)() )
//STRIP001             {
//STRIP001                 SwRect aTmp( aStRect );
//STRIP001                 long nRightAbs = (pSt2Pos->aPortion.*fnRect->fnGetRight)();
//STRIP001                 nRightAbs -= (pSt2Pos->aPortion2.*fnRect->fnGetLeft)();
//STRIP001                 long nLeftAbs = nRightAbs - (pSt2Pos->aPortion2.*fnRect->fnGetWidth)();
//STRIP001
//STRIP001                 (aTmp.*fnRect->fnSetRight)( nRightAbs );
//STRIP001                 aTmp.Intersection( aStFrm );
//STRIP001                 Sub( aRegion, aTmp );
//STRIP001
//STRIP001                 aStRect = pSt2Pos->aLine;
//STRIP001                 (aStRect.*fnRect->fnSetLeft)( bR2L ? nRightAbs : nLeftAbs );
//STRIP001                 (aStRect.*fnRect->fnSetWidth)( 1 );
//STRIP001             }
//STRIP001
//STRIP001             SWRECTFN( pEndFrm )
//STRIP001             if ( (pEnd2Pos->aPortion2.*fnRect->fnGetWidth)() )
//STRIP001             {
//STRIP001                 SwRect aTmp( aEndRect );
//STRIP001                 long nRightAbs = (pEnd2Pos->aPortion.*fnRect->fnGetRight)();
//STRIP001                 nRightAbs -= (pEnd2Pos->aPortion2.*fnRect->fnGetLeft)();
//STRIP001                 long nLeftAbs = nRightAbs - (pEnd2Pos->aPortion2.*fnRect->fnGetWidth)();
//STRIP001
//STRIP001                 (aTmp.*fnRect->fnSetLeft)( nLeftAbs );
//STRIP001                 aTmp.Intersection( aEndFrm );
//STRIP001                 Sub( aRegion, aTmp );
//STRIP001
//STRIP001                 aEndRect = pEnd2Pos->aLine;
//STRIP001                 (aEndRect.*fnRect->fnSetLeft)( bEndR2L ? nLeftAbs : nRightAbs );
//STRIP001                 (aEndRect.*fnRect->fnSetWidth)( 1 );
//STRIP001             }
//STRIP001         }
//STRIP001
//STRIP001      // The charrect may be outside the paintarea (for cursortravelling)
//STRIP001      // but the selection has to be restricted to the paintarea
//STRIP001      if( aStRect.Left() < aStFrm.Left() )
//STRIP001          aStRect.Left( aStFrm.Left() );
//STRIP001      else if( aStRect.Left() > aStFrm.Right() )
//STRIP001          aStRect.Left( aStFrm.Right() );
//STRIP001      SwTwips nTmp = aStRect.Right();
//STRIP001      if( nTmp < aStFrm.Left() )
//STRIP001          aStRect.Right( aStFrm.Left() );
//STRIP001      else if( nTmp > aStFrm.Right() )
//STRIP001          aStRect.Right( aStFrm.Right() );
//STRIP001      if( aEndRect.Left() < aEndFrm.Left() )
//STRIP001          aEndRect.Left( aEndFrm.Left() );
//STRIP001      else if( aEndRect.Left() > aEndFrm.Right() )
//STRIP001          aEndRect.Left( aEndFrm.Right() );
//STRIP001      nTmp = aEndRect.Right();
//STRIP001      if( nTmp < aEndFrm.Left() )
//STRIP001          aEndRect.Right( aEndFrm.Left() );
//STRIP001      else if( nTmp > aEndFrm.Right() )
//STRIP001          aEndRect.Right( aEndFrm.Right() );
//STRIP001
//STRIP001      if( pStartFrm == pEndFrm )
//STRIP001      {
//STRIP001             sal_Bool bSameRotatedOrBidi = pSt2Pos && pEnd2Pos &&
//STRIP001                 ( MT_BIDI & pSt2Pos->nMultiType ) &&
//STRIP001                 pSt2Pos->aPortion == pEnd2Pos->aPortion;
//STRIP001             //case 1: (Same frame and same row)
//STRIP001             if( bSameRotatedOrBidi ||
//STRIP001                 (aStRect.*fnRect->fnGetTop)() == (aEndRect.*fnRect->fnGetTop)() )
//STRIP001          {
//STRIP001              Point aTmpSt( aStRect.Pos() );
//STRIP001              Point aTmpEnd( aEndRect.Right(), aEndRect.Bottom() );
//STRIP001                 if( bSameRotatedOrBidi || bR2L )
//STRIP001                 {
//STRIP001                     if( aTmpSt.Y() > aTmpEnd.Y() )
//STRIP001                     {
//STRIP001                         long nTmpY = aTmpEnd.Y();
//STRIP001                         aTmpEnd.Y() = aTmpSt.Y();
//STRIP001                         aTmpSt.Y() = nTmpY;
//STRIP001                     }
//STRIP001                     if( aTmpSt.X() > aTmpEnd.X() )
//STRIP001                     {
//STRIP001                         long nTmpX = aTmpEnd.X();
//STRIP001                         aTmpEnd.X() = aTmpSt.X();
//STRIP001                         aTmpSt.X() = nTmpX;
//STRIP001                     }
//STRIP001                 }
//STRIP001
//STRIP001              SwRect aTmp = SwRect( aTmpSt, aTmpEnd );
//STRIP001              // Bug 34888: falls Inhalt selektiert ist, der keinen Platz
//STRIP001              //            einnimmt (z.B. PostIts,RefMarks, TOXMarks),
//STRIP001              //            dann mindestens die Breite des Crsr setzen.
//STRIP001                 if( 1 == (aTmp.*fnRect->fnGetWidth)() &&
//STRIP001                     pStartPos->nContent.GetIndex() !=
//STRIP001                     pEndPos->nContent.GetIndex() )
//STRIP001              {
//STRIP001                  OutputDevice* pOut = pSh->GetOut();
//STRIP001                  long nCrsrWidth = pOut->GetSettings().GetStyleSettings().
//STRIP001                                      GetCursorSize();
//STRIP001                     (aTmp.*fnRect->fnSetWidth)( pOut->PixelToLogic(
//STRIP001                                               Size( nCrsrWidth, 0 ) ).Width() );
//STRIP001              }
//STRIP001              aTmp.Intersection( aStFrm );
//STRIP001              Sub( aRegion, aTmp );
//STRIP001          }
//STRIP001             //case 2: (Same frame, but not the same line)
//STRIP001          else
//STRIP001          {
//STRIP001              SwTwips lLeft, lRight;
//STRIP001              if( pSt2Pos && pEnd2Pos && pSt2Pos->aPortion == pEnd2Pos->aPortion )
//STRIP001              {
//STRIP001                     lLeft = (pSt2Pos->aPortion.*fnRect->fnGetLeft)();
//STRIP001                     lRight = (pSt2Pos->aPortion.*fnRect->fnGetRight)();
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                     lLeft = (pStartFrm->Frm().*fnRect->fnGetLeft)() +
//STRIP001                             (pStartFrm->Prt().*fnRect->fnGetLeft)();
//STRIP001                     lRight = (pStartFrm->Frm().*fnRect->fnGetLeft)() +
//STRIP001                              (pStartFrm->Prt().*fnRect->fnGetRight)();
//STRIP001              }
//STRIP001                 if( lLeft < (aStFrm.*fnRect->fnGetLeft)() )
//STRIP001                     lLeft = (aStFrm.*fnRect->fnGetLeft)();
//STRIP001                 if( lRight > (aStFrm.*fnRect->fnGetRight)() )
//STRIP001                     lRight = (aStFrm.*fnRect->fnGetRight)();
//STRIP001                 SwRect aSubRect( aStRect );
//STRIP001                 //First line
//STRIP001                 if( bR2L )
//STRIP001                     (aSubRect.*fnRect->fnSetLeft)( lLeft );
//STRIP001                 else
//STRIP001                     (aSubRect.*fnRect->fnSetRight)( lRight );
//STRIP001                 Sub( aRegion, aSubRect );
//STRIP001
//STRIP001                 //If there's at least a twips between start- and endline,
//STRIP001                 //so the whole area between will be added.
//STRIP001                 SwTwips aTmpBottom = (aStRect.*fnRect->fnGetBottom)();
//STRIP001                 SwTwips aTmpTop = (aEndRect.*fnRect->fnGetTop)();
//STRIP001                 if( aTmpBottom != aTmpTop )
//STRIP001                 {
//STRIP001                     (aSubRect.*fnRect->fnSetLeft)( lLeft );
//STRIP001                     (aSubRect.*fnRect->fnSetRight)( lRight );
//STRIP001                     (aSubRect.*fnRect->fnSetTop)( aTmpBottom );
//STRIP001                     (aSubRect.*fnRect->fnSetBottom)( aTmpTop );
//STRIP001                     Sub( aRegion, aSubRect );
//STRIP001                 }
//STRIP001                 //and the last line
//STRIP001                 aSubRect = aEndRect;
//STRIP001                 if( bR2L )
//STRIP001                     (aSubRect.*fnRect->fnSetRight)( lRight );
//STRIP001                 else
//STRIP001                     (aSubRect.*fnRect->fnSetLeft)( lLeft );
//STRIP001                 Sub( aRegion, aSubRect );
//STRIP001          }
//STRIP001      }
//STRIP001         //case 3: (Different frames, maybe with ohther frames between
//STRIP001      else
//STRIP001      {
//STRIP001             //The startframe first...
//STRIP001             SwRect aSubRect( aStRect );
//STRIP001             if( bR2L )
//STRIP001                 (aSubRect.*fnRect->fnSetLeft)( (aStFrm.*fnRect->fnGetLeft)());
//STRIP001             else
//STRIP001                 (aSubRect.*fnRect->fnSetRight)( (aStFrm.*fnRect->fnGetRight)());
//STRIP001             Sub( aRegion, aSubRect );
//STRIP001             SwTwips nTmp = (aStRect.*fnRect->fnGetBottom)();
//STRIP001             if( (aStFrm.*fnRect->fnGetBottom)() != nTmp )
//STRIP001             {
//STRIP001                 aSubRect = aStFrm;
//STRIP001                 (aSubRect.*fnRect->fnSetTop)( nTmp );
//STRIP001                 Sub( aRegion, aSubRect );
//STRIP001             }
//STRIP001
//STRIP001             //Now the frames between, if there are any
//STRIP001          BOOL bBody = pStartFrm->IsInDocBody();
//STRIP001          const SwCntntFrm *pCntnt = pStartFrm->GetNextCntntFrm();
//STRIP001          SwRect aPrvRect;
//STRIP001
//STRIP001          while ( pCntnt != pEndFrm )
//STRIP001          {
//STRIP001              if ( pCntnt->IsInFly() )
//STRIP001              {
//STRIP001                  const SdrObjectPtr pObj = (SdrObject*)pCntnt->FindFlyFrm()->GetVirtDrawObj();
//STRIP001                  aSortObjs.Insert( pObj );
//STRIP001              }
//STRIP001
//STRIP001              //Wenn ich im DocumentBody war, so beachte ich nur Frm's
//STRIP001              //die im Body liegen und umgekehrt.
//STRIP001              if ( bBody == pCntnt->IsInDocBody() )
//STRIP001              {
//STRIP001                  SwRect aCRect( pCntnt->UnionFrm( sal_True ) );
//STRIP001                  aCRect.Intersection( pCntnt->PaintArea() );
//STRIP001                  if( aCRect.IsOver( aRegion.GetOrigin() ))
//STRIP001                  {
//STRIP001                      SwRect aTmp( aPrvRect );
//STRIP001                      aTmp.Union( aCRect );
//STRIP001                      if ( (aPrvRect.Height() * aPrvRect.Width() +
//STRIP001                          aCRect.Height()   * aCRect.Width()) ==
//STRIP001                          (aTmp.Height() * aTmp.Width()) )
//STRIP001                      {
//STRIP001                          aPrvRect.Union( aCRect );
//STRIP001                      }
//STRIP001                      else
//STRIP001                      {
//STRIP001                          if ( aPrvRect.HasArea() )
//STRIP001                              Sub( aRegion, aPrvRect );
//STRIP001                          aPrvRect = aCRect;
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001              pCntnt = pCntnt->GetNextCntntFrm();
//STRIP001          }
//STRIP001          if ( aPrvRect.HasArea() )
//STRIP001              Sub( aRegion, aPrvRect );
//STRIP001
//STRIP001             //At least the endframe...
//STRIP001             bVert = pEndFrm->IsVertical();
//STRIP001             bRev = pEndFrm->IsReverse();
//STRIP001             fnRect = bVert ? ( bRev ? fnRectVL2R : fnRectVert ) :
//STRIP001                              ( bRev ? fnRectB2T : fnRectHori );
//STRIP001             nTmp = (aEndRect.*fnRect->fnGetTop)();
//STRIP001             if( (aEndFrm.*fnRect->fnGetTop)() != nTmp )
//STRIP001             {
//STRIP001                 aSubRect = aEndFrm;
//STRIP001                 (aSubRect.*fnRect->fnSetBottom)( nTmp );
//STRIP001                 Sub( aRegion, aSubRect );
//STRIP001             }
//STRIP001             aSubRect = aEndRect;
//STRIP001             if( bEndR2L )
//STRIP001                 (aSubRect.*fnRect->fnSetRight)((aEndFrm.*fnRect->fnGetRight)());
//STRIP001             else
//STRIP001                 (aSubRect.*fnRect->fnSetLeft)( (aEndFrm.*fnRect->fnGetLeft)() );
//STRIP001             Sub( aRegion, aSubRect );
//STRIP001      }
//STRIP001
//STRIP001 //       aRegion.Compress( FALSE );
//STRIP001      aRegion.Invert();
//STRIP001      delete pSt2Pos;
//STRIP001      delete pEnd2Pos;
//STRIP001  }
//STRIP001
//STRIP001  //Flys mit Durchlauf ausstanzen. Nicht ausgestanzt werden Flys:
//STRIP001  //- die Lower des StartFrm/EndFrm sind (FlyInCnt und alle Flys die wiederum
//STRIP001  //  darin sitzen)
//STRIP001  //- in der Z-Order ueber denjenigen Flys stehen in denen sich der StartFrm
//STRIP001  //  befindet.
//STRIP001  const SwPageFrm *pPage      = pStartFrm->FindPageFrm();
//STRIP001  const SwPageFrm *pEndPage   = pEndFrm->FindPageFrm();
//STRIP001  const SwFlyFrm  *pStartFly  = pStartFrm->FindFlyFrm();
//STRIP001  const SwFlyFrm  *pEndFly    = pEndFrm->FindFlyFrm();
//STRIP001  while ( pPage )
//STRIP001  {
//STRIP001      if ( pPage->GetSortedObjs() )
//STRIP001      {
//STRIP001          const SwSortDrawObjs &rObjs = *pPage->GetSortedObjs();
//STRIP001          for ( USHORT i = 0; i < rObjs.Count(); ++i )
//STRIP001          {
//STRIP001              SdrObject *pO = rObjs[i];
//STRIP001              if ( !pO->IsWriterFlyFrame() )
//STRIP001                  continue;
//STRIP001              const SwVirtFlyDrawObj *pObj = (SwVirtFlyDrawObj*)pO;
//STRIP001              const SwLayoutFrm *pFly = pObj->GetFlyFrm();
//STRIP001              const SwFmtSurround &rSur = pFly->GetFmt()->GetSurround();
//STRIP001              if ( !pFly->IsAnLower( pStartFrm ) &&
//STRIP001                   (rSur.GetSurround() != SURROUND_THROUGHT &&
//STRIP001                    !rSur.IsContour()) )
//STRIP001              {
//STRIP001                  if ( USHRT_MAX != aSortObjs.Seek_Entry( pO ) )
//STRIP001                      continue;
//STRIP001
//STRIP001                  FASTBOOL bSub = TRUE;
//STRIP001                  const UINT32 nPos = pObj->GetOrdNum();
//STRIP001                  for ( USHORT k = 0; bSub && k < aSortObjs.Count(); ++k )
//STRIP001                  {
//STRIP001                      SwFlyFrm *pTmp = ((SwVirtFlyDrawObj*)aSortObjs[k])->GetFlyFrm();
//STRIP001                      do
//STRIP001                      {   if ( nPos < pTmp->GetVirtDrawObj()->GetOrdNumDirect() )
//STRIP001                              bSub = FALSE;
//STRIP001                          else
//STRIP001                              pTmp = pTmp->GetAnchor()->FindFlyFrm();
//STRIP001                      } while ( bSub && pTmp );
//STRIP001                  }
//STRIP001                  if ( bSub )
//STRIP001                      Sub( aRegion, pFly->Frm() );
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      if ( pPage == pEndPage )
//STRIP001          break;
//STRIP001      else
//STRIP001          pPage = (SwPageFrm*)pPage->GetNext();
//STRIP001  }
//STRIP001
//STRIP001  //Weil's besser aussieht noch die DropCaps ausschliessen.
//STRIP001  SwRect aDropRect;
//STRIP001  if ( pStartFrm->IsTxtFrm() )
//STRIP001  {
//STRIP001      if ( ((SwTxtFrm*)pStartFrm)->GetDropRect( aDropRect ) )
//STRIP001          Sub( aRegion, aDropRect );
//STRIP001  }
//STRIP001  if ( pEndFrm != pStartFrm && pEndFrm->IsTxtFrm() )
//STRIP001  {
//STRIP001      if ( ((SwTxtFrm*)pEndFrm)->GetDropRect( aDropRect ) )
//STRIP001          Sub( aRegion, aDropRect );
//STRIP001  }
//STRIP001
//STRIP001  rCrsr.Remove( 0, rCrsr.Count() );
//STRIP001  rCrsr.Insert( &aRegion, 0 );
//STRIP001 }


}
