/*************************************************************************
 *
 *  $RCSfile: sw_macrofld.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:18:31 $
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


#pragma hdrstop

#ifndef _HINTIDS_HXX
#include <hintids.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
#ifndef _DOCUFLD_HXX
#include <docufld.hxx>
#endif
#ifndef _UNOFLDMID_H
#include <unofldmid.h>
#endif

using namespace ::com::sun::star;
using namespace ::rtl;
/*--------------------------------------------------------------------
    Beschreibung: MacroFeldtypen
 --------------------------------------------------------------------*/

/*N*/ SwMacroFieldType::SwMacroFieldType(SwDoc* pDocument)
/*N*/   : SwFieldType( RES_MACROFLD ),
/*N*/     pDoc(pDocument)
/*N*/ {
/*N*/ }

/*N*/ SwFieldType* SwMacroFieldType::Copy() const
/*N*/ {
DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001 //STRIP001   SwMacroFieldType* pType = new SwMacroFieldType(pDoc);
//STRIP001  return pType;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Das Macrofeld selbst
 --------------------------------------------------------------------*/

/*N*/ SwMacroField::SwMacroField(SwMacroFieldType* pType,
/*N*/                          const String& rLibAndName, const String& rTxt) :
/*N*/   SwField(pType), aMacro(rLibAndName), aText(rTxt)
/*N*/ {
/*N*/ }

/*N*/ String SwMacroField::Expand() const
/*N*/ {     // Button malen anstatt von
/*N*/   return aText ;
/*N*/ }

/*N*/ SwField* SwMacroField::Copy() const
/*N*/ {
/*N*/   return new SwMacroField((SwMacroFieldType*)GetTyp(), aMacro, aText);
/*N*/ }

/*N*/ String SwMacroField::GetCntnt(BOOL bName) const
/*N*/ {
/*N*/   if(bName)
/*N*/   {
/*?*/       String aStr(GetTyp()->GetName());
/*?*/       aStr += ' ';
/*?*/       aStr += aMacro;
/*?*/       return aStr;
/*N*/   }
/*N*/   return Expand();
/*N*/ }

/*N*/ String SwMacroField::GetLibName() const
/*N*/ {
/*N*/   if (aMacro.Len())
/*N*/   {
/*N*/       USHORT nPos = aMacro.Len();
/*N*/
/*N*/       for (USHORT i = 0; i < 3 && nPos > 0; i++)
/*N*/           while (aMacro.GetChar(--nPos) != '.' && nPos > 0);
/*N*/
/*N*/       return aMacro.Copy(0, nPos );
/*N*/   }
/*N*/
/*?*/   DBG_ASSERT(0, "Kein Macroname vorhanden")
/*?*/   return aEmptyStr;
/*N*/ }

/*N*/ String SwMacroField::GetMacroName() const
/*N*/ {
/*N*/   if (aMacro.Len())
/*N*/   {
/*N*/       USHORT nPos = aMacro.Len();
/*N*/
/*N*/       for (USHORT i = 0; i < 3 && nPos > 0; i++)
/*N*/           while (aMacro.GetChar(--nPos) != '.' && nPos > 0);
/*N*/
/*N*/       return aMacro.Copy( ++nPos );
/*N*/   }
/*N*/
/*?*/   DBG_ASSERT(0, "Kein Macroname vorhanden")
/*?*/   return aEmptyStr;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: LibName und MacroName
 --------------------------------------------------------------------*/

//STRIP001 void SwMacroField::SetPar1(const String& rStr)
//STRIP001 {
//STRIP001  aMacro = rStr;
//STRIP001 }

/*N*/ const String& SwMacroField::GetPar1() const
/*N*/ {
/*N*/   return aMacro;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Macrotext
 --------------------------------------------------------------------*/

//STRIP001 void SwMacroField::SetPar2(const String& rStr)
//STRIP001 {
//STRIP001  aText = rStr;
//STRIP001 }

/*N*/ String SwMacroField::GetPar2() const
/*N*/ {
/*N*/   return aText;
/*N*/ }

/*-----------------05.03.98 13:38-------------------

--------------------------------------------------*/
/*N*/ BOOL SwMacroField::QueryValue( uno::Any& rAny, BYTE nMId ) const
/*N*/ {
/*N*/     nMId &= ~CONVERT_TWIPS;
/*N*/   switch( nMId )
/*N*/   {
/*N*/   case FIELD_PROP_PAR1:
/*N*/       rAny <<= OUString(GetMacroName());
/*N*/       break;
/*N*/   case FIELD_PROP_PAR2:
/*N*/       rAny <<= OUString(aText);
/*N*/       break;
/*N*/   case FIELD_PROP_PAR3:
/*N*/       rAny <<= OUString(GetLibName());
/*N*/       break;
/*N*/   default:
/*?*/       DBG_ERROR("illegal property");
/*N*/   }
/*N*/   return TRUE;
/*N*/ }
/*-----------------05.03.98 13:38-------------------

--------------------------------------------------*/
//STRIP001 BOOL SwMacroField::PutValue( const uno::Any& rAny, BYTE nMId )
//STRIP001 {
//STRIP001  String sTmp;
//STRIP001     nMId &= ~CONVERT_TWIPS;
//STRIP001  switch( nMId )
//STRIP001  {
//STRIP001  case FIELD_PROP_PAR1:
//STRIP001      CreateMacroString( aMacro, ::GetString(rAny, sTmp), GetLibName());
//STRIP001      break;
//STRIP001  case FIELD_PROP_PAR2:
//STRIP001      ::GetString( rAny, aText );
//STRIP001      break;
//STRIP001  case FIELD_PROP_PAR3:
//STRIP001      CreateMacroString(aMacro, GetMacroName(), ::GetString(rAny, sTmp) );
//STRIP001      break;
//STRIP001  default:
//STRIP001      DBG_ERROR("illegal property");
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

// create an internally used macro name from the library and macro name parts
/*N*/ void SwMacroField::CreateMacroString(
/*N*/     String& rMacro,
/*N*/     const String& rMacroName,
/*N*/     const String& rLibraryName )
/*N*/ {
/*N*/     // concatenate library and name; use dot only if both strings have content
/*N*/     rMacro = rLibraryName;
/*N*/     if ( rLibraryName.Len() > 0 && rMacroName.Len() > 0 )
/*N*/         rMacro += '.';
/*N*/     rMacro += rMacroName;
/*N*/ }

