/*************************************************************************
 *
 *  $RCSfile: svx_svdsuro.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:42 $
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

#include "svdsuro.hxx"
#include "svdobj.hxx"
#include "svdpage.hxx"
#include "svdmodel.hxx"

#ifndef _TOOLS_DEBUG_HXX //autogen
#include <tools/debug.hxx>
#endif
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////

// fuer Schreiben
/*N*/ SdrObjSurrogate::SdrObjSurrogate(SdrObject* pObj1, const SdrObject* pRefObj1)
/*N*/ {
/*N*/   ImpClearVars();
/*N*/   pObj=pObj1;
/*N*/   pRefObj=pRefObj1;
/*N*/   ImpMakeSurrogate();
/*N*/ }

// fuer Lesen
/*N*/ SdrObjSurrogate::SdrObjSurrogate(const SdrModel& rMod, SvStream& rIn)
/*N*/ {
/*N*/   ImpClearVars();
/*N*/   pModel=&rMod;
/*N*/   ImpRead(rIn);
/*N*/ }

// fuer Lesen
/*N*/ SdrObjSurrogate::SdrObjSurrogate(const SdrObject& rRefObj, SvStream& rIn)
/*N*/ {
/*N*/   ImpClearVars();
/*N*/   pRefObj=&rRefObj;
/*N*/   pModel=rRefObj.GetModel();
/*N*/   ImpRead(rIn);
/*N*/ }

/*N*/ SdrObjSurrogate::~SdrObjSurrogate()
/*N*/ {
/*N*/   if (pGrpOrdNums!=NULL) delete [] pGrpOrdNums;
/*N*/ }

/*N*/ void SdrObjSurrogate::ImpClearVars()
/*N*/ {
/*N*/   pObj=NULL;
/*N*/   pRefObj=NULL;
/*N*/   pList=NULL;
/*N*/   pRootList=NULL;
/*N*/   pPage=NULL;
/*N*/   pModel=NULL;
/*N*/   eList=SDROBJLIST_UNKNOWN;
/*N*/   nOrdNum=0;
/*N*/   pGrpOrdNums=NULL;
/*N*/   nGrpLevel=0;
/*N*/   nPageNum=0;
/*N*/ }

