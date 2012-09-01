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

//------------------------------------------------------------------

#include <bf_svx/unolingu.hxx>
#include <bf_svtools/lingucfg.hxx>

#include <com/sun/star/linguistic2/XThesaurus.hpp>
#include <com/sun/star/lang/Locale.hpp>

using namespace ::com::sun::star;

#include "scmod.hxx"
namespace binfilter {

//------------------------------------------------------------------

//#define LINGUPROP_DEFLOCALE           "DefaultLocale"
//#define LINGUPROP_CJKLOCALE           "DefaultLocale_CJK"
//#define LINGUPROP_CTLLOCALE           "DefaultLocale_CTL"
#define LINGUPROP_AUTOSPELL         "IsSpellAuto"
#define LINGUPROP_HIDEAUTO          "IsSpellHide"

//------------------------------------------------------------------

// static
/*N*/ void ScModule::GetSpellSettings( USHORT& rDefLang, USHORT& rCjkLang, USHORT& rCtlLang,
/*N*/                                   BOOL& rAutoSpell, BOOL& rHideAuto )
/*N*/ {
/*N*/   //  use SvtLinguConfig instead of service LinguProperties to avoid
/*N*/   //  loading the linguistic component
/*N*/   SvtLinguConfig aConfig;
/*N*/
/*N*/   SvtLinguOptions aOptions;
/*N*/   aConfig.GetOptions( aOptions );
/*N*/
/*N*/   rDefLang = aOptions.nDefaultLanguage;
/*N*/   rCjkLang = aOptions.nDefaultLanguage_CJK;
/*N*/   rCtlLang = aOptions.nDefaultLanguage_CTL;
/*N*/   rAutoSpell = aOptions.bIsSpellAuto;
/*N*/   rHideAuto = FALSE;
/*N*/ }

// static

// static


// static


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
