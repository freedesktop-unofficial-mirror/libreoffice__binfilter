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


#include <horiornt.hxx>

#include <docufld.hxx>
#include <unofldmid.h>
namespace binfilter {

extern String& GetString( const ::com::sun::star::uno::Any& rAny, String& rStr );

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


/*--------------------------------------------------------------------
    Beschreibung: Das Macrofeld selbst
 --------------------------------------------------------------------*/

/*N*/ SwMacroField::SwMacroField(SwMacroFieldType* pType3,
/*N*/                          const String& rLibAndName, const String& rTxt) :
/*N*/   SwField(pType3), aMacro(rLibAndName), aText(rTxt)
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
/*?*/   DBG_ASSERT(0, "Kein Macroname vorhanden");
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
/*?*/   DBG_ASSERT(0, "Kein Macroname vorhanden");
/*?*/   return aEmptyStr;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: LibName und MacroName
 --------------------------------------------------------------------*/

void SwMacroField::SetPar1(const String& rStr)
{
    aMacro = rStr;
}

/*N*/ const String& SwMacroField::GetPar1() const
/*N*/ {
/*N*/   return aMacro;
/*N*/ }

/*--------------------------------------------------------------------
    Beschreibung: Macrotext
 --------------------------------------------------------------------*/

void SwMacroField::SetPar2(const String& rStr)
{
    aText = rStr;
}

/*N*/ String SwMacroField::GetPar2() const
/*N*/ {
/*N*/   return aText;
/*N*/ }


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
/*?*/       OSL_FAIL("illegal property");
/*N*/   }
/*N*/   return TRUE;
/*N*/ }

BOOL SwMacroField::PutValue( const uno::Any& rAny, BYTE nMId )
{
    String sTmp;
    nMId &= ~CONVERT_TWIPS;
    switch( nMId )
    {
    case FIELD_PROP_PAR1:
        CreateMacroString( aMacro, ::binfilter::GetString(rAny, sTmp), GetLibName());
        break;
    case FIELD_PROP_PAR2:
        ::binfilter::GetString( rAny, aText );
        break;
    case FIELD_PROP_PAR3:
        CreateMacroString(aMacro, GetMacroName(), ::binfilter::GetString(rAny, sTmp) );
        break;
    default:
        OSL_FAIL("illegal property");
    }
    return TRUE;
}

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

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
