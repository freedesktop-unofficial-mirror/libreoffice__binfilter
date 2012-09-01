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

#ifndef _SVT_SEARCHOPT_HXX_
#define _SVT_SEARCHOPT_HXX_

#include <bf_svtools/bf_solar.h>

namespace binfilter
{

class SvtSearchOptions_Impl;

class  SvtSearchOptions
{
    SvtSearchOptions_Impl   *pImpl;

    // disallow copy-constructor and assignment-operator for now
    SvtSearchOptions( const SvtSearchOptions & );
    SvtSearchOptions & operator = ( const SvtSearchOptions & );

protected:

public:
    SvtSearchOptions();
    ~SvtSearchOptions();

    //
    // General Options
    //

    BOOL    IsWholeWordsOnly() const;
    BOOL    IsBackwards() const;
    BOOL    IsUseRegularExpression() const;
    BOOL    IsSimilaritySearch() const;
    BOOL    IsUseAsianOptions() const;
    BOOL    IsMatchCase() const;            // also Japanese search option

    //
    // Japanese search options
    //

    BOOL    IsMatchFullHalfWidthForms() const;
    BOOL    IsMatchHiraganaKatakana() const;
    BOOL    IsMatchContractions() const;
    BOOL    IsMatchMinusDashChoon() const;
    BOOL    IsMatchRepeatCharMarks() const;
    BOOL    IsMatchVariantFormKanji() const;
    BOOL    IsMatchOldKanaForms() const;
    BOOL    IsMatchDiziDuzu() const;
    BOOL    IsMatchBavaHafa() const;
    BOOL    IsMatchTsithichiDhizi() const;
    BOOL    IsMatchHyuiyuByuvyu() const;
    BOOL    IsMatchSesheZeje() const;
    BOOL    IsMatchIaiya() const;
    BOOL    IsMatchKiku() const;
    BOOL    IsIgnorePunctuation() const;
    BOOL    IsIgnoreWhitespace() const;
    BOOL    IsIgnoreProlongedSoundMark() const;
    BOOL    IsIgnoreMiddleDot() const;
};

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
