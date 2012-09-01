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


#define _OUTLINER_CXX
#include <outleeng.hxx>

#include "editview.hxx"

namespace binfilter {

/*N*/ OutlinerView::~OutlinerView()
/*N*/ {
/*N*/   delete pEditView;
/*N*/ }

/*N*/ Rectangle OutlinerView::GetVisArea() const
/*N*/ {
/*N*/   return pEditView->GetVisArea();
/*N*/ }

/*N*/ void OutlinerView::SetSelection( const ESelection& rSel )
/*N*/ {
/*N*/   pEditView->SetSelection( rSel );
/*N*/ }

/*N*/ Window* OutlinerView::GetWindow() const
/*N*/ {
/*N*/   return pEditView->GetWindow();
/*N*/ }

/*N*/ Rectangle OutlinerView::GetOutputArea() const
/*N*/ {
/*N*/   return pEditView->GetOutputArea();
/*N*/ }

/*N*/ ESelection OutlinerView::GetSelection()
/*N*/ {
/*N*/   return pEditView->GetSelection();
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
