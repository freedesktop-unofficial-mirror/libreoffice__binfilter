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

#include <tools/stream.hxx>

#include <bf_svtools/macitem.hxx>

namespace binfilter
{

// -----------------------------------------------------------------------

TYPEINIT1_FACTORY(SvxMacroItem, SfxPoolItem, new SvxMacroItem(0));

// -----------------------------------------------------------------------


SjJSbxObjectBase::~SjJSbxObjectBase()
{
}

SjJSbxObjectBase* SjJSbxObjectBase::Clone( void )
{
    return NULL;
}

SvxMacro::SvxMacro( const String &rMacName, const String &rLanguage)
    : aMacName( rMacName ), aLibName( rLanguage),
      pFunctionObject(NULL), eType( EXTENDED_STYPE)
{
    if (rLanguage.EqualsAscii(SVX_MACRO_LANGUAGE_STARBASIC))
        eType=STARBASIC;
    else if (rLanguage.EqualsAscii(SVX_MACRO_LANGUAGE_JAVASCRIPT))
        eType=JAVASCRIPT;
}


SvxMacro::~SvxMacro()
{
    delete pFunctionObject;
}

SvxMacro& SvxMacro::operator=( const SvxMacro& rBase )
{
    if( this != &rBase )
    {
        aMacName = rBase.aMacName;
        aLibName = rBase.aLibName;
        delete pFunctionObject;
        pFunctionObject = rBase.pFunctionObject ? rBase.pFunctionObject->Clone() : NULL;
        eType = rBase.eType;
    }
    return *this;
}


SvxMacroTableDtor& SvxMacroTableDtor::operator=( const SvxMacroTableDtor& rTbl )
{
    DelDtor();
    SvxMacro* pTmp = ((SvxMacroTableDtor&)rTbl).First();
    while( pTmp )
    {
        SvxMacro *pNew = new SvxMacro( *pTmp );
        Insert( rTbl.GetCurKey(), pNew );
        pTmp = ((SvxMacroTableDtor&)rTbl).Next();
    }
    return *this;
}


SvStream& SvxMacroTableDtor::Read( SvStream& rStrm, USHORT nVersion )
{
    if( SVX_MACROTBL_VERSION40 <= nVersion )
        rStrm >> nVersion;
    short nMacro;
    rStrm >> nMacro;

    for( short i = 0; i < nMacro; ++i )
    {
        USHORT nCurKey, eType = STARBASIC;
        String aLibName, aMacName;
        rStrm >> nCurKey;
        SfxPoolItem::readByteString(rStrm, aLibName);
        SfxPoolItem::readByteString(rStrm, aMacName);

        if( SVX_MACROTBL_VERSION40 <= nVersion )
            rStrm >> eType;

        SvxMacro* pNew = new SvxMacro( aMacName, aLibName, (ScriptType)eType );

        SvxMacro *pOld = Get( nCurKey );
        if( pOld )
        {
            delete pOld;
            Replace( nCurKey, pNew );
        }
        else
            Insert( nCurKey, pNew );
    }
    return rStrm;
}

// -----------------------------------------------------------------------

void SvxMacroTableDtor::DelDtor()
{
    SvxMacro* pTmp = First();
    while( pTmp )
    {
        delete pTmp;
        pTmp = Next();
    }
    Clear();
}

// -----------------------------------------------------------------------

int SvxMacroItem::operator==( const SfxPoolItem& rAttr ) const
{
    DBG_ASSERT( SfxPoolItem::operator==(rAttr), "unequal types" );

    const SvxMacroTableDtor& rOwn = aMacroTable;
    const SvxMacroTableDtor& rOther = ( (SvxMacroItem&) rAttr ).aMacroTable;

    // Anzahl unterschiedlich => auf jeden Fall ungleich
    if ( rOwn.Count() != rOther.Count() )
        return FALSE;

    // einzeln verleichen; wegen Performance ist die Reihenfolge wichtig
    for ( USHORT nNo = 0; nNo < rOwn.Count(); ++nNo )
    {
        const SvxMacro *pOwnMac = rOwn.GetObject(nNo);
        const SvxMacro *pOtherMac = rOther.GetObject(nNo);
        if (    rOwn.GetKey(pOwnMac) != rOther.GetKey(pOtherMac)  ||
                pOwnMac->GetLibName() != pOtherMac->GetLibName() ||
                pOwnMac->GetMacName() != pOtherMac->GetMacName() )
            return FALSE;
    }

    return TRUE;
}

// -----------------------------------------------------------------------

SfxPoolItem* SvxMacroItem::Clone( SfxItemPool* ) const
{
    return new SvxMacroItem( *this );
}

//------------------------------------------------------------------------

SfxItemPresentation SvxMacroItem::GetPresentation
(
    SfxItemPresentation /*ePres*/,
    SfxMapUnit          /*eCoreUnit*/,
    SfxMapUnit          /*ePresUnit*/,
    XubString&          rText,
    const ::IntlWrapper *
)   const
{
    rText.Erase();
    return SFX_ITEM_PRESENTATION_NONE;
}

// -----------------------------------------------------------------------

SfxPoolItem* SvxMacroItem::Create( SvStream& rStrm, USHORT nVersion ) const
{
    SvxMacroItem* pAttr = new SvxMacroItem( Which() );
    pAttr->aMacroTable.Read( rStrm, nVersion );
    return pAttr;
}

// -----------------------------------------------------------------------

void SvxMacroItem::SetMacro( USHORT nEvent, const SvxMacro& rMacro )
{
    SvxMacro *pMacro;
    if ( 0 != (pMacro=aMacroTable.Get(nEvent)) )
    {
        delete pMacro;
        aMacroTable.Replace(nEvent, new SvxMacro( rMacro ) );
    }
    else
        aMacroTable.Insert(nEvent, new SvxMacro( rMacro ) );
}

// -----------------------------------------------------------------------

USHORT SvxMacroItem::GetVersion( USHORT nFileFormatVersion ) const
{
    return SOFFICE_FILEFORMAT_31 == nFileFormatVersion
                ? 0 : aMacroTable.GetVersion();
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
