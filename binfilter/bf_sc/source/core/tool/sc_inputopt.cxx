/*************************************************************************
 *
 *  $RCSfile: sc_inputopt.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:26:30 $
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

//------------------------------------------------------------------

#include <tools/debug.hxx>

#include <com/sun/star/uno/Any.hxx>
#include <com/sun/star/uno/Sequence.hxx>

#include "cfgids.hxx"
#include "inputopt.hxx"
#include "rechead.hxx"
#include "scresid.hxx"
#include "global.hxx"
#include "bf_sc.hrc"
#include "miscuno.hxx"
namespace binfilter {

using namespace utl;
using namespace rtl;
using namespace ::com::sun::star::uno;

//------------------------------------------------------------------

//  Version, ab der das Item kompatibel ist
#define SC_VERSION ((USHORT)351)


//========================================================================
//      ScInputOptions - Eingabe-Optionen
//========================================================================

/*N*/ ScInputOptions::ScInputOptions()
/*N*/ {
/*N*/   SetDefaults();
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScInputOptions::ScInputOptions( const ScInputOptions& rCpy )
/*N*/ {
/*N*/   *this = rCpy;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ ScInputOptions::~ScInputOptions()
/*N*/ {
/*N*/ }

//------------------------------------------------------------------------

/*N*/ void ScInputOptions::SetDefaults()
/*N*/ {
/*N*/   nMoveDir        = DIR_BOTTOM;
/*N*/   bMoveSelection  = TRUE;
/*N*/   bEnterEdit      = FALSE;
/*N*/   bExtendFormat   = FALSE;
/*N*/   bRangeFinder    = TRUE;
/*N*/   bExpandRefs     = FALSE;
/*N*/   bMarkHeader     = TRUE;
/*N*/   bUseTabCol      = FALSE;
/*N*/   bTextWysiwyg    = FALSE;
/*N*/     bReplCellsWarn  = TRUE;
/*N*/ }

//------------------------------------------------------------------------

/*N*/ const ScInputOptions& ScInputOptions::operator=( const ScInputOptions& rCpy )
/*N*/ {
/*N*/   nMoveDir        = rCpy.nMoveDir;
/*N*/   bMoveSelection  = rCpy.bMoveSelection;
/*N*/   bEnterEdit      = rCpy.bEnterEdit;
/*N*/   bExtendFormat   = rCpy.bExtendFormat;
/*N*/   bRangeFinder    = rCpy.bRangeFinder;
/*N*/   bExpandRefs     = rCpy.bExpandRefs;
/*N*/   bMarkHeader     = rCpy.bMarkHeader;
/*N*/   bUseTabCol      = rCpy.bUseTabCol;
/*N*/   bTextWysiwyg    = rCpy.bTextWysiwyg;
/*N*/     bReplCellsWarn  = rCpy.bReplCellsWarn;
/*N*/
/*N*/   return *this;
/*N*/ }

//------------------------------------------------------------------------

//STRIP001 SvStream& operator>>( SvStream& rStream, ScInputOptions& rOpt )
//STRIP001 {
//STRIP001  rOpt.SetDefaults();
//STRIP001
//STRIP001  ScReadHeader aHdr( rStream );
//STRIP001
//STRIP001  rStream >> rOpt.nMoveDir;
//STRIP001  rStream >> rOpt.bMoveSelection;
//STRIP001  rStream >> rOpt.bEnterEdit;
//STRIP001  rStream >> rOpt.bExtendFormat;
//STRIP001
//STRIP001  if (aHdr.BytesLeft())
//STRIP001      rStream >> rOpt.bRangeFinder;           // ab 363
//STRIP001
//STRIP001  if (aHdr.BytesLeft())
//STRIP001      rStream >> rOpt.bExpandRefs;            // ab 364v
//STRIP001
//STRIP001  if (aHdr.BytesLeft())
//STRIP001      rStream >> rOpt.bMarkHeader;            // ab 364irgendwas
//STRIP001
//STRIP001  if (aHdr.BytesLeft())
//STRIP001      rStream >> rOpt.bUseTabCol;             // ab 373d
//STRIP001
//STRIP001  // newer additions are not in old file format
//STRIP001
//STRIP001  return rStream;
//STRIP001 }

//------------------------------------------------------------------------

//STRIP001 SvStream& operator<<( SvStream& rStream, const ScInputOptions& rOpt )
//STRIP001 {
//STRIP001  ScWriteHeader aHdr( rStream, 6 );
//STRIP001
//STRIP001  rStream << rOpt.nMoveDir;
//STRIP001  rStream << rOpt.bMoveSelection;
//STRIP001  rStream << rOpt.bEnterEdit;
//STRIP001  rStream << rOpt.bExtendFormat;
//STRIP001  rStream << rOpt.bRangeFinder;
//STRIP001  rStream << rOpt.bExpandRefs;
//STRIP001  rStream << rOpt.bMarkHeader;
//STRIP001  rStream << rOpt.bUseTabCol;
//STRIP001
//STRIP001  // newer additions are not in old file format
//STRIP001
//STRIP001  return rStream;
//STRIP001 }

//==================================================================
//  Config Item containing input options
//==================================================================

#define CFGPATH_INPUT           "Office.Calc/Input"

#define SCINPUTOPT_MOVEDIR          0
#define SCINPUTOPT_MOVESEL          1
#define SCINPUTOPT_EDTEREDIT        2
#define SCINPUTOPT_EXTENDFMT        3
#define SCINPUTOPT_RANGEFIND        4
#define SCINPUTOPT_EXPANDREFS       5
#define SCINPUTOPT_MARKHEADER       6
#define SCINPUTOPT_USETABCOL        7
#define SCINPUTOPT_TEXTWYSIWYG      8
#define SCINPUTOPT_REPLCELLSWARN    9
#define SCINPUTOPT_COUNT            10

/*N*/ Sequence<OUString> ScInputCfg::GetPropertyNames()
/*N*/ {
/*N*/   static const char* aPropNames[] =
/*N*/   {
/*N*/       "MoveSelectionDirection",   // SCINPUTOPT_MOVEDIR
/*N*/       "MoveSelection",            // SCINPUTOPT_MOVESEL
/*N*/       "SwitchToEditMode",         // SCINPUTOPT_EDTEREDIT
/*N*/       "ExpandFormatting",         // SCINPUTOPT_EXTENDFMT
/*N*/       "ShowReference",            // SCINPUTOPT_RANGEFIND
/*N*/       "ExpandReference",          // SCINPUTOPT_EXPANDREFS
/*N*/       "HighlightSelection",       // SCINPUTOPT_MARKHEADER
/*N*/       "UseTabCol",                // SCINPUTOPT_USETABCOL
/*N*/         "UsePrinterMetrics",        // SCINPUTOPT_TEXTWYSIWYG
/*N*/         "ReplaceCellsWarning"       // SCINPUTOPT_REPLCELLSWARN
/*N*/   };
/*N*/   Sequence<OUString> aNames(SCINPUTOPT_COUNT);
/*N*/   OUString* pNames = aNames.getArray();
/*N*/   for(int i = 0; i < SCINPUTOPT_COUNT; i++)
/*N*/       pNames[i] = OUString::createFromAscii(aPropNames[i]);
/*N*/
/*N*/   return aNames;
/*N*/ }

/*N*/ ScInputCfg::ScInputCfg() :
/*N*/   ConfigItem( OUString::createFromAscii( CFGPATH_INPUT ) )
/*N*/ {
/*N*/   sal_Int32 nIntVal;
/*N*/
/*N*/   Sequence<OUString> aNames = GetPropertyNames();
/*N*/   Sequence<Any> aValues = GetProperties(aNames);
/*N*/   EnableNotification(aNames);
/*N*/   const Any* pValues = aValues.getConstArray();
/*N*/   DBG_ASSERT(aValues.getLength() == aNames.getLength(), "GetProperties failed")
/*N*/   if(aValues.getLength() == aNames.getLength())
/*N*/   {
/*N*/       for(int nProp = 0; nProp < aNames.getLength(); nProp++)
/*N*/       {
/*N*/           DBG_ASSERT(pValues[nProp].hasValue(), "property value missing")
/*N*/           if(pValues[nProp].hasValue())
/*N*/           {
/*N*/               switch(nProp)
/*N*/               {
/*N*/                   case SCINPUTOPT_MOVEDIR:
/*N*/                       if ( pValues[nProp] >>= nIntVal )
/*N*/                           SetMoveDir( (USHORT)nIntVal );
/*N*/                       break;
/*N*/                   case SCINPUTOPT_MOVESEL:
/*N*/                       SetMoveSelection( ScUnoHelpFunctions::GetBoolFromAny( pValues[nProp] ) );
/*N*/                       break;
/*N*/                   case SCINPUTOPT_EDTEREDIT:
/*N*/                       SetEnterEdit( ScUnoHelpFunctions::GetBoolFromAny( pValues[nProp] ) );
/*N*/                       break;
/*N*/                   case SCINPUTOPT_EXTENDFMT:
/*N*/                       SetExtendFormat( ScUnoHelpFunctions::GetBoolFromAny( pValues[nProp] ) );
/*N*/                       break;
/*N*/                   case SCINPUTOPT_RANGEFIND:
/*N*/                       SetRangeFinder( ScUnoHelpFunctions::GetBoolFromAny( pValues[nProp] ) );
/*N*/                       break;
/*N*/                   case SCINPUTOPT_EXPANDREFS:
/*N*/                       SetExpandRefs( ScUnoHelpFunctions::GetBoolFromAny( pValues[nProp] ) );
/*N*/                       break;
/*N*/                   case SCINPUTOPT_MARKHEADER:
/*N*/                       SetMarkHeader( ScUnoHelpFunctions::GetBoolFromAny( pValues[nProp] ) );
/*N*/                       break;
/*N*/                   case SCINPUTOPT_USETABCOL:
/*N*/                       SetUseTabCol( ScUnoHelpFunctions::GetBoolFromAny( pValues[nProp] ) );
/*N*/                       break;
/*N*/                   case SCINPUTOPT_TEXTWYSIWYG:
/*N*/                       SetTextWysiwyg( ScUnoHelpFunctions::GetBoolFromAny( pValues[nProp] ) );
/*N*/                       break;
/*N*/                     case SCINPUTOPT_REPLCELLSWARN:
/*N*/                         SetReplaceCellsWarn( ScUnoHelpFunctions::GetBoolFromAny( pValues[nProp] ) );
/*N*/                         break;
/*N*/               }
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }


//STRIP001 void ScInputCfg::Commit()
//STRIP001 {
//STRIP001  Sequence<OUString> aNames = GetPropertyNames();
//STRIP001  OUString* pNames = aNames.getArray();
//STRIP001  Sequence<Any> aValues(aNames.getLength());
//STRIP001  Any* pValues = aValues.getArray();
//STRIP001
//STRIP001  const Type& rType = ::getBooleanCppuType();
//STRIP001  for(int nProp = 0; nProp < aNames.getLength(); nProp++)
//STRIP001  {
//STRIP001      switch(nProp)
//STRIP001      {
//STRIP001          case SCINPUTOPT_MOVEDIR:
//STRIP001              pValues[nProp] <<= (sal_Int32) GetMoveDir();
//STRIP001              break;
//STRIP001          case SCINPUTOPT_MOVESEL:
//STRIP001              ScUnoHelpFunctions::SetBoolInAny( pValues[nProp], GetMoveSelection() );
//STRIP001              break;
//STRIP001          case SCINPUTOPT_EDTEREDIT:
//STRIP001              ScUnoHelpFunctions::SetBoolInAny( pValues[nProp], GetEnterEdit() );
//STRIP001              break;
//STRIP001          case SCINPUTOPT_EXTENDFMT:
//STRIP001              ScUnoHelpFunctions::SetBoolInAny( pValues[nProp], GetExtendFormat() );
//STRIP001              break;
//STRIP001          case SCINPUTOPT_RANGEFIND:
//STRIP001              ScUnoHelpFunctions::SetBoolInAny( pValues[nProp], GetRangeFinder() );
//STRIP001              break;
//STRIP001          case SCINPUTOPT_EXPANDREFS:
//STRIP001              ScUnoHelpFunctions::SetBoolInAny( pValues[nProp], GetExpandRefs() );
//STRIP001              break;
//STRIP001          case SCINPUTOPT_MARKHEADER:
//STRIP001              ScUnoHelpFunctions::SetBoolInAny( pValues[nProp], GetMarkHeader() );
//STRIP001              break;
//STRIP001          case SCINPUTOPT_USETABCOL:
//STRIP001              ScUnoHelpFunctions::SetBoolInAny( pValues[nProp], GetUseTabCol() );
//STRIP001              break;
//STRIP001          case SCINPUTOPT_TEXTWYSIWYG:
//STRIP001              ScUnoHelpFunctions::SetBoolInAny( pValues[nProp], GetTextWysiwyg() );
//STRIP001              break;
//STRIP001             case SCINPUTOPT_REPLCELLSWARN:
//STRIP001                 ScUnoHelpFunctions::SetBoolInAny( pValues[nProp], GetReplaceCellsWarn() );
//STRIP001                 break;
//STRIP001      }
//STRIP001  }
//STRIP001  PutProperties(aNames, aValues);
//STRIP001 }

//STRIP001 void ScInputCfg::Notify( const Sequence<rtl::OUString>& aPropertyNames )
//STRIP001 {
//STRIP001  DBG_ERROR("properties have been changed")
//STRIP001 }

//STRIP001 void ScInputCfg::SetOptions( const ScInputOptions& rNew )
//STRIP001 {
//STRIP001  *(ScInputOptions*)this = rNew;
//STRIP001  SetModified();
//STRIP001 }

//STRIP001 void ScInputCfg::OptionsChanged()
//STRIP001 {
//STRIP001  SetModified();
//STRIP001 }


}
