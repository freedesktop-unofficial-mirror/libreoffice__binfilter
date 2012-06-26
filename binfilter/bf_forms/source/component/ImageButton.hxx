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

#ifndef _FRM_IMAGE_BUTTON_HXX_
#define _FRM_IMAGE_BUTTON_HXX_

#include "Image.hxx"

#include <com/sun/star/awt/XMouseListener.hpp>
namespace binfilter {

//.........................................................................
namespace frm
{
//.........................................................................

//==================================================================
// OImageButtonModel
//==================================================================
class OImageButtonModel
        :public OImageModel
        ,public ::comphelper::OAggregationArrayUsageHelper< OImageButtonModel >
{
public:
    DECLARE_DEFAULT_LEAF_XTOR( OImageButtonModel );

// ::com::sun::star::lang::XServiceInfo
    IMPLEMENTATION_NAME(OImageButtonModel);
    virtual StringSequence SAL_CALL getSupportedServiceNames() throw();

// ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet>
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo> SAL_CALL getPropertySetInfo() throw(::com::sun::star::uno::RuntimeException);
    virtual ::cppu::IPropertyArrayHelper& SAL_CALL getInfoHelper();

// ::com::sun::star::io::XPersistObject
    virtual ::rtl::OUString SAL_CALL getServiceName() throw ( ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL write(const ::com::sun::star::uno::Reference< ::com::sun::star::io::XObjectOutputStream>& _rxOutStream) throw ( ::com::sun::star::io::IOException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL read(const ::com::sun::star::uno::Reference< ::com::sun::star::io::XObjectInputStream>& _rxInStream) throw ( ::com::sun::star::io::IOException, ::com::sun::star::uno::RuntimeException);

// OAggregationArrayUsageHelper
    virtual void fillProperties(
        ::com::sun::star::uno::Sequence< ::com::sun::star::beans::Property >& /* [out] */ _rProps,
        ::com::sun::star::uno::Sequence< ::com::sun::star::beans::Property >& /* [out] */ _rAggregateProps
        ) const;
    IMPLEMENT_INFO_SERVICE()

protected:
    DECLARE_XCLONEABLE();
};

//==================================================================
// OImageButtonControl
//==================================================================
typedef ::cppu::ImplHelper1< ::com::sun::star::awt::XMouseListener> OImageButtonControl_BASE;
class OImageButtonControl : public OImageControl,
                            public OImageButtonControl_BASE
{
protected:
    // UNO Anbindung
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type> _getTypes();

public:
    OImageButtonControl(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory>& _rxFactory);

// ::com::sun::star::lang::XServiceInfo
    IMPLEMENTATION_NAME(OImageButtonControl);
    virtual StringSequence SAL_CALL getSupportedServiceNames() throw();

    // UNO Anbindung
    DECLARE_UNO3_AGG_DEFAULTS(OImageButtonControl, OImageControl);
    virtual ::com::sun::star::uno::Any SAL_CALL queryAggregation(const ::com::sun::star::uno::Type& _rType) throw(::com::sun::star::uno::RuntimeException);

// ::com::sun::star::lang::XEventListener
    virtual void SAL_CALL disposing(const ::com::sun::star::lang::EventObject& _rSource) throw(::com::sun::star::uno::RuntimeException)
        { OControl::disposing(_rSource); }

    using OImageControl::disposing;

// ::com::sun::star::awt::XMouseListener
    virtual void SAL_CALL mousePressed(const ::com::sun::star::awt::MouseEvent& /*e*/) throw ( ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL mouseReleased(const ::com::sun::star::awt::MouseEvent& /*e*/) throw ( ::com::sun::star::uno::RuntimeException) { }
    virtual void SAL_CALL mouseEntered(const ::com::sun::star::awt::MouseEvent& /*e*/) throw ( ::com::sun::star::uno::RuntimeException) { }
    virtual void SAL_CALL mouseExited(const ::com::sun::star::awt::MouseEvent& /*e*/) throw ( ::com::sun::star::uno::RuntimeException) { }
};

//.........................................................................
}   // namespace frm
//.........................................................................

}//end of namespace binfilter
#endif // _FRM_IMAGE_BUTTON_HXX_

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
