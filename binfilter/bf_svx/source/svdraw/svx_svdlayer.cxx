/*************************************************************************
 *
 *  $RCSfile: svx_svdlayer.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-20 04:58:55 $
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

#ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
#include <com/sun/star/uno/Sequence.hxx>
#endif

#include "svdlayer.hxx"
#include "svdio.hxx"
#include "svdmodel.hxx" // fuer Broadcasting
#include "svdglob.hxx"  // StringCache
#include "svdstr.hrc"   // Namen aus der Resource
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////
// SetOfByte
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ FASTBOOL SetOfByte::IsEmpty() const
/*N*/ {
/*N*/   for (USHORT i=0; i<32; i++) {
/*N*/       if (aData[i]!=0) return FALSE;
/*N*/   }
/*N*/   return TRUE;
/*N*/ }

//STRIP001 FASTBOOL SetOfByte::IsFull() const
//STRIP001 {
//STRIP001  for (USHORT i=0; i<32; i++) {
//STRIP001      if (aData[i]!=0xFF) return FALSE;
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

//STRIP001 USHORT SetOfByte::GetSetCount() const
//STRIP001 {
//STRIP001  USHORT i;
//STRIP001  USHORT nRet=0;
//STRIP001  for (i=0; i<32; i++) {
//STRIP001      BYTE a=aData[i];
//STRIP001      if (a!=0) {
//STRIP001          if (a & 0x80) nRet++;
//STRIP001          if (a & 0x40) nRet++;
//STRIP001          if (a & 0x20) nRet++;
//STRIP001          if (a & 0x10) nRet++;
//STRIP001          if (a & 0x08) nRet++;
//STRIP001          if (a & 0x04) nRet++;
//STRIP001          if (a & 0x02) nRet++;
//STRIP001          if (a & 0x01) nRet++;
//STRIP001      }
//STRIP001  }
//STRIP001  return nRet;
//STRIP001 }

//STRIP001 BYTE SetOfByte::GetSetBit(USHORT nNum) const
//STRIP001 {
//STRIP001  nNum++;
//STRIP001  USHORT i=0,j=0;
//STRIP001  USHORT nRet=0;
//STRIP001  while (j<nNum && i<256) {
//STRIP001      if (IsSet(BYTE(i))) j++;
//STRIP001      i++;
//STRIP001  }
//STRIP001  if (j==nNum) nRet=i-1;
//STRIP001  return BYTE(nRet);
//STRIP001 }

//STRIP001 USHORT SetOfByte::GetClearCount() const
//STRIP001 {
//STRIP001  return USHORT(256-GetSetCount());
//STRIP001 }

//STRIP001 BYTE SetOfByte::GetClearBit(USHORT nNum) const
//STRIP001 {
//STRIP001  nNum++;
//STRIP001  USHORT i=0,j=0;
//STRIP001  USHORT nRet=0;
//STRIP001  while (j<nNum && i<256) {
//STRIP001      if (!IsSet(BYTE(i))) j++;
//STRIP001      i++;
//STRIP001  }
//STRIP001  if (j==nNum) nRet=i-1;
//STRIP001  return BYTE(nRet);
//STRIP001 }

/*N*/ void SetOfByte::operator&=(const SetOfByte& r2ndSet)
/*N*/ {
/*N*/   for (unsigned i=0; i<32; i++) {
/*N*/       aData[i]&=r2ndSet.aData[i];
/*N*/   }
/*N*/ }

//STRIP001 void SetOfByte::operator|=(const SetOfByte& r2ndSet)
//STRIP001 {
//STRIP001  for (unsigned i=0; i<32; i++) {
//STRIP001      aData[i]|=r2ndSet.aData[i];
//STRIP001  }
//STRIP001 }

