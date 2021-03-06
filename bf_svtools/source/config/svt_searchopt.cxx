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

#include "searchopt.hxx"

#include <bf_svtools/bf_solar.h>
#include <tools/debug.hxx>
#include <unotools/configitem.hxx>
#include <sal/macros.h>

#include <com/sun/star/i18n/TransliterationModules.hpp>
#include <com/sun/star/uno/Sequence.hxx>
#include <com/sun/star/uno/Any.h>
#include <rtl/logfile.hxx>


using namespace utl;
using namespace com::sun::star::uno;
using namespace com::sun::star::i18n;

using ::rtl::OUString;

namespace binfilter
{

#define MAX_FLAGS_OFFSET    24

//////////////////////////////////////////////////////////////////////


class SvtSearchOptions_Impl : public ConfigItem
{
    INT32   nFlags;
    BOOL    bModified;

    // disallow copy-constructor and assignment-operator for now
    SvtSearchOptions_Impl( const SvtSearchOptions_Impl & );
    SvtSearchOptions_Impl & operator = ( const SvtSearchOptions_Impl & );

protected:
    BOOL            IsModified() const { return bModified; }
    using ConfigItem::SetModified;
    void            SetModified( BOOL bVal );
    BOOL            Load();
    BOOL            Save() {return false;}

    Sequence< OUString >    GetPropertyNames() const;

public:
    SvtSearchOptions_Impl();
    virtual ~SvtSearchOptions_Impl();

    // ConfigItem
    virtual void    Commit();
    void Notify( const ::com::sun::star::uno::Sequence< rtl::OUString >& aPropertyNames );

    BOOL            GetFlag( USHORT nOffset ) const;
    void            SetFlag( USHORT nOffset, BOOL bVal );
};



SvtSearchOptions_Impl::SvtSearchOptions_Impl() :
    ConfigItem( OUString( RTL_CONSTASCII_USTRINGPARAM( "Office.Common/SearchOptions" )) )
{
    RTL_LOGFILE_CONTEXT(aLog, "svtools SvtSearchOptions_Impl::SvtSearchOptions_Impl()");
    nFlags = 0x0003FFFF;    // set all options values to 'true'
    Load();
    SetModified( FALSE );
}


SvtSearchOptions_Impl::~SvtSearchOptions_Impl()
{
    Commit();
}


void SvtSearchOptions_Impl::Commit()
{
    if (IsModified())
        Save();
}

