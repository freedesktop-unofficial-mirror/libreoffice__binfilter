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
#ifndef _SFXAPPIMP_HXX
#define _SFXAPPIMP_HXX

#include <tools/time.hxx>
#include <bf_tools/string.hxx>
class MenuBar;
class BasicManager;
class Timer;
namespace binfilter {

class SfxTbxCtrlFactArr_Impl;
class SfxStbCtrlFactArr_Impl;
class SfxMenuCtrlFactArr_Impl;
class SfxViewFrameArr_Impl;
class SfxViewShellArr_Impl;
class SfxObjectShellArr_Impl;
class IntroWindow_Impl;
class SfxTemplateDialog;
class SfxDialogLibraryContainer;
class SfxScriptLibraryContainer;
class SfxBasicTestWin;
class UniqueIndex;

struct SfxApplication_Impl
{
    Time                        aAutoSaveTime;
    String                      aMemExceptionString;
    String                      aResWarningString;
    String                      aResExceptionString;
    String                      aSysResExceptionString;
    String                      aDoubleExceptionString;
    String                      aBasicSourceName;
    SfxTbxCtrlFactArr_Impl*     pTbxCtrlFac;
    SfxStbCtrlFactArr_Impl*     pStbCtrlFac;
    SfxMenuCtrlFactArr_Impl*    pMenuCtrlFac;
    SfxViewFrameArr_Impl*       pViewFrames;
    SfxViewShellArr_Impl*       pViewShells;
    SfxObjectShellArr_Impl*     pObjShells;
    MenuBar*                    pEmptyMenu;         // dummy for no-menu
    IntroWindow_Impl*           pIntro;
    UniqueIndex*                pEventHdl;          // Hook-Liste fuer UserEvents
    SfxTemplateDialog*          pTemplateDlg;
    SfxScriptLibraryContainer*  pBasicLibContainer;
    SfxDialogLibraryContainer*  pDialogLibContainer;
    SfxBasicTestWin*            pBasicTestWin;
    Timer*                      pAutoSaveTimer;
    USHORT                      nDocNo;             // Laufende Doc-Nummer (AutoName)
    USHORT                      nWarnLevel;
    BOOL                        bConfigLoaded:1;
    BOOL                        bAutoSaveNow:1;     // ist TRUE, wenn der Timer abgelaufen ist, wenn die App nicht aktiv war

    SfxApplication_Impl() : aAutoSaveTime( Time::EMPTY ) {}
};

}//end of namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
