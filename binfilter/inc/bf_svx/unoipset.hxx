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

#ifndef _SVX_UNOIPSET_HXX_
#define _SVX_UNOIPSET_HXX_

#include <com/sun/star/beans/XPropertySet.hpp>
#include <vector>

namespace binfilter {
struct SfxItemPropertyMap;
struct SvxIDPropertyCombine;
class SfxItemSet;
class SdrItemPool;

typedef ::std::vector< SvxIDPropertyCombine* > SvxIDPropertyCombineList;

class SvxShape;

class SvxItemPropertySet
{
    const SfxItemPropertyMap*   _pMap;
    const SfxItemPropertyMap*   mpLastMap;
    SvxIDPropertyCombineList*   pCombiList;
    sal_Bool                    mbConvertTwips;

public:
    SvxItemPropertySet( const SfxItemPropertyMap *pMap, sal_Bool bConvertTwips = sal_False );
    ~SvxItemPropertySet();

    // Methoden, die direkt mit dem ItemSet arbeiten
    ::com::sun::star::uno::Any getPropertyValue( const SfxItemPropertyMap* pMap, const SfxItemSet& rSet ) const;
    void setPropertyValue( const SfxItemPropertyMap* pMap, const ::com::sun::star::uno::Any& rVal, SfxItemSet& rSet ) const;

    // Methoden, die stattdessen Any benutzen
    ::com::sun::star::uno::Any getPropertyValue( const SfxItemPropertyMap* pMap ) const;
    void setPropertyValue( const SfxItemPropertyMap* pMap, const ::com::sun::star::uno::Any& rVal ) const;

    // Properties von einem anderen Set uebernehmen
    void ObtainSettingsFromPropertySet(SvxItemPropertySet& rPropSet,  SfxItemSet& rSet, ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > xSet );
    sal_Bool AreThereOwnUsrAnys() { return (pCombiList ? sal_True : sal_False); }
    ::com::sun::star::uno::Any* GetUsrAnyForID(sal_uInt16 nWID) const;
    void AddUsrAnyForID(const ::com::sun::star::uno::Any& rAny, sal_uInt16 nWID);

    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo > getPropertySetInfo() const;
    const SfxItemPropertyMap* getPropertyMap() const {return _pMap;}
    void setPropertyMap( const SfxItemPropertyMap *pMap ) { _pMap = pMap; }
    const SfxItemPropertyMap* getPropertyMapEntry(const ::rtl::OUString &rName) const;

    static ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo > getPropertySetInfo( const SfxItemPropertyMap* pMap );
};

}//end of namespace binfilter
#endif // _SVX_UNOIPSET_HXX_

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