/*N*/ void SdrObjSurrogate::ImpMakeSurrogate()
/*N*/ {
/*N*/   if (pObj!=NULL) { // ansonsten bleibt eList=SDROBJLIST_UNKNOWN, weil Obj=NULL
/*N*/       FASTBOOL bSameList=FALSE;
/*N*/       FASTBOOL bSamePage=FALSE;
/*N*/       pModel=pObj->GetModel();
/*N*/       pList=pObj->GetObjList();
/*N*/       pRootList=pList;
/*N*/       pPage=pObj->GetPage();
/*N*/       nOrdNum=pObj->GetOrdNum();
/*N*/       DBG_ASSERT(pModel!=NULL,"ImpMakeSurrogate(): Zielobjekt hat kein Model");
/*N*/       DBG_ASSERT(pList!=NULL,"ImpMakeSurrogate(): Zielobjekt hat keine ObjList");
/*N*/       if (pModel!=NULL && pList!=NULL) {
/*N*/           if (pRefObj!=NULL) {
/*N*/               if (pList==pRefObj->GetObjList()) bSameList=TRUE;
/*N*/               else if (pPage!=NULL && pPage==pRefObj->GetPage()) bSamePage=TRUE;
/*N*/           }
/*N*/           if (!bSameList) {
/*N*/               //if (eList==SDROBJLIST_UNKNOWN) eList=pList->GetListKind();
/*N*/               SdrObjList* pL=pList->GetUpList();
/*N*/               nGrpLevel=0;
/*N*/               while (pL!=NULL) { pL=pL->GetUpList(); nGrpLevel++; }
/*N*/               if (nGrpLevel!=0) { DBG_BF_ASSERT(0, "STRIP"); //STRIP001 // Aha, verschachtelt
//STRIP001 /*?*/                    pGrpOrdNums=new UINT32[nGrpLevel];
//STRIP001 /*?*/                    const SdrObjList* pL=pRootList;
//STRIP001 /*?*/                    for (unsigned i=nGrpLevel; i>0;) {
//STRIP001 /*?*/                        i--;
//STRIP001 /*?*/                        SdrObject* pGrp=pL->GetOwnerObj();
//STRIP001 /*?*/                        if (pGrp!=NULL && pL->GetListKind()==SDROBJLIST_GROUPOBJ && pGrp->GetObjList()==pL->GetUpList() && pGrp->GetSubList()==pL) {
//STRIP001 /*?*/                            pGrpOrdNums[i]=pGrp->GetOrdNum();
//STRIP001 /*?*/                        } else { // sonst Fehlerhafte Verkettung
//STRIP001 /*?*/ #ifdef DBG_UTIL
//STRIP001 /*?*/                            ByteString aStr("ImpMakeSurrogate() - Inkonsistente Verkettung:\n");
//STRIP001 /*?*/                            String aStr1;
//STRIP001 /*?*/
//STRIP001 /*?*/                            pObj->TakeObjNameSingul(aStr1);
//STRIP001 /*?*/
//STRIP001 /*?*/                            aStr += "Schleifendurchlauf=";
//STRIP001 /*?*/                            aStr += ByteString::CreateFromInt32( i );
//STRIP001 /*?*/                            aStr += " GroupingLevel=";
//STRIP001 /*?*/                            aStr += ByteString::CreateFromInt32( nGrpLevel );
//STRIP001 /*?*/                            aStr += " Ordnumgszahl=";
//STRIP001 /*?*/                            aStr += ByteString::CreateFromInt32( pObj->GetOrdNum() );
//STRIP001 /*?*/                            aStr += "\nObjektbezeichnung='";
//STRIP001 /*?*/                            aStr += ByteString(aStr1, gsl_getSystemTextEncoding());
//STRIP001 /*?*/                            aStr += "'\n";
//STRIP001 /*?*/
//STRIP001 /*?*/                            if(pGrp)
//STRIP001 /*?*/                                aStr += "\n- Liste mit Parent hat kein OwnerObj.";
//STRIP001 /*?*/
//STRIP001 /*?*/                            if(pL->GetListKind()==SDROBJLIST_GROUPOBJ)
//STRIP001 /*?*/                                aStr += "\n- Liste mit Parent liefert ListKind!=SDROBJLIST_GROUPOBJ.";
//STRIP001 /*?*/
//STRIP001 /*?*/                            if(pGrp && pGrp->GetObjList() == pL->GetUpList())
//STRIP001 /*?*/                                aStr += "\n- ObjList des OwnerObj und ParentList seiner SubList sind nicht identisch.";
//STRIP001 /*?*/
//STRIP001 /*?*/                            if(pGrp && pGrp->GetSubList() == pL)
//STRIP001 /*?*/                                aStr += "\n- Sublist des OwnerObj des OwnerObj entspricht nicht der Liste selbst.";
//STRIP001 /*?*/
//STRIP001 /*?*/                            DBG_ERROR(aStr.GetBuffer());
//STRIP001 /*?*/ #endif
//STRIP001 /*?*/                            delete [] pGrpOrdNums;
//STRIP001 /*?*/                            pGrpOrdNums=NULL;
//STRIP001 /*?*/                            nGrpLevel=0;
//STRIP001 /*?*/                            return;
//STRIP001 /*?*/                        }
//STRIP001 /*?*/                        pL=pL->GetUpList();
//STRIP001 /*?*/                    }
//STRIP001 /*?*/                    pRootList=pL;
//STRIP001 /*?*/                    if (pL==NULL || pL->GetUpList()!=NULL || pL->GetOwnerObj()!=NULL || pL->GetListKind()==SDROBJLIST_GROUPOBJ) {
//STRIP001 /*?*/                        delete [] pGrpOrdNums;
//STRIP001 /*?*/                        pGrpOrdNums=NULL;
//STRIP001 /*?*/                        nGrpLevel=0;
//STRIP001 /*?*/                        return;
//STRIP001 /*?*/                    }
/*N*/               } // if (nGrpLevel!=0)
/*N*/           } // if (eList!=SDROBJLIST_SAMELIST)
/*N*/           if (bSameList) eList=SDROBJLIST_SAMELIST;
/*N*/           else if (bSamePage) eList=SDROBJLIST_SAMEPAGE;
/*N*/           else eList=pRootList->GetListKind();
/*N*/           if (eList==SDROBJLIST_GROUPOBJ || eList==SDROBJLIST_UNKNOWN) {
/*?*/               if (pGrpOrdNums!=NULL) {
/*?*/                   delete [] pGrpOrdNums;
/*?*/                   pGrpOrdNums=NULL;
/*?*/                   nGrpLevel=0;
/*?*/               }
/*?*/               eList=SDROBJLIST_UNKNOWN;
/*?*/               return;
/*N*/           }
/*N*/           if (SdrIsPageKind(eList)) {
/*N*/               if (pPage!=NULL) {
/*N*/                   nPageNum=pPage->GetPageNum();
/*N*/               } else {
/*?*/                   DBG_ERROR("ImpMakeSurrogate(): eList ist eine Page, aber pPage==NULL");
/*?*/                   if (pGrpOrdNums!=NULL) {
/*?*/                       delete [] pGrpOrdNums;
/*?*/                       pGrpOrdNums=NULL;
/*?*/                       nGrpLevel=0;
/*N*/                   }
/*N*/                   eList=SDROBJLIST_UNKNOWN;
/*N*/                   return;
/*N*/               }
/*N*/           }
/*N*/           // so, nun ist alles beisammen und kann gestreamt werden.
/*N*/       } // if (pModel!=NULL && pList!=NULL)
/*N*/   } // if (pObj!=NULL)
/*N*/ }

