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

#ifndef _CHART_DIAGRAM_HXX
#define _CHART_DIAGRAM_HXX

#include <cppuhelper/implbase.hxx>

#include <com/sun/star/chart/XDiagram.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/chart/XTwoAxisXSupplier.hpp>
#include <com/sun/star/chart/XTwoAxisYSupplier.hpp>
#include <com/sun/star/chart/XAxisZSupplier.hpp>
#include <com/sun/star/chart/XStatisticDisplay.hpp>
#include <com/sun/star/chart/X3DDisplay.hpp>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/beans/XMultiPropertySet.hpp>
#include <com/sun/star/beans/XPropertyState.hpp>
#include <com/sun/star/beans/XMultiPropertyStates.hpp>
#include <com/sun/star/lang/XUnoTunnel.hpp>
#include <com/sun/star/lang/IndexOutOfBoundsException.hpp>
#include <com/sun/star/lang/XComponent.hpp>
#include <com/sun/star/lang/XEventListener.hpp>
#include <cppuhelper/interfacecontainer.hxx>

// header for class SvxItemPropertySet
#include <bf_svx/unoipset.hxx>
namespace binfilter {

class ChartModel;
class SchChartDocShell;
} //namespace binfilter

//  Construct a WeakImplHelper14 with the emphasis on 14.
//  Fourteen interfaces are two to many to use the newer template definition
//  of WeakImplHelper.
#define __IFC14 Ifc1, Ifc2, Ifc3, Ifc4, Ifc5, Ifc6, Ifc7, Ifc8, Ifc9, Ifc10,\
    Ifc11, Ifc12, Ifc13, Ifc14
#define __CLASS_IFC14 class Ifc1, class Ifc2, class Ifc3, class Ifc4, \
    class Ifc5, class Ifc6, class Ifc7, class Ifc8, class Ifc9, class Ifc10,\
    class Ifc11, class Ifc12, class Ifc13, class Ifc14
#define __PUBLIC_IFC14 public Ifc1, public Ifc2, public Ifc3, public Ifc4,\
    public Ifc5, public Ifc6, public Ifc7, public Ifc8, public Ifc9,\
    public Ifc10, public Ifc11, public Ifc12, public Ifc13, public Ifc14

__DEF_IMPLHELPER_PRE(14)
    __IFC_WRITEOFFSET(1) __IFC_WRITEOFFSET(2) __IFC_WRITEOFFSET(3)\
    __IFC_WRITEOFFSET(4) __IFC_WRITEOFFSET(5) __IFC_WRITEOFFSET(6)\
    __IFC_WRITEOFFSET(7) __IFC_WRITEOFFSET(8) __IFC_WRITEOFFSET(9)\
    __IFC_WRITEOFFSET(10) __IFC_WRITEOFFSET(11) __IFC_WRITEOFFSET(12)\
    __IFC_WRITEOFFSET(13) __IFC_WRITEOFFSET(14)
__DEF_IMPLHELPER_POST(14)

