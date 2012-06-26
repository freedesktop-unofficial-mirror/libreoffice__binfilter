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

#ifndef _FORMS_CURRENCY_HXX_
#define _FORMS_CURRENCY_HXX_

#include "EditBase.hxx"
namespace binfilter {

//.........................................................................
namespace frm
{
//.........................................................................

//==================================================================
//= OCurrencyModel
//==================================================================
class OCurrencyModel
                :public OEditBaseModel
                ,public ::comphelper::OAggregationArrayUsageHelper< OCurrencyModel >
{
    ::com::sun::star::uno::Any          m_aSaveValue;

    static sal_Int32    nValueHandle;

protected:
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type> _getTypes();

public:
    DECLARE_DEFAULT_LEAF_XTOR( OCurrencyModel );

    // ::com::sun::star::lang::XServiceInfo
    IMPLEMENTATION_NAME(OCurrencyModel);
    virtual StringSequence SAL_CALL getSupportedServiceNames() throw();

    // ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet>
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo> SAL_CALL getPropertySetInfo() throw(::com::sun::star::uno::RuntimeException);
    virtual ::cppu::IPropertyArrayHelper& SAL_CALL getInfoHelper();

    // ::com::sun::star::io::XPersistObject
    virtual ::rtl::OUString SAL_CALL getServiceName() throw ( ::com::sun ::star::uno::RuntimeException);

    // OAggregationArrayUsageHelper
    virtual void fillProperties(
        ::com::sun::star::uno::Sequence< ::com::sun::star::beans::Property >& /* [out] */ _rProps,
        ::com::sun::star::uno::Sequence< ::com::sun::star::beans::Property >& /* [out] */ _rAggregateProps
        ) const;
    IMPLEMENT_INFO_SERVICE()

protected:
    DECLARE_XCLONEABLE();

    void implConstruct();
};

//==================================================================
//= OCurrencyControl
//==================================================================
class OCurrencyControl: public OBoundControl
{
protected:
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type> _getTypes();

public:
    OCurrencyControl(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory>& _rxFactory);
    // ::com::sun::star::lang::XServiceInfo
    IMPLEMENTATION_NAME(OCurrencyControl);
    virtual StringSequence SAL_CALL getSupportedServiceNames() throw();
};

//.........................................................................
}   // namespace frm
//.........................................................................

}//end of namespace binfilter
#endif // _FORMS_CURRENCY_HXX_

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
