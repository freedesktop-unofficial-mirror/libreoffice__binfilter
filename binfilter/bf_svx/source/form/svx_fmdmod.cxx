/*************************************************************************
 *
 *  $RCSfile: svx_fmdmod.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:21:51 $
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
#pragma hdrstop

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
#ifndef _COMPHELPER_PROCESSFACTORY_HXX_
#include <comphelper/processfactory.hxx>
#endif
#include "fmglob.hxx"
#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>    //STRIP002
#endif

using namespace ::svxform;

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
//STRIP001 ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SAL_CALL  SvxFmMSFactory::createInstanceWithArguments(const ::rtl::OUString& ServiceSpecifier, const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any >& Arguments) throw( ::com::sun::star::uno::Exception, ::com::sun::star::uno::RuntimeException )
//STRIP001 {
//STRIP001  return SvxUnoDrawMSFactory::createInstanceWithArguments(ServiceSpecifier, Arguments );
//STRIP001 }

//-----------------------------------------------------------------------------
//STRIP001 ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL SvxFmMSFactory::getAvailableServiceNames(void) throw( ::com::sun::star::uno::RuntimeException )
//STRIP001 {
//STRIP001  static const ::rtl::OUString aSvxComponentServiceNameList[] =
//STRIP001  {
//STRIP001      FM_SUN_COMPONENT_TEXTFIELD,
//STRIP001      FM_SUN_COMPONENT_FORM,
//STRIP001      FM_SUN_COMPONENT_LISTBOX,
//STRIP001      FM_SUN_COMPONENT_COMBOBOX,
//STRIP001      FM_SUN_COMPONENT_RADIOBUTTON,
//STRIP001      FM_SUN_COMPONENT_GROUPBOX,
//STRIP001      FM_SUN_COMPONENT_FIXEDTEXT,
//STRIP001      FM_SUN_COMPONENT_COMMANDBUTTON,
//STRIP001      FM_SUN_COMPONENT_CHECKBOX,
//STRIP001      FM_SUN_COMPONENT_GRIDCONTROL,
//STRIP001      FM_SUN_COMPONENT_IMAGEBUTTON,
//STRIP001      FM_SUN_COMPONENT_FILECONTROL,
//STRIP001      FM_SUN_COMPONENT_TIMEFIELD,
//STRIP001      FM_SUN_COMPONENT_DATEFIELD,
//STRIP001      FM_SUN_COMPONENT_NUMERICFIELD,
//STRIP001      FM_SUN_COMPONENT_CURRENCYFIELD,
//STRIP001      FM_SUN_COMPONENT_PATTERNFIELD,
//STRIP001      FM_SUN_COMPONENT_HIDDENCONTROL,
//STRIP001      FM_SUN_COMPONENT_IMAGECONTROL
//STRIP001  };
//STRIP001
//STRIP001  static const sal_uInt16 nSvxComponentServiceNameListCount = sizeof(aSvxComponentServiceNameList) / sizeof ( aSvxComponentServiceNameList[0] );
//STRIP001
//STRIP001  ::com::sun::star::uno::Sequence< ::rtl::OUString > aSeq( nSvxComponentServiceNameListCount );
//STRIP001  ::rtl::OUString* pStrings = aSeq.getArray();
//STRIP001  for( sal_uInt16 nIdx = 0; nIdx < nSvxComponentServiceNameListCount; nIdx++ )
//STRIP001      pStrings[nIdx] = aSvxComponentServiceNameList[nIdx];
//STRIP001
//STRIP001  ::com::sun::star::uno::Sequence< ::rtl::OUString > aParentSeq( SvxUnoDrawMSFactory::getAvailableServiceNames() );
//STRIP001  return concatServiceNames( aParentSeq, aSeq );
//STRIP001 }

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


