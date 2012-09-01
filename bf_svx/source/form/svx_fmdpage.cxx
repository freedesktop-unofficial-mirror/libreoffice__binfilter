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

#include "fmobj.hxx"

#include "fmglob.hxx"

#include "fmdpage.hxx"

#include "unoshape.hxx"
#include "fmimplids.hxx"
namespace binfilter {

/*N*/ DBG_NAME(SvxFmDrawPage)
/*N*/ SvxFmDrawPage::SvxFmDrawPage( SdrPage* pInPage ) :
/*N*/   SvxDrawPage( pInPage )
/*N*/ {
/*N*/   DBG_CTOR(SvxFmDrawPage,NULL);
    /*N*/   m_pHoldImplIdHelper = new ::binfilter::form::OImplementationIdsRef();
/*N*/ }

/*N*/ SvxFmDrawPage::~SvxFmDrawPage() throw ()
/*N*/ {
/*N*/   delete m_pHoldImplIdHelper;
/*N*/   DBG_DTOR(SvxFmDrawPage,NULL);
/*N*/ }

::com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL SvxFmDrawPage::getImplementationId() throw(::com::sun::star::uno::RuntimeException)
{
    DBG_BF_ASSERT(0, "STRIP");  // VIRTUAL
    ::com::sun::star::uno::Sequence< sal_Int8 > a;
    return a;
}

/*N*/ ::com::sun::star::uno::Any SAL_CALL SvxFmDrawPage::queryAggregation( const ::com::sun::star::uno::Type& aType ) throw(::com::sun::star::uno::RuntimeException)
/*N*/ {
/*N*/   ::com::sun::star::uno::Any aRet = ::cppu::queryInterface(aType,
/*N*/       static_cast< ::com::sun::star::form::XFormsSupplier*>(this));
/*N*/   if(aRet.hasValue())
/*N*/       return aRet;
/*N*/
/*N*/   return SvxDrawPage::queryAggregation(aType);
/*N*/ }

/***********************************************************************
*                                                                      *
***********************************************************************/

/*N*/ SdrObject *SvxFmDrawPage::_CreateSdrObject( const ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape > & xDescr ) throw ()
/*N*/ {
/*N*/   ::rtl::OUString aShapeType( xDescr->getShapeType() );
/*N*/
/*N*/   if (aShapeType  ==  ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.drawing.ShapeControl" )))
/*?*/       return new FmFormObj(OBJ_FM_CONTROL);
/*N*/   else
/*N*/       return SvxDrawPage::_CreateSdrObject( xDescr );
/*N*/
/*N*/ }

/*N*/ ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape >  SvxFmDrawPage::_CreateShape( SdrObject *pObj ) const throw ()
/*N*/ {
/*N*/   if( FmFormInventor == pObj->GetObjInventor() )
/*N*/   {
/*N*/       ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape >  xShape = (SvxShape*)new SvxShapeControl( pObj );
/*N*/       return xShape;
/*N*/   }
/*N*/   else
/*N*/       return SvxDrawPage::_CreateShape( pObj );
/*N*/ }

// ::com::sun::star::form::XFormsSupplier
/*N*/ ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer > SAL_CALL SvxFmDrawPage::getForms(void) throw( ::com::sun::star::uno::RuntimeException )
/*N*/ {
/*N*/   ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer >  xForms;
/*N*/
/*N*/   FmFormPage *pFmPage = PTR_CAST( FmFormPage, GetSdrPage() );
/*N*/   if( pFmPage )
/*N*/       xForms = pFmPage->GetForms();
/*N*/
/*N*/   return xForms;
/*N*/ }

// ::com::sun::star::lang::XServiceInfo
/*N*/ ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL SvxFmDrawPage::getSupportedServiceNames(void) throw( ::com::sun::star::uno::RuntimeException )
/*N*/ {
    /* TODO: DG? Irgendwelche Services?
    ::com::sun::star::uno::Sequence aSeq( SvxDrawPage::getSupportedServiceNames() );
    addToSequence( aSeq, 1, ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "stardiv.form.superservice?" )) );
    return aSeq;
    */
/*N*/
/*N*/   return SvxDrawPage::getSupportedServiceNames();
/*N*/ }


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
