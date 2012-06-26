/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */
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

#include <bf_so3/plugin.hxx>
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

#include <bf_so3/applet.hxx>
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


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
