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


#include <frmfmt.hxx>

#include <horiornt.hxx>

#include <doc.hxx>
#include <drawdoc.hxx>
#include <dpage.hxx>
#include <dcontact.hxx>
#include <docsh.hxx>
#include <flyfrm.hxx>
#include <com/sun/star/drawing/XDrawPageSupplier.hpp>
namespace binfilter {

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::drawing;
using namespace ::com::sun::star::frame;

/*?*/ SwDPage::SwDPage(SwDrawDocument& rNewModel, BOOL bMasterPage) :
/*?*/   FmFormPage(rNewModel, 0, bMasterPage),
/*?*/   pGridLst( 0 ),
/*?*/   rDoc(rNewModel.GetDoc())
/*?*/ {
/*?*/ }


/*N*/ SwDPage::~SwDPage()
/*N*/ {
/*N*/   delete pGridLst;
/*N*/ }


/*************************************************************************
|*
|*  SwDPage::ReplaceObject()
|*
*************************************************************************/

/*N*/ SdrObject*  SwDPage::ReplaceObject( SdrObject* pNewObj, ULONG nObjNum )
/*N*/ {
/*N*/   return FmFormPage::ReplaceObject( pNewObj, nObjNum );
/*N*/ }

/*N*/ Reference< XInterface > SwDPage::createUnoPage()
/*N*/ {
/*N*/   Reference<XModel> xModel = rDoc.GetDocShell()->GetBaseModel();
/*N*/   Reference<XDrawPageSupplier> xPageSupp(xModel, UNO_QUERY);
/*N*/   return xPageSupp->getDrawPage();
/*N*/ }



}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
