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

#include <bf_svtools/bf_solar.h>

#include <comphelper/proparrhlp.hxx>
#include "Hidden.hxx"
#include "property.hrc"
#include "services.hxx"
#include <com/sun/star/form/FormComponentType.hpp>
#include <com/sun/star/beans/PropertyAttribute.hpp>
#include <comphelper/property.hxx>

namespace binfilter {

//.........................................................................
namespace frm
{
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

//------------------------------------------------------------------
InterfaceRef SAL_CALL OHiddenModel_CreateInstance(const Reference<XMultiServiceFactory>& _rxFactory) throw (RuntimeException)
{
    return *(new OHiddenModel(_rxFactory));
}

//------------------------------------------------------------------
DBG_NAME( OHiddenModel )
//------------------------------------------------------------------
OHiddenModel::OHiddenModel(const Reference<XMultiServiceFactory>& _rxFactory)
    :OControlModel(_rxFactory, ::rtl::OUString())
{
    DBG_CTOR( OHiddenModel, NULL );
    m_nClassId = FormComponentType::HIDDENCONTROL;
}

//------------------------------------------------------------------
OHiddenModel::OHiddenModel( const OHiddenModel* _pOriginal, const Reference<XMultiServiceFactory>& _rxFactory )
    :OControlModel( _pOriginal, _rxFactory )
{
    DBG_CTOR( OHiddenModel, NULL );
    m_sHiddenValue = _pOriginal->m_sHiddenValue;
}

//------------------------------------------------------------------------------
OHiddenModel::~OHiddenModel( )
{
    DBG_CTOR( OHiddenModel, NULL );
}

//------------------------------------------------------------------------------
IMPLEMENT_DEFAULT_CLONING( OHiddenModel )

//------------------------------------------------------------------------------
void OHiddenModel::getFastPropertyValue(Any& _rValue, sal_Int32 _nHandle) const
{
    switch (_nHandle)
    {
        case PROPERTY_ID_HIDDEN_VALUE : _rValue <<= m_sHiddenValue; break;
        default:
            OControlModel::getFastPropertyValue(_rValue, _nHandle);
    }
}

//------------------------------------------------------------------------------
void OHiddenModel::setFastPropertyValue_NoBroadcast(sal_Int32 _nHandle, const Any& _rValue) throw (com::sun::star::uno::Exception)
{
    switch (_nHandle)
    {
        case PROPERTY_ID_HIDDEN_VALUE :
            DBG_ASSERT(_rValue.getValueType().getTypeClass() == TypeClass_STRING, "OHiddenModel::setFastPropertyValue_NoBroadcast : invalid type !" );
            _rValue >>= m_sHiddenValue;
            break;
        default:
            OControlModel::setFastPropertyValue_NoBroadcast(_nHandle, _rValue);
    }
}

//------------------------------------------------------------------------------
sal_Bool OHiddenModel::convertFastPropertyValue(
            Any& _rConvertedValue, Any& _rOldValue, sal_Int32 _nHandle, const Any& _rValue)
            throw (IllegalArgumentException)
{
    sal_Bool bModified(sal_False);
    switch (_nHandle)
    {
        case PROPERTY_ID_HIDDEN_VALUE :
            bModified = tryPropertyValue(_rConvertedValue, _rOldValue, _rValue, m_sHiddenValue);
            break;
        default:
            bModified = OControlModel::convertFastPropertyValue(_rConvertedValue, _rOldValue, _nHandle, _rValue);
            break;
    }
    return bModified;
}

//------------------------------------------------------------------------------
Reference<XPropertySetInfo> SAL_CALL OHiddenModel::getPropertySetInfo() throw(RuntimeException)
{
    Reference<XPropertySetInfo> xInfo( createPropertySetInfo( getInfoHelper() ) );
    return xInfo;
}

//------------------------------------------------------------------------------
cppu::IPropertyArrayHelper& OHiddenModel::getInfoHelper()
{
    return *const_cast<OHiddenModel*>(this)->getArrayHelper();
}

//------------------------------------------------------------------------------
void OHiddenModel::fillProperties(
        Sequence< Property >& _rProps,
        Sequence< Property >& _rAggregateProps ) const
{
    BEGIN_AGGREGATION_PROPERTY_HELPER(4, m_xAggregateSet)
        DECL_PROP2(CLASSID,         sal_Int16,          READONLY, TRANSIENT);
        DECL_PROP1(HIDDEN_VALUE,    ::rtl::OUString,    BOUND);
        DECL_PROP1(NAME,            ::rtl::OUString,    BOUND);
        DECL_PROP1(TAG,             ::rtl::OUString,    BOUND);
    END_AGGREGATION_PROPERTY_HELPER();
}

// XServiceInfo
//------------------------------------------------------------------------------
StringSequence SAL_CALL OHiddenModel::getSupportedServiceNames() throw(::com::sun::star::uno::RuntimeException)
{
    StringSequence aSupported( 2 );
    aSupported[ 0 ] = FRM_SUN_COMPONENT_HIDDENCONTROL;
    aSupported[ 1 ] = FRM_SUN_FORMCOMPONENT;
    return aSupported;
}

//------------------------------------------------------------------------------
::rtl::OUString SAL_CALL OHiddenModel::getServiceName() throw(RuntimeException)
{
    return FRM_COMPONENT_HIDDEN;    // old (non-sun) name for compatibility !
}

//------------------------------------------------------------------------------
void SAL_CALL OHiddenModel::write(const Reference<stario::XObjectOutputStream>& _rxOutStream)
    throw(stario::IOException, RuntimeException)
{
    // Version
    _rxOutStream->writeShort(0x0002);

    // Wert
    _rxOutStream << m_sHiddenValue;

    OControlModel::write(_rxOutStream);
}

//------------------------------------------------------------------------------
void SAL_CALL OHiddenModel::read(const Reference<stario::XObjectInputStream>& _rxInStream) throw(stario::IOException, RuntimeException)
{
    // Version
    UINT16 nVersion = _rxInStream->readShort();

    // Name
    DBG_ASSERT(nVersion != 1, "OHiddenModel::read : this version is obsolete !");
    switch (nVersion)
    {
        case 1 : { ::rtl::OUString sDummy; _rxInStream >> sDummy; _rxInStream >> m_sHiddenValue; } break;
        case 2 : _rxInStream >> m_sHiddenValue; break;
        default : OSL_FAIL("OHiddenModel::read : unknown version !"); m_sHiddenValue = ::rtl::OUString();
    }
    OControlModel::read(_rxInStream);
}

//.........................................................................
}
//.........................................................................

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
