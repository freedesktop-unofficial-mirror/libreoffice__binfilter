/*************************************************************************
 *
 *  $RCSfile: sc_unitconv.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:26:37 $
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

#include "unitconv.hxx"
#include "global.hxx"
#include "viewopti.hxx"         //! move ScLinkConfigItem to separate header!
namespace binfilter {

using namespace utl;
using namespace rtl;
using namespace ::com::sun::star::uno;

// --------------------------------------------------------------------

/*N*/ const sal_Unicode cDelim = 0x01;      // Delimiter zwischen From und To


// --- ScUnitConverterData --------------------------------------------

/*N*/ ScUnitConverterData::ScUnitConverterData( const String& rFromUnit,
/*N*/           const String& rToUnit, double fVal )
/*N*/       :
/*N*/       StrData( rFromUnit ),
/*N*/       fValue( fVal )
/*N*/ {
/*N*/   String aTmp;
/*N*/   ScUnitConverterData::BuildIndexString( aTmp, rFromUnit, rToUnit );
/*N*/   SetString( aTmp );
/*N*/ }


/*N*/ ScUnitConverterData::ScUnitConverterData( const ScUnitConverterData& r )
/*N*/       :
/*N*/       StrData( r ),
/*N*/       fValue( r.fValue )
/*N*/ {
/*N*/ }


/*N*/ DataObject* ScUnitConverterData::Clone() const
/*N*/ {
/*N*/   return new ScUnitConverterData( *this );
/*N*/ }


// static
/*N*/ void ScUnitConverterData::BuildIndexString( String& rStr,
/*N*/           const String& rFromUnit, const String& rToUnit )
/*N*/ {
/*N*/ #if 1
/*N*/ // case sensitive
/*N*/   rStr = rFromUnit;
/*N*/   rStr += cDelim;
/*N*/   rStr += rToUnit;
/*N*/ #else
/*N*/ // not case sensitive
/*N*/   rStr = rFromUnit;
/*N*/   String aTo( rToUnit );
/*N*/   ScGlobal::pCharClass->toUpper( rStr );
/*N*/   ScGlobal::pCharClass->toUpper( aTo );
/*N*/   rStr += cDelim;
/*N*/   rStr += aTo;
/*N*/ #endif
/*N*/ }


// --- ScUnitConverter ------------------------------------------------

/*N*/ #define CFGPATH_UNIT      "Office.Calc/UnitConversion"
/*N*/ #define CFGSTR_UNIT_FROM  "FromUnit"
/*N*/ #define CFGSTR_UNIT_TO        "ToUnit"
/*N*/ #define CFGSTR_UNIT_FACTOR    "Factor"

/*N*/ ScUnitConverter::ScUnitConverter( USHORT nInit, USHORT nDelta ) :
/*N*/       StrCollection( nInit, nDelta, FALSE )
/*N*/ {
/*N*/   //  read from configuration - "convert.ini" is no longer used
/*N*/   //! config item as member to allow change of values
/*N*/
/*N*/   ScLinkConfigItem aConfigItem( OUString::createFromAscii( CFGPATH_UNIT ) );
/*N*/
/*N*/   // empty node name -> use the config item's path itself
/*N*/     OUString aEmptyString;
/*N*/   Sequence<OUString> aNodeNames = aConfigItem.GetNodeNames( aEmptyString );
/*N*/
/*N*/   long nNodeCount = aNodeNames.getLength();
/*N*/   if ( nNodeCount )
/*N*/   {
/*N*/       const OUString* pNodeArray = aNodeNames.getConstArray();
/*N*/       Sequence<OUString> aValNames( nNodeCount * 3 );
/*N*/       OUString* pValNameArray = aValNames.getArray();
/*N*/       const OUString sSlash('/');
/*N*/
/*N*/       long nIndex = 0;
/*N*/       for (long i=0; i<nNodeCount; i++)
/*N*/       {
/*N*/           OUString sPrefix = pNodeArray[i];
/*N*/           sPrefix += sSlash;
/*N*/
/*N*/           pValNameArray[nIndex] = sPrefix;
/*N*/           pValNameArray[nIndex++] += OUString::createFromAscii( CFGSTR_UNIT_FROM );
/*N*/           pValNameArray[nIndex] = sPrefix;
/*N*/           pValNameArray[nIndex++] += OUString::createFromAscii( CFGSTR_UNIT_TO );
/*N*/           pValNameArray[nIndex] = sPrefix;
/*N*/           pValNameArray[nIndex++] += OUString::createFromAscii( CFGSTR_UNIT_FACTOR );
/*N*/       }
/*N*/
/*N*/       Sequence<Any> aProperties = aConfigItem.GetProperties(aValNames);
/*N*/
/*N*/       if (aProperties.getLength() == aValNames.getLength())
/*N*/       {
/*N*/           const Any* pProperties = aProperties.getConstArray();
/*N*/
/*N*/           OUString sFromUnit;
/*N*/           OUString sToUnit;
/*N*/           double fFactor;
/*N*/
/*N*/           nIndex = 0;
/*N*/           for (long i=0; i<nNodeCount; i++)
/*N*/           {
/*N*/               pProperties[nIndex++] >>= sFromUnit;
/*N*/               pProperties[nIndex++] >>= sToUnit;
/*N*/               pProperties[nIndex++] >>= fFactor;
/*N*/
/*N*/               ScUnitConverterData* pNew = new ScUnitConverterData( sFromUnit, sToUnit, fFactor );
/*N*/               if ( !Insert( pNew ) )
/*N*/                   delete pNew;
/*N*/           }
/*N*/       }
/*N*/   }
/*N*/ }

/*N*/ BOOL ScUnitConverter::GetValue( double& fValue, const String& rFromUnit,
/*N*/               const String& rToUnit ) const
/*N*/ {
/*N*/   ScUnitConverterData aSearch( rFromUnit, rToUnit );
/*N*/   USHORT nIndex;
/*N*/   if ( Search( &aSearch, nIndex ) )
/*N*/   {
/*N*/       fValue = ((const ScUnitConverterData*)(At( nIndex )))->GetValue();
/*N*/       return TRUE;
/*N*/   }
/*N*/   fValue = 1.0;
/*N*/   return FALSE;
/*N*/ }


}
