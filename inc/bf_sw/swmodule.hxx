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
#ifndef _SWMODULE_HXX
#define _SWMODULE_HXX


#include <tools/link.hxx>
#include <bf_sfx2/module.hxx>

#include <bf_svtools/lstner.hxx>
#include <swdll.hxx>
#include "shellid.hxx"
#include <bf_tools/string.hxx>
#include <com/sun/star/linguistic2/XLinguServiceEventListener.hpp>
#include <tools/fldunit.hxx>
namespace com{ namespace sun{ namespace star{ namespace scanner{
    class XScannerManager;
}}}}

class Color;

namespace binfilter {
class SvStringsDtor;
class SvtAccessibilityOptions;
class SvtCTLOptions;
class SfxItemSet;
class SfxErrorHandler;
class ColorConfig;
class AuthorCharAttr;

class SfxRequest;

class SwDBConfig;
class SwModuleOptions;
class SwMasterUsrPref;
class SwViewOption;
class SwView;
class SwPrintOptions;
class SwAutoFmtOpt;
class SwChapterNumRules;
class SwStdFontConfig;
class SwAttrPool;

struct SwDBData;
#define VIEWOPT_DEST_VIEW       0
#define VIEWOPT_DEST_TEXT       1
#define VIEWOPT_DEST_WEB        2
#define VIEWOPT_DEST_VIEW_ONLY  3 //ViewOptions werden nur an der ::com::sun::star::sdbcx::View, nicht an der Appl. gesetzt

class SwModule: public SwModuleDummy , public SfxListener
{
    String              sActAuthor;

    // ConfigItems
    SwModuleOptions*    pModuleConfig;
    SwMasterUsrPref*    pUsrPref;
    SwMasterUsrPref*    pWebUsrPref;
    SwPrintOptions*     pPrtOpt;
    SwPrintOptions*     pWebPrtOpt;
    SwStdFontConfig*    pStdFontConfig;
    SwDBConfig*         pDBConfig;
    ColorConfig*        pColorConfig;
    SvtCTLOptions*      pCTLOptions;

    SfxErrorHandler*    pErrorHdl;

    SwAttrPool          *pAttrPool;

    // Die aktuelle View wird hier gehalten um nicht ueber
    // GetActiveView arbeiten zu muessen
    // Die View ist solange gueltig bis Sie im Activate
    // zerstoert oder ausgetauscht wird
    SwView*             pView;

    // Liste aller Redline-Autoren
    SvStringsDtor*      pAuthorNames;

    // DictionaryList listener to trigger spellchecking or hyphenation
    ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XLinguServiceEventListener > xLngSvcEvtListener;
    ::com::sun::star::uno::Reference<
        ::com::sun::star::scanner::XScannerManager >    m_xScannerManager;

    sal_Bool                bAuthorInitialised : 1;
    sal_Bool                bEmbeddedLoadSave : 1;

    // Hint abfangen fuer DocInfo
    virtual void        Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

public:
    TYPEINFO();

    // dieser Ctor nur fuer SW-Dll
    SwModule( SvFactory* pFact,
                SvFactory* pWebFact,
                    SvFactory* pGlobalFact );
    // dieser Ctor nur fuer Web-Dll
    SwModule( SvFactory* pWebFact );

    ~SwModule();

    virtual SfxModule* Load();

    // View setzen nur fuer internen Gebrauch,
    // aus techn. Gruenden public
    //
    inline  void        SetView(SwView* pVw) { pView = pVw; }
    inline  SwView*     GetView() { return pView; }

    // Benutzereinstellungen modifizieren
    const SwMasterUsrPref *GetUsrPref(sal_Bool bWeb) const;
    const SwViewOption* GetViewOption(sal_Bool bWeb);

    // ConfigItems erzeugen
    SwModuleOptions*    GetModuleConfig()       { return pModuleConfig;}
    SwPrintOptions*     GetPrtOptions(sal_Bool bWeb);
    SwStdFontConfig*    GetStdFontConfig()      { return pStdFontConfig; }
    SwDBConfig*         GetDBConfig();
    ColorConfig&        GetColorConfig();
    SvtCTLOptions&      GetCTLOptions();

    sal_Bool IsEmbeddedLoadSave() const         { return bEmbeddedLoadSave; }
    void SetEmbeddedLoadSave( sal_Bool bFlag )  { bEmbeddedLoadSave = bFlag; }

    // Redlining
    const String&      GetRedlineAuthor(sal_uInt16 nPos);
    sal_uInt16          InsertRedlineAuthor(const String& rAuthor); //SW50.SDW

    // returne den definierten DocStat - WordDelimiter
    const String&       GetDocStatWordDelim() const;

    // Durchreichen der Metric von der ModuleConfig (fuer HTML-Export)
    sal_uInt16 GetMetric( sal_Bool bWeb ) const;

    // Update-Stati durchreichen
    sal_uInt16 GetLinkUpdMode( sal_Bool bWeb ) const;
    sal_uInt16 GetFldUpdateFlags( sal_Bool bWeb ) const;

    //hier wird der Pool angelegt und an der SfxShell gesetzt
    void    InitAttrPool();
    //Pool loeschen bevor es zu spaet ist
    void    RemoveAttrPool();

    inline ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XLinguServiceEventListener >
            GetLngSvcEvtListener();
    inline void SetLngSvcEvtListener( ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XLinguServiceEventListener > & xLstnr);
    void    CreateLngSvcEvtListener();

    ::com::sun::star::uno::Reference<
        ::com::sun::star::scanner::XScannerManager >
            GetScannerManager() const {return m_xScannerManager;}
};


inline ::com::sun::star::uno::Reference<
    ::com::sun::star::linguistic2::XLinguServiceEventListener >
        SwModule::GetLngSvcEvtListener()
{
    return xLngSvcEvtListener;
}

inline void SwModule::SetLngSvcEvtListener(
    ::com::sun::star::uno::Reference<
        ::com::sun::star::linguistic2::XLinguServiceEventListener > & xLstnr)
{
    xLngSvcEvtListener = xLstnr;
}


#define SW_MOD() ( *(SwModule**) GetAppData(BF_SHL_WRITER))
SwView*     GetActiveView();



} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
