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

#ifndef _CHXCHARTDATACHANGEEVENTLISTENER_HXX
#define _CHXCHARTDATACHANGEEVENTLISTENER_HXX

#include <cppuhelper/implbase1.hxx> // helper for implementations

#include <com/sun/star/chart/XChartDataChangeEventListener.hpp>
namespace binfilter {

class ChXChartDocument;

class ChXChartDataChangeEventListener :
    public cppu::WeakImplHelper1< ::com::sun::star::chart::XChartDataChangeEventListener >
{
private:
    ChXChartDocument *mpXDoc;

public:
    ChXChartDataChangeEventListener();
    virtual ~ChXChartDataChangeEventListener(){};

    void Reset() throw();
    void SetOwner( ChXChartDocument* pXDoc ) throw();

    // XChartDataChangeEventListener
    virtual void SAL_CALL chartDataChanged( const ::com::sun::star::chart::ChartDataChangeEvent& aEvent )
        throw( ::com::sun::star::uno::RuntimeException );

    // XEventListener
    virtual void SAL_CALL disposing( const ::com::sun::star::lang::EventObject& Source )
        throw( ::com::sun::star::uno::RuntimeException );

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
        throw( ::com::sun::star::uno::RuntimeException );
};

} //namespace binfilter
#endif  // _CHXCHARTDATACHANGEEVENTLISTENER_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
