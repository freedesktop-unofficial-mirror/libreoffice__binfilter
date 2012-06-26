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

#ifndef SVX_UNOPROV_HXX
#define SVX_UNOPROV_HXX

#include <com/sun/star/lang/XServiceInfo.hpp>

#include <bf_svx/svdpool.hxx>
#include <bf_svtools/itemprop.hxx>
#include <com/sun/star/uno/Sequence.hxx>

namespace binfilter {

/***********************************************************************
* class UHashMap                                                       *
***********************************************************************/

#define UHASHMAP_NOTFOUND sal::static_int_cast< UINT32 >(~0)

class UHashMap
{
    UHashMap() {}
public:
    static sal_uInt32 getId( const ::rtl::OUString& rCompareString );
    static rtl::OUString getNameFromId (sal_uInt32 nId);
    static ::com::sun::star::uno::Sequence< rtl::OUString > getServiceNames();
};

/***********************************************************************
* Soriterer                                                            *
***********************************************************************/

#define SVXMAP_SHAPE                0
#define SVXMAP_CONNECTOR            1
#define SVXMAP_DIMENSIONING         2
#define SVXMAP_CIRCLE               3
#define SVXMAP_POLYPOLYGON          4
#define SVXMAP_POLYPOLYGONBEZIER    5
#define SVXMAP_GRAPHICOBJECT        6
#define SVXMAP_3DSCENEOBJECT        7
#define SVXMAP_3DCUBEOBJEKT         8
#define SVXMAP_3DSPHEREOBJECT       9
#define SVXMAP_3DLATHEOBJECT        10
#define SVXMAP_3DEXTRUDEOBJECT      11
#define SVXMAP_3DPOLYGONOBJECT      12
#define SVXMAP_ALL                  13
#define SVXMAP_GROUP                14
#define SVXMAP_CAPTION              15
#define SVXMAP_OLE2                 16
#define SVXMAP_PLUGIN               17
#define SVXMAP_FRAME                18
#define SVXMAP_APPLET               19
#define SVXMAP_CONTROL              20
#define SVXMAP_TEXT                 21
#define SVXMAP_END                  22  // last+1 !

/***********************************************************************
* SvxUnoPropertyMapProvider                                            *
***********************************************************************/
class SvxUnoPropertyMapProvider
{
    SfxItemPropertyMap* aMapArr[SVXMAP_END];
    void Sort(USHORT nId);
public:
    SvxUnoPropertyMapProvider();
    SfxItemPropertyMap* GetMap(UINT16 nPropertyId);
};

/***********************************************************************
* Globals                                                              *
***********************************************************************/

const sal_Int16 OBJ_OLE2_APPLET = 100;
const sal_Int16 OBJ_OLE2_PLUGIN = 101;

extern SvxUnoPropertyMapProvider aSvxMapProvider;

#define SFX_METRIC_ITEM             (0x40)
#define E3D_INVENTOR_FLAG           (0x80000000)
}//end of namespace binfilter
#include <bf_svx/unoipset.hxx>
namespace binfilter {

/***********************************************************************
* class SvxServiceInfoHelper                                           *
***********************************************************************/

/** this class provides a basic helper for classes suporting the XServiceInfo Interface.
 *
 *  you can overload the <code>getSupprotedServiceNames</code> to implement a XServiceInfo.
 *  you can use the static helper methods to combine your services with that of parent
 *  or aggregatet classes.
 */
class SvxServiceInfoHelper : public ::com::sun::star::lang::XServiceInfo
{
public:
    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName() throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName ) throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames() throw(::com::sun::star::uno::RuntimeException);

    // helper
    static void addToSequence( ::com::sun::star::uno::Sequence< ::rtl::OUString >& rSeq,UINT16 nServices, /* sal_Char* */... ) throw();
    static sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName, const ::com::sun::star::uno::Sequence< ::rtl::OUString >& SupportedServices ) throw();

protected:
    ~SvxServiceInfoHelper() {}
};

/***********************************************************************
* class SvxPropertySetInfoPool                                         *
***********************************************************************/

const sal_Int32 SVXUNO_SERVICEID_COM_SUN_STAR_DRAWING_DEFAULTS = 0;
const sal_Int32 SVXUNO_SERVICEID_COM_SUN_STAR_DRAWING_DEFAULTS_WRITER = 1;
const sal_Int32 SVXUNO_SERVICEID_LASTID = 1;
}//end of namespace binfilter
namespace comphelper { class PropertySetInfo; }
namespace binfilter {
class SvxPropertySetInfoPool
{
public:
    static comphelper::PropertySetInfo* getOrCreate( sal_Int32 nServiceId ) throw();

private:
    static comphelper::PropertySetInfo* mpInfos[SVXUNO_SERVICEID_LASTID+1];
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
