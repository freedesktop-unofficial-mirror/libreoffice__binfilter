/*************************************************************************
 *
 *  $RCSfile: svx_svdpage.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:41 $
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

// HACK
#ifdef SVX_LIGHT
#define _IPOBJ_HXX
#endif

#ifndef _SOT_STORAGE_HXX
#include <sot/storage.hxx>
#endif
#ifndef _SOT_CLSIDS_HXX
#include <sot/clsids.hxx>
#endif
#ifndef _SVSTOR_HXX //autogen
#include <so3/svstor.hxx>
#endif
#ifndef _PERSIST_HXX
#include <so3/persist.hxx>
#endif
#ifndef _SVDVIEW_HXX
#include "svdview.hxx"
#endif
#include "svdpage.hxx"
#include <string.h>
#ifndef _STRING_H
#define _STRING_H
#endif
#ifndef _APP_HXX //autogen
#include <vcl/svapp.hxx>
#endif
#ifndef _IPOBJ_HXX //autogen
#include <so3/ipobj.hxx>
#endif

#include "svdetc.hxx"
#include "svdxout.hxx"
#include "svdio.hxx"
#include "svdobj.hxx"
#include "svdogrp.hxx"
#include "svdograf.hxx" // fuer SwapInAll()
#include "svdoedge.hxx" // Zum kopieren der Konnektoren
#include "svdoole2.hxx" // Sonderbehandlung OLE beim SdrExchangeFormat
#include "svditer.hxx"
#include "svdmodel.hxx"
#include "svdlayer.hxx"
#include "svdotext.hxx"
#include "svdpagv.hxx"
#include "svdundo.hxx"
#include "fmglob.hxx"
#include "polysc3d.hxx"

#ifndef SVX_LIGHT
#include "fmdpage.hxx"
#else
#include "unopage.hxx"
#endif

#ifndef _SV_SALBTYPE_HXX
#include <vcl/salbtype.hxx>     // FRound
#endif
namespace binfilter {

using namespace ::com::sun::star;

/*N*/ DBG_NAME(SdrObjList)

/*N*/ TYPEINIT0(SdrObjList);

/*N*/ SdrObjList::SdrObjList(SdrModel* pNewModel, SdrPage* pNewPage, SdrObjList* pNewUpList):
/*N*/   aList(1024,64,64)
/*N*/ {
/*N*/   DBG_CTOR(SdrObjList,NULL);
/*N*/   pModel=pNewModel;
/*N*/   pPage=pNewPage;
/*N*/   pUpList=pNewUpList;
/*N*/   bObjOrdNumsDirty=FALSE;
/*N*/   bRectsDirty=FALSE;
/*N*/   pOwnerObj=NULL;
/*N*/   eListKind=SDROBJLIST_UNKNOWN;
/*N*/ }

/*?*/ SdrObjList::SdrObjList(const SdrObjList& rSrcList):
/*?*/   aList(1024,64,64)
/*?*/ {
/*?*/   DBG_CTOR(SdrObjList,NULL);
/*?*/   pModel=NULL;
/*?*/   pPage=NULL;
/*?*/   pUpList=NULL;
/*?*/   bObjOrdNumsDirty=FALSE;
/*?*/   bRectsDirty=FALSE;
/*?*/   pOwnerObj=NULL;
/*?*/   eListKind=SDROBJLIST_UNKNOWN;
/*?*/   *this=rSrcList;
/*?*/ }

/*N*/ SdrObjList::~SdrObjList()
/*N*/ {
/*N*/   DBG_DTOR(SdrObjList,NULL);
/*N*/   Clear(); // Containerinhalt loeschen!
/*N*/ }

/*N*/ void SdrObjList::operator=(const SdrObjList& rSrcList)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  Clear();
//STRIP001  eListKind=rSrcList.eListKind;
//STRIP001  CopyObjects(rSrcList);
/*N*/ }

/*N*/ void SdrObjList::CopyObjects(const SdrObjList& rSrcList)
/*N*/ {
/*N*/   Clear();
/*N*/   bObjOrdNumsDirty=FALSE;
/*N*/   bRectsDirty     =FALSE;
/*N*/   ULONG nCloneErrCnt=0;
/*N*/   ULONG nAnz=rSrcList.GetObjCount();
/*N*/   SdrInsertReason aReason(SDRREASON_COPY);
/*N*/   ULONG no;
/*N*/   for (no=0; no<nAnz; no++) {
/*N*/       SdrObject* pSO=rSrcList.GetObj(no);
/*N*/       SdrObject* pDO=pSO->Clone(pPage,pModel);
/*N*/       if (pDO!=NULL) {
/*N*/           NbcInsertObject(pDO,CONTAINER_APPEND,&aReason);
/*N*/       } else {
/*N*/           nCloneErrCnt++;
/*N*/       }
/*N*/   }
/*N*/   // und nun zu den Konnektoren
/*N*/   // Die neuen Objekte werden auf die der rSrcList abgebildet
/*N*/   // und so die Objektverbindungen hergestellt.
/*N*/   // Aehnliche Implementation an folgenden Stellen:
/*N*/   //    void SdrObjList::CopyObjects(const SdrObjList& rSrcList)
/*N*/   //    SdrModel* SdrExchangeView::GetMarkedObjModel() const
/*N*/   //    FASTBOOL SdrExchangeView::Paste(const SdrModel& rMod,...)
/*N*/   //    void SdrEditView::CopyMarked()
/*N*/   if (nCloneErrCnt==0) {
/*N*/       for (no=0; no<nAnz; no++) {
/*N*/           const SdrObject* pSrcOb=rSrcList.GetObj(no);
/*N*/           SdrEdgeObj* pSrcEdge=PTR_CAST(SdrEdgeObj,pSrcOb);
/*N*/           if (pSrcEdge!=NULL) {
/*?*/               SdrObject* pSrcNode1=pSrcEdge->GetConnectedNode(TRUE);
/*?*/               SdrObject* pSrcNode2=pSrcEdge->GetConnectedNode(FALSE);
/*?*/               if (pSrcNode1!=NULL && pSrcNode1->GetObjList()!=pSrcEdge->GetObjList()) pSrcNode1=NULL; // Listenuebergreifend
/*?*/               if (pSrcNode2!=NULL && pSrcNode2->GetObjList()!=pSrcEdge->GetObjList()) pSrcNode2=NULL; // ist (noch) nicht
/*?*/               if (pSrcNode1!=NULL || pSrcNode2!=NULL) {
/*?*/                   SdrObject* pEdgeObjTmp=GetObj(no);
/*?*/                   SdrEdgeObj* pDstEdge=PTR_CAST(SdrEdgeObj,pEdgeObjTmp);
/*?*/                   if (pDstEdge!=NULL) {
/*?*/                       if (pSrcNode1!=NULL) {
/*?*/                           ULONG nDstNode1=pSrcNode1->GetOrdNum();
/*?*/                           SdrObject* pDstNode1=GetObj(nDstNode1);
/*?*/                           if (pDstNode1!=NULL) { // Sonst grober Fehler!
/*?*/                               pDstEdge->ConnectToNode(TRUE,pDstNode1);
/*?*/                           } else {
/*?*/                               DBG_ERROR("SdrObjList::operator=(): pDstNode1==NULL!");
/*?*/                           }
/*?*/                       }
/*?*/                       if (pSrcNode2!=NULL) {
/*?*/                           ULONG nDstNode2=pSrcNode2->GetOrdNum();
/*?*/                           SdrObject* pDstNode2=GetObj(nDstNode2);
/*?*/                           if (pDstNode2!=NULL) { // Node war sonst wohl nicht markiert
/*?*/                               pDstEdge->ConnectToNode(FALSE,pDstNode2);
/*?*/                           } else {
/*?*/                               DBG_ERROR("SdrObjList::operator=(): pDstNode2==NULL!");
/*?*/                           }
/*?*/                       }
/*?*/                   } else {
/*?*/                       DBG_ERROR("SdrObjList::operator=(): pDstEdge==NULL!");
/*?*/                   }
/*?*/               }
/*N*/           }
/*N*/       }
/*N*/   } else {
/*N*/ #ifdef DBG_UTIL
/*?*/       ByteString aStr("SdrObjList::operator=(): Fehler beim Clonen ");
/*?*/
/*?*/       if(nCloneErrCnt == 1)
/*?*/       {
/*?*/           aStr += "eines Zeichenobjekts.";
/*?*/       }
/*?*/       else
/*?*/       {
/*?*/           aStr += "von ";
/*?*/           aStr += ByteString::CreateFromInt32( nCloneErrCnt );
/*?*/           aStr += " Zeichenobjekten.";
/*?*/       }
/*?*/
/*?*/       aStr += " Objektverbindungen werden nicht mitkopiert.";
/*?*/
/*?*/       DBG_ERROR(aStr.GetBuffer());
/*?*/ #endif
/*N*/   }
/*N*/ }

/*N*/ void SdrObjList::Clear()
/*N*/ {
/*N*/   ULONG nAnz=GetObjCount();
/*N*/
/*N*/   if(pModel!=NULL && nAnz!=0)
/*N*/   {
/*N*/       SdrHint aHint(HINT_OBJLISTCLEAR);
/*N*/       aHint.SetPage(pPage);
/*N*/       aHint.SetObjList(this);
/*N*/       pModel->Broadcast(aHint);
/*N*/   }
/*N*/
/*N*/   for (ULONG no=0; no<nAnz; no++) {
/*N*/       SdrObject* pObj=GetObj(no);
/*N*/       delete pObj;
/*N*/   }
/*N*/   aList.Clear();
/*N*/   if (pModel!=NULL && nAnz!=0)
/*N*/   {
/*N*/       pModel->SetChanged();
/*N*/       SdrHint aHint(HINT_OBJLISTCLEARED);
/*N*/       aHint.SetPage(pPage);
/*N*/       aHint.SetObjList(this);
/*N*/       pModel->Broadcast(aHint);
/*N*/   }
/*N*/ }

/*N*/ SdrPage* SdrObjList::GetPage() const
/*N*/ {
/*N*/   return pPage;
/*N*/ }

