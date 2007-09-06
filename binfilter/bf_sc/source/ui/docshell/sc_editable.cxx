/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_editable.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:06:28 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#ifdef PCH
#endif

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "editable.hxx"
#include "document.hxx"
#include "globstr.hrc"
#include "markdata.hxx"

namespace binfilter {

//------------------------------------------------------------------

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

/*N*/ ScEditableTester::ScEditableTester( ScDocument* pDoc, const ScRange& rRange ) :
/*N*/   bIsEditable( TRUE ),
/*N*/   bOnlyMatrix( TRUE )
/*N*/ {
/*N*/ }

/*N*/ ScEditableTester::ScEditableTester( ScDocument* pDoc, const ScMarkData& rMark ) :
/*N*/   bIsEditable( TRUE ),
/*N*/   bOnlyMatrix( TRUE )
/*N*/ {
/*N*/ }


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