/*N*/ void SdrObjSurrogate::ImpWriteValue(SvStream& rOut, UINT32 nVal, unsigned nByteAnz) const
/*N*/ {
/*N*/   switch (nByteAnz) {
/*N*/       case 0: rOut<<BYTE(nVal);   break;
/*N*/       case 1: rOut<<UINT16(nVal); break;
/*N*/       case 3: rOut<<nVal;         break;
/*N*/       default: DBG_ERROR("ImpWriteValue(): Nur Bytelaengen 1, 2 oder 4 sind erlaubt!");
/*N*/   } // switch
/*N*/ }

/*N*/ void SdrObjSurrogate::ImpReadValue(SvStream& rIn, UINT32& rVal, unsigned nByteAnz) const
/*N*/ {
/*N*/   switch (nByteAnz) {
/*N*/       case 0: { BYTE n;   rIn>>n; rVal=n; } break;
/*N*/       case 1: { UINT16 n; rIn>>n; rVal=n; } break;
/*N*/       case 3: {           rIn>>rVal;      } break;
/*N*/       default: DBG_ERROR("ImpReadValue(): Nur Bytelaengen 1, 2 oder 4 sind erlaubt!");
/*N*/   } // switch
/*N*/ }

/*N*/ SvStream& operator<<(SvStream& rOut, const SdrObjSurrogate& rSurro)
/*N*/ {
/*N*/   BYTE nId=BYTE(rSurro.eList);
/*N*/   if (rSurro.eList==SDROBJLIST_UNKNOWN) {
/*N*/       rOut<<nId;
/*N*/   } else {
/*N*/       FASTBOOL bGrp=rSurro.nGrpLevel!=0;
/*N*/       if (bGrp) nId|=0x20; // Gruppierung
/*N*/       ULONG nMaxOrdNum=rSurro.nOrdNum;
/*N*/       unsigned i;
/*N*/       for (i=0; i<rSurro.nGrpLevel; i++) {
/*?*/           if (nMaxOrdNum<rSurro.pGrpOrdNums[i]) nMaxOrdNum=rSurro.pGrpOrdNums[i];
/*N*/       }
/*N*/       unsigned nByteAnz=0;
/*N*/       if (nMaxOrdNum>0xFF) nByteAnz++;
/*N*/       if (nMaxOrdNum>0xFFFF) nByteAnz+=2;
/*N*/       nId|=BYTE(nByteAnz<<6); // Byteanzahl an der richtigen Stelle im ID-Byte eintragen
/*N*/       rOut<<nId;
/*N*/       rSurro.ImpWriteValue(rOut,rSurro.nOrdNum,nByteAnz);
/*N*/       if (SdrIsPageKind(rSurro.eList)) { // Seitennummer schreiben
/*N*/           rOut<<rSurro.nPageNum;
/*N*/       }
/*N*/       if (bGrp) { // Gruppierung
/*?*/           rOut<<rSurro.nGrpLevel;
/*?*/           for (i=0; i<rSurro.nGrpLevel; i++) {
/*?*/               rSurro.ImpWriteValue(rOut,rSurro.pGrpOrdNums[i],nByteAnz);
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/   return rOut;
/*N*/ }

/*N*/ void SdrObjSurrogate::ImpRead(SvStream& rIn)
/*N*/ {
/*N*/   BYTE nId;
/*N*/   rIn>>nId;
/*N*/   eList=SdrObjListKind(nId & 0x1F);
/*N*/   if (eList!=SDROBJLIST_UNKNOWN) {
/*N*/       FASTBOOL bGrp=(nId & 0x20)!=0;      // Id-Byte
/*N*/       unsigned nByteAnz=(nId & 0xC0)>>6;  // aufschluesseln
/*N*/       ImpReadValue(rIn,nOrdNum,nByteAnz); // Ordnungsnummer des Objekts
/*N*/       if (SdrIsPageKind(eList)) { // Seitennummer schreiben
/*N*/           rIn>>nPageNum;
/*N*/       }
/*N*/       if (bGrp) { // Gruppierung
/*?*/           rIn>>nGrpLevel;
/*?*/           pGrpOrdNums=new UINT32[nGrpLevel];
/*?*/           for (unsigned i=0; i<nGrpLevel; i++) {
/*?*/               ImpReadValue(rIn,pGrpOrdNums[i],nByteAnz);
/*?*/           }
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void SdrObjSurrogate::ImpFindObj()
/*N*/ {
/*N*/   if (eList!=SDROBJLIST_UNKNOWN) {
/*N*/       switch (eList) {
/*N*/           case SDROBJLIST_SAMEPAGE: case SDROBJLIST_SAMELIST: {
/*N*/               if (pRefObj!=NULL) {
/*N*/                   pPage=pRefObj->GetPage();
/*N*/                   if (eList==SDROBJLIST_SAMELIST) {
/*N*/                       pRootList=pRefObj->GetObjList();
/*N*/                       if (pRootList==NULL) {
/*N*/                           DBG_ERROR("SdrObjSurrogate::ImpFindObj(): eList=SDROBJLIST_SAMELIST, pRefObj hat jedoch keine ObjList");
/*N*/                           return;
/*N*/                       }
/*N*/                   } else {
/*N*/                       if (pPage!=NULL) {
/*N*/                           pRootList=pPage;
/*N*/                       } else {
/*N*/                           DBG_ERROR("SdrObjSurrogate::ImpFindObj(): eList=SDROBJLIST_SAMEPAGE, pRefObj hat jedoch keine Page");
/*N*/                           return;
/*N*/                       }
/*N*/                   }
/*N*/               } else {
/*N*/                   DBG_ERROR("SdrObjSurrogate::ImpFindObj(): Relatives Surrogat benoetigt Referenzobjekt");
/*N*/                   return;
/*N*/               }
/*N*/           } break;
/*N*/           case SDROBJLIST_DRAWPAGE: pPage=pModel->GetPage(nPageNum); pRootList=pPage; break;
/*N*/           case SDROBJLIST_MASTERPAGE: pPage=pModel->GetMasterPage(nPageNum); pRootList=pPage; break;
/*N*/           case SDROBJLIST_VIRTOBJECTS: {
/*N*/               DBG_ERROR("SdrObjSurrogate::ImpFindObj(): Persistente virtuelle Objekte in dieser Version nicht verfuegbar");
/*N*/               return;
/*N*/           } break;
/*N*/           case SDROBJLIST_SYMBOLTABLE: {
/*N*/               DBG_ERROR("SdrObjSurrogate::ImpFindObj(): Symbole in dieser Version nicht verfuegbar");
/*N*/               return;
/*N*/           } break;
/*N*/           default: {
/*N*/               DBG_ERROR("SdrObjSurrogate::ImpFindObj(): Unbekannter oder unsinniger Objektlistentyp");
/*N*/               return;
/*N*/           }
/*N*/       } // switch
/*N*/       pList=pRootList;
/*N*/       for (unsigned i=0; i<nGrpLevel; i++) {
/*?*/           SdrObject* pO=pList->GetObj(pGrpOrdNums[i]);
/*?*/           if (pO!=NULL) {
/*?*/               pList=pO->GetSubList();
/*?*/               if (pList==NULL) {
/*?*/                   DBG_ERROR("SdrObjSurrogate::ImpFindObj(): Objekt ist kein Gruppenobjekt");
/*?*/                   return;
/*?*/               }
/*?*/           } else {
/*?*/               DBG_ERROR("SdrObjSurrogate::ImpFindObj(): Gruppenobjekt nicht gefunden");
/*?*/               return;
/*?*/           }
/*N*/       }
/*N*/       pObj=pList->GetObj(nOrdNum);
/*N*/       DBG_ASSERT(pObj!=NULL,"SdrObjSurrogate::ImpFindObj(): Zielobjekt nicht gefunden");
/*N*/   }
/*N*/ }

/*N*/ SdrObject* SdrObjSurrogate::GetObject()
/*N*/ {
/*N*/   if (pObj==NULL && eList!=SDROBJLIST_UNKNOWN) ImpFindObj();
/*N*/   return pObj;
/*N*/ }


}
