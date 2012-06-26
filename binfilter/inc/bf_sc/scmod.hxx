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

#ifndef SC_SCMOD_HXX
#define SC_SCMOD_HXX

#include <bf_svtools/bf_solar.h>

#include "scdll.hxx"

#include <vcl/timer.hxx>

#include <bf_svtools/lstner.hxx>

#include "global.hxx"       // ScInputMode

#include "markdata.hxx"     //ScMarkData

#include "shellids.hxx"
class KeyEvent;
class SfxErrorHandler;
namespace binfilter {
class SvtCTLOptions;
class ColorConfig;
class SdrModel;
class SdrView;
class EditView;
class SvxErrorHandler;

class ScRange;
class ScDocument;
class ScViewCfg;
class ScDocCfg;
class ScAppCfg;
class ScInputCfg;
class ScPrintCfg;
class ScViewOptions;
class ScDocOptions;
class ScAppOptions;
class ScInputOptions;
class ScPrintOptions;
class ScInputHandler;
class ScInputWindow;
class ScTabViewShell;
class ScFunctionDlg;
class ScArgDlgBase;
class ScTeamDlg;
class ScEditFunctionDlg;
class ScMessagePool;
class EditFieldInfo;
class ScNavipiCfg;
class ScFormEditData;

//==================================================================

//      for internal Drag&Drop:

#define SC_DROP_NAVIGATOR       1
#define SC_DROP_TABLE           2

struct ScDragData
{
    String              aLinkDoc;
    String              aLinkTable;
    String              aLinkArea;
    ScDocument*         pJumpLocalDoc;
    String              aJumpTarget;
    String              aJumpText;
};

//==================================================================


class ScModule: public ScModuleDummy, public SfxListener
{
    Timer               aIdleTimer;
    Timer               aSpellTimer;
    ScDragData          aDragData;
    ScMessagePool*      pMessagePool;
    //  globalen InputHandler gibt's nicht mehr, jede View hat einen
    ScInputHandler*     pRefInputHandler;
    ScTeamDlg*          pTeamDlg;
    ScViewCfg*          pViewCfg;
    ScDocCfg*           pDocCfg;
    ScAppCfg*           pAppCfg;
    ScInputCfg*         pInputCfg;
    ScPrintCfg*         pPrintCfg;
    ScNavipiCfg*        pNavipiCfg;
    ColorConfig*        pColorConfig;
    SvtCTLOptions*      pCTLOptions;
    SfxErrorHandler*    pErrorHdl;
    SvxErrorHandler*    pSvxErrorHdl;
    ScFormEditData*     pFormEditData;
    USHORT              nCurRefDlgId;
    BOOL                bIsWaterCan;
    BOOL                bIsInEditCommand;

public:
                    ScModule( SfxObjectFactory* pFact );
    virtual         ~ScModule();

    virtual SfxModule*  Load();
    virtual void        FillStatusBar(StatusBar &rBar);

    virtual void        Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

    void                DeleteCfg();

                        // von der Applikation verschoben:

    DECL_LINK( IdleHandler,     Timer* );   // Timer statt idle
    DECL_LINK( SpellTimerHdl,   Timer* );
    DECL_LINK( CalcFieldValueHdl, EditFieldInfo* );

    void                AnythingChanged();

    //  Drag & Drop:
    const ScDragData&   GetDragData() const     { return aDragData; }
    void                ResetDragObject();

    void                SetWaterCan( BOOL bNew )    { bIsWaterCan = bNew; }
    BOOL                GetIsWaterCan() const       { return bIsWaterCan; }

    void                SetInEditCommand( BOOL bNew )   { bIsInEditCommand = bNew; }
    BOOL                IsInEditCommand() const         { return bIsInEditCommand; }

    // Options:
    const ScViewOptions&    GetViewOptions  ();
    const ScDocOptions&     GetDocOptions   ();
    const ScAppOptions&     GetAppOptions   ();
    const ScInputOptions&   GetInputOptions ();
    const ScPrintOptions&   GetPrintOptions ();
    void                    SetAppOptions   ( const ScAppOptions& rOpt );
    void                    SetInputOptions ( const ScInputOptions& rOpt );
    void                    SetPrintOptions ( const ScPrintOptions& rOpt );

    static void         GetSpellSettings( USHORT& rDefLang, USHORT& rCjkLang, USHORT& rCtlLang,
                                        BOOL& rAutoSpell, BOOL& rHideAuto );

    USHORT              GetOptDigitLanguage();      // from CTL options

    ColorConfig&        GetColorConfig();
    SvtCTLOptions&      GetCTLOptions();


    //  InputHandler:
    void                InputEnterHandler( BYTE nBlockMode = 0 );
    ScInputHandler*     GetInputHdl( ScTabViewShell* pViewSh = NULL, BOOL bUseRef = TRUE );

    ScInputHandler*     GetRefInputHdl();

    // Kommunikation mit Funktionsautopilot

    ScFormEditData*     GetFormEditData()       { return pFormEditData; }

    void                SetTeamDlg( ScTeamDlg* pDlg )           { pTeamDlg = pDlg; }
    ScTeamDlg*          GetTeamDlg() const                      { return pTeamDlg; }
    USHORT              GetCurRefDlgId() const                  { return nCurRefDlgId; }

    //virtuelle Methoden fuer den Optionendialog
};

#define SC_MOD() ( *(ScModule**) GetAppData(BF_SHL_CALC) )

} //namespace binfilter
#endif


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
