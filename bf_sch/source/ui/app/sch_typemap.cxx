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

#include <bf_svx/eeitem.hxx>

#include "eetext.hxx"
#include <bf_svx/fontitem.hxx>
#include <bf_svx/postitem.hxx>
#include <bf_svx/wghtitem.hxx>
#include <bf_svx/shdditem.hxx>
#include <bf_svx/cntritem.hxx>
#include <bf_svx/crsditem.hxx>
#include <bf_svx/udlnitem.hxx>
#include <bf_svx/fhgtitem.hxx>
#include <bf_svx/colritem.hxx>

#include <bf_svx/svxids.hrc>

#define ITEMID_FMTSPLIT     0
#define ITEMID_PAGEMODEL    0
#include "eetext.hxx"

#define ITEMID_LINE         0
#define ITEMID_BRUSH        0
#define ITEMID_FMTBREAK     0
#define ITEMID_FMTKEEP      0
#define ITEMID_SIZE         0
#include <bf_svx/sizeitem.hxx>

#define ITEMID_PAGE         0


#include <bf_svtools/stritem.hxx>

#define ITEMID_AUTHOR       0
#define ITEMID_DATE         0
#define ITEMID_TEXT         0

#define ITEMID_SEARCH       0

#define ITEMID_HORJUSTIFY   0
#define ITEMID_VERJUSTIFY   0
#define ITEMID_ORIENTATION  0

#include <bf_svx/zoomitem.hxx>

#define ITEMID_CHARTSTYLE   0
#include <bf_svx/chrtitem.hxx>

#include <bf_sfx2/msg.hxx>

namespace binfilter {

/*?*/ typedef SfxVoidItem   CharSetItem;
/*?*/ typedef SfxVoidItem   FontFamilyItem;
/*?*/ typedef SfxVoidItem   FontPitchItem;
/*?*/ typedef SfxVoidItem   FontAlignItem;
/*?*/ typedef SfxVoidItem   FontWeightItem;
/*?*/ typedef SfxVoidItem   FontUnderlineItem;
/*?*/ typedef SfxVoidItem   FontStrikeoutItem;
/*?*/ typedef SfxVoidItem   FontItalicItem;
/*?*/ typedef SfxVoidItem   SvxDbTypeItem;
/*?*/ typedef SfxVoidItem SvxLineSpaceItem;
/*?*/ typedef SfxVoidItem   SvxInterLineSpaceItem;
/*?*/ typedef SfxVoidItem   SvxBreakItem;
/*?*/ typedef SfxVoidItem   BrushStyleItem;
/*?*/ typedef SfxVoidItem   SvxNumTypeItem;
/*?*/ typedef SfxVoidItem   SvxShadowLocationItem;
/*?*/ typedef SfxVoidItem   SvxChooseControlEnumItem;
/*?*/ typedef SfxVoidItem   SvxDrawToolEnumItem;
/*?*/ typedef SfxVoidItem   SvxChooseControlItem;
/*?*/ typedef SfxVoidItem   SvxDrawToolItem;
/*?*/ typedef SfxVoidItem   SvxCellHorJustifyEnumItem;
/*?*/ typedef SfxVoidItem   SvxCellVerJustifyEnumItem;
/*?*/ typedef SfxVoidItem   SvxCellOrientationEnumItem;
/*?*/ typedef SfxEnumItem   SvxStyleTypeItem;

#define SFX_TYPEMAP
#include "schslots.hxx"





}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
