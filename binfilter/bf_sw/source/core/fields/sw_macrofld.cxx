/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_macrofld.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:14:03 $
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


#ifdef _MSC_VER
#pragma hdrstop
#endif


#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOCUFLD_HXX
#include <docufld.hxx>
#endif
#ifndef _UNOFLDMID_H
#include <unofldmid.h>
#endif
namespace binfilter {

extern String& GetString( const ::com::sun::star::uno::Any& rAny, String& rStr ); //STRIP008

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
DBG_BF_ASSERT(0, "STRIP"); return NULL;//STRIP001 //STRIP001    SwMacroFieldType* pType = new SwMacroFieldType(pDoc);
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
        DBG_ERROR("illegal property");
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
