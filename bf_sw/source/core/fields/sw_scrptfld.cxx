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

#include <docufld.hxx>
#include <unofldmid.h>
namespace binfilter {

extern String& GetString( const ::com::sun::star::uno::Any& rAny, String& rStr );

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
        return new SwScriptFieldType( pDoc );
/*N*/ }


/*--------------------------------------------------------------------
    Beschreibung: SwScriptField
 --------------------------------------------------------------------*/

/*N*/ SwScriptField::SwScriptField( SwScriptFieldType* pType2,
/*N*/                               const String& rType, const String& rCode,
/*N*/                               BOOL bURL )
/*N*/   : SwField( pType2 ), sType( rType ), sCode( rCode ), bCodeURL( bURL )
/*N*/ {
/*N*/ }

/*N*/ String SwScriptField::Expand() const
/*N*/ {
/*N*/   return aEmptyStr;
/*N*/ }

SwField* SwScriptField::Copy() const
{
    return new SwScriptField( (SwScriptFieldType*)GetTyp(), sType, sCode, bCodeURL );
}

/*--------------------------------------------------------------------
    Beschreibung: Type setzen
 --------------------------------------------------------------------*/

void SwScriptField::SetPar1( const String& rStr )
{
    sType = rStr;
}

const String& SwScriptField::GetPar1() const
{
    return sType;
}

/*--------------------------------------------------------------------
    Beschreibung: Code setzen
 --------------------------------------------------------------------*/

void SwScriptField::SetPar2( const String& rStr )
{
    sCode = rStr;
}


String SwScriptField::GetPar2() const
{
    return sCode;
}

BOOL SwScriptField::QueryValue( uno::Any& rAny, BYTE nMId ) const
{
    nMId &= ~CONVERT_TWIPS;
    switch( nMId )
    {
    case FIELD_PROP_PAR1:
        rAny <<= OUString( sType );
        break;
    case FIELD_PROP_PAR2:
        rAny <<= OUString( sCode );
        break;
    case FIELD_PROP_BOOL1:
        rAny.setValue(&bCodeURL, ::getBooleanCppuType());
        break;
    default:
        OSL_FAIL("illegal property");
    }
    return TRUE;
}

BOOL SwScriptField::PutValue( const uno::Any& rAny, BYTE nMId )
{
    nMId &= ~CONVERT_TWIPS;
    switch( nMId )
    {
    case FIELD_PROP_PAR1:
        ::binfilter::GetString( rAny, sType );
        break;
    case FIELD_PROP_PAR2:
        ::binfilter::GetString( rAny, sCode );
        break;
    case FIELD_PROP_BOOL1:
        bCodeURL = *(sal_Bool*)rAny.getValue();
        break;
    default:
        OSL_FAIL("illegal property");
    }
    return TRUE;
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
