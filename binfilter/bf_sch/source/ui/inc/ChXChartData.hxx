/*************************************************************************
 *
 *  $RCSfile: ChXChartData.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:17:38 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef _CHART_DATA_HXX
#define _CHART_DATA_HXX

#ifndef _CPPUHELPER_IMPLBASE4_HXX_
#include <cppuhelper/implbase4.hxx>
#endif
// header for OInterfaceContainerHelper
#ifndef _CPPUHELPER_INTERFACECONTAINER_H_
#include <cppuhelper/interfacecontainer.hxx>
#endif
#ifndef _OSL_MUTEX_HXX_
#include <osl/mutex.hxx>
#endif

#ifndef _COM_SUN_STAR_CHART_XCHARTDATA_HPP_
#include <com/sun/star/chart/XChartData.hpp>
#endif
#ifndef _COM_SUN_STAR_CHART_XCHARTDATAARRAY_HPP_
#include <com/sun/star/chart/XChartDataArray.hpp>
#endif
#ifndef _COM_SUN_STAR_CHART_CHARTDATACHANGEEVENT_HPP_
#include <com/sun/star/chart/ChartDataChangeEvent.hpp>
#endif
#ifndef _COM_SUN_STAR_CHART_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XEVENTLISTENER_HPP_
#include <com/sun/star/lang/XEventListener.hpp>
#endif
#ifndef _COM_SUN_STAR_UNO_XUNOTUNNEL_HPP_
#include <com/sun/star/lang/XUnoTunnel.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XCOMPONENT_HPP_
#include <com/sun/star/lang/XComponent.hpp>
#endif

class ChartModel;

// ----------------------------------------
// ChXChartData
// ----------------------------------------

class ChXChartData : public cppu::WeakImplHelper4<
    com::sun::star::chart::XChartData,
    com::sun::star::lang::XServiceInfo,
    com::sun::star::lang::XEventListener,
    com::sun::star::lang::XUnoTunnel >
{
private:
    ::osl::Mutex maMutex;
    cppu::OInterfaceContainerHelper maListeners;

protected:
    ChartModel* mpModel;

public:
    // the model is used for listening for the 'death' of the ChartModel
    ChXChartData( com::sun::star::uno::Reference< com::sun::star::lang::XComponent > xModel,
                  ChartModel* pModel );
    virtual ~ChXChartData();

    ::osl::Mutex& GetMutex()    { return maMutex; }

    virtual void DataModified( com::sun::star::chart::ChartDataChangeEvent& );

    static const com::sun::star::uno::Sequence< sal_Int8 > & getUnoTunnelId() throw();
    static ChXChartData* getImplementation( com::sun::star::uno::Reference< com::sun::star::uno::XInterface > ) throw();

    // XChartData
    virtual void SAL_CALL addChartDataChangeEventListener(
        const com::sun::star::uno::Reference< ::com::sun::star::chart::XChartDataChangeEventListener >& aListener )
        throw( com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL removeChartDataChangeEventListener(
        const com::sun::star::uno::Reference< ::com::sun::star::chart::XChartDataChangeEventListener >& aListener )
        throw( com::sun::star::uno::RuntimeException );
    virtual double SAL_CALL getNotANumber() throw( com::sun::star::uno::RuntimeException );
    virtual sal_Bool SAL_CALL isNotANumber( double nNumber ) throw( com::sun::star::uno::RuntimeException );

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName()
        throw( com::sun::star::uno::RuntimeException );
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
        throw( com::sun::star::uno::RuntimeException );
    virtual com::sun::star::uno::Sequence< rtl::OUString > SAL_CALL getSupportedServiceNames()
        throw( com::sun::star::uno::RuntimeException );

    // XUnoTunnel
    virtual sal_Int64 SAL_CALL getSomething( const com::sun::star::uno::Sequence< sal_Int8 >& aIdentifier )
        throw( com::sun::star::uno::RuntimeException );

    // XEventListener listens to disposing of XModel
    virtual void SAL_CALL disposing( const com::sun::star::lang::EventObject& Source )
        throw( com::sun::star::uno::RuntimeException );
};


// ----------------------------------------
// ChXChartDataArray
// ----------------------------------------

class ChXChartDataArray :
    public ChXChartData,
    public com::sun::star::chart::XChartDataArray
{
private:
    static ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type > maTypeSequence;

public:
    // the model is used for listening for the 'death' of the ChartModel
    ChXChartDataArray( com::sun::star::uno::Reference< com::sun::star::lang::XComponent > xModel,
                       ChartModel* pModel );
    virtual ~ChXChartDataArray();

    // XInterface
    virtual com::sun::star::uno::Any SAL_CALL queryInterface( const com::sun::star::uno::Type& aType )
        throw( com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL acquire() throw();
    virtual void SAL_CALL release() throw();

    // XTypeProvider
    virtual com::sun::star::uno::Sequence< com::sun::star::uno::Type > SAL_CALL getTypes()
        throw( com::sun::star::uno::RuntimeException );
    virtual com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL getImplementationId()
        throw( com::sun::star::uno::RuntimeException );

    // XChartDataArray
    virtual com::sun::star::uno::Sequence< com::sun::star::uno::Sequence< double > > SAL_CALL getData()
        throw( com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL setData( const com::sun::star::uno::Sequence< com::sun::star::uno::Sequence< double > >& aData )
        throw( com::sun::star::uno::RuntimeException );
    virtual com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getRowDescriptions()
        throw( com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL setRowDescriptions( const com::sun::star::uno::Sequence< ::rtl::OUString >& aRowDescriptions )
        throw( com::sun::star::uno::RuntimeException );
    virtual com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getColumnDescriptions()
        throw( com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL setColumnDescriptions( const com::sun::star::uno::Sequence< ::rtl::OUString >& aColumnDescriptions )
        throw( com::sun::star::uno::RuntimeException );

    // XChartData ( ::XChartDataArray )
    virtual void SAL_CALL addChartDataChangeEventListener(
        const com::sun::star::uno::Reference< ::com::sun::star::chart::XChartDataChangeEventListener >& aListener )
        throw( com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL removeChartDataChangeEventListener(
        const com::sun::star::uno::Reference< ::com::sun::star::chart::XChartDataChangeEventListener >& aListener )
        throw( com::sun::star::uno::RuntimeException );
    virtual double SAL_CALL getNotANumber() throw( com::sun::star::uno::RuntimeException );
    virtual sal_Bool SAL_CALL isNotANumber( double nNumber ) throw( com::sun::star::uno::RuntimeException );

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName()
        throw( com::sun::star::uno::RuntimeException );
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
        throw( com::sun::star::uno::RuntimeException );
    virtual com::sun::star::uno::Sequence< rtl::OUString > SAL_CALL getSupportedServiceNames()
        throw( com::sun::star::uno::RuntimeException );
};

#endif  // _CHART_DATA_HXX

