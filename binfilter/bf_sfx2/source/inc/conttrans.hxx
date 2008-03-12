/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: conttrans.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 08:08:44 $
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

#ifndef _CONTTRANS_HXX
#define _CONTTRANS_HXX

// interfaces and structs
#ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XSINGLESERVICEFACTORY_HPP_
#include <com/sun/star/lang/XSingleServiceFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_REGISTRY_XREGISTRYKEY_HPP_
#include <com/sun/star/registry/XRegistryKey.hpp>
#endif
#ifndef  _COM_SUN_STAR_UCB_XCONTENTTRANSMITTER_HPP_
#include <com/sun/star/ucb/XContentTransmitter.hpp>
#endif

// helper classes and functions
#ifndef _CPPUHELPER_IMPLBASE2_HXX_
#include <cppuhelper/implbase2.hxx>
#endif
#ifndef _UNO_DISPATCHER_H_
#include <uno/dispatcher.h>
#endif
#ifndef _UNO_MAPPING_HXX_
#include <uno/mapping.hxx>
#endif
#ifndef _CPPUHELPER_FACTORY_HXX_
#include <cppuhelper/factory.hxx>
#endif


#ifndef _RTL_USTRBUF_HXX_
#include <rtl/ustrbuf.hxx>
#endif
#ifndef _SFXLSTNER_HXX
#include <bf_svtools/lstner.hxx>
#endif
namespace binfilter {

//=========================================================================

#define CT_SERVICE_NAME L"com.sun.star.ucb.ContentTransmitter"
#define FLAG_SET_READONLY   0x01
#define FLAG_NOTIFY_ANCHOR  0x02

//=========================================================================

class ContentTransmitter : public SfxListener,
                           public cppu::WeakImplHelper2<
                                ::com::sun::star::ucb::XContentTransmitter,
                                ::com::sun::star::lang::XServiceInfo >
{
    ::com::sun::star::uno::Reference < ::com::sun::star::lang::XMultiServiceFactory > m_xFact;
    ::rtl::OUString m_aSource;
    ::rtl::OUString m_aDest;
    long            m_nFlags;

public:

    ContentTransmitter( const ::com::sun::star::uno::Reference < ::com::sun::star::lang::XMultiServiceFactory >& rFact )
        : m_xFact( rFact )
    {}

    // SfxListener
    virtual void
    Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

    // XContentTransmitter
    virtual void SAL_CALL
    transmit( const ::rtl::OUString& Source,
              const ::rtl::OUString& Destination,
              long                 Flags )
        throw( ::com::sun::star::uno::RuntimeException );

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL
    getImplementationName()
        throw( ::com::sun::star::uno::RuntimeException );

    virtual sal_Bool SAL_CALL
    supportsService( const ::rtl::OUString& ServiceName )
        throw( ::com::sun::star::uno::RuntimeException );

    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL
    getSupportedServiceNames()
        throw( ::com::sun::star::uno::RuntimeException );

    // static Helper functions
    static ::com::sun::star::uno::Sequence< ::rtl::OUString >
    getSupportedServiceNames_Static();

    static ::rtl::OUString
    getImplementationName_Static() { return CT_SERVICE_NAME; }

    ::com::sun::star::uno::Reference< ::com::sun::star::lang::XSingleServiceFactory >
    createServiceFactory( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& rxServiceMgr );
};


}//end of namespace binfilter
#endif
