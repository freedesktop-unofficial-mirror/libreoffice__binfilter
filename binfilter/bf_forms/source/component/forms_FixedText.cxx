/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: forms_FixedText.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 15:43:53 $
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


#ifndef _COMPHELPER_PROPERTY_ARRAY_HELPER_HXX_
#include <comphelper/proparrhlp.hxx>
#endif

#ifndef _FORMS_FIXEDTEXT_HXX_
#include "FixedText.hxx"
#endif
#ifndef _FRM_SERVICES_HXX_
#include "services.hxx"
#endif
#ifndef _FRM_PROPERTY_HRC_
#include "property.hrc"
#endif
// auto strip #ifndef _FRM_PROPERTY_HXX_
// auto strip #include "property.hxx"
// auto strip #endif
// auto strip #ifndef _TOOLS_DEBUG_HXX
// auto strip #include <tools/debug.hxx>
// auto strip #endif

#ifndef _COMPHELPER_PROPERTY_HXX_
#include <comphelper/property.hxx>
#endif

#ifndef _COM_SUN_STAR_BEANS_PROPERTYATTRIBUTE_HPP_
#include <com/sun/star/beans/PropertyAttribute.hpp>
#endif

#ifndef _COM_SUN_STAR_FORM_FORMCOMPONENTTYPE_HPP_
#include <com/sun/star/form/FormComponentType.hpp>
#endif

namespace binfilter {

//.........................................................................
namespace frm
{
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::sdbc;
//using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::form;
using namespace ::com::sun::star::awt;
using namespace ::com::sun::star::io;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::util;

//------------------------------------------------------------------------------
InterfaceRef SAL_CALL OFixedTextModel_CreateInstance(const Reference<XMultiServiceFactory>& _rxFactory) throw (RuntimeException)
{
    return *(new OFixedTextModel(_rxFactory));
}

//------------------------------------------------------------------
DBG_NAME( OFixedTextModel )
//------------------------------------------------------------------
OFixedTextModel::OFixedTextModel( const Reference<XMultiServiceFactory>& _rxFactory )
        :OControlModel(_rxFactory, VCL_CONTROLMODEL_FIXEDTEXT)

{
    DBG_CTOR( OFixedTextModel, NULL );
    m_nClassId = FormComponentType::FIXEDTEXT;
}

//------------------------------------------------------------------
OFixedTextModel::OFixedTextModel( const OFixedTextModel* _pOriginal, const Reference<XMultiServiceFactory>& _rxFactory )
    :OControlModel( _pOriginal, _rxFactory )

{
    DBG_CTOR( OFixedTextModel, NULL );
}

//------------------------------------------------------------------
OFixedTextModel::~OFixedTextModel( )
{
    DBG_DTOR( OFixedTextModel, NULL );
}

//------------------------------------------------------------------------------
IMPLEMENT_DEFAULT_CLONING( OFixedTextModel )

//------------------------------------------------------------------------------
StringSequence SAL_CALL OFixedTextModel::getSupportedServiceNames() throw(::com::sun::star::uno::RuntimeException)
{
    StringSequence aSupported = OControlModel::getSupportedServiceNames();
    aSupported.realloc(aSupported.getLength() + 1);

    ::rtl::OUString* pArray = aSupported.getArray();
    pArray[aSupported.getLength()-1] = FRM_SUN_COMPONENT_FIXEDTEXT;
    return aSupported;
}

//------------------------------------------------------------------------------
Reference<starbeans::XPropertySetInfo> SAL_CALL OFixedTextModel::getPropertySetInfo() throw(RuntimeException)
{
    Reference<starbeans::XPropertySetInfo> xInfo(createPropertySetInfo(getInfoHelper()));
    return xInfo;
}

//------------------------------------------------------------------------------
cppu::IPropertyArrayHelper& OFixedTextModel::getInfoHelper()
{
    return *const_cast<OFixedTextModel*>(this)->getArrayHelper();
}

//------------------------------------------------------------------------------
void OFixedTextModel::fillProperties(
        Sequence< starbeans::Property >& _rProps,
        Sequence< starbeans::Property >& _rAggregateProps ) const
{
    FRM_BEGIN_PROP_HELPER(3)
        RemoveProperty(_rAggregateProps, PROPERTY_TABSTOP);

        DECL_PROP1(NAME,    rtl::OUString,  BOUND);
        DECL_PROP2(CLASSID, sal_Int16,  READONLY, TRANSIENT);
        DECL_PROP1(TAG,     rtl::OUString,  BOUND);
    FRM_END_PROP_HELPER();
}

//------------------------------------------------------------------------------
::rtl::OUString SAL_CALL OFixedTextModel::getServiceName() throw(RuntimeException)
{
    return FRM_COMPONENT_FIXEDTEXT; // old (non-sun) name for compatibility !
}

//------------------------------------------------------------------------------
void SAL_CALL OFixedTextModel::write(const Reference<XObjectOutputStream>& _rxOutStream)
    throw(IOException, RuntimeException)
{
    OControlModel::write(_rxOutStream);

    // Version
    _rxOutStream->writeShort(0x0002);
    writeHelpTextCompatibly(_rxOutStream);
}

//------------------------------------------------------------------------------
void SAL_CALL OFixedTextModel::read(const Reference<XObjectInputStream>& _rxInStream) throw(IOException, RuntimeException)
{
    OControlModel::read(_rxInStream);

    // Version
    sal_Int16 nVersion = _rxInStream->readShort();
    if (nVersion > 1)
        readHelpTextCompatibly(_rxInStream);
}

//.........................................................................
}
//.........................................................................

}