namespace binfilter {
    class ChXDiagram : public ::cppu::WeakImplHelper14
 <
    ::com::sun::star::chart::XDiagram,
    ::com::sun::star::chart::XAxisZSupplier,
    ::com::sun::star::chart::XTwoAxisXSupplier, //  : XAxisXSupplier
    ::com::sun::star::chart::XTwoAxisYSupplier, //  : XAxisYSupplier
    ::com::sun::star::chart::XStatisticDisplay,
    ::com::sun::star::chart::X3DDisplay,
    ::com::sun::star::beans::XPropertySet,
    ::com::sun::star::beans::XMultiPropertySet,
    ::com::sun::star::beans::XPropertyState,
    ::com::sun::star::beans::XMultiPropertyStates,
    ::com::sun::star::lang::XServiceInfo,
    ::com::sun::star::lang::XUnoTunnel,
       ::com::sun::star::lang::XComponent,
       ::com::sun::star::lang::XEventListener
 >
{
private:
    ::rtl::OUString maServiceName;
    sal_Int32 mnBaseType;
    ChartModel* mpModel;
    SvxItemPropertySet maPropSet;

    // some shape references (ChXChartObjects)
    ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape > mxXAxisTitle;
    ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape > mxYAxisTitle;
    ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape > mxZAxisTitle;

    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > mxXAxis;
    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > mxYAxis;
    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > mxZAxis;
    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > mxSecXAxis;
    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > mxSecYAxis;

    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > mxMajorGridX;
    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > mxMajorGridY;
    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > mxMajorGridZ;

    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > mxMinorGridX;
    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > mxMinorGridY;
    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > mxMinorGridZ;

    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > mxMinMaxLine;
    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > mxUpBar;
    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > mxDownBar;

    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > mxWall;
    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > mxFloor;


    ::com::sun::star::uno::Any GetAnyByItem( SfxItemSet& aSet, const SfxItemPropertyMap* pMap );

public:
    ChXDiagram( SchChartDocShell* pShell, sal_Bool bPreInit = sal_True );
    virtual ~ChXDiagram();

    void SetServiceName( const ::rtl::OUString& u ) throw() { maServiceName = u; }
    const ::rtl::OUString& getServiceName() throw()         { return maServiceName; }
    sal_Bool SetDocShell( SchChartDocShell* pDocShell, sal_Bool bKeepModel = sal_False ) throw();

    static const ::com::sun::star::uno::Sequence< sal_Int8 > & getUnoTunnelId() throw();
    static ChXDiagram* getImplementation( ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > ) throw();

    // XDiagram
    virtual ::rtl::OUString SAL_CALL getDiagramType() throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > SAL_CALL getDataRowProperties( sal_Int32 Row )
        throw( ::com::sun::star::uno::RuntimeException,
               ::com::sun::star::lang::IndexOutOfBoundsException );
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > SAL_CALL getDataPointProperties( sal_Int32 Column, sal_Int32 Row )
        throw( ::com::sun::star::uno::RuntimeException,
               ::com::sun::star::lang::IndexOutOfBoundsException );

    // XShape ( ::XDiagram )
    virtual ::com::sun::star::awt::Size SAL_CALL getSize()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL setSize( const ::com::sun::star::awt::Size& )
        throw( ::com::sun::star::beans::PropertyVetoException,
               ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::awt::Point SAL_CALL getPosition()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL setPosition( const ::com::sun::star::awt::Point& )
        throw( ::com::sun::star::uno::RuntimeException );

    // XShapeDescriptor ( ::XShape ::XDiagram )
    virtual ::rtl::OUString SAL_CALL getShapeType() throw( ::com::sun::star::uno::RuntimeException );


    // XAxisXSupplier, XAxisYSupplier, XAxisZSupplier,
    // XTwoAxisXSupplier, XTwoAxisYSupplier
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape > SAL_CALL getXAxisTitle()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape > SAL_CALL getYAxisTitle()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape > SAL_CALL getZAxisTitle()
        throw( ::com::sun::star::uno::RuntimeException );

    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > SAL_CALL getXAxis()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > SAL_CALL getYAxis()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > SAL_CALL getZAxis()
        throw( ::com::sun::star::uno::RuntimeException );

    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > SAL_CALL getSecondaryXAxis()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > SAL_CALL getSecondaryYAxis()
        throw( ::com::sun::star::uno::RuntimeException );

    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > SAL_CALL getXMainGrid()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > SAL_CALL getYMainGrid()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > SAL_CALL getZMainGrid()
        throw( ::com::sun::star::uno::RuntimeException );

    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > SAL_CALL getXHelpGrid()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > SAL_CALL getYHelpGrid()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > SAL_CALL getZHelpGrid()
        throw( ::com::sun::star::uno::RuntimeException );


    // XStatisticDisplay
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > SAL_CALL getMinMaxLine()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > SAL_CALL getUpBar()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > SAL_CALL getDownBar()
        throw( ::com::sun::star::uno::RuntimeException );


    // X3DDisplay
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > SAL_CALL getWall()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > SAL_CALL getFloor()
        throw( ::com::sun::star::uno::RuntimeException );

    // XPropertySet
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo > SAL_CALL getPropertySetInfo()
        throw( ::com::sun::star::uno::RuntimeException );
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
    virtual void SAL_CALL addPropertyChangeListener( const ::rtl::OUString& aPropertyName,
                const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertyChangeListener >& xListener )
        throw( ::com::sun::star::beans::UnknownPropertyException,
               ::com::sun::star::lang::WrappedTargetException,
               ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL removePropertyChangeListener( const ::rtl::OUString& aPropertyName,
                const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertyChangeListener >& aListener )
        throw( ::com::sun::star::beans::UnknownPropertyException,
               ::com::sun::star::lang::WrappedTargetException,
               ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL addVetoableChangeListener( const ::rtl::OUString& PropertyName,
                const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XVetoableChangeListener >& aListener )
        throw( ::com::sun::star::beans::UnknownPropertyException,
               ::com::sun::star::lang::WrappedTargetException,
               ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL removeVetoableChangeListener( const ::rtl::OUString& PropertyName,
                const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XVetoableChangeListener >& aListener )
        throw( ::com::sun::star::beans::UnknownPropertyException,
               ::com::sun::star::lang::WrappedTargetException,
               ::com::sun::star::uno::RuntimeException );

    //  XMultiPropertySet
    virtual void SAL_CALL setPropertyValues (
                const ::com::sun::star::uno::Sequence< ::rtl::OUString >& aPropertyNames,
                const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any >& aValues )
        throw (::com::sun::star::beans::PropertyVetoException,
                ::com::sun::star::lang::IllegalArgumentException,
                ::com::sun::star::lang::WrappedTargetException,
                ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any > SAL_CALL getPropertyValues    (
                const ::com::sun::star::uno::Sequence< ::rtl::OUString >& aPropertyNames )
        throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL addPropertiesChangeListener   (
                const ::com::sun::star::uno::Sequence< ::rtl::OUString >& aPropertyNames,
                const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertiesChangeListener >& xListener )
        throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL removePropertiesChangeListener    (
                const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertiesChangeListener >& xListener )
        throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL firePropertiesChangeEvent (
                const ::com::sun::star::uno::Sequence< ::rtl::OUString >& aPropertyNames,
                const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertiesChangeListener >& xListener )
        throw (::com::sun::star::uno::RuntimeException);

    // XPropertyState
    virtual ::com::sun::star::beans::PropertyState SAL_CALL getPropertyState( const ::rtl::OUString& PropertyName )
        throw( ::com::sun::star::beans::UnknownPropertyException,
               ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyState > SAL_CALL getPropertyStates(
        const ::com::sun::star::uno::Sequence< ::rtl::OUString >& aPropertyName )
        throw( ::com::sun::star::beans::UnknownPropertyException,
               ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL setPropertyToDefault( const ::rtl::OUString& PropertyName )
        throw( ::com::sun::star::beans::UnknownPropertyException,
               ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Any SAL_CALL getPropertyDefault( const ::rtl::OUString& aPropertyName )
        throw( ::com::sun::star::beans::UnknownPropertyException,
               ::com::sun::star::lang::WrappedTargetException,
               ::com::sun::star::uno::RuntimeException );

    //  XMultiPropertyStates
    //  getPropertyStates   already part of interface XPropertyState
    virtual void SAL_CALL setAllPropertiesToDefault (void)
        throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setPropertiesToDefault    (
                const ::com::sun::star::uno::Sequence< ::rtl::OUString >& aPropertyNames )
        throw (::com::sun::star::beans::UnknownPropertyException,
                ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any > SAL_CALL getPropertyDefaults  (
                const ::com::sun::star::uno::Sequence< ::rtl::OUString >& aPropertyNames )
        throw (::com::sun::star::beans::UnknownPropertyException,
                ::com::sun::star::lang::WrappedTargetException,
                ::com::sun::star::uno::RuntimeException);

    // XServiceInfo
    // supportsService is handled by SvxServiceInfoHelper
    virtual ::rtl::OUString SAL_CALL getImplementationName()
        throw( ::com::sun::star::uno::RuntimeException );
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
        throw( ::com::sun::star::uno::RuntimeException );
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
        throw( ::com::sun::star::uno::RuntimeException );


    // XUnoTunnel
    virtual sal_Int64 SAL_CALL getSomething( const ::com::sun::star::uno::Sequence< sal_Int8 >& aIdentifier )
        throw( ::com::sun::star::uno::RuntimeException );

    // XComponent
    virtual void SAL_CALL dispose() throw( ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL addEventListener( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XEventListener >& xListener )
        throw( ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL removeEventListener( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XEventListener >& aListener )
        throw( ::com::sun::star::uno::RuntimeException );

    //  XEventListener
    virtual void SAL_CALL disposing (const ::com::sun::star::lang::EventObject & Source)
        throw (::com::sun::star::uno::RuntimeException);

protected:
    /** @descr  In an array of SfxItemPropertyMap entries advance from the position pointed to
            by pProperty to that property that has the name given by pPropertyName.  If the
            property list does not contain such an entry an UnknownPropertyException is thrown.
        @param  pProperty Pointer into an array of properties.  It is modified such that after
            the methods returns it points to a property with the same name as pPropertyName.
        @param  pPropertyName   Name of the property that is searched for.
    */
    void AdvanceToName  (const SfxItemPropertyMap *& pProperty,
                        const ::rtl::OUString * pPropertyName)
        throw (::com::sun::star::beans::UnknownPropertyException);

private:
    /// Mutex used by the interface container.
    ::osl::Mutex    maMutex;

    /// List of listeners for the XComponent interface.
    ::cppu::OInterfaceContainerHelper   maListenerList;
};

} //namespace binfilter
#endif  // _CHART_DIAGRAM_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
