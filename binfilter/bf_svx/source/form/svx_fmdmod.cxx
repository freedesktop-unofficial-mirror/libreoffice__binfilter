/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_fmdmod.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:39:13 $
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
#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef _SVX_FMDMOD_HXX
#include "fmdmod.hxx"
#endif

#ifndef _SVX_FMSERVS_HXX
#include "fmservs.hxx"
#endif
#ifndef _SVX_FMOBJ_HXX
#include <fmobj.hxx>
#endif
#ifndef _SVX_UNOSHAPE_HXX
#include <unoshape.hxx>
#endif
#include "fmglob.hxx"
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif
namespace binfilter {

using namespace ::binfilter::svxform;//STRIP008 using namespace ::svxform;

//-----------------------------------------------------------------------------
/*N*/ ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >  SAL_CALL SvxFmMSFactory::createInstance(const ::rtl::OUString& ServiceSpecifier) throw( ::com::sun::star::uno::Exception, ::com::sun::star::uno::RuntimeException )
/*N*/ {
/*N*/   ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >  xRet;
/*N*/   if ( ServiceSpecifier.indexOf( ::rtl::OUString::createFromAscii("com.sun.star.form.component.") ) == 0 )
/*N*/   {
/*?*/       xRet = ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(ServiceSpecifier);
/*N*/   }
/*N*/   else if ( ServiceSpecifier == ::rtl::OUString( ::rtl::OUString::createFromAscii("com.sun.star.drawing.ControlShape") ) )
/*N*/   {
/*N*/       SdrObject* pObj = new FmFormObj(OBJ_FM_CONTROL);
/*N*/       xRet = *new SvxShapeControl(pObj);
/*N*/   }
/*N*/   if (!xRet.is())
/*N*/       xRet = SvxUnoDrawMSFactory::createInstance(ServiceSpecifier);
/*N*/   return xRet;
/*N*/ }

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

/*
// XServiceManager
::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >  SvxFmDrawModel::createInstance(const ::rtl::OUString& ServiceName)
            const throw( ::com::sun::star::lang::ServiceNotRegisteredException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException )
{
    ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >  xRet;
    sal_uInt16 nTokenCount = ServiceName.getTokenCount('.');
    if (nTokenCount == 5 &&
        ServiceName.getToken( 0, '.' ) == ::rtl::OUString::createFromAscii("stardiv") &&
        ServiceName.getToken( 1, '.' ) == ::rtl::OUString::createFromAscii("one") &&
        ServiceName.getToken( 2, '.' ) == ::rtl::OUString::createFromAscii("form") &&
        ServiceName.getToken( 3, '.' ) == ::rtl::OUString::createFromAscii("component"))
    {
        xRet = ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(ServiceName);
    }
    else
    if (nTokenCount == 4 &&
        ServiceName.getToken( 0, '.' ) == ::rtl::OUString::createFromAscii("stardiv") &&
        ServiceName.getToken( 1, '.' ) == ::rtl::OUString::createFromAscii("one") &&
        ServiceName.getToken( 2, '.' ) == ::rtl::OUString::createFromAscii("drawing") &&
        ServiceName.getToken( 3, '.' ) == ::rtl::OUString::createFromAscii("ControlShape"))
    {
        SdrObject* pObj = new FmFormObj();
        xRet = *new SvxShapeControl(pObj);
    }
    if (!xRet.is())
        xRet = SvxUnoDrawModel::createInstance(ServiceName);
    return xRet;
}
*/


}
