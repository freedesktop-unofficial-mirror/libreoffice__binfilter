/*************************************************************************
 *
 *  $RCSfile: sc_documen6.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 14:34:56 $
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
#include "core_pch.hxx"
#endif

#pragma hdrstop

#include "scitems.hxx"
#include <bf_svx/scripttypeitem.hxx>

#include <com/sun/star/i18n/XBreakIterator.hpp>
#include <com/sun/star/i18n/ScriptType.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>

#include "document.hxx"
#include "cell.hxx"
#include "cellform.hxx"
#include "patattr.hxx"
#include "scrdata.hxx"
#include "poolhelp.hxx"

using namespace com::sun::star;

#define SC_BREAKITER_SERVICE    "com.sun.star.i18n.BreakIterator"

//
//  this file is compiled with exceptions enabled
//  put functions here that need exceptions!
//

// -----------------------------------------------------------------------

/*N*/ const uno::Reference< i18n::XBreakIterator >& ScDocument::GetBreakIterator()
/*N*/ {
/*N*/   if ( !pScriptTypeData )
/*N*/       pScriptTypeData = new ScScriptTypeData;
/*N*/     if ( !pScriptTypeData->xBreakIter.is() )
/*N*/     {
/*N*/         uno::Reference< uno::XInterface > xInterface = xServiceManager->createInstance(
/*N*/                             ::rtl::OUString::createFromAscii( SC_BREAKITER_SERVICE ) );
/*N*/         pScriptTypeData->xBreakIter = uno::Reference< i18n::XBreakIterator >( xInterface, uno::UNO_QUERY );
/*N*/       DBG_ASSERT( pScriptTypeData->xBreakIter.is(), "can't get BreakIterator" );
/*N*/   }
/*N*/     return pScriptTypeData->xBreakIter;
/*N*/ }

//STRIP001 BOOL ScDocument::HasStringWeakCharacters( const String& rString )
//STRIP001 {
//STRIP001  BYTE nRet = 0;
//STRIP001  if (rString.Len())
//STRIP001  {
//STRIP001         uno::Reference<i18n::XBreakIterator> xBreakIter = GetBreakIterator();
//STRIP001      if ( xBreakIter.is() )
//STRIP001      {
//STRIP001          rtl::OUString aText = rString;
//STRIP001          sal_Int32 nLen = aText.getLength();
//STRIP001
//STRIP001          sal_Int32 nPos = 0;
//STRIP001          do
//STRIP001          {
//STRIP001              sal_Int16 nType = xBreakIter->getScriptType( aText, nPos );
//STRIP001              if ( nType == i18n::ScriptType::WEAK )
//STRIP001                  return TRUE;                            // found
//STRIP001
//STRIP001              nPos = xBreakIter->endOfScript( aText, nPos, nType );
//STRIP001          }
//STRIP001          while ( nPos >= 0 && nPos < nLen );
//STRIP001      }
//STRIP001  }
//STRIP001
//STRIP001  return FALSE;       // none found
//STRIP001 }

/*N*/ BYTE ScDocument::GetStringScriptType( const String& rString )
/*N*/ {
/*N*/
/*N*/   BYTE nRet = 0;
/*N*/   if (rString.Len())
/*N*/   {
/*N*/         uno::Reference<i18n::XBreakIterator> xBreakIter = GetBreakIterator();
/*N*/       if ( xBreakIter.is() )
/*N*/       {
/*N*/           rtl::OUString aText = rString;
/*N*/           sal_Int32 nLen = aText.getLength();
/*N*/
/*N*/           sal_Int32 nPos = 0;
/*N*/           do
/*N*/           {
/*N*/               sal_Int16 nType = xBreakIter->getScriptType( aText, nPos );
/*N*/               switch ( nType )
/*N*/               {
/*N*/                   case i18n::ScriptType::LATIN:
/*N*/                       nRet |= SCRIPTTYPE_LATIN;
/*N*/                       break;
/*N*/                   case i18n::ScriptType::ASIAN:
/*N*/                       nRet |= SCRIPTTYPE_ASIAN;
/*N*/                       break;
/*N*/                   case i18n::ScriptType::COMPLEX:
/*N*/                       nRet |= SCRIPTTYPE_COMPLEX;
/*N*/                       break;
/*N*/                   // WEAK is ignored
/*N*/               }
/*N*/               nPos = xBreakIter->endOfScript( aText, nPos, nType );
/*N*/           }
/*N*/           while ( nPos >= 0 && nPos < nLen );
/*N*/       }
/*N*/   }
/*N*/   return nRet;
/*N*/ }

/*N*/ BYTE ScDocument::GetCellScriptType( ScBaseCell* pCell, ULONG nNumberFormat )
/*N*/ {
/*N*/   if ( !pCell )
/*N*/       return 0;       // empty
/*N*/
/*N*/   BYTE nStored = pCell->GetScriptType();
/*N*/   if ( nStored != SC_SCRIPTTYPE_UNKNOWN )         // stored value valid?
/*N*/       return nStored;                             // use stored value
/*N*/
/*N*/   String aStr;
/*N*/   Color* pColor;
/*N*/   ScCellFormat::GetString( pCell, nNumberFormat, aStr, &pColor, *xPoolHelper->GetFormTable() );
/*N*/
/*N*/   BYTE nRet = GetStringScriptType( aStr );
/*N*/
/*N*/   pCell->SetScriptType( nRet );       // store for later calls
/*N*/
/*N*/   return nRet;
/*N*/ }

/*N*/ BYTE ScDocument::GetScriptType( USHORT nCol, USHORT nRow, USHORT nTab, ScBaseCell* pCell )
/*N*/ {
/*N*/   // if cell is not passed, take from document
/*N*/
/*N*/   if (!pCell)
/*N*/   {
/*N*/       pCell = GetCell( ScAddress( nCol, nRow, nTab ) );
/*N*/       if ( !pCell )
/*N*/           return 0;       // empty
/*N*/   }
/*N*/
/*N*/   // if script type is set, don't have to get number formats
/*N*/
/*N*/   BYTE nStored = pCell->GetScriptType();
/*N*/   if ( nStored != SC_SCRIPTTYPE_UNKNOWN )         // stored value valid?
/*N*/       return nStored;                             // use stored value
/*N*/
/*N*/   // include number formats from conditional formatting
/*N*/
/*N*/   const ScPatternAttr* pPattern = GetPattern( nCol, nRow, nTab );
/*N*/   if (!pPattern) return 0;
/*N*/   const SfxItemSet* pCondSet = NULL;
/*N*/   if ( ((const SfxUInt32Item&)pPattern->GetItem(ATTR_CONDITIONAL)).GetValue() )
/*N*/       pCondSet = GetCondResult( nCol, nRow, nTab );
/*N*/
/*N*/   ULONG nFormat = pPattern->GetNumberFormat( xPoolHelper->GetFormTable(), pCondSet );
/*N*/   return GetCellScriptType( pCell, nFormat );
/*N*/ }