/** initialize this set with a uno sequence of sal_Int8
*/
/*N*/  void SetOfByte::PutValue( const ::com::sun::star::uno::Any & rAny )
/*N*/  {
/*N*/   ::com::sun::star::uno::Sequence< sal_Int8 > aSeq;
/*N*/   if( rAny >>= aSeq )
/*N*/   {
/*N*/       sal_Int16 nCount = (sal_Int16)aSeq.getLength();
/*N*/       if( nCount > 32 )
/*N*/           nCount = 32;
/*N*/
/*N*/       sal_Int16 nIndex;
/*N*/       for( nIndex = 0; nIndex < nCount; nIndex++ )
/*N*/       {
/*N*/           aData[nIndex] = static_cast<BYTE>(aSeq[nIndex]);
/*N*/       }
/*N*/
/*N*/       for( ; nIndex < 32; nIndex++ )
/*N*/       {
/*N*/           aData[nIndex] = 0;
/*N*/       }
/*N*/   }
/*N*/  }

/** returns a uno sequence of sal_Int8
*/
/*N*/ void SetOfByte::QueryValue( ::com::sun::star::uno::Any & rAny ) const
/*N*/ {
/*N*/   sal_Int16 nNumBytesSet = 0;
/*N*/   sal_Int16 nIndex;
/*N*/   for( nIndex = 31; nIndex >= 00; nIndex-- )
/*N*/   {
/*N*/       if( 0 != aData[nIndex] )
/*N*/       {
/*N*/           nNumBytesSet = nIndex + 1;
/*N*/           break;
/*N*/       }
/*N*/   }
/*N*/
/*N*/   ::com::sun::star::uno::Sequence< sal_Int8 > aSeq( nNumBytesSet );
/*N*/
/*N*/   for( nIndex = 0; nIndex < nNumBytesSet; nIndex++ )
/*N*/   {
/*N*/       aSeq[nIndex] = static_cast<sal_Int8>(aData[nIndex]);
/*N*/   }
/*N*/
/*N*/   rAny <<= aSeq;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// SdrLayer
////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 void SdrLayer::SetStandardLayer(FASTBOOL bStd)
//STRIP001 {
//STRIP001  nType=(UINT16)bStd;
//STRIP001  if (bStd) {
//STRIP001      aName=ImpGetResStr(STR_StandardLayerName);
//STRIP001  }
//STRIP001  if (pModel!=NULL) {
//STRIP001      SdrHint aHint(HINT_LAYERCHG);
//STRIP001      pModel->Broadcast(aHint);
//STRIP001      pModel->SetChanged();
//STRIP001  }
//STRIP001 }

/*N*/ void SdrLayer::SetName(const XubString& rNewName)
/*N*/ {
/*N*/   if(!rNewName.Equals(aName))
/*N*/   {
/*N*/       aName = rNewName;
/*N*/       nType = 0; // Userdefined
/*N*/
/*N*/       if(pModel)
/*N*/       {
/*N*/           SdrHint aHint(HINT_LAYERCHG);
/*N*/
/*N*/           pModel->Broadcast(aHint);
/*N*/           pModel->SetChanged();
/*N*/       }
/*N*/   }
/*N*/ }

//STRIP001 FASTBOOL SdrLayer::operator==(const SdrLayer& rCmpLayer) const
//STRIP001 {
//STRIP001  return (nID == rCmpLayer.nID
//STRIP001      && nType == rCmpLayer.nType
//STRIP001      && aName.Equals(rCmpLayer.aName));
//STRIP001 }

/*N*/ SvStream& operator>>(SvStream& rIn, SdrLayer& rLayer)
/*N*/ {
/*N*/   if(rIn.GetError())
/*?*/       return rIn;
/*N*/
/*N*/   SdrIOHeader aHead(rIn, STREAM_READ);
/*N*/
/*N*/   rIn >> rLayer.nID;
/*N*/
/*N*/   // UNICODE: rIn >> rLayer.aName;
/*N*/   rIn.ReadByteString(rLayer.aName);
/*N*/
/*N*/   if(aHead.GetVersion() >= 1)
/*N*/   {
/*N*/       // Das Standardlayerflag kam direkt nach der Betalieferung dazu
/*N*/       rIn >> rLayer.nType;
/*N*/
/*N*/       if(rLayer.nType == 1)
/*N*/       {DBG_ASSERT(0, "STRIP"); //STRIP001
//STRIP001 /*?*/            rLayer.aName = ImpGetResStr(STR_StandardLayerName);
/*N*/       }
/*N*/   }
/*N*/
/*N*/   if(aHead.GetVersion() <= 12)
/*N*/   {
/*N*/       // nType war lange Zeit nicht initiallisiert!
/*N*/       if(rLayer.nType > 1)
/*N*/           rLayer.nType = 0;
/*N*/   }
/*N*/
/*N*/   return rIn;
/*N*/ }

/*N*/ SvStream& operator<<(SvStream& rOut, const SdrLayer& rLayer)
/*N*/ {
/*N*/   SdrIOHeader aHead(rOut, STREAM_WRITE, SdrIOLayrID);
/*N*/
/*N*/   rOut << rLayer.nID;
/*N*/
/*N*/   // UNICODE: rOut << rLayer.aName;
/*N*/   rOut.WriteByteString(rLayer.aName);
/*N*/
/*N*/   rOut << rLayer.nType;
/*N*/
/*N*/   return rOut;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// SdrLayerSet
////////////////////////////////////////////////////////////////////////////////////////////////////

//STRIP001 FASTBOOL SdrLayerSet::operator==(const SdrLayerSet& rCmpLayerSet) const
//STRIP001 {
//STRIP001  return(aName.Equals(rCmpLayerSet.aName)
//STRIP001      && aMember == rCmpLayerSet.aMember
//STRIP001      && aExclude == rCmpLayerSet.aExclude);
//STRIP001 }

//STRIP001 void SdrLayerSet::Broadcast() const
//STRIP001 {
//STRIP001  if (pModel!=NULL) {
//STRIP001      SdrHint aHint(HINT_LAYERSETCHG);
//STRIP001      pModel->Broadcast(aHint);
//STRIP001      pModel->SetChanged();
//STRIP001  }
//STRIP001 }

/*?*/ SvStream& operator>>(SvStream& rIn, SdrLayerSet& rSet)
/*?*/ {
/*?*/   if(rIn.GetError())
/*?*/       return rIn;
/*?*/
/*?*/   SdrIOHeader aHead(rIn, STREAM_READ);
/*?*/
/*?*/   rIn >> rSet.aMember;
/*?*/   rIn >> rSet.aExclude;
/*?*/
/*?*/   // UNICODE: rIn >> rSet.aName;
/*?*/   rIn.ReadByteString(rSet.aName);
/*?*/
/*?*/   return rIn;
/*?*/ }

/*?*/ SvStream& operator<<(SvStream& rOut, const SdrLayerSet& rSet)
/*?*/ {
/*?*/   SdrIOHeader aHead(rOut, STREAM_WRITE, SdrIOLSetID);
/*?*/
/*?*/   rOut << rSet.aMember;
/*?*/   rOut << rSet.aExclude;
/*?*/
/*?*/   // UNICODE: rOut << rSet.aName;
/*?*/   rOut.WriteByteString(rSet.aName);
/*?*/
/*?*/   return rOut;
/*?*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// SdrLayerAdmin
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ SdrLayerAdmin::SdrLayerAdmin(SdrLayerAdmin* pNewParent):
/*N*/   aLayer(1024,16,16),
/*N*/   aLSets(1024,16,16),
/*N*/   pModel(NULL)
/*N*/ {
/*N*/   sal_Char aTextControls[] = "Controls";
/*N*/   aControlLayerName = String(aTextControls, sizeof(aTextControls-1));
/*N*/   pParent=pNewParent;
/*N*/ }

/*?*/ SdrLayerAdmin::SdrLayerAdmin(const SdrLayerAdmin& rSrcLayerAdmin):
/*?*/   aLayer(1024,16,16),
/*?*/   aLSets(1024,16,16),
/*?*/   pParent(NULL),
/*?*/   pModel(NULL)
/*?*/ {
/*?*/   sal_Char aTextControls[] = "Controls";
/*?*/   aControlLayerName = String(aTextControls, sizeof(aTextControls-1));
/*?*/   *this = rSrcLayerAdmin;
/*?*/ }

/*N*/ SdrLayerAdmin::~SdrLayerAdmin()
/*N*/ {
/*N*/   ClearLayer();
/*N*/   ClearLayerSets();
/*N*/ }

/*N*/ void SdrLayerAdmin::ClearLayer()
/*N*/ {
/*N*/   SdrLayer* pL;
/*N*/   pL=(SdrLayer*)aLayer.First();
/*N*/   while (pL!=NULL) {
/*N*/       delete pL;
/*N*/       pL=(SdrLayer*)aLayer.Next();
/*N*/   }
/*N*/   aLayer.Clear();
/*N*/ }

/*N*/ void SdrLayerAdmin::ClearLayerSets()
/*N*/ {
/*N*/   SdrLayerSet* pL;
/*N*/   pL=(SdrLayerSet*)aLSets.First();
/*N*/   while (pL!=NULL) {
/*?*/       delete pL;
/*?*/       pL=(SdrLayerSet*)aLSets.Next();
/*N*/   }
/*N*/   aLSets.Clear();
/*N*/ }

//STRIP001 const SdrLayerAdmin& SdrLayerAdmin::operator=(const SdrLayerAdmin& rSrcLayerAdmin)
//STRIP001 {
//STRIP001  ClearLayer();
//STRIP001  ClearLayerSets();
//STRIP001  pParent=rSrcLayerAdmin.pParent;
//STRIP001  USHORT i;
//STRIP001  USHORT nAnz=rSrcLayerAdmin.GetLayerCount();
//STRIP001  for (i=0; i<nAnz; i++) {
//STRIP001      aLayer.Insert(new SdrLayer(*rSrcLayerAdmin.GetLayer(i)),CONTAINER_APPEND);
//STRIP001  }
//STRIP001  nAnz=rSrcLayerAdmin.GetLayerSetCount();
//STRIP001  for (i=0; i<nAnz; i++) {
//STRIP001      aLSets.Insert(new SdrLayerSet(*rSrcLayerAdmin.GetLayerSet(i)),CONTAINER_APPEND);
//STRIP001  }
//STRIP001  return *this;
//STRIP001 }

//STRIP001 FASTBOOL SdrLayerAdmin::operator==(const SdrLayerAdmin& rCmpLayerAdmin) const
//STRIP001 {
//STRIP001  if (pParent!=rCmpLayerAdmin.pParent ||
//STRIP001      aLayer.Count()!=rCmpLayerAdmin.aLayer.Count() ||
//STRIP001      aLSets.Count()!=rCmpLayerAdmin.aLSets.Count()) return FALSE;
//STRIP001  FASTBOOL bOk=TRUE;
//STRIP001  USHORT nAnz=GetLayerCount();
//STRIP001  USHORT i=0;
//STRIP001  while (bOk && i<nAnz) {
//STRIP001      bOk=*GetLayer(i)==*rCmpLayerAdmin.GetLayer(i);
//STRIP001      i++;
//STRIP001  }
//STRIP001  nAnz=GetLayerSetCount();
//STRIP001  i=0;
//STRIP001  while (bOk && i<nAnz) {
//STRIP001      bOk=*GetLayerSet(i)==*rCmpLayerAdmin.GetLayerSet(i);
//STRIP001      i++;
//STRIP001  }
//STRIP001  return bOk;
//STRIP001 }

/*N*/ void SdrLayerAdmin::SetModel(SdrModel* pNewModel)
/*N*/ {
/*N*/   if (pNewModel!=pModel) {
/*N*/       pModel=pNewModel;
/*N*/       USHORT nAnz=GetLayerCount();
/*N*/       USHORT i;
/*N*/       for (i=0; i<nAnz; i++) {
/*?*/           GetLayer(i)->SetModel(pNewModel);
/*N*/       }
/*N*/       nAnz=GetLayerSetCount();
/*N*/       for (i=0; i<nAnz; i++) {
/*?*/           GetLayerSet(i)->SetModel(pNewModel);
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void SdrLayerAdmin::Broadcast(FASTBOOL bLayerSet) const
/*N*/ {
/*N*/   if (pModel!=NULL) {
/*N*/       SdrHint aHint(bLayerSet ? HINT_LAYERSETORDERCHG : HINT_LAYERORDERCHG);
/*N*/       pModel->Broadcast(aHint);
/*N*/       pModel->SetChanged();
/*N*/   }
/*N*/ }

/*?*/ SdrLayer* SdrLayerAdmin::RemoveLayer(USHORT nPos)
/*?*/ {
/*?*/   SdrLayer* pRetLayer=(SdrLayer*)(aLayer.Remove(nPos));
/*?*/   Broadcast(FALSE);
/*?*/   return pRetLayer;
/*?*/ }

/*N*/ SdrLayer* SdrLayerAdmin::NewLayer(const XubString& rName, USHORT nPos)
/*N*/ {
/*N*/   SdrLayerID nID=GetUniqueLayerID();
/*N*/   SdrLayer* pLay=new SdrLayer(nID,rName);
/*N*/   pLay->SetModel(pModel);
/*N*/   aLayer.Insert(pLay,nPos);
/*N*/   Broadcast(FALSE);
/*N*/   return pLay;
/*N*/ }

//STRIP001 SdrLayer* SdrLayerAdmin::NewStandardLayer(USHORT nPos)
//STRIP001 {
//STRIP001  SdrLayerID nID=GetUniqueLayerID();
//STRIP001  SdrLayer* pLay=new SdrLayer(nID,String());
//STRIP001  pLay->SetStandardLayer();
//STRIP001  pLay->SetModel(pModel);
//STRIP001  aLayer.Insert(pLay,nPos);
//STRIP001  Broadcast(FALSE);
//STRIP001  return pLay;
//STRIP001 }

//STRIP001 SdrLayer* SdrLayerAdmin::MoveLayer(USHORT nPos, USHORT nNewPos)
//STRIP001 {
//STRIP001  SdrLayer* pLayer=(SdrLayer*)(aLayer.Remove(nPos));
//STRIP001  if (pLayer!=NULL) {
//STRIP001      aLayer.Insert(pLayer,nNewPos);
//STRIP001  }
//STRIP001  Broadcast(FALSE);
//STRIP001  return pLayer;
//STRIP001 }

//STRIP001 void SdrLayerAdmin::MoveLayer(SdrLayer* pLayer, USHORT nNewPos)
//STRIP001 {
//STRIP001  ULONG nPos=aLayer.GetPos(pLayer);
//STRIP001  if (nPos!=CONTAINER_ENTRY_NOTFOUND) {
//STRIP001      aLayer.Remove(nPos);
//STRIP001      aLayer.Insert(pLayer,nNewPos);
//STRIP001      Broadcast(FALSE);
//STRIP001  }
//STRIP001 }

//STRIP001 USHORT SdrLayerAdmin::GetLayerPos(SdrLayer* pLayer) const
//STRIP001 {
//STRIP001  ULONG nRet=SDRLAYER_NOTFOUND;
//STRIP001  if (pLayer!=NULL) {
//STRIP001      nRet=aLayer.GetPos(pLayer);
//STRIP001      if (nRet==CONTAINER_ENTRY_NOTFOUND) {
//STRIP001          nRet=SDRLAYER_NOTFOUND;
//STRIP001      }
//STRIP001  }
//STRIP001  return USHORT(nRet);
//STRIP001 }

/*N*/ const SdrLayer* SdrLayerAdmin::GetLayer(const XubString& rName, FASTBOOL bInherited) const
/*N*/ {
/*N*/   UINT16 i(0);
/*N*/   const SdrLayer* pLay = NULL;
/*N*/
/*N*/   while(i < GetLayerCount() && !pLay)
/*N*/   {
/*N*/       if(rName.Equals(GetLayer(i)->GetName()))
/*N*/           pLay = GetLayer(i);
/*N*/       else
/*N*/           i++;
/*N*/   }
/*N*/
/*N*/   if(!pLay && pParent)
/*N*/   {
/*N*/       pLay = pParent->GetLayer(rName, TRUE);
/*N*/   }
/*N*/
/*N*/   return pLay;
/*N*/ }

/*N*/ SdrLayerID SdrLayerAdmin::GetLayerID(const XubString& rName, FASTBOOL bInherited) const
/*N*/ {
/*N*/   SdrLayerID nRet=SDRLAYER_NOTFOUND;
/*N*/   const SdrLayer* pLay=GetLayer(rName,bInherited);
/*N*/   if (pLay!=NULL) nRet=pLay->GetID();
/*N*/   return nRet;
/*N*/ }

/*N*/ const SdrLayer* SdrLayerAdmin::GetLayerPerID(USHORT nID) const
/*N*/ {
/*N*/   USHORT i=0;
/*N*/   const SdrLayer* pLay=NULL;
/*N*/   while (i<GetLayerCount() && pLay==NULL) {
/*N*/       if (nID==GetLayer(i)->GetID()) pLay=GetLayer(i);
/*N*/       else i++;
/*N*/   }
/*N*/   return pLay;
/*N*/ }

// Globale LayerID's beginnen mit 0 aufsteigend.
// Lokale LayerID's beginnen mit 254 absteigend.
// 255 ist reserviert fuer SDRLAYER_NOTFOUND

/*N*/ SdrLayerID SdrLayerAdmin::GetUniqueLayerID() const
/*N*/ {
/*N*/   SetOfByte aSet;
/*N*/   sal_Bool bDown = (pParent == NULL);
/*N*/   sal_Int32 j;
/*N*/   for (j=0; j<GetLayerCount(); j++)
/*N*/     {
/*N*/       aSet.Set(GetLayer(j)->GetID());
/*N*/   }
/*N*/   SdrLayerID i;
/*N*/   if (!bDown)
/*N*/     {
/*N*/       i=254;
/*N*/       while (i && aSet.IsSet(BYTE(i)))
/*N*/             --i;
/*N*/       if (i == 0)
/*N*/             i=254;
/*N*/   }
/*N*/     else
/*N*/     {
/*N*/       i=0;
/*N*/       while (i<=254 && aSet.IsSet(BYTE(i)))
/*N*/             i++;
/*N*/       if (i>254)
/*N*/             i=0;
/*N*/   }
/*N*/   return i;
/*N*/ }

//STRIP001 SdrLayerSet* SdrLayerAdmin::NewLayerSet(const XubString& rName, USHORT nPos)
//STRIP001 {
//STRIP001  SdrLayerSet* pSet=new SdrLayerSet(/**this,*/rName);
//STRIP001  pSet->SetModel(pModel);
//STRIP001  aLSets.Insert(pSet,nPos);
//STRIP001  Broadcast(TRUE);
//STRIP001  return pSet;
//STRIP001 }

//STRIP001 SdrLayerSet* SdrLayerAdmin::RemoveLayerSet(SdrLayerSet* pSet)
//STRIP001 {
//STRIP001  SdrLayerSet* pRetSet=(SdrLayerSet*)aLSets.Remove(pSet);
//STRIP001  Broadcast(TRUE);
//STRIP001  return pRetSet;
//STRIP001 }

//STRIP001 void SdrLayerAdmin::MoveLayerSet(SdrLayerSet* pSet, USHORT nNewPos)
//STRIP001 {
//STRIP001  ULONG nPos=aLSets.GetPos(pSet);
//STRIP001  if (nPos!=CONTAINER_ENTRY_NOTFOUND) {
//STRIP001      aLSets.Remove(nPos);
//STRIP001      aLSets.Insert(pSet,nNewPos);
//STRIP001      Broadcast(TRUE);
//STRIP001  }
//STRIP001 }

//STRIP001 const SdrLayerSet* SdrLayerAdmin::GetLayerSet(const XubString& rName, FASTBOOL bInherited) const
//STRIP001 {
//STRIP001  UINT16 i(0);
//STRIP001  const SdrLayerSet* pSet = NULL;
//STRIP001
//STRIP001  while(i <= GetLayerSetCount() && !pSet)
//STRIP001  {
//STRIP001      if(rName.Equals(GetLayerSet(i)->GetName()))
//STRIP001          pSet = GetLayerSet(i);
//STRIP001      else
//STRIP001          i++;
//STRIP001  }
//STRIP001
//STRIP001  if(!pSet && pParent)
//STRIP001  {
//STRIP001      pSet = pParent->GetLayerSet(rName, TRUE);
//STRIP001  }
//STRIP001
//STRIP001  return pSet;
//STRIP001 }

}