    void SvtSearchOptions_Impl::Notify( const ::com::sun::star::uno::Sequence< rtl::OUString >& ) {}

BOOL SvtSearchOptions_Impl::GetFlag( USHORT nOffset ) const
{
    DBG_ASSERT( nOffset <= MAX_FLAGS_OFFSET, "offset out of range");
    return ((nFlags >> nOffset) & 0x01) ? TRUE : FALSE;
}


void SvtSearchOptions_Impl::SetFlag( USHORT nOffset, BOOL bVal )
{
    DBG_ASSERT( nOffset <= MAX_FLAGS_OFFSET, "offset out of range");
    INT32 nOldFlags = nFlags;
    INT32 nMask = ((INT32) 1)  << nOffset;
    if (bVal)
        nFlags |= nMask;
    else
        nFlags &= ~nMask;
    if (nFlags != nOldFlags)
        SetModified( TRUE );
}


void SvtSearchOptions_Impl::SetModified( BOOL bVal )
{
    bModified = bVal;
    if (bModified)
    {
        ConfigItem::SetModified();
    }
}


Sequence< OUString > SvtSearchOptions_Impl::GetPropertyNames() const
{
    static const char* aPropNames[ MAX_FLAGS_OFFSET + 1 ] =
    {
        "IsWholeWordsOnly",                     //  0
        "IsBackwards",                          //  1
        "IsUseRegularExpression",               //  2
        //"IsCurrentSelectionOnly",             // interactively set or not...
        "IsSearchForStyles",                    //  3
        "IsSimilaritySearch",                   //  4
        "IsUseAsianOptions",                    //  5
        "IsMatchCase",                          //  6
        "Japanese/IsMatchFullHalfWidthForms",   //  7
        "Japanese/IsMatchHiraganaKatakana",     //  8
        "Japanese/IsMatchContractions",         //  9
        "Japanese/IsMatchMinusDashCho-on",      // 10
        "Japanese/IsMatchRepeatCharMarks",      // 11
        "Japanese/IsMatchVariantFormKanji",     // 12
        "Japanese/IsMatchOldKanaForms",         // 13
        "Japanese/IsMatch_DiZi_DuZu",           // 14
        "Japanese/IsMatch_BaVa_HaFa",           // 15
        "Japanese/IsMatch_TsiThiChi_DhiZi",     // 16
        "Japanese/IsMatch_HyuIyu_ByuVyu",       // 17
        "Japanese/IsMatch_SeShe_ZeJe",          // 18
        "Japanese/IsMatch_IaIya",               // 19
        "Japanese/IsMatch_KiKu",                // 20
        "Japanese/IsIgnorePunctuation",         // 21
        "Japanese/IsIgnoreWhitespace",          // 22
        "Japanese/IsIgnoreProlongedSoundMark",  // 23
        "Japanese/IsIgnoreMiddleDot"            // 24
    };

    const int nCount = SAL_N_ELEMENTS( aPropNames );
    Sequence< OUString > aNames( nCount );
    OUString* pNames = aNames.getArray();
    for (INT32 i = 0;  i < nCount;  ++i)
        pNames[i] = OUString::createFromAscii( aPropNames[i] );

    return aNames;
}


BOOL SvtSearchOptions_Impl::Load()
{
    BOOL bSucc = FALSE;

    Sequence< OUString > aNames = GetPropertyNames();
    INT32 nProps = aNames.getLength();

    const Sequence< Any > aValues = GetProperties( aNames );
    DBG_ASSERT( aValues.getLength() == aNames.getLength(),
            "GetProperties failed" );
    //EnableNotification( aNames );

    if (nProps  &&  aValues.getLength() == nProps)
    {
        bSucc = TRUE;

        const Any* pValues = aValues.getConstArray();
        for (USHORT i = 0;  i < nProps;  ++i)
        {
            const Any &rVal = pValues[i];
            DBG_ASSERT( rVal.hasValue(), "property value missing" );
            if (rVal.hasValue())
            {
                BOOL bVal = BOOL();
                if (rVal >>= bVal)
                {
                    if (i <= MAX_FLAGS_OFFSET)
                    {
                        // use index in sequence as flag index
                        SetFlag( i, bVal );
                    }
                    else
                    {
                        OSL_FAIL( "unexpected index" );
                    }
                }
                else
                {
                    OSL_FAIL( "unexpected type" );
                    bSucc = FALSE;
                }
            }
            else
            {
                OSL_FAIL( "value missing" );
                bSucc = FALSE;
            }
        }
    }
    DBG_ASSERT( bSucc, "LoadConfig failed" );

    return bSucc;
}


SvtSearchOptions::SvtSearchOptions()
{
    pImpl = new SvtSearchOptions_Impl;
}


SvtSearchOptions::~SvtSearchOptions()
{
    delete pImpl;
}

BOOL SvtSearchOptions::IsWholeWordsOnly() const
{
    return pImpl->GetFlag( 0 );
}


BOOL SvtSearchOptions::IsBackwards() const
{
    return pImpl->GetFlag( 1 );
}

BOOL SvtSearchOptions::IsUseRegularExpression() const
{
    return pImpl->GetFlag( 2 );
}

BOOL SvtSearchOptions::IsSimilaritySearch() const
{
    return pImpl->GetFlag( 4 );
}

BOOL SvtSearchOptions::IsUseAsianOptions() const
{
    return pImpl->GetFlag( 5 );
}

BOOL SvtSearchOptions::IsMatchCase() const
{
    return pImpl->GetFlag( 6 );
}

BOOL SvtSearchOptions::IsMatchFullHalfWidthForms() const
{
    return pImpl->GetFlag( 7 );
}

BOOL SvtSearchOptions::IsMatchHiraganaKatakana() const
{
    return pImpl->GetFlag( 8 );
}

BOOL SvtSearchOptions::IsMatchContractions() const
{
    return pImpl->GetFlag( 9 );
}

BOOL SvtSearchOptions::IsMatchMinusDashChoon() const
{
    return pImpl->GetFlag( 10 );
}


BOOL SvtSearchOptions::IsMatchRepeatCharMarks() const
{
    return pImpl->GetFlag( 11 );
}

BOOL SvtSearchOptions::IsMatchVariantFormKanji() const
{
    return pImpl->GetFlag( 12 );
}

BOOL SvtSearchOptions::IsMatchOldKanaForms() const
{
    return pImpl->GetFlag( 13 );
}


BOOL SvtSearchOptions::IsMatchDiziDuzu() const
{
    return pImpl->GetFlag( 14 );
}

BOOL SvtSearchOptions::IsMatchBavaHafa() const
{
    return pImpl->GetFlag( 15 );
}

BOOL SvtSearchOptions::IsMatchTsithichiDhizi() const
{
    return pImpl->GetFlag( 16 );
}

BOOL SvtSearchOptions::IsMatchHyuiyuByuvyu() const
{
    return pImpl->GetFlag( 17 );
}

BOOL SvtSearchOptions::IsMatchSesheZeje() const
{
    return pImpl->GetFlag( 18 );
}

BOOL SvtSearchOptions::IsMatchIaiya() const
{
    return pImpl->GetFlag( 19 );
}

BOOL SvtSearchOptions::IsMatchKiku() const
{
    return pImpl->GetFlag( 20 );
}

BOOL SvtSearchOptions::IsIgnorePunctuation() const
{
    return pImpl->GetFlag( 21 );
}

BOOL SvtSearchOptions::IsIgnoreWhitespace() const
{
    return pImpl->GetFlag( 22 );
}

BOOL SvtSearchOptions::IsIgnoreProlongedSoundMark() const
{
    return pImpl->GetFlag( 23 );
}

BOOL SvtSearchOptions::IsIgnoreMiddleDot() const
{
    return pImpl->GetFlag( 24 );
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
