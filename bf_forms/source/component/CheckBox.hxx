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

#ifndef _FORMS_CHECKBOX_HXX_
#define _FORMS_CHECKBOX_HXX_

#include "FormComponent.hxx"

#include <comphelper/propmultiplex.hxx>
namespace binfilter {

//.........................................................................
namespace frm
{

enum { CB_NOCHECK, CB_CHECK, CB_DONTKNOW };

//==================================================================
//= OCheckBoxModel
//==================================================================
class OCheckBoxModel    :public OBoundControlModel
                        ,public OPropertyChangeListener
                        ,public ::comphelper::OAggregationArrayUsageHelper< OCheckBoxModel >
{
    ::rtl::OUString     m_sReferenceValue;  // Referenzwert zum Checken des Buttons
    sal_Int16           m_nDefaultChecked;      // Soll beim Reset gecheckt werden ?
    sal_Bool            m_bInReset;

    OPropertyChangeMultiplexer* m_pAggregatePropertyMultiplexer;

protected:
    sal_Int16   getState(const ::com::sun::star::uno::Any& rValue);

    virtual ::com::sun::star::uno::Any  _getControlValue() const;

public:
    DECLARE_DEFAULT_LEAF_XTOR( OCheckBoxModel );

    // XServiceInfo
    IMPLEMENTATION_NAME(OCheckBoxModel);
    virtual StringSequence SAL_CALL getSupportedServiceNames() throw(::com::sun::star::uno::RuntimeException);

    // OPropertySetHelper
    virtual void SAL_CALL getFastPropertyValue(::com::sun::star::uno::Any& rValue, sal_Int32 nHandle) const;
    virtual void SAL_CALL setFastPropertyValue_NoBroadcast( sal_Int32 nHandle, const ::com::sun::star::uno::Any& rValue )
                throw (::com::sun::star::uno::Exception);
    virtual sal_Bool SAL_CALL convertFastPropertyValue(
                ::com::sun::star::uno::Any& _rConvertedValue, ::com::sun::star::uno::Any& _rOldValue, sal_Int32 _nHandle, const ::com::sun::star::uno::Any& _rValue )
                throw (::com::sun::star::lang::IllegalArgumentException);

    // XPropertySetRef
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo> SAL_CALL getPropertySetInfo() throw(::com::sun::star::uno::RuntimeException);
    virtual cppu::IPropertyArrayHelper& SAL_CALL getInfoHelper();

    // XPersistObject
    virtual ::rtl::OUString SAL_CALL    getServiceName() throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL
        write(const ::com::sun::star::uno::Reference< ::com::sun::star::io::XObjectOutputStream>& _rxOutStream) throw(::com::sun::star::io::IOException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL
        read(const ::com::sun::star::uno::Reference< ::com::sun::star::io::XObjectInputStream>& _rxInStream) throw(::com::sun::star::io::IOException, ::com::sun::star::uno::RuntimeException);

    // OPropertyChangeListener
    virtual void _propertyChanged(const ::com::sun::star::beans::PropertyChangeEvent& evt) throw(::com::sun::star::uno::RuntimeException);

    // XReset
    virtual void SAL_CALL reset() throw(::com::sun::star::uno::RuntimeException);

// OAggregationArrayUsageHelper
    virtual void fillProperties(
        ::com::sun::star::uno::Sequence< ::com::sun::star::beans::Property >& /* [out] */ _rProps,
        ::com::sun::star::uno::Sequence< ::com::sun::star::beans::Property >& /* [out] */ _rAggregateProps
        ) const;
    IMPLEMENT_INFO_SERVICE()

protected:
    virtual void SAL_CALL disposing();
    using OBoundControlModel::disposing;
    using OPropertySetHelper::getFastPropertyValue;

protected:
    void implConstruct();

    DECLARE_XCLONEABLE();
};

//==================================================================
//= OCheckBoxControl
//==================================================================
class OCheckBoxControl : public OBoundControl
{
public:
    OCheckBoxControl(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory>& _rxFactory);

    // XServiceInfo
    IMPLEMENTATION_NAME(OCheckBoxControl);
    virtual StringSequence SAL_CALL getSupportedServiceNames() throw(::com::sun::star::uno::RuntimeException);
};

//.........................................................................
}
//.........................................................................

}//end of namespace binfilter
#endif // _FORMS_CHECKBOX_HXX_

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
