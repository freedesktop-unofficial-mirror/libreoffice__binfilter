/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sch_register.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 23:14:17 $
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

// auto strip #ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
// auto strip #include <com/sun/star/lang/XServiceInfo.hpp>
// auto strip #endif

#include <bf_sfx2/sfxuno.hxx>

#include "schdll.hxx"
namespace binfilter {

using namespace ::com::sun::star;

//StarChart document
extern uno::Sequence< ::rtl::OUString > SAL_CALL SchDocument_getSupportedServiceNames() throw();
extern ::rtl::OUString SAL_CALL SchDocument_getImplementationName() throw();
extern uno::Reference< uno::XInterface > SAL_CALL SchDocument_createInstance(const uno::Reference< lang::XMultiServiceFactory > & rSMgr) throw( uno::Exception );

extern "C" {

void SAL_CALL component_getImplementationEnvironment(   const   sal_Char**          ppEnvironmentTypeName   ,
                                                                uno_Environment**   ppEnvironment           )
{
    *ppEnvironmentTypeName = CPPU_CURRENT_LANGUAGE_BINDING_NAME ;
}

sal_Bool SAL_CALL component_writeInfo(  void*   pServiceManager ,
                                        void*   pRegistryKey    )
{
    uno::Reference< registry::XRegistryKey >
            xKey( reinterpret_cast< registry::XRegistryKey* >( pRegistryKey ) ) ;

    sal_Int32 i;
    uno::Reference< registry::XRegistryKey >  xNewKey;

    xNewKey = xKey->createKey(::rtl::OUString(
    RTL_CONSTASCII_USTRINGPARAM("/") ) + SchDocument_getImplementationName() +
    ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM( "/UNO/SERVICES") )  );

    uno::Sequence< ::rtl::OUString > rServices = SchDocument_getSupportedServiceNames();
    for(i = 0; i < rServices.getLength(); i++ )
        xNewKey->createKey( rServices.getConstArray()[i]);

    return sal_True;
}

void* SAL_CALL component_getFactory(    const   sal_Char*   pImplementationName ,
                                                void*       pServiceManager     ,
                                                void*       pRegistryKey        )
{
    void* pReturn = NULL ;

    if  ( ( pImplementationName !=  NULL ) && ( pServiceManager     !=  NULL ) )
    {
        uno::Reference< lang::XSingleServiceFactory > xFactory;
        uno::Reference< lang::XMultiServiceFactory > xServiceManager(
                    reinterpret_cast< lang::XMultiServiceFactory* >( pServiceManager ) );

        if( SchDocument_getImplementationName().equalsAsciiL(
            pImplementationName, strlen(pImplementationName)) )
        {
            xFactory = ::cppu::createSingleFactory( xServiceManager,
            SchDocument_getImplementationName(),
            SchDocument_createInstance,
            SchDocument_getSupportedServiceNames() );
        }


        if ( xFactory.is() )
        {
            xFactory->acquire();
            pReturn = xFactory.get();
        }
    }

    return pReturn ;
}
} // extern "C"



}
