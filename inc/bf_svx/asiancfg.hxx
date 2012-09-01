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
#ifndef _SVX_ASIANCFG_HXX
#define _SVX_ASIANCFG_HXX

#include <unotools/configitem.hxx>
#include <com/sun/star/uno/Sequence.h>
namespace com{namespace sun{namespace star{
namespace lang{
    struct Locale;
}}}}
namespace binfilter {

//-----------------------------------------------------------------------------
struct SvxAsianConfig_Impl;
class SvxAsianConfig : public ::utl::ConfigItem
{
    SvxAsianConfig_Impl* pImpl;

public:
    SvxAsianConfig(sal_Bool bEnableNotify = sal_True);
    virtual ~SvxAsianConfig();

void Notify( const ::com::sun::star::uno::Sequence< rtl::OUString >& aPropertyNames );
void Commit();

    void            Load();

    sal_Bool    IsKerningWesternTextOnly() const;

    sal_Int16   GetCharDistanceCompression() const;
    void        SetCharDistanceCompression(sal_Int16 nSet);

    ::com::sun::star::uno::Sequence< ::com::sun::star::lang::Locale>
                GetStartEndCharLocales();

};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
