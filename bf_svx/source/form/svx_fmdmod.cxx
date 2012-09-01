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
#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "fmdmod.hxx"

#include "fmservs.hxx"
#include <fmobj.hxx>
#include <unoshape.hxx>
#include "fmglob.hxx"
#include <legacysmgr/legacy_binfilters_smgr.hxx>
namespace binfilter {

using namespace ::binfilter::svxform;

//-----------------------------------------------------------------------------
/*N*/ ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >  SAL_CALL SvxFmMSFactory::createInstance(const ::rtl::OUString& ServiceSpecifier) throw( ::com::sun::star::uno::Exception, ::com::sun::star::uno::RuntimeException )
/*N*/ {
/*N*/   ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >  xRet;
/*N*/   if ( ServiceSpecifier.indexOf( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.form.component." )) ) == 0 )
/*N*/   {
/*?*/       xRet = ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(ServiceSpecifier);
/*N*/   }
/*N*/   else if ( ServiceSpecifier == ::rtl::OUString( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.drawing.ControlShape" )) ) )
/*N*/   {
/*N*/       SdrObject* pObj = new FmFormObj(OBJ_FM_CONTROL);
/*N*/       xRet = *new SvxShapeControl(pObj);
/*N*/   }
/*N*/   if (!xRet.is())
/*N*/       xRet = SvxUnoDrawMSFactory::createInstance(ServiceSpecifier);
/*N*/   return xRet;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
