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

#include <algorithm>
#include <bf_svtools/poolitem.hxx>
#include <unofldmid.h>
#include <flddropdown.hxx>
namespace binfilter {
extern String& GetString( const ::com::sun::star::uno::Any& rAny, String& rStr );
static String aEmptyString;

SwDropDownFieldType::SwDropDownFieldType()
    : SwFieldType(RES_DROPDOWN)
{
}

SwDropDownFieldType::~SwDropDownFieldType()
{
}

SwFieldType * SwDropDownFieldType::Copy() const
{
    return new SwDropDownFieldType;
}

SwDropDownField::SwDropDownField(SwFieldType * pTyp)
    : SwField(pTyp, 0, LANGUAGE_SYSTEM)
{
}

SwDropDownField::SwDropDownField(const SwDropDownField & rSrc)
    : SwField(rSrc.GetTyp(), rSrc.GetFormat(), rSrc.GetLanguage()),
      aValues(rSrc.aValues), aSelectedItem(rSrc.aSelectedItem),
      aName(rSrc.aName)
{
}

SwDropDownField::~SwDropDownField()
{
}

String SwDropDownField::Expand() const
{
    String sSelect = GetSelectedItem();
    if(!sSelect.Len())
    {
        vector<String>::const_iterator aIt = aValues.begin();
        if ( aIt != aValues.end())
            sSelect = *aIt;
    }
    //if still no list value is available a default text of 10 spaces is to be set
    if(!sSelect.Len())
        sSelect.AppendAscii ( RTL_CONSTASCII_STRINGPARAM ("          "));
    return sSelect;
}

SwField * SwDropDownField::Copy() const
{
    return new SwDropDownField(*this);
}

const String & SwDropDownField::GetPar1() const
{
    return GetSelectedItem();
}

String SwDropDownField::GetPar2() const
{
    return GetName();
}

void SwDropDownField::SetPar1(const String & rStr)
{
    SetSelectedItem(rStr);
}

void SwDropDownField::SetPar2(const String & rName)
{
    SetName(rName);
}

void SwDropDownField::SetItems(const Sequence<OUString> & rItems)
{
    aValues.clear();

    sal_Int32 aCount = rItems.getLength();
    for (int i = 0; i < aCount; i++)
        aValues.push_back(rItems[i]);

    aSelectedItem = aEmptyString;
}

Sequence<OUString> SwDropDownField::GetItemSequence() const
{
    Sequence<OUString> aSeq( aValues.size() );
    OUString* pSeq = aSeq.getArray();
    int i = 0;
    vector<String>::const_iterator aIt;

    for (aIt = aValues.begin(); aIt != aValues.end(); ++aIt)
    {
        pSeq[i] = ::rtl::OUString(*aIt);

        i++;
    }

    return aSeq;
}

const String & SwDropDownField::GetSelectedItem() const
{
    return aSelectedItem;
}

const String & SwDropDownField::GetName() const
{
    return aName;
}

BOOL SwDropDownField::SetSelectedItem(const String & rItem)
{
    vector<String>::const_iterator aIt =
        find(aValues.begin(), aValues.end(), rItem);

    if (aIt != aValues.end())
        aSelectedItem = *aIt;
    else
        aSelectedItem = String();

    return (aIt != aValues.end());
}

void SwDropDownField::SetName(const String & rName)
{
    aName = rName;
}

BOOL SwDropDownField::QueryValue(Any &rVal, BYTE nMId)
    const
{
    nMId &= ~CONVERT_TWIPS;
    switch( nMId )
    {
    case FIELD_PROP_PAR1:
        rVal <<= ::rtl::OUString(GetSelectedItem());
        break;
    case FIELD_PROP_PAR2:
        rVal <<= ::rtl::OUString(GetName());
        break;
    case FIELD_PROP_STRINGS:
        rVal <<= GetItemSequence();

        break;

    default:
        OSL_FAIL("illegal property");
    }
    return sal_True;
}

BOOL SwDropDownField::PutValue(const Any &rVal,
                               BYTE nMId)
{
    nMId &= ~CONVERT_TWIPS;
    switch( nMId )
    {
    case FIELD_PROP_PAR1:
        {
            String aTmpStr;
            ::binfilter::GetString( rVal, aTmpStr );

            SetSelectedItem(aTmpStr);
        }
        break;

    case FIELD_PROP_PAR2:
        {
            String aTmpStr;
            ::binfilter::GetString( rVal, aTmpStr );

            SetName(aTmpStr);
        }
        break;

    case FIELD_PROP_STRINGS:
        {
            Sequence<OUString> aSeq;
            rVal >>= aSeq;
            SetItems(aSeq);
        }
        break;

    default:
        OSL_FAIL("illegal property");
    }
    return sal_True;
}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
