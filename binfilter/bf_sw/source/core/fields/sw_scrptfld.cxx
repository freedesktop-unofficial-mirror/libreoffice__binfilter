/*************************************************************************
 *
 *  $RCSfile: sw_scrptfld.cxx,v $
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

#ifndef _DOCUFLD_HXX
#include <docufld.hxx>
#endif
#ifndef _UNOFLDMID_H
#include <unofldmid.h>
#endif

using namespace ::com::sun::star;
using namespace ::rtl;
/*--------------------------------------------------------------------
    Beschreibung: ScriptField
 --------------------------------------------------------------------*/

/*N*/ SwScriptFieldType::SwScriptFieldType( SwDoc* pD )
/*N*/   : SwFieldType( RES_SCRIPTFLD ), pDoc( pD )
/*N*/ {}

/*N*/ SwFieldType* SwScriptFieldType::Copy() const
/*N*/ {
DBG_ASSERT(0, "STRIP"); return NULL;//STRIP001 //STRIP001   return new SwScriptFieldType( pDoc );
/*N*/ }


/*--------------------------------------------------------------------
    Beschreibung: SwScriptField
 --------------------------------------------------------------------*/

/*N*/ SwScriptField::SwScriptField( SwScriptFieldType* pType,
/*N*/                               const String& rType, const String& rCode,
/*N*/                               BOOL bURL )
/*N*/   : SwField( pType ), sType( rType ), sCode( rCode ), bCodeURL( bURL )
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
/*N*/ }

/*N*/ String SwScriptField::Expand() const
/*N*/ {DBG_ASSERT(0, "STRIP"); //STRIP001
/*N*/   return aEmptyStr;
/*N*/ }

//STRIP001 SwField* SwScriptField::Copy() const
//STRIP001 {
//STRIP001  return new SwScriptField( (SwScriptFieldType*)GetTyp(), sType, sCode, bCodeURL );
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Type setzen
 --------------------------------------------------------------------*/

//STRIP001 void SwScriptField::SetPar1( const String& rStr )
//STRIP001 {
//STRIP001  sType = rStr;
//STRIP001 }

//STRIP001 const String& SwScriptField::GetPar1() const
//STRIP001 {
//STRIP001  return sType;
//STRIP001 }

/*--------------------------------------------------------------------
    Beschreibung: Code setzen
 --------------------------------------------------------------------*/

//STRIP001 void SwScriptField::SetPar2( const String& rStr )
//STRIP001 {
//STRIP001  sCode = rStr;
//STRIP001 }


//STRIP001 String SwScriptField::GetPar2() const
//STRIP001 {
//STRIP001  return sCode;
//STRIP001 }
/*-----------------05.03.98 15:00-------------------

--------------------------------------------------*/
//STRIP001 BOOL SwScriptField::QueryValue( uno::Any& rAny, BYTE nMId ) const
//STRIP001 {
//STRIP001     nMId &= ~CONVERT_TWIPS;
//STRIP001  switch( nMId )
//STRIP001  {
//STRIP001  case FIELD_PROP_PAR1:
//STRIP001      rAny <<= OUString( sType );
//STRIP001      break;
//STRIP001  case FIELD_PROP_PAR2:
//STRIP001      rAny <<= OUString( sCode );
//STRIP001      break;
//STRIP001  case FIELD_PROP_BOOL1:
//STRIP001      rAny.setValue(&bCodeURL, ::getBooleanCppuType());
//STRIP001      break;
//STRIP001  default:
//STRIP001      DBG_ERROR("illegal property");
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }
/*-----------------05.03.98 15:00-------------------

--------------------------------------------------*/
//STRIP001 BOOL SwScriptField::PutValue( const uno::Any& rAny, BYTE nMId )
//STRIP001 {
//STRIP001     nMId &= ~CONVERT_TWIPS;
//STRIP001  switch( nMId )
//STRIP001  {
//STRIP001  case FIELD_PROP_PAR1:
//STRIP001      ::GetString( rAny, sType );
//STRIP001      break;
//STRIP001  case FIELD_PROP_PAR2:
//STRIP001      ::GetString( rAny, sCode );
//STRIP001      break;
//STRIP001  case FIELD_PROP_BOOL1:
//STRIP001      bCodeURL = *(sal_Bool*)rAny.getValue();
//STRIP001      break;
//STRIP001  default:
//STRIP001      DBG_ERROR("illegal property");
//STRIP001  }
//STRIP001  return TRUE;
//STRIP001 }

