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
#ifndef INCLUDED_SVTOOLS_PATHOPTIONS_HXX
#define INCLUDED_SVTOOLS_PATHOPTIONS_HXX

#include <bf_tools/string.hxx>
#include <com/sun/star/lang/Locale.hpp>
#include <bf_svtools/options.hxx>

#define SVT_SEARCHPATH_DELIMITER      ';'

namespace binfilter
{

// class SvtPathOptions --------------------------------------------------

class SvtPathOptions_Impl;
class  SvtPathOptions: public Options
{
private:
    SvtPathOptions_Impl*    pImp;

public:
    enum Pathes
    {
        PATH_ADDIN,
        PATH_AUTOCORRECT,
        PATH_AUTOTEXT,
        PATH_BACKUP,
        PATH_BASIC,
        PATH_BITMAP,
        PATH_CONFIG,
        PATH_DICTIONARY,
        PATH_FAVORITES,
        PATH_FILTER,
        PATH_GALLERY,
        PATH_GRAPHIC,
        PATH_HELP,
        PATH_LINGUISTIC,
        PATH_MODULE,
        PATH_PALETTE,
        PATH_PLUGIN,
        PATH_STORAGE,
        PATH_TEMP,
        PATH_TEMPLATE,
        PATH_USERCONFIG,
        PATH_USERDICTIONARY,
        PATH_WORK,
        PATH_UICONFIG,
        PATH_FINGERPRINT,
        PATH_COUNT // should always be the last element
    };

    SvtPathOptions();
    virtual ~SvtPathOptions();

    // get the paths, not const because of using a mutex
    const String&   GetAddinPath() const;
    const String&   GetAutoCorrectPath() const;
    const String&   GetAutoTextPath() const;
    const String&   GetBackupPath() const;
    const String&   GetBasicPath() const;
    const String&   GetBitmapPath() const;
    const String&   GetConfigPath() const;
    const String&   GetDictionaryPath() const;
    const String&   GetFavoritesPath() const;
    const String&   GetFilterPath() const;
    const String&   GetGalleryPath() const;
    const String&   GetGraphicPath() const;
    const String&   GetHelpPath() const;
    const String&   GetLinguisticPath() const;
    const String&   GetModulePath() const;
    const String&   GetPalettePath() const;
    const String&   GetPluginPath() const;
    const String&   GetStoragePath() const;
    const String&   GetTempPath() const;
    const String&   GetTemplatePath() const;
    const String&   GetUserConfigPath() const;
    const String&   GetUserDictionaryPath() const;
    const String&   GetWorkPath() const;
    const String&   GetUIConfigPath() const;
    const String&   GetFingerprintPath() const;

    // set the paths
    void            SetBasicPath( const String& rPath );

    String          SubstituteVariable( const String& rVar );
    String          UseVariable( const String& rVar );
    sal_Bool        SearchFile( rtl::OUString& rIniFile, Pathes ePath = PATH_USERCONFIG );
    sal_Bool        IsReadonly() const;
};

}

#endif // #ifndef INCLUDED_SVTOOLS_PATHOPTIONS_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
