/*************************************************************************
 *
 *  $RCSfile: sc_printopt.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:39:36 $
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

#include <com/sun/star/uno/Any.hxx>
#include <com/sun/star/uno/Sequence.hxx>

#include "printopt.hxx"
#include "miscuno.hxx"
namespace binfilter {

using namespace utl;
using namespace rtl;
using namespace ::com::sun::star::uno;

// -----------------------------------------------------------------------

//STRIP001 TYPEINIT1(ScTpPrintItem, SfxPoolItem);

// -----------------------------------------------------------------------

/*N*/ ScPrintOptions::ScPrintOptions()
/*N*/ {
/*N*/   SetDefaults();
/*N*/ }

/*N*/ ScPrintOptions::ScPrintOptions( const ScPrintOptions& rCpy ) :
/*N*/   bSkipEmpty( rCpy.bSkipEmpty ),
/*N*/   bAllSheets( rCpy.bAllSheets )
/*N*/ {
/*N*/ }

/*N*/ ScPrintOptions::~ScPrintOptions()
/*N*/ {
/*N*/ }

/*N*/ void ScPrintOptions::SetDefaults()
/*N*/ {
/*N*/   bSkipEmpty = FALSE;
/*N*/   bAllSheets = TRUE;
/*N*/ }

//STRIP001 const ScPrintOptions& ScPrintOptions::operator=( const ScPrintOptions& rCpy )
//STRIP001 {
//STRIP001  bSkipEmpty = rCpy.bSkipEmpty;
//STRIP001  bAllSheets = rCpy.bAllSheets;
//STRIP001  return *this;
//STRIP001 }

//STRIP001 inline int ScPrintOptions::operator==( const ScPrintOptions& rOpt ) const
//STRIP001 {
//STRIP001  return bSkipEmpty == rOpt.bSkipEmpty
//STRIP001      && bAllSheets == rOpt.bAllSheets;
//STRIP001 }

//STRIP001 inline int ScPrintOptions::operator!=( const ScPrintOptions& rOpt ) const
//STRIP001 {
//STRIP001  return !(operator==(rOpt));
//STRIP001 }

// -----------------------------------------------------------------------

//STRIP001 ScTpPrintItem::ScTpPrintItem( USHORT nWhich ) : SfxPoolItem( nWhich )
//STRIP001 {
//STRIP001 }

//STRIP001 ScTpPrintItem::ScTpPrintItem( USHORT nWhich, const ScPrintOptions& rOpt ) :
//STRIP001  SfxPoolItem ( nWhich ),
//STRIP001  theOptions  ( rOpt )
//STRIP001 {
//STRIP001 }

//STRIP001 ScTpPrintItem::ScTpPrintItem( const ScTpPrintItem& rItem ) :
//STRIP001  SfxPoolItem ( rItem ),
//STRIP001  theOptions  ( rItem.theOptions )
//STRIP001 {
//STRIP001 }

//STRIP001 ScTpPrintItem::~ScTpPrintItem()
//STRIP001 {
//STRIP001 }

//STRIP001 String ScTpPrintItem::GetValueText() const
//STRIP001 {
//STRIP001  return String::CreateFromAscii( "ScTpPrintItem" );
//STRIP001 }

//STRIP001 int ScTpPrintItem::operator==( const SfxPoolItem& rItem ) const
//STRIP001 {
//STRIP001  DBG_ASSERT( SfxPoolItem::operator==( rItem ), "unequal Which or Type" );
//STRIP001
//STRIP001  const ScTpPrintItem& rPItem = (const ScTpPrintItem&)rItem;
//STRIP001  return ( theOptions == rPItem.theOptions );
//STRIP001 }

//STRIP001 SfxPoolItem* ScTpPrintItem::Clone( SfxItemPool * ) const
//STRIP001 {
//STRIP001  return new ScTpPrintItem( *this );
//STRIP001 }

// -----------------------------------------------------------------------

#define CFGPATH_PRINT           "Office.Calc/Print"

#define SCPRINTOPT_EMPTYPAGES       0
#define SCPRINTOPT_ALLSHEETS        1
#define SCPRINTOPT_COUNT            2

//STRIP001 Sequence<OUString> ScPrintCfg::GetPropertyNames()
//STRIP001 {
//STRIP001  static const char* aPropNames[] =
//STRIP001  {
//STRIP001      "Page/EmptyPages",          // SCPRINTOPT_EMPTYPAGES
//STRIP001      "Other/AllSheets"           // SCPRINTOPT_ALLSHEETS
//STRIP001  };
//STRIP001  Sequence<OUString> aNames(SCPRINTOPT_COUNT);
//STRIP001  OUString* pNames = aNames.getArray();
//STRIP001  for(int i = 0; i < SCPRINTOPT_COUNT; i++)
//STRIP001      pNames[i] = OUString::createFromAscii(aPropNames[i]);
//STRIP001
//STRIP001  return aNames;
//STRIP001 }

/*N*/ ScPrintCfg::ScPrintCfg() :
/*N*/   ConfigItem( OUString::createFromAscii( CFGPATH_PRINT ) )
/*N*/ {
    DBG_BF_ASSERT(0, "STRIP"); //STRIP001 Sequence<OUString> aNames = GetPropertyNames();
//STRIP001  Sequence<Any> aValues = GetProperties(aNames);
//STRIP001 //   EnableNotification(aNames);
//STRIP001  const Any* pValues = aValues.getConstArray();
//STRIP001  DBG_ASSERT(aValues.getLength() == aNames.getLength(), "GetProperties failed")
//STRIP001  if(aValues.getLength() == aNames.getLength())
//STRIP001  {
//STRIP001      for(int nProp = 0; nProp < aNames.getLength(); nProp++)
//STRIP001      {
//STRIP001          DBG_ASSERT(pValues[nProp].hasValue(), "property value missing")
//STRIP001          if(pValues[nProp].hasValue())
//STRIP001          {
//STRIP001              switch(nProp)
//STRIP001              {
//STRIP001                  case SCPRINTOPT_EMPTYPAGES:
//STRIP001                      // reversed
//STRIP001                      SetSkipEmpty( !ScUnoHelpFunctions::GetBoolFromAny( pValues[nProp] ) );
//STRIP001                      break;
//STRIP001                  case SCPRINTOPT_ALLSHEETS:
//STRIP001                      SetAllSheets( ScUnoHelpFunctions::GetBoolFromAny( pValues[nProp] ) );
//STRIP001                      break;
//STRIP001              }
//STRIP001          }
//STRIP001      }
//STRIP001  }
/*N*/ }


//STRIP001 void ScPrintCfg::Commit()
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
//STRIP001          case SCPRINTOPT_EMPTYPAGES:
//STRIP001              // reversed
//STRIP001              ScUnoHelpFunctions::SetBoolInAny( pValues[nProp], !GetSkipEmpty() );
//STRIP001              break;
//STRIP001          case SCPRINTOPT_ALLSHEETS:
//STRIP001              ScUnoHelpFunctions::SetBoolInAny( pValues[nProp], GetAllSheets() );
//STRIP001              break;
//STRIP001      }
//STRIP001  }
//STRIP001  PutProperties(aNames, aValues);
//STRIP001 }

//STRIP001 void ScPrintCfg::SetOptions( const ScPrintOptions& rNew )
//STRIP001 {
//STRIP001  *(ScPrintOptions*)this = rNew;
//STRIP001  SetModified();
//STRIP001 }

//STRIP001 void ScPrintCfg::OptionsChanged()
//STRIP001 {
//STRIP001  SetModified();
//STRIP001 }


}
