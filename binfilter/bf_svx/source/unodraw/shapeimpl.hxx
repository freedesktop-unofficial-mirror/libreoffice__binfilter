/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: shapeimpl.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 17:34:57 $
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
#ifndef _SVX_SHAPEIMPL_HXX
#define _SVX_SHAPEIMPL_HXX

#include "unoshape.hxx"
class SvGlobalName;
namespace binfilter {


/***********************************************************************
*                                                                      *
***********************************************************************/

class SvxShapeCaption : public SvxShapeText
{
public:
    SvxShapeCaption( SdrObject* pObj ) throw();
    virtual ~SvxShapeCaption() throw();
};

/***********************************************************************
*                                                                      *
***********************************************************************/

class SvxOle2Shape : public SvxShape
{
public:
    SvxOle2Shape( SdrObject* pObject, const SfxItemPropertyMap* pPropertySet ) throw ();
    virtual ~SvxOle2Shape() throw();

    sal_Bool createObject( const SvGlobalName &aClassName );

    // XInterface
    virtual ::com::sun::star::uno::Any SAL_CALL queryAggregation( const ::com::sun::star::uno::Type & rType ) throw(::com::sun::star::uno::RuntimeException);

    //XPropertySet
    virtual void SAL_CALL   setPropertyValue( const ::rtl::OUString& aPropertyName, const ::com::sun::star::uno::Any& aValue )  throw(::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::beans::PropertyVetoException, ::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Any SAL_CALL getPropertyValue( const ::rtl::OUString& PropertyName ) throw(::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);
};

/***********************************************************************
*                                                                      *
***********************************************************************/
}//end of namespace binfilter
#ifndef SVX_LIGHT

#ifndef _PLUGIN_HXX
#include <so3/plugin.hxx>
#endif
namespace binfilter {
class SvxPluginShape : public SvxOle2Shape
{
private:
    SvPlugInObjectRef mxPlugin;

public:
    SvxPluginShape( SdrObject* pObj ) throw();
    virtual ~SvxPluginShape() throw();

    virtual void Create( SdrObject* pNewOpj, SvxDrawPage* pNewPage = NULL ) throw ();

    //XPropertySet
    virtual void SAL_CALL   setPropertyValue( const ::rtl::OUString& aPropertyName, const ::com::sun::star::uno::Any& aValue )  throw(::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::beans::PropertyVetoException, ::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Any SAL_CALL getPropertyValue( const ::rtl::OUString& PropertyName ) throw(::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);
};
}//end of namespace binfilter
#endif

/***********************************************************************
*                                                                      *
***********************************************************************/

#ifndef SVX_LIGHT

#ifndef _APPLET_HXX
#include <so3/applet.hxx>
#endif
namespace binfilter {
class SvxAppletShape : public SvxOle2Shape
{
private:
    SvAppletObjectRef mxApplet;

public:
    SvxAppletShape( SdrObject* pObj ) throw();
    virtual ~SvxAppletShape() throw();

    virtual void Create( SdrObject* pNewOpj, SvxDrawPage* pNewPage = NULL ) throw ();

    //XPropertySet
    virtual void SAL_CALL   setPropertyValue( const ::rtl::OUString& aPropertyName, const ::com::sun::star::uno::Any& aValue )  throw(::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::beans::PropertyVetoException, ::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Any SAL_CALL getPropertyValue( const ::rtl::OUString& PropertyName ) throw(::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);
};
}//end of namespace binfilter
#endif

/***********************************************************************
*                                                                      *
***********************************************************************/

#ifndef SVX_LIGHT

namespace binfilter {
class SvxFrameShape : public SvxOle2Shape
{
public:
    SvxFrameShape( SdrObject* pObj ) throw();
    virtual ~SvxFrameShape() throw();

    virtual void Create( SdrObject* pNewOpj, SvxDrawPage* pNewPage = NULL ) throw ();

    //XPropertySet
    virtual void SAL_CALL   setPropertyValue( const ::rtl::OUString& aPropertyName, const ::com::sun::star::uno::Any& aValue )  throw(::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::beans::PropertyVetoException, ::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Any SAL_CALL getPropertyValue( const ::rtl::OUString& PropertyName ) throw(::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::lang::WrappedTargetException, ::com::sun::star::uno::RuntimeException);
};
}//end of namespace binfilter
#endif

#endif


