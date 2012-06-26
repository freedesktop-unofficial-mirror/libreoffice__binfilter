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

#ifndef _FORMS_DATE_HXX_
#define _FORMS_DATE_HXX_

#include "EditBase.hxx"
#include "limitedformats.hxx"
namespace binfilter {

//.........................................................................
namespace frm
{
//.........................................................................

//==================================================================
//= ODateModel
//==================================================================
class ODateModel
                :public OEditBaseModel
                ,public OLimitedFormats
                ,public ::comphelper::OAggregationArrayUsageHelper< ODateModel >
{
    ::com::sun::star::uno::Any      m_aSaveValue;
    sal_Bool            m_bDateTimeField;
    static sal_Int32    nDateHandle;

protected:
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type> _getTypes();

public:
    DECLARE_DEFAULT_LEAF_XTOR( ODateModel );

// stario::XPersistObject
    virtual ::rtl::OUString SAL_CALL getServiceName() throw ( ::com::sun::star::uno::RuntimeException );

    // ::com::sun::star::beans::XPropertySet
    virtual void SAL_CALL getFastPropertyValue(::com::sun::star::uno::Any& rValue, sal_Int32 nHandle ) const;
    virtual sal_Bool SAL_CALL convertFastPropertyValue(::com::sun::star::uno::Any& rConvertedValue, ::com::sun::star::uno::Any& rOldValue,
                                          sal_Int32 nHandle, const ::com::sun::star::uno::Any& rValue )
                                        throw(::com::sun::star::lang::IllegalArgumentException);
    virtual void SAL_CALL setFastPropertyValue_NoBroadcast(sal_Int32 nHandle, const ::com::sun::star::uno::Any& rValue) throw ( ::com::sun::star::uno::Exception);

// ::com::sun::star::lang::XServiceInfo
    IMPLEMENTATION_NAME(ODateModel);
    virtual StringSequence SAL_CALL getSupportedServiceNames() throw();

// ::com::sun::star::beans::XPropertySet
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo> SAL_CALL getPropertySetInfo() throw(::com::sun::star::uno::RuntimeException);
    virtual ::cppu::IPropertyArrayHelper& SAL_CALL getInfoHelper();

// OAggregationArrayUsageHelper
    virtual void fillProperties(
        ::com::sun::star::uno::Sequence< ::com::sun::star::beans::Property >& /* [out] */ _rProps,
        ::com::sun::star::uno::Sequence< ::com::sun::star::beans::Property >& /* [out] */ _rAggregateProps
        ) const;

    using OPropertySetHelper::getFastPropertyValue;

    IMPLEMENT_INFO_SERVICE()

protected:
    DECLARE_XCLONEABLE();
};

//==================================================================
//= ODateControl
//==================================================================
class ODateControl: public OBoundControl
{
protected:
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type> _getTypes();

public:
    ODateControl(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory>& _rxFactory);
    DECLARE_UNO3_AGG_DEFAULTS(ODateControl, OBoundControl);

// ::com::sun::star::lang::XServiceInfo
    IMPLEMENTATION_NAME(ODateControl);
    virtual StringSequence SAL_CALL getSupportedServiceNames() throw();
};

//.........................................................................
}   // namespace frm
//.........................................................................

}//end of namespace binfilter
#endif // _FORMS_DATE_HXX_

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
