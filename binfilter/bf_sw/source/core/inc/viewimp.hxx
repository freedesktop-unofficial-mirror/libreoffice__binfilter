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
#ifndef _VIEWIMP_HXX
#define _VIEWIMP_HXX

#include <bf_svtools/bf_solar.h>


#include <vcl/timer.hxx>
#include <tools/color.hxx>
#include <bf_svx/svdtypes.hxx>

#include "swtypes.hxx"
#include "swrect.hxx"
#include <tools/debug.hxx> //for strip
#ifdef ACCESSIBLE_LAYOUT
class Fraction;
#endif
namespace binfilter {
class ViewShell;
class SwFlyFrm;
class SwViewOption;
class SwScrollAreas;
class SwScrollColumn;
class SwFrm;
class SwDrawView;
class SdrPageView;
class SwPageFrm;
class ExtOutputDevice;
class SdrPaintInfoRec;
#ifdef ACCESSIBLE_LAYOUT
class SwAccessibleMap;
class SdrObject;
#endif
class SwPagePreviewLayout;
} //namespace binfilter

#include <prevwpage.hxx>
#include <vector>
namespace binfilter {
class SwViewImp
{
    friend class ViewShell;

    // for paint of page preview
    friend class SwPagePreviewLayout;

    ViewShell *pSh;             //Falls jemand einen Imp durchreicht und doch
                                //mal eine ViewShell braucht hier die
                                //Rueckwaertsverkettung.

    SdrPageView *pSdrPageView;  //Genau eine Seite fuer unsere DrawView

    BOOL bFirstPageInvalid  :1; //Pointer auf erste Seite ungueltig?
    BOOL bNextScroll        :1; //Scroll in der folgenden EndAction erlaubt?
    BOOL bScroll            :1; //Scroll in der aktuellen EndAction erlaubt?
    BOOL bScrolled          :1; //Wurde gescrolled? Dann im Idle aufraeumen.

    BOOL bResetXorVisibility:1; //StartAction/EndAction
    BOOL bShowHdlPaint      :1; //LockPaint/UnlockPaint
    BOOL bResetHdlHiddenPaint:1;//  -- "" --
    BOOL bPaintInScroll     :1; //Paint (Update() im ScrollHdl der ViewShell

    BOOL bSmoothUpdate      :1; //Meber fuer SmoothScroll
    BOOL bStopSmooth        :1;
    BOOL bStopPrt           :1; // Stop Printing

    USHORT nRestoreActions  ; //Die Anzahl der zu restaurierenden Actions (UNO)
    SwRect aSmoothRect;


    /**
        Signal whether to stop printing.

        @param _useless just to fit macro
    */
    DECL_LINK(SetStopPrt, void * _useless = NULL);
public:
    ~SwViewImp();

    const ViewShell *GetShell() const { return pSh; }
          ViewShell *GetShell()       { return pSh; }

    void SetFirstVisPageInvalid() { bFirstPageInvalid = TRUE; }

    //Wird vom Layout ggf. waehrend einer Action gerufen, wenn der
    //Verdacht besteht, dass es etwas drunter und drueber geht.
    void ResetScroll()        { bScroll = FALSE; }

    // neues Interface fuer StarView Drawing
          SdrPageView*GetPageView()       { return pSdrPageView; }
    const SdrPageView*GetPageView() const { return pSdrPageView; }
};
} //namespace binfilter
#endif //_VIEWIMP_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
