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

#ifndef _CHART_DATA_HXX
#define _CHART_DATA_HXX

#include <cppuhelper/implbase4.hxx>
// header for OInterfaceContainerHelper
#include <cppuhelper/interfacecontainer.hxx>

#include <com/sun/star/chart/XChartDataArray.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/lang/XUnoTunnel.hpp>
#include <com/sun/star/lang/XComponent.hpp>
namespace binfilter {

class ChartModel;

// ----------------------------------------
// ChXChartData
// ----------------------------------------

class ChXChartData : public cppu::WeakImplHelper4<
    ::com::sun::star::chart::XChartData,
    ::com::sun::star::lang::XServiceInfo,
    ::com::sun::star::lang::XEventListener,
    ::com::sun::star::lang::XUnoTunnel >
{
private:
    ::osl::Mutex maMutex;
    cppu::OInterfaceContainerHelper maListeners;

protected:
    ChartModel* mpModel;

public:
    // the model is used for listening for the 'death' of the ChartModel
    ChXChartData( ::com::sun::star::uno::Reference< ::com::sun::star::lang::XComponent > xModel,
                  ChartModel* pModel );
    virtual ~ChXChartData();

    ::osl::Mutex& GetMutex()    { return maMutex; }

    virtual void DataModified( ::com::sun::star::chart::ChartDataChangeEvent& );

    static const ::com::sun::star::uno::Sequence< sal_Int8 > & getUnoTunnelId() throw();
    static ChXChartData* getImplementation( ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > ) throw();

    // XChartData
    virtual void SAL_CALL addChartDataChangeEventListener(
        const ::com::sun::star::uno::Reference< ::com::sun::star::chart::XChartDataChangeEventListener >& aListener )
        throw( ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL removeChartDataChangeEventListener(
        const ::com::sun::star::uno::Reference< ::com::sun::star::chart::XChartDataChangeEventListener >& aListener )
        throw( ::com::sun::star::uno::RuntimeException );
    virtual double SAL_CALL getNotANumber() throw( ::com::sun::star::uno::RuntimeException );
    virtual sal_Bool SAL_CALL isNotANumber( double nNumber ) throw( ::com::sun::star::uno::RuntimeException );

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
        throw( ::com::sun::star::uno::RuntimeException );

    // XUnoTunnel
    virtual sal_Int64 SAL_CALL getSomething( const ::com::sun::star::uno::Sequence< sal_Int8 >& aIdentifier )
        throw( ::com::sun::star::uno::RuntimeException );

    // XEventListener listens to disposing of XModel
    virtual void SAL_CALL disposing( const ::com::sun::star::lang::EventObject& Source )
        throw( ::com::sun::star::uno::RuntimeException );
};


// ----------------------------------------
// ChXChartDataArray
// ----------------------------------------

class ChXChartDataArray :
    public ChXChartData,
    public ::com::sun::star::chart::XChartDataArray
{
private:
    static ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type > maTypeSequence;

public:
    // the model is used for listening for the 'death' of the ChartModel
    ChXChartDataArray( ::com::sun::star::uno::Reference< ::com::sun::star::lang::XComponent > xModel,
                       ChartModel* pModel );
    virtual ~ChXChartDataArray();

    // XInterface
    virtual ::com::sun::star::uno::Any SAL_CALL queryInterface( const ::com::sun::star::uno::Type& aType )
        throw( ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL acquire() throw();
    virtual void SAL_CALL release() throw();

    // XTypeProvider
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type > SAL_CALL getTypes()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL getImplementationId()
        throw( ::com::sun::star::uno::RuntimeException );

    // XChartDataArray
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Sequence< double > > SAL_CALL getData()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL setData( const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Sequence< double > >& aData )
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getRowDescriptions()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL setRowDescriptions( const ::com::sun::star::uno::Sequence< ::rtl::OUString >& aRowDescriptions )
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getColumnDescriptions()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL setColumnDescriptions( const ::com::sun::star::uno::Sequence< ::rtl::OUString >& aColumnDescriptions )
        throw( ::com::sun::star::uno::RuntimeException );

    // XChartData ( ::XChartDataArray )
    virtual void SAL_CALL addChartDataChangeEventListener(
        const ::com::sun::star::uno::Reference< ::com::sun::star::chart::XChartDataChangeEventListener >& aListener )
        throw( ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL removeChartDataChangeEventListener(
        const ::com::sun::star::uno::Reference< ::com::sun::star::chart::XChartDataChangeEventListener >& aListener )
        throw( ::com::sun::star::uno::RuntimeException );
    virtual double SAL_CALL getNotANumber() throw( ::com::sun::star::uno::RuntimeException );
    virtual sal_Bool SAL_CALL isNotANumber( double nNumber ) throw( ::com::sun::star::uno::RuntimeException );

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
        throw( ::com::sun::star::uno::RuntimeException );
};

} //namespace binfilter
#endif  // _CHART_DATA_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
