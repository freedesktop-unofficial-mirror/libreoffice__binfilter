/*************************************************************************
 *
 *  $RCSfile: svx_svdedtv2.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 16:20:33 $
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

#include "svdedtv.hxx"
// auto strip #include "outliner.hxx"
// auto strip #include "svdundo.hxx"
// auto strip #include "svdogrp.hxx"   // fuer's Gruppieren
// auto strip #include "svdovirt.hxx"  // fuer VirtualObject-Bundling (Writer)
// auto strip #include "svdopath.hxx"  // fuer CombineObjects
// auto strip #include "svdpage.hxx"
// auto strip #include "svdpagv.hxx"
// auto strip #include "svditer.hxx"
// auto strip #include "svdograf.hxx"  // fuer Possibilities
// auto strip #include "svdoole2.hxx"  // und Mtf-Import
#include "svdstr.hrc"   // Namen aus der Resource
// auto strip #include "svdglob.hxx"  // StringCache
// auto strip #include "svdfmtf.hxx"
// auto strip #include "svdetc.hxx"

// auto strip #ifndef _BASEDLGS_HXX
// auto strip #include <bf_sfx2/basedlgs.hxx>
// auto strip #endif

// auto strip #include "dstribut.hxx"

// auto strip #ifndef _SV_MSGBOX_HXX //autogen
// auto strip #include <vcl/msgbox.hxx>
// auto strip #endif

// auto strip #ifndef _OUTLOBJ_HXX //autogen
// auto strip #include <outlobj.hxx>
// auto strip #endif

// auto strip #ifndef _EEITEM_HXX
// auto strip #include "eeitem.hxx"
// auto strip #endif

// auto strip #ifndef _POLY3D_HXX
// auto strip #include "poly3d.hxx"
// auto strip #endif
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@@@@ @@@@@  @@ @@@@@@  @@ @@ @@ @@@@@ @@   @@
//  @@    @@  @@ @@   @@    @@ @@ @@ @@    @@   @@
//  @@    @@  @@ @@   @@    @@ @@ @@ @@    @@ @ @@
//  @@@@  @@  @@ @@   @@    @@@@@ @@ @@@@  @@@@@@@
//  @@    @@  @@ @@   @@     @@@  @@ @@    @@@@@@@
//  @@    @@  @@ @@   @@     @@@  @@ @@    @@@ @@@
//  @@@@@ @@@@@  @@   @@      @   @@ @@@@@ @@   @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrEditView::ImpBundleVirtObjOfMarkList()
//STRIP001 {
//STRIP001   // ... fehlende Implementation
//STRIP001 }

//STRIP001 SdrObject* SdrEditView::GetMaxToTopObj(SdrObject* pObj) const
//STRIP001 {
//STRIP001  return NULL;
//STRIP001 }

//STRIP001 SdrObject* SdrEditView::GetMaxToBtmObj(SdrObject* pObj) const
//STRIP001 {
//STRIP001  return NULL;
//STRIP001 }

//STRIP001 void SdrEditView::ObjOrderChanged(SdrObject* pObj, ULONG nOldPos, ULONG nNewPos)
//STRIP001 {
//STRIP001 }

//STRIP001 void SdrEditView::MovMarkedToTop()
//STRIP001 {
//STRIP001  ULONG nAnz=aMark.GetMarkCount();
//STRIP001  if (nAnz!=0) {
//STRIP001      BegUndo(ImpGetResStr(STR_EditMovToTop),aMark.GetMarkDescription(),SDRREPFUNC_OBJ_MOVTOTOP);
//STRIP001      aMark.ForceSort();
//STRIP001      ULONG nm;
//STRIP001      for (nm=0; nm<nAnz; nm++) { // Ordnums muessen alle stimmen!
//STRIP001          aMark.GetMark(nm)->GetObj()->GetOrdNum();
//STRIP001      }
//STRIP001      BOOL bNeedBundle=FALSE;
//STRIP001      BOOL bChg=FALSE;
//STRIP001      SdrObjList* pOL0=NULL;
//STRIP001      ULONG nNewPos=0;
//STRIP001      for (nm=nAnz; nm>0;) {
//STRIP001          nm--;
//STRIP001          SdrMark* pM=aMark.GetMark(nm);
//STRIP001          SdrObject* pObj=pM->GetObj();
//STRIP001          SdrObjList* pOL=pObj->GetObjList();
//STRIP001          if (pOL!=pOL0) {
//STRIP001              nNewPos=ULONG(pOL->GetObjCount()-1);
//STRIP001              pOL0=pOL;
//STRIP001          }
//STRIP001          ULONG nNowPos=pObj->GetOrdNumDirect();
//STRIP001          const Rectangle& rBR=pObj->GetBoundRect();
//STRIP001          ULONG nCmpPos=nNowPos+1;
//STRIP001          SdrObject* pMaxObj=GetMaxToTopObj(pObj);
//STRIP001          if (pMaxObj!=NULL) {
//STRIP001              ULONG nMaxPos=pMaxObj->GetOrdNum();
//STRIP001              if (nMaxPos!=0) nMaxPos--;
//STRIP001              if (nNewPos>nMaxPos) nNewPos=nMaxPos; // diesen nicht ueberholen.
//STRIP001              if (nNewPos<nNowPos) nNewPos=nNowPos; // aber dabei auch nicht in die falsche Richtung schieben
//STRIP001          }
//STRIP001          BOOL bEnd=FALSE;
//STRIP001          while (nCmpPos<nNewPos && !bEnd) {
//STRIP001              SdrObject* pCmpObj=pOL->GetObj(nCmpPos);
//STRIP001              if (pCmpObj==NULL) {
//STRIP001                  DBG_ERROR("MovMarkedToTop(): Vergleichsobjekt nicht gefunden");
//STRIP001                  bEnd=TRUE;
//STRIP001              } else if (pCmpObj==pMaxObj) {
//STRIP001                  nNewPos=nCmpPos;
//STRIP001                  nNewPos--;
//STRIP001                  bEnd=TRUE;
//STRIP001              } else if (rBR.IsOver(pCmpObj->GetBoundRect())) {
//STRIP001                  nNewPos=nCmpPos;
//STRIP001                  bEnd=TRUE;
//STRIP001              } else nCmpPos++;
//STRIP001          }
//STRIP001          if (nNowPos!=nNewPos) {
//STRIP001              if (bBundleVirtObj) {
//STRIP001                  SdrVirtObj* pV0=PTR_CAST(SdrVirtObj,pObj);
//STRIP001                  if (pV0!=NULL) bNeedBundle=TRUE;
//STRIP001                  do { // nicht zwischen virtuelle Objekte draengeln
//STRIP001                      SdrObject* pV1Tmp=pOL->GetObj(nNewPos);
//STRIP001                      SdrObject* pV2Tmp=pOL->GetObj(nNewPos+1);
//STRIP001                      SdrVirtObj* pV1=PTR_CAST(SdrVirtObj,pV1Tmp);
//STRIP001                      SdrVirtObj* pV2=PTR_CAST(SdrVirtObj,pV2Tmp);
//STRIP001                      // Zwischen VirtObj mit gleichem Master wie ich darf ich schon
//STRIP001                      if (pV0!=NULL && pV1!=NULL && &pV0->GetReferencedObj()==&pV1->GetReferencedObj()) break;
//STRIP001                      // Zwischen andere nicht
//STRIP001                      if (pV1==NULL || pV2==NULL || &pV1->GetReferencedObj()!=&pV2->GetReferencedObj()) break;
//STRIP001                      nNewPos++;
//STRIP001                  } while (TRUE);
//STRIP001              }
//STRIP001              bChg=TRUE;
//STRIP001              pOL->SetObjectOrdNum(nNowPos,nNewPos);
//STRIP001              AddUndo(new SdrUndoObjOrdNum(*pObj,nNowPos,nNewPos));
//STRIP001              ObjOrderChanged(pObj,nNowPos,nNewPos);
//STRIP001          }
//STRIP001          nNewPos--;
//STRIP001      }
//STRIP001      if (bNeedBundle) ImpBundleVirtObjOfMarkList();
//STRIP001      EndUndo();
//STRIP001      if (bChg) MarkListHasChanged();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrEditView::MovMarkedToBtm()
//STRIP001 {
//STRIP001  ULONG nAnz=aMark.GetMarkCount();
//STRIP001  if (nAnz!=0) {
//STRIP001      BegUndo(ImpGetResStr(STR_EditMovToBtm),aMark.GetMarkDescription(),SDRREPFUNC_OBJ_MOVTOBTM);
//STRIP001      aMark.ForceSort();
//STRIP001      ULONG nm;
//STRIP001      for (nm=0; nm<nAnz; nm++) { // Ordnums muessen alle stimmen!
//STRIP001          aMark.GetMark(nm)->GetObj()->GetOrdNum();
//STRIP001      }
//STRIP001      BOOL bNeedBundle=FALSE;
//STRIP001      BOOL bChg=FALSE;
//STRIP001      SdrObjList* pOL0=NULL;
//STRIP001      ULONG nNewPos=0;
//STRIP001      for (nm=0; nm<nAnz; nm++) {
//STRIP001          SdrMark* pM=aMark.GetMark(nm);
//STRIP001          SdrObject* pObj=pM->GetObj();
//STRIP001          SdrObjList* pOL=pObj->GetObjList();
//STRIP001          if (pOL!=pOL0) {
//STRIP001              nNewPos=0;
//STRIP001              pOL0=pOL;
//STRIP001          }
//STRIP001          ULONG nNowPos=pObj->GetOrdNumDirect();
//STRIP001          const Rectangle& rBR=pObj->GetBoundRect();
//STRIP001          ULONG nCmpPos=nNowPos; if (nCmpPos>0) nCmpPos--;
//STRIP001          SdrObject* pMaxObj=GetMaxToBtmObj(pObj);
//STRIP001          if (pMaxObj!=NULL) {
//STRIP001              ULONG nMinPos=pMaxObj->GetOrdNum()+1;
//STRIP001              if (nNewPos<nMinPos) nNewPos=nMinPos; // diesen nicht ueberholen.
//STRIP001              if (nNewPos>nNowPos) nNewPos=nNowPos; // aber dabei auch nicht in die falsche Richtung schieben
//STRIP001          }
//STRIP001          BOOL bEnd=FALSE;
//STRIP001          // nNewPos ist an dieser Stelle noch die maximale Position,
//STRIP001          // an der das Obj hinruecken darf, ohne seinen Vorgaenger
//STRIP001          // (Mehrfachselektion) zu ueberholen.
//STRIP001          while (nCmpPos>nNewPos && !bEnd) {
//STRIP001              SdrObject* pCmpObj=pOL->GetObj(nCmpPos);
//STRIP001              if (pCmpObj==NULL) {
//STRIP001                  DBG_ERROR("MovMarkedToBtm(): Vergleichsobjekt nicht gefunden");
//STRIP001                  bEnd=TRUE;
//STRIP001              } else if (pCmpObj==pMaxObj) {
//STRIP001                  nNewPos=nCmpPos;
//STRIP001                  nNewPos++;
//STRIP001                  bEnd=TRUE;
//STRIP001              } else if (rBR.IsOver(pCmpObj->GetBoundRect())) {
//STRIP001                  nNewPos=nCmpPos;
//STRIP001                  bEnd=TRUE;
//STRIP001              } else nCmpPos--;
//STRIP001          }
//STRIP001          if (nNowPos!=nNewPos) {
//STRIP001              if (bBundleVirtObj) {
//STRIP001                  SdrVirtObj* pV0=PTR_CAST(SdrVirtObj,pObj);
//STRIP001                  if (pV0!=NULL) bNeedBundle=TRUE;
//STRIP001                  do { // nicht zwischen virtuelle Objekte draengeln
//STRIP001                      if (nNewPos==0) break;
//STRIP001                      SdrObject* pV1Tmp=pOL->GetObj(nNewPos);
//STRIP001                      SdrObject* pV2Tmp=pOL->GetObj(ULONG(nNewPos-1));
//STRIP001                      SdrVirtObj* pV1=PTR_CAST(SdrVirtObj,pV1Tmp);
//STRIP001                      SdrVirtObj* pV2=PTR_CAST(SdrVirtObj,pV2Tmp);
//STRIP001                      // Zwischen VirtObj mit gleichem Master wie ich darf ich schon
//STRIP001                      if (pV0!=NULL && pV1!=NULL && &pV0->GetReferencedObj()==&pV1->GetReferencedObj()) break;
//STRIP001                      // Zwischen andere nicht
//STRIP001                      if (pV1==NULL || pV2==NULL || &pV1->GetReferencedObj()!=&pV2->GetReferencedObj()) break;
//STRIP001                      nNewPos--;
//STRIP001                  } while (TRUE);
//STRIP001              }
//STRIP001              bChg=TRUE;
//STRIP001              pOL->SetObjectOrdNum(nNowPos,nNewPos);
//STRIP001              AddUndo(new SdrUndoObjOrdNum(*pObj,nNowPos,nNewPos));
//STRIP001              ObjOrderChanged(pObj,nNowPos,nNewPos);
//STRIP001          }
//STRIP001          nNewPos++;
//STRIP001      }
//STRIP001      if (bNeedBundle) ImpBundleVirtObjOfMarkList();
//STRIP001      EndUndo();
//STRIP001      if (bChg) MarkListHasChanged();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrEditView::PutMarkedToTop()
//STRIP001 {
//STRIP001  PutMarkedInFrontOfObj(NULL);
//STRIP001 }

//STRIP001 void SdrEditView::PutMarkedInFrontOfObj(const SdrObject* pRefObj)
//STRIP001 {
//STRIP001  ULONG nAnz=aMark.GetMarkCount();
//STRIP001  if (nAnz!=0) {
//STRIP001      BegUndo(ImpGetResStr(STR_EditPutToTop),aMark.GetMarkDescription(),SDRREPFUNC_OBJ_PUTTOTOP);
//STRIP001      aMark.ForceSort();
//STRIP001      if (pRefObj!=NULL) {
//STRIP001          // Damit "Vor das Objekt" auch funktioniert wenn die
//STRIP001          // markierten Objekte bereits vor dem Objekt stehen
//STRIP001          ULONG nRefMark=aMark.FindObject(pRefObj);
//STRIP001          SdrMark aRefMark;
//STRIP001          if (nRefMark!=CONTAINER_ENTRY_NOTFOUND) {
//STRIP001              aRefMark=*aMark.GetMark(nRefMark);
//STRIP001              aMark.DeleteMark(nRefMark);
//STRIP001          }
//STRIP001          PutMarkedToBtm();
//STRIP001          if (nRefMark!=CONTAINER_ENTRY_NOTFOUND) {
//STRIP001              aMark.InsertEntry(aRefMark);
//STRIP001              aMark.ForceSort();
//STRIP001          }
//STRIP001      }
//STRIP001      ULONG nm;
//STRIP001      for (nm=0; nm<nAnz; nm++) { // Ordnums muessen alle stimmen!
//STRIP001          aMark.GetMark(nm)->GetObj()->GetOrdNum();
//STRIP001      }
//STRIP001      BOOL bNeedBundle=FALSE;
//STRIP001      BOOL bChg=FALSE;
//STRIP001      SdrObjList* pOL0=NULL;
//STRIP001      ULONG nNewPos=0;
//STRIP001      for (nm=nAnz; nm>0;) {
//STRIP001          nm--;
//STRIP001          SdrMark* pM=aMark.GetMark(nm);
//STRIP001          SdrObject* pObj=pM->GetObj();
//STRIP001          if (pObj!=pRefObj) {
//STRIP001              SdrObjList* pOL=pObj->GetObjList();
//STRIP001              if (pOL!=pOL0) {
//STRIP001                  nNewPos=ULONG(pOL->GetObjCount()-1);
//STRIP001                  pOL0=pOL;
//STRIP001              }
//STRIP001              ULONG nNowPos=pObj->GetOrdNumDirect();
//STRIP001              SdrObject* pMaxObj=GetMaxToTopObj(pObj);
//STRIP001              if (pMaxObj!=NULL) {
//STRIP001                  ULONG nMaxOrd=pMaxObj->GetOrdNum(); // geht leider nicht anders
//STRIP001                  if (nMaxOrd>0) nMaxOrd--;
//STRIP001                  if (nNewPos>nMaxOrd) nNewPos=nMaxOrd; // nicht ueberholen.
//STRIP001                  if (nNewPos<nNowPos) nNewPos=nNowPos; // aber dabei auch nicht in die falsche Richtung schieben
//STRIP001              }
//STRIP001              if (pRefObj!=NULL) {
//STRIP001                  if (pRefObj->GetObjList()==pObj->GetObjList()) {
//STRIP001                      ULONG nMaxOrd=pRefObj->GetOrdNum(); // geht leider nicht anders
//STRIP001                      if (nNewPos>nMaxOrd) nNewPos=nMaxOrd; // nicht ueberholen.
//STRIP001                      if (nNewPos<nNowPos) nNewPos=nNowPos; // aber dabei auch nicht in die falsche Richtung schieben
//STRIP001                  } else {
//STRIP001                      nNewPos=nNowPos; // andere PageView, also nicht veraendern
//STRIP001                  }
//STRIP001              }
//STRIP001              if (nNowPos!=nNewPos) {
//STRIP001                  if (bBundleVirtObj && HAS_BASE(SdrVirtObj,pObj)) bNeedBundle=TRUE;
//STRIP001                  bChg=TRUE;
//STRIP001                  pOL->SetObjectOrdNum(nNowPos,nNewPos);
//STRIP001                  AddUndo(new SdrUndoObjOrdNum(*pObj,nNowPos,nNewPos));
//STRIP001                  ObjOrderChanged(pObj,nNowPos,nNewPos);
//STRIP001              }
//STRIP001              nNewPos--;
//STRIP001          } // if (pObj!=pRefObj)
//STRIP001      } // for-Schleife ueber alle Markierten Objekte
//STRIP001      if (bNeedBundle) ImpBundleVirtObjOfMarkList();
//STRIP001      EndUndo();
//STRIP001      if (bChg) MarkListHasChanged();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrEditView::PutMarkedToBtm()
//STRIP001 {
//STRIP001  PutMarkedBehindObj(NULL);
//STRIP001 }

//STRIP001 void SdrEditView::PutMarkedBehindObj(const SdrObject* pRefObj)
//STRIP001 {
//STRIP001  ULONG nAnz=aMark.GetMarkCount();
//STRIP001  if (nAnz!=0) {
//STRIP001      BegUndo(ImpGetResStr(STR_EditPutToBtm),aMark.GetMarkDescription(),SDRREPFUNC_OBJ_PUTTOBTM);
//STRIP001      aMark.ForceSort();
//STRIP001      if (pRefObj!=NULL) {
//STRIP001          // Damit "Hinter das Objekt" auch funktioniert wenn die
//STRIP001          // markierten Objekte bereits hinter dem Objekt stehen
//STRIP001          ULONG nRefMark=aMark.FindObject(pRefObj);
//STRIP001          SdrMark aRefMark;
//STRIP001          if (nRefMark!=CONTAINER_ENTRY_NOTFOUND) {
//STRIP001              aRefMark=*aMark.GetMark(nRefMark);
//STRIP001              aMark.DeleteMark(nRefMark);
//STRIP001          }
//STRIP001          PutMarkedToTop();
//STRIP001          if (nRefMark!=CONTAINER_ENTRY_NOTFOUND) {
//STRIP001              aMark.InsertEntry(aRefMark);
//STRIP001              aMark.ForceSort();
//STRIP001          }
//STRIP001      }
//STRIP001      ULONG nm;
//STRIP001      for (nm=0; nm<nAnz; nm++) { // Ordnums muessen alle stimmen!
//STRIP001          aMark.GetMark(nm)->GetObj()->GetOrdNum();
//STRIP001      }
//STRIP001      BOOL bNeedBundle=FALSE;
//STRIP001      BOOL bChg=FALSE;
//STRIP001      SdrObjList* pOL0=NULL;
//STRIP001      ULONG nNewPos=0;
//STRIP001      for (nm=0; nm<nAnz; nm++) {
//STRIP001          SdrMark* pM=aMark.GetMark(nm);
//STRIP001          SdrObject* pObj=pM->GetObj();
//STRIP001          if (pObj!=pRefObj) {
//STRIP001              SdrObjList* pOL=pObj->GetObjList();
//STRIP001              if (pOL!=pOL0) {
//STRIP001                  nNewPos=0;
//STRIP001                  pOL0=pOL;
//STRIP001              }
//STRIP001              ULONG nNowPos=pObj->GetOrdNumDirect();
//STRIP001              SdrObject* pMinObj=GetMaxToBtmObj(pObj);
//STRIP001              if (pMinObj!=NULL) {
//STRIP001                  ULONG nMinOrd=pMinObj->GetOrdNum()+1; // geht leider nicht anders
//STRIP001                  if (nNewPos<nMinOrd) nNewPos=nMinOrd; // nicht ueberholen.
//STRIP001                  if (nNewPos>nNowPos) nNewPos=nNowPos; // aber dabei auch nicht in die falsche Richtung schieben
//STRIP001              }
//STRIP001              if (pRefObj!=NULL) {
//STRIP001                  if (pRefObj->GetObjList()==pObj->GetObjList()) {
//STRIP001                      ULONG nMinOrd=pRefObj->GetOrdNum(); // geht leider nicht anders
//STRIP001                      if (nNewPos<nMinOrd) nNewPos=nMinOrd; // nicht ueberholen.
//STRIP001                      if (nNewPos>nNowPos) nNewPos=nNowPos; // aber dabei auch nicht in die falsche Richtung schieben
//STRIP001                  } else {
//STRIP001                      nNewPos=nNowPos; // andere PageView, also nicht veraendern
//STRIP001                  }
//STRIP001              }
//STRIP001              if (nNowPos!=nNewPos) {
//STRIP001                  if (bBundleVirtObj && !bNeedBundle && HAS_BASE(SdrVirtObj,pObj)) bNeedBundle=TRUE;
//STRIP001                  bChg=TRUE;
//STRIP001                  pOL->SetObjectOrdNum(nNowPos,nNewPos);
//STRIP001                  AddUndo(new SdrUndoObjOrdNum(*pObj,nNowPos,nNewPos));
//STRIP001                  ObjOrderChanged(pObj,nNowPos,nNewPos);
//STRIP001              }
//STRIP001              nNewPos++;
//STRIP001          } // if (pObj!=pRefObj)
//STRIP001      } // for-Schleife ueber alle markierten Objekte
//STRIP001      if (bNeedBundle) ImpBundleVirtObjOfMarkList();
//STRIP001      EndUndo();
//STRIP001      if (bChg) MarkListHasChanged();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrEditView::ReverseOrderOfMarked()
//STRIP001 {
//STRIP001  aMark.ForceSort();
//STRIP001  ULONG nMarkAnz=aMark.GetMarkCount();
//STRIP001  if (nMarkAnz>0) {
//STRIP001      BOOL bNeedBundle=FALSE;
//STRIP001      BOOL bChg=FALSE;
//STRIP001      BegUndo(ImpGetResStr(STR_EditRevOrder),aMark.GetMarkDescription(),SDRREPFUNC_OBJ_REVORDER);
//STRIP001      ULONG a=0;
//STRIP001      do {
//STRIP001          // Markierung ueber mehrere PageViews berueksichtigen
//STRIP001          ULONG b=a+1;
//STRIP001          while (b<nMarkAnz && aMark.GetMark(b)->GetPageView()==aMark.GetMark(a)->GetPageView()) b++;
//STRIP001          b--;
//STRIP001          SdrObjList* pOL=aMark.GetMark(a)->GetPageView()->GetObjList();
//STRIP001          ULONG c=b;
//STRIP001          if (a<c) { // Sicherstellen, dass die OrdNums nicht Dirty sind
//STRIP001              aMark.GetMark(a)->GetObj()->GetOrdNum();
//STRIP001          }
//STRIP001          while (a<c) {
//STRIP001              SdrObject* pObj1=aMark.GetMark(a)->GetObj();
//STRIP001              SdrObject* pObj2=aMark.GetMark(c)->GetObj();
//STRIP001              ULONG nOrd1=pObj1->GetOrdNumDirect();
//STRIP001              ULONG nOrd2=pObj2->GetOrdNumDirect();
//STRIP001              AddUndo(new SdrUndoObjOrdNum(*pObj1,nOrd1,nOrd2));
//STRIP001              AddUndo(new SdrUndoObjOrdNum(*pObj2,nOrd2-1,nOrd1));
//STRIP001              pOL->SetObjectOrdNum(nOrd1,nOrd2);
//STRIP001              // Obj 2 ist um eine Position nach vorn gerutscht, deshalb nun nOrd2-1
//STRIP001              pOL->SetObjectOrdNum(nOrd2-1,nOrd1);
//STRIP001              // Verwendung von Replace statt SetOrdNum wg. Performance (Neuberechnung der Ordnums)
//STRIP001              a++; c--;
//STRIP001              bChg=TRUE;
//STRIP001              if (bBundleVirtObj && !bNeedBundle &&
//STRIP001                  (HAS_BASE(SdrVirtObj,pObj1) || HAS_BASE(SdrVirtObj,pObj2))) bNeedBundle=TRUE;
//STRIP001          }
//STRIP001          a=b+1;
//STRIP001      } while (a<nMarkAnz);
//STRIP001      if (bNeedBundle) ImpBundleVirtObjOfMarkList();
//STRIP001      EndUndo();
//STRIP001      if (bChg) MarkListHasChanged();
//STRIP001  }
//STRIP001 }

/*N*/ void SdrEditView::ImpCheckToTopBtmPossible()
/*N*/ {
/*N*/   ULONG nAnz=aMark.GetMarkCount();
/*N*/   if (nAnz==0) return;
/*?*/   if (nAnz==1) { DBG_BF_ASSERT(0, "STRIP"); //STRIP001 // Sonderbehandlung fuer Einzelmarkierung
//STRIP001 /*?*/        SdrObject* pObj=aMark.GetMark(0)->GetObj();
//STRIP001 /*?*/        SdrObjList* pOL=pObj->GetObjList();
//STRIP001 /*?*/        ULONG nMax=pOL->GetObjCount();
//STRIP001 /*?*/        ULONG nMin=0;
//STRIP001 /*?*/        ULONG nObjNum=pObj->GetOrdNum();
//STRIP001 /*?*/        SdrObject* pRestrict=GetMaxToTopObj(pObj);
//STRIP001 /*?*/        if (pRestrict!=NULL) {
//STRIP001 /*?*/            ULONG nRestrict=pRestrict->GetOrdNum();
//STRIP001 /*?*/            if (nRestrict<nMax) nMax=nRestrict;
//STRIP001 /*?*/        }
//STRIP001 /*?*/        pRestrict=GetMaxToBtmObj(pObj);
//STRIP001 /*?*/        if (pRestrict!=NULL) {
//STRIP001 /*?*/            ULONG nRestrict=pRestrict->GetOrdNum();
//STRIP001 /*?*/            if (nRestrict>nMin) nMin=nRestrict;
//STRIP001 /*?*/        }
//STRIP001 /*?*/        bToTopPossible=nObjNum<ULONG(nMax-1);
//STRIP001 /*?*/        bToBtmPossible=nObjNum>nMin;
/*N*/ } else {DBG_BF_ASSERT(0, "STRIP"); //STRIP001  // Mehrfachselektion
//STRIP001 /*?*/        ULONG nm=0;
//STRIP001 /*?*/        SdrObjList* pOL0=NULL;
//STRIP001 /*?*/        long nPos0=-1;
//STRIP001 /*?*/        while (!bToBtmPossible && nm<nAnz) { // 'nach hinten' checken
//STRIP001 /*?*/            SdrObject* pObj=aMark.GetMark(nm)->GetObj();
//STRIP001 /*?*/            SdrObjList* pOL=pObj->GetObjList();
//STRIP001 /*?*/            if (pOL!=pOL0) {
//STRIP001 /*?*/                nPos0=-1;
//STRIP001 /*?*/                pOL0=pOL;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            ULONG nPos=pObj->GetOrdNum();
//STRIP001 /*?*/            bToBtmPossible=nPos>ULONG(nPos0+1);
//STRIP001 /*?*/            nPos0=long(nPos);
//STRIP001 /*?*/            nm++;
//STRIP001 /*?*/        }
//STRIP001 /*?*/        nm=nAnz;
//STRIP001 /*?*/        pOL0=NULL;
//STRIP001 /*?*/        nPos0=0x7FFFFFFF;
//STRIP001 /*?*/        while (!bToTopPossible && nm>0) { // 'nach vorn' checken
//STRIP001 /*?*/            nm--;
//STRIP001 /*?*/            SdrObject* pObj=aMark.GetMark(nm)->GetObj();
//STRIP001 /*?*/            SdrObjList* pOL=pObj->GetObjList();
//STRIP001 /*?*/            if (pOL!=pOL0) {
//STRIP001 /*?*/                nPos0=pOL->GetObjCount();
//STRIP001 /*?*/                pOL0=pOL;
//STRIP001 /*?*/            }
//STRIP001 /*?*/            ULONG nPos=pObj->GetOrdNum();
//STRIP001 /*?*/            bToTopPossible=nPos+1<ULONG(nPos0);
//STRIP001 /*?*/            nPos0=nPos;
//STRIP001 /*?*/        }
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//   @@@@    @@@@   @@   @@  @@@@@   @@  @@  @@  @@@@@
//  @@  @@  @@  @@  @@@ @@@  @@  @@  @@  @@@ @@  @@
//  @@      @@  @@  @@@@@@@  @@  @@  @@  @@@@@@  @@
//  @@      @@  @@  @@@@@@@  @@@@@   @@  @@@@@@  @@@@
//  @@      @@  @@  @@ @ @@  @@  @@  @@  @@ @@@  @@
//  @@  @@  @@  @@  @@   @@  @@  @@  @@  @@  @@  @@
//   @@@@    @@@@   @@   @@  @@@@@   @@  @@  @@  @@@@@
//
////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrEditView::ImpCopyAttributes(const SdrObject* pSource, SdrObject* pDest) const
//STRIP001 {
//STRIP001  if (pSource!=NULL) {
//STRIP001      SdrObjList* pOL=pSource->GetSubList();
//STRIP001      if (pOL!=NULL && !pSource->Is3DObj()) { // erstes Nichtgruppenobjekt aus der Gruppe holen
//STRIP001          SdrObjListIter aIter(*pOL,IM_DEEPNOGROUPS);
//STRIP001          pSource=aIter.Next();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if(pSource && pDest)
//STRIP001  {
//STRIP001      SfxItemSet aSet(pMod->GetItemPool(),
//STRIP001          SDRATTR_START,              SDRATTR_NOTPERSIST_FIRST-1,
//STRIP001          SDRATTR_NOTPERSIST_LAST+1,  SDRATTR_END,
//STRIP001          EE_ITEMS_START,             EE_ITEMS_END,
//STRIP001          0, 0); // #52757#, #52762#
//STRIP001
//STRIP001      aSet.Put(pSource->GetItemSet());
//STRIP001
//STRIP001      pDest->ClearItem();
//STRIP001      pDest->SetItemSet(aSet);
//STRIP001
//STRIP001      pDest->NbcSetLayer(pSource->GetLayer());
//STRIP001      pDest->NbcSetStyleSheet(pSource->GetStyleSheet(),TRUE);
//STRIP001  }
//STRIP001 }

//STRIP001 BOOL SdrEditView::ImpCanConvertForCombine1(const SdrObject* pObj) const
//STRIP001 {
//STRIP001  // #69711 : new condition IsLine() to be able to combine simple Lines
//STRIP001  BOOL bIsLine = FALSE;
//STRIP001  const SdrPathObj* pPath=PTR_CAST(SdrPathObj,pObj);
//STRIP001  if (pPath!=NULL)
//STRIP001      bIsLine = pPath->IsLine();
//STRIP001
//STRIP001  SdrObjTransformInfoRec aInfo;
//STRIP001  pObj->TakeObjInfo(aInfo);
//STRIP001  return ( aInfo.bCanConvToPath || aInfo.bCanConvToPoly || bIsLine );
//STRIP001 }

//STRIP001 BOOL SdrEditView::ImpCanConvertForCombine(const SdrObject* pObj) const
//STRIP001 {
//STRIP001  SdrObjList* pOL=pObj->GetSubList();
//STRIP001  if (pOL!=NULL && !pObj->Is3DObj()) {
//STRIP001      SdrObjListIter aIter(*pOL,IM_DEEPNOGROUPS);
//STRIP001      while (aIter.IsMore()) {
//STRIP001          SdrObject* pObj1=aIter.Next();
//STRIP001          // Es muessen alle Member einer Gruppe konvertierbar sein
//STRIP001          if (!ImpCanConvertForCombine1(pObj1)) return FALSE;
//STRIP001      }
//STRIP001  } else {
//STRIP001      if (!ImpCanConvertForCombine1(pObj)) return FALSE;
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 XPolyPolygon SdrEditView::ImpGetXPolyPoly1(const SdrObject* pObj, BOOL bCombine) const
//STRIP001 {
//STRIP001  XPolyPolygon aRet;
//STRIP001  SdrPathObj* pPath=PTR_CAST(SdrPathObj,pObj);
//STRIP001  if (bCombine && pPath!=NULL && pObj->GetOutlinerParaObject()==NULL) {
//STRIP001      aRet=pPath->GetPathPoly();
//STRIP001  } else {
//STRIP001      SdrObject* pConvObj=pObj->ConvertToPolyObj(bCombine, FALSE);
//STRIP001      if (pConvObj!=NULL) {
//STRIP001          SdrObjList* pOL=pConvObj->GetSubList();
//STRIP001          if (pOL!=NULL) {
//STRIP001              SdrObjListIter aIter(*pOL,IM_DEEPNOGROUPS);
//STRIP001              while (aIter.IsMore() && !bCombineError) {
//STRIP001                  SdrObject* pObj1=aIter.Next();
//STRIP001                  pPath=PTR_CAST(SdrPathObj,pObj1);
//STRIP001                  if (pPath!=NULL) {
//STRIP001                      if ((ULONG)aRet.Count()+(ULONG)pPath->GetPathPoly().Count()<=0xFFFF) {
//STRIP001                          aRet.Insert(pPath->GetPathPoly());
//STRIP001                      } else {
//STRIP001                          ((SdrEditView*)this)->bCombineError=TRUE;
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001          } else {
//STRIP001              pPath=PTR_CAST(SdrPathObj,pConvObj);
//STRIP001              if (pPath!=NULL) {
//STRIP001                  aRet=pPath->GetPathPoly();
//STRIP001              }
//STRIP001          }
//STRIP001          delete pConvObj;
//STRIP001      }
//STRIP001  }
//STRIP001  return aRet;
//STRIP001 }

//STRIP001 XPolyPolygon SdrEditView::ImpGetXPolyPoly(const SdrObject* pObj, BOOL bCombine) const
//STRIP001 {
//STRIP001  XPolyPolygon aRet;
//STRIP001  SdrObjList* pOL=pObj->GetSubList();
//STRIP001  if (pOL!=NULL && !pObj->Is3DObj()) {
//STRIP001      SdrObjListIter aIter(*pOL,IM_DEEPNOGROUPS);
//STRIP001      while (aIter.IsMore() && !bCombineError) {
//STRIP001          SdrObject* pObj1=aIter.Next();
//STRIP001          XPolyPolygon aXPP(ImpGetXPolyPoly1(pObj1, bCombine));
//STRIP001          if ((ULONG)aRet.Count()+(ULONG)aXPP.Count()<=0xFFFF) {
//STRIP001              aRet.Insert(aXPP);
//STRIP001          } else {
//STRIP001              ((SdrEditView*)this)->bCombineError=TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  } else {
//STRIP001      aRet=ImpGetXPolyPoly1(pObj, bCombine);
//STRIP001  }
//STRIP001  return aRet;
//STRIP001 }

//STRIP001 void SdrEditView::ImpCombineToSinglePoly(XPolyPolygon& rXPP, long nJoinTol) const
//STRIP001 {
//STRIP001  USHORT nPolyCount=rXPP.Count();
//STRIP001  if (nPolyCount>=2) {
//STRIP001      XPolygon aXP(rXPP[0]);
//STRIP001      if (aXP.GetPointCount()!=0) {
//STRIP001          aXP.SetFlags(0,XPOLY_NORMAL);
//STRIP001          aXP.SetFlags(USHORT(aXP.GetPointCount()-1),XPOLY_NORMAL);
//STRIP001      }
//STRIP001      for (USHORT i=1; i<nPolyCount && !bCombineError; i++) {
//STRIP001          USHORT nDstPointCount=aXP.GetPointCount();
//STRIP001          const XPolygon rSrcPoly=rXPP[i];
//STRIP001          USHORT nSrcPointCount=rSrcPoly.GetPointCount();
//STRIP001          if ((ULONG)nSrcPointCount+(ULONG)nDstPointCount>XPOLY_MAXPOINTS) {
//STRIP001              ((SdrEditView*)this)->bCombineError=TRUE;
//STRIP001          } else {
//STRIP001              if (nDstPointCount==0 || nSrcPointCount==0) {
//STRIP001                  aXP.Insert(nDstPointCount,rSrcPoly);
//STRIP001              } else {
//STRIP001                  Point aDstPt0(aXP[0]);
//STRIP001                  Point aDstPt1(aXP[USHORT(nDstPointCount-1)]);
//STRIP001                  Point aSrcPt0(rSrcPoly[0]);
//STRIP001                  Point aSrcPt1(rSrcPoly[USHORT(nSrcPointCount-1)]);
//STRIP001                  long n00=Abs(aSrcPt0.X()-aDstPt0.X())+Abs(aSrcPt0.Y()-aDstPt0.Y());
//STRIP001                  long n10=Abs(aSrcPt1.X()-aDstPt0.X())+Abs(aSrcPt1.Y()-aDstPt0.Y());
//STRIP001                  long n01=Abs(aSrcPt0.X()-aDstPt1.X())+Abs(aSrcPt0.Y()-aDstPt1.Y());
//STRIP001                  long n11=Abs(aSrcPt1.X()-aDstPt1.X())+Abs(aSrcPt1.Y()-aDstPt1.Y());
//STRIP001                  BOOL bAppend=(n01<=n00 && n01<=n10) || (n11<=n00 && n11<=n10);
//STRIP001                  BOOL bRevers=bAppend ? n11<n01 : n00<n10;
//STRIP001                  USHORT nDstPos=bAppend ? nDstPointCount : 0;
//STRIP001                  BOOL b1st=TRUE;
//STRIP001                  if (bRevers) {
//STRIP001                      for (USHORT nSrcPos=nSrcPointCount; nSrcPos>0;) {
//STRIP001                          nSrcPos--;
//STRIP001                          BOOL bNoIns=FALSE;
//STRIP001                          if (b1st) bNoIns=(bAppend ? n11 : n00) <=nJoinTol;
//STRIP001                          if (!bNoIns) {
//STRIP001                              aXP.Insert(nDstPos,rSrcPoly[nSrcPos],rSrcPoly.GetFlags(nSrcPos));
//STRIP001                              if (bAppend) nDstPos++;
//STRIP001                          }
//STRIP001                          b1st=FALSE;
//STRIP001                      }
//STRIP001                  } else {
//STRIP001                      for (USHORT nSrcPos=0; nSrcPos<nSrcPointCount; nSrcPos++) {
//STRIP001                          BOOL bNoIns=FALSE;
//STRIP001                          if (b1st) bNoIns=(bAppend ? n01 : n10) <=nJoinTol;
//STRIP001                          if (!bNoIns) {
//STRIP001                              aXP.Insert(nDstPos,rSrcPoly[nSrcPos],rSrcPoly.GetFlags(nSrcPos));
//STRIP001                              if (bAppend) nDstPos++;
//STRIP001                          }
//STRIP001                          b1st=FALSE;
//STRIP001                      }
//STRIP001                  }
//STRIP001              }
//STRIP001              if (aXP.GetPointCount()!=0) {
//STRIP001                  aXP.SetFlags(0,XPOLY_NORMAL);
//STRIP001                  aXP.SetFlags(USHORT(aXP.GetPointCount()-1),XPOLY_NORMAL);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      if (!bCombineError) {
//STRIP001          rXPP.Clear();
//STRIP001          rXPP.Insert(aXP,0);
//STRIP001      }
//STRIP001  }
//STRIP001 }

// for distribution dialog function
//STRIP001 struct ImpDistributeEntry
//STRIP001 {
//STRIP001  SdrObject*                  mpObj;
//STRIP001  INT32                       mnPos;
//STRIP001  INT32                       mnLength;
//STRIP001 };

//STRIP001 DECLARE_LIST(ImpDistributeEntryList, ImpDistributeEntry*)//STRIP008 ;

//STRIP001 void SdrEditView::DistributeMarkedObjects()
//STRIP001 {
//STRIP001 #ifndef SVX_LIGHT
//STRIP001
//STRIP001  UINT32 nMark(aMark.GetMarkCount());
//STRIP001
//STRIP001  if(nMark > 2)
//STRIP001  {
//STRIP001      SfxItemSet aNewAttr(pMod->GetItemPool());
//STRIP001      SvxDistributeDialog* pDlg = new SvxDistributeDialog(NULL, aNewAttr);
//STRIP001      UINT16 nResult = pDlg->Execute();
//STRIP001
//STRIP001      if(nResult == RET_OK)
//STRIP001      {
//STRIP001          SvxDistributeHorizontal eHor = pDlg->GetDistributeHor();
//STRIP001          SvxDistributeVertical eVer = pDlg->GetDistributeVer();
//STRIP001          ImpDistributeEntryList aEntryList;
//STRIP001          UINT32 a, nInsPos, nFullLength;
//STRIP001
//STRIP001          BegUndo();
//STRIP001
//STRIP001          if(eHor != SvxDistributeHorizontalNone)
//STRIP001          {
//STRIP001              // build sorted entry list
//STRIP001              nFullLength = 0L;
//STRIP001
//STRIP001              for(a=0;a<nMark;a++)
//STRIP001              {
//STRIP001                  SdrMark* pMark = aMark.GetMark(a);
//STRIP001                  ImpDistributeEntry* pNew = new ImpDistributeEntry;
//STRIP001
//STRIP001                  pNew->mpObj = pMark->GetObj();
//STRIP001                  nInsPos = 0;
//STRIP001
//STRIP001                  switch(eHor)
//STRIP001                  {
//STRIP001                      case SvxDistributeHorizontalLeft:
//STRIP001                      {
//STRIP001                          pNew->mnPos = pNew->mpObj->GetSnapRect().Left();
//STRIP001                          break;
//STRIP001                      }
//STRIP001                      case SvxDistributeHorizontalCenter:
//STRIP001                      {
//STRIP001                          pNew->mnPos = (pNew->mpObj->GetSnapRect().Right() + pNew->mpObj->GetSnapRect().Left()) / 2;
//STRIP001                          break;
//STRIP001                      }
//STRIP001                      case SvxDistributeHorizontalDistance:
//STRIP001                      {
//STRIP001                          pNew->mnLength = pNew->mpObj->GetSnapRect().GetWidth() + 1;
//STRIP001                          nFullLength += pNew->mnLength;
//STRIP001                          pNew->mnPos = (pNew->mpObj->GetSnapRect().Right() + pNew->mpObj->GetSnapRect().Left()) / 2;
//STRIP001                          break;
//STRIP001                      }
//STRIP001                      case SvxDistributeHorizontalRight:
//STRIP001                      {
//STRIP001                          pNew->mnPos = pNew->mpObj->GetSnapRect().Right();
//STRIP001                          break;
//STRIP001                      }
//STRIP001                  }
//STRIP001
//STRIP001                  while(nInsPos < aEntryList.Count() && aEntryList.GetObject(nInsPos)->mnPos < pNew->mnPos)
//STRIP001                      nInsPos++;
//STRIP001
//STRIP001                  aEntryList.Insert(pNew, nInsPos);
//STRIP001              }
//STRIP001
//STRIP001              if(eHor == SvxDistributeHorizontalDistance)
//STRIP001              {
//STRIP001                  // calc room in-between
//STRIP001                  INT32 nWidth = GetAllMarkedBoundRect().GetWidth() + 1;
//STRIP001                  double fStepWidth = ((double)nWidth - (double)nFullLength) / (double)(aEntryList.Count() - 1);
//STRIP001                  double fStepStart = (double)aEntryList.GetObject(0)->mnPos;
//STRIP001                  fStepStart += fStepWidth + (double)((aEntryList.GetObject(0)->mnLength + aEntryList.GetObject(1)->mnLength) / 2);
//STRIP001
//STRIP001                  // move entries 1..n-1
//STRIP001                  for(a=1;a<aEntryList.Count()-1;a++)
//STRIP001                  {
//STRIP001                      ImpDistributeEntry* pCurr = aEntryList.GetObject(a);
//STRIP001                      ImpDistributeEntry* pNext = aEntryList.GetObject(a+1);
//STRIP001                      INT32 nDelta = (INT32)(fStepStart + 0.5) - pCurr->mnPos;
//STRIP001                      AddUndo(new SdrUndoGeoObj(*pCurr->mpObj));
//STRIP001                      pCurr->mpObj->Move(Size(nDelta, 0));
//STRIP001                      fStepStart += fStepWidth + (double)((pCurr->mnLength + pNext->mnLength) / 2);
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  // calc distances
//STRIP001                  INT32 nWidth = aEntryList.GetObject(aEntryList.Count() - 1)->mnPos - aEntryList.GetObject(0)->mnPos;
//STRIP001                  double fStepWidth = (double)nWidth / (double)(aEntryList.Count() - 1);
//STRIP001                  double fStepStart = (double)aEntryList.GetObject(0)->mnPos;
//STRIP001                  fStepStart += fStepWidth;
//STRIP001
//STRIP001                  // move entries 1..n-1
//STRIP001                  for(a=1;a<aEntryList.Count()-1;a++)
//STRIP001                  {
//STRIP001                      ImpDistributeEntry* pCurr = aEntryList.GetObject(a);
//STRIP001                      INT32 nDelta = (INT32)(fStepStart + 0.5) - pCurr->mnPos;
//STRIP001                      AddUndo(new SdrUndoGeoObj(*pCurr->mpObj));
//STRIP001                      pCurr->mpObj->Move(Size(nDelta, 0));
//STRIP001                      fStepStart += fStepWidth;
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              // clear list
//STRIP001              while(aEntryList.Count())
//STRIP001                  delete aEntryList.Remove((UINT32)0L);
//STRIP001          }
//STRIP001
//STRIP001          if(eVer != SvxDistributeVerticalNone)
//STRIP001          {
//STRIP001              // build sorted entry list
//STRIP001              nFullLength = 0L;
//STRIP001
//STRIP001              for(a=0;a<nMark;a++)
//STRIP001              {
//STRIP001                  SdrMark* pMark = aMark.GetMark(a);
//STRIP001                  ImpDistributeEntry* pNew = new ImpDistributeEntry;
//STRIP001
//STRIP001                  pNew->mpObj = pMark->GetObj();
//STRIP001                  nInsPos = 0;
//STRIP001
//STRIP001                  switch(eVer)
//STRIP001                  {
//STRIP001                      case SvxDistributeVerticalTop:
//STRIP001                      {
//STRIP001                          pNew->mnPos = pNew->mpObj->GetSnapRect().Top();
//STRIP001                          break;
//STRIP001                      }
//STRIP001                      case SvxDistributeVerticalCenter:
//STRIP001                      {
//STRIP001                          pNew->mnPos = (pNew->mpObj->GetSnapRect().Bottom() + pNew->mpObj->GetSnapRect().Top()) / 2;
//STRIP001                          break;
//STRIP001                      }
//STRIP001                      case SvxDistributeVerticalDistance:
//STRIP001                      {
//STRIP001                          pNew->mnLength = pNew->mpObj->GetSnapRect().GetHeight() + 1;
//STRIP001                          nFullLength += pNew->mnLength;
//STRIP001                          pNew->mnPos = (pNew->mpObj->GetSnapRect().Bottom() + pNew->mpObj->GetSnapRect().Top()) / 2;
//STRIP001                          break;
//STRIP001                      }
//STRIP001                      case SvxDistributeVerticalBottom:
//STRIP001                      {
//STRIP001                          pNew->mnPos = pNew->mpObj->GetSnapRect().Bottom();
//STRIP001                          break;
//STRIP001                      }
//STRIP001                  }
//STRIP001
//STRIP001                  while(nInsPos < aEntryList.Count() && aEntryList.GetObject(nInsPos)->mnPos < pNew->mnPos)
//STRIP001                      nInsPos++;
//STRIP001
//STRIP001                  aEntryList.Insert(pNew, nInsPos);
//STRIP001              }
//STRIP001
//STRIP001              if(eVer == SvxDistributeVerticalDistance)
//STRIP001              {
//STRIP001                  // calc room in-between
//STRIP001                  INT32 nHeight = GetAllMarkedBoundRect().GetHeight() + 1;
//STRIP001                  double fStepWidth = ((double)nHeight - (double)nFullLength) / (double)(aEntryList.Count() - 1);
//STRIP001                  double fStepStart = (double)aEntryList.GetObject(0)->mnPos;
//STRIP001                  fStepStart += fStepWidth + (double)((aEntryList.GetObject(0)->mnLength + aEntryList.GetObject(1)->mnLength) / 2);
//STRIP001
//STRIP001                  // move entries 1..n-1
//STRIP001                  for(a=1;a<aEntryList.Count()-1;a++)
//STRIP001                  {
//STRIP001                      ImpDistributeEntry* pCurr = aEntryList.GetObject(a);
//STRIP001                      ImpDistributeEntry* pNext = aEntryList.GetObject(a+1);
//STRIP001                      INT32 nDelta = (INT32)(fStepStart + 0.5) - pCurr->mnPos;
//STRIP001                      AddUndo(new SdrUndoGeoObj(*pCurr->mpObj));
//STRIP001                      pCurr->mpObj->Move(Size(0, nDelta));
//STRIP001                      fStepStart += fStepWidth + (double)((pCurr->mnLength + pNext->mnLength) / 2);
//STRIP001                  }
//STRIP001              }
//STRIP001              else
//STRIP001              {
//STRIP001                  // calc distances
//STRIP001                  INT32 nHeight = aEntryList.GetObject(aEntryList.Count() - 1)->mnPos - aEntryList.GetObject(0)->mnPos;
//STRIP001                  double fStepWidth = (double)nHeight / (double)(aEntryList.Count() - 1);
//STRIP001                  double fStepStart = (double)aEntryList.GetObject(0)->mnPos;
//STRIP001                  fStepStart += fStepWidth;
//STRIP001
//STRIP001                  // move entries 1..n-1
//STRIP001                  for(a=1;a<aEntryList.Count()-1;a++)
//STRIP001                  {
//STRIP001                      ImpDistributeEntry* pCurr = aEntryList.GetObject(a);
//STRIP001                      INT32 nDelta = (INT32)(fStepStart + 0.5) - pCurr->mnPos;
//STRIP001                      AddUndo(new SdrUndoGeoObj(*pCurr->mpObj));
//STRIP001                      pCurr->mpObj->Move(Size(0, nDelta));
//STRIP001                      fStepStart += fStepWidth;
//STRIP001                  }
//STRIP001              }
//STRIP001
//STRIP001              // clear list
//STRIP001              while(aEntryList.Count())
//STRIP001                  delete aEntryList.Remove((UINT32)0L);
//STRIP001          }
//STRIP001
//STRIP001          // UNDO-Comment and end of UNDO
//STRIP001          SetUndoComment(ImpGetResStr(STR_DistributeMarkedObjects));
//STRIP001          EndUndo();
//STRIP001      }
//STRIP001
//STRIP001      delete(pDlg);
//STRIP001  }
//STRIP001 #endif
//STRIP001 }

//STRIP001 void SdrEditView::MergeMarkedObjects(SdrMergeMode eMode)
//STRIP001 {
//STRIP001  SdrMarkList aRemove;
//STRIP001  aMark.ForceSort();
//STRIP001  BegUndo();
//STRIP001
//STRIP001  UINT32 nInsPos=0xFFFFFFFF;
//STRIP001  UINT32 nAnz=aMark.GetMarkCount();
//STRIP001  const SdrObject* pAttrObj = NULL;
//STRIP001  PolyPolygon3D aMergePolyPolygonA;
//STRIP001  PolyPolygon3D aMergePolyPolygonB;
//STRIP001  SdrObjList* pInsOL = NULL;
//STRIP001  SdrPageView* pInsPV = NULL;
//STRIP001  BOOL bFirstObjectComplete(FALSE);
//STRIP001
//STRIP001  // make sure selected objects are contour objects
//STRIP001  ConvertMarkedToPolyObj(TRUE);
//STRIP001
//STRIP001  for(UINT32 a=0;a<aMark.GetMarkCount();a++)
//STRIP001  {
//STRIP001      SdrMark* pM = aMark.GetMark(a);
//STRIP001      SdrObject* pObj = pM->GetObj();
//STRIP001
//STRIP001      if(ImpCanConvertForCombine(pObj))
//STRIP001      {
//STRIP001          if(!pAttrObj)
//STRIP001              pAttrObj = pObj;
//STRIP001
//STRIP001          nInsPos = pObj->GetOrdNum() + 1;
//STRIP001          pInsPV = pM->GetPageView();
//STRIP001          pInsOL = pObj->GetObjList();
//STRIP001
//STRIP001          // get the polygons; do NOT use ImpGetXPolyPoly here - it does fetch all
//STRIP001          // the polygons, but they are all put in one single XPolyPolygon so that
//STRIP001          // no SetDirections() on single objects can be made. This would lead to
//STRIP001          // wrong results.
//STRIP001          SdrObjList* pObjectList = pObj->GetSubList();
//STRIP001          Vector3D aCommonNormal(0.0, 0.0, 1.0);
//STRIP001
//STRIP001          if(pObjectList)
//STRIP001          {
//STRIP001              SdrObjListIter aIter(*pObjectList, IM_DEEPWITHGROUPS);
//STRIP001
//STRIP001              while(aIter.IsMore())
//STRIP001              {
//STRIP001                  SdrObject* pCandidate = aIter.Next();
//STRIP001                  SdrPathObj* pPathObj = PTR_CAST(SdrPathObj, pCandidate);
//STRIP001                  if(pPathObj)
//STRIP001                  {
//STRIP001                      PolyPolygon3D aTmpPoly3D(pPathObj->GetPathPoly());
//STRIP001                      aTmpPoly3D.SetDirections(aCommonNormal);
//STRIP001
//STRIP001                      if(!bFirstObjectComplete)
//STRIP001                          aMergePolyPolygonA.Insert(aTmpPoly3D);
//STRIP001                      else
//STRIP001                          aMergePolyPolygonB.Insert(aTmpPoly3D);
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          else
//STRIP001          {
//STRIP001              SdrPathObj* pPathObj = PTR_CAST(SdrPathObj, pObj);
//STRIP001              if(pPathObj)
//STRIP001              {
//STRIP001                  PolyPolygon3D aTmpPoly3D(pPathObj->GetPathPoly());
//STRIP001                  aTmpPoly3D.SetDirections(aCommonNormal);
//STRIP001
//STRIP001                  if(!bFirstObjectComplete)
//STRIP001                      aMergePolyPolygonA.Insert(aTmpPoly3D);
//STRIP001                  else
//STRIP001                      aMergePolyPolygonB.Insert(aTmpPoly3D);
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          // was there something added to the first poly?
//STRIP001          if(!bFirstObjectComplete && aMergePolyPolygonA.Count())
//STRIP001              bFirstObjectComplete = TRUE;
//STRIP001
//STRIP001          // move object to temporary delete list
//STRIP001          aRemove.InsertEntry(SdrMark(pObj, pM->GetPageView()));
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  switch(eMode)
//STRIP001  {
//STRIP001      case SDR_MERGE_MERGE:
//STRIP001      {
//STRIP001          // simple merge all contained parts (OR)
//STRIP001          aMergePolyPolygonA.Insert(aMergePolyPolygonB);
//STRIP001          aMergePolyPolygonA.Merge(FALSE);
//STRIP001
//STRIP001          break;
//STRIP001      }
//STRIP001      case SDR_MERGE_SUBSTRACT:
//STRIP001      {
//STRIP001          // take selected poly 2..n (is in Polygon B), merge them, flipdirections
//STRIP001          // and merge with poly 1
//STRIP001          aMergePolyPolygonA.Merge(FALSE);
//STRIP001          aMergePolyPolygonB.Merge(FALSE);
//STRIP001          aMergePolyPolygonB.FlipDirections();
//STRIP001          aMergePolyPolygonA.Insert(aMergePolyPolygonB);
//STRIP001          aMergePolyPolygonA.Merge(FALSE);
//STRIP001
//STRIP001          // #72995# one more call to resolve self intersections which
//STRIP001          // may have been built by substracting (see bug)
//STRIP001          aMergePolyPolygonA.Merge(FALSE);
//STRIP001
//STRIP001          break;
//STRIP001      }
//STRIP001      case SDR_MERGE_INTERSECT:
//STRIP001      {
//STRIP001          // cut poly 1 against polys 2..n (AND)
//STRIP001          aMergePolyPolygonA.Merge(FALSE);
//STRIP001          aMergePolyPolygonB.Merge(FALSE);
//STRIP001          aMergePolyPolygonA.Insert(aMergePolyPolygonB);
//STRIP001          aMergePolyPolygonA.Merge(FALSE, TRUE);
//STRIP001
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  XPolyPolygon aXPP = aMergePolyPolygonA.GetXPolyPolygon();
//STRIP001  SdrPathObj* pPath = new SdrPathObj(OBJ_PATHFILL, aXPP);
//STRIP001  ImpCopyAttributes(pAttrObj, pPath);
//STRIP001  SdrInsertReason aReason(SDRREASON_VIEWCALL, pAttrObj);
//STRIP001  pInsOL->InsertObject(pPath, nInsPos, &aReason);
//STRIP001  AddUndo(new SdrUndoNewObj(*pPath));
//STRIP001  MarkObj(pPath, pInsPV, FALSE, TRUE);
//STRIP001
//STRIP001  aRemove.ForceSort();
//STRIP001  switch(eMode)
//STRIP001  {
//STRIP001      case SDR_MERGE_MERGE:
//STRIP001      {
//STRIP001          SetUndoComment(
//STRIP001              ImpGetResStr(STR_EditMergeMergePoly),
//STRIP001              aRemove.GetMarkDescription());
//STRIP001          break;
//STRIP001      }
//STRIP001      case SDR_MERGE_SUBSTRACT:
//STRIP001      {
//STRIP001          SetUndoComment(
//STRIP001              ImpGetResStr(STR_EditMergeSubstractPoly),
//STRIP001              aRemove.GetMarkDescription());
//STRIP001          break;
//STRIP001      }
//STRIP001      case SDR_MERGE_INTERSECT:
//STRIP001      {
//STRIP001          SetUndoComment(
//STRIP001              ImpGetResStr(STR_EditMergeIntersectPoly),
//STRIP001              aRemove.GetMarkDescription());
//STRIP001          break;
//STRIP001      }
//STRIP001  }
//STRIP001  DeleteMarked(aRemove);
//STRIP001
//STRIP001  EndUndo();
//STRIP001 }

/*N*/ BOOL SdrEditView::CombineMarkedObjects(BOOL bNoPolyPoly)
/*N*/ {{DBG_BF_ASSERT(0, "STRIP"); } return false;//STRIP001
//STRIP001  // #105899# Start of Combine-Undo put to front, else ConvertMarkedToPolyObj would
//STRIP001  // create a 2nd Undo-action and Undo-Comment.
//STRIP001
//STRIP001  // Undo-String will be set later
//STRIP001  BegUndo(String(), String(),
//STRIP001      bNoPolyPoly ? SDRREPFUNC_OBJ_COMBINE_ONEPOLY : SDRREPFUNC_OBJ_COMBINE_POLYPOLY);
//STRIP001
//STRIP001  // #105899# First, guarantee that all objects are converted to polyobjects,
//STRIP001  // especially for SdrGrafObj with bitmap filling this is necessary to not
//STRIP001  // loose the bitmap filling.
//STRIP001
//STRIP001  // #i12392#
//STRIP001  // ConvertMarkedToPolyObj was too strong here, it will loose quality and
//STRIP001  // information when curve objects are combined. This can be replaced by
//STRIP001  // using ConvertMarkedToPathObj without changing the previous fix.
//STRIP001  ConvertMarkedToPathObj(sal_True);
//STRIP001
//STRIP001  // continue as before
//STRIP001  bCombineError = FALSE;
//STRIP001  XPolyPolygon aXPP;
//STRIP001  SdrObjList* pAktOL = NULL;
//STRIP001  // Temporaere Marklist
//STRIP001  SdrMarkList aRemoveMerker;
//STRIP001
//STRIP001  aMark.ForceSort();
//STRIP001  ULONG nInsPos=0xFFFFFFFF;
//STRIP001  SdrObjList* pInsOL=NULL;
//STRIP001  SdrPageView* pInsPV=NULL;
//STRIP001  ULONG nAktPointCount=0; // Gesamtpunkteanzahl aller Teilpolygone des PolyPolygons
//STRIP001  ULONG nm;
//STRIP001  ULONG nAnz=aMark.GetMarkCount();
//STRIP001  const SdrObject* pAttrObj=NULL;
//STRIP001  for (nm=nAnz; nm>0 && !bCombineError;) {
//STRIP001      nm--;
//STRIP001      SdrMark* pM=aMark.GetMark(nm);
//STRIP001      SdrObject* pObj=pM->GetObj();
//STRIP001      SdrObjList* pThisOL=pObj->GetObjList();
//STRIP001      if (pAktOL!=pThisOL) {
//STRIP001          pAktOL=pThisOL;
//STRIP001      }
//STRIP001      if (ImpCanConvertForCombine(pObj)) {
//STRIP001          pAttrObj=pObj; // Obj merken fuer Attribute kopieren
//STRIP001          XPolyPolygon aTmpXPP(ImpGetXPolyPoly(pObj, TRUE));
//STRIP001          ULONG nAktPolyCount=aXPP.Count();
//STRIP001          ULONG nTmpPolyCount=aTmpXPP.Count();
//STRIP001          ULONG nTmpPointCount=0;
//STRIP001          for (ULONG nTmpPolyNum=0; nTmpPolyNum<nTmpPolyCount; nTmpPolyNum++) {
//STRIP001              nTmpPointCount+=aTmpXPP[(USHORT)nTmpPolyNum].GetPointCount();
//STRIP001          }
//STRIP001          if (nAktPolyCount+nTmpPolyCount<=0xFFFF && nAktPointCount+nTmpPointCount<=XPOLY_MAXPOINTS) {
//STRIP001              aXPP.Insert(aTmpXPP,0);
//STRIP001              nAktPointCount+=nTmpPointCount;
//STRIP001          } else {
//STRIP001              bCombineError=TRUE;
//STRIP001          }
//STRIP001          if (pInsOL==NULL) {
//STRIP001              nInsPos=pObj->GetOrdNum()+1;
//STRIP001              pInsPV=pM->GetPageView();
//STRIP001              pInsOL=pObj->GetObjList();
//STRIP001          }
//STRIP001          aRemoveMerker.InsertEntry(SdrMark(pObj,pM->GetPageView()));
//STRIP001      }
//STRIP001  }
//STRIP001  long nJoinTol=10;
//STRIP001  if (bNoPolyPoly && !bCombineError) ImpCombineToSinglePoly(aXPP,nJoinTol);
//STRIP001  USHORT nPolyCount=aXPP.Count();
//STRIP001  if (nPolyCount!=0 && !bCombineError) {
//STRIP001      SdrObjKind eKind=OBJ_PATHFILL;
//STRIP001      if (nPolyCount>1) {
//STRIP001          // Polygone ggf. schliessen (Polylines,...)
//STRIP001          for (USHORT i=0; i<nPolyCount; i++) {
//STRIP001              const XPolygon& rXP=aXPP.GetObject(i);
//STRIP001              USHORT nPointCount=rXP.GetPointCount();
//STRIP001              USHORT nMaxPoint=USHORT(nPointCount-1);
//STRIP001              if (nPointCount>0 && rXP[0]!=rXP[nMaxPoint]) { // nicht geschlossen?
//STRIP001                  // XPolygon um einen Punkt erweitern (zum schliessen)
//STRIP001                  aXPP[i][nPointCount]=aXPP[i][0];
//STRIP001              }
//STRIP001          }
//STRIP001      } else { // auf Polyline Checken
//STRIP001          const XPolygon& rXP=aXPP.GetObject(0);
//STRIP001          USHORT nPointCount=rXP.GetPointCount();
//STRIP001          USHORT nMaxPoint=USHORT(nPointCount-1);
//STRIP001          if (nPointCount<=2) eKind=OBJ_PATHLINE;
//STRIP001          else {
//STRIP001              const Point& rPt0=rXP[0];
//STRIP001              const Point& rPt1=rXP[nMaxPoint];
//STRIP001              if (rPt0!=rPt1) { // nicht geschlossen?
//STRIP001                  long nDist=Abs(rPt0.X()-rPt1.X())+Abs(rPt0.Y()-rPt1.Y());
//STRIP001                  if (nDist<=nJoinTol) {
//STRIP001                      long x=(rPt0.X()+rPt1.X()+1)/2;
//STRIP001                      long y=(rPt0.Y()+rPt1.Y()+1)/2;
//STRIP001                      Point aMitte(x,y);
//STRIP001                      aXPP[0][0]=aMitte;
//STRIP001                      aXPP[0][nMaxPoint]=aMitte;
//STRIP001                  } else {
//STRIP001                      eKind=OBJ_PATHLINE;
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001
//STRIP001      SdrPathObj* pPath=new SdrPathObj(eKind,aXPP);
//STRIP001      // Attribute des untersten Objekts
//STRIP001      ImpCopyAttributes(pAttrObj,pPath);
//STRIP001
//STRIP001      // #100408# If LineStyle is XLINE_NONE force to XLINE_SOLID to make visible.
//STRIP001      const XLineStyle eLineStyle = ((const XLineStyleItem&)pPath->GetItem(XATTR_LINESTYLE)).GetValue();
//STRIP001      if(XLINE_NONE == eLineStyle)
//STRIP001      {
//STRIP001          pPath->SetItem(XLineStyleItem(XLINE_SOLID));
//STRIP001      }
//STRIP001
//STRIP001      SdrInsertReason aReason(SDRREASON_VIEWCALL,pAttrObj);
//STRIP001      pInsOL->InsertObject(pPath,nInsPos,&aReason);
//STRIP001      AddUndo(new SdrUndoNewObj(*pPath)); // Insert durch New ersetzt - Joe, 31-08-1995
//STRIP001      MarkObj(pPath,pInsPV,FALSE,TRUE);
//STRIP001  }
//STRIP001  if (!bCombineError) {
//STRIP001      // UndoComment aus den tatsaechlich verwendeten Objekten zusammenbauen
//STRIP001      aRemoveMerker.ForceSort(); // wichtig fuer Remove (s.u.)
//STRIP001      SetUndoComment(ImpGetResStr(bNoPolyPoly?STR_EditCombine_OnePoly:STR_EditCombine_PolyPoly),aRemoveMerker.GetMarkDescription());
//STRIP001      // die tatsaechlich verwendeten Objekten aus der Liste entfernen
//STRIP001      DeleteMarked(aRemoveMerker);
//STRIP001  }
//STRIP001  EndUndo();
//STRIP001  return !bCombineError;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@@@@   @@   @@@@   @@   @@   @@@@   @@  @@  @@@@@@  @@     @@@@@
//  @@  @@  @@  @@  @@  @@@ @@@  @@  @@  @@@ @@    @@    @@     @@
//  @@  @@  @@  @@      @@@@@@@  @@  @@  @@@@@@    @@    @@     @@
//  @@  @@  @@   @@@@   @@@@@@@  @@@@@@  @@@@@@    @@    @@     @@@@
//  @@  @@  @@      @@  @@ @ @@  @@  @@  @@ @@@    @@    @@     @@
//  @@  @@  @@  @@  @@  @@   @@  @@  @@  @@  @@    @@    @@     @@
//  @@@@@   @@   @@@@   @@   @@  @@  @@  @@  @@    @@    @@@@@  @@@@@
//
////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 BOOL SdrEditView::ImpCanDismantle(const XPolyPolygon& rXPP, BOOL bMakeLines) const
//STRIP001 {
//STRIP001  BOOL bCan=FALSE;
//STRIP001  USHORT nPolyAnz=rXPP.Count();
//STRIP001  // Dismantle macht erst Sinn ab 2 Polygone im PolyPolygon
//STRIP001  if (nPolyAnz>=2) bCan=TRUE;
//STRIP001  else if (bMakeLines && nPolyAnz==1) { // oder ab 2 Linien bzw. 2 Segmenten im Polygon
//STRIP001      const XPolygon& rXP=rXPP[0];
//STRIP001      USHORT nPointAnz=rXP.GetPointCount();
//STRIP001      if (nPointAnz>4) bCan=TRUE;
//STRIP001      else if (nPointAnz>2) { // sonst ist es nur eine Linie
//STRIP001          if (!rXP.IsControl(1)) bCan=TRUE; // sonst ist es nun ein Beziersegment
//STRIP001      }
//STRIP001  }
//STRIP001  return bCan;
//STRIP001 }

//STRIP001 BOOL SdrEditView::ImpCanDismantle(const SdrObject* pObj, BOOL bMakeLines) const
//STRIP001 {
//STRIP001  BOOL bOtherObjs=FALSE;    // TRUE=andere Objekte ausser PathObj's vorhanden
//STRIP001  BOOL bMin1PolyPoly=FALSE; // TRUE=mind. 1 PolyPolygon mit mehr als ein Polygon vorhanden
//STRIP001  SdrObjList* pOL=pObj->GetSubList();
//STRIP001  if (pOL!=NULL) {
//STRIP001      // Aha, Gruppenobjekt. Also alle Member ansehen.
//STRIP001      // Alle muessen PathObjs sein !
//STRIP001      SdrObjListIter aIter(*pOL,IM_DEEPNOGROUPS);
//STRIP001      while (aIter.IsMore() && !bOtherObjs) {
//STRIP001          const SdrObject* pObj1=aIter.Next();
//STRIP001          const SdrPathObj* pPath=PTR_CAST(SdrPathObj,pObj1);
//STRIP001          if (pPath!=NULL) {
//STRIP001              if (ImpCanDismantle(pPath->GetPathPoly(),bMakeLines)) bMin1PolyPoly=TRUE;
//STRIP001              SdrObjTransformInfoRec aInfo;
//STRIP001              pObj1->TakeObjInfo(aInfo);
//STRIP001              if (!aInfo.bCanConvToPath) bOtherObjs=TRUE; // Passiert z.B. im Falle Fontwork (Joe, 28-11-95)
//STRIP001          } else {
//STRIP001              bOtherObjs=TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001  } else {
//STRIP001      const SdrPathObj* pPath=PTR_CAST(SdrPathObj,pObj);
//STRIP001      if (pPath!=NULL) {
//STRIP001          if (ImpCanDismantle(pPath->GetPathPoly(),bMakeLines)) bMin1PolyPoly=TRUE;
//STRIP001          SdrObjTransformInfoRec aInfo;
//STRIP001          pObj->TakeObjInfo(aInfo);
//STRIP001          // #69711 : new condition IsLine() to be able to break simple Lines
//STRIP001          if (!(aInfo.bCanConvToPath || aInfo.bCanConvToPoly) && !pPath->IsLine() ) bOtherObjs=TRUE; // Passiert z.B. im Falle Fontwork (Joe, 28-11-95)
//STRIP001      } else {
//STRIP001          bOtherObjs=TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  return bMin1PolyPoly && !bOtherObjs;
//STRIP001 }

//STRIP001 void SdrEditView::ImpDismantleOneObject(const SdrObject* pObj, SdrObjList& rOL, ULONG& rPos, SdrPageView* pPV, BOOL bMakeLines)
//STRIP001 {
//STRIP001  const SdrPathObj* pSrcPath=PTR_CAST(SdrPathObj,pObj);
//STRIP001  if (pSrcPath!=NULL) {
//STRIP001      SdrObject* pLast=NULL; // // fuer die Zuweisung des OutlinerParaObject
//STRIP001      const XPolyPolygon& rXPP=pSrcPath->GetPathPoly();
//STRIP001      USHORT nPolyAnz=rXPP.Count();
//STRIP001      for (USHORT i=0; i<nPolyAnz; i++) {
//STRIP001          const XPolygon& rAktXP=rXPP.GetObject(i);
//STRIP001          const XPolygon* pXP=&rAktXP;
//STRIP001          XPolygon aTmpPoly;
//STRIP001          USHORT nPointAnz=rAktXP.GetPointCount();
//STRIP001          if (nPointAnz<2) bMakeLines=FALSE;
//STRIP001          for (USHORT nPoint=0; nPoint<nPointAnz; nPoint++) {
//STRIP001              SdrObjKind eKind=OBJ_PATHFILL;
//STRIP001              if (bMakeLines) {
//STRIP001                  eKind=OBJ_PLIN;
//STRIP001                  pXP=&aTmpPoly;
//STRIP001                  aTmpPoly.SetSize(2);
//STRIP001                  aTmpPoly[0]=rAktXP[nPoint];
//STRIP001                  aTmpPoly.SetFlags(0,XPOLY_NORMAL);
//STRIP001                  aTmpPoly[1]=rAktXP[nPoint+1];
//STRIP001                  aTmpPoly.SetFlags(1,rAktXP.GetFlags(nPoint+1));
//STRIP001                  if (aTmpPoly.IsControl(1) && nPoint+3<nPointAnz) { // Aha, Beziersegment
//STRIP001                      aTmpPoly[2]=rAktXP[nPoint+2];
//STRIP001                      aTmpPoly.SetFlags(2,rAktXP.GetFlags(nPoint+2));
//STRIP001                      aTmpPoly[3]=rAktXP[nPoint+3];
//STRIP001                      aTmpPoly.SetFlags(3,rAktXP.GetFlags(nPoint+3));
//STRIP001                      nPoint+=2;
//STRIP001                      eKind=OBJ_PATHLINE;
//STRIP001                  }
//STRIP001                  aTmpPoly.SetFlags(USHORT(aTmpPoly.GetPointCount()-1),XPOLY_NORMAL);
//STRIP001                  if (nPoint>=USHORT(nPointAnz-2)) nPoint=nPointAnz;
//STRIP001              } else {
//STRIP001                  nPoint=nPointAnz;
//STRIP001                  eKind=SdrObjKind(pSrcPath->GetObjIdentifier());
//STRIP001              }
//STRIP001              SdrPathObj* pPath=new SdrPathObj(eKind,XPolyPolygon(*pXP));
//STRIP001              ImpCopyAttributes(pSrcPath,pPath);
//STRIP001              pLast=pPath;
//STRIP001              SdrInsertReason aReason(SDRREASON_VIEWCALL,pSrcPath);
//STRIP001              rOL.InsertObject(pPath,rPos,&aReason);
//STRIP001              AddUndo(new SdrUndoNewObj(*pPath,TRUE)); // Insert durch New ersetzt - Joe, 31-08-1995
//STRIP001              MarkObj(pPath,pPV,FALSE,TRUE);
//STRIP001              rPos++;
//STRIP001          }
//STRIP001      }
//STRIP001      if (pLast!=NULL && pSrcPath->GetOutlinerParaObject()!=NULL)
//STRIP001          pLast->SetOutlinerParaObject(pSrcPath->GetOutlinerParaObject()->Clone());
//STRIP001  }
//STRIP001 }

/*N*/ void SdrEditView::DismantleMarkedObjects(BOOL bMakeLines)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  UINT32 nCnt(0);
//STRIP001  // Temporaere Marklist
//STRIP001  SdrMarkList aRemoveMerker;
//STRIP001
//STRIP001  aMark.ForceSort();
//STRIP001  // Der Comment wird spaeter zusammengebaut
//STRIP001  BegUndo(String(), String(),
//STRIP001      bMakeLines ? SDRREPFUNC_OBJ_DISMANTLE_LINES : SDRREPFUNC_OBJ_DISMANTLE_POLYS);
//STRIP001
//STRIP001  ULONG nm;
//STRIP001  ULONG nAnz=aMark.GetMarkCount();
//STRIP001  SdrObjList* pOL0=NULL;
//STRIP001  for (nm=nAnz; nm>0;) {
//STRIP001      nm--;
//STRIP001      SdrMark* pM=aMark.GetMark(nm);
//STRIP001      SdrObject* pObj=pM->GetObj();
//STRIP001      SdrPageView* pPV=pM->GetPageView();
//STRIP001      SdrObjList* pOL=pObj->GetObjList();
//STRIP001      if (pOL!=pOL0) { pOL0=pOL; pObj->GetOrdNum(); } // sicherstellen, dass OrdNums stimmen!
//STRIP001      if (ImpCanDismantle(pObj,bMakeLines)) {
//STRIP001          aRemoveMerker.InsertEntry(SdrMark(pObj,pM->GetPageView()));
//STRIP001          ULONG nPos0=pObj->GetOrdNumDirect();
//STRIP001          ULONG nPos=nPos0+1;
//STRIP001          SdrObjList* pSubList=pObj->GetSubList();
//STRIP001          if (pSubList!=NULL && !pObj->Is3DObj()) {
//STRIP001              SdrObjListIter aIter(*pSubList,IM_DEEPNOGROUPS);
//STRIP001              while (aIter.IsMore()) {
//STRIP001                  const SdrObject* pObj1=aIter.Next();
//STRIP001                  ImpDismantleOneObject(pObj1,*pOL,nPos,pPV,bMakeLines);
//STRIP001              }
//STRIP001          } else {
//STRIP001              ImpDismantleOneObject(pObj,*pOL,nPos,pPV,bMakeLines);
//STRIP001          }
//STRIP001          AddUndo(new SdrUndoDelObj(*pObj,TRUE));
//STRIP001          pOL->RemoveObject(nPos0);
//STRIP001      }
//STRIP001  }
//STRIP001  // UndoComment aus den tatsaechlich verwendeten Objekten zusammenbauen
//STRIP001  SetUndoComment(ImpGetResStr(bMakeLines?STR_EditDismantle_Lines:STR_EditDismantle_Polys),aRemoveMerker.GetMarkDescription());
//STRIP001  // die tatsaechlich verwendeten Objekten aus der Liste entfernen
//STRIP001  EndUndo();
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//   #### ####   ###  #   # ####
//  #     #   # #   # #   # #   #
//  #  ## ####  #   # #   # ####
//  #   # #   # #   # #   # #
//   #### #   #  ###   ###  #
//
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrEditView::GroupMarked(const SdrObject* pUserGrp)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  if (HasMarkedObj()) {
//STRIP001      BegUndo(ImpGetResStr(STR_EditGroup),aMark.GetMarkDescription(),SDRREPFUNC_OBJ_GROUP);
//STRIP001      aMark.ForceSort();
//STRIP001      ULONG nAnz=aMark.GetMarkCount();
//STRIP001      for (ULONG nm=nAnz; nm>0;) { // UndoActions fuer alle betroffenen Objekte anlegen
//STRIP001          nm--;
//STRIP001          SdrMark* pM=aMark.GetMark(nm);
//STRIP001          AddUndo(new SdrUndoRemoveObj(*pM->GetObj()));
//STRIP001      }
//STRIP001
//STRIP001      SdrMarkList aNewMark;
//STRIP001      for (USHORT nv=0; nv<GetPageViewCount(); nv++) {
//STRIP001          SdrPageView* pPV=GetPageViewPvNum(nv);
//STRIP001          SdrObjList* pAktLst=pPV->GetObjList();
//STRIP001          SdrObjList* pSrcLst=pAktLst;
//STRIP001          SdrObjList* pSrcLst0=pSrcLst;
//STRIP001          SdrPage*    pPage=pPV->GetPage();
//STRIP001          // sicherstellen, dass die OrdNums stimmen
//STRIP001          if (pSrcLst->IsObjOrdNumsDirty()) pSrcLst->RecalcObjOrdNums();
//STRIP001          SdrObject*  pGrp=NULL;
//STRIP001          SdrObject*  pRefObj=NULL; // Referenz fuer InsertReason (-> rumankern im Writer)
//STRIP001          SdrObject*  pRefObj1=NULL; // Referenz fuer InsertReason (-> rumankern im Writer)
//STRIP001          SdrObjList* pDstLst=NULL;
//STRIP001          // Falls alle markierten Objekte aus Fremden Obj-Listen
//STRIP001          // kommen, kommt das Gruppenobjekt an das Ende der Liste.
//STRIP001          ULONG       nInsPos=pSrcLst->GetObjCount();
//STRIP001          BOOL    bNeedInsPos=TRUE;
//STRIP001          for (ULONG nm=aMark.GetMarkCount(); nm>0;) {
//STRIP001              nm--;
//STRIP001              SdrMark* pM=aMark.GetMark(nm);
//STRIP001              if (pM->GetPageView()==pPV) {
//STRIP001                  if (pGrp==NULL) {
//STRIP001                      if (pUserGrp!=NULL) pGrp=pUserGrp->Clone();
//STRIP001                      if (pGrp==NULL) pGrp=new SdrObjGroup;
//STRIP001                      pDstLst=pGrp->GetSubList();
//STRIP001                      DBG_ASSERT(pDstLst!=NULL,"Angebliches Gruppenobjekt liefert keine Objektliste");
//STRIP001                  }
//STRIP001                  SdrObject* pObj=pM->GetObj();
//STRIP001                  pSrcLst=pObj->GetObjList();
//STRIP001                  if (pSrcLst!=pSrcLst0) {
//STRIP001                      if (pSrcLst->IsObjOrdNumsDirty()) pSrcLst->RecalcObjOrdNums();
//STRIP001                  }
//STRIP001                  BOOL bForeignList=pSrcLst!=pAktLst;
//STRIP001                  BOOL bGrouped=pSrcLst!=pPage;
//STRIP001                  if (!bForeignList && bNeedInsPos) {
//STRIP001                      nInsPos=pObj->GetOrdNum(); // ua, damit sind alle ObjOrdNum der Page gesetzt
//STRIP001                      nInsPos++;
//STRIP001                      bNeedInsPos=FALSE;
//STRIP001                  }
//STRIP001                  pSrcLst->RemoveObject(pObj->GetOrdNumDirect());
//STRIP001                  if (!bForeignList) nInsPos--; // InsertPos korregieren
//STRIP001                  SdrInsertReason aReason(SDRREASON_VIEWCALL);
//STRIP001                  pDstLst->InsertObject(pObj,0,&aReason);
//STRIP001                  aMark.DeleteMarkNum(nm);
//STRIP001                  if (pRefObj1==NULL) pRefObj1=pObj; // Das oberste sichtbare Objekt
//STRIP001                  if (!bGrouped) {
//STRIP001                      if (pRefObj==NULL) pRefObj=pObj; // Das oberste sichtbare nicht gruppierte Objekt
//STRIP001                  }
//STRIP001                  pSrcLst0=pSrcLst;
//STRIP001              }
//STRIP001          }
//STRIP001          if (pRefObj==NULL) pRefObj=pRefObj1;
//STRIP001          if (pGrp!=NULL) {
//STRIP001              aNewMark.InsertEntry(SdrMark(pGrp,pPV));
//STRIP001              ULONG nAnz=pDstLst->GetObjCount();
//STRIP001              SdrInsertReason aReason(SDRREASON_VIEWCALL,pRefObj);
//STRIP001              pAktLst->InsertObject(pGrp,nInsPos,&aReason);
//STRIP001              AddUndo(new SdrUndoNewObj(*pGrp,TRUE)); // Kein Recalc!
//STRIP001              for (ULONG no=0; no<nAnz; no++) {
//STRIP001                  AddUndo(new SdrUndoInsertObj(*pDstLst->GetObj(no)));
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      aMark.Merge(aNewMark);
//STRIP001      MarkListHasChanged();
//STRIP001      EndUndo();
//STRIP001  }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  #   # #   #  #### ####   ###  #   # ####
//  #   # ##  # #     #   # #   # #   # #   #
//  #   # # # # #  ## ####  #   # #   # ####
//  #   # #  ## #   # #   # #   # #   # #
//   ###  #   #  #### #   #  ###   ###  #
//
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrEditView::UnGroupMarked()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  SdrMarkList aNewMark;
//STRIP001
//STRIP001  BegUndo(String(), String(), SDRREPFUNC_OBJ_UNGROUP);
//STRIP001  ULONG nCount=0;
//STRIP001  XubString aName1;
//STRIP001  XubString aName;
//STRIP001  BOOL bNameOk=FALSE;
//STRIP001  for (ULONG nm=aMark.GetMarkCount(); nm>0;) {
//STRIP001      nm--;
//STRIP001      SdrMark* pM=aMark.GetMark(nm);
//STRIP001      SdrObject* pGrp=pM->GetObj();
//STRIP001      SdrObjList* pSrcLst=pGrp->GetSubList();
//STRIP001      if (pSrcLst!=NULL) {
//STRIP001          nCount++;
//STRIP001          if (nCount==1) {
//STRIP001              pGrp->TakeObjNameSingul(aName);  // Bezeichnung der Gruppe holen
//STRIP001              pGrp->TakeObjNamePlural(aName1); // Bezeichnung der Gruppe holen
//STRIP001              bNameOk=TRUE;
//STRIP001          } else {
//STRIP001              if (nCount==2) aName=aName1; // Pluralname setzen
//STRIP001              if (bNameOk) {
//STRIP001                  XubString aStr;
//STRIP001                  pGrp->TakeObjNamePlural(aStr); // Bezeichnung der Gruppe holen
//STRIP001
//STRIP001                  if(!aStr.Equals(aName))
//STRIP001                      bNameOk = FALSE;
//STRIP001              }
//STRIP001          }
//STRIP001          ULONG nDstCnt=pGrp->GetOrdNum();
//STRIP001          SdrObjList* pDstLst=pM->GetPageView()->GetObjList();
//STRIP001
//STRIP001          // FIRST move contained objects to parent of group, so that
//STRIP001          // the contained objects are NOT migrated to the UNDO-ItemPool
//STRIP001          // when AddUndo(new SdrUndoDelObj(*pGrp)) is called.
//STRIP001          ULONG nAnz=pSrcLst->GetObjCount();
//STRIP001          ULONG no;
//STRIP001          for (no=nAnz; no>0;) {
//STRIP001              no--;
//STRIP001              SdrObject* pObj=pSrcLst->GetObj(no);
//STRIP001              AddUndo(new SdrUndoRemoveObj(*pObj));
//STRIP001          }
//STRIP001          for (no=0; no<nAnz; no++) {
//STRIP001              SdrObject* pObj=pSrcLst->RemoveObject(0);
//STRIP001              SdrInsertReason aReason(SDRREASON_VIEWCALL,pGrp);
//STRIP001              pDstLst->InsertObject(pObj,nDstCnt,&aReason);
//STRIP001              AddUndo(new SdrUndoInsertObj(*pObj,TRUE)); // Kein RecalcOrdNum
//STRIP001              nDstCnt++;
//STRIP001              // Kein SortCheck beim einfuegen in die MarkList, denn das
//STRIP001              // wuerde wg. pObj->GetOrdNum() jedesmal ein RecalcOrdNums()
//STRIP001              // provozieren:
//STRIP001              aNewMark.InsertEntry(SdrMark(pObj,pM->GetPageView()),FALSE);
//STRIP001          }
//STRIP001
//STRIP001          // Now it is safe to add the delete-UNDO which trigers the
//STRIP001          // MigrateItemPool now only for itself, not for the subobjects.
//STRIP001          // nDstCnt is right, because previous inserts move group
//STRIP001          // object deeper and increase nDstCnt.
//STRIP001          AddUndo(new SdrUndoDelObj(*pGrp));
//STRIP001          pDstLst->RemoveObject(nDstCnt);
//STRIP001
//STRIP001          aMark.DeleteMarkNum(nm);
//STRIP001      }
//STRIP001  }
//STRIP001  if (nCount!=0) {
//STRIP001      if (!bNameOk) aName=ImpGetResStr(STR_ObjNamePluralGRUP); // Oberbegriff Gruppenobjekte verwenden, wenn verschiedene Objekte.
//STRIP001      SetUndoComment(ImpGetResStr(STR_EditUngroup),aName);
//STRIP001  }
//STRIP001  EndUndo();
//STRIP001  if (nCount!=0) {
//STRIP001      aMark.Merge(aNewMark,TRUE); // Durch das obige Einsortieren ist aNewMark genau verkehrtherum
//STRIP001      MarkListHasChanged();
//STRIP001  }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//   ###   ###  #   # #   # ##### ####  #####   #####  ###    ####   ###  #  #   #
//  #   # #   # ##  # #   # #     #   #   #       #   #   #   #   # #   # #   # #
//  #     #   # # # # #   # ####  ####    #       #   #   #   ####  #   # #    #
//  #   # #   # #  ##  # #  #     #   #   #       #   #   #   #     #   # #    #
//   ###   ###  #   #   #   ##### #   #   #       #    ###    #      ###  #### #
//
////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 SdrObject* SdrEditView::ImpConvertOneObj(SdrObject* pObj, BOOL bPath, BOOL bLineToArea)
//STRIP001 {
//STRIP001  SdrObject* pNewObj = pObj->ConvertToPolyObj(bPath, bLineToArea);
//STRIP001  if (pNewObj!=NULL) {
//STRIP001      SdrObjList* pOL=pObj->GetObjList();
//STRIP001      DBG_ASSERT(pOL!=NULL,"ConvertTo: Obj liefert keine ObjList");
//STRIP001      if (pOL!=NULL) {
//STRIP001          AddUndo(new SdrUndoReplaceObj(*pObj,*pNewObj));
//STRIP001          pOL->ReplaceObject(pNewObj,pObj->GetOrdNum());
//STRIP001      }
//STRIP001  }
//STRIP001  return pNewObj;
//STRIP001 }

//STRIP001 void SdrEditView::ImpConvertTo(BOOL bPath, BOOL bLineToArea)
//STRIP001 {
//STRIP001  BOOL bMrkChg=FALSE;
//STRIP001  BOOL bModChg=FALSE;
//STRIP001  if (HasMarkedObj()) {
//STRIP001      ULONG nMarkAnz=aMark.GetMarkCount();
//STRIP001      USHORT nDscrID=0;
//STRIP001      if(bLineToArea)
//STRIP001      {
//STRIP001          if(nMarkAnz == 1)
//STRIP001              nDscrID = STR_EditConvToContour;
//STRIP001          else
//STRIP001              nDscrID = STR_EditConvToContours;
//STRIP001
//STRIP001          BegUndo(ImpGetResStr(nDscrID), aMark.GetMarkDescription());
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          if (bPath) {
//STRIP001              if (nMarkAnz==1) nDscrID=STR_EditConvToCurve;
//STRIP001              else nDscrID=STR_EditConvToCurves;
//STRIP001              BegUndo(ImpGetResStr(nDscrID),aMark.GetMarkDescription(),SDRREPFUNC_OBJ_CONVERTTOPATH);
//STRIP001          } else {
//STRIP001              if (nMarkAnz==1) nDscrID=STR_EditConvToPoly;
//STRIP001              else nDscrID=STR_EditConvToPolys;
//STRIP001              BegUndo(ImpGetResStr(nDscrID),aMark.GetMarkDescription(),SDRREPFUNC_OBJ_CONVERTTOPOLY);
//STRIP001          }
//STRIP001      }
//STRIP001      for (ULONG nm=nMarkAnz; nm>0;) {
//STRIP001          nm--;
//STRIP001          SdrMark* pM=aMark.GetMark(nm);
//STRIP001          SdrObject* pObj=pM->GetObj();
//STRIP001          SdrPageView* pPV=pM->GetPageView();
//STRIP001          if (pObj->IsGroupObject() && !pObj->Is3DObj()) {
//STRIP001              SdrObject* pGrp=pObj;
//STRIP001              SdrObjListIter aIter(*pGrp,IM_DEEPNOGROUPS);
//STRIP001              while (aIter.IsMore()) {
//STRIP001                  pObj=aIter.Next();
//STRIP001                  if (ImpConvertOneObj(pObj,bPath,bLineToArea)) bModChg=TRUE;
//STRIP001              }
//STRIP001          } else {
//STRIP001              SdrObject* pNewObj=ImpConvertOneObj(pObj,bPath,bLineToArea);
//STRIP001              if (pNewObj!=NULL) {
//STRIP001                  bModChg=TRUE;
//STRIP001                  bMrkChg=TRUE;
//STRIP001                  aMark.ReplaceMark(SdrMark(pNewObj,pPV),nm);
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001      EndUndo();
//STRIP001      if (bMrkChg) AdjustMarkHdl();
//STRIP001      if (bMrkChg) MarkListHasChanged();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrEditView::ConvertMarkedToPathObj(BOOL bLineToArea)
//STRIP001 {
//STRIP001  ImpConvertTo(TRUE, bLineToArea);
//STRIP001 }

//STRIP001 void SdrEditView::ConvertMarkedToPolyObj(BOOL bLineToArea)
//STRIP001 {
//STRIP001  ImpConvertTo(FALSE, bLineToArea);
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  #   # ##### #####  ###  ##### # #    #####      # #   # ####   ###  ####  #####
//  ## ## #       #   #   # #     # #    #          # ## ## #   # #   # #   #   #
//  # # # ####    #   ##### ###   # #    ####  ###  # # # # ####  #   # ####    #
//  #   # #       #   #   # #     # #    #          # #   # #     #   # #   #   #
//  #   # #####   #   #   # #     # #### #####      # #   # #      ###  #   #   #
//
////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrEditView::DoImportMarkedMtf(SvdProgressInfo *pProgrInfo)
//STRIP001 {
//STRIP001  BegUndo(String(), String(), SDRREPFUNC_OBJ_IMPORTMTF);
//STRIP001  aMark.ForceSort();
//STRIP001  SdrMarkList aForTheDescription;
//STRIP001  SdrMarkList aNewMarked;
//STRIP001  ULONG nAnz=aMark.GetMarkCount();
//STRIP001
//STRIP001  for (ULONG nm=nAnz; nm>0;)
//STRIP001  { // Undo Objekte fuer alle neuen Objekte erzeugen
//STRIP001      // zwischen den Metafiles auf Abbruch testen
//STRIP001      if( pProgrInfo != NULL )
//STRIP001      {
//STRIP001          pProgrInfo->SetNextObject();
//STRIP001          if(!pProgrInfo->ReportActions(0))
//STRIP001              break;
//STRIP001      }
//STRIP001
//STRIP001      nm--;
//STRIP001      SdrMark*     pM=aMark.GetMark(nm);
//STRIP001      SdrObject*   pObj=pM->GetObj();
//STRIP001      SdrPageView* pPV=pM->GetPageView();
//STRIP001      SdrObjList*  pOL=pObj->GetObjList();
//STRIP001      ULONG        nInsPos=pObj->GetOrdNum()+1;
//STRIP001      SdrGrafObj*  pGraf=PTR_CAST(SdrGrafObj,pObj);
//STRIP001      SdrOle2Obj*  pOle2=PTR_CAST(SdrOle2Obj,pObj);
//STRIP001      ULONG        nInsAnz=0;
//STRIP001      if (pGraf!=NULL && pGraf->HasGDIMetaFile())
//STRIP001      {
//STRIP001          ImpSdrGDIMetaFileImport aFilter(*pMod);
//STRIP001          aFilter.SetScaleRect(pGraf->GetSnapRect());
//STRIP001          aFilter.SetLayer(pObj->GetLayer());
//STRIP001          nInsAnz=aFilter.DoImport(pGraf->GetTransformedGraphic().GetGDIMetaFile(),*pOL,nInsPos,pProgrInfo);
//STRIP001      }
//STRIP001      if (pOle2!=NULL && pOle2->HasGDIMetaFile())
//STRIP001      {
//STRIP001          const GDIMetaFile* pMtf=pOle2->GetGDIMetaFile();
//STRIP001          ImpSdrGDIMetaFileImport aFilter(*pMod);
//STRIP001          aFilter.SetScaleRect(pOle2->GetLogicRect());
//STRIP001          aFilter.SetLayer(pObj->GetLayer());
//STRIP001          nInsAnz=aFilter.DoImport(*pMtf,*pOL,nInsPos,pProgrInfo);
//STRIP001      }
//STRIP001      if (nInsAnz!=0) {
//STRIP001          ULONG nObj=nInsPos;
//STRIP001          for (ULONG i=0; i<nInsAnz; i++) {
//STRIP001              AddUndo(new SdrUndoNewObj(*pOL->GetObj(nObj)));
//STRIP001
//STRIP001              // Neue MarkList pflegen
//STRIP001              SdrMark aNewMark(pOL->GetObj(nObj), pPV);
//STRIP001              aNewMarked.InsertEntry(aNewMark);
//STRIP001
//STRIP001              nObj++;
//STRIP001          }
//STRIP001          aForTheDescription.InsertEntry(*pM);
//STRIP001          AddUndo(new SdrUndoDelObj(*pObj));
//STRIP001
//STRIP001          // Objekt aus selektion loesen und loeschen
//STRIP001          aMark.DeleteMark(aMark.FindObject(pObj));
//STRIP001          pOL->RemoveObject(nInsPos-1);
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  // MarkObj... fehlt... jetzt nicht mehr (AW)
//STRIP001  if(aNewMarked.GetMarkCount())
//STRIP001  {
//STRIP001      // Neue Selektion bilden
//STRIP001      for(INT32 a=0;a<aNewMarked.GetMarkCount();a++)
//STRIP001          aMark.InsertEntry(*aNewMarked.GetMark(a));
//STRIP001      aMark.ForceSort();
//STRIP001  }
//STRIP001
//STRIP001  SetUndoComment(ImpGetResStr(STR_EditImportMtf),aForTheDescription.GetMarkDescription());
//STRIP001  EndUndo();
//STRIP001 }

}
