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

#include "editable.hxx"
#include "document.hxx"
#include "globstr.hrc"
#include "markdata.hxx"

namespace binfilter {


/*N*/ ScEditableTester::ScEditableTester() :
/*N*/   bIsEditable( TRUE ),
/*N*/   bOnlyMatrix( TRUE )
/*N*/ {
/*N*/ }


/*N*/ ScEditableTester::ScEditableTester( ScDocument* pDoc, USHORT nTab,
/*N*/                       USHORT nStartCol, USHORT nStartRow, USHORT nEndCol, USHORT nEndRow ) :
/*N*/   bIsEditable( TRUE ),
/*N*/   bOnlyMatrix( TRUE )
/*N*/ {
/*N*/   TestBlock( pDoc, nTab, nStartCol, nStartRow, nEndCol, nEndRow );
/*N*/ }

/*N*/ ScEditableTester::ScEditableTester( ScDocument* pDoc,
/*N*/                       USHORT nStartCol, USHORT nStartRow, USHORT nEndCol, USHORT nEndRow,
/*N*/                       const ScMarkData& rMark ) :
/*N*/   bIsEditable( TRUE ),
/*N*/   bOnlyMatrix( TRUE )
/*N*/ {
/*N*/   TestSelectedBlock( pDoc, nStartCol, nStartRow, nEndCol, nEndRow, rMark );
/*N*/ }

/*N*/ ScEditableTester::ScEditableTester( ScDocument* /*pDoc*/, const ScRange& /*rRange*/ ) :
/*N*/   bIsEditable( TRUE ),
/*N*/   bOnlyMatrix( TRUE )
/*N*/ {
/*N*/ }

/*N*/ ScEditableTester::ScEditableTester( ScDocument* /*pDoc*/, const ScMarkData& /*rMark*/ ) :
/*N*/   bIsEditable( TRUE ),
/*N*/   bOnlyMatrix( TRUE )
/*N*/ {
/*N*/ }


/*N*/ void ScEditableTester::TestBlock( ScDocument* pDoc, USHORT nTab,
/*N*/                       USHORT nStartCol, USHORT nStartRow, USHORT nEndCol, USHORT nEndRow )
/*N*/ {
/*N*/   if ( bIsEditable || bOnlyMatrix )
/*N*/   {
/*N*/       BOOL bThisMatrix;
/*N*/       if ( !pDoc->IsBlockEditable( nTab, nStartCol, nStartRow, nEndCol, nEndRow, &bThisMatrix ) )
/*N*/       {
/*N*/           bIsEditable = FALSE;
/*N*/           if ( !bThisMatrix )
/*N*/               bOnlyMatrix = FALSE;
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ void ScEditableTester::TestSelectedBlock( ScDocument* pDoc,
/*N*/                       USHORT nStartCol, USHORT nStartRow, USHORT nEndCol, USHORT nEndRow,
/*N*/                       const ScMarkData& rMark )
/*N*/ {
/*N*/   USHORT nTabCount = pDoc->GetTableCount();
/*N*/   for (USHORT nTab=0; nTab<nTabCount; nTab++)
/*N*/       if (rMark.GetTableSelect(nTab))
/*N*/           TestBlock( pDoc, nTab, nStartCol, nStartRow, nEndCol, nEndRow );
/*N*/ }

/*N*/ USHORT ScEditableTester::GetMessageId() const
/*N*/ {
/*N*/   if (bIsEditable)
/*N*/       return 0;
/*N*/   else if (bOnlyMatrix)
/*N*/       return STR_MATRIXFRAGMENTERR;
/*N*/   else
/*N*/       return STR_PROTECTIONERR;
/*N*/ }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
