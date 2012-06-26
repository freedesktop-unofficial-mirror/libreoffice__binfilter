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

#ifndef SC_CHARTUNO_HXX
#define SC_CHARTUNO_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_svtools/lstner.hxx>
#include <bf_tools/string.hxx>

#include <com/sun/star/table/XTableChart.hpp>
#include <com/sun/star/table/XTableCharts.hpp>
#include <com/sun/star/document/XEmbeddedObjectSupplier.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/container/XEnumerationAccess.hpp>
#include <com/sun/star/container/XIndexAccess.hpp>
#include <com/sun/star/container/XNamed.hpp>

#include <cppuhelper/implbase4.hxx>
namespace binfilter {


class ScDocShell;
class ScRangeListRef;
class ScChartObj;


class ScChartsObj : public cppu::WeakImplHelper4<
                            ::com::sun::star::table::XTableCharts,
                            ::com::sun::star::container::XEnumerationAccess,
                            ::com::sun::star::container::XIndexAccess,
                            ::com::sun::star::lang::XServiceInfo >,
                        public SfxListener
{
private:
    ScDocShell*             pDocShell;
    USHORT                  nTab;           // Charts sind pro Sheet

    ScChartObj*             GetObjectByIndex_Impl(long nIndex) const;
    ScChartObj*             GetObjectByName_Impl(const ::rtl::OUString& aName) const;

public:
                            ScChartsObj(ScDocShell* pDocSh, USHORT nT);
    virtual                 ~ScChartsObj();

    virtual void            Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

                            // XTableCharts
    virtual void SAL_CALL   addNewByName( const ::rtl::OUString& aName,
                                    const ::com::sun::star::awt::Rectangle& aRect,
                                    const ::com::sun::star::uno::Sequence<
                                        ::com::sun::star::table::CellRangeAddress >& aRanges,
                                    sal_Bool bColumnHeaders, sal_Bool bRowHeaders )
                                        throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL   removeByName( const ::rtl::OUString& aName )
                                        throw(::com::sun::star::uno::RuntimeException);

                            // XNameAccess
    virtual ::com::sun::star::uno::Any SAL_CALL getByName( const ::rtl::OUString& aName )
                                throw(::com::sun::star::container::NoSuchElementException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getElementNames()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasByName( const ::rtl::OUString& aName )
                                throw(::com::sun::star::uno::RuntimeException);

                            // XIndexAccess
    virtual sal_Int32 SAL_CALL getCount() throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Any SAL_CALL getByIndex( sal_Int32 Index )
                                throw(::com::sun::star::lang::IndexOutOfBoundsException,
                                    ::com::sun::star::lang::WrappedTargetException,
                                    ::com::sun::star::uno::RuntimeException);

                            // XEnumerationAccess
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XEnumeration > SAL_CALL
                            createEnumeration() throw(::com::sun::star::uno::RuntimeException);

                            // XElementAccess
    virtual ::com::sun::star::uno::Type SAL_CALL getElementType()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL hasElements() throw(::com::sun::star::uno::RuntimeException);

                            // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
                                throw(::com::sun::star::uno::RuntimeException);
};


class ScChartObj : public cppu::WeakImplHelper4<
                            ::com::sun::star::table::XTableChart,
                            ::com::sun::star::document::XEmbeddedObjectSupplier,
                            ::com::sun::star::container::XNamed,
                            ::com::sun::star::lang::XServiceInfo >,
                        public SfxListener
{
private:
    ScDocShell*             pDocShell;
    USHORT                  nTab;           // Charts sind pro Sheet
    String                  aChartName;

    void    Update_Impl( const ScRangeListRef& rRanges, BOOL bColHeaders, BOOL bRowHeaders );
    void    GetData_Impl( ScRangeListRef& rRanges, BOOL& rColHeaders, BOOL& rRowHeaders ) const;

public:
                            ScChartObj(ScDocShell* pDocSh, USHORT nT, const String& rN);
    virtual                 ~ScChartObj();

    virtual void            Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

                            // XTableChart
    virtual sal_Bool SAL_CALL getHasColumnHeaders() throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL   setHasColumnHeaders( sal_Bool bHasColumnHeaders )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL getHasRowHeaders() throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL   setHasRowHeaders( sal_Bool bHasRowHeaders )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::table::CellRangeAddress > SAL_CALL
                            getRanges(  ) throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL   setRanges( const ::com::sun::star::uno::Sequence<
                                    ::com::sun::star::table::CellRangeAddress >& aRanges )
                                throw(::com::sun::star::uno::RuntimeException);

                            // XEmbeddedObjectSupplier
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::lang::XComponent > SAL_CALL
                            getEmbeddedObject() throw(::com::sun::star::uno::RuntimeException);

                            // XNamed
    virtual ::rtl::OUString SAL_CALL getName() throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL   setName( const ::rtl::OUString& aName )
                                throw(::com::sun::star::uno::RuntimeException);

                            // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
                                throw(::com::sun::star::uno::RuntimeException);
};

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
