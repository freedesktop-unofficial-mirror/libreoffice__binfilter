/*************************************************************************
 *
 *  $RCSfile: svx_svdviter.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:22:17 $
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

#include "svdviter.hxx"
#include "svdobj.hxx"
#include "svdpage.hxx"
#include "svdmodel.hxx"
#include "svdview.hxx"
#include "svdpagv.hxx"
#include "svdsob.hxx"

#ifndef _SFXBRDCST_HXX //autogen
#include <svtools/brdcst.hxx>
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrViewIter::ImpInitVars()
/*N*/ {
/*N*/   nListenerNum=0;
/*N*/   nPageViewNum=0;
/*N*/   nOutDevNum=0;
/*N*/   pAktView=NULL;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 SdrViewIter::SdrViewIter(const SdrModel* pModel_)
//STRIP001 {
//STRIP001  pModel=pModel_;
//STRIP001  pPage=NULL;
//STRIP001  pObject=NULL;
//STRIP001  ImpInitVars();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 SdrViewIter::SdrViewIter(const SdrPage* pPage_, FASTBOOL bNoMasterPage_)
//STRIP001 {
//STRIP001  pPage=pPage_;
//STRIP001  pModel=pPage_!=NULL ? pPage_->GetModel() : NULL;
//STRIP001  pObject=NULL;
//STRIP001  bNoMasterPage=bNoMasterPage_;
//STRIP001  ImpInitVars();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrViewIter::SdrViewIter(const SdrObject* pObject_, FASTBOOL bNoMasterPage_)
/*N*/ {
/*N*/   pObject=pObject_;
/*N*/   pModel=pObject_!=NULL ? pObject_->GetModel() : NULL;
/*N*/   pPage=pObject_!=NULL ? pObject_->GetPage() : NULL;
/*N*/   bNoMasterPage=bNoMasterPage_;
/*N*/   if (pModel==NULL || pPage==NULL) {
/*N*/       pModel=NULL;
/*N*/       pPage=NULL;
/*N*/   }
/*N*/   ImpInitVars();
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ FASTBOOL SdrViewIter::ImpCheckPageView(SdrPageView* pPV) const
/*N*/ {
/*N*/   if (pPage!=NULL) {
/*N*/       FASTBOOL bMaster=pPage->IsMasterPage();
/*N*/       USHORT nPageNum=pPage->GetPageNum();
/*N*/       SdrPage* pPg=pPV->GetPage();
/*N*/       if (pPg==pPage) {
/*N*/           if (pObject!=NULL) {
/*N*/               // Objekt gewuenscht? Na dann erstmal sehen, ob
/*N*/               // das Obj in dieser PageView auch sichtbar ist.
/*N*/               SetOfByte aObjLay;
/*N*/               pObject->GetLayer(aObjLay);
/*N*/               aObjLay&=pPV->GetVisibleLayers();
/*N*/               return !aObjLay.IsEmpty();
/*N*/           } else {
/*N*/               return TRUE;
/*N*/           }
/*N*/       } else {
/*N*/           if (!bNoMasterPage && bMaster && (pObject==NULL || !pObject->IsNotVisibleAsMaster())) {
/*N*/               USHORT nMasterPageAnz=pPg->GetMasterPageCount();
/*N*/               USHORT nMasterPagePos=0;
/*N*/               while (nMasterPagePos<nMasterPageAnz) {
/*N*/                   if (nPageNum==pPg->GetMasterPageNum(nMasterPagePos)) {
/*N*/                       // Aha, die gewuenschte Page ist also MasterPage in dieser PageView
/*N*/                       if (pObject!=NULL) {
/*N*/                           // Objekt gewuenscht? Na dann erstmal sehen, ob
/*N*/                           // das Obj in dieser PageView auch sichtbar ist.
/*N*/                           SetOfByte aObjLay;
/*N*/                           pObject->GetLayer(aObjLay);
/*N*/                           aObjLay&=pPV->GetVisibleLayers();
/*N*/                           aObjLay&=pPg->GetMasterPageVisibleLayers(nMasterPagePos);
/*N*/                           if (!aObjLay.IsEmpty()) {
/*N*/                               return TRUE;
/*N*/                           } // ansonsten die naechste MasterPage der Page ansehen...
/*N*/                       } else {
/*N*/                           return TRUE;
/*N*/                       }
/*N*/                   }
/*N*/                   nMasterPagePos++;
/*N*/               }
/*N*/           }
/*N*/           // MasterPage nicht erlaubt oder keine passende gefunden
/*N*/           return FALSE;
/*N*/       }
/*N*/   } else {
/*N*/       return TRUE;
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrView* SdrViewIter::ImpFindView()
/*N*/ {
/*N*/   if (pModel!=NULL) {
/*N*/       USHORT nLsAnz=pModel->GetListenerCount();
/*N*/       while (nListenerNum<nLsAnz) {
/*N*/           SfxListener* pLs=pModel->GetListener(nListenerNum);
/*N*/           pAktView=PTR_CAST(SdrView,pLs);
/*N*/           if (pAktView!=NULL) {
/*N*/               if (pPage!=NULL) {
/*N*/                   USHORT nPvAnz=pAktView->GetPageViewCount();
/*N*/                   USHORT nPvNum=0;
/*N*/                   while (nPvNum<nPvAnz) {
/*N*/                       SdrPageView* pPV=pAktView->GetPageViewPvNum(nPvNum);
/*N*/                       if (ImpCheckPageView(pPV)) {
/*N*/                           return pAktView;
/*N*/                       }
/*N*/                       nPvNum++;
/*N*/                   }
/*N*/               } else {
/*N*/                   return pAktView;
/*N*/               }
/*N*/           }
/*N*/           nListenerNum++;
/*N*/       }
/*N*/   }
/*N*/   pAktView=NULL;
/*N*/   return pAktView;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 SdrPageView* SdrViewIter::ImpFindPageView()
//STRIP001 {
//STRIP001  SdrView* pRet=NULL;
//STRIP001  if (pModel!=NULL) {
//STRIP001      while (pAktView!=NULL) {
//STRIP001          USHORT nPvAnz=pAktView->GetPageViewCount();
//STRIP001          while (nPageViewNum<nPvAnz) {
//STRIP001              SdrPageView* pPV=pAktView->GetPageViewPvNum(nPageViewNum);
//STRIP001              if (pPage!=NULL) {
//STRIP001                  if (ImpCheckPageView(pPV)) {
//STRIP001                      return pPV;
//STRIP001                  }
//STRIP001              } else {
//STRIP001                  return pPV;
//STRIP001              }
//STRIP001              nPageViewNum++;
//STRIP001          }
//STRIP001          nListenerNum++;
//STRIP001          ImpFindView();
//STRIP001      }
//STRIP001  }
//STRIP001  return NULL;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 OutputDevice* SdrViewIter::ImpFindOutDev()
//STRIP001 {
//STRIP001  while (pAktView!=NULL) {
//STRIP001      USHORT nOutDevAnz=pAktView->GetWinCount();
//STRIP001      if (nOutDevNum<nOutDevAnz) {
//STRIP001          return pAktView->GetWin(nOutDevNum);
//STRIP001      }
//STRIP001      nListenerNum++;
//STRIP001      ImpFindView();
//STRIP001  }
//STRIP001  return NULL;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 Window* SdrViewIter::ImpFindWindow()
//STRIP001 {
//STRIP001  while (pAktView!=NULL) {
//STRIP001      USHORT nOutDevAnz=pAktView->GetWinCount();
//STRIP001      while (nOutDevNum<nOutDevAnz) {
//STRIP001          OutputDevice* pOutDev=pAktView->GetWin(nOutDevNum);
//STRIP001          if (pOutDev->GetOutDevType()==OUTDEV_WINDOW) {
//STRIP001              return (Window*)pOutDev;
//STRIP001          }
//STRIP001          nOutDevNum++;
//STRIP001      }
//STRIP001      nListenerNum++;
//STRIP001      ImpFindView();
//STRIP001  }
//STRIP001  return NULL;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrView* SdrViewIter::FirstView()
/*N*/ {
/*N*/   ImpInitVars();
/*N*/   return ImpFindView();
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrView* SdrViewIter::NextView()
/*N*/ {
/*N*/   nListenerNum++;
/*N*/   return ImpFindView();
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 SdrPageView* SdrViewIter::FirstPageView()
//STRIP001 {
//STRIP001  ImpInitVars();
//STRIP001  ImpFindView();
//STRIP001  return ImpFindPageView();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 SdrPageView* SdrViewIter::NextPageView()
//STRIP001 {
//STRIP001  nPageViewNum++;
//STRIP001  return ImpFindPageView();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 OutputDevice* SdrViewIter::FirstOutDev()
//STRIP001 {
//STRIP001  ImpInitVars();
//STRIP001  ImpFindView();
//STRIP001  return ImpFindOutDev();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 OutputDevice* SdrViewIter::NextOutDev()
//STRIP001 {
//STRIP001  nOutDevNum++;
//STRIP001  return ImpFindOutDev();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 Window* SdrViewIter::FirstWindow()
//STRIP001 {
//STRIP001  ImpInitVars();
//STRIP001  ImpFindView();
//STRIP001  return ImpFindWindow();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 Window* SdrViewIter::NextWindow()
//STRIP001 {
//STRIP001  nOutDevNum++;
//STRIP001  return ImpFindWindow();
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

