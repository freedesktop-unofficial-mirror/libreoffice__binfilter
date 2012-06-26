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

#ifndef _CHXCHART_AXIS_HXX
#define _CHXCHART_AXIS_HXX

// header for SvNumberFormatsSupplierObj
#include <bf_svtools/numuno.hxx>

#include <com/sun/star/util/XNumberFormatsSupplier.hpp>

#include "ChXChartObject.hxx"
namespace binfilter {

class ChXChartAxis :
    public ::com::sun::star::util::XNumberFormatsSupplier,
    public ChXChartObject
{
private:
    ::com::sun::star::uno::Reference<
        ::com::sun::star::util::XNumberFormatsSupplier >    rNumberFormatter;

    ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type > maTypeSequence;

public:
    ChXChartAxis( ChartModel* _Model, long _WhichId );
    virtual ~ChXChartAxis();

    virtual void InitNumberFormatter() throw( ::com::sun::star::uno::RuntimeException );

    static const ::com::sun::star::uno::Sequence< sal_Int8 > & getUnoTunnelId() throw();

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName() throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames() throw( ::com::sun::star::uno::RuntimeException );

    // XNumberFormatsSupplier
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > SAL_CALL getNumberFormatSettings()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormats > SAL_CALL getNumberFormats()
        throw( ::com::sun::star::uno::RuntimeException );

    // XPropertySet
    virtual void SAL_CALL setPropertyValue( const ::rtl::OUString& aPropertyName,
                                            const ::com::sun::star::uno::Any& aValue )
        throw( ::com::sun::star::beans::UnknownPropertyException,
               ::com::sun::star::beans::PropertyVetoException,
               ::com::sun::star::lang::IllegalArgumentException,
               ::com::sun::star::lang::WrappedTargetException,
               ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Any SAL_CALL getPropertyValue( const ::rtl::OUString& PropertyName )
        throw( ::com::sun::star::beans::UnknownPropertyException,
               ::com::sun::star::lang::WrappedTargetException,
               ::com::sun::star::uno::RuntimeException );

    // XInterface
    virtual ::com::sun::star::uno::Any SAL_CALL queryInterface( const ::com::sun::star::uno::Type & rType )
        throw ( ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL acquire() throw();
    virtual void SAL_CALL release() throw();

    // XTypeProvider
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type > SAL_CALL getTypes()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL getImplementationId()
        throw( ::com::sun::star::uno::RuntimeException );

    // XShapeDescriptor
    virtual ::rtl::OUString SAL_CALL getShapeType() throw( ::com::sun::star::uno::RuntimeException );

    // XUnoTunnel
    virtual sal_Int64 SAL_CALL getSomething( const ::com::sun::star::uno::Sequence< sal_Int8 >& aIdentifier )
        throw( ::com::sun::star::uno::RuntimeException );

    //  ChXChartObject::XMultiPropertySet
    virtual void SAL_CALL setPropertyValues (
                const ::com::sun::star::uno::Sequence< ::rtl::OUString >& aPropertyNames,
                const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any >& aValues )
        throw ( ::com::sun::star::beans::PropertyVetoException,
                ::com::sun::star::lang::IllegalArgumentException,
                ::com::sun::star::lang::WrappedTargetException,
                ::com::sun::star::uno::RuntimeException);

protected:
    /** @descr  Creates an item set with a which range specific to chart axes.
        @return Returns a pointer to an item set.  The caller is responsible for deleting it.
    */
    virtual SfxItemSet * CreateItemSet  (void);

    /** @descr  Handle the axis special cases and call the base class method for all other.
            See there for further documentation.
        @see    ChxChartObject::GetPropertyValue.
    */
    virtual void    GetPropertyValue    (const SfxItemPropertyMap & rProperty,
                                        ::com::sun::star::uno::Any & rValue,
                                        SfxItemSet & rAttributes);
};

} //namespace binfilter
#endif  // _CHXCHART_AXIS_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
