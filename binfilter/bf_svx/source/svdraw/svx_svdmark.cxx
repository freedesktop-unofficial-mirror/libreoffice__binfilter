/*************************************************************************
 *
 *  $RCSfile: svx_svdmark.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:46:15 $
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

#include "svdmark.hxx"
#include "svdetc.hxx"
#include "svdobj.hxx"
#include "svdpage.hxx"
#include "svditer.hxx"
#include "svdpagv.hxx"
#include "svdopath.hxx" // zur Abschaltung
#include "svdogrp.hxx"  // des Cache bei
#include "svdorect.hxx" // GetMarkDescription
#include "svdstr.hrc"   // Namen aus der Resource
#include "svdglob.hxx"  // StringCache
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 class ImpSdrUShortContSorter: public ContainerSorter
//STRIP001 {
//STRIP001 public:
//STRIP001  ImpSdrUShortContSorter(Container& rNewCont): ContainerSorter(rNewCont) {}
//STRIP001  virtual int Compare(const void* pElem1, const void* pElem2) const;
//STRIP001 };

//STRIP001 int ImpSdrUShortContSorter::Compare(const void* pElem1, const void* pElem2) const
//STRIP001 {
//STRIP001  USHORT n1=USHORT(ULONG(pElem1));
//STRIP001  USHORT n2=USHORT(ULONG(pElem2));
//STRIP001  return n1<n2 ? -1 : n1>n2 ? 1 : 0;
//STRIP001 }

//STRIP001 void SdrUShortCont::Sort()
//STRIP001 {
//STRIP001  ImpSdrUShortContSorter aSort(aArr);
//STRIP001  aSort.DoSort();
//STRIP001  bSorted=TRUE;
//STRIP001  if (bDelDups) {
//STRIP001      ULONG nNum=GetCount();
//STRIP001      if (nNum>1) {
//STRIP001          nNum--;
//STRIP001          USHORT nVal0=GetObject(nNum);
//STRIP001          while (nNum>0) {
//STRIP001              nNum--;
//STRIP001              USHORT nVal1=GetObject(nNum);
//STRIP001              if (nVal1==nVal0) {
//STRIP001                  Remove(nNum);
//STRIP001              }
//STRIP001              nVal0=nVal1;
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrUShortCont::CheckSort(ULONG nPos)
//STRIP001 {
//STRIP001  ULONG nAnz=aArr.Count();
//STRIP001  if (nPos>nAnz) nPos=nAnz;
//STRIP001  USHORT nAktVal=GetObject(nPos);
//STRIP001  if (nPos>0) {
//STRIP001      USHORT nPrevVal=GetObject(nPos-1);
//STRIP001      if (bDelDups) {
//STRIP001          if (nPrevVal>=nAktVal) bSorted=FALSE;
//STRIP001      } else {
//STRIP001          if (nPrevVal>nAktVal) bSorted=FALSE;
//STRIP001      }
//STRIP001  }
//STRIP001  if (nPos<nAnz-1) {
//STRIP001      USHORT nNextVal=GetObject(nPos+1);
//STRIP001      if (bDelDups) {
//STRIP001          if (nNextVal<=nAktVal) bSorted=FALSE;
//STRIP001      } else {
//STRIP001          if (nNextVal<nAktVal) bSorted=FALSE;
//STRIP001      }
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 SdrMark& SdrMark::operator=(const SdrMark& rMark)
//STRIP001 {
//STRIP001  pObj=rMark.pObj;
//STRIP001  pPageView=rMark.pPageView;
//STRIP001  bCon1=rMark.bCon1;
//STRIP001  bCon2=rMark.bCon2;
//STRIP001  nUser=rMark.nUser;
//STRIP001  if (rMark.pPoints==NULL) {
//STRIP001      if (pPoints!=NULL) {
//STRIP001          delete pPoints;
//STRIP001          pPoints=NULL;
//STRIP001      }
//STRIP001  } else {
//STRIP001      if (pPoints==NULL) {
//STRIP001          pPoints=new SdrUShortCont(*rMark.pPoints);
//STRIP001      } else {
//STRIP001          *pPoints=*rMark.pPoints;
//STRIP001      }
//STRIP001  }
//STRIP001  if (rMark.pLines==NULL) {
//STRIP001      if (pLines!=NULL) {
//STRIP001          delete pLines;
//STRIP001          pLines=NULL;
//STRIP001      }
//STRIP001  } else {
//STRIP001      if (pLines==NULL) {
//STRIP001          pLines=new SdrUShortCont(*rMark.pLines);
//STRIP001      } else {
//STRIP001          *pLines=*rMark.pLines;
//STRIP001      }
//STRIP001  }
//STRIP001  if (rMark.pGluePoints==NULL) {
//STRIP001      if (pGluePoints!=NULL) {
//STRIP001          delete pGluePoints;
//STRIP001          pGluePoints=NULL;
//STRIP001      }
//STRIP001  } else {
//STRIP001      if (pGluePoints==NULL) {
//STRIP001          pGluePoints=new SdrUShortCont(*rMark.pGluePoints);
//STRIP001      } else {
//STRIP001          *pGluePoints=*rMark.pGluePoints;
//STRIP001      }
//STRIP001  }
//STRIP001  return *this;
//STRIP001 }

//STRIP001 FASTBOOL SdrMark::operator==(const SdrMark& rMark) const
//STRIP001 {
//STRIP001  FASTBOOL bRet=pObj==rMark.pObj && pPageView==rMark.pPageView && bCon1==rMark.bCon1 && bCon2==rMark.bCon2 && nUser==rMark.nUser;
//STRIP001  if ((pPoints!=NULL) != (rMark.pPoints!=NULL)) bRet=FALSE;
//STRIP001  if ((pLines !=NULL) != (rMark.pLines !=NULL)) bRet=FALSE;
//STRIP001  if ((pGluePoints!=NULL) != (rMark.pGluePoints!=NULL)) bRet=FALSE;
//STRIP001  if (bRet && pPoints!=NULL && *pPoints!=*rMark.pPoints) bRet=FALSE;
//STRIP001  if (bRet && pLines !=NULL && *pLines !=*rMark.pLines ) bRet=FALSE;
//STRIP001  if (bRet && pGluePoints!=NULL && *pGluePoints!=*rMark.pGluePoints) bRet=FALSE;
//STRIP001  return bRet;
//STRIP001 }

//STRIP001 SdrPage* SdrMark::GetPage() const
//STRIP001 {
//STRIP001  return (pObj!=NULL ? pObj->GetPage() : NULL);
//STRIP001 }

//STRIP001 SdrObjList* SdrMark::GetObjList() const
//STRIP001 {
//STRIP001  return (pObj!=NULL ? pObj->GetObjList() : NULL);
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 class ImpSdrMarkListSorter: public ContainerSorter
//STRIP001 {
//STRIP001 public:
//STRIP001  ImpSdrMarkListSorter(Container& rNewCont): ContainerSorter(rNewCont) {}
//STRIP001  virtual int Compare(const void* pElem1, const void* pElem2) const;
//STRIP001 };

//STRIP001 int ImpSdrMarkListSorter::Compare(const void* pElem1, const void* pElem2) const
//STRIP001 {
//STRIP001  const SdrObject* pObj1=((SdrMark*)pElem1)->GetObj();
//STRIP001  const SdrObject* pObj2=((SdrMark*)pElem2)->GetObj();
//STRIP001  const SdrObjList* pOL1=pObj1!=NULL ? pObj1->GetObjList() : NULL;
//STRIP001  const SdrObjList* pOL2=pObj2!=NULL ? pObj2->GetObjList() : NULL;
//STRIP001  if (pOL1==pOL2) {
//STRIP001      ULONG nObjOrd1=pObj1!=NULL ? pObj1->GetOrdNum() : 0;
//STRIP001      ULONG nObjOrd2=pObj2!=NULL ? pObj2->GetOrdNum() : 0;
//STRIP001      return nObjOrd1<nObjOrd2 ? -1 : 1;
//STRIP001  } else {
//STRIP001      return (long)pOL1<(long)pOL2 ? -1 : 1;
//STRIP001  }
//STRIP001 }

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrMarkList::ForceSort()
/*N*/ {
/*N*/   if (!bSorted) {
/*N*/       bSorted=TRUE;
/*N*/       ULONG nAnz=aList.Count();
/*N*/       if (nAnz>1) {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            ImpSdrMarkListSorter aSort(aList);
//STRIP001 /*?*/            aSort.DoSort();
//STRIP001 /*?*/            // und nun doppelte rauswerfen
//STRIP001 /*?*/            if (aList.Count()>1) {
//STRIP001 /*?*/                SdrMark* pAkt=(SdrMark*)aList.Last();
//STRIP001 /*?*/                SdrMark* pCmp=(SdrMark*)aList.Prev();
//STRIP001 /*?*/                while (pCmp!=NULL) {
//STRIP001 /*?*/                    if (pAkt->GetObj()==pCmp->GetObj()) {
//STRIP001 /*?*/                        // Con1/Con2 Merging
//STRIP001 /*?*/                        if (pCmp->IsCon1()) pAkt->SetCon1(TRUE);
//STRIP001 /*?*/                        if (pCmp->IsCon2()) pAkt->SetCon2(TRUE);
//STRIP001 /*?*/                        // pCmp loeschen.
//STRIP001 /*?*/                        aList.Remove();
//STRIP001 /*?*/                        delete pCmp;
//STRIP001 /*?*/                        // Aktueller Entry im Container ist nun pAkt!
//STRIP001 /*?*/                    } else {
//STRIP001 /*?*/                        pAkt=pCmp;
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    pCmp=(SdrMark*)aList.Prev();
//STRIP001 /*?*/                }
//STRIP001 /*?*/            }
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void SdrMarkList::Clear()
/*N*/ {
/*N*/   for (ULONG i=0; i<GetMarkCount(); i++) {
/*?*/       SdrMark* pMark=GetMark(i);
/*?*/       delete pMark;
/*N*/   }
/*N*/   aList.Clear();
/*N*/   SetNameDirty();
/*N*/ }

/*N*/ void SdrMarkList::operator=(const SdrMarkList& rLst)
/*N*/ {
/*N*/   Clear();
/*N*/   for (ULONG i=0; i<rLst.GetMarkCount(); i++) {
/*?*/       SdrMark* pMark=rLst.GetMark(i);
/*?*/       SdrMark* pNeuMark=new SdrMark(*pMark);
/*?*/       aList.Insert(pNeuMark,CONTAINER_APPEND);
/*N*/   }
/*N*/   aMarkName=rLst.aMarkName;
/*N*/   bNameOk=rLst.bNameOk;
/*N*/   aPointName=rLst.aPointName;
/*N*/   bPointNameOk=rLst.bPointNameOk;
/*N*/   aGluePointName=rLst.aGluePointName;
/*N*/   bGluePointNameOk=rLst.bGluePointNameOk;
/*N*/   bSorted=rLst.bSorted;
/*N*/ }

/*N*/ ULONG SdrMarkList::FindObject(const SdrObject* pObj)
/*N*/ {
    // #109658#
    //
    // Since relying on OrdNums is not allowed for the selection because objects in the
    // selection may not be inserted in a list if they are e.g. modified ATM, i changed
    // this loop to just look if the object pointer is in the selection.
    //
    // Problem is that GetOrdNum() which is const, internally casts no non-const and
    // hardly sets the OrdNum member of the object (nOrdNum) to 0 (ZERO) if the object
    // is not inserted in a object list.
    // Since this may be by purpose and necessary somewhere else i decided that it is
    // less dangerous to change this method then changing SdrObject::GetOrdNum().
/*N*/   if(pObj && aList.Count())
/*N*/   {
/*N*/       for(sal_uInt32 a(0L); a < aList.Count(); a++)
/*N*/       {
/*N*/           if(((SdrMark*)(aList.GetObject(a)))->GetObj() == pObj)
/*N*/           {
/*N*/               return a;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/
/*N*/   return CONTAINER_ENTRY_NOTFOUND;

    /*
    ForceSort();
    if (pObj==NULL || aList.Count()==0) return CONTAINER_ENTRY_NOTFOUND;
    const SdrObjList* pOL=pObj->GetObjList();
    ULONG nObjOrd=pObj->GetOrdNum();
    ULONG nL=0;
    ULONG nR=aList.Count();
    if (GetMark(nL)->GetObj()==pObj) return nL;
    while (nL+1<nR) { // Der Gesuchte befindet sich zwischen, nicht auf den Grenzen!
        ULONG nMid=(nL+nR)/2;
        const SdrObject* pMidObj=GetMark(nMid)->GetObj();
        if (pMidObj==pObj) return nMid; // Hurra, gefunden!
        const SdrObjList* pMidOL=pMidObj!=NULL ? pMidObj->GetObjList() : NULL;
        ULONG nMidObjOrd=pMidObj!=NULL ? pMidObj->GetOrdNum() : 0;
        if (pMidOL==pOL) {
            if (nMidObjOrd<nObjOrd) nL=nMid;
            else if (nMidObjOrd>nObjOrd) nR=nMid;
            else {
                DBG_ASSERT(FALSE,"SdrMarkList::FindObject(): Anderes Objekt mit gleicher OrdNum gefunden!");
                return CONTAINER_ENTRY_NOTFOUND;
            }
        } else if ((long)pMidOL<(long)pOL) nL=nMid;
        else nR=nMid;
    }
    return CONTAINER_ENTRY_NOTFOUND;
    */
/*N*/ }

/*N*/ void SdrMarkList::InsertEntry(const SdrMark& rMark, FASTBOOL bChkSort)
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001  SetNameDirty();
//STRIP001  ULONG nAnz=aList.Count();
//STRIP001  if (!bChkSort || !bSorted || nAnz==0) {
//STRIP001      if (!bChkSort) bSorted=FALSE;
//STRIP001      aList.Insert(new SdrMark(rMark),CONTAINER_APPEND);
//STRIP001  } else {
//STRIP001      SdrMark* pLast=GetMark(ULONG(nAnz-1));
//STRIP001      const SdrObject* pLastObj=pLast->GetObj();
//STRIP001      const SdrObject* pNeuObj=rMark.GetObj();
//STRIP001      if (pLastObj==pNeuObj) { // Aha, den gibt's schon
//STRIP001          // Con1/Con2 Merging
//STRIP001          if (rMark.IsCon1()) pLast->SetCon1(TRUE);
//STRIP001          if (rMark.IsCon2()) pLast->SetCon2(TRUE);
//STRIP001      } else {
//STRIP001          SdrMark* pKopie=new SdrMark(rMark);
//STRIP001          aList.Insert(pKopie,CONTAINER_APPEND);
//STRIP001          // und nun checken, ob die Sortierung noch ok ist
//STRIP001          const SdrObjList* pLastOL=pLastObj!=NULL ? pLastObj->GetObjList() : NULL;
//STRIP001          const SdrObjList* pNeuOL =pNeuObj !=NULL ? pNeuObj ->GetObjList() : NULL;
//STRIP001          if (pLastOL==pNeuOL) {
//STRIP001              ULONG nLastNum=pLastObj!=NULL ? pLastObj->GetOrdNum() : 0;
//STRIP001              ULONG nNeuNum =pNeuObj !=NULL ? pNeuObj ->GetOrdNum() : 0;
//STRIP001              if (nNeuNum<nLastNum) {
//STRIP001                  bSorted=FALSE; // irgendwann muss mal sortiert werden
//STRIP001              }
//STRIP001          } else {
//STRIP001              if ((long)pNeuOL<(long)pLastOL) {
//STRIP001                  bSorted=FALSE; // irgendwann muss mal sortiert werden
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
//STRIP001  return;
/*N*/ }

//STRIP001 void SdrMarkList::DeleteMark(ULONG nNum)
//STRIP001 {
//STRIP001  //ForceSort();
//STRIP001  SdrMark* pMark=GetMark(nNum);
//STRIP001  DBG_ASSERT(pMark!=NULL,"DeleteMark: MarkEntry nicht gefunden");
//STRIP001  if (pMark!=NULL) {
//STRIP001      aList.Remove(nNum);
//STRIP001      delete pMark;
//STRIP001      SetNameDirty();
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrMarkList::ReplaceMark(const SdrMark& rNewMark, ULONG nNum)
//STRIP001 {
//STRIP001  SdrMark* pMark=GetMark(nNum);
//STRIP001  DBG_ASSERT(pMark!=NULL,"ReplaceMark: MarkEntry nicht gefunden");
//STRIP001  if (pMark!=NULL) {
//STRIP001      delete pMark;
//STRIP001      SetNameDirty();
//STRIP001      SdrMark* pKopie=new SdrMark(rNewMark);
//STRIP001      aList.Replace(pKopie,nNum);
//STRIP001      bSorted=FALSE;
//STRIP001      // Checken, ob bSorted wirklich gesetzt werden muss
//STRIP001  }
//STRIP001 }

//STRIP001 void SdrMarkList::Merge(const SdrMarkList& rSrcList, FASTBOOL bReverse)
//STRIP001 {
//STRIP001  // Merging ohne ein Sort bei rSrcList zu erzwingen
//STRIP001  if (rSrcList.bSorted) bReverse=FALSE;
//STRIP001  ULONG nAnz=rSrcList.aList.Count();
//STRIP001  if (!bReverse) {
//STRIP001      for (ULONG i=0; i<nAnz; i++) {
//STRIP001          SdrMark* pM=(SdrMark*)(rSrcList.aList.GetObject(i));
//STRIP001          InsertEntry(*pM);
//STRIP001      }
//STRIP001  } else {
//STRIP001      for (ULONG i=nAnz; i>0;) {
//STRIP001          i--;
//STRIP001          SdrMark* pM=(SdrMark*)(rSrcList.aList.GetObject(i));
//STRIP001          InsertEntry(*pM);
//STRIP001      }
//STRIP001  }
//STRIP001 }

/*N*/ FASTBOOL SdrMarkList::DeletePageView(const SdrPageView& rPV)
/*N*/ {
/*N*/   FASTBOOL bChgd=FALSE;
/*N*/   for (ULONG i=GetMarkCount(); i>0;) {
/*?*/       i--;
/*?*/       SdrMark* pMark=GetMark(i);
/*?*/       if (pMark->GetPageView()==&rPV) {
/*?*/           aList.Remove(i);
/*?*/           delete pMark;
/*?*/           SetNameDirty();
/*?*/           bChgd=TRUE;
/*?*/       }
/*N*/   }
/*N*/   return bChgd;
/*N*/ }

//STRIP001 FASTBOOL SdrMarkList::InsertPageView(const SdrPageView& rPV)
//STRIP001 {
//STRIP001  FASTBOOL bChgd=FALSE;
//STRIP001  DeletePageView(rPV); // erstmal alle raus, dann die ganze Seite hinten dran
//STRIP001  SdrObject* pObj;
//STRIP001  const SdrObjList* pOL=rPV.GetObjList();
//STRIP001  ULONG nObjAnz=pOL->GetObjCount();
//STRIP001  for (ULONG nO=0; nO<nObjAnz; nO++) {
//STRIP001      pObj=pOL->GetObj(nO);
//STRIP001      FASTBOOL bDoIt=rPV.IsObjMarkable(pObj);
//STRIP001      if (bDoIt) {
//STRIP001          SdrMark* pM=new SdrMark(pObj,(SdrPageView*)&rPV);
//STRIP001          aList.Insert(pM,CONTAINER_APPEND);
//STRIP001          SetNameDirty();
//STRIP001          bChgd=TRUE;
//STRIP001      }
//STRIP001  }
//STRIP001  return bChgd;
//STRIP001 }

//STRIP001 const XubString& SdrMarkList::GetMarkDescription() const
//STRIP001 {
//STRIP001  UINT32 nAnz(GetMarkCount());
//STRIP001
//STRIP001  if(bNameOk && nAnz==1)
//STRIP001  {
//STRIP001      // Bei Einfachselektion nur Textrahmen cachen
//STRIP001      SdrObject* pObj = GetMark(0)->GetObj();
//STRIP001      SdrTextObj* pTextObj = PTR_CAST(SdrTextObj,pObj);
//STRIP001
//STRIP001      if(!pTextObj || !pTextObj->IsTextFrame())
//STRIP001      {
//STRIP001          ((SdrMarkList*)(this))->bNameOk = FALSE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if(!bNameOk)
//STRIP001  {
//STRIP001      SdrMark* pMark = GetMark(0);
//STRIP001      XubString aNam;
//STRIP001
//STRIP001      if(!nAnz)
//STRIP001      {
//STRIP001          ((SdrMarkList*)(this))->aMarkName = ImpGetResStr(STR_ObjNameNoObj);
//STRIP001      }
//STRIP001      else if(nAnz == 1)
//STRIP001      {
//STRIP001          pMark->GetObj()->TakeObjNameSingul(aNam);
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pMark->GetObj()->TakeObjNamePlural(aNam);
//STRIP001          XubString aStr1;
//STRIP001          BOOL bEq(TRUE);
//STRIP001
//STRIP001          for(UINT32 i = 1; i < GetMarkCount() && bEq; i++)
//STRIP001          {
//STRIP001              SdrMark* pMark = GetMark(i);
//STRIP001              pMark->GetObj()->TakeObjNamePlural(aStr1);
//STRIP001              bEq = aNam.Equals(aStr1);
//STRIP001          }
//STRIP001
//STRIP001          if(!bEq)
//STRIP001              aNam = ImpGetResStr(STR_ObjNamePlural);
//STRIP001
//STRIP001          aNam.Insert(sal_Unicode(' '), 0);
//STRIP001          aNam.Insert(UniString::CreateFromInt32(nAnz), 0);
//STRIP001      }
//STRIP001
//STRIP001      ((SdrMarkList*)(this))->aMarkName = aNam;
//STRIP001      ((SdrMarkList*)(this))->bNameOk = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  return aMarkName;
//STRIP001 }

//STRIP001 const XubString& SdrMarkList::GetPointMarkDescription(FASTBOOL bGlue) const
//STRIP001 {
//STRIP001  FASTBOOL& rNameOk = (FASTBOOL&)(bGlue ? bGluePointNameOk : bPointNameOk);
//STRIP001  XubString& rName = (XubString&)(bGlue ? aGluePointName : aPointName);
//STRIP001  UINT32 nMarkAnz(GetMarkCount());
//STRIP001  UINT32 nMarkPtAnz(0);
//STRIP001  UINT32 nMarkPtObjAnz(0);
//STRIP001  UINT32 n1stMarkNum(0xFFFFFFFF);
//STRIP001
//STRIP001  for(UINT32 nMarkNum = 0; nMarkNum < nMarkAnz; nMarkNum++)
//STRIP001  {
//STRIP001      const SdrMark* pMark = GetMark(nMarkNum);
//STRIP001      const SdrUShortCont* pPts = bGlue ? pMark->GetMarkedGluePoints() : pMark->GetMarkedPoints();
//STRIP001      UINT32 nAnz(pPts ? pPts->GetCount() : 0);
//STRIP001
//STRIP001      if(nAnz)
//STRIP001      {
//STRIP001          if(n1stMarkNum == 0xFFFFFFFF)
//STRIP001              n1stMarkNum = nMarkNum;
//STRIP001
//STRIP001          nMarkPtAnz += nAnz;
//STRIP001          nMarkPtObjAnz++;
//STRIP001      }
//STRIP001
//STRIP001      if(nMarkPtObjAnz > 1 && rNameOk)
//STRIP001          // vorzeitige Entscheidung
//STRIP001          return rName;
//STRIP001  }
//STRIP001
//STRIP001  if(rNameOk && nMarkPtObjAnz == 1)
//STRIP001  {
//STRIP001      // Bei Einfachselektion nur Textrahmen cachen
//STRIP001      SdrObject* pObj = GetMark(0)->GetObj();
//STRIP001      SdrTextObj* pTextObj = PTR_CAST(SdrTextObj,pObj);
//STRIP001
//STRIP001      if(!pTextObj || !pTextObj->IsTextFrame())
//STRIP001      {
//STRIP001          rNameOk = FALSE;
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  if(!nMarkPtObjAnz)
//STRIP001  {
//STRIP001      rName.Erase();
//STRIP001      rNameOk = TRUE;
//STRIP001  }
//STRIP001  else if(!rNameOk)
//STRIP001  {
//STRIP001      const SdrMark* pMark = GetMark(n1stMarkNum);
//STRIP001      XubString aNam;
//STRIP001
//STRIP001      if(nMarkPtObjAnz == 1)
//STRIP001      {
//STRIP001          pMark->GetObj()->TakeObjNameSingul(aNam);
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          pMark->GetObj()->TakeObjNamePlural(aNam);
//STRIP001          XubString aStr1;
//STRIP001          BOOL bEq(TRUE);
//STRIP001
//STRIP001          for(UINT32 i = n1stMarkNum + 1; i < GetMarkCount() && bEq; i++)
//STRIP001          {
//STRIP001              const SdrMark* pMark = GetMark(i);
//STRIP001              const SdrUShortCont* pPts = bGlue ? pMark->GetMarkedGluePoints() : pMark->GetMarkedPoints();
//STRIP001
//STRIP001              if(pPts && pPts->GetCount())
//STRIP001              {
//STRIP001                  pMark->GetObj()->TakeObjNamePlural(aStr1);
//STRIP001                  bEq = aNam.Equals(aStr1);
//STRIP001              }
//STRIP001          }
//STRIP001
//STRIP001          if(!bEq)
//STRIP001              aNam = ImpGetResStr(STR_ObjNamePlural);
//STRIP001
//STRIP001          aNam.Insert(sal_Unicode(' '), 0);
//STRIP001          aNam.Insert(UniString::CreateFromInt32(nMarkPtObjAnz), 0);
//STRIP001      }
//STRIP001
//STRIP001      XubString aStr1;
//STRIP001
//STRIP001      if(nMarkPtAnz == 1)
//STRIP001      {
//STRIP001          aStr1 = (ImpGetResStr(bGlue ? STR_ViewMarkedGluePoint : STR_ViewMarkedPoint));
//STRIP001      }
//STRIP001      else
//STRIP001      {
//STRIP001          aStr1 = (ImpGetResStr(bGlue ? STR_ViewMarkedGluePoints : STR_ViewMarkedPoints));
//STRIP001          aStr1.SearchAndReplaceAscii("%N", UniString::CreateFromInt32(nMarkPtAnz));
//STRIP001      }
//STRIP001
//STRIP001      aStr1.SearchAndReplaceAscii("%O", aNam);
//STRIP001      rName = aStr1;
//STRIP001      rNameOk = TRUE;
//STRIP001  }
//STRIP001
//STRIP001  return rName;
//STRIP001 }

//STRIP001 USHORT SdrMarkList::GetPageViewAnz() const
//STRIP001 {
//STRIP001  USHORT nAnz=0;
//STRIP001  SdrPageView* pPV=NULL;
//STRIP001  for (ULONG i=0; i<GetMarkCount(); i++) {
//STRIP001      SdrMark* pMark=GetMark(i);
//STRIP001      if (pMark->GetPageView()!=pPV) {
//STRIP001          pPV=pMark->GetPageView();
//STRIP001          nAnz++;
//STRIP001      }
//STRIP001  }
//STRIP001  return nAnz;
//STRIP001 }

//STRIP001 SdrPageView* SdrMarkList::GetPageView(USHORT nNum) const
//STRIP001 {
//STRIP001   return NULL;
//STRIP001 }

/*N*/ FASTBOOL SdrMarkList::TakeBoundRect(SdrPageView* pPV, Rectangle& rRect) const
/*N*/ {
/*N*/   FASTBOOL bFnd=FALSE;
/*N*/   Rectangle aR;
/*N*/
/*N*/   for (ULONG i=0; i<GetMarkCount(); i++) {
/*?*/       SdrMark* pMark=GetMark(i);
/*?*/       if (pPV==NULL || pMark->GetPageView()==pPV) {
/*?*/           aR=pMark->GetObj()->GetBoundRect();
/*?*/           if (bFnd) {
/*?*/               rRect.Union(aR);
/*?*/           } else {
/*?*/               rRect=aR;
/*?*/               bFnd=TRUE;
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/   return bFnd;
/*N*/ }

/*N*/ FASTBOOL SdrMarkList::TakeSnapRect(SdrPageView* pPV, Rectangle& rRect) const
/*N*/ {
/*N*/   FASTBOOL bFnd=FALSE;
/*N*/
/*N*/   for (ULONG i=0; i<GetMarkCount(); i++) {
/*?*/       SdrMark* pMark=GetMark(i);
/*?*/       if (pPV==NULL || pMark->GetPageView()==pPV) {
/*?*/           Rectangle aR(pMark->GetObj()->GetSnapRect());
/*?*/           if (bFnd) {
/*?*/               rRect.Union(aR);
/*?*/           } else {
/*?*/               rRect=aR;
/*?*/               bFnd=TRUE;
/*?*/           }
/*?*/       }
/*N*/   }
/*N*/   return bFnd;
/*N*/ }

}