/*N*/ void SdrObjList::SetPage(SdrPage* pNewPage)
/*N*/ {
/*N*/   if (pPage!=pNewPage) {
/*N*/       pPage=pNewPage;
/*N*/       ULONG nAnz=GetObjCount();
/*N*/       for (ULONG no=0; no<nAnz; no++) {
/*N*/           SdrObject* pObj=GetObj(no);
/*N*/           pObj->SetPage(pPage);
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ SdrModel* SdrObjList::GetModel() const
/*N*/ {
/*N*/   return pModel;
/*N*/ }

/*N*/ void SdrObjList::SetModel(SdrModel* pNewModel)
/*N*/ {
/*N*/   if (pModel!=pNewModel) {
/*N*/       pModel=pNewModel;
/*N*/       ULONG nAnz=GetObjCount();
/*N*/       for (ULONG i=0; i<nAnz; i++) {
/*N*/           SdrObject* pObj=GetObj(i);
/*N*/           pObj->SetModel(pModel);
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void SdrObjList::RecalcObjOrdNums()
/*N*/ {
/*N*/   ULONG nAnz=GetObjCount();
/*N*/   for (ULONG no=0; no<nAnz; no++) {
/*N*/       SdrObject* pObj=GetObj(no);
/*N*/       pObj->SetOrdNum(no);
/*N*/   }
/*N*/   bObjOrdNumsDirty=FALSE;
/*N*/ }

/*N*/ void SdrObjList::RecalcRects()
/*N*/ {
/*N*/   aOutRect=Rectangle();
/*N*/   aSnapRect=aOutRect;
/*N*/   ULONG nAnz=GetObjCount();
/*N*/   ULONG i;
/*N*/   for (i=0; i<nAnz; i++) {
/*N*/       SdrObject* pObj=GetObj(i);
/*N*/       if (i==0) {
/*N*/           aOutRect=pObj->GetBoundRect();
/*N*/           aSnapRect=pObj->GetSnapRect();
/*N*/       } else {
/*N*/           aOutRect.Union(pObj->GetBoundRect());
/*N*/           aSnapRect.Union(pObj->GetSnapRect());
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void SdrObjList::SetRectsDirty()
/*N*/ {
/*N*/   bRectsDirty=TRUE;
/*N*/   if (pUpList!=NULL) pUpList->SetRectsDirty();
/*N*/ }

/*N*/ void SdrObjList::NbcInsertObject(SdrObject* pObj, ULONG nPos, const SdrInsertReason* pReason)
/*N*/ {
/*N*/   DBG_ASSERT(pObj!=NULL,"SdrObjList::NbcInsertObject(NULL)");
/*N*/   if (pObj!=NULL) {
/*N*/       DBG_ASSERT(!pObj->IsInserted(),"ZObjekt hat bereits Inserted-Status");
/*N*/       ULONG nAnz=GetObjCount();
/*N*/       if (nPos>nAnz) nPos=nAnz;
/*N*/       aList.Insert(pObj,nPos);
/*N*/       if (nPos<nAnz) bObjOrdNumsDirty=TRUE;
/*N*/       pObj->SetOrdNum(nPos);
/*N*/       pObj->SetObjList(this);
/*N*/       pObj->SetPage(pPage);
/*N*/       if (!bRectsDirty) {
/*N*/           aOutRect.Union(pObj->GetBoundRect());
/*N*/           aSnapRect.Union(pObj->GetSnapRect());
/*N*/       }
/*N*/       pObj->SetInserted(TRUE); // Ruft u.a. den UserCall
/*N*/   }
/*N*/ }

/*N*/ void SdrObjList::InsertObject(SdrObject* pObj, ULONG nPos, const SdrInsertReason* pReason)
/*N*/ {
/*N*/   DBG_ASSERT(pObj!=NULL,"SdrObjList::InsertObject(NULL)");
/*N*/
/*N*/   if(pObj)
/*N*/   {
/*N*/       if(pOwnerObj && !GetObjCount())
/*N*/       {
/*N*/           // damit der graue Rahmen des leeren Gruppenobjekts korrekt weggemalt wird
/*N*/           pOwnerObj->SendRepaintBroadcast();
/*N*/       }
/*N*/
/*N*/       // #69055# if anchor is used, reset it before grouping
/*N*/       if(GetOwnerObj())
/*N*/       {
/*N*/           const Point& rAnchorPos = pObj->GetAnchorPos();
/*N*/           if(rAnchorPos.X() || rAnchorPos.Y())
/*N*/               pObj->NbcSetAnchorPos(Point());
/*N*/       }
/*N*/
/*N*/       // do insert to new group
/*N*/       NbcInsertObject(pObj, nPos, pReason);
/*N*/
/*N*/       // Falls das Objekt in eine Gruppe eingefuegt wird
/*N*/       // und nicht mit seinen Bruedern ueberlappt, muss es
/*N*/       // einen eigenen Redraw bekommen
/*N*/       if(pOwnerObj)
/*N*/       {
/*N*/           pOwnerObj->SendRepaintBroadcast();
/*N*/       }
/*N*/
/*N*/       if(pModel)
/*N*/       {
/*N*/           // Hier muss ein anderer Broadcast her!
/*N*/           // Repaint ab Objekt Nummer ... (Achtung: GroupObj)
/*N*/           if(pObj->GetPage())
/*N*/           {
/*N*/               SdrHint aHint(*pObj);
/*N*/
/*N*/               aHint.SetKind(HINT_OBJINSERTED);
/*N*/               pModel->Broadcast(aHint);
/*N*/           }
/*N*/
/*N*/           pModel->SetChanged();
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ SdrObject* SdrObjList::NbcRemoveObject(ULONG nObjNum)
/*N*/ {DBG_BF_ASSERT(0, "STRIP");return NULL; //STRIP001
//STRIP001  ULONG nAnz=GetObjCount();
//STRIP001  SdrObject* pObj=(SdrObject*)aList.Remove(nObjNum);
//STRIP001  DBG_ASSERT(pObj!=NULL,"Object zum Removen nicht gefunden");
//STRIP001  if (pObj!=NULL) {
//STRIP001      DBG_ASSERT(pObj->IsInserted(),"ZObjekt hat keinen Inserted-Status");
//STRIP001      pObj->SetInserted(FALSE); // Ruft u.a. den UserCall
//STRIP001      pObj->SetObjList(NULL);
//STRIP001      pObj->SetPage(NULL);
//STRIP001      if (!bObjOrdNumsDirty) { // Optimierung fuer den Fall, dass das letzte Obj rausgenommen wird
//STRIP001          if (nObjNum!=ULONG(nAnz-1)) {
//STRIP001              bObjOrdNumsDirty=TRUE;
//STRIP001          }
//STRIP001      }
//STRIP001      SetRectsDirty();
//STRIP001  }
//STRIP001  return pObj;
/*N*/ }

/*N*/ SdrObject* SdrObjList::RemoveObject(ULONG nObjNum)
/*N*/ {
/*N*/   ULONG nAnz=GetObjCount();
/*N*/   SdrObject* pObj=(SdrObject*)aList.Remove(nObjNum);
/*N*/   DBG_ASSERT(pObj!=NULL,"Object zum Removen nicht gefunden");
/*N*/   if (pObj!=NULL) {
/*N*/       DBG_ASSERT(pObj->IsInserted(),"ZObjekt hat keinen Inserted-Status");
/*N*/       if (pModel!=NULL) {
/*N*/           // Hier muss ein anderer Broadcast her!
/*N*/           if (pObj->GetPage()!=NULL) {
/*N*/               SdrHint aHint(*pObj);
/*N*/               aHint.SetKind(HINT_OBJREMOVED);
/*N*/               pModel->Broadcast(aHint);
/*N*/           }
/*N*/           pModel->SetChanged();
/*N*/       }
/*N*/       pObj->SetInserted(FALSE); // Ruft u.a. den UserCall
/*N*/       pObj->SetObjList(NULL);
/*N*/       pObj->SetPage(NULL);
/*N*/       if (!bObjOrdNumsDirty) { // Optimierung fuer den Fall, dass das letzte Obj rausgenommen wird
/*N*/           if (nObjNum!=ULONG(nAnz-1)) {
/*N*/               bObjOrdNumsDirty=TRUE;
/*N*/           }
/*N*/       }
/*N*/       SetRectsDirty();
/*N*/       if (pOwnerObj!=NULL && GetObjCount()==0) {
/*N*/           // damit der graue Rahmen des leeren Gruppenobjekts korrekt gemalt wird
/*N*/           pOwnerObj->SendRepaintBroadcast();
/*N*/       }
/*N*/   }
/*N*/   return pObj;
/*N*/ }

//STRIP001 SdrObject* SdrObjList::NbcReplaceObject(SdrObject* pNewObj, ULONG nObjNum)
//STRIP001 {
//STRIP001  SdrObject* pObj=(SdrObject*)aList.GetObject(nObjNum);
//STRIP001  DBG_ASSERT(pObj!=NULL,"SdrObjList::ReplaceObject: Object zum Removen nicht gefunden");
//STRIP001  if (pObj!=NULL) {
//STRIP001      DBG_ASSERT(pObj->IsInserted(),"SdrObjList::ReplaceObject: ZObjekt hat keinen Inserted-Status");
//STRIP001      pObj->SetInserted(FALSE);
//STRIP001      pObj->SetObjList(NULL);
//STRIP001      pObj->SetPage(NULL);
//STRIP001      aList.Replace(pNewObj,nObjNum);
//STRIP001      pNewObj->SetOrdNum(nObjNum);
//STRIP001      pNewObj->SetObjList(this);
//STRIP001      pNewObj->SetPage(pPage);
//STRIP001      pNewObj->SetInserted(TRUE);
//STRIP001      SetRectsDirty();
//STRIP001  }
//STRIP001  return pObj;
//STRIP001 }

/*N*/ SdrObject* SdrObjList::ReplaceObject(SdrObject* pNewObj, ULONG nObjNum)
/*N*/ {
/*N*/   //ULONG nAnz=GetObjCount();
/*N*/   SdrObject* pObj=(SdrObject*)aList.GetObject(nObjNum);
/*N*/   DBG_ASSERT(pObj!=NULL,"SdrObjList::ReplaceObject: Object zum Removen nicht gefunden");
/*N*/   if (pObj!=NULL) {
/*N*/       DBG_ASSERT(pObj->IsInserted(),"SdrObjList::ReplaceObject: ZObjekt hat keinen Inserted-Status");
/*N*/       if (pModel!=NULL) {
/*N*/           // Hier muss ein anderer Broadcast her!
/*N*/           if (pObj->GetPage()!=NULL) {
/*N*/               SdrHint aHint(*pObj);
/*N*/               aHint.SetKind(HINT_OBJREMOVED);
/*N*/               pModel->Broadcast(aHint);
/*N*/           }
/*N*/       }
/*N*/       pObj->SetInserted(FALSE);
/*N*/       pObj->SetObjList(NULL);
/*N*/       pObj->SetPage(NULL);
/*N*/       aList.Replace(pNewObj,nObjNum);
/*N*/       pNewObj->SetOrdNum(nObjNum);
/*N*/       pNewObj->SetObjList(this);
/*N*/       pNewObj->SetPage(pPage);
/*N*/       pNewObj->SetInserted(TRUE);
/*N*/       if (pModel!=NULL) {
/*N*/           // Hier muss ein anderer Broadcast her!
/*N*/           if (pNewObj->GetPage()!=NULL) {
/*N*/               SdrHint aHint(*pNewObj);
/*N*/               aHint.SetKind(HINT_OBJINSERTED);
/*N*/               pModel->Broadcast(aHint);
/*N*/           }
/*N*/           pModel->SetChanged();
/*N*/       }
/*N*/       SetRectsDirty();
/*N*/   }
/*N*/   return pObj;
/*N*/ }

/*N*/ SdrObject* SdrObjList::NbcSetObjectOrdNum(ULONG nOldObjNum, ULONG nNewObjNum)
/*N*/ {
/*N*/   SdrObject* pObj=(SdrObject*)aList.GetObject(nOldObjNum);
/*N*/   if (nOldObjNum==nNewObjNum) return pObj;
/*N*/   DBG_ASSERT(pObj!=NULL,"SdrObjList::NbcSetObjectOrdNum: Object nicht gefunden");
/*N*/   if (pObj!=NULL) {
/*N*/       DBG_ASSERT(pObj->IsInserted(),"SdrObjList::NbcSetObjectOrdNum: ZObjekt hat keinen Inserted-Status");
/*N*/       aList.Remove(nOldObjNum);
/*N*/       aList.Insert(pObj,nNewObjNum);
/*N*/       pObj->SetOrdNum(nNewObjNum);
/*N*/       bObjOrdNumsDirty=TRUE;
/*N*/   }
/*N*/   return pObj;
/*N*/ }

/*N*/ SdrObject* SdrObjList::SetObjectOrdNum(ULONG nOldObjNum, ULONG nNewObjNum)
/*N*/ {
/*N*/   SdrObject* pObj=(SdrObject*)aList.GetObject(nOldObjNum);
/*N*/   if (nOldObjNum==nNewObjNum) return pObj;
/*N*/   DBG_ASSERT(pObj!=NULL,"SdrObjList::SetObjectOrdNum: Object nicht gefunden");
/*N*/   if (pObj!=NULL) {
/*N*/       DBG_ASSERT(pObj->IsInserted(),"SdrObjList::SetObjectOrdNum: ZObjekt hat keinen Inserted-Status");
        /*if (pModel!=NULL) {
            // Hier muss ein anderer Broadcast her!
            if (pObj->GetPage()!=NULL) pModel->Broadcast(SdrHint(*pObj));
        }*/
/*N*/       aList.Remove(nOldObjNum);
/*N*/       aList.Insert(pObj,nNewObjNum);
/*N*/       pObj->SetOrdNum(nNewObjNum);
/*N*/       bObjOrdNumsDirty=TRUE;
/*N*/       if (pModel!=NULL) {
/*N*/           // Hier muss ein anderer Broadcast her!
/*N*/           if (pObj->GetPage()!=NULL) pModel->Broadcast(SdrHint(*pObj));
/*N*/           pModel->SetChanged();
/*N*/       }
/*N*/   }
/*N*/   return pObj;
/*N*/ }

/*N*/ const Rectangle& SdrObjList::GetAllObjSnapRect() const
/*N*/ {
/*N*/   if (bRectsDirty) {
/*N*/       ((SdrObjList*)this)->RecalcRects();
/*N*/       ((SdrObjList*)this)->bRectsDirty=FALSE;
/*N*/   }
/*N*/   return aSnapRect;
/*N*/ }

/*N*/ const Rectangle& SdrObjList::GetAllObjBoundRect() const
/*N*/ {
/*N*/   if (bRectsDirty) {
/*N*/       ((SdrObjList*)this)->RecalcRects();
/*N*/       ((SdrObjList*)this)->bRectsDirty=FALSE;
/*N*/   }
/*N*/   return aOutRect;
/*N*/ }

/*N*/ FASTBOOL SdrObjList::Paint(ExtOutputDevice& rXOut, const SdrPaintInfoRec& rInfoRec, FASTBOOL bRestoreColors) const
/*N*/ {
/*N*/   BOOL bOk(TRUE);
/*N*/   BOOL bWasNotActive = rInfoRec.bNotActive;
/*N*/   BOOL bIsEnteredGroup(FALSE);
/*N*/   UINT32 nWasDrawMode = rXOut.GetOutDev()->GetDrawMode();
/*N*/
/*N*/   if(!rInfoRec.bOriginalDrawModeSet)
/*N*/   {
/*N*/       // Original-Paintmode retten
/*N*/       ((SdrPaintInfoRec&)rInfoRec).bOriginalDrawModeSet = TRUE;
/*N*/       ((SdrPaintInfoRec&)rInfoRec).nOriginalDrawMode = rXOut.GetOutDev()->GetDrawMode();
/*N*/   }
/*N*/
/*N*/   if((rInfoRec.pPV && rInfoRec.pPV->GetObjList() == this)
/*N*/       || (rInfoRec.nPaintMode & SDRPAINTMODE_MASTERPAGE))
/*N*/   {
/*N*/       bIsEnteredGroup = TRUE;
/*N*/   }
/*N*/
/*N*/   if(bIsEnteredGroup && bWasNotActive)
/*N*/   {
/*N*/       // auf aktive Elemente schalten
/*?*/       ((SdrPaintInfoRec&)rInfoRec).bNotActive = FALSE;
/*N*/   }
/*N*/
/*N*/   if(rInfoRec.pPV && rInfoRec.bNotActive)
/*N*/   {
/*?*/       if(rInfoRec.pPV->GetView().DoVisualizeEnteredGroup())
/*?*/       {
/*?*/           // Darstellung schmal
/*?*/           rXOut.GetOutDev()->SetDrawMode(nWasDrawMode | (
/*?*/               DRAWMODE_GHOSTEDLINE|DRAWMODE_GHOSTEDFILL|DRAWMODE_GHOSTEDTEXT|DRAWMODE_GHOSTEDBITMAP|DRAWMODE_GHOSTEDGRADIENT));
/*?*/       }
/*N*/   }
/*N*/   else
/*N*/   {
/*N*/       // Darstellung normal
/*N*/       rXOut.GetOutDev()->SetDrawMode(rInfoRec.nOriginalDrawMode);
/*N*/   }
/*N*/
/*N*/   bOk = Paint(rXOut, rInfoRec, bRestoreColors, IMP_PAGEPAINT_NORMAL);
/*N*/
/*N*/   if(bIsEnteredGroup && bWasNotActive)
/*N*/   {
/*?*/       // Zurueck auf Ursprung, Zustand wieder verlassen
/*?*/       ((SdrPaintInfoRec&)rInfoRec).bNotActive = TRUE;
/*N*/   }
/*N*/
/*N*/   // Darstellung restaurieren
/*N*/   rXOut.GetOutDev()->SetDrawMode(nWasDrawMode);
/*N*/
/*N*/   return bOk;
/*N*/ }

/*N*/ FASTBOOL SdrObjList::Paint(ExtOutputDevice& rXOut, const SdrPaintInfoRec& rInfoRec, FASTBOOL bRestoreColors, USHORT nImpMode) const
/*N*/ {
/*N*/   FASTBOOL bOk=TRUE;
/*N*/   FASTBOOL bBrk=FALSE;
/*N*/   ULONG nObjAnz=GetObjCount();
/*N*/   if (nObjAnz==0) return TRUE;
/*N*/   USHORT nEvent=rInfoRec.nBrkEvent;
/*N*/   const SetOfByte* pVisiLayer=&rInfoRec.aPaintLayer;
/*N*/   FASTBOOL bPrinter=rInfoRec.bPrinter;
/*N*/   OutputDevice* pOut=rXOut.GetOutDev();
/*N*/   Rectangle aCheckRect(rInfoRec.aCheckRect);
/*N*/   FASTBOOL bDrawAll=aCheckRect.IsEmpty();
/*N*/   ImpSdrHdcMerk aHDCMerk(*pOut,SDRHDC_SAVEPENANDBRUSHANDFONT,bRestoreColors);
/*N*/   FASTBOOL bColorsDirty=FALSE;
/*N*/   if (bDrawAll || aCheckRect.IsOver(GetAllObjBoundRect())) {
/*N*/       Application* pAppPtr=NULL;
/*N*/       if (nEvent!=0) pAppPtr=GetpApp();
/*N*/       SetOfByte aPaintLayer(*pVisiLayer);
/*N*/       USHORT nPaintCycles = 1;
/*N*/       SdrLayerID nLayerId = 0;
/*N*/
/*N*/       // #85670# if pModel is NULL, try to get model of list owner
/*N*/       SdrModel *pLocalModel = pModel;
/*N*/       if(!pLocalModel && GetOwnerObj())
/*N*/           pLocalModel = GetOwnerObj()->GetModel();
/*N*/
/*N*/       // #85670# use correct model to get layer ID
/*N*/       if(pLocalModel)
/*N*/       {
/*N*/           const SdrLayerAdmin& rLayerAdmin = pLocalModel->GetLayerAdmin();
/*N*/           nLayerId = rLayerAdmin.GetLayerID(rLayerAdmin.GetControlLayerName(), FALSE);
/*N*/       }
/*N*/
/*N*/       if( pPage == NULL || ( !pPage->IsMasterPage() && aPaintLayer.IsSet( nLayerId ) ) )
/*N*/       {
/*N*/           // Der ControlLayer soll gezeichnet werden
/*N*/           // Wenn Controls existieren, wird der ControlLayer als letztes gezeichnet
/*N*/           SetOfByte aTestLayerSet = aPaintLayer;
/*N*/           aTestLayerSet.Clear(nLayerId);
/*N*/
/*N*/           if (!aTestLayerSet.IsEmpty())
/*N*/           {
/*N*/               // Es soll nicht nur der ControlLayer gezeichnet werden
/*N*/               ULONG nObjNum=0;
/*N*/               while (nObjNum<nObjAnz && nPaintCycles < 2)
/*N*/               {
/*N*/                   if (GetObj(nObjNum)->GetLayer() == nLayerId)
/*N*/                   {
/*N*/                       // Objekt auf ControlLayer gefunden
/*?*/                       // Der ControlLayer wird ersteinmal unsichtbar geschaltet
/*?*/                       nPaintCycles = 2;
/*?*/                       aPaintLayer.Clear(nLayerId);
/*N*/                   }
/*N*/
/*N*/                   nObjNum++;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/
/*N*/       for (USHORT nCycle = 1; nCycle <= nPaintCycles; nCycle++)
/*N*/       {
/*N*/           USHORT      nPaintImpMode = nImpMode;
/*N*/           FASTBOOL    bNormal = ( nPaintImpMode == IMP_PAGEPAINT_NORMAL );
/*N*/           FASTBOOL    bCachePrepare = ( nPaintImpMode == IMP_PAGEPAINT_PREPARE_CACHE );
/*N*/           FASTBOOL    bBGCachePrepare = ( nPaintImpMode == IMP_PAGEPAINT_PREPARE_BG_CACHE );
/*N*/           FASTBOOL    bCachePaint = ( nPaintImpMode == IMP_PAGEPAINT_PAINT_CACHE );
/*N*/           FASTBOOL    bBGCachePaint = ( nPaintImpMode == IMP_PAGEPAINT_PAINT_BG_CACHE );
/*N*/           FASTBOOL    bPaintFlag = ( bNormal || bCachePrepare || bBGCachePrepare );
/*N*/
/*N*/           if( nCycle == 2 )
/*N*/           {
/*N*/               // Im zweiten Durchgang nur den ControlLayer zeichnen
/*?*/               aPaintLayer.ClearAll();
/*?*/               aPaintLayer.Set(nLayerId);
/*N*/           }
/*N*/
/*N*/           ULONG nObjNum = 0UL;
/*N*/
/*N*/           while( ( nObjNum < nObjAnz ) && !bBrk )
/*N*/           {
/*N*/               SdrObject* pObj = GetObj( nObjNum );
/*N*/
/*N*/               if( nObjNum == 0 && eListKind == SDROBJLIST_MASTERPAGE &&
/*N*/                   pPage && pPage->IsMasterPage() && rInfoRec.pPV )
/*N*/               {
/*?*/                   // painting pages background obj instead of masterpages background obj
/*?*/                   SdrPage* pPg = rInfoRec.pPV->GetPage();
/*?*/                   SdrObject* pBackgroundObj = pPg ? pPg->GetBackgroundObj() : NULL;
/*?*/                   if( pBackgroundObj )
/*?*/                   {
/*?*/                       if( rXOut.GetOutDev()->GetDrawMode() == DRAWMODE_DEFAULT )
/*?*/                       {
/*?*/                           pObj = pBackgroundObj;
/*?*/                           Point aPos ( pPage->GetLftBorder(), pPage->GetUppBorder() );
/*?*/                           Size aSize ( pPage->GetSize() );
/*?*/                           aSize.Width()  -= pPage->GetLftBorder() + pPage->GetRgtBorder() - 1;
/*?*/                           aSize.Height() -= pPage->GetUppBorder() + pPage->GetLwrBorder() - 1;
/*?*/                           Rectangle aLogicRect( aPos, aSize );
/*?*/
/*?*/                           if( pBackgroundObj->GetLogicRect() != aLogicRect )
/*?*/                           {
/*?*/                               pBackgroundObj->SetLogicRect( aLogicRect );
/*?*/                               pBackgroundObj->RecalcBoundRect();
/*?*/                           }
/*?*/                       }
/*?*/                       else
/*?*/                           pObj = NULL;
/*?*/
/*?*/                   }
/*N*/               }

/*N*/               if( pObj && ( bDrawAll || aCheckRect.IsOver( pObj->GetBoundRect() ) ) )
/*N*/               {
/*N*/                   SdrObjList* pSubList = pObj->GetSubList();
/*N*/
/*N*/                   // Gruppenobjekte beruecksichtigen sichtbare Layer selbst (Ansonsten nur Painten, wenn Layer sichtbar)
/*N*/                   if( pSubList!=NULL || ((!bPrinter || pObj->IsPrintable()) && aPaintLayer.IsSet(pObj->GetLayer())) )
/*N*/                   {
/*N*/                       // #108937#
/*N*/                       // IsMasterCachable() does not visit groups automatically. Since
/*N*/                       // this mechanism should be changed to set information at the page
/*N*/                       // (counter?) later, i will fix that with a SdrObjListIter here.
/*N*/                       sal_Bool bHierarchyIsMasterPageCachable(pObj->IsMasterCachable());
/*N*/
/*N*/                       if(bHierarchyIsMasterPageCachable && pObj->IsGroupObject())
/*N*/                       {
/*N*/                           SdrObjListIter aIter(*pObj, IM_DEEPNOGROUPS);
/*N*/
/*N*/                           while(bHierarchyIsMasterPageCachable && aIter.IsMore())
/*N*/                           {
/*N*/                               SdrObject* pNestedObj = aIter.Next();
/*N*/
/*N*/                               if(!pNestedObj->IsMasterCachable())
/*N*/                               {
/*N*/                                   bHierarchyIsMasterPageCachable = sal_False;
/*N*/                               }
/*N*/                           }
/*N*/                       }
/*N*/
/*N*/                       if( !bNormal && !bHierarchyIsMasterPageCachable)
/*N*/                       {
/*?*/                           if( bCachePrepare || bBGCachePrepare )
/*?*/                               bBrk = TRUE, bPaintFlag = FALSE;
/*?*/                           else if( bCachePaint || bBGCachePaint )
/*?*/                           {
/*?*/                               bPaintFlag = bNormal = TRUE;
/*N*/                           }
/*N*/                       }
/*N*/
/*N*/                       if( bPaintFlag )
/*N*/                       {
/*N*/                           if( pObj->IsNeedColorRestore() )
/*?*/                           {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/                                if (bColorsDirty && bRestoreColors)
//STRIP001 /*?*/                                    aHDCMerk.Restore(*pOut);
//STRIP001 /*?*/
//STRIP001 /*?*/                                bColorsDirty=FALSE;
/*N*/                           }
/*N*/                           else
/*N*/                               bColorsDirty=TRUE; // andere aendern die Farben
/*N*/
/*N*/                           if( rInfoRec.pPaintProc!=NULL )
/*N*/                           {
/*?*/                               SdrPaintProcRec aRec(pObj,rXOut,rInfoRec);
/*?*/                               Link aLink(*rInfoRec.pPaintProc);
/*?*/                               aLink.Call(&aRec); // sollte mal 'nen ReturnCode liefern
/*N*/                           }
/*N*/                           else
/*N*/                           {
/*N*/                               bOk=pObj->Paint(rXOut,rInfoRec);

//////////////////////////////////////////////////////////////////////////////
//
//  Vector2D aTRScale;
//  double fTRShear;
//  double fTRRotate;
//  Vector2D aTRTranslate;
//  Matrix3D aOrigMat;
//  XPolyPolygon aTRPolyPolygon;
//
//  BOOL bIsPath = pObj->TRGetBaseGeometry(aOrigMat, aTRPolyPolygon);
//  aOrigMat.DecomposeAndCorrect(aTRScale, fTRShear, fTRRotate, aTRTranslate);
//  Vector2D aVectorTranslate;
//  aVectorTranslate.X() = FRound(aTRTranslate.X());
//  aVectorTranslate.Y() = FRound(aTRTranslate.Y());
//
//  Point aPoint(aVectorTranslate.X(), aVectorTranslate.Y());
//  Rectangle aTRBaseRect(
//      aPoint,
//      Size(FRound(aTRScale.X()), FRound(aTRScale.Y())));
//
//  Color aLineColorMerk(rXOut.GetOutDev()->GetLineColor());
//  Color aFillColorMerk(rXOut.GetOutDev()->GetFillColor());
//  rXOut.GetOutDev()->SetFillColor();
//
//  rXOut.GetOutDev()->SetLineColor(COL_BLACK);
//  rXOut.GetOutDev()->DrawRect(aTRBaseRect);
//
//  if(bIsPath)
//  {
//      rXOut.GetOutDev()->SetLineColor(COL_LIGHTRED);
//      XPolyPolygon aTRPoPo(aTRPolyPolygon);
//      aTRPoPo.Move(aTRBaseRect.Left(), aTRBaseRect.Top());
//      sal_uInt16 nCount(aTRPoPo.Count());
//      for(sal_uInt16 a(0); a < nCount; a++)
//          rXOut.GetOutDev()->DrawPolygon(XOutCreatePolygon(aTRPoPo[a], rXOut.GetOutDev()));
//  }
//
//  rXOut.GetOutDev()->SetLineColor(aLineColorMerk);
//  rXOut.GetOutDev()->SetFillColor(aFillColorMerk);
//
//  static BOOL bDoTestSetAllGeometry(FALSE);
//  if(bDoTestSetAllGeometry)
//      pObj->TRSetBaseGeometry(aOrigMat, aTRPolyPolygon);
//
//
//////////////////////////////////////////////////////////////////////////////
/*N*/                           }
/*N*/
/*N*/                           // nach dem ersten Objekt bei reinem Hintergrundcache
/*N*/                           // sollen die folgenden Objekte natuerlich nicht gezeichnet werden
/*N*/                           if( bBGCachePrepare )
/*N*/                               bPaintFlag = FALSE;
/*N*/                       }
/*N*/                       else if( bBGCachePaint )
/*N*/                           bPaintFlag = TRUE;
/*N*/                   }
/*N*/
/*N*/                   if( bOk && nEvent != 0 )
/*?*/                       bOk = !pAppPtr->AnyInput( nEvent );
/*N*/
/*N*/                   if( !bOk )
/*N*/                       bBrk = TRUE;
/*N*/               }
/*N*/               nObjNum++;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if (bColorsDirty && bRestoreColors)
/*N*/       aHDCMerk.Restore(*pOut);
/*N*/
/*N*/   return bOk;
/*N*/ }

//STRIP001 SdrObject* SdrObjList::CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer, FASTBOOL bBackward) const
//STRIP001 {
//STRIP001  SdrObject* pHit=NULL;
//STRIP001  Rectangle R(rPnt.X()-nTol,rPnt.Y()-nTol,rPnt.X()+nTol,rPnt.Y()+nTol);
//STRIP001  if (R.IsOver(GetAllObjBoundRect())) {
//STRIP001      ULONG nObjAnz=GetObjCount();
//STRIP001      ULONG nObjNum=bBackward ? 0 : nObjAnz;
//STRIP001      while (pHit==NULL && (bBackward ? nObjNum<nObjAnz : nObjNum>0)) {
//STRIP001          if (!bBackward) nObjNum--;
//STRIP001          SdrObject* pObj=GetObj(nObjNum);
//STRIP001          if (R.IsOver(pObj->GetBoundRect())) {
//STRIP001              SdrObjList* pSubList=pObj->GetSubList();
//STRIP001              if (pSubList!=NULL || pVisiLayer==NULL) { // Gruppenobjekte beruecksichtigen sichtbare Layer selbst
//STRIP001                  pHit=pObj->CheckHit(rPnt,nTol,pVisiLayer/*,bBackward*/);
//STRIP001              } else {             // Ansonsten nur wenn Layer sichtbar
//STRIP001                  SdrLayerID nLayer=pObj->GetLayer();
//STRIP001                  if (pVisiLayer->IsSet(nLayer)) {
//STRIP001                      pHit=pObj->CheckHit(rPnt,nTol,pVisiLayer/*,bBackward*/);
//STRIP001                  }
//STRIP001              }
//STRIP001          }
//STRIP001          if (bBackward) nObjNum++;
//STRIP001      }
//STRIP001  }
//STRIP001  return pHit;
//STRIP001 }

//STRIP001 void SdrObjList::NbcReformatAllTextObjects()
//STRIP001 {
//STRIP001  ULONG nAnz=GetObjCount();
//STRIP001  ULONG nNum=0;
//STRIP001
//STRIP001  Printer* pPrinter = NULL;
//STRIP001
//STRIP001  if (pModel)
//STRIP001  {
//STRIP001      if (pModel->GetRefDevice() && pModel->GetRefDevice()->GetOutDevType() == OUTDEV_PRINTER)
//STRIP001      {
//STRIP001          // Kein RefDevice oder RefDevice kein Printer
//STRIP001          pPrinter = (Printer*) pModel->GetRefDevice();
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  while (nNum<nAnz)
//STRIP001  {
//STRIP001      SdrObject* pObj = GetObj(nNum);
//STRIP001 #ifndef SVX_LIGHT
//STRIP001      if (pPrinter &&
//STRIP001          pObj->GetObjInventor() == SdrInventor &&
//STRIP001          pObj->GetObjIdentifier() == OBJ_OLE2  &&
//STRIP001          !( (SdrOle2Obj*) pObj )->IsEmpty() )
//STRIP001      {
//STRIP001          const SvInPlaceObjectRef& xObjRef = ((SdrOle2Obj*) pObj)->GetObjRef();
//STRIP001
//STRIP001          if( xObjRef.Is() && ( xObjRef->GetMiscStatus() & SVOBJ_MISCSTATUS_RESIZEONPRINTERCHANGE ) )
//STRIP001              xObjRef->OnDocumentPrinterChanged(pPrinter);
//STRIP001      }
//STRIP001 #endif
//STRIP001
//STRIP001      pObj->NbcReformatText();
//STRIP001      nAnz=GetObjCount();             // ReformatText may delete an object
//STRIP001      nNum++;
//STRIP001  }
//STRIP001
//STRIP001 }

/*N*/ void SdrObjList::ReformatAllTextObjects()
/*N*/ {
/*N*/   ULONG nAnz=GetObjCount();
/*N*/   ULONG nNum=0;
/*N*/
/*N*/   Printer* pPrinter = NULL;
/*N*/
/*N*/   if (pModel)
/*N*/   {
/*N*/       if (pModel->GetRefDevice() && pModel->GetRefDevice()->GetOutDevType() == OUTDEV_PRINTER)
/*N*/       {
/*N*/           // Kein RefDevice oder RefDevice kein Printer
/*N*/           pPrinter = (Printer*) pModel->GetRefDevice();
/*N*/       }
/*N*/   }
/*N*/
/*N*/   while (nNum<nAnz)
/*N*/   {
/*N*/       SdrObject* pObj = GetObj(nNum);
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/       if (pPrinter &&
/*N*/           pObj->GetObjInventor() == SdrInventor &&
/*N*/           pObj->GetObjIdentifier() == OBJ_OLE2  &&
/*N*/           !( (SdrOle2Obj*) pObj )->IsEmpty() )
/*N*/       {
/*?*/           const SvInPlaceObjectRef& xObjRef = ((SdrOle2Obj*) pObj)->GetObjRef();
/*?*/
/*?*/           if( xObjRef.Is() && ( xObjRef->GetMiscStatus() & SVOBJ_MISCSTATUS_RESIZEONPRINTERCHANGE ) )
/*?*/               xObjRef->OnDocumentPrinterChanged(pPrinter);
/*N*/       }
/*N*/ #endif
/*N*/
/*N*/       pObj->ReformatText();
/*N*/       nAnz=GetObjCount();             // ReformatText may delete an object
/*N*/       nNum++;
/*N*/   }
/*N*/ }

/** steps over all available objects and reformats all
    edge objects that are connected to other objects so that
    they may reposition itselfs.
    #103122#
*/
/*N*/ void SdrObjList::ReformatAllEdgeObjects()
/*N*/ {
/*N*/   const sal_uInt32 nCount=GetObjCount();
/*N*/   sal_uInt32 nObj;
/*N*/
/*N*/   for( nObj = 0; nObj < nCount; nObj++ )
/*N*/   {
/*N*/       SdrObject* pObj = GetObj(nObj);
/*N*/       if( pObj->ISA(SdrEdgeObj) )
/*N*/           static_cast<SdrEdgeObj*>(pObj)->Reformat();
/*N*/   }
/*N*/ }

//STRIP001 void SdrObjList::BurnInStyleSheetAttributes( BOOL bPseudoSheetsOnly )
//STRIP001 {
//STRIP001  ULONG nAnz=GetObjCount();
//STRIP001  ULONG nNum=0;
//STRIP001  while (nNum<nAnz)
//STRIP001  {
//STRIP001      SdrObject* pObj = GetObj(nNum);
//STRIP001      if( pObj->ISA( SdrAttrObj ) && !pObj->ISA( E3dPolyScene ) )
//STRIP001          ( (SdrAttrObj*) pObj )->BurnInStyleSheetAttributes( bPseudoSheetsOnly );
//STRIP001      else if( pObj->ISA( SdrObjGroup ) )
//STRIP001          ( (SdrObjGroup*) pObj )->BurnInStyleSheetAttributes( bPseudoSheetsOnly );
//STRIP001
//STRIP001      nNum++;
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrObjList::RemoveNotPersistentObjects(FASTBOOL bNoBroadcast)
//STRIP001 {
//STRIP001  FASTBOOL bNoOLE=pModel!=NULL && pModel->IsStreamingSdrModel();
//STRIP001  ULONG nObjAnz=GetObjCount();
//STRIP001  for (ULONG nObjNum=nObjAnz; nObjNum>0;) {
//STRIP001      nObjNum--;
//STRIP001      SdrObject* pObj=GetObj(nObjNum);
//STRIP001      FASTBOOL bThisObjNot=pObj->IsNotPersistent();
//STRIP001      if (!bThisObjNot && bNoOLE && pObj->ISA(SdrOle2Obj)) {
//STRIP001          bThisObjNot=TRUE;
//STRIP001      }
//STRIP001      if (bThisObjNot) {
//STRIP001          if (bNoBroadcast) NbcRemoveObject(nObjNum);
//STRIP001          else RemoveObject(nObjNum);
//STRIP001      } else {
//STRIP001          SdrObjList* pOL=pObj->GetSubList();
//STRIP001          if (pOL!=NULL) {
//STRIP001              pOL->RemoveNotPersistentObjects(bNoBroadcast);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*N*/ void SdrObjList::RestartAllAnimations(SdrPageView* pPageView) const
/*N*/ {
/*N*/   ULONG nAnz=GetObjCount();
/*N*/   ULONG nNum=0;
/*N*/   while (nNum<nAnz) {
/*N*/       GetObj(nNum)->RestartAnimation(pPageView);
/*N*/       nNum++;
/*N*/   }
/*N*/ }

/*?*/ FASTBOOL SdrObjList::ImpGetFillColor(SdrObject* pObj, Color& rCol) const
/*?*/ {
/*?*/   return GetDraftFillColor(pObj->GetItemSet(),rCol);
/*?*/ }

//STRIP001 FASTBOOL SdrObjList::GetFillColor(const Point& rPnt, const SetOfByte& rVisLayers,
//STRIP001                                FASTBOOL bLayerSorted, Color& rCol) const
//STRIP001 {
//STRIP001  if (pModel==NULL) return FALSE;
//STRIP001  FASTBOOL bRet=FALSE;
//STRIP001  FASTBOOL bMaster=pPage!=NULL ? pPage->IsMasterPage() : FALSE;
//STRIP001  for (ULONG no=GetObjCount(); !bRet && no>0; ) {
//STRIP001      no--;
//STRIP001      SdrObject* pObj=GetObj(no);
//STRIP001      SdrObjList* pOL=pObj->GetSubList();
//STRIP001      if (pOL!=NULL) { // Aha, Gruppenobjekt
//STRIP001          bRet=pOL->GetFillColor(rPnt,rVisLayers,bLayerSorted,rCol);
//STRIP001      } else {
//STRIP001          SdrTextObj* pTextObj=PTR_CAST(SdrTextObj,pObj);
//STRIP001             // #108867# Exclude zero master page object (i.e. background
//STRIP001             // shape) from color query
//STRIP001          if (pTextObj!=NULL &&
//STRIP001              pObj->IsClosedObj() && rVisLayers.IsSet(pObj->GetLayer()) &&
//STRIP001              (!bMaster || (!pObj->IsNotVisibleAsMaster() && no!=0)) &&
//STRIP001              pObj->GetBoundRect().IsInside(rPnt) &&
//STRIP001              !pTextObj->IsHideContour() && pObj->IsHit(rPnt,0,NULL))
//STRIP001          {   // Nachfolgend extra Funktion um Stack zu sparen,
//STRIP001              // da diese Methode hier rekursiv ist.
//STRIP001              bRet=ImpGetFillColor(pObj,rCol);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return bRet;
//STRIP001 }


//STRIP001 FASTBOOL SdrObjList::IsReadOnly() const
//STRIP001 {
//STRIP001  FASTBOOL bRet=FALSE;
//STRIP001  if (pPage!=NULL && pPage!=this) bRet=pPage->IsReadOnly();
//STRIP001  return bRet;
//STRIP001 }

/*N*/ ULONG SdrObjList::CountAllObjects() const
/*N*/ {
/*N*/   ULONG nCnt=GetObjCount();
/*N*/   ULONG nAnz=nCnt;
/*N*/   for (USHORT nNum=0; nNum<nAnz; nNum++) {
/*N*/       SdrObjList* pSubOL=GetObj(nNum)->GetSubList();
/*N*/       if (pSubOL!=NULL) {
/*N*/           nCnt+=pSubOL->CountAllObjects();
/*N*/       }
/*N*/   }
/*N*/   return nCnt;
/*N*/ }

//STRIP001 void SdrObjList::ForceSwapInObjects() const
//STRIP001 {
//STRIP001  ULONG nObjAnz=GetObjCount();
//STRIP001  for (ULONG nObjNum=nObjAnz; nObjNum>0;) {
//STRIP001      SdrObject* pObj=GetObj(--nObjNum);
//STRIP001      SdrGrafObj* pGrafObj=PTR_CAST(SdrGrafObj,pObj);
//STRIP001      if (pGrafObj!=NULL) {
//STRIP001          pGrafObj->ForceSwapIn();
//STRIP001      }
//STRIP001      SdrObjList* pOL=pObj->GetSubList();
//STRIP001      if (pOL!=NULL) {
//STRIP001          pOL->ForceSwapInObjects();
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrObjList::ForceSwapOutObjects() const
//STRIP001 {
//STRIP001  ULONG nObjAnz=GetObjCount();
//STRIP001  for (ULONG nObjNum=nObjAnz; nObjNum>0;) {
//STRIP001      SdrObject* pObj=GetObj(--nObjNum);
//STRIP001      SdrGrafObj* pGrafObj=PTR_CAST(SdrGrafObj,pObj);
//STRIP001      if (pGrafObj!=NULL) {
//STRIP001          pGrafObj->ForceSwapOut();
//STRIP001      }
//STRIP001      SdrObjList* pOL=pObj->GetSubList();
//STRIP001      if (pOL!=NULL) {
//STRIP001          pOL->ForceSwapOutObjects();
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*N*/ void SdrObjList::Save(SvStream& rOut) const
/*N*/ {
/*N*/   FASTBOOL bNotPersist=pPage!=NULL && pPage->IsObjectsNotPersistent();
/*N*/   FASTBOOL bNoOLE=pModel!=NULL && pModel->IsStreamingSdrModel();
/*N*/   if (!bNotPersist) {
/*N*/       SdrObjListIter aIter(*this,IM_FLAT);
/*N*/       while (aIter.IsMore()) {
/*N*/           SdrObject* pObj=aIter.Next();
/*N*/           FASTBOOL bThisObjNot=pObj->IsNotPersistent();
/*N*/           if (!bThisObjNot && bNoOLE && pObj->ISA(SdrOle2Obj)) {
/*N*/               bThisObjNot=TRUE;
/*N*/           }
/*N*/           if (!bThisObjNot) rOut<<*pObj;
/*N*/           if (pModel!=NULL) pModel->IncProgress();
/*N*/       }
/*N*/   }
/*N*/   SdrIOHeader(rOut,STREAM_WRITE,SdrIOEndeID); // Endemarke
/*N*/ }

/*N*/ void SdrObjList::Load(SvStream& rIn, SdrPage& rPage)
/*N*/ {
/*N*/   Clear();
/*N*/
/*N*/   if (rIn.GetError()!=0)
/*N*/       return;
/*N*/
/*N*/   SdrInsertReason aReason(SDRREASON_STREAMING);
/*N*/   FASTBOOL        bEnde=FALSE;
/*N*/
/*N*/   while( rIn.GetError()==0 && !rIn.IsEof() && !bEnde )
/*N*/   {
/*N*/       SdrObjIOHeaderLookAhead aHead(rIn,STREAM_READ);
/*N*/
/*N*/       if (!aHead.IsEnde())
/*N*/       {
/*N*/           SdrObject* pObj=SdrObjFactory::MakeNewObject(aHead.nInventor,aHead.nIdentifier,&rPage);
/*N*/
/*N*/           if( pObj!=NULL )
/*N*/           {
/*N*/               rIn >> *pObj;
/*N*/
/*N*/ #ifndef SVX_LIGHT
/*N*/               if( ( pObj->GetObjIdentifier() == OBJ_OLE2 ) && ( pObj->GetObjInventor() == SdrInventor ) )
/*N*/               {
/*N*/                   // convert StarImage OLE objects to normal graphic objects
/*N*/                   SdrOle2Obj* pOLEObj = (SdrOle2Obj*) pObj;
/*N*/                   BOOL        bImageOLE = FALSE;
/*N*/
/*N*/                   if( pOLEObj->GetProgName() == String( RTL_CONSTASCII_USTRINGPARAM( "StarImage" ) ) )
/*N*/                       bImageOLE = TRUE;
/*N*/                   else if( pModel->GetPersist() )
/*N*/                   {
/*N*/                       SvInfoObjectRef     xInfo( pModel->GetPersist()->Find( pOLEObj->GetPersistName() ) );
/*N*/                       const SvGlobalName  aSim30Name( BF_SO3_SIM_CLASSID_30 );
/*N*/                       const SvGlobalName  aSim40Name( BF_SO3_SIM_CLASSID_40 );
/*N*/                       const SvGlobalName  aSim50Name( BF_SO3_SIM_CLASSID_50 );
/*N*/
/*N*/                       if( xInfo.Is() &&
/*N*/                           ( xInfo->GetClassName() == aSim30Name ||
/*N*/                             xInfo->GetClassName() == aSim40Name ||
/*N*/                             xInfo->GetClassName() == aSim50Name ) )
/*N*/                       {
/*N*/                           bImageOLE = TRUE;
/*N*/                       }
/*N*/                   }
/*N*/
/*N*/                   if( bImageOLE && pOLEObj->GetPersistName().Len() )
/*N*/                   {
/*?*/                       SotStorage*     pModelStorage = pModel->GetModelStorage();
/*?*/                       const String    aSimStorageName( pOLEObj->GetPersistName() );
/*?*/
/*?*/                       if( pModelStorage && pModelStorage->IsStorage( aSimStorageName ) )
/*?*/                       {
/*?*/                           SotStorageRef xSimStorage( pModelStorage->OpenSotStorage( aSimStorageName ) );
/*?*/
/*?*/                           if( xSimStorage.Is() )
/*?*/                           {
/*?*/                               String aStmName( RTL_CONSTASCII_USTRINGPARAM( "StarImageDocument" ) );
/*?*/
/*?*/                               if( xSimStorage->IsStream( aStmName ) ||
/*?*/                                   xSimStorage->IsStream( aStmName = String( RTL_CONSTASCII_USTRINGPARAM( "StarImageDocument 4.0" ) ) ) )
/*?*/                               {
/*?*/                                   SotStorageStreamRef xSimStm( xSimStorage->OpenSotStream( aStmName ) );
/*?*/
/*?*/                                   if( xSimStm.Is() && !xSimStm->GetError() )
/*?*/                                   {
/*?*/                                       Graphic aGraphic;
/*?*/
/*?*/                                       xSimStm->SetBufferSize( 32768 );
/*?*/                                       xSimStm->SetKey( xSimStorage->GetKey() );
/*?*/                                       *xSimStm >> aGraphic;
/*?*/                                       xSimStm->SetBufferSize( 0 );
/*?*/
/*?*/                                       SdrGrafObj* pNewObj = (SdrGrafObj*) SdrObjFactory::MakeNewObject( SdrInventor, OBJ_GRAF, &rPage );
/*?*/
/*?*/                                       if( pNewObj )
/*?*/                                       {
/*?*/                                           pNewObj->SetGraphic( aGraphic );
/*?*/                                           pNewObj->SetLogicRect( pObj->GetLogicRect() );
/*?*/                                           delete pObj;
/*?*/                                           pObj = pNewObj;
/*?*/                                       }
/*?*/                                   }
/*?*/                               }
/*?*/                           }
/*?*/                       }
/*N*/                   }
/*N*/               }
#endif // SVX_LIGHT

/*N*/               InsertObject(pObj,CONTAINER_APPEND,&aReason);
/*N*/           }
/*N*/           else
/*N*/           { // aha, das wil keiner. Also ueberlesen.
/*N*/ #ifdef SVX_LIGHT
/*N*/               if( aHead.nInventor != FmFormInventor )
/*N*/               {
/*N*/ #endif
/*N*/
/*N*/ #ifdef DBG_UTIL
/*?*/               ByteString aStr("SdrObjList::Load(): Zeichenobjekt kann von der Factory nicht erzeugt werden:\n");
/*?*/               UINT32 nPos(GetObjCount());
/*?*/
/*?*/               aStr += "Listenposition: ";
/*?*/               aStr += ByteString::CreateFromInt32( nPos );
/*?*/               aStr += "\n";
/*?*/               aStr += "Inventor: ";
/*?*/                 sal_Int32 nInv = SWAPLONG( aHead.nInventor );
/*?*/                 aStr += ByteString::CreateFromInt32( nInv );
/*?*/               aStr += ", Identifier: ";
/*?*/               aStr += ByteString::CreateFromInt32( aHead.nIdentifier );
/*?*/               aStr += "\n";
/*?*/               aStr += "FilePos: ";
/*?*/               aStr += ByteString::CreateFromInt32( aHead.GetFilePos() );
/*?*/               aStr += ", BlockSize: ";
/*?*/               aStr += ByteString::CreateFromInt32( aHead.GetBlockSize() );
/*?*/
/*?*/               DBG_ERROR(aStr.GetBuffer());
/*?*/ #endif
/*?*/
/*?*/ #ifdef SVX_LIGHT
/*?*/               }
/*?*/ #endif
/*?*/               aHead.SkipRecord();
/*?*/           }
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           bEnde=TRUE;
/*N*/           aHead.SkipRecord(); // die Endemarke weglesen
/*N*/       }
/*N*/
/*N*/       SdrModel* pMd=pModel;
/*N*/
/*N*/       if (pMd==NULL)
/*N*/           pMd=rPage.GetModel();
/*N*/
/*N*/       if (pMd!=NULL)
/*N*/           pMd->DoProgress(rIn.Tell());
/*N*/   }
/*N*/ }

/*N*/ void SdrObjList::AfterRead()
/*N*/ {
/*N*/   ULONG nAnz=GetObjCount();
/*N*/   for (ULONG i=0; i<nAnz; i++) {
/*N*/       GetObj(i)->AfterRead();
/*N*/   }
/*N*/ }

/*?*/ void SdrObjList::FlattenGroups()
/*?*/ {DBG_BF_ASSERT(0, "STRIP");//STRIP001
//STRIP001     sal_Int32 nObj = GetObjCount();
//STRIP001     sal_Int32 i;
//STRIP001     for( i=nObj-1; i>=0; --i)
//STRIP001         UnGroupObj(i);
/*?*/ }

/*?*/ void SdrObjList::UnGroupObj( ULONG nObjNum )
/*?*/ {DBG_BF_ASSERT(0, "STRIP");//STRIP001
//STRIP001     // if the given object is no group, this method is a noop
//STRIP001     SdrObject* pUngroupObj = GetObj( nObjNum );
//STRIP001     if( pUngroupObj )
//STRIP001     {
//STRIP001         SdrObjList* pSrcLst = pUngroupObj->GetSubList();
//STRIP001         sal_Int32 nCount( 0 );
//STRIP001         if( pUngroupObj->ISA( SdrObjGroup ) && pSrcLst )
//STRIP001         {
//STRIP001             SdrObjGroup* pUngroupGroup = static_cast< SdrObjGroup* > (pUngroupObj);
//STRIP001
//STRIP001             // ungroup recursively (has to be head recursion,
//STRIP001             // otherwise our indices will get trashed when doing it in
//STRIP001             // the loop)
//STRIP001             pSrcLst->FlattenGroups();
//STRIP001
//STRIP001             // the position at which we insert the members of rUngroupGroup
//STRIP001             sal_Int32 nInsertPos( pUngroupGroup->GetOrdNum() );
//STRIP001
//STRIP001             SdrObject* pObj;
//STRIP001             sal_Int32 i, nAnz = pSrcLst->GetObjCount();
//STRIP001             for( i=0; i<nAnz; ++i )
//STRIP001             {
//STRIP001                 pObj = pSrcLst->RemoveObject(0);
//STRIP001                 SdrInsertReason aReason(SDRREASON_VIEWCALL, pUngroupGroup);
//STRIP001                 InsertObject(pObj, nInsertPos, &aReason);
//STRIP001                 ++nInsertPos;
//STRIP001             }
//STRIP001
//STRIP001             RemoveObject(nInsertPos);
//STRIP001         }
//STRIP001     }
//STRIP001 #ifdef DBG_UTIL
//STRIP001     else
//STRIP001         DBG_ERROR("SdrObjList::UnGroupObj: object index invalid");
//STRIP001 #endif
/*?*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SvStream& operator<<(SvStream& rOut, const SdrMasterPageDescriptor& rMDP)
/*N*/ {
/*N*/   SdrIOHeader aHead(rOut,STREAM_WRITE,SdrIOMPgDID);
/*N*/   rOut<<rMDP.nPgNum;
/*N*/   rOut<<rMDP.aVisLayers;
/*N*/   return rOut;
/*N*/ }

/*N*/ SvStream& operator>>(SvStream& rIn, SdrMasterPageDescriptor& rMDP)
/*N*/ {
/*N*/   if (rIn.GetError()!=0) return rIn;
/*N*/   SdrIOHeader aHead(rIn,STREAM_READ);
/*N*/   rIn>>rMDP.nPgNum;
/*N*/   rIn>>rMDP.aVisLayers;
/*N*/   return rIn;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrMasterPageDescriptorList::Clear()
/*N*/ {
/*N*/   USHORT nAnz=GetCount();
/*N*/   for (USHORT i=0; i<nAnz; i++) {
/*N*/       delete GetObject(i);
/*N*/   }
/*N*/   aList.Clear();
/*N*/ }

//STRIP001 void SdrMasterPageDescriptorList::operator=(const SdrMasterPageDescriptorList& rSrcList)
//STRIP001 {
//STRIP001  Clear();
//STRIP001  USHORT nAnz=rSrcList.GetCount();
//STRIP001  for (USHORT i=0; i<nAnz; i++) {
//STRIP001      Insert(rSrcList[i]);
//STRIP001  }
//STRIP001 }

/*N*/ SvStream& operator<<(SvStream& rOut, const SdrMasterPageDescriptorList& rMPDL)
/*N*/ {
/*N*/   SdrIOHeader aHead(rOut,STREAM_WRITE,SdrIOMPDLID);
/*N*/   USHORT nAnz=rMPDL.GetCount();
/*N*/   rOut<<nAnz;
/*N*/   for (USHORT i=0; i<nAnz; i++) {
/*N*/       rOut<<rMPDL[i];
/*N*/   }
/*N*/   return rOut;
/*N*/ }

/*N*/ SvStream& operator>>(SvStream& rIn, SdrMasterPageDescriptorList& rMPDL)
/*N*/ {
/*N*/   if (rIn.GetError()!=0) return rIn;
/*N*/   SdrIOHeader aHead(rIn,STREAM_READ);
/*N*/   rMPDL.Clear();
/*N*/   USHORT nAnz;
/*N*/   rIn>>nAnz;
/*N*/   for (USHORT i=0; i<nAnz; i++) {
/*N*/       SdrMasterPageDescriptor* pMPD=new SdrMasterPageDescriptor;
/*N*/       rIn>>*pMPD;
/*N*/       rMPDL.aList.Insert(pMPD,CONTAINER_APPEND);
/*N*/   }
/*N*/   return rIn;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrPageGridFrameList::Clear()
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  USHORT nAnz=GetCount();
//STRIP001  for (USHORT i=0; i<nAnz; i++) {
//STRIP001      delete GetObject(i);
//STRIP001  }
//STRIP001  aList.Clear();
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ TYPEINIT1(SdrPage,SdrObjList);

/*N*/ SdrPage::SdrPage(SdrModel& rNewModel, FASTBOOL bMasterPage):
/*N*/   SdrObjList(&rNewModel,this),
/*N*/   pBackgroundObj( NULL )
/*N*/ {
/*N*/   pLayerAdmin=new SdrLayerAdmin(&rNewModel.GetLayerAdmin());
/*N*/   bMaster=bMasterPage;
/*N*/   bInserted=FALSE;
/*N*/   aPrefVisiLayers.SetAll();
/*N*/   nWdt=10;
/*N*/   nHgt=10;
/*N*/   nBordLft=0;
/*N*/   nBordUpp=0;
/*N*/   nBordRgt=0;
/*N*/   nBordLwr=0;
/*N*/   nPageNum=0;
/*N*/   eListKind=bMasterPage ? SDROBJLIST_MASTERPAGE : SDROBJLIST_DRAWPAGE;
/*N*/   bSwappingLocked=FALSE;
/*N*/   bObjectsNotPersistent=FALSE;
/*N*/ }

/*?*/ SdrPage::SdrPage(const SdrPage& rSrcPage):
/*?*/   SdrObjList(rSrcPage.pModel,this),
/*?*/   pBackgroundObj( NULL )
/*?*/ {
/*?*/   pLayerAdmin=new SdrLayerAdmin(rSrcPage.pModel->GetLayerAdmin());
/*?*/   *this=rSrcPage;
/*?*/   eListKind=bMaster ? SDROBJLIST_MASTERPAGE : SDROBJLIST_DRAWPAGE;
/*?*/ }

/*N*/ SdrPage::~SdrPage()
/*N*/ {
/*N*/   delete pBackgroundObj;
/*N*/   delete pLayerAdmin;
/*N*/ }

//STRIP001 void SdrPage::operator=(const SdrPage& rSrcPage)
//STRIP001 {
//STRIP001  SdrObjList::operator=(rSrcPage);
//STRIP001  pPage=this;
//STRIP001  bMaster        =rSrcPage.bMaster        ;
//STRIP001  bSwappingLocked=rSrcPage.bSwappingLocked;
//STRIP001  aPrefVisiLayers=rSrcPage.aPrefVisiLayers;
//STRIP001  nWdt           =rSrcPage.nWdt           ;
//STRIP001  nHgt           =rSrcPage.nHgt           ;
//STRIP001  nBordLft       =rSrcPage.nBordLft       ;
//STRIP001  nBordUpp       =rSrcPage.nBordUpp       ;
//STRIP001  nBordRgt       =rSrcPage.nBordRgt       ;
//STRIP001  nBordLwr       =rSrcPage.nBordLwr       ;
//STRIP001  nPageNum       =rSrcPage.nPageNum       ;
//STRIP001  aMasters       =rSrcPage.aMasters       ;
//STRIP001  bObjectsNotPersistent=rSrcPage.bObjectsNotPersistent;
//STRIP001
//STRIP001  if( rSrcPage.pBackgroundObj )
//STRIP001  {
//STRIP001      pBackgroundObj = rSrcPage.pBackgroundObj->Clone();
//STRIP001      pBackgroundObj->SetPage( this );
//STRIP001      pBackgroundObj->SetModel( pModel );
//STRIP001  }
//STRIP001 }

//STRIP001 SdrPage* SdrPage::Clone() const
//STRIP001 {
//STRIP001  return Clone(NULL);
//STRIP001 }

//STRIP001 SdrPage* SdrPage::Clone(SdrModel* pNewModel) const
//STRIP001 {
//STRIP001  if (pNewModel==NULL) pNewModel=pModel;
//STRIP001  SdrPage* pPage=new SdrPage(*pNewModel);
//STRIP001  *pPage=*this;
//STRIP001  return pPage;
//STRIP001 }

//STRIP001 SfxItemPool& SdrPage::GetItemPool() const
//STRIP001 {
//STRIP001  return pModel->GetItemPool();
//STRIP001 }

/*N*/ void SdrPage::SetSize(const Size& aSiz)
/*N*/ {
/*N*/   nWdt=aSiz.Width();
/*N*/   nHgt=aSiz.Height();
/*N*/   if( pModel )
/*N*/       pModel->SetChanged();
/*N*/ }

/*N*/ Size SdrPage::GetSize() const
/*N*/ {
/*N*/   return Size(nWdt,nHgt);
/*N*/ }

/*N*/ INT32 SdrPage::GetWdt() const
/*N*/ {
/*N*/   return nWdt;
/*N*/ }

/*N*/ void SdrPage::SetOrientation(Orientation eOri)
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  // Quadratisch ist und bleibt immer Portrait
//STRIP001  Size aSiz(GetSize());
//STRIP001  if (aSiz.Width()!=aSiz.Height()) {
//STRIP001      if ((eOri==ORIENTATION_PORTRAIT) == (aSiz.Width()>aSiz.Height())) {
//STRIP001          SetSize(Size(aSiz.Height(),aSiz.Width()));
//STRIP001      }
//STRIP001  }
/*N*/ }

//STRIP001 Orientation SdrPage::GetOrientation() const
//STRIP001 {
//STRIP001  // Quadratisch ist Portrait
//STRIP001  Orientation eRet=ORIENTATION_PORTRAIT;
//STRIP001  Size aSiz(GetSize());
//STRIP001  if (aSiz.Width()>aSiz.Height()) eRet=ORIENTATION_LANDSCAPE;
//STRIP001  return eRet;
//STRIP001 }

/*N*/ INT32 SdrPage::GetHgt() const
/*N*/ {
/*N*/   return nHgt;
/*N*/ }

/*N*/ void  SdrPage::SetBorder(INT32 nLft, INT32 nUpp, INT32 nRgt, INT32 nLwr)
/*N*/ {
/*N*/   nBordLft=nLft;
/*N*/   nBordUpp=nUpp;
/*N*/   nBordRgt=nRgt;
/*N*/   nBordLwr=nLwr;
/*N*/   if( pModel )
/*N*/       pModel->SetChanged();
/*N*/ }

/*N*/ void  SdrPage::SetLftBorder(INT32 nBorder)
/*N*/ {
/*N*/   nBordLft=nBorder;
/*N*/   if( pModel )
/*N*/       pModel->SetChanged();
/*N*/ }

/*N*/ void  SdrPage::SetUppBorder(INT32 nBorder)
/*N*/ {
/*N*/   nBordUpp=nBorder;
/*N*/   if( pModel )
/*N*/       pModel->SetChanged();
/*N*/ }

/*N*/ void  SdrPage::SetRgtBorder(INT32 nBorder)
/*N*/ {
/*N*/   nBordRgt=nBorder;
/*N*/   if( pModel )
/*N*/       pModel->SetChanged();
/*N*/ }

/*N*/ void  SdrPage::SetLwrBorder(INT32 nBorder)
/*N*/ {
/*N*/   nBordLwr=nBorder;
/*N*/   if( pModel )
/*N*/       pModel->SetChanged();
/*N*/ }

/*N*/ INT32 SdrPage::GetLftBorder() const
/*N*/ {
/*N*/   return nBordLft;
/*N*/ }

/*N*/ INT32 SdrPage::GetUppBorder() const
/*N*/ {
/*N*/   return nBordUpp;
/*N*/ }

/*N*/ INT32 SdrPage::GetRgtBorder() const
/*N*/ {
/*N*/   return nBordRgt;
/*N*/ }

/*N*/ INT32 SdrPage::GetLwrBorder() const
/*N*/ {
/*N*/   return nBordLwr;
/*N*/ }

// #i3694#
// This GetOffset() method is not needed anymore, it even leads to errors.
//Point SdrPage::GetOffset() const
//{
//  return Point();
//}

/*N*/ void SdrPage::SetModel(SdrModel* pNewModel)
/*N*/ {
/*N*/   SdrModel* pOldModel=pModel;
/*N*/   SdrObjList::SetModel(pNewModel);
/*N*/   if (pNewModel!=pOldModel)
/*N*/   {
/*?*/       if (pNewModel!=NULL) {
/*?*/           pLayerAdmin->SetParent(&pNewModel->GetLayerAdmin());
/*?*/       } else {
/*?*/           pLayerAdmin->SetParent(NULL);
/*?*/       }
/*?*/       pLayerAdmin->SetModel(pNewModel);
/*?*/
/*?*/       if( pBackgroundObj )
/*?*/           pBackgroundObj->SetModel( pNewModel );
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ USHORT SdrPage::GetPageNum() const
/*N*/ {
/*N*/   if (!bInserted) return 0;
/*N*/   if (bMaster) {
/*N*/       if (pModel && pModel->IsMPgNumsDirty())
/*N*/           ((SdrModel*)pModel)->RecalcPageNums(TRUE);
/*N*/   } else {
/*N*/       if (pModel && pModel->IsPagNumsDirty())
/*N*/           ((SdrModel*)pModel)->RecalcPageNums(FALSE);
/*N*/   }
/*N*/   return nPageNum;
/*N*/ }

/*N*/ void SdrPage::SetChanged()
/*N*/ {
/*N*/   if( pModel )
/*N*/       pModel->SetChanged();
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrPage::SendRepaintBroadcast() const
/*N*/ {
/*N*/   if (bInserted && pModel!=NULL) pModel->Broadcast(SdrHint(*this));
/*N*/ }

//STRIP001 USHORT SdrPage::GetMasterPagePos(USHORT nPgNum) const
//STRIP001 {
//STRIP001  USHORT nAnz=aMasters.GetCount();
//STRIP001  for (USHORT i=0; i<nAnz; i++) {
//STRIP001      USHORT nMaPgNum=aMasters[i].GetPageNum();
//STRIP001      if (nMaPgNum==nPgNum) return i;
//STRIP001  }
//STRIP001  return SDRPAGE_NOTFOUND;
//STRIP001 }

/*N*/ void SdrPage::InsertMasterPage(USHORT nPgNum, USHORT nPos)
/*N*/ {
/*N*/   aMasters.Insert(nPgNum,nPos);
/*N*/   SetChanged();
/*N*/   SendRepaintBroadcast();
/*N*/ }

/*?*/ void SdrPage::InsertMasterPage(const SdrMasterPageDescriptor& rMPD, USHORT nPos)
/*?*/ {
/*?*/   aMasters.Insert(rMPD,nPos);
/*?*/   SetChanged();
/*?*/   SendRepaintBroadcast();
/*?*/ }

/*N*/ void SdrPage::RemoveMasterPage(USHORT nPos)
/*N*/ {
/*N*/   if (nPos<aMasters.GetCount()) {
/*N*/       aMasters.Remove(nPos);
/*N*/       SetChanged();
/*N*/       SendRepaintBroadcast();
/*N*/   }
/*N*/ }

/*N*/ void SdrPage::MoveMasterPage(USHORT nPos, USHORT nNewPos)
/*N*/ {
/*N*/   if (nPos<aMasters.GetCount()) {
/*N*/       aMasters.Move(nPos,nNewPos);
/*N*/       SendRepaintBroadcast();
/*N*/   }
/*N*/ }

/*?*/ SdrPage* SdrPage::GetMasterPage(USHORT nPos) const
/*?*/ {
/*?*/   USHORT nPgNum=GetMasterPageNum(nPos);
/*?*/   SdrPage* pPg=NULL;
/*?*/   if( pModel )
/*?*/       pPg = pModel->GetMasterPage(nPgNum);
/*?*/   return pPg;
/*?*/ }

//STRIP001 void SdrPage::SetMasterPageNum(USHORT nPgNum, USHORT nPos)
//STRIP001 {
//STRIP001  aMasters[nPos].SetPageNum(nPgNum);
//STRIP001  SendRepaintBroadcast();
//STRIP001 }

/*N*/ void SdrPage::SetMasterPageVisibleLayers(const SetOfByte& rVL, USHORT nPos)
/*N*/ {
/*N*/   aMasters[nPos].SetVisibleLayers(rVL);
/*N*/   SendRepaintBroadcast();
/*N*/ }

//STRIP001 void SdrPage::SetMasterPageDescriptor(const SdrMasterPageDescriptor& rMPD, USHORT nPos)
//STRIP001 {
//STRIP001  aMasters[nPos]=rMPD;
//STRIP001  SendRepaintBroadcast();
//STRIP001 }

//STRIP001 void SdrPage::SetMasterPageDescriptorList(const SdrMasterPageDescriptorList& rMPDL)
//STRIP001 {
//STRIP001  aMasters=rMPDL;
//STRIP001  SendRepaintBroadcast();
//STRIP001 }

/*N*/ void SdrPage::ImpMasterPageRemoved(USHORT nMasterPageNum)
/*N*/ {
/*N*/   USHORT nMasterAnz=GetMasterPageCount();
/*N*/   for (USHORT nm=nMasterAnz; nm>0;) {
/*N*/       nm--;
/*N*/       USHORT nNum=aMasters[nm].GetPageNum();
/*N*/       if (nNum==nMasterPageNum) { RemoveMasterPage(nm); SendRepaintBroadcast(); }
/*N*/       if (nNum>nMasterPageNum) {
/*N*/           // Hintere anpassen wegen Verschiebung durch entfernen
/*?*/           aMasters[nm].SetPageNum(USHORT(nNum-1));
/*N*/       }
/*N*/   }
/*N*/ }

//STRIP001 void SdrPage::ImpMasterPageInserted(USHORT nMasterPageNum)
//STRIP001 {
//STRIP001  USHORT nMasterAnz=GetMasterPageCount();
//STRIP001  for (USHORT nm=nMasterAnz; nm>0;) {
//STRIP001      nm--;
//STRIP001      USHORT nNum=aMasters[nm].GetPageNum();
//STRIP001      if (nNum>=nMasterPageNum) {
//STRIP001          // Hintere anpassen wegen Verschiebung durch einfuegen
//STRIP001          aMasters[nm].SetPageNum(nNum+1);
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*N*/ void SdrPage::ImpMasterPageMoved(USHORT nMasterPageNum, USHORT nNewMasterPageNum)
/*N*/ {
/*N*/   USHORT nMasterAnz=GetMasterPageCount();
/*N*/   for (USHORT nm=nMasterAnz; nm>0;) {
/*N*/       nm--;
/*N*/       USHORT nNum=aMasters[nm].GetPageNum();
/*N*/       if (nNum==nMasterPageNum) {
/*N*/           aMasters[nm].SetPageNum(nNewMasterPageNum);
/*N*/       } else {
/*N*/           // Hintere anpassen wegen Verschiebung durch entfernen und einfuegen
/*N*/           USHORT nNeuNum=nNum;
/*N*/           if (nNeuNum>nMasterPageNum) nNeuNum--;
/*N*/           if (nNeuNum>=nNewMasterPageNum) nNeuNum++;
/*N*/           aMasters[nm].SetPageNum(nNeuNum);
/*N*/       }
/*N*/   }
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 FASTBOOL SdrPage::ImplGetFillColor(const Point& rPnt, const SetOfByte& rVisLayers,
//STRIP001                                    FASTBOOL bLayerSorted, Color& rCol, FASTBOOL bSkipBackgroundShape) const
//STRIP001 {
//STRIP001  if (pModel==NULL) return FALSE;
//STRIP001  FASTBOOL bRet=SdrObjList::GetFillColor(rPnt,rVisLayers,bLayerSorted,rCol);
//STRIP001  if (!bRet && !bMaster) {
//STRIP001      // nun zu den Masterpages
//STRIP001      USHORT nMasterAnz=GetMasterPageCount();
//STRIP001      for (USHORT nMaster=nMasterAnz; nMaster>0 && !bRet;) {
//STRIP001          nMaster--;
//STRIP001          const SdrMasterPageDescriptor& rMaster=GetMasterPageDescriptor(nMaster);
//STRIP001          SetOfByte aSet(rVisLayers);
//STRIP001          aSet&=rMaster.GetVisibleLayers();
//STRIP001          SdrPage* pMaster=pModel->GetMasterPage(rMaster.GetPageNum());
//STRIP001          if (pMaster!=NULL)
//STRIP001             {
//STRIP001                 // #108867# Don't fall back to background shape on
//STRIP001                 // master pages. This is later handled by
//STRIP001                 // GetBackgroundColor, and is necessary to cater for
//STRIP001                 // the silly ordering: 1. shapes, 2. master page
//STRIP001                 // shapes, 3. page background, 4. master page
//STRIP001                 // background.
//STRIP001              bRet=pMaster->ImplGetFillColor(rPnt,aSet,bLayerSorted,rCol,TRUE);
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001     // #108867# Only now determine background color from background shapes
//STRIP001     if( !bRet && !bSkipBackgroundShape )
//STRIP001     {
//STRIP001         rCol = GetBackgroundColor();
//STRIP001         return TRUE;
//STRIP001     }
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 FASTBOOL SdrPage::GetFillColor(const Point& rPnt, const SetOfByte& rVisLayers,
//STRIP001                             FASTBOOL bLayerSorted, Color& rCol) const
//STRIP001 {
//STRIP001     // #108867# Wrapper for ImplGetFillColor. Used to properly set the
//STRIP001     // bSkipBackgroundShape parameter. Never skip background shape on
//STRIP001     // first level of recursion
//STRIP001     return ImplGetFillColor(rPnt,rVisLayers,bLayerSorted,rCol,FALSE);
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 const SdrPageGridFrameList* SdrPage::GetGridFrameList(const SdrPageView* pPV, const Rectangle* pRect) const
//STRIP001 {
//STRIP001  return NULL;
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrPage::ReadData(const SdrIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   if (rIn.GetError()!=0) return;
/*N*/   SdrDownCompat aCompat(rIn,STREAM_READ); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("SdrPage");
/*N*/ #endif
/*N*/
/*N*/   if (rHead.GetVersion()>=11) {
/*N*/       // damit ich meine eigenen SubRecords erkenne (ab V11)
/*N*/       char cMagic[4];
/*N*/       if (rIn.Read(cMagic,4)!=4 || memcmp(cMagic,SdrIOJoeMagic,4)!=0) {
/*?*/           rIn.SetError(SVSTREAM_FILEFORMAT_ERROR);
/*?*/           return;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   { // MiscellaneousData ab V11 eingepackt
/*N*/       SdrDownCompat* pPageMiscCompat=NULL;
/*N*/       if (rHead.GetVersion()>=11) {
/*N*/           pPageMiscCompat=new SdrDownCompat(rIn,STREAM_READ);
/*N*/ #ifdef DBG_UTIL
/*N*/           pPageMiscCompat->SetID("SdrPage(Miscellaneous)");
/*N*/ #endif
/*N*/       }
/*N*/       rIn>>nWdt;
/*N*/       rIn>>nHgt;
/*N*/       rIn>>nBordLft;
/*N*/       rIn>>nBordUpp;
/*N*/       rIn>>nBordRgt;
/*N*/       rIn>>nBordLwr;
/*N*/       USHORT n;
/*N*/       rIn>>n; //aName;
/*N*/       if (pPageMiscCompat!=NULL) {
/*N*/           delete pPageMiscCompat;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   FASTBOOL bEnde=FALSE;
/*N*/   while (rIn.GetError()==0 && !rIn.IsEof() && !bEnde) {
/*N*/       SdrIOHeaderLookAhead aHead(rIn);   // Layerdefinitionen lesen
/*N*/       if (aHead.IsID(SdrIOLayrID)) {
/*?*/           SdrLayer* pLay=new SdrLayer;       // Layerdefinition lesen
/*?*/           rIn>>*pLay;
/*?*/           pLayerAdmin->InsertLayer(pLay);
/*N*/       } else
/*N*/       if (aHead.IsID(SdrIOLSetID)) {
/*?*/           SdrLayerSet* pSet=new SdrLayerSet; // Layersetdefinition lesen
/*?*/           rIn>>*pSet;
/*?*/           pLayerAdmin->InsertLayerSet(pSet);
/*N*/       } else
/*N*/       // Fuer den Fall der Faelle kann hier ww. MPgDscr oder MPgDscrList stehen
/*N*/       if (aHead.IsID(SdrIOMPgDID)) { // Masterpagedescriptor
/*?*/           SdrMasterPageDescriptor aDscr;
/*?*/           rIn>>aDscr;
/*?*/           aMasters.Insert(aDscr);
/*N*/       } else
/*N*/       if (aHead.IsID(SdrIOMPDLID)) { // MasterpagedescriptorList
/*N*/           SdrMasterPageDescriptorList aDscrList;
/*N*/           rIn>>aDscrList;
/*N*/           USHORT nAnz=aDscrList.GetCount();
/*N*/           for (USHORT nNum=0; nNum<nAnz; nNum++) {
/*N*/               aMasters.Insert(aDscrList[nNum]);
/*N*/           }
/*N*/       } else bEnde=TRUE;
/*N*/   }
/*N*/
/*N*/   if (rHead.GetVersion()>=1) {
/*N*/   } else {
/*?*/       USHORT nMaAnz=0,i;
/*?*/       rIn>>nMaAnz;
/*?*/       for (i=0; i<nMaAnz; i++) {
/*?*/           USHORT nMaPgNum;
/*?*/           rIn>>nMaPgNum;
/*?*/           InsertMasterPage(nMaPgNum);
/*N*/       }
/*N*/   }
/*N*/   SdrObjList::Load(rIn,*this);  // Liste der Objekte lesen
/*N*/
/*N*/   if ( rHead.GetVersion() >= 16 )
/*N*/   {
/*N*/       BOOL bBackgroundObj = FALSE;
/*N*/       rIn >> bBackgroundObj;
/*N*/       if( bBackgroundObj )
/*N*/       {
/*N*/           SdrObjIOHeaderLookAhead aHead( rIn,STREAM_READ );
/*N*/           if ( !aHead.IsEnde() )
/*N*/           {
/*N*/               pBackgroundObj = SdrObjFactory::MakeNewObject( aHead.nInventor, aHead.nIdentifier, this );
/*N*/               if ( bBackgroundObj )
/*N*/                   rIn >> *pBackgroundObj;
/*N*/           }
/*N*/           else
/*?*/               aHead.SkipRecord(); // skip end mark
/*N*/       }
/*N*/   }
/*N*/
    // #88340#
/*N*/   if(!aMasters.GetCount() && !IsMasterPage())
/*N*/   {
/*N*/       if(pModel && pModel->GetMasterPageCount() > 2)
/*N*/       {
/*N*/           // This is not allowed. Create a dummy entry
/*N*/           // to compensate this error.
/*?*/           SdrMasterPageDescriptor aDscr(1/*PageMaster*/);
/*?*/           aMasters.Insert(aDscr);
/*N*/       }
/*N*/       else
/*N*/       {
/*N*/           SdrMasterPageDescriptor aDscr(0);
/*N*/           aMasters.Insert(aDscr);
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void SdrPage::WriteData(SvStream& rOut) const
/*N*/ {
/*N*/   SdrDownCompat aCompat(rOut,STREAM_WRITE); // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/ #ifdef DBG_UTIL
/*N*/   aCompat.SetID("SdrPage");
/*N*/ #endif
/*N*/   rOut.Write(SdrIOJoeMagic,4); // damit ich meine eigenen SubRecords erkenne (ab V11)
/*N*/   { // MiscellaneousData ab V11 eingepackt
/*N*/       SdrDownCompat aPageMiscCompat(rOut,STREAM_WRITE);
/*N*/ #ifdef DBG_UTIL
/*N*/       aPageMiscCompat.SetID("SdrPage(Miscellaneous)");
/*N*/ #endif
/*N*/       rOut<<nWdt;
/*N*/       rOut<<nHgt;
/*N*/       rOut<<nBordLft;
/*N*/       rOut<<nBordUpp;
/*N*/       rOut<<nBordRgt;
/*N*/       rOut<<nBordLwr;
/*N*/       USHORT n=0;
/*N*/       rOut<<n; //rPg.aName;
/*N*/   }
/*N*/
/*N*/   USHORT i; // Lokale Layerdefinitionen der Seite
/*N*/   for (i=0; i<pLayerAdmin->GetLayerCount(); i++) {
/*?*/       rOut<<*pLayerAdmin->GetLayer(i);
/*N*/   }
/*N*/   for (i=0; i<pLayerAdmin->GetLayerSetCount(); i++) {
/*?*/       rOut<<*pLayerAdmin->GetLayerSet(i);
/*N*/   }
/*N*/
/*N*/   rOut<<aMasters;
/*N*/   SdrObjList::Save(rOut);
/*N*/
/*N*/   BOOL bBackgroundObj = pBackgroundObj ? TRUE : FALSE;
/*N*/   rOut << bBackgroundObj;
/*N*/   if( pBackgroundObj )
/*N*/       rOut << *pBackgroundObj;
/*N*/ }

/*N*/ SvStream& operator>>(SvStream& rIn, SdrPage& rPg)
/*N*/ {
/*N*/   if (rIn.GetError()!=0) return rIn;
/*N*/   SdrIOHeader aHead(rIn,STREAM_READ);
/*N*/   rPg.ReadData(aHead,rIn);
/*N*/   return rIn;
/*N*/ }

/*N*/ SvStream& operator<<(SvStream& rOut, const SdrPage& rPg)
/*N*/ {
/*N*/   SdrIOHeader aHead(rOut,STREAM_WRITE,!rPg.bMaster ? SdrIOPageID : SdrIOMaPgID);
/*N*/   rPg.WriteData(rOut);
/*N*/   return rOut;
/*N*/ }

/*N*/ XubString SdrPage::GetLayoutName() const
/*N*/ {
/*N*/   // Die wollte Dieter haben.
/*N*/   return String();
/*N*/ }

/*N*/ void SdrPage::SetBackgroundObj( SdrObject* pObj )
/*N*/ {
/*N*/   if ( pObj )
/*N*/   {
/*N*/       pObj->SetPage( this );
/*N*/       pObj->SetModel( pModel );
/*N*/       pObj->SetLayer( 1 );        // Nothing known about the backgroundlayer...
/*N*/   }
/*N*/   delete pBackgroundObj, pBackgroundObj = pObj;
/*N*/ }

/*N*/ void SdrPage::SetInserted( FASTBOOL bIns )
/*N*/ {
/*N*/   if( bInserted != bIns )
/*N*/   {
/*N*/       bInserted = bIns;
/*N*/
/*N*/       SdrObjListIter aIter( *this, IM_FLAT );
/*N*/       while ( aIter.IsMore() )
/*N*/       {
/*N*/           SdrObject* pObj = aIter.Next();
/*N*/           if ( pObj->ISA(SdrOle2Obj) )
/*N*/           {
/*N*/               if( bInserted )
/*N*/                   ( (SdrOle2Obj*) pObj)->Connect();
/*N*/               else
/*N*/                   ( (SdrOle2Obj*) pObj)->Disconnect();
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }


/*N*/ uno::Reference< uno::XInterface > SdrPage::getUnoPage()
/*N*/ {
/*N*/   // try weak reference first
/*N*/   uno::Reference< uno::XInterface > xPage( mxUnoPage );
/*N*/
/*N*/   if( !xPage.is() )
/*N*/   {
/*N*/       // create one
/*N*/       xPage = createUnoPage();
/*N*/
/*N*/       mxUnoPage = xPage;
/*N*/   }
/*N*/
/*N*/   return xPage;
/*N*/ }

/*N*/ uno::Reference< uno::XInterface > SdrPage::createUnoPage()
/*N*/ {
/*N*/   ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > xInt =
/*N*/ #ifndef SVX_LIGHT
/*N*/       static_cast<cppu::OWeakObject*>( new SvxFmDrawPage( this ) );
/*N*/ #else
/*N*/       static_cast<cppu::OWeakObject*>( new SvxDrawPage( this ) );
/*N*/ #endif
/*N*/   return xInt;
/*N*/ }

/*N*/ SfxStyleSheet* SdrPage::GetTextStyleSheetForObject( SdrObject* pObj ) const
/*N*/ {
/*N*/   return pObj->GetStyleSheet();
/*N*/ }

//STRIP001 FASTBOOL SdrPage::HasTransparentObjects( BOOL bCheckForAlphaChannel ) const
//STRIP001 {
//STRIP001  FASTBOOL bRet = FALSE;
//STRIP001
//STRIP001  for( ULONG n = 0, nCount = GetObjCount(); ( n < nCount ) && !bRet; n++ )
//STRIP001      if( GetObj( n )->IsTransparent( bCheckForAlphaChannel ) )
//STRIP001          bRet = TRUE;
//STRIP001
//STRIP001  return bRet;
//STRIP001 }

/** returns an averaged background color of this page */
/*N*/ Color SdrPage::GetBackgroundColor( SdrPageView* pView ) const
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); Color aColor; return aColor;
//STRIP001  Color aColor;
//STRIP001
//STRIP001  if( (NULL == pView) || (pView->GetApplicationDocumentColor() == COL_AUTO) )
//STRIP001  {
//STRIP001         svtools::ColorConfig aColorConfig;
//STRIP001         aColor = aColorConfig.GetColorValue( svtools::DOCCOLOR ).nColor;
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      aColor = pView->GetApplicationDocumentColor();
//STRIP001  }
//STRIP001
//STRIP001  // first, see if we have a background object
//STRIP001  SdrObject* pBackgroundObj = NULL;
//STRIP001
//STRIP001
//STRIP001  if( IsMasterPage() )
//STRIP001  {
//STRIP001      if( GetObjCount() )
//STRIP001          pBackgroundObj = GetObj( 0 );
//STRIP001  }
//STRIP001  else
//STRIP001  {
//STRIP001      pBackgroundObj = GetBackgroundObj();
//STRIP001      if( NULL == pBackgroundObj )
//STRIP001      {
//STRIP001          // if not, see if we have a masterpage and get that background object
//STRIP001          if( GetMasterPageCount() )
//STRIP001          {
//STRIP001              SdrPage* pMaster = GetMasterPage(0);
//STRIP001
//STRIP001              if( pMaster && pMaster->GetObjCount() )
//STRIP001                  pBackgroundObj = pMaster->GetObj( 0 );
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if( pBackgroundObj )
//STRIP001  {
//STRIP001      const SfxItemSet& rSet = pBackgroundObj->GetItemSet();
//STRIP001      GetDraftFillColor( rSet, aColor );
//STRIP001  }
//STRIP001
//STRIP001  return aColor;
/*N*/ }

/** *deprecated, use GetBackgroundColor with SdrPageView */
/*N*/ Color SdrPage::GetBackgroundColor() const
/*N*/ {
/*N*/   return GetBackgroundColor( NULL );
/*N*/ }

#ifdef GCC
// Dummy-Implementationen fuer Deklarationen in svdpage.hxx
/*N*/ Bitmap      SdrPage::GetBitmap(const SetOfByte& rVisibleLayers, FASTBOOL bTrimBorders) const {}
/*N*/ GDIMetaFile SdrPage::GetMetaFile(const SetOfByte& rVisibleLayers, FASTBOOL bTrimBorders) {}
#endif
}
