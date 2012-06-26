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

#include "fmobjfac.hxx"
#include "fmglob.hxx"
#include "fmobj.hxx"

#include <com/sun/star/sdbc/XRowSetListener.hpp>
#include <com/sun/star/sdb/XSQLQueryComposerFactory.hpp>
#include <com/sun/star/frame/XFrame.hpp>

#include "fmshimp.hxx"
#include "svxids.hrc"
#include "fmresids.hrc"
#include "fmservs.hxx"
#include "fmprop.hrc"

namespace binfilter {

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::binfilter::svxform;

/*************************************************************************
|*
|* Ctor
|*
\************************************************************************/
/*N*/ FmFormObjFactory::FmFormObjFactory()
/*N*/ {
/*N*/   SdrObjFactory::InsertMakeObjectHdl(LINK(this, FmFormObjFactory, MakeObject));
/*N*/
/*N*/   // ImplSmartRegisterUnoServices();
/*N*/
/*N*/ }


/*************************************************************************
|*
|* Dtor
|*
\************************************************************************/
/*N*/ FmFormObjFactory::~FmFormObjFactory()
/*N*/ {
/*N*/ }


/*************************************************************************
|*
|* ::com::sun::star::form::Form-Objekte erzeugen
|*
\************************************************************************/

/*N*/ IMPL_LINK(FmFormObjFactory, MakeObject, SdrObjFactory*, pObjFactory)
/*N*/ {
/*N*/   if (pObjFactory->nInventor == FmFormInventor)
/*N*/   {
/*N*/       switch (pObjFactory->nIdentifier)
/*N*/       {
/*N*/           case OBJ_FM_CONTROL:    // allgemeines Object
/*N*/           {
/*N*/               pObjFactory->pNewObj = new FmFormObj(pObjFactory->nIdentifier);
/*N*/           }   break;
/*?*/           default:
                    break;
/*?*/       }
/*?*/   }
/*N*/
/*N*/   return 0;
/*N*/ }



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
