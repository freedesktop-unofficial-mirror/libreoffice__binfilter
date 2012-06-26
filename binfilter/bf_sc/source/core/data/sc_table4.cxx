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

#ifdef _MSC_VER
#pragma optimize("",off)
#endif
                                        // sonst Absturz Win beim Fuellen

#include "scitems.hxx"

#include "globstr.hrc"
#include "document.hxx"
#include "autoform.hxx"
namespace binfilter {

// STATIC DATA -----------------------------------------------------------

#define _D_MAX_LONG_  (double) 0x7fffffff

extern USHORT nScFillModeMouseModifier;     // global.cxx

// -----------------------------------------------------------------------














#define LF_LEFT         1
#define LF_TOP          2
#define LF_RIGHT        4
#define LF_BOTTOM       8
#define LF_ALL          (LF_LEFT | LF_TOP | LF_RIGHT | LF_BOTTOM)



/*N*/ void ScTable::SetError( USHORT nCol, USHORT nRow, USHORT nError)
/*N*/ {
/*N*/   if (ValidColRow(nCol, nRow))
/*N*/       aCol[nCol].SetError( nRow, nError );
/*N*/ }





/*N*/ BOOL ScTable::TestTabRefAbs(USHORT nTable)
/*N*/ {
/*N*/   BOOL bRet = FALSE;
/*N*/   for (USHORT i=0; i <= MAXCOL; i++)
/*N*/       if (aCol[i].TestTabRefAbs(nTable))
/*N*/           bRet = TRUE;
/*N*/   return bRet;
/*N*/ }


/*N*/ void ScTable::CompileDBFormula( BOOL bCreateFormulaString )
/*N*/ {
/*N*/   for (USHORT i=0; i<=MAXCOL; i++) aCol[i].CompileDBFormula( bCreateFormulaString );
/*N*/ }

/*N*/ void ScTable::CompileNameFormula( BOOL bCreateFormulaString )
/*N*/ {
/*N*/   for (USHORT i=0; i<=MAXCOL; i++) aCol[i].CompileNameFormula( bCreateFormulaString );
/*N*/ }

/*N*/ void ScTable::CompileColRowNameFormula()
/*N*/ {
/*N*/   for (USHORT i=0; i<=MAXCOL; i++) aCol[i].CompileColRowNameFormula();
/*N*/ }






}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
