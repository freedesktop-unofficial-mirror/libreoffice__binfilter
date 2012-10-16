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


#include "svdlayer.hxx"
#include "svdio.hxx"
#include "svdmodel.hxx" // fuer Broadcasting
#include "svdstr.hrc"   // Namen aus der Resource
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////
// SetOfByte
////////////////////////////////////////////////////////////////////////////////////////////////////

/*N*/ bool SetOfByte::IsEmpty() const
/*N*/ {
/*N*/   for (USHORT i=0; i<32; i++) {
/*N*/       if (aData[i]!=0) return FALSE;
/*N*/   }
/*N*/   return TRUE;
/*N*/ }






/*N*/ void SetOfByte::operator&=(const SetOfByte& r2ndSet)
/*N*/ {
/*N*/   for (unsigned i=0; i<32; i++) {
/*N*/       aData[i]&=r2ndSet.aData[i];
/*N*/   }
/*N*/ }


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
/*N*/   rLayer.aName = rIn.ReadUniOrByteString(rIn.GetStreamCharSet());
/*N*/
/*N*/   if(aHead.GetVersion() >= 1)
/*N*/   {
/*N*/       // Das Standardlayerflag kam direkt nach der Betalieferung dazu
/*N*/       rIn >> rLayer.nType;
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
/*N*/   rOut.WriteUniOrByteString(rLayer.aName, rOut.GetStreamCharSet());
/*N*/
/*N*/   rOut << rLayer.nType;
/*N*/
/*N*/   return rOut;
/*N*/ }

////////////////////////////////////////////////////////////////////////////////////////////////////
// SdrLayerSet
////////////////////////////////////////////////////////////////////////////////////////////////////



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
/*?*/   rSet.aName = rIn.ReadUniOrByteString(rIn.GetStreamCharSet());
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
/*?*/   rOut.WriteUniOrByteString(rSet.aName, rOut.GetStreamCharSet());
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
/*N*/   aControlLayerName = String(RTL_CONSTASCII_USTRINGPARAM("Controls"));
/*N*/   pParent=pNewParent;
/*N*/ }

/*?*/ SdrLayerAdmin::SdrLayerAdmin(const SdrLayerAdmin& rSrcLayerAdmin):
/*?*/   aLayer(1024,16,16),
/*?*/   aLSets(1024,16,16),
/*?*/   pParent(NULL),
/*?*/   pModel(NULL)
/*?*/ {
/*?*/   aControlLayerName = String(RTL_CONSTASCII_USTRINGPARAM("Controls"));
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

/*N*/ void SdrLayerAdmin::Broadcast(bool bLayerSet) const
/*N*/ {
/*N*/   if (pModel!=NULL) {
/*N*/       SdrHint aHint(bLayerSet ? HINT_LAYERSETORDERCHG : HINT_LAYERORDERCHG);
/*N*/       pModel->Broadcast(aHint);
/*N*/       pModel->SetChanged();
/*N*/   }
/*N*/ }

/*N*/ SdrLayer* SdrLayerAdmin::NewLayer(const XubString& rName, USHORT nPos)
/*N*/ {
/*N*/   SdrLayerID nID=GetUniqueLayerID();
/*N*/   SdrLayer* pLay=new SdrLayer(nID,rName);
/*N*/   pLay->SetModel(pModel);
/*N*/   aLayer.Insert(pLay,nPos);
/*N*/   Broadcast(FALSE);
/*N*/   return pLay;
/*N*/ }





/*N*/ const SdrLayer* SdrLayerAdmin::GetLayer(const XubString& rName, bool /*bInherited*/) const
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

/*N*/ SdrLayerID SdrLayerAdmin::GetLayerID(const XubString& rName, bool bInherited) const
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





}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
