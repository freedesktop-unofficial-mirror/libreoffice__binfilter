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

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "fmpage.hxx"

#include "fmmodel.hxx"

#ifndef SVX_LIGHT
#include "fmresids.hrc"
#endif

#ifndef SVX_LIGHT
#include "fmpgeimp.hxx"
#endif

#include "svdio.hxx"

#ifndef SVX_LIGHT
#include "fmprop.hrc"
using namespace ::binfilter::svxform;
#endif

namespace binfilter {

/*N*/ TYPEINIT1(FmFormPage, SdrPage);

//------------------------------------------------------------------
/*N*/ FmFormPage::FmFormPage(FmFormModel& rModel, StarBASIC* _pBasic, bool bMasterPage)
/*N*/          :SdrPage(rModel, bMasterPage)
/*N*/ #ifndef SVX_LIGHT
/*N*/          ,pImpl(new FmFormPageImpl(this))
/*N*/ #else
/*N*/          ,pImpl(NULL)
/*N*/ #endif
/*N*/          ,pBasic(_pBasic)
/*N*/ {
/*N*/ }

/*N*/ FmFormPage::~FmFormPage()
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   delete pImpl;
/*N*/ #endif
/*N*/ }

/*N*/ void FmFormPage::ReadData(const SdrIOHeader& rHead, SvStream& rIn)
/*N*/ {
/*N*/   {
/*N*/       {
/*N*/           SdrDownCompat aVCCompat1( rIn, STREAM_READ );
/*N*/       }
/*N*/       SdrPage::ReadData( rHead, rIn );
/*N*/       {
/*N*/           SdrDownCompat aVCCompat2( rIn, STREAM_READ );
/*N*/           aPageName = read_lenPrefixed_uInt8s_ToOUString<sal_uInt16>(rIn,
/*N*/               osl_getThreadTextEncoding());
/*N*/       }
/*N*/   }
/*N*/
/*N*/   // dont use the flag in that way: if (rIn.GetVersion() >= SOFFICE_FILEFORMAT_40)
/*N*/   if (rIn.GetVersion() >= 3830 && rHead.GetVersion() >=14)
/*N*/   {
/*N*/       SdrDownCompat aCompat(rIn, STREAM_READ);    // Fuer Abwaertskompatibilitaet (Lesen neuer Daten mit altem Code)
/*N*/ #ifndef SVX_LIGHT
/*N*/       DBG_ASSERT( aCompat.GetBytesLeft(), "FmFormPage::ReadData: invalid file format!" );
/*N*/       if ( aCompat.GetBytesLeft() )
/*N*/           pImpl->ReadData(rHead, rIn);
/*N*/       // some old (corrupted) versions between 511 and 554 wrote an empty block here - and some of these documents
/*N*/       // are still out there
/*N*/       // So we allow for such an empty block ...
/*N*/ #endif
/*N*/   }
/*N*/ }

//------------------------------------------------------------------
/*N*/ void FmFormPage::SetModel(SdrModel* pNewModel)
/*N*/ {
/*N*/   SdrPage::SetModel( pNewModel );
/*N*/ }

//------------------------------------------------------------------
/*N*/ SdrPage* FmFormPage::Clone() const
/*N*/ {
/*N*/   return new FmFormPage(*this);
/*N*/   // hier fehlt noch ein kopieren der Objekte
/*N*/ }

//------------------------------------------------------------------
/*N*/ void FmFormPage::InsertObject(SdrObject* pObj, ULONG nPos,
/*N*/                             const SdrInsertReason* pReason)
/*N*/ {
/*N*/   SdrPage::InsertObject( pObj, nPos, pReason );
/*N*/ }

//------------------------------------------------------------------
/*N*/ const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer > & FmFormPage::GetForms() const
/*N*/ {
/*N*/ #ifndef SVX_LIGHT
/*N*/   return pImpl->getForms();
/*N*/ #else
/*N*/   static ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer >  aRef;
/*N*/   return aRef;
/*N*/ #endif
/*N*/ }

//------------------------------------------------------------------
/*N*/ SdrObject* FmFormPage::RemoveObject(ULONG nObjNum)
/*N*/ {
/*N*/   SdrObject* pObj = SdrPage::RemoveObject(nObjNum);
/*N*/   return pObj;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
