/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sd_unodoc.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 01:26:00 $
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

// System - Includes -----------------------------------------------------

// auto strip #include <tools/string.hxx>
#include <bf_sfx2/docfac.hxx>

// auto strip #ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
// auto strip #include <com/sun/star/lang/XMultiServiceFactory.hpp>
// auto strip #endif

#include "sdmod.hxx"

#ifndef _VOS_MUTEX_HXX_
#include <vos/mutex.hxx>
#endif
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif
namespace binfilter {

using namespace ::com::sun::star;

// com.sun.star.comp.Draw.DrawingDocument

::rtl::OUString SAL_CALL SdDrawingDocument_getImplementationName() throw( uno::RuntimeException )
{
    return ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.comp.Draw.DrawingDocument" ) );
}

uno::Sequence< ::rtl::OUString > SAL_CALL SdDrawingDocument_getSupportedServiceNames() throw( uno::RuntimeException )
{
    // useable for component registration only!
    uno::Sequence< ::rtl::OUString > aSeq( 1 );
    aSeq[0] = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.drawing.DrawingDocument"));

    return aSeq;
}

uno::Reference< uno::XInterface > SAL_CALL SdDrawingDocument_createInstance(
                const uno::Reference< lang::XMultiServiceFactory > & rSMgr )
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    // to create the service the SW_MOD should be already initialized
    DBG_ASSERT( SD_MOD(), "No StarDraw module!" );

    if ( SD_MOD() )
    {
        ::rtl::OUString aFactoryURL( RTL_CONSTASCII_USTRINGPARAM ( "private:factory/sdraw" ) );
        const SfxObjectFactory* pFactory = SfxObjectFactory::GetFactory( aFactoryURL );
        if ( pFactory )
        {
            SfxObjectShell* pShell = pFactory->CreateObject();
            if( pShell )
                return uno::Reference< uno::XInterface >( pShell->GetModel() );
        }
    }

    return uno::Reference< uno::XInterface >();
}

// com.sun.star.comp.Draw.PresentationDocument

::rtl::OUString SAL_CALL SdPresentationDocument_getImplementationName() throw( uno::RuntimeException )
{
    return ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.comp.Draw.PresentationDocument" ) );
}

uno::Sequence< ::rtl::OUString > SAL_CALL SdPresentationDocument_getSupportedServiceNames() throw( uno::RuntimeException )
{
    // useable for component registration only!
    uno::Sequence< ::rtl::OUString > aSeq( 1 );
    aSeq[0] = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.presentation.PresentationDocument"));

    return aSeq;
}

uno::Reference< uno::XInterface > SAL_CALL SdPresentationDocument_createInstance(
                const uno::Reference< lang::XMultiServiceFactory > & rSMgr )
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );

    // to create the service the SW_MOD should be already initialized
    DBG_ASSERT( SD_MOD(), "No StarDraw module!" );

    if ( SD_MOD() )
    {
        ::rtl::OUString aFactoryURL( RTL_CONSTASCII_USTRINGPARAM ( "private:factory/simpress" ) );
        const SfxObjectFactory* pFactory = SfxObjectFactory::GetFactory( aFactoryURL );
        if ( pFactory )
        {
            SfxObjectShell* pShell = pFactory->CreateObject();
            if( pShell )
                return uno::Reference< uno::XInterface >( pShell->GetModel() );
        }
    }

    return uno::Reference< uno::XInterface >();
}


}
