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

#ifndef _SMMOD_HXX
#define _SMMOD_HXX

#include <i18npool/lang.h>
#include <tools/rc.hxx>
#include <tools/resary.hxx>
#include <bf_svtools/lstner.hxx>
#include <bf_svtools/colorcfg.hxx>

#ifndef _SMDLL_HXX
#define _SM_DLL             // fuer SD_MOD()
#include <bf_starmath/smdll.hxx>        // fuer SdModuleDummy
#endif
#include "starmath.hrc"
class VirtualDevice;

namespace binfilter {

class SvxErrorHandler;
class SvtSysLocale;
class SvFactory;


class SmConfig;
class SmModule;

/*************************************************************************
|*
|* This subclass of <SfxModule> (which is a subclass of <SfxShell>) is
|* linked to the DLL. One instance of this class exists while the DLL is
|* loaded.
|*
|* SdModule is like to be compared with the <SfxApplication>-subclass.
|*
|* Remember: Don`t export this class! It uses DLL-internal symbols.
|*
\************************************************************************/

class SmRectCache;

/////////////////////////////////////////////////////////////////

/*N*/ class SmNamesArray : public Resource
/*N*/ {
/*N*/     ResStringArray      aNamesAry;
/*N*/     LanguageType        nLanguage;
/*N*/
/*N*/ public:
/*N*/     SmNamesArray( LanguageType nLang, int nRID ) :
/*N*/         Resource( SmResId(RID_LOCALIZED_NAMES) ),
/*N*/         aNamesAry   (SmResId(nRID)),
/*N*/         nLanguage   (nLang)
/*N*/     {
/*N*/         FreeResource();
/*N*/     }
/*N*/
/*N*/     LanguageType            GetLanguage() const     { return nLanguage; }
/*N*/     const ResStringArray&   GetNamesArray() const   { return aNamesAry; }
/*N*/ };

/////////////////////////////////////////////////////////////////

class SmLocalizedSymbolData : public Resource
{
    ResStringArray      aUiSymbolNamesAry;
    ResStringArray      aExportSymbolNamesAry;
    ResStringArray      aUiSymbolSetNamesAry;
    ResStringArray      aExportSymbolSetNamesAry;
    SmNamesArray       *p50NamesAry;
    SmNamesArray       *p60NamesAry;
    LanguageType        n50NamesLang;
    LanguageType        n60NamesLang;

public:
    SmLocalizedSymbolData();
    ~SmLocalizedSymbolData();

    const ResStringArray& GetUiSymbolNamesArray() const     { return aUiSymbolNamesAry; }
    const ResStringArray& GetExportSymbolNamesArray() const { return aExportSymbolNamesAry; }
    const String          GetUiSymbolName( const String &rExportName ) const;
    const String          GetExportSymbolName( const String &rUiName ) const;

    const ResStringArray& GetUiSymbolSetNamesArray() const     { return aUiSymbolSetNamesAry; }
    const ResStringArray& GetExportSymbolSetNamesArray() const { return aExportSymbolSetNamesAry; }
    const String          GetUiSymbolSetName( const String &rExportName ) const;

    const ResStringArray* Get50NamesArray( LanguageType nLang );
    const ResStringArray* Get60NamesArray( LanguageType nLang );
};

/////////////////////////////////////////////////////////////////

class SmModule : public SmModuleDummy, public SfxListener
{
    ColorConfig        *pColorConfig;
    SmConfig                *pConfig;
    SmLocalizedSymbolData   *pLocSymbolData;
    SmRectCache             *pRectCache;
    SvtSysLocale            *pSysLocale;
    VirtualDevice           *pVirtualDev;

    void _CreateSysLocale() const;
    void _CreateVirtualDev() const;

    void ApplyColorConfigValues( const ColorConfig &rColorCfg );

public:
    TYPEINFO();

    SmModule(SvFactory* pObjFact);
    virtual ~SmModule();


    // SfxListener
    virtual void        Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

    ColorConfig &  GetColorConfig();

    SmConfig *          GetConfig();
    SmRectCache *       GetRectCache()     { return pRectCache; }

    SmLocalizedSymbolData &   GetLocSymbolData() const;

    const SvtSysLocale& GetSysLocale() const
    {
        if( !pSysLocale )
            _CreateSysLocale();
        return *pSysLocale;
    }

    VirtualDevice &     GetDefaultVirtualDev()
    {
        if (!pVirtualDev)
            _CreateVirtualDev();
        return *pVirtualDev;
    }

    //virtuelle Methoden fuer den Optionendialog
};

#define SM_MOD1() ( *(SmModule**) GetAppData(BF_SHL_SM) )

} //namespace binfilter
#endif                                 // _SDMOD_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
