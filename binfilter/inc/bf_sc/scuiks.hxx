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
#ifndef SC_UIKS_HRC
#define SC_UIKS_HRC

#include <usr/uiks.hrc>
namespace binfilter {

#define UIK_XADDRESSABLECELL            UIK_STARCALC(00)
#define UIK_XTABLECOLUMN                UIK_STARCALC(01)
#define UIK_XTABLEROW                   UIK_STARCALC(02)
#define UIK_XCOLUMNROWRANGE             UIK_STARCALC(03)
#define UIK_XADDRESSABLECELLRANGE       UIK_STARCALC(04)
#define UIK_XFORMULAARRAY               UIK_STARCALC(05)
#define UIK_XTABLEOPERATION             UIK_STARCALC(06)
#define UIK_XMERGEABLE                  UIK_STARCALC(07)
#define UIK_XCELLSERIES                 UIK_STARCALC(08)
#define UIK_XCELLRANGES                 UIK_STARCALC(09)
#define UIK_XINDENT                     UIK_STARCALC(0A)
#define UIK_XSPREADSHEETDOCUMENT        UIK_STARCALC(0B)
#define UIK_XCALCULATE                  UIK_STARCALC(0C)
#define UIK_XGOALSEEK                   UIK_STARCALC(0D)
#define UIK_XDOCUMENTAUDITING           UIK_STARCALC(0E)
#define UIK_XCELLRANGESOURCE            UIK_STARCALC(0F)
#define UIK_XNAMEDRANGE                 UIK_STARCALC(10)
#define UIK_XNAMEDRANGES                UIK_STARCALC(11)
#define UIK_XLABELRANGE                 UIK_STARCALC(12)
#define UIK_XLABELRANGES                UIK_STARCALC(13)
#define UIK_XFILELINK                   UIK_STARCALC(14)
#define UIK_XAREALINK                   UIK_STARCALC(15)
#define UIK_XDDELINK                    UIK_STARCALC(16)
#define UIK_XSHEETLINKS                 UIK_STARCALC(17)
#define UIK_XAREALINKS                  UIK_STARCALC(18)
#define UIK_XDDELINKS                   UIK_STARCALC(19)
#define UIK_XTABLESHEETS                UIK_STARCALC(1A)
#define UIK_XTABLESHEET                 UIK_STARCALC(1B)
#define UIK_XSHEETPASTETARGET           UIK_STARCALC(1C)
#define UIK_XSHEETAUDITING              UIK_STARCALC(1D)
#define UIK_XSHEETOUTLINE               UIK_STARCALC(1E)
#define UIK_XCELLMOVEMENT               UIK_STARCALC(1F)
#define UIK_XPRINTAREAS                 UIK_STARCALC(20)
#define UIK_XSHEETLINKDESTINATION       UIK_STARCALC(21)
#define UIK_XSCENARIO                   UIK_STARCALC(22)
#define UIK_XSCENARIOS                  UIK_STARCALC(23)
#define UIK_XTABLECOLUMNS               UIK_STARCALC(24)
#define UIK_XTABLEROWS                  UIK_STARCALC(25)
#define UIK_XTABLEFILTERDESCRIPTOR      UIK_STARCALC(26)
#define UIK_XADVANCEDFILTERSOURCE       UIK_STARCALC(27)
#define UIK_XTABLESORTDESCRIPTOR        UIK_STARCALC(28)
#define UIK_XSUBTOTALFIELD              UIK_STARCALC(29)
#define UIK_XSUBTOTALDESCRIPTOR         UIK_STARCALC(2A)
#define UIK_XIMPORTDESCRIPTOR           UIK_STARCALC(2B)
#define UIK_XCONSOLIDATIONDESCRIPTOR    UIK_STARCALC(2C)
#define UIK_XDATABASERANGE              UIK_STARCALC(2D)
#define UIK_XDATABASERANGES             UIK_STARCALC(2E)
#define UIK_XDATAPILOTFIELD             UIK_STARCALC(2F)
#define UIK_XDATAPILOTFIELDS            UIK_STARCALC(30)
#define UIK_XDATAPILOTDESCRIPTOR        UIK_STARCALC(31)
#define UIK_XDATAPILOTTABLE             UIK_STARCALC(32)
#define UIK_XDATAPILOTTABLES            UIK_STARCALC(33)
//#define UIK_XSORTABLE                 UIK_STARCALC(34)
#define UIK_XFILTERABLE                 UIK_STARCALC(35)
#define UIK_XSUBTOTALSOURCE             UIK_STARCALC(36)
#define UIK_XIMPORTTARGET               UIK_STARCALC(37)
#define UIK_XCONSOLIDATION              UIK_STARCALC(38)
#define UIK_XSHEETCHART                 UIK_STARCALC(39)
#define UIK_XCHARTS                     UIK_STARCALC(3A)
#define UIK_XSHEETANNOTATION            UIK_STARCALC(3B)
#define UIK_XSHEETANNOTATIONS           UIK_STARCALC(3C)
#define UIK_XSHEETANNOTATIONANCHOR      UIK_STARCALC(3D)
#define UIK_XTABLECONDITION             UIK_STARCALC(3E)
#define UIK_XTABLECONDITIONALENTRY      UIK_STARCALC(3F)
#define UIK_XTABLECONDITIONALFORMAT     UIK_STARCALC(40)
#define UIK_XTABLEVALIDATION            UIK_STARCALC(41)
#define UIK_XHEADERFOOTERCONTENT        UIK_STARCALC(42)
#define UIK_XVIEWPANE                   UIK_STARCALC(43)
#define UIK_XSTARCALCVIEW               UIK_STARCALC(44)
#define UIK_XCELLCURSOR                 UIK_STARCALC(45)
#define UIK_XCELLCONTENTCURSOR          UIK_STARCALC(46)
#define UIK_XCELLRANGECURSOR            UIK_STARCALC(47)
#define UIK_XCELLRANGESCURSOR           UIK_STARCALC(48)
#define UIK_XFORMULACURSOR              UIK_STARCALC(49)
#define UIK_XFUNCTIONDESCRIPTION        UIK_STARCALC(4A)
#define UIK_XFUNCTIONLIST               UIK_STARCALC(4B)
#define UIK_XRECENTFUNCTIONS            UIK_STARCALC(4C)
#define UIK_XCELLCOLLECTION             UIK_STARCALC(4D)
#define UIK_XFIELDCONTAINER             UIK_STARCALC(4E)
#define UIK_XSELECTIONCHANGELISTENER    UIK_STARCALC(4F)



} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
