/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#ifdef _MSC_VER
#pragma hdrstop
#endif



#include "drawpage.hxx"
#include "drwlayer.hxx"
#include "pageuno.hxx"
namespace binfilter {

// STATIC DATA -----------------------------------------------------------

// -----------------------------------------------------------------------

/*N*/ ScDrawPage::ScDrawPage(ScDrawLayer& rNewModel, StarBASIC* pInBasic, BOOL bMasterPage) :
/*N*/   FmFormPage(rNewModel, pInBasic, bMasterPage)
/*N*/ {
/*N*/   SetSize( Size( LONG_MAX, LONG_MAX ) );
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ ScDrawPage::~ScDrawPage()
/*N*/ {
/*N*/ }

// -----------------------------------------------------------------------


// -----------------------------------------------------------------------

/*N*/ ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > ScDrawPage::createUnoPage()
/*N*/ {
/*N*/   return static_cast<cppu::OWeakObject*>( new ScPageObj( this ) );
/*N*/ }


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
