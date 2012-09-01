/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#include "svdmark.hxx"
#include "svdorect.hxx" // GetMarkDescription
#include "svdstr.hrc"   // Namen aus der Resource
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ void SdrMarkList::ForceSort()
/*N*/ {
/*N*/   if (!bSorted) {
/*N*/       bSorted=TRUE;
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
/*N*/ }

/*N*/ bool SdrMarkList::DeletePageView(const SdrPageView& rPV)
/*N*/ {
/*N*/   bool bChgd=FALSE;
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






/*N*/ bool SdrMarkList::TakeBoundRect(SdrPageView* pPV, Rectangle& rRect) const
/*N*/ {
/*N*/   bool bFnd=FALSE;
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

/*N*/ bool SdrMarkList::TakeSnapRect(SdrPageView* pPV, Rectangle& rRect) const
/*N*/ {
/*N*/   bool bFnd=FALSE;
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

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
