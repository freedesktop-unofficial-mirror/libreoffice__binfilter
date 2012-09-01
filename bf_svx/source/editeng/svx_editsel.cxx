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

#include <vcl/window.hxx>

#include <impedit.hxx>
#include <editview.hxx>
namespace binfilter {

//  ----------------------------------------------------------------------
//  class EditSelFunctionSet
//  ----------------------------------------------------------------------
/*N*/ EditSelFunctionSet::EditSelFunctionSet()
/*N*/ {
/*N*/   pCurView = NULL;
/*N*/ }

//  ----------------------------------------------------------------------
//  class EditSelectionEngine
//  ----------------------------------------------------------------------
/*N*/ EditSelectionEngine::EditSelectionEngine() : SelectionEngine( (Window*)0 )
/*N*/ {
/*N*/   // Wegen Bug OV: (1994)
/*N*/   // 1995: RangeSelection lassen, SingleSelection nur fuer ListBoxen geeignet!
/*N*/   SetSelectionMode( RANGE_SELECTION );
/*N*/   EnableDrag( TRUE );
/*N*/ }

/*N*/ void EditSelectionEngine::SetCurView( EditView* pNewView )
/*N*/ {
/*N*/   if ( GetFunctionSet() )
/*N*/       ((EditSelFunctionSet*)GetFunctionSet())->SetCurView( pNewView );
/*N*/
/*N*/   if ( pNewView )
/*?*/       SetWindow( pNewView->GetWindow() );
/*N*/   else
/*N*/       SetWindow( (Window*)0 );
/*N*/ }


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
