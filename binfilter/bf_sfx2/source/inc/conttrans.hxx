/*************************************************************************
 *
 *  $RCSfile: conttrans.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:39:45 $
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
#include <svtools/lstner.hxx>
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
