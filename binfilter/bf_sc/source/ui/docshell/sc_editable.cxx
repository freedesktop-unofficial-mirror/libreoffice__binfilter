/*************************************************************************
 *
 *  $RCSfile: sc_editable.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:39:41 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifdef PCH
#include "ui_pch.hxx"
#endif

#pragma hdrstop

#include "editable.hxx"
#include "document.hxx"
#include "viewfunc.hxx"
#include "globstr.hrc"
namespace binfilter {

//------------------------------------------------------------------

/*N*/ ScEditableTester::ScEditableTester() :
/*N*/   bIsEditable( TRUE ),
/*N*/   bOnlyMatrix( TRUE )
/*N*/ {
/*N*/ }

//STRIP001 void ScEditableTester::Reset()
//STRIP001 {
//STRIP001  bIsEditable = bOnlyMatrix = TRUE;
//STRIP001 }

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

/*N*/ ScEditableTester::ScEditableTester( ScDocument* pDoc, const ScRange& rRange ) :
/*N*/   bIsEditable( TRUE ),
/*N*/   bOnlyMatrix( TRUE )
/*N*/ {
/*N*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 TestRange( pDoc, rRange );
/*N*/ }

/*N*/ ScEditableTester::ScEditableTester( ScDocument* pDoc, const ScMarkData& rMark ) :
/*N*/   bIsEditable( TRUE ),
/*N*/   bOnlyMatrix( TRUE )
/*N*/ {
/*N*/   DBG_BF_ASSERT(0, "STRIP"); //STRIP001 TestSelection( pDoc, rMark );
/*N*/ }

//STRIP001 ScEditableTester::ScEditableTester( ScViewFunc* pView ) :
//STRIP001  bIsEditable( TRUE ),
//STRIP001  bOnlyMatrix( TRUE )
//STRIP001 {
//STRIP001  TestView( pView );
//STRIP001 }

//------------------------------------------------------------------

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

//STRIP001 void ScEditableTester::TestRange( ScDocument* pDoc, const ScRange& rRange )
//STRIP001 {
//STRIP001  USHORT nStartCol = rRange.aStart.Col();
//STRIP001  USHORT nStartRow = rRange.aStart.Row();
//STRIP001  USHORT nStartTab = rRange.aStart.Tab();
//STRIP001  USHORT nEndCol = rRange.aEnd.Col();
//STRIP001  USHORT nEndRow = rRange.aEnd.Row();
//STRIP001  USHORT nEndTab = rRange.aEnd.Tab();
//STRIP001  for (USHORT nTab=nStartTab; nTab<=nEndTab; nTab++)
//STRIP001      TestBlock( pDoc, nTab, nStartCol, nStartRow, nEndCol, nEndRow );
//STRIP001 }

//STRIP001 void ScEditableTester::TestSelection( ScDocument* pDoc, const ScMarkData& rMark )
//STRIP001 {
//STRIP001  if ( bIsEditable || bOnlyMatrix )
//STRIP001  {
//STRIP001      BOOL bThisMatrix;
//STRIP001      if ( !pDoc->IsSelectionEditable( rMark, &bThisMatrix ) )
//STRIP001      {
//STRIP001          bIsEditable = FALSE;
//STRIP001          if ( !bThisMatrix )
//STRIP001              bOnlyMatrix = FALSE;
//STRIP001      }
//STRIP001  }
//STRIP001 }

//STRIP001 void ScEditableTester::TestView( ScViewFunc* pView )
//STRIP001 {
//STRIP001  if ( bIsEditable || bOnlyMatrix )
//STRIP001  {
//STRIP001      BOOL bThisMatrix;
//STRIP001      if ( !pView->SelectionEditable( &bThisMatrix ) )
//STRIP001      {
//STRIP001          bIsEditable = FALSE;
//STRIP001          if ( !bThisMatrix )
//STRIP001              bOnlyMatrix = FALSE;
//STRIP001      }
//STRIP001  }
//STRIP001 }

//------------------------------------------------------------------

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
