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
#ifndef _SFX_DOCFILT_HACK_HXX
#define _SFX_DOCFILT_HACK_HXX

#include <bf_svtools/bf_solar.h>

#include <com/sun/star/plugin/PluginDescription.hpp>

#include <tools/wldcrd.hxx>
namespace binfilter {

#define SFX_FILTER_IMPORT            0x00000001L
#define SFX_FILTER_EXPORT            0x00000002L
#define SFX_FILTER_TEMPLATE          0x00000004L
#define SFX_FILTER_INTERNAL          0x00000008L
#define SFX_FILTER_TEMPLATEPATH      0x00000010L
#define SFX_FILTER_OWN               0x00000020L
#define SFX_FILTER_ALIEN             0x00000040L
#define SFX_FILTER_USESOPTIONS       0x00000080L
#define SFX_FILTER_NOTINFILEDLG      0x00001000L
#define SFX_FILTER_NOTINCHOOSER      0x00002000L

#define SFX_FILTER_DEFAULT           0x00000100L
#define SFX_FILTER_EXECUTABLE        0x00000200L
#define SFX_FILTER_SUPPORTSSELECTION 0x00000400L
#define SFX_FILTER_MAPTOAPPPLUG      0x00000800L
#define SFX_FILTER_ASYNC             0x00004000L
// Legt Objekt nur an, kein Laden
#define SFX_FILTER_CREATOR           0x00008000L
#define SFX_FILTER_OPENREADONLY      0x00010000L
#define SFX_FILTER_MUSTINSTALL       0x00020000L
#define SFX_FILTER_CONSULTSERVICE    0x00040000L

#define SFX_FILTER_STARONEFILTER     0x00080000L
#define SFX_FILTER_PACKED            0x00100000L

#define SFX_FILTER_BROWSERPREFERED   0x00400000L
#define SFX_FILTER_PREFERED          0x10000000L

#define SFX_FILTER_VERSION_NONE      0
#define SFX_FILTER_NOTINSTALLED      SFX_FILTER_MUSTINSTALL | SFX_FILTER_CONSULTSERVICE

#include <bf_sfx2/sfxdefs.hxx>

//========================================================================
class SfxFilterContainer;

class SfxFilter
{
friend class SfxFilterContainer;

    String          aName;
    WildCard        aWildCard;
    ULONG           lFormat;
    String          aMacType;
    String          aTypeName;
    String          aUserData;
    SfxFilterFlags  nFormatType;
    USHORT          nDocIcon;
    const SfxFilterContainer* pContainer;
    String          aMimeType;
    String          aFilterName;
    String          aPattern;
    ULONG           nVersion;
    BOOL            bPlugDataSearched;
    ::com::sun::star::plugin::PluginDescription* pPlugData;
    String          aUIName;
    String          aDefaultTemplate;

public:
                    SfxFilter( const String &rName,
                               const String &rWildCard,
                               SfxFilterFlags nFormatType,
                               ULONG lFormat,       // Clipboardformat
                               const String &rMacType,  // Dateityp (MAC)
                               const String &rTypeName, // Dateityp als String (OS/2)
                               USHORT nDocIcon,         // Dokumenticon OS/2
                               const String &rMimeType,
                               const SfxFilterContainer* pFactoryP,
                               const String &rUserData );// Daten der Anwendung
                    ~SfxFilter();

    const SfxFilterContainer* GetFilterContainer( ) const { return pContainer; }

    bool        IsAllowedAsTemplate() const
                    { return nFormatType & SFX_FILTER_TEMPLATE; }
    bool        IsOwnFormat() const
                    { return nFormatType & SFX_FILTER_OWN; }
    bool        IsOwnTemplateFormat() const
                    { return nFormatType & SFX_FILTER_TEMPLATEPATH; }
    bool        IsAlienFormat() const
                    { return nFormatType & SFX_FILTER_ALIEN; }
    bool        CanImport() const
                    { return nFormatType & SFX_FILTER_IMPORT; }
    bool        CanExport() const
                    { return nFormatType & SFX_FILTER_EXPORT; }
    bool        IsInternal() const
                    { return nFormatType & SFX_FILTER_INTERNAL; }
    SfxFilterFlags  GetFilterFlags() const  { return nFormatType; }
    const String&   GetFilterName() const { return aFilterName; }
    const String&   GetMimeType() const { return aMimeType; }
    const String&   GetName() const { return  aName; }
    String          GetFilterNameWithPrefix() const;
    const WildCard& GetWildcard() const { return aWildCard; }
    const String&   GetMacType() const { return aMacType; }
    const String&   GetRealTypeName() const { return aTypeName; }
    ULONG           GetFormat() const { return lFormat; }
    const String&   GetTypeName() const;
    const String&   GetUIName() const { return aUIName; }
    USHORT          GetDocIconId() const { return nDocIcon; }
    const String&   GetUserData() const { return aUserData; }
    const String&   GetDefaultTemplate() const { return aDefaultTemplate; }
    void            SetDefaultTemplate( const String& rStr )
                        { aDefaultTemplate = rStr; }
    BOOL            UsesStorage() const { return GetFormat() != 0; }
    void            SetURLPattern( const String& rStr )
                    {
                        aPattern = rStr;
                        aPattern.ToLowerAscii();
                    }
    String          GetURLPattern() const { return aPattern; }
    void            SetUIName( const String& rName ) { aUIName = rName; }
    void            SetVersion( ULONG nVersionP ) { nVersion = nVersionP; }
    ULONG           GetVersion() const { return nVersion; }
    const ::com::sun::star::plugin::PluginDescription* GetPlugData() const {
        return ((SfxFilter*)this)->GetPlugData();   }

#if _SOLAR__PRIVATE
    void            InitMembers_Impl();
#endif
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
