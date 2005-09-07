/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ChXChartDataChangeEventListener.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 22:40:38 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#ifndef _CHXCHARTDATACHANGEEVENTLISTENER_HXX
#define _CHXCHARTDATACHANGEEVENTLISTENER_HXX

#include <cppuhelper/implbase1.hxx> // helper for implementations

#ifndef _COM_SUN_STAR_CHART_XCHARTDATACHANGEEVENTLISTENER_HPP_
#include <com/sun/star/chart/XChartDataChangeEventListener.hpp>
#endif
// auto strip #ifndef _COM_SUN_STAR_CHART_CHARTDATACHANGEEVENT_HPP_
// auto strip #include <com/sun/star/chart/ChartDataChangeEvent.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_CHART_CHARTDATACHANGEEVENT_HPP_
// auto strip #include <com/sun/star/lang/XServiceInfo.hpp>
// auto strip #endif
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

