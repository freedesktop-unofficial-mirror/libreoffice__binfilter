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

#ifndef _SVSTDARR_HXX
#define _SVSTDARR_USHORTS
#endif


#include <viewopt.hxx>
#include <frmtool.hxx>
#include <viscrs.hxx>

#include <horiornt.hxx>

#include <crsrsh.hxx>
#include <dview.hxx>
#include <txtfrm.hxx>   // SwTxtFrm
#include <ndtxt.hxx>
#include <drawfont.hxx>

#include <comcore.hrc>          // ResId fuer Abfrage wenn zu Search & Replaces
namespace binfilter {

extern void SwCalcPixStatics( OutputDevice *pOut );


//Damit beim ShowCrsr nicht immer wieder die gleiche Size teuer ermittelt
//werden muss, hier statische Member, die beim Wechsel des MapModes
// angepasst werden

long SwSelPaintRects::nPixPtX = 0;
long SwSelPaintRects::nPixPtY = 0;
MapMode* SwSelPaintRects::pMapMode = 0;


#ifdef SHOW_BOOKMARKS
#define SHOWBOOKMARKS1( nAct )          ShowBookmarks( GetShell(),nAct );
#else
#define SHOWBOOKMARKS1( nAct )
#endif

#ifdef SHOW_REDLINES
#define SHOWREDLINES1( nAct )           ShowRedlines( GetShell(),nAct );
#else
#define SHOWREDLINES1( nAct )
#endif

/*N*/ SwVisCrsr::~SwVisCrsr()
/*N*/ {
/*N*/ #ifdef SW_CRSR_TIMER
/*N*/   if( bTimerOn )
/*N*/       Stop();     // Timer stoppen
/*N*/ #endif
/*N*/
/*N*/   if( bIsVisible && aTxtCrsr.IsVisible() )
/*?*/       aTxtCrsr.Hide();
/*N*/
/*N*/   pCrsrShell->GetWin()->SetCursor( 0 );
/*N*/ }

// ------ Ab hier Klassen / Methoden fuer die Selectionen -------

/*N*/ SwSelPaintRects::~SwSelPaintRects()
/*N*/ {
/*N*/   Hide();
/*N*/ }

/*N*/ void SwSelPaintRects::Hide()
/*N*/ {
/*N*/   SwRects::Remove( 0, Count() );
/*N*/ }

/*N*/ SwShellCrsr::~SwShellCrsr() {}

/*N*/ SwShellCrsr::operator SwShellCrsr* () { return this; }

/*N*/ SwShellTableCrsr::~SwShellTableCrsr() {}

/*N*/ void SwShellTableCrsr::SetMark()              { SwShellCrsr::SetMark(); }
/*N*/ SwShellTableCrsr::operator SwShellCrsr* ()        { return this; }
/*N*/ SwShellTableCrsr::operator SwTableCursor* ()  { return this; }
/*N*/ SwShellTableCrsr::operator SwShellTableCrsr* ()   { return this; }

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
