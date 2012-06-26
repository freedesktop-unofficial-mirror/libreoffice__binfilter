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

#include <comphelper/proparrhlp.hxx>
#include "Numeric.hxx"
#include <com/sun/star/beans/PropertyAttribute.hpp>
#include "services.hxx"
#include <com/sun/star/form/FormComponentType.hpp>

namespace binfilter {

//.........................................................................
namespace frm
{
//.........................................................................
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::form;
using namespace ::com::sun::star::awt;
using namespace ::com::sun::star::io;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::util;

//==================================================================
// ONumericControl
//==================================================================

//------------------------------------------------------------------
ONumericControl::ONumericControl(const Reference<XMultiServiceFactory>& _rxFactory)
    :OBoundControl(_rxFactory, VCL_CONTROL_NUMERICFIELD)
{
}

//------------------------------------------------------------------------------
StringSequence ONumericControl::getSupportedServiceNames() throw()
{
    StringSequence aSupported = OBoundControl::getSupportedServiceNames();
    aSupported.realloc(aSupported.getLength() + 1);

    ::rtl::OUString*pArray = aSupported.getArray();
    pArray[aSupported.getLength()-1] = FRM_SUN_CONTROL_NUMERICFIELD;
    return aSupported;
}


//------------------------------------------------------------------
InterfaceRef SAL_CALL ONumericControl_CreateInstance(const Reference<XMultiServiceFactory>& _rxFactory)
{
    return *(new ONumericControl(_rxFactory));
}

//------------------------------------------------------------------------------
Sequence<Type> ONumericControl::_getTypes()
{
    return OBoundControl::_getTypes();
}

//==================================================================
// ONumericModel
//==================================================================
sal_Int32   ONumericModel::nValueHandle = -1;
//------------------------------------------------------------------
InterfaceRef SAL_CALL ONumericModel_CreateInstance(const Reference<XMultiServiceFactory>& _rxFactory)
{
    return *(new ONumericModel(_rxFactory));
}

//------------------------------------------------------------------------------
Sequence<Type> ONumericModel::_getTypes()
{
    return OEditBaseModel::_getTypes();
}

//------------------------------------------------------------------
DBG_NAME( ONumericModel )
//------------------------------------------------------------------
ONumericModel::ONumericModel(const Reference<XMultiServiceFactory>& _rxFactory)
                :OEditBaseModel(_rxFactory, VCL_CONTROLMODEL_NUMERICFIELD, FRM_CONTROL_NUMERICFIELD)
                                    // use the old control name for compytibility reasons
{
    DBG_CTOR( ONumericModel, NULL );

    m_nClassId = FormComponentType::NUMERICFIELD;
    m_sDataFieldConnectivityProperty = PROPERTY_VALUE;
    if (ONumericModel::nValueHandle == -1)
        ONumericModel::nValueHandle = getOriginalHandle(PROPERTY_ID_VALUE);
}

//------------------------------------------------------------------
ONumericModel::ONumericModel( const ONumericModel* _pOriginal, const Reference<XMultiServiceFactory>& _rxFactory )
    :OEditBaseModel( _pOriginal, _rxFactory )
{
    DBG_CTOR( ONumericModel, NULL );
}

//------------------------------------------------------------------
ONumericModel::~ONumericModel()
{
    DBG_DTOR( ONumericModel, NULL );
}

// XCloneable
//------------------------------------------------------------------------------
IMPLEMENT_DEFAULT_CLONING( ONumericModel )

// XServiceInfo
//------------------------------------------------------------------------------
StringSequence ONumericModel::getSupportedServiceNames() throw()
{
    StringSequence aSupported = OBoundControlModel::getSupportedServiceNames();
    aSupported.realloc(aSupported.getLength() + 2);

    ::rtl::OUString*pArray = aSupported.getArray();
    pArray[aSupported.getLength()-2] = FRM_SUN_COMPONENT_DATABASE_NUMERICFIELD;
    pArray[aSupported.getLength()-1] = FRM_SUN_COMPONENT_NUMERICFIELD;
    return aSupported;
}

//------------------------------------------------------------------------------
Reference<XPropertySetInfo> SAL_CALL ONumericModel::getPropertySetInfo() throw( RuntimeException )
{
    Reference<XPropertySetInfo>  xInfo( createPropertySetInfo( getInfoHelper() ) );
    return xInfo;
}

//------------------------------------------------------------------------------
void ONumericModel::fillProperties(
        Sequence< Property >& _rProps,
        Sequence< Property >& _rAggregateProps ) const
{
    FRM_BEGIN_PROP_HELPER(9)
        DECL_PROP2(CLASSID,         sal_Int16,          READONLY, TRANSIENT);
        DECL_PROP3(DEFAULT_VALUE,   double,             BOUND, MAYBEDEFAULT, MAYBEVOID);
        DECL_PROP1(NAME,            ::rtl::OUString,    BOUND);
        DECL_PROP1(TAG,             ::rtl::OUString,    BOUND);
        DECL_PROP1(TABINDEX,        sal_Int16,          BOUND);
        DECL_PROP1(CONTROLSOURCE,   ::rtl::OUString,    BOUND);
        DECL_IFACE_PROP3(BOUNDFIELD,        XPropertySet,BOUND,READONLY, TRANSIENT);
        DECL_IFACE_PROP2(CONTROLLABEL,      XPropertySet,   BOUND, MAYBEVOID);
        DECL_PROP2(CONTROLSOURCEPROPERTY,   rtl::OUString,  READONLY, TRANSIENT);
    FRM_END_PROP_HELPER();
}

//------------------------------------------------------------------------------
::cppu::IPropertyArrayHelper& ONumericModel::getInfoHelper()
{
    return *const_cast<ONumericModel*>(this)->getArrayHelper();
}

//------------------------------------------------------------------------------
::rtl::OUString SAL_CALL ONumericModel::getServiceName() throw ( ::com::sun::star::uno::RuntimeException)
{
    return FRM_COMPONENT_NUMERICFIELD;  // old (non-sun) name for compatibility !
}

//.........................................................................
}   // namespace frm
//.........................................................................

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
